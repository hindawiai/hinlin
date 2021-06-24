<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/* Synopsys DesignWare 8250 library header file. */

#समावेश <linux/types.h>

#समावेश "8250.h"

काष्ठा dw8250_port_data अणु
	/* Port properties */
	पूर्णांक			line;

	/* DMA operations */
	काष्ठा uart_8250_dma	dma;

	/* Hardware configuration */
	u8			dlf_size;
पूर्ण;

व्योम dw8250_setup_port(काष्ठा uart_port *p);
