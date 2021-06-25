<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * comedi/drivers/rtd520.c
 * Comedi driver क्रम Real Time Devices (RTD) PCI4520/DM7520
 *
 * COMEDI - Linux Control and Measurement Device Interface
 * Copyright (C) 2001 David A. Schleef <ds@schleef.org>
 */

/*
 * Driver: rtd520
 * Description: Real Time Devices PCI4520/DM7520
 * Devices: [Real Time Devices] DM7520HR-1 (DM7520), DM7520HR-8,
 *   PCI4520 (PCI4520), PCI4520-8
 * Author: Dan Christian
 * Status: Works. Only tested on DM7520-8. Not SMP safe.
 *
 * Configuration options: not applicable, uses PCI स्वतः config
 */

/*
 * Created by Dan Christian, NASA Ames Research Center.
 *
 * The PCI4520 is a PCI card. The DM7520 is a PC/104-plus card.
 * Both have:
 *   8/16 12 bit ADC with FIFO and channel gain table
 *   8 bits high speed digital out (क्रम बाह्यal MUX) (or 8 in or 8 out)
 *   8 bits high speed digital in with FIFO and पूर्णांकerrupt on change (or 8 IO)
 *   2 12 bit DACs with FIFOs
 *   2 bits output
 *   2 bits input
 *   bus mastering DMA
 *   समयrs: ADC sample, pacer, burst, about, delay, DA1, DA2
 *   sample counter
 *   3 user समयr/counters (8254)
 *   बाह्यal पूर्णांकerrupt
 *
 * The DM7520 has slightly fewer features (fewer gain steps).
 *
 * These boards can support बाह्यal multiplexors and multi-board
 * synchronization, but this driver करोesn't support that.
 *
 * Board करोcs: http://www.rtdusa.com/PC104/DM/analog%20IO/dm7520.hपंचांग
 * Data sheet: http://www.rtdusa.com/pdf/dm7520.pdf
 * Example source: http://www.rtdusa.com/examples/dm/dm7520.zip
 * Call them and ask क्रम the रेजिस्टर level manual.
 * PCI chip: http://www.plxtech.com/products/io/pci9080
 *
 * Notes:
 * This board is memory mapped. There is some IO stuff, but it isn't needed.
 *
 * I use a pretty loose naming style within the driver (rtd_blah).
 * All बाह्यally visible names should be rtd520_blah.
 * I use camelCase क्रम काष्ठाures (and inside them).
 * I may also use upper CamelCase क्रम function names (old habit).
 *
 * This board is somewhat related to the RTD PCI4400 board.
 *
 * I borrowed heavily from the ni_mio_common, ni_aपंचांगio16d, mite, and
 * das1800, since they have the best करोcumented code. Driver cb_pcidas64.c
 * uses the same DMA controller.
 *
 * As far as I can tell, the About पूर्णांकerrupt करोesn't work अगर Sample is
 * also enabled. It turns out that About really isn't needed, since
 * we always count करोwn samples पढ़ो.
 */

/*
 * driver status:
 *
 * Analog-In supports inकाष्ठाion and command mode.
 *
 * With DMA, you can sample at 1.15Mhz with 70% idle on a 400Mhz K6-2
 * (single channel, 64K पढ़ो buffer). I get अक्रमom प्रणाली lockups when
 * using DMA with ALI-15xx based प्रणालीs. I haven't been able to test
 * any other chipsets. The lockups happen soon after the start of an
 * acquistion, not in the middle of a दीर्घ run.
 *
 * Without DMA, you can करो 620Khz sampling with 20% idle on a 400Mhz K6-2
 * (with a 256K पढ़ो buffer).
 *
 * Digital-IO and Analog-Out only support inकाष्ठाion mode.
 */

#समावेश <linux/module.h>
#समावेश <linux/delay.h>
#समावेश <linux/पूर्णांकerrupt.h>

#समावेश "../comedi_pci.h"

#समावेश "comedi_8254.h"
#समावेश "plx9080.h"

/*
 * Local Address Space 0 Offsets
 */
#घोषणा LAS0_USER_IO		0x0008	/* User I/O */
#घोषणा LAS0_ADC		0x0010	/* FIFO Status/Software A/D Start */
#घोषणा FS_DAC1_NOT_EMPTY	BIT(0)	/* DAC1 FIFO not empty */
#घोषणा FS_DAC1_HEMPTY		BIT(1)	/* DAC1 FIFO half empty */
#घोषणा FS_DAC1_NOT_FULL	BIT(2)	/* DAC1 FIFO not full */
#घोषणा FS_DAC2_NOT_EMPTY	BIT(4)	/* DAC2 FIFO not empty */
#घोषणा FS_DAC2_HEMPTY		BIT(5)	/* DAC2 FIFO half empty */
#घोषणा FS_DAC2_NOT_FULL	BIT(6)	/* DAC2 FIFO not full */
#घोषणा FS_ADC_NOT_EMPTY	BIT(8)	/* ADC FIFO not empty */
#घोषणा FS_ADC_HEMPTY		BIT(9)	/* ADC FIFO half empty */
#घोषणा FS_ADC_NOT_FULL		BIT(10)	/* ADC FIFO not full */
#घोषणा FS_DIN_NOT_EMPTY	BIT(12)	/* DIN FIFO not empty */
#घोषणा FS_DIN_HEMPTY		BIT(13)	/* DIN FIFO half empty */
#घोषणा FS_DIN_NOT_FULL		BIT(14)	/* DIN FIFO not full */
#घोषणा LAS0_UPDATE_DAC(x)	(0x0014 + ((x) * 0x4))	/* D/Ax Update (w) */
#घोषणा LAS0_DAC		0x0024	/* Software Simultaneous Update (w) */
#घोषणा LAS0_PACER		0x0028	/* Software Pacer Start/Stop */
#घोषणा LAS0_TIMER		0x002c	/* Timer Status/HDIN Software Trig. */
#घोषणा LAS0_IT			0x0030	/* Interrupt Status/Enable */
#घोषणा IRQM_ADC_FIFO_WRITE	BIT(0)	/* ADC FIFO Write */
#घोषणा IRQM_CGT_RESET		BIT(1)	/* Reset CGT */
#घोषणा IRQM_CGT_PAUSE		BIT(3)	/* Pause CGT */
#घोषणा IRQM_ADC_ABOUT_CNT	BIT(4)	/* About Counter out */
#घोषणा IRQM_ADC_DELAY_CNT	BIT(5)	/* Delay Counter out */
#घोषणा IRQM_ADC_SAMPLE_CNT	BIT(6)	/* ADC Sample Counter */
#घोषणा IRQM_DAC1_UCNT		BIT(7)	/* DAC1 Update Counter */
#घोषणा IRQM_DAC2_UCNT		BIT(8)	/* DAC2 Update Counter */
#घोषणा IRQM_UTC1		BIT(9)	/* User TC1 out */
#घोषणा IRQM_UTC1_INV		BIT(10)	/* User TC1 out, inverted */
#घोषणा IRQM_UTC2		BIT(11)	/* User TC2 out */
#घोषणा IRQM_DIGITAL_IT		BIT(12)	/* Digital Interrupt */
#घोषणा IRQM_EXTERNAL_IT	BIT(13)	/* External Interrupt */
#घोषणा IRQM_ETRIG_RISING	BIT(14)	/* Ext Trigger rising-edge */
#घोषणा IRQM_ETRIG_FALLING	BIT(15)	/* Ext Trigger falling-edge */
#घोषणा LAS0_CLEAR		0x0034	/* Clear/Set Interrupt Clear Mask */
#घोषणा LAS0_OVERRUN		0x0038	/* Pending पूर्णांकerrupts/Clear Overrun */
#घोषणा LAS0_PCLK		0x0040	/* Pacer Clock (24bit) */
#घोषणा LAS0_BCLK		0x0044	/* Burst Clock (10bit) */
#घोषणा LAS0_ADC_SCNT		0x0048	/* A/D Sample counter (10bit) */
#घोषणा LAS0_DAC1_UCNT		0x004c	/* D/A1 Update counter (10 bit) */
#घोषणा LAS0_DAC2_UCNT		0x0050	/* D/A2 Update counter (10 bit) */
#घोषणा LAS0_DCNT		0x0054	/* Delay counter (16 bit) */
#घोषणा LAS0_ACNT		0x0058	/* About counter (16 bit) */
#घोषणा LAS0_DAC_CLK		0x005c	/* DAC घड़ी (16bit) */
#घोषणा LAS0_8254_TIMER_BASE	0x0060	/* 8254 समयr/counter base */
#घोषणा LAS0_DIO0		0x0070	/* Digital I/O Port 0 */
#घोषणा LAS0_DIO1		0x0074	/* Digital I/O Port 1 */
#घोषणा LAS0_DIO0_CTRL		0x0078	/* Digital I/O Control */
#घोषणा LAS0_DIO_STATUS		0x007c	/* Digital I/O Status */
#घोषणा LAS0_BOARD_RESET	0x0100	/* Board reset */
#घोषणा LAS0_DMA0_SRC		0x0104	/* DMA 0 Sources select */
#घोषणा LAS0_DMA1_SRC		0x0108	/* DMA 1 Sources select */
#घोषणा LAS0_ADC_CONVERSION	0x010c	/* A/D Conversion Signal select */
#घोषणा LAS0_BURST_START	0x0110	/* Burst Clock Start Trigger select */
#घोषणा LAS0_PACER_START	0x0114	/* Pacer Clock Start Trigger select */
#घोषणा LAS0_PACER_STOP		0x0118	/* Pacer Clock Stop Trigger select */
#घोषणा LAS0_ACNT_STOP_ENABLE	0x011c	/* About Counter Stop Enable */
#घोषणा LAS0_PACER_REPEAT	0x0120	/* Pacer Start Trigger Mode select */
#घोषणा LAS0_DIN_START		0x0124	/* HiSpd DI Sampling Signal select */
#घोषणा LAS0_DIN_FIFO_CLEAR	0x0128	/* Digital Input FIFO Clear */
#घोषणा LAS0_ADC_FIFO_CLEAR	0x012c	/* A/D FIFO Clear */
#घोषणा LAS0_CGT_WRITE		0x0130	/* Channel Gain Table Write */
#घोषणा LAS0_CGL_WRITE		0x0134	/* Channel Gain Latch Write */
#घोषणा LAS0_CG_DATA		0x0138	/* Digital Table Write */
#घोषणा LAS0_CGT_ENABLE		0x013c	/* Channel Gain Table Enable */
#घोषणा LAS0_CG_ENABLE		0x0140	/* Digital Table Enable */
#घोषणा LAS0_CGT_PAUSE		0x0144	/* Table Pause Enable */
#घोषणा LAS0_CGT_RESET		0x0148	/* Reset Channel Gain Table */
#घोषणा LAS0_CGT_CLEAR		0x014c	/* Clear Channel Gain Table */
#घोषणा LAS0_DAC_CTRL(x)	(0x0150	+ ((x) * 0x14))	/* D/Ax type/range */
#घोषणा LAS0_DAC_SRC(x)		(0x0154 + ((x) * 0x14))	/* D/Ax update source */
#घोषणा LAS0_DAC_CYCLE(x)	(0x0158 + ((x) * 0x14))	/* D/Ax cycle mode */
#घोषणा LAS0_DAC_RESET(x)	(0x015c + ((x) * 0x14))	/* D/Ax FIFO reset */
#घोषणा LAS0_DAC_FIFO_CLEAR(x)	(0x0160 + ((x) * 0x14))	/* D/Ax FIFO clear */
#घोषणा LAS0_ADC_SCNT_SRC	0x0178	/* A/D Sample Counter Source select */
#घोषणा LAS0_PACER_SELECT	0x0180	/* Pacer Clock select */
#घोषणा LAS0_SBUS0_SRC		0x0184	/* SyncBus 0 Source select */
#घोषणा LAS0_SBUS0_ENABLE	0x0188	/* SyncBus 0 enable */
#घोषणा LAS0_SBUS1_SRC		0x018c	/* SyncBus 1 Source select */
#घोषणा LAS0_SBUS1_ENABLE	0x0190	/* SyncBus 1 enable */
#घोषणा LAS0_SBUS2_SRC		0x0198	/* SyncBus 2 Source select */
#घोषणा LAS0_SBUS2_ENABLE	0x019c	/* SyncBus 2 enable */
#घोषणा LAS0_ETRG_POLARITY	0x01a4	/* Ext. Trigger polarity select */
#घोषणा LAS0_EINT_POLARITY	0x01a8	/* Ext. Interrupt polarity select */
#घोषणा LAS0_8254_CLK_SEL(x)	(0x01ac + ((x) * 0x8))	/* 8254 घड़ी select */
#घोषणा LAS0_8254_GATE_SEL(x)	(0x01b0 + ((x) * 0x8))	/* 8254 gate select */
#घोषणा LAS0_UOUT0_SELECT	0x01c4	/* User Output 0 source select */
#घोषणा LAS0_UOUT1_SELECT	0x01c8	/* User Output 1 source select */
#घोषणा LAS0_DMA0_RESET		0x01cc	/* DMA0 Request state machine reset */
#घोषणा LAS0_DMA1_RESET		0x01d0	/* DMA1 Request state machine reset */

/*
 * Local Address Space 1 Offsets
 */
#घोषणा LAS1_ADC_FIFO		0x0000	/* A/D FIFO (16bit) */
#घोषणा LAS1_HDIO_FIFO		0x0004	/* HiSpd DI FIFO (16bit) */
#घोषणा LAS1_DAC_FIFO(x)	(0x0008 + ((x) * 0x4))	/* D/Ax FIFO (16bit) */

/*
 * Driver specअगरic stuff (tunable)
 */

/*
 * We really only need 2 buffers.  More than that means being much
 * smarter about knowing which ones are full.
 */
#घोषणा DMA_CHAIN_COUNT 2	/* max DMA segments/buffers in a ring (min 2) */

/* Target period क्रम periodic transfers.  This sets the user पढ़ो latency. */
/* Note: There are certain rates where we give this up and transfer 1/2 FIFO */
/* If this is too low, efficiency is poor */
#घोषणा TRANS_TARGET_PERIOD 10000000	/* 10 ms (in nanoseconds) */

/* Set a practical limit on how दीर्घ a list to support (affects memory use) */
/* The board support a channel list up to the FIFO length (1K or 8K) */
#घोषणा RTD_MAX_CHANLIST	128	/* max channel list that we allow */

/*
 * Board specअगरic stuff
 */

#घोषणा RTD_CLOCK_RATE	8000000	/* 8Mhz onboard घड़ी */
#घोषणा RTD_CLOCK_BASE	125	/* घड़ी period in ns */

/* Note: these speed are slower than the spec, but fit the counter resolution*/
#घोषणा RTD_MAX_SPEED	1625	/* when sampling, in nanoseconds */
/* max speed अगर we करोn't have to रुको क्रम settling */
#घोषणा RTD_MAX_SPEED_1	875	/* अगर single channel, in nanoseconds */

#घोषणा RTD_MIN_SPEED	2097151875	/* (24bit counter) in nanoseconds */
/* min speed when only 1 channel (no burst counter) */
#घोषणा RTD_MIN_SPEED_1	5000000	/* 200Hz, in nanoseconds */

/* Setup continuous ring of 1/2 FIFO transfers.  See RTD manual p91 */
#घोषणा DMA_MODE_BITS (\
		       PLX_LOCAL_BUS_16_WIDE_BITS \
		       | PLX_DMA_EN_READYIN_BIT \
		       | PLX_DMA_LOCAL_BURST_EN_BIT \
		       | PLX_EN_CHAIN_BIT \
		       | PLX_DMA_INTR_PCI_BIT \
		       | PLX_LOCAL_ADDR_CONST_BIT \
		       | PLX_DEMAND_MODE_BIT)

#घोषणा DMA_TRANSFER_BITS (\
/* descriptors in PCI memory*/  PLX_DESC_IN_PCI_BIT \
/* पूर्णांकerrupt at end of block */ | PLX_INTR_TERM_COUNT \
/* from board to PCI */		| PLX_XFER_LOCAL_TO_PCI)

/*
 * Comedi specअगरic stuff
 */

/*
 * The board has 3 input modes and the gains of 1,2,4,...32 (, 64, 128)
 */
अटल स्थिर काष्ठा comedi_lrange rtd_ai_7520_range = अणु
	18, अणु
		/* +-5V input range gain steps */
		BIP_RANGE(5.0),
		BIP_RANGE(5.0 / 2),
		BIP_RANGE(5.0 / 4),
		BIP_RANGE(5.0 / 8),
		BIP_RANGE(5.0 / 16),
		BIP_RANGE(5.0 / 32),
		/* +-10V input range gain steps */
		BIP_RANGE(10.0),
		BIP_RANGE(10.0 / 2),
		BIP_RANGE(10.0 / 4),
		BIP_RANGE(10.0 / 8),
		BIP_RANGE(10.0 / 16),
		BIP_RANGE(10.0 / 32),
		/* +10V input range gain steps */
		UNI_RANGE(10.0),
		UNI_RANGE(10.0 / 2),
		UNI_RANGE(10.0 / 4),
		UNI_RANGE(10.0 / 8),
		UNI_RANGE(10.0 / 16),
		UNI_RANGE(10.0 / 32),
	पूर्ण
पूर्ण;

/* PCI4520 has two more gains (6 more entries) */
अटल स्थिर काष्ठा comedi_lrange rtd_ai_4520_range = अणु
	24, अणु
		/* +-5V input range gain steps */
		BIP_RANGE(5.0),
		BIP_RANGE(5.0 / 2),
		BIP_RANGE(5.0 / 4),
		BIP_RANGE(5.0 / 8),
		BIP_RANGE(5.0 / 16),
		BIP_RANGE(5.0 / 32),
		BIP_RANGE(5.0 / 64),
		BIP_RANGE(5.0 / 128),
		/* +-10V input range gain steps */
		BIP_RANGE(10.0),
		BIP_RANGE(10.0 / 2),
		BIP_RANGE(10.0 / 4),
		BIP_RANGE(10.0 / 8),
		BIP_RANGE(10.0 / 16),
		BIP_RANGE(10.0 / 32),
		BIP_RANGE(10.0 / 64),
		BIP_RANGE(10.0 / 128),
		/* +10V input range gain steps */
		UNI_RANGE(10.0),
		UNI_RANGE(10.0 / 2),
		UNI_RANGE(10.0 / 4),
		UNI_RANGE(10.0 / 8),
		UNI_RANGE(10.0 / 16),
		UNI_RANGE(10.0 / 32),
		UNI_RANGE(10.0 / 64),
		UNI_RANGE(10.0 / 128),
	पूर्ण
पूर्ण;

/* Table order matches range values */
अटल स्थिर काष्ठा comedi_lrange rtd_ao_range = अणु
	4, अणु
		UNI_RANGE(5),
		UNI_RANGE(10),
		BIP_RANGE(5),
		BIP_RANGE(10),
	पूर्ण
पूर्ण;

क्रमागत rtd_boardid अणु
	BOARD_DM7520,
	BOARD_PCI4520,
पूर्ण;

काष्ठा rtd_boardinfo अणु
	स्थिर अक्षर *name;
	पूर्णांक range_bip10;	/* start of +-10V range */
	पूर्णांक range_uni10;	/* start of +10V range */
	स्थिर काष्ठा comedi_lrange *ai_range;
पूर्ण;

अटल स्थिर काष्ठा rtd_boardinfo rtd520_boards[] = अणु
	[BOARD_DM7520] = अणु
		.name		= "DM7520",
		.range_bip10	= 6,
		.range_uni10	= 12,
		.ai_range	= &rtd_ai_7520_range,
	पूर्ण,
	[BOARD_PCI4520] = अणु
		.name		= "PCI4520",
		.range_bip10	= 8,
		.range_uni10	= 16,
		.ai_range	= &rtd_ai_4520_range,
	पूर्ण,
पूर्ण;

काष्ठा rtd_निजी अणु
	/* memory mapped board काष्ठाures */
	व्योम __iomem *las1;
	व्योम __iomem *lcfg;

	दीर्घ ai_count;		/* total transfer size (samples) */
	पूर्णांक xfer_count;		/* # to transfer data. 0->1/2FIFO */
	पूर्णांक flags;		/* flag event modes */
	अचिन्हित पूर्णांक fअगरosz;

	/* 8254 Timer/Counter gate and घड़ी sources */
	अचिन्हित अक्षर समयr_gate_src[3];
	अचिन्हित अक्षर समयr_clk_src[3];
पूर्ण;

/* bit defines क्रम "flags" */
#घोषणा SEND_EOS	0x01	/* send End Of Scan events */
#घोषणा DMA0_ACTIVE	0x02	/* DMA0 is active */
#घोषणा DMA1_ACTIVE	0x04	/* DMA1 is active */

/*
 * Given a desired period and the घड़ी period (both in ns), वापस the
 * proper counter value (भागider-1). Sets the original period to be the
 * true value.
 * Note: you have to check अगर the value is larger than the counter range!
 */
अटल पूर्णांक rtd_ns_to_समयr_base(अचिन्हित पूर्णांक *nanosec,
				अचिन्हित पूर्णांक flags, पूर्णांक base)
अणु
	पूर्णांक भागider;

	चयन (flags & CMDF_ROUND_MASK) अणु
	हाल CMDF_ROUND_NEAREST:
	शेष:
		भागider = DIV_ROUND_CLOSEST(*nanosec, base);
		अवरोध;
	हाल CMDF_ROUND_DOWN:
		भागider = (*nanosec) / base;
		अवरोध;
	हाल CMDF_ROUND_UP:
		भागider = DIV_ROUND_UP(*nanosec, base);
		अवरोध;
	पूर्ण
	अगर (भागider < 2)
		भागider = 2;	/* min is भागide by 2 */

	/*
	 * Note: we करोn't check क्रम max, because dअगरferent समयrs
	 * have dअगरferent ranges
	 */

	*nanosec = base * भागider;
	वापस भागider - 1;	/* countकरोwn is भागisor+1 */
पूर्ण

/*
 * Given a desired period (in ns), वापस the proper counter value
 * (भागider-1) क्रम the पूर्णांकernal घड़ी. Sets the original period to
 * be the true value.
 */
अटल पूर्णांक rtd_ns_to_समयr(अचिन्हित पूर्णांक *ns, अचिन्हित पूर्णांक flags)
अणु
	वापस rtd_ns_to_समयr_base(ns, flags, RTD_CLOCK_BASE);
पूर्ण

/* Convert a single comedi channel-gain entry to a RTD520 table entry */
अटल अचिन्हित लघु rtd_convert_chan_gain(काष्ठा comedi_device *dev,
					    अचिन्हित पूर्णांक chanspec, पूर्णांक index)
अणु
	स्थिर काष्ठा rtd_boardinfo *board = dev->board_ptr;
	अचिन्हित पूर्णांक chan = CR_CHAN(chanspec);
	अचिन्हित पूर्णांक range = CR_RANGE(chanspec);
	अचिन्हित पूर्णांक aref = CR_AREF(chanspec);
	अचिन्हित लघु r = 0;

	r |= chan & 0xf;

	/* Note: we also setup the channel list bipolar flag array */
	अगर (range < board->range_bip10) अणु
		/* +-5 range */
		r |= 0x000;
		r |= (range & 0x7) << 4;
	पूर्ण अन्यथा अगर (range < board->range_uni10) अणु
		/* +-10 range */
		r |= 0x100;
		r |= ((range - board->range_bip10) & 0x7) << 4;
	पूर्ण अन्यथा अणु
		/* +10 range */
		r |= 0x200;
		r |= ((range - board->range_uni10) & 0x7) << 4;
	पूर्ण

	चयन (aref) अणु
	हाल AREF_GROUND:	/* on-board ground */
		अवरोध;

	हाल AREF_COMMON:
		r |= 0x80;	/* ref बाह्यal analog common */
		अवरोध;

	हाल AREF_DIFF:
		r |= 0x400;	/* dअगरferential inमाला_दो */
		अवरोध;

	हाल AREF_OTHER:	/* ??? */
		अवरोध;
	पूर्ण
	वापस r;
पूर्ण

/* Setup the channel-gain table from a comedi list */
अटल व्योम rtd_load_channelgain_list(काष्ठा comedi_device *dev,
				      अचिन्हित पूर्णांक n_chan, अचिन्हित पूर्णांक *list)
अणु
	अगर (n_chan > 1) अणु	/* setup channel gain table */
		पूर्णांक ii;

		ग_लिखोl(0, dev->mmio + LAS0_CGT_CLEAR);
		ग_लिखोl(1, dev->mmio + LAS0_CGT_ENABLE);
		क्रम (ii = 0; ii < n_chan; ii++) अणु
			ग_लिखोl(rtd_convert_chan_gain(dev, list[ii], ii),
			       dev->mmio + LAS0_CGT_WRITE);
		पूर्ण
	पूर्ण अन्यथा अणु		/* just use the channel gain latch */
		ग_लिखोl(0, dev->mmio + LAS0_CGT_ENABLE);
		ग_लिखोl(rtd_convert_chan_gain(dev, list[0], 0),
		       dev->mmio + LAS0_CGL_WRITE);
	पूर्ण
पूर्ण

/*
 * Determine fअगरo size by करोing adc conversions until the fअगरo half
 * empty status flag clears.
 */
अटल पूर्णांक rtd520_probe_fअगरo_depth(काष्ठा comedi_device *dev)
अणु
	अचिन्हित पूर्णांक chanspec = CR_PACK(0, 0, AREF_GROUND);
	अचिन्हित पूर्णांक i;
	अटल स्थिर अचिन्हित पूर्णांक limit = 0x2000;
	अचिन्हित पूर्णांक fअगरo_size = 0;

	ग_लिखोl(0, dev->mmio + LAS0_ADC_FIFO_CLEAR);
	rtd_load_channelgain_list(dev, 1, &chanspec);
	/* ADC conversion trigger source: SOFTWARE */
	ग_लिखोl(0, dev->mmio + LAS0_ADC_CONVERSION);
	/* convert  samples */
	क्रम (i = 0; i < limit; ++i) अणु
		अचिन्हित पूर्णांक fअगरo_status;
		/* trigger conversion */
		ग_लिखोw(0, dev->mmio + LAS0_ADC);
		usleep_range(1, 1000);
		fअगरo_status = पढ़ोl(dev->mmio + LAS0_ADC);
		अगर ((fअगरo_status & FS_ADC_HEMPTY) == 0) अणु
			fअगरo_size = 2 * i;
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (i == limit) अणु
		dev_info(dev->class_dev, "failed to probe fifo size.\n");
		वापस -EIO;
	पूर्ण
	ग_लिखोl(0, dev->mmio + LAS0_ADC_FIFO_CLEAR);
	अगर (fअगरo_size != 0x400 && fअगरo_size != 0x2000) अणु
		dev_info(dev->class_dev,
			 "unexpected fifo size of %i, expected 1024 or 8192.\n",
			 fअगरo_size);
		वापस -EIO;
	पूर्ण
	वापस fअगरo_size;
पूर्ण

अटल पूर्णांक rtd_ai_eoc(काष्ठा comedi_device *dev,
		      काष्ठा comedi_subdevice *s,
		      काष्ठा comedi_insn *insn,
		      अचिन्हित दीर्घ context)
अणु
	अचिन्हित पूर्णांक status;

	status = पढ़ोl(dev->mmio + LAS0_ADC);
	अगर (status & FS_ADC_NOT_EMPTY)
		वापस 0;
	वापस -EBUSY;
पूर्ण

अटल पूर्णांक rtd_ai_rinsn(काष्ठा comedi_device *dev,
			काष्ठा comedi_subdevice *s, काष्ठा comedi_insn *insn,
			अचिन्हित पूर्णांक *data)
अणु
	काष्ठा rtd_निजी *devpriv = dev->निजी;
	अचिन्हित पूर्णांक range = CR_RANGE(insn->chanspec);
	पूर्णांक ret;
	पूर्णांक n;

	/* clear any old fअगरo data */
	ग_लिखोl(0, dev->mmio + LAS0_ADC_FIFO_CLEAR);

	/* ग_लिखो channel to multiplexer and clear channel gain table */
	rtd_load_channelgain_list(dev, 1, &insn->chanspec);

	/* ADC conversion trigger source: SOFTWARE */
	ग_लिखोl(0, dev->mmio + LAS0_ADC_CONVERSION);

	/* convert n samples */
	क्रम (n = 0; n < insn->n; n++) अणु
		अचिन्हित लघु d;
		/* trigger conversion */
		ग_लिखोw(0, dev->mmio + LAS0_ADC);

		ret = comedi_समयout(dev, s, insn, rtd_ai_eoc, 0);
		अगर (ret)
			वापस ret;

		/* पढ़ो data */
		d = पढ़ोw(devpriv->las1 + LAS1_ADC_FIFO);
		d >>= 3;	/* low 3 bits are marker lines */

		/* convert bipolar data to comedi अचिन्हित data */
		अगर (comedi_range_is_bipolar(s, range))
			d = comedi_offset_munge(s, d);

		data[n] = d & s->maxdata;
	पूर्ण

	/* वापस the number of samples पढ़ो/written */
	वापस n;
पूर्ण

अटल पूर्णांक ai_पढ़ो_n(काष्ठा comedi_device *dev, काष्ठा comedi_subdevice *s,
		     पूर्णांक count)
अणु
	काष्ठा rtd_निजी *devpriv = dev->निजी;
	काष्ठा comedi_async *async = s->async;
	काष्ठा comedi_cmd *cmd = &async->cmd;
	पूर्णांक ii;

	क्रम (ii = 0; ii < count; ii++) अणु
		अचिन्हित पूर्णांक range = CR_RANGE(cmd->chanlist[async->cur_chan]);
		अचिन्हित लघु d;

		अगर (devpriv->ai_count == 0) अणु	/* करोne */
			d = पढ़ोw(devpriv->las1 + LAS1_ADC_FIFO);
			जारी;
		पूर्ण

		d = पढ़ोw(devpriv->las1 + LAS1_ADC_FIFO);
		d >>= 3;	/* low 3 bits are marker lines */

		/* convert bipolar data to comedi अचिन्हित data */
		अगर (comedi_range_is_bipolar(s, range))
			d = comedi_offset_munge(s, d);
		d &= s->maxdata;

		अगर (!comedi_buf_ग_लिखो_samples(s, &d, 1))
			वापस -1;

		अगर (devpriv->ai_count > 0)	/* < 0, means पढ़ो क्रमever */
			devpriv->ai_count--;
	पूर्ण
	वापस 0;
पूर्ण

अटल irqवापस_t rtd_पूर्णांकerrupt(पूर्णांक irq, व्योम *d)
अणु
	काष्ठा comedi_device *dev = d;
	काष्ठा comedi_subdevice *s = dev->पढ़ो_subdev;
	काष्ठा rtd_निजी *devpriv = dev->निजी;
	u32 overrun;
	u16 status;
	u16 fअगरo_status;

	अगर (!dev->attached)
		वापस IRQ_NONE;

	fअगरo_status = पढ़ोl(dev->mmio + LAS0_ADC);
	/* check क्रम FIFO full, this स्वतःmatically halts the ADC! */
	अगर (!(fअगरo_status & FS_ADC_NOT_FULL))	/* 0 -> full */
		जाओ xfer_पात;

	status = पढ़ोw(dev->mmio + LAS0_IT);
	/* अगर पूर्णांकerrupt was not caused by our board, or handled above */
	अगर (status == 0)
		वापस IRQ_HANDLED;

	अगर (status & IRQM_ADC_ABOUT_CNT) अणु	/* sample count -> पढ़ो FIFO */
		/*
		 * since the priority पूर्णांकerrupt controller may have queued
		 * a sample counter पूर्णांकerrupt, even though we have alपढ़ोy
		 * finished, we must handle the possibility that there is
		 * no data here
		 */
		अगर (!(fअगरo_status & FS_ADC_HEMPTY)) अणु
			/* FIFO half full */
			अगर (ai_पढ़ो_n(dev, s, devpriv->fअगरosz / 2) < 0)
				जाओ xfer_पात;

			अगर (devpriv->ai_count == 0)
				जाओ xfer_करोne;
		पूर्ण अन्यथा अगर (devpriv->xfer_count > 0) अणु
			अगर (fअगरo_status & FS_ADC_NOT_EMPTY) अणु
				/* FIFO not empty */
				अगर (ai_पढ़ो_n(dev, s, devpriv->xfer_count) < 0)
					जाओ xfer_पात;

				अगर (devpriv->ai_count == 0)
					जाओ xfer_करोne;
			पूर्ण
		पूर्ण
	पूर्ण

	overrun = पढ़ोl(dev->mmio + LAS0_OVERRUN) & 0xffff;
	अगर (overrun)
		जाओ xfer_पात;

	/* clear the पूर्णांकerrupt */
	ग_लिखोw(status, dev->mmio + LAS0_CLEAR);
	पढ़ोw(dev->mmio + LAS0_CLEAR);

	comedi_handle_events(dev, s);

	वापस IRQ_HANDLED;

xfer_पात:
	s->async->events |= COMEDI_CB_ERROR;

xfer_करोne:
	s->async->events |= COMEDI_CB_EOA;

	/* clear the पूर्णांकerrupt */
	status = पढ़ोw(dev->mmio + LAS0_IT);
	ग_लिखोw(status, dev->mmio + LAS0_CLEAR);
	पढ़ोw(dev->mmio + LAS0_CLEAR);

	fअगरo_status = पढ़ोl(dev->mmio + LAS0_ADC);
	overrun = पढ़ोl(dev->mmio + LAS0_OVERRUN) & 0xffff;

	comedi_handle_events(dev, s);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक rtd_ai_cmdtest(काष्ठा comedi_device *dev,
			  काष्ठा comedi_subdevice *s, काष्ठा comedi_cmd *cmd)
अणु
	पूर्णांक err = 0;
	अचिन्हित पूर्णांक arg;

	/* Step 1 : check अगर triggers are trivially valid */

	err |= comedi_check_trigger_src(&cmd->start_src, TRIG_NOW);
	err |= comedi_check_trigger_src(&cmd->scan_begin_src,
					TRIG_TIMER | TRIG_EXT);
	err |= comedi_check_trigger_src(&cmd->convert_src,
					TRIG_TIMER | TRIG_EXT);
	err |= comedi_check_trigger_src(&cmd->scan_end_src, TRIG_COUNT);
	err |= comedi_check_trigger_src(&cmd->stop_src, TRIG_COUNT | TRIG_NONE);

	अगर (err)
		वापस 1;

	/* Step 2a : make sure trigger sources are unique */

	err |= comedi_check_trigger_is_unique(cmd->scan_begin_src);
	err |= comedi_check_trigger_is_unique(cmd->convert_src);
	err |= comedi_check_trigger_is_unique(cmd->stop_src);

	/* Step 2b : and mutually compatible */

	अगर (err)
		वापस 2;

	/* Step 3: check अगर arguments are trivially valid */

	err |= comedi_check_trigger_arg_is(&cmd->start_arg, 0);

	अगर (cmd->scan_begin_src == TRIG_TIMER) अणु
		/* Note: these are समय periods, not actual rates */
		अगर (cmd->chanlist_len == 1) अणु	/* no scanning */
			अगर (comedi_check_trigger_arg_min(&cmd->scan_begin_arg,
							 RTD_MAX_SPEED_1)) अणु
				rtd_ns_to_समयr(&cmd->scan_begin_arg,
						CMDF_ROUND_UP);
				err |= -EINVAL;
			पूर्ण
			अगर (comedi_check_trigger_arg_max(&cmd->scan_begin_arg,
							 RTD_MIN_SPEED_1)) अणु
				rtd_ns_to_समयr(&cmd->scan_begin_arg,
						CMDF_ROUND_DOWN);
				err |= -EINVAL;
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (comedi_check_trigger_arg_min(&cmd->scan_begin_arg,
							 RTD_MAX_SPEED)) अणु
				rtd_ns_to_समयr(&cmd->scan_begin_arg,
						CMDF_ROUND_UP);
				err |= -EINVAL;
			पूर्ण
			अगर (comedi_check_trigger_arg_max(&cmd->scan_begin_arg,
							 RTD_MIN_SPEED)) अणु
				rtd_ns_to_समयr(&cmd->scan_begin_arg,
						CMDF_ROUND_DOWN);
				err |= -EINVAL;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		/* बाह्यal trigger */
		/* should be level/edge, hi/lo specअगरication here */
		/* should specअगरy multiple बाह्यal triggers */
		err |= comedi_check_trigger_arg_max(&cmd->scan_begin_arg, 9);
	पूर्ण

	अगर (cmd->convert_src == TRIG_TIMER) अणु
		अगर (cmd->chanlist_len == 1) अणु	/* no scanning */
			अगर (comedi_check_trigger_arg_min(&cmd->convert_arg,
							 RTD_MAX_SPEED_1)) अणु
				rtd_ns_to_समयr(&cmd->convert_arg,
						CMDF_ROUND_UP);
				err |= -EINVAL;
			पूर्ण
			अगर (comedi_check_trigger_arg_max(&cmd->convert_arg,
							 RTD_MIN_SPEED_1)) अणु
				rtd_ns_to_समयr(&cmd->convert_arg,
						CMDF_ROUND_DOWN);
				err |= -EINVAL;
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (comedi_check_trigger_arg_min(&cmd->convert_arg,
							 RTD_MAX_SPEED)) अणु
				rtd_ns_to_समयr(&cmd->convert_arg,
						CMDF_ROUND_UP);
				err |= -EINVAL;
			पूर्ण
			अगर (comedi_check_trigger_arg_max(&cmd->convert_arg,
							 RTD_MIN_SPEED)) अणु
				rtd_ns_to_समयr(&cmd->convert_arg,
						CMDF_ROUND_DOWN);
				err |= -EINVAL;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		/* बाह्यal trigger */
		/* see above */
		err |= comedi_check_trigger_arg_max(&cmd->convert_arg, 9);
	पूर्ण

	err |= comedi_check_trigger_arg_is(&cmd->scan_end_arg,
					   cmd->chanlist_len);

	अगर (cmd->stop_src == TRIG_COUNT)
		err |= comedi_check_trigger_arg_min(&cmd->stop_arg, 1);
	अन्यथा	/* TRIG_NONE */
		err |= comedi_check_trigger_arg_is(&cmd->stop_arg, 0);

	अगर (err)
		वापस 3;

	/* step 4: fix up any arguments */

	अगर (cmd->scan_begin_src == TRIG_TIMER) अणु
		arg = cmd->scan_begin_arg;
		rtd_ns_to_समयr(&arg, cmd->flags);
		err |= comedi_check_trigger_arg_is(&cmd->scan_begin_arg, arg);
	पूर्ण

	अगर (cmd->convert_src == TRIG_TIMER) अणु
		arg = cmd->convert_arg;
		rtd_ns_to_समयr(&arg, cmd->flags);
		err |= comedi_check_trigger_arg_is(&cmd->convert_arg, arg);

		अगर (cmd->scan_begin_src == TRIG_TIMER) अणु
			arg = cmd->convert_arg * cmd->scan_end_arg;
			err |= comedi_check_trigger_arg_min(
					&cmd->scan_begin_arg, arg);
		पूर्ण
	पूर्ण

	अगर (err)
		वापस 4;

	वापस 0;
पूर्ण

अटल पूर्णांक rtd_ai_cmd(काष्ठा comedi_device *dev, काष्ठा comedi_subdevice *s)
अणु
	काष्ठा rtd_निजी *devpriv = dev->निजी;
	काष्ठा comedi_cmd *cmd = &s->async->cmd;
	पूर्णांक समयr;

	/* stop anything currently running */
	/* pacer stop source: SOFTWARE */
	ग_लिखोl(0, dev->mmio + LAS0_PACER_STOP);
	ग_लिखोl(0, dev->mmio + LAS0_PACER);	/* stop pacer */
	ग_लिखोl(0, dev->mmio + LAS0_ADC_CONVERSION);
	ग_लिखोw(0, dev->mmio + LAS0_IT);
	ग_लिखोl(0, dev->mmio + LAS0_ADC_FIFO_CLEAR);
	ग_लिखोl(0, dev->mmio + LAS0_OVERRUN);

	/* start configuration */
	/* load channel list and reset CGT */
	rtd_load_channelgain_list(dev, cmd->chanlist_len, cmd->chanlist);

	/* setup the common हाल and override अगर needed */
	अगर (cmd->chanlist_len > 1) अणु
		/* pacer start source: SOFTWARE */
		ग_लिखोl(0, dev->mmio + LAS0_PACER_START);
		/* burst trigger source: PACER */
		ग_लिखोl(1, dev->mmio + LAS0_BURST_START);
		/* ADC conversion trigger source: BURST */
		ग_लिखोl(2, dev->mmio + LAS0_ADC_CONVERSION);
	पूर्ण अन्यथा अणु		/* single channel */
		/* pacer start source: SOFTWARE */
		ग_लिखोl(0, dev->mmio + LAS0_PACER_START);
		/* ADC conversion trigger source: PACER */
		ग_लिखोl(1, dev->mmio + LAS0_ADC_CONVERSION);
	पूर्ण
	ग_लिखोl((devpriv->fअगरosz / 2 - 1) & 0xffff, dev->mmio + LAS0_ACNT);

	अगर (cmd->scan_begin_src == TRIG_TIMER) अणु
		/* scan_begin_arg is in nanoseconds */
		/* find out how many samples to रुको beक्रमe transferring */
		अगर (cmd->flags & CMDF_WAKE_EOS) अणु
			/*
			 * this may generate un-sustainable पूर्णांकerrupt rates
			 * the application is responsible क्रम करोing the
			 * right thing
			 */
			devpriv->xfer_count = cmd->chanlist_len;
			devpriv->flags |= SEND_EOS;
		पूर्ण अन्यथा अणु
			/* arrange to transfer data periodically */
			devpriv->xfer_count =
			    (TRANS_TARGET_PERIOD * cmd->chanlist_len) /
			    cmd->scan_begin_arg;
			अगर (devpriv->xfer_count < cmd->chanlist_len) अणु
				/* transfer after each scan (and aव्योम 0) */
				devpriv->xfer_count = cmd->chanlist_len;
			पूर्ण अन्यथा अणु	/* make a multiple of scan length */
				devpriv->xfer_count =
				    DIV_ROUND_UP(devpriv->xfer_count,
						 cmd->chanlist_len);
				devpriv->xfer_count *= cmd->chanlist_len;
			पूर्ण
			devpriv->flags |= SEND_EOS;
		पूर्ण
		अगर (devpriv->xfer_count >= (devpriv->fअगरosz / 2)) अणु
			/* out of counter range, use 1/2 fअगरo instead */
			devpriv->xfer_count = 0;
			devpriv->flags &= ~SEND_EOS;
		पूर्ण अन्यथा अणु
			/* पूर्णांकerrupt क्रम each transfer */
			ग_लिखोl((devpriv->xfer_count - 1) & 0xffff,
			       dev->mmio + LAS0_ACNT);
		पूर्ण
	पूर्ण अन्यथा अणु		/* unknown timing, just use 1/2 FIFO */
		devpriv->xfer_count = 0;
		devpriv->flags &= ~SEND_EOS;
	पूर्ण
	/* pacer घड़ी source: INTERNAL 8MHz */
	ग_लिखोl(1, dev->mmio + LAS0_PACER_SELECT);
	/* just पूर्णांकerrupt, करोn't stop */
	ग_लिखोl(1, dev->mmio + LAS0_ACNT_STOP_ENABLE);

	/* BUG??? these look like क्रमागतerated values, but they are bit fields */

	/* First, setup when to stop */
	चयन (cmd->stop_src) अणु
	हाल TRIG_COUNT:	/* stop after N scans */
		devpriv->ai_count = cmd->stop_arg * cmd->chanlist_len;
		अगर ((devpriv->xfer_count > 0) &&
		    (devpriv->xfer_count > devpriv->ai_count)) अणु
			devpriv->xfer_count = devpriv->ai_count;
		पूर्ण
		अवरोध;

	हाल TRIG_NONE:	/* stop when cancel is called */
		devpriv->ai_count = -1;	/* पढ़ो क्रमever */
		अवरोध;
	पूर्ण

	/* Scan timing */
	चयन (cmd->scan_begin_src) अणु
	हाल TRIG_TIMER:	/* periodic scanning */
		समयr = rtd_ns_to_समयr(&cmd->scan_begin_arg,
					CMDF_ROUND_NEAREST);
		/* set PACER घड़ी */
		ग_लिखोl(समयr & 0xffffff, dev->mmio + LAS0_PCLK);

		अवरोध;

	हाल TRIG_EXT:
		/* pacer start source: EXTERNAL */
		ग_लिखोl(1, dev->mmio + LAS0_PACER_START);
		अवरोध;
	पूर्ण

	/* Sample timing within a scan */
	चयन (cmd->convert_src) अणु
	हाल TRIG_TIMER:	/* periodic */
		अगर (cmd->chanlist_len > 1) अणु
			/* only needed क्रम multi-channel */
			समयr = rtd_ns_to_समयr(&cmd->convert_arg,
						CMDF_ROUND_NEAREST);
			/* setup BURST घड़ी */
			ग_लिखोl(समयr & 0x3ff, dev->mmio + LAS0_BCLK);
		पूर्ण

		अवरोध;

	हाल TRIG_EXT:		/* बाह्यal */
		/* burst trigger source: EXTERNAL */
		ग_लिखोl(2, dev->mmio + LAS0_BURST_START);
		अवरोध;
	पूर्ण
	/* end configuration */

	/*
	 * This करोesn't seem to work.  There is no way to clear an पूर्णांकerrupt
	 * that the priority controller has queued!
	 */
	ग_लिखोw(~0, dev->mmio + LAS0_CLEAR);
	पढ़ोw(dev->mmio + LAS0_CLEAR);

	/* TODO: allow multiple पूर्णांकerrupt sources */
	/* transfer every N samples */
	ग_लिखोw(IRQM_ADC_ABOUT_CNT, dev->mmio + LAS0_IT);

	/* BUG: start_src is ASSUMED to be TRIG_NOW */
	/* BUG? it seems like things are running beक्रमe the "start" */
	पढ़ोl(dev->mmio + LAS0_PACER);	/* start pacer */
	वापस 0;
पूर्ण

अटल पूर्णांक rtd_ai_cancel(काष्ठा comedi_device *dev, काष्ठा comedi_subdevice *s)
अणु
	काष्ठा rtd_निजी *devpriv = dev->निजी;

	/* pacer stop source: SOFTWARE */
	ग_लिखोl(0, dev->mmio + LAS0_PACER_STOP);
	ग_लिखोl(0, dev->mmio + LAS0_PACER);	/* stop pacer */
	ग_लिखोl(0, dev->mmio + LAS0_ADC_CONVERSION);
	ग_लिखोw(0, dev->mmio + LAS0_IT);
	devpriv->ai_count = 0;	/* stop and करोn't transfer any more */
	ग_लिखोl(0, dev->mmio + LAS0_ADC_FIFO_CLEAR);
	वापस 0;
पूर्ण

अटल पूर्णांक rtd_ao_eoc(काष्ठा comedi_device *dev,
		      काष्ठा comedi_subdevice *s,
		      काष्ठा comedi_insn *insn,
		      अचिन्हित दीर्घ context)
अणु
	अचिन्हित पूर्णांक chan = CR_CHAN(insn->chanspec);
	अचिन्हित पूर्णांक bit = (chan == 0) ? FS_DAC1_NOT_EMPTY : FS_DAC2_NOT_EMPTY;
	अचिन्हित पूर्णांक status;

	status = पढ़ोl(dev->mmio + LAS0_ADC);
	अगर (status & bit)
		वापस 0;
	वापस -EBUSY;
पूर्ण

अटल पूर्णांक rtd_ao_insn_ग_लिखो(काष्ठा comedi_device *dev,
			     काष्ठा comedi_subdevice *s,
			     काष्ठा comedi_insn *insn,
			     अचिन्हित पूर्णांक *data)
अणु
	काष्ठा rtd_निजी *devpriv = dev->निजी;
	अचिन्हित पूर्णांक chan = CR_CHAN(insn->chanspec);
	अचिन्हित पूर्णांक range = CR_RANGE(insn->chanspec);
	पूर्णांक ret;
	पूर्णांक i;

	/* Configure the output range (table index matches the range values) */
	ग_लिखोw(range & 7, dev->mmio + LAS0_DAC_CTRL(chan));

	क्रम (i = 0; i < insn->n; ++i) अणु
		अचिन्हित पूर्णांक val = data[i];

		/* bipolar uses 2's complement values with an extended sign */
		अगर (comedi_range_is_bipolar(s, range)) अणु
			val = comedi_offset_munge(s, val);
			val |= (val & ((s->maxdata + 1) >> 1)) << 1;
		पूर्ण

		/* shअगरt the 12-bit data (+ sign) to match the रेजिस्टर */
		val <<= 3;

		ग_लिखोw(val, devpriv->las1 + LAS1_DAC_FIFO(chan));
		ग_लिखोw(0, dev->mmio + LAS0_UPDATE_DAC(chan));

		ret = comedi_समयout(dev, s, insn, rtd_ao_eoc, 0);
		अगर (ret)
			वापस ret;

		s->पढ़ोback[chan] = data[i];
	पूर्ण

	वापस insn->n;
पूर्ण

अटल पूर्णांक rtd_dio_insn_bits(काष्ठा comedi_device *dev,
			     काष्ठा comedi_subdevice *s,
			     काष्ठा comedi_insn *insn,
			     अचिन्हित पूर्णांक *data)
अणु
	अगर (comedi_dio_update_state(s, data))
		ग_लिखोw(s->state & 0xff, dev->mmio + LAS0_DIO0);

	data[1] = पढ़ोw(dev->mmio + LAS0_DIO0) & 0xff;

	वापस insn->n;
पूर्ण

अटल पूर्णांक rtd_dio_insn_config(काष्ठा comedi_device *dev,
			       काष्ठा comedi_subdevice *s,
			       काष्ठा comedi_insn *insn,
			       अचिन्हित पूर्णांक *data)
अणु
	पूर्णांक ret;

	ret = comedi_dio_insn_config(dev, s, insn, data, 0);
	अगर (ret)
		वापस ret;

	/* TODO support digital match पूर्णांकerrupts and strobes */

	/* set direction */
	ग_लिखोw(0x01, dev->mmio + LAS0_DIO_STATUS);
	ग_लिखोw(s->io_bits & 0xff, dev->mmio + LAS0_DIO0_CTRL);

	/* clear पूर्णांकerrupts */
	ग_लिखोw(0x00, dev->mmio + LAS0_DIO_STATUS);

	/* port1 can only be all input or all output */

	/* there are also 2 user input lines and 2 user output lines */

	वापस insn->n;
पूर्ण

अटल पूर्णांक rtd_counter_insn_config(काष्ठा comedi_device *dev,
				   काष्ठा comedi_subdevice *s,
				   काष्ठा comedi_insn *insn,
				   अचिन्हित पूर्णांक *data)
अणु
	काष्ठा rtd_निजी *devpriv = dev->निजी;
	अचिन्हित पूर्णांक chan = CR_CHAN(insn->chanspec);
	अचिन्हित पूर्णांक max_src;
	अचिन्हित पूर्णांक src;

	चयन (data[0]) अणु
	हाल INSN_CONFIG_SET_GATE_SRC:
		/*
		 * 8254 Timer/Counter gate sources:
		 *
		 * 0 = Not gated, मुक्त running (reset state)
		 * 1 = Gated, off
		 * 2 = Ext. TC Gate 1
		 * 3 = Ext. TC Gate 2
		 * 4 = Previous TC out (chan 1 and 2 only)
		 */
		src = data[2];
		max_src = (chan == 0) ? 3 : 4;
		अगर (src > max_src)
			वापस -EINVAL;

		devpriv->समयr_gate_src[chan] = src;
		ग_लिखोb(src, dev->mmio + LAS0_8254_GATE_SEL(chan));
		अवरोध;
	हाल INSN_CONFIG_GET_GATE_SRC:
		data[2] = devpriv->समयr_gate_src[chan];
		अवरोध;
	हाल INSN_CONFIG_SET_CLOCK_SRC:
		/*
		 * 8254 Timer/Counter घड़ी sources:
		 *
		 * 0 = 8 MHz (reset state)
		 * 1 = Ext. TC Clock 1
		 * 2 = Ext. TX Clock 2
		 * 3 = Ext. Pacer Clock
		 * 4 = Previous TC out (chan 1 and 2 only)
		 * 5 = High-Speed Digital Input Sampling संकेत (chan 1 only)
		 */
		src = data[1];
		चयन (chan) अणु
		हाल 0:
			max_src = 3;
			अवरोध;
		हाल 1:
			max_src = 5;
			अवरोध;
		हाल 2:
			max_src = 4;
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण
		अगर (src > max_src)
			वापस -EINVAL;

		devpriv->समयr_clk_src[chan] = src;
		ग_लिखोb(src, dev->mmio + LAS0_8254_CLK_SEL(chan));
		अवरोध;
	हाल INSN_CONFIG_GET_CLOCK_SRC:
		src = devpriv->समयr_clk_src[chan];
		data[1] = devpriv->समयr_clk_src[chan];
		data[2] = (src == 0) ? RTD_CLOCK_BASE : 0;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस insn->n;
पूर्ण

अटल व्योम rtd_reset(काष्ठा comedi_device *dev)
अणु
	काष्ठा rtd_निजी *devpriv = dev->निजी;

	ग_लिखोl(0, dev->mmio + LAS0_BOARD_RESET);
	usleep_range(100, 1000);	/* needed? */
	ग_लिखोl(0, devpriv->lcfg + PLX_REG_INTCSR);
	ग_लिखोw(0, dev->mmio + LAS0_IT);
	ग_लिखोw(~0, dev->mmio + LAS0_CLEAR);
	पढ़ोw(dev->mmio + LAS0_CLEAR);
पूर्ण

/*
 * initialize board, per RTD spec
 * also, initialize shaकरोw रेजिस्टरs
 */
अटल व्योम rtd_init_board(काष्ठा comedi_device *dev)
अणु
	rtd_reset(dev);

	ग_लिखोl(0, dev->mmio + LAS0_OVERRUN);
	ग_लिखोl(0, dev->mmio + LAS0_CGT_CLEAR);
	ग_लिखोl(0, dev->mmio + LAS0_ADC_FIFO_CLEAR);
	ग_लिखोl(0, dev->mmio + LAS0_DAC_RESET(0));
	ग_लिखोl(0, dev->mmio + LAS0_DAC_RESET(1));
	/* clear digital IO fअगरo */
	ग_लिखोw(0, dev->mmio + LAS0_DIO_STATUS);
	/* TODO: set user out source ??? */
पूर्ण

/* The RTD driver करोes this */
अटल व्योम rtd_pci_latency_quirk(काष्ठा comedi_device *dev,
				  काष्ठा pci_dev *pcidev)
अणु
	अचिन्हित अक्षर pci_latency;

	pci_पढ़ो_config_byte(pcidev, PCI_LATENCY_TIMER, &pci_latency);
	अगर (pci_latency < 32) अणु
		dev_info(dev->class_dev,
			 "PCI latency changed from %d to %d\n",
			 pci_latency, 32);
		pci_ग_लिखो_config_byte(pcidev, PCI_LATENCY_TIMER, 32);
	पूर्ण
पूर्ण

अटल पूर्णांक rtd_स्वतः_attach(काष्ठा comedi_device *dev,
			   अचिन्हित दीर्घ context)
अणु
	काष्ठा pci_dev *pcidev = comedi_to_pci_dev(dev);
	स्थिर काष्ठा rtd_boardinfo *board = शून्य;
	काष्ठा rtd_निजी *devpriv;
	काष्ठा comedi_subdevice *s;
	पूर्णांक ret;

	अगर (context < ARRAY_SIZE(rtd520_boards))
		board = &rtd520_boards[context];
	अगर (!board)
		वापस -ENODEV;
	dev->board_ptr = board;
	dev->board_name = board->name;

	devpriv = comedi_alloc_devpriv(dev, माप(*devpriv));
	अगर (!devpriv)
		वापस -ENOMEM;

	ret = comedi_pci_enable(dev);
	अगर (ret)
		वापस ret;

	dev->mmio = pci_ioremap_bar(pcidev, 2);
	devpriv->las1 = pci_ioremap_bar(pcidev, 3);
	devpriv->lcfg = pci_ioremap_bar(pcidev, 0);
	अगर (!dev->mmio || !devpriv->las1 || !devpriv->lcfg)
		वापस -ENOMEM;

	rtd_pci_latency_quirk(dev, pcidev);

	अगर (pcidev->irq) अणु
		ret = request_irq(pcidev->irq, rtd_पूर्णांकerrupt, IRQF_SHARED,
				  dev->board_name, dev);
		अगर (ret == 0)
			dev->irq = pcidev->irq;
	पूर्ण

	ret = comedi_alloc_subdevices(dev, 4);
	अगर (ret)
		वापस ret;

	s = &dev->subdevices[0];
	/* analog input subdevice */
	s->type		= COMEDI_SUBD_AI;
	s->subdev_flags	= SDF_READABLE | SDF_GROUND | SDF_COMMON | SDF_DIFF;
	s->n_chan	= 16;
	s->maxdata	= 0x0fff;
	s->range_table	= board->ai_range;
	s->len_chanlist	= RTD_MAX_CHANLIST;
	s->insn_पढ़ो	= rtd_ai_rinsn;
	अगर (dev->irq) अणु
		dev->पढ़ो_subdev = s;
		s->subdev_flags	|= SDF_CMD_READ;
		s->करो_cmd	= rtd_ai_cmd;
		s->करो_cmdtest	= rtd_ai_cmdtest;
		s->cancel	= rtd_ai_cancel;
	पूर्ण

	s = &dev->subdevices[1];
	/* analog output subdevice */
	s->type		= COMEDI_SUBD_AO;
	s->subdev_flags	= SDF_WRITABLE;
	s->n_chan	= 2;
	s->maxdata	= 0x0fff;
	s->range_table	= &rtd_ao_range;
	s->insn_ग_लिखो	= rtd_ao_insn_ग_लिखो;

	ret = comedi_alloc_subdev_पढ़ोback(s);
	अगर (ret)
		वापस ret;

	s = &dev->subdevices[2];
	/* digital i/o subdevice */
	s->type		= COMEDI_SUBD_DIO;
	s->subdev_flags	= SDF_READABLE | SDF_WRITABLE;
	/* we only support port 0 right now.  Ignoring port 1 and user IO */
	s->n_chan	= 8;
	s->maxdata	= 1;
	s->range_table	= &range_digital;
	s->insn_bits	= rtd_dio_insn_bits;
	s->insn_config	= rtd_dio_insn_config;

	/* 8254 Timer/Counter subdevice */
	s = &dev->subdevices[3];
	dev->pacer = comedi_8254_mm_init(dev->mmio + LAS0_8254_TIMER_BASE,
					 RTD_CLOCK_BASE, I8254_IO8, 2);
	अगर (!dev->pacer)
		वापस -ENOMEM;

	comedi_8254_subdevice_init(s, dev->pacer);
	dev->pacer->insn_config = rtd_counter_insn_config;

	rtd_init_board(dev);

	ret = rtd520_probe_fअगरo_depth(dev);
	अगर (ret < 0)
		वापस ret;
	devpriv->fअगरosz = ret;

	अगर (dev->irq)
		ग_लिखोl(PLX_INTCSR_PIEN | PLX_INTCSR_PLIEN,
		       devpriv->lcfg + PLX_REG_INTCSR);

	वापस 0;
पूर्ण

अटल व्योम rtd_detach(काष्ठा comedi_device *dev)
अणु
	काष्ठा rtd_निजी *devpriv = dev->निजी;

	अगर (devpriv) अणु
		/* Shut करोwn any board ops by resetting it */
		अगर (dev->mmio && devpriv->lcfg)
			rtd_reset(dev);
		अगर (dev->irq)
			मुक्त_irq(dev->irq, dev);
		अगर (dev->mmio)
			iounmap(dev->mmio);
		अगर (devpriv->las1)
			iounmap(devpriv->las1);
		अगर (devpriv->lcfg)
			iounmap(devpriv->lcfg);
	पूर्ण
	comedi_pci_disable(dev);
पूर्ण

अटल काष्ठा comedi_driver rtd520_driver = अणु
	.driver_name	= "rtd520",
	.module		= THIS_MODULE,
	.स्वतः_attach	= rtd_स्वतः_attach,
	.detach		= rtd_detach,
पूर्ण;

अटल पूर्णांक rtd520_pci_probe(काष्ठा pci_dev *dev,
			    स्थिर काष्ठा pci_device_id *id)
अणु
	वापस comedi_pci_स्वतः_config(dev, &rtd520_driver, id->driver_data);
पूर्ण

अटल स्थिर काष्ठा pci_device_id rtd520_pci_table[] = अणु
	अणु PCI_VDEVICE(RTD, 0x7520), BOARD_DM7520 पूर्ण,
	अणु PCI_VDEVICE(RTD, 0x4520), BOARD_PCI4520 पूर्ण,
	अणु 0 पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(pci, rtd520_pci_table);

अटल काष्ठा pci_driver rtd520_pci_driver = अणु
	.name		= "rtd520",
	.id_table	= rtd520_pci_table,
	.probe		= rtd520_pci_probe,
	.हटाओ		= comedi_pci_स्वतः_unconfig,
पूर्ण;
module_comedi_pci_driver(rtd520_driver, rtd520_pci_driver);

MODULE_AUTHOR("Comedi https://www.comedi.org");
MODULE_DESCRIPTION("Comedi low-level driver");
MODULE_LICENSE("GPL");
