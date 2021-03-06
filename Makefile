# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: qfremeau <qfremeau@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/11/23 17:10:25 by qfremeau          #+#    #+#              #
#    Updated: 2017/01/04 18:11:30 by qfremeau         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Compilation
CC =		gcc
CFLAGS =	-Wall -Wextra
ADDFLAGS =	-g

# Precompiled header
PRECOMP =	stdafx.h

# Default rule
DEFRULE =	all

# Binary
NAME =		rtv1
DST =		

# Directories
SRCDIR =	srcs
OBJDIR =	objs
ifeq ($(OS),Windows_NT)
	INCDIR =	includes\
				libft/includes
	CFSDL =		
else
	UNAME_S := $(shell uname -s)
	ifeq ($(UNAME_S),Darwin)
		ID_UN := $(shell id -un)
		INCDIR =	includes\
					libft/includes\
					/Users/$(ID_UN)/.brew/Cellar/sdl2/2.0.5/include/SDL2\
					/Users/$(ID_UN)/.brew/Cellar/sdl2_ttf/2.0.14/include/SDL2\
					-F -framework Cocoa 
		CFSDL =		
	endif
	ifeq ($(UNAME_S),Linux)
		INCDIR =	includes\
					libft/includes
		CFSDL =		`sdl2-config --cflags`
	endif
endif
PREDIR =	includes

# Sources
SRC = \
			main.c\
			esdl_init.c\
			esdl_ttf.c\
			esdl_fps.c\
			esdl_surface.c\
			esdl_events.c\
			esdl_color.c\
			esdl_pixel.c\
			esdl_image.c\
			esdl_rect.c\
			esdl_exit.c\
			v3_create.c\
			v3_operation.c\
			v3_transform.c\
			v3_unit.c\
			rt_init.c\
			rt_skybox.c\
			rt_menu.c\
			rt_view.c\
			rt_3dview.c\
			rt_scene.c\
			rt_camera.c\
			rt_material.c\
			rt_light.c\
			rt_bound_box.c\
			rt_object.c\
			rt_sphere.c\
			rt_plane.c\
			rt_ray.c\
			rt_thread.c\
			rt_hook.c\
			rt_button.c\
			rt_render.c\
			rt_events.c\
			rt_random.c\
			rt_quit.c\
			ft_list.c\
			ft_list2.c\
			ft_utils.c\
			ft_utils2.c\
			kernel_isopencl.c

OBJ =		$(SRC:.c=.o)

# Prefixes
ifeq ($(OS),Windows_NT)
	OPNCL =		-L/lib/ -lOpenCL
	LSDL2 =		-L/lib/ -lSDL2 -lSDL2_ttf
	LMATH =		
	LPTHR =		
else
	UNAME_S := $(shell uname -s)
	ifeq ($(UNAME_S),Darwin)
		OPNCL =		-framework OpenCL
		LSDL2 =		-L/Users/$(ID_UN)/.brew/Cellar/sdl2/2.0.5/lib -lSDL2\
					-L/Users/$(ID_UN)/.brew/Cellar/sdl2_ttf/2.0.14/lib -lSDL2_ttf
		LMATH =		-lm
		LPTHR =		-lpthread
	endif
	ifeq ($(UNAME_S),Linux)
		OPNCL =		-L/usr/lib/x86_64-linux-gnu -lOpenCL
		LSDL2 =		`sdl2-config --libs` -lSDL2_ttf
		LMATH =		-lm
		LPTHR =		-pthread
	endif
endif
LIBFT =		-Llibft/ -lft


# Paths foreach
OBJP =		$(addprefix $(OBJDIR)/, $(SRC:.c=.o))
INCP =		$(foreach dir, $(INCDIR), -I$(dir))
PREP =		$(addprefix $(PREDIR)/, $(PRECOMP))

# **************************************************************************** #
# SPECIAL CHARS

LOG_CLEAR		= \033[2K
LOG_UP			= \033[A
LOG_NOCOLOR		= \033[0m
LOG_BOLD		= \033[1m
LOG_UNDERLINE	= \033[4m
LOG_BLINKING	= \033[5m
LOG_BLACK		= \033[1;30m
LOG_RED			= \033[1;31m
LOG_GREEN		= \033[1;32m
LOG_YELLOW		= \033[1;33m
LOG_BLUE		= \033[1;34m
LOG_VIOLET		= \033[1;35m
LOG_CYAN		= \033[1;36m
LOG_WHITE		= \033[1;37m

# **************************************************************************** #
# RULES
.SILENT:

# Main rules
default:
	@echo -e "$(LOG_BOLD)Default execution: rule $(DEFRULE)$(LOG_NOCOLOR)"
	@make $(DEFRULE)
	@echo -e "$(LOG_BOLD)Execution finished     $(LOG_NOCOLOR)ヽ(ヅ)ノ"

all: libftcomp $(OBJDIR) $(NAME)

re: fclean all

# Compilation rules
libftcomp:
	@make all -C libft/

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@echo -e "--$(LOG_CLEAR)$(LOG_VIOLET)$(NAME)$(LOG_NOCOLOR)....................... $(LOG_YELLOW)$<$(LOG_NOCOLOR)$(LOG_UP)"
	@$(CC) $(CFLAGS) $(ADDFLAGS) -c -o $@ $^ $(INCP) $(CFSDL)

$(OBJDIR):
	@echo -e "$(LOG_CLEAR)$(LOG_BLUE)build $(NAME)$(LOG_NOCOLOR)"
	@mkdir -p $(OBJDIR)

$(NAME): $(OBJP)
	@echo -e "--$(LOG_CLEAR)$(LOG_VIOLET)$(NAME)$(LOG_NOCOLOR)....................... $(LOG_YELLOW)assembling$(LOG_NOCOLOR)$(LOG_UP)"
	@$(CC) $(CFLAGS) $(ADDFLAGS) $(LPTHR) -o $@ $^ $(OPNCL) $(LSDL2) $(LIBFT) $(LMATH) $(INCP)
	@echo -e "--$(LOG_CLEAR)$(LOG_VIOLET)$(NAME)$(LOG_NOCOLOR) compiled.............. $(LOG_GREEN)✓$(LOG_NOCOLOR)"

# MrProper's legacy
.PHONY: fclean clean glu

clean:
	@echo -e "$(LOG_CLEAR)$(LOG_BLUE)clean $(NAME)$(LOG_NOCOLOR)"
	@echo -e "--$(LOG_CLEAR)$(LOG_YELLOW)Objects$(LOG_NOCOLOR) deletion............. $(LOG_RED)×$(LOG_NOCOLOR)"
	@rm -rf $(OBJDIR)
	@echo -e "$(LOG_CLEAR)$(LOG_BLUE)clean libft$(LOG_NOCOLOR)"
	@make clean -C libft/

fclean:
	@echo -e "$(LOG_CLEAR)$(LOG_BLUE)fclean libft$(LOG_NOCOLOR)"
	@make fclean -C libft/
	@echo -e "$(LOG_CLEAR)$(LOG_BLUE)fclean $(NAME)$(LOG_NOCOLOR)"
	@echo -e "--$(LOG_CLEAR)$(LOG_YELLOW)Objects$(LOG_NOCOLOR) deletion............. $(LOG_RED)×$(LOG_NOCOLOR)"
	@rm -rf $(OBJDIR)
	@echo -e "--$(LOG_CLEAR)$(LOG_YELLOW)Binary$(LOG_NOCOLOR) deletion.............. $(LOG_RED)×$(LOG_NOCOLOR)"
	@rm -f $(NAME)

glu: re clean

# SDL2 brew

sdl2:
	brew install sdl2
	brew link sdl2
	brew install sdl2_ttf
	brew link sdl2_ttf
