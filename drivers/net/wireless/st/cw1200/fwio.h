<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Firmware API क्रम mac80211 ST-Ericsson CW1200 drivers
 *
 * Copyright (c) 2010, ST-Ericsson
 * Author: Dmitry Tarnyagin <dmitry.tarnyagin@lockless.no>
 *
 * Based on:
 * ST-Ericsson UMAC CW1200 driver which is
 * Copyright (c) 2010, ST-Ericsson
 * Author: Ajitpal Singh <ajitpal.singh@stericsson.com>
 */

#अगर_अघोषित FWIO_H_INCLUDED
#घोषणा FWIO_H_INCLUDED

#घोषणा BOOTLOADER_CW1X60       "boot_cw1x60.bin"
#घोषणा FIRMWARE_CW1X60		"wsm_cw1x60.bin"
#घोषणा FIRMWARE_CUT22		"wsm_22.bin"
#घोषणा FIRMWARE_CUT20		"wsm_20.bin"
#घोषणा FIRMWARE_CUT11		"wsm_11.bin"
#घोषणा FIRMWARE_CUT10		"wsm_10.bin"
#घोषणा SDD_खाता_CW1X60		"sdd_cw1x60.bin"
#घोषणा SDD_खाता_22		"sdd_22.bin"
#घोषणा SDD_खाता_20		"sdd_20.bin"
#घोषणा SDD_खाता_11		"sdd_11.bin"
#घोषणा SDD_खाता_10		"sdd_10.bin"

पूर्णांक cw1200_load_firmware(काष्ठा cw1200_common *priv);

/* SDD definitions */
#घोषणा SDD_PTA_CFG_ELT_ID 0xEB
#घोषणा SDD_REFERENCE_FREQUENCY_ELT_ID 0xc5
u32 cw1200_dpll_from_clk(u16 clk);

#पूर्ण_अगर
