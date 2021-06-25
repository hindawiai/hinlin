<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2018-2021, The Linux Foundation. All rights reserved.
 */

#समावेश <linux/clk-provider.h>
#समावेश <linux/err.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <soc/qcom/cmd-db.h>
#समावेश <soc/qcom/rpmh.h>
#समावेश <soc/qcom/tcs.h>

#समावेश <dt-bindings/घड़ी/qcom,rpmh.h>

#घोषणा CLK_RPMH_ARC_EN_OFFSET		0
#घोषणा CLK_RPMH_VRM_EN_OFFSET		4

/**
 * काष्ठा bcm_db - Auxiliary data pertaining to each Bus Clock Manager(BCM)
 * @unit: भागisor used to convert Hz value to an RPMh msg
 * @width: multiplier used to convert Hz value to an RPMh msg
 * @vcd: भव घड़ी करोमुख्य that this bcm beदीर्घs to
 * @reserved: reserved to pad the काष्ठा
 */
काष्ठा bcm_db अणु
	__le32 unit;
	__le16 width;
	u8 vcd;
	u8 reserved;
पूर्ण;

/**
 * काष्ठा clk_rpmh - inभागidual rpmh घड़ी data काष्ठाure
 * @hw:			handle between common and hardware-specअगरic पूर्णांकerfaces
 * @res_name:		resource name क्रम the rpmh घड़ी
 * @भाग:		घड़ी भागider to compute the घड़ी rate
 * @res_addr:		base address of the rpmh resource within the RPMh
 * @res_on_val:		rpmh घड़ी enable value
 * @state:		rpmh घड़ी requested state
 * @aggr_state:		rpmh घड़ी aggregated state
 * @last_sent_aggr_state: rpmh घड़ी last aggr state sent to RPMh
 * @valid_state_mask:	mask to determine the state of the rpmh घड़ी
 * @unit:		भागisor to convert rate to rpmh msg in magnitudes of Khz
 * @dev:		device to which it is attached
 * @peer:		poपूर्णांकer to the घड़ी rpmh sibling
 */
काष्ठा clk_rpmh अणु
	काष्ठा clk_hw hw;
	स्थिर अक्षर *res_name;
	u8 भाग;
	u32 res_addr;
	u32 res_on_val;
	u32 state;
	u32 aggr_state;
	u32 last_sent_aggr_state;
	u32 valid_state_mask;
	u32 unit;
	काष्ठा device *dev;
	काष्ठा clk_rpmh *peer;
पूर्ण;

काष्ठा clk_rpmh_desc अणु
	काष्ठा clk_hw **clks;
	माप_प्रकार num_clks;
पूर्ण;

अटल DEFINE_MUTEX(rpmh_clk_lock);

#घोषणा __DEFINE_CLK_RPMH(_platक्रमm, _name, _name_active, _res_name,	\
			  _res_en_offset, _res_on, _भाग)		\
	अटल काष्ठा clk_rpmh _platक्रमm##_##_name_active;		\
	अटल काष्ठा clk_rpmh _platक्रमm##_##_name = अणु			\
		.res_name = _res_name,					\
		.res_addr = _res_en_offset,				\
		.res_on_val = _res_on,					\
		.भाग = _भाग,						\
		.peer = &_platक्रमm##_##_name_active,			\
		.valid_state_mask = (BIT(RPMH_WAKE_ONLY_STATE) |	\
				      BIT(RPMH_ACTIVE_ONLY_STATE) |	\
				      BIT(RPMH_SLEEP_STATE)),		\
		.hw.init = &(काष्ठा clk_init_data)अणु			\
			.ops = &clk_rpmh_ops,				\
			.name = #_name,					\
			.parent_data =  &(स्थिर काष्ठा clk_parent_data)अणु \
					.fw_name = "xo",		\
					.name = "xo_board",		\
			पूर्ण,						\
			.num_parents = 1,				\
		पूर्ण,							\
	पूर्ण;								\
	अटल काष्ठा clk_rpmh _platक्रमm##_##_name_active = अणु		\
		.res_name = _res_name,					\
		.res_addr = _res_en_offset,				\
		.res_on_val = _res_on,					\
		.भाग = _भाग,						\
		.peer = &_platक्रमm##_##_name,				\
		.valid_state_mask = (BIT(RPMH_WAKE_ONLY_STATE) |	\
					BIT(RPMH_ACTIVE_ONLY_STATE)),	\
		.hw.init = &(काष्ठा clk_init_data)अणु			\
			.ops = &clk_rpmh_ops,				\
			.name = #_name_active,				\
			.parent_data =  &(स्थिर काष्ठा clk_parent_data)अणु \
					.fw_name = "xo",		\
					.name = "xo_board",		\
			पूर्ण,						\
			.num_parents = 1,				\
		पूर्ण,							\
	पूर्ण

#घोषणा DEFINE_CLK_RPMH_ARC(_platक्रमm, _name, _name_active, _res_name,	\
			    _res_on, _भाग)				\
	__DEFINE_CLK_RPMH(_platक्रमm, _name, _name_active, _res_name,	\
			  CLK_RPMH_ARC_EN_OFFSET, _res_on, _भाग)

#घोषणा DEFINE_CLK_RPMH_VRM(_platक्रमm, _name, _name_active, _res_name,	\
				_भाग)					\
	__DEFINE_CLK_RPMH(_platक्रमm, _name, _name_active, _res_name,	\
			  CLK_RPMH_VRM_EN_OFFSET, 1, _भाग)

#घोषणा DEFINE_CLK_RPMH_BCM(_platक्रमm, _name, _res_name)		\
	अटल काष्ठा clk_rpmh _platक्रमm##_##_name = अणु			\
		.res_name = _res_name,					\
		.valid_state_mask = BIT(RPMH_ACTIVE_ONLY_STATE),	\
		.भाग = 1,						\
		.hw.init = &(काष्ठा clk_init_data)अणु			\
			.ops = &clk_rpmh_bcm_ops,			\
			.name = #_name,					\
		पूर्ण,							\
	पूर्ण

अटल अंतरभूत काष्ठा clk_rpmh *to_clk_rpmh(काष्ठा clk_hw *_hw)
अणु
	वापस container_of(_hw, काष्ठा clk_rpmh, hw);
पूर्ण

अटल अंतरभूत bool has_state_changed(काष्ठा clk_rpmh *c, u32 state)
अणु
	वापस (c->last_sent_aggr_state & BIT(state))
		!= (c->aggr_state & BIT(state));
पूर्ण

अटल पूर्णांक clk_rpmh_send(काष्ठा clk_rpmh *c, क्रमागत rpmh_state state,
			 काष्ठा tcs_cmd *cmd, bool रुको)
अणु
	अगर (रुको)
		वापस rpmh_ग_लिखो(c->dev, state, cmd, 1);

	वापस rpmh_ग_लिखो_async(c->dev, state, cmd, 1);
पूर्ण

अटल पूर्णांक clk_rpmh_send_aggregate_command(काष्ठा clk_rpmh *c)
अणु
	काष्ठा tcs_cmd cmd = अणु 0 पूर्ण;
	u32 cmd_state, on_val;
	क्रमागत rpmh_state state = RPMH_SLEEP_STATE;
	पूर्णांक ret;
	bool रुको;

	cmd.addr = c->res_addr;
	cmd_state = c->aggr_state;
	on_val = c->res_on_val;

	क्रम (; state <= RPMH_ACTIVE_ONLY_STATE; state++) अणु
		अगर (has_state_changed(c, state)) अणु
			अगर (cmd_state & BIT(state))
				cmd.data = on_val;

			रुको = cmd_state && state == RPMH_ACTIVE_ONLY_STATE;
			ret = clk_rpmh_send(c, state, &cmd, रुको);
			अगर (ret) अणु
				dev_err(c->dev, "set %s state of %s failed: (%d)\n",
					!state ? "sleep" :
					state == RPMH_WAKE_ONLY_STATE	?
					"wake" : "active", c->res_name, ret);
				वापस ret;
			पूर्ण
		पूर्ण
	पूर्ण

	c->last_sent_aggr_state = c->aggr_state;
	c->peer->last_sent_aggr_state =  c->last_sent_aggr_state;

	वापस 0;
पूर्ण

/*
 * Update state and aggregate state values based on enable value.
 */
अटल पूर्णांक clk_rpmh_aggregate_state_send_command(काष्ठा clk_rpmh *c,
						bool enable)
अणु
	पूर्णांक ret;

	/* Nothing required to be करोne अगर alपढ़ोy off or on */
	अगर (enable == c->state)
		वापस 0;

	c->state = enable ? c->valid_state_mask : 0;
	c->aggr_state = c->state | c->peer->state;
	c->peer->aggr_state = c->aggr_state;

	ret = clk_rpmh_send_aggregate_command(c);
	अगर (!ret)
		वापस 0;

	अगर (ret && enable)
		c->state = 0;
	अन्यथा अगर (ret)
		c->state = c->valid_state_mask;

	WARN(1, "clk: %s failed to %s\n", c->res_name,
	     enable ? "enable" : "disable");
	वापस ret;
पूर्ण

अटल पूर्णांक clk_rpmh_prepare(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_rpmh *c = to_clk_rpmh(hw);
	पूर्णांक ret = 0;

	mutex_lock(&rpmh_clk_lock);
	ret = clk_rpmh_aggregate_state_send_command(c, true);
	mutex_unlock(&rpmh_clk_lock);

	वापस ret;
पूर्ण

अटल व्योम clk_rpmh_unprepare(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_rpmh *c = to_clk_rpmh(hw);

	mutex_lock(&rpmh_clk_lock);
	clk_rpmh_aggregate_state_send_command(c, false);
	mutex_unlock(&rpmh_clk_lock);
पूर्ण;

अटल अचिन्हित दीर्घ clk_rpmh_recalc_rate(काष्ठा clk_hw *hw,
					अचिन्हित दीर्घ prate)
अणु
	काष्ठा clk_rpmh *r = to_clk_rpmh(hw);

	/*
	 * RPMh घड़ीs have a fixed rate. Return अटल rate.
	 */
	वापस prate / r->भाग;
पूर्ण

अटल स्थिर काष्ठा clk_ops clk_rpmh_ops = अणु
	.prepare	= clk_rpmh_prepare,
	.unprepare	= clk_rpmh_unprepare,
	.recalc_rate	= clk_rpmh_recalc_rate,
पूर्ण;

अटल पूर्णांक clk_rpmh_bcm_send_cmd(काष्ठा clk_rpmh *c, bool enable)
अणु
	काष्ठा tcs_cmd cmd = अणु 0 पूर्ण;
	u32 cmd_state;
	पूर्णांक ret = 0;

	mutex_lock(&rpmh_clk_lock);
	अगर (enable) अणु
		cmd_state = 1;
		अगर (c->aggr_state)
			cmd_state = c->aggr_state;
	पूर्ण अन्यथा अणु
		cmd_state = 0;
	पूर्ण

	अगर (c->last_sent_aggr_state != cmd_state) अणु
		cmd.addr = c->res_addr;
		cmd.data = BCM_TCS_CMD(1, enable, 0, cmd_state);

		ret = clk_rpmh_send(c, RPMH_ACTIVE_ONLY_STATE, &cmd, enable);
		अगर (ret) अणु
			dev_err(c->dev, "set active state of %s failed: (%d)\n",
				c->res_name, ret);
		पूर्ण अन्यथा अणु
			c->last_sent_aggr_state = cmd_state;
		पूर्ण
	पूर्ण

	mutex_unlock(&rpmh_clk_lock);

	वापस ret;
पूर्ण

अटल पूर्णांक clk_rpmh_bcm_prepare(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_rpmh *c = to_clk_rpmh(hw);

	वापस clk_rpmh_bcm_send_cmd(c, true);
पूर्ण

अटल व्योम clk_rpmh_bcm_unprepare(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_rpmh *c = to_clk_rpmh(hw);

	clk_rpmh_bcm_send_cmd(c, false);
पूर्ण

अटल पूर्णांक clk_rpmh_bcm_set_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
				 अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा clk_rpmh *c = to_clk_rpmh(hw);

	c->aggr_state = rate / c->unit;
	/*
	 * Since any non-zero value sent to hw would result in enabling the
	 * घड़ी, only send the value अगर the घड़ी has alपढ़ोy been prepared.
	 */
	अगर (clk_hw_is_prepared(hw))
		clk_rpmh_bcm_send_cmd(c, true);

	वापस 0;
पूर्ण

अटल दीर्घ clk_rpmh_round_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
				अचिन्हित दीर्घ *parent_rate)
अणु
	वापस rate;
पूर्ण

अटल अचिन्हित दीर्घ clk_rpmh_bcm_recalc_rate(काष्ठा clk_hw *hw,
					अचिन्हित दीर्घ prate)
अणु
	काष्ठा clk_rpmh *c = to_clk_rpmh(hw);

	वापस c->aggr_state * c->unit;
पूर्ण

अटल स्थिर काष्ठा clk_ops clk_rpmh_bcm_ops = अणु
	.prepare	= clk_rpmh_bcm_prepare,
	.unprepare	= clk_rpmh_bcm_unprepare,
	.set_rate	= clk_rpmh_bcm_set_rate,
	.round_rate	= clk_rpmh_round_rate,
	.recalc_rate	= clk_rpmh_bcm_recalc_rate,
पूर्ण;

/* Resource name must match resource id present in cmd-db */
DEFINE_CLK_RPMH_ARC(sdm845, bi_tcxo, bi_tcxo_ao, "xo.lvl", 0x3, 2);
DEFINE_CLK_RPMH_VRM(sdm845, ln_bb_clk2, ln_bb_clk2_ao, "lnbclka2", 2);
DEFINE_CLK_RPMH_VRM(sdm845, ln_bb_clk3, ln_bb_clk3_ao, "lnbclka3", 2);
DEFINE_CLK_RPMH_VRM(sdm845, rf_clk1, rf_clk1_ao, "rfclka1", 1);
DEFINE_CLK_RPMH_VRM(sdm845, rf_clk2, rf_clk2_ao, "rfclka2", 1);
DEFINE_CLK_RPMH_VRM(sdm845, rf_clk3, rf_clk3_ao, "rfclka3", 1);
DEFINE_CLK_RPMH_VRM(sm8150, rf_clk3, rf_clk3_ao, "rfclka3", 1);
DEFINE_CLK_RPMH_VRM(sc8180x, rf_clk1, rf_clk1_ao, "rfclkd1", 1);
DEFINE_CLK_RPMH_VRM(sc8180x, rf_clk2, rf_clk2_ao, "rfclkd2", 1);
DEFINE_CLK_RPMH_VRM(sc8180x, rf_clk3, rf_clk3_ao, "rfclkd3", 1);
DEFINE_CLK_RPMH_VRM(sc8180x, rf_clk4, rf_clk4_ao, "rfclkd4", 1);
DEFINE_CLK_RPMH_BCM(sdm845, ipa, "IP0");
DEFINE_CLK_RPMH_BCM(sdm845, ce, "CE0");

अटल काष्ठा clk_hw *sdm845_rpmh_घड़ीs[] = अणु
	[RPMH_CXO_CLK]		= &sdm845_bi_tcxo.hw,
	[RPMH_CXO_CLK_A]	= &sdm845_bi_tcxo_ao.hw,
	[RPMH_LN_BB_CLK2]	= &sdm845_ln_bb_clk2.hw,
	[RPMH_LN_BB_CLK2_A]	= &sdm845_ln_bb_clk2_ao.hw,
	[RPMH_LN_BB_CLK3]	= &sdm845_ln_bb_clk3.hw,
	[RPMH_LN_BB_CLK3_A]	= &sdm845_ln_bb_clk3_ao.hw,
	[RPMH_RF_CLK1]		= &sdm845_rf_clk1.hw,
	[RPMH_RF_CLK1_A]	= &sdm845_rf_clk1_ao.hw,
	[RPMH_RF_CLK2]		= &sdm845_rf_clk2.hw,
	[RPMH_RF_CLK2_A]	= &sdm845_rf_clk2_ao.hw,
	[RPMH_RF_CLK3]		= &sdm845_rf_clk3.hw,
	[RPMH_RF_CLK3_A]	= &sdm845_rf_clk3_ao.hw,
	[RPMH_IPA_CLK]		= &sdm845_ipa.hw,
	[RPMH_CE_CLK]		= &sdm845_ce.hw,
पूर्ण;

अटल स्थिर काष्ठा clk_rpmh_desc clk_rpmh_sdm845 = अणु
	.clks = sdm845_rpmh_घड़ीs,
	.num_clks = ARRAY_SIZE(sdm845_rpmh_घड़ीs),
पूर्ण;

DEFINE_CLK_RPMH_VRM(sdx55, rf_clk1, rf_clk1_ao, "rfclkd1", 1);
DEFINE_CLK_RPMH_VRM(sdx55, rf_clk2, rf_clk2_ao, "rfclkd2", 1);
DEFINE_CLK_RPMH_BCM(sdx55, qpic_clk, "QP0");
DEFINE_CLK_RPMH_BCM(sdx55, ipa, "IP0");

अटल काष्ठा clk_hw *sdx55_rpmh_घड़ीs[] = अणु
	[RPMH_CXO_CLK]		= &sdm845_bi_tcxo.hw,
	[RPMH_CXO_CLK_A]	= &sdm845_bi_tcxo_ao.hw,
	[RPMH_RF_CLK1]		= &sdx55_rf_clk1.hw,
	[RPMH_RF_CLK1_A]	= &sdx55_rf_clk1_ao.hw,
	[RPMH_RF_CLK2]		= &sdx55_rf_clk2.hw,
	[RPMH_RF_CLK2_A]	= &sdx55_rf_clk2_ao.hw,
	[RPMH_QPIC_CLK]		= &sdx55_qpic_clk.hw,
	[RPMH_IPA_CLK]		= &sdx55_ipa.hw,
पूर्ण;

अटल स्थिर काष्ठा clk_rpmh_desc clk_rpmh_sdx55 = अणु
	.clks = sdx55_rpmh_घड़ीs,
	.num_clks = ARRAY_SIZE(sdx55_rpmh_घड़ीs),
पूर्ण;

अटल काष्ठा clk_hw *sm8150_rpmh_घड़ीs[] = अणु
	[RPMH_CXO_CLK]		= &sdm845_bi_tcxo.hw,
	[RPMH_CXO_CLK_A]	= &sdm845_bi_tcxo_ao.hw,
	[RPMH_LN_BB_CLK2]	= &sdm845_ln_bb_clk2.hw,
	[RPMH_LN_BB_CLK2_A]	= &sdm845_ln_bb_clk2_ao.hw,
	[RPMH_LN_BB_CLK3]	= &sdm845_ln_bb_clk3.hw,
	[RPMH_LN_BB_CLK3_A]	= &sdm845_ln_bb_clk3_ao.hw,
	[RPMH_RF_CLK1]		= &sdm845_rf_clk1.hw,
	[RPMH_RF_CLK1_A]	= &sdm845_rf_clk1_ao.hw,
	[RPMH_RF_CLK2]		= &sdm845_rf_clk2.hw,
	[RPMH_RF_CLK2_A]	= &sdm845_rf_clk2_ao.hw,
	[RPMH_RF_CLK3]		= &sdm845_rf_clk3.hw,
	[RPMH_RF_CLK3_A]	= &sdm845_rf_clk3_ao.hw,
पूर्ण;

अटल स्थिर काष्ठा clk_rpmh_desc clk_rpmh_sm8150 = अणु
	.clks = sm8150_rpmh_घड़ीs,
	.num_clks = ARRAY_SIZE(sm8150_rpmh_घड़ीs),
पूर्ण;

अटल काष्ठा clk_hw *sc7180_rpmh_घड़ीs[] = अणु
	[RPMH_CXO_CLK]		= &sdm845_bi_tcxo.hw,
	[RPMH_CXO_CLK_A]	= &sdm845_bi_tcxo_ao.hw,
	[RPMH_LN_BB_CLK2]	= &sdm845_ln_bb_clk2.hw,
	[RPMH_LN_BB_CLK2_A]	= &sdm845_ln_bb_clk2_ao.hw,
	[RPMH_LN_BB_CLK3]	= &sdm845_ln_bb_clk3.hw,
	[RPMH_LN_BB_CLK3_A]	= &sdm845_ln_bb_clk3_ao.hw,
	[RPMH_RF_CLK1]		= &sdm845_rf_clk1.hw,
	[RPMH_RF_CLK1_A]	= &sdm845_rf_clk1_ao.hw,
	[RPMH_RF_CLK2]		= &sdm845_rf_clk2.hw,
	[RPMH_RF_CLK2_A]	= &sdm845_rf_clk2_ao.hw,
	[RPMH_IPA_CLK]		= &sdm845_ipa.hw,
पूर्ण;

अटल स्थिर काष्ठा clk_rpmh_desc clk_rpmh_sc7180 = अणु
	.clks = sc7180_rpmh_घड़ीs,
	.num_clks = ARRAY_SIZE(sc7180_rpmh_घड़ीs),
पूर्ण;

अटल काष्ठा clk_hw *sc8180x_rpmh_घड़ीs[] = अणु
	[RPMH_CXO_CLK]		= &sdm845_bi_tcxo.hw,
	[RPMH_CXO_CLK_A]	= &sdm845_bi_tcxo_ao.hw,
	[RPMH_LN_BB_CLK2]	= &sdm845_ln_bb_clk2.hw,
	[RPMH_LN_BB_CLK2_A]	= &sdm845_ln_bb_clk2_ao.hw,
	[RPMH_LN_BB_CLK3]	= &sdm845_ln_bb_clk3.hw,
	[RPMH_LN_BB_CLK3_A]	= &sdm845_ln_bb_clk3_ao.hw,
	[RPMH_RF_CLK1]		= &sc8180x_rf_clk1.hw,
	[RPMH_RF_CLK1_A]	= &sc8180x_rf_clk1_ao.hw,
	[RPMH_RF_CLK2]		= &sc8180x_rf_clk2.hw,
	[RPMH_RF_CLK2_A]	= &sc8180x_rf_clk2_ao.hw,
	[RPMH_RF_CLK3]		= &sc8180x_rf_clk3.hw,
	[RPMH_RF_CLK3_A]	= &sc8180x_rf_clk3_ao.hw,
पूर्ण;

अटल स्थिर काष्ठा clk_rpmh_desc clk_rpmh_sc8180x = अणु
	.clks = sc8180x_rpmh_घड़ीs,
	.num_clks = ARRAY_SIZE(sc8180x_rpmh_घड़ीs),
पूर्ण;

DEFINE_CLK_RPMH_VRM(sm8250, ln_bb_clk1, ln_bb_clk1_ao, "lnbclka1", 2);

अटल काष्ठा clk_hw *sm8250_rpmh_घड़ीs[] = अणु
	[RPMH_CXO_CLK]		= &sdm845_bi_tcxo.hw,
	[RPMH_CXO_CLK_A]	= &sdm845_bi_tcxo_ao.hw,
	[RPMH_LN_BB_CLK1]	= &sm8250_ln_bb_clk1.hw,
	[RPMH_LN_BB_CLK1_A]	= &sm8250_ln_bb_clk1_ao.hw,
	[RPMH_LN_BB_CLK2]	= &sdm845_ln_bb_clk2.hw,
	[RPMH_LN_BB_CLK2_A]	= &sdm845_ln_bb_clk2_ao.hw,
	[RPMH_LN_BB_CLK3]	= &sdm845_ln_bb_clk3.hw,
	[RPMH_LN_BB_CLK3_A]	= &sdm845_ln_bb_clk3_ao.hw,
	[RPMH_RF_CLK1]		= &sdm845_rf_clk1.hw,
	[RPMH_RF_CLK1_A]	= &sdm845_rf_clk1_ao.hw,
	[RPMH_RF_CLK3]		= &sdm845_rf_clk3.hw,
	[RPMH_RF_CLK3_A]	= &sdm845_rf_clk3_ao.hw,
पूर्ण;

अटल स्थिर काष्ठा clk_rpmh_desc clk_rpmh_sm8250 = अणु
	.clks = sm8250_rpmh_घड़ीs,
	.num_clks = ARRAY_SIZE(sm8250_rpmh_घड़ीs),
पूर्ण;

DEFINE_CLK_RPMH_VRM(sm8350, भाग_clk1, भाग_clk1_ao, "divclka1", 2);
DEFINE_CLK_RPMH_VRM(sm8350, rf_clk4, rf_clk4_ao, "rfclka4", 1);
DEFINE_CLK_RPMH_VRM(sm8350, rf_clk5, rf_clk5_ao, "rfclka5", 1);
DEFINE_CLK_RPMH_BCM(sm8350, pka, "PKA0");
DEFINE_CLK_RPMH_BCM(sm8350, hwkm, "HK0");

अटल काष्ठा clk_hw *sm8350_rpmh_घड़ीs[] = अणु
	[RPMH_CXO_CLK]		= &sdm845_bi_tcxo.hw,
	[RPMH_CXO_CLK_A]	= &sdm845_bi_tcxo_ao.hw,
	[RPMH_DIV_CLK1]		= &sm8350_भाग_clk1.hw,
	[RPMH_DIV_CLK1_A]	= &sm8350_भाग_clk1_ao.hw,
	[RPMH_LN_BB_CLK1]	= &sm8250_ln_bb_clk1.hw,
	[RPMH_LN_BB_CLK1_A]	= &sm8250_ln_bb_clk1_ao.hw,
	[RPMH_LN_BB_CLK2]	= &sdm845_ln_bb_clk2.hw,
	[RPMH_LN_BB_CLK2_A]	= &sdm845_ln_bb_clk2_ao.hw,
	[RPMH_RF_CLK1]		= &sdm845_rf_clk1.hw,
	[RPMH_RF_CLK1_A]	= &sdm845_rf_clk1_ao.hw,
	[RPMH_RF_CLK3]		= &sdm845_rf_clk3.hw,
	[RPMH_RF_CLK3_A]	= &sdm845_rf_clk3_ao.hw,
	[RPMH_RF_CLK4]		= &sm8350_rf_clk4.hw,
	[RPMH_RF_CLK4_A]	= &sm8350_rf_clk4_ao.hw,
	[RPMH_RF_CLK5]		= &sm8350_rf_clk5.hw,
	[RPMH_RF_CLK5_A]	= &sm8350_rf_clk5_ao.hw,
	[RPMH_IPA_CLK]		= &sdm845_ipa.hw,
	[RPMH_PKA_CLK]		= &sm8350_pka.hw,
	[RPMH_HWKM_CLK]		= &sm8350_hwkm.hw,
पूर्ण;

अटल स्थिर काष्ठा clk_rpmh_desc clk_rpmh_sm8350 = अणु
	.clks = sm8350_rpmh_घड़ीs,
	.num_clks = ARRAY_SIZE(sm8350_rpmh_घड़ीs),
पूर्ण;

/* Resource name must match resource id present in cmd-db */
DEFINE_CLK_RPMH_ARC(sc7280, bi_tcxo, bi_tcxo_ao, "xo.lvl", 0x3, 4);

अटल काष्ठा clk_hw *sc7280_rpmh_घड़ीs[] = अणु
	[RPMH_CXO_CLK]      = &sc7280_bi_tcxo.hw,
	[RPMH_CXO_CLK_A]    = &sc7280_bi_tcxo_ao.hw,
	[RPMH_LN_BB_CLK2]   = &sdm845_ln_bb_clk2.hw,
	[RPMH_LN_BB_CLK2_A] = &sdm845_ln_bb_clk2_ao.hw,
	[RPMH_RF_CLK1]      = &sdm845_rf_clk1.hw,
	[RPMH_RF_CLK1_A]    = &sdm845_rf_clk1_ao.hw,
	[RPMH_RF_CLK3]      = &sdm845_rf_clk3.hw,
	[RPMH_RF_CLK3_A]    = &sdm845_rf_clk3_ao.hw,
	[RPMH_RF_CLK4]      = &sm8350_rf_clk4.hw,
	[RPMH_RF_CLK4_A]    = &sm8350_rf_clk4_ao.hw,
	[RPMH_IPA_CLK]      = &sdm845_ipa.hw,
	[RPMH_PKA_CLK]      = &sm8350_pka.hw,
	[RPMH_HWKM_CLK]     = &sm8350_hwkm.hw,
पूर्ण;

अटल स्थिर काष्ठा clk_rpmh_desc clk_rpmh_sc7280 = अणु
	.clks = sc7280_rpmh_घड़ीs,
	.num_clks = ARRAY_SIZE(sc7280_rpmh_घड़ीs),
पूर्ण;

अटल काष्ठा clk_hw *of_clk_rpmh_hw_get(काष्ठा of_phandle_args *clkspec,
					 व्योम *data)
अणु
	काष्ठा clk_rpmh_desc *rpmh = data;
	अचिन्हित पूर्णांक idx = clkspec->args[0];

	अगर (idx >= rpmh->num_clks) अणु
		pr_err("%s: invalid index %u\n", __func__, idx);
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	वापस rpmh->clks[idx];
पूर्ण

अटल पूर्णांक clk_rpmh_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा clk_hw **hw_clks;
	काष्ठा clk_rpmh *rpmh_clk;
	स्थिर काष्ठा clk_rpmh_desc *desc;
	पूर्णांक ret, i;

	desc = of_device_get_match_data(&pdev->dev);
	अगर (!desc)
		वापस -ENODEV;

	hw_clks = desc->clks;

	क्रम (i = 0; i < desc->num_clks; i++) अणु
		स्थिर अक्षर *name;
		u32 res_addr;
		माप_प्रकार aux_data_len;
		स्थिर काष्ठा bcm_db *data;

		अगर (!hw_clks[i])
			जारी;

		name = hw_clks[i]->init->name;

		rpmh_clk = to_clk_rpmh(hw_clks[i]);
		res_addr = cmd_db_पढ़ो_addr(rpmh_clk->res_name);
		अगर (!res_addr) अणु
			dev_err(&pdev->dev, "missing RPMh resource address for %s\n",
				rpmh_clk->res_name);
			वापस -ENODEV;
		पूर्ण

		data = cmd_db_पढ़ो_aux_data(rpmh_clk->res_name, &aux_data_len);
		अगर (IS_ERR(data)) अणु
			ret = PTR_ERR(data);
			dev_err(&pdev->dev,
				"error reading RPMh aux data for %s (%d)\n",
				rpmh_clk->res_name, ret);
			वापस ret;
		पूर्ण

		/* Convert unit from Khz to Hz */
		अगर (aux_data_len == माप(*data))
			rpmh_clk->unit = le32_to_cpu(data->unit) * 1000ULL;

		rpmh_clk->res_addr += res_addr;
		rpmh_clk->dev = &pdev->dev;

		ret = devm_clk_hw_रेजिस्टर(&pdev->dev, hw_clks[i]);
		अगर (ret) अणु
			dev_err(&pdev->dev, "failed to register %s\n", name);
			वापस ret;
		पूर्ण
	पूर्ण

	/* typecast to silence compiler warning */
	ret = devm_of_clk_add_hw_provider(&pdev->dev, of_clk_rpmh_hw_get,
					  (व्योम *)desc);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Failed to add clock provider\n");
		वापस ret;
	पूर्ण

	dev_dbg(&pdev->dev, "Registered RPMh clocks\n");

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id clk_rpmh_match_table[] = अणु
	अणु .compatible = "qcom,sc7180-rpmh-clk", .data = &clk_rpmh_sc7180पूर्ण,
	अणु .compatible = "qcom,sc8180x-rpmh-clk", .data = &clk_rpmh_sc8180xपूर्ण,
	अणु .compatible = "qcom,sdm845-rpmh-clk", .data = &clk_rpmh_sdm845पूर्ण,
	अणु .compatible = "qcom,sdx55-rpmh-clk",  .data = &clk_rpmh_sdx55पूर्ण,
	अणु .compatible = "qcom,sm8150-rpmh-clk", .data = &clk_rpmh_sm8150पूर्ण,
	अणु .compatible = "qcom,sm8250-rpmh-clk", .data = &clk_rpmh_sm8250पूर्ण,
	अणु .compatible = "qcom,sm8350-rpmh-clk", .data = &clk_rpmh_sm8350पूर्ण,
	अणु .compatible = "qcom,sc7280-rpmh-clk", .data = &clk_rpmh_sc7280पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, clk_rpmh_match_table);

अटल काष्ठा platक्रमm_driver clk_rpmh_driver = अणु
	.probe		= clk_rpmh_probe,
	.driver		= अणु
		.name	= "clk-rpmh",
		.of_match_table = clk_rpmh_match_table,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init clk_rpmh_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&clk_rpmh_driver);
पूर्ण
core_initcall(clk_rpmh_init);

अटल व्योम __निकास clk_rpmh_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&clk_rpmh_driver);
पूर्ण
module_निकास(clk_rpmh_निकास);

MODULE_DESCRIPTION("QCOM RPMh Clock Driver");
MODULE_LICENSE("GPL v2");
