<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2014-2015, The Linux Foundation. All rights reserved.
 */

#समावेश <linux/clk.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <drm/drm_crtc.h>
#समावेश <drm/drm_dp_helper.h>
#समावेश <drm/drm_edid.h>

#समावेश "edp.h"
#समावेश "edp.xml.h"

#घोषणा VDDA_UA_ON_LOAD		100000	/* uA units */
#घोषणा VDDA_UA_OFF_LOAD	100	/* uA units */

#घोषणा DPCD_LINK_VOLTAGE_MAX		4
#घोषणा DPCD_LINK_PRE_EMPHASIS_MAX	4

#घोषणा EDP_LINK_BW_MAX		DP_LINK_BW_2_7

/* Link training वापस value */
#घोषणा EDP_TRAIN_FAIL		-1
#घोषणा EDP_TRAIN_SUCCESS	0
#घोषणा EDP_TRAIN_RECONFIG	1

#घोषणा EDP_CLK_MASK_AHB		BIT(0)
#घोषणा EDP_CLK_MASK_AUX		BIT(1)
#घोषणा EDP_CLK_MASK_LINK		BIT(2)
#घोषणा EDP_CLK_MASK_PIXEL		BIT(3)
#घोषणा EDP_CLK_MASK_MDP_CORE		BIT(4)
#घोषणा EDP_CLK_MASK_LINK_CHAN	(EDP_CLK_MASK_LINK | EDP_CLK_MASK_PIXEL)
#घोषणा EDP_CLK_MASK_AUX_CHAN	\
	(EDP_CLK_MASK_AHB | EDP_CLK_MASK_AUX | EDP_CLK_MASK_MDP_CORE)
#घोषणा EDP_CLK_MASK_ALL	(EDP_CLK_MASK_AUX_CHAN | EDP_CLK_MASK_LINK_CHAN)

#घोषणा EDP_BACKLIGHT_MAX	255

#घोषणा EDP_INTR_STATUS1	\
	(EDP_INTERRUPT_REG_1_HPD | EDP_INTERRUPT_REG_1_AUX_I2C_DONE | \
	EDP_INTERRUPT_REG_1_WRONG_ADDR | EDP_INTERRUPT_REG_1_TIMEOUT | \
	EDP_INTERRUPT_REG_1_NACK_DEFER | EDP_INTERRUPT_REG_1_WRONG_DATA_CNT | \
	EDP_INTERRUPT_REG_1_I2C_NACK | EDP_INTERRUPT_REG_1_I2C_DEFER | \
	EDP_INTERRUPT_REG_1_PLL_UNLOCK | EDP_INTERRUPT_REG_1_AUX_ERROR)
#घोषणा EDP_INTR_MASK1	(EDP_INTR_STATUS1 << 2)
#घोषणा EDP_INTR_STATUS2	\
	(EDP_INTERRUPT_REG_2_READY_FOR_VIDEO | \
	EDP_INTERRUPT_REG_2_IDLE_PATTERNs_SENT | \
	EDP_INTERRUPT_REG_2_FRAME_END | EDP_INTERRUPT_REG_2_CRC_UPDATED)
#घोषणा EDP_INTR_MASK2	(EDP_INTR_STATUS2 << 2)

काष्ठा edp_ctrl अणु
	काष्ठा platक्रमm_device *pdev;

	व्योम __iomem *base;

	/* regulators */
	काष्ठा regulator *vdda_vreg;	/* 1.8 V */
	काष्ठा regulator *lvl_vreg;

	/* घड़ीs */
	काष्ठा clk *aux_clk;
	काष्ठा clk *pixel_clk;
	काष्ठा clk *ahb_clk;
	काष्ठा clk *link_clk;
	काष्ठा clk *mdp_core_clk;

	/* gpios */
	काष्ठा gpio_desc *panel_en_gpio;
	काष्ठा gpio_desc *panel_hpd_gpio;

	/* completion and mutex */
	काष्ठा completion idle_comp;
	काष्ठा mutex dev_mutex; /* To protect device घातer status */

	/* work queue */
	काष्ठा work_काष्ठा on_work;
	काष्ठा work_काष्ठा off_work;
	काष्ठा workqueue_काष्ठा *workqueue;

	/* Interrupt रेजिस्टर lock */
	spinlock_t irq_lock;

	bool edp_connected;
	bool घातer_on;

	/* edid raw data */
	काष्ठा edid *edid;

	काष्ठा drm_dp_aux *drm_aux;

	/* dpcd raw data */
	u8 dpcd[DP_RECEIVER_CAP_SIZE];

	/* Link status */
	u8 link_rate;
	u8 lane_cnt;
	u8 v_level;
	u8 p_level;

	/* Timing status */
	u8 पूर्णांकerlaced;
	u32 pixel_rate; /* in kHz */
	u32 color_depth;

	काष्ठा edp_aux *aux;
	काष्ठा edp_phy *phy;
पूर्ण;

काष्ठा edp_pixel_clk_भाग अणु
	u32 rate; /* in kHz */
	u32 m;
	u32 n;
पूर्ण;

#घोषणा EDP_PIXEL_CLK_NUM 8
अटल स्थिर काष्ठा edp_pixel_clk_भाग clk_भागs[2][EDP_PIXEL_CLK_NUM] = अणु
	अणु /* Link घड़ी = 162MHz, source घड़ी = 810MHz */
		अणु119000, 31,  211पूर्ण, /* WSXGA+ 1680x1050@60Hz CVT */
		अणु130250, 32,  199पूर्ण, /* UXGA 1600x1200@60Hz CVT */
		अणु148500, 11,  60पूर्ण,  /* FHD 1920x1080@60Hz */
		अणु154000, 50,  263पूर्ण, /* WUXGA 1920x1200@60Hz CVT */
		अणु209250, 31,  120पूर्ण, /* QXGA 2048x1536@60Hz CVT */
		अणु268500, 119, 359पूर्ण, /* WQXGA 2560x1600@60Hz CVT */
		अणु138530, 33,  193पूर्ण, /* AUO B116HAN03.0 Panel */
		अणु141400, 48,  275पूर्ण, /* AUO B133HTN01.2 Panel */
	पूर्ण,
	अणु /* Link घड़ी = 270MHz, source घड़ी = 675MHz */
		अणु119000, 52,  295पूर्ण, /* WSXGA+ 1680x1050@60Hz CVT */
		अणु130250, 11,  57पूर्ण,  /* UXGA 1600x1200@60Hz CVT */
		अणु148500, 11,  50पूर्ण,  /* FHD 1920x1080@60Hz */
		अणु154000, 47,  206पूर्ण, /* WUXGA 1920x1200@60Hz CVT */
		अणु209250, 31,  100पूर्ण, /* QXGA 2048x1536@60Hz CVT */
		अणु268500, 107, 269पूर्ण, /* WQXGA 2560x1600@60Hz CVT */
		अणु138530, 63,  307पूर्ण, /* AUO B116HAN03.0 Panel */
		अणु141400, 53,  253पूर्ण, /* AUO B133HTN01.2 Panel */
	पूर्ण,
पूर्ण;

अटल पूर्णांक edp_clk_init(काष्ठा edp_ctrl *ctrl)
अणु
	काष्ठा platक्रमm_device *pdev = ctrl->pdev;
	पूर्णांक ret;

	ctrl->aux_clk = msm_clk_get(pdev, "core");
	अगर (IS_ERR(ctrl->aux_clk)) अणु
		ret = PTR_ERR(ctrl->aux_clk);
		pr_err("%s: Can't find core clock, %d\n", __func__, ret);
		ctrl->aux_clk = शून्य;
		वापस ret;
	पूर्ण

	ctrl->pixel_clk = msm_clk_get(pdev, "pixel");
	अगर (IS_ERR(ctrl->pixel_clk)) अणु
		ret = PTR_ERR(ctrl->pixel_clk);
		pr_err("%s: Can't find pixel clock, %d\n", __func__, ret);
		ctrl->pixel_clk = शून्य;
		वापस ret;
	पूर्ण

	ctrl->ahb_clk = msm_clk_get(pdev, "iface");
	अगर (IS_ERR(ctrl->ahb_clk)) अणु
		ret = PTR_ERR(ctrl->ahb_clk);
		pr_err("%s: Can't find iface clock, %d\n", __func__, ret);
		ctrl->ahb_clk = शून्य;
		वापस ret;
	पूर्ण

	ctrl->link_clk = msm_clk_get(pdev, "link");
	अगर (IS_ERR(ctrl->link_clk)) अणु
		ret = PTR_ERR(ctrl->link_clk);
		pr_err("%s: Can't find link clock, %d\n", __func__, ret);
		ctrl->link_clk = शून्य;
		वापस ret;
	पूर्ण

	/* need mdp core घड़ी to receive irq */
	ctrl->mdp_core_clk = msm_clk_get(pdev, "mdp_core");
	अगर (IS_ERR(ctrl->mdp_core_clk)) अणु
		ret = PTR_ERR(ctrl->mdp_core_clk);
		pr_err("%s: Can't find mdp_core clock, %d\n", __func__, ret);
		ctrl->mdp_core_clk = शून्य;
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक edp_clk_enable(काष्ठा edp_ctrl *ctrl, u32 clk_mask)
अणु
	पूर्णांक ret;

	DBG("mask=%x", clk_mask);
	/* ahb_clk should be enabled first */
	अगर (clk_mask & EDP_CLK_MASK_AHB) अणु
		ret = clk_prepare_enable(ctrl->ahb_clk);
		अगर (ret) अणु
			pr_err("%s: Failed to enable ahb clk\n", __func__);
			जाओ f0;
		पूर्ण
	पूर्ण
	अगर (clk_mask & EDP_CLK_MASK_AUX) अणु
		ret = clk_set_rate(ctrl->aux_clk, 19200000);
		अगर (ret) अणु
			pr_err("%s: Failed to set rate aux clk\n", __func__);
			जाओ f1;
		पूर्ण
		ret = clk_prepare_enable(ctrl->aux_clk);
		अगर (ret) अणु
			pr_err("%s: Failed to enable aux clk\n", __func__);
			जाओ f1;
		पूर्ण
	पूर्ण
	/* Need to set rate and enable link_clk prior to pixel_clk */
	अगर (clk_mask & EDP_CLK_MASK_LINK) अणु
		DBG("edp->link_clk, set_rate %ld",
				(अचिन्हित दीर्घ)ctrl->link_rate * 27000000);
		ret = clk_set_rate(ctrl->link_clk,
				(अचिन्हित दीर्घ)ctrl->link_rate * 27000000);
		अगर (ret) अणु
			pr_err("%s: Failed to set rate to link clk\n",
				__func__);
			जाओ f2;
		पूर्ण

		ret = clk_prepare_enable(ctrl->link_clk);
		अगर (ret) अणु
			pr_err("%s: Failed to enable link clk\n", __func__);
			जाओ f2;
		पूर्ण
	पूर्ण
	अगर (clk_mask & EDP_CLK_MASK_PIXEL) अणु
		DBG("edp->pixel_clk, set_rate %ld",
				(अचिन्हित दीर्घ)ctrl->pixel_rate * 1000);
		ret = clk_set_rate(ctrl->pixel_clk,
				(अचिन्हित दीर्घ)ctrl->pixel_rate * 1000);
		अगर (ret) अणु
			pr_err("%s: Failed to set rate to pixel clk\n",
				__func__);
			जाओ f3;
		पूर्ण

		ret = clk_prepare_enable(ctrl->pixel_clk);
		अगर (ret) अणु
			pr_err("%s: Failed to enable pixel clk\n", __func__);
			जाओ f3;
		पूर्ण
	पूर्ण
	अगर (clk_mask & EDP_CLK_MASK_MDP_CORE) अणु
		ret = clk_prepare_enable(ctrl->mdp_core_clk);
		अगर (ret) अणु
			pr_err("%s: Failed to enable mdp core clk\n", __func__);
			जाओ f4;
		पूर्ण
	पूर्ण

	वापस 0;

f4:
	अगर (clk_mask & EDP_CLK_MASK_PIXEL)
		clk_disable_unprepare(ctrl->pixel_clk);
f3:
	अगर (clk_mask & EDP_CLK_MASK_LINK)
		clk_disable_unprepare(ctrl->link_clk);
f2:
	अगर (clk_mask & EDP_CLK_MASK_AUX)
		clk_disable_unprepare(ctrl->aux_clk);
f1:
	अगर (clk_mask & EDP_CLK_MASK_AHB)
		clk_disable_unprepare(ctrl->ahb_clk);
f0:
	वापस ret;
पूर्ण

अटल व्योम edp_clk_disable(काष्ठा edp_ctrl *ctrl, u32 clk_mask)
अणु
	अगर (clk_mask & EDP_CLK_MASK_MDP_CORE)
		clk_disable_unprepare(ctrl->mdp_core_clk);
	अगर (clk_mask & EDP_CLK_MASK_PIXEL)
		clk_disable_unprepare(ctrl->pixel_clk);
	अगर (clk_mask & EDP_CLK_MASK_LINK)
		clk_disable_unprepare(ctrl->link_clk);
	अगर (clk_mask & EDP_CLK_MASK_AUX)
		clk_disable_unprepare(ctrl->aux_clk);
	अगर (clk_mask & EDP_CLK_MASK_AHB)
		clk_disable_unprepare(ctrl->ahb_clk);
पूर्ण

अटल पूर्णांक edp_regulator_init(काष्ठा edp_ctrl *ctrl)
अणु
	काष्ठा device *dev = &ctrl->pdev->dev;
	पूर्णांक ret;

	DBG("");
	ctrl->vdda_vreg = devm_regulator_get(dev, "vdda");
	ret = PTR_ERR_OR_ZERO(ctrl->vdda_vreg);
	अगर (ret) अणु
		pr_err("%s: Could not get vdda reg, ret = %d\n", __func__,
				ret);
		ctrl->vdda_vreg = शून्य;
		वापस ret;
	पूर्ण
	ctrl->lvl_vreg = devm_regulator_get(dev, "lvl-vdd");
	ret = PTR_ERR_OR_ZERO(ctrl->lvl_vreg);
	अगर (ret) अणु
		pr_err("%s: Could not get lvl-vdd reg, ret = %d\n", __func__,
				ret);
		ctrl->lvl_vreg = शून्य;
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक edp_regulator_enable(काष्ठा edp_ctrl *ctrl)
अणु
	पूर्णांक ret;

	ret = regulator_set_load(ctrl->vdda_vreg, VDDA_UA_ON_LOAD);
	अगर (ret < 0) अणु
		pr_err("%s: vdda_vreg set regulator mode failed.\n", __func__);
		जाओ vdda_set_fail;
	पूर्ण

	ret = regulator_enable(ctrl->vdda_vreg);
	अगर (ret) अणु
		pr_err("%s: Failed to enable vdda_vreg regulator.\n", __func__);
		जाओ vdda_enable_fail;
	पूर्ण

	ret = regulator_enable(ctrl->lvl_vreg);
	अगर (ret) अणु
		pr_err("Failed to enable lvl-vdd reg regulator, %d", ret);
		जाओ lvl_enable_fail;
	पूर्ण

	DBG("exit");
	वापस 0;

lvl_enable_fail:
	regulator_disable(ctrl->vdda_vreg);
vdda_enable_fail:
	regulator_set_load(ctrl->vdda_vreg, VDDA_UA_OFF_LOAD);
vdda_set_fail:
	वापस ret;
पूर्ण

अटल व्योम edp_regulator_disable(काष्ठा edp_ctrl *ctrl)
अणु
	regulator_disable(ctrl->lvl_vreg);
	regulator_disable(ctrl->vdda_vreg);
	regulator_set_load(ctrl->vdda_vreg, VDDA_UA_OFF_LOAD);
पूर्ण

अटल पूर्णांक edp_gpio_config(काष्ठा edp_ctrl *ctrl)
अणु
	काष्ठा device *dev = &ctrl->pdev->dev;
	पूर्णांक ret;

	ctrl->panel_hpd_gpio = devm_gpiod_get(dev, "panel-hpd", GPIOD_IN);
	अगर (IS_ERR(ctrl->panel_hpd_gpio)) अणु
		ret = PTR_ERR(ctrl->panel_hpd_gpio);
		ctrl->panel_hpd_gpio = शून्य;
		pr_err("%s: cannot get panel-hpd-gpios, %d\n", __func__, ret);
		वापस ret;
	पूर्ण

	ctrl->panel_en_gpio = devm_gpiod_get(dev, "panel-en", GPIOD_OUT_LOW);
	अगर (IS_ERR(ctrl->panel_en_gpio)) अणु
		ret = PTR_ERR(ctrl->panel_en_gpio);
		ctrl->panel_en_gpio = शून्य;
		pr_err("%s: cannot get panel-en-gpios, %d\n", __func__, ret);
		वापस ret;
	पूर्ण

	DBG("gpio on");

	वापस 0;
पूर्ण

अटल व्योम edp_ctrl_irq_enable(काष्ठा edp_ctrl *ctrl, पूर्णांक enable)
अणु
	अचिन्हित दीर्घ flags;

	DBG("%d", enable);
	spin_lock_irqsave(&ctrl->irq_lock, flags);
	अगर (enable) अणु
		edp_ग_लिखो(ctrl->base + REG_EDP_INTERRUPT_REG_1, EDP_INTR_MASK1);
		edp_ग_लिखो(ctrl->base + REG_EDP_INTERRUPT_REG_2, EDP_INTR_MASK2);
	पूर्ण अन्यथा अणु
		edp_ग_लिखो(ctrl->base + REG_EDP_INTERRUPT_REG_1, 0x0);
		edp_ग_लिखो(ctrl->base + REG_EDP_INTERRUPT_REG_2, 0x0);
	पूर्ण
	spin_unlock_irqrestore(&ctrl->irq_lock, flags);
	DBG("exit");
पूर्ण

अटल व्योम edp_fill_link_cfg(काष्ठा edp_ctrl *ctrl)
अणु
	u32 prate;
	u32 lrate;
	u32 bpp;
	u8 max_lane = drm_dp_max_lane_count(ctrl->dpcd);
	u8 lane;

	prate = ctrl->pixel_rate;
	bpp = ctrl->color_depth * 3;

	/*
	 * By शेष, use the maximum link rate and minimum lane count,
	 * so that we can करो rate करोwn shअगरt during link training.
	 */
	ctrl->link_rate = ctrl->dpcd[DP_MAX_LINK_RATE];

	prate *= bpp;
	prate /= 8; /* in kByte */

	lrate = 270000; /* in kHz */
	lrate *= ctrl->link_rate;
	lrate /= 10; /* in kByte, 10 bits --> 8 bits */

	क्रम (lane = 1; lane <= max_lane; lane <<= 1) अणु
		अगर (lrate >= prate)
			अवरोध;
		lrate <<= 1;
	पूर्ण

	ctrl->lane_cnt = lane;
	DBG("rate=%d lane=%d", ctrl->link_rate, ctrl->lane_cnt);
पूर्ण

अटल व्योम edp_config_ctrl(काष्ठा edp_ctrl *ctrl)
अणु
	u32 data;
	क्रमागत edp_color_depth depth;

	data = EDP_CONFIGURATION_CTRL_LANES(ctrl->lane_cnt - 1);

	अगर (drm_dp_enhanced_frame_cap(ctrl->dpcd))
		data |= EDP_CONFIGURATION_CTRL_ENHANCED_FRAMING;

	depth = EDP_6BIT;
	अगर (ctrl->color_depth == 8)
		depth = EDP_8BIT;

	data |= EDP_CONFIGURATION_CTRL_COLOR(depth);

	अगर (!ctrl->पूर्णांकerlaced)	/* progressive */
		data |= EDP_CONFIGURATION_CTRL_PROGRESSIVE;

	data |= (EDP_CONFIGURATION_CTRL_SYNC_CLK |
		EDP_CONFIGURATION_CTRL_STATIC_MVID);

	edp_ग_लिखो(ctrl->base + REG_EDP_CONFIGURATION_CTRL, data);
पूर्ण

अटल व्योम edp_state_ctrl(काष्ठा edp_ctrl *ctrl, u32 state)
अणु
	edp_ग_लिखो(ctrl->base + REG_EDP_STATE_CTRL, state);
	/* Make sure H/W status is set */
	wmb();
पूर्ण

अटल पूर्णांक edp_lane_set_ग_लिखो(काष्ठा edp_ctrl *ctrl,
	u8 voltage_level, u8 pre_emphasis_level)
अणु
	पूर्णांक i;
	u8 buf[4];

	अगर (voltage_level >= DPCD_LINK_VOLTAGE_MAX)
		voltage_level |= 0x04;

	अगर (pre_emphasis_level >= DPCD_LINK_PRE_EMPHASIS_MAX)
		pre_emphasis_level |= 0x04;

	pre_emphasis_level <<= 3;

	क्रम (i = 0; i < 4; i++)
		buf[i] = voltage_level | pre_emphasis_level;

	DBG("%s: p|v=0x%x", __func__, voltage_level | pre_emphasis_level);
	अगर (drm_dp_dpcd_ग_लिखो(ctrl->drm_aux, 0x103, buf, 4) < 4) अणु
		pr_err("%s: Set sw/pe to panel failed\n", __func__);
		वापस -ENOLINK;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक edp_train_pattern_set_ग_लिखो(काष्ठा edp_ctrl *ctrl, u8 pattern)
अणु
	u8 p = pattern;

	DBG("pattern=%x", p);
	अगर (drm_dp_dpcd_ग_लिखो(ctrl->drm_aux,
				DP_TRAINING_PATTERN_SET, &p, 1) < 1) अणु
		pr_err("%s: Set training pattern to panel failed\n", __func__);
		वापस -ENOLINK;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम edp_sink_train_set_adjust(काष्ठा edp_ctrl *ctrl,
	स्थिर u8 *link_status)
अणु
	पूर्णांक i;
	u8 max = 0;
	u8 data;

	/* use the max level across lanes */
	क्रम (i = 0; i < ctrl->lane_cnt; i++) अणु
		data = drm_dp_get_adjust_request_voltage(link_status, i);
		DBG("lane=%d req_voltage_swing=0x%x", i, data);
		अगर (max < data)
			max = data;
	पूर्ण

	ctrl->v_level = max >> DP_TRAIN_VOLTAGE_SWING_SHIFT;

	/* use the max level across lanes */
	max = 0;
	क्रम (i = 0; i < ctrl->lane_cnt; i++) अणु
		data = drm_dp_get_adjust_request_pre_emphasis(link_status, i);
		DBG("lane=%d req_pre_emphasis=0x%x", i, data);
		अगर (max < data)
			max = data;
	पूर्ण

	ctrl->p_level = max >> DP_TRAIN_PRE_EMPHASIS_SHIFT;
	DBG("v_level=%d, p_level=%d", ctrl->v_level, ctrl->p_level);
पूर्ण

अटल व्योम edp_host_train_set(काष्ठा edp_ctrl *ctrl, u32 train)
अणु
	पूर्णांक cnt = 10;
	u32 data;
	u32 shअगरt = train - 1;

	DBG("train=%d", train);

	edp_state_ctrl(ctrl, EDP_STATE_CTRL_TRAIN_PATTERN_1 << shअगरt);
	जबतक (--cnt) अणु
		data = edp_पढ़ो(ctrl->base + REG_EDP_MAINLINK_READY);
		अगर (data & (EDP_MAINLINK_READY_TRAIN_PATTERN_1_READY << shअगरt))
			अवरोध;
	पूर्ण

	अगर (cnt == 0)
		pr_err("%s: set link_train=%d failed\n", __func__, train);
पूर्ण

अटल स्थिर u8 vm_pre_emphasis[4][4] = अणु
	अणु0x03, 0x06, 0x09, 0x0Cपूर्ण,	/* pe0, 0 db */
	अणु0x03, 0x06, 0x09, 0xFFपूर्ण,	/* pe1, 3.5 db */
	अणु0x03, 0x06, 0xFF, 0xFFपूर्ण,	/* pe2, 6.0 db */
	अणु0x03, 0xFF, 0xFF, 0xFFपूर्ण	/* pe3, 9.5 db */
पूर्ण;

/* voltage swing, 0.2v and 1.0v are not support */
अटल स्थिर u8 vm_voltage_swing[4][4] = अणु
	अणु0x14, 0x18, 0x1A, 0x1Eपूर्ण, /* sw0, 0.4v  */
	अणु0x18, 0x1A, 0x1E, 0xFFपूर्ण, /* sw1, 0.6 v */
	अणु0x1A, 0x1E, 0xFF, 0xFFपूर्ण, /* sw1, 0.8 v */
	अणु0x1E, 0xFF, 0xFF, 0xFFपूर्ण  /* sw1, 1.2 v, optional */
पूर्ण;

अटल पूर्णांक edp_voltage_pre_emphasise_set(काष्ठा edp_ctrl *ctrl)
अणु
	u32 value0;
	u32 value1;

	DBG("v=%d p=%d", ctrl->v_level, ctrl->p_level);

	value0 = vm_pre_emphasis[(पूर्णांक)(ctrl->v_level)][(पूर्णांक)(ctrl->p_level)];
	value1 = vm_voltage_swing[(पूर्णांक)(ctrl->v_level)][(पूर्णांक)(ctrl->p_level)];

	/* Configure host and panel only अगर both values are allowed */
	अगर (value0 != 0xFF && value1 != 0xFF) अणु
		msm_edp_phy_vm_pe_cfg(ctrl->phy, value0, value1);
		वापस edp_lane_set_ग_लिखो(ctrl, ctrl->v_level, ctrl->p_level);
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक edp_start_link_train_1(काष्ठा edp_ctrl *ctrl)
अणु
	u8 link_status[DP_LINK_STATUS_SIZE];
	u8 old_v_level;
	पूर्णांक tries;
	पूर्णांक ret;
	पूर्णांक rlen;

	DBG("");

	edp_host_train_set(ctrl, DP_TRAINING_PATTERN_1);
	ret = edp_voltage_pre_emphasise_set(ctrl);
	अगर (ret)
		वापस ret;
	ret = edp_train_pattern_set_ग_लिखो(ctrl,
			DP_TRAINING_PATTERN_1 | DP_RECOVERED_CLOCK_OUT_EN);
	अगर (ret)
		वापस ret;

	tries = 0;
	old_v_level = ctrl->v_level;
	जबतक (1) अणु
		drm_dp_link_train_घड़ी_recovery_delay(ctrl->dpcd);

		rlen = drm_dp_dpcd_पढ़ो_link_status(ctrl->drm_aux, link_status);
		अगर (rlen < DP_LINK_STATUS_SIZE) अणु
			pr_err("%s: read link status failed\n", __func__);
			वापस -ENOLINK;
		पूर्ण
		अगर (drm_dp_घड़ी_recovery_ok(link_status, ctrl->lane_cnt)) अणु
			ret = 0;
			अवरोध;
		पूर्ण

		अगर (ctrl->v_level == DPCD_LINK_VOLTAGE_MAX) अणु
			ret = -1;
			अवरोध;
		पूर्ण

		अगर (old_v_level == ctrl->v_level) अणु
			tries++;
			अगर (tries >= 5) अणु
				ret = -1;
				अवरोध;
			पूर्ण
		पूर्ण अन्यथा अणु
			tries = 0;
			old_v_level = ctrl->v_level;
		पूर्ण

		edp_sink_train_set_adjust(ctrl, link_status);
		ret = edp_voltage_pre_emphasise_set(ctrl);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक edp_start_link_train_2(काष्ठा edp_ctrl *ctrl)
अणु
	u8 link_status[DP_LINK_STATUS_SIZE];
	पूर्णांक tries = 0;
	पूर्णांक ret;
	पूर्णांक rlen;

	DBG("");

	edp_host_train_set(ctrl, DP_TRAINING_PATTERN_2);
	ret = edp_voltage_pre_emphasise_set(ctrl);
	अगर (ret)
		वापस ret;

	ret = edp_train_pattern_set_ग_लिखो(ctrl,
			DP_TRAINING_PATTERN_2 | DP_RECOVERED_CLOCK_OUT_EN);
	अगर (ret)
		वापस ret;

	जबतक (1) अणु
		drm_dp_link_train_channel_eq_delay(ctrl->dpcd);

		rlen = drm_dp_dpcd_पढ़ो_link_status(ctrl->drm_aux, link_status);
		अगर (rlen < DP_LINK_STATUS_SIZE) अणु
			pr_err("%s: read link status failed\n", __func__);
			वापस -ENOLINK;
		पूर्ण
		अगर (drm_dp_channel_eq_ok(link_status, ctrl->lane_cnt)) अणु
			ret = 0;
			अवरोध;
		पूर्ण

		tries++;
		अगर (tries > 10) अणु
			ret = -1;
			अवरोध;
		पूर्ण

		edp_sink_train_set_adjust(ctrl, link_status);
		ret = edp_voltage_pre_emphasise_set(ctrl);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक edp_link_rate_करोwn_shअगरt(काष्ठा edp_ctrl *ctrl)
अणु
	u32 prate, lrate, bpp;
	u8 rate, lane, max_lane;
	पूर्णांक changed = 0;

	rate = ctrl->link_rate;
	lane = ctrl->lane_cnt;
	max_lane = drm_dp_max_lane_count(ctrl->dpcd);

	bpp = ctrl->color_depth * 3;
	prate = ctrl->pixel_rate;
	prate *= bpp;
	prate /= 8; /* in kByte */

	अगर (rate > DP_LINK_BW_1_62 && rate <= EDP_LINK_BW_MAX) अणु
		rate -= 4;	/* reduce rate */
		changed++;
	पूर्ण

	अगर (changed) अणु
		अगर (lane >= 1 && lane < max_lane)
			lane <<= 1;	/* increase lane */

		lrate = 270000; /* in kHz */
		lrate *= rate;
		lrate /= 10; /* kByte, 10 bits --> 8 bits */
		lrate *= lane;

		DBG("new lrate=%u prate=%u(kHz) rate=%d lane=%d p=%u b=%d",
			lrate, prate, rate, lane,
			ctrl->pixel_rate,
			bpp);

		अगर (lrate > prate) अणु
			ctrl->link_rate = rate;
			ctrl->lane_cnt = lane;
			DBG("new rate=%d %d", rate, lane);
			वापस 0;
		पूर्ण
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक edp_clear_training_pattern(काष्ठा edp_ctrl *ctrl)
अणु
	पूर्णांक ret;

	ret = edp_train_pattern_set_ग_लिखो(ctrl, 0);

	drm_dp_link_train_channel_eq_delay(ctrl->dpcd);

	वापस ret;
पूर्ण

अटल पूर्णांक edp_करो_link_train(काष्ठा edp_ctrl *ctrl)
अणु
	u8 values[2];
	पूर्णांक ret;

	DBG("");
	/*
	 * Set the current link rate and lane cnt to panel. They may have been
	 * adjusted and the values are dअगरferent from them in DPCD CAP
	 */
	values[0] = ctrl->lane_cnt;
	values[1] = ctrl->link_rate;

	अगर (drm_dp_enhanced_frame_cap(ctrl->dpcd))
		values[1] |= DP_LANE_COUNT_ENHANCED_FRAME_EN;

	अगर (drm_dp_dpcd_ग_लिखो(ctrl->drm_aux, DP_LINK_BW_SET, values,
			      माप(values)) < 0)
		वापस EDP_TRAIN_FAIL;

	ctrl->v_level = 0; /* start from शेष level */
	ctrl->p_level = 0;

	edp_state_ctrl(ctrl, 0);
	अगर (edp_clear_training_pattern(ctrl))
		वापस EDP_TRAIN_FAIL;

	ret = edp_start_link_train_1(ctrl);
	अगर (ret < 0) अणु
		अगर (edp_link_rate_करोwn_shअगरt(ctrl) == 0) अणु
			DBG("link reconfig");
			ret = EDP_TRAIN_RECONFIG;
			जाओ clear;
		पूर्ण अन्यथा अणु
			pr_err("%s: Training 1 failed", __func__);
			ret = EDP_TRAIN_FAIL;
			जाओ clear;
		पूर्ण
	पूर्ण
	DBG("Training 1 completed successfully");

	edp_state_ctrl(ctrl, 0);
	अगर (edp_clear_training_pattern(ctrl))
		वापस EDP_TRAIN_FAIL;

	ret = edp_start_link_train_2(ctrl);
	अगर (ret < 0) अणु
		अगर (edp_link_rate_करोwn_shअगरt(ctrl) == 0) अणु
			DBG("link reconfig");
			ret = EDP_TRAIN_RECONFIG;
			जाओ clear;
		पूर्ण अन्यथा अणु
			pr_err("%s: Training 2 failed", __func__);
			ret = EDP_TRAIN_FAIL;
			जाओ clear;
		पूर्ण
	पूर्ण
	DBG("Training 2 completed successfully");

	edp_state_ctrl(ctrl, EDP_STATE_CTRL_SEND_VIDEO);
clear:
	edp_clear_training_pattern(ctrl);

	वापस ret;
पूर्ण

अटल व्योम edp_घड़ी_synchrous(काष्ठा edp_ctrl *ctrl, पूर्णांक sync)
अणु
	u32 data;
	क्रमागत edp_color_depth depth;

	data = edp_पढ़ो(ctrl->base + REG_EDP_MISC1_MISC0);

	अगर (sync)
		data |= EDP_MISC1_MISC0_SYNC;
	अन्यथा
		data &= ~EDP_MISC1_MISC0_SYNC;

	/* only legacy rgb mode supported */
	depth = EDP_6BIT; /* Default */
	अगर (ctrl->color_depth == 8)
		depth = EDP_8BIT;
	अन्यथा अगर (ctrl->color_depth == 10)
		depth = EDP_10BIT;
	अन्यथा अगर (ctrl->color_depth == 12)
		depth = EDP_12BIT;
	अन्यथा अगर (ctrl->color_depth == 16)
		depth = EDP_16BIT;

	data |= EDP_MISC1_MISC0_COLOR(depth);

	edp_ग_लिखो(ctrl->base + REG_EDP_MISC1_MISC0, data);
पूर्ण

अटल पूर्णांक edp_sw_mvid_nvid(काष्ठा edp_ctrl *ctrl, u32 m, u32 n)
अणु
	u32 n_multi, m_multi = 5;

	अगर (ctrl->link_rate == DP_LINK_BW_1_62) अणु
		n_multi = 1;
	पूर्ण अन्यथा अगर (ctrl->link_rate == DP_LINK_BW_2_7) अणु
		n_multi = 2;
	पूर्ण अन्यथा अणु
		pr_err("%s: Invalid link rate, %d\n", __func__,
			ctrl->link_rate);
		वापस -EINVAL;
	पूर्ण

	edp_ग_लिखो(ctrl->base + REG_EDP_SOFTWARE_MVID, m * m_multi);
	edp_ग_लिखो(ctrl->base + REG_EDP_SOFTWARE_NVID, n * n_multi);

	वापस 0;
पूर्ण

अटल व्योम edp_मुख्यlink_ctrl(काष्ठा edp_ctrl *ctrl, पूर्णांक enable)
अणु
	u32 data = 0;

	edp_ग_लिखो(ctrl->base + REG_EDP_MAINLINK_CTRL, EDP_MAINLINK_CTRL_RESET);
	/* Make sure fully reset */
	wmb();
	usleep_range(500, 1000);

	अगर (enable)
		data |= EDP_MAINLINK_CTRL_ENABLE;

	edp_ग_लिखो(ctrl->base + REG_EDP_MAINLINK_CTRL, data);
पूर्ण

अटल व्योम edp_ctrl_phy_aux_enable(काष्ठा edp_ctrl *ctrl, पूर्णांक enable)
अणु
	अगर (enable) अणु
		edp_regulator_enable(ctrl);
		edp_clk_enable(ctrl, EDP_CLK_MASK_AUX_CHAN);
		msm_edp_phy_ctrl(ctrl->phy, 1);
		msm_edp_aux_ctrl(ctrl->aux, 1);
		gpiod_set_value(ctrl->panel_en_gpio, 1);
	पूर्ण अन्यथा अणु
		gpiod_set_value(ctrl->panel_en_gpio, 0);
		msm_edp_aux_ctrl(ctrl->aux, 0);
		msm_edp_phy_ctrl(ctrl->phy, 0);
		edp_clk_disable(ctrl, EDP_CLK_MASK_AUX_CHAN);
		edp_regulator_disable(ctrl);
	पूर्ण
पूर्ण

अटल व्योम edp_ctrl_link_enable(काष्ठा edp_ctrl *ctrl, पूर्णांक enable)
अणु
	u32 m, n;

	अगर (enable) अणु
		/* Enable link channel घड़ीs */
		edp_clk_enable(ctrl, EDP_CLK_MASK_LINK_CHAN);

		msm_edp_phy_lane_घातer_ctrl(ctrl->phy, true, ctrl->lane_cnt);

		msm_edp_phy_vm_pe_init(ctrl->phy);

		/* Make sure phy is programed */
		wmb();
		msm_edp_phy_पढ़ोy(ctrl->phy);

		edp_config_ctrl(ctrl);
		msm_edp_ctrl_pixel_घड़ी_valid(ctrl, ctrl->pixel_rate, &m, &n);
		edp_sw_mvid_nvid(ctrl, m, n);
		edp_मुख्यlink_ctrl(ctrl, 1);
	पूर्ण अन्यथा अणु
		edp_मुख्यlink_ctrl(ctrl, 0);

		msm_edp_phy_lane_घातer_ctrl(ctrl->phy, false, 0);
		edp_clk_disable(ctrl, EDP_CLK_MASK_LINK_CHAN);
	पूर्ण
पूर्ण

अटल पूर्णांक edp_ctrl_training(काष्ठा edp_ctrl *ctrl)
अणु
	पूर्णांक ret;

	/* Do link training only when घातer is on */
	अगर (!ctrl->घातer_on)
		वापस -EINVAL;

train_start:
	ret = edp_करो_link_train(ctrl);
	अगर (ret == EDP_TRAIN_RECONFIG) अणु
		/* Re-configure मुख्य link */
		edp_ctrl_irq_enable(ctrl, 0);
		edp_ctrl_link_enable(ctrl, 0);
		msm_edp_phy_ctrl(ctrl->phy, 0);

		/* Make sure link is fully disabled */
		wmb();
		usleep_range(500, 1000);

		msm_edp_phy_ctrl(ctrl->phy, 1);
		edp_ctrl_link_enable(ctrl, 1);
		edp_ctrl_irq_enable(ctrl, 1);
		जाओ train_start;
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम edp_ctrl_on_worker(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा edp_ctrl *ctrl = container_of(
				work, काष्ठा edp_ctrl, on_work);
	u8 value;
	पूर्णांक ret;

	mutex_lock(&ctrl->dev_mutex);

	अगर (ctrl->घातer_on) अणु
		DBG("already on");
		जाओ unlock_ret;
	पूर्ण

	edp_ctrl_phy_aux_enable(ctrl, 1);
	edp_ctrl_link_enable(ctrl, 1);

	edp_ctrl_irq_enable(ctrl, 1);

	/* DP_SET_POWER रेजिस्टर is only available on DPCD v1.1 and later */
	अगर (ctrl->dpcd[DP_DPCD_REV] >= 0x11) अणु
		ret = drm_dp_dpcd_पढ़ोb(ctrl->drm_aux, DP_SET_POWER, &value);
		अगर (ret < 0)
			जाओ fail;

		value &= ~DP_SET_POWER_MASK;
		value |= DP_SET_POWER_D0;

		ret = drm_dp_dpcd_ग_लिखोb(ctrl->drm_aux, DP_SET_POWER, value);
		अगर (ret < 0)
			जाओ fail;

		/*
		 * According to the DP 1.1 specअगरication, a "Sink Device must
		 * निकास the घातer saving state within 1 ms" (Section 2.5.3.1,
		 * Table 5-52, "Sink Control Field" (रेजिस्टर 0x600).
		 */
		usleep_range(1000, 2000);
	पूर्ण

	ctrl->घातer_on = true;

	/* Start link training */
	ret = edp_ctrl_training(ctrl);
	अगर (ret != EDP_TRAIN_SUCCESS)
		जाओ fail;

	DBG("DONE");
	जाओ unlock_ret;

fail:
	edp_ctrl_irq_enable(ctrl, 0);
	edp_ctrl_link_enable(ctrl, 0);
	edp_ctrl_phy_aux_enable(ctrl, 0);
	ctrl->घातer_on = false;
unlock_ret:
	mutex_unlock(&ctrl->dev_mutex);
पूर्ण

अटल व्योम edp_ctrl_off_worker(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा edp_ctrl *ctrl = container_of(
				work, काष्ठा edp_ctrl, off_work);
	अचिन्हित दीर्घ समय_left;

	mutex_lock(&ctrl->dev_mutex);

	अगर (!ctrl->घातer_on) अणु
		DBG("already off");
		जाओ unlock_ret;
	पूर्ण

	reinit_completion(&ctrl->idle_comp);
	edp_state_ctrl(ctrl, EDP_STATE_CTRL_PUSH_IDLE);

	समय_left = रुको_क्रम_completion_समयout(&ctrl->idle_comp,
						msecs_to_jअगरfies(500));
	अगर (!समय_left)
		DBG("%s: idle pattern timedout\n", __func__);

	edp_state_ctrl(ctrl, 0);

	/* DP_SET_POWER रेजिस्टर is only available on DPCD v1.1 and later */
	अगर (ctrl->dpcd[DP_DPCD_REV] >= 0x11) अणु
		u8 value;
		पूर्णांक ret;

		ret = drm_dp_dpcd_पढ़ोb(ctrl->drm_aux, DP_SET_POWER, &value);
		अगर (ret > 0) अणु
			value &= ~DP_SET_POWER_MASK;
			value |= DP_SET_POWER_D3;

			drm_dp_dpcd_ग_लिखोb(ctrl->drm_aux, DP_SET_POWER, value);
		पूर्ण
	पूर्ण

	edp_ctrl_irq_enable(ctrl, 0);

	edp_ctrl_link_enable(ctrl, 0);

	edp_ctrl_phy_aux_enable(ctrl, 0);

	ctrl->घातer_on = false;

unlock_ret:
	mutex_unlock(&ctrl->dev_mutex);
पूर्ण

irqवापस_t msm_edp_ctrl_irq(काष्ठा edp_ctrl *ctrl)
अणु
	u32 isr1, isr2, mask1, mask2;
	u32 ack;

	DBG("");
	spin_lock(&ctrl->irq_lock);
	isr1 = edp_पढ़ो(ctrl->base + REG_EDP_INTERRUPT_REG_1);
	isr2 = edp_पढ़ो(ctrl->base + REG_EDP_INTERRUPT_REG_2);

	mask1 = isr1 & EDP_INTR_MASK1;
	mask2 = isr2 & EDP_INTR_MASK2;

	isr1 &= ~mask1;	/* हटाओ masks bit */
	isr2 &= ~mask2;

	DBG("isr=%x mask=%x isr2=%x mask2=%x",
			isr1, mask1, isr2, mask2);

	ack = isr1 & EDP_INTR_STATUS1;
	ack <<= 1;	/* ack bits */
	ack |= mask1;
	edp_ग_लिखो(ctrl->base + REG_EDP_INTERRUPT_REG_1, ack);

	ack = isr2 & EDP_INTR_STATUS2;
	ack <<= 1;	/* ack bits */
	ack |= mask2;
	edp_ग_लिखो(ctrl->base + REG_EDP_INTERRUPT_REG_2, ack);
	spin_unlock(&ctrl->irq_lock);

	अगर (isr1 & EDP_INTERRUPT_REG_1_HPD)
		DBG("edp_hpd");

	अगर (isr2 & EDP_INTERRUPT_REG_2_READY_FOR_VIDEO)
		DBG("edp_video_ready");

	अगर (isr2 & EDP_INTERRUPT_REG_2_IDLE_PATTERNs_SENT) अणु
		DBG("idle_patterns_sent");
		complete(&ctrl->idle_comp);
	पूर्ण

	msm_edp_aux_irq(ctrl->aux, isr1);

	वापस IRQ_HANDLED;
पूर्ण

व्योम msm_edp_ctrl_घातer(काष्ठा edp_ctrl *ctrl, bool on)
अणु
	अगर (on)
		queue_work(ctrl->workqueue, &ctrl->on_work);
	अन्यथा
		queue_work(ctrl->workqueue, &ctrl->off_work);
पूर्ण

पूर्णांक msm_edp_ctrl_init(काष्ठा msm_edp *edp)
अणु
	काष्ठा edp_ctrl *ctrl = शून्य;
	काष्ठा device *dev = &edp->pdev->dev;
	पूर्णांक ret;

	अगर (!edp) अणु
		pr_err("%s: edp is NULL!\n", __func__);
		वापस -EINVAL;
	पूर्ण

	ctrl = devm_kzalloc(dev, माप(*ctrl), GFP_KERNEL);
	अगर (!ctrl)
		वापस -ENOMEM;

	edp->ctrl = ctrl;
	ctrl->pdev = edp->pdev;

	ctrl->base = msm_ioremap(ctrl->pdev, "edp", "eDP");
	अगर (IS_ERR(ctrl->base))
		वापस PTR_ERR(ctrl->base);

	/* Get regulator, घड़ी, gpio, pwm */
	ret = edp_regulator_init(ctrl);
	अगर (ret) अणु
		pr_err("%s:regulator init fail\n", __func__);
		वापस ret;
	पूर्ण
	ret = edp_clk_init(ctrl);
	अगर (ret) अणु
		pr_err("%s:clk init fail\n", __func__);
		वापस ret;
	पूर्ण
	ret = edp_gpio_config(ctrl);
	अगर (ret) अणु
		pr_err("%s:failed to configure GPIOs: %d", __func__, ret);
		वापस ret;
	पूर्ण

	/* Init aux and phy */
	ctrl->aux = msm_edp_aux_init(dev, ctrl->base, &ctrl->drm_aux);
	अगर (!ctrl->aux || !ctrl->drm_aux) अणु
		pr_err("%s:failed to init aux\n", __func__);
		वापस -ENOMEM;
	पूर्ण

	ctrl->phy = msm_edp_phy_init(dev, ctrl->base);
	अगर (!ctrl->phy) अणु
		pr_err("%s:failed to init phy\n", __func__);
		ret = -ENOMEM;
		जाओ err_destory_aux;
	पूर्ण

	spin_lock_init(&ctrl->irq_lock);
	mutex_init(&ctrl->dev_mutex);
	init_completion(&ctrl->idle_comp);

	/* setup workqueue */
	ctrl->workqueue = alloc_ordered_workqueue("edp_drm_work", 0);
	INIT_WORK(&ctrl->on_work, edp_ctrl_on_worker);
	INIT_WORK(&ctrl->off_work, edp_ctrl_off_worker);

	वापस 0;

err_destory_aux:
	msm_edp_aux_destroy(dev, ctrl->aux);
	ctrl->aux = शून्य;
	वापस ret;
पूर्ण

व्योम msm_edp_ctrl_destroy(काष्ठा edp_ctrl *ctrl)
अणु
	अगर (!ctrl)
		वापस;

	अगर (ctrl->workqueue) अणु
		flush_workqueue(ctrl->workqueue);
		destroy_workqueue(ctrl->workqueue);
		ctrl->workqueue = शून्य;
	पूर्ण

	अगर (ctrl->aux) अणु
		msm_edp_aux_destroy(&ctrl->pdev->dev, ctrl->aux);
		ctrl->aux = शून्य;
	पूर्ण

	kमुक्त(ctrl->edid);
	ctrl->edid = शून्य;

	mutex_destroy(&ctrl->dev_mutex);
पूर्ण

bool msm_edp_ctrl_panel_connected(काष्ठा edp_ctrl *ctrl)
अणु
	mutex_lock(&ctrl->dev_mutex);
	DBG("connect status = %d", ctrl->edp_connected);
	अगर (ctrl->edp_connected) अणु
		mutex_unlock(&ctrl->dev_mutex);
		वापस true;
	पूर्ण

	अगर (!ctrl->घातer_on) अणु
		edp_ctrl_phy_aux_enable(ctrl, 1);
		edp_ctrl_irq_enable(ctrl, 1);
	पूर्ण

	अगर (drm_dp_dpcd_पढ़ो(ctrl->drm_aux, DP_DPCD_REV, ctrl->dpcd,
				DP_RECEIVER_CAP_SIZE) < DP_RECEIVER_CAP_SIZE) अणु
		pr_err("%s: AUX channel is NOT ready\n", __func__);
		स_रखो(ctrl->dpcd, 0, DP_RECEIVER_CAP_SIZE);
	पूर्ण अन्यथा अणु
		ctrl->edp_connected = true;
	पूर्ण

	अगर (!ctrl->घातer_on) अणु
		edp_ctrl_irq_enable(ctrl, 0);
		edp_ctrl_phy_aux_enable(ctrl, 0);
	पूर्ण

	DBG("exit: connect status=%d", ctrl->edp_connected);

	mutex_unlock(&ctrl->dev_mutex);

	वापस ctrl->edp_connected;
पूर्ण

पूर्णांक msm_edp_ctrl_get_panel_info(काष्ठा edp_ctrl *ctrl,
		काष्ठा drm_connector *connector, काष्ठा edid **edid)
अणु
	पूर्णांक ret = 0;

	mutex_lock(&ctrl->dev_mutex);

	अगर (ctrl->edid) अणु
		अगर (edid) अणु
			DBG("Just return edid buffer");
			*edid = ctrl->edid;
		पूर्ण
		जाओ unlock_ret;
	पूर्ण

	अगर (!ctrl->घातer_on) अणु
		edp_ctrl_phy_aux_enable(ctrl, 1);
		edp_ctrl_irq_enable(ctrl, 1);
	पूर्ण

	/* Initialize link rate as panel max link rate */
	ctrl->link_rate = ctrl->dpcd[DP_MAX_LINK_RATE];

	ctrl->edid = drm_get_edid(connector, &ctrl->drm_aux->ddc);
	अगर (!ctrl->edid) अणु
		pr_err("%s: edid read fail\n", __func__);
		जाओ disable_ret;
	पूर्ण

	अगर (edid)
		*edid = ctrl->edid;

disable_ret:
	अगर (!ctrl->घातer_on) अणु
		edp_ctrl_irq_enable(ctrl, 0);
		edp_ctrl_phy_aux_enable(ctrl, 0);
	पूर्ण
unlock_ret:
	mutex_unlock(&ctrl->dev_mutex);
	वापस ret;
पूर्ण

पूर्णांक msm_edp_ctrl_timing_cfg(काष्ठा edp_ctrl *ctrl,
				स्थिर काष्ठा drm_display_mode *mode,
				स्थिर काष्ठा drm_display_info *info)
अणु
	u32 hstart_from_sync, vstart_from_sync;
	u32 data;
	पूर्णांक ret = 0;

	mutex_lock(&ctrl->dev_mutex);
	/*
	 * Need to keep color depth, pixel rate and
	 * पूर्णांकerlaced inक्रमmation in ctrl context
	 */
	ctrl->color_depth = info->bpc;
	ctrl->pixel_rate = mode->घड़ी;
	ctrl->पूर्णांकerlaced = !!(mode->flags & DRM_MODE_FLAG_INTERLACE);

	/* Fill initial link config based on passed in timing */
	edp_fill_link_cfg(ctrl);

	अगर (edp_clk_enable(ctrl, EDP_CLK_MASK_AHB)) अणु
		pr_err("%s, fail to prepare enable ahb clk\n", __func__);
		ret = -EINVAL;
		जाओ unlock_ret;
	पूर्ण
	edp_घड़ी_synchrous(ctrl, 1);

	/* Configure eDP timing to HW */
	edp_ग_लिखो(ctrl->base + REG_EDP_TOTAL_HOR_VER,
		EDP_TOTAL_HOR_VER_HORIZ(mode->htotal) |
		EDP_TOTAL_HOR_VER_VERT(mode->vtotal));

	vstart_from_sync = mode->vtotal - mode->vsync_start;
	hstart_from_sync = mode->htotal - mode->hsync_start;
	edp_ग_लिखो(ctrl->base + REG_EDP_START_HOR_VER_FROM_SYNC,
		EDP_START_HOR_VER_FROM_SYNC_HORIZ(hstart_from_sync) |
		EDP_START_HOR_VER_FROM_SYNC_VERT(vstart_from_sync));

	data = EDP_HSYNC_VSYNC_WIDTH_POLARITY_VERT(
			mode->vsync_end - mode->vsync_start);
	data |= EDP_HSYNC_VSYNC_WIDTH_POLARITY_HORIZ(
			mode->hsync_end - mode->hsync_start);
	अगर (mode->flags & DRM_MODE_FLAG_NVSYNC)
		data |= EDP_HSYNC_VSYNC_WIDTH_POLARITY_NVSYNC;
	अगर (mode->flags & DRM_MODE_FLAG_NHSYNC)
		data |= EDP_HSYNC_VSYNC_WIDTH_POLARITY_NHSYNC;
	edp_ग_लिखो(ctrl->base + REG_EDP_HSYNC_VSYNC_WIDTH_POLARITY, data);

	edp_ग_लिखो(ctrl->base + REG_EDP_ACTIVE_HOR_VER,
		EDP_ACTIVE_HOR_VER_HORIZ(mode->hdisplay) |
		EDP_ACTIVE_HOR_VER_VERT(mode->vdisplay));

	edp_clk_disable(ctrl, EDP_CLK_MASK_AHB);

unlock_ret:
	mutex_unlock(&ctrl->dev_mutex);
	वापस ret;
पूर्ण

bool msm_edp_ctrl_pixel_घड़ी_valid(काष्ठा edp_ctrl *ctrl,
	u32 pixel_rate, u32 *pm, u32 *pn)
अणु
	स्थिर काष्ठा edp_pixel_clk_भाग *भागs;
	u32 err = 1; /* 1% error tolerance */
	u32 clk_err;
	पूर्णांक i;

	अगर (ctrl->link_rate == DP_LINK_BW_1_62) अणु
		भागs = clk_भागs[0];
	पूर्ण अन्यथा अगर (ctrl->link_rate == DP_LINK_BW_2_7) अणु
		भागs = clk_भागs[1];
	पूर्ण अन्यथा अणु
		pr_err("%s: Invalid link rate,%d\n", __func__, ctrl->link_rate);
		वापस false;
	पूर्ण

	क्रम (i = 0; i < EDP_PIXEL_CLK_NUM; i++) अणु
		clk_err = असल(भागs[i].rate - pixel_rate);
		अगर ((भागs[i].rate * err / 100) >= clk_err) अणु
			अगर (pm)
				*pm = भागs[i].m;
			अगर (pn)
				*pn = भागs[i].n;
			वापस true;
		पूर्ण
	पूर्ण

	DBG("pixel clock %d(kHz) not supported", pixel_rate);

	वापस false;
पूर्ण

