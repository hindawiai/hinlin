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

#अगर_अघोषित __DC_HUBBUB_DCN20_H__
#घोषणा __DC_HUBBUB_DCN20_H__

#समावेश "dcn10/dcn10_hubbub.h"
#समावेश "dcn20_vmid.h"

#घोषणा HUBBUB_REG_LIST_DCN20_COMMON()\
	HUBBUB_REG_LIST_DCN_COMMON(), \
	SR(DCHUBBUB_CRC_CTRL), \
	SR(DCN_VM_FB_LOCATION_BASE),\
	SR(DCN_VM_FB_LOCATION_TOP),\
	SR(DCN_VM_FB_OFFSET),\
	SR(DCN_VM_AGP_BOT),\
	SR(DCN_VM_AGP_TOP),\
	SR(DCN_VM_AGP_BASE)

#घोषणा TO_DCN20_HUBBUB(hubbub)\
	container_of(hubbub, काष्ठा dcn20_hubbub, base)

#घोषणा HUBBUB_REG_LIST_DCN20_COMMON()\
	HUBBUB_REG_LIST_DCN_COMMON(), \
	SR(DCHUBBUB_CRC_CTRL), \
	SR(DCN_VM_FB_LOCATION_BASE),\
	SR(DCN_VM_FB_LOCATION_TOP),\
	SR(DCN_VM_FB_OFFSET),\
	SR(DCN_VM_AGP_BOT),\
	SR(DCN_VM_AGP_TOP),\
	SR(DCN_VM_AGP_BASE)

#घोषणा HUBBUB_REG_LIST_DCN20(id)\
	HUBBUB_REG_LIST_DCN20_COMMON(), \
	HUBBUB_SR_WATERMARK_REG_LIST(), \
	HUBBUB_VM_REG_LIST(),\
	SR(DCN_VM_PROTECTION_FAULT_DEFAULT_ADDR_MSB),\
	SR(DCN_VM_PROTECTION_FAULT_DEFAULT_ADDR_LSB)


#घोषणा HUBBUB_MASK_SH_LIST_DCN20(mask_sh)\
	HUBBUB_MASK_SH_LIST_DCN_COMMON(mask_sh), \
	HUBBUB_MASK_SH_LIST_STUTTER(mask_sh), \
	HUBBUB_SF(DCHUBBUB_GLOBAL_TIMER_CNTL, DCHUBBUB_GLOBAL_TIMER_REFDIV, mask_sh), \
	HUBBUB_SF(DCN_VM_FB_LOCATION_BASE, FB_BASE, mask_sh), \
	HUBBUB_SF(DCN_VM_FB_LOCATION_TOP, FB_TOP, mask_sh), \
	HUBBUB_SF(DCN_VM_FB_OFFSET, FB_OFFSET, mask_sh), \
	HUBBUB_SF(DCN_VM_AGP_BOT, AGP_BOT, mask_sh), \
	HUBBUB_SF(DCN_VM_AGP_TOP, AGP_TOP, mask_sh), \
	HUBBUB_SF(DCN_VM_AGP_BASE, AGP_BASE, mask_sh), \
	HUBBUB_SF(DCN_VM_PROTECTION_FAULT_DEFAULT_ADDR_MSB, DCN_VM_PROTECTION_FAULT_DEFAULT_ADDR_MSB, mask_sh), \
	HUBBUB_SF(DCN_VM_PROTECTION_FAULT_DEFAULT_ADDR_LSB, DCN_VM_PROTECTION_FAULT_DEFAULT_ADDR_LSB, mask_sh)

काष्ठा dcn20_hubbub अणु
	काष्ठा hubbub base;
	स्थिर काष्ठा dcn_hubbub_रेजिस्टरs *regs;
	स्थिर काष्ठा dcn_hubbub_shअगरt *shअगरts;
	स्थिर काष्ठा dcn_hubbub_mask *masks;
	अचिन्हित पूर्णांक debug_test_index_pstate;
	काष्ठा dcn_watermark_set watermarks;
	पूर्णांक num_vmid;
	काष्ठा dcn20_vmid vmid[16];
	अचिन्हित पूर्णांक detile_buf_size;
पूर्ण;

व्योम hubbub2_स्थिरruct(काष्ठा dcn20_hubbub *hubbub,
	काष्ठा dc_context *ctx,
	स्थिर काष्ठा dcn_hubbub_रेजिस्टरs *hubbub_regs,
	स्थिर काष्ठा dcn_hubbub_shअगरt *hubbub_shअगरt,
	स्थिर काष्ठा dcn_hubbub_mask *hubbub_mask);

bool hubbub2_dcc_support_swizzle(
		क्रमागत swizzle_mode_values swizzle,
		अचिन्हित पूर्णांक bytes_per_element,
		क्रमागत segment_order *segment_order_horz,
		क्रमागत segment_order *segment_order_vert);

bool hubbub2_dcc_support_pixel_क्रमmat(
		क्रमागत surface_pixel_क्रमmat क्रमmat,
		अचिन्हित पूर्णांक *bytes_per_element);

bool hubbub2_get_dcc_compression_cap(काष्ठा hubbub *hubbub,
		स्थिर काष्ठा dc_dcc_surface_param *input,
		काष्ठा dc_surface_dcc_cap *output);

bool hubbub2_initialize_vmids(काष्ठा hubbub *hubbub,
		स्थिर काष्ठा dc_dcc_surface_param *input,
		काष्ठा dc_surface_dcc_cap *output);

पूर्णांक hubbub2_init_dchub_sys_ctx(काष्ठा hubbub *hubbub,
		काष्ठा dcn_hubbub_phys_addr_config *pa_config);
व्योम hubbub2_init_vm_ctx(काष्ठा hubbub *hubbub,
		काष्ठा dcn_hubbub_virt_addr_config *va_config,
		पूर्णांक vmid);
व्योम hubbub2_update_dchub(काष्ठा hubbub *hubbub,
		काष्ठा dchub_init_data *dh_data);

व्योम hubbub2_get_dchub_ref_freq(काष्ठा hubbub *hubbub,
		अचिन्हित पूर्णांक dccg_ref_freq_inKhz,
		अचिन्हित पूर्णांक *dchub_ref_freq_inKhz);

व्योम hubbub2_wm_पढ़ो_state(काष्ठा hubbub *hubbub,
		काष्ठा dcn_hubbub_wm *wm);

#पूर्ण_अगर
