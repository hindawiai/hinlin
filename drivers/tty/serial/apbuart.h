<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __GRLIB_APBUART_H__
#घोषणा __GRLIB_APBUART_H__

#समावेश <यंत्र/पन.स>

#घोषणा UART_NR		8
अटल पूर्णांक grlib_apbuart_port_nr;

काष्ठा grlib_apbuart_regs_map अणु
	u32 data;
	u32 status;
	u32 ctrl;
	u32 scaler;
पूर्ण;

काष्ठा amba_prom_रेजिस्टरs अणु
	अचिन्हित पूर्णांक phys_addr;
	अचिन्हित पूर्णांक reg_size;
पूर्ण;

/*
 *  The following defines the bits in the APBUART Status Registers.
 */
#घोषणा UART_STATUS_DR   0x00000001	/* Data Ready */
#घोषणा UART_STATUS_TSE  0x00000002	/* TX Send Register Empty */
#घोषणा UART_STATUS_THE  0x00000004	/* TX Hold Register Empty */
#घोषणा UART_STATUS_BR   0x00000008	/* Break Error */
#घोषणा UART_STATUS_OE   0x00000010	/* RX Overrun Error */
#घोषणा UART_STATUS_PE   0x00000020	/* RX Parity Error */
#घोषणा UART_STATUS_FE   0x00000040	/* RX Framing Error */
#घोषणा UART_STATUS_ERR  0x00000078	/* Error Mask */

/*
 *  The following defines the bits in the APBUART Ctrl Registers.
 */
#घोषणा UART_CTRL_RE     0x00000001	/* Receiver enable */
#घोषणा UART_CTRL_TE     0x00000002	/* Transmitter enable */
#घोषणा UART_CTRL_RI     0x00000004	/* Receiver पूर्णांकerrupt enable */
#घोषणा UART_CTRL_TI     0x00000008	/* Transmitter irq */
#घोषणा UART_CTRL_PS     0x00000010	/* Parity select */
#घोषणा UART_CTRL_PE     0x00000020	/* Parity enable */
#घोषणा UART_CTRL_FL     0x00000040	/* Flow control enable */
#घोषणा UART_CTRL_LB     0x00000080	/* Loopback enable */

#घोषणा APBBASE(port) ((काष्ठा grlib_apbuart_regs_map *)((port)->membase))

#घोषणा APBBASE_DATA_P(port)	(&(APBBASE(port)->data))
#घोषणा APBBASE_STATUS_P(port)	(&(APBBASE(port)->status))
#घोषणा APBBASE_CTRL_P(port)	(&(APBBASE(port)->ctrl))
#घोषणा APBBASE_SCALAR_P(port)	(&(APBBASE(port)->scaler))

#घोषणा UART_GET_CHAR(port)	(__raw_पढ़ोl(APBBASE_DATA_P(port)))
#घोषणा UART_PUT_CHAR(port, v)	(__raw_ग_लिखोl(v, APBBASE_DATA_P(port)))
#घोषणा UART_GET_STATUS(port)	(__raw_पढ़ोl(APBBASE_STATUS_P(port)))
#घोषणा UART_PUT_STATUS(port, v)(__raw_ग_लिखोl(v, APBBASE_STATUS_P(port)))
#घोषणा UART_GET_CTRL(port)	(__raw_पढ़ोl(APBBASE_CTRL_P(port)))
#घोषणा UART_PUT_CTRL(port, v)	(__raw_ग_लिखोl(v, APBBASE_CTRL_P(port)))
#घोषणा UART_GET_SCAL(port)	(__raw_पढ़ोl(APBBASE_SCALAR_P(port)))
#घोषणा UART_PUT_SCAL(port, v)	(__raw_ग_लिखोl(v, APBBASE_SCALAR_P(port)))

#घोषणा UART_RX_DATA(s)		(((s) & UART_STATUS_DR) != 0)
#घोषणा UART_TX_READY(s)	(((s) & UART_STATUS_THE) != 0)

#पूर्ण_अगर /* __GRLIB_APBUART_H__ */
