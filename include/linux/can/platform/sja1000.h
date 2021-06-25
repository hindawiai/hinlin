<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _CAN_PLATFORM_SJA1000_H
#घोषणा _CAN_PLATFORM_SJA1000_H

/* घड़ी भागider रेजिस्टर */
#घोषणा CDR_CLKOUT_MASK 0x07
#घोषणा CDR_CLK_OFF	0x08 /* Clock off (CLKOUT pin) */
#घोषणा CDR_RXINPEN	0x20 /* TX1 output is RX irq output */
#घोषणा CDR_CBP		0x40 /* CAN input comparator bypass */
#घोषणा CDR_PELICAN	0x80 /* PeliCAN mode */

/* output control रेजिस्टर */
#घोषणा OCR_MODE_BIPHASE  0x00
#घोषणा OCR_MODE_TEST     0x01
#घोषणा OCR_MODE_NORMAL   0x02
#घोषणा OCR_MODE_CLOCK    0x03
#घोषणा OCR_MODE_MASK     0x07
#घोषणा OCR_TX0_INVERT    0x04
#घोषणा OCR_TX0_PULLDOWN  0x08
#घोषणा OCR_TX0_PULLUP    0x10
#घोषणा OCR_TX0_PUSHPULL  0x18
#घोषणा OCR_TX1_INVERT    0x20
#घोषणा OCR_TX1_PULLDOWN  0x40
#घोषणा OCR_TX1_PULLUP    0x80
#घोषणा OCR_TX1_PUSHPULL  0xc0
#घोषणा OCR_TX_MASK       0xfc
#घोषणा OCR_TX_SHIFT      2

काष्ठा sja1000_platक्रमm_data अणु
	u32 osc_freq;	/* CAN bus oscillator frequency in Hz */

	u8 ocr;		/* output control रेजिस्टर */
	u8 cdr;		/* घड़ी भागider रेजिस्टर */
पूर्ण;

#पूर्ण_अगर	/* !_CAN_PLATFORM_SJA1000_H */
