<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * comedi/drivers/s626.h
 * Sensoray s626 Comedi driver, header file
 *
 * COMEDI - Linux Control and Measurement Device Interface
 * Copyright (C) 2000 David A. Schleef <ds@schleef.org>
 *
 * Based on Sensoray Model 626 Linux driver Version 0.2
 * Copyright (C) 2002-2004 Sensoray Co., Inc.
 */

#अगर_अघोषित S626_H_INCLUDED
#घोषणा S626_H_INCLUDED

#घोषणा S626_DMABUF_SIZE	4096	/* 4k pages */

#घोषणा S626_ADC_CHANNELS       16
#घोषणा S626_DAC_CHANNELS       4
#घोषणा S626_ENCODER_CHANNELS   6
#घोषणा S626_DIO_CHANNELS       48
#घोषणा S626_DIO_BANKS		3	/* Number of DIO groups. */
#घोषणा S626_DIO_EXTCHANS	40	/*
					 * Number of extended-capability
					 * DIO channels.
					 */

#घोषणा S626_NUM_TRIMDACS	12	/* Number of valid TrimDAC channels. */

/* PCI bus पूर्णांकerface types. */
#घोषणा S626_INTEL		1	/* Intel bus type. */
#घोषणा S626_MOTOROLA		2	/* Motorola bus type. */

#घोषणा S626_PLATFORM		S626_INTEL /* *** SELECT PLATFORM TYPE *** */

#घोषणा S626_RANGE_5V		0x10	/* +/-5V range */
#घोषणा S626_RANGE_10V		0x00	/* +/-10V range */

#घोषणा S626_EOPL		0x80	/* End of ADC poll list marker. */
#घोषणा S626_GSEL_BIPOLAR5V	0x00F0	/* S626_LP_GSEL setting 5V bipolar. */
#घोषणा S626_GSEL_BIPOLAR10V	0x00A0	/* S626_LP_GSEL setting 10V bipolar. */

/* Error codes that must be visible to this base class. */
#घोषणा S626_ERR_ILLEGAL_PARM	0x00010000	/*
						 * Illegal function parameter
						 * value was specअगरied.
						 */
#घोषणा S626_ERR_I2C		0x00020000	/* I2C error. */
#घोषणा S626_ERR_COUNTERSETUP	0x00200000	/*
						 * Illegal setup specअगरied क्रम
						 * counter channel.
						 */
#घोषणा S626_ERR_DEBI_TIMEOUT	0x00400000	/* DEBI transfer समयd out. */

/*
 * Organization (physical order) and size (in DWORDs) of logical DMA buffers
 * contained by ANA_DMABUF.
 */
#घोषणा S626_ADC_DMABUF_DWORDS	40	/*
					 * ADC DMA buffer must hold 16 samples,
					 * plus pre/post garbage samples.
					 */
#घोषणा S626_DAC_WDMABUF_DWORDS	1	/*
					 * DAC output DMA buffer holds a single
					 * sample.
					 */

/* All reमुख्यing space in 4KB DMA buffer is available क्रम the RPS1 program. */

/* Address offsets, in DWORDS, from base of DMA buffer. */
#घोषणा S626_DAC_WDMABUF_OS	S626_ADC_DMABUF_DWORDS

/* Interrupt enable bit in ISR and IER. */
#घोषणा S626_IRQ_GPIO3		0x00000040	/* IRQ enable क्रम GPIO3. */
#घोषणा S626_IRQ_RPS1		0x10000000
#घोषणा S626_ISR_AFOU		0x00000800
/* Audio fअगरo under/overflow  detected. */

#घोषणा S626_IRQ_COINT1A	0x0400	/* counter 1A overflow पूर्णांकerrupt mask */
#घोषणा S626_IRQ_COINT1B	0x0800	/* counter 1B overflow पूर्णांकerrupt mask */
#घोषणा S626_IRQ_COINT2A	0x1000	/* counter 2A overflow पूर्णांकerrupt mask */
#घोषणा S626_IRQ_COINT2B	0x2000	/* counter 2B overflow पूर्णांकerrupt mask */
#घोषणा S626_IRQ_COINT3A	0x4000	/* counter 3A overflow पूर्णांकerrupt mask */
#घोषणा S626_IRQ_COINT3B	0x8000	/* counter 3B overflow पूर्णांकerrupt mask */

/* RPS command codes. */
#घोषणा S626_RPS_CLRSIGNAL	0x00000000	/* CLEAR SIGNAL */
#घोषणा S626_RPS_SETSIGNAL	0x10000000	/* SET SIGNAL */
#घोषणा S626_RPS_NOP		0x00000000	/* NOP */
#घोषणा S626_RPS_PAUSE		0x20000000	/* PAUSE */
#घोषणा S626_RPS_UPLOAD		0x40000000	/* UPLOAD */
#घोषणा S626_RPS_JUMP		0x80000000	/* JUMP */
#घोषणा S626_RPS_LDREG		0x90000100	/* LDREG (1 uपूर्णांक32_t only) */
#घोषणा S626_RPS_STREG		0xA0000100	/* STREG (1 uपूर्णांक32_t only) */
#घोषणा S626_RPS_STOP		0x50000000	/* STOP */
#घोषणा S626_RPS_IRQ		0x60000000	/* IRQ */

#घोषणा S626_RPS_LOGICAL_OR	0x08000000	/* Logical OR conditionals. */
#घोषणा S626_RPS_INVERT		0x04000000	/*
						 * Test क्रम negated
						 * semaphores.
						 */
#घोषणा S626_RPS_DEBI		0x00000002	/* DEBI करोne */

#घोषणा S626_RPS_SIG0		0x00200000	/*
						 * RPS semaphore 0
						 * (used by ADC).
						 */
#घोषणा S626_RPS_SIG1		0x00400000	/*
						 * RPS semaphore 1
						 * (used by DAC).
						 */
#घोषणा S626_RPS_SIG2		0x00800000	/*
						 * RPS semaphore 2
						 * (not used).
						 */
#घोषणा S626_RPS_GPIO2		0x00080000	/* RPS GPIO2 */
#घोषणा S626_RPS_GPIO3		0x00100000	/* RPS GPIO3 */

#घोषणा S626_RPS_SIGADC		S626_RPS_SIG0	/*
						 * Trigger/status क्रम
						 * ADC's RPS program.
						 */
#घोषणा S626_RPS_SIGDAC		S626_RPS_SIG1	/*
						 * Trigger/status क्रम
						 * DAC's RPS program.
						 */

/* RPS घड़ी parameters. */
#घोषणा S626_RPSCLK_SCALAR	8	/*
					 * This is apparent ratio of
					 * PCI/RPS clks (unकरोcumented!!).
					 */
#घोषणा S626_RPSCLK_PER_US	(33 / S626_RPSCLK_SCALAR)
					/*
					 * Number of RPS घड़ीs in one
					 * microsecond.
					 */

/* Event counter source addresses. */
#घोषणा S626_SBA_RPS_A0		0x27	/* Time of RPS0 busy, in PCI घड़ीs. */

/* GPIO स्थिरants. */
#घोषणा S626_GPIO_BASE		0x10004000	/*
						 * GPIO 0,2,3 = inमाला_दो,
						 * GPIO3 = IRQ; GPIO1 = out.
						 */
#घोषणा S626_GPIO1_LO		0x00000000	/* GPIO1 set to LOW. */
#घोषणा S626_GPIO1_HI		0x00001000	/* GPIO1 set to HIGH. */

/* Primary Status Register (PSR) स्थिरants. */
#घोषणा S626_PSR_DEBI_E		0x00040000	/* DEBI event flag. */
#घोषणा S626_PSR_DEBI_S		0x00080000	/* DEBI status flag. */
#घोषणा S626_PSR_A2_IN		0x00008000	/*
						 * Audio output DMA2 protection
						 * address reached.
						 */
#घोषणा S626_PSR_AFOU		0x00000800	/*
						 * Audio FIFO under/overflow
						 * detected.
						 */
#घोषणा S626_PSR_GPIO2		0x00000020	/*
						 * GPIO2 input pin: 0=AdcBusy,
						 * 1=AdcIdle.
						 */
#घोषणा S626_PSR_EC0S		0x00000001	/*
						 * Event counter 0 threshold
						 * reached.
						 */

/* Secondary Status Register (SSR) स्थिरants. */
#घोषणा S626_SSR_AF2_OUT	0x00000200	/*
						 * Audio 2 output FIFO
						 * under/overflow detected.
						 */

/* Master Control Register 1 (MC1) स्थिरants. */
#घोषणा S626_MC1_SOFT_RESET	0x80000000	/* Invoke 7146 soft reset. */
#घोषणा S626_MC1_SHUTDOWN	0x3FFF0000	/*
						 * Shut करोwn all MC1-controlled
						 * enables.
						 */

#घोषणा S626_MC1_ERPS1		0x2000	/* Enab/disable RPS task 1. */
#घोषणा S626_MC1_ERPS0		0x1000	/* Enab/disable RPS task 0. */
#घोषणा S626_MC1_DEBI		0x0800	/* Enab/disable DEBI pins. */
#घोषणा S626_MC1_AUDIO		0x0200	/* Enab/disable audio port pins. */
#घोषणा S626_MC1_I2C		0x0100	/* Enab/disable I2C पूर्णांकerface. */
#घोषणा S626_MC1_A2OUT		0x0008	/* Enab/disable transfer on A2 out. */
#घोषणा S626_MC1_A2IN		0x0004	/* Enab/disable transfer on A2 in. */
#घोषणा S626_MC1_A1IN		0x0001	/* Enab/disable transfer on A1 in. */

/* Master Control Register 2 (MC2) स्थिरants. */
#घोषणा S626_MC2_UPLD_DEBI	0x0002	/* Upload DEBI. */
#घोषणा S626_MC2_UPLD_IIC	0x0001	/* Upload I2C. */
#घोषणा S626_MC2_RPSSIG2	0x2000	/* RPS संकेत 2 (not used). */
#घोषणा S626_MC2_RPSSIG1	0x1000	/* RPS संकेत 1 (DAC RPS busy). */
#घोषणा S626_MC2_RPSSIG0	0x0800	/* RPS संकेत 0 (ADC RPS busy). */

#घोषणा S626_MC2_ADC_RPS	S626_MC2_RPSSIG0	/* ADC RPS busy. */
#घोषणा S626_MC2_DAC_RPS	S626_MC2_RPSSIG1	/* DAC RPS busy. */

/* PCI BUS (SAA7146) REGISTER ADDRESS OFFSETS */
#घोषणा S626_P_PCI_BT_A		0x004C	/* Audio DMA burst/threshold control. */
#घोषणा S626_P_DEBICFG		0x007C	/* DEBI configuration. */
#घोषणा S626_P_DEBICMD		0x0080	/* DEBI command. */
#घोषणा S626_P_DEBIPAGE		0x0084	/* DEBI page. */
#घोषणा S626_P_DEBIAD		0x0088	/* DEBI target address. */
#घोषणा S626_P_I2CCTRL		0x008C	/* I2C control. */
#घोषणा S626_P_I2CSTAT		0x0090	/* I2C status. */
#घोषणा S626_P_BASEA2_IN	0x00AC	/*
					 * Audio input 2 base physical DMAbuf
					 * address.
					 */
#घोषणा S626_P_PROTA2_IN	0x00B0	/*
					 * Audio input 2 physical DMAbuf
					 * protection address.
					 */
#घोषणा S626_P_PAGEA2_IN	0x00B4	/* Audio input 2 paging attributes. */
#घोषणा S626_P_BASEA2_OUT	0x00B8	/*
					 * Audio output 2 base physical DMAbuf
					 * address.
					 */
#घोषणा S626_P_PROTA2_OUT	0x00BC	/*
					 * Audio output 2 physical DMAbuf
					 * protection address.
					 */
#घोषणा S626_P_PAGEA2_OUT	0x00C0	/* Audio output 2 paging attributes. */
#घोषणा S626_P_RPSPAGE0		0x00C4	/* RPS0 page. */
#घोषणा S626_P_RPSPAGE1		0x00C8	/* RPS1 page. */
#घोषणा S626_P_RPS0_TOUT	0x00D4	/* RPS0 समय-out. */
#घोषणा S626_P_RPS1_TOUT	0x00D8	/* RPS1 समय-out. */
#घोषणा S626_P_IER		0x00DC	/* Interrupt enable. */
#घोषणा S626_P_GPIO		0x00E0	/* General-purpose I/O. */
#घोषणा S626_P_EC1SSR		0x00E4	/* Event counter set 1 source select. */
#घोषणा S626_P_ECT1R		0x00EC	/* Event counter threshold set 1. */
#घोषणा S626_P_ACON1		0x00F4	/* Audio control 1. */
#घोषणा S626_P_ACON2		0x00F8	/* Audio control 2. */
#घोषणा S626_P_MC1		0x00FC	/* Master control 1. */
#घोषणा S626_P_MC2		0x0100	/* Master control 2. */
#घोषणा S626_P_RPSADDR0		0x0104	/* RPS0 inकाष्ठाion poपूर्णांकer. */
#घोषणा S626_P_RPSADDR1		0x0108	/* RPS1 inकाष्ठाion poपूर्णांकer. */
#घोषणा S626_P_ISR		0x010C	/* Interrupt status. */
#घोषणा S626_P_PSR		0x0110	/* Primary status. */
#घोषणा S626_P_SSR		0x0114	/* Secondary status. */
#घोषणा S626_P_EC1R		0x0118	/* Event counter set 1. */
#घोषणा S626_P_ADP4		0x0138	/*
					 * Logical audio DMA poपूर्णांकer of audio
					 * input FIFO A2_IN.
					 */
#घोषणा S626_P_FB_BUFFER1	0x0144	/* Audio feedback buffer 1. */
#घोषणा S626_P_FB_BUFFER2	0x0148	/* Audio feedback buffer 2. */
#घोषणा S626_P_TSL1		0x0180	/* Audio समय slot list 1. */
#घोषणा S626_P_TSL2		0x01C0	/* Audio समय slot list 2. */

/* LOCAL BUS (GATE ARRAY) REGISTER ADDRESS OFFSETS */
/* Analog I/O रेजिस्टरs: */
#घोषणा S626_LP_DACPOL		0x0082	/* Write DAC polarity. */
#घोषणा S626_LP_GSEL		0x0084	/* Write ADC gain. */
#घोषणा S626_LP_ISEL		0x0086	/* Write ADC channel select. */

/* Digital I/O रेजिस्टरs */
#घोषणा S626_LP_RDDIN(x)	(0x0040 + (x) * 0x10)	/* R: digital input */
#घोषणा S626_LP_WRINTSEL(x)	(0x0042 + (x) * 0x10)	/* W: पूर्णांक enable */
#घोषणा S626_LP_WREDGSEL(x)	(0x0044 + (x) * 0x10)	/* W: edge selection */
#घोषणा S626_LP_WRCAPSEL(x)	(0x0046 + (x) * 0x10)	/* W: capture enable */
#घोषणा S626_LP_RDCAPFLG(x)	(0x0048 + (x) * 0x10)	/* R: edges captured */
#घोषणा S626_LP_WRDOUT(x)	(0x0048 + (x) * 0x10)	/* W: digital output */
#घोषणा S626_LP_RDINTSEL(x)	(0x004a + (x) * 0x10)	/* R: पूर्णांक enable */
#घोषणा S626_LP_RDEDGSEL(x)	(0x004c + (x) * 0x10)	/* R: edge selection */
#घोषणा S626_LP_RDCAPSEL(x)	(0x004e + (x) * 0x10)	/* R: capture enable */

/* Counter रेजिस्टरs (पढ़ो/ग_लिखो): 0A 1A 2A 0B 1B 2B */
#घोषणा S626_LP_CRA(x)		(0x0000 + (((x) % 3) * 0x4))
#घोषणा S626_LP_CRB(x)		(0x0002 + (((x) % 3) * 0x4))

/* Counter PreLoad (ग_लिखो) and Latch (पढ़ो) Registers: 0A 1A 2A 0B 1B 2B */
#घोषणा S626_LP_CNTR(x)		(0x000c  + (((x) < 3) ? 0x0 : 0x4) + \
					   (((x) % 3) * 0x8))

/* Miscellaneous Registers (पढ़ो/ग_लिखो): */
#घोषणा S626_LP_MISC1		0x0088	/* Read/ग_लिखो Misc1. */
#घोषणा S626_LP_WRMISC2		0x0090	/* Write Misc2. */
#घोषणा S626_LP_RDMISC2		0x0082	/* Read Misc2. */

/* Bit masks क्रम MISC1 रेजिस्टर that are the same क्रम पढ़ोs and ग_लिखोs. */
#घोषणा S626_MISC1_WENABLE	0x8000	/*
					 * enab ग_लिखोs to MISC2 (except Clear
					 * Watchकरोg bit).
					 */
#घोषणा S626_MISC1_WDISABLE	0x0000	/* Disable ग_लिखोs to MISC2. */
#घोषणा S626_MISC1_EDCAP	0x1000	/*
					 * Enable edge capture on DIO chans
					 * specअगरied by S626_LP_WRCAPSELx.
					 */
#घोषणा S626_MISC1_NOEDCAP	0x0000	/*
					 * Disable edge capture on specअगरied
					 * DIO chans.
					 */

/* Bit masks क्रम MISC1 रेजिस्टर पढ़ोs. */
#घोषणा S626_RDMISC1_WDTIMEOUT	0x4000	/* Watchकरोg समयr समयd out. */

/* Bit masks क्रम MISC2 रेजिस्टर ग_लिखोs. */
#घोषणा S626_WRMISC2_WDCLEAR	0x8000	/* Reset watchकरोg समयr to zero. */
#घोषणा S626_WRMISC2_CHARGE_ENABLE 0x4000 /* Enable battery trickle अक्षरging. */

/* Bit masks क्रम MISC2 रेजिस्टर that are the same क्रम पढ़ोs and ग_लिखोs. */
#घोषणा S626_MISC2_BATT_ENABLE	0x0008	/* Backup battery enable. */
#घोषणा S626_MISC2_WDENABLE	0x0004	/* Watchकरोg समयr enable. */
#घोषणा S626_MISC2_WDPERIOD_MASK 0x0003	/* Watchकरोg पूर्णांकerval select mask. */

/* Bit masks क्रम ACON1 रेजिस्टर. */
#घोषणा S626_A2_RUN		0x40000000	/* Run A2 based on TSL2. */
#घोषणा S626_A1_RUN		0x20000000	/* Run A1 based on TSL1. */
#घोषणा S626_A1_SWAP		0x00200000	/* Use big-endian क्रम A1. */
#घोषणा S626_A2_SWAP		0x00100000	/* Use big-endian क्रम A2. */
#घोषणा S626_WS_MODES		0x00019999	/*
						 * WS0 = TSL1 trigger input,
						 * WS1-WS4 = CS* outमाला_दो.
						 */

#अगर (S626_PLATFORM == S626_INTEL)	/*
					 * Base ACON1 config: always run
					 * A1 based on TSL1.
					 */
#घोषणा S626_ACON1_BASE		(S626_WS_MODES | S626_A1_RUN)
#या_अगर S626_PLATFORM == S626_MOTOROLA
#घोषणा S626_ACON1_BASE		\
	(S626_WS_MODES | S626_A1_RUN | S626_A1_SWAP | S626_A2_SWAP)
#पूर्ण_अगर

#घोषणा S626_ACON1_ADCSTART	S626_ACON1_BASE	/*
						 * Start ADC: run A1
						 * based on TSL1.
						 */
#घोषणा S626_ACON1_DACSTART	(S626_ACON1_BASE | S626_A2_RUN)
/* Start transmit to DAC: run A2 based on TSL2. */
#घोषणा S626_ACON1_DACSTOP	S626_ACON1_BASE	/* Halt A2. */

/* Bit masks क्रम ACON2 रेजिस्टर. */
#घोषणा S626_A1_CLKSRC_BCLK1	0x00000000	/* A1 bit rate = BCLK1 (ADC). */
#घोषणा S626_A2_CLKSRC_X1	0x00800000	/*
						 * A2 bit rate = ACLK/1
						 * (DACs).
						 */
#घोषणा S626_A2_CLKSRC_X2	0x00C00000	/*
						 * A2 bit rate = ACLK/2
						 * (DACs).
						 */
#घोषणा S626_A2_CLKSRC_X4	0x01400000	/*
						 * A2 bit rate = ACLK/4
						 * (DACs).
						 */
#घोषणा S626_INVERT_BCLK2	0x00100000	/* Invert BCLK2 (DACs). */
#घोषणा S626_BCLK2_OE		0x00040000	/* Enable BCLK2 (DACs). */
#घोषणा S626_ACON2_XORMASK	0x000C0000	/*
						 * XOR mask क्रम ACON2
						 * active-low bits.
						 */

#घोषणा S626_ACON2_INIT		(S626_ACON2_XORMASK ^ \
				 (S626_A1_CLKSRC_BCLK1 | S626_A2_CLKSRC_X2 | \
				  S626_INVERT_BCLK2 | S626_BCLK2_OE))

/* Bit masks क्रम बारlot records. */
#घोषणा S626_WS1		0x40000000	/* WS output to निश्चित. */
#घोषणा S626_WS2		0x20000000
#घोषणा S626_WS3		0x10000000
#घोषणा S626_WS4		0x08000000
#घोषणा S626_RSD1		0x01000000	/* Shअगरt A1 data in on SD1. */
#घोषणा S626_SDW_A1		0x00800000	/*
						 * Store rcv'd अक्षर at next अक्षर
						 * slot of DWORD1 buffer.
						 */
#घोषणा S626_SIB_A1		0x00400000	/*
						 * Store rcv'd अक्षर at next
						 * अक्षर slot of FB1 buffer.
						 */
#घोषणा S626_SF_A1		0x00200000	/*
						 * Write अचिन्हित दीर्घ
						 * buffer to input FIFO.
						 */

/* Select parallel-to-serial converter's data source: */
#घोषणा S626_XFIFO_0		0x00000000	/* Data fअगरo byte 0. */
#घोषणा S626_XFIFO_1		0x00000010	/* Data fअगरo byte 1. */
#घोषणा S626_XFIFO_2		0x00000020	/* Data fअगरo byte 2. */
#घोषणा S626_XFIFO_3		0x00000030	/* Data fअगरo byte 3. */
#घोषणा S626_XFB0		0x00000040	/* FB_BUFFER byte 0. */
#घोषणा S626_XFB1		0x00000050	/* FB_BUFFER byte 1. */
#घोषणा S626_XFB2		0x00000060	/* FB_BUFFER byte 2. */
#घोषणा S626_XFB3		0x00000070	/* FB_BUFFER byte 3. */
#घोषणा S626_SIB_A2		0x00000200	/*
						 * Store next dword from A2's
						 * input shअगरter to FB2
						 * buffer.
						 */
#घोषणा S626_SF_A2		0x00000100	/*
						 * Store next dword from A2's
						 * input shअगरter to its input
						 * fअगरo.
						 */
#घोषणा S626_LF_A2		0x00000080	/*
						 * Load next dword from A2's
						 * output fअगरo पूर्णांकo its
						 * output dword buffer.
						 */
#घोषणा S626_XSD2		0x00000008	/* Shअगरt data out on SD2. */
#घोषणा S626_RSD3		0x00001800	/* Shअगरt data in on SD3. */
#घोषणा S626_RSD2		0x00001000	/* Shअगरt data in on SD2. */
#घोषणा S626_LOW_A2		0x00000002	/*
						 * Drive last SD low क्रम 7 clks,
						 * then tri-state.
						 */
#घोषणा S626_EOS		0x00000001	/* End of superframe. */

/* I2C configuration स्थिरants. */
#घोषणा S626_I2C_CLKSEL		0x0400		/*
						 * I2C bit rate =
						 * PCIclk/480 = 68.75 KHz.
						 */
#घोषणा S626_I2C_BITRATE	68.75		/*
						 * I2C bus data bit rate
						 * (determined by
						 * S626_I2C_CLKSEL) in KHz.
						 */
#घोषणा S626_I2C_WRTIME		15.0		/*
						 * Worst हाल समय, in msec,
						 * क्रम EEPROM पूर्णांकernal ग_लिखो
						 * op.
						 */

/* I2C manअगरest स्थिरants. */

/* Max retries to रुको क्रम EEPROM ग_लिखो. */
#घोषणा S626_I2C_RETRIES	(S626_I2C_WRTIME * S626_I2C_BITRATE / 9.0)
#घोषणा S626_I2C_ERR		0x0002	/* I2C control/status flag ERROR. */
#घोषणा S626_I2C_BUSY		0x0001	/* I2C control/status flag BUSY. */
#घोषणा S626_I2C_ABORT		0x0080	/* I2C status flag ABORT. */
#घोषणा S626_I2C_ATTRSTART	0x3	/* I2C attribute START. */
#घोषणा S626_I2C_ATTRCONT	0x2	/* I2C attribute CONT. */
#घोषणा S626_I2C_ATTRSTOP	0x1	/* I2C attribute STOP. */
#घोषणा S626_I2C_ATTRNOP	0x0	/* I2C attribute NOP. */

/* Code macros used क्रम स्थिरructing I2C command bytes. */
#घोषणा S626_I2C_B2(ATTR, VAL)	(((ATTR) << 6) | ((VAL) << 24))
#घोषणा S626_I2C_B1(ATTR, VAL)	(((ATTR) << 4) | ((VAL) << 16))
#घोषणा S626_I2C_B0(ATTR, VAL)	(((ATTR) << 2) | ((VAL) <<  8))

/* DEBI command स्थिरants. */
#घोषणा S626_DEBI_CMD_SIZE16	(2 << 17)	/*
						 * Transfer size is always
						 * 2 bytes.
						 */
#घोषणा S626_DEBI_CMD_READ	0x00010000	/* Read operation. */
#घोषणा S626_DEBI_CMD_WRITE	0x00000000	/* Write operation. */

/* Read immediate 2 bytes. */
#घोषणा S626_DEBI_CMD_RDWORD	(S626_DEBI_CMD_READ | S626_DEBI_CMD_SIZE16)

/* Write immediate 2 bytes. */
#घोषणा S626_DEBI_CMD_WRWORD	(S626_DEBI_CMD_WRITE | S626_DEBI_CMD_SIZE16)

/* DEBI configuration स्थिरants. */
#घोषणा S626_DEBI_CFG_XIRQ_EN	0x80000000	/*
						 * Enable बाह्यal पूर्णांकerrupt
						 * on GPIO3.
						 */
#घोषणा S626_DEBI_CFG_XRESUME	0x40000000	/* Resume block */
						/*
						 * Transfer when XIRQ
						 * deनिश्चितed.
						 */
#घोषणा S626_DEBI_CFG_TOQ	0x03C00000	/* Timeout (15 PCI cycles). */
#घोषणा S626_DEBI_CFG_FAST	0x10000000	/* Fast mode enable. */

/* 4-bit field that specअगरies DEBI समयout value in PCI घड़ी cycles: */
#घोषणा S626_DEBI_CFG_TOUT_BIT	22	/*
					 * Finish DEBI cycle after this many
					 * घड़ीs.
					 */

/* 2-bit field that specअगरies Endian byte lane steering: */
#घोषणा S626_DEBI_CFG_SWAP_NONE	0x00000000	/*
						 * Straight - करोn't swap any
						 * bytes (Intel).
						 */
#घोषणा S626_DEBI_CFG_SWAP_2	0x00100000	/* 2-byte swap (Motorola). */
#घोषणा S626_DEBI_CFG_SWAP_4	0x00200000	/* 4-byte swap. */
#घोषणा S626_DEBI_CFG_SLAVE16	0x00080000	/*
						 * Slave is able to serve
						 * 16-bit cycles.
						 */
#घोषणा S626_DEBI_CFG_INC	0x00040000	/*
						 * Enable address increment
						 * क्रम block transfers.
						 */
#घोषणा S626_DEBI_CFG_INTEL	0x00020000	/* Intel style local bus. */
#घोषणा S626_DEBI_CFG_TIMEROFF	0x00010000	/* Disable समयr. */

#अगर S626_PLATFORM == S626_INTEL

#घोषणा S626_DEBI_TOUT		7	/*
					 * Wait 7 PCI घड़ीs (212 ns) beक्रमe
					 * polling RDY.
					 */

/* Intel byte lane steering (pass through all byte lanes). */
#घोषणा S626_DEBI_SWAP		S626_DEBI_CFG_SWAP_NONE

#या_अगर S626_PLATFORM == S626_MOTOROLA

#घोषणा S626_DEBI_TOUT		15	/*
					 * Wait 15 PCI घड़ीs (454 ns) maximum
					 * beक्रमe timing out.
					 */

/* Motorola byte lane steering. */
#घोषणा S626_DEBI_SWAP		S626_DEBI_CFG_SWAP_2

#पूर्ण_अगर

/* DEBI page table स्थिरants. */
#घोषणा S626_DEBI_PAGE_DISABLE	0x00000000	/* Paging disable. */

/* ******* EXTRA FROM OTHER SENSORAY  * .h  ******* */

/* LoadSrc values: */
#घोषणा S626_LOADSRC_INDX	0	/* Preload core in response to Index. */
#घोषणा S626_LOADSRC_OVER	1	/*
					 * Preload core in response to
					 * Overflow.
					 */
#घोषणा S626_LOADSRCB_OVERA	2	/*
					 * Preload B core in response to
					 * A Overflow.
					 */
#घोषणा S626_LOADSRC_NONE	3	/* Never preload core. */

/* IntSrc values: */
#घोषणा S626_INTSRC_NONE	0	/* Interrupts disabled. */
#घोषणा S626_INTSRC_OVER	1	/* Interrupt on Overflow. */
#घोषणा S626_INTSRC_INDX	2	/* Interrupt on Index. */
#घोषणा S626_INTSRC_BOTH	3	/* Interrupt on Index or Overflow. */

/* LatchSrc values: */
#घोषणा S626_LATCHSRC_AB_READ	0	/* Latch on पढ़ो. */
#घोषणा S626_LATCHSRC_A_INDXA	1	/* Latch A on A Index. */
#घोषणा S626_LATCHSRC_B_INDXB	2	/* Latch B on B Index. */
#घोषणा S626_LATCHSRC_B_OVERA	3	/* Latch B on A Overflow. */

/* IndxSrc values: */
#घोषणा S626_INDXSRC_ENCODER	0	/* Encoder. */
#घोषणा S626_INDXSRC_DIGIN	1	/* Digital inमाला_दो. */
#घोषणा S626_INDXSRC_SOFT	2	/* S/w controlled by IndxPol bit. */
#घोषणा S626_INDXSRC_DISABLED	3	/* Index disabled. */

/* IndxPol values: */
#घोषणा S626_INDXPOL_POS	0	/* Index input is active high. */
#घोषणा S626_INDXPOL_NEG	1	/* Index input is active low. */

/* Logical encoder mode values: */
#घोषणा S626_ENCMODE_COUNTER	0	/* Counter mode. */
#घोषणा S626_ENCMODE_TIMER	2	/* Timer mode. */
#घोषणा S626_ENCMODE_EXTENDER	3	/* Extender mode. */

/* Physical CntSrc values (क्रम Counter A source and Counter B source): */
#घोषणा S626_CNTSRC_ENCODER	0	/* Encoder */
#घोषणा S626_CNTSRC_DIGIN	1	/* Digital inमाला_दो */
#घोषणा S626_CNTSRC_SYSCLK	2	/* System घड़ी up */
#घोषणा S626_CNTSRC_SYSCLK_DOWN	3	/* System घड़ी करोwn */

/* ClkPol values: */
#घोषणा S626_CLKPOL_POS		0	/*
					 * Counter/Extender घड़ी is
					 * active high.
					 */
#घोषणा S626_CLKPOL_NEG		1	/*
					 * Counter/Extender घड़ी is
					 * active low.
					 */
#घोषणा S626_CNTसूची_UP		0	/* Timer counts up. */
#घोषणा S626_CNTसूची_DOWN	1	/* Timer counts करोwn. */

/* ClkEnab values: */
#घोषणा S626_CLKENAB_ALWAYS	0	/* Clock always enabled. */
#घोषणा S626_CLKENAB_INDEX	1	/* Clock is enabled by index. */

/* ClkMult values: */
#घोषणा S626_CLKMULT_4X		0	/* 4x घड़ी multiplier. */
#घोषणा S626_CLKMULT_2X		1	/* 2x घड़ी multiplier. */
#घोषणा S626_CLKMULT_1X		2	/* 1x घड़ी multiplier. */
#घोषणा S626_CLKMULT_SPECIAL	3	/* Special घड़ी multiplier value. */

/* Sanity-check limits क्रम parameters. */

#घोषणा S626_NUM_COUNTERS	6	/*
					 * Maximum valid counter
					 * logical channel number.
					 */
#घोषणा S626_NUM_INTSOURCES	4
#घोषणा S626_NUM_LATCHSOURCES	4
#घोषणा S626_NUM_CLKMULTS	4
#घोषणा S626_NUM_CLKSOURCES	4
#घोषणा S626_NUM_CLKPOLS	2
#घोषणा S626_NUM_INDEXPOLS	2
#घोषणा S626_NUM_INDEXSOURCES	2
#घोषणा S626_NUM_LOADTRIGS	4

/* General macros क्रम manipulating bitfields: */
#घोषणा S626_MAKE(x, w, p)	(((x) & ((1 << (w)) - 1)) << (p))
#घोषणा S626_UNMAKE(v, w, p)	(((v) >> (p)) & ((1 << (w)) - 1))

/* Bit field positions in CRA: */
#घोषणा S626_CRABIT_INDXSRC_B	14	/* B index source. */
#घोषणा S626_CRABIT_CNTSRC_B	12	/* B counter source. */
#घोषणा S626_CRABIT_INDXPOL_A	11	/* A index polarity. */
#घोषणा S626_CRABIT_LOADSRC_A	 9	/* A preload trigger. */
#घोषणा S626_CRABIT_CLKMULT_A	 7	/* A घड़ी multiplier. */
#घोषणा S626_CRABIT_INTSRC_A	 5	/* A पूर्णांकerrupt source. */
#घोषणा S626_CRABIT_CLKPOL_A	 4	/* A घड़ी polarity. */
#घोषणा S626_CRABIT_INDXSRC_A	 2	/* A index source. */
#घोषणा S626_CRABIT_CNTSRC_A	 0	/* A counter source. */

/* Bit field widths in CRA: */
#घोषणा S626_CRAWID_INDXSRC_B	2
#घोषणा S626_CRAWID_CNTSRC_B	2
#घोषणा S626_CRAWID_INDXPOL_A	1
#घोषणा S626_CRAWID_LOADSRC_A	2
#घोषणा S626_CRAWID_CLKMULT_A	2
#घोषणा S626_CRAWID_INTSRC_A	2
#घोषणा S626_CRAWID_CLKPOL_A	1
#घोषणा S626_CRAWID_INDXSRC_A	2
#घोषणा S626_CRAWID_CNTSRC_A	2

/* Bit field masks क्रम CRA: */
#घोषणा S626_CRAMSK_INDXSRC_B	S626_SET_CRA_INDXSRC_B(~0)
#घोषणा S626_CRAMSK_CNTSRC_B	S626_SET_CRA_CNTSRC_B(~0)
#घोषणा S626_CRAMSK_INDXPOL_A	S626_SET_CRA_INDXPOL_A(~0)
#घोषणा S626_CRAMSK_LOADSRC_A	S626_SET_CRA_LOADSRC_A(~0)
#घोषणा S626_CRAMSK_CLKMULT_A	S626_SET_CRA_CLKMULT_A(~0)
#घोषणा S626_CRAMSK_INTSRC_A	S626_SET_CRA_INTSRC_A(~0)
#घोषणा S626_CRAMSK_CLKPOL_A	S626_SET_CRA_CLKPOL_A(~0)
#घोषणा S626_CRAMSK_INDXSRC_A	S626_SET_CRA_INDXSRC_A(~0)
#घोषणा S626_CRAMSK_CNTSRC_A	S626_SET_CRA_CNTSRC_A(~0)

/* Conकाष्ठा parts of the CRA value: */
#घोषणा S626_SET_CRA_INDXSRC_B(x)	\
	S626_MAKE((x), S626_CRAWID_INDXSRC_B, S626_CRABIT_INDXSRC_B)
#घोषणा S626_SET_CRA_CNTSRC_B(x)	\
	S626_MAKE((x), S626_CRAWID_CNTSRC_B, S626_CRABIT_CNTSRC_B)
#घोषणा S626_SET_CRA_INDXPOL_A(x)	\
	S626_MAKE((x), S626_CRAWID_INDXPOL_A, S626_CRABIT_INDXPOL_A)
#घोषणा S626_SET_CRA_LOADSRC_A(x)	\
	S626_MAKE((x), S626_CRAWID_LOADSRC_A, S626_CRABIT_LOADSRC_A)
#घोषणा S626_SET_CRA_CLKMULT_A(x)	\
	S626_MAKE((x), S626_CRAWID_CLKMULT_A, S626_CRABIT_CLKMULT_A)
#घोषणा S626_SET_CRA_INTSRC_A(x)	\
	S626_MAKE((x), S626_CRAWID_INTSRC_A, S626_CRABIT_INTSRC_A)
#घोषणा S626_SET_CRA_CLKPOL_A(x)	\
	S626_MAKE((x), S626_CRAWID_CLKPOL_A, S626_CRABIT_CLKPOL_A)
#घोषणा S626_SET_CRA_INDXSRC_A(x)	\
	S626_MAKE((x), S626_CRAWID_INDXSRC_A, S626_CRABIT_INDXSRC_A)
#घोषणा S626_SET_CRA_CNTSRC_A(x)	\
	S626_MAKE((x), S626_CRAWID_CNTSRC_A, S626_CRABIT_CNTSRC_A)

/* Extract parts of the CRA value: */
#घोषणा S626_GET_CRA_INDXSRC_B(v)	\
	S626_UNMAKE((v), S626_CRAWID_INDXSRC_B, S626_CRABIT_INDXSRC_B)
#घोषणा S626_GET_CRA_CNTSRC_B(v)	\
	S626_UNMAKE((v), S626_CRAWID_CNTSRC_B, S626_CRABIT_CNTSRC_B)
#घोषणा S626_GET_CRA_INDXPOL_A(v)	\
	S626_UNMAKE((v), S626_CRAWID_INDXPOL_A, S626_CRABIT_INDXPOL_A)
#घोषणा S626_GET_CRA_LOADSRC_A(v)	\
	S626_UNMAKE((v), S626_CRAWID_LOADSRC_A, S626_CRABIT_LOADSRC_A)
#घोषणा S626_GET_CRA_CLKMULT_A(v)	\
	S626_UNMAKE((v), S626_CRAWID_CLKMULT_A, S626_CRABIT_CLKMULT_A)
#घोषणा S626_GET_CRA_INTSRC_A(v)	\
	S626_UNMAKE((v), S626_CRAWID_INTSRC_A, S626_CRABIT_INTSRC_A)
#घोषणा S626_GET_CRA_CLKPOL_A(v)	\
	S626_UNMAKE((v), S626_CRAWID_CLKPOL_A, S626_CRABIT_CLKPOL_A)
#घोषणा S626_GET_CRA_INDXSRC_A(v)	\
	S626_UNMAKE((v), S626_CRAWID_INDXSRC_A, S626_CRABIT_INDXSRC_A)
#घोषणा S626_GET_CRA_CNTSRC_A(v)	\
	S626_UNMAKE((v), S626_CRAWID_CNTSRC_A, S626_CRABIT_CNTSRC_A)

/* Bit field positions in CRB: */
#घोषणा S626_CRBBIT_INTRESETCMD	15	/* (w) Interrupt reset command. */
#घोषणा S626_CRBBIT_CNTसूची_B	15	/* (r) B counter direction. */
#घोषणा S626_CRBBIT_INTRESET_B	14	/* (w) B पूर्णांकerrupt reset enable. */
#घोषणा S626_CRBBIT_OVERDO_A	14	/* (r) A overflow routed to dig. out. */
#घोषणा S626_CRBBIT_INTRESET_A	13	/* (w) A पूर्णांकerrupt reset enable. */
#घोषणा S626_CRBBIT_OVERDO_B	13	/* (r) B overflow routed to dig. out. */
#घोषणा S626_CRBBIT_CLKENAB_A	12	/* A घड़ी enable. */
#घोषणा S626_CRBBIT_INTSRC_B	10	/* B पूर्णांकerrupt source. */
#घोषणा S626_CRBBIT_LATCHSRC	 8	/* A/B latch source. */
#घोषणा S626_CRBBIT_LOADSRC_B	 6	/* B preload trigger. */
#घोषणा S626_CRBBIT_CLEAR_B	 7	/* B cleared when A overflows. */
#घोषणा S626_CRBBIT_CLKMULT_B	 3	/* B घड़ी multiplier. */
#घोषणा S626_CRBBIT_CLKENAB_B	 2	/* B घड़ी enable. */
#घोषणा S626_CRBBIT_INDXPOL_B	 1	/* B index polarity. */
#घोषणा S626_CRBBIT_CLKPOL_B	 0	/* B घड़ी polarity. */

/* Bit field widths in CRB: */
#घोषणा S626_CRBWID_INTRESETCMD	1
#घोषणा S626_CRBWID_CNTसूची_B	1
#घोषणा S626_CRBWID_INTRESET_B	1
#घोषणा S626_CRBWID_OVERDO_A	1
#घोषणा S626_CRBWID_INTRESET_A	1
#घोषणा S626_CRBWID_OVERDO_B	1
#घोषणा S626_CRBWID_CLKENAB_A	1
#घोषणा S626_CRBWID_INTSRC_B	2
#घोषणा S626_CRBWID_LATCHSRC	2
#घोषणा S626_CRBWID_LOADSRC_B	2
#घोषणा S626_CRBWID_CLEAR_B	1
#घोषणा S626_CRBWID_CLKMULT_B	2
#घोषणा S626_CRBWID_CLKENAB_B	1
#घोषणा S626_CRBWID_INDXPOL_B	1
#घोषणा S626_CRBWID_CLKPOL_B	1

/* Bit field masks क्रम CRB: */
#घोषणा S626_CRBMSK_INTRESETCMD	S626_SET_CRB_INTRESETCMD(~0)	/* (w) */
#घोषणा S626_CRBMSK_CNTसूची_B	S626_CRBMSK_INTRESETCMD		/* (r) */
#घोषणा S626_CRBMSK_INTRESET_B	S626_SET_CRB_INTRESET_B(~0)	/* (w) */
#घोषणा S626_CRBMSK_OVERDO_A	S626_CRBMSK_INTRESET_B		/* (r) */
#घोषणा S626_CRBMSK_INTRESET_A	S626_SET_CRB_INTRESET_A(~0)	/* (w) */
#घोषणा S626_CRBMSK_OVERDO_B	S626_CRBMSK_INTRESET_A		/* (r) */
#घोषणा S626_CRBMSK_CLKENAB_A	S626_SET_CRB_CLKENAB_A(~0)
#घोषणा S626_CRBMSK_INTSRC_B	S626_SET_CRB_INTSRC_B(~0)
#घोषणा S626_CRBMSK_LATCHSRC	S626_SET_CRB_LATCHSRC(~0)
#घोषणा S626_CRBMSK_LOADSRC_B	S626_SET_CRB_LOADSRC_B(~0)
#घोषणा S626_CRBMSK_CLEAR_B	S626_SET_CRB_CLEAR_B(~0)
#घोषणा S626_CRBMSK_CLKMULT_B	S626_SET_CRB_CLKMULT_B(~0)
#घोषणा S626_CRBMSK_CLKENAB_B	S626_SET_CRB_CLKENAB_B(~0)
#घोषणा S626_CRBMSK_INDXPOL_B	S626_SET_CRB_INDXPOL_B(~0)
#घोषणा S626_CRBMSK_CLKPOL_B	S626_SET_CRB_CLKPOL_B(~0)

/* Interrupt reset control bits. */
#घोषणा S626_CRBMSK_INTCTRL	(S626_CRBMSK_INTRESETCMD | \
				 S626_CRBMSK_INTRESET_A | \
				 S626_CRBMSK_INTRESET_B)

/* Conकाष्ठा parts of the CRB value: */
#घोषणा S626_SET_CRB_INTRESETCMD(x)	\
	S626_MAKE((x), S626_CRBWID_INTRESETCMD, S626_CRBBIT_INTRESETCMD)
#घोषणा S626_SET_CRB_INTRESET_B(x)	\
	S626_MAKE((x), S626_CRBWID_INTRESET_B, S626_CRBBIT_INTRESET_B)
#घोषणा S626_SET_CRB_INTRESET_A(x)	\
	S626_MAKE((x), S626_CRBWID_INTRESET_A, S626_CRBBIT_INTRESET_A)
#घोषणा S626_SET_CRB_CLKENAB_A(x)	\
	S626_MAKE((x), S626_CRBWID_CLKENAB_A, S626_CRBBIT_CLKENAB_A)
#घोषणा S626_SET_CRB_INTSRC_B(x)	\
	S626_MAKE((x), S626_CRBWID_INTSRC_B, S626_CRBBIT_INTSRC_B)
#घोषणा S626_SET_CRB_LATCHSRC(x)	\
	S626_MAKE((x), S626_CRBWID_LATCHSRC, S626_CRBBIT_LATCHSRC)
#घोषणा S626_SET_CRB_LOADSRC_B(x)	\
	S626_MAKE((x), S626_CRBWID_LOADSRC_B, S626_CRBBIT_LOADSRC_B)
#घोषणा S626_SET_CRB_CLEAR_B(x)	\
	S626_MAKE((x), S626_CRBWID_CLEAR_B, S626_CRBBIT_CLEAR_B)
#घोषणा S626_SET_CRB_CLKMULT_B(x)	\
	S626_MAKE((x), S626_CRBWID_CLKMULT_B, S626_CRBBIT_CLKMULT_B)
#घोषणा S626_SET_CRB_CLKENAB_B(x)	\
	S626_MAKE((x), S626_CRBWID_CLKENAB_B, S626_CRBBIT_CLKENAB_B)
#घोषणा S626_SET_CRB_INDXPOL_B(x)	\
	S626_MAKE((x), S626_CRBWID_INDXPOL_B, S626_CRBBIT_INDXPOL_B)
#घोषणा S626_SET_CRB_CLKPOL_B(x)	\
	S626_MAKE((x), S626_CRBWID_CLKPOL_B, S626_CRBBIT_CLKPOL_B)

/* Extract parts of the CRB value: */
#घोषणा S626_GET_CRB_CNTसूची_B(v)	\
	S626_UNMAKE((v), S626_CRBWID_CNTसूची_B, S626_CRBBIT_CNTसूची_B)
#घोषणा S626_GET_CRB_OVERDO_A(v)	\
	S626_UNMAKE((v), S626_CRBWID_OVERDO_A, S626_CRBBIT_OVERDO_A)
#घोषणा S626_GET_CRB_OVERDO_B(v)	\
	S626_UNMAKE((v), S626_CRBWID_OVERDO_B, S626_CRBBIT_OVERDO_B)
#घोषणा S626_GET_CRB_CLKENAB_A(v)	\
	S626_UNMAKE((v), S626_CRBWID_CLKENAB_A, S626_CRBBIT_CLKENAB_A)
#घोषणा S626_GET_CRB_INTSRC_B(v)	\
	S626_UNMAKE((v), S626_CRBWID_INTSRC_B, S626_CRBBIT_INTSRC_B)
#घोषणा S626_GET_CRB_LATCHSRC(v)	\
	S626_UNMAKE((v), S626_CRBWID_LATCHSRC, S626_CRBBIT_LATCHSRC)
#घोषणा S626_GET_CRB_LOADSRC_B(v)	\
	S626_UNMAKE((v), S626_CRBWID_LOADSRC_B, S626_CRBBIT_LOADSRC_B)
#घोषणा S626_GET_CRB_CLEAR_B(v)	\
	S626_UNMAKE((v), S626_CRBWID_CLEAR_B, S626_CRBBIT_CLEAR_B)
#घोषणा S626_GET_CRB_CLKMULT_B(v)	\
	S626_UNMAKE((v), S626_CRBWID_CLKMULT_B, S626_CRBBIT_CLKMULT_B)
#घोषणा S626_GET_CRB_CLKENAB_B(v)	\
	S626_UNMAKE((v), S626_CRBWID_CLKENAB_B, S626_CRBBIT_CLKENAB_B)
#घोषणा S626_GET_CRB_INDXPOL_B(v)	\
	S626_UNMAKE((v), S626_CRBWID_INDXPOL_B, S626_CRBBIT_INDXPOL_B)
#घोषणा S626_GET_CRB_CLKPOL_B(v)	\
	S626_UNMAKE((v), S626_CRBWID_CLKPOL_B, S626_CRBBIT_CLKPOL_B)

/* Bit field positions क्रम standardized SETUP काष्ठाure: */
#घोषणा S626_STDBIT_INTSRC	13
#घोषणा S626_STDBIT_LATCHSRC	11
#घोषणा S626_STDBIT_LOADSRC	 9
#घोषणा S626_STDBIT_INDXSRC	 7
#घोषणा S626_STDBIT_INDXPOL	 6
#घोषणा S626_STDBIT_ENCMODE	 4
#घोषणा S626_STDBIT_CLKPOL	 3
#घोषणा S626_STDBIT_CLKMULT	 1
#घोषणा S626_STDBIT_CLKENAB	 0

/* Bit field widths क्रम standardized SETUP काष्ठाure: */
#घोषणा S626_STDWID_INTSRC	2
#घोषणा S626_STDWID_LATCHSRC	2
#घोषणा S626_STDWID_LOADSRC	2
#घोषणा S626_STDWID_INDXSRC	2
#घोषणा S626_STDWID_INDXPOL	1
#घोषणा S626_STDWID_ENCMODE	2
#घोषणा S626_STDWID_CLKPOL	1
#घोषणा S626_STDWID_CLKMULT	2
#घोषणा S626_STDWID_CLKENAB	1

/* Bit field masks क्रम standardized SETUP काष्ठाure: */
#घोषणा S626_STDMSK_INTSRC	S626_SET_STD_INTSRC(~0)
#घोषणा S626_STDMSK_LATCHSRC	S626_SET_STD_LATCHSRC(~0)
#घोषणा S626_STDMSK_LOADSRC	S626_SET_STD_LOADSRC(~0)
#घोषणा S626_STDMSK_INDXSRC	S626_SET_STD_INDXSRC(~0)
#घोषणा S626_STDMSK_INDXPOL	S626_SET_STD_INDXPOL(~0)
#घोषणा S626_STDMSK_ENCMODE	S626_SET_STD_ENCMODE(~0)
#घोषणा S626_STDMSK_CLKPOL	S626_SET_STD_CLKPOL(~0)
#घोषणा S626_STDMSK_CLKMULT	S626_SET_STD_CLKMULT(~0)
#घोषणा S626_STDMSK_CLKENAB	S626_SET_STD_CLKENAB(~0)

/* Conकाष्ठा parts of standardized SETUP काष्ठाure: */
#घोषणा S626_SET_STD_INTSRC(x)	\
	S626_MAKE((x), S626_STDWID_INTSRC, S626_STDBIT_INTSRC)
#घोषणा S626_SET_STD_LATCHSRC(x)	\
	S626_MAKE((x), S626_STDWID_LATCHSRC, S626_STDBIT_LATCHSRC)
#घोषणा S626_SET_STD_LOADSRC(x)	\
	S626_MAKE((x), S626_STDWID_LOADSRC, S626_STDBIT_LOADSRC)
#घोषणा S626_SET_STD_INDXSRC(x)	\
	S626_MAKE((x), S626_STDWID_INDXSRC, S626_STDBIT_INDXSRC)
#घोषणा S626_SET_STD_INDXPOL(x)	\
	S626_MAKE((x), S626_STDWID_INDXPOL, S626_STDBIT_INDXPOL)
#घोषणा S626_SET_STD_ENCMODE(x)	\
	S626_MAKE((x), S626_STDWID_ENCMODE, S626_STDBIT_ENCMODE)
#घोषणा S626_SET_STD_CLKPOL(x)	\
	S626_MAKE((x), S626_STDWID_CLKPOL, S626_STDBIT_CLKPOL)
#घोषणा S626_SET_STD_CLKMULT(x)	\
	S626_MAKE((x), S626_STDWID_CLKMULT, S626_STDBIT_CLKMULT)
#घोषणा S626_SET_STD_CLKENAB(x)	\
	S626_MAKE((x), S626_STDWID_CLKENAB, S626_STDBIT_CLKENAB)

/* Extract parts of standardized SETUP काष्ठाure: */
#घोषणा S626_GET_STD_INTSRC(v)	\
	S626_UNMAKE((v), S626_STDWID_INTSRC, S626_STDBIT_INTSRC)
#घोषणा S626_GET_STD_LATCHSRC(v)	\
	S626_UNMAKE((v), S626_STDWID_LATCHSRC, S626_STDBIT_LATCHSRC)
#घोषणा S626_GET_STD_LOADSRC(v)	\
	S626_UNMAKE((v), S626_STDWID_LOADSRC, S626_STDBIT_LOADSRC)
#घोषणा S626_GET_STD_INDXSRC(v)	\
	S626_UNMAKE((v), S626_STDWID_INDXSRC, S626_STDBIT_INDXSRC)
#घोषणा S626_GET_STD_INDXPOL(v)	\
	S626_UNMAKE((v), S626_STDWID_INDXPOL, S626_STDBIT_INDXPOL)
#घोषणा S626_GET_STD_ENCMODE(v)	\
	S626_UNMAKE((v), S626_STDWID_ENCMODE, S626_STDBIT_ENCMODE)
#घोषणा S626_GET_STD_CLKPOL(v)	\
	S626_UNMAKE((v), S626_STDWID_CLKPOL, S626_STDBIT_CLKPOL)
#घोषणा S626_GET_STD_CLKMULT(v)	\
	S626_UNMAKE((v), S626_STDWID_CLKMULT, S626_STDBIT_CLKMULT)
#घोषणा S626_GET_STD_CLKENAB(v)	\
	S626_UNMAKE((v), S626_STDWID_CLKENAB, S626_STDBIT_CLKENAB)

#पूर्ण_अगर
