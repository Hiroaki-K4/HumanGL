PARENT_DIR := /home/hiroakik4/mypro/
SRCS := main.cpp glad.c Shader.cpp PerlineNoise.cpp Terrain.cpp
INCLUDE := -I../glm -I../glad/include -I../glfw/include -I.
LDFLAGS := -L$(PARENT_DIR)gl_programming/glfw/build/src `pkg-config --libs glfw3` -lglfw3 -lGL -lX11 -lpthread -lXrandr -lXi -ldl
NAME := ft_vox
CXX := g++

all: $(NAME)

$(NAME):
	$(CXX) $(SRCS) $(INCLUDE) $(LDFLAGS) -o $(NAME)

clean:
	rm -rf $(NAME)

re: clean all

.PHONY: all clean re
