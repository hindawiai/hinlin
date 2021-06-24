<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (C) 2019 MediaTek Inc.
 */

#अगर_अघोषित _UFS_MEDIATEK_H
#घोषणा _UFS_MEDIATEK_H

#समावेश <linux/bitops.h>
#समावेश <linux/soc/mediatek/mtk_sip_svc.h>

/*
 * Venकरोr specअगरic UFSHCI Registers
 */
#घोषणा REG_UFS_REFCLK_CTRL         0x144
#घोषणा REG_UFS_EXTREG              0x2100
#घोषणा REG_UFS_MPHYCTRL            0x2200
#घोषणा REG_UFS_REJECT_MON          0x22AC
#घोषणा REG_UFS_DEBUG_SEL           0x22C0
#घोषणा REG_UFS_PROBE               0x22C8

/*
 * Ref-clk control
 *
 * Values क्रम रेजिस्टर REG_UFS_REFCLK_CTRL
 */
#घोषणा REFCLK_RELEASE              0x0
#घोषणा REFCLK_REQUEST              BIT(0)
#घोषणा REFCLK_ACK                  BIT(1)

#घोषणा REFCLK_REQ_TIMEOUT_US       3000

/*
 * Other attributes
 */
#घोषणा VS_DEBUGCLOCKENABLE         0xD0A1
#घोषणा VS_SAVEPOWERCONTROL         0xD0A6
#घोषणा VS_UNIPROPOWERDOWNCONTROL   0xD0A8

/*
 * Venकरोr specअगरic link state
 */
क्रमागत अणु
	VS_LINK_DISABLED            = 0,
	VS_LINK_DOWN                = 1,
	VS_LINK_UP                  = 2,
	VS_LINK_HIBERN8             = 3,
	VS_LINK_LOST                = 4,
	VS_LINK_CFG                 = 5,
पूर्ण;

/*
 * SiP commands
 */
#घोषणा MTK_SIP_UFS_CONTROL               MTK_SIP_SMC_CMD(0x276)
#घोषणा UFS_MTK_SIP_VA09_PWR_CTRL         BIT(0)
#घोषणा UFS_MTK_SIP_DEVICE_RESET          BIT(1)
#घोषणा UFS_MTK_SIP_CRYPTO_CTRL           BIT(2)
#घोषणा UFS_MTK_SIP_REF_CLK_NOTIFICATION  BIT(3)

/*
 * VS_DEBUGCLOCKENABLE
 */
क्रमागत अणु
	TX_SYMBOL_CLK_REQ_FORCE = 5,
पूर्ण;

/*
 * VS_SAVEPOWERCONTROL
 */
क्रमागत अणु
	RX_SYMBOL_CLK_GATE_EN   = 0,
	SYS_CLK_GATE_EN         = 2,
	TX_CLK_GATE_EN          = 3,
पूर्ण;

/*
 * Host capability
 */
क्रमागत ufs_mtk_host_caps अणु
	UFS_MTK_CAP_BOOST_CRYPT_ENGINE         = 1 << 0,
	UFS_MTK_CAP_VA09_PWR_CTRL              = 1 << 1,
	UFS_MTK_CAP_DISABLE_AH8                = 1 << 2,
	UFS_MTK_CAP_BROKEN_VCC                 = 1 << 3,
पूर्ण;

काष्ठा ufs_mtk_crypt_cfg अणु
	काष्ठा regulator *reg_vcore;
	काष्ठा clk *clk_crypt_perf;
	काष्ठा clk *clk_crypt_mux;
	काष्ठा clk *clk_crypt_lp;
	पूर्णांक vcore_volt;
पूर्ण;

काष्ठा ufs_mtk_hw_ver अणु
	u8 step;
	u8 minor;
	u8 major;
पूर्ण;

काष्ठा ufs_mtk_host अणु
	काष्ठा phy *mphy;
	काष्ठा regulator *reg_va09;
	काष्ठा reset_control *hci_reset;
	काष्ठा reset_control *unipro_reset;
	काष्ठा reset_control *crypto_reset;
	काष्ठा ufs_hba *hba;
	काष्ठा ufs_mtk_crypt_cfg *crypt;
	काष्ठा ufs_mtk_hw_ver hw_ver;
	क्रमागत ufs_mtk_host_caps caps;
	bool mphy_घातered_on;
	bool unipro_lpm;
	bool ref_clk_enabled;
	u16 ref_clk_ungating_रुको_us;
	u16 ref_clk_gating_रुको_us;
पूर्ण;

#पूर्ण_अगर /* !_UFS_MEDIATEK_H */
