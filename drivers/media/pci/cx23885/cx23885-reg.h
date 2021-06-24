<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 *  Driver क्रम the Conexant CX23885 PCIe bridge
 *
 *  Copyright (c) 2006 Steven Toth <stoth@linuxtv.org>
 */

#अगर_अघोषित _CX23885_REG_H_
#घोषणा _CX23885_REG_H_

/*
Address Map
0x00000000 -> 0x00009000   TX SRAM  (Fअगरos)
0x00010000 -> 0x00013c00   RX SRAM  CMDS + CDT

EACH CMDS काष्ठा is 0x80 bytes दीर्घ

DMAx_PTR1 = 0x03040 address of first cluster
DMAx_PTR2 = 0x10600 address of the CDT
DMAx_CNT1 = cluster size in (bytes >> 4) -1
DMAx_CNT2 = total cdt size क्रम all entries >> 3

Cluster Descriptor entry = 4 DWORDS
 DWORD 0 -> ptr to cluster
 DWORD 1 Reserved
 DWORD 2 Reserved
 DWORD 3 Reserved

Channel manager Data Structure entry = 20 DWORD
  0  IntialProgramCounterLow
  1  IntialProgramCounterHigh
  2  ClusterDescriptorTableBase
  3  ClusterDescriptorTableSize
  4  Inकाष्ठाionQueueBase
  5  Inकाष्ठाionQueueSize
...  Reserved
 19  Reserved
*/

/* Risc Inकाष्ठाions */
#घोषणा RISC_CNT_INC		 0x00010000
#घोषणा RISC_CNT_RESET		 0x00030000
#घोषणा RISC_IRQ1		 0x01000000
#घोषणा RISC_IRQ2		 0x02000000
#घोषणा RISC_EOL		 0x04000000
#घोषणा RISC_SOL		 0x08000000
#घोषणा RISC_WRITE		 0x10000000
#घोषणा RISC_SKIP		 0x20000000
#घोषणा RISC_JUMP		 0x70000000
#घोषणा RISC_SYNC		 0x80000000
#घोषणा RISC_RESYNC		 0x80008000
#घोषणा RISC_READ		 0x90000000
#घोषणा RISC_WRITERM		 0xB0000000
#घोषणा RISC_WRITECM		 0xC0000000
#घोषणा RISC_WRITECR		 0xD0000000
#घोषणा RISC_WRITEC		 0x50000000
#घोषणा RISC_READC		 0xA0000000


/* Audio and Video Core */
#घोषणा HOST_REG1		0x00000000
#घोषणा HOST_REG2		0x00000001
#घोषणा HOST_REG3		0x00000002

/* Chip Configuration Registers */
#घोषणा CHIP_CTRL		0x00000100
#घोषणा AFE_CTRL		0x00000104
#घोषणा VID_PLL_INT_POST	0x00000108
#घोषणा VID_PLL_FRAC		0x0000010C
#घोषणा AUX_PLL_INT_POST	0x00000110
#घोषणा AUX_PLL_FRAC		0x00000114
#घोषणा SYS_PLL_INT_POST	0x00000118
#घोषणा SYS_PLL_FRAC		0x0000011C
#घोषणा PIN_CTRL		0x00000120
#घोषणा AUD_IO_CTRL		0x00000124
#घोषणा AUD_LOCK1		0x00000128
#घोषणा AUD_LOCK2		0x0000012C
#घोषणा POWER_CTRL		0x00000130
#घोषणा AFE_DIAG_CTRL1		0x00000134
#घोषणा AFE_DIAG_CTRL3		0x0000013C
#घोषणा PLL_DIAG_CTRL		0x00000140
#घोषणा AFE_CLK_OUT_CTRL	0x00000144
#घोषणा DLL1_DIAG_CTRL		0x0000015C

/* GPIO[23:19] Output Enable */
#घोषणा GPIO2_OUT_EN_REG	0x00000160
/* GPIO[23:19] Data Registers */
#घोषणा GPIO2			0x00000164

#घोषणा IFADC_CTRL		0x00000180

/* Infrared Remote Registers */
#घोषणा IR_CNTRL_REG	0x00000200
#घोषणा IR_TXCLK_REG	0x00000204
#घोषणा IR_RXCLK_REG	0x00000208
#घोषणा IR_CDUTY_REG	0x0000020C
#घोषणा IR_STAT_REG	0x00000210
#घोषणा IR_IRQEN_REG	0x00000214
#घोषणा IR_FILTR_REG	0x00000218
#घोषणा IR_FIFO_REG	0x0000023C

/* Video Decoder Registers */
#घोषणा MODE_CTRL		0x00000400
#घोषणा OUT_CTRL1		0x00000404
#घोषणा OUT_CTRL2		0x00000408
#घोषणा GEN_STAT		0x0000040C
#घोषणा INT_STAT_MASK		0x00000410
#घोषणा LUMA_CTRL		0x00000414
#घोषणा HSCALE_CTRL		0x00000418
#घोषणा VSCALE_CTRL		0x0000041C
#घोषणा CHROMA_CTRL		0x00000420
#घोषणा VBI_LINE_CTRL1		0x00000424
#घोषणा VBI_LINE_CTRL2		0x00000428
#घोषणा VBI_LINE_CTRL3		0x0000042C
#घोषणा VBI_LINE_CTRL4		0x00000430
#घोषणा VBI_LINE_CTRL5		0x00000434
#घोषणा VBI_FC_CFG		0x00000438
#घोषणा VBI_MISC_CFG1		0x0000043C
#घोषणा VBI_MISC_CFG2		0x00000440
#घोषणा VBI_PAY1		0x00000444
#घोषणा VBI_PAY2		0x00000448
#घोषणा VBI_CUST1_CFG1		0x0000044C
#घोषणा VBI_CUST1_CFG2		0x00000450
#घोषणा VBI_CUST1_CFG3		0x00000454
#घोषणा VBI_CUST2_CFG1		0x00000458
#घोषणा VBI_CUST2_CFG2		0x0000045C
#घोषणा VBI_CUST2_CFG3		0x00000460
#घोषणा VBI_CUST3_CFG1		0x00000464
#घोषणा VBI_CUST3_CFG2		0x00000468
#घोषणा VBI_CUST3_CFG3		0x0000046C
#घोषणा HORIZ_TIM_CTRL		0x00000470
#घोषणा VERT_TIM_CTRL		0x00000474
#घोषणा SRC_COMB_CFG		0x00000478
#घोषणा CHROMA_VBIOFF_CFG	0x0000047C
#घोषणा FIELD_COUNT		0x00000480
#घोषणा MISC_TIM_CTRL		0x00000484
#घोषणा DFE_CTRL1		0x00000488
#घोषणा DFE_CTRL2		0x0000048C
#घोषणा DFE_CTRL3		0x00000490
#घोषणा PLL_CTRL		0x00000494
#घोषणा HTL_CTRL		0x00000498
#घोषणा COMB_CTRL		0x0000049C
#घोषणा CRUSH_CTRL		0x000004A0
#घोषणा SOFT_RST_CTRL		0x000004A4
#घोषणा CX885_VERSION		0x000004B4
#घोषणा VBI_PASS_CTRL		0x000004BC

/* Audio Decoder Registers */
/* 8051 Configuration */
#घोषणा DL_CTL		0x00000800
#घोषणा STD_DET_STATUS	0x00000804
#घोषणा STD_DET_CTL	0x00000808
#घोषणा DW8051_INT	0x0000080C
#घोषणा GENERAL_CTL	0x00000810
#घोषणा AAGC_CTL	0x00000814
#घोषणा DEMATRIX_CTL	0x000008CC
#घोषणा PATH1_CTL1	0x000008D0
#घोषणा PATH1_VOL_CTL	0x000008D4
#घोषणा PATH1_EQ_CTL	0x000008D8
#घोषणा PATH1_SC_CTL	0x000008DC
#घोषणा PATH2_CTL1	0x000008E0
#घोषणा PATH2_VOL_CTL	0x000008E4
#घोषणा PATH2_EQ_CTL	0x000008E8
#घोषणा PATH2_SC_CTL	0x000008EC

/* Sample Rate Converter */
#घोषणा SRC_CTL		0x000008F0
#घोषणा SRC_LF_COEF	0x000008F4
#घोषणा SRC1_CTL	0x000008F8
#घोषणा SRC2_CTL	0x000008FC
#घोषणा SRC3_CTL	0x00000900
#घोषणा SRC4_CTL	0x00000904
#घोषणा SRC5_CTL	0x00000908
#घोषणा SRC6_CTL	0x0000090C
#घोषणा BAND_OUT_SEL	0x00000910
#घोषणा I2S_N_CTL	0x00000914
#घोषणा I2S_OUT_CTL	0x00000918
#घोषणा AUTOCONFIG_REG	0x000009C4

/* Audio ADC Registers */
#घोषणा DSM_CTRL1	0x00000000
#घोषणा DSM_CTRL2	0x00000001
#घोषणा CHP_EN_CTRL	0x00000002
#घोषणा CHP_CLK_CTRL1	0x00000004
#घोषणा CHP_CLK_CTRL2	0x00000005
#घोषणा BG_REF_CTRL	0x00000006
#घोषणा SD2_SW_CTRL1	0x00000008
#घोषणा SD2_SW_CTRL2	0x00000009
#घोषणा SD2_BIAS_CTRL	0x0000000A
#घोषणा AMP_BIAS_CTRL	0x0000000C
#घोषणा CH_PWR_CTRL1	0x0000000E
#घोषणा FLD_CH_SEL      (1 << 3)
#घोषणा CH_PWR_CTRL2	0x0000000F
#घोषणा DSM_STATUS1	0x00000010
#घोषणा DSM_STATUS2	0x00000011
#घोषणा DIG_CTL1	0x00000012
#घोषणा DIG_CTL2	0x00000013
#घोषणा I2S_TX_CFG	0x0000001A

#घोषणा DEV_CNTRL2	0x00040000

#घोषणा PCI_MSK_IR        (1 << 28)
#घोषणा PCI_MSK_AV_CORE   (1 << 27)
#घोषणा PCI_MSK_GPIO1     (1 << 24)
#घोषणा PCI_MSK_GPIO0     (1 << 23)
#घोषणा PCI_MSK_APB_DMA   (1 << 12)
#घोषणा PCI_MSK_AL_WR     (1 << 11)
#घोषणा PCI_MSK_AL_RD     (1 << 10)
#घोषणा PCI_MSK_RISC_WR   (1 <<  9)
#घोषणा PCI_MSK_RISC_RD   (1 <<  8)
#घोषणा PCI_MSK_AUD_EXT   (1 <<  4)
#घोषणा PCI_MSK_AUD_INT   (1 <<  3)
#घोषणा PCI_MSK_VID_C     (1 <<  2)
#घोषणा PCI_MSK_VID_B     (1 <<  1)
#घोषणा PCI_MSK_VID_A      1
#घोषणा PCI_INT_MSK	0x00040010

#घोषणा PCI_INT_STAT	0x00040014
#घोषणा PCI_INT_MSTAT	0x00040018

#घोषणा VID_A_INT_MSK	0x00040020
#घोषणा VID_A_INT_STAT	0x00040024
#घोषणा VID_A_INT_MSTAT	0x00040028
#घोषणा VID_A_INT_SSTAT	0x0004002C

#घोषणा VID_B_INT_MSK	0x00040030
#घोषणा VID_B_MSK_BAD_PKT     (1 << 20)
#घोषणा VID_B_MSK_VBI_OPC_ERR (1 << 17)
#घोषणा VID_B_MSK_OPC_ERR     (1 << 16)
#घोषणा VID_B_MSK_VBI_SYNC    (1 << 13)
#घोषणा VID_B_MSK_SYNC        (1 << 12)
#घोषणा VID_B_MSK_VBI_OF      (1 <<  9)
#घोषणा VID_B_MSK_OF          (1 <<  8)
#घोषणा VID_B_MSK_VBI_RISCI2  (1 <<  5)
#घोषणा VID_B_MSK_RISCI2      (1 <<  4)
#घोषणा VID_B_MSK_VBI_RISCI1  (1 <<  1)
#घोषणा VID_B_MSK_RISCI1       1
#घोषणा VID_B_INT_STAT	0x00040034
#घोषणा VID_B_INT_MSTAT	0x00040038
#घोषणा VID_B_INT_SSTAT	0x0004003C

#घोषणा VID_B_MSK_BAD_PKT (1 << 20)
#घोषणा VID_B_MSK_OPC_ERR (1 << 16)
#घोषणा VID_B_MSK_SYNC    (1 << 12)
#घोषणा VID_B_MSK_OF      (1 <<  8)
#घोषणा VID_B_MSK_RISCI2  (1 <<  4)
#घोषणा VID_B_MSK_RISCI1   1

#घोषणा VID_C_MSK_BAD_PKT (1 << 20)
#घोषणा VID_C_MSK_OPC_ERR (1 << 16)
#घोषणा VID_C_MSK_SYNC    (1 << 12)
#घोषणा VID_C_MSK_OF      (1 <<  8)
#घोषणा VID_C_MSK_RISCI2  (1 <<  4)
#घोषणा VID_C_MSK_RISCI1   1

/* A superset क्रम testing purposes */
#घोषणा VID_BC_MSK_BAD_PKT (1 << 20)
#घोषणा VID_BC_MSK_OPC_ERR (1 << 16)
#घोषणा VID_BC_MSK_SYNC    (1 << 12)
#घोषणा VID_BC_MSK_OF      (1 <<  8)
#घोषणा VID_BC_MSK_VBI_RISCI2 (1 <<  5)
#घोषणा VID_BC_MSK_RISCI2  (1 <<  4)
#घोषणा VID_BC_MSK_VBI_RISCI1 (1 <<  1)
#घोषणा VID_BC_MSK_RISCI1   1

#घोषणा VID_C_INT_MSK	0x00040040
#घोषणा VID_C_INT_STAT	0x00040044
#घोषणा VID_C_INT_MSTAT	0x00040048
#घोषणा VID_C_INT_SSTAT	0x0004004C

#घोषणा AUDIO_INT_INT_MSK	0x00040050
#घोषणा AUDIO_INT_INT_STAT	0x00040054
#घोषणा AUDIO_INT_INT_MSTAT	0x00040058
#घोषणा AUDIO_INT_INT_SSTAT	0x0004005C

#घोषणा AUDIO_EXT_INT_MSK	0x00040060
#घोषणा AUDIO_EXT_INT_STAT	0x00040064
#घोषणा AUDIO_EXT_INT_MSTAT	0x00040068
#घोषणा AUDIO_EXT_INT_SSTAT	0x0004006C

/* Bits [7:0] set in both TC_REQ and TC_REQ_SET
 * indicate a stall in the RISC engine क्रम a
 * particular rider traffic class. This causes
 * the 885 and 888 bridges (unknown about 887)
 * to become inoperable. Setting bits in
 * TC_REQ_SET resets the corresponding bits
 * in TC_REQ (and TC_REQ_SET) allowing
 * operation to जारी.
 */
#घोषणा TC_REQ		0x00040090
#घोषणा TC_REQ_SET	0x00040094

#घोषणा RDR_CFG0	0x00050000
#घोषणा RDR_CFG1	0x00050004
#घोषणा RDR_CFG2	0x00050008
#घोषणा RDR_RDRCTL1	0x0005030c
#घोषणा RDR_TLCTL0	0x00050318

/* APB DMAC Current Buffer Poपूर्णांकer */
#घोषणा DMA1_PTR1	0x00100000
#घोषणा DMA2_PTR1	0x00100004
#घोषणा DMA3_PTR1	0x00100008
#घोषणा DMA4_PTR1	0x0010000C
#घोषणा DMA5_PTR1	0x00100010
#घोषणा DMA6_PTR1	0x00100014
#घोषणा DMA7_PTR1	0x00100018
#घोषणा DMA8_PTR1	0x0010001C

/* APB DMAC Current Table Poपूर्णांकer */
#घोषणा DMA1_PTR2	0x00100040
#घोषणा DMA2_PTR2	0x00100044
#घोषणा DMA3_PTR2	0x00100048
#घोषणा DMA4_PTR2	0x0010004C
#घोषणा DMA5_PTR2	0x00100050
#घोषणा DMA6_PTR2	0x00100054
#घोषणा DMA7_PTR2	0x00100058
#घोषणा DMA8_PTR2	0x0010005C

/* APB DMAC Buffer Limit */
#घोषणा DMA1_CNT1	0x00100080
#घोषणा DMA2_CNT1	0x00100084
#घोषणा DMA3_CNT1	0x00100088
#घोषणा DMA4_CNT1	0x0010008C
#घोषणा DMA5_CNT1	0x00100090
#घोषणा DMA6_CNT1	0x00100094
#घोषणा DMA7_CNT1	0x00100098
#घोषणा DMA8_CNT1	0x0010009C

/* APB DMAC Table Size */
#घोषणा DMA1_CNT2	0x001000C0
#घोषणा DMA2_CNT2	0x001000C4
#घोषणा DMA3_CNT2	0x001000C8
#घोषणा DMA4_CNT2	0x001000CC
#घोषणा DMA5_CNT2	0x001000D0
#घोषणा DMA6_CNT2	0x001000D4
#घोषणा DMA7_CNT2	0x001000D8
#घोषणा DMA8_CNT2	0x001000DC

/* Timer Counters */
#घोषणा TM_CNT_LDW	0x00110000
#घोषणा TM_CNT_UW	0x00110004
#घोषणा TM_LMT_LDW	0x00110008
#घोषणा TM_LMT_UW	0x0011000C

/* GPIO */
#घोषणा GP0_IO		0x00110010
#घोषणा GPIO_ISM	0x00110014
#घोषणा SOFT_RESET	0x0011001C

/* GPIO (417 Microsoftcontroller) RW Data */
#घोषणा MC417_RWD	0x00110020

/* GPIO (417 Microsoftcontroller) Output Enable, Low Active */
#घोषणा MC417_OEN	0x00110024
#घोषणा MC417_CTL	0x00110028
#घोषणा ALT_PIN_OUT_SEL 0x0011002C
#घोषणा CLK_DELAY	0x00110048
#घोषणा PAD_CTRL	0x0011004C

/* Video A Interface */
#घोषणा VID_A_GPCNT		0x00130020
#घोषणा VBI_A_GPCNT		0x00130024
#घोषणा VID_A_GPCNT_CTL		0x00130030
#घोषणा VBI_A_GPCNT_CTL		0x00130034
#घोषणा VID_A_DMA_CTL		0x00130040
#घोषणा VID_A_VIP_CTRL		0x00130080
#घोषणा VID_A_PIXEL_FRMT	0x00130084
#घोषणा VID_A_VBI_CTRL		0x00130088

/* Video B Interface */
#घोषणा VID_B_DMA		0x00130100
#घोषणा VBI_B_DMA		0x00130108
#घोषणा VID_B_GPCNT		0x00130120
#घोषणा VBI_B_GPCNT		0x00130124
#घोषणा VID_B_GPCNT_CTL		0x00130134
#घोषणा VBI_B_GPCNT_CTL		0x00130138
#घोषणा VID_B_DMA_CTL		0x00130140
#घोषणा VID_B_SRC_SEL		0x00130144
#घोषणा VID_B_LNGTH		0x00130150
#घोषणा VID_B_HW_SOP_CTL	0x00130154
#घोषणा VID_B_GEN_CTL		0x00130158
#घोषणा VID_B_BD_PKT_STATUS	0x0013015C
#घोषणा VID_B_SOP_STATUS	0x00130160
#घोषणा VID_B_FIFO_OVFL_STAT	0x00130164
#घोषणा VID_B_VLD_MISC		0x00130168
#घोषणा VID_B_TS_CLK_EN		0x0013016C
#घोषणा VID_B_VIP_CTRL		0x00130180
#घोषणा VID_B_PIXEL_FRMT	0x00130184

/* Video C Interface */
#घोषणा VID_C_DMA		0x00130200
#घोषणा VBI_C_DMA		0x00130208
#घोषणा VID_C_GPCNT		0x00130220
#घोषणा VID_C_GPCNT_CTL		0x00130230
#घोषणा VBI_C_GPCNT_CTL		0x00130234
#घोषणा VID_C_DMA_CTL		0x00130240
#घोषणा VID_C_LNGTH		0x00130250
#घोषणा VID_C_HW_SOP_CTL	0x00130254
#घोषणा VID_C_GEN_CTL		0x00130258
#घोषणा VID_C_BD_PKT_STATUS	0x0013025C
#घोषणा VID_C_SOP_STATUS	0x00130260
#घोषणा VID_C_FIFO_OVFL_STAT	0x00130264
#घोषणा VID_C_VLD_MISC		0x00130268
#घोषणा VID_C_TS_CLK_EN		0x0013026C

/* Internal Audio Interface */
#घोषणा AUD_INT_A_GPCNT		0x00140020
#घोषणा AUD_INT_B_GPCNT		0x00140024
#घोषणा AUD_INT_A_GPCNT_CTL	0x00140030
#घोषणा AUD_INT_B_GPCNT_CTL	0x00140034
#घोषणा AUD_INT_DMA_CTL		0x00140040
#घोषणा AUD_INT_A_LNGTH		0x00140050
#घोषणा AUD_INT_B_LNGTH		0x00140054
#घोषणा AUD_INT_A_MODE		0x00140058
#घोषणा AUD_INT_B_MODE		0x0014005C

/* External Audio Interface */
#घोषणा AUD_EXT_DMA		0x00140100
#घोषणा AUD_EXT_GPCNT		0x00140120
#घोषणा AUD_EXT_GPCNT_CTL	0x00140130
#घोषणा AUD_EXT_DMA_CTL		0x00140140
#घोषणा AUD_EXT_LNGTH		0x00140150
#घोषणा AUD_EXT_A_MODE		0x00140158

/* I2C Bus 1 */
#घोषणा I2C1_ADDR	0x00180000
#घोषणा I2C1_WDATA	0x00180004
#घोषणा I2C1_CTRL	0x00180008
#घोषणा I2C1_RDATA	0x0018000C
#घोषणा I2C1_STAT	0x00180010

/* I2C Bus 2 */
#घोषणा I2C2_ADDR	0x00190000
#घोषणा I2C2_WDATA	0x00190004
#घोषणा I2C2_CTRL	0x00190008
#घोषणा I2C2_RDATA	0x0019000C
#घोषणा I2C2_STAT	0x00190010

/* I2C Bus 3 */
#घोषणा I2C3_ADDR	0x001A0000
#घोषणा I2C3_WDATA	0x001A0004
#घोषणा I2C3_CTRL	0x001A0008
#घोषणा I2C3_RDATA	0x001A000C
#घोषणा I2C3_STAT	0x001A0010

/* UART */
#घोषणा UART_CTL	0x001B0000
#घोषणा UART_BRD	0x001B0004
#घोषणा UART_ISR	0x001B000C
#घोषणा UART_CNT	0x001B0010

#पूर्ण_अगर /* _CX23885_REG_H_ */
