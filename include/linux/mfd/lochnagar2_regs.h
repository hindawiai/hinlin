<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Lochnagar2 रेजिस्टर definitions
 *
 * Copyright (c) 2017-2018 Cirrus Logic, Inc. and
 *                         Cirrus Logic International Semiconductor Ltd.
 *
 * Author: Charles Keepax <ckeepax@खोलोsource.cirrus.com>
 */

#अगर_अघोषित LOCHNAGAR2_REGISTERS_H
#घोषणा LOCHNAGAR2_REGISTERS_H

/* Register Addresses */
#घोषणा LOCHNAGAR2_CDC_AIF1_CTRL                      0x000D
#घोषणा LOCHNAGAR2_CDC_AIF2_CTRL                      0x000E
#घोषणा LOCHNAGAR2_CDC_AIF3_CTRL                      0x000F
#घोषणा LOCHNAGAR2_DSP_AIF1_CTRL                      0x0010
#घोषणा LOCHNAGAR2_DSP_AIF2_CTRL                      0x0011
#घोषणा LOCHNAGAR2_PSIA1_CTRL                         0x0012
#घोषणा LOCHNAGAR2_PSIA2_CTRL                         0x0013
#घोषणा LOCHNAGAR2_GF_AIF3_CTRL                       0x0014
#घोषणा LOCHNAGAR2_GF_AIF4_CTRL                       0x0015
#घोषणा LOCHNAGAR2_GF_AIF1_CTRL                       0x0016
#घोषणा LOCHNAGAR2_GF_AIF2_CTRL                       0x0017
#घोषणा LOCHNAGAR2_SPDIF_AIF_CTRL                     0x0018
#घोषणा LOCHNAGAR2_USB_AIF1_CTRL                      0x0019
#घोषणा LOCHNAGAR2_USB_AIF2_CTRL                      0x001A
#घोषणा LOCHNAGAR2_ADAT_AIF_CTRL                      0x001B
#घोषणा LOCHNAGAR2_CDC_MCLK1_CTRL                     0x001E
#घोषणा LOCHNAGAR2_CDC_MCLK2_CTRL                     0x001F
#घोषणा LOCHNAGAR2_DSP_CLKIN_CTRL                     0x0020
#घोषणा LOCHNAGAR2_PSIA1_MCLK_CTRL                    0x0021
#घोषणा LOCHNAGAR2_PSIA2_MCLK_CTRL                    0x0022
#घोषणा LOCHNAGAR2_SPDIF_MCLK_CTRL                    0x0023
#घोषणा LOCHNAGAR2_GF_CLKOUT1_CTRL                    0x0024
#घोषणा LOCHNAGAR2_GF_CLKOUT2_CTRL                    0x0025
#घोषणा LOCHNAGAR2_ADAT_MCLK_CTRL                     0x0026
#घोषणा LOCHNAGAR2_SOUNDCARD_MCLK_CTRL                0x0027
#घोषणा LOCHNAGAR2_GPIO_FPGA_GPIO1                    0x0031
#घोषणा LOCHNAGAR2_GPIO_FPGA_GPIO2                    0x0032
#घोषणा LOCHNAGAR2_GPIO_FPGA_GPIO3                    0x0033
#घोषणा LOCHNAGAR2_GPIO_FPGA_GPIO4                    0x0034
#घोषणा LOCHNAGAR2_GPIO_FPGA_GPIO5                    0x0035
#घोषणा LOCHNAGAR2_GPIO_FPGA_GPIO6                    0x0036
#घोषणा LOCHNAGAR2_GPIO_CDC_GPIO1                     0x0037
#घोषणा LOCHNAGAR2_GPIO_CDC_GPIO2                     0x0038
#घोषणा LOCHNAGAR2_GPIO_CDC_GPIO3                     0x0039
#घोषणा LOCHNAGAR2_GPIO_CDC_GPIO4                     0x003A
#घोषणा LOCHNAGAR2_GPIO_CDC_GPIO5                     0x003B
#घोषणा LOCHNAGAR2_GPIO_CDC_GPIO6                     0x003C
#घोषणा LOCHNAGAR2_GPIO_CDC_GPIO7                     0x003D
#घोषणा LOCHNAGAR2_GPIO_CDC_GPIO8                     0x003E
#घोषणा LOCHNAGAR2_GPIO_DSP_GPIO1                     0x003F
#घोषणा LOCHNAGAR2_GPIO_DSP_GPIO2                     0x0040
#घोषणा LOCHNAGAR2_GPIO_DSP_GPIO3                     0x0041
#घोषणा LOCHNAGAR2_GPIO_DSP_GPIO4                     0x0042
#घोषणा LOCHNAGAR2_GPIO_DSP_GPIO5                     0x0043
#घोषणा LOCHNAGAR2_GPIO_DSP_GPIO6                     0x0044
#घोषणा LOCHNAGAR2_GPIO_GF_GPIO2                      0x0045
#घोषणा LOCHNAGAR2_GPIO_GF_GPIO3                      0x0046
#घोषणा LOCHNAGAR2_GPIO_GF_GPIO7                      0x0047
#घोषणा LOCHNAGAR2_GPIO_CDC_AIF1_BCLK                 0x0048
#घोषणा LOCHNAGAR2_GPIO_CDC_AIF1_RXDAT                0x0049
#घोषणा LOCHNAGAR2_GPIO_CDC_AIF1_LRCLK                0x004A
#घोषणा LOCHNAGAR2_GPIO_CDC_AIF1_TXDAT                0x004B
#घोषणा LOCHNAGAR2_GPIO_CDC_AIF2_BCLK                 0x004C
#घोषणा LOCHNAGAR2_GPIO_CDC_AIF2_RXDAT                0x004D
#घोषणा LOCHNAGAR2_GPIO_CDC_AIF2_LRCLK                0x004E
#घोषणा LOCHNAGAR2_GPIO_CDC_AIF2_TXDAT                0x004F
#घोषणा LOCHNAGAR2_GPIO_CDC_AIF3_BCLK                 0x0050
#घोषणा LOCHNAGAR2_GPIO_CDC_AIF3_RXDAT                0x0051
#घोषणा LOCHNAGAR2_GPIO_CDC_AIF3_LRCLK                0x0052
#घोषणा LOCHNAGAR2_GPIO_CDC_AIF3_TXDAT                0x0053
#घोषणा LOCHNAGAR2_GPIO_DSP_AIF1_BCLK                 0x0054
#घोषणा LOCHNAGAR2_GPIO_DSP_AIF1_RXDAT                0x0055
#घोषणा LOCHNAGAR2_GPIO_DSP_AIF1_LRCLK                0x0056
#घोषणा LOCHNAGAR2_GPIO_DSP_AIF1_TXDAT                0x0057
#घोषणा LOCHNAGAR2_GPIO_DSP_AIF2_BCLK                 0x0058
#घोषणा LOCHNAGAR2_GPIO_DSP_AIF2_RXDAT                0x0059
#घोषणा LOCHNAGAR2_GPIO_DSP_AIF2_LRCLK                0x005A
#घोषणा LOCHNAGAR2_GPIO_DSP_AIF2_TXDAT                0x005B
#घोषणा LOCHNAGAR2_GPIO_PSIA1_BCLK                    0x005C
#घोषणा LOCHNAGAR2_GPIO_PSIA1_RXDAT                   0x005D
#घोषणा LOCHNAGAR2_GPIO_PSIA1_LRCLK                   0x005E
#घोषणा LOCHNAGAR2_GPIO_PSIA1_TXDAT                   0x005F
#घोषणा LOCHNAGAR2_GPIO_PSIA2_BCLK                    0x0060
#घोषणा LOCHNAGAR2_GPIO_PSIA2_RXDAT                   0x0061
#घोषणा LOCHNAGAR2_GPIO_PSIA2_LRCLK                   0x0062
#घोषणा LOCHNAGAR2_GPIO_PSIA2_TXDAT                   0x0063
#घोषणा LOCHNAGAR2_GPIO_GF_AIF3_BCLK                  0x0064
#घोषणा LOCHNAGAR2_GPIO_GF_AIF3_RXDAT                 0x0065
#घोषणा LOCHNAGAR2_GPIO_GF_AIF3_LRCLK                 0x0066
#घोषणा LOCHNAGAR2_GPIO_GF_AIF3_TXDAT                 0x0067
#घोषणा LOCHNAGAR2_GPIO_GF_AIF4_BCLK                  0x0068
#घोषणा LOCHNAGAR2_GPIO_GF_AIF4_RXDAT                 0x0069
#घोषणा LOCHNAGAR2_GPIO_GF_AIF4_LRCLK                 0x006A
#घोषणा LOCHNAGAR2_GPIO_GF_AIF4_TXDAT                 0x006B
#घोषणा LOCHNAGAR2_GPIO_GF_AIF1_BCLK                  0x006C
#घोषणा LOCHNAGAR2_GPIO_GF_AIF1_RXDAT                 0x006D
#घोषणा LOCHNAGAR2_GPIO_GF_AIF1_LRCLK                 0x006E
#घोषणा LOCHNAGAR2_GPIO_GF_AIF1_TXDAT                 0x006F
#घोषणा LOCHNAGAR2_GPIO_GF_AIF2_BCLK                  0x0070
#घोषणा LOCHNAGAR2_GPIO_GF_AIF2_RXDAT                 0x0071
#घोषणा LOCHNAGAR2_GPIO_GF_AIF2_LRCLK                 0x0072
#घोषणा LOCHNAGAR2_GPIO_GF_AIF2_TXDAT                 0x0073
#घोषणा LOCHNAGAR2_GPIO_DSP_UART1_RX                  0x0074
#घोषणा LOCHNAGAR2_GPIO_DSP_UART1_TX                  0x0075
#घोषणा LOCHNAGAR2_GPIO_DSP_UART2_RX                  0x0076
#घोषणा LOCHNAGAR2_GPIO_DSP_UART2_TX                  0x0077
#घोषणा LOCHNAGAR2_GPIO_GF_UART2_RX                   0x0078
#घोषणा LOCHNAGAR2_GPIO_GF_UART2_TX                   0x0079
#घोषणा LOCHNAGAR2_GPIO_USB_UART_RX                   0x007A
#घोषणा LOCHNAGAR2_GPIO_CDC_PDMCLK1                   0x007C
#घोषणा LOCHNAGAR2_GPIO_CDC_PDMDAT1                   0x007D
#घोषणा LOCHNAGAR2_GPIO_CDC_PDMCLK2                   0x007E
#घोषणा LOCHNAGAR2_GPIO_CDC_PDMDAT2                   0x007F
#घोषणा LOCHNAGAR2_GPIO_CDC_DMICCLK1                  0x0080
#घोषणा LOCHNAGAR2_GPIO_CDC_DMICDAT1                  0x0081
#घोषणा LOCHNAGAR2_GPIO_CDC_DMICCLK2                  0x0082
#घोषणा LOCHNAGAR2_GPIO_CDC_DMICDAT2                  0x0083
#घोषणा LOCHNAGAR2_GPIO_CDC_DMICCLK3                  0x0084
#घोषणा LOCHNAGAR2_GPIO_CDC_DMICDAT3                  0x0085
#घोषणा LOCHNAGAR2_GPIO_CDC_DMICCLK4                  0x0086
#घोषणा LOCHNAGAR2_GPIO_CDC_DMICDAT4                  0x0087
#घोषणा LOCHNAGAR2_GPIO_DSP_DMICCLK1                  0x0088
#घोषणा LOCHNAGAR2_GPIO_DSP_DMICDAT1                  0x0089
#घोषणा LOCHNAGAR2_GPIO_DSP_DMICCLK2                  0x008A
#घोषणा LOCHNAGAR2_GPIO_DSP_DMICDAT2                  0x008B
#घोषणा LOCHNAGAR2_GPIO_I2C2_SCL                      0x008C
#घोषणा LOCHNAGAR2_GPIO_I2C2_SDA                      0x008D
#घोषणा LOCHNAGAR2_GPIO_I2C3_SCL                      0x008E
#घोषणा LOCHNAGAR2_GPIO_I2C3_SDA                      0x008F
#घोषणा LOCHNAGAR2_GPIO_I2C4_SCL                      0x0090
#घोषणा LOCHNAGAR2_GPIO_I2C4_SDA                      0x0091
#घोषणा LOCHNAGAR2_GPIO_DSP_STANDBY                   0x0092
#घोषणा LOCHNAGAR2_GPIO_CDC_MCLK1                     0x0093
#घोषणा LOCHNAGAR2_GPIO_CDC_MCLK2                     0x0094
#घोषणा LOCHNAGAR2_GPIO_DSP_CLKIN                     0x0095
#घोषणा LOCHNAGAR2_GPIO_PSIA1_MCLK                    0x0096
#घोषणा LOCHNAGAR2_GPIO_PSIA2_MCLK                    0x0097
#घोषणा LOCHNAGAR2_GPIO_GF_GPIO1                      0x0098
#घोषणा LOCHNAGAR2_GPIO_GF_GPIO5                      0x0099
#घोषणा LOCHNAGAR2_GPIO_DSP_GPIO20                    0x009A
#घोषणा LOCHNAGAR2_GPIO_CHANNEL1                      0x00B9
#घोषणा LOCHNAGAR2_GPIO_CHANNEL2                      0x00BA
#घोषणा LOCHNAGAR2_GPIO_CHANNEL3                      0x00BB
#घोषणा LOCHNAGAR2_GPIO_CHANNEL4                      0x00BC
#घोषणा LOCHNAGAR2_GPIO_CHANNEL5                      0x00BD
#घोषणा LOCHNAGAR2_GPIO_CHANNEL6                      0x00BE
#घोषणा LOCHNAGAR2_GPIO_CHANNEL7                      0x00BF
#घोषणा LOCHNAGAR2_GPIO_CHANNEL8                      0x00C0
#घोषणा LOCHNAGAR2_GPIO_CHANNEL9                      0x00C1
#घोषणा LOCHNAGAR2_GPIO_CHANNEL10                     0x00C2
#घोषणा LOCHNAGAR2_GPIO_CHANNEL11                     0x00C3
#घोषणा LOCHNAGAR2_GPIO_CHANNEL12                     0x00C4
#घोषणा LOCHNAGAR2_GPIO_CHANNEL13                     0x00C5
#घोषणा LOCHNAGAR2_GPIO_CHANNEL14                     0x00C6
#घोषणा LOCHNAGAR2_GPIO_CHANNEL15                     0x00C7
#घोषणा LOCHNAGAR2_GPIO_CHANNEL16                     0x00C8
#घोषणा LOCHNAGAR2_MINICARD_RESETS                    0x00DF
#घोषणा LOCHNAGAR2_ANALOGUE_PATH_CTRL1                0x00E3
#घोषणा LOCHNAGAR2_ANALOGUE_PATH_CTRL2                0x00E4
#घोषणा LOCHNAGAR2_COMMS_CTRL4                        0x00F0
#घोषणा LOCHNAGAR2_SPDIF_CTRL                         0x00FE
#घोषणा LOCHNAGAR2_IMON_CTRL1                         0x0108
#घोषणा LOCHNAGAR2_IMON_CTRL2                         0x0109
#घोषणा LOCHNAGAR2_IMON_CTRL3                         0x010A
#घोषणा LOCHNAGAR2_IMON_CTRL4                         0x010B
#घोषणा LOCHNAGAR2_IMON_DATA1                         0x010C
#घोषणा LOCHNAGAR2_IMON_DATA2                         0x010D
#घोषणा LOCHNAGAR2_POWER_CTRL                         0x0116
#घोषणा LOCHNAGAR2_MICVDD_CTRL1                       0x0119
#घोषणा LOCHNAGAR2_MICVDD_CTRL2                       0x011B
#घोषणा LOCHNAGAR2_VDDCORE_CDC_CTRL1                  0x011E
#घोषणा LOCHNAGAR2_VDDCORE_CDC_CTRL2                  0x0120
#घोषणा LOCHNAGAR2_SOUNDCARD_AIF_CTRL                 0x0180

/* (0x000D-0x001B, 0x0180)  CDC_AIF1_CTRL - SOUNCARD_AIF_CTRL */
#घोषणा LOCHNAGAR2_AIF_ENA_MASK                       0x8000
#घोषणा LOCHNAGAR2_AIF_ENA_SHIFT                          15
#घोषणा LOCHNAGAR2_AIF_LRCLK_सूची_MASK                 0x4000
#घोषणा LOCHNAGAR2_AIF_LRCLK_सूची_SHIFT                    14
#घोषणा LOCHNAGAR2_AIF_BCLK_सूची_MASK                  0x2000
#घोषणा LOCHNAGAR2_AIF_BCLK_सूची_SHIFT                     13
#घोषणा LOCHNAGAR2_AIF_SRC_MASK                       0x00FF
#घोषणा LOCHNAGAR2_AIF_SRC_SHIFT                           0

/* (0x001E - 0x0027)  CDC_MCLK1_CTRL - SOUNDCARD_MCLK_CTRL */
#घोषणा LOCHNAGAR2_CLK_ENA_MASK                       0x8000
#घोषणा LOCHNAGAR2_CLK_ENA_SHIFT                          15
#घोषणा LOCHNAGAR2_CLK_SRC_MASK                       0x00FF
#घोषणा LOCHNAGAR2_CLK_SRC_SHIFT                           0

/* (0x0031 - 0x009A)  GPIO_FPGA_GPIO1 - GPIO_DSP_GPIO20 */
#घोषणा LOCHNAGAR2_GPIO_SRC_MASK                      0x00FF
#घोषणा LOCHNAGAR2_GPIO_SRC_SHIFT                          0

/* (0x00B9 - 0x00C8)  GPIO_CHANNEL1 - GPIO_CHANNEL16 */
#घोषणा LOCHNAGAR2_GPIO_CHANNEL_STS_MASK              0x8000
#घोषणा LOCHNAGAR2_GPIO_CHANNEL_STS_SHIFT                 15
#घोषणा LOCHNAGAR2_GPIO_CHANNEL_SRC_MASK              0x00FF
#घोषणा LOCHNAGAR2_GPIO_CHANNEL_SRC_SHIFT                  0

/* (0x00DF)  MINICARD_RESETS */
#घोषणा LOCHNAGAR2_DSP_RESET_MASK                     0x0002
#घोषणा LOCHNAGAR2_DSP_RESET_SHIFT                         1
#घोषणा LOCHNAGAR2_CDC_RESET_MASK                     0x0001
#घोषणा LOCHNAGAR2_CDC_RESET_SHIFT                         0

/* (0x00E3)  ANALOGUE_PATH_CTRL1 */
#घोषणा LOCHNAGAR2_ANALOGUE_PATH_UPDATE_MASK          0x8000
#घोषणा LOCHNAGAR2_ANALOGUE_PATH_UPDATE_SHIFT             15
#घोषणा LOCHNAGAR2_ANALOGUE_PATH_UPDATE_STS_MASK      0x4000
#घोषणा LOCHNAGAR2_ANALOGUE_PATH_UPDATE_STS_SHIFT         14

/* (0x00E4)  ANALOGUE_PATH_CTRL2 */
#घोषणा LOCHNAGAR2_P2_INPUT_BIAS_ENA_MASK             0x0080
#घोषणा LOCHNAGAR2_P2_INPUT_BIAS_ENA_SHIFT                 7
#घोषणा LOCHNAGAR2_P1_INPUT_BIAS_ENA_MASK             0x0040
#घोषणा LOCHNAGAR2_P1_INPUT_BIAS_ENA_SHIFT                 6
#घोषणा LOCHNAGAR2_P2_MICBIAS_SRC_MASK                0x0038
#घोषणा LOCHNAGAR2_P2_MICBIAS_SRC_SHIFT                    3
#घोषणा LOCHNAGAR2_P1_MICBIAS_SRC_MASK                0x0007
#घोषणा LOCHNAGAR2_P1_MICBIAS_SRC_SHIFT                    0

/* (0x00F0)  COMMS_CTRL4 */
#घोषणा LOCHNAGAR2_CDC_CIF1MODE_MASK                  0x0001
#घोषणा LOCHNAGAR2_CDC_CIF1MODE_SHIFT                      0

/* (0x00FE)  SPDIF_CTRL */
#घोषणा LOCHNAGAR2_SPDIF_HWMODE_MASK                  0x0008
#घोषणा LOCHNAGAR2_SPDIF_HWMODE_SHIFT                      3
#घोषणा LOCHNAGAR2_SPDIF_RESET_MASK                   0x0001
#घोषणा LOCHNAGAR2_SPDIF_RESET_SHIFT                       0

/* (0x0108)  IMON_CTRL1 */
#घोषणा LOCHNAGAR2_IMON_ENA_MASK                      0x8000
#घोषणा LOCHNAGAR2_IMON_ENA_SHIFT                         15
#घोषणा LOCHNAGAR2_IMON_MEASURED_CHANNELS_MASK        0x03FC
#घोषणा LOCHNAGAR2_IMON_MEASURED_CHANNELS_SHIFT            2
#घोषणा LOCHNAGAR2_IMON_MODE_SEL_MASK                 0x0003
#घोषणा LOCHNAGAR2_IMON_MODE_SEL_SHIFT                     0

/* (0x0109)  IMON_CTRL2 */
#घोषणा LOCHNAGAR2_IMON_FSR_MASK                      0x03FF
#घोषणा LOCHNAGAR2_IMON_FSR_SHIFT                          0

/* (0x010A)  IMON_CTRL3 */
#घोषणा LOCHNAGAR2_IMON_DONE_MASK                     0x0004
#घोषणा LOCHNAGAR2_IMON_DONE_SHIFT                         2
#घोषणा LOCHNAGAR2_IMON_CONFIGURE_MASK                0x0002
#घोषणा LOCHNAGAR2_IMON_CONFIGURE_SHIFT                    1
#घोषणा LOCHNAGAR2_IMON_MEASURE_MASK                  0x0001
#घोषणा LOCHNAGAR2_IMON_MEASURE_SHIFT                      0

/* (0x010B)  IMON_CTRL4 */
#घोषणा LOCHNAGAR2_IMON_DATA_REQ_MASK                 0x0080
#घोषणा LOCHNAGAR2_IMON_DATA_REQ_SHIFT                     7
#घोषणा LOCHNAGAR2_IMON_CH_SEL_MASK                   0x0070
#घोषणा LOCHNAGAR2_IMON_CH_SEL_SHIFT                       4
#घोषणा LOCHNAGAR2_IMON_DATA_RDY_MASK                 0x0008
#घोषणा LOCHNAGAR2_IMON_DATA_RDY_SHIFT                     3
#घोषणा LOCHNAGAR2_IMON_CH_SRC_MASK                   0x0007
#घोषणा LOCHNAGAR2_IMON_CH_SRC_SHIFT                       0

/* (0x010C, 0x010D)  IMON_DATA1, IMON_DATA2 */
#घोषणा LOCHNAGAR2_IMON_DATA_MASK                     0xFFFF
#घोषणा LOCHNAGAR2_IMON_DATA_SHIFT                         0

/* (0x0116)  POWER_CTRL */
#घोषणा LOCHNAGAR2_PWR_ENA_MASK                       0x0001
#घोषणा LOCHNAGAR2_PWR_ENA_SHIFT                           0

/* (0x0119)  MICVDD_CTRL1 */
#घोषणा LOCHNAGAR2_MICVDD_REG_ENA_MASK                0x8000
#घोषणा LOCHNAGAR2_MICVDD_REG_ENA_SHIFT                   15

/* (0x011B)  MICVDD_CTRL2 */
#घोषणा LOCHNAGAR2_MICVDD_VSEL_MASK                   0x001F
#घोषणा LOCHNAGAR2_MICVDD_VSEL_SHIFT                       0

/* (0x011E)  VDDCORE_CDC_CTRL1 */
#घोषणा LOCHNAGAR2_VDDCORE_CDC_REG_ENA_MASK           0x8000
#घोषणा LOCHNAGAR2_VDDCORE_CDC_REG_ENA_SHIFT              15

/* (0x0120)  VDDCORE_CDC_CTRL2 */
#घोषणा LOCHNAGAR2_VDDCORE_CDC_VSEL_MASK              0x007F
#घोषणा LOCHNAGAR2_VDDCORE_CDC_VSEL_SHIFT                  0

#पूर्ण_अगर
