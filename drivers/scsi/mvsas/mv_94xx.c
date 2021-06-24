<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Marvell 88SE94xx hardware specअगरic
 *
 * Copyright 2007 Red Hat, Inc.
 * Copyright 2008 Marvell. <kewei@marvell.com>
 * Copyright 2009-2011 Marvell. <yuxiangl@marvell.com>
*/

#समावेश "mv_sas.h"
#समावेश "mv_94xx.h"
#समावेश "mv_chips.h"

अटल व्योम mvs_94xx_detect_porttype(काष्ठा mvs_info *mvi, पूर्णांक i)
अणु
	u32 reg;
	काष्ठा mvs_phy *phy = &mvi->phy[i];
	u32 phy_status;

	mvs_ग_लिखो_port_vsr_addr(mvi, i, VSR_PHY_MODE3);
	reg = mvs_पढ़ो_port_vsr_data(mvi, i);
	phy_status = ((reg & 0x3f0000) >> 16) & 0xff;
	phy->phy_type &= ~(PORT_TYPE_SAS | PORT_TYPE_SATA);
	चयन (phy_status) अणु
	हाल 0x10:
		phy->phy_type |= PORT_TYPE_SAS;
		अवरोध;
	हाल 0x1d:
	शेष:
		phy->phy_type |= PORT_TYPE_SATA;
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम set_phy_tuning(काष्ठा mvs_info *mvi, पूर्णांक phy_id,
			   काष्ठा phy_tuning phy_tuning)
अणु
	u32 पंचांगp, setting_0 = 0, setting_1 = 0;
	u8 i;

	/* Remap inक्रमmation क्रम B0 chip:
	*
	* R0Ch -> R118h[15:0] (Adapted DFE F3 - F5 coefficient)
	* R0Dh -> R118h[31:16] (Generation 1 Setting 0)
	* R0Eh -> R11Ch[15:0]  (Generation 1 Setting 1)
	* R0Fh -> R11Ch[31:16] (Generation 2 Setting 0)
	* R10h -> R120h[15:0]  (Generation 2 Setting 1)
	* R11h -> R120h[31:16] (Generation 3 Setting 0)
	* R12h -> R124h[15:0]  (Generation 3 Setting 1)
	* R13h -> R124h[31:16] (Generation 4 Setting 0 (Reserved))
	*/

	/* A0 has a dअगरferent set of रेजिस्टरs */
	अगर (mvi->pdev->revision == VANIR_A0_REV)
		वापस;

	क्रम (i = 0; i < 3; i++) अणु
		/* loop 3 बार, set Gen 1, Gen 2, Gen 3 */
		चयन (i) अणु
		हाल 0:
			setting_0 = GENERATION_1_SETTING;
			setting_1 = GENERATION_1_2_SETTING;
			अवरोध;
		हाल 1:
			setting_0 = GENERATION_1_2_SETTING;
			setting_1 = GENERATION_2_3_SETTING;
			अवरोध;
		हाल 2:
			setting_0 = GENERATION_2_3_SETTING;
			setting_1 = GENERATION_3_4_SETTING;
			अवरोध;
		पूर्ण

		/* Set:
		*
		* Transmitter Emphasis Enable
		* Transmitter Emphasis Amplitude
		* Transmitter Amplitude
		*/
		mvs_ग_लिखो_port_vsr_addr(mvi, phy_id, setting_0);
		पंचांगp = mvs_पढ़ो_port_vsr_data(mvi, phy_id);
		पंचांगp &= ~(0xFBE << 16);
		पंचांगp |= (((phy_tuning.trans_emp_en << 11) |
			(phy_tuning.trans_emp_amp << 7) |
			(phy_tuning.trans_amp << 1)) << 16);
		mvs_ग_लिखो_port_vsr_data(mvi, phy_id, पंचांगp);

		/* Set Transmitter Amplitude Adjust */
		mvs_ग_लिखो_port_vsr_addr(mvi, phy_id, setting_1);
		पंचांगp = mvs_पढ़ो_port_vsr_data(mvi, phy_id);
		पंचांगp &= ~(0xC000);
		पंचांगp |= (phy_tuning.trans_amp_adj << 14);
		mvs_ग_लिखो_port_vsr_data(mvi, phy_id, पंचांगp);
	पूर्ण
पूर्ण

अटल व्योम set_phy_ffe_tuning(काष्ठा mvs_info *mvi, पूर्णांक phy_id,
			       काष्ठा ffe_control ffe)
अणु
	u32 पंचांगp;

	/* Don't run this अगर A0/B0 */
	अगर ((mvi->pdev->revision == VANIR_A0_REV)
		|| (mvi->pdev->revision == VANIR_B0_REV))
		वापस;

	/* FFE Resistor and Capacitor */
	/* R10Ch DFE Resolution Control/Squelch and FFE Setting
	 *
	 * FFE_FORCE            [7]
	 * FFE_RES_SEL          [6:4]
	 * FFE_CAP_SEL          [3:0]
	 */
	mvs_ग_लिखो_port_vsr_addr(mvi, phy_id, VSR_PHY_FFE_CONTROL);
	पंचांगp = mvs_पढ़ो_port_vsr_data(mvi, phy_id);
	पंचांगp &= ~0xFF;

	/* Read from HBA_Info_Page */
	पंचांगp |= ((0x1 << 7) |
		(ffe.ffe_rss_sel << 4) |
		(ffe.ffe_cap_sel << 0));

	mvs_ग_लिखो_port_vsr_data(mvi, phy_id, पंचांगp);

	/* R064h PHY Mode Register 1
	 *
	 * DFE_DIS		18
	 */
	mvs_ग_लिखो_port_vsr_addr(mvi, phy_id, VSR_REF_CLOCK_CRTL);
	पंचांगp = mvs_पढ़ो_port_vsr_data(mvi, phy_id);
	पंचांगp &= ~0x40001;
	/* Hard coding */
	/* No defines in HBA_Info_Page */
	पंचांगp |= (0 << 18);
	mvs_ग_लिखो_port_vsr_data(mvi, phy_id, पंचांगp);

	/* R110h DFE F0-F1 Coefficient Control/DFE Update Control
	 *
	 * DFE_UPDATE_EN        [11:6]
	 * DFE_FX_FORCE         [5:0]
	 */
	mvs_ग_लिखो_port_vsr_addr(mvi, phy_id, VSR_PHY_DFE_UPDATE_CRTL);
	पंचांगp = mvs_पढ़ो_port_vsr_data(mvi, phy_id);
	पंचांगp &= ~0xFFF;
	/* Hard coding */
	/* No defines in HBA_Info_Page */
	पंचांगp |= ((0x3F << 6) | (0x0 << 0));
	mvs_ग_लिखो_port_vsr_data(mvi, phy_id, पंचांगp);

	/* R1A0h Interface and Digital Reference Clock Control/Reserved_50h
	 *
	 * FFE_TRAIN_EN         3
	 */
	mvs_ग_लिखो_port_vsr_addr(mvi, phy_id, VSR_REF_CLOCK_CRTL);
	पंचांगp = mvs_पढ़ो_port_vsr_data(mvi, phy_id);
	पंचांगp &= ~0x8;
	/* Hard coding */
	/* No defines in HBA_Info_Page */
	पंचांगp |= (0 << 3);
	mvs_ग_लिखो_port_vsr_data(mvi, phy_id, पंचांगp);
पूर्ण

/*Notice: this function must be called when phy is disabled*/
अटल व्योम set_phy_rate(काष्ठा mvs_info *mvi, पूर्णांक phy_id, u8 rate)
अणु
	जोड़ reg_phy_cfg phy_cfg, phy_cfg_पंचांगp;
	mvs_ग_लिखो_port_vsr_addr(mvi, phy_id, VSR_PHY_MODE2);
	phy_cfg_पंचांगp.v = mvs_पढ़ो_port_vsr_data(mvi, phy_id);
	phy_cfg.v = 0;
	phy_cfg.u.disable_phy = phy_cfg_पंचांगp.u.disable_phy;
	phy_cfg.u.sas_support = 1;
	phy_cfg.u.sata_support = 1;
	phy_cfg.u.sata_host_mode = 1;

	चयन (rate) अणु
	हाल 0x0:
		/* support 1.5 Gbps */
		phy_cfg.u.speed_support = 1;
		phy_cfg.u.snw_3_support = 0;
		phy_cfg.u.tx_lnk_parity = 1;
		phy_cfg.u.tx_spt_phs_lnk_rate = 0x30;
		अवरोध;
	हाल 0x1:

		/* support 1.5, 3.0 Gbps */
		phy_cfg.u.speed_support = 3;
		phy_cfg.u.tx_spt_phs_lnk_rate = 0x3c;
		phy_cfg.u.tx_lgcl_lnk_rate = 0x08;
		अवरोध;
	हाल 0x2:
	शेष:
		/* support 1.5, 3.0, 6.0 Gbps */
		phy_cfg.u.speed_support = 7;
		phy_cfg.u.snw_3_support = 1;
		phy_cfg.u.tx_lnk_parity = 1;
		phy_cfg.u.tx_spt_phs_lnk_rate = 0x3f;
		phy_cfg.u.tx_lgcl_lnk_rate = 0x09;
		अवरोध;
	पूर्ण
	mvs_ग_लिखो_port_vsr_data(mvi, phy_id, phy_cfg.v);
पूर्ण

अटल व्योम mvs_94xx_config_reg_from_hba(काष्ठा mvs_info *mvi, पूर्णांक phy_id)
अणु
	u32 temp;
	temp = (u32)(*(u32 *)&mvi->hba_info_param.phy_tuning[phy_id]);
	अगर (temp == 0xFFFFFFFFL) अणु
		mvi->hba_info_param.phy_tuning[phy_id].trans_emp_amp = 0x6;
		mvi->hba_info_param.phy_tuning[phy_id].trans_amp = 0x1A;
		mvi->hba_info_param.phy_tuning[phy_id].trans_amp_adj = 0x3;
	पूर्ण

	temp = (u8)(*(u8 *)&mvi->hba_info_param.ffe_ctl[phy_id]);
	अगर (temp == 0xFFL) अणु
		चयन (mvi->pdev->revision) अणु
		हाल VANIR_A0_REV:
		हाल VANIR_B0_REV:
			mvi->hba_info_param.ffe_ctl[phy_id].ffe_rss_sel = 0x7;
			mvi->hba_info_param.ffe_ctl[phy_id].ffe_cap_sel = 0x7;
			अवरोध;
		हाल VANIR_C0_REV:
		हाल VANIR_C1_REV:
		हाल VANIR_C2_REV:
		शेष:
			mvi->hba_info_param.ffe_ctl[phy_id].ffe_rss_sel = 0x7;
			mvi->hba_info_param.ffe_ctl[phy_id].ffe_cap_sel = 0xC;
			अवरोध;
		पूर्ण
	पूर्ण

	temp = (u8)(*(u8 *)&mvi->hba_info_param.phy_rate[phy_id]);
	अगर (temp == 0xFFL)
		/*set शेष phy_rate = 6Gbps*/
		mvi->hba_info_param.phy_rate[phy_id] = 0x2;

	set_phy_tuning(mvi, phy_id,
		mvi->hba_info_param.phy_tuning[phy_id]);
	set_phy_ffe_tuning(mvi, phy_id,
		mvi->hba_info_param.ffe_ctl[phy_id]);
	set_phy_rate(mvi, phy_id,
		mvi->hba_info_param.phy_rate[phy_id]);
पूर्ण

अटल व्योम mvs_94xx_enable_xmt(काष्ठा mvs_info *mvi, पूर्णांक phy_id)
अणु
	व्योम __iomem *regs = mvi->regs;
	u32 पंचांगp;

	पंचांगp = mr32(MVS_PCS);
	पंचांगp |= 1 << (phy_id + PCS_EN_PORT_XMT_SHIFT2);
	mw32(MVS_PCS, पंचांगp);
पूर्ण

अटल व्योम mvs_94xx_phy_reset(काष्ठा mvs_info *mvi, u32 phy_id, पूर्णांक hard)
अणु
	u32 पंचांगp;
	u32 delay = 5000;
	अगर (hard == MVS_PHY_TUNE) अणु
		mvs_ग_लिखो_port_cfg_addr(mvi, phy_id, PHYR_SATA_CTL);
		पंचांगp = mvs_पढ़ो_port_cfg_data(mvi, phy_id);
		mvs_ग_लिखो_port_cfg_data(mvi, phy_id, पंचांगp|0x20000000);
		mvs_ग_लिखो_port_cfg_data(mvi, phy_id, पंचांगp|0x100000);
		वापस;
	पूर्ण
	पंचांगp = mvs_पढ़ो_port_irq_stat(mvi, phy_id);
	पंचांगp &= ~PHYEV_RDY_CH;
	mvs_ग_लिखो_port_irq_stat(mvi, phy_id, पंचांगp);
	अगर (hard) अणु
		पंचांगp = mvs_पढ़ो_phy_ctl(mvi, phy_id);
		पंचांगp |= PHY_RST_HARD;
		mvs_ग_लिखो_phy_ctl(mvi, phy_id, पंचांगp);
		करो अणु
			पंचांगp = mvs_पढ़ो_phy_ctl(mvi, phy_id);
			udelay(10);
			delay--;
		पूर्ण जबतक ((पंचांगp & PHY_RST_HARD) && delay);
		अगर (!delay)
			mv_dprपूर्णांकk("phy hard reset failed.\n");
	पूर्ण अन्यथा अणु
		पंचांगp = mvs_पढ़ो_phy_ctl(mvi, phy_id);
		पंचांगp |= PHY_RST;
		mvs_ग_लिखो_phy_ctl(mvi, phy_id, पंचांगp);
	पूर्ण
पूर्ण

अटल व्योम mvs_94xx_phy_disable(काष्ठा mvs_info *mvi, u32 phy_id)
अणु
	u32 पंचांगp;
	mvs_ग_लिखो_port_vsr_addr(mvi, phy_id, VSR_PHY_MODE2);
	पंचांगp = mvs_पढ़ो_port_vsr_data(mvi, phy_id);
	mvs_ग_लिखो_port_vsr_data(mvi, phy_id, पंचांगp | 0x00800000);
पूर्ण

अटल व्योम mvs_94xx_phy_enable(काष्ठा mvs_info *mvi, u32 phy_id)
अणु
	u32 पंचांगp;
	u8 revision = 0;

	revision = mvi->pdev->revision;
	अगर (revision == VANIR_A0_REV) अणु
		mvs_ग_लिखो_port_vsr_addr(mvi, phy_id, CMD_HOST_RD_DATA);
		mvs_ग_लिखो_port_vsr_data(mvi, phy_id, 0x8300ffc1);
	पूर्ण
	अगर (revision == VANIR_B0_REV) अणु
		mvs_ग_लिखो_port_vsr_addr(mvi, phy_id, CMD_APP_MEM_CTL);
		mvs_ग_लिखो_port_vsr_data(mvi, phy_id, 0x08001006);
		mvs_ग_लिखो_port_vsr_addr(mvi, phy_id, CMD_HOST_RD_DATA);
		mvs_ग_लिखो_port_vsr_data(mvi, phy_id, 0x0000705f);
	पूर्ण

	mvs_ग_लिखो_port_vsr_addr(mvi, phy_id, VSR_PHY_MODE2);
	पंचांगp = mvs_पढ़ो_port_vsr_data(mvi, phy_id);
	पंचांगp |= bit(0);
	mvs_ग_लिखो_port_vsr_data(mvi, phy_id, पंचांगp & 0xfd7fffff);
पूर्ण

अटल व्योम mvs_94xx_sgpio_init(काष्ठा mvs_info *mvi)
अणु
	व्योम __iomem *regs = mvi->regs_ex - 0x10200;
	u32 पंचांगp;

	पंचांगp = mr32(MVS_HST_CHIP_CONFIG);
	पंचांगp |= 0x100;
	mw32(MVS_HST_CHIP_CONFIG, पंचांगp);

	mw32(MVS_SGPIO_CTRL + MVS_SGPIO_HOST_OFFSET * mvi->id,
		MVS_SGPIO_CTRL_SDOUT_AUTO << MVS_SGPIO_CTRL_SDOUT_SHIFT);

	mw32(MVS_SGPIO_CFG1 + MVS_SGPIO_HOST_OFFSET * mvi->id,
		8 << MVS_SGPIO_CFG1_LOWA_SHIFT |
		8 << MVS_SGPIO_CFG1_HIA_SHIFT |
		4 << MVS_SGPIO_CFG1_LOWB_SHIFT |
		4 << MVS_SGPIO_CFG1_HIB_SHIFT |
		2 << MVS_SGPIO_CFG1_MAXACTON_SHIFT |
		1 << MVS_SGPIO_CFG1_FORCEACTOFF_SHIFT
	);

	mw32(MVS_SGPIO_CFG2 + MVS_SGPIO_HOST_OFFSET * mvi->id,
		(300000 / 100) << MVS_SGPIO_CFG2_CLK_SHIFT | /* 100kHz घड़ी */
		66 << MVS_SGPIO_CFG2_BLINK_SHIFT /* (66 * 0,121 Hz?)*/
	);

	mw32(MVS_SGPIO_CFG0 + MVS_SGPIO_HOST_OFFSET * mvi->id,
		MVS_SGPIO_CFG0_ENABLE |
		MVS_SGPIO_CFG0_BLINKA |
		MVS_SGPIO_CFG0_BLINKB |
		/* 3*4 data bits / PDU */
		(12 - 1) << MVS_SGPIO_CFG0_AUT_BITLEN_SHIFT
	);

	mw32(MVS_SGPIO_DCTRL + MVS_SGPIO_HOST_OFFSET * mvi->id,
		DEFAULT_SGPIO_BITS);

	mw32(MVS_SGPIO_DSRC + MVS_SGPIO_HOST_OFFSET * mvi->id,
		((mvi->id * 4) + 3) << (8 * 3) |
		((mvi->id * 4) + 2) << (8 * 2) |
		((mvi->id * 4) + 1) << (8 * 1) |
		((mvi->id * 4) + 0) << (8 * 0));

पूर्ण

अटल पूर्णांक mvs_94xx_init(काष्ठा mvs_info *mvi)
अणु
	व्योम __iomem *regs = mvi->regs;
	पूर्णांक i;
	u32 पंचांगp, cctl;
	u8 revision;

	revision = mvi->pdev->revision;
	mvs_show_pcie_usage(mvi);
	अगर (mvi->flags & MVF_FLAG_SOC) अणु
		पंचांगp = mr32(MVS_PHY_CTL);
		पंचांगp &= ~PCTL_PWR_OFF;
		पंचांगp |= PCTL_PHY_DSBL;
		mw32(MVS_PHY_CTL, पंचांगp);
	पूर्ण

	/* Init Chip */
	/* make sure RST is set; HBA_RST /should/ have करोne that क्रम us */
	cctl = mr32(MVS_CTL) & 0xFFFF;
	अगर (cctl & CCTL_RST)
		cctl &= ~CCTL_RST;
	अन्यथा
		mw32_f(MVS_CTL, cctl | CCTL_RST);

	अगर (mvi->flags & MVF_FLAG_SOC) अणु
		पंचांगp = mr32(MVS_PHY_CTL);
		पंचांगp &= ~PCTL_PWR_OFF;
		पंचांगp |= PCTL_COM_ON;
		पंचांगp &= ~PCTL_PHY_DSBL;
		पंचांगp |= PCTL_LINK_RST;
		mw32(MVS_PHY_CTL, पंचांगp);
		msleep(100);
		पंचांगp &= ~PCTL_LINK_RST;
		mw32(MVS_PHY_CTL, पंचांगp);
		msleep(100);
	पूर्ण

	/* disable Multiplexing, enable phy implemented */
	mw32(MVS_PORTS_IMP, 0xFF);

	अगर (revision == VANIR_A0_REV) अणु
		mw32(MVS_PA_VSR_ADDR, CMD_CMWK_OOB_DET);
		mw32(MVS_PA_VSR_PORT, 0x00018080);
	पूर्ण
	mw32(MVS_PA_VSR_ADDR, VSR_PHY_MODE2);
	अगर (revision == VANIR_A0_REV || revision == VANIR_B0_REV)
		/* set 6G/3G/1.5G, multiplexing, without SSC */
		mw32(MVS_PA_VSR_PORT, 0x0084d4fe);
	अन्यथा
		/* set 6G/3G/1.5G, multiplexing, with and without SSC */
		mw32(MVS_PA_VSR_PORT, 0x0084fffe);

	अगर (revision == VANIR_B0_REV) अणु
		mw32(MVS_PA_VSR_ADDR, CMD_APP_MEM_CTL);
		mw32(MVS_PA_VSR_PORT, 0x08001006);
		mw32(MVS_PA_VSR_ADDR, CMD_HOST_RD_DATA);
		mw32(MVS_PA_VSR_PORT, 0x0000705f);
	पूर्ण

	/* reset control */
	mw32(MVS_PCS, 0);		/* MVS_PCS */
	mw32(MVS_STP_REG_SET_0, 0);
	mw32(MVS_STP_REG_SET_1, 0);

	/* init phys */
	mvs_phy_hacks(mvi);

	/* disable non data frame retry */
	पंचांगp = mvs_cr32(mvi, CMD_SAS_CTL1);
	अगर ((revision == VANIR_A0_REV) ||
		(revision == VANIR_B0_REV) ||
		(revision == VANIR_C0_REV)) अणु
		पंचांगp &= ~0xffff;
		पंचांगp |= 0x007f;
		mvs_cw32(mvi, CMD_SAS_CTL1, पंचांगp);
	पूर्ण

	/* set LED blink when IO*/
	mw32(MVS_PA_VSR_ADDR, VSR_PHY_ACT_LED);
	पंचांगp = mr32(MVS_PA_VSR_PORT);
	पंचांगp &= 0xFFFF00FF;
	पंचांगp |= 0x00003300;
	mw32(MVS_PA_VSR_PORT, पंचांगp);

	mw32(MVS_CMD_LIST_LO, mvi->slot_dma);
	mw32(MVS_CMD_LIST_HI, (mvi->slot_dma >> 16) >> 16);

	mw32(MVS_RX_FIS_LO, mvi->rx_fis_dma);
	mw32(MVS_RX_FIS_HI, (mvi->rx_fis_dma >> 16) >> 16);

	mw32(MVS_TX_CFG, MVS_CHIP_SLOT_SZ);
	mw32(MVS_TX_LO, mvi->tx_dma);
	mw32(MVS_TX_HI, (mvi->tx_dma >> 16) >> 16);

	mw32(MVS_RX_CFG, MVS_RX_RING_SZ);
	mw32(MVS_RX_LO, mvi->rx_dma);
	mw32(MVS_RX_HI, (mvi->rx_dma >> 16) >> 16);

	क्रम (i = 0; i < mvi->chip->n_phy; i++) अणु
		mvs_94xx_phy_disable(mvi, i);
		/* set phy local SAS address */
		mvs_set_sas_addr(mvi, i, CONFIG_ID_FRAME3, CONFIG_ID_FRAME4,
						cpu_to_le64(mvi->phy[i].dev_sas_addr));

		mvs_94xx_enable_xmt(mvi, i);
		mvs_94xx_config_reg_from_hba(mvi, i);
		mvs_94xx_phy_enable(mvi, i);

		mvs_94xx_phy_reset(mvi, i, PHY_RST_HARD);
		msleep(500);
		mvs_94xx_detect_porttype(mvi, i);
	पूर्ण

	अगर (mvi->flags & MVF_FLAG_SOC) अणु
		/* set select रेजिस्टरs */
		ग_लिखोl(0x0E008000, regs + 0x000);
		ग_लिखोl(0x59000008, regs + 0x004);
		ग_लिखोl(0x20, regs + 0x008);
		ग_लिखोl(0x20, regs + 0x00c);
		ग_लिखोl(0x20, regs + 0x010);
		ग_लिखोl(0x20, regs + 0x014);
		ग_लिखोl(0x20, regs + 0x018);
		ग_लिखोl(0x20, regs + 0x01c);
	पूर्ण
	क्रम (i = 0; i < mvi->chip->n_phy; i++) अणु
		/* clear phy पूर्णांक status */
		पंचांगp = mvs_पढ़ो_port_irq_stat(mvi, i);
		पंचांगp &= ~PHYEV_SIG_FIS;
		mvs_ग_लिखो_port_irq_stat(mvi, i, पंचांगp);

		/* set phy पूर्णांक mask */
		पंचांगp = PHYEV_RDY_CH | PHYEV_BROAD_CH |
			PHYEV_ID_DONE  | PHYEV_DCDR_ERR | PHYEV_CRC_ERR ;
		mvs_ग_लिखो_port_irq_mask(mvi, i, पंचांगp);

		msleep(100);
		mvs_update_phyinfo(mvi, i, 1);
	पूर्ण

	/* little endian क्रम खोलो address and command table, etc. */
	cctl = mr32(MVS_CTL);
	cctl |= CCTL_ENDIAN_CMD;
	cctl &= ~CCTL_ENDIAN_OPEN;
	cctl |= CCTL_ENDIAN_RSP;
	mw32_f(MVS_CTL, cctl);

	/* reset CMD queue */
	पंचांगp = mr32(MVS_PCS);
	पंचांगp |= PCS_CMD_RST;
	पंचांगp &= ~PCS_SELF_CLEAR;
	mw32(MVS_PCS, पंचांगp);
	/*
	 * the max count is 0x1ff, जबतक our max slot is 0x200,
	 * it will make count 0.
	 */
	पंचांगp = 0;
	अगर (MVS_CHIP_SLOT_SZ > 0x1ff)
		mw32(MVS_INT_COAL, 0x1ff | COAL_EN);
	अन्यथा
		mw32(MVS_INT_COAL, MVS_CHIP_SLOT_SZ | COAL_EN);

	/* शेष पूर्णांकerrupt coalescing समय is 128us */
	पंचांगp = 0x10000 | पूर्णांकerrupt_coalescing;
	mw32(MVS_INT_COAL_TMOUT, पंचांगp);

	/* ladies and gentlemen, start your engines */
	mw32(MVS_TX_CFG, 0);
	mw32(MVS_TX_CFG, MVS_CHIP_SLOT_SZ | TX_EN);
	mw32(MVS_RX_CFG, MVS_RX_RING_SZ | RX_EN);
	/* enable CMD/CMPL_Q/RESP mode */
	mw32(MVS_PCS, PCS_SATA_RETRY_2 | PCS_FIS_RX_EN |
		PCS_CMD_EN | PCS_CMD_STOP_ERR);

	/* enable completion queue पूर्णांकerrupt */
	पंचांगp = (CINT_PORT_MASK | CINT_DONE | CINT_MEM | CINT_SRS | CINT_CI_STOP |
		CINT_DMA_PCIE | CINT_NON_SPEC_NCQ_ERROR);
	पंचांगp |= CINT_PHY_MASK;
	mw32(MVS_INT_MASK, पंचांगp);

	पंचांगp = mvs_cr32(mvi, CMD_LINK_TIMER);
	पंचांगp |= 0xFFFF0000;
	mvs_cw32(mvi, CMD_LINK_TIMER, पंचांगp);

	/* tune STP perक्रमmance */
	पंचांगp = 0x003F003F;
	mvs_cw32(mvi, CMD_PL_TIMER, पंचांगp);

	/* This can improve expander large block size seq ग_लिखो perक्रमmance */
	पंचांगp = mvs_cr32(mvi, CMD_PORT_LAYER_TIMER1);
	पंचांगp |= 0xFFFF007F;
	mvs_cw32(mvi, CMD_PORT_LAYER_TIMER1, पंचांगp);

	/* change the connection खोलो-बंद behavior (bit 9)
	 * set bit8 to 1 क्रम perक्रमmance tuning */
	पंचांगp = mvs_cr32(mvi, CMD_SL_MODE0);
	पंचांगp |= 0x00000300;
	/* set bit0 to 0 to enable retry क्रम no_dest reject हाल */
	पंचांगp &= 0xFFFFFFFE;
	mvs_cw32(mvi, CMD_SL_MODE0, पंचांगp);

	/* Enable SRS पूर्णांकerrupt */
	mw32(MVS_INT_MASK_SRS_0, 0xFFFF);

	mvs_94xx_sgpio_init(mvi);

	वापस 0;
पूर्ण

अटल पूर्णांक mvs_94xx_ioremap(काष्ठा mvs_info *mvi)
अणु
	अगर (!mvs_ioremap(mvi, 2, -1)) अणु
		mvi->regs_ex = mvi->regs + 0x10200;
		mvi->regs += 0x20000;
		अगर (mvi->id == 1)
			mvi->regs += 0x4000;
		वापस 0;
	पूर्ण
	वापस -1;
पूर्ण

अटल व्योम mvs_94xx_iounmap(काष्ठा mvs_info *mvi)
अणु
	अगर (mvi->regs) अणु
		mvi->regs -= 0x20000;
		अगर (mvi->id == 1)
			mvi->regs -= 0x4000;
		mvs_iounmap(mvi->regs);
	पूर्ण
पूर्ण

अटल व्योम mvs_94xx_पूर्णांकerrupt_enable(काष्ठा mvs_info *mvi)
अणु
	व्योम __iomem *regs = mvi->regs_ex;
	u32 पंचांगp;

	पंचांगp = mr32(MVS_GBL_CTL);
	पंचांगp |= (MVS_IRQ_SAS_A | MVS_IRQ_SAS_B);
	mw32(MVS_GBL_INT_STAT, पंचांगp);
	ग_लिखोl(पंचांगp, regs + 0x0C);
	ग_लिखोl(पंचांगp, regs + 0x10);
	ग_लिखोl(पंचांगp, regs + 0x14);
	ग_लिखोl(पंचांगp, regs + 0x18);
	mw32(MVS_GBL_CTL, पंचांगp);
पूर्ण

अटल व्योम mvs_94xx_पूर्णांकerrupt_disable(काष्ठा mvs_info *mvi)
अणु
	व्योम __iomem *regs = mvi->regs_ex;
	u32 पंचांगp;

	पंचांगp = mr32(MVS_GBL_CTL);

	पंचांगp &= ~(MVS_IRQ_SAS_A | MVS_IRQ_SAS_B);
	mw32(MVS_GBL_INT_STAT, पंचांगp);
	ग_लिखोl(पंचांगp, regs + 0x0C);
	ग_लिखोl(पंचांगp, regs + 0x10);
	ग_लिखोl(पंचांगp, regs + 0x14);
	ग_लिखोl(पंचांगp, regs + 0x18);
	mw32(MVS_GBL_CTL, पंचांगp);
पूर्ण

अटल u32 mvs_94xx_isr_status(काष्ठा mvs_info *mvi, पूर्णांक irq)
अणु
	व्योम __iomem *regs = mvi->regs_ex;
	u32 stat = 0;
	अगर (!(mvi->flags & MVF_FLAG_SOC)) अणु
		stat = mr32(MVS_GBL_INT_STAT);

		अगर (!(stat & (MVS_IRQ_SAS_A | MVS_IRQ_SAS_B)))
			वापस 0;
	पूर्ण
	वापस stat;
पूर्ण

अटल irqवापस_t mvs_94xx_isr(काष्ठा mvs_info *mvi, पूर्णांक irq, u32 stat)
अणु
	व्योम __iomem *regs = mvi->regs;

	अगर (((stat & MVS_IRQ_SAS_A) && mvi->id == 0) ||
			((stat & MVS_IRQ_SAS_B) && mvi->id == 1)) अणु
		mw32_f(MVS_INT_STAT, CINT_DONE);

		spin_lock(&mvi->lock);
		mvs_पूर्णांक_full(mvi);
		spin_unlock(&mvi->lock);
	पूर्ण
	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम mvs_94xx_command_active(काष्ठा mvs_info *mvi, u32 slot_idx)
अणु
	u32 पंचांगp;
	पंचांगp = mvs_cr32(mvi, MVS_COMMAND_ACTIVE+(slot_idx >> 3));
	अगर (पंचांगp & 1 << (slot_idx % 32)) अणु
		mv_prपूर्णांकk("command active %08X,  slot [%x].\n", पंचांगp, slot_idx);
		mvs_cw32(mvi, MVS_COMMAND_ACTIVE + (slot_idx >> 3),
			1 << (slot_idx % 32));
		करो अणु
			पंचांगp = mvs_cr32(mvi,
				MVS_COMMAND_ACTIVE + (slot_idx >> 3));
		पूर्ण जबतक (पंचांगp & 1 << (slot_idx % 32));
	पूर्ण
पूर्ण

अटल व्योम
mvs_94xx_clear_srs_irq(काष्ठा mvs_info *mvi, u8 reg_set, u8 clear_all)
अणु
	व्योम __iomem *regs = mvi->regs;
	u32 पंचांगp;

	अगर (clear_all) अणु
		पंचांगp = mr32(MVS_INT_STAT_SRS_0);
		अगर (पंचांगp) अणु
			mv_dprपूर्णांकk("check SRS 0 %08X.\n", पंचांगp);
			mw32(MVS_INT_STAT_SRS_0, पंचांगp);
		पूर्ण
		पंचांगp = mr32(MVS_INT_STAT_SRS_1);
		अगर (पंचांगp) अणु
			mv_dprपूर्णांकk("check SRS 1 %08X.\n", पंचांगp);
			mw32(MVS_INT_STAT_SRS_1, पंचांगp);
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (reg_set > 31)
			पंचांगp = mr32(MVS_INT_STAT_SRS_1);
		अन्यथा
			पंचांगp = mr32(MVS_INT_STAT_SRS_0);

		अगर (पंचांगp & (1 << (reg_set % 32))) अणु
			mv_dprपूर्णांकk("register set 0x%x was stopped.\n", reg_set);
			अगर (reg_set > 31)
				mw32(MVS_INT_STAT_SRS_1, 1 << (reg_set % 32));
			अन्यथा
				mw32(MVS_INT_STAT_SRS_0, 1 << (reg_set % 32));
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम mvs_94xx_issue_stop(काष्ठा mvs_info *mvi, क्रमागत mvs_port_type type,
				u32 tfs)
अणु
	व्योम __iomem *regs = mvi->regs;
	u32 पंचांगp;
	mvs_94xx_clear_srs_irq(mvi, 0, 1);

	पंचांगp = mr32(MVS_INT_STAT);
	mw32(MVS_INT_STAT, पंचांगp | CINT_CI_STOP);
	पंचांगp = mr32(MVS_PCS) | 0xFF00;
	mw32(MVS_PCS, पंचांगp);
पूर्ण

अटल व्योम mvs_94xx_non_spec_ncq_error(काष्ठा mvs_info *mvi)
अणु
	व्योम __iomem *regs = mvi->regs;
	u32 err_0, err_1;
	u8 i;
	काष्ठा mvs_device *device;

	err_0 = mr32(MVS_NON_NCQ_ERR_0);
	err_1 = mr32(MVS_NON_NCQ_ERR_1);

	mv_dprपूर्णांकk("non specific ncq error err_0:%x,err_1:%x.\n",
			err_0, err_1);
	क्रम (i = 0; i < 32; i++) अणु
		अगर (err_0 & bit(i)) अणु
			device = mvs_find_dev_by_reg_set(mvi, i);
			अगर (device)
				mvs_release_task(mvi, device->sas_device);
		पूर्ण
		अगर (err_1 & bit(i)) अणु
			device = mvs_find_dev_by_reg_set(mvi, i+32);
			अगर (device)
				mvs_release_task(mvi, device->sas_device);
		पूर्ण
	पूर्ण

	mw32(MVS_NON_NCQ_ERR_0, err_0);
	mw32(MVS_NON_NCQ_ERR_1, err_1);
पूर्ण

अटल व्योम mvs_94xx_मुक्त_reg_set(काष्ठा mvs_info *mvi, u8 *tfs)
अणु
	व्योम __iomem *regs = mvi->regs;
	u8 reg_set = *tfs;

	अगर (*tfs == MVS_ID_NOT_MAPPED)
		वापस;

	mvi->sata_reg_set &= ~bit(reg_set);
	अगर (reg_set < 32)
		w_reg_set_enable(reg_set, (u32)mvi->sata_reg_set);
	अन्यथा
		w_reg_set_enable(reg_set, (u32)(mvi->sata_reg_set >> 32));

	*tfs = MVS_ID_NOT_MAPPED;

	वापस;
पूर्ण

अटल u8 mvs_94xx_assign_reg_set(काष्ठा mvs_info *mvi, u8 *tfs)
अणु
	पूर्णांक i;
	व्योम __iomem *regs = mvi->regs;

	अगर (*tfs != MVS_ID_NOT_MAPPED)
		वापस 0;

	i = mv_ffc64(mvi->sata_reg_set);
	अगर (i >= 32) अणु
		mvi->sata_reg_set |= bit(i);
		w_reg_set_enable(i, (u32)(mvi->sata_reg_set >> 32));
		*tfs = i;
		वापस 0;
	पूर्ण अन्यथा अगर (i >= 0) अणु
		mvi->sata_reg_set |= bit(i);
		w_reg_set_enable(i, (u32)mvi->sata_reg_set);
		*tfs = i;
		वापस 0;
	पूर्ण
	वापस MVS_ID_NOT_MAPPED;
पूर्ण

अटल व्योम mvs_94xx_make_prd(काष्ठा scatterlist *scatter, पूर्णांक nr, व्योम *prd)
अणु
	पूर्णांक i;
	काष्ठा scatterlist *sg;
	काष्ठा mvs_prd *buf_prd = prd;
	काष्ठा mvs_prd_imt im_len;
	*(u32 *)&im_len = 0;
	क्रम_each_sg(scatter, sg, nr, i) अणु
		buf_prd->addr = cpu_to_le64(sg_dma_address(sg));
		im_len.len = sg_dma_len(sg);
		buf_prd->im_len = cpu_to_le32(*(u32 *)&im_len);
		buf_prd++;
	पूर्ण
पूर्ण

अटल पूर्णांक mvs_94xx_oob_करोne(काष्ठा mvs_info *mvi, पूर्णांक i)
अणु
	u32 phy_st;
	phy_st = mvs_पढ़ो_phy_ctl(mvi, i);
	अगर (phy_st & PHY_READY_MASK)
		वापस 1;
	वापस 0;
पूर्ण

अटल व्योम mvs_94xx_get_dev_identअगरy_frame(काष्ठा mvs_info *mvi, पूर्णांक port_id,
					काष्ठा sas_identअगरy_frame *id)
अणु
	पूर्णांक i;
	u32 id_frame[7];

	क्रम (i = 0; i < 7; i++) अणु
		mvs_ग_लिखो_port_cfg_addr(mvi, port_id,
					CONFIG_ID_FRAME0 + i * 4);
		id_frame[i] = cpu_to_le32(mvs_पढ़ो_port_cfg_data(mvi, port_id));
	पूर्ण
	स_नकल(id, id_frame, 28);
पूर्ण

अटल व्योम mvs_94xx_get_att_identअगरy_frame(काष्ठा mvs_info *mvi, पूर्णांक port_id,
					काष्ठा sas_identअगरy_frame *id)
अणु
	पूर्णांक i;
	u32 id_frame[7];

	क्रम (i = 0; i < 7; i++) अणु
		mvs_ग_लिखो_port_cfg_addr(mvi, port_id,
					CONFIG_ATT_ID_FRAME0 + i * 4);
		id_frame[i] = cpu_to_le32(mvs_पढ़ो_port_cfg_data(mvi, port_id));
		mv_dprपूर्णांकk("94xx phy %d atta frame %d %x.\n",
			port_id + mvi->id * mvi->chip->n_phy, i, id_frame[i]);
	पूर्ण
	स_नकल(id, id_frame, 28);
पूर्ण

अटल u32 mvs_94xx_make_dev_info(काष्ठा sas_identअगरy_frame *id)
अणु
	u32 att_dev_info = 0;

	att_dev_info |= id->dev_type;
	अगर (id->stp_iport)
		att_dev_info |= PORT_DEV_STP_INIT;
	अगर (id->smp_iport)
		att_dev_info |= PORT_DEV_SMP_INIT;
	अगर (id->ssp_iport)
		att_dev_info |= PORT_DEV_SSP_INIT;
	अगर (id->stp_tport)
		att_dev_info |= PORT_DEV_STP_TRGT;
	अगर (id->smp_tport)
		att_dev_info |= PORT_DEV_SMP_TRGT;
	अगर (id->ssp_tport)
		att_dev_info |= PORT_DEV_SSP_TRGT;

	att_dev_info |= (u32)id->phy_id<<24;
	वापस att_dev_info;
पूर्ण

अटल u32 mvs_94xx_make_att_info(काष्ठा sas_identअगरy_frame *id)
अणु
	वापस mvs_94xx_make_dev_info(id);
पूर्ण

अटल व्योम mvs_94xx_fix_phy_info(काष्ठा mvs_info *mvi, पूर्णांक i,
				काष्ठा sas_identअगरy_frame *id)
अणु
	काष्ठा mvs_phy *phy = &mvi->phy[i];
	काष्ठा asd_sas_phy *sas_phy = &phy->sas_phy;
	mv_dprपूर्णांकk("get all reg link rate is 0x%x\n", phy->phy_status);
	sas_phy->linkrate =
		(phy->phy_status & PHY_NEG_SPP_PHYS_LINK_RATE_MASK) >>
			PHY_NEG_SPP_PHYS_LINK_RATE_MASK_OFFSET;
	sas_phy->linkrate += 0x8;
	mv_dprपूर्णांकk("get link rate is %d\n", sas_phy->linkrate);
	phy->minimum_linkrate = SAS_LINK_RATE_1_5_GBPS;
	phy->maximum_linkrate = SAS_LINK_RATE_6_0_GBPS;
	mvs_94xx_get_dev_identअगरy_frame(mvi, i, id);
	phy->dev_info = mvs_94xx_make_dev_info(id);

	अगर (phy->phy_type & PORT_TYPE_SAS) अणु
		mvs_94xx_get_att_identअगरy_frame(mvi, i, id);
		phy->att_dev_info = mvs_94xx_make_att_info(id);
		phy->att_dev_sas_addr = *(u64 *)id->sas_addr;
	पूर्ण अन्यथा अणु
		phy->att_dev_info = PORT_DEV_STP_TRGT | 1;
	पूर्ण

	/* enable spin up bit */
	mvs_ग_लिखो_port_cfg_addr(mvi, i, PHYR_PHY_STAT);
	mvs_ग_लिखो_port_cfg_data(mvi, i, 0x04);

पूर्ण

अटल व्योम mvs_94xx_phy_set_link_rate(काष्ठा mvs_info *mvi, u32 phy_id,
				       काष्ठा sas_phy_linkrates *rates)
अणु
	u32 lrmax = 0;
	u32 पंचांगp;

	पंचांगp = mvs_पढ़ो_phy_ctl(mvi, phy_id);
	lrmax = (rates->maximum_linkrate - SAS_LINK_RATE_1_5_GBPS) << 12;

	अगर (lrmax) अणु
		पंचांगp &= ~(0x3 << 12);
		पंचांगp |= lrmax;
	पूर्ण
	mvs_ग_लिखो_phy_ctl(mvi, phy_id, पंचांगp);
	mvs_94xx_phy_reset(mvi, phy_id, PHY_RST_HARD);
पूर्ण

अटल व्योम mvs_94xx_clear_active_cmds(काष्ठा mvs_info *mvi)
अणु
	u32 पंचांगp;
	व्योम __iomem *regs = mvi->regs;
	पंचांगp = mr32(MVS_STP_REG_SET_0);
	mw32(MVS_STP_REG_SET_0, 0);
	mw32(MVS_STP_REG_SET_0, पंचांगp);
	पंचांगp = mr32(MVS_STP_REG_SET_1);
	mw32(MVS_STP_REG_SET_1, 0);
	mw32(MVS_STP_REG_SET_1, पंचांगp);
पूर्ण


अटल u32 mvs_94xx_spi_पढ़ो_data(काष्ठा mvs_info *mvi)
अणु
	व्योम __iomem *regs = mvi->regs_ex - 0x10200;
	वापस mr32(SPI_RD_DATA_REG_94XX);
पूर्ण

अटल व्योम mvs_94xx_spi_ग_लिखो_data(काष्ठा mvs_info *mvi, u32 data)
अणु
	व्योम __iomem *regs = mvi->regs_ex - 0x10200;

	mw32(SPI_RD_DATA_REG_94XX, data);
पूर्ण


अटल पूर्णांक mvs_94xx_spi_buildcmd(काष्ठा mvs_info *mvi,
				 u32      *dwCmd,
				 u8       cmd,
				 u8       पढ़ो,
				 u8       length,
				 u32      addr
				)
अणु
	व्योम __iomem *regs = mvi->regs_ex - 0x10200;
	u32  dwTmp;

	dwTmp = ((u32)cmd << 8) | ((u32)length << 4);
	अगर (पढ़ो)
		dwTmp |= SPI_CTRL_READ_94XX;

	अगर (addr != MV_MAX_U32) अणु
		mw32(SPI_ADDR_REG_94XX, (addr & 0x0003FFFFL));
		dwTmp |= SPI_ADDR_VLD_94XX;
	पूर्ण

	*dwCmd = dwTmp;
	वापस 0;
पूर्ण


अटल पूर्णांक mvs_94xx_spi_issuecmd(काष्ठा mvs_info *mvi, u32 cmd)
अणु
	व्योम __iomem *regs = mvi->regs_ex - 0x10200;
	mw32(SPI_CTRL_REG_94XX, cmd | SPI_CTRL_SpiStart_94XX);

	वापस 0;
पूर्ण

अटल पूर्णांक mvs_94xx_spi_रुकोdataपढ़ोy(काष्ठा mvs_info *mvi, u32 समयout)
अणु
	व्योम __iomem *regs = mvi->regs_ex - 0x10200;
	u32   i, dwTmp;

	क्रम (i = 0; i < समयout; i++) अणु
		dwTmp = mr32(SPI_CTRL_REG_94XX);
		अगर (!(dwTmp & SPI_CTRL_SpiStart_94XX))
			वापस 0;
		msleep(10);
	पूर्ण

	वापस -1;
पूर्ण

अटल व्योम mvs_94xx_fix_dma(काष्ठा mvs_info *mvi, u32 phy_mask,
			     पूर्णांक buf_len, पूर्णांक from, व्योम *prd)
अणु
	पूर्णांक i;
	काष्ठा mvs_prd *buf_prd = prd;
	dma_addr_t buf_dma;
	काष्ठा mvs_prd_imt im_len;

	*(u32 *)&im_len = 0;
	buf_prd += from;

#घोषणा PRD_CHAINED_ENTRY 0x01
	अगर ((mvi->pdev->revision == VANIR_A0_REV) ||
			(mvi->pdev->revision == VANIR_B0_REV))
		buf_dma = (phy_mask <= 0x08) ?
				mvi->bulk_buffer_dma : mvi->bulk_buffer_dma1;
	अन्यथा
		वापस;

	क्रम (i = from; i < MAX_SG_ENTRY; i++, ++buf_prd) अणु
		अगर (i == MAX_SG_ENTRY - 1) अणु
			buf_prd->addr = cpu_to_le64(virt_to_phys(buf_prd - 1));
			im_len.len = 2;
			im_len.misc_ctl = PRD_CHAINED_ENTRY;
		पूर्ण अन्यथा अणु
			buf_prd->addr = cpu_to_le64(buf_dma);
			im_len.len = buf_len;
		पूर्ण
		buf_prd->im_len = cpu_to_le32(*(u32 *)&im_len);
	पूर्ण
पूर्ण

अटल व्योम mvs_94xx_tune_पूर्णांकerrupt(काष्ठा mvs_info *mvi, u32 समय)
अणु
	व्योम __iomem *regs = mvi->regs;
	u32 पंचांगp = 0;
	/*
	 * the max count is 0x1ff, जबतक our max slot is 0x200,
	 * it will make count 0.
	 */
	अगर (समय == 0) अणु
		mw32(MVS_INT_COAL, 0);
		mw32(MVS_INT_COAL_TMOUT, 0x10000);
	पूर्ण अन्यथा अणु
		अगर (MVS_CHIP_SLOT_SZ > 0x1ff)
			mw32(MVS_INT_COAL, 0x1ff|COAL_EN);
		अन्यथा
			mw32(MVS_INT_COAL, MVS_CHIP_SLOT_SZ|COAL_EN);

		पंचांगp = 0x10000 | समय;
		mw32(MVS_INT_COAL_TMOUT, पंचांगp);
	पूर्ण

पूर्ण

अटल पूर्णांक mvs_94xx_gpio_ग_लिखो(काष्ठा mvs_prv_info *mvs_prv,
			u8 reg_type, u8 reg_index,
			u8 reg_count, u8 *ग_लिखो_data)
अणु
	पूर्णांक i;

	चयन (reg_type) अणु

	हाल SAS_GPIO_REG_TX_GP:
		अगर (reg_index == 0)
			वापस -EINVAL;

		अगर (reg_count > 1)
			वापस -EINVAL;

		अगर (reg_count == 0)
			वापस 0;

		/* maximum supported bits = hosts * 4 drives * 3 bits */
		क्रम (i = 0; i < mvs_prv->n_host * 4 * 3; i++) अणु

			/* select host */
			काष्ठा mvs_info *mvi = mvs_prv->mvi[i/(4*3)];

			व्योम __iomem *regs = mvi->regs_ex - 0x10200;

			पूर्णांक drive = (i/3) & (4-1); /* drive number on host */
			पूर्णांक driveshअगरt = drive * 8; /* bit offset of drive */
			u32 block = ioपढ़ो32be(regs + MVS_SGPIO_DCTRL +
				MVS_SGPIO_HOST_OFFSET * mvi->id);

			/*
			* अगर bit is set then create a mask with the first
			* bit of the drive set in the mask ...
			*/
			u32 bit = get_unaligned_be32(ग_लिखो_data) & (1 << i) ?
				1 << driveshअगरt : 0;

			/*
			* ... and then shअगरt it to the right position based
			* on the led type (activity/id/fail)
			*/
			चयन (i%3) अणु
			हाल 0: /* activity */
				block &= ~((0x7 << MVS_SGPIO_DCTRL_ACT_SHIFT)
					<< driveshअगरt);
					/* hardwire activity bit to SOF */
				block |= LED_BLINKA_SOF << (
					MVS_SGPIO_DCTRL_ACT_SHIFT +
					driveshअगरt);
				अवरोध;
			हाल 1: /* id */
				block &= ~((0x3 << MVS_SGPIO_DCTRL_LOC_SHIFT)
					<< driveshअगरt);
				block |= bit << MVS_SGPIO_DCTRL_LOC_SHIFT;
				अवरोध;
			हाल 2: /* fail */
				block &= ~((0x7 << MVS_SGPIO_DCTRL_ERR_SHIFT)
					<< driveshअगरt);
				block |= bit << MVS_SGPIO_DCTRL_ERR_SHIFT;
				अवरोध;
			पूर्ण

			ioग_लिखो32be(block,
				regs + MVS_SGPIO_DCTRL +
				MVS_SGPIO_HOST_OFFSET * mvi->id);

		पूर्ण

		वापस reg_count;

	हाल SAS_GPIO_REG_TX:
		अगर (reg_index + reg_count > mvs_prv->n_host)
			वापस -EINVAL;

		क्रम (i = 0; i < reg_count; i++) अणु
			काष्ठा mvs_info *mvi = mvs_prv->mvi[i+reg_index];
			व्योम __iomem *regs = mvi->regs_ex - 0x10200;

			mw32(MVS_SGPIO_DCTRL + MVS_SGPIO_HOST_OFFSET * mvi->id,
				((u32 *) ग_लिखो_data)[i]);
		पूर्ण
		वापस reg_count;
	पूर्ण
	वापस -ENOSYS;
पूर्ण

स्थिर काष्ठा mvs_dispatch mvs_94xx_dispatch = अणु
	"mv94xx",
	mvs_94xx_init,
	शून्य,
	mvs_94xx_ioremap,
	mvs_94xx_iounmap,
	mvs_94xx_isr,
	mvs_94xx_isr_status,
	mvs_94xx_पूर्णांकerrupt_enable,
	mvs_94xx_पूर्णांकerrupt_disable,
	mvs_पढ़ो_phy_ctl,
	mvs_ग_लिखो_phy_ctl,
	mvs_पढ़ो_port_cfg_data,
	mvs_ग_लिखो_port_cfg_data,
	mvs_ग_लिखो_port_cfg_addr,
	mvs_पढ़ो_port_vsr_data,
	mvs_ग_लिखो_port_vsr_data,
	mvs_ग_लिखो_port_vsr_addr,
	mvs_पढ़ो_port_irq_stat,
	mvs_ग_लिखो_port_irq_stat,
	mvs_पढ़ो_port_irq_mask,
	mvs_ग_लिखो_port_irq_mask,
	mvs_94xx_command_active,
	mvs_94xx_clear_srs_irq,
	mvs_94xx_issue_stop,
	mvs_start_delivery,
	mvs_rx_update,
	mvs_पूर्णांक_full,
	mvs_94xx_assign_reg_set,
	mvs_94xx_मुक्त_reg_set,
	mvs_get_prd_size,
	mvs_get_prd_count,
	mvs_94xx_make_prd,
	mvs_94xx_detect_porttype,
	mvs_94xx_oob_करोne,
	mvs_94xx_fix_phy_info,
	शून्य,
	mvs_94xx_phy_set_link_rate,
	mvs_hw_max_link_rate,
	mvs_94xx_phy_disable,
	mvs_94xx_phy_enable,
	mvs_94xx_phy_reset,
	शून्य,
	mvs_94xx_clear_active_cmds,
	mvs_94xx_spi_पढ़ो_data,
	mvs_94xx_spi_ग_लिखो_data,
	mvs_94xx_spi_buildcmd,
	mvs_94xx_spi_issuecmd,
	mvs_94xx_spi_रुकोdataपढ़ोy,
	mvs_94xx_fix_dma,
	mvs_94xx_tune_पूर्णांकerrupt,
	mvs_94xx_non_spec_ncq_error,
	mvs_94xx_gpio_ग_लिखो,
पूर्ण;

