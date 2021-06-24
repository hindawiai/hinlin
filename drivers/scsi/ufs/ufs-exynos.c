<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * UFS Host Controller driver क्रम Exynos specअगरic extensions
 *
 * Copyright (C) 2014-2015 Samsung Electronics Co., Ltd.
 * Author: Seungwon Jeon  <essuuj@gmail.com>
 * Author: Alim Akhtar <alim.akhtar@samsung.com>
 *
 */

#समावेश <linux/clk.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/phy/phy.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश "ufshcd.h"
#समावेश "ufshcd-pltfrm.h"
#समावेश "ufshci.h"
#समावेश "unipro.h"

#समावेश "ufs-exynos.h"

/*
 * Exynos's Venकरोr specअगरic रेजिस्टरs क्रम UFSHCI
 */
#घोषणा HCI_TXPRDT_ENTRY_SIZE	0x00
#घोषणा PRDT_PREFECT_EN		BIT(31)
#घोषणा PRDT_SET_SIZE(x)	((x) & 0x1F)
#घोषणा HCI_RXPRDT_ENTRY_SIZE	0x04
#घोषणा HCI_1US_TO_CNT_VAL	0x0C
#घोषणा CNT_VAL_1US_MASK	0x3FF
#घोषणा HCI_UTRL_NEXUS_TYPE	0x40
#घोषणा HCI_UTMRL_NEXUS_TYPE	0x44
#घोषणा HCI_SW_RST		0x50
#घोषणा UFS_LINK_SW_RST		BIT(0)
#घोषणा UFS_UNIPRO_SW_RST	BIT(1)
#घोषणा UFS_SW_RST_MASK		(UFS_UNIPRO_SW_RST | UFS_LINK_SW_RST)
#घोषणा HCI_DATA_REORDER	0x60
#घोषणा HCI_UNIPRO_APB_CLK_CTRL	0x68
#घोषणा UNIPRO_APB_CLK(v, x)	(((v) & ~0xF) | ((x) & 0xF))
#घोषणा HCI_AXIDMA_RWDATA_BURST_LEN	0x6C
#घोषणा HCI_GPIO_OUT		0x70
#घोषणा HCI_ERR_EN_PA_LAYER	0x78
#घोषणा HCI_ERR_EN_DL_LAYER	0x7C
#घोषणा HCI_ERR_EN_N_LAYER	0x80
#घोषणा HCI_ERR_EN_T_LAYER	0x84
#घोषणा HCI_ERR_EN_DME_LAYER	0x88
#घोषणा HCI_CLKSTOP_CTRL	0xB0
#घोषणा REFCLK_STOP		BIT(2)
#घोषणा UNIPRO_MCLK_STOP	BIT(1)
#घोषणा UNIPRO_PCLK_STOP	BIT(0)
#घोषणा CLK_STOP_MASK		(REFCLK_STOP |\
				 UNIPRO_MCLK_STOP |\
				 UNIPRO_PCLK_STOP)
#घोषणा HCI_MISC		0xB4
#घोषणा REFCLK_CTRL_EN		BIT(7)
#घोषणा UNIPRO_PCLK_CTRL_EN	BIT(6)
#घोषणा UNIPRO_MCLK_CTRL_EN	BIT(5)
#घोषणा HCI_CORECLK_CTRL_EN	BIT(4)
#घोषणा CLK_CTRL_EN_MASK	(REFCLK_CTRL_EN |\
				 UNIPRO_PCLK_CTRL_EN |\
				 UNIPRO_MCLK_CTRL_EN)
/* Device fatal error */
#घोषणा DFES_ERR_EN		BIT(31)
#घोषणा DFES_DEF_L2_ERRS	(UIC_DATA_LINK_LAYER_ERROR_RX_BUF_OF |\
				 UIC_DATA_LINK_LAYER_ERROR_PA_INIT)
#घोषणा DFES_DEF_L3_ERRS	(UIC_NETWORK_UNSUPPORTED_HEADER_TYPE |\
				 UIC_NETWORK_BAD_DEVICEID_ENC |\
				 UIC_NETWORK_LHDR_TRAP_PACKET_DROPPING)
#घोषणा DFES_DEF_L4_ERRS	(UIC_TRANSPORT_UNSUPPORTED_HEADER_TYPE |\
				 UIC_TRANSPORT_UNKNOWN_CPORTID |\
				 UIC_TRANSPORT_NO_CONNECTION_RX |\
				 UIC_TRANSPORT_BAD_TC)

क्रमागत अणु
	UNIPRO_L1_5 = 0,/* PHY Adapter */
	UNIPRO_L2,	/* Data Link */
	UNIPRO_L3,	/* Network */
	UNIPRO_L4,	/* Transport */
	UNIPRO_DME,	/* DME */
पूर्ण;

/*
 * UNIPRO रेजिस्टरs
 */
#घोषणा UNIPRO_COMP_VERSION			0x000
#घोषणा UNIPRO_DME_PWR_REQ			0x090
#घोषणा UNIPRO_DME_PWR_REQ_POWERMODE		0x094
#घोषणा UNIPRO_DME_PWR_REQ_LOCALL2TIMER0	0x098
#घोषणा UNIPRO_DME_PWR_REQ_LOCALL2TIMER1	0x09C
#घोषणा UNIPRO_DME_PWR_REQ_LOCALL2TIMER2	0x0A0
#घोषणा UNIPRO_DME_PWR_REQ_REMOTEL2TIMER0	0x0A4
#घोषणा UNIPRO_DME_PWR_REQ_REMOTEL2TIMER1	0x0A8
#घोषणा UNIPRO_DME_PWR_REQ_REMOTEL2TIMER2	0x0AC

/*
 * UFS Protector रेजिस्टरs
 */
#घोषणा UFSPRSECURITY	0x010
#घोषणा NSSMU		BIT(14)
#घोषणा UFSPSBEGIN0	0x200
#घोषणा UFSPSEND0	0x204
#घोषणा UFSPSLUN0	0x208
#घोषणा UFSPSCTRL0	0x20C

#घोषणा CNTR_DIV_VAL 40

अटल व्योम exynos_ufs_स्वतः_ctrl_hcc(काष्ठा exynos_ufs *ufs, bool en);
अटल व्योम exynos_ufs_ctrl_clkstop(काष्ठा exynos_ufs *ufs, bool en);

अटल अंतरभूत व्योम exynos_ufs_enable_स्वतः_ctrl_hcc(काष्ठा exynos_ufs *ufs)
अणु
	exynos_ufs_स्वतः_ctrl_hcc(ufs, true);
पूर्ण

अटल अंतरभूत व्योम exynos_ufs_disable_स्वतः_ctrl_hcc(काष्ठा exynos_ufs *ufs)
अणु
	exynos_ufs_स्वतः_ctrl_hcc(ufs, false);
पूर्ण

अटल अंतरभूत व्योम exynos_ufs_disable_स्वतः_ctrl_hcc_save(
					काष्ठा exynos_ufs *ufs, u32 *val)
अणु
	*val = hci_पढ़ोl(ufs, HCI_MISC);
	exynos_ufs_स्वतः_ctrl_hcc(ufs, false);
पूर्ण

अटल अंतरभूत व्योम exynos_ufs_स्वतः_ctrl_hcc_restore(
					काष्ठा exynos_ufs *ufs, u32 *val)
अणु
	hci_ग_लिखोl(ufs, *val, HCI_MISC);
पूर्ण

अटल अंतरभूत व्योम exynos_ufs_gate_clks(काष्ठा exynos_ufs *ufs)
अणु
	exynos_ufs_ctrl_clkstop(ufs, true);
पूर्ण

अटल अंतरभूत व्योम exynos_ufs_ungate_clks(काष्ठा exynos_ufs *ufs)
अणु
	exynos_ufs_ctrl_clkstop(ufs, false);
पूर्ण

अटल पूर्णांक exynos7_ufs_drv_init(काष्ठा device *dev, काष्ठा exynos_ufs *ufs)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक exynos7_ufs_pre_link(काष्ठा exynos_ufs *ufs)
अणु
	काष्ठा ufs_hba *hba = ufs->hba;
	u32 val = ufs->drv_data->uic_attr->pa_dbg_option_suite;
	पूर्णांक i;

	exynos_ufs_enable_ov_पंचांग(hba);
	क्रम_each_ufs_tx_lane(ufs, i)
		ufshcd_dme_set(hba, UIC_ARG_MIB_SEL(0x297, i), 0x17);
	क्रम_each_ufs_rx_lane(ufs, i) अणु
		ufshcd_dme_set(hba, UIC_ARG_MIB_SEL(0x362, i), 0xff);
		ufshcd_dme_set(hba, UIC_ARG_MIB_SEL(0x363, i), 0x00);
	पूर्ण
	exynos_ufs_disable_ov_पंचांग(hba);

	क्रम_each_ufs_tx_lane(ufs, i)
		ufshcd_dme_set(hba,
			UIC_ARG_MIB_SEL(TX_HIBERN8_CONTROL, i), 0x0);
	ufshcd_dme_set(hba, UIC_ARG_MIB(PA_DBG_TXPHY_CFGUPDT), 0x1);
	udelay(1);
	ufshcd_dme_set(hba, UIC_ARG_MIB(PA_DBG_OPTION_SUITE), val | (1 << 12));
	ufshcd_dme_set(hba, UIC_ARG_MIB(PA_DBG_SKIP_RESET_PHY), 0x1);
	ufshcd_dme_set(hba, UIC_ARG_MIB(PA_DBG_SKIP_LINE_RESET), 0x1);
	ufshcd_dme_set(hba, UIC_ARG_MIB(PA_DBG_LINE_RESET_REQ), 0x1);
	udelay(1600);
	ufshcd_dme_set(hba, UIC_ARG_MIB(PA_DBG_OPTION_SUITE), val);

	वापस 0;
पूर्ण

अटल पूर्णांक exynos7_ufs_post_link(काष्ठा exynos_ufs *ufs)
अणु
	काष्ठा ufs_hba *hba = ufs->hba;
	पूर्णांक i;

	exynos_ufs_enable_ov_पंचांग(hba);
	क्रम_each_ufs_tx_lane(ufs, i) अणु
		ufshcd_dme_set(hba, UIC_ARG_MIB_SEL(0x28b, i), 0x83);
		ufshcd_dme_set(hba, UIC_ARG_MIB_SEL(0x29a, i), 0x07);
		ufshcd_dme_set(hba, UIC_ARG_MIB_SEL(0x277, i),
			TX_LINERESET_N(exynos_ufs_calc_समय_cntr(ufs, 200000)));
	पूर्ण
	exynos_ufs_disable_ov_पंचांग(hba);

	exynos_ufs_enable_dbg_mode(hba);
	ufshcd_dme_set(hba, UIC_ARG_MIB(PA_SAVECONFIGTIME), 0xbb8);
	exynos_ufs_disable_dbg_mode(hba);

	वापस 0;
पूर्ण

अटल पूर्णांक exynos7_ufs_pre_pwr_change(काष्ठा exynos_ufs *ufs,
						काष्ठा ufs_pa_layer_attr *pwr)
अणु
	unipro_ग_लिखोl(ufs, 0x22, UNIPRO_DBG_FORCE_DME_CTRL_STATE);

	वापस 0;
पूर्ण

अटल पूर्णांक exynos7_ufs_post_pwr_change(काष्ठा exynos_ufs *ufs,
						काष्ठा ufs_pa_layer_attr *pwr)
अणु
	काष्ठा ufs_hba *hba = ufs->hba;
	पूर्णांक lanes = max_t(u32, pwr->lane_rx, pwr->lane_tx);

	ufshcd_dme_set(hba, UIC_ARG_MIB(PA_DBG_RXPHY_CFGUPDT), 0x1);

	अगर (lanes == 1) अणु
		exynos_ufs_enable_dbg_mode(hba);
		ufshcd_dme_set(hba, UIC_ARG_MIB(PA_CONNECTEDTXDATALANES), 0x1);
		exynos_ufs_disable_dbg_mode(hba);
	पूर्ण

	वापस 0;
पूर्ण

/*
 * exynos_ufs_स्वतः_ctrl_hcc - HCI core घड़ी control by h/w
 * Control should be disabled in the below हालs
 * - Beक्रमe host controller S/W reset
 * - Access to UFS protector's रेजिस्टर
 */
अटल व्योम exynos_ufs_स्वतः_ctrl_hcc(काष्ठा exynos_ufs *ufs, bool en)
अणु
	u32 misc = hci_पढ़ोl(ufs, HCI_MISC);

	अगर (en)
		hci_ग_लिखोl(ufs, misc | HCI_CORECLK_CTRL_EN, HCI_MISC);
	अन्यथा
		hci_ग_लिखोl(ufs, misc & ~HCI_CORECLK_CTRL_EN, HCI_MISC);
पूर्ण

अटल व्योम exynos_ufs_ctrl_clkstop(काष्ठा exynos_ufs *ufs, bool en)
अणु
	u32 ctrl = hci_पढ़ोl(ufs, HCI_CLKSTOP_CTRL);
	u32 misc = hci_पढ़ोl(ufs, HCI_MISC);

	अगर (en) अणु
		hci_ग_लिखोl(ufs, misc | CLK_CTRL_EN_MASK, HCI_MISC);
		hci_ग_लिखोl(ufs, ctrl | CLK_STOP_MASK, HCI_CLKSTOP_CTRL);
	पूर्ण अन्यथा अणु
		hci_ग_लिखोl(ufs, ctrl & ~CLK_STOP_MASK, HCI_CLKSTOP_CTRL);
		hci_ग_लिखोl(ufs, misc & ~CLK_CTRL_EN_MASK, HCI_MISC);
	पूर्ण
पूर्ण

अटल पूर्णांक exynos_ufs_get_clk_info(काष्ठा exynos_ufs *ufs)
अणु
	काष्ठा ufs_hba *hba = ufs->hba;
	काष्ठा list_head *head = &hba->clk_list_head;
	काष्ठा ufs_clk_info *clki;
	u32 pclk_rate;
	u32 f_min, f_max;
	u8 भाग = 0;
	पूर्णांक ret = 0;

	अगर (list_empty(head))
		जाओ out;

	list_क्रम_each_entry(clki, head, list) अणु
		अगर (!IS_ERR(clki->clk)) अणु
			अगर (!म_भेद(clki->name, "core_clk"))
				ufs->clk_hci_core = clki->clk;
			अन्यथा अगर (!म_भेद(clki->name, "sclk_unipro_main"))
				ufs->clk_unipro_मुख्य = clki->clk;
		पूर्ण
	पूर्ण

	अगर (!ufs->clk_hci_core || !ufs->clk_unipro_मुख्य) अणु
		dev_err(hba->dev, "failed to get clk info\n");
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	ufs->mclk_rate = clk_get_rate(ufs->clk_unipro_मुख्य);
	pclk_rate = clk_get_rate(ufs->clk_hci_core);
	f_min = ufs->pclk_avail_min;
	f_max = ufs->pclk_avail_max;

	अगर (ufs->opts & EXYNOS_UFS_OPT_HAS_APB_CLK_CTRL) अणु
		करो अणु
			pclk_rate /= (भाग + 1);

			अगर (pclk_rate <= f_max)
				अवरोध;
			भाग++;
		पूर्ण जबतक (pclk_rate >= f_min);
	पूर्ण

	अगर (unlikely(pclk_rate < f_min || pclk_rate > f_max)) अणु
		dev_err(hba->dev, "not available pclk range %d\n", pclk_rate);
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	ufs->pclk_rate = pclk_rate;
	ufs->pclk_भाग = भाग;

out:
	वापस ret;
पूर्ण

अटल व्योम exynos_ufs_set_unipro_pclk_भाग(काष्ठा exynos_ufs *ufs)
अणु
	अगर (ufs->opts & EXYNOS_UFS_OPT_HAS_APB_CLK_CTRL) अणु
		u32 val;

		val = hci_पढ़ोl(ufs, HCI_UNIPRO_APB_CLK_CTRL);
		hci_ग_लिखोl(ufs, UNIPRO_APB_CLK(val, ufs->pclk_भाग),
			   HCI_UNIPRO_APB_CLK_CTRL);
	पूर्ण
पूर्ण

अटल व्योम exynos_ufs_set_pwm_clk_भाग(काष्ठा exynos_ufs *ufs)
अणु
	काष्ठा ufs_hba *hba = ufs->hba;
	काष्ठा exynos_ufs_uic_attr *attr = ufs->drv_data->uic_attr;

	ufshcd_dme_set(hba,
		UIC_ARG_MIB(CMN_PWM_CLK_CTRL), attr->cmn_pwm_clk_ctrl);
पूर्ण

अटल व्योम exynos_ufs_calc_pwm_clk_भाग(काष्ठा exynos_ufs *ufs)
अणु
	काष्ठा ufs_hba *hba = ufs->hba;
	काष्ठा exynos_ufs_uic_attr *attr = ufs->drv_data->uic_attr;
	स्थिर अचिन्हित पूर्णांक भाग = 30, mult = 20;
	स्थिर अचिन्हित दीर्घ pwm_min = 3 * 1000 * 1000;
	स्थिर अचिन्हित दीर्घ pwm_max = 9 * 1000 * 1000;
	स्थिर पूर्णांक भागs[] = अणु32, 16, 8, 4पूर्ण;
	अचिन्हित दीर्घ clk = 0, _clk, clk_period;
	पूर्णांक i = 0, clk_idx = -1;

	clk_period = UNIPRO_PCLK_PERIOD(ufs);
	क्रम (i = 0; i < ARRAY_SIZE(भागs); i++) अणु
		_clk = NSEC_PER_SEC * mult / (clk_period * भागs[i] * भाग);
		अगर (_clk >= pwm_min && _clk <= pwm_max) अणु
			अगर (_clk > clk) अणु
				clk_idx = i;
				clk = _clk;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (clk_idx == -1) अणु
		ufshcd_dme_get(hba, UIC_ARG_MIB(CMN_PWM_CLK_CTRL), &clk_idx);
		dev_err(hba->dev,
			"failed to decide pwm clock divider, will not change\n");
	पूर्ण

	attr->cmn_pwm_clk_ctrl = clk_idx & PWM_CLK_CTRL_MASK;
पूर्ण

दीर्घ exynos_ufs_calc_समय_cntr(काष्ठा exynos_ufs *ufs, दीर्घ period)
अणु
	स्थिर पूर्णांक precise = 10;
	दीर्घ pclk_rate = ufs->pclk_rate;
	दीर्घ clk_period, fraction;

	clk_period = UNIPRO_PCLK_PERIOD(ufs);
	fraction = ((NSEC_PER_SEC % pclk_rate) * precise) / pclk_rate;

	वापस (period * precise) / ((clk_period * precise) + fraction);
पूर्ण

अटल व्योम exynos_ufs_specअगरy_phy_समय_attr(काष्ठा exynos_ufs *ufs)
अणु
	काष्ठा exynos_ufs_uic_attr *attr = ufs->drv_data->uic_attr;
	काष्ठा ufs_phy_समय_cfg *t_cfg = &ufs->t_cfg;

	t_cfg->tx_linereset_p =
		exynos_ufs_calc_समय_cntr(ufs, attr->tx_dअगर_p_nsec);
	t_cfg->tx_linereset_n =
		exynos_ufs_calc_समय_cntr(ufs, attr->tx_dअगर_n_nsec);
	t_cfg->tx_high_z_cnt =
		exynos_ufs_calc_समय_cntr(ufs, attr->tx_high_z_cnt_nsec);
	t_cfg->tx_base_n_val =
		exynos_ufs_calc_समय_cntr(ufs, attr->tx_base_unit_nsec);
	t_cfg->tx_gran_n_val =
		exynos_ufs_calc_समय_cntr(ufs, attr->tx_gran_unit_nsec);
	t_cfg->tx_sleep_cnt =
		exynos_ufs_calc_समय_cntr(ufs, attr->tx_sleep_cnt);

	t_cfg->rx_linereset =
		exynos_ufs_calc_समय_cntr(ufs, attr->rx_dअगर_p_nsec);
	t_cfg->rx_hibern8_रुको =
		exynos_ufs_calc_समय_cntr(ufs, attr->rx_hibern8_रुको_nsec);
	t_cfg->rx_base_n_val =
		exynos_ufs_calc_समय_cntr(ufs, attr->rx_base_unit_nsec);
	t_cfg->rx_gran_n_val =
		exynos_ufs_calc_समय_cntr(ufs, attr->rx_gran_unit_nsec);
	t_cfg->rx_sleep_cnt =
		exynos_ufs_calc_समय_cntr(ufs, attr->rx_sleep_cnt);
	t_cfg->rx_stall_cnt =
		exynos_ufs_calc_समय_cntr(ufs, attr->rx_stall_cnt);
पूर्ण

अटल व्योम exynos_ufs_config_phy_समय_attr(काष्ठा exynos_ufs *ufs)
अणु
	काष्ठा ufs_hba *hba = ufs->hba;
	काष्ठा ufs_phy_समय_cfg *t_cfg = &ufs->t_cfg;
	पूर्णांक i;

	exynos_ufs_set_pwm_clk_भाग(ufs);

	exynos_ufs_enable_ov_पंचांग(hba);

	क्रम_each_ufs_rx_lane(ufs, i) अणु
		ufshcd_dme_set(hba, UIC_ARG_MIB_SEL(RX_FILLER_ENABLE, i),
				ufs->drv_data->uic_attr->rx_filler_enable);
		ufshcd_dme_set(hba, UIC_ARG_MIB_SEL(RX_LINERESET_VAL, i),
				RX_LINERESET(t_cfg->rx_linereset));
		ufshcd_dme_set(hba, UIC_ARG_MIB_SEL(RX_BASE_NVAL_07_00, i),
				RX_BASE_NVAL_L(t_cfg->rx_base_n_val));
		ufshcd_dme_set(hba, UIC_ARG_MIB_SEL(RX_BASE_NVAL_15_08, i),
				RX_BASE_NVAL_H(t_cfg->rx_base_n_val));
		ufshcd_dme_set(hba, UIC_ARG_MIB_SEL(RX_GRAN_NVAL_07_00, i),
				RX_GRAN_NVAL_L(t_cfg->rx_gran_n_val));
		ufshcd_dme_set(hba, UIC_ARG_MIB_SEL(RX_GRAN_NVAL_10_08, i),
				RX_GRAN_NVAL_H(t_cfg->rx_gran_n_val));
		ufshcd_dme_set(hba, UIC_ARG_MIB_SEL(RX_OV_SLEEP_CNT_TIMER, i),
				RX_OV_SLEEP_CNT(t_cfg->rx_sleep_cnt));
		ufshcd_dme_set(hba, UIC_ARG_MIB_SEL(RX_OV_STALL_CNT_TIMER, i),
				RX_OV_STALL_CNT(t_cfg->rx_stall_cnt));
	पूर्ण

	क्रम_each_ufs_tx_lane(ufs, i) अणु
		ufshcd_dme_set(hba, UIC_ARG_MIB_SEL(TX_LINERESET_P_VAL, i),
				TX_LINERESET_P(t_cfg->tx_linereset_p));
		ufshcd_dme_set(hba, UIC_ARG_MIB_SEL(TX_HIGH_Z_CNT_07_00, i),
				TX_HIGH_Z_CNT_L(t_cfg->tx_high_z_cnt));
		ufshcd_dme_set(hba, UIC_ARG_MIB_SEL(TX_HIGH_Z_CNT_11_08, i),
				TX_HIGH_Z_CNT_H(t_cfg->tx_high_z_cnt));
		ufshcd_dme_set(hba, UIC_ARG_MIB_SEL(TX_BASE_NVAL_07_00, i),
				TX_BASE_NVAL_L(t_cfg->tx_base_n_val));
		ufshcd_dme_set(hba, UIC_ARG_MIB_SEL(TX_BASE_NVAL_15_08, i),
				TX_BASE_NVAL_H(t_cfg->tx_base_n_val));
		ufshcd_dme_set(hba, UIC_ARG_MIB_SEL(TX_GRAN_NVAL_07_00, i),
				TX_GRAN_NVAL_L(t_cfg->tx_gran_n_val));
		ufshcd_dme_set(hba, UIC_ARG_MIB_SEL(TX_GRAN_NVAL_10_08, i),
				TX_GRAN_NVAL_H(t_cfg->tx_gran_n_val));
		ufshcd_dme_set(hba, UIC_ARG_MIB_SEL(TX_OV_SLEEP_CNT_TIMER, i),
				TX_OV_H8_ENTER_EN |
				TX_OV_SLEEP_CNT(t_cfg->tx_sleep_cnt));
		ufshcd_dme_set(hba, UIC_ARG_MIB_SEL(TX_MIN_ACTIVATETIME, i),
				ufs->drv_data->uic_attr->tx_min_activateसमय);
	पूर्ण

	exynos_ufs_disable_ov_पंचांग(hba);
पूर्ण

अटल व्योम exynos_ufs_config_phy_cap_attr(काष्ठा exynos_ufs *ufs)
अणु
	काष्ठा ufs_hba *hba = ufs->hba;
	काष्ठा exynos_ufs_uic_attr *attr = ufs->drv_data->uic_attr;
	पूर्णांक i;

	exynos_ufs_enable_ov_पंचांग(hba);

	क्रम_each_ufs_rx_lane(ufs, i) अणु
		ufshcd_dme_set(hba,
				UIC_ARG_MIB_SEL(RX_HS_G1_SYNC_LENGTH_CAP, i),
				attr->rx_hs_g1_sync_len_cap);
		ufshcd_dme_set(hba,
				UIC_ARG_MIB_SEL(RX_HS_G2_SYNC_LENGTH_CAP, i),
				attr->rx_hs_g2_sync_len_cap);
		ufshcd_dme_set(hba,
				UIC_ARG_MIB_SEL(RX_HS_G3_SYNC_LENGTH_CAP, i),
				attr->rx_hs_g3_sync_len_cap);
		ufshcd_dme_set(hba,
				UIC_ARG_MIB_SEL(RX_HS_G1_PREP_LENGTH_CAP, i),
				attr->rx_hs_g1_prep_sync_len_cap);
		ufshcd_dme_set(hba,
				UIC_ARG_MIB_SEL(RX_HS_G2_PREP_LENGTH_CAP, i),
				attr->rx_hs_g2_prep_sync_len_cap);
		ufshcd_dme_set(hba,
				UIC_ARG_MIB_SEL(RX_HS_G3_PREP_LENGTH_CAP, i),
				attr->rx_hs_g3_prep_sync_len_cap);
	पूर्ण

	अगर (attr->rx_adv_fine_gran_sup_en == 0) अणु
		क्रम_each_ufs_rx_lane(ufs, i) अणु
			ufshcd_dme_set(hba,
				UIC_ARG_MIB_SEL(RX_ADV_GRANULARITY_CAP, i), 0);

			अगर (attr->rx_min_actv_समय_cap)
				ufshcd_dme_set(hba,
					UIC_ARG_MIB_SEL(RX_MIN_ACTIVATETIME_CAP,
						i), attr->rx_min_actv_समय_cap);

			अगर (attr->rx_hibern8_समय_cap)
				ufshcd_dme_set(hba,
					UIC_ARG_MIB_SEL(RX_HIBERN8TIME_CAP, i),
						attr->rx_hibern8_समय_cap);
		पूर्ण
	पूर्ण अन्यथा अगर (attr->rx_adv_fine_gran_sup_en == 1) अणु
		क्रम_each_ufs_rx_lane(ufs, i) अणु
			अगर (attr->rx_adv_fine_gran_step)
				ufshcd_dme_set(hba,
					UIC_ARG_MIB_SEL(RX_ADV_GRANULARITY_CAP,
						i), RX_ADV_FINE_GRAN_STEP(
						attr->rx_adv_fine_gran_step));

			अगर (attr->rx_adv_min_actv_समय_cap)
				ufshcd_dme_set(hba,
					UIC_ARG_MIB_SEL(
						RX_ADV_MIN_ACTIVATETIME_CAP, i),
						attr->rx_adv_min_actv_समय_cap);

			अगर (attr->rx_adv_hibern8_समय_cap)
				ufshcd_dme_set(hba,
					UIC_ARG_MIB_SEL(RX_ADV_HIBERN8TIME_CAP,
						i),
						attr->rx_adv_hibern8_समय_cap);
		पूर्ण
	पूर्ण

	exynos_ufs_disable_ov_पंचांग(hba);
पूर्ण

अटल व्योम exynos_ufs_establish_connt(काष्ठा exynos_ufs *ufs)
अणु
	काष्ठा ufs_hba *hba = ufs->hba;
	क्रमागत अणु
		DEV_ID		= 0x00,
		PEER_DEV_ID	= 0x01,
		PEER_CPORT_ID	= 0x00,
		TRAFFIC_CLASS	= 0x00,
	पूर्ण;

	/* allow cport attributes to be set */
	ufshcd_dme_set(hba, UIC_ARG_MIB(T_CONNECTIONSTATE), CPORT_IDLE);

	/* local unipro attributes */
	ufshcd_dme_set(hba, UIC_ARG_MIB(N_DEVICEID), DEV_ID);
	ufshcd_dme_set(hba, UIC_ARG_MIB(N_DEVICEID_VALID), TRUE);
	ufshcd_dme_set(hba, UIC_ARG_MIB(T_PEERDEVICEID), PEER_DEV_ID);
	ufshcd_dme_set(hba, UIC_ARG_MIB(T_PEERCPORTID), PEER_CPORT_ID);
	ufshcd_dme_set(hba, UIC_ARG_MIB(T_CPORTFLAGS), CPORT_DEF_FLAGS);
	ufshcd_dme_set(hba, UIC_ARG_MIB(T_TRAFFICCLASS), TRAFFIC_CLASS);
	ufshcd_dme_set(hba, UIC_ARG_MIB(T_CONNECTIONSTATE), CPORT_CONNECTED);
पूर्ण

अटल व्योम exynos_ufs_config_smu(काष्ठा exynos_ufs *ufs)
अणु
	u32 reg, val;

	exynos_ufs_disable_स्वतः_ctrl_hcc_save(ufs, &val);

	/* make encryption disabled by शेष */
	reg = ufsp_पढ़ोl(ufs, UFSPRSECURITY);
	ufsp_ग_लिखोl(ufs, reg | NSSMU, UFSPRSECURITY);
	ufsp_ग_लिखोl(ufs, 0x0, UFSPSBEGIN0);
	ufsp_ग_लिखोl(ufs, 0xffffffff, UFSPSEND0);
	ufsp_ग_लिखोl(ufs, 0xff, UFSPSLUN0);
	ufsp_ग_लिखोl(ufs, 0xf1, UFSPSCTRL0);

	exynos_ufs_स्वतः_ctrl_hcc_restore(ufs, &val);
पूर्ण

अटल व्योम exynos_ufs_config_sync_pattern_mask(काष्ठा exynos_ufs *ufs,
					काष्ठा ufs_pa_layer_attr *pwr)
अणु
	काष्ठा ufs_hba *hba = ufs->hba;
	u8 g = max_t(u32, pwr->gear_rx, pwr->gear_tx);
	u32 mask, sync_len;
	क्रमागत अणु
		SYNC_LEN_G1 = 80 * 1000, /* 80us */
		SYNC_LEN_G2 = 40 * 1000, /* 44us */
		SYNC_LEN_G3 = 20 * 1000, /* 20us */
	पूर्ण;
	पूर्णांक i;

	अगर (g == 1)
		sync_len = SYNC_LEN_G1;
	अन्यथा अगर (g == 2)
		sync_len = SYNC_LEN_G2;
	अन्यथा अगर (g == 3)
		sync_len = SYNC_LEN_G3;
	अन्यथा
		वापस;

	mask = exynos_ufs_calc_समय_cntr(ufs, sync_len);
	mask = (mask >> 8) & 0xff;

	exynos_ufs_enable_ov_पंचांग(hba);

	क्रम_each_ufs_rx_lane(ufs, i)
		ufshcd_dme_set(hba,
			UIC_ARG_MIB_SEL(RX_SYNC_MASK_LENGTH, i), mask);

	exynos_ufs_disable_ov_पंचांग(hba);
पूर्ण

अटल पूर्णांक exynos_ufs_pre_pwr_mode(काष्ठा ufs_hba *hba,
				काष्ठा ufs_pa_layer_attr *dev_max_params,
				काष्ठा ufs_pa_layer_attr *dev_req_params)
अणु
	काष्ठा exynos_ufs *ufs = ufshcd_get_variant(hba);
	काष्ठा phy *generic_phy = ufs->phy;
	काष्ठा ufs_dev_params ufs_exynos_cap;
	पूर्णांक ret;

	अगर (!dev_req_params) अणु
		pr_err("%s: incoming dev_req_params is NULL\n", __func__);
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	ufshcd_init_pwr_dev_param(&ufs_exynos_cap);

	ret = ufshcd_get_pwr_dev_param(&ufs_exynos_cap,
				       dev_max_params, dev_req_params);
	अगर (ret) अणु
		pr_err("%s: failed to determine capabilities\n", __func__);
		जाओ out;
	पूर्ण

	अगर (ufs->drv_data->pre_pwr_change)
		ufs->drv_data->pre_pwr_change(ufs, dev_req_params);

	अगर (ufshcd_is_hs_mode(dev_req_params)) अणु
		exynos_ufs_config_sync_pattern_mask(ufs, dev_req_params);

		चयन (dev_req_params->hs_rate) अणु
		हाल PA_HS_MODE_A:
		हाल PA_HS_MODE_B:
			phy_calibrate(generic_phy);
			अवरोध;
		पूर्ण
	पूर्ण

	/* setting क्रम three समयout values क्रम traffic class #0 */
	ufshcd_dme_set(hba, UIC_ARG_MIB(PA_PWRMODEUSERDATA0), 8064);
	ufshcd_dme_set(hba, UIC_ARG_MIB(PA_PWRMODEUSERDATA1), 28224);
	ufshcd_dme_set(hba, UIC_ARG_MIB(PA_PWRMODEUSERDATA2), 20160);

	वापस 0;
out:
	वापस ret;
पूर्ण

#घोषणा PWR_MODE_STR_LEN	64
अटल पूर्णांक exynos_ufs_post_pwr_mode(काष्ठा ufs_hba *hba,
				काष्ठा ufs_pa_layer_attr *pwr_req)
अणु
	काष्ठा exynos_ufs *ufs = ufshcd_get_variant(hba);
	काष्ठा phy *generic_phy = ufs->phy;
	पूर्णांक gear = max_t(u32, pwr_req->gear_rx, pwr_req->gear_tx);
	पूर्णांक lanes = max_t(u32, pwr_req->lane_rx, pwr_req->lane_tx);
	अक्षर pwr_str[PWR_MODE_STR_LEN] = "";

	/* let शेष be PWM Gear 1, Lane 1 */
	अगर (!gear)
		gear = 1;

	अगर (!lanes)
		lanes = 1;

	अगर (ufs->drv_data->post_pwr_change)
		ufs->drv_data->post_pwr_change(ufs, pwr_req);

	अगर ((ufshcd_is_hs_mode(pwr_req))) अणु
		चयन (pwr_req->hs_rate) अणु
		हाल PA_HS_MODE_A:
		हाल PA_HS_MODE_B:
			phy_calibrate(generic_phy);
			अवरोध;
		पूर्ण

		snम_लिखो(pwr_str, PWR_MODE_STR_LEN, "%s series_%s G_%d L_%d",
			"FAST",	pwr_req->hs_rate == PA_HS_MODE_A ? "A" : "B",
			gear, lanes);
	पूर्ण अन्यथा अणु
		snम_लिखो(pwr_str, PWR_MODE_STR_LEN, "%s G_%d L_%d",
			"SLOW", gear, lanes);
	पूर्ण

	dev_info(hba->dev, "Power mode changed to : %s\n", pwr_str);

	वापस 0;
पूर्ण

अटल व्योम exynos_ufs_specअगरy_nexus_t_xfer_req(काष्ठा ufs_hba *hba,
						पूर्णांक tag, bool op)
अणु
	काष्ठा exynos_ufs *ufs = ufshcd_get_variant(hba);
	u32 type;

	type =  hci_पढ़ोl(ufs, HCI_UTRL_NEXUS_TYPE);

	अगर (op)
		hci_ग_लिखोl(ufs, type | (1 << tag), HCI_UTRL_NEXUS_TYPE);
	अन्यथा
		hci_ग_लिखोl(ufs, type & ~(1 << tag), HCI_UTRL_NEXUS_TYPE);
पूर्ण

अटल व्योम exynos_ufs_specअगरy_nexus_t_पंचांग_req(काष्ठा ufs_hba *hba,
						पूर्णांक tag, u8 func)
अणु
	काष्ठा exynos_ufs *ufs = ufshcd_get_variant(hba);
	u32 type;

	type =  hci_पढ़ोl(ufs, HCI_UTMRL_NEXUS_TYPE);

	चयन (func) अणु
	हाल UFS_ABORT_TASK:
	हाल UFS_QUERY_TASK:
		hci_ग_लिखोl(ufs, type | (1 << tag), HCI_UTMRL_NEXUS_TYPE);
		अवरोध;
	हाल UFS_ABORT_TASK_SET:
	हाल UFS_CLEAR_TASK_SET:
	हाल UFS_LOGICAL_RESET:
	हाल UFS_QUERY_TASK_SET:
		hci_ग_लिखोl(ufs, type & ~(1 << tag), HCI_UTMRL_NEXUS_TYPE);
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक exynos_ufs_phy_init(काष्ठा exynos_ufs *ufs)
अणु
	काष्ठा ufs_hba *hba = ufs->hba;
	काष्ठा phy *generic_phy = ufs->phy;
	पूर्णांक ret = 0;

	अगर (ufs->avail_ln_rx == 0 || ufs->avail_ln_tx == 0) अणु
		ufshcd_dme_get(hba, UIC_ARG_MIB(PA_AVAILRXDATALANES),
			&ufs->avail_ln_rx);
		ufshcd_dme_get(hba, UIC_ARG_MIB(PA_AVAILTXDATALANES),
			&ufs->avail_ln_tx);
		WARN(ufs->avail_ln_rx != ufs->avail_ln_tx,
			"available data lane is not equal(rx:%d, tx:%d)\n",
			ufs->avail_ln_rx, ufs->avail_ln_tx);
	पूर्ण

	phy_set_bus_width(generic_phy, ufs->avail_ln_rx);
	ret = phy_init(generic_phy);
	अगर (ret) अणु
		dev_err(hba->dev, "%s: phy init failed, ret = %d\n",
			__func__, ret);
		जाओ out_निकास_phy;
	पूर्ण

	वापस 0;

out_निकास_phy:
	phy_निकास(generic_phy);

	वापस ret;
पूर्ण

अटल व्योम exynos_ufs_config_unipro(काष्ठा exynos_ufs *ufs)
अणु
	काष्ठा ufs_hba *hba = ufs->hba;

	ufshcd_dme_set(hba, UIC_ARG_MIB(PA_DBG_CLK_PERIOD),
		DIV_ROUND_UP(NSEC_PER_SEC, ufs->mclk_rate));
	ufshcd_dme_set(hba, UIC_ARG_MIB(PA_TXTRAILINGCLOCKS),
			ufs->drv_data->uic_attr->tx_trailingclks);
	ufshcd_dme_set(hba, UIC_ARG_MIB(PA_DBG_OPTION_SUITE),
			ufs->drv_data->uic_attr->pa_dbg_option_suite);
पूर्ण

अटल व्योम exynos_ufs_config_पूर्णांकr(काष्ठा exynos_ufs *ufs, u32 errs, u8 index)
अणु
	चयन (index) अणु
	हाल UNIPRO_L1_5:
		hci_ग_लिखोl(ufs, DFES_ERR_EN | errs, HCI_ERR_EN_PA_LAYER);
		अवरोध;
	हाल UNIPRO_L2:
		hci_ग_लिखोl(ufs, DFES_ERR_EN | errs, HCI_ERR_EN_DL_LAYER);
		अवरोध;
	हाल UNIPRO_L3:
		hci_ग_लिखोl(ufs, DFES_ERR_EN | errs, HCI_ERR_EN_N_LAYER);
		अवरोध;
	हाल UNIPRO_L4:
		hci_ग_लिखोl(ufs, DFES_ERR_EN | errs, HCI_ERR_EN_T_LAYER);
		अवरोध;
	हाल UNIPRO_DME:
		hci_ग_लिखोl(ufs, DFES_ERR_EN | errs, HCI_ERR_EN_DME_LAYER);
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक exynos_ufs_pre_link(काष्ठा ufs_hba *hba)
अणु
	काष्ठा exynos_ufs *ufs = ufshcd_get_variant(hba);

	/* hci */
	exynos_ufs_config_पूर्णांकr(ufs, DFES_DEF_L2_ERRS, UNIPRO_L2);
	exynos_ufs_config_पूर्णांकr(ufs, DFES_DEF_L3_ERRS, UNIPRO_L3);
	exynos_ufs_config_पूर्णांकr(ufs, DFES_DEF_L4_ERRS, UNIPRO_L4);
	exynos_ufs_set_unipro_pclk_भाग(ufs);

	/* unipro */
	exynos_ufs_config_unipro(ufs);

	/* m-phy */
	exynos_ufs_phy_init(ufs);
	exynos_ufs_config_phy_समय_attr(ufs);
	exynos_ufs_config_phy_cap_attr(ufs);

	अगर (ufs->drv_data->pre_link)
		ufs->drv_data->pre_link(ufs);

	वापस 0;
पूर्ण

अटल व्योम exynos_ufs_fit_aggr_समयout(काष्ठा exynos_ufs *ufs)
अणु
	u32 val;

	val = exynos_ufs_calc_समय_cntr(ufs, IATOVAL_NSEC / CNTR_DIV_VAL);
	hci_ग_लिखोl(ufs, val & CNT_VAL_1US_MASK, HCI_1US_TO_CNT_VAL);
पूर्ण

अटल पूर्णांक exynos_ufs_post_link(काष्ठा ufs_hba *hba)
अणु
	काष्ठा exynos_ufs *ufs = ufshcd_get_variant(hba);
	काष्ठा phy *generic_phy = ufs->phy;
	काष्ठा exynos_ufs_uic_attr *attr = ufs->drv_data->uic_attr;

	exynos_ufs_establish_connt(ufs);
	exynos_ufs_fit_aggr_समयout(ufs);

	hci_ग_लिखोl(ufs, 0xa, HCI_DATA_REORDER);
	hci_ग_लिखोl(ufs, PRDT_SET_SIZE(12), HCI_TXPRDT_ENTRY_SIZE);
	hci_ग_लिखोl(ufs, PRDT_SET_SIZE(12), HCI_RXPRDT_ENTRY_SIZE);
	hci_ग_लिखोl(ufs, (1 << hba->nutrs) - 1, HCI_UTRL_NEXUS_TYPE);
	hci_ग_लिखोl(ufs, (1 << hba->nuपंचांगrs) - 1, HCI_UTMRL_NEXUS_TYPE);
	hci_ग_लिखोl(ufs, 0xf, HCI_AXIDMA_RWDATA_BURST_LEN);

	अगर (ufs->opts & EXYNOS_UFS_OPT_SKIP_CONNECTION_ESTAB)
		ufshcd_dme_set(hba,
			UIC_ARG_MIB(T_DBG_SKIP_INIT_HIBERN8_EXIT), TRUE);

	अगर (attr->pa_granularity) अणु
		exynos_ufs_enable_dbg_mode(hba);
		ufshcd_dme_set(hba, UIC_ARG_MIB(PA_GRANULARITY),
				attr->pa_granularity);
		exynos_ufs_disable_dbg_mode(hba);

		अगर (attr->pa_tactivate)
			ufshcd_dme_set(hba, UIC_ARG_MIB(PA_TACTIVATE),
					attr->pa_tactivate);
		अगर (attr->pa_hibern8समय &&
		    !(ufs->opts & EXYNOS_UFS_OPT_USE_SW_HIBERN8_TIMER))
			ufshcd_dme_set(hba, UIC_ARG_MIB(PA_HIBERN8TIME),
					attr->pa_hibern8समय);
	पूर्ण

	अगर (ufs->opts & EXYNOS_UFS_OPT_USE_SW_HIBERN8_TIMER) अणु
		अगर (!attr->pa_granularity)
			ufshcd_dme_get(hba, UIC_ARG_MIB(PA_GRANULARITY),
					&attr->pa_granularity);
		अगर (!attr->pa_hibern8समय)
			ufshcd_dme_get(hba, UIC_ARG_MIB(PA_HIBERN8TIME),
					&attr->pa_hibern8समय);
		/*
		 * not रुको क्रम HIBERN8 समय to निकास hibernation
		 */
		ufshcd_dme_set(hba, UIC_ARG_MIB(PA_HIBERN8TIME), 0);

		अगर (attr->pa_granularity < 1 || attr->pa_granularity > 6) अणु
			/* Valid range क्रम granularity: 1 ~ 6 */
			dev_warn(hba->dev,
				"%s: pa_granularity %d is invalid, assuming backwards compatibility\n",
				__func__,
				attr->pa_granularity);
			attr->pa_granularity = 6;
		पूर्ण
	पूर्ण

	phy_calibrate(generic_phy);

	अगर (ufs->drv_data->post_link)
		ufs->drv_data->post_link(ufs);

	वापस 0;
पूर्ण

अटल पूर्णांक exynos_ufs_parse_dt(काष्ठा device *dev, काष्ठा exynos_ufs *ufs)
अणु
	काष्ठा device_node *np = dev->of_node;
	काष्ठा exynos_ufs_drv_data *drv_data = &exynos_ufs_drvs;
	काष्ठा exynos_ufs_uic_attr *attr;
	पूर्णांक ret = 0;

	जबतक (drv_data->compatible) अणु
		अगर (of_device_is_compatible(np, drv_data->compatible)) अणु
			ufs->drv_data = drv_data;
			अवरोध;
		पूर्ण
		drv_data++;
	पूर्ण

	अगर (ufs->drv_data && ufs->drv_data->uic_attr) अणु
		attr = ufs->drv_data->uic_attr;
	पूर्ण अन्यथा अणु
		dev_err(dev, "failed to get uic attributes\n");
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	ufs->pclk_avail_min = PCLK_AVAIL_MIN;
	ufs->pclk_avail_max = PCLK_AVAIL_MAX;

	attr->rx_adv_fine_gran_sup_en = RX_ADV_FINE_GRAN_SUP_EN;
	attr->rx_adv_fine_gran_step = RX_ADV_FINE_GRAN_STEP_VAL;
	attr->rx_adv_min_actv_समय_cap = RX_ADV_MIN_ACTV_TIME_CAP;
	attr->pa_granularity = PA_GRANULARITY_VAL;
	attr->pa_tactivate = PA_TACTIVATE_VAL;
	attr->pa_hibern8समय = PA_HIBERN8TIME_VAL;

out:
	वापस ret;
पूर्ण

अटल पूर्णांक exynos_ufs_init(काष्ठा ufs_hba *hba)
अणु
	काष्ठा device *dev = hba->dev;
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);
	काष्ठा exynos_ufs *ufs;
	पूर्णांक ret;

	ufs = devm_kzalloc(dev, माप(*ufs), GFP_KERNEL);
	अगर (!ufs)
		वापस -ENOMEM;

	/* exynos-specअगरic hci */
	ufs->reg_hci = devm_platक्रमm_ioremap_resource_byname(pdev, "vs_hci");
	अगर (IS_ERR(ufs->reg_hci)) अणु
		dev_err(dev, "cannot ioremap for hci vendor register\n");
		वापस PTR_ERR(ufs->reg_hci);
	पूर्ण

	/* unipro */
	ufs->reg_unipro = devm_platक्रमm_ioremap_resource_byname(pdev, "unipro");
	अगर (IS_ERR(ufs->reg_unipro)) अणु
		dev_err(dev, "cannot ioremap for unipro register\n");
		वापस PTR_ERR(ufs->reg_unipro);
	पूर्ण

	/* ufs protector */
	ufs->reg_ufsp = devm_platक्रमm_ioremap_resource_byname(pdev, "ufsp");
	अगर (IS_ERR(ufs->reg_ufsp)) अणु
		dev_err(dev, "cannot ioremap for ufs protector register\n");
		वापस PTR_ERR(ufs->reg_ufsp);
	पूर्ण

	ret = exynos_ufs_parse_dt(dev, ufs);
	अगर (ret) अणु
		dev_err(dev, "failed to get dt info.\n");
		जाओ out;
	पूर्ण

	ufs->phy = devm_phy_get(dev, "ufs-phy");
	अगर (IS_ERR(ufs->phy)) अणु
		ret = PTR_ERR(ufs->phy);
		dev_err(dev, "failed to get ufs-phy\n");
		जाओ out;
	पूर्ण

	ret = phy_घातer_on(ufs->phy);
	अगर (ret)
		जाओ phy_off;

	ufs->hba = hba;
	ufs->opts = ufs->drv_data->opts;
	ufs->rx_sel_idx = PA_MAXDATALANES;
	अगर (ufs->opts & EXYNOS_UFS_OPT_BROKEN_RX_SEL_IDX)
		ufs->rx_sel_idx = 0;
	hba->priv = (व्योम *)ufs;
	hba->quirks = ufs->drv_data->quirks;
	अगर (ufs->drv_data->drv_init) अणु
		ret = ufs->drv_data->drv_init(dev, ufs);
		अगर (ret) अणु
			dev_err(dev, "failed to init drv-data\n");
			जाओ out;
		पूर्ण
	पूर्ण

	ret = exynos_ufs_get_clk_info(ufs);
	अगर (ret)
		जाओ out;
	exynos_ufs_specअगरy_phy_समय_attr(ufs);
	exynos_ufs_config_smu(ufs);
	वापस 0;

phy_off:
	phy_घातer_off(ufs->phy);
out:
	hba->priv = शून्य;
	वापस ret;
पूर्ण

अटल पूर्णांक exynos_ufs_host_reset(काष्ठा ufs_hba *hba)
अणु
	काष्ठा exynos_ufs *ufs = ufshcd_get_variant(hba);
	अचिन्हित दीर्घ समयout = jअगरfies + msecs_to_jअगरfies(1);
	u32 val;
	पूर्णांक ret = 0;

	exynos_ufs_disable_स्वतः_ctrl_hcc_save(ufs, &val);

	hci_ग_लिखोl(ufs, UFS_SW_RST_MASK, HCI_SW_RST);

	करो अणु
		अगर (!(hci_पढ़ोl(ufs, HCI_SW_RST) & UFS_SW_RST_MASK))
			जाओ out;
	पूर्ण जबतक (समय_beक्रमe(jअगरfies, समयout));

	dev_err(hba->dev, "timeout host sw-reset\n");
	ret = -ETIMEDOUT;

out:
	exynos_ufs_स्वतः_ctrl_hcc_restore(ufs, &val);
	वापस ret;
पूर्ण

अटल व्योम exynos_ufs_dev_hw_reset(काष्ठा ufs_hba *hba)
अणु
	काष्ठा exynos_ufs *ufs = ufshcd_get_variant(hba);

	hci_ग_लिखोl(ufs, 0 << 0, HCI_GPIO_OUT);
	udelay(5);
	hci_ग_लिखोl(ufs, 1 << 0, HCI_GPIO_OUT);
पूर्ण

अटल व्योम exynos_ufs_pre_hibern8(काष्ठा ufs_hba *hba, u8 enter)
अणु
	काष्ठा exynos_ufs *ufs = ufshcd_get_variant(hba);
	काष्ठा exynos_ufs_uic_attr *attr = ufs->drv_data->uic_attr;

	अगर (!enter) अणु
		अगर (ufs->opts & EXYNOS_UFS_OPT_BROKEN_AUTO_CLK_CTRL)
			exynos_ufs_disable_स्वतः_ctrl_hcc(ufs);
		exynos_ufs_ungate_clks(ufs);

		अगर (ufs->opts & EXYNOS_UFS_OPT_USE_SW_HIBERN8_TIMER) अणु
			स्थिर अचिन्हित पूर्णांक granularity_tbl[] = अणु
				1, 4, 8, 16, 32, 100
			पूर्ण;
			पूर्णांक h8_समय = attr->pa_hibern8समय *
				granularity_tbl[attr->pa_granularity - 1];
			अचिन्हित दीर्घ us;
			s64 delta;

			करो अणु
				delta = h8_समय - kसमय_us_delta(kसमय_get(),
							ufs->entry_hibern8_t);
				अगर (delta <= 0)
					अवरोध;

				us = min_t(s64, delta, USEC_PER_MSEC);
				अगर (us >= 10)
					usleep_range(us, us + 10);
			पूर्ण जबतक (1);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम exynos_ufs_post_hibern8(काष्ठा ufs_hba *hba, u8 enter)
अणु
	काष्ठा exynos_ufs *ufs = ufshcd_get_variant(hba);

	अगर (!enter) अणु
		u32 cur_mode = 0;
		u32 pwrmode;

		अगर (ufshcd_is_hs_mode(&ufs->dev_req_params))
			pwrmode = FAST_MODE;
		अन्यथा
			pwrmode = SLOW_MODE;

		ufshcd_dme_get(hba, UIC_ARG_MIB(PA_PWRMODE), &cur_mode);
		अगर (cur_mode != (pwrmode << 4 | pwrmode)) अणु
			dev_warn(hba->dev, "%s: power mode change\n", __func__);
			hba->pwr_info.pwr_rx = (cur_mode >> 4) & 0xf;
			hba->pwr_info.pwr_tx = cur_mode & 0xf;
			ufshcd_config_pwr_mode(hba, &hba->max_pwr_info.info);
		पूर्ण

		अगर (!(ufs->opts & EXYNOS_UFS_OPT_SKIP_CONNECTION_ESTAB))
			exynos_ufs_establish_connt(ufs);
	पूर्ण अन्यथा अणु
		ufs->entry_hibern8_t = kसमय_get();
		exynos_ufs_gate_clks(ufs);
		अगर (ufs->opts & EXYNOS_UFS_OPT_BROKEN_AUTO_CLK_CTRL)
			exynos_ufs_enable_स्वतः_ctrl_hcc(ufs);
	पूर्ण
पूर्ण

अटल पूर्णांक exynos_ufs_hce_enable_notअगरy(काष्ठा ufs_hba *hba,
					क्रमागत ufs_notअगरy_change_status status)
अणु
	काष्ठा exynos_ufs *ufs = ufshcd_get_variant(hba);
	पूर्णांक ret = 0;

	चयन (status) अणु
	हाल PRE_CHANGE:
		ret = exynos_ufs_host_reset(hba);
		अगर (ret)
			वापस ret;
		exynos_ufs_dev_hw_reset(hba);
		अवरोध;
	हाल POST_CHANGE:
		exynos_ufs_calc_pwm_clk_भाग(ufs);
		अगर (!(ufs->opts & EXYNOS_UFS_OPT_BROKEN_AUTO_CLK_CTRL))
			exynos_ufs_enable_स्वतः_ctrl_hcc(ufs);
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक exynos_ufs_link_startup_notअगरy(काष्ठा ufs_hba *hba,
					  क्रमागत ufs_notअगरy_change_status status)
अणु
	पूर्णांक ret = 0;

	चयन (status) अणु
	हाल PRE_CHANGE:
		ret = exynos_ufs_pre_link(hba);
		अवरोध;
	हाल POST_CHANGE:
		ret = exynos_ufs_post_link(hba);
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक exynos_ufs_pwr_change_notअगरy(काष्ठा ufs_hba *hba,
				क्रमागत ufs_notअगरy_change_status status,
				काष्ठा ufs_pa_layer_attr *dev_max_params,
				काष्ठा ufs_pa_layer_attr *dev_req_params)
अणु
	पूर्णांक ret = 0;

	चयन (status) अणु
	हाल PRE_CHANGE:
		ret = exynos_ufs_pre_pwr_mode(hba, dev_max_params,
					      dev_req_params);
		अवरोध;
	हाल POST_CHANGE:
		ret = exynos_ufs_post_pwr_mode(hba, dev_req_params);
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम exynos_ufs_hibern8_notअगरy(काष्ठा ufs_hba *hba,
				     क्रमागत uic_cmd_dme enter,
				     क्रमागत ufs_notअगरy_change_status notअगरy)
अणु
	चयन ((u8)notअगरy) अणु
	हाल PRE_CHANGE:
		exynos_ufs_pre_hibern8(hba, enter);
		अवरोध;
	हाल POST_CHANGE:
		exynos_ufs_post_hibern8(hba, enter);
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक exynos_ufs_suspend(काष्ठा ufs_hba *hba, क्रमागत ufs_pm_op pm_op)
अणु
	काष्ठा exynos_ufs *ufs = ufshcd_get_variant(hba);

	अगर (!ufshcd_is_link_active(hba))
		phy_घातer_off(ufs->phy);

	वापस 0;
पूर्ण

अटल पूर्णांक exynos_ufs_resume(काष्ठा ufs_hba *hba, क्रमागत ufs_pm_op pm_op)
अणु
	काष्ठा exynos_ufs *ufs = ufshcd_get_variant(hba);

	अगर (!ufshcd_is_link_active(hba))
		phy_घातer_on(ufs->phy);

	exynos_ufs_config_smu(ufs);

	वापस 0;
पूर्ण

अटल काष्ठा ufs_hba_variant_ops ufs_hba_exynos_ops = अणु
	.name				= "exynos_ufs",
	.init				= exynos_ufs_init,
	.hce_enable_notअगरy		= exynos_ufs_hce_enable_notअगरy,
	.link_startup_notअगरy		= exynos_ufs_link_startup_notअगरy,
	.pwr_change_notअगरy		= exynos_ufs_pwr_change_notअगरy,
	.setup_xfer_req			= exynos_ufs_specअगरy_nexus_t_xfer_req,
	.setup_task_mgmt		= exynos_ufs_specअगरy_nexus_t_पंचांग_req,
	.hibern8_notअगरy			= exynos_ufs_hibern8_notअगरy,
	.suspend			= exynos_ufs_suspend,
	.resume				= exynos_ufs_resume,
पूर्ण;

अटल पूर्णांक exynos_ufs_probe(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक err;
	काष्ठा device *dev = &pdev->dev;

	err = ufshcd_pltfrm_init(pdev, &ufs_hba_exynos_ops);
	अगर (err)
		dev_err(dev, "ufshcd_pltfrm_init() failed %d\n", err);

	वापस err;
पूर्ण

अटल पूर्णांक exynos_ufs_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा ufs_hba *hba =  platक्रमm_get_drvdata(pdev);

	pm_runसमय_get_sync(&(pdev)->dev);
	ufshcd_हटाओ(hba);
	वापस 0;
पूर्ण

काष्ठा exynos_ufs_drv_data exynos_ufs_drvs = अणु

	.compatible		= "samsung,exynos7-ufs",
	.uic_attr		= &exynos7_uic_attr,
	.quirks			= UFSHCD_QUIRK_PRDT_BYTE_GRAN |
				  UFSHCI_QUIRK_BROKEN_REQ_LIST_CLR |
				  UFSHCI_QUIRK_BROKEN_HCE |
				  UFSHCI_QUIRK_SKIP_RESET_INTR_AGGR |
				  UFSHCD_QUIRK_BROKEN_OCS_FATAL_ERROR |
				  UFSHCI_QUIRK_SKIP_MANUAL_WB_FLUSH_CTRL |
				  UFSHCD_QUIRK_SKIP_DEF_UNIPRO_TIMEOUT_SETTING |
				  UFSHCD_QUIRK_ALIGN_SG_WITH_PAGE_SIZE,
	.opts			= EXYNOS_UFS_OPT_HAS_APB_CLK_CTRL |
				  EXYNOS_UFS_OPT_BROKEN_AUTO_CLK_CTRL |
				  EXYNOS_UFS_OPT_BROKEN_RX_SEL_IDX |
				  EXYNOS_UFS_OPT_SKIP_CONNECTION_ESTAB |
				  EXYNOS_UFS_OPT_USE_SW_HIBERN8_TIMER,
	.drv_init		= exynos7_ufs_drv_init,
	.pre_link		= exynos7_ufs_pre_link,
	.post_link		= exynos7_ufs_post_link,
	.pre_pwr_change		= exynos7_ufs_pre_pwr_change,
	.post_pwr_change	= exynos7_ufs_post_pwr_change,
पूर्ण;

अटल स्थिर काष्ठा of_device_id exynos_ufs_of_match[] = अणु
	अणु .compatible = "samsung,exynos7-ufs",
	  .data	      = &exynos_ufs_drvs पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल स्थिर काष्ठा dev_pm_ops exynos_ufs_pm_ops = अणु
	.suspend	= ufshcd_pltfrm_suspend,
	.resume		= ufshcd_pltfrm_resume,
	.runसमय_suspend = ufshcd_pltfrm_runसमय_suspend,
	.runसमय_resume  = ufshcd_pltfrm_runसमय_resume,
	.runसमय_idle    = ufshcd_pltfrm_runसमय_idle,
पूर्ण;

अटल काष्ठा platक्रमm_driver exynos_ufs_pltक्रमm = अणु
	.probe	= exynos_ufs_probe,
	.हटाओ	= exynos_ufs_हटाओ,
	.shutकरोwn = ufshcd_pltfrm_shutकरोwn,
	.driver	= अणु
		.name	= "exynos-ufshc",
		.pm	= &exynos_ufs_pm_ops,
		.of_match_table = of_match_ptr(exynos_ufs_of_match),
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(exynos_ufs_pltक्रमm);

MODULE_AUTHOR("Alim Akhtar <alim.akhtar@samsung.com>");
MODULE_AUTHOR("Seungwon Jeon  <essuuj@gmail.com>");
MODULE_DESCRIPTION("Exynos UFS HCI Driver");
MODULE_LICENSE("GPL v2");
