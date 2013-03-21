
#include "ParameterList.h"

/**
 * Constructs a new parameter list.
 */
ParameterList::ParameterList()
{
	
	
}

/**
 * Constructs a new parameter list from copy.
 * @param copy Parameter list to copy.
 */
ParameterList::ParameterList( const ParameterList &copy )
{
	Parameter *newParameter;
	
	for (unsigned int i = 0; i < copy.parameters.size(); i++ ) {
		newParameter = new Parameter;
		newParameter->type = copy.parameters[i]->type;
		newParameter->title = copy.parameters[i]->title;
		newParameter->minValue = copy.parameters[i]->minValue;
		newParameter->stepLength = copy.parameters[i]->stepLength;
		newParameter->stepCount = copy.parameters[i]->stepCount;
		newParameter->loop = copy.parameters[i]->loop;
		newParameter->currentStep = copy.parameters[i]->currentStep;
		this->parameters.push_back( newParameter );
	}
	
}

/**
 * Destructs the parameter list.
 */
ParameterList::~ParameterList()
{
	
	for (unsigned int i = 0; i < this->parameters.size(); i++ )
		delete this->parameters[i];
	
	this->parameters.clear();
	
}

/**
 * Tries to set the parameter values using the values of given parameter
 * list. Does NOT add or change any parameters. Just tries to set the
 * values.
 * @param copy Parameter list whose values to use.
 */
void ParameterList::setParameters( const ParameterList &copy )
{

	for (unsigned int i = 0;
	      i < this->parameters.size() && i < copy.parameters.size();
	      i++ ) {
	      	
		this->parameters[i]->currentStep = copy.parameters[i]->currentStep;
		
		if ( this->parameters[i]->stepCount > 0
		     && this->parameters[i]->currentStep
		        > this->parameters[i]->stepCount )
		{
			this->parameters[i]->currentStep = this->parameters[i]->stepCount;
		}
		
	}
	
}

/**
 * Adds a new parameter.
 * @param type       Type of the parameter.
 * @param title      Name of the parameter.
 * @param minValue   Minimum value of the parameter.
 * @param stepLength Length of a step.
 * @param stepCount  Number of possible steps, zero for unlimited steps.
 * @param loop       Tells whether the value should loop at both ends.
 * @return Index of the new parameter.
 */
int ParameterList::addParameter( EParameterType type,
                                 const std::string &title, int minValue,
                                 int stepLength, int stepCount, bool loop )
{
	
	Parameter *newParameter = new Parameter;
	newParameter->type = type;
	newParameter->title = title;
	newParameter->minValue = minValue;
	newParameter->stepLength = stepLength;
	newParameter->stepCount = stepCount;
	newParameter->loop = loop;
	newParameter->currentStep = 0;
	this->parameters.push_back( newParameter );
	return this->parameters.size() - 1;
	
}

/**
 * Tries to set the parameter value to given value. It will be converted to
 * currentStep value, so invalid step values are converted to closest match.
 * @param index Index of the parameter.
 * @param value The value.
 */
void ParameterList::setParameterValue( int index, int value )
{
	
	if ( index < 0 || index >= (int)this->parameters.size() ) {
		return;
	}
	
	if ( value < this->parameters[index]->minValue ) {
		this->parameters[index]->currentStep = 0;
	}
	else if ( this->parameters[index]->stepCount > 0
	          && value >= this->parameters[index]->minValue
	                      + this->parameters[index]->stepLength
	                      * ( this->parameters[index]->stepCount - 1 ) )
	{
		this->parameters[index]->currentStep =
			this->parameters[index]->stepCount - 1;
	}
	else {
		value -= this->parameters[index]->minValue;
		this->parameters[index]->currentStep =
			( int )( 0.5 + (double)value / this->parameters[index]->stepLength );
	}
	
}


/**
 * Increases the parameter.
 * @param index Index of the parameter.
 * @param steps Steps to increase.
 */
void ParameterList::increaseParameterValue( int index, int steps )
{
	
	if ( index < 0 || index >= (int)this->parameters.size() ) {
		return;
	}
	
	this->parameters[index]->currentStep += steps;

	if ( this->parameters[index]->currentStep < 0
	     && !this->parameters[index]->loop ) {
		this->parameters[index]->currentStep = 0;
	}
	else if ( this->parameters[index]->stepCount > 0 ) {
		//Check for limits..
		if ( this->parameters[index]->currentStep
		     >= this->parameters[index]->stepCount
		     && !this->parameters[index]->loop )
		{
			this->parameters[index]->currentStep =
				this->parameters[index]->stepCount - 1;
		}
		else if ( this->parameters[index]->loop ) {
			
			this->parameters[index]->currentStep %=
				this->parameters[index]->stepCount;
			if ( this->parameters[index]->currentStep < 0 )
			{
				this->parameters[index]->currentStep +=
					this->parameters[index]->stepCount;
			}
			
		}
	}
	
}

/**
 * Returns the value of the parameter.
 * @param index Index of the parameter.
 * @return Value of the parameter.
 */
int ParameterList::getParameterValue( int index )
{
	
	if ( index < 0 || index >= (int)this->parameters.size() ) {
		return 0;
	}
	
	return this->parameters[index]->minValue
	       + ( this->parameters[index]->currentStep
	           * this->parameters[index]->stepLength );
	
}

/**
 * Tells the parameter text.
 * @param index Index of the parameter.
 * @param text  String to store the parameter text.
 */
void ParameterList::getParameterText( int index, std::string &text )
{
	
	if ( index < 0 || index >= (int)this->parameters.size() ) {
		text = "N/A";
		return;
	}
	
	char number[20];
	
	//The text will be different depending on parameter type.
	if ( this->parameters[index]->type == BOOLEAN ) {
		if ( this->parameters[index]->currentStep )
			text = "ON";
		else
			text = "OFF";
	}
	else {
		sprintf( number, "%d", this->getParameterValue( index ) );
		text = number;
		switch ( this->parameters[index]->type ) {
			case ANGLE:
				text += " deg";
				break;
			case TIME:
				text += " ms";
				break;
				
			default:
				break;
		}
	}
	
}

/**
 * Tells the parameter title (=name).
 * @param index Index of the parameter.
 * @param title String to store the title.
 */
void ParameterList::getParameterTitle( int index, std::string &title )
{
	
	if ( index < 0 || index >= (int)this->parameters.size() ) {
		title = "N/A";
		return;
	}
	
	title = this->parameters[index]->title;
	
}
