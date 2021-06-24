<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * wm8961.h  --  WM8961 Soc Audio driver
 */

#अगर_अघोषित _WM8961_H
#घोषणा _WM8961_H

#समावेश <sound/soc.h>

#घोषणा WM8961_BCLK  1
#घोषणा WM8961_LRCLK 2

#घोषणा WM8961_BCLK_DIV_1    0
#घोषणा WM8961_BCLK_DIV_1_5  1
#घोषणा WM8961_BCLK_DIV_2    2
#घोषणा WM8961_BCLK_DIV_3    3
#घोषणा WM8961_BCLK_DIV_4    4
#घोषणा WM8961_BCLK_DIV_5_5  5
#घोषणा WM8961_BCLK_DIV_6    6
#घोषणा WM8961_BCLK_DIV_8    7
#घोषणा WM8961_BCLK_DIV_11   8
#घोषणा WM8961_BCLK_DIV_12   9
#घोषणा WM8961_BCLK_DIV_16  10
#घोषणा WM8961_BCLK_DIV_24  11
#घोषणा WM8961_BCLK_DIV_32  13


/*
 * Register values.
 */
#घोषणा WM8961_LEFT_INPUT_VOLUME                0x00
#घोषणा WM8961_RIGHT_INPUT_VOLUME               0x01
#घोषणा WM8961_LOUT1_VOLUME                     0x02
#घोषणा WM8961_ROUT1_VOLUME                     0x03
#घोषणा WM8961_CLOCKING1                        0x04
#घोषणा WM8961_ADC_DAC_CONTROL_1                0x05
#घोषणा WM8961_ADC_DAC_CONTROL_2                0x06
#घोषणा WM8961_AUDIO_INTERFACE_0                0x07
#घोषणा WM8961_CLOCKING2                        0x08
#घोषणा WM8961_AUDIO_INTERFACE_1                0x09
#घोषणा WM8961_LEFT_DAC_VOLUME                  0x0A
#घोषणा WM8961_RIGHT_DAC_VOLUME                 0x0B
#घोषणा WM8961_AUDIO_INTERFACE_2                0x0E
#घोषणा WM8961_SOFTWARE_RESET                   0x0F
#घोषणा WM8961_ALC1                             0x11
#घोषणा WM8961_ALC2                             0x12
#घोषणा WM8961_ALC3                             0x13
#घोषणा WM8961_NOISE_GATE                       0x14
#घोषणा WM8961_LEFT_ADC_VOLUME                  0x15
#घोषणा WM8961_RIGHT_ADC_VOLUME                 0x16
#घोषणा WM8961_ADDITIONAL_CONTROL_1             0x17
#घोषणा WM8961_ADDITIONAL_CONTROL_2             0x18
#घोषणा WM8961_PWR_MGMT_1                       0x19
#घोषणा WM8961_PWR_MGMT_2                       0x1A
#घोषणा WM8961_ADDITIONAL_CONTROL_3             0x1B
#घोषणा WM8961_ANTI_POP                         0x1C
#घोषणा WM8961_CLOCKING_3                       0x1E
#घोषणा WM8961_ADCL_SIGNAL_PATH                 0x20
#घोषणा WM8961_ADCR_SIGNAL_PATH                 0x21
#घोषणा WM8961_LOUT2_VOLUME                     0x28
#घोषणा WM8961_ROUT2_VOLUME                     0x29
#घोषणा WM8961_PWR_MGMT_3                       0x2F
#घोषणा WM8961_ADDITIONAL_CONTROL_4             0x30
#घोषणा WM8961_CLASS_D_CONTROL_1                0x31
#घोषणा WM8961_CLASS_D_CONTROL_2                0x33
#घोषणा WM8961_CLOCKING_4                       0x38
#घोषणा WM8961_DSP_SIDETONE_0                   0x39
#घोषणा WM8961_DSP_SIDETONE_1                   0x3A
#घोषणा WM8961_DC_SERVO_0                       0x3C
#घोषणा WM8961_DC_SERVO_1                       0x3D
#घोषणा WM8961_DC_SERVO_3                       0x3F
#घोषणा WM8961_DC_SERVO_5                       0x41
#घोषणा WM8961_ANALOGUE_PGA_BIAS                0x44
#घोषणा WM8961_ANALOGUE_HP_0                    0x45
#घोषणा WM8961_ANALOGUE_HP_2                    0x47
#घोषणा WM8961_CHARGE_PUMP_1                    0x48
#घोषणा WM8961_CHARGE_PUMP_B                    0x52
#घोषणा WM8961_WRITE_SEQUENCER_1                0x57
#घोषणा WM8961_WRITE_SEQUENCER_2                0x58
#घोषणा WM8961_WRITE_SEQUENCER_3                0x59
#घोषणा WM8961_WRITE_SEQUENCER_4                0x5A
#घोषणा WM8961_WRITE_SEQUENCER_5                0x5B
#घोषणा WM8961_WRITE_SEQUENCER_6                0x5C
#घोषणा WM8961_WRITE_SEQUENCER_7                0x5D
#घोषणा WM8961_GENERAL_TEST_1                   0xFC


/*
 * Field Definitions.
 */

/*
 * R0 (0x00) - Left Input volume
 */
#घोषणा WM8961_IPVU                             0x0100  /* IPVU */
#घोषणा WM8961_IPVU_MASK                        0x0100  /* IPVU */
#घोषणा WM8961_IPVU_SHIFT                            8  /* IPVU */
#घोषणा WM8961_IPVU_WIDTH                            1  /* IPVU */
#घोषणा WM8961_LINMUTE                          0x0080  /* LINMUTE */
#घोषणा WM8961_LINMUTE_MASK                     0x0080  /* LINMUTE */
#घोषणा WM8961_LINMUTE_SHIFT                         7  /* LINMUTE */
#घोषणा WM8961_LINMUTE_WIDTH                         1  /* LINMUTE */
#घोषणा WM8961_LIZC                             0x0040  /* LIZC */
#घोषणा WM8961_LIZC_MASK                        0x0040  /* LIZC */
#घोषणा WM8961_LIZC_SHIFT                            6  /* LIZC */
#घोषणा WM8961_LIZC_WIDTH                            1  /* LIZC */
#घोषणा WM8961_LINVOL_MASK                      0x003F  /* LINVOL - [5:0] */
#घोषणा WM8961_LINVOL_SHIFT                          0  /* LINVOL - [5:0] */
#घोषणा WM8961_LINVOL_WIDTH                          6  /* LINVOL - [5:0] */

/*
 * R1 (0x01) - Right Input volume
 */
#घोषणा WM8961_DEVICE_ID_MASK                   0xF000  /* DEVICE_ID - [15:12] */
#घोषणा WM8961_DEVICE_ID_SHIFT                      12  /* DEVICE_ID - [15:12] */
#घोषणा WM8961_DEVICE_ID_WIDTH                       4  /* DEVICE_ID - [15:12] */
#घोषणा WM8961_CHIP_REV_MASK                    0x0E00  /* CHIP_REV - [11:9] */
#घोषणा WM8961_CHIP_REV_SHIFT                        9  /* CHIP_REV - [11:9] */
#घोषणा WM8961_CHIP_REV_WIDTH                        3  /* CHIP_REV - [11:9] */
#घोषणा WM8961_IPVU                             0x0100  /* IPVU */
#घोषणा WM8961_IPVU_MASK                        0x0100  /* IPVU */
#घोषणा WM8961_IPVU_SHIFT                            8  /* IPVU */
#घोषणा WM8961_IPVU_WIDTH                            1  /* IPVU */
#घोषणा WM8961_RINMUTE                          0x0080  /* RINMUTE */
#घोषणा WM8961_RINMUTE_MASK                     0x0080  /* RINMUTE */
#घोषणा WM8961_RINMUTE_SHIFT                         7  /* RINMUTE */
#घोषणा WM8961_RINMUTE_WIDTH                         1  /* RINMUTE */
#घोषणा WM8961_RIZC                             0x0040  /* RIZC */
#घोषणा WM8961_RIZC_MASK                        0x0040  /* RIZC */
#घोषणा WM8961_RIZC_SHIFT                            6  /* RIZC */
#घोषणा WM8961_RIZC_WIDTH                            1  /* RIZC */
#घोषणा WM8961_RINVOL_MASK                      0x003F  /* RINVOL - [5:0] */
#घोषणा WM8961_RINVOL_SHIFT                          0  /* RINVOL - [5:0] */
#घोषणा WM8961_RINVOL_WIDTH                          6  /* RINVOL - [5:0] */

/*
 * R2 (0x02) - LOUT1 volume
 */
#घोषणा WM8961_OUT1VU                           0x0100  /* OUT1VU */
#घोषणा WM8961_OUT1VU_MASK                      0x0100  /* OUT1VU */
#घोषणा WM8961_OUT1VU_SHIFT                          8  /* OUT1VU */
#घोषणा WM8961_OUT1VU_WIDTH                          1  /* OUT1VU */
#घोषणा WM8961_LO1ZC                            0x0080  /* LO1ZC */
#घोषणा WM8961_LO1ZC_MASK                       0x0080  /* LO1ZC */
#घोषणा WM8961_LO1ZC_SHIFT                           7  /* LO1ZC */
#घोषणा WM8961_LO1ZC_WIDTH                           1  /* LO1ZC */
#घोषणा WM8961_LOUT1VOL_MASK                    0x007F  /* LOUT1VOL - [6:0] */
#घोषणा WM8961_LOUT1VOL_SHIFT                        0  /* LOUT1VOL - [6:0] */
#घोषणा WM8961_LOUT1VOL_WIDTH                        7  /* LOUT1VOL - [6:0] */

/*
 * R3 (0x03) - ROUT1 volume
 */
#घोषणा WM8961_OUT1VU                           0x0100  /* OUT1VU */
#घोषणा WM8961_OUT1VU_MASK                      0x0100  /* OUT1VU */
#घोषणा WM8961_OUT1VU_SHIFT                          8  /* OUT1VU */
#घोषणा WM8961_OUT1VU_WIDTH                          1  /* OUT1VU */
#घोषणा WM8961_RO1ZC                            0x0080  /* RO1ZC */
#घोषणा WM8961_RO1ZC_MASK                       0x0080  /* RO1ZC */
#घोषणा WM8961_RO1ZC_SHIFT                           7  /* RO1ZC */
#घोषणा WM8961_RO1ZC_WIDTH                           1  /* RO1ZC */
#घोषणा WM8961_ROUT1VOL_MASK                    0x007F  /* ROUT1VOL - [6:0] */
#घोषणा WM8961_ROUT1VOL_SHIFT                        0  /* ROUT1VOL - [6:0] */
#घोषणा WM8961_ROUT1VOL_WIDTH                        7  /* ROUT1VOL - [6:0] */

/*
 * R4 (0x04) - Clocking1
 */
#घोषणा WM8961_ADCDIV_MASK                      0x01C0  /* ADCDIV - [8:6] */
#घोषणा WM8961_ADCDIV_SHIFT                          6  /* ADCDIV - [8:6] */
#घोषणा WM8961_ADCDIV_WIDTH                          3  /* ADCDIV - [8:6] */
#घोषणा WM8961_DACDIV_MASK                      0x0038  /* DACDIV - [5:3] */
#घोषणा WM8961_DACDIV_SHIFT                          3  /* DACDIV - [5:3] */
#घोषणा WM8961_DACDIV_WIDTH                          3  /* DACDIV - [5:3] */
#घोषणा WM8961_MCLKDIV                          0x0004  /* MCLKDIV */
#घोषणा WM8961_MCLKDIV_MASK                     0x0004  /* MCLKDIV */
#घोषणा WM8961_MCLKDIV_SHIFT                         2  /* MCLKDIV */
#घोषणा WM8961_MCLKDIV_WIDTH                         1  /* MCLKDIV */

/*
 * R5 (0x05) - ADC & DAC Control 1
 */
#घोषणा WM8961_ADCPOL_MASK                      0x0060  /* ADCPOL - [6:5] */
#घोषणा WM8961_ADCPOL_SHIFT                          5  /* ADCPOL - [6:5] */
#घोषणा WM8961_ADCPOL_WIDTH                          2  /* ADCPOL - [6:5] */
#घोषणा WM8961_DACMU                            0x0008  /* DACMU */
#घोषणा WM8961_DACMU_MASK                       0x0008  /* DACMU */
#घोषणा WM8961_DACMU_SHIFT                           3  /* DACMU */
#घोषणा WM8961_DACMU_WIDTH                           1  /* DACMU */
#घोषणा WM8961_DEEMPH_MASK                      0x0006  /* DEEMPH - [2:1] */
#घोषणा WM8961_DEEMPH_SHIFT                          1  /* DEEMPH - [2:1] */
#घोषणा WM8961_DEEMPH_WIDTH                          2  /* DEEMPH - [2:1] */
#घोषणा WM8961_ADCHPD                           0x0001  /* ADCHPD */
#घोषणा WM8961_ADCHPD_MASK                      0x0001  /* ADCHPD */
#घोषणा WM8961_ADCHPD_SHIFT                          0  /* ADCHPD */
#घोषणा WM8961_ADCHPD_WIDTH                          1  /* ADCHPD */

/*
 * R6 (0x06) - ADC & DAC Control 2
 */
#घोषणा WM8961_ADC_HPF_CUT_MASK                 0x0180  /* ADC_HPF_CUT - [8:7] */
#घोषणा WM8961_ADC_HPF_CUT_SHIFT                     7  /* ADC_HPF_CUT - [8:7] */
#घोषणा WM8961_ADC_HPF_CUT_WIDTH                     2  /* ADC_HPF_CUT - [8:7] */
#घोषणा WM8961_DACPOL_MASK                      0x0060  /* DACPOL - [6:5] */
#घोषणा WM8961_DACPOL_SHIFT                          5  /* DACPOL - [6:5] */
#घोषणा WM8961_DACPOL_WIDTH                          2  /* DACPOL - [6:5] */
#घोषणा WM8961_DACSMM                           0x0008  /* DACSMM */
#घोषणा WM8961_DACSMM_MASK                      0x0008  /* DACSMM */
#घोषणा WM8961_DACSMM_SHIFT                          3  /* DACSMM */
#घोषणा WM8961_DACSMM_WIDTH                          1  /* DACSMM */
#घोषणा WM8961_DACMR                            0x0004  /* DACMR */
#घोषणा WM8961_DACMR_MASK                       0x0004  /* DACMR */
#घोषणा WM8961_DACMR_SHIFT                           2  /* DACMR */
#घोषणा WM8961_DACMR_WIDTH                           1  /* DACMR */
#घोषणा WM8961_DACSLOPE                         0x0002  /* DACSLOPE */
#घोषणा WM8961_DACSLOPE_MASK                    0x0002  /* DACSLOPE */
#घोषणा WM8961_DACSLOPE_SHIFT                        1  /* DACSLOPE */
#घोषणा WM8961_DACSLOPE_WIDTH                        1  /* DACSLOPE */
#घोषणा WM8961_DAC_OSR128                       0x0001  /* DAC_OSR128 */
#घोषणा WM8961_DAC_OSR128_MASK                  0x0001  /* DAC_OSR128 */
#घोषणा WM8961_DAC_OSR128_SHIFT                      0  /* DAC_OSR128 */
#घोषणा WM8961_DAC_OSR128_WIDTH                      1  /* DAC_OSR128 */

/*
 * R7 (0x07) - Audio Interface 0
 */
#घोषणा WM8961_ALRSWAP                          0x0100  /* ALRSWAP */
#घोषणा WM8961_ALRSWAP_MASK                     0x0100  /* ALRSWAP */
#घोषणा WM8961_ALRSWAP_SHIFT                         8  /* ALRSWAP */
#घोषणा WM8961_ALRSWAP_WIDTH                         1  /* ALRSWAP */
#घोषणा WM8961_BCLKINV                          0x0080  /* BCLKINV */
#घोषणा WM8961_BCLKINV_MASK                     0x0080  /* BCLKINV */
#घोषणा WM8961_BCLKINV_SHIFT                         7  /* BCLKINV */
#घोषणा WM8961_BCLKINV_WIDTH                         1  /* BCLKINV */
#घोषणा WM8961_MS                               0x0040  /* MS */
#घोषणा WM8961_MS_MASK                          0x0040  /* MS */
#घोषणा WM8961_MS_SHIFT                              6  /* MS */
#घोषणा WM8961_MS_WIDTH                              1  /* MS */
#घोषणा WM8961_DLRSWAP                          0x0020  /* DLRSWAP */
#घोषणा WM8961_DLRSWAP_MASK                     0x0020  /* DLRSWAP */
#घोषणा WM8961_DLRSWAP_SHIFT                         5  /* DLRSWAP */
#घोषणा WM8961_DLRSWAP_WIDTH                         1  /* DLRSWAP */
#घोषणा WM8961_LRP                              0x0010  /* LRP */
#घोषणा WM8961_LRP_MASK                         0x0010  /* LRP */
#घोषणा WM8961_LRP_SHIFT                             4  /* LRP */
#घोषणा WM8961_LRP_WIDTH                             1  /* LRP */
#घोषणा WM8961_WL_MASK                          0x000C  /* WL - [3:2] */
#घोषणा WM8961_WL_SHIFT                              2  /* WL - [3:2] */
#घोषणा WM8961_WL_WIDTH                              2  /* WL - [3:2] */
#घोषणा WM8961_FORMAT_MASK                      0x0003  /* FORMAT - [1:0] */
#घोषणा WM8961_FORMAT_SHIFT                          0  /* FORMAT - [1:0] */
#घोषणा WM8961_FORMAT_WIDTH                          2  /* FORMAT - [1:0] */

/*
 * R8 (0x08) - Clocking2
 */
#घोषणा WM8961_DCLKDIV_MASK                     0x01C0  /* DCLKDIV - [8:6] */
#घोषणा WM8961_DCLKDIV_SHIFT                         6  /* DCLKDIV - [8:6] */
#घोषणा WM8961_DCLKDIV_WIDTH                         3  /* DCLKDIV - [8:6] */
#घोषणा WM8961_CLK_SYS_ENA                      0x0020  /* CLK_SYS_ENA */
#घोषणा WM8961_CLK_SYS_ENA_MASK                 0x0020  /* CLK_SYS_ENA */
#घोषणा WM8961_CLK_SYS_ENA_SHIFT                     5  /* CLK_SYS_ENA */
#घोषणा WM8961_CLK_SYS_ENA_WIDTH                     1  /* CLK_SYS_ENA */
#घोषणा WM8961_CLK_DSP_ENA                      0x0010  /* CLK_DSP_ENA */
#घोषणा WM8961_CLK_DSP_ENA_MASK                 0x0010  /* CLK_DSP_ENA */
#घोषणा WM8961_CLK_DSP_ENA_SHIFT                     4  /* CLK_DSP_ENA */
#घोषणा WM8961_CLK_DSP_ENA_WIDTH                     1  /* CLK_DSP_ENA */
#घोषणा WM8961_BCLKDIV_MASK                     0x000F  /* BCLKDIV - [3:0] */
#घोषणा WM8961_BCLKDIV_SHIFT                         0  /* BCLKDIV - [3:0] */
#घोषणा WM8961_BCLKDIV_WIDTH                         4  /* BCLKDIV - [3:0] */

/*
 * R9 (0x09) - Audio Interface 1
 */
#घोषणा WM8961_DACCOMP_MASK                     0x0018  /* DACCOMP - [4:3] */
#घोषणा WM8961_DACCOMP_SHIFT                         3  /* DACCOMP - [4:3] */
#घोषणा WM8961_DACCOMP_WIDTH                         2  /* DACCOMP - [4:3] */
#घोषणा WM8961_ADCCOMP_MASK                     0x0006  /* ADCCOMP - [2:1] */
#घोषणा WM8961_ADCCOMP_SHIFT                         1  /* ADCCOMP - [2:1] */
#घोषणा WM8961_ADCCOMP_WIDTH                         2  /* ADCCOMP - [2:1] */
#घोषणा WM8961_LOOPBACK                         0x0001  /* LOOPBACK */
#घोषणा WM8961_LOOPBACK_MASK                    0x0001  /* LOOPBACK */
#घोषणा WM8961_LOOPBACK_SHIFT                        0  /* LOOPBACK */
#घोषणा WM8961_LOOPBACK_WIDTH                        1  /* LOOPBACK */

/*
 * R10 (0x0A) - Left DAC volume
 */
#घोषणा WM8961_DACVU                            0x0100  /* DACVU */
#घोषणा WM8961_DACVU_MASK                       0x0100  /* DACVU */
#घोषणा WM8961_DACVU_SHIFT                           8  /* DACVU */
#घोषणा WM8961_DACVU_WIDTH                           1  /* DACVU */
#घोषणा WM8961_LDACVOL_MASK                     0x00FF  /* LDACVOL - [7:0] */
#घोषणा WM8961_LDACVOL_SHIFT                         0  /* LDACVOL - [7:0] */
#घोषणा WM8961_LDACVOL_WIDTH                         8  /* LDACVOL - [7:0] */

/*
 * R11 (0x0B) - Right DAC volume
 */
#घोषणा WM8961_DACVU                            0x0100  /* DACVU */
#घोषणा WM8961_DACVU_MASK                       0x0100  /* DACVU */
#घोषणा WM8961_DACVU_SHIFT                           8  /* DACVU */
#घोषणा WM8961_DACVU_WIDTH                           1  /* DACVU */
#घोषणा WM8961_RDACVOL_MASK                     0x00FF  /* RDACVOL - [7:0] */
#घोषणा WM8961_RDACVOL_SHIFT                         0  /* RDACVOL - [7:0] */
#घोषणा WM8961_RDACVOL_WIDTH                         8  /* RDACVOL - [7:0] */

/*
 * R14 (0x0E) - Audio Interface 2
 */
#घोषणा WM8961_LRCLK_RATE_MASK                  0x01FF  /* LRCLK_RATE - [8:0] */
#घोषणा WM8961_LRCLK_RATE_SHIFT                      0  /* LRCLK_RATE - [8:0] */
#घोषणा WM8961_LRCLK_RATE_WIDTH                      9  /* LRCLK_RATE - [8:0] */

/*
 * R15 (0x0F) - Software Reset
 */
#घोषणा WM8961_SW_RST_DEV_ID1_MASK              0xFFFF  /* SW_RST_DEV_ID1 - [15:0] */
#घोषणा WM8961_SW_RST_DEV_ID1_SHIFT                  0  /* SW_RST_DEV_ID1 - [15:0] */
#घोषणा WM8961_SW_RST_DEV_ID1_WIDTH                 16  /* SW_RST_DEV_ID1 - [15:0] */

/*
 * R17 (0x11) - ALC1
 */
#घोषणा WM8961_ALCSEL_MASK                      0x0180  /* ALCSEL - [8:7] */
#घोषणा WM8961_ALCSEL_SHIFT                          7  /* ALCSEL - [8:7] */
#घोषणा WM8961_ALCSEL_WIDTH                          2  /* ALCSEL - [8:7] */
#घोषणा WM8961_MAXGAIN_MASK                     0x0070  /* MAXGAIN - [6:4] */
#घोषणा WM8961_MAXGAIN_SHIFT                         4  /* MAXGAIN - [6:4] */
#घोषणा WM8961_MAXGAIN_WIDTH                         3  /* MAXGAIN - [6:4] */
#घोषणा WM8961_ALCL_MASK                        0x000F  /* ALCL - [3:0] */
#घोषणा WM8961_ALCL_SHIFT                            0  /* ALCL - [3:0] */
#घोषणा WM8961_ALCL_WIDTH                            4  /* ALCL - [3:0] */

/*
 * R18 (0x12) - ALC2
 */
#घोषणा WM8961_ALCZC                            0x0080  /* ALCZC */
#घोषणा WM8961_ALCZC_MASK                       0x0080  /* ALCZC */
#घोषणा WM8961_ALCZC_SHIFT                           7  /* ALCZC */
#घोषणा WM8961_ALCZC_WIDTH                           1  /* ALCZC */
#घोषणा WM8961_MINGAIN_MASK                     0x0070  /* MINGAIN - [6:4] */
#घोषणा WM8961_MINGAIN_SHIFT                         4  /* MINGAIN - [6:4] */
#घोषणा WM8961_MINGAIN_WIDTH                         3  /* MINGAIN - [6:4] */
#घोषणा WM8961_HLD_MASK                         0x000F  /* HLD - [3:0] */
#घोषणा WM8961_HLD_SHIFT                             0  /* HLD - [3:0] */
#घोषणा WM8961_HLD_WIDTH                             4  /* HLD - [3:0] */

/*
 * R19 (0x13) - ALC3
 */
#घोषणा WM8961_ALCMODE                          0x0100  /* ALCMODE */
#घोषणा WM8961_ALCMODE_MASK                     0x0100  /* ALCMODE */
#घोषणा WM8961_ALCMODE_SHIFT                         8  /* ALCMODE */
#घोषणा WM8961_ALCMODE_WIDTH                         1  /* ALCMODE */
#घोषणा WM8961_DCY_MASK                         0x00F0  /* DCY - [7:4] */
#घोषणा WM8961_DCY_SHIFT                             4  /* DCY - [7:4] */
#घोषणा WM8961_DCY_WIDTH                             4  /* DCY - [7:4] */
#घोषणा WM8961_ATK_MASK                         0x000F  /* ATK - [3:0] */
#घोषणा WM8961_ATK_SHIFT                             0  /* ATK - [3:0] */
#घोषणा WM8961_ATK_WIDTH                             4  /* ATK - [3:0] */

/*
 * R20 (0x14) - Noise Gate
 */
#घोषणा WM8961_NGTH_MASK                        0x00F8  /* NGTH - [7:3] */
#घोषणा WM8961_NGTH_SHIFT                            3  /* NGTH - [7:3] */
#घोषणा WM8961_NGTH_WIDTH                            5  /* NGTH - [7:3] */
#घोषणा WM8961_NGG                              0x0002  /* NGG */
#घोषणा WM8961_NGG_MASK                         0x0002  /* NGG */
#घोषणा WM8961_NGG_SHIFT                             1  /* NGG */
#घोषणा WM8961_NGG_WIDTH                             1  /* NGG */
#घोषणा WM8961_NGAT                             0x0001  /* NGAT */
#घोषणा WM8961_NGAT_MASK                        0x0001  /* NGAT */
#घोषणा WM8961_NGAT_SHIFT                            0  /* NGAT */
#घोषणा WM8961_NGAT_WIDTH                            1  /* NGAT */

/*
 * R21 (0x15) - Left ADC volume
 */
#घोषणा WM8961_ADCVU                            0x0100  /* ADCVU */
#घोषणा WM8961_ADCVU_MASK                       0x0100  /* ADCVU */
#घोषणा WM8961_ADCVU_SHIFT                           8  /* ADCVU */
#घोषणा WM8961_ADCVU_WIDTH                           1  /* ADCVU */
#घोषणा WM8961_LADCVOL_MASK                     0x00FF  /* LADCVOL - [7:0] */
#घोषणा WM8961_LADCVOL_SHIFT                         0  /* LADCVOL - [7:0] */
#घोषणा WM8961_LADCVOL_WIDTH                         8  /* LADCVOL - [7:0] */

/*
 * R22 (0x16) - Right ADC volume
 */
#घोषणा WM8961_ADCVU                            0x0100  /* ADCVU */
#घोषणा WM8961_ADCVU_MASK                       0x0100  /* ADCVU */
#घोषणा WM8961_ADCVU_SHIFT                           8  /* ADCVU */
#घोषणा WM8961_ADCVU_WIDTH                           1  /* ADCVU */
#घोषणा WM8961_RADCVOL_MASK                     0x00FF  /* RADCVOL - [7:0] */
#घोषणा WM8961_RADCVOL_SHIFT                         0  /* RADCVOL - [7:0] */
#घोषणा WM8961_RADCVOL_WIDTH                         8  /* RADCVOL - [7:0] */

/*
 * R23 (0x17) - Additional control(1)
 */
#घोषणा WM8961_TSDEN                            0x0100  /* TSDEN */
#घोषणा WM8961_TSDEN_MASK                       0x0100  /* TSDEN */
#घोषणा WM8961_TSDEN_SHIFT                           8  /* TSDEN */
#घोषणा WM8961_TSDEN_WIDTH                           1  /* TSDEN */
#घोषणा WM8961_DMONOMIX                         0x0010  /* DMONOMIX */
#घोषणा WM8961_DMONOMIX_MASK                    0x0010  /* DMONOMIX */
#घोषणा WM8961_DMONOMIX_SHIFT                        4  /* DMONOMIX */
#घोषणा WM8961_DMONOMIX_WIDTH                        1  /* DMONOMIX */
#घोषणा WM8961_TOEN                             0x0001  /* TOEN */
#घोषणा WM8961_TOEN_MASK                        0x0001  /* TOEN */
#घोषणा WM8961_TOEN_SHIFT                            0  /* TOEN */
#घोषणा WM8961_TOEN_WIDTH                            1  /* TOEN */

/*
 * R24 (0x18) - Additional control(2)
 */
#घोषणा WM8961_TRIS                             0x0008  /* TRIS */
#घोषणा WM8961_TRIS_MASK                        0x0008  /* TRIS */
#घोषणा WM8961_TRIS_SHIFT                            3  /* TRIS */
#घोषणा WM8961_TRIS_WIDTH                            1  /* TRIS */

/*
 * R25 (0x19) - Pwr Mgmt (1)
 */
#घोषणा WM8961_VMIDSEL_MASK                     0x0180  /* VMIDSEL - [8:7] */
#घोषणा WM8961_VMIDSEL_SHIFT                         7  /* VMIDSEL - [8:7] */
#घोषणा WM8961_VMIDSEL_WIDTH                         2  /* VMIDSEL - [8:7] */
#घोषणा WM8961_VREF                             0x0040  /* VREF */
#घोषणा WM8961_VREF_MASK                        0x0040  /* VREF */
#घोषणा WM8961_VREF_SHIFT                            6  /* VREF */
#घोषणा WM8961_VREF_WIDTH                            1  /* VREF */
#घोषणा WM8961_AINL                             0x0020  /* AINL */
#घोषणा WM8961_AINL_MASK                        0x0020  /* AINL */
#घोषणा WM8961_AINL_SHIFT                            5  /* AINL */
#घोषणा WM8961_AINL_WIDTH                            1  /* AINL */
#घोषणा WM8961_AINR                             0x0010  /* AINR */
#घोषणा WM8961_AINR_MASK                        0x0010  /* AINR */
#घोषणा WM8961_AINR_SHIFT                            4  /* AINR */
#घोषणा WM8961_AINR_WIDTH                            1  /* AINR */
#घोषणा WM8961_ADCL                             0x0008  /* ADCL */
#घोषणा WM8961_ADCL_MASK                        0x0008  /* ADCL */
#घोषणा WM8961_ADCL_SHIFT                            3  /* ADCL */
#घोषणा WM8961_ADCL_WIDTH                            1  /* ADCL */
#घोषणा WM8961_ADCR                             0x0004  /* ADCR */
#घोषणा WM8961_ADCR_MASK                        0x0004  /* ADCR */
#घोषणा WM8961_ADCR_SHIFT                            2  /* ADCR */
#घोषणा WM8961_ADCR_WIDTH                            1  /* ADCR */
#घोषणा WM8961_MICB                             0x0002  /* MICB */
#घोषणा WM8961_MICB_MASK                        0x0002  /* MICB */
#घोषणा WM8961_MICB_SHIFT                            1  /* MICB */
#घोषणा WM8961_MICB_WIDTH                            1  /* MICB */

/*
 * R26 (0x1A) - Pwr Mgmt (2)
 */
#घोषणा WM8961_DACL                             0x0100  /* DACL */
#घोषणा WM8961_DACL_MASK                        0x0100  /* DACL */
#घोषणा WM8961_DACL_SHIFT                            8  /* DACL */
#घोषणा WM8961_DACL_WIDTH                            1  /* DACL */
#घोषणा WM8961_DACR                             0x0080  /* DACR */
#घोषणा WM8961_DACR_MASK                        0x0080  /* DACR */
#घोषणा WM8961_DACR_SHIFT                            7  /* DACR */
#घोषणा WM8961_DACR_WIDTH                            1  /* DACR */
#घोषणा WM8961_LOUT1_PGA                        0x0040  /* LOUT1_PGA */
#घोषणा WM8961_LOUT1_PGA_MASK                   0x0040  /* LOUT1_PGA */
#घोषणा WM8961_LOUT1_PGA_SHIFT                       6  /* LOUT1_PGA */
#घोषणा WM8961_LOUT1_PGA_WIDTH                       1  /* LOUT1_PGA */
#घोषणा WM8961_ROUT1_PGA                        0x0020  /* ROUT1_PGA */
#घोषणा WM8961_ROUT1_PGA_MASK                   0x0020  /* ROUT1_PGA */
#घोषणा WM8961_ROUT1_PGA_SHIFT                       5  /* ROUT1_PGA */
#घोषणा WM8961_ROUT1_PGA_WIDTH                       1  /* ROUT1_PGA */
#घोषणा WM8961_SPKL_PGA                         0x0010  /* SPKL_PGA */
#घोषणा WM8961_SPKL_PGA_MASK                    0x0010  /* SPKL_PGA */
#घोषणा WM8961_SPKL_PGA_SHIFT                        4  /* SPKL_PGA */
#घोषणा WM8961_SPKL_PGA_WIDTH                        1  /* SPKL_PGA */
#घोषणा WM8961_SPKR_PGA                         0x0008  /* SPKR_PGA */
#घोषणा WM8961_SPKR_PGA_MASK                    0x0008  /* SPKR_PGA */
#घोषणा WM8961_SPKR_PGA_SHIFT                        3  /* SPKR_PGA */
#घोषणा WM8961_SPKR_PGA_WIDTH                        1  /* SPKR_PGA */

/*
 * R27 (0x1B) - Additional Control (3)
 */
#घोषणा WM8961_SAMPLE_RATE_MASK                 0x0007  /* SAMPLE_RATE - [2:0] */
#घोषणा WM8961_SAMPLE_RATE_SHIFT                     0  /* SAMPLE_RATE - [2:0] */
#घोषणा WM8961_SAMPLE_RATE_WIDTH                     3  /* SAMPLE_RATE - [2:0] */

/*
 * R28 (0x1C) - Anti-pop
 */
#घोषणा WM8961_BUFDCOPEN                        0x0010  /* BUFDCOPEN */
#घोषणा WM8961_BUFDCOPEN_MASK                   0x0010  /* BUFDCOPEN */
#घोषणा WM8961_BUFDCOPEN_SHIFT                       4  /* BUFDCOPEN */
#घोषणा WM8961_BUFDCOPEN_WIDTH                       1  /* BUFDCOPEN */
#घोषणा WM8961_BUFIOEN                          0x0008  /* BUFIOEN */
#घोषणा WM8961_BUFIOEN_MASK                     0x0008  /* BUFIOEN */
#घोषणा WM8961_BUFIOEN_SHIFT                         3  /* BUFIOEN */
#घोषणा WM8961_BUFIOEN_WIDTH                         1  /* BUFIOEN */
#घोषणा WM8961_SOFT_ST                          0x0004  /* SOFT_ST */
#घोषणा WM8961_SOFT_ST_MASK                     0x0004  /* SOFT_ST */
#घोषणा WM8961_SOFT_ST_SHIFT                         2  /* SOFT_ST */
#घोषणा WM8961_SOFT_ST_WIDTH                         1  /* SOFT_ST */

/*
 * R30 (0x1E) - Clocking 3
 */
#घोषणा WM8961_CLK_TO_DIV_MASK                  0x0180  /* CLK_TO_DIV - [8:7] */
#घोषणा WM8961_CLK_TO_DIV_SHIFT                      7  /* CLK_TO_DIV - [8:7] */
#घोषणा WM8961_CLK_TO_DIV_WIDTH                      2  /* CLK_TO_DIV - [8:7] */
#घोषणा WM8961_CLK_256K_DIV_MASK                0x007E  /* CLK_256K_DIV - [6:1] */
#घोषणा WM8961_CLK_256K_DIV_SHIFT                    1  /* CLK_256K_DIV - [6:1] */
#घोषणा WM8961_CLK_256K_DIV_WIDTH                    6  /* CLK_256K_DIV - [6:1] */
#घोषणा WM8961_MANUAL_MODE                      0x0001  /* MANUAL_MODE */
#घोषणा WM8961_MANUAL_MODE_MASK                 0x0001  /* MANUAL_MODE */
#घोषणा WM8961_MANUAL_MODE_SHIFT                     0  /* MANUAL_MODE */
#घोषणा WM8961_MANUAL_MODE_WIDTH                     1  /* MANUAL_MODE */

/*
 * R32 (0x20) - ADCL संकेत path
 */
#घोषणा WM8961_LMICBOOST_MASK                   0x0030  /* LMICBOOST - [5:4] */
#घोषणा WM8961_LMICBOOST_SHIFT                       4  /* LMICBOOST - [5:4] */
#घोषणा WM8961_LMICBOOST_WIDTH                       2  /* LMICBOOST - [5:4] */

/*
 * R33 (0x21) - ADCR संकेत path
 */
#घोषणा WM8961_RMICBOOST_MASK                   0x0030  /* RMICBOOST - [5:4] */
#घोषणा WM8961_RMICBOOST_SHIFT                       4  /* RMICBOOST - [5:4] */
#घोषणा WM8961_RMICBOOST_WIDTH                       2  /* RMICBOOST - [5:4] */

/*
 * R40 (0x28) - LOUT2 volume
 */
#घोषणा WM8961_SPKVU                            0x0100  /* SPKVU */
#घोषणा WM8961_SPKVU_MASK                       0x0100  /* SPKVU */
#घोषणा WM8961_SPKVU_SHIFT                           8  /* SPKVU */
#घोषणा WM8961_SPKVU_WIDTH                           1  /* SPKVU */
#घोषणा WM8961_SPKLZC                           0x0080  /* SPKLZC */
#घोषणा WM8961_SPKLZC_MASK                      0x0080  /* SPKLZC */
#घोषणा WM8961_SPKLZC_SHIFT                          7  /* SPKLZC */
#घोषणा WM8961_SPKLZC_WIDTH                          1  /* SPKLZC */
#घोषणा WM8961_SPKLVOL_MASK                     0x007F  /* SPKLVOL - [6:0] */
#घोषणा WM8961_SPKLVOL_SHIFT                         0  /* SPKLVOL - [6:0] */
#घोषणा WM8961_SPKLVOL_WIDTH                         7  /* SPKLVOL - [6:0] */

/*
 * R41 (0x29) - ROUT2 volume
 */
#घोषणा WM8961_SPKVU                            0x0100  /* SPKVU */
#घोषणा WM8961_SPKVU_MASK                       0x0100  /* SPKVU */
#घोषणा WM8961_SPKVU_SHIFT                           8  /* SPKVU */
#घोषणा WM8961_SPKVU_WIDTH                           1  /* SPKVU */
#घोषणा WM8961_SPKRZC                           0x0080  /* SPKRZC */
#घोषणा WM8961_SPKRZC_MASK                      0x0080  /* SPKRZC */
#घोषणा WM8961_SPKRZC_SHIFT                          7  /* SPKRZC */
#घोषणा WM8961_SPKRZC_WIDTH                          1  /* SPKRZC */
#घोषणा WM8961_SPKRVOL_MASK                     0x007F  /* SPKRVOL - [6:0] */
#घोषणा WM8961_SPKRVOL_SHIFT                         0  /* SPKRVOL - [6:0] */
#घोषणा WM8961_SPKRVOL_WIDTH                         7  /* SPKRVOL - [6:0] */

/*
 * R47 (0x2F) - Pwr Mgmt (3)
 */
#घोषणा WM8961_TEMP_SHUT                        0x0002  /* TEMP_SHUT */
#घोषणा WM8961_TEMP_SHUT_MASK                   0x0002  /* TEMP_SHUT */
#घोषणा WM8961_TEMP_SHUT_SHIFT                       1  /* TEMP_SHUT */
#घोषणा WM8961_TEMP_SHUT_WIDTH                       1  /* TEMP_SHUT */
#घोषणा WM8961_TEMP_WARN                        0x0001  /* TEMP_WARN */
#घोषणा WM8961_TEMP_WARN_MASK                   0x0001  /* TEMP_WARN */
#घोषणा WM8961_TEMP_WARN_SHIFT                       0  /* TEMP_WARN */
#घोषणा WM8961_TEMP_WARN_WIDTH                       1  /* TEMP_WARN */

/*
 * R48 (0x30) - Additional Control (4)
 */
#घोषणा WM8961_TSENSEN                          0x0002  /* TSENSEN */
#घोषणा WM8961_TSENSEN_MASK                     0x0002  /* TSENSEN */
#घोषणा WM8961_TSENSEN_SHIFT                         1  /* TSENSEN */
#घोषणा WM8961_TSENSEN_WIDTH                         1  /* TSENSEN */
#घोषणा WM8961_MBSEL                            0x0001  /* MBSEL */
#घोषणा WM8961_MBSEL_MASK                       0x0001  /* MBSEL */
#घोषणा WM8961_MBSEL_SHIFT                           0  /* MBSEL */
#घोषणा WM8961_MBSEL_WIDTH                           1  /* MBSEL */

/*
 * R49 (0x31) - Class D Control 1
 */
#घोषणा WM8961_SPKR_ENA                         0x0080  /* SPKR_ENA */
#घोषणा WM8961_SPKR_ENA_MASK                    0x0080  /* SPKR_ENA */
#घोषणा WM8961_SPKR_ENA_SHIFT                        7  /* SPKR_ENA */
#घोषणा WM8961_SPKR_ENA_WIDTH                        1  /* SPKR_ENA */
#घोषणा WM8961_SPKL_ENA                         0x0040  /* SPKL_ENA */
#घोषणा WM8961_SPKL_ENA_MASK                    0x0040  /* SPKL_ENA */
#घोषणा WM8961_SPKL_ENA_SHIFT                        6  /* SPKL_ENA */
#घोषणा WM8961_SPKL_ENA_WIDTH                        1  /* SPKL_ENA */

/*
 * R51 (0x33) - Class D Control 2
 */
#घोषणा WM8961_CLASSD_ACGAIN_MASK               0x0007  /* CLASSD_ACGAIN - [2:0] */
#घोषणा WM8961_CLASSD_ACGAIN_SHIFT                   0  /* CLASSD_ACGAIN - [2:0] */
#घोषणा WM8961_CLASSD_ACGAIN_WIDTH                   3  /* CLASSD_ACGAIN - [2:0] */

/*
 * R56 (0x38) - Clocking 4
 */
#घोषणा WM8961_CLK_DCS_DIV_MASK                 0x01E0  /* CLK_DCS_DIV - [8:5] */
#घोषणा WM8961_CLK_DCS_DIV_SHIFT                     5  /* CLK_DCS_DIV - [8:5] */
#घोषणा WM8961_CLK_DCS_DIV_WIDTH                     4  /* CLK_DCS_DIV - [8:5] */
#घोषणा WM8961_CLK_SYS_RATE_MASK                0x001E  /* CLK_SYS_RATE - [4:1] */
#घोषणा WM8961_CLK_SYS_RATE_SHIFT                    1  /* CLK_SYS_RATE - [4:1] */
#घोषणा WM8961_CLK_SYS_RATE_WIDTH                    4  /* CLK_SYS_RATE - [4:1] */

/*
 * R57 (0x39) - DSP Sidetone 0
 */
#घोषणा WM8961_ADCR_DAC_SVOL_MASK               0x00F0  /* ADCR_DAC_SVOL - [7:4] */
#घोषणा WM8961_ADCR_DAC_SVOL_SHIFT                   4  /* ADCR_DAC_SVOL - [7:4] */
#घोषणा WM8961_ADCR_DAC_SVOL_WIDTH                   4  /* ADCR_DAC_SVOL - [7:4] */
#घोषणा WM8961_ADC_TO_DACR_MASK                 0x000C  /* ADC_TO_DACR - [3:2] */
#घोषणा WM8961_ADC_TO_DACR_SHIFT                     2  /* ADC_TO_DACR - [3:2] */
#घोषणा WM8961_ADC_TO_DACR_WIDTH                     2  /* ADC_TO_DACR - [3:2] */

/*
 * R58 (0x3A) - DSP Sidetone 1
 */
#घोषणा WM8961_ADCL_DAC_SVOL_MASK               0x00F0  /* ADCL_DAC_SVOL - [7:4] */
#घोषणा WM8961_ADCL_DAC_SVOL_SHIFT                   4  /* ADCL_DAC_SVOL - [7:4] */
#घोषणा WM8961_ADCL_DAC_SVOL_WIDTH                   4  /* ADCL_DAC_SVOL - [7:4] */
#घोषणा WM8961_ADC_TO_DACL_MASK                 0x000C  /* ADC_TO_DACL - [3:2] */
#घोषणा WM8961_ADC_TO_DACL_SHIFT                     2  /* ADC_TO_DACL - [3:2] */
#घोषणा WM8961_ADC_TO_DACL_WIDTH                     2  /* ADC_TO_DACL - [3:2] */

/*
 * R60 (0x3C) - DC Servo 0
 */
#घोषणा WM8961_DCS_ENA_CHAN_INL                 0x0080  /* DCS_ENA_CHAN_INL */
#घोषणा WM8961_DCS_ENA_CHAN_INL_MASK            0x0080  /* DCS_ENA_CHAN_INL */
#घोषणा WM8961_DCS_ENA_CHAN_INL_SHIFT                7  /* DCS_ENA_CHAN_INL */
#घोषणा WM8961_DCS_ENA_CHAN_INL_WIDTH                1  /* DCS_ENA_CHAN_INL */
#घोषणा WM8961_DCS_TRIG_STARTUP_INL             0x0040  /* DCS_TRIG_STARTUP_INL */
#घोषणा WM8961_DCS_TRIG_STARTUP_INL_MASK        0x0040  /* DCS_TRIG_STARTUP_INL */
#घोषणा WM8961_DCS_TRIG_STARTUP_INL_SHIFT            6  /* DCS_TRIG_STARTUP_INL */
#घोषणा WM8961_DCS_TRIG_STARTUP_INL_WIDTH            1  /* DCS_TRIG_STARTUP_INL */
#घोषणा WM8961_DCS_TRIG_SERIES_INL              0x0010  /* DCS_TRIG_SERIES_INL */
#घोषणा WM8961_DCS_TRIG_SERIES_INL_MASK         0x0010  /* DCS_TRIG_SERIES_INL */
#घोषणा WM8961_DCS_TRIG_SERIES_INL_SHIFT             4  /* DCS_TRIG_SERIES_INL */
#घोषणा WM8961_DCS_TRIG_SERIES_INL_WIDTH             1  /* DCS_TRIG_SERIES_INL */
#घोषणा WM8961_DCS_ENA_CHAN_INR                 0x0008  /* DCS_ENA_CHAN_INR */
#घोषणा WM8961_DCS_ENA_CHAN_INR_MASK            0x0008  /* DCS_ENA_CHAN_INR */
#घोषणा WM8961_DCS_ENA_CHAN_INR_SHIFT                3  /* DCS_ENA_CHAN_INR */
#घोषणा WM8961_DCS_ENA_CHAN_INR_WIDTH                1  /* DCS_ENA_CHAN_INR */
#घोषणा WM8961_DCS_TRIG_STARTUP_INR             0x0004  /* DCS_TRIG_STARTUP_INR */
#घोषणा WM8961_DCS_TRIG_STARTUP_INR_MASK        0x0004  /* DCS_TRIG_STARTUP_INR */
#घोषणा WM8961_DCS_TRIG_STARTUP_INR_SHIFT            2  /* DCS_TRIG_STARTUP_INR */
#घोषणा WM8961_DCS_TRIG_STARTUP_INR_WIDTH            1  /* DCS_TRIG_STARTUP_INR */
#घोषणा WM8961_DCS_TRIG_SERIES_INR              0x0001  /* DCS_TRIG_SERIES_INR */
#घोषणा WM8961_DCS_TRIG_SERIES_INR_MASK         0x0001  /* DCS_TRIG_SERIES_INR */
#घोषणा WM8961_DCS_TRIG_SERIES_INR_SHIFT             0  /* DCS_TRIG_SERIES_INR */
#घोषणा WM8961_DCS_TRIG_SERIES_INR_WIDTH             1  /* DCS_TRIG_SERIES_INR */

/*
 * R61 (0x3D) - DC Servo 1
 */
#घोषणा WM8961_DCS_ENA_CHAN_HPL                 0x0080  /* DCS_ENA_CHAN_HPL */
#घोषणा WM8961_DCS_ENA_CHAN_HPL_MASK            0x0080  /* DCS_ENA_CHAN_HPL */
#घोषणा WM8961_DCS_ENA_CHAN_HPL_SHIFT                7  /* DCS_ENA_CHAN_HPL */
#घोषणा WM8961_DCS_ENA_CHAN_HPL_WIDTH                1  /* DCS_ENA_CHAN_HPL */
#घोषणा WM8961_DCS_TRIG_STARTUP_HPL             0x0040  /* DCS_TRIG_STARTUP_HPL */
#घोषणा WM8961_DCS_TRIG_STARTUP_HPL_MASK        0x0040  /* DCS_TRIG_STARTUP_HPL */
#घोषणा WM8961_DCS_TRIG_STARTUP_HPL_SHIFT            6  /* DCS_TRIG_STARTUP_HPL */
#घोषणा WM8961_DCS_TRIG_STARTUP_HPL_WIDTH            1  /* DCS_TRIG_STARTUP_HPL */
#घोषणा WM8961_DCS_TRIG_SERIES_HPL              0x0010  /* DCS_TRIG_SERIES_HPL */
#घोषणा WM8961_DCS_TRIG_SERIES_HPL_MASK         0x0010  /* DCS_TRIG_SERIES_HPL */
#घोषणा WM8961_DCS_TRIG_SERIES_HPL_SHIFT             4  /* DCS_TRIG_SERIES_HPL */
#घोषणा WM8961_DCS_TRIG_SERIES_HPL_WIDTH             1  /* DCS_TRIG_SERIES_HPL */
#घोषणा WM8961_DCS_ENA_CHAN_HPR                 0x0008  /* DCS_ENA_CHAN_HPR */
#घोषणा WM8961_DCS_ENA_CHAN_HPR_MASK            0x0008  /* DCS_ENA_CHAN_HPR */
#घोषणा WM8961_DCS_ENA_CHAN_HPR_SHIFT                3  /* DCS_ENA_CHAN_HPR */
#घोषणा WM8961_DCS_ENA_CHAN_HPR_WIDTH                1  /* DCS_ENA_CHAN_HPR */
#घोषणा WM8961_DCS_TRIG_STARTUP_HPR             0x0004  /* DCS_TRIG_STARTUP_HPR */
#घोषणा WM8961_DCS_TRIG_STARTUP_HPR_MASK        0x0004  /* DCS_TRIG_STARTUP_HPR */
#घोषणा WM8961_DCS_TRIG_STARTUP_HPR_SHIFT            2  /* DCS_TRIG_STARTUP_HPR */
#घोषणा WM8961_DCS_TRIG_STARTUP_HPR_WIDTH            1  /* DCS_TRIG_STARTUP_HPR */
#घोषणा WM8961_DCS_TRIG_SERIES_HPR              0x0001  /* DCS_TRIG_SERIES_HPR */
#घोषणा WM8961_DCS_TRIG_SERIES_HPR_MASK         0x0001  /* DCS_TRIG_SERIES_HPR */
#घोषणा WM8961_DCS_TRIG_SERIES_HPR_SHIFT             0  /* DCS_TRIG_SERIES_HPR */
#घोषणा WM8961_DCS_TRIG_SERIES_HPR_WIDTH             1  /* DCS_TRIG_SERIES_HPR */

/*
 * R63 (0x3F) - DC Servo 3
 */
#घोषणा WM8961_DCS_FILT_BW_SERIES_MASK          0x0030  /* DCS_FILT_BW_SERIES - [5:4] */
#घोषणा WM8961_DCS_FILT_BW_SERIES_SHIFT              4  /* DCS_FILT_BW_SERIES - [5:4] */
#घोषणा WM8961_DCS_FILT_BW_SERIES_WIDTH              2  /* DCS_FILT_BW_SERIES - [5:4] */

/*
 * R65 (0x41) - DC Servo 5
 */
#घोषणा WM8961_DCS_SERIES_NO_HP_MASK            0x007F  /* DCS_SERIES_NO_HP - [6:0] */
#घोषणा WM8961_DCS_SERIES_NO_HP_SHIFT                0  /* DCS_SERIES_NO_HP - [6:0] */
#घोषणा WM8961_DCS_SERIES_NO_HP_WIDTH                7  /* DCS_SERIES_NO_HP - [6:0] */

/*
 * R68 (0x44) - Analogue PGA Bias
 */
#घोषणा WM8961_HP_PGAS_BIAS_MASK                0x0007  /* HP_PGAS_BIAS - [2:0] */
#घोषणा WM8961_HP_PGAS_BIAS_SHIFT                    0  /* HP_PGAS_BIAS - [2:0] */
#घोषणा WM8961_HP_PGAS_BIAS_WIDTH                    3  /* HP_PGAS_BIAS - [2:0] */

/*
 * R69 (0x45) - Analogue HP 0
 */
#घोषणा WM8961_HPL_RMV_SHORT                    0x0080  /* HPL_RMV_SHORT */
#घोषणा WM8961_HPL_RMV_SHORT_MASK               0x0080  /* HPL_RMV_SHORT */
#घोषणा WM8961_HPL_RMV_SHORT_SHIFT                   7  /* HPL_RMV_SHORT */
#घोषणा WM8961_HPL_RMV_SHORT_WIDTH                   1  /* HPL_RMV_SHORT */
#घोषणा WM8961_HPL_ENA_OUTP                     0x0040  /* HPL_ENA_OUTP */
#घोषणा WM8961_HPL_ENA_OUTP_MASK                0x0040  /* HPL_ENA_OUTP */
#घोषणा WM8961_HPL_ENA_OUTP_SHIFT                    6  /* HPL_ENA_OUTP */
#घोषणा WM8961_HPL_ENA_OUTP_WIDTH                    1  /* HPL_ENA_OUTP */
#घोषणा WM8961_HPL_ENA_DLY                      0x0020  /* HPL_ENA_DLY */
#घोषणा WM8961_HPL_ENA_DLY_MASK                 0x0020  /* HPL_ENA_DLY */
#घोषणा WM8961_HPL_ENA_DLY_SHIFT                     5  /* HPL_ENA_DLY */
#घोषणा WM8961_HPL_ENA_DLY_WIDTH                     1  /* HPL_ENA_DLY */
#घोषणा WM8961_HPL_ENA                          0x0010  /* HPL_ENA */
#घोषणा WM8961_HPL_ENA_MASK                     0x0010  /* HPL_ENA */
#घोषणा WM8961_HPL_ENA_SHIFT                         4  /* HPL_ENA */
#घोषणा WM8961_HPL_ENA_WIDTH                         1  /* HPL_ENA */
#घोषणा WM8961_HPR_RMV_SHORT                    0x0008  /* HPR_RMV_SHORT */
#घोषणा WM8961_HPR_RMV_SHORT_MASK               0x0008  /* HPR_RMV_SHORT */
#घोषणा WM8961_HPR_RMV_SHORT_SHIFT                   3  /* HPR_RMV_SHORT */
#घोषणा WM8961_HPR_RMV_SHORT_WIDTH                   1  /* HPR_RMV_SHORT */
#घोषणा WM8961_HPR_ENA_OUTP                     0x0004  /* HPR_ENA_OUTP */
#घोषणा WM8961_HPR_ENA_OUTP_MASK                0x0004  /* HPR_ENA_OUTP */
#घोषणा WM8961_HPR_ENA_OUTP_SHIFT                    2  /* HPR_ENA_OUTP */
#घोषणा WM8961_HPR_ENA_OUTP_WIDTH                    1  /* HPR_ENA_OUTP */
#घोषणा WM8961_HPR_ENA_DLY                      0x0002  /* HPR_ENA_DLY */
#घोषणा WM8961_HPR_ENA_DLY_MASK                 0x0002  /* HPR_ENA_DLY */
#घोषणा WM8961_HPR_ENA_DLY_SHIFT                     1  /* HPR_ENA_DLY */
#घोषणा WM8961_HPR_ENA_DLY_WIDTH                     1  /* HPR_ENA_DLY */
#घोषणा WM8961_HPR_ENA                          0x0001  /* HPR_ENA */
#घोषणा WM8961_HPR_ENA_MASK                     0x0001  /* HPR_ENA */
#घोषणा WM8961_HPR_ENA_SHIFT                         0  /* HPR_ENA */
#घोषणा WM8961_HPR_ENA_WIDTH                         1  /* HPR_ENA */

/*
 * R71 (0x47) - Analogue HP 2
 */
#घोषणा WM8961_HPL_VOL_MASK                     0x01C0  /* HPL_VOL - [8:6] */
#घोषणा WM8961_HPL_VOL_SHIFT                         6  /* HPL_VOL - [8:6] */
#घोषणा WM8961_HPL_VOL_WIDTH                         3  /* HPL_VOL - [8:6] */
#घोषणा WM8961_HPR_VOL_MASK                     0x0038  /* HPR_VOL - [5:3] */
#घोषणा WM8961_HPR_VOL_SHIFT                         3  /* HPR_VOL - [5:3] */
#घोषणा WM8961_HPR_VOL_WIDTH                         3  /* HPR_VOL - [5:3] */
#घोषणा WM8961_HP_BIAS_BOOST_MASK               0x0007  /* HP_BIAS_BOOST - [2:0] */
#घोषणा WM8961_HP_BIAS_BOOST_SHIFT                   0  /* HP_BIAS_BOOST - [2:0] */
#घोषणा WM8961_HP_BIAS_BOOST_WIDTH                   3  /* HP_BIAS_BOOST - [2:0] */

/*
 * R72 (0x48) - Charge Pump 1
 */
#घोषणा WM8961_CP_ENA                           0x0001  /* CP_ENA */
#घोषणा WM8961_CP_ENA_MASK                      0x0001  /* CP_ENA */
#घोषणा WM8961_CP_ENA_SHIFT                          0  /* CP_ENA */
#घोषणा WM8961_CP_ENA_WIDTH                          1  /* CP_ENA */

/*
 * R82 (0x52) - Charge Pump B
 */
#घोषणा WM8961_CP_DYN_PWR_MASK                  0x0003  /* CP_DYN_PWR - [1:0] */
#घोषणा WM8961_CP_DYN_PWR_SHIFT                      0  /* CP_DYN_PWR - [1:0] */
#घोषणा WM8961_CP_DYN_PWR_WIDTH                      2  /* CP_DYN_PWR - [1:0] */

/*
 * R87 (0x57) - Write Sequencer 1
 */
#घोषणा WM8961_WSEQ_ENA                         0x0020  /* WSEQ_ENA */
#घोषणा WM8961_WSEQ_ENA_MASK                    0x0020  /* WSEQ_ENA */
#घोषणा WM8961_WSEQ_ENA_SHIFT                        5  /* WSEQ_ENA */
#घोषणा WM8961_WSEQ_ENA_WIDTH                        1  /* WSEQ_ENA */
#घोषणा WM8961_WSEQ_WRITE_INDEX_MASK            0x001F  /* WSEQ_WRITE_INDEX - [4:0] */
#घोषणा WM8961_WSEQ_WRITE_INDEX_SHIFT                0  /* WSEQ_WRITE_INDEX - [4:0] */
#घोषणा WM8961_WSEQ_WRITE_INDEX_WIDTH                5  /* WSEQ_WRITE_INDEX - [4:0] */

/*
 * R88 (0x58) - Write Sequencer 2
 */
#घोषणा WM8961_WSEQ_EOS                         0x0100  /* WSEQ_EOS */
#घोषणा WM8961_WSEQ_EOS_MASK                    0x0100  /* WSEQ_EOS */
#घोषणा WM8961_WSEQ_EOS_SHIFT                        8  /* WSEQ_EOS */
#घोषणा WM8961_WSEQ_EOS_WIDTH                        1  /* WSEQ_EOS */
#घोषणा WM8961_WSEQ_ADDR_MASK                   0x00FF  /* WSEQ_ADDR - [7:0] */
#घोषणा WM8961_WSEQ_ADDR_SHIFT                       0  /* WSEQ_ADDR - [7:0] */
#घोषणा WM8961_WSEQ_ADDR_WIDTH                       8  /* WSEQ_ADDR - [7:0] */

/*
 * R89 (0x59) - Write Sequencer 3
 */
#घोषणा WM8961_WSEQ_DATA_MASK                   0x00FF  /* WSEQ_DATA - [7:0] */
#घोषणा WM8961_WSEQ_DATA_SHIFT                       0  /* WSEQ_DATA - [7:0] */
#घोषणा WM8961_WSEQ_DATA_WIDTH                       8  /* WSEQ_DATA - [7:0] */

/*
 * R90 (0x5A) - Write Sequencer 4
 */
#घोषणा WM8961_WSEQ_ABORT                       0x0100  /* WSEQ_ABORT */
#घोषणा WM8961_WSEQ_ABORT_MASK                  0x0100  /* WSEQ_ABORT */
#घोषणा WM8961_WSEQ_ABORT_SHIFT                      8  /* WSEQ_ABORT */
#घोषणा WM8961_WSEQ_ABORT_WIDTH                      1  /* WSEQ_ABORT */
#घोषणा WM8961_WSEQ_START                       0x0080  /* WSEQ_START */
#घोषणा WM8961_WSEQ_START_MASK                  0x0080  /* WSEQ_START */
#घोषणा WM8961_WSEQ_START_SHIFT                      7  /* WSEQ_START */
#घोषणा WM8961_WSEQ_START_WIDTH                      1  /* WSEQ_START */
#घोषणा WM8961_WSEQ_START_INDEX_MASK            0x003F  /* WSEQ_START_INDEX - [5:0] */
#घोषणा WM8961_WSEQ_START_INDEX_SHIFT                0  /* WSEQ_START_INDEX - [5:0] */
#घोषणा WM8961_WSEQ_START_INDEX_WIDTH                6  /* WSEQ_START_INDEX - [5:0] */

/*
 * R91 (0x5B) - Write Sequencer 5
 */
#घोषणा WM8961_WSEQ_DATA_WIDTH_MASK             0x0070  /* WSEQ_DATA_WIDTH - [6:4] */
#घोषणा WM8961_WSEQ_DATA_WIDTH_SHIFT                 4  /* WSEQ_DATA_WIDTH - [6:4] */
#घोषणा WM8961_WSEQ_DATA_WIDTH_WIDTH                 3  /* WSEQ_DATA_WIDTH - [6:4] */
#घोषणा WM8961_WSEQ_DATA_START_MASK             0x000F  /* WSEQ_DATA_START - [3:0] */
#घोषणा WM8961_WSEQ_DATA_START_SHIFT                 0  /* WSEQ_DATA_START - [3:0] */
#घोषणा WM8961_WSEQ_DATA_START_WIDTH                 4  /* WSEQ_DATA_START - [3:0] */

/*
 * R92 (0x5C) - Write Sequencer 6
 */
#घोषणा WM8961_WSEQ_DELAY_MASK                  0x000F  /* WSEQ_DELAY - [3:0] */
#घोषणा WM8961_WSEQ_DELAY_SHIFT                      0  /* WSEQ_DELAY - [3:0] */
#घोषणा WM8961_WSEQ_DELAY_WIDTH                      4  /* WSEQ_DELAY - [3:0] */

/*
 * R93 (0x5D) - Write Sequencer 7
 */
#घोषणा WM8961_WSEQ_BUSY                        0x0001  /* WSEQ_BUSY */
#घोषणा WM8961_WSEQ_BUSY_MASK                   0x0001  /* WSEQ_BUSY */
#घोषणा WM8961_WSEQ_BUSY_SHIFT                       0  /* WSEQ_BUSY */
#घोषणा WM8961_WSEQ_BUSY_WIDTH                       1  /* WSEQ_BUSY */

/*
 * R252 (0xFC) - General test 1
 */
#घोषणा WM8961_ARA_ENA                          0x0002  /* ARA_ENA */
#घोषणा WM8961_ARA_ENA_MASK                     0x0002  /* ARA_ENA */
#घोषणा WM8961_ARA_ENA_SHIFT                         1  /* ARA_ENA */
#घोषणा WM8961_ARA_ENA_WIDTH                         1  /* ARA_ENA */
#घोषणा WM8961_AUTO_INC                         0x0001  /* AUTO_INC */
#घोषणा WM8961_AUTO_INC_MASK                    0x0001  /* AUTO_INC */
#घोषणा WM8961_AUTO_INC_SHIFT                        0  /* AUTO_INC */
#घोषणा WM8961_AUTO_INC_WIDTH                        1  /* AUTO_INC */

#पूर्ण_अगर
