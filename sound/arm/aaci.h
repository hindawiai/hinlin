<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *  linux/sound/arm/aaci.c - ARM PrimeCell AACI PL041 driver
 *
 *  Copyright (C) 2003 Deep Blue Solutions, Ltd, All Rights Reserved.
 */
#अगर_अघोषित AACI_H
#घोषणा AACI_H

/*
 * Control and status रेजिस्टर offsets
 *  P39.
 */
#घोषणा AACI_CSCH1	0x000
#घोषणा AACI_CSCH2	0x014
#घोषणा AACI_CSCH3	0x028
#घोषणा AACI_CSCH4	0x03c

#घोषणा AACI_RXCR	0x000	/* 29 bits Control Rx FIFO */
#घोषणा AACI_TXCR	0x004	/* 17 bits Control Tx FIFO */
#घोषणा AACI_SR		0x008	/* 12 bits Status */
#घोषणा AACI_ISR	0x00c	/* 7 bits  Int Status */
#घोषणा AACI_IE 	0x010	/* 7 bits  Int Enable */

/*
 * Other रेजिस्टरs
 */
#घोषणा AACI_SL1RX	0x050
#घोषणा AACI_SL1TX	0x054
#घोषणा AACI_SL2RX	0x058
#घोषणा AACI_SL2TX	0x05c
#घोषणा AACI_SL12RX	0x060
#घोषणा AACI_SL12TX	0x064
#घोषणा AACI_SLFR	0x068	/* slot flags */
#घोषणा AACI_SLISTAT	0x06c	/* slot पूर्णांकerrupt status */
#घोषणा AACI_SLIEN	0x070	/* slot पूर्णांकerrupt enable */
#घोषणा AACI_INTCLR	0x074	/* पूर्णांकerrupt clear */
#घोषणा AACI_MAINCR	0x078	/* मुख्य control */
#घोषणा AACI_RESET	0x07c	/* reset control */
#घोषणा AACI_SYNC	0x080	/* sync control */
#घोषणा AACI_ALLINTS	0x084	/* all fअगरo पूर्णांकerrupt status */
#घोषणा AACI_MAINFR	0x088	/* मुख्य flag रेजिस्टर */
#घोषणा AACI_DR1	0x090	/* data पढ़ो/written fअगरo 1 */
#घोषणा AACI_DR2	0x0b0	/* data पढ़ो/written fअगरo 2 */
#घोषणा AACI_DR3	0x0d0	/* data पढ़ो/written fअगरo 3 */
#घोषणा AACI_DR4	0x0f0	/* data पढ़ो/written fअगरo 4 */

/*
 * TX/RX fअगरo control रेजिस्टर (CR). P48
 */
#घोषणा CR_FEN		(1 << 16)	/* fअगरo enable */
#घोषणा CR_COMPACT	(1 << 15)	/* compact mode */
#घोषणा CR_SZ16		(0 << 13)	/* 16 bits */
#घोषणा CR_SZ18		(1 << 13)	/* 18 bits */
#घोषणा CR_SZ20		(2 << 13)	/* 20 bits */
#घोषणा CR_SZ12		(3 << 13)	/* 12 bits */
#घोषणा CR_SL12		(1 << 12)
#घोषणा CR_SL11		(1 << 11)
#घोषणा CR_SL10		(1 << 10)
#घोषणा CR_SL9		(1 << 9)
#घोषणा CR_SL8		(1 << 8)
#घोषणा CR_SL7		(1 << 7)
#घोषणा CR_SL6		(1 << 6)
#घोषणा CR_SL5		(1 << 5)
#घोषणा CR_SL4		(1 << 4)
#घोषणा CR_SL3		(1 << 3)
#घोषणा CR_SL2		(1 << 2)
#घोषणा CR_SL1		(1 << 1)
#घोषणा CR_EN		(1 << 0)	/* transmit enable */

/*
 * status रेजिस्टर bits. P49
 */
#घोषणा SR_RXTOFE	(1 << 11)	/* rx समयout fअगरo empty */
#घोषणा SR_TXTO		(1 << 10)	/* rx समयout fअगरo nonempty */
#घोषणा SR_TXU		(1 << 9)	/* tx underrun */
#घोषणा SR_RXO		(1 << 8)	/* rx overrun */
#घोषणा SR_TXB		(1 << 7)	/* tx busy */
#घोषणा SR_RXB		(1 << 6)	/* rx busy */
#घोषणा SR_TXFF		(1 << 5)	/* tx fअगरo full */
#घोषणा SR_RXFF		(1 << 4)	/* rx fअगरo full */
#घोषणा SR_TXHE		(1 << 3)	/* tx fअगरo half empty */
#घोषणा SR_RXHF		(1 << 2)	/* rx fअगरo half full */
#घोषणा SR_TXFE		(1 << 1)	/* tx fअगरo empty */
#घोषणा SR_RXFE		(1 << 0)	/* rx fअगरo empty */

/*
 * पूर्णांकerrupt status रेजिस्टर bits.
 */
#घोषणा ISR_RXTOFEINTR	(1 << 6)	/* rx fअगरo empty */
#घोषणा ISR_URINTR	(1 << 5)	/* tx underflow */
#घोषणा ISR_ORINTR	(1 << 4)	/* rx overflow */
#घोषणा ISR_RXINTR	(1 << 3)	/* rx fअगरo */
#घोषणा ISR_TXINTR	(1 << 2)	/* tx fअगरo पूर्णांकr */
#घोषणा ISR_RXTOINTR	(1 << 1)	/* tx समयout */
#घोषणा ISR_TXCINTR	(1 << 0)	/* tx complete */

/*
 * पूर्णांकerrupt enable रेजिस्टर bits.
 */
#घोषणा IE_RXTOIE	(1 << 6)
#घोषणा IE_URIE		(1 << 5)
#घोषणा IE_ORIE		(1 << 4)
#घोषणा IE_RXIE		(1 << 3)
#घोषणा IE_TXIE		(1 << 2)
#घोषणा IE_RXTIE	(1 << 1)
#घोषणा IE_TXCIE	(1 << 0)

/*
 * पूर्णांकerrupt status. P51
 */
#घोषणा ISR_RXTOFE	(1 << 6)	/* rx समयout fअगरo empty */
#घोषणा ISR_UR		(1 << 5)	/* tx fअगरo underrun */
#घोषणा ISR_OR		(1 << 4)	/* rx fअगरo overrun */
#घोषणा ISR_RX		(1 << 3)	/* rx पूर्णांकerrupt status */
#घोषणा ISR_TX		(1 << 2)	/* tx पूर्णांकerrupt status */
#घोषणा ISR_RXTO	(1 << 1)	/* rx समयout */
#घोषणा ISR_TXC		(1 << 0)	/* tx complete */

/*
 * पूर्णांकerrupt enable. P52
 */
#घोषणा IE_RXTOFE	(1 << 6)	/* rx समयout fअगरo empty */
#घोषणा IE_UR		(1 << 5)	/* tx fअगरo underrun */
#घोषणा IE_OR		(1 << 4)	/* rx fअगरo overrun */
#घोषणा IE_RX		(1 << 3)	/* rx पूर्णांकerrupt status */
#घोषणा IE_TX		(1 << 2)	/* tx पूर्णांकerrupt status */
#घोषणा IE_RXTO		(1 << 1)	/* rx समयout */
#घोषणा IE_TXC		(1 << 0)	/* tx complete */

/*
 * slot flag रेजिस्टर bits. P56
 */
#घोषणा SLFR_RWIS	(1 << 13)	/* raw wake-up पूर्णांकerrupt status */
#घोषणा SLFR_RGPIOINTR	(1 << 12)	/* raw gpio पूर्णांकerrupt */
#घोषणा SLFR_12TXE	(1 << 11)	/* slot 12 tx empty */
#घोषणा SLFR_12RXV	(1 << 10)	/* slot 12 rx valid */
#घोषणा SLFR_2TXE	(1 << 9)	/* slot 2 tx empty */
#घोषणा SLFR_2RXV	(1 << 8)	/* slot 2 rx valid */
#घोषणा SLFR_1TXE	(1 << 7)	/* slot 1 tx empty */
#घोषणा SLFR_1RXV	(1 << 6)	/* slot 1 rx valid */
#घोषणा SLFR_12TXB	(1 << 5)	/* slot 12 tx busy */
#घोषणा SLFR_12RXB	(1 << 4)	/* slot 12 rx busy */
#घोषणा SLFR_2TXB	(1 << 3)	/* slot 2 tx busy */
#घोषणा SLFR_2RXB	(1 << 2)	/* slot 2 rx busy */
#घोषणा SLFR_1TXB	(1 << 1)	/* slot 1 tx busy */
#घोषणा SLFR_1RXB	(1 << 0)	/* slot 1 rx busy */

/*
 * Interrupt clear रेजिस्टर.
 */
#घोषणा ICLR_RXTOFEC4	(1 << 12)
#घोषणा ICLR_RXTOFEC3	(1 << 11)
#घोषणा ICLR_RXTOFEC2	(1 << 10)
#घोषणा ICLR_RXTOFEC1	(1 << 9)
#घोषणा ICLR_TXUEC4	(1 << 8)
#घोषणा ICLR_TXUEC3	(1 << 7)
#घोषणा ICLR_TXUEC2	(1 << 6)
#घोषणा ICLR_TXUEC1	(1 << 5)
#घोषणा ICLR_RXOEC4	(1 << 4)
#घोषणा ICLR_RXOEC3	(1 << 3)
#घोषणा ICLR_RXOEC2	(1 << 2)
#घोषणा ICLR_RXOEC1	(1 << 1)
#घोषणा ICLR_WISC	(1 << 0)

/*
 * Main control रेजिस्टर bits. P62
 */
#घोषणा MAINCR_SCRA(x)	((x) << 10)	/* secondary codec reg access */
#घोषणा MAINCR_DMAEN	(1 << 9)	/* dma enable */
#घोषणा MAINCR_SL12TXEN	(1 << 8)	/* slot 12 transmit enable */
#घोषणा MAINCR_SL12RXEN	(1 << 7)	/* slot 12 receive enable */
#घोषणा MAINCR_SL2TXEN	(1 << 6)	/* slot 2 transmit enable */
#घोषणा MAINCR_SL2RXEN	(1 << 5)	/* slot 2 receive enable */
#घोषणा MAINCR_SL1TXEN	(1 << 4)	/* slot 1 transmit enable */
#घोषणा MAINCR_SL1RXEN	(1 << 3)	/* slot 1 receive enable */
#घोषणा MAINCR_LPM	(1 << 2)	/* low घातer mode */
#घोषणा MAINCR_LOOPBK	(1 << 1)	/* loopback */
#घोषणा MAINCR_IE	(1 << 0)	/* aaci पूर्णांकerface enable */

/*
 * Reset रेजिस्टर bits. P65
 */
#घोषणा RESET_NRST	(1 << 0)

/*
 * Sync रेजिस्टर bits. P65
 */
#घोषणा SYNC_FORCE	(1 << 0)

/*
 * Main flag रेजिस्टर bits. P66
 */
#घोषणा MAINFR_TXB	(1 << 1)	/* transmit busy */
#घोषणा MAINFR_RXB	(1 << 0)	/* receive busy */



काष्ठा aaci_runसमय अणु
	व्योम			__iomem *base;
	व्योम			__iomem *fअगरo;
	spinlock_t		lock;

	काष्ठा ac97_pcm		*pcm;
	पूर्णांक			pcm_खोलो;

	u32			cr;
	काष्ठा snd_pcm_substream	*substream;

	अचिन्हित पूर्णांक		period;	/* byte size of a "period" */

	/*
	 * PIO support
	 */
	व्योम			*start;
	व्योम			*end;
	व्योम			*ptr;
	पूर्णांक			bytes;
	अचिन्हित पूर्णांक		fअगरo_bytes;
पूर्ण;

काष्ठा aaci अणु
	काष्ठा amba_device	*dev;
	काष्ठा snd_card		*card;
	व्योम			__iomem *base;
	अचिन्हित पूर्णांक		fअगरo_depth;
	अचिन्हित पूर्णांक		users;
	काष्ठा mutex		irq_lock;

	/* AC'97 */
	काष्ठा mutex		ac97_sem;
	काष्ठा snd_ac97_bus	*ac97_bus;
	काष्ठा snd_ac97		*ac97;

	u32			मुख्यcr;

	काष्ठा aaci_runसमय	playback;
	काष्ठा aaci_runसमय	capture;

	काष्ठा snd_pcm		*pcm;
पूर्ण;

#घोषणा ACSTREAM_FRONT		0
#घोषणा ACSTREAM_SURROUND	1
#घोषणा ACSTREAM_LFE		2

#पूर्ण_अगर
