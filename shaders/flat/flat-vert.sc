$input a_position, a_color0

#include <../mrender.sh>

void main() {
    gl_Position = mul(u_modelViewProj, vec4(a_position, 1.0));
}