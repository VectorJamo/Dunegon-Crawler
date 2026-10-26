#version 120

// All the lighting calculations are done in screen-space (for now)
uniform sampler2D texture;

uniform vec2 playerCenterScreenPos;
uniform float screenHeight;

void main()
{
	vec4 pixel = texture2D(texture, gl_TexCoord[0].xy);
	vec2 fragPos = vec2(gl_FragCoord.x, screenHeight - gl_FragCoord.y);

	// Ambient Light
	vec4 lightColor = vec4(1.0, 1.0, 1.0, 1.0);
	float ambientIntensity = 0.1;
	vec4 ambientLight = ambientIntensity * lightColor;

	vec4 ambientColor = ambientLight * pixel;

	// Point Light
	float dist = distance(fragPos, playerCenterScreenPos);
	
	float multiplier = 60.0;
	float intensity = clamp((1.0/dist) * multiplier, 0.0, 1.0);
	vec4 pointLight = lightColor * intensity;

	vec4 pointLightColor = pointLight * pixel;

	gl_FragColor = (ambientColor + pointLightColor);
}