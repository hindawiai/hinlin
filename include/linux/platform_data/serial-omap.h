<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Driver क्रम OMAP-UART controller.
 * Based on drivers/serial/8250.c
 *
 * Copyright (C) 2010 Texas Instruments.
 *
 * Authors:
 *	Govindraj R	<govindraj.raja@ti.com>
 *	Thara Gopinath	<thara@ti.com>
 */

#अगर_अघोषित __OMAP_SERIAL_H__
#घोषणा __OMAP_SERIAL_H__

#समावेश <linux/serial_core.h>
#समावेश <linux/device.h>
#समावेश <linux/pm_qos.h>

#घोषणा OMAP_SERIAL_DRIVER_NAME	"omap_uart"

/*
 * Use tty device name as ttyO, [O -> OMAP]
 * in bootargs we specअगरy as console=ttyO0 अगर uart1
 * is used as console uart.
 */
#घोषणा OMAP_SERIAL_NAME	"ttyO"

काष्ठा omap_uart_port_info अणु
	bool			dma_enabled;	/* To specअगरy DMA Mode */
	अचिन्हित पूर्णांक		uartclk;	/* UART घड़ी rate */
	upf_t			flags;		/* UPF_* flags */
	अचिन्हित पूर्णांक		dma_rx_buf_size;
	अचिन्हित पूर्णांक		dma_rx_समयout;
	अचिन्हित पूर्णांक		स्वतःsuspend_समयout;
	अचिन्हित पूर्णांक		dma_rx_poll_rate;

	पूर्णांक (*get_context_loss_count)(काष्ठा device *);
	व्योम (*enable_wakeup)(काष्ठा device *, bool);
पूर्ण;

#पूर्ण_अगर /* __OMAP_SERIAL_H__ */
