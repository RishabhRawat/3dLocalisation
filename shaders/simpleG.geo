#version 440
layout(points) in;
layout(TRIANGLE_STRIP, max_vertices = 15) out;

out vec4 fragColor;
uniform mat4 Transform;
uniform sampler3D my_data_texture;
uniform isampler2D lookupTableTexture;
uniform vec4 cubeVector[12];

int lookupVertexTable(int cubeindex, int vertexID)
{
	return int(texelFetch(lookupTableTexture,ivec2(vertexID,cubeindex),0).r);
}

vec4 lookupVertex(int cubeindex, int vertexID )
{	
	int id  = lookupVertexTable(cubeindex,vertexID);
	return cubeVector[id];
}

float retrieveData(vec4 pos)
{
	//return texelFetch(my_data_texture,ivec3(gl_in[0].gl_Position + pos).rgb,0).r;
	return texture(my_data_texture,vec3((gl_in[0].gl_Position/4 + pos/4).rgb)).r;
}


void main()
{
	int cubeindex = 0;
	if(retrieveData(vec4(0.0f, 0.0f, 0.0f, 0.0f)) != 0) cubeindex = cubeindex  + 1;
	if(retrieveData(vec4(1.0f, 0.0f, 0.0f, 0.0f)) != 0) cubeindex = cubeindex  + 2;
	if(retrieveData(vec4(1.0f, 1.0f, 0.0f, 0.0f)) != 0) cubeindex = cubeindex  + 4;
	if(retrieveData(vec4(0.0f, 1.0f, 0.0f, 0.0f)) != 0) cubeindex = cubeindex  + 8;

	if(retrieveData(vec4(0.0f, 0.0f, 1.0f, 0.0f)) != 0) cubeindex = cubeindex  + 16;
	if(retrieveData(vec4(1.0f, 0.0f, 0.0f, 0.0f)) != 0) cubeindex = cubeindex  + 32;
	if(retrieveData(vec4(1.0f, 1.0f, 1.0f, 0.0f)) != 0) cubeindex = cubeindex  + 64;
	if(retrieveData(vec4(0.0f, 1.0f ,0.0f, 0.0f)) != 0) cubeindex = cubeindex  + 128;
	
	if(lookupVertexTable(cubeindex,0) != -1)
	{
		gl_Position = Transform*(gl_in[0].gl_Position+lookupVertex(cubeindex,0));
		fragColor = vec4(1.0f,1.0f,1.0f,1.0f);
		EmitVertex();
		gl_Position = Transform*(gl_in[0].gl_Position+lookupVertex(cubeindex,1));
		fragColor = vec4(1.0f,1.0f,1.0f,1.0f);
		EmitVertex();
		gl_Position = Transform*(gl_in[0].gl_Position+lookupVertex(cubeindex,2));
		fragColor = vec4(1.0f,1.0f,1.0f,1.0f);
		EmitVertex();
		EndPrimitive();
	}
	if(lookupVertexTable(cubeindex,3) != -1)
	{
		gl_Position = Transform*(gl_in[0].gl_Position+lookupVertex(cubeindex,3));
		fragColor = vec4(1.0f,1.0f,1.0f,1.0f);
		EmitVertex();
		gl_Position = Transform*(gl_in[0].gl_Position+lookupVertex(cubeindex,4));
		fragColor = vec4(1.0f,1.0f,1.0f,1.0f);
		EmitVertex();
		gl_Position = Transform*(gl_in[0].gl_Position+lookupVertex(cubeindex,5));
		fragColor = vec4(1.0f,1.0f,1.0f,1.0f);
		EmitVertex();
		EndPrimitive();
	}
	if(lookupVertexTable(cubeindex,6) != -1)
	{
		gl_Position = Transform*(gl_in[0].gl_Position+lookupVertex(cubeindex,6));
		fragColor = vec4(1.0f,1.0f,1.0f,1.0f);
		EmitVertex();
		gl_Position = Transform*(gl_in[0].gl_Position+lookupVertex(cubeindex,7));
		fragColor = vec4(1.0f,1.0f,1.0f,1.0f);
		EmitVertex();
		gl_Position = Transform*(gl_in[0].gl_Position+lookupVertex(cubeindex,8));
		fragColor = vec4(1.0f,1.0f,1.0f,1.0f);
		EmitVertex();
		EndPrimitive();
	}
	if(lookupVertexTable(cubeindex,9) != -1)
	{
		gl_Position = Transform*(gl_in[0].gl_Position+lookupVertex(cubeindex,9));
		fragColor = vec4(1.0f,1.0f,1.0f,1.0f);
		EmitVertex();
		gl_Position = Transform*(gl_in[0].gl_Position+lookupVertex(cubeindex,10));
		fragColor = vec4(1.0f,1.0f,1.0f,1.0f);
		EmitVertex();
		gl_Position = Transform*(gl_in[0].gl_Position+lookupVertex(cubeindex,11));
		fragColor = vec4(1.0f,1.0f,1.0f,1.0f);
		EmitVertex();
		EndPrimitive();
	}
	if(lookupVertexTable(cubeindex,12) != -1)
	{
		gl_Position = Transform*(gl_in[0].gl_Position+lookupVertex(cubeindex,12));
		fragColor = vec4(1.0f,1.0f,1.0f,1.0f);
		EmitVertex();
		gl_Position = Transform*(gl_in[0].gl_Position+lookupVertex(cubeindex,13));
		fragColor = vec4(1.0f,1.0f,1.0f,1.0f);
		EmitVertex();
		gl_Position = Transform*(gl_in[0].gl_Position+lookupVertex(cubeindex,14));
		fragColor = vec4(1.0f,1.0f,1.0f,1.0f);
		EmitVertex();
		EndPrimitive();
	}
}
