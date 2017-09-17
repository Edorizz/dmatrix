/* Header file */
#include "dmatrix.h"
/* OpenGL */
#include <GL/glew.h>
#include <GLFW/glfw3.h>
/* GLSL Shader */
#include "shader.h"
	
int
create_matrix(struct dot_matrix *dm, int scr_w, int scr_h)
{
	int err;
	GLfloat data[] = {
		/* Position		Texture UV */
		-1.0f, -1.0f, 0.0f,     0.0f, 1.0f,
	 	 1.0f, -1.0f, 0.0f,     1.0f, 1.0f,
	 	 1.0f,  1.0f, 0.0f,     1.0f, 0.0f,

	 	 1.0f,  1.0f, 0.0f,     1.0f, 0.0f,
	 	-1.0f,  1.0f, 0.0f,     0.0f, 0.0f,
		-1.0f, -1.0f, 0.0f,     0.0f, 1.0f,
	};
	
	/* Initialize GLFW */
	if (!glfwInit()) {
		return -1;
	}

	/* Set OpenGL context version (3.3) */
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	/* Create Window */
	if ((dm->win = glfwCreateWindow(scr_w, scr_h, "dmatrix", NULL, NULL)) == NULL) {
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(dm->win);
	glfwSwapInterval(1);

	/* Initialize GLEW */
	if ((err = glewInit()) != GLEW_OK) {
		fprintf(stderr, "glewInit: %s\n", glewGetErrorString(err));
		glfwTerminate();
		return -1;
	}

	/* Compile shader */
	dm->program = compile_program();

	/* Generate buffers */
	glGenVertexArrays(1, &dm->vao);
	glGenBuffers(1, &dm->vbo);

	glBindVertexArray(dm->vao);
	glBindBuffer(GL_ARRAY_BUFFER, dm->vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof data, data, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof (GLfloat) * 5, (GLvoid *) 0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof (GLfloat) * 5, (GLvoid *) (sizeof (GLfloat) * 3));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	/* Create screen buffer texture */
	glGenTextures(1, &dm->texture);
	glBindTexture(GL_TEXTURE_2D, dm->texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, dm->scr_buf_w, dm->scr_buf_h, 0, GL_RGB, GL_UNSIGNED_BYTE, dm->scr_buf);

	return 0;
}

void
free_matrix(struct dot_matrix *dm)
{
	glfwDestroyWindow(dm->win);
	glfwTerminate();
}

void
update_matrix(struct dot_matrix *dm)
{
	glBindTexture(GL_TEXTURE_2D, dm->texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, dm->scr_buf_w, dm->scr_buf_h, 0, GL_RGB, GL_UNSIGNED_BYTE, dm->scr_buf);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void
render_matrix(struct dot_matrix *dm)
{
	glClear(GL_COLOR_BUFFER_BIT);

	glUseProgram(dm->program);
	glBindTexture(GL_TEXTURE_2D, dm->texture);
	glBindVertexArray(dm->vao);

	glDrawArrays(GL_TRIANGLES, 0, 6);

	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
	glUseProgram(0);
}

