<शैली गुरु>
/*
 * Copyright(c) 2011-2016 Intel Corporation. All rights reserved.
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the next
 * paragraph) shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#अगर_अघोषित _I915_PVINFO_H_
#घोषणा _I915_PVINFO_H_

#समावेश <linux/types.h>

/* The MMIO offset of the shared info between guest and host emulator */
#घोषणा VGT_PVINFO_PAGE	0x78000
#घोषणा VGT_PVINFO_SIZE	0x1000

/*
 * The following काष्ठाure pages are defined in GEN MMIO space
 * क्रम भवization. (One page क्रम now)
 */
#घोषणा VGT_MAGIC         0x4776544776544776ULL	/* 'vGTvGTvG' */
#घोषणा VGT_VERSION_MAJOR 1
#घोषणा VGT_VERSION_MINOR 0

/*
 * notअगरications from guest to vgpu device model
 */
क्रमागत vgt_g2v_type अणु
	VGT_G2V_PPGTT_L3_PAGE_TABLE_CREATE = 2,
	VGT_G2V_PPGTT_L3_PAGE_TABLE_DESTROY,
	VGT_G2V_PPGTT_L4_PAGE_TABLE_CREATE,
	VGT_G2V_PPGTT_L4_PAGE_TABLE_DESTROY,
	VGT_G2V_EXECLIST_CONTEXT_CREATE,
	VGT_G2V_EXECLIST_CONTEXT_DESTROY,
	VGT_G2V_MAX,
पूर्ण;

/*
 * VGT capabilities type
 */
#घोषणा VGT_CAPS_FULL_PPGTT		BIT(2)
#घोषणा VGT_CAPS_HWSP_EMULATION		BIT(3)
#घोषणा VGT_CAPS_HUGE_GTT		BIT(4)

काष्ठा vgt_अगर अणु
	u64 magic;		/* VGT_MAGIC */
	u16 version_major;
	u16 version_minor;
	u32 vgt_id;		/* ID of vGT instance */
	u32 vgt_caps;		/* VGT capabilities */
	u32 rsv1[11];		/* pad to offset 0x40 */
	/*
	 *  Data काष्ठाure to describe the balooning info of resources.
	 *  Each VM can only have one portion of continuous area क्रम now.
	 *  (May support scattered resource in future)
	 *  (starting from offset 0x40)
	 */
	काष्ठा अणु
		/* Aperture रेजिस्टर balooning */
		काष्ठा अणु
			u32 base;
			u32 size;
		पूर्ण mappable_gmadr;	/* aperture */
		/* GMADR रेजिस्टर balooning */
		काष्ठा अणु
			u32 base;
			u32 size;
		पूर्ण nonmappable_gmadr;	/* non aperture */
		/* allowed fence रेजिस्टरs */
		u32 fence_num;
		u32 rsv2[3];
	पूर्ण avail_rs;		/* available/asचिन्हित resource */
	u32 rsv3[0x200 - 24];	/* pad to half page */
	/*
	 * The bottom half page is क्रम response from Gfx driver to hypervisor.
	 */
	u32 rsv4;
	u32 display_पढ़ोy;	/* पढ़ोy क्रम display owner चयन */

	u32 rsv5[4];

	u32 g2v_notअगरy;
	u32 rsv6[5];

	u32 cursor_x_hot;
	u32 cursor_y_hot;

	काष्ठा अणु
		u32 lo;
		u32 hi;
	पूर्ण pdp[4];

	u32 execlist_context_descriptor_lo;
	u32 execlist_context_descriptor_hi;

	u32  rsv7[0x200 - 24];    /* pad to one page */
पूर्ण __packed;

#घोषणा vgtअगर_offset(x) (दुरत्व(काष्ठा vgt_अगर, x))

#घोषणा vgtअगर_reg(x) _MMIO(VGT_PVINFO_PAGE + vgtअगर_offset(x))

/* vGPU display status to be used by the host side */
#घोषणा VGT_DRV_DISPLAY_NOT_READY 0
#घोषणा VGT_DRV_DISPLAY_READY     1  /* पढ़ोy क्रम display चयन */

#पूर्ण_अगर /* _I915_PVINFO_H_ */
