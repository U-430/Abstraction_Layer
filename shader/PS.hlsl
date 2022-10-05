struct VSOutput
{
	float4 Position : SV_POSITION;	// 位置座標
	float4 Color	: COLOR;		// 頂点カラー
};

struct PSOutput
{
	float4 Color	: SV_TARGET0;	// ピクセルカラー
};

// ピクセルシェーダーのメインエントリーポイント
PSOutput main( VSOutput Input )
{
	PSOutput output = (PSOutput)0;

	output.Color = Input.Color;

	return output;
}