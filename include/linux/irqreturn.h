<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_IRQRETURN_H
#घोषणा _LINUX_IRQRETURN_H

/**
 * क्रमागत irqवापस
 * @IRQ_NONE		पूर्णांकerrupt was not from this device or was not handled
 * @IRQ_HANDLED		पूर्णांकerrupt was handled by this device
 * @IRQ_WAKE_THREAD	handler requests to wake the handler thपढ़ो
 */
क्रमागत irqवापस अणु
	IRQ_NONE		= (0 << 0),
	IRQ_HANDLED		= (1 << 0),
	IRQ_WAKE_THREAD		= (1 << 1),
पूर्ण;

प्रकार क्रमागत irqवापस irqवापस_t;
#घोषणा IRQ_RETVAL(x)	((x) ? IRQ_HANDLED : IRQ_NONE)

#पूर्ण_अगर
