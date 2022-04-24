MINE		= ft_container
REAL		= std_container
MINE_SRC	= main.cpp
REAL_SRC	= real_main.cpp
MINE_OBJ	= $(MINE_SRC:.cpp=.o)
REAL_OBJ	= $(REAL_SRC:.cpp=.o)
CXX			= clang++
RM			= rm -f
CXXFLAGS	= -g3 -Wall -Wextra -Werror -std=c++98 -fsanitize=address -I .

all:		$(MINE) ${REAL}

%.o: %.cpp
			$(CXX) $(CXXFLAGS) -c $< -o $@
			
$(MINE):	$(MINE_OBJ)
			@echo "Compiling program with my container..."
			$(CXX) $(CXXFLAGS) -o $(MINE) $(MINE_OBJ)

$(REAL):	$(REAL_OBJ)
			@echo "Compiling program with the real container..."
			$(CXX) $(CXXFLAGS) -o $(REAL) $(REAL_OBJ)

clean:
			@$(RM) $(REAL_OBJ)
			@$(RM) $(MINE_OBJ)

fclean:		clean
			$(RM) $(REAL)
			$(RM) $(MINE)
			$(RM) $(MINE_OBJ)
			$(RM) $(REAL_OBJ)

re:			fclean all

.PHONY:		all clean fclean re