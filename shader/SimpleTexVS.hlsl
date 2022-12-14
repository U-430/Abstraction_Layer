struct VSInput
{
	float3 Position : POSITION;	// 位置座標
	float4 Color	: COLOR;	// 頂点カラー
	float2 TexCoord	: TEXCOORD;	// テクスチャ座標
};

struct VSOutput
{
	float4 Position : SV_POSITION;	// 位置座標
	float4 Color	: COLOR0;		// 頂点カラー
	float2 TexCoord	: TEXCOORD0;	// テクスチャ座標
};

cbuffer Transform : register(b0)
{
	float4x4 World	: packoffset(c0);	// ワールド行列
	float4x4 View	: packoffset(c4);	// ビュー行列
	float4x4 Proj	: packoffset(c8);	// 射影行列
}

// メインエントリーポイント
VSOutput main(VSInput Input)
{
	VSOutput output = (VSOutput)0;

	float4 localPos = float4(Input.Position, 1.0f);
	float4 worldPos = mul(World, localPos);
	float4 viewPos  = mul(View, worldPos);
	float4 projPos  = mul(Proj, viewPos);

	output.Position = projPos;
	output.Color	= Input.Color;
	output.TexCoord = Input.TexCoord;

	return output;
}