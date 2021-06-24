<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * wm8962.h  --  WM8962 Soc Audio driver platक्रमm data
 */

#अगर_अघोषित _WM8962_PDATA_H
#घोषणा _WM8962_PDATA_H

#घोषणा WM8962_MAX_GPIO 6

/* Use to set GPIO शेष values to zero */
#घोषणा WM8962_GPIO_SET 0x10000

#घोषणा WM8962_GPIO_FN_CLKOUT           0
#घोषणा WM8962_GPIO_FN_LOGIC            1
#घोषणा WM8962_GPIO_FN_SDOUT            2
#घोषणा WM8962_GPIO_FN_IRQ              3
#घोषणा WM8962_GPIO_FN_THERMAL          4
#घोषणा WM8962_GPIO_FN_PLL2_LOCK        6
#घोषणा WM8962_GPIO_FN_PLL3_LOCK        7
#घोषणा WM8962_GPIO_FN_FLL_LOCK         9
#घोषणा WM8962_GPIO_FN_DRC_ACT         10
#घोषणा WM8962_GPIO_FN_WSEQ_DONE       11
#घोषणा WM8962_GPIO_FN_ALC_NG_ACT      12
#घोषणा WM8962_GPIO_FN_ALC_PEAK_LIMIT  13
#घोषणा WM8962_GPIO_FN_ALC_SATURATION  14
#घोषणा WM8962_GPIO_FN_ALC_LEVEL_THR   15
#घोषणा WM8962_GPIO_FN_ALC_LEVEL_LOCK  16
#घोषणा WM8962_GPIO_FN_FIFO_ERR        17
#घोषणा WM8962_GPIO_FN_OPCLK           18
#घोषणा WM8962_GPIO_FN_DMICCLK         19
#घोषणा WM8962_GPIO_FN_DMICDAT         20
#घोषणा WM8962_GPIO_FN_MICD            21
#घोषणा WM8962_GPIO_FN_MICSCD          22

काष्ठा wm8962_pdata अणु
	काष्ठा clk *mclk;
	पूर्णांक gpio_base;
	u32 gpio_init[WM8962_MAX_GPIO];

	/* Setup क्रम microphone detection, raw value to be written to
	 * R48(0x30) - only microphone related bits will be updated.
	 * Detection may be enabled here क्रम use with संकेतs brought
	 * out on the GPIOs. */
	u32 mic_cfg;

	bool irq_active_low;

	bool spk_mono;   /* Speaker outमाला_दो tied together as mono */

	/**
	 * This flag should be set अगर one or both IN4 inमाला_दो is wired
	 * in a DC measurement configuration.
	 */
	bool in4_dc_measure;
पूर्ण;

#पूर्ण_अगर
