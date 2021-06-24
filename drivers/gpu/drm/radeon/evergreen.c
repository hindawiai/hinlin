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
#समावेश <linux/pci.h>
#समावेश <linux/slab.h>

#समावेश <drm/drm_vblank.h>
#समावेश <drm/radeon_drm.h>

#समावेश "atom.h"
#समावेश "avivod.h"
#समावेश "cik.h"
#समावेश "ni.h"
#समावेश "rv770.h"
#समावेश "evergreen.h"
#समावेश "evergreen_blit_shaders.h"
#समावेश "evergreen_reg.h"
#समावेश "evergreend.h"
#समावेश "radeon.h"
#समावेश "radeon_asic.h"
#समावेश "radeon_audio.h"
#समावेश "radeon_ucode.h"
#समावेश "si.h"

#घोषणा DC_HPDx_CONTROL(x)        (DC_HPD1_CONTROL     + (x * 0xc))
#घोषणा DC_HPDx_INT_CONTROL(x)    (DC_HPD1_INT_CONTROL + (x * 0xc))
#घोषणा DC_HPDx_INT_STATUS_REG(x) (DC_HPD1_INT_STATUS  + (x * 0xc))

/*
 * Indirect रेजिस्टरs accessor
 */
u32 eg_cg_rreg(काष्ठा radeon_device *rdev, u32 reg)
अणु
	अचिन्हित दीर्घ flags;
	u32 r;

	spin_lock_irqsave(&rdev->cg_idx_lock, flags);
	WREG32(EVERGREEN_CG_IND_ADDR, ((reg) & 0xffff));
	r = RREG32(EVERGREEN_CG_IND_DATA);
	spin_unlock_irqrestore(&rdev->cg_idx_lock, flags);
	वापस r;
पूर्ण

व्योम eg_cg_wreg(काष्ठा radeon_device *rdev, u32 reg, u32 v)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&rdev->cg_idx_lock, flags);
	WREG32(EVERGREEN_CG_IND_ADDR, ((reg) & 0xffff));
	WREG32(EVERGREEN_CG_IND_DATA, (v));
	spin_unlock_irqrestore(&rdev->cg_idx_lock, flags);
पूर्ण

u32 eg_pअगर_phy0_rreg(काष्ठा radeon_device *rdev, u32 reg)
अणु
	अचिन्हित दीर्घ flags;
	u32 r;

	spin_lock_irqsave(&rdev->pअगर_idx_lock, flags);
	WREG32(EVERGREEN_PIF_PHY0_INDEX, ((reg) & 0xffff));
	r = RREG32(EVERGREEN_PIF_PHY0_DATA);
	spin_unlock_irqrestore(&rdev->pअगर_idx_lock, flags);
	वापस r;
पूर्ण

व्योम eg_pअगर_phy0_wreg(काष्ठा radeon_device *rdev, u32 reg, u32 v)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&rdev->pअगर_idx_lock, flags);
	WREG32(EVERGREEN_PIF_PHY0_INDEX, ((reg) & 0xffff));
	WREG32(EVERGREEN_PIF_PHY0_DATA, (v));
	spin_unlock_irqrestore(&rdev->pअगर_idx_lock, flags);
पूर्ण

u32 eg_pअगर_phy1_rreg(काष्ठा radeon_device *rdev, u32 reg)
अणु
	अचिन्हित दीर्घ flags;
	u32 r;

	spin_lock_irqsave(&rdev->pअगर_idx_lock, flags);
	WREG32(EVERGREEN_PIF_PHY1_INDEX, ((reg) & 0xffff));
	r = RREG32(EVERGREEN_PIF_PHY1_DATA);
	spin_unlock_irqrestore(&rdev->pअगर_idx_lock, flags);
	वापस r;
पूर्ण

व्योम eg_pअगर_phy1_wreg(काष्ठा radeon_device *rdev, u32 reg, u32 v)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&rdev->pअगर_idx_lock, flags);
	WREG32(EVERGREEN_PIF_PHY1_INDEX, ((reg) & 0xffff));
	WREG32(EVERGREEN_PIF_PHY1_DATA, (v));
	spin_unlock_irqrestore(&rdev->pअगर_idx_lock, flags);
पूर्ण

अटल स्थिर u32 crtc_offsets[6] =
अणु
	EVERGREEN_CRTC0_REGISTER_OFFSET,
	EVERGREEN_CRTC1_REGISTER_OFFSET,
	EVERGREEN_CRTC2_REGISTER_OFFSET,
	EVERGREEN_CRTC3_REGISTER_OFFSET,
	EVERGREEN_CRTC4_REGISTER_OFFSET,
	EVERGREEN_CRTC5_REGISTER_OFFSET
पूर्ण;

#समावेश "clearstate_evergreen.h"

अटल स्थिर u32 sumo_rlc_save_restore_रेजिस्टर_list[] =
अणु
	0x98fc,
	0x9830,
	0x9834,
	0x9838,
	0x9870,
	0x9874,
	0x8a14,
	0x8b24,
	0x8bcc,
	0x8b10,
	0x8d00,
	0x8d04,
	0x8c00,
	0x8c04,
	0x8c08,
	0x8c0c,
	0x8d8c,
	0x8c20,
	0x8c24,
	0x8c28,
	0x8c18,
	0x8c1c,
	0x8cf0,
	0x8e2c,
	0x8e38,
	0x8c30,
	0x9508,
	0x9688,
	0x9608,
	0x960c,
	0x9610,
	0x9614,
	0x88c4,
	0x88d4,
	0xa008,
	0x900c,
	0x9100,
	0x913c,
	0x98f8,
	0x98f4,
	0x9b7c,
	0x3f8c,
	0x8950,
	0x8954,
	0x8a18,
	0x8b28,
	0x9144,
	0x9148,
	0x914c,
	0x3f90,
	0x3f94,
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
	0x9150,
	0x802c,
पूर्ण;

अटल व्योम evergreen_gpu_init(काष्ठा radeon_device *rdev);
व्योम evergreen_fini(काष्ठा radeon_device *rdev);
व्योम evergreen_pcie_gen2_enable(काष्ठा radeon_device *rdev);
व्योम evergreen_program_aspm(काष्ठा radeon_device *rdev);

अटल स्थिर u32 evergreen_golden_रेजिस्टरs[] =
अणु
	0x3f90, 0xffff0000, 0xff000000,
	0x9148, 0xffff0000, 0xff000000,
	0x3f94, 0xffff0000, 0xff000000,
	0x914c, 0xffff0000, 0xff000000,
	0x9b7c, 0xffffffff, 0x00000000,
	0x8a14, 0xffffffff, 0x00000007,
	0x8b10, 0xffffffff, 0x00000000,
	0x960c, 0xffffffff, 0x54763210,
	0x88c4, 0xffffffff, 0x000000c2,
	0x88d4, 0xffffffff, 0x00000010,
	0x8974, 0xffffffff, 0x00000000,
	0xc78, 0x00000080, 0x00000080,
	0x5eb4, 0xffffffff, 0x00000002,
	0x5e78, 0xffffffff, 0x001000f0,
	0x6104, 0x01000300, 0x00000000,
	0x5bc0, 0x00300000, 0x00000000,
	0x7030, 0xffffffff, 0x00000011,
	0x7c30, 0xffffffff, 0x00000011,
	0x10830, 0xffffffff, 0x00000011,
	0x11430, 0xffffffff, 0x00000011,
	0x12030, 0xffffffff, 0x00000011,
	0x12c30, 0xffffffff, 0x00000011,
	0xd02c, 0xffffffff, 0x08421000,
	0x240c, 0xffffffff, 0x00000380,
	0x8b24, 0xffffffff, 0x00ff0fff,
	0x28a4c, 0x06000000, 0x06000000,
	0x10c, 0x00000001, 0x00000001,
	0x8d00, 0xffffffff, 0x100e4848,
	0x8d04, 0xffffffff, 0x00164745,
	0x8c00, 0xffffffff, 0xe4000003,
	0x8c04, 0xffffffff, 0x40600060,
	0x8c08, 0xffffffff, 0x001c001c,
	0x8cf0, 0xffffffff, 0x08e00620,
	0x8c20, 0xffffffff, 0x00800080,
	0x8c24, 0xffffffff, 0x00800080,
	0x8c18, 0xffffffff, 0x20202078,
	0x8c1c, 0xffffffff, 0x00001010,
	0x28350, 0xffffffff, 0x00000000,
	0xa008, 0xffffffff, 0x00010000,
	0x5c4, 0xffffffff, 0x00000001,
	0x9508, 0xffffffff, 0x00000002,
	0x913c, 0x0000000f, 0x0000000a
पूर्ण;

अटल स्थिर u32 evergreen_golden_रेजिस्टरs2[] =
अणु
	0x2f4c, 0xffffffff, 0x00000000,
	0x54f4, 0xffffffff, 0x00000000,
	0x54f0, 0xffffffff, 0x00000000,
	0x5498, 0xffffffff, 0x00000000,
	0x549c, 0xffffffff, 0x00000000,
	0x5494, 0xffffffff, 0x00000000,
	0x53cc, 0xffffffff, 0x00000000,
	0x53c8, 0xffffffff, 0x00000000,
	0x53c4, 0xffffffff, 0x00000000,
	0x53c0, 0xffffffff, 0x00000000,
	0x53bc, 0xffffffff, 0x00000000,
	0x53b8, 0xffffffff, 0x00000000,
	0x53b4, 0xffffffff, 0x00000000,
	0x53b0, 0xffffffff, 0x00000000
पूर्ण;

अटल स्थिर u32 cypress_mgcg_init[] =
अणु
	0x802c, 0xffffffff, 0xc0000000,
	0x5448, 0xffffffff, 0x00000100,
	0x55e4, 0xffffffff, 0x00000100,
	0x160c, 0xffffffff, 0x00000100,
	0x5644, 0xffffffff, 0x00000100,
	0xc164, 0xffffffff, 0x00000100,
	0x8a18, 0xffffffff, 0x00000100,
	0x897c, 0xffffffff, 0x06000100,
	0x8b28, 0xffffffff, 0x00000100,
	0x9144, 0xffffffff, 0x00000100,
	0x9a60, 0xffffffff, 0x00000100,
	0x9868, 0xffffffff, 0x00000100,
	0x8d58, 0xffffffff, 0x00000100,
	0x9510, 0xffffffff, 0x00000100,
	0x949c, 0xffffffff, 0x00000100,
	0x9654, 0xffffffff, 0x00000100,
	0x9030, 0xffffffff, 0x00000100,
	0x9034, 0xffffffff, 0x00000100,
	0x9038, 0xffffffff, 0x00000100,
	0x903c, 0xffffffff, 0x00000100,
	0x9040, 0xffffffff, 0x00000100,
	0xa200, 0xffffffff, 0x00000100,
	0xa204, 0xffffffff, 0x00000100,
	0xa208, 0xffffffff, 0x00000100,
	0xa20c, 0xffffffff, 0x00000100,
	0x971c, 0xffffffff, 0x00000100,
	0x977c, 0xffffffff, 0x00000100,
	0x3f80, 0xffffffff, 0x00000100,
	0xa210, 0xffffffff, 0x00000100,
	0xa214, 0xffffffff, 0x00000100,
	0x4d8, 0xffffffff, 0x00000100,
	0x9784, 0xffffffff, 0x00000100,
	0x9698, 0xffffffff, 0x00000100,
	0x4d4, 0xffffffff, 0x00000200,
	0x30cc, 0xffffffff, 0x00000100,
	0xd0c0, 0xffffffff, 0xff000100,
	0x802c, 0xffffffff, 0x40000000,
	0x915c, 0xffffffff, 0x00010000,
	0x9160, 0xffffffff, 0x00030002,
	0x9178, 0xffffffff, 0x00070000,
	0x917c, 0xffffffff, 0x00030002,
	0x9180, 0xffffffff, 0x00050004,
	0x918c, 0xffffffff, 0x00010006,
	0x9190, 0xffffffff, 0x00090008,
	0x9194, 0xffffffff, 0x00070000,
	0x9198, 0xffffffff, 0x00030002,
	0x919c, 0xffffffff, 0x00050004,
	0x91a8, 0xffffffff, 0x00010006,
	0x91ac, 0xffffffff, 0x00090008,
	0x91b0, 0xffffffff, 0x00070000,
	0x91b4, 0xffffffff, 0x00030002,
	0x91b8, 0xffffffff, 0x00050004,
	0x91c4, 0xffffffff, 0x00010006,
	0x91c8, 0xffffffff, 0x00090008,
	0x91cc, 0xffffffff, 0x00070000,
	0x91d0, 0xffffffff, 0x00030002,
	0x91d4, 0xffffffff, 0x00050004,
	0x91e0, 0xffffffff, 0x00010006,
	0x91e4, 0xffffffff, 0x00090008,
	0x91e8, 0xffffffff, 0x00000000,
	0x91ec, 0xffffffff, 0x00070000,
	0x91f0, 0xffffffff, 0x00030002,
	0x91f4, 0xffffffff, 0x00050004,
	0x9200, 0xffffffff, 0x00010006,
	0x9204, 0xffffffff, 0x00090008,
	0x9208, 0xffffffff, 0x00070000,
	0x920c, 0xffffffff, 0x00030002,
	0x9210, 0xffffffff, 0x00050004,
	0x921c, 0xffffffff, 0x00010006,
	0x9220, 0xffffffff, 0x00090008,
	0x9224, 0xffffffff, 0x00070000,
	0x9228, 0xffffffff, 0x00030002,
	0x922c, 0xffffffff, 0x00050004,
	0x9238, 0xffffffff, 0x00010006,
	0x923c, 0xffffffff, 0x00090008,
	0x9240, 0xffffffff, 0x00070000,
	0x9244, 0xffffffff, 0x00030002,
	0x9248, 0xffffffff, 0x00050004,
	0x9254, 0xffffffff, 0x00010006,
	0x9258, 0xffffffff, 0x00090008,
	0x925c, 0xffffffff, 0x00070000,
	0x9260, 0xffffffff, 0x00030002,
	0x9264, 0xffffffff, 0x00050004,
	0x9270, 0xffffffff, 0x00010006,
	0x9274, 0xffffffff, 0x00090008,
	0x9278, 0xffffffff, 0x00070000,
	0x927c, 0xffffffff, 0x00030002,
	0x9280, 0xffffffff, 0x00050004,
	0x928c, 0xffffffff, 0x00010006,
	0x9290, 0xffffffff, 0x00090008,
	0x9294, 0xffffffff, 0x00000000,
	0x929c, 0xffffffff, 0x00000001,
	0x802c, 0xffffffff, 0x40010000,
	0x915c, 0xffffffff, 0x00010000,
	0x9160, 0xffffffff, 0x00030002,
	0x9178, 0xffffffff, 0x00070000,
	0x917c, 0xffffffff, 0x00030002,
	0x9180, 0xffffffff, 0x00050004,
	0x918c, 0xffffffff, 0x00010006,
	0x9190, 0xffffffff, 0x00090008,
	0x9194, 0xffffffff, 0x00070000,
	0x9198, 0xffffffff, 0x00030002,
	0x919c, 0xffffffff, 0x00050004,
	0x91a8, 0xffffffff, 0x00010006,
	0x91ac, 0xffffffff, 0x00090008,
	0x91b0, 0xffffffff, 0x00070000,
	0x91b4, 0xffffffff, 0x00030002,
	0x91b8, 0xffffffff, 0x00050004,
	0x91c4, 0xffffffff, 0x00010006,
	0x91c8, 0xffffffff, 0x00090008,
	0x91cc, 0xffffffff, 0x00070000,
	0x91d0, 0xffffffff, 0x00030002,
	0x91d4, 0xffffffff, 0x00050004,
	0x91e0, 0xffffffff, 0x00010006,
	0x91e4, 0xffffffff, 0x00090008,
	0x91e8, 0xffffffff, 0x00000000,
	0x91ec, 0xffffffff, 0x00070000,
	0x91f0, 0xffffffff, 0x00030002,
	0x91f4, 0xffffffff, 0x00050004,
	0x9200, 0xffffffff, 0x00010006,
	0x9204, 0xffffffff, 0x00090008,
	0x9208, 0xffffffff, 0x00070000,
	0x920c, 0xffffffff, 0x00030002,
	0x9210, 0xffffffff, 0x00050004,
	0x921c, 0xffffffff, 0x00010006,
	0x9220, 0xffffffff, 0x00090008,
	0x9224, 0xffffffff, 0x00070000,
	0x9228, 0xffffffff, 0x00030002,
	0x922c, 0xffffffff, 0x00050004,
	0x9238, 0xffffffff, 0x00010006,
	0x923c, 0xffffffff, 0x00090008,
	0x9240, 0xffffffff, 0x00070000,
	0x9244, 0xffffffff, 0x00030002,
	0x9248, 0xffffffff, 0x00050004,
	0x9254, 0xffffffff, 0x00010006,
	0x9258, 0xffffffff, 0x00090008,
	0x925c, 0xffffffff, 0x00070000,
	0x9260, 0xffffffff, 0x00030002,
	0x9264, 0xffffffff, 0x00050004,
	0x9270, 0xffffffff, 0x00010006,
	0x9274, 0xffffffff, 0x00090008,
	0x9278, 0xffffffff, 0x00070000,
	0x927c, 0xffffffff, 0x00030002,
	0x9280, 0xffffffff, 0x00050004,
	0x928c, 0xffffffff, 0x00010006,
	0x9290, 0xffffffff, 0x00090008,
	0x9294, 0xffffffff, 0x00000000,
	0x929c, 0xffffffff, 0x00000001,
	0x802c, 0xffffffff, 0xc0000000
पूर्ण;

अटल स्थिर u32 redwood_mgcg_init[] =
अणु
	0x802c, 0xffffffff, 0xc0000000,
	0x5448, 0xffffffff, 0x00000100,
	0x55e4, 0xffffffff, 0x00000100,
	0x160c, 0xffffffff, 0x00000100,
	0x5644, 0xffffffff, 0x00000100,
	0xc164, 0xffffffff, 0x00000100,
	0x8a18, 0xffffffff, 0x00000100,
	0x897c, 0xffffffff, 0x06000100,
	0x8b28, 0xffffffff, 0x00000100,
	0x9144, 0xffffffff, 0x00000100,
	0x9a60, 0xffffffff, 0x00000100,
	0x9868, 0xffffffff, 0x00000100,
	0x8d58, 0xffffffff, 0x00000100,
	0x9510, 0xffffffff, 0x00000100,
	0x949c, 0xffffffff, 0x00000100,
	0x9654, 0xffffffff, 0x00000100,
	0x9030, 0xffffffff, 0x00000100,
	0x9034, 0xffffffff, 0x00000100,
	0x9038, 0xffffffff, 0x00000100,
	0x903c, 0xffffffff, 0x00000100,
	0x9040, 0xffffffff, 0x00000100,
	0xa200, 0xffffffff, 0x00000100,
	0xa204, 0xffffffff, 0x00000100,
	0xa208, 0xffffffff, 0x00000100,
	0xa20c, 0xffffffff, 0x00000100,
	0x971c, 0xffffffff, 0x00000100,
	0x977c, 0xffffffff, 0x00000100,
	0x3f80, 0xffffffff, 0x00000100,
	0xa210, 0xffffffff, 0x00000100,
	0xa214, 0xffffffff, 0x00000100,
	0x4d8, 0xffffffff, 0x00000100,
	0x9784, 0xffffffff, 0x00000100,
	0x9698, 0xffffffff, 0x00000100,
	0x4d4, 0xffffffff, 0x00000200,
	0x30cc, 0xffffffff, 0x00000100,
	0xd0c0, 0xffffffff, 0xff000100,
	0x802c, 0xffffffff, 0x40000000,
	0x915c, 0xffffffff, 0x00010000,
	0x9160, 0xffffffff, 0x00030002,
	0x9178, 0xffffffff, 0x00070000,
	0x917c, 0xffffffff, 0x00030002,
	0x9180, 0xffffffff, 0x00050004,
	0x918c, 0xffffffff, 0x00010006,
	0x9190, 0xffffffff, 0x00090008,
	0x9194, 0xffffffff, 0x00070000,
	0x9198, 0xffffffff, 0x00030002,
	0x919c, 0xffffffff, 0x00050004,
	0x91a8, 0xffffffff, 0x00010006,
	0x91ac, 0xffffffff, 0x00090008,
	0x91b0, 0xffffffff, 0x00070000,
	0x91b4, 0xffffffff, 0x00030002,
	0x91b8, 0xffffffff, 0x00050004,
	0x91c4, 0xffffffff, 0x00010006,
	0x91c8, 0xffffffff, 0x00090008,
	0x91cc, 0xffffffff, 0x00070000,
	0x91d0, 0xffffffff, 0x00030002,
	0x91d4, 0xffffffff, 0x00050004,
	0x91e0, 0xffffffff, 0x00010006,
	0x91e4, 0xffffffff, 0x00090008,
	0x91e8, 0xffffffff, 0x00000000,
	0x91ec, 0xffffffff, 0x00070000,
	0x91f0, 0xffffffff, 0x00030002,
	0x91f4, 0xffffffff, 0x00050004,
	0x9200, 0xffffffff, 0x00010006,
	0x9204, 0xffffffff, 0x00090008,
	0x9294, 0xffffffff, 0x00000000,
	0x929c, 0xffffffff, 0x00000001,
	0x802c, 0xffffffff, 0xc0000000
पूर्ण;

अटल स्थिर u32 cedar_golden_रेजिस्टरs[] =
अणु
	0x3f90, 0xffff0000, 0xff000000,
	0x9148, 0xffff0000, 0xff000000,
	0x3f94, 0xffff0000, 0xff000000,
	0x914c, 0xffff0000, 0xff000000,
	0x9b7c, 0xffffffff, 0x00000000,
	0x8a14, 0xffffffff, 0x00000007,
	0x8b10, 0xffffffff, 0x00000000,
	0x960c, 0xffffffff, 0x54763210,
	0x88c4, 0xffffffff, 0x000000c2,
	0x88d4, 0xffffffff, 0x00000000,
	0x8974, 0xffffffff, 0x00000000,
	0xc78, 0x00000080, 0x00000080,
	0x5eb4, 0xffffffff, 0x00000002,
	0x5e78, 0xffffffff, 0x001000f0,
	0x6104, 0x01000300, 0x00000000,
	0x5bc0, 0x00300000, 0x00000000,
	0x7030, 0xffffffff, 0x00000011,
	0x7c30, 0xffffffff, 0x00000011,
	0x10830, 0xffffffff, 0x00000011,
	0x11430, 0xffffffff, 0x00000011,
	0xd02c, 0xffffffff, 0x08421000,
	0x240c, 0xffffffff, 0x00000380,
	0x8b24, 0xffffffff, 0x00ff0fff,
	0x28a4c, 0x06000000, 0x06000000,
	0x10c, 0x00000001, 0x00000001,
	0x8d00, 0xffffffff, 0x100e4848,
	0x8d04, 0xffffffff, 0x00164745,
	0x8c00, 0xffffffff, 0xe4000003,
	0x8c04, 0xffffffff, 0x40600060,
	0x8c08, 0xffffffff, 0x001c001c,
	0x8cf0, 0xffffffff, 0x08e00410,
	0x8c20, 0xffffffff, 0x00800080,
	0x8c24, 0xffffffff, 0x00800080,
	0x8c18, 0xffffffff, 0x20202078,
	0x8c1c, 0xffffffff, 0x00001010,
	0x28350, 0xffffffff, 0x00000000,
	0xa008, 0xffffffff, 0x00010000,
	0x5c4, 0xffffffff, 0x00000001,
	0x9508, 0xffffffff, 0x00000002
पूर्ण;

अटल स्थिर u32 cedar_mgcg_init[] =
अणु
	0x802c, 0xffffffff, 0xc0000000,
	0x5448, 0xffffffff, 0x00000100,
	0x55e4, 0xffffffff, 0x00000100,
	0x160c, 0xffffffff, 0x00000100,
	0x5644, 0xffffffff, 0x00000100,
	0xc164, 0xffffffff, 0x00000100,
	0x8a18, 0xffffffff, 0x00000100,
	0x897c, 0xffffffff, 0x06000100,
	0x8b28, 0xffffffff, 0x00000100,
	0x9144, 0xffffffff, 0x00000100,
	0x9a60, 0xffffffff, 0x00000100,
	0x9868, 0xffffffff, 0x00000100,
	0x8d58, 0xffffffff, 0x00000100,
	0x9510, 0xffffffff, 0x00000100,
	0x949c, 0xffffffff, 0x00000100,
	0x9654, 0xffffffff, 0x00000100,
	0x9030, 0xffffffff, 0x00000100,
	0x9034, 0xffffffff, 0x00000100,
	0x9038, 0xffffffff, 0x00000100,
	0x903c, 0xffffffff, 0x00000100,
	0x9040, 0xffffffff, 0x00000100,
	0xa200, 0xffffffff, 0x00000100,
	0xa204, 0xffffffff, 0x00000100,
	0xa208, 0xffffffff, 0x00000100,
	0xa20c, 0xffffffff, 0x00000100,
	0x971c, 0xffffffff, 0x00000100,
	0x977c, 0xffffffff, 0x00000100,
	0x3f80, 0xffffffff, 0x00000100,
	0xa210, 0xffffffff, 0x00000100,
	0xa214, 0xffffffff, 0x00000100,
	0x4d8, 0xffffffff, 0x00000100,
	0x9784, 0xffffffff, 0x00000100,
	0x9698, 0xffffffff, 0x00000100,
	0x4d4, 0xffffffff, 0x00000200,
	0x30cc, 0xffffffff, 0x00000100,
	0xd0c0, 0xffffffff, 0xff000100,
	0x802c, 0xffffffff, 0x40000000,
	0x915c, 0xffffffff, 0x00010000,
	0x9178, 0xffffffff, 0x00050000,
	0x917c, 0xffffffff, 0x00030002,
	0x918c, 0xffffffff, 0x00010004,
	0x9190, 0xffffffff, 0x00070006,
	0x9194, 0xffffffff, 0x00050000,
	0x9198, 0xffffffff, 0x00030002,
	0x91a8, 0xffffffff, 0x00010004,
	0x91ac, 0xffffffff, 0x00070006,
	0x91e8, 0xffffffff, 0x00000000,
	0x9294, 0xffffffff, 0x00000000,
	0x929c, 0xffffffff, 0x00000001,
	0x802c, 0xffffffff, 0xc0000000
पूर्ण;

अटल स्थिर u32 juniper_mgcg_init[] =
अणु
	0x802c, 0xffffffff, 0xc0000000,
	0x5448, 0xffffffff, 0x00000100,
	0x55e4, 0xffffffff, 0x00000100,
	0x160c, 0xffffffff, 0x00000100,
	0x5644, 0xffffffff, 0x00000100,
	0xc164, 0xffffffff, 0x00000100,
	0x8a18, 0xffffffff, 0x00000100,
	0x897c, 0xffffffff, 0x06000100,
	0x8b28, 0xffffffff, 0x00000100,
	0x9144, 0xffffffff, 0x00000100,
	0x9a60, 0xffffffff, 0x00000100,
	0x9868, 0xffffffff, 0x00000100,
	0x8d58, 0xffffffff, 0x00000100,
	0x9510, 0xffffffff, 0x00000100,
	0x949c, 0xffffffff, 0x00000100,
	0x9654, 0xffffffff, 0x00000100,
	0x9030, 0xffffffff, 0x00000100,
	0x9034, 0xffffffff, 0x00000100,
	0x9038, 0xffffffff, 0x00000100,
	0x903c, 0xffffffff, 0x00000100,
	0x9040, 0xffffffff, 0x00000100,
	0xa200, 0xffffffff, 0x00000100,
	0xa204, 0xffffffff, 0x00000100,
	0xa208, 0xffffffff, 0x00000100,
	0xa20c, 0xffffffff, 0x00000100,
	0x971c, 0xffffffff, 0x00000100,
	0xd0c0, 0xffffffff, 0xff000100,
	0x802c, 0xffffffff, 0x40000000,
	0x915c, 0xffffffff, 0x00010000,
	0x9160, 0xffffffff, 0x00030002,
	0x9178, 0xffffffff, 0x00070000,
	0x917c, 0xffffffff, 0x00030002,
	0x9180, 0xffffffff, 0x00050004,
	0x918c, 0xffffffff, 0x00010006,
	0x9190, 0xffffffff, 0x00090008,
	0x9194, 0xffffffff, 0x00070000,
	0x9198, 0xffffffff, 0x00030002,
	0x919c, 0xffffffff, 0x00050004,
	0x91a8, 0xffffffff, 0x00010006,
	0x91ac, 0xffffffff, 0x00090008,
	0x91b0, 0xffffffff, 0x00070000,
	0x91b4, 0xffffffff, 0x00030002,
	0x91b8, 0xffffffff, 0x00050004,
	0x91c4, 0xffffffff, 0x00010006,
	0x91c8, 0xffffffff, 0x00090008,
	0x91cc, 0xffffffff, 0x00070000,
	0x91d0, 0xffffffff, 0x00030002,
	0x91d4, 0xffffffff, 0x00050004,
	0x91e0, 0xffffffff, 0x00010006,
	0x91e4, 0xffffffff, 0x00090008,
	0x91e8, 0xffffffff, 0x00000000,
	0x91ec, 0xffffffff, 0x00070000,
	0x91f0, 0xffffffff, 0x00030002,
	0x91f4, 0xffffffff, 0x00050004,
	0x9200, 0xffffffff, 0x00010006,
	0x9204, 0xffffffff, 0x00090008,
	0x9208, 0xffffffff, 0x00070000,
	0x920c, 0xffffffff, 0x00030002,
	0x9210, 0xffffffff, 0x00050004,
	0x921c, 0xffffffff, 0x00010006,
	0x9220, 0xffffffff, 0x00090008,
	0x9224, 0xffffffff, 0x00070000,
	0x9228, 0xffffffff, 0x00030002,
	0x922c, 0xffffffff, 0x00050004,
	0x9238, 0xffffffff, 0x00010006,
	0x923c, 0xffffffff, 0x00090008,
	0x9240, 0xffffffff, 0x00070000,
	0x9244, 0xffffffff, 0x00030002,
	0x9248, 0xffffffff, 0x00050004,
	0x9254, 0xffffffff, 0x00010006,
	0x9258, 0xffffffff, 0x00090008,
	0x925c, 0xffffffff, 0x00070000,
	0x9260, 0xffffffff, 0x00030002,
	0x9264, 0xffffffff, 0x00050004,
	0x9270, 0xffffffff, 0x00010006,
	0x9274, 0xffffffff, 0x00090008,
	0x9278, 0xffffffff, 0x00070000,
	0x927c, 0xffffffff, 0x00030002,
	0x9280, 0xffffffff, 0x00050004,
	0x928c, 0xffffffff, 0x00010006,
	0x9290, 0xffffffff, 0x00090008,
	0x9294, 0xffffffff, 0x00000000,
	0x929c, 0xffffffff, 0x00000001,
	0x802c, 0xffffffff, 0xc0000000,
	0x977c, 0xffffffff, 0x00000100,
	0x3f80, 0xffffffff, 0x00000100,
	0xa210, 0xffffffff, 0x00000100,
	0xa214, 0xffffffff, 0x00000100,
	0x4d8, 0xffffffff, 0x00000100,
	0x9784, 0xffffffff, 0x00000100,
	0x9698, 0xffffffff, 0x00000100,
	0x4d4, 0xffffffff, 0x00000200,
	0x30cc, 0xffffffff, 0x00000100,
	0x802c, 0xffffffff, 0xc0000000
पूर्ण;

अटल स्थिर u32 supersumo_golden_रेजिस्टरs[] =
अणु
	0x5eb4, 0xffffffff, 0x00000002,
	0x5c4, 0xffffffff, 0x00000001,
	0x7030, 0xffffffff, 0x00000011,
	0x7c30, 0xffffffff, 0x00000011,
	0x6104, 0x01000300, 0x00000000,
	0x5bc0, 0x00300000, 0x00000000,
	0x8c04, 0xffffffff, 0x40600060,
	0x8c08, 0xffffffff, 0x001c001c,
	0x8c20, 0xffffffff, 0x00800080,
	0x8c24, 0xffffffff, 0x00800080,
	0x8c18, 0xffffffff, 0x20202078,
	0x8c1c, 0xffffffff, 0x00001010,
	0x918c, 0xffffffff, 0x00010006,
	0x91a8, 0xffffffff, 0x00010006,
	0x91c4, 0xffffffff, 0x00010006,
	0x91e0, 0xffffffff, 0x00010006,
	0x9200, 0xffffffff, 0x00010006,
	0x9150, 0xffffffff, 0x6e944040,
	0x917c, 0xffffffff, 0x00030002,
	0x9180, 0xffffffff, 0x00050004,
	0x9198, 0xffffffff, 0x00030002,
	0x919c, 0xffffffff, 0x00050004,
	0x91b4, 0xffffffff, 0x00030002,
	0x91b8, 0xffffffff, 0x00050004,
	0x91d0, 0xffffffff, 0x00030002,
	0x91d4, 0xffffffff, 0x00050004,
	0x91f0, 0xffffffff, 0x00030002,
	0x91f4, 0xffffffff, 0x00050004,
	0x915c, 0xffffffff, 0x00010000,
	0x9160, 0xffffffff, 0x00030002,
	0x3f90, 0xffff0000, 0xff000000,
	0x9178, 0xffffffff, 0x00070000,
	0x9194, 0xffffffff, 0x00070000,
	0x91b0, 0xffffffff, 0x00070000,
	0x91cc, 0xffffffff, 0x00070000,
	0x91ec, 0xffffffff, 0x00070000,
	0x9148, 0xffff0000, 0xff000000,
	0x9190, 0xffffffff, 0x00090008,
	0x91ac, 0xffffffff, 0x00090008,
	0x91c8, 0xffffffff, 0x00090008,
	0x91e4, 0xffffffff, 0x00090008,
	0x9204, 0xffffffff, 0x00090008,
	0x3f94, 0xffff0000, 0xff000000,
	0x914c, 0xffff0000, 0xff000000,
	0x929c, 0xffffffff, 0x00000001,
	0x8a18, 0xffffffff, 0x00000100,
	0x8b28, 0xffffffff, 0x00000100,
	0x9144, 0xffffffff, 0x00000100,
	0x5644, 0xffffffff, 0x00000100,
	0x9b7c, 0xffffffff, 0x00000000,
	0x8030, 0xffffffff, 0x0000100a,
	0x8a14, 0xffffffff, 0x00000007,
	0x8b24, 0xffffffff, 0x00ff0fff,
	0x8b10, 0xffffffff, 0x00000000,
	0x28a4c, 0x06000000, 0x06000000,
	0x4d8, 0xffffffff, 0x00000100,
	0x913c, 0xffff000f, 0x0100000a,
	0x960c, 0xffffffff, 0x54763210,
	0x88c4, 0xffffffff, 0x000000c2,
	0x88d4, 0xffffffff, 0x00000010,
	0x8974, 0xffffffff, 0x00000000,
	0xc78, 0x00000080, 0x00000080,
	0x5e78, 0xffffffff, 0x001000f0,
	0xd02c, 0xffffffff, 0x08421000,
	0xa008, 0xffffffff, 0x00010000,
	0x8d00, 0xffffffff, 0x100e4848,
	0x8d04, 0xffffffff, 0x00164745,
	0x8c00, 0xffffffff, 0xe4000003,
	0x8cf0, 0x1fffffff, 0x08e00620,
	0x28350, 0xffffffff, 0x00000000,
	0x9508, 0xffffffff, 0x00000002
पूर्ण;

अटल स्थिर u32 sumo_golden_रेजिस्टरs[] =
अणु
	0x900c, 0x00ffffff, 0x0017071f,
	0x8c18, 0xffffffff, 0x10101060,
	0x8c1c, 0xffffffff, 0x00001010,
	0x8c30, 0x0000000f, 0x00000005,
	0x9688, 0x0000000f, 0x00000007
पूर्ण;

अटल स्थिर u32 wrestler_golden_रेजिस्टरs[] =
अणु
	0x5eb4, 0xffffffff, 0x00000002,
	0x5c4, 0xffffffff, 0x00000001,
	0x7030, 0xffffffff, 0x00000011,
	0x7c30, 0xffffffff, 0x00000011,
	0x6104, 0x01000300, 0x00000000,
	0x5bc0, 0x00300000, 0x00000000,
	0x918c, 0xffffffff, 0x00010006,
	0x91a8, 0xffffffff, 0x00010006,
	0x9150, 0xffffffff, 0x6e944040,
	0x917c, 0xffffffff, 0x00030002,
	0x9198, 0xffffffff, 0x00030002,
	0x915c, 0xffffffff, 0x00010000,
	0x3f90, 0xffff0000, 0xff000000,
	0x9178, 0xffffffff, 0x00070000,
	0x9194, 0xffffffff, 0x00070000,
	0x9148, 0xffff0000, 0xff000000,
	0x9190, 0xffffffff, 0x00090008,
	0x91ac, 0xffffffff, 0x00090008,
	0x3f94, 0xffff0000, 0xff000000,
	0x914c, 0xffff0000, 0xff000000,
	0x929c, 0xffffffff, 0x00000001,
	0x8a18, 0xffffffff, 0x00000100,
	0x8b28, 0xffffffff, 0x00000100,
	0x9144, 0xffffffff, 0x00000100,
	0x9b7c, 0xffffffff, 0x00000000,
	0x8030, 0xffffffff, 0x0000100a,
	0x8a14, 0xffffffff, 0x00000001,
	0x8b24, 0xffffffff, 0x00ff0fff,
	0x8b10, 0xffffffff, 0x00000000,
	0x28a4c, 0x06000000, 0x06000000,
	0x4d8, 0xffffffff, 0x00000100,
	0x913c, 0xffff000f, 0x0100000a,
	0x960c, 0xffffffff, 0x54763210,
	0x88c4, 0xffffffff, 0x000000c2,
	0x88d4, 0xffffffff, 0x00000010,
	0x8974, 0xffffffff, 0x00000000,
	0xc78, 0x00000080, 0x00000080,
	0x5e78, 0xffffffff, 0x001000f0,
	0xd02c, 0xffffffff, 0x08421000,
	0xa008, 0xffffffff, 0x00010000,
	0x8d00, 0xffffffff, 0x100e4848,
	0x8d04, 0xffffffff, 0x00164745,
	0x8c00, 0xffffffff, 0xe4000003,
	0x8cf0, 0x1fffffff, 0x08e00410,
	0x28350, 0xffffffff, 0x00000000,
	0x9508, 0xffffffff, 0x00000002,
	0x900c, 0xffffffff, 0x0017071f,
	0x8c18, 0xffffffff, 0x10101060,
	0x8c1c, 0xffffffff, 0x00001010
पूर्ण;

अटल स्थिर u32 barts_golden_रेजिस्टरs[] =
अणु
	0x5eb4, 0xffffffff, 0x00000002,
	0x5e78, 0x8f311ff1, 0x001000f0,
	0x3f90, 0xffff0000, 0xff000000,
	0x9148, 0xffff0000, 0xff000000,
	0x3f94, 0xffff0000, 0xff000000,
	0x914c, 0xffff0000, 0xff000000,
	0xc78, 0x00000080, 0x00000080,
	0xbd4, 0x70073777, 0x00010001,
	0xd02c, 0xbfffff1f, 0x08421000,
	0xd0b8, 0x03773777, 0x02011003,
	0x5bc0, 0x00200000, 0x50100000,
	0x98f8, 0x33773777, 0x02011003,
	0x98fc, 0xffffffff, 0x76543210,
	0x7030, 0x31000311, 0x00000011,
	0x2f48, 0x00000007, 0x02011003,
	0x6b28, 0x00000010, 0x00000012,
	0x7728, 0x00000010, 0x00000012,
	0x10328, 0x00000010, 0x00000012,
	0x10f28, 0x00000010, 0x00000012,
	0x11b28, 0x00000010, 0x00000012,
	0x12728, 0x00000010, 0x00000012,
	0x240c, 0x000007ff, 0x00000380,
	0x8a14, 0xf000001f, 0x00000007,
	0x8b24, 0x3fff3fff, 0x00ff0fff,
	0x8b10, 0x0000ff0f, 0x00000000,
	0x28a4c, 0x07ffffff, 0x06000000,
	0x10c, 0x00000001, 0x00010003,
	0xa02c, 0xffffffff, 0x0000009b,
	0x913c, 0x0000000f, 0x0100000a,
	0x8d00, 0xffff7f7f, 0x100e4848,
	0x8d04, 0x00ffffff, 0x00164745,
	0x8c00, 0xfffc0003, 0xe4000003,
	0x8c04, 0xf8ff00ff, 0x40600060,
	0x8c08, 0x00ff00ff, 0x001c001c,
	0x8cf0, 0x1fff1fff, 0x08e00620,
	0x8c20, 0x0fff0fff, 0x00800080,
	0x8c24, 0x0fff0fff, 0x00800080,
	0x8c18, 0xffffffff, 0x20202078,
	0x8c1c, 0x0000ffff, 0x00001010,
	0x28350, 0x00000f01, 0x00000000,
	0x9508, 0x3700001f, 0x00000002,
	0x960c, 0xffffffff, 0x54763210,
	0x88c4, 0x001f3ae3, 0x000000c2,
	0x88d4, 0x0000001f, 0x00000010,
	0x8974, 0xffffffff, 0x00000000
पूर्ण;

अटल स्थिर u32 turks_golden_रेजिस्टरs[] =
अणु
	0x5eb4, 0xffffffff, 0x00000002,
	0x5e78, 0x8f311ff1, 0x001000f0,
	0x8c8, 0x00003000, 0x00001070,
	0x8cc, 0x000fffff, 0x00040035,
	0x3f90, 0xffff0000, 0xfff00000,
	0x9148, 0xffff0000, 0xfff00000,
	0x3f94, 0xffff0000, 0xfff00000,
	0x914c, 0xffff0000, 0xfff00000,
	0xc78, 0x00000080, 0x00000080,
	0xbd4, 0x00073007, 0x00010002,
	0xd02c, 0xbfffff1f, 0x08421000,
	0xd0b8, 0x03773777, 0x02010002,
	0x5bc0, 0x00200000, 0x50100000,
	0x98f8, 0x33773777, 0x00010002,
	0x98fc, 0xffffffff, 0x33221100,
	0x7030, 0x31000311, 0x00000011,
	0x2f48, 0x33773777, 0x00010002,
	0x6b28, 0x00000010, 0x00000012,
	0x7728, 0x00000010, 0x00000012,
	0x10328, 0x00000010, 0x00000012,
	0x10f28, 0x00000010, 0x00000012,
	0x11b28, 0x00000010, 0x00000012,
	0x12728, 0x00000010, 0x00000012,
	0x240c, 0x000007ff, 0x00000380,
	0x8a14, 0xf000001f, 0x00000007,
	0x8b24, 0x3fff3fff, 0x00ff0fff,
	0x8b10, 0x0000ff0f, 0x00000000,
	0x28a4c, 0x07ffffff, 0x06000000,
	0x10c, 0x00000001, 0x00010003,
	0xa02c, 0xffffffff, 0x0000009b,
	0x913c, 0x0000000f, 0x0100000a,
	0x8d00, 0xffff7f7f, 0x100e4848,
	0x8d04, 0x00ffffff, 0x00164745,
	0x8c00, 0xfffc0003, 0xe4000003,
	0x8c04, 0xf8ff00ff, 0x40600060,
	0x8c08, 0x00ff00ff, 0x001c001c,
	0x8cf0, 0x1fff1fff, 0x08e00410,
	0x8c20, 0x0fff0fff, 0x00800080,
	0x8c24, 0x0fff0fff, 0x00800080,
	0x8c18, 0xffffffff, 0x20202078,
	0x8c1c, 0x0000ffff, 0x00001010,
	0x28350, 0x00000f01, 0x00000000,
	0x9508, 0x3700001f, 0x00000002,
	0x960c, 0xffffffff, 0x54763210,
	0x88c4, 0x001f3ae3, 0x000000c2,
	0x88d4, 0x0000001f, 0x00000010,
	0x8974, 0xffffffff, 0x00000000
पूर्ण;

अटल स्थिर u32 caicos_golden_रेजिस्टरs[] =
अणु
	0x5eb4, 0xffffffff, 0x00000002,
	0x5e78, 0x8f311ff1, 0x001000f0,
	0x8c8, 0x00003420, 0x00001450,
	0x8cc, 0x000fffff, 0x00040035,
	0x3f90, 0xffff0000, 0xfffc0000,
	0x9148, 0xffff0000, 0xfffc0000,
	0x3f94, 0xffff0000, 0xfffc0000,
	0x914c, 0xffff0000, 0xfffc0000,
	0xc78, 0x00000080, 0x00000080,
	0xbd4, 0x00073007, 0x00010001,
	0xd02c, 0xbfffff1f, 0x08421000,
	0xd0b8, 0x03773777, 0x02010001,
	0x5bc0, 0x00200000, 0x50100000,
	0x98f8, 0x33773777, 0x02010001,
	0x98fc, 0xffffffff, 0x33221100,
	0x7030, 0x31000311, 0x00000011,
	0x2f48, 0x33773777, 0x02010001,
	0x6b28, 0x00000010, 0x00000012,
	0x7728, 0x00000010, 0x00000012,
	0x10328, 0x00000010, 0x00000012,
	0x10f28, 0x00000010, 0x00000012,
	0x11b28, 0x00000010, 0x00000012,
	0x12728, 0x00000010, 0x00000012,
	0x240c, 0x000007ff, 0x00000380,
	0x8a14, 0xf000001f, 0x00000001,
	0x8b24, 0x3fff3fff, 0x00ff0fff,
	0x8b10, 0x0000ff0f, 0x00000000,
	0x28a4c, 0x07ffffff, 0x06000000,
	0x10c, 0x00000001, 0x00010003,
	0xa02c, 0xffffffff, 0x0000009b,
	0x913c, 0x0000000f, 0x0100000a,
	0x8d00, 0xffff7f7f, 0x100e4848,
	0x8d04, 0x00ffffff, 0x00164745,
	0x8c00, 0xfffc0003, 0xe4000003,
	0x8c04, 0xf8ff00ff, 0x40600060,
	0x8c08, 0x00ff00ff, 0x001c001c,
	0x8cf0, 0x1fff1fff, 0x08e00410,
	0x8c20, 0x0fff0fff, 0x00800080,
	0x8c24, 0x0fff0fff, 0x00800080,
	0x8c18, 0xffffffff, 0x20202078,
	0x8c1c, 0x0000ffff, 0x00001010,
	0x28350, 0x00000f01, 0x00000000,
	0x9508, 0x3700001f, 0x00000002,
	0x960c, 0xffffffff, 0x54763210,
	0x88c4, 0x001f3ae3, 0x000000c2,
	0x88d4, 0x0000001f, 0x00000010,
	0x8974, 0xffffffff, 0x00000000
पूर्ण;

अटल व्योम evergreen_init_golden_रेजिस्टरs(काष्ठा radeon_device *rdev)
अणु
	चयन (rdev->family) अणु
	हाल CHIP_CYPRESS:
	हाल CHIP_HEMLOCK:
		radeon_program_रेजिस्टर_sequence(rdev,
						 evergreen_golden_रेजिस्टरs,
						 (स्थिर u32)ARRAY_SIZE(evergreen_golden_रेजिस्टरs));
		radeon_program_रेजिस्टर_sequence(rdev,
						 evergreen_golden_रेजिस्टरs2,
						 (स्थिर u32)ARRAY_SIZE(evergreen_golden_रेजिस्टरs2));
		radeon_program_रेजिस्टर_sequence(rdev,
						 cypress_mgcg_init,
						 (स्थिर u32)ARRAY_SIZE(cypress_mgcg_init));
		अवरोध;
	हाल CHIP_JUNIPER:
		radeon_program_रेजिस्टर_sequence(rdev,
						 evergreen_golden_रेजिस्टरs,
						 (स्थिर u32)ARRAY_SIZE(evergreen_golden_रेजिस्टरs));
		radeon_program_रेजिस्टर_sequence(rdev,
						 evergreen_golden_रेजिस्टरs2,
						 (स्थिर u32)ARRAY_SIZE(evergreen_golden_रेजिस्टरs2));
		radeon_program_रेजिस्टर_sequence(rdev,
						 juniper_mgcg_init,
						 (स्थिर u32)ARRAY_SIZE(juniper_mgcg_init));
		अवरोध;
	हाल CHIP_REDWOOD:
		radeon_program_रेजिस्टर_sequence(rdev,
						 evergreen_golden_रेजिस्टरs,
						 (स्थिर u32)ARRAY_SIZE(evergreen_golden_रेजिस्टरs));
		radeon_program_रेजिस्टर_sequence(rdev,
						 evergreen_golden_रेजिस्टरs2,
						 (स्थिर u32)ARRAY_SIZE(evergreen_golden_रेजिस्टरs2));
		radeon_program_रेजिस्टर_sequence(rdev,
						 redwood_mgcg_init,
						 (स्थिर u32)ARRAY_SIZE(redwood_mgcg_init));
		अवरोध;
	हाल CHIP_CEDAR:
		radeon_program_रेजिस्टर_sequence(rdev,
						 cedar_golden_रेजिस्टरs,
						 (स्थिर u32)ARRAY_SIZE(cedar_golden_रेजिस्टरs));
		radeon_program_रेजिस्टर_sequence(rdev,
						 evergreen_golden_रेजिस्टरs2,
						 (स्थिर u32)ARRAY_SIZE(evergreen_golden_रेजिस्टरs2));
		radeon_program_रेजिस्टर_sequence(rdev,
						 cedar_mgcg_init,
						 (स्थिर u32)ARRAY_SIZE(cedar_mgcg_init));
		अवरोध;
	हाल CHIP_PALM:
		radeon_program_रेजिस्टर_sequence(rdev,
						 wrestler_golden_रेजिस्टरs,
						 (स्थिर u32)ARRAY_SIZE(wrestler_golden_रेजिस्टरs));
		अवरोध;
	हाल CHIP_SUMO:
		radeon_program_रेजिस्टर_sequence(rdev,
						 supersumo_golden_रेजिस्टरs,
						 (स्थिर u32)ARRAY_SIZE(supersumo_golden_रेजिस्टरs));
		अवरोध;
	हाल CHIP_SUMO2:
		radeon_program_रेजिस्टर_sequence(rdev,
						 supersumo_golden_रेजिस्टरs,
						 (स्थिर u32)ARRAY_SIZE(supersumo_golden_रेजिस्टरs));
		radeon_program_रेजिस्टर_sequence(rdev,
						 sumo_golden_रेजिस्टरs,
						 (स्थिर u32)ARRAY_SIZE(sumo_golden_रेजिस्टरs));
		अवरोध;
	हाल CHIP_BARTS:
		radeon_program_रेजिस्टर_sequence(rdev,
						 barts_golden_रेजिस्टरs,
						 (स्थिर u32)ARRAY_SIZE(barts_golden_रेजिस्टरs));
		अवरोध;
	हाल CHIP_TURKS:
		radeon_program_रेजिस्टर_sequence(rdev,
						 turks_golden_रेजिस्टरs,
						 (स्थिर u32)ARRAY_SIZE(turks_golden_रेजिस्टरs));
		अवरोध;
	हाल CHIP_CAICOS:
		radeon_program_रेजिस्टर_sequence(rdev,
						 caicos_golden_रेजिस्टरs,
						 (स्थिर u32)ARRAY_SIZE(caicos_golden_रेजिस्टरs));
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

/**
 * evergreen_get_allowed_info_रेजिस्टर - fetch the रेजिस्टर क्रम the info ioctl
 *
 * @rdev: radeon_device poपूर्णांकer
 * @reg: रेजिस्टर offset in bytes
 * @val: रेजिस्टर value
 *
 * Returns 0 क्रम success or -EINVAL क्रम an invalid रेजिस्टर
 *
 */
पूर्णांक evergreen_get_allowed_info_रेजिस्टर(काष्ठा radeon_device *rdev,
					u32 reg, u32 *val)
अणु
	चयन (reg) अणु
	हाल GRBM_STATUS:
	हाल GRBM_STATUS_SE0:
	हाल GRBM_STATUS_SE1:
	हाल SRBM_STATUS:
	हाल SRBM_STATUS2:
	हाल DMA_STATUS_REG:
	हाल UVD_STATUS:
		*val = RREG32(reg);
		वापस 0;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

व्योम evergreen_tiling_fields(अचिन्हित tiling_flags, अचिन्हित *bankw,
			     अचिन्हित *bankh, अचिन्हित *mtaspect,
			     अचिन्हित *tile_split)
अणु
	*bankw = (tiling_flags >> RADEON_TILING_EG_BANKW_SHIFT) & RADEON_TILING_EG_BANKW_MASK;
	*bankh = (tiling_flags >> RADEON_TILING_EG_BANKH_SHIFT) & RADEON_TILING_EG_BANKH_MASK;
	*mtaspect = (tiling_flags >> RADEON_TILING_EG_MACRO_TILE_ASPECT_SHIFT) & RADEON_TILING_EG_MACRO_TILE_ASPECT_MASK;
	*tile_split = (tiling_flags >> RADEON_TILING_EG_TILE_SPLIT_SHIFT) & RADEON_TILING_EG_TILE_SPLIT_MASK;
	चयन (*bankw) अणु
	शेष:
	हाल 1: *bankw = EVERGREEN_ADDR_SURF_BANK_WIDTH_1; अवरोध;
	हाल 2: *bankw = EVERGREEN_ADDR_SURF_BANK_WIDTH_2; अवरोध;
	हाल 4: *bankw = EVERGREEN_ADDR_SURF_BANK_WIDTH_4; अवरोध;
	हाल 8: *bankw = EVERGREEN_ADDR_SURF_BANK_WIDTH_8; अवरोध;
	पूर्ण
	चयन (*bankh) अणु
	शेष:
	हाल 1: *bankh = EVERGREEN_ADDR_SURF_BANK_HEIGHT_1; अवरोध;
	हाल 2: *bankh = EVERGREEN_ADDR_SURF_BANK_HEIGHT_2; अवरोध;
	हाल 4: *bankh = EVERGREEN_ADDR_SURF_BANK_HEIGHT_4; अवरोध;
	हाल 8: *bankh = EVERGREEN_ADDR_SURF_BANK_HEIGHT_8; अवरोध;
	पूर्ण
	चयन (*mtaspect) अणु
	शेष:
	हाल 1: *mtaspect = EVERGREEN_ADDR_SURF_MACRO_TILE_ASPECT_1; अवरोध;
	हाल 2: *mtaspect = EVERGREEN_ADDR_SURF_MACRO_TILE_ASPECT_2; अवरोध;
	हाल 4: *mtaspect = EVERGREEN_ADDR_SURF_MACRO_TILE_ASPECT_4; अवरोध;
	हाल 8: *mtaspect = EVERGREEN_ADDR_SURF_MACRO_TILE_ASPECT_8; अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक sumo_set_uvd_घड़ी(काष्ठा radeon_device *rdev, u32 घड़ी,
			      u32 cntl_reg, u32 status_reg)
अणु
	पूर्णांक r, i;
	काष्ठा atom_घड़ी_भागiders भागiders;

	r = radeon_atom_get_घड़ी_भागiders(rdev, COMPUTE_ENGINE_PLL_PARAM,
					   घड़ी, false, &भागiders);
	अगर (r)
		वापस r;

	WREG32_P(cntl_reg, भागiders.post_भाग, ~(DCLK_सूची_CNTL_EN|DCLK_DIVIDER_MASK));

	क्रम (i = 0; i < 100; i++) अणु
		अगर (RREG32(status_reg) & DCLK_STATUS)
			अवरोध;
		mdelay(10);
	पूर्ण
	अगर (i == 100)
		वापस -ETIMEDOUT;

	वापस 0;
पूर्ण

पूर्णांक sumo_set_uvd_घड़ीs(काष्ठा radeon_device *rdev, u32 vclk, u32 dclk)
अणु
	पूर्णांक r = 0;
	u32 cg_scratch = RREG32(CG_SCRATCH1);

	r = sumo_set_uvd_घड़ी(rdev, vclk, CG_VCLK_CNTL, CG_VCLK_STATUS);
	अगर (r)
		जाओ करोne;
	cg_scratch &= 0xffff0000;
	cg_scratch |= vclk / 100; /* Mhz */

	r = sumo_set_uvd_घड़ी(rdev, dclk, CG_DCLK_CNTL, CG_DCLK_STATUS);
	अगर (r)
		जाओ करोne;
	cg_scratch &= 0x0000ffff;
	cg_scratch |= (dclk / 100) << 16; /* Mhz */

करोne:
	WREG32(CG_SCRATCH1, cg_scratch);

	वापस r;
पूर्ण

पूर्णांक evergreen_set_uvd_घड़ीs(काष्ठा radeon_device *rdev, u32 vclk, u32 dclk)
अणु
	/* start off with something large */
	अचिन्हित fb_भाग = 0, vclk_भाग = 0, dclk_भाग = 0;
	पूर्णांक r;

	/* bypass vclk and dclk with bclk */
	WREG32_P(CG_UPLL_FUNC_CNTL_2,
		VCLK_SRC_SEL(1) | DCLK_SRC_SEL(1),
		~(VCLK_SRC_SEL_MASK | DCLK_SRC_SEL_MASK));

	/* put PLL in bypass mode */
	WREG32_P(CG_UPLL_FUNC_CNTL, UPLL_BYPASS_EN_MASK, ~UPLL_BYPASS_EN_MASK);

	अगर (!vclk || !dclk) अणु
		/* keep the Bypass mode, put PLL to sleep */
		WREG32_P(CG_UPLL_FUNC_CNTL, UPLL_SLEEP_MASK, ~UPLL_SLEEP_MASK);
		वापस 0;
	पूर्ण

	r = radeon_uvd_calc_upll_भागiders(rdev, vclk, dclk, 125000, 250000,
					  16384, 0x03FFFFFF, 0, 128, 5,
					  &fb_भाग, &vclk_भाग, &dclk_भाग);
	अगर (r)
		वापस r;

	/* set VCO_MODE to 1 */
	WREG32_P(CG_UPLL_FUNC_CNTL, UPLL_VCO_MODE_MASK, ~UPLL_VCO_MODE_MASK);

	/* toggle UPLL_SLEEP to 1 then back to 0 */
	WREG32_P(CG_UPLL_FUNC_CNTL, UPLL_SLEEP_MASK, ~UPLL_SLEEP_MASK);
	WREG32_P(CG_UPLL_FUNC_CNTL, 0, ~UPLL_SLEEP_MASK);

	/* deनिश्चित UPLL_RESET */
	WREG32_P(CG_UPLL_FUNC_CNTL, 0, ~UPLL_RESET_MASK);

	mdelay(1);

	r = radeon_uvd_send_upll_ctlreq(rdev, CG_UPLL_FUNC_CNTL);
	अगर (r)
		वापस r;

	/* निश्चित UPLL_RESET again */
	WREG32_P(CG_UPLL_FUNC_CNTL, UPLL_RESET_MASK, ~UPLL_RESET_MASK);

	/* disable spपढ़ो spectrum. */
	WREG32_P(CG_UPLL_SPREAD_SPECTRUM, 0, ~SSEN_MASK);

	/* set feedback भागider */
	WREG32_P(CG_UPLL_FUNC_CNTL_3, UPLL_FB_DIV(fb_भाग), ~UPLL_FB_DIV_MASK);

	/* set ref भागider to 0 */
	WREG32_P(CG_UPLL_FUNC_CNTL, 0, ~UPLL_REF_DIV_MASK);

	अगर (fb_भाग < 307200)
		WREG32_P(CG_UPLL_FUNC_CNTL_4, 0, ~UPLL_SPARE_ISPARE9);
	अन्यथा
		WREG32_P(CG_UPLL_FUNC_CNTL_4, UPLL_SPARE_ISPARE9, ~UPLL_SPARE_ISPARE9);

	/* set PDIV_A and PDIV_B */
	WREG32_P(CG_UPLL_FUNC_CNTL_2,
		UPLL_PDIV_A(vclk_भाग) | UPLL_PDIV_B(dclk_भाग),
		~(UPLL_PDIV_A_MASK | UPLL_PDIV_B_MASK));

	/* give the PLL some समय to settle */
	mdelay(15);

	/* deनिश्चित PLL_RESET */
	WREG32_P(CG_UPLL_FUNC_CNTL, 0, ~UPLL_RESET_MASK);

	mdelay(15);

	/* चयन from bypass mode to normal mode */
	WREG32_P(CG_UPLL_FUNC_CNTL, 0, ~UPLL_BYPASS_EN_MASK);

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

व्योम evergreen_fix_pci_max_पढ़ो_req_size(काष्ठा radeon_device *rdev)
अणु
	पूर्णांक पढ़ोrq;
	u16 v;

	पढ़ोrq = pcie_get_पढ़ोrq(rdev->pdev);
	v = ffs(पढ़ोrq) - 8;
	/* अगर bios or OS sets MAX_READ_REQUEST_SIZE to an invalid value, fix it
	 * to aव्योम hangs or perfomance issues
	 */
	अगर ((v == 0) || (v == 6) || (v == 7))
		pcie_set_पढ़ोrq(rdev->pdev, 512);
पूर्ण

व्योम dce4_program_fmt(काष्ठा drm_encoder *encoder)
अणु
	काष्ठा drm_device *dev = encoder->dev;
	काष्ठा radeon_device *rdev = dev->dev_निजी;
	काष्ठा radeon_encoder *radeon_encoder = to_radeon_encoder(encoder);
	काष्ठा radeon_crtc *radeon_crtc = to_radeon_crtc(encoder->crtc);
	काष्ठा drm_connector *connector = radeon_get_connector_क्रम_encoder(encoder);
	पूर्णांक bpc = 0;
	u32 पंचांगp = 0;
	क्रमागत radeon_connector_dither dither = RADEON_FMT_DITHER_DISABLE;

	अगर (connector) अणु
		काष्ठा radeon_connector *radeon_connector = to_radeon_connector(connector);
		bpc = radeon_get_monitor_bpc(connector);
		dither = radeon_connector->dither;
	पूर्ण

	/* LVDS/eDP FMT is set up by atom */
	अगर (radeon_encoder->devices & ATOM_DEVICE_LCD_SUPPORT)
		वापस;

	/* not needed क्रम analog */
	अगर ((radeon_encoder->encoder_id == ENCODER_OBJECT_ID_INTERNAL_KLDSCP_DAC1) ||
	    (radeon_encoder->encoder_id == ENCODER_OBJECT_ID_INTERNAL_KLDSCP_DAC2))
		वापस;

	अगर (bpc == 0)
		वापस;

	चयन (bpc) अणु
	हाल 6:
		अगर (dither == RADEON_FMT_DITHER_ENABLE)
			/* XXX sort out optimal dither settings */
			पंचांगp |= (FMT_FRAME_RANDOM_ENABLE | FMT_HIGHPASS_RANDOM_ENABLE |
				FMT_SPATIAL_DITHER_EN);
		अन्यथा
			पंचांगp |= FMT_TRUNCATE_EN;
		अवरोध;
	हाल 8:
		अगर (dither == RADEON_FMT_DITHER_ENABLE)
			/* XXX sort out optimal dither settings */
			पंचांगp |= (FMT_FRAME_RANDOM_ENABLE | FMT_HIGHPASS_RANDOM_ENABLE |
				FMT_RGB_RANDOM_ENABLE |
				FMT_SPATIAL_DITHER_EN | FMT_SPATIAL_DITHER_DEPTH);
		अन्यथा
			पंचांगp |= (FMT_TRUNCATE_EN | FMT_TRUNCATE_DEPTH);
		अवरोध;
	हाल 10:
	शेष:
		/* not needed */
		अवरोध;
	पूर्ण

	WREG32(FMT_BIT_DEPTH_CONTROL + radeon_crtc->crtc_offset, पंचांगp);
पूर्ण

अटल bool dce4_is_in_vblank(काष्ठा radeon_device *rdev, पूर्णांक crtc)
अणु
	अगर (RREG32(EVERGREEN_CRTC_STATUS + crtc_offsets[crtc]) & EVERGREEN_CRTC_V_BLANK)
		वापस true;
	अन्यथा
		वापस false;
पूर्ण

अटल bool dce4_is_counter_moving(काष्ठा radeon_device *rdev, पूर्णांक crtc)
अणु
	u32 pos1, pos2;

	pos1 = RREG32(EVERGREEN_CRTC_STATUS_POSITION + crtc_offsets[crtc]);
	pos2 = RREG32(EVERGREEN_CRTC_STATUS_POSITION + crtc_offsets[crtc]);

	अगर (pos1 != pos2)
		वापस true;
	अन्यथा
		वापस false;
पूर्ण

/**
 * dce4_रुको_क्रम_vblank - vblank रुको asic callback.
 *
 * @rdev: radeon_device poपूर्णांकer
 * @crtc: crtc to रुको क्रम vblank on
 *
 * Wait क्रम vblank on the requested crtc (evergreen+).
 */
व्योम dce4_रुको_क्रम_vblank(काष्ठा radeon_device *rdev, पूर्णांक crtc)
अणु
	अचिन्हित i = 0;

	अगर (crtc >= rdev->num_crtc)
		वापस;

	अगर (!(RREG32(EVERGREEN_CRTC_CONTROL + crtc_offsets[crtc]) & EVERGREEN_CRTC_MASTER_EN))
		वापस;

	/* depending on when we hit vblank, we may be बंद to active; अगर so,
	 * रुको क्रम another frame.
	 */
	जबतक (dce4_is_in_vblank(rdev, crtc)) अणु
		अगर (i++ % 100 == 0) अणु
			अगर (!dce4_is_counter_moving(rdev, crtc))
				अवरोध;
		पूर्ण
	पूर्ण

	जबतक (!dce4_is_in_vblank(rdev, crtc)) अणु
		अगर (i++ % 100 == 0) अणु
			अगर (!dce4_is_counter_moving(rdev, crtc))
				अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

/**
 * evergreen_page_flip - pageflip callback.
 *
 * @rdev: radeon_device poपूर्णांकer
 * @crtc_id: crtc to cleanup pageflip on
 * @crtc_base: new address of the crtc (GPU MC address)
 * @async: asynchronous flip
 *
 * Triggers the actual pageflip by updating the primary
 * surface base address (evergreen+).
 */
व्योम evergreen_page_flip(काष्ठा radeon_device *rdev, पूर्णांक crtc_id, u64 crtc_base,
			 bool async)
अणु
	काष्ठा radeon_crtc *radeon_crtc = rdev->mode_info.crtcs[crtc_id];

	/* update the scanout addresses */
	WREG32(EVERGREEN_GRPH_FLIP_CONTROL + radeon_crtc->crtc_offset,
	       async ? EVERGREEN_GRPH_SURFACE_UPDATE_H_RETRACE_EN : 0);
	WREG32(EVERGREEN_GRPH_PRIMARY_SURFACE_ADDRESS_HIGH + radeon_crtc->crtc_offset,
	       upper_32_bits(crtc_base));
	WREG32(EVERGREEN_GRPH_PRIMARY_SURFACE_ADDRESS + radeon_crtc->crtc_offset,
	       (u32)crtc_base);
	/* post the ग_लिखो */
	RREG32(EVERGREEN_GRPH_PRIMARY_SURFACE_ADDRESS + radeon_crtc->crtc_offset);
पूर्ण

/**
 * evergreen_page_flip_pending - check अगर page flip is still pending
 *
 * @rdev: radeon_device poपूर्णांकer
 * @crtc_id: crtc to check
 *
 * Returns the current update pending status.
 */
bool evergreen_page_flip_pending(काष्ठा radeon_device *rdev, पूर्णांक crtc_id)
अणु
	काष्ठा radeon_crtc *radeon_crtc = rdev->mode_info.crtcs[crtc_id];

	/* Return current update_pending status: */
	वापस !!(RREG32(EVERGREEN_GRPH_UPDATE + radeon_crtc->crtc_offset) &
		EVERGREEN_GRPH_SURFACE_UPDATE_PENDING);
पूर्ण

/* get temperature in millidegrees */
पूर्णांक evergreen_get_temp(काष्ठा radeon_device *rdev)
अणु
	u32 temp, toffset;
	पूर्णांक actual_temp = 0;

	अगर (rdev->family == CHIP_JUNIPER) अणु
		toffset = (RREG32(CG_THERMAL_CTRL) & TOFFSET_MASK) >>
			TOFFSET_SHIFT;
		temp = (RREG32(CG_TS0_STATUS) & TS0_ADC_DOUT_MASK) >>
			TS0_ADC_DOUT_SHIFT;

		अगर (toffset & 0x100)
			actual_temp = temp / 2 - (0x200 - toffset);
		अन्यथा
			actual_temp = temp / 2 + toffset;

		actual_temp = actual_temp * 1000;

	पूर्ण अन्यथा अणु
		temp = (RREG32(CG_MULT_THERMAL_STATUS) & ASIC_T_MASK) >>
			ASIC_T_SHIFT;

		अगर (temp & 0x400)
			actual_temp = -256;
		अन्यथा अगर (temp & 0x200)
			actual_temp = 255;
		अन्यथा अगर (temp & 0x100) अणु
			actual_temp = temp & 0x1ff;
			actual_temp |= ~0x1ff;
		पूर्ण अन्यथा
			actual_temp = temp & 0xff;

		actual_temp = (actual_temp * 1000) / 2;
	पूर्ण

	वापस actual_temp;
पूर्ण

पूर्णांक sumo_get_temp(काष्ठा radeon_device *rdev)
अणु
	u32 temp = RREG32(CG_THERMAL_STATUS) & 0xff;
	पूर्णांक actual_temp = temp - 49;

	वापस actual_temp * 1000;
पूर्ण

/**
 * sumo_pm_init_profile - Initialize घातer profiles callback.
 *
 * @rdev: radeon_device poपूर्णांकer
 *
 * Initialize the घातer states used in profile mode
 * (sumo, trinity, SI).
 * Used क्रम profile mode only.
 */
व्योम sumo_pm_init_profile(काष्ठा radeon_device *rdev)
अणु
	पूर्णांक idx;

	/* शेष */
	rdev->pm.profiles[PM_PROखाता_DEFAULT_IDX].dpms_off_ps_idx = rdev->pm.शेष_घातer_state_index;
	rdev->pm.profiles[PM_PROखाता_DEFAULT_IDX].dpms_on_ps_idx = rdev->pm.शेष_घातer_state_index;
	rdev->pm.profiles[PM_PROखाता_DEFAULT_IDX].dpms_off_cm_idx = 0;
	rdev->pm.profiles[PM_PROखाता_DEFAULT_IDX].dpms_on_cm_idx = 0;

	/* low,mid sh/mh */
	अगर (rdev->flags & RADEON_IS_MOBILITY)
		idx = radeon_pm_get_type_index(rdev, POWER_STATE_TYPE_BATTERY, 0);
	अन्यथा
		idx = radeon_pm_get_type_index(rdev, POWER_STATE_TYPE_PERFORMANCE, 0);

	rdev->pm.profiles[PM_PROखाता_LOW_SH_IDX].dpms_off_ps_idx = idx;
	rdev->pm.profiles[PM_PROखाता_LOW_SH_IDX].dpms_on_ps_idx = idx;
	rdev->pm.profiles[PM_PROखाता_LOW_SH_IDX].dpms_off_cm_idx = 0;
	rdev->pm.profiles[PM_PROखाता_LOW_SH_IDX].dpms_on_cm_idx = 0;

	rdev->pm.profiles[PM_PROखाता_LOW_MH_IDX].dpms_off_ps_idx = idx;
	rdev->pm.profiles[PM_PROखाता_LOW_MH_IDX].dpms_on_ps_idx = idx;
	rdev->pm.profiles[PM_PROखाता_LOW_MH_IDX].dpms_off_cm_idx = 0;
	rdev->pm.profiles[PM_PROखाता_LOW_MH_IDX].dpms_on_cm_idx = 0;

	rdev->pm.profiles[PM_PROखाता_MID_SH_IDX].dpms_off_ps_idx = idx;
	rdev->pm.profiles[PM_PROखाता_MID_SH_IDX].dpms_on_ps_idx = idx;
	rdev->pm.profiles[PM_PROखाता_MID_SH_IDX].dpms_off_cm_idx = 0;
	rdev->pm.profiles[PM_PROखाता_MID_SH_IDX].dpms_on_cm_idx = 0;

	rdev->pm.profiles[PM_PROखाता_MID_MH_IDX].dpms_off_ps_idx = idx;
	rdev->pm.profiles[PM_PROखाता_MID_MH_IDX].dpms_on_ps_idx = idx;
	rdev->pm.profiles[PM_PROखाता_MID_MH_IDX].dpms_off_cm_idx = 0;
	rdev->pm.profiles[PM_PROखाता_MID_MH_IDX].dpms_on_cm_idx = 0;

	/* high sh/mh */
	idx = radeon_pm_get_type_index(rdev, POWER_STATE_TYPE_PERFORMANCE, 0);
	rdev->pm.profiles[PM_PROखाता_HIGH_SH_IDX].dpms_off_ps_idx = idx;
	rdev->pm.profiles[PM_PROखाता_HIGH_SH_IDX].dpms_on_ps_idx = idx;
	rdev->pm.profiles[PM_PROखाता_HIGH_SH_IDX].dpms_off_cm_idx = 0;
	rdev->pm.profiles[PM_PROखाता_HIGH_SH_IDX].dpms_on_cm_idx =
		rdev->pm.घातer_state[idx].num_घड़ी_modes - 1;

	rdev->pm.profiles[PM_PROखाता_HIGH_MH_IDX].dpms_off_ps_idx = idx;
	rdev->pm.profiles[PM_PROखाता_HIGH_MH_IDX].dpms_on_ps_idx = idx;
	rdev->pm.profiles[PM_PROखाता_HIGH_MH_IDX].dpms_off_cm_idx = 0;
	rdev->pm.profiles[PM_PROखाता_HIGH_MH_IDX].dpms_on_cm_idx =
		rdev->pm.घातer_state[idx].num_घड़ी_modes - 1;
पूर्ण

/**
 * btc_pm_init_profile - Initialize घातer profiles callback.
 *
 * @rdev: radeon_device poपूर्णांकer
 *
 * Initialize the घातer states used in profile mode
 * (BTC, cayman).
 * Used क्रम profile mode only.
 */
व्योम btc_pm_init_profile(काष्ठा radeon_device *rdev)
अणु
	पूर्णांक idx;

	/* शेष */
	rdev->pm.profiles[PM_PROखाता_DEFAULT_IDX].dpms_off_ps_idx = rdev->pm.शेष_घातer_state_index;
	rdev->pm.profiles[PM_PROखाता_DEFAULT_IDX].dpms_on_ps_idx = rdev->pm.शेष_घातer_state_index;
	rdev->pm.profiles[PM_PROखाता_DEFAULT_IDX].dpms_off_cm_idx = 0;
	rdev->pm.profiles[PM_PROखाता_DEFAULT_IDX].dpms_on_cm_idx = 2;
	/* starting with BTC, there is one state that is used क्रम both
	 * MH and SH.  Dअगरference is that we always use the high घड़ी index क्रम
	 * mclk.
	 */
	अगर (rdev->flags & RADEON_IS_MOBILITY)
		idx = radeon_pm_get_type_index(rdev, POWER_STATE_TYPE_BATTERY, 0);
	अन्यथा
		idx = radeon_pm_get_type_index(rdev, POWER_STATE_TYPE_PERFORMANCE, 0);
	/* low sh */
	rdev->pm.profiles[PM_PROखाता_LOW_SH_IDX].dpms_off_ps_idx = idx;
	rdev->pm.profiles[PM_PROखाता_LOW_SH_IDX].dpms_on_ps_idx = idx;
	rdev->pm.profiles[PM_PROखाता_LOW_SH_IDX].dpms_off_cm_idx = 0;
	rdev->pm.profiles[PM_PROखाता_LOW_SH_IDX].dpms_on_cm_idx = 0;
	/* mid sh */
	rdev->pm.profiles[PM_PROखाता_MID_SH_IDX].dpms_off_ps_idx = idx;
	rdev->pm.profiles[PM_PROखाता_MID_SH_IDX].dpms_on_ps_idx = idx;
	rdev->pm.profiles[PM_PROखाता_MID_SH_IDX].dpms_off_cm_idx = 0;
	rdev->pm.profiles[PM_PROखाता_MID_SH_IDX].dpms_on_cm_idx = 1;
	/* high sh */
	rdev->pm.profiles[PM_PROखाता_HIGH_SH_IDX].dpms_off_ps_idx = idx;
	rdev->pm.profiles[PM_PROखाता_HIGH_SH_IDX].dpms_on_ps_idx = idx;
	rdev->pm.profiles[PM_PROखाता_HIGH_SH_IDX].dpms_off_cm_idx = 0;
	rdev->pm.profiles[PM_PROखाता_HIGH_SH_IDX].dpms_on_cm_idx = 2;
	/* low mh */
	rdev->pm.profiles[PM_PROखाता_LOW_MH_IDX].dpms_off_ps_idx = idx;
	rdev->pm.profiles[PM_PROखाता_LOW_MH_IDX].dpms_on_ps_idx = idx;
	rdev->pm.profiles[PM_PROखाता_LOW_MH_IDX].dpms_off_cm_idx = 0;
	rdev->pm.profiles[PM_PROखाता_LOW_MH_IDX].dpms_on_cm_idx = 0;
	/* mid mh */
	rdev->pm.profiles[PM_PROखाता_MID_MH_IDX].dpms_off_ps_idx = idx;
	rdev->pm.profiles[PM_PROखाता_MID_MH_IDX].dpms_on_ps_idx = idx;
	rdev->pm.profiles[PM_PROखाता_MID_MH_IDX].dpms_off_cm_idx = 0;
	rdev->pm.profiles[PM_PROखाता_MID_MH_IDX].dpms_on_cm_idx = 1;
	/* high mh */
	rdev->pm.profiles[PM_PROखाता_HIGH_MH_IDX].dpms_off_ps_idx = idx;
	rdev->pm.profiles[PM_PROखाता_HIGH_MH_IDX].dpms_on_ps_idx = idx;
	rdev->pm.profiles[PM_PROखाता_HIGH_MH_IDX].dpms_off_cm_idx = 0;
	rdev->pm.profiles[PM_PROखाता_HIGH_MH_IDX].dpms_on_cm_idx = 2;
पूर्ण

/**
 * evergreen_pm_misc - set additional pm hw parameters callback.
 *
 * @rdev: radeon_device poपूर्णांकer
 *
 * Set non-घड़ी parameters associated with a घातer state
 * (voltage, etc.) (evergreen+).
 */
व्योम evergreen_pm_misc(काष्ठा radeon_device *rdev)
अणु
	पूर्णांक req_ps_idx = rdev->pm.requested_घातer_state_index;
	पूर्णांक req_cm_idx = rdev->pm.requested_घड़ी_mode_index;
	काष्ठा radeon_घातer_state *ps = &rdev->pm.घातer_state[req_ps_idx];
	काष्ठा radeon_voltage *voltage = &ps->घड़ी_info[req_cm_idx].voltage;

	अगर (voltage->type == VOLTAGE_SW) अणु
		/* 0xff0x are flags rather then an actual voltage */
		अगर ((voltage->voltage & 0xff00) == 0xff00)
			वापस;
		अगर (voltage->voltage && (voltage->voltage != rdev->pm.current_vddc)) अणु
			radeon_atom_set_voltage(rdev, voltage->voltage, SET_VOLTAGE_TYPE_ASIC_VDDC);
			rdev->pm.current_vddc = voltage->voltage;
			DRM_DEBUG("Setting: vddc: %d\n", voltage->voltage);
		पूर्ण

		/* starting with BTC, there is one state that is used क्रम both
		 * MH and SH.  Dअगरference is that we always use the high घड़ी index क्रम
		 * mclk and vddci.
		 */
		अगर ((rdev->pm.pm_method == PM_METHOD_PROखाता) &&
		    (rdev->family >= CHIP_BARTS) &&
		    rdev->pm.active_crtc_count &&
		    ((rdev->pm.profile_index == PM_PROखाता_MID_MH_IDX) ||
		     (rdev->pm.profile_index == PM_PROखाता_LOW_MH_IDX)))
			voltage = &rdev->pm.घातer_state[req_ps_idx].
				घड़ी_info[rdev->pm.profiles[PM_PROखाता_HIGH_MH_IDX].dpms_on_cm_idx].voltage;

		/* 0xff0x are flags rather then an actual voltage */
		अगर ((voltage->vddci & 0xff00) == 0xff00)
			वापस;
		अगर (voltage->vddci && (voltage->vddci != rdev->pm.current_vddci)) अणु
			radeon_atom_set_voltage(rdev, voltage->vddci, SET_VOLTAGE_TYPE_ASIC_VDDCI);
			rdev->pm.current_vddci = voltage->vddci;
			DRM_DEBUG("Setting: vddci: %d\n", voltage->vddci);
		पूर्ण
	पूर्ण
पूर्ण

/**
 * evergreen_pm_prepare - pre-घातer state change callback.
 *
 * @rdev: radeon_device poपूर्णांकer
 *
 * Prepare क्रम a घातer state change (evergreen+).
 */
व्योम evergreen_pm_prepare(काष्ठा radeon_device *rdev)
अणु
	काष्ठा drm_device *ddev = rdev->ddev;
	काष्ठा drm_crtc *crtc;
	काष्ठा radeon_crtc *radeon_crtc;
	u32 पंचांगp;

	/* disable any active CRTCs */
	list_क्रम_each_entry(crtc, &ddev->mode_config.crtc_list, head) अणु
		radeon_crtc = to_radeon_crtc(crtc);
		अगर (radeon_crtc->enabled) अणु
			पंचांगp = RREG32(EVERGREEN_CRTC_CONTROL + radeon_crtc->crtc_offset);
			पंचांगp |= EVERGREEN_CRTC_DISP_READ_REQUEST_DISABLE;
			WREG32(EVERGREEN_CRTC_CONTROL + radeon_crtc->crtc_offset, पंचांगp);
		पूर्ण
	पूर्ण
पूर्ण

/**
 * evergreen_pm_finish - post-घातer state change callback.
 *
 * @rdev: radeon_device poपूर्णांकer
 *
 * Clean up after a घातer state change (evergreen+).
 */
व्योम evergreen_pm_finish(काष्ठा radeon_device *rdev)
अणु
	काष्ठा drm_device *ddev = rdev->ddev;
	काष्ठा drm_crtc *crtc;
	काष्ठा radeon_crtc *radeon_crtc;
	u32 पंचांगp;

	/* enable any active CRTCs */
	list_क्रम_each_entry(crtc, &ddev->mode_config.crtc_list, head) अणु
		radeon_crtc = to_radeon_crtc(crtc);
		अगर (radeon_crtc->enabled) अणु
			पंचांगp = RREG32(EVERGREEN_CRTC_CONTROL + radeon_crtc->crtc_offset);
			पंचांगp &= ~EVERGREEN_CRTC_DISP_READ_REQUEST_DISABLE;
			WREG32(EVERGREEN_CRTC_CONTROL + radeon_crtc->crtc_offset, पंचांगp);
		पूर्ण
	पूर्ण
पूर्ण

/**
 * evergreen_hpd_sense - hpd sense callback.
 *
 * @rdev: radeon_device poपूर्णांकer
 * @hpd: hpd (hotplug detect) pin
 *
 * Checks अगर a digital monitor is connected (evergreen+).
 * Returns true अगर connected, false अगर not connected.
 */
bool evergreen_hpd_sense(काष्ठा radeon_device *rdev, क्रमागत radeon_hpd_id hpd)
अणु
	अगर (hpd == RADEON_HPD_NONE)
		वापस false;

	वापस !!(RREG32(DC_HPDx_INT_STATUS_REG(hpd)) & DC_HPDx_SENSE);
पूर्ण

/**
 * evergreen_hpd_set_polarity - hpd set polarity callback.
 *
 * @rdev: radeon_device poपूर्णांकer
 * @hpd: hpd (hotplug detect) pin
 *
 * Set the polarity of the hpd pin (evergreen+).
 */
व्योम evergreen_hpd_set_polarity(काष्ठा radeon_device *rdev,
				क्रमागत radeon_hpd_id hpd)
अणु
	bool connected = evergreen_hpd_sense(rdev, hpd);

	अगर (hpd == RADEON_HPD_NONE)
		वापस;

	अगर (connected)
		WREG32_AND(DC_HPDx_INT_CONTROL(hpd), ~DC_HPDx_INT_POLARITY);
	अन्यथा
		WREG32_OR(DC_HPDx_INT_CONTROL(hpd), DC_HPDx_INT_POLARITY);
पूर्ण

/**
 * evergreen_hpd_init - hpd setup callback.
 *
 * @rdev: radeon_device poपूर्णांकer
 *
 * Setup the hpd pins used by the card (evergreen+).
 * Enable the pin, set the polarity, and enable the hpd पूर्णांकerrupts.
 */
व्योम evergreen_hpd_init(काष्ठा radeon_device *rdev)
अणु
	काष्ठा drm_device *dev = rdev->ddev;
	काष्ठा drm_connector *connector;
	अचिन्हित enabled = 0;
	u32 पंचांगp = DC_HPDx_CONNECTION_TIMER(0x9c4) |
		DC_HPDx_RX_INT_TIMER(0xfa) | DC_HPDx_EN;

	list_क्रम_each_entry(connector, &dev->mode_config.connector_list, head) अणु
		क्रमागत radeon_hpd_id hpd =
			to_radeon_connector(connector)->hpd.hpd;

		अगर (connector->connector_type == DRM_MODE_CONNECTOR_eDP ||
		    connector->connector_type == DRM_MODE_CONNECTOR_LVDS) अणु
			/* करोn't try to enable hpd on eDP or LVDS aव्योम अवरोधing the
			 * aux dp channel on imac and help (but not completely fix)
			 * https://bugzilla.redhat.com/show_bug.cgi?id=726143
			 * also aव्योम पूर्णांकerrupt storms during dpms.
			 */
			जारी;
		पूर्ण

		अगर (hpd == RADEON_HPD_NONE)
			जारी;

		WREG32(DC_HPDx_CONTROL(hpd), पंचांगp);
		enabled |= 1 << hpd;

		radeon_hpd_set_polarity(rdev, hpd);
	पूर्ण
	radeon_irq_kms_enable_hpd(rdev, enabled);
पूर्ण

/**
 * evergreen_hpd_fini - hpd tear करोwn callback.
 *
 * @rdev: radeon_device poपूर्णांकer
 *
 * Tear करोwn the hpd pins used by the card (evergreen+).
 * Disable the hpd पूर्णांकerrupts.
 */
व्योम evergreen_hpd_fini(काष्ठा radeon_device *rdev)
अणु
	काष्ठा drm_device *dev = rdev->ddev;
	काष्ठा drm_connector *connector;
	अचिन्हित disabled = 0;

	list_क्रम_each_entry(connector, &dev->mode_config.connector_list, head) अणु
		क्रमागत radeon_hpd_id hpd =
			to_radeon_connector(connector)->hpd.hpd;

		अगर (hpd == RADEON_HPD_NONE)
			जारी;

		WREG32(DC_HPDx_CONTROL(hpd), 0);
		disabled |= 1 << hpd;
	पूर्ण
	radeon_irq_kms_disable_hpd(rdev, disabled);
पूर्ण

/* watermark setup */

अटल u32 evergreen_line_buffer_adjust(काष्ठा radeon_device *rdev,
					काष्ठा radeon_crtc *radeon_crtc,
					काष्ठा drm_display_mode *mode,
					काष्ठा drm_display_mode *other_mode)
अणु
	u32 पंचांगp, buffer_alloc, i;
	u32 pipe_offset = radeon_crtc->crtc_id * 0x20;
	/*
	 * Line Buffer Setup
	 * There are 3 line buffers, each one shared by 2 display controllers.
	 * DC_LB_MEMORY_SPLIT controls how that line buffer is shared between
	 * the display controllers.  The paritioning is करोne via one of four
	 * preset allocations specअगरied in bits 2:0:
	 * first display controller
	 *  0 - first half of lb (3840 * 2)
	 *  1 - first 3/4 of lb (5760 * 2)
	 *  2 - whole lb (7680 * 2), other crtc must be disabled
	 *  3 - first 1/4 of lb (1920 * 2)
	 * second display controller
	 *  4 - second half of lb (3840 * 2)
	 *  5 - second 3/4 of lb (5760 * 2)
	 *  6 - whole lb (7680 * 2), other crtc must be disabled
	 *  7 - last 1/4 of lb (1920 * 2)
	 */
	/* this can get tricky अगर we have two large displays on a paired group
	 * of crtcs.  Ideally क्रम multiple large displays we'd assign them to
	 * non-linked crtcs क्रम maximum line buffer allocation.
	 */
	अगर (radeon_crtc->base.enabled && mode) अणु
		अगर (other_mode) अणु
			पंचांगp = 0; /* 1/2 */
			buffer_alloc = 1;
		पूर्ण अन्यथा अणु
			पंचांगp = 2; /* whole */
			buffer_alloc = 2;
		पूर्ण
	पूर्ण अन्यथा अणु
		पंचांगp = 0;
		buffer_alloc = 0;
	पूर्ण

	/* second controller of the pair uses second half of the lb */
	अगर (radeon_crtc->crtc_id % 2)
		पंचांगp += 4;
	WREG32(DC_LB_MEMORY_SPLIT + radeon_crtc->crtc_offset, पंचांगp);

	अगर (ASIC_IS_DCE41(rdev) || ASIC_IS_DCE5(rdev)) अणु
		WREG32(PIPE0_DMIF_BUFFER_CONTROL + pipe_offset,
		       DMIF_BUFFERS_ALLOCATED(buffer_alloc));
		क्रम (i = 0; i < rdev->usec_समयout; i++) अणु
			अगर (RREG32(PIPE0_DMIF_BUFFER_CONTROL + pipe_offset) &
			    DMIF_BUFFERS_ALLOCATED_COMPLETED)
				अवरोध;
			udelay(1);
		पूर्ण
	पूर्ण

	अगर (radeon_crtc->base.enabled && mode) अणु
		चयन (पंचांगp) अणु
		हाल 0:
		हाल 4:
		शेष:
			अगर (ASIC_IS_DCE5(rdev))
				वापस 4096 * 2;
			अन्यथा
				वापस 3840 * 2;
		हाल 1:
		हाल 5:
			अगर (ASIC_IS_DCE5(rdev))
				वापस 6144 * 2;
			अन्यथा
				वापस 5760 * 2;
		हाल 2:
		हाल 6:
			अगर (ASIC_IS_DCE5(rdev))
				वापस 8192 * 2;
			अन्यथा
				वापस 7680 * 2;
		हाल 3:
		हाल 7:
			अगर (ASIC_IS_DCE5(rdev))
				वापस 2048 * 2;
			अन्यथा
				वापस 1920 * 2;
		पूर्ण
	पूर्ण

	/* controller not enabled, so no lb used */
	वापस 0;
पूर्ण

u32 evergreen_get_number_of_dram_channels(काष्ठा radeon_device *rdev)
अणु
	u32 पंचांगp = RREG32(MC_SHARED_CHMAP);

	चयन ((पंचांगp & NOOFCHAN_MASK) >> NOOFCHAN_SHIFT) अणु
	हाल 0:
	शेष:
		वापस 1;
	हाल 1:
		वापस 2;
	हाल 2:
		वापस 4;
	हाल 3:
		वापस 8;
	पूर्ण
पूर्ण

काष्ठा evergreen_wm_params अणु
	u32 dram_channels; /* number of dram channels */
	u32 yclk;          /* bandwidth per dram data pin in kHz */
	u32 sclk;          /* engine घड़ी in kHz */
	u32 disp_clk;      /* display घड़ी in kHz */
	u32 src_width;     /* viewport width */
	u32 active_समय;   /* active display समय in ns */
	u32 blank_समय;    /* blank समय in ns */
	bool पूर्णांकerlaced;    /* mode is पूर्णांकerlaced */
	fixed20_12 vsc;    /* vertical scale ratio */
	u32 num_heads;     /* number of active crtcs */
	u32 bytes_per_pixel; /* bytes per pixel display + overlay */
	u32 lb_size;       /* line buffer allocated to pipe */
	u32 vtaps;         /* vertical scaler taps */
पूर्ण;

अटल u32 evergreen_dram_bandwidth(काष्ठा evergreen_wm_params *wm)
अणु
	/* Calculate DRAM Bandwidth and the part allocated to display. */
	fixed20_12 dram_efficiency; /* 0.7 */
	fixed20_12 yclk, dram_channels, bandwidth;
	fixed20_12 a;

	a.full = dfixed_स्थिर(1000);
	yclk.full = dfixed_स्थिर(wm->yclk);
	yclk.full = dfixed_भाग(yclk, a);
	dram_channels.full = dfixed_स्थिर(wm->dram_channels * 4);
	a.full = dfixed_स्थिर(10);
	dram_efficiency.full = dfixed_स्थिर(7);
	dram_efficiency.full = dfixed_भाग(dram_efficiency, a);
	bandwidth.full = dfixed_mul(dram_channels, yclk);
	bandwidth.full = dfixed_mul(bandwidth, dram_efficiency);

	वापस dfixed_trunc(bandwidth);
पूर्ण

अटल u32 evergreen_dram_bandwidth_क्रम_display(काष्ठा evergreen_wm_params *wm)
अणु
	/* Calculate DRAM Bandwidth and the part allocated to display. */
	fixed20_12 disp_dram_allocation; /* 0.3 to 0.7 */
	fixed20_12 yclk, dram_channels, bandwidth;
	fixed20_12 a;

	a.full = dfixed_स्थिर(1000);
	yclk.full = dfixed_स्थिर(wm->yclk);
	yclk.full = dfixed_भाग(yclk, a);
	dram_channels.full = dfixed_स्थिर(wm->dram_channels * 4);
	a.full = dfixed_स्थिर(10);
	disp_dram_allocation.full = dfixed_स्थिर(3); /* XXX worse हाल value 0.3 */
	disp_dram_allocation.full = dfixed_भाग(disp_dram_allocation, a);
	bandwidth.full = dfixed_mul(dram_channels, yclk);
	bandwidth.full = dfixed_mul(bandwidth, disp_dram_allocation);

	वापस dfixed_trunc(bandwidth);
पूर्ण

अटल u32 evergreen_data_वापस_bandwidth(काष्ठा evergreen_wm_params *wm)
अणु
	/* Calculate the display Data वापस Bandwidth */
	fixed20_12 वापस_efficiency; /* 0.8 */
	fixed20_12 sclk, bandwidth;
	fixed20_12 a;

	a.full = dfixed_स्थिर(1000);
	sclk.full = dfixed_स्थिर(wm->sclk);
	sclk.full = dfixed_भाग(sclk, a);
	a.full = dfixed_स्थिर(10);
	वापस_efficiency.full = dfixed_स्थिर(8);
	वापस_efficiency.full = dfixed_भाग(वापस_efficiency, a);
	a.full = dfixed_स्थिर(32);
	bandwidth.full = dfixed_mul(a, sclk);
	bandwidth.full = dfixed_mul(bandwidth, वापस_efficiency);

	वापस dfixed_trunc(bandwidth);
पूर्ण

अटल u32 evergreen_dmअगर_request_bandwidth(काष्ठा evergreen_wm_params *wm)
अणु
	/* Calculate the DMIF Request Bandwidth */
	fixed20_12 disp_clk_request_efficiency; /* 0.8 */
	fixed20_12 disp_clk, bandwidth;
	fixed20_12 a;

	a.full = dfixed_स्थिर(1000);
	disp_clk.full = dfixed_स्थिर(wm->disp_clk);
	disp_clk.full = dfixed_भाग(disp_clk, a);
	a.full = dfixed_स्थिर(10);
	disp_clk_request_efficiency.full = dfixed_स्थिर(8);
	disp_clk_request_efficiency.full = dfixed_भाग(disp_clk_request_efficiency, a);
	a.full = dfixed_स्थिर(32);
	bandwidth.full = dfixed_mul(a, disp_clk);
	bandwidth.full = dfixed_mul(bandwidth, disp_clk_request_efficiency);

	वापस dfixed_trunc(bandwidth);
पूर्ण

अटल u32 evergreen_available_bandwidth(काष्ठा evergreen_wm_params *wm)
अणु
	/* Calculate the Available bandwidth. Display can use this temporarily but not in average. */
	u32 dram_bandwidth = evergreen_dram_bandwidth(wm);
	u32 data_वापस_bandwidth = evergreen_data_वापस_bandwidth(wm);
	u32 dmअगर_req_bandwidth = evergreen_dmअगर_request_bandwidth(wm);

	वापस min(dram_bandwidth, min(data_वापस_bandwidth, dmअगर_req_bandwidth));
पूर्ण

अटल u32 evergreen_average_bandwidth(काष्ठा evergreen_wm_params *wm)
अणु
	/* Calculate the display mode Average Bandwidth
	 * DisplayMode should contain the source and destination dimensions,
	 * timing, etc.
	 */
	fixed20_12 bpp;
	fixed20_12 line_समय;
	fixed20_12 src_width;
	fixed20_12 bandwidth;
	fixed20_12 a;

	a.full = dfixed_स्थिर(1000);
	line_समय.full = dfixed_स्थिर(wm->active_समय + wm->blank_समय);
	line_समय.full = dfixed_भाग(line_समय, a);
	bpp.full = dfixed_स्थिर(wm->bytes_per_pixel);
	src_width.full = dfixed_स्थिर(wm->src_width);
	bandwidth.full = dfixed_mul(src_width, bpp);
	bandwidth.full = dfixed_mul(bandwidth, wm->vsc);
	bandwidth.full = dfixed_भाग(bandwidth, line_समय);

	वापस dfixed_trunc(bandwidth);
पूर्ण

अटल u32 evergreen_latency_watermark(काष्ठा evergreen_wm_params *wm)
अणु
	/* First calcualte the latency in ns */
	u32 mc_latency = 2000; /* 2000 ns. */
	u32 available_bandwidth = evergreen_available_bandwidth(wm);
	u32 worst_chunk_वापस_समय = (512 * 8 * 1000) / available_bandwidth;
	u32 cursor_line_pair_वापस_समय = (128 * 4 * 1000) / available_bandwidth;
	u32 dc_latency = 40000000 / wm->disp_clk; /* dc pipe latency */
	u32 other_heads_data_वापस_समय = ((wm->num_heads + 1) * worst_chunk_वापस_समय) +
		(wm->num_heads * cursor_line_pair_वापस_समय);
	u32 latency = mc_latency + other_heads_data_वापस_समय + dc_latency;
	u32 max_src_lines_per_dst_line, lb_fill_bw, line_fill_समय;
	fixed20_12 a, b, c;

	अगर (wm->num_heads == 0)
		वापस 0;

	a.full = dfixed_स्थिर(2);
	b.full = dfixed_स्थिर(1);
	अगर ((wm->vsc.full > a.full) ||
	    ((wm->vsc.full > b.full) && (wm->vtaps >= 3)) ||
	    (wm->vtaps >= 5) ||
	    ((wm->vsc.full >= a.full) && wm->पूर्णांकerlaced))
		max_src_lines_per_dst_line = 4;
	अन्यथा
		max_src_lines_per_dst_line = 2;

	a.full = dfixed_स्थिर(available_bandwidth);
	b.full = dfixed_स्थिर(wm->num_heads);
	a.full = dfixed_भाग(a, b);

	lb_fill_bw = min(dfixed_trunc(a), wm->disp_clk * wm->bytes_per_pixel / 1000);

	a.full = dfixed_स्थिर(max_src_lines_per_dst_line * wm->src_width * wm->bytes_per_pixel);
	b.full = dfixed_स्थिर(1000);
	c.full = dfixed_स्थिर(lb_fill_bw);
	b.full = dfixed_भाग(c, b);
	a.full = dfixed_भाग(a, b);
	line_fill_समय = dfixed_trunc(a);

	अगर (line_fill_समय < wm->active_समय)
		वापस latency;
	अन्यथा
		वापस latency + (line_fill_समय - wm->active_समय);

पूर्ण

अटल bool evergreen_average_bandwidth_vs_dram_bandwidth_क्रम_display(काष्ठा evergreen_wm_params *wm)
अणु
	अगर (evergreen_average_bandwidth(wm) <=
	    (evergreen_dram_bandwidth_क्रम_display(wm) / wm->num_heads))
		वापस true;
	अन्यथा
		वापस false;
पूर्ण;

अटल bool evergreen_average_bandwidth_vs_available_bandwidth(काष्ठा evergreen_wm_params *wm)
अणु
	अगर (evergreen_average_bandwidth(wm) <=
	    (evergreen_available_bandwidth(wm) / wm->num_heads))
		वापस true;
	अन्यथा
		वापस false;
पूर्ण;

अटल bool evergreen_check_latency_hiding(काष्ठा evergreen_wm_params *wm)
अणु
	u32 lb_partitions = wm->lb_size / wm->src_width;
	u32 line_समय = wm->active_समय + wm->blank_समय;
	u32 latency_tolerant_lines;
	u32 latency_hiding;
	fixed20_12 a;

	a.full = dfixed_स्थिर(1);
	अगर (wm->vsc.full > a.full)
		latency_tolerant_lines = 1;
	अन्यथा अणु
		अगर (lb_partitions <= (wm->vtaps + 1))
			latency_tolerant_lines = 1;
		अन्यथा
			latency_tolerant_lines = 2;
	पूर्ण

	latency_hiding = (latency_tolerant_lines * line_समय + wm->blank_समय);

	अगर (evergreen_latency_watermark(wm) <= latency_hiding)
		वापस true;
	अन्यथा
		वापस false;
पूर्ण

अटल व्योम evergreen_program_watermarks(काष्ठा radeon_device *rdev,
					 काष्ठा radeon_crtc *radeon_crtc,
					 u32 lb_size, u32 num_heads)
अणु
	काष्ठा drm_display_mode *mode = &radeon_crtc->base.mode;
	काष्ठा evergreen_wm_params wm_low, wm_high;
	u32 dram_channels;
	u32 active_समय;
	u32 line_समय = 0;
	u32 latency_watermark_a = 0, latency_watermark_b = 0;
	u32 priority_a_mark = 0, priority_b_mark = 0;
	u32 priority_a_cnt = PRIORITY_OFF;
	u32 priority_b_cnt = PRIORITY_OFF;
	u32 pipe_offset = radeon_crtc->crtc_id * 16;
	u32 पंचांगp, arb_control3;
	fixed20_12 a, b, c;

	अगर (radeon_crtc->base.enabled && num_heads && mode) अणु
		active_समय = (u32) भाग_u64((u64)mode->crtc_hdisplay * 1000000,
					    (u32)mode->घड़ी);
		line_समय = (u32) भाग_u64((u64)mode->crtc_htotal * 1000000,
					  (u32)mode->घड़ी);
		line_समय = min(line_समय, (u32)65535);
		priority_a_cnt = 0;
		priority_b_cnt = 0;
		dram_channels = evergreen_get_number_of_dram_channels(rdev);

		/* watermark क्रम high घड़ीs */
		अगर ((rdev->pm.pm_method == PM_METHOD_DPM) && rdev->pm.dpm_enabled) अणु
			wm_high.yclk =
				radeon_dpm_get_mclk(rdev, false) * 10;
			wm_high.sclk =
				radeon_dpm_get_sclk(rdev, false) * 10;
		पूर्ण अन्यथा अणु
			wm_high.yclk = rdev->pm.current_mclk * 10;
			wm_high.sclk = rdev->pm.current_sclk * 10;
		पूर्ण

		wm_high.disp_clk = mode->घड़ी;
		wm_high.src_width = mode->crtc_hdisplay;
		wm_high.active_समय = active_समय;
		wm_high.blank_समय = line_समय - wm_high.active_समय;
		wm_high.पूर्णांकerlaced = false;
		अगर (mode->flags & DRM_MODE_FLAG_INTERLACE)
			wm_high.पूर्णांकerlaced = true;
		wm_high.vsc = radeon_crtc->vsc;
		wm_high.vtaps = 1;
		अगर (radeon_crtc->rmx_type != RMX_OFF)
			wm_high.vtaps = 2;
		wm_high.bytes_per_pixel = 4; /* XXX: get this from fb config */
		wm_high.lb_size = lb_size;
		wm_high.dram_channels = dram_channels;
		wm_high.num_heads = num_heads;

		/* watermark क्रम low घड़ीs */
		अगर ((rdev->pm.pm_method == PM_METHOD_DPM) && rdev->pm.dpm_enabled) अणु
			wm_low.yclk =
				radeon_dpm_get_mclk(rdev, true) * 10;
			wm_low.sclk =
				radeon_dpm_get_sclk(rdev, true) * 10;
		पूर्ण अन्यथा अणु
			wm_low.yclk = rdev->pm.current_mclk * 10;
			wm_low.sclk = rdev->pm.current_sclk * 10;
		पूर्ण

		wm_low.disp_clk = mode->घड़ी;
		wm_low.src_width = mode->crtc_hdisplay;
		wm_low.active_समय = active_समय;
		wm_low.blank_समय = line_समय - wm_low.active_समय;
		wm_low.पूर्णांकerlaced = false;
		अगर (mode->flags & DRM_MODE_FLAG_INTERLACE)
			wm_low.पूर्णांकerlaced = true;
		wm_low.vsc = radeon_crtc->vsc;
		wm_low.vtaps = 1;
		अगर (radeon_crtc->rmx_type != RMX_OFF)
			wm_low.vtaps = 2;
		wm_low.bytes_per_pixel = 4; /* XXX: get this from fb config */
		wm_low.lb_size = lb_size;
		wm_low.dram_channels = dram_channels;
		wm_low.num_heads = num_heads;

		/* set क्रम high घड़ीs */
		latency_watermark_a = min(evergreen_latency_watermark(&wm_high), (u32)65535);
		/* set क्रम low घड़ीs */
		latency_watermark_b = min(evergreen_latency_watermark(&wm_low), (u32)65535);

		/* possibly क्रमce display priority to high */
		/* should really करो this at mode validation समय... */
		अगर (!evergreen_average_bandwidth_vs_dram_bandwidth_क्रम_display(&wm_high) ||
		    !evergreen_average_bandwidth_vs_available_bandwidth(&wm_high) ||
		    !evergreen_check_latency_hiding(&wm_high) ||
		    (rdev->disp_priority == 2)) अणु
			DRM_DEBUG_KMS("force priority a to high\n");
			priority_a_cnt |= PRIORITY_ALWAYS_ON;
		पूर्ण
		अगर (!evergreen_average_bandwidth_vs_dram_bandwidth_क्रम_display(&wm_low) ||
		    !evergreen_average_bandwidth_vs_available_bandwidth(&wm_low) ||
		    !evergreen_check_latency_hiding(&wm_low) ||
		    (rdev->disp_priority == 2)) अणु
			DRM_DEBUG_KMS("force priority b to high\n");
			priority_b_cnt |= PRIORITY_ALWAYS_ON;
		पूर्ण

		a.full = dfixed_स्थिर(1000);
		b.full = dfixed_स्थिर(mode->घड़ी);
		b.full = dfixed_भाग(b, a);
		c.full = dfixed_स्थिर(latency_watermark_a);
		c.full = dfixed_mul(c, b);
		c.full = dfixed_mul(c, radeon_crtc->hsc);
		c.full = dfixed_भाग(c, a);
		a.full = dfixed_स्थिर(16);
		c.full = dfixed_भाग(c, a);
		priority_a_mark = dfixed_trunc(c);
		priority_a_cnt |= priority_a_mark & PRIORITY_MARK_MASK;

		a.full = dfixed_स्थिर(1000);
		b.full = dfixed_स्थिर(mode->घड़ी);
		b.full = dfixed_भाग(b, a);
		c.full = dfixed_स्थिर(latency_watermark_b);
		c.full = dfixed_mul(c, b);
		c.full = dfixed_mul(c, radeon_crtc->hsc);
		c.full = dfixed_भाग(c, a);
		a.full = dfixed_स्थिर(16);
		c.full = dfixed_भाग(c, a);
		priority_b_mark = dfixed_trunc(c);
		priority_b_cnt |= priority_b_mark & PRIORITY_MARK_MASK;

		/* Save number of lines the linebuffer leads beक्रमe the scanout */
		radeon_crtc->lb_vblank_lead_lines = DIV_ROUND_UP(lb_size, mode->crtc_hdisplay);
	पूर्ण

	/* select wm A */
	arb_control3 = RREG32(PIPE0_ARBITRATION_CONTROL3 + pipe_offset);
	पंचांगp = arb_control3;
	पंचांगp &= ~LATENCY_WATERMARK_MASK(3);
	पंचांगp |= LATENCY_WATERMARK_MASK(1);
	WREG32(PIPE0_ARBITRATION_CONTROL3 + pipe_offset, पंचांगp);
	WREG32(PIPE0_LATENCY_CONTROL + pipe_offset,
	       (LATENCY_LOW_WATERMARK(latency_watermark_a) |
		LATENCY_HIGH_WATERMARK(line_समय)));
	/* select wm B */
	पंचांगp = RREG32(PIPE0_ARBITRATION_CONTROL3 + pipe_offset);
	पंचांगp &= ~LATENCY_WATERMARK_MASK(3);
	पंचांगp |= LATENCY_WATERMARK_MASK(2);
	WREG32(PIPE0_ARBITRATION_CONTROL3 + pipe_offset, पंचांगp);
	WREG32(PIPE0_LATENCY_CONTROL + pipe_offset,
	       (LATENCY_LOW_WATERMARK(latency_watermark_b) |
		LATENCY_HIGH_WATERMARK(line_समय)));
	/* restore original selection */
	WREG32(PIPE0_ARBITRATION_CONTROL3 + pipe_offset, arb_control3);

	/* ग_लिखो the priority marks */
	WREG32(PRIORITY_A_CNT + radeon_crtc->crtc_offset, priority_a_cnt);
	WREG32(PRIORITY_B_CNT + radeon_crtc->crtc_offset, priority_b_cnt);

	/* save values क्रम DPM */
	radeon_crtc->line_समय = line_समय;
	radeon_crtc->wm_high = latency_watermark_a;
	radeon_crtc->wm_low = latency_watermark_b;
पूर्ण

/**
 * evergreen_bandwidth_update - update display watermarks callback.
 *
 * @rdev: radeon_device poपूर्णांकer
 *
 * Update the display watermarks based on the requested mode(s)
 * (evergreen+).
 */
व्योम evergreen_bandwidth_update(काष्ठा radeon_device *rdev)
अणु
	काष्ठा drm_display_mode *mode0 = शून्य;
	काष्ठा drm_display_mode *mode1 = शून्य;
	u32 num_heads = 0, lb_size;
	पूर्णांक i;

	अगर (!rdev->mode_info.mode_config_initialized)
		वापस;

	radeon_update_display_priority(rdev);

	क्रम (i = 0; i < rdev->num_crtc; i++) अणु
		अगर (rdev->mode_info.crtcs[i]->base.enabled)
			num_heads++;
	पूर्ण
	क्रम (i = 0; i < rdev->num_crtc; i += 2) अणु
		mode0 = &rdev->mode_info.crtcs[i]->base.mode;
		mode1 = &rdev->mode_info.crtcs[i+1]->base.mode;
		lb_size = evergreen_line_buffer_adjust(rdev, rdev->mode_info.crtcs[i], mode0, mode1);
		evergreen_program_watermarks(rdev, rdev->mode_info.crtcs[i], lb_size, num_heads);
		lb_size = evergreen_line_buffer_adjust(rdev, rdev->mode_info.crtcs[i+1], mode1, mode0);
		evergreen_program_watermarks(rdev, rdev->mode_info.crtcs[i+1], lb_size, num_heads);
	पूर्ण
पूर्ण

/**
 * evergreen_mc_रुको_क्रम_idle - रुको क्रम MC idle callback.
 *
 * @rdev: radeon_device poपूर्णांकer
 *
 * Wait क्रम the MC (memory controller) to be idle.
 * (evergreen+).
 * Returns 0 अगर the MC is idle, -1 अगर not.
 */
पूर्णांक evergreen_mc_रुको_क्रम_idle(काष्ठा radeon_device *rdev)
अणु
	अचिन्हित i;
	u32 पंचांगp;

	क्रम (i = 0; i < rdev->usec_समयout; i++) अणु
		/* पढ़ो MC_STATUS */
		पंचांगp = RREG32(SRBM_STATUS) & 0x1F00;
		अगर (!पंचांगp)
			वापस 0;
		udelay(1);
	पूर्ण
	वापस -1;
पूर्ण

/*
 * GART
 */
व्योम evergreen_pcie_gart_tlb_flush(काष्ठा radeon_device *rdev)
अणु
	अचिन्हित i;
	u32 पंचांगp;

	WREG32(HDP_MEM_COHERENCY_FLUSH_CNTL, 0x1);

	WREG32(VM_CONTEXT0_REQUEST_RESPONSE, REQUEST_TYPE(1));
	क्रम (i = 0; i < rdev->usec_समयout; i++) अणु
		/* पढ़ो MC_STATUS */
		पंचांगp = RREG32(VM_CONTEXT0_REQUEST_RESPONSE);
		पंचांगp = (पंचांगp & RESPONSE_TYPE_MASK) >> RESPONSE_TYPE_SHIFT;
		अगर (पंचांगp == 2) अणु
			pr_warn("[drm] r600 flush TLB failed\n");
			वापस;
		पूर्ण
		अगर (पंचांगp) अणु
			वापस;
		पूर्ण
		udelay(1);
	पूर्ण
पूर्ण

अटल पूर्णांक evergreen_pcie_gart_enable(काष्ठा radeon_device *rdev)
अणु
	u32 पंचांगp;
	पूर्णांक r;

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
	अगर (rdev->flags & RADEON_IS_IGP) अणु
		WREG32(FUS_MC_VM_MD_L1_TLB0_CNTL, पंचांगp);
		WREG32(FUS_MC_VM_MD_L1_TLB1_CNTL, पंचांगp);
		WREG32(FUS_MC_VM_MD_L1_TLB2_CNTL, पंचांगp);
	पूर्ण अन्यथा अणु
		WREG32(MC_VM_MD_L1_TLB0_CNTL, पंचांगp);
		WREG32(MC_VM_MD_L1_TLB1_CNTL, पंचांगp);
		WREG32(MC_VM_MD_L1_TLB2_CNTL, पंचांगp);
		अगर ((rdev->family == CHIP_JUNIPER) ||
		    (rdev->family == CHIP_CYPRESS) ||
		    (rdev->family == CHIP_HEMLOCK) ||
		    (rdev->family == CHIP_BARTS))
			WREG32(MC_VM_MD_L1_TLB3_CNTL, पंचांगp);
	पूर्ण
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
	WREG32(VM_CONTEXT1_CNTL, 0);

	evergreen_pcie_gart_tlb_flush(rdev);
	DRM_INFO("PCIE GART of %uM enabled (table at 0x%016llX).\n",
		 (अचिन्हित)(rdev->mc.gtt_size >> 20),
		 (अचिन्हित दीर्घ दीर्घ)rdev->gart.table_addr);
	rdev->gart.पढ़ोy = true;
	वापस 0;
पूर्ण

अटल व्योम evergreen_pcie_gart_disable(काष्ठा radeon_device *rdev)
अणु
	u32 पंचांगp;

	/* Disable all tables */
	WREG32(VM_CONTEXT0_CNTL, 0);
	WREG32(VM_CONTEXT1_CNTL, 0);

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

अटल व्योम evergreen_pcie_gart_fini(काष्ठा radeon_device *rdev)
अणु
	evergreen_pcie_gart_disable(rdev);
	radeon_gart_table_vram_मुक्त(rdev);
	radeon_gart_fini(rdev);
पूर्ण


अटल व्योम evergreen_agp_enable(काष्ठा radeon_device *rdev)
अणु
	u32 पंचांगp;

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
	WREG32(VM_CONTEXT0_CNTL, 0);
	WREG32(VM_CONTEXT1_CNTL, 0);
पूर्ण

अटल स्थिर अचिन्हित ni_dig_offsets[] =
अणु
	NI_DIG0_REGISTER_OFFSET,
	NI_DIG1_REGISTER_OFFSET,
	NI_DIG2_REGISTER_OFFSET,
	NI_DIG3_REGISTER_OFFSET,
	NI_DIG4_REGISTER_OFFSET,
	NI_DIG5_REGISTER_OFFSET
पूर्ण;

अटल स्थिर अचिन्हित ni_tx_offsets[] =
अणु
	NI_DCIO_UNIPHY0_UNIPHY_TX_CONTROL1,
	NI_DCIO_UNIPHY1_UNIPHY_TX_CONTROL1,
	NI_DCIO_UNIPHY2_UNIPHY_TX_CONTROL1,
	NI_DCIO_UNIPHY3_UNIPHY_TX_CONTROL1,
	NI_DCIO_UNIPHY4_UNIPHY_TX_CONTROL1,
	NI_DCIO_UNIPHY5_UNIPHY_TX_CONTROL1
पूर्ण;

अटल स्थिर अचिन्हित evergreen_dp_offsets[] =
अणु
	EVERGREEN_DP0_REGISTER_OFFSET,
	EVERGREEN_DP1_REGISTER_OFFSET,
	EVERGREEN_DP2_REGISTER_OFFSET,
	EVERGREEN_DP3_REGISTER_OFFSET,
	EVERGREEN_DP4_REGISTER_OFFSET,
	EVERGREEN_DP5_REGISTER_OFFSET
पूर्ण;

अटल स्थिर अचिन्हित evergreen_disp_पूर्णांक_status[] =
अणु
	DISP_INTERRUPT_STATUS,
	DISP_INTERRUPT_STATUS_CONTINUE,
	DISP_INTERRUPT_STATUS_CONTINUE2,
	DISP_INTERRUPT_STATUS_CONTINUE3,
	DISP_INTERRUPT_STATUS_CONTINUE4,
	DISP_INTERRUPT_STATUS_CONTINUE5
पूर्ण;

/*
 * Assumption is that EVERGREEN_CRTC_MASTER_EN enable क्रम requested crtc
 * We go from crtc to connector and it is not relible  since it
 * should be an opposite direction .If crtc is enable then
 * find the dig_fe which selects this crtc and insure that it enable.
 * अगर such dig_fe is found then find dig_be which selects found dig_be and
 * insure that it enable and in DP_SST mode.
 * अगर UNIPHY_PLL_CONTROL1.enable then we should disconnect timing
 * from dp symbols घड़ीs .
 */
अटल bool evergreen_is_dp_sst_stream_enabled(काष्ठा radeon_device *rdev,
					       अचिन्हित crtc_id, अचिन्हित *ret_dig_fe)
अणु
	अचिन्हित i;
	अचिन्हित dig_fe;
	अचिन्हित dig_be;
	अचिन्हित dig_en_be;
	अचिन्हित uniphy_pll;
	अचिन्हित digs_fe_selected;
	अचिन्हित dig_be_mode;
	अचिन्हित dig_fe_mask;
	bool is_enabled = false;
	bool found_crtc = false;

	/* loop through all running dig_fe to find selected crtc */
	क्रम (i = 0; i < ARRAY_SIZE(ni_dig_offsets); i++) अणु
		dig_fe = RREG32(NI_DIG_FE_CNTL + ni_dig_offsets[i]);
		अगर (dig_fe & NI_DIG_FE_CNTL_SYMCLK_FE_ON &&
		    crtc_id == NI_DIG_FE_CNTL_SOURCE_SELECT(dig_fe)) अणु
			/* found running pipe */
			found_crtc = true;
			dig_fe_mask = 1 << i;
			dig_fe = i;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (found_crtc) अणु
		/* loop through all running dig_be to find selected dig_fe */
		क्रम (i = 0; i < ARRAY_SIZE(ni_dig_offsets); i++) अणु
			dig_be = RREG32(NI_DIG_BE_CNTL + ni_dig_offsets[i]);
			/* अगर dig_fe_selected by dig_be? */
			digs_fe_selected = NI_DIG_BE_CNTL_FE_SOURCE_SELECT(dig_be);
			dig_be_mode = NI_DIG_FE_CNTL_MODE(dig_be);
			अगर (dig_fe_mask &  digs_fe_selected &&
			    /* अगर dig_be in sst mode? */
			    dig_be_mode == NI_DIG_BE_DPSST) अणु
				dig_en_be = RREG32(NI_DIG_BE_EN_CNTL +
						   ni_dig_offsets[i]);
				uniphy_pll = RREG32(NI_DCIO_UNIPHY0_PLL_CONTROL1 +
						    ni_tx_offsets[i]);
				/* dig_be enable and tx is running */
				अगर (dig_en_be & NI_DIG_BE_EN_CNTL_ENABLE &&
				    dig_en_be & NI_DIG_BE_EN_CNTL_SYMBCLK_ON &&
				    uniphy_pll & NI_DCIO_UNIPHY0_PLL_CONTROL1_ENABLE) अणु
					is_enabled = true;
					*ret_dig_fe = dig_fe;
					अवरोध;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण

	वापस is_enabled;
पूर्ण

/*
 * Blank dig when in dp sst mode
 * Dig ignores crtc timing
 */
अटल व्योम evergreen_blank_dp_output(काष्ठा radeon_device *rdev,
				      अचिन्हित dig_fe)
अणु
	अचिन्हित stream_ctrl;
	अचिन्हित fअगरo_ctrl;
	अचिन्हित counter = 0;

	अगर (dig_fe >= ARRAY_SIZE(evergreen_dp_offsets)) अणु
		DRM_ERROR("invalid dig_fe %d\n", dig_fe);
		वापस;
	पूर्ण

	stream_ctrl = RREG32(EVERGREEN_DP_VID_STREAM_CNTL +
			     evergreen_dp_offsets[dig_fe]);
	अगर (!(stream_ctrl & EVERGREEN_DP_VID_STREAM_CNTL_ENABLE)) अणु
		DRM_ERROR("dig %d , should be enable\n", dig_fe);
		वापस;
	पूर्ण

	stream_ctrl &=~EVERGREEN_DP_VID_STREAM_CNTL_ENABLE;
	WREG32(EVERGREEN_DP_VID_STREAM_CNTL +
	       evergreen_dp_offsets[dig_fe], stream_ctrl);

	stream_ctrl = RREG32(EVERGREEN_DP_VID_STREAM_CNTL +
			     evergreen_dp_offsets[dig_fe]);
	जबतक (counter < 32 && stream_ctrl & EVERGREEN_DP_VID_STREAM_STATUS) अणु
		msleep(1);
		counter++;
		stream_ctrl = RREG32(EVERGREEN_DP_VID_STREAM_CNTL +
				     evergreen_dp_offsets[dig_fe]);
	पूर्ण
	अगर (counter >= 32 )
		DRM_ERROR("counter exceeds %d\n", counter);

	fअगरo_ctrl = RREG32(EVERGREEN_DP_STEER_FIFO + evergreen_dp_offsets[dig_fe]);
	fअगरo_ctrl |= EVERGREEN_DP_STEER_FIFO_RESET;
	WREG32(EVERGREEN_DP_STEER_FIFO + evergreen_dp_offsets[dig_fe], fअगरo_ctrl);

पूर्ण

व्योम evergreen_mc_stop(काष्ठा radeon_device *rdev, काष्ठा evergreen_mc_save *save)
अणु
	u32 crtc_enabled, पंचांगp, frame_count, blackout;
	पूर्णांक i, j;
	अचिन्हित dig_fe;

	अगर (!ASIC_IS_NODCE(rdev)) अणु
		save->vga_render_control = RREG32(VGA_RENDER_CONTROL);
		save->vga_hdp_control = RREG32(VGA_HDP_CONTROL);

		/* disable VGA render */
		WREG32(VGA_RENDER_CONTROL, 0);
	पूर्ण
	/* blank the display controllers */
	क्रम (i = 0; i < rdev->num_crtc; i++) अणु
		crtc_enabled = RREG32(EVERGREEN_CRTC_CONTROL + crtc_offsets[i]) & EVERGREEN_CRTC_MASTER_EN;
		अगर (crtc_enabled) अणु
			save->crtc_enabled[i] = true;
			अगर (ASIC_IS_DCE6(rdev)) अणु
				पंचांगp = RREG32(EVERGREEN_CRTC_BLANK_CONTROL + crtc_offsets[i]);
				अगर (!(पंचांगp & EVERGREEN_CRTC_BLANK_DATA_EN)) अणु
					radeon_रुको_क्रम_vblank(rdev, i);
					WREG32(EVERGREEN_CRTC_UPDATE_LOCK + crtc_offsets[i], 1);
					पंचांगp |= EVERGREEN_CRTC_BLANK_DATA_EN;
					WREG32(EVERGREEN_CRTC_BLANK_CONTROL + crtc_offsets[i], पंचांगp);
					WREG32(EVERGREEN_CRTC_UPDATE_LOCK + crtc_offsets[i], 0);
				पूर्ण
			पूर्ण अन्यथा अणु
				पंचांगp = RREG32(EVERGREEN_CRTC_CONTROL + crtc_offsets[i]);
				अगर (!(पंचांगp & EVERGREEN_CRTC_DISP_READ_REQUEST_DISABLE)) अणु
					radeon_रुको_क्रम_vblank(rdev, i);
					WREG32(EVERGREEN_CRTC_UPDATE_LOCK + crtc_offsets[i], 1);
					पंचांगp |= EVERGREEN_CRTC_DISP_READ_REQUEST_DISABLE;
					WREG32(EVERGREEN_CRTC_CONTROL + crtc_offsets[i], पंचांगp);
					WREG32(EVERGREEN_CRTC_UPDATE_LOCK + crtc_offsets[i], 0);
				पूर्ण
			पूर्ण
			/* रुको क्रम the next frame */
			frame_count = radeon_get_vblank_counter(rdev, i);
			क्रम (j = 0; j < rdev->usec_समयout; j++) अणु
				अगर (radeon_get_vblank_counter(rdev, i) != frame_count)
					अवरोध;
				udelay(1);
			पूर्ण
			/*we should disable dig अगर it drives dp sst*/
			/*but we are in radeon_device_init and the topology is unknown*/
			/*and it is available after radeon_modeset_init*/
			/*the following method radeon_atom_encoder_dpms_dig*/
			/*करोes the job अगर we initialize it properly*/
			/*क्रम now we करो it this manually*/
			/**/
			अगर (ASIC_IS_DCE5(rdev) &&
			    evergreen_is_dp_sst_stream_enabled(rdev, i ,&dig_fe))
				evergreen_blank_dp_output(rdev, dig_fe);
			/*we could हटाओ 6 lines below*/
			/* XXX this is a hack to aव्योम strange behavior with EFI on certain प्रणालीs */
			WREG32(EVERGREEN_CRTC_UPDATE_LOCK + crtc_offsets[i], 1);
			पंचांगp = RREG32(EVERGREEN_CRTC_CONTROL + crtc_offsets[i]);
			पंचांगp &= ~EVERGREEN_CRTC_MASTER_EN;
			WREG32(EVERGREEN_CRTC_CONTROL + crtc_offsets[i], पंचांगp);
			WREG32(EVERGREEN_CRTC_UPDATE_LOCK + crtc_offsets[i], 0);
			save->crtc_enabled[i] = false;
			/* ***** */
		पूर्ण अन्यथा अणु
			save->crtc_enabled[i] = false;
		पूर्ण
	पूर्ण

	radeon_mc_रुको_क्रम_idle(rdev);

	blackout = RREG32(MC_SHARED_BLACKOUT_CNTL);
	अगर ((blackout & BLACKOUT_MODE_MASK) != 1) अणु
		/* Block CPU access */
		WREG32(BIF_FB_EN, 0);
		/* blackout the MC */
		blackout &= ~BLACKOUT_MODE_MASK;
		WREG32(MC_SHARED_BLACKOUT_CNTL, blackout | 1);
	पूर्ण
	/* रुको क्रम the MC to settle */
	udelay(100);

	/* lock द्विगुन buffered regs */
	क्रम (i = 0; i < rdev->num_crtc; i++) अणु
		अगर (save->crtc_enabled[i]) अणु
			पंचांगp = RREG32(EVERGREEN_GRPH_UPDATE + crtc_offsets[i]);
			अगर (!(पंचांगp & EVERGREEN_GRPH_UPDATE_LOCK)) अणु
				पंचांगp |= EVERGREEN_GRPH_UPDATE_LOCK;
				WREG32(EVERGREEN_GRPH_UPDATE + crtc_offsets[i], पंचांगp);
			पूर्ण
			पंचांगp = RREG32(EVERGREEN_MASTER_UPDATE_LOCK + crtc_offsets[i]);
			अगर (!(पंचांगp & 1)) अणु
				पंचांगp |= 1;
				WREG32(EVERGREEN_MASTER_UPDATE_LOCK + crtc_offsets[i], पंचांगp);
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

व्योम evergreen_mc_resume(काष्ठा radeon_device *rdev, काष्ठा evergreen_mc_save *save)
अणु
	u32 पंचांगp, frame_count;
	पूर्णांक i, j;

	/* update crtc base addresses */
	क्रम (i = 0; i < rdev->num_crtc; i++) अणु
		WREG32(EVERGREEN_GRPH_PRIMARY_SURFACE_ADDRESS_HIGH + crtc_offsets[i],
		       upper_32_bits(rdev->mc.vram_start));
		WREG32(EVERGREEN_GRPH_SECONDARY_SURFACE_ADDRESS_HIGH + crtc_offsets[i],
		       upper_32_bits(rdev->mc.vram_start));
		WREG32(EVERGREEN_GRPH_PRIMARY_SURFACE_ADDRESS + crtc_offsets[i],
		       (u32)rdev->mc.vram_start);
		WREG32(EVERGREEN_GRPH_SECONDARY_SURFACE_ADDRESS + crtc_offsets[i],
		       (u32)rdev->mc.vram_start);
	पूर्ण

	अगर (!ASIC_IS_NODCE(rdev)) अणु
		WREG32(EVERGREEN_VGA_MEMORY_BASE_ADDRESS_HIGH, upper_32_bits(rdev->mc.vram_start));
		WREG32(EVERGREEN_VGA_MEMORY_BASE_ADDRESS, (u32)rdev->mc.vram_start);
	पूर्ण

	/* unlock regs and रुको क्रम update */
	क्रम (i = 0; i < rdev->num_crtc; i++) अणु
		अगर (save->crtc_enabled[i]) अणु
			पंचांगp = RREG32(EVERGREEN_MASTER_UPDATE_MODE + crtc_offsets[i]);
			अगर ((पंचांगp & 0x7) != 0) अणु
				पंचांगp &= ~0x7;
				WREG32(EVERGREEN_MASTER_UPDATE_MODE + crtc_offsets[i], पंचांगp);
			पूर्ण
			पंचांगp = RREG32(EVERGREEN_GRPH_UPDATE + crtc_offsets[i]);
			अगर (पंचांगp & EVERGREEN_GRPH_UPDATE_LOCK) अणु
				पंचांगp &= ~EVERGREEN_GRPH_UPDATE_LOCK;
				WREG32(EVERGREEN_GRPH_UPDATE + crtc_offsets[i], पंचांगp);
			पूर्ण
			पंचांगp = RREG32(EVERGREEN_MASTER_UPDATE_LOCK + crtc_offsets[i]);
			अगर (पंचांगp & 1) अणु
				पंचांगp &= ~1;
				WREG32(EVERGREEN_MASTER_UPDATE_LOCK + crtc_offsets[i], पंचांगp);
			पूर्ण
			क्रम (j = 0; j < rdev->usec_समयout; j++) अणु
				पंचांगp = RREG32(EVERGREEN_GRPH_UPDATE + crtc_offsets[i]);
				अगर ((पंचांगp & EVERGREEN_GRPH_SURFACE_UPDATE_PENDING) == 0)
					अवरोध;
				udelay(1);
			पूर्ण
		पूर्ण
	पूर्ण

	/* unblackout the MC */
	पंचांगp = RREG32(MC_SHARED_BLACKOUT_CNTL);
	पंचांगp &= ~BLACKOUT_MODE_MASK;
	WREG32(MC_SHARED_BLACKOUT_CNTL, पंचांगp);
	/* allow CPU access */
	WREG32(BIF_FB_EN, FB_READ_EN | FB_WRITE_EN);

	क्रम (i = 0; i < rdev->num_crtc; i++) अणु
		अगर (save->crtc_enabled[i]) अणु
			अगर (ASIC_IS_DCE6(rdev)) अणु
				पंचांगp = RREG32(EVERGREEN_CRTC_BLANK_CONTROL + crtc_offsets[i]);
				पंचांगp &= ~EVERGREEN_CRTC_BLANK_DATA_EN;
				WREG32(EVERGREEN_CRTC_UPDATE_LOCK + crtc_offsets[i], 1);
				WREG32(EVERGREEN_CRTC_BLANK_CONTROL + crtc_offsets[i], पंचांगp);
				WREG32(EVERGREEN_CRTC_UPDATE_LOCK + crtc_offsets[i], 0);
			पूर्ण अन्यथा अणु
				पंचांगp = RREG32(EVERGREEN_CRTC_CONTROL + crtc_offsets[i]);
				पंचांगp &= ~EVERGREEN_CRTC_DISP_READ_REQUEST_DISABLE;
				WREG32(EVERGREEN_CRTC_UPDATE_LOCK + crtc_offsets[i], 1);
				WREG32(EVERGREEN_CRTC_CONTROL + crtc_offsets[i], पंचांगp);
				WREG32(EVERGREEN_CRTC_UPDATE_LOCK + crtc_offsets[i], 0);
			पूर्ण
			/* रुको क्रम the next frame */
			frame_count = radeon_get_vblank_counter(rdev, i);
			क्रम (j = 0; j < rdev->usec_समयout; j++) अणु
				अगर (radeon_get_vblank_counter(rdev, i) != frame_count)
					अवरोध;
				udelay(1);
			पूर्ण
		पूर्ण
	पूर्ण
	अगर (!ASIC_IS_NODCE(rdev)) अणु
		/* Unlock vga access */
		WREG32(VGA_HDP_CONTROL, save->vga_hdp_control);
		mdelay(1);
		WREG32(VGA_RENDER_CONTROL, save->vga_render_control);
	पूर्ण
पूर्ण

व्योम evergreen_mc_program(काष्ठा radeon_device *rdev)
अणु
	काष्ठा evergreen_mc_save save;
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
	WREG32(HDP_REG_COHERENCY_FLUSH_CNTL, 0);

	evergreen_mc_stop(rdev, &save);
	अगर (evergreen_mc_रुको_क्रम_idle(rdev)) अणु
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
	/* llano/ontario only */
	अगर ((rdev->family == CHIP_PALM) ||
	    (rdev->family == CHIP_SUMO) ||
	    (rdev->family == CHIP_SUMO2)) अणु
		पंचांगp = RREG32(MC_FUS_VM_FB_OFFSET) & 0x000FFFFF;
		पंचांगp |= ((rdev->mc.vram_end >> 20) & 0xF) << 24;
		पंचांगp |= ((rdev->mc.vram_start >> 20) & 0xF) << 20;
		WREG32(MC_FUS_VM_FB_OFFSET, पंचांगp);
	पूर्ण
	पंचांगp = ((rdev->mc.vram_end >> 24) & 0xFFFF) << 16;
	पंचांगp |= ((rdev->mc.vram_start >> 24) & 0xFFFF);
	WREG32(MC_VM_FB_LOCATION, पंचांगp);
	WREG32(HDP_NONSURFACE_BASE, (rdev->mc.vram_start >> 8));
	WREG32(HDP_NONSURFACE_INFO, (2 << 7) | (1 << 30));
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
	अगर (evergreen_mc_रुको_क्रम_idle(rdev)) अणु
		dev_warn(rdev->dev, "Wait for MC idle timedout !\n");
	पूर्ण
	evergreen_mc_resume(rdev, &save);
	/* we need to own VRAM, so turn off the VGA renderer here
	 * to stop it overwriting our objects */
	rv515_vga_render_disable(rdev);
पूर्ण

/*
 * CP.
 */
व्योम evergreen_ring_ib_execute(काष्ठा radeon_device *rdev, काष्ठा radeon_ib *ib)
अणु
	काष्ठा radeon_ring *ring = &rdev->ring[ib->ring];
	u32 next_rptr;

	/* set to DX10/11 mode */
	radeon_ring_ग_लिखो(ring, PACKET3(PACKET3_MODE_CONTROL, 0));
	radeon_ring_ग_लिखो(ring, 1);

	अगर (ring->rptr_save_reg) अणु
		next_rptr = ring->wptr + 3 + 4;
		radeon_ring_ग_लिखो(ring, PACKET3(PACKET3_SET_CONFIG_REG, 1));
		radeon_ring_ग_लिखो(ring, ((ring->rptr_save_reg - 
					  PACKET3_SET_CONFIG_REG_START) >> 2));
		radeon_ring_ग_लिखो(ring, next_rptr);
	पूर्ण अन्यथा अगर (rdev->wb.enabled) अणु
		next_rptr = ring->wptr + 5 + 4;
		radeon_ring_ग_लिखो(ring, PACKET3(PACKET3_MEM_WRITE, 3));
		radeon_ring_ग_लिखो(ring, ring->next_rptr_gpu_addr & 0xfffffffc);
		radeon_ring_ग_लिखो(ring, (upper_32_bits(ring->next_rptr_gpu_addr) & 0xff) | (1 << 18));
		radeon_ring_ग_लिखो(ring, next_rptr);
		radeon_ring_ग_लिखो(ring, 0);
	पूर्ण

	radeon_ring_ग_लिखो(ring, PACKET3(PACKET3_INसूचीECT_BUFFER, 2));
	radeon_ring_ग_लिखो(ring,
#अगर_घोषित __BIG_ENDIAN
			  (2 << 0) |
#पूर्ण_अगर
			  (ib->gpu_addr & 0xFFFFFFFC));
	radeon_ring_ग_लिखो(ring, upper_32_bits(ib->gpu_addr) & 0xFF);
	radeon_ring_ग_लिखो(ring, ib->length_dw);
पूर्ण


अटल पूर्णांक evergreen_cp_load_microcode(काष्ठा radeon_device *rdev)
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

	fw_data = (स्थिर __be32 *)rdev->pfp_fw->data;
	WREG32(CP_PFP_UCODE_ADDR, 0);
	क्रम (i = 0; i < EVERGREEN_PFP_UCODE_SIZE; i++)
		WREG32(CP_PFP_UCODE_DATA, be32_to_cpup(fw_data++));
	WREG32(CP_PFP_UCODE_ADDR, 0);

	fw_data = (स्थिर __be32 *)rdev->me_fw->data;
	WREG32(CP_ME_RAM_WADDR, 0);
	क्रम (i = 0; i < EVERGREEN_PM4_UCODE_SIZE; i++)
		WREG32(CP_ME_RAM_DATA, be32_to_cpup(fw_data++));

	WREG32(CP_PFP_UCODE_ADDR, 0);
	WREG32(CP_ME_RAM_WADDR, 0);
	WREG32(CP_ME_RAM_RADDR, 0);
	वापस 0;
पूर्ण

अटल पूर्णांक evergreen_cp_start(काष्ठा radeon_device *rdev)
अणु
	काष्ठा radeon_ring *ring = &rdev->ring[RADEON_RING_TYPE_GFX_INDEX];
	पूर्णांक r, i;
	uपूर्णांक32_t cp_me;

	r = radeon_ring_lock(rdev, ring, 7);
	अगर (r) अणु
		DRM_ERROR("radeon: cp failed to lock ring (%d).\n", r);
		वापस r;
	पूर्ण
	radeon_ring_ग_लिखो(ring, PACKET3(PACKET3_ME_INITIALIZE, 5));
	radeon_ring_ग_लिखो(ring, 0x1);
	radeon_ring_ग_लिखो(ring, 0x0);
	radeon_ring_ग_लिखो(ring, rdev->config.evergreen.max_hw_contexts - 1);
	radeon_ring_ग_लिखो(ring, PACKET3_ME_INITIALIZE_DEVICE_ID(1));
	radeon_ring_ग_लिखो(ring, 0);
	radeon_ring_ग_लिखो(ring, 0);
	radeon_ring_unlock_commit(rdev, ring, false);

	cp_me = 0xff;
	WREG32(CP_ME_CNTL, cp_me);

	r = radeon_ring_lock(rdev, ring, evergreen_शेष_size + 19);
	अगर (r) अणु
		DRM_ERROR("radeon: cp failed to lock ring (%d).\n", r);
		वापस r;
	पूर्ण

	/* setup clear context state */
	radeon_ring_ग_लिखो(ring, PACKET3(PACKET3_PREAMBLE_CNTL, 0));
	radeon_ring_ग_लिखो(ring, PACKET3_PREAMBLE_BEGIN_CLEAR_STATE);

	क्रम (i = 0; i < evergreen_शेष_size; i++)
		radeon_ring_ग_लिखो(ring, evergreen_शेष_state[i]);

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

	वापस 0;
पूर्ण

अटल पूर्णांक evergreen_cp_resume(काष्ठा radeon_device *rdev)
अणु
	काष्ठा radeon_ring *ring = &rdev->ring[RADEON_RING_TYPE_GFX_INDEX];
	u32 पंचांगp;
	u32 rb_bufsz;
	पूर्णांक r;

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

	/* Set ring buffer size */
	rb_bufsz = order_base_2(ring->ring_size / 8);
	पंचांगp = (order_base_2(RADEON_GPU_PAGE_SIZE/8) << 8) | rb_bufsz;
#अगर_घोषित __BIG_ENDIAN
	पंचांगp |= BUF_SWAP_32BIT;
#पूर्ण_अगर
	WREG32(CP_RB_CNTL, पंचांगp);
	WREG32(CP_SEM_WAIT_TIMER, 0x0);
	WREG32(CP_SEM_INCOMPLETE_TIMER_CNTL, 0x0);

	/* Set the ग_लिखो poपूर्णांकer delay */
	WREG32(CP_RB_WPTR_DELAY, 0);

	/* Initialize the ring buffer's पढ़ो and ग_लिखो poपूर्णांकers */
	WREG32(CP_RB_CNTL, पंचांगp | RB_RPTR_WR_ENA);
	WREG32(CP_RB_RPTR_WR, 0);
	ring->wptr = 0;
	WREG32(CP_RB_WPTR, ring->wptr);

	/* set the wb address whether it's enabled or not */
	WREG32(CP_RB_RPTR_ADDR,
	       ((rdev->wb.gpu_addr + RADEON_WB_CP_RPTR_OFFSET) & 0xFFFFFFFC));
	WREG32(CP_RB_RPTR_ADDR_HI, upper_32_bits(rdev->wb.gpu_addr + RADEON_WB_CP_RPTR_OFFSET) & 0xFF);
	WREG32(SCRATCH_ADDR, ((rdev->wb.gpu_addr + RADEON_WB_SCRATCH_OFFSET) >> 8) & 0xFFFFFFFF);

	अगर (rdev->wb.enabled)
		WREG32(SCRATCH_UMSK, 0xff);
	अन्यथा अणु
		पंचांगp |= RB_NO_UPDATE;
		WREG32(SCRATCH_UMSK, 0);
	पूर्ण

	mdelay(1);
	WREG32(CP_RB_CNTL, पंचांगp);

	WREG32(CP_RB_BASE, ring->gpu_addr >> 8);
	WREG32(CP_DEBUG, (1 << 27) | (1 << 28));

	evergreen_cp_start(rdev);
	ring->पढ़ोy = true;
	r = radeon_ring_test(rdev, RADEON_RING_TYPE_GFX_INDEX, ring);
	अगर (r) अणु
		ring->पढ़ोy = false;
		वापस r;
	पूर्ण
	वापस 0;
पूर्ण

/*
 * Core functions
 */
अटल व्योम evergreen_gpu_init(काष्ठा radeon_device *rdev)
अणु
	u32 gb_addr_config;
	u32 mc_arb_ramcfg;
	u32 sx_debug_1;
	u32 smx_dc_ctl0;
	u32 sq_config;
	u32 sq_lds_resource_mgmt;
	u32 sq_gpr_resource_mgmt_1;
	u32 sq_gpr_resource_mgmt_2;
	u32 sq_gpr_resource_mgmt_3;
	u32 sq_thपढ़ो_resource_mgmt;
	u32 sq_thपढ़ो_resource_mgmt_2;
	u32 sq_stack_resource_mgmt_1;
	u32 sq_stack_resource_mgmt_2;
	u32 sq_stack_resource_mgmt_3;
	u32 vgt_cache_invalidation;
	u32 hdp_host_path_cntl, पंचांगp;
	u32 disabled_rb_mask;
	पूर्णांक i, j, ps_thपढ़ो_count;

	चयन (rdev->family) अणु
	हाल CHIP_CYPRESS:
	हाल CHIP_HEMLOCK:
		rdev->config.evergreen.num_ses = 2;
		rdev->config.evergreen.max_pipes = 4;
		rdev->config.evergreen.max_tile_pipes = 8;
		rdev->config.evergreen.max_simds = 10;
		rdev->config.evergreen.max_backends = 4 * rdev->config.evergreen.num_ses;
		rdev->config.evergreen.max_gprs = 256;
		rdev->config.evergreen.max_thपढ़ोs = 248;
		rdev->config.evergreen.max_gs_thपढ़ोs = 32;
		rdev->config.evergreen.max_stack_entries = 512;
		rdev->config.evergreen.sx_num_of_sets = 4;
		rdev->config.evergreen.sx_max_export_size = 256;
		rdev->config.evergreen.sx_max_export_pos_size = 64;
		rdev->config.evergreen.sx_max_export_smx_size = 192;
		rdev->config.evergreen.max_hw_contexts = 8;
		rdev->config.evergreen.sq_num_cf_insts = 2;

		rdev->config.evergreen.sc_prim_fअगरo_size = 0x100;
		rdev->config.evergreen.sc_hiz_tile_fअगरo_size = 0x30;
		rdev->config.evergreen.sc_earlyz_tile_fअगरo_size = 0x130;
		gb_addr_config = CYPRESS_GB_ADDR_CONFIG_GOLDEN;
		अवरोध;
	हाल CHIP_JUNIPER:
		rdev->config.evergreen.num_ses = 1;
		rdev->config.evergreen.max_pipes = 4;
		rdev->config.evergreen.max_tile_pipes = 4;
		rdev->config.evergreen.max_simds = 10;
		rdev->config.evergreen.max_backends = 4 * rdev->config.evergreen.num_ses;
		rdev->config.evergreen.max_gprs = 256;
		rdev->config.evergreen.max_thपढ़ोs = 248;
		rdev->config.evergreen.max_gs_thपढ़ोs = 32;
		rdev->config.evergreen.max_stack_entries = 512;
		rdev->config.evergreen.sx_num_of_sets = 4;
		rdev->config.evergreen.sx_max_export_size = 256;
		rdev->config.evergreen.sx_max_export_pos_size = 64;
		rdev->config.evergreen.sx_max_export_smx_size = 192;
		rdev->config.evergreen.max_hw_contexts = 8;
		rdev->config.evergreen.sq_num_cf_insts = 2;

		rdev->config.evergreen.sc_prim_fअगरo_size = 0x100;
		rdev->config.evergreen.sc_hiz_tile_fअगरo_size = 0x30;
		rdev->config.evergreen.sc_earlyz_tile_fअगरo_size = 0x130;
		gb_addr_config = JUNIPER_GB_ADDR_CONFIG_GOLDEN;
		अवरोध;
	हाल CHIP_REDWOOD:
		rdev->config.evergreen.num_ses = 1;
		rdev->config.evergreen.max_pipes = 4;
		rdev->config.evergreen.max_tile_pipes = 4;
		rdev->config.evergreen.max_simds = 5;
		rdev->config.evergreen.max_backends = 2 * rdev->config.evergreen.num_ses;
		rdev->config.evergreen.max_gprs = 256;
		rdev->config.evergreen.max_thपढ़ोs = 248;
		rdev->config.evergreen.max_gs_thपढ़ोs = 32;
		rdev->config.evergreen.max_stack_entries = 256;
		rdev->config.evergreen.sx_num_of_sets = 4;
		rdev->config.evergreen.sx_max_export_size = 256;
		rdev->config.evergreen.sx_max_export_pos_size = 64;
		rdev->config.evergreen.sx_max_export_smx_size = 192;
		rdev->config.evergreen.max_hw_contexts = 8;
		rdev->config.evergreen.sq_num_cf_insts = 2;

		rdev->config.evergreen.sc_prim_fअगरo_size = 0x100;
		rdev->config.evergreen.sc_hiz_tile_fअगरo_size = 0x30;
		rdev->config.evergreen.sc_earlyz_tile_fअगरo_size = 0x130;
		gb_addr_config = REDWOOD_GB_ADDR_CONFIG_GOLDEN;
		अवरोध;
	हाल CHIP_CEDAR:
	शेष:
		rdev->config.evergreen.num_ses = 1;
		rdev->config.evergreen.max_pipes = 2;
		rdev->config.evergreen.max_tile_pipes = 2;
		rdev->config.evergreen.max_simds = 2;
		rdev->config.evergreen.max_backends = 1 * rdev->config.evergreen.num_ses;
		rdev->config.evergreen.max_gprs = 256;
		rdev->config.evergreen.max_thपढ़ोs = 192;
		rdev->config.evergreen.max_gs_thपढ़ोs = 16;
		rdev->config.evergreen.max_stack_entries = 256;
		rdev->config.evergreen.sx_num_of_sets = 4;
		rdev->config.evergreen.sx_max_export_size = 128;
		rdev->config.evergreen.sx_max_export_pos_size = 32;
		rdev->config.evergreen.sx_max_export_smx_size = 96;
		rdev->config.evergreen.max_hw_contexts = 4;
		rdev->config.evergreen.sq_num_cf_insts = 1;

		rdev->config.evergreen.sc_prim_fअगरo_size = 0x40;
		rdev->config.evergreen.sc_hiz_tile_fअगरo_size = 0x30;
		rdev->config.evergreen.sc_earlyz_tile_fअगरo_size = 0x130;
		gb_addr_config = CEDAR_GB_ADDR_CONFIG_GOLDEN;
		अवरोध;
	हाल CHIP_PALM:
		rdev->config.evergreen.num_ses = 1;
		rdev->config.evergreen.max_pipes = 2;
		rdev->config.evergreen.max_tile_pipes = 2;
		rdev->config.evergreen.max_simds = 2;
		rdev->config.evergreen.max_backends = 1 * rdev->config.evergreen.num_ses;
		rdev->config.evergreen.max_gprs = 256;
		rdev->config.evergreen.max_thपढ़ोs = 192;
		rdev->config.evergreen.max_gs_thपढ़ोs = 16;
		rdev->config.evergreen.max_stack_entries = 256;
		rdev->config.evergreen.sx_num_of_sets = 4;
		rdev->config.evergreen.sx_max_export_size = 128;
		rdev->config.evergreen.sx_max_export_pos_size = 32;
		rdev->config.evergreen.sx_max_export_smx_size = 96;
		rdev->config.evergreen.max_hw_contexts = 4;
		rdev->config.evergreen.sq_num_cf_insts = 1;

		rdev->config.evergreen.sc_prim_fअगरo_size = 0x40;
		rdev->config.evergreen.sc_hiz_tile_fअगरo_size = 0x30;
		rdev->config.evergreen.sc_earlyz_tile_fअगरo_size = 0x130;
		gb_addr_config = CEDAR_GB_ADDR_CONFIG_GOLDEN;
		अवरोध;
	हाल CHIP_SUMO:
		rdev->config.evergreen.num_ses = 1;
		rdev->config.evergreen.max_pipes = 4;
		rdev->config.evergreen.max_tile_pipes = 4;
		अगर (rdev->pdev->device == 0x9648)
			rdev->config.evergreen.max_simds = 3;
		अन्यथा अगर ((rdev->pdev->device == 0x9647) ||
			 (rdev->pdev->device == 0x964a))
			rdev->config.evergreen.max_simds = 4;
		अन्यथा
			rdev->config.evergreen.max_simds = 5;
		rdev->config.evergreen.max_backends = 2 * rdev->config.evergreen.num_ses;
		rdev->config.evergreen.max_gprs = 256;
		rdev->config.evergreen.max_thपढ़ोs = 248;
		rdev->config.evergreen.max_gs_thपढ़ोs = 32;
		rdev->config.evergreen.max_stack_entries = 256;
		rdev->config.evergreen.sx_num_of_sets = 4;
		rdev->config.evergreen.sx_max_export_size = 256;
		rdev->config.evergreen.sx_max_export_pos_size = 64;
		rdev->config.evergreen.sx_max_export_smx_size = 192;
		rdev->config.evergreen.max_hw_contexts = 8;
		rdev->config.evergreen.sq_num_cf_insts = 2;

		rdev->config.evergreen.sc_prim_fअगरo_size = 0x40;
		rdev->config.evergreen.sc_hiz_tile_fअगरo_size = 0x30;
		rdev->config.evergreen.sc_earlyz_tile_fअगरo_size = 0x130;
		gb_addr_config = SUMO_GB_ADDR_CONFIG_GOLDEN;
		अवरोध;
	हाल CHIP_SUMO2:
		rdev->config.evergreen.num_ses = 1;
		rdev->config.evergreen.max_pipes = 4;
		rdev->config.evergreen.max_tile_pipes = 4;
		rdev->config.evergreen.max_simds = 2;
		rdev->config.evergreen.max_backends = 1 * rdev->config.evergreen.num_ses;
		rdev->config.evergreen.max_gprs = 256;
		rdev->config.evergreen.max_thपढ़ोs = 248;
		rdev->config.evergreen.max_gs_thपढ़ोs = 32;
		rdev->config.evergreen.max_stack_entries = 512;
		rdev->config.evergreen.sx_num_of_sets = 4;
		rdev->config.evergreen.sx_max_export_size = 256;
		rdev->config.evergreen.sx_max_export_pos_size = 64;
		rdev->config.evergreen.sx_max_export_smx_size = 192;
		rdev->config.evergreen.max_hw_contexts = 4;
		rdev->config.evergreen.sq_num_cf_insts = 2;

		rdev->config.evergreen.sc_prim_fअगरo_size = 0x40;
		rdev->config.evergreen.sc_hiz_tile_fअगरo_size = 0x30;
		rdev->config.evergreen.sc_earlyz_tile_fअगरo_size = 0x130;
		gb_addr_config = SUMO2_GB_ADDR_CONFIG_GOLDEN;
		अवरोध;
	हाल CHIP_BARTS:
		rdev->config.evergreen.num_ses = 2;
		rdev->config.evergreen.max_pipes = 4;
		rdev->config.evergreen.max_tile_pipes = 8;
		rdev->config.evergreen.max_simds = 7;
		rdev->config.evergreen.max_backends = 4 * rdev->config.evergreen.num_ses;
		rdev->config.evergreen.max_gprs = 256;
		rdev->config.evergreen.max_thपढ़ोs = 248;
		rdev->config.evergreen.max_gs_thपढ़ोs = 32;
		rdev->config.evergreen.max_stack_entries = 512;
		rdev->config.evergreen.sx_num_of_sets = 4;
		rdev->config.evergreen.sx_max_export_size = 256;
		rdev->config.evergreen.sx_max_export_pos_size = 64;
		rdev->config.evergreen.sx_max_export_smx_size = 192;
		rdev->config.evergreen.max_hw_contexts = 8;
		rdev->config.evergreen.sq_num_cf_insts = 2;

		rdev->config.evergreen.sc_prim_fअगरo_size = 0x100;
		rdev->config.evergreen.sc_hiz_tile_fअगरo_size = 0x30;
		rdev->config.evergreen.sc_earlyz_tile_fअगरo_size = 0x130;
		gb_addr_config = BARTS_GB_ADDR_CONFIG_GOLDEN;
		अवरोध;
	हाल CHIP_TURKS:
		rdev->config.evergreen.num_ses = 1;
		rdev->config.evergreen.max_pipes = 4;
		rdev->config.evergreen.max_tile_pipes = 4;
		rdev->config.evergreen.max_simds = 6;
		rdev->config.evergreen.max_backends = 2 * rdev->config.evergreen.num_ses;
		rdev->config.evergreen.max_gprs = 256;
		rdev->config.evergreen.max_thपढ़ोs = 248;
		rdev->config.evergreen.max_gs_thपढ़ोs = 32;
		rdev->config.evergreen.max_stack_entries = 256;
		rdev->config.evergreen.sx_num_of_sets = 4;
		rdev->config.evergreen.sx_max_export_size = 256;
		rdev->config.evergreen.sx_max_export_pos_size = 64;
		rdev->config.evergreen.sx_max_export_smx_size = 192;
		rdev->config.evergreen.max_hw_contexts = 8;
		rdev->config.evergreen.sq_num_cf_insts = 2;

		rdev->config.evergreen.sc_prim_fअगरo_size = 0x100;
		rdev->config.evergreen.sc_hiz_tile_fअगरo_size = 0x30;
		rdev->config.evergreen.sc_earlyz_tile_fअगरo_size = 0x130;
		gb_addr_config = TURKS_GB_ADDR_CONFIG_GOLDEN;
		अवरोध;
	हाल CHIP_CAICOS:
		rdev->config.evergreen.num_ses = 1;
		rdev->config.evergreen.max_pipes = 2;
		rdev->config.evergreen.max_tile_pipes = 2;
		rdev->config.evergreen.max_simds = 2;
		rdev->config.evergreen.max_backends = 1 * rdev->config.evergreen.num_ses;
		rdev->config.evergreen.max_gprs = 256;
		rdev->config.evergreen.max_thपढ़ोs = 192;
		rdev->config.evergreen.max_gs_thपढ़ोs = 16;
		rdev->config.evergreen.max_stack_entries = 256;
		rdev->config.evergreen.sx_num_of_sets = 4;
		rdev->config.evergreen.sx_max_export_size = 128;
		rdev->config.evergreen.sx_max_export_pos_size = 32;
		rdev->config.evergreen.sx_max_export_smx_size = 96;
		rdev->config.evergreen.max_hw_contexts = 4;
		rdev->config.evergreen.sq_num_cf_insts = 1;

		rdev->config.evergreen.sc_prim_fअगरo_size = 0x40;
		rdev->config.evergreen.sc_hiz_tile_fअगरo_size = 0x30;
		rdev->config.evergreen.sc_earlyz_tile_fअगरo_size = 0x130;
		gb_addr_config = CAICOS_GB_ADDR_CONFIG_GOLDEN;
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
	अगर ((rdev->family == CHIP_PALM) ||
	    (rdev->family == CHIP_SUMO) ||
	    (rdev->family == CHIP_SUMO2))
		mc_arb_ramcfg = RREG32(FUS_MC_ARB_RAMCFG);
	अन्यथा
		mc_arb_ramcfg = RREG32(MC_ARB_RAMCFG);

	/* setup tiling info dword.  gb_addr_config is not adequate since it करोes
	 * not have bank info, so create a custom tiling dword.
	 * bits 3:0   num_pipes
	 * bits 7:4   num_banks
	 * bits 11:8  group_size
	 * bits 15:12 row_size
	 */
	rdev->config.evergreen.tile_config = 0;
	चयन (rdev->config.evergreen.max_tile_pipes) अणु
	हाल 1:
	शेष:
		rdev->config.evergreen.tile_config |= (0 << 0);
		अवरोध;
	हाल 2:
		rdev->config.evergreen.tile_config |= (1 << 0);
		अवरोध;
	हाल 4:
		rdev->config.evergreen.tile_config |= (2 << 0);
		अवरोध;
	हाल 8:
		rdev->config.evergreen.tile_config |= (3 << 0);
		अवरोध;
	पूर्ण
	/* num banks is 8 on all fusion asics. 0 = 4, 1 = 8, 2 = 16 */
	अगर (rdev->flags & RADEON_IS_IGP)
		rdev->config.evergreen.tile_config |= 1 << 4;
	अन्यथा अणु
		चयन ((mc_arb_ramcfg & NOOFBANK_MASK) >> NOOFBANK_SHIFT) अणु
		हाल 0: /* four banks */
			rdev->config.evergreen.tile_config |= 0 << 4;
			अवरोध;
		हाल 1: /* eight banks */
			rdev->config.evergreen.tile_config |= 1 << 4;
			अवरोध;
		हाल 2: /* sixteen banks */
		शेष:
			rdev->config.evergreen.tile_config |= 2 << 4;
			अवरोध;
		पूर्ण
	पूर्ण
	rdev->config.evergreen.tile_config |= 0 << 8;
	rdev->config.evergreen.tile_config |=
		((gb_addr_config & 0x30000000) >> 28) << 12;

	अगर ((rdev->family >= CHIP_CEDAR) && (rdev->family <= CHIP_HEMLOCK)) अणु
		u32 efuse_straps_4;
		u32 efuse_straps_3;

		efuse_straps_4 = RREG32_RCU(0x204);
		efuse_straps_3 = RREG32_RCU(0x203);
		पंचांगp = (((efuse_straps_4 & 0xf) << 4) |
		      ((efuse_straps_3 & 0xf0000000) >> 28));
	पूर्ण अन्यथा अणु
		पंचांगp = 0;
		क्रम (i = (rdev->config.evergreen.num_ses - 1); i >= 0; i--) अणु
			u32 rb_disable_biपंचांगap;

			WREG32(GRBM_GFX_INDEX, INSTANCE_BROADCAST_WRITES | SE_INDEX(i));
			WREG32(RLC_GFX_INDEX, INSTANCE_BROADCAST_WRITES | SE_INDEX(i));
			rb_disable_biपंचांगap = (RREG32(CC_RB_BACKEND_DISABLE) & 0x00ff0000) >> 16;
			पंचांगp <<= 4;
			पंचांगp |= rb_disable_biपंचांगap;
		पूर्ण
	पूर्ण
	/* enabled rb are just the one not disabled :) */
	disabled_rb_mask = पंचांगp;
	पंचांगp = 0;
	क्रम (i = 0; i < rdev->config.evergreen.max_backends; i++)
		पंचांगp |= (1 << i);
	/* अगर all the backends are disabled, fix it up here */
	अगर ((disabled_rb_mask & पंचांगp) == पंचांगp) अणु
		क्रम (i = 0; i < rdev->config.evergreen.max_backends; i++)
			disabled_rb_mask &= ~(1 << i);
	पूर्ण

	क्रम (i = 0; i < rdev->config.evergreen.num_ses; i++) अणु
		u32 simd_disable_biपंचांगap;

		WREG32(GRBM_GFX_INDEX, INSTANCE_BROADCAST_WRITES | SE_INDEX(i));
		WREG32(RLC_GFX_INDEX, INSTANCE_BROADCAST_WRITES | SE_INDEX(i));
		simd_disable_biपंचांगap = (RREG32(CC_GC_SHADER_PIPE_CONFIG) & 0xffff0000) >> 16;
		simd_disable_biपंचांगap |= 0xffffffff << rdev->config.evergreen.max_simds;
		पंचांगp <<= 16;
		पंचांगp |= simd_disable_biपंचांगap;
	पूर्ण
	rdev->config.evergreen.active_simds = hweight32(~पंचांगp);

	WREG32(GRBM_GFX_INDEX, INSTANCE_BROADCAST_WRITES | SE_BROADCAST_WRITES);
	WREG32(RLC_GFX_INDEX, INSTANCE_BROADCAST_WRITES | SE_BROADCAST_WRITES);

	WREG32(GB_ADDR_CONFIG, gb_addr_config);
	WREG32(DMIF_ADDR_CONFIG, gb_addr_config);
	WREG32(HDP_ADDR_CONFIG, gb_addr_config);
	WREG32(DMA_TILING_CONFIG, gb_addr_config);
	WREG32(UVD_UDEC_ADDR_CONFIG, gb_addr_config);
	WREG32(UVD_UDEC_DB_ADDR_CONFIG, gb_addr_config);
	WREG32(UVD_UDEC_DBW_ADDR_CONFIG, gb_addr_config);

	अगर ((rdev->config.evergreen.max_backends == 1) &&
	    (rdev->flags & RADEON_IS_IGP)) अणु
		अगर ((disabled_rb_mask & 3) == 1) अणु
			/* RB0 disabled, RB1 enabled */
			पंचांगp = 0x11111111;
		पूर्ण अन्यथा अणु
			/* RB1 disabled, RB0 enabled */
			पंचांगp = 0x00000000;
		पूर्ण
	पूर्ण अन्यथा अणु
		पंचांगp = gb_addr_config & NUM_PIPES_MASK;
		पंचांगp = r6xx_remap_render_backend(rdev, पंचांगp, rdev->config.evergreen.max_backends,
						EVERGREEN_MAX_BACKENDS, disabled_rb_mask);
	पूर्ण
	rdev->config.evergreen.backend_map = पंचांगp;
	WREG32(GB_BACKEND_MAP, पंचांगp);

	WREG32(CGTS_SYS_TCC_DISABLE, 0);
	WREG32(CGTS_TCC_DISABLE, 0);
	WREG32(CGTS_USER_SYS_TCC_DISABLE, 0);
	WREG32(CGTS_USER_TCC_DISABLE, 0);

	/* set HW शेषs क्रम 3D engine */
	WREG32(CP_QUEUE_THRESHOLDS, (ROQ_IB1_START(0x16) |
				     ROQ_IB2_START(0x2b)));

	WREG32(CP_MEQ_THRESHOLDS, STQ_SPLIT(0x30));

	WREG32(TA_CNTL_AUX, (DISABLE_CUBE_ANISO |
			     SYNC_GRADIENT |
			     SYNC_WALKER |
			     SYNC_ALIGNER));

	sx_debug_1 = RREG32(SX_DEBUG_1);
	sx_debug_1 |= ENABLE_NEW_SMX_ADDRESS;
	WREG32(SX_DEBUG_1, sx_debug_1);


	smx_dc_ctl0 = RREG32(SMX_DC_CTL0);
	smx_dc_ctl0 &= ~NUMBER_OF_SETS(0x1ff);
	smx_dc_ctl0 |= NUMBER_OF_SETS(rdev->config.evergreen.sx_num_of_sets);
	WREG32(SMX_DC_CTL0, smx_dc_ctl0);

	अगर (rdev->family <= CHIP_SUMO2)
		WREG32(SMX_SAR_CTL0, 0x00010000);

	WREG32(SX_EXPORT_BUFFER_SIZES, (COLOR_BUFFER_SIZE((rdev->config.evergreen.sx_max_export_size / 4) - 1) |
					POSITION_BUFFER_SIZE((rdev->config.evergreen.sx_max_export_pos_size / 4) - 1) |
					SMX_BUFFER_SIZE((rdev->config.evergreen.sx_max_export_smx_size / 4) - 1)));

	WREG32(PA_SC_FIFO_SIZE, (SC_PRIM_FIFO_SIZE(rdev->config.evergreen.sc_prim_fअगरo_size) |
				 SC_HIZ_TILE_FIFO_SIZE(rdev->config.evergreen.sc_hiz_tile_fअगरo_size) |
				 SC_EARLYZ_TILE_FIFO_SIZE(rdev->config.evergreen.sc_earlyz_tile_fअगरo_size)));

	WREG32(VGT_NUM_INSTANCES, 1);
	WREG32(SPI_CONFIG_CNTL, 0);
	WREG32(SPI_CONFIG_CNTL_1, VTX_DONE_DELAY(4));
	WREG32(CP_PERFMON_CNTL, 0);

	WREG32(SQ_MS_FIFO_SIZES, (CACHE_FIFO_SIZE(16 * rdev->config.evergreen.sq_num_cf_insts) |
				  FETCH_FIFO_HIWATER(0x4) |
				  DONE_FIFO_HIWATER(0xe0) |
				  ALU_UPDATE_FIFO_HIWATER(0x8)));

	sq_config = RREG32(SQ_CONFIG);
	sq_config &= ~(PS_PRIO(3) |
		       VS_PRIO(3) |
		       GS_PRIO(3) |
		       ES_PRIO(3));
	sq_config |= (VC_ENABLE |
		      EXPORT_SRC_C |
		      PS_PRIO(0) |
		      VS_PRIO(1) |
		      GS_PRIO(2) |
		      ES_PRIO(3));

	चयन (rdev->family) अणु
	हाल CHIP_CEDAR:
	हाल CHIP_PALM:
	हाल CHIP_SUMO:
	हाल CHIP_SUMO2:
	हाल CHIP_CAICOS:
		/* no vertex cache */
		sq_config &= ~VC_ENABLE;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	sq_lds_resource_mgmt = RREG32(SQ_LDS_RESOURCE_MGMT);

	sq_gpr_resource_mgmt_1 = NUM_PS_GPRS((rdev->config.evergreen.max_gprs - (4 * 2))* 12 / 32);
	sq_gpr_resource_mgmt_1 |= NUM_VS_GPRS((rdev->config.evergreen.max_gprs - (4 * 2)) * 6 / 32);
	sq_gpr_resource_mgmt_1 |= NUM_CLAUSE_TEMP_GPRS(4);
	sq_gpr_resource_mgmt_2 = NUM_GS_GPRS((rdev->config.evergreen.max_gprs - (4 * 2)) * 4 / 32);
	sq_gpr_resource_mgmt_2 |= NUM_ES_GPRS((rdev->config.evergreen.max_gprs - (4 * 2)) * 4 / 32);
	sq_gpr_resource_mgmt_3 = NUM_HS_GPRS((rdev->config.evergreen.max_gprs - (4 * 2)) * 3 / 32);
	sq_gpr_resource_mgmt_3 |= NUM_LS_GPRS((rdev->config.evergreen.max_gprs - (4 * 2)) * 3 / 32);

	चयन (rdev->family) अणु
	हाल CHIP_CEDAR:
	हाल CHIP_PALM:
	हाल CHIP_SUMO:
	हाल CHIP_SUMO2:
		ps_thपढ़ो_count = 96;
		अवरोध;
	शेष:
		ps_thपढ़ो_count = 128;
		अवरोध;
	पूर्ण

	sq_thपढ़ो_resource_mgmt = NUM_PS_THREADS(ps_thपढ़ो_count);
	sq_thपढ़ो_resource_mgmt |= NUM_VS_THREADS((((rdev->config.evergreen.max_thपढ़ोs - ps_thपढ़ो_count) / 6) / 8) * 8);
	sq_thपढ़ो_resource_mgmt |= NUM_GS_THREADS((((rdev->config.evergreen.max_thपढ़ोs - ps_thपढ़ो_count) / 6) / 8) * 8);
	sq_thपढ़ो_resource_mgmt |= NUM_ES_THREADS((((rdev->config.evergreen.max_thपढ़ोs - ps_thपढ़ो_count) / 6) / 8) * 8);
	sq_thपढ़ो_resource_mgmt_2 = NUM_HS_THREADS((((rdev->config.evergreen.max_thपढ़ोs - ps_thपढ़ो_count) / 6) / 8) * 8);
	sq_thपढ़ो_resource_mgmt_2 |= NUM_LS_THREADS((((rdev->config.evergreen.max_thपढ़ोs - ps_thपढ़ो_count) / 6) / 8) * 8);

	sq_stack_resource_mgmt_1 = NUM_PS_STACK_ENTRIES((rdev->config.evergreen.max_stack_entries * 1) / 6);
	sq_stack_resource_mgmt_1 |= NUM_VS_STACK_ENTRIES((rdev->config.evergreen.max_stack_entries * 1) / 6);
	sq_stack_resource_mgmt_2 = NUM_GS_STACK_ENTRIES((rdev->config.evergreen.max_stack_entries * 1) / 6);
	sq_stack_resource_mgmt_2 |= NUM_ES_STACK_ENTRIES((rdev->config.evergreen.max_stack_entries * 1) / 6);
	sq_stack_resource_mgmt_3 = NUM_HS_STACK_ENTRIES((rdev->config.evergreen.max_stack_entries * 1) / 6);
	sq_stack_resource_mgmt_3 |= NUM_LS_STACK_ENTRIES((rdev->config.evergreen.max_stack_entries * 1) / 6);

	WREG32(SQ_CONFIG, sq_config);
	WREG32(SQ_GPR_RESOURCE_MGMT_1, sq_gpr_resource_mgmt_1);
	WREG32(SQ_GPR_RESOURCE_MGMT_2, sq_gpr_resource_mgmt_2);
	WREG32(SQ_GPR_RESOURCE_MGMT_3, sq_gpr_resource_mgmt_3);
	WREG32(SQ_THREAD_RESOURCE_MGMT, sq_thपढ़ो_resource_mgmt);
	WREG32(SQ_THREAD_RESOURCE_MGMT_2, sq_thपढ़ो_resource_mgmt_2);
	WREG32(SQ_STACK_RESOURCE_MGMT_1, sq_stack_resource_mgmt_1);
	WREG32(SQ_STACK_RESOURCE_MGMT_2, sq_stack_resource_mgmt_2);
	WREG32(SQ_STACK_RESOURCE_MGMT_3, sq_stack_resource_mgmt_3);
	WREG32(SQ_DYN_GPR_CNTL_PS_FLUSH_REQ, 0);
	WREG32(SQ_LDS_RESOURCE_MGMT, sq_lds_resource_mgmt);

	WREG32(PA_SC_FORCE_EOV_MAX_CNTS, (FORCE_EOV_MAX_CLK_CNT(4095) |
					  FORCE_EOV_MAX_REZ_CNT(255)));

	चयन (rdev->family) अणु
	हाल CHIP_CEDAR:
	हाल CHIP_PALM:
	हाल CHIP_SUMO:
	हाल CHIP_SUMO2:
	हाल CHIP_CAICOS:
		vgt_cache_invalidation = CACHE_INVALIDATION(TC_ONLY);
		अवरोध;
	शेष:
		vgt_cache_invalidation = CACHE_INVALIDATION(VC_AND_TC);
		अवरोध;
	पूर्ण
	vgt_cache_invalidation |= AUTO_INVLD_EN(ES_AND_GS_AUTO);
	WREG32(VGT_CACHE_INVALIDATION, vgt_cache_invalidation);

	WREG32(VGT_GS_VERTEX_REUSE, 16);
	WREG32(PA_SU_LINE_STIPPLE_VALUE, 0);
	WREG32(PA_SC_LINE_STIPPLE_STATE, 0);

	WREG32(VGT_VERTEX_REUSE_BLOCK_CNTL, 14);
	WREG32(VGT_OUT_DEALLOC_CNTL, 16);

	WREG32(CB_PERF_CTR0_SEL_0, 0);
	WREG32(CB_PERF_CTR0_SEL_1, 0);
	WREG32(CB_PERF_CTR1_SEL_0, 0);
	WREG32(CB_PERF_CTR1_SEL_1, 0);
	WREG32(CB_PERF_CTR2_SEL_0, 0);
	WREG32(CB_PERF_CTR2_SEL_1, 0);
	WREG32(CB_PERF_CTR3_SEL_0, 0);
	WREG32(CB_PERF_CTR3_SEL_1, 0);

	/* clear render buffer base addresses */
	WREG32(CB_COLOR0_BASE, 0);
	WREG32(CB_COLOR1_BASE, 0);
	WREG32(CB_COLOR2_BASE, 0);
	WREG32(CB_COLOR3_BASE, 0);
	WREG32(CB_COLOR4_BASE, 0);
	WREG32(CB_COLOR5_BASE, 0);
	WREG32(CB_COLOR6_BASE, 0);
	WREG32(CB_COLOR7_BASE, 0);
	WREG32(CB_COLOR8_BASE, 0);
	WREG32(CB_COLOR9_BASE, 0);
	WREG32(CB_COLOR10_BASE, 0);
	WREG32(CB_COLOR11_BASE, 0);

	/* set the shader स्थिर cache sizes to 0 */
	क्रम (i = SQ_ALU_CONST_BUFFER_SIZE_PS_0; i < 0x28200; i += 4)
		WREG32(i, 0);
	क्रम (i = SQ_ALU_CONST_BUFFER_SIZE_HS_0; i < 0x29000; i += 4)
		WREG32(i, 0);

	पंचांगp = RREG32(HDP_MISC_CNTL);
	पंचांगp |= HDP_FLUSH_INVALIDATE_CACHE;
	WREG32(HDP_MISC_CNTL, पंचांगp);

	hdp_host_path_cntl = RREG32(HDP_HOST_PATH_CNTL);
	WREG32(HDP_HOST_PATH_CNTL, hdp_host_path_cntl);

	WREG32(PA_CL_ENHANCE, CLIP_VTX_REORDER_ENA | NUM_CLIP_SEQ(3));

	udelay(50);

पूर्ण

पूर्णांक evergreen_mc_init(काष्ठा radeon_device *rdev)
अणु
	u32 पंचांगp;
	पूर्णांक chansize, numchan;

	/* Get VRAM inक्रमmations */
	rdev->mc.vram_is_ddr = true;
	अगर ((rdev->family == CHIP_PALM) ||
	    (rdev->family == CHIP_SUMO) ||
	    (rdev->family == CHIP_SUMO2))
		पंचांगp = RREG32(FUS_MC_ARB_RAMCFG);
	अन्यथा
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
	अगर ((rdev->family == CHIP_PALM) ||
	    (rdev->family == CHIP_SUMO) ||
	    (rdev->family == CHIP_SUMO2)) अणु
		/* size in bytes on fusion */
		rdev->mc.mc_vram_size = RREG32(CONFIG_MEMSIZE);
		rdev->mc.real_vram_size = RREG32(CONFIG_MEMSIZE);
	पूर्ण अन्यथा अणु
		/* size in MB on evergreen/cayman/tn */
		rdev->mc.mc_vram_size = RREG32(CONFIG_MEMSIZE) * 1024ULL * 1024ULL;
		rdev->mc.real_vram_size = RREG32(CONFIG_MEMSIZE) * 1024ULL * 1024ULL;
	पूर्ण
	rdev->mc.visible_vram_size = rdev->mc.aper_size;
	r700_vram_gtt_location(rdev, &rdev->mc);
	radeon_update_bandwidth_info(rdev);

	वापस 0;
पूर्ण

व्योम evergreen_prपूर्णांक_gpu_status_regs(काष्ठा radeon_device *rdev)
अणु
	dev_info(rdev->dev, "  GRBM_STATUS               = 0x%08X\n",
		RREG32(GRBM_STATUS));
	dev_info(rdev->dev, "  GRBM_STATUS_SE0           = 0x%08X\n",
		RREG32(GRBM_STATUS_SE0));
	dev_info(rdev->dev, "  GRBM_STATUS_SE1           = 0x%08X\n",
		RREG32(GRBM_STATUS_SE1));
	dev_info(rdev->dev, "  SRBM_STATUS               = 0x%08X\n",
		RREG32(SRBM_STATUS));
	dev_info(rdev->dev, "  SRBM_STATUS2              = 0x%08X\n",
		RREG32(SRBM_STATUS2));
	dev_info(rdev->dev, "  R_008674_CP_STALLED_STAT1 = 0x%08X\n",
		RREG32(CP_STALLED_STAT1));
	dev_info(rdev->dev, "  R_008678_CP_STALLED_STAT2 = 0x%08X\n",
		RREG32(CP_STALLED_STAT2));
	dev_info(rdev->dev, "  R_00867C_CP_BUSY_STAT     = 0x%08X\n",
		RREG32(CP_BUSY_STAT));
	dev_info(rdev->dev, "  R_008680_CP_STAT          = 0x%08X\n",
		RREG32(CP_STAT));
	dev_info(rdev->dev, "  R_00D034_DMA_STATUS_REG   = 0x%08X\n",
		RREG32(DMA_STATUS_REG));
	अगर (rdev->family >= CHIP_CAYMAN) अणु
		dev_info(rdev->dev, "  R_00D834_DMA_STATUS_REG   = 0x%08X\n",
			 RREG32(DMA_STATUS_REG + 0x800));
	पूर्ण
पूर्ण

bool evergreen_is_display_hung(काष्ठा radeon_device *rdev)
अणु
	u32 crtc_hung = 0;
	u32 crtc_status[6];
	u32 i, j, पंचांगp;

	क्रम (i = 0; i < rdev->num_crtc; i++) अणु
		अगर (RREG32(EVERGREEN_CRTC_CONTROL + crtc_offsets[i]) & EVERGREEN_CRTC_MASTER_EN) अणु
			crtc_status[i] = RREG32(EVERGREEN_CRTC_STATUS_HV_COUNT + crtc_offsets[i]);
			crtc_hung |= (1 << i);
		पूर्ण
	पूर्ण

	क्रम (j = 0; j < 10; j++) अणु
		क्रम (i = 0; i < rdev->num_crtc; i++) अणु
			अगर (crtc_hung & (1 << i)) अणु
				पंचांगp = RREG32(EVERGREEN_CRTC_STATUS_HV_COUNT + crtc_offsets[i]);
				अगर (पंचांगp != crtc_status[i])
					crtc_hung &= ~(1 << i);
			पूर्ण
		पूर्ण
		अगर (crtc_hung == 0)
			वापस false;
		udelay(100);
	पूर्ण

	वापस true;
पूर्ण

u32 evergreen_gpu_check_soft_reset(काष्ठा radeon_device *rdev)
अणु
	u32 reset_mask = 0;
	u32 पंचांगp;

	/* GRBM_STATUS */
	पंचांगp = RREG32(GRBM_STATUS);
	अगर (पंचांगp & (PA_BUSY | SC_BUSY |
		   SH_BUSY | SX_BUSY |
		   TA_BUSY | VGT_BUSY |
		   DB_BUSY | CB_BUSY |
		   SPI_BUSY | VGT_BUSY_NO_DMA))
		reset_mask |= RADEON_RESET_GFX;

	अगर (पंचांगp & (CF_RQ_PENDING | PF_RQ_PENDING |
		   CP_BUSY | CP_COHERENCY_BUSY))
		reset_mask |= RADEON_RESET_CP;

	अगर (पंचांगp & GRBM_EE_BUSY)
		reset_mask |= RADEON_RESET_GRBM | RADEON_RESET_GFX | RADEON_RESET_CP;

	/* DMA_STATUS_REG */
	पंचांगp = RREG32(DMA_STATUS_REG);
	अगर (!(पंचांगp & DMA_IDLE))
		reset_mask |= RADEON_RESET_DMA;

	/* SRBM_STATUS2 */
	पंचांगp = RREG32(SRBM_STATUS2);
	अगर (पंचांगp & DMA_BUSY)
		reset_mask |= RADEON_RESET_DMA;

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

अटल व्योम evergreen_gpu_soft_reset(काष्ठा radeon_device *rdev, u32 reset_mask)
अणु
	काष्ठा evergreen_mc_save save;
	u32 grbm_soft_reset = 0, srbm_soft_reset = 0;
	u32 पंचांगp;

	अगर (reset_mask == 0)
		वापस;

	dev_info(rdev->dev, "GPU softreset: 0x%08X\n", reset_mask);

	evergreen_prपूर्णांक_gpu_status_regs(rdev);

	/* Disable CP parsing/prefetching */
	WREG32(CP_ME_CNTL, CP_ME_HALT | CP_PFP_HALT);

	अगर (reset_mask & RADEON_RESET_DMA) अणु
		/* Disable DMA */
		पंचांगp = RREG32(DMA_RB_CNTL);
		पंचांगp &= ~DMA_RB_ENABLE;
		WREG32(DMA_RB_CNTL, पंचांगp);
	पूर्ण

	udelay(50);

	evergreen_mc_stop(rdev, &save);
	अगर (evergreen_mc_रुको_क्रम_idle(rdev)) अणु
		dev_warn(rdev->dev, "Wait for MC idle timedout !\n");
	पूर्ण

	अगर (reset_mask & (RADEON_RESET_GFX | RADEON_RESET_COMPUTE)) अणु
		grbm_soft_reset |= SOFT_RESET_DB |
			SOFT_RESET_CB |
			SOFT_RESET_PA |
			SOFT_RESET_SC |
			SOFT_RESET_SPI |
			SOFT_RESET_SX |
			SOFT_RESET_SH |
			SOFT_RESET_TC |
			SOFT_RESET_TA |
			SOFT_RESET_VC |
			SOFT_RESET_VGT;
	पूर्ण

	अगर (reset_mask & RADEON_RESET_CP) अणु
		grbm_soft_reset |= SOFT_RESET_CP |
			SOFT_RESET_VGT;

		srbm_soft_reset |= SOFT_RESET_GRBM;
	पूर्ण

	अगर (reset_mask & RADEON_RESET_DMA)
		srbm_soft_reset |= SOFT_RESET_DMA;

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

व्योम evergreen_gpu_pci_config_reset(काष्ठा radeon_device *rdev)
अणु
	काष्ठा evergreen_mc_save save;
	u32 पंचांगp, i;

	dev_info(rdev->dev, "GPU pci config reset\n");

	/* disable dpm? */

	/* Disable CP parsing/prefetching */
	WREG32(CP_ME_CNTL, CP_ME_HALT | CP_PFP_HALT);
	udelay(50);
	/* Disable DMA */
	पंचांगp = RREG32(DMA_RB_CNTL);
	पंचांगp &= ~DMA_RB_ENABLE;
	WREG32(DMA_RB_CNTL, पंचांगp);
	/* XXX other engines? */

	/* halt the rlc */
	r600_rlc_stop(rdev);

	udelay(50);

	/* set mclk/sclk to bypass */
	rv770_set_clk_bypass_mode(rdev);
	/* disable BM */
	pci_clear_master(rdev->pdev);
	/* disable mem access */
	evergreen_mc_stop(rdev, &save);
	अगर (evergreen_mc_रुको_क्रम_idle(rdev)) अणु
		dev_warn(rdev->dev, "Wait for MC idle timed out !\n");
	पूर्ण
	/* reset */
	radeon_pci_config_reset(rdev);
	/* रुको क्रम asic to come out of reset */
	क्रम (i = 0; i < rdev->usec_समयout; i++) अणु
		अगर (RREG32(CONFIG_MEMSIZE) != 0xffffffff)
			अवरोध;
		udelay(1);
	पूर्ण
पूर्ण

पूर्णांक evergreen_asic_reset(काष्ठा radeon_device *rdev, bool hard)
अणु
	u32 reset_mask;

	अगर (hard) अणु
		evergreen_gpu_pci_config_reset(rdev);
		वापस 0;
	पूर्ण

	reset_mask = evergreen_gpu_check_soft_reset(rdev);

	अगर (reset_mask)
		r600_set_bios_scratch_engine_hung(rdev, true);

	/* try soft reset */
	evergreen_gpu_soft_reset(rdev, reset_mask);

	reset_mask = evergreen_gpu_check_soft_reset(rdev);

	/* try pci config reset */
	अगर (reset_mask && radeon_hard_reset)
		evergreen_gpu_pci_config_reset(rdev);

	reset_mask = evergreen_gpu_check_soft_reset(rdev);

	अगर (!reset_mask)
		r600_set_bios_scratch_engine_hung(rdev, false);

	वापस 0;
पूर्ण

/**
 * evergreen_gfx_is_lockup - Check अगर the GFX engine is locked up
 *
 * @rdev: radeon_device poपूर्णांकer
 * @ring: radeon_ring काष्ठाure holding ring inक्रमmation
 *
 * Check अगर the GFX engine is locked up.
 * Returns true अगर the engine appears to be locked up, false अगर not.
 */
bool evergreen_gfx_is_lockup(काष्ठा radeon_device *rdev, काष्ठा radeon_ring *ring)
अणु
	u32 reset_mask = evergreen_gpu_check_soft_reset(rdev);

	अगर (!(reset_mask & (RADEON_RESET_GFX |
			    RADEON_RESET_COMPUTE |
			    RADEON_RESET_CP))) अणु
		radeon_ring_lockup_update(rdev, ring);
		वापस false;
	पूर्ण
	वापस radeon_ring_test_lockup(rdev, ring);
पूर्ण

/*
 * RLC
 */
#घोषणा RLC_SAVE_RESTORE_LIST_END_MARKER    0x00000000
#घोषणा RLC_CLEAR_STATE_END_MARKER          0x00000001

व्योम sumo_rlc_fini(काष्ठा radeon_device *rdev)
अणु
	पूर्णांक r;

	/* save restore block */
	अगर (rdev->rlc.save_restore_obj) अणु
		r = radeon_bo_reserve(rdev->rlc.save_restore_obj, false);
		अगर (unlikely(r != 0))
			dev_warn(rdev->dev, "(%d) reserve RLC sr bo failed\n", r);
		radeon_bo_unpin(rdev->rlc.save_restore_obj);
		radeon_bo_unreserve(rdev->rlc.save_restore_obj);

		radeon_bo_unref(&rdev->rlc.save_restore_obj);
		rdev->rlc.save_restore_obj = शून्य;
	पूर्ण

	/* clear state block */
	अगर (rdev->rlc.clear_state_obj) अणु
		r = radeon_bo_reserve(rdev->rlc.clear_state_obj, false);
		अगर (unlikely(r != 0))
			dev_warn(rdev->dev, "(%d) reserve RLC c bo failed\n", r);
		radeon_bo_unpin(rdev->rlc.clear_state_obj);
		radeon_bo_unreserve(rdev->rlc.clear_state_obj);

		radeon_bo_unref(&rdev->rlc.clear_state_obj);
		rdev->rlc.clear_state_obj = शून्य;
	पूर्ण

	/* clear state block */
	अगर (rdev->rlc.cp_table_obj) अणु
		r = radeon_bo_reserve(rdev->rlc.cp_table_obj, false);
		अगर (unlikely(r != 0))
			dev_warn(rdev->dev, "(%d) reserve RLC cp table bo failed\n", r);
		radeon_bo_unpin(rdev->rlc.cp_table_obj);
		radeon_bo_unreserve(rdev->rlc.cp_table_obj);

		radeon_bo_unref(&rdev->rlc.cp_table_obj);
		rdev->rlc.cp_table_obj = शून्य;
	पूर्ण
पूर्ण

#घोषणा CP_ME_TABLE_SIZE    96

पूर्णांक sumo_rlc_init(काष्ठा radeon_device *rdev)
अणु
	स्थिर u32 *src_ptr;
	अस्थिर u32 *dst_ptr;
	u32 dws, data, i, j, k, reg_num;
	u32 reg_list_num, reg_list_hdr_blk_index, reg_list_blk_index = 0;
	u64 reg_list_mc_addr;
	स्थिर काष्ठा cs_section_def *cs_data;
	पूर्णांक r;

	src_ptr = rdev->rlc.reg_list;
	dws = rdev->rlc.reg_list_size;
	अगर (rdev->family >= CHIP_BONAIRE) अणु
		dws += (5 * 16) + 48 + 48 + 64;
	पूर्ण
	cs_data = rdev->rlc.cs_data;

	अगर (src_ptr) अणु
		/* save restore block */
		अगर (rdev->rlc.save_restore_obj == शून्य) अणु
			r = radeon_bo_create(rdev, dws * 4, PAGE_SIZE, true,
					     RADEON_GEM_DOMAIN_VRAM, 0, शून्य,
					     शून्य, &rdev->rlc.save_restore_obj);
			अगर (r) अणु
				dev_warn(rdev->dev, "(%d) create RLC sr bo failed\n", r);
				वापस r;
			पूर्ण
		पूर्ण

		r = radeon_bo_reserve(rdev->rlc.save_restore_obj, false);
		अगर (unlikely(r != 0)) अणु
			sumo_rlc_fini(rdev);
			वापस r;
		पूर्ण
		r = radeon_bo_pin(rdev->rlc.save_restore_obj, RADEON_GEM_DOMAIN_VRAM,
				  &rdev->rlc.save_restore_gpu_addr);
		अगर (r) अणु
			radeon_bo_unreserve(rdev->rlc.save_restore_obj);
			dev_warn(rdev->dev, "(%d) pin RLC sr bo failed\n", r);
			sumo_rlc_fini(rdev);
			वापस r;
		पूर्ण

		r = radeon_bo_kmap(rdev->rlc.save_restore_obj, (व्योम **)&rdev->rlc.sr_ptr);
		अगर (r) अणु
			dev_warn(rdev->dev, "(%d) map RLC sr bo failed\n", r);
			sumo_rlc_fini(rdev);
			वापस r;
		पूर्ण
		/* ग_लिखो the sr buffer */
		dst_ptr = rdev->rlc.sr_ptr;
		अगर (rdev->family >= CHIP_TAHITI) अणु
			/* SI */
			क्रम (i = 0; i < rdev->rlc.reg_list_size; i++)
				dst_ptr[i] = cpu_to_le32(src_ptr[i]);
		पूर्ण अन्यथा अणु
			/* ON/LN/TN */
			/* क्रमmat:
			 * dw0: (reg2 << 16) | reg1
			 * dw1: reg1 save space
			 * dw2: reg2 save space
			 */
			क्रम (i = 0; i < dws; i++) अणु
				data = src_ptr[i] >> 2;
				i++;
				अगर (i < dws)
					data |= (src_ptr[i] >> 2) << 16;
				j = (((i - 1) * 3) / 2);
				dst_ptr[j] = cpu_to_le32(data);
			पूर्ण
			j = ((i * 3) / 2);
			dst_ptr[j] = cpu_to_le32(RLC_SAVE_RESTORE_LIST_END_MARKER);
		पूर्ण
		radeon_bo_kunmap(rdev->rlc.save_restore_obj);
		radeon_bo_unreserve(rdev->rlc.save_restore_obj);
	पूर्ण

	अगर (cs_data) अणु
		/* clear state block */
		अगर (rdev->family >= CHIP_BONAIRE) अणु
			rdev->rlc.clear_state_size = dws = cik_get_csb_size(rdev);
		पूर्ण अन्यथा अगर (rdev->family >= CHIP_TAHITI) अणु
			rdev->rlc.clear_state_size = si_get_csb_size(rdev);
			dws = rdev->rlc.clear_state_size + (256 / 4);
		पूर्ण अन्यथा अणु
			reg_list_num = 0;
			dws = 0;
			क्रम (i = 0; cs_data[i].section != शून्य; i++) अणु
				क्रम (j = 0; cs_data[i].section[j].extent != शून्य; j++) अणु
					reg_list_num++;
					dws += cs_data[i].section[j].reg_count;
				पूर्ण
			पूर्ण
			reg_list_blk_index = (3 * reg_list_num + 2);
			dws += reg_list_blk_index;
			rdev->rlc.clear_state_size = dws;
		पूर्ण

		अगर (rdev->rlc.clear_state_obj == शून्य) अणु
			r = radeon_bo_create(rdev, dws * 4, PAGE_SIZE, true,
					     RADEON_GEM_DOMAIN_VRAM, 0, शून्य,
					     शून्य, &rdev->rlc.clear_state_obj);
			अगर (r) अणु
				dev_warn(rdev->dev, "(%d) create RLC c bo failed\n", r);
				sumo_rlc_fini(rdev);
				वापस r;
			पूर्ण
		पूर्ण
		r = radeon_bo_reserve(rdev->rlc.clear_state_obj, false);
		अगर (unlikely(r != 0)) अणु
			sumo_rlc_fini(rdev);
			वापस r;
		पूर्ण
		r = radeon_bo_pin(rdev->rlc.clear_state_obj, RADEON_GEM_DOMAIN_VRAM,
				  &rdev->rlc.clear_state_gpu_addr);
		अगर (r) अणु
			radeon_bo_unreserve(rdev->rlc.clear_state_obj);
			dev_warn(rdev->dev, "(%d) pin RLC c bo failed\n", r);
			sumo_rlc_fini(rdev);
			वापस r;
		पूर्ण

		r = radeon_bo_kmap(rdev->rlc.clear_state_obj, (व्योम **)&rdev->rlc.cs_ptr);
		अगर (r) अणु
			dev_warn(rdev->dev, "(%d) map RLC c bo failed\n", r);
			sumo_rlc_fini(rdev);
			वापस r;
		पूर्ण
		/* set up the cs buffer */
		dst_ptr = rdev->rlc.cs_ptr;
		अगर (rdev->family >= CHIP_BONAIRE) अणु
			cik_get_csb_buffer(rdev, dst_ptr);
		पूर्ण अन्यथा अगर (rdev->family >= CHIP_TAHITI) अणु
			reg_list_mc_addr = rdev->rlc.clear_state_gpu_addr + 256;
			dst_ptr[0] = cpu_to_le32(upper_32_bits(reg_list_mc_addr));
			dst_ptr[1] = cpu_to_le32(lower_32_bits(reg_list_mc_addr));
			dst_ptr[2] = cpu_to_le32(rdev->rlc.clear_state_size);
			si_get_csb_buffer(rdev, &dst_ptr[(256/4)]);
		पूर्ण अन्यथा अणु
			reg_list_hdr_blk_index = 0;
			reg_list_mc_addr = rdev->rlc.clear_state_gpu_addr + (reg_list_blk_index * 4);
			data = upper_32_bits(reg_list_mc_addr);
			dst_ptr[reg_list_hdr_blk_index] = cpu_to_le32(data);
			reg_list_hdr_blk_index++;
			क्रम (i = 0; cs_data[i].section != शून्य; i++) अणु
				क्रम (j = 0; cs_data[i].section[j].extent != शून्य; j++) अणु
					reg_num = cs_data[i].section[j].reg_count;
					data = reg_list_mc_addr & 0xffffffff;
					dst_ptr[reg_list_hdr_blk_index] = cpu_to_le32(data);
					reg_list_hdr_blk_index++;

					data = (cs_data[i].section[j].reg_index * 4) & 0xffffffff;
					dst_ptr[reg_list_hdr_blk_index] = cpu_to_le32(data);
					reg_list_hdr_blk_index++;

					data = 0x08000000 | (reg_num * 4);
					dst_ptr[reg_list_hdr_blk_index] = cpu_to_le32(data);
					reg_list_hdr_blk_index++;

					क्रम (k = 0; k < reg_num; k++) अणु
						data = cs_data[i].section[j].extent[k];
						dst_ptr[reg_list_blk_index + k] = cpu_to_le32(data);
					पूर्ण
					reg_list_mc_addr += reg_num * 4;
					reg_list_blk_index += reg_num;
				पूर्ण
			पूर्ण
			dst_ptr[reg_list_hdr_blk_index] = cpu_to_le32(RLC_CLEAR_STATE_END_MARKER);
		पूर्ण
		radeon_bo_kunmap(rdev->rlc.clear_state_obj);
		radeon_bo_unreserve(rdev->rlc.clear_state_obj);
	पूर्ण

	अगर (rdev->rlc.cp_table_size) अणु
		अगर (rdev->rlc.cp_table_obj == शून्य) अणु
			r = radeon_bo_create(rdev, rdev->rlc.cp_table_size,
					     PAGE_SIZE, true,
					     RADEON_GEM_DOMAIN_VRAM, 0, शून्य,
					     शून्य, &rdev->rlc.cp_table_obj);
			अगर (r) अणु
				dev_warn(rdev->dev, "(%d) create RLC cp table bo failed\n", r);
				sumo_rlc_fini(rdev);
				वापस r;
			पूर्ण
		पूर्ण

		r = radeon_bo_reserve(rdev->rlc.cp_table_obj, false);
		अगर (unlikely(r != 0)) अणु
			dev_warn(rdev->dev, "(%d) reserve RLC cp table bo failed\n", r);
			sumo_rlc_fini(rdev);
			वापस r;
		पूर्ण
		r = radeon_bo_pin(rdev->rlc.cp_table_obj, RADEON_GEM_DOMAIN_VRAM,
				  &rdev->rlc.cp_table_gpu_addr);
		अगर (r) अणु
			radeon_bo_unreserve(rdev->rlc.cp_table_obj);
			dev_warn(rdev->dev, "(%d) pin RLC cp_table bo failed\n", r);
			sumo_rlc_fini(rdev);
			वापस r;
		पूर्ण
		r = radeon_bo_kmap(rdev->rlc.cp_table_obj, (व्योम **)&rdev->rlc.cp_table_ptr);
		अगर (r) अणु
			dev_warn(rdev->dev, "(%d) map RLC cp table bo failed\n", r);
			sumo_rlc_fini(rdev);
			वापस r;
		पूर्ण

		cik_init_cp_pg_table(rdev);

		radeon_bo_kunmap(rdev->rlc.cp_table_obj);
		radeon_bo_unreserve(rdev->rlc.cp_table_obj);

	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम evergreen_rlc_start(काष्ठा radeon_device *rdev)
अणु
	u32 mask = RLC_ENABLE;

	अगर (rdev->flags & RADEON_IS_IGP) अणु
		mask |= GFX_POWER_GATING_ENABLE | GFX_POWER_GATING_SRC;
	पूर्ण

	WREG32(RLC_CNTL, mask);
पूर्ण

पूर्णांक evergreen_rlc_resume(काष्ठा radeon_device *rdev)
अणु
	u32 i;
	स्थिर __be32 *fw_data;

	अगर (!rdev->rlc_fw)
		वापस -EINVAL;

	r600_rlc_stop(rdev);

	WREG32(RLC_HB_CNTL, 0);

	अगर (rdev->flags & RADEON_IS_IGP) अणु
		अगर (rdev->family == CHIP_ARUBA) अणु
			u32 always_on_biपंचांगap =
				3 | (3 << (16 * rdev->config.cayman.max_shader_engines));
			/* find out the number of active simds */
			u32 पंचांगp = (RREG32(CC_GC_SHADER_PIPE_CONFIG) & 0xffff0000) >> 16;
			पंचांगp |= 0xffffffff << rdev->config.cayman.max_simds_per_se;
			पंचांगp = hweight32(~पंचांगp);
			अगर (पंचांगp == rdev->config.cayman.max_simds_per_se) अणु
				WREG32(TN_RLC_LB_ALWAYS_ACTIVE_SIMD_MASK, always_on_biपंचांगap);
				WREG32(TN_RLC_LB_PARAMS, 0x00601004);
				WREG32(TN_RLC_LB_INIT_SIMD_MASK, 0xffffffff);
				WREG32(TN_RLC_LB_CNTR_INIT, 0x00000000);
				WREG32(TN_RLC_LB_CNTR_MAX, 0x00002000);
			पूर्ण
		पूर्ण अन्यथा अणु
			WREG32(RLC_HB_WPTR_LSB_ADDR, 0);
			WREG32(RLC_HB_WPTR_MSB_ADDR, 0);
		पूर्ण
		WREG32(TN_RLC_SAVE_AND_RESTORE_BASE, rdev->rlc.save_restore_gpu_addr >> 8);
		WREG32(TN_RLC_CLEAR_STATE_RESTORE_BASE, rdev->rlc.clear_state_gpu_addr >> 8);
	पूर्ण अन्यथा अणु
		WREG32(RLC_HB_BASE, 0);
		WREG32(RLC_HB_RPTR, 0);
		WREG32(RLC_HB_WPTR, 0);
		WREG32(RLC_HB_WPTR_LSB_ADDR, 0);
		WREG32(RLC_HB_WPTR_MSB_ADDR, 0);
	पूर्ण
	WREG32(RLC_MC_CNTL, 0);
	WREG32(RLC_UCODE_CNTL, 0);

	fw_data = (स्थिर __be32 *)rdev->rlc_fw->data;
	अगर (rdev->family >= CHIP_ARUBA) अणु
		क्रम (i = 0; i < ARUBA_RLC_UCODE_SIZE; i++) अणु
			WREG32(RLC_UCODE_ADDR, i);
			WREG32(RLC_UCODE_DATA, be32_to_cpup(fw_data++));
		पूर्ण
	पूर्ण अन्यथा अगर (rdev->family >= CHIP_CAYMAN) अणु
		क्रम (i = 0; i < CAYMAN_RLC_UCODE_SIZE; i++) अणु
			WREG32(RLC_UCODE_ADDR, i);
			WREG32(RLC_UCODE_DATA, be32_to_cpup(fw_data++));
		पूर्ण
	पूर्ण अन्यथा अणु
		क्रम (i = 0; i < EVERGREEN_RLC_UCODE_SIZE; i++) अणु
			WREG32(RLC_UCODE_ADDR, i);
			WREG32(RLC_UCODE_DATA, be32_to_cpup(fw_data++));
		पूर्ण
	पूर्ण
	WREG32(RLC_UCODE_ADDR, 0);

	evergreen_rlc_start(rdev);

	वापस 0;
पूर्ण

/* Interrupts */

u32 evergreen_get_vblank_counter(काष्ठा radeon_device *rdev, पूर्णांक crtc)
अणु
	अगर (crtc >= rdev->num_crtc)
		वापस 0;
	अन्यथा
		वापस RREG32(CRTC_STATUS_FRAME_COUNT + crtc_offsets[crtc]);
पूर्ण

व्योम evergreen_disable_पूर्णांकerrupt_state(काष्ठा radeon_device *rdev)
अणु
	पूर्णांक i;
	u32 पंचांगp;

	अगर (rdev->family >= CHIP_CAYMAN) अणु
		cayman_cp_पूर्णांक_cntl_setup(rdev, 0,
					 CNTX_BUSY_INT_ENABLE | CNTX_EMPTY_INT_ENABLE);
		cayman_cp_पूर्णांक_cntl_setup(rdev, 1, 0);
		cayman_cp_पूर्णांक_cntl_setup(rdev, 2, 0);
		पंचांगp = RREG32(CAYMAN_DMA1_CNTL) & ~TRAP_ENABLE;
		WREG32(CAYMAN_DMA1_CNTL, पंचांगp);
	पूर्ण अन्यथा
		WREG32(CP_INT_CNTL, CNTX_BUSY_INT_ENABLE | CNTX_EMPTY_INT_ENABLE);
	पंचांगp = RREG32(DMA_CNTL) & ~TRAP_ENABLE;
	WREG32(DMA_CNTL, पंचांगp);
	WREG32(GRBM_INT_CNTL, 0);
	WREG32(SRBM_INT_CNTL, 0);
	क्रम (i = 0; i < rdev->num_crtc; i++)
		WREG32(INT_MASK + crtc_offsets[i], 0);
	क्रम (i = 0; i < rdev->num_crtc; i++)
		WREG32(GRPH_INT_CONTROL + crtc_offsets[i], 0);

	/* only one DAC on DCE5 */
	अगर (!ASIC_IS_DCE5(rdev))
		WREG32(DACA_AUTODETECT_INT_CONTROL, 0);
	WREG32(DACB_AUTODETECT_INT_CONTROL, 0);

	क्रम (i = 0; i < 6; i++)
		WREG32_AND(DC_HPDx_INT_CONTROL(i), DC_HPDx_INT_POLARITY);
पूर्ण

/* Note that the order we ग_लिखो back regs here is important */
पूर्णांक evergreen_irq_set(काष्ठा radeon_device *rdev)
अणु
	पूर्णांक i;
	u32 cp_पूर्णांक_cntl = CNTX_BUSY_INT_ENABLE | CNTX_EMPTY_INT_ENABLE;
	u32 cp_पूर्णांक_cntl1 = 0, cp_पूर्णांक_cntl2 = 0;
	u32 grbm_पूर्णांक_cntl = 0;
	u32 dma_cntl, dma_cntl1 = 0;
	u32 thermal_पूर्णांक = 0;

	अगर (!rdev->irq.installed) अणु
		WARN(1, "Can't enable IRQ/MSI because no handler is installed\n");
		वापस -EINVAL;
	पूर्ण
	/* करोn't enable anything अगर the ih is disabled */
	अगर (!rdev->ih.enabled) अणु
		r600_disable_पूर्णांकerrupts(rdev);
		/* क्रमce the active पूर्णांकerrupt state to all disabled */
		evergreen_disable_पूर्णांकerrupt_state(rdev);
		वापस 0;
	पूर्ण

	अगर (rdev->family == CHIP_ARUBA)
		thermal_पूर्णांक = RREG32(TN_CG_THERMAL_INT_CTRL) &
			~(THERM_INT_MASK_HIGH | THERM_INT_MASK_LOW);
	अन्यथा
		thermal_पूर्णांक = RREG32(CG_THERMAL_INT) &
			~(THERM_INT_MASK_HIGH | THERM_INT_MASK_LOW);

	dma_cntl = RREG32(DMA_CNTL) & ~TRAP_ENABLE;

	अगर (rdev->family >= CHIP_CAYMAN) अणु
		/* enable CP पूर्णांकerrupts on all rings */
		अगर (atomic_पढ़ो(&rdev->irq.ring_पूर्णांक[RADEON_RING_TYPE_GFX_INDEX])) अणु
			DRM_DEBUG("evergreen_irq_set: sw int gfx\n");
			cp_पूर्णांक_cntl |= TIME_STAMP_INT_ENABLE;
		पूर्ण
		अगर (atomic_पढ़ो(&rdev->irq.ring_पूर्णांक[CAYMAN_RING_TYPE_CP1_INDEX])) अणु
			DRM_DEBUG("evergreen_irq_set: sw int cp1\n");
			cp_पूर्णांक_cntl1 |= TIME_STAMP_INT_ENABLE;
		पूर्ण
		अगर (atomic_पढ़ो(&rdev->irq.ring_पूर्णांक[CAYMAN_RING_TYPE_CP2_INDEX])) अणु
			DRM_DEBUG("evergreen_irq_set: sw int cp2\n");
			cp_पूर्णांक_cntl2 |= TIME_STAMP_INT_ENABLE;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (atomic_पढ़ो(&rdev->irq.ring_पूर्णांक[RADEON_RING_TYPE_GFX_INDEX])) अणु
			DRM_DEBUG("evergreen_irq_set: sw int gfx\n");
			cp_पूर्णांक_cntl |= RB_INT_ENABLE;
			cp_पूर्णांक_cntl |= TIME_STAMP_INT_ENABLE;
		पूर्ण
	पूर्ण

	अगर (atomic_पढ़ो(&rdev->irq.ring_पूर्णांक[R600_RING_TYPE_DMA_INDEX])) अणु
		DRM_DEBUG("r600_irq_set: sw int dma\n");
		dma_cntl |= TRAP_ENABLE;
	पूर्ण

	अगर (rdev->family >= CHIP_CAYMAN) अणु
		dma_cntl1 = RREG32(CAYMAN_DMA1_CNTL) & ~TRAP_ENABLE;
		अगर (atomic_पढ़ो(&rdev->irq.ring_पूर्णांक[CAYMAN_RING_TYPE_DMA1_INDEX])) अणु
			DRM_DEBUG("r600_irq_set: sw int dma1\n");
			dma_cntl1 |= TRAP_ENABLE;
		पूर्ण
	पूर्ण

	अगर (rdev->irq.dpm_thermal) अणु
		DRM_DEBUG("dpm thermal\n");
		thermal_पूर्णांक |= THERM_INT_MASK_HIGH | THERM_INT_MASK_LOW;
	पूर्ण

	अगर (rdev->family >= CHIP_CAYMAN) अणु
		cayman_cp_पूर्णांक_cntl_setup(rdev, 0, cp_पूर्णांक_cntl);
		cayman_cp_पूर्णांक_cntl_setup(rdev, 1, cp_पूर्णांक_cntl1);
		cayman_cp_पूर्णांक_cntl_setup(rdev, 2, cp_पूर्णांक_cntl2);
	पूर्ण अन्यथा
		WREG32(CP_INT_CNTL, cp_पूर्णांक_cntl);

	WREG32(DMA_CNTL, dma_cntl);

	अगर (rdev->family >= CHIP_CAYMAN)
		WREG32(CAYMAN_DMA1_CNTL, dma_cntl1);

	WREG32(GRBM_INT_CNTL, grbm_पूर्णांक_cntl);

	क्रम (i = 0; i < rdev->num_crtc; i++) अणु
		radeon_irq_kms_set_irq_n_enabled(
		    rdev, INT_MASK + crtc_offsets[i],
		    VBLANK_INT_MASK,
		    rdev->irq.crtc_vblank_पूर्णांक[i] ||
		    atomic_पढ़ो(&rdev->irq.pflip[i]), "vblank", i);
	पूर्ण

	क्रम (i = 0; i < rdev->num_crtc; i++)
		WREG32(GRPH_INT_CONTROL + crtc_offsets[i], GRPH_PFLIP_INT_MASK);

	क्रम (i = 0; i < 6; i++) अणु
		radeon_irq_kms_set_irq_n_enabled(
		    rdev, DC_HPDx_INT_CONTROL(i),
		    DC_HPDx_INT_EN | DC_HPDx_RX_INT_EN,
		    rdev->irq.hpd[i], "HPD", i);
	पूर्ण

	अगर (rdev->family == CHIP_ARUBA)
		WREG32(TN_CG_THERMAL_INT_CTRL, thermal_पूर्णांक);
	अन्यथा
		WREG32(CG_THERMAL_INT, thermal_पूर्णांक);

	क्रम (i = 0; i < 6; i++) अणु
		radeon_irq_kms_set_irq_n_enabled(
		    rdev, AFMT_AUDIO_PACKET_CONTROL + crtc_offsets[i],
		    AFMT_AZ_FORMAT_WTRIG_MASK,
		    rdev->irq.afmt[i], "HDMI", i);
	पूर्ण

	/* posting पढ़ो */
	RREG32(SRBM_STATUS);

	वापस 0;
पूर्ण

/* Note that the order we ग_लिखो back regs here is important */
अटल व्योम evergreen_irq_ack(काष्ठा radeon_device *rdev)
अणु
	पूर्णांक i, j;
	u32 *grph_पूर्णांक = rdev->irq.stat_regs.evergreen.grph_पूर्णांक;
	u32 *disp_पूर्णांक = rdev->irq.stat_regs.evergreen.disp_पूर्णांक;
	u32 *afmt_status = rdev->irq.stat_regs.evergreen.afmt_status;

	क्रम (i = 0; i < 6; i++) अणु
		disp_पूर्णांक[i] = RREG32(evergreen_disp_पूर्णांक_status[i]);
		afmt_status[i] = RREG32(AFMT_STATUS + crtc_offsets[i]);
		अगर (i < rdev->num_crtc)
			grph_पूर्णांक[i] = RREG32(GRPH_INT_STATUS + crtc_offsets[i]);
	पूर्ण

	/* We ग_लिखो back each पूर्णांकerrupt रेजिस्टर in pairs of two */
	क्रम (i = 0; i < rdev->num_crtc; i += 2) अणु
		क्रम (j = i; j < (i + 2); j++) अणु
			अगर (grph_पूर्णांक[j] & GRPH_PFLIP_INT_OCCURRED)
				WREG32(GRPH_INT_STATUS + crtc_offsets[j],
				       GRPH_PFLIP_INT_CLEAR);
		पूर्ण

		क्रम (j = i; j < (i + 2); j++) अणु
			अगर (disp_पूर्णांक[j] & LB_D1_VBLANK_INTERRUPT)
				WREG32(VBLANK_STATUS + crtc_offsets[j],
				       VBLANK_ACK);
			अगर (disp_पूर्णांक[j] & LB_D1_VLINE_INTERRUPT)
				WREG32(VLINE_STATUS + crtc_offsets[j],
				       VLINE_ACK);
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < 6; i++) अणु
		अगर (disp_पूर्णांक[i] & DC_HPD1_INTERRUPT)
			WREG32_OR(DC_HPDx_INT_CONTROL(i), DC_HPDx_INT_ACK);
	पूर्ण

	क्रम (i = 0; i < 6; i++) अणु
		अगर (disp_पूर्णांक[i] & DC_HPD1_RX_INTERRUPT)
			WREG32_OR(DC_HPDx_INT_CONTROL(i), DC_HPDx_RX_INT_ACK);
	पूर्ण

	क्रम (i = 0; i < 6; i++) अणु
		अगर (afmt_status[i] & AFMT_AZ_FORMAT_WTRIG)
			WREG32_OR(AFMT_AUDIO_PACKET_CONTROL + crtc_offsets[i],
				  AFMT_AZ_FORMAT_WTRIG_ACK);
	पूर्ण
पूर्ण

अटल व्योम evergreen_irq_disable(काष्ठा radeon_device *rdev)
अणु
	r600_disable_पूर्णांकerrupts(rdev);
	/* Wait and acknowledge irq */
	mdelay(1);
	evergreen_irq_ack(rdev);
	evergreen_disable_पूर्णांकerrupt_state(rdev);
पूर्ण

व्योम evergreen_irq_suspend(काष्ठा radeon_device *rdev)
अणु
	evergreen_irq_disable(rdev);
	r600_rlc_stop(rdev);
पूर्ण

अटल u32 evergreen_get_ih_wptr(काष्ठा radeon_device *rdev)
अणु
	u32 wptr, पंचांगp;

	अगर (rdev->wb.enabled)
		wptr = le32_to_cpu(rdev->wb.wb[R600_WB_IH_WPTR_OFFSET/4]);
	अन्यथा
		wptr = RREG32(IH_RB_WPTR);

	अगर (wptr & RB_OVERFLOW) अणु
		wptr &= ~RB_OVERFLOW;
		/* When a ring buffer overflow happen start parsing पूर्णांकerrupt
		 * from the last not overwritten vector (wptr + 16). Hopefully
		 * this should allow us to catchup.
		 */
		dev_warn(rdev->dev, "IH ring buffer overflow (0x%08X, 0x%08X, 0x%08X)\n",
			 wptr, rdev->ih.rptr, (wptr + 16) & rdev->ih.ptr_mask);
		rdev->ih.rptr = (wptr + 16) & rdev->ih.ptr_mask;
		पंचांगp = RREG32(IH_RB_CNTL);
		पंचांगp |= IH_WPTR_OVERFLOW_CLEAR;
		WREG32(IH_RB_CNTL, पंचांगp);
	पूर्ण
	वापस (wptr & rdev->ih.ptr_mask);
पूर्ण

पूर्णांक evergreen_irq_process(काष्ठा radeon_device *rdev)
अणु
	u32 *disp_पूर्णांक = rdev->irq.stat_regs.evergreen.disp_पूर्णांक;
	u32 *afmt_status = rdev->irq.stat_regs.evergreen.afmt_status;
	u32 crtc_idx, hpd_idx, afmt_idx;
	u32 mask;
	u32 wptr;
	u32 rptr;
	u32 src_id, src_data;
	u32 ring_index;
	bool queue_hotplug = false;
	bool queue_hdmi = false;
	bool queue_dp = false;
	bool queue_thermal = false;
	u32 status, addr;
	स्थिर अक्षर *event_name;

	अगर (!rdev->ih.enabled || rdev->shutकरोwn)
		वापस IRQ_NONE;

	wptr = evergreen_get_ih_wptr(rdev);

restart_ih:
	/* is somebody अन्यथा alपढ़ोy processing irqs? */
	अगर (atomic_xchg(&rdev->ih.lock, 1))
		वापस IRQ_NONE;

	rptr = rdev->ih.rptr;
	DRM_DEBUG("evergreen_irq_process start: rptr %d, wptr %d\n", rptr, wptr);

	/* Order पढ़ोing of wptr vs. पढ़ोing of IH ring data */
	rmb();

	/* display पूर्णांकerrupts */
	evergreen_irq_ack(rdev);

	जबतक (rptr != wptr) अणु
		/* wptr/rptr are in bytes! */
		ring_index = rptr / 4;
		src_id =  le32_to_cpu(rdev->ih.ring[ring_index]) & 0xff;
		src_data = le32_to_cpu(rdev->ih.ring[ring_index + 1]) & 0xfffffff;

		चयन (src_id) अणु
		हाल 1: /* D1 vblank/vline */
		हाल 2: /* D2 vblank/vline */
		हाल 3: /* D3 vblank/vline */
		हाल 4: /* D4 vblank/vline */
		हाल 5: /* D5 vblank/vline */
		हाल 6: /* D6 vblank/vline */
			crtc_idx = src_id - 1;

			अगर (src_data == 0) अणु /* vblank */
				mask = LB_D1_VBLANK_INTERRUPT;
				event_name = "vblank";

				अगर (rdev->irq.crtc_vblank_पूर्णांक[crtc_idx]) अणु
					drm_handle_vblank(rdev->ddev, crtc_idx);
					rdev->pm.vblank_sync = true;
					wake_up(&rdev->irq.vblank_queue);
				पूर्ण
				अगर (atomic_पढ़ो(&rdev->irq.pflip[crtc_idx])) अणु
					radeon_crtc_handle_vblank(rdev,
								  crtc_idx);
				पूर्ण

			पूर्ण अन्यथा अगर (src_data == 1) अणु /* vline */
				mask = LB_D1_VLINE_INTERRUPT;
				event_name = "vline";
			पूर्ण अन्यथा अणु
				DRM_DEBUG("Unhandled interrupt: %d %d\n",
					  src_id, src_data);
				अवरोध;
			पूर्ण

			अगर (!(disp_पूर्णांक[crtc_idx] & mask)) अणु
				DRM_DEBUG("IH: D%d %s - IH event w/o asserted irq bit?\n",
					  crtc_idx + 1, event_name);
			पूर्ण

			disp_पूर्णांक[crtc_idx] &= ~mask;
			DRM_DEBUG("IH: D%d %s\n", crtc_idx + 1, event_name);

			अवरोध;
		हाल 8: /* D1 page flip */
		हाल 10: /* D2 page flip */
		हाल 12: /* D3 page flip */
		हाल 14: /* D4 page flip */
		हाल 16: /* D5 page flip */
		हाल 18: /* D6 page flip */
			DRM_DEBUG("IH: D%d flip\n", ((src_id - 8) >> 1) + 1);
			अगर (radeon_use_pflipirq > 0)
				radeon_crtc_handle_flip(rdev, (src_id - 8) >> 1);
			अवरोध;
		हाल 42: /* HPD hotplug */
			अगर (src_data <= 5) अणु
				hpd_idx = src_data;
				mask = DC_HPD1_INTERRUPT;
				queue_hotplug = true;
				event_name = "HPD";

			पूर्ण अन्यथा अगर (src_data <= 11) अणु
				hpd_idx = src_data - 6;
				mask = DC_HPD1_RX_INTERRUPT;
				queue_dp = true;
				event_name = "HPD_RX";

			पूर्ण अन्यथा अणु
				DRM_DEBUG("Unhandled interrupt: %d %d\n",
					  src_id, src_data);
				अवरोध;
			पूर्ण

			अगर (!(disp_पूर्णांक[hpd_idx] & mask))
				DRM_DEBUG("IH: IH event w/o asserted irq bit?\n");

			disp_पूर्णांक[hpd_idx] &= ~mask;
			DRM_DEBUG("IH: %s%d\n", event_name, hpd_idx + 1);

			अवरोध;
		हाल 44: /* hdmi */
			afmt_idx = src_data;
			अगर (!(afmt_status[afmt_idx] & AFMT_AZ_FORMAT_WTRIG))
				DRM_DEBUG("IH: IH event w/o asserted irq bit?\n");

			अगर (afmt_idx > 5) अणु
				DRM_ERROR("Unhandled interrupt: %d %d\n",
					  src_id, src_data);
				अवरोध;
			पूर्ण
			afmt_status[afmt_idx] &= ~AFMT_AZ_FORMAT_WTRIG;
			queue_hdmi = true;
			DRM_DEBUG("IH: HDMI%d\n", afmt_idx + 1);
			अवरोध;
		हाल 96:
			DRM_ERROR("SRBM_READ_ERROR: 0x%x\n", RREG32(SRBM_READ_ERROR));
			WREG32(SRBM_INT_ACK, 0x1);
			अवरोध;
		हाल 124: /* UVD */
			DRM_DEBUG("IH: UVD int: 0x%08x\n", src_data);
			radeon_fence_process(rdev, R600_RING_TYPE_UVD_INDEX);
			अवरोध;
		हाल 146:
		हाल 147:
			addr = RREG32(VM_CONTEXT1_PROTECTION_FAULT_ADDR);
			status = RREG32(VM_CONTEXT1_PROTECTION_FAULT_STATUS);
			/* reset addr and status */
			WREG32_P(VM_CONTEXT1_CNTL2, 1, ~1);
			अगर (addr == 0x0 && status == 0x0)
				अवरोध;
			dev_err(rdev->dev, "GPU fault detected: %d 0x%08x\n", src_id, src_data);
			dev_err(rdev->dev, "  VM_CONTEXT1_PROTECTION_FAULT_ADDR   0x%08X\n",
				addr);
			dev_err(rdev->dev, "  VM_CONTEXT1_PROTECTION_FAULT_STATUS 0x%08X\n",
				status);
			cayman_vm_decode_fault(rdev, status, addr);
			अवरोध;
		हाल 176: /* CP_INT in ring buffer */
		हाल 177: /* CP_INT in IB1 */
		हाल 178: /* CP_INT in IB2 */
			DRM_DEBUG("IH: CP int: 0x%08x\n", src_data);
			radeon_fence_process(rdev, RADEON_RING_TYPE_GFX_INDEX);
			अवरोध;
		हाल 181: /* CP EOP event */
			DRM_DEBUG("IH: CP EOP\n");
			अगर (rdev->family >= CHIP_CAYMAN) अणु
				चयन (src_data) अणु
				हाल 0:
					radeon_fence_process(rdev, RADEON_RING_TYPE_GFX_INDEX);
					अवरोध;
				हाल 1:
					radeon_fence_process(rdev, CAYMAN_RING_TYPE_CP1_INDEX);
					अवरोध;
				हाल 2:
					radeon_fence_process(rdev, CAYMAN_RING_TYPE_CP2_INDEX);
					अवरोध;
				पूर्ण
			पूर्ण अन्यथा
				radeon_fence_process(rdev, RADEON_RING_TYPE_GFX_INDEX);
			अवरोध;
		हाल 224: /* DMA trap event */
			DRM_DEBUG("IH: DMA trap\n");
			radeon_fence_process(rdev, R600_RING_TYPE_DMA_INDEX);
			अवरोध;
		हाल 230: /* thermal low to high */
			DRM_DEBUG("IH: thermal low to high\n");
			rdev->pm.dpm.thermal.high_to_low = false;
			queue_thermal = true;
			अवरोध;
		हाल 231: /* thermal high to low */
			DRM_DEBUG("IH: thermal high to low\n");
			rdev->pm.dpm.thermal.high_to_low = true;
			queue_thermal = true;
			अवरोध;
		हाल 233: /* GUI IDLE */
			DRM_DEBUG("IH: GUI idle\n");
			अवरोध;
		हाल 244: /* DMA trap event */
			अगर (rdev->family >= CHIP_CAYMAN) अणु
				DRM_DEBUG("IH: DMA1 trap\n");
				radeon_fence_process(rdev, CAYMAN_RING_TYPE_DMA1_INDEX);
			पूर्ण
			अवरोध;
		शेष:
			DRM_DEBUG("Unhandled interrupt: %d %d\n", src_id, src_data);
			अवरोध;
		पूर्ण

		/* wptr/rptr are in bytes! */
		rptr += 16;
		rptr &= rdev->ih.ptr_mask;
		WREG32(IH_RB_RPTR, rptr);
	पूर्ण
	अगर (queue_dp)
		schedule_work(&rdev->dp_work);
	अगर (queue_hotplug)
		schedule_delayed_work(&rdev->hotplug_work, 0);
	अगर (queue_hdmi)
		schedule_work(&rdev->audio_work);
	अगर (queue_thermal && rdev->pm.dpm_enabled)
		schedule_work(&rdev->pm.dpm.thermal.work);
	rdev->ih.rptr = rptr;
	atomic_set(&rdev->ih.lock, 0);

	/* make sure wptr hasn't changed जबतक processing */
	wptr = evergreen_get_ih_wptr(rdev);
	अगर (wptr != rptr)
		जाओ restart_ih;

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम evergreen_uvd_init(काष्ठा radeon_device *rdev)
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

अटल व्योम evergreen_uvd_start(काष्ठा radeon_device *rdev)
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

अटल व्योम evergreen_uvd_resume(काष्ठा radeon_device *rdev)
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

अटल पूर्णांक evergreen_startup(काष्ठा radeon_device *rdev)
अणु
	काष्ठा radeon_ring *ring;
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

	अगर (ASIC_IS_DCE5(rdev) && !rdev->pm.dpm_enabled) अणु
		r = ni_mc_load_microcode(rdev);
		अगर (r) अणु
			DRM_ERROR("Failed to load MC firmware!\n");
			वापस r;
		पूर्ण
	पूर्ण

	अगर (rdev->flags & RADEON_IS_AGP) अणु
		evergreen_agp_enable(rdev);
	पूर्ण अन्यथा अणु
		r = evergreen_pcie_gart_enable(rdev);
		अगर (r)
			वापस r;
	पूर्ण
	evergreen_gpu_init(rdev);

	/* allocate rlc buffers */
	अगर (rdev->flags & RADEON_IS_IGP) अणु
		rdev->rlc.reg_list = sumo_rlc_save_restore_रेजिस्टर_list;
		rdev->rlc.reg_list_size =
			(u32)ARRAY_SIZE(sumo_rlc_save_restore_रेजिस्टर_list);
		rdev->rlc.cs_data = evergreen_cs_data;
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

	r = radeon_fence_driver_start_ring(rdev, R600_RING_TYPE_DMA_INDEX);
	अगर (r) अणु
		dev_err(rdev->dev, "failed initializing DMA fences (%d).\n", r);
		वापस r;
	पूर्ण

	evergreen_uvd_start(rdev);

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

	ring = &rdev->ring[RADEON_RING_TYPE_GFX_INDEX];
	r = radeon_ring_init(rdev, ring, ring->ring_size, RADEON_WB_CP_RPTR_OFFSET,
			     RADEON_CP_PACKET2);
	अगर (r)
		वापस r;

	ring = &rdev->ring[R600_RING_TYPE_DMA_INDEX];
	r = radeon_ring_init(rdev, ring, ring->ring_size, R600_WB_DMA_RPTR_OFFSET,
			     DMA_PACKET(DMA_PACKET_NOP, 0, 0));
	अगर (r)
		वापस r;

	r = evergreen_cp_load_microcode(rdev);
	अगर (r)
		वापस r;
	r = evergreen_cp_resume(rdev);
	अगर (r)
		वापस r;
	r = r600_dma_resume(rdev);
	अगर (r)
		वापस r;

	evergreen_uvd_resume(rdev);

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

पूर्णांक evergreen_resume(काष्ठा radeon_device *rdev)
अणु
	पूर्णांक r;

	/* reset the asic, the gfx blocks are often in a bad state
	 * after the driver is unloaded or after a resume
	 */
	अगर (radeon_asic_reset(rdev))
		dev_warn(rdev->dev, "GPU reset failed !\n");
	/* Do not reset GPU beक्रमe posting, on rv770 hw unlike on r500 hw,
	 * posting will perक्रमm necessary task to bring back GPU पूर्णांकo good
	 * shape.
	 */
	/* post card */
	atom_asic_init(rdev->mode_info.atom_context);

	/* init golden रेजिस्टरs */
	evergreen_init_golden_रेजिस्टरs(rdev);

	अगर (rdev->pm.pm_method == PM_METHOD_DPM)
		radeon_pm_resume(rdev);

	rdev->accel_working = true;
	r = evergreen_startup(rdev);
	अगर (r) अणु
		DRM_ERROR("evergreen startup failed on resume\n");
		rdev->accel_working = false;
		वापस r;
	पूर्ण

	वापस r;

पूर्ण

पूर्णांक evergreen_suspend(काष्ठा radeon_device *rdev)
अणु
	radeon_pm_suspend(rdev);
	radeon_audio_fini(rdev);
	अगर (rdev->has_uvd) अणु
		uvd_v1_0_fini(rdev);
		radeon_uvd_suspend(rdev);
	पूर्ण
	r700_cp_stop(rdev);
	r600_dma_stop(rdev);
	evergreen_irq_suspend(rdev);
	radeon_wb_disable(rdev);
	evergreen_pcie_gart_disable(rdev);

	वापस 0;
पूर्ण

/* Plan is to move initialization in that function and use
 * helper function so that radeon_device_init pretty much
 * करो nothing more than calling asic specअगरic function. This
 * should also allow to हटाओ a bunch of callback function
 * like vram_info.
 */
पूर्णांक evergreen_init(काष्ठा radeon_device *rdev)
अणु
	पूर्णांक r;

	/* Read BIOS */
	अगर (!radeon_get_bios(rdev)) अणु
		अगर (ASIC_IS_AVIVO(rdev))
			वापस -EINVAL;
	पूर्ण
	/* Must be an ATOMBIOS */
	अगर (!rdev->is_atom_bios) अणु
		dev_err(rdev->dev, "Expecting atombios for evergreen GPU\n");
		वापस -EINVAL;
	पूर्ण
	r = radeon_atombios_init(rdev);
	अगर (r)
		वापस r;
	/* reset the asic, the gfx blocks are often in a bad state
	 * after the driver is unloaded or after a resume
	 */
	अगर (radeon_asic_reset(rdev))
		dev_warn(rdev->dev, "GPU reset failed !\n");
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
	evergreen_init_golden_रेजिस्टरs(rdev);
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
	/* initialize memory controller */
	r = evergreen_mc_init(rdev);
	अगर (r)
		वापस r;
	/* Memory manager */
	r = radeon_bo_init(rdev);
	अगर (r)
		वापस r;

	अगर (ASIC_IS_DCE5(rdev)) अणु
		अगर (!rdev->me_fw || !rdev->pfp_fw || !rdev->rlc_fw || !rdev->mc_fw) अणु
			r = ni_init_microcode(rdev);
			अगर (r) अणु
				DRM_ERROR("Failed to load firmware!\n");
				वापस r;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (!rdev->me_fw || !rdev->pfp_fw || !rdev->rlc_fw) अणु
			r = r600_init_microcode(rdev);
			अगर (r) अणु
				DRM_ERROR("Failed to load firmware!\n");
				वापस r;
			पूर्ण
		पूर्ण
	पूर्ण

	/* Initialize घातer management */
	radeon_pm_init(rdev);

	rdev->ring[RADEON_RING_TYPE_GFX_INDEX].ring_obj = शून्य;
	r600_ring_init(rdev, &rdev->ring[RADEON_RING_TYPE_GFX_INDEX], 1024 * 1024);

	rdev->ring[R600_RING_TYPE_DMA_INDEX].ring_obj = शून्य;
	r600_ring_init(rdev, &rdev->ring[R600_RING_TYPE_DMA_INDEX], 64 * 1024);

	evergreen_uvd_init(rdev);

	rdev->ih.ring_obj = शून्य;
	r600_ih_ring_init(rdev, 64 * 1024);

	r = r600_pcie_gart_init(rdev);
	अगर (r)
		वापस r;

	rdev->accel_working = true;
	r = evergreen_startup(rdev);
	अगर (r) अणु
		dev_err(rdev->dev, "disabling GPU acceleration\n");
		r700_cp_fini(rdev);
		r600_dma_fini(rdev);
		r600_irq_fini(rdev);
		अगर (rdev->flags & RADEON_IS_IGP)
			sumo_rlc_fini(rdev);
		radeon_wb_fini(rdev);
		radeon_ib_pool_fini(rdev);
		radeon_irq_kms_fini(rdev);
		evergreen_pcie_gart_fini(rdev);
		rdev->accel_working = false;
	पूर्ण

	/* Don't start up अगर the MC ucode is missing on BTC parts.
	 * The शेष घड़ीs and voltages beक्रमe the MC ucode
	 * is loaded are not suffient क्रम advanced operations.
	 */
	अगर (ASIC_IS_DCE5(rdev)) अणु
		अगर (!rdev->mc_fw && !(rdev->flags & RADEON_IS_IGP)) अणु
			DRM_ERROR("radeon: MC ucode required for NI+.\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

व्योम evergreen_fini(काष्ठा radeon_device *rdev)
अणु
	radeon_pm_fini(rdev);
	radeon_audio_fini(rdev);
	r700_cp_fini(rdev);
	r600_dma_fini(rdev);
	r600_irq_fini(rdev);
	अगर (rdev->flags & RADEON_IS_IGP)
		sumo_rlc_fini(rdev);
	radeon_wb_fini(rdev);
	radeon_ib_pool_fini(rdev);
	radeon_irq_kms_fini(rdev);
	uvd_v1_0_fini(rdev);
	radeon_uvd_fini(rdev);
	evergreen_pcie_gart_fini(rdev);
	r600_vram_scratch_fini(rdev);
	radeon_gem_fini(rdev);
	radeon_fence_driver_fini(rdev);
	radeon_agp_fini(rdev);
	radeon_bo_fini(rdev);
	radeon_atombios_fini(rdev);
	kमुक्त(rdev->bios);
	rdev->bios = शून्य;
पूर्ण

व्योम evergreen_pcie_gen2_enable(काष्ठा radeon_device *rdev)
अणु
	u32 link_width_cntl, speed_cntl;

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

	speed_cntl = RREG32_PCIE_PORT(PCIE_LC_SPEED_CNTL);
	अगर (speed_cntl & LC_CURRENT_DATA_RATE) अणु
		DRM_INFO("PCIE gen 2 link speeds already enabled\n");
		वापस;
	पूर्ण

	DRM_INFO("enabling PCIE gen 2 link speeds, disable with radeon.pcie_gen2=0\n");

	अगर ((speed_cntl & LC_OTHER_SIDE_EVER_SENT_GEN2) ||
	    (speed_cntl & LC_OTHER_SIDE_SUPPORTS_GEN2)) अणु

		link_width_cntl = RREG32_PCIE_PORT(PCIE_LC_LINK_WIDTH_CNTL);
		link_width_cntl &= ~LC_UPCONFIGURE_DIS;
		WREG32_PCIE_PORT(PCIE_LC_LINK_WIDTH_CNTL, link_width_cntl);

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

व्योम evergreen_program_aspm(काष्ठा radeon_device *rdev)
अणु
	u32 data, orig;
	u32 pcie_lc_cntl, pcie_lc_cntl_old;
	bool disable_l0s, disable_l1 = false, disable_plloff_in_l1 = false;
	/* fusion_platक्रमm = true
	 * अगर the प्रणाली is a fusion प्रणाली
	 * (APU or DGPU in a fusion प्रणाली).
	 * toकरो: check अगर the प्रणाली is a fusion platक्रमm.
	 */
	bool fusion_platक्रमm = false;

	अगर (radeon_aspm == 0)
		वापस;

	अगर (!(rdev->flags & RADEON_IS_PCIE))
		वापस;

	चयन (rdev->family) अणु
	हाल CHIP_CYPRESS:
	हाल CHIP_HEMLOCK:
	हाल CHIP_JUNIPER:
	हाल CHIP_REDWOOD:
	हाल CHIP_CEDAR:
	हाल CHIP_SUMO:
	हाल CHIP_SUMO2:
	हाल CHIP_PALM:
	हाल CHIP_ARUBA:
		disable_l0s = true;
		अवरोध;
	शेष:
		disable_l0s = false;
		अवरोध;
	पूर्ण

	अगर (rdev->flags & RADEON_IS_IGP)
		fusion_platक्रमm = true; /* XXX also dGPUs in a fusion प्रणाली */

	data = orig = RREG32_PIF_PHY0(PB0_PIF_PAIRING);
	अगर (fusion_platक्रमm)
		data &= ~MULTI_PIF;
	अन्यथा
		data |= MULTI_PIF;
	अगर (data != orig)
		WREG32_PIF_PHY0(PB0_PIF_PAIRING, data);

	data = orig = RREG32_PIF_PHY1(PB1_PIF_PAIRING);
	अगर (fusion_platक्रमm)
		data &= ~MULTI_PIF;
	अन्यथा
		data |= MULTI_PIF;
	अगर (data != orig)
		WREG32_PIF_PHY1(PB1_PIF_PAIRING, data);

	pcie_lc_cntl = pcie_lc_cntl_old = RREG32_PCIE_PORT(PCIE_LC_CNTL);
	pcie_lc_cntl &= ~(LC_L0S_INACTIVITY_MASK | LC_L1_INACTIVITY_MASK);
	अगर (!disable_l0s) अणु
		अगर (rdev->family >= CHIP_BARTS)
			pcie_lc_cntl |= LC_L0S_INACTIVITY(7);
		अन्यथा
			pcie_lc_cntl |= LC_L0S_INACTIVITY(3);
	पूर्ण

	अगर (!disable_l1) अणु
		अगर (rdev->family >= CHIP_BARTS)
			pcie_lc_cntl |= LC_L1_INACTIVITY(7);
		अन्यथा
			pcie_lc_cntl |= LC_L1_INACTIVITY(8);

		अगर (!disable_plloff_in_l1) अणु
			data = orig = RREG32_PIF_PHY0(PB0_PIF_PWRDOWN_0);
			data &= ~(PLL_POWER_STATE_IN_OFF_0_MASK | PLL_POWER_STATE_IN_TXS2_0_MASK);
			data |= PLL_POWER_STATE_IN_OFF_0(7) | PLL_POWER_STATE_IN_TXS2_0(7);
			अगर (data != orig)
				WREG32_PIF_PHY0(PB0_PIF_PWRDOWN_0, data);

			data = orig = RREG32_PIF_PHY0(PB0_PIF_PWRDOWN_1);
			data &= ~(PLL_POWER_STATE_IN_OFF_1_MASK | PLL_POWER_STATE_IN_TXS2_1_MASK);
			data |= PLL_POWER_STATE_IN_OFF_1(7) | PLL_POWER_STATE_IN_TXS2_1(7);
			अगर (data != orig)
				WREG32_PIF_PHY0(PB0_PIF_PWRDOWN_1, data);

			data = orig = RREG32_PIF_PHY1(PB1_PIF_PWRDOWN_0);
			data &= ~(PLL_POWER_STATE_IN_OFF_0_MASK | PLL_POWER_STATE_IN_TXS2_0_MASK);
			data |= PLL_POWER_STATE_IN_OFF_0(7) | PLL_POWER_STATE_IN_TXS2_0(7);
			अगर (data != orig)
				WREG32_PIF_PHY1(PB1_PIF_PWRDOWN_0, data);

			data = orig = RREG32_PIF_PHY1(PB1_PIF_PWRDOWN_1);
			data &= ~(PLL_POWER_STATE_IN_OFF_1_MASK | PLL_POWER_STATE_IN_TXS2_1_MASK);
			data |= PLL_POWER_STATE_IN_OFF_1(7) | PLL_POWER_STATE_IN_TXS2_1(7);
			अगर (data != orig)
				WREG32_PIF_PHY1(PB1_PIF_PWRDOWN_1, data);

			अगर (rdev->family >= CHIP_BARTS) अणु
				data = orig = RREG32_PIF_PHY0(PB0_PIF_PWRDOWN_0);
				data &= ~PLL_RAMP_UP_TIME_0_MASK;
				data |= PLL_RAMP_UP_TIME_0(4);
				अगर (data != orig)
					WREG32_PIF_PHY0(PB0_PIF_PWRDOWN_0, data);

				data = orig = RREG32_PIF_PHY0(PB0_PIF_PWRDOWN_1);
				data &= ~PLL_RAMP_UP_TIME_1_MASK;
				data |= PLL_RAMP_UP_TIME_1(4);
				अगर (data != orig)
					WREG32_PIF_PHY0(PB0_PIF_PWRDOWN_1, data);

				data = orig = RREG32_PIF_PHY1(PB1_PIF_PWRDOWN_0);
				data &= ~PLL_RAMP_UP_TIME_0_MASK;
				data |= PLL_RAMP_UP_TIME_0(4);
				अगर (data != orig)
					WREG32_PIF_PHY1(PB1_PIF_PWRDOWN_0, data);

				data = orig = RREG32_PIF_PHY1(PB1_PIF_PWRDOWN_1);
				data &= ~PLL_RAMP_UP_TIME_1_MASK;
				data |= PLL_RAMP_UP_TIME_1(4);
				अगर (data != orig)
					WREG32_PIF_PHY1(PB1_PIF_PWRDOWN_1, data);
			पूर्ण

			data = orig = RREG32_PCIE_PORT(PCIE_LC_LINK_WIDTH_CNTL);
			data &= ~LC_DYN_LANES_PWR_STATE_MASK;
			data |= LC_DYN_LANES_PWR_STATE(3);
			अगर (data != orig)
				WREG32_PCIE_PORT(PCIE_LC_LINK_WIDTH_CNTL, data);

			अगर (rdev->family >= CHIP_BARTS) अणु
				data = orig = RREG32_PIF_PHY0(PB0_PIF_CNTL);
				data &= ~LS2_EXIT_TIME_MASK;
				data |= LS2_EXIT_TIME(1);
				अगर (data != orig)
					WREG32_PIF_PHY0(PB0_PIF_CNTL, data);

				data = orig = RREG32_PIF_PHY1(PB1_PIF_CNTL);
				data &= ~LS2_EXIT_TIME_MASK;
				data |= LS2_EXIT_TIME(1);
				अगर (data != orig)
					WREG32_PIF_PHY1(PB1_PIF_CNTL, data);
			पूर्ण
		पूर्ण
	पूर्ण

	/* evergreen parts only */
	अगर (rdev->family < CHIP_BARTS)
		pcie_lc_cntl |= LC_PMI_TO_L1_DIS;

	अगर (pcie_lc_cntl != pcie_lc_cntl_old)
		WREG32_PCIE_PORT(PCIE_LC_CNTL, pcie_lc_cntl);
पूर्ण
