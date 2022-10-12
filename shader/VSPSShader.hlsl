struct VSInput
{
	float4 Position : POSITION0;	// �ʒu���W
	float4 Color	: COLOR0;		// ���_�J���[
	float2 TexCoord : TEXCOORD0;		// UV
};

struct VSOutput
{
	float4 Position : SV_POSITION;	// �ʒu���W
	float4 Color	: COLOR0;		// ���_�J���[
	float2 TexCoord : TEXCOORD0;		// UV
};

cbuffer constantBuffer
{
	float4x4 World;	// ���[���h�s��
	float4x4 View;	// �r���[�s��
	float4x4 Proj;	// �ˉe�s��
}

Texture2D Tex : register(t0);			// �e�N�X�`��
SamplerState Sampler : register(s0);	// �T���v���[

// ���C���G���g���[�|�C���g
VSOutput vs_main(VSInput input)
{
	VSOutput output = (VSOutput)0;

	float4 localPos = input.Position;
	float4 worldPos = mul( localPos, World );
	float4 viewPos	= mul( worldPos, View );
	float4 projPos	= mul( viewPos, Proj );

	output.Position = projPos;
	//output.Position = input.Position;
	output.Color	= input.Color;
	output.TexCoord = input.TexCoord;

	return output;
}

// �s�N�Z���V�F�[�_�[�̃��C���G���g���[�|�C���g
float4 ps_main(VSOutput input) : SV_Target
{
	//PSOutput output = (PSOutput)0;

	float4 texcol = Tex.Sample(Sampler, input.TexCoord);
	//float4 texcol = float4(1, 1, 1, 1);

	return input.Color * texcol;
}