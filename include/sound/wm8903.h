<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * linux/sound/wm8903.h -- Platक्रमm data क्रम WM8903
 *
 * Copyright 2010 Wolfson Microelectronics. PLC.
 */

#अगर_अघोषित __LINUX_SND_WM8903_H
#घोषणा __LINUX_SND_WM8903_H

/*
 * Used to enable configuration of a GPIO to all zeros; a gpio_cfg value of
 * zero in platक्रमm data means "don't touch this pin".
 */
#घोषणा WM8903_GPIO_CONFIG_ZERO 0x8000

/*
 * R6 (0x06) - Mic Bias Control 0
 */
#घोषणा WM8903_MICDET_THR_MASK                  0x0030  /* MICDET_THR - [5:4] */
#घोषणा WM8903_MICDET_THR_SHIFT                      4  /* MICDET_THR - [5:4] */
#घोषणा WM8903_MICDET_THR_WIDTH                      2  /* MICDET_THR - [5:4] */
#घोषणा WM8903_MICSHORT_THR_MASK                0x000C  /* MICSHORT_THR - [3:2] */
#घोषणा WM8903_MICSHORT_THR_SHIFT                    2  /* MICSHORT_THR - [3:2] */
#घोषणा WM8903_MICSHORT_THR_WIDTH                    2  /* MICSHORT_THR - [3:2] */
#घोषणा WM8903_MICDET_ENA                       0x0002  /* MICDET_ENA */
#घोषणा WM8903_MICDET_ENA_MASK                  0x0002  /* MICDET_ENA */
#घोषणा WM8903_MICDET_ENA_SHIFT                      1  /* MICDET_ENA */
#घोषणा WM8903_MICDET_ENA_WIDTH                      1  /* MICDET_ENA */
#घोषणा WM8903_MICBIAS_ENA                      0x0001  /* MICBIAS_ENA */
#घोषणा WM8903_MICBIAS_ENA_MASK                 0x0001  /* MICBIAS_ENA */
#घोषणा WM8903_MICBIAS_ENA_SHIFT                     0  /* MICBIAS_ENA */
#घोषणा WM8903_MICBIAS_ENA_WIDTH                     1  /* MICBIAS_ENA */

/*
 * WM8903_GPn_FN values
 *
 * See datasheets क्रम list of valid values per pin
 */
#घोषणा WM8903_GPn_FN_GPIO_OUTPUT                    0
#घोषणा WM8903_GPn_FN_BCLK                           1
#घोषणा WM8903_GPn_FN_IRQ_OUTPT                      2
#घोषणा WM8903_GPn_FN_GPIO_INPUT                     3
#घोषणा WM8903_GPn_FN_MICBIAS_CURRENT_DETECT         4
#घोषणा WM8903_GPn_FN_MICBIAS_SHORT_DETECT           5
#घोषणा WM8903_GPn_FN_DMIC_LR_CLK_OUTPUT             6
#घोषणा WM8903_GPn_FN_FLL_LOCK_OUTPUT                8
#घोषणा WM8903_GPn_FN_FLL_CLOCK_OUTPUT               9

/*
 * R116 (0x74) - GPIO Control 1
 */
#घोषणा WM8903_GP1_FN_MASK                      0x1F00  /* GP1_FN - [12:8] */
#घोषणा WM8903_GP1_FN_SHIFT                          8  /* GP1_FN - [12:8] */
#घोषणा WM8903_GP1_FN_WIDTH                          5  /* GP1_FN - [12:8] */
#घोषणा WM8903_GP1_सूची                          0x0080  /* GP1_सूची */
#घोषणा WM8903_GP1_सूची_MASK                     0x0080  /* GP1_सूची */
#घोषणा WM8903_GP1_सूची_SHIFT                         7  /* GP1_सूची */
#घोषणा WM8903_GP1_सूची_WIDTH                         1  /* GP1_सूची */
#घोषणा WM8903_GP1_OP_CFG                       0x0040  /* GP1_OP_CFG */
#घोषणा WM8903_GP1_OP_CFG_MASK                  0x0040  /* GP1_OP_CFG */
#घोषणा WM8903_GP1_OP_CFG_SHIFT                      6  /* GP1_OP_CFG */
#घोषणा WM8903_GP1_OP_CFG_WIDTH                      1  /* GP1_OP_CFG */
#घोषणा WM8903_GP1_IP_CFG                       0x0020  /* GP1_IP_CFG */
#घोषणा WM8903_GP1_IP_CFG_MASK                  0x0020  /* GP1_IP_CFG */
#घोषणा WM8903_GP1_IP_CFG_SHIFT                      5  /* GP1_IP_CFG */
#घोषणा WM8903_GP1_IP_CFG_WIDTH                      1  /* GP1_IP_CFG */
#घोषणा WM8903_GP1_LVL                          0x0010  /* GP1_LVL */
#घोषणा WM8903_GP1_LVL_MASK                     0x0010  /* GP1_LVL */
#घोषणा WM8903_GP1_LVL_SHIFT                         4  /* GP1_LVL */
#घोषणा WM8903_GP1_LVL_WIDTH                         1  /* GP1_LVL */
#घोषणा WM8903_GP1_PD                           0x0008  /* GP1_PD */
#घोषणा WM8903_GP1_PD_MASK                      0x0008  /* GP1_PD */
#घोषणा WM8903_GP1_PD_SHIFT                          3  /* GP1_PD */
#घोषणा WM8903_GP1_PD_WIDTH                          1  /* GP1_PD */
#घोषणा WM8903_GP1_PU                           0x0004  /* GP1_PU */
#घोषणा WM8903_GP1_PU_MASK                      0x0004  /* GP1_PU */
#घोषणा WM8903_GP1_PU_SHIFT                          2  /* GP1_PU */
#घोषणा WM8903_GP1_PU_WIDTH                          1  /* GP1_PU */
#घोषणा WM8903_GP1_INTMODE                      0x0002  /* GP1_INTMODE */
#घोषणा WM8903_GP1_INTMODE_MASK                 0x0002  /* GP1_INTMODE */
#घोषणा WM8903_GP1_INTMODE_SHIFT                     1  /* GP1_INTMODE */
#घोषणा WM8903_GP1_INTMODE_WIDTH                     1  /* GP1_INTMODE */
#घोषणा WM8903_GP1_DB                           0x0001  /* GP1_DB */
#घोषणा WM8903_GP1_DB_MASK                      0x0001  /* GP1_DB */
#घोषणा WM8903_GP1_DB_SHIFT                          0  /* GP1_DB */
#घोषणा WM8903_GP1_DB_WIDTH                          1  /* GP1_DB */

/*
 * R117 (0x75) - GPIO Control 2
 */
#घोषणा WM8903_GP2_FN_MASK                      0x1F00  /* GP2_FN - [12:8] */
#घोषणा WM8903_GP2_FN_SHIFT                          8  /* GP2_FN - [12:8] */
#घोषणा WM8903_GP2_FN_WIDTH                          5  /* GP2_FN - [12:8] */
#घोषणा WM8903_GP2_सूची                          0x0080  /* GP2_सूची */
#घोषणा WM8903_GP2_सूची_MASK                     0x0080  /* GP2_सूची */
#घोषणा WM8903_GP2_सूची_SHIFT                         7  /* GP2_सूची */
#घोषणा WM8903_GP2_सूची_WIDTH                         1  /* GP2_सूची */
#घोषणा WM8903_GP2_OP_CFG                       0x0040  /* GP2_OP_CFG */
#घोषणा WM8903_GP2_OP_CFG_MASK                  0x0040  /* GP2_OP_CFG */
#घोषणा WM8903_GP2_OP_CFG_SHIFT                      6  /* GP2_OP_CFG */
#घोषणा WM8903_GP2_OP_CFG_WIDTH                      1  /* GP2_OP_CFG */
#घोषणा WM8903_GP2_IP_CFG                       0x0020  /* GP2_IP_CFG */
#घोषणा WM8903_GP2_IP_CFG_MASK                  0x0020  /* GP2_IP_CFG */
#घोषणा WM8903_GP2_IP_CFG_SHIFT                      5  /* GP2_IP_CFG */
#घोषणा WM8903_GP2_IP_CFG_WIDTH                      1  /* GP2_IP_CFG */
#घोषणा WM8903_GP2_LVL                          0x0010  /* GP2_LVL */
#घोषणा WM8903_GP2_LVL_MASK                     0x0010  /* GP2_LVL */
#घोषणा WM8903_GP2_LVL_SHIFT                         4  /* GP2_LVL */
#घोषणा WM8903_GP2_LVL_WIDTH                         1  /* GP2_LVL */
#घोषणा WM8903_GP2_PD                           0x0008  /* GP2_PD */
#घोषणा WM8903_GP2_PD_MASK                      0x0008  /* GP2_PD */
#घोषणा WM8903_GP2_PD_SHIFT                          3  /* GP2_PD */
#घोषणा WM8903_GP2_PD_WIDTH                          1  /* GP2_PD */
#घोषणा WM8903_GP2_PU                           0x0004  /* GP2_PU */
#घोषणा WM8903_GP2_PU_MASK                      0x0004  /* GP2_PU */
#घोषणा WM8903_GP2_PU_SHIFT                          2  /* GP2_PU */
#घोषणा WM8903_GP2_PU_WIDTH                          1  /* GP2_PU */
#घोषणा WM8903_GP2_INTMODE                      0x0002  /* GP2_INTMODE */
#घोषणा WM8903_GP2_INTMODE_MASK                 0x0002  /* GP2_INTMODE */
#घोषणा WM8903_GP2_INTMODE_SHIFT                     1  /* GP2_INTMODE */
#घोषणा WM8903_GP2_INTMODE_WIDTH                     1  /* GP2_INTMODE */
#घोषणा WM8903_GP2_DB                           0x0001  /* GP2_DB */
#घोषणा WM8903_GP2_DB_MASK                      0x0001  /* GP2_DB */
#घोषणा WM8903_GP2_DB_SHIFT                          0  /* GP2_DB */
#घोषणा WM8903_GP2_DB_WIDTH                          1  /* GP2_DB */

/*
 * R118 (0x76) - GPIO Control 3
 */
#घोषणा WM8903_GP3_FN_MASK                      0x1F00  /* GP3_FN - [12:8] */
#घोषणा WM8903_GP3_FN_SHIFT                          8  /* GP3_FN - [12:8] */
#घोषणा WM8903_GP3_FN_WIDTH                          5  /* GP3_FN - [12:8] */
#घोषणा WM8903_GP3_सूची                          0x0080  /* GP3_सूची */
#घोषणा WM8903_GP3_सूची_MASK                     0x0080  /* GP3_सूची */
#घोषणा WM8903_GP3_सूची_SHIFT                         7  /* GP3_सूची */
#घोषणा WM8903_GP3_सूची_WIDTH                         1  /* GP3_सूची */
#घोषणा WM8903_GP3_OP_CFG                       0x0040  /* GP3_OP_CFG */
#घोषणा WM8903_GP3_OP_CFG_MASK                  0x0040  /* GP3_OP_CFG */
#घोषणा WM8903_GP3_OP_CFG_SHIFT                      6  /* GP3_OP_CFG */
#घोषणा WM8903_GP3_OP_CFG_WIDTH                      1  /* GP3_OP_CFG */
#घोषणा WM8903_GP3_IP_CFG                       0x0020  /* GP3_IP_CFG */
#घोषणा WM8903_GP3_IP_CFG_MASK                  0x0020  /* GP3_IP_CFG */
#घोषणा WM8903_GP3_IP_CFG_SHIFT                      5  /* GP3_IP_CFG */
#घोषणा WM8903_GP3_IP_CFG_WIDTH                      1  /* GP3_IP_CFG */
#घोषणा WM8903_GP3_LVL                          0x0010  /* GP3_LVL */
#घोषणा WM8903_GP3_LVL_MASK                     0x0010  /* GP3_LVL */
#घोषणा WM8903_GP3_LVL_SHIFT                         4  /* GP3_LVL */
#घोषणा WM8903_GP3_LVL_WIDTH                         1  /* GP3_LVL */
#घोषणा WM8903_GP3_PD                           0x0008  /* GP3_PD */
#घोषणा WM8903_GP3_PD_MASK                      0x0008  /* GP3_PD */
#घोषणा WM8903_GP3_PD_SHIFT                          3  /* GP3_PD */
#घोषणा WM8903_GP3_PD_WIDTH                          1  /* GP3_PD */
#घोषणा WM8903_GP3_PU                           0x0004  /* GP3_PU */
#घोषणा WM8903_GP3_PU_MASK                      0x0004  /* GP3_PU */
#घोषणा WM8903_GP3_PU_SHIFT                          2  /* GP3_PU */
#घोषणा WM8903_GP3_PU_WIDTH                          1  /* GP3_PU */
#घोषणा WM8903_GP3_INTMODE                      0x0002  /* GP3_INTMODE */
#घोषणा WM8903_GP3_INTMODE_MASK                 0x0002  /* GP3_INTMODE */
#घोषणा WM8903_GP3_INTMODE_SHIFT                     1  /* GP3_INTMODE */
#घोषणा WM8903_GP3_INTMODE_WIDTH                     1  /* GP3_INTMODE */
#घोषणा WM8903_GP3_DB                           0x0001  /* GP3_DB */
#घोषणा WM8903_GP3_DB_MASK                      0x0001  /* GP3_DB */
#घोषणा WM8903_GP3_DB_SHIFT                          0  /* GP3_DB */
#घोषणा WM8903_GP3_DB_WIDTH                          1  /* GP3_DB */

/*
 * R119 (0x77) - GPIO Control 4
 */
#घोषणा WM8903_GP4_FN_MASK                      0x1F00  /* GP4_FN - [12:8] */
#घोषणा WM8903_GP4_FN_SHIFT                          8  /* GP4_FN - [12:8] */
#घोषणा WM8903_GP4_FN_WIDTH                          5  /* GP4_FN - [12:8] */
#घोषणा WM8903_GP4_सूची                          0x0080  /* GP4_सूची */
#घोषणा WM8903_GP4_सूची_MASK                     0x0080  /* GP4_सूची */
#घोषणा WM8903_GP4_सूची_SHIFT                         7  /* GP4_सूची */
#घोषणा WM8903_GP4_सूची_WIDTH                         1  /* GP4_सूची */
#घोषणा WM8903_GP4_OP_CFG                       0x0040  /* GP4_OP_CFG */
#घोषणा WM8903_GP4_OP_CFG_MASK                  0x0040  /* GP4_OP_CFG */
#घोषणा WM8903_GP4_OP_CFG_SHIFT                      6  /* GP4_OP_CFG */
#घोषणा WM8903_GP4_OP_CFG_WIDTH                      1  /* GP4_OP_CFG */
#घोषणा WM8903_GP4_IP_CFG                       0x0020  /* GP4_IP_CFG */
#घोषणा WM8903_GP4_IP_CFG_MASK                  0x0020  /* GP4_IP_CFG */
#घोषणा WM8903_GP4_IP_CFG_SHIFT                      5  /* GP4_IP_CFG */
#घोषणा WM8903_GP4_IP_CFG_WIDTH                      1  /* GP4_IP_CFG */
#घोषणा WM8903_GP4_LVL                          0x0010  /* GP4_LVL */
#घोषणा WM8903_GP4_LVL_MASK                     0x0010  /* GP4_LVL */
#घोषणा WM8903_GP4_LVL_SHIFT                         4  /* GP4_LVL */
#घोषणा WM8903_GP4_LVL_WIDTH                         1  /* GP4_LVL */
#घोषणा WM8903_GP4_PD                           0x0008  /* GP4_PD */
#घोषणा WM8903_GP4_PD_MASK                      0x0008  /* GP4_PD */
#घोषणा WM8903_GP4_PD_SHIFT                          3  /* GP4_PD */
#घोषणा WM8903_GP4_PD_WIDTH                          1  /* GP4_PD */
#घोषणा WM8903_GP4_PU                           0x0004  /* GP4_PU */
#घोषणा WM8903_GP4_PU_MASK                      0x0004  /* GP4_PU */
#घोषणा WM8903_GP4_PU_SHIFT                          2  /* GP4_PU */
#घोषणा WM8903_GP4_PU_WIDTH                          1  /* GP4_PU */
#घोषणा WM8903_GP4_INTMODE                      0x0002  /* GP4_INTMODE */
#घोषणा WM8903_GP4_INTMODE_MASK                 0x0002  /* GP4_INTMODE */
#घोषणा WM8903_GP4_INTMODE_SHIFT                     1  /* GP4_INTMODE */
#घोषणा WM8903_GP4_INTMODE_WIDTH                     1  /* GP4_INTMODE */
#घोषणा WM8903_GP4_DB                           0x0001  /* GP4_DB */
#घोषणा WM8903_GP4_DB_MASK                      0x0001  /* GP4_DB */
#घोषणा WM8903_GP4_DB_SHIFT                          0  /* GP4_DB */
#घोषणा WM8903_GP4_DB_WIDTH                          1  /* GP4_DB */

/*
 * R120 (0x78) - GPIO Control 5
 */
#घोषणा WM8903_GP5_FN_MASK                      0x1F00  /* GP5_FN - [12:8] */
#घोषणा WM8903_GP5_FN_SHIFT                          8  /* GP5_FN - [12:8] */
#घोषणा WM8903_GP5_FN_WIDTH                          5  /* GP5_FN - [12:8] */
#घोषणा WM8903_GP5_सूची                          0x0080  /* GP5_सूची */
#घोषणा WM8903_GP5_सूची_MASK                     0x0080  /* GP5_सूची */
#घोषणा WM8903_GP5_सूची_SHIFT                         7  /* GP5_सूची */
#घोषणा WM8903_GP5_सूची_WIDTH                         1  /* GP5_सूची */
#घोषणा WM8903_GP5_OP_CFG                       0x0040  /* GP5_OP_CFG */
#घोषणा WM8903_GP5_OP_CFG_MASK                  0x0040  /* GP5_OP_CFG */
#घोषणा WM8903_GP5_OP_CFG_SHIFT                      6  /* GP5_OP_CFG */
#घोषणा WM8903_GP5_OP_CFG_WIDTH                      1  /* GP5_OP_CFG */
#घोषणा WM8903_GP5_IP_CFG                       0x0020  /* GP5_IP_CFG */
#घोषणा WM8903_GP5_IP_CFG_MASK                  0x0020  /* GP5_IP_CFG */
#घोषणा WM8903_GP5_IP_CFG_SHIFT                      5  /* GP5_IP_CFG */
#घोषणा WM8903_GP5_IP_CFG_WIDTH                      1  /* GP5_IP_CFG */
#घोषणा WM8903_GP5_LVL                          0x0010  /* GP5_LVL */
#घोषणा WM8903_GP5_LVL_MASK                     0x0010  /* GP5_LVL */
#घोषणा WM8903_GP5_LVL_SHIFT                         4  /* GP5_LVL */
#घोषणा WM8903_GP5_LVL_WIDTH                         1  /* GP5_LVL */
#घोषणा WM8903_GP5_PD                           0x0008  /* GP5_PD */
#घोषणा WM8903_GP5_PD_MASK                      0x0008  /* GP5_PD */
#घोषणा WM8903_GP5_PD_SHIFT                          3  /* GP5_PD */
#घोषणा WM8903_GP5_PD_WIDTH                          1  /* GP5_PD */
#घोषणा WM8903_GP5_PU                           0x0004  /* GP5_PU */
#घोषणा WM8903_GP5_PU_MASK                      0x0004  /* GP5_PU */
#घोषणा WM8903_GP5_PU_SHIFT                          2  /* GP5_PU */
#घोषणा WM8903_GP5_PU_WIDTH                          1  /* GP5_PU */
#घोषणा WM8903_GP5_INTMODE                      0x0002  /* GP5_INTMODE */
#घोषणा WM8903_GP5_INTMODE_MASK                 0x0002  /* GP5_INTMODE */
#घोषणा WM8903_GP5_INTMODE_SHIFT                     1  /* GP5_INTMODE */
#घोषणा WM8903_GP5_INTMODE_WIDTH                     1  /* GP5_INTMODE */
#घोषणा WM8903_GP5_DB                           0x0001  /* GP5_DB */
#घोषणा WM8903_GP5_DB_MASK                      0x0001  /* GP5_DB */
#घोषणा WM8903_GP5_DB_SHIFT                          0  /* GP5_DB */
#घोषणा WM8903_GP5_DB_WIDTH                          1  /* GP5_DB */

#घोषणा WM8903_NUM_GPIO 5

काष्ठा wm8903_platक्रमm_data अणु
	bool irq_active_low;   /* Set अगर IRQ active low, शेष high */

        /* Default रेजिस्टर value क्रम R6 (Mic bias), used to configure
	 * microphone detection.  In conjunction with gpio_cfg this
	 * can be used to route the microphone status संकेतs out onto
	 * the GPIOs क्रम use with snd_soc_jack_add_gpios().
	 */
	u16 micdet_cfg;

	पूर्णांक micdet_delay;      /* Delay after microphone detection (ms) */

	पूर्णांक gpio_base;
	u32 gpio_cfg[WM8903_NUM_GPIO]; /* Default रेजिस्टर values क्रम GPIO pin mux */
पूर्ण;

#पूर्ण_अगर
