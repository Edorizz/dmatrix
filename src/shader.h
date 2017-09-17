#ifndef SHADER_H
#define SHADER_H

#include <GL/glew.h>

GLuint compile_program(void);
GLuint compile_shader(const char *path, GLenum type);

#endif /* SHADER_H */

