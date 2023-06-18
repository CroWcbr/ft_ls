.DEFAULT_GOAL	:=	all

NAME			=	ft_ls

CC				=	gcc
# CFLAGS			=	-Wall -Werror -Wextra

SRC_DIR			=	./src
INC_DIR			= 	./inc
OBJ_DIR			=	./obj
LIBFT_DIR		=	./external/libft
LIBFT_LIB		=	libft.a
INC_ALL			=	-I$(INC_DIR) \
					-I$(LIBFT_DIR)/include

SRC				=	ft_ls.c \
					parse.c \
					utily.c

OBJ				=	$(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))
$(OBJ)			: 	| $(OBJ_DIR)
$(OBJ_DIR)		:
					@mkdir -p $(OBJ_DIR)
$(OBJ_DIR)/%.o	:	$(SRC_DIR)/%.c
					$(CC) $(CFLAGS) -c $< -o $@ $(INC_ALL)

RM_DIR			=	rm -rf
RM_FILE			=	rm -f

#COLORS
C_NO			=	"\033[00m"
C_OK			=	"\033[32m"
C_GOOD			=	"\033[32m"

#DEBUG
SUCCESS			=	$(C_GOOD)SUCCESS$(C_NO)
OK				=	$(C_OK)OK$(C_NO)

all				:	$(NAME)

$(NAME)			:	$(OBJ)
#					@make -C ${LIBFT_DIR}/ all
					$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(LIBFT_DIR)/$(LIBFT_LIB) $(INC_ALL)
					@echo "\tCompiling...\t" [ $(NAME) ] $(SUCCESS)

clean			:
#					@make -C ${LIBFT_DIR}/ clean
					@$(RM_DIR) $(OBJ_DIR)
					@echo "\tCleaning...\t" [ $(OBJ_DIR) ] $(OK)

fclean			:	clean
#					@${RM_FILE} $(LIBFT_DIR)/$(LIBFT_LIB)
#					@echo "\tDeleting...\t" [ $(LIBFT_LIB) ] $(OK)
					@$(RM_FILE) $(NAME)
					@echo "\tDeleting...\t" [ $(NAME) ] $(OK)

re				:	fclean all

.PHONY			:	all, clean, fclean, re
