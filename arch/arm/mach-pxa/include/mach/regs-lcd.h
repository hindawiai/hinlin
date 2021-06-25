<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ASM_ARCH_REGS_LCD_H
#घोषणा __ASM_ARCH_REGS_LCD_H

#समावेश <mach/bitfield.h>

/*
 * LCD Controller Registers and Bits Definitions
 */
#घोषणा LCCR0		(0x000)	/* LCD Controller Control Register 0 */
#घोषणा LCCR1		(0x004)	/* LCD Controller Control Register 1 */
#घोषणा LCCR2		(0x008)	/* LCD Controller Control Register 2 */
#घोषणा LCCR3		(0x00C)	/* LCD Controller Control Register 3 */
#घोषणा LCCR4		(0x010)	/* LCD Controller Control Register 4 */
#घोषणा LCCR5		(0x014)	/* LCD Controller Control Register 5 */
#घोषणा LCSR		(0x038)	/* LCD Controller Status Register 0 */
#घोषणा LCSR1		(0x034)	/* LCD Controller Status Register 1 */
#घोषणा LIIDR		(0x03C)	/* LCD Controller Interrupt ID Register */
#घोषणा TMEDRGBR	(0x040)	/* TMED RGB Seed Register */
#घोषणा TMEDCR		(0x044)	/* TMED Control Register */

#घोषणा FBR0		(0x020)	/* DMA Channel 0 Frame Branch Register */
#घोषणा FBR1		(0x024)	/* DMA Channel 1 Frame Branch Register */
#घोषणा FBR2		(0x028) /* DMA Channel 2 Frame Branch Register */
#घोषणा FBR3		(0x02C) /* DMA Channel 2 Frame Branch Register */
#घोषणा FBR4		(0x030) /* DMA Channel 2 Frame Branch Register */
#घोषणा FBR5		(0x110) /* DMA Channel 2 Frame Branch Register */
#घोषणा FBR6		(0x114) /* DMA Channel 2 Frame Branch Register */

#घोषणा OVL1C1		(0x050)	/* Overlay 1 Control Register 1 */
#घोषणा OVL1C2		(0x060)	/* Overlay 1 Control Register 2 */
#घोषणा OVL2C1		(0x070)	/* Overlay 2 Control Register 1 */
#घोषणा OVL2C2		(0x080)	/* Overlay 2 Control Register 2 */

#घोषणा CMDCR		(0x100)	/* Command Control Register */
#घोषणा PRSR		(0x104)	/* Panel Read Status Register */

#घोषणा LCCR3_BPP(x)	((((x) & 0x7) << 24) | (((x) & 0x8) ? (1 << 29) : 0))

#घोषणा LCCR3_PDFOR_0	(0 << 30)
#घोषणा LCCR3_PDFOR_1	(1 << 30)
#घोषणा LCCR3_PDFOR_2	(2 << 30)
#घोषणा LCCR3_PDFOR_3	(3 << 30)

#घोषणा LCCR4_PAL_FOR_0	(0 << 15)
#घोषणा LCCR4_PAL_FOR_1	(1 << 15)
#घोषणा LCCR4_PAL_FOR_2	(2 << 15)
#घोषणा LCCR4_PAL_FOR_3	(3 << 15)
#घोषणा LCCR4_PAL_FOR_MASK	(3 << 15)

#घोषणा FDADR0		(0x200)	/* DMA Channel 0 Frame Descriptor Address Register */
#घोषणा FDADR1		(0x210)	/* DMA Channel 1 Frame Descriptor Address Register */
#घोषणा FDADR2		(0x220)	/* DMA Channel 2 Frame Descriptor Address Register */
#घोषणा FDADR3		(0x230)	/* DMA Channel 3 Frame Descriptor Address Register */
#घोषणा FDADR4		(0x240)	/* DMA Channel 4 Frame Descriptor Address Register */
#घोषणा FDADR5		(0x250)	/* DMA Channel 5 Frame Descriptor Address Register */
#घोषणा FDADR6		(0x260) /* DMA Channel 6 Frame Descriptor Address Register */

#घोषणा LCCR0_ENB	(1 << 0)	/* LCD Controller enable */
#घोषणा LCCR0_CMS	(1 << 1)	/* Color/Monochrome Display Select */
#घोषणा LCCR0_Color	(LCCR0_CMS*0)	/*  Color display */
#घोषणा LCCR0_Mono	(LCCR0_CMS*1)	/*  Monochrome display */
#घोषणा LCCR0_SDS	(1 << 2)	/* Single/Dual Panel Display Select */
#घोषणा LCCR0_Sngl	(LCCR0_SDS*0)	/*  Single panel display */
#घोषणा LCCR0_Dual	(LCCR0_SDS*1)	/*  Dual panel display */

#घोषणा LCCR0_LDM	(1 << 3)	/* LCD Disable Done Mask */
#घोषणा LCCR0_SFM	(1 << 4)	/* Start of frame mask */
#घोषणा LCCR0_IUM	(1 << 5)	/* Input FIFO underrun mask */
#घोषणा LCCR0_EFM	(1 << 6)	/* End of Frame mask */
#घोषणा LCCR0_PAS	(1 << 7)	/* Passive/Active display Select */
#घोषणा LCCR0_Pas	(LCCR0_PAS*0)	/*  Passive display (STN) */
#घोषणा LCCR0_Act	(LCCR0_PAS*1)	/*  Active display (TFT) */
#घोषणा LCCR0_DPD	(1 << 9)	/* Double Pixel Data (monochrome) */
#घोषणा LCCR0_4PixMono	(LCCR0_DPD*0)	/*  4-Pixel/घड़ी Monochrome display */
#घोषणा LCCR0_8PixMono	(LCCR0_DPD*1)	/*  8-Pixel/घड़ी Monochrome display */
#घोषणा LCCR0_DIS	(1 << 10)	/* LCD Disable */
#घोषणा LCCR0_QDM	(1 << 11)	/* LCD Quick Disable mask */
#घोषणा LCCR0_PDD	(0xff << 12)	/* Palette DMA request delay */
#घोषणा LCCR0_PDD_S	12
#घोषणा LCCR0_BM	(1 << 20)	/* Branch mask */
#घोषणा LCCR0_OUM	(1 << 21)	/* Output FIFO underrun mask */
#घोषणा LCCR0_LCDT	(1 << 22)	/* LCD panel type */
#घोषणा LCCR0_RDSTM	(1 << 23)	/* Read status पूर्णांकerrupt mask */
#घोषणा LCCR0_CMDIM	(1 << 24)	/* Command पूर्णांकerrupt mask */
#घोषणा LCCR0_OUC	(1 << 25)	/* Overlay Underlay control bit */
#घोषणा LCCR0_LDDALT	(1 << 26)	/* LDD alternate mapping control */

#घोषणा LCCR1_PPL	Fld (10, 0)	/* Pixels Per Line - 1 */
#घोषणा LCCR1_DisWdth(Pixel)	(((Pixel) - 1) << FShft (LCCR1_PPL))

#घोषणा LCCR1_HSW	Fld (6, 10)	/* Horizontal Synchronization */
#घोषणा LCCR1_HorSnchWdth(Tpix)	(((Tpix) - 1) << FShft (LCCR1_HSW))

#घोषणा LCCR1_ELW	Fld (8, 16)	/* End-of-Line pixel घड़ी Wait - 1 */
#घोषणा LCCR1_EndLnDel(Tpix)	(((Tpix) - 1) << FShft (LCCR1_ELW))

#घोषणा LCCR1_BLW	Fld (8, 24)	/* Beginning-of-Line pixel घड़ी */
#घोषणा LCCR1_BegLnDel(Tpix)	(((Tpix) - 1) << FShft (LCCR1_BLW))

#घोषणा LCCR2_LPP	Fld (10, 0)	/* Line Per Panel - 1 */
#घोषणा LCCR2_DisHght(Line)	(((Line) - 1) << FShft (LCCR2_LPP))

#घोषणा LCCR2_VSW	Fld (6, 10)	/* Vertical Synchronization pulse - 1 */
#घोषणा LCCR2_VrtSnchWdth(Tln)	(((Tln) - 1) << FShft (LCCR2_VSW))

#घोषणा LCCR2_EFW	Fld (8, 16)	/* End-of-Frame line घड़ी Wait */
#घोषणा LCCR2_EndFrmDel(Tln)	((Tln) << FShft (LCCR2_EFW))

#घोषणा LCCR2_BFW	Fld (8, 24)	/* Beginning-of-Frame line घड़ी */
#घोषणा LCCR2_BegFrmDel(Tln)	((Tln) << FShft (LCCR2_BFW))

#घोषणा LCCR3_API	(0xf << 16)	/* AC Bias pin trasitions per पूर्णांकerrupt */
#घोषणा LCCR3_API_S	16
#घोषणा LCCR3_VSP	(1 << 20)	/* vertical sync polarity */
#घोषणा LCCR3_HSP	(1 << 21)	/* horizontal sync polarity */
#घोषणा LCCR3_PCP	(1 << 22)	/* Pixel Clock Polarity (L_PCLK) */
#घोषणा LCCR3_PixRsEdg	(LCCR3_PCP*0)	/*  Pixel घड़ी Rising-Edge */
#घोषणा LCCR3_PixFlEdg	(LCCR3_PCP*1)	/*  Pixel घड़ी Falling-Edge */

#घोषणा LCCR3_OEP	(1 << 23)	/* Output Enable Polarity */
#घोषणा LCCR3_OutEnH	(LCCR3_OEP*0)	/*  Output Enable active High */
#घोषणा LCCR3_OutEnL	(LCCR3_OEP*1)	/*  Output Enable active Low */

#घोषणा LCCR3_DPC	(1 << 27)	/* द्विगुन pixel घड़ी mode */
#घोषणा LCCR3_PCD	Fld (8, 0)	/* Pixel Clock Divisor */
#घोषणा LCCR3_PixClkDiv(Div)	(((Div) << FShft (LCCR3_PCD)))

#घोषणा LCCR3_ACB	Fld (8, 8)	/* AC Bias */
#घोषणा LCCR3_Acb(Acb)	(((Acb) << FShft (LCCR3_ACB)))

#घोषणा LCCR3_HorSnchH	(LCCR3_HSP*0)	/*  HSP Active High */
#घोषणा LCCR3_HorSnchL	(LCCR3_HSP*1)	/*  HSP Active Low */

#घोषणा LCCR3_VrtSnchH	(LCCR3_VSP*0)	/*  VSP Active High */
#घोषणा LCCR3_VrtSnchL	(LCCR3_VSP*1)	/*  VSP Active Low */

#घोषणा LCCR5_IUM(x)	(1 << ((x) + 23)) /* input underrun mask */
#घोषणा LCCR5_BSM(x)	(1 << ((x) + 15)) /* branch mask */
#घोषणा LCCR5_खातापूर्णM(x)	(1 << ((x) + 7))  /* end of frame mask */
#घोषणा LCCR5_SOFM(x)	(1 << ((x) + 0))  /* start of frame mask */

#घोषणा LCSR_LDD	(1 << 0)	/* LCD Disable Done */
#घोषणा LCSR_SOF	(1 << 1)	/* Start of frame */
#घोषणा LCSR_BER	(1 << 2)	/* Bus error */
#घोषणा LCSR_ABC	(1 << 3)	/* AC Bias count */
#घोषणा LCSR_IUL	(1 << 4)	/* input FIFO underrun Lower panel */
#घोषणा LCSR_IUU	(1 << 5)	/* input FIFO underrun Upper panel */
#घोषणा LCSR_OU		(1 << 6)	/* output FIFO underrun */
#घोषणा LCSR_QD		(1 << 7)	/* quick disable */
#घोषणा LCSR_खातापूर्ण	(1 << 8)	/* end of frame */
#घोषणा LCSR_BS		(1 << 9)	/* branch status */
#घोषणा LCSR_SINT	(1 << 10)	/* subsequent पूर्णांकerrupt */
#घोषणा LCSR_RD_ST	(1 << 11)	/* पढ़ो status */
#घोषणा LCSR_CMD_INT	(1 << 12)	/* command पूर्णांकerrupt */

#घोषणा LCSR1_IU(x)	(1 << ((x) + 23)) /* Input FIFO underrun */
#घोषणा LCSR1_BS(x)	(1 << ((x) + 15)) /* Branch Status */
#घोषणा LCSR1_खातापूर्ण(x)	(1 << ((x) + 7))  /* End of Frame Status */
#घोषणा LCSR1_SOF(x)	(1 << ((x) - 1))  /* Start of Frame Status */

#घोषणा LDCMD_PAL	(1 << 26)	/* inकाष्ठाs DMA to load palette buffer */

/* overlay control रेजिस्टरs */
#घोषणा OVLxC1_PPL(x)	((((x) - 1) & 0x3ff) << 0)	/* Pixels Per Line */
#घोषणा OVLxC1_LPO(x)	((((x) - 1) & 0x3ff) << 10)	/* Number of Lines */
#घोषणा OVLxC1_BPP(x)	(((x) & 0xf) << 20)	/* Bits Per Pixel */
#घोषणा OVLxC1_OEN	(1 << 31)		/* Enable bit क्रम Overlay */
#घोषणा OVLxC2_XPOS(x)	(((x) & 0x3ff) << 0)	/* Horizontal Position */
#घोषणा OVLxC2_YPOS(x)	(((x) & 0x3ff) << 10)	/* Vertical Position */
#घोषणा OVL2C2_PFOR(x)	(((x) & 0x7) << 20)	/* Pixel Format */

/* smartpanel related */
#घोषणा PRSR_DATA(x)	((x) & 0xff)	/* Panel Data */
#घोषणा PRSR_A0		(1 << 8)	/* Read Data Source */
#घोषणा PRSR_ST_OK	(1 << 9)	/* Status OK */
#घोषणा PRSR_CON_NT	(1 << 10)	/* Continue to Next Command */

#घोषणा SMART_CMD_A0			 (0x1 << 8)
#घोषणा SMART_CMD_READ_STATUS_REG	 (0x0 << 9)
#घोषणा SMART_CMD_READ_FRAME_BUFFER	((0x0 << 9) | SMART_CMD_A0)
#घोषणा SMART_CMD_WRITE_COMMAND		 (0x1 << 9)
#घोषणा SMART_CMD_WRITE_DATA		((0x1 << 9) | SMART_CMD_A0)
#घोषणा SMART_CMD_WRITE_FRAME		((0x2 << 9) | SMART_CMD_A0)
#घोषणा SMART_CMD_WAIT_FOR_VSYNC	 (0x3 << 9)
#घोषणा SMART_CMD_NOOP			 (0x4 << 9)
#घोषणा SMART_CMD_INTERRUPT		 (0x5 << 9)

#घोषणा SMART_CMD(x)	(SMART_CMD_WRITE_COMMAND | ((x) & 0xff))
#घोषणा SMART_DAT(x)	(SMART_CMD_WRITE_DATA | ((x) & 0xff))

/* SMART_DELAY() is पूर्णांकroduced क्रम software controlled delay primitive which
 * can be inserted between command sequences, unused command 0x6 is used here
 * and delay ranges from 0ms ~ 255ms
 */
#घोषणा SMART_CMD_DELAY		(0x6 << 9)
#घोषणा SMART_DELAY(ms)		(SMART_CMD_DELAY | ((ms) & 0xff))
#पूर्ण_अगर /* __ASM_ARCH_REGS_LCD_H */
