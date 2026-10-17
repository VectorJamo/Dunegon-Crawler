uniform sampler2D texture;

uniform ivec2 playerPosition;

uniform ivec2 explosionPositions[10];
uniform float numExplosions;

float CalculateLightIntensity(vec2 lightPosition, int multiplier)
{
    int windowHeight = 32*20;

    vec2 fragmentPosition = vec2(gl_FragCoord.x, float(windowHeight) - gl_FragCoord.y);

    float dist = distance(lightPosition, fragmentPosition);

    float intensity = clamp((1.0/dist)*float(multiplier), 0.0, 1.0);

    return intensity;
}

void main()
{
    vec4 pixel = texture2D(texture, gl_TexCoord[0].xy);

    float finalIntensity = 0.0;
    finalIntensity = CalculateLightIntensity(vec2(playerPosition), 60); // From the player
    
    for(int i = 0; i < int(numExplosions); i++)
    {
        finalIntensity += CalculateLightIntensity(vec2(explosionPositions[i]), 10); // From the explosions
    }

    gl_FragColor = finalIntensity * pixel;
}