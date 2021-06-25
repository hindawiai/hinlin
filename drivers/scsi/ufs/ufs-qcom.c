<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2013-2016, Linux Foundation. All rights reserved.
 */

#समावेश <linux/acpi.h>
#समावेश <linux/समय.स>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/phy/phy.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/reset-controller.h>
#समावेश <linux/devfreq.h>

#समावेश "ufshcd.h"
#समावेश "ufshcd-pltfrm.h"
#समावेश "unipro.h"
#समावेश "ufs-qcom.h"
#समावेश "ufshci.h"
#समावेश "ufs_quirks.h"
#घोषणा UFS_QCOM_DEFAULT_DBG_PRINT_EN	\
	(UFS_QCOM_DBG_PRINT_REGS_EN | UFS_QCOM_DBG_PRINT_TEST_BUS_EN)

क्रमागत अणु
	TSTBUS_UAWM,
	TSTBUS_UARM,
	TSTBUS_TXUC,
	TSTBUS_RXUC,
	TSTBUS_DFC,
	TSTBUS_TRLUT,
	TSTBUS_TMRLUT,
	TSTBUS_OCSC,
	TSTBUS_UTP_HCI,
	TSTBUS_COMBINED,
	TSTBUS_WRAPPER,
	TSTBUS_UNIPRO,
	TSTBUS_MAX,
पूर्ण;

अटल काष्ठा ufs_qcom_host *ufs_qcom_hosts[MAX_UFS_QCOM_HOSTS];

अटल व्योम ufs_qcom_get_शेष_testbus_cfg(काष्ठा ufs_qcom_host *host);
अटल पूर्णांक ufs_qcom_set_dme_vs_core_clk_ctrl_clear_भाग(काष्ठा ufs_hba *hba,
						       u32 clk_cycles);

अटल काष्ठा ufs_qcom_host *rcdev_to_ufs_host(काष्ठा reset_controller_dev *rcd)
अणु
	वापस container_of(rcd, काष्ठा ufs_qcom_host, rcdev);
पूर्ण

अटल व्योम ufs_qcom_dump_regs_wrapper(काष्ठा ufs_hba *hba, पूर्णांक offset, पूर्णांक len,
				       स्थिर अक्षर *prefix, व्योम *priv)
अणु
	ufshcd_dump_regs(hba, offset, len * 4, prefix);
पूर्ण

अटल पूर्णांक ufs_qcom_get_connected_tx_lanes(काष्ठा ufs_hba *hba, u32 *tx_lanes)
अणु
	पूर्णांक err = 0;

	err = ufshcd_dme_get(hba,
			UIC_ARG_MIB(PA_CONNECTEDTXDATALANES), tx_lanes);
	अगर (err)
		dev_err(hba->dev, "%s: couldn't read PA_CONNECTEDTXDATALANES %d\n",
				__func__, err);

	वापस err;
पूर्ण

अटल पूर्णांक ufs_qcom_host_clk_get(काष्ठा device *dev,
		स्थिर अक्षर *name, काष्ठा clk **clk_out, bool optional)
अणु
	काष्ठा clk *clk;
	पूर्णांक err = 0;

	clk = devm_clk_get(dev, name);
	अगर (!IS_ERR(clk)) अणु
		*clk_out = clk;
		वापस 0;
	पूर्ण

	err = PTR_ERR(clk);

	अगर (optional && err == -ENOENT) अणु
		*clk_out = शून्य;
		वापस 0;
	पूर्ण

	अगर (err != -EPROBE_DEFER)
		dev_err(dev, "failed to get %s err %d\n", name, err);

	वापस err;
पूर्ण

अटल पूर्णांक ufs_qcom_host_clk_enable(काष्ठा device *dev,
		स्थिर अक्षर *name, काष्ठा clk *clk)
अणु
	पूर्णांक err = 0;

	err = clk_prepare_enable(clk);
	अगर (err)
		dev_err(dev, "%s: %s enable failed %d\n", __func__, name, err);

	वापस err;
पूर्ण

अटल व्योम ufs_qcom_disable_lane_clks(काष्ठा ufs_qcom_host *host)
अणु
	अगर (!host->is_lane_clks_enabled)
		वापस;

	clk_disable_unprepare(host->tx_l1_sync_clk);
	clk_disable_unprepare(host->tx_l0_sync_clk);
	clk_disable_unprepare(host->rx_l1_sync_clk);
	clk_disable_unprepare(host->rx_l0_sync_clk);

	host->is_lane_clks_enabled = false;
पूर्ण

अटल पूर्णांक ufs_qcom_enable_lane_clks(काष्ठा ufs_qcom_host *host)
अणु
	पूर्णांक err = 0;
	काष्ठा device *dev = host->hba->dev;

	अगर (host->is_lane_clks_enabled)
		वापस 0;

	err = ufs_qcom_host_clk_enable(dev, "rx_lane0_sync_clk",
		host->rx_l0_sync_clk);
	अगर (err)
		जाओ out;

	err = ufs_qcom_host_clk_enable(dev, "tx_lane0_sync_clk",
		host->tx_l0_sync_clk);
	अगर (err)
		जाओ disable_rx_l0;

	err = ufs_qcom_host_clk_enable(dev, "rx_lane1_sync_clk",
			host->rx_l1_sync_clk);
	अगर (err)
		जाओ disable_tx_l0;

	err = ufs_qcom_host_clk_enable(dev, "tx_lane1_sync_clk",
			host->tx_l1_sync_clk);
	अगर (err)
		जाओ disable_rx_l1;

	host->is_lane_clks_enabled = true;
	जाओ out;

disable_rx_l1:
	clk_disable_unprepare(host->rx_l1_sync_clk);
disable_tx_l0:
	clk_disable_unprepare(host->tx_l0_sync_clk);
disable_rx_l0:
	clk_disable_unprepare(host->rx_l0_sync_clk);
out:
	वापस err;
पूर्ण

अटल पूर्णांक ufs_qcom_init_lane_clks(काष्ठा ufs_qcom_host *host)
अणु
	पूर्णांक err = 0;
	काष्ठा device *dev = host->hba->dev;

	अगर (has_acpi_companion(dev))
		वापस 0;

	err = ufs_qcom_host_clk_get(dev, "rx_lane0_sync_clk",
					&host->rx_l0_sync_clk, false);
	अगर (err)
		जाओ out;

	err = ufs_qcom_host_clk_get(dev, "tx_lane0_sync_clk",
					&host->tx_l0_sync_clk, false);
	अगर (err)
		जाओ out;

	/* In हाल of single lane per direction, करोn't पढ़ो lane1 घड़ीs */
	अगर (host->hba->lanes_per_direction > 1) अणु
		err = ufs_qcom_host_clk_get(dev, "rx_lane1_sync_clk",
			&host->rx_l1_sync_clk, false);
		अगर (err)
			जाओ out;

		err = ufs_qcom_host_clk_get(dev, "tx_lane1_sync_clk",
			&host->tx_l1_sync_clk, true);
	पूर्ण
out:
	वापस err;
पूर्ण

अटल पूर्णांक ufs_qcom_link_startup_post_change(काष्ठा ufs_hba *hba)
अणु
	u32 tx_lanes;

	वापस ufs_qcom_get_connected_tx_lanes(hba, &tx_lanes);
पूर्ण

अटल पूर्णांक ufs_qcom_check_hibern8(काष्ठा ufs_hba *hba)
अणु
	पूर्णांक err;
	u32 tx_fsm_val = 0;
	अचिन्हित दीर्घ समयout = jअगरfies + msecs_to_jअगरfies(HBRN8_POLL_TOUT_MS);

	करो अणु
		err = ufshcd_dme_get(hba,
				UIC_ARG_MIB_SEL(MPHY_TX_FSM_STATE,
					UIC_ARG_MPHY_TX_GEN_SEL_INDEX(0)),
				&tx_fsm_val);
		अगर (err || tx_fsm_val == TX_FSM_HIBERN8)
			अवरोध;

		/* sleep क्रम max. 200us */
		usleep_range(100, 200);
	पूर्ण जबतक (समय_beक्रमe(jअगरfies, समयout));

	/*
	 * we might have scheduled out क्रम दीर्घ during polling so
	 * check the state again.
	 */
	अगर (समय_after(jअगरfies, समयout))
		err = ufshcd_dme_get(hba,
				UIC_ARG_MIB_SEL(MPHY_TX_FSM_STATE,
					UIC_ARG_MPHY_TX_GEN_SEL_INDEX(0)),
				&tx_fsm_val);

	अगर (err) अणु
		dev_err(hba->dev, "%s: unable to get TX_FSM_STATE, err %d\n",
				__func__, err);
	पूर्ण अन्यथा अगर (tx_fsm_val != TX_FSM_HIBERN8) अणु
		err = tx_fsm_val;
		dev_err(hba->dev, "%s: invalid TX_FSM_STATE = %d\n",
				__func__, err);
	पूर्ण

	वापस err;
पूर्ण

अटल व्योम ufs_qcom_select_unipro_mode(काष्ठा ufs_qcom_host *host)
अणु
	ufshcd_rmwl(host->hba, QUNIPRO_SEL,
		   ufs_qcom_cap_qunipro(host) ? QUNIPRO_SEL : 0,
		   REG_UFS_CFG1);
	/* make sure above configuration is applied beक्रमe we वापस */
	mb();
पूर्ण

/*
 * ufs_qcom_host_reset - reset host controller and PHY
 */
अटल पूर्णांक ufs_qcom_host_reset(काष्ठा ufs_hba *hba)
अणु
	पूर्णांक ret = 0;
	काष्ठा ufs_qcom_host *host = ufshcd_get_variant(hba);
	bool reenable_पूर्णांकr = false;

	अगर (!host->core_reset) अणु
		dev_warn(hba->dev, "%s: reset control not set\n", __func__);
		जाओ out;
	पूर्ण

	reenable_पूर्णांकr = hba->is_irq_enabled;
	disable_irq(hba->irq);
	hba->is_irq_enabled = false;

	ret = reset_control_निश्चित(host->core_reset);
	अगर (ret) अणु
		dev_err(hba->dev, "%s: core_reset assert failed, err = %d\n",
				 __func__, ret);
		जाओ out;
	पूर्ण

	/*
	 * The hardware requirement क्रम delay between निश्चित/deनिश्चित
	 * is at least 3-4 sleep घड़ी (32.7KHz) cycles, which comes to
	 * ~125us (4/32768). To be on the safe side add 200us delay.
	 */
	usleep_range(200, 210);

	ret = reset_control_deनिश्चित(host->core_reset);
	अगर (ret)
		dev_err(hba->dev, "%s: core_reset deassert failed, err = %d\n",
				 __func__, ret);

	usleep_range(1000, 1100);

	अगर (reenable_पूर्णांकr) अणु
		enable_irq(hba->irq);
		hba->is_irq_enabled = true;
	पूर्ण

out:
	वापस ret;
पूर्ण

अटल पूर्णांक ufs_qcom_घातer_up_sequence(काष्ठा ufs_hba *hba)
अणु
	काष्ठा ufs_qcom_host *host = ufshcd_get_variant(hba);
	काष्ठा phy *phy = host->generic_phy;
	पूर्णांक ret = 0;
	bool is_rate_B = (UFS_QCOM_LIMIT_HS_RATE == PA_HS_MODE_B)
							? true : false;

	/* Reset UFS Host Controller and PHY */
	ret = ufs_qcom_host_reset(hba);
	अगर (ret)
		dev_warn(hba->dev, "%s: host reset returned %d\n",
				  __func__, ret);

	अगर (is_rate_B)
		phy_set_mode(phy, PHY_MODE_UFS_HS_B);

	/* phy initialization - calibrate the phy */
	ret = phy_init(phy);
	अगर (ret) अणु
		dev_err(hba->dev, "%s: phy init failed, ret = %d\n",
			__func__, ret);
		जाओ out;
	पूर्ण

	/* घातer on phy - start serdes and phy's घातer and घड़ीs */
	ret = phy_घातer_on(phy);
	अगर (ret) अणु
		dev_err(hba->dev, "%s: phy power on failed, ret = %d\n",
			__func__, ret);
		जाओ out_disable_phy;
	पूर्ण

	ufs_qcom_select_unipro_mode(host);

	वापस 0;

out_disable_phy:
	phy_निकास(phy);
out:
	वापस ret;
पूर्ण

/*
 * The UTP controller has a number of पूर्णांकernal घड़ी gating cells (CGCs).
 * Internal hardware sub-modules within the UTP controller control the CGCs.
 * Hardware CGCs disable the घड़ी to inactivate UTP sub-modules not involved
 * in a specअगरic operation, UTP controller CGCs are by शेष disabled and
 * this function enables them (after every UFS link startup) to save some घातer
 * leakage.
 */
अटल व्योम ufs_qcom_enable_hw_clk_gating(काष्ठा ufs_hba *hba)
अणु
	ufshcd_ग_लिखोl(hba,
		ufshcd_पढ़ोl(hba, REG_UFS_CFG2) | REG_UFS_CFG2_CGC_EN_ALL,
		REG_UFS_CFG2);

	/* Ensure that HW घड़ी gating is enabled beक्रमe next operations */
	mb();
पूर्ण

अटल पूर्णांक ufs_qcom_hce_enable_notअगरy(काष्ठा ufs_hba *hba,
				      क्रमागत ufs_notअगरy_change_status status)
अणु
	काष्ठा ufs_qcom_host *host = ufshcd_get_variant(hba);
	पूर्णांक err = 0;

	चयन (status) अणु
	हाल PRE_CHANGE:
		ufs_qcom_घातer_up_sequence(hba);
		/*
		 * The PHY PLL output is the source of tx/rx lane symbol
		 * घड़ीs, hence, enable the lane घड़ीs only after PHY
		 * is initialized.
		 */
		err = ufs_qcom_enable_lane_clks(host);
		अवरोध;
	हाल POST_CHANGE:
		/* check अगर UFS PHY moved from DISABLED to HIBERN8 */
		err = ufs_qcom_check_hibern8(hba);
		ufs_qcom_enable_hw_clk_gating(hba);
		ufs_qcom_ice_enable(host);
		अवरोध;
	शेष:
		dev_err(hba->dev, "%s: invalid status %d\n", __func__, status);
		err = -EINVAL;
		अवरोध;
	पूर्ण
	वापस err;
पूर्ण

/*
 * Returns zero क्रम success and non-zero in हाल of a failure
 */
अटल पूर्णांक ufs_qcom_cfg_समयrs(काष्ठा ufs_hba *hba, u32 gear,
			       u32 hs, u32 rate, bool update_link_startup_समयr)
अणु
	पूर्णांक ret = 0;
	काष्ठा ufs_qcom_host *host = ufshcd_get_variant(hba);
	काष्ठा ufs_clk_info *clki;
	u32 core_clk_period_in_ns;
	u32 tx_clk_cycles_per_us = 0;
	अचिन्हित दीर्घ core_clk_rate = 0;
	u32 core_clk_cycles_per_us = 0;

	अटल u32 pwm_fr_table[][2] = अणु
		अणुUFS_PWM_G1, 0x1पूर्ण,
		अणुUFS_PWM_G2, 0x1पूर्ण,
		अणुUFS_PWM_G3, 0x1पूर्ण,
		अणुUFS_PWM_G4, 0x1पूर्ण,
	पूर्ण;

	अटल u32 hs_fr_table_rA[][2] = अणु
		अणुUFS_HS_G1, 0x1Fपूर्ण,
		अणुUFS_HS_G2, 0x3eपूर्ण,
		अणुUFS_HS_G3, 0x7Dपूर्ण,
	पूर्ण;

	अटल u32 hs_fr_table_rB[][2] = अणु
		अणुUFS_HS_G1, 0x24पूर्ण,
		अणुUFS_HS_G2, 0x49पूर्ण,
		अणुUFS_HS_G3, 0x92पूर्ण,
	पूर्ण;

	/*
	 * The Qunipro controller करोes not use following रेजिस्टरs:
	 * SYS1CLK_1US_REG, TX_SYMBOL_CLK_1US_REG, CLK_NS_REG &
	 * UFS_REG_PA_LINK_STARTUP_TIMER
	 * But UTP controller uses SYS1CLK_1US_REG रेजिस्टर क्रम Interrupt
	 * Aggregation logic.
	*/
	अगर (ufs_qcom_cap_qunipro(host) && !ufshcd_is_पूर्णांकr_aggr_allowed(hba))
		जाओ out;

	अगर (gear == 0) अणु
		dev_err(hba->dev, "%s: invalid gear = %d\n", __func__, gear);
		जाओ out_error;
	पूर्ण

	list_क्रम_each_entry(clki, &hba->clk_list_head, list) अणु
		अगर (!म_भेद(clki->name, "core_clk"))
			core_clk_rate = clk_get_rate(clki->clk);
	पूर्ण

	/* If frequency is smaller than 1MHz, set to 1MHz */
	अगर (core_clk_rate < DEFAULT_CLK_RATE_HZ)
		core_clk_rate = DEFAULT_CLK_RATE_HZ;

	core_clk_cycles_per_us = core_clk_rate / USEC_PER_SEC;
	अगर (ufshcd_पढ़ोl(hba, REG_UFS_SYS1CLK_1US) != core_clk_cycles_per_us) अणु
		ufshcd_ग_लिखोl(hba, core_clk_cycles_per_us, REG_UFS_SYS1CLK_1US);
		/*
		 * make sure above ग_लिखो माला_लो applied beक्रमe we वापस from
		 * this function.
		 */
		mb();
	पूर्ण

	अगर (ufs_qcom_cap_qunipro(host))
		जाओ out;

	core_clk_period_in_ns = NSEC_PER_SEC / core_clk_rate;
	core_clk_period_in_ns <<= OFFSET_CLK_NS_REG;
	core_clk_period_in_ns &= MASK_CLK_NS_REG;

	चयन (hs) अणु
	हाल FASTAUTO_MODE:
	हाल FAST_MODE:
		अगर (rate == PA_HS_MODE_A) अणु
			अगर (gear > ARRAY_SIZE(hs_fr_table_rA)) अणु
				dev_err(hba->dev,
					"%s: index %d exceeds table size %zu\n",
					__func__, gear,
					ARRAY_SIZE(hs_fr_table_rA));
				जाओ out_error;
			पूर्ण
			tx_clk_cycles_per_us = hs_fr_table_rA[gear-1][1];
		पूर्ण अन्यथा अगर (rate == PA_HS_MODE_B) अणु
			अगर (gear > ARRAY_SIZE(hs_fr_table_rB)) अणु
				dev_err(hba->dev,
					"%s: index %d exceeds table size %zu\n",
					__func__, gear,
					ARRAY_SIZE(hs_fr_table_rB));
				जाओ out_error;
			पूर्ण
			tx_clk_cycles_per_us = hs_fr_table_rB[gear-1][1];
		पूर्ण अन्यथा अणु
			dev_err(hba->dev, "%s: invalid rate = %d\n",
				__func__, rate);
			जाओ out_error;
		पूर्ण
		अवरोध;
	हाल SLOWAUTO_MODE:
	हाल SLOW_MODE:
		अगर (gear > ARRAY_SIZE(pwm_fr_table)) अणु
			dev_err(hba->dev,
					"%s: index %d exceeds table size %zu\n",
					__func__, gear,
					ARRAY_SIZE(pwm_fr_table));
			जाओ out_error;
		पूर्ण
		tx_clk_cycles_per_us = pwm_fr_table[gear-1][1];
		अवरोध;
	हाल UNCHANGED:
	शेष:
		dev_err(hba->dev, "%s: invalid mode = %d\n", __func__, hs);
		जाओ out_error;
	पूर्ण

	अगर (ufshcd_पढ़ोl(hba, REG_UFS_TX_SYMBOL_CLK_NS_US) !=
	    (core_clk_period_in_ns | tx_clk_cycles_per_us)) अणु
		/* this रेजिस्टर 2 fields shall be written at once */
		ufshcd_ग_लिखोl(hba, core_clk_period_in_ns | tx_clk_cycles_per_us,
			      REG_UFS_TX_SYMBOL_CLK_NS_US);
		/*
		 * make sure above ग_लिखो माला_लो applied beक्रमe we वापस from
		 * this function.
		 */
		mb();
	पूर्ण

	अगर (update_link_startup_समयr) अणु
		ufshcd_ग_लिखोl(hba, ((core_clk_rate / MSEC_PER_SEC) * 100),
			      REG_UFS_PA_LINK_STARTUP_TIMER);
		/*
		 * make sure that this configuration is applied beक्रमe
		 * we वापस
		 */
		mb();
	पूर्ण
	जाओ out;

out_error:
	ret = -EINVAL;
out:
	वापस ret;
पूर्ण

अटल पूर्णांक ufs_qcom_link_startup_notअगरy(काष्ठा ufs_hba *hba,
					क्रमागत ufs_notअगरy_change_status status)
अणु
	पूर्णांक err = 0;
	काष्ठा ufs_qcom_host *host = ufshcd_get_variant(hba);

	चयन (status) अणु
	हाल PRE_CHANGE:
		अगर (ufs_qcom_cfg_समयrs(hba, UFS_PWM_G1, SLOWAUTO_MODE,
					0, true)) अणु
			dev_err(hba->dev, "%s: ufs_qcom_cfg_timers() failed\n",
				__func__);
			err = -EINVAL;
			जाओ out;
		पूर्ण

		अगर (ufs_qcom_cap_qunipro(host))
			/*
			 * set unipro core घड़ी cycles to 150 & clear घड़ी
			 * भागider
			 */
			err = ufs_qcom_set_dme_vs_core_clk_ctrl_clear_भाग(hba,
									  150);

		/*
		 * Some UFS devices (and may be host) have issues अगर LCC is
		 * enabled. So we are setting PA_Local_TX_LCC_Enable to 0
		 * beक्रमe link startup which will make sure that both host
		 * and device TX LCC are disabled once link startup is
		 * completed.
		 */
		अगर (ufshcd_get_local_unipro_ver(hba) != UFS_UNIPRO_VER_1_41)
			err = ufshcd_disable_host_tx_lcc(hba);

		अवरोध;
	हाल POST_CHANGE:
		ufs_qcom_link_startup_post_change(hba);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

out:
	वापस err;
पूर्ण

अटल व्योम ufs_qcom_device_reset_ctrl(काष्ठा ufs_hba *hba, bool निश्चितed)
अणु
	काष्ठा ufs_qcom_host *host = ufshcd_get_variant(hba);

	/* reset gpio is optional */
	अगर (!host->device_reset)
		वापस;

	gpiod_set_value_cansleep(host->device_reset, निश्चितed);
पूर्ण

अटल पूर्णांक ufs_qcom_suspend(काष्ठा ufs_hba *hba, क्रमागत ufs_pm_op pm_op)
अणु
	काष्ठा ufs_qcom_host *host = ufshcd_get_variant(hba);
	काष्ठा phy *phy = host->generic_phy;

	अगर (ufs_qcom_is_link_off(hba)) अणु
		/*
		 * Disable the tx/rx lane symbol घड़ीs beक्रमe PHY is
		 * घातered करोwn as the PLL source should be disabled
		 * after करोwnstream घड़ीs are disabled.
		 */
		ufs_qcom_disable_lane_clks(host);
		phy_घातer_off(phy);

		/* reset the connected UFS device during घातer करोwn */
		ufs_qcom_device_reset_ctrl(hba, true);

	पूर्ण अन्यथा अगर (!ufs_qcom_is_link_active(hba)) अणु
		ufs_qcom_disable_lane_clks(host);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ufs_qcom_resume(काष्ठा ufs_hba *hba, क्रमागत ufs_pm_op pm_op)
अणु
	काष्ठा ufs_qcom_host *host = ufshcd_get_variant(hba);
	काष्ठा phy *phy = host->generic_phy;
	पूर्णांक err;

	अगर (ufs_qcom_is_link_off(hba)) अणु
		err = phy_घातer_on(phy);
		अगर (err) अणु
			dev_err(hba->dev, "%s: failed PHY power on: %d\n",
				__func__, err);
			वापस err;
		पूर्ण

		err = ufs_qcom_enable_lane_clks(host);
		अगर (err)
			वापस err;

	पूर्ण अन्यथा अगर (!ufs_qcom_is_link_active(hba)) अणु
		err = ufs_qcom_enable_lane_clks(host);
		अगर (err)
			वापस err;
	पूर्ण

	err = ufs_qcom_ice_resume(host);
	अगर (err)
		वापस err;

	hba->is_sys_suspended = false;
	वापस 0;
पूर्ण

अटल व्योम ufs_qcom_dev_ref_clk_ctrl(काष्ठा ufs_qcom_host *host, bool enable)
अणु
	अगर (host->dev_ref_clk_ctrl_mmio &&
	    (enable ^ host->is_dev_ref_clk_enabled)) अणु
		u32 temp = पढ़ोl_relaxed(host->dev_ref_clk_ctrl_mmio);

		अगर (enable)
			temp |= host->dev_ref_clk_en_mask;
		अन्यथा
			temp &= ~host->dev_ref_clk_en_mask;

		/*
		 * If we are here to disable this घड़ी it might be immediately
		 * after entering पूर्णांकo hibern8 in which हाल we need to make
		 * sure that device ref_clk is active क्रम specअगरic समय after
		 * hibern8 enter.
		 */
		अगर (!enable) अणु
			अचिन्हित दीर्घ gating_रुको;

			gating_रुको = host->hba->dev_info.clk_gating_रुको_us;
			अगर (!gating_रुको) अणु
				udelay(1);
			पूर्ण अन्यथा अणु
				/*
				 * bRefClkGatingWaitTime defines the minimum
				 * समय क्रम which the reference घड़ी is
				 * required by device during transition from
				 * HS-MODE to LS-MODE or HIBERN8 state. Give it
				 * more delay to be on the safe side.
				 */
				gating_रुको += 10;
				usleep_range(gating_रुको, gating_रुको + 10);
			पूर्ण
		पूर्ण

		ग_लिखोl_relaxed(temp, host->dev_ref_clk_ctrl_mmio);

		/* ensure that ref_clk is enabled/disabled beक्रमe we वापस */
		wmb();

		/*
		 * If we call hibern8 निकास after this, we need to make sure that
		 * device ref_clk is stable क्रम at least 1us beक्रमe the hibern8
		 * निकास command.
		 */
		अगर (enable)
			udelay(1);

		host->is_dev_ref_clk_enabled = enable;
	पूर्ण
पूर्ण

अटल पूर्णांक ufs_qcom_pwr_change_notअगरy(काष्ठा ufs_hba *hba,
				क्रमागत ufs_notअगरy_change_status status,
				काष्ठा ufs_pa_layer_attr *dev_max_params,
				काष्ठा ufs_pa_layer_attr *dev_req_params)
अणु
	काष्ठा ufs_qcom_host *host = ufshcd_get_variant(hba);
	काष्ठा ufs_dev_params ufs_qcom_cap;
	पूर्णांक ret = 0;

	अगर (!dev_req_params) अणु
		pr_err("%s: incoming dev_req_params is NULL\n", __func__);
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	चयन (status) अणु
	हाल PRE_CHANGE:
		ufshcd_init_pwr_dev_param(&ufs_qcom_cap);
		ufs_qcom_cap.hs_rate = UFS_QCOM_LIMIT_HS_RATE;

		अगर (host->hw_ver.major == 0x1) अणु
			/*
			 * HS-G3 operations may not reliably work on legacy QCOM
			 * UFS host controller hardware even though capability
			 * exchange during link startup phase may end up
			 * negotiating maximum supported gear as G3.
			 * Hence करोwngrade the maximum supported gear to HS-G2.
			 */
			अगर (ufs_qcom_cap.hs_tx_gear > UFS_HS_G2)
				ufs_qcom_cap.hs_tx_gear = UFS_HS_G2;
			अगर (ufs_qcom_cap.hs_rx_gear > UFS_HS_G2)
				ufs_qcom_cap.hs_rx_gear = UFS_HS_G2;
		पूर्ण

		ret = ufshcd_get_pwr_dev_param(&ufs_qcom_cap,
					       dev_max_params,
					       dev_req_params);
		अगर (ret) अणु
			pr_err("%s: failed to determine capabilities\n",
					__func__);
			जाओ out;
		पूर्ण

		/* enable the device ref घड़ी beक्रमe changing to HS mode */
		अगर (!ufshcd_is_hs_mode(&hba->pwr_info) &&
			ufshcd_is_hs_mode(dev_req_params))
			ufs_qcom_dev_ref_clk_ctrl(host, true);

		अगर (host->hw_ver.major >= 0x4) अणु
			ufshcd_dme_configure_adapt(hba,
						dev_req_params->gear_tx,
						PA_INITIAL_ADAPT);
		पूर्ण
		अवरोध;
	हाल POST_CHANGE:
		अगर (ufs_qcom_cfg_समयrs(hba, dev_req_params->gear_rx,
					dev_req_params->pwr_rx,
					dev_req_params->hs_rate, false)) अणु
			dev_err(hba->dev, "%s: ufs_qcom_cfg_timers() failed\n",
				__func__);
			/*
			 * we वापस error code at the end of the routine,
			 * but जारी to configure UFS_PHY_TX_LANE_ENABLE
			 * and bus voting as usual
			 */
			ret = -EINVAL;
		पूर्ण

		/* cache the घातer mode parameters to use पूर्णांकernally */
		स_नकल(&host->dev_req_params,
				dev_req_params, माप(*dev_req_params));

		/* disable the device ref घड़ी अगर entered PWM mode */
		अगर (ufshcd_is_hs_mode(&hba->pwr_info) &&
			!ufshcd_is_hs_mode(dev_req_params))
			ufs_qcom_dev_ref_clk_ctrl(host, false);
		अवरोध;
	शेष:
		ret = -EINVAL;
		अवरोध;
	पूर्ण
out:
	वापस ret;
पूर्ण

अटल पूर्णांक ufs_qcom_quirk_host_pa_saveconfigसमय(काष्ठा ufs_hba *hba)
अणु
	पूर्णांक err;
	u32 pa_vs_config_reg1;

	err = ufshcd_dme_get(hba, UIC_ARG_MIB(PA_VS_CONFIG_REG1),
			     &pa_vs_config_reg1);
	अगर (err)
		जाओ out;

	/* Allow extension of MSB bits of PA_SaveConfigTime attribute */
	err = ufshcd_dme_set(hba, UIC_ARG_MIB(PA_VS_CONFIG_REG1),
			    (pa_vs_config_reg1 | (1 << 12)));

out:
	वापस err;
पूर्ण

अटल पूर्णांक ufs_qcom_apply_dev_quirks(काष्ठा ufs_hba *hba)
अणु
	पूर्णांक err = 0;

	अगर (hba->dev_quirks & UFS_DEVICE_QUIRK_HOST_PA_SAVECONFIGTIME)
		err = ufs_qcom_quirk_host_pa_saveconfigसमय(hba);

	अगर (hba->dev_info.wmanufacturerid == UFS_VENDOR_WDC)
		hba->dev_quirks |= UFS_DEVICE_QUIRK_HOST_PA_TACTIVATE;

	वापस err;
पूर्ण

अटल u32 ufs_qcom_get_ufs_hci_version(काष्ठा ufs_hba *hba)
अणु
	काष्ठा ufs_qcom_host *host = ufshcd_get_variant(hba);

	अगर (host->hw_ver.major == 0x1)
		वापस ufshci_version(1, 1);
	अन्यथा
		वापस ufshci_version(2, 0);
पूर्ण

/**
 * ufs_qcom_advertise_quirks - advertise the known QCOM UFS controller quirks
 * @hba: host controller instance
 *
 * QCOM UFS host controller might have some non standard behaviours (quirks)
 * than what is specअगरied by UFSHCI specअगरication. Advertise all such
 * quirks to standard UFS host controller driver so standard takes them पूर्णांकo
 * account.
 */
अटल व्योम ufs_qcom_advertise_quirks(काष्ठा ufs_hba *hba)
अणु
	काष्ठा ufs_qcom_host *host = ufshcd_get_variant(hba);

	अगर (host->hw_ver.major == 0x01) अणु
		hba->quirks |= UFSHCD_QUIRK_DELAY_BEFORE_DME_CMDS
			    | UFSHCD_QUIRK_BROKEN_PA_RXHSUNTERMCAP
			    | UFSHCD_QUIRK_DME_PEER_ACCESS_AUTO_MODE;

		अगर (host->hw_ver.minor == 0x0001 && host->hw_ver.step == 0x0001)
			hba->quirks |= UFSHCD_QUIRK_BROKEN_INTR_AGGR;

		hba->quirks |= UFSHCD_QUIRK_BROKEN_LCC;
	पूर्ण

	अगर (host->hw_ver.major == 0x2) अणु
		hba->quirks |= UFSHCD_QUIRK_BROKEN_UFS_HCI_VERSION;

		अगर (!ufs_qcom_cap_qunipro(host))
			/* Legacy UniPro mode still need following quirks */
			hba->quirks |= (UFSHCD_QUIRK_DELAY_BEFORE_DME_CMDS
				| UFSHCD_QUIRK_DME_PEER_ACCESS_AUTO_MODE
				| UFSHCD_QUIRK_BROKEN_PA_RXHSUNTERMCAP);
	पूर्ण
पूर्ण

अटल व्योम ufs_qcom_set_caps(काष्ठा ufs_hba *hba)
अणु
	काष्ठा ufs_qcom_host *host = ufshcd_get_variant(hba);

	hba->caps |= UFSHCD_CAP_CLK_GATING | UFSHCD_CAP_HIBERN8_WITH_CLK_GATING;
	hba->caps |= UFSHCD_CAP_CLK_SCALING;
	hba->caps |= UFSHCD_CAP_AUTO_BKOPS_SUSPEND;
	hba->caps |= UFSHCD_CAP_WB_EN;
	hba->caps |= UFSHCD_CAP_CRYPTO;
	hba->caps |= UFSHCD_CAP_AGGR_POWER_COLLAPSE;

	अगर (host->hw_ver.major >= 0x2) अणु
		host->caps = UFS_QCOM_CAP_QUNIPRO |
			     UFS_QCOM_CAP_RETAIN_SEC_CFG_AFTER_PWR_COLLAPSE;
	पूर्ण
पूर्ण

/**
 * ufs_qcom_setup_घड़ीs - enables/disable घड़ीs
 * @hba: host controller instance
 * @on: If true, enable घड़ीs अन्यथा disable them.
 * @status: PRE_CHANGE or POST_CHANGE notअगरy
 *
 * Returns 0 on success, non-zero on failure.
 */
अटल पूर्णांक ufs_qcom_setup_घड़ीs(काष्ठा ufs_hba *hba, bool on,
				 क्रमागत ufs_notअगरy_change_status status)
अणु
	काष्ठा ufs_qcom_host *host = ufshcd_get_variant(hba);
	पूर्णांक err = 0;

	/*
	 * In हाल ufs_qcom_init() is not yet करोne, simply ignore.
	 * This ufs_qcom_setup_घड़ीs() shall be called from
	 * ufs_qcom_init() after init is करोne.
	 */
	अगर (!host)
		वापस 0;

	चयन (status) अणु
	हाल PRE_CHANGE:
		अगर (!on) अणु
			अगर (!ufs_qcom_is_link_active(hba)) अणु
				/* disable device ref_clk */
				ufs_qcom_dev_ref_clk_ctrl(host, false);
			पूर्ण
		पूर्ण
		अवरोध;
	हाल POST_CHANGE:
		अगर (on) अणु
			/* enable the device ref घड़ी क्रम HS mode*/
			अगर (ufshcd_is_hs_mode(&hba->pwr_info))
				ufs_qcom_dev_ref_clk_ctrl(host, true);
		पूर्ण
		अवरोध;
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक
ufs_qcom_reset_निश्चित(काष्ठा reset_controller_dev *rcdev, अचिन्हित दीर्घ id)
अणु
	काष्ठा ufs_qcom_host *host = rcdev_to_ufs_host(rcdev);

	/* Currently this code only knows about a single reset. */
	WARN_ON(id);
	ufs_qcom_निश्चित_reset(host->hba);
	/* provide 1ms delay to let the reset pulse propagate. */
	usleep_range(1000, 1100);
	वापस 0;
पूर्ण

अटल पूर्णांक
ufs_qcom_reset_deनिश्चित(काष्ठा reset_controller_dev *rcdev, अचिन्हित दीर्घ id)
अणु
	काष्ठा ufs_qcom_host *host = rcdev_to_ufs_host(rcdev);

	/* Currently this code only knows about a single reset. */
	WARN_ON(id);
	ufs_qcom_deनिश्चित_reset(host->hba);

	/*
	 * after reset deनिश्चितion, phy will need all ref घड़ीs,
	 * voltage, current to settle करोwn beक्रमe starting serdes.
	 */
	usleep_range(1000, 1100);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा reset_control_ops ufs_qcom_reset_ops = अणु
	.निश्चित = ufs_qcom_reset_निश्चित,
	.deनिश्चित = ufs_qcom_reset_deनिश्चित,
पूर्ण;

#घोषणा	ANDROID_BOOT_DEV_MAX	30
अटल अक्षर android_boot_dev[ANDROID_BOOT_DEV_MAX];

#अगर_अघोषित MODULE
अटल पूर्णांक __init get_android_boot_dev(अक्षर *str)
अणु
	strlcpy(android_boot_dev, str, ANDROID_BOOT_DEV_MAX);
	वापस 1;
पूर्ण
__setup("androidboot.bootdevice=", get_android_boot_dev);
#पूर्ण_अगर

/**
 * ufs_qcom_init - bind phy with controller
 * @hba: host controller instance
 *
 * Binds PHY with controller and घातers up PHY enabling घड़ीs
 * and regulators.
 *
 * Returns -EPROBE_DEFER अगर binding fails, वापसs negative error
 * on phy घातer up failure and वापसs zero on success.
 */
अटल पूर्णांक ufs_qcom_init(काष्ठा ufs_hba *hba)
अणु
	पूर्णांक err;
	काष्ठा device *dev = hba->dev;
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);
	काष्ठा ufs_qcom_host *host;
	काष्ठा resource *res;
	काष्ठा ufs_clk_info *clki;

	अगर (म_माप(android_boot_dev) && म_भेद(android_boot_dev, dev_name(dev)))
		वापस -ENODEV;

	host = devm_kzalloc(dev, माप(*host), GFP_KERNEL);
	अगर (!host) अणु
		err = -ENOMEM;
		dev_err(dev, "%s: no memory for qcom ufs host\n", __func__);
		जाओ out;
	पूर्ण

	/* Make a two way bind between the qcom host and the hba */
	host->hba = hba;
	ufshcd_set_variant(hba, host);

	/* Setup the reset control of HCI */
	host->core_reset = devm_reset_control_get(hba->dev, "rst");
	अगर (IS_ERR(host->core_reset)) अणु
		err = PTR_ERR(host->core_reset);
		dev_warn(dev, "Failed to get reset control %d\n", err);
		host->core_reset = शून्य;
		err = 0;
	पूर्ण

	/* Fire up the reset controller. Failure here is non-fatal. */
	host->rcdev.of_node = dev->of_node;
	host->rcdev.ops = &ufs_qcom_reset_ops;
	host->rcdev.owner = dev->driver->owner;
	host->rcdev.nr_resets = 1;
	err = devm_reset_controller_रेजिस्टर(dev, &host->rcdev);
	अगर (err) अणु
		dev_warn(dev, "Failed to register reset controller\n");
		err = 0;
	पूर्ण

	/*
	 * voting/devoting device ref_clk source is समय consuming hence
	 * skip devoting it during aggressive घड़ी gating. This घड़ी
	 * will still be gated off during runसमय suspend.
	 */
	host->generic_phy = devm_phy_get(dev, "ufsphy");

	अगर (host->generic_phy == ERR_PTR(-EPROBE_DEFER)) अणु
		/*
		 * UFS driver might be probed beक्रमe the phy driver करोes.
		 * In that हाल we would like to वापस EPROBE_DEFER code.
		 */
		err = -EPROBE_DEFER;
		dev_warn(dev, "%s: required phy device. hasn't probed yet. err = %d\n",
			__func__, err);
		जाओ out_variant_clear;
	पूर्ण अन्यथा अगर (IS_ERR(host->generic_phy)) अणु
		अगर (has_acpi_companion(dev)) अणु
			host->generic_phy = शून्य;
		पूर्ण अन्यथा अणु
			err = PTR_ERR(host->generic_phy);
			dev_err(dev, "%s: PHY get failed %d\n", __func__, err);
			जाओ out_variant_clear;
		पूर्ण
	पूर्ण

	host->device_reset = devm_gpiod_get_optional(dev, "reset",
						     GPIOD_OUT_HIGH);
	अगर (IS_ERR(host->device_reset)) अणु
		err = PTR_ERR(host->device_reset);
		अगर (err != -EPROBE_DEFER)
			dev_err(dev, "failed to acquire reset gpio: %d\n", err);
		जाओ out_variant_clear;
	पूर्ण

	ufs_qcom_get_controller_revision(hba, &host->hw_ver.major,
		&host->hw_ver.minor, &host->hw_ver.step);

	/*
	 * क्रम newer controllers, device reference घड़ी control bit has
	 * moved inside UFS controller रेजिस्टर address space itself.
	 */
	अगर (host->hw_ver.major >= 0x02) अणु
		host->dev_ref_clk_ctrl_mmio = hba->mmio_base + REG_UFS_CFG1;
		host->dev_ref_clk_en_mask = BIT(26);
	पूर्ण अन्यथा अणु
		/* "dev_ref_clk_ctrl_mem" is optional resource */
		res = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM,
						   "dev_ref_clk_ctrl_mem");
		अगर (res) अणु
			host->dev_ref_clk_ctrl_mmio =
					devm_ioremap_resource(dev, res);
			अगर (IS_ERR(host->dev_ref_clk_ctrl_mmio))
				host->dev_ref_clk_ctrl_mmio = शून्य;
			host->dev_ref_clk_en_mask = BIT(5);
		पूर्ण
	पूर्ण

	list_क्रम_each_entry(clki, &hba->clk_list_head, list) अणु
		अगर (!म_भेद(clki->name, "core_clk_unipro"))
			clki->keep_link_active = true;
	पूर्ण

	err = ufs_qcom_init_lane_clks(host);
	अगर (err)
		जाओ out_variant_clear;

	ufs_qcom_set_caps(hba);
	ufs_qcom_advertise_quirks(hba);

	err = ufs_qcom_ice_init(host);
	अगर (err)
		जाओ out_variant_clear;

	ufs_qcom_setup_घड़ीs(hba, true, POST_CHANGE);

	अगर (hba->dev->id < MAX_UFS_QCOM_HOSTS)
		ufs_qcom_hosts[hba->dev->id] = host;

	host->dbg_prपूर्णांक_en |= UFS_QCOM_DEFAULT_DBG_PRINT_EN;
	ufs_qcom_get_शेष_testbus_cfg(host);
	err = ufs_qcom_testbus_config(host);
	अगर (err) अणु
		dev_warn(dev, "%s: failed to configure the testbus %d\n",
				__func__, err);
		err = 0;
	पूर्ण

	जाओ out;

out_variant_clear:
	ufshcd_set_variant(hba, शून्य);
out:
	वापस err;
पूर्ण

अटल व्योम ufs_qcom_निकास(काष्ठा ufs_hba *hba)
अणु
	काष्ठा ufs_qcom_host *host = ufshcd_get_variant(hba);

	ufs_qcom_disable_lane_clks(host);
	phy_घातer_off(host->generic_phy);
	phy_निकास(host->generic_phy);
पूर्ण

अटल पूर्णांक ufs_qcom_set_dme_vs_core_clk_ctrl_clear_भाग(काष्ठा ufs_hba *hba,
						       u32 clk_cycles)
अणु
	पूर्णांक err;
	u32 core_clk_ctrl_reg;

	अगर (clk_cycles > DME_VS_CORE_CLK_CTRL_MAX_CORE_CLK_1US_CYCLES_MASK)
		वापस -EINVAL;

	err = ufshcd_dme_get(hba,
			    UIC_ARG_MIB(DME_VS_CORE_CLK_CTRL),
			    &core_clk_ctrl_reg);
	अगर (err)
		जाओ out;

	core_clk_ctrl_reg &= ~DME_VS_CORE_CLK_CTRL_MAX_CORE_CLK_1US_CYCLES_MASK;
	core_clk_ctrl_reg |= clk_cycles;

	/* Clear CORE_CLK_DIV_EN */
	core_clk_ctrl_reg &= ~DME_VS_CORE_CLK_CTRL_CORE_CLK_DIV_EN_BIT;

	err = ufshcd_dme_set(hba,
			    UIC_ARG_MIB(DME_VS_CORE_CLK_CTRL),
			    core_clk_ctrl_reg);
out:
	वापस err;
पूर्ण

अटल पूर्णांक ufs_qcom_clk_scale_up_pre_change(काष्ठा ufs_hba *hba)
अणु
	/* nothing to करो as of now */
	वापस 0;
पूर्ण

अटल पूर्णांक ufs_qcom_clk_scale_up_post_change(काष्ठा ufs_hba *hba)
अणु
	काष्ठा ufs_qcom_host *host = ufshcd_get_variant(hba);

	अगर (!ufs_qcom_cap_qunipro(host))
		वापस 0;

	/* set unipro core घड़ी cycles to 150 and clear घड़ी भागider */
	वापस ufs_qcom_set_dme_vs_core_clk_ctrl_clear_भाग(hba, 150);
पूर्ण

अटल पूर्णांक ufs_qcom_clk_scale_करोwn_pre_change(काष्ठा ufs_hba *hba)
अणु
	काष्ठा ufs_qcom_host *host = ufshcd_get_variant(hba);
	पूर्णांक err;
	u32 core_clk_ctrl_reg;

	अगर (!ufs_qcom_cap_qunipro(host))
		वापस 0;

	err = ufshcd_dme_get(hba,
			    UIC_ARG_MIB(DME_VS_CORE_CLK_CTRL),
			    &core_clk_ctrl_reg);

	/* make sure CORE_CLK_DIV_EN is cleared */
	अगर (!err &&
	    (core_clk_ctrl_reg & DME_VS_CORE_CLK_CTRL_CORE_CLK_DIV_EN_BIT)) अणु
		core_clk_ctrl_reg &= ~DME_VS_CORE_CLK_CTRL_CORE_CLK_DIV_EN_BIT;
		err = ufshcd_dme_set(hba,
				    UIC_ARG_MIB(DME_VS_CORE_CLK_CTRL),
				    core_clk_ctrl_reg);
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक ufs_qcom_clk_scale_करोwn_post_change(काष्ठा ufs_hba *hba)
अणु
	काष्ठा ufs_qcom_host *host = ufshcd_get_variant(hba);

	अगर (!ufs_qcom_cap_qunipro(host))
		वापस 0;

	/* set unipro core घड़ी cycles to 75 and clear घड़ी भागider */
	वापस ufs_qcom_set_dme_vs_core_clk_ctrl_clear_भाग(hba, 75);
पूर्ण

अटल पूर्णांक ufs_qcom_clk_scale_notअगरy(काष्ठा ufs_hba *hba,
		bool scale_up, क्रमागत ufs_notअगरy_change_status status)
अणु
	काष्ठा ufs_qcom_host *host = ufshcd_get_variant(hba);
	काष्ठा ufs_pa_layer_attr *dev_req_params = &host->dev_req_params;
	पूर्णांक err = 0;

	अगर (status == PRE_CHANGE) अणु
		अगर (scale_up)
			err = ufs_qcom_clk_scale_up_pre_change(hba);
		अन्यथा
			err = ufs_qcom_clk_scale_करोwn_pre_change(hba);
	पूर्ण अन्यथा अणु
		अगर (scale_up)
			err = ufs_qcom_clk_scale_up_post_change(hba);
		अन्यथा
			err = ufs_qcom_clk_scale_करोwn_post_change(hba);

		अगर (err || !dev_req_params)
			जाओ out;

		ufs_qcom_cfg_समयrs(hba,
				    dev_req_params->gear_rx,
				    dev_req_params->pwr_rx,
				    dev_req_params->hs_rate,
				    false);
	पूर्ण

out:
	वापस err;
पूर्ण

अटल व्योम ufs_qcom_prपूर्णांक_hw_debug_reg_all(काष्ठा ufs_hba *hba,
		व्योम *priv, व्योम (*prपूर्णांक_fn)(काष्ठा ufs_hba *hba,
		पूर्णांक offset, पूर्णांक num_regs, स्थिर अक्षर *str, व्योम *priv))
अणु
	u32 reg;
	काष्ठा ufs_qcom_host *host;

	अगर (unlikely(!hba)) अणु
		pr_err("%s: hba is NULL\n", __func__);
		वापस;
	पूर्ण
	अगर (unlikely(!prपूर्णांक_fn)) अणु
		dev_err(hba->dev, "%s: print_fn is NULL\n", __func__);
		वापस;
	पूर्ण

	host = ufshcd_get_variant(hba);
	अगर (!(host->dbg_prपूर्णांक_en & UFS_QCOM_DBG_PRINT_REGS_EN))
		वापस;

	reg = ufs_qcom_get_debug_reg_offset(host, UFS_UFS_DBG_RD_REG_OCSC);
	prपूर्णांक_fn(hba, reg, 44, "UFS_UFS_DBG_RD_REG_OCSC ", priv);

	reg = ufshcd_पढ़ोl(hba, REG_UFS_CFG1);
	reg |= UTP_DBG_RAMS_EN;
	ufshcd_ग_लिखोl(hba, reg, REG_UFS_CFG1);

	reg = ufs_qcom_get_debug_reg_offset(host, UFS_UFS_DBG_RD_EDTL_RAM);
	prपूर्णांक_fn(hba, reg, 32, "UFS_UFS_DBG_RD_EDTL_RAM ", priv);

	reg = ufs_qcom_get_debug_reg_offset(host, UFS_UFS_DBG_RD_DESC_RAM);
	prपूर्णांक_fn(hba, reg, 128, "UFS_UFS_DBG_RD_DESC_RAM ", priv);

	reg = ufs_qcom_get_debug_reg_offset(host, UFS_UFS_DBG_RD_PRDT_RAM);
	prपूर्णांक_fn(hba, reg, 64, "UFS_UFS_DBG_RD_PRDT_RAM ", priv);

	/* clear bit 17 - UTP_DBG_RAMS_EN */
	ufshcd_rmwl(hba, UTP_DBG_RAMS_EN, 0, REG_UFS_CFG1);

	reg = ufs_qcom_get_debug_reg_offset(host, UFS_DBG_RD_REG_UAWM);
	prपूर्णांक_fn(hba, reg, 4, "UFS_DBG_RD_REG_UAWM ", priv);

	reg = ufs_qcom_get_debug_reg_offset(host, UFS_DBG_RD_REG_UARM);
	prपूर्णांक_fn(hba, reg, 4, "UFS_DBG_RD_REG_UARM ", priv);

	reg = ufs_qcom_get_debug_reg_offset(host, UFS_DBG_RD_REG_TXUC);
	prपूर्णांक_fn(hba, reg, 48, "UFS_DBG_RD_REG_TXUC ", priv);

	reg = ufs_qcom_get_debug_reg_offset(host, UFS_DBG_RD_REG_RXUC);
	prपूर्णांक_fn(hba, reg, 27, "UFS_DBG_RD_REG_RXUC ", priv);

	reg = ufs_qcom_get_debug_reg_offset(host, UFS_DBG_RD_REG_DFC);
	prपूर्णांक_fn(hba, reg, 19, "UFS_DBG_RD_REG_DFC ", priv);

	reg = ufs_qcom_get_debug_reg_offset(host, UFS_DBG_RD_REG_TRLUT);
	prपूर्णांक_fn(hba, reg, 34, "UFS_DBG_RD_REG_TRLUT ", priv);

	reg = ufs_qcom_get_debug_reg_offset(host, UFS_DBG_RD_REG_TMRLUT);
	prपूर्णांक_fn(hba, reg, 9, "UFS_DBG_RD_REG_TMRLUT ", priv);
पूर्ण

अटल व्योम ufs_qcom_enable_test_bus(काष्ठा ufs_qcom_host *host)
अणु
	अगर (host->dbg_prपूर्णांक_en & UFS_QCOM_DBG_PRINT_TEST_BUS_EN) अणु
		ufshcd_rmwl(host->hba, UFS_REG_TEST_BUS_EN,
				UFS_REG_TEST_BUS_EN, REG_UFS_CFG1);
		ufshcd_rmwl(host->hba, TEST_BUS_EN, TEST_BUS_EN, REG_UFS_CFG1);
	पूर्ण अन्यथा अणु
		ufshcd_rmwl(host->hba, UFS_REG_TEST_BUS_EN, 0, REG_UFS_CFG1);
		ufshcd_rmwl(host->hba, TEST_BUS_EN, 0, REG_UFS_CFG1);
	पूर्ण
पूर्ण

अटल व्योम ufs_qcom_get_शेष_testbus_cfg(काष्ठा ufs_qcom_host *host)
अणु
	/* provide a legal शेष configuration */
	host->testbus.select_major = TSTBUS_UNIPRO;
	host->testbus.select_minor = 37;
पूर्ण

अटल bool ufs_qcom_testbus_cfg_is_ok(काष्ठा ufs_qcom_host *host)
अणु
	अगर (host->testbus.select_major >= TSTBUS_MAX) अणु
		dev_err(host->hba->dev,
			"%s: UFS_CFG1[TEST_BUS_SEL} may not equal 0x%05X\n",
			__func__, host->testbus.select_major);
		वापस false;
	पूर्ण

	वापस true;
पूर्ण

पूर्णांक ufs_qcom_testbus_config(काष्ठा ufs_qcom_host *host)
अणु
	पूर्णांक reg;
	पूर्णांक offset;
	u32 mask = TEST_BUS_SUB_SEL_MASK;

	अगर (!host)
		वापस -EINVAL;

	अगर (!ufs_qcom_testbus_cfg_is_ok(host))
		वापस -EPERM;

	चयन (host->testbus.select_major) अणु
	हाल TSTBUS_UAWM:
		reg = UFS_TEST_BUS_CTRL_0;
		offset = 24;
		अवरोध;
	हाल TSTBUS_UARM:
		reg = UFS_TEST_BUS_CTRL_0;
		offset = 16;
		अवरोध;
	हाल TSTBUS_TXUC:
		reg = UFS_TEST_BUS_CTRL_0;
		offset = 8;
		अवरोध;
	हाल TSTBUS_RXUC:
		reg = UFS_TEST_BUS_CTRL_0;
		offset = 0;
		अवरोध;
	हाल TSTBUS_DFC:
		reg = UFS_TEST_BUS_CTRL_1;
		offset = 24;
		अवरोध;
	हाल TSTBUS_TRLUT:
		reg = UFS_TEST_BUS_CTRL_1;
		offset = 16;
		अवरोध;
	हाल TSTBUS_TMRLUT:
		reg = UFS_TEST_BUS_CTRL_1;
		offset = 8;
		अवरोध;
	हाल TSTBUS_OCSC:
		reg = UFS_TEST_BUS_CTRL_1;
		offset = 0;
		अवरोध;
	हाल TSTBUS_WRAPPER:
		reg = UFS_TEST_BUS_CTRL_2;
		offset = 16;
		अवरोध;
	हाल TSTBUS_COMBINED:
		reg = UFS_TEST_BUS_CTRL_2;
		offset = 8;
		अवरोध;
	हाल TSTBUS_UTP_HCI:
		reg = UFS_TEST_BUS_CTRL_2;
		offset = 0;
		अवरोध;
	हाल TSTBUS_UNIPRO:
		reg = UFS_UNIPRO_CFG;
		offset = 20;
		mask = 0xFFF;
		अवरोध;
	/*
	 * No need क्रम a शेष हाल, since
	 * ufs_qcom_testbus_cfg_is_ok() checks that the configuration
	 * is legal
	 */
	पूर्ण
	mask <<= offset;
	ufshcd_rmwl(host->hba, TEST_BUS_SEL,
		    (u32)host->testbus.select_major << 19,
		    REG_UFS_CFG1);
	ufshcd_rmwl(host->hba, mask,
		    (u32)host->testbus.select_minor << offset,
		    reg);
	ufs_qcom_enable_test_bus(host);
	/*
	 * Make sure the test bus configuration is
	 * committed beक्रमe वापसing.
	 */
	mb();

	वापस 0;
पूर्ण

अटल व्योम ufs_qcom_dump_dbg_regs(काष्ठा ufs_hba *hba)
अणु
	ufshcd_dump_regs(hba, REG_UFS_SYS1CLK_1US, 16 * 4,
			 "HCI Vendor Specific Registers ");

	ufs_qcom_prपूर्णांक_hw_debug_reg_all(hba, शून्य, ufs_qcom_dump_regs_wrapper);
पूर्ण

/**
 * ufs_qcom_device_reset() - toggle the (optional) device reset line
 * @hba: per-adapter instance
 *
 * Toggles the (optional) reset line to reset the attached device.
 */
अटल पूर्णांक ufs_qcom_device_reset(काष्ठा ufs_hba *hba)
अणु
	काष्ठा ufs_qcom_host *host = ufshcd_get_variant(hba);

	/* reset gpio is optional */
	अगर (!host->device_reset)
		वापस -EOPNOTSUPP;

	/*
	 * The UFS device shall detect reset pulses of 1us, sleep क्रम 10us to
	 * be on the safe side.
	 */
	ufs_qcom_device_reset_ctrl(hba, true);
	usleep_range(10, 15);

	ufs_qcom_device_reset_ctrl(hba, false);
	usleep_range(10, 15);

	वापस 0;
पूर्ण

#अगर IS_ENABLED(CONFIG_DEVFREQ_GOV_SIMPLE_ONDEMAND)
अटल व्योम ufs_qcom_config_scaling_param(काष्ठा ufs_hba *hba,
					  काष्ठा devfreq_dev_profile *p,
					  व्योम *data)
अणु
	अटल काष्ठा devfreq_simple_ondemand_data *d;

	अगर (!data)
		वापस;

	d = (काष्ठा devfreq_simple_ondemand_data *)data;
	p->polling_ms = 60;
	d->upthreshold = 70;
	d->करोwndअगरferential = 5;
पूर्ण
#अन्यथा
अटल व्योम ufs_qcom_config_scaling_param(काष्ठा ufs_hba *hba,
					  काष्ठा devfreq_dev_profile *p,
					  व्योम *data)
अणु
पूर्ण
#पूर्ण_अगर

/*
 * काष्ठा ufs_hba_qcom_vops - UFS QCOM specअगरic variant operations
 *
 * The variant operations configure the necessary controller and PHY
 * handshake during initialization.
 */
अटल स्थिर काष्ठा ufs_hba_variant_ops ufs_hba_qcom_vops = अणु
	.name                   = "qcom",
	.init                   = ufs_qcom_init,
	.निकास                   = ufs_qcom_निकास,
	.get_ufs_hci_version	= ufs_qcom_get_ufs_hci_version,
	.clk_scale_notअगरy	= ufs_qcom_clk_scale_notअगरy,
	.setup_घड़ीs           = ufs_qcom_setup_घड़ीs,
	.hce_enable_notअगरy      = ufs_qcom_hce_enable_notअगरy,
	.link_startup_notअगरy    = ufs_qcom_link_startup_notअगरy,
	.pwr_change_notअगरy	= ufs_qcom_pwr_change_notअगरy,
	.apply_dev_quirks	= ufs_qcom_apply_dev_quirks,
	.suspend		= ufs_qcom_suspend,
	.resume			= ufs_qcom_resume,
	.dbg_रेजिस्टर_dump	= ufs_qcom_dump_dbg_regs,
	.device_reset		= ufs_qcom_device_reset,
	.config_scaling_param = ufs_qcom_config_scaling_param,
	.program_key		= ufs_qcom_ice_program_key,
पूर्ण;

/**
 * ufs_qcom_probe - probe routine of the driver
 * @pdev: poपूर्णांकer to Platक्रमm device handle
 *
 * Return zero क्रम success and non-zero क्रम failure
 */
अटल पूर्णांक ufs_qcom_probe(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक err;
	काष्ठा device *dev = &pdev->dev;

	/* Perक्रमm generic probe */
	err = ufshcd_pltfrm_init(pdev, &ufs_hba_qcom_vops);
	अगर (err)
		dev_err(dev, "ufshcd_pltfrm_init() failed %d\n", err);

	वापस err;
पूर्ण

/**
 * ufs_qcom_हटाओ - set driver_data of the device to शून्य
 * @pdev: poपूर्णांकer to platक्रमm device handle
 *
 * Always वापसs 0
 */
अटल पूर्णांक ufs_qcom_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा ufs_hba *hba =  platक्रमm_get_drvdata(pdev);

	pm_runसमय_get_sync(&(pdev)->dev);
	ufshcd_हटाओ(hba);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id ufs_qcom_of_match[] = अणु
	अणु .compatible = "qcom,ufshc"पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, ufs_qcom_of_match);

#अगर_घोषित CONFIG_ACPI
अटल स्थिर काष्ठा acpi_device_id ufs_qcom_acpi_match[] = अणु
	अणु "QCOM24A5" पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(acpi, ufs_qcom_acpi_match);
#पूर्ण_अगर

अटल स्थिर काष्ठा dev_pm_ops ufs_qcom_pm_ops = अणु
	.suspend	= ufshcd_pltfrm_suspend,
	.resume		= ufshcd_pltfrm_resume,
	.runसमय_suspend = ufshcd_pltfrm_runसमय_suspend,
	.runसमय_resume  = ufshcd_pltfrm_runसमय_resume,
	.runसमय_idle    = ufshcd_pltfrm_runसमय_idle,
पूर्ण;

अटल काष्ठा platक्रमm_driver ufs_qcom_pltक्रमm = अणु
	.probe	= ufs_qcom_probe,
	.हटाओ	= ufs_qcom_हटाओ,
	.shutकरोwn = ufshcd_pltfrm_shutकरोwn,
	.driver	= अणु
		.name	= "ufshcd-qcom",
		.pm	= &ufs_qcom_pm_ops,
		.of_match_table = of_match_ptr(ufs_qcom_of_match),
		.acpi_match_table = ACPI_PTR(ufs_qcom_acpi_match),
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(ufs_qcom_pltक्रमm);

MODULE_LICENSE("GPL v2");
