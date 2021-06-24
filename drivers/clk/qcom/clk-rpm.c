<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2016, Linaro Limited
 * Copyright (c) 2014, The Linux Foundation. All rights reserved.
 */

#समावेश <linux/clk-provider.h>
#समावेश <linux/err.h>
#समावेश <linux/export.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/mfd/qcom_rpm.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश <dt-bindings/mfd/qcom-rpm.h>
#समावेश <dt-bindings/घड़ी/qcom,rpmcc.h>

#घोषणा QCOM_RPM_MISC_CLK_TYPE				0x306b6c63
#घोषणा QCOM_RPM_SCALING_ENABLE_ID			0x2
#घोषणा QCOM_RPM_XO_MODE_ON				0x2

#घोषणा DEFINE_CLK_RPM(_platक्रमm, _name, _active, r_id)			      \
	अटल काष्ठा clk_rpm _platक्रमm##_##_active;			      \
	अटल काष्ठा clk_rpm _platक्रमm##_##_name = अणु			      \
		.rpm_clk_id = (r_id),					      \
		.peer = &_platक्रमm##_##_active,				      \
		.rate = पूर्णांक_उच्च,					      \
		.hw.init = &(काष्ठा clk_init_data)अणु			      \
			.ops = &clk_rpm_ops,				      \
			.name = #_name,					      \
			.parent_names = (स्थिर अक्षर *[])अणु "pxo_board" पूर्ण,      \
			.num_parents = 1,				      \
		पूर्ण,							      \
	पूर्ण;								      \
	अटल काष्ठा clk_rpm _platक्रमm##_##_active = अणु			      \
		.rpm_clk_id = (r_id),					      \
		.peer = &_platक्रमm##_##_name,				      \
		.active_only = true,					      \
		.rate = पूर्णांक_उच्च,					      \
		.hw.init = &(काष्ठा clk_init_data)अणु			      \
			.ops = &clk_rpm_ops,				      \
			.name = #_active,				      \
			.parent_names = (स्थिर अक्षर *[])अणु "pxo_board" पूर्ण,      \
			.num_parents = 1,				      \
		पूर्ण,							      \
	पूर्ण

#घोषणा DEFINE_CLK_RPM_XO_BUFFER(_platक्रमm, _name, _active, offset)	      \
	अटल काष्ठा clk_rpm _platक्रमm##_##_name = अणु			      \
		.rpm_clk_id = QCOM_RPM_CXO_BUFFERS,			      \
		.xo_offset = (offset),					      \
		.hw.init = &(काष्ठा clk_init_data)अणु			      \
			.ops = &clk_rpm_xo_ops,			      \
			.name = #_name,					      \
			.parent_names = (स्थिर अक्षर *[])अणु "cxo_board" पूर्ण,      \
			.num_parents = 1,				      \
		पूर्ण,							      \
	पूर्ण

#घोषणा DEFINE_CLK_RPM_FIXED(_platक्रमm, _name, _active, r_id, r)	      \
	अटल काष्ठा clk_rpm _platक्रमm##_##_name = अणु			      \
		.rpm_clk_id = (r_id),					      \
		.rate = (r),						      \
		.hw.init = &(काष्ठा clk_init_data)अणु			      \
			.ops = &clk_rpm_fixed_ops,			      \
			.name = #_name,					      \
			.parent_names = (स्थिर अक्षर *[])अणु "pxo" पूर्ण,	      \
			.num_parents = 1,				      \
		पूर्ण,							      \
	पूर्ण

#घोषणा to_clk_rpm(_hw) container_of(_hw, काष्ठा clk_rpm, hw)

काष्ठा rpm_cc;

काष्ठा clk_rpm अणु
	स्थिर पूर्णांक rpm_clk_id;
	स्थिर पूर्णांक xo_offset;
	स्थिर bool active_only;
	अचिन्हित दीर्घ rate;
	bool enabled;
	bool branch;
	काष्ठा clk_rpm *peer;
	काष्ठा clk_hw hw;
	काष्ठा qcom_rpm *rpm;
	काष्ठा rpm_cc *rpm_cc;
पूर्ण;

काष्ठा rpm_cc अणु
	काष्ठा qcom_rpm *rpm;
	काष्ठा clk_rpm **clks;
	माप_प्रकार num_clks;
	u32 xo_buffer_value;
	काष्ठा mutex xo_lock;
पूर्ण;

काष्ठा rpm_clk_desc अणु
	काष्ठा clk_rpm **clks;
	माप_प्रकार num_clks;
पूर्ण;

अटल DEFINE_MUTEX(rpm_clk_lock);

अटल पूर्णांक clk_rpm_hanकरोff(काष्ठा clk_rpm *r)
अणु
	पूर्णांक ret;
	u32 value = पूर्णांक_उच्च;

	/*
	 * The venकरोr tree simply पढ़ोs the status क्रम this
	 * RPM घड़ी.
	 */
	अगर (r->rpm_clk_id == QCOM_RPM_PLL_4 ||
		r->rpm_clk_id == QCOM_RPM_CXO_BUFFERS)
		वापस 0;

	ret = qcom_rpm_ग_लिखो(r->rpm, QCOM_RPM_ACTIVE_STATE,
			     r->rpm_clk_id, &value, 1);
	अगर (ret)
		वापस ret;
	ret = qcom_rpm_ग_लिखो(r->rpm, QCOM_RPM_SLEEP_STATE,
			     r->rpm_clk_id, &value, 1);
	अगर (ret)
		वापस ret;

	वापस 0;
पूर्ण

अटल पूर्णांक clk_rpm_set_rate_active(काष्ठा clk_rpm *r, अचिन्हित दीर्घ rate)
अणु
	u32 value = DIV_ROUND_UP(rate, 1000); /* to kHz */

	वापस qcom_rpm_ग_लिखो(r->rpm, QCOM_RPM_ACTIVE_STATE,
			      r->rpm_clk_id, &value, 1);
पूर्ण

अटल पूर्णांक clk_rpm_set_rate_sleep(काष्ठा clk_rpm *r, अचिन्हित दीर्घ rate)
अणु
	u32 value = DIV_ROUND_UP(rate, 1000); /* to kHz */

	वापस qcom_rpm_ग_लिखो(r->rpm, QCOM_RPM_SLEEP_STATE,
			      r->rpm_clk_id, &value, 1);
पूर्ण

अटल व्योम to_active_sleep(काष्ठा clk_rpm *r, अचिन्हित दीर्घ rate,
			    अचिन्हित दीर्घ *active, अचिन्हित दीर्घ *sleep)
अणु
	*active = rate;

	/*
	 * Active-only घड़ीs करोn't care what the rate is during sleep. So,
	 * they vote क्रम zero.
	 */
	अगर (r->active_only)
		*sleep = 0;
	अन्यथा
		*sleep = *active;
पूर्ण

अटल पूर्णांक clk_rpm_prepare(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_rpm *r = to_clk_rpm(hw);
	काष्ठा clk_rpm *peer = r->peer;
	अचिन्हित दीर्घ this_rate = 0, this_sleep_rate = 0;
	अचिन्हित दीर्घ peer_rate = 0, peer_sleep_rate = 0;
	अचिन्हित दीर्घ active_rate, sleep_rate;
	पूर्णांक ret = 0;

	mutex_lock(&rpm_clk_lock);

	/* Don't send requests to the RPM अगर the rate has not been set. */
	अगर (!r->rate)
		जाओ out;

	to_active_sleep(r, r->rate, &this_rate, &this_sleep_rate);

	/* Take peer घड़ी's rate into account only if it's enabled. */
	अगर (peer->enabled)
		to_active_sleep(peer, peer->rate,
				&peer_rate, &peer_sleep_rate);

	active_rate = max(this_rate, peer_rate);

	अगर (r->branch)
		active_rate = !!active_rate;

	ret = clk_rpm_set_rate_active(r, active_rate);
	अगर (ret)
		जाओ out;

	sleep_rate = max(this_sleep_rate, peer_sleep_rate);
	अगर (r->branch)
		sleep_rate = !!sleep_rate;

	ret = clk_rpm_set_rate_sleep(r, sleep_rate);
	अगर (ret)
		/* Unकरो the active set vote and restore it */
		ret = clk_rpm_set_rate_active(r, peer_rate);

out:
	अगर (!ret)
		r->enabled = true;

	mutex_unlock(&rpm_clk_lock);

	वापस ret;
पूर्ण

अटल व्योम clk_rpm_unprepare(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_rpm *r = to_clk_rpm(hw);
	काष्ठा clk_rpm *peer = r->peer;
	अचिन्हित दीर्घ peer_rate = 0, peer_sleep_rate = 0;
	अचिन्हित दीर्घ active_rate, sleep_rate;
	पूर्णांक ret;

	mutex_lock(&rpm_clk_lock);

	अगर (!r->rate)
		जाओ out;

	/* Take peer घड़ी's rate into account only if it's enabled. */
	अगर (peer->enabled)
		to_active_sleep(peer, peer->rate, &peer_rate,
				&peer_sleep_rate);

	active_rate = r->branch ? !!peer_rate : peer_rate;
	ret = clk_rpm_set_rate_active(r, active_rate);
	अगर (ret)
		जाओ out;

	sleep_rate = r->branch ? !!peer_sleep_rate : peer_sleep_rate;
	ret = clk_rpm_set_rate_sleep(r, sleep_rate);
	अगर (ret)
		जाओ out;

	r->enabled = false;

out:
	mutex_unlock(&rpm_clk_lock);
पूर्ण

अटल पूर्णांक clk_rpm_xo_prepare(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_rpm *r = to_clk_rpm(hw);
	काष्ठा rpm_cc *rcc = r->rpm_cc;
	पूर्णांक ret, clk_id = r->rpm_clk_id;
	u32 value;

	mutex_lock(&rcc->xo_lock);

	value = rcc->xo_buffer_value | (QCOM_RPM_XO_MODE_ON << r->xo_offset);
	ret = qcom_rpm_ग_लिखो(r->rpm, QCOM_RPM_ACTIVE_STATE, clk_id, &value, 1);
	अगर (!ret) अणु
		r->enabled = true;
		rcc->xo_buffer_value = value;
	पूर्ण

	mutex_unlock(&rcc->xo_lock);

	वापस ret;
पूर्ण

अटल व्योम clk_rpm_xo_unprepare(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_rpm *r = to_clk_rpm(hw);
	काष्ठा rpm_cc *rcc = r->rpm_cc;
	पूर्णांक ret, clk_id = r->rpm_clk_id;
	u32 value;

	mutex_lock(&rcc->xo_lock);

	value = rcc->xo_buffer_value & ~(QCOM_RPM_XO_MODE_ON << r->xo_offset);
	ret = qcom_rpm_ग_लिखो(r->rpm, QCOM_RPM_ACTIVE_STATE, clk_id, &value, 1);
	अगर (!ret) अणु
		r->enabled = false;
		rcc->xo_buffer_value = value;
	पूर्ण

	mutex_unlock(&rcc->xo_lock);
पूर्ण

अटल पूर्णांक clk_rpm_fixed_prepare(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_rpm *r = to_clk_rpm(hw);
	u32 value = 1;
	पूर्णांक ret;

	ret = qcom_rpm_ग_लिखो(r->rpm, QCOM_RPM_ACTIVE_STATE,
			     r->rpm_clk_id, &value, 1);
	अगर (!ret)
		r->enabled = true;

	वापस ret;
पूर्ण

अटल व्योम clk_rpm_fixed_unprepare(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_rpm *r = to_clk_rpm(hw);
	u32 value = 0;
	पूर्णांक ret;

	ret = qcom_rpm_ग_लिखो(r->rpm, QCOM_RPM_ACTIVE_STATE,
			     r->rpm_clk_id, &value, 1);
	अगर (!ret)
		r->enabled = false;
पूर्ण

अटल पूर्णांक clk_rpm_set_rate(काष्ठा clk_hw *hw,
			    अचिन्हित दीर्घ rate, अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा clk_rpm *r = to_clk_rpm(hw);
	काष्ठा clk_rpm *peer = r->peer;
	अचिन्हित दीर्घ active_rate, sleep_rate;
	अचिन्हित दीर्घ this_rate = 0, this_sleep_rate = 0;
	अचिन्हित दीर्घ peer_rate = 0, peer_sleep_rate = 0;
	पूर्णांक ret = 0;

	mutex_lock(&rpm_clk_lock);

	अगर (!r->enabled)
		जाओ out;

	to_active_sleep(r, rate, &this_rate, &this_sleep_rate);

	/* Take peer घड़ी's rate into account only if it's enabled. */
	अगर (peer->enabled)
		to_active_sleep(peer, peer->rate,
				&peer_rate, &peer_sleep_rate);

	active_rate = max(this_rate, peer_rate);
	ret = clk_rpm_set_rate_active(r, active_rate);
	अगर (ret)
		जाओ out;

	sleep_rate = max(this_sleep_rate, peer_sleep_rate);
	ret = clk_rpm_set_rate_sleep(r, sleep_rate);
	अगर (ret)
		जाओ out;

	r->rate = rate;

out:
	mutex_unlock(&rpm_clk_lock);

	वापस ret;
पूर्ण

अटल दीर्घ clk_rpm_round_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
			       अचिन्हित दीर्घ *parent_rate)
अणु
	/*
	 * RPM handles rate rounding and we करोn't have a way to
	 * know what the rate will be, so just वापस whatever
	 * rate is requested.
	 */
	वापस rate;
पूर्ण

अटल अचिन्हित दीर्घ clk_rpm_recalc_rate(काष्ठा clk_hw *hw,
					 अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा clk_rpm *r = to_clk_rpm(hw);

	/*
	 * RPM handles rate rounding and we करोn't have a way to
	 * know what the rate will be, so just वापस whatever
	 * rate was set.
	 */
	वापस r->rate;
पूर्ण

अटल स्थिर काष्ठा clk_ops clk_rpm_xo_ops = अणु
	.prepare	= clk_rpm_xo_prepare,
	.unprepare	= clk_rpm_xo_unprepare,
पूर्ण;

अटल स्थिर काष्ठा clk_ops clk_rpm_fixed_ops = अणु
	.prepare	= clk_rpm_fixed_prepare,
	.unprepare	= clk_rpm_fixed_unprepare,
	.round_rate	= clk_rpm_round_rate,
	.recalc_rate	= clk_rpm_recalc_rate,
पूर्ण;

अटल स्थिर काष्ठा clk_ops clk_rpm_ops = अणु
	.prepare	= clk_rpm_prepare,
	.unprepare	= clk_rpm_unprepare,
	.set_rate	= clk_rpm_set_rate,
	.round_rate	= clk_rpm_round_rate,
	.recalc_rate	= clk_rpm_recalc_rate,
पूर्ण;

/* MSM8660/APQ8060 */
DEFINE_CLK_RPM(msm8660, afab_clk, afab_a_clk, QCOM_RPM_APPS_FABRIC_CLK);
DEFINE_CLK_RPM(msm8660, sfab_clk, sfab_a_clk, QCOM_RPM_SYS_FABRIC_CLK);
DEFINE_CLK_RPM(msm8660, mmfab_clk, mmfab_a_clk, QCOM_RPM_MM_FABRIC_CLK);
DEFINE_CLK_RPM(msm8660, daytona_clk, daytona_a_clk, QCOM_RPM_DAYTONA_FABRIC_CLK);
DEFINE_CLK_RPM(msm8660, sfpb_clk, sfpb_a_clk, QCOM_RPM_SFPB_CLK);
DEFINE_CLK_RPM(msm8660, cfpb_clk, cfpb_a_clk, QCOM_RPM_CFPB_CLK);
DEFINE_CLK_RPM(msm8660, mmfpb_clk, mmfpb_a_clk, QCOM_RPM_MMFPB_CLK);
DEFINE_CLK_RPM(msm8660, smi_clk, smi_a_clk, QCOM_RPM_SMI_CLK);
DEFINE_CLK_RPM(msm8660, ebi1_clk, ebi1_a_clk, QCOM_RPM_EBI1_CLK);
DEFINE_CLK_RPM_FIXED(msm8660, pll4_clk, pll4_a_clk, QCOM_RPM_PLL_4, 540672000);

अटल काष्ठा clk_rpm *msm8660_clks[] = अणु
	[RPM_APPS_FABRIC_CLK] = &msm8660_afab_clk,
	[RPM_APPS_FABRIC_A_CLK] = &msm8660_afab_a_clk,
	[RPM_SYS_FABRIC_CLK] = &msm8660_sfab_clk,
	[RPM_SYS_FABRIC_A_CLK] = &msm8660_sfab_a_clk,
	[RPM_MM_FABRIC_CLK] = &msm8660_mmfab_clk,
	[RPM_MM_FABRIC_A_CLK] = &msm8660_mmfab_a_clk,
	[RPM_DAYTONA_FABRIC_CLK] = &msm8660_daytona_clk,
	[RPM_DAYTONA_FABRIC_A_CLK] = &msm8660_daytona_a_clk,
	[RPM_SFPB_CLK] = &msm8660_sfpb_clk,
	[RPM_SFPB_A_CLK] = &msm8660_sfpb_a_clk,
	[RPM_CFPB_CLK] = &msm8660_cfpb_clk,
	[RPM_CFPB_A_CLK] = &msm8660_cfpb_a_clk,
	[RPM_MMFPB_CLK] = &msm8660_mmfpb_clk,
	[RPM_MMFPB_A_CLK] = &msm8660_mmfpb_a_clk,
	[RPM_SMI_CLK] = &msm8660_smi_clk,
	[RPM_SMI_A_CLK] = &msm8660_smi_a_clk,
	[RPM_EBI1_CLK] = &msm8660_ebi1_clk,
	[RPM_EBI1_A_CLK] = &msm8660_ebi1_a_clk,
	[RPM_PLL4_CLK] = &msm8660_pll4_clk,
पूर्ण;

अटल स्थिर काष्ठा rpm_clk_desc rpm_clk_msm8660 = अणु
	.clks = msm8660_clks,
	.num_clks = ARRAY_SIZE(msm8660_clks),
पूर्ण;

/* apq8064 */
DEFINE_CLK_RPM(apq8064, afab_clk, afab_a_clk, QCOM_RPM_APPS_FABRIC_CLK);
DEFINE_CLK_RPM(apq8064, cfpb_clk, cfpb_a_clk, QCOM_RPM_CFPB_CLK);
DEFINE_CLK_RPM(apq8064, daytona_clk, daytona_a_clk, QCOM_RPM_DAYTONA_FABRIC_CLK);
DEFINE_CLK_RPM(apq8064, ebi1_clk, ebi1_a_clk, QCOM_RPM_EBI1_CLK);
DEFINE_CLK_RPM(apq8064, mmfab_clk, mmfab_a_clk, QCOM_RPM_MM_FABRIC_CLK);
DEFINE_CLK_RPM(apq8064, mmfpb_clk, mmfpb_a_clk, QCOM_RPM_MMFPB_CLK);
DEFINE_CLK_RPM(apq8064, sfab_clk, sfab_a_clk, QCOM_RPM_SYS_FABRIC_CLK);
DEFINE_CLK_RPM(apq8064, sfpb_clk, sfpb_a_clk, QCOM_RPM_SFPB_CLK);
DEFINE_CLK_RPM(apq8064, qdss_clk, qdss_a_clk, QCOM_RPM_QDSS_CLK);
DEFINE_CLK_RPM_XO_BUFFER(apq8064, xo_d0_clk, xo_d0_a_clk, 0);
DEFINE_CLK_RPM_XO_BUFFER(apq8064, xo_d1_clk, xo_d1_a_clk, 8);
DEFINE_CLK_RPM_XO_BUFFER(apq8064, xo_a0_clk, xo_a0_a_clk, 16);
DEFINE_CLK_RPM_XO_BUFFER(apq8064, xo_a1_clk, xo_a1_a_clk, 24);
DEFINE_CLK_RPM_XO_BUFFER(apq8064, xo_a2_clk, xo_a2_a_clk, 28);

अटल काष्ठा clk_rpm *apq8064_clks[] = अणु
	[RPM_APPS_FABRIC_CLK] = &apq8064_afab_clk,
	[RPM_APPS_FABRIC_A_CLK] = &apq8064_afab_a_clk,
	[RPM_CFPB_CLK] = &apq8064_cfpb_clk,
	[RPM_CFPB_A_CLK] = &apq8064_cfpb_a_clk,
	[RPM_DAYTONA_FABRIC_CLK] = &apq8064_daytona_clk,
	[RPM_DAYTONA_FABRIC_A_CLK] = &apq8064_daytona_a_clk,
	[RPM_EBI1_CLK] = &apq8064_ebi1_clk,
	[RPM_EBI1_A_CLK] = &apq8064_ebi1_a_clk,
	[RPM_MM_FABRIC_CLK] = &apq8064_mmfab_clk,
	[RPM_MM_FABRIC_A_CLK] = &apq8064_mmfab_a_clk,
	[RPM_MMFPB_CLK] = &apq8064_mmfpb_clk,
	[RPM_MMFPB_A_CLK] = &apq8064_mmfpb_a_clk,
	[RPM_SYS_FABRIC_CLK] = &apq8064_sfab_clk,
	[RPM_SYS_FABRIC_A_CLK] = &apq8064_sfab_a_clk,
	[RPM_SFPB_CLK] = &apq8064_sfpb_clk,
	[RPM_SFPB_A_CLK] = &apq8064_sfpb_a_clk,
	[RPM_QDSS_CLK] = &apq8064_qdss_clk,
	[RPM_QDSS_A_CLK] = &apq8064_qdss_a_clk,
	[RPM_XO_D0] = &apq8064_xo_d0_clk,
	[RPM_XO_D1] = &apq8064_xo_d1_clk,
	[RPM_XO_A0] = &apq8064_xo_a0_clk,
	[RPM_XO_A1] = &apq8064_xo_a1_clk,
	[RPM_XO_A2] = &apq8064_xo_a2_clk,
पूर्ण;

अटल स्थिर काष्ठा rpm_clk_desc rpm_clk_apq8064 = अणु
	.clks = apq8064_clks,
	.num_clks = ARRAY_SIZE(apq8064_clks),
पूर्ण;

/* ipq806x */
DEFINE_CLK_RPM(ipq806x, afab_clk, afab_a_clk, QCOM_RPM_APPS_FABRIC_CLK);
DEFINE_CLK_RPM(ipq806x, cfpb_clk, cfpb_a_clk, QCOM_RPM_CFPB_CLK);
DEFINE_CLK_RPM(ipq806x, daytona_clk, daytona_a_clk, QCOM_RPM_DAYTONA_FABRIC_CLK);
DEFINE_CLK_RPM(ipq806x, ebi1_clk, ebi1_a_clk, QCOM_RPM_EBI1_CLK);
DEFINE_CLK_RPM(ipq806x, sfab_clk, sfab_a_clk, QCOM_RPM_SYS_FABRIC_CLK);
DEFINE_CLK_RPM(ipq806x, sfpb_clk, sfpb_a_clk, QCOM_RPM_SFPB_CLK);
DEFINE_CLK_RPM(ipq806x, nss_fabric_0_clk, nss_fabric_0_a_clk, QCOM_RPM_NSS_FABRIC_0_CLK);
DEFINE_CLK_RPM(ipq806x, nss_fabric_1_clk, nss_fabric_1_a_clk, QCOM_RPM_NSS_FABRIC_1_CLK);

अटल काष्ठा clk_rpm *ipq806x_clks[] = अणु
	[RPM_APPS_FABRIC_CLK] = &ipq806x_afab_clk,
	[RPM_APPS_FABRIC_A_CLK] = &ipq806x_afab_a_clk,
	[RPM_CFPB_CLK] = &ipq806x_cfpb_clk,
	[RPM_CFPB_A_CLK] = &ipq806x_cfpb_a_clk,
	[RPM_DAYTONA_FABRIC_CLK] = &ipq806x_daytona_clk,
	[RPM_DAYTONA_FABRIC_A_CLK] = &ipq806x_daytona_a_clk,
	[RPM_EBI1_CLK] = &ipq806x_ebi1_clk,
	[RPM_EBI1_A_CLK] = &ipq806x_ebi1_a_clk,
	[RPM_SYS_FABRIC_CLK] = &ipq806x_sfab_clk,
	[RPM_SYS_FABRIC_A_CLK] = &ipq806x_sfab_a_clk,
	[RPM_SFPB_CLK] = &ipq806x_sfpb_clk,
	[RPM_SFPB_A_CLK] = &ipq806x_sfpb_a_clk,
	[RPM_NSS_FABRIC_0_CLK] = &ipq806x_nss_fabric_0_clk,
	[RPM_NSS_FABRIC_0_A_CLK] = &ipq806x_nss_fabric_0_a_clk,
	[RPM_NSS_FABRIC_1_CLK] = &ipq806x_nss_fabric_1_clk,
	[RPM_NSS_FABRIC_1_A_CLK] = &ipq806x_nss_fabric_1_a_clk,
पूर्ण;

अटल स्थिर काष्ठा rpm_clk_desc rpm_clk_ipq806x = अणु
	.clks = ipq806x_clks,
	.num_clks = ARRAY_SIZE(ipq806x_clks),
पूर्ण;

अटल स्थिर काष्ठा of_device_id rpm_clk_match_table[] = अणु
	अणु .compatible = "qcom,rpmcc-msm8660", .data = &rpm_clk_msm8660 पूर्ण,
	अणु .compatible = "qcom,rpmcc-apq8060", .data = &rpm_clk_msm8660 पूर्ण,
	अणु .compatible = "qcom,rpmcc-apq8064", .data = &rpm_clk_apq8064 पूर्ण,
	अणु .compatible = "qcom,rpmcc-ipq806x", .data = &rpm_clk_ipq806x पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, rpm_clk_match_table);

अटल काष्ठा clk_hw *qcom_rpm_clk_hw_get(काष्ठा of_phandle_args *clkspec,
					  व्योम *data)
अणु
	काष्ठा rpm_cc *rcc = data;
	अचिन्हित पूर्णांक idx = clkspec->args[0];

	अगर (idx >= rcc->num_clks) अणु
		pr_err("%s: invalid index %u\n", __func__, idx);
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	वापस rcc->clks[idx] ? &rcc->clks[idx]->hw : ERR_PTR(-ENOENT);
पूर्ण

अटल पूर्णांक rpm_clk_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा rpm_cc *rcc;
	पूर्णांक ret;
	माप_प्रकार num_clks, i;
	काष्ठा qcom_rpm *rpm;
	काष्ठा clk_rpm **rpm_clks;
	स्थिर काष्ठा rpm_clk_desc *desc;

	rpm = dev_get_drvdata(pdev->dev.parent);
	अगर (!rpm) अणु
		dev_err(&pdev->dev, "Unable to retrieve handle to RPM\n");
		वापस -ENODEV;
	पूर्ण

	desc = of_device_get_match_data(&pdev->dev);
	अगर (!desc)
		वापस -EINVAL;

	rpm_clks = desc->clks;
	num_clks = desc->num_clks;

	rcc = devm_kzalloc(&pdev->dev, माप(*rcc), GFP_KERNEL);
	अगर (!rcc)
		वापस -ENOMEM;

	rcc->clks = rpm_clks;
	rcc->num_clks = num_clks;
	mutex_init(&rcc->xo_lock);

	क्रम (i = 0; i < num_clks; i++) अणु
		अगर (!rpm_clks[i])
			जारी;

		rpm_clks[i]->rpm = rpm;
		rpm_clks[i]->rpm_cc = rcc;

		ret = clk_rpm_hanकरोff(rpm_clks[i]);
		अगर (ret)
			जाओ err;
	पूर्ण

	क्रम (i = 0; i < num_clks; i++) अणु
		अगर (!rpm_clks[i])
			जारी;

		ret = devm_clk_hw_रेजिस्टर(&pdev->dev, &rpm_clks[i]->hw);
		अगर (ret)
			जाओ err;
	पूर्ण

	ret = of_clk_add_hw_provider(pdev->dev.of_node, qcom_rpm_clk_hw_get,
				     rcc);
	अगर (ret)
		जाओ err;

	वापस 0;
err:
	dev_err(&pdev->dev, "Error registering RPM Clock driver (%d)\n", ret);
	वापस ret;
पूर्ण

अटल पूर्णांक rpm_clk_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	of_clk_del_provider(pdev->dev.of_node);
	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver rpm_clk_driver = अणु
	.driver = अणु
		.name = "qcom-clk-rpm",
		.of_match_table = rpm_clk_match_table,
	पूर्ण,
	.probe = rpm_clk_probe,
	.हटाओ = rpm_clk_हटाओ,
पूर्ण;

अटल पूर्णांक __init rpm_clk_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&rpm_clk_driver);
पूर्ण
core_initcall(rpm_clk_init);

अटल व्योम __निकास rpm_clk_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&rpm_clk_driver);
पूर्ण
module_निकास(rpm_clk_निकास);

MODULE_DESCRIPTION("Qualcomm RPM Clock Controller Driver");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:qcom-clk-rpm");
