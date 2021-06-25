<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Driver क्रम the PSC of the Freescale MPC52xx PSCs configured as UARTs.
 *
 * FIXME According to the usermanual the status bits in the status रेजिस्टर
 * are only updated when the peripherals access the FIFO and not when the
 * CPU access them. So since we use this bits to know when we stop writing
 * and पढ़ोing, they may not be updated in-समय and a race condition may
 * exists. But I haven't be able to prove this and I don't care. But अगर
 * any problem arises, it might worth checking. The TX/RX FIFO Stats
 * रेजिस्टरs should be used in addition.
 * Update: Actually, they seem updated ... At least the bits we use.
 *
 *
 * Maपूर्णांकainer : Sylvain Munaut <tnt@246tNt.com>
 *
 * Some of the code has been inspired/copied from the 2.4 code written
 * by Dale Farnsworth <dfarnsworth@mvista.com>.
 *
 * Copyright (C) 2008 Freescale Semiconductor Inc.
 *                    John Rigby <jrigby@gmail.com>
 * Added support क्रम MPC5121
 * Copyright (C) 2006 Secret Lab Technologies Ltd.
 *                    Grant Likely <grant.likely@secretlab.ca>
 * Copyright (C) 2004-2006 Sylvain Munaut <tnt@246tNt.com>
 * Copyright (C) 2003 MontaVista, Software, Inc.
 */

#अघोषित DEBUG

#समावेश <linux/device.h>
#समावेश <linux/module.h>
#समावेश <linux/tty.h>
#समावेश <linux/tty_flip.h>
#समावेश <linux/serial.h>
#समावेश <linux/sysrq.h>
#समावेश <linux/console.h>
#समावेश <linux/delay.h>
#समावेश <linux/पन.स>
#समावेश <linux/of.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/clk.h>

#समावेश <यंत्र/mpc52xx.h>
#समावेश <यंत्र/mpc52xx_psc.h>

#समावेश <linux/serial_core.h>


/* We've been asचिन्हित a range on the "Low-density serial ports" major */
#घोषणा SERIAL_PSC_MAJOR	204
#घोषणा SERIAL_PSC_MINOR	148


#घोषणा ISR_PASS_LIMIT 256	/* Max number of iteration in the पूर्णांकerrupt */


अटल काष्ठा uart_port mpc52xx_uart_ports[MPC52xx_PSC_MAXNUM];
	/* Rem: - We use the पढ़ो_status_mask as a shaकरोw of
	 *        psc->mpc52xx_psc_imr
	 *      - It's important that is array is all zero on start as we
	 *        use it to know अगर it's initialized or not ! If it's not sure
	 *        it's cleared, then a स_रखो(...,0,...) should be added to
	 *        the console_init
	 */

/* lookup table क्रम matching device nodes to index numbers */
अटल काष्ठा device_node *mpc52xx_uart_nodes[MPC52xx_PSC_MAXNUM];

अटल व्योम mpc52xx_uart_of_क्रमागतerate(व्योम);


#घोषणा PSC(port) ((काष्ठा mpc52xx_psc __iomem *)((port)->membase))


/* Forward declaration of the पूर्णांकerruption handling routine */
अटल irqवापस_t mpc52xx_uart_पूर्णांक(पूर्णांक irq, व्योम *dev_id);
अटल irqवापस_t mpc5xxx_uart_process_पूर्णांक(काष्ठा uart_port *port);

/* ======================================================================== */
/* PSC fअगरo operations क्रम isolating dअगरferences between 52xx and 512x      */
/* ======================================================================== */

काष्ठा psc_ops अणु
	व्योम		(*fअगरo_init)(काष्ठा uart_port *port);
	पूर्णांक		(*raw_rx_rdy)(काष्ठा uart_port *port);
	पूर्णांक		(*raw_tx_rdy)(काष्ठा uart_port *port);
	पूर्णांक		(*rx_rdy)(काष्ठा uart_port *port);
	पूर्णांक		(*tx_rdy)(काष्ठा uart_port *port);
	पूर्णांक		(*tx_empty)(काष्ठा uart_port *port);
	व्योम		(*stop_rx)(काष्ठा uart_port *port);
	व्योम		(*start_tx)(काष्ठा uart_port *port);
	व्योम		(*stop_tx)(काष्ठा uart_port *port);
	व्योम		(*rx_clr_irq)(काष्ठा uart_port *port);
	व्योम		(*tx_clr_irq)(काष्ठा uart_port *port);
	व्योम		(*ग_लिखो_अक्षर)(काष्ठा uart_port *port, अचिन्हित अक्षर c);
	अचिन्हित अक्षर	(*पढ़ो_अक्षर)(काष्ठा uart_port *port);
	व्योम		(*cw_disable_पूर्णांकs)(काष्ठा uart_port *port);
	व्योम		(*cw_restore_पूर्णांकs)(काष्ठा uart_port *port);
	अचिन्हित पूर्णांक	(*set_baudrate)(काष्ठा uart_port *port,
					काष्ठा ktermios *new,
					काष्ठा ktermios *old);
	पूर्णांक		(*घड़ी_alloc)(काष्ठा uart_port *port);
	व्योम		(*घड़ी_rअन्यथा)(काष्ठा uart_port *port);
	पूर्णांक		(*घड़ी)(काष्ठा uart_port *port, पूर्णांक enable);
	पूर्णांक		(*fअगरoc_init)(व्योम);
	व्योम		(*fअगरoc_uninit)(व्योम);
	व्योम		(*get_irq)(काष्ठा uart_port *, काष्ठा device_node *);
	irqवापस_t	(*handle_irq)(काष्ठा uart_port *port);
	u16		(*get_status)(काष्ठा uart_port *port);
	u8		(*get_ipcr)(काष्ठा uart_port *port);
	व्योम		(*command)(काष्ठा uart_port *port, u8 cmd);
	व्योम		(*set_mode)(काष्ठा uart_port *port, u8 mr1, u8 mr2);
	व्योम		(*set_rts)(काष्ठा uart_port *port, पूर्णांक state);
	व्योम		(*enable_ms)(काष्ठा uart_port *port);
	व्योम		(*set_sicr)(काष्ठा uart_port *port, u32 val);
	व्योम		(*set_imr)(काष्ठा uart_port *port, u16 val);
	u8		(*get_mr1)(काष्ठा uart_port *port);
पूर्ण;

/* setting the prescaler and भागisor reg is common क्रम all chips */
अटल अंतरभूत व्योम mpc52xx_set_भागisor(काष्ठा mpc52xx_psc __iomem *psc,
				       u16 prescaler, अचिन्हित पूर्णांक भागisor)
अणु
	/* select prescaler */
	out_be16(&psc->mpc52xx_psc_घड़ी_select, prescaler);
	out_8(&psc->ctur, भागisor >> 8);
	out_8(&psc->ctlr, भागisor & 0xff);
पूर्ण

अटल u16 mpc52xx_psc_get_status(काष्ठा uart_port *port)
अणु
	वापस in_be16(&PSC(port)->mpc52xx_psc_status);
पूर्ण

अटल u8 mpc52xx_psc_get_ipcr(काष्ठा uart_port *port)
अणु
	वापस in_8(&PSC(port)->mpc52xx_psc_ipcr);
पूर्ण

अटल व्योम mpc52xx_psc_command(काष्ठा uart_port *port, u8 cmd)
अणु
	out_8(&PSC(port)->command, cmd);
पूर्ण

अटल व्योम mpc52xx_psc_set_mode(काष्ठा uart_port *port, u8 mr1, u8 mr2)
अणु
	out_8(&PSC(port)->command, MPC52xx_PSC_SEL_MODE_REG_1);
	out_8(&PSC(port)->mode, mr1);
	out_8(&PSC(port)->mode, mr2);
पूर्ण

अटल व्योम mpc52xx_psc_set_rts(काष्ठा uart_port *port, पूर्णांक state)
अणु
	अगर (state)
		out_8(&PSC(port)->op1, MPC52xx_PSC_OP_RTS);
	अन्यथा
		out_8(&PSC(port)->op0, MPC52xx_PSC_OP_RTS);
पूर्ण

अटल व्योम mpc52xx_psc_enable_ms(काष्ठा uart_port *port)
अणु
	काष्ठा mpc52xx_psc __iomem *psc = PSC(port);

	/* clear D_*-bits by पढ़ोing them */
	in_8(&psc->mpc52xx_psc_ipcr);
	/* enable CTS and DCD as IPC पूर्णांकerrupts */
	out_8(&psc->mpc52xx_psc_acr, MPC52xx_PSC_IEC_CTS | MPC52xx_PSC_IEC_DCD);

	port->पढ़ो_status_mask |= MPC52xx_PSC_IMR_IPC;
	out_be16(&psc->mpc52xx_psc_imr, port->पढ़ो_status_mask);
पूर्ण

अटल व्योम mpc52xx_psc_set_sicr(काष्ठा uart_port *port, u32 val)
अणु
	out_be32(&PSC(port)->sicr, val);
पूर्ण

अटल व्योम mpc52xx_psc_set_imr(काष्ठा uart_port *port, u16 val)
अणु
	out_be16(&PSC(port)->mpc52xx_psc_imr, val);
पूर्ण

अटल u8 mpc52xx_psc_get_mr1(काष्ठा uart_port *port)
अणु
	out_8(&PSC(port)->command, MPC52xx_PSC_SEL_MODE_REG_1);
	वापस in_8(&PSC(port)->mode);
पूर्ण

#अगर_घोषित CONFIG_PPC_MPC52xx
#घोषणा FIFO_52xx(port) ((काष्ठा mpc52xx_psc_fअगरo __iomem *)(PSC(port)+1))
अटल व्योम mpc52xx_psc_fअगरo_init(काष्ठा uart_port *port)
अणु
	काष्ठा mpc52xx_psc __iomem *psc = PSC(port);
	काष्ठा mpc52xx_psc_fअगरo __iomem *fअगरo = FIFO_52xx(port);

	out_8(&fअगरo->rfcntl, 0x00);
	out_be16(&fअगरo->rfalarm, 0x1ff);
	out_8(&fअगरo->tfcntl, 0x07);
	out_be16(&fअगरo->tfalarm, 0x80);

	port->पढ़ो_status_mask |= MPC52xx_PSC_IMR_RXRDY | MPC52xx_PSC_IMR_TXRDY;
	out_be16(&psc->mpc52xx_psc_imr, port->पढ़ो_status_mask);
पूर्ण

अटल पूर्णांक mpc52xx_psc_raw_rx_rdy(काष्ठा uart_port *port)
अणु
	वापस in_be16(&PSC(port)->mpc52xx_psc_status)
	    & MPC52xx_PSC_SR_RXRDY;
पूर्ण

अटल पूर्णांक mpc52xx_psc_raw_tx_rdy(काष्ठा uart_port *port)
अणु
	वापस in_be16(&PSC(port)->mpc52xx_psc_status)
	    & MPC52xx_PSC_SR_TXRDY;
पूर्ण


अटल पूर्णांक mpc52xx_psc_rx_rdy(काष्ठा uart_port *port)
अणु
	वापस in_be16(&PSC(port)->mpc52xx_psc_isr)
	    & port->पढ़ो_status_mask
	    & MPC52xx_PSC_IMR_RXRDY;
पूर्ण

अटल पूर्णांक mpc52xx_psc_tx_rdy(काष्ठा uart_port *port)
अणु
	वापस in_be16(&PSC(port)->mpc52xx_psc_isr)
	    & port->पढ़ो_status_mask
	    & MPC52xx_PSC_IMR_TXRDY;
पूर्ण

अटल पूर्णांक mpc52xx_psc_tx_empty(काष्ठा uart_port *port)
अणु
	u16 sts = in_be16(&PSC(port)->mpc52xx_psc_status);

	वापस (sts & MPC52xx_PSC_SR_TXEMP) ? TIOCSER_TEMT : 0;
पूर्ण

अटल व्योम mpc52xx_psc_start_tx(काष्ठा uart_port *port)
अणु
	port->पढ़ो_status_mask |= MPC52xx_PSC_IMR_TXRDY;
	out_be16(&PSC(port)->mpc52xx_psc_imr, port->पढ़ो_status_mask);
पूर्ण

अटल व्योम mpc52xx_psc_stop_tx(काष्ठा uart_port *port)
अणु
	port->पढ़ो_status_mask &= ~MPC52xx_PSC_IMR_TXRDY;
	out_be16(&PSC(port)->mpc52xx_psc_imr, port->पढ़ो_status_mask);
पूर्ण

अटल व्योम mpc52xx_psc_stop_rx(काष्ठा uart_port *port)
अणु
	port->पढ़ो_status_mask &= ~MPC52xx_PSC_IMR_RXRDY;
	out_be16(&PSC(port)->mpc52xx_psc_imr, port->पढ़ो_status_mask);
पूर्ण

अटल व्योम mpc52xx_psc_rx_clr_irq(काष्ठा uart_port *port)
अणु
पूर्ण

अटल व्योम mpc52xx_psc_tx_clr_irq(काष्ठा uart_port *port)
अणु
पूर्ण

अटल व्योम mpc52xx_psc_ग_लिखो_अक्षर(काष्ठा uart_port *port, अचिन्हित अक्षर c)
अणु
	out_8(&PSC(port)->mpc52xx_psc_buffer_8, c);
पूर्ण

अटल अचिन्हित अक्षर mpc52xx_psc_पढ़ो_अक्षर(काष्ठा uart_port *port)
अणु
	वापस in_8(&PSC(port)->mpc52xx_psc_buffer_8);
पूर्ण

अटल व्योम mpc52xx_psc_cw_disable_पूर्णांकs(काष्ठा uart_port *port)
अणु
	out_be16(&PSC(port)->mpc52xx_psc_imr, 0);
पूर्ण

अटल व्योम mpc52xx_psc_cw_restore_पूर्णांकs(काष्ठा uart_port *port)
अणु
	out_be16(&PSC(port)->mpc52xx_psc_imr, port->पढ़ो_status_mask);
पूर्ण

अटल अचिन्हित पूर्णांक mpc5200_psc_set_baudrate(काष्ठा uart_port *port,
					     काष्ठा ktermios *new,
					     काष्ठा ktermios *old)
अणु
	अचिन्हित पूर्णांक baud;
	अचिन्हित पूर्णांक भागisor;

	/* The 5200 has a fixed /32 prescaler, uartclk contains the ipb freq */
	baud = uart_get_baud_rate(port, new, old,
				  port->uartclk / (32 * 0xffff) + 1,
				  port->uartclk / 32);
	भागisor = (port->uartclk + 16 * baud) / (32 * baud);

	/* enable the /32 prescaler and set the भागisor */
	mpc52xx_set_भागisor(PSC(port), 0xdd00, भागisor);
	वापस baud;
पूर्ण

अटल अचिन्हित पूर्णांक mpc5200b_psc_set_baudrate(काष्ठा uart_port *port,
					      काष्ठा ktermios *new,
					      काष्ठा ktermios *old)
अणु
	अचिन्हित पूर्णांक baud;
	अचिन्हित पूर्णांक भागisor;
	u16 prescaler;

	/* The 5200B has a selectable /4 or /32 prescaler, uartclk contains the
	 * ipb freq */
	baud = uart_get_baud_rate(port, new, old,
				  port->uartclk / (32 * 0xffff) + 1,
				  port->uartclk / 4);
	भागisor = (port->uartclk + 2 * baud) / (4 * baud);

	/* select the proper prescaler and set the भागisor
	 * prefer high prescaler क्रम more tolerance on low baudrates */
	अगर (भागisor > 0xffff || baud <= 115200) अणु
		भागisor = (भागisor + 4) / 8;
		prescaler = 0xdd00; /* /32 */
	पूर्ण अन्यथा
		prescaler = 0xff00; /* /4 */
	mpc52xx_set_भागisor(PSC(port), prescaler, भागisor);
	वापस baud;
पूर्ण

अटल व्योम mpc52xx_psc_get_irq(काष्ठा uart_port *port, काष्ठा device_node *np)
अणु
	port->irqflags = 0;
	port->irq = irq_of_parse_and_map(np, 0);
पूर्ण

/* 52xx specअगरic पूर्णांकerrupt handler. The caller holds the port lock */
अटल irqवापस_t mpc52xx_psc_handle_irq(काष्ठा uart_port *port)
अणु
	वापस mpc5xxx_uart_process_पूर्णांक(port);
पूर्ण

अटल स्थिर काष्ठा psc_ops mpc52xx_psc_ops = अणु
	.fअगरo_init = mpc52xx_psc_fअगरo_init,
	.raw_rx_rdy = mpc52xx_psc_raw_rx_rdy,
	.raw_tx_rdy = mpc52xx_psc_raw_tx_rdy,
	.rx_rdy = mpc52xx_psc_rx_rdy,
	.tx_rdy = mpc52xx_psc_tx_rdy,
	.tx_empty = mpc52xx_psc_tx_empty,
	.stop_rx = mpc52xx_psc_stop_rx,
	.start_tx = mpc52xx_psc_start_tx,
	.stop_tx = mpc52xx_psc_stop_tx,
	.rx_clr_irq = mpc52xx_psc_rx_clr_irq,
	.tx_clr_irq = mpc52xx_psc_tx_clr_irq,
	.ग_लिखो_अक्षर = mpc52xx_psc_ग_लिखो_अक्षर,
	.पढ़ो_अक्षर = mpc52xx_psc_पढ़ो_अक्षर,
	.cw_disable_पूर्णांकs = mpc52xx_psc_cw_disable_पूर्णांकs,
	.cw_restore_पूर्णांकs = mpc52xx_psc_cw_restore_पूर्णांकs,
	.set_baudrate = mpc5200_psc_set_baudrate,
	.get_irq = mpc52xx_psc_get_irq,
	.handle_irq = mpc52xx_psc_handle_irq,
	.get_status = mpc52xx_psc_get_status,
	.get_ipcr = mpc52xx_psc_get_ipcr,
	.command = mpc52xx_psc_command,
	.set_mode = mpc52xx_psc_set_mode,
	.set_rts = mpc52xx_psc_set_rts,
	.enable_ms = mpc52xx_psc_enable_ms,
	.set_sicr = mpc52xx_psc_set_sicr,
	.set_imr = mpc52xx_psc_set_imr,
	.get_mr1 = mpc52xx_psc_get_mr1,
पूर्ण;

अटल स्थिर काष्ठा psc_ops mpc5200b_psc_ops = अणु
	.fअगरo_init = mpc52xx_psc_fअगरo_init,
	.raw_rx_rdy = mpc52xx_psc_raw_rx_rdy,
	.raw_tx_rdy = mpc52xx_psc_raw_tx_rdy,
	.rx_rdy = mpc52xx_psc_rx_rdy,
	.tx_rdy = mpc52xx_psc_tx_rdy,
	.tx_empty = mpc52xx_psc_tx_empty,
	.stop_rx = mpc52xx_psc_stop_rx,
	.start_tx = mpc52xx_psc_start_tx,
	.stop_tx = mpc52xx_psc_stop_tx,
	.rx_clr_irq = mpc52xx_psc_rx_clr_irq,
	.tx_clr_irq = mpc52xx_psc_tx_clr_irq,
	.ग_लिखो_अक्षर = mpc52xx_psc_ग_लिखो_अक्षर,
	.पढ़ो_अक्षर = mpc52xx_psc_पढ़ो_अक्षर,
	.cw_disable_पूर्णांकs = mpc52xx_psc_cw_disable_पूर्णांकs,
	.cw_restore_पूर्णांकs = mpc52xx_psc_cw_restore_पूर्णांकs,
	.set_baudrate = mpc5200b_psc_set_baudrate,
	.get_irq = mpc52xx_psc_get_irq,
	.handle_irq = mpc52xx_psc_handle_irq,
	.get_status = mpc52xx_psc_get_status,
	.get_ipcr = mpc52xx_psc_get_ipcr,
	.command = mpc52xx_psc_command,
	.set_mode = mpc52xx_psc_set_mode,
	.set_rts = mpc52xx_psc_set_rts,
	.enable_ms = mpc52xx_psc_enable_ms,
	.set_sicr = mpc52xx_psc_set_sicr,
	.set_imr = mpc52xx_psc_set_imr,
	.get_mr1 = mpc52xx_psc_get_mr1,
पूर्ण;

#पूर्ण_अगर /* CONFIG_PPC_MPC52xx */

#अगर_घोषित CONFIG_PPC_MPC512x
#घोषणा FIFO_512x(port) ((काष्ठा mpc512x_psc_fअगरo __iomem *)(PSC(port)+1))

/* PSC FIFO Controller क्रम mpc512x */
काष्ठा psc_fअगरoc अणु
	u32 fअगरoc_cmd;
	u32 fअगरoc_पूर्णांक;
	u32 fअगरoc_dma;
	u32 fअगरoc_axe;
	u32 fअगरoc_debug;
पूर्ण;

अटल काष्ठा psc_fअगरoc __iomem *psc_fअगरoc;
अटल अचिन्हित पूर्णांक psc_fअगरoc_irq;
अटल काष्ठा clk *psc_fअगरoc_clk;

अटल व्योम mpc512x_psc_fअगरo_init(काष्ठा uart_port *port)
अणु
	/* /32 prescaler */
	out_be16(&PSC(port)->mpc52xx_psc_घड़ी_select, 0xdd00);

	out_be32(&FIFO_512x(port)->txcmd, MPC512x_PSC_FIFO_RESET_SLICE);
	out_be32(&FIFO_512x(port)->txcmd, MPC512x_PSC_FIFO_ENABLE_SLICE);
	out_be32(&FIFO_512x(port)->txalarm, 1);
	out_be32(&FIFO_512x(port)->tximr, 0);

	out_be32(&FIFO_512x(port)->rxcmd, MPC512x_PSC_FIFO_RESET_SLICE);
	out_be32(&FIFO_512x(port)->rxcmd, MPC512x_PSC_FIFO_ENABLE_SLICE);
	out_be32(&FIFO_512x(port)->rxalarm, 1);
	out_be32(&FIFO_512x(port)->rximr, 0);

	out_be32(&FIFO_512x(port)->tximr, MPC512x_PSC_FIFO_ALARM);
	out_be32(&FIFO_512x(port)->rximr, MPC512x_PSC_FIFO_ALARM);
पूर्ण

अटल पूर्णांक mpc512x_psc_raw_rx_rdy(काष्ठा uart_port *port)
अणु
	वापस !(in_be32(&FIFO_512x(port)->rxsr) & MPC512x_PSC_FIFO_EMPTY);
पूर्ण

अटल पूर्णांक mpc512x_psc_raw_tx_rdy(काष्ठा uart_port *port)
अणु
	वापस !(in_be32(&FIFO_512x(port)->txsr) & MPC512x_PSC_FIFO_FULL);
पूर्ण

अटल पूर्णांक mpc512x_psc_rx_rdy(काष्ठा uart_port *port)
अणु
	वापस in_be32(&FIFO_512x(port)->rxsr)
	    & in_be32(&FIFO_512x(port)->rximr)
	    & MPC512x_PSC_FIFO_ALARM;
पूर्ण

अटल पूर्णांक mpc512x_psc_tx_rdy(काष्ठा uart_port *port)
अणु
	वापस in_be32(&FIFO_512x(port)->txsr)
	    & in_be32(&FIFO_512x(port)->tximr)
	    & MPC512x_PSC_FIFO_ALARM;
पूर्ण

अटल पूर्णांक mpc512x_psc_tx_empty(काष्ठा uart_port *port)
अणु
	वापस in_be32(&FIFO_512x(port)->txsr)
	    & MPC512x_PSC_FIFO_EMPTY;
पूर्ण

अटल व्योम mpc512x_psc_stop_rx(काष्ठा uart_port *port)
अणु
	अचिन्हित दीर्घ rx_fअगरo_imr;

	rx_fअगरo_imr = in_be32(&FIFO_512x(port)->rximr);
	rx_fअगरo_imr &= ~MPC512x_PSC_FIFO_ALARM;
	out_be32(&FIFO_512x(port)->rximr, rx_fअगरo_imr);
पूर्ण

अटल व्योम mpc512x_psc_start_tx(काष्ठा uart_port *port)
अणु
	अचिन्हित दीर्घ tx_fअगरo_imr;

	tx_fअगरo_imr = in_be32(&FIFO_512x(port)->tximr);
	tx_fअगरo_imr |= MPC512x_PSC_FIFO_ALARM;
	out_be32(&FIFO_512x(port)->tximr, tx_fअगरo_imr);
पूर्ण

अटल व्योम mpc512x_psc_stop_tx(काष्ठा uart_port *port)
अणु
	अचिन्हित दीर्घ tx_fअगरo_imr;

	tx_fअगरo_imr = in_be32(&FIFO_512x(port)->tximr);
	tx_fअगरo_imr &= ~MPC512x_PSC_FIFO_ALARM;
	out_be32(&FIFO_512x(port)->tximr, tx_fअगरo_imr);
पूर्ण

अटल व्योम mpc512x_psc_rx_clr_irq(काष्ठा uart_port *port)
अणु
	out_be32(&FIFO_512x(port)->rxisr, in_be32(&FIFO_512x(port)->rxisr));
पूर्ण

अटल व्योम mpc512x_psc_tx_clr_irq(काष्ठा uart_port *port)
अणु
	out_be32(&FIFO_512x(port)->txisr, in_be32(&FIFO_512x(port)->txisr));
पूर्ण

अटल व्योम mpc512x_psc_ग_लिखो_अक्षर(काष्ठा uart_port *port, अचिन्हित अक्षर c)
अणु
	out_8(&FIFO_512x(port)->txdata_8, c);
पूर्ण

अटल अचिन्हित अक्षर mpc512x_psc_पढ़ो_अक्षर(काष्ठा uart_port *port)
अणु
	वापस in_8(&FIFO_512x(port)->rxdata_8);
पूर्ण

अटल व्योम mpc512x_psc_cw_disable_पूर्णांकs(काष्ठा uart_port *port)
अणु
	port->पढ़ो_status_mask =
		in_be32(&FIFO_512x(port)->tximr) << 16 |
		in_be32(&FIFO_512x(port)->rximr);
	out_be32(&FIFO_512x(port)->tximr, 0);
	out_be32(&FIFO_512x(port)->rximr, 0);
पूर्ण

अटल व्योम mpc512x_psc_cw_restore_पूर्णांकs(काष्ठा uart_port *port)
अणु
	out_be32(&FIFO_512x(port)->tximr,
		(port->पढ़ो_status_mask >> 16) & 0x7f);
	out_be32(&FIFO_512x(port)->rximr, port->पढ़ो_status_mask & 0x7f);
पूर्ण

अटल अचिन्हित पूर्णांक mpc512x_psc_set_baudrate(काष्ठा uart_port *port,
					     काष्ठा ktermios *new,
					     काष्ठा ktermios *old)
अणु
	अचिन्हित पूर्णांक baud;
	अचिन्हित पूर्णांक भागisor;

	/*
	 * The "MPC5121e Microcontroller Reference Manual, Rev. 3" says on
	 * pg. 30-10 that the chip supports a /32 and a /10 prescaler.
	 * Furthermore, it states that "After reset, the prescaler by 10
	 * क्रम the UART mode is selected", but the reset रेजिस्टर value is
	 * 0x0000 which means a /32 prescaler. This is wrong.
	 *
	 * In reality using /32 prescaler करोesn't work, as it is not supported!
	 * Use /16 or /10 prescaler, see "MPC5121e Hardware Design Guide",
	 * Chapter 4.1 PSC in UART Mode.
	 * Calculate with a /16 prescaler here.
	 */

	/* uartclk contains the ips freq */
	baud = uart_get_baud_rate(port, new, old,
				  port->uartclk / (16 * 0xffff) + 1,
				  port->uartclk / 16);
	भागisor = (port->uartclk + 8 * baud) / (16 * baud);

	/* enable the /16 prescaler and set the भागisor */
	mpc52xx_set_भागisor(PSC(port), 0xdd00, भागisor);
	वापस baud;
पूर्ण

/* Init PSC FIFO Controller */
अटल पूर्णांक __init mpc512x_psc_fअगरoc_init(व्योम)
अणु
	पूर्णांक err;
	काष्ठा device_node *np;
	काष्ठा clk *clk;

	/* शेष error code, potentially overwritten by घड़ी calls */
	err = -ENODEV;

	np = of_find_compatible_node(शून्य, शून्य,
				     "fsl,mpc5121-psc-fifo");
	अगर (!np) अणु
		pr_err("%s: Can't find FIFOC node\n", __func__);
		जाओ out_err;
	पूर्ण

	clk = of_clk_get(np, 0);
	अगर (IS_ERR(clk)) अणु
		/* backwards compat with device trees that lack घड़ी specs */
		clk = clk_get_sys(np->name, "ipg");
	पूर्ण
	अगर (IS_ERR(clk)) अणु
		pr_err("%s: Can't lookup FIFO clock\n", __func__);
		err = PTR_ERR(clk);
		जाओ out_ofnode_put;
	पूर्ण
	अगर (clk_prepare_enable(clk)) अणु
		pr_err("%s: Can't enable FIFO clock\n", __func__);
		clk_put(clk);
		जाओ out_ofnode_put;
	पूर्ण
	psc_fअगरoc_clk = clk;

	psc_fअगरoc = of_iomap(np, 0);
	अगर (!psc_fअगरoc) अणु
		pr_err("%s: Can't map FIFOC\n", __func__);
		जाओ out_clk_disable;
	पूर्ण

	psc_fअगरoc_irq = irq_of_parse_and_map(np, 0);
	अगर (psc_fअगरoc_irq == 0) अणु
		pr_err("%s: Can't get FIFOC irq\n", __func__);
		जाओ out_unmap;
	पूर्ण

	of_node_put(np);
	वापस 0;

out_unmap:
	iounmap(psc_fअगरoc);
out_clk_disable:
	clk_disable_unprepare(psc_fअगरoc_clk);
	clk_put(psc_fअगरoc_clk);
out_ofnode_put:
	of_node_put(np);
out_err:
	वापस err;
पूर्ण

अटल व्योम __निकास mpc512x_psc_fअगरoc_uninit(व्योम)
अणु
	iounmap(psc_fअगरoc);

	/* disable the घड़ी, errors are not fatal */
	अगर (psc_fअगरoc_clk) अणु
		clk_disable_unprepare(psc_fअगरoc_clk);
		clk_put(psc_fअगरoc_clk);
		psc_fअगरoc_clk = शून्य;
	पूर्ण
पूर्ण

/* 512x specअगरic पूर्णांकerrupt handler. The caller holds the port lock */
अटल irqवापस_t mpc512x_psc_handle_irq(काष्ठा uart_port *port)
अणु
	अचिन्हित दीर्घ fअगरoc_पूर्णांक;
	पूर्णांक psc_num;

	/* Read pending PSC FIFOC पूर्णांकerrupts */
	fअगरoc_पूर्णांक = in_be32(&psc_fअगरoc->fअगरoc_पूर्णांक);

	/* Check अगर it is an पूर्णांकerrupt क्रम this port */
	psc_num = (port->mapbase & 0xf00) >> 8;
	अगर (test_bit(psc_num, &fअगरoc_पूर्णांक) ||
	    test_bit(psc_num + 16, &fअगरoc_पूर्णांक))
		वापस mpc5xxx_uart_process_पूर्णांक(port);

	वापस IRQ_NONE;
पूर्ण

अटल काष्ठा clk *psc_mclk_clk[MPC52xx_PSC_MAXNUM];
अटल काष्ठा clk *psc_ipg_clk[MPC52xx_PSC_MAXNUM];

/* called from within the .request_port() callback (allocation) */
अटल पूर्णांक mpc512x_psc_alloc_घड़ी(काष्ठा uart_port *port)
अणु
	पूर्णांक psc_num;
	काष्ठा clk *clk;
	पूर्णांक err;

	psc_num = (port->mapbase & 0xf00) >> 8;

	clk = devm_clk_get(port->dev, "mclk");
	अगर (IS_ERR(clk)) अणु
		dev_err(port->dev, "Failed to get MCLK!\n");
		err = PTR_ERR(clk);
		जाओ out_err;
	पूर्ण
	err = clk_prepare_enable(clk);
	अगर (err) अणु
		dev_err(port->dev, "Failed to enable MCLK!\n");
		जाओ out_err;
	पूर्ण
	psc_mclk_clk[psc_num] = clk;

	clk = devm_clk_get(port->dev, "ipg");
	अगर (IS_ERR(clk)) अणु
		dev_err(port->dev, "Failed to get IPG clock!\n");
		err = PTR_ERR(clk);
		जाओ out_err;
	पूर्ण
	err = clk_prepare_enable(clk);
	अगर (err) अणु
		dev_err(port->dev, "Failed to enable IPG clock!\n");
		जाओ out_err;
	पूर्ण
	psc_ipg_clk[psc_num] = clk;

	वापस 0;

out_err:
	अगर (psc_mclk_clk[psc_num]) अणु
		clk_disable_unprepare(psc_mclk_clk[psc_num]);
		psc_mclk_clk[psc_num] = शून्य;
	पूर्ण
	अगर (psc_ipg_clk[psc_num]) अणु
		clk_disable_unprepare(psc_ipg_clk[psc_num]);
		psc_ipg_clk[psc_num] = शून्य;
	पूर्ण
	वापस err;
पूर्ण

/* called from within the .release_port() callback (release) */
अटल व्योम mpc512x_psc_rअन्यथा_घड़ी(काष्ठा uart_port *port)
अणु
	पूर्णांक psc_num;
	काष्ठा clk *clk;

	psc_num = (port->mapbase & 0xf00) >> 8;
	clk = psc_mclk_clk[psc_num];
	अगर (clk) अणु
		clk_disable_unprepare(clk);
		psc_mclk_clk[psc_num] = शून्य;
	पूर्ण
	अगर (psc_ipg_clk[psc_num]) अणु
		clk_disable_unprepare(psc_ipg_clk[psc_num]);
		psc_ipg_clk[psc_num] = शून्य;
	पूर्ण
पूर्ण

/* implementation of the .घड़ी() callback (enable/disable) */
अटल पूर्णांक mpc512x_psc_endis_घड़ी(काष्ठा uart_port *port, पूर्णांक enable)
अणु
	पूर्णांक psc_num;
	काष्ठा clk *psc_clk;
	पूर्णांक ret;

	अगर (uart_console(port))
		वापस 0;

	psc_num = (port->mapbase & 0xf00) >> 8;
	psc_clk = psc_mclk_clk[psc_num];
	अगर (!psc_clk) अणु
		dev_err(port->dev, "Failed to get PSC clock entry!\n");
		वापस -ENODEV;
	पूर्ण

	dev_dbg(port->dev, "mclk %sable\n", enable ? "en" : "dis");
	अगर (enable) अणु
		ret = clk_enable(psc_clk);
		अगर (ret)
			dev_err(port->dev, "Failed to enable MCLK!\n");
		वापस ret;
	पूर्ण अन्यथा अणु
		clk_disable(psc_clk);
		वापस 0;
	पूर्ण
पूर्ण

अटल व्योम mpc512x_psc_get_irq(काष्ठा uart_port *port, काष्ठा device_node *np)
अणु
	port->irqflags = IRQF_SHARED;
	port->irq = psc_fअगरoc_irq;
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_PPC_MPC512x

#घोषणा PSC_5125(port) ((काष्ठा mpc5125_psc __iomem *)((port)->membase))
#घोषणा FIFO_5125(port) ((काष्ठा mpc512x_psc_fअगरo __iomem *)(PSC_5125(port)+1))

अटल व्योम mpc5125_psc_fअगरo_init(काष्ठा uart_port *port)
अणु
	/* /32 prescaler */
	out_8(&PSC_5125(port)->mpc52xx_psc_घड़ी_select, 0xdd);

	out_be32(&FIFO_5125(port)->txcmd, MPC512x_PSC_FIFO_RESET_SLICE);
	out_be32(&FIFO_5125(port)->txcmd, MPC512x_PSC_FIFO_ENABLE_SLICE);
	out_be32(&FIFO_5125(port)->txalarm, 1);
	out_be32(&FIFO_5125(port)->tximr, 0);

	out_be32(&FIFO_5125(port)->rxcmd, MPC512x_PSC_FIFO_RESET_SLICE);
	out_be32(&FIFO_5125(port)->rxcmd, MPC512x_PSC_FIFO_ENABLE_SLICE);
	out_be32(&FIFO_5125(port)->rxalarm, 1);
	out_be32(&FIFO_5125(port)->rximr, 0);

	out_be32(&FIFO_5125(port)->tximr, MPC512x_PSC_FIFO_ALARM);
	out_be32(&FIFO_5125(port)->rximr, MPC512x_PSC_FIFO_ALARM);
पूर्ण

अटल पूर्णांक mpc5125_psc_raw_rx_rdy(काष्ठा uart_port *port)
अणु
	वापस !(in_be32(&FIFO_5125(port)->rxsr) & MPC512x_PSC_FIFO_EMPTY);
पूर्ण

अटल पूर्णांक mpc5125_psc_raw_tx_rdy(काष्ठा uart_port *port)
अणु
	वापस !(in_be32(&FIFO_5125(port)->txsr) & MPC512x_PSC_FIFO_FULL);
पूर्ण

अटल पूर्णांक mpc5125_psc_rx_rdy(काष्ठा uart_port *port)
अणु
	वापस in_be32(&FIFO_5125(port)->rxsr) &
	       in_be32(&FIFO_5125(port)->rximr) & MPC512x_PSC_FIFO_ALARM;
पूर्ण

अटल पूर्णांक mpc5125_psc_tx_rdy(काष्ठा uart_port *port)
अणु
	वापस in_be32(&FIFO_5125(port)->txsr) &
	       in_be32(&FIFO_5125(port)->tximr) & MPC512x_PSC_FIFO_ALARM;
पूर्ण

अटल पूर्णांक mpc5125_psc_tx_empty(काष्ठा uart_port *port)
अणु
	वापस in_be32(&FIFO_5125(port)->txsr) & MPC512x_PSC_FIFO_EMPTY;
पूर्ण

अटल व्योम mpc5125_psc_stop_rx(काष्ठा uart_port *port)
अणु
	अचिन्हित दीर्घ rx_fअगरo_imr;

	rx_fअगरo_imr = in_be32(&FIFO_5125(port)->rximr);
	rx_fअगरo_imr &= ~MPC512x_PSC_FIFO_ALARM;
	out_be32(&FIFO_5125(port)->rximr, rx_fअगरo_imr);
पूर्ण

अटल व्योम mpc5125_psc_start_tx(काष्ठा uart_port *port)
अणु
	अचिन्हित दीर्घ tx_fअगरo_imr;

	tx_fअगरo_imr = in_be32(&FIFO_5125(port)->tximr);
	tx_fअगरo_imr |= MPC512x_PSC_FIFO_ALARM;
	out_be32(&FIFO_5125(port)->tximr, tx_fअगरo_imr);
पूर्ण

अटल व्योम mpc5125_psc_stop_tx(काष्ठा uart_port *port)
अणु
	अचिन्हित दीर्घ tx_fअगरo_imr;

	tx_fअगरo_imr = in_be32(&FIFO_5125(port)->tximr);
	tx_fअगरo_imr &= ~MPC512x_PSC_FIFO_ALARM;
	out_be32(&FIFO_5125(port)->tximr, tx_fअगरo_imr);
पूर्ण

अटल व्योम mpc5125_psc_rx_clr_irq(काष्ठा uart_port *port)
अणु
	out_be32(&FIFO_5125(port)->rxisr, in_be32(&FIFO_5125(port)->rxisr));
पूर्ण

अटल व्योम mpc5125_psc_tx_clr_irq(काष्ठा uart_port *port)
अणु
	out_be32(&FIFO_5125(port)->txisr, in_be32(&FIFO_5125(port)->txisr));
पूर्ण

अटल व्योम mpc5125_psc_ग_लिखो_अक्षर(काष्ठा uart_port *port, अचिन्हित अक्षर c)
अणु
	out_8(&FIFO_5125(port)->txdata_8, c);
पूर्ण

अटल अचिन्हित अक्षर mpc5125_psc_पढ़ो_अक्षर(काष्ठा uart_port *port)
अणु
	वापस in_8(&FIFO_5125(port)->rxdata_8);
पूर्ण

अटल व्योम mpc5125_psc_cw_disable_पूर्णांकs(काष्ठा uart_port *port)
अणु
	port->पढ़ो_status_mask =
		in_be32(&FIFO_5125(port)->tximr) << 16 |
		in_be32(&FIFO_5125(port)->rximr);
	out_be32(&FIFO_5125(port)->tximr, 0);
	out_be32(&FIFO_5125(port)->rximr, 0);
पूर्ण

अटल व्योम mpc5125_psc_cw_restore_पूर्णांकs(काष्ठा uart_port *port)
अणु
	out_be32(&FIFO_5125(port)->tximr,
		(port->पढ़ो_status_mask >> 16) & 0x7f);
	out_be32(&FIFO_5125(port)->rximr, port->पढ़ो_status_mask & 0x7f);
पूर्ण

अटल अंतरभूत व्योम mpc5125_set_भागisor(काष्ठा mpc5125_psc __iomem *psc,
		u8 prescaler, अचिन्हित पूर्णांक भागisor)
अणु
	/* select prescaler */
	out_8(&psc->mpc52xx_psc_घड़ी_select, prescaler);
	out_8(&psc->ctur, भागisor >> 8);
	out_8(&psc->ctlr, भागisor & 0xff);
पूर्ण

अटल अचिन्हित पूर्णांक mpc5125_psc_set_baudrate(काष्ठा uart_port *port,
					     काष्ठा ktermios *new,
					     काष्ठा ktermios *old)
अणु
	अचिन्हित पूर्णांक baud;
	अचिन्हित पूर्णांक भागisor;

	/*
	 * Calculate with a /16 prescaler here.
	 */

	/* uartclk contains the ips freq */
	baud = uart_get_baud_rate(port, new, old,
				  port->uartclk / (16 * 0xffff) + 1,
				  port->uartclk / 16);
	भागisor = (port->uartclk + 8 * baud) / (16 * baud);

	/* enable the /16 prescaler and set the भागisor */
	mpc5125_set_भागisor(PSC_5125(port), 0xdd, भागisor);
	वापस baud;
पूर्ण

/*
 * MPC5125 have compatible PSC FIFO Controller.
 * Special init not needed.
 */
अटल u16 mpc5125_psc_get_status(काष्ठा uart_port *port)
अणु
	वापस in_be16(&PSC_5125(port)->mpc52xx_psc_status);
पूर्ण

अटल u8 mpc5125_psc_get_ipcr(काष्ठा uart_port *port)
अणु
	वापस in_8(&PSC_5125(port)->mpc52xx_psc_ipcr);
पूर्ण

अटल व्योम mpc5125_psc_command(काष्ठा uart_port *port, u8 cmd)
अणु
	out_8(&PSC_5125(port)->command, cmd);
पूर्ण

अटल व्योम mpc5125_psc_set_mode(काष्ठा uart_port *port, u8 mr1, u8 mr2)
अणु
	out_8(&PSC_5125(port)->mr1, mr1);
	out_8(&PSC_5125(port)->mr2, mr2);
पूर्ण

अटल व्योम mpc5125_psc_set_rts(काष्ठा uart_port *port, पूर्णांक state)
अणु
	अगर (state & TIOCM_RTS)
		out_8(&PSC_5125(port)->op1, MPC52xx_PSC_OP_RTS);
	अन्यथा
		out_8(&PSC_5125(port)->op0, MPC52xx_PSC_OP_RTS);
पूर्ण

अटल व्योम mpc5125_psc_enable_ms(काष्ठा uart_port *port)
अणु
	काष्ठा mpc5125_psc __iomem *psc = PSC_5125(port);

	/* clear D_*-bits by पढ़ोing them */
	in_8(&psc->mpc52xx_psc_ipcr);
	/* enable CTS and DCD as IPC पूर्णांकerrupts */
	out_8(&psc->mpc52xx_psc_acr, MPC52xx_PSC_IEC_CTS | MPC52xx_PSC_IEC_DCD);

	port->पढ़ो_status_mask |= MPC52xx_PSC_IMR_IPC;
	out_be16(&psc->mpc52xx_psc_imr, port->पढ़ो_status_mask);
पूर्ण

अटल व्योम mpc5125_psc_set_sicr(काष्ठा uart_port *port, u32 val)
अणु
	out_be32(&PSC_5125(port)->sicr, val);
पूर्ण

अटल व्योम mpc5125_psc_set_imr(काष्ठा uart_port *port, u16 val)
अणु
	out_be16(&PSC_5125(port)->mpc52xx_psc_imr, val);
पूर्ण

अटल u8 mpc5125_psc_get_mr1(काष्ठा uart_port *port)
अणु
	वापस in_8(&PSC_5125(port)->mr1);
पूर्ण

अटल स्थिर काष्ठा psc_ops mpc5125_psc_ops = अणु
	.fअगरo_init = mpc5125_psc_fअगरo_init,
	.raw_rx_rdy = mpc5125_psc_raw_rx_rdy,
	.raw_tx_rdy = mpc5125_psc_raw_tx_rdy,
	.rx_rdy = mpc5125_psc_rx_rdy,
	.tx_rdy = mpc5125_psc_tx_rdy,
	.tx_empty = mpc5125_psc_tx_empty,
	.stop_rx = mpc5125_psc_stop_rx,
	.start_tx = mpc5125_psc_start_tx,
	.stop_tx = mpc5125_psc_stop_tx,
	.rx_clr_irq = mpc5125_psc_rx_clr_irq,
	.tx_clr_irq = mpc5125_psc_tx_clr_irq,
	.ग_लिखो_अक्षर = mpc5125_psc_ग_लिखो_अक्षर,
	.पढ़ो_अक्षर = mpc5125_psc_पढ़ो_अक्षर,
	.cw_disable_पूर्णांकs = mpc5125_psc_cw_disable_पूर्णांकs,
	.cw_restore_पूर्णांकs = mpc5125_psc_cw_restore_पूर्णांकs,
	.set_baudrate = mpc5125_psc_set_baudrate,
	.घड़ी_alloc = mpc512x_psc_alloc_घड़ी,
	.घड़ी_rअन्यथा = mpc512x_psc_rअन्यथा_घड़ी,
	.घड़ी = mpc512x_psc_endis_घड़ी,
	.fअगरoc_init = mpc512x_psc_fअगरoc_init,
	.fअगरoc_uninit = mpc512x_psc_fअगरoc_uninit,
	.get_irq = mpc512x_psc_get_irq,
	.handle_irq = mpc512x_psc_handle_irq,
	.get_status = mpc5125_psc_get_status,
	.get_ipcr = mpc5125_psc_get_ipcr,
	.command = mpc5125_psc_command,
	.set_mode = mpc5125_psc_set_mode,
	.set_rts = mpc5125_psc_set_rts,
	.enable_ms = mpc5125_psc_enable_ms,
	.set_sicr = mpc5125_psc_set_sicr,
	.set_imr = mpc5125_psc_set_imr,
	.get_mr1 = mpc5125_psc_get_mr1,
पूर्ण;

अटल स्थिर काष्ठा psc_ops mpc512x_psc_ops = अणु
	.fअगरo_init = mpc512x_psc_fअगरo_init,
	.raw_rx_rdy = mpc512x_psc_raw_rx_rdy,
	.raw_tx_rdy = mpc512x_psc_raw_tx_rdy,
	.rx_rdy = mpc512x_psc_rx_rdy,
	.tx_rdy = mpc512x_psc_tx_rdy,
	.tx_empty = mpc512x_psc_tx_empty,
	.stop_rx = mpc512x_psc_stop_rx,
	.start_tx = mpc512x_psc_start_tx,
	.stop_tx = mpc512x_psc_stop_tx,
	.rx_clr_irq = mpc512x_psc_rx_clr_irq,
	.tx_clr_irq = mpc512x_psc_tx_clr_irq,
	.ग_लिखो_अक्षर = mpc512x_psc_ग_लिखो_अक्षर,
	.पढ़ो_अक्षर = mpc512x_psc_पढ़ो_अक्षर,
	.cw_disable_पूर्णांकs = mpc512x_psc_cw_disable_पूर्णांकs,
	.cw_restore_पूर्णांकs = mpc512x_psc_cw_restore_पूर्णांकs,
	.set_baudrate = mpc512x_psc_set_baudrate,
	.घड़ी_alloc = mpc512x_psc_alloc_घड़ी,
	.घड़ी_rअन्यथा = mpc512x_psc_rअन्यथा_घड़ी,
	.घड़ी = mpc512x_psc_endis_घड़ी,
	.fअगरoc_init = mpc512x_psc_fअगरoc_init,
	.fअगरoc_uninit = mpc512x_psc_fअगरoc_uninit,
	.get_irq = mpc512x_psc_get_irq,
	.handle_irq = mpc512x_psc_handle_irq,
	.get_status = mpc52xx_psc_get_status,
	.get_ipcr = mpc52xx_psc_get_ipcr,
	.command = mpc52xx_psc_command,
	.set_mode = mpc52xx_psc_set_mode,
	.set_rts = mpc52xx_psc_set_rts,
	.enable_ms = mpc52xx_psc_enable_ms,
	.set_sicr = mpc52xx_psc_set_sicr,
	.set_imr = mpc52xx_psc_set_imr,
	.get_mr1 = mpc52xx_psc_get_mr1,
पूर्ण;
#पूर्ण_अगर /* CONFIG_PPC_MPC512x */


अटल स्थिर काष्ठा psc_ops *psc_ops;

/* ======================================================================== */
/* UART operations                                                          */
/* ======================================================================== */

अटल अचिन्हित पूर्णांक
mpc52xx_uart_tx_empty(काष्ठा uart_port *port)
अणु
	वापस psc_ops->tx_empty(port) ? TIOCSER_TEMT : 0;
पूर्ण

अटल व्योम
mpc52xx_uart_set_mctrl(काष्ठा uart_port *port, अचिन्हित पूर्णांक mctrl)
अणु
	psc_ops->set_rts(port, mctrl & TIOCM_RTS);
पूर्ण

अटल अचिन्हित पूर्णांक
mpc52xx_uart_get_mctrl(काष्ठा uart_port *port)
अणु
	अचिन्हित पूर्णांक ret = TIOCM_DSR;
	u8 status = psc_ops->get_ipcr(port);

	अगर (!(status & MPC52xx_PSC_CTS))
		ret |= TIOCM_CTS;
	अगर (!(status & MPC52xx_PSC_DCD))
		ret |= TIOCM_CAR;

	वापस ret;
पूर्ण

अटल व्योम
mpc52xx_uart_stop_tx(काष्ठा uart_port *port)
अणु
	/* port->lock taken by caller */
	psc_ops->stop_tx(port);
पूर्ण

अटल व्योम
mpc52xx_uart_start_tx(काष्ठा uart_port *port)
अणु
	/* port->lock taken by caller */
	psc_ops->start_tx(port);
पूर्ण

अटल व्योम
mpc52xx_uart_stop_rx(काष्ठा uart_port *port)
अणु
	/* port->lock taken by caller */
	psc_ops->stop_rx(port);
पूर्ण

अटल व्योम
mpc52xx_uart_enable_ms(काष्ठा uart_port *port)
अणु
	psc_ops->enable_ms(port);
पूर्ण

अटल व्योम
mpc52xx_uart_अवरोध_ctl(काष्ठा uart_port *port, पूर्णांक ctl)
अणु
	अचिन्हित दीर्घ flags;
	spin_lock_irqsave(&port->lock, flags);

	अगर (ctl == -1)
		psc_ops->command(port, MPC52xx_PSC_START_BRK);
	अन्यथा
		psc_ops->command(port, MPC52xx_PSC_STOP_BRK);

	spin_unlock_irqrestore(&port->lock, flags);
पूर्ण

अटल पूर्णांक
mpc52xx_uart_startup(काष्ठा uart_port *port)
अणु
	पूर्णांक ret;

	अगर (psc_ops->घड़ी) अणु
		ret = psc_ops->घड़ी(port, 1);
		अगर (ret)
			वापस ret;
	पूर्ण

	/* Request IRQ */
	ret = request_irq(port->irq, mpc52xx_uart_पूर्णांक,
			  port->irqflags, "mpc52xx_psc_uart", port);
	अगर (ret)
		वापस ret;

	/* Reset/activate the port, clear and enable पूर्णांकerrupts */
	psc_ops->command(port, MPC52xx_PSC_RST_RX);
	psc_ops->command(port, MPC52xx_PSC_RST_TX);

	/*
	 * According to Freescale's support the RST_TX command can produce a
	 * spike on the TX pin. So they recommend to delay "for one character".
	 * One millisecond should be enough क्रम everyone.
	 */
	msleep(1);

	psc_ops->set_sicr(port, 0);	/* UART mode DCD ignored */

	psc_ops->fअगरo_init(port);

	psc_ops->command(port, MPC52xx_PSC_TX_ENABLE);
	psc_ops->command(port, MPC52xx_PSC_RX_ENABLE);

	वापस 0;
पूर्ण

अटल व्योम
mpc52xx_uart_shutकरोwn(काष्ठा uart_port *port)
अणु
	/* Shut करोwn the port.  Leave TX active अगर on a console port */
	psc_ops->command(port, MPC52xx_PSC_RST_RX);
	अगर (!uart_console(port))
		psc_ops->command(port, MPC52xx_PSC_RST_TX);

	port->पढ़ो_status_mask = 0;
	psc_ops->set_imr(port, port->पढ़ो_status_mask);

	अगर (psc_ops->घड़ी)
		psc_ops->घड़ी(port, 0);

	/* Disable पूर्णांकerrupt */
	psc_ops->cw_disable_पूर्णांकs(port);

	/* Release पूर्णांकerrupt */
	मुक्त_irq(port->irq, port);
पूर्ण

अटल व्योम
mpc52xx_uart_set_termios(काष्ठा uart_port *port, काष्ठा ktermios *new,
			 काष्ठा ktermios *old)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित अक्षर mr1, mr2;
	अचिन्हित पूर्णांक j;
	अचिन्हित पूर्णांक baud;

	/* Prepare what we're gonna ग_लिखो */
	mr1 = 0;

	चयन (new->c_cflag & CSIZE) अणु
	हाल CS5:	mr1 |= MPC52xx_PSC_MODE_5_BITS;
		अवरोध;
	हाल CS6:	mr1 |= MPC52xx_PSC_MODE_6_BITS;
		अवरोध;
	हाल CS7:	mr1 |= MPC52xx_PSC_MODE_7_BITS;
		अवरोध;
	हाल CS8:
	शेष:	mr1 |= MPC52xx_PSC_MODE_8_BITS;
	पूर्ण

	अगर (new->c_cflag & PARENB) अणु
		अगर (new->c_cflag & CMSPAR)
			mr1 |= MPC52xx_PSC_MODE_PARFORCE;

		/* With CMSPAR, PARODD also means high parity (same as termios) */
		mr1 |= (new->c_cflag & PARODD) ?
			MPC52xx_PSC_MODE_PARODD : MPC52xx_PSC_MODE_PAREVEN;
	पूर्ण अन्यथा अणु
		mr1 |= MPC52xx_PSC_MODE_PARNONE;
	पूर्ण

	mr2 = 0;

	अगर (new->c_cflag & CSTOPB)
		mr2 |= MPC52xx_PSC_MODE_TWO_STOP;
	अन्यथा
		mr2 |= ((new->c_cflag & CSIZE) == CS5) ?
			MPC52xx_PSC_MODE_ONE_STOP_5_BITS :
			MPC52xx_PSC_MODE_ONE_STOP;

	अगर (new->c_cflag & CRTSCTS) अणु
		mr1 |= MPC52xx_PSC_MODE_RXRTS;
		mr2 |= MPC52xx_PSC_MODE_TXCTS;
	पूर्ण

	/* Get the lock */
	spin_lock_irqsave(&port->lock, flags);

	/* Do our best to flush TX & RX, so we करोn't lose anything */
	/* But we करोn't रुको indefinitely ! */
	j = 5000000;	/* Maximum रुको */
	/* FIXME Can't receive अक्षरs since set_termios might be called at early
	 * boot क्रम the console, all stuff is not yet पढ़ोy to receive at that
	 * समय and that just makes the kernel oops */
	/* जबतक (j-- && mpc52xx_uart_पूर्णांक_rx_अक्षरs(port)); */
	जबतक (!mpc52xx_uart_tx_empty(port) && --j)
		udelay(1);

	अगर (!j)
		prपूर्णांकk(KERN_ERR "mpc52xx_uart.c: "
			"Unable to flush RX & TX fifos in-time in set_termios."
			"Some chars may have been lost.\n");

	/* Reset the TX & RX */
	psc_ops->command(port, MPC52xx_PSC_RST_RX);
	psc_ops->command(port, MPC52xx_PSC_RST_TX);

	/* Send new mode settings */
	psc_ops->set_mode(port, mr1, mr2);
	baud = psc_ops->set_baudrate(port, new, old);

	/* Update the per-port समयout */
	uart_update_समयout(port, new->c_cflag, baud);

	अगर (UART_ENABLE_MS(port, new->c_cflag))
		mpc52xx_uart_enable_ms(port);

	/* Reenable TX & RX */
	psc_ops->command(port, MPC52xx_PSC_TX_ENABLE);
	psc_ops->command(port, MPC52xx_PSC_RX_ENABLE);

	/* We're all set, release the lock */
	spin_unlock_irqrestore(&port->lock, flags);
पूर्ण

अटल स्थिर अक्षर *
mpc52xx_uart_type(काष्ठा uart_port *port)
अणु
	/*
	 * We keep using PORT_MPC52xx क्रम historic reasons although it applies
	 * क्रम MPC512x, too, but prपूर्णांक "MPC5xxx" to not irritate users
	 */
	वापस port->type == PORT_MPC52xx ? "MPC5xxx PSC" : शून्य;
पूर्ण

अटल व्योम
mpc52xx_uart_release_port(काष्ठा uart_port *port)
अणु
	अगर (psc_ops->घड़ी_rअन्यथा)
		psc_ops->घड़ी_rअन्यथा(port);

	/* remapped by us ? */
	अगर (port->flags & UPF_IOREMAP) अणु
		iounmap(port->membase);
		port->membase = शून्य;
	पूर्ण

	release_mem_region(port->mapbase, माप(काष्ठा mpc52xx_psc));
पूर्ण

अटल पूर्णांक
mpc52xx_uart_request_port(काष्ठा uart_port *port)
अणु
	पूर्णांक err;

	अगर (port->flags & UPF_IOREMAP) /* Need to remap ? */
		port->membase = ioremap(port->mapbase,
					माप(काष्ठा mpc52xx_psc));

	अगर (!port->membase)
		वापस -EINVAL;

	err = request_mem_region(port->mapbase, माप(काष्ठा mpc52xx_psc),
			"mpc52xx_psc_uart") != शून्य ? 0 : -EBUSY;

	अगर (err)
		जाओ out_membase;

	अगर (psc_ops->घड़ी_alloc) अणु
		err = psc_ops->घड़ी_alloc(port);
		अगर (err)
			जाओ out_mapregion;
	पूर्ण

	वापस 0;

out_mapregion:
	release_mem_region(port->mapbase, माप(काष्ठा mpc52xx_psc));
out_membase:
	अगर (port->flags & UPF_IOREMAP) अणु
		iounmap(port->membase);
		port->membase = शून्य;
	पूर्ण
	वापस err;
पूर्ण

अटल व्योम
mpc52xx_uart_config_port(काष्ठा uart_port *port, पूर्णांक flags)
अणु
	अगर ((flags & UART_CONFIG_TYPE)
		&& (mpc52xx_uart_request_port(port) == 0))
		port->type = PORT_MPC52xx;
पूर्ण

अटल पूर्णांक
mpc52xx_uart_verअगरy_port(काष्ठा uart_port *port, काष्ठा serial_काष्ठा *ser)
अणु
	अगर (ser->type != PORT_UNKNOWN && ser->type != PORT_MPC52xx)
		वापस -EINVAL;

	अगर ((ser->irq != port->irq) ||
	    (ser->io_type != UPIO_MEM) ||
	    (ser->baud_base != port->uartclk)  ||
	    (ser->iomem_base != (व्योम *)port->mapbase) ||
	    (ser->hub6 != 0))
		वापस -EINVAL;

	वापस 0;
पूर्ण


अटल स्थिर काष्ठा uart_ops mpc52xx_uart_ops = अणु
	.tx_empty	= mpc52xx_uart_tx_empty,
	.set_mctrl	= mpc52xx_uart_set_mctrl,
	.get_mctrl	= mpc52xx_uart_get_mctrl,
	.stop_tx	= mpc52xx_uart_stop_tx,
	.start_tx	= mpc52xx_uart_start_tx,
	.stop_rx	= mpc52xx_uart_stop_rx,
	.enable_ms	= mpc52xx_uart_enable_ms,
	.अवरोध_ctl	= mpc52xx_uart_अवरोध_ctl,
	.startup	= mpc52xx_uart_startup,
	.shutकरोwn	= mpc52xx_uart_shutकरोwn,
	.set_termios	= mpc52xx_uart_set_termios,
/*	.pm		= mpc52xx_uart_pm,		Not supported yet */
	.type		= mpc52xx_uart_type,
	.release_port	= mpc52xx_uart_release_port,
	.request_port	= mpc52xx_uart_request_port,
	.config_port	= mpc52xx_uart_config_port,
	.verअगरy_port	= mpc52xx_uart_verअगरy_port
पूर्ण;


/* ======================================================================== */
/* Interrupt handling                                                       */
/* ======================================================================== */

अटल अंतरभूत पूर्णांक
mpc52xx_uart_पूर्णांक_rx_अक्षरs(काष्ठा uart_port *port)
अणु
	काष्ठा tty_port *tport = &port->state->port;
	अचिन्हित अक्षर ch, flag;
	अचिन्हित लघु status;

	/* While we can पढ़ो, करो so ! */
	जबतक (psc_ops->raw_rx_rdy(port)) अणु
		/* Get the अक्षर */
		ch = psc_ops->पढ़ो_अक्षर(port);

		/* Handle sysreq अक्षर */
		अगर (uart_handle_sysrq_अक्षर(port, ch))
			जारी;

		/* Store it */

		flag = TTY_NORMAL;
		port->icount.rx++;

		status = psc_ops->get_status(port);

		अगर (status & (MPC52xx_PSC_SR_PE |
			      MPC52xx_PSC_SR_FE |
			      MPC52xx_PSC_SR_RB)) अणु

			अगर (status & MPC52xx_PSC_SR_RB) अणु
				flag = TTY_BREAK;
				uart_handle_अवरोध(port);
				port->icount.brk++;
			पूर्ण अन्यथा अगर (status & MPC52xx_PSC_SR_PE) अणु
				flag = TTY_PARITY;
				port->icount.parity++;
			पूर्ण
			अन्यथा अगर (status & MPC52xx_PSC_SR_FE) अणु
				flag = TTY_FRAME;
				port->icount.frame++;
			पूर्ण

			/* Clear error condition */
			psc_ops->command(port, MPC52xx_PSC_RST_ERR_STAT);

		पूर्ण
		tty_insert_flip_अक्षर(tport, ch, flag);
		अगर (status & MPC52xx_PSC_SR_OE) अणु
			/*
			 * Overrun is special, since it's
			 * reported immediately, and करोesn't
			 * affect the current अक्षरacter
			 */
			tty_insert_flip_अक्षर(tport, 0, TTY_OVERRUN);
			port->icount.overrun++;
		पूर्ण
	पूर्ण

	tty_flip_buffer_push(tport);

	वापस psc_ops->raw_rx_rdy(port);
पूर्ण

अटल अंतरभूत पूर्णांक
mpc52xx_uart_पूर्णांक_tx_अक्षरs(काष्ठा uart_port *port)
अणु
	काष्ठा circ_buf *xmit = &port->state->xmit;

	/* Process out of band अक्षरs */
	अगर (port->x_अक्षर) अणु
		psc_ops->ग_लिखो_अक्षर(port, port->x_अक्षर);
		port->icount.tx++;
		port->x_अक्षर = 0;
		वापस 1;
	पूर्ण

	/* Nothing to करो ? */
	अगर (uart_circ_empty(xmit) || uart_tx_stopped(port)) अणु
		mpc52xx_uart_stop_tx(port);
		वापस 0;
	पूर्ण

	/* Send अक्षरs */
	जबतक (psc_ops->raw_tx_rdy(port)) अणु
		psc_ops->ग_लिखो_अक्षर(port, xmit->buf[xmit->tail]);
		xmit->tail = (xmit->tail + 1) & (UART_XMIT_SIZE - 1);
		port->icount.tx++;
		अगर (uart_circ_empty(xmit))
			अवरोध;
	पूर्ण

	/* Wake up */
	अगर (uart_circ_अक्षरs_pending(xmit) < WAKEUP_CHARS)
		uart_ग_लिखो_wakeup(port);

	/* Maybe we're करोne after all */
	अगर (uart_circ_empty(xmit)) अणु
		mpc52xx_uart_stop_tx(port);
		वापस 0;
	पूर्ण

	वापस 1;
पूर्ण

अटल irqवापस_t
mpc5xxx_uart_process_पूर्णांक(काष्ठा uart_port *port)
अणु
	अचिन्हित दीर्घ pass = ISR_PASS_LIMIT;
	अचिन्हित पूर्णांक keepgoing;
	u8 status;

	/* While we have stuff to करो, we जारी */
	करो अणु
		/* If we करोn't find anything to करो, we stop */
		keepgoing = 0;

		psc_ops->rx_clr_irq(port);
		अगर (psc_ops->rx_rdy(port))
			keepgoing |= mpc52xx_uart_पूर्णांक_rx_अक्षरs(port);

		psc_ops->tx_clr_irq(port);
		अगर (psc_ops->tx_rdy(port))
			keepgoing |= mpc52xx_uart_पूर्णांक_tx_अक्षरs(port);

		status = psc_ops->get_ipcr(port);
		अगर (status & MPC52xx_PSC_D_DCD)
			uart_handle_dcd_change(port, !(status & MPC52xx_PSC_DCD));

		अगर (status & MPC52xx_PSC_D_CTS)
			uart_handle_cts_change(port, !(status & MPC52xx_PSC_CTS));

		/* Limit number of iteration */
		अगर (!(--pass))
			keepgoing = 0;

	पूर्ण जबतक (keepgoing);

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t
mpc52xx_uart_पूर्णांक(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा uart_port *port = dev_id;
	irqवापस_t ret;

	spin_lock(&port->lock);

	ret = psc_ops->handle_irq(port);

	spin_unlock(&port->lock);

	वापस ret;
पूर्ण

/* ======================================================================== */
/* Console ( अगर applicable )                                                */
/* ======================================================================== */

#अगर_घोषित CONFIG_SERIAL_MPC52xx_CONSOLE

अटल व्योम __init
mpc52xx_console_get_options(काष्ठा uart_port *port,
			    पूर्णांक *baud, पूर्णांक *parity, पूर्णांक *bits, पूर्णांक *flow)
अणु
	अचिन्हित अक्षर mr1;

	pr_debug("mpc52xx_console_get_options(port=%p)\n", port);

	/* Read the mode रेजिस्टरs */
	mr1 = psc_ops->get_mr1(port);

	/* CTअणुU,Lपूर्णR are ग_लिखो-only ! */
	*baud = CONFIG_SERIAL_MPC52xx_CONSOLE_BAUD;

	/* Parse them */
	चयन (mr1 & MPC52xx_PSC_MODE_BITS_MASK) अणु
	हाल MPC52xx_PSC_MODE_5_BITS:
		*bits = 5;
		अवरोध;
	हाल MPC52xx_PSC_MODE_6_BITS:
		*bits = 6;
		अवरोध;
	हाल MPC52xx_PSC_MODE_7_BITS:
		*bits = 7;
		अवरोध;
	हाल MPC52xx_PSC_MODE_8_BITS:
	शेष:
		*bits = 8;
	पूर्ण

	अगर (mr1 & MPC52xx_PSC_MODE_PARNONE)
		*parity = 'n';
	अन्यथा
		*parity = mr1 & MPC52xx_PSC_MODE_PARODD ? 'o' : 'e';
पूर्ण

अटल व्योम
mpc52xx_console_ग_लिखो(काष्ठा console *co, स्थिर अक्षर *s, अचिन्हित पूर्णांक count)
अणु
	काष्ठा uart_port *port = &mpc52xx_uart_ports[co->index];
	अचिन्हित पूर्णांक i, j;

	/* Disable पूर्णांकerrupts */
	psc_ops->cw_disable_पूर्णांकs(port);

	/* Wait the TX buffer to be empty */
	j = 5000000;	/* Maximum रुको */
	जबतक (!mpc52xx_uart_tx_empty(port) && --j)
		udelay(1);

	/* Write all the अक्षरs */
	क्रम (i = 0; i < count; i++, s++) अणु
		/* Line वापस handling */
		अगर (*s == '\n')
			psc_ops->ग_लिखो_अक्षर(port, '\r');

		/* Send the अक्षर */
		psc_ops->ग_लिखो_अक्षर(port, *s);

		/* Wait the TX buffer to be empty */
		j = 20000;	/* Maximum रुको */
		जबतक (!mpc52xx_uart_tx_empty(port) && --j)
			udelay(1);
	पूर्ण

	/* Restore पूर्णांकerrupt state */
	psc_ops->cw_restore_पूर्णांकs(port);
पूर्ण


अटल पूर्णांक __init
mpc52xx_console_setup(काष्ठा console *co, अक्षर *options)
अणु
	काष्ठा uart_port *port = &mpc52xx_uart_ports[co->index];
	काष्ठा device_node *np = mpc52xx_uart_nodes[co->index];
	अचिन्हित पूर्णांक uartclk;
	काष्ठा resource res;
	पूर्णांक ret;

	पूर्णांक baud = CONFIG_SERIAL_MPC52xx_CONSOLE_BAUD;
	पूर्णांक bits = 8;
	पूर्णांक parity = 'n';
	पूर्णांक flow = 'n';

	pr_debug("mpc52xx_console_setup co=%p, co->index=%i, options=%s\n",
		 co, co->index, options);

	अगर ((co->index < 0) || (co->index >= MPC52xx_PSC_MAXNUM)) अणु
		pr_debug("PSC%x out of range\n", co->index);
		वापस -EINVAL;
	पूर्ण

	अगर (!np) अणु
		pr_debug("PSC%x not found in device tree\n", co->index);
		वापस -EINVAL;
	पूर्ण

	pr_debug("Console on ttyPSC%x is %pOF\n",
		 co->index, mpc52xx_uart_nodes[co->index]);

	/* Fetch रेजिस्टर locations */
	ret = of_address_to_resource(np, 0, &res);
	अगर (ret) अणु
		pr_debug("Could not get resources for PSC%x\n", co->index);
		वापस ret;
	पूर्ण

	uartclk = mpc5xxx_get_bus_frequency(np);
	अगर (uartclk == 0) अणु
		pr_debug("Could not find uart clock frequency!\n");
		वापस -EINVAL;
	पूर्ण

	/* Basic port init. Needed since we use some uart_??? func beक्रमe
	 * real init क्रम early access */
	spin_lock_init(&port->lock);
	port->uartclk = uartclk;
	port->ops	= &mpc52xx_uart_ops;
	port->mapbase = res.start;
	port->membase = ioremap(res.start, माप(काष्ठा mpc52xx_psc));
	port->irq = irq_of_parse_and_map(np, 0);

	अगर (port->membase == शून्य)
		वापस -EINVAL;

	pr_debug("mpc52xx-psc uart at %p, mapped to %p, irq=%x, freq=%i\n",
		 (व्योम *)port->mapbase, port->membase,
		 port->irq, port->uartclk);

	/* Setup the port parameters accoding to options */
	अगर (options)
		uart_parse_options(options, &baud, &parity, &bits, &flow);
	अन्यथा
		mpc52xx_console_get_options(port, &baud, &parity, &bits, &flow);

	pr_debug("Setting console parameters: %i %i%c1 flow=%c\n",
		 baud, bits, parity, flow);

	वापस uart_set_options(port, co, baud, parity, bits, flow);
पूर्ण


अटल काष्ठा uart_driver mpc52xx_uart_driver;

अटल काष्ठा console mpc52xx_console = अणु
	.name	= "ttyPSC",
	.ग_लिखो	= mpc52xx_console_ग_लिखो,
	.device	= uart_console_device,
	.setup	= mpc52xx_console_setup,
	.flags	= CON_PRINTBUFFER,
	.index	= -1,	/* Specअगरied on the cmdline (e.g. console=ttyPSC0) */
	.data	= &mpc52xx_uart_driver,
पूर्ण;


अटल पूर्णांक __init
mpc52xx_console_init(व्योम)
अणु
	mpc52xx_uart_of_क्रमागतerate();
	रेजिस्टर_console(&mpc52xx_console);
	वापस 0;
पूर्ण

console_initcall(mpc52xx_console_init);

#घोषणा MPC52xx_PSC_CONSOLE &mpc52xx_console
#अन्यथा
#घोषणा MPC52xx_PSC_CONSOLE शून्य
#पूर्ण_अगर


/* ======================================================================== */
/* UART Driver                                                              */
/* ======================================================================== */

अटल काष्ठा uart_driver mpc52xx_uart_driver = अणु
	.driver_name	= "mpc52xx_psc_uart",
	.dev_name	= "ttyPSC",
	.major		= SERIAL_PSC_MAJOR,
	.minor		= SERIAL_PSC_MINOR,
	.nr		= MPC52xx_PSC_MAXNUM,
	.cons		= MPC52xx_PSC_CONSOLE,
पूर्ण;

/* ======================================================================== */
/* OF Platक्रमm Driver                                                       */
/* ======================================================================== */

अटल स्थिर काष्ठा of_device_id mpc52xx_uart_of_match[] = अणु
#अगर_घोषित CONFIG_PPC_MPC52xx
	अणु .compatible = "fsl,mpc5200b-psc-uart", .data = &mpc5200b_psc_ops, पूर्ण,
	अणु .compatible = "fsl,mpc5200-psc-uart", .data = &mpc52xx_psc_ops, पूर्ण,
	/* binding used by old lite5200 device trees: */
	अणु .compatible = "mpc5200-psc-uart", .data = &mpc52xx_psc_ops, पूर्ण,
	/* binding used by efika: */
	अणु .compatible = "mpc5200-serial", .data = &mpc52xx_psc_ops, पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_PPC_MPC512x
	अणु .compatible = "fsl,mpc5121-psc-uart", .data = &mpc512x_psc_ops, पूर्ण,
	अणु .compatible = "fsl,mpc5125-psc-uart", .data = &mpc5125_psc_ops, पूर्ण,
#पूर्ण_अगर
	अणुपूर्ण,
पूर्ण;

अटल पूर्णांक mpc52xx_uart_of_probe(काष्ठा platक्रमm_device *op)
अणु
	पूर्णांक idx = -1;
	अचिन्हित पूर्णांक uartclk;
	काष्ठा uart_port *port = शून्य;
	काष्ठा resource res;
	पूर्णांक ret;

	/* Check validity & presence */
	क्रम (idx = 0; idx < MPC52xx_PSC_MAXNUM; idx++)
		अगर (mpc52xx_uart_nodes[idx] == op->dev.of_node)
			अवरोध;
	अगर (idx >= MPC52xx_PSC_MAXNUM)
		वापस -EINVAL;
	pr_debug("Found %pOF assigned to ttyPSC%x\n",
		 mpc52xx_uart_nodes[idx], idx);

	/* set the uart घड़ी to the input घड़ी of the psc, the dअगरferent
	 * prescalers are taken पूर्णांकo account in the set_baudrate() methods
	 * of the respective chip */
	uartclk = mpc5xxx_get_bus_frequency(op->dev.of_node);
	अगर (uartclk == 0) अणु
		dev_dbg(&op->dev, "Could not find uart clock frequency!\n");
		वापस -EINVAL;
	पूर्ण

	/* Init the port काष्ठाure */
	port = &mpc52xx_uart_ports[idx];

	spin_lock_init(&port->lock);
	port->uartclk = uartclk;
	port->fअगरosize	= 512;
	port->has_sysrq = IS_ENABLED(CONFIG_SERIAL_MPC52xx_CONSOLE);
	port->iotype	= UPIO_MEM;
	port->flags	= UPF_BOOT_AUTOCONF |
			  (uart_console(port) ? 0 : UPF_IOREMAP);
	port->line	= idx;
	port->ops	= &mpc52xx_uart_ops;
	port->dev	= &op->dev;

	/* Search क्रम IRQ and mapbase */
	ret = of_address_to_resource(op->dev.of_node, 0, &res);
	अगर (ret)
		वापस ret;

	port->mapbase = res.start;
	अगर (!port->mapbase) अणु
		dev_dbg(&op->dev, "Could not allocate resources for PSC\n");
		वापस -EINVAL;
	पूर्ण

	psc_ops->get_irq(port, op->dev.of_node);
	अगर (port->irq == 0) अणु
		dev_dbg(&op->dev, "Could not get irq\n");
		वापस -EINVAL;
	पूर्ण

	dev_dbg(&op->dev, "mpc52xx-psc uart at %p, irq=%x, freq=%i\n",
		(व्योम *)port->mapbase, port->irq, port->uartclk);

	/* Add the port to the uart sub-प्रणाली */
	ret = uart_add_one_port(&mpc52xx_uart_driver, port);
	अगर (ret)
		वापस ret;

	platक्रमm_set_drvdata(op, (व्योम *)port);
	वापस 0;
पूर्ण

अटल पूर्णांक
mpc52xx_uart_of_हटाओ(काष्ठा platक्रमm_device *op)
अणु
	काष्ठा uart_port *port = platक्रमm_get_drvdata(op);

	अगर (port)
		uart_हटाओ_one_port(&mpc52xx_uart_driver, port);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक
mpc52xx_uart_of_suspend(काष्ठा platक्रमm_device *op, pm_message_t state)
अणु
	काष्ठा uart_port *port = platक्रमm_get_drvdata(op);

	अगर (port)
		uart_suspend_port(&mpc52xx_uart_driver, port);

	वापस 0;
पूर्ण

अटल पूर्णांक
mpc52xx_uart_of_resume(काष्ठा platक्रमm_device *op)
अणु
	काष्ठा uart_port *port = platक्रमm_get_drvdata(op);

	अगर (port)
		uart_resume_port(&mpc52xx_uart_driver, port);

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल व्योम
mpc52xx_uart_of_assign(काष्ठा device_node *np)
अणु
	पूर्णांक i;

	/* Find the first मुक्त PSC number */
	क्रम (i = 0; i < MPC52xx_PSC_MAXNUM; i++) अणु
		अगर (mpc52xx_uart_nodes[i] == शून्य) अणु
			of_node_get(np);
			mpc52xx_uart_nodes[i] = np;
			वापस;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम
mpc52xx_uart_of_क्रमागतerate(व्योम)
अणु
	अटल पूर्णांक क्रमागत_करोne;
	काष्ठा device_node *np;
	स्थिर काष्ठा  of_device_id *match;
	पूर्णांक i;

	अगर (क्रमागत_करोne)
		वापस;

	/* Assign index to each PSC in device tree */
	क्रम_each_matching_node(np, mpc52xx_uart_of_match) अणु
		match = of_match_node(mpc52xx_uart_of_match, np);
		psc_ops = match->data;
		mpc52xx_uart_of_assign(np);
	पूर्ण

	क्रमागत_करोne = 1;

	क्रम (i = 0; i < MPC52xx_PSC_MAXNUM; i++) अणु
		अगर (mpc52xx_uart_nodes[i])
			pr_debug("%pOF assigned to ttyPSC%x\n",
				 mpc52xx_uart_nodes[i], i);
	पूर्ण
पूर्ण

MODULE_DEVICE_TABLE(of, mpc52xx_uart_of_match);

अटल काष्ठा platक्रमm_driver mpc52xx_uart_of_driver = अणु
	.probe		= mpc52xx_uart_of_probe,
	.हटाओ		= mpc52xx_uart_of_हटाओ,
#अगर_घोषित CONFIG_PM
	.suspend	= mpc52xx_uart_of_suspend,
	.resume		= mpc52xx_uart_of_resume,
#पूर्ण_अगर
	.driver = अणु
		.name = "mpc52xx-psc-uart",
		.of_match_table = mpc52xx_uart_of_match,
	पूर्ण,
पूर्ण;


/* ======================================================================== */
/* Module                                                                   */
/* ======================================================================== */

अटल पूर्णांक __init
mpc52xx_uart_init(व्योम)
अणु
	पूर्णांक ret;

	prपूर्णांकk(KERN_INFO "Serial: MPC52xx PSC UART driver\n");

	ret = uart_रेजिस्टर_driver(&mpc52xx_uart_driver);
	अगर (ret) अणु
		prपूर्णांकk(KERN_ERR "%s: uart_register_driver failed (%i)\n",
		       __खाता__, ret);
		वापस ret;
	पूर्ण

	mpc52xx_uart_of_क्रमागतerate();

	/*
	 * Map the PSC FIFO Controller and init अगर on MPC512x.
	 */
	अगर (psc_ops && psc_ops->fअगरoc_init) अणु
		ret = psc_ops->fअगरoc_init();
		अगर (ret)
			जाओ err_init;
	पूर्ण

	ret = platक्रमm_driver_रेजिस्टर(&mpc52xx_uart_of_driver);
	अगर (ret) अणु
		prपूर्णांकk(KERN_ERR "%s: platform_driver_register failed (%i)\n",
		       __खाता__, ret);
		जाओ err_reg;
	पूर्ण

	वापस 0;
err_reg:
	अगर (psc_ops && psc_ops->fअगरoc_uninit)
		psc_ops->fअगरoc_uninit();
err_init:
	uart_unरेजिस्टर_driver(&mpc52xx_uart_driver);
	वापस ret;
पूर्ण

अटल व्योम __निकास
mpc52xx_uart_निकास(व्योम)
अणु
	अगर (psc_ops->fअगरoc_uninit)
		psc_ops->fअगरoc_uninit();

	platक्रमm_driver_unरेजिस्टर(&mpc52xx_uart_of_driver);
	uart_unरेजिस्टर_driver(&mpc52xx_uart_driver);
पूर्ण


module_init(mpc52xx_uart_init);
module_निकास(mpc52xx_uart_निकास);

MODULE_AUTHOR("Sylvain Munaut <tnt@246tNt.com>");
MODULE_DESCRIPTION("Freescale MPC52xx PSC UART");
MODULE_LICENSE("GPL");
