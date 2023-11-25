NAME        = ft_nm
SRCS        = ./srcs/
INCS        = ./incs/
LIBFT_INC   = ./libft/
SUBMODULE   = submodule_directory

CC          = gcc
CFLAGS      = -Wall -Wextra -Werror $(INCLUDES) -g
LIBS        = -L ./libft/ -lft -lm

INCLUDES    = -I $(INCS) -I $(LIBFT_INC)

SRC         = $(wildcard $(SRCS)*.c)
OBJS        = $(addprefix objs/,$(notdir $(SRC:.c=.o)))

GREEN       = \033[0;32m
CYAN        = \033[0;36m
RESET       = \033[0m

all: $(NAME)

submodule_update:
	@echo "$(CYAN)Updating submodule...$(RESET)"
	git submodule update --init --recursive
	@echo "$(GREEN)Submodule updated successfully!$(RESET)"

$(NAME): $(OBJS)
	@make -C ./libft
	@echo "$(CYAN)Building $(NAME)...$(RESET)"
	@$(CC) $(OBJS) -o $(NAME) $(LIBS)
	@echo "$(GREEN)$(NAME) built successfully!$(RESET)"

objs/%.o: $(SRCS)%.c
	@mkdir -p objs
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@make -C ./libft clean
	@rm -rf objs
	@echo "$(GREEN)Object files removed!$(RESET)"

.PHONY: clean

fclean: clean
	@make -C ./libft fclean
	@rm -f $(NAME)
	@echo "$(GREEN)$(NAME) removed!$(RESET)"

.PHONY: fclean

re: fclean all
.PHONY: re
