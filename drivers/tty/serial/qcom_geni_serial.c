<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (c) 2017-2018, The Linux foundation. All rights reserved.

#समावेश <linux/clk.h>
#समावेश <linux/console.h>
#समावेश <linux/पन.स>
#समावेश <linux/iopoll.h>
#समावेश <linux/irq.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/pm_opp.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/pm_wakeirq.h>
#समावेश <linux/qcom-geni-se.h>
#समावेश <linux/serial.h>
#समावेश <linux/serial_core.h>
#समावेश <linux/slab.h>
#समावेश <linux/tty.h>
#समावेश <linux/tty_flip.h>

/* UART specअगरic GENI रेजिस्टरs */
#घोषणा SE_UART_LOOPBACK_CFG		0x22c
#घोषणा SE_UART_IO_MACRO_CTRL		0x240
#घोषणा SE_UART_TX_TRANS_CFG		0x25c
#घोषणा SE_UART_TX_WORD_LEN		0x268
#घोषणा SE_UART_TX_STOP_BIT_LEN		0x26c
#घोषणा SE_UART_TX_TRANS_LEN		0x270
#घोषणा SE_UART_RX_TRANS_CFG		0x280
#घोषणा SE_UART_RX_WORD_LEN		0x28c
#घोषणा SE_UART_RX_STALE_CNT		0x294
#घोषणा SE_UART_TX_PARITY_CFG		0x2a4
#घोषणा SE_UART_RX_PARITY_CFG		0x2a8
#घोषणा SE_UART_MANUAL_RFR		0x2ac

/* SE_UART_TRANS_CFG */
#घोषणा UART_TX_PAR_EN		BIT(0)
#घोषणा UART_CTS_MASK		BIT(1)

/* SE_UART_TX_WORD_LEN */
#घोषणा TX_WORD_LEN_MSK		GENMASK(9, 0)

/* SE_UART_TX_STOP_BIT_LEN */
#घोषणा TX_STOP_BIT_LEN_MSK	GENMASK(23, 0)
#घोषणा TX_STOP_BIT_LEN_1	0
#घोषणा TX_STOP_BIT_LEN_1_5	1
#घोषणा TX_STOP_BIT_LEN_2	2

/* SE_UART_TX_TRANS_LEN */
#घोषणा TX_TRANS_LEN_MSK	GENMASK(23, 0)

/* SE_UART_RX_TRANS_CFG */
#घोषणा UART_RX_INS_STATUS_BIT	BIT(2)
#घोषणा UART_RX_PAR_EN		BIT(3)

/* SE_UART_RX_WORD_LEN */
#घोषणा RX_WORD_LEN_MASK	GENMASK(9, 0)

/* SE_UART_RX_STALE_CNT */
#घोषणा RX_STALE_CNT		GENMASK(23, 0)

/* SE_UART_TX_PARITY_CFG/RX_PARITY_CFG */
#घोषणा PAR_CALC_EN		BIT(0)
#घोषणा PAR_MODE_MSK		GENMASK(2, 1)
#घोषणा PAR_MODE_SHFT		1
#घोषणा PAR_EVEN		0x00
#घोषणा PAR_ODD			0x01
#घोषणा PAR_SPACE		0x10
#घोषणा PAR_MARK		0x11

/* SE_UART_MANUAL_RFR रेजिस्टर fields */
#घोषणा UART_MANUAL_RFR_EN	BIT(31)
#घोषणा UART_RFR_NOT_READY	BIT(1)
#घोषणा UART_RFR_READY		BIT(0)

/* UART M_CMD OP codes */
#घोषणा UART_START_TX		0x1
#घोषणा UART_START_BREAK	0x4
#घोषणा UART_STOP_BREAK		0x5
/* UART S_CMD OP codes */
#घोषणा UART_START_READ		0x1
#घोषणा UART_PARAM		0x1

#घोषणा UART_OVERSAMPLING	32
#घोषणा STALE_TIMEOUT		16
#घोषणा DEFAULT_BITS_PER_CHAR	10
#घोषणा GENI_UART_CONS_PORTS	1
#घोषणा GENI_UART_PORTS		3
#घोषणा DEF_FIFO_DEPTH_WORDS	16
#घोषणा DEF_TX_WM		2
#घोषणा DEF_FIFO_WIDTH_BITS	32
#घोषणा UART_RX_WM		2

/* SE_UART_LOOPBACK_CFG */
#घोषणा RX_TX_SORTED	BIT(0)
#घोषणा CTS_RTS_SORTED	BIT(1)
#घोषणा RX_TX_CTS_RTS_SORTED	(RX_TX_SORTED | CTS_RTS_SORTED)

/* UART pin swap value */
#घोषणा DEFAULT_IO_MACRO_IO0_IO1_MASK		GENMASK(3, 0)
#घोषणा IO_MACRO_IO0_SEL		0x3
#घोषणा DEFAULT_IO_MACRO_IO2_IO3_MASK		GENMASK(15, 4)
#घोषणा IO_MACRO_IO2_IO3_SWAP		0x4640

/* We always configure 4 bytes per FIFO word */
#घोषणा BYTES_PER_FIFO_WORD		4

काष्ठा qcom_geni_निजी_data अणु
	/* NOTE: earlycon port will have शून्य here */
	काष्ठा uart_driver *drv;

	u32 poll_cached_bytes;
	अचिन्हित पूर्णांक poll_cached_bytes_cnt;

	u32 ग_लिखो_cached_bytes;
	अचिन्हित पूर्णांक ग_लिखो_cached_bytes_cnt;
पूर्ण;

काष्ठा qcom_geni_serial_port अणु
	काष्ठा uart_port uport;
	काष्ठा geni_se se;
	स्थिर अक्षर *name;
	u32 tx_fअगरo_depth;
	u32 tx_fअगरo_width;
	u32 rx_fअगरo_depth;
	bool setup;
	पूर्णांक (*handle_rx)(काष्ठा uart_port *uport, u32 bytes, bool drop);
	अचिन्हित पूर्णांक baud;
	व्योम *rx_fअगरo;
	u32 loopback;
	bool brk;

	अचिन्हित पूर्णांक tx_reमुख्यing;
	पूर्णांक wakeup_irq;
	bool rx_tx_swap;
	bool cts_rts_swap;

	काष्ठा qcom_geni_निजी_data निजी_data;
पूर्ण;

अटल स्थिर काष्ठा uart_ops qcom_geni_console_pops;
अटल स्थिर काष्ठा uart_ops qcom_geni_uart_pops;
अटल काष्ठा uart_driver qcom_geni_console_driver;
अटल काष्ठा uart_driver qcom_geni_uart_driver;
अटल पूर्णांक handle_rx_console(काष्ठा uart_port *uport, u32 bytes, bool drop);
अटल पूर्णांक handle_rx_uart(काष्ठा uart_port *uport, u32 bytes, bool drop);
अटल अचिन्हित पूर्णांक qcom_geni_serial_tx_empty(काष्ठा uart_port *port);
अटल व्योम qcom_geni_serial_stop_rx(काष्ठा uart_port *uport);
अटल व्योम qcom_geni_serial_handle_rx(काष्ठा uart_port *uport, bool drop);

अटल स्थिर अचिन्हित दीर्घ root_freq[] = अणु7372800, 14745600, 19200000, 29491200,
					32000000, 48000000, 51200000, 64000000,
					80000000, 96000000, 100000000,
					102400000, 112000000, 120000000,
					128000000पूर्ण;

#घोषणा to_dev_port(ptr, member) \
		container_of(ptr, काष्ठा qcom_geni_serial_port, member)

अटल काष्ठा qcom_geni_serial_port qcom_geni_uart_ports[GENI_UART_PORTS] = अणु
	[0] = अणु
		.uport = अणु
				.iotype = UPIO_MEM,
				.ops = &qcom_geni_uart_pops,
				.flags = UPF_BOOT_AUTOCONF,
				.line = 0,
		पूर्ण,
	पूर्ण,
	[1] = अणु
		.uport = अणु
				.iotype = UPIO_MEM,
				.ops = &qcom_geni_uart_pops,
				.flags = UPF_BOOT_AUTOCONF,
				.line = 1,
		पूर्ण,
	पूर्ण,
	[2] = अणु
		.uport = अणु
				.iotype = UPIO_MEM,
				.ops = &qcom_geni_uart_pops,
				.flags = UPF_BOOT_AUTOCONF,
				.line = 2,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा qcom_geni_serial_port qcom_geni_console_port = अणु
	.uport = अणु
		.iotype = UPIO_MEM,
		.ops = &qcom_geni_console_pops,
		.flags = UPF_BOOT_AUTOCONF,
		.line = 0,
	पूर्ण,
पूर्ण;

अटल पूर्णांक qcom_geni_serial_request_port(काष्ठा uart_port *uport)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(uport->dev);
	काष्ठा qcom_geni_serial_port *port = to_dev_port(uport, uport);

	uport->membase = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(uport->membase))
		वापस PTR_ERR(uport->membase);
	port->se.base = uport->membase;
	वापस 0;
पूर्ण

अटल व्योम qcom_geni_serial_config_port(काष्ठा uart_port *uport, पूर्णांक cfg_flags)
अणु
	अगर (cfg_flags & UART_CONFIG_TYPE) अणु
		uport->type = PORT_MSM;
		qcom_geni_serial_request_port(uport);
	पूर्ण
पूर्ण

अटल अचिन्हित पूर्णांक qcom_geni_serial_get_mctrl(काष्ठा uart_port *uport)
अणु
	अचिन्हित पूर्णांक mctrl = TIOCM_DSR | TIOCM_CAR;
	u32 geni_ios;

	अगर (uart_console(uport)) अणु
		mctrl |= TIOCM_CTS;
	पूर्ण अन्यथा अणु
		geni_ios = पढ़ोl(uport->membase + SE_GENI_IOS);
		अगर (!(geni_ios & IO2_DATA_IN))
			mctrl |= TIOCM_CTS;
	पूर्ण

	वापस mctrl;
पूर्ण

अटल व्योम qcom_geni_serial_set_mctrl(काष्ठा uart_port *uport,
							अचिन्हित पूर्णांक mctrl)
अणु
	u32 uart_manual_rfr = 0;
	काष्ठा qcom_geni_serial_port *port = to_dev_port(uport, uport);

	अगर (uart_console(uport))
		वापस;

	अगर (mctrl & TIOCM_LOOP)
		port->loopback = RX_TX_CTS_RTS_SORTED;

	अगर (!(mctrl & TIOCM_RTS) && !uport->suspended)
		uart_manual_rfr = UART_MANUAL_RFR_EN | UART_RFR_NOT_READY;
	ग_लिखोl(uart_manual_rfr, uport->membase + SE_UART_MANUAL_RFR);
पूर्ण

अटल स्थिर अक्षर *qcom_geni_serial_get_type(काष्ठा uart_port *uport)
अणु
	वापस "MSM";
पूर्ण

अटल काष्ठा qcom_geni_serial_port *get_port_from_line(पूर्णांक line, bool console)
अणु
	काष्ठा qcom_geni_serial_port *port;
	पूर्णांक nr_ports = console ? GENI_UART_CONS_PORTS : GENI_UART_PORTS;

	अगर (line < 0 || line >= nr_ports)
		वापस ERR_PTR(-ENXIO);

	port = console ? &qcom_geni_console_port : &qcom_geni_uart_ports[line];
	वापस port;
पूर्ण

अटल bool qcom_geni_serial_poll_bit(काष्ठा uart_port *uport,
				पूर्णांक offset, पूर्णांक field, bool set)
अणु
	u32 reg;
	काष्ठा qcom_geni_serial_port *port;
	अचिन्हित पूर्णांक baud;
	अचिन्हित पूर्णांक fअगरo_bits;
	अचिन्हित दीर्घ समयout_us = 20000;
	काष्ठा qcom_geni_निजी_data *निजी_data = uport->निजी_data;

	अगर (निजी_data->drv) अणु
		port = to_dev_port(uport, uport);
		baud = port->baud;
		अगर (!baud)
			baud = 115200;
		fअगरo_bits = port->tx_fअगरo_depth * port->tx_fअगरo_width;
		/*
		 * Total polling iterations based on FIFO worth of bytes to be
		 * sent at current baud. Add a little fluff to the रुको.
		 */
		समयout_us = ((fअगरo_bits * USEC_PER_SEC) / baud) + 500;
	पूर्ण

	/*
	 * Use custom implementation instead of पढ़ोl_poll_atomic since kसमयr
	 * is not पढ़ोy at the समय of early console.
	 */
	समयout_us = DIV_ROUND_UP(समयout_us, 10) * 10;
	जबतक (समयout_us) अणु
		reg = पढ़ोl(uport->membase + offset);
		अगर ((bool)(reg & field) == set)
			वापस true;
		udelay(10);
		समयout_us -= 10;
	पूर्ण
	वापस false;
पूर्ण

अटल व्योम qcom_geni_serial_setup_tx(काष्ठा uart_port *uport, u32 xmit_size)
अणु
	u32 m_cmd;

	ग_लिखोl(xmit_size, uport->membase + SE_UART_TX_TRANS_LEN);
	m_cmd = UART_START_TX << M_OPCODE_SHFT;
	ग_लिखोl(m_cmd, uport->membase + SE_GENI_M_CMD0);
पूर्ण

अटल व्योम qcom_geni_serial_poll_tx_करोne(काष्ठा uart_port *uport)
अणु
	पूर्णांक करोne;
	u32 irq_clear = M_CMD_DONE_EN;

	करोne = qcom_geni_serial_poll_bit(uport, SE_GENI_M_IRQ_STATUS,
						M_CMD_DONE_EN, true);
	अगर (!करोne) अणु
		ग_लिखोl(M_GENI_CMD_ABORT, uport->membase +
						SE_GENI_M_CMD_CTRL_REG);
		irq_clear |= M_CMD_ABORT_EN;
		qcom_geni_serial_poll_bit(uport, SE_GENI_M_IRQ_STATUS,
							M_CMD_ABORT_EN, true);
	पूर्ण
	ग_लिखोl(irq_clear, uport->membase + SE_GENI_M_IRQ_CLEAR);
पूर्ण

अटल व्योम qcom_geni_serial_पात_rx(काष्ठा uart_port *uport)
अणु
	u32 irq_clear = S_CMD_DONE_EN | S_CMD_ABORT_EN;

	ग_लिखोl(S_GENI_CMD_ABORT, uport->membase + SE_GENI_S_CMD_CTRL_REG);
	qcom_geni_serial_poll_bit(uport, SE_GENI_S_CMD_CTRL_REG,
					S_GENI_CMD_ABORT, false);
	ग_लिखोl(irq_clear, uport->membase + SE_GENI_S_IRQ_CLEAR);
	ग_लिखोl(FORCE_DEFAULT, uport->membase + GENI_FORCE_DEFAULT_REG);
पूर्ण

#अगर_घोषित CONFIG_CONSOLE_POLL

अटल पूर्णांक qcom_geni_serial_get_अक्षर(काष्ठा uart_port *uport)
अणु
	काष्ठा qcom_geni_निजी_data *निजी_data = uport->निजी_data;
	u32 status;
	u32 word_cnt;
	पूर्णांक ret;

	अगर (!निजी_data->poll_cached_bytes_cnt) अणु
		status = पढ़ोl(uport->membase + SE_GENI_M_IRQ_STATUS);
		ग_लिखोl(status, uport->membase + SE_GENI_M_IRQ_CLEAR);

		status = पढ़ोl(uport->membase + SE_GENI_S_IRQ_STATUS);
		ग_लिखोl(status, uport->membase + SE_GENI_S_IRQ_CLEAR);

		status = पढ़ोl(uport->membase + SE_GENI_RX_FIFO_STATUS);
		word_cnt = status & RX_FIFO_WC_MSK;
		अगर (!word_cnt)
			वापस NO_POLL_CHAR;

		अगर (word_cnt == 1 && (status & RX_LAST))
			/*
			 * NOTE: If RX_LAST_BYTE_VALID is 0 it needs to be
			 * treated as अगर it was BYTES_PER_FIFO_WORD.
			 */
			निजी_data->poll_cached_bytes_cnt =
				(status & RX_LAST_BYTE_VALID_MSK) >>
				RX_LAST_BYTE_VALID_SHFT;

		अगर (निजी_data->poll_cached_bytes_cnt == 0)
			निजी_data->poll_cached_bytes_cnt = BYTES_PER_FIFO_WORD;

		निजी_data->poll_cached_bytes =
			पढ़ोl(uport->membase + SE_GENI_RX_FIFOn);
	पूर्ण

	निजी_data->poll_cached_bytes_cnt--;
	ret = निजी_data->poll_cached_bytes & 0xff;
	निजी_data->poll_cached_bytes >>= 8;

	वापस ret;
पूर्ण

अटल व्योम qcom_geni_serial_poll_put_अक्षर(काष्ठा uart_port *uport,
							अचिन्हित अक्षर c)
अणु
	ग_लिखोl(DEF_TX_WM, uport->membase + SE_GENI_TX_WATERMARK_REG);
	qcom_geni_serial_setup_tx(uport, 1);
	WARN_ON(!qcom_geni_serial_poll_bit(uport, SE_GENI_M_IRQ_STATUS,
						M_TX_FIFO_WATERMARK_EN, true));
	ग_लिखोl(c, uport->membase + SE_GENI_TX_FIFOn);
	ग_लिखोl(M_TX_FIFO_WATERMARK_EN, uport->membase + SE_GENI_M_IRQ_CLEAR);
	qcom_geni_serial_poll_tx_करोne(uport);
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_SERIAL_QCOM_GENI_CONSOLE
अटल व्योम qcom_geni_serial_wr_अक्षर(काष्ठा uart_port *uport, पूर्णांक ch)
अणु
	काष्ठा qcom_geni_निजी_data *निजी_data = uport->निजी_data;

	निजी_data->ग_लिखो_cached_bytes =
		(निजी_data->ग_लिखो_cached_bytes >> 8) | (ch << 24);
	निजी_data->ग_लिखो_cached_bytes_cnt++;

	अगर (निजी_data->ग_लिखो_cached_bytes_cnt == BYTES_PER_FIFO_WORD) अणु
		ग_लिखोl(निजी_data->ग_लिखो_cached_bytes,
		       uport->membase + SE_GENI_TX_FIFOn);
		निजी_data->ग_लिखो_cached_bytes_cnt = 0;
	पूर्ण
पूर्ण

अटल व्योम
__qcom_geni_serial_console_ग_लिखो(काष्ठा uart_port *uport, स्थिर अक्षर *s,
				 अचिन्हित पूर्णांक count)
अणु
	काष्ठा qcom_geni_निजी_data *निजी_data = uport->निजी_data;

	पूर्णांक i;
	u32 bytes_to_send = count;

	क्रम (i = 0; i < count; i++) अणु
		/*
		 * uart_console_ग_लिखो() adds a carriage वापस क्रम each newline.
		 * Account क्रम additional bytes to be written.
		 */
		अगर (s[i] == '\n')
			bytes_to_send++;
	पूर्ण

	ग_लिखोl(DEF_TX_WM, uport->membase + SE_GENI_TX_WATERMARK_REG);
	qcom_geni_serial_setup_tx(uport, bytes_to_send);
	क्रम (i = 0; i < count; ) अणु
		माप_प्रकार अक्षरs_to_ग_लिखो = 0;
		माप_प्रकार avail = DEF_FIFO_DEPTH_WORDS - DEF_TX_WM;

		/*
		 * If the WM bit never set, then the Tx state machine is not
		 * in a valid state, so अवरोध, cancel/पात any existing
		 * command. Unक्रमtunately the current data being written is
		 * lost.
		 */
		अगर (!qcom_geni_serial_poll_bit(uport, SE_GENI_M_IRQ_STATUS,
						M_TX_FIFO_WATERMARK_EN, true))
			अवरोध;
		अक्षरs_to_ग_लिखो = min_t(माप_प्रकार, count - i, avail / 2);
		uart_console_ग_लिखो(uport, s + i, अक्षरs_to_ग_लिखो,
						qcom_geni_serial_wr_अक्षर);
		ग_लिखोl(M_TX_FIFO_WATERMARK_EN, uport->membase +
							SE_GENI_M_IRQ_CLEAR);
		i += अक्षरs_to_ग_लिखो;
	पूर्ण

	अगर (निजी_data->ग_लिखो_cached_bytes_cnt) अणु
		निजी_data->ग_लिखो_cached_bytes >>= BITS_PER_BYTE *
			(BYTES_PER_FIFO_WORD - निजी_data->ग_लिखो_cached_bytes_cnt);
		ग_लिखोl(निजी_data->ग_लिखो_cached_bytes,
		       uport->membase + SE_GENI_TX_FIFOn);
		निजी_data->ग_लिखो_cached_bytes_cnt = 0;
	पूर्ण

	qcom_geni_serial_poll_tx_करोne(uport);
पूर्ण

अटल व्योम qcom_geni_serial_console_ग_लिखो(काष्ठा console *co, स्थिर अक्षर *s,
			      अचिन्हित पूर्णांक count)
अणु
	काष्ठा uart_port *uport;
	काष्ठा qcom_geni_serial_port *port;
	bool locked = true;
	अचिन्हित दीर्घ flags;
	u32 geni_status;
	u32 irq_en;

	WARN_ON(co->index < 0 || co->index >= GENI_UART_CONS_PORTS);

	port = get_port_from_line(co->index, true);
	अगर (IS_ERR(port))
		वापस;

	uport = &port->uport;
	अगर (oops_in_progress)
		locked = spin_trylock_irqsave(&uport->lock, flags);
	अन्यथा
		spin_lock_irqsave(&uport->lock, flags);

	geni_status = पढ़ोl(uport->membase + SE_GENI_STATUS);

	/* Cancel the current ग_लिखो to log the fault */
	अगर (!locked) अणु
		geni_se_cancel_m_cmd(&port->se);
		अगर (!qcom_geni_serial_poll_bit(uport, SE_GENI_M_IRQ_STATUS,
						M_CMD_CANCEL_EN, true)) अणु
			geni_se_पात_m_cmd(&port->se);
			qcom_geni_serial_poll_bit(uport, SE_GENI_M_IRQ_STATUS,
							M_CMD_ABORT_EN, true);
			ग_लिखोl(M_CMD_ABORT_EN, uport->membase +
							SE_GENI_M_IRQ_CLEAR);
		पूर्ण
		ग_लिखोl(M_CMD_CANCEL_EN, uport->membase + SE_GENI_M_IRQ_CLEAR);
	पूर्ण अन्यथा अगर ((geni_status & M_GENI_CMD_ACTIVE) && !port->tx_reमुख्यing) अणु
		/*
		 * It seems we can't पूर्णांकerrupt existing transfers अगर all data
		 * has been sent, in which हाल we need to look क्रम करोne first.
		 */
		qcom_geni_serial_poll_tx_करोne(uport);

		अगर (uart_circ_अक्षरs_pending(&uport->state->xmit)) अणु
			irq_en = पढ़ोl(uport->membase + SE_GENI_M_IRQ_EN);
			ग_लिखोl(irq_en | M_TX_FIFO_WATERMARK_EN,
					uport->membase + SE_GENI_M_IRQ_EN);
		पूर्ण
	पूर्ण

	__qcom_geni_serial_console_ग_लिखो(uport, s, count);

	अगर (port->tx_reमुख्यing)
		qcom_geni_serial_setup_tx(uport, port->tx_reमुख्यing);

	अगर (locked)
		spin_unlock_irqrestore(&uport->lock, flags);
पूर्ण

अटल पूर्णांक handle_rx_console(काष्ठा uart_port *uport, u32 bytes, bool drop)
अणु
	u32 i;
	अचिन्हित अक्षर buf[माप(u32)];
	काष्ठा tty_port *tport;
	काष्ठा qcom_geni_serial_port *port = to_dev_port(uport, uport);

	tport = &uport->state->port;
	क्रम (i = 0; i < bytes; ) अणु
		पूर्णांक c;
		पूर्णांक chunk = min_t(पूर्णांक, bytes - i, BYTES_PER_FIFO_WORD);

		ioपढ़ो32_rep(uport->membase + SE_GENI_RX_FIFOn, buf, 1);
		i += chunk;
		अगर (drop)
			जारी;

		क्रम (c = 0; c < chunk; c++) अणु
			पूर्णांक sysrq;

			uport->icount.rx++;
			अगर (port->brk && buf[c] == 0) अणु
				port->brk = false;
				अगर (uart_handle_अवरोध(uport))
					जारी;
			पूर्ण

			sysrq = uart_prepare_sysrq_अक्षर(uport, buf[c]);

			अगर (!sysrq)
				tty_insert_flip_अक्षर(tport, buf[c], TTY_NORMAL);
		पूर्ण
	पूर्ण
	अगर (!drop)
		tty_flip_buffer_push(tport);
	वापस 0;
पूर्ण
#अन्यथा
अटल पूर्णांक handle_rx_console(काष्ठा uart_port *uport, u32 bytes, bool drop)
अणु
	वापस -EPERM;
पूर्ण

#पूर्ण_अगर /* CONFIG_SERIAL_QCOM_GENI_CONSOLE */

अटल पूर्णांक handle_rx_uart(काष्ठा uart_port *uport, u32 bytes, bool drop)
अणु
	काष्ठा tty_port *tport;
	काष्ठा qcom_geni_serial_port *port = to_dev_port(uport, uport);
	u32 num_bytes_pw = port->tx_fअगरo_width / BITS_PER_BYTE;
	u32 words = ALIGN(bytes, num_bytes_pw) / num_bytes_pw;
	पूर्णांक ret;

	tport = &uport->state->port;
	ioपढ़ो32_rep(uport->membase + SE_GENI_RX_FIFOn, port->rx_fअगरo, words);
	अगर (drop)
		वापस 0;

	ret = tty_insert_flip_string(tport, port->rx_fअगरo, bytes);
	अगर (ret != bytes) अणु
		dev_err(uport->dev, "%s:Unable to push data ret %d_bytes %d\n",
				__func__, ret, bytes);
		WARN_ON_ONCE(1);
	पूर्ण
	uport->icount.rx += ret;
	tty_flip_buffer_push(tport);
	वापस ret;
पूर्ण

अटल व्योम qcom_geni_serial_start_tx(काष्ठा uart_port *uport)
अणु
	u32 irq_en;
	u32 status;

	status = पढ़ोl(uport->membase + SE_GENI_STATUS);
	अगर (status & M_GENI_CMD_ACTIVE)
		वापस;

	अगर (!qcom_geni_serial_tx_empty(uport))
		वापस;

	irq_en = पढ़ोl(uport->membase +	SE_GENI_M_IRQ_EN);
	irq_en |= M_TX_FIFO_WATERMARK_EN | M_CMD_DONE_EN;

	ग_लिखोl(DEF_TX_WM, uport->membase + SE_GENI_TX_WATERMARK_REG);
	ग_लिखोl(irq_en, uport->membase +	SE_GENI_M_IRQ_EN);
पूर्ण

अटल व्योम qcom_geni_serial_stop_tx(काष्ठा uart_port *uport)
अणु
	u32 irq_en;
	u32 status;
	काष्ठा qcom_geni_serial_port *port = to_dev_port(uport, uport);

	irq_en = पढ़ोl(uport->membase + SE_GENI_M_IRQ_EN);
	irq_en &= ~(M_CMD_DONE_EN | M_TX_FIFO_WATERMARK_EN);
	ग_लिखोl(0, uport->membase + SE_GENI_TX_WATERMARK_REG);
	ग_लिखोl(irq_en, uport->membase + SE_GENI_M_IRQ_EN);
	status = पढ़ोl(uport->membase + SE_GENI_STATUS);
	/* Possible stop tx is called multiple बार. */
	अगर (!(status & M_GENI_CMD_ACTIVE))
		वापस;

	geni_se_cancel_m_cmd(&port->se);
	अगर (!qcom_geni_serial_poll_bit(uport, SE_GENI_M_IRQ_STATUS,
						M_CMD_CANCEL_EN, true)) अणु
		geni_se_पात_m_cmd(&port->se);
		qcom_geni_serial_poll_bit(uport, SE_GENI_M_IRQ_STATUS,
						M_CMD_ABORT_EN, true);
		ग_लिखोl(M_CMD_ABORT_EN, uport->membase + SE_GENI_M_IRQ_CLEAR);
	पूर्ण
	ग_लिखोl(M_CMD_CANCEL_EN, uport->membase + SE_GENI_M_IRQ_CLEAR);
पूर्ण

अटल व्योम qcom_geni_serial_start_rx(काष्ठा uart_port *uport)
अणु
	u32 irq_en;
	u32 status;
	काष्ठा qcom_geni_serial_port *port = to_dev_port(uport, uport);

	status = पढ़ोl(uport->membase + SE_GENI_STATUS);
	अगर (status & S_GENI_CMD_ACTIVE)
		qcom_geni_serial_stop_rx(uport);

	geni_se_setup_s_cmd(&port->se, UART_START_READ, 0);

	irq_en = पढ़ोl(uport->membase + SE_GENI_S_IRQ_EN);
	irq_en |= S_RX_FIFO_WATERMARK_EN | S_RX_FIFO_LAST_EN;
	ग_लिखोl(irq_en, uport->membase + SE_GENI_S_IRQ_EN);

	irq_en = पढ़ोl(uport->membase + SE_GENI_M_IRQ_EN);
	irq_en |= M_RX_FIFO_WATERMARK_EN | M_RX_FIFO_LAST_EN;
	ग_लिखोl(irq_en, uport->membase + SE_GENI_M_IRQ_EN);
पूर्ण

अटल व्योम qcom_geni_serial_stop_rx(काष्ठा uart_port *uport)
अणु
	u32 irq_en;
	u32 status;
	काष्ठा qcom_geni_serial_port *port = to_dev_port(uport, uport);
	u32 s_irq_status;

	irq_en = पढ़ोl(uport->membase + SE_GENI_S_IRQ_EN);
	irq_en &= ~(S_RX_FIFO_WATERMARK_EN | S_RX_FIFO_LAST_EN);
	ग_लिखोl(irq_en, uport->membase + SE_GENI_S_IRQ_EN);

	irq_en = पढ़ोl(uport->membase + SE_GENI_M_IRQ_EN);
	irq_en &= ~(M_RX_FIFO_WATERMARK_EN | M_RX_FIFO_LAST_EN);
	ग_लिखोl(irq_en, uport->membase + SE_GENI_M_IRQ_EN);

	status = पढ़ोl(uport->membase + SE_GENI_STATUS);
	/* Possible stop rx is called multiple बार. */
	अगर (!(status & S_GENI_CMD_ACTIVE))
		वापस;

	geni_se_cancel_s_cmd(&port->se);
	qcom_geni_serial_poll_bit(uport, SE_GENI_S_IRQ_STATUS,
					S_CMD_CANCEL_EN, true);
	/*
	 * If समयout occurs secondary engine reमुख्यs active
	 * and Abort sequence is executed.
	 */
	s_irq_status = पढ़ोl(uport->membase + SE_GENI_S_IRQ_STATUS);
	/* Flush the Rx buffer */
	अगर (s_irq_status & S_RX_FIFO_LAST_EN)
		qcom_geni_serial_handle_rx(uport, true);
	ग_लिखोl(s_irq_status, uport->membase + SE_GENI_S_IRQ_CLEAR);

	status = पढ़ोl(uport->membase + SE_GENI_STATUS);
	अगर (status & S_GENI_CMD_ACTIVE)
		qcom_geni_serial_पात_rx(uport);
पूर्ण

अटल व्योम qcom_geni_serial_handle_rx(काष्ठा uart_port *uport, bool drop)
अणु
	u32 status;
	u32 word_cnt;
	u32 last_word_byte_cnt;
	u32 last_word_partial;
	u32 total_bytes;
	काष्ठा qcom_geni_serial_port *port = to_dev_port(uport, uport);

	status = पढ़ोl(uport->membase +	SE_GENI_RX_FIFO_STATUS);
	word_cnt = status & RX_FIFO_WC_MSK;
	last_word_partial = status & RX_LAST;
	last_word_byte_cnt = (status & RX_LAST_BYTE_VALID_MSK) >>
						RX_LAST_BYTE_VALID_SHFT;

	अगर (!word_cnt)
		वापस;
	total_bytes = BYTES_PER_FIFO_WORD * (word_cnt - 1);
	अगर (last_word_partial && last_word_byte_cnt)
		total_bytes += last_word_byte_cnt;
	अन्यथा
		total_bytes += BYTES_PER_FIFO_WORD;
	port->handle_rx(uport, total_bytes, drop);
पूर्ण

अटल व्योम qcom_geni_serial_handle_tx(काष्ठा uart_port *uport, bool करोne,
		bool active)
अणु
	काष्ठा qcom_geni_serial_port *port = to_dev_port(uport, uport);
	काष्ठा circ_buf *xmit = &uport->state->xmit;
	माप_प्रकार avail;
	माप_प्रकार reमुख्यing;
	माप_प्रकार pending;
	पूर्णांक i;
	u32 status;
	u32 irq_en;
	अचिन्हित पूर्णांक chunk;
	पूर्णांक tail;

	status = पढ़ोl(uport->membase + SE_GENI_TX_FIFO_STATUS);

	/* Complete the current tx command beक्रमe taking newly added data */
	अगर (active)
		pending = port->tx_reमुख्यing;
	अन्यथा
		pending = uart_circ_अक्षरs_pending(xmit);

	/* All data has been transmitted and acknowledged as received */
	अगर (!pending && !status && करोne) अणु
		qcom_geni_serial_stop_tx(uport);
		जाओ out_ग_लिखो_wakeup;
	पूर्ण

	avail = port->tx_fअगरo_depth - (status & TX_FIFO_WC);
	avail *= BYTES_PER_FIFO_WORD;

	tail = xmit->tail;
	chunk = min(avail, pending);
	अगर (!chunk)
		जाओ out_ग_लिखो_wakeup;

	अगर (!port->tx_reमुख्यing) अणु
		qcom_geni_serial_setup_tx(uport, pending);
		port->tx_reमुख्यing = pending;

		irq_en = पढ़ोl(uport->membase + SE_GENI_M_IRQ_EN);
		अगर (!(irq_en & M_TX_FIFO_WATERMARK_EN))
			ग_लिखोl(irq_en | M_TX_FIFO_WATERMARK_EN,
					uport->membase + SE_GENI_M_IRQ_EN);
	पूर्ण

	reमुख्यing = chunk;
	क्रम (i = 0; i < chunk; ) अणु
		अचिन्हित पूर्णांक tx_bytes;
		u8 buf[माप(u32)];
		पूर्णांक c;

		स_रखो(buf, 0, माप(buf));
		tx_bytes = min_t(माप_प्रकार, reमुख्यing, BYTES_PER_FIFO_WORD);

		क्रम (c = 0; c < tx_bytes ; c++) अणु
			buf[c] = xmit->buf[tail++];
			tail &= UART_XMIT_SIZE - 1;
		पूर्ण

		ioग_लिखो32_rep(uport->membase + SE_GENI_TX_FIFOn, buf, 1);

		i += tx_bytes;
		uport->icount.tx += tx_bytes;
		reमुख्यing -= tx_bytes;
		port->tx_reमुख्यing -= tx_bytes;
	पूर्ण

	xmit->tail = tail;

	/*
	 * The tx fअगरo watermark is level triggered and latched. Though we had
	 * cleared it in qcom_geni_serial_isr it will have alपढ़ोy reनिश्चितed
	 * so we must clear it again here after our ग_लिखोs.
	 */
	ग_लिखोl(M_TX_FIFO_WATERMARK_EN,
			uport->membase + SE_GENI_M_IRQ_CLEAR);

out_ग_लिखो_wakeup:
	अगर (!port->tx_reमुख्यing) अणु
		irq_en = पढ़ोl(uport->membase + SE_GENI_M_IRQ_EN);
		अगर (irq_en & M_TX_FIFO_WATERMARK_EN)
			ग_लिखोl(irq_en & ~M_TX_FIFO_WATERMARK_EN,
					uport->membase + SE_GENI_M_IRQ_EN);
	पूर्ण

	अगर (uart_circ_अक्षरs_pending(xmit) < WAKEUP_CHARS)
		uart_ग_लिखो_wakeup(uport);
पूर्ण

अटल irqवापस_t qcom_geni_serial_isr(पूर्णांक isr, व्योम *dev)
अणु
	u32 m_irq_en;
	u32 m_irq_status;
	u32 s_irq_status;
	u32 geni_status;
	काष्ठा uart_port *uport = dev;
	bool drop_rx = false;
	काष्ठा tty_port *tport = &uport->state->port;
	काष्ठा qcom_geni_serial_port *port = to_dev_port(uport, uport);

	अगर (uport->suspended)
		वापस IRQ_NONE;

	spin_lock(&uport->lock);

	m_irq_status = पढ़ोl(uport->membase + SE_GENI_M_IRQ_STATUS);
	s_irq_status = पढ़ोl(uport->membase + SE_GENI_S_IRQ_STATUS);
	geni_status = पढ़ोl(uport->membase + SE_GENI_STATUS);
	m_irq_en = पढ़ोl(uport->membase + SE_GENI_M_IRQ_EN);
	ग_लिखोl(m_irq_status, uport->membase + SE_GENI_M_IRQ_CLEAR);
	ग_लिखोl(s_irq_status, uport->membase + SE_GENI_S_IRQ_CLEAR);

	अगर (WARN_ON(m_irq_status & M_ILLEGAL_CMD_EN))
		जाओ out_unlock;

	अगर (s_irq_status & S_RX_FIFO_WR_ERR_EN) अणु
		uport->icount.overrun++;
		tty_insert_flip_अक्षर(tport, 0, TTY_OVERRUN);
	पूर्ण

	अगर (m_irq_status & m_irq_en & (M_TX_FIFO_WATERMARK_EN | M_CMD_DONE_EN))
		qcom_geni_serial_handle_tx(uport, m_irq_status & M_CMD_DONE_EN,
					geni_status & M_GENI_CMD_ACTIVE);

	अगर (s_irq_status & S_GP_IRQ_0_EN || s_irq_status & S_GP_IRQ_1_EN) अणु
		अगर (s_irq_status & S_GP_IRQ_0_EN)
			uport->icount.parity++;
		drop_rx = true;
	पूर्ण अन्यथा अगर (s_irq_status & S_GP_IRQ_2_EN ||
					s_irq_status & S_GP_IRQ_3_EN) अणु
		uport->icount.brk++;
		port->brk = true;
	पूर्ण

	अगर (s_irq_status & S_RX_FIFO_WATERMARK_EN ||
					s_irq_status & S_RX_FIFO_LAST_EN)
		qcom_geni_serial_handle_rx(uport, drop_rx);

out_unlock:
	uart_unlock_and_check_sysrq(uport);

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम get_tx_fअगरo_size(काष्ठा qcom_geni_serial_port *port)
अणु
	काष्ठा uart_port *uport;

	uport = &port->uport;
	port->tx_fअगरo_depth = geni_se_get_tx_fअगरo_depth(&port->se);
	port->tx_fअगरo_width = geni_se_get_tx_fअगरo_width(&port->se);
	port->rx_fअगरo_depth = geni_se_get_rx_fअगरo_depth(&port->se);
	uport->fअगरosize =
		(port->tx_fअगरo_depth * port->tx_fअगरo_width) / BITS_PER_BYTE;
पूर्ण


अटल व्योम qcom_geni_serial_shutकरोwn(काष्ठा uart_port *uport)
अणु
	disable_irq(uport->irq);
पूर्ण

अटल पूर्णांक qcom_geni_serial_port_setup(काष्ठा uart_port *uport)
अणु
	काष्ठा qcom_geni_serial_port *port = to_dev_port(uport, uport);
	u32 rxstale = DEFAULT_BITS_PER_CHAR * STALE_TIMEOUT;
	u32 proto;
	u32 pin_swap;

	proto = geni_se_पढ़ो_proto(&port->se);
	अगर (proto != GENI_SE_UART) अणु
		dev_err(uport->dev, "Invalid FW loaded, proto: %d\n", proto);
		वापस -ENXIO;
	पूर्ण

	qcom_geni_serial_stop_rx(uport);

	get_tx_fअगरo_size(port);

	ग_लिखोl(rxstale, uport->membase + SE_UART_RX_STALE_CNT);

	pin_swap = पढ़ोl(uport->membase + SE_UART_IO_MACRO_CTRL);
	अगर (port->rx_tx_swap) अणु
		pin_swap &= ~DEFAULT_IO_MACRO_IO2_IO3_MASK;
		pin_swap |= IO_MACRO_IO2_IO3_SWAP;
	पूर्ण
	अगर (port->cts_rts_swap) अणु
		pin_swap &= ~DEFAULT_IO_MACRO_IO0_IO1_MASK;
		pin_swap |= IO_MACRO_IO0_SEL;
	पूर्ण
	/* Configure this रेजिस्टर अगर RX-TX, CTS-RTS pins are swapped */
	अगर (port->rx_tx_swap || port->cts_rts_swap)
		ग_लिखोl(pin_swap, uport->membase + SE_UART_IO_MACRO_CTRL);

	/*
	 * Make an unconditional cancel on the मुख्य sequencer to reset
	 * it अन्यथा we could end up in data loss scenarios.
	 */
	अगर (uart_console(uport))
		qcom_geni_serial_poll_tx_करोne(uport);
	geni_se_config_packing(&port->se, BITS_PER_BYTE, BYTES_PER_FIFO_WORD,
			       false, true, true);
	geni_se_init(&port->se, UART_RX_WM, port->rx_fअगरo_depth - 2);
	geni_se_select_mode(&port->se, GENI_SE_FIFO);
	port->setup = true;

	वापस 0;
पूर्ण

अटल पूर्णांक qcom_geni_serial_startup(काष्ठा uart_port *uport)
अणु
	पूर्णांक ret;
	काष्ठा qcom_geni_serial_port *port = to_dev_port(uport, uport);

	अगर (!port->setup) अणु
		ret = qcom_geni_serial_port_setup(uport);
		अगर (ret)
			वापस ret;
	पूर्ण
	enable_irq(uport->irq);

	वापस 0;
पूर्ण

अटल अचिन्हित दीर्घ get_clk_cfg(अचिन्हित दीर्घ clk_freq)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(root_freq); i++) अणु
		अगर (!(root_freq[i] % clk_freq))
			वापस root_freq[i];
	पूर्ण
	वापस 0;
पूर्ण

अटल अचिन्हित दीर्घ get_clk_भाग_rate(अचिन्हित पूर्णांक baud,
			अचिन्हित पूर्णांक sampling_rate, अचिन्हित पूर्णांक *clk_भाग)
अणु
	अचिन्हित दीर्घ ser_clk;
	अचिन्हित दीर्घ desired_clk;

	desired_clk = baud * sampling_rate;
	ser_clk = get_clk_cfg(desired_clk);
	अगर (!ser_clk) अणु
		pr_err("%s: Can't find matching DFS entry for baud %d\n",
								__func__, baud);
		वापस ser_clk;
	पूर्ण

	*clk_भाग = ser_clk / desired_clk;
	वापस ser_clk;
पूर्ण

अटल व्योम qcom_geni_serial_set_termios(काष्ठा uart_port *uport,
				काष्ठा ktermios *termios, काष्ठा ktermios *old)
अणु
	अचिन्हित पूर्णांक baud;
	u32 bits_per_अक्षर;
	u32 tx_trans_cfg;
	u32 tx_parity_cfg;
	u32 rx_trans_cfg;
	u32 rx_parity_cfg;
	u32 stop_bit_len;
	अचिन्हित पूर्णांक clk_भाग;
	u32 ser_clk_cfg;
	काष्ठा qcom_geni_serial_port *port = to_dev_port(uport, uport);
	अचिन्हित दीर्घ clk_rate;
	u32 ver, sampling_rate;
	अचिन्हित पूर्णांक avg_bw_core;

	qcom_geni_serial_stop_rx(uport);
	/* baud rate */
	baud = uart_get_baud_rate(uport, termios, old, 300, 4000000);
	port->baud = baud;

	sampling_rate = UART_OVERSAMPLING;
	/* Sampling rate is halved क्रम IP versions >= 2.5 */
	ver = geni_se_get_qup_hw_version(&port->se);
	अगर (ver >= QUP_SE_VERSION_2_5)
		sampling_rate /= 2;

	clk_rate = get_clk_भाग_rate(baud, sampling_rate, &clk_भाग);
	अगर (!clk_rate)
		जाओ out_restart_rx;

	uport->uartclk = clk_rate;
	dev_pm_opp_set_rate(uport->dev, clk_rate);
	ser_clk_cfg = SER_CLK_EN;
	ser_clk_cfg |= clk_भाग << CLK_DIV_SHFT;

	/*
	 * Bump up BW vote on CPU and CORE path as driver supports FIFO mode
	 * only.
	 */
	avg_bw_core = (baud > 115200) ? Bps_to_icc(CORE_2X_50_MHZ)
						: GENI_DEFAULT_BW;
	port->se.icc_paths[GENI_TO_CORE].avg_bw = avg_bw_core;
	port->se.icc_paths[CPU_TO_GENI].avg_bw = Bps_to_icc(baud);
	geni_icc_set_bw(&port->se);

	/* parity */
	tx_trans_cfg = पढ़ोl(uport->membase + SE_UART_TX_TRANS_CFG);
	tx_parity_cfg = पढ़ोl(uport->membase + SE_UART_TX_PARITY_CFG);
	rx_trans_cfg = पढ़ोl(uport->membase + SE_UART_RX_TRANS_CFG);
	rx_parity_cfg = पढ़ोl(uport->membase + SE_UART_RX_PARITY_CFG);
	अगर (termios->c_cflag & PARENB) अणु
		tx_trans_cfg |= UART_TX_PAR_EN;
		rx_trans_cfg |= UART_RX_PAR_EN;
		tx_parity_cfg |= PAR_CALC_EN;
		rx_parity_cfg |= PAR_CALC_EN;
		अगर (termios->c_cflag & PARODD) अणु
			tx_parity_cfg |= PAR_ODD;
			rx_parity_cfg |= PAR_ODD;
		पूर्ण अन्यथा अगर (termios->c_cflag & CMSPAR) अणु
			tx_parity_cfg |= PAR_SPACE;
			rx_parity_cfg |= PAR_SPACE;
		पूर्ण अन्यथा अणु
			tx_parity_cfg |= PAR_EVEN;
			rx_parity_cfg |= PAR_EVEN;
		पूर्ण
	पूर्ण अन्यथा अणु
		tx_trans_cfg &= ~UART_TX_PAR_EN;
		rx_trans_cfg &= ~UART_RX_PAR_EN;
		tx_parity_cfg &= ~PAR_CALC_EN;
		rx_parity_cfg &= ~PAR_CALC_EN;
	पूर्ण

	/* bits per अक्षर */
	चयन (termios->c_cflag & CSIZE) अणु
	हाल CS5:
		bits_per_अक्षर = 5;
		अवरोध;
	हाल CS6:
		bits_per_अक्षर = 6;
		अवरोध;
	हाल CS7:
		bits_per_अक्षर = 7;
		अवरोध;
	हाल CS8:
	शेष:
		bits_per_अक्षर = 8;
		अवरोध;
	पूर्ण

	/* stop bits */
	अगर (termios->c_cflag & CSTOPB)
		stop_bit_len = TX_STOP_BIT_LEN_2;
	अन्यथा
		stop_bit_len = TX_STOP_BIT_LEN_1;

	/* flow control, clear the CTS_MASK bit अगर using flow control. */
	अगर (termios->c_cflag & CRTSCTS)
		tx_trans_cfg &= ~UART_CTS_MASK;
	अन्यथा
		tx_trans_cfg |= UART_CTS_MASK;

	अगर (baud)
		uart_update_समयout(uport, termios->c_cflag, baud);

	अगर (!uart_console(uport))
		ग_लिखोl(port->loopback,
				uport->membase + SE_UART_LOOPBACK_CFG);
	ग_लिखोl(tx_trans_cfg, uport->membase + SE_UART_TX_TRANS_CFG);
	ग_लिखोl(tx_parity_cfg, uport->membase + SE_UART_TX_PARITY_CFG);
	ग_लिखोl(rx_trans_cfg, uport->membase + SE_UART_RX_TRANS_CFG);
	ग_लिखोl(rx_parity_cfg, uport->membase + SE_UART_RX_PARITY_CFG);
	ग_लिखोl(bits_per_अक्षर, uport->membase + SE_UART_TX_WORD_LEN);
	ग_लिखोl(bits_per_अक्षर, uport->membase + SE_UART_RX_WORD_LEN);
	ग_लिखोl(stop_bit_len, uport->membase + SE_UART_TX_STOP_BIT_LEN);
	ग_लिखोl(ser_clk_cfg, uport->membase + GENI_SER_M_CLK_CFG);
	ग_लिखोl(ser_clk_cfg, uport->membase + GENI_SER_S_CLK_CFG);
out_restart_rx:
	qcom_geni_serial_start_rx(uport);
पूर्ण

अटल अचिन्हित पूर्णांक qcom_geni_serial_tx_empty(काष्ठा uart_port *uport)
अणु
	वापस !पढ़ोl(uport->membase + SE_GENI_TX_FIFO_STATUS);
पूर्ण

#अगर_घोषित CONFIG_SERIAL_QCOM_GENI_CONSOLE
अटल पूर्णांक qcom_geni_console_setup(काष्ठा console *co, अक्षर *options)
अणु
	काष्ठा uart_port *uport;
	काष्ठा qcom_geni_serial_port *port;
	पूर्णांक baud = 115200;
	पूर्णांक bits = 8;
	पूर्णांक parity = 'n';
	पूर्णांक flow = 'n';
	पूर्णांक ret;

	अगर (co->index >= GENI_UART_CONS_PORTS  || co->index < 0)
		वापस -ENXIO;

	port = get_port_from_line(co->index, true);
	अगर (IS_ERR(port)) अणु
		pr_err("Invalid line %d\n", co->index);
		वापस PTR_ERR(port);
	पूर्ण

	uport = &port->uport;

	अगर (unlikely(!uport->membase))
		वापस -ENXIO;

	अगर (!port->setup) अणु
		ret = qcom_geni_serial_port_setup(uport);
		अगर (ret)
			वापस ret;
	पूर्ण

	अगर (options)
		uart_parse_options(options, &baud, &parity, &bits, &flow);

	वापस uart_set_options(uport, co, baud, parity, bits, flow);
पूर्ण

अटल व्योम qcom_geni_serial_earlycon_ग_लिखो(काष्ठा console *con,
					स्थिर अक्षर *s, अचिन्हित पूर्णांक n)
अणु
	काष्ठा earlycon_device *dev = con->data;

	__qcom_geni_serial_console_ग_लिखो(&dev->port, s, n);
पूर्ण

#अगर_घोषित CONFIG_CONSOLE_POLL
अटल पूर्णांक qcom_geni_serial_earlycon_पढ़ो(काष्ठा console *con,
					  अक्षर *s, अचिन्हित पूर्णांक n)
अणु
	काष्ठा earlycon_device *dev = con->data;
	काष्ठा uart_port *uport = &dev->port;
	पूर्णांक num_पढ़ो = 0;
	पूर्णांक ch;

	जबतक (num_पढ़ो < n) अणु
		ch = qcom_geni_serial_get_अक्षर(uport);
		अगर (ch == NO_POLL_CHAR)
			अवरोध;
		s[num_पढ़ो++] = ch;
	पूर्ण

	वापस num_पढ़ो;
पूर्ण

अटल व्योम __init qcom_geni_serial_enable_early_पढ़ो(काष्ठा geni_se *se,
						      काष्ठा console *con)
अणु
	geni_se_setup_s_cmd(se, UART_START_READ, 0);
	con->पढ़ो = qcom_geni_serial_earlycon_पढ़ो;
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम qcom_geni_serial_enable_early_पढ़ो(काष्ठा geni_se *se,
						      काष्ठा console *con) अणु पूर्ण
#पूर्ण_अगर

अटल काष्ठा qcom_geni_निजी_data earlycon_निजी_data;

अटल पूर्णांक __init qcom_geni_serial_earlycon_setup(काष्ठा earlycon_device *dev,
								स्थिर अक्षर *opt)
अणु
	काष्ठा uart_port *uport = &dev->port;
	u32 tx_trans_cfg;
	u32 tx_parity_cfg = 0;	/* Disable Tx Parity */
	u32 rx_trans_cfg = 0;
	u32 rx_parity_cfg = 0;	/* Disable Rx Parity */
	u32 stop_bit_len = 0;	/* Default stop bit length - 1 bit */
	u32 bits_per_अक्षर;
	काष्ठा geni_se se;

	अगर (!uport->membase)
		वापस -EINVAL;

	uport->निजी_data = &earlycon_निजी_data;

	स_रखो(&se, 0, माप(se));
	se.base = uport->membase;
	अगर (geni_se_पढ़ो_proto(&se) != GENI_SE_UART)
		वापस -ENXIO;
	/*
	 * Ignore Flow control.
	 * n = 8.
	 */
	tx_trans_cfg = UART_CTS_MASK;
	bits_per_अक्षर = BITS_PER_BYTE;

	/*
	 * Make an unconditional cancel on the मुख्य sequencer to reset
	 * it अन्यथा we could end up in data loss scenarios.
	 */
	qcom_geni_serial_poll_tx_करोne(uport);
	qcom_geni_serial_पात_rx(uport);
	geni_se_config_packing(&se, BITS_PER_BYTE, BYTES_PER_FIFO_WORD,
			       false, true, true);
	geni_se_init(&se, DEF_FIFO_DEPTH_WORDS / 2, DEF_FIFO_DEPTH_WORDS - 2);
	geni_se_select_mode(&se, GENI_SE_FIFO);

	ग_लिखोl(tx_trans_cfg, uport->membase + SE_UART_TX_TRANS_CFG);
	ग_लिखोl(tx_parity_cfg, uport->membase + SE_UART_TX_PARITY_CFG);
	ग_लिखोl(rx_trans_cfg, uport->membase + SE_UART_RX_TRANS_CFG);
	ग_लिखोl(rx_parity_cfg, uport->membase + SE_UART_RX_PARITY_CFG);
	ग_लिखोl(bits_per_अक्षर, uport->membase + SE_UART_TX_WORD_LEN);
	ग_लिखोl(bits_per_अक्षर, uport->membase + SE_UART_RX_WORD_LEN);
	ग_लिखोl(stop_bit_len, uport->membase + SE_UART_TX_STOP_BIT_LEN);

	dev->con->ग_लिखो = qcom_geni_serial_earlycon_ग_लिखो;
	dev->con->setup = शून्य;
	qcom_geni_serial_enable_early_पढ़ो(&se, dev->con);

	वापस 0;
पूर्ण
OF_EARLYCON_DECLARE(qcom_geni, "qcom,geni-debug-uart",
				qcom_geni_serial_earlycon_setup);

अटल पूर्णांक __init console_रेजिस्टर(काष्ठा uart_driver *drv)
अणु
	वापस uart_रेजिस्टर_driver(drv);
पूर्ण

अटल व्योम console_unरेजिस्टर(काष्ठा uart_driver *drv)
अणु
	uart_unरेजिस्टर_driver(drv);
पूर्ण

अटल काष्ठा console cons_ops = अणु
	.name = "ttyMSM",
	.ग_लिखो = qcom_geni_serial_console_ग_लिखो,
	.device = uart_console_device,
	.setup = qcom_geni_console_setup,
	.flags = CON_PRINTBUFFER,
	.index = -1,
	.data = &qcom_geni_console_driver,
पूर्ण;

अटल काष्ठा uart_driver qcom_geni_console_driver = अणु
	.owner = THIS_MODULE,
	.driver_name = "qcom_geni_console",
	.dev_name = "ttyMSM",
	.nr =  GENI_UART_CONS_PORTS,
	.cons = &cons_ops,
पूर्ण;
#अन्यथा
अटल पूर्णांक console_रेजिस्टर(काष्ठा uart_driver *drv)
अणु
	वापस 0;
पूर्ण

अटल व्योम console_unरेजिस्टर(काष्ठा uart_driver *drv)
अणु
पूर्ण
#पूर्ण_अगर /* CONFIG_SERIAL_QCOM_GENI_CONSOLE */

अटल काष्ठा uart_driver qcom_geni_uart_driver = अणु
	.owner = THIS_MODULE,
	.driver_name = "qcom_geni_uart",
	.dev_name = "ttyHS",
	.nr =  GENI_UART_PORTS,
पूर्ण;

अटल व्योम qcom_geni_serial_pm(काष्ठा uart_port *uport,
		अचिन्हित पूर्णांक new_state, अचिन्हित पूर्णांक old_state)
अणु
	काष्ठा qcom_geni_serial_port *port = to_dev_port(uport, uport);

	/* If we've never been called, treat it as off */
	अगर (old_state == UART_PM_STATE_UNDEFINED)
		old_state = UART_PM_STATE_OFF;

	अगर (new_state == UART_PM_STATE_ON && old_state == UART_PM_STATE_OFF) अणु
		geni_icc_enable(&port->se);
		geni_se_resources_on(&port->se);
	पूर्ण अन्यथा अगर (new_state == UART_PM_STATE_OFF &&
			old_state == UART_PM_STATE_ON) अणु
		geni_se_resources_off(&port->se);
		geni_icc_disable(&port->se);
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा uart_ops qcom_geni_console_pops = अणु
	.tx_empty = qcom_geni_serial_tx_empty,
	.stop_tx = qcom_geni_serial_stop_tx,
	.start_tx = qcom_geni_serial_start_tx,
	.stop_rx = qcom_geni_serial_stop_rx,
	.set_termios = qcom_geni_serial_set_termios,
	.startup = qcom_geni_serial_startup,
	.request_port = qcom_geni_serial_request_port,
	.config_port = qcom_geni_serial_config_port,
	.shutकरोwn = qcom_geni_serial_shutकरोwn,
	.type = qcom_geni_serial_get_type,
	.set_mctrl = qcom_geni_serial_set_mctrl,
	.get_mctrl = qcom_geni_serial_get_mctrl,
#अगर_घोषित CONFIG_CONSOLE_POLL
	.poll_get_अक्षर	= qcom_geni_serial_get_अक्षर,
	.poll_put_अक्षर	= qcom_geni_serial_poll_put_अक्षर,
#पूर्ण_अगर
	.pm = qcom_geni_serial_pm,
पूर्ण;

अटल स्थिर काष्ठा uart_ops qcom_geni_uart_pops = अणु
	.tx_empty = qcom_geni_serial_tx_empty,
	.stop_tx = qcom_geni_serial_stop_tx,
	.start_tx = qcom_geni_serial_start_tx,
	.stop_rx = qcom_geni_serial_stop_rx,
	.set_termios = qcom_geni_serial_set_termios,
	.startup = qcom_geni_serial_startup,
	.request_port = qcom_geni_serial_request_port,
	.config_port = qcom_geni_serial_config_port,
	.shutकरोwn = qcom_geni_serial_shutकरोwn,
	.type = qcom_geni_serial_get_type,
	.set_mctrl = qcom_geni_serial_set_mctrl,
	.get_mctrl = qcom_geni_serial_get_mctrl,
	.pm = qcom_geni_serial_pm,
पूर्ण;

अटल पूर्णांक qcom_geni_serial_probe(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक ret = 0;
	पूर्णांक line = -1;
	काष्ठा qcom_geni_serial_port *port;
	काष्ठा uart_port *uport;
	काष्ठा resource *res;
	पूर्णांक irq;
	bool console = false;
	काष्ठा uart_driver *drv;

	अगर (of_device_is_compatible(pdev->dev.of_node, "qcom,geni-debug-uart"))
		console = true;

	अगर (console) अणु
		drv = &qcom_geni_console_driver;
		line = of_alias_get_id(pdev->dev.of_node, "serial");
	पूर्ण अन्यथा अणु
		drv = &qcom_geni_uart_driver;
		line = of_alias_get_id(pdev->dev.of_node, "hsuart");
	पूर्ण

	port = get_port_from_line(line, console);
	अगर (IS_ERR(port)) अणु
		dev_err(&pdev->dev, "Invalid line %d\n", line);
		वापस PTR_ERR(port);
	पूर्ण

	uport = &port->uport;
	/* Don't allow 2 drivers to access the same port */
	अगर (uport->निजी_data)
		वापस -ENODEV;

	uport->dev = &pdev->dev;
	port->se.dev = &pdev->dev;
	port->se.wrapper = dev_get_drvdata(pdev->dev.parent);
	port->se.clk = devm_clk_get(&pdev->dev, "se");
	अगर (IS_ERR(port->se.clk)) अणु
		ret = PTR_ERR(port->se.clk);
		dev_err(&pdev->dev, "Err getting SE Core clk %d\n", ret);
		वापस ret;
	पूर्ण

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (!res)
		वापस -EINVAL;
	uport->mapbase = res->start;

	port->tx_fअगरo_depth = DEF_FIFO_DEPTH_WORDS;
	port->rx_fअगरo_depth = DEF_FIFO_DEPTH_WORDS;
	port->tx_fअगरo_width = DEF_FIFO_WIDTH_BITS;

	अगर (!console) अणु
		port->rx_fअगरo = devm_kसुस्मृति(uport->dev,
			port->rx_fअगरo_depth, माप(u32), GFP_KERNEL);
		अगर (!port->rx_fअगरo)
			वापस -ENOMEM;
	पूर्ण

	ret = geni_icc_get(&port->se, शून्य);
	अगर (ret)
		वापस ret;
	port->se.icc_paths[GENI_TO_CORE].avg_bw = GENI_DEFAULT_BW;
	port->se.icc_paths[CPU_TO_GENI].avg_bw = GENI_DEFAULT_BW;

	/* Set BW क्रम रेजिस्टर access */
	ret = geni_icc_set_bw(&port->se);
	अगर (ret)
		वापस ret;

	port->name = devm_kaप्र_लिखो(uport->dev, GFP_KERNEL,
			"qcom_geni_serial_%s%d",
			uart_console(uport) ? "console" : "uart", uport->line);
	अगर (!port->name)
		वापस -ENOMEM;

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0)
		वापस irq;
	uport->irq = irq;
	uport->has_sysrq = IS_ENABLED(CONFIG_SERIAL_QCOM_GENI_CONSOLE);

	अगर (!console)
		port->wakeup_irq = platक्रमm_get_irq_optional(pdev, 1);

	अगर (of_property_पढ़ो_bool(pdev->dev.of_node, "rx-tx-swap"))
		port->rx_tx_swap = true;

	अगर (of_property_पढ़ो_bool(pdev->dev.of_node, "cts-rts-swap"))
		port->cts_rts_swap = true;

	ret = devm_pm_opp_set_clkname(&pdev->dev, "se");
	अगर (ret)
		वापस ret;
	/* OPP table is optional */
	ret = devm_pm_opp_of_add_table(&pdev->dev);
	अगर (ret && ret != -ENODEV) अणु
		dev_err(&pdev->dev, "invalid OPP table in device tree\n");
		वापस ret;
	पूर्ण

	port->निजी_data.drv = drv;
	uport->निजी_data = &port->निजी_data;
	platक्रमm_set_drvdata(pdev, port);
	port->handle_rx = console ? handle_rx_console : handle_rx_uart;

	ret = uart_add_one_port(drv, uport);
	अगर (ret)
		वापस ret;

	irq_set_status_flags(uport->irq, IRQ_NOAUTOEN);
	ret = devm_request_irq(uport->dev, uport->irq, qcom_geni_serial_isr,
			IRQF_TRIGGER_HIGH, port->name, uport);
	अगर (ret) अणु
		dev_err(uport->dev, "Failed to get IRQ ret %d\n", ret);
		uart_हटाओ_one_port(drv, uport);
		वापस ret;
	पूर्ण

	/*
	 * Set pm_runसमय status as ACTIVE so that wakeup_irq माला_लो
	 * enabled/disabled from dev_pm_arm_wake_irq during प्रणाली
	 * suspend/resume respectively.
	 */
	pm_runसमय_set_active(&pdev->dev);

	अगर (port->wakeup_irq > 0) अणु
		device_init_wakeup(&pdev->dev, true);
		ret = dev_pm_set_dedicated_wake_irq(&pdev->dev,
						port->wakeup_irq);
		अगर (ret) अणु
			device_init_wakeup(&pdev->dev, false);
			uart_हटाओ_one_port(drv, uport);
			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक qcom_geni_serial_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा qcom_geni_serial_port *port = platक्रमm_get_drvdata(pdev);
	काष्ठा uart_driver *drv = port->निजी_data.drv;

	dev_pm_clear_wake_irq(&pdev->dev);
	device_init_wakeup(&pdev->dev, false);
	uart_हटाओ_one_port(drv, &port->uport);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused qcom_geni_serial_sys_suspend(काष्ठा device *dev)
अणु
	काष्ठा qcom_geni_serial_port *port = dev_get_drvdata(dev);
	काष्ठा uart_port *uport = &port->uport;
	काष्ठा qcom_geni_निजी_data *निजी_data = uport->निजी_data;

	/*
	 * This is करोne so we can hit the lowest possible state in suspend
	 * even with no_console_suspend
	 */
	अगर (uart_console(uport)) अणु
		geni_icc_set_tag(&port->se, 0x3);
		geni_icc_set_bw(&port->se);
	पूर्ण
	वापस uart_suspend_port(निजी_data->drv, uport);
पूर्ण

अटल पूर्णांक __maybe_unused qcom_geni_serial_sys_resume(काष्ठा device *dev)
अणु
	पूर्णांक ret;
	काष्ठा qcom_geni_serial_port *port = dev_get_drvdata(dev);
	काष्ठा uart_port *uport = &port->uport;
	काष्ठा qcom_geni_निजी_data *निजी_data = uport->निजी_data;

	ret = uart_resume_port(निजी_data->drv, uport);
	अगर (uart_console(uport)) अणु
		geni_icc_set_tag(&port->se, 0x7);
		geni_icc_set_bw(&port->se);
	पूर्ण
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops qcom_geni_serial_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(qcom_geni_serial_sys_suspend,
					qcom_geni_serial_sys_resume)
पूर्ण;

अटल स्थिर काष्ठा of_device_id qcom_geni_serial_match_table[] = अणु
	अणु .compatible = "qcom,geni-debug-uart", पूर्ण,
	अणु .compatible = "qcom,geni-uart", पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, qcom_geni_serial_match_table);

अटल काष्ठा platक्रमm_driver qcom_geni_serial_platक्रमm_driver = अणु
	.हटाओ = qcom_geni_serial_हटाओ,
	.probe = qcom_geni_serial_probe,
	.driver = अणु
		.name = "qcom_geni_serial",
		.of_match_table = qcom_geni_serial_match_table,
		.pm = &qcom_geni_serial_pm_ops,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init qcom_geni_serial_init(व्योम)
अणु
	पूर्णांक ret;

	ret = console_रेजिस्टर(&qcom_geni_console_driver);
	अगर (ret)
		वापस ret;

	ret = uart_रेजिस्टर_driver(&qcom_geni_uart_driver);
	अगर (ret) अणु
		console_unरेजिस्टर(&qcom_geni_console_driver);
		वापस ret;
	पूर्ण

	ret = platक्रमm_driver_रेजिस्टर(&qcom_geni_serial_platक्रमm_driver);
	अगर (ret) अणु
		console_unरेजिस्टर(&qcom_geni_console_driver);
		uart_unरेजिस्टर_driver(&qcom_geni_uart_driver);
	पूर्ण
	वापस ret;
पूर्ण
module_init(qcom_geni_serial_init);

अटल व्योम __निकास qcom_geni_serial_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&qcom_geni_serial_platक्रमm_driver);
	console_unरेजिस्टर(&qcom_geni_console_driver);
	uart_unरेजिस्टर_driver(&qcom_geni_uart_driver);
पूर्ण
module_निकास(qcom_geni_serial_निकास);

MODULE_DESCRIPTION("Serial driver for GENI based QUP cores");
MODULE_LICENSE("GPL v2");
