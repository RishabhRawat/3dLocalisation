#version 440
layout(points) in;
layout(TRIANGLE_STRIP, max_vertices = 15) out;

out vec4 fragColor;
out vec3 surfaceNormal;
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
	vec4 vertices[3];
	vec3 v1,v2,v3;
	int cubeindex = 0;
	if(retrieveData(vec4(0.0f, 0.0f, 0.0f, 0.0f)) != 0) cubeindex = cubeindex  + 1;
	if(retrieveData(vec4(1.0f, 0.0f, 0.0f, 0.0f)) != 0) cubeindex = cubeindex  + 2;
	if(retrieveData(vec4(1.0f, 1.0f, 0.0f, 0.0f)) != 0) cubeindex = cubeindex  + 4;
	if(retrieveData(vec4(0.0f, 1.0f, 0.0f, 0.0f)) != 0) cubeindex = cubeindex  + 8;

	if(retrieveData(vec4(0.0f, 0.0f, 1.0f, 0.0f)) != 0) cubeindex = cubeindex  + 16;
	if(retrieveData(vec4(1.0f, 0.0f, 1.0f, 0.0f)) != 0) cubeindex = cubeindex  + 32;
	if(retrieveData(vec4(1.0f, 1.0f, 1.0f, 0.0f)) != 0) cubeindex = cubeindex  + 64;
	if(retrieveData(vec4(0.0f, 1.0f ,1.0f, 0.0f)) != 0) cubeindex = cubeindex  + 128;
	
	int i = 0;
	while(i < 13)
	{
		if(lookupVertexTable(cubeindex,i) != -1)
		{
			vertices[0] = Transform*(gl_in[0].gl_Position+lookupVertex(cubeindex,i));
			i++;
			vertices[1] = Transform*(gl_in[0].gl_Position+lookupVertex(cubeindex,i));
			i++;
			vertices[2] = Transform*(gl_in[0].gl_Position+lookupVertex(cubeindex,i));
			i++;
			v1 = (vertices[2] - vertices[0]).rgb;
			v2 = (vertices[2] - vertices[1]).rgb;
			v3 = cross(v1,v2);

			gl_Position = vertices[0];
			fragColor = vec4(0.2f,0.0f,0.8f,1.0f);
			surfaceNormal = v3;
			EmitVertex();
			gl_Position = vertices[1];
			fragColor = vec4(0.2f,0.0f,0.8f,1.0f);
			surfaceNormal = v3;
			EmitVertex();
			gl_Position = vertices[2];
			fragColor = vec4(0.2f,0.0f,0.8f,1.0f);
			surfaceNormal = v3;
			EmitVertex();
			EndPrimitive();
		}
		else
		{
			break;
		}
	}
}
