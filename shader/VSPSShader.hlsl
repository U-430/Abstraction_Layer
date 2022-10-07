struct VSInput
{
	float4 Position : POSITION0;	// �ʒu���W
	float4 Color	: COLOR0;		// ���_�J���[
	float2 TexCoord : TEXCOORD0;	// UV
};

struct VSOutput
{
	float4 Position : SV_POSITION;	// �ʒu���W
	float4 Color	: COLOR0;		// ���_�J���[
	float2 TexCoord : TEXCOORD0;		// UV
};

cbuffer constantBuffer : register(b0)
{
	float4x4 World	: packoffset(c0);	// ���[���h�s��
	float4x4 View	: packoffset(c4);	// �r���[�s��
	float4x4 Proj	: packoffset(c8);	// �ˉe�s��
}

Texture2D Tex : register(t0);			// �e�N�X�`��
SamplerState Sampler : register(s0);	// �T���v���[

// ���C���G���g���[�|�C���g
VSOutput vs_main(VSInput input)
{
	VSOutput output = (VSOutput)0;

	//float4 localPos = input.Position;
	//float4 worldPos = mul( World, localPos );
	//float4 viewPos	= mul( View, worldPos );
	//float4 projPos	= mul( Proj, viewPos );

	//output.Position = projPos;
	output.Position = input.Position;
	output.Color	= input.Color;
	output.TexCoord = input.TexCoord;

	//output.Position = input;

	return output;
}

// �s�N�Z���V�F�[�_�[�̃��C���G���g���[�|�C���g
float4 ps_main(VSOutput input) : SV_Target
{
	//PSOutput output = (PSOutput)0;

	//output.Color = input.Color;

	//float4 texcol = Tex.Sample(Sampler, input.TexCoord);
	float4 texcol = float4(0, 1, 1, 1);

	return input.Color * texcol;
}