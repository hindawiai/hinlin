<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * cx88x-hw.h - CX2388x रेजिस्टर offsets
 *
 * Copyright (C) 1996,97,98 Ralph Metzler (rjkm@thp.uni-koeln.de)
 *		  2001 Michael Eskin
 *		  2002 Yurij Sysoev <yurij@naturesoft.net>
 *		  2003 Gerd Knorr <kraxel@bytesex.org>
 */

#अगर_अघोषित _CX88_REG_H_
#घोषणा _CX88_REG_H_

/*
 * PCI IDs and config space
 */

#अगर_अघोषित PCI_VENDOR_ID_CONEXANT
# define PCI_VENDOR_ID_CONEXANT		0x14F1
#पूर्ण_अगर
#अगर_अघोषित PCI_DEVICE_ID_CX2300_VID
# define PCI_DEVICE_ID_CX2300_VID	0x8800
#पूर्ण_अगर

#घोषणा CX88X_DEVCTRL 0x40
#घोषणा CX88X_EN_TBFX 0x02
#घोषणा CX88X_EN_VSFX 0x04

/*
 * PCI controller रेजिस्टरs
 */

/* Command and Status Register */
#घोषणा F0_CMD_STAT_MM      0x2f0004
#घोषणा F1_CMD_STAT_MM      0x2f0104
#घोषणा F2_CMD_STAT_MM      0x2f0204
#घोषणा F3_CMD_STAT_MM      0x2f0304
#घोषणा F4_CMD_STAT_MM      0x2f0404

/* Device Control #1 */
#घोषणा F0_DEV_CNTRL1_MM    0x2f0040
#घोषणा F1_DEV_CNTRL1_MM    0x2f0140
#घोषणा F2_DEV_CNTRL1_MM    0x2f0240
#घोषणा F3_DEV_CNTRL1_MM    0x2f0340
#घोषणा F4_DEV_CNTRL1_MM    0x2f0440

/* Device Control #1 */
#घोषणा F0_BAR0_MM          0x2f0010
#घोषणा F1_BAR0_MM          0x2f0110
#घोषणा F2_BAR0_MM          0x2f0210
#घोषणा F3_BAR0_MM          0x2f0310
#घोषणा F4_BAR0_MM          0x2f0410

/*
 * DMA Controller रेजिस्टरs
 */

#घोषणा MO_PDMA_STHRSH      0x200000 // Source threshold
#घोषणा MO_PDMA_STADRS      0x200004 // Source target address
#घोषणा MO_PDMA_SIADRS      0x200008 // Source पूर्णांकernal address
#घोषणा MO_PDMA_SCNTRL      0x20000C // Source control
#घोषणा MO_PDMA_DTHRSH      0x200010 // Destination threshold
#घोषणा MO_PDMA_DTADRS      0x200014 // Destination target address
#घोषणा MO_PDMA_DIADRS      0x200018 // Destination पूर्णांकernal address
#घोषणा MO_PDMA_DCNTRL      0x20001C // Destination control
#घोषणा MO_LD_SSID          0x200030 // Load subप्रणाली ID
#घोषणा MO_DEV_CNTRL2       0x200034 // Device control
#घोषणा MO_PCI_INTMSK       0x200040 // PCI पूर्णांकerrupt mask
#घोषणा MO_PCI_INTSTAT      0x200044 // PCI पूर्णांकerrupt status
#घोषणा MO_PCI_INTMSTAT     0x200048 // PCI पूर्णांकerrupt masked status
#घोषणा MO_VID_INTMSK       0x200050 // Video पूर्णांकerrupt mask
#घोषणा MO_VID_INTSTAT      0x200054 // Video पूर्णांकerrupt status
#घोषणा MO_VID_INTMSTAT     0x200058 // Video पूर्णांकerrupt masked status
#घोषणा MO_VID_INTSSTAT     0x20005C // Video पूर्णांकerrupt set status
#घोषणा MO_AUD_INTMSK       0x200060 // Audio पूर्णांकerrupt mask
#घोषणा MO_AUD_INTSTAT      0x200064 // Audio पूर्णांकerrupt status
#घोषणा MO_AUD_INTMSTAT     0x200068 // Audio पूर्णांकerrupt masked status
#घोषणा MO_AUD_INTSSTAT     0x20006C // Audio पूर्णांकerrupt set status
#घोषणा MO_TS_INTMSK        0x200070 // Transport stream पूर्णांकerrupt mask
#घोषणा MO_TS_INTSTAT       0x200074 // Transport stream पूर्णांकerrupt status
#घोषणा MO_TS_INTMSTAT      0x200078 // Transport stream पूर्णांकerrupt mask status
#घोषणा MO_TS_INTSSTAT      0x20007C // Transport stream पूर्णांकerrupt set status
#घोषणा MO_VIP_INTMSK       0x200080 // VIP पूर्णांकerrupt mask
#घोषणा MO_VIP_INTSTAT      0x200084 // VIP पूर्णांकerrupt status
#घोषणा MO_VIP_INTMSTAT     0x200088 // VIP पूर्णांकerrupt masked status
#घोषणा MO_VIP_INTSSTAT     0x20008C // VIP पूर्णांकerrupt set status
#घोषणा MO_GPHST_INTMSK     0x200090 // Host पूर्णांकerrupt mask
#घोषणा MO_GPHST_INTSTAT    0x200094 // Host पूर्णांकerrupt status
#घोषणा MO_GPHST_INTMSTAT   0x200098 // Host पूर्णांकerrupt masked status
#घोषणा MO_GPHST_INTSSTAT   0x20009C // Host पूर्णांकerrupt set status

// DMA Channels 1-6 beदीर्घ to SPIPE
#घोषणा MO_DMA7_PTR1        0x300018 // अणु24पूर्णRW* DMA Current Ptr : Ch#7
#घोषणा MO_DMA8_PTR1        0x30001C // अणु24पूर्णRW* DMA Current Ptr : Ch#8

// DMA Channels 9-20 beदीर्घ to SPIPE
#घोषणा MO_DMA21_PTR1       0x300080 // अणु24पूर्णR0* DMA Current Ptr : Ch#21
#घोषणा MO_DMA22_PTR1       0x300084 // अणु24पूर्णR0* DMA Current Ptr : Ch#22
#घोषणा MO_DMA23_PTR1       0x300088 // अणु24पूर्णR0* DMA Current Ptr : Ch#23
#घोषणा MO_DMA24_PTR1       0x30008C // अणु24पूर्णR0* DMA Current Ptr : Ch#24
#घोषणा MO_DMA25_PTR1       0x300090 // अणु24पूर्णR0* DMA Current Ptr : Ch#25
#घोषणा MO_DMA26_PTR1       0x300094 // अणु24पूर्णR0* DMA Current Ptr : Ch#26
#घोषणा MO_DMA27_PTR1       0x300098 // अणु24पूर्णR0* DMA Current Ptr : Ch#27
#घोषणा MO_DMA28_PTR1       0x30009C // अणु24पूर्णR0* DMA Current Ptr : Ch#28
#घोषणा MO_DMA29_PTR1       0x3000A0 // अणु24पूर्णR0* DMA Current Ptr : Ch#29
#घोषणा MO_DMA30_PTR1       0x3000A4 // अणु24पूर्णR0* DMA Current Ptr : Ch#30
#घोषणा MO_DMA31_PTR1       0x3000A8 // अणु24पूर्णR0* DMA Current Ptr : Ch#31
#घोषणा MO_DMA32_PTR1       0x3000AC // अणु24पूर्णR0* DMA Current Ptr : Ch#32

#घोषणा MO_DMA21_PTR2       0x3000C0 // अणु24पूर्णRW* DMA Tab Ptr : Ch#21
#घोषणा MO_DMA22_PTR2       0x3000C4 // अणु24पूर्णRW* DMA Tab Ptr : Ch#22
#घोषणा MO_DMA23_PTR2       0x3000C8 // अणु24पूर्णRW* DMA Tab Ptr : Ch#23
#घोषणा MO_DMA24_PTR2       0x3000CC // अणु24पूर्णRW* DMA Tab Ptr : Ch#24
#घोषणा MO_DMA25_PTR2       0x3000D0 // अणु24पूर्णRW* DMA Tab Ptr : Ch#25
#घोषणा MO_DMA26_PTR2       0x3000D4 // अणु24पूर्णRW* DMA Tab Ptr : Ch#26
#घोषणा MO_DMA27_PTR2       0x3000D8 // अणु24पूर्णRW* DMA Tab Ptr : Ch#27
#घोषणा MO_DMA28_PTR2       0x3000DC // अणु24पूर्णRW* DMA Tab Ptr : Ch#28
#घोषणा MO_DMA29_PTR2       0x3000E0 // अणु24पूर्णRW* DMA Tab Ptr : Ch#29
#घोषणा MO_DMA30_PTR2       0x3000E4 // अणु24पूर्णRW* DMA Tab Ptr : Ch#30
#घोषणा MO_DMA31_PTR2       0x3000E8 // अणु24पूर्णRW* DMA Tab Ptr : Ch#31
#घोषणा MO_DMA32_PTR2       0x3000EC // अणु24पूर्णRW* DMA Tab Ptr : Ch#32

#घोषणा MO_DMA21_CNT1       0x300100 // अणु11पूर्णRW* DMA Buffer Size : Ch#21
#घोषणा MO_DMA22_CNT1       0x300104 // अणु11पूर्णRW* DMA Buffer Size : Ch#22
#घोषणा MO_DMA23_CNT1       0x300108 // अणु11पूर्णRW* DMA Buffer Size : Ch#23
#घोषणा MO_DMA24_CNT1       0x30010C // अणु11पूर्णRW* DMA Buffer Size : Ch#24
#घोषणा MO_DMA25_CNT1       0x300110 // अणु11पूर्णRW* DMA Buffer Size : Ch#25
#घोषणा MO_DMA26_CNT1       0x300114 // अणु11पूर्णRW* DMA Buffer Size : Ch#26
#घोषणा MO_DMA27_CNT1       0x300118 // अणु11पूर्णRW* DMA Buffer Size : Ch#27
#घोषणा MO_DMA28_CNT1       0x30011C // अणु11पूर्णRW* DMA Buffer Size : Ch#28
#घोषणा MO_DMA29_CNT1       0x300120 // अणु11पूर्णRW* DMA Buffer Size : Ch#29
#घोषणा MO_DMA30_CNT1       0x300124 // अणु11पूर्णRW* DMA Buffer Size : Ch#30
#घोषणा MO_DMA31_CNT1       0x300128 // अणु11पूर्णRW* DMA Buffer Size : Ch#31
#घोषणा MO_DMA32_CNT1       0x30012C // अणु11पूर्णRW* DMA Buffer Size : Ch#32

#घोषणा MO_DMA21_CNT2       0x300140 // अणु11पूर्णRW* DMA Table Size : Ch#21
#घोषणा MO_DMA22_CNT2       0x300144 // अणु11पूर्णRW* DMA Table Size : Ch#22
#घोषणा MO_DMA23_CNT2       0x300148 // अणु11पूर्णRW* DMA Table Size : Ch#23
#घोषणा MO_DMA24_CNT2       0x30014C // अणु11पूर्णRW* DMA Table Size : Ch#24
#घोषणा MO_DMA25_CNT2       0x300150 // अणु11पूर्णRW* DMA Table Size : Ch#25
#घोषणा MO_DMA26_CNT2       0x300154 // अणु11पूर्णRW* DMA Table Size : Ch#26
#घोषणा MO_DMA27_CNT2       0x300158 // अणु11पूर्णRW* DMA Table Size : Ch#27
#घोषणा MO_DMA28_CNT2       0x30015C // अणु11पूर्णRW* DMA Table Size : Ch#28
#घोषणा MO_DMA29_CNT2       0x300160 // अणु11पूर्णRW* DMA Table Size : Ch#29
#घोषणा MO_DMA30_CNT2       0x300164 // अणु11पूर्णRW* DMA Table Size : Ch#30
#घोषणा MO_DMA31_CNT2       0x300168 // अणु11पूर्णRW* DMA Table Size : Ch#31
#घोषणा MO_DMA32_CNT2       0x30016C // अणु11पूर्णRW* DMA Table Size : Ch#32

/*
 * Video रेजिस्टरs
 */

#घोषणा MO_VIDY_DMA         0x310000 // अणु64पूर्णRWp Video Y
#घोषणा MO_VIDU_DMA         0x310008 // अणु64पूर्णRWp Video U
#घोषणा MO_VIDV_DMA         0x310010 // अणु64पूर्णRWp Video V
#घोषणा MO_VBI_DMA          0x310018 // अणु64पूर्णRWp VBI (Vertical blanking पूर्णांकerval)

#घोषणा MO_DEVICE_STATUS    0x310100
#घोषणा MO_INPUT_FORMAT     0x310104
#घोषणा MO_AGC_BURST        0x31010c
#घोषणा MO_CONTR_BRIGHT     0x310110
#घोषणा MO_UV_SATURATION    0x310114
#घोषणा MO_HUE              0x310118
#घोषणा MO_HTOTAL           0x310120
#घोषणा MO_HDELAY_EVEN      0x310124
#घोषणा MO_HDELAY_ODD       0x310128
#घोषणा MO_VDELAY_ODD       0x31012c
#घोषणा MO_VDELAY_EVEN      0x310130
#घोषणा MO_HACTIVE_EVEN     0x31013c
#घोषणा MO_HACTIVE_ODD      0x310140
#घोषणा MO_VACTIVE_EVEN     0x310144
#घोषणा MO_VACTIVE_ODD      0x310148
#घोषणा MO_HSCALE_EVEN      0x31014c
#घोषणा MO_HSCALE_ODD       0x310150
#घोषणा MO_VSCALE_EVEN      0x310154
#घोषणा MO_FILTER_EVEN      0x31015c
#घोषणा MO_VSCALE_ODD       0x310158
#घोषणा MO_FILTER_ODD       0x310160
#घोषणा MO_OUTPUT_FORMAT    0x310164

#घोषणा MO_PLL_REG          0x310168 // PLL रेजिस्टर
#घोषणा MO_PLL_ADJ_CTRL     0x31016c // PLL adjust control रेजिस्टर
#घोषणा MO_SCONV_REG        0x310170 // sample rate conversion रेजिस्टर
#घोषणा MO_SCONV_FIFO       0x310174 // sample rate conversion fअगरo
#घोषणा MO_SUB_STEP         0x310178 // subcarrier step size
#घोषणा MO_SUB_STEP_DR      0x31017c // subcarrier step size क्रम DR line

#घोषणा MO_CAPTURE_CTRL     0x310180 // capture control
#घोषणा MO_COLOR_CTRL       0x310184
#घोषणा MO_VBI_PACKET       0x310188 // vbi packet size / delay
#घोषणा MO_FIELD_COUNT      0x310190 // field counter
#घोषणा MO_VIP_CONFIG       0x310194
#घोषणा MO_VBOS_CONTROL	    0x3101a8

#घोषणा MO_AGC_BACK_VBI     0x310200
#घोषणा MO_AGC_SYNC_TIP1    0x310208

#घोषणा MO_VIDY_GPCNT       0x31C020 // अणु16पूर्णRO Video Y general purpose counter
#घोषणा MO_VIDU_GPCNT       0x31C024 // अणु16पूर्णRO Video U general purpose counter
#घोषणा MO_VIDV_GPCNT       0x31C028 // अणु16पूर्णRO Video V general purpose counter
#घोषणा MO_VBI_GPCNT        0x31C02C // अणु16पूर्णRO VBI general purpose counter
#घोषणा MO_VIDY_GPCNTRL     0x31C030 // अणु2पूर्णWO Video Y general purpose control
#घोषणा MO_VIDU_GPCNTRL     0x31C034 // अणु2पूर्णWO Video U general purpose control
#घोषणा MO_VIDV_GPCNTRL     0x31C038 // अणु2पूर्णWO Video V general purpose control
#घोषणा MO_VBI_GPCNTRL      0x31C03C // अणु2पूर्णWO VBI general purpose counter
#घोषणा MO_VID_DMACNTRL     0x31C040 // अणु8पूर्णRW Video DMA control
#घोषणा MO_VID_XFR_STAT     0x31C044 // अणु1पूर्णRO Video transfer status

/*
 * audio रेजिस्टरs
 */

#घोषणा MO_AUDD_DMA         0x320000 // अणु64पूर्णRWp Audio करोwnstream
#घोषणा MO_AUDU_DMA         0x320008 // अणु64पूर्णRWp Audio upstream
#घोषणा MO_AUDR_DMA         0x320010 // अणु64पूर्णRWp Audio RDS (करोwnstream)
#घोषणा MO_AUDD_GPCNT       0x32C020 // अणु16पूर्णRO Audio करोwn general purpose counter
#घोषणा MO_AUDU_GPCNT       0x32C024 // अणु16पूर्णRO Audio up general purpose counter
#घोषणा MO_AUDR_GPCNT       0x32C028 // अणु16पूर्णRO Audio RDS general purpose counter
#घोषणा MO_AUDD_GPCNTRL     0x32C030 // अणु2पूर्णWO Audio करोwn general purpose control
#घोषणा MO_AUDU_GPCNTRL     0x32C034 // अणु2पूर्णWO Audio up general purpose control
#घोषणा MO_AUDR_GPCNTRL     0x32C038 // अणु2पूर्णWO Audio RDS general purpose control
#घोषणा MO_AUD_DMACNTRL     0x32C040 // अणु6पूर्णRW Audio DMA control
#घोषणा MO_AUD_XFR_STAT     0x32C044 // अणु1पूर्णRO Audio transfer status
#घोषणा MO_AUDD_LNGTH       0x32C048 // अणु12पूर्णRW Audio करोwn line length
#घोषणा MO_AUDR_LNGTH       0x32C04C // अणु12पूर्णRW Audio RDS line length

#घोषणा AUD_INIT                 0x320100
#घोषणा AUD_INIT_LD              0x320104
#घोषणा AUD_SOFT_RESET           0x320108
#घोषणा AUD_I2SINPUTCNTL         0x320120
#घोषणा AUD_BAUDRATE             0x320124
#घोषणा AUD_I2SOUTPUTCNTL        0x320128
#घोषणा AAGC_HYST                0x320134
#घोषणा AAGC_GAIN                0x320138
#घोषणा AAGC_DEF                 0x32013c
#घोषणा AUD_IIR1_0_SEL           0x320150
#घोषणा AUD_IIR1_0_SHIFT         0x320154
#घोषणा AUD_IIR1_1_SEL           0x320158
#घोषणा AUD_IIR1_1_SHIFT         0x32015c
#घोषणा AUD_IIR1_2_SEL           0x320160
#घोषणा AUD_IIR1_2_SHIFT         0x320164
#घोषणा AUD_IIR1_3_SEL           0x320168
#घोषणा AUD_IIR1_3_SHIFT         0x32016c
#घोषणा AUD_IIR1_4_SEL           0x320170
#घोषणा AUD_IIR1_4_SHIFT         0x32017c
#घोषणा AUD_IIR1_5_SEL           0x320180
#घोषणा AUD_IIR1_5_SHIFT         0x320184
#घोषणा AUD_IIR2_0_SEL           0x320190
#घोषणा AUD_IIR2_0_SHIFT         0x320194
#घोषणा AUD_IIR2_1_SEL           0x320198
#घोषणा AUD_IIR2_1_SHIFT         0x32019c
#घोषणा AUD_IIR2_2_SEL           0x3201a0
#घोषणा AUD_IIR2_2_SHIFT         0x3201a4
#घोषणा AUD_IIR2_3_SEL           0x3201a8
#घोषणा AUD_IIR2_3_SHIFT         0x3201ac
#घोषणा AUD_IIR3_0_SEL           0x3201c0
#घोषणा AUD_IIR3_0_SHIFT         0x3201c4
#घोषणा AUD_IIR3_1_SEL           0x3201c8
#घोषणा AUD_IIR3_1_SHIFT         0x3201cc
#घोषणा AUD_IIR3_2_SEL           0x3201d0
#घोषणा AUD_IIR3_2_SHIFT         0x3201d4
#घोषणा AUD_IIR4_0_SEL           0x3201e0
#घोषणा AUD_IIR4_0_SHIFT         0x3201e4
#घोषणा AUD_IIR4_1_SEL           0x3201e8
#घोषणा AUD_IIR4_1_SHIFT         0x3201ec
#घोषणा AUD_IIR4_2_SEL           0x3201f0
#घोषणा AUD_IIR4_2_SHIFT         0x3201f4
#घोषणा AUD_IIR4_0_CA0           0x320200
#घोषणा AUD_IIR4_0_CA1           0x320204
#घोषणा AUD_IIR4_0_CA2           0x320208
#घोषणा AUD_IIR4_0_CB0           0x32020c
#घोषणा AUD_IIR4_0_CB1           0x320210
#घोषणा AUD_IIR4_1_CA0           0x320214
#घोषणा AUD_IIR4_1_CA1           0x320218
#घोषणा AUD_IIR4_1_CA2           0x32021c
#घोषणा AUD_IIR4_1_CB0           0x320220
#घोषणा AUD_IIR4_1_CB1           0x320224
#घोषणा AUD_IIR4_2_CA0           0x320228
#घोषणा AUD_IIR4_2_CA1           0x32022c
#घोषणा AUD_IIR4_2_CA2           0x320230
#घोषणा AUD_IIR4_2_CB0           0x320234
#घोषणा AUD_IIR4_2_CB1           0x320238
#घोषणा AUD_HP_MD_IIR4_1         0x320250
#घोषणा AUD_HP_PROG_IIR4_1       0x320254
#घोषणा AUD_FM_MODE_ENABLE       0x320258
#घोषणा AUD_POLY0_DDS_CONSTANT   0x320270
#घोषणा AUD_DN0_FREQ             0x320274
#घोषणा AUD_DN1_FREQ             0x320278
#घोषणा AUD_DN1_FREQ_SHIFT       0x32027c
#घोषणा AUD_DN1_AFC              0x320280
#घोषणा AUD_DN1_SRC_SEL          0x320284
#घोषणा AUD_DN1_SHFT             0x320288
#घोषणा AUD_DN2_FREQ             0x32028c
#घोषणा AUD_DN2_FREQ_SHIFT       0x320290
#घोषणा AUD_DN2_AFC              0x320294
#घोषणा AUD_DN2_SRC_SEL          0x320298
#घोषणा AUD_DN2_SHFT             0x32029c
#घोषणा AUD_CRDC0_SRC_SEL        0x320300
#घोषणा AUD_CRDC0_SHIFT          0x320304
#घोषणा AUD_CORDIC_SHIFT_0       0x320308
#घोषणा AUD_CRDC1_SRC_SEL        0x32030c
#घोषणा AUD_CRDC1_SHIFT          0x320310
#घोषणा AUD_CORDIC_SHIFT_1       0x320314
#घोषणा AUD_DCOC_0_SRC           0x320320
#घोषणा AUD_DCOC0_SHIFT          0x320324
#घोषणा AUD_DCOC_0_SHIFT_IN0     0x320328
#घोषणा AUD_DCOC_0_SHIFT_IN1     0x32032c
#घोषणा AUD_DCOC_1_SRC           0x320330
#घोषणा AUD_DCOC1_SHIFT          0x320334
#घोषणा AUD_DCOC_1_SHIFT_IN0     0x320338
#घोषणा AUD_DCOC_1_SHIFT_IN1     0x32033c
#घोषणा AUD_DCOC_2_SRC           0x320340
#घोषणा AUD_DCOC2_SHIFT          0x320344
#घोषणा AUD_DCOC_2_SHIFT_IN0     0x320348
#घोषणा AUD_DCOC_2_SHIFT_IN1     0x32034c
#घोषणा AUD_DCOC_PASS_IN         0x320350
#घोषणा AUD_PDET_SRC             0x320370
#घोषणा AUD_PDET_SHIFT           0x320374
#घोषणा AUD_PILOT_BQD_1_K0       0x320380
#घोषणा AUD_PILOT_BQD_1_K1       0x320384
#घोषणा AUD_PILOT_BQD_1_K2       0x320388
#घोषणा AUD_PILOT_BQD_1_K3       0x32038c
#घोषणा AUD_PILOT_BQD_1_K4       0x320390
#घोषणा AUD_PILOT_BQD_2_K0       0x320394
#घोषणा AUD_PILOT_BQD_2_K1       0x320398
#घोषणा AUD_PILOT_BQD_2_K2       0x32039c
#घोषणा AUD_PILOT_BQD_2_K3       0x3203a0
#घोषणा AUD_PILOT_BQD_2_K4       0x3203a4
#घोषणा AUD_THR_FR               0x3203c0
#घोषणा AUD_X_PROG               0x3203c4
#घोषणा AUD_Y_PROG               0x3203c8
#घोषणा AUD_HARMONIC_MULT        0x3203cc
#घोषणा AUD_C1_UP_THR            0x3203d0
#घोषणा AUD_C1_LO_THR            0x3203d4
#घोषणा AUD_C2_UP_THR            0x3203d8
#घोषणा AUD_C2_LO_THR            0x3203dc
#घोषणा AUD_PLL_EN               0x320400
#घोषणा AUD_PLL_SRC              0x320404
#घोषणा AUD_PLL_SHIFT            0x320408
#घोषणा AUD_PLL_IF_SEL           0x32040c
#घोषणा AUD_PLL_IF_SHIFT         0x320410
#घोषणा AUD_BIQUAD_PLL_K0        0x320414
#घोषणा AUD_BIQUAD_PLL_K1        0x320418
#घोषणा AUD_BIQUAD_PLL_K2        0x32041c
#घोषणा AUD_BIQUAD_PLL_K3        0x320420
#घोषणा AUD_BIQUAD_PLL_K4        0x320424
#घोषणा AUD_DEEMPH0_SRC_SEL      0x320440
#घोषणा AUD_DEEMPH0_SHIFT        0x320444
#घोषणा AUD_DEEMPH0_G0           0x320448
#घोषणा AUD_DEEMPH0_A0           0x32044c
#घोषणा AUD_DEEMPH0_B0           0x320450
#घोषणा AUD_DEEMPH0_A1           0x320454
#घोषणा AUD_DEEMPH0_B1           0x320458
#घोषणा AUD_DEEMPH1_SRC_SEL      0x32045c
#घोषणा AUD_DEEMPH1_SHIFT        0x320460
#घोषणा AUD_DEEMPH1_G0           0x320464
#घोषणा AUD_DEEMPH1_A0           0x320468
#घोषणा AUD_DEEMPH1_B0           0x32046c
#घोषणा AUD_DEEMPH1_A1           0x320470
#घोषणा AUD_DEEMPH1_B1           0x320474
#घोषणा AUD_OUT0_SEL             0x320490
#घोषणा AUD_OUT0_SHIFT           0x320494
#घोषणा AUD_OUT1_SEL             0x320498
#घोषणा AUD_OUT1_SHIFT           0x32049c
#घोषणा AUD_RDSI_SEL             0x3204a0
#घोषणा AUD_RDSI_SHIFT           0x3204a4
#घोषणा AUD_RDSQ_SEL             0x3204a8
#घोषणा AUD_RDSQ_SHIFT           0x3204ac
#घोषणा AUD_DBX_IN_GAIN          0x320500
#घोषणा AUD_DBX_WBE_GAIN         0x320504
#घोषणा AUD_DBX_SE_GAIN          0x320508
#घोषणा AUD_DBX_RMS_WBE          0x32050c
#घोषणा AUD_DBX_RMS_SE           0x320510
#घोषणा AUD_DBX_SE_BYPASS        0x320514
#घोषणा AUD_FAWDETCTL            0x320530
#घोषणा AUD_FAWDETWINCTL         0x320534
#घोषणा AUD_DEEMPHGAIN_R         0x320538
#घोषणा AUD_DEEMPHNUMER1_R       0x32053c
#घोषणा AUD_DEEMPHNUMER2_R       0x320540
#घोषणा AUD_DEEMPHDENOM1_R       0x320544
#घोषणा AUD_DEEMPHDENOM2_R       0x320548
#घोषणा AUD_ERRLOGPERIOD_R       0x32054c
#घोषणा AUD_ERRINTRPTTHSHLD1_R   0x320550
#घोषणा AUD_ERRINTRPTTHSHLD2_R   0x320554
#घोषणा AUD_ERRINTRPTTHSHLD3_R   0x320558
#घोषणा AUD_NICAM_STATUS1        0x32055c
#घोषणा AUD_NICAM_STATUS2        0x320560
#घोषणा AUD_ERRLOG1              0x320564
#घोषणा AUD_ERRLOG2              0x320568
#घोषणा AUD_ERRLOG3              0x32056c
#घोषणा AUD_DAC_BYPASS_L         0x320580
#घोषणा AUD_DAC_BYPASS_R         0x320584
#घोषणा AUD_DAC_BYPASS_CTL       0x320588
#घोषणा AUD_CTL                  0x32058c
#घोषणा AUD_STATUS               0x320590
#घोषणा AUD_VOL_CTL              0x320594
#घोषणा AUD_BAL_CTL              0x320598
#घोषणा AUD_START_TIMER          0x3205b0
#घोषणा AUD_MODE_CHG_TIMER       0x3205b4
#घोषणा AUD_POLYPH80SCALEFAC     0x3205b8
#घोषणा AUD_DMD_RA_DDS           0x3205bc
#घोषणा AUD_I2S_RA_DDS           0x3205c0
#घोषणा AUD_RATE_THRES_DMD       0x3205d0
#घोषणा AUD_RATE_THRES_I2S       0x3205d4
#घोषणा AUD_RATE_ADJ1            0x3205d8
#घोषणा AUD_RATE_ADJ2            0x3205dc
#घोषणा AUD_RATE_ADJ3            0x3205e0
#घोषणा AUD_RATE_ADJ4            0x3205e4
#घोषणा AUD_RATE_ADJ5            0x3205e8
#घोषणा AUD_APB_IN_RATE_ADJ      0x3205ec
#घोषणा AUD_I2SCNTL              0x3205ec
#घोषणा AUD_PHASE_FIX_CTL        0x3205f0
#घोषणा AUD_PLL_PRESCALE         0x320600
#घोषणा AUD_PLL_DDS              0x320604
#घोषणा AUD_PLL_INT              0x320608
#घोषणा AUD_PLL_FRAC             0x32060c
#घोषणा AUD_PLL_JTAG             0x320620
#घोषणा AUD_PLL_SPMP             0x320624
#घोषणा AUD_AFE_12DB_EN          0x320628

// Audio QAM Register Addresses
#घोषणा AUD_PDF_DDS_CNST_BYTE2   0x320d01
#घोषणा AUD_PDF_DDS_CNST_BYTE1   0x320d02
#घोषणा AUD_PDF_DDS_CNST_BYTE0   0x320d03
#घोषणा AUD_PHACC_FREQ_8MSB      0x320d2a
#घोषणा AUD_PHACC_FREQ_8LSB      0x320d2b
#घोषणा AUD_QAM_MODE             0x320d04

/*
 * transport stream रेजिस्टरs
 */

#घोषणा MO_TS_DMA           0x330000 // अणु64पूर्णRWp Transport stream करोwnstream
#घोषणा MO_TS_GPCNT         0x33C020 // अणु16पूर्णRO TS general purpose counter
#घोषणा MO_TS_GPCNTRL       0x33C030 // अणु2पूर्णWO TS general purpose control
#घोषणा MO_TS_DMACNTRL      0x33C040 // अणु6पूर्णRW TS DMA control
#घोषणा MO_TS_XFR_STAT      0x33C044 // अणु1पूर्णRO TS transfer status
#घोषणा MO_TS_LNGTH         0x33C048 // अणु12पूर्णRW TS line length

#घोषणा TS_HW_SOP_CNTRL     0x33C04C
#घोषणा TS_GEN_CNTRL        0x33C050
#घोषणा TS_BD_PKT_STAT      0x33C054
#घोषणा TS_SOP_STAT         0x33C058
#घोषणा TS_FIFO_OVFL_STAT   0x33C05C
#घोषणा TS_VALERR_CNTRL     0x33C060

/*
 * VIP रेजिस्टरs
 */

#घोषणा MO_VIPD_DMA         0x340000 // अणु64पूर्णRWp VIP करोwnstream
#घोषणा MO_VIPU_DMA         0x340008 // अणु64पूर्णRWp VIP upstream
#घोषणा MO_VIPD_GPCNT       0x34C020 // अणु16पूर्णRO VIP करोwn general purpose counter
#घोषणा MO_VIPU_GPCNT       0x34C024 // अणु16पूर्णRO VIP up general purpose counter
#घोषणा MO_VIPD_GPCNTRL     0x34C030 // अणु2पूर्णWO VIP करोwn general purpose control
#घोषणा MO_VIPU_GPCNTRL     0x34C034 // अणु2पूर्णWO VIP up general purpose control
#घोषणा MO_VIP_DMACNTRL     0x34C040 // अणु6पूर्णRW VIP DMA control
#घोषणा MO_VIP_XFR_STAT     0x34C044 // अणु1पूर्णRO VIP transfer status
#घोषणा MO_VIP_CFG          0x340048 // VIP configuration
#घोषणा MO_VIPU_CNTRL       0x34004C // VIP upstream control #1
#घोषणा MO_VIPD_CNTRL       0x340050 // VIP करोwnstream control #2
#घोषणा MO_VIPD_LNGTH       0x340054 // VIP करोwnstream line length
#घोषणा MO_VIP_BRSTLN       0x340058 // VIP burst length
#घोषणा MO_VIP_INTCNTRL     0x34C05C // VIP Interrupt Control
#घोषणा MO_VIP_XFTERM       0x340060 // VIP transfer terminate

/*
 * misc रेजिस्टरs
 */

#घोषणा MO_M2M_DMA          0x350000 // अणु64पूर्णRWp Mem2Mem DMA Bfr
#घोषणा MO_GP0_IO           0x350010 // अणु32पूर्णRW* GPIOoutput enablesdata I/O
#घोषणा MO_GP1_IO           0x350014 // अणु32पूर्णRW* GPIOoutput enablesdata I/O
#घोषणा MO_GP2_IO           0x350018 // अणु32पूर्णRW* GPIOoutput enablesdata I/O
#घोषणा MO_GP3_IO           0x35001C // अणु32पूर्णRW* GPIO Mode/Ctrloutput enables
#घोषणा MO_GPIO             0x350020 // अणु32पूर्णRW* GPIO I2C Ctrldata I/O
#घोषणा MO_GPOE             0x350024 // अणु32पूर्णRW  GPIO I2C Ctrloutput enables
#घोषणा MO_GP_ISM           0x350028 // अणु16पूर्णWO  GPIO Intr Sens/Pol

#घोषणा MO_PLL_B            0x35C008 // अणु32पूर्णRW* PLL Control क्रम ASB bus clks
#घोषणा MO_M2M_CNT          0x35C024 // अणु32पूर्णRW  Mem2Mem DMA Cnt
#घोषणा MO_M2M_XSUM         0x35C028 // अणु32पूर्णRO  M2M XOR-Checksum
#घोषणा MO_CRC              0x35C02C // अणु16पूर्णRW  CRC16 init/result
#घोषणा MO_CRC_D            0x35C030 // अणु32पूर्णWO  CRC16 new data in
#घोषणा MO_TM_CNT_LDW       0x35C034 // अणु32पूर्णRO  Timer : Counter low dword
#घोषणा MO_TM_CNT_UW        0x35C038 // अणु16पूर्णRO  Timer : Counter high word
#घोषणा MO_TM_LMT_LDW       0x35C03C // अणु32पूर्णRW  Timer : Limit low dword
#घोषणा MO_TM_LMT_UW        0x35C040 // अणु32पूर्णRW  Timer : Limit high word
#घोषणा MO_PINMUX_IO        0x35C044 // अणु8पूर्णRW  Pin Mux Control
#घोषणा MO_TSTSEL_IO        0x35C048 // अणु2पूर्णRW  Pin Mux Control
#घोषणा MO_AFECFG_IO        0x35C04C // AFE configuration reg
#घोषणा MO_DDS_IO           0x35C050 // DDS Increment reg
#घोषणा MO_DDSCFG_IO        0x35C054 // DDS Configuration reg
#घोषणा MO_SAMPLE_IO        0x35C058 // IRIn sample reg
#घोषणा MO_SRST_IO          0x35C05C // Output प्रणाली reset reg

#घोषणा MO_INT1_MSK         0x35C060 // DMA RISC पूर्णांकerrupt mask
#घोषणा MO_INT1_STAT        0x35C064 // DMA RISC पूर्णांकerrupt status
#घोषणा MO_INT1_MSTAT       0x35C068 // DMA RISC पूर्णांकerrupt masked status

/*
 * i2c bus रेजिस्टरs
 */

#घोषणा MO_I2C              0x368000 // I2C data/control
#घोषणा MO_I2C_DIV          (0xf<<4)
#घोषणा MO_I2C_SYNC         (1<<3)
#घोषणा MO_I2C_W3B          (1<<2)
#घोषणा MO_I2C_SCL          (1<<1)
#घोषणा MO_I2C_SDA          (1<<0)


/*
 * general purpose host रेजिस्टरs
 *
 * FIXME: tyops?  s/0x35/0x38/ ??
 */

#घोषणा MO_GPHSTD_DMA       0x350000 // अणु64पूर्णRWp Host करोwnstream
#घोषणा MO_GPHSTU_DMA       0x350008 // अणु64पूर्णRWp Host upstream
#घोषणा MO_GPHSTU_CNTRL     0x380048 // Host upstream control #1
#घोषणा MO_GPHSTD_CNTRL     0x38004C // Host करोwnstream control #2
#घोषणा MO_GPHSTD_LNGTH     0x380050 // Host करोwnstream line length
#घोषणा MO_GPHST_WSC        0x380054 // Host रुको state control
#घोषणा MO_GPHST_XFR        0x380058 // Host transfer control
#घोषणा MO_GPHST_WDTH       0x38005C // Host पूर्णांकerface width
#घोषणा MO_GPHST_HDSHK      0x380060 // Host peripheral handshake
#घोषणा MO_GPHST_MUX16      0x380064 // Host muxed 16-bit transfer parameters
#घोषणा MO_GPHST_MODE       0x380068 // Host mode select

#घोषणा MO_GPHSTD_GPCNT     0x35C020 // Host करोwn general purpose counter
#घोषणा MO_GPHSTU_GPCNT     0x35C024 // Host up general purpose counter
#घोषणा MO_GPHSTD_GPCNTRL   0x38C030 // Host करोwn general purpose control
#घोषणा MO_GPHSTU_GPCNTRL   0x38C034 // Host up general purpose control
#घोषणा MO_GPHST_DMACNTRL   0x38C040 // Host DMA control
#घोषणा MO_GPHST_XFR_STAT   0x38C044 // Host transfer status
#घोषणा MO_GPHST_SOFT_RST   0x38C06C // Host software reset

/*
 * RISC inकाष्ठाions
 */

#घोषणा RISC_SYNC		 0x80000000
#घोषणा RISC_SYNC_ODD		 0x80000000
#घोषणा RISC_SYNC_EVEN		 0x80000200
#घोषणा RISC_RESYNC		 0x80008000
#घोषणा RISC_RESYNC_ODD		 0x80008000
#घोषणा RISC_RESYNC_EVEN	 0x80008200
#घोषणा RISC_WRITE		 0x10000000
#घोषणा RISC_WRITEC		 0x50000000
#घोषणा RISC_READ		 0x90000000
#घोषणा RISC_READC		 0xA0000000
#घोषणा RISC_JUMP		 0x70000000
#घोषणा RISC_SKIP		 0x20000000
#घोषणा RISC_WRITERM		 0xB0000000
#घोषणा RISC_WRITECM		 0xC0000000
#घोषणा RISC_WRITECR		 0xD0000000
#घोषणा RISC_IMM		 0x00000001

#घोषणा RISC_SOL		 0x08000000
#घोषणा RISC_EOL		 0x04000000

#घोषणा RISC_IRQ2		 0x02000000
#घोषणा RISC_IRQ1		 0x01000000

#घोषणा RISC_CNT_NONE		 0x00000000
#घोषणा RISC_CNT_INC		 0x00010000
#घोषणा RISC_CNT_RSVR		 0x00020000
#घोषणा RISC_CNT_RESET		 0x00030000
#घोषणा RISC_JMP_SRP		 0x01

/*
 * various स्थिरants
 */

// DMA
/* Interrupt mask/status */
#घोषणा PCI_INT_VIDINT		(1 <<  0)
#घोषणा PCI_INT_AUDINT		(1 <<  1)
#घोषणा PCI_INT_TSINT		(1 <<  2)
#घोषणा PCI_INT_VIPINT		(1 <<  3)
#घोषणा PCI_INT_HSTINT		(1 <<  4)
#घोषणा PCI_INT_TM1INT		(1 <<  5)
#घोषणा PCI_INT_SRCDMAINT	(1 <<  6)
#घोषणा PCI_INT_DSTDMAINT	(1 <<  7)
#घोषणा PCI_INT_RISC_RD_BERRINT	(1 << 10)
#घोषणा PCI_INT_RISC_WR_BERRINT	(1 << 11)
#घोषणा PCI_INT_BRDG_BERRINT	(1 << 12)
#घोषणा PCI_INT_SRC_DMA_BERRINT	(1 << 13)
#घोषणा PCI_INT_DST_DMA_BERRINT	(1 << 14)
#घोषणा PCI_INT_IPB_DMA_BERRINT	(1 << 15)
#घोषणा PCI_INT_I2CDONE		(1 << 16)
#घोषणा PCI_INT_I2CRACK		(1 << 17)
#घोषणा PCI_INT_IR_SMPINT	(1 << 18)
#घोषणा PCI_INT_GPIO_INT0	(1 << 19)
#घोषणा PCI_INT_GPIO_INT1	(1 << 20)

#घोषणा SEL_BTSC     0x01
#घोषणा SEL_EIAJ     0x02
#घोषणा SEL_A2       0x04
#घोषणा SEL_SAP      0x08
#घोषणा SEL_NICAM    0x10
#घोषणा SEL_FMRADIO  0x20

// AUD_CTL
#घोषणा AUD_INT_DN_RISCI1	(1 <<  0)
#घोषणा AUD_INT_UP_RISCI1	(1 <<  1)
#घोषणा AUD_INT_RDS_DN_RISCI1	(1 <<  2)
#घोषणा AUD_INT_DN_RISCI2	(1 <<  4) /* yes, 3 is skipped */
#घोषणा AUD_INT_UP_RISCI2	(1 <<  5)
#घोषणा AUD_INT_RDS_DN_RISCI2	(1 <<  6)
#घोषणा AUD_INT_DN_SYNC		(1 << 12)
#घोषणा AUD_INT_UP_SYNC		(1 << 13)
#घोषणा AUD_INT_RDS_DN_SYNC	(1 << 14)
#घोषणा AUD_INT_OPC_ERR		(1 << 16)
#घोषणा AUD_INT_BER_IRQ		(1 << 20)
#घोषणा AUD_INT_MCHG_IRQ	(1 << 21)

#घोषणा EN_BTSC_FORCE_MONO      0
#घोषणा EN_BTSC_FORCE_STEREO    1
#घोषणा EN_BTSC_FORCE_SAP       2
#घोषणा EN_BTSC_AUTO_STEREO     3
#घोषणा EN_BTSC_AUTO_SAP        4

#घोषणा EN_A2_FORCE_MONO1       8
#घोषणा EN_A2_FORCE_MONO2       9
#घोषणा EN_A2_FORCE_STEREO      10
#घोषणा EN_A2_AUTO_MONO2        11
#घोषणा EN_A2_AUTO_STEREO       12

#घोषणा EN_EIAJ_FORCE_MONO1     16
#घोषणा EN_EIAJ_FORCE_MONO2     17
#घोषणा EN_EIAJ_FORCE_STEREO    18
#घोषणा EN_EIAJ_AUTO_MONO2      19
#घोषणा EN_EIAJ_AUTO_STEREO     20

#घोषणा EN_NICAM_FORCE_MONO1    32
#घोषणा EN_NICAM_FORCE_MONO2    33
#घोषणा EN_NICAM_FORCE_STEREO   34
#घोषणा EN_NICAM_AUTO_MONO2     35
#घोषणा EN_NICAM_AUTO_STEREO    36

#घोषणा EN_FMRADIO_FORCE_MONO   24
#घोषणा EN_FMRADIO_FORCE_STEREO 25
#घोषणा EN_FMRADIO_AUTO_STEREO  26

#घोषणा EN_NICAM_AUTO_FALLBACK  0x00000040
#घोषणा EN_FMRADIO_EN_RDS       0x00000200
#घोषणा EN_NICAM_TRY_AGAIN_BIT  0x00000400
#घोषणा EN_DAC_ENABLE           0x00001000
#घोषणा EN_I2SOUT_ENABLE        0x00002000
#घोषणा EN_I2SIN_STR2DAC        0x00004000
#घोषणा EN_I2SIN_ENABLE         0x00008000

#घोषणा EN_DMTRX_SUMDIFF        (0 << 7)
#घोषणा EN_DMTRX_SUMR           (1 << 7)
#घोषणा EN_DMTRX_LR             (2 << 7)
#घोषणा EN_DMTRX_MONO           (3 << 7)
#घोषणा EN_DMTRX_BYPASS         (1 << 11)

// Video
#घोषणा VID_CAPTURE_CONTROL		0x310180

#घोषणा CX23880_CAP_CTL_CAPTURE_VBI_ODD  (1<<3)
#घोषणा CX23880_CAP_CTL_CAPTURE_VBI_EVEN (1<<2)
#घोषणा CX23880_CAP_CTL_CAPTURE_ODD      (1<<1)
#घोषणा CX23880_CAP_CTL_CAPTURE_EVEN     (1<<0)

#घोषणा VideoInputMux0		 0x0
#घोषणा VideoInputMux1		 0x1
#घोषणा VideoInputMux2		 0x2
#घोषणा VideoInputMux3		 0x3
#घोषणा VideoInputTuner		 0x0
#घोषणा VideoInputComposite	 0x1
#घोषणा VideoInputSVideo	 0x2
#घोषणा VideoInputOther		 0x3

#घोषणा Xtal0		 0x1
#घोषणा Xtal1		 0x2
#घोषणा XtalAuto	 0x3

#घोषणा VideoFormatAuto		 0x0
#घोषणा VideoFormatNTSC		 0x1
#घोषणा VideoFormatNTSCJapan	 0x2
#घोषणा VideoFormatNTSC443	 0x3
#घोषणा VideoFormatPAL		 0x4
#घोषणा VideoFormatPALB		 0x4
#घोषणा VideoFormatPALD		 0x4
#घोषणा VideoFormatPALG		 0x4
#घोषणा VideoFormatPALH		 0x4
#घोषणा VideoFormatPALI		 0x4
#घोषणा VideoFormatPALBDGHI	 0x4
#घोषणा VideoFormatPALM		 0x5
#घोषणा VideoFormatPALN		 0x6
#घोषणा VideoFormatPALNC	 0x7
#घोषणा VideoFormatPAL60	 0x8
#घोषणा VideoFormatSECAM	 0x9

#घोषणा VideoFormatAuto27MHz		 0x10
#घोषणा VideoFormatNTSC27MHz		 0x11
#घोषणा VideoFormatNTSCJapan27MHz	 0x12
#घोषणा VideoFormatNTSC44327MHz		 0x13
#घोषणा VideoFormatPAL27MHz		 0x14
#घोषणा VideoFormatPALB27MHz		 0x14
#घोषणा VideoFormatPALD27MHz		 0x14
#घोषणा VideoFormatPALG27MHz		 0x14
#घोषणा VideoFormatPALH27MHz		 0x14
#घोषणा VideoFormatPALI27MHz		 0x14
#घोषणा VideoFormatPALBDGHI27MHz	 0x14
#घोषणा VideoFormatPALM27MHz		 0x15
#घोषणा VideoFormatPALN27MHz		 0x16
#घोषणा VideoFormatPALNC27MHz		 0x17
#घोषणा VideoFormatPAL6027MHz		 0x18
#घोषणा VideoFormatSECAM27MHz		 0x19

#घोषणा NominalUSECAM	 0x87
#घोषणा NominalVSECAM	 0x85
#घोषणा NominalUNTSC	 0xFE
#घोषणा NominalVNTSC	 0xB4

#घोषणा NominalContrast  0xD8

#घोषणा HFilterAutoFormat	 0x0
#घोषणा HFilterCIF		 0x1
#घोषणा HFilterQCIF		 0x2
#घोषणा HFilterICON		 0x3

#घोषणा VFilter2TapInterpolate  0
#घोषणा VFilter3TapInterpolate  1
#घोषणा VFilter4TapInterpolate  2
#घोषणा VFilter5TapInterpolate  3
#घोषणा VFilter2TapNoInterpolate  4
#घोषणा VFilter3TapNoInterpolate  5
#घोषणा VFilter4TapNoInterpolate  6
#घोषणा VFilter5TapNoInterpolate  7

#घोषणा ColorFormatRGB32	 0x0000
#घोषणा ColorFormatRGB24	 0x0011
#घोषणा ColorFormatRGB16	 0x0022
#घोषणा ColorFormatRGB15	 0x0033
#घोषणा ColorFormatYUY2		 0x0044
#घोषणा ColorFormatBTYUV	 0x0055
#घोषणा ColorFormatY8		 0x0066
#घोषणा ColorFormatRGB8		 0x0077
#घोषणा ColorFormatPL422	 0x0088
#घोषणा ColorFormatPL411	 0x0099
#घोषणा ColorFormatYUV12	 0x00AA
#घोषणा ColorFormatYUV9		 0x00BB
#घोषणा ColorFormatRAW		 0x00EE
#घोषणा ColorFormatBSWAP         0x0300
#घोषणा ColorFormatWSWAP         0x0c00
#घोषणा ColorFormatEvenMask      0x050f
#घोषणा ColorFormatOddMask       0x0af0
#घोषणा ColorFormatGamma         0x1000

#घोषणा Interlaced		 0x1
#घोषणा NonInterlaced		 0x0

#घोषणा FieldEven		 0x1
#घोषणा FieldOdd		 0x0

#घोषणा TGReadWriteMode		 0x0
#घोषणा TGEnableMode		 0x1

#घोषणा DV_CbAlign		 0x0
#घोषणा DV_Y0Align		 0x1
#घोषणा DV_CrAlign		 0x2
#घोषणा DV_Y1Align		 0x3

#घोषणा DVF_Analog		 0x0
#घोषणा DVF_CCIR656		 0x1
#घोषणा DVF_ByteStream		 0x2
#घोषणा DVF_ExtVSYNC		 0x4
#घोषणा DVF_ExtField		 0x5

#घोषणा CHANNEL_VID_Y		 0x1
#घोषणा CHANNEL_VID_U		 0x2
#घोषणा CHANNEL_VID_V		 0x3
#घोषणा CHANNEL_VID_VBI		 0x4
#घोषणा CHANNEL_AUD_DN		 0x5
#घोषणा CHANNEL_AUD_UP		 0x6
#घोषणा CHANNEL_AUD_RDS_DN	 0x7
#घोषणा CHANNEL_MPEG_DN		 0x8
#घोषणा CHANNEL_VIP_DN		 0x9
#घोषणा CHANNEL_VIP_UP		 0xA
#घोषणा CHANNEL_HOST_DN		 0xB
#घोषणा CHANNEL_HOST_UP		 0xC
#घोषणा CHANNEL_FIRST		 0x1
#घोषणा CHANNEL_LAST		 0xC

#घोषणा GP_COUNT_CONTROL_NONE		 0x0
#घोषणा GP_COUNT_CONTROL_INC		 0x1
#घोषणा GP_COUNT_CONTROL_RESERVED	 0x2
#घोषणा GP_COUNT_CONTROL_RESET		 0x3

#घोषणा PLL_PRESCALE_BY_2  2
#घोषणा PLL_PRESCALE_BY_3  3
#घोषणा PLL_PRESCALE_BY_4  4
#घोषणा PLL_PRESCALE_BY_5  5

#घोषणा HLNotchFilter4xFsc	 0
#घोषणा HLNotchFilterSquare	 1
#घोषणा HLNotchFilter135NTSC	 2
#घोषणा HLNotchFilter135PAL	 3

#घोषणा NTSC_8x_SUB_CARRIER  28.63636E6
#घोषणा PAL_8x_SUB_CARRIER  35.46895E6

// Default analog settings
#घोषणा DEFAULT_HUE_NTSC			0x00
#घोषणा DEFAULT_BRIGHTNESS_NTSC			0x00
#घोषणा DEFAULT_CONTRAST_NTSC			0x39
#घोषणा DEFAULT_SAT_U_NTSC			0x7F
#घोषणा DEFAULT_SAT_V_NTSC			0x5A

#पूर्ण_अगर /* _CX88_REG_H_ */
