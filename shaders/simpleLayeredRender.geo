#version 440
layout(points) in;
layout(TRIANGLE_STRIP, max_vertices = 4) out;

void main()
{

	int layer = int(gl_in[0].gl_Position.x);

	gl_Position = vec4(-1,-1,0,1);
	gl_Layer = layer;
	EmitVertex();

	gl_Position = vec4(-1,1,0,1);
	gl_Layer = layer;
	EmitVertex();

	gl_Position = vec4(1,-1,0,1);
	gl_Layer = layer;
	EmitVertex();

	gl_Position = vec4(1,1,0,1);
	gl_Layer = layer;
	EmitVertex();

	EndPrimitive();
	
}
