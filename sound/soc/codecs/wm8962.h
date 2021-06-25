<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * wm8962.h  --  WM8962 ASoC driver
 *
 * Copyright 2010 Wolfson Microelectronics, plc
 *
 * Author: Mark Brown <broonie@खोलोsource.wolfsonmicro.com>
 */

#अगर_अघोषित _WM8962_H
#घोषणा _WM8962_H

#समावेश <यंत्र/types.h>
#समावेश <sound/soc.h>

#घोषणा WM8962_SYSCLK_MCLK 0
#घोषणा WM8962_SYSCLK_FLL  1
#घोषणा WM8962_SYSCLK_PLL3 2

#घोषणा WM8962_FLL  1

#घोषणा WM8962_FLL_MCLK 1
#घोषणा WM8962_FLL_BCLK 2
#घोषणा WM8962_FLL_OSC  3
#घोषणा WM8962_FLL_INT  4

/*
 * Register values.
 */
#घोषणा WM8962_LEFT_INPUT_VOLUME                0x00
#घोषणा WM8962_RIGHT_INPUT_VOLUME               0x01
#घोषणा WM8962_HPOUTL_VOLUME                    0x02
#घोषणा WM8962_HPOUTR_VOLUME                    0x03
#घोषणा WM8962_CLOCKING1                        0x04
#घोषणा WM8962_ADC_DAC_CONTROL_1                0x05
#घोषणा WM8962_ADC_DAC_CONTROL_2                0x06
#घोषणा WM8962_AUDIO_INTERFACE_0                0x07
#घोषणा WM8962_CLOCKING2                        0x08
#घोषणा WM8962_AUDIO_INTERFACE_1                0x09
#घोषणा WM8962_LEFT_DAC_VOLUME                  0x0A
#घोषणा WM8962_RIGHT_DAC_VOLUME                 0x0B
#घोषणा WM8962_AUDIO_INTERFACE_2                0x0E
#घोषणा WM8962_SOFTWARE_RESET                   0x0F
#घोषणा WM8962_ALC1                             0x11
#घोषणा WM8962_ALC2                             0x12
#घोषणा WM8962_ALC3                             0x13
#घोषणा WM8962_NOISE_GATE                       0x14
#घोषणा WM8962_LEFT_ADC_VOLUME                  0x15
#घोषणा WM8962_RIGHT_ADC_VOLUME                 0x16
#घोषणा WM8962_ADDITIONAL_CONTROL_1             0x17
#घोषणा WM8962_ADDITIONAL_CONTROL_2             0x18
#घोषणा WM8962_PWR_MGMT_1                       0x19
#घोषणा WM8962_PWR_MGMT_2                       0x1A
#घोषणा WM8962_ADDITIONAL_CONTROL_3             0x1B
#घोषणा WM8962_ANTI_POP                         0x1C
#घोषणा WM8962_CLOCKING_3                       0x1E
#घोषणा WM8962_INPUT_MIXER_CONTROL_1            0x1F
#घोषणा WM8962_LEFT_INPUT_MIXER_VOLUME          0x20
#घोषणा WM8962_RIGHT_INPUT_MIXER_VOLUME         0x21
#घोषणा WM8962_INPUT_MIXER_CONTROL_2            0x22
#घोषणा WM8962_INPUT_BIAS_CONTROL               0x23
#घोषणा WM8962_LEFT_INPUT_PGA_CONTROL           0x25
#घोषणा WM8962_RIGHT_INPUT_PGA_CONTROL          0x26
#घोषणा WM8962_SPKOUTL_VOLUME                   0x28
#घोषणा WM8962_SPKOUTR_VOLUME                   0x29
#घोषणा WM8962_THERMAL_SHUTDOWN_STATUS          0x2F
#घोषणा WM8962_ADDITIONAL_CONTROL_4             0x30
#घोषणा WM8962_CLASS_D_CONTROL_1                0x31
#घोषणा WM8962_CLASS_D_CONTROL_2                0x33
#घोषणा WM8962_CLOCKING_4                       0x38
#घोषणा WM8962_DAC_DSP_MIXING_1                 0x39
#घोषणा WM8962_DAC_DSP_MIXING_2                 0x3A
#घोषणा WM8962_DC_SERVO_0                       0x3C
#घोषणा WM8962_DC_SERVO_1                       0x3D
#घोषणा WM8962_DC_SERVO_4                       0x40
#घोषणा WM8962_DC_SERVO_6                       0x42
#घोषणा WM8962_ANALOGUE_PGA_BIAS                0x44
#घोषणा WM8962_ANALOGUE_HP_0                    0x45
#घोषणा WM8962_ANALOGUE_HP_2                    0x47
#घोषणा WM8962_CHARGE_PUMP_1                    0x48
#घोषणा WM8962_CHARGE_PUMP_B                    0x52
#घोषणा WM8962_WRITE_SEQUENCER_CONTROL_1        0x57
#घोषणा WM8962_WRITE_SEQUENCER_CONTROL_2        0x5A
#घोषणा WM8962_WRITE_SEQUENCER_CONTROL_3        0x5D
#घोषणा WM8962_CONTROL_INTERFACE                0x5E
#घोषणा WM8962_MIXER_ENABLES                    0x63
#घोषणा WM8962_HEADPHONE_MIXER_1                0x64
#घोषणा WM8962_HEADPHONE_MIXER_2                0x65
#घोषणा WM8962_HEADPHONE_MIXER_3                0x66
#घोषणा WM8962_HEADPHONE_MIXER_4                0x67
#घोषणा WM8962_SPEAKER_MIXER_1                  0x69
#घोषणा WM8962_SPEAKER_MIXER_2                  0x6A
#घोषणा WM8962_SPEAKER_MIXER_3                  0x6B
#घोषणा WM8962_SPEAKER_MIXER_4                  0x6C
#घोषणा WM8962_SPEAKER_MIXER_5                  0x6D
#घोषणा WM8962_BEEP_GENERATOR_1                 0x6E
#घोषणा WM8962_OSCILLATOR_TRIM_3                0x73
#घोषणा WM8962_OSCILLATOR_TRIM_4                0x74
#घोषणा WM8962_OSCILLATOR_TRIM_7                0x77
#घोषणा WM8962_ANALOGUE_CLOCKING1               0x7C
#घोषणा WM8962_ANALOGUE_CLOCKING2               0x7D
#घोषणा WM8962_ANALOGUE_CLOCKING3               0x7E
#घोषणा WM8962_PLL_SOFTWARE_RESET               0x7F
#घोषणा WM8962_PLL2                             0x81
#घोषणा WM8962_PLL_4                            0x83
#घोषणा WM8962_PLL_9                            0x88
#घोषणा WM8962_PLL_10                           0x89
#घोषणा WM8962_PLL_11                           0x8A
#घोषणा WM8962_PLL_12                           0x8B
#घोषणा WM8962_PLL_13                           0x8C
#घोषणा WM8962_PLL_14                           0x8D
#घोषणा WM8962_PLL_15                           0x8E
#घोषणा WM8962_PLL_16                           0x8F
#घोषणा WM8962_FLL_CONTROL_1                    0x9B
#घोषणा WM8962_FLL_CONTROL_2                    0x9C
#घोषणा WM8962_FLL_CONTROL_3                    0x9D
#घोषणा WM8962_FLL_CONTROL_5                    0x9F
#घोषणा WM8962_FLL_CONTROL_6                    0xA0
#घोषणा WM8962_FLL_CONTROL_7                    0xA1
#घोषणा WM8962_FLL_CONTROL_8                    0xA2
#घोषणा WM8962_GENERAL_TEST_1                   0xFC
#घोषणा WM8962_DF1                              0x100
#घोषणा WM8962_DF2                              0x101
#घोषणा WM8962_DF3                              0x102
#घोषणा WM8962_DF4                              0x103
#घोषणा WM8962_DF5                              0x104
#घोषणा WM8962_DF6                              0x105
#घोषणा WM8962_DF7                              0x106
#घोषणा WM8962_LHPF1                            0x108
#घोषणा WM8962_LHPF2                            0x109
#घोषणा WM8962_THREED1                          0x10C
#घोषणा WM8962_THREED2                          0x10D
#घोषणा WM8962_THREED3                          0x10E
#घोषणा WM8962_THREED4                          0x10F
#घोषणा WM8962_DRC_1                            0x114
#घोषणा WM8962_DRC_2                            0x115
#घोषणा WM8962_DRC_3                            0x116
#घोषणा WM8962_DRC_4                            0x117
#घोषणा WM8962_DRC_5                            0x118
#घोषणा WM8962_TLOOPBACK                        0x11D
#घोषणा WM8962_EQ1                              0x14F
#घोषणा WM8962_EQ2                              0x150
#घोषणा WM8962_EQ3                              0x151
#घोषणा WM8962_EQ4                              0x152
#घोषणा WM8962_EQ5                              0x153
#घोषणा WM8962_EQ6                              0x154
#घोषणा WM8962_EQ7                              0x155
#घोषणा WM8962_EQ8                              0x156
#घोषणा WM8962_EQ9                              0x157
#घोषणा WM8962_EQ10                             0x158
#घोषणा WM8962_EQ11                             0x159
#घोषणा WM8962_EQ12                             0x15A
#घोषणा WM8962_EQ13                             0x15B
#घोषणा WM8962_EQ14                             0x15C
#घोषणा WM8962_EQ15                             0x15D
#घोषणा WM8962_EQ16                             0x15E
#घोषणा WM8962_EQ17                             0x15F
#घोषणा WM8962_EQ18                             0x160
#घोषणा WM8962_EQ19                             0x161
#घोषणा WM8962_EQ20                             0x162
#घोषणा WM8962_EQ21                             0x163
#घोषणा WM8962_EQ22                             0x164
#घोषणा WM8962_EQ23                             0x165
#घोषणा WM8962_EQ24                             0x166
#घोषणा WM8962_EQ25                             0x167
#घोषणा WM8962_EQ26                             0x168
#घोषणा WM8962_EQ27                             0x169
#घोषणा WM8962_EQ28                             0x16A
#घोषणा WM8962_EQ29                             0x16B
#घोषणा WM8962_EQ30                             0x16C
#घोषणा WM8962_EQ31                             0x16D
#घोषणा WM8962_EQ32                             0x16E
#घोषणा WM8962_EQ33                             0x16F
#घोषणा WM8962_EQ34                             0x170
#घोषणा WM8962_EQ35                             0x171
#घोषणा WM8962_EQ36                             0x172
#घोषणा WM8962_EQ37                             0x173
#घोषणा WM8962_EQ38                             0x174
#घोषणा WM8962_EQ39                             0x175
#घोषणा WM8962_EQ40                             0x176
#घोषणा WM8962_EQ41                             0x177
#घोषणा WM8962_GPIO_BASE			0x200
#घोषणा WM8962_GPIO_2                           0x201
#घोषणा WM8962_GPIO_3                           0x202
#घोषणा WM8962_GPIO_5                           0x204
#घोषणा WM8962_GPIO_6                           0x205
#घोषणा WM8962_INTERRUPT_STATUS_1               0x230
#घोषणा WM8962_INTERRUPT_STATUS_2               0x231
#घोषणा WM8962_INTERRUPT_STATUS_1_MASK          0x238
#घोषणा WM8962_INTERRUPT_STATUS_2_MASK          0x239
#घोषणा WM8962_INTERRUPT_CONTROL                0x240
#घोषणा WM8962_IRQ_DEBOUNCE                     0x248
#घोषणा WM8962_MICINT_SOURCE_POL                0x24A
#घोषणा WM8962_DSP2_POWER_MANAGEMENT            0x300
#घोषणा WM8962_DSP2_EXECCONTROL                 0x40D
#घोषणा WM8962_WRITE_SEQUENCER_0                0x1000
#घोषणा WM8962_WRITE_SEQUENCER_1                0x1001
#घोषणा WM8962_WRITE_SEQUENCER_2                0x1002
#घोषणा WM8962_WRITE_SEQUENCER_3                0x1003
#घोषणा WM8962_WRITE_SEQUENCER_4                0x1004
#घोषणा WM8962_WRITE_SEQUENCER_5                0x1005
#घोषणा WM8962_WRITE_SEQUENCER_6                0x1006
#घोषणा WM8962_WRITE_SEQUENCER_7                0x1007
#घोषणा WM8962_WRITE_SEQUENCER_8                0x1008
#घोषणा WM8962_WRITE_SEQUENCER_9                0x1009
#घोषणा WM8962_WRITE_SEQUENCER_10               0x100A
#घोषणा WM8962_WRITE_SEQUENCER_11               0x100B
#घोषणा WM8962_WRITE_SEQUENCER_12               0x100C
#घोषणा WM8962_WRITE_SEQUENCER_13               0x100D
#घोषणा WM8962_WRITE_SEQUENCER_14               0x100E
#घोषणा WM8962_WRITE_SEQUENCER_15               0x100F
#घोषणा WM8962_WRITE_SEQUENCER_16               0x1010
#घोषणा WM8962_WRITE_SEQUENCER_17               0x1011
#घोषणा WM8962_WRITE_SEQUENCER_18               0x1012
#घोषणा WM8962_WRITE_SEQUENCER_19               0x1013
#घोषणा WM8962_WRITE_SEQUENCER_20               0x1014
#घोषणा WM8962_WRITE_SEQUENCER_21               0x1015
#घोषणा WM8962_WRITE_SEQUENCER_22               0x1016
#घोषणा WM8962_WRITE_SEQUENCER_23               0x1017
#घोषणा WM8962_WRITE_SEQUENCER_24               0x1018
#घोषणा WM8962_WRITE_SEQUENCER_25               0x1019
#घोषणा WM8962_WRITE_SEQUENCER_26               0x101A
#घोषणा WM8962_WRITE_SEQUENCER_27               0x101B
#घोषणा WM8962_WRITE_SEQUENCER_28               0x101C
#घोषणा WM8962_WRITE_SEQUENCER_29               0x101D
#घोषणा WM8962_WRITE_SEQUENCER_30               0x101E
#घोषणा WM8962_WRITE_SEQUENCER_31               0x101F
#घोषणा WM8962_WRITE_SEQUENCER_32               0x1020
#घोषणा WM8962_WRITE_SEQUENCER_33               0x1021
#घोषणा WM8962_WRITE_SEQUENCER_34               0x1022
#घोषणा WM8962_WRITE_SEQUENCER_35               0x1023
#घोषणा WM8962_WRITE_SEQUENCER_36               0x1024
#घोषणा WM8962_WRITE_SEQUENCER_37               0x1025
#घोषणा WM8962_WRITE_SEQUENCER_38               0x1026
#घोषणा WM8962_WRITE_SEQUENCER_39               0x1027
#घोषणा WM8962_WRITE_SEQUENCER_40               0x1028
#घोषणा WM8962_WRITE_SEQUENCER_41               0x1029
#घोषणा WM8962_WRITE_SEQUENCER_42               0x102A
#घोषणा WM8962_WRITE_SEQUENCER_43               0x102B
#घोषणा WM8962_WRITE_SEQUENCER_44               0x102C
#घोषणा WM8962_WRITE_SEQUENCER_45               0x102D
#घोषणा WM8962_WRITE_SEQUENCER_46               0x102E
#घोषणा WM8962_WRITE_SEQUENCER_47               0x102F
#घोषणा WM8962_WRITE_SEQUENCER_48               0x1030
#घोषणा WM8962_WRITE_SEQUENCER_49               0x1031
#घोषणा WM8962_WRITE_SEQUENCER_50               0x1032
#घोषणा WM8962_WRITE_SEQUENCER_51               0x1033
#घोषणा WM8962_WRITE_SEQUENCER_52               0x1034
#घोषणा WM8962_WRITE_SEQUENCER_53               0x1035
#घोषणा WM8962_WRITE_SEQUENCER_54               0x1036
#घोषणा WM8962_WRITE_SEQUENCER_55               0x1037
#घोषणा WM8962_WRITE_SEQUENCER_56               0x1038
#घोषणा WM8962_WRITE_SEQUENCER_57               0x1039
#घोषणा WM8962_WRITE_SEQUENCER_58               0x103A
#घोषणा WM8962_WRITE_SEQUENCER_59               0x103B
#घोषणा WM8962_WRITE_SEQUENCER_60               0x103C
#घोषणा WM8962_WRITE_SEQUENCER_61               0x103D
#घोषणा WM8962_WRITE_SEQUENCER_62               0x103E
#घोषणा WM8962_WRITE_SEQUENCER_63               0x103F
#घोषणा WM8962_WRITE_SEQUENCER_64               0x1040
#घोषणा WM8962_WRITE_SEQUENCER_65               0x1041
#घोषणा WM8962_WRITE_SEQUENCER_66               0x1042
#घोषणा WM8962_WRITE_SEQUENCER_67               0x1043
#घोषणा WM8962_WRITE_SEQUENCER_68               0x1044
#घोषणा WM8962_WRITE_SEQUENCER_69               0x1045
#घोषणा WM8962_WRITE_SEQUENCER_70               0x1046
#घोषणा WM8962_WRITE_SEQUENCER_71               0x1047
#घोषणा WM8962_WRITE_SEQUENCER_72               0x1048
#घोषणा WM8962_WRITE_SEQUENCER_73               0x1049
#घोषणा WM8962_WRITE_SEQUENCER_74               0x104A
#घोषणा WM8962_WRITE_SEQUENCER_75               0x104B
#घोषणा WM8962_WRITE_SEQUENCER_76               0x104C
#घोषणा WM8962_WRITE_SEQUENCER_77               0x104D
#घोषणा WM8962_WRITE_SEQUENCER_78               0x104E
#घोषणा WM8962_WRITE_SEQUENCER_79               0x104F
#घोषणा WM8962_WRITE_SEQUENCER_80               0x1050
#घोषणा WM8962_WRITE_SEQUENCER_81               0x1051
#घोषणा WM8962_WRITE_SEQUENCER_82               0x1052
#घोषणा WM8962_WRITE_SEQUENCER_83               0x1053
#घोषणा WM8962_WRITE_SEQUENCER_84               0x1054
#घोषणा WM8962_WRITE_SEQUENCER_85               0x1055
#घोषणा WM8962_WRITE_SEQUENCER_86               0x1056
#घोषणा WM8962_WRITE_SEQUENCER_87               0x1057
#घोषणा WM8962_WRITE_SEQUENCER_88               0x1058
#घोषणा WM8962_WRITE_SEQUENCER_89               0x1059
#घोषणा WM8962_WRITE_SEQUENCER_90               0x105A
#घोषणा WM8962_WRITE_SEQUENCER_91               0x105B
#घोषणा WM8962_WRITE_SEQUENCER_92               0x105C
#घोषणा WM8962_WRITE_SEQUENCER_93               0x105D
#घोषणा WM8962_WRITE_SEQUENCER_94               0x105E
#घोषणा WM8962_WRITE_SEQUENCER_95               0x105F
#घोषणा WM8962_WRITE_SEQUENCER_96               0x1060
#घोषणा WM8962_WRITE_SEQUENCER_97               0x1061
#घोषणा WM8962_WRITE_SEQUENCER_98               0x1062
#घोषणा WM8962_WRITE_SEQUENCER_99               0x1063
#घोषणा WM8962_WRITE_SEQUENCER_100              0x1064
#घोषणा WM8962_WRITE_SEQUENCER_101              0x1065
#घोषणा WM8962_WRITE_SEQUENCER_102              0x1066
#घोषणा WM8962_WRITE_SEQUENCER_103              0x1067
#घोषणा WM8962_WRITE_SEQUENCER_104              0x1068
#घोषणा WM8962_WRITE_SEQUENCER_105              0x1069
#घोषणा WM8962_WRITE_SEQUENCER_106              0x106A
#घोषणा WM8962_WRITE_SEQUENCER_107              0x106B
#घोषणा WM8962_WRITE_SEQUENCER_108              0x106C
#घोषणा WM8962_WRITE_SEQUENCER_109              0x106D
#घोषणा WM8962_WRITE_SEQUENCER_110              0x106E
#घोषणा WM8962_WRITE_SEQUENCER_111              0x106F
#घोषणा WM8962_WRITE_SEQUENCER_112              0x1070
#घोषणा WM8962_WRITE_SEQUENCER_113              0x1071
#घोषणा WM8962_WRITE_SEQUENCER_114              0x1072
#घोषणा WM8962_WRITE_SEQUENCER_115              0x1073
#घोषणा WM8962_WRITE_SEQUENCER_116              0x1074
#घोषणा WM8962_WRITE_SEQUENCER_117              0x1075
#घोषणा WM8962_WRITE_SEQUENCER_118              0x1076
#घोषणा WM8962_WRITE_SEQUENCER_119              0x1077
#घोषणा WM8962_WRITE_SEQUENCER_120              0x1078
#घोषणा WM8962_WRITE_SEQUENCER_121              0x1079
#घोषणा WM8962_WRITE_SEQUENCER_122              0x107A
#घोषणा WM8962_WRITE_SEQUENCER_123              0x107B
#घोषणा WM8962_WRITE_SEQUENCER_124              0x107C
#घोषणा WM8962_WRITE_SEQUENCER_125              0x107D
#घोषणा WM8962_WRITE_SEQUENCER_126              0x107E
#घोषणा WM8962_WRITE_SEQUENCER_127              0x107F
#घोषणा WM8962_WRITE_SEQUENCER_128              0x1080
#घोषणा WM8962_WRITE_SEQUENCER_129              0x1081
#घोषणा WM8962_WRITE_SEQUENCER_130              0x1082
#घोषणा WM8962_WRITE_SEQUENCER_131              0x1083
#घोषणा WM8962_WRITE_SEQUENCER_132              0x1084
#घोषणा WM8962_WRITE_SEQUENCER_133              0x1085
#घोषणा WM8962_WRITE_SEQUENCER_134              0x1086
#घोषणा WM8962_WRITE_SEQUENCER_135              0x1087
#घोषणा WM8962_WRITE_SEQUENCER_136              0x1088
#घोषणा WM8962_WRITE_SEQUENCER_137              0x1089
#घोषणा WM8962_WRITE_SEQUENCER_138              0x108A
#घोषणा WM8962_WRITE_SEQUENCER_139              0x108B
#घोषणा WM8962_WRITE_SEQUENCER_140              0x108C
#घोषणा WM8962_WRITE_SEQUENCER_141              0x108D
#घोषणा WM8962_WRITE_SEQUENCER_142              0x108E
#घोषणा WM8962_WRITE_SEQUENCER_143              0x108F
#घोषणा WM8962_WRITE_SEQUENCER_144              0x1090
#घोषणा WM8962_WRITE_SEQUENCER_145              0x1091
#घोषणा WM8962_WRITE_SEQUENCER_146              0x1092
#घोषणा WM8962_WRITE_SEQUENCER_147              0x1093
#घोषणा WM8962_WRITE_SEQUENCER_148              0x1094
#घोषणा WM8962_WRITE_SEQUENCER_149              0x1095
#घोषणा WM8962_WRITE_SEQUENCER_150              0x1096
#घोषणा WM8962_WRITE_SEQUENCER_151              0x1097
#घोषणा WM8962_WRITE_SEQUENCER_152              0x1098
#घोषणा WM8962_WRITE_SEQUENCER_153              0x1099
#घोषणा WM8962_WRITE_SEQUENCER_154              0x109A
#घोषणा WM8962_WRITE_SEQUENCER_155              0x109B
#घोषणा WM8962_WRITE_SEQUENCER_156              0x109C
#घोषणा WM8962_WRITE_SEQUENCER_157              0x109D
#घोषणा WM8962_WRITE_SEQUENCER_158              0x109E
#घोषणा WM8962_WRITE_SEQUENCER_159              0x109F
#घोषणा WM8962_WRITE_SEQUENCER_160              0x10A0
#घोषणा WM8962_WRITE_SEQUENCER_161              0x10A1
#घोषणा WM8962_WRITE_SEQUENCER_162              0x10A2
#घोषणा WM8962_WRITE_SEQUENCER_163              0x10A3
#घोषणा WM8962_WRITE_SEQUENCER_164              0x10A4
#घोषणा WM8962_WRITE_SEQUENCER_165              0x10A5
#घोषणा WM8962_WRITE_SEQUENCER_166              0x10A6
#घोषणा WM8962_WRITE_SEQUENCER_167              0x10A7
#घोषणा WM8962_WRITE_SEQUENCER_168              0x10A8
#घोषणा WM8962_WRITE_SEQUENCER_169              0x10A9
#घोषणा WM8962_WRITE_SEQUENCER_170              0x10AA
#घोषणा WM8962_WRITE_SEQUENCER_171              0x10AB
#घोषणा WM8962_WRITE_SEQUENCER_172              0x10AC
#घोषणा WM8962_WRITE_SEQUENCER_173              0x10AD
#घोषणा WM8962_WRITE_SEQUENCER_174              0x10AE
#घोषणा WM8962_WRITE_SEQUENCER_175              0x10AF
#घोषणा WM8962_WRITE_SEQUENCER_176              0x10B0
#घोषणा WM8962_WRITE_SEQUENCER_177              0x10B1
#घोषणा WM8962_WRITE_SEQUENCER_178              0x10B2
#घोषणा WM8962_WRITE_SEQUENCER_179              0x10B3
#घोषणा WM8962_WRITE_SEQUENCER_180              0x10B4
#घोषणा WM8962_WRITE_SEQUENCER_181              0x10B5
#घोषणा WM8962_WRITE_SEQUENCER_182              0x10B6
#घोषणा WM8962_WRITE_SEQUENCER_183              0x10B7
#घोषणा WM8962_WRITE_SEQUENCER_184              0x10B8
#घोषणा WM8962_WRITE_SEQUENCER_185              0x10B9
#घोषणा WM8962_WRITE_SEQUENCER_186              0x10BA
#घोषणा WM8962_WRITE_SEQUENCER_187              0x10BB
#घोषणा WM8962_WRITE_SEQUENCER_188              0x10BC
#घोषणा WM8962_WRITE_SEQUENCER_189              0x10BD
#घोषणा WM8962_WRITE_SEQUENCER_190              0x10BE
#घोषणा WM8962_WRITE_SEQUENCER_191              0x10BF
#घोषणा WM8962_WRITE_SEQUENCER_192              0x10C0
#घोषणा WM8962_WRITE_SEQUENCER_193              0x10C1
#घोषणा WM8962_WRITE_SEQUENCER_194              0x10C2
#घोषणा WM8962_WRITE_SEQUENCER_195              0x10C3
#घोषणा WM8962_WRITE_SEQUENCER_196              0x10C4
#घोषणा WM8962_WRITE_SEQUENCER_197              0x10C5
#घोषणा WM8962_WRITE_SEQUENCER_198              0x10C6
#घोषणा WM8962_WRITE_SEQUENCER_199              0x10C7
#घोषणा WM8962_WRITE_SEQUENCER_200              0x10C8
#घोषणा WM8962_WRITE_SEQUENCER_201              0x10C9
#घोषणा WM8962_WRITE_SEQUENCER_202              0x10CA
#घोषणा WM8962_WRITE_SEQUENCER_203              0x10CB
#घोषणा WM8962_WRITE_SEQUENCER_204              0x10CC
#घोषणा WM8962_WRITE_SEQUENCER_205              0x10CD
#घोषणा WM8962_WRITE_SEQUENCER_206              0x10CE
#घोषणा WM8962_WRITE_SEQUENCER_207              0x10CF
#घोषणा WM8962_WRITE_SEQUENCER_208              0x10D0
#घोषणा WM8962_WRITE_SEQUENCER_209              0x10D1
#घोषणा WM8962_WRITE_SEQUENCER_210              0x10D2
#घोषणा WM8962_WRITE_SEQUENCER_211              0x10D3
#घोषणा WM8962_WRITE_SEQUENCER_212              0x10D4
#घोषणा WM8962_WRITE_SEQUENCER_213              0x10D5
#घोषणा WM8962_WRITE_SEQUENCER_214              0x10D6
#घोषणा WM8962_WRITE_SEQUENCER_215              0x10D7
#घोषणा WM8962_WRITE_SEQUENCER_216              0x10D8
#घोषणा WM8962_WRITE_SEQUENCER_217              0x10D9
#घोषणा WM8962_WRITE_SEQUENCER_218              0x10DA
#घोषणा WM8962_WRITE_SEQUENCER_219              0x10DB
#घोषणा WM8962_WRITE_SEQUENCER_220              0x10DC
#घोषणा WM8962_WRITE_SEQUENCER_221              0x10DD
#घोषणा WM8962_WRITE_SEQUENCER_222              0x10DE
#घोषणा WM8962_WRITE_SEQUENCER_223              0x10DF
#घोषणा WM8962_WRITE_SEQUENCER_224              0x10E0
#घोषणा WM8962_WRITE_SEQUENCER_225              0x10E1
#घोषणा WM8962_WRITE_SEQUENCER_226              0x10E2
#घोषणा WM8962_WRITE_SEQUENCER_227              0x10E3
#घोषणा WM8962_WRITE_SEQUENCER_228              0x10E4
#घोषणा WM8962_WRITE_SEQUENCER_229              0x10E5
#घोषणा WM8962_WRITE_SEQUENCER_230              0x10E6
#घोषणा WM8962_WRITE_SEQUENCER_231              0x10E7
#घोषणा WM8962_WRITE_SEQUENCER_232              0x10E8
#घोषणा WM8962_WRITE_SEQUENCER_233              0x10E9
#घोषणा WM8962_WRITE_SEQUENCER_234              0x10EA
#घोषणा WM8962_WRITE_SEQUENCER_235              0x10EB
#घोषणा WM8962_WRITE_SEQUENCER_236              0x10EC
#घोषणा WM8962_WRITE_SEQUENCER_237              0x10ED
#घोषणा WM8962_WRITE_SEQUENCER_238              0x10EE
#घोषणा WM8962_WRITE_SEQUENCER_239              0x10EF
#घोषणा WM8962_WRITE_SEQUENCER_240              0x10F0
#घोषणा WM8962_WRITE_SEQUENCER_241              0x10F1
#घोषणा WM8962_WRITE_SEQUENCER_242              0x10F2
#घोषणा WM8962_WRITE_SEQUENCER_243              0x10F3
#घोषणा WM8962_WRITE_SEQUENCER_244              0x10F4
#घोषणा WM8962_WRITE_SEQUENCER_245              0x10F5
#घोषणा WM8962_WRITE_SEQUENCER_246              0x10F6
#घोषणा WM8962_WRITE_SEQUENCER_247              0x10F7
#घोषणा WM8962_WRITE_SEQUENCER_248              0x10F8
#घोषणा WM8962_WRITE_SEQUENCER_249              0x10F9
#घोषणा WM8962_WRITE_SEQUENCER_250              0x10FA
#घोषणा WM8962_WRITE_SEQUENCER_251              0x10FB
#घोषणा WM8962_WRITE_SEQUENCER_252              0x10FC
#घोषणा WM8962_WRITE_SEQUENCER_253              0x10FD
#घोषणा WM8962_WRITE_SEQUENCER_254              0x10FE
#घोषणा WM8962_WRITE_SEQUENCER_255              0x10FF
#घोषणा WM8962_WRITE_SEQUENCER_256              0x1100
#घोषणा WM8962_WRITE_SEQUENCER_257              0x1101
#घोषणा WM8962_WRITE_SEQUENCER_258              0x1102
#घोषणा WM8962_WRITE_SEQUENCER_259              0x1103
#घोषणा WM8962_WRITE_SEQUENCER_260              0x1104
#घोषणा WM8962_WRITE_SEQUENCER_261              0x1105
#घोषणा WM8962_WRITE_SEQUENCER_262              0x1106
#घोषणा WM8962_WRITE_SEQUENCER_263              0x1107
#घोषणा WM8962_WRITE_SEQUENCER_264              0x1108
#घोषणा WM8962_WRITE_SEQUENCER_265              0x1109
#घोषणा WM8962_WRITE_SEQUENCER_266              0x110A
#घोषणा WM8962_WRITE_SEQUENCER_267              0x110B
#घोषणा WM8962_WRITE_SEQUENCER_268              0x110C
#घोषणा WM8962_WRITE_SEQUENCER_269              0x110D
#घोषणा WM8962_WRITE_SEQUENCER_270              0x110E
#घोषणा WM8962_WRITE_SEQUENCER_271              0x110F
#घोषणा WM8962_WRITE_SEQUENCER_272              0x1110
#घोषणा WM8962_WRITE_SEQUENCER_273              0x1111
#घोषणा WM8962_WRITE_SEQUENCER_274              0x1112
#घोषणा WM8962_WRITE_SEQUENCER_275              0x1113
#घोषणा WM8962_WRITE_SEQUENCER_276              0x1114
#घोषणा WM8962_WRITE_SEQUENCER_277              0x1115
#घोषणा WM8962_WRITE_SEQUENCER_278              0x1116
#घोषणा WM8962_WRITE_SEQUENCER_279              0x1117
#घोषणा WM8962_WRITE_SEQUENCER_280              0x1118
#घोषणा WM8962_WRITE_SEQUENCER_281              0x1119
#घोषणा WM8962_WRITE_SEQUENCER_282              0x111A
#घोषणा WM8962_WRITE_SEQUENCER_283              0x111B
#घोषणा WM8962_WRITE_SEQUENCER_284              0x111C
#घोषणा WM8962_WRITE_SEQUENCER_285              0x111D
#घोषणा WM8962_WRITE_SEQUENCER_286              0x111E
#घोषणा WM8962_WRITE_SEQUENCER_287              0x111F
#घोषणा WM8962_WRITE_SEQUENCER_288              0x1120
#घोषणा WM8962_WRITE_SEQUENCER_289              0x1121
#घोषणा WM8962_WRITE_SEQUENCER_290              0x1122
#घोषणा WM8962_WRITE_SEQUENCER_291              0x1123
#घोषणा WM8962_WRITE_SEQUENCER_292              0x1124
#घोषणा WM8962_WRITE_SEQUENCER_293              0x1125
#घोषणा WM8962_WRITE_SEQUENCER_294              0x1126
#घोषणा WM8962_WRITE_SEQUENCER_295              0x1127
#घोषणा WM8962_WRITE_SEQUENCER_296              0x1128
#घोषणा WM8962_WRITE_SEQUENCER_297              0x1129
#घोषणा WM8962_WRITE_SEQUENCER_298              0x112A
#घोषणा WM8962_WRITE_SEQUENCER_299              0x112B
#घोषणा WM8962_WRITE_SEQUENCER_300              0x112C
#घोषणा WM8962_WRITE_SEQUENCER_301              0x112D
#घोषणा WM8962_WRITE_SEQUENCER_302              0x112E
#घोषणा WM8962_WRITE_SEQUENCER_303              0x112F
#घोषणा WM8962_WRITE_SEQUENCER_304              0x1130
#घोषणा WM8962_WRITE_SEQUENCER_305              0x1131
#घोषणा WM8962_WRITE_SEQUENCER_306              0x1132
#घोषणा WM8962_WRITE_SEQUENCER_307              0x1133
#घोषणा WM8962_WRITE_SEQUENCER_308              0x1134
#घोषणा WM8962_WRITE_SEQUENCER_309              0x1135
#घोषणा WM8962_WRITE_SEQUENCER_310              0x1136
#घोषणा WM8962_WRITE_SEQUENCER_311              0x1137
#घोषणा WM8962_WRITE_SEQUENCER_312              0x1138
#घोषणा WM8962_WRITE_SEQUENCER_313              0x1139
#घोषणा WM8962_WRITE_SEQUENCER_314              0x113A
#घोषणा WM8962_WRITE_SEQUENCER_315              0x113B
#घोषणा WM8962_WRITE_SEQUENCER_316              0x113C
#घोषणा WM8962_WRITE_SEQUENCER_317              0x113D
#घोषणा WM8962_WRITE_SEQUENCER_318              0x113E
#घोषणा WM8962_WRITE_SEQUENCER_319              0x113F
#घोषणा WM8962_WRITE_SEQUENCER_320              0x1140
#घोषणा WM8962_WRITE_SEQUENCER_321              0x1141
#घोषणा WM8962_WRITE_SEQUENCER_322              0x1142
#घोषणा WM8962_WRITE_SEQUENCER_323              0x1143
#घोषणा WM8962_WRITE_SEQUENCER_324              0x1144
#घोषणा WM8962_WRITE_SEQUENCER_325              0x1145
#घोषणा WM8962_WRITE_SEQUENCER_326              0x1146
#घोषणा WM8962_WRITE_SEQUENCER_327              0x1147
#घोषणा WM8962_WRITE_SEQUENCER_328              0x1148
#घोषणा WM8962_WRITE_SEQUENCER_329              0x1149
#घोषणा WM8962_WRITE_SEQUENCER_330              0x114A
#घोषणा WM8962_WRITE_SEQUENCER_331              0x114B
#घोषणा WM8962_WRITE_SEQUENCER_332              0x114C
#घोषणा WM8962_WRITE_SEQUENCER_333              0x114D
#घोषणा WM8962_WRITE_SEQUENCER_334              0x114E
#घोषणा WM8962_WRITE_SEQUENCER_335              0x114F
#घोषणा WM8962_WRITE_SEQUENCER_336              0x1150
#घोषणा WM8962_WRITE_SEQUENCER_337              0x1151
#घोषणा WM8962_WRITE_SEQUENCER_338              0x1152
#घोषणा WM8962_WRITE_SEQUENCER_339              0x1153
#घोषणा WM8962_WRITE_SEQUENCER_340              0x1154
#घोषणा WM8962_WRITE_SEQUENCER_341              0x1155
#घोषणा WM8962_WRITE_SEQUENCER_342              0x1156
#घोषणा WM8962_WRITE_SEQUENCER_343              0x1157
#घोषणा WM8962_WRITE_SEQUENCER_344              0x1158
#घोषणा WM8962_WRITE_SEQUENCER_345              0x1159
#घोषणा WM8962_WRITE_SEQUENCER_346              0x115A
#घोषणा WM8962_WRITE_SEQUENCER_347              0x115B
#घोषणा WM8962_WRITE_SEQUENCER_348              0x115C
#घोषणा WM8962_WRITE_SEQUENCER_349              0x115D
#घोषणा WM8962_WRITE_SEQUENCER_350              0x115E
#घोषणा WM8962_WRITE_SEQUENCER_351              0x115F
#घोषणा WM8962_WRITE_SEQUENCER_352              0x1160
#घोषणा WM8962_WRITE_SEQUENCER_353              0x1161
#घोषणा WM8962_WRITE_SEQUENCER_354              0x1162
#घोषणा WM8962_WRITE_SEQUENCER_355              0x1163
#घोषणा WM8962_WRITE_SEQUENCER_356              0x1164
#घोषणा WM8962_WRITE_SEQUENCER_357              0x1165
#घोषणा WM8962_WRITE_SEQUENCER_358              0x1166
#घोषणा WM8962_WRITE_SEQUENCER_359              0x1167
#घोषणा WM8962_WRITE_SEQUENCER_360              0x1168
#घोषणा WM8962_WRITE_SEQUENCER_361              0x1169
#घोषणा WM8962_WRITE_SEQUENCER_362              0x116A
#घोषणा WM8962_WRITE_SEQUENCER_363              0x116B
#घोषणा WM8962_WRITE_SEQUENCER_364              0x116C
#घोषणा WM8962_WRITE_SEQUENCER_365              0x116D
#घोषणा WM8962_WRITE_SEQUENCER_366              0x116E
#घोषणा WM8962_WRITE_SEQUENCER_367              0x116F
#घोषणा WM8962_WRITE_SEQUENCER_368              0x1170
#घोषणा WM8962_WRITE_SEQUENCER_369              0x1171
#घोषणा WM8962_WRITE_SEQUENCER_370              0x1172
#घोषणा WM8962_WRITE_SEQUENCER_371              0x1173
#घोषणा WM8962_WRITE_SEQUENCER_372              0x1174
#घोषणा WM8962_WRITE_SEQUENCER_373              0x1175
#घोषणा WM8962_WRITE_SEQUENCER_374              0x1176
#घोषणा WM8962_WRITE_SEQUENCER_375              0x1177
#घोषणा WM8962_WRITE_SEQUENCER_376              0x1178
#घोषणा WM8962_WRITE_SEQUENCER_377              0x1179
#घोषणा WM8962_WRITE_SEQUENCER_378              0x117A
#घोषणा WM8962_WRITE_SEQUENCER_379              0x117B
#घोषणा WM8962_WRITE_SEQUENCER_380              0x117C
#घोषणा WM8962_WRITE_SEQUENCER_381              0x117D
#घोषणा WM8962_WRITE_SEQUENCER_382              0x117E
#घोषणा WM8962_WRITE_SEQUENCER_383              0x117F
#घोषणा WM8962_WRITE_SEQUENCER_384              0x1180
#घोषणा WM8962_WRITE_SEQUENCER_385              0x1181
#घोषणा WM8962_WRITE_SEQUENCER_386              0x1182
#घोषणा WM8962_WRITE_SEQUENCER_387              0x1183
#घोषणा WM8962_WRITE_SEQUENCER_388              0x1184
#घोषणा WM8962_WRITE_SEQUENCER_389              0x1185
#घोषणा WM8962_WRITE_SEQUENCER_390              0x1186
#घोषणा WM8962_WRITE_SEQUENCER_391              0x1187
#घोषणा WM8962_WRITE_SEQUENCER_392              0x1188
#घोषणा WM8962_WRITE_SEQUENCER_393              0x1189
#घोषणा WM8962_WRITE_SEQUENCER_394              0x118A
#घोषणा WM8962_WRITE_SEQUENCER_395              0x118B
#घोषणा WM8962_WRITE_SEQUENCER_396              0x118C
#घोषणा WM8962_WRITE_SEQUENCER_397              0x118D
#घोषणा WM8962_WRITE_SEQUENCER_398              0x118E
#घोषणा WM8962_WRITE_SEQUENCER_399              0x118F
#घोषणा WM8962_WRITE_SEQUENCER_400              0x1190
#घोषणा WM8962_WRITE_SEQUENCER_401              0x1191
#घोषणा WM8962_WRITE_SEQUENCER_402              0x1192
#घोषणा WM8962_WRITE_SEQUENCER_403              0x1193
#घोषणा WM8962_WRITE_SEQUENCER_404              0x1194
#घोषणा WM8962_WRITE_SEQUENCER_405              0x1195
#घोषणा WM8962_WRITE_SEQUENCER_406              0x1196
#घोषणा WM8962_WRITE_SEQUENCER_407              0x1197
#घोषणा WM8962_WRITE_SEQUENCER_408              0x1198
#घोषणा WM8962_WRITE_SEQUENCER_409              0x1199
#घोषणा WM8962_WRITE_SEQUENCER_410              0x119A
#घोषणा WM8962_WRITE_SEQUENCER_411              0x119B
#घोषणा WM8962_WRITE_SEQUENCER_412              0x119C
#घोषणा WM8962_WRITE_SEQUENCER_413              0x119D
#घोषणा WM8962_WRITE_SEQUENCER_414              0x119E
#घोषणा WM8962_WRITE_SEQUENCER_415              0x119F
#घोषणा WM8962_WRITE_SEQUENCER_416              0x11A0
#घोषणा WM8962_WRITE_SEQUENCER_417              0x11A1
#घोषणा WM8962_WRITE_SEQUENCER_418              0x11A2
#घोषणा WM8962_WRITE_SEQUENCER_419              0x11A3
#घोषणा WM8962_WRITE_SEQUENCER_420              0x11A4
#घोषणा WM8962_WRITE_SEQUENCER_421              0x11A5
#घोषणा WM8962_WRITE_SEQUENCER_422              0x11A6
#घोषणा WM8962_WRITE_SEQUENCER_423              0x11A7
#घोषणा WM8962_WRITE_SEQUENCER_424              0x11A8
#घोषणा WM8962_WRITE_SEQUENCER_425              0x11A9
#घोषणा WM8962_WRITE_SEQUENCER_426              0x11AA
#घोषणा WM8962_WRITE_SEQUENCER_427              0x11AB
#घोषणा WM8962_WRITE_SEQUENCER_428              0x11AC
#घोषणा WM8962_WRITE_SEQUENCER_429              0x11AD
#घोषणा WM8962_WRITE_SEQUENCER_430              0x11AE
#घोषणा WM8962_WRITE_SEQUENCER_431              0x11AF
#घोषणा WM8962_WRITE_SEQUENCER_432              0x11B0
#घोषणा WM8962_WRITE_SEQUENCER_433              0x11B1
#घोषणा WM8962_WRITE_SEQUENCER_434              0x11B2
#घोषणा WM8962_WRITE_SEQUENCER_435              0x11B3
#घोषणा WM8962_WRITE_SEQUENCER_436              0x11B4
#घोषणा WM8962_WRITE_SEQUENCER_437              0x11B5
#घोषणा WM8962_WRITE_SEQUENCER_438              0x11B6
#घोषणा WM8962_WRITE_SEQUENCER_439              0x11B7
#घोषणा WM8962_WRITE_SEQUENCER_440              0x11B8
#घोषणा WM8962_WRITE_SEQUENCER_441              0x11B9
#घोषणा WM8962_WRITE_SEQUENCER_442              0x11BA
#घोषणा WM8962_WRITE_SEQUENCER_443              0x11BB
#घोषणा WM8962_WRITE_SEQUENCER_444              0x11BC
#घोषणा WM8962_WRITE_SEQUENCER_445              0x11BD
#घोषणा WM8962_WRITE_SEQUENCER_446              0x11BE
#घोषणा WM8962_WRITE_SEQUENCER_447              0x11BF
#घोषणा WM8962_WRITE_SEQUENCER_448              0x11C0
#घोषणा WM8962_WRITE_SEQUENCER_449              0x11C1
#घोषणा WM8962_WRITE_SEQUENCER_450              0x11C2
#घोषणा WM8962_WRITE_SEQUENCER_451              0x11C3
#घोषणा WM8962_WRITE_SEQUENCER_452              0x11C4
#घोषणा WM8962_WRITE_SEQUENCER_453              0x11C5
#घोषणा WM8962_WRITE_SEQUENCER_454              0x11C6
#घोषणा WM8962_WRITE_SEQUENCER_455              0x11C7
#घोषणा WM8962_WRITE_SEQUENCER_456              0x11C8
#घोषणा WM8962_WRITE_SEQUENCER_457              0x11C9
#घोषणा WM8962_WRITE_SEQUENCER_458              0x11CA
#घोषणा WM8962_WRITE_SEQUENCER_459              0x11CB
#घोषणा WM8962_WRITE_SEQUENCER_460              0x11CC
#घोषणा WM8962_WRITE_SEQUENCER_461              0x11CD
#घोषणा WM8962_WRITE_SEQUENCER_462              0x11CE
#घोषणा WM8962_WRITE_SEQUENCER_463              0x11CF
#घोषणा WM8962_WRITE_SEQUENCER_464              0x11D0
#घोषणा WM8962_WRITE_SEQUENCER_465              0x11D1
#घोषणा WM8962_WRITE_SEQUENCER_466              0x11D2
#घोषणा WM8962_WRITE_SEQUENCER_467              0x11D3
#घोषणा WM8962_WRITE_SEQUENCER_468              0x11D4
#घोषणा WM8962_WRITE_SEQUENCER_469              0x11D5
#घोषणा WM8962_WRITE_SEQUENCER_470              0x11D6
#घोषणा WM8962_WRITE_SEQUENCER_471              0x11D7
#घोषणा WM8962_WRITE_SEQUENCER_472              0x11D8
#घोषणा WM8962_WRITE_SEQUENCER_473              0x11D9
#घोषणा WM8962_WRITE_SEQUENCER_474              0x11DA
#घोषणा WM8962_WRITE_SEQUENCER_475              0x11DB
#घोषणा WM8962_WRITE_SEQUENCER_476              0x11DC
#घोषणा WM8962_WRITE_SEQUENCER_477              0x11DD
#घोषणा WM8962_WRITE_SEQUENCER_478              0x11DE
#घोषणा WM8962_WRITE_SEQUENCER_479              0x11DF
#घोषणा WM8962_WRITE_SEQUENCER_480              0x11E0
#घोषणा WM8962_WRITE_SEQUENCER_481              0x11E1
#घोषणा WM8962_WRITE_SEQUENCER_482              0x11E2
#घोषणा WM8962_WRITE_SEQUENCER_483              0x11E3
#घोषणा WM8962_WRITE_SEQUENCER_484              0x11E4
#घोषणा WM8962_WRITE_SEQUENCER_485              0x11E5
#घोषणा WM8962_WRITE_SEQUENCER_486              0x11E6
#घोषणा WM8962_WRITE_SEQUENCER_487              0x11E7
#घोषणा WM8962_WRITE_SEQUENCER_488              0x11E8
#घोषणा WM8962_WRITE_SEQUENCER_489              0x11E9
#घोषणा WM8962_WRITE_SEQUENCER_490              0x11EA
#घोषणा WM8962_WRITE_SEQUENCER_491              0x11EB
#घोषणा WM8962_WRITE_SEQUENCER_492              0x11EC
#घोषणा WM8962_WRITE_SEQUENCER_493              0x11ED
#घोषणा WM8962_WRITE_SEQUENCER_494              0x11EE
#घोषणा WM8962_WRITE_SEQUENCER_495              0x11EF
#घोषणा WM8962_WRITE_SEQUENCER_496              0x11F0
#घोषणा WM8962_WRITE_SEQUENCER_497              0x11F1
#घोषणा WM8962_WRITE_SEQUENCER_498              0x11F2
#घोषणा WM8962_WRITE_SEQUENCER_499              0x11F3
#घोषणा WM8962_WRITE_SEQUENCER_500              0x11F4
#घोषणा WM8962_WRITE_SEQUENCER_501              0x11F5
#घोषणा WM8962_WRITE_SEQUENCER_502              0x11F6
#घोषणा WM8962_WRITE_SEQUENCER_503              0x11F7
#घोषणा WM8962_WRITE_SEQUENCER_504              0x11F8
#घोषणा WM8962_WRITE_SEQUENCER_505              0x11F9
#घोषणा WM8962_WRITE_SEQUENCER_506              0x11FA
#घोषणा WM8962_WRITE_SEQUENCER_507              0x11FB
#घोषणा WM8962_WRITE_SEQUENCER_508              0x11FC
#घोषणा WM8962_WRITE_SEQUENCER_509              0x11FD
#घोषणा WM8962_WRITE_SEQUENCER_510              0x11FE
#घोषणा WM8962_WRITE_SEQUENCER_511              0x11FF
#घोषणा WM8962_DSP2_INSTRUCTION_RAM_0           0x2000
#घोषणा WM8962_DSP2_ADDRESS_RAM_2               0x2400
#घोषणा WM8962_DSP2_ADDRESS_RAM_1               0x2401
#घोषणा WM8962_DSP2_ADDRESS_RAM_0               0x2402
#घोषणा WM8962_DSP2_DATA1_RAM_1                 0x3000
#घोषणा WM8962_DSP2_DATA1_RAM_0                 0x3001
#घोषणा WM8962_DSP2_DATA2_RAM_1                 0x3400
#घोषणा WM8962_DSP2_DATA2_RAM_0                 0x3401
#घोषणा WM8962_DSP2_DATA3_RAM_1                 0x3800
#घोषणा WM8962_DSP2_DATA3_RAM_0                 0x3801
#घोषणा WM8962_DSP2_COEFF_RAM_0                 0x3C00
#घोषणा WM8962_RETUNEADC_SHARED_COEFF_1         0x4000
#घोषणा WM8962_RETUNEADC_SHARED_COEFF_0         0x4001
#घोषणा WM8962_RETUNEDAC_SHARED_COEFF_1         0x4002
#घोषणा WM8962_RETUNEDAC_SHARED_COEFF_0         0x4003
#घोषणा WM8962_SOUNDSTAGE_ENABLES_1             0x4004
#घोषणा WM8962_SOUNDSTAGE_ENABLES_0             0x4005
#घोषणा WM8962_HDBASS_AI_1                      0x4200
#घोषणा WM8962_HDBASS_AI_0                      0x4201
#घोषणा WM8962_HDBASS_AR_1                      0x4202
#घोषणा WM8962_HDBASS_AR_0                      0x4203
#घोषणा WM8962_HDBASS_B_1                       0x4204
#घोषणा WM8962_HDBASS_B_0                       0x4205
#घोषणा WM8962_HDBASS_K_1                       0x4206
#घोषणा WM8962_HDBASS_K_0                       0x4207
#घोषणा WM8962_HDBASS_N1_1                      0x4208
#घोषणा WM8962_HDBASS_N1_0                      0x4209
#घोषणा WM8962_HDBASS_N2_1                      0x420A
#घोषणा WM8962_HDBASS_N2_0                      0x420B
#घोषणा WM8962_HDBASS_N3_1                      0x420C
#घोषणा WM8962_HDBASS_N3_0                      0x420D
#घोषणा WM8962_HDBASS_N4_1                      0x420E
#घोषणा WM8962_HDBASS_N4_0                      0x420F
#घोषणा WM8962_HDBASS_N5_1                      0x4210
#घोषणा WM8962_HDBASS_N5_0                      0x4211
#घोषणा WM8962_HDBASS_X1_1                      0x4212
#घोषणा WM8962_HDBASS_X1_0                      0x4213
#घोषणा WM8962_HDBASS_X2_1                      0x4214
#घोषणा WM8962_HDBASS_X2_0                      0x4215
#घोषणा WM8962_HDBASS_X3_1                      0x4216
#घोषणा WM8962_HDBASS_X3_0                      0x4217
#घोषणा WM8962_HDBASS_ATK_1                     0x4218
#घोषणा WM8962_HDBASS_ATK_0                     0x4219
#घोषणा WM8962_HDBASS_DCY_1                     0x421A
#घोषणा WM8962_HDBASS_DCY_0                     0x421B
#घोषणा WM8962_HDBASS_PG_1                      0x421C
#घोषणा WM8962_HDBASS_PG_0                      0x421D
#घोषणा WM8962_HPF_C_1                          0x4400
#घोषणा WM8962_HPF_C_0                          0x4401
#घोषणा WM8962_ADCL_RETUNE_C1_1                 0x4600
#घोषणा WM8962_ADCL_RETUNE_C1_0                 0x4601
#घोषणा WM8962_ADCL_RETUNE_C2_1                 0x4602
#घोषणा WM8962_ADCL_RETUNE_C2_0                 0x4603
#घोषणा WM8962_ADCL_RETUNE_C3_1                 0x4604
#घोषणा WM8962_ADCL_RETUNE_C3_0                 0x4605
#घोषणा WM8962_ADCL_RETUNE_C4_1                 0x4606
#घोषणा WM8962_ADCL_RETUNE_C4_0                 0x4607
#घोषणा WM8962_ADCL_RETUNE_C5_1                 0x4608
#घोषणा WM8962_ADCL_RETUNE_C5_0                 0x4609
#घोषणा WM8962_ADCL_RETUNE_C6_1                 0x460A
#घोषणा WM8962_ADCL_RETUNE_C6_0                 0x460B
#घोषणा WM8962_ADCL_RETUNE_C7_1                 0x460C
#घोषणा WM8962_ADCL_RETUNE_C7_0                 0x460D
#घोषणा WM8962_ADCL_RETUNE_C8_1                 0x460E
#घोषणा WM8962_ADCL_RETUNE_C8_0                 0x460F
#घोषणा WM8962_ADCL_RETUNE_C9_1                 0x4610
#घोषणा WM8962_ADCL_RETUNE_C9_0                 0x4611
#घोषणा WM8962_ADCL_RETUNE_C10_1                0x4612
#घोषणा WM8962_ADCL_RETUNE_C10_0                0x4613
#घोषणा WM8962_ADCL_RETUNE_C11_1                0x4614
#घोषणा WM8962_ADCL_RETUNE_C11_0                0x4615
#घोषणा WM8962_ADCL_RETUNE_C12_1                0x4616
#घोषणा WM8962_ADCL_RETUNE_C12_0                0x4617
#घोषणा WM8962_ADCL_RETUNE_C13_1                0x4618
#घोषणा WM8962_ADCL_RETUNE_C13_0                0x4619
#घोषणा WM8962_ADCL_RETUNE_C14_1                0x461A
#घोषणा WM8962_ADCL_RETUNE_C14_0                0x461B
#घोषणा WM8962_ADCL_RETUNE_C15_1                0x461C
#घोषणा WM8962_ADCL_RETUNE_C15_0                0x461D
#घोषणा WM8962_ADCL_RETUNE_C16_1                0x461E
#घोषणा WM8962_ADCL_RETUNE_C16_0                0x461F
#घोषणा WM8962_ADCL_RETUNE_C17_1                0x4620
#घोषणा WM8962_ADCL_RETUNE_C17_0                0x4621
#घोषणा WM8962_ADCL_RETUNE_C18_1                0x4622
#घोषणा WM8962_ADCL_RETUNE_C18_0                0x4623
#घोषणा WM8962_ADCL_RETUNE_C19_1                0x4624
#घोषणा WM8962_ADCL_RETUNE_C19_0                0x4625
#घोषणा WM8962_ADCL_RETUNE_C20_1                0x4626
#घोषणा WM8962_ADCL_RETUNE_C20_0                0x4627
#घोषणा WM8962_ADCL_RETUNE_C21_1                0x4628
#घोषणा WM8962_ADCL_RETUNE_C21_0                0x4629
#घोषणा WM8962_ADCL_RETUNE_C22_1                0x462A
#घोषणा WM8962_ADCL_RETUNE_C22_0                0x462B
#घोषणा WM8962_ADCL_RETUNE_C23_1                0x462C
#घोषणा WM8962_ADCL_RETUNE_C23_0                0x462D
#घोषणा WM8962_ADCL_RETUNE_C24_1                0x462E
#घोषणा WM8962_ADCL_RETUNE_C24_0                0x462F
#घोषणा WM8962_ADCL_RETUNE_C25_1                0x4630
#घोषणा WM8962_ADCL_RETUNE_C25_0                0x4631
#घोषणा WM8962_ADCL_RETUNE_C26_1                0x4632
#घोषणा WM8962_ADCL_RETUNE_C26_0                0x4633
#घोषणा WM8962_ADCL_RETUNE_C27_1                0x4634
#घोषणा WM8962_ADCL_RETUNE_C27_0                0x4635
#घोषणा WM8962_ADCL_RETUNE_C28_1                0x4636
#घोषणा WM8962_ADCL_RETUNE_C28_0                0x4637
#घोषणा WM8962_ADCL_RETUNE_C29_1                0x4638
#घोषणा WM8962_ADCL_RETUNE_C29_0                0x4639
#घोषणा WM8962_ADCL_RETUNE_C30_1                0x463A
#घोषणा WM8962_ADCL_RETUNE_C30_0                0x463B
#घोषणा WM8962_ADCL_RETUNE_C31_1                0x463C
#घोषणा WM8962_ADCL_RETUNE_C31_0                0x463D
#घोषणा WM8962_ADCL_RETUNE_C32_1                0x463E
#घोषणा WM8962_ADCL_RETUNE_C32_0                0x463F
#घोषणा WM8962_RETUNEADC_PG2_1                  0x4800
#घोषणा WM8962_RETUNEADC_PG2_0                  0x4801
#घोषणा WM8962_RETUNEADC_PG_1                   0x4802
#घोषणा WM8962_RETUNEADC_PG_0                   0x4803
#घोषणा WM8962_ADCR_RETUNE_C1_1                 0x4A00
#घोषणा WM8962_ADCR_RETUNE_C1_0                 0x4A01
#घोषणा WM8962_ADCR_RETUNE_C2_1                 0x4A02
#घोषणा WM8962_ADCR_RETUNE_C2_0                 0x4A03
#घोषणा WM8962_ADCR_RETUNE_C3_1                 0x4A04
#घोषणा WM8962_ADCR_RETUNE_C3_0                 0x4A05
#घोषणा WM8962_ADCR_RETUNE_C4_1                 0x4A06
#घोषणा WM8962_ADCR_RETUNE_C4_0                 0x4A07
#घोषणा WM8962_ADCR_RETUNE_C5_1                 0x4A08
#घोषणा WM8962_ADCR_RETUNE_C5_0                 0x4A09
#घोषणा WM8962_ADCR_RETUNE_C6_1                 0x4A0A
#घोषणा WM8962_ADCR_RETUNE_C6_0                 0x4A0B
#घोषणा WM8962_ADCR_RETUNE_C7_1                 0x4A0C
#घोषणा WM8962_ADCR_RETUNE_C7_0                 0x4A0D
#घोषणा WM8962_ADCR_RETUNE_C8_1                 0x4A0E
#घोषणा WM8962_ADCR_RETUNE_C8_0                 0x4A0F
#घोषणा WM8962_ADCR_RETUNE_C9_1                 0x4A10
#घोषणा WM8962_ADCR_RETUNE_C9_0                 0x4A11
#घोषणा WM8962_ADCR_RETUNE_C10_1                0x4A12
#घोषणा WM8962_ADCR_RETUNE_C10_0                0x4A13
#घोषणा WM8962_ADCR_RETUNE_C11_1                0x4A14
#घोषणा WM8962_ADCR_RETUNE_C11_0                0x4A15
#घोषणा WM8962_ADCR_RETUNE_C12_1                0x4A16
#घोषणा WM8962_ADCR_RETUNE_C12_0                0x4A17
#घोषणा WM8962_ADCR_RETUNE_C13_1                0x4A18
#घोषणा WM8962_ADCR_RETUNE_C13_0                0x4A19
#घोषणा WM8962_ADCR_RETUNE_C14_1                0x4A1A
#घोषणा WM8962_ADCR_RETUNE_C14_0                0x4A1B
#घोषणा WM8962_ADCR_RETUNE_C15_1                0x4A1C
#घोषणा WM8962_ADCR_RETUNE_C15_0                0x4A1D
#घोषणा WM8962_ADCR_RETUNE_C16_1                0x4A1E
#घोषणा WM8962_ADCR_RETUNE_C16_0                0x4A1F
#घोषणा WM8962_ADCR_RETUNE_C17_1                0x4A20
#घोषणा WM8962_ADCR_RETUNE_C17_0                0x4A21
#घोषणा WM8962_ADCR_RETUNE_C18_1                0x4A22
#घोषणा WM8962_ADCR_RETUNE_C18_0                0x4A23
#घोषणा WM8962_ADCR_RETUNE_C19_1                0x4A24
#घोषणा WM8962_ADCR_RETUNE_C19_0                0x4A25
#घोषणा WM8962_ADCR_RETUNE_C20_1                0x4A26
#घोषणा WM8962_ADCR_RETUNE_C20_0                0x4A27
#घोषणा WM8962_ADCR_RETUNE_C21_1                0x4A28
#घोषणा WM8962_ADCR_RETUNE_C21_0                0x4A29
#घोषणा WM8962_ADCR_RETUNE_C22_1                0x4A2A
#घोषणा WM8962_ADCR_RETUNE_C22_0                0x4A2B
#घोषणा WM8962_ADCR_RETUNE_C23_1                0x4A2C
#घोषणा WM8962_ADCR_RETUNE_C23_0                0x4A2D
#घोषणा WM8962_ADCR_RETUNE_C24_1                0x4A2E
#घोषणा WM8962_ADCR_RETUNE_C24_0                0x4A2F
#घोषणा WM8962_ADCR_RETUNE_C25_1                0x4A30
#घोषणा WM8962_ADCR_RETUNE_C25_0                0x4A31
#घोषणा WM8962_ADCR_RETUNE_C26_1                0x4A32
#घोषणा WM8962_ADCR_RETUNE_C26_0                0x4A33
#घोषणा WM8962_ADCR_RETUNE_C27_1                0x4A34
#घोषणा WM8962_ADCR_RETUNE_C27_0                0x4A35
#घोषणा WM8962_ADCR_RETUNE_C28_1                0x4A36
#घोषणा WM8962_ADCR_RETUNE_C28_0                0x4A37
#घोषणा WM8962_ADCR_RETUNE_C29_1                0x4A38
#घोषणा WM8962_ADCR_RETUNE_C29_0                0x4A39
#घोषणा WM8962_ADCR_RETUNE_C30_1                0x4A3A
#घोषणा WM8962_ADCR_RETUNE_C30_0                0x4A3B
#घोषणा WM8962_ADCR_RETUNE_C31_1                0x4A3C
#घोषणा WM8962_ADCR_RETUNE_C31_0                0x4A3D
#घोषणा WM8962_ADCR_RETUNE_C32_1                0x4A3E
#घोषणा WM8962_ADCR_RETUNE_C32_0                0x4A3F
#घोषणा WM8962_DACL_RETUNE_C1_1                 0x4C00
#घोषणा WM8962_DACL_RETUNE_C1_0                 0x4C01
#घोषणा WM8962_DACL_RETUNE_C2_1                 0x4C02
#घोषणा WM8962_DACL_RETUNE_C2_0                 0x4C03
#घोषणा WM8962_DACL_RETUNE_C3_1                 0x4C04
#घोषणा WM8962_DACL_RETUNE_C3_0                 0x4C05
#घोषणा WM8962_DACL_RETUNE_C4_1                 0x4C06
#घोषणा WM8962_DACL_RETUNE_C4_0                 0x4C07
#घोषणा WM8962_DACL_RETUNE_C5_1                 0x4C08
#घोषणा WM8962_DACL_RETUNE_C5_0                 0x4C09
#घोषणा WM8962_DACL_RETUNE_C6_1                 0x4C0A
#घोषणा WM8962_DACL_RETUNE_C6_0                 0x4C0B
#घोषणा WM8962_DACL_RETUNE_C7_1                 0x4C0C
#घोषणा WM8962_DACL_RETUNE_C7_0                 0x4C0D
#घोषणा WM8962_DACL_RETUNE_C8_1                 0x4C0E
#घोषणा WM8962_DACL_RETUNE_C8_0                 0x4C0F
#घोषणा WM8962_DACL_RETUNE_C9_1                 0x4C10
#घोषणा WM8962_DACL_RETUNE_C9_0                 0x4C11
#घोषणा WM8962_DACL_RETUNE_C10_1                0x4C12
#घोषणा WM8962_DACL_RETUNE_C10_0                0x4C13
#घोषणा WM8962_DACL_RETUNE_C11_1                0x4C14
#घोषणा WM8962_DACL_RETUNE_C11_0                0x4C15
#घोषणा WM8962_DACL_RETUNE_C12_1                0x4C16
#घोषणा WM8962_DACL_RETUNE_C12_0                0x4C17
#घोषणा WM8962_DACL_RETUNE_C13_1                0x4C18
#घोषणा WM8962_DACL_RETUNE_C13_0                0x4C19
#घोषणा WM8962_DACL_RETUNE_C14_1                0x4C1A
#घोषणा WM8962_DACL_RETUNE_C14_0                0x4C1B
#घोषणा WM8962_DACL_RETUNE_C15_1                0x4C1C
#घोषणा WM8962_DACL_RETUNE_C15_0                0x4C1D
#घोषणा WM8962_DACL_RETUNE_C16_1                0x4C1E
#घोषणा WM8962_DACL_RETUNE_C16_0                0x4C1F
#घोषणा WM8962_DACL_RETUNE_C17_1                0x4C20
#घोषणा WM8962_DACL_RETUNE_C17_0                0x4C21
#घोषणा WM8962_DACL_RETUNE_C18_1                0x4C22
#घोषणा WM8962_DACL_RETUNE_C18_0                0x4C23
#घोषणा WM8962_DACL_RETUNE_C19_1                0x4C24
#घोषणा WM8962_DACL_RETUNE_C19_0                0x4C25
#घोषणा WM8962_DACL_RETUNE_C20_1                0x4C26
#घोषणा WM8962_DACL_RETUNE_C20_0                0x4C27
#घोषणा WM8962_DACL_RETUNE_C21_1                0x4C28
#घोषणा WM8962_DACL_RETUNE_C21_0                0x4C29
#घोषणा WM8962_DACL_RETUNE_C22_1                0x4C2A
#घोषणा WM8962_DACL_RETUNE_C22_0                0x4C2B
#घोषणा WM8962_DACL_RETUNE_C23_1                0x4C2C
#घोषणा WM8962_DACL_RETUNE_C23_0                0x4C2D
#घोषणा WM8962_DACL_RETUNE_C24_1                0x4C2E
#घोषणा WM8962_DACL_RETUNE_C24_0                0x4C2F
#घोषणा WM8962_DACL_RETUNE_C25_1                0x4C30
#घोषणा WM8962_DACL_RETUNE_C25_0                0x4C31
#घोषणा WM8962_DACL_RETUNE_C26_1                0x4C32
#घोषणा WM8962_DACL_RETUNE_C26_0                0x4C33
#घोषणा WM8962_DACL_RETUNE_C27_1                0x4C34
#घोषणा WM8962_DACL_RETUNE_C27_0                0x4C35
#घोषणा WM8962_DACL_RETUNE_C28_1                0x4C36
#घोषणा WM8962_DACL_RETUNE_C28_0                0x4C37
#घोषणा WM8962_DACL_RETUNE_C29_1                0x4C38
#घोषणा WM8962_DACL_RETUNE_C29_0                0x4C39
#घोषणा WM8962_DACL_RETUNE_C30_1                0x4C3A
#घोषणा WM8962_DACL_RETUNE_C30_0                0x4C3B
#घोषणा WM8962_DACL_RETUNE_C31_1                0x4C3C
#घोषणा WM8962_DACL_RETUNE_C31_0                0x4C3D
#घोषणा WM8962_DACL_RETUNE_C32_1                0x4C3E
#घोषणा WM8962_DACL_RETUNE_C32_0                0x4C3F
#घोषणा WM8962_RETUNEDAC_PG2_1                  0x4E00
#घोषणा WM8962_RETUNEDAC_PG2_0                  0x4E01
#घोषणा WM8962_RETUNEDAC_PG_1                   0x4E02
#घोषणा WM8962_RETUNEDAC_PG_0                   0x4E03
#घोषणा WM8962_DACR_RETUNE_C1_1                 0x5000
#घोषणा WM8962_DACR_RETUNE_C1_0                 0x5001
#घोषणा WM8962_DACR_RETUNE_C2_1                 0x5002
#घोषणा WM8962_DACR_RETUNE_C2_0                 0x5003
#घोषणा WM8962_DACR_RETUNE_C3_1                 0x5004
#घोषणा WM8962_DACR_RETUNE_C3_0                 0x5005
#घोषणा WM8962_DACR_RETUNE_C4_1                 0x5006
#घोषणा WM8962_DACR_RETUNE_C4_0                 0x5007
#घोषणा WM8962_DACR_RETUNE_C5_1                 0x5008
#घोषणा WM8962_DACR_RETUNE_C5_0                 0x5009
#घोषणा WM8962_DACR_RETUNE_C6_1                 0x500A
#घोषणा WM8962_DACR_RETUNE_C6_0                 0x500B
#घोषणा WM8962_DACR_RETUNE_C7_1                 0x500C
#घोषणा WM8962_DACR_RETUNE_C7_0                 0x500D
#घोषणा WM8962_DACR_RETUNE_C8_1                 0x500E
#घोषणा WM8962_DACR_RETUNE_C8_0                 0x500F
#घोषणा WM8962_DACR_RETUNE_C9_1                 0x5010
#घोषणा WM8962_DACR_RETUNE_C9_0                 0x5011
#घोषणा WM8962_DACR_RETUNE_C10_1                0x5012
#घोषणा WM8962_DACR_RETUNE_C10_0                0x5013
#घोषणा WM8962_DACR_RETUNE_C11_1                0x5014
#घोषणा WM8962_DACR_RETUNE_C11_0                0x5015
#घोषणा WM8962_DACR_RETUNE_C12_1                0x5016
#घोषणा WM8962_DACR_RETUNE_C12_0                0x5017
#घोषणा WM8962_DACR_RETUNE_C13_1                0x5018
#घोषणा WM8962_DACR_RETUNE_C13_0                0x5019
#घोषणा WM8962_DACR_RETUNE_C14_1                0x501A
#घोषणा WM8962_DACR_RETUNE_C14_0                0x501B
#घोषणा WM8962_DACR_RETUNE_C15_1                0x501C
#घोषणा WM8962_DACR_RETUNE_C15_0                0x501D
#घोषणा WM8962_DACR_RETUNE_C16_1                0x501E
#घोषणा WM8962_DACR_RETUNE_C16_0                0x501F
#घोषणा WM8962_DACR_RETUNE_C17_1                0x5020
#घोषणा WM8962_DACR_RETUNE_C17_0                0x5021
#घोषणा WM8962_DACR_RETUNE_C18_1                0x5022
#घोषणा WM8962_DACR_RETUNE_C18_0                0x5023
#घोषणा WM8962_DACR_RETUNE_C19_1                0x5024
#घोषणा WM8962_DACR_RETUNE_C19_0                0x5025
#घोषणा WM8962_DACR_RETUNE_C20_1                0x5026
#घोषणा WM8962_DACR_RETUNE_C20_0                0x5027
#घोषणा WM8962_DACR_RETUNE_C21_1                0x5028
#घोषणा WM8962_DACR_RETUNE_C21_0                0x5029
#घोषणा WM8962_DACR_RETUNE_C22_1                0x502A
#घोषणा WM8962_DACR_RETUNE_C22_0                0x502B
#घोषणा WM8962_DACR_RETUNE_C23_1                0x502C
#घोषणा WM8962_DACR_RETUNE_C23_0                0x502D
#घोषणा WM8962_DACR_RETUNE_C24_1                0x502E
#घोषणा WM8962_DACR_RETUNE_C24_0                0x502F
#घोषणा WM8962_DACR_RETUNE_C25_1                0x5030
#घोषणा WM8962_DACR_RETUNE_C25_0                0x5031
#घोषणा WM8962_DACR_RETUNE_C26_1                0x5032
#घोषणा WM8962_DACR_RETUNE_C26_0                0x5033
#घोषणा WM8962_DACR_RETUNE_C27_1                0x5034
#घोषणा WM8962_DACR_RETUNE_C27_0                0x5035
#घोषणा WM8962_DACR_RETUNE_C28_1                0x5036
#घोषणा WM8962_DACR_RETUNE_C28_0                0x5037
#घोषणा WM8962_DACR_RETUNE_C29_1                0x5038
#घोषणा WM8962_DACR_RETUNE_C29_0                0x5039
#घोषणा WM8962_DACR_RETUNE_C30_1                0x503A
#घोषणा WM8962_DACR_RETUNE_C30_0                0x503B
#घोषणा WM8962_DACR_RETUNE_C31_1                0x503C
#घोषणा WM8962_DACR_RETUNE_C31_0                0x503D
#घोषणा WM8962_DACR_RETUNE_C32_1                0x503E
#घोषणा WM8962_DACR_RETUNE_C32_0                0x503F
#घोषणा WM8962_VSS_XHD2_1                       0x5200
#घोषणा WM8962_VSS_XHD2_0                       0x5201
#घोषणा WM8962_VSS_XHD3_1                       0x5202
#घोषणा WM8962_VSS_XHD3_0                       0x5203
#घोषणा WM8962_VSS_XHN1_1                       0x5204
#घोषणा WM8962_VSS_XHN1_0                       0x5205
#घोषणा WM8962_VSS_XHN2_1                       0x5206
#घोषणा WM8962_VSS_XHN2_0                       0x5207
#घोषणा WM8962_VSS_XHN3_1                       0x5208
#घोषणा WM8962_VSS_XHN3_0                       0x5209
#घोषणा WM8962_VSS_XLA_1                        0x520A
#घोषणा WM8962_VSS_XLA_0                        0x520B
#घोषणा WM8962_VSS_XLB_1                        0x520C
#घोषणा WM8962_VSS_XLB_0                        0x520D
#घोषणा WM8962_VSS_XLG_1                        0x520E
#घोषणा WM8962_VSS_XLG_0                        0x520F
#घोषणा WM8962_VSS_PG2_1                        0x5210
#घोषणा WM8962_VSS_PG2_0                        0x5211
#घोषणा WM8962_VSS_PG_1                         0x5212
#घोषणा WM8962_VSS_PG_0                         0x5213
#घोषणा WM8962_VSS_XTD1_1                       0x5214
#घोषणा WM8962_VSS_XTD1_0                       0x5215
#घोषणा WM8962_VSS_XTD2_1                       0x5216
#घोषणा WM8962_VSS_XTD2_0                       0x5217
#घोषणा WM8962_VSS_XTD3_1                       0x5218
#घोषणा WM8962_VSS_XTD3_0                       0x5219
#घोषणा WM8962_VSS_XTD4_1                       0x521A
#घोषणा WM8962_VSS_XTD4_0                       0x521B
#घोषणा WM8962_VSS_XTD5_1                       0x521C
#घोषणा WM8962_VSS_XTD5_0                       0x521D
#घोषणा WM8962_VSS_XTD6_1                       0x521E
#घोषणा WM8962_VSS_XTD6_0                       0x521F
#घोषणा WM8962_VSS_XTD7_1                       0x5220
#घोषणा WM8962_VSS_XTD7_0                       0x5221
#घोषणा WM8962_VSS_XTD8_1                       0x5222
#घोषणा WM8962_VSS_XTD8_0                       0x5223
#घोषणा WM8962_VSS_XTD9_1                       0x5224
#घोषणा WM8962_VSS_XTD9_0                       0x5225
#घोषणा WM8962_VSS_XTD10_1                      0x5226
#घोषणा WM8962_VSS_XTD10_0                      0x5227
#घोषणा WM8962_VSS_XTD11_1                      0x5228
#घोषणा WM8962_VSS_XTD11_0                      0x5229
#घोषणा WM8962_VSS_XTD12_1                      0x522A
#घोषणा WM8962_VSS_XTD12_0                      0x522B
#घोषणा WM8962_VSS_XTD13_1                      0x522C
#घोषणा WM8962_VSS_XTD13_0                      0x522D
#घोषणा WM8962_VSS_XTD14_1                      0x522E
#घोषणा WM8962_VSS_XTD14_0                      0x522F
#घोषणा WM8962_VSS_XTD15_1                      0x5230
#घोषणा WM8962_VSS_XTD15_0                      0x5231
#घोषणा WM8962_VSS_XTD16_1                      0x5232
#घोषणा WM8962_VSS_XTD16_0                      0x5233
#घोषणा WM8962_VSS_XTD17_1                      0x5234
#घोषणा WM8962_VSS_XTD17_0                      0x5235
#घोषणा WM8962_VSS_XTD18_1                      0x5236
#घोषणा WM8962_VSS_XTD18_0                      0x5237
#घोषणा WM8962_VSS_XTD19_1                      0x5238
#घोषणा WM8962_VSS_XTD19_0                      0x5239
#घोषणा WM8962_VSS_XTD20_1                      0x523A
#घोषणा WM8962_VSS_XTD20_0                      0x523B
#घोषणा WM8962_VSS_XTD21_1                      0x523C
#घोषणा WM8962_VSS_XTD21_0                      0x523D
#घोषणा WM8962_VSS_XTD22_1                      0x523E
#घोषणा WM8962_VSS_XTD22_0                      0x523F
#घोषणा WM8962_VSS_XTD23_1                      0x5240
#घोषणा WM8962_VSS_XTD23_0                      0x5241
#घोषणा WM8962_VSS_XTD24_1                      0x5242
#घोषणा WM8962_VSS_XTD24_0                      0x5243
#घोषणा WM8962_VSS_XTD25_1                      0x5244
#घोषणा WM8962_VSS_XTD25_0                      0x5245
#घोषणा WM8962_VSS_XTD26_1                      0x5246
#घोषणा WM8962_VSS_XTD26_0                      0x5247
#घोषणा WM8962_VSS_XTD27_1                      0x5248
#घोषणा WM8962_VSS_XTD27_0                      0x5249
#घोषणा WM8962_VSS_XTD28_1                      0x524A
#घोषणा WM8962_VSS_XTD28_0                      0x524B
#घोषणा WM8962_VSS_XTD29_1                      0x524C
#घोषणा WM8962_VSS_XTD29_0                      0x524D
#घोषणा WM8962_VSS_XTD30_1                      0x524E
#घोषणा WM8962_VSS_XTD30_0                      0x524F
#घोषणा WM8962_VSS_XTD31_1                      0x5250
#घोषणा WM8962_VSS_XTD31_0                      0x5251
#घोषणा WM8962_VSS_XTD32_1                      0x5252
#घोषणा WM8962_VSS_XTD32_0                      0x5253
#घोषणा WM8962_VSS_XTS1_1                       0x5254
#घोषणा WM8962_VSS_XTS1_0                       0x5255
#घोषणा WM8962_VSS_XTS2_1                       0x5256
#घोषणा WM8962_VSS_XTS2_0                       0x5257
#घोषणा WM8962_VSS_XTS3_1                       0x5258
#घोषणा WM8962_VSS_XTS3_0                       0x5259
#घोषणा WM8962_VSS_XTS4_1                       0x525A
#घोषणा WM8962_VSS_XTS4_0                       0x525B
#घोषणा WM8962_VSS_XTS5_1                       0x525C
#घोषणा WM8962_VSS_XTS5_0                       0x525D
#घोषणा WM8962_VSS_XTS6_1                       0x525E
#घोषणा WM8962_VSS_XTS6_0                       0x525F
#घोषणा WM8962_VSS_XTS7_1                       0x5260
#घोषणा WM8962_VSS_XTS7_0                       0x5261
#घोषणा WM8962_VSS_XTS8_1                       0x5262
#घोषणा WM8962_VSS_XTS8_0                       0x5263
#घोषणा WM8962_VSS_XTS9_1                       0x5264
#घोषणा WM8962_VSS_XTS9_0                       0x5265
#घोषणा WM8962_VSS_XTS10_1                      0x5266
#घोषणा WM8962_VSS_XTS10_0                      0x5267
#घोषणा WM8962_VSS_XTS11_1                      0x5268
#घोषणा WM8962_VSS_XTS11_0                      0x5269
#घोषणा WM8962_VSS_XTS12_1                      0x526A
#घोषणा WM8962_VSS_XTS12_0                      0x526B
#घोषणा WM8962_VSS_XTS13_1                      0x526C
#घोषणा WM8962_VSS_XTS13_0                      0x526D
#घोषणा WM8962_VSS_XTS14_1                      0x526E
#घोषणा WM8962_VSS_XTS14_0                      0x526F
#घोषणा WM8962_VSS_XTS15_1                      0x5270
#घोषणा WM8962_VSS_XTS15_0                      0x5271
#घोषणा WM8962_VSS_XTS16_1                      0x5272
#घोषणा WM8962_VSS_XTS16_0                      0x5273
#घोषणा WM8962_VSS_XTS17_1                      0x5274
#घोषणा WM8962_VSS_XTS17_0                      0x5275
#घोषणा WM8962_VSS_XTS18_1                      0x5276
#घोषणा WM8962_VSS_XTS18_0                      0x5277
#घोषणा WM8962_VSS_XTS19_1                      0x5278
#घोषणा WM8962_VSS_XTS19_0                      0x5279
#घोषणा WM8962_VSS_XTS20_1                      0x527A
#घोषणा WM8962_VSS_XTS20_0                      0x527B
#घोषणा WM8962_VSS_XTS21_1                      0x527C
#घोषणा WM8962_VSS_XTS21_0                      0x527D
#घोषणा WM8962_VSS_XTS22_1                      0x527E
#घोषणा WM8962_VSS_XTS22_0                      0x527F
#घोषणा WM8962_VSS_XTS23_1                      0x5280
#घोषणा WM8962_VSS_XTS23_0                      0x5281
#घोषणा WM8962_VSS_XTS24_1                      0x5282
#घोषणा WM8962_VSS_XTS24_0                      0x5283
#घोषणा WM8962_VSS_XTS25_1                      0x5284
#घोषणा WM8962_VSS_XTS25_0                      0x5285
#घोषणा WM8962_VSS_XTS26_1                      0x5286
#घोषणा WM8962_VSS_XTS26_0                      0x5287
#घोषणा WM8962_VSS_XTS27_1                      0x5288
#घोषणा WM8962_VSS_XTS27_0                      0x5289
#घोषणा WM8962_VSS_XTS28_1                      0x528A
#घोषणा WM8962_VSS_XTS28_0                      0x528B
#घोषणा WM8962_VSS_XTS29_1                      0x528C
#घोषणा WM8962_VSS_XTS29_0                      0x528D
#घोषणा WM8962_VSS_XTS30_1                      0x528E
#घोषणा WM8962_VSS_XTS30_0                      0x528F
#घोषणा WM8962_VSS_XTS31_1                      0x5290
#घोषणा WM8962_VSS_XTS31_0                      0x5291
#घोषणा WM8962_VSS_XTS32_1                      0x5292
#घोषणा WM8962_VSS_XTS32_0                      0x5293

#घोषणा WM8962_REGISTER_COUNT                   1138
#घोषणा WM8962_MAX_REGISTER                     0x5293

/*
 * Field Definitions.
 */

/*
 * R0 (0x00) - Left Input volume
 */
#घोषणा WM8962_IN_VU                            0x0100  /* IN_VU */
#घोषणा WM8962_IN_VU_MASK                       0x0100  /* IN_VU */
#घोषणा WM8962_IN_VU_SHIFT                           8  /* IN_VU */
#घोषणा WM8962_IN_VU_WIDTH                           1  /* IN_VU */
#घोषणा WM8962_INPGAL_MUTE                      0x0080  /* INPGAL_MUTE */
#घोषणा WM8962_INPGAL_MUTE_MASK                 0x0080  /* INPGAL_MUTE */
#घोषणा WM8962_INPGAL_MUTE_SHIFT                     7  /* INPGAL_MUTE */
#घोषणा WM8962_INPGAL_MUTE_WIDTH                     1  /* INPGAL_MUTE */
#घोषणा WM8962_INL_ZC                           0x0040  /* INL_ZC */
#घोषणा WM8962_INL_ZC_MASK                      0x0040  /* INL_ZC */
#घोषणा WM8962_INL_ZC_SHIFT                          6  /* INL_ZC */
#घोषणा WM8962_INL_ZC_WIDTH                          1  /* INL_ZC */
#घोषणा WM8962_INL_VOL_MASK                     0x003F  /* INL_VOL - [5:0] */
#घोषणा WM8962_INL_VOL_SHIFT                         0  /* INL_VOL - [5:0] */
#घोषणा WM8962_INL_VOL_WIDTH                         6  /* INL_VOL - [5:0] */

/*
 * R1 (0x01) - Right Input volume
 */
#घोषणा WM8962_CUST_ID_MASK                     0xF000  /* CUST_ID - [15:12] */
#घोषणा WM8962_CUST_ID_SHIFT                        12  /* CUST_ID - [15:12] */
#घोषणा WM8962_CUST_ID_WIDTH                         4  /* CUST_ID - [15:12] */
#घोषणा WM8962_CHIP_REV_MASK                    0x0E00  /* CHIP_REV - [11:9] */
#घोषणा WM8962_CHIP_REV_SHIFT                        9  /* CHIP_REV - [11:9] */
#घोषणा WM8962_CHIP_REV_WIDTH                        3  /* CHIP_REV - [11:9] */
#घोषणा WM8962_IN_VU                            0x0100  /* IN_VU */
#घोषणा WM8962_IN_VU_MASK                       0x0100  /* IN_VU */
#घोषणा WM8962_IN_VU_SHIFT                           8  /* IN_VU */
#घोषणा WM8962_IN_VU_WIDTH                           1  /* IN_VU */
#घोषणा WM8962_INPGAR_MUTE                      0x0080  /* INPGAR_MUTE */
#घोषणा WM8962_INPGAR_MUTE_MASK                 0x0080  /* INPGAR_MUTE */
#घोषणा WM8962_INPGAR_MUTE_SHIFT                     7  /* INPGAR_MUTE */
#घोषणा WM8962_INPGAR_MUTE_WIDTH                     1  /* INPGAR_MUTE */
#घोषणा WM8962_INR_ZC                           0x0040  /* INR_ZC */
#घोषणा WM8962_INR_ZC_MASK                      0x0040  /* INR_ZC */
#घोषणा WM8962_INR_ZC_SHIFT                          6  /* INR_ZC */
#घोषणा WM8962_INR_ZC_WIDTH                          1  /* INR_ZC */
#घोषणा WM8962_INR_VOL_MASK                     0x003F  /* INR_VOL - [5:0] */
#घोषणा WM8962_INR_VOL_SHIFT                         0  /* INR_VOL - [5:0] */
#घोषणा WM8962_INR_VOL_WIDTH                         6  /* INR_VOL - [5:0] */

/*
 * R2 (0x02) - HPOUTL volume
 */
#घोषणा WM8962_HPOUT_VU                         0x0100  /* HPOUT_VU */
#घोषणा WM8962_HPOUT_VU_MASK                    0x0100  /* HPOUT_VU */
#घोषणा WM8962_HPOUT_VU_SHIFT                        8  /* HPOUT_VU */
#घोषणा WM8962_HPOUT_VU_WIDTH                        1  /* HPOUT_VU */
#घोषणा WM8962_HPOUTL_ZC                        0x0080  /* HPOUTL_ZC */
#घोषणा WM8962_HPOUTL_ZC_MASK                   0x0080  /* HPOUTL_ZC */
#घोषणा WM8962_HPOUTL_ZC_SHIFT                       7  /* HPOUTL_ZC */
#घोषणा WM8962_HPOUTL_ZC_WIDTH                       1  /* HPOUTL_ZC */
#घोषणा WM8962_HPOUTL_VOL_MASK                  0x007F  /* HPOUTL_VOL - [6:0] */
#घोषणा WM8962_HPOUTL_VOL_SHIFT                      0  /* HPOUTL_VOL - [6:0] */
#घोषणा WM8962_HPOUTL_VOL_WIDTH                      7  /* HPOUTL_VOL - [6:0] */

/*
 * R3 (0x03) - HPOUTR volume
 */
#घोषणा WM8962_HPOUT_VU                         0x0100  /* HPOUT_VU */
#घोषणा WM8962_HPOUT_VU_MASK                    0x0100  /* HPOUT_VU */
#घोषणा WM8962_HPOUT_VU_SHIFT                        8  /* HPOUT_VU */
#घोषणा WM8962_HPOUT_VU_WIDTH                        1  /* HPOUT_VU */
#घोषणा WM8962_HPOUTR_ZC                        0x0080  /* HPOUTR_ZC */
#घोषणा WM8962_HPOUTR_ZC_MASK                   0x0080  /* HPOUTR_ZC */
#घोषणा WM8962_HPOUTR_ZC_SHIFT                       7  /* HPOUTR_ZC */
#घोषणा WM8962_HPOUTR_ZC_WIDTH                       1  /* HPOUTR_ZC */
#घोषणा WM8962_HPOUTR_VOL_MASK                  0x007F  /* HPOUTR_VOL - [6:0] */
#घोषणा WM8962_HPOUTR_VOL_SHIFT                      0  /* HPOUTR_VOL - [6:0] */
#घोषणा WM8962_HPOUTR_VOL_WIDTH                      7  /* HPOUTR_VOL - [6:0] */

/*
 * R4 (0x04) - Clocking1
 */
#घोषणा WM8962_DSPCLK_DIV_MASK                  0x0600  /* DSPCLK_DIV - [10:9] */
#घोषणा WM8962_DSPCLK_DIV_SHIFT                      9  /* DSPCLK_DIV - [10:9] */
#घोषणा WM8962_DSPCLK_DIV_WIDTH                      2  /* DSPCLK_DIV - [10:9] */
#घोषणा WM8962_ADCSYS_CLK_DIV_MASK              0x01C0  /* ADCSYS_CLK_DIV - [8:6] */
#घोषणा WM8962_ADCSYS_CLK_DIV_SHIFT                  6  /* ADCSYS_CLK_DIV - [8:6] */
#घोषणा WM8962_ADCSYS_CLK_DIV_WIDTH                  3  /* ADCSYS_CLK_DIV - [8:6] */
#घोषणा WM8962_DACSYS_CLK_DIV_MASK              0x0038  /* DACSYS_CLK_DIV - [5:3] */
#घोषणा WM8962_DACSYS_CLK_DIV_SHIFT                  3  /* DACSYS_CLK_DIV - [5:3] */
#घोषणा WM8962_DACSYS_CLK_DIV_WIDTH                  3  /* DACSYS_CLK_DIV - [5:3] */
#घोषणा WM8962_MCLKDIV_MASK                     0x0006  /* MCLKDIV - [2:1] */
#घोषणा WM8962_MCLKDIV_SHIFT                         1  /* MCLKDIV - [2:1] */
#घोषणा WM8962_MCLKDIV_WIDTH                         2  /* MCLKDIV - [2:1] */

/*
 * R5 (0x05) - ADC & DAC Control 1
 */
#घोषणा WM8962_ADCR_DAT_INV                     0x0040  /* ADCR_DAT_INV */
#घोषणा WM8962_ADCR_DAT_INV_MASK                0x0040  /* ADCR_DAT_INV */
#घोषणा WM8962_ADCR_DAT_INV_SHIFT                    6  /* ADCR_DAT_INV */
#घोषणा WM8962_ADCR_DAT_INV_WIDTH                    1  /* ADCR_DAT_INV */
#घोषणा WM8962_ADCL_DAT_INV                     0x0020  /* ADCL_DAT_INV */
#घोषणा WM8962_ADCL_DAT_INV_MASK                0x0020  /* ADCL_DAT_INV */
#घोषणा WM8962_ADCL_DAT_INV_SHIFT                    5  /* ADCL_DAT_INV */
#घोषणा WM8962_ADCL_DAT_INV_WIDTH                    1  /* ADCL_DAT_INV */
#घोषणा WM8962_DAC_MUTE_RAMP                    0x0010  /* DAC_MUTE_RAMP */
#घोषणा WM8962_DAC_MUTE_RAMP_MASK               0x0010  /* DAC_MUTE_RAMP */
#घोषणा WM8962_DAC_MUTE_RAMP_SHIFT                   4  /* DAC_MUTE_RAMP */
#घोषणा WM8962_DAC_MUTE_RAMP_WIDTH                   1  /* DAC_MUTE_RAMP */
#घोषणा WM8962_DAC_MUTE                         0x0008  /* DAC_MUTE */
#घोषणा WM8962_DAC_MUTE_MASK                    0x0008  /* DAC_MUTE */
#घोषणा WM8962_DAC_MUTE_SHIFT                        3  /* DAC_MUTE */
#घोषणा WM8962_DAC_MUTE_WIDTH                        1  /* DAC_MUTE */
#घोषणा WM8962_DAC_DEEMP_MASK                   0x0006  /* DAC_DEEMP - [2:1] */
#घोषणा WM8962_DAC_DEEMP_SHIFT                       1  /* DAC_DEEMP - [2:1] */
#घोषणा WM8962_DAC_DEEMP_WIDTH                       2  /* DAC_DEEMP - [2:1] */
#घोषणा WM8962_ADC_HPF_DIS                      0x0001  /* ADC_HPF_DIS */
#घोषणा WM8962_ADC_HPF_DIS_MASK                 0x0001  /* ADC_HPF_DIS */
#घोषणा WM8962_ADC_HPF_DIS_SHIFT                     0  /* ADC_HPF_DIS */
#घोषणा WM8962_ADC_HPF_DIS_WIDTH                     1  /* ADC_HPF_DIS */

/*
 * R6 (0x06) - ADC & DAC Control 2
 */
#घोषणा WM8962_ADC_HPF_SR_MASK                  0x3000  /* ADC_HPF_SR - [13:12] */
#घोषणा WM8962_ADC_HPF_SR_SHIFT                     12  /* ADC_HPF_SR - [13:12] */
#घोषणा WM8962_ADC_HPF_SR_WIDTH                      2  /* ADC_HPF_SR - [13:12] */
#घोषणा WM8962_ADC_HPF_MODE                     0x0400  /* ADC_HPF_MODE */
#घोषणा WM8962_ADC_HPF_MODE_MASK                0x0400  /* ADC_HPF_MODE */
#घोषणा WM8962_ADC_HPF_MODE_SHIFT                   10  /* ADC_HPF_MODE */
#घोषणा WM8962_ADC_HPF_MODE_WIDTH                    1  /* ADC_HPF_MODE */
#घोषणा WM8962_ADC_HPF_CUT_MASK                 0x0380  /* ADC_HPF_CUT - [9:7] */
#घोषणा WM8962_ADC_HPF_CUT_SHIFT                     7  /* ADC_HPF_CUT - [9:7] */
#घोषणा WM8962_ADC_HPF_CUT_WIDTH                     3  /* ADC_HPF_CUT - [9:7] */
#घोषणा WM8962_DACR_DAT_INV                     0x0040  /* DACR_DAT_INV */
#घोषणा WM8962_DACR_DAT_INV_MASK                0x0040  /* DACR_DAT_INV */
#घोषणा WM8962_DACR_DAT_INV_SHIFT                    6  /* DACR_DAT_INV */
#घोषणा WM8962_DACR_DAT_INV_WIDTH                    1  /* DACR_DAT_INV */
#घोषणा WM8962_DACL_DAT_INV                     0x0020  /* DACL_DAT_INV */
#घोषणा WM8962_DACL_DAT_INV_MASK                0x0020  /* DACL_DAT_INV */
#घोषणा WM8962_DACL_DAT_INV_SHIFT                    5  /* DACL_DAT_INV */
#घोषणा WM8962_DACL_DAT_INV_WIDTH                    1  /* DACL_DAT_INV */
#घोषणा WM8962_DAC_UNMUTE_RAMP                  0x0008  /* DAC_UNMUTE_RAMP */
#घोषणा WM8962_DAC_UNMUTE_RAMP_MASK             0x0008  /* DAC_UNMUTE_RAMP */
#घोषणा WM8962_DAC_UNMUTE_RAMP_SHIFT                 3  /* DAC_UNMUTE_RAMP */
#घोषणा WM8962_DAC_UNMUTE_RAMP_WIDTH                 1  /* DAC_UNMUTE_RAMP */
#घोषणा WM8962_DAC_MUTERATE                     0x0004  /* DAC_MUTERATE */
#घोषणा WM8962_DAC_MUTERATE_MASK                0x0004  /* DAC_MUTERATE */
#घोषणा WM8962_DAC_MUTERATE_SHIFT                    2  /* DAC_MUTERATE */
#घोषणा WM8962_DAC_MUTERATE_WIDTH                    1  /* DAC_MUTERATE */
#घोषणा WM8962_DAC_HP                           0x0001  /* DAC_HP */
#घोषणा WM8962_DAC_HP_MASK                      0x0001  /* DAC_HP */
#घोषणा WM8962_DAC_HP_SHIFT                          0  /* DAC_HP */
#घोषणा WM8962_DAC_HP_WIDTH                          1  /* DAC_HP */

/*
 * R7 (0x07) - Audio Interface 0
 */
#घोषणा WM8962_AIFDAC_TDM_MODE                  0x1000  /* AIFDAC_TDM_MODE */
#घोषणा WM8962_AIFDAC_TDM_MODE_MASK             0x1000  /* AIFDAC_TDM_MODE */
#घोषणा WM8962_AIFDAC_TDM_MODE_SHIFT                12  /* AIFDAC_TDM_MODE */
#घोषणा WM8962_AIFDAC_TDM_MODE_WIDTH                 1  /* AIFDAC_TDM_MODE */
#घोषणा WM8962_AIFDAC_TDM_SLOT                  0x0800  /* AIFDAC_TDM_SLOT */
#घोषणा WM8962_AIFDAC_TDM_SLOT_MASK             0x0800  /* AIFDAC_TDM_SLOT */
#घोषणा WM8962_AIFDAC_TDM_SLOT_SHIFT                11  /* AIFDAC_TDM_SLOT */
#घोषणा WM8962_AIFDAC_TDM_SLOT_WIDTH                 1  /* AIFDAC_TDM_SLOT */
#घोषणा WM8962_AIFADC_TDM_MODE                  0x0400  /* AIFADC_TDM_MODE */
#घोषणा WM8962_AIFADC_TDM_MODE_MASK             0x0400  /* AIFADC_TDM_MODE */
#घोषणा WM8962_AIFADC_TDM_MODE_SHIFT                10  /* AIFADC_TDM_MODE */
#घोषणा WM8962_AIFADC_TDM_MODE_WIDTH                 1  /* AIFADC_TDM_MODE */
#घोषणा WM8962_AIFADC_TDM_SLOT                  0x0200  /* AIFADC_TDM_SLOT */
#घोषणा WM8962_AIFADC_TDM_SLOT_MASK             0x0200  /* AIFADC_TDM_SLOT */
#घोषणा WM8962_AIFADC_TDM_SLOT_SHIFT                 9  /* AIFADC_TDM_SLOT */
#घोषणा WM8962_AIFADC_TDM_SLOT_WIDTH                 1  /* AIFADC_TDM_SLOT */
#घोषणा WM8962_ADC_LRSWAP                       0x0100  /* ADC_LRSWAP */
#घोषणा WM8962_ADC_LRSWAP_MASK                  0x0100  /* ADC_LRSWAP */
#घोषणा WM8962_ADC_LRSWAP_SHIFT                      8  /* ADC_LRSWAP */
#घोषणा WM8962_ADC_LRSWAP_WIDTH                      1  /* ADC_LRSWAP */
#घोषणा WM8962_BCLK_INV                         0x0080  /* BCLK_INV */
#घोषणा WM8962_BCLK_INV_MASK                    0x0080  /* BCLK_INV */
#घोषणा WM8962_BCLK_INV_SHIFT                        7  /* BCLK_INV */
#घोषणा WM8962_BCLK_INV_WIDTH                        1  /* BCLK_INV */
#घोषणा WM8962_MSTR                             0x0040  /* MSTR */
#घोषणा WM8962_MSTR_MASK                        0x0040  /* MSTR */
#घोषणा WM8962_MSTR_SHIFT                            6  /* MSTR */
#घोषणा WM8962_MSTR_WIDTH                            1  /* MSTR */
#घोषणा WM8962_DAC_LRSWAP                       0x0020  /* DAC_LRSWAP */
#घोषणा WM8962_DAC_LRSWAP_MASK                  0x0020  /* DAC_LRSWAP */
#घोषणा WM8962_DAC_LRSWAP_SHIFT                      5  /* DAC_LRSWAP */
#घोषणा WM8962_DAC_LRSWAP_WIDTH                      1  /* DAC_LRSWAP */
#घोषणा WM8962_LRCLK_INV                        0x0010  /* LRCLK_INV */
#घोषणा WM8962_LRCLK_INV_MASK                   0x0010  /* LRCLK_INV */
#घोषणा WM8962_LRCLK_INV_SHIFT                       4  /* LRCLK_INV */
#घोषणा WM8962_LRCLK_INV_WIDTH                       1  /* LRCLK_INV */
#घोषणा WM8962_WL_MASK                          0x000C  /* WL - [3:2] */
#घोषणा WM8962_WL_SHIFT                              2  /* WL - [3:2] */
#घोषणा WM8962_WL_WIDTH                              2  /* WL - [3:2] */
#घोषणा WM8962_FMT_MASK                         0x0003  /* FMT - [1:0] */
#घोषणा WM8962_FMT_SHIFT                             0  /* FMT - [1:0] */
#घोषणा WM8962_FMT_WIDTH                             2  /* FMT - [1:0] */

/*
 * R8 (0x08) - Clocking2
 */
#घोषणा WM8962_CLKREG_OVD                       0x0800  /* CLKREG_OVD */
#घोषणा WM8962_CLKREG_OVD_MASK                  0x0800  /* CLKREG_OVD */
#घोषणा WM8962_CLKREG_OVD_SHIFT                     11  /* CLKREG_OVD */
#घोषणा WM8962_CLKREG_OVD_WIDTH                      1  /* CLKREG_OVD */
#घोषणा WM8962_SYSCLK_SRC_MASK                  0x0600  /* SYSCLK_SRC - [10:9] */
#घोषणा WM8962_SYSCLK_SRC_SHIFT                      9  /* SYSCLK_SRC - [10:9] */
#घोषणा WM8962_SYSCLK_SRC_WIDTH                      2  /* SYSCLK_SRC - [10:9] */
#घोषणा WM8962_CLASSD_CLK_DIV_MASK              0x01C0  /* CLASSD_CLK_DIV - [8:6] */
#घोषणा WM8962_CLASSD_CLK_DIV_SHIFT                  6  /* CLASSD_CLK_DIV - [8:6] */
#घोषणा WM8962_CLASSD_CLK_DIV_WIDTH                  3  /* CLASSD_CLK_DIV - [8:6] */
#घोषणा WM8962_SYSCLK_ENA                       0x0020  /* SYSCLK_ENA */
#घोषणा WM8962_SYSCLK_ENA_MASK                  0x0020  /* SYSCLK_ENA */
#घोषणा WM8962_SYSCLK_ENA_SHIFT                      5  /* SYSCLK_ENA */
#घोषणा WM8962_SYSCLK_ENA_WIDTH                      1  /* SYSCLK_ENA */
#घोषणा WM8962_BCLK_DIV_MASK                    0x000F  /* BCLK_DIV - [3:0] */
#घोषणा WM8962_BCLK_DIV_SHIFT                        0  /* BCLK_DIV - [3:0] */
#घोषणा WM8962_BCLK_DIV_WIDTH                        4  /* BCLK_DIV - [3:0] */

/*
 * R9 (0x09) - Audio Interface 1
 */
#घोषणा WM8962_AUTOMUTE_STS                     0x0800  /* AUTOMUTE_STS */
#घोषणा WM8962_AUTOMUTE_STS_MASK                0x0800  /* AUTOMUTE_STS */
#घोषणा WM8962_AUTOMUTE_STS_SHIFT                   11  /* AUTOMUTE_STS */
#घोषणा WM8962_AUTOMUTE_STS_WIDTH                    1  /* AUTOMUTE_STS */
#घोषणा WM8962_DAC_AUTOMUTE_SAMPLES_MASK        0x0300  /* DAC_AUTOMUTE_SAMPLES - [9:8] */
#घोषणा WM8962_DAC_AUTOMUTE_SAMPLES_SHIFT            8  /* DAC_AUTOMUTE_SAMPLES - [9:8] */
#घोषणा WM8962_DAC_AUTOMUTE_SAMPLES_WIDTH            2  /* DAC_AUTOMUTE_SAMPLES - [9:8] */
#घोषणा WM8962_DAC_AUTOMUTE                     0x0080  /* DAC_AUTOMUTE */
#घोषणा WM8962_DAC_AUTOMUTE_MASK                0x0080  /* DAC_AUTOMUTE */
#घोषणा WM8962_DAC_AUTOMUTE_SHIFT                    7  /* DAC_AUTOMUTE */
#घोषणा WM8962_DAC_AUTOMUTE_WIDTH                    1  /* DAC_AUTOMUTE */
#घोषणा WM8962_DAC_COMP                         0x0010  /* DAC_COMP */
#घोषणा WM8962_DAC_COMP_MASK                    0x0010  /* DAC_COMP */
#घोषणा WM8962_DAC_COMP_SHIFT                        4  /* DAC_COMP */
#घोषणा WM8962_DAC_COMP_WIDTH                        1  /* DAC_COMP */
#घोषणा WM8962_DAC_COMPMODE                     0x0008  /* DAC_COMPMODE */
#घोषणा WM8962_DAC_COMPMODE_MASK                0x0008  /* DAC_COMPMODE */
#घोषणा WM8962_DAC_COMPMODE_SHIFT                    3  /* DAC_COMPMODE */
#घोषणा WM8962_DAC_COMPMODE_WIDTH                    1  /* DAC_COMPMODE */
#घोषणा WM8962_ADC_COMP                         0x0004  /* ADC_COMP */
#घोषणा WM8962_ADC_COMP_MASK                    0x0004  /* ADC_COMP */
#घोषणा WM8962_ADC_COMP_SHIFT                        2  /* ADC_COMP */
#घोषणा WM8962_ADC_COMP_WIDTH                        1  /* ADC_COMP */
#घोषणा WM8962_ADC_COMPMODE                     0x0002  /* ADC_COMPMODE */
#घोषणा WM8962_ADC_COMPMODE_MASK                0x0002  /* ADC_COMPMODE */
#घोषणा WM8962_ADC_COMPMODE_SHIFT                    1  /* ADC_COMPMODE */
#घोषणा WM8962_ADC_COMPMODE_WIDTH                    1  /* ADC_COMPMODE */
#घोषणा WM8962_LOOPBACK                         0x0001  /* LOOPBACK */
#घोषणा WM8962_LOOPBACK_MASK                    0x0001  /* LOOPBACK */
#घोषणा WM8962_LOOPBACK_SHIFT                        0  /* LOOPBACK */
#घोषणा WM8962_LOOPBACK_WIDTH                        1  /* LOOPBACK */

/*
 * R10 (0x0A) - Left DAC volume
 */
#घोषणा WM8962_DAC_VU                           0x0100  /* DAC_VU */
#घोषणा WM8962_DAC_VU_MASK                      0x0100  /* DAC_VU */
#घोषणा WM8962_DAC_VU_SHIFT                          8  /* DAC_VU */
#घोषणा WM8962_DAC_VU_WIDTH                          1  /* DAC_VU */
#घोषणा WM8962_DACL_VOL_MASK                    0x00FF  /* DACL_VOL - [7:0] */
#घोषणा WM8962_DACL_VOL_SHIFT                        0  /* DACL_VOL - [7:0] */
#घोषणा WM8962_DACL_VOL_WIDTH                        8  /* DACL_VOL - [7:0] */

/*
 * R11 (0x0B) - Right DAC volume
 */
#घोषणा WM8962_DAC_VU                           0x0100  /* DAC_VU */
#घोषणा WM8962_DAC_VU_MASK                      0x0100  /* DAC_VU */
#घोषणा WM8962_DAC_VU_SHIFT                          8  /* DAC_VU */
#घोषणा WM8962_DAC_VU_WIDTH                          1  /* DAC_VU */
#घोषणा WM8962_DACR_VOL_MASK                    0x00FF  /* DACR_VOL - [7:0] */
#घोषणा WM8962_DACR_VOL_SHIFT                        0  /* DACR_VOL - [7:0] */
#घोषणा WM8962_DACR_VOL_WIDTH                        8  /* DACR_VOL - [7:0] */

/*
 * R14 (0x0E) - Audio Interface 2
 */
#घोषणा WM8962_AIF_RATE_MASK                    0x07FF  /* AIF_RATE - [10:0] */
#घोषणा WM8962_AIF_RATE_SHIFT                        0  /* AIF_RATE - [10:0] */
#घोषणा WM8962_AIF_RATE_WIDTH                       11  /* AIF_RATE - [10:0] */

/*
 * R15 (0x0F) - Software Reset
 */
#घोषणा WM8962_SW_RESET_MASK                    0xFFFF  /* SW_RESET - [15:0] */
#घोषणा WM8962_SW_RESET_SHIFT                        0  /* SW_RESET - [15:0] */
#घोषणा WM8962_SW_RESET_WIDTH                       16  /* SW_RESET - [15:0] */

/*
 * R17 (0x11) - ALC1
 */
#घोषणा WM8962_ALC_INACTIVE_ENA                 0x0400  /* ALC_INACTIVE_ENA */
#घोषणा WM8962_ALC_INACTIVE_ENA_MASK            0x0400  /* ALC_INACTIVE_ENA */
#घोषणा WM8962_ALC_INACTIVE_ENA_SHIFT               10  /* ALC_INACTIVE_ENA */
#घोषणा WM8962_ALC_INACTIVE_ENA_WIDTH                1  /* ALC_INACTIVE_ENA */
#घोषणा WM8962_ALC_LVL_MODE                     0x0200  /* ALC_LVL_MODE */
#घोषणा WM8962_ALC_LVL_MODE_MASK                0x0200  /* ALC_LVL_MODE */
#घोषणा WM8962_ALC_LVL_MODE_SHIFT                    9  /* ALC_LVL_MODE */
#घोषणा WM8962_ALC_LVL_MODE_WIDTH                    1  /* ALC_LVL_MODE */
#घोषणा WM8962_ALCL_ENA                         0x0100  /* ALCL_ENA */
#घोषणा WM8962_ALCL_ENA_MASK                    0x0100  /* ALCL_ENA */
#घोषणा WM8962_ALCL_ENA_SHIFT                        8  /* ALCL_ENA */
#घोषणा WM8962_ALCL_ENA_WIDTH                        1  /* ALCL_ENA */
#घोषणा WM8962_ALCR_ENA                         0x0080  /* ALCR_ENA */
#घोषणा WM8962_ALCR_ENA_MASK                    0x0080  /* ALCR_ENA */
#घोषणा WM8962_ALCR_ENA_SHIFT                        7  /* ALCR_ENA */
#घोषणा WM8962_ALCR_ENA_WIDTH                        1  /* ALCR_ENA */
#घोषणा WM8962_ALC_MAXGAIN_MASK                 0x0070  /* ALC_MAXGAIN - [6:4] */
#घोषणा WM8962_ALC_MAXGAIN_SHIFT                     4  /* ALC_MAXGAIN - [6:4] */
#घोषणा WM8962_ALC_MAXGAIN_WIDTH                     3  /* ALC_MAXGAIN - [6:4] */
#घोषणा WM8962_ALC_LVL_MASK                     0x000F  /* ALC_LVL - [3:0] */
#घोषणा WM8962_ALC_LVL_SHIFT                         0  /* ALC_LVL - [3:0] */
#घोषणा WM8962_ALC_LVL_WIDTH                         4  /* ALC_LVL - [3:0] */

/*
 * R18 (0x12) - ALC2
 */
#घोषणा WM8962_ALC_LOCK_STS                     0x8000  /* ALC_LOCK_STS */
#घोषणा WM8962_ALC_LOCK_STS_MASK                0x8000  /* ALC_LOCK_STS */
#घोषणा WM8962_ALC_LOCK_STS_SHIFT                   15  /* ALC_LOCK_STS */
#घोषणा WM8962_ALC_LOCK_STS_WIDTH                    1  /* ALC_LOCK_STS */
#घोषणा WM8962_ALC_THRESH_STS                   0x4000  /* ALC_THRESH_STS */
#घोषणा WM8962_ALC_THRESH_STS_MASK              0x4000  /* ALC_THRESH_STS */
#घोषणा WM8962_ALC_THRESH_STS_SHIFT                 14  /* ALC_THRESH_STS */
#घोषणा WM8962_ALC_THRESH_STS_WIDTH                  1  /* ALC_THRESH_STS */
#घोषणा WM8962_ALC_SAT_STS                      0x2000  /* ALC_SAT_STS */
#घोषणा WM8962_ALC_SAT_STS_MASK                 0x2000  /* ALC_SAT_STS */
#घोषणा WM8962_ALC_SAT_STS_SHIFT                    13  /* ALC_SAT_STS */
#घोषणा WM8962_ALC_SAT_STS_WIDTH                     1  /* ALC_SAT_STS */
#घोषणा WM8962_ALC_PKOVR_STS                    0x1000  /* ALC_PKOVR_STS */
#घोषणा WM8962_ALC_PKOVR_STS_MASK               0x1000  /* ALC_PKOVR_STS */
#घोषणा WM8962_ALC_PKOVR_STS_SHIFT                  12  /* ALC_PKOVR_STS */
#घोषणा WM8962_ALC_PKOVR_STS_WIDTH                   1  /* ALC_PKOVR_STS */
#घोषणा WM8962_ALC_NGATE_STS                    0x0800  /* ALC_NGATE_STS */
#घोषणा WM8962_ALC_NGATE_STS_MASK               0x0800  /* ALC_NGATE_STS */
#घोषणा WM8962_ALC_NGATE_STS_SHIFT                  11  /* ALC_NGATE_STS */
#घोषणा WM8962_ALC_NGATE_STS_WIDTH                   1  /* ALC_NGATE_STS */
#घोषणा WM8962_ALC_ZC                           0x0080  /* ALC_ZC */
#घोषणा WM8962_ALC_ZC_MASK                      0x0080  /* ALC_ZC */
#घोषणा WM8962_ALC_ZC_SHIFT                          7  /* ALC_ZC */
#घोषणा WM8962_ALC_ZC_WIDTH                          1  /* ALC_ZC */
#घोषणा WM8962_ALC_MINGAIN_MASK                 0x0070  /* ALC_MINGAIN - [6:4] */
#घोषणा WM8962_ALC_MINGAIN_SHIFT                     4  /* ALC_MINGAIN - [6:4] */
#घोषणा WM8962_ALC_MINGAIN_WIDTH                     3  /* ALC_MINGAIN - [6:4] */
#घोषणा WM8962_ALC_HLD_MASK                     0x000F  /* ALC_HLD - [3:0] */
#घोषणा WM8962_ALC_HLD_SHIFT                         0  /* ALC_HLD - [3:0] */
#घोषणा WM8962_ALC_HLD_WIDTH                         4  /* ALC_HLD - [3:0] */

/*
 * R19 (0x13) - ALC3
 */
#घोषणा WM8962_ALC_NGATE_GAIN_MASK              0x1C00  /* ALC_NGATE_GAIN - [12:10] */
#घोषणा WM8962_ALC_NGATE_GAIN_SHIFT                 10  /* ALC_NGATE_GAIN - [12:10] */
#घोषणा WM8962_ALC_NGATE_GAIN_WIDTH                  3  /* ALC_NGATE_GAIN - [12:10] */
#घोषणा WM8962_ALC_MODE                         0x0100  /* ALC_MODE */
#घोषणा WM8962_ALC_MODE_MASK                    0x0100  /* ALC_MODE */
#घोषणा WM8962_ALC_MODE_SHIFT                        8  /* ALC_MODE */
#घोषणा WM8962_ALC_MODE_WIDTH                        1  /* ALC_MODE */
#घोषणा WM8962_ALC_DCY_MASK                     0x00F0  /* ALC_DCY - [7:4] */
#घोषणा WM8962_ALC_DCY_SHIFT                         4  /* ALC_DCY - [7:4] */
#घोषणा WM8962_ALC_DCY_WIDTH                         4  /* ALC_DCY - [7:4] */
#घोषणा WM8962_ALC_ATK_MASK                     0x000F  /* ALC_ATK - [3:0] */
#घोषणा WM8962_ALC_ATK_SHIFT                         0  /* ALC_ATK - [3:0] */
#घोषणा WM8962_ALC_ATK_WIDTH                         4  /* ALC_ATK - [3:0] */

/*
 * R20 (0x14) - Noise Gate
 */
#घोषणा WM8962_ALC_NGATE_DCY_MASK               0xF000  /* ALC_NGATE_DCY - [15:12] */
#घोषणा WM8962_ALC_NGATE_DCY_SHIFT                  12  /* ALC_NGATE_DCY - [15:12] */
#घोषणा WM8962_ALC_NGATE_DCY_WIDTH                   4  /* ALC_NGATE_DCY - [15:12] */
#घोषणा WM8962_ALC_NGATE_ATK_MASK               0x0F00  /* ALC_NGATE_ATK - [11:8] */
#घोषणा WM8962_ALC_NGATE_ATK_SHIFT                   8  /* ALC_NGATE_ATK - [11:8] */
#घोषणा WM8962_ALC_NGATE_ATK_WIDTH                   4  /* ALC_NGATE_ATK - [11:8] */
#घोषणा WM8962_ALC_NGATE_THR_MASK               0x00F8  /* ALC_NGATE_THR - [7:3] */
#घोषणा WM8962_ALC_NGATE_THR_SHIFT                   3  /* ALC_NGATE_THR - [7:3] */
#घोषणा WM8962_ALC_NGATE_THR_WIDTH                   5  /* ALC_NGATE_THR - [7:3] */
#घोषणा WM8962_ALC_NGATE_MODE_MASK              0x0006  /* ALC_NGATE_MODE - [2:1] */
#घोषणा WM8962_ALC_NGATE_MODE_SHIFT                  1  /* ALC_NGATE_MODE - [2:1] */
#घोषणा WM8962_ALC_NGATE_MODE_WIDTH                  2  /* ALC_NGATE_MODE - [2:1] */
#घोषणा WM8962_ALC_NGATE_ENA                    0x0001  /* ALC_NGATE_ENA */
#घोषणा WM8962_ALC_NGATE_ENA_MASK               0x0001  /* ALC_NGATE_ENA */
#घोषणा WM8962_ALC_NGATE_ENA_SHIFT                   0  /* ALC_NGATE_ENA */
#घोषणा WM8962_ALC_NGATE_ENA_WIDTH                   1  /* ALC_NGATE_ENA */

/*
 * R21 (0x15) - Left ADC volume
 */
#घोषणा WM8962_ADC_VU                           0x0100  /* ADC_VU */
#घोषणा WM8962_ADC_VU_MASK                      0x0100  /* ADC_VU */
#घोषणा WM8962_ADC_VU_SHIFT                          8  /* ADC_VU */
#घोषणा WM8962_ADC_VU_WIDTH                          1  /* ADC_VU */
#घोषणा WM8962_ADCL_VOL_MASK                    0x00FF  /* ADCL_VOL - [7:0] */
#घोषणा WM8962_ADCL_VOL_SHIFT                        0  /* ADCL_VOL - [7:0] */
#घोषणा WM8962_ADCL_VOL_WIDTH                        8  /* ADCL_VOL - [7:0] */

/*
 * R22 (0x16) - Right ADC volume
 */
#घोषणा WM8962_ADC_VU                           0x0100  /* ADC_VU */
#घोषणा WM8962_ADC_VU_MASK                      0x0100  /* ADC_VU */
#घोषणा WM8962_ADC_VU_SHIFT                          8  /* ADC_VU */
#घोषणा WM8962_ADC_VU_WIDTH                          1  /* ADC_VU */
#घोषणा WM8962_ADCR_VOL_MASK                    0x00FF  /* ADCR_VOL - [7:0] */
#घोषणा WM8962_ADCR_VOL_SHIFT                        0  /* ADCR_VOL - [7:0] */
#घोषणा WM8962_ADCR_VOL_WIDTH                        8  /* ADCR_VOL - [7:0] */

/*
 * R23 (0x17) - Additional control(1)
 */
#घोषणा WM8962_THERR_ACT                        0x0100  /* THERR_ACT */
#घोषणा WM8962_THERR_ACT_MASK                   0x0100  /* THERR_ACT */
#घोषणा WM8962_THERR_ACT_SHIFT                       8  /* THERR_ACT */
#घोषणा WM8962_THERR_ACT_WIDTH                       1  /* THERR_ACT */
#घोषणा WM8962_ADC_BIAS                         0x0040  /* ADC_BIAS */
#घोषणा WM8962_ADC_BIAS_MASK                    0x0040  /* ADC_BIAS */
#घोषणा WM8962_ADC_BIAS_SHIFT                        6  /* ADC_BIAS */
#घोषणा WM8962_ADC_BIAS_WIDTH                        1  /* ADC_BIAS */
#घोषणा WM8962_ADC_HP                           0x0020  /* ADC_HP */
#घोषणा WM8962_ADC_HP_MASK                      0x0020  /* ADC_HP */
#घोषणा WM8962_ADC_HP_SHIFT                          5  /* ADC_HP */
#घोषणा WM8962_ADC_HP_WIDTH                          1  /* ADC_HP */
#घोषणा WM8962_TOCLK_ENA                        0x0001  /* TOCLK_ENA */
#घोषणा WM8962_TOCLK_ENA_MASK                   0x0001  /* TOCLK_ENA */
#घोषणा WM8962_TOCLK_ENA_SHIFT                       0  /* TOCLK_ENA */
#घोषणा WM8962_TOCLK_ENA_WIDTH                       1  /* TOCLK_ENA */

/*
 * R24 (0x18) - Additional control(2)
 */
#घोषणा WM8962_AIF_TRI                          0x0008  /* AIF_TRI */
#घोषणा WM8962_AIF_TRI_MASK                     0x0008  /* AIF_TRI */
#घोषणा WM8962_AIF_TRI_SHIFT                         3  /* AIF_TRI */
#घोषणा WM8962_AIF_TRI_WIDTH                         1  /* AIF_TRI */

/*
 * R25 (0x19) - Pwr Mgmt (1)
 */
#घोषणा WM8962_DMIC_ENA                         0x0400  /* DMIC_ENA */
#घोषणा WM8962_DMIC_ENA_MASK                    0x0400  /* DMIC_ENA */
#घोषणा WM8962_DMIC_ENA_SHIFT                       10  /* DMIC_ENA */
#घोषणा WM8962_DMIC_ENA_WIDTH                        1  /* DMIC_ENA */
#घोषणा WM8962_OPCLK_ENA                        0x0200  /* OPCLK_ENA */
#घोषणा WM8962_OPCLK_ENA_MASK                   0x0200  /* OPCLK_ENA */
#घोषणा WM8962_OPCLK_ENA_SHIFT                       9  /* OPCLK_ENA */
#घोषणा WM8962_OPCLK_ENA_WIDTH                       1  /* OPCLK_ENA */
#घोषणा WM8962_VMID_SEL_MASK                    0x0180  /* VMID_SEL - [8:7] */
#घोषणा WM8962_VMID_SEL_SHIFT                        7  /* VMID_SEL - [8:7] */
#घोषणा WM8962_VMID_SEL_WIDTH                        2  /* VMID_SEL - [8:7] */
#घोषणा WM8962_BIAS_ENA                         0x0040  /* BIAS_ENA */
#घोषणा WM8962_BIAS_ENA_MASK                    0x0040  /* BIAS_ENA */
#घोषणा WM8962_BIAS_ENA_SHIFT                        6  /* BIAS_ENA */
#घोषणा WM8962_BIAS_ENA_WIDTH                        1  /* BIAS_ENA */
#घोषणा WM8962_INL_ENA                          0x0020  /* INL_ENA */
#घोषणा WM8962_INL_ENA_MASK                     0x0020  /* INL_ENA */
#घोषणा WM8962_INL_ENA_SHIFT                         5  /* INL_ENA */
#घोषणा WM8962_INL_ENA_WIDTH                         1  /* INL_ENA */
#घोषणा WM8962_INR_ENA                          0x0010  /* INR_ENA */
#घोषणा WM8962_INR_ENA_MASK                     0x0010  /* INR_ENA */
#घोषणा WM8962_INR_ENA_SHIFT                         4  /* INR_ENA */
#घोषणा WM8962_INR_ENA_WIDTH                         1  /* INR_ENA */
#घोषणा WM8962_ADCL_ENA                         0x0008  /* ADCL_ENA */
#घोषणा WM8962_ADCL_ENA_MASK                    0x0008  /* ADCL_ENA */
#घोषणा WM8962_ADCL_ENA_SHIFT                        3  /* ADCL_ENA */
#घोषणा WM8962_ADCL_ENA_WIDTH                        1  /* ADCL_ENA */
#घोषणा WM8962_ADCR_ENA                         0x0004  /* ADCR_ENA */
#घोषणा WM8962_ADCR_ENA_MASK                    0x0004  /* ADCR_ENA */
#घोषणा WM8962_ADCR_ENA_SHIFT                        2  /* ADCR_ENA */
#घोषणा WM8962_ADCR_ENA_WIDTH                        1  /* ADCR_ENA */
#घोषणा WM8962_MICBIAS_ENA                      0x0002  /* MICBIAS_ENA */
#घोषणा WM8962_MICBIAS_ENA_MASK                 0x0002  /* MICBIAS_ENA */
#घोषणा WM8962_MICBIAS_ENA_SHIFT                     1  /* MICBIAS_ENA */
#घोषणा WM8962_MICBIAS_ENA_WIDTH                     1  /* MICBIAS_ENA */

/*
 * R26 (0x1A) - Pwr Mgmt (2)
 */
#घोषणा WM8962_DACL_ENA                         0x0100  /* DACL_ENA */
#घोषणा WM8962_DACL_ENA_MASK                    0x0100  /* DACL_ENA */
#घोषणा WM8962_DACL_ENA_SHIFT                        8  /* DACL_ENA */
#घोषणा WM8962_DACL_ENA_WIDTH                        1  /* DACL_ENA */
#घोषणा WM8962_DACR_ENA                         0x0080  /* DACR_ENA */
#घोषणा WM8962_DACR_ENA_MASK                    0x0080  /* DACR_ENA */
#घोषणा WM8962_DACR_ENA_SHIFT                        7  /* DACR_ENA */
#घोषणा WM8962_DACR_ENA_WIDTH                        1  /* DACR_ENA */
#घोषणा WM8962_HPOUTL_PGA_ENA                   0x0040  /* HPOUTL_PGA_ENA */
#घोषणा WM8962_HPOUTL_PGA_ENA_MASK              0x0040  /* HPOUTL_PGA_ENA */
#घोषणा WM8962_HPOUTL_PGA_ENA_SHIFT                  6  /* HPOUTL_PGA_ENA */
#घोषणा WM8962_HPOUTL_PGA_ENA_WIDTH                  1  /* HPOUTL_PGA_ENA */
#घोषणा WM8962_HPOUTR_PGA_ENA                   0x0020  /* HPOUTR_PGA_ENA */
#घोषणा WM8962_HPOUTR_PGA_ENA_MASK              0x0020  /* HPOUTR_PGA_ENA */
#घोषणा WM8962_HPOUTR_PGA_ENA_SHIFT                  5  /* HPOUTR_PGA_ENA */
#घोषणा WM8962_HPOUTR_PGA_ENA_WIDTH                  1  /* HPOUTR_PGA_ENA */
#घोषणा WM8962_SPKOUTL_PGA_ENA                  0x0010  /* SPKOUTL_PGA_ENA */
#घोषणा WM8962_SPKOUTL_PGA_ENA_MASK             0x0010  /* SPKOUTL_PGA_ENA */
#घोषणा WM8962_SPKOUTL_PGA_ENA_SHIFT                 4  /* SPKOUTL_PGA_ENA */
#घोषणा WM8962_SPKOUTL_PGA_ENA_WIDTH                 1  /* SPKOUTL_PGA_ENA */
#घोषणा WM8962_SPKOUTR_PGA_ENA                  0x0008  /* SPKOUTR_PGA_ENA */
#घोषणा WM8962_SPKOUTR_PGA_ENA_MASK             0x0008  /* SPKOUTR_PGA_ENA */
#घोषणा WM8962_SPKOUTR_PGA_ENA_SHIFT                 3  /* SPKOUTR_PGA_ENA */
#घोषणा WM8962_SPKOUTR_PGA_ENA_WIDTH                 1  /* SPKOUTR_PGA_ENA */
#घोषणा WM8962_HPOUTL_PGA_MUTE                  0x0002  /* HPOUTL_PGA_MUTE */
#घोषणा WM8962_HPOUTL_PGA_MUTE_MASK             0x0002  /* HPOUTL_PGA_MUTE */
#घोषणा WM8962_HPOUTL_PGA_MUTE_SHIFT                 1  /* HPOUTL_PGA_MUTE */
#घोषणा WM8962_HPOUTL_PGA_MUTE_WIDTH                 1  /* HPOUTL_PGA_MUTE */
#घोषणा WM8962_HPOUTR_PGA_MUTE                  0x0001  /* HPOUTR_PGA_MUTE */
#घोषणा WM8962_HPOUTR_PGA_MUTE_MASK             0x0001  /* HPOUTR_PGA_MUTE */
#घोषणा WM8962_HPOUTR_PGA_MUTE_SHIFT                 0  /* HPOUTR_PGA_MUTE */
#घोषणा WM8962_HPOUTR_PGA_MUTE_WIDTH                 1  /* HPOUTR_PGA_MUTE */

/*
 * R27 (0x1B) - Additional Control (3)
 */
#घोषणा WM8962_SAMPLE_RATE_INT_MODE             0x0010  /* SAMPLE_RATE_INT_MODE */
#घोषणा WM8962_SAMPLE_RATE_INT_MODE_MASK        0x0010  /* SAMPLE_RATE_INT_MODE */
#घोषणा WM8962_SAMPLE_RATE_INT_MODE_SHIFT            4  /* SAMPLE_RATE_INT_MODE */
#घोषणा WM8962_SAMPLE_RATE_INT_MODE_WIDTH            1  /* SAMPLE_RATE_INT_MODE */
#घोषणा WM8962_SAMPLE_RATE_MASK                 0x0007  /* SAMPLE_RATE - [2:0] */
#घोषणा WM8962_SAMPLE_RATE_SHIFT                     0  /* SAMPLE_RATE - [2:0] */
#घोषणा WM8962_SAMPLE_RATE_WIDTH                     3  /* SAMPLE_RATE - [2:0] */

/*
 * R28 (0x1C) - Anti-pop
 */
#घोषणा WM8962_STARTUP_BIAS_ENA                 0x0010  /* STARTUP_BIAS_ENA */
#घोषणा WM8962_STARTUP_BIAS_ENA_MASK            0x0010  /* STARTUP_BIAS_ENA */
#घोषणा WM8962_STARTUP_BIAS_ENA_SHIFT                4  /* STARTUP_BIAS_ENA */
#घोषणा WM8962_STARTUP_BIAS_ENA_WIDTH                1  /* STARTUP_BIAS_ENA */
#घोषणा WM8962_VMID_BUF_ENA                     0x0008  /* VMID_BUF_ENA */
#घोषणा WM8962_VMID_BUF_ENA_MASK                0x0008  /* VMID_BUF_ENA */
#घोषणा WM8962_VMID_BUF_ENA_SHIFT                    3  /* VMID_BUF_ENA */
#घोषणा WM8962_VMID_BUF_ENA_WIDTH                    1  /* VMID_BUF_ENA */
#घोषणा WM8962_VMID_RAMP                        0x0004  /* VMID_RAMP */
#घोषणा WM8962_VMID_RAMP_MASK                   0x0004  /* VMID_RAMP */
#घोषणा WM8962_VMID_RAMP_SHIFT                       2  /* VMID_RAMP */
#घोषणा WM8962_VMID_RAMP_WIDTH                       1  /* VMID_RAMP */

/*
 * R30 (0x1E) - Clocking 3
 */
#घोषणा WM8962_DBCLK_DIV_MASK                   0xE000  /* DBCLK_DIV - [15:13] */
#घोषणा WM8962_DBCLK_DIV_SHIFT                      13  /* DBCLK_DIV - [15:13] */
#घोषणा WM8962_DBCLK_DIV_WIDTH                       3  /* DBCLK_DIV - [15:13] */
#घोषणा WM8962_OPCLK_DIV_MASK                   0x1C00  /* OPCLK_DIV - [12:10] */
#घोषणा WM8962_OPCLK_DIV_SHIFT                      10  /* OPCLK_DIV - [12:10] */
#घोषणा WM8962_OPCLK_DIV_WIDTH                       3  /* OPCLK_DIV - [12:10] */
#घोषणा WM8962_TOCLK_DIV_MASK                   0x0380  /* TOCLK_DIV - [9:7] */
#घोषणा WM8962_TOCLK_DIV_SHIFT                       7  /* TOCLK_DIV - [9:7] */
#घोषणा WM8962_TOCLK_DIV_WIDTH                       3  /* TOCLK_DIV - [9:7] */
#घोषणा WM8962_F256KCLK_DIV_MASK                0x007E  /* F256KCLK_DIV - [6:1] */
#घोषणा WM8962_F256KCLK_DIV_SHIFT                    1  /* F256KCLK_DIV - [6:1] */
#घोषणा WM8962_F256KCLK_DIV_WIDTH                    6  /* F256KCLK_DIV - [6:1] */

/*
 * R31 (0x1F) - Input mixer control (1)
 */
#घोषणा WM8962_MIXINL_MUTE                      0x0008  /* MIXINL_MUTE */
#घोषणा WM8962_MIXINL_MUTE_MASK                 0x0008  /* MIXINL_MUTE */
#घोषणा WM8962_MIXINL_MUTE_SHIFT                     3  /* MIXINL_MUTE */
#घोषणा WM8962_MIXINL_MUTE_WIDTH                     1  /* MIXINL_MUTE */
#घोषणा WM8962_MIXINR_MUTE                      0x0004  /* MIXINR_MUTE */
#घोषणा WM8962_MIXINR_MUTE_MASK                 0x0004  /* MIXINR_MUTE */
#घोषणा WM8962_MIXINR_MUTE_SHIFT                     2  /* MIXINR_MUTE */
#घोषणा WM8962_MIXINR_MUTE_WIDTH                     1  /* MIXINR_MUTE */
#घोषणा WM8962_MIXINL_ENA                       0x0002  /* MIXINL_ENA */
#घोषणा WM8962_MIXINL_ENA_MASK                  0x0002  /* MIXINL_ENA */
#घोषणा WM8962_MIXINL_ENA_SHIFT                      1  /* MIXINL_ENA */
#घोषणा WM8962_MIXINL_ENA_WIDTH                      1  /* MIXINL_ENA */
#घोषणा WM8962_MIXINR_ENA                       0x0001  /* MIXINR_ENA */
#घोषणा WM8962_MIXINR_ENA_MASK                  0x0001  /* MIXINR_ENA */
#घोषणा WM8962_MIXINR_ENA_SHIFT                      0  /* MIXINR_ENA */
#घोषणा WM8962_MIXINR_ENA_WIDTH                      1  /* MIXINR_ENA */

/*
 * R32 (0x20) - Left input mixer volume
 */
#घोषणा WM8962_IN2L_MIXINL_VOL_MASK             0x01C0  /* IN2L_MIXINL_VOL - [8:6] */
#घोषणा WM8962_IN2L_MIXINL_VOL_SHIFT                 6  /* IN2L_MIXINL_VOL - [8:6] */
#घोषणा WM8962_IN2L_MIXINL_VOL_WIDTH                 3  /* IN2L_MIXINL_VOL - [8:6] */
#घोषणा WM8962_INPGAL_MIXINL_VOL_MASK           0x0038  /* INPGAL_MIXINL_VOL - [5:3] */
#घोषणा WM8962_INPGAL_MIXINL_VOL_SHIFT               3  /* INPGAL_MIXINL_VOL - [5:3] */
#घोषणा WM8962_INPGAL_MIXINL_VOL_WIDTH               3  /* INPGAL_MIXINL_VOL - [5:3] */
#घोषणा WM8962_IN3L_MIXINL_VOL_MASK             0x0007  /* IN3L_MIXINL_VOL - [2:0] */
#घोषणा WM8962_IN3L_MIXINL_VOL_SHIFT                 0  /* IN3L_MIXINL_VOL - [2:0] */
#घोषणा WM8962_IN3L_MIXINL_VOL_WIDTH                 3  /* IN3L_MIXINL_VOL - [2:0] */

/*
 * R33 (0x21) - Right input mixer volume
 */
#घोषणा WM8962_IN2R_MIXINR_VOL_MASK             0x01C0  /* IN2R_MIXINR_VOL - [8:6] */
#घोषणा WM8962_IN2R_MIXINR_VOL_SHIFT                 6  /* IN2R_MIXINR_VOL - [8:6] */
#घोषणा WM8962_IN2R_MIXINR_VOL_WIDTH                 3  /* IN2R_MIXINR_VOL - [8:6] */
#घोषणा WM8962_INPGAR_MIXINR_VOL_MASK           0x0038  /* INPGAR_MIXINR_VOL - [5:3] */
#घोषणा WM8962_INPGAR_MIXINR_VOL_SHIFT               3  /* INPGAR_MIXINR_VOL - [5:3] */
#घोषणा WM8962_INPGAR_MIXINR_VOL_WIDTH               3  /* INPGAR_MIXINR_VOL - [5:3] */
#घोषणा WM8962_IN3R_MIXINR_VOL_MASK             0x0007  /* IN3R_MIXINR_VOL - [2:0] */
#घोषणा WM8962_IN3R_MIXINR_VOL_SHIFT                 0  /* IN3R_MIXINR_VOL - [2:0] */
#घोषणा WM8962_IN3R_MIXINR_VOL_WIDTH                 3  /* IN3R_MIXINR_VOL - [2:0] */

/*
 * R34 (0x22) - Input mixer control (2)
 */
#घोषणा WM8962_IN2L_TO_MIXINL                   0x0020  /* IN2L_TO_MIXINL */
#घोषणा WM8962_IN2L_TO_MIXINL_MASK              0x0020  /* IN2L_TO_MIXINL */
#घोषणा WM8962_IN2L_TO_MIXINL_SHIFT                  5  /* IN2L_TO_MIXINL */
#घोषणा WM8962_IN2L_TO_MIXINL_WIDTH                  1  /* IN2L_TO_MIXINL */
#घोषणा WM8962_IN3L_TO_MIXINL                   0x0010  /* IN3L_TO_MIXINL */
#घोषणा WM8962_IN3L_TO_MIXINL_MASK              0x0010  /* IN3L_TO_MIXINL */
#घोषणा WM8962_IN3L_TO_MIXINL_SHIFT                  4  /* IN3L_TO_MIXINL */
#घोषणा WM8962_IN3L_TO_MIXINL_WIDTH                  1  /* IN3L_TO_MIXINL */
#घोषणा WM8962_INPGAL_TO_MIXINL                 0x0008  /* INPGAL_TO_MIXINL */
#घोषणा WM8962_INPGAL_TO_MIXINL_MASK            0x0008  /* INPGAL_TO_MIXINL */
#घोषणा WM8962_INPGAL_TO_MIXINL_SHIFT                3  /* INPGAL_TO_MIXINL */
#घोषणा WM8962_INPGAL_TO_MIXINL_WIDTH                1  /* INPGAL_TO_MIXINL */
#घोषणा WM8962_IN2R_TO_MIXINR                   0x0004  /* IN2R_TO_MIXINR */
#घोषणा WM8962_IN2R_TO_MIXINR_MASK              0x0004  /* IN2R_TO_MIXINR */
#घोषणा WM8962_IN2R_TO_MIXINR_SHIFT                  2  /* IN2R_TO_MIXINR */
#घोषणा WM8962_IN2R_TO_MIXINR_WIDTH                  1  /* IN2R_TO_MIXINR */
#घोषणा WM8962_IN3R_TO_MIXINR                   0x0002  /* IN3R_TO_MIXINR */
#घोषणा WM8962_IN3R_TO_MIXINR_MASK              0x0002  /* IN3R_TO_MIXINR */
#घोषणा WM8962_IN3R_TO_MIXINR_SHIFT                  1  /* IN3R_TO_MIXINR */
#घोषणा WM8962_IN3R_TO_MIXINR_WIDTH                  1  /* IN3R_TO_MIXINR */
#घोषणा WM8962_INPGAR_TO_MIXINR                 0x0001  /* INPGAR_TO_MIXINR */
#घोषणा WM8962_INPGAR_TO_MIXINR_MASK            0x0001  /* INPGAR_TO_MIXINR */
#घोषणा WM8962_INPGAR_TO_MIXINR_SHIFT                0  /* INPGAR_TO_MIXINR */
#घोषणा WM8962_INPGAR_TO_MIXINR_WIDTH                1  /* INPGAR_TO_MIXINR */

/*
 * R35 (0x23) - Input bias control
 */
#घोषणा WM8962_MIXIN_BIAS_MASK                  0x0038  /* MIXIN_BIAS - [5:3] */
#घोषणा WM8962_MIXIN_BIAS_SHIFT                      3  /* MIXIN_BIAS - [5:3] */
#घोषणा WM8962_MIXIN_BIAS_WIDTH                      3  /* MIXIN_BIAS - [5:3] */
#घोषणा WM8962_INPGA_BIAS_MASK                  0x0007  /* INPGA_BIAS - [2:0] */
#घोषणा WM8962_INPGA_BIAS_SHIFT                      0  /* INPGA_BIAS - [2:0] */
#घोषणा WM8962_INPGA_BIAS_WIDTH                      3  /* INPGA_BIAS - [2:0] */

/*
 * R37 (0x25) - Left input PGA control
 */
#घोषणा WM8962_INPGAL_ENA                       0x0010  /* INPGAL_ENA */
#घोषणा WM8962_INPGAL_ENA_MASK                  0x0010  /* INPGAL_ENA */
#घोषणा WM8962_INPGAL_ENA_SHIFT                      4  /* INPGAL_ENA */
#घोषणा WM8962_INPGAL_ENA_WIDTH                      1  /* INPGAL_ENA */
#घोषणा WM8962_IN1L_TO_INPGAL                   0x0008  /* IN1L_TO_INPGAL */
#घोषणा WM8962_IN1L_TO_INPGAL_MASK              0x0008  /* IN1L_TO_INPGAL */
#घोषणा WM8962_IN1L_TO_INPGAL_SHIFT                  3  /* IN1L_TO_INPGAL */
#घोषणा WM8962_IN1L_TO_INPGAL_WIDTH                  1  /* IN1L_TO_INPGAL */
#घोषणा WM8962_IN2L_TO_INPGAL                   0x0004  /* IN2L_TO_INPGAL */
#घोषणा WM8962_IN2L_TO_INPGAL_MASK              0x0004  /* IN2L_TO_INPGAL */
#घोषणा WM8962_IN2L_TO_INPGAL_SHIFT                  2  /* IN2L_TO_INPGAL */
#घोषणा WM8962_IN2L_TO_INPGAL_WIDTH                  1  /* IN2L_TO_INPGAL */
#घोषणा WM8962_IN3L_TO_INPGAL                   0x0002  /* IN3L_TO_INPGAL */
#घोषणा WM8962_IN3L_TO_INPGAL_MASK              0x0002  /* IN3L_TO_INPGAL */
#घोषणा WM8962_IN3L_TO_INPGAL_SHIFT                  1  /* IN3L_TO_INPGAL */
#घोषणा WM8962_IN3L_TO_INPGAL_WIDTH                  1  /* IN3L_TO_INPGAL */
#घोषणा WM8962_IN4L_TO_INPGAL                   0x0001  /* IN4L_TO_INPGAL */
#घोषणा WM8962_IN4L_TO_INPGAL_MASK              0x0001  /* IN4L_TO_INPGAL */
#घोषणा WM8962_IN4L_TO_INPGAL_SHIFT                  0  /* IN4L_TO_INPGAL */
#घोषणा WM8962_IN4L_TO_INPGAL_WIDTH                  1  /* IN4L_TO_INPGAL */

/*
 * R38 (0x26) - Right input PGA control
 */
#घोषणा WM8962_INPGAR_ENA                       0x0010  /* INPGAR_ENA */
#घोषणा WM8962_INPGAR_ENA_MASK                  0x0010  /* INPGAR_ENA */
#घोषणा WM8962_INPGAR_ENA_SHIFT                      4  /* INPGAR_ENA */
#घोषणा WM8962_INPGAR_ENA_WIDTH                      1  /* INPGAR_ENA */
#घोषणा WM8962_IN1R_TO_INPGAR                   0x0008  /* IN1R_TO_INPGAR */
#घोषणा WM8962_IN1R_TO_INPGAR_MASK              0x0008  /* IN1R_TO_INPGAR */
#घोषणा WM8962_IN1R_TO_INPGAR_SHIFT                  3  /* IN1R_TO_INPGAR */
#घोषणा WM8962_IN1R_TO_INPGAR_WIDTH                  1  /* IN1R_TO_INPGAR */
#घोषणा WM8962_IN2R_TO_INPGAR                   0x0004  /* IN2R_TO_INPGAR */
#घोषणा WM8962_IN2R_TO_INPGAR_MASK              0x0004  /* IN2R_TO_INPGAR */
#घोषणा WM8962_IN2R_TO_INPGAR_SHIFT                  2  /* IN2R_TO_INPGAR */
#घोषणा WM8962_IN2R_TO_INPGAR_WIDTH                  1  /* IN2R_TO_INPGAR */
#घोषणा WM8962_IN3R_TO_INPGAR                   0x0002  /* IN3R_TO_INPGAR */
#घोषणा WM8962_IN3R_TO_INPGAR_MASK              0x0002  /* IN3R_TO_INPGAR */
#घोषणा WM8962_IN3R_TO_INPGAR_SHIFT                  1  /* IN3R_TO_INPGAR */
#घोषणा WM8962_IN3R_TO_INPGAR_WIDTH                  1  /* IN3R_TO_INPGAR */
#घोषणा WM8962_IN4R_TO_INPGAR                   0x0001  /* IN4R_TO_INPGAR */
#घोषणा WM8962_IN4R_TO_INPGAR_MASK              0x0001  /* IN4R_TO_INPGAR */
#घोषणा WM8962_IN4R_TO_INPGAR_SHIFT                  0  /* IN4R_TO_INPGAR */
#घोषणा WM8962_IN4R_TO_INPGAR_WIDTH                  1  /* IN4R_TO_INPGAR */

/*
 * R40 (0x28) - SPKOUTL volume
 */
#घोषणा WM8962_SPKOUT_VU                        0x0100  /* SPKOUT_VU */
#घोषणा WM8962_SPKOUT_VU_MASK                   0x0100  /* SPKOUT_VU */
#घोषणा WM8962_SPKOUT_VU_SHIFT                       8  /* SPKOUT_VU */
#घोषणा WM8962_SPKOUT_VU_WIDTH                       1  /* SPKOUT_VU */
#घोषणा WM8962_SPKOUTL_ZC                       0x0080  /* SPKOUTL_ZC */
#घोषणा WM8962_SPKOUTL_ZC_MASK                  0x0080  /* SPKOUTL_ZC */
#घोषणा WM8962_SPKOUTL_ZC_SHIFT                      7  /* SPKOUTL_ZC */
#घोषणा WM8962_SPKOUTL_ZC_WIDTH                      1  /* SPKOUTL_ZC */
#घोषणा WM8962_SPKOUTL_VOL_MASK                 0x007F  /* SPKOUTL_VOL - [6:0] */
#घोषणा WM8962_SPKOUTL_VOL_SHIFT                     0  /* SPKOUTL_VOL - [6:0] */
#घोषणा WM8962_SPKOUTL_VOL_WIDTH                     7  /* SPKOUTL_VOL - [6:0] */

/*
 * R41 (0x29) - SPKOUTR volume
 */
#घोषणा WM8962_SPKOUTR_ZC                       0x0080  /* SPKOUTR_ZC */
#घोषणा WM8962_SPKOUTR_ZC_MASK                  0x0080  /* SPKOUTR_ZC */
#घोषणा WM8962_SPKOUTR_ZC_SHIFT                      7  /* SPKOUTR_ZC */
#घोषणा WM8962_SPKOUTR_ZC_WIDTH                      1  /* SPKOUTR_ZC */
#घोषणा WM8962_SPKOUTR_VOL_MASK                 0x007F  /* SPKOUTR_VOL - [6:0] */
#घोषणा WM8962_SPKOUTR_VOL_SHIFT                     0  /* SPKOUTR_VOL - [6:0] */
#घोषणा WM8962_SPKOUTR_VOL_WIDTH                     7  /* SPKOUTR_VOL - [6:0] */

/*
 * R47 (0x2F) - Thermal Shutकरोwn Status
 */
#घोषणा WM8962_TEMP_ERR_HP                      0x0008  /* TEMP_ERR_HP */
#घोषणा WM8962_TEMP_ERR_HP_MASK                 0x0008  /* TEMP_ERR_HP */
#घोषणा WM8962_TEMP_ERR_HP_SHIFT                     3  /* TEMP_ERR_HP */
#घोषणा WM8962_TEMP_ERR_HP_WIDTH                     1  /* TEMP_ERR_HP */
#घोषणा WM8962_TEMP_WARN_HP                     0x0004  /* TEMP_WARN_HP */
#घोषणा WM8962_TEMP_WARN_HP_MASK                0x0004  /* TEMP_WARN_HP */
#घोषणा WM8962_TEMP_WARN_HP_SHIFT                    2  /* TEMP_WARN_HP */
#घोषणा WM8962_TEMP_WARN_HP_WIDTH                    1  /* TEMP_WARN_HP */
#घोषणा WM8962_TEMP_ERR_SPK                     0x0002  /* TEMP_ERR_SPK */
#घोषणा WM8962_TEMP_ERR_SPK_MASK                0x0002  /* TEMP_ERR_SPK */
#घोषणा WM8962_TEMP_ERR_SPK_SHIFT                    1  /* TEMP_ERR_SPK */
#घोषणा WM8962_TEMP_ERR_SPK_WIDTH                    1  /* TEMP_ERR_SPK */
#घोषणा WM8962_TEMP_WARN_SPK                    0x0001  /* TEMP_WARN_SPK */
#घोषणा WM8962_TEMP_WARN_SPK_MASK               0x0001  /* TEMP_WARN_SPK */
#घोषणा WM8962_TEMP_WARN_SPK_SHIFT                   0  /* TEMP_WARN_SPK */
#घोषणा WM8962_TEMP_WARN_SPK_WIDTH                   1  /* TEMP_WARN_SPK */

/*
 * R48 (0x30) - Additional Control (4)
 */
#घोषणा WM8962_MICDET_THR_MASK                  0x7000  /* MICDET_THR - [14:12] */
#घोषणा WM8962_MICDET_THR_SHIFT                     12  /* MICDET_THR - [14:12] */
#घोषणा WM8962_MICDET_THR_WIDTH                      3  /* MICDET_THR - [14:12] */
#घोषणा WM8962_MICSHORT_THR_MASK                0x0C00  /* MICSHORT_THR - [11:10] */
#घोषणा WM8962_MICSHORT_THR_SHIFT                   10  /* MICSHORT_THR - [11:10] */
#घोषणा WM8962_MICSHORT_THR_WIDTH                    2  /* MICSHORT_THR - [11:10] */
#घोषणा WM8962_MICDET_ENA                       0x0200  /* MICDET_ENA */
#घोषणा WM8962_MICDET_ENA_MASK                  0x0200  /* MICDET_ENA */
#घोषणा WM8962_MICDET_ENA_SHIFT                      9  /* MICDET_ENA */
#घोषणा WM8962_MICDET_ENA_WIDTH                      1  /* MICDET_ENA */
#घोषणा WM8962_MICDET_STS                       0x0080  /* MICDET_STS */
#घोषणा WM8962_MICDET_STS_MASK                  0x0080  /* MICDET_STS */
#घोषणा WM8962_MICDET_STS_SHIFT                      7  /* MICDET_STS */
#घोषणा WM8962_MICDET_STS_WIDTH                      1  /* MICDET_STS */
#घोषणा WM8962_MICSHORT_STS                     0x0040  /* MICSHORT_STS */
#घोषणा WM8962_MICSHORT_STS_MASK                0x0040  /* MICSHORT_STS */
#घोषणा WM8962_MICSHORT_STS_SHIFT                    6  /* MICSHORT_STS */
#घोषणा WM8962_MICSHORT_STS_WIDTH                    1  /* MICSHORT_STS */
#घोषणा WM8962_TEMP_ENA_HP                      0x0004  /* TEMP_ENA_HP */
#घोषणा WM8962_TEMP_ENA_HP_MASK                 0x0004  /* TEMP_ENA_HP */
#घोषणा WM8962_TEMP_ENA_HP_SHIFT                     2  /* TEMP_ENA_HP */
#घोषणा WM8962_TEMP_ENA_HP_WIDTH                     1  /* TEMP_ENA_HP */
#घोषणा WM8962_TEMP_ENA_SPK                     0x0002  /* TEMP_ENA_SPK */
#घोषणा WM8962_TEMP_ENA_SPK_MASK                0x0002  /* TEMP_ENA_SPK */
#घोषणा WM8962_TEMP_ENA_SPK_SHIFT                    1  /* TEMP_ENA_SPK */
#घोषणा WM8962_TEMP_ENA_SPK_WIDTH                    1  /* TEMP_ENA_SPK */
#घोषणा WM8962_MICBIAS_LVL                      0x0001  /* MICBIAS_LVL */
#घोषणा WM8962_MICBIAS_LVL_MASK                 0x0001  /* MICBIAS_LVL */
#घोषणा WM8962_MICBIAS_LVL_SHIFT                     0  /* MICBIAS_LVL */
#घोषणा WM8962_MICBIAS_LVL_WIDTH                     1  /* MICBIAS_LVL */

/*
 * R49 (0x31) - Class D Control 1
 */
#घोषणा WM8962_SPKOUTR_ENA                      0x0080  /* SPKOUTR_ENA */
#घोषणा WM8962_SPKOUTR_ENA_MASK                 0x0080  /* SPKOUTR_ENA */
#घोषणा WM8962_SPKOUTR_ENA_SHIFT                     7  /* SPKOUTR_ENA */
#घोषणा WM8962_SPKOUTR_ENA_WIDTH                     1  /* SPKOUTR_ENA */
#घोषणा WM8962_SPKOUTL_ENA                      0x0040  /* SPKOUTL_ENA */
#घोषणा WM8962_SPKOUTL_ENA_MASK                 0x0040  /* SPKOUTL_ENA */
#घोषणा WM8962_SPKOUTL_ENA_SHIFT                     6  /* SPKOUTL_ENA */
#घोषणा WM8962_SPKOUTL_ENA_WIDTH                     1  /* SPKOUTL_ENA */
#घोषणा WM8962_DAC_MUTE_ALT                     0x0010  /* DAC_MUTE */
#घोषणा WM8962_DAC_MUTE_ALT_MASK                0x0010  /* DAC_MUTE */
#घोषणा WM8962_DAC_MUTE_ALT_SHIFT                    4  /* DAC_MUTE */
#घोषणा WM8962_DAC_MUTE_ALT_WIDTH                    1  /* DAC_MUTE */
#घोषणा WM8962_SPKOUTL_PGA_MUTE                 0x0002  /* SPKOUTL_PGA_MUTE */
#घोषणा WM8962_SPKOUTL_PGA_MUTE_MASK            0x0002  /* SPKOUTL_PGA_MUTE */
#घोषणा WM8962_SPKOUTL_PGA_MUTE_SHIFT                1  /* SPKOUTL_PGA_MUTE */
#घोषणा WM8962_SPKOUTL_PGA_MUTE_WIDTH                1  /* SPKOUTL_PGA_MUTE */
#घोषणा WM8962_SPKOUTR_PGA_MUTE                 0x0001  /* SPKOUTR_PGA_MUTE */
#घोषणा WM8962_SPKOUTR_PGA_MUTE_MASK            0x0001  /* SPKOUTR_PGA_MUTE */
#घोषणा WM8962_SPKOUTR_PGA_MUTE_SHIFT                0  /* SPKOUTR_PGA_MUTE */
#घोषणा WM8962_SPKOUTR_PGA_MUTE_WIDTH                1  /* SPKOUTR_PGA_MUTE */

/*
 * R51 (0x33) - Class D Control 2
 */
#घोषणा WM8962_SPK_MONO                         0x0040  /* SPK_MONO */
#घोषणा WM8962_SPK_MONO_MASK                    0x0040  /* SPK_MONO */
#घोषणा WM8962_SPK_MONO_SHIFT                        6  /* SPK_MONO */
#घोषणा WM8962_SPK_MONO_WIDTH                        1  /* SPK_MONO */
#घोषणा WM8962_CLASSD_VOL_MASK                  0x0007  /* CLASSD_VOL - [2:0] */
#घोषणा WM8962_CLASSD_VOL_SHIFT                      0  /* CLASSD_VOL - [2:0] */
#घोषणा WM8962_CLASSD_VOL_WIDTH                      3  /* CLASSD_VOL - [2:0] */

/*
 * R56 (0x38) - Clocking 4
 */
#घोषणा WM8962_SYSCLK_RATE_MASK                 0x001E  /* SYSCLK_RATE - [4:1] */
#घोषणा WM8962_SYSCLK_RATE_SHIFT                     1  /* SYSCLK_RATE - [4:1] */
#घोषणा WM8962_SYSCLK_RATE_WIDTH                     4  /* SYSCLK_RATE - [4:1] */

/*
 * R57 (0x39) - DAC DSP Mixing (1)
 */
#घोषणा WM8962_DAC_MONOMIX                      0x0200  /* DAC_MONOMIX */
#घोषणा WM8962_DAC_MONOMIX_MASK                 0x0200  /* DAC_MONOMIX */
#घोषणा WM8962_DAC_MONOMIX_SHIFT                     9  /* DAC_MONOMIX */
#घोषणा WM8962_DAC_MONOMIX_WIDTH                     1  /* DAC_MONOMIX */
#घोषणा WM8962_ADCR_DAC_SVOL_MASK               0x00F0  /* ADCR_DAC_SVOL - [7:4] */
#घोषणा WM8962_ADCR_DAC_SVOL_SHIFT                   4  /* ADCR_DAC_SVOL - [7:4] */
#घोषणा WM8962_ADCR_DAC_SVOL_WIDTH                   4  /* ADCR_DAC_SVOL - [7:4] */
#घोषणा WM8962_ADC_TO_DACR_MASK                 0x000C  /* ADC_TO_DACR - [3:2] */
#घोषणा WM8962_ADC_TO_DACR_SHIFT                     2  /* ADC_TO_DACR - [3:2] */
#घोषणा WM8962_ADC_TO_DACR_WIDTH                     2  /* ADC_TO_DACR - [3:2] */

/*
 * R58 (0x3A) - DAC DSP Mixing (2)
 */
#घोषणा WM8962_ADCL_DAC_SVOL_MASK               0x00F0  /* ADCL_DAC_SVOL - [7:4] */
#घोषणा WM8962_ADCL_DAC_SVOL_SHIFT                   4  /* ADCL_DAC_SVOL - [7:4] */
#घोषणा WM8962_ADCL_DAC_SVOL_WIDTH                   4  /* ADCL_DAC_SVOL - [7:4] */
#घोषणा WM8962_ADC_TO_DACL_MASK                 0x000C  /* ADC_TO_DACL - [3:2] */
#घोषणा WM8962_ADC_TO_DACL_SHIFT                     2  /* ADC_TO_DACL - [3:2] */
#घोषणा WM8962_ADC_TO_DACL_WIDTH                     2  /* ADC_TO_DACL - [3:2] */

/*
 * R60 (0x3C) - DC Servo 0
 */
#घोषणा WM8962_INL_DCS_ENA                      0x0080  /* INL_DCS_ENA */
#घोषणा WM8962_INL_DCS_ENA_MASK                 0x0080  /* INL_DCS_ENA */
#घोषणा WM8962_INL_DCS_ENA_SHIFT                     7  /* INL_DCS_ENA */
#घोषणा WM8962_INL_DCS_ENA_WIDTH                     1  /* INL_DCS_ENA */
#घोषणा WM8962_INL_DCS_STARTUP                  0x0040  /* INL_DCS_STARTUP */
#घोषणा WM8962_INL_DCS_STARTUP_MASK             0x0040  /* INL_DCS_STARTUP */
#घोषणा WM8962_INL_DCS_STARTUP_SHIFT                 6  /* INL_DCS_STARTUP */
#घोषणा WM8962_INL_DCS_STARTUP_WIDTH                 1  /* INL_DCS_STARTUP */
#घोषणा WM8962_INR_DCS_ENA                      0x0008  /* INR_DCS_ENA */
#घोषणा WM8962_INR_DCS_ENA_MASK                 0x0008  /* INR_DCS_ENA */
#घोषणा WM8962_INR_DCS_ENA_SHIFT                     3  /* INR_DCS_ENA */
#घोषणा WM8962_INR_DCS_ENA_WIDTH                     1  /* INR_DCS_ENA */
#घोषणा WM8962_INR_DCS_STARTUP                  0x0004  /* INR_DCS_STARTUP */
#घोषणा WM8962_INR_DCS_STARTUP_MASK             0x0004  /* INR_DCS_STARTUP */
#घोषणा WM8962_INR_DCS_STARTUP_SHIFT                 2  /* INR_DCS_STARTUP */
#घोषणा WM8962_INR_DCS_STARTUP_WIDTH                 1  /* INR_DCS_STARTUP */

/*
 * R61 (0x3D) - DC Servo 1
 */
#घोषणा WM8962_HP1L_DCS_ENA                     0x0080  /* HP1L_DCS_ENA */
#घोषणा WM8962_HP1L_DCS_ENA_MASK                0x0080  /* HP1L_DCS_ENA */
#घोषणा WM8962_HP1L_DCS_ENA_SHIFT                    7  /* HP1L_DCS_ENA */
#घोषणा WM8962_HP1L_DCS_ENA_WIDTH                    1  /* HP1L_DCS_ENA */
#घोषणा WM8962_HP1L_DCS_STARTUP                 0x0040  /* HP1L_DCS_STARTUP */
#घोषणा WM8962_HP1L_DCS_STARTUP_MASK            0x0040  /* HP1L_DCS_STARTUP */
#घोषणा WM8962_HP1L_DCS_STARTUP_SHIFT                6  /* HP1L_DCS_STARTUP */
#घोषणा WM8962_HP1L_DCS_STARTUP_WIDTH                1  /* HP1L_DCS_STARTUP */
#घोषणा WM8962_HP1L_DCS_SYNC                    0x0010  /* HP1L_DCS_SYNC */
#घोषणा WM8962_HP1L_DCS_SYNC_MASK               0x0010  /* HP1L_DCS_SYNC */
#घोषणा WM8962_HP1L_DCS_SYNC_SHIFT                   4  /* HP1L_DCS_SYNC */
#घोषणा WM8962_HP1L_DCS_SYNC_WIDTH                   1  /* HP1L_DCS_SYNC */
#घोषणा WM8962_HP1R_DCS_ENA                     0x0008  /* HP1R_DCS_ENA */
#घोषणा WM8962_HP1R_DCS_ENA_MASK                0x0008  /* HP1R_DCS_ENA */
#घोषणा WM8962_HP1R_DCS_ENA_SHIFT                    3  /* HP1R_DCS_ENA */
#घोषणा WM8962_HP1R_DCS_ENA_WIDTH                    1  /* HP1R_DCS_ENA */
#घोषणा WM8962_HP1R_DCS_STARTUP                 0x0004  /* HP1R_DCS_STARTUP */
#घोषणा WM8962_HP1R_DCS_STARTUP_MASK            0x0004  /* HP1R_DCS_STARTUP */
#घोषणा WM8962_HP1R_DCS_STARTUP_SHIFT                2  /* HP1R_DCS_STARTUP */
#घोषणा WM8962_HP1R_DCS_STARTUP_WIDTH                1  /* HP1R_DCS_STARTUP */
#घोषणा WM8962_HP1R_DCS_SYNC                    0x0001  /* HP1R_DCS_SYNC */
#घोषणा WM8962_HP1R_DCS_SYNC_MASK               0x0001  /* HP1R_DCS_SYNC */
#घोषणा WM8962_HP1R_DCS_SYNC_SHIFT                   0  /* HP1R_DCS_SYNC */
#घोषणा WM8962_HP1R_DCS_SYNC_WIDTH                   1  /* HP1R_DCS_SYNC */

/*
 * R64 (0x40) - DC Servo 4
 */
#घोषणा WM8962_HP1_DCS_SYNC_STEPS_MASK          0x3F80  /* HP1_DCS_SYNC_STEPS - [13:7] */
#घोषणा WM8962_HP1_DCS_SYNC_STEPS_SHIFT              7  /* HP1_DCS_SYNC_STEPS - [13:7] */
#घोषणा WM8962_HP1_DCS_SYNC_STEPS_WIDTH              7  /* HP1_DCS_SYNC_STEPS - [13:7] */

/*
 * R66 (0x42) - DC Servo 6
 */
#घोषणा WM8962_DCS_STARTUP_DONE_INL             0x0400  /* DCS_STARTUP_DONE_INL */
#घोषणा WM8962_DCS_STARTUP_DONE_INL_MASK        0x0400  /* DCS_STARTUP_DONE_INL */
#घोषणा WM8962_DCS_STARTUP_DONE_INL_SHIFT           10  /* DCS_STARTUP_DONE_INL */
#घोषणा WM8962_DCS_STARTUP_DONE_INL_WIDTH            1  /* DCS_STARTUP_DONE_INL */
#घोषणा WM8962_DCS_STARTUP_DONE_INR             0x0200  /* DCS_STARTUP_DONE_INR */
#घोषणा WM8962_DCS_STARTUP_DONE_INR_MASK        0x0200  /* DCS_STARTUP_DONE_INR */
#घोषणा WM8962_DCS_STARTUP_DONE_INR_SHIFT            9  /* DCS_STARTUP_DONE_INR */
#घोषणा WM8962_DCS_STARTUP_DONE_INR_WIDTH            1  /* DCS_STARTUP_DONE_INR */
#घोषणा WM8962_DCS_STARTUP_DONE_HP1L            0x0100  /* DCS_STARTUP_DONE_HP1L */
#घोषणा WM8962_DCS_STARTUP_DONE_HP1L_MASK       0x0100  /* DCS_STARTUP_DONE_HP1L */
#घोषणा WM8962_DCS_STARTUP_DONE_HP1L_SHIFT           8  /* DCS_STARTUP_DONE_HP1L */
#घोषणा WM8962_DCS_STARTUP_DONE_HP1L_WIDTH           1  /* DCS_STARTUP_DONE_HP1L */
#घोषणा WM8962_DCS_STARTUP_DONE_HP1R            0x0080  /* DCS_STARTUP_DONE_HP1R */
#घोषणा WM8962_DCS_STARTUP_DONE_HP1R_MASK       0x0080  /* DCS_STARTUP_DONE_HP1R */
#घोषणा WM8962_DCS_STARTUP_DONE_HP1R_SHIFT           7  /* DCS_STARTUP_DONE_HP1R */
#घोषणा WM8962_DCS_STARTUP_DONE_HP1R_WIDTH           1  /* DCS_STARTUP_DONE_HP1R */

/*
 * R68 (0x44) - Analogue PGA Bias
 */
#घोषणा WM8962_HP_PGAS_BIAS_MASK                0x0007  /* HP_PGAS_BIAS - [2:0] */
#घोषणा WM8962_HP_PGAS_BIAS_SHIFT                    0  /* HP_PGAS_BIAS - [2:0] */
#घोषणा WM8962_HP_PGAS_BIAS_WIDTH                    3  /* HP_PGAS_BIAS - [2:0] */

/*
 * R69 (0x45) - Analogue HP 0
 */
#घोषणा WM8962_HP1L_RMV_SHORT                   0x0080  /* HP1L_RMV_SHORT */
#घोषणा WM8962_HP1L_RMV_SHORT_MASK              0x0080  /* HP1L_RMV_SHORT */
#घोषणा WM8962_HP1L_RMV_SHORT_SHIFT                  7  /* HP1L_RMV_SHORT */
#घोषणा WM8962_HP1L_RMV_SHORT_WIDTH                  1  /* HP1L_RMV_SHORT */
#घोषणा WM8962_HP1L_ENA_OUTP                    0x0040  /* HP1L_ENA_OUTP */
#घोषणा WM8962_HP1L_ENA_OUTP_MASK               0x0040  /* HP1L_ENA_OUTP */
#घोषणा WM8962_HP1L_ENA_OUTP_SHIFT                   6  /* HP1L_ENA_OUTP */
#घोषणा WM8962_HP1L_ENA_OUTP_WIDTH                   1  /* HP1L_ENA_OUTP */
#घोषणा WM8962_HP1L_ENA_DLY                     0x0020  /* HP1L_ENA_DLY */
#घोषणा WM8962_HP1L_ENA_DLY_MASK                0x0020  /* HP1L_ENA_DLY */
#घोषणा WM8962_HP1L_ENA_DLY_SHIFT                    5  /* HP1L_ENA_DLY */
#घोषणा WM8962_HP1L_ENA_DLY_WIDTH                    1  /* HP1L_ENA_DLY */
#घोषणा WM8962_HP1L_ENA                         0x0010  /* HP1L_ENA */
#घोषणा WM8962_HP1L_ENA_MASK                    0x0010  /* HP1L_ENA */
#घोषणा WM8962_HP1L_ENA_SHIFT                        4  /* HP1L_ENA */
#घोषणा WM8962_HP1L_ENA_WIDTH                        1  /* HP1L_ENA */
#घोषणा WM8962_HP1R_RMV_SHORT                   0x0008  /* HP1R_RMV_SHORT */
#घोषणा WM8962_HP1R_RMV_SHORT_MASK              0x0008  /* HP1R_RMV_SHORT */
#घोषणा WM8962_HP1R_RMV_SHORT_SHIFT                  3  /* HP1R_RMV_SHORT */
#घोषणा WM8962_HP1R_RMV_SHORT_WIDTH                  1  /* HP1R_RMV_SHORT */
#घोषणा WM8962_HP1R_ENA_OUTP                    0x0004  /* HP1R_ENA_OUTP */
#घोषणा WM8962_HP1R_ENA_OUTP_MASK               0x0004  /* HP1R_ENA_OUTP */
#घोषणा WM8962_HP1R_ENA_OUTP_SHIFT                   2  /* HP1R_ENA_OUTP */
#घोषणा WM8962_HP1R_ENA_OUTP_WIDTH                   1  /* HP1R_ENA_OUTP */
#घोषणा WM8962_HP1R_ENA_DLY                     0x0002  /* HP1R_ENA_DLY */
#घोषणा WM8962_HP1R_ENA_DLY_MASK                0x0002  /* HP1R_ENA_DLY */
#घोषणा WM8962_HP1R_ENA_DLY_SHIFT                    1  /* HP1R_ENA_DLY */
#घोषणा WM8962_HP1R_ENA_DLY_WIDTH                    1  /* HP1R_ENA_DLY */
#घोषणा WM8962_HP1R_ENA                         0x0001  /* HP1R_ENA */
#घोषणा WM8962_HP1R_ENA_MASK                    0x0001  /* HP1R_ENA */
#घोषणा WM8962_HP1R_ENA_SHIFT                        0  /* HP1R_ENA */
#घोषणा WM8962_HP1R_ENA_WIDTH                        1  /* HP1R_ENA */

/*
 * R71 (0x47) - Analogue HP 2
 */
#घोषणा WM8962_HP1L_VOL_MASK                    0x01C0  /* HP1L_VOL - [8:6] */
#घोषणा WM8962_HP1L_VOL_SHIFT                        6  /* HP1L_VOL - [8:6] */
#घोषणा WM8962_HP1L_VOL_WIDTH                        3  /* HP1L_VOL - [8:6] */
#घोषणा WM8962_HP1R_VOL_MASK                    0x0038  /* HP1R_VOL - [5:3] */
#घोषणा WM8962_HP1R_VOL_SHIFT                        3  /* HP1R_VOL - [5:3] */
#घोषणा WM8962_HP1R_VOL_WIDTH                        3  /* HP1R_VOL - [5:3] */
#घोषणा WM8962_HP_BIAS_BOOST_MASK               0x0007  /* HP_BIAS_BOOST - [2:0] */
#घोषणा WM8962_HP_BIAS_BOOST_SHIFT                   0  /* HP_BIAS_BOOST - [2:0] */
#घोषणा WM8962_HP_BIAS_BOOST_WIDTH                   3  /* HP_BIAS_BOOST - [2:0] */

/*
 * R72 (0x48) - Charge Pump 1
 */
#घोषणा WM8962_CP_ENA                           0x0001  /* CP_ENA */
#घोषणा WM8962_CP_ENA_MASK                      0x0001  /* CP_ENA */
#घोषणा WM8962_CP_ENA_SHIFT                          0  /* CP_ENA */
#घोषणा WM8962_CP_ENA_WIDTH                          1  /* CP_ENA */

/*
 * R82 (0x52) - Charge Pump B
 */
#घोषणा WM8962_CP_DYN_PWR                       0x0001  /* CP_DYN_PWR */
#घोषणा WM8962_CP_DYN_PWR_MASK                  0x0001  /* CP_DYN_PWR */
#घोषणा WM8962_CP_DYN_PWR_SHIFT                      0  /* CP_DYN_PWR */
#घोषणा WM8962_CP_DYN_PWR_WIDTH                      1  /* CP_DYN_PWR */

/*
 * R87 (0x57) - Write Sequencer Control 1
 */
#घोषणा WM8962_WSEQ_AUTOSEQ_ENA                 0x0080  /* WSEQ_AUTOSEQ_ENA */
#घोषणा WM8962_WSEQ_AUTOSEQ_ENA_MASK            0x0080  /* WSEQ_AUTOSEQ_ENA */
#घोषणा WM8962_WSEQ_AUTOSEQ_ENA_SHIFT                7  /* WSEQ_AUTOSEQ_ENA */
#घोषणा WM8962_WSEQ_AUTOSEQ_ENA_WIDTH                1  /* WSEQ_AUTOSEQ_ENA */
#घोषणा WM8962_WSEQ_ENA                         0x0020  /* WSEQ_ENA */
#घोषणा WM8962_WSEQ_ENA_MASK                    0x0020  /* WSEQ_ENA */
#घोषणा WM8962_WSEQ_ENA_SHIFT                        5  /* WSEQ_ENA */
#घोषणा WM8962_WSEQ_ENA_WIDTH                        1  /* WSEQ_ENA */

/*
 * R90 (0x5A) - Write Sequencer Control 2
 */
#घोषणा WM8962_WSEQ_ABORT                       0x0100  /* WSEQ_ABORT */
#घोषणा WM8962_WSEQ_ABORT_MASK                  0x0100  /* WSEQ_ABORT */
#घोषणा WM8962_WSEQ_ABORT_SHIFT                      8  /* WSEQ_ABORT */
#घोषणा WM8962_WSEQ_ABORT_WIDTH                      1  /* WSEQ_ABORT */
#घोषणा WM8962_WSEQ_START                       0x0080  /* WSEQ_START */
#घोषणा WM8962_WSEQ_START_MASK                  0x0080  /* WSEQ_START */
#घोषणा WM8962_WSEQ_START_SHIFT                      7  /* WSEQ_START */
#घोषणा WM8962_WSEQ_START_WIDTH                      1  /* WSEQ_START */
#घोषणा WM8962_WSEQ_START_INDEX_MASK            0x007F  /* WSEQ_START_INDEX - [6:0] */
#घोषणा WM8962_WSEQ_START_INDEX_SHIFT                0  /* WSEQ_START_INDEX - [6:0] */
#घोषणा WM8962_WSEQ_START_INDEX_WIDTH                7  /* WSEQ_START_INDEX - [6:0] */

/*
 * R93 (0x5D) - Write Sequencer Control 3
 */
#घोषणा WM8962_WSEQ_CURRENT_INDEX_MASK          0x03F8  /* WSEQ_CURRENT_INDEX - [9:3] */
#घोषणा WM8962_WSEQ_CURRENT_INDEX_SHIFT              3  /* WSEQ_CURRENT_INDEX - [9:3] */
#घोषणा WM8962_WSEQ_CURRENT_INDEX_WIDTH              7  /* WSEQ_CURRENT_INDEX - [9:3] */
#घोषणा WM8962_WSEQ_BUSY                        0x0001  /* WSEQ_BUSY */
#घोषणा WM8962_WSEQ_BUSY_MASK                   0x0001  /* WSEQ_BUSY */
#घोषणा WM8962_WSEQ_BUSY_SHIFT                       0  /* WSEQ_BUSY */
#घोषणा WM8962_WSEQ_BUSY_WIDTH                       1  /* WSEQ_BUSY */

/*
 * R94 (0x5E) - Control Interface
 */
#घोषणा WM8962_SPI_CONTRD                       0x0040  /* SPI_CONTRD */
#घोषणा WM8962_SPI_CONTRD_MASK                  0x0040  /* SPI_CONTRD */
#घोषणा WM8962_SPI_CONTRD_SHIFT                      6  /* SPI_CONTRD */
#घोषणा WM8962_SPI_CONTRD_WIDTH                      1  /* SPI_CONTRD */
#घोषणा WM8962_SPI_4WIRE                        0x0020  /* SPI_4WIRE */
#घोषणा WM8962_SPI_4WIRE_MASK                   0x0020  /* SPI_4WIRE */
#घोषणा WM8962_SPI_4WIRE_SHIFT                       5  /* SPI_4WIRE */
#घोषणा WM8962_SPI_4WIRE_WIDTH                       1  /* SPI_4WIRE */
#घोषणा WM8962_SPI_CFG                          0x0010  /* SPI_CFG */
#घोषणा WM8962_SPI_CFG_MASK                     0x0010  /* SPI_CFG */
#घोषणा WM8962_SPI_CFG_SHIFT                         4  /* SPI_CFG */
#घोषणा WM8962_SPI_CFG_WIDTH                         1  /* SPI_CFG */

/*
 * R99 (0x63) - Mixer Enables
 */
#घोषणा WM8962_HPMIXL_ENA                       0x0008  /* HPMIXL_ENA */
#घोषणा WM8962_HPMIXL_ENA_MASK                  0x0008  /* HPMIXL_ENA */
#घोषणा WM8962_HPMIXL_ENA_SHIFT                      3  /* HPMIXL_ENA */
#घोषणा WM8962_HPMIXL_ENA_WIDTH                      1  /* HPMIXL_ENA */
#घोषणा WM8962_HPMIXR_ENA                       0x0004  /* HPMIXR_ENA */
#घोषणा WM8962_HPMIXR_ENA_MASK                  0x0004  /* HPMIXR_ENA */
#घोषणा WM8962_HPMIXR_ENA_SHIFT                      2  /* HPMIXR_ENA */
#घोषणा WM8962_HPMIXR_ENA_WIDTH                      1  /* HPMIXR_ENA */
#घोषणा WM8962_SPKMIXL_ENA                      0x0002  /* SPKMIXL_ENA */
#घोषणा WM8962_SPKMIXL_ENA_MASK                 0x0002  /* SPKMIXL_ENA */
#घोषणा WM8962_SPKMIXL_ENA_SHIFT                     1  /* SPKMIXL_ENA */
#घोषणा WM8962_SPKMIXL_ENA_WIDTH                     1  /* SPKMIXL_ENA */
#घोषणा WM8962_SPKMIXR_ENA                      0x0001  /* SPKMIXR_ENA */
#घोषणा WM8962_SPKMIXR_ENA_MASK                 0x0001  /* SPKMIXR_ENA */
#घोषणा WM8962_SPKMIXR_ENA_SHIFT                     0  /* SPKMIXR_ENA */
#घोषणा WM8962_SPKMIXR_ENA_WIDTH                     1  /* SPKMIXR_ENA */

/*
 * R100 (0x64) - Headphone Mixer (1)
 */
#घोषणा WM8962_HPMIXL_TO_HPOUTL_PGA             0x0080  /* HPMIXL_TO_HPOUTL_PGA */
#घोषणा WM8962_HPMIXL_TO_HPOUTL_PGA_MASK        0x0080  /* HPMIXL_TO_HPOUTL_PGA */
#घोषणा WM8962_HPMIXL_TO_HPOUTL_PGA_SHIFT            7  /* HPMIXL_TO_HPOUTL_PGA */
#घोषणा WM8962_HPMIXL_TO_HPOUTL_PGA_WIDTH            1  /* HPMIXL_TO_HPOUTL_PGA */
#घोषणा WM8962_DACL_TO_HPMIXL                   0x0020  /* DACL_TO_HPMIXL */
#घोषणा WM8962_DACL_TO_HPMIXL_MASK              0x0020  /* DACL_TO_HPMIXL */
#घोषणा WM8962_DACL_TO_HPMIXL_SHIFT                  5  /* DACL_TO_HPMIXL */
#घोषणा WM8962_DACL_TO_HPMIXL_WIDTH                  1  /* DACL_TO_HPMIXL */
#घोषणा WM8962_DACR_TO_HPMIXL                   0x0010  /* DACR_TO_HPMIXL */
#घोषणा WM8962_DACR_TO_HPMIXL_MASK              0x0010  /* DACR_TO_HPMIXL */
#घोषणा WM8962_DACR_TO_HPMIXL_SHIFT                  4  /* DACR_TO_HPMIXL */
#घोषणा WM8962_DACR_TO_HPMIXL_WIDTH                  1  /* DACR_TO_HPMIXL */
#घोषणा WM8962_MIXINL_TO_HPMIXL                 0x0008  /* MIXINL_TO_HPMIXL */
#घोषणा WM8962_MIXINL_TO_HPMIXL_MASK            0x0008  /* MIXINL_TO_HPMIXL */
#घोषणा WM8962_MIXINL_TO_HPMIXL_SHIFT                3  /* MIXINL_TO_HPMIXL */
#घोषणा WM8962_MIXINL_TO_HPMIXL_WIDTH                1  /* MIXINL_TO_HPMIXL */
#घोषणा WM8962_MIXINR_TO_HPMIXL                 0x0004  /* MIXINR_TO_HPMIXL */
#घोषणा WM8962_MIXINR_TO_HPMIXL_MASK            0x0004  /* MIXINR_TO_HPMIXL */
#घोषणा WM8962_MIXINR_TO_HPMIXL_SHIFT                2  /* MIXINR_TO_HPMIXL */
#घोषणा WM8962_MIXINR_TO_HPMIXL_WIDTH                1  /* MIXINR_TO_HPMIXL */
#घोषणा WM8962_IN4L_TO_HPMIXL                   0x0002  /* IN4L_TO_HPMIXL */
#घोषणा WM8962_IN4L_TO_HPMIXL_MASK              0x0002  /* IN4L_TO_HPMIXL */
#घोषणा WM8962_IN4L_TO_HPMIXL_SHIFT                  1  /* IN4L_TO_HPMIXL */
#घोषणा WM8962_IN4L_TO_HPMIXL_WIDTH                  1  /* IN4L_TO_HPMIXL */
#घोषणा WM8962_IN4R_TO_HPMIXL                   0x0001  /* IN4R_TO_HPMIXL */
#घोषणा WM8962_IN4R_TO_HPMIXL_MASK              0x0001  /* IN4R_TO_HPMIXL */
#घोषणा WM8962_IN4R_TO_HPMIXL_SHIFT                  0  /* IN4R_TO_HPMIXL */
#घोषणा WM8962_IN4R_TO_HPMIXL_WIDTH                  1  /* IN4R_TO_HPMIXL */

/*
 * R101 (0x65) - Headphone Mixer (2)
 */
#घोषणा WM8962_HPMIXR_TO_HPOUTR_PGA             0x0080  /* HPMIXR_TO_HPOUTR_PGA */
#घोषणा WM8962_HPMIXR_TO_HPOUTR_PGA_MASK        0x0080  /* HPMIXR_TO_HPOUTR_PGA */
#घोषणा WM8962_HPMIXR_TO_HPOUTR_PGA_SHIFT            7  /* HPMIXR_TO_HPOUTR_PGA */
#घोषणा WM8962_HPMIXR_TO_HPOUTR_PGA_WIDTH            1  /* HPMIXR_TO_HPOUTR_PGA */
#घोषणा WM8962_DACL_TO_HPMIXR                   0x0020  /* DACL_TO_HPMIXR */
#घोषणा WM8962_DACL_TO_HPMIXR_MASK              0x0020  /* DACL_TO_HPMIXR */
#घोषणा WM8962_DACL_TO_HPMIXR_SHIFT                  5  /* DACL_TO_HPMIXR */
#घोषणा WM8962_DACL_TO_HPMIXR_WIDTH                  1  /* DACL_TO_HPMIXR */
#घोषणा WM8962_DACR_TO_HPMIXR                   0x0010  /* DACR_TO_HPMIXR */
#घोषणा WM8962_DACR_TO_HPMIXR_MASK              0x0010  /* DACR_TO_HPMIXR */
#घोषणा WM8962_DACR_TO_HPMIXR_SHIFT                  4  /* DACR_TO_HPMIXR */
#घोषणा WM8962_DACR_TO_HPMIXR_WIDTH                  1  /* DACR_TO_HPMIXR */
#घोषणा WM8962_MIXINL_TO_HPMIXR                 0x0008  /* MIXINL_TO_HPMIXR */
#घोषणा WM8962_MIXINL_TO_HPMIXR_MASK            0x0008  /* MIXINL_TO_HPMIXR */
#घोषणा WM8962_MIXINL_TO_HPMIXR_SHIFT                3  /* MIXINL_TO_HPMIXR */
#घोषणा WM8962_MIXINL_TO_HPMIXR_WIDTH                1  /* MIXINL_TO_HPMIXR */
#घोषणा WM8962_MIXINR_TO_HPMIXR                 0x0004  /* MIXINR_TO_HPMIXR */
#घोषणा WM8962_MIXINR_TO_HPMIXR_MASK            0x0004  /* MIXINR_TO_HPMIXR */
#घोषणा WM8962_MIXINR_TO_HPMIXR_SHIFT                2  /* MIXINR_TO_HPMIXR */
#घोषणा WM8962_MIXINR_TO_HPMIXR_WIDTH                1  /* MIXINR_TO_HPMIXR */
#घोषणा WM8962_IN4L_TO_HPMIXR                   0x0002  /* IN4L_TO_HPMIXR */
#घोषणा WM8962_IN4L_TO_HPMIXR_MASK              0x0002  /* IN4L_TO_HPMIXR */
#घोषणा WM8962_IN4L_TO_HPMIXR_SHIFT                  1  /* IN4L_TO_HPMIXR */
#घोषणा WM8962_IN4L_TO_HPMIXR_WIDTH                  1  /* IN4L_TO_HPMIXR */
#घोषणा WM8962_IN4R_TO_HPMIXR                   0x0001  /* IN4R_TO_HPMIXR */
#घोषणा WM8962_IN4R_TO_HPMIXR_MASK              0x0001  /* IN4R_TO_HPMIXR */
#घोषणा WM8962_IN4R_TO_HPMIXR_SHIFT                  0  /* IN4R_TO_HPMIXR */
#घोषणा WM8962_IN4R_TO_HPMIXR_WIDTH                  1  /* IN4R_TO_HPMIXR */

/*
 * R102 (0x66) - Headphone Mixer (3)
 */
#घोषणा WM8962_HPMIXL_MUTE                      0x0100  /* HPMIXL_MUTE */
#घोषणा WM8962_HPMIXL_MUTE_MASK                 0x0100  /* HPMIXL_MUTE */
#घोषणा WM8962_HPMIXL_MUTE_SHIFT                     8  /* HPMIXL_MUTE */
#घोषणा WM8962_HPMIXL_MUTE_WIDTH                     1  /* HPMIXL_MUTE */
#घोषणा WM8962_MIXINL_HPMIXL_VOL                0x0080  /* MIXINL_HPMIXL_VOL */
#घोषणा WM8962_MIXINL_HPMIXL_VOL_MASK           0x0080  /* MIXINL_HPMIXL_VOL */
#घोषणा WM8962_MIXINL_HPMIXL_VOL_SHIFT               7  /* MIXINL_HPMIXL_VOL */
#घोषणा WM8962_MIXINL_HPMIXL_VOL_WIDTH               1  /* MIXINL_HPMIXL_VOL */
#घोषणा WM8962_MIXINR_HPMIXL_VOL                0x0040  /* MIXINR_HPMIXL_VOL */
#घोषणा WM8962_MIXINR_HPMIXL_VOL_MASK           0x0040  /* MIXINR_HPMIXL_VOL */
#घोषणा WM8962_MIXINR_HPMIXL_VOL_SHIFT               6  /* MIXINR_HPMIXL_VOL */
#घोषणा WM8962_MIXINR_HPMIXL_VOL_WIDTH               1  /* MIXINR_HPMIXL_VOL */
#घोषणा WM8962_IN4L_HPMIXL_VOL_MASK             0x0038  /* IN4L_HPMIXL_VOL - [5:3] */
#घोषणा WM8962_IN4L_HPMIXL_VOL_SHIFT                 3  /* IN4L_HPMIXL_VOL - [5:3] */
#घोषणा WM8962_IN4L_HPMIXL_VOL_WIDTH                 3  /* IN4L_HPMIXL_VOL - [5:3] */
#घोषणा WM8962_IN4R_HPMIXL_VOL_MASK             0x0007  /* IN4R_HPMIXL_VOL - [2:0] */
#घोषणा WM8962_IN4R_HPMIXL_VOL_SHIFT                 0  /* IN4R_HPMIXL_VOL - [2:0] */
#घोषणा WM8962_IN4R_HPMIXL_VOL_WIDTH                 3  /* IN4R_HPMIXL_VOL - [2:0] */

/*
 * R103 (0x67) - Headphone Mixer (4)
 */
#घोषणा WM8962_HPMIXR_MUTE                      0x0100  /* HPMIXR_MUTE */
#घोषणा WM8962_HPMIXR_MUTE_MASK                 0x0100  /* HPMIXR_MUTE */
#घोषणा WM8962_HPMIXR_MUTE_SHIFT                     8  /* HPMIXR_MUTE */
#घोषणा WM8962_HPMIXR_MUTE_WIDTH                     1  /* HPMIXR_MUTE */
#घोषणा WM8962_MIXINL_HPMIXR_VOL                0x0080  /* MIXINL_HPMIXR_VOL */
#घोषणा WM8962_MIXINL_HPMIXR_VOL_MASK           0x0080  /* MIXINL_HPMIXR_VOL */
#घोषणा WM8962_MIXINL_HPMIXR_VOL_SHIFT               7  /* MIXINL_HPMIXR_VOL */
#घोषणा WM8962_MIXINL_HPMIXR_VOL_WIDTH               1  /* MIXINL_HPMIXR_VOL */
#घोषणा WM8962_MIXINR_HPMIXR_VOL                0x0040  /* MIXINR_HPMIXR_VOL */
#घोषणा WM8962_MIXINR_HPMIXR_VOL_MASK           0x0040  /* MIXINR_HPMIXR_VOL */
#घोषणा WM8962_MIXINR_HPMIXR_VOL_SHIFT               6  /* MIXINR_HPMIXR_VOL */
#घोषणा WM8962_MIXINR_HPMIXR_VOL_WIDTH               1  /* MIXINR_HPMIXR_VOL */
#घोषणा WM8962_IN4L_HPMIXR_VOL_MASK             0x0038  /* IN4L_HPMIXR_VOL - [5:3] */
#घोषणा WM8962_IN4L_HPMIXR_VOL_SHIFT                 3  /* IN4L_HPMIXR_VOL - [5:3] */
#घोषणा WM8962_IN4L_HPMIXR_VOL_WIDTH                 3  /* IN4L_HPMIXR_VOL - [5:3] */
#घोषणा WM8962_IN4R_HPMIXR_VOL_MASK             0x0007  /* IN4R_HPMIXR_VOL - [2:0] */
#घोषणा WM8962_IN4R_HPMIXR_VOL_SHIFT                 0  /* IN4R_HPMIXR_VOL - [2:0] */
#घोषणा WM8962_IN4R_HPMIXR_VOL_WIDTH                 3  /* IN4R_HPMIXR_VOL - [2:0] */

/*
 * R105 (0x69) - Speaker Mixer (1)
 */
#घोषणा WM8962_SPKMIXL_TO_SPKOUTL_PGA           0x0080  /* SPKMIXL_TO_SPKOUTL_PGA */
#घोषणा WM8962_SPKMIXL_TO_SPKOUTL_PGA_MASK      0x0080  /* SPKMIXL_TO_SPKOUTL_PGA */
#घोषणा WM8962_SPKMIXL_TO_SPKOUTL_PGA_SHIFT          7  /* SPKMIXL_TO_SPKOUTL_PGA */
#घोषणा WM8962_SPKMIXL_TO_SPKOUTL_PGA_WIDTH          1  /* SPKMIXL_TO_SPKOUTL_PGA */
#घोषणा WM8962_DACL_TO_SPKMIXL                  0x0020  /* DACL_TO_SPKMIXL */
#घोषणा WM8962_DACL_TO_SPKMIXL_MASK             0x0020  /* DACL_TO_SPKMIXL */
#घोषणा WM8962_DACL_TO_SPKMIXL_SHIFT                 5  /* DACL_TO_SPKMIXL */
#घोषणा WM8962_DACL_TO_SPKMIXL_WIDTH                 1  /* DACL_TO_SPKMIXL */
#घोषणा WM8962_DACR_TO_SPKMIXL                  0x0010  /* DACR_TO_SPKMIXL */
#घोषणा WM8962_DACR_TO_SPKMIXL_MASK             0x0010  /* DACR_TO_SPKMIXL */
#घोषणा WM8962_DACR_TO_SPKMIXL_SHIFT                 4  /* DACR_TO_SPKMIXL */
#घोषणा WM8962_DACR_TO_SPKMIXL_WIDTH                 1  /* DACR_TO_SPKMIXL */
#घोषणा WM8962_MIXINL_TO_SPKMIXL                0x0008  /* MIXINL_TO_SPKMIXL */
#घोषणा WM8962_MIXINL_TO_SPKMIXL_MASK           0x0008  /* MIXINL_TO_SPKMIXL */
#घोषणा WM8962_MIXINL_TO_SPKMIXL_SHIFT               3  /* MIXINL_TO_SPKMIXL */
#घोषणा WM8962_MIXINL_TO_SPKMIXL_WIDTH               1  /* MIXINL_TO_SPKMIXL */
#घोषणा WM8962_MIXINR_TO_SPKMIXL                0x0004  /* MIXINR_TO_SPKMIXL */
#घोषणा WM8962_MIXINR_TO_SPKMIXL_MASK           0x0004  /* MIXINR_TO_SPKMIXL */
#घोषणा WM8962_MIXINR_TO_SPKMIXL_SHIFT               2  /* MIXINR_TO_SPKMIXL */
#घोषणा WM8962_MIXINR_TO_SPKMIXL_WIDTH               1  /* MIXINR_TO_SPKMIXL */
#घोषणा WM8962_IN4L_TO_SPKMIXL                  0x0002  /* IN4L_TO_SPKMIXL */
#घोषणा WM8962_IN4L_TO_SPKMIXL_MASK             0x0002  /* IN4L_TO_SPKMIXL */
#घोषणा WM8962_IN4L_TO_SPKMIXL_SHIFT                 1  /* IN4L_TO_SPKMIXL */
#घोषणा WM8962_IN4L_TO_SPKMIXL_WIDTH                 1  /* IN4L_TO_SPKMIXL */
#घोषणा WM8962_IN4R_TO_SPKMIXL                  0x0001  /* IN4R_TO_SPKMIXL */
#घोषणा WM8962_IN4R_TO_SPKMIXL_MASK             0x0001  /* IN4R_TO_SPKMIXL */
#घोषणा WM8962_IN4R_TO_SPKMIXL_SHIFT                 0  /* IN4R_TO_SPKMIXL */
#घोषणा WM8962_IN4R_TO_SPKMIXL_WIDTH                 1  /* IN4R_TO_SPKMIXL */

/*
 * R106 (0x6A) - Speaker Mixer (2)
 */
#घोषणा WM8962_SPKMIXR_TO_SPKOUTR_PGA           0x0080  /* SPKMIXR_TO_SPKOUTR_PGA */
#घोषणा WM8962_SPKMIXR_TO_SPKOUTR_PGA_MASK      0x0080  /* SPKMIXR_TO_SPKOUTR_PGA */
#घोषणा WM8962_SPKMIXR_TO_SPKOUTR_PGA_SHIFT          7  /* SPKMIXR_TO_SPKOUTR_PGA */
#घोषणा WM8962_SPKMIXR_TO_SPKOUTR_PGA_WIDTH          1  /* SPKMIXR_TO_SPKOUTR_PGA */
#घोषणा WM8962_DACL_TO_SPKMIXR                  0x0020  /* DACL_TO_SPKMIXR */
#घोषणा WM8962_DACL_TO_SPKMIXR_MASK             0x0020  /* DACL_TO_SPKMIXR */
#घोषणा WM8962_DACL_TO_SPKMIXR_SHIFT                 5  /* DACL_TO_SPKMIXR */
#घोषणा WM8962_DACL_TO_SPKMIXR_WIDTH                 1  /* DACL_TO_SPKMIXR */
#घोषणा WM8962_DACR_TO_SPKMIXR                  0x0010  /* DACR_TO_SPKMIXR */
#घोषणा WM8962_DACR_TO_SPKMIXR_MASK             0x0010  /* DACR_TO_SPKMIXR */
#घोषणा WM8962_DACR_TO_SPKMIXR_SHIFT                 4  /* DACR_TO_SPKMIXR */
#घोषणा WM8962_DACR_TO_SPKMIXR_WIDTH                 1  /* DACR_TO_SPKMIXR */
#घोषणा WM8962_MIXINL_TO_SPKMIXR                0x0008  /* MIXINL_TO_SPKMIXR */
#घोषणा WM8962_MIXINL_TO_SPKMIXR_MASK           0x0008  /* MIXINL_TO_SPKMIXR */
#घोषणा WM8962_MIXINL_TO_SPKMIXR_SHIFT               3  /* MIXINL_TO_SPKMIXR */
#घोषणा WM8962_MIXINL_TO_SPKMIXR_WIDTH               1  /* MIXINL_TO_SPKMIXR */
#घोषणा WM8962_MIXINR_TO_SPKMIXR                0x0004  /* MIXINR_TO_SPKMIXR */
#घोषणा WM8962_MIXINR_TO_SPKMIXR_MASK           0x0004  /* MIXINR_TO_SPKMIXR */
#घोषणा WM8962_MIXINR_TO_SPKMIXR_SHIFT               2  /* MIXINR_TO_SPKMIXR */
#घोषणा WM8962_MIXINR_TO_SPKMIXR_WIDTH               1  /* MIXINR_TO_SPKMIXR */
#घोषणा WM8962_IN4L_TO_SPKMIXR                  0x0002  /* IN4L_TO_SPKMIXR */
#घोषणा WM8962_IN4L_TO_SPKMIXR_MASK             0x0002  /* IN4L_TO_SPKMIXR */
#घोषणा WM8962_IN4L_TO_SPKMIXR_SHIFT                 1  /* IN4L_TO_SPKMIXR */
#घोषणा WM8962_IN4L_TO_SPKMIXR_WIDTH                 1  /* IN4L_TO_SPKMIXR */
#घोषणा WM8962_IN4R_TO_SPKMIXR                  0x0001  /* IN4R_TO_SPKMIXR */
#घोषणा WM8962_IN4R_TO_SPKMIXR_MASK             0x0001  /* IN4R_TO_SPKMIXR */
#घोषणा WM8962_IN4R_TO_SPKMIXR_SHIFT                 0  /* IN4R_TO_SPKMIXR */
#घोषणा WM8962_IN4R_TO_SPKMIXR_WIDTH                 1  /* IN4R_TO_SPKMIXR */

/*
 * R107 (0x6B) - Speaker Mixer (3)
 */
#घोषणा WM8962_SPKMIXL_MUTE                     0x0100  /* SPKMIXL_MUTE */
#घोषणा WM8962_SPKMIXL_MUTE_MASK                0x0100  /* SPKMIXL_MUTE */
#घोषणा WM8962_SPKMIXL_MUTE_SHIFT                    8  /* SPKMIXL_MUTE */
#घोषणा WM8962_SPKMIXL_MUTE_WIDTH                    1  /* SPKMIXL_MUTE */
#घोषणा WM8962_MIXINL_SPKMIXL_VOL               0x0080  /* MIXINL_SPKMIXL_VOL */
#घोषणा WM8962_MIXINL_SPKMIXL_VOL_MASK          0x0080  /* MIXINL_SPKMIXL_VOL */
#घोषणा WM8962_MIXINL_SPKMIXL_VOL_SHIFT              7  /* MIXINL_SPKMIXL_VOL */
#घोषणा WM8962_MIXINL_SPKMIXL_VOL_WIDTH              1  /* MIXINL_SPKMIXL_VOL */
#घोषणा WM8962_MIXINR_SPKMIXL_VOL               0x0040  /* MIXINR_SPKMIXL_VOL */
#घोषणा WM8962_MIXINR_SPKMIXL_VOL_MASK          0x0040  /* MIXINR_SPKMIXL_VOL */
#घोषणा WM8962_MIXINR_SPKMIXL_VOL_SHIFT              6  /* MIXINR_SPKMIXL_VOL */
#घोषणा WM8962_MIXINR_SPKMIXL_VOL_WIDTH              1  /* MIXINR_SPKMIXL_VOL */
#घोषणा WM8962_IN4L_SPKMIXL_VOL_MASK            0x0038  /* IN4L_SPKMIXL_VOL - [5:3] */
#घोषणा WM8962_IN4L_SPKMIXL_VOL_SHIFT                3  /* IN4L_SPKMIXL_VOL - [5:3] */
#घोषणा WM8962_IN4L_SPKMIXL_VOL_WIDTH                3  /* IN4L_SPKMIXL_VOL - [5:3] */
#घोषणा WM8962_IN4R_SPKMIXL_VOL_MASK            0x0007  /* IN4R_SPKMIXL_VOL - [2:0] */
#घोषणा WM8962_IN4R_SPKMIXL_VOL_SHIFT                0  /* IN4R_SPKMIXL_VOL - [2:0] */
#घोषणा WM8962_IN4R_SPKMIXL_VOL_WIDTH                3  /* IN4R_SPKMIXL_VOL - [2:0] */

/*
 * R108 (0x6C) - Speaker Mixer (4)
 */
#घोषणा WM8962_SPKMIXR_MUTE                     0x0100  /* SPKMIXR_MUTE */
#घोषणा WM8962_SPKMIXR_MUTE_MASK                0x0100  /* SPKMIXR_MUTE */
#घोषणा WM8962_SPKMIXR_MUTE_SHIFT                    8  /* SPKMIXR_MUTE */
#घोषणा WM8962_SPKMIXR_MUTE_WIDTH                    1  /* SPKMIXR_MUTE */
#घोषणा WM8962_MIXINL_SPKMIXR_VOL               0x0080  /* MIXINL_SPKMIXR_VOL */
#घोषणा WM8962_MIXINL_SPKMIXR_VOL_MASK          0x0080  /* MIXINL_SPKMIXR_VOL */
#घोषणा WM8962_MIXINL_SPKMIXR_VOL_SHIFT              7  /* MIXINL_SPKMIXR_VOL */
#घोषणा WM8962_MIXINL_SPKMIXR_VOL_WIDTH              1  /* MIXINL_SPKMIXR_VOL */
#घोषणा WM8962_MIXINR_SPKMIXR_VOL               0x0040  /* MIXINR_SPKMIXR_VOL */
#घोषणा WM8962_MIXINR_SPKMIXR_VOL_MASK          0x0040  /* MIXINR_SPKMIXR_VOL */
#घोषणा WM8962_MIXINR_SPKMIXR_VOL_SHIFT              6  /* MIXINR_SPKMIXR_VOL */
#घोषणा WM8962_MIXINR_SPKMIXR_VOL_WIDTH              1  /* MIXINR_SPKMIXR_VOL */
#घोषणा WM8962_IN4L_SPKMIXR_VOL_MASK            0x0038  /* IN4L_SPKMIXR_VOL - [5:3] */
#घोषणा WM8962_IN4L_SPKMIXR_VOL_SHIFT                3  /* IN4L_SPKMIXR_VOL - [5:3] */
#घोषणा WM8962_IN4L_SPKMIXR_VOL_WIDTH                3  /* IN4L_SPKMIXR_VOL - [5:3] */
#घोषणा WM8962_IN4R_SPKMIXR_VOL_MASK            0x0007  /* IN4R_SPKMIXR_VOL - [2:0] */
#घोषणा WM8962_IN4R_SPKMIXR_VOL_SHIFT                0  /* IN4R_SPKMIXR_VOL - [2:0] */
#घोषणा WM8962_IN4R_SPKMIXR_VOL_WIDTH                3  /* IN4R_SPKMIXR_VOL - [2:0] */

/*
 * R109 (0x6D) - Speaker Mixer (5)
 */
#घोषणा WM8962_DACL_SPKMIXL_VOL                 0x0080  /* DACL_SPKMIXL_VOL */
#घोषणा WM8962_DACL_SPKMIXL_VOL_MASK            0x0080  /* DACL_SPKMIXL_VOL */
#घोषणा WM8962_DACL_SPKMIXL_VOL_SHIFT                7  /* DACL_SPKMIXL_VOL */
#घोषणा WM8962_DACL_SPKMIXL_VOL_WIDTH                1  /* DACL_SPKMIXL_VOL */
#घोषणा WM8962_DACR_SPKMIXL_VOL                 0x0040  /* DACR_SPKMIXL_VOL */
#घोषणा WM8962_DACR_SPKMIXL_VOL_MASK            0x0040  /* DACR_SPKMIXL_VOL */
#घोषणा WM8962_DACR_SPKMIXL_VOL_SHIFT                6  /* DACR_SPKMIXL_VOL */
#घोषणा WM8962_DACR_SPKMIXL_VOL_WIDTH                1  /* DACR_SPKMIXL_VOL */
#घोषणा WM8962_DACL_SPKMIXR_VOL                 0x0020  /* DACL_SPKMIXR_VOL */
#घोषणा WM8962_DACL_SPKMIXR_VOL_MASK            0x0020  /* DACL_SPKMIXR_VOL */
#घोषणा WM8962_DACL_SPKMIXR_VOL_SHIFT                5  /* DACL_SPKMIXR_VOL */
#घोषणा WM8962_DACL_SPKMIXR_VOL_WIDTH                1  /* DACL_SPKMIXR_VOL */
#घोषणा WM8962_DACR_SPKMIXR_VOL                 0x0010  /* DACR_SPKMIXR_VOL */
#घोषणा WM8962_DACR_SPKMIXR_VOL_MASK            0x0010  /* DACR_SPKMIXR_VOL */
#घोषणा WM8962_DACR_SPKMIXR_VOL_SHIFT                4  /* DACR_SPKMIXR_VOL */
#घोषणा WM8962_DACR_SPKMIXR_VOL_WIDTH                1  /* DACR_SPKMIXR_VOL */

/*
 * R110 (0x6E) - Beep Generator (1)
 */
#घोषणा WM8962_BEEP_GAIN_MASK                   0x00F0  /* BEEP_GAIN - [7:4] */
#घोषणा WM8962_BEEP_GAIN_SHIFT                       4  /* BEEP_GAIN - [7:4] */
#घोषणा WM8962_BEEP_GAIN_WIDTH                       4  /* BEEP_GAIN - [7:4] */
#घोषणा WM8962_BEEP_RATE_MASK                   0x0006  /* BEEP_RATE - [2:1] */
#घोषणा WM8962_BEEP_RATE_SHIFT                       1  /* BEEP_RATE - [2:1] */
#घोषणा WM8962_BEEP_RATE_WIDTH                       2  /* BEEP_RATE - [2:1] */
#घोषणा WM8962_BEEP_ENA                         0x0001  /* BEEP_ENA */
#घोषणा WM8962_BEEP_ENA_MASK                    0x0001  /* BEEP_ENA */
#घोषणा WM8962_BEEP_ENA_SHIFT                        0  /* BEEP_ENA */
#घोषणा WM8962_BEEP_ENA_WIDTH                        1  /* BEEP_ENA */

/*
 * R115 (0x73) - Oscillator Trim (3)
 */
#घोषणा WM8962_OSC_TRIM_XTI_MASK                0x001F  /* OSC_TRIM_XTI - [4:0] */
#घोषणा WM8962_OSC_TRIM_XTI_SHIFT                    0  /* OSC_TRIM_XTI - [4:0] */
#घोषणा WM8962_OSC_TRIM_XTI_WIDTH                    5  /* OSC_TRIM_XTI - [4:0] */

/*
 * R116 (0x74) - Oscillator Trim (4)
 */
#घोषणा WM8962_OSC_TRIM_XTO_MASK                0x001F  /* OSC_TRIM_XTO - [4:0] */
#घोषणा WM8962_OSC_TRIM_XTO_SHIFT                    0  /* OSC_TRIM_XTO - [4:0] */
#घोषणा WM8962_OSC_TRIM_XTO_WIDTH                    5  /* OSC_TRIM_XTO - [4:0] */

/*
 * R119 (0x77) - Oscillator Trim (7)
 */
#घोषणा WM8962_XTO_CAP_SEL_MASK                 0x00F0  /* XTO_CAP_SEL - [7:4] */
#घोषणा WM8962_XTO_CAP_SEL_SHIFT                     4  /* XTO_CAP_SEL - [7:4] */
#घोषणा WM8962_XTO_CAP_SEL_WIDTH                     4  /* XTO_CAP_SEL - [7:4] */
#घोषणा WM8962_XTI_CAP_SEL_MASK                 0x000F  /* XTI_CAP_SEL - [3:0] */
#घोषणा WM8962_XTI_CAP_SEL_SHIFT                     0  /* XTI_CAP_SEL - [3:0] */
#घोषणा WM8962_XTI_CAP_SEL_WIDTH                     4  /* XTI_CAP_SEL - [3:0] */

/*
 * R124 (0x7C) - Analogue Clocking1
 */
#घोषणा WM8962_CLKOUT2_SEL_MASK                 0x0060  /* CLKOUT2_SEL - [6:5] */
#घोषणा WM8962_CLKOUT2_SEL_SHIFT                     5  /* CLKOUT2_SEL - [6:5] */
#घोषणा WM8962_CLKOUT2_SEL_WIDTH                     2  /* CLKOUT2_SEL - [6:5] */
#घोषणा WM8962_CLKOUT3_SEL_MASK                 0x0018  /* CLKOUT3_SEL - [4:3] */
#घोषणा WM8962_CLKOUT3_SEL_SHIFT                     3  /* CLKOUT3_SEL - [4:3] */
#घोषणा WM8962_CLKOUT3_SEL_WIDTH                     2  /* CLKOUT3_SEL - [4:3] */
#घोषणा WM8962_CLKOUT5_SEL                      0x0001  /* CLKOUT5_SEL */
#घोषणा WM8962_CLKOUT5_SEL_MASK                 0x0001  /* CLKOUT5_SEL */
#घोषणा WM8962_CLKOUT5_SEL_SHIFT                     0  /* CLKOUT5_SEL */
#घोषणा WM8962_CLKOUT5_SEL_WIDTH                     1  /* CLKOUT5_SEL */

/*
 * R125 (0x7D) - Analogue Clocking2
 */
#घोषणा WM8962_PLL2_OUTDIV                      0x0080  /* PLL2_OUTDIV */
#घोषणा WM8962_PLL2_OUTDIV_MASK                 0x0080  /* PLL2_OUTDIV */
#घोषणा WM8962_PLL2_OUTDIV_SHIFT                     7  /* PLL2_OUTDIV */
#घोषणा WM8962_PLL2_OUTDIV_WIDTH                     1  /* PLL2_OUTDIV */
#घोषणा WM8962_PLL3_OUTDIV                      0x0040  /* PLL3_OUTDIV */
#घोषणा WM8962_PLL3_OUTDIV_MASK                 0x0040  /* PLL3_OUTDIV */
#घोषणा WM8962_PLL3_OUTDIV_SHIFT                     6  /* PLL3_OUTDIV */
#घोषणा WM8962_PLL3_OUTDIV_WIDTH                     1  /* PLL3_OUTDIV */
#घोषणा WM8962_PLL_SYSCLK_DIV_MASK              0x0018  /* PLL_SYSCLK_DIV - [4:3] */
#घोषणा WM8962_PLL_SYSCLK_DIV_SHIFT                  3  /* PLL_SYSCLK_DIV - [4:3] */
#घोषणा WM8962_PLL_SYSCLK_DIV_WIDTH                  2  /* PLL_SYSCLK_DIV - [4:3] */
#घोषणा WM8962_CLKOUT3_DIV                      0x0004  /* CLKOUT3_DIV */
#घोषणा WM8962_CLKOUT3_DIV_MASK                 0x0004  /* CLKOUT3_DIV */
#घोषणा WM8962_CLKOUT3_DIV_SHIFT                     2  /* CLKOUT3_DIV */
#घोषणा WM8962_CLKOUT3_DIV_WIDTH                     1  /* CLKOUT3_DIV */
#घोषणा WM8962_CLKOUT2_DIV                      0x0002  /* CLKOUT2_DIV */
#घोषणा WM8962_CLKOUT2_DIV_MASK                 0x0002  /* CLKOUT2_DIV */
#घोषणा WM8962_CLKOUT2_DIV_SHIFT                     1  /* CLKOUT2_DIV */
#घोषणा WM8962_CLKOUT2_DIV_WIDTH                     1  /* CLKOUT2_DIV */
#घोषणा WM8962_CLKOUT5_DIV                      0x0001  /* CLKOUT5_DIV */
#घोषणा WM8962_CLKOUT5_DIV_MASK                 0x0001  /* CLKOUT5_DIV */
#घोषणा WM8962_CLKOUT5_DIV_SHIFT                     0  /* CLKOUT5_DIV */
#घोषणा WM8962_CLKOUT5_DIV_WIDTH                     1  /* CLKOUT5_DIV */

/*
 * R126 (0x7E) - Analogue Clocking3
 */
#घोषणा WM8962_CLKOUT2_OE                       0x0008  /* CLKOUT2_OE */
#घोषणा WM8962_CLKOUT2_OE_MASK                  0x0008  /* CLKOUT2_OE */
#घोषणा WM8962_CLKOUT2_OE_SHIFT                      3  /* CLKOUT2_OE */
#घोषणा WM8962_CLKOUT2_OE_WIDTH                      1  /* CLKOUT2_OE */
#घोषणा WM8962_CLKOUT3_OE                       0x0004  /* CLKOUT3_OE */
#घोषणा WM8962_CLKOUT3_OE_MASK                  0x0004  /* CLKOUT3_OE */
#घोषणा WM8962_CLKOUT3_OE_SHIFT                      2  /* CLKOUT3_OE */
#घोषणा WM8962_CLKOUT3_OE_WIDTH                      1  /* CLKOUT3_OE */
#घोषणा WM8962_CLKOUT5_OE                       0x0001  /* CLKOUT5_OE */
#घोषणा WM8962_CLKOUT5_OE_MASK                  0x0001  /* CLKOUT5_OE */
#घोषणा WM8962_CLKOUT5_OE_SHIFT                      0  /* CLKOUT5_OE */
#घोषणा WM8962_CLKOUT5_OE_WIDTH                      1  /* CLKOUT5_OE */

/*
 * R127 (0x7F) - PLL Software Reset
 */
#घोषणा WM8962_SW_RESET_PLL_MASK                0xFFFF  /* SW_RESET_PLL - [15:0] */
#घोषणा WM8962_SW_RESET_PLL_SHIFT                    0  /* SW_RESET_PLL - [15:0] */
#घोषणा WM8962_SW_RESET_PLL_WIDTH                   16  /* SW_RESET_PLL - [15:0] */

/*
 * R129 (0x81) - PLL2
 */
#घोषणा WM8962_OSC_ENA                          0x0080  /* OSC_ENA */
#घोषणा WM8962_OSC_ENA_MASK                     0x0080  /* OSC_ENA */
#घोषणा WM8962_OSC_ENA_SHIFT                         7  /* OSC_ENA */
#घोषणा WM8962_OSC_ENA_WIDTH                         1  /* OSC_ENA */
#घोषणा WM8962_PLL2_ENA                         0x0020  /* PLL2_ENA */
#घोषणा WM8962_PLL2_ENA_MASK                    0x0020  /* PLL2_ENA */
#घोषणा WM8962_PLL2_ENA_SHIFT                        5  /* PLL2_ENA */
#घोषणा WM8962_PLL2_ENA_WIDTH                        1  /* PLL2_ENA */
#घोषणा WM8962_PLL3_ENA                         0x0010  /* PLL3_ENA */
#घोषणा WM8962_PLL3_ENA_MASK                    0x0010  /* PLL3_ENA */
#घोषणा WM8962_PLL3_ENA_SHIFT                        4  /* PLL3_ENA */
#घोषणा WM8962_PLL3_ENA_WIDTH                        1  /* PLL3_ENA */

/*
 * R131 (0x83) - PLL 4
 */
#घोषणा WM8962_PLL_CLK_SRC                      0x0002  /* PLL_CLK_SRC */
#घोषणा WM8962_PLL_CLK_SRC_MASK                 0x0002  /* PLL_CLK_SRC */
#घोषणा WM8962_PLL_CLK_SRC_SHIFT                     1  /* PLL_CLK_SRC */
#घोषणा WM8962_PLL_CLK_SRC_WIDTH                     1  /* PLL_CLK_SRC */
#घोषणा WM8962_FLL_TO_PLL3                      0x0001  /* FLL_TO_PLL3 */
#घोषणा WM8962_FLL_TO_PLL3_MASK                 0x0001  /* FLL_TO_PLL3 */
#घोषणा WM8962_FLL_TO_PLL3_SHIFT                     0  /* FLL_TO_PLL3 */
#घोषणा WM8962_FLL_TO_PLL3_WIDTH                     1  /* FLL_TO_PLL3 */

/*
 * R136 (0x88) - PLL 9
 */
#घोषणा WM8962_PLL2_FRAC                        0x0040  /* PLL2_FRAC */
#घोषणा WM8962_PLL2_FRAC_MASK                   0x0040  /* PLL2_FRAC */
#घोषणा WM8962_PLL2_FRAC_SHIFT                       6  /* PLL2_FRAC */
#घोषणा WM8962_PLL2_FRAC_WIDTH                       1  /* PLL2_FRAC */
#घोषणा WM8962_PLL2_N_MASK                      0x001F  /* PLL2_N - [4:0] */
#घोषणा WM8962_PLL2_N_SHIFT                          0  /* PLL2_N - [4:0] */
#घोषणा WM8962_PLL2_N_WIDTH                          5  /* PLL2_N - [4:0] */

/*
 * R137 (0x89) - PLL 10
 */
#घोषणा WM8962_PLL2_K_MASK                      0x00FF  /* PLL2_K - [7:0] */
#घोषणा WM8962_PLL2_K_SHIFT                          0  /* PLL2_K - [7:0] */
#घोषणा WM8962_PLL2_K_WIDTH                          8  /* PLL2_K - [7:0] */

/*
 * R138 (0x8A) - PLL 11
 */
#घोषणा WM8962_PLL2_K_MASK                      0x00FF  /* PLL2_K - [7:0] */
#घोषणा WM8962_PLL2_K_SHIFT                          0  /* PLL2_K - [7:0] */
#घोषणा WM8962_PLL2_K_WIDTH                          8  /* PLL2_K - [7:0] */

/*
 * R139 (0x8B) - PLL 12
 */
#घोषणा WM8962_PLL2_K_MASK                      0x00FF  /* PLL2_K - [7:0] */
#घोषणा WM8962_PLL2_K_SHIFT                          0  /* PLL2_K - [7:0] */
#घोषणा WM8962_PLL2_K_WIDTH                          8  /* PLL2_K - [7:0] */

/*
 * R140 (0x8C) - PLL 13
 */
#घोषणा WM8962_PLL3_FRAC                        0x0040  /* PLL3_FRAC */
#घोषणा WM8962_PLL3_FRAC_MASK                   0x0040  /* PLL3_FRAC */
#घोषणा WM8962_PLL3_FRAC_SHIFT                       6  /* PLL3_FRAC */
#घोषणा WM8962_PLL3_FRAC_WIDTH                       1  /* PLL3_FRAC */
#घोषणा WM8962_PLL3_N_MASK                      0x001F  /* PLL3_N - [4:0] */
#घोषणा WM8962_PLL3_N_SHIFT                          0  /* PLL3_N - [4:0] */
#घोषणा WM8962_PLL3_N_WIDTH                          5  /* PLL3_N - [4:0] */

/*
 * R141 (0x8D) - PLL 14
 */
#घोषणा WM8962_PLL3_K_MASK                      0x00FF  /* PLL3_K - [7:0] */
#घोषणा WM8962_PLL3_K_SHIFT                          0  /* PLL3_K - [7:0] */
#घोषणा WM8962_PLL3_K_WIDTH                          8  /* PLL3_K - [7:0] */

/*
 * R142 (0x8E) - PLL 15
 */
#घोषणा WM8962_PLL3_K_MASK                      0x00FF  /* PLL3_K - [7:0] */
#घोषणा WM8962_PLL3_K_SHIFT                          0  /* PLL3_K - [7:0] */
#घोषणा WM8962_PLL3_K_WIDTH                          8  /* PLL3_K - [7:0] */

/*
 * R143 (0x8F) - PLL 16
 */
#घोषणा WM8962_PLL3_K_MASK                      0x00FF  /* PLL3_K - [7:0] */
#घोषणा WM8962_PLL3_K_SHIFT                          0  /* PLL3_K - [7:0] */
#घोषणा WM8962_PLL3_K_WIDTH                          8  /* PLL3_K - [7:0] */

/*
 * R155 (0x9B) - FLL Control (1)
 */
#घोषणा WM8962_FLL_REFCLK_SRC_MASK              0x0060  /* FLL_REFCLK_SRC - [6:5] */
#घोषणा WM8962_FLL_REFCLK_SRC_SHIFT                  5  /* FLL_REFCLK_SRC - [6:5] */
#घोषणा WM8962_FLL_REFCLK_SRC_WIDTH                  2  /* FLL_REFCLK_SRC - [6:5] */
#घोषणा WM8962_FLL_FRAC                         0x0004  /* FLL_FRAC */
#घोषणा WM8962_FLL_FRAC_MASK                    0x0004  /* FLL_FRAC */
#घोषणा WM8962_FLL_FRAC_SHIFT                        2  /* FLL_FRAC */
#घोषणा WM8962_FLL_FRAC_WIDTH                        1  /* FLL_FRAC */
#घोषणा WM8962_FLL_OSC_ENA                      0x0002  /* FLL_OSC_ENA */
#घोषणा WM8962_FLL_OSC_ENA_MASK                 0x0002  /* FLL_OSC_ENA */
#घोषणा WM8962_FLL_OSC_ENA_SHIFT                     1  /* FLL_OSC_ENA */
#घोषणा WM8962_FLL_OSC_ENA_WIDTH                     1  /* FLL_OSC_ENA */
#घोषणा WM8962_FLL_ENA                          0x0001  /* FLL_ENA */
#घोषणा WM8962_FLL_ENA_MASK                     0x0001  /* FLL_ENA */
#घोषणा WM8962_FLL_ENA_SHIFT                         0  /* FLL_ENA */
#घोषणा WM8962_FLL_ENA_WIDTH                         1  /* FLL_ENA */

/*
 * R156 (0x9C) - FLL Control (2)
 */
#घोषणा WM8962_FLL_OUTDIV_MASK                  0x01F8  /* FLL_OUTDIV - [8:3] */
#घोषणा WM8962_FLL_OUTDIV_SHIFT                      3  /* FLL_OUTDIV - [8:3] */
#घोषणा WM8962_FLL_OUTDIV_WIDTH                      6  /* FLL_OUTDIV - [8:3] */
#घोषणा WM8962_FLL_REFCLK_DIV_MASK              0x0003  /* FLL_REFCLK_DIV - [1:0] */
#घोषणा WM8962_FLL_REFCLK_DIV_SHIFT                  0  /* FLL_REFCLK_DIV - [1:0] */
#घोषणा WM8962_FLL_REFCLK_DIV_WIDTH                  2  /* FLL_REFCLK_DIV - [1:0] */

/*
 * R157 (0x9D) - FLL Control (3)
 */
#घोषणा WM8962_FLL_FRATIO_MASK                  0x0007  /* FLL_FRATIO - [2:0] */
#घोषणा WM8962_FLL_FRATIO_SHIFT                      0  /* FLL_FRATIO - [2:0] */
#घोषणा WM8962_FLL_FRATIO_WIDTH                      3  /* FLL_FRATIO - [2:0] */

/*
 * R159 (0x9F) - FLL Control (5)
 */
#घोषणा WM8962_FLL_FRC_NCO_VAL_MASK             0x007E  /* FLL_FRC_NCO_VAL - [6:1] */
#घोषणा WM8962_FLL_FRC_NCO_VAL_SHIFT                 1  /* FLL_FRC_NCO_VAL - [6:1] */
#घोषणा WM8962_FLL_FRC_NCO_VAL_WIDTH                 6  /* FLL_FRC_NCO_VAL - [6:1] */
#घोषणा WM8962_FLL_FRC_NCO                      0x0001  /* FLL_FRC_NCO */
#घोषणा WM8962_FLL_FRC_NCO_MASK                 0x0001  /* FLL_FRC_NCO */
#घोषणा WM8962_FLL_FRC_NCO_SHIFT                     0  /* FLL_FRC_NCO */
#घोषणा WM8962_FLL_FRC_NCO_WIDTH                     1  /* FLL_FRC_NCO */

/*
 * R160 (0xA0) - FLL Control (6)
 */
#घोषणा WM8962_FLL_THETA_MASK                   0xFFFF  /* FLL_THETA - [15:0] */
#घोषणा WM8962_FLL_THETA_SHIFT                       0  /* FLL_THETA - [15:0] */
#घोषणा WM8962_FLL_THETA_WIDTH                      16  /* FLL_THETA - [15:0] */

/*
 * R161 (0xA1) - FLL Control (7)
 */
#घोषणा WM8962_FLL_LAMBDA_MASK                  0xFFFF  /* FLL_LAMBDA - [15:0] */
#घोषणा WM8962_FLL_LAMBDA_SHIFT                      0  /* FLL_LAMBDA - [15:0] */
#घोषणा WM8962_FLL_LAMBDA_WIDTH                     16  /* FLL_LAMBDA - [15:0] */

/*
 * R162 (0xA2) - FLL Control (8)
 */
#घोषणा WM8962_FLL_N_MASK                       0x03FF  /* FLL_N - [9:0] */
#घोषणा WM8962_FLL_N_SHIFT                           0  /* FLL_N - [9:0] */
#घोषणा WM8962_FLL_N_WIDTH                          10  /* FLL_N - [9:0] */

/*
 * R252 (0xFC) - General test 1
 */
#घोषणा WM8962_REG_SYNC                         0x0004  /* REG_SYNC */
#घोषणा WM8962_REG_SYNC_MASK                    0x0004  /* REG_SYNC */
#घोषणा WM8962_REG_SYNC_SHIFT                        2  /* REG_SYNC */
#घोषणा WM8962_REG_SYNC_WIDTH                        1  /* REG_SYNC */
#घोषणा WM8962_AUTO_INC                         0x0001  /* AUTO_INC */
#घोषणा WM8962_AUTO_INC_MASK                    0x0001  /* AUTO_INC */
#घोषणा WM8962_AUTO_INC_SHIFT                        0  /* AUTO_INC */
#घोषणा WM8962_AUTO_INC_WIDTH                        1  /* AUTO_INC */

/*
 * R256 (0x100) - DF1
 */
#घोषणा WM8962_DRC_DF1_ENA                      0x0008  /* DRC_DF1_ENA */
#घोषणा WM8962_DRC_DF1_ENA_MASK                 0x0008  /* DRC_DF1_ENA */
#घोषणा WM8962_DRC_DF1_ENA_SHIFT                     3  /* DRC_DF1_ENA */
#घोषणा WM8962_DRC_DF1_ENA_WIDTH                     1  /* DRC_DF1_ENA */
#घोषणा WM8962_DF1_SHARED_COEFF                 0x0004  /* DF1_SHARED_COEFF */
#घोषणा WM8962_DF1_SHARED_COEFF_MASK            0x0004  /* DF1_SHARED_COEFF */
#घोषणा WM8962_DF1_SHARED_COEFF_SHIFT                2  /* DF1_SHARED_COEFF */
#घोषणा WM8962_DF1_SHARED_COEFF_WIDTH                1  /* DF1_SHARED_COEFF */
#घोषणा WM8962_DF1_SHARED_COEFF_SEL             0x0002  /* DF1_SHARED_COEFF_SEL */
#घोषणा WM8962_DF1_SHARED_COEFF_SEL_MASK        0x0002  /* DF1_SHARED_COEFF_SEL */
#घोषणा WM8962_DF1_SHARED_COEFF_SEL_SHIFT            1  /* DF1_SHARED_COEFF_SEL */
#घोषणा WM8962_DF1_SHARED_COEFF_SEL_WIDTH            1  /* DF1_SHARED_COEFF_SEL */
#घोषणा WM8962_DF1_ENA                          0x0001  /* DF1_ENA */
#घोषणा WM8962_DF1_ENA_MASK                     0x0001  /* DF1_ENA */
#घोषणा WM8962_DF1_ENA_SHIFT                         0  /* DF1_ENA */
#घोषणा WM8962_DF1_ENA_WIDTH                         1  /* DF1_ENA */

/*
 * R257 (0x101) - DF2
 */
#घोषणा WM8962_DF1_COEFF_L0_MASK                0xFFFF  /* DF1_COEFF_L0 - [15:0] */
#घोषणा WM8962_DF1_COEFF_L0_SHIFT                    0  /* DF1_COEFF_L0 - [15:0] */
#घोषणा WM8962_DF1_COEFF_L0_WIDTH                   16  /* DF1_COEFF_L0 - [15:0] */

/*
 * R258 (0x102) - DF3
 */
#घोषणा WM8962_DF1_COEFF_L1_MASK                0xFFFF  /* DF1_COEFF_L1 - [15:0] */
#घोषणा WM8962_DF1_COEFF_L1_SHIFT                    0  /* DF1_COEFF_L1 - [15:0] */
#घोषणा WM8962_DF1_COEFF_L1_WIDTH                   16  /* DF1_COEFF_L1 - [15:0] */

/*
 * R259 (0x103) - DF4
 */
#घोषणा WM8962_DF1_COEFF_L2_MASK                0xFFFF  /* DF1_COEFF_L2 - [15:0] */
#घोषणा WM8962_DF1_COEFF_L2_SHIFT                    0  /* DF1_COEFF_L2 - [15:0] */
#घोषणा WM8962_DF1_COEFF_L2_WIDTH                   16  /* DF1_COEFF_L2 - [15:0] */

/*
 * R260 (0x104) - DF5
 */
#घोषणा WM8962_DF1_COEFF_R0_MASK                0xFFFF  /* DF1_COEFF_R0 - [15:0] */
#घोषणा WM8962_DF1_COEFF_R0_SHIFT                    0  /* DF1_COEFF_R0 - [15:0] */
#घोषणा WM8962_DF1_COEFF_R0_WIDTH                   16  /* DF1_COEFF_R0 - [15:0] */

/*
 * R261 (0x105) - DF6
 */
#घोषणा WM8962_DF1_COEFF_R1_MASK                0xFFFF  /* DF1_COEFF_R1 - [15:0] */
#घोषणा WM8962_DF1_COEFF_R1_SHIFT                    0  /* DF1_COEFF_R1 - [15:0] */
#घोषणा WM8962_DF1_COEFF_R1_WIDTH                   16  /* DF1_COEFF_R1 - [15:0] */

/*
 * R262 (0x106) - DF7
 */
#घोषणा WM8962_DF1_COEFF_R2_MASK                0xFFFF  /* DF1_COEFF_R2 - [15:0] */
#घोषणा WM8962_DF1_COEFF_R2_SHIFT                    0  /* DF1_COEFF_R2 - [15:0] */
#घोषणा WM8962_DF1_COEFF_R2_WIDTH                   16  /* DF1_COEFF_R2 - [15:0] */

/*
 * R264 (0x108) - LHPF1
 */
#घोषणा WM8962_LHPF_MODE                        0x0002  /* LHPF_MODE */
#घोषणा WM8962_LHPF_MODE_MASK                   0x0002  /* LHPF_MODE */
#घोषणा WM8962_LHPF_MODE_SHIFT                       1  /* LHPF_MODE */
#घोषणा WM8962_LHPF_MODE_WIDTH                       1  /* LHPF_MODE */
#घोषणा WM8962_LHPF_ENA                         0x0001  /* LHPF_ENA */
#घोषणा WM8962_LHPF_ENA_MASK                    0x0001  /* LHPF_ENA */
#घोषणा WM8962_LHPF_ENA_SHIFT                        0  /* LHPF_ENA */
#घोषणा WM8962_LHPF_ENA_WIDTH                        1  /* LHPF_ENA */

/*
 * R265 (0x109) - LHPF2
 */
#घोषणा WM8962_LHPF_COEFF_MASK                  0xFFFF  /* LHPF_COEFF - [15:0] */
#घोषणा WM8962_LHPF_COEFF_SHIFT                      0  /* LHPF_COEFF - [15:0] */
#घोषणा WM8962_LHPF_COEFF_WIDTH                     16  /* LHPF_COEFF - [15:0] */

/*
 * R268 (0x10C) - THREED1
 */
#घोषणा WM8962_ADC_MONOMIX                      0x0040  /* ADC_MONOMIX */
#घोषणा WM8962_ADC_MONOMIX_MASK                 0x0040  /* ADC_MONOMIX */
#घोषणा WM8962_ADC_MONOMIX_SHIFT                     6  /* ADC_MONOMIX */
#घोषणा WM8962_ADC_MONOMIX_WIDTH                     1  /* ADC_MONOMIX */
#घोषणा WM8962_THREED_SIGN_L                    0x0020  /* THREED_SIGN_L */
#घोषणा WM8962_THREED_SIGN_L_MASK               0x0020  /* THREED_SIGN_L */
#घोषणा WM8962_THREED_SIGN_L_SHIFT                   5  /* THREED_SIGN_L */
#घोषणा WM8962_THREED_SIGN_L_WIDTH                   1  /* THREED_SIGN_L */
#घोषणा WM8962_THREED_SIGN_R                    0x0010  /* THREED_SIGN_R */
#घोषणा WM8962_THREED_SIGN_R_MASK               0x0010  /* THREED_SIGN_R */
#घोषणा WM8962_THREED_SIGN_R_SHIFT                   4  /* THREED_SIGN_R */
#घोषणा WM8962_THREED_SIGN_R_WIDTH                   1  /* THREED_SIGN_R */
#घोषणा WM8962_THREED_LHPF_MODE                 0x0004  /* THREED_LHPF_MODE */
#घोषणा WM8962_THREED_LHPF_MODE_MASK            0x0004  /* THREED_LHPF_MODE */
#घोषणा WM8962_THREED_LHPF_MODE_SHIFT                2  /* THREED_LHPF_MODE */
#घोषणा WM8962_THREED_LHPF_MODE_WIDTH                1  /* THREED_LHPF_MODE */
#घोषणा WM8962_THREED_LHPF_ENA                  0x0002  /* THREED_LHPF_ENA */
#घोषणा WM8962_THREED_LHPF_ENA_MASK             0x0002  /* THREED_LHPF_ENA */
#घोषणा WM8962_THREED_LHPF_ENA_SHIFT                 1  /* THREED_LHPF_ENA */
#घोषणा WM8962_THREED_LHPF_ENA_WIDTH                 1  /* THREED_LHPF_ENA */
#घोषणा WM8962_THREED_ENA                       0x0001  /* THREED_ENA */
#घोषणा WM8962_THREED_ENA_MASK                  0x0001  /* THREED_ENA */
#घोषणा WM8962_THREED_ENA_SHIFT                      0  /* THREED_ENA */
#घोषणा WM8962_THREED_ENA_WIDTH                      1  /* THREED_ENA */

/*
 * R269 (0x10D) - THREED2
 */
#घोषणा WM8962_THREED_FGAINL_MASK               0xF800  /* THREED_FGAINL - [15:11] */
#घोषणा WM8962_THREED_FGAINL_SHIFT                  11  /* THREED_FGAINL - [15:11] */
#घोषणा WM8962_THREED_FGAINL_WIDTH                   5  /* THREED_FGAINL - [15:11] */
#घोषणा WM8962_THREED_CGAINL_MASK               0x07C0  /* THREED_CGAINL - [10:6] */
#घोषणा WM8962_THREED_CGAINL_SHIFT                   6  /* THREED_CGAINL - [10:6] */
#घोषणा WM8962_THREED_CGAINL_WIDTH                   5  /* THREED_CGAINL - [10:6] */
#घोषणा WM8962_THREED_DELAYL_MASK               0x003C  /* THREED_DELAYL - [5:2] */
#घोषणा WM8962_THREED_DELAYL_SHIFT                   2  /* THREED_DELAYL - [5:2] */
#घोषणा WM8962_THREED_DELAYL_WIDTH                   4  /* THREED_DELAYL - [5:2] */

/*
 * R270 (0x10E) - THREED3
 */
#घोषणा WM8962_THREED_LHPF_COEFF_MASK           0xFFFF  /* THREED_LHPF_COEFF - [15:0] */
#घोषणा WM8962_THREED_LHPF_COEFF_SHIFT               0  /* THREED_LHPF_COEFF - [15:0] */
#घोषणा WM8962_THREED_LHPF_COEFF_WIDTH              16  /* THREED_LHPF_COEFF - [15:0] */

/*
 * R271 (0x10F) - THREED4
 */
#घोषणा WM8962_THREED_FGAINR_MASK               0xF800  /* THREED_FGAINR - [15:11] */
#घोषणा WM8962_THREED_FGAINR_SHIFT                  11  /* THREED_FGAINR - [15:11] */
#घोषणा WM8962_THREED_FGAINR_WIDTH                   5  /* THREED_FGAINR - [15:11] */
#घोषणा WM8962_THREED_CGAINR_MASK               0x07C0  /* THREED_CGAINR - [10:6] */
#घोषणा WM8962_THREED_CGAINR_SHIFT                   6  /* THREED_CGAINR - [10:6] */
#घोषणा WM8962_THREED_CGAINR_WIDTH                   5  /* THREED_CGAINR - [10:6] */
#घोषणा WM8962_THREED_DELAYR_MASK               0x003C  /* THREED_DELAYR - [5:2] */
#घोषणा WM8962_THREED_DELAYR_SHIFT                   2  /* THREED_DELAYR - [5:2] */
#घोषणा WM8962_THREED_DELAYR_WIDTH                   4  /* THREED_DELAYR - [5:2] */

/*
 * R276 (0x114) - DRC 1
 */
#घोषणा WM8962_DRC_SIG_DET_RMS_MASK             0x7C00  /* DRC_SIG_DET_RMS - [14:10] */
#घोषणा WM8962_DRC_SIG_DET_RMS_SHIFT                10  /* DRC_SIG_DET_RMS - [14:10] */
#घोषणा WM8962_DRC_SIG_DET_RMS_WIDTH                 5  /* DRC_SIG_DET_RMS - [14:10] */
#घोषणा WM8962_DRC_SIG_DET_PK_MASK              0x0300  /* DRC_SIG_DET_PK - [9:8] */
#घोषणा WM8962_DRC_SIG_DET_PK_SHIFT                  8  /* DRC_SIG_DET_PK - [9:8] */
#घोषणा WM8962_DRC_SIG_DET_PK_WIDTH                  2  /* DRC_SIG_DET_PK - [9:8] */
#घोषणा WM8962_DRC_NG_ENA                       0x0080  /* DRC_NG_ENA */
#घोषणा WM8962_DRC_NG_ENA_MASK                  0x0080  /* DRC_NG_ENA */
#घोषणा WM8962_DRC_NG_ENA_SHIFT                      7  /* DRC_NG_ENA */
#घोषणा WM8962_DRC_NG_ENA_WIDTH                      1  /* DRC_NG_ENA */
#घोषणा WM8962_DRC_SIG_DET_MODE                 0x0040  /* DRC_SIG_DET_MODE */
#घोषणा WM8962_DRC_SIG_DET_MODE_MASK            0x0040  /* DRC_SIG_DET_MODE */
#घोषणा WM8962_DRC_SIG_DET_MODE_SHIFT                6  /* DRC_SIG_DET_MODE */
#घोषणा WM8962_DRC_SIG_DET_MODE_WIDTH                1  /* DRC_SIG_DET_MODE */
#घोषणा WM8962_DRC_SIG_DET                      0x0020  /* DRC_SIG_DET */
#घोषणा WM8962_DRC_SIG_DET_MASK                 0x0020  /* DRC_SIG_DET */
#घोषणा WM8962_DRC_SIG_DET_SHIFT                     5  /* DRC_SIG_DET */
#घोषणा WM8962_DRC_SIG_DET_WIDTH                     1  /* DRC_SIG_DET */
#घोषणा WM8962_DRC_KNEE2_OP_ENA                 0x0010  /* DRC_KNEE2_OP_ENA */
#घोषणा WM8962_DRC_KNEE2_OP_ENA_MASK            0x0010  /* DRC_KNEE2_OP_ENA */
#घोषणा WM8962_DRC_KNEE2_OP_ENA_SHIFT                4  /* DRC_KNEE2_OP_ENA */
#घोषणा WM8962_DRC_KNEE2_OP_ENA_WIDTH                1  /* DRC_KNEE2_OP_ENA */
#घोषणा WM8962_DRC_QR                           0x0008  /* DRC_QR */
#घोषणा WM8962_DRC_QR_MASK                      0x0008  /* DRC_QR */
#घोषणा WM8962_DRC_QR_SHIFT                          3  /* DRC_QR */
#घोषणा WM8962_DRC_QR_WIDTH                          1  /* DRC_QR */
#घोषणा WM8962_DRC_ANTICLIP                     0x0004  /* DRC_ANTICLIP */
#घोषणा WM8962_DRC_ANTICLIP_MASK                0x0004  /* DRC_ANTICLIP */
#घोषणा WM8962_DRC_ANTICLIP_SHIFT                    2  /* DRC_ANTICLIP */
#घोषणा WM8962_DRC_ANTICLIP_WIDTH                    1  /* DRC_ANTICLIP */
#घोषणा WM8962_DRC_MODE                         0x0002  /* DRC_MODE */
#घोषणा WM8962_DRC_MODE_MASK                    0x0002  /* DRC_MODE */
#घोषणा WM8962_DRC_MODE_SHIFT                        1  /* DRC_MODE */
#घोषणा WM8962_DRC_MODE_WIDTH                        1  /* DRC_MODE */
#घोषणा WM8962_DRC_ENA                          0x0001  /* DRC_ENA */
#घोषणा WM8962_DRC_ENA_MASK                     0x0001  /* DRC_ENA */
#घोषणा WM8962_DRC_ENA_SHIFT                         0  /* DRC_ENA */
#घोषणा WM8962_DRC_ENA_WIDTH                         1  /* DRC_ENA */

/*
 * R277 (0x115) - DRC 2
 */
#घोषणा WM8962_DRC_ATK_MASK                     0x1E00  /* DRC_ATK - [12:9] */
#घोषणा WM8962_DRC_ATK_SHIFT                         9  /* DRC_ATK - [12:9] */
#घोषणा WM8962_DRC_ATK_WIDTH                         4  /* DRC_ATK - [12:9] */
#घोषणा WM8962_DRC_DCY_MASK                     0x01E0  /* DRC_DCY - [8:5] */
#घोषणा WM8962_DRC_DCY_SHIFT                         5  /* DRC_DCY - [8:5] */
#घोषणा WM8962_DRC_DCY_WIDTH                         4  /* DRC_DCY - [8:5] */
#घोषणा WM8962_DRC_MINGAIN_MASK                 0x001C  /* DRC_MINGAIN - [4:2] */
#घोषणा WM8962_DRC_MINGAIN_SHIFT                     2  /* DRC_MINGAIN - [4:2] */
#घोषणा WM8962_DRC_MINGAIN_WIDTH                     3  /* DRC_MINGAIN - [4:2] */
#घोषणा WM8962_DRC_MAXGAIN_MASK                 0x0003  /* DRC_MAXGAIN - [1:0] */
#घोषणा WM8962_DRC_MAXGAIN_SHIFT                     0  /* DRC_MAXGAIN - [1:0] */
#घोषणा WM8962_DRC_MAXGAIN_WIDTH                     2  /* DRC_MAXGAIN - [1:0] */

/*
 * R278 (0x116) - DRC 3
 */
#घोषणा WM8962_DRC_NG_MINGAIN_MASK              0xF000  /* DRC_NG_MINGAIN - [15:12] */
#घोषणा WM8962_DRC_NG_MINGAIN_SHIFT                 12  /* DRC_NG_MINGAIN - [15:12] */
#घोषणा WM8962_DRC_NG_MINGAIN_WIDTH                  4  /* DRC_NG_MINGAIN - [15:12] */
#घोषणा WM8962_DRC_QR_THR_MASK                  0x0C00  /* DRC_QR_THR - [11:10] */
#घोषणा WM8962_DRC_QR_THR_SHIFT                     10  /* DRC_QR_THR - [11:10] */
#घोषणा WM8962_DRC_QR_THR_WIDTH                      2  /* DRC_QR_THR - [11:10] */
#घोषणा WM8962_DRC_QR_DCY_MASK                  0x0300  /* DRC_QR_DCY - [9:8] */
#घोषणा WM8962_DRC_QR_DCY_SHIFT                      8  /* DRC_QR_DCY - [9:8] */
#घोषणा WM8962_DRC_QR_DCY_WIDTH                      2  /* DRC_QR_DCY - [9:8] */
#घोषणा WM8962_DRC_NG_EXP_MASK                  0x00C0  /* DRC_NG_EXP - [7:6] */
#घोषणा WM8962_DRC_NG_EXP_SHIFT                      6  /* DRC_NG_EXP - [7:6] */
#घोषणा WM8962_DRC_NG_EXP_WIDTH                      2  /* DRC_NG_EXP - [7:6] */
#घोषणा WM8962_DRC_HI_COMP_MASK                 0x0038  /* DRC_HI_COMP - [5:3] */
#घोषणा WM8962_DRC_HI_COMP_SHIFT                     3  /* DRC_HI_COMP - [5:3] */
#घोषणा WM8962_DRC_HI_COMP_WIDTH                     3  /* DRC_HI_COMP - [5:3] */
#घोषणा WM8962_DRC_LO_COMP_MASK                 0x0007  /* DRC_LO_COMP - [2:0] */
#घोषणा WM8962_DRC_LO_COMP_SHIFT                     0  /* DRC_LO_COMP - [2:0] */
#घोषणा WM8962_DRC_LO_COMP_WIDTH                     3  /* DRC_LO_COMP - [2:0] */

/*
 * R279 (0x117) - DRC 4
 */
#घोषणा WM8962_DRC_KNEE_IP_MASK                 0x07E0  /* DRC_KNEE_IP - [10:5] */
#घोषणा WM8962_DRC_KNEE_IP_SHIFT                     5  /* DRC_KNEE_IP - [10:5] */
#घोषणा WM8962_DRC_KNEE_IP_WIDTH                     6  /* DRC_KNEE_IP - [10:5] */
#घोषणा WM8962_DRC_KNEE_OP_MASK                 0x001F  /* DRC_KNEE_OP - [4:0] */
#घोषणा WM8962_DRC_KNEE_OP_SHIFT                     0  /* DRC_KNEE_OP - [4:0] */
#घोषणा WM8962_DRC_KNEE_OP_WIDTH                     5  /* DRC_KNEE_OP - [4:0] */

/*
 * R280 (0x118) - DRC 5
 */
#घोषणा WM8962_DRC_KNEE2_IP_MASK                0x03E0  /* DRC_KNEE2_IP - [9:5] */
#घोषणा WM8962_DRC_KNEE2_IP_SHIFT                    5  /* DRC_KNEE2_IP - [9:5] */
#घोषणा WM8962_DRC_KNEE2_IP_WIDTH                    5  /* DRC_KNEE2_IP - [9:5] */
#घोषणा WM8962_DRC_KNEE2_OP_MASK                0x001F  /* DRC_KNEE2_OP - [4:0] */
#घोषणा WM8962_DRC_KNEE2_OP_SHIFT                    0  /* DRC_KNEE2_OP - [4:0] */
#घोषणा WM8962_DRC_KNEE2_OP_WIDTH                    5  /* DRC_KNEE2_OP - [4:0] */

/*
 * R285 (0x11D) - Tloopback
 */
#घोषणा WM8962_TLB_ENA                          0x0002  /* TLB_ENA */
#घोषणा WM8962_TLB_ENA_MASK                     0x0002  /* TLB_ENA */
#घोषणा WM8962_TLB_ENA_SHIFT                         1  /* TLB_ENA */
#घोषणा WM8962_TLB_ENA_WIDTH                         1  /* TLB_ENA */
#घोषणा WM8962_TLB_MODE                         0x0001  /* TLB_MODE */
#घोषणा WM8962_TLB_MODE_MASK                    0x0001  /* TLB_MODE */
#घोषणा WM8962_TLB_MODE_SHIFT                        0  /* TLB_MODE */
#घोषणा WM8962_TLB_MODE_WIDTH                        1  /* TLB_MODE */

/*
 * R335 (0x14F) - EQ1
 */
#घोषणा WM8962_EQ_SHARED_COEFF                  0x0004  /* EQ_SHARED_COEFF */
#घोषणा WM8962_EQ_SHARED_COEFF_MASK             0x0004  /* EQ_SHARED_COEFF */
#घोषणा WM8962_EQ_SHARED_COEFF_SHIFT                 2  /* EQ_SHARED_COEFF */
#घोषणा WM8962_EQ_SHARED_COEFF_WIDTH                 1  /* EQ_SHARED_COEFF */
#घोषणा WM8962_EQ_SHARED_COEFF_SEL              0x0002  /* EQ_SHARED_COEFF_SEL */
#घोषणा WM8962_EQ_SHARED_COEFF_SEL_MASK         0x0002  /* EQ_SHARED_COEFF_SEL */
#घोषणा WM8962_EQ_SHARED_COEFF_SEL_SHIFT             1  /* EQ_SHARED_COEFF_SEL */
#घोषणा WM8962_EQ_SHARED_COEFF_SEL_WIDTH             1  /* EQ_SHARED_COEFF_SEL */
#घोषणा WM8962_EQ_ENA                           0x0001  /* EQ_ENA */
#घोषणा WM8962_EQ_ENA_MASK                      0x0001  /* EQ_ENA */
#घोषणा WM8962_EQ_ENA_SHIFT                          0  /* EQ_ENA */
#घोषणा WM8962_EQ_ENA_WIDTH                          1  /* EQ_ENA */

/*
 * R336 (0x150) - EQ2
 */
#घोषणा WM8962_EQL_B1_GAIN_MASK                 0xF800  /* EQL_B1_GAIN - [15:11] */
#घोषणा WM8962_EQL_B1_GAIN_SHIFT                    11  /* EQL_B1_GAIN - [15:11] */
#घोषणा WM8962_EQL_B1_GAIN_WIDTH                     5  /* EQL_B1_GAIN - [15:11] */
#घोषणा WM8962_EQL_B2_GAIN_MASK                 0x07C0  /* EQL_B2_GAIN - [10:6] */
#घोषणा WM8962_EQL_B2_GAIN_SHIFT                     6  /* EQL_B2_GAIN - [10:6] */
#घोषणा WM8962_EQL_B2_GAIN_WIDTH                     5  /* EQL_B2_GAIN - [10:6] */
#घोषणा WM8962_EQL_B3_GAIN_MASK                 0x003E  /* EQL_B3_GAIN - [5:1] */
#घोषणा WM8962_EQL_B3_GAIN_SHIFT                     1  /* EQL_B3_GAIN - [5:1] */
#घोषणा WM8962_EQL_B3_GAIN_WIDTH                     5  /* EQL_B3_GAIN - [5:1] */

/*
 * R337 (0x151) - EQ3
 */
#घोषणा WM8962_EQL_B4_GAIN_MASK                 0xF800  /* EQL_B4_GAIN - [15:11] */
#घोषणा WM8962_EQL_B4_GAIN_SHIFT                    11  /* EQL_B4_GAIN - [15:11] */
#घोषणा WM8962_EQL_B4_GAIN_WIDTH                     5  /* EQL_B4_GAIN - [15:11] */
#घोषणा WM8962_EQL_B5_GAIN_MASK                 0x07C0  /* EQL_B5_GAIN - [10:6] */
#घोषणा WM8962_EQL_B5_GAIN_SHIFT                     6  /* EQL_B5_GAIN - [10:6] */
#घोषणा WM8962_EQL_B5_GAIN_WIDTH                     5  /* EQL_B5_GAIN - [10:6] */

/*
 * R338 (0x152) - EQ4
 */
#घोषणा WM8962_EQL_B1_A_MASK                    0xFFFF  /* EQL_B1_A - [15:0] */
#घोषणा WM8962_EQL_B1_A_SHIFT                        0  /* EQL_B1_A - [15:0] */
#घोषणा WM8962_EQL_B1_A_WIDTH                       16  /* EQL_B1_A - [15:0] */

/*
 * R339 (0x153) - EQ5
 */
#घोषणा WM8962_EQL_B1_B_MASK                    0xFFFF  /* EQL_B1_B - [15:0] */
#घोषणा WM8962_EQL_B1_B_SHIFT                        0  /* EQL_B1_B - [15:0] */
#घोषणा WM8962_EQL_B1_B_WIDTH                       16  /* EQL_B1_B - [15:0] */

/*
 * R340 (0x154) - EQ6
 */
#घोषणा WM8962_EQL_B1_PG_MASK                   0xFFFF  /* EQL_B1_PG - [15:0] */
#घोषणा WM8962_EQL_B1_PG_SHIFT                       0  /* EQL_B1_PG - [15:0] */
#घोषणा WM8962_EQL_B1_PG_WIDTH                      16  /* EQL_B1_PG - [15:0] */

/*
 * R341 (0x155) - EQ7
 */
#घोषणा WM8962_EQL_B2_A_MASK                    0xFFFF  /* EQL_B2_A - [15:0] */
#घोषणा WM8962_EQL_B2_A_SHIFT                        0  /* EQL_B2_A - [15:0] */
#घोषणा WM8962_EQL_B2_A_WIDTH                       16  /* EQL_B2_A - [15:0] */

/*
 * R342 (0x156) - EQ8
 */
#घोषणा WM8962_EQL_B2_B_MASK                    0xFFFF  /* EQL_B2_B - [15:0] */
#घोषणा WM8962_EQL_B2_B_SHIFT                        0  /* EQL_B2_B - [15:0] */
#घोषणा WM8962_EQL_B2_B_WIDTH                       16  /* EQL_B2_B - [15:0] */

/*
 * R343 (0x157) - EQ9
 */
#घोषणा WM8962_EQL_B2_C_MASK                    0xFFFF  /* EQL_B2_C - [15:0] */
#घोषणा WM8962_EQL_B2_C_SHIFT                        0  /* EQL_B2_C - [15:0] */
#घोषणा WM8962_EQL_B2_C_WIDTH                       16  /* EQL_B2_C - [15:0] */

/*
 * R344 (0x158) - EQ10
 */
#घोषणा WM8962_EQL_B2_PG_MASK                   0xFFFF  /* EQL_B2_PG - [15:0] */
#घोषणा WM8962_EQL_B2_PG_SHIFT                       0  /* EQL_B2_PG - [15:0] */
#घोषणा WM8962_EQL_B2_PG_WIDTH                      16  /* EQL_B2_PG - [15:0] */

/*
 * R345 (0x159) - EQ11
 */
#घोषणा WM8962_EQL_B3_A_MASK                    0xFFFF  /* EQL_B3_A - [15:0] */
#घोषणा WM8962_EQL_B3_A_SHIFT                        0  /* EQL_B3_A - [15:0] */
#घोषणा WM8962_EQL_B3_A_WIDTH                       16  /* EQL_B3_A - [15:0] */

/*
 * R346 (0x15A) - EQ12
 */
#घोषणा WM8962_EQL_B3_B_MASK                    0xFFFF  /* EQL_B3_B - [15:0] */
#घोषणा WM8962_EQL_B3_B_SHIFT                        0  /* EQL_B3_B - [15:0] */
#घोषणा WM8962_EQL_B3_B_WIDTH                       16  /* EQL_B3_B - [15:0] */

/*
 * R347 (0x15B) - EQ13
 */
#घोषणा WM8962_EQL_B3_C_MASK                    0xFFFF  /* EQL_B3_C - [15:0] */
#घोषणा WM8962_EQL_B3_C_SHIFT                        0  /* EQL_B3_C - [15:0] */
#घोषणा WM8962_EQL_B3_C_WIDTH                       16  /* EQL_B3_C - [15:0] */

/*
 * R348 (0x15C) - EQ14
 */
#घोषणा WM8962_EQL_B3_PG_MASK                   0xFFFF  /* EQL_B3_PG - [15:0] */
#घोषणा WM8962_EQL_B3_PG_SHIFT                       0  /* EQL_B3_PG - [15:0] */
#घोषणा WM8962_EQL_B3_PG_WIDTH                      16  /* EQL_B3_PG - [15:0] */

/*
 * R349 (0x15D) - EQ15
 */
#घोषणा WM8962_EQL_B4_A_MASK                    0xFFFF  /* EQL_B4_A - [15:0] */
#घोषणा WM8962_EQL_B4_A_SHIFT                        0  /* EQL_B4_A - [15:0] */
#घोषणा WM8962_EQL_B4_A_WIDTH                       16  /* EQL_B4_A - [15:0] */

/*
 * R350 (0x15E) - EQ16
 */
#घोषणा WM8962_EQL_B4_B_MASK                    0xFFFF  /* EQL_B4_B - [15:0] */
#घोषणा WM8962_EQL_B4_B_SHIFT                        0  /* EQL_B4_B - [15:0] */
#घोषणा WM8962_EQL_B4_B_WIDTH                       16  /* EQL_B4_B - [15:0] */

/*
 * R351 (0x15F) - EQ17
 */
#घोषणा WM8962_EQL_B4_C_MASK                    0xFFFF  /* EQL_B4_C - [15:0] */
#घोषणा WM8962_EQL_B4_C_SHIFT                        0  /* EQL_B4_C - [15:0] */
#घोषणा WM8962_EQL_B4_C_WIDTH                       16  /* EQL_B4_C - [15:0] */

/*
 * R352 (0x160) - EQ18
 */
#घोषणा WM8962_EQL_B4_PG_MASK                   0xFFFF  /* EQL_B4_PG - [15:0] */
#घोषणा WM8962_EQL_B4_PG_SHIFT                       0  /* EQL_B4_PG - [15:0] */
#घोषणा WM8962_EQL_B4_PG_WIDTH                      16  /* EQL_B4_PG - [15:0] */

/*
 * R353 (0x161) - EQ19
 */
#घोषणा WM8962_EQL_B5_A_MASK                    0xFFFF  /* EQL_B5_A - [15:0] */
#घोषणा WM8962_EQL_B5_A_SHIFT                        0  /* EQL_B5_A - [15:0] */
#घोषणा WM8962_EQL_B5_A_WIDTH                       16  /* EQL_B5_A - [15:0] */

/*
 * R354 (0x162) - EQ20
 */
#घोषणा WM8962_EQL_B5_B_MASK                    0xFFFF  /* EQL_B5_B - [15:0] */
#घोषणा WM8962_EQL_B5_B_SHIFT                        0  /* EQL_B5_B - [15:0] */
#घोषणा WM8962_EQL_B5_B_WIDTH                       16  /* EQL_B5_B - [15:0] */

/*
 * R355 (0x163) - EQ21
 */
#घोषणा WM8962_EQL_B5_PG_MASK                   0xFFFF  /* EQL_B5_PG - [15:0] */
#घोषणा WM8962_EQL_B5_PG_SHIFT                       0  /* EQL_B5_PG - [15:0] */
#घोषणा WM8962_EQL_B5_PG_WIDTH                      16  /* EQL_B5_PG - [15:0] */

/*
 * R356 (0x164) - EQ22
 */
#घोषणा WM8962_EQR_B1_GAIN_MASK                 0xF800  /* EQR_B1_GAIN - [15:11] */
#घोषणा WM8962_EQR_B1_GAIN_SHIFT                    11  /* EQR_B1_GAIN - [15:11] */
#घोषणा WM8962_EQR_B1_GAIN_WIDTH                     5  /* EQR_B1_GAIN - [15:11] */
#घोषणा WM8962_EQR_B2_GAIN_MASK                 0x07C0  /* EQR_B2_GAIN - [10:6] */
#घोषणा WM8962_EQR_B2_GAIN_SHIFT                     6  /* EQR_B2_GAIN - [10:6] */
#घोषणा WM8962_EQR_B2_GAIN_WIDTH                     5  /* EQR_B2_GAIN - [10:6] */
#घोषणा WM8962_EQR_B3_GAIN_MASK                 0x003E  /* EQR_B3_GAIN - [5:1] */
#घोषणा WM8962_EQR_B3_GAIN_SHIFT                     1  /* EQR_B3_GAIN - [5:1] */
#घोषणा WM8962_EQR_B3_GAIN_WIDTH                     5  /* EQR_B3_GAIN - [5:1] */

/*
 * R357 (0x165) - EQ23
 */
#घोषणा WM8962_EQR_B4_GAIN_MASK                 0xF800  /* EQR_B4_GAIN - [15:11] */
#घोषणा WM8962_EQR_B4_GAIN_SHIFT                    11  /* EQR_B4_GAIN - [15:11] */
#घोषणा WM8962_EQR_B4_GAIN_WIDTH                     5  /* EQR_B4_GAIN - [15:11] */
#घोषणा WM8962_EQR_B5_GAIN_MASK                 0x07C0  /* EQR_B5_GAIN - [10:6] */
#घोषणा WM8962_EQR_B5_GAIN_SHIFT                     6  /* EQR_B5_GAIN - [10:6] */
#घोषणा WM8962_EQR_B5_GAIN_WIDTH                     5  /* EQR_B5_GAIN - [10:6] */

/*
 * R358 (0x166) - EQ24
 */
#घोषणा WM8962_EQR_B1_A_MASK                    0xFFFF  /* EQR_B1_A - [15:0] */
#घोषणा WM8962_EQR_B1_A_SHIFT                        0  /* EQR_B1_A - [15:0] */
#घोषणा WM8962_EQR_B1_A_WIDTH                       16  /* EQR_B1_A - [15:0] */

/*
 * R359 (0x167) - EQ25
 */
#घोषणा WM8962_EQR_B1_B_MASK                    0xFFFF  /* EQR_B1_B - [15:0] */
#घोषणा WM8962_EQR_B1_B_SHIFT                        0  /* EQR_B1_B - [15:0] */
#घोषणा WM8962_EQR_B1_B_WIDTH                       16  /* EQR_B1_B - [15:0] */

/*
 * R360 (0x168) - EQ26
 */
#घोषणा WM8962_EQR_B1_PG_MASK                   0xFFFF  /* EQR_B1_PG - [15:0] */
#घोषणा WM8962_EQR_B1_PG_SHIFT                       0  /* EQR_B1_PG - [15:0] */
#घोषणा WM8962_EQR_B1_PG_WIDTH                      16  /* EQR_B1_PG - [15:0] */

/*
 * R361 (0x169) - EQ27
 */
#घोषणा WM8962_EQR_B2_A_MASK                    0xFFFF  /* EQR_B2_A - [15:0] */
#घोषणा WM8962_EQR_B2_A_SHIFT                        0  /* EQR_B2_A - [15:0] */
#घोषणा WM8962_EQR_B2_A_WIDTH                       16  /* EQR_B2_A - [15:0] */

/*
 * R362 (0x16A) - EQ28
 */
#घोषणा WM8962_EQR_B2_B_MASK                    0xFFFF  /* EQR_B2_B - [15:0] */
#घोषणा WM8962_EQR_B2_B_SHIFT                        0  /* EQR_B2_B - [15:0] */
#घोषणा WM8962_EQR_B2_B_WIDTH                       16  /* EQR_B2_B - [15:0] */

/*
 * R363 (0x16B) - EQ29
 */
#घोषणा WM8962_EQR_B2_C_MASK                    0xFFFF  /* EQR_B2_C - [15:0] */
#घोषणा WM8962_EQR_B2_C_SHIFT                        0  /* EQR_B2_C - [15:0] */
#घोषणा WM8962_EQR_B2_C_WIDTH                       16  /* EQR_B2_C - [15:0] */

/*
 * R364 (0x16C) - EQ30
 */
#घोषणा WM8962_EQR_B2_PG_MASK                   0xFFFF  /* EQR_B2_PG - [15:0] */
#घोषणा WM8962_EQR_B2_PG_SHIFT                       0  /* EQR_B2_PG - [15:0] */
#घोषणा WM8962_EQR_B2_PG_WIDTH                      16  /* EQR_B2_PG - [15:0] */

/*
 * R365 (0x16D) - EQ31
 */
#घोषणा WM8962_EQR_B3_A_MASK                    0xFFFF  /* EQR_B3_A - [15:0] */
#घोषणा WM8962_EQR_B3_A_SHIFT                        0  /* EQR_B3_A - [15:0] */
#घोषणा WM8962_EQR_B3_A_WIDTH                       16  /* EQR_B3_A - [15:0] */

/*
 * R366 (0x16E) - EQ32
 */
#घोषणा WM8962_EQR_B3_B_MASK                    0xFFFF  /* EQR_B3_B - [15:0] */
#घोषणा WM8962_EQR_B3_B_SHIFT                        0  /* EQR_B3_B - [15:0] */
#घोषणा WM8962_EQR_B3_B_WIDTH                       16  /* EQR_B3_B - [15:0] */

/*
 * R367 (0x16F) - EQ33
 */
#घोषणा WM8962_EQR_B3_C_MASK                    0xFFFF  /* EQR_B3_C - [15:0] */
#घोषणा WM8962_EQR_B3_C_SHIFT                        0  /* EQR_B3_C - [15:0] */
#घोषणा WM8962_EQR_B3_C_WIDTH                       16  /* EQR_B3_C - [15:0] */

/*
 * R368 (0x170) - EQ34
 */
#घोषणा WM8962_EQR_B3_PG_MASK                   0xFFFF  /* EQR_B3_PG - [15:0] */
#घोषणा WM8962_EQR_B3_PG_SHIFT                       0  /* EQR_B3_PG - [15:0] */
#घोषणा WM8962_EQR_B3_PG_WIDTH                      16  /* EQR_B3_PG - [15:0] */

/*
 * R369 (0x171) - EQ35
 */
#घोषणा WM8962_EQR_B4_A_MASK                    0xFFFF  /* EQR_B4_A - [15:0] */
#घोषणा WM8962_EQR_B4_A_SHIFT                        0  /* EQR_B4_A - [15:0] */
#घोषणा WM8962_EQR_B4_A_WIDTH                       16  /* EQR_B4_A - [15:0] */

/*
 * R370 (0x172) - EQ36
 */
#घोषणा WM8962_EQR_B4_B_MASK                    0xFFFF  /* EQR_B4_B - [15:0] */
#घोषणा WM8962_EQR_B4_B_SHIFT                        0  /* EQR_B4_B - [15:0] */
#घोषणा WM8962_EQR_B4_B_WIDTH                       16  /* EQR_B4_B - [15:0] */

/*
 * R371 (0x173) - EQ37
 */
#घोषणा WM8962_EQR_B4_C_MASK                    0xFFFF  /* EQR_B4_C - [15:0] */
#घोषणा WM8962_EQR_B4_C_SHIFT                        0  /* EQR_B4_C - [15:0] */
#घोषणा WM8962_EQR_B4_C_WIDTH                       16  /* EQR_B4_C - [15:0] */

/*
 * R372 (0x174) - EQ38
 */
#घोषणा WM8962_EQR_B4_PG_MASK                   0xFFFF  /* EQR_B4_PG - [15:0] */
#घोषणा WM8962_EQR_B4_PG_SHIFT                       0  /* EQR_B4_PG - [15:0] */
#घोषणा WM8962_EQR_B4_PG_WIDTH                      16  /* EQR_B4_PG - [15:0] */

/*
 * R373 (0x175) - EQ39
 */
#घोषणा WM8962_EQR_B5_A_MASK                    0xFFFF  /* EQR_B5_A - [15:0] */
#घोषणा WM8962_EQR_B5_A_SHIFT                        0  /* EQR_B5_A - [15:0] */
#घोषणा WM8962_EQR_B5_A_WIDTH                       16  /* EQR_B5_A - [15:0] */

/*
 * R374 (0x176) - EQ40
 */
#घोषणा WM8962_EQR_B5_B_MASK                    0xFFFF  /* EQR_B5_B - [15:0] */
#घोषणा WM8962_EQR_B5_B_SHIFT                        0  /* EQR_B5_B - [15:0] */
#घोषणा WM8962_EQR_B5_B_WIDTH                       16  /* EQR_B5_B - [15:0] */

/*
 * R375 (0x177) - EQ41
 */
#घोषणा WM8962_EQR_B5_PG_MASK                   0xFFFF  /* EQR_B5_PG - [15:0] */
#घोषणा WM8962_EQR_B5_PG_SHIFT                       0  /* EQR_B5_PG - [15:0] */
#घोषणा WM8962_EQR_B5_PG_WIDTH                      16  /* EQR_B5_PG - [15:0] */

/*
 * R513 (0x201) - GPIO 2
 */
#घोषणा WM8962_GP2_POL                          0x0400  /* GP2_POL */
#घोषणा WM8962_GP2_POL_MASK                     0x0400  /* GP2_POL */
#घोषणा WM8962_GP2_POL_SHIFT                        10  /* GP2_POL */
#घोषणा WM8962_GP2_POL_WIDTH                         1  /* GP2_POL */
#घोषणा WM8962_GP2_LVL                          0x0040  /* GP2_LVL */
#घोषणा WM8962_GP2_LVL_MASK                     0x0040  /* GP2_LVL */
#घोषणा WM8962_GP2_LVL_SHIFT                         6  /* GP2_LVL */
#घोषणा WM8962_GP2_LVL_WIDTH                         1  /* GP2_LVL */
#घोषणा WM8962_GP2_FN_MASK                      0x001F  /* GP2_FN - [4:0] */
#घोषणा WM8962_GP2_FN_SHIFT                          0  /* GP2_FN - [4:0] */
#घोषणा WM8962_GP2_FN_WIDTH                          5  /* GP2_FN - [4:0] */

/*
 * R514 (0x202) - GPIO 3
 */
#घोषणा WM8962_GP3_POL                          0x0400  /* GP3_POL */
#घोषणा WM8962_GP3_POL_MASK                     0x0400  /* GP3_POL */
#घोषणा WM8962_GP3_POL_SHIFT                        10  /* GP3_POL */
#घोषणा WM8962_GP3_POL_WIDTH                         1  /* GP3_POL */
#घोषणा WM8962_GP3_LVL                          0x0040  /* GP3_LVL */
#घोषणा WM8962_GP3_LVL_MASK                     0x0040  /* GP3_LVL */
#घोषणा WM8962_GP3_LVL_SHIFT                         6  /* GP3_LVL */
#घोषणा WM8962_GP3_LVL_WIDTH                         1  /* GP3_LVL */
#घोषणा WM8962_GP3_FN_MASK                      0x001F  /* GP3_FN - [4:0] */
#घोषणा WM8962_GP3_FN_SHIFT                          0  /* GP3_FN - [4:0] */
#घोषणा WM8962_GP3_FN_WIDTH                          5  /* GP3_FN - [4:0] */

/*
 * R516 (0x204) - GPIO 5
 */
#घोषणा WM8962_GP5_सूची                          0x8000  /* GP5_सूची */
#घोषणा WM8962_GP5_सूची_MASK                     0x8000  /* GP5_सूची */
#घोषणा WM8962_GP5_सूची_SHIFT                        15  /* GP5_सूची */
#घोषणा WM8962_GP5_सूची_WIDTH                         1  /* GP5_सूची */
#घोषणा WM8962_GP5_PU                           0x4000  /* GP5_PU */
#घोषणा WM8962_GP5_PU_MASK                      0x4000  /* GP5_PU */
#घोषणा WM8962_GP5_PU_SHIFT                         14  /* GP5_PU */
#घोषणा WM8962_GP5_PU_WIDTH                          1  /* GP5_PU */
#घोषणा WM8962_GP5_PD                           0x2000  /* GP5_PD */
#घोषणा WM8962_GP5_PD_MASK                      0x2000  /* GP5_PD */
#घोषणा WM8962_GP5_PD_SHIFT                         13  /* GP5_PD */
#घोषणा WM8962_GP5_PD_WIDTH                          1  /* GP5_PD */
#घोषणा WM8962_GP5_POL                          0x0400  /* GP5_POL */
#घोषणा WM8962_GP5_POL_MASK                     0x0400  /* GP5_POL */
#घोषणा WM8962_GP5_POL_SHIFT                        10  /* GP5_POL */
#घोषणा WM8962_GP5_POL_WIDTH                         1  /* GP5_POL */
#घोषणा WM8962_GP5_OP_CFG                       0x0200  /* GP5_OP_CFG */
#घोषणा WM8962_GP5_OP_CFG_MASK                  0x0200  /* GP5_OP_CFG */
#घोषणा WM8962_GP5_OP_CFG_SHIFT                      9  /* GP5_OP_CFG */
#घोषणा WM8962_GP5_OP_CFG_WIDTH                      1  /* GP5_OP_CFG */
#घोषणा WM8962_GP5_DB                           0x0100  /* GP5_DB */
#घोषणा WM8962_GP5_DB_MASK                      0x0100  /* GP5_DB */
#घोषणा WM8962_GP5_DB_SHIFT                          8  /* GP5_DB */
#घोषणा WM8962_GP5_DB_WIDTH                          1  /* GP5_DB */
#घोषणा WM8962_GP5_LVL                          0x0040  /* GP5_LVL */
#घोषणा WM8962_GP5_LVL_MASK                     0x0040  /* GP5_LVL */
#घोषणा WM8962_GP5_LVL_SHIFT                         6  /* GP5_LVL */
#घोषणा WM8962_GP5_LVL_WIDTH                         1  /* GP5_LVL */
#घोषणा WM8962_GP5_FN_MASK                      0x001F  /* GP5_FN - [4:0] */
#घोषणा WM8962_GP5_FN_SHIFT                          0  /* GP5_FN - [4:0] */
#घोषणा WM8962_GP5_FN_WIDTH                          5  /* GP5_FN - [4:0] */

/*
 * R517 (0x205) - GPIO 6
 */
#घोषणा WM8962_GP6_सूची                          0x8000  /* GP6_सूची */
#घोषणा WM8962_GP6_सूची_MASK                     0x8000  /* GP6_सूची */
#घोषणा WM8962_GP6_सूची_SHIFT                        15  /* GP6_सूची */
#घोषणा WM8962_GP6_सूची_WIDTH                         1  /* GP6_सूची */
#घोषणा WM8962_GP6_PU                           0x4000  /* GP6_PU */
#घोषणा WM8962_GP6_PU_MASK                      0x4000  /* GP6_PU */
#घोषणा WM8962_GP6_PU_SHIFT                         14  /* GP6_PU */
#घोषणा WM8962_GP6_PU_WIDTH                          1  /* GP6_PU */
#घोषणा WM8962_GP6_PD                           0x2000  /* GP6_PD */
#घोषणा WM8962_GP6_PD_MASK                      0x2000  /* GP6_PD */
#घोषणा WM8962_GP6_PD_SHIFT                         13  /* GP6_PD */
#घोषणा WM8962_GP6_PD_WIDTH                          1  /* GP6_PD */
#घोषणा WM8962_GP6_POL                          0x0400  /* GP6_POL */
#घोषणा WM8962_GP6_POL_MASK                     0x0400  /* GP6_POL */
#घोषणा WM8962_GP6_POL_SHIFT                        10  /* GP6_POL */
#घोषणा WM8962_GP6_POL_WIDTH                         1  /* GP6_POL */
#घोषणा WM8962_GP6_OP_CFG                       0x0200  /* GP6_OP_CFG */
#घोषणा WM8962_GP6_OP_CFG_MASK                  0x0200  /* GP6_OP_CFG */
#घोषणा WM8962_GP6_OP_CFG_SHIFT                      9  /* GP6_OP_CFG */
#घोषणा WM8962_GP6_OP_CFG_WIDTH                      1  /* GP6_OP_CFG */
#घोषणा WM8962_GP6_DB                           0x0100  /* GP6_DB */
#घोषणा WM8962_GP6_DB_MASK                      0x0100  /* GP6_DB */
#घोषणा WM8962_GP6_DB_SHIFT                          8  /* GP6_DB */
#घोषणा WM8962_GP6_DB_WIDTH                          1  /* GP6_DB */
#घोषणा WM8962_GP6_LVL                          0x0040  /* GP6_LVL */
#घोषणा WM8962_GP6_LVL_MASK                     0x0040  /* GP6_LVL */
#घोषणा WM8962_GP6_LVL_SHIFT                         6  /* GP6_LVL */
#घोषणा WM8962_GP6_LVL_WIDTH                         1  /* GP6_LVL */
#घोषणा WM8962_GP6_FN_MASK                      0x001F  /* GP6_FN - [4:0] */
#घोषणा WM8962_GP6_FN_SHIFT                          0  /* GP6_FN - [4:0] */
#घोषणा WM8962_GP6_FN_WIDTH                          5  /* GP6_FN - [4:0] */

/*
 * R560 (0x230) - Interrupt Status 1
 */
#घोषणा WM8962_GP6_EINT                         0x0020  /* GP6_EINT */
#घोषणा WM8962_GP6_EINT_MASK                    0x0020  /* GP6_EINT */
#घोषणा WM8962_GP6_EINT_SHIFT                        5  /* GP6_EINT */
#घोषणा WM8962_GP6_EINT_WIDTH                        1  /* GP6_EINT */
#घोषणा WM8962_GP5_EINT                         0x0010  /* GP5_EINT */
#घोषणा WM8962_GP5_EINT_MASK                    0x0010  /* GP5_EINT */
#घोषणा WM8962_GP5_EINT_SHIFT                        4  /* GP5_EINT */
#घोषणा WM8962_GP5_EINT_WIDTH                        1  /* GP5_EINT */

/*
 * R561 (0x231) - Interrupt Status 2
 */
#घोषणा WM8962_MICSCD_EINT                      0x8000  /* MICSCD_EINT */
#घोषणा WM8962_MICSCD_EINT_MASK                 0x8000  /* MICSCD_EINT */
#घोषणा WM8962_MICSCD_EINT_SHIFT                    15  /* MICSCD_EINT */
#घोषणा WM8962_MICSCD_EINT_WIDTH                     1  /* MICSCD_EINT */
#घोषणा WM8962_MICD_EINT                        0x4000  /* MICD_EINT */
#घोषणा WM8962_MICD_EINT_MASK                   0x4000  /* MICD_EINT */
#घोषणा WM8962_MICD_EINT_SHIFT                      14  /* MICD_EINT */
#घोषणा WM8962_MICD_EINT_WIDTH                       1  /* MICD_EINT */
#घोषणा WM8962_FIFOS_ERR_EINT                   0x2000  /* FIFOS_ERR_EINT */
#घोषणा WM8962_FIFOS_ERR_EINT_MASK              0x2000  /* FIFOS_ERR_EINT */
#घोषणा WM8962_FIFOS_ERR_EINT_SHIFT                 13  /* FIFOS_ERR_EINT */
#घोषणा WM8962_FIFOS_ERR_EINT_WIDTH                  1  /* FIFOS_ERR_EINT */
#घोषणा WM8962_ALC_LOCK_EINT                    0x1000  /* ALC_LOCK_EINT */
#घोषणा WM8962_ALC_LOCK_EINT_MASK               0x1000  /* ALC_LOCK_EINT */
#घोषणा WM8962_ALC_LOCK_EINT_SHIFT                  12  /* ALC_LOCK_EINT */
#घोषणा WM8962_ALC_LOCK_EINT_WIDTH                   1  /* ALC_LOCK_EINT */
#घोषणा WM8962_ALC_THRESH_EINT                  0x0800  /* ALC_THRESH_EINT */
#घोषणा WM8962_ALC_THRESH_EINT_MASK             0x0800  /* ALC_THRESH_EINT */
#घोषणा WM8962_ALC_THRESH_EINT_SHIFT                11  /* ALC_THRESH_EINT */
#घोषणा WM8962_ALC_THRESH_EINT_WIDTH                 1  /* ALC_THRESH_EINT */
#घोषणा WM8962_ALC_SAT_EINT                     0x0400  /* ALC_SAT_EINT */
#घोषणा WM8962_ALC_SAT_EINT_MASK                0x0400  /* ALC_SAT_EINT */
#घोषणा WM8962_ALC_SAT_EINT_SHIFT                   10  /* ALC_SAT_EINT */
#घोषणा WM8962_ALC_SAT_EINT_WIDTH                    1  /* ALC_SAT_EINT */
#घोषणा WM8962_ALC_PKOVR_EINT                   0x0200  /* ALC_PKOVR_EINT */
#घोषणा WM8962_ALC_PKOVR_EINT_MASK              0x0200  /* ALC_PKOVR_EINT */
#घोषणा WM8962_ALC_PKOVR_EINT_SHIFT                  9  /* ALC_PKOVR_EINT */
#घोषणा WM8962_ALC_PKOVR_EINT_WIDTH                  1  /* ALC_PKOVR_EINT */
#घोषणा WM8962_ALC_NGATE_EINT                   0x0100  /* ALC_NGATE_EINT */
#घोषणा WM8962_ALC_NGATE_EINT_MASK              0x0100  /* ALC_NGATE_EINT */
#घोषणा WM8962_ALC_NGATE_EINT_SHIFT                  8  /* ALC_NGATE_EINT */
#घोषणा WM8962_ALC_NGATE_EINT_WIDTH                  1  /* ALC_NGATE_EINT */
#घोषणा WM8962_WSEQ_DONE_EINT                   0x0080  /* WSEQ_DONE_EINT */
#घोषणा WM8962_WSEQ_DONE_EINT_MASK              0x0080  /* WSEQ_DONE_EINT */
#घोषणा WM8962_WSEQ_DONE_EINT_SHIFT                  7  /* WSEQ_DONE_EINT */
#घोषणा WM8962_WSEQ_DONE_EINT_WIDTH                  1  /* WSEQ_DONE_EINT */
#घोषणा WM8962_DRC_ACTDET_EINT                  0x0040  /* DRC_ACTDET_EINT */
#घोषणा WM8962_DRC_ACTDET_EINT_MASK             0x0040  /* DRC_ACTDET_EINT */
#घोषणा WM8962_DRC_ACTDET_EINT_SHIFT                 6  /* DRC_ACTDET_EINT */
#घोषणा WM8962_DRC_ACTDET_EINT_WIDTH                 1  /* DRC_ACTDET_EINT */
#घोषणा WM8962_FLL_LOCK_EINT                    0x0020  /* FLL_LOCK_EINT */
#घोषणा WM8962_FLL_LOCK_EINT_MASK               0x0020  /* FLL_LOCK_EINT */
#घोषणा WM8962_FLL_LOCK_EINT_SHIFT                   5  /* FLL_LOCK_EINT */
#घोषणा WM8962_FLL_LOCK_EINT_WIDTH                   1  /* FLL_LOCK_EINT */
#घोषणा WM8962_PLL3_LOCK_EINT                   0x0008  /* PLL3_LOCK_EINT */
#घोषणा WM8962_PLL3_LOCK_EINT_MASK              0x0008  /* PLL3_LOCK_EINT */
#घोषणा WM8962_PLL3_LOCK_EINT_SHIFT                  3  /* PLL3_LOCK_EINT */
#घोषणा WM8962_PLL3_LOCK_EINT_WIDTH                  1  /* PLL3_LOCK_EINT */
#घोषणा WM8962_PLL2_LOCK_EINT                   0x0004  /* PLL2_LOCK_EINT */
#घोषणा WM8962_PLL2_LOCK_EINT_MASK              0x0004  /* PLL2_LOCK_EINT */
#घोषणा WM8962_PLL2_LOCK_EINT_SHIFT                  2  /* PLL2_LOCK_EINT */
#घोषणा WM8962_PLL2_LOCK_EINT_WIDTH                  1  /* PLL2_LOCK_EINT */
#घोषणा WM8962_TEMP_SHUT_EINT                   0x0001  /* TEMP_SHUT_EINT */
#घोषणा WM8962_TEMP_SHUT_EINT_MASK              0x0001  /* TEMP_SHUT_EINT */
#घोषणा WM8962_TEMP_SHUT_EINT_SHIFT                  0  /* TEMP_SHUT_EINT */
#घोषणा WM8962_TEMP_SHUT_EINT_WIDTH                  1  /* TEMP_SHUT_EINT */

/*
 * R568 (0x238) - Interrupt Status 1 Mask
 */
#घोषणा WM8962_IM_GP6_EINT                      0x0020  /* IM_GP6_EINT */
#घोषणा WM8962_IM_GP6_EINT_MASK                 0x0020  /* IM_GP6_EINT */
#घोषणा WM8962_IM_GP6_EINT_SHIFT                     5  /* IM_GP6_EINT */
#घोषणा WM8962_IM_GP6_EINT_WIDTH                     1  /* IM_GP6_EINT */
#घोषणा WM8962_IM_GP5_EINT                      0x0010  /* IM_GP5_EINT */
#घोषणा WM8962_IM_GP5_EINT_MASK                 0x0010  /* IM_GP5_EINT */
#घोषणा WM8962_IM_GP5_EINT_SHIFT                     4  /* IM_GP5_EINT */
#घोषणा WM8962_IM_GP5_EINT_WIDTH                     1  /* IM_GP5_EINT */

/*
 * R569 (0x239) - Interrupt Status 2 Mask
 */
#घोषणा WM8962_IM_MICSCD_EINT                   0x8000  /* IM_MICSCD_EINT */
#घोषणा WM8962_IM_MICSCD_EINT_MASK              0x8000  /* IM_MICSCD_EINT */
#घोषणा WM8962_IM_MICSCD_EINT_SHIFT                 15  /* IM_MICSCD_EINT */
#घोषणा WM8962_IM_MICSCD_EINT_WIDTH                  1  /* IM_MICSCD_EINT */
#घोषणा WM8962_IM_MICD_EINT                     0x4000  /* IM_MICD_EINT */
#घोषणा WM8962_IM_MICD_EINT_MASK                0x4000  /* IM_MICD_EINT */
#घोषणा WM8962_IM_MICD_EINT_SHIFT                   14  /* IM_MICD_EINT */
#घोषणा WM8962_IM_MICD_EINT_WIDTH                    1  /* IM_MICD_EINT */
#घोषणा WM8962_IM_FIFOS_ERR_EINT                0x2000  /* IM_FIFOS_ERR_EINT */
#घोषणा WM8962_IM_FIFOS_ERR_EINT_MASK           0x2000  /* IM_FIFOS_ERR_EINT */
#घोषणा WM8962_IM_FIFOS_ERR_EINT_SHIFT              13  /* IM_FIFOS_ERR_EINT */
#घोषणा WM8962_IM_FIFOS_ERR_EINT_WIDTH               1  /* IM_FIFOS_ERR_EINT */
#घोषणा WM8962_IM_ALC_LOCK_EINT                 0x1000  /* IM_ALC_LOCK_EINT */
#घोषणा WM8962_IM_ALC_LOCK_EINT_MASK            0x1000  /* IM_ALC_LOCK_EINT */
#घोषणा WM8962_IM_ALC_LOCK_EINT_SHIFT               12  /* IM_ALC_LOCK_EINT */
#घोषणा WM8962_IM_ALC_LOCK_EINT_WIDTH                1  /* IM_ALC_LOCK_EINT */
#घोषणा WM8962_IM_ALC_THRESH_EINT               0x0800  /* IM_ALC_THRESH_EINT */
#घोषणा WM8962_IM_ALC_THRESH_EINT_MASK          0x0800  /* IM_ALC_THRESH_EINT */
#घोषणा WM8962_IM_ALC_THRESH_EINT_SHIFT             11  /* IM_ALC_THRESH_EINT */
#घोषणा WM8962_IM_ALC_THRESH_EINT_WIDTH              1  /* IM_ALC_THRESH_EINT */
#घोषणा WM8962_IM_ALC_SAT_EINT                  0x0400  /* IM_ALC_SAT_EINT */
#घोषणा WM8962_IM_ALC_SAT_EINT_MASK             0x0400  /* IM_ALC_SAT_EINT */
#घोषणा WM8962_IM_ALC_SAT_EINT_SHIFT                10  /* IM_ALC_SAT_EINT */
#घोषणा WM8962_IM_ALC_SAT_EINT_WIDTH                 1  /* IM_ALC_SAT_EINT */
#घोषणा WM8962_IM_ALC_PKOVR_EINT                0x0200  /* IM_ALC_PKOVR_EINT */
#घोषणा WM8962_IM_ALC_PKOVR_EINT_MASK           0x0200  /* IM_ALC_PKOVR_EINT */
#घोषणा WM8962_IM_ALC_PKOVR_EINT_SHIFT               9  /* IM_ALC_PKOVR_EINT */
#घोषणा WM8962_IM_ALC_PKOVR_EINT_WIDTH               1  /* IM_ALC_PKOVR_EINT */
#घोषणा WM8962_IM_ALC_NGATE_EINT                0x0100  /* IM_ALC_NGATE_EINT */
#घोषणा WM8962_IM_ALC_NGATE_EINT_MASK           0x0100  /* IM_ALC_NGATE_EINT */
#घोषणा WM8962_IM_ALC_NGATE_EINT_SHIFT               8  /* IM_ALC_NGATE_EINT */
#घोषणा WM8962_IM_ALC_NGATE_EINT_WIDTH               1  /* IM_ALC_NGATE_EINT */
#घोषणा WM8962_IM_WSEQ_DONE_EINT                0x0080  /* IM_WSEQ_DONE_EINT */
#घोषणा WM8962_IM_WSEQ_DONE_EINT_MASK           0x0080  /* IM_WSEQ_DONE_EINT */
#घोषणा WM8962_IM_WSEQ_DONE_EINT_SHIFT               7  /* IM_WSEQ_DONE_EINT */
#घोषणा WM8962_IM_WSEQ_DONE_EINT_WIDTH               1  /* IM_WSEQ_DONE_EINT */
#घोषणा WM8962_IM_DRC_ACTDET_EINT               0x0040  /* IM_DRC_ACTDET_EINT */
#घोषणा WM8962_IM_DRC_ACTDET_EINT_MASK          0x0040  /* IM_DRC_ACTDET_EINT */
#घोषणा WM8962_IM_DRC_ACTDET_EINT_SHIFT              6  /* IM_DRC_ACTDET_EINT */
#घोषणा WM8962_IM_DRC_ACTDET_EINT_WIDTH              1  /* IM_DRC_ACTDET_EINT */
#घोषणा WM8962_IM_FLL_LOCK_EINT                 0x0020  /* IM_FLL_LOCK_EINT */
#घोषणा WM8962_IM_FLL_LOCK_EINT_MASK            0x0020  /* IM_FLL_LOCK_EINT */
#घोषणा WM8962_IM_FLL_LOCK_EINT_SHIFT                5  /* IM_FLL_LOCK_EINT */
#घोषणा WM8962_IM_FLL_LOCK_EINT_WIDTH                1  /* IM_FLL_LOCK_EINT */
#घोषणा WM8962_IM_PLL3_LOCK_EINT                0x0008  /* IM_PLL3_LOCK_EINT */
#घोषणा WM8962_IM_PLL3_LOCK_EINT_MASK           0x0008  /* IM_PLL3_LOCK_EINT */
#घोषणा WM8962_IM_PLL3_LOCK_EINT_SHIFT               3  /* IM_PLL3_LOCK_EINT */
#घोषणा WM8962_IM_PLL3_LOCK_EINT_WIDTH               1  /* IM_PLL3_LOCK_EINT */
#घोषणा WM8962_IM_PLL2_LOCK_EINT                0x0004  /* IM_PLL2_LOCK_EINT */
#घोषणा WM8962_IM_PLL2_LOCK_EINT_MASK           0x0004  /* IM_PLL2_LOCK_EINT */
#घोषणा WM8962_IM_PLL2_LOCK_EINT_SHIFT               2  /* IM_PLL2_LOCK_EINT */
#घोषणा WM8962_IM_PLL2_LOCK_EINT_WIDTH               1  /* IM_PLL2_LOCK_EINT */
#घोषणा WM8962_IM_TEMP_SHUT_EINT                0x0001  /* IM_TEMP_SHUT_EINT */
#घोषणा WM8962_IM_TEMP_SHUT_EINT_MASK           0x0001  /* IM_TEMP_SHUT_EINT */
#घोषणा WM8962_IM_TEMP_SHUT_EINT_SHIFT               0  /* IM_TEMP_SHUT_EINT */
#घोषणा WM8962_IM_TEMP_SHUT_EINT_WIDTH               1  /* IM_TEMP_SHUT_EINT */

/*
 * R576 (0x240) - Interrupt Control
 */
#घोषणा WM8962_IRQ_POL                          0x0001  /* IRQ_POL */
#घोषणा WM8962_IRQ_POL_MASK                     0x0001  /* IRQ_POL */
#घोषणा WM8962_IRQ_POL_SHIFT                         0  /* IRQ_POL */
#घोषणा WM8962_IRQ_POL_WIDTH                         1  /* IRQ_POL */

/*
 * R584 (0x248) - IRQ Debounce
 */
#घोषणा WM8962_FLL_LOCK_DB                      0x0020  /* FLL_LOCK_DB */
#घोषणा WM8962_FLL_LOCK_DB_MASK                 0x0020  /* FLL_LOCK_DB */
#घोषणा WM8962_FLL_LOCK_DB_SHIFT                     5  /* FLL_LOCK_DB */
#घोषणा WM8962_FLL_LOCK_DB_WIDTH                     1  /* FLL_LOCK_DB */
#घोषणा WM8962_PLL3_LOCK_DB                     0x0008  /* PLL3_LOCK_DB */
#घोषणा WM8962_PLL3_LOCK_DB_MASK                0x0008  /* PLL3_LOCK_DB */
#घोषणा WM8962_PLL3_LOCK_DB_SHIFT                    3  /* PLL3_LOCK_DB */
#घोषणा WM8962_PLL3_LOCK_DB_WIDTH                    1  /* PLL3_LOCK_DB */
#घोषणा WM8962_PLL2_LOCK_DB                     0x0004  /* PLL2_LOCK_DB */
#घोषणा WM8962_PLL2_LOCK_DB_MASK                0x0004  /* PLL2_LOCK_DB */
#घोषणा WM8962_PLL2_LOCK_DB_SHIFT                    2  /* PLL2_LOCK_DB */
#घोषणा WM8962_PLL2_LOCK_DB_WIDTH                    1  /* PLL2_LOCK_DB */
#घोषणा WM8962_TEMP_SHUT_DB                     0x0001  /* TEMP_SHUT_DB */
#घोषणा WM8962_TEMP_SHUT_DB_MASK                0x0001  /* TEMP_SHUT_DB */
#घोषणा WM8962_TEMP_SHUT_DB_SHIFT                    0  /* TEMP_SHUT_DB */
#घोषणा WM8962_TEMP_SHUT_DB_WIDTH                    1  /* TEMP_SHUT_DB */

/*
 * R586 (0x24A) -  MICINT Source Pol
 */
#घोषणा WM8962_MICSCD_IRQ_POL                   0x8000  /* MICSCD_IRQ_POL */
#घोषणा WM8962_MICSCD_IRQ_POL_MASK              0x8000  /* MICSCD_IRQ_POL */
#घोषणा WM8962_MICSCD_IRQ_POL_SHIFT                 15  /* MICSCD_IRQ_POL */
#घोषणा WM8962_MICSCD_IRQ_POL_WIDTH                  1  /* MICSCD_IRQ_POL */
#घोषणा WM8962_MICD_IRQ_POL                     0x4000  /* MICD_IRQ_POL */
#घोषणा WM8962_MICD_IRQ_POL_MASK                0x4000  /* MICD_IRQ_POL */
#घोषणा WM8962_MICD_IRQ_POL_SHIFT                   14  /* MICD_IRQ_POL */
#घोषणा WM8962_MICD_IRQ_POL_WIDTH                    1  /* MICD_IRQ_POL */

/*
 * R768 (0x300) - DSP2 Power Management
 */
#घोषणा WM8962_DSP2_ENA                         0x0001  /* DSP2_ENA */
#घोषणा WM8962_DSP2_ENA_MASK                    0x0001  /* DSP2_ENA */
#घोषणा WM8962_DSP2_ENA_SHIFT                        0  /* DSP2_ENA */
#घोषणा WM8962_DSP2_ENA_WIDTH                        1  /* DSP2_ENA */

/*
 * R1037 (0x40D) - DSP2_ExecControl
 */
#घोषणा WM8962_DSP2_STOPC                       0x0020  /* DSP2_STOPC */
#घोषणा WM8962_DSP2_STOPC_MASK                  0x0020  /* DSP2_STOPC */
#घोषणा WM8962_DSP2_STOPC_SHIFT                      5  /* DSP2_STOPC */
#घोषणा WM8962_DSP2_STOPC_WIDTH                      1  /* DSP2_STOPC */
#घोषणा WM8962_DSP2_STOPS                       0x0010  /* DSP2_STOPS */
#घोषणा WM8962_DSP2_STOPS_MASK                  0x0010  /* DSP2_STOPS */
#घोषणा WM8962_DSP2_STOPS_SHIFT                      4  /* DSP2_STOPS */
#घोषणा WM8962_DSP2_STOPS_WIDTH                      1  /* DSP2_STOPS */
#घोषणा WM8962_DSP2_STOPI                       0x0008  /* DSP2_STOPI */
#घोषणा WM8962_DSP2_STOPI_MASK                  0x0008  /* DSP2_STOPI */
#घोषणा WM8962_DSP2_STOPI_SHIFT                      3  /* DSP2_STOPI */
#घोषणा WM8962_DSP2_STOPI_WIDTH                      1  /* DSP2_STOPI */
#घोषणा WM8962_DSP2_STOP                        0x0004  /* DSP2_STOP */
#घोषणा WM8962_DSP2_STOP_MASK                   0x0004  /* DSP2_STOP */
#घोषणा WM8962_DSP2_STOP_SHIFT                       2  /* DSP2_STOP */
#घोषणा WM8962_DSP2_STOP_WIDTH                       1  /* DSP2_STOP */
#घोषणा WM8962_DSP2_RUNR                        0x0002  /* DSP2_RUNR */
#घोषणा WM8962_DSP2_RUNR_MASK                   0x0002  /* DSP2_RUNR */
#घोषणा WM8962_DSP2_RUNR_SHIFT                       1  /* DSP2_RUNR */
#घोषणा WM8962_DSP2_RUNR_WIDTH                       1  /* DSP2_RUNR */
#घोषणा WM8962_DSP2_RUN                         0x0001  /* DSP2_RUN */
#घोषणा WM8962_DSP2_RUN_MASK                    0x0001  /* DSP2_RUN */
#घोषणा WM8962_DSP2_RUN_SHIFT                        0  /* DSP2_RUN */
#घोषणा WM8962_DSP2_RUN_WIDTH                        1  /* DSP2_RUN */

/*
 * R8192 (0x2000) - DSP2 Inकाष्ठाion RAM 0
 */
#घोषणा WM8962_DSP2_INSTR_RAM_1024_10_9_0_MASK  0x03FF  /* DSP2_INSTR_RAM_1024_10_9_0 - [9:0] */
#घोषणा WM8962_DSP2_INSTR_RAM_1024_10_9_0_SHIFT      0  /* DSP2_INSTR_RAM_1024_10_9_0 - [9:0] */
#घोषणा WM8962_DSP2_INSTR_RAM_1024_10_9_0_WIDTH     10  /* DSP2_INSTR_RAM_1024_10_9_0 - [9:0] */

/*
 * R9216 (0x2400) - DSP2 Address RAM 2
 */
#घोषणा WM8962_DSP2_ADDR_RAM_1024_38_37_32_MASK 0x003F  /* DSP2_ADDR_RAM_1024_38_37_32 - [5:0] */
#घोषणा WM8962_DSP2_ADDR_RAM_1024_38_37_32_SHIFT      0  /* DSP2_ADDR_RAM_1024_38_37_32 - [5:0] */
#घोषणा WM8962_DSP2_ADDR_RAM_1024_38_37_32_WIDTH      6  /* DSP2_ADDR_RAM_1024_38_37_32 - [5:0] */

/*
 * R9217 (0x2401) - DSP2 Address RAM 1
 */
#घोषणा WM8962_DSP2_ADDR_RAM_1024_38_31_16_MASK 0xFFFF  /* DSP2_ADDR_RAM_1024_38_31_16 - [15:0] */
#घोषणा WM8962_DSP2_ADDR_RAM_1024_38_31_16_SHIFT      0  /* DSP2_ADDR_RAM_1024_38_31_16 - [15:0] */
#घोषणा WM8962_DSP2_ADDR_RAM_1024_38_31_16_WIDTH     16  /* DSP2_ADDR_RAM_1024_38_31_16 - [15:0] */

/*
 * R9218 (0x2402) - DSP2 Address RAM 0
 */
#घोषणा WM8962_DSP2_ADDR_RAM_1024_38_15_0_MASK  0xFFFF  /* DSP2_ADDR_RAM_1024_38_15_0 - [15:0] */
#घोषणा WM8962_DSP2_ADDR_RAM_1024_38_15_0_SHIFT      0  /* DSP2_ADDR_RAM_1024_38_15_0 - [15:0] */
#घोषणा WM8962_DSP2_ADDR_RAM_1024_38_15_0_WIDTH     16  /* DSP2_ADDR_RAM_1024_38_15_0 - [15:0] */

/*
 * R12288 (0x3000) - DSP2 Data1 RAM 1
 */
#घोषणा WM8962_DSP2_DATA1_RAM_384_24_23_16_MASK 0x00FF  /* DSP2_DATA1_RAM_384_24_23_16 - [7:0] */
#घोषणा WM8962_DSP2_DATA1_RAM_384_24_23_16_SHIFT      0  /* DSP2_DATA1_RAM_384_24_23_16 - [7:0] */
#घोषणा WM8962_DSP2_DATA1_RAM_384_24_23_16_WIDTH      8  /* DSP2_DATA1_RAM_384_24_23_16 - [7:0] */

/*
 * R12289 (0x3001) - DSP2 Data1 RAM 0
 */
#घोषणा WM8962_DSP2_DATA1_RAM_384_24_15_0_MASK  0xFFFF  /* DSP2_DATA1_RAM_384_24_15_0 - [15:0] */
#घोषणा WM8962_DSP2_DATA1_RAM_384_24_15_0_SHIFT      0  /* DSP2_DATA1_RAM_384_24_15_0 - [15:0] */
#घोषणा WM8962_DSP2_DATA1_RAM_384_24_15_0_WIDTH     16  /* DSP2_DATA1_RAM_384_24_15_0 - [15:0] */

/*
 * R13312 (0x3400) - DSP2 Data2 RAM 1
 */
#घोषणा WM8962_DSP2_DATA2_RAM_384_24_23_16_MASK 0x00FF  /* DSP2_DATA2_RAM_384_24_23_16 - [7:0] */
#घोषणा WM8962_DSP2_DATA2_RAM_384_24_23_16_SHIFT      0  /* DSP2_DATA2_RAM_384_24_23_16 - [7:0] */
#घोषणा WM8962_DSP2_DATA2_RAM_384_24_23_16_WIDTH      8  /* DSP2_DATA2_RAM_384_24_23_16 - [7:0] */

/*
 * R13313 (0x3401) - DSP2 Data2 RAM 0
 */
#घोषणा WM8962_DSP2_DATA2_RAM_384_24_15_0_MASK  0xFFFF  /* DSP2_DATA2_RAM_384_24_15_0 - [15:0] */
#घोषणा WM8962_DSP2_DATA2_RAM_384_24_15_0_SHIFT      0  /* DSP2_DATA2_RAM_384_24_15_0 - [15:0] */
#घोषणा WM8962_DSP2_DATA2_RAM_384_24_15_0_WIDTH     16  /* DSP2_DATA2_RAM_384_24_15_0 - [15:0] */

/*
 * R14336 (0x3800) - DSP2 Data3 RAM 1
 */
#घोषणा WM8962_DSP2_DATA3_RAM_384_24_23_16_MASK 0x00FF  /* DSP2_DATA3_RAM_384_24_23_16 - [7:0] */
#घोषणा WM8962_DSP2_DATA3_RAM_384_24_23_16_SHIFT      0  /* DSP2_DATA3_RAM_384_24_23_16 - [7:0] */
#घोषणा WM8962_DSP2_DATA3_RAM_384_24_23_16_WIDTH      8  /* DSP2_DATA3_RAM_384_24_23_16 - [7:0] */

/*
 * R14337 (0x3801) - DSP2 Data3 RAM 0
 */
#घोषणा WM8962_DSP2_DATA3_RAM_384_24_15_0_MASK  0xFFFF  /* DSP2_DATA3_RAM_384_24_15_0 - [15:0] */
#घोषणा WM8962_DSP2_DATA3_RAM_384_24_15_0_SHIFT      0  /* DSP2_DATA3_RAM_384_24_15_0 - [15:0] */
#घोषणा WM8962_DSP2_DATA3_RAM_384_24_15_0_WIDTH     16  /* DSP2_DATA3_RAM_384_24_15_0 - [15:0] */

/*
 * R15360 (0x3C00) - DSP2 Coeff RAM 0
 */
#घोषणा WM8962_DSP2_CMAP_RAM_384_11_10_0_MASK   0x07FF  /* DSP2_CMAP_RAM_384_11_10_0 - [10:0] */
#घोषणा WM8962_DSP2_CMAP_RAM_384_11_10_0_SHIFT       0  /* DSP2_CMAP_RAM_384_11_10_0 - [10:0] */
#घोषणा WM8962_DSP2_CMAP_RAM_384_11_10_0_WIDTH      11  /* DSP2_CMAP_RAM_384_11_10_0 - [10:0] */

/*
 * R16384 (0x4000) - RETUNEADC_SHARED_COEFF_1
 */
#घोषणा WM8962_ADC_RETUNE_SCV                   0x0080  /* ADC_RETUNE_SCV */
#घोषणा WM8962_ADC_RETUNE_SCV_MASK              0x0080  /* ADC_RETUNE_SCV */
#घोषणा WM8962_ADC_RETUNE_SCV_SHIFT                  7  /* ADC_RETUNE_SCV */
#घोषणा WM8962_ADC_RETUNE_SCV_WIDTH                  1  /* ADC_RETUNE_SCV */
#घोषणा WM8962_RETUNEADC_SHARED_COEFF_22_16_MASK 0x007F  /* RETUNEADC_SHARED_COEFF_22_16 - [6:0] */
#घोषणा WM8962_RETUNEADC_SHARED_COEFF_22_16_SHIFT      0  /* RETUNEADC_SHARED_COEFF_22_16 - [6:0] */
#घोषणा WM8962_RETUNEADC_SHARED_COEFF_22_16_WIDTH      7  /* RETUNEADC_SHARED_COEFF_22_16 - [6:0] */

/*
 * R16385 (0x4001) - RETUNEADC_SHARED_COEFF_0
 */
#घोषणा WM8962_RETUNEADC_SHARED_COEFF_15_00_MASK 0xFFFF  /* RETUNEADC_SHARED_COEFF_15_00 - [15:0] */
#घोषणा WM8962_RETUNEADC_SHARED_COEFF_15_00_SHIFT      0  /* RETUNEADC_SHARED_COEFF_15_00 - [15:0] */
#घोषणा WM8962_RETUNEADC_SHARED_COEFF_15_00_WIDTH     16  /* RETUNEADC_SHARED_COEFF_15_00 - [15:0] */

/*
 * R16386 (0x4002) - RETUNEDAC_SHARED_COEFF_1
 */
#घोषणा WM8962_DAC_RETUNE_SCV                   0x0080  /* DAC_RETUNE_SCV */
#घोषणा WM8962_DAC_RETUNE_SCV_MASK              0x0080  /* DAC_RETUNE_SCV */
#घोषणा WM8962_DAC_RETUNE_SCV_SHIFT                  7  /* DAC_RETUNE_SCV */
#घोषणा WM8962_DAC_RETUNE_SCV_WIDTH                  1  /* DAC_RETUNE_SCV */
#घोषणा WM8962_RETUNEDAC_SHARED_COEFF_23_16_MASK 0x007F  /* RETUNEDAC_SHARED_COEFF_23_16 - [6:0] */
#घोषणा WM8962_RETUNEDAC_SHARED_COEFF_23_16_SHIFT      0  /* RETUNEDAC_SHARED_COEFF_23_16 - [6:0] */
#घोषणा WM8962_RETUNEDAC_SHARED_COEFF_23_16_WIDTH      7  /* RETUNEDAC_SHARED_COEFF_23_16 - [6:0] */

/*
 * R16387 (0x4003) - RETUNEDAC_SHARED_COEFF_0
 */
#घोषणा WM8962_RETUNEDAC_SHARED_COEFF_15_00_MASK 0xFFFF  /* RETUNEDAC_SHARED_COEFF_15_00 - [15:0] */
#घोषणा WM8962_RETUNEDAC_SHARED_COEFF_15_00_SHIFT      0  /* RETUNEDAC_SHARED_COEFF_15_00 - [15:0] */
#घोषणा WM8962_RETUNEDAC_SHARED_COEFF_15_00_WIDTH     16  /* RETUNEDAC_SHARED_COEFF_15_00 - [15:0] */

/*
 * R16388 (0x4004) - SOUNDSTAGE_ENABLES_1
 */
#घोषणा WM8962_SOUNDSTAGE_ENABLES_23_16_MASK    0x00FF  /* SOUNDSTAGE_ENABLES_23_16 - [7:0] */
#घोषणा WM8962_SOUNDSTAGE_ENABLES_23_16_SHIFT        0  /* SOUNDSTAGE_ENABLES_23_16 - [7:0] */
#घोषणा WM8962_SOUNDSTAGE_ENABLES_23_16_WIDTH        8  /* SOUNDSTAGE_ENABLES_23_16 - [7:0] */

/*
 * R16389 (0x4005) - SOUNDSTAGE_ENABLES_0
 */
#घोषणा WM8962_SOUNDSTAGE_ENABLES_15_06_MASK    0xFFC0  /* SOUNDSTAGE_ENABLES_15_06 - [15:6] */
#घोषणा WM8962_SOUNDSTAGE_ENABLES_15_06_SHIFT        6  /* SOUNDSTAGE_ENABLES_15_06 - [15:6] */
#घोषणा WM8962_SOUNDSTAGE_ENABLES_15_06_WIDTH       10  /* SOUNDSTAGE_ENABLES_15_06 - [15:6] */
#घोषणा WM8962_RTN_ADC_ENA                      0x0020  /* RTN_ADC_ENA */
#घोषणा WM8962_RTN_ADC_ENA_MASK                 0x0020  /* RTN_ADC_ENA */
#घोषणा WM8962_RTN_ADC_ENA_SHIFT                     5  /* RTN_ADC_ENA */
#घोषणा WM8962_RTN_ADC_ENA_WIDTH                     1  /* RTN_ADC_ENA */
#घोषणा WM8962_RTN_DAC_ENA                      0x0010  /* RTN_DAC_ENA */
#घोषणा WM8962_RTN_DAC_ENA_MASK                 0x0010  /* RTN_DAC_ENA */
#घोषणा WM8962_RTN_DAC_ENA_SHIFT                     4  /* RTN_DAC_ENA */
#घोषणा WM8962_RTN_DAC_ENA_WIDTH                     1  /* RTN_DAC_ENA */
#घोषणा WM8962_HDBASS_ENA                       0x0008  /* HDBASS_ENA */
#घोषणा WM8962_HDBASS_ENA_MASK                  0x0008  /* HDBASS_ENA */
#घोषणा WM8962_HDBASS_ENA_SHIFT                      3  /* HDBASS_ENA */
#घोषणा WM8962_HDBASS_ENA_WIDTH                      1  /* HDBASS_ENA */
#घोषणा WM8962_HPF2_ENA                         0x0004  /* HPF2_ENA */
#घोषणा WM8962_HPF2_ENA_MASK                    0x0004  /* HPF2_ENA */
#घोषणा WM8962_HPF2_ENA_SHIFT                        2  /* HPF2_ENA */
#घोषणा WM8962_HPF2_ENA_WIDTH                        1  /* HPF2_ENA */
#घोषणा WM8962_HPF1_ENA                         0x0002  /* HPF1_ENA */
#घोषणा WM8962_HPF1_ENA_MASK                    0x0002  /* HPF1_ENA */
#घोषणा WM8962_HPF1_ENA_SHIFT                        1  /* HPF1_ENA */
#घोषणा WM8962_HPF1_ENA_WIDTH                        1  /* HPF1_ENA */
#घोषणा WM8962_VSS_ENA                          0x0001  /* VSS_ENA */
#घोषणा WM8962_VSS_ENA_MASK                     0x0001  /* VSS_ENA */
#घोषणा WM8962_VSS_ENA_SHIFT                         0  /* VSS_ENA */
#घोषणा WM8962_VSS_ENA_WIDTH                         1  /* VSS_ENA */

पूर्णांक wm8962_mic_detect(काष्ठा snd_soc_component *component, काष्ठा snd_soc_jack *jack);

#पूर्ण_अगर
