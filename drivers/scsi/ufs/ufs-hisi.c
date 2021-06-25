<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * HiSilicon Hixxxx UFS Driver
 *
 * Copyright (c) 2016-2017 Linaro Ltd.
 * Copyright (c) 2016-2017 HiSilicon Technologies Co., Ltd.
 */

#समावेश <linux/समय.स>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/reset.h>

#समावेश "ufshcd.h"
#समावेश "ufshcd-pltfrm.h"
#समावेश "unipro.h"
#समावेश "ufs-hisi.h"
#समावेश "ufshci.h"
#समावेश "ufs_quirks.h"

अटल पूर्णांक ufs_hisi_check_hibern8(काष्ठा ufs_hba *hba)
अणु
	पूर्णांक err = 0;
	u32 tx_fsm_val_0 = 0;
	u32 tx_fsm_val_1 = 0;
	अचिन्हित दीर्घ समयout = jअगरfies + msecs_to_jअगरfies(HBRN8_POLL_TOUT_MS);

	करो अणु
		err = ufshcd_dme_get(hba, UIC_ARG_MIB_SEL(MPHY_TX_FSM_STATE, 0),
				      &tx_fsm_val_0);
		err |= ufshcd_dme_get(hba,
		    UIC_ARG_MIB_SEL(MPHY_TX_FSM_STATE, 1), &tx_fsm_val_1);
		अगर (err || (tx_fsm_val_0 == TX_FSM_HIBERN8 &&
			tx_fsm_val_1 == TX_FSM_HIBERN8))
			अवरोध;

		/* sleep क्रम max. 200us */
		usleep_range(100, 200);
	पूर्ण जबतक (समय_beक्रमe(jअगरfies, समयout));

	/*
	 * we might have scheduled out क्रम दीर्घ during polling so
	 * check the state again.
	 */
	अगर (समय_after(jअगरfies, समयout)) अणु
		err = ufshcd_dme_get(hba, UIC_ARG_MIB_SEL(MPHY_TX_FSM_STATE, 0),
				     &tx_fsm_val_0);
		err |= ufshcd_dme_get(hba,
		 UIC_ARG_MIB_SEL(MPHY_TX_FSM_STATE, 1), &tx_fsm_val_1);
	पूर्ण

	अगर (err) अणु
		dev_err(hba->dev, "%s: unable to get TX_FSM_STATE, err %d\n",
			__func__, err);
	पूर्ण अन्यथा अगर (tx_fsm_val_0 != TX_FSM_HIBERN8 ||
			 tx_fsm_val_1 != TX_FSM_HIBERN8) अणु
		err = -1;
		dev_err(hba->dev, "%s: invalid TX_FSM_STATE, lane0 = %d, lane1 = %d\n",
			__func__, tx_fsm_val_0, tx_fsm_val_1);
	पूर्ण

	वापस err;
पूर्ण

अटल व्योम ufs_hisi_clk_init(काष्ठा ufs_hba *hba)
अणु
	काष्ठा ufs_hisi_host *host = ufshcd_get_variant(hba);

	ufs_sys_ctrl_clr_bits(host, BIT_SYSCTRL_REF_CLOCK_EN, PHY_CLK_CTRL);
	अगर (ufs_sys_ctrl_पढ़ोl(host, PHY_CLK_CTRL) & BIT_SYSCTRL_REF_CLOCK_EN)
		mdelay(1);
	/* use abb clk */
	ufs_sys_ctrl_clr_bits(host, BIT_UFS_REFCLK_SRC_SEl, UFS_SYSCTRL);
	ufs_sys_ctrl_clr_bits(host, BIT_UFS_REFCLK_ISO_EN, PHY_ISO_EN);
	/* खोलो mphy ref clk */
	ufs_sys_ctrl_set_bits(host, BIT_SYSCTRL_REF_CLOCK_EN, PHY_CLK_CTRL);
पूर्ण

अटल व्योम ufs_hisi_soc_init(काष्ठा ufs_hba *hba)
अणु
	काष्ठा ufs_hisi_host *host = ufshcd_get_variant(hba);
	u32 reg;

	अगर (!IS_ERR(host->rst))
		reset_control_निश्चित(host->rst);

	/* HC_PSW घातerup */
	ufs_sys_ctrl_set_bits(host, BIT_UFS_PSW_MTCMOS_EN, PSW_POWER_CTRL);
	udelay(10);
	/* notअगरy PWR पढ़ोy */
	ufs_sys_ctrl_set_bits(host, BIT_SYSCTRL_PWR_READY, HC_LP_CTRL);
	ufs_sys_ctrl_ग_लिखोl(host, MASK_UFS_DEVICE_RESET | 0,
		UFS_DEVICE_RESET_CTRL);

	reg = ufs_sys_ctrl_पढ़ोl(host, PHY_CLK_CTRL);
	reg = (reg & ~MASK_SYSCTRL_CFG_CLOCK_FREQ) | UFS_FREQ_CFG_CLK;
	/* set cfg clk freq */
	ufs_sys_ctrl_ग_लिखोl(host, reg, PHY_CLK_CTRL);
	/* set ref clk freq */
	ufs_sys_ctrl_clr_bits(host, MASK_SYSCTRL_REF_CLOCK_SEL, PHY_CLK_CTRL);
	/* bypass ufs clk gate */
	ufs_sys_ctrl_set_bits(host, MASK_UFS_CLK_GATE_BYPASS,
						 CLOCK_GATE_BYPASS);
	ufs_sys_ctrl_set_bits(host, MASK_UFS_SYSCRTL_BYPASS, UFS_SYSCTRL);

	/* खोलो psw clk */
	ufs_sys_ctrl_set_bits(host, BIT_SYSCTRL_PSW_CLK_EN, PSW_CLK_CTRL);
	/* disable ufshc iso */
	ufs_sys_ctrl_clr_bits(host, BIT_UFS_PSW_ISO_CTRL, PSW_POWER_CTRL);
	/* disable phy iso */
	ufs_sys_ctrl_clr_bits(host, BIT_UFS_PHY_ISO_CTRL, PHY_ISO_EN);
	/* notice iso disable */
	ufs_sys_ctrl_clr_bits(host, BIT_SYSCTRL_LP_ISOL_EN, HC_LP_CTRL);

	/* disable lp_reset_n */
	ufs_sys_ctrl_set_bits(host, BIT_SYSCTRL_LP_RESET_N, RESET_CTRL_EN);
	mdelay(1);

	ufs_sys_ctrl_ग_लिखोl(host, MASK_UFS_DEVICE_RESET | BIT_UFS_DEVICE_RESET,
		UFS_DEVICE_RESET_CTRL);

	msleep(20);

	/*
	 * enable the fix of linereset recovery,
	 * and enable rx_reset/tx_rest beat
	 * enable ref_clk_en override(bit5) &
	 * override value = 1(bit4), with mask
	 */
	ufs_sys_ctrl_ग_लिखोl(host, 0x03300330, UFS_DEVICE_RESET_CTRL);

	अगर (!IS_ERR(host->rst))
		reset_control_deनिश्चित(host->rst);
पूर्ण

अटल पूर्णांक ufs_hisi_link_startup_pre_change(काष्ठा ufs_hba *hba)
अणु
	काष्ठा ufs_hisi_host *host = ufshcd_get_variant(hba);
	पूर्णांक err;
	uपूर्णांक32_t value;
	uपूर्णांक32_t reg;

	/* Unipro VS_mphy_disable */
	ufshcd_dme_set(hba, UIC_ARG_MIB_SEL(0xD0C1, 0x0), 0x1);
	/* PA_HSSeries */
	ufshcd_dme_set(hba, UIC_ARG_MIB_SEL(0x156A, 0x0), 0x2);
	/* MPHY CBRATESEL */
	ufshcd_dme_set(hba, UIC_ARG_MIB_SEL(0x8114, 0x0), 0x1);
	/* MPHY CBOVRCTRL2 */
	ufshcd_dme_set(hba, UIC_ARG_MIB_SEL(0x8121, 0x0), 0x2D);
	/* MPHY CBOVRCTRL3 */
	ufshcd_dme_set(hba, UIC_ARG_MIB_SEL(0x8122, 0x0), 0x1);

	अगर (host->caps & UFS_HISI_CAP_PHY10nm) अणु
		/* MPHY CBOVRCTRL4 */
		ufshcd_dme_set(hba, UIC_ARG_MIB_SEL(0x8127, 0x0), 0x98);
		/* MPHY CBOVRCTRL5 */
		ufshcd_dme_set(hba, UIC_ARG_MIB_SEL(0x8128, 0x0), 0x1);
	पूर्ण

	/* Unipro VS_MphyCfgUpdt */
	ufshcd_dme_set(hba, UIC_ARG_MIB_SEL(0xD085, 0x0), 0x1);
	/* MPHY RXOVRCTRL4 rx0 */
	ufshcd_dme_set(hba, UIC_ARG_MIB_SEL(0x800D, 0x4), 0x58);
	/* MPHY RXOVRCTRL4 rx1 */
	ufshcd_dme_set(hba, UIC_ARG_MIB_SEL(0x800D, 0x5), 0x58);
	/* MPHY RXOVRCTRL5 rx0 */
	ufshcd_dme_set(hba, UIC_ARG_MIB_SEL(0x800E, 0x4), 0xB);
	/* MPHY RXOVRCTRL5 rx1 */
	ufshcd_dme_set(hba, UIC_ARG_MIB_SEL(0x800E, 0x5), 0xB);
	/* MPHY RXSQCONTROL rx0 */
	ufshcd_dme_set(hba, UIC_ARG_MIB_SEL(0x8009, 0x4), 0x1);
	/* MPHY RXSQCONTROL rx1 */
	ufshcd_dme_set(hba, UIC_ARG_MIB_SEL(0x8009, 0x5), 0x1);
	/* Unipro VS_MphyCfgUpdt */
	ufshcd_dme_set(hba, UIC_ARG_MIB_SEL(0xD085, 0x0), 0x1);

	ufshcd_dme_set(hba, UIC_ARG_MIB_SEL(0x8113, 0x0), 0x1);
	ufshcd_dme_set(hba, UIC_ARG_MIB_SEL(0xD085, 0x0), 0x1);

	अगर (host->caps & UFS_HISI_CAP_PHY10nm) अणु
		/* RX_Hibern8Time_Capability*/
		ufshcd_dme_set(hba, UIC_ARG_MIB_SEL(0x0092, 0x4), 0xA);
		/* RX_Hibern8Time_Capability*/
		ufshcd_dme_set(hba, UIC_ARG_MIB_SEL(0x0092, 0x5), 0xA);
		/* RX_Min_ActivateTime */
		ufshcd_dme_set(hba, UIC_ARG_MIB_SEL(0x008f, 0x4), 0xA);
		/* RX_Min_ActivateTime*/
		ufshcd_dme_set(hba, UIC_ARG_MIB_SEL(0x008f, 0x5), 0xA);
	पूर्ण अन्यथा अणु
		/* Tactive RX */
		ufshcd_dme_set(hba, UIC_ARG_MIB_SEL(0x008F, 0x4), 0x7);
		/* Tactive RX */
		ufshcd_dme_set(hba, UIC_ARG_MIB_SEL(0x008F, 0x5), 0x7);
	पूर्ण

	/* Gear3 Synclength */
	ufshcd_dme_set(hba, UIC_ARG_MIB_SEL(0x0095, 0x4), 0x4F);
	/* Gear3 Synclength */
	ufshcd_dme_set(hba, UIC_ARG_MIB_SEL(0x0095, 0x5), 0x4F);
	/* Gear2 Synclength */
	ufshcd_dme_set(hba, UIC_ARG_MIB_SEL(0x0094, 0x4), 0x4F);
	/* Gear2 Synclength */
	ufshcd_dme_set(hba, UIC_ARG_MIB_SEL(0x0094, 0x5), 0x4F);
	/* Gear1 Synclength */
	ufshcd_dme_set(hba, UIC_ARG_MIB_SEL(0x008B, 0x4), 0x4F);
	/* Gear1 Synclength */
	ufshcd_dme_set(hba, UIC_ARG_MIB_SEL(0x008B, 0x5), 0x4F);
	/* Thibernate Tx */
	ufshcd_dme_set(hba, UIC_ARG_MIB_SEL(0x000F, 0x0), 0x5);
	/* Thibernate Tx */
	ufshcd_dme_set(hba, UIC_ARG_MIB_SEL(0x000F, 0x1), 0x5);

	ufshcd_dme_set(hba, UIC_ARG_MIB_SEL(0xD085, 0x0), 0x1);
	/* Unipro VS_mphy_disable */
	ufshcd_dme_get(hba, UIC_ARG_MIB_SEL(0xD0C1, 0x0), &value);
	अगर (value != 0x1)
		dev_info(hba->dev,
		    "Warring!!! Unipro VS_mphy_disable is 0x%x\n", value);

	/* Unipro VS_mphy_disable */
	ufshcd_dme_set(hba, UIC_ARG_MIB_SEL(0xD0C1, 0x0), 0x0);
	err = ufs_hisi_check_hibern8(hba);
	अगर (err)
		dev_err(hba->dev, "ufs_hisi_check_hibern8 error\n");

	अगर (!(host->caps & UFS_HISI_CAP_PHY10nm))
		ufshcd_ग_लिखोl(hba, UFS_HCLKDIV_NORMAL_VALUE, UFS_REG_HCLKDIV);

	/* disable स्वतः H8 */
	reg = ufshcd_पढ़ोl(hba, REG_AUTO_HIBERNATE_IDLE_TIMER);
	reg = reg & (~UFS_AHIT_AH8ITV_MASK);
	ufshcd_ग_लिखोl(hba, reg, REG_AUTO_HIBERNATE_IDLE_TIMER);

	/* Unipro PA_Local_TX_LCC_Enable */
	ufshcd_disable_host_tx_lcc(hba);
	/* बंद Unipro VS_Mk2ExtnSupport */
	ufshcd_dme_set(hba, UIC_ARG_MIB_SEL(0xD0AB, 0x0), 0x0);
	ufshcd_dme_get(hba, UIC_ARG_MIB_SEL(0xD0AB, 0x0), &value);
	अगर (value != 0) अणु
		/* Ensure बंद success */
		dev_info(hba->dev, "WARN: close VS_Mk2ExtnSupport failed\n");
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक ufs_hisi_link_startup_post_change(काष्ठा ufs_hba *hba)
अणु
	काष्ठा ufs_hisi_host *host = ufshcd_get_variant(hba);

	/* Unipro DL_AFC0CreditThreshold */
	ufshcd_dme_set(hba, UIC_ARG_MIB(0x2044), 0x0);
	/* Unipro DL_TC0OutAckThreshold */
	ufshcd_dme_set(hba, UIC_ARG_MIB(0x2045), 0x0);
	/* Unipro DL_TC0TXFCThreshold */
	ufshcd_dme_set(hba, UIC_ARG_MIB(0x2040), 0x9);

	/* not bypass ufs clk gate */
	ufs_sys_ctrl_clr_bits(host, MASK_UFS_CLK_GATE_BYPASS,
						CLOCK_GATE_BYPASS);
	ufs_sys_ctrl_clr_bits(host, MASK_UFS_SYSCRTL_BYPASS,
						UFS_SYSCTRL);

	/* select received symbol cnt */
	ufshcd_dme_set(hba, UIC_ARG_MIB(0xd09a), 0x80000000);
	 /* reset counter0 and enable */
	ufshcd_dme_set(hba, UIC_ARG_MIB(0xd09c), 0x00000005);

	वापस 0;
पूर्ण

अटल पूर्णांक ufs_hisi_link_startup_notअगरy(काष्ठा ufs_hba *hba,
					  क्रमागत ufs_notअगरy_change_status status)
अणु
	पूर्णांक err = 0;

	चयन (status) अणु
	हाल PRE_CHANGE:
		err = ufs_hisi_link_startup_pre_change(hba);
		अवरोध;
	हाल POST_CHANGE:
		err = ufs_hisi_link_startup_post_change(hba);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस err;
पूर्ण

अटल व्योम ufs_hisi_set_dev_cap(काष्ठा ufs_dev_params *hisi_param)
अणु
	ufshcd_init_pwr_dev_param(hisi_param);
पूर्ण

अटल व्योम ufs_hisi_pwr_change_pre_change(काष्ठा ufs_hba *hba)
अणु
	काष्ठा ufs_hisi_host *host = ufshcd_get_variant(hba);

	अगर (host->caps & UFS_HISI_CAP_PHY10nm) अणु
		/*
		 * Boston platक्रमm need to set SaveConfigTime to 0x13,
		 * and change sync length to maximum value
		 */
		/* VS_DebugSaveConfigTime */
		ufshcd_dme_set(hba, UIC_ARG_MIB((u32)0xD0A0), 0x13);
		/* g1 sync length */
		ufshcd_dme_set(hba, UIC_ARG_MIB((u32)0x1552), 0x4f);
		/* g2 sync length */
		ufshcd_dme_set(hba, UIC_ARG_MIB((u32)0x1554), 0x4f);
		/* g3 sync length */
		ufshcd_dme_set(hba, UIC_ARG_MIB((u32)0x1556), 0x4f);
		/* PA_Hibern8Time */
		ufshcd_dme_set(hba, UIC_ARG_MIB((u32)0x15a7), 0xA);
		/* PA_Tactivate */
		ufshcd_dme_set(hba, UIC_ARG_MIB((u32)0x15a8), 0xA);
		ufshcd_dme_set(hba, UIC_ARG_MIB_SEL(0xd085, 0x0), 0x01);
	पूर्ण

	अगर (hba->dev_quirks & UFS_DEVICE_QUIRK_HOST_VS_DEBUGSAVECONFIGTIME) अणु
		pr_info("ufs flash device must set VS_DebugSaveConfigTime 0x10\n");
		/* VS_DebugSaveConfigTime */
		ufshcd_dme_set(hba, UIC_ARG_MIB(0xD0A0), 0x10);
		/* sync length */
		ufshcd_dme_set(hba, UIC_ARG_MIB(0x1556), 0x48);
	पूर्ण

	/* update */
	ufshcd_dme_set(hba, UIC_ARG_MIB(0x15A8), 0x1);
	/* PA_TxSkip */
	ufshcd_dme_set(hba, UIC_ARG_MIB(0x155c), 0x0);
	/*PA_PWRModeUserData0 = 8191, शेष is 0*/
	ufshcd_dme_set(hba, UIC_ARG_MIB(0x15b0), 8191);
	/*PA_PWRModeUserData1 = 65535, शेष is 0*/
	ufshcd_dme_set(hba, UIC_ARG_MIB(0x15b1), 65535);
	/*PA_PWRModeUserData2 = 32767, शेष is 0*/
	ufshcd_dme_set(hba, UIC_ARG_MIB(0x15b2), 32767);
	/*DME_FC0ProtectionTimeOutVal = 8191, शेष is 0*/
	ufshcd_dme_set(hba, UIC_ARG_MIB(0xd041), 8191);
	/*DME_TC0ReplayTimeOutVal = 65535, शेष is 0*/
	ufshcd_dme_set(hba, UIC_ARG_MIB(0xd042), 65535);
	/*DME_AFC0ReqTimeOutVal = 32767, शेष is 0*/
	ufshcd_dme_set(hba, UIC_ARG_MIB(0xd043), 32767);
	/*PA_PWRModeUserData3 = 8191, शेष is 0*/
	ufshcd_dme_set(hba, UIC_ARG_MIB(0x15b3), 8191);
	/*PA_PWRModeUserData4 = 65535, शेष is 0*/
	ufshcd_dme_set(hba, UIC_ARG_MIB(0x15b4), 65535);
	/*PA_PWRModeUserData5 = 32767, शेष is 0*/
	ufshcd_dme_set(hba, UIC_ARG_MIB(0x15b5), 32767);
	/*DME_FC1ProtectionTimeOutVal = 8191, शेष is 0*/
	ufshcd_dme_set(hba, UIC_ARG_MIB(0xd044), 8191);
	/*DME_TC1ReplayTimeOutVal = 65535, शेष is 0*/
	ufshcd_dme_set(hba, UIC_ARG_MIB(0xd045), 65535);
	/*DME_AFC1ReqTimeOutVal = 32767, शेष is 0*/
	ufshcd_dme_set(hba, UIC_ARG_MIB(0xd046), 32767);
पूर्ण

अटल पूर्णांक ufs_hisi_pwr_change_notअगरy(काष्ठा ufs_hba *hba,
				       क्रमागत ufs_notअगरy_change_status status,
				       काष्ठा ufs_pa_layer_attr *dev_max_params,
				       काष्ठा ufs_pa_layer_attr *dev_req_params)
अणु
	काष्ठा ufs_dev_params ufs_hisi_cap;
	पूर्णांक ret = 0;

	अगर (!dev_req_params) अणु
		dev_err(hba->dev,
			    "%s: incoming dev_req_params is NULL\n", __func__);
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	चयन (status) अणु
	हाल PRE_CHANGE:
		ufs_hisi_set_dev_cap(&ufs_hisi_cap);
		ret = ufshcd_get_pwr_dev_param(&ufs_hisi_cap,
					       dev_max_params, dev_req_params);
		अगर (ret) अणु
			dev_err(hba->dev,
			    "%s: failed to determine capabilities\n", __func__);
			जाओ out;
		पूर्ण

		ufs_hisi_pwr_change_pre_change(hba);
		अवरोध;
	हाल POST_CHANGE:
		अवरोध;
	शेष:
		ret = -EINVAL;
		अवरोध;
	पूर्ण
out:
	वापस ret;
पूर्ण

अटल पूर्णांक ufs_hisi_suspend(काष्ठा ufs_hba *hba, क्रमागत ufs_pm_op pm_op)
अणु
	काष्ठा ufs_hisi_host *host = ufshcd_get_variant(hba);

	अगर (ufshcd_is_runसमय_pm(pm_op))
		वापस 0;

	अगर (host->in_suspend) अणु
		WARN_ON(1);
		वापस 0;
	पूर्ण

	ufs_sys_ctrl_clr_bits(host, BIT_SYSCTRL_REF_CLOCK_EN, PHY_CLK_CTRL);
	udelay(10);
	/* set ref_dig_clk override of PHY PCS to 0 */
	ufs_sys_ctrl_ग_लिखोl(host, 0x00100000, UFS_DEVICE_RESET_CTRL);

	host->in_suspend = true;

	वापस 0;
पूर्ण

अटल पूर्णांक ufs_hisi_resume(काष्ठा ufs_hba *hba, क्रमागत ufs_pm_op pm_op)
अणु
	काष्ठा ufs_hisi_host *host = ufshcd_get_variant(hba);

	अगर (!host->in_suspend)
		वापस 0;

	/* set ref_dig_clk override of PHY PCS to 1 */
	ufs_sys_ctrl_ग_लिखोl(host, 0x00100010, UFS_DEVICE_RESET_CTRL);
	udelay(10);
	ufs_sys_ctrl_set_bits(host, BIT_SYSCTRL_REF_CLOCK_EN, PHY_CLK_CTRL);

	host->in_suspend = false;
	वापस 0;
पूर्ण

अटल पूर्णांक ufs_hisi_get_resource(काष्ठा ufs_hisi_host *host)
अणु
	काष्ठा device *dev = host->hba->dev;
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);

	/* get resource of ufs sys ctrl */
	host->ufs_sys_ctrl = devm_platक्रमm_ioremap_resource(pdev, 1);
	वापस PTR_ERR_OR_ZERO(host->ufs_sys_ctrl);
पूर्ण

अटल व्योम ufs_hisi_set_pm_lvl(काष्ठा ufs_hba *hba)
अणु
	hba->rpm_lvl = UFS_PM_LVL_1;
	hba->spm_lvl = UFS_PM_LVL_3;
पूर्ण

/**
 * ufs_hisi_init_common
 * @hba: host controller instance
 */
अटल पूर्णांक ufs_hisi_init_common(काष्ठा ufs_hba *hba)
अणु
	पूर्णांक err = 0;
	काष्ठा device *dev = hba->dev;
	काष्ठा ufs_hisi_host *host;

	host = devm_kzalloc(dev, माप(*host), GFP_KERNEL);
	अगर (!host)
		वापस -ENOMEM;

	host->hba = hba;
	ufshcd_set_variant(hba, host);

	host->rst = devm_reset_control_get(dev, "rst");
	अगर (IS_ERR(host->rst)) अणु
		dev_err(dev, "%s: failed to get reset control\n", __func__);
		err = PTR_ERR(host->rst);
		जाओ error;
	पूर्ण

	ufs_hisi_set_pm_lvl(hba);

	err = ufs_hisi_get_resource(host);
	अगर (err)
		जाओ error;

	वापस 0;

error:
	ufshcd_set_variant(hba, शून्य);
	वापस err;
पूर्ण

अटल पूर्णांक ufs_hi3660_init(काष्ठा ufs_hba *hba)
अणु
	पूर्णांक ret = 0;
	काष्ठा device *dev = hba->dev;

	ret = ufs_hisi_init_common(hba);
	अगर (ret) अणु
		dev_err(dev, "%s: ufs common init fail\n", __func__);
		वापस ret;
	पूर्ण

	ufs_hisi_clk_init(hba);

	ufs_hisi_soc_init(hba);

	वापस 0;
पूर्ण

अटल पूर्णांक ufs_hi3670_init(काष्ठा ufs_hba *hba)
अणु
	पूर्णांक ret = 0;
	काष्ठा device *dev = hba->dev;
	काष्ठा ufs_hisi_host *host;

	ret = ufs_hisi_init_common(hba);
	अगर (ret) अणु
		dev_err(dev, "%s: ufs common init fail\n", __func__);
		वापस ret;
	पूर्ण

	ufs_hisi_clk_init(hba);

	ufs_hisi_soc_init(hba);

	/* Add cap क्रम 10nm PHY variant on HI3670 SoC */
	host = ufshcd_get_variant(hba);
	host->caps |= UFS_HISI_CAP_PHY10nm;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा ufs_hba_variant_ops ufs_hba_hi3660_vops = अणु
	.name = "hi3660",
	.init = ufs_hi3660_init,
	.link_startup_notअगरy = ufs_hisi_link_startup_notअगरy,
	.pwr_change_notअगरy = ufs_hisi_pwr_change_notअगरy,
	.suspend = ufs_hisi_suspend,
	.resume = ufs_hisi_resume,
पूर्ण;

अटल स्थिर काष्ठा ufs_hba_variant_ops ufs_hba_hi3670_vops = अणु
	.name = "hi3670",
	.init = ufs_hi3670_init,
	.link_startup_notअगरy = ufs_hisi_link_startup_notअगरy,
	.pwr_change_notअगरy = ufs_hisi_pwr_change_notअगरy,
	.suspend = ufs_hisi_suspend,
	.resume = ufs_hisi_resume,
पूर्ण;

अटल स्थिर काष्ठा of_device_id ufs_hisi_of_match[] = अणु
	अणु .compatible = "hisilicon,hi3660-ufs", .data = &ufs_hba_hi3660_vops पूर्ण,
	अणु .compatible = "hisilicon,hi3670-ufs", .data = &ufs_hba_hi3670_vops पूर्ण,
	अणुपूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(of, ufs_hisi_of_match);

अटल पूर्णांक ufs_hisi_probe(काष्ठा platक्रमm_device *pdev)
अणु
	स्थिर काष्ठा of_device_id *of_id;

	of_id = of_match_node(ufs_hisi_of_match, pdev->dev.of_node);

	वापस ufshcd_pltfrm_init(pdev, of_id->data);
पूर्ण

अटल पूर्णांक ufs_hisi_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा ufs_hba *hba =  platक्रमm_get_drvdata(pdev);

	ufshcd_हटाओ(hba);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops ufs_hisi_pm_ops = अणु
	.suspend	= ufshcd_pltfrm_suspend,
	.resume		= ufshcd_pltfrm_resume,
	.runसमय_suspend = ufshcd_pltfrm_runसमय_suspend,
	.runसमय_resume  = ufshcd_pltfrm_runसमय_resume,
	.runसमय_idle    = ufshcd_pltfrm_runसमय_idle,
पूर्ण;

अटल काष्ठा platक्रमm_driver ufs_hisi_pltक्रमm = अणु
	.probe	= ufs_hisi_probe,
	.हटाओ	= ufs_hisi_हटाओ,
	.shutकरोwn = ufshcd_pltfrm_shutकरोwn,
	.driver	= अणु
		.name	= "ufshcd-hisi",
		.pm	= &ufs_hisi_pm_ops,
		.of_match_table = of_match_ptr(ufs_hisi_of_match),
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(ufs_hisi_pltक्रमm);

MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:ufshcd-hisi");
MODULE_DESCRIPTION("HiSilicon Hixxxx UFS Driver");
