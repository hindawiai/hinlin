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
#समावेश "sumod.h"
#समावेश "sumo_dpm.h"
#समावेश "ppsmc.h"

#घोषणा SUMO_SMU_SERVICE_ROUTINE_PG_INIT        1
#घोषणा SUMO_SMU_SERVICE_ROUTINE_ALTVDDNB_NOTIFY  27
#घोषणा SUMO_SMU_SERVICE_ROUTINE_GFX_SRV_ID_20  20

अटल व्योम sumo_send_msg_to_smu(काष्ठा radeon_device *rdev, u32 id)
अणु
	u32 gfx_पूर्णांक_req;
	पूर्णांक i;

	क्रम (i = 0; i < rdev->usec_समयout; i++) अणु
		अगर (RREG32(GFX_INT_STATUS) & INT_DONE)
			अवरोध;
		udelay(1);
	पूर्ण

	gfx_पूर्णांक_req = SERV_INDEX(id) | INT_REQ;
	WREG32(GFX_INT_REQ, gfx_पूर्णांक_req);

	क्रम (i = 0; i < rdev->usec_समयout; i++) अणु
		अगर (RREG32(GFX_INT_REQ) & INT_REQ)
			अवरोध;
		udelay(1);
	पूर्ण

	क्रम (i = 0; i < rdev->usec_समयout; i++) अणु
		अगर (RREG32(GFX_INT_STATUS) & INT_ACK)
			अवरोध;
		udelay(1);
	पूर्ण

	क्रम (i = 0; i < rdev->usec_समयout; i++) अणु
		अगर (RREG32(GFX_INT_STATUS) & INT_DONE)
			अवरोध;
		udelay(1);
	पूर्ण

	gfx_पूर्णांक_req &= ~INT_REQ;
	WREG32(GFX_INT_REQ, gfx_पूर्णांक_req);
पूर्ण

व्योम sumo_initialize_m3_arb(काष्ठा radeon_device *rdev)
अणु
	काष्ठा sumo_घातer_info *pi = sumo_get_pi(rdev);
	u32 i;

	अगर (!pi->enable_dynamic_m3_arbiter)
		वापस;

	क्रम (i = 0; i < NUMBER_OF_M3ARB_PARAM_SETS; i++)
		WREG32_RCU(MCU_M3ARB_PARAMS + (i * 4),
			   pi->sys_info.csr_m3_arb_cntl_शेष[i]);

	क्रम (; i < NUMBER_OF_M3ARB_PARAM_SETS * 2; i++)
		WREG32_RCU(MCU_M3ARB_PARAMS + (i * 4),
			   pi->sys_info.csr_m3_arb_cntl_uvd[i % NUMBER_OF_M3ARB_PARAM_SETS]);

	क्रम (; i < NUMBER_OF_M3ARB_PARAM_SETS * 3; i++)
		WREG32_RCU(MCU_M3ARB_PARAMS + (i * 4),
			   pi->sys_info.csr_m3_arb_cntl_fs3d[i % NUMBER_OF_M3ARB_PARAM_SETS]);
पूर्ण

अटल bool sumo_is_alt_vddnb_supported(काष्ठा radeon_device *rdev)
अणु
	काष्ठा sumo_घातer_info *pi = sumo_get_pi(rdev);
	bool वापस_code = false;

	अगर (!pi->enable_alt_vddnb)
		वापस वापस_code;

	अगर ((rdev->family == CHIP_SUMO) || (rdev->family == CHIP_SUMO2)) अणु
		अगर (pi->fw_version >= 0x00010C00)
			वापस_code = true;
	पूर्ण

	वापस वापस_code;
पूर्ण

व्योम sumo_smu_notअगरy_alt_vddnb_change(काष्ठा radeon_device *rdev,
				      bool घातersaving, bool क्रमce_nbps1)
अणु
	u32 param = 0;

	अगर (!sumo_is_alt_vddnb_supported(rdev))
		वापस;

	अगर (घातersaving)
		param |= 1;

	अगर (क्रमce_nbps1)
		param |= 2;

	WREG32_RCU(RCU_ALTVDDNB_NOTIFY, param);

	sumo_send_msg_to_smu(rdev, SUMO_SMU_SERVICE_ROUTINE_ALTVDDNB_NOTIFY);
पूर्ण

व्योम sumo_smu_pg_init(काष्ठा radeon_device *rdev)
अणु
	sumo_send_msg_to_smu(rdev, SUMO_SMU_SERVICE_ROUTINE_PG_INIT);
पूर्ण

अटल u32 sumo_घातer_of_4(u32 unit)
अणु
	u32 ret = 1;
	u32 i;

	क्रम (i = 0; i < unit; i++)
		ret *= 4;

	वापस ret;
पूर्ण

व्योम sumo_enable_boost_समयr(काष्ठा radeon_device *rdev)
अणु
	काष्ठा sumo_घातer_info *pi = sumo_get_pi(rdev);
	u32 period, unit, समयr_value;
	u32 xclk = radeon_get_xclk(rdev);

	unit = (RREG32_RCU(RCU_LCLK_SCALING_CNTL) & LCLK_SCALING_TIMER_PRESCALER_MASK)
		>> LCLK_SCALING_TIMER_PRESCALER_SHIFT;

	period = 100 * (xclk / 100 / sumo_घातer_of_4(unit));

	समयr_value = (period << 16) | (unit << 4);

	WREG32_RCU(RCU_GNB_PWR_REP_TIMER_CNTL, समयr_value);
	WREG32_RCU(RCU_BOOST_MARGIN, pi->sys_info.sclk_dpm_boost_margin);
	WREG32_RCU(RCU_THROTTLE_MARGIN, pi->sys_info.sclk_dpm_throttle_margin);
	WREG32_RCU(GNB_TDP_LIMIT, pi->sys_info.gnb_tdp_limit);
	WREG32_RCU(RCU_SclkDpmTdpLimitPG, pi->sys_info.sclk_dpm_tdp_limit_pg);

	sumo_send_msg_to_smu(rdev, SUMO_SMU_SERVICE_ROUTINE_GFX_SRV_ID_20);
पूर्ण

व्योम sumo_set_tdp_limit(काष्ठा radeon_device *rdev, u32 index, u32 tdp_limit)
अणु
	u32 regoffset = 0;
	u32 shअगरt = 0;
	u32 mask = 0xFFF;
	u32 sclk_dpm_tdp_limit;

	चयन (index) अणु
	हाल 0:
		regoffset = RCU_SclkDpmTdpLimit01;
		shअगरt = 16;
		अवरोध;
	हाल 1:
		regoffset = RCU_SclkDpmTdpLimit01;
		shअगरt = 0;
		अवरोध;
	हाल 2:
		regoffset = RCU_SclkDpmTdpLimit23;
		shअगरt = 16;
		अवरोध;
	हाल 3:
		regoffset = RCU_SclkDpmTdpLimit23;
		shअगरt = 0;
		अवरोध;
	हाल 4:
		regoffset = RCU_SclkDpmTdpLimit47;
		shअगरt = 16;
		अवरोध;
	हाल 7:
		regoffset = RCU_SclkDpmTdpLimit47;
		shअगरt = 0;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	sclk_dpm_tdp_limit = RREG32_RCU(regoffset);
	sclk_dpm_tdp_limit &= ~(mask << shअगरt);
	sclk_dpm_tdp_limit |= (tdp_limit << shअगरt);
	WREG32_RCU(regoffset, sclk_dpm_tdp_limit);
पूर्ण

व्योम sumo_boost_state_enable(काष्ठा radeon_device *rdev, bool enable)
अणु
	u32 boost_disable = RREG32_RCU(RCU_GPU_BOOST_DISABLE);

	boost_disable &= 0xFFFFFFFE;
	boost_disable |= (enable ? 0 : 1);
	WREG32_RCU(RCU_GPU_BOOST_DISABLE, boost_disable);
पूर्ण

u32 sumo_get_running_fw_version(काष्ठा radeon_device *rdev)
अणु
	वापस RREG32_RCU(RCU_FW_VERSION);
पूर्ण

