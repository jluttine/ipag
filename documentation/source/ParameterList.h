
#ifndef _PARAMETERLIST_H_
#define _PARAMETERLIST_H_

#include <vector>
#include <iostream>

/**
 * Author: Jaakko Luttinen
 * ParameterList is a class for different selection of different parameters.
 * It allows to add specific parameters into the list which are then easily
 * modified.
 */
class ParameterList
{
	
public:

	enum EParameterType { BOOLEAN, ANGLE, TIME, NUMBER };
	
	/**
	 * Constructs a new parameter list.
	 */
	ParameterList();
	
	/**
	 * Constructs a new parameter list from copy.
	 * @param copy Parameter list to copy.
	 */
	ParameterList( const ParameterList &copy );
	
	/**
	 * Destructs the parameter list.
	 */
	~ParameterList();

	/**
	 * Tries to set the parameter values using the values of given parameter
	 * list. Does NOT add or change any parameters. Just tries to set the
	 * values.
	 * @param copy Parameter list whose values to use.
	 */
	void setParameters( const ParameterList &copy );

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
	int addParameter( EParameterType type, const std::string &title,
	                  int minValue, int stepLength, int stepCount, bool loop);

	/**
	 * Tries to set the parameter value to given value. It will be converted
	 * to currentStep value, so invalid step values are converted to closest
	 * match.
	 * @param index Index of the parameter.
	 * @param value The value.
	 */
	void setParameterValue( int index, int value );
	
	/**
	 * Returns the number of parameters.
	 * @return Number of parameters.
	 */
	inline int getParameterCount() const  { return this->parameters.size(); };
	
	/**
	 * Increases the parameter.
	 * @param index Index of the parameter.
	 * @param steps Steps to increase.
	 */
	void increaseParameterValue( int index, int steps );
	
	/**
	 * Returns the value of the parameter.
	 * @param index Index of the parameter.
	 * @return Value of the parameter.
	 */
	int getParameterValue( int index );
	
	/**
	 * Tells the parameter text.
	 * @param index Index of the parameter.
	 * @param text  String to store the parameter text.
	 */
	void getParameterText( int index, std::string &text );
	
	/**
	 * Tells the parameter title (=name).
	 * @param index Index of the parameter.
	 * @param title String to store the title.
	 */
	void getParameterTitle( int index, std::string &title );

private:

	struct Parameter
	{
		EParameterType type; //Type of the parameter.
		std::string title; //Name of the parameter.
		int currentStep; //Current step value.
		int minValue, stepLength, stepCount; //Value coordinators.
		bool loop; //Does the value loop?
	};
	
	/**
	 * Parameters of the parameter list.
	 */
	std::vector<Parameter*> parameters;
	
};

#endif //_PARAMETERLIST_H_
