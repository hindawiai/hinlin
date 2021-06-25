<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (c) 2010 Simtec Electronics
 *	Ben Dooks <ben@simtec.co.uk>
 *
 * Header file क्रम Samsung SoC UART IRQ demux क्रम S3C64XX and later
 */

काष्ठा s3c_uart_irq अणु
	व्योम __iomem	*regs;
	अचिन्हित पूर्णांक	 base_irq;
	अचिन्हित पूर्णांक	 parent_irq;
पूर्ण;

बाह्य व्योम s3c_init_uart_irqs(काष्ठा s3c_uart_irq *irq, अचिन्हित पूर्णांक nr_irqs);

