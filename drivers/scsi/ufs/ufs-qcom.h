<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/* Copyright (c) 2013-2015, The Linux Foundation. All rights reserved.
 */

#अगर_अघोषित UFS_QCOM_H_
#घोषणा UFS_QCOM_H_

#समावेश <linux/reset-controller.h>
#समावेश <linux/reset.h>

#घोषणा MAX_UFS_QCOM_HOSTS	1
#घोषणा MAX_U32                 (~(u32)0)
#घोषणा MPHY_TX_FSM_STATE       0x41
#घोषणा TX_FSM_HIBERN8          0x1
#घोषणा HBRN8_POLL_TOUT_MS      100
#घोषणा DEFAULT_CLK_RATE_HZ     1000000
#घोषणा BUS_VECTOR_NAME_LEN     32

#घोषणा UFS_HW_VER_MAJOR_SHFT	(28)
#घोषणा UFS_HW_VER_MAJOR_MASK	(0x000F << UFS_HW_VER_MAJOR_SHFT)
#घोषणा UFS_HW_VER_MINOR_SHFT	(16)
#घोषणा UFS_HW_VER_MINOR_MASK	(0x0FFF << UFS_HW_VER_MINOR_SHFT)
#घोषणा UFS_HW_VER_STEP_SHFT	(0)
#घोषणा UFS_HW_VER_STEP_MASK	(0xFFFF << UFS_HW_VER_STEP_SHFT)

/* venकरोr specअगरic pre-defined parameters */
#घोषणा SLOW 1
#घोषणा FAST 2

#घोषणा UFS_QCOM_LIMIT_HS_RATE		PA_HS_MODE_B

/* QCOM UFS host controller venकरोr specअगरic रेजिस्टरs */
क्रमागत अणु
	REG_UFS_SYS1CLK_1US                 = 0xC0,
	REG_UFS_TX_SYMBOL_CLK_NS_US         = 0xC4,
	REG_UFS_LOCAL_PORT_ID_REG           = 0xC8,
	REG_UFS_PA_ERR_CODE                 = 0xCC,
	REG_UFS_RETRY_TIMER_REG             = 0xD0,
	REG_UFS_PA_LINK_STARTUP_TIMER       = 0xD8,
	REG_UFS_CFG1                        = 0xDC,
	REG_UFS_CFG2                        = 0xE0,
	REG_UFS_HW_VERSION                  = 0xE4,

	UFS_TEST_BUS				= 0xE8,
	UFS_TEST_BUS_CTRL_0			= 0xEC,
	UFS_TEST_BUS_CTRL_1			= 0xF0,
	UFS_TEST_BUS_CTRL_2			= 0xF4,
	UFS_UNIPRO_CFG				= 0xF8,

	/*
	 * QCOM UFS host controller venकरोr specअगरic रेजिस्टरs
	 * added in HW Version 3.0.0
	 */
	UFS_AH8_CFG				= 0xFC,
पूर्ण;

/* QCOM UFS host controller venकरोr specअगरic debug रेजिस्टरs */
क्रमागत अणु
	UFS_DBG_RD_REG_UAWM			= 0x100,
	UFS_DBG_RD_REG_UARM			= 0x200,
	UFS_DBG_RD_REG_TXUC			= 0x300,
	UFS_DBG_RD_REG_RXUC			= 0x400,
	UFS_DBG_RD_REG_DFC			= 0x500,
	UFS_DBG_RD_REG_TRLUT			= 0x600,
	UFS_DBG_RD_REG_TMRLUT			= 0x700,
	UFS_UFS_DBG_RD_REG_OCSC			= 0x800,

	UFS_UFS_DBG_RD_DESC_RAM			= 0x1500,
	UFS_UFS_DBG_RD_PRDT_RAM			= 0x1700,
	UFS_UFS_DBG_RD_RESP_RAM			= 0x1800,
	UFS_UFS_DBG_RD_EDTL_RAM			= 0x1900,
पूर्ण;

#घोषणा UFS_CNTLR_2_x_x_VEN_REGS_OFFSET(x)	(0x000 + x)
#घोषणा UFS_CNTLR_3_x_x_VEN_REGS_OFFSET(x)	(0x400 + x)

/* bit definitions क्रम REG_UFS_CFG1 रेजिस्टर */
#घोषणा QUNIPRO_SEL		0x1
#घोषणा UTP_DBG_RAMS_EN		0x20000
#घोषणा TEST_BUS_EN		BIT(18)
#घोषणा TEST_BUS_SEL		GENMASK(22, 19)
#घोषणा UFS_REG_TEST_BUS_EN	BIT(30)

/* bit definitions क्रम REG_UFS_CFG2 रेजिस्टर */
#घोषणा UAWM_HW_CGC_EN		(1 << 0)
#घोषणा UARM_HW_CGC_EN		(1 << 1)
#घोषणा TXUC_HW_CGC_EN		(1 << 2)
#घोषणा RXUC_HW_CGC_EN		(1 << 3)
#घोषणा DFC_HW_CGC_EN		(1 << 4)
#घोषणा TRLUT_HW_CGC_EN		(1 << 5)
#घोषणा TMRLUT_HW_CGC_EN	(1 << 6)
#घोषणा OCSC_HW_CGC_EN		(1 << 7)

/* bit definition क्रम UFS_UFS_TEST_BUS_CTRL_n */
#घोषणा TEST_BUS_SUB_SEL_MASK	0x1F  /* All XXX_SEL fields are 5 bits wide */

#घोषणा REG_UFS_CFG2_CGC_EN_ALL (UAWM_HW_CGC_EN | UARM_HW_CGC_EN |\
				 TXUC_HW_CGC_EN | RXUC_HW_CGC_EN |\
				 DFC_HW_CGC_EN | TRLUT_HW_CGC_EN |\
				 TMRLUT_HW_CGC_EN | OCSC_HW_CGC_EN)

/* bit offset */
क्रमागत अणु
	OFFSET_UFS_PHY_SOFT_RESET           = 1,
	OFFSET_CLK_NS_REG                   = 10,
पूर्ण;

/* bit masks */
क्रमागत अणु
	MASK_UFS_PHY_SOFT_RESET             = 0x2,
	MASK_TX_SYMBOL_CLK_1US_REG          = 0x3FF,
	MASK_CLK_NS_REG                     = 0xFFFC00,
पूर्ण;

/* QCOM UFS debug prपूर्णांक bit mask */
#घोषणा UFS_QCOM_DBG_PRINT_REGS_EN	BIT(0)
#घोषणा UFS_QCOM_DBG_PRINT_ICE_REGS_EN	BIT(1)
#घोषणा UFS_QCOM_DBG_PRINT_TEST_BUS_EN	BIT(2)

#घोषणा UFS_QCOM_DBG_PRINT_ALL	\
	(UFS_QCOM_DBG_PRINT_REGS_EN | UFS_QCOM_DBG_PRINT_ICE_REGS_EN | \
	 UFS_QCOM_DBG_PRINT_TEST_BUS_EN)

/* QUniPro Venकरोr specअगरic attributes */
#घोषणा PA_VS_CONFIG_REG1	0x9000
#घोषणा DME_VS_CORE_CLK_CTRL	0xD002
/* bit and mask definitions क्रम DME_VS_CORE_CLK_CTRL attribute */
#घोषणा DME_VS_CORE_CLK_CTRL_CORE_CLK_DIV_EN_BIT		BIT(8)
#घोषणा DME_VS_CORE_CLK_CTRL_MAX_CORE_CLK_1US_CYCLES_MASK	0xFF

अटल अंतरभूत व्योम
ufs_qcom_get_controller_revision(काष्ठा ufs_hba *hba,
				 u8 *major, u16 *minor, u16 *step)
अणु
	u32 ver = ufshcd_पढ़ोl(hba, REG_UFS_HW_VERSION);

	*major = (ver & UFS_HW_VER_MAJOR_MASK) >> UFS_HW_VER_MAJOR_SHFT;
	*minor = (ver & UFS_HW_VER_MINOR_MASK) >> UFS_HW_VER_MINOR_SHFT;
	*step = (ver & UFS_HW_VER_STEP_MASK) >> UFS_HW_VER_STEP_SHFT;
पूर्ण;

अटल अंतरभूत व्योम ufs_qcom_निश्चित_reset(काष्ठा ufs_hba *hba)
अणु
	ufshcd_rmwl(hba, MASK_UFS_PHY_SOFT_RESET,
			1 << OFFSET_UFS_PHY_SOFT_RESET, REG_UFS_CFG1);

	/*
	 * Make sure निश्चितion of ufs phy reset is written to
	 * रेजिस्टर beक्रमe वापसing
	 */
	mb();
पूर्ण

अटल अंतरभूत व्योम ufs_qcom_deनिश्चित_reset(काष्ठा ufs_hba *hba)
अणु
	ufshcd_rmwl(hba, MASK_UFS_PHY_SOFT_RESET,
			0 << OFFSET_UFS_PHY_SOFT_RESET, REG_UFS_CFG1);

	/*
	 * Make sure de-निश्चितion of ufs phy reset is written to
	 * रेजिस्टर beक्रमe वापसing
	 */
	mb();
पूर्ण

/* Host controller hardware version: major.minor.step */
काष्ठा ufs_hw_version अणु
	u16 step;
	u16 minor;
	u8 major;
पूर्ण;

काष्ठा ufs_qcom_testbus अणु
	u8 select_major;
	u8 select_minor;
पूर्ण;

काष्ठा gpio_desc;

काष्ठा ufs_qcom_host अणु
	/*
	 * Set this capability अगर host controller supports the QUniPro mode
	 * and अगर driver wants the Host controller to operate in QUniPro mode.
	 * Note: By शेष this capability will be kept enabled अगर host
	 * controller supports the QUniPro mode.
	 */
	#घोषणा UFS_QCOM_CAP_QUNIPRO	0x1

	/*
	 * Set this capability अगर host controller can retain the secure
	 * configuration even after UFS controller core घातer collapse.
	 */
	#घोषणा UFS_QCOM_CAP_RETAIN_SEC_CFG_AFTER_PWR_COLLAPSE	0x2
	u32 caps;

	काष्ठा phy *generic_phy;
	काष्ठा ufs_hba *hba;
	काष्ठा ufs_pa_layer_attr dev_req_params;
	काष्ठा clk *rx_l0_sync_clk;
	काष्ठा clk *tx_l0_sync_clk;
	काष्ठा clk *rx_l1_sync_clk;
	काष्ठा clk *tx_l1_sync_clk;
	bool is_lane_clks_enabled;

	व्योम __iomem *dev_ref_clk_ctrl_mmio;
	bool is_dev_ref_clk_enabled;
	काष्ठा ufs_hw_version hw_ver;
#अगर_घोषित CONFIG_SCSI_UFS_CRYPTO
	व्योम __iomem *ice_mmio;
#पूर्ण_अगर

	u32 dev_ref_clk_en_mask;

	/* Biपंचांगask क्रम enabling debug prपूर्णांकs */
	u32 dbg_prपूर्णांक_en;
	काष्ठा ufs_qcom_testbus testbus;

	/* Reset control of HCI */
	काष्ठा reset_control *core_reset;
	काष्ठा reset_controller_dev rcdev;

	काष्ठा gpio_desc *device_reset;
पूर्ण;

अटल अंतरभूत u32
ufs_qcom_get_debug_reg_offset(काष्ठा ufs_qcom_host *host, u32 reg)
अणु
	अगर (host->hw_ver.major <= 0x02)
		वापस UFS_CNTLR_2_x_x_VEN_REGS_OFFSET(reg);

	वापस UFS_CNTLR_3_x_x_VEN_REGS_OFFSET(reg);
पूर्ण;

#घोषणा ufs_qcom_is_link_off(hba) ufshcd_is_link_off(hba)
#घोषणा ufs_qcom_is_link_active(hba) ufshcd_is_link_active(hba)
#घोषणा ufs_qcom_is_link_hibern8(hba) ufshcd_is_link_hibern8(hba)

पूर्णांक ufs_qcom_testbus_config(काष्ठा ufs_qcom_host *host);

अटल अंतरभूत bool ufs_qcom_cap_qunipro(काष्ठा ufs_qcom_host *host)
अणु
	अगर (host->caps & UFS_QCOM_CAP_QUNIPRO)
		वापस true;
	अन्यथा
		वापस false;
पूर्ण

/* ufs-qcom-ice.c */

#अगर_घोषित CONFIG_SCSI_UFS_CRYPTO
पूर्णांक ufs_qcom_ice_init(काष्ठा ufs_qcom_host *host);
पूर्णांक ufs_qcom_ice_enable(काष्ठा ufs_qcom_host *host);
पूर्णांक ufs_qcom_ice_resume(काष्ठा ufs_qcom_host *host);
पूर्णांक ufs_qcom_ice_program_key(काष्ठा ufs_hba *hba,
			     स्थिर जोड़ ufs_crypto_cfg_entry *cfg, पूर्णांक slot);
#अन्यथा
अटल अंतरभूत पूर्णांक ufs_qcom_ice_init(काष्ठा ufs_qcom_host *host)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत पूर्णांक ufs_qcom_ice_enable(काष्ठा ufs_qcom_host *host)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत पूर्णांक ufs_qcom_ice_resume(काष्ठा ufs_qcom_host *host)
अणु
	वापस 0;
पूर्ण
#घोषणा ufs_qcom_ice_program_key शून्य
#पूर्ण_अगर /* !CONFIG_SCSI_UFS_CRYPTO */

#पूर्ण_अगर /* UFS_QCOM_H_ */
