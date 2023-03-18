#version 460 core

layout(local_size_x = 1, local_size_y = 704, local_size_z = 1) in;
layout(std430, binding = 0) buffer Input
{
    vec3 input_array[16]; 
};

uniform uint PixelsX;
uniform uint Log2Levels;
uniform uint InputArraySize;
uniform uint OutputArraySize;

const double PI = 3.14159265358979323846;
const double M_2PI = 2 * PI;

// right = a + bi, left = c + di
// right + left = (a + bi) + (c + di) = 
// = (a + c) + i(b + d)
vec2 ComplexSum(vec2 right, vec2 left)
{
	vec2 result;

	result.x = right.x + left.x;
	result.y = right.y + left.y;

	return result;
}

// right = a + bi, left = c + di
// right - left = (a + bi) - (c + di) = 
// = (a - c) + i(b - d) 
vec2 ComplexDiff(vec2 right, vec2 left)
{
    vec2 result;

    result.x = right.x - left.x;
    result.y = right.y - left.y;

    return result;
}

// right = a + bi, left = c + di
// right * left = (a + bi) * (c + di) = 
// = (a * c) + i(a * d) + i(b * c) - (b * d) = 
// = (ac - bd) + i(ad + bc) 
vec2 ComplexMul(vec2 right, vec2 left)
{
	vec2 result;

	result.x = right.x * left.x - right.y * left.y;
	result.y = right.x * left.y + right.y * left.x;

	return result;
}

uint BitReverse(uint index, uint logm)
{
	uint result = index;

	result = (result & 0x00005555) << 1 | (result & 0x0000AAAA) >> 1;
	result = (result & 0x00003333) << 2 | (result & 0x0000CCCC) >> 2;
	result = (result & 0x00000F0F) << 4 | (result & 0x0000F0F0) >> 4;
	result = (result & 0x000000FF) << 8 | (result & 0x0000FF00) >> 8;

	return result >> (16 - logm);
}

void main()
{
    uint nBlocks = InputArraySize / 2;
    uint nButterflyOperations = 1;
    uint offset = 2;
    uint idParElem = 1;

    vec2 output_array[16];

    for(uint i = 0; i < InputArraySize; i++)
    {
        uint reverse_i = BitReverse(i, Log2Levels);
        output_array[i] = input_array[reverse_i];
    }

    for(uint i = 0; i < InputArraySize; i++)
    {
        input_array[i] = output_array;
    }

    /*for(uint logLevel = 0, _2_k = 2; logLevel < Log2Levels; logLevel++, _2_k *= 2)
    {
        for(uint idBlock = 0, idFirstElemInBlock = 0; idBlock < nBlocks; idBlock++, idFirstElemInBlock += offset)
        {
            for(uint oper = 0; oper < nButterflyOperations; oper++)
            {
                double y = ((double)oper) / ((double)_2_k);
                double phi = M_2PI * y;

                vec2 W;
                W.x = cos(phi);
                W.y = sin(phi);

                uint rightId = idFirstElemInBlock + oper;
                uint leftId = rightId + idParElem;

                vec2 right = output_array[rightId];
                vec2 left = output_array[leftId];

                left = ComplexMul(left, W);

                output_array = ComplexSum(right, left);
                output_array = ComplexDiff(right, left);
            }
        }

        nBlocks /= 2;
        nButterflyOperations *= 2;

        offset *= 2;
        idFirstElemInBlock *= 2;
    }*/
}