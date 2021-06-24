<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
* Analogix DP (Display Port) core पूर्णांकerface driver.
*
* Copyright (C) 2012 Samsung Electronics Co., Ltd.
* Author: Jingoo Han <jg1.han@samsung.com>
*/

#समावेश <linux/clk.h>
#समावेश <linux/component.h>
#समावेश <linux/err.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/iopoll.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/phy/phy.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश <drm/bridge/analogix_dp.h>
#समावेश <drm/drm_atomic.h>
#समावेश <drm/drm_atomic_helper.h>
#समावेश <drm/drm_bridge.h>
#समावेश <drm/drm_crtc.h>
#समावेश <drm/drm_device.h>
#समावेश <drm/drm_panel.h>
#समावेश <drm/drm_prपूर्णांक.h>
#समावेश <drm/drm_probe_helper.h>

#समावेश "analogix_dp_core.h"
#समावेश "analogix_dp_reg.h"

#घोषणा to_dp(nm)	container_of(nm, काष्ठा analogix_dp_device, nm)

अटल स्थिर bool verअगरy_fast_training;

काष्ठा bridge_init अणु
	काष्ठा i2c_client *client;
	काष्ठा device_node *node;
पूर्ण;

अटल पूर्णांक analogix_dp_init_dp(काष्ठा analogix_dp_device *dp)
अणु
	पूर्णांक ret;

	analogix_dp_reset(dp);

	analogix_dp_swreset(dp);

	analogix_dp_init_analog_param(dp);
	analogix_dp_init_पूर्णांकerrupt(dp);

	/* SW defined function Normal operation */
	analogix_dp_enable_sw_function(dp);

	analogix_dp_config_पूर्णांकerrupt(dp);
	ret = analogix_dp_init_analog_func(dp);
	अगर (ret)
		वापस ret;

	analogix_dp_init_hpd(dp);
	analogix_dp_init_aux(dp);
	वापस 0;
पूर्ण

अटल पूर्णांक analogix_dp_detect_hpd(काष्ठा analogix_dp_device *dp)
अणु
	पूर्णांक समयout_loop = 0;

	जबतक (समयout_loop < DP_TIMEOUT_LOOP_COUNT) अणु
		अगर (analogix_dp_get_plug_in_status(dp) == 0)
			वापस 0;

		समयout_loop++;
		usleep_range(1000, 1100);
	पूर्ण

	/*
	 * Some edp screen करो not have hpd संकेत, so we can't just
	 * वापस failed when hpd plug in detect failed, DT property
	 * "force-hpd" would indicate whether driver need this.
	 */
	अगर (!dp->क्रमce_hpd)
		वापस -ETIMEDOUT;

	/*
	 * The eDP TRM indicate that अगर HPD_STATUS(RO) is 0, AUX CH
	 * will not work, so we need to give a क्रमce hpd action to
	 * set HPD_STATUS manually.
	 */
	dev_dbg(dp->dev, "failed to get hpd plug status, try to force hpd\n");

	analogix_dp_क्रमce_hpd(dp);

	अगर (analogix_dp_get_plug_in_status(dp) != 0) अणु
		dev_err(dp->dev, "failed to get hpd plug in status\n");
		वापस -EINVAL;
	पूर्ण

	dev_dbg(dp->dev, "success to get plug in status after force hpd\n");

	वापस 0;
पूर्ण

अटल bool analogix_dp_detect_sink_psr(काष्ठा analogix_dp_device *dp)
अणु
	अचिन्हित अक्षर psr_version;
	पूर्णांक ret;

	ret = drm_dp_dpcd_पढ़ोb(&dp->aux, DP_PSR_SUPPORT, &psr_version);
	अगर (ret != 1) अणु
		dev_err(dp->dev, "failed to get PSR version, disable it\n");
		वापस false;
	पूर्ण

	dev_dbg(dp->dev, "Panel PSR version : %x\n", psr_version);
	वापस psr_version & DP_PSR_IS_SUPPORTED;
पूर्ण

अटल पूर्णांक analogix_dp_enable_sink_psr(काष्ठा analogix_dp_device *dp)
अणु
	अचिन्हित अक्षर psr_en;
	पूर्णांक ret;

	/* Disable psr function */
	ret = drm_dp_dpcd_पढ़ोb(&dp->aux, DP_PSR_EN_CFG, &psr_en);
	अगर (ret != 1) अणु
		dev_err(dp->dev, "failed to get psr config\n");
		जाओ end;
	पूर्ण

	psr_en &= ~DP_PSR_ENABLE;
	ret = drm_dp_dpcd_ग_लिखोb(&dp->aux, DP_PSR_EN_CFG, psr_en);
	अगर (ret != 1) अणु
		dev_err(dp->dev, "failed to disable panel psr\n");
		जाओ end;
	पूर्ण

	/* Main-Link transmitter reमुख्यs active during PSR active states */
	psr_en = DP_PSR_CRC_VERIFICATION;
	ret = drm_dp_dpcd_ग_लिखोb(&dp->aux, DP_PSR_EN_CFG, psr_en);
	अगर (ret != 1) अणु
		dev_err(dp->dev, "failed to set panel psr\n");
		जाओ end;
	पूर्ण

	/* Enable psr function */
	psr_en = DP_PSR_ENABLE | DP_PSR_CRC_VERIFICATION;
	ret = drm_dp_dpcd_ग_लिखोb(&dp->aux, DP_PSR_EN_CFG, psr_en);
	अगर (ret != 1) अणु
		dev_err(dp->dev, "failed to set panel psr\n");
		जाओ end;
	पूर्ण

	analogix_dp_enable_psr_crc(dp);

	dp->psr_supported = true;

	वापस 0;
end:
	dev_err(dp->dev, "enable psr fail, force to disable psr\n");

	वापस ret;
पूर्ण

अटल पूर्णांक
analogix_dp_enable_rx_to_enhanced_mode(काष्ठा analogix_dp_device *dp,
				       bool enable)
अणु
	u8 data;
	पूर्णांक ret;

	ret = drm_dp_dpcd_पढ़ोb(&dp->aux, DP_LANE_COUNT_SET, &data);
	अगर (ret != 1)
		वापस ret;

	अगर (enable)
		ret = drm_dp_dpcd_ग_लिखोb(&dp->aux, DP_LANE_COUNT_SET,
					 DP_LANE_COUNT_ENHANCED_FRAME_EN |
					 DPCD_LANE_COUNT_SET(data));
	अन्यथा
		ret = drm_dp_dpcd_ग_लिखोb(&dp->aux, DP_LANE_COUNT_SET,
					 DPCD_LANE_COUNT_SET(data));

	वापस ret < 0 ? ret : 0;
पूर्ण

अटल पूर्णांक analogix_dp_is_enhanced_mode_available(काष्ठा analogix_dp_device *dp,
						  u8 *enhanced_mode_support)
अणु
	u8 data;
	पूर्णांक ret;

	ret = drm_dp_dpcd_पढ़ोb(&dp->aux, DP_MAX_LANE_COUNT, &data);
	अगर (ret != 1) अणु
		*enhanced_mode_support = 0;
		वापस ret;
	पूर्ण

	*enhanced_mode_support = DPCD_ENHANCED_FRAME_CAP(data);

	वापस 0;
पूर्ण

अटल पूर्णांक analogix_dp_set_enhanced_mode(काष्ठा analogix_dp_device *dp)
अणु
	u8 data;
	पूर्णांक ret;

	ret = analogix_dp_is_enhanced_mode_available(dp, &data);
	अगर (ret < 0)
		वापस ret;

	ret = analogix_dp_enable_rx_to_enhanced_mode(dp, data);
	अगर (ret < 0)
		वापस ret;

	analogix_dp_enable_enhanced_mode(dp, data);

	वापस 0;
पूर्ण

अटल पूर्णांक analogix_dp_training_pattern_dis(काष्ठा analogix_dp_device *dp)
अणु
	पूर्णांक ret;

	analogix_dp_set_training_pattern(dp, DP_NONE);

	ret = drm_dp_dpcd_ग_लिखोb(&dp->aux, DP_TRAINING_PATTERN_SET,
				 DP_TRAINING_PATTERN_DISABLE);

	वापस ret < 0 ? ret : 0;
पूर्ण

अटल व्योम
analogix_dp_set_lane_lane_pre_emphasis(काष्ठा analogix_dp_device *dp,
				       पूर्णांक pre_emphasis, पूर्णांक lane)
अणु
	चयन (lane) अणु
	हाल 0:
		analogix_dp_set_lane0_pre_emphasis(dp, pre_emphasis);
		अवरोध;
	हाल 1:
		analogix_dp_set_lane1_pre_emphasis(dp, pre_emphasis);
		अवरोध;

	हाल 2:
		analogix_dp_set_lane2_pre_emphasis(dp, pre_emphasis);
		अवरोध;

	हाल 3:
		analogix_dp_set_lane3_pre_emphasis(dp, pre_emphasis);
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक analogix_dp_link_start(काष्ठा analogix_dp_device *dp)
अणु
	u8 buf[4];
	पूर्णांक lane, lane_count, pll_tries, retval;

	lane_count = dp->link_train.lane_count;

	dp->link_train.lt_state = CLOCK_RECOVERY;
	dp->link_train.eq_loop = 0;

	क्रम (lane = 0; lane < lane_count; lane++)
		dp->link_train.cr_loop[lane] = 0;

	/* Set link rate and count as you want to establish*/
	analogix_dp_set_link_bandwidth(dp, dp->link_train.link_rate);
	analogix_dp_set_lane_count(dp, dp->link_train.lane_count);

	/* Setup RX configuration */
	buf[0] = dp->link_train.link_rate;
	buf[1] = dp->link_train.lane_count;
	retval = drm_dp_dpcd_ग_लिखो(&dp->aux, DP_LINK_BW_SET, buf, 2);
	अगर (retval < 0)
		वापस retval;
	/* set enhanced mode अगर available */
	retval = analogix_dp_set_enhanced_mode(dp);
	अगर (retval < 0) अणु
		dev_err(dp->dev, "failed to set enhance mode\n");
		वापस retval;
	पूर्ण

	/* Set TX pre-emphasis to minimum */
	क्रम (lane = 0; lane < lane_count; lane++)
		analogix_dp_set_lane_lane_pre_emphasis(dp,
			PRE_EMPHASIS_LEVEL_0, lane);

	/* Wait क्रम PLL lock */
	pll_tries = 0;
	जबतक (analogix_dp_get_pll_lock_status(dp) == PLL_UNLOCKED) अणु
		अगर (pll_tries == DP_TIMEOUT_LOOP_COUNT) अणु
			dev_err(dp->dev, "Wait for PLL lock timed out\n");
			वापस -ETIMEDOUT;
		पूर्ण

		pll_tries++;
		usleep_range(90, 120);
	पूर्ण

	/* Set training pattern 1 */
	analogix_dp_set_training_pattern(dp, TRAINING_PTN1);

	/* Set RX training pattern */
	retval = drm_dp_dpcd_ग_लिखोb(&dp->aux, DP_TRAINING_PATTERN_SET,
				    DP_LINK_SCRAMBLING_DISABLE |
					DP_TRAINING_PATTERN_1);
	अगर (retval < 0)
		वापस retval;

	क्रम (lane = 0; lane < lane_count; lane++)
		buf[lane] = DP_TRAIN_PRE_EMPH_LEVEL_0 |
			    DP_TRAIN_VOLTAGE_SWING_LEVEL_0;

	retval = drm_dp_dpcd_ग_लिखो(&dp->aux, DP_TRAINING_LANE0_SET, buf,
				   lane_count);
	अगर (retval < 0)
		वापस retval;

	वापस 0;
पूर्ण

अटल अचिन्हित अक्षर analogix_dp_get_lane_status(u8 link_status[2], पूर्णांक lane)
अणु
	पूर्णांक shअगरt = (lane & 1) * 4;
	u8 link_value = link_status[lane >> 1];

	वापस (link_value >> shअगरt) & 0xf;
पूर्ण

अटल पूर्णांक analogix_dp_घड़ी_recovery_ok(u8 link_status[2], पूर्णांक lane_count)
अणु
	पूर्णांक lane;
	u8 lane_status;

	क्रम (lane = 0; lane < lane_count; lane++) अणु
		lane_status = analogix_dp_get_lane_status(link_status, lane);
		अगर ((lane_status & DP_LANE_CR_DONE) == 0)
			वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक analogix_dp_channel_eq_ok(u8 link_status[2], u8 link_align,
				     पूर्णांक lane_count)
अणु
	पूर्णांक lane;
	u8 lane_status;

	अगर ((link_align & DP_INTERLANE_ALIGN_DONE) == 0)
		वापस -EINVAL;

	क्रम (lane = 0; lane < lane_count; lane++) अणु
		lane_status = analogix_dp_get_lane_status(link_status, lane);
		lane_status &= DP_CHANNEL_EQ_BITS;
		अगर (lane_status != DP_CHANNEL_EQ_BITS)
			वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल अचिन्हित अक्षर
analogix_dp_get_adjust_request_voltage(u8 adjust_request[2], पूर्णांक lane)
अणु
	पूर्णांक shअगरt = (lane & 1) * 4;
	u8 link_value = adjust_request[lane >> 1];

	वापस (link_value >> shअगरt) & 0x3;
पूर्ण

अटल अचिन्हित अक्षर analogix_dp_get_adjust_request_pre_emphasis(
					u8 adjust_request[2],
					पूर्णांक lane)
अणु
	पूर्णांक shअगरt = (lane & 1) * 4;
	u8 link_value = adjust_request[lane >> 1];

	वापस ((link_value >> shअगरt) & 0xc) >> 2;
पूर्ण

अटल व्योम analogix_dp_set_lane_link_training(काष्ठा analogix_dp_device *dp,
					       u8 training_lane_set, पूर्णांक lane)
अणु
	चयन (lane) अणु
	हाल 0:
		analogix_dp_set_lane0_link_training(dp, training_lane_set);
		अवरोध;
	हाल 1:
		analogix_dp_set_lane1_link_training(dp, training_lane_set);
		अवरोध;

	हाल 2:
		analogix_dp_set_lane2_link_training(dp, training_lane_set);
		अवरोध;

	हाल 3:
		analogix_dp_set_lane3_link_training(dp, training_lane_set);
		अवरोध;
	पूर्ण
पूर्ण

अटल अचिन्हित पूर्णांक
analogix_dp_get_lane_link_training(काष्ठा analogix_dp_device *dp,
				   पूर्णांक lane)
अणु
	u32 reg;

	चयन (lane) अणु
	हाल 0:
		reg = analogix_dp_get_lane0_link_training(dp);
		अवरोध;
	हाल 1:
		reg = analogix_dp_get_lane1_link_training(dp);
		अवरोध;
	हाल 2:
		reg = analogix_dp_get_lane2_link_training(dp);
		अवरोध;
	हाल 3:
		reg = analogix_dp_get_lane3_link_training(dp);
		अवरोध;
	शेष:
		WARN_ON(1);
		वापस 0;
	पूर्ण

	वापस reg;
पूर्ण

अटल व्योम analogix_dp_reduce_link_rate(काष्ठा analogix_dp_device *dp)
अणु
	analogix_dp_training_pattern_dis(dp);
	analogix_dp_set_enhanced_mode(dp);

	dp->link_train.lt_state = FAILED;
पूर्ण

अटल व्योम analogix_dp_get_adjust_training_lane(काष्ठा analogix_dp_device *dp,
						 u8 adjust_request[2])
अणु
	पूर्णांक lane, lane_count;
	u8 voltage_swing, pre_emphasis, training_lane;

	lane_count = dp->link_train.lane_count;
	क्रम (lane = 0; lane < lane_count; lane++) अणु
		voltage_swing = analogix_dp_get_adjust_request_voltage(
						adjust_request, lane);
		pre_emphasis = analogix_dp_get_adjust_request_pre_emphasis(
						adjust_request, lane);
		training_lane = DPCD_VOLTAGE_SWING_SET(voltage_swing) |
				DPCD_PRE_EMPHASIS_SET(pre_emphasis);

		अगर (voltage_swing == VOLTAGE_LEVEL_3)
			training_lane |= DP_TRAIN_MAX_SWING_REACHED;
		अगर (pre_emphasis == PRE_EMPHASIS_LEVEL_3)
			training_lane |= DP_TRAIN_MAX_PRE_EMPHASIS_REACHED;

		dp->link_train.training_lane[lane] = training_lane;
	पूर्ण
पूर्ण

अटल पूर्णांक analogix_dp_process_घड़ी_recovery(काष्ठा analogix_dp_device *dp)
अणु
	पूर्णांक lane, lane_count, retval;
	u8 voltage_swing, pre_emphasis, training_lane;
	u8 link_status[2], adjust_request[2];

	usleep_range(100, 101);

	lane_count = dp->link_train.lane_count;

	retval = drm_dp_dpcd_पढ़ो(&dp->aux, DP_LANE0_1_STATUS, link_status, 2);
	अगर (retval < 0)
		वापस retval;

	retval = drm_dp_dpcd_पढ़ो(&dp->aux, DP_ADJUST_REQUEST_LANE0_1,
				  adjust_request, 2);
	अगर (retval < 0)
		वापस retval;

	अगर (analogix_dp_घड़ी_recovery_ok(link_status, lane_count) == 0) अणु
		/* set training pattern 2 क्रम EQ */
		analogix_dp_set_training_pattern(dp, TRAINING_PTN2);

		retval = drm_dp_dpcd_ग_लिखोb(&dp->aux, DP_TRAINING_PATTERN_SET,
					    DP_LINK_SCRAMBLING_DISABLE |
						DP_TRAINING_PATTERN_2);
		अगर (retval < 0)
			वापस retval;

		dev_dbg(dp->dev, "Link Training Clock Recovery success\n");
		dp->link_train.lt_state = EQUALIZER_TRAINING;
	पूर्ण अन्यथा अणु
		क्रम (lane = 0; lane < lane_count; lane++) अणु
			training_lane = analogix_dp_get_lane_link_training(
							dp, lane);
			voltage_swing = analogix_dp_get_adjust_request_voltage(
							adjust_request, lane);
			pre_emphasis = analogix_dp_get_adjust_request_pre_emphasis(
							adjust_request, lane);

			अगर (DPCD_VOLTAGE_SWING_GET(training_lane) ==
					voltage_swing &&
			    DPCD_PRE_EMPHASIS_GET(training_lane) ==
					pre_emphasis)
				dp->link_train.cr_loop[lane]++;

			अगर (dp->link_train.cr_loop[lane] == MAX_CR_LOOP ||
			    voltage_swing == VOLTAGE_LEVEL_3 ||
			    pre_emphasis == PRE_EMPHASIS_LEVEL_3) अणु
				dev_err(dp->dev, "CR Max reached (%d,%d,%d)\n",
					dp->link_train.cr_loop[lane],
					voltage_swing, pre_emphasis);
				analogix_dp_reduce_link_rate(dp);
				वापस -EIO;
			पूर्ण
		पूर्ण
	पूर्ण

	analogix_dp_get_adjust_training_lane(dp, adjust_request);

	क्रम (lane = 0; lane < lane_count; lane++)
		analogix_dp_set_lane_link_training(dp,
			dp->link_train.training_lane[lane], lane);

	retval = drm_dp_dpcd_ग_लिखो(&dp->aux, DP_TRAINING_LANE0_SET,
				   dp->link_train.training_lane, lane_count);
	अगर (retval < 0)
		वापस retval;

	वापस 0;
पूर्ण

अटल पूर्णांक analogix_dp_process_equalizer_training(काष्ठा analogix_dp_device *dp)
अणु
	पूर्णांक lane, lane_count, retval;
	u32 reg;
	u8 link_align, link_status[2], adjust_request[2];

	usleep_range(400, 401);

	lane_count = dp->link_train.lane_count;

	retval = drm_dp_dpcd_पढ़ो(&dp->aux, DP_LANE0_1_STATUS, link_status, 2);
	अगर (retval < 0)
		वापस retval;

	अगर (analogix_dp_घड़ी_recovery_ok(link_status, lane_count)) अणु
		analogix_dp_reduce_link_rate(dp);
		वापस -EIO;
	पूर्ण

	retval = drm_dp_dpcd_पढ़ो(&dp->aux, DP_ADJUST_REQUEST_LANE0_1,
				  adjust_request, 2);
	अगर (retval < 0)
		वापस retval;

	retval = drm_dp_dpcd_पढ़ोb(&dp->aux, DP_LANE_ALIGN_STATUS_UPDATED,
				   &link_align);
	अगर (retval < 0)
		वापस retval;

	analogix_dp_get_adjust_training_lane(dp, adjust_request);

	अगर (!analogix_dp_channel_eq_ok(link_status, link_align, lane_count)) अणु
		/* traing pattern Set to Normal */
		retval = analogix_dp_training_pattern_dis(dp);
		अगर (retval < 0)
			वापस retval;

		dev_dbg(dp->dev, "Link Training success!\n");
		analogix_dp_get_link_bandwidth(dp, &reg);
		dp->link_train.link_rate = reg;
		dev_dbg(dp->dev, "final bandwidth = %.2x\n",
			dp->link_train.link_rate);

		analogix_dp_get_lane_count(dp, &reg);
		dp->link_train.lane_count = reg;
		dev_dbg(dp->dev, "final lane count = %.2x\n",
			dp->link_train.lane_count);

		dp->link_train.lt_state = FINISHED;

		वापस 0;
	पूर्ण

	/* not all locked */
	dp->link_train.eq_loop++;

	अगर (dp->link_train.eq_loop > MAX_EQ_LOOP) अणु
		dev_err(dp->dev, "EQ Max loop\n");
		analogix_dp_reduce_link_rate(dp);
		वापस -EIO;
	पूर्ण

	क्रम (lane = 0; lane < lane_count; lane++)
		analogix_dp_set_lane_link_training(dp,
			dp->link_train.training_lane[lane], lane);

	retval = drm_dp_dpcd_ग_लिखो(&dp->aux, DP_TRAINING_LANE0_SET,
				   dp->link_train.training_lane, lane_count);
	अगर (retval < 0)
		वापस retval;

	वापस 0;
पूर्ण

अटल व्योम analogix_dp_get_max_rx_bandwidth(काष्ठा analogix_dp_device *dp,
					     u8 *bandwidth)
अणु
	u8 data;

	/*
	 * For DP rev.1.1, Maximum link rate of Main Link lanes
	 * 0x06 = 1.62 Gbps, 0x0a = 2.7 Gbps
	 * For DP rev.1.2, Maximum link rate of Main Link lanes
	 * 0x06 = 1.62 Gbps, 0x0a = 2.7 Gbps, 0x14 = 5.4Gbps
	 */
	drm_dp_dpcd_पढ़ोb(&dp->aux, DP_MAX_LINK_RATE, &data);
	*bandwidth = data;
पूर्ण

अटल व्योम analogix_dp_get_max_rx_lane_count(काष्ठा analogix_dp_device *dp,
					      u8 *lane_count)
अणु
	u8 data;

	/*
	 * For DP rev.1.1, Maximum number of Main Link lanes
	 * 0x01 = 1 lane, 0x02 = 2 lanes, 0x04 = 4 lanes
	 */
	drm_dp_dpcd_पढ़ोb(&dp->aux, DP_MAX_LANE_COUNT, &data);
	*lane_count = DPCD_MAX_LANE_COUNT(data);
पूर्ण

अटल पूर्णांक analogix_dp_full_link_train(काष्ठा analogix_dp_device *dp,
				       u32 max_lanes, u32 max_rate)
अणु
	पूर्णांक retval = 0;
	bool training_finished = false;

	/*
	 * MACRO_RST must be applied after the PLL_LOCK to aव्योम
	 * the DP पूर्णांकer pair skew issue क्रम at least 10 us
	 */
	analogix_dp_reset_macro(dp);

	/* Initialize by पढ़ोing RX's DPCD */
	analogix_dp_get_max_rx_bandwidth(dp, &dp->link_train.link_rate);
	analogix_dp_get_max_rx_lane_count(dp, &dp->link_train.lane_count);

	अगर ((dp->link_train.link_rate != DP_LINK_BW_1_62) &&
	    (dp->link_train.link_rate != DP_LINK_BW_2_7) &&
	    (dp->link_train.link_rate != DP_LINK_BW_5_4)) अणु
		dev_err(dp->dev, "Rx Max Link Rate is abnormal :%x !\n",
			dp->link_train.link_rate);
		dp->link_train.link_rate = DP_LINK_BW_1_62;
	पूर्ण

	अगर (dp->link_train.lane_count == 0) अणु
		dev_err(dp->dev, "Rx Max Lane count is abnormal :%x !\n",
			dp->link_train.lane_count);
		dp->link_train.lane_count = (u8)LANE_COUNT1;
	पूर्ण

	/* Setup TX lane count & rate */
	अगर (dp->link_train.lane_count > max_lanes)
		dp->link_train.lane_count = max_lanes;
	अगर (dp->link_train.link_rate > max_rate)
		dp->link_train.link_rate = max_rate;

	/* All DP analog module घातer up */
	analogix_dp_set_analog_घातer_करोwn(dp, POWER_ALL, 0);

	dp->link_train.lt_state = START;

	/* Process here */
	जबतक (!retval && !training_finished) अणु
		चयन (dp->link_train.lt_state) अणु
		हाल START:
			retval = analogix_dp_link_start(dp);
			अगर (retval)
				dev_err(dp->dev, "LT link start failed!\n");
			अवरोध;
		हाल CLOCK_RECOVERY:
			retval = analogix_dp_process_घड़ी_recovery(dp);
			अगर (retval)
				dev_err(dp->dev, "LT CR failed!\n");
			अवरोध;
		हाल EQUALIZER_TRAINING:
			retval = analogix_dp_process_equalizer_training(dp);
			अगर (retval)
				dev_err(dp->dev, "LT EQ failed!\n");
			अवरोध;
		हाल FINISHED:
			training_finished = 1;
			अवरोध;
		हाल FAILED:
			वापस -EREMOTEIO;
		पूर्ण
	पूर्ण
	अगर (retval)
		dev_err(dp->dev, "eDP link training failed (%d)\n", retval);

	वापस retval;
पूर्ण

अटल पूर्णांक analogix_dp_fast_link_train(काष्ठा analogix_dp_device *dp)
अणु
	पूर्णांक i, ret;
	u8 link_align, link_status[2];
	क्रमागत pll_status status;

	analogix_dp_reset_macro(dp);

	analogix_dp_set_link_bandwidth(dp, dp->link_train.link_rate);
	analogix_dp_set_lane_count(dp, dp->link_train.lane_count);

	क्रम (i = 0; i < dp->link_train.lane_count; i++) अणु
		analogix_dp_set_lane_link_training(dp,
			dp->link_train.training_lane[i], i);
	पूर्ण

	ret = पढ़ोx_poll_समयout(analogix_dp_get_pll_lock_status, dp, status,
				 status != PLL_UNLOCKED, 120,
				 120 * DP_TIMEOUT_LOOP_COUNT);
	अगर (ret) अणु
		DRM_DEV_ERROR(dp->dev, "Wait for pll lock failed %d\n", ret);
		वापस ret;
	पूर्ण

	/* source Set training pattern 1 */
	analogix_dp_set_training_pattern(dp, TRAINING_PTN1);
	/* From DP spec, pattern must be on-screen क्रम a minimum 500us */
	usleep_range(500, 600);

	analogix_dp_set_training_pattern(dp, TRAINING_PTN2);
	/* From DP spec, pattern must be on-screen क्रम a minimum 500us */
	usleep_range(500, 600);

	/* TODO: enhanced_mode?*/
	analogix_dp_set_training_pattern(dp, DP_NONE);

	/*
	 * Useful क्रम debugging issues with fast link training, disable क्रम more
	 * speed
	 */
	अगर (verअगरy_fast_training) अणु
		ret = drm_dp_dpcd_पढ़ोb(&dp->aux, DP_LANE_ALIGN_STATUS_UPDATED,
					&link_align);
		अगर (ret < 0) अणु
			DRM_DEV_ERROR(dp->dev, "Read align status failed %d\n",
				      ret);
			वापस ret;
		पूर्ण

		ret = drm_dp_dpcd_पढ़ो(&dp->aux, DP_LANE0_1_STATUS, link_status,
				       2);
		अगर (ret < 0) अणु
			DRM_DEV_ERROR(dp->dev, "Read link status failed %d\n",
				      ret);
			वापस ret;
		पूर्ण

		अगर (analogix_dp_घड़ी_recovery_ok(link_status,
						  dp->link_train.lane_count)) अणु
			DRM_DEV_ERROR(dp->dev, "Clock recovery failed\n");
			analogix_dp_reduce_link_rate(dp);
			वापस -EIO;
		पूर्ण

		अगर (analogix_dp_channel_eq_ok(link_status, link_align,
					      dp->link_train.lane_count)) अणु
			DRM_DEV_ERROR(dp->dev, "Channel EQ failed\n");
			analogix_dp_reduce_link_rate(dp);
			वापस -EIO;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक analogix_dp_train_link(काष्ठा analogix_dp_device *dp)
अणु
	अगर (dp->fast_train_enable)
		वापस analogix_dp_fast_link_train(dp);

	वापस analogix_dp_full_link_train(dp, dp->video_info.max_lane_count,
					   dp->video_info.max_link_rate);
पूर्ण

अटल पूर्णांक analogix_dp_config_video(काष्ठा analogix_dp_device *dp)
अणु
	पूर्णांक समयout_loop = 0;
	पूर्णांक करोne_count = 0;

	analogix_dp_config_video_slave_mode(dp);

	analogix_dp_set_video_color_क्रमmat(dp);

	अगर (analogix_dp_get_pll_lock_status(dp) == PLL_UNLOCKED) अणु
		dev_err(dp->dev, "PLL is not locked yet.\n");
		वापस -EINVAL;
	पूर्ण

	क्रम (;;) अणु
		समयout_loop++;
		अगर (analogix_dp_is_slave_video_stream_घड़ी_on(dp) == 0)
			अवरोध;
		अगर (समयout_loop > DP_TIMEOUT_LOOP_COUNT) अणु
			dev_err(dp->dev, "Timeout of slave video streamclk ok\n");
			वापस -ETIMEDOUT;
		पूर्ण
		usleep_range(1000, 1001);
	पूर्ण

	/* Set to use the रेजिस्टर calculated M/N video */
	analogix_dp_set_video_cr_mn(dp, CALCULATED_M, 0, 0);

	/* For video bist, Video timing must be generated by रेजिस्टर */
	analogix_dp_set_video_timing_mode(dp, VIDEO_TIMING_FROM_CAPTURE);

	/* Disable video mute */
	analogix_dp_enable_video_mute(dp, 0);

	/* Configure video slave mode */
	analogix_dp_enable_video_master(dp, 0);

	/* Enable video */
	analogix_dp_start_video(dp);

	समयout_loop = 0;

	क्रम (;;) अणु
		समयout_loop++;
		अगर (analogix_dp_is_video_stream_on(dp) == 0) अणु
			करोne_count++;
			अगर (करोne_count > 10)
				अवरोध;
		पूर्ण अन्यथा अगर (करोne_count) अणु
			करोne_count = 0;
		पूर्ण
		अगर (समयout_loop > DP_TIMEOUT_LOOP_COUNT) अणु
			dev_warn(dp->dev,
				 "Ignoring timeout of video streamclk ok\n");
			अवरोध;
		पूर्ण

		usleep_range(1000, 1001);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक analogix_dp_enable_scramble(काष्ठा analogix_dp_device *dp,
				       bool enable)
अणु
	u8 data;
	पूर्णांक ret;

	अगर (enable) अणु
		analogix_dp_enable_scrambling(dp);

		ret = drm_dp_dpcd_पढ़ोb(&dp->aux, DP_TRAINING_PATTERN_SET,
					&data);
		अगर (ret != 1)
			वापस ret;
		ret = drm_dp_dpcd_ग_लिखोb(&dp->aux, DP_TRAINING_PATTERN_SET,
				   (u8)(data & ~DP_LINK_SCRAMBLING_DISABLE));
	पूर्ण अन्यथा अणु
		analogix_dp_disable_scrambling(dp);

		ret = drm_dp_dpcd_पढ़ोb(&dp->aux, DP_TRAINING_PATTERN_SET,
					&data);
		अगर (ret != 1)
			वापस ret;
		ret = drm_dp_dpcd_ग_लिखोb(&dp->aux, DP_TRAINING_PATTERN_SET,
				   (u8)(data | DP_LINK_SCRAMBLING_DISABLE));
	पूर्ण
	वापस ret < 0 ? ret : 0;
पूर्ण

अटल irqवापस_t analogix_dp_hardirq(पूर्णांक irq, व्योम *arg)
अणु
	काष्ठा analogix_dp_device *dp = arg;
	irqवापस_t ret = IRQ_NONE;
	क्रमागत dp_irq_type irq_type;

	irq_type = analogix_dp_get_irq_type(dp);
	अगर (irq_type != DP_IRQ_TYPE_UNKNOWN) अणु
		analogix_dp_mute_hpd_पूर्णांकerrupt(dp);
		ret = IRQ_WAKE_THREAD;
	पूर्ण

	वापस ret;
पूर्ण

अटल irqवापस_t analogix_dp_irq_thपढ़ो(पूर्णांक irq, व्योम *arg)
अणु
	काष्ठा analogix_dp_device *dp = arg;
	क्रमागत dp_irq_type irq_type;

	irq_type = analogix_dp_get_irq_type(dp);
	अगर (irq_type & DP_IRQ_TYPE_HP_CABLE_IN ||
	    irq_type & DP_IRQ_TYPE_HP_CABLE_OUT) अणु
		dev_dbg(dp->dev, "Detected cable status changed!\n");
		अगर (dp->drm_dev)
			drm_helper_hpd_irq_event(dp->drm_dev);
	पूर्ण

	अगर (irq_type != DP_IRQ_TYPE_UNKNOWN) अणु
		analogix_dp_clear_hotplug_पूर्णांकerrupts(dp);
		analogix_dp_unmute_hpd_पूर्णांकerrupt(dp);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक analogix_dp_fast_link_train_detection(काष्ठा analogix_dp_device *dp)
अणु
	पूर्णांक ret;
	u8 spपढ़ो;

	ret = drm_dp_dpcd_पढ़ोb(&dp->aux, DP_MAX_DOWNSPREAD, &spपढ़ो);
	अगर (ret != 1) अणु
		dev_err(dp->dev, "failed to read downspread %d\n", ret);
		वापस ret;
	पूर्ण
	dp->fast_train_enable = !!(spपढ़ो & DP_NO_AUX_HANDSHAKE_LINK_TRAINING);
	dev_dbg(dp->dev, "fast link training %s\n",
		dp->fast_train_enable ? "supported" : "unsupported");
	वापस 0;
पूर्ण

अटल पूर्णांक analogix_dp_commit(काष्ठा analogix_dp_device *dp)
अणु
	पूर्णांक ret;

	/* Keep the panel disabled जबतक we configure video */
	अगर (dp->plat_data->panel) अणु
		अगर (drm_panel_disable(dp->plat_data->panel))
			DRM_ERROR("failed to disable the panel\n");
	पूर्ण

	ret = analogix_dp_train_link(dp);
	अगर (ret) अणु
		dev_err(dp->dev, "unable to do link train, ret=%d\n", ret);
		वापस ret;
	पूर्ण

	ret = analogix_dp_enable_scramble(dp, 1);
	अगर (ret < 0) अणु
		dev_err(dp->dev, "can not enable scramble\n");
		वापस ret;
	पूर्ण

	analogix_dp_init_video(dp);
	ret = analogix_dp_config_video(dp);
	अगर (ret) अणु
		dev_err(dp->dev, "unable to config video\n");
		वापस ret;
	पूर्ण

	/* Safe to enable the panel now */
	अगर (dp->plat_data->panel) अणु
		ret = drm_panel_enable(dp->plat_data->panel);
		अगर (ret) अणु
			DRM_ERROR("failed to enable the panel\n");
			वापस ret;
		पूर्ण
	पूर्ण

	/* Check whether panel supports fast training */
	ret = analogix_dp_fast_link_train_detection(dp);
	अगर (ret)
		वापस ret;

	अगर (analogix_dp_detect_sink_psr(dp)) अणु
		ret = analogix_dp_enable_sink_psr(dp);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक analogix_dp_enable_psr(काष्ठा analogix_dp_device *dp)
अणु
	काष्ठा dp_sdp psr_vsc;
	पूर्णांक ret;
	u8 sink;

	ret = drm_dp_dpcd_पढ़ोb(&dp->aux, DP_PSR_STATUS, &sink);
	अगर (ret != 1)
		DRM_DEV_ERROR(dp->dev, "Failed to read psr status %d\n", ret);
	अन्यथा अगर (sink == DP_PSR_SINK_ACTIVE_RFB)
		वापस 0;

	/* Prepare VSC packet as per EDP 1.4 spec, Table 6.9 */
	स_रखो(&psr_vsc, 0, माप(psr_vsc));
	psr_vsc.sdp_header.HB0 = 0;
	psr_vsc.sdp_header.HB1 = 0x7;
	psr_vsc.sdp_header.HB2 = 0x2;
	psr_vsc.sdp_header.HB3 = 0x8;
	psr_vsc.db[0] = 0;
	psr_vsc.db[1] = EDP_VSC_PSR_STATE_ACTIVE | EDP_VSC_PSR_CRC_VALUES_VALID;

	ret = analogix_dp_send_psr_spd(dp, &psr_vsc, true);
	अगर (!ret)
		analogix_dp_set_analog_घातer_करोwn(dp, POWER_ALL, true);

	वापस ret;
पूर्ण

अटल पूर्णांक analogix_dp_disable_psr(काष्ठा analogix_dp_device *dp)
अणु
	काष्ठा dp_sdp psr_vsc;
	पूर्णांक ret;
	u8 sink;

	analogix_dp_set_analog_घातer_करोwn(dp, POWER_ALL, false);

	ret = drm_dp_dpcd_ग_लिखोb(&dp->aux, DP_SET_POWER, DP_SET_POWER_D0);
	अगर (ret != 1) अणु
		DRM_DEV_ERROR(dp->dev, "Failed to set DP Power0 %d\n", ret);
		वापस ret;
	पूर्ण

	ret = drm_dp_dpcd_पढ़ोb(&dp->aux, DP_PSR_STATUS, &sink);
	अगर (ret != 1) अणु
		DRM_DEV_ERROR(dp->dev, "Failed to read psr status %d\n", ret);
		वापस ret;
	पूर्ण अन्यथा अगर (sink == DP_PSR_SINK_INACTIVE) अणु
		DRM_DEV_ERROR(dp->dev, "sink inactive, skip disable psr");
		वापस 0;
	पूर्ण

	ret = analogix_dp_train_link(dp);
	अगर (ret) अणु
		DRM_DEV_ERROR(dp->dev, "Failed to train the link %d\n", ret);
		वापस ret;
	पूर्ण

	/* Prepare VSC packet as per EDP 1.4 spec, Table 6.9 */
	स_रखो(&psr_vsc, 0, माप(psr_vsc));
	psr_vsc.sdp_header.HB0 = 0;
	psr_vsc.sdp_header.HB1 = 0x7;
	psr_vsc.sdp_header.HB2 = 0x2;
	psr_vsc.sdp_header.HB3 = 0x8;

	psr_vsc.db[0] = 0;
	psr_vsc.db[1] = 0;

	वापस analogix_dp_send_psr_spd(dp, &psr_vsc, true);
पूर्ण

/*
 * This function is a bit of a catch-all क्रम panel preparation, hopefully
 * simplअगरying the logic of functions that need to prepare/unprepare the panel
 * below.
 *
 * If @prepare is true, this function will prepare the panel. Conversely, अगर it
 * is false, the panel will be unprepared.
 *
 * If @is_modeset_prepare is true, the function will disregard the current state
 * of the panel and either prepare/unprepare the panel based on @prepare. Once
 * it finishes, it will update dp->panel_is_modeset to reflect the current state
 * of the panel.
 */
अटल पूर्णांक analogix_dp_prepare_panel(काष्ठा analogix_dp_device *dp,
				     bool prepare, bool is_modeset_prepare)
अणु
	पूर्णांक ret = 0;

	अगर (!dp->plat_data->panel)
		वापस 0;

	mutex_lock(&dp->panel_lock);

	/*
	 * Exit early अगर this is a temporary prepare/unprepare and we're alपढ़ोy
	 * modeset (since we neither want to prepare twice or unprepare early).
	 */
	अगर (dp->panel_is_modeset && !is_modeset_prepare)
		जाओ out;

	अगर (prepare)
		ret = drm_panel_prepare(dp->plat_data->panel);
	अन्यथा
		ret = drm_panel_unprepare(dp->plat_data->panel);

	अगर (ret)
		जाओ out;

	अगर (is_modeset_prepare)
		dp->panel_is_modeset = prepare;

out:
	mutex_unlock(&dp->panel_lock);
	वापस ret;
पूर्ण

अटल पूर्णांक analogix_dp_get_modes(काष्ठा drm_connector *connector)
अणु
	काष्ठा analogix_dp_device *dp = to_dp(connector);
	काष्ठा edid *edid;
	पूर्णांक ret, num_modes = 0;

	अगर (dp->plat_data->panel) अणु
		num_modes += drm_panel_get_modes(dp->plat_data->panel, connector);
	पूर्ण अन्यथा अणु
		ret = analogix_dp_prepare_panel(dp, true, false);
		अगर (ret) अणु
			DRM_ERROR("Failed to prepare panel (%d)\n", ret);
			वापस 0;
		पूर्ण

		pm_runसमय_get_sync(dp->dev);
		edid = drm_get_edid(connector, &dp->aux.ddc);
		pm_runसमय_put(dp->dev);
		अगर (edid) अणु
			drm_connector_update_edid_property(&dp->connector,
							   edid);
			num_modes += drm_add_edid_modes(&dp->connector, edid);
			kमुक्त(edid);
		पूर्ण

		ret = analogix_dp_prepare_panel(dp, false, false);
		अगर (ret)
			DRM_ERROR("Failed to unprepare panel (%d)\n", ret);
	पूर्ण

	अगर (dp->plat_data->get_modes)
		num_modes += dp->plat_data->get_modes(dp->plat_data, connector);

	वापस num_modes;
पूर्ण

अटल काष्ठा drm_encoder *
analogix_dp_best_encoder(काष्ठा drm_connector *connector)
अणु
	काष्ठा analogix_dp_device *dp = to_dp(connector);

	वापस dp->encoder;
पूर्ण


अटल पूर्णांक analogix_dp_atomic_check(काष्ठा drm_connector *connector,
				    काष्ठा drm_atomic_state *state)
अणु
	काष्ठा analogix_dp_device *dp = to_dp(connector);
	काष्ठा drm_connector_state *conn_state;
	काष्ठा drm_crtc_state *crtc_state;

	conn_state = drm_atomic_get_new_connector_state(state, connector);
	अगर (WARN_ON(!conn_state))
		वापस -ENODEV;

	conn_state->self_refresh_aware = true;

	अगर (!conn_state->crtc)
		वापस 0;

	crtc_state = drm_atomic_get_new_crtc_state(state, conn_state->crtc);
	अगर (!crtc_state)
		वापस 0;

	अगर (crtc_state->self_refresh_active && !dp->psr_supported)
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा drm_connector_helper_funcs analogix_dp_connector_helper_funcs = अणु
	.get_modes = analogix_dp_get_modes,
	.best_encoder = analogix_dp_best_encoder,
	.atomic_check = analogix_dp_atomic_check,
पूर्ण;

अटल क्रमागत drm_connector_status
analogix_dp_detect(काष्ठा drm_connector *connector, bool क्रमce)
अणु
	काष्ठा analogix_dp_device *dp = to_dp(connector);
	क्रमागत drm_connector_status status = connector_status_disconnected;
	पूर्णांक ret;

	अगर (dp->plat_data->panel)
		वापस connector_status_connected;

	ret = analogix_dp_prepare_panel(dp, true, false);
	अगर (ret) अणु
		DRM_ERROR("Failed to prepare panel (%d)\n", ret);
		वापस connector_status_disconnected;
	पूर्ण

	अगर (!analogix_dp_detect_hpd(dp))
		status = connector_status_connected;

	ret = analogix_dp_prepare_panel(dp, false, false);
	अगर (ret)
		DRM_ERROR("Failed to unprepare panel (%d)\n", ret);

	वापस status;
पूर्ण

अटल स्थिर काष्ठा drm_connector_funcs analogix_dp_connector_funcs = अणु
	.fill_modes = drm_helper_probe_single_connector_modes,
	.detect = analogix_dp_detect,
	.destroy = drm_connector_cleanup,
	.reset = drm_atomic_helper_connector_reset,
	.atomic_duplicate_state = drm_atomic_helper_connector_duplicate_state,
	.atomic_destroy_state = drm_atomic_helper_connector_destroy_state,
पूर्ण;

अटल पूर्णांक analogix_dp_bridge_attach(काष्ठा drm_bridge *bridge,
				     क्रमागत drm_bridge_attach_flags flags)
अणु
	काष्ठा analogix_dp_device *dp = bridge->driver_निजी;
	काष्ठा drm_encoder *encoder = dp->encoder;
	काष्ठा drm_connector *connector = शून्य;
	पूर्णांक ret = 0;

	अगर (flags & DRM_BRIDGE_ATTACH_NO_CONNECTOR) अणु
		DRM_ERROR("Fix bridge driver to make connector optional!");
		वापस -EINVAL;
	पूर्ण

	अगर (!bridge->encoder) अणु
		DRM_ERROR("Parent encoder object not found");
		वापस -ENODEV;
	पूर्ण

	अगर (!dp->plat_data->skip_connector) अणु
		connector = &dp->connector;
		connector->polled = DRM_CONNECTOR_POLL_HPD;

		ret = drm_connector_init(dp->drm_dev, connector,
					 &analogix_dp_connector_funcs,
					 DRM_MODE_CONNECTOR_eDP);
		अगर (ret) अणु
			DRM_ERROR("Failed to initialize connector with drm\n");
			वापस ret;
		पूर्ण

		drm_connector_helper_add(connector,
					 &analogix_dp_connector_helper_funcs);
		drm_connector_attach_encoder(connector, encoder);
	पूर्ण

	/*
	 * NOTE: the connector registration is implemented in analogix
	 * platक्रमm driver, that to say connector would be exist after
	 * plat_data->attch वापस, that's why we record the connector
	 * poपूर्णांक after plat attached.
	 */
	अगर (dp->plat_data->attach) अणु
		ret = dp->plat_data->attach(dp->plat_data, bridge, connector);
		अगर (ret) अणु
			DRM_ERROR("Failed at platform attach func\n");
			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल
काष्ठा drm_crtc *analogix_dp_get_new_crtc(काष्ठा analogix_dp_device *dp,
					  काष्ठा drm_atomic_state *state)
अणु
	काष्ठा drm_encoder *encoder = dp->encoder;
	काष्ठा drm_connector *connector;
	काष्ठा drm_connector_state *conn_state;

	connector = drm_atomic_get_new_connector_क्रम_encoder(state, encoder);
	अगर (!connector)
		वापस शून्य;

	conn_state = drm_atomic_get_new_connector_state(state, connector);
	अगर (!conn_state)
		वापस शून्य;

	वापस conn_state->crtc;
पूर्ण

अटल व्योम
analogix_dp_bridge_atomic_pre_enable(काष्ठा drm_bridge *bridge,
				     काष्ठा drm_bridge_state *old_bridge_state)
अणु
	काष्ठा drm_atomic_state *old_state = old_bridge_state->base.state;
	काष्ठा analogix_dp_device *dp = bridge->driver_निजी;
	काष्ठा drm_crtc *crtc;
	काष्ठा drm_crtc_state *old_crtc_state;
	पूर्णांक ret;

	crtc = analogix_dp_get_new_crtc(dp, old_state);
	अगर (!crtc)
		वापस;

	old_crtc_state = drm_atomic_get_old_crtc_state(old_state, crtc);
	/* Don't touch the panel if we're coming back from PSR */
	अगर (old_crtc_state && old_crtc_state->self_refresh_active)
		वापस;

	ret = analogix_dp_prepare_panel(dp, true, true);
	अगर (ret)
		DRM_ERROR("failed to setup the panel ret = %d\n", ret);
पूर्ण

अटल पूर्णांक analogix_dp_set_bridge(काष्ठा analogix_dp_device *dp)
अणु
	पूर्णांक ret;

	pm_runसमय_get_sync(dp->dev);

	ret = clk_prepare_enable(dp->घड़ी);
	अगर (ret < 0) अणु
		DRM_ERROR("Failed to prepare_enable the clock clk [%d]\n", ret);
		जाओ out_dp_clk_pre;
	पूर्ण

	अगर (dp->plat_data->घातer_on_start)
		dp->plat_data->घातer_on_start(dp->plat_data);

	phy_घातer_on(dp->phy);

	ret = analogix_dp_init_dp(dp);
	अगर (ret)
		जाओ out_dp_init;

	/*
	 * According to DP spec v1.3 chap 3.5.1.2 Link Training,
	 * We should first make sure the HPD संकेत is निश्चितed high by device
	 * when we want to establish a link with it.
	 */
	ret = analogix_dp_detect_hpd(dp);
	अगर (ret) अणु
		DRM_ERROR("failed to get hpd single ret = %d\n", ret);
		जाओ out_dp_init;
	पूर्ण

	ret = analogix_dp_commit(dp);
	अगर (ret) अणु
		DRM_ERROR("dp commit error, ret = %d\n", ret);
		जाओ out_dp_init;
	पूर्ण

	अगर (dp->plat_data->घातer_on_end)
		dp->plat_data->घातer_on_end(dp->plat_data);

	enable_irq(dp->irq);
	वापस 0;

out_dp_init:
	phy_घातer_off(dp->phy);
	अगर (dp->plat_data->घातer_off)
		dp->plat_data->घातer_off(dp->plat_data);
	clk_disable_unprepare(dp->घड़ी);
out_dp_clk_pre:
	pm_runसमय_put_sync(dp->dev);

	वापस ret;
पूर्ण

अटल व्योम
analogix_dp_bridge_atomic_enable(काष्ठा drm_bridge *bridge,
				 काष्ठा drm_bridge_state *old_bridge_state)
अणु
	काष्ठा drm_atomic_state *old_state = old_bridge_state->base.state;
	काष्ठा analogix_dp_device *dp = bridge->driver_निजी;
	काष्ठा drm_crtc *crtc;
	काष्ठा drm_crtc_state *old_crtc_state;
	पूर्णांक समयout_loop = 0;
	पूर्णांक ret;

	crtc = analogix_dp_get_new_crtc(dp, old_state);
	अगर (!crtc)
		वापस;

	old_crtc_state = drm_atomic_get_old_crtc_state(old_state, crtc);
	/* Not a full enable, just disable PSR and जारी */
	अगर (old_crtc_state && old_crtc_state->self_refresh_active) अणु
		ret = analogix_dp_disable_psr(dp);
		अगर (ret)
			DRM_ERROR("Failed to disable psr %d\n", ret);
		वापस;
	पूर्ण

	अगर (dp->dpms_mode == DRM_MODE_DPMS_ON)
		वापस;

	जबतक (समयout_loop < MAX_PLL_LOCK_LOOP) अणु
		अगर (analogix_dp_set_bridge(dp) == 0) अणु
			dp->dpms_mode = DRM_MODE_DPMS_ON;
			वापस;
		पूर्ण
		dev_err(dp->dev, "failed to set bridge, retry: %d\n",
			समयout_loop);
		समयout_loop++;
		usleep_range(10, 11);
	पूर्ण
	dev_err(dp->dev, "too many times retry set bridge, give it up\n");
पूर्ण

अटल व्योम analogix_dp_bridge_disable(काष्ठा drm_bridge *bridge)
अणु
	काष्ठा analogix_dp_device *dp = bridge->driver_निजी;
	पूर्णांक ret;

	अगर (dp->dpms_mode != DRM_MODE_DPMS_ON)
		वापस;

	अगर (dp->plat_data->panel) अणु
		अगर (drm_panel_disable(dp->plat_data->panel)) अणु
			DRM_ERROR("failed to disable the panel\n");
			वापस;
		पूर्ण
	पूर्ण

	disable_irq(dp->irq);

	अगर (dp->plat_data->घातer_off)
		dp->plat_data->घातer_off(dp->plat_data);

	analogix_dp_set_analog_घातer_करोwn(dp, POWER_ALL, 1);
	phy_घातer_off(dp->phy);

	clk_disable_unprepare(dp->घड़ी);

	pm_runसमय_put_sync(dp->dev);

	ret = analogix_dp_prepare_panel(dp, false, true);
	अगर (ret)
		DRM_ERROR("failed to setup the panel ret = %d\n", ret);

	dp->fast_train_enable = false;
	dp->psr_supported = false;
	dp->dpms_mode = DRM_MODE_DPMS_OFF;
पूर्ण

अटल व्योम
analogix_dp_bridge_atomic_disable(काष्ठा drm_bridge *bridge,
				  काष्ठा drm_bridge_state *old_bridge_state)
अणु
	काष्ठा drm_atomic_state *old_state = old_bridge_state->base.state;
	काष्ठा analogix_dp_device *dp = bridge->driver_निजी;
	काष्ठा drm_crtc *crtc;
	काष्ठा drm_crtc_state *new_crtc_state = शून्य;

	crtc = analogix_dp_get_new_crtc(dp, old_state);
	अगर (!crtc)
		जाओ out;

	new_crtc_state = drm_atomic_get_new_crtc_state(old_state, crtc);
	अगर (!new_crtc_state)
		जाओ out;

	/* Don't करो a full disable on PSR transitions */
	अगर (new_crtc_state->self_refresh_active)
		वापस;

out:
	analogix_dp_bridge_disable(bridge);
पूर्ण

अटल व्योम
analogix_dp_bridge_atomic_post_disable(काष्ठा drm_bridge *bridge,
				काष्ठा drm_bridge_state *old_bridge_state)
अणु
	काष्ठा drm_atomic_state *old_state = old_bridge_state->base.state;
	काष्ठा analogix_dp_device *dp = bridge->driver_निजी;
	काष्ठा drm_crtc *crtc;
	काष्ठा drm_crtc_state *new_crtc_state;
	पूर्णांक ret;

	crtc = analogix_dp_get_new_crtc(dp, old_state);
	अगर (!crtc)
		वापस;

	new_crtc_state = drm_atomic_get_new_crtc_state(old_state, crtc);
	अगर (!new_crtc_state || !new_crtc_state->self_refresh_active)
		वापस;

	ret = analogix_dp_enable_psr(dp);
	अगर (ret)
		DRM_ERROR("Failed to enable psr (%d)\n", ret);
पूर्ण

अटल व्योम analogix_dp_bridge_mode_set(काष्ठा drm_bridge *bridge,
				स्थिर काष्ठा drm_display_mode *orig_mode,
				स्थिर काष्ठा drm_display_mode *mode)
अणु
	काष्ठा analogix_dp_device *dp = bridge->driver_निजी;
	काष्ठा drm_display_info *display_info = &dp->connector.display_info;
	काष्ठा video_info *video = &dp->video_info;
	काष्ठा device_node *dp_node = dp->dev->of_node;
	पूर्णांक vic;

	/* Input video पूर्णांकerlaces & hsync pol & vsync pol */
	video->पूर्णांकerlaced = !!(mode->flags & DRM_MODE_FLAG_INTERLACE);
	video->v_sync_polarity = !!(mode->flags & DRM_MODE_FLAG_NVSYNC);
	video->h_sync_polarity = !!(mode->flags & DRM_MODE_FLAG_NHSYNC);

	/* Input video dynamic_range & colorimetry */
	vic = drm_match_cea_mode(mode);
	अगर ((vic == 6) || (vic == 7) || (vic == 21) || (vic == 22) ||
	    (vic == 2) || (vic == 3) || (vic == 17) || (vic == 18)) अणु
		video->dynamic_range = CEA;
		video->ycbcr_coeff = COLOR_YCBCR601;
	पूर्ण अन्यथा अगर (vic) अणु
		video->dynamic_range = CEA;
		video->ycbcr_coeff = COLOR_YCBCR709;
	पूर्ण अन्यथा अणु
		video->dynamic_range = VESA;
		video->ycbcr_coeff = COLOR_YCBCR709;
	पूर्ण

	/* Input vide bpc and color_क्रमmats */
	चयन (display_info->bpc) अणु
	हाल 12:
		video->color_depth = COLOR_12;
		अवरोध;
	हाल 10:
		video->color_depth = COLOR_10;
		अवरोध;
	हाल 8:
		video->color_depth = COLOR_8;
		अवरोध;
	हाल 6:
		video->color_depth = COLOR_6;
		अवरोध;
	शेष:
		video->color_depth = COLOR_8;
		अवरोध;
	पूर्ण
	अगर (display_info->color_क्रमmats & DRM_COLOR_FORMAT_YCRCB444)
		video->color_space = COLOR_YCBCR444;
	अन्यथा अगर (display_info->color_क्रमmats & DRM_COLOR_FORMAT_YCRCB422)
		video->color_space = COLOR_YCBCR422;
	अन्यथा
		video->color_space = COLOR_RGB;

	/*
	 * NOTE: those property parsing code is used क्रम providing backward
	 * compatibility क्रम samsung platक्रमm.
	 * Due to we used the "of_property_read_u32" पूर्णांकerfaces, when this
	 * property isn't present, the "video_info" can keep the original
	 * values and wouldn't be modअगरied.
	 */
	of_property_पढ़ो_u32(dp_node, "samsung,color-space",
			     &video->color_space);
	of_property_पढ़ो_u32(dp_node, "samsung,dynamic-range",
			     &video->dynamic_range);
	of_property_पढ़ो_u32(dp_node, "samsung,ycbcr-coeff",
			     &video->ycbcr_coeff);
	of_property_पढ़ो_u32(dp_node, "samsung,color-depth",
			     &video->color_depth);
	अगर (of_property_पढ़ो_bool(dp_node, "hsync-active-high"))
		video->h_sync_polarity = true;
	अगर (of_property_पढ़ो_bool(dp_node, "vsync-active-high"))
		video->v_sync_polarity = true;
	अगर (of_property_पढ़ो_bool(dp_node, "interlaced"))
		video->पूर्णांकerlaced = true;
पूर्ण

अटल स्थिर काष्ठा drm_bridge_funcs analogix_dp_bridge_funcs = अणु
	.atomic_duplicate_state = drm_atomic_helper_bridge_duplicate_state,
	.atomic_destroy_state = drm_atomic_helper_bridge_destroy_state,
	.atomic_reset = drm_atomic_helper_bridge_reset,
	.atomic_pre_enable = analogix_dp_bridge_atomic_pre_enable,
	.atomic_enable = analogix_dp_bridge_atomic_enable,
	.atomic_disable = analogix_dp_bridge_atomic_disable,
	.atomic_post_disable = analogix_dp_bridge_atomic_post_disable,
	.mode_set = analogix_dp_bridge_mode_set,
	.attach = analogix_dp_bridge_attach,
पूर्ण;

अटल पूर्णांक analogix_dp_create_bridge(काष्ठा drm_device *drm_dev,
				     काष्ठा analogix_dp_device *dp)
अणु
	काष्ठा drm_bridge *bridge;
	पूर्णांक ret;

	bridge = devm_kzalloc(drm_dev->dev, माप(*bridge), GFP_KERNEL);
	अगर (!bridge) अणु
		DRM_ERROR("failed to allocate for drm bridge\n");
		वापस -ENOMEM;
	पूर्ण

	dp->bridge = bridge;

	bridge->driver_निजी = dp;
	bridge->funcs = &analogix_dp_bridge_funcs;

	ret = drm_bridge_attach(dp->encoder, bridge, शून्य, 0);
	अगर (ret) अणु
		DRM_ERROR("failed to attach drm bridge\n");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक analogix_dp_dt_parse_pdata(काष्ठा analogix_dp_device *dp)
अणु
	काष्ठा device_node *dp_node = dp->dev->of_node;
	काष्ठा video_info *video_info = &dp->video_info;

	चयन (dp->plat_data->dev_type) अणु
	हाल RK3288_DP:
	हाल RK3399_EDP:
		/*
		 * Like Rk3288 DisplayPort TRM indicate that "Main link
		 * containing 4 physical lanes of 2.7/1.62 Gbps/lane".
		 */
		video_info->max_link_rate = 0x0A;
		video_info->max_lane_count = 0x04;
		अवरोध;
	हाल EXYNOS_DP:
		/*
		 * NOTE: those property parseing code is used क्रम
		 * providing backward compatibility क्रम samsung platक्रमm.
		 */
		of_property_पढ़ो_u32(dp_node, "samsung,link-rate",
				     &video_info->max_link_rate);
		of_property_पढ़ो_u32(dp_node, "samsung,lane-count",
				     &video_info->max_lane_count);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल sमाप_प्रकार analogix_dpaux_transfer(काष्ठा drm_dp_aux *aux,
				       काष्ठा drm_dp_aux_msg *msg)
अणु
	काष्ठा analogix_dp_device *dp = to_dp(aux);

	वापस analogix_dp_transfer(dp, msg);
पूर्ण

काष्ठा analogix_dp_device *
analogix_dp_probe(काष्ठा device *dev, काष्ठा analogix_dp_plat_data *plat_data)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);
	काष्ठा analogix_dp_device *dp;
	काष्ठा resource *res;
	अचिन्हित पूर्णांक irq_flags;
	पूर्णांक ret;

	अगर (!plat_data) अणु
		dev_err(dev, "Invalided input plat_data\n");
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	dp = devm_kzalloc(dev, माप(काष्ठा analogix_dp_device), GFP_KERNEL);
	अगर (!dp)
		वापस ERR_PTR(-ENOMEM);

	dp->dev = &pdev->dev;
	dp->dpms_mode = DRM_MODE_DPMS_OFF;

	mutex_init(&dp->panel_lock);
	dp->panel_is_modeset = false;

	/*
	 * platक्रमm dp driver need containor_of the plat_data to get
	 * the driver निजी data, so we need to store the poपूर्णांक of
	 * plat_data, not the context of plat_data.
	 */
	dp->plat_data = plat_data;

	ret = analogix_dp_dt_parse_pdata(dp);
	अगर (ret)
		वापस ERR_PTR(ret);

	dp->phy = devm_phy_get(dp->dev, "dp");
	अगर (IS_ERR(dp->phy)) अणु
		dev_err(dp->dev, "no DP phy configured\n");
		ret = PTR_ERR(dp->phy);
		अगर (ret) अणु
			/*
			 * phy itself is not enabled, so we can move क्रमward
			 * assigning शून्य to phy poपूर्णांकer.
			 */
			अगर (ret == -ENOSYS || ret == -ENODEV)
				dp->phy = शून्य;
			अन्यथा
				वापस ERR_PTR(ret);
		पूर्ण
	पूर्ण

	dp->घड़ी = devm_clk_get(&pdev->dev, "dp");
	अगर (IS_ERR(dp->घड़ी)) अणु
		dev_err(&pdev->dev, "failed to get clock\n");
		वापस ERR_CAST(dp->घड़ी);
	पूर्ण

	clk_prepare_enable(dp->घड़ी);

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);

	dp->reg_base = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(dp->reg_base))
		वापस ERR_CAST(dp->reg_base);

	dp->क्रमce_hpd = of_property_पढ़ो_bool(dev->of_node, "force-hpd");

	/* Try two dअगरferent names */
	dp->hpd_gpiod = devm_gpiod_get_optional(dev, "hpd", GPIOD_IN);
	अगर (!dp->hpd_gpiod)
		dp->hpd_gpiod = devm_gpiod_get_optional(dev, "samsung,hpd",
							GPIOD_IN);
	अगर (IS_ERR(dp->hpd_gpiod)) अणु
		dev_err(dev, "error getting HDP GPIO: %ld\n",
			PTR_ERR(dp->hpd_gpiod));
		वापस ERR_CAST(dp->hpd_gpiod);
	पूर्ण

	अगर (dp->hpd_gpiod) अणु
		/*
		 * Set up the hotplug GPIO from the device tree as an पूर्णांकerrupt.
		 * Simply specअगरying a dअगरferent पूर्णांकerrupt in the device tree
		 * करोesn't work since we handle hotplug rather dअगरferently when
		 * using a GPIO.  We also need the actual GPIO specअगरier so
		 * that we can get the current state of the GPIO.
		 */
		dp->irq = gpiod_to_irq(dp->hpd_gpiod);
		irq_flags = IRQF_TRIGGER_RISING | IRQF_TRIGGER_FALLING;
	पूर्ण अन्यथा अणु
		dp->irq = platक्रमm_get_irq(pdev, 0);
		irq_flags = 0;
	पूर्ण

	अगर (dp->irq == -ENXIO) अणु
		dev_err(&pdev->dev, "failed to get irq\n");
		वापस ERR_PTR(-ENODEV);
	पूर्ण

	ret = devm_request_thपढ़ोed_irq(&pdev->dev, dp->irq,
					analogix_dp_hardirq,
					analogix_dp_irq_thपढ़ो,
					irq_flags, "analogix-dp", dp);
	अगर (ret) अणु
		dev_err(&pdev->dev, "failed to request irq\n");
		वापस ERR_PTR(ret);
	पूर्ण
	disable_irq(dp->irq);

	वापस dp;
पूर्ण
EXPORT_SYMBOL_GPL(analogix_dp_probe);

पूर्णांक analogix_dp_bind(काष्ठा analogix_dp_device *dp, काष्ठा drm_device *drm_dev)
अणु
	पूर्णांक ret;

	dp->drm_dev = drm_dev;
	dp->encoder = dp->plat_data->encoder;

	dp->aux.name = "DP-AUX";
	dp->aux.transfer = analogix_dpaux_transfer;
	dp->aux.dev = dp->dev;

	ret = drm_dp_aux_रेजिस्टर(&dp->aux);
	अगर (ret)
		वापस ret;

	pm_runसमय_enable(dp->dev);

	ret = analogix_dp_create_bridge(drm_dev, dp);
	अगर (ret) अणु
		DRM_ERROR("failed to create bridge (%d)\n", ret);
		जाओ err_disable_pm_runसमय;
	पूर्ण

	वापस 0;

err_disable_pm_runसमय:
	pm_runसमय_disable(dp->dev);
	drm_dp_aux_unरेजिस्टर(&dp->aux);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(analogix_dp_bind);

व्योम analogix_dp_unbind(काष्ठा analogix_dp_device *dp)
अणु
	analogix_dp_bridge_disable(dp->bridge);
	dp->connector.funcs->destroy(&dp->connector);

	अगर (dp->plat_data->panel) अणु
		अगर (drm_panel_unprepare(dp->plat_data->panel))
			DRM_ERROR("failed to turnoff the panel\n");
	पूर्ण

	drm_dp_aux_unरेजिस्टर(&dp->aux);
	pm_runसमय_disable(dp->dev);
पूर्ण
EXPORT_SYMBOL_GPL(analogix_dp_unbind);

व्योम analogix_dp_हटाओ(काष्ठा analogix_dp_device *dp)
अणु
	clk_disable_unprepare(dp->घड़ी);
पूर्ण
EXPORT_SYMBOL_GPL(analogix_dp_हटाओ);

#अगर_घोषित CONFIG_PM
पूर्णांक analogix_dp_suspend(काष्ठा analogix_dp_device *dp)
अणु
	clk_disable_unprepare(dp->घड़ी);

	अगर (dp->plat_data->panel) अणु
		अगर (drm_panel_unprepare(dp->plat_data->panel))
			DRM_ERROR("failed to turnoff the panel\n");
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(analogix_dp_suspend);

पूर्णांक analogix_dp_resume(काष्ठा analogix_dp_device *dp)
अणु
	पूर्णांक ret;

	ret = clk_prepare_enable(dp->घड़ी);
	अगर (ret < 0) अणु
		DRM_ERROR("Failed to prepare_enable the clock clk [%d]\n", ret);
		वापस ret;
	पूर्ण

	अगर (dp->plat_data->panel) अणु
		अगर (drm_panel_prepare(dp->plat_data->panel)) अणु
			DRM_ERROR("failed to setup the panel\n");
			वापस -EBUSY;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(analogix_dp_resume);
#पूर्ण_अगर

पूर्णांक analogix_dp_start_crc(काष्ठा drm_connector *connector)
अणु
	काष्ठा analogix_dp_device *dp = to_dp(connector);

	अगर (!connector->state->crtc) अणु
		DRM_ERROR("Connector %s doesn't currently have a CRTC.\n",
			  connector->name);
		वापस -EINVAL;
	पूर्ण

	वापस drm_dp_start_crc(&dp->aux, connector->state->crtc);
पूर्ण
EXPORT_SYMBOL_GPL(analogix_dp_start_crc);

पूर्णांक analogix_dp_stop_crc(काष्ठा drm_connector *connector)
अणु
	काष्ठा analogix_dp_device *dp = to_dp(connector);

	वापस drm_dp_stop_crc(&dp->aux);
पूर्ण
EXPORT_SYMBOL_GPL(analogix_dp_stop_crc);

MODULE_AUTHOR("Jingoo Han <jg1.han@samsung.com>");
MODULE_DESCRIPTION("Analogix DP Core Driver");
MODULE_LICENSE("GPL v2");
