struct PS_INPUT
{
	float4 outPosition : SV_POSITION;
	float3 outColour : COLOUR;
};

float4 main(PS_INPUT input) : SV_Target
{
	return float4(input.outColour, 1.0f);
}