<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Purna Chandra Mandal,<purna.mandal@microchip.com>
 * Copyright (C) 2015 Microchip Technology Inc.  All rights reserved.
 */
#अगर_अघोषित __MICROCHIP_CLK_PIC32_H_
#घोषणा __MICROCHIP_CLK_PIC32_H_

#समावेश <linux/clk-provider.h>

/* PIC32 घड़ी data */
काष्ठा pic32_clk_common अणु
	काष्ठा device *dev;
	व्योम __iomem *iobase;
	spinlock_t reg_lock; /* घड़ी lock */
पूर्ण;

/* System PLL घड़ी */
काष्ठा pic32_sys_pll_data अणु
	काष्ठा clk_init_data init_data;
	स्थिर u32 ctrl_reg;
	स्थिर u32 status_reg;
	स्थिर u32 lock_mask;
पूर्ण;

/* System घड़ी */
काष्ठा pic32_sys_clk_data अणु
	काष्ठा clk_init_data init_data;
	स्थिर u32 mux_reg;
	स्थिर u32 slew_reg;
	स्थिर u32 *parent_map;
	स्थिर u32 slew_भाग;
पूर्ण;

/* Reference Oscillator घड़ी */
काष्ठा pic32_ref_osc_data अणु
	काष्ठा clk_init_data init_data;
	स्थिर u32 ctrl_reg;
	स्थिर u32 *parent_map;
पूर्ण;

/* Peripheral Bus घड़ी */
काष्ठा pic32_periph_clk_data अणु
	काष्ठा clk_init_data init_data;
	स्थिर u32 ctrl_reg;
पूर्ण;

/* External Secondary Oscillator घड़ी  */
काष्ठा pic32_sec_osc_data अणु
	काष्ठा clk_init_data init_data;
	स्थिर u32 enable_reg;
	स्थिर u32 status_reg;
	स्थिर u32 enable_mask;
	स्थिर u32 status_mask;
	स्थिर अचिन्हित दीर्घ fixed_rate;
पूर्ण;

बाह्य स्थिर काष्ठा clk_ops pic32_pbclk_ops;
बाह्य स्थिर काष्ठा clk_ops pic32_sclk_ops;
बाह्य स्थिर काष्ठा clk_ops pic32_sclk_no_भाग_ops;
बाह्य स्थिर काष्ठा clk_ops pic32_spll_ops;
बाह्य स्थिर काष्ठा clk_ops pic32_roclk_ops;
बाह्य स्थिर काष्ठा clk_ops pic32_sosc_ops;

काष्ठा clk *pic32_periph_clk_रेजिस्टर(स्थिर काष्ठा pic32_periph_clk_data *data,
				      काष्ठा pic32_clk_common *core);
काष्ठा clk *pic32_refo_clk_रेजिस्टर(स्थिर काष्ठा pic32_ref_osc_data *data,
				    काष्ठा pic32_clk_common *core);
काष्ठा clk *pic32_sys_clk_रेजिस्टर(स्थिर काष्ठा pic32_sys_clk_data *data,
				   काष्ठा pic32_clk_common *core);
काष्ठा clk *pic32_spll_clk_रेजिस्टर(स्थिर काष्ठा pic32_sys_pll_data *data,
				    काष्ठा pic32_clk_common *core);
काष्ठा clk *pic32_sosc_clk_रेजिस्टर(स्थिर काष्ठा pic32_sec_osc_data *data,
				    काष्ठा pic32_clk_common *core);

#पूर्ण_अगर /* __MICROCHIP_CLK_PIC32_H_*/
