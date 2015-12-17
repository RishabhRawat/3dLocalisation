#version 440
uniform sampler3D pingVoxel;
uniform sampler2D depthMap;
uniform int voxelDepth;
out vec4 out_Color;

void main() {			
	//if(texture(depthMap,gl_FragCoord.xy);)
	out_Color = texture(depthMap,gl_FragCoord.xy/voxelDepth);
	/*
	if(gl_FragCoord.x/voxelDepth > 0.5f)
		out_Color = vec4(1.0f,0.0f,0.0f,1.0f);
	else
		out_Color = vec4(1.0f,1.0f,1.0f,1.0f);
		*/

}
