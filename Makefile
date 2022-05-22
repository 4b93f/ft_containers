MINE		= ft_container
REAL		= std_container
MINE_SRC	= main.cpp
REAL_SRC	= real_main.cpp
MINE_OBJ	= $(MINE_SRC:.cpp=.o)
REAL_OBJ	= std_main.o
CXX			= c++
RM			= rm -f
CXXFLAGS	= -g3 -Wall -Wextra -Werror -std=c++98 -fsanitize=address -I .

all:		$(MINE) ${REAL}

std_main.o:
			${CXX} -D ACCESS=std ${CXXFLAGS} -c main.cpp -o std_main.o

%.o: %.cpp
			$(CXX) -D ACCESS=ft $(CXXFLAGS) -c $< -o $@
			
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