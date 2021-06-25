<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (C) 2013 - 2015 Fujitsu Semiconductor, Ltd
 *              Vincent Yang <vincent.yang@tw.fujitsu.com>
 * Copyright (C) 2015 Linaro Ltd  Andy Green <andy.green@linaro.org>
 * Copyright (C) 2019 Socionext Inc.
 *
 */

/* F_SDH30 extended Controller रेजिस्टरs */
#घोषणा F_SDH30_AHB_CONFIG      0x100
#घोषणा  F_SDH30_AHB_BIGED      BIT(6)
#घोषणा  F_SDH30_BUSLOCK_DMA    BIT(5)
#घोषणा  F_SDH30_BUSLOCK_EN     BIT(4)
#घोषणा  F_SDH30_SIN            BIT(3)
#घोषणा  F_SDH30_AHB_INCR_16    BIT(2)
#घोषणा  F_SDH30_AHB_INCR_8     BIT(1)
#घोषणा  F_SDH30_AHB_INCR_4     BIT(0)

#घोषणा F_SDH30_TUNING_SETTING  0x108
#घोषणा  F_SDH30_CMD_CHK_DIS    BIT(16)

#घोषणा F_SDH30_IO_CONTROL2     0x114
#घोषणा  F_SDH30_CRES_O_DN      BIT(19)
#घोषणा  F_SDH30_MSEL_O_1_8     BIT(18)

#घोषणा F_SDH30_ESD_CONTROL     0x124
#घोषणा	 F_SDH30_EMMC_RST		BIT(1)
#घोषणा  F_SDH30_CMD_DAT_DELAY	BIT(9)
#घोषणा	 F_SDH30_EMMC_HS200		BIT(24)

#घोषणा F_SDH30_MIN_CLOCK		400000
