CC = g++
LD = g++
CFLAGS = -Wall -std=c++98 -g -O3
LDLIBS = -lm -lSDL
OBJS = Ai.o Angle.o Body.o BodyCannon.o BodyDebris.o BodyExplosion.o BodyMovable.o BodyPlanet.o BodyProjectile.o CoordinateSystem.o Coordinates.o GameEngine.o Graphics.o Item.o ParameterList.o Player.o Projectile.o ProjectileBouncing.o ProjectileLaser.o ProjectileSeeking.o ProjectileSeekingBouncing.o ProjectileShooting.o ProjectileShootingBouncing.o ProjectileSplitting.o ProjectileSplittingBouncing.o ProjectileSustaining.o Shield.o Sounds.o Sprite.o UIButton.o UIComponent.o UIText.o UITextField.o Vector.o Weapon.o WeaponSelection.o Window.o WindowCreateWorld.o WindowCredits.o WindowGame.o WindowGameOver.o WindowMainMenu.o WindowShop.o WindowLocations.o WindowPlayers.o World.o ipag.o
TARGET = ipag

all: $(TARGET)

clean: 
	rm -f $(OBJS) *~

%.o: %.cpp
	$(CC) $(CFLAGS) -c -o $@ $<

$(TARGET): $(OBJS) 
	$(LD) $(OBJS) -o $@ $(LDLIBS)

.PHONY: all clean
