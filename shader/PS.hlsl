struct VSOutput
{
	float4 Position : SV_POSITION;	// �ʒu���W
	float4 Color	: COLOR;		// ���_�J���[
};

struct PSOutput
{
	float4 Color	: SV_TARGET0;	// �s�N�Z���J���[
};

// �s�N�Z���V�F�[�_�[�̃��C���G���g���[�|�C���g
PSOutput main( VSOutput Input )
{
	PSOutput output = (PSOutput)0;

	output.Color = Input.Color;

	return output;
}