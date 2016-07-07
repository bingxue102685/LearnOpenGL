#version 330 core
//光照贴图
struct Material
{
	sampler2D diffuse;  //漫反射的颜色为纹理的颜色
	sampler2D specular; //
	//sampler2D emission; //自发光
	float shininess;
};

//光照
struct Light
{
	//此处需要留意，在旧版本的固定管线中，传入的是vec4类型，要根据w值判断是向量还是点
	//w为1，传入的是一个点，即定点光
	//w为0，传入的是一个向量，即定向光
	//此处不加以处理，若要处理if w==0 elseif w== 1即可
	vec3 position;
	//vec3 direction;  
	vec3 ambient;
	vec3 specular;
	vec3 diffuse;
	/*衰减 
	Fa = I / (Kc + Kl * d + Kq * d^2)

	I:当前片段的光的亮度
	d:代表片段到光源的距离
	Kc:常数项
	Kl:一次项
	Kq:二次项
	*/ 
	float constant;  //常量（通常为1.0f）
	float linear;    //一次项
	float quadratic; //二次项
};

uniform Material material;
uniform Light light;
uniform vec3 lightcolor;
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
	float distance = length(light.position - fragPos);
	//衰减因子
	float attenuation = 1.0f / (light.constant + light.linear * distance + light.quadratic * distance * distance);

	//环境光
	vec3 ambient = lightcolor * fragdiffuse * light.ambient * attenuation;

	//散射光
	vec3 normal = normalize(Normal);
	vec3 lightDir = normalize(light.position - fragPos);
	//vec3 lightDir = normalize(-light.direction);
	float diff = max(dot(normal, lightDir), 0.0f);
	vec3 diffuse = diff * lightcolor * fragdiffuse * attenuation;

	//镜面光
	//material.shininess高光的发光值(Shininess)。一个物体的发光值越高，反射光的能力越强，散射得越少，高光点越小
	vec3 viewDir = normalize(viewPos - fragPos);
	vec3 reflecDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(viewDir, reflecDir),0.0f), material.shininess);
	vec3 specular = spec * lightcolor * fragspecular * attenuation;
	//自发光
	//vec3 emission = vec3(texture(material.emission, TexCoords));


	//输出颜色
    vec3 result = ambient + diffuse + specular;
	
    color = vec4(result, 1.0f);
}
