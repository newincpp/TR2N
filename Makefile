SRC	= main.cpp \
	  Player.cpp \
	  Attack.cpp \
	  Animation.cpp \
	  AnimatedSprite.cpp \
	  Input.cpp

NAME	= tron

CXXFLAGS= -Wall -Wextra -W -std=c++0x -g

OBJS	= $(SRC:.cpp=.o)

LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-audio -lsfml-network -lsfml-system

RM	= rm -f

CXX	= clang++

all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(LDFLAGS) $(OBJS) -o $(NAME)

clean:
	$(RM) $(OBJS) *.swp *~ *#

fclean: clean
	$(RM) $(NAME)

re:
	make -B -j4

.PHONY: all clean fclean re
