<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 *  mxl111sf-reg.h - driver क्रम the MaxLinear MXL111SF
 *
 *  Copyright (C) 2010-2014 Michael Krufky <mkrufky@linuxtv.org>
 */

#अगर_अघोषित _DVB_USB_MXL111SF_REG_H_
#घोषणा _DVB_USB_MXL111SF_REG_H_

#घोषणा CHIP_ID_REG                  0xFC
#घोषणा TOP_CHIP_REV_ID_REG          0xFA

#घोषणा V6_SNR_RB_LSB_REG            0x27
#घोषणा V6_SNR_RB_MSB_REG            0x28

#घोषणा V6_N_ACCUMULATE_REG          0x11
#घोषणा V6_RS_AVG_ERRORS_LSB_REG     0x2C
#घोषणा V6_RS_AVG_ERRORS_MSB_REG     0x2D

#घोषणा V6_IRQ_STATUS_REG            0x24
#घोषणा  IRQ_MASK_FEC_LOCK       0x10

#घोषणा V6_SYNC_LOCK_REG             0x28
#घोषणा SYNC_LOCK_MASK           0x10

#घोषणा V6_RS_LOCK_DET_REG           0x28
#घोषणा  RS_LOCK_DET_MASK        0x08

#घोषणा V6_INITACQ_NODETECT_REG    0x20
#घोषणा V6_FORCE_NFFT_CPSIZE_REG   0x20

#घोषणा V6_CODE_RATE_TPS_REG       0x29
#घोषणा V6_CODE_RATE_TPS_MASK      0x07


#घोषणा V6_CP_LOCK_DET_REG        0x28
#घोषणा V6_CP_LOCK_DET_MASK       0x04

#घोषणा V6_TPS_HIERACHY_REG        0x29
#घोषणा V6_TPS_HIERARCHY_INFO_MASK  0x40

#घोषणा V6_MODORDER_TPS_REG        0x2A
#घोषणा V6_PARAM_CONSTELLATION_MASK   0x30

#घोषणा V6_MODE_TPS_REG            0x2A
#घोषणा V6_PARAM_FFT_MODE_MASK        0x0C


#घोषणा V6_CP_TPS_REG             0x29
#घोषणा V6_PARAM_GI_MASK              0x30

#घोषणा V6_TPS_LOCK_REG           0x2A
#घोषणा V6_PARAM_TPS_LOCK_MASK        0x40

#घोषणा V6_FEC_PER_COUNT_REG      0x2E
#घोषणा V6_FEC_PER_SCALE_REG      0x2B
#घोषणा V6_FEC_PER_SCALE_MASK        0x03
#घोषणा V6_FEC_PER_CLR_REG        0x20
#घोषणा V6_FEC_PER_CLR_MASK          0x01

#घोषणा V6_PIN_MUX_MODE_REG       0x1B
#घोषणा V6_ENABLE_PIN_MUX            0x1E

#घोषणा V6_I2S_NUM_SAMPLES_REG    0x16

#घोषणा V6_MPEG_IN_CLK_INV_REG    0x17
#घोषणा V6_MPEG_IN_CTRL_REG       0x18

#घोषणा V6_INVERTED_CLK_PHASE       0x20
#घोषणा V6_MPEG_IN_DATA_PARALLEL    0x01
#घोषणा V6_MPEG_IN_DATA_SERIAL      0x02

#घोषणा V6_INVERTED_MPEG_SYNC       0x04
#घोषणा V6_INVERTED_MPEG_VALID      0x08

#घोषणा TSIF_INPUT_PARALLEL         0
#घोषणा TSIF_INPUT_SERIAL           1
#घोषणा TSIF_NORMAL                 0

#घोषणा V6_MPEG_INOUT_BIT_ORDER_CTRL_REG  0x19
#घोषणा V6_MPEG_SER_MSB_FIRST                0x80
#घोषणा MPEG_SER_MSB_FIRST_ENABLED        0x01

#घोषणा V6_656_I2S_BUFF_STATUS_REG   0x2F
#घोषणा V6_656_OVERFLOW_MASK_BIT         0x08
#घोषणा V6_I2S_OVERFLOW_MASK_BIT         0x01

#घोषणा V6_I2S_STREAM_START_BIT_REG  0x14
#घोषणा V6_I2S_STREAM_END_BIT_REG    0x15
#घोषणा I2S_RIGHT_JUSTIFIED     0
#घोषणा I2S_LEFT_JUSTIFIED      1
#घोषणा I2S_DATA_FORMAT         2

#घोषणा V6_TUNER_LOOP_THRU_CONTROL_REG  0x09
#घोषणा V6_ENABLE_LOOP_THRU               0x01

#घोषणा TOTAL_NUM_IF_OUTPUT_FREQ       16

#घोषणा TUNER_NORMAL_IF_SPECTRUM       0x0
#घोषणा TUNER_INVERT_IF_SPECTRUM       0x10

#घोषणा V6_TUNER_IF_SEL_REG              0x06
#घोषणा V6_TUNER_IF_FCW_REG              0x3C
#घोषणा V6_TUNER_IF_FCW_BYP_REG          0x3D
#घोषणा V6_RF_LOCK_STATUS_REG            0x23

#घोषणा NUM_DIG_TV_CHANNEL     1000

#घोषणा V6_DIG_CLK_FREQ_SEL_REG  0x07
#घोषणा V6_REF_SYNTH_INT_REG     0x5C
#घोषणा V6_REF_SYNTH_REMAIN_REG  0x58
#घोषणा V6_DIG_RFREFSELECT_REG   0x32
#घोषणा V6_XTAL_CLK_OUT_GAIN_REG   0x31
#घोषणा V6_TUNER_LOOP_THRU_CTRL_REG      0x09
#घोषणा V6_DIG_XTAL_ENABLE_REG  0x06
#घोषणा V6_DIG_XTAL_BIAS_REG  0x66
#घोषणा V6_XTAL_CAP_REG    0x08

#घोषणा V6_GPO_CTRL_REG     0x18
#घोषणा MXL_GPO_0           0x00
#घोषणा MXL_GPO_1           0x01
#घोषणा V6_GPO_0_MASK       0x10
#घोषणा V6_GPO_1_MASK       0x20

#घोषणा V6_111SF_GPO_CTRL_REG     0x19
#घोषणा MXL_111SF_GPO_1               0x00
#घोषणा MXL_111SF_GPO_2               0x01
#घोषणा MXL_111SF_GPO_3               0x02
#घोषणा MXL_111SF_GPO_4               0x03
#घोषणा MXL_111SF_GPO_5               0x04
#घोषणा MXL_111SF_GPO_6               0x05
#घोषणा MXL_111SF_GPO_7               0x06

#घोषणा MXL_111SF_GPO_0_MASK          0x01
#घोषणा MXL_111SF_GPO_1_MASK          0x02
#घोषणा MXL_111SF_GPO_2_MASK          0x04
#घोषणा MXL_111SF_GPO_3_MASK          0x08
#घोषणा MXL_111SF_GPO_4_MASK          0x10
#घोषणा MXL_111SF_GPO_5_MASK          0x20
#घोषणा MXL_111SF_GPO_6_MASK          0x40

#घोषणा V6_ATSC_CONFIG_REG  0x0A

#घोषणा MXL_MODE_REG    0x03
#घोषणा START_TUNE_REG  0x1C

#घोषणा V6_IDAC_HYSTERESIS_REG    0x0B
#घोषणा V6_IDAC_SETTINGS_REG      0x0C
#घोषणा IDAC_MANUAL_CONTROL             1
#घोषणा IDAC_CURRENT_SINKING_ENABLE     1
#घोषणा IDAC_MANUAL_CONTROL_BIT_MASK      0x80
#घोषणा IDAC_CURRENT_SINKING_BIT_MASK     0x40

#घोषणा V8_SPI_MODE_REG  0xE9

#घोषणा V6_DIG_RF_PWR_LSB_REG  0x46
#घोषणा V6_DIG_RF_PWR_MSB_REG  0x47

#पूर्ण_अगर /* _DVB_USB_MXL111SF_REG_H_ */
