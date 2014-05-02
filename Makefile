SRC	= main.cpp \
	  Player.cpp \
	  Attack.cpp \
	  Animation.cpp \
	  AnimatedSprite.cpp

NAME	= tron

CXXFLAGS= -Wall -Wextra -W -std=c++0x -g

OBJS	= $(SRC:.cpp=.o)

LDFLAGS = `pkg-config sfml-all --libs`

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
