/* Header file */
#include "shader.h"
/* C library */
#include <stdio.h>
#include <stdlib.h>

const char * const vertex_source = "#version 330 core\n\
                                    layout (location = 0) in vec3 position;\n\
                                    layout (location = 1) in vec2 uv;\n\
                                    out vec2 frag_uv;\n\
                                    void main()\n\
                                    {\n\
                                            gl_Position = vec4(position, 1.0f);\n\
                                            frag_uv = uv;\n\
                                    }";

const char * const fragment_source = "#version 330 core\n\
                                      in vec2 frag_uv;\n\
                                      out vec4 color;\n\
                                      uniform sampler2D tex;\n\
                                      void main()\n\
                                      {\n\
                                              color = texture(tex, frag_uv);\n \
                                      }";

GLuint
compile_program(void)
{
	GLuint shader_program;
	GLuint vertex_shader, fragment_shader;
	GLint status;
	char *buffer;
	int log_length;

	/* Compile shaders */
	shader_program = glCreateProgram();
	vertex_shader = compile_shader(vertex_source, GL_VERTEX_SHADER);
	fragment_shader = compile_shader(fragment_source, GL_FRAGMENT_SHADER);

	/* Attach shaders */
	glAttachShader(shader_program, vertex_shader);
	glAttachShader(shader_program, fragment_shader);

	/* Link shader program */
	glLinkProgram(shader_program);

	glGetProgramiv(shader_program, GL_LINK_STATUS, &status);
	if (status == GL_FALSE) {
		glGetProgramiv(shader_program, GL_INFO_LOG_LENGTH, &log_length);

		buffer = (char*)malloc(log_length);
		glGetProgramInfoLog(shader_program, log_length, &log_length, buffer);

		fprintf(stderr, "Failed to link shaders:\n%s", buffer);
		free(buffer);
	}

	/* Free shaders */
	glDeleteShader(vertex_shader);
	glDeleteShader(fragment_shader);

	return shader_program;
}

GLuint
compile_shader(const char *shader_source, GLenum shader_type)
{
	GLuint shader;
	GLint status;
	char *buffer;
	int log_length;

	/* Compile shader source */
	shader = glCreateShader(shader_type);
	glShaderSource(shader, 1, &shader_source, NULL);
	glCompileShader(shader);

	/* Check compilation status */
	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
	if (status == GL_FALSE) {
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &log_length);

		buffer = (char*)malloc(log_length);
		glGetShaderInfoLog(shader, log_length, &log_length, buffer);

		fprintf(stderr, "Failed to compile shader %s:\n\n"
			"-==+ ERROR LOG +==-\n\n%s\n\n\n",
			shader_source, buffer);
		free(buffer);
	}

	return shader;
}

