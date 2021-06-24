<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * include/linux/aपंचांगel_pdc.h
 *
 * Copyright (C) 2005 Ivan Kokshaysky
 * Copyright (C) SAN People
 *
 * Peripheral Data Controller (PDC) रेजिस्टरs.
 * Based on AT91RM9200 datasheet revision E.
 */

#अगर_अघोषित ATMEL_PDC_H
#घोषणा ATMEL_PDC_H

#घोषणा ATMEL_PDC_RPR		0x100	/* Receive Poपूर्णांकer Register */
#घोषणा ATMEL_PDC_RCR		0x104	/* Receive Counter Register */
#घोषणा ATMEL_PDC_TPR		0x108	/* Transmit Poपूर्णांकer Register */
#घोषणा ATMEL_PDC_TCR		0x10c	/* Transmit Counter Register */
#घोषणा ATMEL_PDC_RNPR		0x110	/* Receive Next Poपूर्णांकer Register */
#घोषणा ATMEL_PDC_RNCR		0x114	/* Receive Next Counter Register */
#घोषणा ATMEL_PDC_TNPR		0x118	/* Transmit Next Poपूर्णांकer Register */
#घोषणा ATMEL_PDC_TNCR		0x11c	/* Transmit Next Counter Register */

#घोषणा ATMEL_PDC_PTCR		0x120	/* Transfer Control Register */
#घोषणा		ATMEL_PDC_RXTEN		(1 << 0)	/* Receiver Transfer Enable */
#घोषणा		ATMEL_PDC_RXTDIS	(1 << 1)	/* Receiver Transfer Disable */
#घोषणा		ATMEL_PDC_TXTEN		(1 << 8)	/* Transmitter Transfer Enable */
#घोषणा		ATMEL_PDC_TXTDIS	(1 << 9)	/* Transmitter Transfer Disable */

#घोषणा ATMEL_PDC_PTSR		0x124	/* Transfer Status Register */

#घोषणा ATMEL_PDC_SCND_BUF_OFF	0x10	/* Offset between first and second buffer रेजिस्टरs */

#पूर्ण_अगर
