<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Joshua Henderson <joshua.henderson@microchip.com>
 * Copyright (C) 2015 Microchip Technology Inc.  All rights reserved.
 */
#अगर_अघोषित PIC32MZDA_COMMON_H
#घोषणा PIC32MZDA_COMMON_H

/* early घड़ी */
u32 pic32_get_pbclk(पूर्णांक bus);
u32 pic32_get_sysclk(व्योम);

/* Device configuration */
व्योम __init pic32_config_init(व्योम);
पूर्णांक pic32_set_lcd_mode(पूर्णांक mode);
पूर्णांक pic32_set_sdhci_adma_fअगरo_threshold(u32 rthrs, u32 wthrs);
u32 pic32_get_boot_status(व्योम);
पूर्णांक pic32_disable_lcd(व्योम);
पूर्णांक pic32_enable_lcd(व्योम);

#पूर्ण_अगर
