<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Lochnagar1 रेजिस्टर definitions
 *
 * Copyright (c) 2017-2018 Cirrus Logic, Inc. and
 *                         Cirrus Logic International Semiconductor Ltd.
 *
 * Author: Charles Keepax <ckeepax@खोलोsource.cirrus.com>
 */

#अगर_अघोषित LOCHNAGAR1_REGISTERS_H
#घोषणा LOCHNAGAR1_REGISTERS_H

/* Register Addresses */
#घोषणा LOCHNAGAR1_CDC_AIF1_SEL                       0x0008
#घोषणा LOCHNAGAR1_CDC_AIF2_SEL                       0x0009
#घोषणा LOCHNAGAR1_CDC_AIF3_SEL                       0x000A
#घोषणा LOCHNAGAR1_CDC_MCLK1_SEL                      0x000B
#घोषणा LOCHNAGAR1_CDC_MCLK2_SEL                      0x000C
#घोषणा LOCHNAGAR1_CDC_AIF_CTRL1                      0x000D
#घोषणा LOCHNAGAR1_CDC_AIF_CTRL2                      0x000E
#घोषणा LOCHNAGAR1_EXT_AIF_CTRL                       0x000F
#घोषणा LOCHNAGAR1_DSP_AIF1_SEL                       0x0010
#घोषणा LOCHNAGAR1_DSP_AIF2_SEL                       0x0011
#घोषणा LOCHNAGAR1_DSP_CLKIN_SEL                      0x0012
#घोषणा LOCHNAGAR1_DSP_AIF                            0x0013
#घोषणा LOCHNAGAR1_GF_AIF1                            0x0014
#घोषणा LOCHNAGAR1_GF_AIF2                            0x0015
#घोषणा LOCHNAGAR1_PSIA_AIF                           0x0016
#घोषणा LOCHNAGAR1_PSIA1_SEL                          0x0017
#घोषणा LOCHNAGAR1_PSIA2_SEL                          0x0018
#घोषणा LOCHNAGAR1_SPDIF_AIF_SEL                      0x0019
#घोषणा LOCHNAGAR1_GF_AIF3_SEL                        0x001C
#घोषणा LOCHNAGAR1_GF_AIF4_SEL                        0x001D
#घोषणा LOCHNAGAR1_GF_CLKOUT1_SEL                     0x001E
#घोषणा LOCHNAGAR1_GF_AIF1_SEL                        0x001F
#घोषणा LOCHNAGAR1_GF_AIF2_SEL                        0x0020
#घोषणा LOCHNAGAR1_GF_GPIO2                           0x0026
#घोषणा LOCHNAGAR1_GF_GPIO3                           0x0027
#घोषणा LOCHNAGAR1_GF_GPIO7                           0x0028
#घोषणा LOCHNAGAR1_RST                                0x0029
#घोषणा LOCHNAGAR1_LED1                               0x002A
#घोषणा LOCHNAGAR1_LED2                               0x002B
#घोषणा LOCHNAGAR1_I2C_CTRL                           0x0046

/*
 * (0x0008 - 0x000C, 0x0010 - 0x0012, 0x0017 - 0x0020)
 * CDC_AIF1_SEL - GF_AIF2_SEL
 */
#घोषणा LOCHNAGAR1_SRC_MASK                             0xFF
#घोषणा LOCHNAGAR1_SRC_SHIFT                               0

/* (0x000D)  CDC_AIF_CTRL1 */
#घोषणा LOCHNAGAR1_CDC_AIF2_LRCLK_सूची_MASK              0x40
#घोषणा LOCHNAGAR1_CDC_AIF2_LRCLK_सूची_SHIFT                6
#घोषणा LOCHNAGAR1_CDC_AIF2_BCLK_सूची_MASK               0x20
#घोषणा LOCHNAGAR1_CDC_AIF2_BCLK_सूची_SHIFT                 5
#घोषणा LOCHNAGAR1_CDC_AIF2_ENA_MASK                    0x10
#घोषणा LOCHNAGAR1_CDC_AIF2_ENA_SHIFT                      4
#घोषणा LOCHNAGAR1_CDC_AIF1_LRCLK_सूची_MASK              0x04
#घोषणा LOCHNAGAR1_CDC_AIF1_LRCLK_सूची_SHIFT                2
#घोषणा LOCHNAGAR1_CDC_AIF1_BCLK_सूची_MASK               0x02
#घोषणा LOCHNAGAR1_CDC_AIF1_BCLK_सूची_SHIFT                 1
#घोषणा LOCHNAGAR1_CDC_AIF1_ENA_MASK                    0x01
#घोषणा LOCHNAGAR1_CDC_AIF1_ENA_SHIFT                      0

/* (0x000E)  CDC_AIF_CTRL2 */
#घोषणा LOCHNAGAR1_CDC_AIF3_LRCLK_सूची_MASK              0x40
#घोषणा LOCHNAGAR1_CDC_AIF3_LRCLK_सूची_SHIFT                6
#घोषणा LOCHNAGAR1_CDC_AIF3_BCLK_सूची_MASK               0x20
#घोषणा LOCHNAGAR1_CDC_AIF3_BCLK_सूची_SHIFT                 5
#घोषणा LOCHNAGAR1_CDC_AIF3_ENA_MASK                    0x10
#घोषणा LOCHNAGAR1_CDC_AIF3_ENA_SHIFT                      4
#घोषणा LOCHNAGAR1_CDC_MCLK1_ENA_MASK                   0x02
#घोषणा LOCHNAGAR1_CDC_MCLK1_ENA_SHIFT                     1
#घोषणा LOCHNAGAR1_CDC_MCLK2_ENA_MASK                   0x01
#घोषणा LOCHNAGAR1_CDC_MCLK2_ENA_SHIFT                     0

/* (0x000F)  EXT_AIF_CTRL */
#घोषणा LOCHNAGAR1_SPDIF_AIF_LRCLK_सूची_MASK             0x20
#घोषणा LOCHNAGAR1_SPDIF_AIF_LRCLK_सूची_SHIFT               5
#घोषणा LOCHNAGAR1_SPDIF_AIF_BCLK_सूची_MASK              0x10
#घोषणा LOCHNAGAR1_SPDIF_AIF_BCLK_सूची_SHIFT                4
#घोषणा LOCHNAGAR1_SPDIF_AIF_ENA_MASK                   0x08
#घोषणा LOCHNAGAR1_SPDIF_AIF_ENA_SHIFT                     3

/* (0x0013)  DSP_AIF */
#घोषणा LOCHNAGAR1_DSP_AIF2_LRCLK_सूची_MASK              0x40
#घोषणा LOCHNAGAR1_DSP_AIF2_LRCLK_सूची_SHIFT                6
#घोषणा LOCHNAGAR1_DSP_AIF2_BCLK_सूची_MASK               0x20
#घोषणा LOCHNAGAR1_DSP_AIF2_BCLK_सूची_SHIFT                 5
#घोषणा LOCHNAGAR1_DSP_AIF2_ENA_MASK                    0x10
#घोषणा LOCHNAGAR1_DSP_AIF2_ENA_SHIFT                      4
#घोषणा LOCHNAGAR1_DSP_CLKIN_ENA_MASK                   0x08
#घोषणा LOCHNAGAR1_DSP_CLKIN_ENA_SHIFT                     3
#घोषणा LOCHNAGAR1_DSP_AIF1_LRCLK_सूची_MASK              0x04
#घोषणा LOCHNAGAR1_DSP_AIF1_LRCLK_सूची_SHIFT                2
#घोषणा LOCHNAGAR1_DSP_AIF1_BCLK_सूची_MASK               0x02
#घोषणा LOCHNAGAR1_DSP_AIF1_BCLK_सूची_SHIFT                 1
#घोषणा LOCHNAGAR1_DSP_AIF1_ENA_MASK                    0x01
#घोषणा LOCHNAGAR1_DSP_AIF1_ENA_SHIFT                      0

/* (0x0014)  GF_AIF1 */
#घोषणा LOCHNAGAR1_GF_CLKOUT1_ENA_MASK                  0x40
#घोषणा LOCHNAGAR1_GF_CLKOUT1_ENA_SHIFT                    6
#घोषणा LOCHNAGAR1_GF_AIF3_LRCLK_सूची_MASK               0x20
#घोषणा LOCHNAGAR1_GF_AIF3_LRCLK_सूची_SHIFT                 5
#घोषणा LOCHNAGAR1_GF_AIF3_BCLK_सूची_MASK                0x10
#घोषणा LOCHNAGAR1_GF_AIF3_BCLK_सूची_SHIFT                  4
#घोषणा LOCHNAGAR1_GF_AIF3_ENA_MASK                     0x08
#घोषणा LOCHNAGAR1_GF_AIF3_ENA_SHIFT                       3
#घोषणा LOCHNAGAR1_GF_AIF1_LRCLK_सूची_MASK               0x04
#घोषणा LOCHNAGAR1_GF_AIF1_LRCLK_सूची_SHIFT                 2
#घोषणा LOCHNAGAR1_GF_AIF1_BCLK_सूची_MASK                0x02
#घोषणा LOCHNAGAR1_GF_AIF1_BCLK_सूची_SHIFT                  1
#घोषणा LOCHNAGAR1_GF_AIF1_ENA_MASK                     0x01
#घोषणा LOCHNAGAR1_GF_AIF1_ENA_SHIFT                       0

/* (0x0015)  GF_AIF2 */
#घोषणा LOCHNAGAR1_GF_AIF4_LRCLK_सूची_MASK               0x20
#घोषणा LOCHNAGAR1_GF_AIF4_LRCLK_सूची_SHIFT                 5
#घोषणा LOCHNAGAR1_GF_AIF4_BCLK_सूची_MASK                0x10
#घोषणा LOCHNAGAR1_GF_AIF4_BCLK_सूची_SHIFT                  4
#घोषणा LOCHNAGAR1_GF_AIF4_ENA_MASK                     0x08
#घोषणा LOCHNAGAR1_GF_AIF4_ENA_SHIFT                       3
#घोषणा LOCHNAGAR1_GF_AIF2_LRCLK_सूची_MASK               0x04
#घोषणा LOCHNAGAR1_GF_AIF2_LRCLK_सूची_SHIFT                 2
#घोषणा LOCHNAGAR1_GF_AIF2_BCLK_सूची_MASK                0x02
#घोषणा LOCHNAGAR1_GF_AIF2_BCLK_सूची_SHIFT                  1
#घोषणा LOCHNAGAR1_GF_AIF2_ENA_MASK                     0x01
#घोषणा LOCHNAGAR1_GF_AIF2_ENA_SHIFT                       0

/* (0x0016)  PSIA_AIF */
#घोषणा LOCHNAGAR1_PSIA2_LRCLK_सूची_MASK                 0x40
#घोषणा LOCHNAGAR1_PSIA2_LRCLK_सूची_SHIFT                   6
#घोषणा LOCHNAGAR1_PSIA2_BCLK_सूची_MASK                  0x20
#घोषणा LOCHNAGAR1_PSIA2_BCLK_सूची_SHIFT                    5
#घोषणा LOCHNAGAR1_PSIA2_ENA_MASK                       0x10
#घोषणा LOCHNAGAR1_PSIA2_ENA_SHIFT                         4
#घोषणा LOCHNAGAR1_PSIA1_LRCLK_सूची_MASK                 0x04
#घोषणा LOCHNAGAR1_PSIA1_LRCLK_सूची_SHIFT                   2
#घोषणा LOCHNAGAR1_PSIA1_BCLK_सूची_MASK                  0x02
#घोषणा LOCHNAGAR1_PSIA1_BCLK_सूची_SHIFT                    1
#घोषणा LOCHNAGAR1_PSIA1_ENA_MASK                       0x01
#घोषणा LOCHNAGAR1_PSIA1_ENA_SHIFT                         0

/* (0x0029)  RST */
#घोषणा LOCHNAGAR1_DSP_RESET_MASK                       0x02
#घोषणा LOCHNAGAR1_DSP_RESET_SHIFT                         1
#घोषणा LOCHNAGAR1_CDC_RESET_MASK                       0x01
#घोषणा LOCHNAGAR1_CDC_RESET_SHIFT                         0

/* (0x0046)  I2C_CTRL */
#घोषणा LOCHNAGAR1_CDC_CIF_MODE_MASK                    0x01
#घोषणा LOCHNAGAR1_CDC_CIF_MODE_SHIFT                      0

#पूर्ण_अगर
