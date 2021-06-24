<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *  linux/drivers/video/cyber2000fb.h
 *
 *  Copyright (C) 1998-2000 Russell King
 *
 * Integraphics Cyber2000 frame buffer device
 */

/*
 * Internal CyberPro sizes and offsets.
 */
#घोषणा MMIO_OFFSET	0x00800000
#घोषणा MMIO_SIZE	0x000c0000

#घोषणा NR_PALETTE	256

#अगर defined(DEBUG) && defined(CONFIG_DEBUG_LL)
अटल व्योम debug_म_लिखो(अक्षर *fmt, ...)
अणु
	बाह्य व्योम prपूर्णांकascii(स्थिर अक्षर *);
	अक्षर buffer[128];
	बहु_सूची ap;

	बहु_शुरू(ap, fmt);
	भम_लिखो(buffer, fmt, ap);
	बहु_पूर्ण(ap);

	prपूर्णांकascii(buffer);
पूर्ण
#अन्यथा
#घोषणा debug_म_लिखो(x...) करो अणु पूर्ण जबतक (0)
#पूर्ण_अगर

#घोषणा RAMDAC_RAMPWRDN		0x01
#घोषणा RAMDAC_DAC8BIT		0x02
#घोषणा RAMDAC_VREFEN		0x04
#घोषणा RAMDAC_BYPASS		0x10
#घोषणा RAMDAC_DACPWRDN		0x40

#घोषणा EXT_CRT_VRTOFL		0x11
#घोषणा EXT_CRT_VRTOFL_LINECOMP10	0x10
#घोषणा EXT_CRT_VRTOFL_INTERLACE	0x20

#घोषणा EXT_CRT_IRQ		0x12
#घोषणा EXT_CRT_IRQ_ENABLE		0x01
#घोषणा EXT_CRT_IRQ_ACT_HIGH		0x04

#घोषणा EXT_CRT_TEST		0x13

#घोषणा EXT_SYNC_CTL		0x16
#घोषणा EXT_SYNC_CTL_HS_NORMAL		0x00
#घोषणा EXT_SYNC_CTL_HS_0		0x01
#घोषणा EXT_SYNC_CTL_HS_1		0x02
#घोषणा EXT_SYNC_CTL_HS_HSVS		0x03
#घोषणा EXT_SYNC_CTL_VS_NORMAL		0x00
#घोषणा EXT_SYNC_CTL_VS_0		0x04
#घोषणा EXT_SYNC_CTL_VS_1		0x08
#घोषणा EXT_SYNC_CTL_VS_COMP		0x0c

#घोषणा EXT_BUS_CTL		0x30
#घोषणा EXT_BUS_CTL_LIN_1MB		0x00
#घोषणा EXT_BUS_CTL_LIN_2MB		0x01
#घोषणा EXT_BUS_CTL_LIN_4MB		0x02
#घोषणा EXT_BUS_CTL_ZEROWAIT		0x04
#घोषणा EXT_BUS_CTL_PCIBURST_WRITE	0x20
#घोषणा EXT_BUS_CTL_PCIBURST_READ	0x80	/* CyberPro 5000 only */

#घोषणा EXT_SEG_WRITE_PTR	0x31
#घोषणा EXT_SEG_READ_PTR	0x32
#घोषणा EXT_BIU_MISC		0x33
#घोषणा EXT_BIU_MISC_LIN_ENABLE		0x01
#घोषणा EXT_BIU_MISC_COP_ENABLE		0x04
#घोषणा EXT_BIU_MISC_COP_BFC		0x08

#घोषणा EXT_FUNC_CTL		0x3c
#घोषणा EXT_FUNC_CTL_EXTREGENBL		0x80	/* enable access to 0xbcxxx		*/

#घोषणा PCI_BM_CTL		0x3e
#घोषणा PCI_BM_CTL_ENABLE		0x01	/* enable bus-master			*/
#घोषणा PCI_BM_CTL_BURST		0x02	/* enable burst				*/
#घोषणा PCI_BM_CTL_BACK2BACK		0x04	/* enable back to back			*/
#घोषणा PCI_BM_CTL_DUMMY		0x08	/* insert dummy cycle			*/

#घोषणा X_V2_VID_MEM_START	0x40
#घोषणा X_V2_VID_SRC_WIDTH	0x43
#घोषणा X_V2_X_START		0x45
#घोषणा X_V2_X_END		0x47
#घोषणा X_V2_Y_START		0x49
#घोषणा X_V2_Y_END		0x4b
#घोषणा X_V2_VID_SRC_WIN_WIDTH	0x4d

#घोषणा Y_V2_DDA_X_INC		0x43
#घोषणा Y_V2_DDA_Y_INC		0x47
#घोषणा Y_V2_VID_FIFO_CTL	0x49
#घोषणा Y_V2_VID_FMT		0x4b
#घोषणा Y_V2_VID_DISP_CTL1	0x4c
#घोषणा Y_V2_VID_FIFO_CTL1	0x4d

#घोषणा J_X2_VID_MEM_START	0x40
#घोषणा J_X2_VID_SRC_WIDTH	0x43
#घोषणा J_X2_X_START		0x47
#घोषणा J_X2_X_END		0x49
#घोषणा J_X2_Y_START		0x4b
#घोषणा J_X2_Y_END		0x4d
#घोषणा J_X2_VID_SRC_WIN_WIDTH	0x4f

#घोषणा K_X2_DDA_X_INIT		0x40
#घोषणा K_X2_DDA_X_INC		0x42
#घोषणा K_X2_DDA_Y_INIT		0x44
#घोषणा K_X2_DDA_Y_INC		0x46
#घोषणा K_X2_VID_FMT		0x48
#घोषणा K_X2_VID_DISP_CTL1	0x49

#घोषणा K_CAP_X2_CTL1		0x49

#घोषणा CURS_H_START		0x50
#घोषणा CURS_H_PRESET		0x52
#घोषणा CURS_V_START		0x53
#घोषणा CURS_V_PRESET		0x55
#घोषणा CURS_CTL		0x56

#घोषणा EXT_ATTRIB_CTL		0x57
#घोषणा EXT_ATTRIB_CTL_EXT		0x01

#घोषणा EXT_OVERSCAN_RED	0x58
#घोषणा EXT_OVERSCAN_GREEN	0x59
#घोषणा EXT_OVERSCAN_BLUE	0x5a

#घोषणा CAP_X_START		0x60
#घोषणा CAP_X_END		0x62
#घोषणा CAP_Y_START		0x64
#घोषणा CAP_Y_END		0x66
#घोषणा CAP_DDA_X_INIT		0x68
#घोषणा CAP_DDA_X_INC		0x6a
#घोषणा CAP_DDA_Y_INIT		0x6c
#घोषणा CAP_DDA_Y_INC		0x6e

#घोषणा EXT_MEM_CTL0		0x70
#घोषणा EXT_MEM_CTL0_7CLK		0x01
#घोषणा EXT_MEM_CTL0_RAS_1		0x02
#घोषणा EXT_MEM_CTL0_RAS2CAS_1		0x04
#घोषणा EXT_MEM_CTL0_MULTCAS		0x08
#घोषणा EXT_MEM_CTL0_ASYM		0x10
#घोषणा EXT_MEM_CTL0_CAS1ON		0x20
#घोषणा EXT_MEM_CTL0_FIFOFLUSH		0x40
#घोषणा EXT_MEM_CTL0_SEQRESET		0x80

#घोषणा EXT_MEM_CTL1		0x71
#घोषणा EXT_MEM_CTL1_PAR		0x00
#घोषणा EXT_MEM_CTL1_SERPAR		0x01
#घोषणा EXT_MEM_CTL1_SER		0x03
#घोषणा EXT_MEM_CTL1_SYNC		0x04
#घोषणा EXT_MEM_CTL1_VRAM		0x08
#घोषणा EXT_MEM_CTL1_4K_REFRESH		0x10
#घोषणा EXT_MEM_CTL1_256Kx4		0x00
#घोषणा EXT_MEM_CTL1_512Kx8		0x40
#घोषणा EXT_MEM_CTL1_1Mx16		0x60

#घोषणा EXT_MEM_CTL2		0x72
#घोषणा MEM_CTL2_SIZE_1MB		0x00
#घोषणा MEM_CTL2_SIZE_2MB		0x01
#घोषणा MEM_CTL2_SIZE_4MB		0x02
#घोषणा MEM_CTL2_SIZE_MASK		0x03
#घोषणा MEM_CTL2_64BIT			0x04

#घोषणा EXT_HIDDEN_CTL1		0x73

#घोषणा EXT_FIFO_CTL		0x74

#घोषणा EXT_SEQ_MISC		0x77
#घोषणा EXT_SEQ_MISC_8			0x01
#घोषणा EXT_SEQ_MISC_16_RGB565		0x02
#घोषणा EXT_SEQ_MISC_32			0x03
#घोषणा EXT_SEQ_MISC_24_RGB888		0x04
#घोषणा EXT_SEQ_MISC_16_RGB555		0x06
#घोषणा EXT_SEQ_MISC_8_RGB332		0x09
#घोषणा EXT_SEQ_MISC_16_RGB444		0x0a

#घोषणा EXT_HIDDEN_CTL4		0x7a

#घोषणा CURS_MEM_START		0x7e		/* bits 23..12 */

#घोषणा CAP_PIP_X_START		0x80
#घोषणा CAP_PIP_X_END		0x82
#घोषणा CAP_PIP_Y_START		0x84
#घोषणा CAP_PIP_Y_END		0x86

#घोषणा EXT_CAP_CTL1		0x88

#घोषणा EXT_CAP_CTL2		0x89
#घोषणा EXT_CAP_CTL2_ODDFRAMEIRQ	0x01
#घोषणा EXT_CAP_CTL2_ANYFRAMEIRQ	0x02

#घोषणा BM_CTRL0		0x9c
#घोषणा BM_CTRL1		0x9d

#घोषणा EXT_CAP_MODE1		0xa4
#घोषणा EXT_CAP_MODE1_8BIT		0x01	/* enable 8bit capture mode		*/
#घोषणा EXT_CAP_MODE1_CCIR656		0x02	/* CCIR656 mode				*/
#घोषणा EXT_CAP_MODE1_IGNOREVGT		0x04	/* ignore VGT				*/
#घोषणा EXT_CAP_MODE1_ALTFIFO		0x10	/* use alternate FIFO क्रम capture	*/
#घोषणा EXT_CAP_MODE1_SWAPUV		0x20	/* swap UV bytes			*/
#घोषणा EXT_CAP_MODE1_MIRRORY		0x40	/* mirror vertically			*/
#घोषणा EXT_CAP_MODE1_MIRRORX		0x80	/* mirror horizontally			*/

#घोषणा EXT_CAP_MODE2		0xa5
#घोषणा EXT_CAP_MODE2_CCIRINVOE		0x01
#घोषणा EXT_CAP_MODE2_CCIRINVVGT	0x02
#घोषणा EXT_CAP_MODE2_CCIRINVHGT	0x04
#घोषणा EXT_CAP_MODE2_CCIRINVDG		0x08
#घोषणा EXT_CAP_MODE2_DATEND		0x10
#घोषणा EXT_CAP_MODE2_CCIRDGH		0x20
#घोषणा EXT_CAP_MODE2_FIXSONY		0x40
#घोषणा EXT_CAP_MODE2_SYNCFREEZE	0x80

#घोषणा EXT_TV_CTL		0xae

#घोषणा EXT_DCLK_MULT		0xb0
#घोषणा EXT_DCLK_DIV		0xb1
#घोषणा EXT_DCLK_DIV_VFSEL		0x20
#घोषणा EXT_MCLK_MULT		0xb2
#घोषणा EXT_MCLK_DIV		0xb3

#घोषणा EXT_LATCH1		0xb5
#घोषणा EXT_LATCH1_VAFC_EN		0x01	/* enable VAFC				*/

#घोषणा EXT_FEATURE		0xb7
#घोषणा EXT_FEATURE_BUS_MASK		0x07	/* host bus mask			*/
#घोषणा EXT_FEATURE_BUS_PCI		0x00
#घोषणा EXT_FEATURE_BUS_VL_STD		0x04
#घोषणा EXT_FEATURE_BUS_VL_LINEAR	0x05
#घोषणा EXT_FEATURE_1682		0x20	/* IGS 1682 compatibility		*/

#घोषणा EXT_LATCH2		0xb6
#घोषणा EXT_LATCH2_I2C_CLKEN		0x10
#घोषणा EXT_LATCH2_I2C_CLK		0x20
#घोषणा EXT_LATCH2_I2C_DATEN		0x40
#घोषणा EXT_LATCH2_I2C_DAT		0x80

#घोषणा EXT_XT_CTL		0xbe
#घोषणा EXT_XT_CAP16			0x04
#घोषणा EXT_XT_LINEARFB			0x08
#घोषणा EXT_XT_PAL			0x10

#घोषणा EXT_MEM_START		0xc0		/* ext start address 21 bits		*/
#घोषणा HOR_PHASE_SHIFT		0xc2		/* high 3 bits				*/
#घोषणा EXT_SRC_WIDTH		0xc3		/* ext offset phase  10 bits		*/
#घोषणा EXT_SRC_HEIGHT		0xc4		/* high 6 bits				*/
#घोषणा EXT_X_START		0xc5		/* ext->screen, 16 bits			*/
#घोषणा EXT_X_END		0xc7		/* ext->screen, 16 bits			*/
#घोषणा EXT_Y_START		0xc9		/* ext->screen, 16 bits			*/
#घोषणा EXT_Y_END		0xcb		/* ext->screen, 16 bits			*/
#घोषणा EXT_SRC_WIN_WIDTH	0xcd		/* 8 bits				*/
#घोषणा EXT_COLOUR_COMPARE	0xce		/* 24 bits				*/
#घोषणा EXT_DDA_X_INIT		0xd1		/* ext->screen 16 bits			*/
#घोषणा EXT_DDA_X_INC		0xd3		/* ext->screen 16 bits			*/
#घोषणा EXT_DDA_Y_INIT		0xd5		/* ext->screen 16 bits			*/
#घोषणा EXT_DDA_Y_INC		0xd7		/* ext->screen 16 bits			*/

#घोषणा EXT_VID_FIFO_CTL	0xd9

#घोषणा EXT_VID_FMT		0xdb
#घोषणा EXT_VID_FMT_YUV422		0x00	/* क्रमmats - करोes this cause conversion? */
#घोषणा EXT_VID_FMT_RGB555		0x01
#घोषणा EXT_VID_FMT_RGB565		0x02
#घोषणा EXT_VID_FMT_RGB888_24		0x03
#घोषणा EXT_VID_FMT_RGB888_32		0x04
#घोषणा EXT_VID_FMT_RGB8		0x05
#घोषणा EXT_VID_FMT_RGB4444		0x06
#घोषणा EXT_VID_FMT_RGB8T		0x07
#घोषणा EXT_VID_FMT_DUP_PIX_ZOON	0x08	/* duplicate pixel zoom			*/
#घोषणा EXT_VID_FMT_MOD_3RD_PIX		0x20	/* modअगरy 3rd duplicated pixel		*/
#घोषणा EXT_VID_FMT_DBL_H_PIX		0x40	/* द्विगुन horiz pixels			*/
#घोषणा EXT_VID_FMT_YUV128		0x80	/* YUV data offset by 128		*/

#घोषणा EXT_VID_DISP_CTL1	0xdc
#घोषणा EXT_VID_DISP_CTL1_INTRAM	0x01	/* video pixels go to पूर्णांकernal RAM	*/
#घोषणा EXT_VID_DISP_CTL1_IGNORE_CCOMP	0x02	/* ignore colour compare रेजिस्टरs	*/
#घोषणा EXT_VID_DISP_CTL1_NOCLIP	0x04	/* करो not clip to 16235,16240		*/
#घोषणा EXT_VID_DISP_CTL1_UV_AVG	0x08	/* U/V data is averaged			*/
#घोषणा EXT_VID_DISP_CTL1_Y128		0x10	/* Y data offset by 128 (अगर YUV128 set)	*/
#घोषणा EXT_VID_DISP_CTL1_VINTERPOL_OFF	0x20	/* disable vertical पूर्णांकerpolation	*/
#घोषणा EXT_VID_DISP_CTL1_FULL_WIN	0x40	/* video out winकरोw full		*/
#घोषणा EXT_VID_DISP_CTL1_ENABLE_WINDOW	0x80	/* enable video winकरोw			*/

#घोषणा EXT_VID_FIFO_CTL1	0xdd
#घोषणा EXT_VID_FIFO_CTL1_OE_HIGH	0x02
#घोषणा EXT_VID_FIFO_CTL1_INTERLEAVE	0x04	/* enable पूर्णांकerleaved memory पढ़ो	*/

#घोषणा EXT_ROM_UCB4GH		0xe5
#घोषणा EXT_ROM_UCB4GH_FREEZE		0x02	/* capture frozen			*/
#घोषणा EXT_ROM_UCB4GH_ODDFRAME		0x04	/* 1 = odd frame captured		*/
#घोषणा EXT_ROM_UCB4GH_1HL		0x08	/* first horizonal line after VGT falling edge */
#घोषणा EXT_ROM_UCB4GH_ODD		0x10	/* odd frame indicator			*/
#घोषणा EXT_ROM_UCB4GH_INTSTAT		0x20	/* video पूर्णांकerrupt			*/

#घोषणा VFAC_CTL1		0xe8
#घोषणा VFAC_CTL1_CAPTURE		0x01	/* capture enable (only when VSYNC high)*/
#घोषणा VFAC_CTL1_VFAC_ENABLE		0x02	/* vfac enable				*/
#घोषणा VFAC_CTL1_FREEZE_CAPTURE	0x04	/* मुक्तze capture			*/
#घोषणा VFAC_CTL1_FREEZE_CAPTURE_SYNC	0x08	/* sync मुक्तze capture			*/
#घोषणा VFAC_CTL1_VALIDFRAME_SRC	0x10	/* select valid frame source		*/
#घोषणा VFAC_CTL1_PHILIPS		0x40	/* select Philips mode			*/
#घोषणा VFAC_CTL1_MODVINTERPOLCLK	0x80	/* modअगरy vertical पूर्णांकerpolation clocl	*/

#घोषणा VFAC_CTL2		0xe9
#घोषणा VFAC_CTL2_INVERT_VIDDATAVALID	0x01	/* invert video data valid		*/
#घोषणा VFAC_CTL2_INVERT_GRAPHREADY	0x02	/* invert graphic पढ़ोy output sig	*/
#घोषणा VFAC_CTL2_INVERT_DATACLK	0x04	/* invert data घड़ी संकेत		*/
#घोषणा VFAC_CTL2_INVERT_HSYNC		0x08	/* invert hsync input			*/
#घोषणा VFAC_CTL2_INVERT_VSYNC		0x10	/* invert vsync input			*/
#घोषणा VFAC_CTL2_INVERT_FRAME		0x20	/* invert frame odd/even input		*/
#घोषणा VFAC_CTL2_INVERT_BLANK		0x40	/* invert blank output			*/
#घोषणा VFAC_CTL2_INVERT_OVSYNC		0x80	/* invert other vsync input		*/

#घोषणा VFAC_CTL3		0xea
#घोषणा VFAC_CTL3_CAP_LARGE_FIFO	0x01	/* large capture fअगरo			*/
#घोषणा VFAC_CTL3_CAP_INTERLACE		0x02	/* capture odd and even fields		*/
#घोषणा VFAC_CTL3_CAP_HOLD_4NS		0x00	/* hold capture data क्रम 4ns		*/
#घोषणा VFAC_CTL3_CAP_HOLD_2NS		0x04	/* hold capture data क्रम 2ns		*/
#घोषणा VFAC_CTL3_CAP_HOLD_6NS		0x08	/* hold capture data क्रम 6ns		*/
#घोषणा VFAC_CTL3_CAP_HOLD_0NS		0x0c	/* hold capture data क्रम 0ns		*/
#घोषणा VFAC_CTL3_CHROMAKEY		0x20	/* capture data will be chromakeyed	*/
#घोषणा VFAC_CTL3_CAP_IRQ		0x40	/* enable capture पूर्णांकerrupt		*/

#घोषणा CAP_MEM_START		0xeb		/* 18 bits				*/
#घोषणा CAP_MAP_WIDTH		0xed		/* high 6 bits				*/
#घोषणा CAP_PITCH		0xee		/* 8 bits				*/

#घोषणा CAP_CTL_MISC		0xef
#घोषणा CAP_CTL_MISC_HDIV		0x01
#घोषणा CAP_CTL_MISC_HDIV4		0x02
#घोषणा CAP_CTL_MISC_ODDEVEN		0x04
#घोषणा CAP_CTL_MISC_HSYNCDIV2		0x08
#घोषणा CAP_CTL_MISC_SYNCTZHIGH		0x10
#घोषणा CAP_CTL_MISC_SYNCTZOR		0x20
#घोषणा CAP_CTL_MISC_DISPUSED		0x80

#घोषणा REG_BANK		0xfa
#घोषणा REG_BANK_X			0x00
#घोषणा REG_BANK_Y			0x01
#घोषणा REG_BANK_W			0x02
#घोषणा REG_BANK_T			0x03
#घोषणा REG_BANK_J			0x04
#घोषणा REG_BANK_K			0x05

/*
 * Bus-master
 */
#घोषणा BM_VID_ADDR_LOW		0xbc040
#घोषणा BM_VID_ADDR_HIGH	0xbc044
#घोषणा BM_ADDRESS_LOW		0xbc080
#घोषणा BM_ADDRESS_HIGH		0xbc084
#घोषणा BM_LENGTH		0xbc088
#घोषणा BM_CONTROL		0xbc08c
#घोषणा BM_CONTROL_ENABLE		0x01	/* enable transfer			*/
#घोषणा BM_CONTROL_IRQEN		0x02	/* enable IRQ at end of transfer	*/
#घोषणा BM_CONTROL_INIT			0x04	/* initialise status & count		*/
#घोषणा BM_COUNT		0xbc090		/* पढ़ो-only				*/

/*
 * TV रेजिस्टरs
 */
#घोषणा TV_VBLANK_EVEN_START	0xbe43c
#घोषणा TV_VBLANK_EVEN_END	0xbe440
#घोषणा TV_VBLANK_ODD_START	0xbe444
#घोषणा TV_VBLANK_ODD_END	0xbe448
#घोषणा TV_SYNC_YGAIN		0xbe44c
#घोषणा TV_UV_GAIN		0xbe450
#घोषणा TV_PED_UVDET		0xbe454
#घोषणा TV_UV_BURST_AMP		0xbe458
#घोषणा TV_HSYNC_START		0xbe45c
#घोषणा TV_HSYNC_END		0xbe460
#घोषणा TV_Y_DELAY1		0xbe464
#घोषणा TV_Y_DELAY2		0xbe468
#घोषणा TV_UV_DELAY1		0xbe46c
#घोषणा TV_BURST_START		0xbe470
#घोषणा TV_BURST_END		0xbe474
#घोषणा TV_HBLANK_START		0xbe478
#घोषणा TV_HBLANK_END		0xbe47c
#घोषणा TV_PED_EVEN_START	0xbe480
#घोषणा TV_PED_EVEN_END		0xbe484
#घोषणा TV_PED_ODD_START	0xbe488
#घोषणा TV_PED_ODD_END		0xbe48c
#घोषणा TV_VSYNC_EVEN_START	0xbe490
#घोषणा TV_VSYNC_EVEN_END	0xbe494
#घोषणा TV_VSYNC_ODD_START	0xbe498
#घोषणा TV_VSYNC_ODD_END	0xbe49c
#घोषणा TV_SCFL			0xbe4a0
#घोषणा TV_SCFH			0xbe4a4
#घोषणा TV_SCP			0xbe4a8
#घोषणा TV_DELAYBYPASS		0xbe4b4
#घोषणा TV_EQL_END		0xbe4bc
#घोषणा TV_SERR_START		0xbe4c0
#घोषणा TV_SERR_END		0xbe4c4
#घोषणा TV_CTL			0xbe4dc	/* reflects a previous रेजिस्टर- MVFCLR, MVPCLR etc P241*/
#घोषणा TV_VSYNC_VGA_HS		0xbe4e8
#घोषणा TV_FLICK_XMIN		0xbe514
#घोषणा TV_FLICK_XMAX		0xbe518
#घोषणा TV_FLICK_YMIN		0xbe51c
#घोषणा TV_FLICK_YMAX		0xbe520

/*
 * Graphics Co-processor
 */
#घोषणा CO_REG_CONTROL		0xbf011
#घोषणा CO_CTRL_BUSY			0x80
#घोषणा CO_CTRL_CMDFULL			0x04
#घोषणा CO_CTRL_FIFOEMPTY		0x02
#घोषणा CO_CTRL_READY			0x01

#घोषणा CO_REG_SRC_WIDTH	0xbf018
#घोषणा CO_REG_PIXFMT		0xbf01c
#घोषणा CO_PIXFMT_32BPP			0x03
#घोषणा CO_PIXFMT_24BPP			0x02
#घोषणा CO_PIXFMT_16BPP			0x01
#घोषणा CO_PIXFMT_8BPP			0x00

#घोषणा CO_REG_FGMIX		0xbf048
#घोषणा CO_FG_MIX_ZERO			0x00
#घोषणा CO_FG_MIX_SRC_AND_DST		0x01
#घोषणा CO_FG_MIX_SRC_AND_NDST		0x02
#घोषणा CO_FG_MIX_SRC			0x03
#घोषणा CO_FG_MIX_NSRC_AND_DST		0x04
#घोषणा CO_FG_MIX_DST			0x05
#घोषणा CO_FG_MIX_SRC_XOR_DST		0x06
#घोषणा CO_FG_MIX_SRC_OR_DST		0x07
#घोषणा CO_FG_MIX_NSRC_AND_NDST		0x08
#घोषणा CO_FG_MIX_SRC_XOR_NDST		0x09
#घोषणा CO_FG_MIX_NDST			0x0a
#घोषणा CO_FG_MIX_SRC_OR_NDST		0x0b
#घोषणा CO_FG_MIX_NSRC			0x0c
#घोषणा CO_FG_MIX_NSRC_OR_DST		0x0d
#घोषणा CO_FG_MIX_NSRC_OR_NDST		0x0e
#घोषणा CO_FG_MIX_ONES			0x0f

#घोषणा CO_REG_FGCOLOUR		0xbf058
#घोषणा CO_REG_BGCOLOUR		0xbf05c
#घोषणा CO_REG_PIXWIDTH		0xbf060
#घोषणा CO_REG_PIXHEIGHT	0xbf062
#घोषणा CO_REG_X_PHASE		0xbf078
#घोषणा CO_REG_CMD_L		0xbf07c
#घोषणा CO_CMD_L_PATTERN_FGCOL		0x8000
#घोषणा CO_CMD_L_INC_LEFT		0x0004
#घोषणा CO_CMD_L_INC_UP			0x0002

#घोषणा CO_REG_CMD_H		0xbf07e
#घोषणा CO_CMD_H_BGSRCMAP		0x8000	/* otherwise bg colour */
#घोषणा CO_CMD_H_FGSRCMAP		0x2000	/* otherwise fg colour */
#घोषणा CO_CMD_H_BLITTER		0x0800

#घोषणा CO_REG_SRC1_PTR		0xbf170
#घोषणा CO_REG_SRC2_PTR		0xbf174
#घोषणा CO_REG_DEST_PTR		0xbf178
#घोषणा CO_REG_DEST_WIDTH	0xbf218

/*
 * Private काष्ठाure
 */
काष्ठा cfb_info;

काष्ठा cyberpro_info अणु
	काष्ठा device	*dev;
	काष्ठा i2c_adapter *i2c;
	अचिन्हित अक्षर	__iomem *regs;
	अक्षर		__iomem *fb;
	अक्षर		dev_name[32];
	अचिन्हित पूर्णांक	fb_size;
	अचिन्हित पूर्णांक	chip_id;
	अचिन्हित पूर्णांक	irq;

	/*
	 * The following is a poपूर्णांकer to be passed पूर्णांकo the
	 * functions below.  The modules outside the मुख्य
	 * cyber2000fb.c driver have no knowledge as to what
	 * is within this काष्ठाure.
	 */
	काष्ठा cfb_info *info;
पूर्ण;

#घोषणा ID_IGA_1682		0
#घोषणा ID_CYBERPRO_2000	1
#घोषणा ID_CYBERPRO_2010	2
#घोषणा ID_CYBERPRO_5000	3

/*
 * Note! Writing to the Cyber20x0 रेजिस्टरs from an पूर्णांकerrupt
 * routine is definitely a bad idea aपंचांग.
 */
पूर्णांक cyber2000fb_attach(काष्ठा cyberpro_info *info, पूर्णांक idx);
व्योम cyber2000fb_detach(पूर्णांक idx);
व्योम cyber2000fb_enable_extregs(काष्ठा cfb_info *cfb);
व्योम cyber2000fb_disable_extregs(काष्ठा cfb_info *cfb);
