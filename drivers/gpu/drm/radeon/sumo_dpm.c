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

#समावेश "radeon.h"
#समावेश "radeon_asic.h"
#समावेश "sumod.h"
#समावेश "r600_dpm.h"
#समावेश "cypress_dpm.h"
#समावेश "sumo_dpm.h"
#समावेश <linux/seq_file.h>

#घोषणा SUMO_MAX_DEEPSLEEP_DIVIDER_ID 5
#घोषणा SUMO_MINIMUM_ENGINE_CLOCK 800
#घोषणा BOOST_DPM_LEVEL 7

अटल स्थिर u32 sumo_utc[SUMO_PM_NUMBER_OF_TC] =
अणु
	SUMO_UTC_DFLT_00,
	SUMO_UTC_DFLT_01,
	SUMO_UTC_DFLT_02,
	SUMO_UTC_DFLT_03,
	SUMO_UTC_DFLT_04,
	SUMO_UTC_DFLT_05,
	SUMO_UTC_DFLT_06,
	SUMO_UTC_DFLT_07,
	SUMO_UTC_DFLT_08,
	SUMO_UTC_DFLT_09,
	SUMO_UTC_DFLT_10,
	SUMO_UTC_DFLT_11,
	SUMO_UTC_DFLT_12,
	SUMO_UTC_DFLT_13,
	SUMO_UTC_DFLT_14,
पूर्ण;

अटल स्थिर u32 sumo_dtc[SUMO_PM_NUMBER_OF_TC] =
अणु
	SUMO_DTC_DFLT_00,
	SUMO_DTC_DFLT_01,
	SUMO_DTC_DFLT_02,
	SUMO_DTC_DFLT_03,
	SUMO_DTC_DFLT_04,
	SUMO_DTC_DFLT_05,
	SUMO_DTC_DFLT_06,
	SUMO_DTC_DFLT_07,
	SUMO_DTC_DFLT_08,
	SUMO_DTC_DFLT_09,
	SUMO_DTC_DFLT_10,
	SUMO_DTC_DFLT_11,
	SUMO_DTC_DFLT_12,
	SUMO_DTC_DFLT_13,
	SUMO_DTC_DFLT_14,
पूर्ण;

अटल काष्ठा sumo_ps *sumo_get_ps(काष्ठा radeon_ps *rps)
अणु
	काष्ठा sumo_ps *ps = rps->ps_priv;

	वापस ps;
पूर्ण

काष्ठा sumo_घातer_info *sumo_get_pi(काष्ठा radeon_device *rdev)
अणु
	काष्ठा sumo_घातer_info *pi = rdev->pm.dpm.priv;

	वापस pi;
पूर्ण

अटल व्योम sumo_gfx_घड़ीgating_enable(काष्ठा radeon_device *rdev, bool enable)
अणु
	अगर (enable)
		WREG32_P(SCLK_PWRMGT_CNTL, DYN_GFX_CLK_OFF_EN, ~DYN_GFX_CLK_OFF_EN);
	अन्यथा अणु
		WREG32_P(SCLK_PWRMGT_CNTL, 0, ~DYN_GFX_CLK_OFF_EN);
		WREG32_P(SCLK_PWRMGT_CNTL, GFX_CLK_FORCE_ON, ~GFX_CLK_FORCE_ON);
		WREG32_P(SCLK_PWRMGT_CNTL, 0, ~GFX_CLK_FORCE_ON);
		RREG32(GB_ADDR_CONFIG);
	पूर्ण
पूर्ण

#घोषणा CGCG_CGTT_LOCAL0_MASK 0xE5BFFFFF
#घोषणा CGCG_CGTT_LOCAL1_MASK 0xEFFF07FF

अटल व्योम sumo_mg_घड़ीgating_enable(काष्ठा radeon_device *rdev, bool enable)
अणु
	u32 local0;
	u32 local1;

	local0 = RREG32(CG_CGTT_LOCAL_0);
	local1 = RREG32(CG_CGTT_LOCAL_1);

	अगर (enable) अणु
		WREG32(CG_CGTT_LOCAL_0, (0 & CGCG_CGTT_LOCAL0_MASK) | (local0 & ~CGCG_CGTT_LOCAL0_MASK) );
		WREG32(CG_CGTT_LOCAL_1, (0 & CGCG_CGTT_LOCAL1_MASK) | (local1 & ~CGCG_CGTT_LOCAL1_MASK) );
	पूर्ण अन्यथा अणु
		WREG32(CG_CGTT_LOCAL_0, (0xFFFFFFFF & CGCG_CGTT_LOCAL0_MASK) | (local0 & ~CGCG_CGTT_LOCAL0_MASK) );
		WREG32(CG_CGTT_LOCAL_1, (0xFFFFCFFF & CGCG_CGTT_LOCAL1_MASK) | (local1 & ~CGCG_CGTT_LOCAL1_MASK) );
	पूर्ण
पूर्ण

अटल व्योम sumo_program_git(काष्ठा radeon_device *rdev)
अणु
	u32 p, u;
	u32 xclk = radeon_get_xclk(rdev);

	r600_calculate_u_and_p(SUMO_GICST_DFLT,
			       xclk, 16, &p, &u);

	WREG32_P(CG_GIT, CG_GICST(p), ~CG_GICST_MASK);
पूर्ण

अटल व्योम sumo_program_grsd(काष्ठा radeon_device *rdev)
अणु
	u32 p, u;
	u32 xclk = radeon_get_xclk(rdev);
	u32 grs = 256 * 25 / 100;

	r600_calculate_u_and_p(1, xclk, 14, &p, &u);

	WREG32(CG_GCOOR, PHC(grs) | SDC(p) | SU(u));
पूर्ण

व्योम sumo_gfx_घड़ीgating_initialize(काष्ठा radeon_device *rdev)
अणु
	sumo_program_git(rdev);
	sumo_program_grsd(rdev);
पूर्ण

अटल व्योम sumo_gfx_घातergating_initialize(काष्ठा radeon_device *rdev)
अणु
	u32 rcu_pwr_gating_cntl;
	u32 p, u;
	u32 p_c, p_p, d_p;
	u32 r_t, i_t;
	u32 xclk = radeon_get_xclk(rdev);

	अगर (rdev->family == CHIP_PALM) अणु
		p_c = 4;
		d_p = 10;
		r_t = 10;
		i_t = 4;
		p_p = 50 + 1000/200 + 6 * 32;
	पूर्ण अन्यथा अणु
		p_c = 16;
		d_p = 50;
		r_t = 50;
		i_t  = 50;
		p_p = 113;
	पूर्ण

	WREG32(CG_SCRATCH2, 0x01B60A17);

	r600_calculate_u_and_p(SUMO_GFXPOWERGATINGT_DFLT,
			       xclk, 16, &p, &u);

	WREG32_P(CG_PWR_GATING_CNTL, PGP(p) | PGU(u),
		 ~(PGP_MASK | PGU_MASK));

	r600_calculate_u_and_p(SUMO_VOLTAGEDROPT_DFLT,
			       xclk, 16, &p, &u);

	WREG32_P(CG_CG_VOLTAGE_CNTL, PGP(p) | PGU(u),
		 ~(PGP_MASK | PGU_MASK));

	अगर (rdev->family == CHIP_PALM) अणु
		WREG32_RCU(RCU_PWR_GATING_SEQ0, 0x10103210);
		WREG32_RCU(RCU_PWR_GATING_SEQ1, 0x10101010);
	पूर्ण अन्यथा अणु
		WREG32_RCU(RCU_PWR_GATING_SEQ0, 0x76543210);
		WREG32_RCU(RCU_PWR_GATING_SEQ1, 0xFEDCBA98);
	पूर्ण

	rcu_pwr_gating_cntl = RREG32_RCU(RCU_PWR_GATING_CNTL);
	rcu_pwr_gating_cntl &=
		~(RSVD_MASK | PCV_MASK | PGS_MASK);
	rcu_pwr_gating_cntl |= PCV(p_c) | PGS(1) | PWR_GATING_EN;
	अगर (rdev->family == CHIP_PALM) अणु
		rcu_pwr_gating_cntl &= ~PCP_MASK;
		rcu_pwr_gating_cntl |= PCP(0x77);
	पूर्ण
	WREG32_RCU(RCU_PWR_GATING_CNTL, rcu_pwr_gating_cntl);

	rcu_pwr_gating_cntl = RREG32_RCU(RCU_PWR_GATING_CNTL_2);
	rcu_pwr_gating_cntl &= ~(MPPU_MASK | MPPD_MASK);
	rcu_pwr_gating_cntl |= MPPU(p_p) | MPPD(50);
	WREG32_RCU(RCU_PWR_GATING_CNTL_2, rcu_pwr_gating_cntl);

	rcu_pwr_gating_cntl = RREG32_RCU(RCU_PWR_GATING_CNTL_3);
	rcu_pwr_gating_cntl &= ~(DPPU_MASK | DPPD_MASK);
	rcu_pwr_gating_cntl |= DPPU(d_p) | DPPD(50);
	WREG32_RCU(RCU_PWR_GATING_CNTL_3, rcu_pwr_gating_cntl);

	rcu_pwr_gating_cntl = RREG32_RCU(RCU_PWR_GATING_CNTL_4);
	rcu_pwr_gating_cntl &= ~(RT_MASK | IT_MASK);
	rcu_pwr_gating_cntl |= RT(r_t) | IT(i_t);
	WREG32_RCU(RCU_PWR_GATING_CNTL_4, rcu_pwr_gating_cntl);

	अगर (rdev->family == CHIP_PALM)
		WREG32_RCU(RCU_PWR_GATING_CNTL_5, 0xA02);

	sumo_smu_pg_init(rdev);

	rcu_pwr_gating_cntl = RREG32_RCU(RCU_PWR_GATING_CNTL);
	rcu_pwr_gating_cntl &=
		~(RSVD_MASK | PCV_MASK | PGS_MASK);
	rcu_pwr_gating_cntl |= PCV(p_c) | PGS(4) | PWR_GATING_EN;
	अगर (rdev->family == CHIP_PALM) अणु
		rcu_pwr_gating_cntl &= ~PCP_MASK;
		rcu_pwr_gating_cntl |= PCP(0x77);
	पूर्ण
	WREG32_RCU(RCU_PWR_GATING_CNTL, rcu_pwr_gating_cntl);

	अगर (rdev->family == CHIP_PALM) अणु
		rcu_pwr_gating_cntl = RREG32_RCU(RCU_PWR_GATING_CNTL_2);
		rcu_pwr_gating_cntl &= ~(MPPU_MASK | MPPD_MASK);
		rcu_pwr_gating_cntl |= MPPU(113) | MPPD(50);
		WREG32_RCU(RCU_PWR_GATING_CNTL_2, rcu_pwr_gating_cntl);

		rcu_pwr_gating_cntl = RREG32_RCU(RCU_PWR_GATING_CNTL_3);
		rcu_pwr_gating_cntl &= ~(DPPU_MASK | DPPD_MASK);
		rcu_pwr_gating_cntl |= DPPU(16) | DPPD(50);
		WREG32_RCU(RCU_PWR_GATING_CNTL_3, rcu_pwr_gating_cntl);
	पूर्ण

	sumo_smu_pg_init(rdev);

	rcu_pwr_gating_cntl = RREG32_RCU(RCU_PWR_GATING_CNTL);
	rcu_pwr_gating_cntl &=
		~(RSVD_MASK | PCV_MASK | PGS_MASK);
	rcu_pwr_gating_cntl |= PGS(5) | PWR_GATING_EN;

	अगर (rdev->family == CHIP_PALM) अणु
		rcu_pwr_gating_cntl |= PCV(4);
		rcu_pwr_gating_cntl &= ~PCP_MASK;
		rcu_pwr_gating_cntl |= PCP(0x77);
	पूर्ण अन्यथा
		rcu_pwr_gating_cntl |= PCV(11);
	WREG32_RCU(RCU_PWR_GATING_CNTL, rcu_pwr_gating_cntl);

	अगर (rdev->family == CHIP_PALM) अणु
		rcu_pwr_gating_cntl = RREG32_RCU(RCU_PWR_GATING_CNTL_2);
		rcu_pwr_gating_cntl &= ~(MPPU_MASK | MPPD_MASK);
		rcu_pwr_gating_cntl |= MPPU(113) | MPPD(50);
		WREG32_RCU(RCU_PWR_GATING_CNTL_2, rcu_pwr_gating_cntl);

		rcu_pwr_gating_cntl = RREG32_RCU(RCU_PWR_GATING_CNTL_3);
		rcu_pwr_gating_cntl &= ~(DPPU_MASK | DPPD_MASK);
		rcu_pwr_gating_cntl |= DPPU(22) | DPPD(50);
		WREG32_RCU(RCU_PWR_GATING_CNTL_3, rcu_pwr_gating_cntl);
	पूर्ण

	sumo_smu_pg_init(rdev);
पूर्ण

अटल व्योम sumo_gfx_घातergating_enable(काष्ठा radeon_device *rdev, bool enable)
अणु
	अगर (enable)
		WREG32_P(CG_PWR_GATING_CNTL, DYN_PWR_DOWN_EN, ~DYN_PWR_DOWN_EN);
	अन्यथा अणु
		WREG32_P(CG_PWR_GATING_CNTL, 0, ~DYN_PWR_DOWN_EN);
		RREG32(GB_ADDR_CONFIG);
	पूर्ण
पूर्ण

अटल पूर्णांक sumo_enable_घड़ी_घातer_gating(काष्ठा radeon_device *rdev)
अणु
	काष्ठा sumo_घातer_info *pi = sumo_get_pi(rdev);

	अगर (pi->enable_gfx_घड़ी_gating)
		sumo_gfx_घड़ीgating_initialize(rdev);
	अगर (pi->enable_gfx_घातer_gating)
		sumo_gfx_घातergating_initialize(rdev);
	अगर (pi->enable_mg_घड़ी_gating)
		sumo_mg_घड़ीgating_enable(rdev, true);
	अगर (pi->enable_gfx_घड़ी_gating)
		sumo_gfx_घड़ीgating_enable(rdev, true);
	अगर (pi->enable_gfx_घातer_gating)
		sumo_gfx_घातergating_enable(rdev, true);

	वापस 0;
पूर्ण

अटल व्योम sumo_disable_घड़ी_घातer_gating(काष्ठा radeon_device *rdev)
अणु
	काष्ठा sumo_घातer_info *pi = sumo_get_pi(rdev);

	अगर (pi->enable_gfx_घड़ी_gating)
		sumo_gfx_घड़ीgating_enable(rdev, false);
	अगर (pi->enable_gfx_घातer_gating)
		sumo_gfx_घातergating_enable(rdev, false);
	अगर (pi->enable_mg_घड़ी_gating)
		sumo_mg_घड़ीgating_enable(rdev, false);
पूर्ण

अटल व्योम sumo_calculate_bsp(काष्ठा radeon_device *rdev,
			       u32 high_clk)
अणु
	काष्ठा sumo_घातer_info *pi = sumo_get_pi(rdev);
	u32 xclk = radeon_get_xclk(rdev);

	pi->pasi = 65535 * 100 / high_clk;
	pi->asi = 65535 * 100 / high_clk;

	r600_calculate_u_and_p(pi->asi,
			       xclk, 16, &pi->bsp, &pi->bsu);

	r600_calculate_u_and_p(pi->pasi,
			       xclk, 16, &pi->pbsp, &pi->pbsu);

	pi->dsp = BSP(pi->bsp) | BSU(pi->bsu);
	pi->psp = BSP(pi->pbsp) | BSU(pi->pbsu);
पूर्ण

अटल व्योम sumo_init_bsp(काष्ठा radeon_device *rdev)
अणु
	काष्ठा sumo_घातer_info *pi = sumo_get_pi(rdev);

	WREG32(CG_BSP_0, pi->psp);
पूर्ण


अटल व्योम sumo_program_bsp(काष्ठा radeon_device *rdev,
			     काष्ठा radeon_ps *rps)
अणु
	काष्ठा sumo_घातer_info *pi = sumo_get_pi(rdev);
	काष्ठा sumo_ps *ps = sumo_get_ps(rps);
	u32 i;
	u32 highest_engine_घड़ी = ps->levels[ps->num_levels - 1].sclk;

	अगर (ps->flags & SUMO_POWERSTATE_FLAGS_BOOST_STATE)
		highest_engine_घड़ी = pi->boost_pl.sclk;

	sumo_calculate_bsp(rdev, highest_engine_घड़ी);

	क्रम (i = 0; i < ps->num_levels - 1; i++)
		WREG32(CG_BSP_0 + (i * 4), pi->dsp);

	WREG32(CG_BSP_0 + (i * 4), pi->psp);

	अगर (ps->flags & SUMO_POWERSTATE_FLAGS_BOOST_STATE)
		WREG32(CG_BSP_0 + (BOOST_DPM_LEVEL * 4), pi->psp);
पूर्ण

अटल व्योम sumo_ग_लिखो_at(काष्ठा radeon_device *rdev,
			  u32 index, u32 value)
अणु
	अगर (index == 0)
		WREG32(CG_AT_0, value);
	अन्यथा अगर (index == 1)
		WREG32(CG_AT_1, value);
	अन्यथा अगर (index == 2)
		WREG32(CG_AT_2, value);
	अन्यथा अगर (index == 3)
		WREG32(CG_AT_3, value);
	अन्यथा अगर (index == 4)
		WREG32(CG_AT_4, value);
	अन्यथा अगर (index == 5)
		WREG32(CG_AT_5, value);
	अन्यथा अगर (index == 6)
		WREG32(CG_AT_6, value);
	अन्यथा अगर (index == 7)
		WREG32(CG_AT_7, value);
पूर्ण

अटल व्योम sumo_program_at(काष्ठा radeon_device *rdev,
			    काष्ठा radeon_ps *rps)
अणु
	काष्ठा sumo_घातer_info *pi = sumo_get_pi(rdev);
	काष्ठा sumo_ps *ps = sumo_get_ps(rps);
	u32 asi;
	u32 i;
	u32 m_a;
	u32 a_t;
	u32 r[SUMO_MAX_HARDWARE_POWERLEVELS];
	u32 l[SUMO_MAX_HARDWARE_POWERLEVELS];

	r[0] = SUMO_R_DFLT0;
	r[1] = SUMO_R_DFLT1;
	r[2] = SUMO_R_DFLT2;
	r[3] = SUMO_R_DFLT3;
	r[4] = SUMO_R_DFLT4;

	l[0] = SUMO_L_DFLT0;
	l[1] = SUMO_L_DFLT1;
	l[2] = SUMO_L_DFLT2;
	l[3] = SUMO_L_DFLT3;
	l[4] = SUMO_L_DFLT4;

	क्रम (i = 0; i < ps->num_levels; i++) अणु
		asi = (i == ps->num_levels - 1) ? pi->pasi : pi->asi;

		m_a = asi * ps->levels[i].sclk / 100;

		a_t = CG_R(m_a * r[i] / 100) | CG_L(m_a * l[i] / 100);

		sumo_ग_लिखो_at(rdev, i, a_t);
	पूर्ण

	अगर (ps->flags & SUMO_POWERSTATE_FLAGS_BOOST_STATE) अणु
		asi = pi->pasi;

		m_a = asi * pi->boost_pl.sclk / 100;

		a_t = CG_R(m_a * r[ps->num_levels - 1] / 100) |
			CG_L(m_a * l[ps->num_levels - 1] / 100);

		sumo_ग_लिखो_at(rdev, BOOST_DPM_LEVEL, a_t);
	पूर्ण
पूर्ण

अटल व्योम sumo_program_tp(काष्ठा radeon_device *rdev)
अणु
	पूर्णांक i;
	क्रमागत r600_td td = R600_TD_DFLT;

	क्रम (i = 0; i < SUMO_PM_NUMBER_OF_TC; i++) अणु
		WREG32_P(CG_FFCT_0 + (i * 4), UTC_0(sumo_utc[i]), ~UTC_0_MASK);
		WREG32_P(CG_FFCT_0 + (i * 4), DTC_0(sumo_dtc[i]), ~DTC_0_MASK);
	पूर्ण

	अगर (td == R600_TD_AUTO)
		WREG32_P(SCLK_PWRMGT_CNTL, 0, ~FIR_FORCE_TREND_SEL);
	अन्यथा
		WREG32_P(SCLK_PWRMGT_CNTL, FIR_FORCE_TREND_SEL, ~FIR_FORCE_TREND_SEL);

	अगर (td == R600_TD_UP)
		WREG32_P(SCLK_PWRMGT_CNTL, 0, ~FIR_TREND_MODE);

	अगर (td == R600_TD_DOWN)
		WREG32_P(SCLK_PWRMGT_CNTL, FIR_TREND_MODE, ~FIR_TREND_MODE);
पूर्ण

व्योम sumo_program_vc(काष्ठा radeon_device *rdev, u32 vrc)
अणु
	WREG32(CG_FTV, vrc);
पूर्ण

व्योम sumo_clear_vc(काष्ठा radeon_device *rdev)
अणु
	WREG32(CG_FTV, 0);
पूर्ण

व्योम sumo_program_sstp(काष्ठा radeon_device *rdev)
अणु
	u32 p, u;
	u32 xclk = radeon_get_xclk(rdev);

	r600_calculate_u_and_p(SUMO_SST_DFLT,
			       xclk, 16, &p, &u);

	WREG32(CG_SSP, SSTU(u) | SST(p));
पूर्ण

अटल व्योम sumo_set_भागider_value(काष्ठा radeon_device *rdev,
				   u32 index, u32 भागider)
अणु
	u32 reg_index = index / 4;
	u32 field_index = index % 4;

	अगर (field_index == 0)
		WREG32_P(CG_SCLK_DPM_CTRL + (reg_index * 4),
			 SCLK_FSTATE_0_DIV(भागider), ~SCLK_FSTATE_0_DIV_MASK);
	अन्यथा अगर (field_index == 1)
		WREG32_P(CG_SCLK_DPM_CTRL + (reg_index * 4),
			 SCLK_FSTATE_1_DIV(भागider), ~SCLK_FSTATE_1_DIV_MASK);
	अन्यथा अगर (field_index == 2)
		WREG32_P(CG_SCLK_DPM_CTRL + (reg_index * 4),
			 SCLK_FSTATE_2_DIV(भागider), ~SCLK_FSTATE_2_DIV_MASK);
	अन्यथा अगर (field_index == 3)
		WREG32_P(CG_SCLK_DPM_CTRL + (reg_index * 4),
			 SCLK_FSTATE_3_DIV(भागider), ~SCLK_FSTATE_3_DIV_MASK);
पूर्ण

अटल व्योम sumo_set_ds_भागiders(काष्ठा radeon_device *rdev,
				 u32 index, u32 भागider)
अणु
	काष्ठा sumo_घातer_info *pi = sumo_get_pi(rdev);

	अगर (pi->enable_sclk_ds) अणु
		u32 dpm_ctrl = RREG32(CG_SCLK_DPM_CTRL_6);

		dpm_ctrl &= ~(0x7 << (index * 3));
		dpm_ctrl |= (भागider << (index * 3));
		WREG32(CG_SCLK_DPM_CTRL_6, dpm_ctrl);
	पूर्ण
पूर्ण

अटल व्योम sumo_set_ss_भागiders(काष्ठा radeon_device *rdev,
				 u32 index, u32 भागider)
अणु
	काष्ठा sumo_घातer_info *pi = sumo_get_pi(rdev);

	अगर (pi->enable_sclk_ds) अणु
		u32 dpm_ctrl = RREG32(CG_SCLK_DPM_CTRL_11);

		dpm_ctrl &= ~(0x7 << (index * 3));
		dpm_ctrl |= (भागider << (index * 3));
		WREG32(CG_SCLK_DPM_CTRL_11, dpm_ctrl);
	पूर्ण
पूर्ण

अटल व्योम sumo_set_vid(काष्ठा radeon_device *rdev, u32 index, u32 vid)
अणु
	u32 voltage_cntl = RREG32(CG_DPM_VOLTAGE_CNTL);

	voltage_cntl &= ~(DPM_STATE0_LEVEL_MASK << (index * 2));
	voltage_cntl |= (vid << (DPM_STATE0_LEVEL_SHIFT + index * 2));
	WREG32(CG_DPM_VOLTAGE_CNTL, voltage_cntl);
पूर्ण

अटल व्योम sumo_set_allos_gnb_slow(काष्ठा radeon_device *rdev, u32 index, u32 gnb_slow)
अणु
	काष्ठा sumo_घातer_info *pi = sumo_get_pi(rdev);
	u32 temp = gnb_slow;
	u32 cg_sclk_dpm_ctrl_3;

	अगर (pi->driver_nbps_policy_disable)
		temp = 1;

	cg_sclk_dpm_ctrl_3 = RREG32(CG_SCLK_DPM_CTRL_3);
	cg_sclk_dpm_ctrl_3 &= ~(GNB_SLOW_FSTATE_0_MASK << index);
	cg_sclk_dpm_ctrl_3 |= (temp << (GNB_SLOW_FSTATE_0_SHIFT + index));

	WREG32(CG_SCLK_DPM_CTRL_3, cg_sclk_dpm_ctrl_3);
पूर्ण

अटल व्योम sumo_program_घातer_level(काष्ठा radeon_device *rdev,
				     काष्ठा sumo_pl *pl, u32 index)
अणु
	काष्ठा sumo_घातer_info *pi = sumo_get_pi(rdev);
	पूर्णांक ret;
	काष्ठा atom_घड़ी_भागiders भागiders;
	u32 ds_en = RREG32(DEEP_SLEEP_CNTL) & ENABLE_DS;

	ret = radeon_atom_get_घड़ी_भागiders(rdev, COMPUTE_ENGINE_PLL_PARAM,
					     pl->sclk, false, &भागiders);
	अगर (ret)
		वापस;

	sumo_set_भागider_value(rdev, index, भागiders.post_भाग);

	sumo_set_vid(rdev, index, pl->vddc_index);

	अगर (pl->ss_भागider_index == 0 || pl->ds_भागider_index == 0) अणु
		अगर (ds_en)
			WREG32_P(DEEP_SLEEP_CNTL, 0, ~ENABLE_DS);
	पूर्ण अन्यथा अणु
		sumo_set_ss_भागiders(rdev, index, pl->ss_भागider_index);
		sumo_set_ds_भागiders(rdev, index, pl->ds_भागider_index);

		अगर (!ds_en)
			WREG32_P(DEEP_SLEEP_CNTL, ENABLE_DS, ~ENABLE_DS);
	पूर्ण

	sumo_set_allos_gnb_slow(rdev, index, pl->allow_gnb_slow);

	अगर (pi->enable_boost)
		sumo_set_tdp_limit(rdev, index, pl->sclk_dpm_tdp_limit);
पूर्ण

अटल व्योम sumo_घातer_level_enable(काष्ठा radeon_device *rdev, u32 index, bool enable)
अणु
	u32 reg_index = index / 4;
	u32 field_index = index % 4;

	अगर (field_index == 0)
		WREG32_P(CG_SCLK_DPM_CTRL + (reg_index * 4),
			 enable ? SCLK_FSTATE_0_VLD : 0, ~SCLK_FSTATE_0_VLD);
	अन्यथा अगर (field_index == 1)
		WREG32_P(CG_SCLK_DPM_CTRL + (reg_index * 4),
			 enable ? SCLK_FSTATE_1_VLD : 0, ~SCLK_FSTATE_1_VLD);
	अन्यथा अगर (field_index == 2)
		WREG32_P(CG_SCLK_DPM_CTRL + (reg_index * 4),
			 enable ? SCLK_FSTATE_2_VLD : 0, ~SCLK_FSTATE_2_VLD);
	अन्यथा अगर (field_index == 3)
		WREG32_P(CG_SCLK_DPM_CTRL + (reg_index * 4),
			 enable ? SCLK_FSTATE_3_VLD : 0, ~SCLK_FSTATE_3_VLD);
पूर्ण

अटल bool sumo_dpm_enabled(काष्ठा radeon_device *rdev)
अणु
	अगर (RREG32(CG_SCLK_DPM_CTRL_3) & DPM_SCLK_ENABLE)
		वापस true;
	अन्यथा
		वापस false;
पूर्ण

अटल व्योम sumo_start_dpm(काष्ठा radeon_device *rdev)
अणु
	WREG32_P(CG_SCLK_DPM_CTRL_3, DPM_SCLK_ENABLE, ~DPM_SCLK_ENABLE);
पूर्ण

अटल व्योम sumo_stop_dpm(काष्ठा radeon_device *rdev)
अणु
	WREG32_P(CG_SCLK_DPM_CTRL_3, 0, ~DPM_SCLK_ENABLE);
पूर्ण

अटल व्योम sumo_set_क्रमced_mode(काष्ठा radeon_device *rdev, bool enable)
अणु
	अगर (enable)
		WREG32_P(CG_SCLK_DPM_CTRL_3, FORCE_SCLK_STATE_EN, ~FORCE_SCLK_STATE_EN);
	अन्यथा
		WREG32_P(CG_SCLK_DPM_CTRL_3, 0, ~FORCE_SCLK_STATE_EN);
पूर्ण

अटल व्योम sumo_set_क्रमced_mode_enabled(काष्ठा radeon_device *rdev)
अणु
	पूर्णांक i;

	sumo_set_क्रमced_mode(rdev, true);
	क्रम (i = 0; i < rdev->usec_समयout; i++) अणु
		अगर (RREG32(CG_SCLK_STATUS) & SCLK_OVERCLK_DETECT)
			अवरोध;
		udelay(1);
	पूर्ण
पूर्ण

अटल व्योम sumo_रुको_क्रम_level_0(काष्ठा radeon_device *rdev)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < rdev->usec_समयout; i++) अणु
		अगर ((RREG32(TARGET_AND_CURRENT_PROखाता_INDEX) & CURR_SCLK_INDEX_MASK) == 0)
			अवरोध;
		udelay(1);
	पूर्ण
	क्रम (i = 0; i < rdev->usec_समयout; i++) अणु
		अगर ((RREG32(TARGET_AND_CURRENT_PROखाता_INDEX) & CURR_INDEX_MASK) == 0)
			अवरोध;
		udelay(1);
	पूर्ण
पूर्ण

अटल व्योम sumo_set_क्रमced_mode_disabled(काष्ठा radeon_device *rdev)
अणु
	sumo_set_क्रमced_mode(rdev, false);
पूर्ण

अटल व्योम sumo_enable_घातer_level_0(काष्ठा radeon_device *rdev)
अणु
	sumo_घातer_level_enable(rdev, 0, true);
पूर्ण

अटल व्योम sumo_patch_boost_state(काष्ठा radeon_device *rdev,
				   काष्ठा radeon_ps *rps)
अणु
	काष्ठा sumo_घातer_info *pi = sumo_get_pi(rdev);
	काष्ठा sumo_ps *new_ps = sumo_get_ps(rps);

	अगर (new_ps->flags & SUMO_POWERSTATE_FLAGS_BOOST_STATE) अणु
		pi->boost_pl = new_ps->levels[new_ps->num_levels - 1];
		pi->boost_pl.sclk = pi->sys_info.boost_sclk;
		pi->boost_pl.vddc_index = pi->sys_info.boost_vid_2bit;
		pi->boost_pl.sclk_dpm_tdp_limit = pi->sys_info.sclk_dpm_tdp_limit_boost;
	पूर्ण
पूर्ण

अटल व्योम sumo_pre_notअगरy_alt_vddnb_change(काष्ठा radeon_device *rdev,
					     काष्ठा radeon_ps *new_rps,
					     काष्ठा radeon_ps *old_rps)
अणु
	काष्ठा sumo_ps *new_ps = sumo_get_ps(new_rps);
	काष्ठा sumo_ps *old_ps = sumo_get_ps(old_rps);
	u32 nbps1_old = 0;
	u32 nbps1_new = 0;

	अगर (old_ps != शून्य)
		nbps1_old = (old_ps->flags & SUMO_POWERSTATE_FLAGS_FORCE_NBPS1_STATE) ? 1 : 0;

	nbps1_new = (new_ps->flags & SUMO_POWERSTATE_FLAGS_FORCE_NBPS1_STATE) ? 1 : 0;

	अगर (nbps1_old == 1 && nbps1_new == 0)
		sumo_smu_notअगरy_alt_vddnb_change(rdev, 0, 0);
पूर्ण

अटल व्योम sumo_post_notअगरy_alt_vddnb_change(काष्ठा radeon_device *rdev,
					      काष्ठा radeon_ps *new_rps,
					      काष्ठा radeon_ps *old_rps)
अणु
	काष्ठा sumo_ps *new_ps = sumo_get_ps(new_rps);
	काष्ठा sumo_ps *old_ps = sumo_get_ps(old_rps);
	u32 nbps1_old = 0;
	u32 nbps1_new = 0;

	अगर (old_ps != शून्य)
		nbps1_old = (old_ps->flags & SUMO_POWERSTATE_FLAGS_FORCE_NBPS1_STATE)? 1 : 0;

	nbps1_new = (new_ps->flags & SUMO_POWERSTATE_FLAGS_FORCE_NBPS1_STATE)? 1 : 0;

	अगर (nbps1_old == 0 && nbps1_new == 1)
		sumo_smu_notअगरy_alt_vddnb_change(rdev, 1, 1);
पूर्ण

अटल व्योम sumo_enable_boost(काष्ठा radeon_device *rdev,
			      काष्ठा radeon_ps *rps,
			      bool enable)
अणु
	काष्ठा sumo_ps *new_ps = sumo_get_ps(rps);

	अगर (enable) अणु
		अगर (new_ps->flags & SUMO_POWERSTATE_FLAGS_BOOST_STATE)
			sumo_boost_state_enable(rdev, true);
	पूर्ण अन्यथा
		sumo_boost_state_enable(rdev, false);
पूर्ण

अटल व्योम sumo_set_क्रमced_level(काष्ठा radeon_device *rdev, u32 index)
अणु
	WREG32_P(CG_SCLK_DPM_CTRL_3, FORCE_SCLK_STATE(index), ~FORCE_SCLK_STATE_MASK);
पूर्ण

अटल व्योम sumo_set_क्रमced_level_0(काष्ठा radeon_device *rdev)
अणु
	sumo_set_क्रमced_level(rdev, 0);
पूर्ण

अटल व्योम sumo_program_wl(काष्ठा radeon_device *rdev,
			    काष्ठा radeon_ps *rps)
अणु
	काष्ठा sumo_ps *new_ps = sumo_get_ps(rps);
	u32 dpm_ctrl4 = RREG32(CG_SCLK_DPM_CTRL_4);

	dpm_ctrl4 &= 0xFFFFFF00;
	dpm_ctrl4 |= (1 << (new_ps->num_levels - 1));

	अगर (new_ps->flags & SUMO_POWERSTATE_FLAGS_BOOST_STATE)
		dpm_ctrl4 |= (1 << BOOST_DPM_LEVEL);

	WREG32(CG_SCLK_DPM_CTRL_4, dpm_ctrl4);
पूर्ण

अटल व्योम sumo_program_घातer_levels_0_to_n(काष्ठा radeon_device *rdev,
					     काष्ठा radeon_ps *new_rps,
					     काष्ठा radeon_ps *old_rps)
अणु
	काष्ठा sumo_घातer_info *pi = sumo_get_pi(rdev);
	काष्ठा sumo_ps *new_ps = sumo_get_ps(new_rps);
	काष्ठा sumo_ps *old_ps = sumo_get_ps(old_rps);
	u32 i;
	u32 n_current_state_levels = (old_ps == शून्य) ? 1 : old_ps->num_levels;

	क्रम (i = 0; i < new_ps->num_levels; i++) अणु
		sumo_program_घातer_level(rdev, &new_ps->levels[i], i);
		sumo_घातer_level_enable(rdev, i, true);
	पूर्ण

	क्रम (i = new_ps->num_levels; i < n_current_state_levels; i++)
		sumo_घातer_level_enable(rdev, i, false);

	अगर (new_ps->flags & SUMO_POWERSTATE_FLAGS_BOOST_STATE)
		sumo_program_घातer_level(rdev, &pi->boost_pl, BOOST_DPM_LEVEL);
पूर्ण

अटल व्योम sumo_enable_acpi_pm(काष्ठा radeon_device *rdev)
अणु
	WREG32_P(GENERAL_PWRMGT, STATIC_PM_EN, ~STATIC_PM_EN);
पूर्ण

अटल व्योम sumo_program_घातer_level_enter_state(काष्ठा radeon_device *rdev)
अणु
	WREG32_P(CG_SCLK_DPM_CTRL_5, SCLK_FSTATE_BOOTUP(0), ~SCLK_FSTATE_BOOTUP_MASK);
पूर्ण

अटल व्योम sumo_program_acpi_घातer_level(काष्ठा radeon_device *rdev)
अणु
	काष्ठा sumo_घातer_info *pi = sumo_get_pi(rdev);
	काष्ठा atom_घड़ी_भागiders भागiders;
	पूर्णांक ret;

	ret = radeon_atom_get_घड़ी_भागiders(rdev, COMPUTE_ENGINE_PLL_PARAM,
					     pi->acpi_pl.sclk,
					     false, &भागiders);
	अगर (ret)
		वापस;

	WREG32_P(CG_ACPI_CNTL, SCLK_ACPI_DIV(भागiders.post_भाग), ~SCLK_ACPI_DIV_MASK);
	WREG32_P(CG_ACPI_VOLTAGE_CNTL, 0, ~ACPI_VOLTAGE_EN);
पूर्ण

अटल व्योम sumo_program_bootup_state(काष्ठा radeon_device *rdev)
अणु
	काष्ठा sumo_घातer_info *pi = sumo_get_pi(rdev);
	u32 dpm_ctrl4 = RREG32(CG_SCLK_DPM_CTRL_4);
	u32 i;

	sumo_program_घातer_level(rdev, &pi->boot_pl, 0);

	dpm_ctrl4 &= 0xFFFFFF00;
	WREG32(CG_SCLK_DPM_CTRL_4, dpm_ctrl4);

	क्रम (i = 1; i < 8; i++)
		sumo_घातer_level_enable(rdev, i, false);
पूर्ण

अटल व्योम sumo_setup_uvd_घड़ीs(काष्ठा radeon_device *rdev,
				  काष्ठा radeon_ps *new_rps,
				  काष्ठा radeon_ps *old_rps)
अणु
	काष्ठा sumo_घातer_info *pi = sumo_get_pi(rdev);

	अगर (pi->enable_gfx_घातer_gating) अणु
		sumo_gfx_घातergating_enable(rdev, false);
	पूर्ण

	radeon_set_uvd_घड़ीs(rdev, new_rps->vclk, new_rps->dclk);

	अगर (pi->enable_gfx_घातer_gating) अणु
		अगर (!pi->disable_gfx_घातer_gating_in_uvd ||
		    !r600_is_uvd_state(new_rps->class, new_rps->class2))
			sumo_gfx_घातergating_enable(rdev, true);
	पूर्ण
पूर्ण

अटल व्योम sumo_set_uvd_घड़ी_beक्रमe_set_eng_घड़ी(काष्ठा radeon_device *rdev,
						    काष्ठा radeon_ps *new_rps,
						    काष्ठा radeon_ps *old_rps)
अणु
	काष्ठा sumo_ps *new_ps = sumo_get_ps(new_rps);
	काष्ठा sumo_ps *current_ps = sumo_get_ps(old_rps);

	अगर ((new_rps->vclk == old_rps->vclk) &&
	    (new_rps->dclk == old_rps->dclk))
		वापस;

	अगर (new_ps->levels[new_ps->num_levels - 1].sclk >=
	    current_ps->levels[current_ps->num_levels - 1].sclk)
		वापस;

	sumo_setup_uvd_घड़ीs(rdev, new_rps, old_rps);
पूर्ण

अटल व्योम sumo_set_uvd_घड़ी_after_set_eng_घड़ी(काष्ठा radeon_device *rdev,
						   काष्ठा radeon_ps *new_rps,
						   काष्ठा radeon_ps *old_rps)
अणु
	काष्ठा sumo_ps *new_ps = sumo_get_ps(new_rps);
	काष्ठा sumo_ps *current_ps = sumo_get_ps(old_rps);

	अगर ((new_rps->vclk == old_rps->vclk) &&
	    (new_rps->dclk == old_rps->dclk))
		वापस;

	अगर (new_ps->levels[new_ps->num_levels - 1].sclk <
	    current_ps->levels[current_ps->num_levels - 1].sclk)
		वापस;

	sumo_setup_uvd_घड़ीs(rdev, new_rps, old_rps);
पूर्ण

व्योम sumo_take_smu_control(काष्ठा radeon_device *rdev, bool enable)
अणु
/* This bit selects who handles display phy घातergating.
 * Clear the bit to let atom handle it.
 * Set it to let the driver handle it.
 * For now we just let atom handle it.
 */
#अगर 0
	u32 v = RREG32(DOUT_SCRATCH3);

	अगर (enable)
		v |= 0x4;
	अन्यथा
		v &= 0xFFFFFFFB;

	WREG32(DOUT_SCRATCH3, v);
#पूर्ण_अगर
पूर्ण

अटल व्योम sumo_enable_sclk_ds(काष्ठा radeon_device *rdev, bool enable)
अणु
	अगर (enable) अणु
		u32 deep_sleep_cntl = RREG32(DEEP_SLEEP_CNTL);
		u32 deep_sleep_cntl2 = RREG32(DEEP_SLEEP_CNTL2);
		u32 t = 1;

		deep_sleep_cntl &= ~R_DIS;
		deep_sleep_cntl &= ~HS_MASK;
		deep_sleep_cntl |= HS(t > 4095 ? 4095 : t);

		deep_sleep_cntl2 |= LB_UFP_EN;
		deep_sleep_cntl2 &= INOUT_C_MASK;
		deep_sleep_cntl2 |= INOUT_C(0xf);

		WREG32(DEEP_SLEEP_CNTL2, deep_sleep_cntl2);
		WREG32(DEEP_SLEEP_CNTL, deep_sleep_cntl);
	पूर्ण अन्यथा
		WREG32_P(DEEP_SLEEP_CNTL, 0, ~ENABLE_DS);
पूर्ण

अटल व्योम sumo_program_bootup_at(काष्ठा radeon_device *rdev)
अणु
	WREG32_P(CG_AT_0, CG_R(0xffff), ~CG_R_MASK);
	WREG32_P(CG_AT_0, CG_L(0), ~CG_L_MASK);
पूर्ण

अटल व्योम sumo_reset_am(काष्ठा radeon_device *rdev)
अणु
	WREG32_P(SCLK_PWRMGT_CNTL, FIR_RESET, ~FIR_RESET);
पूर्ण

अटल व्योम sumo_start_am(काष्ठा radeon_device *rdev)
अणु
	WREG32_P(SCLK_PWRMGT_CNTL, 0, ~FIR_RESET);
पूर्ण

अटल व्योम sumo_program_ttp(काष्ठा radeon_device *rdev)
अणु
	u32 xclk = radeon_get_xclk(rdev);
	u32 p, u;
	u32 cg_sclk_dpm_ctrl_5 = RREG32(CG_SCLK_DPM_CTRL_5);

	r600_calculate_u_and_p(1000,
			       xclk, 16, &p, &u);

	cg_sclk_dpm_ctrl_5 &= ~(TT_TP_MASK | TT_TU_MASK);
	cg_sclk_dpm_ctrl_5 |= TT_TP(p) | TT_TU(u);

	WREG32(CG_SCLK_DPM_CTRL_5, cg_sclk_dpm_ctrl_5);
पूर्ण

अटल व्योम sumo_program_ttt(काष्ठा radeon_device *rdev)
अणु
	u32 cg_sclk_dpm_ctrl_3 = RREG32(CG_SCLK_DPM_CTRL_3);
	काष्ठा sumo_घातer_info *pi = sumo_get_pi(rdev);

	cg_sclk_dpm_ctrl_3 &= ~(GNB_TT_MASK | GNB_THERMTHRO_MASK);
	cg_sclk_dpm_ctrl_3 |= GNB_TT(pi->thermal_स्वतः_throttling + 49);

	WREG32(CG_SCLK_DPM_CTRL_3, cg_sclk_dpm_ctrl_3);
पूर्ण


अटल व्योम sumo_enable_voltage_scaling(काष्ठा radeon_device *rdev, bool enable)
अणु
	अगर (enable) अणु
		WREG32_P(CG_DPM_VOLTAGE_CNTL, DPM_VOLTAGE_EN, ~DPM_VOLTAGE_EN);
		WREG32_P(CG_CG_VOLTAGE_CNTL, 0, ~CG_VOLTAGE_EN);
	पूर्ण अन्यथा अणु
		WREG32_P(CG_CG_VOLTAGE_CNTL, CG_VOLTAGE_EN, ~CG_VOLTAGE_EN);
		WREG32_P(CG_DPM_VOLTAGE_CNTL, 0, ~DPM_VOLTAGE_EN);
	पूर्ण
पूर्ण

अटल व्योम sumo_override_cnb_thermal_events(काष्ठा radeon_device *rdev)
अणु
	WREG32_P(CG_SCLK_DPM_CTRL_3, CNB_THERMTHRO_MASK_SCLK,
		 ~CNB_THERMTHRO_MASK_SCLK);
पूर्ण

अटल व्योम sumo_program_dc_hto(काष्ठा radeon_device *rdev)
अणु
	u32 cg_sclk_dpm_ctrl_4 = RREG32(CG_SCLK_DPM_CTRL_4);
	u32 p, u;
	u32 xclk = radeon_get_xclk(rdev);

	r600_calculate_u_and_p(100000,
			       xclk, 14, &p, &u);

	cg_sclk_dpm_ctrl_4 &= ~(DC_HDC_MASK | DC_HU_MASK);
	cg_sclk_dpm_ctrl_4 |= DC_HDC(p) | DC_HU(u);

	WREG32(CG_SCLK_DPM_CTRL_4, cg_sclk_dpm_ctrl_4);
पूर्ण

अटल व्योम sumo_क्रमce_nbp_state(काष्ठा radeon_device *rdev,
				 काष्ठा radeon_ps *rps)
अणु
	काष्ठा sumo_घातer_info *pi = sumo_get_pi(rdev);
	काष्ठा sumo_ps *new_ps = sumo_get_ps(rps);

	अगर (!pi->driver_nbps_policy_disable) अणु
		अगर (new_ps->flags & SUMO_POWERSTATE_FLAGS_FORCE_NBPS1_STATE)
			WREG32_P(CG_SCLK_DPM_CTRL_3, FORCE_NB_PSTATE_1, ~FORCE_NB_PSTATE_1);
		अन्यथा
			WREG32_P(CG_SCLK_DPM_CTRL_3, 0, ~FORCE_NB_PSTATE_1);
	पूर्ण
पूर्ण

u32 sumo_get_sleep_भागider_from_id(u32 id)
अणु
	वापस 1 << id;
पूर्ण

u32 sumo_get_sleep_भागider_id_from_घड़ी(काष्ठा radeon_device *rdev,
					 u32 sclk,
					 u32 min_sclk_in_sr)
अणु
	काष्ठा sumo_घातer_info *pi = sumo_get_pi(rdev);
	u32 i;
	u32 temp;
	u32 min = (min_sclk_in_sr > SUMO_MINIMUM_ENGINE_CLOCK) ?
		min_sclk_in_sr : SUMO_MINIMUM_ENGINE_CLOCK;

	अगर (sclk < min)
		वापस 0;

	अगर (!pi->enable_sclk_ds)
		वापस 0;

	क्रम (i = SUMO_MAX_DEEPSLEEP_DIVIDER_ID;  ; i--) अणु
		temp = sclk / sumo_get_sleep_भागider_from_id(i);

		अगर (temp >= min || i == 0)
			अवरोध;
	पूर्ण
	वापस i;
पूर्ण

अटल u32 sumo_get_valid_engine_घड़ी(काष्ठा radeon_device *rdev,
				       u32 lower_limit)
अणु
	काष्ठा sumo_घातer_info *pi = sumo_get_pi(rdev);
	u32 i;

	क्रम (i = 0; i < pi->sys_info.sclk_voltage_mapping_table.num_max_dpm_entries; i++) अणु
		अगर (pi->sys_info.sclk_voltage_mapping_table.entries[i].sclk_frequency >= lower_limit)
			वापस pi->sys_info.sclk_voltage_mapping_table.entries[i].sclk_frequency;
	पूर्ण

	वापस pi->sys_info.sclk_voltage_mapping_table.entries[pi->sys_info.sclk_voltage_mapping_table.num_max_dpm_entries - 1].sclk_frequency;
पूर्ण

अटल व्योम sumo_patch_thermal_state(काष्ठा radeon_device *rdev,
				     काष्ठा sumo_ps *ps,
				     काष्ठा sumo_ps *current_ps)
अणु
	काष्ठा sumo_घातer_info *pi = sumo_get_pi(rdev);
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

	ps->levels[0].ss_भागider_index =
		sumo_get_sleep_भागider_id_from_घड़ी(rdev, ps->levels[0].sclk, sclk_in_sr);

	ps->levels[0].ds_भागider_index =
		sumo_get_sleep_भागider_id_from_घड़ी(rdev, ps->levels[0].sclk, SUMO_MINIMUM_ENGINE_CLOCK);

	अगर (ps->levels[0].ds_भागider_index > ps->levels[0].ss_भागider_index + 1)
		ps->levels[0].ds_भागider_index = ps->levels[0].ss_भागider_index + 1;

	अगर (ps->levels[0].ss_भागider_index == ps->levels[0].ds_भागider_index) अणु
		अगर (ps->levels[0].ss_भागider_index > 1)
			ps->levels[0].ss_भागider_index = ps->levels[0].ss_भागider_index - 1;
	पूर्ण

	अगर (ps->levels[0].ss_भागider_index == 0)
		ps->levels[0].ds_भागider_index = 0;

	अगर (ps->levels[0].ds_भागider_index == 0)
		ps->levels[0].ss_भागider_index = 0;
पूर्ण

अटल व्योम sumo_apply_state_adjust_rules(काष्ठा radeon_device *rdev,
					  काष्ठा radeon_ps *new_rps,
					  काष्ठा radeon_ps *old_rps)
अणु
	काष्ठा sumo_ps *ps = sumo_get_ps(new_rps);
	काष्ठा sumo_ps *current_ps = sumo_get_ps(old_rps);
	काष्ठा sumo_घातer_info *pi = sumo_get_pi(rdev);
	u32 min_voltage = 0; /* ??? */
	u32 min_sclk = pi->sys_info.min_sclk; /* XXX check against disp reqs */
	u32 sclk_in_sr = pi->sys_info.min_sclk; /* ??? */
	u32 i;

	अगर (new_rps->class & ATOM_PPLIB_CLASSIFICATION_THERMAL)
		वापस sumo_patch_thermal_state(rdev, ps, current_ps);

	अगर (pi->enable_boost) अणु
		अगर (new_rps->class & ATOM_PPLIB_CLASSIFICATION_UI_PERFORMANCE)
			ps->flags |= SUMO_POWERSTATE_FLAGS_BOOST_STATE;
	पूर्ण

	अगर ((new_rps->class & ATOM_PPLIB_CLASSIFICATION_UI_BATTERY) ||
	    (new_rps->class & ATOM_PPLIB_CLASSIFICATION_SDSTATE) ||
	    (new_rps->class & ATOM_PPLIB_CLASSIFICATION_HDSTATE))
		ps->flags |= SUMO_POWERSTATE_FLAGS_FORCE_NBPS1_STATE;

	क्रम (i = 0; i < ps->num_levels; i++) अणु
		अगर (ps->levels[i].vddc_index < min_voltage)
			ps->levels[i].vddc_index = min_voltage;

		अगर (ps->levels[i].sclk < min_sclk)
			ps->levels[i].sclk =
				sumo_get_valid_engine_घड़ी(rdev, min_sclk);

		ps->levels[i].ss_भागider_index =
			sumo_get_sleep_भागider_id_from_घड़ी(rdev, ps->levels[i].sclk, sclk_in_sr);

		ps->levels[i].ds_भागider_index =
			sumo_get_sleep_भागider_id_from_घड़ी(rdev, ps->levels[i].sclk, SUMO_MINIMUM_ENGINE_CLOCK);

		अगर (ps->levels[i].ds_भागider_index > ps->levels[i].ss_भागider_index + 1)
			ps->levels[i].ds_भागider_index = ps->levels[i].ss_भागider_index + 1;

		अगर (ps->levels[i].ss_भागider_index == ps->levels[i].ds_भागider_index) अणु
			अगर (ps->levels[i].ss_भागider_index > 1)
				ps->levels[i].ss_भागider_index = ps->levels[i].ss_भागider_index - 1;
		पूर्ण

		अगर (ps->levels[i].ss_भागider_index == 0)
			ps->levels[i].ds_भागider_index = 0;

		अगर (ps->levels[i].ds_भागider_index == 0)
			ps->levels[i].ss_भागider_index = 0;

		अगर (ps->flags & SUMO_POWERSTATE_FLAGS_FORCE_NBPS1_STATE)
			ps->levels[i].allow_gnb_slow = 1;
		अन्यथा अगर ((new_rps->class & ATOM_PPLIB_CLASSIFICATION_UVDSTATE) ||
			 (new_rps->class2 & ATOM_PPLIB_CLASSIFICATION2_MVC))
			ps->levels[i].allow_gnb_slow = 0;
		अन्यथा अगर (i == ps->num_levels - 1)
			ps->levels[i].allow_gnb_slow = 0;
		अन्यथा
			ps->levels[i].allow_gnb_slow = 1;
	पूर्ण
पूर्ण

अटल व्योम sumo_cleanup_asic(काष्ठा radeon_device *rdev)
अणु
	sumo_take_smu_control(rdev, false);
पूर्ण

अटल पूर्णांक sumo_set_thermal_temperature_range(काष्ठा radeon_device *rdev,
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

	WREG32_P(CG_THERMAL_INT, DIG_THERM_INTH(49 + (high_temp / 1000)), ~DIG_THERM_INTH_MASK);
	WREG32_P(CG_THERMAL_INT, DIG_THERM_INTL(49 + (low_temp / 1000)), ~DIG_THERM_INTL_MASK);

	rdev->pm.dpm.thermal.min_temp = low_temp;
	rdev->pm.dpm.thermal.max_temp = high_temp;

	वापस 0;
पूर्ण

अटल व्योम sumo_update_current_ps(काष्ठा radeon_device *rdev,
				   काष्ठा radeon_ps *rps)
अणु
	काष्ठा sumo_ps *new_ps = sumo_get_ps(rps);
	काष्ठा sumo_घातer_info *pi = sumo_get_pi(rdev);

	pi->current_rps = *rps;
	pi->current_ps = *new_ps;
	pi->current_rps.ps_priv = &pi->current_ps;
पूर्ण

अटल व्योम sumo_update_requested_ps(काष्ठा radeon_device *rdev,
				     काष्ठा radeon_ps *rps)
अणु
	काष्ठा sumo_ps *new_ps = sumo_get_ps(rps);
	काष्ठा sumo_घातer_info *pi = sumo_get_pi(rdev);

	pi->requested_rps = *rps;
	pi->requested_ps = *new_ps;
	pi->requested_rps.ps_priv = &pi->requested_ps;
पूर्ण

पूर्णांक sumo_dpm_enable(काष्ठा radeon_device *rdev)
अणु
	काष्ठा sumo_घातer_info *pi = sumo_get_pi(rdev);

	अगर (sumo_dpm_enabled(rdev))
		वापस -EINVAL;

	sumo_program_bootup_state(rdev);
	sumo_init_bsp(rdev);
	sumo_reset_am(rdev);
	sumo_program_tp(rdev);
	sumo_program_bootup_at(rdev);
	sumo_start_am(rdev);
	अगर (pi->enable_स्वतः_thermal_throttling) अणु
		sumo_program_ttp(rdev);
		sumo_program_ttt(rdev);
	पूर्ण
	sumo_program_dc_hto(rdev);
	sumo_program_घातer_level_enter_state(rdev);
	sumo_enable_voltage_scaling(rdev, true);
	sumo_program_sstp(rdev);
	sumo_program_vc(rdev, SUMO_VRC_DFLT);
	sumo_override_cnb_thermal_events(rdev);
	sumo_start_dpm(rdev);
	sumo_रुको_क्रम_level_0(rdev);
	अगर (pi->enable_sclk_ds)
		sumo_enable_sclk_ds(rdev, true);
	अगर (pi->enable_boost)
		sumo_enable_boost_समयr(rdev);

	sumo_update_current_ps(rdev, rdev->pm.dpm.boot_ps);

	वापस 0;
पूर्ण

पूर्णांक sumo_dpm_late_enable(काष्ठा radeon_device *rdev)
अणु
	पूर्णांक ret;

	ret = sumo_enable_घड़ी_घातer_gating(rdev);
	अगर (ret)
		वापस ret;

	अगर (rdev->irq.installed &&
	    r600_is_पूर्णांकernal_thermal_sensor(rdev->pm.पूर्णांक_thermal_type)) अणु
		ret = sumo_set_thermal_temperature_range(rdev, R600_TEMP_RANGE_MIN, R600_TEMP_RANGE_MAX);
		अगर (ret)
			वापस ret;
		rdev->irq.dpm_thermal = true;
		radeon_irq_set(rdev);
	पूर्ण

	वापस 0;
पूर्ण

व्योम sumo_dpm_disable(काष्ठा radeon_device *rdev)
अणु
	काष्ठा sumo_घातer_info *pi = sumo_get_pi(rdev);

	अगर (!sumo_dpm_enabled(rdev))
		वापस;
	sumo_disable_घड़ी_घातer_gating(rdev);
	अगर (pi->enable_sclk_ds)
		sumo_enable_sclk_ds(rdev, false);
	sumo_clear_vc(rdev);
	sumo_रुको_क्रम_level_0(rdev);
	sumo_stop_dpm(rdev);
	sumo_enable_voltage_scaling(rdev, false);

	अगर (rdev->irq.installed &&
	    r600_is_पूर्णांकernal_thermal_sensor(rdev->pm.पूर्णांक_thermal_type)) अणु
		rdev->irq.dpm_thermal = false;
		radeon_irq_set(rdev);
	पूर्ण

	sumo_update_current_ps(rdev, rdev->pm.dpm.boot_ps);
पूर्ण

पूर्णांक sumo_dpm_pre_set_घातer_state(काष्ठा radeon_device *rdev)
अणु
	काष्ठा sumo_घातer_info *pi = sumo_get_pi(rdev);
	काष्ठा radeon_ps requested_ps = *rdev->pm.dpm.requested_ps;
	काष्ठा radeon_ps *new_ps = &requested_ps;

	sumo_update_requested_ps(rdev, new_ps);

	अगर (pi->enable_dynamic_patch_ps)
		sumo_apply_state_adjust_rules(rdev,
					      &pi->requested_rps,
					      &pi->current_rps);

	वापस 0;
पूर्ण

पूर्णांक sumo_dpm_set_घातer_state(काष्ठा radeon_device *rdev)
अणु
	काष्ठा sumo_घातer_info *pi = sumo_get_pi(rdev);
	काष्ठा radeon_ps *new_ps = &pi->requested_rps;
	काष्ठा radeon_ps *old_ps = &pi->current_rps;

	अगर (pi->enable_dpm)
		sumo_set_uvd_घड़ी_beक्रमe_set_eng_घड़ी(rdev, new_ps, old_ps);
	अगर (pi->enable_boost) अणु
		sumo_enable_boost(rdev, new_ps, false);
		sumo_patch_boost_state(rdev, new_ps);
	पूर्ण
	अगर (pi->enable_dpm) अणु
		sumo_pre_notअगरy_alt_vddnb_change(rdev, new_ps, old_ps);
		sumo_enable_घातer_level_0(rdev);
		sumo_set_क्रमced_level_0(rdev);
		sumo_set_क्रमced_mode_enabled(rdev);
		sumo_रुको_क्रम_level_0(rdev);
		sumo_program_घातer_levels_0_to_n(rdev, new_ps, old_ps);
		sumo_program_wl(rdev, new_ps);
		sumo_program_bsp(rdev, new_ps);
		sumo_program_at(rdev, new_ps);
		sumo_क्रमce_nbp_state(rdev, new_ps);
		sumo_set_क्रमced_mode_disabled(rdev);
		sumo_set_क्रमced_mode_enabled(rdev);
		sumo_set_क्रमced_mode_disabled(rdev);
		sumo_post_notअगरy_alt_vddnb_change(rdev, new_ps, old_ps);
	पूर्ण
	अगर (pi->enable_boost)
		sumo_enable_boost(rdev, new_ps, true);
	अगर (pi->enable_dpm)
		sumo_set_uvd_घड़ी_after_set_eng_घड़ी(rdev, new_ps, old_ps);

	वापस 0;
पूर्ण

व्योम sumo_dpm_post_set_घातer_state(काष्ठा radeon_device *rdev)
अणु
	काष्ठा sumo_घातer_info *pi = sumo_get_pi(rdev);
	काष्ठा radeon_ps *new_ps = &pi->requested_rps;

	sumo_update_current_ps(rdev, new_ps);
पूर्ण

#अगर 0
व्योम sumo_dpm_reset_asic(काष्ठा radeon_device *rdev)
अणु
	sumo_program_bootup_state(rdev);
	sumo_enable_घातer_level_0(rdev);
	sumo_set_क्रमced_level_0(rdev);
	sumo_set_क्रमced_mode_enabled(rdev);
	sumo_रुको_क्रम_level_0(rdev);
	sumo_set_क्रमced_mode_disabled(rdev);
	sumo_set_क्रमced_mode_enabled(rdev);
	sumo_set_क्रमced_mode_disabled(rdev);
पूर्ण
#पूर्ण_अगर

व्योम sumo_dpm_setup_asic(काष्ठा radeon_device *rdev)
अणु
	काष्ठा sumo_घातer_info *pi = sumo_get_pi(rdev);

	sumo_initialize_m3_arb(rdev);
	pi->fw_version = sumo_get_running_fw_version(rdev);
	DRM_INFO("Found smc ucode version: 0x%08x\n", pi->fw_version);
	sumo_program_acpi_घातer_level(rdev);
	sumo_enable_acpi_pm(rdev);
	sumo_take_smu_control(rdev, true);
पूर्ण

व्योम sumo_dpm_display_configuration_changed(काष्ठा radeon_device *rdev)
अणु

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

अटल व्योम sumo_patch_boot_state(काष्ठा radeon_device *rdev,
				  काष्ठा sumo_ps *ps)
अणु
	काष्ठा sumo_घातer_info *pi = sumo_get_pi(rdev);

	ps->num_levels = 1;
	ps->flags = 0;
	ps->levels[0] = pi->boot_pl;
पूर्ण

अटल व्योम sumo_parse_pplib_non_घड़ी_info(काष्ठा radeon_device *rdev,
					    काष्ठा radeon_ps *rps,
					    काष्ठा _ATOM_PPLIB_NONCLOCK_INFO *non_घड़ी_info,
					    u8 table_rev)
अणु
	काष्ठा sumo_ps *ps = sumo_get_ps(rps);

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
		sumo_patch_boot_state(rdev, ps);
	पूर्ण
	अगर (rps->class & ATOM_PPLIB_CLASSIFICATION_UVDSTATE)
		rdev->pm.dpm.uvd_ps = rps;
पूर्ण

अटल व्योम sumo_parse_pplib_घड़ी_info(काष्ठा radeon_device *rdev,
					काष्ठा radeon_ps *rps, पूर्णांक index,
					जोड़ pplib_घड़ी_info *घड़ी_info)
अणु
	काष्ठा sumo_घातer_info *pi = sumo_get_pi(rdev);
	काष्ठा sumo_ps *ps = sumo_get_ps(rps);
	काष्ठा sumo_pl *pl = &ps->levels[index];
	u32 sclk;

	sclk = le16_to_cpu(घड़ी_info->sumo.usEngineClockLow);
	sclk |= घड़ी_info->sumo.ucEngineClockHigh << 16;
	pl->sclk = sclk;
	pl->vddc_index = घड़ी_info->sumo.vddcIndex;
	pl->sclk_dpm_tdp_limit = घड़ी_info->sumo.tdpLimit;

	ps->num_levels = index + 1;

	अगर (pi->enable_sclk_ds) अणु
		pl->ds_भागider_index = 5;
		pl->ss_भागider_index = 4;
	पूर्ण
पूर्ण

अटल पूर्णांक sumo_parse_घातer_table(काष्ठा radeon_device *rdev)
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
			अगर (k >= SUMO_MAX_HARDWARE_POWERLEVELS)
				अवरोध;

			घड़ी_info = (जोड़ pplib_घड़ी_info *)
				((u8 *)&घड़ी_info_array->घड़ीInfo[0] +
				 (घड़ी_array_index * घड़ी_info_array->ucEntrySize));
			sumo_parse_pplib_घड़ी_info(rdev,
						    &rdev->pm.dpm.ps[i], k,
						    घड़ी_info);
			k++;
		पूर्ण
		sumo_parse_pplib_non_घड़ी_info(rdev, &rdev->pm.dpm.ps[i],
						non_घड़ी_info,
						non_घड़ी_info_array->ucEntrySize);
		घातer_state_offset += 2 + घातer_state->v2.ucNumDPMLevels;
	पूर्ण
	rdev->pm.dpm.num_ps = state_array->ucNumEntries;
	वापस 0;
पूर्ण

u32 sumo_convert_vid2_to_vid7(काष्ठा radeon_device *rdev,
			      काष्ठा sumo_vid_mapping_table *vid_mapping_table,
			      u32 vid_2bit)
अणु
	u32 i;

	क्रम (i = 0; i < vid_mapping_table->num_entries; i++) अणु
		अगर (vid_mapping_table->entries[i].vid_2bit == vid_2bit)
			वापस vid_mapping_table->entries[i].vid_7bit;
	पूर्ण

	वापस vid_mapping_table->entries[vid_mapping_table->num_entries - 1].vid_7bit;
पूर्ण

#अगर 0
u32 sumo_convert_vid7_to_vid2(काष्ठा radeon_device *rdev,
			      काष्ठा sumo_vid_mapping_table *vid_mapping_table,
			      u32 vid_7bit)
अणु
	u32 i;

	क्रम (i = 0; i < vid_mapping_table->num_entries; i++) अणु
		अगर (vid_mapping_table->entries[i].vid_7bit == vid_7bit)
			वापस vid_mapping_table->entries[i].vid_2bit;
	पूर्ण

	वापस vid_mapping_table->entries[vid_mapping_table->num_entries - 1].vid_2bit;
पूर्ण
#पूर्ण_अगर

अटल u16 sumo_convert_voltage_index_to_value(काष्ठा radeon_device *rdev,
					       u32 vid_2bit)
अणु
	काष्ठा sumo_घातer_info *pi = sumo_get_pi(rdev);
	u32 vid_7bit = sumo_convert_vid2_to_vid7(rdev, &pi->sys_info.vid_mapping_table, vid_2bit);

	अगर (vid_7bit > 0x7C)
		वापस 0;

	वापस (15500 - vid_7bit * 125 + 5) / 10;
पूर्ण

अटल व्योम sumo_स्थिरruct_display_voltage_mapping_table(काष्ठा radeon_device *rdev,
							 काष्ठा sumo_disp_घड़ी_voltage_mapping_table *disp_clk_voltage_mapping_table,
							 ATOM_CLK_VOLT_CAPABILITY *table)
अणु
	u32 i;

	क्रम (i = 0; i < SUMO_MAX_NUMBER_VOLTAGES; i++) अणु
		अगर (table[i].ulMaximumSupportedCLK == 0)
			अवरोध;

		disp_clk_voltage_mapping_table->display_घड़ी_frequency[i] =
			table[i].ulMaximumSupportedCLK;
	पूर्ण

	disp_clk_voltage_mapping_table->num_max_voltage_levels = i;

	अगर (disp_clk_voltage_mapping_table->num_max_voltage_levels == 0) अणु
		disp_clk_voltage_mapping_table->display_घड़ी_frequency[0] = 80000;
		disp_clk_voltage_mapping_table->num_max_voltage_levels = 1;
	पूर्ण
पूर्ण

व्योम sumo_स्थिरruct_sclk_voltage_mapping_table(काष्ठा radeon_device *rdev,
					       काष्ठा sumo_sclk_voltage_mapping_table *sclk_voltage_mapping_table,
					       ATOM_AVAILABLE_SCLK_LIST *table)
अणु
	u32 i;
	u32 n = 0;
	u32 prev_sclk = 0;

	क्रम (i = 0; i < SUMO_MAX_HARDWARE_POWERLEVELS; i++) अणु
		अगर (table[i].ulSupportedSCLK > prev_sclk) अणु
			sclk_voltage_mapping_table->entries[n].sclk_frequency =
				table[i].ulSupportedSCLK;
			sclk_voltage_mapping_table->entries[n].vid_2bit =
				table[i].usVoltageIndex;
			prev_sclk = table[i].ulSupportedSCLK;
			n++;
		पूर्ण
	पूर्ण

	sclk_voltage_mapping_table->num_max_dpm_entries = n;
पूर्ण

व्योम sumo_स्थिरruct_vid_mapping_table(काष्ठा radeon_device *rdev,
				      काष्ठा sumo_vid_mapping_table *vid_mapping_table,
				      ATOM_AVAILABLE_SCLK_LIST *table)
अणु
	u32 i, j;

	क्रम (i = 0; i < SUMO_MAX_HARDWARE_POWERLEVELS; i++) अणु
		अगर (table[i].ulSupportedSCLK != 0) अणु
			vid_mapping_table->entries[table[i].usVoltageIndex].vid_7bit =
				table[i].usVoltageID;
			vid_mapping_table->entries[table[i].usVoltageIndex].vid_2bit =
				table[i].usVoltageIndex;
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < SUMO_MAX_NUMBER_VOLTAGES; i++) अणु
		अगर (vid_mapping_table->entries[i].vid_7bit == 0) अणु
			क्रम (j = i + 1; j < SUMO_MAX_NUMBER_VOLTAGES; j++) अणु
				अगर (vid_mapping_table->entries[j].vid_7bit != 0) अणु
					vid_mapping_table->entries[i] =
						vid_mapping_table->entries[j];
					vid_mapping_table->entries[j].vid_7bit = 0;
					अवरोध;
				पूर्ण
			पूर्ण

			अगर (j == SUMO_MAX_NUMBER_VOLTAGES)
				अवरोध;
		पूर्ण
	पूर्ण

	vid_mapping_table->num_entries = i;
पूर्ण

जोड़ igp_info अणु
	काष्ठा _ATOM_INTEGRATED_SYSTEM_INFO info;
	काष्ठा _ATOM_INTEGRATED_SYSTEM_INFO_V2 info_2;
	काष्ठा _ATOM_INTEGRATED_SYSTEM_INFO_V5 info_5;
	काष्ठा _ATOM_INTEGRATED_SYSTEM_INFO_V6 info_6;
पूर्ण;

अटल पूर्णांक sumo_parse_sys_info_table(काष्ठा radeon_device *rdev)
अणु
	काष्ठा sumo_घातer_info *pi = sumo_get_pi(rdev);
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

		अगर (crev != 6) अणु
			DRM_ERROR("Unsupported IGP table: %d %d\n", frev, crev);
			वापस -EINVAL;
		पूर्ण
		pi->sys_info.bootup_sclk = le32_to_cpu(igp_info->info_6.ulBootUpEngineClock);
		pi->sys_info.min_sclk = le32_to_cpu(igp_info->info_6.ulMinEngineClock);
		pi->sys_info.bootup_uma_clk = le32_to_cpu(igp_info->info_6.ulBootUpUMAClock);
		pi->sys_info.bootup_nb_voltage_index =
			le16_to_cpu(igp_info->info_6.usBootUpNBVoltage);
		अगर (igp_info->info_6.ucHtcTmpLmt == 0)
			pi->sys_info.htc_पंचांगp_lmt = 203;
		अन्यथा
			pi->sys_info.htc_पंचांगp_lmt = igp_info->info_6.ucHtcTmpLmt;
		अगर (igp_info->info_6.ucHtcHystLmt == 0)
			pi->sys_info.htc_hyst_lmt = 5;
		अन्यथा
			pi->sys_info.htc_hyst_lmt = igp_info->info_6.ucHtcHystLmt;
		अगर (pi->sys_info.htc_पंचांगp_lmt <= pi->sys_info.htc_hyst_lmt) अणु
			DRM_ERROR("The htcTmpLmt should be larger than htcHystLmt.\n");
		पूर्ण
		क्रम (i = 0; i < NUMBER_OF_M3ARB_PARAM_SETS; i++) अणु
			pi->sys_info.csr_m3_arb_cntl_शेष[i] =
				le32_to_cpu(igp_info->info_6.ulCSR_M3_ARB_CNTL_DEFAULT[i]);
			pi->sys_info.csr_m3_arb_cntl_uvd[i] =
				le32_to_cpu(igp_info->info_6.ulCSR_M3_ARB_CNTL_UVD[i]);
			pi->sys_info.csr_m3_arb_cntl_fs3d[i] =
				le32_to_cpu(igp_info->info_6.ulCSR_M3_ARB_CNTL_FS3D[i]);
		पूर्ण
		pi->sys_info.sclk_dpm_boost_margin =
			le32_to_cpu(igp_info->info_6.SclkDpmBoostMargin);
		pi->sys_info.sclk_dpm_throttle_margin =
			le32_to_cpu(igp_info->info_6.SclkDpmThrottleMargin);
		pi->sys_info.sclk_dpm_tdp_limit_pg =
			le16_to_cpu(igp_info->info_6.SclkDpmTdpLimitPG);
		pi->sys_info.gnb_tdp_limit = le16_to_cpu(igp_info->info_6.GnbTdpLimit);
		pi->sys_info.sclk_dpm_tdp_limit_boost =
			le16_to_cpu(igp_info->info_6.SclkDpmTdpLimitBoost);
		pi->sys_info.boost_sclk = le32_to_cpu(igp_info->info_6.ulBoostEngineCLock);
		pi->sys_info.boost_vid_2bit = igp_info->info_6.ulBoostVid_2bit;
		अगर (igp_info->info_6.EnableBoost)
			pi->sys_info.enable_boost = true;
		अन्यथा
			pi->sys_info.enable_boost = false;
		sumo_स्थिरruct_display_voltage_mapping_table(rdev,
							     &pi->sys_info.disp_clk_voltage_mapping_table,
							     igp_info->info_6.sDISPCLK_Voltage);
		sumo_स्थिरruct_sclk_voltage_mapping_table(rdev,
							  &pi->sys_info.sclk_voltage_mapping_table,
							  igp_info->info_6.sAvail_SCLK);
		sumo_स्थिरruct_vid_mapping_table(rdev, &pi->sys_info.vid_mapping_table,
						 igp_info->info_6.sAvail_SCLK);

	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम sumo_स्थिरruct_boot_and_acpi_state(काष्ठा radeon_device *rdev)
अणु
	काष्ठा sumo_घातer_info *pi = sumo_get_pi(rdev);

	pi->boot_pl.sclk = pi->sys_info.bootup_sclk;
	pi->boot_pl.vddc_index = pi->sys_info.bootup_nb_voltage_index;
	pi->boot_pl.ds_भागider_index = 0;
	pi->boot_pl.ss_भागider_index = 0;
	pi->boot_pl.allow_gnb_slow = 1;
	pi->acpi_pl = pi->boot_pl;
	pi->current_ps.num_levels = 1;
	pi->current_ps.levels[0] = pi->boot_pl;
पूर्ण

पूर्णांक sumo_dpm_init(काष्ठा radeon_device *rdev)
अणु
	काष्ठा sumo_घातer_info *pi;
	u32 hw_rev = (RREG32(HW_REV) & ATI_REV_ID_MASK) >> ATI_REV_ID_SHIFT;
	पूर्णांक ret;

	pi = kzalloc(माप(काष्ठा sumo_घातer_info), GFP_KERNEL);
	अगर (pi == शून्य)
		वापस -ENOMEM;
	rdev->pm.dpm.priv = pi;

	pi->driver_nbps_policy_disable = false;
	अगर ((rdev->family == CHIP_PALM) && (hw_rev < 3))
		pi->disable_gfx_घातer_gating_in_uvd = true;
	अन्यथा
		pi->disable_gfx_घातer_gating_in_uvd = false;
	pi->enable_alt_vddnb = true;
	pi->enable_sclk_ds = true;
	pi->enable_dynamic_m3_arbiter = false;
	pi->enable_dynamic_patch_ps = true;
	/* Some PALM chips करोn't seem to properly ungate gfx when UVD is in use;
	 * क्रम now just disable gfx PG.
	 */
	अगर (rdev->family == CHIP_PALM)
		pi->enable_gfx_घातer_gating = false;
	अन्यथा
		pi->enable_gfx_घातer_gating = true;
	pi->enable_gfx_घड़ी_gating = true;
	pi->enable_mg_घड़ी_gating = true;
	pi->enable_स्वतः_thermal_throttling = true;

	ret = sumo_parse_sys_info_table(rdev);
	अगर (ret)
		वापस ret;

	sumo_स्थिरruct_boot_and_acpi_state(rdev);

	ret = r600_get_platक्रमm_caps(rdev);
	अगर (ret)
		वापस ret;

	ret = sumo_parse_घातer_table(rdev);
	अगर (ret)
		वापस ret;

	pi->pasi = CYPRESS_HASI_DFLT;
	pi->asi = RV770_ASI_DFLT;
	pi->thermal_स्वतः_throttling = pi->sys_info.htc_पंचांगp_lmt;
	pi->enable_boost = pi->sys_info.enable_boost;
	pi->enable_dpm = true;

	वापस 0;
पूर्ण

व्योम sumo_dpm_prपूर्णांक_घातer_state(काष्ठा radeon_device *rdev,
				काष्ठा radeon_ps *rps)
अणु
	पूर्णांक i;
	काष्ठा sumo_ps *ps = sumo_get_ps(rps);

	r600_dpm_prपूर्णांक_class_info(rps->class, rps->class2);
	r600_dpm_prपूर्णांक_cap_info(rps->caps);
	prपूर्णांकk("\tuvd    vclk: %d dclk: %d\n", rps->vclk, rps->dclk);
	क्रम (i = 0; i < ps->num_levels; i++) अणु
		काष्ठा sumo_pl *pl = &ps->levels[i];
		prपूर्णांकk("\t\tpower level %d    sclk: %u vddc: %u\n",
		       i, pl->sclk,
		       sumo_convert_voltage_index_to_value(rdev, pl->vddc_index));
	पूर्ण
	r600_dpm_prपूर्णांक_ps_status(rdev, rps);
पूर्ण

व्योम sumo_dpm_debugfs_prपूर्णांक_current_perक्रमmance_level(काष्ठा radeon_device *rdev,
						      काष्ठा seq_file *m)
अणु
	काष्ठा sumo_घातer_info *pi = sumo_get_pi(rdev);
	काष्ठा radeon_ps *rps = &pi->current_rps;
	काष्ठा sumo_ps *ps = sumo_get_ps(rps);
	काष्ठा sumo_pl *pl;
	u32 current_index =
		(RREG32(TARGET_AND_CURRENT_PROखाता_INDEX) & CURR_INDEX_MASK) >>
		CURR_INDEX_SHIFT;

	अगर (current_index == BOOST_DPM_LEVEL) अणु
		pl = &pi->boost_pl;
		seq_म_लिखो(m, "uvd    vclk: %d dclk: %d\n", rps->vclk, rps->dclk);
		seq_म_लिखो(m, "power level %d    sclk: %u vddc: %u\n",
			   current_index, pl->sclk,
			   sumo_convert_voltage_index_to_value(rdev, pl->vddc_index));
	पूर्ण अन्यथा अगर (current_index >= ps->num_levels) अणु
		seq_म_लिखो(m, "invalid dpm profile %d\n", current_index);
	पूर्ण अन्यथा अणु
		pl = &ps->levels[current_index];
		seq_म_लिखो(m, "uvd    vclk: %d dclk: %d\n", rps->vclk, rps->dclk);
		seq_म_लिखो(m, "power level %d    sclk: %u vddc: %u\n",
			   current_index, pl->sclk,
			   sumo_convert_voltage_index_to_value(rdev, pl->vddc_index));
	पूर्ण
पूर्ण

u32 sumo_dpm_get_current_sclk(काष्ठा radeon_device *rdev)
अणु
	काष्ठा sumo_घातer_info *pi = sumo_get_pi(rdev);
	काष्ठा radeon_ps *rps = &pi->current_rps;
	काष्ठा sumo_ps *ps = sumo_get_ps(rps);
	काष्ठा sumo_pl *pl;
	u32 current_index =
		(RREG32(TARGET_AND_CURRENT_PROखाता_INDEX) & CURR_INDEX_MASK) >>
		CURR_INDEX_SHIFT;

	अगर (current_index == BOOST_DPM_LEVEL) अणु
		pl = &pi->boost_pl;
		वापस pl->sclk;
	पूर्ण अन्यथा अगर (current_index >= ps->num_levels) अणु
		वापस 0;
	पूर्ण अन्यथा अणु
		pl = &ps->levels[current_index];
		वापस pl->sclk;
	पूर्ण
पूर्ण

u32 sumo_dpm_get_current_mclk(काष्ठा radeon_device *rdev)
अणु
	काष्ठा sumo_घातer_info *pi = sumo_get_pi(rdev);

	वापस pi->sys_info.bootup_uma_clk;
पूर्ण

u16 sumo_dpm_get_current_vddc(काष्ठा radeon_device *rdev)
अणु
	काष्ठा sumo_घातer_info *pi = sumo_get_pi(rdev);
	काष्ठा radeon_ps *rps = &pi->current_rps;
	काष्ठा sumo_ps *ps = sumo_get_ps(rps);
	काष्ठा sumo_pl *pl;
	u32 current_index =
		(RREG32(TARGET_AND_CURRENT_PROखाता_INDEX) & CURR_INDEX_MASK) >>
		CURR_INDEX_SHIFT;

	अगर (current_index == BOOST_DPM_LEVEL) अणु
		pl = &pi->boost_pl;
	पूर्ण अन्यथा अगर (current_index >= ps->num_levels) अणु
		वापस 0;
	पूर्ण अन्यथा अणु
		pl = &ps->levels[current_index];
	पूर्ण
	वापस sumo_convert_voltage_index_to_value(rdev, pl->vddc_index);
पूर्ण

व्योम sumo_dpm_fini(काष्ठा radeon_device *rdev)
अणु
	पूर्णांक i;

	sumo_cleanup_asic(rdev); /* ??? */

	क्रम (i = 0; i < rdev->pm.dpm.num_ps; i++) अणु
		kमुक्त(rdev->pm.dpm.ps[i].ps_priv);
	पूर्ण
	kमुक्त(rdev->pm.dpm.ps);
	kमुक्त(rdev->pm.dpm.priv);
पूर्ण

u32 sumo_dpm_get_sclk(काष्ठा radeon_device *rdev, bool low)
अणु
	काष्ठा sumo_घातer_info *pi = sumo_get_pi(rdev);
	काष्ठा sumo_ps *requested_state = sumo_get_ps(&pi->requested_rps);

	अगर (low)
		वापस requested_state->levels[0].sclk;
	अन्यथा
		वापस requested_state->levels[requested_state->num_levels - 1].sclk;
पूर्ण

u32 sumo_dpm_get_mclk(काष्ठा radeon_device *rdev, bool low)
अणु
	काष्ठा sumo_घातer_info *pi = sumo_get_pi(rdev);

	वापस pi->sys_info.bootup_uma_clk;
पूर्ण

पूर्णांक sumo_dpm_क्रमce_perक्रमmance_level(काष्ठा radeon_device *rdev,
				     क्रमागत radeon_dpm_क्रमced_level level)
अणु
	काष्ठा sumo_घातer_info *pi = sumo_get_pi(rdev);
	काष्ठा radeon_ps *rps = &pi->current_rps;
	काष्ठा sumo_ps *ps = sumo_get_ps(rps);
	पूर्णांक i;

	अगर (ps->num_levels <= 1)
		वापस 0;

	अगर (level == RADEON_DPM_FORCED_LEVEL_HIGH) अणु
		अगर (pi->enable_boost)
			sumo_enable_boost(rdev, rps, false);
		sumo_घातer_level_enable(rdev, ps->num_levels - 1, true);
		sumo_set_क्रमced_level(rdev, ps->num_levels - 1);
		sumo_set_क्रमced_mode_enabled(rdev);
		क्रम (i = 0; i < ps->num_levels - 1; i++) अणु
			sumo_घातer_level_enable(rdev, i, false);
		पूर्ण
		sumo_set_क्रमced_mode(rdev, false);
		sumo_set_क्रमced_mode_enabled(rdev);
		sumo_set_क्रमced_mode(rdev, false);
	पूर्ण अन्यथा अगर (level == RADEON_DPM_FORCED_LEVEL_LOW) अणु
		अगर (pi->enable_boost)
			sumo_enable_boost(rdev, rps, false);
		sumo_घातer_level_enable(rdev, 0, true);
		sumo_set_क्रमced_level(rdev, 0);
		sumo_set_क्रमced_mode_enabled(rdev);
		क्रम (i = 1; i < ps->num_levels; i++) अणु
			sumo_घातer_level_enable(rdev, i, false);
		पूर्ण
		sumo_set_क्रमced_mode(rdev, false);
		sumo_set_क्रमced_mode_enabled(rdev);
		sumo_set_क्रमced_mode(rdev, false);
	पूर्ण अन्यथा अणु
		क्रम (i = 0; i < ps->num_levels; i++) अणु
			sumo_घातer_level_enable(rdev, i, true);
		पूर्ण
		अगर (pi->enable_boost)
			sumo_enable_boost(rdev, rps, true);
	पूर्ण

	rdev->pm.dpm.क्रमced_level = level;

	वापस 0;
पूर्ण
