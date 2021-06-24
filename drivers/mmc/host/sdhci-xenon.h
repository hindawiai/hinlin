<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2016 Marvell, All Rights Reserved.
 *
 * Author:	Hu Ziji <huziji@marvell.com>
 * Date:	2016-8-24
 */
#अगर_अघोषित SDHCI_XENON_H_
#घोषणा SDHCI_XENON_H_

/* Register Offset of Xenon SDHC self-defined रेजिस्टर */
#घोषणा XENON_SYS_CFG_INFO			0x0104
#घोषणा XENON_SLOT_TYPE_SDIO_SHIFT		24
#घोषणा XENON_NR_SUPPORTED_SLOT_MASK		0x7

#घोषणा XENON_SYS_OP_CTRL			0x0108
#घोषणा XENON_AUTO_CLKGATE_DISABLE_MASK		BIT(20)
#घोषणा XENON_SDCLK_IDLखातापूर्णF_ENABLE_SHIFT	8
#घोषणा XENON_SLOT_ENABLE_SHIFT			0

#घोषणा XENON_SYS_EXT_OP_CTRL			0x010C
#घोषणा XENON_MASK_CMD_CONFLICT_ERR		BIT(8)

#घोषणा XENON_SLOT_OP_STATUS_CTRL		0x0128
#घोषणा XENON_TUN_CONSECUTIVE_TIMES_SHIFT	16
#घोषणा XENON_TUN_CONSECUTIVE_TIMES_MASK	0x7
#घोषणा XENON_TUN_CONSECUTIVE_TIMES		0x4
#घोषणा XENON_TUNING_STEP_SHIFT			12
#घोषणा XENON_TUNING_STEP_MASK			0xF
#घोषणा XENON_TUNING_STEP_DIVIDER		BIT(6)

#घोषणा XENON_SLOT_EMMC_CTRL			0x0130
#घोषणा XENON_ENABLE_RESP_STROBE		BIT(25)
#घोषणा XENON_ENABLE_DATA_STROBE		BIT(24)

#घोषणा XENON_SLOT_RETUNING_REQ_CTRL		0x0144
/* retuning compatible */
#घोषणा XENON_RETUNING_COMPATIBLE		0x1

#घोषणा XENON_SLOT_EXT_PRESENT_STATE		0x014C
#घोषणा XENON_DLL_LOCK_STATE			0x1

#घोषणा XENON_SLOT_DLL_CUR_DLY_VAL		0x0150

/* Tuning Parameter */
#घोषणा XENON_TMR_RETUN_NO_PRESENT		0xF
#घोषणा XENON_DEF_TUNING_COUNT			0x9

#घोषणा XENON_DEFAULT_SDCLK_FREQ		400000
#घोषणा XENON_LOWEST_SDCLK_FREQ			100000

/* Xenon specअगरic Mode Select value */
#घोषणा XENON_CTRL_HS200			0x5
#घोषणा XENON_CTRL_HS400			0x6

क्रमागत xenon_variant अणु
	XENON_A3700,
	XENON_AP806,
	XENON_AP807,
	XENON_CP110
पूर्ण;

काष्ठा xenon_priv अणु
	अचिन्हित अक्षर	tuning_count;
	/* idx of SDHC */
	u8		sdhc_id;

	/*
	 * eMMC/SD/SDIO require dअगरferent रेजिस्टर settings.
	 * Xenon driver has to recognize card type
	 * beक्रमe mmc_host->card is not available.
	 * This field records the card type during init.
	 * It is updated in xenon_init_card().
	 *
	 * It is only valid during initialization after it is updated.
	 * Do not access this variable in normal transfers after
	 * initialization completes.
	 */
	अचिन्हित पूर्णांक	init_card_type;

	/*
	 * The bus_width, timing, and घड़ी fields in below
	 * record the current ios setting of Xenon SDHC.
	 * Driver will adjust PHY setting अगर any change to
	 * ios affects PHY timing.
	 */
	अचिन्हित अक्षर	bus_width;
	अचिन्हित अक्षर	timing;
	अचिन्हित पूर्णांक	घड़ी;
	काष्ठा clk      *axi_clk;

	पूर्णांक		phy_type;
	/*
	 * Contains board-specअगरic PHY parameters
	 * passed from device tree.
	 */
	व्योम		*phy_params;
	काष्ठा xenon_emmc_phy_regs *emmc_phy_regs;
	bool restore_needed;
	क्रमागत xenon_variant hw_version;
पूर्ण;

पूर्णांक xenon_phy_adj(काष्ठा sdhci_host *host, काष्ठा mmc_ios *ios);
पूर्णांक xenon_phy_parse_params(काष्ठा device *dev,
			   काष्ठा sdhci_host *host);
व्योम xenon_soc_pad_ctrl(काष्ठा sdhci_host *host,
			अचिन्हित अक्षर संकेत_voltage);
#पूर्ण_अगर
