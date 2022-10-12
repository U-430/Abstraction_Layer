struct VSInput
{
	float4 Position : POSITION0;	// 位置座標
	float4 Color	: COLOR0;		// 頂点カラー
	float2 TexCoord : TEXCOORD0;		// UV
};

struct VSOutput
{
	float4 Position : SV_POSITION;	// 位置座標
	float4 Color	: COLOR0;		// 頂点カラー
	float2 TexCoord : TEXCOORD0;		// UV
};

cbuffer constantBuffer
{
	float4x4 World;	// ワールド行列
	float4x4 View;	// ビュー行列
	float4x4 Proj;	// 射影行列
}

Texture2D Tex : register(t0);			// テクスチャ
SamplerState Sampler : register(s0);	// サンプラー

// メインエントリーポイント
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

// ピクセルシェーダーのメインエントリーポイント
float4 ps_main(VSOutput input) : SV_Target
{
	//PSOutput output = (PSOutput)0;

	float4 texcol = Tex.Sample(Sampler, input.TexCoord);
	//float4 texcol = float4(1, 1, 1, 1);

	return input.Color * texcol;
}