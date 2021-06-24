<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * timbuart.c timberdale FPGA GPIO driver
 * Copyright (c) 2009 Intel Corporation
 */

/* Supports:
 * Timberdale FPGA UART
 */

#अगर_अघोषित _TIMBUART_H
#घोषणा _TIMBUART_H

#घोषणा TIMBUART_FIFO_SIZE	2048

#घोषणा TIMBUART_RXFIFO		0x08
#घोषणा TIMBUART_TXFIFO		0x0c
#घोषणा TIMBUART_IER		0x10
#घोषणा TIMBUART_IPR		0x14
#घोषणा TIMBUART_ISR		0x18
#घोषणा TIMBUART_CTRL		0x1c
#घोषणा TIMBUART_BAUDRATE	0x20

#घोषणा TIMBUART_CTRL_RTS	0x01
#घोषणा TIMBUART_CTRL_CTS	0x02
#घोषणा TIMBUART_CTRL_FLSHTX	0x40
#घोषणा TIMBUART_CTRL_FLSHRX	0x80

#घोषणा TXBF		0x01
#घोषणा TXBAE		0x02
#घोषणा CTS_DELTA	0x04
#घोषणा RXDP		0x08
#घोषणा RXBAF		0x10
#घोषणा RXBF		0x20
#घोषणा RXTT		0x40
#घोषणा RXBNAE		0x80
#घोषणा TXBE		0x100

#घोषणा RXFLAGS (RXDP | RXBAF | RXBF | RXTT | RXBNAE)
#घोषणा TXFLAGS (TXBF | TXBAE)

#घोषणा TIMBUART_MAJOR 204
#घोषणा TIMBUART_MINOR 192

#पूर्ण_अगर /* _TIMBUART_H */

