#version 440
layout(points) in;
layout(TRIANGLE_STRIP, max_vertices = 15) out;

out vec4 fragColor;
uniform mat4 Transform;
uniform sampler3D my_data_texture;
uniform isampler2D lookupTableTexture;

vec4 lookupVertex(int cubeindex, int vertexID )
{	
	int id  = texelFetch(lookupTableTexture,ivec2(cubeindex,vertexID),0).r;
	switch(id)
	{
	case 0: return vec4(0.5f,0.0f,0.0f,0.0f);
	case 1: return vec4(1.0f,0.5f,0.0f,0.0f);
	case 2: return vec4(0.5f,1.0f,0.0f,0.0f);
	case 3: return vec4(0.0f,0.5f,0.0f,0.0f);

	case 4: return vec4(0.5f,0.0f,1.0f,0.0f);
	case 5: return vec4(1.0f,0.5f,1.0f,0.0f);
	case 6: return vec4(0.5f,1.0f,1.0f,0.0f);
	case 7: return vec4(0.0f,0.5f,1.0f,0.0f);

	case 8: return vec4(0.0f,0.0f,0.5f,0.0f);
	case 9: return vec4(1.0f,0.0f,0.5f,0.0f);
	case 10: return vec4(1.0f,1.0f,0.5f,0.0f);
	case 11: return vec4(0.0f,1.0f,0.5f,0.0f);
	default:
		gl_Position =  Transform*(vec4(0.1f,0.0f,0.1f,1.0f));
		fragColor = vec4(1.0f,1.0f,1.0f,1.0f);
		EmitVertex();
		gl_Position =  Transform*(vec4(-0.1f,0.0f,0.1f,1.0f));
		fragColor = vec4(1.0f,1.0f,1.0f,1.0f);
		EmitVertex();
		gl_Position =  Transform*(vec4(0.1f,0.1f,0.1f,1.0f));
		fragColor = vec4(1.0f,1.0f,1.0f,1.0f);
		EmitVertex();
	}
	return vec4(0.0f,0.0f,0.0f,0.0f);
}


void main()
{
	int v[8];
	int cubeindex = 0;
	
	/*
	v[0] = int(texture(my_data_texture,(gl_in[0].gl_Position/4+vec4(0.0f, 0.0f, 0.0f, 0.0f)).stp).r != 0);
	v[1] = int(texture(my_data_texture,(gl_in[0].gl_Position/4+vec4(1.0f/4, 0.0f, 0.0f, 0.0f)).stp).r != 0);
	v[3] = int(texture(my_data_texture,(gl_in[0].gl_Position/4+vec4(0.0f, 1.0f/4, 0.0f, 0.0f)).stp).r != 0);
	v[2] = int(texture(my_data_texture,(gl_in[0].gl_Position/4+vec4(1.0f/4, 1.0f/4, 0.0f, 0.0f)).stp).r != 0);

	v[4] = int(texture(my_data_texture,(gl_in[0].gl_Position/4+vec4(0.0f, 0.0f, 1.0f/4, 0.0f)).stp).r != 0);
	v[5] = int(texture(my_data_texture,(gl_in[0].gl_Position/4+vec4(1.0f/4, 0.0f, 0.0f, 0.0f)).stp).r != 0);
	v[7] = int(texture(my_data_texture,(gl_in[0].gl_Position/4+vec4(0.0f, 1.0f/4 ,0.0f, 0.0f)).stp).r != 0);
	v[6] = int(texture(my_data_texture,(gl_in[0].gl_Position/4+vec4(1.0f/4, 1.0f/4, 1.0f/4, 0.0f)).stp).r != 0);

	cubeindex = (v[7]<<7) | (v[6]<<6) | (v[5]<<5) | (v[4]<<4) | (v[3]<<3) | (v[2]<<2) | (v[1]<<1) | (v[0]);
	*/
	
	if(texelFetch(my_data_texture,ivec3(gl_in[0].gl_Position + vec4(0.0f, 0.0f, 0.0f, 0.0f)).rgb,0).r != 0) cubeindex = cubeindex  + 1;
	if(texelFetch(my_data_texture,ivec3(gl_in[0].gl_Position + vec4(1.0f, 0.0f, 0.0f, 0.0f)).rgb,0).r != 0) cubeindex = cubeindex  + 2;
	if(texelFetch(my_data_texture,ivec3(gl_in[0].gl_Position + vec4(1.0f, 1.0f, 0.0f, 0.0f)).rgb,0).r != 0) cubeindex = cubeindex  + 4;
	if(texelFetch(my_data_texture,ivec3(gl_in[0].gl_Position + vec4(0.0f, 1.0f, 0.0f, 0.0f)).rgb,0).r != 0) cubeindex = cubeindex  + 8;

	if(texelFetch(my_data_texture,ivec3(gl_in[0].gl_Position + vec4(0.0f, 0.0f, 1.0f, 0.0f)).rgb,0).r != 0) cubeindex = cubeindex  + 16;
	if(texelFetch(my_data_texture,ivec3(gl_in[0].gl_Position + vec4(1.0f, 0.0f, 0.0f, 0.0f)).rgb,0).r != 0) cubeindex = cubeindex  + 32;
	if(texelFetch(my_data_texture,ivec3(gl_in[0].gl_Position + vec4(1.0f, 1.0f, 1.0f, 0.0f)).rgb,0).r != 0) cubeindex = cubeindex  + 64;
	if(texelFetch(my_data_texture,ivec3(gl_in[0].gl_Position + vec4(0.0f, 1.0f ,0.0f, 0.0f)).rgb,0).r != 0) cubeindex = cubeindex  + 128;
	int a = 1;
	lookupVertex(253,256);
	
	/*
	if(cubeindex > 255)
	{
		gl_Position = Transform*(gl_in[0].gl_Position+lookupVertex(cubeindex,0));
		EmitVertex();
		gl_Position = Transform*(gl_in[0].gl_Position);
		EmitVertex();
		gl_Position = Transform*(gl_in[0].gl_Position);
		EmitVertex();
		EndPrimitive();
	}
	*/
	
	/*
	if(texelFetch(lookupTableTexture,ivec2(cubeindex,0),0).r != -1)
	{
		gl_Position = Transform*(gl_in[0].gl_Position+lookupVertex(cubeindex,0));
		EmitVertex();
		gl_Position = Transform*(gl_in[0].gl_Position+lookupVertex(cubeindex,1));
		EmitVertex();
		gl_Position = Transform*(gl_in[0].gl_Position+lookupVertex(cubeindex,2));
		EmitVertex();
		EndPrimitive();
	}/*
	if(texelFetch(lookupTableTexture,ivec2(cubeindex,3),0).r != -1)
	{
		gl_Position = Transform*(gl_in[0].gl_Position+lookupVertex(cubeindex,3));
		EmitVertex();
		gl_Position = Transform*(gl_in[0].gl_Position+lookupVertex(cubeindex,4));
		EmitVertex();
		gl_Position = Transform*(gl_in[0].gl_Position+lookupVertex(cubeindex,5));
		EmitVertex();
		EndPrimitive();
	}
	if(texelFetch(lookupTableTexture,ivec2(cubeindex,6),0).r != -1)
	{
		gl_Position = Transform*(gl_in[0].gl_Position+lookupVertex(cubeindex,6));
		EmitVertex();
		gl_Position = Transform*(gl_in[0].gl_Position+lookupVertex(cubeindex,7));
		EmitVertex();
		gl_Position = Transform*(gl_in[0].gl_Position+lookupVertex(cubeindex,8));
		EmitVertex();
		EndPrimitive();
	}
	if(texelFetch(lookupTableTexture,ivec2(cubeindex,9),0).r != -1)
	{
		gl_Position = Transform*(gl_in[0].gl_Position+lookupVertex(cubeindex,9));
		EmitVertex();
		gl_Position = Transform*(gl_in[0].gl_Position+lookupVertex(cubeindex,10));
		EmitVertex();
		gl_Position = Transform*(gl_in[0].gl_Position+lookupVertex(cubeindex,11));
		EmitVertex();
		EndPrimitive();
	}
	if(texelFetch(lookupTableTexture,ivec2(cubeindex,12),0).r != -1)
	{
		gl_Position = Transform*(gl_in[0].gl_Position+lookupVertex(cubeindex,12));
		EmitVertex();
		gl_Position = Transform*(gl_in[0].gl_Position+lookupVertex(cubeindex,13));
		EmitVertex();
		gl_Position = Transform*(gl_in[0].gl_Position+lookupVertex(cubeindex,14));
		EmitVertex();
		EndPrimitive();
	}
	*/

}
/*
void main()
{
	gl_Position = Transform*gl_in[0].gl_Position + vec4(-0.1f, 0.0, 0.0, 0.0);
	EmitVertex();
	
	gl_Position = Transform*gl_in[0].gl_Position + vec4(0.1f, 0.0, 0.0, 0.0);
	EmitVertex();

	gl_Position = Transform*gl_in[0].gl_Position + vec4(0.0f, 0.1f, 0.0, 0.0);
	EmitVertex();


}*/