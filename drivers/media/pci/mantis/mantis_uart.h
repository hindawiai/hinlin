<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
	Mantis PCI bridge driver

	Copyright (C) Manu Abraham (abraham.manu@gmail.com)

*/

#अगर_अघोषित __MANTIS_UART_H
#घोषणा __MANTIS_UART_H

#घोषणा MANTIS_UART_CTL			0xe0
#घोषणा MANTIS_UART_RXINT		(1 << 4)
#घोषणा MANTIS_UART_RXFLUSH		(1 << 2)

#घोषणा MANTIS_UART_RXD			0xe8
#घोषणा MANTIS_UART_BAUD		0xec

#घोषणा MANTIS_UART_STAT		0xf0
#घोषणा MANTIS_UART_RXFIFO_DATA		(1 << 7)
#घोषणा MANTIS_UART_RXFIFO_EMPTY	(1 << 6)
#घोषणा MANTIS_UART_RXFIFO_FULL		(1 << 3)
#घोषणा MANTIS_UART_FRAME_ERR		(1 << 2)
#घोषणा MANTIS_UART_PARITY_ERR		(1 << 1)
#घोषणा MANTIS_UART_RXTHRESH_INT	(1 << 0)

क्रमागत mantis_baud अणु
	MANTIS_BAUD_9600	= 0,
	MANTIS_BAUD_19200,
	MANTIS_BAUD_38400,
	MANTIS_BAUD_57600,
	MANTIS_BAUD_115200
पूर्ण;

क्रमागत mantis_parity अणु
	MANTIS_PARITY_NONE	= 0,
	MANTIS_PARITY_EVEN,
	MANTIS_PARITY_ODD,
पूर्ण;

काष्ठा mantis_pci;

बाह्य पूर्णांक mantis_uart_init(काष्ठा mantis_pci *mantis);
बाह्य व्योम mantis_uart_निकास(काष्ठा mantis_pci *mantis);

#पूर्ण_अगर /* __MANTIS_UART_H */
