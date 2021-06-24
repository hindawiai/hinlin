<शैली गुरु>
/*
 * Copyright 2008 Advanced Micro Devices, Inc.
 * Copyright 2008 Red Hat Inc.
 * Copyright 2009 Jerome Glisse.
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
 * Authors: Dave Airlie
 *          Alex Deucher
 *          Jerome Glisse
 */

#समावेश <linux/firmware.h>
#समावेश <linux/pci.h>
#समावेश <linux/slab.h>

#समावेश <drm/drm_device.h>
#समावेश <drm/radeon_drm.h>

#समावेश "atom.h"
#समावेश "avivod.h"
#समावेश "radeon.h"
#समावेश "radeon_asic.h"
#समावेश "radeon_audio.h"
#समावेश "rv770d.h"
#समावेश "rv770.h"

#घोषणा R700_PFP_UCODE_SIZE 848
#घोषणा R700_PM4_UCODE_SIZE 1360

अटल व्योम rv770_gpu_init(काष्ठा radeon_device *rdev);
व्योम rv770_fini(काष्ठा radeon_device *rdev);
अटल व्योम rv770_pcie_gen2_enable(काष्ठा radeon_device *rdev);
पूर्णांक evergreen_set_uvd_घड़ीs(काष्ठा radeon_device *rdev, u32 vclk, u32 dclk);

पूर्णांक rv770_set_uvd_घड़ीs(काष्ठा radeon_device *rdev, u32 vclk, u32 dclk)
अणु
	अचिन्हित fb_भाग = 0, vclk_भाग = 0, dclk_भाग = 0;
	पूर्णांक r;

	/* RV740 uses evergreen uvd clk programming */
	अगर (rdev->family == CHIP_RV740)
		वापस evergreen_set_uvd_घड़ीs(rdev, vclk, dclk);

	/* bypass vclk and dclk with bclk */
	WREG32_P(CG_UPLL_FUNC_CNTL_2,
		 VCLK_SRC_SEL(1) | DCLK_SRC_SEL(1),
		 ~(VCLK_SRC_SEL_MASK | DCLK_SRC_SEL_MASK));

	अगर (!vclk || !dclk) अणु
		/* keep the Bypass mode, put PLL to sleep */
		WREG32_P(CG_UPLL_FUNC_CNTL, UPLL_SLEEP_MASK, ~UPLL_SLEEP_MASK);
		वापस 0;
	पूर्ण

	r = radeon_uvd_calc_upll_भागiders(rdev, vclk, dclk, 50000, 160000,
					  43663, 0x03FFFFFE, 1, 30, ~0,
					  &fb_भाग, &vclk_भाग, &dclk_भाग);
	अगर (r)
		वापस r;

	fb_भाग |= 1;
	vclk_भाग -= 1;
	dclk_भाग -= 1;

	/* set UPLL_FB_DIV to 0x50000 */
	WREG32_P(CG_UPLL_FUNC_CNTL_3, UPLL_FB_DIV(0x50000), ~UPLL_FB_DIV_MASK);

	/* deनिश्चित UPLL_RESET and UPLL_SLEEP */
	WREG32_P(CG_UPLL_FUNC_CNTL, 0, ~(UPLL_RESET_MASK | UPLL_SLEEP_MASK));

	/* निश्चित BYPASS EN and FB_DIV[0] <- ??? why? */
	WREG32_P(CG_UPLL_FUNC_CNTL, UPLL_BYPASS_EN_MASK, ~UPLL_BYPASS_EN_MASK);
	WREG32_P(CG_UPLL_FUNC_CNTL_3, UPLL_FB_DIV(1), ~UPLL_FB_DIV(1));

	r = radeon_uvd_send_upll_ctlreq(rdev, CG_UPLL_FUNC_CNTL);
	अगर (r)
		वापस r;

	/* निश्चित PLL_RESET */
	WREG32_P(CG_UPLL_FUNC_CNTL, UPLL_RESET_MASK, ~UPLL_RESET_MASK);

	/* set the required FB_DIV, REF_DIV, Post भागder values */
	WREG32_P(CG_UPLL_FUNC_CNTL, UPLL_REF_DIV(1), ~UPLL_REF_DIV_MASK);
	WREG32_P(CG_UPLL_FUNC_CNTL_2,
		 UPLL_SW_HILEN(vclk_भाग >> 1) |
		 UPLL_SW_LOLEN((vclk_भाग >> 1) + (vclk_भाग & 1)) |
		 UPLL_SW_HILEN2(dclk_भाग >> 1) |
		 UPLL_SW_LOLEN2((dclk_भाग >> 1) + (dclk_भाग & 1)),
		 ~UPLL_SW_MASK);

	WREG32_P(CG_UPLL_FUNC_CNTL_3, UPLL_FB_DIV(fb_भाग),
		 ~UPLL_FB_DIV_MASK);

	/* give the PLL some समय to settle */
	mdelay(15);

	/* deनिश्चित PLL_RESET */
	WREG32_P(CG_UPLL_FUNC_CNTL, 0, ~UPLL_RESET_MASK);

	mdelay(15);

	/* deनिश्चित BYPASS EN and FB_DIV[0] <- ??? why? */
	WREG32_P(CG_UPLL_FUNC_CNTL, 0, ~UPLL_BYPASS_EN_MASK);
	WREG32_P(CG_UPLL_FUNC_CNTL_3, 0, ~UPLL_FB_DIV(1));

	r = radeon_uvd_send_upll_ctlreq(rdev, CG_UPLL_FUNC_CNTL);
	अगर (r)
		वापस r;

	/* चयन VCLK and DCLK selection */
	WREG32_P(CG_UPLL_FUNC_CNTL_2,
		 VCLK_SRC_SEL(2) | DCLK_SRC_SEL(2),
		 ~(VCLK_SRC_SEL_MASK | DCLK_SRC_SEL_MASK));

	mdelay(100);

	वापस 0;
पूर्ण

अटल स्थिर u32 r7xx_golden_रेजिस्टरs[] =
अणु
	0x8d00, 0xffffffff, 0x0e0e0074,
	0x8d04, 0xffffffff, 0x013a2b34,
	0x9508, 0xffffffff, 0x00000002,
	0x8b20, 0xffffffff, 0,
	0x88c4, 0xffffffff, 0x000000c2,
	0x28350, 0xffffffff, 0,
	0x9058, 0xffffffff, 0x0fffc40f,
	0x240c, 0xffffffff, 0x00000380,
	0x733c, 0xffffffff, 0x00000002,
	0x2650, 0x00040000, 0,
	0x20bc, 0x00040000, 0,
	0x7300, 0xffffffff, 0x001000f0
पूर्ण;

अटल स्थिर u32 r7xx_golden_dyn_gpr_रेजिस्टरs[] =
अणु
	0x8db0, 0xffffffff, 0x98989898,
	0x8db4, 0xffffffff, 0x98989898,
	0x8db8, 0xffffffff, 0x98989898,
	0x8dbc, 0xffffffff, 0x98989898,
	0x8dc0, 0xffffffff, 0x98989898,
	0x8dc4, 0xffffffff, 0x98989898,
	0x8dc8, 0xffffffff, 0x98989898,
	0x8dcc, 0xffffffff, 0x98989898,
	0x88c4, 0xffffffff, 0x00000082
पूर्ण;

अटल स्थिर u32 rv770_golden_रेजिस्टरs[] =
अणु
	0x562c, 0xffffffff, 0,
	0x3f90, 0xffffffff, 0,
	0x9148, 0xffffffff, 0,
	0x3f94, 0xffffffff, 0,
	0x914c, 0xffffffff, 0,
	0x9698, 0x18000000, 0x18000000
पूर्ण;

अटल स्थिर u32 rv770ce_golden_रेजिस्टरs[] =
अणु
	0x562c, 0xffffffff, 0,
	0x3f90, 0xffffffff, 0x00cc0000,
	0x9148, 0xffffffff, 0x00cc0000,
	0x3f94, 0xffffffff, 0x00cc0000,
	0x914c, 0xffffffff, 0x00cc0000,
	0x9b7c, 0xffffffff, 0x00fa0000,
	0x3f8c, 0xffffffff, 0x00fa0000,
	0x9698, 0x18000000, 0x18000000
पूर्ण;

अटल स्थिर u32 rv770_mgcg_init[] =
अणु
	0x8bcc, 0xffffffff, 0x130300f9,
	0x5448, 0xffffffff, 0x100,
	0x55e4, 0xffffffff, 0x100,
	0x160c, 0xffffffff, 0x100,
	0x5644, 0xffffffff, 0x100,
	0xc164, 0xffffffff, 0x100,
	0x8a18, 0xffffffff, 0x100,
	0x897c, 0xffffffff, 0x8000100,
	0x8b28, 0xffffffff, 0x3c000100,
	0x9144, 0xffffffff, 0x100,
	0x9a1c, 0xffffffff, 0x10000,
	0x9a50, 0xffffffff, 0x100,
	0x9a1c, 0xffffffff, 0x10001,
	0x9a50, 0xffffffff, 0x100,
	0x9a1c, 0xffffffff, 0x10002,
	0x9a50, 0xffffffff, 0x100,
	0x9a1c, 0xffffffff, 0x10003,
	0x9a50, 0xffffffff, 0x100,
	0x9a1c, 0xffffffff, 0x0,
	0x9870, 0xffffffff, 0x100,
	0x8d58, 0xffffffff, 0x100,
	0x9500, 0xffffffff, 0x0,
	0x9510, 0xffffffff, 0x100,
	0x9500, 0xffffffff, 0x1,
	0x9510, 0xffffffff, 0x100,
	0x9500, 0xffffffff, 0x2,
	0x9510, 0xffffffff, 0x100,
	0x9500, 0xffffffff, 0x3,
	0x9510, 0xffffffff, 0x100,
	0x9500, 0xffffffff, 0x4,
	0x9510, 0xffffffff, 0x100,
	0x9500, 0xffffffff, 0x5,
	0x9510, 0xffffffff, 0x100,
	0x9500, 0xffffffff, 0x6,
	0x9510, 0xffffffff, 0x100,
	0x9500, 0xffffffff, 0x7,
	0x9510, 0xffffffff, 0x100,
	0x9500, 0xffffffff, 0x8,
	0x9510, 0xffffffff, 0x100,
	0x9500, 0xffffffff, 0x9,
	0x9510, 0xffffffff, 0x100,
	0x9500, 0xffffffff, 0x8000,
	0x9490, 0xffffffff, 0x0,
	0x949c, 0xffffffff, 0x100,
	0x9490, 0xffffffff, 0x1,
	0x949c, 0xffffffff, 0x100,
	0x9490, 0xffffffff, 0x2,
	0x949c, 0xffffffff, 0x100,
	0x9490, 0xffffffff, 0x3,
	0x949c, 0xffffffff, 0x100,
	0x9490, 0xffffffff, 0x4,
	0x949c, 0xffffffff, 0x100,
	0x9490, 0xffffffff, 0x5,
	0x949c, 0xffffffff, 0x100,
	0x9490, 0xffffffff, 0x6,
	0x949c, 0xffffffff, 0x100,
	0x9490, 0xffffffff, 0x7,
	0x949c, 0xffffffff, 0x100,
	0x9490, 0xffffffff, 0x8,
	0x949c, 0xffffffff, 0x100,
	0x9490, 0xffffffff, 0x9,
	0x949c, 0xffffffff, 0x100,
	0x9490, 0xffffffff, 0x8000,
	0x9604, 0xffffffff, 0x0,
	0x9654, 0xffffffff, 0x100,
	0x9604, 0xffffffff, 0x1,
	0x9654, 0xffffffff, 0x100,
	0x9604, 0xffffffff, 0x2,
	0x9654, 0xffffffff, 0x100,
	0x9604, 0xffffffff, 0x3,
	0x9654, 0xffffffff, 0x100,
	0x9604, 0xffffffff, 0x4,
	0x9654, 0xffffffff, 0x100,
	0x9604, 0xffffffff, 0x5,
	0x9654, 0xffffffff, 0x100,
	0x9604, 0xffffffff, 0x6,
	0x9654, 0xffffffff, 0x100,
	0x9604, 0xffffffff, 0x7,
	0x9654, 0xffffffff, 0x100,
	0x9604, 0xffffffff, 0x8,
	0x9654, 0xffffffff, 0x100,
	0x9604, 0xffffffff, 0x9,
	0x9654, 0xffffffff, 0x100,
	0x9604, 0xffffffff, 0x80000000,
	0x9030, 0xffffffff, 0x100,
	0x9034, 0xffffffff, 0x100,
	0x9038, 0xffffffff, 0x100,
	0x903c, 0xffffffff, 0x100,
	0x9040, 0xffffffff, 0x100,
	0xa200, 0xffffffff, 0x100,
	0xa204, 0xffffffff, 0x100,
	0xa208, 0xffffffff, 0x100,
	0xa20c, 0xffffffff, 0x100,
	0x971c, 0xffffffff, 0x100,
	0x915c, 0xffffffff, 0x00020001,
	0x9160, 0xffffffff, 0x00040003,
	0x916c, 0xffffffff, 0x00060005,
	0x9170, 0xffffffff, 0x00080007,
	0x9174, 0xffffffff, 0x000a0009,
	0x9178, 0xffffffff, 0x000c000b,
	0x917c, 0xffffffff, 0x000e000d,
	0x9180, 0xffffffff, 0x0010000f,
	0x918c, 0xffffffff, 0x00120011,
	0x9190, 0xffffffff, 0x00140013,
	0x9194, 0xffffffff, 0x00020001,
	0x9198, 0xffffffff, 0x00040003,
	0x919c, 0xffffffff, 0x00060005,
	0x91a8, 0xffffffff, 0x00080007,
	0x91ac, 0xffffffff, 0x000a0009,
	0x91b0, 0xffffffff, 0x000c000b,
	0x91b4, 0xffffffff, 0x000e000d,
	0x91b8, 0xffffffff, 0x0010000f,
	0x91c4, 0xffffffff, 0x00120011,
	0x91c8, 0xffffffff, 0x00140013,
	0x91cc, 0xffffffff, 0x00020001,
	0x91d0, 0xffffffff, 0x00040003,
	0x91d4, 0xffffffff, 0x00060005,
	0x91e0, 0xffffffff, 0x00080007,
	0x91e4, 0xffffffff, 0x000a0009,
	0x91e8, 0xffffffff, 0x000c000b,
	0x91ec, 0xffffffff, 0x00020001,
	0x91f0, 0xffffffff, 0x00040003,
	0x91f4, 0xffffffff, 0x00060005,
	0x9200, 0xffffffff, 0x00080007,
	0x9204, 0xffffffff, 0x000a0009,
	0x9208, 0xffffffff, 0x000c000b,
	0x920c, 0xffffffff, 0x000e000d,
	0x9210, 0xffffffff, 0x0010000f,
	0x921c, 0xffffffff, 0x00120011,
	0x9220, 0xffffffff, 0x00140013,
	0x9224, 0xffffffff, 0x00020001,
	0x9228, 0xffffffff, 0x00040003,
	0x922c, 0xffffffff, 0x00060005,
	0x9238, 0xffffffff, 0x00080007,
	0x923c, 0xffffffff, 0x000a0009,
	0x9240, 0xffffffff, 0x000c000b,
	0x9244, 0xffffffff, 0x000e000d,
	0x9248, 0xffffffff, 0x0010000f,
	0x9254, 0xffffffff, 0x00120011,
	0x9258, 0xffffffff, 0x00140013,
	0x925c, 0xffffffff, 0x00020001,
	0x9260, 0xffffffff, 0x00040003,
	0x9264, 0xffffffff, 0x00060005,
	0x9270, 0xffffffff, 0x00080007,
	0x9274, 0xffffffff, 0x000a0009,
	0x9278, 0xffffffff, 0x000c000b,
	0x927c, 0xffffffff, 0x000e000d,
	0x9280, 0xffffffff, 0x0010000f,
	0x928c, 0xffffffff, 0x00120011,
	0x9290, 0xffffffff, 0x00140013,
	0x9294, 0xffffffff, 0x00020001,
	0x929c, 0xffffffff, 0x00040003,
	0x92a0, 0xffffffff, 0x00060005,
	0x92a4, 0xffffffff, 0x00080007
पूर्ण;

अटल स्थिर u32 rv710_golden_रेजिस्टरs[] =
अणु
	0x3f90, 0x00ff0000, 0x00fc0000,
	0x9148, 0x00ff0000, 0x00fc0000,
	0x3f94, 0x00ff0000, 0x00fc0000,
	0x914c, 0x00ff0000, 0x00fc0000,
	0xb4c, 0x00000020, 0x00000020,
	0xa180, 0xffffffff, 0x00003f3f
पूर्ण;

अटल स्थिर u32 rv710_mgcg_init[] =
अणु
	0x8bcc, 0xffffffff, 0x13030040,
	0x5448, 0xffffffff, 0x100,
	0x55e4, 0xffffffff, 0x100,
	0x160c, 0xffffffff, 0x100,
	0x5644, 0xffffffff, 0x100,
	0xc164, 0xffffffff, 0x100,
	0x8a18, 0xffffffff, 0x100,
	0x897c, 0xffffffff, 0x8000100,
	0x8b28, 0xffffffff, 0x3c000100,
	0x9144, 0xffffffff, 0x100,
	0x9a1c, 0xffffffff, 0x10000,
	0x9a50, 0xffffffff, 0x100,
	0x9a1c, 0xffffffff, 0x0,
	0x9870, 0xffffffff, 0x100,
	0x8d58, 0xffffffff, 0x100,
	0x9500, 0xffffffff, 0x0,
	0x9510, 0xffffffff, 0x100,
	0x9500, 0xffffffff, 0x1,
	0x9510, 0xffffffff, 0x100,
	0x9500, 0xffffffff, 0x8000,
	0x9490, 0xffffffff, 0x0,
	0x949c, 0xffffffff, 0x100,
	0x9490, 0xffffffff, 0x1,
	0x949c, 0xffffffff, 0x100,
	0x9490, 0xffffffff, 0x8000,
	0x9604, 0xffffffff, 0x0,
	0x9654, 0xffffffff, 0x100,
	0x9604, 0xffffffff, 0x1,
	0x9654, 0xffffffff, 0x100,
	0x9604, 0xffffffff, 0x80000000,
	0x9030, 0xffffffff, 0x100,
	0x9034, 0xffffffff, 0x100,
	0x9038, 0xffffffff, 0x100,
	0x903c, 0xffffffff, 0x100,
	0x9040, 0xffffffff, 0x100,
	0xa200, 0xffffffff, 0x100,
	0xa204, 0xffffffff, 0x100,
	0xa208, 0xffffffff, 0x100,
	0xa20c, 0xffffffff, 0x100,
	0x971c, 0xffffffff, 0x100,
	0x915c, 0xffffffff, 0x00020001,
	0x9174, 0xffffffff, 0x00000003,
	0x9178, 0xffffffff, 0x00050001,
	0x917c, 0xffffffff, 0x00030002,
	0x918c, 0xffffffff, 0x00000004,
	0x9190, 0xffffffff, 0x00070006,
	0x9194, 0xffffffff, 0x00050001,
	0x9198, 0xffffffff, 0x00030002,
	0x91a8, 0xffffffff, 0x00000004,
	0x91ac, 0xffffffff, 0x00070006,
	0x91e8, 0xffffffff, 0x00000001,
	0x9294, 0xffffffff, 0x00000001,
	0x929c, 0xffffffff, 0x00000002,
	0x92a0, 0xffffffff, 0x00040003,
	0x9150, 0xffffffff, 0x4d940000
पूर्ण;

अटल स्थिर u32 rv730_golden_रेजिस्टरs[] =
अणु
	0x3f90, 0x00ff0000, 0x00f00000,
	0x9148, 0x00ff0000, 0x00f00000,
	0x3f94, 0x00ff0000, 0x00f00000,
	0x914c, 0x00ff0000, 0x00f00000,
	0x900c, 0xffffffff, 0x003b033f,
	0xb4c, 0x00000020, 0x00000020,
	0xa180, 0xffffffff, 0x00003f3f
पूर्ण;

अटल स्थिर u32 rv730_mgcg_init[] =
अणु
	0x8bcc, 0xffffffff, 0x130300f9,
	0x5448, 0xffffffff, 0x100,
	0x55e4, 0xffffffff, 0x100,
	0x160c, 0xffffffff, 0x100,
	0x5644, 0xffffffff, 0x100,
	0xc164, 0xffffffff, 0x100,
	0x8a18, 0xffffffff, 0x100,
	0x897c, 0xffffffff, 0x8000100,
	0x8b28, 0xffffffff, 0x3c000100,
	0x9144, 0xffffffff, 0x100,
	0x9a1c, 0xffffffff, 0x10000,
	0x9a50, 0xffffffff, 0x100,
	0x9a1c, 0xffffffff, 0x10001,
	0x9a50, 0xffffffff, 0x100,
	0x9a1c, 0xffffffff, 0x0,
	0x9870, 0xffffffff, 0x100,
	0x8d58, 0xffffffff, 0x100,
	0x9500, 0xffffffff, 0x0,
	0x9510, 0xffffffff, 0x100,
	0x9500, 0xffffffff, 0x1,
	0x9510, 0xffffffff, 0x100,
	0x9500, 0xffffffff, 0x2,
	0x9510, 0xffffffff, 0x100,
	0x9500, 0xffffffff, 0x3,
	0x9510, 0xffffffff, 0x100,
	0x9500, 0xffffffff, 0x4,
	0x9510, 0xffffffff, 0x100,
	0x9500, 0xffffffff, 0x5,
	0x9510, 0xffffffff, 0x100,
	0x9500, 0xffffffff, 0x6,
	0x9510, 0xffffffff, 0x100,
	0x9500, 0xffffffff, 0x7,
	0x9510, 0xffffffff, 0x100,
	0x9500, 0xffffffff, 0x8000,
	0x9490, 0xffffffff, 0x0,
	0x949c, 0xffffffff, 0x100,
	0x9490, 0xffffffff, 0x1,
	0x949c, 0xffffffff, 0x100,
	0x9490, 0xffffffff, 0x2,
	0x949c, 0xffffffff, 0x100,
	0x9490, 0xffffffff, 0x3,
	0x949c, 0xffffffff, 0x100,
	0x9490, 0xffffffff, 0x4,
	0x949c, 0xffffffff, 0x100,
	0x9490, 0xffffffff, 0x5,
	0x949c, 0xffffffff, 0x100,
	0x9490, 0xffffffff, 0x6,
	0x949c, 0xffffffff, 0x100,
	0x9490, 0xffffffff, 0x7,
	0x949c, 0xffffffff, 0x100,
	0x9490, 0xffffffff, 0x8000,
	0x9604, 0xffffffff, 0x0,
	0x9654, 0xffffffff, 0x100,
	0x9604, 0xffffffff, 0x1,
	0x9654, 0xffffffff, 0x100,
	0x9604, 0xffffffff, 0x2,
	0x9654, 0xffffffff, 0x100,
	0x9604, 0xffffffff, 0x3,
	0x9654, 0xffffffff, 0x100,
	0x9604, 0xffffffff, 0x4,
	0x9654, 0xffffffff, 0x100,
	0x9604, 0xffffffff, 0x5,
	0x9654, 0xffffffff, 0x100,
	0x9604, 0xffffffff, 0x6,
	0x9654, 0xffffffff, 0x100,
	0x9604, 0xffffffff, 0x7,
	0x9654, 0xffffffff, 0x100,
	0x9604, 0xffffffff, 0x80000000,
	0x9030, 0xffffffff, 0x100,
	0x9034, 0xffffffff, 0x100,
	0x9038, 0xffffffff, 0x100,
	0x903c, 0xffffffff, 0x100,
	0x9040, 0xffffffff, 0x100,
	0xa200, 0xffffffff, 0x100,
	0xa204, 0xffffffff, 0x100,
	0xa208, 0xffffffff, 0x100,
	0xa20c, 0xffffffff, 0x100,
	0x971c, 0xffffffff, 0x100,
	0x915c, 0xffffffff, 0x00020001,
	0x916c, 0xffffffff, 0x00040003,
	0x9170, 0xffffffff, 0x00000005,
	0x9178, 0xffffffff, 0x00050001,
	0x917c, 0xffffffff, 0x00030002,
	0x918c, 0xffffffff, 0x00000004,
	0x9190, 0xffffffff, 0x00070006,
	0x9194, 0xffffffff, 0x00050001,
	0x9198, 0xffffffff, 0x00030002,
	0x91a8, 0xffffffff, 0x00000004,
	0x91ac, 0xffffffff, 0x00070006,
	0x91b0, 0xffffffff, 0x00050001,
	0x91b4, 0xffffffff, 0x00030002,
	0x91c4, 0xffffffff, 0x00000004,
	0x91c8, 0xffffffff, 0x00070006,
	0x91cc, 0xffffffff, 0x00050001,
	0x91d0, 0xffffffff, 0x00030002,
	0x91e0, 0xffffffff, 0x00000004,
	0x91e4, 0xffffffff, 0x00070006,
	0x91e8, 0xffffffff, 0x00000001,
	0x91ec, 0xffffffff, 0x00050001,
	0x91f0, 0xffffffff, 0x00030002,
	0x9200, 0xffffffff, 0x00000004,
	0x9204, 0xffffffff, 0x00070006,
	0x9208, 0xffffffff, 0x00050001,
	0x920c, 0xffffffff, 0x00030002,
	0x921c, 0xffffffff, 0x00000004,
	0x9220, 0xffffffff, 0x00070006,
	0x9224, 0xffffffff, 0x00050001,
	0x9228, 0xffffffff, 0x00030002,
	0x9238, 0xffffffff, 0x00000004,
	0x923c, 0xffffffff, 0x00070006,
	0x9240, 0xffffffff, 0x00050001,
	0x9244, 0xffffffff, 0x00030002,
	0x9254, 0xffffffff, 0x00000004,
	0x9258, 0xffffffff, 0x00070006,
	0x9294, 0xffffffff, 0x00000001,
	0x929c, 0xffffffff, 0x00000002,
	0x92a0, 0xffffffff, 0x00040003,
	0x92a4, 0xffffffff, 0x00000005
पूर्ण;

अटल स्थिर u32 rv740_golden_रेजिस्टरs[] =
अणु
	0x88c4, 0xffffffff, 0x00000082,
	0x28a50, 0xfffffffc, 0x00000004,
	0x2650, 0x00040000, 0,
	0x20bc, 0x00040000, 0,
	0x733c, 0xffffffff, 0x00000002,
	0x7300, 0xffffffff, 0x001000f0,
	0x3f90, 0x00ff0000, 0,
	0x9148, 0x00ff0000, 0,
	0x3f94, 0x00ff0000, 0,
	0x914c, 0x00ff0000, 0,
	0x240c, 0xffffffff, 0x00000380,
	0x8a14, 0x00000007, 0x00000007,
	0x8b24, 0xffffffff, 0x00ff0fff,
	0x28a4c, 0xffffffff, 0x00004000,
	0xa180, 0xffffffff, 0x00003f3f,
	0x8d00, 0xffffffff, 0x0e0e003a,
	0x8d04, 0xffffffff, 0x013a0e2a,
	0x8c00, 0xffffffff, 0xe400000f,
	0x8db0, 0xffffffff, 0x98989898,
	0x8db4, 0xffffffff, 0x98989898,
	0x8db8, 0xffffffff, 0x98989898,
	0x8dbc, 0xffffffff, 0x98989898,
	0x8dc0, 0xffffffff, 0x98989898,
	0x8dc4, 0xffffffff, 0x98989898,
	0x8dc8, 0xffffffff, 0x98989898,
	0x8dcc, 0xffffffff, 0x98989898,
	0x9058, 0xffffffff, 0x0fffc40f,
	0x900c, 0xffffffff, 0x003b033f,
	0x28350, 0xffffffff, 0,
	0x8cf0, 0x1fffffff, 0x08e00420,
	0x9508, 0xffffffff, 0x00000002,
	0x88c4, 0xffffffff, 0x000000c2,
	0x9698, 0x18000000, 0x18000000
पूर्ण;

अटल स्थिर u32 rv740_mgcg_init[] =
अणु
	0x8bcc, 0xffffffff, 0x13030100,
	0x5448, 0xffffffff, 0x100,
	0x55e4, 0xffffffff, 0x100,
	0x160c, 0xffffffff, 0x100,
	0x5644, 0xffffffff, 0x100,
	0xc164, 0xffffffff, 0x100,
	0x8a18, 0xffffffff, 0x100,
	0x897c, 0xffffffff, 0x100,
	0x8b28, 0xffffffff, 0x100,
	0x9144, 0xffffffff, 0x100,
	0x9a1c, 0xffffffff, 0x10000,
	0x9a50, 0xffffffff, 0x100,
	0x9a1c, 0xffffffff, 0x10001,
	0x9a50, 0xffffffff, 0x100,
	0x9a1c, 0xffffffff, 0x10002,
	0x9a50, 0xffffffff, 0x100,
	0x9a1c, 0xffffffff, 0x10003,
	0x9a50, 0xffffffff, 0x100,
	0x9a1c, 0xffffffff, 0x0,
	0x9870, 0xffffffff, 0x100,
	0x8d58, 0xffffffff, 0x100,
	0x9500, 0xffffffff, 0x0,
	0x9510, 0xffffffff, 0x100,
	0x9500, 0xffffffff, 0x1,
	0x9510, 0xffffffff, 0x100,
	0x9500, 0xffffffff, 0x2,
	0x9510, 0xffffffff, 0x100,
	0x9500, 0xffffffff, 0x3,
	0x9510, 0xffffffff, 0x100,
	0x9500, 0xffffffff, 0x4,
	0x9510, 0xffffffff, 0x100,
	0x9500, 0xffffffff, 0x5,
	0x9510, 0xffffffff, 0x100,
	0x9500, 0xffffffff, 0x6,
	0x9510, 0xffffffff, 0x100,
	0x9500, 0xffffffff, 0x7,
	0x9510, 0xffffffff, 0x100,
	0x9500, 0xffffffff, 0x8000,
	0x9490, 0xffffffff, 0x0,
	0x949c, 0xffffffff, 0x100,
	0x9490, 0xffffffff, 0x1,
	0x949c, 0xffffffff, 0x100,
	0x9490, 0xffffffff, 0x2,
	0x949c, 0xffffffff, 0x100,
	0x9490, 0xffffffff, 0x3,
	0x949c, 0xffffffff, 0x100,
	0x9490, 0xffffffff, 0x4,
	0x949c, 0xffffffff, 0x100,
	0x9490, 0xffffffff, 0x5,
	0x949c, 0xffffffff, 0x100,
	0x9490, 0xffffffff, 0x6,
	0x949c, 0xffffffff, 0x100,
	0x9490, 0xffffffff, 0x7,
	0x949c, 0xffffffff, 0x100,
	0x9490, 0xffffffff, 0x8000,
	0x9604, 0xffffffff, 0x0,
	0x9654, 0xffffffff, 0x100,
	0x9604, 0xffffffff, 0x1,
	0x9654, 0xffffffff, 0x100,
	0x9604, 0xffffffff, 0x2,
	0x9654, 0xffffffff, 0x100,
	0x9604, 0xffffffff, 0x3,
	0x9654, 0xffffffff, 0x100,
	0x9604, 0xffffffff, 0x4,
	0x9654, 0xffffffff, 0x100,
	0x9604, 0xffffffff, 0x5,
	0x9654, 0xffffffff, 0x100,
	0x9604, 0xffffffff, 0x6,
	0x9654, 0xffffffff, 0x100,
	0x9604, 0xffffffff, 0x7,
	0x9654, 0xffffffff, 0x100,
	0x9604, 0xffffffff, 0x80000000,
	0x9030, 0xffffffff, 0x100,
	0x9034, 0xffffffff, 0x100,
	0x9038, 0xffffffff, 0x100,
	0x903c, 0xffffffff, 0x100,
	0x9040, 0xffffffff, 0x100,
	0xa200, 0xffffffff, 0x100,
	0xa204, 0xffffffff, 0x100,
	0xa208, 0xffffffff, 0x100,
	0xa20c, 0xffffffff, 0x100,
	0x971c, 0xffffffff, 0x100,
	0x915c, 0xffffffff, 0x00020001,
	0x9160, 0xffffffff, 0x00040003,
	0x916c, 0xffffffff, 0x00060005,
	0x9170, 0xffffffff, 0x00080007,
	0x9174, 0xffffffff, 0x000a0009,
	0x9178, 0xffffffff, 0x000c000b,
	0x917c, 0xffffffff, 0x000e000d,
	0x9180, 0xffffffff, 0x0010000f,
	0x918c, 0xffffffff, 0x00120011,
	0x9190, 0xffffffff, 0x00140013,
	0x9194, 0xffffffff, 0x00020001,
	0x9198, 0xffffffff, 0x00040003,
	0x919c, 0xffffffff, 0x00060005,
	0x91a8, 0xffffffff, 0x00080007,
	0x91ac, 0xffffffff, 0x000a0009,
	0x91b0, 0xffffffff, 0x000c000b,
	0x91b4, 0xffffffff, 0x000e000d,
	0x91b8, 0xffffffff, 0x0010000f,
	0x91c4, 0xffffffff, 0x00120011,
	0x91c8, 0xffffffff, 0x00140013,
	0x91cc, 0xffffffff, 0x00020001,
	0x91d0, 0xffffffff, 0x00040003,
	0x91d4, 0xffffffff, 0x00060005,
	0x91e0, 0xffffffff, 0x00080007,
	0x91e4, 0xffffffff, 0x000a0009,
	0x91e8, 0xffffffff, 0x000c000b,
	0x91ec, 0xffffffff, 0x00020001,
	0x91f0, 0xffffffff, 0x00040003,
	0x91f4, 0xffffffff, 0x00060005,
	0x9200, 0xffffffff, 0x00080007,
	0x9204, 0xffffffff, 0x000a0009,
	0x9208, 0xffffffff, 0x000c000b,
	0x920c, 0xffffffff, 0x000e000d,
	0x9210, 0xffffffff, 0x0010000f,
	0x921c, 0xffffffff, 0x00120011,
	0x9220, 0xffffffff, 0x00140013,
	0x9224, 0xffffffff, 0x00020001,
	0x9228, 0xffffffff, 0x00040003,
	0x922c, 0xffffffff, 0x00060005,
	0x9238, 0xffffffff, 0x00080007,
	0x923c, 0xffffffff, 0x000a0009,
	0x9240, 0xffffffff, 0x000c000b,
	0x9244, 0xffffffff, 0x000e000d,
	0x9248, 0xffffffff, 0x0010000f,
	0x9254, 0xffffffff, 0x00120011,
	0x9258, 0xffffffff, 0x00140013,
	0x9294, 0xffffffff, 0x00020001,
	0x929c, 0xffffffff, 0x00040003,
	0x92a0, 0xffffffff, 0x00060005,
	0x92a4, 0xffffffff, 0x00080007
पूर्ण;

अटल व्योम rv770_init_golden_रेजिस्टरs(काष्ठा radeon_device *rdev)
अणु
	चयन (rdev->family) अणु
	हाल CHIP_RV770:
		radeon_program_रेजिस्टर_sequence(rdev,
						 r7xx_golden_रेजिस्टरs,
						 (स्थिर u32)ARRAY_SIZE(r7xx_golden_रेजिस्टरs));
		radeon_program_रेजिस्टर_sequence(rdev,
						 r7xx_golden_dyn_gpr_रेजिस्टरs,
						 (स्थिर u32)ARRAY_SIZE(r7xx_golden_dyn_gpr_रेजिस्टरs));
		अगर (rdev->pdev->device == 0x994e)
			radeon_program_रेजिस्टर_sequence(rdev,
							 rv770ce_golden_रेजिस्टरs,
							 (स्थिर u32)ARRAY_SIZE(rv770ce_golden_रेजिस्टरs));
		अन्यथा
			radeon_program_रेजिस्टर_sequence(rdev,
							 rv770_golden_रेजिस्टरs,
							 (स्थिर u32)ARRAY_SIZE(rv770_golden_रेजिस्टरs));
		radeon_program_रेजिस्टर_sequence(rdev,
						 rv770_mgcg_init,
						 (स्थिर u32)ARRAY_SIZE(rv770_mgcg_init));
		अवरोध;
	हाल CHIP_RV730:
		radeon_program_रेजिस्टर_sequence(rdev,
						 r7xx_golden_रेजिस्टरs,
						 (स्थिर u32)ARRAY_SIZE(r7xx_golden_रेजिस्टरs));
		radeon_program_रेजिस्टर_sequence(rdev,
						 r7xx_golden_dyn_gpr_रेजिस्टरs,
						 (स्थिर u32)ARRAY_SIZE(r7xx_golden_dyn_gpr_रेजिस्टरs));
		radeon_program_रेजिस्टर_sequence(rdev,
						 rv730_golden_रेजिस्टरs,
						 (स्थिर u32)ARRAY_SIZE(rv730_golden_रेजिस्टरs));
		radeon_program_रेजिस्टर_sequence(rdev,
						 rv730_mgcg_init,
						 (स्थिर u32)ARRAY_SIZE(rv730_mgcg_init));
		अवरोध;
	हाल CHIP_RV710:
		radeon_program_रेजिस्टर_sequence(rdev,
						 r7xx_golden_रेजिस्टरs,
						 (स्थिर u32)ARRAY_SIZE(r7xx_golden_रेजिस्टरs));
		radeon_program_रेजिस्टर_sequence(rdev,
						 r7xx_golden_dyn_gpr_रेजिस्टरs,
						 (स्थिर u32)ARRAY_SIZE(r7xx_golden_dyn_gpr_रेजिस्टरs));
		radeon_program_रेजिस्टर_sequence(rdev,
						 rv710_golden_रेजिस्टरs,
						 (स्थिर u32)ARRAY_SIZE(rv710_golden_रेजिस्टरs));
		radeon_program_रेजिस्टर_sequence(rdev,
						 rv710_mgcg_init,
						 (स्थिर u32)ARRAY_SIZE(rv710_mgcg_init));
		अवरोध;
	हाल CHIP_RV740:
		radeon_program_रेजिस्टर_sequence(rdev,
						 rv740_golden_रेजिस्टरs,
						 (स्थिर u32)ARRAY_SIZE(rv740_golden_रेजिस्टरs));
		radeon_program_रेजिस्टर_sequence(rdev,
						 rv740_mgcg_init,
						 (स्थिर u32)ARRAY_SIZE(rv740_mgcg_init));
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

#घोषणा PCIE_BUS_CLK                10000
#घोषणा TCLK                        (PCIE_BUS_CLK / 10)

/**
 * rv770_get_xclk - get the xclk
 *
 * @rdev: radeon_device poपूर्णांकer
 *
 * Returns the reference घड़ी used by the gfx engine
 * (r7xx-cayman).
 */
u32 rv770_get_xclk(काष्ठा radeon_device *rdev)
अणु
	u32 reference_घड़ी = rdev->घड़ी.spll.reference_freq;
	u32 पंचांगp = RREG32(CG_CLKPIN_CNTL);

	अगर (पंचांगp & MUX_TCLK_TO_XCLK)
		वापस TCLK;

	अगर (पंचांगp & XTALIN_DIVIDE)
		वापस reference_घड़ी / 4;

	वापस reference_घड़ी;
पूर्ण

व्योम rv770_page_flip(काष्ठा radeon_device *rdev, पूर्णांक crtc_id, u64 crtc_base, bool async)
अणु
	काष्ठा radeon_crtc *radeon_crtc = rdev->mode_info.crtcs[crtc_id];
	u32 पंचांगp = RREG32(AVIVO_D1GRPH_UPDATE + radeon_crtc->crtc_offset);
	पूर्णांक i;

	/* Lock the graphics update lock */
	पंचांगp |= AVIVO_D1GRPH_UPDATE_LOCK;
	WREG32(AVIVO_D1GRPH_UPDATE + radeon_crtc->crtc_offset, पंचांगp);

	/* update the scanout addresses */
	WREG32(AVIVO_D1GRPH_FLIP_CONTROL + radeon_crtc->crtc_offset,
	       async ? AVIVO_D1GRPH_SURFACE_UPDATE_H_RETRACE_EN : 0);
	अगर (radeon_crtc->crtc_id) अणु
		WREG32(D2GRPH_SECONDARY_SURFACE_ADDRESS_HIGH, upper_32_bits(crtc_base));
		WREG32(D2GRPH_PRIMARY_SURFACE_ADDRESS_HIGH, upper_32_bits(crtc_base));
	पूर्ण अन्यथा अणु
		WREG32(D1GRPH_SECONDARY_SURFACE_ADDRESS_HIGH, upper_32_bits(crtc_base));
		WREG32(D1GRPH_PRIMARY_SURFACE_ADDRESS_HIGH, upper_32_bits(crtc_base));
	पूर्ण
	WREG32(D1GRPH_SECONDARY_SURFACE_ADDRESS + radeon_crtc->crtc_offset,
	       (u32)crtc_base);
	WREG32(D1GRPH_PRIMARY_SURFACE_ADDRESS + radeon_crtc->crtc_offset,
	       (u32)crtc_base);

	/* Wait क्रम update_pending to go high. */
	क्रम (i = 0; i < rdev->usec_समयout; i++) अणु
		अगर (RREG32(AVIVO_D1GRPH_UPDATE + radeon_crtc->crtc_offset) & AVIVO_D1GRPH_SURFACE_UPDATE_PENDING)
			अवरोध;
		udelay(1);
	पूर्ण
	DRM_DEBUG("Update pending now high. Unlocking vupdate_lock.\n");

	/* Unlock the lock, so द्विगुन-buffering can take place inside vblank */
	पंचांगp &= ~AVIVO_D1GRPH_UPDATE_LOCK;
	WREG32(AVIVO_D1GRPH_UPDATE + radeon_crtc->crtc_offset, पंचांगp);
पूर्ण

bool rv770_page_flip_pending(काष्ठा radeon_device *rdev, पूर्णांक crtc_id)
अणु
	काष्ठा radeon_crtc *radeon_crtc = rdev->mode_info.crtcs[crtc_id];

	/* Return current update_pending status: */
	वापस !!(RREG32(AVIVO_D1GRPH_UPDATE + radeon_crtc->crtc_offset) &
		AVIVO_D1GRPH_SURFACE_UPDATE_PENDING);
पूर्ण

/* get temperature in millidegrees */
पूर्णांक rv770_get_temp(काष्ठा radeon_device *rdev)
अणु
	u32 temp = (RREG32(CG_MULT_THERMAL_STATUS) & ASIC_T_MASK) >>
		ASIC_T_SHIFT;
	पूर्णांक actual_temp;

	अगर (temp & 0x400)
		actual_temp = -256;
	अन्यथा अगर (temp & 0x200)
		actual_temp = 255;
	अन्यथा अगर (temp & 0x100) अणु
		actual_temp = temp & 0x1ff;
		actual_temp |= ~0x1ff;
	पूर्ण अन्यथा
		actual_temp = temp & 0xff;

	वापस (actual_temp * 1000) / 2;
पूर्ण

व्योम rv770_pm_misc(काष्ठा radeon_device *rdev)
अणु
	पूर्णांक req_ps_idx = rdev->pm.requested_घातer_state_index;
	पूर्णांक req_cm_idx = rdev->pm.requested_घड़ी_mode_index;
	काष्ठा radeon_घातer_state *ps = &rdev->pm.घातer_state[req_ps_idx];
	काष्ठा radeon_voltage *voltage = &ps->घड़ी_info[req_cm_idx].voltage;

	अगर ((voltage->type == VOLTAGE_SW) && voltage->voltage) अणु
		/* 0xff01 is a flag rather then an actual voltage */
		अगर (voltage->voltage == 0xff01)
			वापस;
		अगर (voltage->voltage != rdev->pm.current_vddc) अणु
			radeon_atom_set_voltage(rdev, voltage->voltage, SET_VOLTAGE_TYPE_ASIC_VDDC);
			rdev->pm.current_vddc = voltage->voltage;
			DRM_DEBUG("Setting: v: %d\n", voltage->voltage);
		पूर्ण
	पूर्ण
पूर्ण

/*
 * GART
 */
अटल पूर्णांक rv770_pcie_gart_enable(काष्ठा radeon_device *rdev)
अणु
	u32 पंचांगp;
	पूर्णांक r, i;

	अगर (rdev->gart.robj == शून्य) अणु
		dev_err(rdev->dev, "No VRAM object for PCIE GART.\n");
		वापस -EINVAL;
	पूर्ण
	r = radeon_gart_table_vram_pin(rdev);
	अगर (r)
		वापस r;
	/* Setup L2 cache */
	WREG32(VM_L2_CNTL, ENABLE_L2_CACHE | ENABLE_L2_FRAGMENT_PROCESSING |
				ENABLE_L2_PTE_CACHE_LRU_UPDATE_BY_WRITE |
				EFFECTIVE_L2_QUEUE_SIZE(7));
	WREG32(VM_L2_CNTL2, 0);
	WREG32(VM_L2_CNTL3, BANK_SELECT(0) | CACHE_UPDATE_MODE(2));
	/* Setup TLB control */
	पंचांगp = ENABLE_L1_TLB | ENABLE_L1_FRAGMENT_PROCESSING |
		SYSTEM_ACCESS_MODE_NOT_IN_SYS |
		SYSTEM_APERTURE_UNMAPPED_ACCESS_PASS_THRU |
		EFFECTIVE_L1_TLB_SIZE(5) | EFFECTIVE_L1_QUEUE_SIZE(5);
	WREG32(MC_VM_MD_L1_TLB0_CNTL, पंचांगp);
	WREG32(MC_VM_MD_L1_TLB1_CNTL, पंचांगp);
	WREG32(MC_VM_MD_L1_TLB2_CNTL, पंचांगp);
	अगर (rdev->family == CHIP_RV740)
		WREG32(MC_VM_MD_L1_TLB3_CNTL, पंचांगp);
	WREG32(MC_VM_MB_L1_TLB0_CNTL, पंचांगp);
	WREG32(MC_VM_MB_L1_TLB1_CNTL, पंचांगp);
	WREG32(MC_VM_MB_L1_TLB2_CNTL, पंचांगp);
	WREG32(MC_VM_MB_L1_TLB3_CNTL, पंचांगp);
	WREG32(VM_CONTEXT0_PAGE_TABLE_START_ADDR, rdev->mc.gtt_start >> 12);
	WREG32(VM_CONTEXT0_PAGE_TABLE_END_ADDR, rdev->mc.gtt_end >> 12);
	WREG32(VM_CONTEXT0_PAGE_TABLE_BASE_ADDR, rdev->gart.table_addr >> 12);
	WREG32(VM_CONTEXT0_CNTL, ENABLE_CONTEXT | PAGE_TABLE_DEPTH(0) |
				RANGE_PROTECTION_FAULT_ENABLE_DEFAULT);
	WREG32(VM_CONTEXT0_PROTECTION_FAULT_DEFAULT_ADDR,
			(u32)(rdev->dummy_page.addr >> 12));
	क्रम (i = 1; i < 7; i++)
		WREG32(VM_CONTEXT0_CNTL + (i * 4), 0);

	r600_pcie_gart_tlb_flush(rdev);
	DRM_INFO("PCIE GART of %uM enabled (table at 0x%016llX).\n",
		 (अचिन्हित)(rdev->mc.gtt_size >> 20),
		 (अचिन्हित दीर्घ दीर्घ)rdev->gart.table_addr);
	rdev->gart.पढ़ोy = true;
	वापस 0;
पूर्ण

अटल व्योम rv770_pcie_gart_disable(काष्ठा radeon_device *rdev)
अणु
	u32 पंचांगp;
	पूर्णांक i;

	/* Disable all tables */
	क्रम (i = 0; i < 7; i++)
		WREG32(VM_CONTEXT0_CNTL + (i * 4), 0);

	/* Setup L2 cache */
	WREG32(VM_L2_CNTL, ENABLE_L2_FRAGMENT_PROCESSING |
				EFFECTIVE_L2_QUEUE_SIZE(7));
	WREG32(VM_L2_CNTL2, 0);
	WREG32(VM_L2_CNTL3, BANK_SELECT(0) | CACHE_UPDATE_MODE(2));
	/* Setup TLB control */
	पंचांगp = EFFECTIVE_L1_TLB_SIZE(5) | EFFECTIVE_L1_QUEUE_SIZE(5);
	WREG32(MC_VM_MD_L1_TLB0_CNTL, पंचांगp);
	WREG32(MC_VM_MD_L1_TLB1_CNTL, पंचांगp);
	WREG32(MC_VM_MD_L1_TLB2_CNTL, पंचांगp);
	WREG32(MC_VM_MB_L1_TLB0_CNTL, पंचांगp);
	WREG32(MC_VM_MB_L1_TLB1_CNTL, पंचांगp);
	WREG32(MC_VM_MB_L1_TLB2_CNTL, पंचांगp);
	WREG32(MC_VM_MB_L1_TLB3_CNTL, पंचांगp);
	radeon_gart_table_vram_unpin(rdev);
पूर्ण

अटल व्योम rv770_pcie_gart_fini(काष्ठा radeon_device *rdev)
अणु
	radeon_gart_fini(rdev);
	rv770_pcie_gart_disable(rdev);
	radeon_gart_table_vram_मुक्त(rdev);
पूर्ण


अटल व्योम rv770_agp_enable(काष्ठा radeon_device *rdev)
अणु
	u32 पंचांगp;
	पूर्णांक i;

	/* Setup L2 cache */
	WREG32(VM_L2_CNTL, ENABLE_L2_CACHE | ENABLE_L2_FRAGMENT_PROCESSING |
				ENABLE_L2_PTE_CACHE_LRU_UPDATE_BY_WRITE |
				EFFECTIVE_L2_QUEUE_SIZE(7));
	WREG32(VM_L2_CNTL2, 0);
	WREG32(VM_L2_CNTL3, BANK_SELECT(0) | CACHE_UPDATE_MODE(2));
	/* Setup TLB control */
	पंचांगp = ENABLE_L1_TLB | ENABLE_L1_FRAGMENT_PROCESSING |
		SYSTEM_ACCESS_MODE_NOT_IN_SYS |
		SYSTEM_APERTURE_UNMAPPED_ACCESS_PASS_THRU |
		EFFECTIVE_L1_TLB_SIZE(5) | EFFECTIVE_L1_QUEUE_SIZE(5);
	WREG32(MC_VM_MD_L1_TLB0_CNTL, पंचांगp);
	WREG32(MC_VM_MD_L1_TLB1_CNTL, पंचांगp);
	WREG32(MC_VM_MD_L1_TLB2_CNTL, पंचांगp);
	WREG32(MC_VM_MB_L1_TLB0_CNTL, पंचांगp);
	WREG32(MC_VM_MB_L1_TLB1_CNTL, पंचांगp);
	WREG32(MC_VM_MB_L1_TLB2_CNTL, पंचांगp);
	WREG32(MC_VM_MB_L1_TLB3_CNTL, पंचांगp);
	क्रम (i = 0; i < 7; i++)
		WREG32(VM_CONTEXT0_CNTL + (i * 4), 0);
पूर्ण

अटल व्योम rv770_mc_program(काष्ठा radeon_device *rdev)
अणु
	काष्ठा rv515_mc_save save;
	u32 पंचांगp;
	पूर्णांक i, j;

	/* Initialize HDP */
	क्रम (i = 0, j = 0; i < 32; i++, j += 0x18) अणु
		WREG32((0x2c14 + j), 0x00000000);
		WREG32((0x2c18 + j), 0x00000000);
		WREG32((0x2c1c + j), 0x00000000);
		WREG32((0x2c20 + j), 0x00000000);
		WREG32((0x2c24 + j), 0x00000000);
	पूर्ण
	/* r7xx hw bug.  Read from HDP_DEBUG1 rather
	 * than writing to HDP_REG_COHERENCY_FLUSH_CNTL
	 */
	पंचांगp = RREG32(HDP_DEBUG1);

	rv515_mc_stop(rdev, &save);
	अगर (r600_mc_रुको_क्रम_idle(rdev)) अणु
		dev_warn(rdev->dev, "Wait for MC idle timedout !\n");
	पूर्ण
	/* Lockout access through VGA aperture*/
	WREG32(VGA_HDP_CONTROL, VGA_MEMORY_DISABLE);
	/* Update configuration */
	अगर (rdev->flags & RADEON_IS_AGP) अणु
		अगर (rdev->mc.vram_start < rdev->mc.gtt_start) अणु
			/* VRAM beक्रमe AGP */
			WREG32(MC_VM_SYSTEM_APERTURE_LOW_ADDR,
				rdev->mc.vram_start >> 12);
			WREG32(MC_VM_SYSTEM_APERTURE_HIGH_ADDR,
				rdev->mc.gtt_end >> 12);
		पूर्ण अन्यथा अणु
			/* VRAM after AGP */
			WREG32(MC_VM_SYSTEM_APERTURE_LOW_ADDR,
				rdev->mc.gtt_start >> 12);
			WREG32(MC_VM_SYSTEM_APERTURE_HIGH_ADDR,
				rdev->mc.vram_end >> 12);
		पूर्ण
	पूर्ण अन्यथा अणु
		WREG32(MC_VM_SYSTEM_APERTURE_LOW_ADDR,
			rdev->mc.vram_start >> 12);
		WREG32(MC_VM_SYSTEM_APERTURE_HIGH_ADDR,
			rdev->mc.vram_end >> 12);
	पूर्ण
	WREG32(MC_VM_SYSTEM_APERTURE_DEFAULT_ADDR, rdev->vram_scratch.gpu_addr >> 12);
	पंचांगp = ((rdev->mc.vram_end >> 24) & 0xFFFF) << 16;
	पंचांगp |= ((rdev->mc.vram_start >> 24) & 0xFFFF);
	WREG32(MC_VM_FB_LOCATION, पंचांगp);
	WREG32(HDP_NONSURFACE_BASE, (rdev->mc.vram_start >> 8));
	WREG32(HDP_NONSURFACE_INFO, (2 << 7));
	WREG32(HDP_NONSURFACE_SIZE, 0x3FFFFFFF);
	अगर (rdev->flags & RADEON_IS_AGP) अणु
		WREG32(MC_VM_AGP_TOP, rdev->mc.gtt_end >> 16);
		WREG32(MC_VM_AGP_BOT, rdev->mc.gtt_start >> 16);
		WREG32(MC_VM_AGP_BASE, rdev->mc.agp_base >> 22);
	पूर्ण अन्यथा अणु
		WREG32(MC_VM_AGP_BASE, 0);
		WREG32(MC_VM_AGP_TOP, 0x0FFFFFFF);
		WREG32(MC_VM_AGP_BOT, 0x0FFFFFFF);
	पूर्ण
	अगर (r600_mc_रुको_क्रम_idle(rdev)) अणु
		dev_warn(rdev->dev, "Wait for MC idle timedout !\n");
	पूर्ण
	rv515_mc_resume(rdev, &save);
	/* we need to own VRAM, so turn off the VGA renderer here
	 * to stop it overwriting our objects */
	rv515_vga_render_disable(rdev);
पूर्ण


/*
 * CP.
 */
व्योम r700_cp_stop(काष्ठा radeon_device *rdev)
अणु
	अगर (rdev->asic->copy.copy_ring_index == RADEON_RING_TYPE_GFX_INDEX)
		radeon_tपंचांग_set_active_vram_size(rdev, rdev->mc.visible_vram_size);
	WREG32(CP_ME_CNTL, (CP_ME_HALT | CP_PFP_HALT));
	WREG32(SCRATCH_UMSK, 0);
	rdev->ring[RADEON_RING_TYPE_GFX_INDEX].पढ़ोy = false;
पूर्ण

अटल पूर्णांक rv770_cp_load_microcode(काष्ठा radeon_device *rdev)
अणु
	स्थिर __be32 *fw_data;
	पूर्णांक i;

	अगर (!rdev->me_fw || !rdev->pfp_fw)
		वापस -EINVAL;

	r700_cp_stop(rdev);
	WREG32(CP_RB_CNTL,
#अगर_घोषित __BIG_ENDIAN
	       BUF_SWAP_32BIT |
#पूर्ण_अगर
	       RB_NO_UPDATE | RB_BLKSZ(15) | RB_BUFSZ(3));

	/* Reset cp */
	WREG32(GRBM_SOFT_RESET, SOFT_RESET_CP);
	RREG32(GRBM_SOFT_RESET);
	mdelay(15);
	WREG32(GRBM_SOFT_RESET, 0);

	fw_data = (स्थिर __be32 *)rdev->pfp_fw->data;
	WREG32(CP_PFP_UCODE_ADDR, 0);
	क्रम (i = 0; i < R700_PFP_UCODE_SIZE; i++)
		WREG32(CP_PFP_UCODE_DATA, be32_to_cpup(fw_data++));
	WREG32(CP_PFP_UCODE_ADDR, 0);

	fw_data = (स्थिर __be32 *)rdev->me_fw->data;
	WREG32(CP_ME_RAM_WADDR, 0);
	क्रम (i = 0; i < R700_PM4_UCODE_SIZE; i++)
		WREG32(CP_ME_RAM_DATA, be32_to_cpup(fw_data++));

	WREG32(CP_PFP_UCODE_ADDR, 0);
	WREG32(CP_ME_RAM_WADDR, 0);
	WREG32(CP_ME_RAM_RADDR, 0);
	वापस 0;
पूर्ण

व्योम r700_cp_fini(काष्ठा radeon_device *rdev)
अणु
	काष्ठा radeon_ring *ring = &rdev->ring[RADEON_RING_TYPE_GFX_INDEX];
	r700_cp_stop(rdev);
	radeon_ring_fini(rdev, ring);
	radeon_scratch_मुक्त(rdev, ring->rptr_save_reg);
पूर्ण

व्योम rv770_set_clk_bypass_mode(काष्ठा radeon_device *rdev)
अणु
	u32 पंचांगp, i;

	अगर (rdev->flags & RADEON_IS_IGP)
		वापस;

	पंचांगp = RREG32(CG_SPLL_FUNC_CNTL_2);
	पंचांगp &= SCLK_MUX_SEL_MASK;
	पंचांगp |= SCLK_MUX_SEL(1) | SCLK_MUX_UPDATE;
	WREG32(CG_SPLL_FUNC_CNTL_2, पंचांगp);

	क्रम (i = 0; i < rdev->usec_समयout; i++) अणु
		अगर (RREG32(CG_SPLL_STATUS) & SPLL_CHG_STATUS)
			अवरोध;
		udelay(1);
	पूर्ण

	पंचांगp &= ~SCLK_MUX_UPDATE;
	WREG32(CG_SPLL_FUNC_CNTL_2, पंचांगp);

	पंचांगp = RREG32(MPLL_CNTL_MODE);
	अगर ((rdev->family == CHIP_RV710) || (rdev->family == CHIP_RV730))
		पंचांगp &= ~RV730_MPLL_MCLK_SEL;
	अन्यथा
		पंचांगp &= ~MPLL_MCLK_SEL;
	WREG32(MPLL_CNTL_MODE, पंचांगp);
पूर्ण

/*
 * Core functions
 */
अटल व्योम rv770_gpu_init(काष्ठा radeon_device *rdev)
अणु
	पूर्णांक i, j, num_qd_pipes;
	u32 ta_aux_cntl;
	u32 sx_debug_1;
	u32 smx_dc_ctl0;
	u32 db_debug3;
	u32 num_gs_verts_per_thपढ़ो;
	u32 vgt_gs_per_es;
	u32 gs_prim_buffer_depth = 0;
	u32 sq_ms_fअगरo_sizes;
	u32 sq_config;
	u32 sq_thपढ़ो_resource_mgmt;
	u32 hdp_host_path_cntl;
	u32 sq_dyn_gpr_size_simd_ab_0;
	u32 gb_tiling_config = 0;
	u32 cc_gc_shader_pipe_config = 0;
	u32 mc_arb_ramcfg;
	u32 db_debug4, पंचांगp;
	u32 inactive_pipes, shader_pipe_config;
	u32 disabled_rb_mask;
	अचिन्हित active_number;

	/* setup chip specs */
	rdev->config.rv770.tiling_group_size = 256;
	चयन (rdev->family) अणु
	हाल CHIP_RV770:
		rdev->config.rv770.max_pipes = 4;
		rdev->config.rv770.max_tile_pipes = 8;
		rdev->config.rv770.max_simds = 10;
		rdev->config.rv770.max_backends = 4;
		rdev->config.rv770.max_gprs = 256;
		rdev->config.rv770.max_thपढ़ोs = 248;
		rdev->config.rv770.max_stack_entries = 512;
		rdev->config.rv770.max_hw_contexts = 8;
		rdev->config.rv770.max_gs_thपढ़ोs = 16 * 2;
		rdev->config.rv770.sx_max_export_size = 128;
		rdev->config.rv770.sx_max_export_pos_size = 16;
		rdev->config.rv770.sx_max_export_smx_size = 112;
		rdev->config.rv770.sq_num_cf_insts = 2;

		rdev->config.rv770.sx_num_of_sets = 7;
		rdev->config.rv770.sc_prim_fअगरo_size = 0xF9;
		rdev->config.rv770.sc_hiz_tile_fअगरo_size = 0x30;
		rdev->config.rv770.sc_earlyz_tile_fअगरo_fize = 0x130;
		अवरोध;
	हाल CHIP_RV730:
		rdev->config.rv770.max_pipes = 2;
		rdev->config.rv770.max_tile_pipes = 4;
		rdev->config.rv770.max_simds = 8;
		rdev->config.rv770.max_backends = 2;
		rdev->config.rv770.max_gprs = 128;
		rdev->config.rv770.max_thपढ़ोs = 248;
		rdev->config.rv770.max_stack_entries = 256;
		rdev->config.rv770.max_hw_contexts = 8;
		rdev->config.rv770.max_gs_thपढ़ोs = 16 * 2;
		rdev->config.rv770.sx_max_export_size = 256;
		rdev->config.rv770.sx_max_export_pos_size = 32;
		rdev->config.rv770.sx_max_export_smx_size = 224;
		rdev->config.rv770.sq_num_cf_insts = 2;

		rdev->config.rv770.sx_num_of_sets = 7;
		rdev->config.rv770.sc_prim_fअगरo_size = 0xf9;
		rdev->config.rv770.sc_hiz_tile_fअगरo_size = 0x30;
		rdev->config.rv770.sc_earlyz_tile_fअगरo_fize = 0x130;
		अगर (rdev->config.rv770.sx_max_export_pos_size > 16) अणु
			rdev->config.rv770.sx_max_export_pos_size -= 16;
			rdev->config.rv770.sx_max_export_smx_size += 16;
		पूर्ण
		अवरोध;
	हाल CHIP_RV710:
		rdev->config.rv770.max_pipes = 2;
		rdev->config.rv770.max_tile_pipes = 2;
		rdev->config.rv770.max_simds = 2;
		rdev->config.rv770.max_backends = 1;
		rdev->config.rv770.max_gprs = 256;
		rdev->config.rv770.max_thपढ़ोs = 192;
		rdev->config.rv770.max_stack_entries = 256;
		rdev->config.rv770.max_hw_contexts = 4;
		rdev->config.rv770.max_gs_thपढ़ोs = 8 * 2;
		rdev->config.rv770.sx_max_export_size = 128;
		rdev->config.rv770.sx_max_export_pos_size = 16;
		rdev->config.rv770.sx_max_export_smx_size = 112;
		rdev->config.rv770.sq_num_cf_insts = 1;

		rdev->config.rv770.sx_num_of_sets = 7;
		rdev->config.rv770.sc_prim_fअगरo_size = 0x40;
		rdev->config.rv770.sc_hiz_tile_fअगरo_size = 0x30;
		rdev->config.rv770.sc_earlyz_tile_fअगरo_fize = 0x130;
		अवरोध;
	हाल CHIP_RV740:
		rdev->config.rv770.max_pipes = 4;
		rdev->config.rv770.max_tile_pipes = 4;
		rdev->config.rv770.max_simds = 8;
		rdev->config.rv770.max_backends = 4;
		rdev->config.rv770.max_gprs = 256;
		rdev->config.rv770.max_thपढ़ोs = 248;
		rdev->config.rv770.max_stack_entries = 512;
		rdev->config.rv770.max_hw_contexts = 8;
		rdev->config.rv770.max_gs_thपढ़ोs = 16 * 2;
		rdev->config.rv770.sx_max_export_size = 256;
		rdev->config.rv770.sx_max_export_pos_size = 32;
		rdev->config.rv770.sx_max_export_smx_size = 224;
		rdev->config.rv770.sq_num_cf_insts = 2;

		rdev->config.rv770.sx_num_of_sets = 7;
		rdev->config.rv770.sc_prim_fअगरo_size = 0x100;
		rdev->config.rv770.sc_hiz_tile_fअगरo_size = 0x30;
		rdev->config.rv770.sc_earlyz_tile_fअगरo_fize = 0x130;

		अगर (rdev->config.rv770.sx_max_export_pos_size > 16) अणु
			rdev->config.rv770.sx_max_export_pos_size -= 16;
			rdev->config.rv770.sx_max_export_smx_size += 16;
		पूर्ण
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	/* Initialize HDP */
	j = 0;
	क्रम (i = 0; i < 32; i++) अणु
		WREG32((0x2c14 + j), 0x00000000);
		WREG32((0x2c18 + j), 0x00000000);
		WREG32((0x2c1c + j), 0x00000000);
		WREG32((0x2c20 + j), 0x00000000);
		WREG32((0x2c24 + j), 0x00000000);
		j += 0x18;
	पूर्ण

	WREG32(GRBM_CNTL, GRBM_READ_TIMEOUT(0xff));

	/* setup tiling, simd, pipe config */
	mc_arb_ramcfg = RREG32(MC_ARB_RAMCFG);

	shader_pipe_config = RREG32(CC_GC_SHADER_PIPE_CONFIG);
	inactive_pipes = (shader_pipe_config & INACTIVE_QD_PIPES_MASK) >> INACTIVE_QD_PIPES_SHIFT;
	क्रम (i = 0, पंचांगp = 1, active_number = 0; i < R7XX_MAX_PIPES; i++) अणु
		अगर (!(inactive_pipes & पंचांगp)) अणु
			active_number++;
		पूर्ण
		पंचांगp <<= 1;
	पूर्ण
	अगर (active_number == 1) अणु
		WREG32(SPI_CONFIG_CNTL, DISABLE_INTERP_1);
	पूर्ण अन्यथा अणु
		WREG32(SPI_CONFIG_CNTL, 0);
	पूर्ण

	cc_gc_shader_pipe_config = RREG32(CC_GC_SHADER_PIPE_CONFIG) & 0xffffff00;
	पंचांगp = rdev->config.rv770.max_simds -
		r600_count_pipe_bits((cc_gc_shader_pipe_config >> 16) & R7XX_MAX_SIMDS_MASK);
	rdev->config.rv770.active_simds = पंचांगp;

	चयन (rdev->config.rv770.max_tile_pipes) अणु
	हाल 1:
	शेष:
		gb_tiling_config = PIPE_TILING(0);
		अवरोध;
	हाल 2:
		gb_tiling_config = PIPE_TILING(1);
		अवरोध;
	हाल 4:
		gb_tiling_config = PIPE_TILING(2);
		अवरोध;
	हाल 8:
		gb_tiling_config = PIPE_TILING(3);
		अवरोध;
	पूर्ण
	rdev->config.rv770.tiling_npipes = rdev->config.rv770.max_tile_pipes;

	disabled_rb_mask = (RREG32(CC_RB_BACKEND_DISABLE) >> 16) & R7XX_MAX_BACKENDS_MASK;
	पंचांगp = 0;
	क्रम (i = 0; i < rdev->config.rv770.max_backends; i++)
		पंचांगp |= (1 << i);
	/* अगर all the backends are disabled, fix it up here */
	अगर ((disabled_rb_mask & पंचांगp) == पंचांगp) अणु
		क्रम (i = 0; i < rdev->config.rv770.max_backends; i++)
			disabled_rb_mask &= ~(1 << i);
	पूर्ण
	पंचांगp = (gb_tiling_config & PIPE_TILING__MASK) >> PIPE_TILING__SHIFT;
	पंचांगp = r6xx_remap_render_backend(rdev, पंचांगp, rdev->config.rv770.max_backends,
					R7XX_MAX_BACKENDS, disabled_rb_mask);
	gb_tiling_config |= पंचांगp << 16;
	rdev->config.rv770.backend_map = पंचांगp;

	अगर (rdev->family == CHIP_RV770)
		gb_tiling_config |= BANK_TILING(1);
	अन्यथा अणु
		अगर ((mc_arb_ramcfg & NOOFBANK_MASK) >> NOOFBANK_SHIFT)
			gb_tiling_config |= BANK_TILING(1);
		अन्यथा
			gb_tiling_config |= BANK_TILING(0);
	पूर्ण
	rdev->config.rv770.tiling_nbanks = 4 << ((gb_tiling_config >> 4) & 0x3);
	gb_tiling_config |= GROUP_SIZE((mc_arb_ramcfg & BURSTLENGTH_MASK) >> BURSTLENGTH_SHIFT);
	अगर (((mc_arb_ramcfg & NOOFROWS_MASK) >> NOOFROWS_SHIFT) > 3) अणु
		gb_tiling_config |= ROW_TILING(3);
		gb_tiling_config |= SAMPLE_SPLIT(3);
	पूर्ण अन्यथा अणु
		gb_tiling_config |=
			ROW_TILING(((mc_arb_ramcfg & NOOFROWS_MASK) >> NOOFROWS_SHIFT));
		gb_tiling_config |=
			SAMPLE_SPLIT(((mc_arb_ramcfg & NOOFROWS_MASK) >> NOOFROWS_SHIFT));
	पूर्ण

	gb_tiling_config |= BANK_SWAPS(1);
	rdev->config.rv770.tile_config = gb_tiling_config;

	WREG32(GB_TILING_CONFIG, gb_tiling_config);
	WREG32(DCP_TILING_CONFIG, (gb_tiling_config & 0xffff));
	WREG32(HDP_TILING_CONFIG, (gb_tiling_config & 0xffff));
	WREG32(DMA_TILING_CONFIG, (gb_tiling_config & 0xffff));
	WREG32(DMA_TILING_CONFIG2, (gb_tiling_config & 0xffff));
	अगर (rdev->family == CHIP_RV730) अणु
		WREG32(UVD_UDEC_DB_TILING_CONFIG, (gb_tiling_config & 0xffff));
		WREG32(UVD_UDEC_DBW_TILING_CONFIG, (gb_tiling_config & 0xffff));
		WREG32(UVD_UDEC_TILING_CONFIG, (gb_tiling_config & 0xffff));
	पूर्ण

	WREG32(CGTS_SYS_TCC_DISABLE, 0);
	WREG32(CGTS_TCC_DISABLE, 0);
	WREG32(CGTS_USER_SYS_TCC_DISABLE, 0);
	WREG32(CGTS_USER_TCC_DISABLE, 0);


	num_qd_pipes = R7XX_MAX_PIPES - r600_count_pipe_bits((cc_gc_shader_pipe_config & INACTIVE_QD_PIPES_MASK) >> 8);
	WREG32(VGT_OUT_DEALLOC_CNTL, (num_qd_pipes * 4) & DEALLOC_DIST_MASK);
	WREG32(VGT_VERTEX_REUSE_BLOCK_CNTL, ((num_qd_pipes * 4) - 2) & VTX_REUSE_DEPTH_MASK);

	/* set HW शेषs क्रम 3D engine */
	WREG32(CP_QUEUE_THRESHOLDS, (ROQ_IB1_START(0x16) |
				     ROQ_IB2_START(0x2b)));

	WREG32(CP_MEQ_THRESHOLDS, STQ_SPLIT(0x30));

	ta_aux_cntl = RREG32(TA_CNTL_AUX);
	WREG32(TA_CNTL_AUX, ta_aux_cntl | DISABLE_CUBE_ANISO);

	sx_debug_1 = RREG32(SX_DEBUG_1);
	sx_debug_1 |= ENABLE_NEW_SMX_ADDRESS;
	WREG32(SX_DEBUG_1, sx_debug_1);

	smx_dc_ctl0 = RREG32(SMX_DC_CTL0);
	smx_dc_ctl0 &= ~CACHE_DEPTH(0x1ff);
	smx_dc_ctl0 |= CACHE_DEPTH((rdev->config.rv770.sx_num_of_sets * 64) - 1);
	WREG32(SMX_DC_CTL0, smx_dc_ctl0);

	अगर (rdev->family != CHIP_RV740)
		WREG32(SMX_EVENT_CTL, (ES_FLUSH_CTL(4) |
				       GS_FLUSH_CTL(4) |
				       ACK_FLUSH_CTL(3) |
				       SYNC_FLUSH_CTL));

	अगर (rdev->family != CHIP_RV770)
		WREG32(SMX_SAR_CTL0, 0x00003f3f);

	db_debug3 = RREG32(DB_DEBUG3);
	db_debug3 &= ~DB_CLK_OFF_DELAY(0x1f);
	चयन (rdev->family) अणु
	हाल CHIP_RV770:
	हाल CHIP_RV740:
		db_debug3 |= DB_CLK_OFF_DELAY(0x1f);
		अवरोध;
	हाल CHIP_RV710:
	हाल CHIP_RV730:
	शेष:
		db_debug3 |= DB_CLK_OFF_DELAY(2);
		अवरोध;
	पूर्ण
	WREG32(DB_DEBUG3, db_debug3);

	अगर (rdev->family != CHIP_RV770) अणु
		db_debug4 = RREG32(DB_DEBUG4);
		db_debug4 |= DISABLE_TILE_COVERED_FOR_PS_ITER;
		WREG32(DB_DEBUG4, db_debug4);
	पूर्ण

	WREG32(SX_EXPORT_BUFFER_SIZES, (COLOR_BUFFER_SIZE((rdev->config.rv770.sx_max_export_size / 4) - 1) |
					POSITION_BUFFER_SIZE((rdev->config.rv770.sx_max_export_pos_size / 4) - 1) |
					SMX_BUFFER_SIZE((rdev->config.rv770.sx_max_export_smx_size / 4) - 1)));

	WREG32(PA_SC_FIFO_SIZE, (SC_PRIM_FIFO_SIZE(rdev->config.rv770.sc_prim_fअगरo_size) |
				 SC_HIZ_TILE_FIFO_SIZE(rdev->config.rv770.sc_hiz_tile_fअगरo_size) |
				 SC_EARLYZ_TILE_FIFO_SIZE(rdev->config.rv770.sc_earlyz_tile_fअगरo_fize)));

	WREG32(PA_SC_MULTI_CHIP_CNTL, 0);

	WREG32(VGT_NUM_INSTANCES, 1);

	WREG32(SPI_CONFIG_CNTL_1, VTX_DONE_DELAY(4));

	WREG32(CP_PERFMON_CNTL, 0);

	sq_ms_fअगरo_sizes = (CACHE_FIFO_SIZE(16 * rdev->config.rv770.sq_num_cf_insts) |
			    DONE_FIFO_HIWATER(0xe0) |
			    ALU_UPDATE_FIFO_HIWATER(0x8));
	चयन (rdev->family) अणु
	हाल CHIP_RV770:
	हाल CHIP_RV730:
	हाल CHIP_RV710:
		sq_ms_fअगरo_sizes |= FETCH_FIFO_HIWATER(0x1);
		अवरोध;
	हाल CHIP_RV740:
	शेष:
		sq_ms_fअगरo_sizes |= FETCH_FIFO_HIWATER(0x4);
		अवरोध;
	पूर्ण
	WREG32(SQ_MS_FIFO_SIZES, sq_ms_fअगरo_sizes);

	/* SQ_CONFIG, SQ_GPR_RESOURCE_MGMT, SQ_THREAD_RESOURCE_MGMT, SQ_STACK_RESOURCE_MGMT
	 * should be adjusted as needed by the 2D/3D drivers.  This just sets शेष values
	 */
	sq_config = RREG32(SQ_CONFIG);
	sq_config &= ~(PS_PRIO(3) |
		       VS_PRIO(3) |
		       GS_PRIO(3) |
		       ES_PRIO(3));
	sq_config |= (DX9_CONSTS |
		      VC_ENABLE |
		      EXPORT_SRC_C |
		      PS_PRIO(0) |
		      VS_PRIO(1) |
		      GS_PRIO(2) |
		      ES_PRIO(3));
	अगर (rdev->family == CHIP_RV710)
		/* no vertex cache */
		sq_config &= ~VC_ENABLE;

	WREG32(SQ_CONFIG, sq_config);

	WREG32(SQ_GPR_RESOURCE_MGMT_1,  (NUM_PS_GPRS((rdev->config.rv770.max_gprs * 24)/64) |
					 NUM_VS_GPRS((rdev->config.rv770.max_gprs * 24)/64) |
					 NUM_CLAUSE_TEMP_GPRS(((rdev->config.rv770.max_gprs * 24)/64)/2)));

	WREG32(SQ_GPR_RESOURCE_MGMT_2,  (NUM_GS_GPRS((rdev->config.rv770.max_gprs * 7)/64) |
					 NUM_ES_GPRS((rdev->config.rv770.max_gprs * 7)/64)));

	sq_thपढ़ो_resource_mgmt = (NUM_PS_THREADS((rdev->config.rv770.max_thपढ़ोs * 4)/8) |
				   NUM_VS_THREADS((rdev->config.rv770.max_thपढ़ोs * 2)/8) |
				   NUM_ES_THREADS((rdev->config.rv770.max_thपढ़ोs * 1)/8));
	अगर (((rdev->config.rv770.max_thपढ़ोs * 1) / 8) > rdev->config.rv770.max_gs_thपढ़ोs)
		sq_thपढ़ो_resource_mgmt |= NUM_GS_THREADS(rdev->config.rv770.max_gs_thपढ़ोs);
	अन्यथा
		sq_thपढ़ो_resource_mgmt |= NUM_GS_THREADS((rdev->config.rv770.max_gs_thपढ़ोs * 1)/8);
	WREG32(SQ_THREAD_RESOURCE_MGMT, sq_thपढ़ो_resource_mgmt);

	WREG32(SQ_STACK_RESOURCE_MGMT_1, (NUM_PS_STACK_ENTRIES((rdev->config.rv770.max_stack_entries * 1)/4) |
						     NUM_VS_STACK_ENTRIES((rdev->config.rv770.max_stack_entries * 1)/4)));

	WREG32(SQ_STACK_RESOURCE_MGMT_2, (NUM_GS_STACK_ENTRIES((rdev->config.rv770.max_stack_entries * 1)/4) |
						     NUM_ES_STACK_ENTRIES((rdev->config.rv770.max_stack_entries * 1)/4)));

	sq_dyn_gpr_size_simd_ab_0 = (SIMDA_RING0((rdev->config.rv770.max_gprs * 38)/64) |
				     SIMDA_RING1((rdev->config.rv770.max_gprs * 38)/64) |
				     SIMDB_RING0((rdev->config.rv770.max_gprs * 38)/64) |
				     SIMDB_RING1((rdev->config.rv770.max_gprs * 38)/64));

	WREG32(SQ_DYN_GPR_SIZE_SIMD_AB_0, sq_dyn_gpr_size_simd_ab_0);
	WREG32(SQ_DYN_GPR_SIZE_SIMD_AB_1, sq_dyn_gpr_size_simd_ab_0);
	WREG32(SQ_DYN_GPR_SIZE_SIMD_AB_2, sq_dyn_gpr_size_simd_ab_0);
	WREG32(SQ_DYN_GPR_SIZE_SIMD_AB_3, sq_dyn_gpr_size_simd_ab_0);
	WREG32(SQ_DYN_GPR_SIZE_SIMD_AB_4, sq_dyn_gpr_size_simd_ab_0);
	WREG32(SQ_DYN_GPR_SIZE_SIMD_AB_5, sq_dyn_gpr_size_simd_ab_0);
	WREG32(SQ_DYN_GPR_SIZE_SIMD_AB_6, sq_dyn_gpr_size_simd_ab_0);
	WREG32(SQ_DYN_GPR_SIZE_SIMD_AB_7, sq_dyn_gpr_size_simd_ab_0);

	WREG32(PA_SC_FORCE_EOV_MAX_CNTS, (FORCE_EOV_MAX_CLK_CNT(4095) |
					  FORCE_EOV_MAX_REZ_CNT(255)));

	अगर (rdev->family == CHIP_RV710)
		WREG32(VGT_CACHE_INVALIDATION, (CACHE_INVALIDATION(TC_ONLY) |
						AUTO_INVLD_EN(ES_AND_GS_AUTO)));
	अन्यथा
		WREG32(VGT_CACHE_INVALIDATION, (CACHE_INVALIDATION(VC_AND_TC) |
						AUTO_INVLD_EN(ES_AND_GS_AUTO)));

	चयन (rdev->family) अणु
	हाल CHIP_RV770:
	हाल CHIP_RV730:
	हाल CHIP_RV740:
		gs_prim_buffer_depth = 384;
		अवरोध;
	हाल CHIP_RV710:
		gs_prim_buffer_depth = 128;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	num_gs_verts_per_thपढ़ो = rdev->config.rv770.max_pipes * 16;
	vgt_gs_per_es = gs_prim_buffer_depth + num_gs_verts_per_thपढ़ो;
	/* Max value क्रम this is 256 */
	अगर (vgt_gs_per_es > 256)
		vgt_gs_per_es = 256;

	WREG32(VGT_ES_PER_GS, 128);
	WREG32(VGT_GS_PER_ES, vgt_gs_per_es);
	WREG32(VGT_GS_PER_VS, 2);

	/* more शेष values. 2D/3D driver should adjust as needed */
	WREG32(VGT_GS_VERTEX_REUSE, 16);
	WREG32(PA_SC_LINE_STIPPLE_STATE, 0);
	WREG32(VGT_STRMOUT_EN, 0);
	WREG32(SX_MISC, 0);
	WREG32(PA_SC_MODE_CNTL, 0);
	WREG32(PA_SC_EDGERULE, 0xaaaaaaaa);
	WREG32(PA_SC_AA_CONFIG, 0);
	WREG32(PA_SC_CLIPRECT_RULE, 0xffff);
	WREG32(PA_SC_LINE_STIPPLE, 0);
	WREG32(SPI_INPUT_Z, 0);
	WREG32(SPI_PS_IN_CONTROL_0, NUM_INTERP(2));
	WREG32(CB_COLOR7_FRAG, 0);

	/* clear render buffer base addresses */
	WREG32(CB_COLOR0_BASE, 0);
	WREG32(CB_COLOR1_BASE, 0);
	WREG32(CB_COLOR2_BASE, 0);
	WREG32(CB_COLOR3_BASE, 0);
	WREG32(CB_COLOR4_BASE, 0);
	WREG32(CB_COLOR5_BASE, 0);
	WREG32(CB_COLOR6_BASE, 0);
	WREG32(CB_COLOR7_BASE, 0);

	WREG32(TCP_CNTL, 0);

	hdp_host_path_cntl = RREG32(HDP_HOST_PATH_CNTL);
	WREG32(HDP_HOST_PATH_CNTL, hdp_host_path_cntl);

	WREG32(PA_SC_MULTI_CHIP_CNTL, 0);

	WREG32(PA_CL_ENHANCE, (CLIP_VTX_REORDER_ENA |
					  NUM_CLIP_SEQ(3)));
	WREG32(VC_ENHANCE, 0);
पूर्ण

व्योम r700_vram_gtt_location(काष्ठा radeon_device *rdev, काष्ठा radeon_mc *mc)
अणु
	u64 size_bf, size_af;

	अगर (mc->mc_vram_size > 0xE0000000) अणु
		/* leave room क्रम at least 512M GTT */
		dev_warn(rdev->dev, "limiting VRAM\n");
		mc->real_vram_size = 0xE0000000;
		mc->mc_vram_size = 0xE0000000;
	पूर्ण
	अगर (rdev->flags & RADEON_IS_AGP) अणु
		size_bf = mc->gtt_start;
		size_af = mc->mc_mask - mc->gtt_end;
		अगर (size_bf > size_af) अणु
			अगर (mc->mc_vram_size > size_bf) अणु
				dev_warn(rdev->dev, "limiting VRAM\n");
				mc->real_vram_size = size_bf;
				mc->mc_vram_size = size_bf;
			पूर्ण
			mc->vram_start = mc->gtt_start - mc->mc_vram_size;
		पूर्ण अन्यथा अणु
			अगर (mc->mc_vram_size > size_af) अणु
				dev_warn(rdev->dev, "limiting VRAM\n");
				mc->real_vram_size = size_af;
				mc->mc_vram_size = size_af;
			पूर्ण
			mc->vram_start = mc->gtt_end + 1;
		पूर्ण
		mc->vram_end = mc->vram_start + mc->mc_vram_size - 1;
		dev_info(rdev->dev, "VRAM: %lluM 0x%08llX - 0x%08llX (%lluM used)\n",
				mc->mc_vram_size >> 20, mc->vram_start,
				mc->vram_end, mc->real_vram_size >> 20);
	पूर्ण अन्यथा अणु
		radeon_vram_location(rdev, &rdev->mc, 0);
		rdev->mc.gtt_base_align = 0;
		radeon_gtt_location(rdev, mc);
	पूर्ण
पूर्ण

अटल पूर्णांक rv770_mc_init(काष्ठा radeon_device *rdev)
अणु
	u32 पंचांगp;
	पूर्णांक chansize, numchan;

	/* Get VRAM inक्रमmations */
	rdev->mc.vram_is_ddr = true;
	पंचांगp = RREG32(MC_ARB_RAMCFG);
	अगर (पंचांगp & CHANSIZE_OVERRIDE) अणु
		chansize = 16;
	पूर्ण अन्यथा अगर (पंचांगp & CHANSIZE_MASK) अणु
		chansize = 64;
	पूर्ण अन्यथा अणु
		chansize = 32;
	पूर्ण
	पंचांगp = RREG32(MC_SHARED_CHMAP);
	चयन ((पंचांगp & NOOFCHAN_MASK) >> NOOFCHAN_SHIFT) अणु
	हाल 0:
	शेष:
		numchan = 1;
		अवरोध;
	हाल 1:
		numchan = 2;
		अवरोध;
	हाल 2:
		numchan = 4;
		अवरोध;
	हाल 3:
		numchan = 8;
		अवरोध;
	पूर्ण
	rdev->mc.vram_width = numchan * chansize;
	/* Could aper size report 0 ? */
	rdev->mc.aper_base = pci_resource_start(rdev->pdev, 0);
	rdev->mc.aper_size = pci_resource_len(rdev->pdev, 0);
	/* Setup GPU memory space */
	rdev->mc.mc_vram_size = RREG32(CONFIG_MEMSIZE);
	rdev->mc.real_vram_size = RREG32(CONFIG_MEMSIZE);
	rdev->mc.visible_vram_size = rdev->mc.aper_size;
	r700_vram_gtt_location(rdev, &rdev->mc);
	radeon_update_bandwidth_info(rdev);

	वापस 0;
पूर्ण

अटल व्योम rv770_uvd_init(काष्ठा radeon_device *rdev)
अणु
	पूर्णांक r;

	अगर (!rdev->has_uvd)
		वापस;

	r = radeon_uvd_init(rdev);
	अगर (r) अणु
		dev_err(rdev->dev, "failed UVD (%d) init.\n", r);
		/*
		 * At this poपूर्णांक rdev->uvd.vcpu_bo is शून्य which trickles करोwn
		 * to early fails uvd_v2_2_resume() and thus nothing happens
		 * there. So it is poपूर्णांकless to try to go through that code
		 * hence why we disable uvd here.
		 */
		rdev->has_uvd = false;
		वापस;
	पूर्ण
	rdev->ring[R600_RING_TYPE_UVD_INDEX].ring_obj = शून्य;
	r600_ring_init(rdev, &rdev->ring[R600_RING_TYPE_UVD_INDEX], 4096);
पूर्ण

अटल व्योम rv770_uvd_start(काष्ठा radeon_device *rdev)
अणु
	पूर्णांक r;

	अगर (!rdev->has_uvd)
		वापस;

	r = uvd_v2_2_resume(rdev);
	अगर (r) अणु
		dev_err(rdev->dev, "failed UVD resume (%d).\n", r);
		जाओ error;
	पूर्ण
	r = radeon_fence_driver_start_ring(rdev, R600_RING_TYPE_UVD_INDEX);
	अगर (r) अणु
		dev_err(rdev->dev, "failed initializing UVD fences (%d).\n", r);
		जाओ error;
	पूर्ण
	वापस;

error:
	rdev->ring[R600_RING_TYPE_UVD_INDEX].ring_size = 0;
पूर्ण

अटल व्योम rv770_uvd_resume(काष्ठा radeon_device *rdev)
अणु
	काष्ठा radeon_ring *ring;
	पूर्णांक r;

	अगर (!rdev->has_uvd || !rdev->ring[R600_RING_TYPE_UVD_INDEX].ring_size)
		वापस;

	ring = &rdev->ring[R600_RING_TYPE_UVD_INDEX];
	r = radeon_ring_init(rdev, ring, ring->ring_size, 0, PACKET0(UVD_NO_OP, 0));
	अगर (r) अणु
		dev_err(rdev->dev, "failed initializing UVD ring (%d).\n", r);
		वापस;
	पूर्ण
	r = uvd_v1_0_init(rdev);
	अगर (r) अणु
		dev_err(rdev->dev, "failed initializing UVD (%d).\n", r);
		वापस;
	पूर्ण
पूर्ण

अटल पूर्णांक rv770_startup(काष्ठा radeon_device *rdev)
अणु
	काष्ठा radeon_ring *ring;
	पूर्णांक r;

	/* enable pcie gen2 link */
	rv770_pcie_gen2_enable(rdev);

	/* scratch needs to be initialized beक्रमe MC */
	r = r600_vram_scratch_init(rdev);
	अगर (r)
		वापस r;

	rv770_mc_program(rdev);

	अगर (rdev->flags & RADEON_IS_AGP) अणु
		rv770_agp_enable(rdev);
	पूर्ण अन्यथा अणु
		r = rv770_pcie_gart_enable(rdev);
		अगर (r)
			वापस r;
	पूर्ण

	rv770_gpu_init(rdev);

	/* allocate wb buffer */
	r = radeon_wb_init(rdev);
	अगर (r)
		वापस r;

	r = radeon_fence_driver_start_ring(rdev, RADEON_RING_TYPE_GFX_INDEX);
	अगर (r) अणु
		dev_err(rdev->dev, "failed initializing CP fences (%d).\n", r);
		वापस r;
	पूर्ण

	r = radeon_fence_driver_start_ring(rdev, R600_RING_TYPE_DMA_INDEX);
	अगर (r) अणु
		dev_err(rdev->dev, "failed initializing DMA fences (%d).\n", r);
		वापस r;
	पूर्ण

	rv770_uvd_start(rdev);

	/* Enable IRQ */
	अगर (!rdev->irq.installed) अणु
		r = radeon_irq_kms_init(rdev);
		अगर (r)
			वापस r;
	पूर्ण

	r = r600_irq_init(rdev);
	अगर (r) अणु
		DRM_ERROR("radeon: IH init failed (%d).\n", r);
		radeon_irq_kms_fini(rdev);
		वापस r;
	पूर्ण
	r600_irq_set(rdev);

	ring = &rdev->ring[RADEON_RING_TYPE_GFX_INDEX];
	r = radeon_ring_init(rdev, ring, ring->ring_size, RADEON_WB_CP_RPTR_OFFSET,
			     RADEON_CP_PACKET2);
	अगर (r)
		वापस r;

	ring = &rdev->ring[R600_RING_TYPE_DMA_INDEX];
	r = radeon_ring_init(rdev, ring, ring->ring_size, R600_WB_DMA_RPTR_OFFSET,
			     DMA_PACKET(DMA_PACKET_NOP, 0, 0, 0));
	अगर (r)
		वापस r;

	r = rv770_cp_load_microcode(rdev);
	अगर (r)
		वापस r;
	r = r600_cp_resume(rdev);
	अगर (r)
		वापस r;

	r = r600_dma_resume(rdev);
	अगर (r)
		वापस r;

	rv770_uvd_resume(rdev);

	r = radeon_ib_pool_init(rdev);
	अगर (r) अणु
		dev_err(rdev->dev, "IB initialization failed (%d).\n", r);
		वापस r;
	पूर्ण

	r = radeon_audio_init(rdev);
	अगर (r) अणु
		DRM_ERROR("radeon: audio init failed\n");
		वापस r;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक rv770_resume(काष्ठा radeon_device *rdev)
अणु
	पूर्णांक r;

	/* Do not reset GPU beक्रमe posting, on rv770 hw unlike on r500 hw,
	 * posting will perक्रमm necessary task to bring back GPU पूर्णांकo good
	 * shape.
	 */
	/* post card */
	atom_asic_init(rdev->mode_info.atom_context);

	/* init golden रेजिस्टरs */
	rv770_init_golden_रेजिस्टरs(rdev);

	अगर (rdev->pm.pm_method == PM_METHOD_DPM)
		radeon_pm_resume(rdev);

	rdev->accel_working = true;
	r = rv770_startup(rdev);
	अगर (r) अणु
		DRM_ERROR("r600 startup failed on resume\n");
		rdev->accel_working = false;
		वापस r;
	पूर्ण

	वापस r;

पूर्ण

पूर्णांक rv770_suspend(काष्ठा radeon_device *rdev)
अणु
	radeon_pm_suspend(rdev);
	radeon_audio_fini(rdev);
	अगर (rdev->has_uvd) अणु
		uvd_v1_0_fini(rdev);
		radeon_uvd_suspend(rdev);
	पूर्ण
	r700_cp_stop(rdev);
	r600_dma_stop(rdev);
	r600_irq_suspend(rdev);
	radeon_wb_disable(rdev);
	rv770_pcie_gart_disable(rdev);

	वापस 0;
पूर्ण

/* Plan is to move initialization in that function and use
 * helper function so that radeon_device_init pretty much
 * करो nothing more than calling asic specअगरic function. This
 * should also allow to हटाओ a bunch of callback function
 * like vram_info.
 */
पूर्णांक rv770_init(काष्ठा radeon_device *rdev)
अणु
	पूर्णांक r;

	/* Read BIOS */
	अगर (!radeon_get_bios(rdev)) अणु
		अगर (ASIC_IS_AVIVO(rdev))
			वापस -EINVAL;
	पूर्ण
	/* Must be an ATOMBIOS */
	अगर (!rdev->is_atom_bios) अणु
		dev_err(rdev->dev, "Expecting atombios for R600 GPU\n");
		वापस -EINVAL;
	पूर्ण
	r = radeon_atombios_init(rdev);
	अगर (r)
		वापस r;
	/* Post card अगर necessary */
	अगर (!radeon_card_posted(rdev)) अणु
		अगर (!rdev->bios) अणु
			dev_err(rdev->dev, "Card not posted and no BIOS - ignoring\n");
			वापस -EINVAL;
		पूर्ण
		DRM_INFO("GPU not posted. posting now...\n");
		atom_asic_init(rdev->mode_info.atom_context);
	पूर्ण
	/* init golden रेजिस्टरs */
	rv770_init_golden_रेजिस्टरs(rdev);
	/* Initialize scratch रेजिस्टरs */
	r600_scratch_init(rdev);
	/* Initialize surface रेजिस्टरs */
	radeon_surface_init(rdev);
	/* Initialize घड़ीs */
	radeon_get_घड़ी_info(rdev->ddev);
	/* Fence driver */
	r = radeon_fence_driver_init(rdev);
	अगर (r)
		वापस r;
	/* initialize AGP */
	अगर (rdev->flags & RADEON_IS_AGP) अणु
		r = radeon_agp_init(rdev);
		अगर (r)
			radeon_agp_disable(rdev);
	पूर्ण
	r = rv770_mc_init(rdev);
	अगर (r)
		वापस r;
	/* Memory manager */
	r = radeon_bo_init(rdev);
	अगर (r)
		वापस r;

	अगर (!rdev->me_fw || !rdev->pfp_fw || !rdev->rlc_fw) अणु
		r = r600_init_microcode(rdev);
		अगर (r) अणु
			DRM_ERROR("Failed to load firmware!\n");
			वापस r;
		पूर्ण
	पूर्ण

	/* Initialize घातer management */
	radeon_pm_init(rdev);

	rdev->ring[RADEON_RING_TYPE_GFX_INDEX].ring_obj = शून्य;
	r600_ring_init(rdev, &rdev->ring[RADEON_RING_TYPE_GFX_INDEX], 1024 * 1024);

	rdev->ring[R600_RING_TYPE_DMA_INDEX].ring_obj = शून्य;
	r600_ring_init(rdev, &rdev->ring[R600_RING_TYPE_DMA_INDEX], 64 * 1024);

	rv770_uvd_init(rdev);

	rdev->ih.ring_obj = शून्य;
	r600_ih_ring_init(rdev, 64 * 1024);

	r = r600_pcie_gart_init(rdev);
	अगर (r)
		वापस r;

	rdev->accel_working = true;
	r = rv770_startup(rdev);
	अगर (r) अणु
		dev_err(rdev->dev, "disabling GPU acceleration\n");
		r700_cp_fini(rdev);
		r600_dma_fini(rdev);
		r600_irq_fini(rdev);
		radeon_wb_fini(rdev);
		radeon_ib_pool_fini(rdev);
		radeon_irq_kms_fini(rdev);
		rv770_pcie_gart_fini(rdev);
		rdev->accel_working = false;
	पूर्ण

	वापस 0;
पूर्ण

व्योम rv770_fini(काष्ठा radeon_device *rdev)
अणु
	radeon_pm_fini(rdev);
	r700_cp_fini(rdev);
	r600_dma_fini(rdev);
	r600_irq_fini(rdev);
	radeon_wb_fini(rdev);
	radeon_ib_pool_fini(rdev);
	radeon_irq_kms_fini(rdev);
	uvd_v1_0_fini(rdev);
	radeon_uvd_fini(rdev);
	rv770_pcie_gart_fini(rdev);
	r600_vram_scratch_fini(rdev);
	radeon_gem_fini(rdev);
	radeon_fence_driver_fini(rdev);
	radeon_agp_fini(rdev);
	radeon_bo_fini(rdev);
	radeon_atombios_fini(rdev);
	kमुक्त(rdev->bios);
	rdev->bios = शून्य;
पूर्ण

अटल व्योम rv770_pcie_gen2_enable(काष्ठा radeon_device *rdev)
अणु
	u32 link_width_cntl, lanes, speed_cntl, पंचांगp;
	u16 link_cntl2;

	अगर (radeon_pcie_gen2 == 0)
		वापस;

	अगर (rdev->flags & RADEON_IS_IGP)
		वापस;

	अगर (!(rdev->flags & RADEON_IS_PCIE))
		वापस;

	/* x2 cards have a special sequence */
	अगर (ASIC_IS_X2(rdev))
		वापस;

	अगर ((rdev->pdev->bus->max_bus_speed != PCIE_SPEED_5_0GT) &&
		(rdev->pdev->bus->max_bus_speed != PCIE_SPEED_8_0GT))
		वापस;

	DRM_INFO("enabling PCIE gen 2 link speeds, disable with radeon.pcie_gen2=0\n");

	/* advertise upconfig capability */
	link_width_cntl = RREG32_PCIE_PORT(PCIE_LC_LINK_WIDTH_CNTL);
	link_width_cntl &= ~LC_UPCONFIGURE_DIS;
	WREG32_PCIE_PORT(PCIE_LC_LINK_WIDTH_CNTL, link_width_cntl);
	link_width_cntl = RREG32_PCIE_PORT(PCIE_LC_LINK_WIDTH_CNTL);
	अगर (link_width_cntl & LC_RENEGOTIATION_SUPPORT) अणु
		lanes = (link_width_cntl & LC_LINK_WIDTH_RD_MASK) >> LC_LINK_WIDTH_RD_SHIFT;
		link_width_cntl &= ~(LC_LINK_WIDTH_MASK |
				     LC_RECONFIG_ARC_MISSING_ESCAPE);
		link_width_cntl |= lanes | LC_RECONFIG_NOW |
			LC_RENEGOTIATE_EN | LC_UPCONFIGURE_SUPPORT;
		WREG32_PCIE_PORT(PCIE_LC_LINK_WIDTH_CNTL, link_width_cntl);
	पूर्ण अन्यथा अणु
		link_width_cntl |= LC_UPCONFIGURE_DIS;
		WREG32_PCIE_PORT(PCIE_LC_LINK_WIDTH_CNTL, link_width_cntl);
	पूर्ण

	speed_cntl = RREG32_PCIE_PORT(PCIE_LC_SPEED_CNTL);
	अगर ((speed_cntl & LC_OTHER_SIDE_EVER_SENT_GEN2) &&
	    (speed_cntl & LC_OTHER_SIDE_SUPPORTS_GEN2)) अणु

		पंचांगp = RREG32(0x541c);
		WREG32(0x541c, पंचांगp | 0x8);
		WREG32(MM_CFGREGS_CNTL, MM_WR_TO_CFG_EN);
		link_cntl2 = RREG16(0x4088);
		link_cntl2 &= ~TARGET_LINK_SPEED_MASK;
		link_cntl2 |= 0x2;
		WREG16(0x4088, link_cntl2);
		WREG32(MM_CFGREGS_CNTL, 0);

		speed_cntl = RREG32_PCIE_PORT(PCIE_LC_SPEED_CNTL);
		speed_cntl &= ~LC_TARGET_LINK_SPEED_OVERRIDE_EN;
		WREG32_PCIE_PORT(PCIE_LC_SPEED_CNTL, speed_cntl);

		speed_cntl = RREG32_PCIE_PORT(PCIE_LC_SPEED_CNTL);
		speed_cntl |= LC_CLR_FAILED_SPD_CHANGE_CNT;
		WREG32_PCIE_PORT(PCIE_LC_SPEED_CNTL, speed_cntl);

		speed_cntl = RREG32_PCIE_PORT(PCIE_LC_SPEED_CNTL);
		speed_cntl &= ~LC_CLR_FAILED_SPD_CHANGE_CNT;
		WREG32_PCIE_PORT(PCIE_LC_SPEED_CNTL, speed_cntl);

		speed_cntl = RREG32_PCIE_PORT(PCIE_LC_SPEED_CNTL);
		speed_cntl |= LC_GEN2_EN_STRAP;
		WREG32_PCIE_PORT(PCIE_LC_SPEED_CNTL, speed_cntl);

	पूर्ण अन्यथा अणु
		link_width_cntl = RREG32_PCIE_PORT(PCIE_LC_LINK_WIDTH_CNTL);
		/* XXX: only disable it अगर gen1 bridge venकरोr == 0x111d or 0x1106 */
		अगर (1)
			link_width_cntl |= LC_UPCONFIGURE_DIS;
		अन्यथा
			link_width_cntl &= ~LC_UPCONFIGURE_DIS;
		WREG32_PCIE_PORT(PCIE_LC_LINK_WIDTH_CNTL, link_width_cntl);
	पूर्ण
पूर्ण
