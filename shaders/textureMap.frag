#version 440
uniform sampler2D backgroundImage;
in vec2 TexCoord;
out vec4 out_color;

void main(void)
{
    float col = texture(backgroundImage, TexCoord).r;
    out_color = vec4(col,col,col,1);
}
