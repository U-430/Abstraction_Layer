struct VSInput
{
	float3 Position : POSITION;	// 位置座標
	float4 Color	: COLOR0;	// 頂点カラー
};

struct VSOutput
{
	float4 Position : SV_POSITION;	// 位置座標
	float4 Color	: COLOR0;		// 頂点カラー
};

cbuffer constantBuffer : register(b0)
{
	float4x4 World	: packoffset(c0);	// ワールド行列
	float4x4 View	: packoffset(c4);	// ビュー行列
	float4x4 Proj	: packoffset(c8);	// 射影行列
}

// メインエントリーポイント
VSOutput vs_main(float4 input : POSITION)
{
	VSOutput output = (VSOutput)0;

	//float4 localPos = float4( Input.Position, 1.0f );
	//float4 worldPos = mul( World, localPos );
	//float4 viewPos	= mul( View, worldPos );
	//float4 projPos	= mul( Proj, viewPos );

	//output.Position = projPos;
	//output.Position = input.Position;
	//output.Color	= input.Color;

	output.Position = input;

	return output;
}

// ピクセルシェーダーのメインエントリーポイント
float4 ps_main(VSOutput input) : SV_TARGET
{
	//PSOutput output = (PSOutput)0;

	//output.Color = input.Color;

	return float4(1,1,1,1);
}