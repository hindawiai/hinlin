<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * PIC32 Integrated Serial Driver.
 *
 * Copyright (C) 2015 Microchip Technology, Inc.
 *
 * Authors:
 *   Sorin-Andrei Pistirica <andrei.pistirica@microchip.com>
 */
#अगर_अघोषित __DT_PIC32_UART_H__
#घोषणा __DT_PIC32_UART_H__

#घोषणा PIC32_UART_DFLT_BRATE		(9600)
#घोषणा PIC32_UART_TX_FIFO_DEPTH	(8)
#घोषणा PIC32_UART_RX_FIFO_DEPTH	(8)

#घोषणा PIC32_UART_MODE		0x00
#घोषणा PIC32_UART_STA		0x10
#घोषणा PIC32_UART_TX		0x20
#घोषणा PIC32_UART_RX		0x30
#घोषणा PIC32_UART_BRG		0x40

काष्ठा pic32_console_opt अणु
	पूर्णांक baud;
	पूर्णांक parity;
	पूर्णांक bits;
	पूर्णांक flow;
पूर्ण;

/* काष्ठा pic32_sport - pic32 serial port descriptor
 * @port: uart port descriptor
 * @idx: port index
 * @irq_fault: भव fault पूर्णांकerrupt number
 * @irqflags_fault: flags related to fault irq
 * @irq_fault_name: irq fault name
 * @irq_rx: भव rx पूर्णांकerrupt number
 * @irqflags_rx: flags related to rx irq
 * @irq_rx_name: irq rx name
 * @irq_tx: भव tx पूर्णांकerrupt number
 * @irqflags_tx: : flags related to tx irq
 * @irq_tx_name: irq tx name
 * @cts_gpio: clear to send gpio
 * @dev: device descriptor
 **/
काष्ठा pic32_sport अणु
	काष्ठा uart_port port;
	काष्ठा pic32_console_opt opt;
	पूर्णांक idx;

	पूर्णांक irq_fault;
	पूर्णांक irqflags_fault;
	स्थिर अक्षर *irq_fault_name;
	पूर्णांक irq_rx;
	पूर्णांक irqflags_rx;
	स्थिर अक्षर *irq_rx_name;
	पूर्णांक irq_tx;
	पूर्णांक irqflags_tx;
	स्थिर अक्षर *irq_tx_name;
	u8 enable_tx_irq;

	bool hw_flow_ctrl;
	पूर्णांक cts_gpio;

	पूर्णांक ref_clk;
	काष्ठा clk *clk;

	काष्ठा device *dev;
पूर्ण;
#घोषणा to_pic32_sport(c) container_of(c, काष्ठा pic32_sport, port)
#घोषणा pic32_get_port(sport) (&sport->port)
#घोषणा pic32_get_opt(sport) (&sport->opt)
#घोषणा tx_irq_enabled(sport) (sport->enable_tx_irq)

अटल अंतरभूत व्योम pic32_uart_ग_लिखोl(काष्ठा pic32_sport *sport,
					u32 reg, u32 val)
अणु
	काष्ठा uart_port *port = pic32_get_port(sport);

	__raw_ग_लिखोl(val, port->membase + reg);
पूर्ण

अटल अंतरभूत u32 pic32_uart_पढ़ोl(काष्ठा pic32_sport *sport, u32 reg)
अणु
	काष्ठा uart_port *port = pic32_get_port(sport);

	वापस	__raw_पढ़ोl(port->membase + reg);
पूर्ण

/* pic32 uart mode रेजिस्टर bits */
#घोषणा PIC32_UART_MODE_ON        BIT(15)
#घोषणा PIC32_UART_MODE_FRZ       BIT(14)
#घोषणा PIC32_UART_MODE_SIDL      BIT(13)
#घोषणा PIC32_UART_MODE_IREN      BIT(12)
#घोषणा PIC32_UART_MODE_RTSMD     BIT(11)
#घोषणा PIC32_UART_MODE_RESV1     BIT(10)
#घोषणा PIC32_UART_MODE_UEN1      BIT(9)
#घोषणा PIC32_UART_MODE_UEN0      BIT(8)
#घोषणा PIC32_UART_MODE_WAKE      BIT(7)
#घोषणा PIC32_UART_MODE_LPBK      BIT(6)
#घोषणा PIC32_UART_MODE_ABAUD     BIT(5)
#घोषणा PIC32_UART_MODE_RXINV     BIT(4)
#घोषणा PIC32_UART_MODE_BRGH      BIT(3)
#घोषणा PIC32_UART_MODE_PDSEL1    BIT(2)
#घोषणा PIC32_UART_MODE_PDSEL0    BIT(1)
#घोषणा PIC32_UART_MODE_STSEL     BIT(0)

/* pic32 uart status रेजिस्टर bits */
#घोषणा PIC32_UART_STA_UTXISEL1   BIT(15)
#घोषणा PIC32_UART_STA_UTXISEL0   BIT(14)
#घोषणा PIC32_UART_STA_UTXINV     BIT(13)
#घोषणा PIC32_UART_STA_URXEN      BIT(12)
#घोषणा PIC32_UART_STA_UTXBRK     BIT(11)
#घोषणा PIC32_UART_STA_UTXEN      BIT(10)
#घोषणा PIC32_UART_STA_UTXBF      BIT(9)
#घोषणा PIC32_UART_STA_TRMT       BIT(8)
#घोषणा PIC32_UART_STA_URXISEL1   BIT(7)
#घोषणा PIC32_UART_STA_URXISEL0   BIT(6)
#घोषणा PIC32_UART_STA_ADDEN      BIT(5)
#घोषणा PIC32_UART_STA_RIDLE      BIT(4)
#घोषणा PIC32_UART_STA_PERR       BIT(3)
#घोषणा PIC32_UART_STA_FERR       BIT(2)
#घोषणा PIC32_UART_STA_OERR       BIT(1)
#घोषणा PIC32_UART_STA_URXDA      BIT(0)

#पूर्ण_अगर /* __DT_PIC32_UART_H__ */
