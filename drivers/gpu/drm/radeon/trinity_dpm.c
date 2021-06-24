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
 */

#समावेश <linux/pci.h>
#समावेश <linux/seq_file.h>

#समावेश "r600_dpm.h"
#समावेश "radeon.h"
#समावेश "radeon_asic.h"
#समावेश "trinity_dpm.h"
#समावेश "trinityd.h"
#समावेश "vce.h"

#घोषणा TRINITY_MAX_DEEPSLEEP_DIVIDER_ID 5
#घोषणा TRINITY_MINIMUM_ENGINE_CLOCK 800
#घोषणा SCLK_MIN_DIV_INTV_SHIFT     12
#घोषणा TRINITY_DISPCLK_BYPASS_THRESHOLD 10000

#अगर_अघोषित TRINITY_MGCG_SEQUENCE
#घोषणा TRINITY_MGCG_SEQUENCE  100

अटल स्थिर u32 trinity_mgcg_shls_शेष[] =
अणु
	/* Register, Value, Mask */
	0x0000802c, 0xc0000000, 0xffffffff,
	0x00003fc4, 0xc0000000, 0xffffffff,
	0x00005448, 0x00000100, 0xffffffff,
	0x000055e4, 0x00000100, 0xffffffff,
	0x0000160c, 0x00000100, 0xffffffff,
	0x00008984, 0x06000100, 0xffffffff,
	0x0000c164, 0x00000100, 0xffffffff,
	0x00008a18, 0x00000100, 0xffffffff,
	0x0000897c, 0x06000100, 0xffffffff,
	0x00008b28, 0x00000100, 0xffffffff,
	0x00009144, 0x00800200, 0xffffffff,
	0x00009a60, 0x00000100, 0xffffffff,
	0x00009868, 0x00000100, 0xffffffff,
	0x00008d58, 0x00000100, 0xffffffff,
	0x00009510, 0x00000100, 0xffffffff,
	0x0000949c, 0x00000100, 0xffffffff,
	0x00009654, 0x00000100, 0xffffffff,
	0x00009030, 0x00000100, 0xffffffff,
	0x00009034, 0x00000100, 0xffffffff,
	0x00009038, 0x00000100, 0xffffffff,
	0x0000903c, 0x00000100, 0xffffffff,
	0x00009040, 0x00000100, 0xffffffff,
	0x0000a200, 0x00000100, 0xffffffff,
	0x0000a204, 0x00000100, 0xffffffff,
	0x0000a208, 0x00000100, 0xffffffff,
	0x0000a20c, 0x00000100, 0xffffffff,
	0x00009744, 0x00000100, 0xffffffff,
	0x00003f80, 0x00000100, 0xffffffff,
	0x0000a210, 0x00000100, 0xffffffff,
	0x0000a214, 0x00000100, 0xffffffff,
	0x000004d8, 0x00000100, 0xffffffff,
	0x00009664, 0x00000100, 0xffffffff,
	0x00009698, 0x00000100, 0xffffffff,
	0x000004d4, 0x00000200, 0xffffffff,
	0x000004d0, 0x00000000, 0xffffffff,
	0x000030cc, 0x00000104, 0xffffffff,
	0x0000d0c0, 0x00000100, 0xffffffff,
	0x0000d8c0, 0x00000100, 0xffffffff,
	0x0000951c, 0x00010000, 0xffffffff,
	0x00009160, 0x00030002, 0xffffffff,
	0x00009164, 0x00050004, 0xffffffff,
	0x00009168, 0x00070006, 0xffffffff,
	0x00009178, 0x00070000, 0xffffffff,
	0x0000917c, 0x00030002, 0xffffffff,
	0x00009180, 0x00050004, 0xffffffff,
	0x0000918c, 0x00010006, 0xffffffff,
	0x00009190, 0x00090008, 0xffffffff,
	0x00009194, 0x00070000, 0xffffffff,
	0x00009198, 0x00030002, 0xffffffff,
	0x0000919c, 0x00050004, 0xffffffff,
	0x000091a8, 0x00010006, 0xffffffff,
	0x000091ac, 0x00090008, 0xffffffff,
	0x000091b0, 0x00070000, 0xffffffff,
	0x000091b4, 0x00030002, 0xffffffff,
	0x000091b8, 0x00050004, 0xffffffff,
	0x000091c4, 0x00010006, 0xffffffff,
	0x000091c8, 0x00090008, 0xffffffff,
	0x000091cc, 0x00070000, 0xffffffff,
	0x000091d0, 0x00030002, 0xffffffff,
	0x000091d4, 0x00050004, 0xffffffff,
	0x000091e0, 0x00010006, 0xffffffff,
	0x000091e4, 0x00090008, 0xffffffff,
	0x000091e8, 0x00000000, 0xffffffff,
	0x000091ec, 0x00070000, 0xffffffff,
	0x000091f0, 0x00030002, 0xffffffff,
	0x000091f4, 0x00050004, 0xffffffff,
	0x00009200, 0x00010006, 0xffffffff,
	0x00009204, 0x00090008, 0xffffffff,
	0x00009208, 0x00070000, 0xffffffff,
	0x0000920c, 0x00030002, 0xffffffff,
	0x00009210, 0x00050004, 0xffffffff,
	0x0000921c, 0x00010006, 0xffffffff,
	0x00009220, 0x00090008, 0xffffffff,
	0x00009294, 0x00000000, 0xffffffff
पूर्ण;
#पूर्ण_अगर

#अगर_अघोषित TRINITY_SYSLS_SEQUENCE
#घोषणा TRINITY_SYSLS_SEQUENCE  100

अटल स्थिर u32 trinity_sysls_disable[] =
अणु
	/* Register, Value, Mask */
	0x0000d0c0, 0x00000000, 0xffffffff,
	0x0000d8c0, 0x00000000, 0xffffffff,
	0x000055e8, 0x00000000, 0xffffffff,
	0x0000d0bc, 0x00000000, 0xffffffff,
	0x0000d8bc, 0x00000000, 0xffffffff,
	0x000015c0, 0x00041401, 0xffffffff,
	0x0000264c, 0x00040400, 0xffffffff,
	0x00002648, 0x00040400, 0xffffffff,
	0x00002650, 0x00040400, 0xffffffff,
	0x000020b8, 0x00040400, 0xffffffff,
	0x000020bc, 0x00040400, 0xffffffff,
	0x000020c0, 0x00040c80, 0xffffffff,
	0x0000f4a0, 0x000000c0, 0xffffffff,
	0x0000f4a4, 0x00680000, 0xffffffff,
	0x00002f50, 0x00000404, 0xffffffff,
	0x000004c8, 0x00000001, 0xffffffff,
	0x0000641c, 0x00007ffd, 0xffffffff,
	0x00000c7c, 0x0000ff00, 0xffffffff,
	0x00006dfc, 0x0000007f, 0xffffffff
पूर्ण;

अटल स्थिर u32 trinity_sysls_enable[] =
अणु
	/* Register, Value, Mask */
	0x000055e8, 0x00000001, 0xffffffff,
	0x0000d0bc, 0x00000100, 0xffffffff,
	0x0000d8bc, 0x00000100, 0xffffffff,
	0x000015c0, 0x000c1401, 0xffffffff,
	0x0000264c, 0x000c0400, 0xffffffff,
	0x00002648, 0x000c0400, 0xffffffff,
	0x00002650, 0x000c0400, 0xffffffff,
	0x000020b8, 0x000c0400, 0xffffffff,
	0x000020bc, 0x000c0400, 0xffffffff,
	0x000020c0, 0x000c0c80, 0xffffffff,
	0x0000f4a0, 0x000000c0, 0xffffffff,
	0x0000f4a4, 0x00680fff, 0xffffffff,
	0x00002f50, 0x00000903, 0xffffffff,
	0x000004c8, 0x00000000, 0xffffffff,
	0x0000641c, 0x00000000, 0xffffffff,
	0x00000c7c, 0x00000000, 0xffffffff,
	0x00006dfc, 0x00000000, 0xffffffff
पूर्ण;
#पूर्ण_अगर

अटल स्थिर u32 trinity_override_mgpg_sequences[] =
अणु
	/* Register, Value */
	0x00000200, 0xE030032C,
	0x00000204, 0x00000FFF,
	0x00000200, 0xE0300058,
	0x00000204, 0x00030301,
	0x00000200, 0xE0300054,
	0x00000204, 0x500010FF,
	0x00000200, 0xE0300074,
	0x00000204, 0x00030301,
	0x00000200, 0xE0300070,
	0x00000204, 0x500010FF,
	0x00000200, 0xE0300090,
	0x00000204, 0x00030301,
	0x00000200, 0xE030008C,
	0x00000204, 0x500010FF,
	0x00000200, 0xE03000AC,
	0x00000204, 0x00030301,
	0x00000200, 0xE03000A8,
	0x00000204, 0x500010FF,
	0x00000200, 0xE03000C8,
	0x00000204, 0x00030301,
	0x00000200, 0xE03000C4,
	0x00000204, 0x500010FF,
	0x00000200, 0xE03000E4,
	0x00000204, 0x00030301,
	0x00000200, 0xE03000E0,
	0x00000204, 0x500010FF,
	0x00000200, 0xE0300100,
	0x00000204, 0x00030301,
	0x00000200, 0xE03000FC,
	0x00000204, 0x500010FF,
	0x00000200, 0xE0300058,
	0x00000204, 0x00030303,
	0x00000200, 0xE0300054,
	0x00000204, 0x600010FF,
	0x00000200, 0xE0300074,
	0x00000204, 0x00030303,
	0x00000200, 0xE0300070,
	0x00000204, 0x600010FF,
	0x00000200, 0xE0300090,
	0x00000204, 0x00030303,
	0x00000200, 0xE030008C,
	0x00000204, 0x600010FF,
	0x00000200, 0xE03000AC,
	0x00000204, 0x00030303,
	0x00000200, 0xE03000A8,
	0x00000204, 0x600010FF,
	0x00000200, 0xE03000C8,
	0x00000204, 0x00030303,
	0x00000200, 0xE03000C4,
	0x00000204, 0x600010FF,
	0x00000200, 0xE03000E4,
	0x00000204, 0x00030303,
	0x00000200, 0xE03000E0,
	0x00000204, 0x600010FF,
	0x00000200, 0xE0300100,
	0x00000204, 0x00030303,
	0x00000200, 0xE03000FC,
	0x00000204, 0x600010FF,
	0x00000200, 0xE0300058,
	0x00000204, 0x00030303,
	0x00000200, 0xE0300054,
	0x00000204, 0x700010FF,
	0x00000200, 0xE0300074,
	0x00000204, 0x00030303,
	0x00000200, 0xE0300070,
	0x00000204, 0x700010FF,
	0x00000200, 0xE0300090,
	0x00000204, 0x00030303,
	0x00000200, 0xE030008C,
	0x00000204, 0x700010FF,
	0x00000200, 0xE03000AC,
	0x00000204, 0x00030303,
	0x00000200, 0xE03000A8,
	0x00000204, 0x700010FF,
	0x00000200, 0xE03000C8,
	0x00000204, 0x00030303,
	0x00000200, 0xE03000C4,
	0x00000204, 0x700010FF,
	0x00000200, 0xE03000E4,
	0x00000204, 0x00030303,
	0x00000200, 0xE03000E0,
	0x00000204, 0x700010FF,
	0x00000200, 0xE0300100,
	0x00000204, 0x00030303,
	0x00000200, 0xE03000FC,
	0x00000204, 0x700010FF,
	0x00000200, 0xE0300058,
	0x00000204, 0x00010303,
	0x00000200, 0xE0300054,
	0x00000204, 0x800010FF,
	0x00000200, 0xE0300074,
	0x00000204, 0x00010303,
	0x00000200, 0xE0300070,
	0x00000204, 0x800010FF,
	0x00000200, 0xE0300090,
	0x00000204, 0x00010303,
	0x00000200, 0xE030008C,
	0x00000204, 0x800010FF,
	0x00000200, 0xE03000AC,
	0x00000204, 0x00010303,
	0x00000200, 0xE03000A8,
	0x00000204, 0x800010FF,
	0x00000200, 0xE03000C4,
	0x00000204, 0x800010FF,
	0x00000200, 0xE03000C8,
	0x00000204, 0x00010303,
	0x00000200, 0xE03000E4,
	0x00000204, 0x00010303,
	0x00000200, 0xE03000E0,
	0x00000204, 0x800010FF,
	0x00000200, 0xE0300100,
	0x00000204, 0x00010303,
	0x00000200, 0xE03000FC,
	0x00000204, 0x800010FF,
	0x00000200, 0x0001f198,
	0x00000204, 0x0003ffff,
	0x00000200, 0x0001f19C,
	0x00000204, 0x3fffffff,
	0x00000200, 0xE030032C,
	0x00000204, 0x00000000,
पूर्ण;

अटल व्योम trinity_program_clk_gating_hw_sequence(काष्ठा radeon_device *rdev,
						   स्थिर u32 *seq, u32 count);
अटल व्योम trinity_override_dynamic_mg_घातergating(काष्ठा radeon_device *rdev);
अटल व्योम trinity_apply_state_adjust_rules(काष्ठा radeon_device *rdev,
					     काष्ठा radeon_ps *new_rps,
					     काष्ठा radeon_ps *old_rps);

अटल काष्ठा trinity_ps *trinity_get_ps(काष्ठा radeon_ps *rps)
अणु
	काष्ठा trinity_ps *ps = rps->ps_priv;

	वापस ps;
पूर्ण

अटल काष्ठा trinity_घातer_info *trinity_get_pi(काष्ठा radeon_device *rdev)
अणु
	काष्ठा trinity_घातer_info *pi = rdev->pm.dpm.priv;

	वापस pi;
पूर्ण

अटल व्योम trinity_gfx_घातergating_initialize(काष्ठा radeon_device *rdev)
अणु
	काष्ठा trinity_घातer_info *pi = trinity_get_pi(rdev);
	u32 p, u;
	u32 value;
	काष्ठा atom_घड़ी_भागiders भागiders;
	u32 xclk = radeon_get_xclk(rdev);
	u32 sssd = 1;
	पूर्णांक ret;
	u32 hw_rev = (RREG32(HW_REV) & ATI_REV_ID_MASK) >> ATI_REV_ID_SHIFT;

	ret = radeon_atom_get_घड़ी_भागiders(rdev, COMPUTE_ENGINE_PLL_PARAM,
					     25000, false, &भागiders);
	अगर (ret)
		वापस;

	value = RREG32_SMC(GFX_POWER_GATING_CNTL);
	value &= ~(SSSD_MASK | PDS_DIV_MASK);
	अगर (sssd)
		value |= SSSD(1);
	value |= PDS_DIV(भागiders.post_भाग);
	WREG32_SMC(GFX_POWER_GATING_CNTL, value);

	r600_calculate_u_and_p(500, xclk, 16, &p, &u);

	WREG32(CG_PG_CTRL, SP(p) | SU(u));

	WREG32_P(CG_GIPOTS, CG_GIPOT(p), ~CG_GIPOT_MASK);

	/* XXX द्विगुन check hw_rev */
	अगर (pi->override_dynamic_mgpg && (hw_rev == 0))
		trinity_override_dynamic_mg_घातergating(rdev);

पूर्ण

#घोषणा CGCG_CGTT_LOCAL0_MASK       0xFFFF33FF
#घोषणा CGCG_CGTT_LOCAL1_MASK       0xFFFB0FFE
#घोषणा CGTS_SM_CTRL_REG_DISABLE    0x00600000
#घोषणा CGTS_SM_CTRL_REG_ENABLE     0x96944200

अटल व्योम trinity_mg_घड़ीgating_enable(काष्ठा radeon_device *rdev,
					  bool enable)
अणु
	u32 local0;
	u32 local1;

	अगर (enable) अणु
		local0 = RREG32_CG(CG_CGTT_LOCAL_0);
		local1 = RREG32_CG(CG_CGTT_LOCAL_1);

		WREG32_CG(CG_CGTT_LOCAL_0,
			  (0x00380000 & CGCG_CGTT_LOCAL0_MASK) | (local0 & ~CGCG_CGTT_LOCAL0_MASK) );
		WREG32_CG(CG_CGTT_LOCAL_1,
			  (0x0E000000 & CGCG_CGTT_LOCAL1_MASK) | (local1 & ~CGCG_CGTT_LOCAL1_MASK) );

		WREG32(CGTS_SM_CTRL_REG, CGTS_SM_CTRL_REG_ENABLE);
	पूर्ण अन्यथा अणु
		WREG32(CGTS_SM_CTRL_REG, CGTS_SM_CTRL_REG_DISABLE);

		local0 = RREG32_CG(CG_CGTT_LOCAL_0);
		local1 = RREG32_CG(CG_CGTT_LOCAL_1);

		WREG32_CG(CG_CGTT_LOCAL_0,
			  CGCG_CGTT_LOCAL0_MASK | (local0 & ~CGCG_CGTT_LOCAL0_MASK) );
		WREG32_CG(CG_CGTT_LOCAL_1,
			  CGCG_CGTT_LOCAL1_MASK | (local1 & ~CGCG_CGTT_LOCAL1_MASK) );
	पूर्ण
पूर्ण

अटल व्योम trinity_mg_घड़ीgating_initialize(काष्ठा radeon_device *rdev)
अणु
	u32 count;
	स्थिर u32 *seq = शून्य;

	seq = &trinity_mgcg_shls_शेष[0];
	count = माप(trinity_mgcg_shls_शेष) / (3 * माप(u32));

	trinity_program_clk_gating_hw_sequence(rdev, seq, count);
पूर्ण

अटल व्योम trinity_gfx_घड़ीgating_enable(काष्ठा radeon_device *rdev,
					   bool enable)
अणु
	अगर (enable) अणु
		WREG32_P(SCLK_PWRMGT_CNTL, DYN_GFX_CLK_OFF_EN, ~DYN_GFX_CLK_OFF_EN);
	पूर्ण अन्यथा अणु
		WREG32_P(SCLK_PWRMGT_CNTL, 0, ~DYN_GFX_CLK_OFF_EN);
		WREG32_P(SCLK_PWRMGT_CNTL, GFX_CLK_FORCE_ON, ~GFX_CLK_FORCE_ON);
		WREG32_P(SCLK_PWRMGT_CNTL, 0, ~GFX_CLK_FORCE_ON);
		RREG32(GB_ADDR_CONFIG);
	पूर्ण
पूर्ण

अटल व्योम trinity_program_clk_gating_hw_sequence(काष्ठा radeon_device *rdev,
						   स्थिर u32 *seq, u32 count)
अणु
	u32 i, length = count * 3;

	क्रम (i = 0; i < length; i += 3)
		WREG32_P(seq[i], seq[i+1], ~seq[i+2]);
पूर्ण

अटल व्योम trinity_program_override_mgpg_sequences(काष्ठा radeon_device *rdev,
						    स्थिर u32 *seq, u32 count)
अणु
	u32  i, length = count * 2;

	क्रम (i = 0; i < length; i += 2)
		WREG32(seq[i], seq[i+1]);

पूर्ण

अटल व्योम trinity_override_dynamic_mg_घातergating(काष्ठा radeon_device *rdev)
अणु
	u32 count;
	स्थिर u32 *seq = शून्य;

	seq = &trinity_override_mgpg_sequences[0];
	count = माप(trinity_override_mgpg_sequences) / (2 * माप(u32));

	trinity_program_override_mgpg_sequences(rdev, seq, count);
पूर्ण

अटल व्योम trinity_ls_घड़ीgating_enable(काष्ठा radeon_device *rdev,
					  bool enable)
अणु
	u32 count;
	स्थिर u32 *seq = शून्य;

	अगर (enable) अणु
		seq = &trinity_sysls_enable[0];
		count = माप(trinity_sysls_enable) / (3 * माप(u32));
	पूर्ण अन्यथा अणु
		seq = &trinity_sysls_disable[0];
		count = माप(trinity_sysls_disable) / (3 * माप(u32));
	पूर्ण

	trinity_program_clk_gating_hw_sequence(rdev, seq, count);
पूर्ण

अटल व्योम trinity_gfx_घातergating_enable(काष्ठा radeon_device *rdev,
					   bool enable)
अणु
	अगर (enable) अणु
		अगर (RREG32_SMC(CC_SMU_TST_EFUSE1_MISC) & RB_BACKEND_DISABLE_MASK)
			WREG32_SMC(SMU_SCRATCH_A, (RREG32_SMC(SMU_SCRATCH_A) | 0x01));

		WREG32_P(SCLK_PWRMGT_CNTL, DYN_PWR_DOWN_EN, ~DYN_PWR_DOWN_EN);
	पूर्ण अन्यथा अणु
		WREG32_P(SCLK_PWRMGT_CNTL, 0, ~DYN_PWR_DOWN_EN);
		RREG32(GB_ADDR_CONFIG);
	पूर्ण
पूर्ण

अटल व्योम trinity_gfx_dynamic_mgpg_enable(काष्ठा radeon_device *rdev,
					    bool enable)
अणु
	u32 value;

	अगर (enable) अणु
		value = RREG32_SMC(PM_I_CNTL_1);
		value &= ~DS_PG_CNTL_MASK;
		value |= DS_PG_CNTL(1);
		WREG32_SMC(PM_I_CNTL_1, value);

		value = RREG32_SMC(SMU_S_PG_CNTL);
		value &= ~DS_PG_EN_MASK;
		value |= DS_PG_EN(1);
		WREG32_SMC(SMU_S_PG_CNTL, value);
	पूर्ण अन्यथा अणु
		value = RREG32_SMC(SMU_S_PG_CNTL);
		value &= ~DS_PG_EN_MASK;
		WREG32_SMC(SMU_S_PG_CNTL, value);

		value = RREG32_SMC(PM_I_CNTL_1);
		value &= ~DS_PG_CNTL_MASK;
		WREG32_SMC(PM_I_CNTL_1, value);
	पूर्ण

	trinity_gfx_dynamic_mgpg_config(rdev);

पूर्ण

अटल व्योम trinity_enable_घड़ी_घातer_gating(काष्ठा radeon_device *rdev)
अणु
	काष्ठा trinity_घातer_info *pi = trinity_get_pi(rdev);

	अगर (pi->enable_gfx_घड़ी_gating)
		sumo_gfx_घड़ीgating_initialize(rdev);
	अगर (pi->enable_mg_घड़ी_gating)
		trinity_mg_घड़ीgating_initialize(rdev);
	अगर (pi->enable_gfx_घातer_gating)
		trinity_gfx_घातergating_initialize(rdev);
	अगर (pi->enable_mg_घड़ी_gating) अणु
		trinity_ls_घड़ीgating_enable(rdev, true);
		trinity_mg_घड़ीgating_enable(rdev, true);
	पूर्ण
	अगर (pi->enable_gfx_घड़ी_gating)
		trinity_gfx_घड़ीgating_enable(rdev, true);
	अगर (pi->enable_gfx_dynamic_mgpg)
		trinity_gfx_dynamic_mgpg_enable(rdev, true);
	अगर (pi->enable_gfx_घातer_gating)
		trinity_gfx_घातergating_enable(rdev, true);
पूर्ण

अटल व्योम trinity_disable_घड़ी_घातer_gating(काष्ठा radeon_device *rdev)
अणु
	काष्ठा trinity_घातer_info *pi = trinity_get_pi(rdev);

	अगर (pi->enable_gfx_घातer_gating)
		trinity_gfx_घातergating_enable(rdev, false);
	अगर (pi->enable_gfx_dynamic_mgpg)
		trinity_gfx_dynamic_mgpg_enable(rdev, false);
	अगर (pi->enable_gfx_घड़ी_gating)
		trinity_gfx_घड़ीgating_enable(rdev, false);
	अगर (pi->enable_mg_घड़ी_gating) अणु
		trinity_mg_घड़ीgating_enable(rdev, false);
		trinity_ls_घड़ीgating_enable(rdev, false);
	पूर्ण
पूर्ण

अटल व्योम trinity_set_भागider_value(काष्ठा radeon_device *rdev,
				      u32 index, u32 sclk)
अणु
	काष्ठा atom_घड़ी_भागiders  भागiders;
	पूर्णांक ret;
	u32 value;
	u32 ix = index * TRINITY_SIZखातापूर्ण_DPM_STATE_TABLE;

	ret = radeon_atom_get_घड़ी_भागiders(rdev, COMPUTE_ENGINE_PLL_PARAM,
					     sclk, false, &भागiders);
	अगर (ret)
		वापस;

	value = RREG32_SMC(SMU_SCLK_DPM_STATE_0_CNTL_0 + ix);
	value &= ~CLK_DIVIDER_MASK;
	value |= CLK_DIVIDER(भागiders.post_भाग);
	WREG32_SMC(SMU_SCLK_DPM_STATE_0_CNTL_0 + ix, value);

	ret = radeon_atom_get_घड़ी_भागiders(rdev, COMPUTE_ENGINE_PLL_PARAM,
					     sclk/2, false, &भागiders);
	अगर (ret)
		वापस;

	value = RREG32_SMC(SMU_SCLK_DPM_STATE_0_PG_CNTL + ix);
	value &= ~PD_SCLK_DIVIDER_MASK;
	value |= PD_SCLK_DIVIDER(भागiders.post_भाग);
	WREG32_SMC(SMU_SCLK_DPM_STATE_0_PG_CNTL + ix, value);
पूर्ण

अटल व्योम trinity_set_ds_भागiders(काष्ठा radeon_device *rdev,
				    u32 index, u32 भागider)
अणु
	u32 value;
	u32 ix = index * TRINITY_SIZखातापूर्ण_DPM_STATE_TABLE;

	value = RREG32_SMC(SMU_SCLK_DPM_STATE_0_CNTL_1 + ix);
	value &= ~DS_DIV_MASK;
	value |= DS_DIV(भागider);
	WREG32_SMC(SMU_SCLK_DPM_STATE_0_CNTL_1 + ix, value);
पूर्ण

अटल व्योम trinity_set_ss_भागiders(काष्ठा radeon_device *rdev,
				    u32 index, u32 भागider)
अणु
	u32 value;
	u32 ix = index * TRINITY_SIZखातापूर्ण_DPM_STATE_TABLE;

	value = RREG32_SMC(SMU_SCLK_DPM_STATE_0_CNTL_1 + ix);
	value &= ~DS_SH_DIV_MASK;
	value |= DS_SH_DIV(भागider);
	WREG32_SMC(SMU_SCLK_DPM_STATE_0_CNTL_1 + ix, value);
पूर्ण

अटल व्योम trinity_set_vid(काष्ठा radeon_device *rdev, u32 index, u32 vid)
अणु
	काष्ठा trinity_घातer_info *pi = trinity_get_pi(rdev);
	u32 vid_7bit = sumo_convert_vid2_to_vid7(rdev, &pi->sys_info.vid_mapping_table, vid);
	u32 value;
	u32 ix = index * TRINITY_SIZखातापूर्ण_DPM_STATE_TABLE;

	value = RREG32_SMC(SMU_SCLK_DPM_STATE_0_CNTL_0 + ix);
	value &= ~VID_MASK;
	value |= VID(vid_7bit);
	WREG32_SMC(SMU_SCLK_DPM_STATE_0_CNTL_0 + ix, value);

	value = RREG32_SMC(SMU_SCLK_DPM_STATE_0_CNTL_0 + ix);
	value &= ~LVRT_MASK;
	value |= LVRT(0);
	WREG32_SMC(SMU_SCLK_DPM_STATE_0_CNTL_0 + ix, value);
पूर्ण

अटल व्योम trinity_set_allos_gnb_slow(काष्ठा radeon_device *rdev,
				       u32 index, u32 gnb_slow)
अणु
	u32 value;
	u32 ix = index * TRINITY_SIZखातापूर्ण_DPM_STATE_TABLE;

	value = RREG32_SMC(SMU_SCLK_DPM_STATE_0_CNTL_3 + ix);
	value &= ~GNB_SLOW_MASK;
	value |= GNB_SLOW(gnb_slow);
	WREG32_SMC(SMU_SCLK_DPM_STATE_0_CNTL_3 + ix, value);
पूर्ण

अटल व्योम trinity_set_क्रमce_nbp_state(काष्ठा radeon_device *rdev,
					u32 index, u32 क्रमce_nbp_state)
अणु
	u32 value;
	u32 ix = index * TRINITY_SIZखातापूर्ण_DPM_STATE_TABLE;

	value = RREG32_SMC(SMU_SCLK_DPM_STATE_0_CNTL_3 + ix);
	value &= ~FORCE_NBPS1_MASK;
	value |= FORCE_NBPS1(क्रमce_nbp_state);
	WREG32_SMC(SMU_SCLK_DPM_STATE_0_CNTL_3 + ix, value);
पूर्ण

अटल व्योम trinity_set_display_wm(काष्ठा radeon_device *rdev,
				   u32 index, u32 wm)
अणु
	u32 value;
	u32 ix = index * TRINITY_SIZखातापूर्ण_DPM_STATE_TABLE;

	value = RREG32_SMC(SMU_SCLK_DPM_STATE_0_CNTL_1 + ix);
	value &= ~DISPLAY_WM_MASK;
	value |= DISPLAY_WM(wm);
	WREG32_SMC(SMU_SCLK_DPM_STATE_0_CNTL_1 + ix, value);
पूर्ण

अटल व्योम trinity_set_vce_wm(काष्ठा radeon_device *rdev,
			       u32 index, u32 wm)
अणु
	u32 value;
	u32 ix = index * TRINITY_SIZखातापूर्ण_DPM_STATE_TABLE;

	value = RREG32_SMC(SMU_SCLK_DPM_STATE_0_CNTL_1 + ix);
	value &= ~VCE_WM_MASK;
	value |= VCE_WM(wm);
	WREG32_SMC(SMU_SCLK_DPM_STATE_0_CNTL_1 + ix, value);
पूर्ण

अटल व्योम trinity_set_at(काष्ठा radeon_device *rdev,
			   u32 index, u32 at)
अणु
	u32 value;
	u32 ix = index * TRINITY_SIZखातापूर्ण_DPM_STATE_TABLE;

	value = RREG32_SMC(SMU_SCLK_DPM_STATE_0_AT + ix);
	value &= ~AT_MASK;
	value |= AT(at);
	WREG32_SMC(SMU_SCLK_DPM_STATE_0_AT + ix, value);
पूर्ण

अटल व्योम trinity_program_घातer_level(काष्ठा radeon_device *rdev,
					काष्ठा trinity_pl *pl, u32 index)
अणु
	काष्ठा trinity_घातer_info *pi = trinity_get_pi(rdev);

	अगर (index >= SUMO_MAX_HARDWARE_POWERLEVELS)
		वापस;

	trinity_set_भागider_value(rdev, index, pl->sclk);
	trinity_set_vid(rdev, index, pl->vddc_index);
	trinity_set_ss_भागiders(rdev, index, pl->ss_भागider_index);
	trinity_set_ds_भागiders(rdev, index, pl->ds_भागider_index);
	trinity_set_allos_gnb_slow(rdev, index, pl->allow_gnb_slow);
	trinity_set_क्रमce_nbp_state(rdev, index, pl->क्रमce_nbp_state);
	trinity_set_display_wm(rdev, index, pl->display_wm);
	trinity_set_vce_wm(rdev, index, pl->vce_wm);
	trinity_set_at(rdev, index, pi->at[index]);
पूर्ण

अटल व्योम trinity_घातer_level_enable_disable(काष्ठा radeon_device *rdev,
					       u32 index, bool enable)
अणु
	u32 value;
	u32 ix = index * TRINITY_SIZखातापूर्ण_DPM_STATE_TABLE;

	value = RREG32_SMC(SMU_SCLK_DPM_STATE_0_CNTL_0 + ix);
	value &= ~STATE_VALID_MASK;
	अगर (enable)
		value |= STATE_VALID(1);
	WREG32_SMC(SMU_SCLK_DPM_STATE_0_CNTL_0 + ix, value);
पूर्ण

अटल bool trinity_dpm_enabled(काष्ठा radeon_device *rdev)
अणु
	अगर (RREG32_SMC(SMU_SCLK_DPM_CNTL) & SCLK_DPM_EN(1))
		वापस true;
	अन्यथा
		वापस false;
पूर्ण

अटल व्योम trinity_start_dpm(काष्ठा radeon_device *rdev)
अणु
	u32 value = RREG32_SMC(SMU_SCLK_DPM_CNTL);

	value &= ~(SCLK_DPM_EN_MASK | SCLK_DPM_BOOT_STATE_MASK | VOLTAGE_CHG_EN_MASK);
	value |= SCLK_DPM_EN(1) | SCLK_DPM_BOOT_STATE(0) | VOLTAGE_CHG_EN(1);
	WREG32_SMC(SMU_SCLK_DPM_CNTL, value);

	WREG32_P(GENERAL_PWRMGT, GLOBAL_PWRMGT_EN, ~GLOBAL_PWRMGT_EN);
	WREG32_P(CG_CG_VOLTAGE_CNTL, 0, ~EN);

	trinity_dpm_config(rdev, true);
पूर्ण

अटल व्योम trinity_रुको_क्रम_dpm_enabled(काष्ठा radeon_device *rdev)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < rdev->usec_समयout; i++) अणु
		अगर (RREG32(SCLK_PWRMGT_CNTL) & DYNAMIC_PM_EN)
			अवरोध;
		udelay(1);
	पूर्ण
	क्रम (i = 0; i < rdev->usec_समयout; i++) अणु
		अगर ((RREG32(TARGET_AND_CURRENT_PROखाता_INDEX) & TARGET_STATE_MASK) == 0)
			अवरोध;
		udelay(1);
	पूर्ण
	क्रम (i = 0; i < rdev->usec_समयout; i++) अणु
		अगर ((RREG32(TARGET_AND_CURRENT_PROखाता_INDEX) & CURRENT_STATE_MASK) == 0)
			अवरोध;
		udelay(1);
	पूर्ण
पूर्ण

अटल व्योम trinity_stop_dpm(काष्ठा radeon_device *rdev)
अणु
	u32 sclk_dpm_cntl;

	WREG32_P(CG_CG_VOLTAGE_CNTL, EN, ~EN);

	sclk_dpm_cntl = RREG32_SMC(SMU_SCLK_DPM_CNTL);
	sclk_dpm_cntl &= ~(SCLK_DPM_EN_MASK | VOLTAGE_CHG_EN_MASK);
	WREG32_SMC(SMU_SCLK_DPM_CNTL, sclk_dpm_cntl);

	trinity_dpm_config(rdev, false);
पूर्ण

अटल व्योम trinity_start_am(काष्ठा radeon_device *rdev)
अणु
	WREG32_P(SCLK_PWRMGT_CNTL, 0, ~(RESET_SCLK_CNT | RESET_BUSY_CNT));
पूर्ण

अटल व्योम trinity_reset_am(काष्ठा radeon_device *rdev)
अणु
	WREG32_P(SCLK_PWRMGT_CNTL, RESET_SCLK_CNT | RESET_BUSY_CNT,
		 ~(RESET_SCLK_CNT | RESET_BUSY_CNT));
पूर्ण

अटल व्योम trinity_रुको_क्रम_level_0(काष्ठा radeon_device *rdev)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < rdev->usec_समयout; i++) अणु
		अगर ((RREG32(TARGET_AND_CURRENT_PROखाता_INDEX) & CURRENT_STATE_MASK) == 0)
			अवरोध;
		udelay(1);
	पूर्ण
पूर्ण

अटल व्योम trinity_enable_घातer_level_0(काष्ठा radeon_device *rdev)
अणु
	trinity_घातer_level_enable_disable(rdev, 0, true);
पूर्ण

अटल व्योम trinity_क्रमce_level_0(काष्ठा radeon_device *rdev)
अणु
	trinity_dpm_क्रमce_state(rdev, 0);
पूर्ण

अटल व्योम trinity_unक्रमce_levels(काष्ठा radeon_device *rdev)
अणु
	trinity_dpm_no_क्रमced_level(rdev);
पूर्ण

अटल व्योम trinity_program_घातer_levels_0_to_n(काष्ठा radeon_device *rdev,
						काष्ठा radeon_ps *new_rps,
						काष्ठा radeon_ps *old_rps)
अणु
	काष्ठा trinity_ps *new_ps = trinity_get_ps(new_rps);
	काष्ठा trinity_ps *old_ps = trinity_get_ps(old_rps);
	u32 i;
	u32 n_current_state_levels = (old_ps == शून्य) ? 1 : old_ps->num_levels;

	क्रम (i = 0; i < new_ps->num_levels; i++) अणु
		trinity_program_घातer_level(rdev, &new_ps->levels[i], i);
		trinity_घातer_level_enable_disable(rdev, i, true);
	पूर्ण

	क्रम (i = new_ps->num_levels; i < n_current_state_levels; i++)
		trinity_घातer_level_enable_disable(rdev, i, false);
पूर्ण

अटल व्योम trinity_program_bootup_state(काष्ठा radeon_device *rdev)
अणु
	काष्ठा trinity_घातer_info *pi = trinity_get_pi(rdev);
	u32 i;

	trinity_program_घातer_level(rdev, &pi->boot_pl, 0);
	trinity_घातer_level_enable_disable(rdev, 0, true);

	क्रम (i = 1; i < 8; i++)
		trinity_घातer_level_enable_disable(rdev, i, false);
पूर्ण

अटल व्योम trinity_setup_uvd_घड़ी_प्रकारable(काष्ठा radeon_device *rdev,
					  काष्ठा radeon_ps *rps)
अणु
	काष्ठा trinity_ps *ps = trinity_get_ps(rps);
	u32 uvdstates = (ps->vclk_low_भागider |
			 ps->vclk_high_भागider << 8 |
			 ps->dclk_low_भागider << 16 |
			 ps->dclk_high_भागider << 24);

	WREG32_SMC(SMU_UVD_DPM_STATES, uvdstates);
पूर्ण

अटल व्योम trinity_setup_uvd_dpm_पूर्णांकerval(काष्ठा radeon_device *rdev,
					   u32 पूर्णांकerval)
अणु
	u32 p, u;
	u32 tp = RREG32_SMC(PM_TP);
	u32 val;
	u32 xclk = radeon_get_xclk(rdev);

	r600_calculate_u_and_p(पूर्णांकerval, xclk, 16, &p, &u);

	val = (p + tp - 1) / tp;

	WREG32_SMC(SMU_UVD_DPM_CNTL, val);
पूर्ण

अटल bool trinity_uvd_घड़ीs_zero(काष्ठा radeon_ps *rps)
अणु
	अगर ((rps->vclk == 0) && (rps->dclk == 0))
		वापस true;
	अन्यथा
		वापस false;
पूर्ण

अटल bool trinity_uvd_घड़ीs_equal(काष्ठा radeon_ps *rps1,
				     काष्ठा radeon_ps *rps2)
अणु
	काष्ठा trinity_ps *ps1 = trinity_get_ps(rps1);
	काष्ठा trinity_ps *ps2 = trinity_get_ps(rps2);

	अगर ((rps1->vclk == rps2->vclk) &&
	    (rps1->dclk == rps2->dclk) &&
	    (ps1->vclk_low_भागider == ps2->vclk_low_भागider) &&
	    (ps1->vclk_high_भागider == ps2->vclk_high_भागider) &&
	    (ps1->dclk_low_भागider == ps2->dclk_low_भागider) &&
	    (ps1->dclk_high_भागider == ps2->dclk_high_भागider))
		वापस true;
	अन्यथा
		वापस false;
पूर्ण

अटल व्योम trinity_setup_uvd_घड़ीs(काष्ठा radeon_device *rdev,
				     काष्ठा radeon_ps *new_rps,
				     काष्ठा radeon_ps *old_rps)
अणु
	काष्ठा trinity_घातer_info *pi = trinity_get_pi(rdev);

	अगर (pi->enable_gfx_घातer_gating) अणु
		trinity_gfx_घातergating_enable(rdev, false);
	पूर्ण

	अगर (pi->uvd_dpm) अणु
		अगर (trinity_uvd_घड़ीs_zero(new_rps) &&
		    !trinity_uvd_घड़ीs_zero(old_rps)) अणु
			trinity_setup_uvd_dpm_पूर्णांकerval(rdev, 0);
		पूर्ण अन्यथा अगर (!trinity_uvd_घड़ीs_zero(new_rps)) अणु
			trinity_setup_uvd_घड़ी_प्रकारable(rdev, new_rps);

			अगर (trinity_uvd_घड़ीs_zero(old_rps)) अणु
				u32 पंचांगp = RREG32(CG_MISC_REG);
				पंचांगp &= 0xfffffffd;
				WREG32(CG_MISC_REG, पंचांगp);

				radeon_set_uvd_घड़ीs(rdev, new_rps->vclk, new_rps->dclk);

				trinity_setup_uvd_dpm_पूर्णांकerval(rdev, 3000);
			पूर्ण
		पूर्ण
		trinity_uvd_dpm_config(rdev);
	पूर्ण अन्यथा अणु
		अगर (trinity_uvd_घड़ीs_zero(new_rps) ||
		    trinity_uvd_घड़ीs_equal(new_rps, old_rps))
			वापस;

		radeon_set_uvd_घड़ीs(rdev, new_rps->vclk, new_rps->dclk);
	पूर्ण

	अगर (pi->enable_gfx_घातer_gating) अणु
		trinity_gfx_घातergating_enable(rdev, true);
	पूर्ण
पूर्ण

अटल व्योम trinity_set_uvd_घड़ी_beक्रमe_set_eng_घड़ी(काष्ठा radeon_device *rdev,
						       काष्ठा radeon_ps *new_rps,
						       काष्ठा radeon_ps *old_rps)
अणु
	काष्ठा trinity_ps *new_ps = trinity_get_ps(new_rps);
	काष्ठा trinity_ps *current_ps = trinity_get_ps(new_rps);

	अगर (new_ps->levels[new_ps->num_levels - 1].sclk >=
	    current_ps->levels[current_ps->num_levels - 1].sclk)
		वापस;

	trinity_setup_uvd_घड़ीs(rdev, new_rps, old_rps);
पूर्ण

अटल व्योम trinity_set_uvd_घड़ी_after_set_eng_घड़ी(काष्ठा radeon_device *rdev,
						      काष्ठा radeon_ps *new_rps,
						      काष्ठा radeon_ps *old_rps)
अणु
	काष्ठा trinity_ps *new_ps = trinity_get_ps(new_rps);
	काष्ठा trinity_ps *current_ps = trinity_get_ps(old_rps);

	अगर (new_ps->levels[new_ps->num_levels - 1].sclk <
	    current_ps->levels[current_ps->num_levels - 1].sclk)
		वापस;

	trinity_setup_uvd_घड़ीs(rdev, new_rps, old_rps);
पूर्ण

अटल व्योम trinity_set_vce_घड़ी(काष्ठा radeon_device *rdev,
				  काष्ठा radeon_ps *new_rps,
				  काष्ठा radeon_ps *old_rps)
अणु
	अगर ((old_rps->evclk != new_rps->evclk) ||
	    (old_rps->ecclk != new_rps->ecclk)) अणु
		/* turn the घड़ीs on when encoding, off otherwise */
		अगर (new_rps->evclk || new_rps->ecclk)
			vce_v1_0_enable_mgcg(rdev, false);
		अन्यथा
			vce_v1_0_enable_mgcg(rdev, true);
		radeon_set_vce_घड़ीs(rdev, new_rps->evclk, new_rps->ecclk);
	पूर्ण
पूर्ण

अटल व्योम trinity_program_ttt(काष्ठा radeon_device *rdev)
अणु
	काष्ठा trinity_घातer_info *pi = trinity_get_pi(rdev);
	u32 value = RREG32_SMC(SMU_SCLK_DPM_TTT);

	value &= ~(HT_MASK | LT_MASK);
	value |= HT((pi->thermal_स्वतः_throttling + 49) * 8);
	value |= LT((pi->thermal_स्वतः_throttling + 49 - pi->sys_info.htc_hyst_lmt) * 8);
	WREG32_SMC(SMU_SCLK_DPM_TTT, value);
पूर्ण

अटल व्योम trinity_enable_att(काष्ठा radeon_device *rdev)
अणु
	u32 value = RREG32_SMC(SMU_SCLK_DPM_TT_CNTL);

	value &= ~SCLK_TT_EN_MASK;
	value |= SCLK_TT_EN(1);
	WREG32_SMC(SMU_SCLK_DPM_TT_CNTL, value);
पूर्ण

अटल व्योम trinity_program_sclk_dpm(काष्ठा radeon_device *rdev)
अणु
	u32 p, u;
	u32 tp = RREG32_SMC(PM_TP);
	u32 ni;
	u32 xclk = radeon_get_xclk(rdev);
	u32 value;

	r600_calculate_u_and_p(400, xclk, 16, &p, &u);

	ni = (p + tp - 1) / tp;

	value = RREG32_SMC(PM_I_CNTL_1);
	value &= ~SCLK_DPM_MASK;
	value |= SCLK_DPM(ni);
	WREG32_SMC(PM_I_CNTL_1, value);
पूर्ण

अटल पूर्णांक trinity_set_thermal_temperature_range(काष्ठा radeon_device *rdev,
						 पूर्णांक min_temp, पूर्णांक max_temp)
अणु
	पूर्णांक low_temp = 0 * 1000;
	पूर्णांक high_temp = 255 * 1000;

	अगर (low_temp < min_temp)
		low_temp = min_temp;
	अगर (high_temp > max_temp)
		high_temp = max_temp;
	अगर (high_temp < low_temp) अणु
		DRM_ERROR("invalid thermal range: %d - %d\n", low_temp, high_temp);
		वापस -EINVAL;
	पूर्ण

	WREG32_P(CG_THERMAL_INT_CTRL, DIG_THERM_INTH(49 + (high_temp / 1000)), ~DIG_THERM_INTH_MASK);
	WREG32_P(CG_THERMAL_INT_CTRL, DIG_THERM_INTL(49 + (low_temp / 1000)), ~DIG_THERM_INTL_MASK);

	rdev->pm.dpm.thermal.min_temp = low_temp;
	rdev->pm.dpm.thermal.max_temp = high_temp;

	वापस 0;
पूर्ण

अटल व्योम trinity_update_current_ps(काष्ठा radeon_device *rdev,
				      काष्ठा radeon_ps *rps)
अणु
	काष्ठा trinity_ps *new_ps = trinity_get_ps(rps);
	काष्ठा trinity_घातer_info *pi = trinity_get_pi(rdev);

	pi->current_rps = *rps;
	pi->current_ps = *new_ps;
	pi->current_rps.ps_priv = &pi->current_ps;
पूर्ण

अटल व्योम trinity_update_requested_ps(काष्ठा radeon_device *rdev,
					काष्ठा radeon_ps *rps)
अणु
	काष्ठा trinity_ps *new_ps = trinity_get_ps(rps);
	काष्ठा trinity_घातer_info *pi = trinity_get_pi(rdev);

	pi->requested_rps = *rps;
	pi->requested_ps = *new_ps;
	pi->requested_rps.ps_priv = &pi->requested_ps;
पूर्ण

व्योम trinity_dpm_enable_bapm(काष्ठा radeon_device *rdev, bool enable)
अणु
	काष्ठा trinity_घातer_info *pi = trinity_get_pi(rdev);

	अगर (pi->enable_bapm) अणु
		trinity_acquire_mutex(rdev);
		trinity_dpm_bapm_enable(rdev, enable);
		trinity_release_mutex(rdev);
	पूर्ण
पूर्ण

पूर्णांक trinity_dpm_enable(काष्ठा radeon_device *rdev)
अणु
	काष्ठा trinity_घातer_info *pi = trinity_get_pi(rdev);

	trinity_acquire_mutex(rdev);

	अगर (trinity_dpm_enabled(rdev)) अणु
		trinity_release_mutex(rdev);
		वापस -EINVAL;
	पूर्ण

	trinity_program_bootup_state(rdev);
	sumo_program_vc(rdev, 0x00C00033);
	trinity_start_am(rdev);
	अगर (pi->enable_स्वतः_thermal_throttling) अणु
		trinity_program_ttt(rdev);
		trinity_enable_att(rdev);
	पूर्ण
	trinity_program_sclk_dpm(rdev);
	trinity_start_dpm(rdev);
	trinity_रुको_क्रम_dpm_enabled(rdev);
	trinity_dpm_bapm_enable(rdev, false);
	trinity_release_mutex(rdev);

	trinity_update_current_ps(rdev, rdev->pm.dpm.boot_ps);

	वापस 0;
पूर्ण

पूर्णांक trinity_dpm_late_enable(काष्ठा radeon_device *rdev)
अणु
	पूर्णांक ret;

	trinity_acquire_mutex(rdev);
	trinity_enable_घड़ी_घातer_gating(rdev);

	अगर (rdev->irq.installed &&
	    r600_is_पूर्णांकernal_thermal_sensor(rdev->pm.पूर्णांक_thermal_type)) अणु
		ret = trinity_set_thermal_temperature_range(rdev, R600_TEMP_RANGE_MIN, R600_TEMP_RANGE_MAX);
		अगर (ret) अणु
			trinity_release_mutex(rdev);
			वापस ret;
		पूर्ण
		rdev->irq.dpm_thermal = true;
		radeon_irq_set(rdev);
	पूर्ण
	trinity_release_mutex(rdev);

	वापस 0;
पूर्ण

व्योम trinity_dpm_disable(काष्ठा radeon_device *rdev)
अणु
	trinity_acquire_mutex(rdev);
	अगर (!trinity_dpm_enabled(rdev)) अणु
		trinity_release_mutex(rdev);
		वापस;
	पूर्ण
	trinity_dpm_bapm_enable(rdev, false);
	trinity_disable_घड़ी_घातer_gating(rdev);
	sumo_clear_vc(rdev);
	trinity_रुको_क्रम_level_0(rdev);
	trinity_stop_dpm(rdev);
	trinity_reset_am(rdev);
	trinity_release_mutex(rdev);

	अगर (rdev->irq.installed &&
	    r600_is_पूर्णांकernal_thermal_sensor(rdev->pm.पूर्णांक_thermal_type)) अणु
		rdev->irq.dpm_thermal = false;
		radeon_irq_set(rdev);
	पूर्ण

	trinity_update_current_ps(rdev, rdev->pm.dpm.boot_ps);
पूर्ण

अटल व्योम trinity_get_min_sclk_भागider(काष्ठा radeon_device *rdev)
अणु
	काष्ठा trinity_घातer_info *pi = trinity_get_pi(rdev);

	pi->min_sclk_did =
		(RREG32_SMC(CC_SMU_MISC_FUSES) & MinSClkDid_MASK) >> MinSClkDid_SHIFT;
पूर्ण

अटल व्योम trinity_setup_nbp_sim(काष्ठा radeon_device *rdev,
				  काष्ठा radeon_ps *rps)
अणु
	काष्ठा trinity_घातer_info *pi = trinity_get_pi(rdev);
	काष्ठा trinity_ps *new_ps = trinity_get_ps(rps);
	u32 nbpsconfig;

	अगर (pi->sys_info.nb_dpm_enable) अणु
		nbpsconfig = RREG32_SMC(NB_PSTATE_CONFIG);
		nbpsconfig &= ~(Dpm0PgNbPsLo_MASK | Dpm0PgNbPsHi_MASK | DpmXNbPsLo_MASK | DpmXNbPsHi_MASK);
		nbpsconfig |= (Dpm0PgNbPsLo(new_ps->Dpm0PgNbPsLo) |
			       Dpm0PgNbPsHi(new_ps->Dpm0PgNbPsHi) |
			       DpmXNbPsLo(new_ps->DpmXNbPsLo) |
			       DpmXNbPsHi(new_ps->DpmXNbPsHi));
		WREG32_SMC(NB_PSTATE_CONFIG, nbpsconfig);
	पूर्ण
पूर्ण

पूर्णांक trinity_dpm_क्रमce_perक्रमmance_level(काष्ठा radeon_device *rdev,
					क्रमागत radeon_dpm_क्रमced_level level)
अणु
	काष्ठा trinity_घातer_info *pi = trinity_get_pi(rdev);
	काष्ठा radeon_ps *rps = &pi->current_rps;
	काष्ठा trinity_ps *ps = trinity_get_ps(rps);
	पूर्णांक i, ret;

	अगर (ps->num_levels <= 1)
		वापस 0;

	अगर (level == RADEON_DPM_FORCED_LEVEL_HIGH) अणु
		/* not supported by the hw */
		वापस -EINVAL;
	पूर्ण अन्यथा अगर (level == RADEON_DPM_FORCED_LEVEL_LOW) अणु
		ret = trinity_dpm_n_levels_disabled(rdev, ps->num_levels - 1);
		अगर (ret)
			वापस ret;
	पूर्ण अन्यथा अणु
		क्रम (i = 0; i < ps->num_levels; i++) अणु
			ret = trinity_dpm_n_levels_disabled(rdev, 0);
			अगर (ret)
				वापस ret;
		पूर्ण
	पूर्ण

	rdev->pm.dpm.क्रमced_level = level;

	वापस 0;
पूर्ण

पूर्णांक trinity_dpm_pre_set_घातer_state(काष्ठा radeon_device *rdev)
अणु
	काष्ठा trinity_घातer_info *pi = trinity_get_pi(rdev);
	काष्ठा radeon_ps requested_ps = *rdev->pm.dpm.requested_ps;
	काष्ठा radeon_ps *new_ps = &requested_ps;

	trinity_update_requested_ps(rdev, new_ps);

	trinity_apply_state_adjust_rules(rdev,
					 &pi->requested_rps,
					 &pi->current_rps);

	वापस 0;
पूर्ण

पूर्णांक trinity_dpm_set_घातer_state(काष्ठा radeon_device *rdev)
अणु
	काष्ठा trinity_घातer_info *pi = trinity_get_pi(rdev);
	काष्ठा radeon_ps *new_ps = &pi->requested_rps;
	काष्ठा radeon_ps *old_ps = &pi->current_rps;

	trinity_acquire_mutex(rdev);
	अगर (pi->enable_dpm) अणु
		अगर (pi->enable_bapm)
			trinity_dpm_bapm_enable(rdev, rdev->pm.dpm.ac_घातer);
		trinity_set_uvd_घड़ी_beक्रमe_set_eng_घड़ी(rdev, new_ps, old_ps);
		trinity_enable_घातer_level_0(rdev);
		trinity_क्रमce_level_0(rdev);
		trinity_रुको_क्रम_level_0(rdev);
		trinity_setup_nbp_sim(rdev, new_ps);
		trinity_program_घातer_levels_0_to_n(rdev, new_ps, old_ps);
		trinity_क्रमce_level_0(rdev);
		trinity_unक्रमce_levels(rdev);
		trinity_set_uvd_घड़ी_after_set_eng_घड़ी(rdev, new_ps, old_ps);
		trinity_set_vce_घड़ी(rdev, new_ps, old_ps);
	पूर्ण
	trinity_release_mutex(rdev);

	वापस 0;
पूर्ण

व्योम trinity_dpm_post_set_घातer_state(काष्ठा radeon_device *rdev)
अणु
	काष्ठा trinity_घातer_info *pi = trinity_get_pi(rdev);
	काष्ठा radeon_ps *new_ps = &pi->requested_rps;

	trinity_update_current_ps(rdev, new_ps);
पूर्ण

व्योम trinity_dpm_setup_asic(काष्ठा radeon_device *rdev)
अणु
	trinity_acquire_mutex(rdev);
	sumo_program_sstp(rdev);
	sumo_take_smu_control(rdev, true);
	trinity_get_min_sclk_भागider(rdev);
	trinity_release_mutex(rdev);
पूर्ण

#अगर 0
व्योम trinity_dpm_reset_asic(काष्ठा radeon_device *rdev)
अणु
	काष्ठा trinity_घातer_info *pi = trinity_get_pi(rdev);

	trinity_acquire_mutex(rdev);
	अगर (pi->enable_dpm) अणु
		trinity_enable_घातer_level_0(rdev);
		trinity_क्रमce_level_0(rdev);
		trinity_रुको_क्रम_level_0(rdev);
		trinity_program_bootup_state(rdev);
		trinity_क्रमce_level_0(rdev);
		trinity_unक्रमce_levels(rdev);
	पूर्ण
	trinity_release_mutex(rdev);
पूर्ण
#पूर्ण_अगर

अटल u16 trinity_convert_voltage_index_to_value(काष्ठा radeon_device *rdev,
						  u32 vid_2bit)
अणु
	काष्ठा trinity_घातer_info *pi = trinity_get_pi(rdev);
	u32 vid_7bit = sumo_convert_vid2_to_vid7(rdev, &pi->sys_info.vid_mapping_table, vid_2bit);
	u32 svi_mode = (RREG32_SMC(PM_CONFIG) & SVI_Mode) ? 1 : 0;
	u32 step = (svi_mode == 0) ? 1250 : 625;
	u32 delta = vid_7bit * step + 50;

	अगर (delta > 155000)
		वापस 0;

	वापस (155000 - delta) / 100;
पूर्ण

अटल व्योम trinity_patch_boot_state(काष्ठा radeon_device *rdev,
				     काष्ठा trinity_ps *ps)
अणु
	काष्ठा trinity_घातer_info *pi = trinity_get_pi(rdev);

	ps->num_levels = 1;
	ps->nbps_flags = 0;
	ps->bapm_flags = 0;
	ps->levels[0] = pi->boot_pl;
पूर्ण

अटल u8 trinity_calculate_vce_wm(काष्ठा radeon_device *rdev, u32 sclk)
अणु
	अगर (sclk < 20000)
		वापस 1;
	वापस 0;
पूर्ण

अटल व्योम trinity_स्थिरruct_boot_state(काष्ठा radeon_device *rdev)
अणु
	काष्ठा trinity_घातer_info *pi = trinity_get_pi(rdev);

	pi->boot_pl.sclk = pi->sys_info.bootup_sclk;
	pi->boot_pl.vddc_index = pi->sys_info.bootup_nb_voltage_index;
	pi->boot_pl.ds_भागider_index = 0;
	pi->boot_pl.ss_भागider_index = 0;
	pi->boot_pl.allow_gnb_slow = 1;
	pi->boot_pl.क्रमce_nbp_state = 0;
	pi->boot_pl.display_wm = 0;
	pi->boot_pl.vce_wm = 0;
	pi->current_ps.num_levels = 1;
	pi->current_ps.levels[0] = pi->boot_pl;
पूर्ण

अटल u8 trinity_get_sleep_भागider_id_from_घड़ी(काष्ठा radeon_device *rdev,
						  u32 sclk, u32 min_sclk_in_sr)
अणु
	काष्ठा trinity_घातer_info *pi = trinity_get_pi(rdev);
	u32 i;
	u32 temp;
	u32 min = (min_sclk_in_sr > TRINITY_MINIMUM_ENGINE_CLOCK) ?
		min_sclk_in_sr : TRINITY_MINIMUM_ENGINE_CLOCK;

	अगर (sclk < min)
		वापस 0;

	अगर (!pi->enable_sclk_ds)
		वापस 0;

	क्रम (i = TRINITY_MAX_DEEPSLEEP_DIVIDER_ID;  ; i--) अणु
		temp = sclk / sumo_get_sleep_भागider_from_id(i);
		अगर (temp >= min || i == 0)
			अवरोध;
	पूर्ण

	वापस (u8)i;
पूर्ण

अटल u32 trinity_get_valid_engine_घड़ी(काष्ठा radeon_device *rdev,
					  u32 lower_limit)
अणु
	काष्ठा trinity_घातer_info *pi = trinity_get_pi(rdev);
	u32 i;

	क्रम (i = 0; i < pi->sys_info.sclk_voltage_mapping_table.num_max_dpm_entries; i++) अणु
		अगर (pi->sys_info.sclk_voltage_mapping_table.entries[i].sclk_frequency >= lower_limit)
			वापस pi->sys_info.sclk_voltage_mapping_table.entries[i].sclk_frequency;
	पूर्ण

	अगर (i == pi->sys_info.sclk_voltage_mapping_table.num_max_dpm_entries)
		DRM_ERROR("engine clock out of range!");

	वापस 0;
पूर्ण

अटल व्योम trinity_patch_thermal_state(काष्ठा radeon_device *rdev,
					काष्ठा trinity_ps *ps,
					काष्ठा trinity_ps *current_ps)
अणु
	काष्ठा trinity_घातer_info *pi = trinity_get_pi(rdev);
	u32 sclk_in_sr = pi->sys_info.min_sclk; /* ??? */
	u32 current_vddc;
	u32 current_sclk;
	u32 current_index = 0;

	अगर (current_ps) अणु
		current_vddc = current_ps->levels[current_index].vddc_index;
		current_sclk = current_ps->levels[current_index].sclk;
	पूर्ण अन्यथा अणु
		current_vddc = pi->boot_pl.vddc_index;
		current_sclk = pi->boot_pl.sclk;
	पूर्ण

	ps->levels[0].vddc_index = current_vddc;

	अगर (ps->levels[0].sclk > current_sclk)
		ps->levels[0].sclk = current_sclk;

	ps->levels[0].ds_भागider_index =
		trinity_get_sleep_भागider_id_from_घड़ी(rdev, ps->levels[0].sclk, sclk_in_sr);
	ps->levels[0].ss_भागider_index = ps->levels[0].ds_भागider_index;
	ps->levels[0].allow_gnb_slow = 1;
	ps->levels[0].क्रमce_nbp_state = 0;
	ps->levels[0].display_wm = 0;
	ps->levels[0].vce_wm =
		trinity_calculate_vce_wm(rdev, ps->levels[0].sclk);
पूर्ण

अटल u8 trinity_calculate_display_wm(काष्ठा radeon_device *rdev,
				       काष्ठा trinity_ps *ps, u32 index)
अणु
	अगर (ps == शून्य || ps->num_levels <= 1)
		वापस 0;
	अन्यथा अगर (ps->num_levels == 2) अणु
		अगर (index == 0)
			वापस 0;
		अन्यथा
			वापस 1;
	पूर्ण अन्यथा अणु
		अगर (index == 0)
			वापस 0;
		अन्यथा अगर (ps->levels[index].sclk < 30000)
			वापस 0;
		अन्यथा
			वापस 1;
	पूर्ण
पूर्ण

अटल u32 trinity_get_uvd_घड़ी_index(काष्ठा radeon_device *rdev,
				       काष्ठा radeon_ps *rps)
अणु
	काष्ठा trinity_घातer_info *pi = trinity_get_pi(rdev);
	u32 i = 0;

	क्रम (i = 0; i < 4; i++) अणु
		अगर ((rps->vclk == pi->sys_info.uvd_घड़ी_प्रकारable_entries[i].vclk) &&
		    (rps->dclk == pi->sys_info.uvd_घड़ी_प्रकारable_entries[i].dclk))
		    अवरोध;
	पूर्ण

	अगर (i >= 4) अणु
		DRM_ERROR("UVD clock index not found!\n");
		i = 3;
	पूर्ण
	वापस i;
पूर्ण

अटल व्योम trinity_adjust_uvd_state(काष्ठा radeon_device *rdev,
				     काष्ठा radeon_ps *rps)
अणु
	काष्ठा trinity_ps *ps = trinity_get_ps(rps);
	काष्ठा trinity_घातer_info *pi = trinity_get_pi(rdev);
	u32 high_index = 0;
	u32 low_index = 0;

	अगर (pi->uvd_dpm && r600_is_uvd_state(rps->class, rps->class2)) अणु
		high_index = trinity_get_uvd_घड़ी_index(rdev, rps);

		चयन(high_index) अणु
		हाल 3:
		हाल 2:
			low_index = 1;
			अवरोध;
		हाल 1:
		हाल 0:
		शेष:
			low_index = 0;
			अवरोध;
		पूर्ण

		ps->vclk_low_भागider =
			pi->sys_info.uvd_घड़ी_प्रकारable_entries[high_index].vclk_did;
		ps->dclk_low_भागider =
			pi->sys_info.uvd_घड़ी_प्रकारable_entries[high_index].dclk_did;
		ps->vclk_high_भागider =
			pi->sys_info.uvd_घड़ी_प्रकारable_entries[low_index].vclk_did;
		ps->dclk_high_भागider =
			pi->sys_info.uvd_घड़ी_प्रकारable_entries[low_index].dclk_did;
	पूर्ण
पूर्ण

अटल पूर्णांक trinity_get_vce_घड़ी_voltage(काष्ठा radeon_device *rdev,
					 u32 evclk, u32 ecclk, u16 *voltage)
अणु
	u32 i;
	पूर्णांक ret = -EINVAL;
	काष्ठा radeon_vce_घड़ी_voltage_dependency_table *table =
		&rdev->pm.dpm.dyn_state.vce_घड़ी_voltage_dependency_table;

	अगर (((evclk == 0) && (ecclk == 0)) ||
	    (table && (table->count == 0))) अणु
		*voltage = 0;
		वापस 0;
	पूर्ण

	क्रम (i = 0; i < table->count; i++) अणु
		अगर ((evclk <= table->entries[i].evclk) &&
		    (ecclk <= table->entries[i].ecclk)) अणु
			*voltage = table->entries[i].v;
			ret = 0;
			अवरोध;
		पूर्ण
	पूर्ण

	/* अगर no match वापस the highest voltage */
	अगर (ret)
		*voltage = table->entries[table->count - 1].v;

	वापस ret;
पूर्ण

अटल व्योम trinity_apply_state_adjust_rules(काष्ठा radeon_device *rdev,
					     काष्ठा radeon_ps *new_rps,
					     काष्ठा radeon_ps *old_rps)
अणु
	काष्ठा trinity_ps *ps = trinity_get_ps(new_rps);
	काष्ठा trinity_ps *current_ps = trinity_get_ps(old_rps);
	काष्ठा trinity_घातer_info *pi = trinity_get_pi(rdev);
	u32 min_voltage = 0; /* ??? */
	u32 min_sclk = pi->sys_info.min_sclk; /* XXX check against disp reqs */
	u32 sclk_in_sr = pi->sys_info.min_sclk; /* ??? */
	u32 i;
	u16 min_vce_voltage;
	bool क्रमce_high;
	u32 num_active_displays = rdev->pm.dpm.new_active_crtc_count;

	अगर (new_rps->class & ATOM_PPLIB_CLASSIFICATION_THERMAL)
		वापस trinity_patch_thermal_state(rdev, ps, current_ps);

	trinity_adjust_uvd_state(rdev, new_rps);

	अगर (new_rps->vce_active) अणु
		new_rps->evclk = rdev->pm.dpm.vce_states[rdev->pm.dpm.vce_level].evclk;
		new_rps->ecclk = rdev->pm.dpm.vce_states[rdev->pm.dpm.vce_level].ecclk;
	पूर्ण अन्यथा अणु
		new_rps->evclk = 0;
		new_rps->ecclk = 0;
	पूर्ण

	क्रम (i = 0; i < ps->num_levels; i++) अणु
		अगर (ps->levels[i].vddc_index < min_voltage)
			ps->levels[i].vddc_index = min_voltage;

		अगर (ps->levels[i].sclk < min_sclk)
			ps->levels[i].sclk =
				trinity_get_valid_engine_घड़ी(rdev, min_sclk);

		/* patch in vce limits */
		अगर (new_rps->vce_active) अणु
			/* sclk */
			अगर (ps->levels[i].sclk < rdev->pm.dpm.vce_states[rdev->pm.dpm.vce_level].sclk)
				ps->levels[i].sclk = rdev->pm.dpm.vce_states[rdev->pm.dpm.vce_level].sclk;
			/* vddc */
			trinity_get_vce_घड़ी_voltage(rdev, new_rps->evclk, new_rps->ecclk, &min_vce_voltage);
			अगर (ps->levels[i].vddc_index < min_vce_voltage)
				ps->levels[i].vddc_index = min_vce_voltage;
		पूर्ण

		ps->levels[i].ds_भागider_index =
			sumo_get_sleep_भागider_id_from_घड़ी(rdev, ps->levels[i].sclk, sclk_in_sr);

		ps->levels[i].ss_भागider_index = ps->levels[i].ds_भागider_index;

		ps->levels[i].allow_gnb_slow = 1;
		ps->levels[i].क्रमce_nbp_state = 0;
		ps->levels[i].display_wm =
			trinity_calculate_display_wm(rdev, ps, i);
		ps->levels[i].vce_wm =
			trinity_calculate_vce_wm(rdev, ps->levels[0].sclk);
	पूर्ण

	अगर ((new_rps->class & (ATOM_PPLIB_CLASSIFICATION_HDSTATE | ATOM_PPLIB_CLASSIFICATION_SDSTATE)) ||
	    ((new_rps->class & ATOM_PPLIB_CLASSIFICATION_UI_MASK) == ATOM_PPLIB_CLASSIFICATION_UI_BATTERY))
		ps->bapm_flags |= TRINITY_POWERSTATE_FLAGS_BAPM_DISABLE;

	अगर (pi->sys_info.nb_dpm_enable) अणु
		ps->Dpm0PgNbPsLo = 0x1;
		ps->Dpm0PgNbPsHi = 0x0;
		ps->DpmXNbPsLo = 0x2;
		ps->DpmXNbPsHi = 0x1;

		अगर ((new_rps->class & (ATOM_PPLIB_CLASSIFICATION_HDSTATE | ATOM_PPLIB_CLASSIFICATION_SDSTATE)) ||
		    ((new_rps->class & ATOM_PPLIB_CLASSIFICATION_UI_MASK) == ATOM_PPLIB_CLASSIFICATION_UI_BATTERY)) अणु
			क्रमce_high = ((new_rps->class & ATOM_PPLIB_CLASSIFICATION_HDSTATE) ||
				      ((new_rps->class & ATOM_PPLIB_CLASSIFICATION_SDSTATE) &&
				       (pi->sys_info.uma_channel_number == 1)));
			क्रमce_high = (num_active_displays >= 3) || क्रमce_high;
			ps->Dpm0PgNbPsLo = क्रमce_high ? 0x2 : 0x3;
			ps->Dpm0PgNbPsHi = 0x1;
			ps->DpmXNbPsLo = क्रमce_high ? 0x2 : 0x3;
			ps->DpmXNbPsHi = 0x2;
			ps->levels[ps->num_levels - 1].allow_gnb_slow = 0;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम trinity_cleanup_asic(काष्ठा radeon_device *rdev)
अणु
	sumo_take_smu_control(rdev, false);
पूर्ण

#अगर 0
अटल व्योम trinity_pre_display_configuration_change(काष्ठा radeon_device *rdev)
अणु
	काष्ठा trinity_घातer_info *pi = trinity_get_pi(rdev);

	अगर (pi->voltage_drop_in_dce)
		trinity_dce_enable_voltage_adjusपंचांगent(rdev, false);
पूर्ण
#पूर्ण_अगर

अटल व्योम trinity_add_dccac_value(काष्ठा radeon_device *rdev)
अणु
	u32 gpu_cac_avrg_cntl_winकरोw_size;
	u32 num_active_displays = rdev->pm.dpm.new_active_crtc_count;
	u64 disp_clk = rdev->घड़ी.शेष_dispclk / 100;
	u32 dc_cac_value;

	gpu_cac_avrg_cntl_winकरोw_size =
		(RREG32_SMC(GPU_CAC_AVRG_CNTL) & WINDOW_SIZE_MASK) >> WINDOW_SIZE_SHIFT;

	dc_cac_value = (u32)((14213 * disp_clk * disp_clk * (u64)num_active_displays) >>
			     (32 - gpu_cac_avrg_cntl_winकरोw_size));

	WREG32_SMC(DC_CAC_VALUE, dc_cac_value);
पूर्ण

व्योम trinity_dpm_display_configuration_changed(काष्ठा radeon_device *rdev)
अणु
	काष्ठा trinity_घातer_info *pi = trinity_get_pi(rdev);

	अगर (pi->voltage_drop_in_dce)
		trinity_dce_enable_voltage_adjusपंचांगent(rdev, true);
	trinity_add_dccac_value(rdev);
पूर्ण

जोड़ घातer_info अणु
	काष्ठा _ATOM_POWERPLAY_INFO info;
	काष्ठा _ATOM_POWERPLAY_INFO_V2 info_2;
	काष्ठा _ATOM_POWERPLAY_INFO_V3 info_3;
	काष्ठा _ATOM_PPLIB_POWERPLAYTABLE pplib;
	काष्ठा _ATOM_PPLIB_POWERPLAYTABLE2 pplib2;
	काष्ठा _ATOM_PPLIB_POWERPLAYTABLE3 pplib3;
पूर्ण;

जोड़ pplib_घड़ी_info अणु
	काष्ठा _ATOM_PPLIB_R600_CLOCK_INFO r600;
	काष्ठा _ATOM_PPLIB_RS780_CLOCK_INFO rs780;
	काष्ठा _ATOM_PPLIB_EVERGREEN_CLOCK_INFO evergreen;
	काष्ठा _ATOM_PPLIB_SUMO_CLOCK_INFO sumo;
पूर्ण;

जोड़ pplib_घातer_state अणु
	काष्ठा _ATOM_PPLIB_STATE v1;
	काष्ठा _ATOM_PPLIB_STATE_V2 v2;
पूर्ण;

अटल व्योम trinity_parse_pplib_non_घड़ी_info(काष्ठा radeon_device *rdev,
					       काष्ठा radeon_ps *rps,
					       काष्ठा _ATOM_PPLIB_NONCLOCK_INFO *non_घड़ी_info,
					       u8 table_rev)
अणु
	काष्ठा trinity_ps *ps = trinity_get_ps(rps);

	rps->caps = le32_to_cpu(non_घड़ी_info->ulCapsAndSettings);
	rps->class = le16_to_cpu(non_घड़ी_info->usClassअगरication);
	rps->class2 = le16_to_cpu(non_घड़ी_info->usClassअगरication2);

	अगर (ATOM_PPLIB_NONCLOCKINFO_VER1 < table_rev) अणु
		rps->vclk = le32_to_cpu(non_घड़ी_info->ulVCLK);
		rps->dclk = le32_to_cpu(non_घड़ी_info->ulDCLK);
	पूर्ण अन्यथा अणु
		rps->vclk = 0;
		rps->dclk = 0;
	पूर्ण

	अगर (rps->class & ATOM_PPLIB_CLASSIFICATION_BOOT) अणु
		rdev->pm.dpm.boot_ps = rps;
		trinity_patch_boot_state(rdev, ps);
	पूर्ण
	अगर (rps->class & ATOM_PPLIB_CLASSIFICATION_UVDSTATE)
		rdev->pm.dpm.uvd_ps = rps;
पूर्ण

अटल व्योम trinity_parse_pplib_घड़ी_info(काष्ठा radeon_device *rdev,
					   काष्ठा radeon_ps *rps, पूर्णांक index,
					   जोड़ pplib_घड़ी_info *घड़ी_info)
अणु
	काष्ठा trinity_घातer_info *pi = trinity_get_pi(rdev);
	काष्ठा trinity_ps *ps = trinity_get_ps(rps);
	काष्ठा trinity_pl *pl = &ps->levels[index];
	u32 sclk;

	sclk = le16_to_cpu(घड़ी_info->sumo.usEngineClockLow);
	sclk |= घड़ी_info->sumo.ucEngineClockHigh << 16;
	pl->sclk = sclk;
	pl->vddc_index = घड़ी_info->sumo.vddcIndex;

	ps->num_levels = index + 1;

	अगर (pi->enable_sclk_ds) अणु
		pl->ds_भागider_index = 5;
		pl->ss_भागider_index = 5;
	पूर्ण
पूर्ण

अटल पूर्णांक trinity_parse_घातer_table(काष्ठा radeon_device *rdev)
अणु
	काष्ठा radeon_mode_info *mode_info = &rdev->mode_info;
	काष्ठा _ATOM_PPLIB_NONCLOCK_INFO *non_घड़ी_info;
	जोड़ pplib_घातer_state *घातer_state;
	पूर्णांक i, j, k, non_घड़ी_array_index, घड़ी_array_index;
	जोड़ pplib_घड़ी_info *घड़ी_info;
	काष्ठा _StateArray *state_array;
	काष्ठा _ClockInfoArray *घड़ी_info_array;
	काष्ठा _NonClockInfoArray *non_घड़ी_info_array;
	जोड़ घातer_info *घातer_info;
	पूर्णांक index = GetIndexIntoMasterTable(DATA, PowerPlayInfo);
	u16 data_offset;
	u8 frev, crev;
	u8 *घातer_state_offset;
	काष्ठा sumo_ps *ps;

	अगर (!atom_parse_data_header(mode_info->atom_context, index, शून्य,
				   &frev, &crev, &data_offset))
		वापस -EINVAL;
	घातer_info = (जोड़ घातer_info *)(mode_info->atom_context->bios + data_offset);

	state_array = (काष्ठा _StateArray *)
		(mode_info->atom_context->bios + data_offset +
		 le16_to_cpu(घातer_info->pplib.usStateArrayOffset));
	घड़ी_info_array = (काष्ठा _ClockInfoArray *)
		(mode_info->atom_context->bios + data_offset +
		 le16_to_cpu(घातer_info->pplib.usClockInfoArrayOffset));
	non_घड़ी_info_array = (काष्ठा _NonClockInfoArray *)
		(mode_info->atom_context->bios + data_offset +
		 le16_to_cpu(घातer_info->pplib.usNonClockInfoArrayOffset));

	rdev->pm.dpm.ps = kसुस्मृति(state_array->ucNumEntries,
				  माप(काष्ठा radeon_ps),
				  GFP_KERNEL);
	अगर (!rdev->pm.dpm.ps)
		वापस -ENOMEM;
	घातer_state_offset = (u8 *)state_array->states;
	क्रम (i = 0; i < state_array->ucNumEntries; i++) अणु
		u8 *idx;
		घातer_state = (जोड़ pplib_घातer_state *)घातer_state_offset;
		non_घड़ी_array_index = घातer_state->v2.nonClockInfoIndex;
		non_घड़ी_info = (काष्ठा _ATOM_PPLIB_NONCLOCK_INFO *)
			&non_घड़ी_info_array->nonClockInfo[non_घड़ी_array_index];
		अगर (!rdev->pm.घातer_state[i].घड़ी_info)
			वापस -EINVAL;
		ps = kzalloc(माप(काष्ठा sumo_ps), GFP_KERNEL);
		अगर (ps == शून्य) अणु
			kमुक्त(rdev->pm.dpm.ps);
			वापस -ENOMEM;
		पूर्ण
		rdev->pm.dpm.ps[i].ps_priv = ps;
		k = 0;
		idx = (u8 *)&घातer_state->v2.घड़ीInfoIndex[0];
		क्रम (j = 0; j < घातer_state->v2.ucNumDPMLevels; j++) अणु
			घड़ी_array_index = idx[j];
			अगर (घड़ी_array_index >= घड़ी_info_array->ucNumEntries)
				जारी;
			अगर (k >= SUMO_MAX_HARDWARE_POWERLEVELS)
				अवरोध;
			घड़ी_info = (जोड़ pplib_घड़ी_info *)
				((u8 *)&घड़ी_info_array->घड़ीInfo[0] +
				 (घड़ी_array_index * घड़ी_info_array->ucEntrySize));
			trinity_parse_pplib_घड़ी_info(rdev,
						       &rdev->pm.dpm.ps[i], k,
						       घड़ी_info);
			k++;
		पूर्ण
		trinity_parse_pplib_non_घड़ी_info(rdev, &rdev->pm.dpm.ps[i],
						   non_घड़ी_info,
						   non_घड़ी_info_array->ucEntrySize);
		घातer_state_offset += 2 + घातer_state->v2.ucNumDPMLevels;
	पूर्ण
	rdev->pm.dpm.num_ps = state_array->ucNumEntries;

	/* fill in the vce घातer states */
	क्रम (i = 0; i < RADEON_MAX_VCE_LEVELS; i++) अणु
		u32 sclk;
		घड़ी_array_index = rdev->pm.dpm.vce_states[i].clk_idx;
		घड़ी_info = (जोड़ pplib_घड़ी_info *)
			&घड़ी_info_array->घड़ीInfo[घड़ी_array_index * घड़ी_info_array->ucEntrySize];
		sclk = le16_to_cpu(घड़ी_info->sumo.usEngineClockLow);
		sclk |= घड़ी_info->sumo.ucEngineClockHigh << 16;
		rdev->pm.dpm.vce_states[i].sclk = sclk;
		rdev->pm.dpm.vce_states[i].mclk = 0;
	पूर्ण

	वापस 0;
पूर्ण

जोड़ igp_info अणु
	काष्ठा _ATOM_INTEGRATED_SYSTEM_INFO info;
	काष्ठा _ATOM_INTEGRATED_SYSTEM_INFO_V2 info_2;
	काष्ठा _ATOM_INTEGRATED_SYSTEM_INFO_V5 info_5;
	काष्ठा _ATOM_INTEGRATED_SYSTEM_INFO_V6 info_6;
	काष्ठा _ATOM_INTEGRATED_SYSTEM_INFO_V1_7 info_7;
पूर्ण;

अटल u32 trinity_convert_did_to_freq(काष्ठा radeon_device *rdev, u8 did)
अणु
	काष्ठा trinity_घातer_info *pi = trinity_get_pi(rdev);
	u32 भागider;

	अगर (did >= 8 && did <= 0x3f)
		भागider = did * 25;
	अन्यथा अगर (did > 0x3f && did <= 0x5f)
		भागider = (did - 64) * 50 + 1600;
	अन्यथा अगर (did > 0x5f && did <= 0x7e)
		भागider = (did - 96) * 100 + 3200;
	अन्यथा अगर (did == 0x7f)
		भागider = 128 * 100;
	अन्यथा
		वापस 10000;

	वापस ((pi->sys_info.dentist_vco_freq * 100) + (भागider - 1)) / भागider;
पूर्ण

अटल पूर्णांक trinity_parse_sys_info_table(काष्ठा radeon_device *rdev)
अणु
	काष्ठा trinity_घातer_info *pi = trinity_get_pi(rdev);
	काष्ठा radeon_mode_info *mode_info = &rdev->mode_info;
	पूर्णांक index = GetIndexIntoMasterTable(DATA, IntegratedSystemInfo);
	जोड़ igp_info *igp_info;
	u8 frev, crev;
	u16 data_offset;
	पूर्णांक i;

	अगर (atom_parse_data_header(mode_info->atom_context, index, शून्य,
				   &frev, &crev, &data_offset)) अणु
		igp_info = (जोड़ igp_info *)(mode_info->atom_context->bios +
					      data_offset);

		अगर (crev != 7) अणु
			DRM_ERROR("Unsupported IGP table: %d %d\n", frev, crev);
			वापस -EINVAL;
		पूर्ण
		pi->sys_info.bootup_sclk = le32_to_cpu(igp_info->info_7.ulBootUpEngineClock);
		pi->sys_info.min_sclk = le32_to_cpu(igp_info->info_7.ulMinEngineClock);
		pi->sys_info.bootup_uma_clk = le32_to_cpu(igp_info->info_7.ulBootUpUMAClock);
		pi->sys_info.dentist_vco_freq = le32_to_cpu(igp_info->info_7.ulDentistVCOFreq);
		pi->sys_info.bootup_nb_voltage_index =
			le16_to_cpu(igp_info->info_7.usBootUpNBVoltage);
		अगर (igp_info->info_7.ucHtcTmpLmt == 0)
			pi->sys_info.htc_पंचांगp_lmt = 203;
		अन्यथा
			pi->sys_info.htc_पंचांगp_lmt = igp_info->info_7.ucHtcTmpLmt;
		अगर (igp_info->info_7.ucHtcHystLmt == 0)
			pi->sys_info.htc_hyst_lmt = 5;
		अन्यथा
			pi->sys_info.htc_hyst_lmt = igp_info->info_7.ucHtcHystLmt;
		अगर (pi->sys_info.htc_पंचांगp_lmt <= pi->sys_info.htc_hyst_lmt) अणु
			DRM_ERROR("The htcTmpLmt should be larger than htcHystLmt.\n");
		पूर्ण

		अगर (pi->enable_nbps_policy)
			pi->sys_info.nb_dpm_enable = igp_info->info_7.ucNBDPMEnable;
		अन्यथा
			pi->sys_info.nb_dpm_enable = 0;

		क्रम (i = 0; i < TRINITY_NUM_NBPSTATES; i++) अणु
			pi->sys_info.nbp_mclk[i] = le32_to_cpu(igp_info->info_7.ulNbpStateMemclkFreq[i]);
			pi->sys_info.nbp_nclk[i] = le32_to_cpu(igp_info->info_7.ulNbpStateNClkFreq[i]);
		पूर्ण

		pi->sys_info.nbp_voltage_index[0] = le16_to_cpu(igp_info->info_7.usNBP0Voltage);
		pi->sys_info.nbp_voltage_index[1] = le16_to_cpu(igp_info->info_7.usNBP1Voltage);
		pi->sys_info.nbp_voltage_index[2] = le16_to_cpu(igp_info->info_7.usNBP2Voltage);
		pi->sys_info.nbp_voltage_index[3] = le16_to_cpu(igp_info->info_7.usNBP3Voltage);

		अगर (!pi->sys_info.nb_dpm_enable) अणु
			क्रम (i = 1; i < TRINITY_NUM_NBPSTATES; i++) अणु
				pi->sys_info.nbp_mclk[i] = pi->sys_info.nbp_mclk[0];
				pi->sys_info.nbp_nclk[i] = pi->sys_info.nbp_nclk[0];
				pi->sys_info.nbp_voltage_index[i] = pi->sys_info.nbp_voltage_index[0];
			पूर्ण
		पूर्ण

		pi->sys_info.uma_channel_number = igp_info->info_7.ucUMAChannelNumber;

		sumo_स्थिरruct_sclk_voltage_mapping_table(rdev,
							  &pi->sys_info.sclk_voltage_mapping_table,
							  igp_info->info_7.sAvail_SCLK);
		sumo_स्थिरruct_vid_mapping_table(rdev, &pi->sys_info.vid_mapping_table,
						 igp_info->info_7.sAvail_SCLK);

		pi->sys_info.uvd_घड़ी_प्रकारable_entries[0].vclk_did =
			igp_info->info_7.ucDPMState0VclkFid;
		pi->sys_info.uvd_घड़ी_प्रकारable_entries[1].vclk_did =
			igp_info->info_7.ucDPMState1VclkFid;
		pi->sys_info.uvd_घड़ी_प्रकारable_entries[2].vclk_did =
			igp_info->info_7.ucDPMState2VclkFid;
		pi->sys_info.uvd_घड़ी_प्रकारable_entries[3].vclk_did =
			igp_info->info_7.ucDPMState3VclkFid;

		pi->sys_info.uvd_घड़ी_प्रकारable_entries[0].dclk_did =
			igp_info->info_7.ucDPMState0DclkFid;
		pi->sys_info.uvd_घड़ी_प्रकारable_entries[1].dclk_did =
			igp_info->info_7.ucDPMState1DclkFid;
		pi->sys_info.uvd_घड़ी_प्रकारable_entries[2].dclk_did =
			igp_info->info_7.ucDPMState2DclkFid;
		pi->sys_info.uvd_घड़ी_प्रकारable_entries[3].dclk_did =
			igp_info->info_7.ucDPMState3DclkFid;

		क्रम (i = 0; i < 4; i++) अणु
			pi->sys_info.uvd_घड़ी_प्रकारable_entries[i].vclk =
				trinity_convert_did_to_freq(rdev,
							    pi->sys_info.uvd_घड़ी_प्रकारable_entries[i].vclk_did);
			pi->sys_info.uvd_घड़ी_प्रकारable_entries[i].dclk =
				trinity_convert_did_to_freq(rdev,
							    pi->sys_info.uvd_घड़ी_प्रकारable_entries[i].dclk_did);
		पूर्ण



	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक trinity_dpm_init(काष्ठा radeon_device *rdev)
अणु
	काष्ठा trinity_घातer_info *pi;
	पूर्णांक ret, i;

	pi = kzalloc(माप(काष्ठा trinity_घातer_info), GFP_KERNEL);
	अगर (pi == शून्य)
		वापस -ENOMEM;
	rdev->pm.dpm.priv = pi;

	क्रम (i = 0; i < SUMO_MAX_HARDWARE_POWERLEVELS; i++)
		pi->at[i] = TRINITY_AT_DFLT;

	अगर (radeon_bapm == -1) अणु
		/* There are stability issues reported on with
		 * bapm enabled when चयनing between AC and battery
		 * घातer.  At the same समय, some MSI boards hang
		 * अगर it's not enabled and dpm is enabled.  Just enable
		 * it क्रम MSI boards right now.
		 */
		अगर (rdev->pdev->subप्रणाली_venकरोr == 0x1462)
			pi->enable_bapm = true;
		अन्यथा
			pi->enable_bapm = false;
	पूर्ण अन्यथा अगर (radeon_bapm == 0) अणु
		pi->enable_bapm = false;
	पूर्ण अन्यथा अणु
		pi->enable_bapm = true;
	पूर्ण
	pi->enable_nbps_policy = true;
	pi->enable_sclk_ds = true;
	pi->enable_gfx_घातer_gating = true;
	pi->enable_gfx_घड़ी_gating = true;
	pi->enable_mg_घड़ी_gating = false;
	pi->enable_gfx_dynamic_mgpg = false;
	pi->override_dynamic_mgpg = false;
	pi->enable_स्वतः_thermal_throttling = true;
	pi->voltage_drop_in_dce = false; /* need to reकाष्ठाure dpm/modeset पूर्णांकeraction */
	pi->uvd_dpm = true; /* ??? */

	ret = trinity_parse_sys_info_table(rdev);
	अगर (ret)
		वापस ret;

	trinity_स्थिरruct_boot_state(rdev);

	ret = r600_get_platक्रमm_caps(rdev);
	अगर (ret)
		वापस ret;

	ret = r600_parse_extended_घातer_table(rdev);
	अगर (ret)
		वापस ret;

	ret = trinity_parse_घातer_table(rdev);
	अगर (ret)
		वापस ret;

	pi->thermal_स्वतः_throttling = pi->sys_info.htc_पंचांगp_lmt;
	pi->enable_dpm = true;

	वापस 0;
पूर्ण

व्योम trinity_dpm_prपूर्णांक_घातer_state(काष्ठा radeon_device *rdev,
				   काष्ठा radeon_ps *rps)
अणु
	पूर्णांक i;
	काष्ठा trinity_ps *ps = trinity_get_ps(rps);

	r600_dpm_prपूर्णांक_class_info(rps->class, rps->class2);
	r600_dpm_prपूर्णांक_cap_info(rps->caps);
	prपूर्णांकk("\tuvd    vclk: %d dclk: %d\n", rps->vclk, rps->dclk);
	क्रम (i = 0; i < ps->num_levels; i++) अणु
		काष्ठा trinity_pl *pl = &ps->levels[i];
		prपूर्णांकk("\t\tpower level %d    sclk: %u vddc: %u\n",
		       i, pl->sclk,
		       trinity_convert_voltage_index_to_value(rdev, pl->vddc_index));
	पूर्ण
	r600_dpm_prपूर्णांक_ps_status(rdev, rps);
पूर्ण

व्योम trinity_dpm_debugfs_prपूर्णांक_current_perक्रमmance_level(काष्ठा radeon_device *rdev,
							 काष्ठा seq_file *m)
अणु
	काष्ठा trinity_घातer_info *pi = trinity_get_pi(rdev);
	काष्ठा radeon_ps *rps = &pi->current_rps;
	काष्ठा trinity_ps *ps = trinity_get_ps(rps);
	काष्ठा trinity_pl *pl;
	u32 current_index =
		(RREG32(TARGET_AND_CURRENT_PROखाता_INDEX) & CURRENT_STATE_MASK) >>
		CURRENT_STATE_SHIFT;

	अगर (current_index >= ps->num_levels) अणु
		seq_म_लिखो(m, "invalid dpm profile %d\n", current_index);
	पूर्ण अन्यथा अणु
		pl = &ps->levels[current_index];
		seq_म_लिखो(m, "uvd    vclk: %d dclk: %d\n", rps->vclk, rps->dclk);
		seq_म_लिखो(m, "power level %d    sclk: %u vddc: %u\n",
			   current_index, pl->sclk,
			   trinity_convert_voltage_index_to_value(rdev, pl->vddc_index));
	पूर्ण
पूर्ण

u32 trinity_dpm_get_current_sclk(काष्ठा radeon_device *rdev)
अणु
	काष्ठा trinity_घातer_info *pi = trinity_get_pi(rdev);
	काष्ठा radeon_ps *rps = &pi->current_rps;
	काष्ठा trinity_ps *ps = trinity_get_ps(rps);
	काष्ठा trinity_pl *pl;
	u32 current_index =
		(RREG32(TARGET_AND_CURRENT_PROखाता_INDEX) & CURRENT_STATE_MASK) >>
		CURRENT_STATE_SHIFT;

	अगर (current_index >= ps->num_levels) अणु
		वापस 0;
	पूर्ण अन्यथा अणु
		pl = &ps->levels[current_index];
		वापस pl->sclk;
	पूर्ण
पूर्ण

u32 trinity_dpm_get_current_mclk(काष्ठा radeon_device *rdev)
अणु
	काष्ठा trinity_घातer_info *pi = trinity_get_pi(rdev);

	वापस pi->sys_info.bootup_uma_clk;
पूर्ण

व्योम trinity_dpm_fini(काष्ठा radeon_device *rdev)
अणु
	पूर्णांक i;

	trinity_cleanup_asic(rdev); /* ??? */

	क्रम (i = 0; i < rdev->pm.dpm.num_ps; i++) अणु
		kमुक्त(rdev->pm.dpm.ps[i].ps_priv);
	पूर्ण
	kमुक्त(rdev->pm.dpm.ps);
	kमुक्त(rdev->pm.dpm.priv);
	r600_मुक्त_extended_घातer_table(rdev);
पूर्ण

u32 trinity_dpm_get_sclk(काष्ठा radeon_device *rdev, bool low)
अणु
	काष्ठा trinity_घातer_info *pi = trinity_get_pi(rdev);
	काष्ठा trinity_ps *requested_state = trinity_get_ps(&pi->requested_rps);

	अगर (low)
		वापस requested_state->levels[0].sclk;
	अन्यथा
		वापस requested_state->levels[requested_state->num_levels - 1].sclk;
पूर्ण

u32 trinity_dpm_get_mclk(काष्ठा radeon_device *rdev, bool low)
अणु
	काष्ठा trinity_घातer_info *pi = trinity_get_pi(rdev);

	वापस pi->sys_info.bootup_uma_clk;
पूर्ण
