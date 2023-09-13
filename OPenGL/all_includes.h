# include <GL\glew.h>
//GLEW
/*
GLEW
	extention wrangler
	interface for opengl above 1.1

GLEW stands for the OpenGL Extension Wrangler Library.
It is a cross-platform open-source C/C++ library that helps manage
OpenGL extensions. OpenGL itself provides a core set of functionality,
but extensions are additional features and capabilities that are not part of the core specification.

GLEW simplifies the process of loading and using OpenGL extensions.
It provides a unified interface across different platforms and makes it easier to
write portable OpenGL code. GLEW handles the details of querying the system for available
extensions, loading their function pointers, and managing their usage within your application.


There are a few alternatives to GLEW for managing OpenGL extensions in C++. Some popular alternatives include:

1. GLAD (OpenGL Loader Generator):
	GLAD is a lightweight and easy-to-use library for loading OpenGL extensions.
	It offers similar functionality to GLEW but with a simpler interface.
	GLAD supports multiple programming languages, including C and C++.
	You can generate the necessary loader code for your specific OpenGL version and extensions using the online GLAD generator tool.

2. GLEW's successor, glbinding:
	It offers a type-safe and easy-to-use interface for loading and using OpenGL extensions.
	glbinding is known for its simplicity, type safety, and modern C++ design.

3. SDL (Simple DirectMedia Layer):
	SDL is a multimedia library that supports various platforms and provides functionality for graphics, audio, input, and more.
	It includes support for OpenGL and allows you to create an OpenGL context and manage extensions.
	SDL provides a straightforward interface for OpenGL initialization and extension loading.

4. GLFW (OpenGL FrameWork):
	GLFW is a lightweight framework specifically designed for creating OpenGL applications.
	It provides a simple API for creating windows, handling input, and managing OpenGL contexts.
	GLFW also includes functions for loading and using OpenGL extensions.

5. GL3W :
	It is a simple and lightweight extension loading library specifically designed for modern OpenGL versions (3.0 and above).
	GL3W is generated using a Python script and provides a minimalistic interface for loading function pointers to OpenGL functions.
*/
# include <GLFW\glfw3.h>
//GLFW
/*
GLFW
GLFW stands for "Graphics Library Framework."
It is a lightweight and open-source library that provides a simple and
cross-platform API for creating windows,handling input, and managing OpenGL contexts.
GLFW is primarily designed for creating OpenGL applications but can also be used with other graphics libraries.

Here are some key features and functionalities of GLFW:

1. Window Management:
	GLFW provides a straightforward interface for creating windows and handling their events,
	such as resizing, moving, and closing.
	It allows you to create multiple windows and provides functions for manipulating them.

2. Input Handling:
	GLFW provides input handling for keyboard, mouse, and joystick devices.
	It allows you to detect and respond to various input events, including
	key presses, mouse movements, and joystick button presses.

3. OpenGL Context Management:
	GLFW handles the creation and management of OpenGL contexts.
	It provides functions to create an OpenGL context, set the desired OpenGL version and profile,
	and manage the swapping of buffers for double buffering.

4. Time and Timing:
	GLFW offers functions to retrieve the system time and provides a high-resolution
	timer for precise timing. This is useful for tasks such as frame rate control and animation.

5. Window and Context Configuration:
	GLFW allows you to specify various window and context attributes, such as window size, title,
	monitor selection, and multisampling settings.

6. Cross-Platform Support:
	GLFW is designed to be portable and works on multiple platforms,
	including Windows, macOS, and various Linux distributions.
	It provides a consistent API across different platforms,
	making it easier to write cross-platform applications.

7. Extension Loading:
	GLFW includes functionality to load OpenGL extensions and provides an API for querying and using them.

GLFW is often used in combination with other libraries, such as GLEW or glloadgen, to handle OpenGL extension
loading and provide additional functionality for graphics programming.

Overall, GLFW simplifies the process of window creation, input handling, and OpenGL context management,
making it a popular choice among developers for building OpenGL applications.


There are a few alternatives to GLFW for window management and input handling in OpenGL or graphics programming.
Some popular alternatives include:

1. SDL (Simple DirectMedia Layer):
	SDL is a widely used multimedia library that provides functionality for graphics, audio, input, and more.
	SDL includes support for window creation, input handling, and OpenGL context management, making it a powerful
	alternative to GLFW. SDL offers cross-platform support and has a large community and active development.

2. SFML (Simple and Fast Multimedia Library):
	Its made for 2D spaces.
	SFML is another multimedia library that provides a high-level API for graphics, audio, and input.
	SFML includes window management, input handling, and OpenGL context management features. It is designed to be simple
	and user-friendly and has support for multiple programming languages.

3. FreeGLUT:
	FreeGLUT is an open-source alternative to the original GLUT (OpenGL Utility Toolkit) library.
	It provides a simple API for creating windows and handling input in OpenGL applications.
	FreeGLUT is lightweight and easy to use, making it a good choice for small projects or simple applications.

4. Qt:
	Qt is a comprehensive cross-platform framework that offers a wide range of features,
	including GUI development, networking, multimedia, and OpenGL support.
	Qt provides a robust windowing system, input handling, and OpenGL integration.
	It is highly versatile but may have a steeper learning curve compared to other alternatives.

5. SDL2 with Dear ImGui:
	SDL2 can be combined with Dear ImGui, a user interface library, to handle window creation,
	input handling, and provide a flexible GUI system for OpenGL applications. Dear ImGui is lightweight,
	highly customizable, and widely used for creating debug interfaces or in-game development tools.

6. GLUT
7. Win32 API

*/
# include <stdio.h>
//stdio.h maily for reporting error to user in here
/*
The `stdio.h` header file is part of the C Standard Library.
It stands for "standard input/output" and provides functions for performing
input and output operations in the C programming language.

Here are some commonly used functions and types provided by `stdio.h`:

1. Standard Input/Output Functions:
   - `printf`   : Formats and prints data to the standard output (console).
   - `scanf`    : Reads formatted data from the standard input (keyboard) and stores it into variables.
   - `getchar`  : Reads a single character from the standard input.
   - `puts`     : Writes a null-terminated string to the standard output, followed by a newline character.
   - `fgets`    : Reads a line of text from a file or standard input.

2. File I/O Functions:
   - `fopen`    : Opens a file and returns a file pointer for subsequent read or write operations.
   - `fclose`   : Closes a file that was opened with `fopen`.
   - `fread`/`fwrite`   : Reads/writes a block of data from/to a file.
   - `fprintf`/`fscanf` : Similar to `printf` and `scanf`, but operates on a file stream.

3. File Positioning Functions:
   - `ftell`    : Returns the current position of the file pointer within a file.
   - `fseek`    : Sets the file position indicator for a file stream.
   - `rewind`   : Moves the file position indicator to the beginning of a file.

4. Error Handling:
   - `perror`   : Prints a descriptive error message based on the value of the `errno` variable.
   - `errno`    : An external integer variable that is set by certain functions to indicate specific errors.

These are just a few examples of the functions and types provided by `stdio.h`.
The header file is widely used in C programming for input and output operations, file handling, and error handling.
*/
# include <string.h>
# include <iostream>
//defining constant for width and height
/*
opengl uses GLuint as unsigend integer because The type "unsigned int" has a different size
depending on the platform you're building on.
I expect this to normally be 32 bits, however it could be 16 or 64  depending on the platform.
Library-specific types are often created to be typedef'd according to platform-specific rules.
This allows a generic application to use the right type without having to be aware of the platform
it will be built for. Instead, the platform-specific knowledge is constrained to a single common header file.

const GLuint WIDTH = 800;
const GLuint HEIGHT = 600;

*/
//# include <cmath>
# include <glm\glm.hpp>
# include <glm\gtc\matrix_transform.hpp>
# include <glm\gtc\type_ptr.hpp>