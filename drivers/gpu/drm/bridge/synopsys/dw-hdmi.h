<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright (C) 2011 Freescale Semiconductor, Inc.
 */

#अगर_अघोषित __DW_HDMI_H__
#घोषणा __DW_HDMI_H__

/* Identअगरication Registers */
#घोषणा HDMI_DESIGN_ID                          0x0000
#घोषणा HDMI_REVISION_ID                        0x0001
#घोषणा HDMI_PRODUCT_ID0                        0x0002
#घोषणा HDMI_PRODUCT_ID1                        0x0003
#घोषणा HDMI_CONFIG0_ID                         0x0004
#घोषणा HDMI_CONFIG1_ID                         0x0005
#घोषणा HDMI_CONFIG2_ID                         0x0006
#घोषणा HDMI_CONFIG3_ID                         0x0007

/* Interrupt Registers */
#घोषणा HDMI_IH_FC_STAT0                        0x0100
#घोषणा HDMI_IH_FC_STAT1                        0x0101
#घोषणा HDMI_IH_FC_STAT2                        0x0102
#घोषणा HDMI_IH_AS_STAT0                        0x0103
#घोषणा HDMI_IH_PHY_STAT0                       0x0104
#घोषणा HDMI_IH_I2CM_STAT0                      0x0105
#घोषणा HDMI_IH_CEC_STAT0                       0x0106
#घोषणा HDMI_IH_VP_STAT0                        0x0107
#घोषणा HDMI_IH_I2CMPHY_STAT0                   0x0108
#घोषणा HDMI_IH_AHBDMAAUD_STAT0                 0x0109

#घोषणा HDMI_IH_MUTE_FC_STAT0                   0x0180
#घोषणा HDMI_IH_MUTE_FC_STAT1                   0x0181
#घोषणा HDMI_IH_MUTE_FC_STAT2                   0x0182
#घोषणा HDMI_IH_MUTE_AS_STAT0                   0x0183
#घोषणा HDMI_IH_MUTE_PHY_STAT0                  0x0184
#घोषणा HDMI_IH_MUTE_I2CM_STAT0                 0x0185
#घोषणा HDMI_IH_MUTE_CEC_STAT0                  0x0186
#घोषणा HDMI_IH_MUTE_VP_STAT0                   0x0187
#घोषणा HDMI_IH_MUTE_I2CMPHY_STAT0              0x0188
#घोषणा HDMI_IH_MUTE_AHBDMAAUD_STAT0            0x0189
#घोषणा HDMI_IH_MUTE                            0x01FF

/* Video Sample Registers */
#घोषणा HDMI_TX_INVID0                          0x0200
#घोषणा HDMI_TX_INSTUFFING                      0x0201
#घोषणा HDMI_TX_GYDATA0                         0x0202
#घोषणा HDMI_TX_GYDATA1                         0x0203
#घोषणा HDMI_TX_RCRDATA0                        0x0204
#घोषणा HDMI_TX_RCRDATA1                        0x0205
#घोषणा HDMI_TX_BCBDATA0                        0x0206
#घोषणा HDMI_TX_BCBDATA1                        0x0207

/* Video Packetizer Registers */
#घोषणा HDMI_VP_STATUS                          0x0800
#घोषणा HDMI_VP_PR_CD                           0x0801
#घोषणा HDMI_VP_STUFF                           0x0802
#घोषणा HDMI_VP_REMAP                           0x0803
#घोषणा HDMI_VP_CONF                            0x0804
#घोषणा HDMI_VP_STAT                            0x0805
#घोषणा HDMI_VP_INT                             0x0806
#घोषणा HDMI_VP_MASK                            0x0807
#घोषणा HDMI_VP_POL                             0x0808

/* Frame Composer Registers */
#घोषणा HDMI_FC_INVIDCONF                       0x1000
#घोषणा HDMI_FC_INHACTV0                        0x1001
#घोषणा HDMI_FC_INHACTV1                        0x1002
#घोषणा HDMI_FC_INHBLANK0                       0x1003
#घोषणा HDMI_FC_INHBLANK1                       0x1004
#घोषणा HDMI_FC_INVACTV0                        0x1005
#घोषणा HDMI_FC_INVACTV1                        0x1006
#घोषणा HDMI_FC_INVBLANK                        0x1007
#घोषणा HDMI_FC_HSYNCINDELAY0                   0x1008
#घोषणा HDMI_FC_HSYNCINDELAY1                   0x1009
#घोषणा HDMI_FC_HSYNCINWIDTH0                   0x100A
#घोषणा HDMI_FC_HSYNCINWIDTH1                   0x100B
#घोषणा HDMI_FC_VSYNCINDELAY                    0x100C
#घोषणा HDMI_FC_VSYNCINWIDTH                    0x100D
#घोषणा HDMI_FC_INFREQ0                         0x100E
#घोषणा HDMI_FC_INFREQ1                         0x100F
#घोषणा HDMI_FC_INFREQ2                         0x1010
#घोषणा HDMI_FC_CTRLDUR                         0x1011
#घोषणा HDMI_FC_EXCTRLDUR                       0x1012
#घोषणा HDMI_FC_EXCTRLSPAC                      0x1013
#घोषणा HDMI_FC_CH0PREAM                        0x1014
#घोषणा HDMI_FC_CH1PREAM                        0x1015
#घोषणा HDMI_FC_CH2PREAM                        0x1016
#घोषणा HDMI_FC_AVICONF3                        0x1017
#घोषणा HDMI_FC_GCP                             0x1018
#घोषणा HDMI_FC_AVICONF0                        0x1019
#घोषणा HDMI_FC_AVICONF1                        0x101A
#घोषणा HDMI_FC_AVICONF2                        0x101B
#घोषणा HDMI_FC_AVIVID                          0x101C
#घोषणा HDMI_FC_AVIETB0                         0x101D
#घोषणा HDMI_FC_AVIETB1                         0x101E
#घोषणा HDMI_FC_AVISBB0                         0x101F
#घोषणा HDMI_FC_AVISBB1                         0x1020
#घोषणा HDMI_FC_AVIELB0                         0x1021
#घोषणा HDMI_FC_AVIELB1                         0x1022
#घोषणा HDMI_FC_AVISRB0                         0x1023
#घोषणा HDMI_FC_AVISRB1                         0x1024
#घोषणा HDMI_FC_AUDICONF0                       0x1025
#घोषणा HDMI_FC_AUDICONF1                       0x1026
#घोषणा HDMI_FC_AUDICONF2                       0x1027
#घोषणा HDMI_FC_AUDICONF3                       0x1028
#घोषणा HDMI_FC_VSDIEEEID0                      0x1029
#घोषणा HDMI_FC_VSDSIZE                         0x102A
#घोषणा HDMI_FC_VSDIEEEID1                      0x1030
#घोषणा HDMI_FC_VSDIEEEID2                      0x1031
#घोषणा HDMI_FC_VSDPAYLOAD0                     0x1032
#घोषणा HDMI_FC_VSDPAYLOAD1                     0x1033
#घोषणा HDMI_FC_VSDPAYLOAD2                     0x1034
#घोषणा HDMI_FC_VSDPAYLOAD3                     0x1035
#घोषणा HDMI_FC_VSDPAYLOAD4                     0x1036
#घोषणा HDMI_FC_VSDPAYLOAD5                     0x1037
#घोषणा HDMI_FC_VSDPAYLOAD6                     0x1038
#घोषणा HDMI_FC_VSDPAYLOAD7                     0x1039
#घोषणा HDMI_FC_VSDPAYLOAD8                     0x103A
#घोषणा HDMI_FC_VSDPAYLOAD9                     0x103B
#घोषणा HDMI_FC_VSDPAYLOAD10                    0x103C
#घोषणा HDMI_FC_VSDPAYLOAD11                    0x103D
#घोषणा HDMI_FC_VSDPAYLOAD12                    0x103E
#घोषणा HDMI_FC_VSDPAYLOAD13                    0x103F
#घोषणा HDMI_FC_VSDPAYLOAD14                    0x1040
#घोषणा HDMI_FC_VSDPAYLOAD15                    0x1041
#घोषणा HDMI_FC_VSDPAYLOAD16                    0x1042
#घोषणा HDMI_FC_VSDPAYLOAD17                    0x1043
#घोषणा HDMI_FC_VSDPAYLOAD18                    0x1044
#घोषणा HDMI_FC_VSDPAYLOAD19                    0x1045
#घोषणा HDMI_FC_VSDPAYLOAD20                    0x1046
#घोषणा HDMI_FC_VSDPAYLOAD21                    0x1047
#घोषणा HDMI_FC_VSDPAYLOAD22                    0x1048
#घोषणा HDMI_FC_VSDPAYLOAD23                    0x1049
#घोषणा HDMI_FC_SPDVENDORNAME0                  0x104A
#घोषणा HDMI_FC_SPDVENDORNAME1                  0x104B
#घोषणा HDMI_FC_SPDVENDORNAME2                  0x104C
#घोषणा HDMI_FC_SPDVENDORNAME3                  0x104D
#घोषणा HDMI_FC_SPDVENDORNAME4                  0x104E
#घोषणा HDMI_FC_SPDVENDORNAME5                  0x104F
#घोषणा HDMI_FC_SPDVENDORNAME6                  0x1050
#घोषणा HDMI_FC_SPDVENDORNAME7                  0x1051
#घोषणा HDMI_FC_SDPPRODUCTNAME0                 0x1052
#घोषणा HDMI_FC_SDPPRODUCTNAME1                 0x1053
#घोषणा HDMI_FC_SDPPRODUCTNAME2                 0x1054
#घोषणा HDMI_FC_SDPPRODUCTNAME3                 0x1055
#घोषणा HDMI_FC_SDPPRODUCTNAME4                 0x1056
#घोषणा HDMI_FC_SDPPRODUCTNAME5                 0x1057
#घोषणा HDMI_FC_SDPPRODUCTNAME6                 0x1058
#घोषणा HDMI_FC_SDPPRODUCTNAME7                 0x1059
#घोषणा HDMI_FC_SDPPRODUCTNAME8                 0x105A
#घोषणा HDMI_FC_SDPPRODUCTNAME9                 0x105B
#घोषणा HDMI_FC_SDPPRODUCTNAME10                0x105C
#घोषणा HDMI_FC_SDPPRODUCTNAME11                0x105D
#घोषणा HDMI_FC_SDPPRODUCTNAME12                0x105E
#घोषणा HDMI_FC_SDPPRODUCTNAME13                0x105F
#घोषणा HDMI_FC_SDPPRODUCTNAME14                0x1060
#घोषणा HDMI_FC_SPDPRODUCTNAME15                0x1061
#घोषणा HDMI_FC_SPDDEVICEINF                    0x1062
#घोषणा HDMI_FC_AUDSCONF                        0x1063
#घोषणा HDMI_FC_AUDSSTAT                        0x1064
#घोषणा HDMI_FC_AUDSCHNLS7                      0x106e
#घोषणा HDMI_FC_AUDSCHNLS8                      0x106f
#घोषणा HDMI_FC_DATACH0FILL                     0x1070
#घोषणा HDMI_FC_DATACH1FILL                     0x1071
#घोषणा HDMI_FC_DATACH2FILL                     0x1072
#घोषणा HDMI_FC_CTRLQHIGH                       0x1073
#घोषणा HDMI_FC_CTRLQLOW                        0x1074
#घोषणा HDMI_FC_ACP0                            0x1075
#घोषणा HDMI_FC_ACP28                           0x1076
#घोषणा HDMI_FC_ACP27                           0x1077
#घोषणा HDMI_FC_ACP26                           0x1078
#घोषणा HDMI_FC_ACP25                           0x1079
#घोषणा HDMI_FC_ACP24                           0x107A
#घोषणा HDMI_FC_ACP23                           0x107B
#घोषणा HDMI_FC_ACP22                           0x107C
#घोषणा HDMI_FC_ACP21                           0x107D
#घोषणा HDMI_FC_ACP20                           0x107E
#घोषणा HDMI_FC_ACP19                           0x107F
#घोषणा HDMI_FC_ACP18                           0x1080
#घोषणा HDMI_FC_ACP17                           0x1081
#घोषणा HDMI_FC_ACP16                           0x1082
#घोषणा HDMI_FC_ACP15                           0x1083
#घोषणा HDMI_FC_ACP14                           0x1084
#घोषणा HDMI_FC_ACP13                           0x1085
#घोषणा HDMI_FC_ACP12                           0x1086
#घोषणा HDMI_FC_ACP11                           0x1087
#घोषणा HDMI_FC_ACP10                           0x1088
#घोषणा HDMI_FC_ACP9                            0x1089
#घोषणा HDMI_FC_ACP8                            0x108A
#घोषणा HDMI_FC_ACP7                            0x108B
#घोषणा HDMI_FC_ACP6                            0x108C
#घोषणा HDMI_FC_ACP5                            0x108D
#घोषणा HDMI_FC_ACP4                            0x108E
#घोषणा HDMI_FC_ACP3                            0x108F
#घोषणा HDMI_FC_ACP2                            0x1090
#घोषणा HDMI_FC_ACP1                            0x1091
#घोषणा HDMI_FC_ISCR1_0                         0x1092
#घोषणा HDMI_FC_ISCR1_16                        0x1093
#घोषणा HDMI_FC_ISCR1_15                        0x1094
#घोषणा HDMI_FC_ISCR1_14                        0x1095
#घोषणा HDMI_FC_ISCR1_13                        0x1096
#घोषणा HDMI_FC_ISCR1_12                        0x1097
#घोषणा HDMI_FC_ISCR1_11                        0x1098
#घोषणा HDMI_FC_ISCR1_10                        0x1099
#घोषणा HDMI_FC_ISCR1_9                         0x109A
#घोषणा HDMI_FC_ISCR1_8                         0x109B
#घोषणा HDMI_FC_ISCR1_7                         0x109C
#घोषणा HDMI_FC_ISCR1_6                         0x109D
#घोषणा HDMI_FC_ISCR1_5                         0x109E
#घोषणा HDMI_FC_ISCR1_4                         0x109F
#घोषणा HDMI_FC_ISCR1_3                         0x10A0
#घोषणा HDMI_FC_ISCR1_2                         0x10A1
#घोषणा HDMI_FC_ISCR1_1                         0x10A2
#घोषणा HDMI_FC_ISCR2_15                        0x10A3
#घोषणा HDMI_FC_ISCR2_14                        0x10A4
#घोषणा HDMI_FC_ISCR2_13                        0x10A5
#घोषणा HDMI_FC_ISCR2_12                        0x10A6
#घोषणा HDMI_FC_ISCR2_11                        0x10A7
#घोषणा HDMI_FC_ISCR2_10                        0x10A8
#घोषणा HDMI_FC_ISCR2_9                         0x10A9
#घोषणा HDMI_FC_ISCR2_8                         0x10AA
#घोषणा HDMI_FC_ISCR2_7                         0x10AB
#घोषणा HDMI_FC_ISCR2_6                         0x10AC
#घोषणा HDMI_FC_ISCR2_5                         0x10AD
#घोषणा HDMI_FC_ISCR2_4                         0x10AE
#घोषणा HDMI_FC_ISCR2_3                         0x10AF
#घोषणा HDMI_FC_ISCR2_2                         0x10B0
#घोषणा HDMI_FC_ISCR2_1                         0x10B1
#घोषणा HDMI_FC_ISCR2_0                         0x10B2
#घोषणा HDMI_FC_DATAUTO0                        0x10B3
#घोषणा HDMI_FC_DATAUTO1                        0x10B4
#घोषणा HDMI_FC_DATAUTO2                        0x10B5
#घोषणा HDMI_FC_DATMAN                          0x10B6
#घोषणा HDMI_FC_DATAUTO3                        0x10B7
#घोषणा HDMI_FC_RDRB0                           0x10B8
#घोषणा HDMI_FC_RDRB1                           0x10B9
#घोषणा HDMI_FC_RDRB2                           0x10BA
#घोषणा HDMI_FC_RDRB3                           0x10BB
#घोषणा HDMI_FC_RDRB4                           0x10BC
#घोषणा HDMI_FC_RDRB5                           0x10BD
#घोषणा HDMI_FC_RDRB6                           0x10BE
#घोषणा HDMI_FC_RDRB7                           0x10BF
#घोषणा HDMI_FC_STAT0                           0x10D0
#घोषणा HDMI_FC_INT0                            0x10D1
#घोषणा HDMI_FC_MASK0                           0x10D2
#घोषणा HDMI_FC_POL0                            0x10D3
#घोषणा HDMI_FC_STAT1                           0x10D4
#घोषणा HDMI_FC_INT1                            0x10D5
#घोषणा HDMI_FC_MASK1                           0x10D6
#घोषणा HDMI_FC_POL1                            0x10D7
#घोषणा HDMI_FC_STAT2                           0x10D8
#घोषणा HDMI_FC_INT2                            0x10D9
#घोषणा HDMI_FC_MASK2                           0x10DA
#घोषणा HDMI_FC_POL2                            0x10DB
#घोषणा HDMI_FC_PRCONF                          0x10E0
#घोषणा HDMI_FC_SCRAMBLER_CTRL                  0x10E1
#घोषणा HDMI_FC_PACKET_TX_EN                    0x10E3

#घोषणा HDMI_FC_GMD_STAT                        0x1100
#घोषणा HDMI_FC_GMD_EN                          0x1101
#घोषणा HDMI_FC_GMD_UP                          0x1102
#घोषणा HDMI_FC_GMD_CONF                        0x1103
#घोषणा HDMI_FC_GMD_HB                          0x1104
#घोषणा HDMI_FC_GMD_PB0                         0x1105
#घोषणा HDMI_FC_GMD_PB1                         0x1106
#घोषणा HDMI_FC_GMD_PB2                         0x1107
#घोषणा HDMI_FC_GMD_PB3                         0x1108
#घोषणा HDMI_FC_GMD_PB4                         0x1109
#घोषणा HDMI_FC_GMD_PB5                         0x110A
#घोषणा HDMI_FC_GMD_PB6                         0x110B
#घोषणा HDMI_FC_GMD_PB7                         0x110C
#घोषणा HDMI_FC_GMD_PB8                         0x110D
#घोषणा HDMI_FC_GMD_PB9                         0x110E
#घोषणा HDMI_FC_GMD_PB10                        0x110F
#घोषणा HDMI_FC_GMD_PB11                        0x1110
#घोषणा HDMI_FC_GMD_PB12                        0x1111
#घोषणा HDMI_FC_GMD_PB13                        0x1112
#घोषणा HDMI_FC_GMD_PB14                        0x1113
#घोषणा HDMI_FC_GMD_PB15                        0x1114
#घोषणा HDMI_FC_GMD_PB16                        0x1115
#घोषणा HDMI_FC_GMD_PB17                        0x1116
#घोषणा HDMI_FC_GMD_PB18                        0x1117
#घोषणा HDMI_FC_GMD_PB19                        0x1118
#घोषणा HDMI_FC_GMD_PB20                        0x1119
#घोषणा HDMI_FC_GMD_PB21                        0x111A
#घोषणा HDMI_FC_GMD_PB22                        0x111B
#घोषणा HDMI_FC_GMD_PB23                        0x111C
#घोषणा HDMI_FC_GMD_PB24                        0x111D
#घोषणा HDMI_FC_GMD_PB25                        0x111E
#घोषणा HDMI_FC_GMD_PB26                        0x111F
#घोषणा HDMI_FC_GMD_PB27                        0x1120

#घोषणा HDMI_FC_DRM_UP                          0x1167
#घोषणा HDMI_FC_DRM_HB0                         0x1168
#घोषणा HDMI_FC_DRM_HB1                         0x1169
#घोषणा HDMI_FC_DRM_PB0                         0x116A
#घोषणा HDMI_FC_DRM_PB1                         0x116B
#घोषणा HDMI_FC_DRM_PB2                         0x116C
#घोषणा HDMI_FC_DRM_PB3                         0x116D
#घोषणा HDMI_FC_DRM_PB4                         0x116E
#घोषणा HDMI_FC_DRM_PB5                         0x116F
#घोषणा HDMI_FC_DRM_PB6                         0x1170
#घोषणा HDMI_FC_DRM_PB7                         0x1171
#घोषणा HDMI_FC_DRM_PB8                         0x1172
#घोषणा HDMI_FC_DRM_PB9                         0x1173
#घोषणा HDMI_FC_DRM_PB10                        0x1174
#घोषणा HDMI_FC_DRM_PB11                        0x1175
#घोषणा HDMI_FC_DRM_PB12                        0x1176
#घोषणा HDMI_FC_DRM_PB13                        0x1177
#घोषणा HDMI_FC_DRM_PB14                        0x1178
#घोषणा HDMI_FC_DRM_PB15                        0x1179
#घोषणा HDMI_FC_DRM_PB16                        0x117A
#घोषणा HDMI_FC_DRM_PB17                        0x117B
#घोषणा HDMI_FC_DRM_PB18                        0x117C
#घोषणा HDMI_FC_DRM_PB19                        0x117D
#घोषणा HDMI_FC_DRM_PB20                        0x117E
#घोषणा HDMI_FC_DRM_PB21                        0x117F
#घोषणा HDMI_FC_DRM_PB22                        0x1180
#घोषणा HDMI_FC_DRM_PB23                        0x1181
#घोषणा HDMI_FC_DRM_PB24                        0x1182
#घोषणा HDMI_FC_DRM_PB25                        0x1183
#घोषणा HDMI_FC_DRM_PB26                        0x1184

#घोषणा HDMI_FC_DBGFORCE                        0x1200
#घोषणा HDMI_FC_DBGAUD0CH0                      0x1201
#घोषणा HDMI_FC_DBGAUD1CH0                      0x1202
#घोषणा HDMI_FC_DBGAUD2CH0                      0x1203
#घोषणा HDMI_FC_DBGAUD0CH1                      0x1204
#घोषणा HDMI_FC_DBGAUD1CH1                      0x1205
#घोषणा HDMI_FC_DBGAUD2CH1                      0x1206
#घोषणा HDMI_FC_DBGAUD0CH2                      0x1207
#घोषणा HDMI_FC_DBGAUD1CH2                      0x1208
#घोषणा HDMI_FC_DBGAUD2CH2                      0x1209
#घोषणा HDMI_FC_DBGAUD0CH3                      0x120A
#घोषणा HDMI_FC_DBGAUD1CH3                      0x120B
#घोषणा HDMI_FC_DBGAUD2CH3                      0x120C
#घोषणा HDMI_FC_DBGAUD0CH4                      0x120D
#घोषणा HDMI_FC_DBGAUD1CH4                      0x120E
#घोषणा HDMI_FC_DBGAUD2CH4                      0x120F
#घोषणा HDMI_FC_DBGAUD0CH5                      0x1210
#घोषणा HDMI_FC_DBGAUD1CH5                      0x1211
#घोषणा HDMI_FC_DBGAUD2CH5                      0x1212
#घोषणा HDMI_FC_DBGAUD0CH6                      0x1213
#घोषणा HDMI_FC_DBGAUD1CH6                      0x1214
#घोषणा HDMI_FC_DBGAUD2CH6                      0x1215
#घोषणा HDMI_FC_DBGAUD0CH7                      0x1216
#घोषणा HDMI_FC_DBGAUD1CH7                      0x1217
#घोषणा HDMI_FC_DBGAUD2CH7                      0x1218
#घोषणा HDMI_FC_DBGTMDS0                        0x1219
#घोषणा HDMI_FC_DBGTMDS1                        0x121A
#घोषणा HDMI_FC_DBGTMDS2                        0x121B

/* HDMI Source PHY Registers */
#घोषणा HDMI_PHY_CONF0                          0x3000
#घोषणा HDMI_PHY_TST0                           0x3001
#घोषणा HDMI_PHY_TST1                           0x3002
#घोषणा HDMI_PHY_TST2                           0x3003
#घोषणा HDMI_PHY_STAT0                          0x3004
#घोषणा HDMI_PHY_INT0                           0x3005
#घोषणा HDMI_PHY_MASK0                          0x3006
#घोषणा HDMI_PHY_POL0                           0x3007

/* HDMI Master PHY Registers */
#घोषणा HDMI_PHY_I2CM_SLAVE_ADDR                0x3020
#घोषणा HDMI_PHY_I2CM_ADDRESS_ADDR              0x3021
#घोषणा HDMI_PHY_I2CM_DATAO_1_ADDR              0x3022
#घोषणा HDMI_PHY_I2CM_DATAO_0_ADDR              0x3023
#घोषणा HDMI_PHY_I2CM_DATAI_1_ADDR              0x3024
#घोषणा HDMI_PHY_I2CM_DATAI_0_ADDR              0x3025
#घोषणा HDMI_PHY_I2CM_OPERATION_ADDR            0x3026
#घोषणा HDMI_PHY_I2CM_INT_ADDR                  0x3027
#घोषणा HDMI_PHY_I2CM_CTLINT_ADDR               0x3028
#घोषणा HDMI_PHY_I2CM_DIV_ADDR                  0x3029
#घोषणा HDMI_PHY_I2CM_SOFTRSTZ_ADDR             0x302a
#घोषणा HDMI_PHY_I2CM_SS_SCL_HCNT_1_ADDR        0x302b
#घोषणा HDMI_PHY_I2CM_SS_SCL_HCNT_0_ADDR        0x302c
#घोषणा HDMI_PHY_I2CM_SS_SCL_LCNT_1_ADDR        0x302d
#घोषणा HDMI_PHY_I2CM_SS_SCL_LCNT_0_ADDR        0x302e
#घोषणा HDMI_PHY_I2CM_FS_SCL_HCNT_1_ADDR        0x302f
#घोषणा HDMI_PHY_I2CM_FS_SCL_HCNT_0_ADDR        0x3030
#घोषणा HDMI_PHY_I2CM_FS_SCL_LCNT_1_ADDR        0x3031
#घोषणा HDMI_PHY_I2CM_FS_SCL_LCNT_0_ADDR        0x3032

/* Audio Sampler Registers */
#घोषणा HDMI_AUD_CONF0                          0x3100
#घोषणा HDMI_AUD_CONF1                          0x3101
#घोषणा HDMI_AUD_INT                            0x3102
#घोषणा HDMI_AUD_CONF2                          0x3103
#घोषणा HDMI_AUD_N1                             0x3200
#घोषणा HDMI_AUD_N2                             0x3201
#घोषणा HDMI_AUD_N3                             0x3202
#घोषणा HDMI_AUD_CTS1                           0x3203
#घोषणा HDMI_AUD_CTS2                           0x3204
#घोषणा HDMI_AUD_CTS3                           0x3205
#घोषणा HDMI_AUD_INPUTCLKFS                     0x3206
#घोषणा HDMI_AUD_SPDIFINT			0x3302
#घोषणा HDMI_AUD_CONF0_HBR                      0x3400
#घोषणा HDMI_AUD_HBR_STATUS                     0x3401
#घोषणा HDMI_AUD_HBR_INT                        0x3402
#घोषणा HDMI_AUD_HBR_POL                        0x3403
#घोषणा HDMI_AUD_HBR_MASK                       0x3404

/*
 * Generic Parallel Audio Interface Registers
 * Not used as GPAUD पूर्णांकerface is not enabled in hw
 */
#घोषणा HDMI_GP_CONF0                           0x3500
#घोषणा HDMI_GP_CONF1                           0x3501
#घोषणा HDMI_GP_CONF2                           0x3502
#घोषणा HDMI_GP_STAT                            0x3503
#घोषणा HDMI_GP_INT                             0x3504
#घोषणा HDMI_GP_MASK                            0x3505
#घोषणा HDMI_GP_POL                             0x3506

/* Audio DMA Registers */
#घोषणा HDMI_AHB_DMA_CONF0                      0x3600
#घोषणा HDMI_AHB_DMA_START                      0x3601
#घोषणा HDMI_AHB_DMA_STOP                       0x3602
#घोषणा HDMI_AHB_DMA_THRSLD                     0x3603
#घोषणा HDMI_AHB_DMA_STRADDR0                   0x3604
#घोषणा HDMI_AHB_DMA_STRADDR1                   0x3605
#घोषणा HDMI_AHB_DMA_STRADDR2                   0x3606
#घोषणा HDMI_AHB_DMA_STRADDR3                   0x3607
#घोषणा HDMI_AHB_DMA_STPADDR0                   0x3608
#घोषणा HDMI_AHB_DMA_STPADDR1                   0x3609
#घोषणा HDMI_AHB_DMA_STPADDR2                   0x360a
#घोषणा HDMI_AHB_DMA_STPADDR3                   0x360b
#घोषणा HDMI_AHB_DMA_BSTADDR0                   0x360c
#घोषणा HDMI_AHB_DMA_BSTADDR1                   0x360d
#घोषणा HDMI_AHB_DMA_BSTADDR2                   0x360e
#घोषणा HDMI_AHB_DMA_BSTADDR3                   0x360f
#घोषणा HDMI_AHB_DMA_MBLENGTH0                  0x3610
#घोषणा HDMI_AHB_DMA_MBLENGTH1                  0x3611
#घोषणा HDMI_AHB_DMA_STAT                       0x3612
#घोषणा HDMI_AHB_DMA_INT                        0x3613
#घोषणा HDMI_AHB_DMA_MASK                       0x3614
#घोषणा HDMI_AHB_DMA_POL                        0x3615
#घोषणा HDMI_AHB_DMA_CONF1                      0x3616
#घोषणा HDMI_AHB_DMA_BUFFSTAT                   0x3617
#घोषणा HDMI_AHB_DMA_BUFFINT                    0x3618
#घोषणा HDMI_AHB_DMA_BUFFMASK                   0x3619
#घोषणा HDMI_AHB_DMA_BUFFPOL                    0x361a

/* Main Controller Registers */
#घोषणा HDMI_MC_SFRDIV                          0x4000
#घोषणा HDMI_MC_CLKDIS                          0x4001
#घोषणा HDMI_MC_SWRSTZ                          0x4002
#घोषणा HDMI_MC_OPCTRL                          0x4003
#घोषणा HDMI_MC_FLOWCTRL                        0x4004
#घोषणा HDMI_MC_PHYRSTZ                         0x4005
#घोषणा HDMI_MC_LOCKONCLOCK                     0x4006
#घोषणा HDMI_MC_HEACPHY_RST                     0x4007

/* Color Space  Converter Registers */
#घोषणा HDMI_CSC_CFG                            0x4100
#घोषणा HDMI_CSC_SCALE                          0x4101
#घोषणा HDMI_CSC_COEF_A1_MSB                    0x4102
#घोषणा HDMI_CSC_COEF_A1_LSB                    0x4103
#घोषणा HDMI_CSC_COEF_A2_MSB                    0x4104
#घोषणा HDMI_CSC_COEF_A2_LSB                    0x4105
#घोषणा HDMI_CSC_COEF_A3_MSB                    0x4106
#घोषणा HDMI_CSC_COEF_A3_LSB                    0x4107
#घोषणा HDMI_CSC_COEF_A4_MSB                    0x4108
#घोषणा HDMI_CSC_COEF_A4_LSB                    0x4109
#घोषणा HDMI_CSC_COEF_B1_MSB                    0x410A
#घोषणा HDMI_CSC_COEF_B1_LSB                    0x410B
#घोषणा HDMI_CSC_COEF_B2_MSB                    0x410C
#घोषणा HDMI_CSC_COEF_B2_LSB                    0x410D
#घोषणा HDMI_CSC_COEF_B3_MSB                    0x410E
#घोषणा HDMI_CSC_COEF_B3_LSB                    0x410F
#घोषणा HDMI_CSC_COEF_B4_MSB                    0x4110
#घोषणा HDMI_CSC_COEF_B4_LSB                    0x4111
#घोषणा HDMI_CSC_COEF_C1_MSB                    0x4112
#घोषणा HDMI_CSC_COEF_C1_LSB                    0x4113
#घोषणा HDMI_CSC_COEF_C2_MSB                    0x4114
#घोषणा HDMI_CSC_COEF_C2_LSB                    0x4115
#घोषणा HDMI_CSC_COEF_C3_MSB                    0x4116
#घोषणा HDMI_CSC_COEF_C3_LSB                    0x4117
#घोषणा HDMI_CSC_COEF_C4_MSB                    0x4118
#घोषणा HDMI_CSC_COEF_C4_LSB                    0x4119

/* HDCP Encryption Engine Registers */
#घोषणा HDMI_A_HDCPCFG0                         0x5000
#घोषणा HDMI_A_HDCPCFG1                         0x5001
#घोषणा HDMI_A_HDCPOBS0                         0x5002
#घोषणा HDMI_A_HDCPOBS1                         0x5003
#घोषणा HDMI_A_HDCPOBS2                         0x5004
#घोषणा HDMI_A_HDCPOBS3                         0x5005
#घोषणा HDMI_A_APIINTCLR                        0x5006
#घोषणा HDMI_A_APIINTSTAT                       0x5007
#घोषणा HDMI_A_APIINTMSK                        0x5008
#घोषणा HDMI_A_VIDPOLCFG                        0x5009
#घोषणा HDMI_A_OESSWCFG                         0x500A
#घोषणा HDMI_A_TIMER1SETUP0                     0x500B
#घोषणा HDMI_A_TIMER1SETUP1                     0x500C
#घोषणा HDMI_A_TIMER2SETUP0                     0x500D
#घोषणा HDMI_A_TIMER2SETUP1                     0x500E
#घोषणा HDMI_A_100MSCFG                         0x500F
#घोषणा HDMI_A_2SCFG0                           0x5010
#घोषणा HDMI_A_2SCFG1                           0x5011
#घोषणा HDMI_A_5SCFG0                           0x5012
#घोषणा HDMI_A_5SCFG1                           0x5013
#घोषणा HDMI_A_SRMVERLSB                        0x5014
#घोषणा HDMI_A_SRMVERMSB                        0x5015
#घोषणा HDMI_A_SRMCTRL                          0x5016
#घोषणा HDMI_A_SFRSETUP                         0x5017
#घोषणा HDMI_A_I2CHSETUP                        0x5018
#घोषणा HDMI_A_INTSETUP                         0x5019
#घोषणा HDMI_A_PRESETUP                         0x501A
#घोषणा HDMI_A_SRM_BASE                         0x5020

/* I2C Master Registers (E-DDC) */
#घोषणा HDMI_I2CM_SLAVE                         0x7E00
#घोषणा HDMI_I2CM_ADDRESS                       0x7E01
#घोषणा HDMI_I2CM_DATAO                         0x7E02
#घोषणा HDMI_I2CM_DATAI                         0x7E03
#घोषणा HDMI_I2CM_OPERATION                     0x7E04
#घोषणा HDMI_I2CM_INT                           0x7E05
#घोषणा HDMI_I2CM_CTLINT                        0x7E06
#घोषणा HDMI_I2CM_DIV                           0x7E07
#घोषणा HDMI_I2CM_SEGADDR                       0x7E08
#घोषणा HDMI_I2CM_SOFTRSTZ                      0x7E09
#घोषणा HDMI_I2CM_SEGPTR                        0x7E0A
#घोषणा HDMI_I2CM_SS_SCL_HCNT_1_ADDR            0x7E0B
#घोषणा HDMI_I2CM_SS_SCL_HCNT_0_ADDR            0x7E0C
#घोषणा HDMI_I2CM_SS_SCL_LCNT_1_ADDR            0x7E0D
#घोषणा HDMI_I2CM_SS_SCL_LCNT_0_ADDR            0x7E0E
#घोषणा HDMI_I2CM_FS_SCL_HCNT_1_ADDR            0x7E0F
#घोषणा HDMI_I2CM_FS_SCL_HCNT_0_ADDR            0x7E10
#घोषणा HDMI_I2CM_FS_SCL_LCNT_1_ADDR            0x7E11
#घोषणा HDMI_I2CM_FS_SCL_LCNT_0_ADDR            0x7E12

क्रमागत अणु
/* PRODUCT_ID0 field values */
	HDMI_PRODUCT_ID0_HDMI_TX = 0xa0,

/* PRODUCT_ID1 field values */
	HDMI_PRODUCT_ID1_HDCP = 0xc0,
	HDMI_PRODUCT_ID1_HDMI_RX = 0x02,
	HDMI_PRODUCT_ID1_HDMI_TX = 0x01,

/* CONFIG0_ID field values */
	HDMI_CONFIG0_I2S = 0x10,
	HDMI_CONFIG0_CEC = 0x02,

/* CONFIG1_ID field values */
	HDMI_CONFIG1_AHB = 0x01,

/* CONFIG3_ID field values */
	HDMI_CONFIG3_AHBAUDDMA = 0x02,
	HDMI_CONFIG3_GPAUD = 0x01,

/* IH_FC_INT2 field values */
	HDMI_IH_FC_INT2_OVERFLOW_MASK = 0x03,
	HDMI_IH_FC_INT2_LOW_PRIORITY_OVERFLOW = 0x02,
	HDMI_IH_FC_INT2_HIGH_PRIORITY_OVERFLOW = 0x01,

/* IH_FC_STAT2 field values */
	HDMI_IH_FC_STAT2_OVERFLOW_MASK = 0x03,
	HDMI_IH_FC_STAT2_LOW_PRIORITY_OVERFLOW = 0x02,
	HDMI_IH_FC_STAT2_HIGH_PRIORITY_OVERFLOW = 0x01,

/* IH_PHY_STAT0 field values */
	HDMI_IH_PHY_STAT0_RX_SENSE3 = 0x20,
	HDMI_IH_PHY_STAT0_RX_SENSE2 = 0x10,
	HDMI_IH_PHY_STAT0_RX_SENSE1 = 0x8,
	HDMI_IH_PHY_STAT0_RX_SENSE0 = 0x4,
	HDMI_IH_PHY_STAT0_TX_PHY_LOCK = 0x2,
	HDMI_IH_PHY_STAT0_HPD = 0x1,

/* IH_I2CM_STAT0 and IH_MUTE_I2CM_STAT0 field values */
	HDMI_IH_I2CM_STAT0_DONE = 0x2,
	HDMI_IH_I2CM_STAT0_ERROR = 0x1,

/* IH_MUTE_I2CMPHY_STAT0 field values */
	HDMI_IH_MUTE_I2CMPHY_STAT0_I2CMPHYDONE = 0x2,
	HDMI_IH_MUTE_I2CMPHY_STAT0_I2CMPHYERROR = 0x1,

/* IH_AHBDMAAUD_STAT0 field values */
	HDMI_IH_AHBDMAAUD_STAT0_ERROR = 0x20,
	HDMI_IH_AHBDMAAUD_STAT0_LOST = 0x10,
	HDMI_IH_AHBDMAAUD_STAT0_RETRY = 0x08,
	HDMI_IH_AHBDMAAUD_STAT0_DONE = 0x04,
	HDMI_IH_AHBDMAAUD_STAT0_BUFFFULL = 0x02,
	HDMI_IH_AHBDMAAUD_STAT0_BUFFEMPTY = 0x01,

/* IH_MUTE_FC_STAT2 field values */
	HDMI_IH_MUTE_FC_STAT2_OVERFLOW_MASK = 0x03,
	HDMI_IH_MUTE_FC_STAT2_LOW_PRIORITY_OVERFLOW = 0x02,
	HDMI_IH_MUTE_FC_STAT2_HIGH_PRIORITY_OVERFLOW = 0x01,

/* IH_MUTE_AHBDMAAUD_STAT0 field values */
	HDMI_IH_MUTE_AHBDMAAUD_STAT0_ERROR = 0x20,
	HDMI_IH_MUTE_AHBDMAAUD_STAT0_LOST = 0x10,
	HDMI_IH_MUTE_AHBDMAAUD_STAT0_RETRY = 0x08,
	HDMI_IH_MUTE_AHBDMAAUD_STAT0_DONE = 0x04,
	HDMI_IH_MUTE_AHBDMAAUD_STAT0_BUFFFULL = 0x02,
	HDMI_IH_MUTE_AHBDMAAUD_STAT0_BUFFEMPTY = 0x01,

/* IH_MUTE field values */
	HDMI_IH_MUTE_MUTE_WAKEUP_INTERRUPT = 0x2,
	HDMI_IH_MUTE_MUTE_ALL_INTERRUPT = 0x1,

/* TX_INVID0 field values */
	HDMI_TX_INVID0_INTERNAL_DE_GENERATOR_MASK = 0x80,
	HDMI_TX_INVID0_INTERNAL_DE_GENERATOR_ENABLE = 0x80,
	HDMI_TX_INVID0_INTERNAL_DE_GENERATOR_DISABLE = 0x00,
	HDMI_TX_INVID0_VIDEO_MAPPING_MASK = 0x1F,
	HDMI_TX_INVID0_VIDEO_MAPPING_OFFSET = 0,

/* TX_INSTUFFING field values */
	HDMI_TX_INSTUFFING_BDBDATA_STUFFING_MASK = 0x4,
	HDMI_TX_INSTUFFING_BDBDATA_STUFFING_ENABLE = 0x4,
	HDMI_TX_INSTUFFING_BDBDATA_STUFFING_DISABLE = 0x0,
	HDMI_TX_INSTUFFING_RCRDATA_STUFFING_MASK = 0x2,
	HDMI_TX_INSTUFFING_RCRDATA_STUFFING_ENABLE = 0x2,
	HDMI_TX_INSTUFFING_RCRDATA_STUFFING_DISABLE = 0x0,
	HDMI_TX_INSTUFFING_GYDATA_STUFFING_MASK = 0x1,
	HDMI_TX_INSTUFFING_GYDATA_STUFFING_ENABLE = 0x1,
	HDMI_TX_INSTUFFING_GYDATA_STUFFING_DISABLE = 0x0,

/* VP_PR_CD field values */
	HDMI_VP_PR_CD_COLOR_DEPTH_MASK = 0xF0,
	HDMI_VP_PR_CD_COLOR_DEPTH_OFFSET = 4,
	HDMI_VP_PR_CD_DESIRED_PR_FACTOR_MASK = 0x0F,
	HDMI_VP_PR_CD_DESIRED_PR_FACTOR_OFFSET = 0,

/* VP_STUFF field values */
	HDMI_VP_STUFF_IDEFAULT_PHASE_MASK = 0x20,
	HDMI_VP_STUFF_IDEFAULT_PHASE_OFFSET = 5,
	HDMI_VP_STUFF_IFIX_PP_TO_LAST_MASK = 0x10,
	HDMI_VP_STUFF_IFIX_PP_TO_LAST_OFFSET = 4,
	HDMI_VP_STUFF_ICX_GOTO_P0_ST_MASK = 0x8,
	HDMI_VP_STUFF_ICX_GOTO_P0_ST_OFFSET = 3,
	HDMI_VP_STUFF_YCC422_STUFFING_MASK = 0x4,
	HDMI_VP_STUFF_YCC422_STUFFING_STUFFING_MODE = 0x4,
	HDMI_VP_STUFF_YCC422_STUFFING_सूचीECT_MODE = 0x0,
	HDMI_VP_STUFF_PP_STUFFING_MASK = 0x2,
	HDMI_VP_STUFF_PP_STUFFING_STUFFING_MODE = 0x2,
	HDMI_VP_STUFF_PP_STUFFING_सूचीECT_MODE = 0x0,
	HDMI_VP_STUFF_PR_STUFFING_MASK = 0x1,
	HDMI_VP_STUFF_PR_STUFFING_STUFFING_MODE = 0x1,
	HDMI_VP_STUFF_PR_STUFFING_सूचीECT_MODE = 0x0,

/* VP_CONF field values */
	HDMI_VP_CONF_BYPASS_EN_MASK = 0x40,
	HDMI_VP_CONF_BYPASS_EN_ENABLE = 0x40,
	HDMI_VP_CONF_BYPASS_EN_DISABLE = 0x00,
	HDMI_VP_CONF_PP_EN_ENMASK = 0x20,
	HDMI_VP_CONF_PP_EN_ENABLE = 0x20,
	HDMI_VP_CONF_PP_EN_DISABLE = 0x00,
	HDMI_VP_CONF_PR_EN_MASK = 0x10,
	HDMI_VP_CONF_PR_EN_ENABLE = 0x10,
	HDMI_VP_CONF_PR_EN_DISABLE = 0x00,
	HDMI_VP_CONF_YCC422_EN_MASK = 0x8,
	HDMI_VP_CONF_YCC422_EN_ENABLE = 0x8,
	HDMI_VP_CONF_YCC422_EN_DISABLE = 0x0,
	HDMI_VP_CONF_BYPASS_SELECT_MASK = 0x4,
	HDMI_VP_CONF_BYPASS_SELECT_VID_PACKETIZER = 0x4,
	HDMI_VP_CONF_BYPASS_SELECT_PIX_REPEATER = 0x0,
	HDMI_VP_CONF_OUTPUT_SELECTOR_MASK = 0x3,
	HDMI_VP_CONF_OUTPUT_SELECTOR_BYPASS = 0x3,
	HDMI_VP_CONF_OUTPUT_SELECTOR_YCC422 = 0x1,
	HDMI_VP_CONF_OUTPUT_SELECTOR_PP = 0x0,

/* VP_REMAP field values */
	HDMI_VP_REMAP_MASK = 0x3,
	HDMI_VP_REMAP_YCC422_24bit = 0x2,
	HDMI_VP_REMAP_YCC422_20bit = 0x1,
	HDMI_VP_REMAP_YCC422_16bit = 0x0,

/* FC_INVIDCONF field values */
	HDMI_FC_INVIDCONF_HDCP_KEEPOUT_MASK = 0x80,
	HDMI_FC_INVIDCONF_HDCP_KEEPOUT_ACTIVE = 0x80,
	HDMI_FC_INVIDCONF_HDCP_KEEPOUT_INACTIVE = 0x00,
	HDMI_FC_INVIDCONF_VSYNC_IN_POLARITY_MASK = 0x40,
	HDMI_FC_INVIDCONF_VSYNC_IN_POLARITY_ACTIVE_HIGH = 0x40,
	HDMI_FC_INVIDCONF_VSYNC_IN_POLARITY_ACTIVE_LOW = 0x00,
	HDMI_FC_INVIDCONF_HSYNC_IN_POLARITY_MASK = 0x20,
	HDMI_FC_INVIDCONF_HSYNC_IN_POLARITY_ACTIVE_HIGH = 0x20,
	HDMI_FC_INVIDCONF_HSYNC_IN_POLARITY_ACTIVE_LOW = 0x00,
	HDMI_FC_INVIDCONF_DE_IN_POLARITY_MASK = 0x10,
	HDMI_FC_INVIDCONF_DE_IN_POLARITY_ACTIVE_HIGH = 0x10,
	HDMI_FC_INVIDCONF_DE_IN_POLARITY_ACTIVE_LOW = 0x00,
	HDMI_FC_INVIDCONF_DVI_MODEZ_MASK = 0x8,
	HDMI_FC_INVIDCONF_DVI_MODEZ_HDMI_MODE = 0x8,
	HDMI_FC_INVIDCONF_DVI_MODEZ_DVI_MODE = 0x0,
	HDMI_FC_INVIDCONF_R_V_BLANK_IN_OSC_MASK = 0x2,
	HDMI_FC_INVIDCONF_R_V_BLANK_IN_OSC_ACTIVE_HIGH = 0x2,
	HDMI_FC_INVIDCONF_R_V_BLANK_IN_OSC_ACTIVE_LOW = 0x0,
	HDMI_FC_INVIDCONF_IN_I_P_MASK = 0x1,
	HDMI_FC_INVIDCONF_IN_I_P_INTERLACED = 0x1,
	HDMI_FC_INVIDCONF_IN_I_P_PROGRESSIVE = 0x0,

/* FC_AUDICONF0 field values */
	HDMI_FC_AUDICONF0_CC_OFFSET = 4,
	HDMI_FC_AUDICONF0_CC_MASK = 0x70,
	HDMI_FC_AUDICONF0_CT_OFFSET = 0,
	HDMI_FC_AUDICONF0_CT_MASK = 0xF,

/* FC_AUDICONF1 field values */
	HDMI_FC_AUDICONF1_SS_OFFSET = 3,
	HDMI_FC_AUDICONF1_SS_MASK = 0x18,
	HDMI_FC_AUDICONF1_SF_OFFSET = 0,
	HDMI_FC_AUDICONF1_SF_MASK = 0x7,

/* FC_AUDICONF3 field values */
	HDMI_FC_AUDICONF3_LFEPBL_OFFSET = 5,
	HDMI_FC_AUDICONF3_LFEPBL_MASK = 0x60,
	HDMI_FC_AUDICONF3_DM_INH_OFFSET = 4,
	HDMI_FC_AUDICONF3_DM_INH_MASK = 0x10,
	HDMI_FC_AUDICONF3_LSV_OFFSET = 0,
	HDMI_FC_AUDICONF3_LSV_MASK = 0xF,

/* FC_AUDSCHNLS0 field values */
	HDMI_FC_AUDSCHNLS0_CGMSA_OFFSET = 4,
	HDMI_FC_AUDSCHNLS0_CGMSA_MASK = 0x30,
	HDMI_FC_AUDSCHNLS0_COPYRIGHT_OFFSET = 0,
	HDMI_FC_AUDSCHNLS0_COPYRIGHT_MASK = 0x01,

/* FC_AUDSCHNLS3-6 field values */
	HDMI_FC_AUDSCHNLS3_OIEC_CH0_OFFSET = 0,
	HDMI_FC_AUDSCHNLS3_OIEC_CH0_MASK = 0x0f,
	HDMI_FC_AUDSCHNLS3_OIEC_CH1_OFFSET = 4,
	HDMI_FC_AUDSCHNLS3_OIEC_CH1_MASK = 0xf0,
	HDMI_FC_AUDSCHNLS4_OIEC_CH2_OFFSET = 0,
	HDMI_FC_AUDSCHNLS4_OIEC_CH2_MASK = 0x0f,
	HDMI_FC_AUDSCHNLS4_OIEC_CH3_OFFSET = 4,
	HDMI_FC_AUDSCHNLS4_OIEC_CH3_MASK = 0xf0,

	HDMI_FC_AUDSCHNLS5_OIEC_CH0_OFFSET = 0,
	HDMI_FC_AUDSCHNLS5_OIEC_CH0_MASK = 0x0f,
	HDMI_FC_AUDSCHNLS5_OIEC_CH1_OFFSET = 4,
	HDMI_FC_AUDSCHNLS5_OIEC_CH1_MASK = 0xf0,
	HDMI_FC_AUDSCHNLS6_OIEC_CH2_OFFSET = 0,
	HDMI_FC_AUDSCHNLS6_OIEC_CH2_MASK = 0x0f,
	HDMI_FC_AUDSCHNLS6_OIEC_CH3_OFFSET = 4,
	HDMI_FC_AUDSCHNLS6_OIEC_CH3_MASK = 0xf0,

/* HDMI_FC_AUDSCHNLS7 field values */
	HDMI_FC_AUDSCHNLS7_ACCURACY_OFFSET = 4,
	HDMI_FC_AUDSCHNLS7_ACCURACY_MASK = 0x30,

/* HDMI_FC_AUDSCHNLS8 field values */
	HDMI_FC_AUDSCHNLS8_ORIGSAMPFREQ_MASK = 0xf0,
	HDMI_FC_AUDSCHNLS8_ORIGSAMPFREQ_OFFSET = 4,
	HDMI_FC_AUDSCHNLS8_WORDLEGNTH_MASK = 0x0f,
	HDMI_FC_AUDSCHNLS8_WORDLEGNTH_OFFSET = 0,

/* FC_AUDSCONF field values */
	HDMI_FC_AUDSCONF_AUD_PACKET_SAMPFIT_MASK = 0xF0,
	HDMI_FC_AUDSCONF_AUD_PACKET_SAMPFIT_OFFSET = 4,
	HDMI_FC_AUDSCONF_AUD_PACKET_LAYOUT_MASK = 0x1,
	HDMI_FC_AUDSCONF_AUD_PACKET_LAYOUT_OFFSET = 0,
	HDMI_FC_AUDSCONF_AUD_PACKET_LAYOUT_LAYOUT1 = 0x1,
	HDMI_FC_AUDSCONF_AUD_PACKET_LAYOUT_LAYOUT0 = 0x0,

/* FC_STAT2 field values */
	HDMI_FC_STAT2_OVERFLOW_MASK = 0x03,
	HDMI_FC_STAT2_LOW_PRIORITY_OVERFLOW = 0x02,
	HDMI_FC_STAT2_HIGH_PRIORITY_OVERFLOW = 0x01,

/* FC_INT2 field values */
	HDMI_FC_INT2_OVERFLOW_MASK = 0x03,
	HDMI_FC_INT2_LOW_PRIORITY_OVERFLOW = 0x02,
	HDMI_FC_INT2_HIGH_PRIORITY_OVERFLOW = 0x01,

/* FC_MASK2 field values */
	HDMI_FC_MASK2_OVERFLOW_MASK = 0x03,
	HDMI_FC_MASK2_LOW_PRIORITY_OVERFLOW = 0x02,
	HDMI_FC_MASK2_HIGH_PRIORITY_OVERFLOW = 0x01,

/* FC_PRCONF field values */
	HDMI_FC_PRCONF_INCOMING_PR_FACTOR_MASK = 0xF0,
	HDMI_FC_PRCONF_INCOMING_PR_FACTOR_OFFSET = 4,
	HDMI_FC_PRCONF_OUTPUT_PR_FACTOR_MASK = 0x0F,
	HDMI_FC_PRCONF_OUTPUT_PR_FACTOR_OFFSET = 0,

/* FC_PACKET_TX_EN field values */
	HDMI_FC_PACKET_TX_EN_DRM_MASK = 0x80,
	HDMI_FC_PACKET_TX_EN_DRM_ENABLE = 0x80,
	HDMI_FC_PACKET_TX_EN_DRM_DISABLE = 0x00,

/* FC_AVICONF0-FC_AVICONF3 field values */
	HDMI_FC_AVICONF0_PIX_FMT_MASK = 0x03,
	HDMI_FC_AVICONF0_PIX_FMT_RGB = 0x00,
	HDMI_FC_AVICONF0_PIX_FMT_YCBCR422 = 0x01,
	HDMI_FC_AVICONF0_PIX_FMT_YCBCR444 = 0x02,
	HDMI_FC_AVICONF0_ACTIVE_FMT_MASK = 0x40,
	HDMI_FC_AVICONF0_ACTIVE_FMT_INFO_PRESENT = 0x40,
	HDMI_FC_AVICONF0_ACTIVE_FMT_NO_INFO = 0x00,
	HDMI_FC_AVICONF0_BAR_DATA_MASK = 0x0C,
	HDMI_FC_AVICONF0_BAR_DATA_NO_DATA = 0x00,
	HDMI_FC_AVICONF0_BAR_DATA_VERT_BAR = 0x04,
	HDMI_FC_AVICONF0_BAR_DATA_HORIZ_BAR = 0x08,
	HDMI_FC_AVICONF0_BAR_DATA_VERT_HORIZ_BAR = 0x0C,
	HDMI_FC_AVICONF0_SCAN_INFO_MASK = 0x30,
	HDMI_FC_AVICONF0_SCAN_INFO_OVERSCAN = 0x10,
	HDMI_FC_AVICONF0_SCAN_INFO_UNDERSCAN = 0x20,
	HDMI_FC_AVICONF0_SCAN_INFO_NODATA = 0x00,

	HDMI_FC_AVICONF1_ACTIVE_ASPECT_RATIO_MASK = 0x0F,
	HDMI_FC_AVICONF1_ACTIVE_ASPECT_RATIO_USE_CODED = 0x08,
	HDMI_FC_AVICONF1_ACTIVE_ASPECT_RATIO_4_3 = 0x09,
	HDMI_FC_AVICONF1_ACTIVE_ASPECT_RATIO_16_9 = 0x0A,
	HDMI_FC_AVICONF1_ACTIVE_ASPECT_RATIO_14_9 = 0x0B,
	HDMI_FC_AVICONF1_CODED_ASPECT_RATIO_MASK = 0x30,
	HDMI_FC_AVICONF1_CODED_ASPECT_RATIO_NO_DATA = 0x00,
	HDMI_FC_AVICONF1_CODED_ASPECT_RATIO_4_3 = 0x10,
	HDMI_FC_AVICONF1_CODED_ASPECT_RATIO_16_9 = 0x20,
	HDMI_FC_AVICONF1_COLORIMETRY_MASK = 0xC0,
	HDMI_FC_AVICONF1_COLORIMETRY_NO_DATA = 0x00,
	HDMI_FC_AVICONF1_COLORIMETRY_SMPTE = 0x40,
	HDMI_FC_AVICONF1_COLORIMETRY_ITUR = 0x80,
	HDMI_FC_AVICONF1_COLORIMETRY_EXTENDED_INFO = 0xC0,

	HDMI_FC_AVICONF2_SCALING_MASK = 0x03,
	HDMI_FC_AVICONF2_SCALING_NONE = 0x00,
	HDMI_FC_AVICONF2_SCALING_HORIZ = 0x01,
	HDMI_FC_AVICONF2_SCALING_VERT = 0x02,
	HDMI_FC_AVICONF2_SCALING_HORIZ_VERT = 0x03,
	HDMI_FC_AVICONF2_RGB_QUANT_MASK = 0x0C,
	HDMI_FC_AVICONF2_RGB_QUANT_DEFAULT = 0x00,
	HDMI_FC_AVICONF2_RGB_QUANT_LIMITED_RANGE = 0x04,
	HDMI_FC_AVICONF2_RGB_QUANT_FULL_RANGE = 0x08,
	HDMI_FC_AVICONF2_EXT_COLORIMETRY_MASK = 0x70,
	HDMI_FC_AVICONF2_EXT_COLORIMETRY_XVYCC601 = 0x00,
	HDMI_FC_AVICONF2_EXT_COLORIMETRY_XVYCC709 = 0x10,
	HDMI_FC_AVICONF2_EXT_COLORIMETRY_SYCC601 = 0x20,
	HDMI_FC_AVICONF2_EXT_COLORIMETRY_ADOBE_YCC601 = 0x30,
	HDMI_FC_AVICONF2_EXT_COLORIMETRY_ADOBE_RGB = 0x40,
	HDMI_FC_AVICONF2_IT_CONTENT_MASK = 0x80,
	HDMI_FC_AVICONF2_IT_CONTENT_NO_DATA = 0x00,
	HDMI_FC_AVICONF2_IT_CONTENT_VALID = 0x80,

	HDMI_FC_AVICONF3_IT_CONTENT_TYPE_MASK = 0x03,
	HDMI_FC_AVICONF3_IT_CONTENT_TYPE_GRAPHICS = 0x00,
	HDMI_FC_AVICONF3_IT_CONTENT_TYPE_PHOTO = 0x01,
	HDMI_FC_AVICONF3_IT_CONTENT_TYPE_CINEMA = 0x02,
	HDMI_FC_AVICONF3_IT_CONTENT_TYPE_GAME = 0x03,
	HDMI_FC_AVICONF3_QUANT_RANGE_MASK = 0x0C,
	HDMI_FC_AVICONF3_QUANT_RANGE_LIMITED = 0x00,
	HDMI_FC_AVICONF3_QUANT_RANGE_FULL = 0x04,

/* FC_DBGFORCE field values */
	HDMI_FC_DBGFORCE_FORCEAUDIO = 0x10,
	HDMI_FC_DBGFORCE_FORCEVIDEO = 0x1,

/* FC_DATAUTO0 field values */
	HDMI_FC_DATAUTO0_VSD_MASK = 0x08,
	HDMI_FC_DATAUTO0_VSD_OFFSET = 3,

/* PHY_CONF0 field values */
	HDMI_PHY_CONF0_PDZ_MASK = 0x80,
	HDMI_PHY_CONF0_PDZ_OFFSET = 7,
	HDMI_PHY_CONF0_ENTMDS_MASK = 0x40,
	HDMI_PHY_CONF0_ENTMDS_OFFSET = 6,
	HDMI_PHY_CONF0_SVSRET_MASK = 0x20,
	HDMI_PHY_CONF0_SVSRET_OFFSET = 5,
	HDMI_PHY_CONF0_GEN2_PDDQ_MASK = 0x10,
	HDMI_PHY_CONF0_GEN2_PDDQ_OFFSET = 4,
	HDMI_PHY_CONF0_GEN2_TXPWRON_MASK = 0x8,
	HDMI_PHY_CONF0_GEN2_TXPWRON_OFFSET = 3,
	HDMI_PHY_CONF0_GEN2_ENHPDRXSENSE_MASK = 0x4,
	HDMI_PHY_CONF0_GEN2_ENHPDRXSENSE_OFFSET = 2,
	HDMI_PHY_CONF0_SELDATAENPOL_MASK = 0x2,
	HDMI_PHY_CONF0_SELDATAENPOL_OFFSET = 1,
	HDMI_PHY_CONF0_SELDIPIF_MASK = 0x1,
	HDMI_PHY_CONF0_SELDIPIF_OFFSET = 0,

/* PHY_TST0 field values */
	HDMI_PHY_TST0_TSTCLR_MASK = 0x20,
	HDMI_PHY_TST0_TSTCLR_OFFSET = 5,
	HDMI_PHY_TST0_TSTEN_MASK = 0x10,
	HDMI_PHY_TST0_TSTEN_OFFSET = 4,
	HDMI_PHY_TST0_TSTCLK_MASK = 0x1,
	HDMI_PHY_TST0_TSTCLK_OFFSET = 0,

/* PHY_STAT0 field values */
	HDMI_PHY_RX_SENSE3 = 0x80,
	HDMI_PHY_RX_SENSE2 = 0x40,
	HDMI_PHY_RX_SENSE1 = 0x20,
	HDMI_PHY_RX_SENSE0 = 0x10,
	HDMI_PHY_HPD = 0x02,
	HDMI_PHY_TX_PHY_LOCK = 0x01,

/* PHY_I2CM_SLAVE_ADDR field values */
	HDMI_PHY_I2CM_SLAVE_ADDR_PHY_GEN2 = 0x69,
	HDMI_PHY_I2CM_SLAVE_ADDR_HEAC_PHY = 0x49,

/* PHY_I2CM_OPERATION_ADDR field values */
	HDMI_PHY_I2CM_OPERATION_ADDR_WRITE = 0x10,
	HDMI_PHY_I2CM_OPERATION_ADDR_READ = 0x1,

/* HDMI_PHY_I2CM_INT_ADDR */
	HDMI_PHY_I2CM_INT_ADDR_DONE_POL = 0x08,
	HDMI_PHY_I2CM_INT_ADDR_DONE_MASK = 0x04,

/* HDMI_PHY_I2CM_CTLINT_ADDR */
	HDMI_PHY_I2CM_CTLINT_ADDR_NAC_POL = 0x80,
	HDMI_PHY_I2CM_CTLINT_ADDR_NAC_MASK = 0x40,
	HDMI_PHY_I2CM_CTLINT_ADDR_ARBITRATION_POL = 0x08,
	HDMI_PHY_I2CM_CTLINT_ADDR_ARBITRATION_MASK = 0x04,

/* AUD_CONF0 field values */
	HDMI_AUD_CONF0_SW_RESET = 0x80,
	HDMI_AUD_CONF0_I2S_SELECT = 0x20,
	HDMI_AUD_CONF0_I2S_EN3 = 0x08,
	HDMI_AUD_CONF0_I2S_EN2 = 0x04,
	HDMI_AUD_CONF0_I2S_EN1 = 0x02,
	HDMI_AUD_CONF0_I2S_EN0 = 0x01,

/* AUD_CONF1 field values */
	HDMI_AUD_CONF1_MODE_I2S = 0x00,
	HDMI_AUD_CONF1_MODE_RIGHT_J = 0x20,
	HDMI_AUD_CONF1_MODE_LEFT_J = 0x40,
	HDMI_AUD_CONF1_MODE_BURST_1 = 0x60,
	HDMI_AUD_CONF1_MODE_BURST_2 = 0x80,
	HDMI_AUD_CONF1_WIDTH_16 = 0x10,
	HDMI_AUD_CONF1_WIDTH_24 = 0x18,

/* AUD_CTS3 field values */
	HDMI_AUD_CTS3_N_SHIFT_OFFSET = 5,
	HDMI_AUD_CTS3_N_SHIFT_MASK = 0xe0,
	HDMI_AUD_CTS3_N_SHIFT_1 = 0,
	HDMI_AUD_CTS3_N_SHIFT_16 = 0x20,
	HDMI_AUD_CTS3_N_SHIFT_32 = 0x40,
	HDMI_AUD_CTS3_N_SHIFT_64 = 0x60,
	HDMI_AUD_CTS3_N_SHIFT_128 = 0x80,
	HDMI_AUD_CTS3_N_SHIFT_256 = 0xa0,
	/* note that the CTS3 MANUAL bit has been हटाओd
	   from our part. Can't set it, will पढ़ो as 0. */
	HDMI_AUD_CTS3_CTS_MANUAL = 0x10,
	HDMI_AUD_CTS3_AUDCTS19_16_MASK = 0x0f,

/* HDMI_AUD_INPUTCLKFS field values */
	HDMI_AUD_INPUTCLKFS_128FS = 0,
	HDMI_AUD_INPUTCLKFS_256FS = 1,
	HDMI_AUD_INPUTCLKFS_512FS = 2,
	HDMI_AUD_INPUTCLKFS_64FS = 4,

/* AHB_DMA_CONF0 field values */
	HDMI_AHB_DMA_CONF0_SW_FIFO_RST_OFFSET = 7,
	HDMI_AHB_DMA_CONF0_SW_FIFO_RST_MASK = 0x80,
	HDMI_AHB_DMA_CONF0_HBR = 0x10,
	HDMI_AHB_DMA_CONF0_EN_HLOCK_OFFSET = 3,
	HDMI_AHB_DMA_CONF0_EN_HLOCK_MASK = 0x08,
	HDMI_AHB_DMA_CONF0_INCR_TYPE_OFFSET = 1,
	HDMI_AHB_DMA_CONF0_INCR_TYPE_MASK = 0x06,
	HDMI_AHB_DMA_CONF0_INCR4 = 0x0,
	HDMI_AHB_DMA_CONF0_INCR8 = 0x2,
	HDMI_AHB_DMA_CONF0_INCR16 = 0x4,
	HDMI_AHB_DMA_CONF0_BURST_MODE = 0x1,

/* HDMI_AHB_DMA_START field values */
	HDMI_AHB_DMA_START_START_OFFSET = 0,
	HDMI_AHB_DMA_START_START_MASK = 0x01,

/* HDMI_AHB_DMA_STOP field values */
	HDMI_AHB_DMA_STOP_STOP_OFFSET = 0,
	HDMI_AHB_DMA_STOP_STOP_MASK = 0x01,

/* AHB_DMA_STAT, AHB_DMA_INT, AHB_DMA_MASK, AHB_DMA_POL field values */
	HDMI_AHB_DMA_DONE = 0x80,
	HDMI_AHB_DMA_RETRY_SPLIT = 0x40,
	HDMI_AHB_DMA_LOSTOWNERSHIP = 0x20,
	HDMI_AHB_DMA_ERROR = 0x10,
	HDMI_AHB_DMA_FIFO_THREMPTY = 0x04,
	HDMI_AHB_DMA_FIFO_FULL = 0x02,
	HDMI_AHB_DMA_FIFO_EMPTY = 0x01,

/* AHB_DMA_BUFFSTAT, AHB_DMA_BUFFINT,AHB_DMA_BUFFMASK,AHB_DMA_BUFFPOL values */
	HDMI_AHB_DMA_BUFFSTAT_FULL = 0x02,
	HDMI_AHB_DMA_BUFFSTAT_EMPTY = 0x01,

/* MC_CLKDIS field values */
	HDMI_MC_CLKDIS_HDCPCLK_DISABLE = 0x40,
	HDMI_MC_CLKDIS_CECCLK_DISABLE = 0x20,
	HDMI_MC_CLKDIS_CSCCLK_DISABLE = 0x10,
	HDMI_MC_CLKDIS_AUDCLK_DISABLE = 0x8,
	HDMI_MC_CLKDIS_PREPCLK_DISABLE = 0x4,
	HDMI_MC_CLKDIS_TMDSCLK_DISABLE = 0x2,
	HDMI_MC_CLKDIS_PIXELCLK_DISABLE = 0x1,

/* MC_SWRSTZ field values */
	HDMI_MC_SWRSTZ_I2SSWRST_REQ = 0x08,
	HDMI_MC_SWRSTZ_TMDSSWRST_REQ = 0x02,

/* MC_FLOWCTRL field values */
	HDMI_MC_FLOWCTRL_FEED_THROUGH_OFF_MASK = 0x1,
	HDMI_MC_FLOWCTRL_FEED_THROUGH_OFF_CSC_IN_PATH = 0x1,
	HDMI_MC_FLOWCTRL_FEED_THROUGH_OFF_CSC_BYPASS = 0x0,

/* MC_PHYRSTZ field values */
	HDMI_MC_PHYRSTZ_PHYRSTZ = 0x01,

/* MC_HEACPHY_RST field values */
	HDMI_MC_HEACPHY_RST_ASSERT = 0x1,
	HDMI_MC_HEACPHY_RST_DEASSERT = 0x0,

/* CSC_CFG field values */
	HDMI_CSC_CFG_INTMODE_MASK = 0x30,
	HDMI_CSC_CFG_INTMODE_OFFSET = 4,
	HDMI_CSC_CFG_INTMODE_DISABLE = 0x00,
	HDMI_CSC_CFG_INTMODE_CHROMA_INT_FORMULA1 = 0x10,
	HDMI_CSC_CFG_INTMODE_CHROMA_INT_FORMULA2 = 0x20,
	HDMI_CSC_CFG_DECMODE_MASK = 0x3,
	HDMI_CSC_CFG_DECMODE_OFFSET = 0,
	HDMI_CSC_CFG_DECMODE_DISABLE = 0x0,
	HDMI_CSC_CFG_DECMODE_CHROMA_INT_FORMULA1 = 0x1,
	HDMI_CSC_CFG_DECMODE_CHROMA_INT_FORMULA2 = 0x2,
	HDMI_CSC_CFG_DECMODE_CHROMA_INT_FORMULA3 = 0x3,

/* CSC_SCALE field values */
	HDMI_CSC_SCALE_CSC_COLORDE_PTH_MASK = 0xF0,
	HDMI_CSC_SCALE_CSC_COLORDE_PTH_24BPP = 0x00,
	HDMI_CSC_SCALE_CSC_COLORDE_PTH_30BPP = 0x50,
	HDMI_CSC_SCALE_CSC_COLORDE_PTH_36BPP = 0x60,
	HDMI_CSC_SCALE_CSC_COLORDE_PTH_48BPP = 0x70,
	HDMI_CSC_SCALE_CSCSCALE_MASK = 0x03,

/* A_HDCPCFG0 field values */
	HDMI_A_HDCPCFG0_ELVENA_MASK = 0x80,
	HDMI_A_HDCPCFG0_ELVENA_ENABLE = 0x80,
	HDMI_A_HDCPCFG0_ELVENA_DISABLE = 0x00,
	HDMI_A_HDCPCFG0_I2CFASTMODE_MASK = 0x40,
	HDMI_A_HDCPCFG0_I2CFASTMODE_ENABLE = 0x40,
	HDMI_A_HDCPCFG0_I2CFASTMODE_DISABLE = 0x00,
	HDMI_A_HDCPCFG0_BYPENCRYPTION_MASK = 0x20,
	HDMI_A_HDCPCFG0_BYPENCRYPTION_ENABLE = 0x20,
	HDMI_A_HDCPCFG0_BYPENCRYPTION_DISABLE = 0x00,
	HDMI_A_HDCPCFG0_SYNCRICHECK_MASK = 0x10,
	HDMI_A_HDCPCFG0_SYNCRICHECK_ENABLE = 0x10,
	HDMI_A_HDCPCFG0_SYNCRICHECK_DISABLE = 0x00,
	HDMI_A_HDCPCFG0_AVMUTE_MASK = 0x8,
	HDMI_A_HDCPCFG0_AVMUTE_ENABLE = 0x8,
	HDMI_A_HDCPCFG0_AVMUTE_DISABLE = 0x0,
	HDMI_A_HDCPCFG0_RXDETECT_MASK = 0x4,
	HDMI_A_HDCPCFG0_RXDETECT_ENABLE = 0x4,
	HDMI_A_HDCPCFG0_RXDETECT_DISABLE = 0x0,
	HDMI_A_HDCPCFG0_EN11FEATURE_MASK = 0x2,
	HDMI_A_HDCPCFG0_EN11FEATURE_ENABLE = 0x2,
	HDMI_A_HDCPCFG0_EN11FEATURE_DISABLE = 0x0,
	HDMI_A_HDCPCFG0_HDMIDVI_MASK = 0x1,
	HDMI_A_HDCPCFG0_HDMIDVI_HDMI = 0x1,
	HDMI_A_HDCPCFG0_HDMIDVI_DVI = 0x0,

/* A_HDCPCFG1 field values */
	HDMI_A_HDCPCFG1_DISSHA1CHECK_MASK = 0x8,
	HDMI_A_HDCPCFG1_DISSHA1CHECK_DISABLE = 0x8,
	HDMI_A_HDCPCFG1_DISSHA1CHECK_ENABLE = 0x0,
	HDMI_A_HDCPCFG1_PH2UPSHFTENC_MASK = 0x4,
	HDMI_A_HDCPCFG1_PH2UPSHFTENC_ENABLE = 0x4,
	HDMI_A_HDCPCFG1_PH2UPSHFTENC_DISABLE = 0x0,
	HDMI_A_HDCPCFG1_ENCRYPTIONDISABLE_MASK = 0x2,
	HDMI_A_HDCPCFG1_ENCRYPTIONDISABLE_DISABLE = 0x2,
	HDMI_A_HDCPCFG1_ENCRYPTIONDISABLE_ENABLE = 0x0,
	HDMI_A_HDCPCFG1_SWRESET_MASK = 0x1,
	HDMI_A_HDCPCFG1_SWRESET_ASSERT = 0x0,

/* A_VIDPOLCFG field values */
	HDMI_A_VIDPOLCFG_UNENCRYPTCONF_MASK = 0x60,
	HDMI_A_VIDPOLCFG_UNENCRYPTCONF_OFFSET = 5,
	HDMI_A_VIDPOLCFG_DATAENPOL_MASK = 0x10,
	HDMI_A_VIDPOLCFG_DATAENPOL_ACTIVE_HIGH = 0x10,
	HDMI_A_VIDPOLCFG_DATAENPOL_ACTIVE_LOW = 0x0,
	HDMI_A_VIDPOLCFG_VSYNCPOL_MASK = 0x8,
	HDMI_A_VIDPOLCFG_VSYNCPOL_ACTIVE_HIGH = 0x8,
	HDMI_A_VIDPOLCFG_VSYNCPOL_ACTIVE_LOW = 0x0,
	HDMI_A_VIDPOLCFG_HSYNCPOL_MASK = 0x2,
	HDMI_A_VIDPOLCFG_HSYNCPOL_ACTIVE_HIGH = 0x2,
	HDMI_A_VIDPOLCFG_HSYNCPOL_ACTIVE_LOW = 0x0,

/* I2CM_OPERATION field values */
	HDMI_I2CM_OPERATION_WRITE = 0x10,
	HDMI_I2CM_OPERATION_READ_EXT = 0x2,
	HDMI_I2CM_OPERATION_READ = 0x1,

/* I2CM_INT field values */
	HDMI_I2CM_INT_DONE_POL = 0x8,
	HDMI_I2CM_INT_DONE_MASK = 0x4,

/* I2CM_CTLINT field values */
	HDMI_I2CM_CTLINT_NAC_POL = 0x80,
	HDMI_I2CM_CTLINT_NAC_MASK = 0x40,
	HDMI_I2CM_CTLINT_ARB_POL = 0x8,
	HDMI_I2CM_CTLINT_ARB_MASK = 0x4,
पूर्ण;

/*
 * HDMI 3D TX PHY रेजिस्टरs
 */
#घोषणा HDMI_3D_TX_PHY_PWRCTRL			0x00
#घोषणा HDMI_3D_TX_PHY_SERDIVCTRL		0x01
#घोषणा HDMI_3D_TX_PHY_SERCKCTRL		0x02
#घोषणा HDMI_3D_TX_PHY_SERCKKILLCTRL		0x03
#घोषणा HDMI_3D_TX_PHY_TXRESCTRL		0x04
#घोषणा HDMI_3D_TX_PHY_CKCALCTRL		0x05
#घोषणा HDMI_3D_TX_PHY_CPCE_CTRL		0x06
#घोषणा HDMI_3D_TX_PHY_TXCLKMEASCTRL		0x07
#घोषणा HDMI_3D_TX_PHY_TXMEASCTRL		0x08
#घोषणा HDMI_3D_TX_PHY_CKSYMTXCTRL		0x09
#घोषणा HDMI_3D_TX_PHY_CMPSEQCTRL		0x0a
#घोषणा HDMI_3D_TX_PHY_CMPPWRCTRL		0x0b
#घोषणा HDMI_3D_TX_PHY_CMPMODECTRL		0x0c
#घोषणा HDMI_3D_TX_PHY_MEASCTRL			0x0d
#घोषणा HDMI_3D_TX_PHY_VLEVCTRL			0x0e
#घोषणा HDMI_3D_TX_PHY_D2ACTRL			0x0f
#घोषणा HDMI_3D_TX_PHY_CURRCTRL			0x10
#घोषणा HDMI_3D_TX_PHY_DRVANACTRL		0x11
#घोषणा HDMI_3D_TX_PHY_PLLMEASCTRL		0x12
#घोषणा HDMI_3D_TX_PHY_PLLPHBYCTRL		0x13
#घोषणा HDMI_3D_TX_PHY_GRP_CTRL			0x14
#घोषणा HDMI_3D_TX_PHY_GMPCTRL			0x15
#घोषणा HDMI_3D_TX_PHY_MPLLMEASCTRL		0x16
#घोषणा HDMI_3D_TX_PHY_MSM_CTRL			0x17
#घोषणा HDMI_3D_TX_PHY_SCRPB_STATUS		0x18
#घोषणा HDMI_3D_TX_PHY_TXTERM			0x19
#घोषणा HDMI_3D_TX_PHY_PTRPT_ENBL		0x1a
#घोषणा HDMI_3D_TX_PHY_PATTERNGEN		0x1b
#घोषणा HDMI_3D_TX_PHY_SDCAP_MODE		0x1c
#घोषणा HDMI_3D_TX_PHY_SCOPEMODE		0x1d
#घोषणा HDMI_3D_TX_PHY_DIGTXMODE		0x1e
#घोषणा HDMI_3D_TX_PHY_STR_STATUS		0x1f
#घोषणा HDMI_3D_TX_PHY_SCOPECNT0		0x20
#घोषणा HDMI_3D_TX_PHY_SCOPECNT1		0x21
#घोषणा HDMI_3D_TX_PHY_SCOPECNT2		0x22
#घोषणा HDMI_3D_TX_PHY_SCOPECNTCLK		0x23
#घोषणा HDMI_3D_TX_PHY_SCOPESAMPLE		0x24
#घोषणा HDMI_3D_TX_PHY_SCOPECNTMSB01		0x25
#घोषणा HDMI_3D_TX_PHY_SCOPECNTMSB2CK		0x26

/* HDMI_3D_TX_PHY_CKCALCTRL values */
#घोषणा HDMI_3D_TX_PHY_CKCALCTRL_OVERRIDE		BIT(15)

/* HDMI_3D_TX_PHY_MSM_CTRL values */
#घोषणा HDMI_3D_TX_PHY_MSM_CTRL_MPLL_PH_SEL_CK		BIT(13)
#घोषणा HDMI_3D_TX_PHY_MSM_CTRL_CKO_SEL_CLK_REF_MPLL	(0 << 1)
#घोषणा HDMI_3D_TX_PHY_MSM_CTRL_CKO_SEL_OFF		(1 << 1)
#घोषणा HDMI_3D_TX_PHY_MSM_CTRL_CKO_SEL_PCLK		(2 << 1)
#घोषणा HDMI_3D_TX_PHY_MSM_CTRL_CKO_SEL_FB_CLK		(3 << 1)
#घोषणा HDMI_3D_TX_PHY_MSM_CTRL_SCOPE_CK_SEL		BIT(0)

/* HDMI_3D_TX_PHY_PTRPT_ENBL values */
#घोषणा HDMI_3D_TX_PHY_PTRPT_ENBL_OVERRIDE		BIT(15)
#घोषणा HDMI_3D_TX_PHY_PTRPT_ENBL_PG_SKIP_BIT2		BIT(8)
#घोषणा HDMI_3D_TX_PHY_PTRPT_ENBL_PG_SKIP_BIT1		BIT(7)
#घोषणा HDMI_3D_TX_PHY_PTRPT_ENBL_PG_SKIP_BIT0		BIT(6)
#घोषणा HDMI_3D_TX_PHY_PTRPT_ENBL_CK_REF_ENB		BIT(5)
#घोषणा HDMI_3D_TX_PHY_PTRPT_ENBL_RCAL_ENB		BIT(4)
#घोषणा HDMI_3D_TX_PHY_PTRPT_ENBL_TX_CLK_ALIGN_ENB	BIT(3)
#घोषणा HDMI_3D_TX_PHY_PTRPT_ENBL_TX_READY		BIT(2)
#घोषणा HDMI_3D_TX_PHY_PTRPT_ENBL_CKO_WORD_ENB		BIT(1)
#घोषणा HDMI_3D_TX_PHY_PTRPT_ENBL_REFCLK_ENB		BIT(0)

#पूर्ण_अगर /* __DW_HDMI_H__ */
