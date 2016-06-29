#version 330 core
//光照贴图
struct Material
{
	sampler2D diffuse;  //漫反射的颜色为纹理的颜色
	sampler2D specular; //
	sampler2D emission; //自发光
	float shininess;
};

uniform Material material;
uniform vec3 lightcolor;
uniform vec3 lightPos;
uniform vec3 viewPos;

in vec3 Normal;  //法线向量
in vec3 fragPos; //片段的位置
in vec2 TexCoords; //纹理坐标
out vec4 color;

void main()
{
	//解释一下：输出的颜色由 环境光 + 散射光 + 镜面光 （个人理解）
	//散射光和镜面光由影响因子、 光照的颜色、材质的颜色决定
	//影响因子： 1.环境光，无需解释，就是影响物体整体颜色的光
	//          2.散射光，由光照在材质上，经过漫反射后的光，跟观察的角度无关，影响因子由入射光线和入射点处的法线的夹角决定（点乘（cos（a）））
	//			 角度越大因子越小，反射光越小
	//          3.镜面光，影响因子由反射光和视线（即摄像机到入射点的向量）的角度决定（点乘（cos（a））），角度越小，镜面光越大，
	vec3 fragdiffuse = vec3(texture(material.diffuse, TexCoords));
	vec3 fragspecular = vec3(texture(material.specular, TexCoords));


	//环境光(由于环境光太强，变小点)
	vec3 ambient = lightcolor * fragdiffuse * vec3(0.5f, 0.5f, 0.5f);

	//散射光
	vec3 normal = normalize(Normal);
	vec3 lightDir = normalize(lightPos - fragPos);
	float diff = max(dot(normal, lightDir), 0.0f);
	vec3 diffuse = diff * lightcolor * fragdiffuse;

	//镜面光
	//material.shininess高光的发光值(Shininess)。一个物体的发光值越高，反射光的能力越强，散射得越少，高光点越小
	vec3 viewDir = normalize(viewPos - fragPos);
	vec3 reflecDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(viewDir, reflecDir),0.0f), material.shininess);
	vec3 specular = spec * lightcolor * fragspecular;
	//自发光
	vec3 emission = vec3(texture(material.emission, TexCoords));


	//输出颜色
    vec3 result = ambient + diffuse + specular + emission;
	
    color = vec4(result, 1.0f);
}
