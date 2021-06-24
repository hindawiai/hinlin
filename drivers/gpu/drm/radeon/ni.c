<शैली गुरु>
/*
 * Copyright 2010 Advanced Micro Devices, Inc.
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
 * Authors: Alex Deucher
 */

#समावेश <linux/firmware.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/slab.h>

#समावेश <drm/radeon_drm.h>

#समावेश "atom.h"
#समावेश "cayman_blit_shaders.h"
#समावेश "clearstate_cayman.h"
#समावेश "evergreen.h"
#समावेश "ni.h"
#समावेश "ni_reg.h"
#समावेश "nid.h"
#समावेश "radeon.h"
#समावेश "radeon_asic.h"
#समावेश "radeon_audio.h"
#समावेश "radeon_ucode.h"

/*
 * Indirect रेजिस्टरs accessor
 */
u32 tn_smc_rreg(काष्ठा radeon_device *rdev, u32 reg)
अणु
	अचिन्हित दीर्घ flags;
	u32 r;

	spin_lock_irqsave(&rdev->smc_idx_lock, flags);
	WREG32(TN_SMC_IND_INDEX_0, (reg));
	r = RREG32(TN_SMC_IND_DATA_0);
	spin_unlock_irqrestore(&rdev->smc_idx_lock, flags);
	वापस r;
पूर्ण

व्योम tn_smc_wreg(काष्ठा radeon_device *rdev, u32 reg, u32 v)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&rdev->smc_idx_lock, flags);
	WREG32(TN_SMC_IND_INDEX_0, (reg));
	WREG32(TN_SMC_IND_DATA_0, (v));
	spin_unlock_irqrestore(&rdev->smc_idx_lock, flags);
पूर्ण

अटल स्थिर u32 tn_rlc_save_restore_रेजिस्टर_list[] =
अणु
	0x98fc,
	0x98f0,
	0x9834,
	0x9838,
	0x9870,
	0x9874,
	0x8a14,
	0x8b24,
	0x8bcc,
	0x8b10,
	0x8c30,
	0x8d00,
	0x8d04,
	0x8c00,
	0x8c04,
	0x8c10,
	0x8c14,
	0x8d8c,
	0x8cf0,
	0x8e38,
	0x9508,
	0x9688,
	0x9608,
	0x960c,
	0x9610,
	0x9614,
	0x88c4,
	0x8978,
	0x88d4,
	0x900c,
	0x9100,
	0x913c,
	0x90e8,
	0x9354,
	0xa008,
	0x98f8,
	0x9148,
	0x914c,
	0x3f94,
	0x98f4,
	0x9b7c,
	0x3f8c,
	0x8950,
	0x8954,
	0x8a18,
	0x8b28,
	0x9144,
	0x3f90,
	0x915c,
	0x9160,
	0x9178,
	0x917c,
	0x9180,
	0x918c,
	0x9190,
	0x9194,
	0x9198,
	0x919c,
	0x91a8,
	0x91ac,
	0x91b0,
	0x91b4,
	0x91b8,
	0x91c4,
	0x91c8,
	0x91cc,
	0x91d0,
	0x91d4,
	0x91e0,
	0x91e4,
	0x91ec,
	0x91f0,
	0x91f4,
	0x9200,
	0x9204,
	0x929c,
	0x8030,
	0x9150,
	0x9a60,
	0x920c,
	0x9210,
	0x9228,
	0x922c,
	0x9244,
	0x9248,
	0x91e8,
	0x9294,
	0x9208,
	0x9224,
	0x9240,
	0x9220,
	0x923c,
	0x9258,
	0x9744,
	0xa200,
	0xa204,
	0xa208,
	0xa20c,
	0x8d58,
	0x9030,
	0x9034,
	0x9038,
	0x903c,
	0x9040,
	0x9654,
	0x897c,
	0xa210,
	0xa214,
	0x9868,
	0xa02c,
	0x9664,
	0x9698,
	0x949c,
	0x8e10,
	0x8e18,
	0x8c50,
	0x8c58,
	0x8c60,
	0x8c68,
	0x89b4,
	0x9830,
	0x802c,
पूर्ण;

/* Firmware Names */
MODULE_FIRMWARE("radeon/BARTS_pfp.bin");
MODULE_FIRMWARE("radeon/BARTS_me.bin");
MODULE_FIRMWARE("radeon/BARTS_mc.bin");
MODULE_FIRMWARE("radeon/BARTS_smc.bin");
MODULE_FIRMWARE("radeon/BTC_rlc.bin");
MODULE_FIRMWARE("radeon/TURKS_pfp.bin");
MODULE_FIRMWARE("radeon/TURKS_me.bin");
MODULE_FIRMWARE("radeon/TURKS_mc.bin");
MODULE_FIRMWARE("radeon/TURKS_smc.bin");
MODULE_FIRMWARE("radeon/CAICOS_pfp.bin");
MODULE_FIRMWARE("radeon/CAICOS_me.bin");
MODULE_FIRMWARE("radeon/CAICOS_mc.bin");
MODULE_FIRMWARE("radeon/CAICOS_smc.bin");
MODULE_FIRMWARE("radeon/CAYMAN_pfp.bin");
MODULE_FIRMWARE("radeon/CAYMAN_me.bin");
MODULE_FIRMWARE("radeon/CAYMAN_mc.bin");
MODULE_FIRMWARE("radeon/CAYMAN_rlc.bin");
MODULE_FIRMWARE("radeon/CAYMAN_smc.bin");
MODULE_FIRMWARE("radeon/ARUBA_pfp.bin");
MODULE_FIRMWARE("radeon/ARUBA_me.bin");
MODULE_FIRMWARE("radeon/ARUBA_rlc.bin");


अटल स्थिर u32 cayman_golden_रेजिस्टरs2[] =
अणु
	0x3e5c, 0xffffffff, 0x00000000,
	0x3e48, 0xffffffff, 0x00000000,
	0x3e4c, 0xffffffff, 0x00000000,
	0x3e64, 0xffffffff, 0x00000000,
	0x3e50, 0xffffffff, 0x00000000,
	0x3e60, 0xffffffff, 0x00000000
पूर्ण;

अटल स्थिर u32 cayman_golden_रेजिस्टरs[] =
अणु
	0x5eb4, 0xffffffff, 0x00000002,
	0x5e78, 0x8f311ff1, 0x001000f0,
	0x3f90, 0xffff0000, 0xff000000,
	0x9148, 0xffff0000, 0xff000000,
	0x3f94, 0xffff0000, 0xff000000,
	0x914c, 0xffff0000, 0xff000000,
	0xc78, 0x00000080, 0x00000080,
	0xbd4, 0x70073777, 0x00011003,
	0xd02c, 0xbfffff1f, 0x08421000,
	0xd0b8, 0x73773777, 0x02011003,
	0x5bc0, 0x00200000, 0x50100000,
	0x98f8, 0x33773777, 0x02011003,
	0x98fc, 0xffffffff, 0x76541032,
	0x7030, 0x31000311, 0x00000011,
	0x2f48, 0x33773777, 0x42010001,
	0x6b28, 0x00000010, 0x00000012,
	0x7728, 0x00000010, 0x00000012,
	0x10328, 0x00000010, 0x00000012,
	0x10f28, 0x00000010, 0x00000012,
	0x11b28, 0x00000010, 0x00000012,
	0x12728, 0x00000010, 0x00000012,
	0x240c, 0x000007ff, 0x00000000,
	0x8a14, 0xf000001f, 0x00000007,
	0x8b24, 0x3fff3fff, 0x00ff0fff,
	0x8b10, 0x0000ff0f, 0x00000000,
	0x28a4c, 0x07ffffff, 0x06000000,
	0x10c, 0x00000001, 0x00010003,
	0xa02c, 0xffffffff, 0x0000009b,
	0x913c, 0x0000010f, 0x01000100,
	0x8c04, 0xf8ff00ff, 0x40600060,
	0x28350, 0x00000f01, 0x00000000,
	0x9508, 0x3700001f, 0x00000002,
	0x960c, 0xffffffff, 0x54763210,
	0x88c4, 0x001f3ae3, 0x00000082,
	0x88d0, 0xffffffff, 0x0f40df40,
	0x88d4, 0x0000001f, 0x00000010,
	0x8974, 0xffffffff, 0x00000000
पूर्ण;

अटल स्थिर u32 dvst_golden_रेजिस्टरs2[] =
अणु
	0x8f8, 0xffffffff, 0,
	0x8fc, 0x00380000, 0,
	0x8f8, 0xffffffff, 1,
	0x8fc, 0x0e000000, 0
पूर्ण;

अटल स्थिर u32 dvst_golden_रेजिस्टरs[] =
अणु
	0x690, 0x3fff3fff, 0x20c00033,
	0x918c, 0x0fff0fff, 0x00010006,
	0x91a8, 0x0fff0fff, 0x00010006,
	0x9150, 0xffffdfff, 0x6e944040,
	0x917c, 0x0fff0fff, 0x00030002,
	0x9198, 0x0fff0fff, 0x00030002,
	0x915c, 0x0fff0fff, 0x00010000,
	0x3f90, 0xffff0001, 0xff000000,
	0x9178, 0x0fff0fff, 0x00070000,
	0x9194, 0x0fff0fff, 0x00070000,
	0x9148, 0xffff0001, 0xff000000,
	0x9190, 0x0fff0fff, 0x00090008,
	0x91ac, 0x0fff0fff, 0x00090008,
	0x3f94, 0xffff0000, 0xff000000,
	0x914c, 0xffff0000, 0xff000000,
	0x929c, 0x00000fff, 0x00000001,
	0x55e4, 0xff607fff, 0xfc000100,
	0x8a18, 0xff000fff, 0x00000100,
	0x8b28, 0xff000fff, 0x00000100,
	0x9144, 0xfffc0fff, 0x00000100,
	0x6ed8, 0x00010101, 0x00010000,
	0x9830, 0xffffffff, 0x00000000,
	0x9834, 0xf00fffff, 0x00000400,
	0x9838, 0xfffffffe, 0x00000000,
	0xd0c0, 0xff000fff, 0x00000100,
	0xd02c, 0xbfffff1f, 0x08421000,
	0xd0b8, 0x73773777, 0x12010001,
	0x5bb0, 0x000000f0, 0x00000070,
	0x98f8, 0x73773777, 0x12010001,
	0x98fc, 0xffffffff, 0x00000010,
	0x9b7c, 0x00ff0000, 0x00fc0000,
	0x8030, 0x00001f0f, 0x0000100a,
	0x2f48, 0x73773777, 0x12010001,
	0x2408, 0x00030000, 0x000c007f,
	0x8a14, 0xf000003f, 0x00000007,
	0x8b24, 0x3fff3fff, 0x00ff0fff,
	0x8b10, 0x0000ff0f, 0x00000000,
	0x28a4c, 0x07ffffff, 0x06000000,
	0x4d8, 0x00000fff, 0x00000100,
	0xa008, 0xffffffff, 0x00010000,
	0x913c, 0xffff03ff, 0x01000100,
	0x8c00, 0x000000ff, 0x00000003,
	0x8c04, 0xf8ff00ff, 0x40600060,
	0x8cf0, 0x1fff1fff, 0x08e00410,
	0x28350, 0x00000f01, 0x00000000,
	0x9508, 0xf700071f, 0x00000002,
	0x960c, 0xffffffff, 0x54763210,
	0x20ef8, 0x01ff01ff, 0x00000002,
	0x20e98, 0xfffffbff, 0x00200000,
	0x2015c, 0xffffffff, 0x00000f40,
	0x88c4, 0x001f3ae3, 0x00000082,
	0x8978, 0x3fffffff, 0x04050140,
	0x88d4, 0x0000001f, 0x00000010,
	0x8974, 0xffffffff, 0x00000000
पूर्ण;

अटल स्थिर u32 scrapper_golden_रेजिस्टरs[] =
अणु
	0x690, 0x3fff3fff, 0x20c00033,
	0x918c, 0x0fff0fff, 0x00010006,
	0x918c, 0x0fff0fff, 0x00010006,
	0x91a8, 0x0fff0fff, 0x00010006,
	0x91a8, 0x0fff0fff, 0x00010006,
	0x9150, 0xffffdfff, 0x6e944040,
	0x9150, 0xffffdfff, 0x6e944040,
	0x917c, 0x0fff0fff, 0x00030002,
	0x917c, 0x0fff0fff, 0x00030002,
	0x9198, 0x0fff0fff, 0x00030002,
	0x9198, 0x0fff0fff, 0x00030002,
	0x915c, 0x0fff0fff, 0x00010000,
	0x915c, 0x0fff0fff, 0x00010000,
	0x3f90, 0xffff0001, 0xff000000,
	0x3f90, 0xffff0001, 0xff000000,
	0x9178, 0x0fff0fff, 0x00070000,
	0x9178, 0x0fff0fff, 0x00070000,
	0x9194, 0x0fff0fff, 0x00070000,
	0x9194, 0x0fff0fff, 0x00070000,
	0x9148, 0xffff0001, 0xff000000,
	0x9148, 0xffff0001, 0xff000000,
	0x9190, 0x0fff0fff, 0x00090008,
	0x9190, 0x0fff0fff, 0x00090008,
	0x91ac, 0x0fff0fff, 0x00090008,
	0x91ac, 0x0fff0fff, 0x00090008,
	0x3f94, 0xffff0000, 0xff000000,
	0x3f94, 0xffff0000, 0xff000000,
	0x914c, 0xffff0000, 0xff000000,
	0x914c, 0xffff0000, 0xff000000,
	0x929c, 0x00000fff, 0x00000001,
	0x929c, 0x00000fff, 0x00000001,
	0x55e4, 0xff607fff, 0xfc000100,
	0x8a18, 0xff000fff, 0x00000100,
	0x8a18, 0xff000fff, 0x00000100,
	0x8b28, 0xff000fff, 0x00000100,
	0x8b28, 0xff000fff, 0x00000100,
	0x9144, 0xfffc0fff, 0x00000100,
	0x9144, 0xfffc0fff, 0x00000100,
	0x6ed8, 0x00010101, 0x00010000,
	0x9830, 0xffffffff, 0x00000000,
	0x9830, 0xffffffff, 0x00000000,
	0x9834, 0xf00fffff, 0x00000400,
	0x9834, 0xf00fffff, 0x00000400,
	0x9838, 0xfffffffe, 0x00000000,
	0x9838, 0xfffffffe, 0x00000000,
	0xd0c0, 0xff000fff, 0x00000100,
	0xd02c, 0xbfffff1f, 0x08421000,
	0xd02c, 0xbfffff1f, 0x08421000,
	0xd0b8, 0x73773777, 0x12010001,
	0xd0b8, 0x73773777, 0x12010001,
	0x5bb0, 0x000000f0, 0x00000070,
	0x98f8, 0x73773777, 0x12010001,
	0x98f8, 0x73773777, 0x12010001,
	0x98fc, 0xffffffff, 0x00000010,
	0x98fc, 0xffffffff, 0x00000010,
	0x9b7c, 0x00ff0000, 0x00fc0000,
	0x9b7c, 0x00ff0000, 0x00fc0000,
	0x8030, 0x00001f0f, 0x0000100a,
	0x8030, 0x00001f0f, 0x0000100a,
	0x2f48, 0x73773777, 0x12010001,
	0x2f48, 0x73773777, 0x12010001,
	0x2408, 0x00030000, 0x000c007f,
	0x8a14, 0xf000003f, 0x00000007,
	0x8a14, 0xf000003f, 0x00000007,
	0x8b24, 0x3fff3fff, 0x00ff0fff,
	0x8b24, 0x3fff3fff, 0x00ff0fff,
	0x8b10, 0x0000ff0f, 0x00000000,
	0x8b10, 0x0000ff0f, 0x00000000,
	0x28a4c, 0x07ffffff, 0x06000000,
	0x28a4c, 0x07ffffff, 0x06000000,
	0x4d8, 0x00000fff, 0x00000100,
	0x4d8, 0x00000fff, 0x00000100,
	0xa008, 0xffffffff, 0x00010000,
	0xa008, 0xffffffff, 0x00010000,
	0x913c, 0xffff03ff, 0x01000100,
	0x913c, 0xffff03ff, 0x01000100,
	0x90e8, 0x001fffff, 0x010400c0,
	0x8c00, 0x000000ff, 0x00000003,
	0x8c00, 0x000000ff, 0x00000003,
	0x8c04, 0xf8ff00ff, 0x40600060,
	0x8c04, 0xf8ff00ff, 0x40600060,
	0x8c30, 0x0000000f, 0x00040005,
	0x8cf0, 0x1fff1fff, 0x08e00410,
	0x8cf0, 0x1fff1fff, 0x08e00410,
	0x900c, 0x00ffffff, 0x0017071f,
	0x28350, 0x00000f01, 0x00000000,
	0x28350, 0x00000f01, 0x00000000,
	0x9508, 0xf700071f, 0x00000002,
	0x9508, 0xf700071f, 0x00000002,
	0x9688, 0x00300000, 0x0017000f,
	0x960c, 0xffffffff, 0x54763210,
	0x960c, 0xffffffff, 0x54763210,
	0x20ef8, 0x01ff01ff, 0x00000002,
	0x20e98, 0xfffffbff, 0x00200000,
	0x2015c, 0xffffffff, 0x00000f40,
	0x88c4, 0x001f3ae3, 0x00000082,
	0x88c4, 0x001f3ae3, 0x00000082,
	0x8978, 0x3fffffff, 0x04050140,
	0x8978, 0x3fffffff, 0x04050140,
	0x88d4, 0x0000001f, 0x00000010,
	0x88d4, 0x0000001f, 0x00000010,
	0x8974, 0xffffffff, 0x00000000,
	0x8974, 0xffffffff, 0x00000000
पूर्ण;

अटल व्योम ni_init_golden_रेजिस्टरs(काष्ठा radeon_device *rdev)
अणु
	चयन (rdev->family) अणु
	हाल CHIP_CAYMAN:
		radeon_program_रेजिस्टर_sequence(rdev,
						 cayman_golden_रेजिस्टरs,
						 (स्थिर u32)ARRAY_SIZE(cayman_golden_रेजिस्टरs));
		radeon_program_रेजिस्टर_sequence(rdev,
						 cayman_golden_रेजिस्टरs2,
						 (स्थिर u32)ARRAY_SIZE(cayman_golden_रेजिस्टरs2));
		अवरोध;
	हाल CHIP_ARUBA:
		अगर ((rdev->pdev->device == 0x9900) ||
		    (rdev->pdev->device == 0x9901) ||
		    (rdev->pdev->device == 0x9903) ||
		    (rdev->pdev->device == 0x9904) ||
		    (rdev->pdev->device == 0x9905) ||
		    (rdev->pdev->device == 0x9906) ||
		    (rdev->pdev->device == 0x9907) ||
		    (rdev->pdev->device == 0x9908) ||
		    (rdev->pdev->device == 0x9909) ||
		    (rdev->pdev->device == 0x990A) ||
		    (rdev->pdev->device == 0x990B) ||
		    (rdev->pdev->device == 0x990C) ||
		    (rdev->pdev->device == 0x990D) ||
		    (rdev->pdev->device == 0x990E) ||
		    (rdev->pdev->device == 0x990F) ||
		    (rdev->pdev->device == 0x9910) ||
		    (rdev->pdev->device == 0x9913) ||
		    (rdev->pdev->device == 0x9917) ||
		    (rdev->pdev->device == 0x9918)) अणु
			radeon_program_रेजिस्टर_sequence(rdev,
							 dvst_golden_रेजिस्टरs,
							 (स्थिर u32)ARRAY_SIZE(dvst_golden_रेजिस्टरs));
			radeon_program_रेजिस्टर_sequence(rdev,
							 dvst_golden_रेजिस्टरs2,
							 (स्थिर u32)ARRAY_SIZE(dvst_golden_रेजिस्टरs2));
		पूर्ण अन्यथा अणु
			radeon_program_रेजिस्टर_sequence(rdev,
							 scrapper_golden_रेजिस्टरs,
							 (स्थिर u32)ARRAY_SIZE(scrapper_golden_रेजिस्टरs));
			radeon_program_रेजिस्टर_sequence(rdev,
							 dvst_golden_रेजिस्टरs2,
							 (स्थिर u32)ARRAY_SIZE(dvst_golden_रेजिस्टरs2));
		पूर्ण
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

#घोषणा BTC_IO_MC_REGS_SIZE 29

अटल स्थिर u32 barts_io_mc_regs[BTC_IO_MC_REGS_SIZE][2] = अणु
	अणु0x00000077, 0xff010100पूर्ण,
	अणु0x00000078, 0x00000000पूर्ण,
	अणु0x00000079, 0x00001434पूर्ण,
	अणु0x0000007a, 0xcc08ec08पूर्ण,
	अणु0x0000007b, 0x00040000पूर्ण,
	अणु0x0000007c, 0x000080c0पूर्ण,
	अणु0x0000007d, 0x09000000पूर्ण,
	अणु0x0000007e, 0x00210404पूर्ण,
	अणु0x00000081, 0x08a8e800पूर्ण,
	अणु0x00000082, 0x00030444पूर्ण,
	अणु0x00000083, 0x00000000पूर्ण,
	अणु0x00000085, 0x00000001पूर्ण,
	अणु0x00000086, 0x00000002पूर्ण,
	अणु0x00000087, 0x48490000पूर्ण,
	अणु0x00000088, 0x20244647पूर्ण,
	अणु0x00000089, 0x00000005पूर्ण,
	अणु0x0000008b, 0x66030000पूर्ण,
	अणु0x0000008c, 0x00006603पूर्ण,
	अणु0x0000008d, 0x00000100पूर्ण,
	अणु0x0000008f, 0x00001c0aपूर्ण,
	अणु0x00000090, 0xff000001पूर्ण,
	अणु0x00000094, 0x00101101पूर्ण,
	अणु0x00000095, 0x00000fffपूर्ण,
	अणु0x00000096, 0x00116fffपूर्ण,
	अणु0x00000097, 0x60010000पूर्ण,
	अणु0x00000098, 0x10010000पूर्ण,
	अणु0x00000099, 0x00006000पूर्ण,
	अणु0x0000009a, 0x00001000पूर्ण,
	अणु0x0000009f, 0x00946a00पूर्ण
पूर्ण;

अटल स्थिर u32 turks_io_mc_regs[BTC_IO_MC_REGS_SIZE][2] = अणु
	अणु0x00000077, 0xff010100पूर्ण,
	अणु0x00000078, 0x00000000पूर्ण,
	अणु0x00000079, 0x00001434पूर्ण,
	अणु0x0000007a, 0xcc08ec08पूर्ण,
	अणु0x0000007b, 0x00040000पूर्ण,
	अणु0x0000007c, 0x000080c0पूर्ण,
	अणु0x0000007d, 0x09000000पूर्ण,
	अणु0x0000007e, 0x00210404पूर्ण,
	अणु0x00000081, 0x08a8e800पूर्ण,
	अणु0x00000082, 0x00030444पूर्ण,
	अणु0x00000083, 0x00000000पूर्ण,
	अणु0x00000085, 0x00000001पूर्ण,
	अणु0x00000086, 0x00000002पूर्ण,
	अणु0x00000087, 0x48490000पूर्ण,
	अणु0x00000088, 0x20244647पूर्ण,
	अणु0x00000089, 0x00000005पूर्ण,
	अणु0x0000008b, 0x66030000पूर्ण,
	अणु0x0000008c, 0x00006603पूर्ण,
	अणु0x0000008d, 0x00000100पूर्ण,
	अणु0x0000008f, 0x00001c0aपूर्ण,
	अणु0x00000090, 0xff000001पूर्ण,
	अणु0x00000094, 0x00101101पूर्ण,
	अणु0x00000095, 0x00000fffपूर्ण,
	अणु0x00000096, 0x00116fffपूर्ण,
	अणु0x00000097, 0x60010000पूर्ण,
	अणु0x00000098, 0x10010000पूर्ण,
	अणु0x00000099, 0x00006000पूर्ण,
	अणु0x0000009a, 0x00001000पूर्ण,
	अणु0x0000009f, 0x00936a00पूर्ण
पूर्ण;

अटल स्थिर u32 caicos_io_mc_regs[BTC_IO_MC_REGS_SIZE][2] = अणु
	अणु0x00000077, 0xff010100पूर्ण,
	अणु0x00000078, 0x00000000पूर्ण,
	अणु0x00000079, 0x00001434पूर्ण,
	अणु0x0000007a, 0xcc08ec08पूर्ण,
	अणु0x0000007b, 0x00040000पूर्ण,
	अणु0x0000007c, 0x000080c0पूर्ण,
	अणु0x0000007d, 0x09000000पूर्ण,
	अणु0x0000007e, 0x00210404पूर्ण,
	अणु0x00000081, 0x08a8e800पूर्ण,
	अणु0x00000082, 0x00030444पूर्ण,
	अणु0x00000083, 0x00000000पूर्ण,
	अणु0x00000085, 0x00000001पूर्ण,
	अणु0x00000086, 0x00000002पूर्ण,
	अणु0x00000087, 0x48490000पूर्ण,
	अणु0x00000088, 0x20244647पूर्ण,
	अणु0x00000089, 0x00000005पूर्ण,
	अणु0x0000008b, 0x66030000पूर्ण,
	अणु0x0000008c, 0x00006603पूर्ण,
	अणु0x0000008d, 0x00000100पूर्ण,
	अणु0x0000008f, 0x00001c0aपूर्ण,
	अणु0x00000090, 0xff000001पूर्ण,
	अणु0x00000094, 0x00101101पूर्ण,
	अणु0x00000095, 0x00000fffपूर्ण,
	अणु0x00000096, 0x00116fffपूर्ण,
	अणु0x00000097, 0x60010000पूर्ण,
	अणु0x00000098, 0x10010000पूर्ण,
	अणु0x00000099, 0x00006000पूर्ण,
	अणु0x0000009a, 0x00001000पूर्ण,
	अणु0x0000009f, 0x00916a00पूर्ण
पूर्ण;

अटल स्थिर u32 cayman_io_mc_regs[BTC_IO_MC_REGS_SIZE][2] = अणु
	अणु0x00000077, 0xff010100पूर्ण,
	अणु0x00000078, 0x00000000पूर्ण,
	अणु0x00000079, 0x00001434पूर्ण,
	अणु0x0000007a, 0xcc08ec08पूर्ण,
	अणु0x0000007b, 0x00040000पूर्ण,
	अणु0x0000007c, 0x000080c0पूर्ण,
	अणु0x0000007d, 0x09000000पूर्ण,
	अणु0x0000007e, 0x00210404पूर्ण,
	अणु0x00000081, 0x08a8e800पूर्ण,
	अणु0x00000082, 0x00030444पूर्ण,
	अणु0x00000083, 0x00000000पूर्ण,
	अणु0x00000085, 0x00000001पूर्ण,
	अणु0x00000086, 0x00000002पूर्ण,
	अणु0x00000087, 0x48490000पूर्ण,
	अणु0x00000088, 0x20244647पूर्ण,
	अणु0x00000089, 0x00000005पूर्ण,
	अणु0x0000008b, 0x66030000पूर्ण,
	अणु0x0000008c, 0x00006603पूर्ण,
	अणु0x0000008d, 0x00000100पूर्ण,
	अणु0x0000008f, 0x00001c0aपूर्ण,
	अणु0x00000090, 0xff000001पूर्ण,
	अणु0x00000094, 0x00101101पूर्ण,
	अणु0x00000095, 0x00000fffपूर्ण,
	अणु0x00000096, 0x00116fffपूर्ण,
	अणु0x00000097, 0x60010000पूर्ण,
	अणु0x00000098, 0x10010000पूर्ण,
	अणु0x00000099, 0x00006000पूर्ण,
	अणु0x0000009a, 0x00001000पूर्ण,
	अणु0x0000009f, 0x00976b00पूर्ण
पूर्ण;

पूर्णांक ni_mc_load_microcode(काष्ठा radeon_device *rdev)
अणु
	स्थिर __be32 *fw_data;
	u32 mem_type, running, blackout = 0;
	u32 *io_mc_regs;
	पूर्णांक i, ucode_size, regs_size;

	अगर (!rdev->mc_fw)
		वापस -EINVAL;

	चयन (rdev->family) अणु
	हाल CHIP_BARTS:
		io_mc_regs = (u32 *)&barts_io_mc_regs;
		ucode_size = BTC_MC_UCODE_SIZE;
		regs_size = BTC_IO_MC_REGS_SIZE;
		अवरोध;
	हाल CHIP_TURKS:
		io_mc_regs = (u32 *)&turks_io_mc_regs;
		ucode_size = BTC_MC_UCODE_SIZE;
		regs_size = BTC_IO_MC_REGS_SIZE;
		अवरोध;
	हाल CHIP_CAICOS:
	शेष:
		io_mc_regs = (u32 *)&caicos_io_mc_regs;
		ucode_size = BTC_MC_UCODE_SIZE;
		regs_size = BTC_IO_MC_REGS_SIZE;
		अवरोध;
	हाल CHIP_CAYMAN:
		io_mc_regs = (u32 *)&cayman_io_mc_regs;
		ucode_size = CAYMAN_MC_UCODE_SIZE;
		regs_size = BTC_IO_MC_REGS_SIZE;
		अवरोध;
	पूर्ण

	mem_type = (RREG32(MC_SEQ_MISC0) & MC_SEQ_MISC0_GDDR5_MASK) >> MC_SEQ_MISC0_GDDR5_SHIFT;
	running = RREG32(MC_SEQ_SUP_CNTL) & RUN_MASK;

	अगर ((mem_type == MC_SEQ_MISC0_GDDR5_VALUE) && (running == 0)) अणु
		अगर (running) अणु
			blackout = RREG32(MC_SHARED_BLACKOUT_CNTL);
			WREG32(MC_SHARED_BLACKOUT_CNTL, 1);
		पूर्ण

		/* reset the engine and set to writable */
		WREG32(MC_SEQ_SUP_CNTL, 0x00000008);
		WREG32(MC_SEQ_SUP_CNTL, 0x00000010);

		/* load mc io regs */
		क्रम (i = 0; i < regs_size; i++) अणु
			WREG32(MC_SEQ_IO_DEBUG_INDEX, io_mc_regs[(i << 1)]);
			WREG32(MC_SEQ_IO_DEBUG_DATA, io_mc_regs[(i << 1) + 1]);
		पूर्ण
		/* load the MC ucode */
		fw_data = (स्थिर __be32 *)rdev->mc_fw->data;
		क्रम (i = 0; i < ucode_size; i++)
			WREG32(MC_SEQ_SUP_PGM, be32_to_cpup(fw_data++));

		/* put the engine back पूर्णांकo the active state */
		WREG32(MC_SEQ_SUP_CNTL, 0x00000008);
		WREG32(MC_SEQ_SUP_CNTL, 0x00000004);
		WREG32(MC_SEQ_SUP_CNTL, 0x00000001);

		/* रुको क्रम training to complete */
		क्रम (i = 0; i < rdev->usec_समयout; i++) अणु
			अगर (RREG32(MC_IO_PAD_CNTL_D0) & MEM_FALL_OUT_CMD)
				अवरोध;
			udelay(1);
		पूर्ण

		अगर (running)
			WREG32(MC_SHARED_BLACKOUT_CNTL, blackout);
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक ni_init_microcode(काष्ठा radeon_device *rdev)
अणु
	स्थिर अक्षर *chip_name;
	स्थिर अक्षर *rlc_chip_name;
	माप_प्रकार pfp_req_size, me_req_size, rlc_req_size, mc_req_size;
	माप_प्रकार smc_req_size = 0;
	अक्षर fw_name[30];
	पूर्णांक err;

	DRM_DEBUG("\n");

	चयन (rdev->family) अणु
	हाल CHIP_BARTS:
		chip_name = "BARTS";
		rlc_chip_name = "BTC";
		pfp_req_size = EVERGREEN_PFP_UCODE_SIZE * 4;
		me_req_size = EVERGREEN_PM4_UCODE_SIZE * 4;
		rlc_req_size = EVERGREEN_RLC_UCODE_SIZE * 4;
		mc_req_size = BTC_MC_UCODE_SIZE * 4;
		smc_req_size = ALIGN(BARTS_SMC_UCODE_SIZE, 4);
		अवरोध;
	हाल CHIP_TURKS:
		chip_name = "TURKS";
		rlc_chip_name = "BTC";
		pfp_req_size = EVERGREEN_PFP_UCODE_SIZE * 4;
		me_req_size = EVERGREEN_PM4_UCODE_SIZE * 4;
		rlc_req_size = EVERGREEN_RLC_UCODE_SIZE * 4;
		mc_req_size = BTC_MC_UCODE_SIZE * 4;
		smc_req_size = ALIGN(TURKS_SMC_UCODE_SIZE, 4);
		अवरोध;
	हाल CHIP_CAICOS:
		chip_name = "CAICOS";
		rlc_chip_name = "BTC";
		pfp_req_size = EVERGREEN_PFP_UCODE_SIZE * 4;
		me_req_size = EVERGREEN_PM4_UCODE_SIZE * 4;
		rlc_req_size = EVERGREEN_RLC_UCODE_SIZE * 4;
		mc_req_size = BTC_MC_UCODE_SIZE * 4;
		smc_req_size = ALIGN(CAICOS_SMC_UCODE_SIZE, 4);
		अवरोध;
	हाल CHIP_CAYMAN:
		chip_name = "CAYMAN";
		rlc_chip_name = "CAYMAN";
		pfp_req_size = CAYMAN_PFP_UCODE_SIZE * 4;
		me_req_size = CAYMAN_PM4_UCODE_SIZE * 4;
		rlc_req_size = CAYMAN_RLC_UCODE_SIZE * 4;
		mc_req_size = CAYMAN_MC_UCODE_SIZE * 4;
		smc_req_size = ALIGN(CAYMAN_SMC_UCODE_SIZE, 4);
		अवरोध;
	हाल CHIP_ARUBA:
		chip_name = "ARUBA";
		rlc_chip_name = "ARUBA";
		/* pfp/me same size as CAYMAN */
		pfp_req_size = CAYMAN_PFP_UCODE_SIZE * 4;
		me_req_size = CAYMAN_PM4_UCODE_SIZE * 4;
		rlc_req_size = ARUBA_RLC_UCODE_SIZE * 4;
		mc_req_size = 0;
		अवरोध;
	शेष: BUG();
	पूर्ण

	DRM_INFO("Loading %s Microcode\n", chip_name);

	snम_लिखो(fw_name, माप(fw_name), "radeon/%s_pfp.bin", chip_name);
	err = request_firmware(&rdev->pfp_fw, fw_name, rdev->dev);
	अगर (err)
		जाओ out;
	अगर (rdev->pfp_fw->size != pfp_req_size) अणु
		pr_err("ni_cp: Bogus length %zu in firmware \"%s\"\n",
		       rdev->pfp_fw->size, fw_name);
		err = -EINVAL;
		जाओ out;
	पूर्ण

	snम_लिखो(fw_name, माप(fw_name), "radeon/%s_me.bin", chip_name);
	err = request_firmware(&rdev->me_fw, fw_name, rdev->dev);
	अगर (err)
		जाओ out;
	अगर (rdev->me_fw->size != me_req_size) अणु
		pr_err("ni_cp: Bogus length %zu in firmware \"%s\"\n",
		       rdev->me_fw->size, fw_name);
		err = -EINVAL;
	पूर्ण

	snम_लिखो(fw_name, माप(fw_name), "radeon/%s_rlc.bin", rlc_chip_name);
	err = request_firmware(&rdev->rlc_fw, fw_name, rdev->dev);
	अगर (err)
		जाओ out;
	अगर (rdev->rlc_fw->size != rlc_req_size) अणु
		pr_err("ni_rlc: Bogus length %zu in firmware \"%s\"\n",
		       rdev->rlc_fw->size, fw_name);
		err = -EINVAL;
	पूर्ण

	/* no MC ucode on TN */
	अगर (!(rdev->flags & RADEON_IS_IGP)) अणु
		snम_लिखो(fw_name, माप(fw_name), "radeon/%s_mc.bin", chip_name);
		err = request_firmware(&rdev->mc_fw, fw_name, rdev->dev);
		अगर (err)
			जाओ out;
		अगर (rdev->mc_fw->size != mc_req_size) अणु
			pr_err("ni_mc: Bogus length %zu in firmware \"%s\"\n",
			       rdev->mc_fw->size, fw_name);
			err = -EINVAL;
		पूर्ण
	पूर्ण

	अगर ((rdev->family >= CHIP_BARTS) && (rdev->family <= CHIP_CAYMAN)) अणु
		snम_लिखो(fw_name, माप(fw_name), "radeon/%s_smc.bin", chip_name);
		err = request_firmware(&rdev->smc_fw, fw_name, rdev->dev);
		अगर (err) अणु
			pr_err("smc: error loading firmware \"%s\"\n", fw_name);
			release_firmware(rdev->smc_fw);
			rdev->smc_fw = शून्य;
			err = 0;
		पूर्ण अन्यथा अगर (rdev->smc_fw->size != smc_req_size) अणु
			pr_err("ni_mc: Bogus length %zu in firmware \"%s\"\n",
			       rdev->mc_fw->size, fw_name);
			err = -EINVAL;
		पूर्ण
	पूर्ण

out:
	अगर (err) अणु
		अगर (err != -EINVAL)
			pr_err("ni_cp: Failed to load firmware \"%s\"\n",
			       fw_name);
		release_firmware(rdev->pfp_fw);
		rdev->pfp_fw = शून्य;
		release_firmware(rdev->me_fw);
		rdev->me_fw = शून्य;
		release_firmware(rdev->rlc_fw);
		rdev->rlc_fw = शून्य;
		release_firmware(rdev->mc_fw);
		rdev->mc_fw = शून्य;
	पूर्ण
	वापस err;
पूर्ण

/**
 * cayman_get_allowed_info_रेजिस्टर - fetch the रेजिस्टर क्रम the info ioctl
 *
 * @rdev: radeon_device poपूर्णांकer
 * @reg: रेजिस्टर offset in bytes
 * @val: रेजिस्टर value
 *
 * Returns 0 क्रम success or -EINVAL क्रम an invalid रेजिस्टर
 *
 */
पूर्णांक cayman_get_allowed_info_रेजिस्टर(काष्ठा radeon_device *rdev,
				     u32 reg, u32 *val)
अणु
	चयन (reg) अणु
	हाल GRBM_STATUS:
	हाल GRBM_STATUS_SE0:
	हाल GRBM_STATUS_SE1:
	हाल SRBM_STATUS:
	हाल SRBM_STATUS2:
	हाल (DMA_STATUS_REG + DMA0_REGISTER_OFFSET):
	हाल (DMA_STATUS_REG + DMA1_REGISTER_OFFSET):
	हाल UVD_STATUS:
		*val = RREG32(reg);
		वापस 0;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

पूर्णांक tn_get_temp(काष्ठा radeon_device *rdev)
अणु
	u32 temp = RREG32_SMC(TN_CURRENT_GNB_TEMP) & 0x7ff;
	पूर्णांक actual_temp = (temp / 8) - 49;

	वापस actual_temp * 1000;
पूर्ण

/*
 * Core functions
 */
अटल व्योम cayman_gpu_init(काष्ठा radeon_device *rdev)
अणु
	u32 gb_addr_config = 0;
	u32 mc_arb_ramcfg;
	u32 cgts_tcc_disable;
	u32 sx_debug_1;
	u32 smx_dc_ctl0;
	u32 cgts_sm_ctrl_reg;
	u32 hdp_host_path_cntl;
	u32 पंचांगp;
	u32 disabled_rb_mask;
	पूर्णांक i, j;

	चयन (rdev->family) अणु
	हाल CHIP_CAYMAN:
		rdev->config.cayman.max_shader_engines = 2;
		rdev->config.cayman.max_pipes_per_simd = 4;
		rdev->config.cayman.max_tile_pipes = 8;
		rdev->config.cayman.max_simds_per_se = 12;
		rdev->config.cayman.max_backends_per_se = 4;
		rdev->config.cayman.max_texture_channel_caches = 8;
		rdev->config.cayman.max_gprs = 256;
		rdev->config.cayman.max_thपढ़ोs = 256;
		rdev->config.cayman.max_gs_thपढ़ोs = 32;
		rdev->config.cayman.max_stack_entries = 512;
		rdev->config.cayman.sx_num_of_sets = 8;
		rdev->config.cayman.sx_max_export_size = 256;
		rdev->config.cayman.sx_max_export_pos_size = 64;
		rdev->config.cayman.sx_max_export_smx_size = 192;
		rdev->config.cayman.max_hw_contexts = 8;
		rdev->config.cayman.sq_num_cf_insts = 2;

		rdev->config.cayman.sc_prim_fअगरo_size = 0x100;
		rdev->config.cayman.sc_hiz_tile_fअगरo_size = 0x30;
		rdev->config.cayman.sc_earlyz_tile_fअगरo_size = 0x130;
		gb_addr_config = CAYMAN_GB_ADDR_CONFIG_GOLDEN;
		अवरोध;
	हाल CHIP_ARUBA:
	शेष:
		rdev->config.cayman.max_shader_engines = 1;
		rdev->config.cayman.max_pipes_per_simd = 4;
		rdev->config.cayman.max_tile_pipes = 2;
		अगर ((rdev->pdev->device == 0x9900) ||
		    (rdev->pdev->device == 0x9901) ||
		    (rdev->pdev->device == 0x9905) ||
		    (rdev->pdev->device == 0x9906) ||
		    (rdev->pdev->device == 0x9907) ||
		    (rdev->pdev->device == 0x9908) ||
		    (rdev->pdev->device == 0x9909) ||
		    (rdev->pdev->device == 0x990B) ||
		    (rdev->pdev->device == 0x990C) ||
		    (rdev->pdev->device == 0x990F) ||
		    (rdev->pdev->device == 0x9910) ||
		    (rdev->pdev->device == 0x9917) ||
		    (rdev->pdev->device == 0x9999) ||
		    (rdev->pdev->device == 0x999C)) अणु
			rdev->config.cayman.max_simds_per_se = 6;
			rdev->config.cayman.max_backends_per_se = 2;
			rdev->config.cayman.max_hw_contexts = 8;
			rdev->config.cayman.sx_max_export_size = 256;
			rdev->config.cayman.sx_max_export_pos_size = 64;
			rdev->config.cayman.sx_max_export_smx_size = 192;
		पूर्ण अन्यथा अगर ((rdev->pdev->device == 0x9903) ||
			   (rdev->pdev->device == 0x9904) ||
			   (rdev->pdev->device == 0x990A) ||
			   (rdev->pdev->device == 0x990D) ||
			   (rdev->pdev->device == 0x990E) ||
			   (rdev->pdev->device == 0x9913) ||
			   (rdev->pdev->device == 0x9918) ||
			   (rdev->pdev->device == 0x999D)) अणु
			rdev->config.cayman.max_simds_per_se = 4;
			rdev->config.cayman.max_backends_per_se = 2;
			rdev->config.cayman.max_hw_contexts = 8;
			rdev->config.cayman.sx_max_export_size = 256;
			rdev->config.cayman.sx_max_export_pos_size = 64;
			rdev->config.cayman.sx_max_export_smx_size = 192;
		पूर्ण अन्यथा अगर ((rdev->pdev->device == 0x9919) ||
			   (rdev->pdev->device == 0x9990) ||
			   (rdev->pdev->device == 0x9991) ||
			   (rdev->pdev->device == 0x9994) ||
			   (rdev->pdev->device == 0x9995) ||
			   (rdev->pdev->device == 0x9996) ||
			   (rdev->pdev->device == 0x999A) ||
			   (rdev->pdev->device == 0x99A0)) अणु
			rdev->config.cayman.max_simds_per_se = 3;
			rdev->config.cayman.max_backends_per_se = 1;
			rdev->config.cayman.max_hw_contexts = 4;
			rdev->config.cayman.sx_max_export_size = 128;
			rdev->config.cayman.sx_max_export_pos_size = 32;
			rdev->config.cayman.sx_max_export_smx_size = 96;
		पूर्ण अन्यथा अणु
			rdev->config.cayman.max_simds_per_se = 2;
			rdev->config.cayman.max_backends_per_se = 1;
			rdev->config.cayman.max_hw_contexts = 4;
			rdev->config.cayman.sx_max_export_size = 128;
			rdev->config.cayman.sx_max_export_pos_size = 32;
			rdev->config.cayman.sx_max_export_smx_size = 96;
		पूर्ण
		rdev->config.cayman.max_texture_channel_caches = 2;
		rdev->config.cayman.max_gprs = 256;
		rdev->config.cayman.max_thपढ़ोs = 256;
		rdev->config.cayman.max_gs_thपढ़ोs = 32;
		rdev->config.cayman.max_stack_entries = 512;
		rdev->config.cayman.sx_num_of_sets = 8;
		rdev->config.cayman.sq_num_cf_insts = 2;

		rdev->config.cayman.sc_prim_fअगरo_size = 0x40;
		rdev->config.cayman.sc_hiz_tile_fअगरo_size = 0x30;
		rdev->config.cayman.sc_earlyz_tile_fअगरo_size = 0x130;
		gb_addr_config = ARUBA_GB_ADDR_CONFIG_GOLDEN;
		अवरोध;
	पूर्ण

	/* Initialize HDP */
	क्रम (i = 0, j = 0; i < 32; i++, j += 0x18) अणु
		WREG32((0x2c14 + j), 0x00000000);
		WREG32((0x2c18 + j), 0x00000000);
		WREG32((0x2c1c + j), 0x00000000);
		WREG32((0x2c20 + j), 0x00000000);
		WREG32((0x2c24 + j), 0x00000000);
	पूर्ण

	WREG32(GRBM_CNTL, GRBM_READ_TIMEOUT(0xff));
	WREG32(SRBM_INT_CNTL, 0x1);
	WREG32(SRBM_INT_ACK, 0x1);

	evergreen_fix_pci_max_पढ़ो_req_size(rdev);

	RREG32(MC_SHARED_CHMAP);
	mc_arb_ramcfg = RREG32(MC_ARB_RAMCFG);

	पंचांगp = (mc_arb_ramcfg & NOOFCOLS_MASK) >> NOOFCOLS_SHIFT;
	rdev->config.cayman.mem_row_size_in_kb = (4 * (1 << (8 + पंचांगp))) / 1024;
	अगर (rdev->config.cayman.mem_row_size_in_kb > 4)
		rdev->config.cayman.mem_row_size_in_kb = 4;
	/* XXX use MC settings? */
	rdev->config.cayman.shader_engine_tile_size = 32;
	rdev->config.cayman.num_gpus = 1;
	rdev->config.cayman.multi_gpu_tile_size = 64;

	पंचांगp = (gb_addr_config & NUM_PIPES_MASK) >> NUM_PIPES_SHIFT;
	rdev->config.cayman.num_tile_pipes = (1 << पंचांगp);
	पंचांगp = (gb_addr_config & PIPE_INTERLEAVE_SIZE_MASK) >> PIPE_INTERLEAVE_SIZE_SHIFT;
	rdev->config.cayman.mem_max_burst_length_bytes = (पंचांगp + 1) * 256;
	पंचांगp = (gb_addr_config & NUM_SHADER_ENGINES_MASK) >> NUM_SHADER_ENGINES_SHIFT;
	rdev->config.cayman.num_shader_engines = पंचांगp + 1;
	पंचांगp = (gb_addr_config & NUM_GPUS_MASK) >> NUM_GPUS_SHIFT;
	rdev->config.cayman.num_gpus = पंचांगp + 1;
	पंचांगp = (gb_addr_config & MULTI_GPU_TILE_SIZE_MASK) >> MULTI_GPU_TILE_SIZE_SHIFT;
	rdev->config.cayman.multi_gpu_tile_size = 1 << पंचांगp;
	पंचांगp = (gb_addr_config & ROW_SIZE_MASK) >> ROW_SIZE_SHIFT;
	rdev->config.cayman.mem_row_size_in_kb = 1 << पंचांगp;


	/* setup tiling info dword.  gb_addr_config is not adequate since it करोes
	 * not have bank info, so create a custom tiling dword.
	 * bits 3:0   num_pipes
	 * bits 7:4   num_banks
	 * bits 11:8  group_size
	 * bits 15:12 row_size
	 */
	rdev->config.cayman.tile_config = 0;
	चयन (rdev->config.cayman.num_tile_pipes) अणु
	हाल 1:
	शेष:
		rdev->config.cayman.tile_config |= (0 << 0);
		अवरोध;
	हाल 2:
		rdev->config.cayman.tile_config |= (1 << 0);
		अवरोध;
	हाल 4:
		rdev->config.cayman.tile_config |= (2 << 0);
		अवरोध;
	हाल 8:
		rdev->config.cayman.tile_config |= (3 << 0);
		अवरोध;
	पूर्ण

	/* num banks is 8 on all fusion asics. 0 = 4, 1 = 8, 2 = 16 */
	अगर (rdev->flags & RADEON_IS_IGP)
		rdev->config.cayman.tile_config |= 1 << 4;
	अन्यथा अणु
		चयन ((mc_arb_ramcfg & NOOFBANK_MASK) >> NOOFBANK_SHIFT) अणु
		हाल 0: /* four banks */
			rdev->config.cayman.tile_config |= 0 << 4;
			अवरोध;
		हाल 1: /* eight banks */
			rdev->config.cayman.tile_config |= 1 << 4;
			अवरोध;
		हाल 2: /* sixteen banks */
		शेष:
			rdev->config.cayman.tile_config |= 2 << 4;
			अवरोध;
		पूर्ण
	पूर्ण
	rdev->config.cayman.tile_config |=
		((gb_addr_config & PIPE_INTERLEAVE_SIZE_MASK) >> PIPE_INTERLEAVE_SIZE_SHIFT) << 8;
	rdev->config.cayman.tile_config |=
		((gb_addr_config & ROW_SIZE_MASK) >> ROW_SIZE_SHIFT) << 12;

	पंचांगp = 0;
	क्रम (i = (rdev->config.cayman.max_shader_engines - 1); i >= 0; i--) अणु
		u32 rb_disable_biपंचांगap;

		WREG32(GRBM_GFX_INDEX, INSTANCE_BROADCAST_WRITES | SE_INDEX(i));
		WREG32(RLC_GFX_INDEX, INSTANCE_BROADCAST_WRITES | SE_INDEX(i));
		rb_disable_biपंचांगap = (RREG32(CC_RB_BACKEND_DISABLE) & 0x00ff0000) >> 16;
		पंचांगp <<= 4;
		पंचांगp |= rb_disable_biपंचांगap;
	पूर्ण
	/* enabled rb are just the one not disabled :) */
	disabled_rb_mask = पंचांगp;
	पंचांगp = 0;
	क्रम (i = 0; i < (rdev->config.cayman.max_backends_per_se * rdev->config.cayman.max_shader_engines); i++)
		पंचांगp |= (1 << i);
	/* अगर all the backends are disabled, fix it up here */
	अगर ((disabled_rb_mask & पंचांगp) == पंचांगp) अणु
		क्रम (i = 0; i < (rdev->config.cayman.max_backends_per_se * rdev->config.cayman.max_shader_engines); i++)
			disabled_rb_mask &= ~(1 << i);
	पूर्ण

	क्रम (i = 0; i < rdev->config.cayman.max_shader_engines; i++) अणु
		u32 simd_disable_biपंचांगap;

		WREG32(GRBM_GFX_INDEX, INSTANCE_BROADCAST_WRITES | SE_INDEX(i));
		WREG32(RLC_GFX_INDEX, INSTANCE_BROADCAST_WRITES | SE_INDEX(i));
		simd_disable_biपंचांगap = (RREG32(CC_GC_SHADER_PIPE_CONFIG) & 0xffff0000) >> 16;
		simd_disable_biपंचांगap |= 0xffffffff << rdev->config.cayman.max_simds_per_se;
		पंचांगp <<= 16;
		पंचांगp |= simd_disable_biपंचांगap;
	पूर्ण
	rdev->config.cayman.active_simds = hweight32(~पंचांगp);

	WREG32(GRBM_GFX_INDEX, INSTANCE_BROADCAST_WRITES | SE_BROADCAST_WRITES);
	WREG32(RLC_GFX_INDEX, INSTANCE_BROADCAST_WRITES | SE_BROADCAST_WRITES);

	WREG32(GB_ADDR_CONFIG, gb_addr_config);
	WREG32(DMIF_ADDR_CONFIG, gb_addr_config);
	अगर (ASIC_IS_DCE6(rdev))
		WREG32(DMIF_ADDR_CALC, gb_addr_config);
	WREG32(HDP_ADDR_CONFIG, gb_addr_config);
	WREG32(DMA_TILING_CONFIG + DMA0_REGISTER_OFFSET, gb_addr_config);
	WREG32(DMA_TILING_CONFIG + DMA1_REGISTER_OFFSET, gb_addr_config);
	WREG32(UVD_UDEC_ADDR_CONFIG, gb_addr_config);
	WREG32(UVD_UDEC_DB_ADDR_CONFIG, gb_addr_config);
	WREG32(UVD_UDEC_DBW_ADDR_CONFIG, gb_addr_config);

	अगर ((rdev->config.cayman.max_backends_per_se == 1) &&
	    (rdev->flags & RADEON_IS_IGP)) अणु
		अगर ((disabled_rb_mask & 3) == 2) अणु
			/* RB1 disabled, RB0 enabled */
			पंचांगp = 0x00000000;
		पूर्ण अन्यथा अणु
			/* RB0 disabled, RB1 enabled */
			पंचांगp = 0x11111111;
		पूर्ण
	पूर्ण अन्यथा अणु
		पंचांगp = gb_addr_config & NUM_PIPES_MASK;
		पंचांगp = r6xx_remap_render_backend(rdev, पंचांगp,
						rdev->config.cayman.max_backends_per_se *
						rdev->config.cayman.max_shader_engines,
						CAYMAN_MAX_BACKENDS, disabled_rb_mask);
	पूर्ण
	rdev->config.cayman.backend_map = पंचांगp;
	WREG32(GB_BACKEND_MAP, पंचांगp);

	cgts_tcc_disable = 0xffff0000;
	क्रम (i = 0; i < rdev->config.cayman.max_texture_channel_caches; i++)
		cgts_tcc_disable &= ~(1 << (16 + i));
	WREG32(CGTS_TCC_DISABLE, cgts_tcc_disable);
	WREG32(CGTS_SYS_TCC_DISABLE, cgts_tcc_disable);
	WREG32(CGTS_USER_SYS_TCC_DISABLE, cgts_tcc_disable);
	WREG32(CGTS_USER_TCC_DISABLE, cgts_tcc_disable);

	/* reprogram the shader complex */
	cgts_sm_ctrl_reg = RREG32(CGTS_SM_CTRL_REG);
	क्रम (i = 0; i < 16; i++)
		WREG32(CGTS_SM_CTRL_REG, OVERRIDE);
	WREG32(CGTS_SM_CTRL_REG, cgts_sm_ctrl_reg);

	/* set HW शेषs क्रम 3D engine */
	WREG32(CP_MEQ_THRESHOLDS, MEQ1_START(0x30) | MEQ2_START(0x60));

	sx_debug_1 = RREG32(SX_DEBUG_1);
	sx_debug_1 |= ENABLE_NEW_SMX_ADDRESS;
	WREG32(SX_DEBUG_1, sx_debug_1);

	smx_dc_ctl0 = RREG32(SMX_DC_CTL0);
	smx_dc_ctl0 &= ~NUMBER_OF_SETS(0x1ff);
	smx_dc_ctl0 |= NUMBER_OF_SETS(rdev->config.cayman.sx_num_of_sets);
	WREG32(SMX_DC_CTL0, smx_dc_ctl0);

	WREG32(SPI_CONFIG_CNTL_1, VTX_DONE_DELAY(4) | CRC_SIMD_ID_WADDR_DISABLE);

	/* need to be explicitly zero-ed */
	WREG32(VGT_OFFCHIP_LDS_BASE, 0);
	WREG32(SQ_LSTMP_RING_BASE, 0);
	WREG32(SQ_HSTMP_RING_BASE, 0);
	WREG32(SQ_ESTMP_RING_BASE, 0);
	WREG32(SQ_GSTMP_RING_BASE, 0);
	WREG32(SQ_VSTMP_RING_BASE, 0);
	WREG32(SQ_PSTMP_RING_BASE, 0);

	WREG32(TA_CNTL_AUX, DISABLE_CUBE_ANISO);

	WREG32(SX_EXPORT_BUFFER_SIZES, (COLOR_BUFFER_SIZE((rdev->config.cayman.sx_max_export_size / 4) - 1) |
					POSITION_BUFFER_SIZE((rdev->config.cayman.sx_max_export_pos_size / 4) - 1) |
					SMX_BUFFER_SIZE((rdev->config.cayman.sx_max_export_smx_size / 4) - 1)));

	WREG32(PA_SC_FIFO_SIZE, (SC_PRIM_FIFO_SIZE(rdev->config.cayman.sc_prim_fअगरo_size) |
				 SC_HIZ_TILE_FIFO_SIZE(rdev->config.cayman.sc_hiz_tile_fअगरo_size) |
				 SC_EARLYZ_TILE_FIFO_SIZE(rdev->config.cayman.sc_earlyz_tile_fअगरo_size)));


	WREG32(VGT_NUM_INSTANCES, 1);

	WREG32(CP_PERFMON_CNTL, 0);

	WREG32(SQ_MS_FIFO_SIZES, (CACHE_FIFO_SIZE(16 * rdev->config.cayman.sq_num_cf_insts) |
				  FETCH_FIFO_HIWATER(0x4) |
				  DONE_FIFO_HIWATER(0xe0) |
				  ALU_UPDATE_FIFO_HIWATER(0x8)));

	WREG32(SQ_GPR_RESOURCE_MGMT_1, NUM_CLAUSE_TEMP_GPRS(4));
	WREG32(SQ_CONFIG, (VC_ENABLE |
			   EXPORT_SRC_C |
			   GFX_PRIO(0) |
			   CS1_PRIO(0) |
			   CS2_PRIO(1)));
	WREG32(SQ_DYN_GPR_CNTL_PS_FLUSH_REQ, DYN_GPR_ENABLE);

	WREG32(PA_SC_FORCE_EOV_MAX_CNTS, (FORCE_EOV_MAX_CLK_CNT(4095) |
					  FORCE_EOV_MAX_REZ_CNT(255)));

	WREG32(VGT_CACHE_INVALIDATION, CACHE_INVALIDATION(VC_AND_TC) |
	       AUTO_INVLD_EN(ES_AND_GS_AUTO));

	WREG32(VGT_GS_VERTEX_REUSE, 16);
	WREG32(PA_SC_LINE_STIPPLE_STATE, 0);

	WREG32(CB_PERF_CTR0_SEL_0, 0);
	WREG32(CB_PERF_CTR0_SEL_1, 0);
	WREG32(CB_PERF_CTR1_SEL_0, 0);
	WREG32(CB_PERF_CTR1_SEL_1, 0);
	WREG32(CB_PERF_CTR2_SEL_0, 0);
	WREG32(CB_PERF_CTR2_SEL_1, 0);
	WREG32(CB_PERF_CTR3_SEL_0, 0);
	WREG32(CB_PERF_CTR3_SEL_1, 0);

	पंचांगp = RREG32(HDP_MISC_CNTL);
	पंचांगp |= HDP_FLUSH_INVALIDATE_CACHE;
	WREG32(HDP_MISC_CNTL, पंचांगp);

	hdp_host_path_cntl = RREG32(HDP_HOST_PATH_CNTL);
	WREG32(HDP_HOST_PATH_CNTL, hdp_host_path_cntl);

	WREG32(PA_CL_ENHANCE, CLIP_VTX_REORDER_ENA | NUM_CLIP_SEQ(3));

	udelay(50);

	/* set घड़ीgating golden values on TN */
	अगर (rdev->family == CHIP_ARUBA) अणु
		पंचांगp = RREG32_CG(CG_CGTT_LOCAL_0);
		पंचांगp &= ~0x00380000;
		WREG32_CG(CG_CGTT_LOCAL_0, पंचांगp);
		पंचांगp = RREG32_CG(CG_CGTT_LOCAL_1);
		पंचांगp &= ~0x0e000000;
		WREG32_CG(CG_CGTT_LOCAL_1, पंचांगp);
	पूर्ण
पूर्ण

/*
 * GART
 */
व्योम cayman_pcie_gart_tlb_flush(काष्ठा radeon_device *rdev)
अणु
	/* flush hdp cache */
	WREG32(HDP_MEM_COHERENCY_FLUSH_CNTL, 0x1);

	/* bits 0-7 are the VM contexts0-7 */
	WREG32(VM_INVALIDATE_REQUEST, 1);
पूर्ण

अटल पूर्णांक cayman_pcie_gart_enable(काष्ठा radeon_device *rdev)
अणु
	पूर्णांक i, r;

	अगर (rdev->gart.robj == शून्य) अणु
		dev_err(rdev->dev, "No VRAM object for PCIE GART.\n");
		वापस -EINVAL;
	पूर्ण
	r = radeon_gart_table_vram_pin(rdev);
	अगर (r)
		वापस r;
	/* Setup TLB control */
	WREG32(MC_VM_MX_L1_TLB_CNTL,
	       (0xA << 7) |
	       ENABLE_L1_TLB |
	       ENABLE_L1_FRAGMENT_PROCESSING |
	       SYSTEM_ACCESS_MODE_NOT_IN_SYS |
	       ENABLE_ADVANCED_DRIVER_MODEL |
	       SYSTEM_APERTURE_UNMAPPED_ACCESS_PASS_THRU);
	/* Setup L2 cache */
	WREG32(VM_L2_CNTL, ENABLE_L2_CACHE |
	       ENABLE_L2_FRAGMENT_PROCESSING |
	       ENABLE_L2_PTE_CACHE_LRU_UPDATE_BY_WRITE |
	       ENABLE_L2_PDE0_CACHE_LRU_UPDATE_BY_WRITE |
	       EFFECTIVE_L2_QUEUE_SIZE(7) |
	       CONTEXT1_IDENTITY_ACCESS_MODE(1));
	WREG32(VM_L2_CNTL2, INVALIDATE_ALL_L1_TLBS | INVALIDATE_L2_CACHE);
	WREG32(VM_L2_CNTL3, L2_CACHE_BIGK_ASSOCIATIVITY |
	       BANK_SELECT(6) |
	       L2_CACHE_BIGK_FRAGMENT_SIZE(6));
	/* setup context0 */
	WREG32(VM_CONTEXT0_PAGE_TABLE_START_ADDR, rdev->mc.gtt_start >> 12);
	WREG32(VM_CONTEXT0_PAGE_TABLE_END_ADDR, rdev->mc.gtt_end >> 12);
	WREG32(VM_CONTEXT0_PAGE_TABLE_BASE_ADDR, rdev->gart.table_addr >> 12);
	WREG32(VM_CONTEXT0_PROTECTION_FAULT_DEFAULT_ADDR,
			(u32)(rdev->dummy_page.addr >> 12));
	WREG32(VM_CONTEXT0_CNTL2, 0);
	WREG32(VM_CONTEXT0_CNTL, ENABLE_CONTEXT | PAGE_TABLE_DEPTH(0) |
				RANGE_PROTECTION_FAULT_ENABLE_DEFAULT);

	WREG32(0x15D4, 0);
	WREG32(0x15D8, 0);
	WREG32(0x15DC, 0);

	/* empty context1-7 */
	/* Assign the pt base to something valid क्रम now; the pts used क्रम
	 * the VMs are determined by the application and setup and asचिन्हित
	 * on the fly in the vm part of radeon_gart.c
	 */
	क्रम (i = 1; i < 8; i++) अणु
		WREG32(VM_CONTEXT0_PAGE_TABLE_START_ADDR + (i << 2), 0);
		WREG32(VM_CONTEXT0_PAGE_TABLE_END_ADDR + (i << 2),
			rdev->vm_manager.max_pfn - 1);
		WREG32(VM_CONTEXT0_PAGE_TABLE_BASE_ADDR + (i << 2),
		       rdev->vm_manager.saved_table_addr[i]);
	पूर्ण

	/* enable context1-7 */
	WREG32(VM_CONTEXT1_PROTECTION_FAULT_DEFAULT_ADDR,
	       (u32)(rdev->dummy_page.addr >> 12));
	WREG32(VM_CONTEXT1_CNTL2, 4);
	WREG32(VM_CONTEXT1_CNTL, ENABLE_CONTEXT | PAGE_TABLE_DEPTH(1) |
				PAGE_TABLE_BLOCK_SIZE(radeon_vm_block_size - 9) |
				RANGE_PROTECTION_FAULT_ENABLE_INTERRUPT |
				RANGE_PROTECTION_FAULT_ENABLE_DEFAULT |
				DUMMY_PAGE_PROTECTION_FAULT_ENABLE_INTERRUPT |
				DUMMY_PAGE_PROTECTION_FAULT_ENABLE_DEFAULT |
				PDE0_PROTECTION_FAULT_ENABLE_INTERRUPT |
				PDE0_PROTECTION_FAULT_ENABLE_DEFAULT |
				VALID_PROTECTION_FAULT_ENABLE_INTERRUPT |
				VALID_PROTECTION_FAULT_ENABLE_DEFAULT |
				READ_PROTECTION_FAULT_ENABLE_INTERRUPT |
				READ_PROTECTION_FAULT_ENABLE_DEFAULT |
				WRITE_PROTECTION_FAULT_ENABLE_INTERRUPT |
				WRITE_PROTECTION_FAULT_ENABLE_DEFAULT);

	cayman_pcie_gart_tlb_flush(rdev);
	DRM_INFO("PCIE GART of %uM enabled (table at 0x%016llX).\n",
		 (अचिन्हित)(rdev->mc.gtt_size >> 20),
		 (अचिन्हित दीर्घ दीर्घ)rdev->gart.table_addr);
	rdev->gart.पढ़ोy = true;
	वापस 0;
पूर्ण

अटल व्योम cayman_pcie_gart_disable(काष्ठा radeon_device *rdev)
अणु
	अचिन्हित i;

	क्रम (i = 1; i < 8; ++i) अणु
		rdev->vm_manager.saved_table_addr[i] = RREG32(
			VM_CONTEXT0_PAGE_TABLE_BASE_ADDR + (i << 2));
	पूर्ण

	/* Disable all tables */
	WREG32(VM_CONTEXT0_CNTL, 0);
	WREG32(VM_CONTEXT1_CNTL, 0);
	/* Setup TLB control */
	WREG32(MC_VM_MX_L1_TLB_CNTL, ENABLE_L1_FRAGMENT_PROCESSING |
	       SYSTEM_ACCESS_MODE_NOT_IN_SYS |
	       SYSTEM_APERTURE_UNMAPPED_ACCESS_PASS_THRU);
	/* Setup L2 cache */
	WREG32(VM_L2_CNTL, ENABLE_L2_PTE_CACHE_LRU_UPDATE_BY_WRITE |
	       ENABLE_L2_PDE0_CACHE_LRU_UPDATE_BY_WRITE |
	       EFFECTIVE_L2_QUEUE_SIZE(7) |
	       CONTEXT1_IDENTITY_ACCESS_MODE(1));
	WREG32(VM_L2_CNTL2, 0);
	WREG32(VM_L2_CNTL3, L2_CACHE_BIGK_ASSOCIATIVITY |
	       L2_CACHE_BIGK_FRAGMENT_SIZE(6));
	radeon_gart_table_vram_unpin(rdev);
पूर्ण

अटल व्योम cayman_pcie_gart_fini(काष्ठा radeon_device *rdev)
अणु
	cayman_pcie_gart_disable(rdev);
	radeon_gart_table_vram_मुक्त(rdev);
	radeon_gart_fini(rdev);
पूर्ण

व्योम cayman_cp_पूर्णांक_cntl_setup(काष्ठा radeon_device *rdev,
			      पूर्णांक ring, u32 cp_पूर्णांक_cntl)
अणु
	WREG32(SRBM_GFX_CNTL, RINGID(ring));
	WREG32(CP_INT_CNTL, cp_पूर्णांक_cntl);
पूर्ण

/*
 * CP.
 */
व्योम cayman_fence_ring_emit(काष्ठा radeon_device *rdev,
			    काष्ठा radeon_fence *fence)
अणु
	काष्ठा radeon_ring *ring = &rdev->ring[fence->ring];
	u64 addr = rdev->fence_drv[fence->ring].gpu_addr;
	u32 cp_coher_cntl = PACKET3_FULL_CACHE_ENA | PACKET3_TC_ACTION_ENA |
		PACKET3_SH_ACTION_ENA;

	/* flush पढ़ो cache over gart क्रम this vmid */
	radeon_ring_ग_लिखो(ring, PACKET3(PACKET3_SURFACE_SYNC, 3));
	radeon_ring_ग_लिखो(ring, PACKET3_ENGINE_ME | cp_coher_cntl);
	radeon_ring_ग_लिखो(ring, 0xFFFFFFFF);
	radeon_ring_ग_लिखो(ring, 0);
	radeon_ring_ग_लिखो(ring, 10); /* poll पूर्णांकerval */
	/* EVENT_WRITE_EOP - flush caches, send पूर्णांक */
	radeon_ring_ग_लिखो(ring, PACKET3(PACKET3_EVENT_WRITE_EOP, 4));
	radeon_ring_ग_लिखो(ring, EVENT_TYPE(CACHE_FLUSH_AND_INV_EVENT_TS) | EVENT_INDEX(5));
	radeon_ring_ग_लिखो(ring, lower_32_bits(addr));
	radeon_ring_ग_लिखो(ring, (upper_32_bits(addr) & 0xff) | DATA_SEL(1) | INT_SEL(2));
	radeon_ring_ग_लिखो(ring, fence->seq);
	radeon_ring_ग_लिखो(ring, 0);
पूर्ण

व्योम cayman_ring_ib_execute(काष्ठा radeon_device *rdev, काष्ठा radeon_ib *ib)
अणु
	काष्ठा radeon_ring *ring = &rdev->ring[ib->ring];
	अचिन्हित vm_id = ib->vm ? ib->vm->ids[ib->ring].id : 0;
	u32 cp_coher_cntl = PACKET3_FULL_CACHE_ENA | PACKET3_TC_ACTION_ENA |
		PACKET3_SH_ACTION_ENA;

	/* set to DX10/11 mode */
	radeon_ring_ग_लिखो(ring, PACKET3(PACKET3_MODE_CONTROL, 0));
	radeon_ring_ग_लिखो(ring, 1);

	अगर (ring->rptr_save_reg) अणु
		uपूर्णांक32_t next_rptr = ring->wptr + 3 + 4 + 8;
		radeon_ring_ग_लिखो(ring, PACKET3(PACKET3_SET_CONFIG_REG, 1));
		radeon_ring_ग_लिखो(ring, ((ring->rptr_save_reg - 
					  PACKET3_SET_CONFIG_REG_START) >> 2));
		radeon_ring_ग_लिखो(ring, next_rptr);
	पूर्ण

	radeon_ring_ग_लिखो(ring, PACKET3(PACKET3_INसूचीECT_BUFFER, 2));
	radeon_ring_ग_लिखो(ring,
#अगर_घोषित __BIG_ENDIAN
			  (2 << 0) |
#पूर्ण_अगर
			  (ib->gpu_addr & 0xFFFFFFFC));
	radeon_ring_ग_लिखो(ring, upper_32_bits(ib->gpu_addr) & 0xFF);
	radeon_ring_ग_लिखो(ring, ib->length_dw | (vm_id << 24));

	/* flush पढ़ो cache over gart क्रम this vmid */
	radeon_ring_ग_लिखो(ring, PACKET3(PACKET3_SURFACE_SYNC, 3));
	radeon_ring_ग_लिखो(ring, PACKET3_ENGINE_ME | cp_coher_cntl);
	radeon_ring_ग_लिखो(ring, 0xFFFFFFFF);
	radeon_ring_ग_लिखो(ring, 0);
	radeon_ring_ग_लिखो(ring, (vm_id << 24) | 10); /* poll पूर्णांकerval */
पूर्ण

अटल व्योम cayman_cp_enable(काष्ठा radeon_device *rdev, bool enable)
अणु
	अगर (enable)
		WREG32(CP_ME_CNTL, 0);
	अन्यथा अणु
		अगर (rdev->asic->copy.copy_ring_index == RADEON_RING_TYPE_GFX_INDEX)
			radeon_tपंचांग_set_active_vram_size(rdev, rdev->mc.visible_vram_size);
		WREG32(CP_ME_CNTL, (CP_ME_HALT | CP_PFP_HALT));
		WREG32(SCRATCH_UMSK, 0);
		rdev->ring[RADEON_RING_TYPE_GFX_INDEX].पढ़ोy = false;
	पूर्ण
पूर्ण

u32 cayman_gfx_get_rptr(काष्ठा radeon_device *rdev,
			काष्ठा radeon_ring *ring)
अणु
	u32 rptr;

	अगर (rdev->wb.enabled)
		rptr = rdev->wb.wb[ring->rptr_offs/4];
	अन्यथा अणु
		अगर (ring->idx == RADEON_RING_TYPE_GFX_INDEX)
			rptr = RREG32(CP_RB0_RPTR);
		अन्यथा अगर (ring->idx == CAYMAN_RING_TYPE_CP1_INDEX)
			rptr = RREG32(CP_RB1_RPTR);
		अन्यथा
			rptr = RREG32(CP_RB2_RPTR);
	पूर्ण

	वापस rptr;
पूर्ण

u32 cayman_gfx_get_wptr(काष्ठा radeon_device *rdev,
			काष्ठा radeon_ring *ring)
अणु
	u32 wptr;

	अगर (ring->idx == RADEON_RING_TYPE_GFX_INDEX)
		wptr = RREG32(CP_RB0_WPTR);
	अन्यथा अगर (ring->idx == CAYMAN_RING_TYPE_CP1_INDEX)
		wptr = RREG32(CP_RB1_WPTR);
	अन्यथा
		wptr = RREG32(CP_RB2_WPTR);

	वापस wptr;
पूर्ण

व्योम cayman_gfx_set_wptr(काष्ठा radeon_device *rdev,
			 काष्ठा radeon_ring *ring)
अणु
	अगर (ring->idx == RADEON_RING_TYPE_GFX_INDEX) अणु
		WREG32(CP_RB0_WPTR, ring->wptr);
		(व्योम)RREG32(CP_RB0_WPTR);
	पूर्ण अन्यथा अगर (ring->idx == CAYMAN_RING_TYPE_CP1_INDEX) अणु
		WREG32(CP_RB1_WPTR, ring->wptr);
		(व्योम)RREG32(CP_RB1_WPTR);
	पूर्ण अन्यथा अणु
		WREG32(CP_RB2_WPTR, ring->wptr);
		(व्योम)RREG32(CP_RB2_WPTR);
	पूर्ण
पूर्ण

अटल पूर्णांक cayman_cp_load_microcode(काष्ठा radeon_device *rdev)
अणु
	स्थिर __be32 *fw_data;
	पूर्णांक i;

	अगर (!rdev->me_fw || !rdev->pfp_fw)
		वापस -EINVAL;

	cayman_cp_enable(rdev, false);

	fw_data = (स्थिर __be32 *)rdev->pfp_fw->data;
	WREG32(CP_PFP_UCODE_ADDR, 0);
	क्रम (i = 0; i < CAYMAN_PFP_UCODE_SIZE; i++)
		WREG32(CP_PFP_UCODE_DATA, be32_to_cpup(fw_data++));
	WREG32(CP_PFP_UCODE_ADDR, 0);

	fw_data = (स्थिर __be32 *)rdev->me_fw->data;
	WREG32(CP_ME_RAM_WADDR, 0);
	क्रम (i = 0; i < CAYMAN_PM4_UCODE_SIZE; i++)
		WREG32(CP_ME_RAM_DATA, be32_to_cpup(fw_data++));

	WREG32(CP_PFP_UCODE_ADDR, 0);
	WREG32(CP_ME_RAM_WADDR, 0);
	WREG32(CP_ME_RAM_RADDR, 0);
	वापस 0;
पूर्ण

अटल पूर्णांक cayman_cp_start(काष्ठा radeon_device *rdev)
अणु
	काष्ठा radeon_ring *ring = &rdev->ring[RADEON_RING_TYPE_GFX_INDEX];
	पूर्णांक r, i;

	r = radeon_ring_lock(rdev, ring, 7);
	अगर (r) अणु
		DRM_ERROR("radeon: cp failed to lock ring (%d).\n", r);
		वापस r;
	पूर्ण
	radeon_ring_ग_लिखो(ring, PACKET3(PACKET3_ME_INITIALIZE, 5));
	radeon_ring_ग_लिखो(ring, 0x1);
	radeon_ring_ग_लिखो(ring, 0x0);
	radeon_ring_ग_लिखो(ring, rdev->config.cayman.max_hw_contexts - 1);
	radeon_ring_ग_लिखो(ring, PACKET3_ME_INITIALIZE_DEVICE_ID(1));
	radeon_ring_ग_लिखो(ring, 0);
	radeon_ring_ग_लिखो(ring, 0);
	radeon_ring_unlock_commit(rdev, ring, false);

	cayman_cp_enable(rdev, true);

	r = radeon_ring_lock(rdev, ring, cayman_शेष_size + 19);
	अगर (r) अणु
		DRM_ERROR("radeon: cp failed to lock ring (%d).\n", r);
		वापस r;
	पूर्ण

	/* setup clear context state */
	radeon_ring_ग_लिखो(ring, PACKET3(PACKET3_PREAMBLE_CNTL, 0));
	radeon_ring_ग_लिखो(ring, PACKET3_PREAMBLE_BEGIN_CLEAR_STATE);

	क्रम (i = 0; i < cayman_शेष_size; i++)
		radeon_ring_ग_लिखो(ring, cayman_शेष_state[i]);

	radeon_ring_ग_लिखो(ring, PACKET3(PACKET3_PREAMBLE_CNTL, 0));
	radeon_ring_ग_लिखो(ring, PACKET3_PREAMBLE_END_CLEAR_STATE);

	/* set clear context state */
	radeon_ring_ग_लिखो(ring, PACKET3(PACKET3_CLEAR_STATE, 0));
	radeon_ring_ग_लिखो(ring, 0);

	/* SQ_VTX_BASE_VTX_LOC */
	radeon_ring_ग_लिखो(ring, 0xc0026f00);
	radeon_ring_ग_लिखो(ring, 0x00000000);
	radeon_ring_ग_लिखो(ring, 0x00000000);
	radeon_ring_ग_लिखो(ring, 0x00000000);

	/* Clear स्थिरs */
	radeon_ring_ग_लिखो(ring, 0xc0036f00);
	radeon_ring_ग_लिखो(ring, 0x00000bc4);
	radeon_ring_ग_लिखो(ring, 0xffffffff);
	radeon_ring_ग_लिखो(ring, 0xffffffff);
	radeon_ring_ग_लिखो(ring, 0xffffffff);

	radeon_ring_ग_लिखो(ring, 0xc0026900);
	radeon_ring_ग_लिखो(ring, 0x00000316);
	radeon_ring_ग_लिखो(ring, 0x0000000e); /* VGT_VERTEX_REUSE_BLOCK_CNTL */
	radeon_ring_ग_लिखो(ring, 0x00000010); /*  */

	radeon_ring_unlock_commit(rdev, ring, false);

	/* XXX init other rings */

	वापस 0;
पूर्ण

अटल व्योम cayman_cp_fini(काष्ठा radeon_device *rdev)
अणु
	काष्ठा radeon_ring *ring = &rdev->ring[RADEON_RING_TYPE_GFX_INDEX];
	cayman_cp_enable(rdev, false);
	radeon_ring_fini(rdev, ring);
	radeon_scratch_मुक्त(rdev, ring->rptr_save_reg);
पूर्ण

अटल पूर्णांक cayman_cp_resume(काष्ठा radeon_device *rdev)
अणु
	अटल स्थिर पूर्णांक ridx[] = अणु
		RADEON_RING_TYPE_GFX_INDEX,
		CAYMAN_RING_TYPE_CP1_INDEX,
		CAYMAN_RING_TYPE_CP2_INDEX
	पूर्ण;
	अटल स्थिर अचिन्हित cp_rb_cntl[] = अणु
		CP_RB0_CNTL,
		CP_RB1_CNTL,
		CP_RB2_CNTL,
	पूर्ण;
	अटल स्थिर अचिन्हित cp_rb_rptr_addr[] = अणु
		CP_RB0_RPTR_ADDR,
		CP_RB1_RPTR_ADDR,
		CP_RB2_RPTR_ADDR
	पूर्ण;
	अटल स्थिर अचिन्हित cp_rb_rptr_addr_hi[] = अणु
		CP_RB0_RPTR_ADDR_HI,
		CP_RB1_RPTR_ADDR_HI,
		CP_RB2_RPTR_ADDR_HI
	पूर्ण;
	अटल स्थिर अचिन्हित cp_rb_base[] = अणु
		CP_RB0_BASE,
		CP_RB1_BASE,
		CP_RB2_BASE
	पूर्ण;
	अटल स्थिर अचिन्हित cp_rb_rptr[] = अणु
		CP_RB0_RPTR,
		CP_RB1_RPTR,
		CP_RB2_RPTR
	पूर्ण;
	अटल स्थिर अचिन्हित cp_rb_wptr[] = अणु
		CP_RB0_WPTR,
		CP_RB1_WPTR,
		CP_RB2_WPTR
	पूर्ण;
	काष्ठा radeon_ring *ring;
	पूर्णांक i, r;

	/* Reset cp; अगर cp is reset, then PA, SH, VGT also need to be reset */
	WREG32(GRBM_SOFT_RESET, (SOFT_RESET_CP |
				 SOFT_RESET_PA |
				 SOFT_RESET_SH |
				 SOFT_RESET_VGT |
				 SOFT_RESET_SPI |
				 SOFT_RESET_SX));
	RREG32(GRBM_SOFT_RESET);
	mdelay(15);
	WREG32(GRBM_SOFT_RESET, 0);
	RREG32(GRBM_SOFT_RESET);

	WREG32(CP_SEM_WAIT_TIMER, 0x0);
	WREG32(CP_SEM_INCOMPLETE_TIMER_CNTL, 0x0);

	/* Set the ग_लिखो poपूर्णांकer delay */
	WREG32(CP_RB_WPTR_DELAY, 0);

	WREG32(CP_DEBUG, (1 << 27));

	/* set the wb address whether it's enabled or not */
	WREG32(SCRATCH_ADDR, ((rdev->wb.gpu_addr + RADEON_WB_SCRATCH_OFFSET) >> 8) & 0xFFFFFFFF);
	WREG32(SCRATCH_UMSK, 0xff);

	क्रम (i = 0; i < 3; ++i) अणु
		uपूर्णांक32_t rb_cntl;
		uपूर्णांक64_t addr;

		/* Set ring buffer size */
		ring = &rdev->ring[ridx[i]];
		rb_cntl = order_base_2(ring->ring_size / 8);
		rb_cntl |= order_base_2(RADEON_GPU_PAGE_SIZE/8) << 8;
#अगर_घोषित __BIG_ENDIAN
		rb_cntl |= BUF_SWAP_32BIT;
#पूर्ण_अगर
		WREG32(cp_rb_cntl[i], rb_cntl);

		/* set the wb address whether it's enabled or not */
		addr = rdev->wb.gpu_addr + RADEON_WB_CP_RPTR_OFFSET;
		WREG32(cp_rb_rptr_addr[i], addr & 0xFFFFFFFC);
		WREG32(cp_rb_rptr_addr_hi[i], upper_32_bits(addr) & 0xFF);
	पूर्ण

	/* set the rb base addr, this causes an पूर्णांकernal reset of ALL rings */
	क्रम (i = 0; i < 3; ++i) अणु
		ring = &rdev->ring[ridx[i]];
		WREG32(cp_rb_base[i], ring->gpu_addr >> 8);
	पूर्ण

	क्रम (i = 0; i < 3; ++i) अणु
		/* Initialize the ring buffer's पढ़ो and ग_लिखो poपूर्णांकers */
		ring = &rdev->ring[ridx[i]];
		WREG32_P(cp_rb_cntl[i], RB_RPTR_WR_ENA, ~RB_RPTR_WR_ENA);

		ring->wptr = 0;
		WREG32(cp_rb_rptr[i], 0);
		WREG32(cp_rb_wptr[i], ring->wptr);

		mdelay(1);
		WREG32_P(cp_rb_cntl[i], 0, ~RB_RPTR_WR_ENA);
	पूर्ण

	/* start the rings */
	cayman_cp_start(rdev);
	rdev->ring[RADEON_RING_TYPE_GFX_INDEX].पढ़ोy = true;
	rdev->ring[CAYMAN_RING_TYPE_CP1_INDEX].पढ़ोy = false;
	rdev->ring[CAYMAN_RING_TYPE_CP2_INDEX].पढ़ोy = false;
	/* this only test cp0 */
	r = radeon_ring_test(rdev, RADEON_RING_TYPE_GFX_INDEX, &rdev->ring[RADEON_RING_TYPE_GFX_INDEX]);
	अगर (r) अणु
		rdev->ring[RADEON_RING_TYPE_GFX_INDEX].पढ़ोy = false;
		rdev->ring[CAYMAN_RING_TYPE_CP1_INDEX].पढ़ोy = false;
		rdev->ring[CAYMAN_RING_TYPE_CP2_INDEX].पढ़ोy = false;
		वापस r;
	पूर्ण

	अगर (rdev->asic->copy.copy_ring_index == RADEON_RING_TYPE_GFX_INDEX)
		radeon_tपंचांग_set_active_vram_size(rdev, rdev->mc.real_vram_size);

	वापस 0;
पूर्ण

u32 cayman_gpu_check_soft_reset(काष्ठा radeon_device *rdev)
अणु
	u32 reset_mask = 0;
	u32 पंचांगp;

	/* GRBM_STATUS */
	पंचांगp = RREG32(GRBM_STATUS);
	अगर (पंचांगp & (PA_BUSY | SC_BUSY |
		   SH_BUSY | SX_BUSY |
		   TA_BUSY | VGT_BUSY |
		   DB_BUSY | CB_BUSY |
		   GDS_BUSY | SPI_BUSY |
		   IA_BUSY | IA_BUSY_NO_DMA))
		reset_mask |= RADEON_RESET_GFX;

	अगर (पंचांगp & (CF_RQ_PENDING | PF_RQ_PENDING |
		   CP_BUSY | CP_COHERENCY_BUSY))
		reset_mask |= RADEON_RESET_CP;

	अगर (पंचांगp & GRBM_EE_BUSY)
		reset_mask |= RADEON_RESET_GRBM | RADEON_RESET_GFX | RADEON_RESET_CP;

	/* DMA_STATUS_REG 0 */
	पंचांगp = RREG32(DMA_STATUS_REG + DMA0_REGISTER_OFFSET);
	अगर (!(पंचांगp & DMA_IDLE))
		reset_mask |= RADEON_RESET_DMA;

	/* DMA_STATUS_REG 1 */
	पंचांगp = RREG32(DMA_STATUS_REG + DMA1_REGISTER_OFFSET);
	अगर (!(पंचांगp & DMA_IDLE))
		reset_mask |= RADEON_RESET_DMA1;

	/* SRBM_STATUS2 */
	पंचांगp = RREG32(SRBM_STATUS2);
	अगर (पंचांगp & DMA_BUSY)
		reset_mask |= RADEON_RESET_DMA;

	अगर (पंचांगp & DMA1_BUSY)
		reset_mask |= RADEON_RESET_DMA1;

	/* SRBM_STATUS */
	पंचांगp = RREG32(SRBM_STATUS);
	अगर (पंचांगp & (RLC_RQ_PENDING | RLC_BUSY))
		reset_mask |= RADEON_RESET_RLC;

	अगर (पंचांगp & IH_BUSY)
		reset_mask |= RADEON_RESET_IH;

	अगर (पंचांगp & SEM_BUSY)
		reset_mask |= RADEON_RESET_SEM;

	अगर (पंचांगp & GRBM_RQ_PENDING)
		reset_mask |= RADEON_RESET_GRBM;

	अगर (पंचांगp & VMC_BUSY)
		reset_mask |= RADEON_RESET_VMC;

	अगर (पंचांगp & (MCB_BUSY | MCB_NON_DISPLAY_BUSY |
		   MCC_BUSY | MCD_BUSY))
		reset_mask |= RADEON_RESET_MC;

	अगर (evergreen_is_display_hung(rdev))
		reset_mask |= RADEON_RESET_DISPLAY;

	/* VM_L2_STATUS */
	पंचांगp = RREG32(VM_L2_STATUS);
	अगर (पंचांगp & L2_BUSY)
		reset_mask |= RADEON_RESET_VMC;

	/* Skip MC reset as it's mostly likely not hung, just busy */
	अगर (reset_mask & RADEON_RESET_MC) अणु
		DRM_DEBUG("MC busy: 0x%08X, clearing.\n", reset_mask);
		reset_mask &= ~RADEON_RESET_MC;
	पूर्ण

	वापस reset_mask;
पूर्ण

अटल व्योम cayman_gpu_soft_reset(काष्ठा radeon_device *rdev, u32 reset_mask)
अणु
	काष्ठा evergreen_mc_save save;
	u32 grbm_soft_reset = 0, srbm_soft_reset = 0;
	u32 पंचांगp;

	अगर (reset_mask == 0)
		वापस;

	dev_info(rdev->dev, "GPU softreset: 0x%08X\n", reset_mask);

	evergreen_prपूर्णांक_gpu_status_regs(rdev);
	dev_info(rdev->dev, "  VM_CONTEXT0_PROTECTION_FAULT_ADDR   0x%08X\n",
		 RREG32(0x14F8));
	dev_info(rdev->dev, "  VM_CONTEXT0_PROTECTION_FAULT_STATUS 0x%08X\n",
		 RREG32(0x14D8));
	dev_info(rdev->dev, "  VM_CONTEXT1_PROTECTION_FAULT_ADDR   0x%08X\n",
		 RREG32(0x14FC));
	dev_info(rdev->dev, "  VM_CONTEXT1_PROTECTION_FAULT_STATUS 0x%08X\n",
		 RREG32(0x14DC));

	/* Disable CP parsing/prefetching */
	WREG32(CP_ME_CNTL, CP_ME_HALT | CP_PFP_HALT);

	अगर (reset_mask & RADEON_RESET_DMA) अणु
		/* dma0 */
		पंचांगp = RREG32(DMA_RB_CNTL + DMA0_REGISTER_OFFSET);
		पंचांगp &= ~DMA_RB_ENABLE;
		WREG32(DMA_RB_CNTL + DMA0_REGISTER_OFFSET, पंचांगp);
	पूर्ण

	अगर (reset_mask & RADEON_RESET_DMA1) अणु
		/* dma1 */
		पंचांगp = RREG32(DMA_RB_CNTL + DMA1_REGISTER_OFFSET);
		पंचांगp &= ~DMA_RB_ENABLE;
		WREG32(DMA_RB_CNTL + DMA1_REGISTER_OFFSET, पंचांगp);
	पूर्ण

	udelay(50);

	evergreen_mc_stop(rdev, &save);
	अगर (evergreen_mc_रुको_क्रम_idle(rdev)) अणु
		dev_warn(rdev->dev, "Wait for MC idle timedout !\n");
	पूर्ण

	अगर (reset_mask & (RADEON_RESET_GFX | RADEON_RESET_COMPUTE)) अणु
		grbm_soft_reset = SOFT_RESET_CB |
			SOFT_RESET_DB |
			SOFT_RESET_GDS |
			SOFT_RESET_PA |
			SOFT_RESET_SC |
			SOFT_RESET_SPI |
			SOFT_RESET_SH |
			SOFT_RESET_SX |
			SOFT_RESET_TC |
			SOFT_RESET_TA |
			SOFT_RESET_VGT |
			SOFT_RESET_IA;
	पूर्ण

	अगर (reset_mask & RADEON_RESET_CP) अणु
		grbm_soft_reset |= SOFT_RESET_CP | SOFT_RESET_VGT;

		srbm_soft_reset |= SOFT_RESET_GRBM;
	पूर्ण

	अगर (reset_mask & RADEON_RESET_DMA)
		srbm_soft_reset |= SOFT_RESET_DMA;

	अगर (reset_mask & RADEON_RESET_DMA1)
		srbm_soft_reset |= SOFT_RESET_DMA1;

	अगर (reset_mask & RADEON_RESET_DISPLAY)
		srbm_soft_reset |= SOFT_RESET_DC;

	अगर (reset_mask & RADEON_RESET_RLC)
		srbm_soft_reset |= SOFT_RESET_RLC;

	अगर (reset_mask & RADEON_RESET_SEM)
		srbm_soft_reset |= SOFT_RESET_SEM;

	अगर (reset_mask & RADEON_RESET_IH)
		srbm_soft_reset |= SOFT_RESET_IH;

	अगर (reset_mask & RADEON_RESET_GRBM)
		srbm_soft_reset |= SOFT_RESET_GRBM;

	अगर (reset_mask & RADEON_RESET_VMC)
		srbm_soft_reset |= SOFT_RESET_VMC;

	अगर (!(rdev->flags & RADEON_IS_IGP)) अणु
		अगर (reset_mask & RADEON_RESET_MC)
			srbm_soft_reset |= SOFT_RESET_MC;
	पूर्ण

	अगर (grbm_soft_reset) अणु
		पंचांगp = RREG32(GRBM_SOFT_RESET);
		पंचांगp |= grbm_soft_reset;
		dev_info(rdev->dev, "GRBM_SOFT_RESET=0x%08X\n", पंचांगp);
		WREG32(GRBM_SOFT_RESET, पंचांगp);
		पंचांगp = RREG32(GRBM_SOFT_RESET);

		udelay(50);

		पंचांगp &= ~grbm_soft_reset;
		WREG32(GRBM_SOFT_RESET, पंचांगp);
		पंचांगp = RREG32(GRBM_SOFT_RESET);
	पूर्ण

	अगर (srbm_soft_reset) अणु
		पंचांगp = RREG32(SRBM_SOFT_RESET);
		पंचांगp |= srbm_soft_reset;
		dev_info(rdev->dev, "SRBM_SOFT_RESET=0x%08X\n", पंचांगp);
		WREG32(SRBM_SOFT_RESET, पंचांगp);
		पंचांगp = RREG32(SRBM_SOFT_RESET);

		udelay(50);

		पंचांगp &= ~srbm_soft_reset;
		WREG32(SRBM_SOFT_RESET, पंचांगp);
		पंचांगp = RREG32(SRBM_SOFT_RESET);
	पूर्ण

	/* Wait a little क्रम things to settle करोwn */
	udelay(50);

	evergreen_mc_resume(rdev, &save);
	udelay(50);

	evergreen_prपूर्णांक_gpu_status_regs(rdev);
पूर्ण

पूर्णांक cayman_asic_reset(काष्ठा radeon_device *rdev, bool hard)
अणु
	u32 reset_mask;

	अगर (hard) अणु
		evergreen_gpu_pci_config_reset(rdev);
		वापस 0;
	पूर्ण

	reset_mask = cayman_gpu_check_soft_reset(rdev);

	अगर (reset_mask)
		r600_set_bios_scratch_engine_hung(rdev, true);

	cayman_gpu_soft_reset(rdev, reset_mask);

	reset_mask = cayman_gpu_check_soft_reset(rdev);

	अगर (reset_mask)
		evergreen_gpu_pci_config_reset(rdev);

	r600_set_bios_scratch_engine_hung(rdev, false);

	वापस 0;
पूर्ण

/**
 * cayman_gfx_is_lockup - Check अगर the GFX engine is locked up
 *
 * @rdev: radeon_device poपूर्णांकer
 * @ring: radeon_ring काष्ठाure holding ring inक्रमmation
 *
 * Check अगर the GFX engine is locked up.
 * Returns true अगर the engine appears to be locked up, false अगर not.
 */
bool cayman_gfx_is_lockup(काष्ठा radeon_device *rdev, काष्ठा radeon_ring *ring)
अणु
	u32 reset_mask = cayman_gpu_check_soft_reset(rdev);

	अगर (!(reset_mask & (RADEON_RESET_GFX |
			    RADEON_RESET_COMPUTE |
			    RADEON_RESET_CP))) अणु
		radeon_ring_lockup_update(rdev, ring);
		वापस false;
	पूर्ण
	वापस radeon_ring_test_lockup(rdev, ring);
पूर्ण

अटल व्योम cayman_uvd_init(काष्ठा radeon_device *rdev)
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

अटल व्योम cayman_uvd_start(काष्ठा radeon_device *rdev)
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

अटल व्योम cayman_uvd_resume(काष्ठा radeon_device *rdev)
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

अटल व्योम cayman_vce_init(काष्ठा radeon_device *rdev)
अणु
	पूर्णांक r;

	/* Only set क्रम CHIP_ARUBA */
	अगर (!rdev->has_vce)
		वापस;

	r = radeon_vce_init(rdev);
	अगर (r) अणु
		dev_err(rdev->dev, "failed VCE (%d) init.\n", r);
		/*
		 * At this poपूर्णांक rdev->vce.vcpu_bo is शून्य which trickles करोwn
		 * to early fails cayman_vce_start() and thus nothing happens
		 * there. So it is poपूर्णांकless to try to go through that code
		 * hence why we disable vce here.
		 */
		rdev->has_vce = false;
		वापस;
	पूर्ण
	rdev->ring[TN_RING_TYPE_VCE1_INDEX].ring_obj = शून्य;
	r600_ring_init(rdev, &rdev->ring[TN_RING_TYPE_VCE1_INDEX], 4096);
	rdev->ring[TN_RING_TYPE_VCE2_INDEX].ring_obj = शून्य;
	r600_ring_init(rdev, &rdev->ring[TN_RING_TYPE_VCE2_INDEX], 4096);
पूर्ण

अटल व्योम cayman_vce_start(काष्ठा radeon_device *rdev)
अणु
	पूर्णांक r;

	अगर (!rdev->has_vce)
		वापस;

	r = radeon_vce_resume(rdev);
	अगर (r) अणु
		dev_err(rdev->dev, "failed VCE resume (%d).\n", r);
		जाओ error;
	पूर्ण
	r = vce_v1_0_resume(rdev);
	अगर (r) अणु
		dev_err(rdev->dev, "failed VCE resume (%d).\n", r);
		जाओ error;
	पूर्ण
	r = radeon_fence_driver_start_ring(rdev, TN_RING_TYPE_VCE1_INDEX);
	अगर (r) अणु
		dev_err(rdev->dev, "failed initializing VCE1 fences (%d).\n", r);
		जाओ error;
	पूर्ण
	r = radeon_fence_driver_start_ring(rdev, TN_RING_TYPE_VCE2_INDEX);
	अगर (r) अणु
		dev_err(rdev->dev, "failed initializing VCE2 fences (%d).\n", r);
		जाओ error;
	पूर्ण
	वापस;

error:
	rdev->ring[TN_RING_TYPE_VCE1_INDEX].ring_size = 0;
	rdev->ring[TN_RING_TYPE_VCE2_INDEX].ring_size = 0;
पूर्ण

अटल व्योम cayman_vce_resume(काष्ठा radeon_device *rdev)
अणु
	काष्ठा radeon_ring *ring;
	पूर्णांक r;

	अगर (!rdev->has_vce || !rdev->ring[TN_RING_TYPE_VCE1_INDEX].ring_size)
		वापस;

	ring = &rdev->ring[TN_RING_TYPE_VCE1_INDEX];
	r = radeon_ring_init(rdev, ring, ring->ring_size, 0, 0x0);
	अगर (r) अणु
		dev_err(rdev->dev, "failed initializing VCE1 ring (%d).\n", r);
		वापस;
	पूर्ण
	ring = &rdev->ring[TN_RING_TYPE_VCE2_INDEX];
	r = radeon_ring_init(rdev, ring, ring->ring_size, 0, 0x0);
	अगर (r) अणु
		dev_err(rdev->dev, "failed initializing VCE1 ring (%d).\n", r);
		वापस;
	पूर्ण
	r = vce_v1_0_init(rdev);
	अगर (r) अणु
		dev_err(rdev->dev, "failed initializing VCE (%d).\n", r);
		वापस;
	पूर्ण
पूर्ण

अटल पूर्णांक cayman_startup(काष्ठा radeon_device *rdev)
अणु
	काष्ठा radeon_ring *ring = &rdev->ring[RADEON_RING_TYPE_GFX_INDEX];
	पूर्णांक r;

	/* enable pcie gen2 link */
	evergreen_pcie_gen2_enable(rdev);
	/* enable aspm */
	evergreen_program_aspm(rdev);

	/* scratch needs to be initialized beक्रमe MC */
	r = r600_vram_scratch_init(rdev);
	अगर (r)
		वापस r;

	evergreen_mc_program(rdev);

	अगर (!(rdev->flags & RADEON_IS_IGP) && !rdev->pm.dpm_enabled) अणु
		r = ni_mc_load_microcode(rdev);
		अगर (r) अणु
			DRM_ERROR("Failed to load MC firmware!\n");
			वापस r;
		पूर्ण
	पूर्ण

	r = cayman_pcie_gart_enable(rdev);
	अगर (r)
		वापस r;
	cayman_gpu_init(rdev);

	/* allocate rlc buffers */
	अगर (rdev->flags & RADEON_IS_IGP) अणु
		rdev->rlc.reg_list = tn_rlc_save_restore_रेजिस्टर_list;
		rdev->rlc.reg_list_size =
			(u32)ARRAY_SIZE(tn_rlc_save_restore_रेजिस्टर_list);
		rdev->rlc.cs_data = cayman_cs_data;
		r = sumo_rlc_init(rdev);
		अगर (r) अणु
			DRM_ERROR("Failed to init rlc BOs!\n");
			वापस r;
		पूर्ण
	पूर्ण

	/* allocate wb buffer */
	r = radeon_wb_init(rdev);
	अगर (r)
		वापस r;

	r = radeon_fence_driver_start_ring(rdev, RADEON_RING_TYPE_GFX_INDEX);
	अगर (r) अणु
		dev_err(rdev->dev, "failed initializing CP fences (%d).\n", r);
		वापस r;
	पूर्ण

	cayman_uvd_start(rdev);
	cayman_vce_start(rdev);

	r = radeon_fence_driver_start_ring(rdev, CAYMAN_RING_TYPE_CP1_INDEX);
	अगर (r) अणु
		dev_err(rdev->dev, "failed initializing CP fences (%d).\n", r);
		वापस r;
	पूर्ण

	r = radeon_fence_driver_start_ring(rdev, CAYMAN_RING_TYPE_CP2_INDEX);
	अगर (r) अणु
		dev_err(rdev->dev, "failed initializing CP fences (%d).\n", r);
		वापस r;
	पूर्ण

	r = radeon_fence_driver_start_ring(rdev, R600_RING_TYPE_DMA_INDEX);
	अगर (r) अणु
		dev_err(rdev->dev, "failed initializing DMA fences (%d).\n", r);
		वापस r;
	पूर्ण

	r = radeon_fence_driver_start_ring(rdev, CAYMAN_RING_TYPE_DMA1_INDEX);
	अगर (r) अणु
		dev_err(rdev->dev, "failed initializing DMA fences (%d).\n", r);
		वापस r;
	पूर्ण

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
	evergreen_irq_set(rdev);

	r = radeon_ring_init(rdev, ring, ring->ring_size, RADEON_WB_CP_RPTR_OFFSET,
			     RADEON_CP_PACKET2);
	अगर (r)
		वापस r;

	ring = &rdev->ring[R600_RING_TYPE_DMA_INDEX];
	r = radeon_ring_init(rdev, ring, ring->ring_size, R600_WB_DMA_RPTR_OFFSET,
			     DMA_PACKET(DMA_PACKET_NOP, 0, 0, 0));
	अगर (r)
		वापस r;

	ring = &rdev->ring[CAYMAN_RING_TYPE_DMA1_INDEX];
	r = radeon_ring_init(rdev, ring, ring->ring_size, CAYMAN_WB_DMA1_RPTR_OFFSET,
			     DMA_PACKET(DMA_PACKET_NOP, 0, 0, 0));
	अगर (r)
		वापस r;

	r = cayman_cp_load_microcode(rdev);
	अगर (r)
		वापस r;
	r = cayman_cp_resume(rdev);
	अगर (r)
		वापस r;

	r = cayman_dma_resume(rdev);
	अगर (r)
		वापस r;

	cayman_uvd_resume(rdev);
	cayman_vce_resume(rdev);

	r = radeon_ib_pool_init(rdev);
	अगर (r) अणु
		dev_err(rdev->dev, "IB initialization failed (%d).\n", r);
		वापस r;
	पूर्ण

	r = radeon_vm_manager_init(rdev);
	अगर (r) अणु
		dev_err(rdev->dev, "vm manager initialization failed (%d).\n", r);
		वापस r;
	पूर्ण

	r = radeon_audio_init(rdev);
	अगर (r)
		वापस r;

	वापस 0;
पूर्ण

पूर्णांक cayman_resume(काष्ठा radeon_device *rdev)
अणु
	पूर्णांक r;

	/* Do not reset GPU beक्रमe posting, on rv770 hw unlike on r500 hw,
	 * posting will perक्रमm necessary task to bring back GPU पूर्णांकo good
	 * shape.
	 */
	/* post card */
	atom_asic_init(rdev->mode_info.atom_context);

	/* init golden रेजिस्टरs */
	ni_init_golden_रेजिस्टरs(rdev);

	अगर (rdev->pm.pm_method == PM_METHOD_DPM)
		radeon_pm_resume(rdev);

	rdev->accel_working = true;
	r = cayman_startup(rdev);
	अगर (r) अणु
		DRM_ERROR("cayman startup failed on resume\n");
		rdev->accel_working = false;
		वापस r;
	पूर्ण
	वापस r;
पूर्ण

पूर्णांक cayman_suspend(काष्ठा radeon_device *rdev)
अणु
	radeon_pm_suspend(rdev);
	radeon_audio_fini(rdev);
	radeon_vm_manager_fini(rdev);
	cayman_cp_enable(rdev, false);
	cayman_dma_stop(rdev);
	अगर (rdev->has_uvd) अणु
		uvd_v1_0_fini(rdev);
		radeon_uvd_suspend(rdev);
	पूर्ण
	evergreen_irq_suspend(rdev);
	radeon_wb_disable(rdev);
	cayman_pcie_gart_disable(rdev);
	वापस 0;
पूर्ण

/* Plan is to move initialization in that function and use
 * helper function so that radeon_device_init pretty much
 * करो nothing more than calling asic specअगरic function. This
 * should also allow to हटाओ a bunch of callback function
 * like vram_info.
 */
पूर्णांक cayman_init(काष्ठा radeon_device *rdev)
अणु
	काष्ठा radeon_ring *ring = &rdev->ring[RADEON_RING_TYPE_GFX_INDEX];
	पूर्णांक r;

	/* Read BIOS */
	अगर (!radeon_get_bios(rdev)) अणु
		अगर (ASIC_IS_AVIVO(rdev))
			वापस -EINVAL;
	पूर्ण
	/* Must be an ATOMBIOS */
	अगर (!rdev->is_atom_bios) अणु
		dev_err(rdev->dev, "Expecting atombios for cayman GPU\n");
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
	ni_init_golden_रेजिस्टरs(rdev);
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
	/* initialize memory controller */
	r = evergreen_mc_init(rdev);
	अगर (r)
		वापस r;
	/* Memory manager */
	r = radeon_bo_init(rdev);
	अगर (r)
		वापस r;

	अगर (rdev->flags & RADEON_IS_IGP) अणु
		अगर (!rdev->me_fw || !rdev->pfp_fw || !rdev->rlc_fw) अणु
			r = ni_init_microcode(rdev);
			अगर (r) अणु
				DRM_ERROR("Failed to load firmware!\n");
				वापस r;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (!rdev->me_fw || !rdev->pfp_fw || !rdev->rlc_fw || !rdev->mc_fw) अणु
			r = ni_init_microcode(rdev);
			अगर (r) अणु
				DRM_ERROR("Failed to load firmware!\n");
				वापस r;
			पूर्ण
		पूर्ण
	पूर्ण

	/* Initialize घातer management */
	radeon_pm_init(rdev);

	ring->ring_obj = शून्य;
	r600_ring_init(rdev, ring, 1024 * 1024);

	ring = &rdev->ring[R600_RING_TYPE_DMA_INDEX];
	ring->ring_obj = शून्य;
	r600_ring_init(rdev, ring, 64 * 1024);

	ring = &rdev->ring[CAYMAN_RING_TYPE_DMA1_INDEX];
	ring->ring_obj = शून्य;
	r600_ring_init(rdev, ring, 64 * 1024);

	cayman_uvd_init(rdev);
	cayman_vce_init(rdev);

	rdev->ih.ring_obj = शून्य;
	r600_ih_ring_init(rdev, 64 * 1024);

	r = r600_pcie_gart_init(rdev);
	अगर (r)
		वापस r;

	rdev->accel_working = true;
	r = cayman_startup(rdev);
	अगर (r) अणु
		dev_err(rdev->dev, "disabling GPU acceleration\n");
		cayman_cp_fini(rdev);
		cayman_dma_fini(rdev);
		r600_irq_fini(rdev);
		अगर (rdev->flags & RADEON_IS_IGP)
			sumo_rlc_fini(rdev);
		radeon_wb_fini(rdev);
		radeon_ib_pool_fini(rdev);
		radeon_vm_manager_fini(rdev);
		radeon_irq_kms_fini(rdev);
		cayman_pcie_gart_fini(rdev);
		rdev->accel_working = false;
	पूर्ण

	/* Don't start up अगर the MC ucode is missing.
	 * The शेष घड़ीs and voltages beक्रमe the MC ucode
	 * is loaded are not suffient क्रम advanced operations.
	 *
	 * We can skip this check क्रम TN, because there is no MC
	 * ucode.
	 */
	अगर (!rdev->mc_fw && !(rdev->flags & RADEON_IS_IGP)) अणु
		DRM_ERROR("radeon: MC ucode required for NI+.\n");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

व्योम cayman_fini(काष्ठा radeon_device *rdev)
अणु
	radeon_pm_fini(rdev);
	cayman_cp_fini(rdev);
	cayman_dma_fini(rdev);
	r600_irq_fini(rdev);
	अगर (rdev->flags & RADEON_IS_IGP)
		sumo_rlc_fini(rdev);
	radeon_wb_fini(rdev);
	radeon_vm_manager_fini(rdev);
	radeon_ib_pool_fini(rdev);
	radeon_irq_kms_fini(rdev);
	uvd_v1_0_fini(rdev);
	radeon_uvd_fini(rdev);
	अगर (rdev->has_vce)
		radeon_vce_fini(rdev);
	cayman_pcie_gart_fini(rdev);
	r600_vram_scratch_fini(rdev);
	radeon_gem_fini(rdev);
	radeon_fence_driver_fini(rdev);
	radeon_bo_fini(rdev);
	radeon_atombios_fini(rdev);
	kमुक्त(rdev->bios);
	rdev->bios = शून्य;
पूर्ण

/*
 * vm
 */
पूर्णांक cayman_vm_init(काष्ठा radeon_device *rdev)
अणु
	/* number of VMs */
	rdev->vm_manager.nvm = 8;
	/* base offset of vram pages */
	अगर (rdev->flags & RADEON_IS_IGP) अणु
		u64 पंचांगp = RREG32(FUS_MC_VM_FB_OFFSET);
		पंचांगp <<= 22;
		rdev->vm_manager.vram_base_offset = पंचांगp;
	पूर्ण अन्यथा
		rdev->vm_manager.vram_base_offset = 0;
	वापस 0;
पूर्ण

व्योम cayman_vm_fini(काष्ठा radeon_device *rdev)
अणु
पूर्ण

/**
 * cayman_vm_decode_fault - prपूर्णांक human पढ़ोable fault info
 *
 * @rdev: radeon_device poपूर्णांकer
 * @status: VM_CONTEXT1_PROTECTION_FAULT_STATUS रेजिस्टर value
 * @addr: VM_CONTEXT1_PROTECTION_FAULT_ADDR रेजिस्टर value
 *
 * Prपूर्णांक human पढ़ोable fault inक्रमmation (cayman/TN).
 */
व्योम cayman_vm_decode_fault(काष्ठा radeon_device *rdev,
			    u32 status, u32 addr)
अणु
	u32 mc_id = (status & MEMORY_CLIENT_ID_MASK) >> MEMORY_CLIENT_ID_SHIFT;
	u32 vmid = (status & FAULT_VMID_MASK) >> FAULT_VMID_SHIFT;
	u32 protections = (status & PROTECTIONS_MASK) >> PROTECTIONS_SHIFT;
	अक्षर *block;

	चयन (mc_id) अणु
	हाल 32:
	हाल 16:
	हाल 96:
	हाल 80:
	हाल 160:
	हाल 144:
	हाल 224:
	हाल 208:
		block = "CB";
		अवरोध;
	हाल 33:
	हाल 17:
	हाल 97:
	हाल 81:
	हाल 161:
	हाल 145:
	हाल 225:
	हाल 209:
		block = "CB_FMASK";
		अवरोध;
	हाल 34:
	हाल 18:
	हाल 98:
	हाल 82:
	हाल 162:
	हाल 146:
	हाल 226:
	हाल 210:
		block = "CB_CMASK";
		अवरोध;
	हाल 35:
	हाल 19:
	हाल 99:
	हाल 83:
	हाल 163:
	हाल 147:
	हाल 227:
	हाल 211:
		block = "CB_IMMED";
		अवरोध;
	हाल 36:
	हाल 20:
	हाल 100:
	हाल 84:
	हाल 164:
	हाल 148:
	हाल 228:
	हाल 212:
		block = "DB";
		अवरोध;
	हाल 37:
	हाल 21:
	हाल 101:
	हाल 85:
	हाल 165:
	हाल 149:
	हाल 229:
	हाल 213:
		block = "DB_HTILE";
		अवरोध;
	हाल 38:
	हाल 22:
	हाल 102:
	हाल 86:
	हाल 166:
	हाल 150:
	हाल 230:
	हाल 214:
		block = "SX";
		अवरोध;
	हाल 39:
	हाल 23:
	हाल 103:
	हाल 87:
	हाल 167:
	हाल 151:
	हाल 231:
	हाल 215:
		block = "DB_STEN";
		अवरोध;
	हाल 40:
	हाल 24:
	हाल 104:
	हाल 88:
	हाल 232:
	हाल 216:
	हाल 168:
	हाल 152:
		block = "TC_TFETCH";
		अवरोध;
	हाल 41:
	हाल 25:
	हाल 105:
	हाल 89:
	हाल 233:
	हाल 217:
	हाल 169:
	हाल 153:
		block = "TC_VFETCH";
		अवरोध;
	हाल 42:
	हाल 26:
	हाल 106:
	हाल 90:
	हाल 234:
	हाल 218:
	हाल 170:
	हाल 154:
		block = "VC";
		अवरोध;
	हाल 112:
		block = "CP";
		अवरोध;
	हाल 113:
	हाल 114:
		block = "SH";
		अवरोध;
	हाल 115:
		block = "VGT";
		अवरोध;
	हाल 178:
		block = "IH";
		अवरोध;
	हाल 51:
		block = "RLC";
		अवरोध;
	हाल 55:
		block = "DMA";
		अवरोध;
	हाल 56:
		block = "HDP";
		अवरोध;
	शेष:
		block = "unknown";
		अवरोध;
	पूर्ण

	prपूर्णांकk("VM fault (0x%02x, vmid %d) at page %u, %s from %s (%d)\n",
	       protections, vmid, addr,
	       (status & MEMORY_CLIENT_RW_MASK) ? "write" : "read",
	       block, mc_id);
पूर्ण

/*
 * cayman_vm_flush - vm flush using the CP
 *
 * Update the page table base and flush the VM TLB
 * using the CP (cayman-si).
 */
व्योम cayman_vm_flush(काष्ठा radeon_device *rdev, काष्ठा radeon_ring *ring,
		     अचिन्हित vm_id, uपूर्णांक64_t pd_addr)
अणु
	radeon_ring_ग_लिखो(ring, PACKET0(VM_CONTEXT0_PAGE_TABLE_BASE_ADDR + (vm_id << 2), 0));
	radeon_ring_ग_लिखो(ring, pd_addr >> 12);

	/* flush hdp cache */
	radeon_ring_ग_लिखो(ring, PACKET0(HDP_MEM_COHERENCY_FLUSH_CNTL, 0));
	radeon_ring_ग_लिखो(ring, 0x1);

	/* bits 0-7 are the VM contexts0-7 */
	radeon_ring_ग_लिखो(ring, PACKET0(VM_INVALIDATE_REQUEST, 0));
	radeon_ring_ग_लिखो(ring, 1 << vm_id);

	/* रुको क्रम the invalidate to complete */
	radeon_ring_ग_लिखो(ring, PACKET3(PACKET3_WAIT_REG_MEM, 5));
	radeon_ring_ग_लिखो(ring, (WAIT_REG_MEM_FUNCTION(0) |  /* always */
				 WAIT_REG_MEM_ENGINE(0))); /* me */
	radeon_ring_ग_लिखो(ring, VM_INVALIDATE_REQUEST >> 2);
	radeon_ring_ग_लिखो(ring, 0);
	radeon_ring_ग_लिखो(ring, 0); /* ref */
	radeon_ring_ग_लिखो(ring, 0); /* mask */
	radeon_ring_ग_लिखो(ring, 0x20); /* poll पूर्णांकerval */

	/* sync PFP to ME, otherwise we might get invalid PFP पढ़ोs */
	radeon_ring_ग_लिखो(ring, PACKET3(PACKET3_PFP_SYNC_ME, 0));
	radeon_ring_ग_लिखो(ring, 0x0);
पूर्ण

पूर्णांक tn_set_vce_घड़ीs(काष्ठा radeon_device *rdev, u32 evclk, u32 ecclk)
अणु
	काष्ठा atom_घड़ी_भागiders भागiders;
	पूर्णांक r, i;

	r = radeon_atom_get_घड़ी_भागiders(rdev, COMPUTE_ENGINE_PLL_PARAM,
					   ecclk, false, &भागiders);
	अगर (r)
		वापस r;

	क्रम (i = 0; i < 100; i++) अणु
		अगर (RREG32(CG_ECLK_STATUS) & ECLK_STATUS)
			अवरोध;
		mdelay(10);
	पूर्ण
	अगर (i == 100)
		वापस -ETIMEDOUT;

	WREG32_P(CG_ECLK_CNTL, भागiders.post_भाग, ~(ECLK_सूची_CNTL_EN|ECLK_DIVIDER_MASK));

	क्रम (i = 0; i < 100; i++) अणु
		अगर (RREG32(CG_ECLK_STATUS) & ECLK_STATUS)
			अवरोध;
		mdelay(10);
	पूर्ण
	अगर (i == 100)
		वापस -ETIMEDOUT;

	वापस 0;
पूर्ण
