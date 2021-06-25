<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (c) 2017, HiSilicon. All rights reserved.
 */

#अगर_अघोषित UFS_HISI_H_
#घोषणा UFS_HISI_H_

#घोषणा HBRN8_POLL_TOUT_MS	1000

/*
 * ufs sysctrl specअगरic define
 */
#घोषणा PSW_POWER_CTRL	(0x04)
#घोषणा PHY_ISO_EN	(0x08)
#घोषणा HC_LP_CTRL	(0x0C)
#घोषणा PHY_CLK_CTRL	(0x10)
#घोषणा PSW_CLK_CTRL	(0x14)
#घोषणा CLOCK_GATE_BYPASS	(0x18)
#घोषणा RESET_CTRL_EN	(0x1C)
#घोषणा UFS_SYSCTRL	(0x5C)
#घोषणा UFS_DEVICE_RESET_CTRL	(0x60)

#घोषणा BIT_UFS_PSW_ISO_CTRL		(1 << 16)
#घोषणा BIT_UFS_PSW_MTCMOS_EN		(1 << 0)
#घोषणा BIT_UFS_REFCLK_ISO_EN		(1 << 16)
#घोषणा BIT_UFS_PHY_ISO_CTRL		(1 << 0)
#घोषणा BIT_SYSCTRL_LP_ISOL_EN		(1 << 16)
#घोषणा BIT_SYSCTRL_PWR_READY		(1 << 8)
#घोषणा BIT_SYSCTRL_REF_CLOCK_EN	(1 << 24)
#घोषणा MASK_SYSCTRL_REF_CLOCK_SEL	(0x3 << 8)
#घोषणा MASK_SYSCTRL_CFG_CLOCK_FREQ	(0xFF)
#घोषणा UFS_FREQ_CFG_CLK                (0x39)
#घोषणा BIT_SYSCTRL_PSW_CLK_EN		(1 << 4)
#घोषणा MASK_UFS_CLK_GATE_BYPASS	(0x3F)
#घोषणा BIT_SYSCTRL_LP_RESET_N		(1 << 0)
#घोषणा BIT_UFS_REFCLK_SRC_SEl		(1 << 0)
#घोषणा MASK_UFS_SYSCRTL_BYPASS		(0x3F << 16)
#घोषणा MASK_UFS_DEVICE_RESET		(0x1 << 16)
#घोषणा BIT_UFS_DEVICE_RESET		(0x1)

/*
 * M-TX Configuration Attributes क्रम Hixxxx
 */
#घोषणा MPHY_TX_FSM_STATE	0x41
#घोषणा TX_FSM_HIBERN8	0x1

/*
 * Hixxxx UFS HC specअगरic Registers
 */
क्रमागत अणु
	UFS_REG_OCPTHRTL = 0xc0,
	UFS_REG_OOCPR    = 0xc4,

	UFS_REG_CDACFG   = 0xd0,
	UFS_REG_CDATX1   = 0xd4,
	UFS_REG_CDATX2   = 0xd8,
	UFS_REG_CDARX1   = 0xdc,
	UFS_REG_CDARX2   = 0xe0,
	UFS_REG_CDASTA   = 0xe4,

	UFS_REG_LBMCFG   = 0xf0,
	UFS_REG_LBMSTA   = 0xf4,
	UFS_REG_UFSMODE  = 0xf8,

	UFS_REG_HCLKDIV  = 0xfc,
पूर्ण;

/* AHIT - Auto-Hibernate Idle Timer */
#घोषणा UFS_AHIT_AH8ITV_MASK	0x3FF

/* REG UFS_REG_OCPTHRTL definition */
#घोषणा UFS_HCLKDIV_NORMAL_VALUE	0xE4

/* venकरोr specअगरic pre-defined parameters */
#घोषणा SLOW	1
#घोषणा FAST	2

#घोषणा UFS_HISI_CAP_RESERVED		BIT(0)
#घोषणा UFS_HISI_CAP_PHY10nm		BIT(1)

काष्ठा ufs_hisi_host अणु
	काष्ठा ufs_hba *hba;
	व्योम __iomem *ufs_sys_ctrl;

	काष्ठा reset_control	*rst;

	uपूर्णांक64_t caps;

	bool in_suspend;
पूर्ण;

#घोषणा ufs_sys_ctrl_ग_लिखोl(host, val, reg)                                    \
	ग_लिखोl((val), (host)->ufs_sys_ctrl + (reg))
#घोषणा ufs_sys_ctrl_पढ़ोl(host, reg) पढ़ोl((host)->ufs_sys_ctrl + (reg))
#घोषणा ufs_sys_ctrl_set_bits(host, mask, reg)                                 \
	ufs_sys_ctrl_ग_लिखोl(                                                   \
		(host), ((mask) | (ufs_sys_ctrl_पढ़ोl((host), (reg)))), (reg))
#घोषणा ufs_sys_ctrl_clr_bits(host, mask, reg)                                 \
	ufs_sys_ctrl_ग_लिखोl((host),                                            \
			    ((~(mask)) & (ufs_sys_ctrl_पढ़ोl((host), (reg)))), \
			    (reg))

#पूर्ण_अगर /* UFS_HISI_H_ */
