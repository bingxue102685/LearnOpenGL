#version 330 core
//材质的各种类型颜色属性
struct Material
{
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float shininess;
};
uniform Material material;

//限制光强
struct Light
{
	vec3 position;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};
uniform Light light;


uniform vec3 lightcolor;
uniform vec3 lightPos;
uniform vec3 viewPos;
in vec3 Normal;
in vec3 fragPos;
out vec4 color;

void main()
{
	//解释一下：输出的颜色由 环境光 + 散射光 + 镜面光 （个人理解）
	//散射光和镜面光由影响因子、 光照的颜色、材质的颜色决定
	//影响因子： 1.环境光，无需解释，就是影响物体整体颜色的光
	//          2.散射光，由光照在材质上，经过漫反射后的光，跟观察的角度无关，影响因子由入射光线和入射点处的法线的夹角决定（点乘（cos（a）））
	//			 角度越大因子越小，反射光越小
	//          3.镜面光，影响因子由反射光和视线（即摄像机到入射点的向量）的角度决定（点乘（cos（a））），角度越小，镜面光越大，


	//环境光
	vec3 ambient = lightcolor * material.ambient * light.ambient;

	//散射光
	vec3 normal = normalize(Normal);
	vec3 lightDir = normalize(lightPos - fragPos);
	float diff = max(dot(normal, lightDir), 0.0f);
	vec3 diffuse = diff * lightcolor * material.diffuse * light.diffuse;

	//镜面光
	//material.shininess高光的发光值(Shininess)。一个物体的发光值越高，反射光的能力越强，散射得越少，高光点越小
	vec3 viewDir = normalize(viewPos - fragPos);
	vec3 reflecDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(viewDir, reflecDir),0.0f), material.shininess);
	vec3 specular = spec * lightcolor * material.specular * light.specular;
	//输出颜色

    vec3 result = ambient + diffuse + specular;
    color = vec4(result, 1.0f);
}
