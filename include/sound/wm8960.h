<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * wm8960.h  --  WM8960 Soc Audio driver platक्रमm data
 */

#अगर_अघोषित _WM8960_PDATA_H
#घोषणा _WM8960_PDATA_H

#घोषणा WM8960_DRES_400R 0
#घोषणा WM8960_DRES_200R 1
#घोषणा WM8960_DRES_600R 2
#घोषणा WM8960_DRES_150R 3
#घोषणा WM8960_DRES_MAX  3

काष्ठा wm8960_data अणु
	bool capless;  /* Headphone outमाला_दो configured in capless mode */

	bool shared_lrclk;  /* DAC and ADC LRCLKs are wired together */

	/*
	 * Setup क्रम headphone detection
	 *
	 * hp_cfg[0]: HPSEL[1:0] of R48 (Additional Control 4)
	 * hp_cfg[1]: अणुHPSWEN:HPSWPOLपूर्ण of R24 (Additional Control 2).
	 * hp_cfg[2]: अणुTOCLKSEL:TOENपूर्ण of R23 (Additional Control 1).
	 */
	u32 hp_cfg[3];

	/*
	 * Setup क्रम gpio configuration
	 *
	 * gpio_cfg[0]: ALRCGPIO of R9 (Audio पूर्णांकerface)
	 * gpio_cfg[1]: अणुGPIOPOL:GPIOSEL[2:0]पूर्ण of R48 (Additional Control 4).
	 */
	u32 gpio_cfg[2];
पूर्ण;

#पूर्ण_अगर
