#version 330 core
out vec4 FragColor;

in vec3 FragPos;
in vec2 TexCoord;
in vec3 Normal;


// texture samplers
uniform sampler2D texture1;

uniform vec3 lightColor;
uniform vec3 lightPos;
uniform vec3 viewPos;
uniform bool blinn;

void main()
{
	
  //Ambient
  float ambientStrength = 0.1;
 vec3 ambient = ambientStrength * lightColor;

  //Diffuse
  vec3 norm = normalize(Normal);
  vec3 lightDir = normalize(lightPos - FragPos);
  float diff = max(dot(norm, lightDir),0.0);
  vec3 diffuse = diff * lightColor;

  //Specular
  vec3 viewDir = normalize(viewPos - FragPos);
  vec3 reflectDir = reflect(-lightDir, norm);
  float spec = 0.0;
  if(blinn)
  {
	  vec3 halfwayDir = normalize(lightDir + viewDir);
	  spec = pow(max(dot(norm,halfwayDir),0.0),32.0);
  }
  else
  {
	  vec3 reflectDir = reflect(-lightDir, norm);
      spec = pow(max(dot(viewDir, reflectDir), 0.0), 8.0);
  }
  vec3 specular = vec3(0.3) * spec;

  vec4 result = (vec4(ambient,1.0) + vec4(diffuse, 1.0) + vec4(specular,1.0)) * texture(texture1,TexCoord);
  // linearly interpolate between both textures
  FragColor = result;
}