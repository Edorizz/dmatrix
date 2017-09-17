/* C library */
#include <string.h>
#include <stdlib.h>
#include <time.h>
/* dmatrix */
#include "dmatrix.h"

void key_callback(GLFWwindow *win, int key, int scancode, int action, int mod);

int
main(int argc, char **argv)
{
	struct dot_matrix dm;
	uint8_t scr_buf[64][64][3];

	srand(time(NULL));

	memset(scr_buf, 0, sizeof (uint8_t) * 64 * 64 * 3);
	dm.scr_buf = scr_buf[0][0];
	dm.scr_buf_w = 64;
	dm.scr_buf_h = 64;

	create_matrix(&dm, 640, 640);
	glfwSetKeyCallback(dm.win, key_callback);

	while (!glfwWindowShouldClose(dm.win)) {
		glfwPollEvents();

		scr_buf[rand() % 64][rand() % 64][2] = 255;
		update_matrix(&dm);

		render_matrix(&dm);
		glfwSwapBuffers(dm.win);
	}

	free_matrix(&dm);

	return 0;
}

void
key_callback(GLFWwindow *win, int key, int scancode, int action, int mod)
{
	switch (key) {
	case GLFW_KEY_ESCAPE:
	case GLFW_KEY_Q:
		glfwSetWindowShouldClose(win, GLFW_TRUE);
		break;
	}
}

