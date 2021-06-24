<शैली गुरु>
/*
 * sja1000.h -  Philips SJA1000 network device driver
 *
 * Copyright (c) 2003 Matthias Brukner, Trajet Gmbh, Rebenring 33,
 * 38106 Braunschweig, GERMANY
 *
 * Copyright (c) 2002-2007 Volkswagen Group Electronic Research
 * All rights reserved.
 *
 * Redistribution and use in source and binary क्रमms, with or without
 * modअगरication, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary क्रमm must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    करोcumentation and/or other materials provided with the distribution.
 * 3. Neither the name of Volkswagen nor the names of its contributors
 *    may be used to enकरोrse or promote products derived from this software
 *    without specअगरic prior written permission.
 *
 * Alternatively, provided that this notice is retained in full, this
 * software may be distributed under the terms of the GNU General
 * Public License ("GPL") version 2, in which हाल the provisions of the
 * GPL apply INSTEAD OF those given above.
 *
 * The provided data काष्ठाures and बाह्यal पूर्णांकerfaces from this code
 * are not restricted to be used by modules with a GPL compatible license.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY सूचीECT, INसूचीECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH
 * DAMAGE.
 *
 */

#अगर_अघोषित SJA1000_DEV_H
#घोषणा SJA1000_DEV_H

#समावेश <linux/irqवापस.h>
#समावेश <linux/can/dev.h>
#समावेश <linux/can/platक्रमm/sja1000.h>

#घोषणा SJA1000_ECHO_SKB_MAX	1 /* the SJA1000 has one TX buffer object */

#घोषणा SJA1000_MAX_IRQ 20	/* max. number of पूर्णांकerrupts handled in ISR */

/* SJA1000 रेजिस्टरs - manual section 6.4 (Pelican Mode) */
#घोषणा SJA1000_MOD		0x00
#घोषणा SJA1000_CMR		0x01
#घोषणा SJA1000_SR		0x02
#घोषणा SJA1000_IR		0x03
#घोषणा SJA1000_IER		0x04
#घोषणा SJA1000_ALC		0x0B
#घोषणा SJA1000_ECC		0x0C
#घोषणा SJA1000_EWL		0x0D
#घोषणा SJA1000_RXERR		0x0E
#घोषणा SJA1000_TXERR		0x0F
#घोषणा SJA1000_ACCC0		0x10
#घोषणा SJA1000_ACCC1		0x11
#घोषणा SJA1000_ACCC2		0x12
#घोषणा SJA1000_ACCC3		0x13
#घोषणा SJA1000_ACCM0		0x14
#घोषणा SJA1000_ACCM1		0x15
#घोषणा SJA1000_ACCM2		0x16
#घोषणा SJA1000_ACCM3		0x17
#घोषणा SJA1000_RMC		0x1D
#घोषणा SJA1000_RBSA		0x1E

/* Common रेजिस्टरs - manual section 6.5 */
#घोषणा SJA1000_BTR0		0x06
#घोषणा SJA1000_BTR1		0x07
#घोषणा SJA1000_OCR		0x08
#घोषणा SJA1000_CDR		0x1F

#घोषणा SJA1000_FI		0x10
#घोषणा SJA1000_SFF_BUF		0x13
#घोषणा SJA1000_EFF_BUF		0x15

#घोषणा SJA1000_FI_FF		0x80
#घोषणा SJA1000_FI_RTR		0x40

#घोषणा SJA1000_ID1		0x11
#घोषणा SJA1000_ID2		0x12
#घोषणा SJA1000_ID3		0x13
#घोषणा SJA1000_ID4		0x14

#घोषणा SJA1000_CAN_RAM		0x20

/* mode रेजिस्टर */
#घोषणा MOD_RM		0x01
#घोषणा MOD_LOM		0x02
#घोषणा MOD_STM		0x04
#घोषणा MOD_AFM		0x08
#घोषणा MOD_SM		0x10

/* commands */
#घोषणा CMD_SRR		0x10
#घोषणा CMD_CDO		0x08
#घोषणा CMD_RRB		0x04
#घोषणा CMD_AT		0x02
#घोषणा CMD_TR		0x01

/* पूर्णांकerrupt sources */
#घोषणा IRQ_BEI		0x80
#घोषणा IRQ_ALI		0x40
#घोषणा IRQ_EPI		0x20
#घोषणा IRQ_WUI		0x10
#घोषणा IRQ_DOI		0x08
#घोषणा IRQ_EI		0x04
#घोषणा IRQ_TI		0x02
#घोषणा IRQ_RI		0x01
#घोषणा IRQ_ALL		0xFF
#घोषणा IRQ_OFF		0x00

/* status रेजिस्टर content */
#घोषणा SR_BS		0x80
#घोषणा SR_ES		0x40
#घोषणा SR_TS		0x20
#घोषणा SR_RS		0x10
#घोषणा SR_TCS		0x08
#घोषणा SR_TBS		0x04
#घोषणा SR_DOS		0x02
#घोषणा SR_RBS		0x01

#घोषणा SR_CRIT (SR_BS|SR_ES)

/* ECC रेजिस्टर */
#घोषणा ECC_SEG		0x1F
#घोषणा ECC_सूची		0x20
#घोषणा ECC_ERR		6
#घोषणा ECC_BIT		0x00
#घोषणा ECC_FORM	0x40
#घोषणा ECC_STUFF	0x80
#घोषणा ECC_MASK	0xc0

/*
 * Flags क्रम sja1000priv.flags
 */
#घोषणा SJA1000_CUSTOM_IRQ_HANDLER 0x1

/*
 * SJA1000 निजी data काष्ठाure
 */
काष्ठा sja1000_priv अणु
	काष्ठा can_priv can;	/* must be the first member */
	काष्ठा sk_buff *echo_skb;

	/* the lower-layer is responsible क्रम appropriate locking */
	u8 (*पढ़ो_reg) (स्थिर काष्ठा sja1000_priv *priv, पूर्णांक reg);
	व्योम (*ग_लिखो_reg) (स्थिर काष्ठा sja1000_priv *priv, पूर्णांक reg, u8 val);
	व्योम (*pre_irq) (स्थिर काष्ठा sja1000_priv *priv);
	व्योम (*post_irq) (स्थिर काष्ठा sja1000_priv *priv);

	व्योम *priv;		/* क्रम board-specअगरic data */
	काष्ठा net_device *dev;

	व्योम __iomem *reg_base;	 /* ioremap'ed address to रेजिस्टरs */
	अचिन्हित दीर्घ irq_flags; /* क्रम request_irq() */
	spinlock_t cmdreg_lock;  /* lock क्रम concurrent cmd रेजिस्टर ग_लिखोs */

	u16 flags;		/* custom mode flags */
	u8 ocr;			/* output control रेजिस्टर */
	u8 cdr;			/* घड़ी भागider रेजिस्टर */
पूर्ण;

काष्ठा net_device *alloc_sja1000dev(पूर्णांक माप_priv);
व्योम मुक्त_sja1000dev(काष्ठा net_device *dev);
पूर्णांक रेजिस्टर_sja1000dev(काष्ठा net_device *dev);
व्योम unरेजिस्टर_sja1000dev(काष्ठा net_device *dev);

irqवापस_t sja1000_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id);

#पूर्ण_अगर /* SJA1000_DEV_H */
