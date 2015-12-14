#version 440
layout(points) in;
layout(points, max_vertices = 10) out;

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


void main()
{	
	/**** RENDERING AS EXPECTED
	gl_Position = Transform*(gl_in[0].gl_Position+lookupVertex(1,0));
	fragColor = vec4(1.0f,1.0f,1.0f,1.0f);
	EmitVertex();	
	*/

	/**** RENDERING AS EXPECTED
	if(lookupVertex(1,0) == vec4(0.5f,0.0f,0.0f,0.0f))
	{
		gl_Position = Transform*(gl_in[0].gl_Position);
		fragColor = vec4(1.0f,1.0f,1.0f,1.0f);
		EmitVertex();	
	}
	*/

	/**** RENDERING AS EXPECTED
	if(lookupVertex(1,0) == vec4(0.5f,0.0f,0.0f,0.0f))
	{
		gl_Position = Transform*(gl_in[0].gl_Position+lookupVertex(1,0));
		fragColor = vec4(1.0f,1.0f,1.0f,1.0f);
		EmitVertex();	
	}
	*/

	/**** RENDERING AS EXPECTED
	int cubeindex = 0;
	if(cubeindex < 10)
	{
		gl_Position = Transform*(gl_in[0].gl_Position+lookupVertex(1,0));
		fragColor = vec4(1.0f,1.0f,1.0f,1.0f);
		EmitVertex();
	}
	*/

	/**** RENDERING AS EXPECTED
	if(texture(my_data_texture,vec3((gl_in[0].gl_Position/4).rgb)).r != 0.0f)
	{
		gl_Position = Transform*(gl_in[0].gl_Position);
		fragColor = vec4(1.0f,1.0f,1.0f,1.0f);
		EmitVertex();
	}
	*/

	// BUT NEXT PART GIVES ERROR
	//---------------------opengl-callback-start------------
	//message: glDrawArrays has generated an error (GL_INVALID_OPERATION)
	//type: ERROR
	//id: 1000
	//severity: HIGH
	//---------------------opengl-callback-end--------------
	
	if(texture(my_data_texture,vec3((gl_in[0].gl_Position/4).rgb)).r != 0.0f)
	{
		gl_Position = Transform*(gl_in[0].gl_Position+lookupVertex(1,0));
		fragColor = vec4(1.0f,1.0f,1.0f,1.0f);
		EmitVertex();
	}
}
