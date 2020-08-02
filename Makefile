# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ravernhe <ravernhe@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/30 17:25:22 by ravernhe          #+#    #+#              #
#    Updated: 2020/03/09 12:14:20 by ravernhe         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = doom-nukem

CC = clang
CFLAG = -Wall -Wextra -Werror

SRC_PATH	= ./srcs/
INC_PATH	= ./includes/
OBJ_PATH	= ./obj/
EDT_PATH	= ./map_editor/

LFT_PATH		= ./libft/
LIBFT_FLAG	= -L$(LFT_PATH) -lft
LIBFT				= $(LFT_PATH)libft.a
INCLIBFT  	= $(LFT_PATH)includes

SDL_PATH 		= ./SDL2-2.0.10/
LIBSDL_ROOT = ./libSDL2/
LIBSDL_PATH = ./libSDL2/lib/
LIBSDL			= $(LIBSDL_PATH)libSDL2.a
INCSDL      = $(LIBSDL_ROOT)include/
SDL_FLG 		= -L$(LIBSDL_PATH) -lSDL2 -lSDL2_mixer
CURL_SDL 		= `curl https://www.libsdl.org/release/SDL2-2.0.10.zip -o sdl2.zip`

MIX_PATH 		= ./SDL2_mixer-2.0.4/
LIBMIX_ROOT = ./libSDL2/
LIBMIX_PATH = ./libSDL2/lib/
LIBMIX			= $(LIBMIX_PATH)libSDL2_mixer.a
CURL_MIX 		= `curl https://www.libsdl.org/projects/SDL_mixer/release/SDL2_mixer-2.0.4.zip -o sdl2_Mixer.zip`

OBJ_FILE = $(SRC_FILE:.c=.o)
SRC_FILE = 	main.c\
				hit.c\
				main_tools_1.c\
				tourelle.c\
				init.c\
				get_event.c\
				exit.c\
				world_gen.c\
				world_gen_tools_1.c\
				world_gen_tools_2.c\
				matrice_tools_1.c\
				matrice_tools_2.c\
				matrice_tools_3.c\
				shoot.c\
				shoot_tools_1.c\
				obj_parser.c\
				obj_parser_tools.c\
				obj_parser_tools_2.c\
				obj_parser_tools_3.c\
				obj_parser_tools_4.c\
				algo_tools.c\
				draw_tool.c\
				draw_tools_1.c\
				draw_tools_2.c\
				draw_tools_3.c\
				vector_tools_1.c\
				vector_tools_2.c\
				clipping.c\
				clipping_tools_1.c\
				clipping_tools_2.c\
				display_tools_1.c\
				display_tools_2.c\
				display_thread_tools_2.c\
				display_thread_tools_3.c\
				neo_xpm_parser.c\
				neo_xpm_parser_tool_1.c\
				fill_texture.c\
				fill_texture_tools_1.c\
				movement.c\
				movement_tools_1.c\
				movement_tools_2.c\
				movement_tools_3.c\
				movement_tools_4.c\
				movement_tools_5.c\
				fill_texture_tools_2.c\

OBJ      = $(addprefix $(OBJ_PATH),$(OBJ_FILE))

all: libft sdl mix $(NAME)

$(NAME): $(OBJ) $(LIBFT)
		@$(CC) $(CFLAG) -lm $(LIBFT_FLAG) $(SDL_FLG) -o $@ $^ -lpthread

$(OBJ_PATH)%.o: $(SRC_PATH)%.c Makefile includes/doom.h
		@mkdir -p $(OBJ_PATH)
		@$(CC) $(CFLAG) -I $(INC_PATH) -I $(INCLIBFT) -I $(INCSDL) -o $@ -c $<

libft: $(LIBFT)

$(LIBFT):   $(LFT_PATH)
		@make -C $(LFT_PATH)

sdl: $(LIBSDL)

$(LIBSDL):
		@$(CURL_SDL)
		@unzip sdl2.zip
		@rm sdl2.zip
		@mkdir -p $(LIBSDL_ROOT)
		@cd $(SDL_PATH) && ./configure --prefix=$(PWD)/$(LIBSDL_ROOT)
		@make -C $(SDL_PATH)
		@make install -C $(SDL_PATH)


mix: $(LIBMIX)

$(LIBMIX):
		@$(CURL_MIX)
		@unzip sdl2_Mixer.zip
		@@rm sdl2_Mixer.zip
		@cd $(MIX_PATH) && ./configure --prefix=$(PWD)/$(LIBMIX_ROOT)
		@make -C $(MIX_PATH)
		@make install -C $(MIX_PATH)

editor:
	@make -C $(EDT_PATH)
	@mv $(EDT_PATH)doom_editor .

clean:
	@make -C $(LFT_PATH) clean
	@make -C $(EDT_PATH) clean
	@rm -rf $(OBJ_PATH)

fclean: clean
	@make -C $(LFT_PATH) fclean
	@make -C $(EDT_PATH) fclean
	@rm -rf $(LIBSDL_ROOT)
	@rm -rf $(SDL_PATH)
	@rm -rf $(LIBMIX_ROOT)
	@rm -rf $(MIX_PATH)
	@rm -rf $(NAME)

re: fclean all
