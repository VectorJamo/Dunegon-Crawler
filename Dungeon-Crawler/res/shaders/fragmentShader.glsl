#version 120

#define MAX_TORCHES 100

// All the lighting calculations are done in screen-space (for now)
uniform sampler2D texture;

uniform vec2 playerCenterScreenPos;
uniform float screenHeight;
uniform bool playerHasTorch;

uniform vec2 torchScreenPositions[MAX_TORCHES];
uniform int numTorches;

void main()
{
	vec4 pixel = texture2D(texture, gl_TexCoord[0].xy);
	vec2 fragPos = vec2(gl_FragCoord.x, screenHeight - gl_FragCoord.y);

	// Ambient Light
	vec4 lightColor = vec4(1.0, 1.0, 1.0, 1.0);
	float ambientIntensity = 0.4;
	vec4 ambientLight = ambientIntensity * lightColor;

	vec4 ambientColor = ambientLight * pixel;

	// Player's Light
	float dist, multiplier, intensity = 0.0;
	vec4 torchLightColorValue = vec4(1.0, 0.6, 0.6, 1.0);
	
	if(playerHasTorch)
	{
		dist = distance(fragPos, playerCenterScreenPos);
	
		multiplier = 6000.0;
		intensity = clamp((1.0/(dist*dist)) * multiplier, 0.0, 1.0);
	}
	vec4 pointLight = torchLightColorValue * intensity;

	vec4 pointLightColor = pointLight * pixel;

	// Torch's light
	multiplier = 1000.0;

	float totalIntensity = 0.0f;
	for(int i = 0; i < numTorches; i++) 
	{
		dist = distance(fragPos, torchScreenPositions[i]);
		intensity = clamp((1.0/(dist*dist)) * multiplier, 0.0, 1.0);
		totalIntensity += intensity;
	}

	vec4 torchLight = torchLightColorValue * totalIntensity;

	vec4 torchLightColor = torchLight * pixel;

	gl_FragColor = (ambientColor + pointLightColor + torchLightColor);
}