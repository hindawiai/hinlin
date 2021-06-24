<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * UFS Host Controller driver क्रम Exynos specअगरic extensions
 *
 * Copyright (C) 2014-2015 Samsung Electronics Co., Ltd.
 *
 */

#अगर_अघोषित _UFS_EXYNOS_H_
#घोषणा _UFS_EXYNOS_H_

/*
 * UNIPRO रेजिस्टरs
 */
#घोषणा UNIPRO_DBG_FORCE_DME_CTRL_STATE		0x150

/*
 * MIBs क्रम PA debug रेजिस्टरs
 */
#घोषणा PA_DBG_CLK_PERIOD	0x9514
#घोषणा PA_DBG_TXPHY_CFGUPDT	0x9518
#घोषणा PA_DBG_RXPHY_CFGUPDT	0x9519
#घोषणा PA_DBG_MODE		0x9529
#घोषणा PA_DBG_SKIP_RESET_PHY	0x9539
#घोषणा PA_DBG_OV_TM		0x9540
#घोषणा PA_DBG_SKIP_LINE_RESET	0x9541
#घोषणा PA_DBG_LINE_RESET_REQ	0x9543
#घोषणा PA_DBG_OPTION_SUITE	0x9564
#घोषणा PA_DBG_OPTION_SUITE_DYN	0x9565

/*
 * MIBs क्रम Transport Layer debug रेजिस्टरs
 */
#घोषणा T_DBG_SKIP_INIT_HIBERN8_EXIT	0xc001

/*
 * Exynos MPHY attributes
 */
#घोषणा TX_LINERESET_N_VAL	0x0277
#घोषणा TX_LINERESET_N(v)	(((v) >> 10) & 0xFF)
#घोषणा TX_LINERESET_P_VAL	0x027D
#घोषणा TX_LINERESET_P(v)	(((v) >> 12) & 0xFF)
#घोषणा TX_OV_SLEEP_CNT_TIMER	0x028E
#घोषणा TX_OV_H8_ENTER_EN	(1 << 7)
#घोषणा TX_OV_SLEEP_CNT(v)	(((v) >> 5) & 0x7F)
#घोषणा TX_HIGH_Z_CNT_11_08	0x028C
#घोषणा TX_HIGH_Z_CNT_H(v)	(((v) >> 8) & 0xF)
#घोषणा TX_HIGH_Z_CNT_07_00	0x028D
#घोषणा TX_HIGH_Z_CNT_L(v)	((v) & 0xFF)
#घोषणा TX_BASE_NVAL_07_00	0x0293
#घोषणा TX_BASE_NVAL_L(v)	((v) & 0xFF)
#घोषणा TX_BASE_NVAL_15_08	0x0294
#घोषणा TX_BASE_NVAL_H(v)	(((v) >> 8) & 0xFF)
#घोषणा TX_GRAN_NVAL_07_00	0x0295
#घोषणा TX_GRAN_NVAL_L(v)	((v) & 0xFF)
#घोषणा TX_GRAN_NVAL_10_08	0x0296
#घोषणा TX_GRAN_NVAL_H(v)	(((v) >> 8) & 0x3)

#घोषणा RX_FILLER_ENABLE	0x0316
#घोषणा RX_FILLER_EN		(1 << 1)
#घोषणा RX_LINERESET_VAL	0x0317
#घोषणा RX_LINERESET(v)	(((v) >> 12) & 0xFF)
#घोषणा RX_LCC_IGNORE		0x0318
#घोषणा RX_SYNC_MASK_LENGTH	0x0321
#घोषणा RX_HIBERN8_WAIT_VAL_BIT_20_16	0x0331
#घोषणा RX_HIBERN8_WAIT_VAL_BIT_15_08	0x0332
#घोषणा RX_HIBERN8_WAIT_VAL_BIT_07_00	0x0333
#घोषणा RX_OV_SLEEP_CNT_TIMER	0x0340
#घोषणा RX_OV_SLEEP_CNT(v)	(((v) >> 6) & 0x1F)
#घोषणा RX_OV_STALL_CNT_TIMER	0x0341
#घोषणा RX_OV_STALL_CNT(v)	(((v) >> 4) & 0xFF)
#घोषणा RX_BASE_NVAL_07_00	0x0355
#घोषणा RX_BASE_NVAL_L(v)	((v) & 0xFF)
#घोषणा RX_BASE_NVAL_15_08	0x0354
#घोषणा RX_BASE_NVAL_H(v)	(((v) >> 8) & 0xFF)
#घोषणा RX_GRAN_NVAL_07_00	0x0353
#घोषणा RX_GRAN_NVAL_L(v)	((v) & 0xFF)
#घोषणा RX_GRAN_NVAL_10_08	0x0352
#घोषणा RX_GRAN_NVAL_H(v)	(((v) >> 8) & 0x3)

#घोषणा CMN_PWM_CLK_CTRL	0x0402
#घोषणा PWM_CLK_CTRL_MASK	0x3

#घोषणा IATOVAL_NSEC		20000	/* unit: ns */
#घोषणा UNIPRO_PCLK_PERIOD(ufs) (NSEC_PER_SEC / ufs->pclk_rate)

काष्ठा exynos_ufs;

/* venकरोr specअगरic pre-defined parameters */
#घोषणा SLOW 1
#घोषणा FAST 2

#घोषणा RX_ADV_FINE_GRAN_SUP_EN	0x1
#घोषणा RX_ADV_FINE_GRAN_STEP_VAL	0x3
#घोषणा RX_ADV_MIN_ACTV_TIME_CAP	0x9

#घोषणा PA_GRANULARITY_VAL	0x6
#घोषणा PA_TACTIVATE_VAL	0x3
#घोषणा PA_HIBERN8TIME_VAL	0x20

#घोषणा PCLK_AVAIL_MIN	70000000
#घोषणा PCLK_AVAIL_MAX	133000000

काष्ठा exynos_ufs_uic_attr अणु
	/* TX Attributes */
	अचिन्हित पूर्णांक tx_trailingclks;
	अचिन्हित पूर्णांक tx_dअगर_p_nsec;
	अचिन्हित पूर्णांक tx_dअगर_n_nsec;
	अचिन्हित पूर्णांक tx_high_z_cnt_nsec;
	अचिन्हित पूर्णांक tx_base_unit_nsec;
	अचिन्हित पूर्णांक tx_gran_unit_nsec;
	अचिन्हित पूर्णांक tx_sleep_cnt;
	अचिन्हित पूर्णांक tx_min_activateसमय;
	/* RX Attributes */
	अचिन्हित पूर्णांक rx_filler_enable;
	अचिन्हित पूर्णांक rx_dअगर_p_nsec;
	अचिन्हित पूर्णांक rx_hibern8_रुको_nsec;
	अचिन्हित पूर्णांक rx_base_unit_nsec;
	अचिन्हित पूर्णांक rx_gran_unit_nsec;
	अचिन्हित पूर्णांक rx_sleep_cnt;
	अचिन्हित पूर्णांक rx_stall_cnt;
	अचिन्हित पूर्णांक rx_hs_g1_sync_len_cap;
	अचिन्हित पूर्णांक rx_hs_g2_sync_len_cap;
	अचिन्हित पूर्णांक rx_hs_g3_sync_len_cap;
	अचिन्हित पूर्णांक rx_hs_g1_prep_sync_len_cap;
	अचिन्हित पूर्णांक rx_hs_g2_prep_sync_len_cap;
	अचिन्हित पूर्णांक rx_hs_g3_prep_sync_len_cap;
	/* Common Attributes */
	अचिन्हित पूर्णांक cmn_pwm_clk_ctrl;
	/* Internal Attributes */
	अचिन्हित पूर्णांक pa_dbg_option_suite;
	/* Changeable Attributes */
	अचिन्हित पूर्णांक rx_adv_fine_gran_sup_en;
	अचिन्हित पूर्णांक rx_adv_fine_gran_step;
	अचिन्हित पूर्णांक rx_min_actv_समय_cap;
	अचिन्हित पूर्णांक rx_hibern8_समय_cap;
	अचिन्हित पूर्णांक rx_adv_min_actv_समय_cap;
	अचिन्हित पूर्णांक rx_adv_hibern8_समय_cap;
	अचिन्हित पूर्णांक pa_granularity;
	अचिन्हित पूर्णांक pa_tactivate;
	अचिन्हित पूर्णांक pa_hibern8समय;
पूर्ण;

काष्ठा exynos_ufs_drv_data अणु
	अक्षर *compatible;
	काष्ठा exynos_ufs_uic_attr *uic_attr;
	अचिन्हित पूर्णांक quirks;
	अचिन्हित पूर्णांक opts;
	/* SoC's specअगरic operations */
	पूर्णांक (*drv_init)(काष्ठा device *dev, काष्ठा exynos_ufs *ufs);
	पूर्णांक (*pre_link)(काष्ठा exynos_ufs *ufs);
	पूर्णांक (*post_link)(काष्ठा exynos_ufs *ufs);
	पूर्णांक (*pre_pwr_change)(काष्ठा exynos_ufs *ufs,
				काष्ठा ufs_pa_layer_attr *pwr);
	पूर्णांक (*post_pwr_change)(काष्ठा exynos_ufs *ufs,
				काष्ठा ufs_pa_layer_attr *pwr);
पूर्ण;

काष्ठा ufs_phy_समय_cfg अणु
	u32 tx_linereset_p;
	u32 tx_linereset_n;
	u32 tx_high_z_cnt;
	u32 tx_base_n_val;
	u32 tx_gran_n_val;
	u32 tx_sleep_cnt;
	u32 rx_linereset;
	u32 rx_hibern8_रुको;
	u32 rx_base_n_val;
	u32 rx_gran_n_val;
	u32 rx_sleep_cnt;
	u32 rx_stall_cnt;
पूर्ण;

काष्ठा exynos_ufs अणु
	काष्ठा ufs_hba *hba;
	काष्ठा phy *phy;
	व्योम __iomem *reg_hci;
	व्योम __iomem *reg_unipro;
	व्योम __iomem *reg_ufsp;
	काष्ठा clk *clk_hci_core;
	काष्ठा clk *clk_unipro_मुख्य;
	काष्ठा clk *clk_apb;
	u32 pclk_rate;
	u32 pclk_भाग;
	u32 pclk_avail_min;
	u32 pclk_avail_max;
	u32 mclk_rate;
	पूर्णांक avail_ln_rx;
	पूर्णांक avail_ln_tx;
	पूर्णांक rx_sel_idx;
	काष्ठा ufs_pa_layer_attr dev_req_params;
	काष्ठा ufs_phy_समय_cfg t_cfg;
	kसमय_प्रकार entry_hibern8_t;
	काष्ठा exynos_ufs_drv_data *drv_data;

	u32 opts;
#घोषणा EXYNOS_UFS_OPT_HAS_APB_CLK_CTRL		BIT(0)
#घोषणा EXYNOS_UFS_OPT_SKIP_CONNECTION_ESTAB	BIT(1)
#घोषणा EXYNOS_UFS_OPT_BROKEN_AUTO_CLK_CTRL	BIT(2)
#घोषणा EXYNOS_UFS_OPT_BROKEN_RX_SEL_IDX	BIT(3)
#घोषणा EXYNOS_UFS_OPT_USE_SW_HIBERN8_TIMER	BIT(4)
पूर्ण;

#घोषणा क्रम_each_ufs_rx_lane(ufs, i) \
	क्रम (i = (ufs)->rx_sel_idx; \
		i < (ufs)->rx_sel_idx + (ufs)->avail_ln_rx; i++)
#घोषणा क्रम_each_ufs_tx_lane(ufs, i) \
	क्रम (i = 0; i < (ufs)->avail_ln_tx; i++)

#घोषणा EXYNOS_UFS_MMIO_FUNC(name)					  \
अटल अंतरभूत व्योम name##_ग_लिखोl(काष्ठा exynos_ufs *ufs, u32 val, u32 reg)\
अणु									  \
	ग_लिखोl(val, ufs->reg_##name + reg);				  \
पूर्ण									  \
									  \
अटल अंतरभूत u32 name##_पढ़ोl(काष्ठा exynos_ufs *ufs, u32 reg)		  \
अणु									  \
	वापस पढ़ोl(ufs->reg_##name + reg);				  \
पूर्ण

EXYNOS_UFS_MMIO_FUNC(hci);
EXYNOS_UFS_MMIO_FUNC(unipro);
EXYNOS_UFS_MMIO_FUNC(ufsp);
#अघोषित EXYNOS_UFS_MMIO_FUNC

दीर्घ exynos_ufs_calc_समय_cntr(काष्ठा exynos_ufs *, दीर्घ);

अटल अंतरभूत व्योम exynos_ufs_enable_ov_पंचांग(काष्ठा ufs_hba *hba)
अणु
	ufshcd_dme_set(hba, UIC_ARG_MIB(PA_DBG_OV_TM), TRUE);
पूर्ण

अटल अंतरभूत व्योम exynos_ufs_disable_ov_पंचांग(काष्ठा ufs_hba *hba)
अणु
	ufshcd_dme_set(hba, UIC_ARG_MIB(PA_DBG_OV_TM), FALSE);
पूर्ण

अटल अंतरभूत व्योम exynos_ufs_enable_dbg_mode(काष्ठा ufs_hba *hba)
अणु
	ufshcd_dme_set(hba, UIC_ARG_MIB(PA_DBG_MODE), TRUE);
पूर्ण

अटल अंतरभूत व्योम exynos_ufs_disable_dbg_mode(काष्ठा ufs_hba *hba)
अणु
	ufshcd_dme_set(hba, UIC_ARG_MIB(PA_DBG_MODE), FALSE);
पूर्ण

काष्ठा exynos_ufs_drv_data exynos_ufs_drvs;

काष्ठा exynos_ufs_uic_attr exynos7_uic_attr = अणु
	.tx_trailingclks		= 0x10,
	.tx_dअगर_p_nsec			= 3000000,	/* unit: ns */
	.tx_dअगर_n_nsec			= 1000000,	/* unit: ns */
	.tx_high_z_cnt_nsec		= 20000,	/* unit: ns */
	.tx_base_unit_nsec		= 100000,	/* unit: ns */
	.tx_gran_unit_nsec		= 4000,		/* unit: ns */
	.tx_sleep_cnt			= 1000,		/* unit: ns */
	.tx_min_activateसमय		= 0xa,
	.rx_filler_enable		= 0x2,
	.rx_dअगर_p_nsec			= 1000000,	/* unit: ns */
	.rx_hibern8_रुको_nsec		= 4000000,	/* unit: ns */
	.rx_base_unit_nsec		= 100000,	/* unit: ns */
	.rx_gran_unit_nsec		= 4000,		/* unit: ns */
	.rx_sleep_cnt			= 1280,		/* unit: ns */
	.rx_stall_cnt			= 320,		/* unit: ns */
	.rx_hs_g1_sync_len_cap		= SYNC_LEN_COARSE(0xf),
	.rx_hs_g2_sync_len_cap		= SYNC_LEN_COARSE(0xf),
	.rx_hs_g3_sync_len_cap		= SYNC_LEN_COARSE(0xf),
	.rx_hs_g1_prep_sync_len_cap	= PREP_LEN(0xf),
	.rx_hs_g2_prep_sync_len_cap	= PREP_LEN(0xf),
	.rx_hs_g3_prep_sync_len_cap	= PREP_LEN(0xf),
	.pa_dbg_option_suite		= 0x30103,
पूर्ण;
#पूर्ण_अगर /* _UFS_EXYNOS_H_ */
