<शैली गुरु>
/*
 * Copyright 2017 Advanced Micro Devices, Inc.
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

#अगर_अघोषित _DCN10_IPP_H_
#घोषणा _DCN10_IPP_H_

#समावेश "ipp.h"

#घोषणा TO_DCN10_IPP(ipp)\
	container_of(ipp, काष्ठा dcn10_ipp, base)

#घोषणा IPP_REG_LIST_DCN(id) \
	SRI(FORMAT_CONTROL, CNVC_CFG, id), \
	SRI(CNVC_SURFACE_PIXEL_FORMAT, CNVC_CFG, id), \
	SRI(CURSOR0_CONTROL, CNVC_CUR, id), \
	SRI(CURSOR0_COLOR0, CNVC_CUR, id), \
	SRI(CURSOR0_COLOR1, CNVC_CUR, id)

#घोषणा IPP_REG_LIST_DCN10(id) \
	IPP_REG_LIST_DCN(id), \
	SRI(CURSOR_SETTINS, HUBPREQ, id), \
	SRI(CURSOR_SURFACE_ADDRESS_HIGH, CURSOR, id), \
	SRI(CURSOR_SURFACE_ADDRESS, CURSOR, id), \
	SRI(CURSOR_SIZE, CURSOR, id), \
	SRI(CURSOR_CONTROL, CURSOR, id), \
	SRI(CURSOR_POSITION, CURSOR, id), \
	SRI(CURSOR_HOT_SPOT, CURSOR, id), \
	SRI(CURSOR_DST_OFFSET, CURSOR, id)

#घोषणा IPP_REG_LIST_DCN20(id) \
	IPP_REG_LIST_DCN(id), \
	SRI(CURSOR_SETTINGS, HUBPREQ, id), \
	SRI(CURSOR_SURFACE_ADDRESS_HIGH, CURSOR0_, id), \
	SRI(CURSOR_SURFACE_ADDRESS, CURSOR0_, id), \
	SRI(CURSOR_SIZE, CURSOR0_, id), \
	SRI(CURSOR_CONTROL, CURSOR0_, id), \
	SRI(CURSOR_POSITION, CURSOR0_, id), \
	SRI(CURSOR_HOT_SPOT, CURSOR0_, id), \
	SRI(CURSOR_DST_OFFSET, CURSOR0_, id)

#घोषणा CURSOR0_CURSOR_CONTROL__CURSOR_2X_MAGNIFY__SHIFT	0x4
#घोषणा CURSOR0_CURSOR_CONTROL__CURSOR_2X_MAGNIFY_MASK		0x00000010L
#घोषणा CURSOR1_CURSOR_CONTROL__CURSOR_2X_MAGNIFY__SHIFT	0x4
#घोषणा CURSOR1_CURSOR_CONTROL__CURSOR_2X_MAGNIFY_MASK		0x00000010L
#घोषणा CURSOR2_CURSOR_CONTROL__CURSOR_2X_MAGNIFY__SHIFT	0x4
#घोषणा CURSOR2_CURSOR_CONTROL__CURSOR_2X_MAGNIFY_MASK		0x00000010L
#घोषणा CURSOR3_CURSOR_CONTROL__CURSOR_2X_MAGNIFY__SHIFT	0x4
#घोषणा CURSOR3_CURSOR_CONTROL__CURSOR_2X_MAGNIFY_MASK		0x00000010L

#घोषणा IPP_SF(reg_name, field_name, post_fix)\
	.field_name = reg_name ## __ ## field_name ## post_fix

#घोषणा IPP_MASK_SH_LIST_DCN(mask_sh) \
	IPP_SF(CNVC_CFG0_CNVC_SURFACE_PIXEL_FORMAT, CNVC_SURFACE_PIXEL_FORMAT, mask_sh), \
	IPP_SF(CNVC_CFG0_FORMAT_CONTROL, CNVC_BYPASS, mask_sh), \
	IPP_SF(CNVC_CFG0_FORMAT_CONTROL, ALPHA_EN, mask_sh), \
	IPP_SF(CNVC_CFG0_FORMAT_CONTROL, FORMAT_EXPANSION_MODE, mask_sh), \
	IPP_SF(CNVC_CUR0_CURSOR0_CONTROL, CUR0_MODE, mask_sh), \
	IPP_SF(CNVC_CUR0_CURSOR0_COLOR0, CUR0_COLOR0, mask_sh), \
	IPP_SF(CNVC_CUR0_CURSOR0_COLOR1, CUR0_COLOR1, mask_sh), \
	IPP_SF(CNVC_CUR0_CURSOR0_CONTROL, CUR0_EXPANSION_MODE, mask_sh), \
	IPP_SF(CNVC_CUR0_CURSOR0_CONTROL, CUR0_ENABLE, mask_sh)

#घोषणा IPP_MASK_SH_LIST_DCN10(mask_sh) \
	IPP_MASK_SH_LIST_DCN(mask_sh),\
	IPP_SF(HUBPREQ0_CURSOR_SETTINS, CURSOR0_DST_Y_OFFSET, mask_sh), \
	IPP_SF(HUBPREQ0_CURSOR_SETTINS, CURSOR0_CHUNK_HDL_ADJUST, mask_sh), \
	IPP_SF(CURSOR0_CURSOR_SURFACE_ADDRESS_HIGH, CURSOR_SURFACE_ADDRESS_HIGH, mask_sh), \
	IPP_SF(CURSOR0_CURSOR_SURFACE_ADDRESS, CURSOR_SURFACE_ADDRESS, mask_sh), \
	IPP_SF(CURSOR0_CURSOR_SIZE, CURSOR_WIDTH, mask_sh), \
	IPP_SF(CURSOR0_CURSOR_SIZE, CURSOR_HEIGHT, mask_sh), \
	IPP_SF(CURSOR0_CURSOR_CONTROL, CURSOR_MODE, mask_sh), \
	IPP_SF(CURSOR0_CURSOR_CONTROL, CURSOR_2X_MAGNIFY, mask_sh), \
	IPP_SF(CURSOR0_CURSOR_CONTROL, CURSOR_PITCH, mask_sh), \
	IPP_SF(CURSOR0_CURSOR_CONTROL, CURSOR_LINES_PER_CHUNK, mask_sh), \
	IPP_SF(CURSOR0_CURSOR_CONTROL, CURSOR_ENABLE, mask_sh), \
	IPP_SF(CURSOR0_CURSOR_POSITION, CURSOR_X_POSITION, mask_sh), \
	IPP_SF(CURSOR0_CURSOR_POSITION, CURSOR_Y_POSITION, mask_sh), \
	IPP_SF(CURSOR0_CURSOR_HOT_SPOT, CURSOR_HOT_SPOT_X, mask_sh), \
	IPP_SF(CURSOR0_CURSOR_HOT_SPOT, CURSOR_HOT_SPOT_Y, mask_sh), \
	IPP_SF(CURSOR0_CURSOR_DST_OFFSET, CURSOR_DST_X_OFFSET, mask_sh), \
	IPP_SF(CNVC_CFG0_FORMAT_CONTROL, OUTPUT_FP, mask_sh)

#घोषणा IPP_MASK_SH_LIST_DCN20(mask_sh) \
	IPP_MASK_SH_LIST_DCN(mask_sh), \
	IPP_SF(HUBPREQ0_CURSOR_SETTINGS, CURSOR0_DST_Y_OFFSET, mask_sh), \
	IPP_SF(HUBPREQ0_CURSOR_SETTINGS, CURSOR0_CHUNK_HDL_ADJUST, mask_sh), \
	IPP_SF(CURSOR0_0_CURSOR_SURFACE_ADDRESS_HIGH, CURSOR_SURFACE_ADDRESS_HIGH, mask_sh), \
	IPP_SF(CURSOR0_0_CURSOR_SURFACE_ADDRESS, CURSOR_SURFACE_ADDRESS, mask_sh), \
	IPP_SF(CURSOR0_0_CURSOR_SIZE, CURSOR_WIDTH, mask_sh), \
	IPP_SF(CURSOR0_0_CURSOR_SIZE, CURSOR_HEIGHT, mask_sh), \
	IPP_SF(CURSOR0_0_CURSOR_CONTROL, CURSOR_MODE, mask_sh), \
	IPP_SF(CURSOR0_0_CURSOR_CONTROL, CURSOR_2X_MAGNIFY, mask_sh), \
	IPP_SF(CURSOR0_0_CURSOR_CONTROL, CURSOR_PITCH, mask_sh), \
	IPP_SF(CURSOR0_0_CURSOR_CONTROL, CURSOR_LINES_PER_CHUNK, mask_sh), \
	IPP_SF(CURSOR0_0_CURSOR_CONTROL, CURSOR_ENABLE, mask_sh), \
	IPP_SF(CURSOR0_0_CURSOR_POSITION, CURSOR_X_POSITION, mask_sh), \
	IPP_SF(CURSOR0_0_CURSOR_POSITION, CURSOR_Y_POSITION, mask_sh), \
	IPP_SF(CURSOR0_0_CURSOR_HOT_SPOT, CURSOR_HOT_SPOT_X, mask_sh), \
	IPP_SF(CURSOR0_0_CURSOR_HOT_SPOT, CURSOR_HOT_SPOT_Y, mask_sh), \
	IPP_SF(CURSOR0_0_CURSOR_DST_OFFSET, CURSOR_DST_X_OFFSET, mask_sh)

#घोषणा IPP_DCN10_REG_FIELD_LIST(type) \
	type CNVC_SURFACE_PIXEL_FORMAT; \
	type CNVC_BYPASS; \
	type ALPHA_EN; \
	type FORMAT_EXPANSION_MODE; \
	type CURSOR0_DST_Y_OFFSET; \
	type CURSOR0_CHUNK_HDL_ADJUST; \
	type CUR0_MODE; \
	type CUR0_COLOR0; \
	type CUR0_COLOR1; \
	type CUR0_EXPANSION_MODE; \
	type CURSOR_SURFACE_ADDRESS_HIGH; \
	type CURSOR_SURFACE_ADDRESS; \
	type CURSOR_WIDTH; \
	type CURSOR_HEIGHT; \
	type CURSOR_MODE; \
	type CURSOR_2X_MAGNIFY; \
	type CURSOR_PITCH; \
	type CURSOR_LINES_PER_CHUNK; \
	type CURSOR_ENABLE; \
	type CUR0_ENABLE; \
	type CURSOR_X_POSITION; \
	type CURSOR_Y_POSITION; \
	type CURSOR_HOT_SPOT_X; \
	type CURSOR_HOT_SPOT_Y; \
	type CURSOR_DST_X_OFFSET; \
	type OUTPUT_FP

काष्ठा dcn10_ipp_shअगरt अणु
	IPP_DCN10_REG_FIELD_LIST(uपूर्णांक8_t);
पूर्ण;

काष्ठा dcn10_ipp_mask अणु
	IPP_DCN10_REG_FIELD_LIST(uपूर्णांक32_t);
पूर्ण;

काष्ठा dcn10_ipp_रेजिस्टरs अणु
	uपूर्णांक32_t CURSOR_SETTINS;
	uपूर्णांक32_t CURSOR_SETTINGS;
	uपूर्णांक32_t CNVC_SURFACE_PIXEL_FORMAT;
	uपूर्णांक32_t CURSOR0_CONTROL;
	uपूर्णांक32_t CURSOR0_COLOR0;
	uपूर्णांक32_t CURSOR0_COLOR1;
	uपूर्णांक32_t FORMAT_CONTROL;
	uपूर्णांक32_t CURSOR_SURFACE_ADDRESS_HIGH;
	uपूर्णांक32_t CURSOR_SURFACE_ADDRESS;
	uपूर्णांक32_t CURSOR_SIZE;
	uपूर्णांक32_t CURSOR_CONTROL;
	uपूर्णांक32_t CURSOR_POSITION;
	uपूर्णांक32_t CURSOR_HOT_SPOT;
	uपूर्णांक32_t CURSOR_DST_OFFSET;
पूर्ण;

काष्ठा dcn10_ipp अणु
	काष्ठा input_pixel_processor base;

	स्थिर काष्ठा dcn10_ipp_रेजिस्टरs *regs;
	स्थिर काष्ठा dcn10_ipp_shअगरt *ipp_shअगरt;
	स्थिर काष्ठा dcn10_ipp_mask *ipp_mask;

	काष्ठा dc_cursor_attributes curs_attr;
पूर्ण;

व्योम dcn10_ipp_स्थिरruct(काष्ठा dcn10_ipp *ippn10,
	काष्ठा dc_context *ctx,
	पूर्णांक inst,
	स्थिर काष्ठा dcn10_ipp_रेजिस्टरs *regs,
	स्थिर काष्ठा dcn10_ipp_shअगरt *ipp_shअगरt,
	स्थिर काष्ठा dcn10_ipp_mask *ipp_mask);

व्योम dcn20_ipp_स्थिरruct(काष्ठा dcn10_ipp *ippn10,
	काष्ठा dc_context *ctx,
	पूर्णांक inst,
	स्थिर काष्ठा dcn10_ipp_रेजिस्टरs *regs,
	स्थिर काष्ठा dcn10_ipp_shअगरt *ipp_shअगरt,
	स्थिर काष्ठा dcn10_ipp_mask *ipp_mask);

#पूर्ण_अगर /* _DCN10_IPP_H_ */
