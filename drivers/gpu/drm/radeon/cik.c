<शैली गुरु>
/*
 * Copyright 2012 Advanced Micro Devices, Inc.
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

#समावेश <drm/drm_vblank.h>

#समावेश "atom.h"
#समावेश "evergreen.h"
#समावेश "cik_blit_shaders.h"
#समावेश "cik.h"
#समावेश "cikd.h"
#समावेश "clearstate_ci.h"
#समावेश "r600.h"
#समावेश "radeon.h"
#समावेश "radeon_asic.h"
#समावेश "radeon_audio.h"
#समावेश "radeon_ucode.h"
#समावेश "si.h"
#समावेश "vce.h"

#घोषणा SH_MEM_CONFIG_GFX_DEFAULT \
	ALIGNMENT_MODE(SH_MEM_ALIGNMENT_MODE_UNALIGNED)

MODULE_FIRMWARE("radeon/BONAIRE_pfp.bin");
MODULE_FIRMWARE("radeon/BONAIRE_me.bin");
MODULE_FIRMWARE("radeon/BONAIRE_ce.bin");
MODULE_FIRMWARE("radeon/BONAIRE_mec.bin");
MODULE_FIRMWARE("radeon/BONAIRE_mc.bin");
MODULE_FIRMWARE("radeon/BONAIRE_mc2.bin");
MODULE_FIRMWARE("radeon/BONAIRE_rlc.bin");
MODULE_FIRMWARE("radeon/BONAIRE_sdma.bin");
MODULE_FIRMWARE("radeon/BONAIRE_smc.bin");

MODULE_FIRMWARE("radeon/bonaire_pfp.bin");
MODULE_FIRMWARE("radeon/bonaire_me.bin");
MODULE_FIRMWARE("radeon/bonaire_ce.bin");
MODULE_FIRMWARE("radeon/bonaire_mec.bin");
MODULE_FIRMWARE("radeon/bonaire_mc.bin");
MODULE_FIRMWARE("radeon/bonaire_rlc.bin");
MODULE_FIRMWARE("radeon/bonaire_sdma.bin");
MODULE_FIRMWARE("radeon/bonaire_smc.bin");
MODULE_FIRMWARE("radeon/bonaire_k_smc.bin");

MODULE_FIRMWARE("radeon/HAWAII_pfp.bin");
MODULE_FIRMWARE("radeon/HAWAII_me.bin");
MODULE_FIRMWARE("radeon/HAWAII_ce.bin");
MODULE_FIRMWARE("radeon/HAWAII_mec.bin");
MODULE_FIRMWARE("radeon/HAWAII_mc.bin");
MODULE_FIRMWARE("radeon/HAWAII_mc2.bin");
MODULE_FIRMWARE("radeon/HAWAII_rlc.bin");
MODULE_FIRMWARE("radeon/HAWAII_sdma.bin");
MODULE_FIRMWARE("radeon/HAWAII_smc.bin");

MODULE_FIRMWARE("radeon/hawaii_pfp.bin");
MODULE_FIRMWARE("radeon/hawaii_me.bin");
MODULE_FIRMWARE("radeon/hawaii_ce.bin");
MODULE_FIRMWARE("radeon/hawaii_mec.bin");
MODULE_FIRMWARE("radeon/hawaii_mc.bin");
MODULE_FIRMWARE("radeon/hawaii_rlc.bin");
MODULE_FIRMWARE("radeon/hawaii_sdma.bin");
MODULE_FIRMWARE("radeon/hawaii_smc.bin");
MODULE_FIRMWARE("radeon/hawaii_k_smc.bin");

MODULE_FIRMWARE("radeon/KAVERI_pfp.bin");
MODULE_FIRMWARE("radeon/KAVERI_me.bin");
MODULE_FIRMWARE("radeon/KAVERI_ce.bin");
MODULE_FIRMWARE("radeon/KAVERI_mec.bin");
MODULE_FIRMWARE("radeon/KAVERI_rlc.bin");
MODULE_FIRMWARE("radeon/KAVERI_sdma.bin");

MODULE_FIRMWARE("radeon/kaveri_pfp.bin");
MODULE_FIRMWARE("radeon/kaveri_me.bin");
MODULE_FIRMWARE("radeon/kaveri_ce.bin");
MODULE_FIRMWARE("radeon/kaveri_mec.bin");
MODULE_FIRMWARE("radeon/kaveri_mec2.bin");
MODULE_FIRMWARE("radeon/kaveri_rlc.bin");
MODULE_FIRMWARE("radeon/kaveri_sdma.bin");

MODULE_FIRMWARE("radeon/KABINI_pfp.bin");
MODULE_FIRMWARE("radeon/KABINI_me.bin");
MODULE_FIRMWARE("radeon/KABINI_ce.bin");
MODULE_FIRMWARE("radeon/KABINI_mec.bin");
MODULE_FIRMWARE("radeon/KABINI_rlc.bin");
MODULE_FIRMWARE("radeon/KABINI_sdma.bin");

MODULE_FIRMWARE("radeon/kabini_pfp.bin");
MODULE_FIRMWARE("radeon/kabini_me.bin");
MODULE_FIRMWARE("radeon/kabini_ce.bin");
MODULE_FIRMWARE("radeon/kabini_mec.bin");
MODULE_FIRMWARE("radeon/kabini_rlc.bin");
MODULE_FIRMWARE("radeon/kabini_sdma.bin");

MODULE_FIRMWARE("radeon/MULLINS_pfp.bin");
MODULE_FIRMWARE("radeon/MULLINS_me.bin");
MODULE_FIRMWARE("radeon/MULLINS_ce.bin");
MODULE_FIRMWARE("radeon/MULLINS_mec.bin");
MODULE_FIRMWARE("radeon/MULLINS_rlc.bin");
MODULE_FIRMWARE("radeon/MULLINS_sdma.bin");

MODULE_FIRMWARE("radeon/mullins_pfp.bin");
MODULE_FIRMWARE("radeon/mullins_me.bin");
MODULE_FIRMWARE("radeon/mullins_ce.bin");
MODULE_FIRMWARE("radeon/mullins_mec.bin");
MODULE_FIRMWARE("radeon/mullins_rlc.bin");
MODULE_FIRMWARE("radeon/mullins_sdma.bin");

अटल u32 cik_get_cu_active_biपंचांगap(काष्ठा radeon_device *rdev, u32 se, u32 sh);
अटल व्योम cik_rlc_stop(काष्ठा radeon_device *rdev);
अटल व्योम cik_pcie_gen3_enable(काष्ठा radeon_device *rdev);
अटल व्योम cik_program_aspm(काष्ठा radeon_device *rdev);
अटल व्योम cik_init_pg(काष्ठा radeon_device *rdev);
अटल व्योम cik_init_cg(काष्ठा radeon_device *rdev);
अटल व्योम cik_fini_pg(काष्ठा radeon_device *rdev);
अटल व्योम cik_fini_cg(काष्ठा radeon_device *rdev);
अटल व्योम cik_enable_gui_idle_पूर्णांकerrupt(काष्ठा radeon_device *rdev,
					  bool enable);

/**
 * cik_get_allowed_info_रेजिस्टर - fetch the रेजिस्टर क्रम the info ioctl
 *
 * @rdev: radeon_device poपूर्णांकer
 * @reg: रेजिस्टर offset in bytes
 * @val: रेजिस्टर value
 *
 * Returns 0 क्रम success or -EINVAL क्रम an invalid रेजिस्टर
 *
 */
पूर्णांक cik_get_allowed_info_रेजिस्टर(काष्ठा radeon_device *rdev,
				  u32 reg, u32 *val)
अणु
	चयन (reg) अणु
	हाल GRBM_STATUS:
	हाल GRBM_STATUS2:
	हाल GRBM_STATUS_SE0:
	हाल GRBM_STATUS_SE1:
	हाल GRBM_STATUS_SE2:
	हाल GRBM_STATUS_SE3:
	हाल SRBM_STATUS:
	हाल SRBM_STATUS2:
	हाल (SDMA0_STATUS_REG + SDMA0_REGISTER_OFFSET):
	हाल (SDMA0_STATUS_REG + SDMA1_REGISTER_OFFSET):
	हाल UVD_STATUS:
	/* TODO VCE */
		*val = RREG32(reg);
		वापस 0;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

/*
 * Indirect रेजिस्टरs accessor
 */
u32 cik_didt_rreg(काष्ठा radeon_device *rdev, u32 reg)
अणु
	अचिन्हित दीर्घ flags;
	u32 r;

	spin_lock_irqsave(&rdev->didt_idx_lock, flags);
	WREG32(CIK_DIDT_IND_INDEX, (reg));
	r = RREG32(CIK_DIDT_IND_DATA);
	spin_unlock_irqrestore(&rdev->didt_idx_lock, flags);
	वापस r;
पूर्ण

व्योम cik_didt_wreg(काष्ठा radeon_device *rdev, u32 reg, u32 v)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&rdev->didt_idx_lock, flags);
	WREG32(CIK_DIDT_IND_INDEX, (reg));
	WREG32(CIK_DIDT_IND_DATA, (v));
	spin_unlock_irqrestore(&rdev->didt_idx_lock, flags);
पूर्ण

/* get temperature in millidegrees */
पूर्णांक ci_get_temp(काष्ठा radeon_device *rdev)
अणु
	u32 temp;
	पूर्णांक actual_temp = 0;

	temp = (RREG32_SMC(CG_MULT_THERMAL_STATUS) & CTF_TEMP_MASK) >>
		CTF_TEMP_SHIFT;

	अगर (temp & 0x200)
		actual_temp = 255;
	अन्यथा
		actual_temp = temp & 0x1ff;

	वापस actual_temp * 1000;
पूर्ण

/* get temperature in millidegrees */
पूर्णांक kv_get_temp(काष्ठा radeon_device *rdev)
अणु
	u32 temp;
	पूर्णांक actual_temp = 0;

	temp = RREG32_SMC(0xC0300E0C);

	अगर (temp)
		actual_temp = (temp / 8) - 49;
	अन्यथा
		actual_temp = 0;

	वापस actual_temp * 1000;
पूर्ण

/*
 * Indirect रेजिस्टरs accessor
 */
u32 cik_pciep_rreg(काष्ठा radeon_device *rdev, u32 reg)
अणु
	अचिन्हित दीर्घ flags;
	u32 r;

	spin_lock_irqsave(&rdev->pciep_idx_lock, flags);
	WREG32(PCIE_INDEX, reg);
	(व्योम)RREG32(PCIE_INDEX);
	r = RREG32(PCIE_DATA);
	spin_unlock_irqrestore(&rdev->pciep_idx_lock, flags);
	वापस r;
पूर्ण

व्योम cik_pciep_wreg(काष्ठा radeon_device *rdev, u32 reg, u32 v)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&rdev->pciep_idx_lock, flags);
	WREG32(PCIE_INDEX, reg);
	(व्योम)RREG32(PCIE_INDEX);
	WREG32(PCIE_DATA, v);
	(व्योम)RREG32(PCIE_DATA);
	spin_unlock_irqrestore(&rdev->pciep_idx_lock, flags);
पूर्ण

अटल स्थिर u32 spectre_rlc_save_restore_रेजिस्टर_list[] =
अणु
	(0x0e00 << 16) | (0xc12c >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xc140 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xc150 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xc15c >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xc168 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xc170 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xc178 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xc204 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xc2b4 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xc2b8 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xc2bc >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xc2c0 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x8228 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x829c >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x869c >> 2),
	0x00000000,
	(0x0600 << 16) | (0x98f4 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x98f8 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x9900 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xc260 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x90e8 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x3c000 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x3c00c >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x8c1c >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x9700 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xcd20 >> 2),
	0x00000000,
	(0x4e00 << 16) | (0xcd20 >> 2),
	0x00000000,
	(0x5e00 << 16) | (0xcd20 >> 2),
	0x00000000,
	(0x6e00 << 16) | (0xcd20 >> 2),
	0x00000000,
	(0x7e00 << 16) | (0xcd20 >> 2),
	0x00000000,
	(0x8e00 << 16) | (0xcd20 >> 2),
	0x00000000,
	(0x9e00 << 16) | (0xcd20 >> 2),
	0x00000000,
	(0xae00 << 16) | (0xcd20 >> 2),
	0x00000000,
	(0xbe00 << 16) | (0xcd20 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x89bc >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x8900 >> 2),
	0x00000000,
	0x3,
	(0x0e00 << 16) | (0xc130 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xc134 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xc1fc >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xc208 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xc264 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xc268 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xc26c >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xc270 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xc274 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xc278 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xc27c >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xc280 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xc284 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xc288 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xc28c >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xc290 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xc294 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xc298 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xc29c >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xc2a0 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xc2a4 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xc2a8 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xc2ac  >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xc2b0 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x301d0 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x30238 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x30250 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x30254 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x30258 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x3025c >> 2),
	0x00000000,
	(0x4e00 << 16) | (0xc900 >> 2),
	0x00000000,
	(0x5e00 << 16) | (0xc900 >> 2),
	0x00000000,
	(0x6e00 << 16) | (0xc900 >> 2),
	0x00000000,
	(0x7e00 << 16) | (0xc900 >> 2),
	0x00000000,
	(0x8e00 << 16) | (0xc900 >> 2),
	0x00000000,
	(0x9e00 << 16) | (0xc900 >> 2),
	0x00000000,
	(0xae00 << 16) | (0xc900 >> 2),
	0x00000000,
	(0xbe00 << 16) | (0xc900 >> 2),
	0x00000000,
	(0x4e00 << 16) | (0xc904 >> 2),
	0x00000000,
	(0x5e00 << 16) | (0xc904 >> 2),
	0x00000000,
	(0x6e00 << 16) | (0xc904 >> 2),
	0x00000000,
	(0x7e00 << 16) | (0xc904 >> 2),
	0x00000000,
	(0x8e00 << 16) | (0xc904 >> 2),
	0x00000000,
	(0x9e00 << 16) | (0xc904 >> 2),
	0x00000000,
	(0xae00 << 16) | (0xc904 >> 2),
	0x00000000,
	(0xbe00 << 16) | (0xc904 >> 2),
	0x00000000,
	(0x4e00 << 16) | (0xc908 >> 2),
	0x00000000,
	(0x5e00 << 16) | (0xc908 >> 2),
	0x00000000,
	(0x6e00 << 16) | (0xc908 >> 2),
	0x00000000,
	(0x7e00 << 16) | (0xc908 >> 2),
	0x00000000,
	(0x8e00 << 16) | (0xc908 >> 2),
	0x00000000,
	(0x9e00 << 16) | (0xc908 >> 2),
	0x00000000,
	(0xae00 << 16) | (0xc908 >> 2),
	0x00000000,
	(0xbe00 << 16) | (0xc908 >> 2),
	0x00000000,
	(0x4e00 << 16) | (0xc90c >> 2),
	0x00000000,
	(0x5e00 << 16) | (0xc90c >> 2),
	0x00000000,
	(0x6e00 << 16) | (0xc90c >> 2),
	0x00000000,
	(0x7e00 << 16) | (0xc90c >> 2),
	0x00000000,
	(0x8e00 << 16) | (0xc90c >> 2),
	0x00000000,
	(0x9e00 << 16) | (0xc90c >> 2),
	0x00000000,
	(0xae00 << 16) | (0xc90c >> 2),
	0x00000000,
	(0xbe00 << 16) | (0xc90c >> 2),
	0x00000000,
	(0x4e00 << 16) | (0xc910 >> 2),
	0x00000000,
	(0x5e00 << 16) | (0xc910 >> 2),
	0x00000000,
	(0x6e00 << 16) | (0xc910 >> 2),
	0x00000000,
	(0x7e00 << 16) | (0xc910 >> 2),
	0x00000000,
	(0x8e00 << 16) | (0xc910 >> 2),
	0x00000000,
	(0x9e00 << 16) | (0xc910 >> 2),
	0x00000000,
	(0xae00 << 16) | (0xc910 >> 2),
	0x00000000,
	(0xbe00 << 16) | (0xc910 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xc99c >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x9834 >> 2),
	0x00000000,
	(0x0000 << 16) | (0x30f00 >> 2),
	0x00000000,
	(0x0001 << 16) | (0x30f00 >> 2),
	0x00000000,
	(0x0000 << 16) | (0x30f04 >> 2),
	0x00000000,
	(0x0001 << 16) | (0x30f04 >> 2),
	0x00000000,
	(0x0000 << 16) | (0x30f08 >> 2),
	0x00000000,
	(0x0001 << 16) | (0x30f08 >> 2),
	0x00000000,
	(0x0000 << 16) | (0x30f0c >> 2),
	0x00000000,
	(0x0001 << 16) | (0x30f0c >> 2),
	0x00000000,
	(0x0600 << 16) | (0x9b7c >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x8a14 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x8a18 >> 2),
	0x00000000,
	(0x0600 << 16) | (0x30a00 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x8bf0 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x8bcc >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x8b24 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x30a04 >> 2),
	0x00000000,
	(0x0600 << 16) | (0x30a10 >> 2),
	0x00000000,
	(0x0600 << 16) | (0x30a14 >> 2),
	0x00000000,
	(0x0600 << 16) | (0x30a18 >> 2),
	0x00000000,
	(0x0600 << 16) | (0x30a2c >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xc700 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xc704 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xc708 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xc768 >> 2),
	0x00000000,
	(0x0400 << 16) | (0xc770 >> 2),
	0x00000000,
	(0x0400 << 16) | (0xc774 >> 2),
	0x00000000,
	(0x0400 << 16) | (0xc778 >> 2),
	0x00000000,
	(0x0400 << 16) | (0xc77c >> 2),
	0x00000000,
	(0x0400 << 16) | (0xc780 >> 2),
	0x00000000,
	(0x0400 << 16) | (0xc784 >> 2),
	0x00000000,
	(0x0400 << 16) | (0xc788 >> 2),
	0x00000000,
	(0x0400 << 16) | (0xc78c >> 2),
	0x00000000,
	(0x0400 << 16) | (0xc798 >> 2),
	0x00000000,
	(0x0400 << 16) | (0xc79c >> 2),
	0x00000000,
	(0x0400 << 16) | (0xc7a0 >> 2),
	0x00000000,
	(0x0400 << 16) | (0xc7a4 >> 2),
	0x00000000,
	(0x0400 << 16) | (0xc7a8 >> 2),
	0x00000000,
	(0x0400 << 16) | (0xc7ac >> 2),
	0x00000000,
	(0x0400 << 16) | (0xc7b0 >> 2),
	0x00000000,
	(0x0400 << 16) | (0xc7b4 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x9100 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x3c010 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x92a8 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x92ac >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x92b4 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x92b8 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x92bc >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x92c0 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x92c4 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x92c8 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x92cc >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x92d0 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x8c00 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x8c04 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x8c20 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x8c38 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x8c3c >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xae00 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x9604 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xac08 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xac0c >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xac10 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xac14 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xac58 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xac68 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xac6c >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xac70 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xac74 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xac78 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xac7c >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xac80 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xac84 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xac88 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xac8c >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x970c >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x9714 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x9718 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x971c >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x31068 >> 2),
	0x00000000,
	(0x4e00 << 16) | (0x31068 >> 2),
	0x00000000,
	(0x5e00 << 16) | (0x31068 >> 2),
	0x00000000,
	(0x6e00 << 16) | (0x31068 >> 2),
	0x00000000,
	(0x7e00 << 16) | (0x31068 >> 2),
	0x00000000,
	(0x8e00 << 16) | (0x31068 >> 2),
	0x00000000,
	(0x9e00 << 16) | (0x31068 >> 2),
	0x00000000,
	(0xae00 << 16) | (0x31068 >> 2),
	0x00000000,
	(0xbe00 << 16) | (0x31068 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xcd10 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xcd14 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x88b0 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x88b4 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x88b8 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x88bc >> 2),
	0x00000000,
	(0x0400 << 16) | (0x89c0 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x88c4 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x88c8 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x88d0 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x88d4 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x88d8 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x8980 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x30938 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x3093c >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x30940 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x89a0 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x30900 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x30904 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x89b4 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x3c210 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x3c214 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x3c218 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x8904 >> 2),
	0x00000000,
	0x5,
	(0x0e00 << 16) | (0x8c28 >> 2),
	(0x0e00 << 16) | (0x8c2c >> 2),
	(0x0e00 << 16) | (0x8c30 >> 2),
	(0x0e00 << 16) | (0x8c34 >> 2),
	(0x0e00 << 16) | (0x9600 >> 2),
पूर्ण;

अटल स्थिर u32 kalindi_rlc_save_restore_रेजिस्टर_list[] =
अणु
	(0x0e00 << 16) | (0xc12c >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xc140 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xc150 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xc15c >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xc168 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xc170 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xc204 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xc2b4 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xc2b8 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xc2bc >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xc2c0 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x8228 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x829c >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x869c >> 2),
	0x00000000,
	(0x0600 << 16) | (0x98f4 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x98f8 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x9900 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xc260 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x90e8 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x3c000 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x3c00c >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x8c1c >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x9700 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xcd20 >> 2),
	0x00000000,
	(0x4e00 << 16) | (0xcd20 >> 2),
	0x00000000,
	(0x5e00 << 16) | (0xcd20 >> 2),
	0x00000000,
	(0x6e00 << 16) | (0xcd20 >> 2),
	0x00000000,
	(0x7e00 << 16) | (0xcd20 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x89bc >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x8900 >> 2),
	0x00000000,
	0x3,
	(0x0e00 << 16) | (0xc130 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xc134 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xc1fc >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xc208 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xc264 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xc268 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xc26c >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xc270 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xc274 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xc28c >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xc290 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xc294 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xc298 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xc2a0 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xc2a4 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xc2a8 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xc2ac >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x301d0 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x30238 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x30250 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x30254 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x30258 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x3025c >> 2),
	0x00000000,
	(0x4e00 << 16) | (0xc900 >> 2),
	0x00000000,
	(0x5e00 << 16) | (0xc900 >> 2),
	0x00000000,
	(0x6e00 << 16) | (0xc900 >> 2),
	0x00000000,
	(0x7e00 << 16) | (0xc900 >> 2),
	0x00000000,
	(0x4e00 << 16) | (0xc904 >> 2),
	0x00000000,
	(0x5e00 << 16) | (0xc904 >> 2),
	0x00000000,
	(0x6e00 << 16) | (0xc904 >> 2),
	0x00000000,
	(0x7e00 << 16) | (0xc904 >> 2),
	0x00000000,
	(0x4e00 << 16) | (0xc908 >> 2),
	0x00000000,
	(0x5e00 << 16) | (0xc908 >> 2),
	0x00000000,
	(0x6e00 << 16) | (0xc908 >> 2),
	0x00000000,
	(0x7e00 << 16) | (0xc908 >> 2),
	0x00000000,
	(0x4e00 << 16) | (0xc90c >> 2),
	0x00000000,
	(0x5e00 << 16) | (0xc90c >> 2),
	0x00000000,
	(0x6e00 << 16) | (0xc90c >> 2),
	0x00000000,
	(0x7e00 << 16) | (0xc90c >> 2),
	0x00000000,
	(0x4e00 << 16) | (0xc910 >> 2),
	0x00000000,
	(0x5e00 << 16) | (0xc910 >> 2),
	0x00000000,
	(0x6e00 << 16) | (0xc910 >> 2),
	0x00000000,
	(0x7e00 << 16) | (0xc910 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xc99c >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x9834 >> 2),
	0x00000000,
	(0x0000 << 16) | (0x30f00 >> 2),
	0x00000000,
	(0x0000 << 16) | (0x30f04 >> 2),
	0x00000000,
	(0x0000 << 16) | (0x30f08 >> 2),
	0x00000000,
	(0x0000 << 16) | (0x30f0c >> 2),
	0x00000000,
	(0x0600 << 16) | (0x9b7c >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x8a14 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x8a18 >> 2),
	0x00000000,
	(0x0600 << 16) | (0x30a00 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x8bf0 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x8bcc >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x8b24 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x30a04 >> 2),
	0x00000000,
	(0x0600 << 16) | (0x30a10 >> 2),
	0x00000000,
	(0x0600 << 16) | (0x30a14 >> 2),
	0x00000000,
	(0x0600 << 16) | (0x30a18 >> 2),
	0x00000000,
	(0x0600 << 16) | (0x30a2c >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xc700 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xc704 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xc708 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xc768 >> 2),
	0x00000000,
	(0x0400 << 16) | (0xc770 >> 2),
	0x00000000,
	(0x0400 << 16) | (0xc774 >> 2),
	0x00000000,
	(0x0400 << 16) | (0xc798 >> 2),
	0x00000000,
	(0x0400 << 16) | (0xc79c >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x9100 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x3c010 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x8c00 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x8c04 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x8c20 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x8c38 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x8c3c >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xae00 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x9604 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xac08 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xac0c >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xac10 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xac14 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xac58 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xac68 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xac6c >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xac70 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xac74 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xac78 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xac7c >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xac80 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xac84 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xac88 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xac8c >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x970c >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x9714 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x9718 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x971c >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x31068 >> 2),
	0x00000000,
	(0x4e00 << 16) | (0x31068 >> 2),
	0x00000000,
	(0x5e00 << 16) | (0x31068 >> 2),
	0x00000000,
	(0x6e00 << 16) | (0x31068 >> 2),
	0x00000000,
	(0x7e00 << 16) | (0x31068 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xcd10 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xcd14 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x88b0 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x88b4 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x88b8 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x88bc >> 2),
	0x00000000,
	(0x0400 << 16) | (0x89c0 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x88c4 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x88c8 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x88d0 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x88d4 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x88d8 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x8980 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x30938 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x3093c >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x30940 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x89a0 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x30900 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x30904 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x89b4 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x3e1fc >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x3c210 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x3c214 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x3c218 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x8904 >> 2),
	0x00000000,
	0x5,
	(0x0e00 << 16) | (0x8c28 >> 2),
	(0x0e00 << 16) | (0x8c2c >> 2),
	(0x0e00 << 16) | (0x8c30 >> 2),
	(0x0e00 << 16) | (0x8c34 >> 2),
	(0x0e00 << 16) | (0x9600 >> 2),
पूर्ण;

अटल स्थिर u32 bonaire_golden_spm_रेजिस्टरs[] =
अणु
	0x30800, 0xe0ffffff, 0xe0000000
पूर्ण;

अटल स्थिर u32 bonaire_golden_common_रेजिस्टरs[] =
अणु
	0xc770, 0xffffffff, 0x00000800,
	0xc774, 0xffffffff, 0x00000800,
	0xc798, 0xffffffff, 0x00007fbf,
	0xc79c, 0xffffffff, 0x00007faf
पूर्ण;

अटल स्थिर u32 bonaire_golden_रेजिस्टरs[] =
अणु
	0x3354, 0x00000333, 0x00000333,
	0x3350, 0x000c0fc0, 0x00040200,
	0x9a10, 0x00010000, 0x00058208,
	0x3c000, 0xffff1fff, 0x00140000,
	0x3c200, 0xfdfc0fff, 0x00000100,
	0x3c234, 0x40000000, 0x40000200,
	0x9830, 0xffffffff, 0x00000000,
	0x9834, 0xf00fffff, 0x00000400,
	0x9838, 0x0002021c, 0x00020200,
	0xc78, 0x00000080, 0x00000000,
	0x5bb0, 0x000000f0, 0x00000070,
	0x5bc0, 0xf0311fff, 0x80300000,
	0x98f8, 0x73773777, 0x12010001,
	0x350c, 0x00810000, 0x408af000,
	0x7030, 0x31000111, 0x00000011,
	0x2f48, 0x73773777, 0x12010001,
	0x220c, 0x00007fb6, 0x0021a1b1,
	0x2210, 0x00007fb6, 0x002021b1,
	0x2180, 0x00007fb6, 0x00002191,
	0x2218, 0x00007fb6, 0x002121b1,
	0x221c, 0x00007fb6, 0x002021b1,
	0x21dc, 0x00007fb6, 0x00002191,
	0x21e0, 0x00007fb6, 0x00002191,
	0x3628, 0x0000003f, 0x0000000a,
	0x362c, 0x0000003f, 0x0000000a,
	0x2ae4, 0x00073ffe, 0x000022a2,
	0x240c, 0x000007ff, 0x00000000,
	0x8a14, 0xf000003f, 0x00000007,
	0x8bf0, 0x00002001, 0x00000001,
	0x8b24, 0xffffffff, 0x00ffffff,
	0x30a04, 0x0000ff0f, 0x00000000,
	0x28a4c, 0x07ffffff, 0x06000000,
	0x4d8, 0x00000fff, 0x00000100,
	0x3e78, 0x00000001, 0x00000002,
	0x9100, 0x03000000, 0x0362c688,
	0x8c00, 0x000000ff, 0x00000001,
	0xe40, 0x00001fff, 0x00001fff,
	0x9060, 0x0000007f, 0x00000020,
	0x9508, 0x00010000, 0x00010000,
	0xac14, 0x000003ff, 0x000000f3,
	0xac0c, 0xffffffff, 0x00001032
पूर्ण;

अटल स्थिर u32 bonaire_mgcg_cgcg_init[] =
अणु
	0xc420, 0xffffffff, 0xfffffffc,
	0x30800, 0xffffffff, 0xe0000000,
	0x3c2a0, 0xffffffff, 0x00000100,
	0x3c208, 0xffffffff, 0x00000100,
	0x3c2c0, 0xffffffff, 0xc0000100,
	0x3c2c8, 0xffffffff, 0xc0000100,
	0x3c2c4, 0xffffffff, 0xc0000100,
	0x55e4, 0xffffffff, 0x00600100,
	0x3c280, 0xffffffff, 0x00000100,
	0x3c214, 0xffffffff, 0x06000100,
	0x3c220, 0xffffffff, 0x00000100,
	0x3c218, 0xffffffff, 0x06000100,
	0x3c204, 0xffffffff, 0x00000100,
	0x3c2e0, 0xffffffff, 0x00000100,
	0x3c224, 0xffffffff, 0x00000100,
	0x3c200, 0xffffffff, 0x00000100,
	0x3c230, 0xffffffff, 0x00000100,
	0x3c234, 0xffffffff, 0x00000100,
	0x3c250, 0xffffffff, 0x00000100,
	0x3c254, 0xffffffff, 0x00000100,
	0x3c258, 0xffffffff, 0x00000100,
	0x3c25c, 0xffffffff, 0x00000100,
	0x3c260, 0xffffffff, 0x00000100,
	0x3c27c, 0xffffffff, 0x00000100,
	0x3c278, 0xffffffff, 0x00000100,
	0x3c210, 0xffffffff, 0x06000100,
	0x3c290, 0xffffffff, 0x00000100,
	0x3c274, 0xffffffff, 0x00000100,
	0x3c2b4, 0xffffffff, 0x00000100,
	0x3c2b0, 0xffffffff, 0x00000100,
	0x3c270, 0xffffffff, 0x00000100,
	0x30800, 0xffffffff, 0xe0000000,
	0x3c020, 0xffffffff, 0x00010000,
	0x3c024, 0xffffffff, 0x00030002,
	0x3c028, 0xffffffff, 0x00040007,
	0x3c02c, 0xffffffff, 0x00060005,
	0x3c030, 0xffffffff, 0x00090008,
	0x3c034, 0xffffffff, 0x00010000,
	0x3c038, 0xffffffff, 0x00030002,
	0x3c03c, 0xffffffff, 0x00040007,
	0x3c040, 0xffffffff, 0x00060005,
	0x3c044, 0xffffffff, 0x00090008,
	0x3c048, 0xffffffff, 0x00010000,
	0x3c04c, 0xffffffff, 0x00030002,
	0x3c050, 0xffffffff, 0x00040007,
	0x3c054, 0xffffffff, 0x00060005,
	0x3c058, 0xffffffff, 0x00090008,
	0x3c05c, 0xffffffff, 0x00010000,
	0x3c060, 0xffffffff, 0x00030002,
	0x3c064, 0xffffffff, 0x00040007,
	0x3c068, 0xffffffff, 0x00060005,
	0x3c06c, 0xffffffff, 0x00090008,
	0x3c070, 0xffffffff, 0x00010000,
	0x3c074, 0xffffffff, 0x00030002,
	0x3c078, 0xffffffff, 0x00040007,
	0x3c07c, 0xffffffff, 0x00060005,
	0x3c080, 0xffffffff, 0x00090008,
	0x3c084, 0xffffffff, 0x00010000,
	0x3c088, 0xffffffff, 0x00030002,
	0x3c08c, 0xffffffff, 0x00040007,
	0x3c090, 0xffffffff, 0x00060005,
	0x3c094, 0xffffffff, 0x00090008,
	0x3c098, 0xffffffff, 0x00010000,
	0x3c09c, 0xffffffff, 0x00030002,
	0x3c0a0, 0xffffffff, 0x00040007,
	0x3c0a4, 0xffffffff, 0x00060005,
	0x3c0a8, 0xffffffff, 0x00090008,
	0x3c000, 0xffffffff, 0x96e00200,
	0x8708, 0xffffffff, 0x00900100,
	0xc424, 0xffffffff, 0x0020003f,
	0x38, 0xffffffff, 0x0140001c,
	0x3c, 0x000f0000, 0x000f0000,
	0x220, 0xffffffff, 0xC060000C,
	0x224, 0xc0000fff, 0x00000100,
	0xf90, 0xffffffff, 0x00000100,
	0xf98, 0x00000101, 0x00000000,
	0x20a8, 0xffffffff, 0x00000104,
	0x55e4, 0xff000fff, 0x00000100,
	0x30cc, 0xc0000fff, 0x00000104,
	0xc1e4, 0x00000001, 0x00000001,
	0xd00c, 0xff000ff0, 0x00000100,
	0xd80c, 0xff000ff0, 0x00000100
पूर्ण;

अटल स्थिर u32 spectre_golden_spm_रेजिस्टरs[] =
अणु
	0x30800, 0xe0ffffff, 0xe0000000
पूर्ण;

अटल स्थिर u32 spectre_golden_common_रेजिस्टरs[] =
अणु
	0xc770, 0xffffffff, 0x00000800,
	0xc774, 0xffffffff, 0x00000800,
	0xc798, 0xffffffff, 0x00007fbf,
	0xc79c, 0xffffffff, 0x00007faf
पूर्ण;

अटल स्थिर u32 spectre_golden_रेजिस्टरs[] =
अणु
	0x3c000, 0xffff1fff, 0x96940200,
	0x3c00c, 0xffff0001, 0xff000000,
	0x3c200, 0xfffc0fff, 0x00000100,
	0x6ed8, 0x00010101, 0x00010000,
	0x9834, 0xf00fffff, 0x00000400,
	0x9838, 0xfffffffc, 0x00020200,
	0x5bb0, 0x000000f0, 0x00000070,
	0x5bc0, 0xf0311fff, 0x80300000,
	0x98f8, 0x73773777, 0x12010001,
	0x9b7c, 0x00ff0000, 0x00fc0000,
	0x2f48, 0x73773777, 0x12010001,
	0x8a14, 0xf000003f, 0x00000007,
	0x8b24, 0xffffffff, 0x00ffffff,
	0x28350, 0x3f3f3fff, 0x00000082,
	0x28354, 0x0000003f, 0x00000000,
	0x3e78, 0x00000001, 0x00000002,
	0x913c, 0xffff03df, 0x00000004,
	0xc768, 0x00000008, 0x00000008,
	0x8c00, 0x000008ff, 0x00000800,
	0x9508, 0x00010000, 0x00010000,
	0xac0c, 0xffffffff, 0x54763210,
	0x214f8, 0x01ff01ff, 0x00000002,
	0x21498, 0x007ff800, 0x00200000,
	0x2015c, 0xffffffff, 0x00000f40,
	0x30934, 0xffffffff, 0x00000001
पूर्ण;

अटल स्थिर u32 spectre_mgcg_cgcg_init[] =
अणु
	0xc420, 0xffffffff, 0xfffffffc,
	0x30800, 0xffffffff, 0xe0000000,
	0x3c2a0, 0xffffffff, 0x00000100,
	0x3c208, 0xffffffff, 0x00000100,
	0x3c2c0, 0xffffffff, 0x00000100,
	0x3c2c8, 0xffffffff, 0x00000100,
	0x3c2c4, 0xffffffff, 0x00000100,
	0x55e4, 0xffffffff, 0x00600100,
	0x3c280, 0xffffffff, 0x00000100,
	0x3c214, 0xffffffff, 0x06000100,
	0x3c220, 0xffffffff, 0x00000100,
	0x3c218, 0xffffffff, 0x06000100,
	0x3c204, 0xffffffff, 0x00000100,
	0x3c2e0, 0xffffffff, 0x00000100,
	0x3c224, 0xffffffff, 0x00000100,
	0x3c200, 0xffffffff, 0x00000100,
	0x3c230, 0xffffffff, 0x00000100,
	0x3c234, 0xffffffff, 0x00000100,
	0x3c250, 0xffffffff, 0x00000100,
	0x3c254, 0xffffffff, 0x00000100,
	0x3c258, 0xffffffff, 0x00000100,
	0x3c25c, 0xffffffff, 0x00000100,
	0x3c260, 0xffffffff, 0x00000100,
	0x3c27c, 0xffffffff, 0x00000100,
	0x3c278, 0xffffffff, 0x00000100,
	0x3c210, 0xffffffff, 0x06000100,
	0x3c290, 0xffffffff, 0x00000100,
	0x3c274, 0xffffffff, 0x00000100,
	0x3c2b4, 0xffffffff, 0x00000100,
	0x3c2b0, 0xffffffff, 0x00000100,
	0x3c270, 0xffffffff, 0x00000100,
	0x30800, 0xffffffff, 0xe0000000,
	0x3c020, 0xffffffff, 0x00010000,
	0x3c024, 0xffffffff, 0x00030002,
	0x3c028, 0xffffffff, 0x00040007,
	0x3c02c, 0xffffffff, 0x00060005,
	0x3c030, 0xffffffff, 0x00090008,
	0x3c034, 0xffffffff, 0x00010000,
	0x3c038, 0xffffffff, 0x00030002,
	0x3c03c, 0xffffffff, 0x00040007,
	0x3c040, 0xffffffff, 0x00060005,
	0x3c044, 0xffffffff, 0x00090008,
	0x3c048, 0xffffffff, 0x00010000,
	0x3c04c, 0xffffffff, 0x00030002,
	0x3c050, 0xffffffff, 0x00040007,
	0x3c054, 0xffffffff, 0x00060005,
	0x3c058, 0xffffffff, 0x00090008,
	0x3c05c, 0xffffffff, 0x00010000,
	0x3c060, 0xffffffff, 0x00030002,
	0x3c064, 0xffffffff, 0x00040007,
	0x3c068, 0xffffffff, 0x00060005,
	0x3c06c, 0xffffffff, 0x00090008,
	0x3c070, 0xffffffff, 0x00010000,
	0x3c074, 0xffffffff, 0x00030002,
	0x3c078, 0xffffffff, 0x00040007,
	0x3c07c, 0xffffffff, 0x00060005,
	0x3c080, 0xffffffff, 0x00090008,
	0x3c084, 0xffffffff, 0x00010000,
	0x3c088, 0xffffffff, 0x00030002,
	0x3c08c, 0xffffffff, 0x00040007,
	0x3c090, 0xffffffff, 0x00060005,
	0x3c094, 0xffffffff, 0x00090008,
	0x3c098, 0xffffffff, 0x00010000,
	0x3c09c, 0xffffffff, 0x00030002,
	0x3c0a0, 0xffffffff, 0x00040007,
	0x3c0a4, 0xffffffff, 0x00060005,
	0x3c0a8, 0xffffffff, 0x00090008,
	0x3c0ac, 0xffffffff, 0x00010000,
	0x3c0b0, 0xffffffff, 0x00030002,
	0x3c0b4, 0xffffffff, 0x00040007,
	0x3c0b8, 0xffffffff, 0x00060005,
	0x3c0bc, 0xffffffff, 0x00090008,
	0x3c000, 0xffffffff, 0x96e00200,
	0x8708, 0xffffffff, 0x00900100,
	0xc424, 0xffffffff, 0x0020003f,
	0x38, 0xffffffff, 0x0140001c,
	0x3c, 0x000f0000, 0x000f0000,
	0x220, 0xffffffff, 0xC060000C,
	0x224, 0xc0000fff, 0x00000100,
	0xf90, 0xffffffff, 0x00000100,
	0xf98, 0x00000101, 0x00000000,
	0x20a8, 0xffffffff, 0x00000104,
	0x55e4, 0xff000fff, 0x00000100,
	0x30cc, 0xc0000fff, 0x00000104,
	0xc1e4, 0x00000001, 0x00000001,
	0xd00c, 0xff000ff0, 0x00000100,
	0xd80c, 0xff000ff0, 0x00000100
पूर्ण;

अटल स्थिर u32 kalindi_golden_spm_रेजिस्टरs[] =
अणु
	0x30800, 0xe0ffffff, 0xe0000000
पूर्ण;

अटल स्थिर u32 kalindi_golden_common_रेजिस्टरs[] =
अणु
	0xc770, 0xffffffff, 0x00000800,
	0xc774, 0xffffffff, 0x00000800,
	0xc798, 0xffffffff, 0x00007fbf,
	0xc79c, 0xffffffff, 0x00007faf
पूर्ण;

अटल स्थिर u32 kalindi_golden_रेजिस्टरs[] =
अणु
	0x3c000, 0xffffdfff, 0x6e944040,
	0x55e4, 0xff607fff, 0xfc000100,
	0x3c220, 0xff000fff, 0x00000100,
	0x3c224, 0xff000fff, 0x00000100,
	0x3c200, 0xfffc0fff, 0x00000100,
	0x6ed8, 0x00010101, 0x00010000,
	0x9830, 0xffffffff, 0x00000000,
	0x9834, 0xf00fffff, 0x00000400,
	0x5bb0, 0x000000f0, 0x00000070,
	0x5bc0, 0xf0311fff, 0x80300000,
	0x98f8, 0x73773777, 0x12010001,
	0x98fc, 0xffffffff, 0x00000010,
	0x9b7c, 0x00ff0000, 0x00fc0000,
	0x8030, 0x00001f0f, 0x0000100a,
	0x2f48, 0x73773777, 0x12010001,
	0x2408, 0x000fffff, 0x000c007f,
	0x8a14, 0xf000003f, 0x00000007,
	0x8b24, 0x3fff3fff, 0x00ffcfff,
	0x30a04, 0x0000ff0f, 0x00000000,
	0x28a4c, 0x07ffffff, 0x06000000,
	0x4d8, 0x00000fff, 0x00000100,
	0x3e78, 0x00000001, 0x00000002,
	0xc768, 0x00000008, 0x00000008,
	0x8c00, 0x000000ff, 0x00000003,
	0x214f8, 0x01ff01ff, 0x00000002,
	0x21498, 0x007ff800, 0x00200000,
	0x2015c, 0xffffffff, 0x00000f40,
	0x88c4, 0x001f3ae3, 0x00000082,
	0x88d4, 0x0000001f, 0x00000010,
	0x30934, 0xffffffff, 0x00000000
पूर्ण;

अटल स्थिर u32 kalindi_mgcg_cgcg_init[] =
अणु
	0xc420, 0xffffffff, 0xfffffffc,
	0x30800, 0xffffffff, 0xe0000000,
	0x3c2a0, 0xffffffff, 0x00000100,
	0x3c208, 0xffffffff, 0x00000100,
	0x3c2c0, 0xffffffff, 0x00000100,
	0x3c2c8, 0xffffffff, 0x00000100,
	0x3c2c4, 0xffffffff, 0x00000100,
	0x55e4, 0xffffffff, 0x00600100,
	0x3c280, 0xffffffff, 0x00000100,
	0x3c214, 0xffffffff, 0x06000100,
	0x3c220, 0xffffffff, 0x00000100,
	0x3c218, 0xffffffff, 0x06000100,
	0x3c204, 0xffffffff, 0x00000100,
	0x3c2e0, 0xffffffff, 0x00000100,
	0x3c224, 0xffffffff, 0x00000100,
	0x3c200, 0xffffffff, 0x00000100,
	0x3c230, 0xffffffff, 0x00000100,
	0x3c234, 0xffffffff, 0x00000100,
	0x3c250, 0xffffffff, 0x00000100,
	0x3c254, 0xffffffff, 0x00000100,
	0x3c258, 0xffffffff, 0x00000100,
	0x3c25c, 0xffffffff, 0x00000100,
	0x3c260, 0xffffffff, 0x00000100,
	0x3c27c, 0xffffffff, 0x00000100,
	0x3c278, 0xffffffff, 0x00000100,
	0x3c210, 0xffffffff, 0x06000100,
	0x3c290, 0xffffffff, 0x00000100,
	0x3c274, 0xffffffff, 0x00000100,
	0x3c2b4, 0xffffffff, 0x00000100,
	0x3c2b0, 0xffffffff, 0x00000100,
	0x3c270, 0xffffffff, 0x00000100,
	0x30800, 0xffffffff, 0xe0000000,
	0x3c020, 0xffffffff, 0x00010000,
	0x3c024, 0xffffffff, 0x00030002,
	0x3c028, 0xffffffff, 0x00040007,
	0x3c02c, 0xffffffff, 0x00060005,
	0x3c030, 0xffffffff, 0x00090008,
	0x3c034, 0xffffffff, 0x00010000,
	0x3c038, 0xffffffff, 0x00030002,
	0x3c03c, 0xffffffff, 0x00040007,
	0x3c040, 0xffffffff, 0x00060005,
	0x3c044, 0xffffffff, 0x00090008,
	0x3c000, 0xffffffff, 0x96e00200,
	0x8708, 0xffffffff, 0x00900100,
	0xc424, 0xffffffff, 0x0020003f,
	0x38, 0xffffffff, 0x0140001c,
	0x3c, 0x000f0000, 0x000f0000,
	0x220, 0xffffffff, 0xC060000C,
	0x224, 0xc0000fff, 0x00000100,
	0x20a8, 0xffffffff, 0x00000104,
	0x55e4, 0xff000fff, 0x00000100,
	0x30cc, 0xc0000fff, 0x00000104,
	0xc1e4, 0x00000001, 0x00000001,
	0xd00c, 0xff000ff0, 0x00000100,
	0xd80c, 0xff000ff0, 0x00000100
पूर्ण;

अटल स्थिर u32 hawaii_golden_spm_रेजिस्टरs[] =
अणु
	0x30800, 0xe0ffffff, 0xe0000000
पूर्ण;

अटल स्थिर u32 hawaii_golden_common_रेजिस्टरs[] =
अणु
	0x30800, 0xffffffff, 0xe0000000,
	0x28350, 0xffffffff, 0x3a00161a,
	0x28354, 0xffffffff, 0x0000002e,
	0x9a10, 0xffffffff, 0x00018208,
	0x98f8, 0xffffffff, 0x12011003
पूर्ण;

अटल स्थिर u32 hawaii_golden_रेजिस्टरs[] =
अणु
	0x3354, 0x00000333, 0x00000333,
	0x9a10, 0x00010000, 0x00058208,
	0x9830, 0xffffffff, 0x00000000,
	0x9834, 0xf00fffff, 0x00000400,
	0x9838, 0x0002021c, 0x00020200,
	0xc78, 0x00000080, 0x00000000,
	0x5bb0, 0x000000f0, 0x00000070,
	0x5bc0, 0xf0311fff, 0x80300000,
	0x350c, 0x00810000, 0x408af000,
	0x7030, 0x31000111, 0x00000011,
	0x2f48, 0x73773777, 0x12010001,
	0x2120, 0x0000007f, 0x0000001b,
	0x21dc, 0x00007fb6, 0x00002191,
	0x3628, 0x0000003f, 0x0000000a,
	0x362c, 0x0000003f, 0x0000000a,
	0x2ae4, 0x00073ffe, 0x000022a2,
	0x240c, 0x000007ff, 0x00000000,
	0x8bf0, 0x00002001, 0x00000001,
	0x8b24, 0xffffffff, 0x00ffffff,
	0x30a04, 0x0000ff0f, 0x00000000,
	0x28a4c, 0x07ffffff, 0x06000000,
	0x3e78, 0x00000001, 0x00000002,
	0xc768, 0x00000008, 0x00000008,
	0xc770, 0x00000f00, 0x00000800,
	0xc774, 0x00000f00, 0x00000800,
	0xc798, 0x00ffffff, 0x00ff7fbf,
	0xc79c, 0x00ffffff, 0x00ff7faf,
	0x8c00, 0x000000ff, 0x00000800,
	0xe40, 0x00001fff, 0x00001fff,
	0x9060, 0x0000007f, 0x00000020,
	0x9508, 0x00010000, 0x00010000,
	0xae00, 0x00100000, 0x000ff07c,
	0xac14, 0x000003ff, 0x0000000f,
	0xac10, 0xffffffff, 0x7564fdec,
	0xac0c, 0xffffffff, 0x3120b9a8,
	0xac08, 0x20000000, 0x0f9c0000
पूर्ण;

अटल स्थिर u32 hawaii_mgcg_cgcg_init[] =
अणु
	0xc420, 0xffffffff, 0xfffffffd,
	0x30800, 0xffffffff, 0xe0000000,
	0x3c2a0, 0xffffffff, 0x00000100,
	0x3c208, 0xffffffff, 0x00000100,
	0x3c2c0, 0xffffffff, 0x00000100,
	0x3c2c8, 0xffffffff, 0x00000100,
	0x3c2c4, 0xffffffff, 0x00000100,
	0x55e4, 0xffffffff, 0x00200100,
	0x3c280, 0xffffffff, 0x00000100,
	0x3c214, 0xffffffff, 0x06000100,
	0x3c220, 0xffffffff, 0x00000100,
	0x3c218, 0xffffffff, 0x06000100,
	0x3c204, 0xffffffff, 0x00000100,
	0x3c2e0, 0xffffffff, 0x00000100,
	0x3c224, 0xffffffff, 0x00000100,
	0x3c200, 0xffffffff, 0x00000100,
	0x3c230, 0xffffffff, 0x00000100,
	0x3c234, 0xffffffff, 0x00000100,
	0x3c250, 0xffffffff, 0x00000100,
	0x3c254, 0xffffffff, 0x00000100,
	0x3c258, 0xffffffff, 0x00000100,
	0x3c25c, 0xffffffff, 0x00000100,
	0x3c260, 0xffffffff, 0x00000100,
	0x3c27c, 0xffffffff, 0x00000100,
	0x3c278, 0xffffffff, 0x00000100,
	0x3c210, 0xffffffff, 0x06000100,
	0x3c290, 0xffffffff, 0x00000100,
	0x3c274, 0xffffffff, 0x00000100,
	0x3c2b4, 0xffffffff, 0x00000100,
	0x3c2b0, 0xffffffff, 0x00000100,
	0x3c270, 0xffffffff, 0x00000100,
	0x30800, 0xffffffff, 0xe0000000,
	0x3c020, 0xffffffff, 0x00010000,
	0x3c024, 0xffffffff, 0x00030002,
	0x3c028, 0xffffffff, 0x00040007,
	0x3c02c, 0xffffffff, 0x00060005,
	0x3c030, 0xffffffff, 0x00090008,
	0x3c034, 0xffffffff, 0x00010000,
	0x3c038, 0xffffffff, 0x00030002,
	0x3c03c, 0xffffffff, 0x00040007,
	0x3c040, 0xffffffff, 0x00060005,
	0x3c044, 0xffffffff, 0x00090008,
	0x3c048, 0xffffffff, 0x00010000,
	0x3c04c, 0xffffffff, 0x00030002,
	0x3c050, 0xffffffff, 0x00040007,
	0x3c054, 0xffffffff, 0x00060005,
	0x3c058, 0xffffffff, 0x00090008,
	0x3c05c, 0xffffffff, 0x00010000,
	0x3c060, 0xffffffff, 0x00030002,
	0x3c064, 0xffffffff, 0x00040007,
	0x3c068, 0xffffffff, 0x00060005,
	0x3c06c, 0xffffffff, 0x00090008,
	0x3c070, 0xffffffff, 0x00010000,
	0x3c074, 0xffffffff, 0x00030002,
	0x3c078, 0xffffffff, 0x00040007,
	0x3c07c, 0xffffffff, 0x00060005,
	0x3c080, 0xffffffff, 0x00090008,
	0x3c084, 0xffffffff, 0x00010000,
	0x3c088, 0xffffffff, 0x00030002,
	0x3c08c, 0xffffffff, 0x00040007,
	0x3c090, 0xffffffff, 0x00060005,
	0x3c094, 0xffffffff, 0x00090008,
	0x3c098, 0xffffffff, 0x00010000,
	0x3c09c, 0xffffffff, 0x00030002,
	0x3c0a0, 0xffffffff, 0x00040007,
	0x3c0a4, 0xffffffff, 0x00060005,
	0x3c0a8, 0xffffffff, 0x00090008,
	0x3c0ac, 0xffffffff, 0x00010000,
	0x3c0b0, 0xffffffff, 0x00030002,
	0x3c0b4, 0xffffffff, 0x00040007,
	0x3c0b8, 0xffffffff, 0x00060005,
	0x3c0bc, 0xffffffff, 0x00090008,
	0x3c0c0, 0xffffffff, 0x00010000,
	0x3c0c4, 0xffffffff, 0x00030002,
	0x3c0c8, 0xffffffff, 0x00040007,
	0x3c0cc, 0xffffffff, 0x00060005,
	0x3c0d0, 0xffffffff, 0x00090008,
	0x3c0d4, 0xffffffff, 0x00010000,
	0x3c0d8, 0xffffffff, 0x00030002,
	0x3c0dc, 0xffffffff, 0x00040007,
	0x3c0e0, 0xffffffff, 0x00060005,
	0x3c0e4, 0xffffffff, 0x00090008,
	0x3c0e8, 0xffffffff, 0x00010000,
	0x3c0ec, 0xffffffff, 0x00030002,
	0x3c0f0, 0xffffffff, 0x00040007,
	0x3c0f4, 0xffffffff, 0x00060005,
	0x3c0f8, 0xffffffff, 0x00090008,
	0xc318, 0xffffffff, 0x00020200,
	0x3350, 0xffffffff, 0x00000200,
	0x15c0, 0xffffffff, 0x00000400,
	0x55e8, 0xffffffff, 0x00000000,
	0x2f50, 0xffffffff, 0x00000902,
	0x3c000, 0xffffffff, 0x96940200,
	0x8708, 0xffffffff, 0x00900100,
	0xc424, 0xffffffff, 0x0020003f,
	0x38, 0xffffffff, 0x0140001c,
	0x3c, 0x000f0000, 0x000f0000,
	0x220, 0xffffffff, 0xc060000c,
	0x224, 0xc0000fff, 0x00000100,
	0xf90, 0xffffffff, 0x00000100,
	0xf98, 0x00000101, 0x00000000,
	0x20a8, 0xffffffff, 0x00000104,
	0x55e4, 0xff000fff, 0x00000100,
	0x30cc, 0xc0000fff, 0x00000104,
	0xc1e4, 0x00000001, 0x00000001,
	0xd00c, 0xff000ff0, 0x00000100,
	0xd80c, 0xff000ff0, 0x00000100
पूर्ण;

अटल स्थिर u32 godavari_golden_रेजिस्टरs[] =
अणु
	0x55e4, 0xff607fff, 0xfc000100,
	0x6ed8, 0x00010101, 0x00010000,
	0x9830, 0xffffffff, 0x00000000,
	0x98302, 0xf00fffff, 0x00000400,
	0x6130, 0xffffffff, 0x00010000,
	0x5bb0, 0x000000f0, 0x00000070,
	0x5bc0, 0xf0311fff, 0x80300000,
	0x98f8, 0x73773777, 0x12010001,
	0x98fc, 0xffffffff, 0x00000010,
	0x8030, 0x00001f0f, 0x0000100a,
	0x2f48, 0x73773777, 0x12010001,
	0x2408, 0x000fffff, 0x000c007f,
	0x8a14, 0xf000003f, 0x00000007,
	0x8b24, 0xffffffff, 0x00ff0fff,
	0x30a04, 0x0000ff0f, 0x00000000,
	0x28a4c, 0x07ffffff, 0x06000000,
	0x4d8, 0x00000fff, 0x00000100,
	0xd014, 0x00010000, 0x00810001,
	0xd814, 0x00010000, 0x00810001,
	0x3e78, 0x00000001, 0x00000002,
	0xc768, 0x00000008, 0x00000008,
	0xc770, 0x00000f00, 0x00000800,
	0xc774, 0x00000f00, 0x00000800,
	0xc798, 0x00ffffff, 0x00ff7fbf,
	0xc79c, 0x00ffffff, 0x00ff7faf,
	0x8c00, 0x000000ff, 0x00000001,
	0x214f8, 0x01ff01ff, 0x00000002,
	0x21498, 0x007ff800, 0x00200000,
	0x2015c, 0xffffffff, 0x00000f40,
	0x88c4, 0x001f3ae3, 0x00000082,
	0x88d4, 0x0000001f, 0x00000010,
	0x30934, 0xffffffff, 0x00000000
पूर्ण;


अटल व्योम cik_init_golden_रेजिस्टरs(काष्ठा radeon_device *rdev)
अणु
	चयन (rdev->family) अणु
	हाल CHIP_BONAIRE:
		radeon_program_रेजिस्टर_sequence(rdev,
						 bonaire_mgcg_cgcg_init,
						 (स्थिर u32)ARRAY_SIZE(bonaire_mgcg_cgcg_init));
		radeon_program_रेजिस्टर_sequence(rdev,
						 bonaire_golden_रेजिस्टरs,
						 (स्थिर u32)ARRAY_SIZE(bonaire_golden_रेजिस्टरs));
		radeon_program_रेजिस्टर_sequence(rdev,
						 bonaire_golden_common_रेजिस्टरs,
						 (स्थिर u32)ARRAY_SIZE(bonaire_golden_common_रेजिस्टरs));
		radeon_program_रेजिस्टर_sequence(rdev,
						 bonaire_golden_spm_रेजिस्टरs,
						 (स्थिर u32)ARRAY_SIZE(bonaire_golden_spm_रेजिस्टरs));
		अवरोध;
	हाल CHIP_KABINI:
		radeon_program_रेजिस्टर_sequence(rdev,
						 kalindi_mgcg_cgcg_init,
						 (स्थिर u32)ARRAY_SIZE(kalindi_mgcg_cgcg_init));
		radeon_program_रेजिस्टर_sequence(rdev,
						 kalindi_golden_रेजिस्टरs,
						 (स्थिर u32)ARRAY_SIZE(kalindi_golden_रेजिस्टरs));
		radeon_program_रेजिस्टर_sequence(rdev,
						 kalindi_golden_common_रेजिस्टरs,
						 (स्थिर u32)ARRAY_SIZE(kalindi_golden_common_रेजिस्टरs));
		radeon_program_रेजिस्टर_sequence(rdev,
						 kalindi_golden_spm_रेजिस्टरs,
						 (स्थिर u32)ARRAY_SIZE(kalindi_golden_spm_रेजिस्टरs));
		अवरोध;
	हाल CHIP_MULLINS:
		radeon_program_रेजिस्टर_sequence(rdev,
						 kalindi_mgcg_cgcg_init,
						 (स्थिर u32)ARRAY_SIZE(kalindi_mgcg_cgcg_init));
		radeon_program_रेजिस्टर_sequence(rdev,
						 godavari_golden_रेजिस्टरs,
						 (स्थिर u32)ARRAY_SIZE(godavari_golden_रेजिस्टरs));
		radeon_program_रेजिस्टर_sequence(rdev,
						 kalindi_golden_common_रेजिस्टरs,
						 (स्थिर u32)ARRAY_SIZE(kalindi_golden_common_रेजिस्टरs));
		radeon_program_रेजिस्टर_sequence(rdev,
						 kalindi_golden_spm_रेजिस्टरs,
						 (स्थिर u32)ARRAY_SIZE(kalindi_golden_spm_रेजिस्टरs));
		अवरोध;
	हाल CHIP_KAVERI:
		radeon_program_रेजिस्टर_sequence(rdev,
						 spectre_mgcg_cgcg_init,
						 (स्थिर u32)ARRAY_SIZE(spectre_mgcg_cgcg_init));
		radeon_program_रेजिस्टर_sequence(rdev,
						 spectre_golden_रेजिस्टरs,
						 (स्थिर u32)ARRAY_SIZE(spectre_golden_रेजिस्टरs));
		radeon_program_रेजिस्टर_sequence(rdev,
						 spectre_golden_common_रेजिस्टरs,
						 (स्थिर u32)ARRAY_SIZE(spectre_golden_common_रेजिस्टरs));
		radeon_program_रेजिस्टर_sequence(rdev,
						 spectre_golden_spm_रेजिस्टरs,
						 (स्थिर u32)ARRAY_SIZE(spectre_golden_spm_रेजिस्टरs));
		अवरोध;
	हाल CHIP_HAWAII:
		radeon_program_रेजिस्टर_sequence(rdev,
						 hawaii_mgcg_cgcg_init,
						 (स्थिर u32)ARRAY_SIZE(hawaii_mgcg_cgcg_init));
		radeon_program_रेजिस्टर_sequence(rdev,
						 hawaii_golden_रेजिस्टरs,
						 (स्थिर u32)ARRAY_SIZE(hawaii_golden_रेजिस्टरs));
		radeon_program_रेजिस्टर_sequence(rdev,
						 hawaii_golden_common_रेजिस्टरs,
						 (स्थिर u32)ARRAY_SIZE(hawaii_golden_common_रेजिस्टरs));
		radeon_program_रेजिस्टर_sequence(rdev,
						 hawaii_golden_spm_रेजिस्टरs,
						 (स्थिर u32)ARRAY_SIZE(hawaii_golden_spm_रेजिस्टरs));
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

/**
 * cik_get_xclk - get the xclk
 *
 * @rdev: radeon_device poपूर्णांकer
 *
 * Returns the reference घड़ी used by the gfx engine
 * (CIK).
 */
u32 cik_get_xclk(काष्ठा radeon_device *rdev)
अणु
	u32 reference_घड़ी = rdev->घड़ी.spll.reference_freq;

	अगर (rdev->flags & RADEON_IS_IGP) अणु
		अगर (RREG32_SMC(GENERAL_PWRMGT) & GPU_COUNTER_CLK)
			वापस reference_घड़ी / 2;
	पूर्ण अन्यथा अणु
		अगर (RREG32_SMC(CG_CLKPIN_CNTL) & XTALIN_DIVIDE)
			वापस reference_घड़ी / 4;
	पूर्ण
	वापस reference_घड़ी;
पूर्ण

/**
 * cik_mm_rकरोorbell - पढ़ो a करोorbell dword
 *
 * @rdev: radeon_device poपूर्णांकer
 * @index: करोorbell index
 *
 * Returns the value in the करोorbell aperture at the
 * requested करोorbell index (CIK).
 */
u32 cik_mm_rकरोorbell(काष्ठा radeon_device *rdev, u32 index)
अणु
	अगर (index < rdev->करोorbell.num_करोorbells) अणु
		वापस पढ़ोl(rdev->करोorbell.ptr + index);
	पूर्ण अन्यथा अणु
		DRM_ERROR("reading beyond doorbell aperture: 0x%08x!\n", index);
		वापस 0;
	पूर्ण
पूर्ण

/**
 * cik_mm_wकरोorbell - ग_लिखो a करोorbell dword
 *
 * @rdev: radeon_device poपूर्णांकer
 * @index: करोorbell index
 * @v: value to ग_लिखो
 *
 * Writes @v to the करोorbell aperture at the
 * requested करोorbell index (CIK).
 */
व्योम cik_mm_wकरोorbell(काष्ठा radeon_device *rdev, u32 index, u32 v)
अणु
	अगर (index < rdev->करोorbell.num_करोorbells) अणु
		ग_लिखोl(v, rdev->करोorbell.ptr + index);
	पूर्ण अन्यथा अणु
		DRM_ERROR("writing beyond doorbell aperture: 0x%08x!\n", index);
	पूर्ण
पूर्ण

#घोषणा BONAIRE_IO_MC_REGS_SIZE 36

अटल स्थिर u32 bonaire_io_mc_regs[BONAIRE_IO_MC_REGS_SIZE][2] =
अणु
	अणु0x00000070, 0x04400000पूर्ण,
	अणु0x00000071, 0x80c01803पूर्ण,
	अणु0x00000072, 0x00004004पूर्ण,
	अणु0x00000073, 0x00000100पूर्ण,
	अणु0x00000074, 0x00ff0000पूर्ण,
	अणु0x00000075, 0x34000000पूर्ण,
	अणु0x00000076, 0x08000014पूर्ण,
	अणु0x00000077, 0x00cc08ecपूर्ण,
	अणु0x00000078, 0x00000400पूर्ण,
	अणु0x00000079, 0x00000000पूर्ण,
	अणु0x0000007a, 0x04090000पूर्ण,
	अणु0x0000007c, 0x00000000पूर्ण,
	अणु0x0000007e, 0x4408a8e8पूर्ण,
	अणु0x0000007f, 0x00000304पूर्ण,
	अणु0x00000080, 0x00000000पूर्ण,
	अणु0x00000082, 0x00000001पूर्ण,
	अणु0x00000083, 0x00000002पूर्ण,
	अणु0x00000084, 0xf3e4f400पूर्ण,
	अणु0x00000085, 0x052024e3पूर्ण,
	अणु0x00000087, 0x00000000पूर्ण,
	अणु0x00000088, 0x01000000पूर्ण,
	अणु0x0000008a, 0x1c0a0000पूर्ण,
	अणु0x0000008b, 0xff010000पूर्ण,
	अणु0x0000008d, 0xffffefffपूर्ण,
	अणु0x0000008e, 0xfff3efffपूर्ण,
	अणु0x0000008f, 0xfff3efbfपूर्ण,
	अणु0x00000092, 0xf7ffffffपूर्ण,
	अणु0x00000093, 0xffffff7fपूर्ण,
	अणु0x00000095, 0x00101101पूर्ण,
	अणु0x00000096, 0x00000fffपूर्ण,
	अणु0x00000097, 0x00116fffपूर्ण,
	अणु0x00000098, 0x60010000पूर्ण,
	अणु0x00000099, 0x10010000पूर्ण,
	अणु0x0000009a, 0x00006000पूर्ण,
	अणु0x0000009b, 0x00001000पूर्ण,
	अणु0x0000009f, 0x00b48000पूर्ण
पूर्ण;

#घोषणा HAWAII_IO_MC_REGS_SIZE 22

अटल स्थिर u32 hawaii_io_mc_regs[HAWAII_IO_MC_REGS_SIZE][2] =
अणु
	अणु0x0000007d, 0x40000000पूर्ण,
	अणु0x0000007e, 0x40180304पूर्ण,
	अणु0x0000007f, 0x0000ff00पूर्ण,
	अणु0x00000081, 0x00000000पूर्ण,
	अणु0x00000083, 0x00000800पूर्ण,
	अणु0x00000086, 0x00000000पूर्ण,
	अणु0x00000087, 0x00000100पूर्ण,
	अणु0x00000088, 0x00020100पूर्ण,
	अणु0x00000089, 0x00000000पूर्ण,
	अणु0x0000008b, 0x00040000पूर्ण,
	अणु0x0000008c, 0x00000100पूर्ण,
	अणु0x0000008e, 0xff010000पूर्ण,
	अणु0x00000090, 0xffffefffपूर्ण,
	अणु0x00000091, 0xfff3efffपूर्ण,
	अणु0x00000092, 0xfff3efbfपूर्ण,
	अणु0x00000093, 0xf7ffffffपूर्ण,
	अणु0x00000094, 0xffffff7fपूर्ण,
	अणु0x00000095, 0x00000fffपूर्ण,
	अणु0x00000096, 0x00116fffपूर्ण,
	अणु0x00000097, 0x60010000पूर्ण,
	अणु0x00000098, 0x10010000पूर्ण,
	अणु0x0000009f, 0x00c79000पूर्ण
पूर्ण;


/**
 * cik_srbm_select - select specअगरic रेजिस्टर instances
 *
 * @rdev: radeon_device poपूर्णांकer
 * @me: selected ME (micro engine)
 * @pipe: pipe
 * @queue: queue
 * @vmid: VMID
 *
 * Switches the currently active रेजिस्टरs instances.  Some
 * रेजिस्टरs are instanced per VMID, others are instanced per
 * me/pipe/queue combination.
 */
अटल व्योम cik_srbm_select(काष्ठा radeon_device *rdev,
			    u32 me, u32 pipe, u32 queue, u32 vmid)
अणु
	u32 srbm_gfx_cntl = (PIPEID(pipe & 0x3) |
			     MEID(me & 0x3) |
			     VMID(vmid & 0xf) |
			     QUEUEID(queue & 0x7));
	WREG32(SRBM_GFX_CNTL, srbm_gfx_cntl);
पूर्ण

/* ucode loading */
/**
 * ci_mc_load_microcode - load MC ucode पूर्णांकo the hw
 *
 * @rdev: radeon_device poपूर्णांकer
 *
 * Load the GDDR MC ucode पूर्णांकo the hw (CIK).
 * Returns 0 on success, error on failure.
 */
पूर्णांक ci_mc_load_microcode(काष्ठा radeon_device *rdev)
अणु
	स्थिर __be32 *fw_data = शून्य;
	स्थिर __le32 *new_fw_data = शून्य;
	u32 running, पंचांगp;
	u32 *io_mc_regs = शून्य;
	स्थिर __le32 *new_io_mc_regs = शून्य;
	पूर्णांक i, regs_size, ucode_size;

	अगर (!rdev->mc_fw)
		वापस -EINVAL;

	अगर (rdev->new_fw) अणु
		स्थिर काष्ठा mc_firmware_header_v1_0 *hdr =
			(स्थिर काष्ठा mc_firmware_header_v1_0 *)rdev->mc_fw->data;

		radeon_ucode_prपूर्णांक_mc_hdr(&hdr->header);

		regs_size = le32_to_cpu(hdr->io_debug_size_bytes) / (4 * 2);
		new_io_mc_regs = (स्थिर __le32 *)
			(rdev->mc_fw->data + le32_to_cpu(hdr->io_debug_array_offset_bytes));
		ucode_size = le32_to_cpu(hdr->header.ucode_size_bytes) / 4;
		new_fw_data = (स्थिर __le32 *)
			(rdev->mc_fw->data + le32_to_cpu(hdr->header.ucode_array_offset_bytes));
	पूर्ण अन्यथा अणु
		ucode_size = rdev->mc_fw->size / 4;

		चयन (rdev->family) अणु
		हाल CHIP_BONAIRE:
			io_mc_regs = (u32 *)&bonaire_io_mc_regs;
			regs_size = BONAIRE_IO_MC_REGS_SIZE;
			अवरोध;
		हाल CHIP_HAWAII:
			io_mc_regs = (u32 *)&hawaii_io_mc_regs;
			regs_size = HAWAII_IO_MC_REGS_SIZE;
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण
		fw_data = (स्थिर __be32 *)rdev->mc_fw->data;
	पूर्ण

	running = RREG32(MC_SEQ_SUP_CNTL) & RUN_MASK;

	अगर (running == 0) अणु
		/* reset the engine and set to writable */
		WREG32(MC_SEQ_SUP_CNTL, 0x00000008);
		WREG32(MC_SEQ_SUP_CNTL, 0x00000010);

		/* load mc io regs */
		क्रम (i = 0; i < regs_size; i++) अणु
			अगर (rdev->new_fw) अणु
				WREG32(MC_SEQ_IO_DEBUG_INDEX, le32_to_cpup(new_io_mc_regs++));
				WREG32(MC_SEQ_IO_DEBUG_DATA, le32_to_cpup(new_io_mc_regs++));
			पूर्ण अन्यथा अणु
				WREG32(MC_SEQ_IO_DEBUG_INDEX, io_mc_regs[(i << 1)]);
				WREG32(MC_SEQ_IO_DEBUG_DATA, io_mc_regs[(i << 1) + 1]);
			पूर्ण
		पूर्ण

		पंचांगp = RREG32(MC_SEQ_MISC0);
		अगर ((rdev->pdev->device == 0x6649) && ((पंचांगp & 0xff00) == 0x5600)) अणु
			WREG32(MC_SEQ_IO_DEBUG_INDEX, 5);
			WREG32(MC_SEQ_IO_DEBUG_DATA, 0x00000023);
			WREG32(MC_SEQ_IO_DEBUG_INDEX, 9);
			WREG32(MC_SEQ_IO_DEBUG_DATA, 0x000001f0);
		पूर्ण

		/* load the MC ucode */
		क्रम (i = 0; i < ucode_size; i++) अणु
			अगर (rdev->new_fw)
				WREG32(MC_SEQ_SUP_PGM, le32_to_cpup(new_fw_data++));
			अन्यथा
				WREG32(MC_SEQ_SUP_PGM, be32_to_cpup(fw_data++));
		पूर्ण

		/* put the engine back पूर्णांकo the active state */
		WREG32(MC_SEQ_SUP_CNTL, 0x00000008);
		WREG32(MC_SEQ_SUP_CNTL, 0x00000004);
		WREG32(MC_SEQ_SUP_CNTL, 0x00000001);

		/* रुको क्रम training to complete */
		क्रम (i = 0; i < rdev->usec_समयout; i++) अणु
			अगर (RREG32(MC_SEQ_TRAIN_WAKEUP_CNTL) & TRAIN_DONE_D0)
				अवरोध;
			udelay(1);
		पूर्ण
		क्रम (i = 0; i < rdev->usec_समयout; i++) अणु
			अगर (RREG32(MC_SEQ_TRAIN_WAKEUP_CNTL) & TRAIN_DONE_D1)
				अवरोध;
			udelay(1);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/**
 * cik_init_microcode - load ucode images from disk
 *
 * @rdev: radeon_device poपूर्णांकer
 *
 * Use the firmware पूर्णांकerface to load the ucode images पूर्णांकo
 * the driver (not loaded पूर्णांकo hw).
 * Returns 0 on success, error on failure.
 */
अटल पूर्णांक cik_init_microcode(काष्ठा radeon_device *rdev)
अणु
	स्थिर अक्षर *chip_name;
	स्थिर अक्षर *new_chip_name;
	माप_प्रकार pfp_req_size, me_req_size, ce_req_size,
		mec_req_size, rlc_req_size, mc_req_size = 0,
		sdma_req_size, smc_req_size = 0, mc2_req_size = 0;
	अक्षर fw_name[30];
	पूर्णांक new_fw = 0;
	पूर्णांक err;
	पूर्णांक num_fw;
	bool new_smc = false;

	DRM_DEBUG("\n");

	चयन (rdev->family) अणु
	हाल CHIP_BONAIRE:
		chip_name = "BONAIRE";
		अगर ((rdev->pdev->revision == 0x80) ||
		    (rdev->pdev->revision == 0x81) ||
		    (rdev->pdev->device == 0x665f))
			new_smc = true;
		new_chip_name = "bonaire";
		pfp_req_size = CIK_PFP_UCODE_SIZE * 4;
		me_req_size = CIK_ME_UCODE_SIZE * 4;
		ce_req_size = CIK_CE_UCODE_SIZE * 4;
		mec_req_size = CIK_MEC_UCODE_SIZE * 4;
		rlc_req_size = BONAIRE_RLC_UCODE_SIZE * 4;
		mc_req_size = BONAIRE_MC_UCODE_SIZE * 4;
		mc2_req_size = BONAIRE_MC2_UCODE_SIZE * 4;
		sdma_req_size = CIK_SDMA_UCODE_SIZE * 4;
		smc_req_size = ALIGN(BONAIRE_SMC_UCODE_SIZE, 4);
		num_fw = 8;
		अवरोध;
	हाल CHIP_HAWAII:
		chip_name = "HAWAII";
		अगर (rdev->pdev->revision == 0x80)
			new_smc = true;
		new_chip_name = "hawaii";
		pfp_req_size = CIK_PFP_UCODE_SIZE * 4;
		me_req_size = CIK_ME_UCODE_SIZE * 4;
		ce_req_size = CIK_CE_UCODE_SIZE * 4;
		mec_req_size = CIK_MEC_UCODE_SIZE * 4;
		rlc_req_size = BONAIRE_RLC_UCODE_SIZE * 4;
		mc_req_size = HAWAII_MC_UCODE_SIZE * 4;
		mc2_req_size = HAWAII_MC2_UCODE_SIZE * 4;
		sdma_req_size = CIK_SDMA_UCODE_SIZE * 4;
		smc_req_size = ALIGN(HAWAII_SMC_UCODE_SIZE, 4);
		num_fw = 8;
		अवरोध;
	हाल CHIP_KAVERI:
		chip_name = "KAVERI";
		new_chip_name = "kaveri";
		pfp_req_size = CIK_PFP_UCODE_SIZE * 4;
		me_req_size = CIK_ME_UCODE_SIZE * 4;
		ce_req_size = CIK_CE_UCODE_SIZE * 4;
		mec_req_size = CIK_MEC_UCODE_SIZE * 4;
		rlc_req_size = KV_RLC_UCODE_SIZE * 4;
		sdma_req_size = CIK_SDMA_UCODE_SIZE * 4;
		num_fw = 7;
		अवरोध;
	हाल CHIP_KABINI:
		chip_name = "KABINI";
		new_chip_name = "kabini";
		pfp_req_size = CIK_PFP_UCODE_SIZE * 4;
		me_req_size = CIK_ME_UCODE_SIZE * 4;
		ce_req_size = CIK_CE_UCODE_SIZE * 4;
		mec_req_size = CIK_MEC_UCODE_SIZE * 4;
		rlc_req_size = KB_RLC_UCODE_SIZE * 4;
		sdma_req_size = CIK_SDMA_UCODE_SIZE * 4;
		num_fw = 6;
		अवरोध;
	हाल CHIP_MULLINS:
		chip_name = "MULLINS";
		new_chip_name = "mullins";
		pfp_req_size = CIK_PFP_UCODE_SIZE * 4;
		me_req_size = CIK_ME_UCODE_SIZE * 4;
		ce_req_size = CIK_CE_UCODE_SIZE * 4;
		mec_req_size = CIK_MEC_UCODE_SIZE * 4;
		rlc_req_size = ML_RLC_UCODE_SIZE * 4;
		sdma_req_size = CIK_SDMA_UCODE_SIZE * 4;
		num_fw = 6;
		अवरोध;
	शेष: BUG();
	पूर्ण

	DRM_INFO("Loading %s Microcode\n", new_chip_name);

	snम_लिखो(fw_name, माप(fw_name), "radeon/%s_pfp.bin", new_chip_name);
	err = request_firmware(&rdev->pfp_fw, fw_name, rdev->dev);
	अगर (err) अणु
		snम_लिखो(fw_name, माप(fw_name), "radeon/%s_pfp.bin", chip_name);
		err = request_firmware(&rdev->pfp_fw, fw_name, rdev->dev);
		अगर (err)
			जाओ out;
		अगर (rdev->pfp_fw->size != pfp_req_size) अणु
			pr_err("cik_cp: Bogus length %zu in firmware \"%s\"\n",
			       rdev->pfp_fw->size, fw_name);
			err = -EINVAL;
			जाओ out;
		पूर्ण
	पूर्ण अन्यथा अणु
		err = radeon_ucode_validate(rdev->pfp_fw);
		अगर (err) अणु
			pr_err("cik_fw: validation failed for firmware \"%s\"\n",
			       fw_name);
			जाओ out;
		पूर्ण अन्यथा अणु
			new_fw++;
		पूर्ण
	पूर्ण

	snम_लिखो(fw_name, माप(fw_name), "radeon/%s_me.bin", new_chip_name);
	err = request_firmware(&rdev->me_fw, fw_name, rdev->dev);
	अगर (err) अणु
		snम_लिखो(fw_name, माप(fw_name), "radeon/%s_me.bin", chip_name);
		err = request_firmware(&rdev->me_fw, fw_name, rdev->dev);
		अगर (err)
			जाओ out;
		अगर (rdev->me_fw->size != me_req_size) अणु
			pr_err("cik_cp: Bogus length %zu in firmware \"%s\"\n",
			       rdev->me_fw->size, fw_name);
			err = -EINVAL;
		पूर्ण
	पूर्ण अन्यथा अणु
		err = radeon_ucode_validate(rdev->me_fw);
		अगर (err) अणु
			pr_err("cik_fw: validation failed for firmware \"%s\"\n",
			       fw_name);
			जाओ out;
		पूर्ण अन्यथा अणु
			new_fw++;
		पूर्ण
	पूर्ण

	snम_लिखो(fw_name, माप(fw_name), "radeon/%s_ce.bin", new_chip_name);
	err = request_firmware(&rdev->ce_fw, fw_name, rdev->dev);
	अगर (err) अणु
		snम_लिखो(fw_name, माप(fw_name), "radeon/%s_ce.bin", chip_name);
		err = request_firmware(&rdev->ce_fw, fw_name, rdev->dev);
		अगर (err)
			जाओ out;
		अगर (rdev->ce_fw->size != ce_req_size) अणु
			pr_err("cik_cp: Bogus length %zu in firmware \"%s\"\n",
			       rdev->ce_fw->size, fw_name);
			err = -EINVAL;
		पूर्ण
	पूर्ण अन्यथा अणु
		err = radeon_ucode_validate(rdev->ce_fw);
		अगर (err) अणु
			pr_err("cik_fw: validation failed for firmware \"%s\"\n",
			       fw_name);
			जाओ out;
		पूर्ण अन्यथा अणु
			new_fw++;
		पूर्ण
	पूर्ण

	snम_लिखो(fw_name, माप(fw_name), "radeon/%s_mec.bin", new_chip_name);
	err = request_firmware(&rdev->mec_fw, fw_name, rdev->dev);
	अगर (err) अणु
		snम_लिखो(fw_name, माप(fw_name), "radeon/%s_mec.bin", chip_name);
		err = request_firmware(&rdev->mec_fw, fw_name, rdev->dev);
		अगर (err)
			जाओ out;
		अगर (rdev->mec_fw->size != mec_req_size) अणु
			pr_err("cik_cp: Bogus length %zu in firmware \"%s\"\n",
			       rdev->mec_fw->size, fw_name);
			err = -EINVAL;
		पूर्ण
	पूर्ण अन्यथा अणु
		err = radeon_ucode_validate(rdev->mec_fw);
		अगर (err) अणु
			pr_err("cik_fw: validation failed for firmware \"%s\"\n",
			       fw_name);
			जाओ out;
		पूर्ण अन्यथा अणु
			new_fw++;
		पूर्ण
	पूर्ण

	अगर (rdev->family == CHIP_KAVERI) अणु
		snम_लिखो(fw_name, माप(fw_name), "radeon/%s_mec2.bin", new_chip_name);
		err = request_firmware(&rdev->mec2_fw, fw_name, rdev->dev);
		अगर (err) अणु
			जाओ out;
		पूर्ण अन्यथा अणु
			err = radeon_ucode_validate(rdev->mec2_fw);
			अगर (err) अणु
				जाओ out;
			पूर्ण अन्यथा अणु
				new_fw++;
			पूर्ण
		पूर्ण
	पूर्ण

	snम_लिखो(fw_name, माप(fw_name), "radeon/%s_rlc.bin", new_chip_name);
	err = request_firmware(&rdev->rlc_fw, fw_name, rdev->dev);
	अगर (err) अणु
		snम_लिखो(fw_name, माप(fw_name), "radeon/%s_rlc.bin", chip_name);
		err = request_firmware(&rdev->rlc_fw, fw_name, rdev->dev);
		अगर (err)
			जाओ out;
		अगर (rdev->rlc_fw->size != rlc_req_size) अणु
			pr_err("cik_rlc: Bogus length %zu in firmware \"%s\"\n",
			       rdev->rlc_fw->size, fw_name);
			err = -EINVAL;
		पूर्ण
	पूर्ण अन्यथा अणु
		err = radeon_ucode_validate(rdev->rlc_fw);
		अगर (err) अणु
			pr_err("cik_fw: validation failed for firmware \"%s\"\n",
			       fw_name);
			जाओ out;
		पूर्ण अन्यथा अणु
			new_fw++;
		पूर्ण
	पूर्ण

	snम_लिखो(fw_name, माप(fw_name), "radeon/%s_sdma.bin", new_chip_name);
	err = request_firmware(&rdev->sdma_fw, fw_name, rdev->dev);
	अगर (err) अणु
		snम_लिखो(fw_name, माप(fw_name), "radeon/%s_sdma.bin", chip_name);
		err = request_firmware(&rdev->sdma_fw, fw_name, rdev->dev);
		अगर (err)
			जाओ out;
		अगर (rdev->sdma_fw->size != sdma_req_size) अणु
			pr_err("cik_sdma: Bogus length %zu in firmware \"%s\"\n",
			       rdev->sdma_fw->size, fw_name);
			err = -EINVAL;
		पूर्ण
	पूर्ण अन्यथा अणु
		err = radeon_ucode_validate(rdev->sdma_fw);
		अगर (err) अणु
			pr_err("cik_fw: validation failed for firmware \"%s\"\n",
			       fw_name);
			जाओ out;
		पूर्ण अन्यथा अणु
			new_fw++;
		पूर्ण
	पूर्ण

	/* No SMC, MC ucode on APUs */
	अगर (!(rdev->flags & RADEON_IS_IGP)) अणु
		snम_लिखो(fw_name, माप(fw_name), "radeon/%s_mc.bin", new_chip_name);
		err = request_firmware(&rdev->mc_fw, fw_name, rdev->dev);
		अगर (err) अणु
			snम_लिखो(fw_name, माप(fw_name), "radeon/%s_mc2.bin", chip_name);
			err = request_firmware(&rdev->mc_fw, fw_name, rdev->dev);
			अगर (err) अणु
				snम_लिखो(fw_name, माप(fw_name), "radeon/%s_mc.bin", chip_name);
				err = request_firmware(&rdev->mc_fw, fw_name, rdev->dev);
				अगर (err)
					जाओ out;
			पूर्ण
			अगर ((rdev->mc_fw->size != mc_req_size) &&
			    (rdev->mc_fw->size != mc2_req_size))अणु
				pr_err("cik_mc: Bogus length %zu in firmware \"%s\"\n",
				       rdev->mc_fw->size, fw_name);
				err = -EINVAL;
			पूर्ण
			DRM_INFO("%s: %zu bytes\n", fw_name, rdev->mc_fw->size);
		पूर्ण अन्यथा अणु
			err = radeon_ucode_validate(rdev->mc_fw);
			अगर (err) अणु
				pr_err("cik_fw: validation failed for firmware \"%s\"\n",
				       fw_name);
				जाओ out;
			पूर्ण अन्यथा अणु
				new_fw++;
			पूर्ण
		पूर्ण

		अगर (new_smc)
			snम_लिखो(fw_name, माप(fw_name), "radeon/%s_k_smc.bin", new_chip_name);
		अन्यथा
			snम_लिखो(fw_name, माप(fw_name), "radeon/%s_smc.bin", new_chip_name);
		err = request_firmware(&rdev->smc_fw, fw_name, rdev->dev);
		अगर (err) अणु
			snम_लिखो(fw_name, माप(fw_name), "radeon/%s_smc.bin", chip_name);
			err = request_firmware(&rdev->smc_fw, fw_name, rdev->dev);
			अगर (err) अणु
				pr_err("smc: error loading firmware \"%s\"\n",
				       fw_name);
				release_firmware(rdev->smc_fw);
				rdev->smc_fw = शून्य;
				err = 0;
			पूर्ण अन्यथा अगर (rdev->smc_fw->size != smc_req_size) अणु
				pr_err("cik_smc: Bogus length %zu in firmware \"%s\"\n",
				       rdev->smc_fw->size, fw_name);
				err = -EINVAL;
			पूर्ण
		पूर्ण अन्यथा अणु
			err = radeon_ucode_validate(rdev->smc_fw);
			अगर (err) अणु
				pr_err("cik_fw: validation failed for firmware \"%s\"\n",
				       fw_name);
				जाओ out;
			पूर्ण अन्यथा अणु
				new_fw++;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (new_fw == 0) अणु
		rdev->new_fw = false;
	पूर्ण अन्यथा अगर (new_fw < num_fw) अणु
		pr_err("ci_fw: mixing new and old firmware!\n");
		err = -EINVAL;
	पूर्ण अन्यथा अणु
		rdev->new_fw = true;
	पूर्ण

out:
	अगर (err) अणु
		अगर (err != -EINVAL)
			pr_err("cik_cp: Failed to load firmware \"%s\"\n",
			       fw_name);
		release_firmware(rdev->pfp_fw);
		rdev->pfp_fw = शून्य;
		release_firmware(rdev->me_fw);
		rdev->me_fw = शून्य;
		release_firmware(rdev->ce_fw);
		rdev->ce_fw = शून्य;
		release_firmware(rdev->mec_fw);
		rdev->mec_fw = शून्य;
		release_firmware(rdev->mec2_fw);
		rdev->mec2_fw = शून्य;
		release_firmware(rdev->rlc_fw);
		rdev->rlc_fw = शून्य;
		release_firmware(rdev->sdma_fw);
		rdev->sdma_fw = शून्य;
		release_firmware(rdev->mc_fw);
		rdev->mc_fw = शून्य;
		release_firmware(rdev->smc_fw);
		rdev->smc_fw = शून्य;
	पूर्ण
	वापस err;
पूर्ण

/*
 * Core functions
 */
/**
 * cik_tiling_mode_table_init - init the hw tiling table
 *
 * @rdev: radeon_device poपूर्णांकer
 *
 * Starting with SI, the tiling setup is करोne globally in a
 * set of 32 tiling modes.  Rather than selecting each set of
 * parameters per surface as on older asics, we just select
 * which index in the tiling table we want to use, and the
 * surface uses those parameters (CIK).
 */
अटल व्योम cik_tiling_mode_table_init(काष्ठा radeon_device *rdev)
अणु
	u32 *tile = rdev->config.cik.tile_mode_array;
	u32 *macrotile = rdev->config.cik.macrotile_mode_array;
	स्थिर u32 num_tile_mode_states =
			ARRAY_SIZE(rdev->config.cik.tile_mode_array);
	स्थिर u32 num_secondary_tile_mode_states =
			ARRAY_SIZE(rdev->config.cik.macrotile_mode_array);
	u32 reg_offset, split_equal_to_row_size;
	u32 num_pipe_configs;
	u32 num_rbs = rdev->config.cik.max_backends_per_se *
		rdev->config.cik.max_shader_engines;

	चयन (rdev->config.cik.mem_row_size_in_kb) अणु
	हाल 1:
		split_equal_to_row_size = ADDR_SURF_TILE_SPLIT_1KB;
		अवरोध;
	हाल 2:
	शेष:
		split_equal_to_row_size = ADDR_SURF_TILE_SPLIT_2KB;
		अवरोध;
	हाल 4:
		split_equal_to_row_size = ADDR_SURF_TILE_SPLIT_4KB;
		अवरोध;
	पूर्ण

	num_pipe_configs = rdev->config.cik.max_tile_pipes;
	अगर (num_pipe_configs > 8)
		num_pipe_configs = 16;

	क्रम (reg_offset = 0; reg_offset < num_tile_mode_states; reg_offset++)
		tile[reg_offset] = 0;
	क्रम (reg_offset = 0; reg_offset < num_secondary_tile_mode_states; reg_offset++)
		macrotile[reg_offset] = 0;

	चयन(num_pipe_configs) अणु
	हाल 16:
		tile[0] = (ARRAY_MODE(ARRAY_2D_TILED_THIN1) |
			   MICRO_TILE_MODE_NEW(ADDR_SURF_DEPTH_MICRO_TILING) |
			   PIPE_CONFIG(ADDR_SURF_P16_32x32_16x16) |
			   TILE_SPLIT(ADDR_SURF_TILE_SPLIT_64B));
		tile[1] = (ARRAY_MODE(ARRAY_2D_TILED_THIN1) |
			   MICRO_TILE_MODE_NEW(ADDR_SURF_DEPTH_MICRO_TILING) |
			   PIPE_CONFIG(ADDR_SURF_P16_32x32_16x16) |
			   TILE_SPLIT(ADDR_SURF_TILE_SPLIT_128B));
		tile[2] = (ARRAY_MODE(ARRAY_2D_TILED_THIN1) |
			   MICRO_TILE_MODE_NEW(ADDR_SURF_DEPTH_MICRO_TILING) |
			   PIPE_CONFIG(ADDR_SURF_P16_32x32_16x16) |
			   TILE_SPLIT(ADDR_SURF_TILE_SPLIT_256B));
		tile[3] = (ARRAY_MODE(ARRAY_2D_TILED_THIN1) |
			   MICRO_TILE_MODE_NEW(ADDR_SURF_DEPTH_MICRO_TILING) |
			   PIPE_CONFIG(ADDR_SURF_P16_32x32_16x16) |
			   TILE_SPLIT(ADDR_SURF_TILE_SPLIT_512B));
		tile[4] = (ARRAY_MODE(ARRAY_2D_TILED_THIN1) |
			   MICRO_TILE_MODE_NEW(ADDR_SURF_DEPTH_MICRO_TILING) |
			   PIPE_CONFIG(ADDR_SURF_P16_32x32_16x16) |
			   TILE_SPLIT(split_equal_to_row_size));
		tile[5] = (ARRAY_MODE(ARRAY_1D_TILED_THIN1) |
			   PIPE_CONFIG(ADDR_SURF_P16_32x32_16x16) |
			   MICRO_TILE_MODE_NEW(ADDR_SURF_DEPTH_MICRO_TILING));
		tile[6] = (ARRAY_MODE(ARRAY_PRT_2D_TILED_THIN1) |
			   MICRO_TILE_MODE_NEW(ADDR_SURF_DEPTH_MICRO_TILING) |
			   PIPE_CONFIG(ADDR_SURF_P16_32x32_16x16) |
			   TILE_SPLIT(ADDR_SURF_TILE_SPLIT_256B));
		tile[7] = (ARRAY_MODE(ARRAY_PRT_2D_TILED_THIN1) |
			   MICRO_TILE_MODE_NEW(ADDR_SURF_DEPTH_MICRO_TILING) |
			   PIPE_CONFIG(ADDR_SURF_P16_32x32_16x16) |
			   TILE_SPLIT(split_equal_to_row_size));
		tile[8] = (ARRAY_MODE(ARRAY_LINEAR_ALIGNED) |
			   PIPE_CONFIG(ADDR_SURF_P16_32x32_16x16));
		tile[9] = (ARRAY_MODE(ARRAY_1D_TILED_THIN1) |
			   PIPE_CONFIG(ADDR_SURF_P16_32x32_16x16) |
			   MICRO_TILE_MODE_NEW(ADDR_SURF_DISPLAY_MICRO_TILING));
		tile[10] = (ARRAY_MODE(ARRAY_2D_TILED_THIN1) |
			    MICRO_TILE_MODE_NEW(ADDR_SURF_DISPLAY_MICRO_TILING) |
			    PIPE_CONFIG(ADDR_SURF_P16_32x32_16x16) |
			    SAMPLE_SPLIT(ADDR_SURF_SAMPLE_SPLIT_2));
		tile[11] = (ARRAY_MODE(ARRAY_PRT_TILED_THIN1) |
			    MICRO_TILE_MODE_NEW(ADDR_SURF_DISPLAY_MICRO_TILING) |
			    PIPE_CONFIG(ADDR_SURF_P16_32x32_8x16) |
			    SAMPLE_SPLIT(ADDR_SURF_SAMPLE_SPLIT_2));
		tile[12] = (ARRAY_MODE(ARRAY_PRT_2D_TILED_THIN1) |
			    MICRO_TILE_MODE_NEW(ADDR_SURF_DISPLAY_MICRO_TILING) |
			    PIPE_CONFIG(ADDR_SURF_P16_32x32_16x16) |
			    SAMPLE_SPLIT(ADDR_SURF_SAMPLE_SPLIT_2));
		tile[13] = (ARRAY_MODE(ARRAY_1D_TILED_THIN1) |
			    PIPE_CONFIG(ADDR_SURF_P16_32x32_16x16) |
			    MICRO_TILE_MODE_NEW(ADDR_SURF_THIN_MICRO_TILING));
		tile[14] = (ARRAY_MODE(ARRAY_2D_TILED_THIN1) |
			    MICRO_TILE_MODE_NEW(ADDR_SURF_THIN_MICRO_TILING) |
			    PIPE_CONFIG(ADDR_SURF_P16_32x32_16x16) |
			    SAMPLE_SPLIT(ADDR_SURF_SAMPLE_SPLIT_2));
		tile[16] = (ARRAY_MODE(ARRAY_PRT_TILED_THIN1) |
			    MICRO_TILE_MODE_NEW(ADDR_SURF_THIN_MICRO_TILING) |
			    PIPE_CONFIG(ADDR_SURF_P16_32x32_8x16) |
			    SAMPLE_SPLIT(ADDR_SURF_SAMPLE_SPLIT_2));
		tile[17] = (ARRAY_MODE(ARRAY_PRT_2D_TILED_THIN1) |
			    MICRO_TILE_MODE_NEW(ADDR_SURF_THIN_MICRO_TILING) |
			    PIPE_CONFIG(ADDR_SURF_P16_32x32_16x16) |
			    SAMPLE_SPLIT(ADDR_SURF_SAMPLE_SPLIT_2));
		tile[27] = (ARRAY_MODE(ARRAY_1D_TILED_THIN1) |
			    PIPE_CONFIG(ADDR_SURF_P16_32x32_16x16) |
			    MICRO_TILE_MODE_NEW(ADDR_SURF_ROTATED_MICRO_TILING));
		tile[28] = (ARRAY_MODE(ARRAY_2D_TILED_THIN1) |
			    MICRO_TILE_MODE_NEW(ADDR_SURF_ROTATED_MICRO_TILING) |
			    PIPE_CONFIG(ADDR_SURF_P16_32x32_16x16) |
			    SAMPLE_SPLIT(ADDR_SURF_SAMPLE_SPLIT_2));
		tile[29] = (ARRAY_MODE(ARRAY_PRT_TILED_THIN1) |
			    MICRO_TILE_MODE_NEW(ADDR_SURF_ROTATED_MICRO_TILING) |
			    PIPE_CONFIG(ADDR_SURF_P16_32x32_8x16) |
			    SAMPLE_SPLIT(ADDR_SURF_SAMPLE_SPLIT_2));
		tile[30] = (ARRAY_MODE(ARRAY_PRT_2D_TILED_THIN1) |
			    MICRO_TILE_MODE_NEW(ADDR_SURF_ROTATED_MICRO_TILING) |
			    PIPE_CONFIG(ADDR_SURF_P16_32x32_16x16) |
			    SAMPLE_SPLIT(ADDR_SURF_SAMPLE_SPLIT_2));

		macrotile[0] = (BANK_WIDTH(ADDR_SURF_BANK_WIDTH_1) |
			   BANK_HEIGHT(ADDR_SURF_BANK_HEIGHT_4) |
			   MACRO_TILE_ASPECT(ADDR_SURF_MACRO_ASPECT_2) |
			   NUM_BANKS(ADDR_SURF_16_BANK));
		macrotile[1] = (BANK_WIDTH(ADDR_SURF_BANK_WIDTH_1) |
			   BANK_HEIGHT(ADDR_SURF_BANK_HEIGHT_2) |
			   MACRO_TILE_ASPECT(ADDR_SURF_MACRO_ASPECT_2) |
			   NUM_BANKS(ADDR_SURF_16_BANK));
		macrotile[2] = (BANK_WIDTH(ADDR_SURF_BANK_WIDTH_1) |
			   BANK_HEIGHT(ADDR_SURF_BANK_HEIGHT_1) |
			   MACRO_TILE_ASPECT(ADDR_SURF_MACRO_ASPECT_1) |
			   NUM_BANKS(ADDR_SURF_16_BANK));
		macrotile[3] = (BANK_WIDTH(ADDR_SURF_BANK_WIDTH_1) |
			   BANK_HEIGHT(ADDR_SURF_BANK_HEIGHT_1) |
			   MACRO_TILE_ASPECT(ADDR_SURF_MACRO_ASPECT_1) |
			   NUM_BANKS(ADDR_SURF_16_BANK));
		macrotile[4] = (BANK_WIDTH(ADDR_SURF_BANK_WIDTH_1) |
			   BANK_HEIGHT(ADDR_SURF_BANK_HEIGHT_1) |
			   MACRO_TILE_ASPECT(ADDR_SURF_MACRO_ASPECT_1) |
			   NUM_BANKS(ADDR_SURF_8_BANK));
		macrotile[5] = (BANK_WIDTH(ADDR_SURF_BANK_WIDTH_1) |
			   BANK_HEIGHT(ADDR_SURF_BANK_HEIGHT_1) |
			   MACRO_TILE_ASPECT(ADDR_SURF_MACRO_ASPECT_1) |
			   NUM_BANKS(ADDR_SURF_4_BANK));
		macrotile[6] = (BANK_WIDTH(ADDR_SURF_BANK_WIDTH_1) |
			   BANK_HEIGHT(ADDR_SURF_BANK_HEIGHT_1) |
			   MACRO_TILE_ASPECT(ADDR_SURF_MACRO_ASPECT_1) |
			   NUM_BANKS(ADDR_SURF_2_BANK));
		macrotile[8] = (BANK_WIDTH(ADDR_SURF_BANK_WIDTH_1) |
			   BANK_HEIGHT(ADDR_SURF_BANK_HEIGHT_4) |
			   MACRO_TILE_ASPECT(ADDR_SURF_MACRO_ASPECT_2) |
			   NUM_BANKS(ADDR_SURF_16_BANK));
		macrotile[9] = (BANK_WIDTH(ADDR_SURF_BANK_WIDTH_1) |
			   BANK_HEIGHT(ADDR_SURF_BANK_HEIGHT_2) |
			   MACRO_TILE_ASPECT(ADDR_SURF_MACRO_ASPECT_2) |
			   NUM_BANKS(ADDR_SURF_16_BANK));
		macrotile[10] = (BANK_WIDTH(ADDR_SURF_BANK_WIDTH_1) |
			    BANK_HEIGHT(ADDR_SURF_BANK_HEIGHT_1) |
			    MACRO_TILE_ASPECT(ADDR_SURF_MACRO_ASPECT_1) |
			    NUM_BANKS(ADDR_SURF_16_BANK));
		macrotile[11] = (BANK_WIDTH(ADDR_SURF_BANK_WIDTH_1) |
			    BANK_HEIGHT(ADDR_SURF_BANK_HEIGHT_1) |
			    MACRO_TILE_ASPECT(ADDR_SURF_MACRO_ASPECT_1) |
			    NUM_BANKS(ADDR_SURF_8_BANK));
		macrotile[12] = (BANK_WIDTH(ADDR_SURF_BANK_WIDTH_1) |
			    BANK_HEIGHT(ADDR_SURF_BANK_HEIGHT_1) |
			    MACRO_TILE_ASPECT(ADDR_SURF_MACRO_ASPECT_1) |
			    NUM_BANKS(ADDR_SURF_4_BANK));
		macrotile[13] = (BANK_WIDTH(ADDR_SURF_BANK_WIDTH_1) |
			    BANK_HEIGHT(ADDR_SURF_BANK_HEIGHT_1) |
			    MACRO_TILE_ASPECT(ADDR_SURF_MACRO_ASPECT_1) |
			    NUM_BANKS(ADDR_SURF_2_BANK));
		macrotile[14] = (BANK_WIDTH(ADDR_SURF_BANK_WIDTH_1) |
			    BANK_HEIGHT(ADDR_SURF_BANK_HEIGHT_1) |
			    MACRO_TILE_ASPECT(ADDR_SURF_MACRO_ASPECT_1) |
			    NUM_BANKS(ADDR_SURF_2_BANK));

		क्रम (reg_offset = 0; reg_offset < num_tile_mode_states; reg_offset++)
			WREG32(GB_TILE_MODE0 + (reg_offset * 4), tile[reg_offset]);
		क्रम (reg_offset = 0; reg_offset < num_secondary_tile_mode_states; reg_offset++)
			WREG32(GB_MACROTILE_MODE0 + (reg_offset * 4), macrotile[reg_offset]);
		अवरोध;

	हाल 8:
		tile[0] = (ARRAY_MODE(ARRAY_2D_TILED_THIN1) |
			   MICRO_TILE_MODE_NEW(ADDR_SURF_DEPTH_MICRO_TILING) |
			   PIPE_CONFIG(ADDR_SURF_P8_32x32_16x16) |
			   TILE_SPLIT(ADDR_SURF_TILE_SPLIT_64B));
		tile[1] = (ARRAY_MODE(ARRAY_2D_TILED_THIN1) |
			   MICRO_TILE_MODE_NEW(ADDR_SURF_DEPTH_MICRO_TILING) |
			   PIPE_CONFIG(ADDR_SURF_P8_32x32_16x16) |
			   TILE_SPLIT(ADDR_SURF_TILE_SPLIT_128B));
		tile[2] = (ARRAY_MODE(ARRAY_2D_TILED_THIN1) |
			   MICRO_TILE_MODE_NEW(ADDR_SURF_DEPTH_MICRO_TILING) |
			   PIPE_CONFIG(ADDR_SURF_P8_32x32_16x16) |
			   TILE_SPLIT(ADDR_SURF_TILE_SPLIT_256B));
		tile[3] = (ARRAY_MODE(ARRAY_2D_TILED_THIN1) |
			   MICRO_TILE_MODE_NEW(ADDR_SURF_DEPTH_MICRO_TILING) |
			   PIPE_CONFIG(ADDR_SURF_P8_32x32_16x16) |
			   TILE_SPLIT(ADDR_SURF_TILE_SPLIT_512B));
		tile[4] = (ARRAY_MODE(ARRAY_2D_TILED_THIN1) |
			   MICRO_TILE_MODE_NEW(ADDR_SURF_DEPTH_MICRO_TILING) |
			   PIPE_CONFIG(ADDR_SURF_P8_32x32_16x16) |
			   TILE_SPLIT(split_equal_to_row_size));
		tile[5] = (ARRAY_MODE(ARRAY_1D_TILED_THIN1) |
			   PIPE_CONFIG(ADDR_SURF_P8_32x32_16x16) |
			   MICRO_TILE_MODE_NEW(ADDR_SURF_DEPTH_MICRO_TILING));
		tile[6] = (ARRAY_MODE(ARRAY_PRT_2D_TILED_THIN1) |
			   MICRO_TILE_MODE_NEW(ADDR_SURF_DEPTH_MICRO_TILING) |
			   PIPE_CONFIG(ADDR_SURF_P8_32x32_16x16) |
			   TILE_SPLIT(ADDR_SURF_TILE_SPLIT_256B));
		tile[7] = (ARRAY_MODE(ARRAY_PRT_2D_TILED_THIN1) |
			   MICRO_TILE_MODE_NEW(ADDR_SURF_DEPTH_MICRO_TILING) |
			   PIPE_CONFIG(ADDR_SURF_P8_32x32_16x16) |
			   TILE_SPLIT(split_equal_to_row_size));
		tile[8] = (ARRAY_MODE(ARRAY_LINEAR_ALIGNED) |
			   PIPE_CONFIG(ADDR_SURF_P8_32x32_16x16));
		tile[9] = (ARRAY_MODE(ARRAY_1D_TILED_THIN1) |
			   PIPE_CONFIG(ADDR_SURF_P8_32x32_16x16) |
			   MICRO_TILE_MODE_NEW(ADDR_SURF_DISPLAY_MICRO_TILING));
		tile[10] = (ARRAY_MODE(ARRAY_2D_TILED_THIN1) |
			    MICRO_TILE_MODE_NEW(ADDR_SURF_DISPLAY_MICRO_TILING) |
			    PIPE_CONFIG(ADDR_SURF_P8_32x32_16x16) |
			    SAMPLE_SPLIT(ADDR_SURF_SAMPLE_SPLIT_2));
		tile[11] = (ARRAY_MODE(ARRAY_PRT_TILED_THIN1) |
			    MICRO_TILE_MODE_NEW(ADDR_SURF_DISPLAY_MICRO_TILING) |
			    PIPE_CONFIG(ADDR_SURF_P8_32x32_8x16) |
			    SAMPLE_SPLIT(ADDR_SURF_SAMPLE_SPLIT_2));
		tile[12] = (ARRAY_MODE(ARRAY_PRT_2D_TILED_THIN1) |
			    MICRO_TILE_MODE_NEW(ADDR_SURF_DISPLAY_MICRO_TILING) |
			    PIPE_CONFIG(ADDR_SURF_P8_32x32_16x16) |
			    SAMPLE_SPLIT(ADDR_SURF_SAMPLE_SPLIT_2));
		tile[13] = (ARRAY_MODE(ARRAY_1D_TILED_THIN1) |
			    PIPE_CONFIG(ADDR_SURF_P8_32x32_16x16) |
			    MICRO_TILE_MODE_NEW(ADDR_SURF_THIN_MICRO_TILING));
		tile[14] = (ARRAY_MODE(ARRAY_2D_TILED_THIN1) |
			    MICRO_TILE_MODE_NEW(ADDR_SURF_THIN_MICRO_TILING) |
			    PIPE_CONFIG(ADDR_SURF_P8_32x32_16x16) |
			    SAMPLE_SPLIT(ADDR_SURF_SAMPLE_SPLIT_2));
		tile[16] = (ARRAY_MODE(ARRAY_PRT_TILED_THIN1) |
			    MICRO_TILE_MODE_NEW(ADDR_SURF_THIN_MICRO_TILING) |
			    PIPE_CONFIG(ADDR_SURF_P8_32x32_8x16) |
			    SAMPLE_SPLIT(ADDR_SURF_SAMPLE_SPLIT_2));
		tile[17] = (ARRAY_MODE(ARRAY_PRT_2D_TILED_THIN1) |
			    MICRO_TILE_MODE_NEW(ADDR_SURF_THIN_MICRO_TILING) |
			    PIPE_CONFIG(ADDR_SURF_P8_32x32_16x16) |
			    SAMPLE_SPLIT(ADDR_SURF_SAMPLE_SPLIT_2));
		tile[27] = (ARRAY_MODE(ARRAY_1D_TILED_THIN1) |
			    PIPE_CONFIG(ADDR_SURF_P8_32x32_16x16) |
			    MICRO_TILE_MODE_NEW(ADDR_SURF_ROTATED_MICRO_TILING));
		tile[28] = (ARRAY_MODE(ARRAY_2D_TILED_THIN1) |
			    MICRO_TILE_MODE_NEW(ADDR_SURF_ROTATED_MICRO_TILING) |
			    PIPE_CONFIG(ADDR_SURF_P8_32x32_16x16) |
			    SAMPLE_SPLIT(ADDR_SURF_SAMPLE_SPLIT_2));
		tile[29] = (ARRAY_MODE(ARRAY_PRT_TILED_THIN1) |
			    MICRO_TILE_MODE_NEW(ADDR_SURF_ROTATED_MICRO_TILING) |
			    PIPE_CONFIG(ADDR_SURF_P8_32x32_8x16) |
			    SAMPLE_SPLIT(ADDR_SURF_SAMPLE_SPLIT_2));
		tile[30] = (ARRAY_MODE(ARRAY_PRT_2D_TILED_THIN1) |
			    MICRO_TILE_MODE_NEW(ADDR_SURF_ROTATED_MICRO_TILING) |
			    PIPE_CONFIG(ADDR_SURF_P8_32x32_16x16) |
			    SAMPLE_SPLIT(ADDR_SURF_SAMPLE_SPLIT_2));

		macrotile[0] = (BANK_WIDTH(ADDR_SURF_BANK_WIDTH_1) |
				BANK_HEIGHT(ADDR_SURF_BANK_HEIGHT_4) |
				MACRO_TILE_ASPECT(ADDR_SURF_MACRO_ASPECT_4) |
				NUM_BANKS(ADDR_SURF_16_BANK));
		macrotile[1] = (BANK_WIDTH(ADDR_SURF_BANK_WIDTH_1) |
				BANK_HEIGHT(ADDR_SURF_BANK_HEIGHT_2) |
				MACRO_TILE_ASPECT(ADDR_SURF_MACRO_ASPECT_2) |
				NUM_BANKS(ADDR_SURF_16_BANK));
		macrotile[2] = (BANK_WIDTH(ADDR_SURF_BANK_WIDTH_1) |
				BANK_HEIGHT(ADDR_SURF_BANK_HEIGHT_1) |
				MACRO_TILE_ASPECT(ADDR_SURF_MACRO_ASPECT_2) |
				NUM_BANKS(ADDR_SURF_16_BANK));
		macrotile[3] = (BANK_WIDTH(ADDR_SURF_BANK_WIDTH_1) |
				BANK_HEIGHT(ADDR_SURF_BANK_HEIGHT_1) |
				MACRO_TILE_ASPECT(ADDR_SURF_MACRO_ASPECT_2) |
				NUM_BANKS(ADDR_SURF_16_BANK));
		macrotile[4] = (BANK_WIDTH(ADDR_SURF_BANK_WIDTH_1) |
				BANK_HEIGHT(ADDR_SURF_BANK_HEIGHT_1) |
				MACRO_TILE_ASPECT(ADDR_SURF_MACRO_ASPECT_1) |
				NUM_BANKS(ADDR_SURF_8_BANK));
		macrotile[5] = (BANK_WIDTH(ADDR_SURF_BANK_WIDTH_1) |
				BANK_HEIGHT(ADDR_SURF_BANK_HEIGHT_1) |
				MACRO_TILE_ASPECT(ADDR_SURF_MACRO_ASPECT_1) |
				NUM_BANKS(ADDR_SURF_4_BANK));
		macrotile[6] = (BANK_WIDTH(ADDR_SURF_BANK_WIDTH_1) |
				BANK_HEIGHT(ADDR_SURF_BANK_HEIGHT_1) |
				MACRO_TILE_ASPECT(ADDR_SURF_MACRO_ASPECT_1) |
				NUM_BANKS(ADDR_SURF_2_BANK));
		macrotile[8] = (BANK_WIDTH(ADDR_SURF_BANK_WIDTH_1) |
				BANK_HEIGHT(ADDR_SURF_BANK_HEIGHT_8) |
				MACRO_TILE_ASPECT(ADDR_SURF_MACRO_ASPECT_4) |
				NUM_BANKS(ADDR_SURF_16_BANK));
		macrotile[9] = (BANK_WIDTH(ADDR_SURF_BANK_WIDTH_1) |
				BANK_HEIGHT(ADDR_SURF_BANK_HEIGHT_4) |
				MACRO_TILE_ASPECT(ADDR_SURF_MACRO_ASPECT_4) |
				NUM_BANKS(ADDR_SURF_16_BANK));
		macrotile[10] = (BANK_WIDTH(ADDR_SURF_BANK_WIDTH_1) |
				BANK_HEIGHT(ADDR_SURF_BANK_HEIGHT_2) |
				MACRO_TILE_ASPECT(ADDR_SURF_MACRO_ASPECT_2) |
				NUM_BANKS(ADDR_SURF_16_BANK));
		macrotile[11] = (BANK_WIDTH(ADDR_SURF_BANK_WIDTH_1) |
				BANK_HEIGHT(ADDR_SURF_BANK_HEIGHT_1) |
				MACRO_TILE_ASPECT(ADDR_SURF_MACRO_ASPECT_2) |
				NUM_BANKS(ADDR_SURF_16_BANK));
		macrotile[12] = (BANK_WIDTH(ADDR_SURF_BANK_WIDTH_1) |
				BANK_HEIGHT(ADDR_SURF_BANK_HEIGHT_1) |
				MACRO_TILE_ASPECT(ADDR_SURF_MACRO_ASPECT_1) |
				NUM_BANKS(ADDR_SURF_8_BANK));
		macrotile[13] = (BANK_WIDTH(ADDR_SURF_BANK_WIDTH_1) |
				BANK_HEIGHT(ADDR_SURF_BANK_HEIGHT_1) |
				MACRO_TILE_ASPECT(ADDR_SURF_MACRO_ASPECT_1) |
				NUM_BANKS(ADDR_SURF_4_BANK));
		macrotile[14] = (BANK_WIDTH(ADDR_SURF_BANK_WIDTH_1) |
				BANK_HEIGHT(ADDR_SURF_BANK_HEIGHT_1) |
				MACRO_TILE_ASPECT(ADDR_SURF_MACRO_ASPECT_1) |
				NUM_BANKS(ADDR_SURF_2_BANK));

		क्रम (reg_offset = 0; reg_offset < num_tile_mode_states; reg_offset++)
			WREG32(GB_TILE_MODE0 + (reg_offset * 4), tile[reg_offset]);
		क्रम (reg_offset = 0; reg_offset < num_secondary_tile_mode_states; reg_offset++)
			WREG32(GB_MACROTILE_MODE0 + (reg_offset * 4), macrotile[reg_offset]);
		अवरोध;

	हाल 4:
		अगर (num_rbs == 4) अणु
		tile[0] = (ARRAY_MODE(ARRAY_2D_TILED_THIN1) |
			   MICRO_TILE_MODE_NEW(ADDR_SURF_DEPTH_MICRO_TILING) |
			   PIPE_CONFIG(ADDR_SURF_P4_16x16) |
			   TILE_SPLIT(ADDR_SURF_TILE_SPLIT_64B));
		tile[1] = (ARRAY_MODE(ARRAY_2D_TILED_THIN1) |
			   MICRO_TILE_MODE_NEW(ADDR_SURF_DEPTH_MICRO_TILING) |
			   PIPE_CONFIG(ADDR_SURF_P4_16x16) |
			   TILE_SPLIT(ADDR_SURF_TILE_SPLIT_128B));
		tile[2] = (ARRAY_MODE(ARRAY_2D_TILED_THIN1) |
			   MICRO_TILE_MODE_NEW(ADDR_SURF_DEPTH_MICRO_TILING) |
			   PIPE_CONFIG(ADDR_SURF_P4_16x16) |
			   TILE_SPLIT(ADDR_SURF_TILE_SPLIT_256B));
		tile[3] = (ARRAY_MODE(ARRAY_2D_TILED_THIN1) |
			   MICRO_TILE_MODE_NEW(ADDR_SURF_DEPTH_MICRO_TILING) |
			   PIPE_CONFIG(ADDR_SURF_P4_16x16) |
			   TILE_SPLIT(ADDR_SURF_TILE_SPLIT_512B));
		tile[4] = (ARRAY_MODE(ARRAY_2D_TILED_THIN1) |
			   MICRO_TILE_MODE_NEW(ADDR_SURF_DEPTH_MICRO_TILING) |
			   PIPE_CONFIG(ADDR_SURF_P4_16x16) |
			   TILE_SPLIT(split_equal_to_row_size));
		tile[5] = (ARRAY_MODE(ARRAY_1D_TILED_THIN1) |
			   PIPE_CONFIG(ADDR_SURF_P4_16x16) |
			   MICRO_TILE_MODE_NEW(ADDR_SURF_DEPTH_MICRO_TILING));
		tile[6] = (ARRAY_MODE(ARRAY_PRT_2D_TILED_THIN1) |
			   MICRO_TILE_MODE_NEW(ADDR_SURF_DEPTH_MICRO_TILING) |
			   PIPE_CONFIG(ADDR_SURF_P4_16x16) |
			   TILE_SPLIT(ADDR_SURF_TILE_SPLIT_256B));
		tile[7] = (ARRAY_MODE(ARRAY_PRT_2D_TILED_THIN1) |
			   MICRO_TILE_MODE_NEW(ADDR_SURF_DEPTH_MICRO_TILING) |
			   PIPE_CONFIG(ADDR_SURF_P4_16x16) |
			   TILE_SPLIT(split_equal_to_row_size));
		tile[8] = (ARRAY_MODE(ARRAY_LINEAR_ALIGNED) |
			   PIPE_CONFIG(ADDR_SURF_P4_16x16));
		tile[9] = (ARRAY_MODE(ARRAY_1D_TILED_THIN1) |
			   PIPE_CONFIG(ADDR_SURF_P4_16x16) |
			   MICRO_TILE_MODE_NEW(ADDR_SURF_DISPLAY_MICRO_TILING));
		tile[10] = (ARRAY_MODE(ARRAY_2D_TILED_THIN1) |
			    MICRO_TILE_MODE_NEW(ADDR_SURF_DISPLAY_MICRO_TILING) |
			    PIPE_CONFIG(ADDR_SURF_P4_16x16) |
			    SAMPLE_SPLIT(ADDR_SURF_SAMPLE_SPLIT_2));
		tile[11] = (ARRAY_MODE(ARRAY_PRT_TILED_THIN1) |
			    MICRO_TILE_MODE_NEW(ADDR_SURF_DISPLAY_MICRO_TILING) |
			    PIPE_CONFIG(ADDR_SURF_P4_8x16) |
			    SAMPLE_SPLIT(ADDR_SURF_SAMPLE_SPLIT_2));
		tile[12] = (ARRAY_MODE(ARRAY_PRT_2D_TILED_THIN1) |
			    MICRO_TILE_MODE_NEW(ADDR_SURF_DISPLAY_MICRO_TILING) |
			    PIPE_CONFIG(ADDR_SURF_P4_16x16) |
			    SAMPLE_SPLIT(ADDR_SURF_SAMPLE_SPLIT_2));
		tile[13] = (ARRAY_MODE(ARRAY_1D_TILED_THIN1) |
			    PIPE_CONFIG(ADDR_SURF_P4_16x16) |
			    MICRO_TILE_MODE_NEW(ADDR_SURF_THIN_MICRO_TILING));
		tile[14] = (ARRAY_MODE(ARRAY_2D_TILED_THIN1) |
			    MICRO_TILE_MODE_NEW(ADDR_SURF_THIN_MICRO_TILING) |
			    PIPE_CONFIG(ADDR_SURF_P4_16x16) |
			    SAMPLE_SPLIT(ADDR_SURF_SAMPLE_SPLIT_2));
		tile[16] = (ARRAY_MODE(ARRAY_PRT_TILED_THIN1) |
			    MICRO_TILE_MODE_NEW(ADDR_SURF_THIN_MICRO_TILING) |
			    PIPE_CONFIG(ADDR_SURF_P4_8x16) |
			    SAMPLE_SPLIT(ADDR_SURF_SAMPLE_SPLIT_2));
		tile[17] = (ARRAY_MODE(ARRAY_PRT_2D_TILED_THIN1) |
			    MICRO_TILE_MODE_NEW(ADDR_SURF_THIN_MICRO_TILING) |
			    PIPE_CONFIG(ADDR_SURF_P4_16x16) |
			    SAMPLE_SPLIT(ADDR_SURF_SAMPLE_SPLIT_2));
		tile[27] = (ARRAY_MODE(ARRAY_1D_TILED_THIN1) |
			    PIPE_CONFIG(ADDR_SURF_P4_16x16) |
			    MICRO_TILE_MODE_NEW(ADDR_SURF_ROTATED_MICRO_TILING));
		tile[28] = (ARRAY_MODE(ARRAY_PRT_2D_TILED_THIN1) |
			    MICRO_TILE_MODE_NEW(ADDR_SURF_ROTATED_MICRO_TILING) |
			    PIPE_CONFIG(ADDR_SURF_P4_16x16) |
			    SAMPLE_SPLIT(ADDR_SURF_SAMPLE_SPLIT_2));
		tile[29] = (ARRAY_MODE(ARRAY_PRT_TILED_THIN1) |
			    MICRO_TILE_MODE_NEW(ADDR_SURF_ROTATED_MICRO_TILING) |
			    PIPE_CONFIG(ADDR_SURF_P4_8x16) |
			    SAMPLE_SPLIT(ADDR_SURF_SAMPLE_SPLIT_2));
		tile[30] = (ARRAY_MODE(ARRAY_PRT_2D_TILED_THIN1) |
			    MICRO_TILE_MODE_NEW(ADDR_SURF_ROTATED_MICRO_TILING) |
			    PIPE_CONFIG(ADDR_SURF_P4_16x16) |
			    SAMPLE_SPLIT(ADDR_SURF_SAMPLE_SPLIT_2));

		पूर्ण अन्यथा अगर (num_rbs < 4) अणु
		tile[0] = (ARRAY_MODE(ARRAY_2D_TILED_THIN1) |
			   MICRO_TILE_MODE_NEW(ADDR_SURF_DEPTH_MICRO_TILING) |
			   PIPE_CONFIG(ADDR_SURF_P4_8x16) |
			   TILE_SPLIT(ADDR_SURF_TILE_SPLIT_64B));
		tile[1] = (ARRAY_MODE(ARRAY_2D_TILED_THIN1) |
			   MICRO_TILE_MODE_NEW(ADDR_SURF_DEPTH_MICRO_TILING) |
			   PIPE_CONFIG(ADDR_SURF_P4_8x16) |
			   TILE_SPLIT(ADDR_SURF_TILE_SPLIT_128B));
		tile[2] = (ARRAY_MODE(ARRAY_2D_TILED_THIN1) |
			   MICRO_TILE_MODE_NEW(ADDR_SURF_DEPTH_MICRO_TILING) |
			   PIPE_CONFIG(ADDR_SURF_P4_8x16) |
			   TILE_SPLIT(ADDR_SURF_TILE_SPLIT_256B));
		tile[3] = (ARRAY_MODE(ARRAY_2D_TILED_THIN1) |
			   MICRO_TILE_MODE_NEW(ADDR_SURF_DEPTH_MICRO_TILING) |
			   PIPE_CONFIG(ADDR_SURF_P4_8x16) |
			   TILE_SPLIT(ADDR_SURF_TILE_SPLIT_512B));
		tile[4] = (ARRAY_MODE(ARRAY_2D_TILED_THIN1) |
			   MICRO_TILE_MODE_NEW(ADDR_SURF_DEPTH_MICRO_TILING) |
			   PIPE_CONFIG(ADDR_SURF_P4_8x16) |
			   TILE_SPLIT(split_equal_to_row_size));
		tile[5] = (ARRAY_MODE(ARRAY_1D_TILED_THIN1) |
			   PIPE_CONFIG(ADDR_SURF_P4_8x16) |
			   MICRO_TILE_MODE_NEW(ADDR_SURF_DEPTH_MICRO_TILING));
		tile[6] = (ARRAY_MODE(ARRAY_PRT_2D_TILED_THIN1) |
			   MICRO_TILE_MODE_NEW(ADDR_SURF_DEPTH_MICRO_TILING) |
			   PIPE_CONFIG(ADDR_SURF_P4_8x16) |
			   TILE_SPLIT(ADDR_SURF_TILE_SPLIT_256B));
		tile[7] = (ARRAY_MODE(ARRAY_PRT_2D_TILED_THIN1) |
			   MICRO_TILE_MODE_NEW(ADDR_SURF_DEPTH_MICRO_TILING) |
			   PIPE_CONFIG(ADDR_SURF_P4_8x16) |
			   TILE_SPLIT(split_equal_to_row_size));
		tile[8] = (ARRAY_MODE(ARRAY_LINEAR_ALIGNED) |
			   PIPE_CONFIG(ADDR_SURF_P4_8x16));
		tile[9] = (ARRAY_MODE(ARRAY_1D_TILED_THIN1) |
			   PIPE_CONFIG(ADDR_SURF_P4_8x16) |
			   MICRO_TILE_MODE_NEW(ADDR_SURF_DISPLAY_MICRO_TILING));
		tile[10] = (ARRAY_MODE(ARRAY_2D_TILED_THIN1) |
			    MICRO_TILE_MODE_NEW(ADDR_SURF_DISPLAY_MICRO_TILING) |
			    PIPE_CONFIG(ADDR_SURF_P4_8x16) |
			    SAMPLE_SPLIT(ADDR_SURF_SAMPLE_SPLIT_2));
		tile[11] = (ARRAY_MODE(ARRAY_PRT_TILED_THIN1) |
			    MICRO_TILE_MODE_NEW(ADDR_SURF_DISPLAY_MICRO_TILING) |
			    PIPE_CONFIG(ADDR_SURF_P4_8x16) |
			    SAMPLE_SPLIT(ADDR_SURF_SAMPLE_SPLIT_2));
		tile[12] = (ARRAY_MODE(ARRAY_PRT_2D_TILED_THIN1) |
			    MICRO_TILE_MODE_NEW(ADDR_SURF_DISPLAY_MICRO_TILING) |
			    PIPE_CONFIG(ADDR_SURF_P4_8x16) |
			    SAMPLE_SPLIT(ADDR_SURF_SAMPLE_SPLIT_2));
		tile[13] = (ARRAY_MODE(ARRAY_1D_TILED_THIN1) |
			    PIPE_CONFIG(ADDR_SURF_P4_8x16) |
			    MICRO_TILE_MODE_NEW(ADDR_SURF_THIN_MICRO_TILING));
		tile[14] = (ARRAY_MODE(ARRAY_2D_TILED_THIN1) |
			    MICRO_TILE_MODE_NEW(ADDR_SURF_THIN_MICRO_TILING) |
			    PIPE_CONFIG(ADDR_SURF_P4_8x16) |
			    SAMPLE_SPLIT(ADDR_SURF_SAMPLE_SPLIT_2));
		tile[16] = (ARRAY_MODE(ARRAY_PRT_TILED_THIN1) |
			    MICRO_TILE_MODE_NEW(ADDR_SURF_THIN_MICRO_TILING) |
			    PIPE_CONFIG(ADDR_SURF_P4_8x16) |
			    SAMPLE_SPLIT(ADDR_SURF_SAMPLE_SPLIT_2));
		tile[17] = (ARRAY_MODE(ARRAY_PRT_2D_TILED_THIN1) |
			    MICRO_TILE_MODE_NEW(ADDR_SURF_THIN_MICRO_TILING) |
			    PIPE_CONFIG(ADDR_SURF_P4_8x16) |
			    SAMPLE_SPLIT(ADDR_SURF_SAMPLE_SPLIT_2));
		tile[27] = (ARRAY_MODE(ARRAY_1D_TILED_THIN1) |
			    PIPE_CONFIG(ADDR_SURF_P4_8x16) |
			    MICRO_TILE_MODE_NEW(ADDR_SURF_ROTATED_MICRO_TILING));
		tile[28] = (ARRAY_MODE(ARRAY_PRT_2D_TILED_THIN1) |
			    MICRO_TILE_MODE_NEW(ADDR_SURF_ROTATED_MICRO_TILING) |
			    PIPE_CONFIG(ADDR_SURF_P4_8x16) |
			    SAMPLE_SPLIT(ADDR_SURF_SAMPLE_SPLIT_2));
		tile[29] = (ARRAY_MODE(ARRAY_PRT_TILED_THIN1) |
			    MICRO_TILE_MODE_NEW(ADDR_SURF_ROTATED_MICRO_TILING) |
			    PIPE_CONFIG(ADDR_SURF_P4_8x16) |
			    SAMPLE_SPLIT(ADDR_SURF_SAMPLE_SPLIT_2));
		tile[30] = (ARRAY_MODE(ARRAY_PRT_2D_TILED_THIN1) |
			    MICRO_TILE_MODE_NEW(ADDR_SURF_ROTATED_MICRO_TILING) |
			    PIPE_CONFIG(ADDR_SURF_P4_8x16) |
			    SAMPLE_SPLIT(ADDR_SURF_SAMPLE_SPLIT_2));
		पूर्ण

		macrotile[0] = (BANK_WIDTH(ADDR_SURF_BANK_WIDTH_1) |
				BANK_HEIGHT(ADDR_SURF_BANK_HEIGHT_4) |
				MACRO_TILE_ASPECT(ADDR_SURF_MACRO_ASPECT_4) |
				NUM_BANKS(ADDR_SURF_16_BANK));
		macrotile[1] = (BANK_WIDTH(ADDR_SURF_BANK_WIDTH_1) |
				BANK_HEIGHT(ADDR_SURF_BANK_HEIGHT_2) |
				MACRO_TILE_ASPECT(ADDR_SURF_MACRO_ASPECT_4) |
				NUM_BANKS(ADDR_SURF_16_BANK));
		macrotile[2] = (BANK_WIDTH(ADDR_SURF_BANK_WIDTH_1) |
				BANK_HEIGHT(ADDR_SURF_BANK_HEIGHT_1) |
				MACRO_TILE_ASPECT(ADDR_SURF_MACRO_ASPECT_2) |
				NUM_BANKS(ADDR_SURF_16_BANK));
		macrotile[3] = (BANK_WIDTH(ADDR_SURF_BANK_WIDTH_1) |
				BANK_HEIGHT(ADDR_SURF_BANK_HEIGHT_1) |
				MACRO_TILE_ASPECT(ADDR_SURF_MACRO_ASPECT_2) |
				NUM_BANKS(ADDR_SURF_16_BANK));
		macrotile[4] = (BANK_WIDTH(ADDR_SURF_BANK_WIDTH_1) |
				BANK_HEIGHT(ADDR_SURF_BANK_HEIGHT_1) |
				MACRO_TILE_ASPECT(ADDR_SURF_MACRO_ASPECT_2) |
				NUM_BANKS(ADDR_SURF_16_BANK));
		macrotile[5] = (BANK_WIDTH(ADDR_SURF_BANK_WIDTH_1) |
				BANK_HEIGHT(ADDR_SURF_BANK_HEIGHT_1) |
				MACRO_TILE_ASPECT(ADDR_SURF_MACRO_ASPECT_2) |
				NUM_BANKS(ADDR_SURF_8_BANK));
		macrotile[6] = (BANK_WIDTH(ADDR_SURF_BANK_WIDTH_1) |
				BANK_HEIGHT(ADDR_SURF_BANK_HEIGHT_1) |
				MACRO_TILE_ASPECT(ADDR_SURF_MACRO_ASPECT_1) |
				NUM_BANKS(ADDR_SURF_4_BANK));
		macrotile[8] = (BANK_WIDTH(ADDR_SURF_BANK_WIDTH_2) |
				BANK_HEIGHT(ADDR_SURF_BANK_HEIGHT_8) |
				MACRO_TILE_ASPECT(ADDR_SURF_MACRO_ASPECT_4) |
				NUM_BANKS(ADDR_SURF_16_BANK));
		macrotile[9] = (BANK_WIDTH(ADDR_SURF_BANK_WIDTH_2) |
				BANK_HEIGHT(ADDR_SURF_BANK_HEIGHT_4) |
				MACRO_TILE_ASPECT(ADDR_SURF_MACRO_ASPECT_4) |
				NUM_BANKS(ADDR_SURF_16_BANK));
		macrotile[10] = (BANK_WIDTH(ADDR_SURF_BANK_WIDTH_1) |
				BANK_HEIGHT(ADDR_SURF_BANK_HEIGHT_4) |
				MACRO_TILE_ASPECT(ADDR_SURF_MACRO_ASPECT_4) |
				NUM_BANKS(ADDR_SURF_16_BANK));
		macrotile[11] = (BANK_WIDTH(ADDR_SURF_BANK_WIDTH_1) |
				BANK_HEIGHT(ADDR_SURF_BANK_HEIGHT_2) |
				MACRO_TILE_ASPECT(ADDR_SURF_MACRO_ASPECT_4) |
				NUM_BANKS(ADDR_SURF_16_BANK));
		macrotile[12] = (BANK_WIDTH(ADDR_SURF_BANK_WIDTH_1) |
				BANK_HEIGHT(ADDR_SURF_BANK_HEIGHT_1) |
				MACRO_TILE_ASPECT(ADDR_SURF_MACRO_ASPECT_2) |
				NUM_BANKS(ADDR_SURF_16_BANK));
		macrotile[13] = (BANK_WIDTH(ADDR_SURF_BANK_WIDTH_1) |
				BANK_HEIGHT(ADDR_SURF_BANK_HEIGHT_1) |
				MACRO_TILE_ASPECT(ADDR_SURF_MACRO_ASPECT_2) |
				NUM_BANKS(ADDR_SURF_8_BANK));
		macrotile[14] = (BANK_WIDTH(ADDR_SURF_BANK_WIDTH_1) |
				BANK_HEIGHT(ADDR_SURF_BANK_HEIGHT_1) |
				MACRO_TILE_ASPECT(ADDR_SURF_MACRO_ASPECT_1) |
				NUM_BANKS(ADDR_SURF_4_BANK));

		क्रम (reg_offset = 0; reg_offset < num_tile_mode_states; reg_offset++)
			WREG32(GB_TILE_MODE0 + (reg_offset * 4), tile[reg_offset]);
		क्रम (reg_offset = 0; reg_offset < num_secondary_tile_mode_states; reg_offset++)
			WREG32(GB_MACROTILE_MODE0 + (reg_offset * 4), macrotile[reg_offset]);
		अवरोध;

	हाल 2:
		tile[0] = (ARRAY_MODE(ARRAY_2D_TILED_THIN1) |
			   MICRO_TILE_MODE_NEW(ADDR_SURF_DEPTH_MICRO_TILING) |
			   PIPE_CONFIG(ADDR_SURF_P2) |
			   TILE_SPLIT(ADDR_SURF_TILE_SPLIT_64B));
		tile[1] = (ARRAY_MODE(ARRAY_2D_TILED_THIN1) |
			   MICRO_TILE_MODE_NEW(ADDR_SURF_DEPTH_MICRO_TILING) |
			   PIPE_CONFIG(ADDR_SURF_P2) |
			   TILE_SPLIT(ADDR_SURF_TILE_SPLIT_128B));
		tile[2] = (ARRAY_MODE(ARRAY_2D_TILED_THIN1) |
			   MICRO_TILE_MODE_NEW(ADDR_SURF_DEPTH_MICRO_TILING) |
			   PIPE_CONFIG(ADDR_SURF_P2) |
			   TILE_SPLIT(ADDR_SURF_TILE_SPLIT_256B));
		tile[3] = (ARRAY_MODE(ARRAY_2D_TILED_THIN1) |
			   MICRO_TILE_MODE_NEW(ADDR_SURF_DEPTH_MICRO_TILING) |
			   PIPE_CONFIG(ADDR_SURF_P2) |
			   TILE_SPLIT(ADDR_SURF_TILE_SPLIT_512B));
		tile[4] = (ARRAY_MODE(ARRAY_2D_TILED_THIN1) |
			   MICRO_TILE_MODE_NEW(ADDR_SURF_DEPTH_MICRO_TILING) |
			   PIPE_CONFIG(ADDR_SURF_P2) |
			   TILE_SPLIT(split_equal_to_row_size));
		tile[5] = (ARRAY_MODE(ARRAY_1D_TILED_THIN1) |
			   PIPE_CONFIG(ADDR_SURF_P2) |
			   MICRO_TILE_MODE_NEW(ADDR_SURF_DEPTH_MICRO_TILING));
		tile[6] = (ARRAY_MODE(ARRAY_PRT_2D_TILED_THIN1) |
			   MICRO_TILE_MODE_NEW(ADDR_SURF_DEPTH_MICRO_TILING) |
			   PIPE_CONFIG(ADDR_SURF_P2) |
			   TILE_SPLIT(ADDR_SURF_TILE_SPLIT_256B));
		tile[7] = (ARRAY_MODE(ARRAY_PRT_2D_TILED_THIN1) |
			   MICRO_TILE_MODE_NEW(ADDR_SURF_DEPTH_MICRO_TILING) |
			   PIPE_CONFIG(ADDR_SURF_P2) |
			   TILE_SPLIT(split_equal_to_row_size));
		tile[8] = ARRAY_MODE(ARRAY_LINEAR_ALIGNED) |
			   PIPE_CONFIG(ADDR_SURF_P2);
		tile[9] = (ARRAY_MODE(ARRAY_1D_TILED_THIN1) |
			   MICRO_TILE_MODE_NEW(ADDR_SURF_DISPLAY_MICRO_TILING) |
			   PIPE_CONFIG(ADDR_SURF_P2));
		tile[10] = (ARRAY_MODE(ARRAY_2D_TILED_THIN1) |
			    MICRO_TILE_MODE_NEW(ADDR_SURF_DISPLAY_MICRO_TILING) |
			    PIPE_CONFIG(ADDR_SURF_P2) |
			    SAMPLE_SPLIT(ADDR_SURF_SAMPLE_SPLIT_2));
		tile[11] = (ARRAY_MODE(ARRAY_PRT_TILED_THIN1) |
			    MICRO_TILE_MODE_NEW(ADDR_SURF_DISPLAY_MICRO_TILING) |
			    PIPE_CONFIG(ADDR_SURF_P2) |
			    SAMPLE_SPLIT(ADDR_SURF_SAMPLE_SPLIT_2));
		tile[12] = (ARRAY_MODE(ARRAY_PRT_2D_TILED_THIN1) |
			    MICRO_TILE_MODE_NEW(ADDR_SURF_DISPLAY_MICRO_TILING) |
			    PIPE_CONFIG(ADDR_SURF_P2) |
			    SAMPLE_SPLIT(ADDR_SURF_SAMPLE_SPLIT_2));
		tile[13] = (ARRAY_MODE(ARRAY_1D_TILED_THIN1) |
			    PIPE_CONFIG(ADDR_SURF_P2) |
			    MICRO_TILE_MODE_NEW(ADDR_SURF_THIN_MICRO_TILING));
		tile[14] = (ARRAY_MODE(ARRAY_2D_TILED_THIN1) |
			    MICRO_TILE_MODE_NEW(ADDR_SURF_THIN_MICRO_TILING) |
			    PIPE_CONFIG(ADDR_SURF_P2) |
			    SAMPLE_SPLIT(ADDR_SURF_SAMPLE_SPLIT_2));
		tile[16] = (ARRAY_MODE(ARRAY_PRT_TILED_THIN1) |
			    MICRO_TILE_MODE_NEW(ADDR_SURF_THIN_MICRO_TILING) |
			    PIPE_CONFIG(ADDR_SURF_P2) |
			    SAMPLE_SPLIT(ADDR_SURF_SAMPLE_SPLIT_2));
		tile[17] = (ARRAY_MODE(ARRAY_PRT_2D_TILED_THIN1) |
			    MICRO_TILE_MODE_NEW(ADDR_SURF_THIN_MICRO_TILING) |
			    PIPE_CONFIG(ADDR_SURF_P2) |
			    SAMPLE_SPLIT(ADDR_SURF_SAMPLE_SPLIT_2));
		tile[27] = (ARRAY_MODE(ARRAY_1D_TILED_THIN1) |
			    MICRO_TILE_MODE_NEW(ADDR_SURF_ROTATED_MICRO_TILING) |
			    PIPE_CONFIG(ADDR_SURF_P2));
		tile[28] = (ARRAY_MODE(ARRAY_PRT_2D_TILED_THIN1) |
			    MICRO_TILE_MODE_NEW(ADDR_SURF_ROTATED_MICRO_TILING) |
			    PIPE_CONFIG(ADDR_SURF_P2) |
			    SAMPLE_SPLIT(ADDR_SURF_SAMPLE_SPLIT_2));
		tile[29] = (ARRAY_MODE(ARRAY_PRT_TILED_THIN1) |
			    MICRO_TILE_MODE_NEW(ADDR_SURF_ROTATED_MICRO_TILING) |
			    PIPE_CONFIG(ADDR_SURF_P2) |
			    SAMPLE_SPLIT(ADDR_SURF_SAMPLE_SPLIT_2));
		tile[30] = (ARRAY_MODE(ARRAY_PRT_2D_TILED_THIN1) |
			    MICRO_TILE_MODE_NEW(ADDR_SURF_ROTATED_MICRO_TILING) |
			    PIPE_CONFIG(ADDR_SURF_P2) |
			    SAMPLE_SPLIT(ADDR_SURF_SAMPLE_SPLIT_2));

		macrotile[0] = (BANK_WIDTH(ADDR_SURF_BANK_WIDTH_2) |
				BANK_HEIGHT(ADDR_SURF_BANK_HEIGHT_4) |
				MACRO_TILE_ASPECT(ADDR_SURF_MACRO_ASPECT_4) |
				NUM_BANKS(ADDR_SURF_16_BANK));
		macrotile[1] = (BANK_WIDTH(ADDR_SURF_BANK_WIDTH_2) |
				BANK_HEIGHT(ADDR_SURF_BANK_HEIGHT_2) |
				MACRO_TILE_ASPECT(ADDR_SURF_MACRO_ASPECT_4) |
				NUM_BANKS(ADDR_SURF_16_BANK));
		macrotile[2] = (BANK_WIDTH(ADDR_SURF_BANK_WIDTH_1) |
				BANK_HEIGHT(ADDR_SURF_BANK_HEIGHT_2) |
				MACRO_TILE_ASPECT(ADDR_SURF_MACRO_ASPECT_4) |
				NUM_BANKS(ADDR_SURF_16_BANK));
		macrotile[3] = (BANK_WIDTH(ADDR_SURF_BANK_WIDTH_1) |
				BANK_HEIGHT(ADDR_SURF_BANK_HEIGHT_1) |
				MACRO_TILE_ASPECT(ADDR_SURF_MACRO_ASPECT_4) |
				NUM_BANKS(ADDR_SURF_16_BANK));
		macrotile[4] = (BANK_WIDTH(ADDR_SURF_BANK_WIDTH_1) |
				BANK_HEIGHT(ADDR_SURF_BANK_HEIGHT_1) |
				MACRO_TILE_ASPECT(ADDR_SURF_MACRO_ASPECT_4) |
				NUM_BANKS(ADDR_SURF_16_BANK));
		macrotile[5] = (BANK_WIDTH(ADDR_SURF_BANK_WIDTH_1) |
				BANK_HEIGHT(ADDR_SURF_BANK_HEIGHT_1) |
				MACRO_TILE_ASPECT(ADDR_SURF_MACRO_ASPECT_4) |
				NUM_BANKS(ADDR_SURF_16_BANK));
		macrotile[6] = (BANK_WIDTH(ADDR_SURF_BANK_WIDTH_1) |
				BANK_HEIGHT(ADDR_SURF_BANK_HEIGHT_1) |
				MACRO_TILE_ASPECT(ADDR_SURF_MACRO_ASPECT_2) |
				NUM_BANKS(ADDR_SURF_8_BANK));
		macrotile[8] = (BANK_WIDTH(ADDR_SURF_BANK_WIDTH_4) |
				BANK_HEIGHT(ADDR_SURF_BANK_HEIGHT_8) |
				MACRO_TILE_ASPECT(ADDR_SURF_MACRO_ASPECT_4) |
				NUM_BANKS(ADDR_SURF_16_BANK));
		macrotile[9] = (BANK_WIDTH(ADDR_SURF_BANK_WIDTH_4) |
				BANK_HEIGHT(ADDR_SURF_BANK_HEIGHT_4) |
				MACRO_TILE_ASPECT(ADDR_SURF_MACRO_ASPECT_4) |
				NUM_BANKS(ADDR_SURF_16_BANK));
		macrotile[10] = (BANK_WIDTH(ADDR_SURF_BANK_WIDTH_2) |
				BANK_HEIGHT(ADDR_SURF_BANK_HEIGHT_4) |
				MACRO_TILE_ASPECT(ADDR_SURF_MACRO_ASPECT_4) |
				NUM_BANKS(ADDR_SURF_16_BANK));
		macrotile[11] = (BANK_WIDTH(ADDR_SURF_BANK_WIDTH_2) |
				BANK_HEIGHT(ADDR_SURF_BANK_HEIGHT_2) |
				MACRO_TILE_ASPECT(ADDR_SURF_MACRO_ASPECT_4) |
				NUM_BANKS(ADDR_SURF_16_BANK));
		macrotile[12] = (BANK_WIDTH(ADDR_SURF_BANK_WIDTH_1) |
				BANK_HEIGHT(ADDR_SURF_BANK_HEIGHT_2) |
				MACRO_TILE_ASPECT(ADDR_SURF_MACRO_ASPECT_4) |
				NUM_BANKS(ADDR_SURF_16_BANK));
		macrotile[13] = (BANK_WIDTH(ADDR_SURF_BANK_WIDTH_1) |
				BANK_HEIGHT(ADDR_SURF_BANK_HEIGHT_1) |
				MACRO_TILE_ASPECT(ADDR_SURF_MACRO_ASPECT_4) |
				NUM_BANKS(ADDR_SURF_16_BANK));
		macrotile[14] = (BANK_WIDTH(ADDR_SURF_BANK_WIDTH_1) |
				BANK_HEIGHT(ADDR_SURF_BANK_HEIGHT_1) |
				MACRO_TILE_ASPECT(ADDR_SURF_MACRO_ASPECT_2) |
				NUM_BANKS(ADDR_SURF_8_BANK));

		क्रम (reg_offset = 0; reg_offset < num_tile_mode_states; reg_offset++)
			WREG32(GB_TILE_MODE0 + (reg_offset * 4), tile[reg_offset]);
		क्रम (reg_offset = 0; reg_offset < num_secondary_tile_mode_states; reg_offset++)
			WREG32(GB_MACROTILE_MODE0 + (reg_offset * 4), macrotile[reg_offset]);
		अवरोध;

	शेष:
		DRM_ERROR("unknown num pipe config: 0x%x\n", num_pipe_configs);
	पूर्ण
पूर्ण

/**
 * cik_select_se_sh - select which SE, SH to address
 *
 * @rdev: radeon_device poपूर्णांकer
 * @se_num: shader engine to address
 * @sh_num: sh block to address
 *
 * Select which SE, SH combinations to address. Certain
 * रेजिस्टरs are instanced per SE or SH.  0xffffffff means
 * broadcast to all SEs or SHs (CIK).
 */
अटल व्योम cik_select_se_sh(काष्ठा radeon_device *rdev,
			     u32 se_num, u32 sh_num)
अणु
	u32 data = INSTANCE_BROADCAST_WRITES;

	अगर ((se_num == 0xffffffff) && (sh_num == 0xffffffff))
		data |= SH_BROADCAST_WRITES | SE_BROADCAST_WRITES;
	अन्यथा अगर (se_num == 0xffffffff)
		data |= SE_BROADCAST_WRITES | SH_INDEX(sh_num);
	अन्यथा अगर (sh_num == 0xffffffff)
		data |= SH_BROADCAST_WRITES | SE_INDEX(se_num);
	अन्यथा
		data |= SH_INDEX(sh_num) | SE_INDEX(se_num);
	WREG32(GRBM_GFX_INDEX, data);
पूर्ण

/**
 * cik_create_biपंचांगask - create a biपंचांगask
 *
 * @bit_width: length of the mask
 *
 * create a variable length bit mask (CIK).
 * Returns the biपंचांगask.
 */
अटल u32 cik_create_biपंचांगask(u32 bit_width)
अणु
	u32 i, mask = 0;

	क्रम (i = 0; i < bit_width; i++) अणु
		mask <<= 1;
		mask |= 1;
	पूर्ण
	वापस mask;
पूर्ण

/**
 * cik_get_rb_disabled - computes the mask of disabled RBs
 *
 * @rdev: radeon_device poपूर्णांकer
 * @max_rb_num_per_se: max RBs (render backends) per SE (shader engine) क्रम the asic
 * @sh_per_se: number of SH blocks per SE क्रम the asic
 *
 * Calculates the biपंचांगask of disabled RBs (CIK).
 * Returns the disabled RB biपंचांगask.
 */
अटल u32 cik_get_rb_disabled(काष्ठा radeon_device *rdev,
			      u32 max_rb_num_per_se,
			      u32 sh_per_se)
अणु
	u32 data, mask;

	data = RREG32(CC_RB_BACKEND_DISABLE);
	अगर (data & 1)
		data &= BACKEND_DISABLE_MASK;
	अन्यथा
		data = 0;
	data |= RREG32(GC_USER_RB_BACKEND_DISABLE);

	data >>= BACKEND_DISABLE_SHIFT;

	mask = cik_create_biपंचांगask(max_rb_num_per_se / sh_per_se);

	वापस data & mask;
पूर्ण

/**
 * cik_setup_rb - setup the RBs on the asic
 *
 * @rdev: radeon_device poपूर्णांकer
 * @se_num: number of SEs (shader engines) क्रम the asic
 * @sh_per_se: number of SH blocks per SE क्रम the asic
 * @max_rb_num_per_se: max RBs (render backends) per SE क्रम the asic
 *
 * Configures per-SE/SH RB रेजिस्टरs (CIK).
 */
अटल व्योम cik_setup_rb(काष्ठा radeon_device *rdev,
			 u32 se_num, u32 sh_per_se,
			 u32 max_rb_num_per_se)
अणु
	पूर्णांक i, j;
	u32 data, mask;
	u32 disabled_rbs = 0;
	u32 enabled_rbs = 0;

	क्रम (i = 0; i < se_num; i++) अणु
		क्रम (j = 0; j < sh_per_se; j++) अणु
			cik_select_se_sh(rdev, i, j);
			data = cik_get_rb_disabled(rdev, max_rb_num_per_se, sh_per_se);
			अगर (rdev->family == CHIP_HAWAII)
				disabled_rbs |= data << ((i * sh_per_se + j) * HAWAII_RB_BITMAP_WIDTH_PER_SH);
			अन्यथा
				disabled_rbs |= data << ((i * sh_per_se + j) * CIK_RB_BITMAP_WIDTH_PER_SH);
		पूर्ण
	पूर्ण
	cik_select_se_sh(rdev, 0xffffffff, 0xffffffff);

	mask = 1;
	क्रम (i = 0; i < max_rb_num_per_se * se_num; i++) अणु
		अगर (!(disabled_rbs & mask))
			enabled_rbs |= mask;
		mask <<= 1;
	पूर्ण

	rdev->config.cik.backend_enable_mask = enabled_rbs;

	क्रम (i = 0; i < se_num; i++) अणु
		cik_select_se_sh(rdev, i, 0xffffffff);
		data = 0;
		क्रम (j = 0; j < sh_per_se; j++) अणु
			चयन (enabled_rbs & 3) अणु
			हाल 0:
				अगर (j == 0)
					data |= PKR_MAP(RASTER_CONFIG_RB_MAP_3);
				अन्यथा
					data |= PKR_MAP(RASTER_CONFIG_RB_MAP_0);
				अवरोध;
			हाल 1:
				data |= (RASTER_CONFIG_RB_MAP_0 << (i * sh_per_se + j) * 2);
				अवरोध;
			हाल 2:
				data |= (RASTER_CONFIG_RB_MAP_3 << (i * sh_per_se + j) * 2);
				अवरोध;
			हाल 3:
			शेष:
				data |= (RASTER_CONFIG_RB_MAP_2 << (i * sh_per_se + j) * 2);
				अवरोध;
			पूर्ण
			enabled_rbs >>= 2;
		पूर्ण
		WREG32(PA_SC_RASTER_CONFIG, data);
	पूर्ण
	cik_select_se_sh(rdev, 0xffffffff, 0xffffffff);
पूर्ण

/**
 * cik_gpu_init - setup the 3D engine
 *
 * @rdev: radeon_device poपूर्णांकer
 *
 * Configures the 3D engine and tiling configuration
 * रेजिस्टरs so that the 3D engine is usable.
 */
अटल व्योम cik_gpu_init(काष्ठा radeon_device *rdev)
अणु
	u32 gb_addr_config = RREG32(GB_ADDR_CONFIG);
	u32 mc_arb_ramcfg;
	u32 hdp_host_path_cntl;
	u32 पंचांगp;
	पूर्णांक i, j;

	चयन (rdev->family) अणु
	हाल CHIP_BONAIRE:
		rdev->config.cik.max_shader_engines = 2;
		rdev->config.cik.max_tile_pipes = 4;
		rdev->config.cik.max_cu_per_sh = 7;
		rdev->config.cik.max_sh_per_se = 1;
		rdev->config.cik.max_backends_per_se = 2;
		rdev->config.cik.max_texture_channel_caches = 4;
		rdev->config.cik.max_gprs = 256;
		rdev->config.cik.max_gs_thपढ़ोs = 32;
		rdev->config.cik.max_hw_contexts = 8;

		rdev->config.cik.sc_prim_fअगरo_size_frontend = 0x20;
		rdev->config.cik.sc_prim_fअगरo_size_backend = 0x100;
		rdev->config.cik.sc_hiz_tile_fअगरo_size = 0x30;
		rdev->config.cik.sc_earlyz_tile_fअगरo_size = 0x130;
		gb_addr_config = BONAIRE_GB_ADDR_CONFIG_GOLDEN;
		अवरोध;
	हाल CHIP_HAWAII:
		rdev->config.cik.max_shader_engines = 4;
		rdev->config.cik.max_tile_pipes = 16;
		rdev->config.cik.max_cu_per_sh = 11;
		rdev->config.cik.max_sh_per_se = 1;
		rdev->config.cik.max_backends_per_se = 4;
		rdev->config.cik.max_texture_channel_caches = 16;
		rdev->config.cik.max_gprs = 256;
		rdev->config.cik.max_gs_thपढ़ोs = 32;
		rdev->config.cik.max_hw_contexts = 8;

		rdev->config.cik.sc_prim_fअगरo_size_frontend = 0x20;
		rdev->config.cik.sc_prim_fअगरo_size_backend = 0x100;
		rdev->config.cik.sc_hiz_tile_fअगरo_size = 0x30;
		rdev->config.cik.sc_earlyz_tile_fअगरo_size = 0x130;
		gb_addr_config = HAWAII_GB_ADDR_CONFIG_GOLDEN;
		अवरोध;
	हाल CHIP_KAVERI:
		rdev->config.cik.max_shader_engines = 1;
		rdev->config.cik.max_tile_pipes = 4;
		rdev->config.cik.max_cu_per_sh = 8;
		rdev->config.cik.max_backends_per_se = 2;
		rdev->config.cik.max_sh_per_se = 1;
		rdev->config.cik.max_texture_channel_caches = 4;
		rdev->config.cik.max_gprs = 256;
		rdev->config.cik.max_gs_thपढ़ोs = 16;
		rdev->config.cik.max_hw_contexts = 8;

		rdev->config.cik.sc_prim_fअगरo_size_frontend = 0x20;
		rdev->config.cik.sc_prim_fअगरo_size_backend = 0x100;
		rdev->config.cik.sc_hiz_tile_fअगरo_size = 0x30;
		rdev->config.cik.sc_earlyz_tile_fअगरo_size = 0x130;
		gb_addr_config = BONAIRE_GB_ADDR_CONFIG_GOLDEN;
		अवरोध;
	हाल CHIP_KABINI:
	हाल CHIP_MULLINS:
	शेष:
		rdev->config.cik.max_shader_engines = 1;
		rdev->config.cik.max_tile_pipes = 2;
		rdev->config.cik.max_cu_per_sh = 2;
		rdev->config.cik.max_sh_per_se = 1;
		rdev->config.cik.max_backends_per_se = 1;
		rdev->config.cik.max_texture_channel_caches = 2;
		rdev->config.cik.max_gprs = 256;
		rdev->config.cik.max_gs_thपढ़ोs = 16;
		rdev->config.cik.max_hw_contexts = 8;

		rdev->config.cik.sc_prim_fअगरo_size_frontend = 0x20;
		rdev->config.cik.sc_prim_fअगरo_size_backend = 0x100;
		rdev->config.cik.sc_hiz_tile_fअगरo_size = 0x30;
		rdev->config.cik.sc_earlyz_tile_fअगरo_size = 0x130;
		gb_addr_config = BONAIRE_GB_ADDR_CONFIG_GOLDEN;
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

	WREG32(BIF_FB_EN, FB_READ_EN | FB_WRITE_EN);

	RREG32(MC_SHARED_CHMAP);
	mc_arb_ramcfg = RREG32(MC_ARB_RAMCFG);

	rdev->config.cik.num_tile_pipes = rdev->config.cik.max_tile_pipes;
	rdev->config.cik.mem_max_burst_length_bytes = 256;
	पंचांगp = (mc_arb_ramcfg & NOOFCOLS_MASK) >> NOOFCOLS_SHIFT;
	rdev->config.cik.mem_row_size_in_kb = (4 * (1 << (8 + पंचांगp))) / 1024;
	अगर (rdev->config.cik.mem_row_size_in_kb > 4)
		rdev->config.cik.mem_row_size_in_kb = 4;
	/* XXX use MC settings? */
	rdev->config.cik.shader_engine_tile_size = 32;
	rdev->config.cik.num_gpus = 1;
	rdev->config.cik.multi_gpu_tile_size = 64;

	/* fix up row size */
	gb_addr_config &= ~ROW_SIZE_MASK;
	चयन (rdev->config.cik.mem_row_size_in_kb) अणु
	हाल 1:
	शेष:
		gb_addr_config |= ROW_SIZE(0);
		अवरोध;
	हाल 2:
		gb_addr_config |= ROW_SIZE(1);
		अवरोध;
	हाल 4:
		gb_addr_config |= ROW_SIZE(2);
		अवरोध;
	पूर्ण

	/* setup tiling info dword.  gb_addr_config is not adequate since it करोes
	 * not have bank info, so create a custom tiling dword.
	 * bits 3:0   num_pipes
	 * bits 7:4   num_banks
	 * bits 11:8  group_size
	 * bits 15:12 row_size
	 */
	rdev->config.cik.tile_config = 0;
	चयन (rdev->config.cik.num_tile_pipes) अणु
	हाल 1:
		rdev->config.cik.tile_config |= (0 << 0);
		अवरोध;
	हाल 2:
		rdev->config.cik.tile_config |= (1 << 0);
		अवरोध;
	हाल 4:
		rdev->config.cik.tile_config |= (2 << 0);
		अवरोध;
	हाल 8:
	शेष:
		/* XXX what about 12? */
		rdev->config.cik.tile_config |= (3 << 0);
		अवरोध;
	पूर्ण
	rdev->config.cik.tile_config |=
		((mc_arb_ramcfg & NOOFBANK_MASK) >> NOOFBANK_SHIFT) << 4;
	rdev->config.cik.tile_config |=
		((gb_addr_config & PIPE_INTERLEAVE_SIZE_MASK) >> PIPE_INTERLEAVE_SIZE_SHIFT) << 8;
	rdev->config.cik.tile_config |=
		((gb_addr_config & ROW_SIZE_MASK) >> ROW_SIZE_SHIFT) << 12;

	WREG32(GB_ADDR_CONFIG, gb_addr_config);
	WREG32(HDP_ADDR_CONFIG, gb_addr_config);
	WREG32(DMIF_ADDR_CALC, gb_addr_config);
	WREG32(SDMA0_TILING_CONFIG + SDMA0_REGISTER_OFFSET, gb_addr_config & 0x70);
	WREG32(SDMA0_TILING_CONFIG + SDMA1_REGISTER_OFFSET, gb_addr_config & 0x70);
	WREG32(UVD_UDEC_ADDR_CONFIG, gb_addr_config);
	WREG32(UVD_UDEC_DB_ADDR_CONFIG, gb_addr_config);
	WREG32(UVD_UDEC_DBW_ADDR_CONFIG, gb_addr_config);

	cik_tiling_mode_table_init(rdev);

	cik_setup_rb(rdev, rdev->config.cik.max_shader_engines,
		     rdev->config.cik.max_sh_per_se,
		     rdev->config.cik.max_backends_per_se);

	rdev->config.cik.active_cus = 0;
	क्रम (i = 0; i < rdev->config.cik.max_shader_engines; i++) अणु
		क्रम (j = 0; j < rdev->config.cik.max_sh_per_se; j++) अणु
			rdev->config.cik.active_cus +=
				hweight32(cik_get_cu_active_biपंचांगap(rdev, i, j));
		पूर्ण
	पूर्ण

	/* set HW शेषs क्रम 3D engine */
	WREG32(CP_MEQ_THRESHOLDS, MEQ1_START(0x30) | MEQ2_START(0x60));

	WREG32(SX_DEBUG_1, 0x20);

	WREG32(TA_CNTL_AUX, 0x00010000);

	पंचांगp = RREG32(SPI_CONFIG_CNTL);
	पंचांगp |= 0x03000000;
	WREG32(SPI_CONFIG_CNTL, पंचांगp);

	WREG32(SQ_CONFIG, 1);

	WREG32(DB_DEBUG, 0);

	पंचांगp = RREG32(DB_DEBUG2) & ~0xf00fffff;
	पंचांगp |= 0x00000400;
	WREG32(DB_DEBUG2, पंचांगp);

	पंचांगp = RREG32(DB_DEBUG3) & ~0x0002021c;
	पंचांगp |= 0x00020200;
	WREG32(DB_DEBUG3, पंचांगp);

	पंचांगp = RREG32(CB_HW_CONTROL) & ~0x00010000;
	पंचांगp |= 0x00018208;
	WREG32(CB_HW_CONTROL, पंचांगp);

	WREG32(SPI_CONFIG_CNTL_1, VTX_DONE_DELAY(4));

	WREG32(PA_SC_FIFO_SIZE, (SC_FRONTEND_PRIM_FIFO_SIZE(rdev->config.cik.sc_prim_fअगरo_size_frontend) |
				 SC_BACKEND_PRIM_FIFO_SIZE(rdev->config.cik.sc_prim_fअगरo_size_backend) |
				 SC_HIZ_TILE_FIFO_SIZE(rdev->config.cik.sc_hiz_tile_fअगरo_size) |
				 SC_EARLYZ_TILE_FIFO_SIZE(rdev->config.cik.sc_earlyz_tile_fअगरo_size)));

	WREG32(VGT_NUM_INSTANCES, 1);

	WREG32(CP_PERFMON_CNTL, 0);

	WREG32(SQ_CONFIG, 0);

	WREG32(PA_SC_FORCE_EOV_MAX_CNTS, (FORCE_EOV_MAX_CLK_CNT(4095) |
					  FORCE_EOV_MAX_REZ_CNT(255)));

	WREG32(VGT_CACHE_INVALIDATION, CACHE_INVALIDATION(VC_AND_TC) |
	       AUTO_INVLD_EN(ES_AND_GS_AUTO));

	WREG32(VGT_GS_VERTEX_REUSE, 16);
	WREG32(PA_SC_LINE_STIPPLE_STATE, 0);

	पंचांगp = RREG32(HDP_MISC_CNTL);
	पंचांगp |= HDP_FLUSH_INVALIDATE_CACHE;
	WREG32(HDP_MISC_CNTL, पंचांगp);

	hdp_host_path_cntl = RREG32(HDP_HOST_PATH_CNTL);
	WREG32(HDP_HOST_PATH_CNTL, hdp_host_path_cntl);

	WREG32(PA_CL_ENHANCE, CLIP_VTX_REORDER_ENA | NUM_CLIP_SEQ(3));
	WREG32(PA_SC_ENHANCE, ENABLE_PA_SC_OUT_OF_ORDER);

	udelay(50);
पूर्ण

/*
 * GPU scratch रेजिस्टरs helpers function.
 */
/**
 * cik_scratch_init - setup driver info क्रम CP scratch regs
 *
 * @rdev: radeon_device poपूर्णांकer
 *
 * Set up the number and offset of the CP scratch रेजिस्टरs.
 * NOTE: use of CP scratch रेजिस्टरs is a legacy inferface and
 * is not used by शेष on newer asics (r6xx+).  On newer asics,
 * memory buffers are used क्रम fences rather than scratch regs.
 */
अटल व्योम cik_scratch_init(काष्ठा radeon_device *rdev)
अणु
	पूर्णांक i;

	rdev->scratch.num_reg = 7;
	rdev->scratch.reg_base = SCRATCH_REG0;
	क्रम (i = 0; i < rdev->scratch.num_reg; i++) अणु
		rdev->scratch.मुक्त[i] = true;
		rdev->scratch.reg[i] = rdev->scratch.reg_base + (i * 4);
	पूर्ण
पूर्ण

/**
 * cik_ring_test - basic gfx ring test
 *
 * @rdev: radeon_device poपूर्णांकer
 * @ring: radeon_ring काष्ठाure holding ring inक्रमmation
 *
 * Allocate a scratch रेजिस्टर and ग_लिखो to it using the gfx ring (CIK).
 * Provides a basic gfx ring test to verअगरy that the ring is working.
 * Used by cik_cp_gfx_resume();
 * Returns 0 on success, error on failure.
 */
पूर्णांक cik_ring_test(काष्ठा radeon_device *rdev, काष्ठा radeon_ring *ring)
अणु
	uपूर्णांक32_t scratch;
	uपूर्णांक32_t पंचांगp = 0;
	अचिन्हित i;
	पूर्णांक r;

	r = radeon_scratch_get(rdev, &scratch);
	अगर (r) अणु
		DRM_ERROR("radeon: cp failed to get scratch reg (%d).\n", r);
		वापस r;
	पूर्ण
	WREG32(scratch, 0xCAFEDEAD);
	r = radeon_ring_lock(rdev, ring, 3);
	अगर (r) अणु
		DRM_ERROR("radeon: cp failed to lock ring %d (%d).\n", ring->idx, r);
		radeon_scratch_मुक्त(rdev, scratch);
		वापस r;
	पूर्ण
	radeon_ring_ग_लिखो(ring, PACKET3(PACKET3_SET_UCONFIG_REG, 1));
	radeon_ring_ग_लिखो(ring, ((scratch - PACKET3_SET_UCONFIG_REG_START) >> 2));
	radeon_ring_ग_लिखो(ring, 0xDEADBEEF);
	radeon_ring_unlock_commit(rdev, ring, false);

	क्रम (i = 0; i < rdev->usec_समयout; i++) अणु
		पंचांगp = RREG32(scratch);
		अगर (पंचांगp == 0xDEADBEEF)
			अवरोध;
		udelay(1);
	पूर्ण
	अगर (i < rdev->usec_समयout) अणु
		DRM_INFO("ring test on %d succeeded in %d usecs\n", ring->idx, i);
	पूर्ण अन्यथा अणु
		DRM_ERROR("radeon: ring %d test failed (scratch(0x%04X)=0x%08X)\n",
			  ring->idx, scratch, पंचांगp);
		r = -EINVAL;
	पूर्ण
	radeon_scratch_मुक्त(rdev, scratch);
	वापस r;
पूर्ण

/**
 * cik_hdp_flush_cp_ring_emit - emit an hdp flush on the cp
 *
 * @rdev: radeon_device poपूर्णांकer
 * @ridx: radeon ring index
 *
 * Emits an hdp flush on the cp.
 */
अटल व्योम cik_hdp_flush_cp_ring_emit(काष्ठा radeon_device *rdev,
				       पूर्णांक ridx)
अणु
	काष्ठा radeon_ring *ring = &rdev->ring[ridx];
	u32 ref_and_mask;

	चयन (ring->idx) अणु
	हाल CAYMAN_RING_TYPE_CP1_INDEX:
	हाल CAYMAN_RING_TYPE_CP2_INDEX:
	शेष:
		चयन (ring->me) अणु
		हाल 0:
			ref_and_mask = CP2 << ring->pipe;
			अवरोध;
		हाल 1:
			ref_and_mask = CP6 << ring->pipe;
			अवरोध;
		शेष:
			वापस;
		पूर्ण
		अवरोध;
	हाल RADEON_RING_TYPE_GFX_INDEX:
		ref_and_mask = CP0;
		अवरोध;
	पूर्ण

	radeon_ring_ग_लिखो(ring, PACKET3(PACKET3_WAIT_REG_MEM, 5));
	radeon_ring_ग_लिखो(ring, (WAIT_REG_MEM_OPERATION(1) | /* ग_लिखो, रुको, ग_लिखो */
				 WAIT_REG_MEM_FUNCTION(3) |  /* == */
				 WAIT_REG_MEM_ENGINE(1)));   /* pfp */
	radeon_ring_ग_लिखो(ring, GPU_HDP_FLUSH_REQ >> 2);
	radeon_ring_ग_लिखो(ring, GPU_HDP_FLUSH_DONE >> 2);
	radeon_ring_ग_लिखो(ring, ref_and_mask);
	radeon_ring_ग_लिखो(ring, ref_and_mask);
	radeon_ring_ग_लिखो(ring, 0x20); /* poll पूर्णांकerval */
पूर्ण

/**
 * cik_fence_gfx_ring_emit - emit a fence on the gfx ring
 *
 * @rdev: radeon_device poपूर्णांकer
 * @fence: radeon fence object
 *
 * Emits a fence sequnce number on the gfx ring and flushes
 * GPU caches.
 */
व्योम cik_fence_gfx_ring_emit(काष्ठा radeon_device *rdev,
			     काष्ठा radeon_fence *fence)
अणु
	काष्ठा radeon_ring *ring = &rdev->ring[fence->ring];
	u64 addr = rdev->fence_drv[fence->ring].gpu_addr;

	/* Workaround क्रम cache flush problems. First send a dummy EOP
	 * event करोwn the pipe with seq one below.
	 */
	radeon_ring_ग_लिखो(ring, PACKET3(PACKET3_EVENT_WRITE_EOP, 4));
	radeon_ring_ग_लिखो(ring, (EOP_TCL1_ACTION_EN |
				 EOP_TC_ACTION_EN |
				 EVENT_TYPE(CACHE_FLUSH_AND_INV_TS_EVENT) |
				 EVENT_INDEX(5)));
	radeon_ring_ग_लिखो(ring, addr & 0xfffffffc);
	radeon_ring_ग_लिखो(ring, (upper_32_bits(addr) & 0xffff) |
				DATA_SEL(1) | INT_SEL(0));
	radeon_ring_ग_लिखो(ring, fence->seq - 1);
	radeon_ring_ग_लिखो(ring, 0);

	/* Then send the real EOP event करोwn the pipe. */
	radeon_ring_ग_लिखो(ring, PACKET3(PACKET3_EVENT_WRITE_EOP, 4));
	radeon_ring_ग_लिखो(ring, (EOP_TCL1_ACTION_EN |
				 EOP_TC_ACTION_EN |
				 EVENT_TYPE(CACHE_FLUSH_AND_INV_TS_EVENT) |
				 EVENT_INDEX(5)));
	radeon_ring_ग_लिखो(ring, addr & 0xfffffffc);
	radeon_ring_ग_लिखो(ring, (upper_32_bits(addr) & 0xffff) | DATA_SEL(1) | INT_SEL(2));
	radeon_ring_ग_लिखो(ring, fence->seq);
	radeon_ring_ग_लिखो(ring, 0);
पूर्ण

/**
 * cik_fence_compute_ring_emit - emit a fence on the compute ring
 *
 * @rdev: radeon_device poपूर्णांकer
 * @fence: radeon fence object
 *
 * Emits a fence sequnce number on the compute ring and flushes
 * GPU caches.
 */
व्योम cik_fence_compute_ring_emit(काष्ठा radeon_device *rdev,
				 काष्ठा radeon_fence *fence)
अणु
	काष्ठा radeon_ring *ring = &rdev->ring[fence->ring];
	u64 addr = rdev->fence_drv[fence->ring].gpu_addr;

	/* RELEASE_MEM - flush caches, send पूर्णांक */
	radeon_ring_ग_लिखो(ring, PACKET3(PACKET3_RELEASE_MEM, 5));
	radeon_ring_ग_लिखो(ring, (EOP_TCL1_ACTION_EN |
				 EOP_TC_ACTION_EN |
				 EVENT_TYPE(CACHE_FLUSH_AND_INV_TS_EVENT) |
				 EVENT_INDEX(5)));
	radeon_ring_ग_लिखो(ring, DATA_SEL(1) | INT_SEL(2));
	radeon_ring_ग_लिखो(ring, addr & 0xfffffffc);
	radeon_ring_ग_लिखो(ring, upper_32_bits(addr));
	radeon_ring_ग_लिखो(ring, fence->seq);
	radeon_ring_ग_लिखो(ring, 0);
पूर्ण

/**
 * cik_semaphore_ring_emit - emit a semaphore on the CP ring
 *
 * @rdev: radeon_device poपूर्णांकer
 * @ring: radeon ring buffer object
 * @semaphore: radeon semaphore object
 * @emit_रुको: Is this a sempahore रुको?
 *
 * Emits a semaphore संकेत/रुको packet to the CP ring and prevents the PFP
 * from running ahead of semaphore रुकोs.
 */
bool cik_semaphore_ring_emit(काष्ठा radeon_device *rdev,
			     काष्ठा radeon_ring *ring,
			     काष्ठा radeon_semaphore *semaphore,
			     bool emit_रुको)
अणु
	uपूर्णांक64_t addr = semaphore->gpu_addr;
	अचिन्हित sel = emit_रुको ? PACKET3_SEM_SEL_WAIT : PACKET3_SEM_SEL_SIGNAL;

	radeon_ring_ग_लिखो(ring, PACKET3(PACKET3_MEM_SEMAPHORE, 1));
	radeon_ring_ग_लिखो(ring, lower_32_bits(addr));
	radeon_ring_ग_लिखो(ring, (upper_32_bits(addr) & 0xffff) | sel);

	अगर (emit_रुको && ring->idx == RADEON_RING_TYPE_GFX_INDEX) अणु
		/* Prevent the PFP from running ahead of the semaphore रुको */
		radeon_ring_ग_लिखो(ring, PACKET3(PACKET3_PFP_SYNC_ME, 0));
		radeon_ring_ग_लिखो(ring, 0x0);
	पूर्ण

	वापस true;
पूर्ण

/**
 * cik_copy_cpdma - copy pages using the CP DMA engine
 *
 * @rdev: radeon_device poपूर्णांकer
 * @src_offset: src GPU address
 * @dst_offset: dst GPU address
 * @num_gpu_pages: number of GPU pages to xfer
 * @resv: reservation object to sync to
 *
 * Copy GPU paging using the CP DMA engine (CIK+).
 * Used by the radeon tपंचांग implementation to move pages अगर
 * रेजिस्टरed as the asic copy callback.
 */
काष्ठा radeon_fence *cik_copy_cpdma(काष्ठा radeon_device *rdev,
				    uपूर्णांक64_t src_offset, uपूर्णांक64_t dst_offset,
				    अचिन्हित num_gpu_pages,
				    काष्ठा dma_resv *resv)
अणु
	काष्ठा radeon_fence *fence;
	काष्ठा radeon_sync sync;
	पूर्णांक ring_index = rdev->asic->copy.blit_ring_index;
	काष्ठा radeon_ring *ring = &rdev->ring[ring_index];
	u32 size_in_bytes, cur_size_in_bytes, control;
	पूर्णांक i, num_loops;
	पूर्णांक r = 0;

	radeon_sync_create(&sync);

	size_in_bytes = (num_gpu_pages << RADEON_GPU_PAGE_SHIFT);
	num_loops = DIV_ROUND_UP(size_in_bytes, 0x1fffff);
	r = radeon_ring_lock(rdev, ring, num_loops * 7 + 18);
	अगर (r) अणु
		DRM_ERROR("radeon: moving bo (%d).\n", r);
		radeon_sync_मुक्त(rdev, &sync, शून्य);
		वापस ERR_PTR(r);
	पूर्ण

	radeon_sync_resv(rdev, &sync, resv, false);
	radeon_sync_rings(rdev, &sync, ring->idx);

	क्रम (i = 0; i < num_loops; i++) अणु
		cur_size_in_bytes = size_in_bytes;
		अगर (cur_size_in_bytes > 0x1fffff)
			cur_size_in_bytes = 0x1fffff;
		size_in_bytes -= cur_size_in_bytes;
		control = 0;
		अगर (size_in_bytes == 0)
			control |= PACKET3_DMA_DATA_CP_SYNC;
		radeon_ring_ग_लिखो(ring, PACKET3(PACKET3_DMA_DATA, 5));
		radeon_ring_ग_लिखो(ring, control);
		radeon_ring_ग_लिखो(ring, lower_32_bits(src_offset));
		radeon_ring_ग_लिखो(ring, upper_32_bits(src_offset));
		radeon_ring_ग_लिखो(ring, lower_32_bits(dst_offset));
		radeon_ring_ग_लिखो(ring, upper_32_bits(dst_offset));
		radeon_ring_ग_लिखो(ring, cur_size_in_bytes);
		src_offset += cur_size_in_bytes;
		dst_offset += cur_size_in_bytes;
	पूर्ण

	r = radeon_fence_emit(rdev, &fence, ring->idx);
	अगर (r) अणु
		radeon_ring_unlock_unकरो(rdev, ring);
		radeon_sync_मुक्त(rdev, &sync, शून्य);
		वापस ERR_PTR(r);
	पूर्ण

	radeon_ring_unlock_commit(rdev, ring, false);
	radeon_sync_मुक्त(rdev, &sync, fence);

	वापस fence;
पूर्ण

/*
 * IB stuff
 */
/**
 * cik_ring_ib_execute - emit an IB (Indirect Buffer) on the gfx ring
 *
 * @rdev: radeon_device poपूर्णांकer
 * @ib: radeon indirect buffer object
 *
 * Emits a DE (drawing engine) or CE (स्थिरant engine) IB
 * on the gfx ring.  IBs are usually generated by userspace
 * acceleration drivers and submitted to the kernel क्रम
 * scheduling on the ring.  This function schedules the IB
 * on the gfx ring क्रम execution by the GPU.
 */
व्योम cik_ring_ib_execute(काष्ठा radeon_device *rdev, काष्ठा radeon_ib *ib)
अणु
	काष्ठा radeon_ring *ring = &rdev->ring[ib->ring];
	अचिन्हित vm_id = ib->vm ? ib->vm->ids[ib->ring].id : 0;
	u32 header, control = INसूचीECT_BUFFER_VALID;

	अगर (ib->is_स्थिर_ib) अणु
		/* set चयन buffer packet beक्रमe स्थिर IB */
		radeon_ring_ग_लिखो(ring, PACKET3(PACKET3_SWITCH_BUFFER, 0));
		radeon_ring_ग_लिखो(ring, 0);

		header = PACKET3(PACKET3_INसूचीECT_BUFFER_CONST, 2);
	पूर्ण अन्यथा अणु
		u32 next_rptr;
		अगर (ring->rptr_save_reg) अणु
			next_rptr = ring->wptr + 3 + 4;
			radeon_ring_ग_लिखो(ring, PACKET3(PACKET3_SET_UCONFIG_REG, 1));
			radeon_ring_ग_लिखो(ring, ((ring->rptr_save_reg -
						  PACKET3_SET_UCONFIG_REG_START) >> 2));
			radeon_ring_ग_लिखो(ring, next_rptr);
		पूर्ण अन्यथा अगर (rdev->wb.enabled) अणु
			next_rptr = ring->wptr + 5 + 4;
			radeon_ring_ग_लिखो(ring, PACKET3(PACKET3_WRITE_DATA, 3));
			radeon_ring_ग_लिखो(ring, WRITE_DATA_DST_SEL(1));
			radeon_ring_ग_लिखो(ring, ring->next_rptr_gpu_addr & 0xfffffffc);
			radeon_ring_ग_लिखो(ring, upper_32_bits(ring->next_rptr_gpu_addr));
			radeon_ring_ग_लिखो(ring, next_rptr);
		पूर्ण

		header = PACKET3(PACKET3_INसूचीECT_BUFFER, 2);
	पूर्ण

	control |= ib->length_dw | (vm_id << 24);

	radeon_ring_ग_लिखो(ring, header);
	radeon_ring_ग_लिखो(ring, (ib->gpu_addr & 0xFFFFFFFC));
	radeon_ring_ग_लिखो(ring, upper_32_bits(ib->gpu_addr) & 0xFFFF);
	radeon_ring_ग_लिखो(ring, control);
पूर्ण

/**
 * cik_ib_test - basic gfx ring IB test
 *
 * @rdev: radeon_device poपूर्णांकer
 * @ring: radeon_ring काष्ठाure holding ring inक्रमmation
 *
 * Allocate an IB and execute it on the gfx ring (CIK).
 * Provides a basic gfx ring test to verअगरy that IBs are working.
 * Returns 0 on success, error on failure.
 */
पूर्णांक cik_ib_test(काष्ठा radeon_device *rdev, काष्ठा radeon_ring *ring)
अणु
	काष्ठा radeon_ib ib;
	uपूर्णांक32_t scratch;
	uपूर्णांक32_t पंचांगp = 0;
	अचिन्हित i;
	पूर्णांक r;

	r = radeon_scratch_get(rdev, &scratch);
	अगर (r) अणु
		DRM_ERROR("radeon: failed to get scratch reg (%d).\n", r);
		वापस r;
	पूर्ण
	WREG32(scratch, 0xCAFEDEAD);
	r = radeon_ib_get(rdev, ring->idx, &ib, शून्य, 256);
	अगर (r) अणु
		DRM_ERROR("radeon: failed to get ib (%d).\n", r);
		radeon_scratch_मुक्त(rdev, scratch);
		वापस r;
	पूर्ण
	ib.ptr[0] = PACKET3(PACKET3_SET_UCONFIG_REG, 1);
	ib.ptr[1] = ((scratch - PACKET3_SET_UCONFIG_REG_START) >> 2);
	ib.ptr[2] = 0xDEADBEEF;
	ib.length_dw = 3;
	r = radeon_ib_schedule(rdev, &ib, शून्य, false);
	अगर (r) अणु
		radeon_scratch_मुक्त(rdev, scratch);
		radeon_ib_मुक्त(rdev, &ib);
		DRM_ERROR("radeon: failed to schedule ib (%d).\n", r);
		वापस r;
	पूर्ण
	r = radeon_fence_रुको_समयout(ib.fence, false, usecs_to_jअगरfies(
		RADEON_USEC_IB_TEST_TIMEOUT));
	अगर (r < 0) अणु
		DRM_ERROR("radeon: fence wait failed (%d).\n", r);
		radeon_scratch_मुक्त(rdev, scratch);
		radeon_ib_मुक्त(rdev, &ib);
		वापस r;
	पूर्ण अन्यथा अगर (r == 0) अणु
		DRM_ERROR("radeon: fence wait timed out.\n");
		radeon_scratch_मुक्त(rdev, scratch);
		radeon_ib_मुक्त(rdev, &ib);
		वापस -ETIMEDOUT;
	पूर्ण
	r = 0;
	क्रम (i = 0; i < rdev->usec_समयout; i++) अणु
		पंचांगp = RREG32(scratch);
		अगर (पंचांगp == 0xDEADBEEF)
			अवरोध;
		udelay(1);
	पूर्ण
	अगर (i < rdev->usec_समयout) अणु
		DRM_INFO("ib test on ring %d succeeded in %u usecs\n", ib.fence->ring, i);
	पूर्ण अन्यथा अणु
		DRM_ERROR("radeon: ib test failed (scratch(0x%04X)=0x%08X)\n",
			  scratch, पंचांगp);
		r = -EINVAL;
	पूर्ण
	radeon_scratch_मुक्त(rdev, scratch);
	radeon_ib_मुक्त(rdev, &ib);
	वापस r;
पूर्ण

/*
 * CP.
 * On CIK, gfx and compute now have independant command processors.
 *
 * GFX
 * Gfx consists of a single ring and can process both gfx jobs and
 * compute jobs.  The gfx CP consists of three microengines (ME):
 * PFP - Pre-Fetch Parser
 * ME - Micro Engine
 * CE - Constant Engine
 * The PFP and ME make up what is considered the Drawing Engine (DE).
 * The CE is an asynchronous engine used क्रम updating buffer desciptors
 * used by the DE so that they can be loaded पूर्णांकo cache in parallel
 * जबतक the DE is processing state update packets.
 *
 * Compute
 * The compute CP consists of two microengines (ME):
 * MEC1 - Compute MicroEngine 1
 * MEC2 - Compute MicroEngine 2
 * Each MEC supports 4 compute pipes and each pipe supports 8 queues.
 * The queues are exposed to userspace and are programmed directly
 * by the compute runसमय.
 */
/**
 * cik_cp_gfx_enable - enable/disable the gfx CP MEs
 *
 * @rdev: radeon_device poपूर्णांकer
 * @enable: enable or disable the MEs
 *
 * Halts or unhalts the gfx MEs.
 */
अटल व्योम cik_cp_gfx_enable(काष्ठा radeon_device *rdev, bool enable)
अणु
	अगर (enable)
		WREG32(CP_ME_CNTL, 0);
	अन्यथा अणु
		अगर (rdev->asic->copy.copy_ring_index == RADEON_RING_TYPE_GFX_INDEX)
			radeon_tपंचांग_set_active_vram_size(rdev, rdev->mc.visible_vram_size);
		WREG32(CP_ME_CNTL, (CP_ME_HALT | CP_PFP_HALT | CP_CE_HALT));
		rdev->ring[RADEON_RING_TYPE_GFX_INDEX].पढ़ोy = false;
	पूर्ण
	udelay(50);
पूर्ण

/**
 * cik_cp_gfx_load_microcode - load the gfx CP ME ucode
 *
 * @rdev: radeon_device poपूर्णांकer
 *
 * Loads the gfx PFP, ME, and CE ucode.
 * Returns 0 क्रम success, -EINVAL अगर the ucode is not available.
 */
अटल पूर्णांक cik_cp_gfx_load_microcode(काष्ठा radeon_device *rdev)
अणु
	पूर्णांक i;

	अगर (!rdev->me_fw || !rdev->pfp_fw || !rdev->ce_fw)
		वापस -EINVAL;

	cik_cp_gfx_enable(rdev, false);

	अगर (rdev->new_fw) अणु
		स्थिर काष्ठा gfx_firmware_header_v1_0 *pfp_hdr =
			(स्थिर काष्ठा gfx_firmware_header_v1_0 *)rdev->pfp_fw->data;
		स्थिर काष्ठा gfx_firmware_header_v1_0 *ce_hdr =
			(स्थिर काष्ठा gfx_firmware_header_v1_0 *)rdev->ce_fw->data;
		स्थिर काष्ठा gfx_firmware_header_v1_0 *me_hdr =
			(स्थिर काष्ठा gfx_firmware_header_v1_0 *)rdev->me_fw->data;
		स्थिर __le32 *fw_data;
		u32 fw_size;

		radeon_ucode_prपूर्णांक_gfx_hdr(&pfp_hdr->header);
		radeon_ucode_prपूर्णांक_gfx_hdr(&ce_hdr->header);
		radeon_ucode_prपूर्णांक_gfx_hdr(&me_hdr->header);

		/* PFP */
		fw_data = (स्थिर __le32 *)
			(rdev->pfp_fw->data + le32_to_cpu(pfp_hdr->header.ucode_array_offset_bytes));
		fw_size = le32_to_cpu(pfp_hdr->header.ucode_size_bytes) / 4;
		WREG32(CP_PFP_UCODE_ADDR, 0);
		क्रम (i = 0; i < fw_size; i++)
			WREG32(CP_PFP_UCODE_DATA, le32_to_cpup(fw_data++));
		WREG32(CP_PFP_UCODE_ADDR, le32_to_cpu(pfp_hdr->header.ucode_version));

		/* CE */
		fw_data = (स्थिर __le32 *)
			(rdev->ce_fw->data + le32_to_cpu(ce_hdr->header.ucode_array_offset_bytes));
		fw_size = le32_to_cpu(ce_hdr->header.ucode_size_bytes) / 4;
		WREG32(CP_CE_UCODE_ADDR, 0);
		क्रम (i = 0; i < fw_size; i++)
			WREG32(CP_CE_UCODE_DATA, le32_to_cpup(fw_data++));
		WREG32(CP_CE_UCODE_ADDR, le32_to_cpu(ce_hdr->header.ucode_version));

		/* ME */
		fw_data = (स्थिर __be32 *)
			(rdev->me_fw->data + le32_to_cpu(me_hdr->header.ucode_array_offset_bytes));
		fw_size = le32_to_cpu(me_hdr->header.ucode_size_bytes) / 4;
		WREG32(CP_ME_RAM_WADDR, 0);
		क्रम (i = 0; i < fw_size; i++)
			WREG32(CP_ME_RAM_DATA, le32_to_cpup(fw_data++));
		WREG32(CP_ME_RAM_WADDR, le32_to_cpu(me_hdr->header.ucode_version));
		WREG32(CP_ME_RAM_RADDR, le32_to_cpu(me_hdr->header.ucode_version));
	पूर्ण अन्यथा अणु
		स्थिर __be32 *fw_data;

		/* PFP */
		fw_data = (स्थिर __be32 *)rdev->pfp_fw->data;
		WREG32(CP_PFP_UCODE_ADDR, 0);
		क्रम (i = 0; i < CIK_PFP_UCODE_SIZE; i++)
			WREG32(CP_PFP_UCODE_DATA, be32_to_cpup(fw_data++));
		WREG32(CP_PFP_UCODE_ADDR, 0);

		/* CE */
		fw_data = (स्थिर __be32 *)rdev->ce_fw->data;
		WREG32(CP_CE_UCODE_ADDR, 0);
		क्रम (i = 0; i < CIK_CE_UCODE_SIZE; i++)
			WREG32(CP_CE_UCODE_DATA, be32_to_cpup(fw_data++));
		WREG32(CP_CE_UCODE_ADDR, 0);

		/* ME */
		fw_data = (स्थिर __be32 *)rdev->me_fw->data;
		WREG32(CP_ME_RAM_WADDR, 0);
		क्रम (i = 0; i < CIK_ME_UCODE_SIZE; i++)
			WREG32(CP_ME_RAM_DATA, be32_to_cpup(fw_data++));
		WREG32(CP_ME_RAM_WADDR, 0);
	पूर्ण

	वापस 0;
पूर्ण

/**
 * cik_cp_gfx_start - start the gfx ring
 *
 * @rdev: radeon_device poपूर्णांकer
 *
 * Enables the ring and loads the clear state context and other
 * packets required to init the ring.
 * Returns 0 क्रम success, error क्रम failure.
 */
अटल पूर्णांक cik_cp_gfx_start(काष्ठा radeon_device *rdev)
अणु
	काष्ठा radeon_ring *ring = &rdev->ring[RADEON_RING_TYPE_GFX_INDEX];
	पूर्णांक r, i;

	/* init the CP */
	WREG32(CP_MAX_CONTEXT, rdev->config.cik.max_hw_contexts - 1);
	WREG32(CP_ENDIAN_SWAP, 0);
	WREG32(CP_DEVICE_ID, 1);

	cik_cp_gfx_enable(rdev, true);

	r = radeon_ring_lock(rdev, ring, cik_शेष_size + 17);
	अगर (r) अणु
		DRM_ERROR("radeon: cp failed to lock ring (%d).\n", r);
		वापस r;
	पूर्ण

	/* init the CE partitions.  CE only used क्रम gfx on CIK */
	radeon_ring_ग_लिखो(ring, PACKET3(PACKET3_SET_BASE, 2));
	radeon_ring_ग_लिखो(ring, PACKET3_BASE_INDEX(CE_PARTITION_BASE));
	radeon_ring_ग_लिखो(ring, 0x8000);
	radeon_ring_ग_लिखो(ring, 0x8000);

	/* setup clear context state */
	radeon_ring_ग_लिखो(ring, PACKET3(PACKET3_PREAMBLE_CNTL, 0));
	radeon_ring_ग_लिखो(ring, PACKET3_PREAMBLE_BEGIN_CLEAR_STATE);

	radeon_ring_ग_लिखो(ring, PACKET3(PACKET3_CONTEXT_CONTROL, 1));
	radeon_ring_ग_लिखो(ring, 0x80000000);
	radeon_ring_ग_लिखो(ring, 0x80000000);

	क्रम (i = 0; i < cik_शेष_size; i++)
		radeon_ring_ग_लिखो(ring, cik_शेष_state[i]);

	radeon_ring_ग_लिखो(ring, PACKET3(PACKET3_PREAMBLE_CNTL, 0));
	radeon_ring_ग_लिखो(ring, PACKET3_PREAMBLE_END_CLEAR_STATE);

	/* set clear context state */
	radeon_ring_ग_लिखो(ring, PACKET3(PACKET3_CLEAR_STATE, 0));
	radeon_ring_ग_लिखो(ring, 0);

	radeon_ring_ग_लिखो(ring, PACKET3(PACKET3_SET_CONTEXT_REG, 2));
	radeon_ring_ग_लिखो(ring, 0x00000316);
	radeon_ring_ग_लिखो(ring, 0x0000000e); /* VGT_VERTEX_REUSE_BLOCK_CNTL */
	radeon_ring_ग_लिखो(ring, 0x00000010); /* VGT_OUT_DEALLOC_CNTL */

	radeon_ring_unlock_commit(rdev, ring, false);

	वापस 0;
पूर्ण

/**
 * cik_cp_gfx_fini - stop the gfx ring
 *
 * @rdev: radeon_device poपूर्णांकer
 *
 * Stop the gfx ring and tear करोwn the driver ring
 * info.
 */
अटल व्योम cik_cp_gfx_fini(काष्ठा radeon_device *rdev)
अणु
	cik_cp_gfx_enable(rdev, false);
	radeon_ring_fini(rdev, &rdev->ring[RADEON_RING_TYPE_GFX_INDEX]);
पूर्ण

/**
 * cik_cp_gfx_resume - setup the gfx ring buffer रेजिस्टरs
 *
 * @rdev: radeon_device poपूर्णांकer
 *
 * Program the location and size of the gfx ring buffer
 * and test it to make sure it's working.
 * Returns 0 क्रम success, error क्रम failure.
 */
अटल पूर्णांक cik_cp_gfx_resume(काष्ठा radeon_device *rdev)
अणु
	काष्ठा radeon_ring *ring;
	u32 पंचांगp;
	u32 rb_bufsz;
	u64 rb_addr;
	पूर्णांक r;

	WREG32(CP_SEM_WAIT_TIMER, 0x0);
	अगर (rdev->family != CHIP_HAWAII)
		WREG32(CP_SEM_INCOMPLETE_TIMER_CNTL, 0x0);

	/* Set the ग_लिखो poपूर्णांकer delay */
	WREG32(CP_RB_WPTR_DELAY, 0);

	/* set the RB to use vmid 0 */
	WREG32(CP_RB_VMID, 0);

	WREG32(SCRATCH_ADDR, ((rdev->wb.gpu_addr + RADEON_WB_SCRATCH_OFFSET) >> 8) & 0xFFFFFFFF);

	/* ring 0 - compute and gfx */
	/* Set ring buffer size */
	ring = &rdev->ring[RADEON_RING_TYPE_GFX_INDEX];
	rb_bufsz = order_base_2(ring->ring_size / 8);
	पंचांगp = (order_base_2(RADEON_GPU_PAGE_SIZE/8) << 8) | rb_bufsz;
#अगर_घोषित __BIG_ENDIAN
	पंचांगp |= BUF_SWAP_32BIT;
#पूर्ण_अगर
	WREG32(CP_RB0_CNTL, पंचांगp);

	/* Initialize the ring buffer's पढ़ो and ग_लिखो poपूर्णांकers */
	WREG32(CP_RB0_CNTL, पंचांगp | RB_RPTR_WR_ENA);
	ring->wptr = 0;
	WREG32(CP_RB0_WPTR, ring->wptr);

	/* set the wb address wether it's enabled or not */
	WREG32(CP_RB0_RPTR_ADDR, (rdev->wb.gpu_addr + RADEON_WB_CP_RPTR_OFFSET) & 0xFFFFFFFC);
	WREG32(CP_RB0_RPTR_ADDR_HI, upper_32_bits(rdev->wb.gpu_addr + RADEON_WB_CP_RPTR_OFFSET) & 0xFF);

	/* scratch रेजिस्टर shaकरोwing is no दीर्घer supported */
	WREG32(SCRATCH_UMSK, 0);

	अगर (!rdev->wb.enabled)
		पंचांगp |= RB_NO_UPDATE;

	mdelay(1);
	WREG32(CP_RB0_CNTL, पंचांगp);

	rb_addr = ring->gpu_addr >> 8;
	WREG32(CP_RB0_BASE, rb_addr);
	WREG32(CP_RB0_BASE_HI, upper_32_bits(rb_addr));

	/* start the ring */
	cik_cp_gfx_start(rdev);
	rdev->ring[RADEON_RING_TYPE_GFX_INDEX].पढ़ोy = true;
	r = radeon_ring_test(rdev, RADEON_RING_TYPE_GFX_INDEX, &rdev->ring[RADEON_RING_TYPE_GFX_INDEX]);
	अगर (r) अणु
		rdev->ring[RADEON_RING_TYPE_GFX_INDEX].पढ़ोy = false;
		वापस r;
	पूर्ण

	अगर (rdev->asic->copy.copy_ring_index == RADEON_RING_TYPE_GFX_INDEX)
		radeon_tपंचांग_set_active_vram_size(rdev, rdev->mc.real_vram_size);

	वापस 0;
पूर्ण

u32 cik_gfx_get_rptr(काष्ठा radeon_device *rdev,
		     काष्ठा radeon_ring *ring)
अणु
	u32 rptr;

	अगर (rdev->wb.enabled)
		rptr = rdev->wb.wb[ring->rptr_offs/4];
	अन्यथा
		rptr = RREG32(CP_RB0_RPTR);

	वापस rptr;
पूर्ण

u32 cik_gfx_get_wptr(काष्ठा radeon_device *rdev,
		     काष्ठा radeon_ring *ring)
अणु
	वापस RREG32(CP_RB0_WPTR);
पूर्ण

व्योम cik_gfx_set_wptr(काष्ठा radeon_device *rdev,
		      काष्ठा radeon_ring *ring)
अणु
	WREG32(CP_RB0_WPTR, ring->wptr);
	(व्योम)RREG32(CP_RB0_WPTR);
पूर्ण

u32 cik_compute_get_rptr(काष्ठा radeon_device *rdev,
			 काष्ठा radeon_ring *ring)
अणु
	u32 rptr;

	अगर (rdev->wb.enabled) अणु
		rptr = rdev->wb.wb[ring->rptr_offs/4];
	पूर्ण अन्यथा अणु
		mutex_lock(&rdev->srbm_mutex);
		cik_srbm_select(rdev, ring->me, ring->pipe, ring->queue, 0);
		rptr = RREG32(CP_HQD_PQ_RPTR);
		cik_srbm_select(rdev, 0, 0, 0, 0);
		mutex_unlock(&rdev->srbm_mutex);
	पूर्ण

	वापस rptr;
पूर्ण

u32 cik_compute_get_wptr(काष्ठा radeon_device *rdev,
			 काष्ठा radeon_ring *ring)
अणु
	u32 wptr;

	अगर (rdev->wb.enabled) अणु
		/* XXX check अगर swapping is necessary on BE */
		wptr = rdev->wb.wb[ring->wptr_offs/4];
	पूर्ण अन्यथा अणु
		mutex_lock(&rdev->srbm_mutex);
		cik_srbm_select(rdev, ring->me, ring->pipe, ring->queue, 0);
		wptr = RREG32(CP_HQD_PQ_WPTR);
		cik_srbm_select(rdev, 0, 0, 0, 0);
		mutex_unlock(&rdev->srbm_mutex);
	पूर्ण

	वापस wptr;
पूर्ण

व्योम cik_compute_set_wptr(काष्ठा radeon_device *rdev,
			  काष्ठा radeon_ring *ring)
अणु
	/* XXX check अगर swapping is necessary on BE */
	rdev->wb.wb[ring->wptr_offs/4] = ring->wptr;
	WDOORBELL32(ring->करोorbell_index, ring->wptr);
पूर्ण

अटल व्योम cik_compute_stop(काष्ठा radeon_device *rdev,
			     काष्ठा radeon_ring *ring)
अणु
	u32 j, पंचांगp;

	cik_srbm_select(rdev, ring->me, ring->pipe, ring->queue, 0);
	/* Disable wptr polling. */
	पंचांगp = RREG32(CP_PQ_WPTR_POLL_CNTL);
	पंचांगp &= ~WPTR_POLL_EN;
	WREG32(CP_PQ_WPTR_POLL_CNTL, पंचांगp);
	/* Disable HQD. */
	अगर (RREG32(CP_HQD_ACTIVE) & 1) अणु
		WREG32(CP_HQD_DEQUEUE_REQUEST, 1);
		क्रम (j = 0; j < rdev->usec_समयout; j++) अणु
			अगर (!(RREG32(CP_HQD_ACTIVE) & 1))
				अवरोध;
			udelay(1);
		पूर्ण
		WREG32(CP_HQD_DEQUEUE_REQUEST, 0);
		WREG32(CP_HQD_PQ_RPTR, 0);
		WREG32(CP_HQD_PQ_WPTR, 0);
	पूर्ण
	cik_srbm_select(rdev, 0, 0, 0, 0);
पूर्ण

/**
 * cik_cp_compute_enable - enable/disable the compute CP MEs
 *
 * @rdev: radeon_device poपूर्णांकer
 * @enable: enable or disable the MEs
 *
 * Halts or unhalts the compute MEs.
 */
अटल व्योम cik_cp_compute_enable(काष्ठा radeon_device *rdev, bool enable)
अणु
	अगर (enable)
		WREG32(CP_MEC_CNTL, 0);
	अन्यथा अणु
		/*
		 * To make hibernation reliable we need to clear compute ring
		 * configuration beक्रमe halting the compute ring.
		 */
		mutex_lock(&rdev->srbm_mutex);
		cik_compute_stop(rdev,&rdev->ring[CAYMAN_RING_TYPE_CP1_INDEX]);
		cik_compute_stop(rdev,&rdev->ring[CAYMAN_RING_TYPE_CP2_INDEX]);
		mutex_unlock(&rdev->srbm_mutex);

		WREG32(CP_MEC_CNTL, (MEC_ME1_HALT | MEC_ME2_HALT));
		rdev->ring[CAYMAN_RING_TYPE_CP1_INDEX].पढ़ोy = false;
		rdev->ring[CAYMAN_RING_TYPE_CP2_INDEX].पढ़ोy = false;
	पूर्ण
	udelay(50);
पूर्ण

/**
 * cik_cp_compute_load_microcode - load the compute CP ME ucode
 *
 * @rdev: radeon_device poपूर्णांकer
 *
 * Loads the compute MEC1&2 ucode.
 * Returns 0 क्रम success, -EINVAL अगर the ucode is not available.
 */
अटल पूर्णांक cik_cp_compute_load_microcode(काष्ठा radeon_device *rdev)
अणु
	पूर्णांक i;

	अगर (!rdev->mec_fw)
		वापस -EINVAL;

	cik_cp_compute_enable(rdev, false);

	अगर (rdev->new_fw) अणु
		स्थिर काष्ठा gfx_firmware_header_v1_0 *mec_hdr =
			(स्थिर काष्ठा gfx_firmware_header_v1_0 *)rdev->mec_fw->data;
		स्थिर __le32 *fw_data;
		u32 fw_size;

		radeon_ucode_prपूर्णांक_gfx_hdr(&mec_hdr->header);

		/* MEC1 */
		fw_data = (स्थिर __le32 *)
			(rdev->mec_fw->data + le32_to_cpu(mec_hdr->header.ucode_array_offset_bytes));
		fw_size = le32_to_cpu(mec_hdr->header.ucode_size_bytes) / 4;
		WREG32(CP_MEC_ME1_UCODE_ADDR, 0);
		क्रम (i = 0; i < fw_size; i++)
			WREG32(CP_MEC_ME1_UCODE_DATA, le32_to_cpup(fw_data++));
		WREG32(CP_MEC_ME1_UCODE_ADDR, le32_to_cpu(mec_hdr->header.ucode_version));

		/* MEC2 */
		अगर (rdev->family == CHIP_KAVERI) अणु
			स्थिर काष्ठा gfx_firmware_header_v1_0 *mec2_hdr =
				(स्थिर काष्ठा gfx_firmware_header_v1_0 *)rdev->mec2_fw->data;

			fw_data = (स्थिर __le32 *)
				(rdev->mec2_fw->data +
				 le32_to_cpu(mec2_hdr->header.ucode_array_offset_bytes));
			fw_size = le32_to_cpu(mec2_hdr->header.ucode_size_bytes) / 4;
			WREG32(CP_MEC_ME2_UCODE_ADDR, 0);
			क्रम (i = 0; i < fw_size; i++)
				WREG32(CP_MEC_ME2_UCODE_DATA, le32_to_cpup(fw_data++));
			WREG32(CP_MEC_ME2_UCODE_ADDR, le32_to_cpu(mec2_hdr->header.ucode_version));
		पूर्ण
	पूर्ण अन्यथा अणु
		स्थिर __be32 *fw_data;

		/* MEC1 */
		fw_data = (स्थिर __be32 *)rdev->mec_fw->data;
		WREG32(CP_MEC_ME1_UCODE_ADDR, 0);
		क्रम (i = 0; i < CIK_MEC_UCODE_SIZE; i++)
			WREG32(CP_MEC_ME1_UCODE_DATA, be32_to_cpup(fw_data++));
		WREG32(CP_MEC_ME1_UCODE_ADDR, 0);

		अगर (rdev->family == CHIP_KAVERI) अणु
			/* MEC2 */
			fw_data = (स्थिर __be32 *)rdev->mec_fw->data;
			WREG32(CP_MEC_ME2_UCODE_ADDR, 0);
			क्रम (i = 0; i < CIK_MEC_UCODE_SIZE; i++)
				WREG32(CP_MEC_ME2_UCODE_DATA, be32_to_cpup(fw_data++));
			WREG32(CP_MEC_ME2_UCODE_ADDR, 0);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/**
 * cik_cp_compute_start - start the compute queues
 *
 * @rdev: radeon_device poपूर्णांकer
 *
 * Enable the compute queues.
 * Returns 0 क्रम success, error क्रम failure.
 */
अटल पूर्णांक cik_cp_compute_start(काष्ठा radeon_device *rdev)
अणु
	cik_cp_compute_enable(rdev, true);

	वापस 0;
पूर्ण

/**
 * cik_cp_compute_fini - stop the compute queues
 *
 * @rdev: radeon_device poपूर्णांकer
 *
 * Stop the compute queues and tear करोwn the driver queue
 * info.
 */
अटल व्योम cik_cp_compute_fini(काष्ठा radeon_device *rdev)
अणु
	पूर्णांक i, idx, r;

	cik_cp_compute_enable(rdev, false);

	क्रम (i = 0; i < 2; i++) अणु
		अगर (i == 0)
			idx = CAYMAN_RING_TYPE_CP1_INDEX;
		अन्यथा
			idx = CAYMAN_RING_TYPE_CP2_INDEX;

		अगर (rdev->ring[idx].mqd_obj) अणु
			r = radeon_bo_reserve(rdev->ring[idx].mqd_obj, false);
			अगर (unlikely(r != 0))
				dev_warn(rdev->dev, "(%d) reserve MQD bo failed\n", r);

			radeon_bo_unpin(rdev->ring[idx].mqd_obj);
			radeon_bo_unreserve(rdev->ring[idx].mqd_obj);

			radeon_bo_unref(&rdev->ring[idx].mqd_obj);
			rdev->ring[idx].mqd_obj = शून्य;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम cik_mec_fini(काष्ठा radeon_device *rdev)
अणु
	पूर्णांक r;

	अगर (rdev->mec.hpd_eop_obj) अणु
		r = radeon_bo_reserve(rdev->mec.hpd_eop_obj, false);
		अगर (unlikely(r != 0))
			dev_warn(rdev->dev, "(%d) reserve HPD EOP bo failed\n", r);
		radeon_bo_unpin(rdev->mec.hpd_eop_obj);
		radeon_bo_unreserve(rdev->mec.hpd_eop_obj);

		radeon_bo_unref(&rdev->mec.hpd_eop_obj);
		rdev->mec.hpd_eop_obj = शून्य;
	पूर्ण
पूर्ण

#घोषणा MEC_HPD_SIZE 2048

अटल पूर्णांक cik_mec_init(काष्ठा radeon_device *rdev)
अणु
	पूर्णांक r;
	u32 *hpd;

	/*
	 * KV:    2 MEC, 4 Pipes/MEC, 8 Queues/Pipe - 64 Queues total
	 * CI/KB: 1 MEC, 4 Pipes/MEC, 8 Queues/Pipe - 32 Queues total
	 */
	अगर (rdev->family == CHIP_KAVERI)
		rdev->mec.num_mec = 2;
	अन्यथा
		rdev->mec.num_mec = 1;
	rdev->mec.num_pipe = 4;
	rdev->mec.num_queue = rdev->mec.num_mec * rdev->mec.num_pipe * 8;

	अगर (rdev->mec.hpd_eop_obj == शून्य) अणु
		r = radeon_bo_create(rdev,
				     rdev->mec.num_mec *rdev->mec.num_pipe * MEC_HPD_SIZE * 2,
				     PAGE_SIZE, true,
				     RADEON_GEM_DOMAIN_GTT, 0, शून्य, शून्य,
				     &rdev->mec.hpd_eop_obj);
		अगर (r) अणु
			dev_warn(rdev->dev, "(%d) create HDP EOP bo failed\n", r);
			वापस r;
		पूर्ण
	पूर्ण

	r = radeon_bo_reserve(rdev->mec.hpd_eop_obj, false);
	अगर (unlikely(r != 0)) अणु
		cik_mec_fini(rdev);
		वापस r;
	पूर्ण
	r = radeon_bo_pin(rdev->mec.hpd_eop_obj, RADEON_GEM_DOMAIN_GTT,
			  &rdev->mec.hpd_eop_gpu_addr);
	अगर (r) अणु
		dev_warn(rdev->dev, "(%d) pin HDP EOP bo failed\n", r);
		cik_mec_fini(rdev);
		वापस r;
	पूर्ण
	r = radeon_bo_kmap(rdev->mec.hpd_eop_obj, (व्योम **)&hpd);
	अगर (r) अणु
		dev_warn(rdev->dev, "(%d) map HDP EOP bo failed\n", r);
		cik_mec_fini(rdev);
		वापस r;
	पूर्ण

	/* clear memory.  Not sure अगर this is required or not */
	स_रखो(hpd, 0, rdev->mec.num_mec *rdev->mec.num_pipe * MEC_HPD_SIZE * 2);

	radeon_bo_kunmap(rdev->mec.hpd_eop_obj);
	radeon_bo_unreserve(rdev->mec.hpd_eop_obj);

	वापस 0;
पूर्ण

काष्ठा hqd_रेजिस्टरs
अणु
	u32 cp_mqd_base_addr;
	u32 cp_mqd_base_addr_hi;
	u32 cp_hqd_active;
	u32 cp_hqd_vmid;
	u32 cp_hqd_persistent_state;
	u32 cp_hqd_pipe_priority;
	u32 cp_hqd_queue_priority;
	u32 cp_hqd_quantum;
	u32 cp_hqd_pq_base;
	u32 cp_hqd_pq_base_hi;
	u32 cp_hqd_pq_rptr;
	u32 cp_hqd_pq_rptr_report_addr;
	u32 cp_hqd_pq_rptr_report_addr_hi;
	u32 cp_hqd_pq_wptr_poll_addr;
	u32 cp_hqd_pq_wptr_poll_addr_hi;
	u32 cp_hqd_pq_करोorbell_control;
	u32 cp_hqd_pq_wptr;
	u32 cp_hqd_pq_control;
	u32 cp_hqd_ib_base_addr;
	u32 cp_hqd_ib_base_addr_hi;
	u32 cp_hqd_ib_rptr;
	u32 cp_hqd_ib_control;
	u32 cp_hqd_iq_समयr;
	u32 cp_hqd_iq_rptr;
	u32 cp_hqd_dequeue_request;
	u32 cp_hqd_dma_offload;
	u32 cp_hqd_sema_cmd;
	u32 cp_hqd_msg_type;
	u32 cp_hqd_atomic0_preop_lo;
	u32 cp_hqd_atomic0_preop_hi;
	u32 cp_hqd_atomic1_preop_lo;
	u32 cp_hqd_atomic1_preop_hi;
	u32 cp_hqd_hq_scheduler0;
	u32 cp_hqd_hq_scheduler1;
	u32 cp_mqd_control;
पूर्ण;

काष्ठा bonaire_mqd
अणु
	u32 header;
	u32 dispatch_initiator;
	u32 dimensions[3];
	u32 start_idx[3];
	u32 num_thपढ़ोs[3];
	u32 pipeline_stat_enable;
	u32 perf_counter_enable;
	u32 pgm[2];
	u32 tba[2];
	u32 पंचांगa[2];
	u32 pgm_rsrc[2];
	u32 vmid;
	u32 resource_limits;
	u32 अटल_thपढ़ो_mgmt01[2];
	u32 पंचांगp_ring_size;
	u32 अटल_thपढ़ो_mgmt23[2];
	u32 restart[3];
	u32 thपढ़ो_trace_enable;
	u32 reserved1;
	u32 user_data[16];
	u32 vgtcs_invoke_count[2];
	काष्ठा hqd_रेजिस्टरs queue_state;
	u32 dequeue_cntr;
	u32 पूर्णांकerrupt_queue[64];
पूर्ण;

/**
 * cik_cp_compute_resume - setup the compute queue रेजिस्टरs
 *
 * @rdev: radeon_device poपूर्णांकer
 *
 * Program the compute queues and test them to make sure they
 * are working.
 * Returns 0 क्रम success, error क्रम failure.
 */
अटल पूर्णांक cik_cp_compute_resume(काष्ठा radeon_device *rdev)
अणु
	पूर्णांक r, i, j, idx;
	u32 पंचांगp;
	bool use_करोorbell = true;
	u64 hqd_gpu_addr;
	u64 mqd_gpu_addr;
	u64 eop_gpu_addr;
	u64 wb_gpu_addr;
	u32 *buf;
	काष्ठा bonaire_mqd *mqd;

	r = cik_cp_compute_start(rdev);
	अगर (r)
		वापस r;

	/* fix up chicken bits */
	पंचांगp = RREG32(CP_CPF_DEBUG);
	पंचांगp |= (1 << 23);
	WREG32(CP_CPF_DEBUG, पंचांगp);

	/* init the pipes */
	mutex_lock(&rdev->srbm_mutex);

	क्रम (i = 0; i < (rdev->mec.num_pipe * rdev->mec.num_mec); ++i) अणु
		पूर्णांक me = (i < 4) ? 1 : 2;
		पूर्णांक pipe = (i < 4) ? i : (i - 4);

		cik_srbm_select(rdev, me, pipe, 0, 0);

		eop_gpu_addr = rdev->mec.hpd_eop_gpu_addr + (i * MEC_HPD_SIZE * 2) ;
		/* ग_लिखो the EOP addr */
		WREG32(CP_HPD_EOP_BASE_ADDR, eop_gpu_addr >> 8);
		WREG32(CP_HPD_EOP_BASE_ADDR_HI, upper_32_bits(eop_gpu_addr) >> 8);

		/* set the VMID asचिन्हित */
		WREG32(CP_HPD_EOP_VMID, 0);

		/* set the EOP size, रेजिस्टर value is 2^(EOP_SIZE+1) dwords */
		पंचांगp = RREG32(CP_HPD_EOP_CONTROL);
		पंचांगp &= ~EOP_SIZE_MASK;
		पंचांगp |= order_base_2(MEC_HPD_SIZE / 8);
		WREG32(CP_HPD_EOP_CONTROL, पंचांगp);

	पूर्ण
	cik_srbm_select(rdev, 0, 0, 0, 0);
	mutex_unlock(&rdev->srbm_mutex);

	/* init the queues.  Just two क्रम now. */
	क्रम (i = 0; i < 2; i++) अणु
		अगर (i == 0)
			idx = CAYMAN_RING_TYPE_CP1_INDEX;
		अन्यथा
			idx = CAYMAN_RING_TYPE_CP2_INDEX;

		अगर (rdev->ring[idx].mqd_obj == शून्य) अणु
			r = radeon_bo_create(rdev,
					     माप(काष्ठा bonaire_mqd),
					     PAGE_SIZE, true,
					     RADEON_GEM_DOMAIN_GTT, 0, शून्य,
					     शून्य, &rdev->ring[idx].mqd_obj);
			अगर (r) अणु
				dev_warn(rdev->dev, "(%d) create MQD bo failed\n", r);
				वापस r;
			पूर्ण
		पूर्ण

		r = radeon_bo_reserve(rdev->ring[idx].mqd_obj, false);
		अगर (unlikely(r != 0)) अणु
			cik_cp_compute_fini(rdev);
			वापस r;
		पूर्ण
		r = radeon_bo_pin(rdev->ring[idx].mqd_obj, RADEON_GEM_DOMAIN_GTT,
				  &mqd_gpu_addr);
		अगर (r) अणु
			dev_warn(rdev->dev, "(%d) pin MQD bo failed\n", r);
			cik_cp_compute_fini(rdev);
			वापस r;
		पूर्ण
		r = radeon_bo_kmap(rdev->ring[idx].mqd_obj, (व्योम **)&buf);
		अगर (r) अणु
			dev_warn(rdev->dev, "(%d) map MQD bo failed\n", r);
			cik_cp_compute_fini(rdev);
			वापस r;
		पूर्ण

		/* init the mqd काष्ठा */
		स_रखो(buf, 0, माप(काष्ठा bonaire_mqd));

		mqd = (काष्ठा bonaire_mqd *)buf;
		mqd->header = 0xC0310800;
		mqd->अटल_thपढ़ो_mgmt01[0] = 0xffffffff;
		mqd->अटल_thपढ़ो_mgmt01[1] = 0xffffffff;
		mqd->अटल_thपढ़ो_mgmt23[0] = 0xffffffff;
		mqd->अटल_thपढ़ो_mgmt23[1] = 0xffffffff;

		mutex_lock(&rdev->srbm_mutex);
		cik_srbm_select(rdev, rdev->ring[idx].me,
				rdev->ring[idx].pipe,
				rdev->ring[idx].queue, 0);

		/* disable wptr polling */
		पंचांगp = RREG32(CP_PQ_WPTR_POLL_CNTL);
		पंचांगp &= ~WPTR_POLL_EN;
		WREG32(CP_PQ_WPTR_POLL_CNTL, पंचांगp);

		/* enable करोorbell? */
		mqd->queue_state.cp_hqd_pq_करोorbell_control =
			RREG32(CP_HQD_PQ_DOORBELL_CONTROL);
		अगर (use_करोorbell)
			mqd->queue_state.cp_hqd_pq_करोorbell_control |= DOORBELL_EN;
		अन्यथा
			mqd->queue_state.cp_hqd_pq_करोorbell_control &= ~DOORBELL_EN;
		WREG32(CP_HQD_PQ_DOORBELL_CONTROL,
		       mqd->queue_state.cp_hqd_pq_करोorbell_control);

		/* disable the queue अगर it's active */
		mqd->queue_state.cp_hqd_dequeue_request = 0;
		mqd->queue_state.cp_hqd_pq_rptr = 0;
		mqd->queue_state.cp_hqd_pq_wptr= 0;
		अगर (RREG32(CP_HQD_ACTIVE) & 1) अणु
			WREG32(CP_HQD_DEQUEUE_REQUEST, 1);
			क्रम (j = 0; j < rdev->usec_समयout; j++) अणु
				अगर (!(RREG32(CP_HQD_ACTIVE) & 1))
					अवरोध;
				udelay(1);
			पूर्ण
			WREG32(CP_HQD_DEQUEUE_REQUEST, mqd->queue_state.cp_hqd_dequeue_request);
			WREG32(CP_HQD_PQ_RPTR, mqd->queue_state.cp_hqd_pq_rptr);
			WREG32(CP_HQD_PQ_WPTR, mqd->queue_state.cp_hqd_pq_wptr);
		पूर्ण

		/* set the poपूर्णांकer to the MQD */
		mqd->queue_state.cp_mqd_base_addr = mqd_gpu_addr & 0xfffffffc;
		mqd->queue_state.cp_mqd_base_addr_hi = upper_32_bits(mqd_gpu_addr);
		WREG32(CP_MQD_BASE_ADDR, mqd->queue_state.cp_mqd_base_addr);
		WREG32(CP_MQD_BASE_ADDR_HI, mqd->queue_state.cp_mqd_base_addr_hi);
		/* set MQD vmid to 0 */
		mqd->queue_state.cp_mqd_control = RREG32(CP_MQD_CONTROL);
		mqd->queue_state.cp_mqd_control &= ~MQD_VMID_MASK;
		WREG32(CP_MQD_CONTROL, mqd->queue_state.cp_mqd_control);

		/* set the poपूर्णांकer to the HQD, this is similar CP_RB0_BASE/_HI */
		hqd_gpu_addr = rdev->ring[idx].gpu_addr >> 8;
		mqd->queue_state.cp_hqd_pq_base = hqd_gpu_addr;
		mqd->queue_state.cp_hqd_pq_base_hi = upper_32_bits(hqd_gpu_addr);
		WREG32(CP_HQD_PQ_BASE, mqd->queue_state.cp_hqd_pq_base);
		WREG32(CP_HQD_PQ_BASE_HI, mqd->queue_state.cp_hqd_pq_base_hi);

		/* set up the HQD, this is similar to CP_RB0_CNTL */
		mqd->queue_state.cp_hqd_pq_control = RREG32(CP_HQD_PQ_CONTROL);
		mqd->queue_state.cp_hqd_pq_control &=
			~(QUEUE_SIZE_MASK | RPTR_BLOCK_SIZE_MASK);

		mqd->queue_state.cp_hqd_pq_control |=
			order_base_2(rdev->ring[idx].ring_size / 8);
		mqd->queue_state.cp_hqd_pq_control |=
			(order_base_2(RADEON_GPU_PAGE_SIZE/8) << 8);
#अगर_घोषित __BIG_ENDIAN
		mqd->queue_state.cp_hqd_pq_control |= BUF_SWAP_32BIT;
#पूर्ण_अगर
		mqd->queue_state.cp_hqd_pq_control &=
			~(UNORD_DISPATCH | ROQ_PQ_IB_FLIP | PQ_VOLATILE);
		mqd->queue_state.cp_hqd_pq_control |=
			PRIV_STATE | KMD_QUEUE; /* assuming kernel queue control */
		WREG32(CP_HQD_PQ_CONTROL, mqd->queue_state.cp_hqd_pq_control);

		/* only used अगर CP_PQ_WPTR_POLL_CNTL.WPTR_POLL_EN=1 */
		अगर (i == 0)
			wb_gpu_addr = rdev->wb.gpu_addr + CIK_WB_CP1_WPTR_OFFSET;
		अन्यथा
			wb_gpu_addr = rdev->wb.gpu_addr + CIK_WB_CP2_WPTR_OFFSET;
		mqd->queue_state.cp_hqd_pq_wptr_poll_addr = wb_gpu_addr & 0xfffffffc;
		mqd->queue_state.cp_hqd_pq_wptr_poll_addr_hi = upper_32_bits(wb_gpu_addr) & 0xffff;
		WREG32(CP_HQD_PQ_WPTR_POLL_ADDR, mqd->queue_state.cp_hqd_pq_wptr_poll_addr);
		WREG32(CP_HQD_PQ_WPTR_POLL_ADDR_HI,
		       mqd->queue_state.cp_hqd_pq_wptr_poll_addr_hi);

		/* set the wb address wether it's enabled or not */
		अगर (i == 0)
			wb_gpu_addr = rdev->wb.gpu_addr + RADEON_WB_CP1_RPTR_OFFSET;
		अन्यथा
			wb_gpu_addr = rdev->wb.gpu_addr + RADEON_WB_CP2_RPTR_OFFSET;
		mqd->queue_state.cp_hqd_pq_rptr_report_addr = wb_gpu_addr & 0xfffffffc;
		mqd->queue_state.cp_hqd_pq_rptr_report_addr_hi =
			upper_32_bits(wb_gpu_addr) & 0xffff;
		WREG32(CP_HQD_PQ_RPTR_REPORT_ADDR,
		       mqd->queue_state.cp_hqd_pq_rptr_report_addr);
		WREG32(CP_HQD_PQ_RPTR_REPORT_ADDR_HI,
		       mqd->queue_state.cp_hqd_pq_rptr_report_addr_hi);

		/* enable the करोorbell अगर requested */
		अगर (use_करोorbell) अणु
			mqd->queue_state.cp_hqd_pq_करोorbell_control =
				RREG32(CP_HQD_PQ_DOORBELL_CONTROL);
			mqd->queue_state.cp_hqd_pq_करोorbell_control &= ~DOORBELL_OFFSET_MASK;
			mqd->queue_state.cp_hqd_pq_करोorbell_control |=
				DOORBELL_OFFSET(rdev->ring[idx].करोorbell_index);
			mqd->queue_state.cp_hqd_pq_करोorbell_control |= DOORBELL_EN;
			mqd->queue_state.cp_hqd_pq_करोorbell_control &=
				~(DOORBELL_SOURCE | DOORBELL_HIT);

		पूर्ण अन्यथा अणु
			mqd->queue_state.cp_hqd_pq_करोorbell_control = 0;
		पूर्ण
		WREG32(CP_HQD_PQ_DOORBELL_CONTROL,
		       mqd->queue_state.cp_hqd_pq_करोorbell_control);

		/* पढ़ो and ग_लिखो poपूर्णांकers, similar to CP_RB0_WPTR/_RPTR */
		rdev->ring[idx].wptr = 0;
		mqd->queue_state.cp_hqd_pq_wptr = rdev->ring[idx].wptr;
		WREG32(CP_HQD_PQ_WPTR, mqd->queue_state.cp_hqd_pq_wptr);
		mqd->queue_state.cp_hqd_pq_rptr = RREG32(CP_HQD_PQ_RPTR);

		/* set the vmid क्रम the queue */
		mqd->queue_state.cp_hqd_vmid = 0;
		WREG32(CP_HQD_VMID, mqd->queue_state.cp_hqd_vmid);

		/* activate the queue */
		mqd->queue_state.cp_hqd_active = 1;
		WREG32(CP_HQD_ACTIVE, mqd->queue_state.cp_hqd_active);

		cik_srbm_select(rdev, 0, 0, 0, 0);
		mutex_unlock(&rdev->srbm_mutex);

		radeon_bo_kunmap(rdev->ring[idx].mqd_obj);
		radeon_bo_unreserve(rdev->ring[idx].mqd_obj);

		rdev->ring[idx].पढ़ोy = true;
		r = radeon_ring_test(rdev, idx, &rdev->ring[idx]);
		अगर (r)
			rdev->ring[idx].पढ़ोy = false;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम cik_cp_enable(काष्ठा radeon_device *rdev, bool enable)
अणु
	cik_cp_gfx_enable(rdev, enable);
	cik_cp_compute_enable(rdev, enable);
पूर्ण

अटल पूर्णांक cik_cp_load_microcode(काष्ठा radeon_device *rdev)
अणु
	पूर्णांक r;

	r = cik_cp_gfx_load_microcode(rdev);
	अगर (r)
		वापस r;
	r = cik_cp_compute_load_microcode(rdev);
	अगर (r)
		वापस r;

	वापस 0;
पूर्ण

अटल व्योम cik_cp_fini(काष्ठा radeon_device *rdev)
अणु
	cik_cp_gfx_fini(rdev);
	cik_cp_compute_fini(rdev);
पूर्ण

अटल पूर्णांक cik_cp_resume(काष्ठा radeon_device *rdev)
अणु
	पूर्णांक r;

	cik_enable_gui_idle_पूर्णांकerrupt(rdev, false);

	r = cik_cp_load_microcode(rdev);
	अगर (r)
		वापस r;

	r = cik_cp_gfx_resume(rdev);
	अगर (r)
		वापस r;
	r = cik_cp_compute_resume(rdev);
	अगर (r)
		वापस r;

	cik_enable_gui_idle_पूर्णांकerrupt(rdev, true);

	वापस 0;
पूर्ण

अटल व्योम cik_prपूर्णांक_gpu_status_regs(काष्ठा radeon_device *rdev)
अणु
	dev_info(rdev->dev, "  GRBM_STATUS=0x%08X\n",
		RREG32(GRBM_STATUS));
	dev_info(rdev->dev, "  GRBM_STATUS2=0x%08X\n",
		RREG32(GRBM_STATUS2));
	dev_info(rdev->dev, "  GRBM_STATUS_SE0=0x%08X\n",
		RREG32(GRBM_STATUS_SE0));
	dev_info(rdev->dev, "  GRBM_STATUS_SE1=0x%08X\n",
		RREG32(GRBM_STATUS_SE1));
	dev_info(rdev->dev, "  GRBM_STATUS_SE2=0x%08X\n",
		RREG32(GRBM_STATUS_SE2));
	dev_info(rdev->dev, "  GRBM_STATUS_SE3=0x%08X\n",
		RREG32(GRBM_STATUS_SE3));
	dev_info(rdev->dev, "  SRBM_STATUS=0x%08X\n",
		RREG32(SRBM_STATUS));
	dev_info(rdev->dev, "  SRBM_STATUS2=0x%08X\n",
		RREG32(SRBM_STATUS2));
	dev_info(rdev->dev, "  SDMA0_STATUS_REG   = 0x%08X\n",
		RREG32(SDMA0_STATUS_REG + SDMA0_REGISTER_OFFSET));
	dev_info(rdev->dev, "  SDMA1_STATUS_REG   = 0x%08X\n",
		 RREG32(SDMA0_STATUS_REG + SDMA1_REGISTER_OFFSET));
	dev_info(rdev->dev, "  CP_STAT = 0x%08x\n", RREG32(CP_STAT));
	dev_info(rdev->dev, "  CP_STALLED_STAT1 = 0x%08x\n",
		 RREG32(CP_STALLED_STAT1));
	dev_info(rdev->dev, "  CP_STALLED_STAT2 = 0x%08x\n",
		 RREG32(CP_STALLED_STAT2));
	dev_info(rdev->dev, "  CP_STALLED_STAT3 = 0x%08x\n",
		 RREG32(CP_STALLED_STAT3));
	dev_info(rdev->dev, "  CP_CPF_BUSY_STAT = 0x%08x\n",
		 RREG32(CP_CPF_BUSY_STAT));
	dev_info(rdev->dev, "  CP_CPF_STALLED_STAT1 = 0x%08x\n",
		 RREG32(CP_CPF_STALLED_STAT1));
	dev_info(rdev->dev, "  CP_CPF_STATUS = 0x%08x\n", RREG32(CP_CPF_STATUS));
	dev_info(rdev->dev, "  CP_CPC_BUSY_STAT = 0x%08x\n", RREG32(CP_CPC_BUSY_STAT));
	dev_info(rdev->dev, "  CP_CPC_STALLED_STAT1 = 0x%08x\n",
		 RREG32(CP_CPC_STALLED_STAT1));
	dev_info(rdev->dev, "  CP_CPC_STATUS = 0x%08x\n", RREG32(CP_CPC_STATUS));
पूर्ण

/**
 * cik_gpu_check_soft_reset - check which blocks are busy
 *
 * @rdev: radeon_device poपूर्णांकer
 *
 * Check which blocks are busy and वापस the relevant reset
 * mask to be used by cik_gpu_soft_reset().
 * Returns a mask of the blocks to be reset.
 */
u32 cik_gpu_check_soft_reset(काष्ठा radeon_device *rdev)
अणु
	u32 reset_mask = 0;
	u32 पंचांगp;

	/* GRBM_STATUS */
	पंचांगp = RREG32(GRBM_STATUS);
	अगर (पंचांगp & (PA_BUSY | SC_BUSY |
		   BCI_BUSY | SX_BUSY |
		   TA_BUSY | VGT_BUSY |
		   DB_BUSY | CB_BUSY |
		   GDS_BUSY | SPI_BUSY |
		   IA_BUSY | IA_BUSY_NO_DMA))
		reset_mask |= RADEON_RESET_GFX;

	अगर (पंचांगp & (CP_BUSY | CP_COHERENCY_BUSY))
		reset_mask |= RADEON_RESET_CP;

	/* GRBM_STATUS2 */
	पंचांगp = RREG32(GRBM_STATUS2);
	अगर (पंचांगp & RLC_BUSY)
		reset_mask |= RADEON_RESET_RLC;

	/* SDMA0_STATUS_REG */
	पंचांगp = RREG32(SDMA0_STATUS_REG + SDMA0_REGISTER_OFFSET);
	अगर (!(पंचांगp & SDMA_IDLE))
		reset_mask |= RADEON_RESET_DMA;

	/* SDMA1_STATUS_REG */
	पंचांगp = RREG32(SDMA0_STATUS_REG + SDMA1_REGISTER_OFFSET);
	अगर (!(पंचांगp & SDMA_IDLE))
		reset_mask |= RADEON_RESET_DMA1;

	/* SRBM_STATUS2 */
	पंचांगp = RREG32(SRBM_STATUS2);
	अगर (पंचांगp & SDMA_BUSY)
		reset_mask |= RADEON_RESET_DMA;

	अगर (पंचांगp & SDMA1_BUSY)
		reset_mask |= RADEON_RESET_DMA1;

	/* SRBM_STATUS */
	पंचांगp = RREG32(SRBM_STATUS);

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

	/* Skip MC reset as it's mostly likely not hung, just busy */
	अगर (reset_mask & RADEON_RESET_MC) अणु
		DRM_DEBUG("MC busy: 0x%08X, clearing.\n", reset_mask);
		reset_mask &= ~RADEON_RESET_MC;
	पूर्ण

	वापस reset_mask;
पूर्ण

/**
 * cik_gpu_soft_reset - soft reset GPU
 *
 * @rdev: radeon_device poपूर्णांकer
 * @reset_mask: mask of which blocks to reset
 *
 * Soft reset the blocks specअगरied in @reset_mask.
 */
अटल व्योम cik_gpu_soft_reset(काष्ठा radeon_device *rdev, u32 reset_mask)
अणु
	काष्ठा evergreen_mc_save save;
	u32 grbm_soft_reset = 0, srbm_soft_reset = 0;
	u32 पंचांगp;

	अगर (reset_mask == 0)
		वापस;

	dev_info(rdev->dev, "GPU softreset: 0x%08X\n", reset_mask);

	cik_prपूर्णांक_gpu_status_regs(rdev);
	dev_info(rdev->dev, "  VM_CONTEXT1_PROTECTION_FAULT_ADDR   0x%08X\n",
		 RREG32(VM_CONTEXT1_PROTECTION_FAULT_ADDR));
	dev_info(rdev->dev, "  VM_CONTEXT1_PROTECTION_FAULT_STATUS 0x%08X\n",
		 RREG32(VM_CONTEXT1_PROTECTION_FAULT_STATUS));

	/* disable CG/PG */
	cik_fini_pg(rdev);
	cik_fini_cg(rdev);

	/* stop the rlc */
	cik_rlc_stop(rdev);

	/* Disable GFX parsing/prefetching */
	WREG32(CP_ME_CNTL, CP_ME_HALT | CP_PFP_HALT | CP_CE_HALT);

	/* Disable MEC parsing/prefetching */
	WREG32(CP_MEC_CNTL, MEC_ME1_HALT | MEC_ME2_HALT);

	अगर (reset_mask & RADEON_RESET_DMA) अणु
		/* sdma0 */
		पंचांगp = RREG32(SDMA0_ME_CNTL + SDMA0_REGISTER_OFFSET);
		पंचांगp |= SDMA_HALT;
		WREG32(SDMA0_ME_CNTL + SDMA0_REGISTER_OFFSET, पंचांगp);
	पूर्ण
	अगर (reset_mask & RADEON_RESET_DMA1) अणु
		/* sdma1 */
		पंचांगp = RREG32(SDMA0_ME_CNTL + SDMA1_REGISTER_OFFSET);
		पंचांगp |= SDMA_HALT;
		WREG32(SDMA0_ME_CNTL + SDMA1_REGISTER_OFFSET, पंचांगp);
	पूर्ण

	evergreen_mc_stop(rdev, &save);
	अगर (evergreen_mc_रुको_क्रम_idle(rdev)) अणु
		dev_warn(rdev->dev, "Wait for MC idle timedout !\n");
	पूर्ण

	अगर (reset_mask & (RADEON_RESET_GFX | RADEON_RESET_COMPUTE | RADEON_RESET_CP))
		grbm_soft_reset = SOFT_RESET_CP | SOFT_RESET_GFX;

	अगर (reset_mask & RADEON_RESET_CP) अणु
		grbm_soft_reset |= SOFT_RESET_CP;

		srbm_soft_reset |= SOFT_RESET_GRBM;
	पूर्ण

	अगर (reset_mask & RADEON_RESET_DMA)
		srbm_soft_reset |= SOFT_RESET_SDMA;

	अगर (reset_mask & RADEON_RESET_DMA1)
		srbm_soft_reset |= SOFT_RESET_SDMA1;

	अगर (reset_mask & RADEON_RESET_DISPLAY)
		srbm_soft_reset |= SOFT_RESET_DC;

	अगर (reset_mask & RADEON_RESET_RLC)
		grbm_soft_reset |= SOFT_RESET_RLC;

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

	cik_prपूर्णांक_gpu_status_regs(rdev);
पूर्ण

काष्ठा kv_reset_save_regs अणु
	u32 gmcon_reng_execute;
	u32 gmcon_misc;
	u32 gmcon_misc3;
पूर्ण;

अटल व्योम kv_save_regs_क्रम_reset(काष्ठा radeon_device *rdev,
				   काष्ठा kv_reset_save_regs *save)
अणु
	save->gmcon_reng_execute = RREG32(GMCON_RENG_EXECUTE);
	save->gmcon_misc = RREG32(GMCON_MISC);
	save->gmcon_misc3 = RREG32(GMCON_MISC3);

	WREG32(GMCON_RENG_EXECUTE, save->gmcon_reng_execute & ~RENG_EXECUTE_ON_PWR_UP);
	WREG32(GMCON_MISC, save->gmcon_misc & ~(RENG_EXECUTE_ON_REG_UPDATE |
						STCTRL_STUTTER_EN));
पूर्ण

अटल व्योम kv_restore_regs_क्रम_reset(काष्ठा radeon_device *rdev,
				      काष्ठा kv_reset_save_regs *save)
अणु
	पूर्णांक i;

	WREG32(GMCON_PGFSM_WRITE, 0);
	WREG32(GMCON_PGFSM_CONFIG, 0x200010ff);

	क्रम (i = 0; i < 5; i++)
		WREG32(GMCON_PGFSM_WRITE, 0);

	WREG32(GMCON_PGFSM_WRITE, 0);
	WREG32(GMCON_PGFSM_CONFIG, 0x300010ff);

	क्रम (i = 0; i < 5; i++)
		WREG32(GMCON_PGFSM_WRITE, 0);

	WREG32(GMCON_PGFSM_WRITE, 0x210000);
	WREG32(GMCON_PGFSM_CONFIG, 0xa00010ff);

	क्रम (i = 0; i < 5; i++)
		WREG32(GMCON_PGFSM_WRITE, 0);

	WREG32(GMCON_PGFSM_WRITE, 0x21003);
	WREG32(GMCON_PGFSM_CONFIG, 0xb00010ff);

	क्रम (i = 0; i < 5; i++)
		WREG32(GMCON_PGFSM_WRITE, 0);

	WREG32(GMCON_PGFSM_WRITE, 0x2b00);
	WREG32(GMCON_PGFSM_CONFIG, 0xc00010ff);

	क्रम (i = 0; i < 5; i++)
		WREG32(GMCON_PGFSM_WRITE, 0);

	WREG32(GMCON_PGFSM_WRITE, 0);
	WREG32(GMCON_PGFSM_CONFIG, 0xd00010ff);

	क्रम (i = 0; i < 5; i++)
		WREG32(GMCON_PGFSM_WRITE, 0);

	WREG32(GMCON_PGFSM_WRITE, 0x420000);
	WREG32(GMCON_PGFSM_CONFIG, 0x100010ff);

	क्रम (i = 0; i < 5; i++)
		WREG32(GMCON_PGFSM_WRITE, 0);

	WREG32(GMCON_PGFSM_WRITE, 0x120202);
	WREG32(GMCON_PGFSM_CONFIG, 0x500010ff);

	क्रम (i = 0; i < 5; i++)
		WREG32(GMCON_PGFSM_WRITE, 0);

	WREG32(GMCON_PGFSM_WRITE, 0x3e3e36);
	WREG32(GMCON_PGFSM_CONFIG, 0x600010ff);

	क्रम (i = 0; i < 5; i++)
		WREG32(GMCON_PGFSM_WRITE, 0);

	WREG32(GMCON_PGFSM_WRITE, 0x373f3e);
	WREG32(GMCON_PGFSM_CONFIG, 0x700010ff);

	क्रम (i = 0; i < 5; i++)
		WREG32(GMCON_PGFSM_WRITE, 0);

	WREG32(GMCON_PGFSM_WRITE, 0x3e1332);
	WREG32(GMCON_PGFSM_CONFIG, 0xe00010ff);

	WREG32(GMCON_MISC3, save->gmcon_misc3);
	WREG32(GMCON_MISC, save->gmcon_misc);
	WREG32(GMCON_RENG_EXECUTE, save->gmcon_reng_execute);
पूर्ण

अटल व्योम cik_gpu_pci_config_reset(काष्ठा radeon_device *rdev)
अणु
	काष्ठा evergreen_mc_save save;
	काष्ठा kv_reset_save_regs kv_save = अणु 0 पूर्ण;
	u32 पंचांगp, i;

	dev_info(rdev->dev, "GPU pci config reset\n");

	/* disable dpm? */

	/* disable cg/pg */
	cik_fini_pg(rdev);
	cik_fini_cg(rdev);

	/* Disable GFX parsing/prefetching */
	WREG32(CP_ME_CNTL, CP_ME_HALT | CP_PFP_HALT | CP_CE_HALT);

	/* Disable MEC parsing/prefetching */
	WREG32(CP_MEC_CNTL, MEC_ME1_HALT | MEC_ME2_HALT);

	/* sdma0 */
	पंचांगp = RREG32(SDMA0_ME_CNTL + SDMA0_REGISTER_OFFSET);
	पंचांगp |= SDMA_HALT;
	WREG32(SDMA0_ME_CNTL + SDMA0_REGISTER_OFFSET, पंचांगp);
	/* sdma1 */
	पंचांगp = RREG32(SDMA0_ME_CNTL + SDMA1_REGISTER_OFFSET);
	पंचांगp |= SDMA_HALT;
	WREG32(SDMA0_ME_CNTL + SDMA1_REGISTER_OFFSET, पंचांगp);
	/* XXX other engines? */

	/* halt the rlc, disable cp पूर्णांकernal पूर्णांकs */
	cik_rlc_stop(rdev);

	udelay(50);

	/* disable mem access */
	evergreen_mc_stop(rdev, &save);
	अगर (evergreen_mc_रुको_क्रम_idle(rdev)) अणु
		dev_warn(rdev->dev, "Wait for MC idle timed out !\n");
	पूर्ण

	अगर (rdev->flags & RADEON_IS_IGP)
		kv_save_regs_क्रम_reset(rdev, &kv_save);

	/* disable BM */
	pci_clear_master(rdev->pdev);
	/* reset */
	radeon_pci_config_reset(rdev);

	udelay(100);

	/* रुको क्रम asic to come out of reset */
	क्रम (i = 0; i < rdev->usec_समयout; i++) अणु
		अगर (RREG32(CONFIG_MEMSIZE) != 0xffffffff)
			अवरोध;
		udelay(1);
	पूर्ण

	/* करोes asic init need to be run first??? */
	अगर (rdev->flags & RADEON_IS_IGP)
		kv_restore_regs_क्रम_reset(rdev, &kv_save);
पूर्ण

/**
 * cik_asic_reset - soft reset GPU
 *
 * @rdev: radeon_device poपूर्णांकer
 * @hard: क्रमce hard reset
 *
 * Look up which blocks are hung and attempt
 * to reset them.
 * Returns 0 क्रम success.
 */
पूर्णांक cik_asic_reset(काष्ठा radeon_device *rdev, bool hard)
अणु
	u32 reset_mask;

	अगर (hard) अणु
		cik_gpu_pci_config_reset(rdev);
		वापस 0;
	पूर्ण

	reset_mask = cik_gpu_check_soft_reset(rdev);

	अगर (reset_mask)
		r600_set_bios_scratch_engine_hung(rdev, true);

	/* try soft reset */
	cik_gpu_soft_reset(rdev, reset_mask);

	reset_mask = cik_gpu_check_soft_reset(rdev);

	/* try pci config reset */
	अगर (reset_mask && radeon_hard_reset)
		cik_gpu_pci_config_reset(rdev);

	reset_mask = cik_gpu_check_soft_reset(rdev);

	अगर (!reset_mask)
		r600_set_bios_scratch_engine_hung(rdev, false);

	वापस 0;
पूर्ण

/**
 * cik_gfx_is_lockup - check अगर the 3D engine is locked up
 *
 * @rdev: radeon_device poपूर्णांकer
 * @ring: radeon_ring काष्ठाure holding ring inक्रमmation
 *
 * Check अगर the 3D engine is locked up (CIK).
 * Returns true अगर the engine is locked, false अगर not.
 */
bool cik_gfx_is_lockup(काष्ठा radeon_device *rdev, काष्ठा radeon_ring *ring)
अणु
	u32 reset_mask = cik_gpu_check_soft_reset(rdev);

	अगर (!(reset_mask & (RADEON_RESET_GFX |
			    RADEON_RESET_COMPUTE |
			    RADEON_RESET_CP))) अणु
		radeon_ring_lockup_update(rdev, ring);
		वापस false;
	पूर्ण
	वापस radeon_ring_test_lockup(rdev, ring);
पूर्ण

/* MC */
/**
 * cik_mc_program - program the GPU memory controller
 *
 * @rdev: radeon_device poपूर्णांकer
 *
 * Set the location of vram, gart, and AGP in the GPU's
 * physical address space (CIK).
 */
अटल व्योम cik_mc_program(काष्ठा radeon_device *rdev)
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
	अगर (radeon_mc_रुको_क्रम_idle(rdev)) अणु
		dev_warn(rdev->dev, "Wait for MC idle timedout !\n");
	पूर्ण
	/* Lockout access through VGA aperture*/
	WREG32(VGA_HDP_CONTROL, VGA_MEMORY_DISABLE);
	/* Update configuration */
	WREG32(MC_VM_SYSTEM_APERTURE_LOW_ADDR,
	       rdev->mc.vram_start >> 12);
	WREG32(MC_VM_SYSTEM_APERTURE_HIGH_ADDR,
	       rdev->mc.vram_end >> 12);
	WREG32(MC_VM_SYSTEM_APERTURE_DEFAULT_ADDR,
	       rdev->vram_scratch.gpu_addr >> 12);
	पंचांगp = ((rdev->mc.vram_end >> 24) & 0xFFFF) << 16;
	पंचांगp |= ((rdev->mc.vram_start >> 24) & 0xFFFF);
	WREG32(MC_VM_FB_LOCATION, पंचांगp);
	/* XXX द्विगुन check these! */
	WREG32(HDP_NONSURFACE_BASE, (rdev->mc.vram_start >> 8));
	WREG32(HDP_NONSURFACE_INFO, (2 << 7) | (1 << 30));
	WREG32(HDP_NONSURFACE_SIZE, 0x3FFFFFFF);
	WREG32(MC_VM_AGP_BASE, 0);
	WREG32(MC_VM_AGP_TOP, 0x0FFFFFFF);
	WREG32(MC_VM_AGP_BOT, 0x0FFFFFFF);
	अगर (radeon_mc_रुको_क्रम_idle(rdev)) अणु
		dev_warn(rdev->dev, "Wait for MC idle timedout !\n");
	पूर्ण
	evergreen_mc_resume(rdev, &save);
	/* we need to own VRAM, so turn off the VGA renderer here
	 * to stop it overwriting our objects */
	rv515_vga_render_disable(rdev);
पूर्ण

/**
 * cik_mc_init - initialize the memory controller driver params
 *
 * @rdev: radeon_device poपूर्णांकer
 *
 * Look up the amount of vram, vram width, and decide how to place
 * vram and gart within the GPU's physical address space (CIK).
 * Returns 0 क्रम success.
 */
अटल पूर्णांक cik_mc_init(काष्ठा radeon_device *rdev)
अणु
	u32 पंचांगp;
	पूर्णांक chansize, numchan;

	/* Get VRAM inक्रमmations */
	rdev->mc.vram_is_ddr = true;
	पंचांगp = RREG32(MC_ARB_RAMCFG);
	अगर (पंचांगp & CHANSIZE_MASK) अणु
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
	हाल 4:
		numchan = 3;
		अवरोध;
	हाल 5:
		numchan = 6;
		अवरोध;
	हाल 6:
		numchan = 10;
		अवरोध;
	हाल 7:
		numchan = 12;
		अवरोध;
	हाल 8:
		numchan = 16;
		अवरोध;
	पूर्ण
	rdev->mc.vram_width = numchan * chansize;
	/* Could aper size report 0 ? */
	rdev->mc.aper_base = pci_resource_start(rdev->pdev, 0);
	rdev->mc.aper_size = pci_resource_len(rdev->pdev, 0);
	/* size in MB on si */
	rdev->mc.mc_vram_size = RREG32(CONFIG_MEMSIZE) * 1024ULL * 1024ULL;
	rdev->mc.real_vram_size = RREG32(CONFIG_MEMSIZE) * 1024ULL * 1024ULL;
	rdev->mc.visible_vram_size = rdev->mc.aper_size;
	si_vram_gtt_location(rdev, &rdev->mc);
	radeon_update_bandwidth_info(rdev);

	वापस 0;
पूर्ण

/*
 * GART
 * VMID 0 is the physical GPU addresses as used by the kernel.
 * VMIDs 1-15 are used क्रम userspace clients and are handled
 * by the radeon vm/hsa code.
 */
/**
 * cik_pcie_gart_tlb_flush - gart tlb flush callback
 *
 * @rdev: radeon_device poपूर्णांकer
 *
 * Flush the TLB क्रम the VMID 0 page table (CIK).
 */
व्योम cik_pcie_gart_tlb_flush(काष्ठा radeon_device *rdev)
अणु
	/* flush hdp cache */
	WREG32(HDP_MEM_COHERENCY_FLUSH_CNTL, 0);

	/* bits 0-15 are the VM contexts0-15 */
	WREG32(VM_INVALIDATE_REQUEST, 0x1);
पूर्ण

/**
 * cik_pcie_gart_enable - gart enable
 *
 * @rdev: radeon_device poपूर्णांकer
 *
 * This sets up the TLBs, programs the page tables क्रम VMID0,
 * sets up the hw क्रम VMIDs 1-15 which are allocated on
 * demand, and sets up the global locations क्रम the LDS, GDS,
 * and GPUVM क्रम FSA64 clients (CIK).
 * Returns 0 क्रम success, errors क्रम failure.
 */
अटल पूर्णांक cik_pcie_gart_enable(काष्ठा radeon_device *rdev)
अणु
	पूर्णांक r, i;

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
	       BANK_SELECT(4) |
	       L2_CACHE_BIGK_FRAGMENT_SIZE(4));
	/* setup context0 */
	WREG32(VM_CONTEXT0_PAGE_TABLE_START_ADDR, rdev->mc.gtt_start >> 12);
	WREG32(VM_CONTEXT0_PAGE_TABLE_END_ADDR, rdev->mc.gtt_end >> 12);
	WREG32(VM_CONTEXT0_PAGE_TABLE_BASE_ADDR, rdev->gart.table_addr >> 12);
	WREG32(VM_CONTEXT0_PROTECTION_FAULT_DEFAULT_ADDR,
			(u32)(rdev->dummy_page.addr >> 12));
	WREG32(VM_CONTEXT0_CNTL2, 0);
	WREG32(VM_CONTEXT0_CNTL, (ENABLE_CONTEXT | PAGE_TABLE_DEPTH(0) |
				  RANGE_PROTECTION_FAULT_ENABLE_DEFAULT));

	WREG32(0x15D4, 0);
	WREG32(0x15D8, 0);
	WREG32(0x15DC, 0);

	/* restore context1-15 */
	/* set vm size, must be a multiple of 4 */
	WREG32(VM_CONTEXT1_PAGE_TABLE_START_ADDR, 0);
	WREG32(VM_CONTEXT1_PAGE_TABLE_END_ADDR, rdev->vm_manager.max_pfn - 1);
	क्रम (i = 1; i < 16; i++) अणु
		अगर (i < 8)
			WREG32(VM_CONTEXT0_PAGE_TABLE_BASE_ADDR + (i << 2),
			       rdev->vm_manager.saved_table_addr[i]);
		अन्यथा
			WREG32(VM_CONTEXT8_PAGE_TABLE_BASE_ADDR + ((i - 8) << 2),
			       rdev->vm_manager.saved_table_addr[i]);
	पूर्ण

	/* enable context1-15 */
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

	अगर (rdev->family == CHIP_KAVERI) अणु
		u32 पंचांगp = RREG32(CHUB_CONTROL);
		पंचांगp &= ~BYPASS_VM;
		WREG32(CHUB_CONTROL, पंचांगp);
	पूर्ण

	/* XXX SH_MEM regs */
	/* where to put LDS, scratch, GPUVM in FSA64 space */
	mutex_lock(&rdev->srbm_mutex);
	क्रम (i = 0; i < 16; i++) अणु
		cik_srbm_select(rdev, 0, 0, 0, i);
		/* CP and shaders */
		WREG32(SH_MEM_CONFIG, SH_MEM_CONFIG_GFX_DEFAULT);
		WREG32(SH_MEM_APE1_BASE, 1);
		WREG32(SH_MEM_APE1_LIMIT, 0);
		WREG32(SH_MEM_BASES, 0);
		/* SDMA GFX */
		WREG32(SDMA0_GFX_VIRTUAL_ADDR + SDMA0_REGISTER_OFFSET, 0);
		WREG32(SDMA0_GFX_APE1_CNTL + SDMA0_REGISTER_OFFSET, 0);
		WREG32(SDMA0_GFX_VIRTUAL_ADDR + SDMA1_REGISTER_OFFSET, 0);
		WREG32(SDMA0_GFX_APE1_CNTL + SDMA1_REGISTER_OFFSET, 0);
		/* XXX SDMA RLC - toकरो */
	पूर्ण
	cik_srbm_select(rdev, 0, 0, 0, 0);
	mutex_unlock(&rdev->srbm_mutex);

	cik_pcie_gart_tlb_flush(rdev);
	DRM_INFO("PCIE GART of %uM enabled (table at 0x%016llX).\n",
		 (अचिन्हित)(rdev->mc.gtt_size >> 20),
		 (अचिन्हित दीर्घ दीर्घ)rdev->gart.table_addr);
	rdev->gart.पढ़ोy = true;
	वापस 0;
पूर्ण

/**
 * cik_pcie_gart_disable - gart disable
 *
 * @rdev: radeon_device poपूर्णांकer
 *
 * This disables all VM page table (CIK).
 */
अटल व्योम cik_pcie_gart_disable(काष्ठा radeon_device *rdev)
अणु
	अचिन्हित i;

	क्रम (i = 1; i < 16; ++i) अणु
		uपूर्णांक32_t reg;
		अगर (i < 8)
			reg = VM_CONTEXT0_PAGE_TABLE_BASE_ADDR + (i << 2);
		अन्यथा
			reg = VM_CONTEXT8_PAGE_TABLE_BASE_ADDR + ((i - 8) << 2);
		rdev->vm_manager.saved_table_addr[i] = RREG32(reg);
	पूर्ण

	/* Disable all tables */
	WREG32(VM_CONTEXT0_CNTL, 0);
	WREG32(VM_CONTEXT1_CNTL, 0);
	/* Setup TLB control */
	WREG32(MC_VM_MX_L1_TLB_CNTL, SYSTEM_ACCESS_MODE_NOT_IN_SYS |
	       SYSTEM_APERTURE_UNMAPPED_ACCESS_PASS_THRU);
	/* Setup L2 cache */
	WREG32(VM_L2_CNTL,
	       ENABLE_L2_FRAGMENT_PROCESSING |
	       ENABLE_L2_PTE_CACHE_LRU_UPDATE_BY_WRITE |
	       ENABLE_L2_PDE0_CACHE_LRU_UPDATE_BY_WRITE |
	       EFFECTIVE_L2_QUEUE_SIZE(7) |
	       CONTEXT1_IDENTITY_ACCESS_MODE(1));
	WREG32(VM_L2_CNTL2, 0);
	WREG32(VM_L2_CNTL3, L2_CACHE_BIGK_ASSOCIATIVITY |
	       L2_CACHE_BIGK_FRAGMENT_SIZE(6));
	radeon_gart_table_vram_unpin(rdev);
पूर्ण

/**
 * cik_pcie_gart_fini - vm fini callback
 *
 * @rdev: radeon_device poपूर्णांकer
 *
 * Tears करोwn the driver GART/VM setup (CIK).
 */
अटल व्योम cik_pcie_gart_fini(काष्ठा radeon_device *rdev)
अणु
	cik_pcie_gart_disable(rdev);
	radeon_gart_table_vram_मुक्त(rdev);
	radeon_gart_fini(rdev);
पूर्ण

/* vm parser */
/**
 * cik_ib_parse - vm ib_parse callback
 *
 * @rdev: radeon_device poपूर्णांकer
 * @ib: indirect buffer poपूर्णांकer
 *
 * CIK uses hw IB checking so this is a nop (CIK).
 */
पूर्णांक cik_ib_parse(काष्ठा radeon_device *rdev, काष्ठा radeon_ib *ib)
अणु
	वापस 0;
पूर्ण

/*
 * vm
 * VMID 0 is the physical GPU addresses as used by the kernel.
 * VMIDs 1-15 are used क्रम userspace clients and are handled
 * by the radeon vm/hsa code.
 */
/**
 * cik_vm_init - cik vm init callback
 *
 * @rdev: radeon_device poपूर्णांकer
 *
 * Inits cik specअगरic vm parameters (number of VMs, base of vram क्रम
 * VMIDs 1-15) (CIK).
 * Returns 0 क्रम success.
 */
पूर्णांक cik_vm_init(काष्ठा radeon_device *rdev)
अणु
	/*
	 * number of VMs
	 * VMID 0 is reserved क्रम System
	 * radeon graphics/compute will use VMIDs 1-15
	 */
	rdev->vm_manager.nvm = 16;
	/* base offset of vram pages */
	अगर (rdev->flags & RADEON_IS_IGP) अणु
		u64 पंचांगp = RREG32(MC_VM_FB_OFFSET);
		पंचांगp <<= 22;
		rdev->vm_manager.vram_base_offset = पंचांगp;
	पूर्ण अन्यथा
		rdev->vm_manager.vram_base_offset = 0;

	वापस 0;
पूर्ण

/**
 * cik_vm_fini - cik vm fini callback
 *
 * @rdev: radeon_device poपूर्णांकer
 *
 * Tear करोwn any asic specअगरic VM setup (CIK).
 */
व्योम cik_vm_fini(काष्ठा radeon_device *rdev)
अणु
पूर्ण

/**
 * cik_vm_decode_fault - prपूर्णांक human पढ़ोable fault info
 *
 * @rdev: radeon_device poपूर्णांकer
 * @status: VM_CONTEXT1_PROTECTION_FAULT_STATUS रेजिस्टर value
 * @addr: VM_CONTEXT1_PROTECTION_FAULT_ADDR रेजिस्टर value
 * @mc_client: VM_CONTEXT1_PROTECTION_FAULT_MCCLIENT रेजिस्टर value
 *
 * Prपूर्णांक human पढ़ोable fault inक्रमmation (CIK).
 */
अटल व्योम cik_vm_decode_fault(काष्ठा radeon_device *rdev,
				u32 status, u32 addr, u32 mc_client)
अणु
	u32 mc_id;
	u32 vmid = (status & FAULT_VMID_MASK) >> FAULT_VMID_SHIFT;
	u32 protections = (status & PROTECTIONS_MASK) >> PROTECTIONS_SHIFT;
	अक्षर block[5] = अणु mc_client >> 24, (mc_client >> 16) & 0xff,
		(mc_client >> 8) & 0xff, mc_client & 0xff, 0 पूर्ण;

	अगर (rdev->family == CHIP_HAWAII)
		mc_id = (status & HAWAII_MEMORY_CLIENT_ID_MASK) >> MEMORY_CLIENT_ID_SHIFT;
	अन्यथा
		mc_id = (status & MEMORY_CLIENT_ID_MASK) >> MEMORY_CLIENT_ID_SHIFT;

	prपूर्णांकk("VM fault (0x%02x, vmid %d) at page %u, %s from '%s' (0x%08x) (%d)\n",
	       protections, vmid, addr,
	       (status & MEMORY_CLIENT_RW_MASK) ? "write" : "read",
	       block, mc_client, mc_id);
पूर्ण

/*
 * cik_vm_flush - cik vm flush using the CP
 *
 * Update the page table base and flush the VM TLB
 * using the CP (CIK).
 */
व्योम cik_vm_flush(काष्ठा radeon_device *rdev, काष्ठा radeon_ring *ring,
		  अचिन्हित vm_id, uपूर्णांक64_t pd_addr)
अणु
	पूर्णांक usepfp = (ring->idx == RADEON_RING_TYPE_GFX_INDEX);

	radeon_ring_ग_लिखो(ring, PACKET3(PACKET3_WRITE_DATA, 3));
	radeon_ring_ग_लिखो(ring, (WRITE_DATA_ENGINE_SEL(usepfp) |
				 WRITE_DATA_DST_SEL(0)));
	अगर (vm_id < 8) अणु
		radeon_ring_ग_लिखो(ring,
				  (VM_CONTEXT0_PAGE_TABLE_BASE_ADDR + (vm_id << 2)) >> 2);
	पूर्ण अन्यथा अणु
		radeon_ring_ग_लिखो(ring,
				  (VM_CONTEXT8_PAGE_TABLE_BASE_ADDR + ((vm_id - 8) << 2)) >> 2);
	पूर्ण
	radeon_ring_ग_लिखो(ring, 0);
	radeon_ring_ग_लिखो(ring, pd_addr >> 12);

	/* update SH_MEM_* regs */
	radeon_ring_ग_लिखो(ring, PACKET3(PACKET3_WRITE_DATA, 3));
	radeon_ring_ग_लिखो(ring, (WRITE_DATA_ENGINE_SEL(usepfp) |
				 WRITE_DATA_DST_SEL(0)));
	radeon_ring_ग_लिखो(ring, SRBM_GFX_CNTL >> 2);
	radeon_ring_ग_लिखो(ring, 0);
	radeon_ring_ग_लिखो(ring, VMID(vm_id));

	radeon_ring_ग_लिखो(ring, PACKET3(PACKET3_WRITE_DATA, 6));
	radeon_ring_ग_लिखो(ring, (WRITE_DATA_ENGINE_SEL(usepfp) |
				 WRITE_DATA_DST_SEL(0)));
	radeon_ring_ग_लिखो(ring, SH_MEM_BASES >> 2);
	radeon_ring_ग_लिखो(ring, 0);

	radeon_ring_ग_लिखो(ring, 0); /* SH_MEM_BASES */
	radeon_ring_ग_लिखो(ring, SH_MEM_CONFIG_GFX_DEFAULT); /* SH_MEM_CONFIG */
	radeon_ring_ग_लिखो(ring, 1); /* SH_MEM_APE1_BASE */
	radeon_ring_ग_लिखो(ring, 0); /* SH_MEM_APE1_LIMIT */

	radeon_ring_ग_लिखो(ring, PACKET3(PACKET3_WRITE_DATA, 3));
	radeon_ring_ग_लिखो(ring, (WRITE_DATA_ENGINE_SEL(usepfp) |
				 WRITE_DATA_DST_SEL(0)));
	radeon_ring_ग_लिखो(ring, SRBM_GFX_CNTL >> 2);
	radeon_ring_ग_लिखो(ring, 0);
	radeon_ring_ग_लिखो(ring, VMID(0));

	/* HDP flush */
	cik_hdp_flush_cp_ring_emit(rdev, ring->idx);

	/* bits 0-15 are the VM contexts0-15 */
	radeon_ring_ग_लिखो(ring, PACKET3(PACKET3_WRITE_DATA, 3));
	radeon_ring_ग_लिखो(ring, (WRITE_DATA_ENGINE_SEL(usepfp) |
				 WRITE_DATA_DST_SEL(0)));
	radeon_ring_ग_लिखो(ring, VM_INVALIDATE_REQUEST >> 2);
	radeon_ring_ग_लिखो(ring, 0);
	radeon_ring_ग_लिखो(ring, 1 << vm_id);

	/* रुको क्रम the invalidate to complete */
	radeon_ring_ग_लिखो(ring, PACKET3(PACKET3_WAIT_REG_MEM, 5));
	radeon_ring_ग_लिखो(ring, (WAIT_REG_MEM_OPERATION(0) | /* रुको */
				 WAIT_REG_MEM_FUNCTION(0) |  /* always */
				 WAIT_REG_MEM_ENGINE(0))); /* me */
	radeon_ring_ग_लिखो(ring, VM_INVALIDATE_REQUEST >> 2);
	radeon_ring_ग_लिखो(ring, 0);
	radeon_ring_ग_लिखो(ring, 0); /* ref */
	radeon_ring_ग_लिखो(ring, 0); /* mask */
	radeon_ring_ग_लिखो(ring, 0x20); /* poll पूर्णांकerval */

	/* compute करोesn't have PFP */
	अगर (usepfp) अणु
		/* sync PFP to ME, otherwise we might get invalid PFP पढ़ोs */
		radeon_ring_ग_लिखो(ring, PACKET3(PACKET3_PFP_SYNC_ME, 0));
		radeon_ring_ग_लिखो(ring, 0x0);
	पूर्ण
पूर्ण

/*
 * RLC
 * The RLC is a multi-purpose microengine that handles a
 * variety of functions, the most important of which is
 * the पूर्णांकerrupt controller.
 */
अटल व्योम cik_enable_gui_idle_पूर्णांकerrupt(काष्ठा radeon_device *rdev,
					  bool enable)
अणु
	u32 पंचांगp = RREG32(CP_INT_CNTL_RING0);

	अगर (enable)
		पंचांगp |= (CNTX_BUSY_INT_ENABLE | CNTX_EMPTY_INT_ENABLE);
	अन्यथा
		पंचांगp &= ~(CNTX_BUSY_INT_ENABLE | CNTX_EMPTY_INT_ENABLE);
	WREG32(CP_INT_CNTL_RING0, पंचांगp);
पूर्ण

अटल व्योम cik_enable_lbpw(काष्ठा radeon_device *rdev, bool enable)
अणु
	u32 पंचांगp;

	पंचांगp = RREG32(RLC_LB_CNTL);
	अगर (enable)
		पंचांगp |= LOAD_BALANCE_ENABLE;
	अन्यथा
		पंचांगp &= ~LOAD_BALANCE_ENABLE;
	WREG32(RLC_LB_CNTL, पंचांगp);
पूर्ण

अटल व्योम cik_रुको_क्रम_rlc_serdes(काष्ठा radeon_device *rdev)
अणु
	u32 i, j, k;
	u32 mask;

	क्रम (i = 0; i < rdev->config.cik.max_shader_engines; i++) अणु
		क्रम (j = 0; j < rdev->config.cik.max_sh_per_se; j++) अणु
			cik_select_se_sh(rdev, i, j);
			क्रम (k = 0; k < rdev->usec_समयout; k++) अणु
				अगर (RREG32(RLC_SERDES_CU_MASTER_BUSY) == 0)
					अवरोध;
				udelay(1);
			पूर्ण
		पूर्ण
	पूर्ण
	cik_select_se_sh(rdev, 0xffffffff, 0xffffffff);

	mask = SE_MASTER_BUSY_MASK | GC_MASTER_BUSY | TC0_MASTER_BUSY | TC1_MASTER_BUSY;
	क्रम (k = 0; k < rdev->usec_समयout; k++) अणु
		अगर ((RREG32(RLC_SERDES_NONCU_MASTER_BUSY) & mask) == 0)
			अवरोध;
		udelay(1);
	पूर्ण
पूर्ण

अटल व्योम cik_update_rlc(काष्ठा radeon_device *rdev, u32 rlc)
अणु
	u32 पंचांगp;

	पंचांगp = RREG32(RLC_CNTL);
	अगर (पंचांगp != rlc)
		WREG32(RLC_CNTL, rlc);
पूर्ण

अटल u32 cik_halt_rlc(काष्ठा radeon_device *rdev)
अणु
	u32 data, orig;

	orig = data = RREG32(RLC_CNTL);

	अगर (data & RLC_ENABLE) अणु
		u32 i;

		data &= ~RLC_ENABLE;
		WREG32(RLC_CNTL, data);

		क्रम (i = 0; i < rdev->usec_समयout; i++) अणु
			अगर ((RREG32(RLC_GPM_STAT) & RLC_GPM_BUSY) == 0)
				अवरोध;
			udelay(1);
		पूर्ण

		cik_रुको_क्रम_rlc_serdes(rdev);
	पूर्ण

	वापस orig;
पूर्ण

व्योम cik_enter_rlc_safe_mode(काष्ठा radeon_device *rdev)
अणु
	u32 पंचांगp, i, mask;

	पंचांगp = REQ | MESSAGE(MSG_ENTER_RLC_SAFE_MODE);
	WREG32(RLC_GPR_REG2, पंचांगp);

	mask = GFX_POWER_STATUS | GFX_CLOCK_STATUS;
	क्रम (i = 0; i < rdev->usec_समयout; i++) अणु
		अगर ((RREG32(RLC_GPM_STAT) & mask) == mask)
			अवरोध;
		udelay(1);
	पूर्ण

	क्रम (i = 0; i < rdev->usec_समयout; i++) अणु
		अगर ((RREG32(RLC_GPR_REG2) & REQ) == 0)
			अवरोध;
		udelay(1);
	पूर्ण
पूर्ण

व्योम cik_निकास_rlc_safe_mode(काष्ठा radeon_device *rdev)
अणु
	u32 पंचांगp;

	पंचांगp = REQ | MESSAGE(MSG_EXIT_RLC_SAFE_MODE);
	WREG32(RLC_GPR_REG2, पंचांगp);
पूर्ण

/**
 * cik_rlc_stop - stop the RLC ME
 *
 * @rdev: radeon_device poपूर्णांकer
 *
 * Halt the RLC ME (MicroEngine) (CIK).
 */
अटल व्योम cik_rlc_stop(काष्ठा radeon_device *rdev)
अणु
	WREG32(RLC_CNTL, 0);

	cik_enable_gui_idle_पूर्णांकerrupt(rdev, false);

	cik_रुको_क्रम_rlc_serdes(rdev);
पूर्ण

/**
 * cik_rlc_start - start the RLC ME
 *
 * @rdev: radeon_device poपूर्णांकer
 *
 * Unhalt the RLC ME (MicroEngine) (CIK).
 */
अटल व्योम cik_rlc_start(काष्ठा radeon_device *rdev)
अणु
	WREG32(RLC_CNTL, RLC_ENABLE);

	cik_enable_gui_idle_पूर्णांकerrupt(rdev, true);

	udelay(50);
पूर्ण

/**
 * cik_rlc_resume - setup the RLC hw
 *
 * @rdev: radeon_device poपूर्णांकer
 *
 * Initialize the RLC रेजिस्टरs, load the ucode,
 * and start the RLC (CIK).
 * Returns 0 क्रम success, -EINVAL अगर the ucode is not available.
 */
अटल पूर्णांक cik_rlc_resume(काष्ठा radeon_device *rdev)
अणु
	u32 i, size, पंचांगp;

	अगर (!rdev->rlc_fw)
		वापस -EINVAL;

	cik_rlc_stop(rdev);

	/* disable CG */
	पंचांगp = RREG32(RLC_CGCG_CGLS_CTRL) & 0xfffffffc;
	WREG32(RLC_CGCG_CGLS_CTRL, पंचांगp);

	si_rlc_reset(rdev);

	cik_init_pg(rdev);

	cik_init_cg(rdev);

	WREG32(RLC_LB_CNTR_INIT, 0);
	WREG32(RLC_LB_CNTR_MAX, 0x00008000);

	cik_select_se_sh(rdev, 0xffffffff, 0xffffffff);
	WREG32(RLC_LB_INIT_CU_MASK, 0xffffffff);
	WREG32(RLC_LB_PARAMS, 0x00600408);
	WREG32(RLC_LB_CNTL, 0x80000004);

	WREG32(RLC_MC_CNTL, 0);
	WREG32(RLC_UCODE_CNTL, 0);

	अगर (rdev->new_fw) अणु
		स्थिर काष्ठा rlc_firmware_header_v1_0 *hdr =
			(स्थिर काष्ठा rlc_firmware_header_v1_0 *)rdev->rlc_fw->data;
		स्थिर __le32 *fw_data = (स्थिर __le32 *)
			(rdev->rlc_fw->data + le32_to_cpu(hdr->header.ucode_array_offset_bytes));

		radeon_ucode_prपूर्णांक_rlc_hdr(&hdr->header);

		size = le32_to_cpu(hdr->header.ucode_size_bytes) / 4;
		WREG32(RLC_GPM_UCODE_ADDR, 0);
		क्रम (i = 0; i < size; i++)
			WREG32(RLC_GPM_UCODE_DATA, le32_to_cpup(fw_data++));
		WREG32(RLC_GPM_UCODE_ADDR, le32_to_cpu(hdr->header.ucode_version));
	पूर्ण अन्यथा अणु
		स्थिर __be32 *fw_data;

		चयन (rdev->family) अणु
		हाल CHIP_BONAIRE:
		हाल CHIP_HAWAII:
		शेष:
			size = BONAIRE_RLC_UCODE_SIZE;
			अवरोध;
		हाल CHIP_KAVERI:
			size = KV_RLC_UCODE_SIZE;
			अवरोध;
		हाल CHIP_KABINI:
			size = KB_RLC_UCODE_SIZE;
			अवरोध;
		हाल CHIP_MULLINS:
			size = ML_RLC_UCODE_SIZE;
			अवरोध;
		पूर्ण

		fw_data = (स्थिर __be32 *)rdev->rlc_fw->data;
		WREG32(RLC_GPM_UCODE_ADDR, 0);
		क्रम (i = 0; i < size; i++)
			WREG32(RLC_GPM_UCODE_DATA, be32_to_cpup(fw_data++));
		WREG32(RLC_GPM_UCODE_ADDR, 0);
	पूर्ण

	/* XXX - find out what chips support lbpw */
	cik_enable_lbpw(rdev, false);

	अगर (rdev->family == CHIP_BONAIRE)
		WREG32(RLC_DRIVER_DMA_STATUS, 0);

	cik_rlc_start(rdev);

	वापस 0;
पूर्ण

अटल व्योम cik_enable_cgcg(काष्ठा radeon_device *rdev, bool enable)
अणु
	u32 data, orig, पंचांगp, पंचांगp2;

	orig = data = RREG32(RLC_CGCG_CGLS_CTRL);

	अगर (enable && (rdev->cg_flags & RADEON_CG_SUPPORT_GFX_CGCG)) अणु
		cik_enable_gui_idle_पूर्णांकerrupt(rdev, true);

		पंचांगp = cik_halt_rlc(rdev);

		cik_select_se_sh(rdev, 0xffffffff, 0xffffffff);
		WREG32(RLC_SERDES_WR_CU_MASTER_MASK, 0xffffffff);
		WREG32(RLC_SERDES_WR_NONCU_MASTER_MASK, 0xffffffff);
		पंचांगp2 = BPM_ADDR_MASK | CGCG_OVERRIDE_0 | CGLS_ENABLE;
		WREG32(RLC_SERDES_WR_CTRL, पंचांगp2);

		cik_update_rlc(rdev, पंचांगp);

		data |= CGCG_EN | CGLS_EN;
	पूर्ण अन्यथा अणु
		cik_enable_gui_idle_पूर्णांकerrupt(rdev, false);

		RREG32(CB_CGTT_SCLK_CTRL);
		RREG32(CB_CGTT_SCLK_CTRL);
		RREG32(CB_CGTT_SCLK_CTRL);
		RREG32(CB_CGTT_SCLK_CTRL);

		data &= ~(CGCG_EN | CGLS_EN);
	पूर्ण

	अगर (orig != data)
		WREG32(RLC_CGCG_CGLS_CTRL, data);

पूर्ण

अटल व्योम cik_enable_mgcg(काष्ठा radeon_device *rdev, bool enable)
अणु
	u32 data, orig, पंचांगp = 0;

	अगर (enable && (rdev->cg_flags & RADEON_CG_SUPPORT_GFX_MGCG)) अणु
		अगर (rdev->cg_flags & RADEON_CG_SUPPORT_GFX_MGLS) अणु
			अगर (rdev->cg_flags & RADEON_CG_SUPPORT_GFX_CP_LS) अणु
				orig = data = RREG32(CP_MEM_SLP_CNTL);
				data |= CP_MEM_LS_EN;
				अगर (orig != data)
					WREG32(CP_MEM_SLP_CNTL, data);
			पूर्ण
		पूर्ण

		orig = data = RREG32(RLC_CGTT_MGCG_OVERRIDE);
		data |= 0x00000001;
		data &= 0xfffffffd;
		अगर (orig != data)
			WREG32(RLC_CGTT_MGCG_OVERRIDE, data);

		पंचांगp = cik_halt_rlc(rdev);

		cik_select_se_sh(rdev, 0xffffffff, 0xffffffff);
		WREG32(RLC_SERDES_WR_CU_MASTER_MASK, 0xffffffff);
		WREG32(RLC_SERDES_WR_NONCU_MASTER_MASK, 0xffffffff);
		data = BPM_ADDR_MASK | MGCG_OVERRIDE_0;
		WREG32(RLC_SERDES_WR_CTRL, data);

		cik_update_rlc(rdev, पंचांगp);

		अगर (rdev->cg_flags & RADEON_CG_SUPPORT_GFX_CGTS) अणु
			orig = data = RREG32(CGTS_SM_CTRL_REG);
			data &= ~SM_MODE_MASK;
			data |= SM_MODE(0x2);
			data |= SM_MODE_ENABLE;
			data &= ~CGTS_OVERRIDE;
			अगर ((rdev->cg_flags & RADEON_CG_SUPPORT_GFX_MGLS) &&
			    (rdev->cg_flags & RADEON_CG_SUPPORT_GFX_CGTS_LS))
				data &= ~CGTS_LS_OVERRIDE;
			data &= ~ON_MONITOR_ADD_MASK;
			data |= ON_MONITOR_ADD_EN;
			data |= ON_MONITOR_ADD(0x96);
			अगर (orig != data)
				WREG32(CGTS_SM_CTRL_REG, data);
		पूर्ण
	पूर्ण अन्यथा अणु
		orig = data = RREG32(RLC_CGTT_MGCG_OVERRIDE);
		data |= 0x00000003;
		अगर (orig != data)
			WREG32(RLC_CGTT_MGCG_OVERRIDE, data);

		data = RREG32(RLC_MEM_SLP_CNTL);
		अगर (data & RLC_MEM_LS_EN) अणु
			data &= ~RLC_MEM_LS_EN;
			WREG32(RLC_MEM_SLP_CNTL, data);
		पूर्ण

		data = RREG32(CP_MEM_SLP_CNTL);
		अगर (data & CP_MEM_LS_EN) अणु
			data &= ~CP_MEM_LS_EN;
			WREG32(CP_MEM_SLP_CNTL, data);
		पूर्ण

		orig = data = RREG32(CGTS_SM_CTRL_REG);
		data |= CGTS_OVERRIDE | CGTS_LS_OVERRIDE;
		अगर (orig != data)
			WREG32(CGTS_SM_CTRL_REG, data);

		पंचांगp = cik_halt_rlc(rdev);

		cik_select_se_sh(rdev, 0xffffffff, 0xffffffff);
		WREG32(RLC_SERDES_WR_CU_MASTER_MASK, 0xffffffff);
		WREG32(RLC_SERDES_WR_NONCU_MASTER_MASK, 0xffffffff);
		data = BPM_ADDR_MASK | MGCG_OVERRIDE_1;
		WREG32(RLC_SERDES_WR_CTRL, data);

		cik_update_rlc(rdev, पंचांगp);
	पूर्ण
पूर्ण

अटल स्थिर u32 mc_cg_रेजिस्टरs[] =
अणु
	MC_HUB_MISC_HUB_CG,
	MC_HUB_MISC_SIP_CG,
	MC_HUB_MISC_VM_CG,
	MC_XPB_CLK_GAT,
	ATC_MISC_CG,
	MC_CITF_MISC_WR_CG,
	MC_CITF_MISC_RD_CG,
	MC_CITF_MISC_VM_CG,
	VM_L2_CG,
पूर्ण;

अटल व्योम cik_enable_mc_ls(काष्ठा radeon_device *rdev,
			     bool enable)
अणु
	पूर्णांक i;
	u32 orig, data;

	क्रम (i = 0; i < ARRAY_SIZE(mc_cg_रेजिस्टरs); i++) अणु
		orig = data = RREG32(mc_cg_रेजिस्टरs[i]);
		अगर (enable && (rdev->cg_flags & RADEON_CG_SUPPORT_MC_LS))
			data |= MC_LS_ENABLE;
		अन्यथा
			data &= ~MC_LS_ENABLE;
		अगर (data != orig)
			WREG32(mc_cg_रेजिस्टरs[i], data);
	पूर्ण
पूर्ण

अटल व्योम cik_enable_mc_mgcg(काष्ठा radeon_device *rdev,
			       bool enable)
अणु
	पूर्णांक i;
	u32 orig, data;

	क्रम (i = 0; i < ARRAY_SIZE(mc_cg_रेजिस्टरs); i++) अणु
		orig = data = RREG32(mc_cg_रेजिस्टरs[i]);
		अगर (enable && (rdev->cg_flags & RADEON_CG_SUPPORT_MC_MGCG))
			data |= MC_CG_ENABLE;
		अन्यथा
			data &= ~MC_CG_ENABLE;
		अगर (data != orig)
			WREG32(mc_cg_रेजिस्टरs[i], data);
	पूर्ण
पूर्ण

अटल व्योम cik_enable_sdma_mgcg(काष्ठा radeon_device *rdev,
				 bool enable)
अणु
	u32 orig, data;

	अगर (enable && (rdev->cg_flags & RADEON_CG_SUPPORT_SDMA_MGCG)) अणु
		WREG32(SDMA0_CLK_CTRL + SDMA0_REGISTER_OFFSET, 0x00000100);
		WREG32(SDMA0_CLK_CTRL + SDMA1_REGISTER_OFFSET, 0x00000100);
	पूर्ण अन्यथा अणु
		orig = data = RREG32(SDMA0_CLK_CTRL + SDMA0_REGISTER_OFFSET);
		data |= 0xff000000;
		अगर (data != orig)
			WREG32(SDMA0_CLK_CTRL + SDMA0_REGISTER_OFFSET, data);

		orig = data = RREG32(SDMA0_CLK_CTRL + SDMA1_REGISTER_OFFSET);
		data |= 0xff000000;
		अगर (data != orig)
			WREG32(SDMA0_CLK_CTRL + SDMA1_REGISTER_OFFSET, data);
	पूर्ण
पूर्ण

अटल व्योम cik_enable_sdma_mgls(काष्ठा radeon_device *rdev,
				 bool enable)
अणु
	u32 orig, data;

	अगर (enable && (rdev->cg_flags & RADEON_CG_SUPPORT_SDMA_LS)) अणु
		orig = data = RREG32(SDMA0_POWER_CNTL + SDMA0_REGISTER_OFFSET);
		data |= 0x100;
		अगर (orig != data)
			WREG32(SDMA0_POWER_CNTL + SDMA0_REGISTER_OFFSET, data);

		orig = data = RREG32(SDMA0_POWER_CNTL + SDMA1_REGISTER_OFFSET);
		data |= 0x100;
		अगर (orig != data)
			WREG32(SDMA0_POWER_CNTL + SDMA1_REGISTER_OFFSET, data);
	पूर्ण अन्यथा अणु
		orig = data = RREG32(SDMA0_POWER_CNTL + SDMA0_REGISTER_OFFSET);
		data &= ~0x100;
		अगर (orig != data)
			WREG32(SDMA0_POWER_CNTL + SDMA0_REGISTER_OFFSET, data);

		orig = data = RREG32(SDMA0_POWER_CNTL + SDMA1_REGISTER_OFFSET);
		data &= ~0x100;
		अगर (orig != data)
			WREG32(SDMA0_POWER_CNTL + SDMA1_REGISTER_OFFSET, data);
	पूर्ण
पूर्ण

अटल व्योम cik_enable_uvd_mgcg(काष्ठा radeon_device *rdev,
				bool enable)
अणु
	u32 orig, data;

	अगर (enable && (rdev->cg_flags & RADEON_CG_SUPPORT_UVD_MGCG)) अणु
		data = RREG32_UVD_CTX(UVD_CGC_MEM_CTRL);
		data = 0xfff;
		WREG32_UVD_CTX(UVD_CGC_MEM_CTRL, data);

		orig = data = RREG32(UVD_CGC_CTRL);
		data |= DCM;
		अगर (orig != data)
			WREG32(UVD_CGC_CTRL, data);
	पूर्ण अन्यथा अणु
		data = RREG32_UVD_CTX(UVD_CGC_MEM_CTRL);
		data &= ~0xfff;
		WREG32_UVD_CTX(UVD_CGC_MEM_CTRL, data);

		orig = data = RREG32(UVD_CGC_CTRL);
		data &= ~DCM;
		अगर (orig != data)
			WREG32(UVD_CGC_CTRL, data);
	पूर्ण
पूर्ण

अटल व्योम cik_enable_bअगर_mgls(काष्ठा radeon_device *rdev,
			       bool enable)
अणु
	u32 orig, data;

	orig = data = RREG32_PCIE_PORT(PCIE_CNTL2);

	अगर (enable && (rdev->cg_flags & RADEON_CG_SUPPORT_BIF_LS))
		data |= SLV_MEM_LS_EN | MST_MEM_LS_EN |
			REPLAY_MEM_LS_EN | SLV_MEM_AGGRESSIVE_LS_EN;
	अन्यथा
		data &= ~(SLV_MEM_LS_EN | MST_MEM_LS_EN |
			  REPLAY_MEM_LS_EN | SLV_MEM_AGGRESSIVE_LS_EN);

	अगर (orig != data)
		WREG32_PCIE_PORT(PCIE_CNTL2, data);
पूर्ण

अटल व्योम cik_enable_hdp_mgcg(काष्ठा radeon_device *rdev,
				bool enable)
अणु
	u32 orig, data;

	orig = data = RREG32(HDP_HOST_PATH_CNTL);

	अगर (enable && (rdev->cg_flags & RADEON_CG_SUPPORT_HDP_MGCG))
		data &= ~CLOCK_GATING_DIS;
	अन्यथा
		data |= CLOCK_GATING_DIS;

	अगर (orig != data)
		WREG32(HDP_HOST_PATH_CNTL, data);
पूर्ण

अटल व्योम cik_enable_hdp_ls(काष्ठा radeon_device *rdev,
			      bool enable)
अणु
	u32 orig, data;

	orig = data = RREG32(HDP_MEM_POWER_LS);

	अगर (enable && (rdev->cg_flags & RADEON_CG_SUPPORT_HDP_LS))
		data |= HDP_LS_ENABLE;
	अन्यथा
		data &= ~HDP_LS_ENABLE;

	अगर (orig != data)
		WREG32(HDP_MEM_POWER_LS, data);
पूर्ण

व्योम cik_update_cg(काष्ठा radeon_device *rdev,
		   u32 block, bool enable)
अणु

	अगर (block & RADEON_CG_BLOCK_GFX) अणु
		cik_enable_gui_idle_पूर्णांकerrupt(rdev, false);
		/* order matters! */
		अगर (enable) अणु
			cik_enable_mgcg(rdev, true);
			cik_enable_cgcg(rdev, true);
		पूर्ण अन्यथा अणु
			cik_enable_cgcg(rdev, false);
			cik_enable_mgcg(rdev, false);
		पूर्ण
		cik_enable_gui_idle_पूर्णांकerrupt(rdev, true);
	पूर्ण

	अगर (block & RADEON_CG_BLOCK_MC) अणु
		अगर (!(rdev->flags & RADEON_IS_IGP)) अणु
			cik_enable_mc_mgcg(rdev, enable);
			cik_enable_mc_ls(rdev, enable);
		पूर्ण
	पूर्ण

	अगर (block & RADEON_CG_BLOCK_SDMA) अणु
		cik_enable_sdma_mgcg(rdev, enable);
		cik_enable_sdma_mgls(rdev, enable);
	पूर्ण

	अगर (block & RADEON_CG_BLOCK_BIF) अणु
		cik_enable_bअगर_mgls(rdev, enable);
	पूर्ण

	अगर (block & RADEON_CG_BLOCK_UVD) अणु
		अगर (rdev->has_uvd)
			cik_enable_uvd_mgcg(rdev, enable);
	पूर्ण

	अगर (block & RADEON_CG_BLOCK_HDP) अणु
		cik_enable_hdp_mgcg(rdev, enable);
		cik_enable_hdp_ls(rdev, enable);
	पूर्ण

	अगर (block & RADEON_CG_BLOCK_VCE) अणु
		vce_v2_0_enable_mgcg(rdev, enable);
	पूर्ण
पूर्ण

अटल व्योम cik_init_cg(काष्ठा radeon_device *rdev)
अणु

	cik_update_cg(rdev, RADEON_CG_BLOCK_GFX, true);

	अगर (rdev->has_uvd)
		si_init_uvd_पूर्णांकernal_cg(rdev);

	cik_update_cg(rdev, (RADEON_CG_BLOCK_MC |
			     RADEON_CG_BLOCK_SDMA |
			     RADEON_CG_BLOCK_BIF |
			     RADEON_CG_BLOCK_UVD |
			     RADEON_CG_BLOCK_HDP), true);
पूर्ण

अटल व्योम cik_fini_cg(काष्ठा radeon_device *rdev)
अणु
	cik_update_cg(rdev, (RADEON_CG_BLOCK_MC |
			     RADEON_CG_BLOCK_SDMA |
			     RADEON_CG_BLOCK_BIF |
			     RADEON_CG_BLOCK_UVD |
			     RADEON_CG_BLOCK_HDP), false);

	cik_update_cg(rdev, RADEON_CG_BLOCK_GFX, false);
पूर्ण

अटल व्योम cik_enable_sck_slowकरोwn_on_pu(काष्ठा radeon_device *rdev,
					  bool enable)
अणु
	u32 data, orig;

	orig = data = RREG32(RLC_PG_CNTL);
	अगर (enable && (rdev->pg_flags & RADEON_PG_SUPPORT_RLC_SMU_HS))
		data |= SMU_CLK_SLOWDOWN_ON_PU_ENABLE;
	अन्यथा
		data &= ~SMU_CLK_SLOWDOWN_ON_PU_ENABLE;
	अगर (orig != data)
		WREG32(RLC_PG_CNTL, data);
पूर्ण

अटल व्योम cik_enable_sck_slowकरोwn_on_pd(काष्ठा radeon_device *rdev,
					  bool enable)
अणु
	u32 data, orig;

	orig = data = RREG32(RLC_PG_CNTL);
	अगर (enable && (rdev->pg_flags & RADEON_PG_SUPPORT_RLC_SMU_HS))
		data |= SMU_CLK_SLOWDOWN_ON_PD_ENABLE;
	अन्यथा
		data &= ~SMU_CLK_SLOWDOWN_ON_PD_ENABLE;
	अगर (orig != data)
		WREG32(RLC_PG_CNTL, data);
पूर्ण

अटल व्योम cik_enable_cp_pg(काष्ठा radeon_device *rdev, bool enable)
अणु
	u32 data, orig;

	orig = data = RREG32(RLC_PG_CNTL);
	अगर (enable && (rdev->pg_flags & RADEON_PG_SUPPORT_CP))
		data &= ~DISABLE_CP_PG;
	अन्यथा
		data |= DISABLE_CP_PG;
	अगर (orig != data)
		WREG32(RLC_PG_CNTL, data);
पूर्ण

अटल व्योम cik_enable_gds_pg(काष्ठा radeon_device *rdev, bool enable)
अणु
	u32 data, orig;

	orig = data = RREG32(RLC_PG_CNTL);
	अगर (enable && (rdev->pg_flags & RADEON_PG_SUPPORT_GDS))
		data &= ~DISABLE_GDS_PG;
	अन्यथा
		data |= DISABLE_GDS_PG;
	अगर (orig != data)
		WREG32(RLC_PG_CNTL, data);
पूर्ण

#घोषणा CP_ME_TABLE_SIZE    96
#घोषणा CP_ME_TABLE_OFFSET  2048
#घोषणा CP_MEC_TABLE_OFFSET 4096

व्योम cik_init_cp_pg_table(काष्ठा radeon_device *rdev)
अणु
	अस्थिर u32 *dst_ptr;
	पूर्णांक me, i, max_me = 4;
	u32 bo_offset = 0;
	u32 table_offset, table_size;

	अगर (rdev->family == CHIP_KAVERI)
		max_me = 5;

	अगर (rdev->rlc.cp_table_ptr == शून्य)
		वापस;

	/* ग_लिखो the cp table buffer */
	dst_ptr = rdev->rlc.cp_table_ptr;
	क्रम (me = 0; me < max_me; me++) अणु
		अगर (rdev->new_fw) अणु
			स्थिर __le32 *fw_data;
			स्थिर काष्ठा gfx_firmware_header_v1_0 *hdr;

			अगर (me == 0) अणु
				hdr = (स्थिर काष्ठा gfx_firmware_header_v1_0 *)rdev->ce_fw->data;
				fw_data = (स्थिर __le32 *)
					(rdev->ce_fw->data + le32_to_cpu(hdr->header.ucode_array_offset_bytes));
				table_offset = le32_to_cpu(hdr->jt_offset);
				table_size = le32_to_cpu(hdr->jt_size);
			पूर्ण अन्यथा अगर (me == 1) अणु
				hdr = (स्थिर काष्ठा gfx_firmware_header_v1_0 *)rdev->pfp_fw->data;
				fw_data = (स्थिर __le32 *)
					(rdev->pfp_fw->data + le32_to_cpu(hdr->header.ucode_array_offset_bytes));
				table_offset = le32_to_cpu(hdr->jt_offset);
				table_size = le32_to_cpu(hdr->jt_size);
			पूर्ण अन्यथा अगर (me == 2) अणु
				hdr = (स्थिर काष्ठा gfx_firmware_header_v1_0 *)rdev->me_fw->data;
				fw_data = (स्थिर __le32 *)
					(rdev->me_fw->data + le32_to_cpu(hdr->header.ucode_array_offset_bytes));
				table_offset = le32_to_cpu(hdr->jt_offset);
				table_size = le32_to_cpu(hdr->jt_size);
			पूर्ण अन्यथा अगर (me == 3) अणु
				hdr = (स्थिर काष्ठा gfx_firmware_header_v1_0 *)rdev->mec_fw->data;
				fw_data = (स्थिर __le32 *)
					(rdev->mec_fw->data + le32_to_cpu(hdr->header.ucode_array_offset_bytes));
				table_offset = le32_to_cpu(hdr->jt_offset);
				table_size = le32_to_cpu(hdr->jt_size);
			पूर्ण अन्यथा अणु
				hdr = (स्थिर काष्ठा gfx_firmware_header_v1_0 *)rdev->mec2_fw->data;
				fw_data = (स्थिर __le32 *)
					(rdev->mec2_fw->data + le32_to_cpu(hdr->header.ucode_array_offset_bytes));
				table_offset = le32_to_cpu(hdr->jt_offset);
				table_size = le32_to_cpu(hdr->jt_size);
			पूर्ण

			क्रम (i = 0; i < table_size; i ++) अणु
				dst_ptr[bo_offset + i] =
					cpu_to_le32(le32_to_cpu(fw_data[table_offset + i]));
			पूर्ण
			bo_offset += table_size;
		पूर्ण अन्यथा अणु
			स्थिर __be32 *fw_data;
			table_size = CP_ME_TABLE_SIZE;

			अगर (me == 0) अणु
				fw_data = (स्थिर __be32 *)rdev->ce_fw->data;
				table_offset = CP_ME_TABLE_OFFSET;
			पूर्ण अन्यथा अगर (me == 1) अणु
				fw_data = (स्थिर __be32 *)rdev->pfp_fw->data;
				table_offset = CP_ME_TABLE_OFFSET;
			पूर्ण अन्यथा अगर (me == 2) अणु
				fw_data = (स्थिर __be32 *)rdev->me_fw->data;
				table_offset = CP_ME_TABLE_OFFSET;
			पूर्ण अन्यथा अणु
				fw_data = (स्थिर __be32 *)rdev->mec_fw->data;
				table_offset = CP_MEC_TABLE_OFFSET;
			पूर्ण

			क्रम (i = 0; i < table_size; i ++) अणु
				dst_ptr[bo_offset + i] =
					cpu_to_le32(be32_to_cpu(fw_data[table_offset + i]));
			पूर्ण
			bo_offset += table_size;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम cik_enable_gfx_cgpg(काष्ठा radeon_device *rdev,
				bool enable)
अणु
	u32 data, orig;

	अगर (enable && (rdev->pg_flags & RADEON_PG_SUPPORT_GFX_PG)) अणु
		orig = data = RREG32(RLC_PG_CNTL);
		data |= GFX_PG_ENABLE;
		अगर (orig != data)
			WREG32(RLC_PG_CNTL, data);

		orig = data = RREG32(RLC_AUTO_PG_CTRL);
		data |= AUTO_PG_EN;
		अगर (orig != data)
			WREG32(RLC_AUTO_PG_CTRL, data);
	पूर्ण अन्यथा अणु
		orig = data = RREG32(RLC_PG_CNTL);
		data &= ~GFX_PG_ENABLE;
		अगर (orig != data)
			WREG32(RLC_PG_CNTL, data);

		orig = data = RREG32(RLC_AUTO_PG_CTRL);
		data &= ~AUTO_PG_EN;
		अगर (orig != data)
			WREG32(RLC_AUTO_PG_CTRL, data);

		data = RREG32(DB_RENDER_CONTROL);
	पूर्ण
पूर्ण

अटल u32 cik_get_cu_active_biपंचांगap(काष्ठा radeon_device *rdev, u32 se, u32 sh)
अणु
	u32 mask = 0, पंचांगp, पंचांगp1;
	पूर्णांक i;

	cik_select_se_sh(rdev, se, sh);
	पंचांगp = RREG32(CC_GC_SHADER_ARRAY_CONFIG);
	पंचांगp1 = RREG32(GC_USER_SHADER_ARRAY_CONFIG);
	cik_select_se_sh(rdev, 0xffffffff, 0xffffffff);

	पंचांगp &= 0xffff0000;

	पंचांगp |= पंचांगp1;
	पंचांगp >>= 16;

	क्रम (i = 0; i < rdev->config.cik.max_cu_per_sh; i ++) अणु
		mask <<= 1;
		mask |= 1;
	पूर्ण

	वापस (~पंचांगp) & mask;
पूर्ण

अटल व्योम cik_init_ao_cu_mask(काष्ठा radeon_device *rdev)
अणु
	u32 i, j, k, active_cu_number = 0;
	u32 mask, counter, cu_biपंचांगap;
	u32 पंचांगp = 0;

	क्रम (i = 0; i < rdev->config.cik.max_shader_engines; i++) अणु
		क्रम (j = 0; j < rdev->config.cik.max_sh_per_se; j++) अणु
			mask = 1;
			cu_biपंचांगap = 0;
			counter = 0;
			क्रम (k = 0; k < rdev->config.cik.max_cu_per_sh; k ++) अणु
				अगर (cik_get_cu_active_biपंचांगap(rdev, i, j) & mask) अणु
					अगर (counter < 2)
						cu_biपंचांगap |= mask;
					counter ++;
				पूर्ण
				mask <<= 1;
			पूर्ण

			active_cu_number += counter;
			पंचांगp |= (cu_biपंचांगap << (i * 16 + j * 8));
		पूर्ण
	पूर्ण

	WREG32(RLC_PG_AO_CU_MASK, पंचांगp);

	पंचांगp = RREG32(RLC_MAX_PG_CU);
	पंचांगp &= ~MAX_PU_CU_MASK;
	पंचांगp |= MAX_PU_CU(active_cu_number);
	WREG32(RLC_MAX_PG_CU, पंचांगp);
पूर्ण

अटल व्योम cik_enable_gfx_अटल_mgpg(काष्ठा radeon_device *rdev,
				       bool enable)
अणु
	u32 data, orig;

	orig = data = RREG32(RLC_PG_CNTL);
	अगर (enable && (rdev->pg_flags & RADEON_PG_SUPPORT_GFX_SMG))
		data |= STATIC_PER_CU_PG_ENABLE;
	अन्यथा
		data &= ~STATIC_PER_CU_PG_ENABLE;
	अगर (orig != data)
		WREG32(RLC_PG_CNTL, data);
पूर्ण

अटल व्योम cik_enable_gfx_dynamic_mgpg(काष्ठा radeon_device *rdev,
					bool enable)
अणु
	u32 data, orig;

	orig = data = RREG32(RLC_PG_CNTL);
	अगर (enable && (rdev->pg_flags & RADEON_PG_SUPPORT_GFX_DMG))
		data |= DYN_PER_CU_PG_ENABLE;
	अन्यथा
		data &= ~DYN_PER_CU_PG_ENABLE;
	अगर (orig != data)
		WREG32(RLC_PG_CNTL, data);
पूर्ण

#घोषणा RLC_SAVE_AND_RESTORE_STARTING_OFFSET 0x90
#घोषणा RLC_CLEAR_STATE_DESCRIPTOR_OFFSET    0x3D

अटल व्योम cik_init_gfx_cgpg(काष्ठा radeon_device *rdev)
अणु
	u32 data, orig;
	u32 i;

	अगर (rdev->rlc.cs_data) अणु
		WREG32(RLC_GPM_SCRATCH_ADDR, RLC_CLEAR_STATE_DESCRIPTOR_OFFSET);
		WREG32(RLC_GPM_SCRATCH_DATA, upper_32_bits(rdev->rlc.clear_state_gpu_addr));
		WREG32(RLC_GPM_SCRATCH_DATA, lower_32_bits(rdev->rlc.clear_state_gpu_addr));
		WREG32(RLC_GPM_SCRATCH_DATA, rdev->rlc.clear_state_size);
	पूर्ण अन्यथा अणु
		WREG32(RLC_GPM_SCRATCH_ADDR, RLC_CLEAR_STATE_DESCRIPTOR_OFFSET);
		क्रम (i = 0; i < 3; i++)
			WREG32(RLC_GPM_SCRATCH_DATA, 0);
	पूर्ण
	अगर (rdev->rlc.reg_list) अणु
		WREG32(RLC_GPM_SCRATCH_ADDR, RLC_SAVE_AND_RESTORE_STARTING_OFFSET);
		क्रम (i = 0; i < rdev->rlc.reg_list_size; i++)
			WREG32(RLC_GPM_SCRATCH_DATA, rdev->rlc.reg_list[i]);
	पूर्ण

	orig = data = RREG32(RLC_PG_CNTL);
	data |= GFX_PG_SRC;
	अगर (orig != data)
		WREG32(RLC_PG_CNTL, data);

	WREG32(RLC_SAVE_AND_RESTORE_BASE, rdev->rlc.save_restore_gpu_addr >> 8);
	WREG32(RLC_CP_TABLE_RESTORE, rdev->rlc.cp_table_gpu_addr >> 8);

	data = RREG32(CP_RB_WPTR_POLL_CNTL);
	data &= ~IDLE_POLL_COUNT_MASK;
	data |= IDLE_POLL_COUNT(0x60);
	WREG32(CP_RB_WPTR_POLL_CNTL, data);

	data = 0x10101010;
	WREG32(RLC_PG_DELAY, data);

	data = RREG32(RLC_PG_DELAY_2);
	data &= ~0xff;
	data |= 0x3;
	WREG32(RLC_PG_DELAY_2, data);

	data = RREG32(RLC_AUTO_PG_CTRL);
	data &= ~GRBM_REG_SGIT_MASK;
	data |= GRBM_REG_SGIT(0x700);
	WREG32(RLC_AUTO_PG_CTRL, data);

पूर्ण

अटल व्योम cik_update_gfx_pg(काष्ठा radeon_device *rdev, bool enable)
अणु
	cik_enable_gfx_cgpg(rdev, enable);
	cik_enable_gfx_अटल_mgpg(rdev, enable);
	cik_enable_gfx_dynamic_mgpg(rdev, enable);
पूर्ण

u32 cik_get_csb_size(काष्ठा radeon_device *rdev)
अणु
	u32 count = 0;
	स्थिर काष्ठा cs_section_def *sect = शून्य;
	स्थिर काष्ठा cs_extent_def *ext = शून्य;

	अगर (rdev->rlc.cs_data == शून्य)
		वापस 0;

	/* begin clear state */
	count += 2;
	/* context control state */
	count += 3;

	क्रम (sect = rdev->rlc.cs_data; sect->section != शून्य; ++sect) अणु
		क्रम (ext = sect->section; ext->extent != शून्य; ++ext) अणु
			अगर (sect->id == SECT_CONTEXT)
				count += 2 + ext->reg_count;
			अन्यथा
				वापस 0;
		पूर्ण
	पूर्ण
	/* pa_sc_raster_config/pa_sc_raster_config1 */
	count += 4;
	/* end clear state */
	count += 2;
	/* clear state */
	count += 2;

	वापस count;
पूर्ण

व्योम cik_get_csb_buffer(काष्ठा radeon_device *rdev, अस्थिर u32 *buffer)
अणु
	u32 count = 0, i;
	स्थिर काष्ठा cs_section_def *sect = शून्य;
	स्थिर काष्ठा cs_extent_def *ext = शून्य;

	अगर (rdev->rlc.cs_data == शून्य)
		वापस;
	अगर (buffer == शून्य)
		वापस;

	buffer[count++] = cpu_to_le32(PACKET3(PACKET3_PREAMBLE_CNTL, 0));
	buffer[count++] = cpu_to_le32(PACKET3_PREAMBLE_BEGIN_CLEAR_STATE);

	buffer[count++] = cpu_to_le32(PACKET3(PACKET3_CONTEXT_CONTROL, 1));
	buffer[count++] = cpu_to_le32(0x80000000);
	buffer[count++] = cpu_to_le32(0x80000000);

	क्रम (sect = rdev->rlc.cs_data; sect->section != शून्य; ++sect) अणु
		क्रम (ext = sect->section; ext->extent != शून्य; ++ext) अणु
			अगर (sect->id == SECT_CONTEXT) अणु
				buffer[count++] =
					cpu_to_le32(PACKET3(PACKET3_SET_CONTEXT_REG, ext->reg_count));
				buffer[count++] = cpu_to_le32(ext->reg_index - 0xa000);
				क्रम (i = 0; i < ext->reg_count; i++)
					buffer[count++] = cpu_to_le32(ext->extent[i]);
			पूर्ण अन्यथा अणु
				वापस;
			पूर्ण
		पूर्ण
	पूर्ण

	buffer[count++] = cpu_to_le32(PACKET3(PACKET3_SET_CONTEXT_REG, 2));
	buffer[count++] = cpu_to_le32(PA_SC_RASTER_CONFIG - PACKET3_SET_CONTEXT_REG_START);
	चयन (rdev->family) अणु
	हाल CHIP_BONAIRE:
		buffer[count++] = cpu_to_le32(0x16000012);
		buffer[count++] = cpu_to_le32(0x00000000);
		अवरोध;
	हाल CHIP_KAVERI:
		buffer[count++] = cpu_to_le32(0x00000000); /* XXX */
		buffer[count++] = cpu_to_le32(0x00000000);
		अवरोध;
	हाल CHIP_KABINI:
	हाल CHIP_MULLINS:
		buffer[count++] = cpu_to_le32(0x00000000); /* XXX */
		buffer[count++] = cpu_to_le32(0x00000000);
		अवरोध;
	हाल CHIP_HAWAII:
		buffer[count++] = cpu_to_le32(0x3a00161a);
		buffer[count++] = cpu_to_le32(0x0000002e);
		अवरोध;
	शेष:
		buffer[count++] = cpu_to_le32(0x00000000);
		buffer[count++] = cpu_to_le32(0x00000000);
		अवरोध;
	पूर्ण

	buffer[count++] = cpu_to_le32(PACKET3(PACKET3_PREAMBLE_CNTL, 0));
	buffer[count++] = cpu_to_le32(PACKET3_PREAMBLE_END_CLEAR_STATE);

	buffer[count++] = cpu_to_le32(PACKET3(PACKET3_CLEAR_STATE, 0));
	buffer[count++] = cpu_to_le32(0);
पूर्ण

अटल व्योम cik_init_pg(काष्ठा radeon_device *rdev)
अणु
	अगर (rdev->pg_flags) अणु
		cik_enable_sck_slowकरोwn_on_pu(rdev, true);
		cik_enable_sck_slowकरोwn_on_pd(rdev, true);
		अगर (rdev->pg_flags & RADEON_PG_SUPPORT_GFX_PG) अणु
			cik_init_gfx_cgpg(rdev);
			cik_enable_cp_pg(rdev, true);
			cik_enable_gds_pg(rdev, true);
		पूर्ण
		cik_init_ao_cu_mask(rdev);
		cik_update_gfx_pg(rdev, true);
	पूर्ण
पूर्ण

अटल व्योम cik_fini_pg(काष्ठा radeon_device *rdev)
अणु
	अगर (rdev->pg_flags) अणु
		cik_update_gfx_pg(rdev, false);
		अगर (rdev->pg_flags & RADEON_PG_SUPPORT_GFX_PG) अणु
			cik_enable_cp_pg(rdev, false);
			cik_enable_gds_pg(rdev, false);
		पूर्ण
	पूर्ण
पूर्ण

/*
 * Interrupts
 * Starting with r6xx, पूर्णांकerrupts are handled via a ring buffer.
 * Ring buffers are areas of GPU accessible memory that the GPU
 * ग_लिखोs पूर्णांकerrupt vectors पूर्णांकo and the host पढ़ोs vectors out of.
 * There is a rptr (पढ़ो poपूर्णांकer) that determines where the
 * host is currently पढ़ोing, and a wptr (ग_लिखो poपूर्णांकer)
 * which determines where the GPU has written.  When the
 * poपूर्णांकers are equal, the ring is idle.  When the GPU
 * ग_लिखोs vectors to the ring buffer, it increments the
 * wptr.  When there is an पूर्णांकerrupt, the host then starts
 * fetching commands and processing them until the poपूर्णांकers are
 * equal again at which poपूर्णांक it updates the rptr.
 */

/**
 * cik_enable_पूर्णांकerrupts - Enable the पूर्णांकerrupt ring buffer
 *
 * @rdev: radeon_device poपूर्णांकer
 *
 * Enable the पूर्णांकerrupt ring buffer (CIK).
 */
अटल व्योम cik_enable_पूर्णांकerrupts(काष्ठा radeon_device *rdev)
अणु
	u32 ih_cntl = RREG32(IH_CNTL);
	u32 ih_rb_cntl = RREG32(IH_RB_CNTL);

	ih_cntl |= ENABLE_INTR;
	ih_rb_cntl |= IH_RB_ENABLE;
	WREG32(IH_CNTL, ih_cntl);
	WREG32(IH_RB_CNTL, ih_rb_cntl);
	rdev->ih.enabled = true;
पूर्ण

/**
 * cik_disable_पूर्णांकerrupts - Disable the पूर्णांकerrupt ring buffer
 *
 * @rdev: radeon_device poपूर्णांकer
 *
 * Disable the पूर्णांकerrupt ring buffer (CIK).
 */
अटल व्योम cik_disable_पूर्णांकerrupts(काष्ठा radeon_device *rdev)
अणु
	u32 ih_rb_cntl = RREG32(IH_RB_CNTL);
	u32 ih_cntl = RREG32(IH_CNTL);

	ih_rb_cntl &= ~IH_RB_ENABLE;
	ih_cntl &= ~ENABLE_INTR;
	WREG32(IH_RB_CNTL, ih_rb_cntl);
	WREG32(IH_CNTL, ih_cntl);
	/* set rptr, wptr to 0 */
	WREG32(IH_RB_RPTR, 0);
	WREG32(IH_RB_WPTR, 0);
	rdev->ih.enabled = false;
	rdev->ih.rptr = 0;
पूर्ण

/**
 * cik_disable_पूर्णांकerrupt_state - Disable all पूर्णांकerrupt sources
 *
 * @rdev: radeon_device poपूर्णांकer
 *
 * Clear all पूर्णांकerrupt enable bits used by the driver (CIK).
 */
अटल व्योम cik_disable_पूर्णांकerrupt_state(काष्ठा radeon_device *rdev)
अणु
	u32 पंचांगp;

	/* gfx ring */
	पंचांगp = RREG32(CP_INT_CNTL_RING0) &
		(CNTX_BUSY_INT_ENABLE | CNTX_EMPTY_INT_ENABLE);
	WREG32(CP_INT_CNTL_RING0, पंचांगp);
	/* sdma */
	पंचांगp = RREG32(SDMA0_CNTL + SDMA0_REGISTER_OFFSET) & ~TRAP_ENABLE;
	WREG32(SDMA0_CNTL + SDMA0_REGISTER_OFFSET, पंचांगp);
	पंचांगp = RREG32(SDMA0_CNTL + SDMA1_REGISTER_OFFSET) & ~TRAP_ENABLE;
	WREG32(SDMA0_CNTL + SDMA1_REGISTER_OFFSET, पंचांगp);
	/* compute queues */
	WREG32(CP_ME1_PIPE0_INT_CNTL, 0);
	WREG32(CP_ME1_PIPE1_INT_CNTL, 0);
	WREG32(CP_ME1_PIPE2_INT_CNTL, 0);
	WREG32(CP_ME1_PIPE3_INT_CNTL, 0);
	WREG32(CP_ME2_PIPE0_INT_CNTL, 0);
	WREG32(CP_ME2_PIPE1_INT_CNTL, 0);
	WREG32(CP_ME2_PIPE2_INT_CNTL, 0);
	WREG32(CP_ME2_PIPE3_INT_CNTL, 0);
	/* grbm */
	WREG32(GRBM_INT_CNTL, 0);
	/* SRBM */
	WREG32(SRBM_INT_CNTL, 0);
	/* vline/vblank, etc. */
	WREG32(LB_INTERRUPT_MASK + EVERGREEN_CRTC0_REGISTER_OFFSET, 0);
	WREG32(LB_INTERRUPT_MASK + EVERGREEN_CRTC1_REGISTER_OFFSET, 0);
	अगर (rdev->num_crtc >= 4) अणु
		WREG32(LB_INTERRUPT_MASK + EVERGREEN_CRTC2_REGISTER_OFFSET, 0);
		WREG32(LB_INTERRUPT_MASK + EVERGREEN_CRTC3_REGISTER_OFFSET, 0);
	पूर्ण
	अगर (rdev->num_crtc >= 6) अणु
		WREG32(LB_INTERRUPT_MASK + EVERGREEN_CRTC4_REGISTER_OFFSET, 0);
		WREG32(LB_INTERRUPT_MASK + EVERGREEN_CRTC5_REGISTER_OFFSET, 0);
	पूर्ण
	/* pflip */
	अगर (rdev->num_crtc >= 2) अणु
		WREG32(GRPH_INT_CONTROL + EVERGREEN_CRTC0_REGISTER_OFFSET, 0);
		WREG32(GRPH_INT_CONTROL + EVERGREEN_CRTC1_REGISTER_OFFSET, 0);
	पूर्ण
	अगर (rdev->num_crtc >= 4) अणु
		WREG32(GRPH_INT_CONTROL + EVERGREEN_CRTC2_REGISTER_OFFSET, 0);
		WREG32(GRPH_INT_CONTROL + EVERGREEN_CRTC3_REGISTER_OFFSET, 0);
	पूर्ण
	अगर (rdev->num_crtc >= 6) अणु
		WREG32(GRPH_INT_CONTROL + EVERGREEN_CRTC4_REGISTER_OFFSET, 0);
		WREG32(GRPH_INT_CONTROL + EVERGREEN_CRTC5_REGISTER_OFFSET, 0);
	पूर्ण

	/* dac hotplug */
	WREG32(DAC_AUTODETECT_INT_CONTROL, 0);

	/* digital hotplug */
	पंचांगp = RREG32(DC_HPD1_INT_CONTROL) & DC_HPDx_INT_POLARITY;
	WREG32(DC_HPD1_INT_CONTROL, पंचांगp);
	पंचांगp = RREG32(DC_HPD2_INT_CONTROL) & DC_HPDx_INT_POLARITY;
	WREG32(DC_HPD2_INT_CONTROL, पंचांगp);
	पंचांगp = RREG32(DC_HPD3_INT_CONTROL) & DC_HPDx_INT_POLARITY;
	WREG32(DC_HPD3_INT_CONTROL, पंचांगp);
	पंचांगp = RREG32(DC_HPD4_INT_CONTROL) & DC_HPDx_INT_POLARITY;
	WREG32(DC_HPD4_INT_CONTROL, पंचांगp);
	पंचांगp = RREG32(DC_HPD5_INT_CONTROL) & DC_HPDx_INT_POLARITY;
	WREG32(DC_HPD5_INT_CONTROL, पंचांगp);
	पंचांगp = RREG32(DC_HPD6_INT_CONTROL) & DC_HPDx_INT_POLARITY;
	WREG32(DC_HPD6_INT_CONTROL, पंचांगp);

पूर्ण

/**
 * cik_irq_init - init and enable the पूर्णांकerrupt ring
 *
 * @rdev: radeon_device poपूर्णांकer
 *
 * Allocate a ring buffer क्रम the पूर्णांकerrupt controller,
 * enable the RLC, disable पूर्णांकerrupts, enable the IH
 * ring buffer and enable it (CIK).
 * Called at device load and reume.
 * Returns 0 क्रम success, errors क्रम failure.
 */
अटल पूर्णांक cik_irq_init(काष्ठा radeon_device *rdev)
अणु
	पूर्णांक ret = 0;
	पूर्णांक rb_bufsz;
	u32 पूर्णांकerrupt_cntl, ih_cntl, ih_rb_cntl;

	/* allocate ring */
	ret = r600_ih_ring_alloc(rdev);
	अगर (ret)
		वापस ret;

	/* disable irqs */
	cik_disable_पूर्णांकerrupts(rdev);

	/* init rlc */
	ret = cik_rlc_resume(rdev);
	अगर (ret) अणु
		r600_ih_ring_fini(rdev);
		वापस ret;
	पूर्ण

	/* setup पूर्णांकerrupt control */
	/* set dummy पढ़ो address to dummy page address */
	WREG32(INTERRUPT_CNTL2, rdev->dummy_page.addr >> 8);
	पूर्णांकerrupt_cntl = RREG32(INTERRUPT_CNTL);
	/* IH_DUMMY_RD_OVERRIDE=0 - dummy पढ़ो disabled with msi, enabled without msi
	 * IH_DUMMY_RD_OVERRIDE=1 - dummy पढ़ो controlled by IH_DUMMY_RD_EN
	 */
	पूर्णांकerrupt_cntl &= ~IH_DUMMY_RD_OVERRIDE;
	/* IH_REQ_NONSNOOP_EN=1 अगर ring is in non-cacheable memory, e.g., vram */
	पूर्णांकerrupt_cntl &= ~IH_REQ_NONSNOOP_EN;
	WREG32(INTERRUPT_CNTL, पूर्णांकerrupt_cntl);

	WREG32(IH_RB_BASE, rdev->ih.gpu_addr >> 8);
	rb_bufsz = order_base_2(rdev->ih.ring_size / 4);

	ih_rb_cntl = (IH_WPTR_OVERFLOW_ENABLE |
		      IH_WPTR_OVERFLOW_CLEAR |
		      (rb_bufsz << 1));

	अगर (rdev->wb.enabled)
		ih_rb_cntl |= IH_WPTR_WRITEBACK_ENABLE;

	/* set the ग_लिखोback address whether it's enabled or not */
	WREG32(IH_RB_WPTR_ADDR_LO, (rdev->wb.gpu_addr + R600_WB_IH_WPTR_OFFSET) & 0xFFFFFFFC);
	WREG32(IH_RB_WPTR_ADDR_HI, upper_32_bits(rdev->wb.gpu_addr + R600_WB_IH_WPTR_OFFSET) & 0xFF);

	WREG32(IH_RB_CNTL, ih_rb_cntl);

	/* set rptr, wptr to 0 */
	WREG32(IH_RB_RPTR, 0);
	WREG32(IH_RB_WPTR, 0);

	/* Default settings क्रम IH_CNTL (disabled at first) */
	ih_cntl = MC_WRREQ_CREDIT(0x10) | MC_WR_CLEAN_CNT(0x10) | MC_VMID(0);
	/* RPTR_REARM only works अगर msi's are enabled */
	अगर (rdev->msi_enabled)
		ih_cntl |= RPTR_REARM;
	WREG32(IH_CNTL, ih_cntl);

	/* क्रमce the active पूर्णांकerrupt state to all disabled */
	cik_disable_पूर्णांकerrupt_state(rdev);

	pci_set_master(rdev->pdev);

	/* enable irqs */
	cik_enable_पूर्णांकerrupts(rdev);

	वापस ret;
पूर्ण

/**
 * cik_irq_set - enable/disable पूर्णांकerrupt sources
 *
 * @rdev: radeon_device poपूर्णांकer
 *
 * Enable पूर्णांकerrupt sources on the GPU (vblanks, hpd,
 * etc.) (CIK).
 * Returns 0 क्रम success, errors क्रम failure.
 */
पूर्णांक cik_irq_set(काष्ठा radeon_device *rdev)
अणु
	u32 cp_पूर्णांक_cntl;
	u32 cp_m1p0, cp_m1p1, cp_m1p2, cp_m1p3;
	u32 cp_m2p0, cp_m2p1, cp_m2p2, cp_m2p3;
	u32 crtc1 = 0, crtc2 = 0, crtc3 = 0, crtc4 = 0, crtc5 = 0, crtc6 = 0;
	u32 hpd1, hpd2, hpd3, hpd4, hpd5, hpd6;
	u32 grbm_पूर्णांक_cntl = 0;
	u32 dma_cntl, dma_cntl1;

	अगर (!rdev->irq.installed) अणु
		WARN(1, "Can't enable IRQ/MSI because no handler is installed\n");
		वापस -EINVAL;
	पूर्ण
	/* करोn't enable anything अगर the ih is disabled */
	अगर (!rdev->ih.enabled) अणु
		cik_disable_पूर्णांकerrupts(rdev);
		/* क्रमce the active पूर्णांकerrupt state to all disabled */
		cik_disable_पूर्णांकerrupt_state(rdev);
		वापस 0;
	पूर्ण

	cp_पूर्णांक_cntl = RREG32(CP_INT_CNTL_RING0) &
		(CNTX_BUSY_INT_ENABLE | CNTX_EMPTY_INT_ENABLE);
	cp_पूर्णांक_cntl |= PRIV_INSTR_INT_ENABLE | PRIV_REG_INT_ENABLE;

	hpd1 = RREG32(DC_HPD1_INT_CONTROL) & ~(DC_HPDx_INT_EN | DC_HPDx_RX_INT_EN);
	hpd2 = RREG32(DC_HPD2_INT_CONTROL) & ~(DC_HPDx_INT_EN | DC_HPDx_RX_INT_EN);
	hpd3 = RREG32(DC_HPD3_INT_CONTROL) & ~(DC_HPDx_INT_EN | DC_HPDx_RX_INT_EN);
	hpd4 = RREG32(DC_HPD4_INT_CONTROL) & ~(DC_HPDx_INT_EN | DC_HPDx_RX_INT_EN);
	hpd5 = RREG32(DC_HPD5_INT_CONTROL) & ~(DC_HPDx_INT_EN | DC_HPDx_RX_INT_EN);
	hpd6 = RREG32(DC_HPD6_INT_CONTROL) & ~(DC_HPDx_INT_EN | DC_HPDx_RX_INT_EN);

	dma_cntl = RREG32(SDMA0_CNTL + SDMA0_REGISTER_OFFSET) & ~TRAP_ENABLE;
	dma_cntl1 = RREG32(SDMA0_CNTL + SDMA1_REGISTER_OFFSET) & ~TRAP_ENABLE;

	cp_m1p0 = RREG32(CP_ME1_PIPE0_INT_CNTL) & ~TIME_STAMP_INT_ENABLE;
	cp_m1p1 = RREG32(CP_ME1_PIPE1_INT_CNTL) & ~TIME_STAMP_INT_ENABLE;
	cp_m1p2 = RREG32(CP_ME1_PIPE2_INT_CNTL) & ~TIME_STAMP_INT_ENABLE;
	cp_m1p3 = RREG32(CP_ME1_PIPE3_INT_CNTL) & ~TIME_STAMP_INT_ENABLE;
	cp_m2p0 = RREG32(CP_ME2_PIPE0_INT_CNTL) & ~TIME_STAMP_INT_ENABLE;
	cp_m2p1 = RREG32(CP_ME2_PIPE1_INT_CNTL) & ~TIME_STAMP_INT_ENABLE;
	cp_m2p2 = RREG32(CP_ME2_PIPE2_INT_CNTL) & ~TIME_STAMP_INT_ENABLE;
	cp_m2p3 = RREG32(CP_ME2_PIPE3_INT_CNTL) & ~TIME_STAMP_INT_ENABLE;

	/* enable CP पूर्णांकerrupts on all rings */
	अगर (atomic_पढ़ो(&rdev->irq.ring_पूर्णांक[RADEON_RING_TYPE_GFX_INDEX])) अणु
		DRM_DEBUG("cik_irq_set: sw int gfx\n");
		cp_पूर्णांक_cntl |= TIME_STAMP_INT_ENABLE;
	पूर्ण
	अगर (atomic_पढ़ो(&rdev->irq.ring_पूर्णांक[CAYMAN_RING_TYPE_CP1_INDEX])) अणु
		काष्ठा radeon_ring *ring = &rdev->ring[CAYMAN_RING_TYPE_CP1_INDEX];
		DRM_DEBUG("si_irq_set: sw int cp1\n");
		अगर (ring->me == 1) अणु
			चयन (ring->pipe) अणु
			हाल 0:
				cp_m1p0 |= TIME_STAMP_INT_ENABLE;
				अवरोध;
			हाल 1:
				cp_m1p1 |= TIME_STAMP_INT_ENABLE;
				अवरोध;
			हाल 2:
				cp_m1p2 |= TIME_STAMP_INT_ENABLE;
				अवरोध;
			हाल 3:
				cp_m1p2 |= TIME_STAMP_INT_ENABLE;
				अवरोध;
			शेष:
				DRM_DEBUG("si_irq_set: sw int cp1 invalid pipe %d\n", ring->pipe);
				अवरोध;
			पूर्ण
		पूर्ण अन्यथा अगर (ring->me == 2) अणु
			चयन (ring->pipe) अणु
			हाल 0:
				cp_m2p0 |= TIME_STAMP_INT_ENABLE;
				अवरोध;
			हाल 1:
				cp_m2p1 |= TIME_STAMP_INT_ENABLE;
				अवरोध;
			हाल 2:
				cp_m2p2 |= TIME_STAMP_INT_ENABLE;
				अवरोध;
			हाल 3:
				cp_m2p2 |= TIME_STAMP_INT_ENABLE;
				अवरोध;
			शेष:
				DRM_DEBUG("si_irq_set: sw int cp1 invalid pipe %d\n", ring->pipe);
				अवरोध;
			पूर्ण
		पूर्ण अन्यथा अणु
			DRM_DEBUG("si_irq_set: sw int cp1 invalid me %d\n", ring->me);
		पूर्ण
	पूर्ण
	अगर (atomic_पढ़ो(&rdev->irq.ring_पूर्णांक[CAYMAN_RING_TYPE_CP2_INDEX])) अणु
		काष्ठा radeon_ring *ring = &rdev->ring[CAYMAN_RING_TYPE_CP2_INDEX];
		DRM_DEBUG("si_irq_set: sw int cp2\n");
		अगर (ring->me == 1) अणु
			चयन (ring->pipe) अणु
			हाल 0:
				cp_m1p0 |= TIME_STAMP_INT_ENABLE;
				अवरोध;
			हाल 1:
				cp_m1p1 |= TIME_STAMP_INT_ENABLE;
				अवरोध;
			हाल 2:
				cp_m1p2 |= TIME_STAMP_INT_ENABLE;
				अवरोध;
			हाल 3:
				cp_m1p2 |= TIME_STAMP_INT_ENABLE;
				अवरोध;
			शेष:
				DRM_DEBUG("si_irq_set: sw int cp2 invalid pipe %d\n", ring->pipe);
				अवरोध;
			पूर्ण
		पूर्ण अन्यथा अगर (ring->me == 2) अणु
			चयन (ring->pipe) अणु
			हाल 0:
				cp_m2p0 |= TIME_STAMP_INT_ENABLE;
				अवरोध;
			हाल 1:
				cp_m2p1 |= TIME_STAMP_INT_ENABLE;
				अवरोध;
			हाल 2:
				cp_m2p2 |= TIME_STAMP_INT_ENABLE;
				अवरोध;
			हाल 3:
				cp_m2p2 |= TIME_STAMP_INT_ENABLE;
				अवरोध;
			शेष:
				DRM_DEBUG("si_irq_set: sw int cp2 invalid pipe %d\n", ring->pipe);
				अवरोध;
			पूर्ण
		पूर्ण अन्यथा अणु
			DRM_DEBUG("si_irq_set: sw int cp2 invalid me %d\n", ring->me);
		पूर्ण
	पूर्ण

	अगर (atomic_पढ़ो(&rdev->irq.ring_पूर्णांक[R600_RING_TYPE_DMA_INDEX])) अणु
		DRM_DEBUG("cik_irq_set: sw int dma\n");
		dma_cntl |= TRAP_ENABLE;
	पूर्ण

	अगर (atomic_पढ़ो(&rdev->irq.ring_पूर्णांक[CAYMAN_RING_TYPE_DMA1_INDEX])) अणु
		DRM_DEBUG("cik_irq_set: sw int dma1\n");
		dma_cntl1 |= TRAP_ENABLE;
	पूर्ण

	अगर (rdev->irq.crtc_vblank_पूर्णांक[0] ||
	    atomic_पढ़ो(&rdev->irq.pflip[0])) अणु
		DRM_DEBUG("cik_irq_set: vblank 0\n");
		crtc1 |= VBLANK_INTERRUPT_MASK;
	पूर्ण
	अगर (rdev->irq.crtc_vblank_पूर्णांक[1] ||
	    atomic_पढ़ो(&rdev->irq.pflip[1])) अणु
		DRM_DEBUG("cik_irq_set: vblank 1\n");
		crtc2 |= VBLANK_INTERRUPT_MASK;
	पूर्ण
	अगर (rdev->irq.crtc_vblank_पूर्णांक[2] ||
	    atomic_पढ़ो(&rdev->irq.pflip[2])) अणु
		DRM_DEBUG("cik_irq_set: vblank 2\n");
		crtc3 |= VBLANK_INTERRUPT_MASK;
	पूर्ण
	अगर (rdev->irq.crtc_vblank_पूर्णांक[3] ||
	    atomic_पढ़ो(&rdev->irq.pflip[3])) अणु
		DRM_DEBUG("cik_irq_set: vblank 3\n");
		crtc4 |= VBLANK_INTERRUPT_MASK;
	पूर्ण
	अगर (rdev->irq.crtc_vblank_पूर्णांक[4] ||
	    atomic_पढ़ो(&rdev->irq.pflip[4])) अणु
		DRM_DEBUG("cik_irq_set: vblank 4\n");
		crtc5 |= VBLANK_INTERRUPT_MASK;
	पूर्ण
	अगर (rdev->irq.crtc_vblank_पूर्णांक[5] ||
	    atomic_पढ़ो(&rdev->irq.pflip[5])) अणु
		DRM_DEBUG("cik_irq_set: vblank 5\n");
		crtc6 |= VBLANK_INTERRUPT_MASK;
	पूर्ण
	अगर (rdev->irq.hpd[0]) अणु
		DRM_DEBUG("cik_irq_set: hpd 1\n");
		hpd1 |= DC_HPDx_INT_EN | DC_HPDx_RX_INT_EN;
	पूर्ण
	अगर (rdev->irq.hpd[1]) अणु
		DRM_DEBUG("cik_irq_set: hpd 2\n");
		hpd2 |= DC_HPDx_INT_EN | DC_HPDx_RX_INT_EN;
	पूर्ण
	अगर (rdev->irq.hpd[2]) अणु
		DRM_DEBUG("cik_irq_set: hpd 3\n");
		hpd3 |= DC_HPDx_INT_EN | DC_HPDx_RX_INT_EN;
	पूर्ण
	अगर (rdev->irq.hpd[3]) अणु
		DRM_DEBUG("cik_irq_set: hpd 4\n");
		hpd4 |= DC_HPDx_INT_EN | DC_HPDx_RX_INT_EN;
	पूर्ण
	अगर (rdev->irq.hpd[4]) अणु
		DRM_DEBUG("cik_irq_set: hpd 5\n");
		hpd5 |= DC_HPDx_INT_EN | DC_HPDx_RX_INT_EN;
	पूर्ण
	अगर (rdev->irq.hpd[5]) अणु
		DRM_DEBUG("cik_irq_set: hpd 6\n");
		hpd6 |= DC_HPDx_INT_EN | DC_HPDx_RX_INT_EN;
	पूर्ण

	WREG32(CP_INT_CNTL_RING0, cp_पूर्णांक_cntl);

	WREG32(SDMA0_CNTL + SDMA0_REGISTER_OFFSET, dma_cntl);
	WREG32(SDMA0_CNTL + SDMA1_REGISTER_OFFSET, dma_cntl1);

	WREG32(CP_ME1_PIPE0_INT_CNTL, cp_m1p0);
	WREG32(CP_ME1_PIPE1_INT_CNTL, cp_m1p1);
	WREG32(CP_ME1_PIPE2_INT_CNTL, cp_m1p2);
	WREG32(CP_ME1_PIPE3_INT_CNTL, cp_m1p3);
	WREG32(CP_ME2_PIPE0_INT_CNTL, cp_m2p0);
	WREG32(CP_ME2_PIPE1_INT_CNTL, cp_m2p1);
	WREG32(CP_ME2_PIPE2_INT_CNTL, cp_m2p2);
	WREG32(CP_ME2_PIPE3_INT_CNTL, cp_m2p3);

	WREG32(GRBM_INT_CNTL, grbm_पूर्णांक_cntl);

	WREG32(LB_INTERRUPT_MASK + EVERGREEN_CRTC0_REGISTER_OFFSET, crtc1);
	WREG32(LB_INTERRUPT_MASK + EVERGREEN_CRTC1_REGISTER_OFFSET, crtc2);
	अगर (rdev->num_crtc >= 4) अणु
		WREG32(LB_INTERRUPT_MASK + EVERGREEN_CRTC2_REGISTER_OFFSET, crtc3);
		WREG32(LB_INTERRUPT_MASK + EVERGREEN_CRTC3_REGISTER_OFFSET, crtc4);
	पूर्ण
	अगर (rdev->num_crtc >= 6) अणु
		WREG32(LB_INTERRUPT_MASK + EVERGREEN_CRTC4_REGISTER_OFFSET, crtc5);
		WREG32(LB_INTERRUPT_MASK + EVERGREEN_CRTC5_REGISTER_OFFSET, crtc6);
	पूर्ण

	अगर (rdev->num_crtc >= 2) अणु
		WREG32(GRPH_INT_CONTROL + EVERGREEN_CRTC0_REGISTER_OFFSET,
		       GRPH_PFLIP_INT_MASK);
		WREG32(GRPH_INT_CONTROL + EVERGREEN_CRTC1_REGISTER_OFFSET,
		       GRPH_PFLIP_INT_MASK);
	पूर्ण
	अगर (rdev->num_crtc >= 4) अणु
		WREG32(GRPH_INT_CONTROL + EVERGREEN_CRTC2_REGISTER_OFFSET,
		       GRPH_PFLIP_INT_MASK);
		WREG32(GRPH_INT_CONTROL + EVERGREEN_CRTC3_REGISTER_OFFSET,
		       GRPH_PFLIP_INT_MASK);
	पूर्ण
	अगर (rdev->num_crtc >= 6) अणु
		WREG32(GRPH_INT_CONTROL + EVERGREEN_CRTC4_REGISTER_OFFSET,
		       GRPH_PFLIP_INT_MASK);
		WREG32(GRPH_INT_CONTROL + EVERGREEN_CRTC5_REGISTER_OFFSET,
		       GRPH_PFLIP_INT_MASK);
	पूर्ण

	WREG32(DC_HPD1_INT_CONTROL, hpd1);
	WREG32(DC_HPD2_INT_CONTROL, hpd2);
	WREG32(DC_HPD3_INT_CONTROL, hpd3);
	WREG32(DC_HPD4_INT_CONTROL, hpd4);
	WREG32(DC_HPD5_INT_CONTROL, hpd5);
	WREG32(DC_HPD6_INT_CONTROL, hpd6);

	/* posting पढ़ो */
	RREG32(SRBM_STATUS);

	वापस 0;
पूर्ण

/**
 * cik_irq_ack - ack पूर्णांकerrupt sources
 *
 * @rdev: radeon_device poपूर्णांकer
 *
 * Ack पूर्णांकerrupt sources on the GPU (vblanks, hpd,
 * etc.) (CIK).  Certain पूर्णांकerrupts sources are sw
 * generated and करो not require an explicit ack.
 */
अटल अंतरभूत व्योम cik_irq_ack(काष्ठा radeon_device *rdev)
अणु
	u32 पंचांगp;

	rdev->irq.stat_regs.cik.disp_पूर्णांक = RREG32(DISP_INTERRUPT_STATUS);
	rdev->irq.stat_regs.cik.disp_पूर्णांक_cont = RREG32(DISP_INTERRUPT_STATUS_CONTINUE);
	rdev->irq.stat_regs.cik.disp_पूर्णांक_cont2 = RREG32(DISP_INTERRUPT_STATUS_CONTINUE2);
	rdev->irq.stat_regs.cik.disp_पूर्णांक_cont3 = RREG32(DISP_INTERRUPT_STATUS_CONTINUE3);
	rdev->irq.stat_regs.cik.disp_पूर्णांक_cont4 = RREG32(DISP_INTERRUPT_STATUS_CONTINUE4);
	rdev->irq.stat_regs.cik.disp_पूर्णांक_cont5 = RREG32(DISP_INTERRUPT_STATUS_CONTINUE5);
	rdev->irq.stat_regs.cik.disp_पूर्णांक_cont6 = RREG32(DISP_INTERRUPT_STATUS_CONTINUE6);

	rdev->irq.stat_regs.cik.d1grph_पूर्णांक = RREG32(GRPH_INT_STATUS +
		EVERGREEN_CRTC0_REGISTER_OFFSET);
	rdev->irq.stat_regs.cik.d2grph_पूर्णांक = RREG32(GRPH_INT_STATUS +
		EVERGREEN_CRTC1_REGISTER_OFFSET);
	अगर (rdev->num_crtc >= 4) अणु
		rdev->irq.stat_regs.cik.d3grph_पूर्णांक = RREG32(GRPH_INT_STATUS +
			EVERGREEN_CRTC2_REGISTER_OFFSET);
		rdev->irq.stat_regs.cik.d4grph_पूर्णांक = RREG32(GRPH_INT_STATUS +
			EVERGREEN_CRTC3_REGISTER_OFFSET);
	पूर्ण
	अगर (rdev->num_crtc >= 6) अणु
		rdev->irq.stat_regs.cik.d5grph_पूर्णांक = RREG32(GRPH_INT_STATUS +
			EVERGREEN_CRTC4_REGISTER_OFFSET);
		rdev->irq.stat_regs.cik.d6grph_पूर्णांक = RREG32(GRPH_INT_STATUS +
			EVERGREEN_CRTC5_REGISTER_OFFSET);
	पूर्ण

	अगर (rdev->irq.stat_regs.cik.d1grph_पूर्णांक & GRPH_PFLIP_INT_OCCURRED)
		WREG32(GRPH_INT_STATUS + EVERGREEN_CRTC0_REGISTER_OFFSET,
		       GRPH_PFLIP_INT_CLEAR);
	अगर (rdev->irq.stat_regs.cik.d2grph_पूर्णांक & GRPH_PFLIP_INT_OCCURRED)
		WREG32(GRPH_INT_STATUS + EVERGREEN_CRTC1_REGISTER_OFFSET,
		       GRPH_PFLIP_INT_CLEAR);
	अगर (rdev->irq.stat_regs.cik.disp_पूर्णांक & LB_D1_VBLANK_INTERRUPT)
		WREG32(LB_VBLANK_STATUS + EVERGREEN_CRTC0_REGISTER_OFFSET, VBLANK_ACK);
	अगर (rdev->irq.stat_regs.cik.disp_पूर्णांक & LB_D1_VLINE_INTERRUPT)
		WREG32(LB_VLINE_STATUS + EVERGREEN_CRTC0_REGISTER_OFFSET, VLINE_ACK);
	अगर (rdev->irq.stat_regs.cik.disp_पूर्णांक_cont & LB_D2_VBLANK_INTERRUPT)
		WREG32(LB_VBLANK_STATUS + EVERGREEN_CRTC1_REGISTER_OFFSET, VBLANK_ACK);
	अगर (rdev->irq.stat_regs.cik.disp_पूर्णांक_cont & LB_D2_VLINE_INTERRUPT)
		WREG32(LB_VLINE_STATUS + EVERGREEN_CRTC1_REGISTER_OFFSET, VLINE_ACK);

	अगर (rdev->num_crtc >= 4) अणु
		अगर (rdev->irq.stat_regs.cik.d3grph_पूर्णांक & GRPH_PFLIP_INT_OCCURRED)
			WREG32(GRPH_INT_STATUS + EVERGREEN_CRTC2_REGISTER_OFFSET,
			       GRPH_PFLIP_INT_CLEAR);
		अगर (rdev->irq.stat_regs.cik.d4grph_पूर्णांक & GRPH_PFLIP_INT_OCCURRED)
			WREG32(GRPH_INT_STATUS + EVERGREEN_CRTC3_REGISTER_OFFSET,
			       GRPH_PFLIP_INT_CLEAR);
		अगर (rdev->irq.stat_regs.cik.disp_पूर्णांक_cont2 & LB_D3_VBLANK_INTERRUPT)
			WREG32(LB_VBLANK_STATUS + EVERGREEN_CRTC2_REGISTER_OFFSET, VBLANK_ACK);
		अगर (rdev->irq.stat_regs.cik.disp_पूर्णांक_cont2 & LB_D3_VLINE_INTERRUPT)
			WREG32(LB_VLINE_STATUS + EVERGREEN_CRTC2_REGISTER_OFFSET, VLINE_ACK);
		अगर (rdev->irq.stat_regs.cik.disp_पूर्णांक_cont3 & LB_D4_VBLANK_INTERRUPT)
			WREG32(LB_VBLANK_STATUS + EVERGREEN_CRTC3_REGISTER_OFFSET, VBLANK_ACK);
		अगर (rdev->irq.stat_regs.cik.disp_पूर्णांक_cont3 & LB_D4_VLINE_INTERRUPT)
			WREG32(LB_VLINE_STATUS + EVERGREEN_CRTC3_REGISTER_OFFSET, VLINE_ACK);
	पूर्ण

	अगर (rdev->num_crtc >= 6) अणु
		अगर (rdev->irq.stat_regs.cik.d5grph_पूर्णांक & GRPH_PFLIP_INT_OCCURRED)
			WREG32(GRPH_INT_STATUS + EVERGREEN_CRTC4_REGISTER_OFFSET,
			       GRPH_PFLIP_INT_CLEAR);
		अगर (rdev->irq.stat_regs.cik.d6grph_पूर्णांक & GRPH_PFLIP_INT_OCCURRED)
			WREG32(GRPH_INT_STATUS + EVERGREEN_CRTC5_REGISTER_OFFSET,
			       GRPH_PFLIP_INT_CLEAR);
		अगर (rdev->irq.stat_regs.cik.disp_पूर्णांक_cont4 & LB_D5_VBLANK_INTERRUPT)
			WREG32(LB_VBLANK_STATUS + EVERGREEN_CRTC4_REGISTER_OFFSET, VBLANK_ACK);
		अगर (rdev->irq.stat_regs.cik.disp_पूर्णांक_cont4 & LB_D5_VLINE_INTERRUPT)
			WREG32(LB_VLINE_STATUS + EVERGREEN_CRTC4_REGISTER_OFFSET, VLINE_ACK);
		अगर (rdev->irq.stat_regs.cik.disp_पूर्णांक_cont5 & LB_D6_VBLANK_INTERRUPT)
			WREG32(LB_VBLANK_STATUS + EVERGREEN_CRTC5_REGISTER_OFFSET, VBLANK_ACK);
		अगर (rdev->irq.stat_regs.cik.disp_पूर्णांक_cont5 & LB_D6_VLINE_INTERRUPT)
			WREG32(LB_VLINE_STATUS + EVERGREEN_CRTC5_REGISTER_OFFSET, VLINE_ACK);
	पूर्ण

	अगर (rdev->irq.stat_regs.cik.disp_पूर्णांक & DC_HPD1_INTERRUPT) अणु
		पंचांगp = RREG32(DC_HPD1_INT_CONTROL);
		पंचांगp |= DC_HPDx_INT_ACK;
		WREG32(DC_HPD1_INT_CONTROL, पंचांगp);
	पूर्ण
	अगर (rdev->irq.stat_regs.cik.disp_पूर्णांक_cont & DC_HPD2_INTERRUPT) अणु
		पंचांगp = RREG32(DC_HPD2_INT_CONTROL);
		पंचांगp |= DC_HPDx_INT_ACK;
		WREG32(DC_HPD2_INT_CONTROL, पंचांगp);
	पूर्ण
	अगर (rdev->irq.stat_regs.cik.disp_पूर्णांक_cont2 & DC_HPD3_INTERRUPT) अणु
		पंचांगp = RREG32(DC_HPD3_INT_CONTROL);
		पंचांगp |= DC_HPDx_INT_ACK;
		WREG32(DC_HPD3_INT_CONTROL, पंचांगp);
	पूर्ण
	अगर (rdev->irq.stat_regs.cik.disp_पूर्णांक_cont3 & DC_HPD4_INTERRUPT) अणु
		पंचांगp = RREG32(DC_HPD4_INT_CONTROL);
		पंचांगp |= DC_HPDx_INT_ACK;
		WREG32(DC_HPD4_INT_CONTROL, पंचांगp);
	पूर्ण
	अगर (rdev->irq.stat_regs.cik.disp_पूर्णांक_cont4 & DC_HPD5_INTERRUPT) अणु
		पंचांगp = RREG32(DC_HPD5_INT_CONTROL);
		पंचांगp |= DC_HPDx_INT_ACK;
		WREG32(DC_HPD5_INT_CONTROL, पंचांगp);
	पूर्ण
	अगर (rdev->irq.stat_regs.cik.disp_पूर्णांक_cont5 & DC_HPD6_INTERRUPT) अणु
		पंचांगp = RREG32(DC_HPD6_INT_CONTROL);
		पंचांगp |= DC_HPDx_INT_ACK;
		WREG32(DC_HPD6_INT_CONTROL, पंचांगp);
	पूर्ण
	अगर (rdev->irq.stat_regs.cik.disp_पूर्णांक & DC_HPD1_RX_INTERRUPT) अणु
		पंचांगp = RREG32(DC_HPD1_INT_CONTROL);
		पंचांगp |= DC_HPDx_RX_INT_ACK;
		WREG32(DC_HPD1_INT_CONTROL, पंचांगp);
	पूर्ण
	अगर (rdev->irq.stat_regs.cik.disp_पूर्णांक_cont & DC_HPD2_RX_INTERRUPT) अणु
		पंचांगp = RREG32(DC_HPD2_INT_CONTROL);
		पंचांगp |= DC_HPDx_RX_INT_ACK;
		WREG32(DC_HPD2_INT_CONTROL, पंचांगp);
	पूर्ण
	अगर (rdev->irq.stat_regs.cik.disp_पूर्णांक_cont2 & DC_HPD3_RX_INTERRUPT) अणु
		पंचांगp = RREG32(DC_HPD3_INT_CONTROL);
		पंचांगp |= DC_HPDx_RX_INT_ACK;
		WREG32(DC_HPD3_INT_CONTROL, पंचांगp);
	पूर्ण
	अगर (rdev->irq.stat_regs.cik.disp_पूर्णांक_cont3 & DC_HPD4_RX_INTERRUPT) अणु
		पंचांगp = RREG32(DC_HPD4_INT_CONTROL);
		पंचांगp |= DC_HPDx_RX_INT_ACK;
		WREG32(DC_HPD4_INT_CONTROL, पंचांगp);
	पूर्ण
	अगर (rdev->irq.stat_regs.cik.disp_पूर्णांक_cont4 & DC_HPD5_RX_INTERRUPT) अणु
		पंचांगp = RREG32(DC_HPD5_INT_CONTROL);
		पंचांगp |= DC_HPDx_RX_INT_ACK;
		WREG32(DC_HPD5_INT_CONTROL, पंचांगp);
	पूर्ण
	अगर (rdev->irq.stat_regs.cik.disp_पूर्णांक_cont5 & DC_HPD6_RX_INTERRUPT) अणु
		पंचांगp = RREG32(DC_HPD6_INT_CONTROL);
		पंचांगp |= DC_HPDx_RX_INT_ACK;
		WREG32(DC_HPD6_INT_CONTROL, पंचांगp);
	पूर्ण
पूर्ण

/**
 * cik_irq_disable - disable पूर्णांकerrupts
 *
 * @rdev: radeon_device poपूर्णांकer
 *
 * Disable पूर्णांकerrupts on the hw (CIK).
 */
अटल व्योम cik_irq_disable(काष्ठा radeon_device *rdev)
अणु
	cik_disable_पूर्णांकerrupts(rdev);
	/* Wait and acknowledge irq */
	mdelay(1);
	cik_irq_ack(rdev);
	cik_disable_पूर्णांकerrupt_state(rdev);
पूर्ण

/**
 * cik_irq_disable - disable पूर्णांकerrupts क्रम suspend
 *
 * @rdev: radeon_device poपूर्णांकer
 *
 * Disable पूर्णांकerrupts and stop the RLC (CIK).
 * Used क्रम suspend.
 */
अटल व्योम cik_irq_suspend(काष्ठा radeon_device *rdev)
अणु
	cik_irq_disable(rdev);
	cik_rlc_stop(rdev);
पूर्ण

/**
 * cik_irq_fini - tear करोwn पूर्णांकerrupt support
 *
 * @rdev: radeon_device poपूर्णांकer
 *
 * Disable पूर्णांकerrupts on the hw and मुक्त the IH ring
 * buffer (CIK).
 * Used क्रम driver unload.
 */
अटल व्योम cik_irq_fini(काष्ठा radeon_device *rdev)
अणु
	cik_irq_suspend(rdev);
	r600_ih_ring_fini(rdev);
पूर्ण

/**
 * cik_get_ih_wptr - get the IH ring buffer wptr
 *
 * @rdev: radeon_device poपूर्णांकer
 *
 * Get the IH ring buffer wptr from either the रेजिस्टर
 * or the ग_लिखोback memory buffer (CIK).  Also check क्रम
 * ring buffer overflow and deal with it.
 * Used by cik_irq_process().
 * Returns the value of the wptr.
 */
अटल अंतरभूत u32 cik_get_ih_wptr(काष्ठा radeon_device *rdev)
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

/*        CIK IV Ring
 * Each IV ring entry is 128 bits:
 * [7:0]    - पूर्णांकerrupt source id
 * [31:8]   - reserved
 * [59:32]  - पूर्णांकerrupt source data
 * [63:60]  - reserved
 * [71:64]  - RINGID
 *            CP:
 *            ME_ID [1:0], PIPE_ID[1:0], QUEUE_ID[2:0]
 *            QUEUE_ID - क्रम compute, which of the 8 queues owned by the dispatcher
 *                     - क्रम gfx, hw shader state (0=PS...5=LS, 6=CS)
 *            ME_ID - 0 = gfx, 1 = first 4 CS pipes, 2 = second 4 CS pipes
 *            PIPE_ID - ME0 0=3D
 *                    - ME1&2 compute dispatcher (4 pipes each)
 *            SDMA:
 *            INSTANCE_ID [1:0], QUEUE_ID[1:0]
 *            INSTANCE_ID - 0 = sdma0, 1 = sdma1
 *            QUEUE_ID - 0 = gfx, 1 = rlc0, 2 = rlc1
 * [79:72]  - VMID
 * [95:80]  - PASID
 * [127:96] - reserved
 */
/**
 * cik_irq_process - पूर्णांकerrupt handler
 *
 * @rdev: radeon_device poपूर्णांकer
 *
 * Interrupt hander (CIK).  Walk the IH ring,
 * ack पूर्णांकerrupts and schedule work to handle
 * पूर्णांकerrupt events.
 * Returns irq process वापस code.
 */
पूर्णांक cik_irq_process(काष्ठा radeon_device *rdev)
अणु
	काष्ठा radeon_ring *cp1_ring = &rdev->ring[CAYMAN_RING_TYPE_CP1_INDEX];
	काष्ठा radeon_ring *cp2_ring = &rdev->ring[CAYMAN_RING_TYPE_CP2_INDEX];
	u32 wptr;
	u32 rptr;
	u32 src_id, src_data, ring_id;
	u8 me_id, pipe_id, queue_id;
	u32 ring_index;
	bool queue_hotplug = false;
	bool queue_dp = false;
	bool queue_reset = false;
	u32 addr, status, mc_client;
	bool queue_thermal = false;

	अगर (!rdev->ih.enabled || rdev->shutकरोwn)
		वापस IRQ_NONE;

	wptr = cik_get_ih_wptr(rdev);

restart_ih:
	/* is somebody अन्यथा alपढ़ोy processing irqs? */
	अगर (atomic_xchg(&rdev->ih.lock, 1))
		वापस IRQ_NONE;

	rptr = rdev->ih.rptr;
	DRM_DEBUG("cik_irq_process start: rptr %d, wptr %d\n", rptr, wptr);

	/* Order पढ़ोing of wptr vs. पढ़ोing of IH ring data */
	rmb();

	/* display पूर्णांकerrupts */
	cik_irq_ack(rdev);

	जबतक (rptr != wptr) अणु
		/* wptr/rptr are in bytes! */
		ring_index = rptr / 4;

		src_id =  le32_to_cpu(rdev->ih.ring[ring_index]) & 0xff;
		src_data = le32_to_cpu(rdev->ih.ring[ring_index + 1]) & 0xfffffff;
		ring_id = le32_to_cpu(rdev->ih.ring[ring_index + 2]) & 0xff;

		चयन (src_id) अणु
		हाल 1: /* D1 vblank/vline */
			चयन (src_data) अणु
			हाल 0: /* D1 vblank */
				अगर (!(rdev->irq.stat_regs.cik.disp_पूर्णांक & LB_D1_VBLANK_INTERRUPT))
					DRM_DEBUG("IH: IH event w/o asserted irq bit?\n");

				अगर (rdev->irq.crtc_vblank_पूर्णांक[0]) अणु
					drm_handle_vblank(rdev->ddev, 0);
					rdev->pm.vblank_sync = true;
					wake_up(&rdev->irq.vblank_queue);
				पूर्ण
				अगर (atomic_पढ़ो(&rdev->irq.pflip[0]))
					radeon_crtc_handle_vblank(rdev, 0);
				rdev->irq.stat_regs.cik.disp_पूर्णांक &= ~LB_D1_VBLANK_INTERRUPT;
				DRM_DEBUG("IH: D1 vblank\n");

				अवरोध;
			हाल 1: /* D1 vline */
				अगर (!(rdev->irq.stat_regs.cik.disp_पूर्णांक & LB_D1_VLINE_INTERRUPT))
					DRM_DEBUG("IH: IH event w/o asserted irq bit?\n");

				rdev->irq.stat_regs.cik.disp_पूर्णांक &= ~LB_D1_VLINE_INTERRUPT;
				DRM_DEBUG("IH: D1 vline\n");

				अवरोध;
			शेष:
				DRM_DEBUG("Unhandled interrupt: %d %d\n", src_id, src_data);
				अवरोध;
			पूर्ण
			अवरोध;
		हाल 2: /* D2 vblank/vline */
			चयन (src_data) अणु
			हाल 0: /* D2 vblank */
				अगर (!(rdev->irq.stat_regs.cik.disp_पूर्णांक_cont & LB_D2_VBLANK_INTERRUPT))
					DRM_DEBUG("IH: IH event w/o asserted irq bit?\n");

				अगर (rdev->irq.crtc_vblank_पूर्णांक[1]) अणु
					drm_handle_vblank(rdev->ddev, 1);
					rdev->pm.vblank_sync = true;
					wake_up(&rdev->irq.vblank_queue);
				पूर्ण
				अगर (atomic_पढ़ो(&rdev->irq.pflip[1]))
					radeon_crtc_handle_vblank(rdev, 1);
				rdev->irq.stat_regs.cik.disp_पूर्णांक_cont &= ~LB_D2_VBLANK_INTERRUPT;
				DRM_DEBUG("IH: D2 vblank\n");

				अवरोध;
			हाल 1: /* D2 vline */
				अगर (!(rdev->irq.stat_regs.cik.disp_पूर्णांक_cont & LB_D2_VLINE_INTERRUPT))
					DRM_DEBUG("IH: IH event w/o asserted irq bit?\n");

				rdev->irq.stat_regs.cik.disp_पूर्णांक_cont &= ~LB_D2_VLINE_INTERRUPT;
				DRM_DEBUG("IH: D2 vline\n");

				अवरोध;
			शेष:
				DRM_DEBUG("Unhandled interrupt: %d %d\n", src_id, src_data);
				अवरोध;
			पूर्ण
			अवरोध;
		हाल 3: /* D3 vblank/vline */
			चयन (src_data) अणु
			हाल 0: /* D3 vblank */
				अगर (!(rdev->irq.stat_regs.cik.disp_पूर्णांक_cont2 & LB_D3_VBLANK_INTERRUPT))
					DRM_DEBUG("IH: IH event w/o asserted irq bit?\n");

				अगर (rdev->irq.crtc_vblank_पूर्णांक[2]) अणु
					drm_handle_vblank(rdev->ddev, 2);
					rdev->pm.vblank_sync = true;
					wake_up(&rdev->irq.vblank_queue);
				पूर्ण
				अगर (atomic_पढ़ो(&rdev->irq.pflip[2]))
					radeon_crtc_handle_vblank(rdev, 2);
				rdev->irq.stat_regs.cik.disp_पूर्णांक_cont2 &= ~LB_D3_VBLANK_INTERRUPT;
				DRM_DEBUG("IH: D3 vblank\n");

				अवरोध;
			हाल 1: /* D3 vline */
				अगर (!(rdev->irq.stat_regs.cik.disp_पूर्णांक_cont2 & LB_D3_VLINE_INTERRUPT))
					DRM_DEBUG("IH: IH event w/o asserted irq bit?\n");

				rdev->irq.stat_regs.cik.disp_पूर्णांक_cont2 &= ~LB_D3_VLINE_INTERRUPT;
				DRM_DEBUG("IH: D3 vline\n");

				अवरोध;
			शेष:
				DRM_DEBUG("Unhandled interrupt: %d %d\n", src_id, src_data);
				अवरोध;
			पूर्ण
			अवरोध;
		हाल 4: /* D4 vblank/vline */
			चयन (src_data) अणु
			हाल 0: /* D4 vblank */
				अगर (!(rdev->irq.stat_regs.cik.disp_पूर्णांक_cont3 & LB_D4_VBLANK_INTERRUPT))
					DRM_DEBUG("IH: IH event w/o asserted irq bit?\n");

				अगर (rdev->irq.crtc_vblank_पूर्णांक[3]) अणु
					drm_handle_vblank(rdev->ddev, 3);
					rdev->pm.vblank_sync = true;
					wake_up(&rdev->irq.vblank_queue);
				पूर्ण
				अगर (atomic_पढ़ो(&rdev->irq.pflip[3]))
					radeon_crtc_handle_vblank(rdev, 3);
				rdev->irq.stat_regs.cik.disp_पूर्णांक_cont3 &= ~LB_D4_VBLANK_INTERRUPT;
				DRM_DEBUG("IH: D4 vblank\n");

				अवरोध;
			हाल 1: /* D4 vline */
				अगर (!(rdev->irq.stat_regs.cik.disp_पूर्णांक_cont3 & LB_D4_VLINE_INTERRUPT))
					DRM_DEBUG("IH: IH event w/o asserted irq bit?\n");

				rdev->irq.stat_regs.cik.disp_पूर्णांक_cont3 &= ~LB_D4_VLINE_INTERRUPT;
				DRM_DEBUG("IH: D4 vline\n");

				अवरोध;
			शेष:
				DRM_DEBUG("Unhandled interrupt: %d %d\n", src_id, src_data);
				अवरोध;
			पूर्ण
			अवरोध;
		हाल 5: /* D5 vblank/vline */
			चयन (src_data) अणु
			हाल 0: /* D5 vblank */
				अगर (!(rdev->irq.stat_regs.cik.disp_पूर्णांक_cont4 & LB_D5_VBLANK_INTERRUPT))
					DRM_DEBUG("IH: IH event w/o asserted irq bit?\n");

				अगर (rdev->irq.crtc_vblank_पूर्णांक[4]) अणु
					drm_handle_vblank(rdev->ddev, 4);
					rdev->pm.vblank_sync = true;
					wake_up(&rdev->irq.vblank_queue);
				पूर्ण
				अगर (atomic_पढ़ो(&rdev->irq.pflip[4]))
					radeon_crtc_handle_vblank(rdev, 4);
				rdev->irq.stat_regs.cik.disp_पूर्णांक_cont4 &= ~LB_D5_VBLANK_INTERRUPT;
				DRM_DEBUG("IH: D5 vblank\n");

				अवरोध;
			हाल 1: /* D5 vline */
				अगर (!(rdev->irq.stat_regs.cik.disp_पूर्णांक_cont4 & LB_D5_VLINE_INTERRUPT))
					DRM_DEBUG("IH: IH event w/o asserted irq bit?\n");

				rdev->irq.stat_regs.cik.disp_पूर्णांक_cont4 &= ~LB_D5_VLINE_INTERRUPT;
				DRM_DEBUG("IH: D5 vline\n");

				अवरोध;
			शेष:
				DRM_DEBUG("Unhandled interrupt: %d %d\n", src_id, src_data);
				अवरोध;
			पूर्ण
			अवरोध;
		हाल 6: /* D6 vblank/vline */
			चयन (src_data) अणु
			हाल 0: /* D6 vblank */
				अगर (!(rdev->irq.stat_regs.cik.disp_पूर्णांक_cont5 & LB_D6_VBLANK_INTERRUPT))
					DRM_DEBUG("IH: IH event w/o asserted irq bit?\n");

				अगर (rdev->irq.crtc_vblank_पूर्णांक[5]) अणु
					drm_handle_vblank(rdev->ddev, 5);
					rdev->pm.vblank_sync = true;
					wake_up(&rdev->irq.vblank_queue);
				पूर्ण
				अगर (atomic_पढ़ो(&rdev->irq.pflip[5]))
					radeon_crtc_handle_vblank(rdev, 5);
				rdev->irq.stat_regs.cik.disp_पूर्णांक_cont5 &= ~LB_D6_VBLANK_INTERRUPT;
				DRM_DEBUG("IH: D6 vblank\n");

				अवरोध;
			हाल 1: /* D6 vline */
				अगर (!(rdev->irq.stat_regs.cik.disp_पूर्णांक_cont5 & LB_D6_VLINE_INTERRUPT))
					DRM_DEBUG("IH: IH event w/o asserted irq bit?\n");

				rdev->irq.stat_regs.cik.disp_पूर्णांक_cont5 &= ~LB_D6_VLINE_INTERRUPT;
				DRM_DEBUG("IH: D6 vline\n");

				अवरोध;
			शेष:
				DRM_DEBUG("Unhandled interrupt: %d %d\n", src_id, src_data);
				अवरोध;
			पूर्ण
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
			चयन (src_data) अणु
			हाल 0:
				अगर (!(rdev->irq.stat_regs.cik.disp_पूर्णांक & DC_HPD1_INTERRUPT))
					DRM_DEBUG("IH: IH event w/o asserted irq bit?\n");

				rdev->irq.stat_regs.cik.disp_पूर्णांक &= ~DC_HPD1_INTERRUPT;
				queue_hotplug = true;
				DRM_DEBUG("IH: HPD1\n");

				अवरोध;
			हाल 1:
				अगर (!(rdev->irq.stat_regs.cik.disp_पूर्णांक_cont & DC_HPD2_INTERRUPT))
					DRM_DEBUG("IH: IH event w/o asserted irq bit?\n");

				rdev->irq.stat_regs.cik.disp_पूर्णांक_cont &= ~DC_HPD2_INTERRUPT;
				queue_hotplug = true;
				DRM_DEBUG("IH: HPD2\n");

				अवरोध;
			हाल 2:
				अगर (!(rdev->irq.stat_regs.cik.disp_पूर्णांक_cont2 & DC_HPD3_INTERRUPT))
					DRM_DEBUG("IH: IH event w/o asserted irq bit?\n");

				rdev->irq.stat_regs.cik.disp_पूर्णांक_cont2 &= ~DC_HPD3_INTERRUPT;
				queue_hotplug = true;
				DRM_DEBUG("IH: HPD3\n");

				अवरोध;
			हाल 3:
				अगर (!(rdev->irq.stat_regs.cik.disp_पूर्णांक_cont3 & DC_HPD4_INTERRUPT))
					DRM_DEBUG("IH: IH event w/o asserted irq bit?\n");

				rdev->irq.stat_regs.cik.disp_पूर्णांक_cont3 &= ~DC_HPD4_INTERRUPT;
				queue_hotplug = true;
				DRM_DEBUG("IH: HPD4\n");

				अवरोध;
			हाल 4:
				अगर (!(rdev->irq.stat_regs.cik.disp_पूर्णांक_cont4 & DC_HPD5_INTERRUPT))
					DRM_DEBUG("IH: IH event w/o asserted irq bit?\n");

				rdev->irq.stat_regs.cik.disp_पूर्णांक_cont4 &= ~DC_HPD5_INTERRUPT;
				queue_hotplug = true;
				DRM_DEBUG("IH: HPD5\n");

				अवरोध;
			हाल 5:
				अगर (!(rdev->irq.stat_regs.cik.disp_पूर्णांक_cont5 & DC_HPD6_INTERRUPT))
					DRM_DEBUG("IH: IH event w/o asserted irq bit?\n");

				rdev->irq.stat_regs.cik.disp_पूर्णांक_cont5 &= ~DC_HPD6_INTERRUPT;
				queue_hotplug = true;
				DRM_DEBUG("IH: HPD6\n");

				अवरोध;
			हाल 6:
				अगर (!(rdev->irq.stat_regs.cik.disp_पूर्णांक & DC_HPD1_RX_INTERRUPT))
					DRM_DEBUG("IH: IH event w/o asserted irq bit?\n");

				rdev->irq.stat_regs.cik.disp_पूर्णांक &= ~DC_HPD1_RX_INTERRUPT;
				queue_dp = true;
				DRM_DEBUG("IH: HPD_RX 1\n");

				अवरोध;
			हाल 7:
				अगर (!(rdev->irq.stat_regs.cik.disp_पूर्णांक_cont & DC_HPD2_RX_INTERRUPT))
					DRM_DEBUG("IH: IH event w/o asserted irq bit?\n");

				rdev->irq.stat_regs.cik.disp_पूर्णांक_cont &= ~DC_HPD2_RX_INTERRUPT;
				queue_dp = true;
				DRM_DEBUG("IH: HPD_RX 2\n");

				अवरोध;
			हाल 8:
				अगर (!(rdev->irq.stat_regs.cik.disp_पूर्णांक_cont2 & DC_HPD3_RX_INTERRUPT))
					DRM_DEBUG("IH: IH event w/o asserted irq bit?\n");

				rdev->irq.stat_regs.cik.disp_पूर्णांक_cont2 &= ~DC_HPD3_RX_INTERRUPT;
				queue_dp = true;
				DRM_DEBUG("IH: HPD_RX 3\n");

				अवरोध;
			हाल 9:
				अगर (!(rdev->irq.stat_regs.cik.disp_पूर्णांक_cont3 & DC_HPD4_RX_INTERRUPT))
					DRM_DEBUG("IH: IH event w/o asserted irq bit?\n");

				rdev->irq.stat_regs.cik.disp_पूर्णांक_cont3 &= ~DC_HPD4_RX_INTERRUPT;
				queue_dp = true;
				DRM_DEBUG("IH: HPD_RX 4\n");

				अवरोध;
			हाल 10:
				अगर (!(rdev->irq.stat_regs.cik.disp_पूर्णांक_cont4 & DC_HPD5_RX_INTERRUPT))
					DRM_DEBUG("IH: IH event w/o asserted irq bit?\n");

				rdev->irq.stat_regs.cik.disp_पूर्णांक_cont4 &= ~DC_HPD5_RX_INTERRUPT;
				queue_dp = true;
				DRM_DEBUG("IH: HPD_RX 5\n");

				अवरोध;
			हाल 11:
				अगर (!(rdev->irq.stat_regs.cik.disp_पूर्णांक_cont5 & DC_HPD6_RX_INTERRUPT))
					DRM_DEBUG("IH: IH event w/o asserted irq bit?\n");

				rdev->irq.stat_regs.cik.disp_पूर्णांक_cont5 &= ~DC_HPD6_RX_INTERRUPT;
				queue_dp = true;
				DRM_DEBUG("IH: HPD_RX 6\n");

				अवरोध;
			शेष:
				DRM_DEBUG("Unhandled interrupt: %d %d\n", src_id, src_data);
				अवरोध;
			पूर्ण
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
			mc_client = RREG32(VM_CONTEXT1_PROTECTION_FAULT_MCCLIENT);
			/* reset addr and status */
			WREG32_P(VM_CONTEXT1_CNTL2, 1, ~1);
			अगर (addr == 0x0 && status == 0x0)
				अवरोध;
			dev_err(rdev->dev, "GPU fault detected: %d 0x%08x\n", src_id, src_data);
			dev_err(rdev->dev, "  VM_CONTEXT1_PROTECTION_FAULT_ADDR   0x%08X\n",
				addr);
			dev_err(rdev->dev, "  VM_CONTEXT1_PROTECTION_FAULT_STATUS 0x%08X\n",
				status);
			cik_vm_decode_fault(rdev, status, addr, mc_client);
			अवरोध;
		हाल 167: /* VCE */
			DRM_DEBUG("IH: VCE int: 0x%08x\n", src_data);
			चयन (src_data) अणु
			हाल 0:
				radeon_fence_process(rdev, TN_RING_TYPE_VCE1_INDEX);
				अवरोध;
			हाल 1:
				radeon_fence_process(rdev, TN_RING_TYPE_VCE2_INDEX);
				अवरोध;
			शेष:
				DRM_ERROR("Unhandled interrupt: %d %d\n", src_id, src_data);
				अवरोध;
			पूर्ण
			अवरोध;
		हाल 176: /* GFX RB CP_INT */
		हाल 177: /* GFX IB CP_INT */
			radeon_fence_process(rdev, RADEON_RING_TYPE_GFX_INDEX);
			अवरोध;
		हाल 181: /* CP EOP event */
			DRM_DEBUG("IH: CP EOP\n");
			/* XXX check the bitfield order! */
			me_id = (ring_id & 0x60) >> 5;
			pipe_id = (ring_id & 0x18) >> 3;
			queue_id = (ring_id & 0x7) >> 0;
			चयन (me_id) अणु
			हाल 0:
				radeon_fence_process(rdev, RADEON_RING_TYPE_GFX_INDEX);
				अवरोध;
			हाल 1:
			हाल 2:
				अगर ((cp1_ring->me == me_id) & (cp1_ring->pipe == pipe_id))
					radeon_fence_process(rdev, CAYMAN_RING_TYPE_CP1_INDEX);
				अगर ((cp2_ring->me == me_id) & (cp2_ring->pipe == pipe_id))
					radeon_fence_process(rdev, CAYMAN_RING_TYPE_CP2_INDEX);
				अवरोध;
			पूर्ण
			अवरोध;
		हाल 184: /* CP Privileged reg access */
			DRM_ERROR("Illegal register access in command stream\n");
			/* XXX check the bitfield order! */
			me_id = (ring_id & 0x60) >> 5;
			चयन (me_id) अणु
			हाल 0:
				/* This results in a full GPU reset, but all we need to करो is soft
				 * reset the CP क्रम gfx
				 */
				queue_reset = true;
				अवरोध;
			हाल 1:
				/* XXX compute */
				queue_reset = true;
				अवरोध;
			हाल 2:
				/* XXX compute */
				queue_reset = true;
				अवरोध;
			पूर्ण
			अवरोध;
		हाल 185: /* CP Privileged inst */
			DRM_ERROR("Illegal instruction in command stream\n");
			/* XXX check the bitfield order! */
			me_id = (ring_id & 0x60) >> 5;
			चयन (me_id) अणु
			हाल 0:
				/* This results in a full GPU reset, but all we need to करो is soft
				 * reset the CP क्रम gfx
				 */
				queue_reset = true;
				अवरोध;
			हाल 1:
				/* XXX compute */
				queue_reset = true;
				अवरोध;
			हाल 2:
				/* XXX compute */
				queue_reset = true;
				अवरोध;
			पूर्ण
			अवरोध;
		हाल 224: /* SDMA trap event */
			/* XXX check the bitfield order! */
			me_id = (ring_id & 0x3) >> 0;
			queue_id = (ring_id & 0xc) >> 2;
			DRM_DEBUG("IH: SDMA trap\n");
			चयन (me_id) अणु
			हाल 0:
				चयन (queue_id) अणु
				हाल 0:
					radeon_fence_process(rdev, R600_RING_TYPE_DMA_INDEX);
					अवरोध;
				हाल 1:
					/* XXX compute */
					अवरोध;
				हाल 2:
					/* XXX compute */
					अवरोध;
				पूर्ण
				अवरोध;
			हाल 1:
				चयन (queue_id) अणु
				हाल 0:
					radeon_fence_process(rdev, CAYMAN_RING_TYPE_DMA1_INDEX);
					अवरोध;
				हाल 1:
					/* XXX compute */
					अवरोध;
				हाल 2:
					/* XXX compute */
					अवरोध;
				पूर्ण
				अवरोध;
			पूर्ण
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
		हाल 241: /* SDMA Privileged inst */
		हाल 247: /* SDMA Privileged inst */
			DRM_ERROR("Illegal instruction in SDMA command stream\n");
			/* XXX check the bitfield order! */
			me_id = (ring_id & 0x3) >> 0;
			queue_id = (ring_id & 0xc) >> 2;
			चयन (me_id) अणु
			हाल 0:
				चयन (queue_id) अणु
				हाल 0:
					queue_reset = true;
					अवरोध;
				हाल 1:
					/* XXX compute */
					queue_reset = true;
					अवरोध;
				हाल 2:
					/* XXX compute */
					queue_reset = true;
					अवरोध;
				पूर्ण
				अवरोध;
			हाल 1:
				चयन (queue_id) अणु
				हाल 0:
					queue_reset = true;
					अवरोध;
				हाल 1:
					/* XXX compute */
					queue_reset = true;
					अवरोध;
				हाल 2:
					/* XXX compute */
					queue_reset = true;
					अवरोध;
				पूर्ण
				अवरोध;
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
	अगर (queue_reset) अणु
		rdev->needs_reset = true;
		wake_up_all(&rdev->fence_queue);
	पूर्ण
	अगर (queue_thermal)
		schedule_work(&rdev->pm.dpm.thermal.work);
	rdev->ih.rptr = rptr;
	atomic_set(&rdev->ih.lock, 0);

	/* make sure wptr hasn't changed जबतक processing */
	wptr = cik_get_ih_wptr(rdev);
	अगर (wptr != rptr)
		जाओ restart_ih;

	वापस IRQ_HANDLED;
पूर्ण

/*
 * startup/shutकरोwn callbacks
 */
अटल व्योम cik_uvd_init(काष्ठा radeon_device *rdev)
अणु
	पूर्णांक r;

	अगर (!rdev->has_uvd)
		वापस;

	r = radeon_uvd_init(rdev);
	अगर (r) अणु
		dev_err(rdev->dev, "failed UVD (%d) init.\n", r);
		/*
		 * At this poपूर्णांक rdev->uvd.vcpu_bo is शून्य which trickles करोwn
		 * to early fails cik_uvd_start() and thus nothing happens
		 * there. So it is poपूर्णांकless to try to go through that code
		 * hence why we disable uvd here.
		 */
		rdev->has_uvd = false;
		वापस;
	पूर्ण
	rdev->ring[R600_RING_TYPE_UVD_INDEX].ring_obj = शून्य;
	r600_ring_init(rdev, &rdev->ring[R600_RING_TYPE_UVD_INDEX], 4096);
पूर्ण

अटल व्योम cik_uvd_start(काष्ठा radeon_device *rdev)
अणु
	पूर्णांक r;

	अगर (!rdev->has_uvd)
		वापस;

	r = radeon_uvd_resume(rdev);
	अगर (r) अणु
		dev_err(rdev->dev, "failed UVD resume (%d).\n", r);
		जाओ error;
	पूर्ण
	r = uvd_v4_2_resume(rdev);
	अगर (r) अणु
		dev_err(rdev->dev, "failed UVD 4.2 resume (%d).\n", r);
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

अटल व्योम cik_uvd_resume(काष्ठा radeon_device *rdev)
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

अटल व्योम cik_vce_init(काष्ठा radeon_device *rdev)
अणु
	पूर्णांक r;

	अगर (!rdev->has_vce)
		वापस;

	r = radeon_vce_init(rdev);
	अगर (r) अणु
		dev_err(rdev->dev, "failed VCE (%d) init.\n", r);
		/*
		 * At this poपूर्णांक rdev->vce.vcpu_bo is शून्य which trickles करोwn
		 * to early fails cik_vce_start() and thus nothing happens
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

अटल व्योम cik_vce_start(काष्ठा radeon_device *rdev)
अणु
	पूर्णांक r;

	अगर (!rdev->has_vce)
		वापस;

	r = radeon_vce_resume(rdev);
	अगर (r) अणु
		dev_err(rdev->dev, "failed VCE resume (%d).\n", r);
		जाओ error;
	पूर्ण
	r = vce_v2_0_resume(rdev);
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

अटल व्योम cik_vce_resume(काष्ठा radeon_device *rdev)
अणु
	काष्ठा radeon_ring *ring;
	पूर्णांक r;

	अगर (!rdev->has_vce || !rdev->ring[TN_RING_TYPE_VCE1_INDEX].ring_size)
		वापस;

	ring = &rdev->ring[TN_RING_TYPE_VCE1_INDEX];
	r = radeon_ring_init(rdev, ring, ring->ring_size, 0, VCE_CMD_NO_OP);
	अगर (r) अणु
		dev_err(rdev->dev, "failed initializing VCE1 ring (%d).\n", r);
		वापस;
	पूर्ण
	ring = &rdev->ring[TN_RING_TYPE_VCE2_INDEX];
	r = radeon_ring_init(rdev, ring, ring->ring_size, 0, VCE_CMD_NO_OP);
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

/**
 * cik_startup - program the asic to a functional state
 *
 * @rdev: radeon_device poपूर्णांकer
 *
 * Programs the asic to a functional state (CIK).
 * Called by cik_init() and cik_resume().
 * Returns 0 क्रम success, error क्रम failure.
 */
अटल पूर्णांक cik_startup(काष्ठा radeon_device *rdev)
अणु
	काष्ठा radeon_ring *ring;
	u32 nop;
	पूर्णांक r;

	/* enable pcie gen2/3 link */
	cik_pcie_gen3_enable(rdev);
	/* enable aspm */
	cik_program_aspm(rdev);

	/* scratch needs to be initialized beक्रमe MC */
	r = r600_vram_scratch_init(rdev);
	अगर (r)
		वापस r;

	cik_mc_program(rdev);

	अगर (!(rdev->flags & RADEON_IS_IGP) && !rdev->pm.dpm_enabled) अणु
		r = ci_mc_load_microcode(rdev);
		अगर (r) अणु
			DRM_ERROR("Failed to load MC firmware!\n");
			वापस r;
		पूर्ण
	पूर्ण

	r = cik_pcie_gart_enable(rdev);
	अगर (r)
		वापस r;
	cik_gpu_init(rdev);

	/* allocate rlc buffers */
	अगर (rdev->flags & RADEON_IS_IGP) अणु
		अगर (rdev->family == CHIP_KAVERI) अणु
			rdev->rlc.reg_list = spectre_rlc_save_restore_रेजिस्टर_list;
			rdev->rlc.reg_list_size =
				(u32)ARRAY_SIZE(spectre_rlc_save_restore_रेजिस्टर_list);
		पूर्ण अन्यथा अणु
			rdev->rlc.reg_list = kalindi_rlc_save_restore_रेजिस्टर_list;
			rdev->rlc.reg_list_size =
				(u32)ARRAY_SIZE(kalindi_rlc_save_restore_रेजिस्टर_list);
		पूर्ण
	पूर्ण
	rdev->rlc.cs_data = ci_cs_data;
	rdev->rlc.cp_table_size = ALIGN(CP_ME_TABLE_SIZE * 5 * 4, 2048); /* CP JT */
	rdev->rlc.cp_table_size += 64 * 1024; /* GDS */
	r = sumo_rlc_init(rdev);
	अगर (r) अणु
		DRM_ERROR("Failed to init rlc BOs!\n");
		वापस r;
	पूर्ण

	/* allocate wb buffer */
	r = radeon_wb_init(rdev);
	अगर (r)
		वापस r;

	/* allocate mec buffers */
	r = cik_mec_init(rdev);
	अगर (r) अणु
		DRM_ERROR("Failed to init MEC BOs!\n");
		वापस r;
	पूर्ण

	r = radeon_fence_driver_start_ring(rdev, RADEON_RING_TYPE_GFX_INDEX);
	अगर (r) अणु
		dev_err(rdev->dev, "failed initializing CP fences (%d).\n", r);
		वापस r;
	पूर्ण

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

	cik_uvd_start(rdev);
	cik_vce_start(rdev);

	/* Enable IRQ */
	अगर (!rdev->irq.installed) अणु
		r = radeon_irq_kms_init(rdev);
		अगर (r)
			वापस r;
	पूर्ण

	r = cik_irq_init(rdev);
	अगर (r) अणु
		DRM_ERROR("radeon: IH init failed (%d).\n", r);
		radeon_irq_kms_fini(rdev);
		वापस r;
	पूर्ण
	cik_irq_set(rdev);

	अगर (rdev->family == CHIP_HAWAII) अणु
		अगर (rdev->new_fw)
			nop = PACKET3(PACKET3_NOP, 0x3FFF);
		अन्यथा
			nop = RADEON_CP_PACKET2;
	पूर्ण अन्यथा अणु
		nop = PACKET3(PACKET3_NOP, 0x3FFF);
	पूर्ण

	ring = &rdev->ring[RADEON_RING_TYPE_GFX_INDEX];
	r = radeon_ring_init(rdev, ring, ring->ring_size, RADEON_WB_CP_RPTR_OFFSET,
			     nop);
	अगर (r)
		वापस r;

	/* set up the compute queues */
	/* type-2 packets are deprecated on MEC, use type-3 instead */
	ring = &rdev->ring[CAYMAN_RING_TYPE_CP1_INDEX];
	r = radeon_ring_init(rdev, ring, ring->ring_size, RADEON_WB_CP1_RPTR_OFFSET,
			     nop);
	अगर (r)
		वापस r;
	ring->me = 1; /* first MEC */
	ring->pipe = 0; /* first pipe */
	ring->queue = 0; /* first queue */
	ring->wptr_offs = CIK_WB_CP1_WPTR_OFFSET;

	/* type-2 packets are deprecated on MEC, use type-3 instead */
	ring = &rdev->ring[CAYMAN_RING_TYPE_CP2_INDEX];
	r = radeon_ring_init(rdev, ring, ring->ring_size, RADEON_WB_CP2_RPTR_OFFSET,
			     nop);
	अगर (r)
		वापस r;
	/* dGPU only have 1 MEC */
	ring->me = 1; /* first MEC */
	ring->pipe = 0; /* first pipe */
	ring->queue = 1; /* second queue */
	ring->wptr_offs = CIK_WB_CP2_WPTR_OFFSET;

	ring = &rdev->ring[R600_RING_TYPE_DMA_INDEX];
	r = radeon_ring_init(rdev, ring, ring->ring_size, R600_WB_DMA_RPTR_OFFSET,
			     SDMA_PACKET(SDMA_OPCODE_NOP, 0, 0));
	अगर (r)
		वापस r;

	ring = &rdev->ring[CAYMAN_RING_TYPE_DMA1_INDEX];
	r = radeon_ring_init(rdev, ring, ring->ring_size, CAYMAN_WB_DMA1_RPTR_OFFSET,
			     SDMA_PACKET(SDMA_OPCODE_NOP, 0, 0));
	अगर (r)
		वापस r;

	r = cik_cp_resume(rdev);
	अगर (r)
		वापस r;

	r = cik_sdma_resume(rdev);
	अगर (r)
		वापस r;

	cik_uvd_resume(rdev);
	cik_vce_resume(rdev);

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

/**
 * cik_resume - resume the asic to a functional state
 *
 * @rdev: radeon_device poपूर्णांकer
 *
 * Programs the asic to a functional state (CIK).
 * Called at resume.
 * Returns 0 क्रम success, error क्रम failure.
 */
पूर्णांक cik_resume(काष्ठा radeon_device *rdev)
अणु
	पूर्णांक r;

	/* post card */
	atom_asic_init(rdev->mode_info.atom_context);

	/* init golden रेजिस्टरs */
	cik_init_golden_रेजिस्टरs(rdev);

	अगर (rdev->pm.pm_method == PM_METHOD_DPM)
		radeon_pm_resume(rdev);

	rdev->accel_working = true;
	r = cik_startup(rdev);
	अगर (r) अणु
		DRM_ERROR("cik startup failed on resume\n");
		rdev->accel_working = false;
		वापस r;
	पूर्ण

	वापस r;

पूर्ण

/**
 * cik_suspend - suspend the asic
 *
 * @rdev: radeon_device poपूर्णांकer
 *
 * Bring the chip पूर्णांकo a state suitable क्रम suspend (CIK).
 * Called at suspend.
 * Returns 0 क्रम success.
 */
पूर्णांक cik_suspend(काष्ठा radeon_device *rdev)
अणु
	radeon_pm_suspend(rdev);
	radeon_audio_fini(rdev);
	radeon_vm_manager_fini(rdev);
	cik_cp_enable(rdev, false);
	cik_sdma_enable(rdev, false);
	अगर (rdev->has_uvd) अणु
		uvd_v1_0_fini(rdev);
		radeon_uvd_suspend(rdev);
	पूर्ण
	अगर (rdev->has_vce)
		radeon_vce_suspend(rdev);
	cik_fini_pg(rdev);
	cik_fini_cg(rdev);
	cik_irq_suspend(rdev);
	radeon_wb_disable(rdev);
	cik_pcie_gart_disable(rdev);
	वापस 0;
पूर्ण

/* Plan is to move initialization in that function and use
 * helper function so that radeon_device_init pretty much
 * करो nothing more than calling asic specअगरic function. This
 * should also allow to हटाओ a bunch of callback function
 * like vram_info.
 */
/**
 * cik_init - asic specअगरic driver and hw init
 *
 * @rdev: radeon_device poपूर्णांकer
 *
 * Setup asic specअगरic driver variables and program the hw
 * to a functional state (CIK).
 * Called at driver startup.
 * Returns 0 क्रम success, errors क्रम failure.
 */
पूर्णांक cik_init(काष्ठा radeon_device *rdev)
अणु
	काष्ठा radeon_ring *ring;
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
	cik_init_golden_रेजिस्टरs(rdev);
	/* Initialize scratch रेजिस्टरs */
	cik_scratch_init(rdev);
	/* Initialize surface रेजिस्टरs */
	radeon_surface_init(rdev);
	/* Initialize घड़ीs */
	radeon_get_घड़ी_info(rdev->ddev);

	/* Fence driver */
	r = radeon_fence_driver_init(rdev);
	अगर (r)
		वापस r;

	/* initialize memory controller */
	r = cik_mc_init(rdev);
	अगर (r)
		वापस r;
	/* Memory manager */
	r = radeon_bo_init(rdev);
	अगर (r)
		वापस r;

	अगर (rdev->flags & RADEON_IS_IGP) अणु
		अगर (!rdev->me_fw || !rdev->pfp_fw || !rdev->ce_fw ||
		    !rdev->mec_fw || !rdev->sdma_fw || !rdev->rlc_fw) अणु
			r = cik_init_microcode(rdev);
			अगर (r) अणु
				DRM_ERROR("Failed to load firmware!\n");
				वापस r;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (!rdev->me_fw || !rdev->pfp_fw || !rdev->ce_fw ||
		    !rdev->mec_fw || !rdev->sdma_fw || !rdev->rlc_fw ||
		    !rdev->mc_fw) अणु
			r = cik_init_microcode(rdev);
			अगर (r) अणु
				DRM_ERROR("Failed to load firmware!\n");
				वापस r;
			पूर्ण
		पूर्ण
	पूर्ण

	/* Initialize घातer management */
	radeon_pm_init(rdev);

	ring = &rdev->ring[RADEON_RING_TYPE_GFX_INDEX];
	ring->ring_obj = शून्य;
	r600_ring_init(rdev, ring, 1024 * 1024);

	ring = &rdev->ring[CAYMAN_RING_TYPE_CP1_INDEX];
	ring->ring_obj = शून्य;
	r600_ring_init(rdev, ring, 1024 * 1024);
	r = radeon_करोorbell_get(rdev, &ring->करोorbell_index);
	अगर (r)
		वापस r;

	ring = &rdev->ring[CAYMAN_RING_TYPE_CP2_INDEX];
	ring->ring_obj = शून्य;
	r600_ring_init(rdev, ring, 1024 * 1024);
	r = radeon_करोorbell_get(rdev, &ring->करोorbell_index);
	अगर (r)
		वापस r;

	ring = &rdev->ring[R600_RING_TYPE_DMA_INDEX];
	ring->ring_obj = शून्य;
	r600_ring_init(rdev, ring, 256 * 1024);

	ring = &rdev->ring[CAYMAN_RING_TYPE_DMA1_INDEX];
	ring->ring_obj = शून्य;
	r600_ring_init(rdev, ring, 256 * 1024);

	cik_uvd_init(rdev);
	cik_vce_init(rdev);

	rdev->ih.ring_obj = शून्य;
	r600_ih_ring_init(rdev, 64 * 1024);

	r = r600_pcie_gart_init(rdev);
	अगर (r)
		वापस r;

	rdev->accel_working = true;
	r = cik_startup(rdev);
	अगर (r) अणु
		dev_err(rdev->dev, "disabling GPU acceleration\n");
		cik_cp_fini(rdev);
		cik_sdma_fini(rdev);
		cik_irq_fini(rdev);
		sumo_rlc_fini(rdev);
		cik_mec_fini(rdev);
		radeon_wb_fini(rdev);
		radeon_ib_pool_fini(rdev);
		radeon_vm_manager_fini(rdev);
		radeon_irq_kms_fini(rdev);
		cik_pcie_gart_fini(rdev);
		rdev->accel_working = false;
	पूर्ण

	/* Don't start up अगर the MC ucode is missing.
	 * The शेष घड़ीs and voltages beक्रमe the MC ucode
	 * is loaded are not suffient क्रम advanced operations.
	 */
	अगर (!rdev->mc_fw && !(rdev->flags & RADEON_IS_IGP)) अणु
		DRM_ERROR("radeon: MC ucode required for NI+.\n");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * cik_fini - asic specअगरic driver and hw fini
 *
 * @rdev: radeon_device poपूर्णांकer
 *
 * Tear करोwn the asic specअगरic driver variables and program the hw
 * to an idle state (CIK).
 * Called at driver unload.
 */
व्योम cik_fini(काष्ठा radeon_device *rdev)
अणु
	radeon_pm_fini(rdev);
	cik_cp_fini(rdev);
	cik_sdma_fini(rdev);
	cik_fini_pg(rdev);
	cik_fini_cg(rdev);
	cik_irq_fini(rdev);
	sumo_rlc_fini(rdev);
	cik_mec_fini(rdev);
	radeon_wb_fini(rdev);
	radeon_vm_manager_fini(rdev);
	radeon_ib_pool_fini(rdev);
	radeon_irq_kms_fini(rdev);
	uvd_v1_0_fini(rdev);
	radeon_uvd_fini(rdev);
	radeon_vce_fini(rdev);
	cik_pcie_gart_fini(rdev);
	r600_vram_scratch_fini(rdev);
	radeon_gem_fini(rdev);
	radeon_fence_driver_fini(rdev);
	radeon_bo_fini(rdev);
	radeon_atombios_fini(rdev);
	kमुक्त(rdev->bios);
	rdev->bios = शून्य;
पूर्ण

व्योम dce8_program_fmt(काष्ठा drm_encoder *encoder)
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
				FMT_SPATIAL_DITHER_EN | FMT_SPATIAL_DITHER_DEPTH(0));
		अन्यथा
			पंचांगp |= (FMT_TRUNCATE_EN | FMT_TRUNCATE_DEPTH(0));
		अवरोध;
	हाल 8:
		अगर (dither == RADEON_FMT_DITHER_ENABLE)
			/* XXX sort out optimal dither settings */
			पंचांगp |= (FMT_FRAME_RANDOM_ENABLE | FMT_HIGHPASS_RANDOM_ENABLE |
				FMT_RGB_RANDOM_ENABLE |
				FMT_SPATIAL_DITHER_EN | FMT_SPATIAL_DITHER_DEPTH(1));
		अन्यथा
			पंचांगp |= (FMT_TRUNCATE_EN | FMT_TRUNCATE_DEPTH(1));
		अवरोध;
	हाल 10:
		अगर (dither == RADEON_FMT_DITHER_ENABLE)
			/* XXX sort out optimal dither settings */
			पंचांगp |= (FMT_FRAME_RANDOM_ENABLE | FMT_HIGHPASS_RANDOM_ENABLE |
				FMT_RGB_RANDOM_ENABLE |
				FMT_SPATIAL_DITHER_EN | FMT_SPATIAL_DITHER_DEPTH(2));
		अन्यथा
			पंचांगp |= (FMT_TRUNCATE_EN | FMT_TRUNCATE_DEPTH(2));
		अवरोध;
	शेष:
		/* not needed */
		अवरोध;
	पूर्ण

	WREG32(FMT_BIT_DEPTH_CONTROL + radeon_crtc->crtc_offset, पंचांगp);
पूर्ण

/* display watermark setup */
/**
 * dce8_line_buffer_adjust - Set up the line buffer
 *
 * @rdev: radeon_device poपूर्णांकer
 * @radeon_crtc: the selected display controller
 * @mode: the current display mode on the selected display
 * controller
 *
 * Setup up the line buffer allocation क्रम
 * the selected display controller (CIK).
 * Returns the line buffer size in pixels.
 */
अटल u32 dce8_line_buffer_adjust(काष्ठा radeon_device *rdev,
				   काष्ठा radeon_crtc *radeon_crtc,
				   काष्ठा drm_display_mode *mode)
अणु
	u32 पंचांगp, buffer_alloc, i;
	u32 pipe_offset = radeon_crtc->crtc_id * 0x20;
	/*
	 * Line Buffer Setup
	 * There are 6 line buffers, one क्रम each display controllers.
	 * There are 3 partitions per LB. Select the number of partitions
	 * to enable based on the display width.  For display widths larger
	 * than 4096, you need use to use 2 display controllers and combine
	 * them using the stereo blender.
	 */
	अगर (radeon_crtc->base.enabled && mode) अणु
		अगर (mode->crtc_hdisplay < 1920) अणु
			पंचांगp = 1;
			buffer_alloc = 2;
		पूर्ण अन्यथा अगर (mode->crtc_hdisplay < 2560) अणु
			पंचांगp = 2;
			buffer_alloc = 2;
		पूर्ण अन्यथा अगर (mode->crtc_hdisplay < 4096) अणु
			पंचांगp = 0;
			buffer_alloc = (rdev->flags & RADEON_IS_IGP) ? 2 : 4;
		पूर्ण अन्यथा अणु
			DRM_DEBUG_KMS("Mode too big for LB!\n");
			पंचांगp = 0;
			buffer_alloc = (rdev->flags & RADEON_IS_IGP) ? 2 : 4;
		पूर्ण
	पूर्ण अन्यथा अणु
		पंचांगp = 1;
		buffer_alloc = 0;
	पूर्ण

	WREG32(LB_MEMORY_CTRL + radeon_crtc->crtc_offset,
	       LB_MEMORY_CONFIG(पंचांगp) | LB_MEMORY_SIZE(0x6B0));

	WREG32(PIPE0_DMIF_BUFFER_CONTROL + pipe_offset,
	       DMIF_BUFFERS_ALLOCATED(buffer_alloc));
	क्रम (i = 0; i < rdev->usec_समयout; i++) अणु
		अगर (RREG32(PIPE0_DMIF_BUFFER_CONTROL + pipe_offset) &
		    DMIF_BUFFERS_ALLOCATED_COMPLETED)
			अवरोध;
		udelay(1);
	पूर्ण

	अगर (radeon_crtc->base.enabled && mode) अणु
		चयन (पंचांगp) अणु
		हाल 0:
		शेष:
			वापस 4096 * 2;
		हाल 1:
			वापस 1920 * 2;
		हाल 2:
			वापस 2560 * 2;
		पूर्ण
	पूर्ण

	/* controller not enabled, so no lb used */
	वापस 0;
पूर्ण

/**
 * cik_get_number_of_dram_channels - get the number of dram channels
 *
 * @rdev: radeon_device poपूर्णांकer
 *
 * Look up the number of video ram channels (CIK).
 * Used क्रम display watermark bandwidth calculations
 * Returns the number of dram channels
 */
अटल u32 cik_get_number_of_dram_channels(काष्ठा radeon_device *rdev)
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
	हाल 4:
		वापस 3;
	हाल 5:
		वापस 6;
	हाल 6:
		वापस 10;
	हाल 7:
		वापस 12;
	हाल 8:
		वापस 16;
	पूर्ण
पूर्ण

काष्ठा dce8_wm_params अणु
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

/**
 * dce8_dram_bandwidth - get the dram bandwidth
 *
 * @wm: watermark calculation data
 *
 * Calculate the raw dram bandwidth (CIK).
 * Used क्रम display watermark bandwidth calculations
 * Returns the dram bandwidth in MBytes/s
 */
अटल u32 dce8_dram_bandwidth(काष्ठा dce8_wm_params *wm)
अणु
	/* Calculate raw DRAM Bandwidth */
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

/**
 * dce8_dram_bandwidth_क्रम_display - get the dram bandwidth क्रम display
 *
 * @wm: watermark calculation data
 *
 * Calculate the dram bandwidth used क्रम display (CIK).
 * Used क्रम display watermark bandwidth calculations
 * Returns the dram bandwidth क्रम display in MBytes/s
 */
अटल u32 dce8_dram_bandwidth_क्रम_display(काष्ठा dce8_wm_params *wm)
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

/**
 * dce8_data_वापस_bandwidth - get the data वापस bandwidth
 *
 * @wm: watermark calculation data
 *
 * Calculate the data वापस bandwidth used क्रम display (CIK).
 * Used क्रम display watermark bandwidth calculations
 * Returns the data वापस bandwidth in MBytes/s
 */
अटल u32 dce8_data_वापस_bandwidth(काष्ठा dce8_wm_params *wm)
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

/**
 * dce8_dmअगर_request_bandwidth - get the dmअगर bandwidth
 *
 * @wm: watermark calculation data
 *
 * Calculate the dmअगर bandwidth used क्रम display (CIK).
 * Used क्रम display watermark bandwidth calculations
 * Returns the dmअगर bandwidth in MBytes/s
 */
अटल u32 dce8_dmअगर_request_bandwidth(काष्ठा dce8_wm_params *wm)
अणु
	/* Calculate the DMIF Request Bandwidth */
	fixed20_12 disp_clk_request_efficiency; /* 0.8 */
	fixed20_12 disp_clk, bandwidth;
	fixed20_12 a, b;

	a.full = dfixed_स्थिर(1000);
	disp_clk.full = dfixed_स्थिर(wm->disp_clk);
	disp_clk.full = dfixed_भाग(disp_clk, a);
	a.full = dfixed_स्थिर(32);
	b.full = dfixed_mul(a, disp_clk);

	a.full = dfixed_स्थिर(10);
	disp_clk_request_efficiency.full = dfixed_स्थिर(8);
	disp_clk_request_efficiency.full = dfixed_भाग(disp_clk_request_efficiency, a);

	bandwidth.full = dfixed_mul(b, disp_clk_request_efficiency);

	वापस dfixed_trunc(bandwidth);
पूर्ण

/**
 * dce8_available_bandwidth - get the min available bandwidth
 *
 * @wm: watermark calculation data
 *
 * Calculate the min available bandwidth used क्रम display (CIK).
 * Used क्रम display watermark bandwidth calculations
 * Returns the min available bandwidth in MBytes/s
 */
अटल u32 dce8_available_bandwidth(काष्ठा dce8_wm_params *wm)
अणु
	/* Calculate the Available bandwidth. Display can use this temporarily but not in average. */
	u32 dram_bandwidth = dce8_dram_bandwidth(wm);
	u32 data_वापस_bandwidth = dce8_data_वापस_bandwidth(wm);
	u32 dmअगर_req_bandwidth = dce8_dmअगर_request_bandwidth(wm);

	वापस min(dram_bandwidth, min(data_वापस_bandwidth, dmअगर_req_bandwidth));
पूर्ण

/**
 * dce8_average_bandwidth - get the average available bandwidth
 *
 * @wm: watermark calculation data
 *
 * Calculate the average available bandwidth used क्रम display (CIK).
 * Used क्रम display watermark bandwidth calculations
 * Returns the average available bandwidth in MBytes/s
 */
अटल u32 dce8_average_bandwidth(काष्ठा dce8_wm_params *wm)
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

/**
 * dce8_latency_watermark - get the latency watermark
 *
 * @wm: watermark calculation data
 *
 * Calculate the latency watermark (CIK).
 * Used क्रम display watermark bandwidth calculations
 * Returns the latency watermark in ns
 */
अटल u32 dce8_latency_watermark(काष्ठा dce8_wm_params *wm)
अणु
	/* First calculate the latency in ns */
	u32 mc_latency = 2000; /* 2000 ns. */
	u32 available_bandwidth = dce8_available_bandwidth(wm);
	u32 worst_chunk_वापस_समय = (512 * 8 * 1000) / available_bandwidth;
	u32 cursor_line_pair_वापस_समय = (128 * 4 * 1000) / available_bandwidth;
	u32 dc_latency = 40000000 / wm->disp_clk; /* dc pipe latency */
	u32 other_heads_data_वापस_समय = ((wm->num_heads + 1) * worst_chunk_वापस_समय) +
		(wm->num_heads * cursor_line_pair_वापस_समय);
	u32 latency = mc_latency + other_heads_data_वापस_समय + dc_latency;
	u32 max_src_lines_per_dst_line, lb_fill_bw, line_fill_समय;
	u32 पंचांगp, dmअगर_size = 12288;
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
	पंचांगp = भाग_u64((u64) dmअगर_size * (u64) wm->disp_clk, mc_latency + 512);
	पंचांगp = min(dfixed_trunc(a), पंचांगp);

	lb_fill_bw = min(पंचांगp, wm->disp_clk * wm->bytes_per_pixel / 1000);

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

/**
 * dce8_average_bandwidth_vs_dram_bandwidth_क्रम_display - check
 * average and available dram bandwidth
 *
 * @wm: watermark calculation data
 *
 * Check अगर the display average bandwidth fits in the display
 * dram bandwidth (CIK).
 * Used क्रम display watermark bandwidth calculations
 * Returns true अगर the display fits, false अगर not.
 */
अटल bool dce8_average_bandwidth_vs_dram_bandwidth_क्रम_display(काष्ठा dce8_wm_params *wm)
अणु
	अगर (dce8_average_bandwidth(wm) <=
	    (dce8_dram_bandwidth_क्रम_display(wm) / wm->num_heads))
		वापस true;
	अन्यथा
		वापस false;
पूर्ण

/**
 * dce8_average_bandwidth_vs_available_bandwidth - check
 * average and available bandwidth
 *
 * @wm: watermark calculation data
 *
 * Check अगर the display average bandwidth fits in the display
 * available bandwidth (CIK).
 * Used क्रम display watermark bandwidth calculations
 * Returns true अगर the display fits, false अगर not.
 */
अटल bool dce8_average_bandwidth_vs_available_bandwidth(काष्ठा dce8_wm_params *wm)
अणु
	अगर (dce8_average_bandwidth(wm) <=
	    (dce8_available_bandwidth(wm) / wm->num_heads))
		वापस true;
	अन्यथा
		वापस false;
पूर्ण

/**
 * dce8_check_latency_hiding - check latency hiding
 *
 * @wm: watermark calculation data
 *
 * Check latency hiding (CIK).
 * Used क्रम display watermark bandwidth calculations
 * Returns true अगर the display fits, false अगर not.
 */
अटल bool dce8_check_latency_hiding(काष्ठा dce8_wm_params *wm)
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

	अगर (dce8_latency_watermark(wm) <= latency_hiding)
		वापस true;
	अन्यथा
		वापस false;
पूर्ण

/**
 * dce8_program_watermarks - program display watermarks
 *
 * @rdev: radeon_device poपूर्णांकer
 * @radeon_crtc: the selected display controller
 * @lb_size: line buffer size
 * @num_heads: number of display controllers in use
 *
 * Calculate and program the display watermarks क्रम the
 * selected display controller (CIK).
 */
अटल व्योम dce8_program_watermarks(काष्ठा radeon_device *rdev,
				    काष्ठा radeon_crtc *radeon_crtc,
				    u32 lb_size, u32 num_heads)
अणु
	काष्ठा drm_display_mode *mode = &radeon_crtc->base.mode;
	काष्ठा dce8_wm_params wm_low, wm_high;
	u32 active_समय;
	u32 line_समय = 0;
	u32 latency_watermark_a = 0, latency_watermark_b = 0;
	u32 पंचांगp, wm_mask;

	अगर (radeon_crtc->base.enabled && num_heads && mode) अणु
		active_समय = (u32) भाग_u64((u64)mode->crtc_hdisplay * 1000000,
					    (u32)mode->घड़ी);
		line_समय = (u32) भाग_u64((u64)mode->crtc_htotal * 1000000,
					  (u32)mode->घड़ी);
		line_समय = min(line_समय, (u32)65535);

		/* watermark क्रम high घड़ीs */
		अगर ((rdev->pm.pm_method == PM_METHOD_DPM) &&
		    rdev->pm.dpm_enabled) अणु
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
		wm_high.dram_channels = cik_get_number_of_dram_channels(rdev);
		wm_high.num_heads = num_heads;

		/* set क्रम high घड़ीs */
		latency_watermark_a = min(dce8_latency_watermark(&wm_high), (u32)65535);

		/* possibly क्रमce display priority to high */
		/* should really करो this at mode validation समय... */
		अगर (!dce8_average_bandwidth_vs_dram_bandwidth_क्रम_display(&wm_high) ||
		    !dce8_average_bandwidth_vs_available_bandwidth(&wm_high) ||
		    !dce8_check_latency_hiding(&wm_high) ||
		    (rdev->disp_priority == 2)) अणु
			DRM_DEBUG_KMS("force priority to high\n");
		पूर्ण

		/* watermark क्रम low घड़ीs */
		अगर ((rdev->pm.pm_method == PM_METHOD_DPM) &&
		    rdev->pm.dpm_enabled) अणु
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
		wm_low.dram_channels = cik_get_number_of_dram_channels(rdev);
		wm_low.num_heads = num_heads;

		/* set क्रम low घड़ीs */
		latency_watermark_b = min(dce8_latency_watermark(&wm_low), (u32)65535);

		/* possibly क्रमce display priority to high */
		/* should really करो this at mode validation समय... */
		अगर (!dce8_average_bandwidth_vs_dram_bandwidth_क्रम_display(&wm_low) ||
		    !dce8_average_bandwidth_vs_available_bandwidth(&wm_low) ||
		    !dce8_check_latency_hiding(&wm_low) ||
		    (rdev->disp_priority == 2)) अणु
			DRM_DEBUG_KMS("force priority to high\n");
		पूर्ण

		/* Save number of lines the linebuffer leads beक्रमe the scanout */
		radeon_crtc->lb_vblank_lead_lines = DIV_ROUND_UP(lb_size, mode->crtc_hdisplay);
	पूर्ण

	/* select wm A */
	wm_mask = RREG32(DPG_WATERMARK_MASK_CONTROL + radeon_crtc->crtc_offset);
	पंचांगp = wm_mask;
	पंचांगp &= ~LATENCY_WATERMARK_MASK(3);
	पंचांगp |= LATENCY_WATERMARK_MASK(1);
	WREG32(DPG_WATERMARK_MASK_CONTROL + radeon_crtc->crtc_offset, पंचांगp);
	WREG32(DPG_PIPE_LATENCY_CONTROL + radeon_crtc->crtc_offset,
	       (LATENCY_LOW_WATERMARK(latency_watermark_a) |
		LATENCY_HIGH_WATERMARK(line_समय)));
	/* select wm B */
	पंचांगp = RREG32(DPG_WATERMARK_MASK_CONTROL + radeon_crtc->crtc_offset);
	पंचांगp &= ~LATENCY_WATERMARK_MASK(3);
	पंचांगp |= LATENCY_WATERMARK_MASK(2);
	WREG32(DPG_WATERMARK_MASK_CONTROL + radeon_crtc->crtc_offset, पंचांगp);
	WREG32(DPG_PIPE_LATENCY_CONTROL + radeon_crtc->crtc_offset,
	       (LATENCY_LOW_WATERMARK(latency_watermark_b) |
		LATENCY_HIGH_WATERMARK(line_समय)));
	/* restore original selection */
	WREG32(DPG_WATERMARK_MASK_CONTROL + radeon_crtc->crtc_offset, wm_mask);

	/* save values क्रम DPM */
	radeon_crtc->line_समय = line_समय;
	radeon_crtc->wm_high = latency_watermark_a;
	radeon_crtc->wm_low = latency_watermark_b;
पूर्ण

/**
 * dce8_bandwidth_update - program display watermarks
 *
 * @rdev: radeon_device poपूर्णांकer
 *
 * Calculate and program the display watermarks and line
 * buffer allocation (CIK).
 */
व्योम dce8_bandwidth_update(काष्ठा radeon_device *rdev)
अणु
	काष्ठा drm_display_mode *mode = शून्य;
	u32 num_heads = 0, lb_size;
	पूर्णांक i;

	अगर (!rdev->mode_info.mode_config_initialized)
		वापस;

	radeon_update_display_priority(rdev);

	क्रम (i = 0; i < rdev->num_crtc; i++) अणु
		अगर (rdev->mode_info.crtcs[i]->base.enabled)
			num_heads++;
	पूर्ण
	क्रम (i = 0; i < rdev->num_crtc; i++) अणु
		mode = &rdev->mode_info.crtcs[i]->base.mode;
		lb_size = dce8_line_buffer_adjust(rdev, rdev->mode_info.crtcs[i], mode);
		dce8_program_watermarks(rdev, rdev->mode_info.crtcs[i], lb_size, num_heads);
	पूर्ण
पूर्ण

/**
 * cik_get_gpu_घड़ी_counter - वापस GPU घड़ी counter snapshot
 *
 * @rdev: radeon_device poपूर्णांकer
 *
 * Fetches a GPU घड़ी counter snapshot (SI).
 * Returns the 64 bit घड़ी counter snapshot.
 */
uपूर्णांक64_t cik_get_gpu_घड़ी_counter(काष्ठा radeon_device *rdev)
अणु
	uपूर्णांक64_t घड़ी;

	mutex_lock(&rdev->gpu_घड़ी_mutex);
	WREG32(RLC_CAPTURE_GPU_CLOCK_COUNT, 1);
	घड़ी = (uपूर्णांक64_t)RREG32(RLC_GPU_CLOCK_COUNT_LSB) |
		((uपूर्णांक64_t)RREG32(RLC_GPU_CLOCK_COUNT_MSB) << 32ULL);
	mutex_unlock(&rdev->gpu_घड़ी_mutex);
	वापस घड़ी;
पूर्ण

अटल पूर्णांक cik_set_uvd_घड़ी(काष्ठा radeon_device *rdev, u32 घड़ी,
			     u32 cntl_reg, u32 status_reg)
अणु
	पूर्णांक r, i;
	काष्ठा atom_घड़ी_भागiders भागiders;
	uपूर्णांक32_t पंचांगp;

	r = radeon_atom_get_घड़ी_भागiders(rdev, COMPUTE_GPUCLK_INPUT_FLAG_DEFAULT_GPUCLK,
					   घड़ी, false, &भागiders);
	अगर (r)
		वापस r;

	पंचांगp = RREG32_SMC(cntl_reg);
	पंचांगp &= ~(DCLK_सूची_CNTL_EN|DCLK_DIVIDER_MASK);
	पंचांगp |= भागiders.post_भागider;
	WREG32_SMC(cntl_reg, पंचांगp);

	क्रम (i = 0; i < 100; i++) अणु
		अगर (RREG32_SMC(status_reg) & DCLK_STATUS)
			अवरोध;
		mdelay(10);
	पूर्ण
	अगर (i == 100)
		वापस -ETIMEDOUT;

	वापस 0;
पूर्ण

पूर्णांक cik_set_uvd_घड़ीs(काष्ठा radeon_device *rdev, u32 vclk, u32 dclk)
अणु
	पूर्णांक r = 0;

	r = cik_set_uvd_घड़ी(rdev, vclk, CG_VCLK_CNTL, CG_VCLK_STATUS);
	अगर (r)
		वापस r;

	r = cik_set_uvd_घड़ी(rdev, dclk, CG_DCLK_CNTL, CG_DCLK_STATUS);
	वापस r;
पूर्ण

पूर्णांक cik_set_vce_घड़ीs(काष्ठा radeon_device *rdev, u32 evclk, u32 ecclk)
अणु
	पूर्णांक r, i;
	काष्ठा atom_घड़ी_भागiders भागiders;
	u32 पंचांगp;

	r = radeon_atom_get_घड़ी_भागiders(rdev, COMPUTE_GPUCLK_INPUT_FLAG_DEFAULT_GPUCLK,
					   ecclk, false, &भागiders);
	अगर (r)
		वापस r;

	क्रम (i = 0; i < 100; i++) अणु
		अगर (RREG32_SMC(CG_ECLK_STATUS) & ECLK_STATUS)
			अवरोध;
		mdelay(10);
	पूर्ण
	अगर (i == 100)
		वापस -ETIMEDOUT;

	पंचांगp = RREG32_SMC(CG_ECLK_CNTL);
	पंचांगp &= ~(ECLK_सूची_CNTL_EN|ECLK_DIVIDER_MASK);
	पंचांगp |= भागiders.post_भागider;
	WREG32_SMC(CG_ECLK_CNTL, पंचांगp);

	क्रम (i = 0; i < 100; i++) अणु
		अगर (RREG32_SMC(CG_ECLK_STATUS) & ECLK_STATUS)
			अवरोध;
		mdelay(10);
	पूर्ण
	अगर (i == 100)
		वापस -ETIMEDOUT;

	वापस 0;
पूर्ण

अटल व्योम cik_pcie_gen3_enable(काष्ठा radeon_device *rdev)
अणु
	काष्ठा pci_dev *root = rdev->pdev->bus->self;
	क्रमागत pci_bus_speed speed_cap;
	u32 speed_cntl, current_data_rate;
	पूर्णांक i;
	u16 पंचांगp16;

	अगर (pci_is_root_bus(rdev->pdev->bus))
		वापस;

	अगर (radeon_pcie_gen2 == 0)
		वापस;

	अगर (rdev->flags & RADEON_IS_IGP)
		वापस;

	अगर (!(rdev->flags & RADEON_IS_PCIE))
		वापस;

	speed_cap = pcie_get_speed_cap(root);
	अगर (speed_cap == PCI_SPEED_UNKNOWN)
		वापस;

	अगर ((speed_cap != PCIE_SPEED_8_0GT) &&
	    (speed_cap != PCIE_SPEED_5_0GT))
		वापस;

	speed_cntl = RREG32_PCIE_PORT(PCIE_LC_SPEED_CNTL);
	current_data_rate = (speed_cntl & LC_CURRENT_DATA_RATE_MASK) >>
		LC_CURRENT_DATA_RATE_SHIFT;
	अगर (speed_cap == PCIE_SPEED_8_0GT) अणु
		अगर (current_data_rate == 2) अणु
			DRM_INFO("PCIE gen 3 link speeds already enabled\n");
			वापस;
		पूर्ण
		DRM_INFO("enabling PCIE gen 3 link speeds, disable with radeon.pcie_gen2=0\n");
	पूर्ण अन्यथा अगर (speed_cap == PCIE_SPEED_5_0GT) अणु
		अगर (current_data_rate == 1) अणु
			DRM_INFO("PCIE gen 2 link speeds already enabled\n");
			वापस;
		पूर्ण
		DRM_INFO("enabling PCIE gen 2 link speeds, disable with radeon.pcie_gen2=0\n");
	पूर्ण

	अगर (!pci_is_pcie(root) || !pci_is_pcie(rdev->pdev))
		वापस;

	अगर (speed_cap == PCIE_SPEED_8_0GT) अणु
		/* re-try equalization अगर gen3 is not alपढ़ोy enabled */
		अगर (current_data_rate != 2) अणु
			u16 bridge_cfg, gpu_cfg;
			u16 bridge_cfg2, gpu_cfg2;
			u32 max_lw, current_lw, पंचांगp;

			pcie_capability_पढ़ो_word(root, PCI_EXP_LNKCTL,
						  &bridge_cfg);
			pcie_capability_पढ़ो_word(rdev->pdev, PCI_EXP_LNKCTL,
						  &gpu_cfg);

			पंचांगp16 = bridge_cfg | PCI_EXP_LNKCTL_HAWD;
			pcie_capability_ग_लिखो_word(root, PCI_EXP_LNKCTL, पंचांगp16);

			पंचांगp16 = gpu_cfg | PCI_EXP_LNKCTL_HAWD;
			pcie_capability_ग_लिखो_word(rdev->pdev, PCI_EXP_LNKCTL,
						   पंचांगp16);

			पंचांगp = RREG32_PCIE_PORT(PCIE_LC_STATUS1);
			max_lw = (पंचांगp & LC_DETECTED_LINK_WIDTH_MASK) >> LC_DETECTED_LINK_WIDTH_SHIFT;
			current_lw = (पंचांगp & LC_OPERATING_LINK_WIDTH_MASK) >> LC_OPERATING_LINK_WIDTH_SHIFT;

			अगर (current_lw < max_lw) अणु
				पंचांगp = RREG32_PCIE_PORT(PCIE_LC_LINK_WIDTH_CNTL);
				अगर (पंचांगp & LC_RENEGOTIATION_SUPPORT) अणु
					पंचांगp &= ~(LC_LINK_WIDTH_MASK | LC_UPCONFIGURE_DIS);
					पंचांगp |= (max_lw << LC_LINK_WIDTH_SHIFT);
					पंचांगp |= LC_UPCONFIGURE_SUPPORT | LC_RENEGOTIATE_EN | LC_RECONFIG_NOW;
					WREG32_PCIE_PORT(PCIE_LC_LINK_WIDTH_CNTL, पंचांगp);
				पूर्ण
			पूर्ण

			क्रम (i = 0; i < 10; i++) अणु
				/* check status */
				pcie_capability_पढ़ो_word(rdev->pdev,
							  PCI_EXP_DEVSTA,
							  &पंचांगp16);
				अगर (पंचांगp16 & PCI_EXP_DEVSTA_TRPND)
					अवरोध;

				pcie_capability_पढ़ो_word(root, PCI_EXP_LNKCTL,
							  &bridge_cfg);
				pcie_capability_पढ़ो_word(rdev->pdev,
							  PCI_EXP_LNKCTL,
							  &gpu_cfg);

				pcie_capability_पढ़ो_word(root, PCI_EXP_LNKCTL2,
							  &bridge_cfg2);
				pcie_capability_पढ़ो_word(rdev->pdev,
							  PCI_EXP_LNKCTL2,
							  &gpu_cfg2);

				पंचांगp = RREG32_PCIE_PORT(PCIE_LC_CNTL4);
				पंचांगp |= LC_SET_QUIESCE;
				WREG32_PCIE_PORT(PCIE_LC_CNTL4, पंचांगp);

				पंचांगp = RREG32_PCIE_PORT(PCIE_LC_CNTL4);
				पंचांगp |= LC_REDO_EQ;
				WREG32_PCIE_PORT(PCIE_LC_CNTL4, पंचांगp);

				msleep(100);

				/* linkctl */
				pcie_capability_पढ़ो_word(root, PCI_EXP_LNKCTL,
							  &पंचांगp16);
				पंचांगp16 &= ~PCI_EXP_LNKCTL_HAWD;
				पंचांगp16 |= (bridge_cfg & PCI_EXP_LNKCTL_HAWD);
				pcie_capability_ग_लिखो_word(root, PCI_EXP_LNKCTL,
							   पंचांगp16);

				pcie_capability_पढ़ो_word(rdev->pdev,
							  PCI_EXP_LNKCTL,
							  &पंचांगp16);
				पंचांगp16 &= ~PCI_EXP_LNKCTL_HAWD;
				पंचांगp16 |= (gpu_cfg & PCI_EXP_LNKCTL_HAWD);
				pcie_capability_ग_लिखो_word(rdev->pdev,
							   PCI_EXP_LNKCTL,
							   पंचांगp16);

				/* linkctl2 */
				pcie_capability_पढ़ो_word(root, PCI_EXP_LNKCTL2,
							  &पंचांगp16);
				पंचांगp16 &= ~(PCI_EXP_LNKCTL2_ENTER_COMP |
					   PCI_EXP_LNKCTL2_TX_MARGIN);
				पंचांगp16 |= (bridge_cfg2 &
					  (PCI_EXP_LNKCTL2_ENTER_COMP |
					   PCI_EXP_LNKCTL2_TX_MARGIN));
				pcie_capability_ग_लिखो_word(root,
							   PCI_EXP_LNKCTL2,
							   पंचांगp16);

				pcie_capability_पढ़ो_word(rdev->pdev,
							  PCI_EXP_LNKCTL2,
							  &पंचांगp16);
				पंचांगp16 &= ~(PCI_EXP_LNKCTL2_ENTER_COMP |
					   PCI_EXP_LNKCTL2_TX_MARGIN);
				पंचांगp16 |= (gpu_cfg2 &
					  (PCI_EXP_LNKCTL2_ENTER_COMP |
					   PCI_EXP_LNKCTL2_TX_MARGIN));
				pcie_capability_ग_लिखो_word(rdev->pdev,
							   PCI_EXP_LNKCTL2,
							   पंचांगp16);

				पंचांगp = RREG32_PCIE_PORT(PCIE_LC_CNTL4);
				पंचांगp &= ~LC_SET_QUIESCE;
				WREG32_PCIE_PORT(PCIE_LC_CNTL4, पंचांगp);
			पूर्ण
		पूर्ण
	पूर्ण

	/* set the link speed */
	speed_cntl |= LC_FORCE_EN_SW_SPEED_CHANGE | LC_FORCE_DIS_HW_SPEED_CHANGE;
	speed_cntl &= ~LC_FORCE_DIS_SW_SPEED_CHANGE;
	WREG32_PCIE_PORT(PCIE_LC_SPEED_CNTL, speed_cntl);

	pcie_capability_पढ़ो_word(rdev->pdev, PCI_EXP_LNKCTL2, &पंचांगp16);
	पंचांगp16 &= ~PCI_EXP_LNKCTL2_TLS;
	अगर (speed_cap == PCIE_SPEED_8_0GT)
		पंचांगp16 |= PCI_EXP_LNKCTL2_TLS_8_0GT; /* gen3 */
	अन्यथा अगर (speed_cap == PCIE_SPEED_5_0GT)
		पंचांगp16 |= PCI_EXP_LNKCTL2_TLS_5_0GT; /* gen2 */
	अन्यथा
		पंचांगp16 |= PCI_EXP_LNKCTL2_TLS_2_5GT; /* gen1 */
	pcie_capability_ग_लिखो_word(rdev->pdev, PCI_EXP_LNKCTL2, पंचांगp16);

	speed_cntl = RREG32_PCIE_PORT(PCIE_LC_SPEED_CNTL);
	speed_cntl |= LC_INITIATE_LINK_SPEED_CHANGE;
	WREG32_PCIE_PORT(PCIE_LC_SPEED_CNTL, speed_cntl);

	क्रम (i = 0; i < rdev->usec_समयout; i++) अणु
		speed_cntl = RREG32_PCIE_PORT(PCIE_LC_SPEED_CNTL);
		अगर ((speed_cntl & LC_INITIATE_LINK_SPEED_CHANGE) == 0)
			अवरोध;
		udelay(1);
	पूर्ण
पूर्ण

अटल व्योम cik_program_aspm(काष्ठा radeon_device *rdev)
अणु
	u32 data, orig;
	bool disable_l0s = false, disable_l1 = false, disable_plloff_in_l1 = false;
	bool disable_clkreq = false;

	अगर (radeon_aspm == 0)
		वापस;

	/* XXX द्विगुन check IGPs */
	अगर (rdev->flags & RADEON_IS_IGP)
		वापस;

	अगर (!(rdev->flags & RADEON_IS_PCIE))
		वापस;

	orig = data = RREG32_PCIE_PORT(PCIE_LC_N_FTS_CNTL);
	data &= ~LC_XMIT_N_FTS_MASK;
	data |= LC_XMIT_N_FTS(0x24) | LC_XMIT_N_FTS_OVERRIDE_EN;
	अगर (orig != data)
		WREG32_PCIE_PORT(PCIE_LC_N_FTS_CNTL, data);

	orig = data = RREG32_PCIE_PORT(PCIE_LC_CNTL3);
	data |= LC_GO_TO_RECOVERY;
	अगर (orig != data)
		WREG32_PCIE_PORT(PCIE_LC_CNTL3, data);

	orig = data = RREG32_PCIE_PORT(PCIE_P_CNTL);
	data |= P_IGNORE_EDB_ERR;
	अगर (orig != data)
		WREG32_PCIE_PORT(PCIE_P_CNTL, data);

	orig = data = RREG32_PCIE_PORT(PCIE_LC_CNTL);
	data &= ~(LC_L0S_INACTIVITY_MASK | LC_L1_INACTIVITY_MASK);
	data |= LC_PMI_TO_L1_DIS;
	अगर (!disable_l0s)
		data |= LC_L0S_INACTIVITY(7);

	अगर (!disable_l1) अणु
		data |= LC_L1_INACTIVITY(7);
		data &= ~LC_PMI_TO_L1_DIS;
		अगर (orig != data)
			WREG32_PCIE_PORT(PCIE_LC_CNTL, data);

		अगर (!disable_plloff_in_l1) अणु
			bool clk_req_support;

			orig = data = RREG32_PCIE_PORT(PB0_PIF_PWRDOWN_0);
			data &= ~(PLL_POWER_STATE_IN_OFF_0_MASK | PLL_POWER_STATE_IN_TXS2_0_MASK);
			data |= PLL_POWER_STATE_IN_OFF_0(7) | PLL_POWER_STATE_IN_TXS2_0(7);
			अगर (orig != data)
				WREG32_PCIE_PORT(PB0_PIF_PWRDOWN_0, data);

			orig = data = RREG32_PCIE_PORT(PB0_PIF_PWRDOWN_1);
			data &= ~(PLL_POWER_STATE_IN_OFF_1_MASK | PLL_POWER_STATE_IN_TXS2_1_MASK);
			data |= PLL_POWER_STATE_IN_OFF_1(7) | PLL_POWER_STATE_IN_TXS2_1(7);
			अगर (orig != data)
				WREG32_PCIE_PORT(PB0_PIF_PWRDOWN_1, data);

			orig = data = RREG32_PCIE_PORT(PB1_PIF_PWRDOWN_0);
			data &= ~(PLL_POWER_STATE_IN_OFF_0_MASK | PLL_POWER_STATE_IN_TXS2_0_MASK);
			data |= PLL_POWER_STATE_IN_OFF_0(7) | PLL_POWER_STATE_IN_TXS2_0(7);
			अगर (orig != data)
				WREG32_PCIE_PORT(PB1_PIF_PWRDOWN_0, data);

			orig = data = RREG32_PCIE_PORT(PB1_PIF_PWRDOWN_1);
			data &= ~(PLL_POWER_STATE_IN_OFF_1_MASK | PLL_POWER_STATE_IN_TXS2_1_MASK);
			data |= PLL_POWER_STATE_IN_OFF_1(7) | PLL_POWER_STATE_IN_TXS2_1(7);
			अगर (orig != data)
				WREG32_PCIE_PORT(PB1_PIF_PWRDOWN_1, data);

			orig = data = RREG32_PCIE_PORT(PCIE_LC_LINK_WIDTH_CNTL);
			data &= ~LC_DYN_LANES_PWR_STATE_MASK;
			data |= LC_DYN_LANES_PWR_STATE(3);
			अगर (orig != data)
				WREG32_PCIE_PORT(PCIE_LC_LINK_WIDTH_CNTL, data);

			अगर (!disable_clkreq &&
			    !pci_is_root_bus(rdev->pdev->bus)) अणु
				काष्ठा pci_dev *root = rdev->pdev->bus->self;
				u32 lnkcap;

				clk_req_support = false;
				pcie_capability_पढ़ो_dword(root, PCI_EXP_LNKCAP, &lnkcap);
				अगर (lnkcap & PCI_EXP_LNKCAP_CLKPM)
					clk_req_support = true;
			पूर्ण अन्यथा अणु
				clk_req_support = false;
			पूर्ण

			अगर (clk_req_support) अणु
				orig = data = RREG32_PCIE_PORT(PCIE_LC_CNTL2);
				data |= LC_ALLOW_PDWN_IN_L1 | LC_ALLOW_PDWN_IN_L23;
				अगर (orig != data)
					WREG32_PCIE_PORT(PCIE_LC_CNTL2, data);

				orig = data = RREG32_SMC(THM_CLK_CNTL);
				data &= ~(CMON_CLK_SEL_MASK | TMON_CLK_SEL_MASK);
				data |= CMON_CLK_SEL(1) | TMON_CLK_SEL(1);
				अगर (orig != data)
					WREG32_SMC(THM_CLK_CNTL, data);

				orig = data = RREG32_SMC(MISC_CLK_CTRL);
				data &= ~(DEEP_SLEEP_CLK_SEL_MASK | ZCLK_SEL_MASK);
				data |= DEEP_SLEEP_CLK_SEL(1) | ZCLK_SEL(1);
				अगर (orig != data)
					WREG32_SMC(MISC_CLK_CTRL, data);

				orig = data = RREG32_SMC(CG_CLKPIN_CNTL);
				data &= ~BCLK_AS_XCLK;
				अगर (orig != data)
					WREG32_SMC(CG_CLKPIN_CNTL, data);

				orig = data = RREG32_SMC(CG_CLKPIN_CNTL_2);
				data &= ~FORCE_BIF_REFCLK_EN;
				अगर (orig != data)
					WREG32_SMC(CG_CLKPIN_CNTL_2, data);

				orig = data = RREG32_SMC(MPLL_BYPASSCLK_SEL);
				data &= ~MPLL_CLKOUT_SEL_MASK;
				data |= MPLL_CLKOUT_SEL(4);
				अगर (orig != data)
					WREG32_SMC(MPLL_BYPASSCLK_SEL, data);
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (orig != data)
			WREG32_PCIE_PORT(PCIE_LC_CNTL, data);
	पूर्ण

	orig = data = RREG32_PCIE_PORT(PCIE_CNTL2);
	data |= SLV_MEM_LS_EN | MST_MEM_LS_EN | REPLAY_MEM_LS_EN;
	अगर (orig != data)
		WREG32_PCIE_PORT(PCIE_CNTL2, data);

	अगर (!disable_l0s) अणु
		data = RREG32_PCIE_PORT(PCIE_LC_N_FTS_CNTL);
		अगर((data & LC_N_FTS_MASK) == LC_N_FTS_MASK) अणु
			data = RREG32_PCIE_PORT(PCIE_LC_STATUS1);
			अगर ((data & LC_REVERSE_XMIT) && (data & LC_REVERSE_RCVR)) अणु
				orig = data = RREG32_PCIE_PORT(PCIE_LC_CNTL);
				data &= ~LC_L0S_INACTIVITY_MASK;
				अगर (orig != data)
					WREG32_PCIE_PORT(PCIE_LC_CNTL, data);
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण
