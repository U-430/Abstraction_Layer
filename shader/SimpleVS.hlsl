struct VSInput
{
	float3 Position : POSITION;	// �ʒu���W
	float4 Color	: COLOR;	// ���_�J���[
};

struct VSOutput
{
	float4 Position : SV_POSITION;	// �ʒu���W
	float4 Color	: COLOR;		// ���_�J���[
};

cbuffer Transform : register(b0)
{
	float4x4 World	: packoffset(c0);	// ���[���h�s��
	float4x4 View	: packoffset(c4);	// �r���[�s��
	float4x4 Proj	: packoffset(c8);	// �ˉe�s��
}

// ���C���G���g���[�|�C���g
VSOutput main(VSInput Input)
{
	VSOutput output = (VSOutput)0;

	float4 localPos = float4( Input.Position, 1.0f );
	float4 worldPos = mul( World, localPos );
	float4 viewPos	= mul( View, worldPos );
	float4 projPos	= mul( Proj, viewPos );

	output.Position = projPos;
	output.Color	= Input.Color;

	return output;
}