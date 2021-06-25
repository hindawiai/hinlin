<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * include/linux/mfd/wm8994/gpपन.स - GPIO configuration क्रम WM8994
 *
 * Copyright 2009 Wolfson Microelectronics PLC.
 *
 * Author: Mark Brown <broonie@खोलोsource.wolfsonmicro.com>
 */

#अगर_अघोषित __MFD_WM8994_GPIO_H__
#घोषणा __MFD_WM8994_GPIO_H__

#घोषणा WM8994_GPIO_MAX 11

#घोषणा WM8994_GP_FN_PIN_SPECIFIC    0
#घोषणा WM8994_GP_FN_GPIO            1
#घोषणा WM8994_GP_FN_SDOUT           2
#घोषणा WM8994_GP_FN_IRQ             3
#घोषणा WM8994_GP_FN_TEMPERATURE     4
#घोषणा WM8994_GP_FN_MICBIAS1_DET    5
#घोषणा WM8994_GP_FN_MICBIAS1_SHORT  6
#घोषणा WM8994_GP_FN_MICBIAS2_DET    7
#घोषणा WM8994_GP_FN_MICBIAS2_SHORT  8
#घोषणा WM8994_GP_FN_FLL1_LOCK       9
#घोषणा WM8994_GP_FN_FLL2_LOCK      10
#घोषणा WM8994_GP_FN_SRC1_LOCK      11
#घोषणा WM8994_GP_FN_SRC2_LOCK      12
#घोषणा WM8994_GP_FN_DRC1_ACT       13
#घोषणा WM8994_GP_FN_DRC2_ACT       14
#घोषणा WM8994_GP_FN_DRC3_ACT       15
#घोषणा WM8994_GP_FN_WSEQ_STATUS    16
#घोषणा WM8994_GP_FN_FIFO_ERROR     17
#घोषणा WM8994_GP_FN_OPCLK          18
#घोषणा WM8994_GP_FN_THW	    19
#घोषणा WM8994_GP_FN_DCS_DONE	    20
#घोषणा WM8994_GP_FN_FLL1_OUT       21
#घोषणा WM8994_GP_FN_FLL2_OUT       22

#घोषणा WM8994_GPN_सूची                          0x8000  /* GPN_सूची */
#घोषणा WM8994_GPN_सूची_MASK                     0x8000  /* GPN_सूची */
#घोषणा WM8994_GPN_सूची_SHIFT                        15  /* GPN_सूची */
#घोषणा WM8994_GPN_सूची_WIDTH                         1  /* GPN_सूची */
#घोषणा WM8994_GPN_PU                           0x4000  /* GPN_PU */
#घोषणा WM8994_GPN_PU_MASK                      0x4000  /* GPN_PU */
#घोषणा WM8994_GPN_PU_SHIFT                         14  /* GPN_PU */
#घोषणा WM8994_GPN_PU_WIDTH                          1  /* GPN_PU */
#घोषणा WM8994_GPN_PD                           0x2000  /* GPN_PD */
#घोषणा WM8994_GPN_PD_MASK                      0x2000  /* GPN_PD */
#घोषणा WM8994_GPN_PD_SHIFT                         13  /* GPN_PD */
#घोषणा WM8994_GPN_PD_WIDTH                          1  /* GPN_PD */
#घोषणा WM8994_GPN_POL                          0x0400  /* GPN_POL */
#घोषणा WM8994_GPN_POL_MASK                     0x0400  /* GPN_POL */
#घोषणा WM8994_GPN_POL_SHIFT                        10  /* GPN_POL */
#घोषणा WM8994_GPN_POL_WIDTH                         1  /* GPN_POL */
#घोषणा WM8994_GPN_OP_CFG                       0x0200  /* GPN_OP_CFG */
#घोषणा WM8994_GPN_OP_CFG_MASK                  0x0200  /* GPN_OP_CFG */
#घोषणा WM8994_GPN_OP_CFG_SHIFT                      9  /* GPN_OP_CFG */
#घोषणा WM8994_GPN_OP_CFG_WIDTH                      1  /* GPN_OP_CFG */
#घोषणा WM8994_GPN_DB                           0x0100  /* GPN_DB */
#घोषणा WM8994_GPN_DB_MASK                      0x0100  /* GPN_DB */
#घोषणा WM8994_GPN_DB_SHIFT                          8  /* GPN_DB */
#घोषणा WM8994_GPN_DB_WIDTH                          1  /* GPN_DB */
#घोषणा WM8994_GPN_LVL                          0x0040  /* GPN_LVL */
#घोषणा WM8994_GPN_LVL_MASK                     0x0040  /* GPN_LVL */
#घोषणा WM8994_GPN_LVL_SHIFT                         6  /* GPN_LVL */
#घोषणा WM8994_GPN_LVL_WIDTH                         1  /* GPN_LVL */
#घोषणा WM8994_GPN_FN_MASK                      0x001F  /* GPN_FN - [4:0] */
#घोषणा WM8994_GPN_FN_SHIFT                          0  /* GPN_FN - [4:0] */
#घोषणा WM8994_GPN_FN_WIDTH                          5  /* GPN_FN - [4:0] */

#पूर्ण_अगर
