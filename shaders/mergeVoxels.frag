#version 440
uniform sampler3D pingVoxel;
uniform sampler2D depthMap;
uniform int voxelDepth;
uniform float mu;

uniform vec3 t_gk;
uniform mat3 inv_R_gk;

uniform mat3 K_camera;
uniform mat3 InverseK;

out vec4 out_Color;
void main() {		
	float scaling = 1/voxelDepth;
	vec3 viewTranslation = vec3(0,0,0);

	//I think this is true not sure though!!!
	vec3 globalCoord = (gl_FragCoord.xyz*scaling) - viewTranslation;	//Always in metres
	vec3 translated = gl_FragCoord.xyz - t_gk;
	vec3 localCoord = inv_R_gk*translated;
	vec3 temp2 = K_camera*localCoord;
	ivec2 pix = ivec2(temp2/temp2.z);
	float Lambda = length(InverseK*vec3(pix,1.0f));

	ivec2 maxSize = textureSize(depthMap,0);
	if(pix.x < 0 || pix.y < 0 || pix.x > maxSize.x || pix.y > maxSize.y){
		//out_Color = texelFetch(pingVoxel,ivec3(gl_FragCoord),0);
		out_Color = vec4(0,0,0,111);
		return;
	}
	float readDistance = texelFetch(depthMap,pix,0).r;
	if(readDistance == 0){
		//out_Color = texelFetch(pingVoxel,ivec3(gl_FragCoord),0);
		out_Color = vec4(0,0,0,11);
		return;
	}
	float sdf  = length(translated)/Lambda - readDistance;
	float tsdf = clamp(sdf,-mu,mu);
	out_Color = texelFetch(pingVoxel,ivec3(gl_FragCoord),0)+vec4(tsdf,0,0,0);		
}
