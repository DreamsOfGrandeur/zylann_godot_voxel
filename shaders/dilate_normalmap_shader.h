// Generated file

// clang-format off
const char *g_dilate_normalmap_shader = 
"#version 450\n"
"\n"
"// Dilates a normalmap by filling \"empty\" pixels with the average of surrounding pixels.\n"
"// Assumes the input image is tiled: dilation will not interact across tiles.\n"
"// One run of this shader will dilate by 1 pixel.\n"
"\n"
"layout (local_size_x = 8, local_size_y = 8, local_size_z = 1) in;\n"
"\n"
"layout (set = 0, binding = 0, rgba8ui) restrict readonly uniform uimage2D u_src_image;\n"
"layout (set = 0, binding = 1, rgba8ui) restrict writeonly uniform uimage2D u_dst_image;\n"
"layout (set = 0, binding = 2) uniform Params {\n"
"	int u_tile_size;\n"
"};\n"
"\n"
"void main() {\n"
"	// This color corresponds to a null normal.\n"
"	const ivec4 nocol = ivec4(127, 127, 127, 255);\n"
"	const ivec2 pixel_pos = ivec2(gl_GlobalInvocationID.xy);\n"
"\n"
"	const ivec4 col11 = ivec4(imageLoad(u_src_image, pixel_pos));\n"
"	if (col11 != nocol) {\n"
"		imageStore(u_dst_image, pixel_pos, col11);\n"
"		return;\n"
"	}\n"
"\n"
"	//const ivec2 im_size = imageSize(u_src_image).xy;\n"
"\n"
"	const ivec2 p01 = pixel_pos + ivec2(-1, 0);\n"
"	const ivec2 p21 = pixel_pos + ivec2(1, 0);\n"
"	const ivec2 p10 = pixel_pos + ivec2(0, -1);\n"
"	const ivec2 p12 = pixel_pos + ivec2(0, 1);\n"
"\n"
"	ivec4 col_sum = ivec4(0,0,0,0);\n"
"	int count = 0;\n"
"\n"
"	const ivec4 col01 = ivec4(imageLoad(u_src_image, p01));\n"
"	// Don't sample pixels of different tiles than the current one.\n"
"	// This also takes care of image borders, but we must do it more explicitely for negative borders\n"
"	// because of how division works\n"
"	if (col01 != nocol && pixel_pos.x != 0 && (pixel_pos.x - 1) / u_tile_size == pixel_pos.x / u_tile_size) {\n"
"		col_sum += col01;\n"
"		++count;\n"
"	}\n"
"\n"
"	const ivec4 col21 = ivec4(imageLoad(u_src_image, p21));\n"
"	if (col21 != nocol && (pixel_pos.x + 1) / u_tile_size == pixel_pos.x / u_tile_size) {\n"
"		col_sum += col21;\n"
"		++count;\n"
"	}\n"
"\n"
"	const ivec4 col10 = ivec4(imageLoad(u_src_image, p10));\n"
"	if (col10 != nocol && pixel_pos.y != 0 && (pixel_pos.y - 1) / u_tile_size == pixel_pos.y / u_tile_size) {\n"
"		col_sum += col10;\n"
"		++count;\n"
"	}\n"
"\n"
"	const ivec4 col12 = ivec4(imageLoad(u_src_image, p12));\n"
"	if (col12 != nocol && (pixel_pos.y + 1) / u_tile_size == pixel_pos.y / u_tile_size) {\n"
"		col_sum += col12;\n"
"		++count;\n"
"	}\n"
"\n"
"	ivec4 col_avg = count == 0 ? col11 : col_sum / count;\n"
"\n"
"	imageStore(u_dst_image, pixel_pos, col_avg);\n"
"}\n"
"\n";
// clang-format on
