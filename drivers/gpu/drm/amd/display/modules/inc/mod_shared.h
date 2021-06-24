<शैली गुरु>
/*
 * Copyright 2016 Advanced Micro Devices, Inc.
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE COPYRIGHT HOLDER(S) OR AUTHOR(S) BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * Authors: AMD
 *
 */

#अगर_अघोषित MOD_SHARED_H_
#घोषणा MOD_SHARED_H_

क्रमागत color_transfer_func अणु
	TRANSFER_FUNC_UNKNOWN,
	TRANSFER_FUNC_SRGB,
	TRANSFER_FUNC_BT709,
	TRANSFER_FUNC_PQ2084,
	TRANSFER_FUNC_PQ2084_INTERIM,
	TRANSFER_FUNC_LINEAR_0_1,
	TRANSFER_FUNC_LINEAR_0_125,
	TRANSFER_FUNC_GAMMA_22,
	TRANSFER_FUNC_GAMMA_26
पूर्ण;

क्रमागत vrr_packet_type अणु
	PACKET_TYPE_VRR,
	PACKET_TYPE_FS_V1,
	PACKET_TYPE_FS_V2,
	PACKET_TYPE_FS_V3,
	PACKET_TYPE_VTEM
पूर्ण;

जोड़ lut3d_control_flags अणु
	अचिन्हित पूर्णांक raw;
	काष्ठा अणु
		अचिन्हित पूर्णांक करो_chroma_scale				:1;
		अचिन्हित पूर्णांक spec_version				:3;
		अचिन्हित पूर्णांक use_zero_display_black			:1;
		अचिन्हित पूर्णांक use_zero_source_black			:1;
		अचिन्हित पूर्णांक क्रमce_display_black			:6;
		अचिन्हित पूर्णांक apply_display_gamma			:1;
		अचिन्हित पूर्णांक exp_shaper_max				:6;
		अचिन्हित पूर्णांक unity_3dlut				:1;
		अचिन्हित पूर्णांक bypass_3dlut				:1;
		अचिन्हित पूर्णांक use_3dlut					:1;
		अचिन्हित पूर्णांक less_than_dcip3				:1;
		अचिन्हित पूर्णांक override_lum				:1;
		अचिन्हित पूर्णांक use_gamut_map_lib					:1;
		अचिन्हित पूर्णांक chromatic_adaptation_src				:1;
		अचिन्हित पूर्णांक chromatic_adaptation_dst				:1;
		अचिन्हित पूर्णांक करो_blender_lut_degamma		:1;
		अचिन्हित पूर्णांक reseved					:4;
	पूर्ण bits;
पूर्ण;

क्रमागत पंचांग_show_option_पूर्णांकernal अणु
	पंचांग_show_option_पूर्णांकernal_single_file		= 0,/*flags2 not in use*/
	पंचांग_show_option_पूर्णांकernal_duplicate_file,		/*use flags2*/
	पंचांग_show_option_पूर्णांकernal_duplicate_sidebyside/*use flags2*/
पूर्ण;

क्रमागत lut3d_control_gamut_map अणु
	lut3d_control_gamut_map_none = 0,
	lut3d_control_gamut_map_tonemap,
	lut3d_control_gamut_map_chto,
	lut3d_control_gamut_map_chso,
	lut3d_control_gamut_map_chci
पूर्ण;

क्रमागत lut3d_control_rotation_mode अणु
	lut3d_control_rotation_mode_none = 0,
	lut3d_control_rotation_mode_hue,
	lut3d_control_rotation_mode_cc,
	lut3d_control_rotation_mode_hue_cc
पूर्ण;

काष्ठा lut3d_settings अणु
	अचिन्हित अक्षर version;
	जोड़ lut3d_control_flags flags;
	जोड़ lut3d_control_flags flags2;
	क्रमागत पंचांग_show_option_पूर्णांकernal option;
	अचिन्हित पूर्णांक min_lum;/*multiplied by 100*/
	अचिन्हित पूर्णांक max_lum;
	अचिन्हित पूर्णांक min_lum2;
	अचिन्हित पूर्णांक max_lum2;
	क्रमागत lut3d_control_gamut_map map;
	क्रमागत lut3d_control_rotation_mode rotation;
	क्रमागत lut3d_control_gamut_map map2;
	क्रमागत lut3d_control_rotation_mode rotation2;
पूर्ण;

#पूर्ण_अगर /* MOD_SHARED_H_ */
