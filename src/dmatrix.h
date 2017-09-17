#ifndef DMATRIX_H
#define DMATRIX_H

/* C library */
#include <stdio.h>
#include <stdint.h>
/* OpenGL */
#include <GL/glew.h>
#include <GLFW/glfw3.h>

struct dot_matrix {
	/* Set by user before calling create_matrix() */
	uint8_t *scr_buf;
	GLuint scr_buf_w, scr_buf_h;
	/* OpenGL */
	GLFWwindow *win;
	GLuint vao, vbo, program, texture;
};

/* One time callers */
int  create_matrix(struct dot_matrix *dm, int scr_w, int scr_h);
void free_matrix(struct dot_matrix *dm);

/* Rendering */
void update_matrix(struct dot_matrix *dm);
void render_matrix(struct dot_matrix *dm);

#endif /* DMATRIX_H */
