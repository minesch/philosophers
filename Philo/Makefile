NAME = philo
CC = cc
OBJS_DIR = objs
SRCS_DIR = src
FLAGS =  -Wall -Werror -Wextra -g -Iincludes #-fsanitize=address
SRCS = $(wildcard $(SRCS_DIR)/*.c)
OBJS = $(patsubst $(SRCS_DIR)/%.c, $(OBJS_DIR)/%.o, $(SRCS))
RM = rm -rf
CCLEAN = bash ~/Cleaner_42.sh
MKDIR = mkdir -p

.DEFAULT_GOAL = all
all: $(NAME)

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c | $(OBJS_DIR)
	$(CC) $(FLAGS) -c $< -o $@

$(OBJS_DIR):
	$(MKDIR) $(OBJS_DIR)

$(NAME):  $(OBJS) | $(OBJS_DIR)
		$(CC) $(FLAGS) -o $(NAME) $(OBJS)

bonus:	all

clean:
	$(RM) $(OBJS_DIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re push
