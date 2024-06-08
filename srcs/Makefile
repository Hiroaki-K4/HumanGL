PARENT_DIR := /home/hiroakik4/mypro/
SRCS := main.cpp glad.c shader.cpp Human.cpp Torso.cpp Head.cpp UpperArm.cpp ForeArm.cpp UpperLeg.cpp LowerLeg.cpp
INCLUDE := -I../glm -I../glad/include -I../glfw/include -I.
LDFLAGS := -L$(PARENT_DIR)gl_programming/glfw/build/src `pkg-config --libs glfw3` -lglfw3 -lGL -lX11 -lpthread -lXrandr -lXi -ldl
NAME := HumanGL
CXX := g++

all: $(NAME)

$(NAME):
	$(CXX) $(SRCS) $(INCLUDE) $(LDFLAGS) -o $(NAME)

clean:
	rm -rf $(NAME)

re: clean all

.PHONY: all clean re
