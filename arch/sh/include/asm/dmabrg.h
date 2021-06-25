<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * SH7760 DMABRG (USB/Audio) support
 */

#अगर_अघोषित _DMABRG_H_
#घोषणा _DMABRG_H_

/* IRQ sources */
#घोषणा DMABRGIRQ_USBDMA	0
#घोषणा DMABRGIRQ_USBDMAERR	1
#घोषणा DMABRGIRQ_A0TXF		2
#घोषणा DMABRGIRQ_A0TXH		3
#घोषणा DMABRGIRQ_A0RXF		4
#घोषणा DMABRGIRQ_A0RXH		5
#घोषणा DMABRGIRQ_A1TXF		6
#घोषणा DMABRGIRQ_A1TXH		7
#घोषणा DMABRGIRQ_A1RXF		8
#घोषणा DMABRGIRQ_A1RXH		9

बाह्य पूर्णांक dmabrg_request_irq(अचिन्हित पूर्णांक, व्योम(*)(व्योम *), व्योम *);
बाह्य व्योम dmabrg_मुक्त_irq(अचिन्हित पूर्णांक);

#पूर्ण_अगर
