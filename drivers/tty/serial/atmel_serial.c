<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 *  Driver क्रम Aपंचांगel AT91 Serial ports
 *  Copyright (C) 2003 Rick Bronson
 *
 *  Based on drivers/अक्षर/serial_sa1100.c, by Deep Blue Solutions Ltd.
 *  Based on drivers/अक्षर/serial.c, by Linus Torvalds, Theoकरोre Ts'o.
 *
 *  DMA support added by Chip Coldwell.
 */
#समावेश <linux/tty.h>
#समावेश <linux/ioport.h>
#समावेश <linux/slab.h>
#समावेश <linux/init.h>
#समावेश <linux/serial.h>
#समावेश <linux/clk.h>
#समावेश <linux/console.h>
#समावेश <linux/sysrq.h>
#समावेश <linux/tty_flip.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/dmaengine.h>
#समावेश <linux/aपंचांगel_pdc.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/platक्रमm_data/aपंचांगel.h>
#समावेश <linux/समयr.h>
#समावेश <linux/err.h>
#समावेश <linux/irq.h>
#समावेश <linux/suspend.h>
#समावेश <linux/mm.h>

#समावेश <यंत्र/भाग64.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/ioctls.h>

#घोषणा PDC_BUFFER_SIZE		512
/* Revisit: We should calculate this based on the actual port settings */
#घोषणा PDC_RX_TIMEOUT		(3 * 10)		/* 3 bytes */

/* The minium number of data FIFOs should be able to contain */
#घोषणा ATMEL_MIN_FIFO_SIZE	8
/*
 * These two offsets are substracted from the RX FIFO size to define the RTS
 * high and low thresholds
 */
#घोषणा ATMEL_RTS_HIGH_OFFSET	16
#घोषणा ATMEL_RTS_LOW_OFFSET	20

#समावेश <linux/serial_core.h>

#समावेश "serial_mctrl_gpio.h"
#समावेश "atmel_serial.h"

अटल व्योम aपंचांगel_start_rx(काष्ठा uart_port *port);
अटल व्योम aपंचांगel_stop_rx(काष्ठा uart_port *port);

#अगर_घोषित CONFIG_SERIAL_ATMEL_TTYAT

/* Use device name ttyAT, major 204 and minor 154-169.  This is necessary अगर we
 * should coexist with the 8250 driver, such as अगर we have an बाह्यal 16C550
 * UART. */
#घोषणा SERIAL_ATMEL_MAJOR	204
#घोषणा MINOR_START		154
#घोषणा ATMEL_DEVICENAME	"ttyAT"

#अन्यथा

/* Use device name ttyS, major 4, minor 64-68.  This is the usual serial port
 * name, but it is legally reserved क्रम the 8250 driver. */
#घोषणा SERIAL_ATMEL_MAJOR	TTY_MAJOR
#घोषणा MINOR_START		64
#घोषणा ATMEL_DEVICENAME	"ttyS"

#पूर्ण_अगर

#घोषणा ATMEL_ISR_PASS_LIMIT	256

काष्ठा aपंचांगel_dma_buffer अणु
	अचिन्हित अक्षर	*buf;
	dma_addr_t	dma_addr;
	अचिन्हित पूर्णांक	dma_size;
	अचिन्हित पूर्णांक	ofs;
पूर्ण;

काष्ठा aपंचांगel_uart_अक्षर अणु
	u16		status;
	u16		ch;
पूर्ण;

/*
 * Be careful, the real size of the ring buffer is
 * माप(aपंचांगel_uart_अक्षर) * ATMEL_SERIAL_RINGSIZE. It means that ring buffer
 * can contain up to 1024 अक्षरacters in PIO mode and up to 4096 अक्षरacters in
 * DMA mode.
 */
#घोषणा ATMEL_SERIAL_RINGSIZE 1024

/*
 * at91: 6 USARTs and one DBGU port (SAM9260)
 * samx7: 3 USARTs and 5 UARTs
 */
#घोषणा ATMEL_MAX_UART		8

/*
 * We wrap our port काष्ठाure around the generic uart_port.
 */
काष्ठा aपंचांगel_uart_port अणु
	काष्ठा uart_port	uart;		/* uart */
	काष्ठा clk		*clk;		/* uart घड़ी */
	पूर्णांक			may_wakeup;	/* cached value of device_may_wakeup क्रम बार we need to disable it */
	u32			backup_imr;	/* IMR saved during suspend */
	पूर्णांक			अवरोध_active;	/* अवरोध being received */

	bool			use_dma_rx;	/* enable DMA receiver */
	bool			use_pdc_rx;	/* enable PDC receiver */
	लघु			pdc_rx_idx;	/* current PDC RX buffer */
	काष्ठा aपंचांगel_dma_buffer	pdc_rx[2];	/* PDC receier */

	bool			use_dma_tx;     /* enable DMA transmitter */
	bool			use_pdc_tx;	/* enable PDC transmitter */
	काष्ठा aपंचांगel_dma_buffer	pdc_tx;		/* PDC transmitter */

	spinlock_t			lock_tx;	/* port lock */
	spinlock_t			lock_rx;	/* port lock */
	काष्ठा dma_chan			*chan_tx;
	काष्ठा dma_chan			*chan_rx;
	काष्ठा dma_async_tx_descriptor	*desc_tx;
	काष्ठा dma_async_tx_descriptor	*desc_rx;
	dma_cookie_t			cookie_tx;
	dma_cookie_t			cookie_rx;
	काष्ठा scatterlist		sg_tx;
	काष्ठा scatterlist		sg_rx;
	काष्ठा tasklet_काष्ठा	tasklet_rx;
	काष्ठा tasklet_काष्ठा	tasklet_tx;
	atomic_t		tasklet_shutकरोwn;
	अचिन्हित पूर्णांक		irq_status_prev;
	अचिन्हित पूर्णांक		tx_len;

	काष्ठा circ_buf		rx_ring;

	काष्ठा mctrl_gpios	*gpios;
	u32			backup_mode;	/* MR saved during iso7816 operations */
	u32			backup_brgr;	/* BRGR saved during iso7816 operations */
	अचिन्हित पूर्णांक		tx_करोne_mask;
	u32			fअगरo_size;
	u32			rts_high;
	u32			rts_low;
	bool			ms_irq_enabled;
	u32			rtor;	/* address of receiver समयout रेजिस्टर अगर it exists */
	bool			has_frac_baudrate;
	bool			has_hw_समयr;
	काष्ठा समयr_list	uart_समयr;

	bool			tx_stopped;
	bool			suspended;
	अचिन्हित पूर्णांक		pending;
	अचिन्हित पूर्णांक		pending_status;
	spinlock_t		lock_suspended;

	bool			hd_start_rx;	/* can start RX during half-duplex operation */

	/* ISO7816 */
	अचिन्हित पूर्णांक		fidi_min;
	अचिन्हित पूर्णांक		fidi_max;

#अगर_घोषित CONFIG_PM
	काष्ठा अणु
		u32		cr;
		u32		mr;
		u32		imr;
		u32		brgr;
		u32		rtor;
		u32		ttgr;
		u32		fmr;
		u32		fimr;
	पूर्ण cache;
#पूर्ण_अगर

	पूर्णांक (*prepare_rx)(काष्ठा uart_port *port);
	पूर्णांक (*prepare_tx)(काष्ठा uart_port *port);
	व्योम (*schedule_rx)(काष्ठा uart_port *port);
	व्योम (*schedule_tx)(काष्ठा uart_port *port);
	व्योम (*release_rx)(काष्ठा uart_port *port);
	व्योम (*release_tx)(काष्ठा uart_port *port);
पूर्ण;

अटल काष्ठा aपंचांगel_uart_port aपंचांगel_ports[ATMEL_MAX_UART];
अटल DECLARE_BITMAP(aपंचांगel_ports_in_use, ATMEL_MAX_UART);

#अगर defined(CONFIG_OF)
अटल स्थिर काष्ठा of_device_id aपंचांगel_serial_dt_ids[] = अणु
	अणु .compatible = "atmel,at91rm9200-usart-serial" पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
#पूर्ण_अगर

अटल अंतरभूत काष्ठा aपंचांगel_uart_port *
to_aपंचांगel_uart_port(काष्ठा uart_port *uart)
अणु
	वापस container_of(uart, काष्ठा aपंचांगel_uart_port, uart);
पूर्ण

अटल अंतरभूत u32 aपंचांगel_uart_पढ़ोl(काष्ठा uart_port *port, u32 reg)
अणु
	वापस __raw_पढ़ोl(port->membase + reg);
पूर्ण

अटल अंतरभूत व्योम aपंचांगel_uart_ग_लिखोl(काष्ठा uart_port *port, u32 reg, u32 value)
अणु
	__raw_ग_लिखोl(value, port->membase + reg);
पूर्ण

अटल अंतरभूत u8 aपंचांगel_uart_पढ़ो_अक्षर(काष्ठा uart_port *port)
अणु
	वापस __raw_पढ़ोb(port->membase + ATMEL_US_RHR);
पूर्ण

अटल अंतरभूत व्योम aपंचांगel_uart_ग_लिखो_अक्षर(काष्ठा uart_port *port, u8 value)
अणु
	__raw_ग_लिखोb(value, port->membase + ATMEL_US_THR);
पूर्ण

अटल अंतरभूत पूर्णांक aपंचांगel_uart_is_half_duplex(काष्ठा uart_port *port)
अणु
	वापस ((port->rs485.flags & SER_RS485_ENABLED) &&
		!(port->rs485.flags & SER_RS485_RX_DURING_TX)) ||
		(port->iso7816.flags & SER_ISO7816_ENABLED);
पूर्ण

#अगर_घोषित CONFIG_SERIAL_ATMEL_PDC
अटल bool aपंचांगel_use_pdc_rx(काष्ठा uart_port *port)
अणु
	काष्ठा aपंचांगel_uart_port *aपंचांगel_port = to_aपंचांगel_uart_port(port);

	वापस aपंचांगel_port->use_pdc_rx;
पूर्ण

अटल bool aपंचांगel_use_pdc_tx(काष्ठा uart_port *port)
अणु
	काष्ठा aपंचांगel_uart_port *aपंचांगel_port = to_aपंचांगel_uart_port(port);

	वापस aपंचांगel_port->use_pdc_tx;
पूर्ण
#अन्यथा
अटल bool aपंचांगel_use_pdc_rx(काष्ठा uart_port *port)
अणु
	वापस false;
पूर्ण

अटल bool aपंचांगel_use_pdc_tx(काष्ठा uart_port *port)
अणु
	वापस false;
पूर्ण
#पूर्ण_अगर

अटल bool aपंचांगel_use_dma_tx(काष्ठा uart_port *port)
अणु
	काष्ठा aपंचांगel_uart_port *aपंचांगel_port = to_aपंचांगel_uart_port(port);

	वापस aपंचांगel_port->use_dma_tx;
पूर्ण

अटल bool aपंचांगel_use_dma_rx(काष्ठा uart_port *port)
अणु
	काष्ठा aपंचांगel_uart_port *aपंचांगel_port = to_aपंचांगel_uart_port(port);

	वापस aपंचांगel_port->use_dma_rx;
पूर्ण

अटल bool aपंचांगel_use_fअगरo(काष्ठा uart_port *port)
अणु
	काष्ठा aपंचांगel_uart_port *aपंचांगel_port = to_aपंचांगel_uart_port(port);

	वापस aपंचांगel_port->fअगरo_size;
पूर्ण

अटल व्योम aपंचांगel_tasklet_schedule(काष्ठा aपंचांगel_uart_port *aपंचांगel_port,
				   काष्ठा tasklet_काष्ठा *t)
अणु
	अगर (!atomic_पढ़ो(&aपंचांगel_port->tasklet_shutकरोwn))
		tasklet_schedule(t);
पूर्ण

/* Enable or disable the rs485 support */
अटल पूर्णांक aपंचांगel_config_rs485(काष्ठा uart_port *port,
			      काष्ठा serial_rs485 *rs485conf)
अणु
	काष्ठा aपंचांगel_uart_port *aपंचांगel_port = to_aपंचांगel_uart_port(port);
	अचिन्हित पूर्णांक mode;

	/* Disable पूर्णांकerrupts */
	aपंचांगel_uart_ग_लिखोl(port, ATMEL_US_IDR, aपंचांगel_port->tx_करोne_mask);

	mode = aपंचांगel_uart_पढ़ोl(port, ATMEL_US_MR);

	/* Resetting serial mode to RS232 (0x0) */
	mode &= ~ATMEL_US_USMODE;

	port->rs485 = *rs485conf;

	अगर (rs485conf->flags & SER_RS485_ENABLED) अणु
		dev_dbg(port->dev, "Setting UART to RS485\n");
		अगर (port->rs485.flags & SER_RS485_RX_DURING_TX)
			aपंचांगel_port->tx_करोne_mask = ATMEL_US_TXRDY;
		अन्यथा
			aपंचांगel_port->tx_करोne_mask = ATMEL_US_TXEMPTY;

		aपंचांगel_uart_ग_लिखोl(port, ATMEL_US_TTGR,
				  rs485conf->delay_rts_after_send);
		mode |= ATMEL_US_USMODE_RS485;
	पूर्ण अन्यथा अणु
		dev_dbg(port->dev, "Setting UART to RS232\n");
		अगर (aपंचांगel_use_pdc_tx(port))
			aपंचांगel_port->tx_करोne_mask = ATMEL_US_ENDTX |
				ATMEL_US_TXBUFE;
		अन्यथा
			aपंचांगel_port->tx_करोne_mask = ATMEL_US_TXRDY;
	पूर्ण
	aपंचांगel_uart_ग_लिखोl(port, ATMEL_US_MR, mode);

	/* Enable पूर्णांकerrupts */
	aपंचांगel_uart_ग_लिखोl(port, ATMEL_US_IER, aपंचांगel_port->tx_करोne_mask);

	वापस 0;
पूर्ण

अटल अचिन्हित पूर्णांक aपंचांगel_calc_cd(काष्ठा uart_port *port,
				  काष्ठा serial_iso7816 *iso7816conf)
अणु
	काष्ठा aपंचांगel_uart_port *aपंचांगel_port = to_aपंचांगel_uart_port(port);
	अचिन्हित पूर्णांक cd;
	u64 mck_rate;

	mck_rate = (u64)clk_get_rate(aपंचांगel_port->clk);
	करो_भाग(mck_rate, iso7816conf->clk);
	cd = mck_rate;
	वापस cd;
पूर्ण

अटल अचिन्हित पूर्णांक aपंचांगel_calc_fidi(काष्ठा uart_port *port,
				    काष्ठा serial_iso7816 *iso7816conf)
अणु
	u64 fidi = 0;

	अगर (iso7816conf->sc_fi && iso7816conf->sc_di) अणु
		fidi = (u64)iso7816conf->sc_fi;
		करो_भाग(fidi, iso7816conf->sc_di);
	पूर्ण
	वापस (u32)fidi;
पूर्ण

/* Enable or disable the iso7816 support */
/* Called with पूर्णांकerrupts disabled */
अटल पूर्णांक aपंचांगel_config_iso7816(काष्ठा uart_port *port,
				काष्ठा serial_iso7816 *iso7816conf)
अणु
	काष्ठा aपंचांगel_uart_port *aपंचांगel_port = to_aपंचांगel_uart_port(port);
	अचिन्हित पूर्णांक mode;
	अचिन्हित पूर्णांक cd, fidi;
	पूर्णांक ret = 0;

	/* Disable पूर्णांकerrupts */
	aपंचांगel_uart_ग_लिखोl(port, ATMEL_US_IDR, aपंचांगel_port->tx_करोne_mask);

	mode = aपंचांगel_uart_पढ़ोl(port, ATMEL_US_MR);

	अगर (iso7816conf->flags & SER_ISO7816_ENABLED) अणु
		mode &= ~ATMEL_US_USMODE;

		अगर (iso7816conf->tg > 255) अणु
			dev_err(port->dev, "ISO7816: Timeguard exceeding 255\n");
			स_रखो(iso7816conf, 0, माप(काष्ठा serial_iso7816));
			ret = -EINVAL;
			जाओ err_out;
		पूर्ण

		अगर ((iso7816conf->flags & SER_ISO7816_T_PARAM)
		    == SER_ISO7816_T(0)) अणु
			mode |= ATMEL_US_USMODE_ISO7816_T0 | ATMEL_US_DSNACK;
		पूर्ण अन्यथा अगर ((iso7816conf->flags & SER_ISO7816_T_PARAM)
			   == SER_ISO7816_T(1)) अणु
			mode |= ATMEL_US_USMODE_ISO7816_T1 | ATMEL_US_INACK;
		पूर्ण अन्यथा अणु
			dev_err(port->dev, "ISO7816: Type not supported\n");
			स_रखो(iso7816conf, 0, माप(काष्ठा serial_iso7816));
			ret = -EINVAL;
			जाओ err_out;
		पूर्ण

		mode &= ~(ATMEL_US_USCLKS | ATMEL_US_NBSTOP | ATMEL_US_PAR);

		/* select mck घड़ी, and output  */
		mode |= ATMEL_US_USCLKS_MCK | ATMEL_US_CLKO;
		/* set parity क्रम normal/inverse mode + max iterations */
		mode |= ATMEL_US_PAR_EVEN | ATMEL_US_NBSTOP_1 | ATMEL_US_MAX_ITER(3);

		cd = aपंचांगel_calc_cd(port, iso7816conf);
		fidi = aपंचांगel_calc_fidi(port, iso7816conf);
		अगर (fidi == 0) अणु
			dev_warn(port->dev, "ISO7816 fidi = 0, Generator generates no signal\n");
		पूर्ण अन्यथा अगर (fidi < aपंचांगel_port->fidi_min
			   || fidi > aपंचांगel_port->fidi_max) अणु
			dev_err(port->dev, "ISO7816 fidi = %u, value not supported\n", fidi);
			स_रखो(iso7816conf, 0, माप(काष्ठा serial_iso7816));
			ret = -EINVAL;
			जाओ err_out;
		पूर्ण

		अगर (!(port->iso7816.flags & SER_ISO7816_ENABLED)) अणु
			/* port not yet in iso7816 mode: store configuration */
			aपंचांगel_port->backup_mode = aपंचांगel_uart_पढ़ोl(port, ATMEL_US_MR);
			aपंचांगel_port->backup_brgr = aपंचांगel_uart_पढ़ोl(port, ATMEL_US_BRGR);
		पूर्ण

		aपंचांगel_uart_ग_लिखोl(port, ATMEL_US_TTGR, iso7816conf->tg);
		aपंचांगel_uart_ग_लिखोl(port, ATMEL_US_BRGR, cd);
		aपंचांगel_uart_ग_लिखोl(port, ATMEL_US_FIDI, fidi);

		aपंचांगel_uart_ग_लिखोl(port, ATMEL_US_CR, ATMEL_US_TXDIS | ATMEL_US_RXEN);
		aपंचांगel_port->tx_करोne_mask = ATMEL_US_TXEMPTY | ATMEL_US_NACK | ATMEL_US_ITERATION;
	पूर्ण अन्यथा अणु
		dev_dbg(port->dev, "Setting UART back to RS232\n");
		/* back to last RS232 settings */
		mode = aपंचांगel_port->backup_mode;
		स_रखो(iso7816conf, 0, माप(काष्ठा serial_iso7816));
		aपंचांगel_uart_ग_लिखोl(port, ATMEL_US_TTGR, 0);
		aपंचांगel_uart_ग_लिखोl(port, ATMEL_US_BRGR, aपंचांगel_port->backup_brgr);
		aपंचांगel_uart_ग_लिखोl(port, ATMEL_US_FIDI, 0x174);

		अगर (aपंचांगel_use_pdc_tx(port))
			aपंचांगel_port->tx_करोne_mask = ATMEL_US_ENDTX |
						   ATMEL_US_TXBUFE;
		अन्यथा
			aपंचांगel_port->tx_करोne_mask = ATMEL_US_TXRDY;
	पूर्ण

	port->iso7816 = *iso7816conf;

	aपंचांगel_uart_ग_लिखोl(port, ATMEL_US_MR, mode);

err_out:
	/* Enable पूर्णांकerrupts */
	aपंचांगel_uart_ग_लिखोl(port, ATMEL_US_IER, aपंचांगel_port->tx_करोne_mask);

	वापस ret;
पूर्ण

/*
 * Return TIOCSER_TEMT when transmitter FIFO and Shअगरt रेजिस्टर is empty.
 */
अटल u_पूर्णांक aपंचांगel_tx_empty(काष्ठा uart_port *port)
अणु
	काष्ठा aपंचांगel_uart_port *aपंचांगel_port = to_aपंचांगel_uart_port(port);

	अगर (aपंचांगel_port->tx_stopped)
		वापस TIOCSER_TEMT;
	वापस (aपंचांगel_uart_पढ़ोl(port, ATMEL_US_CSR) & ATMEL_US_TXEMPTY) ?
		TIOCSER_TEMT :
		0;
पूर्ण

/*
 * Set state of the modem control output lines
 */
अटल व्योम aपंचांगel_set_mctrl(काष्ठा uart_port *port, u_पूर्णांक mctrl)
अणु
	अचिन्हित पूर्णांक control = 0;
	अचिन्हित पूर्णांक mode = aपंचांगel_uart_पढ़ोl(port, ATMEL_US_MR);
	अचिन्हित पूर्णांक rts_छोड़ोd, rts_पढ़ोy;
	काष्ठा aपंचांगel_uart_port *aपंचांगel_port = to_aपंचांगel_uart_port(port);

	/* override mode to RS485 अगर needed, otherwise keep the current mode */
	अगर (port->rs485.flags & SER_RS485_ENABLED) अणु
		aपंचांगel_uart_ग_लिखोl(port, ATMEL_US_TTGR,
				  port->rs485.delay_rts_after_send);
		mode &= ~ATMEL_US_USMODE;
		mode |= ATMEL_US_USMODE_RS485;
	पूर्ण

	/* set the RTS line state according to the mode */
	अगर ((mode & ATMEL_US_USMODE) == ATMEL_US_USMODE_HWHS) अणु
		/* क्रमce RTS line to high level */
		rts_छोड़ोd = ATMEL_US_RTSEN;

		/* give the control of the RTS line back to the hardware */
		rts_पढ़ोy = ATMEL_US_RTSDIS;
	पूर्ण अन्यथा अणु
		/* क्रमce RTS line to high level */
		rts_छोड़ोd = ATMEL_US_RTSDIS;

		/* क्रमce RTS line to low level */
		rts_पढ़ोy = ATMEL_US_RTSEN;
	पूर्ण

	अगर (mctrl & TIOCM_RTS)
		control |= rts_पढ़ोy;
	अन्यथा
		control |= rts_छोड़ोd;

	अगर (mctrl & TIOCM_DTR)
		control |= ATMEL_US_DTREN;
	अन्यथा
		control |= ATMEL_US_DTRDIS;

	aपंचांगel_uart_ग_लिखोl(port, ATMEL_US_CR, control);

	mctrl_gpio_set(aपंचांगel_port->gpios, mctrl);

	/* Local loopback mode? */
	mode &= ~ATMEL_US_CHMODE;
	अगर (mctrl & TIOCM_LOOP)
		mode |= ATMEL_US_CHMODE_LOC_LOOP;
	अन्यथा
		mode |= ATMEL_US_CHMODE_NORMAL;

	aपंचांगel_uart_ग_लिखोl(port, ATMEL_US_MR, mode);
पूर्ण

/*
 * Get state of the modem control input lines
 */
अटल u_पूर्णांक aपंचांगel_get_mctrl(काष्ठा uart_port *port)
अणु
	काष्ठा aपंचांगel_uart_port *aपंचांगel_port = to_aपंचांगel_uart_port(port);
	अचिन्हित पूर्णांक ret = 0, status;

	status = aपंचांगel_uart_पढ़ोl(port, ATMEL_US_CSR);

	/*
	 * The control संकेतs are active low.
	 */
	अगर (!(status & ATMEL_US_DCD))
		ret |= TIOCM_CD;
	अगर (!(status & ATMEL_US_CTS))
		ret |= TIOCM_CTS;
	अगर (!(status & ATMEL_US_DSR))
		ret |= TIOCM_DSR;
	अगर (!(status & ATMEL_US_RI))
		ret |= TIOCM_RI;

	वापस mctrl_gpio_get(aपंचांगel_port->gpios, &ret);
पूर्ण

/*
 * Stop transmitting.
 */
अटल व्योम aपंचांगel_stop_tx(काष्ठा uart_port *port)
अणु
	काष्ठा aपंचांगel_uart_port *aपंचांगel_port = to_aपंचांगel_uart_port(port);

	अगर (aपंचांगel_use_pdc_tx(port)) अणु
		/* disable PDC transmit */
		aपंचांगel_uart_ग_लिखोl(port, ATMEL_PDC_PTCR, ATMEL_PDC_TXTDIS);
	पूर्ण

	/*
	 * Disable the transmitter.
	 * This is mandatory when DMA is used, otherwise the DMA buffer
	 * is fully transmitted.
	 */
	aपंचांगel_uart_ग_लिखोl(port, ATMEL_US_CR, ATMEL_US_TXDIS);
	aपंचांगel_port->tx_stopped = true;

	/* Disable पूर्णांकerrupts */
	aपंचांगel_uart_ग_लिखोl(port, ATMEL_US_IDR, aपंचांगel_port->tx_करोne_mask);

	अगर (aपंचांगel_uart_is_half_duplex(port))
		अगर (!atomic_पढ़ो(&aपंचांगel_port->tasklet_shutकरोwn))
			aपंचांगel_start_rx(port);

पूर्ण

/*
 * Start transmitting.
 */
अटल व्योम aपंचांगel_start_tx(काष्ठा uart_port *port)
अणु
	काष्ठा aपंचांगel_uart_port *aपंचांगel_port = to_aपंचांगel_uart_port(port);

	अगर (aपंचांगel_use_pdc_tx(port) && (aपंचांगel_uart_पढ़ोl(port, ATMEL_PDC_PTSR)
				       & ATMEL_PDC_TXTEN))
		/* The transmitter is alपढ़ोy running.  Yes, we
		   really need this.*/
		वापस;

	अगर (aपंचांगel_use_pdc_tx(port) || aपंचांगel_use_dma_tx(port))
		अगर (aपंचांगel_uart_is_half_duplex(port))
			aपंचांगel_stop_rx(port);

	अगर (aपंचांगel_use_pdc_tx(port))
		/* re-enable PDC transmit */
		aपंचांगel_uart_ग_लिखोl(port, ATMEL_PDC_PTCR, ATMEL_PDC_TXTEN);

	/* Enable पूर्णांकerrupts */
	aपंचांगel_uart_ग_लिखोl(port, ATMEL_US_IER, aपंचांगel_port->tx_करोne_mask);

	/* re-enable the transmitter */
	aपंचांगel_uart_ग_लिखोl(port, ATMEL_US_CR, ATMEL_US_TXEN);
	aपंचांगel_port->tx_stopped = false;
पूर्ण

/*
 * start receiving - port is in process of being खोलोed.
 */
अटल व्योम aपंचांगel_start_rx(काष्ठा uart_port *port)
अणु
	/* reset status and receiver */
	aपंचांगel_uart_ग_लिखोl(port, ATMEL_US_CR, ATMEL_US_RSTSTA);

	aपंचांगel_uart_ग_लिखोl(port, ATMEL_US_CR, ATMEL_US_RXEN);

	अगर (aपंचांगel_use_pdc_rx(port)) अणु
		/* enable PDC controller */
		aपंचांगel_uart_ग_लिखोl(port, ATMEL_US_IER,
				  ATMEL_US_ENDRX | ATMEL_US_TIMEOUT |
				  port->पढ़ो_status_mask);
		aपंचांगel_uart_ग_लिखोl(port, ATMEL_PDC_PTCR, ATMEL_PDC_RXTEN);
	पूर्ण अन्यथा अणु
		aपंचांगel_uart_ग_लिखोl(port, ATMEL_US_IER, ATMEL_US_RXRDY);
	पूर्ण
पूर्ण

/*
 * Stop receiving - port is in process of being बंदd.
 */
अटल व्योम aपंचांगel_stop_rx(काष्ठा uart_port *port)
अणु
	aपंचांगel_uart_ग_लिखोl(port, ATMEL_US_CR, ATMEL_US_RXDIS);

	अगर (aपंचांगel_use_pdc_rx(port)) अणु
		/* disable PDC receive */
		aपंचांगel_uart_ग_लिखोl(port, ATMEL_PDC_PTCR, ATMEL_PDC_RXTDIS);
		aपंचांगel_uart_ग_लिखोl(port, ATMEL_US_IDR,
				  ATMEL_US_ENDRX | ATMEL_US_TIMEOUT |
				  port->पढ़ो_status_mask);
	पूर्ण अन्यथा अणु
		aपंचांगel_uart_ग_लिखोl(port, ATMEL_US_IDR, ATMEL_US_RXRDY);
	पूर्ण
पूर्ण

/*
 * Enable modem status पूर्णांकerrupts
 */
अटल व्योम aपंचांगel_enable_ms(काष्ठा uart_port *port)
अणु
	काष्ठा aपंचांगel_uart_port *aपंचांगel_port = to_aपंचांगel_uart_port(port);
	uपूर्णांक32_t ier = 0;

	/*
	 * Interrupt should not be enabled twice
	 */
	अगर (aपंचांगel_port->ms_irq_enabled)
		वापस;

	aपंचांगel_port->ms_irq_enabled = true;

	अगर (!mctrl_gpio_to_gpiod(aपंचांगel_port->gpios, UART_GPIO_CTS))
		ier |= ATMEL_US_CTSIC;

	अगर (!mctrl_gpio_to_gpiod(aपंचांगel_port->gpios, UART_GPIO_DSR))
		ier |= ATMEL_US_DSRIC;

	अगर (!mctrl_gpio_to_gpiod(aपंचांगel_port->gpios, UART_GPIO_RI))
		ier |= ATMEL_US_RIIC;

	अगर (!mctrl_gpio_to_gpiod(aपंचांगel_port->gpios, UART_GPIO_DCD))
		ier |= ATMEL_US_DCDIC;

	aपंचांगel_uart_ग_लिखोl(port, ATMEL_US_IER, ier);

	mctrl_gpio_enable_ms(aपंचांगel_port->gpios);
पूर्ण

/*
 * Disable modem status पूर्णांकerrupts
 */
अटल व्योम aपंचांगel_disable_ms(काष्ठा uart_port *port)
अणु
	काष्ठा aपंचांगel_uart_port *aपंचांगel_port = to_aपंचांगel_uart_port(port);
	uपूर्णांक32_t idr = 0;

	/*
	 * Interrupt should not be disabled twice
	 */
	अगर (!aपंचांगel_port->ms_irq_enabled)
		वापस;

	aपंचांगel_port->ms_irq_enabled = false;

	mctrl_gpio_disable_ms(aपंचांगel_port->gpios);

	अगर (!mctrl_gpio_to_gpiod(aपंचांगel_port->gpios, UART_GPIO_CTS))
		idr |= ATMEL_US_CTSIC;

	अगर (!mctrl_gpio_to_gpiod(aपंचांगel_port->gpios, UART_GPIO_DSR))
		idr |= ATMEL_US_DSRIC;

	अगर (!mctrl_gpio_to_gpiod(aपंचांगel_port->gpios, UART_GPIO_RI))
		idr |= ATMEL_US_RIIC;

	अगर (!mctrl_gpio_to_gpiod(aपंचांगel_port->gpios, UART_GPIO_DCD))
		idr |= ATMEL_US_DCDIC;

	aपंचांगel_uart_ग_लिखोl(port, ATMEL_US_IDR, idr);
पूर्ण

/*
 * Control the transmission of a अवरोध संकेत
 */
अटल व्योम aपंचांगel_अवरोध_ctl(काष्ठा uart_port *port, पूर्णांक अवरोध_state)
अणु
	अगर (अवरोध_state != 0)
		/* start अवरोध */
		aपंचांगel_uart_ग_लिखोl(port, ATMEL_US_CR, ATMEL_US_STTBRK);
	अन्यथा
		/* stop अवरोध */
		aपंचांगel_uart_ग_लिखोl(port, ATMEL_US_CR, ATMEL_US_STPBRK);
पूर्ण

/*
 * Stores the incoming अक्षरacter in the ring buffer
 */
अटल व्योम
aपंचांगel_buffer_rx_अक्षर(काष्ठा uart_port *port, अचिन्हित पूर्णांक status,
		     अचिन्हित पूर्णांक ch)
अणु
	काष्ठा aपंचांगel_uart_port *aपंचांगel_port = to_aपंचांगel_uart_port(port);
	काष्ठा circ_buf *ring = &aपंचांगel_port->rx_ring;
	काष्ठा aपंचांगel_uart_अक्षर *c;

	अगर (!CIRC_SPACE(ring->head, ring->tail, ATMEL_SERIAL_RINGSIZE))
		/* Buffer overflow, ignore अक्षर */
		वापस;

	c = &((काष्ठा aपंचांगel_uart_अक्षर *)ring->buf)[ring->head];
	c->status	= status;
	c->ch		= ch;

	/* Make sure the अक्षरacter is stored beक्रमe we update head. */
	smp_wmb();

	ring->head = (ring->head + 1) & (ATMEL_SERIAL_RINGSIZE - 1);
पूर्ण

/*
 * Deal with parity, framing and overrun errors.
 */
अटल व्योम aपंचांगel_pdc_rxerr(काष्ठा uart_port *port, अचिन्हित पूर्णांक status)
अणु
	/* clear error */
	aपंचांगel_uart_ग_लिखोl(port, ATMEL_US_CR, ATMEL_US_RSTSTA);

	अगर (status & ATMEL_US_RXBRK) अणु
		/* ignore side-effect */
		status &= ~(ATMEL_US_PARE | ATMEL_US_FRAME);
		port->icount.brk++;
	पूर्ण
	अगर (status & ATMEL_US_PARE)
		port->icount.parity++;
	अगर (status & ATMEL_US_FRAME)
		port->icount.frame++;
	अगर (status & ATMEL_US_OVRE)
		port->icount.overrun++;
पूर्ण

/*
 * Characters received (called from पूर्णांकerrupt handler)
 */
अटल व्योम aपंचांगel_rx_अक्षरs(काष्ठा uart_port *port)
अणु
	काष्ठा aपंचांगel_uart_port *aपंचांगel_port = to_aपंचांगel_uart_port(port);
	अचिन्हित पूर्णांक status, ch;

	status = aपंचांगel_uart_पढ़ोl(port, ATMEL_US_CSR);
	जबतक (status & ATMEL_US_RXRDY) अणु
		ch = aपंचांगel_uart_पढ़ो_अक्षर(port);

		/*
		 * note that the error handling code is
		 * out of the मुख्य execution path
		 */
		अगर (unlikely(status & (ATMEL_US_PARE | ATMEL_US_FRAME
				       | ATMEL_US_OVRE | ATMEL_US_RXBRK)
			     || aपंचांगel_port->अवरोध_active)) अणु

			/* clear error */
			aपंचांगel_uart_ग_लिखोl(port, ATMEL_US_CR, ATMEL_US_RSTSTA);

			अगर (status & ATMEL_US_RXBRK
			    && !aपंचांगel_port->अवरोध_active) अणु
				aपंचांगel_port->अवरोध_active = 1;
				aपंचांगel_uart_ग_लिखोl(port, ATMEL_US_IER,
						  ATMEL_US_RXBRK);
			पूर्ण अन्यथा अणु
				/*
				 * This is either the end-of-अवरोध
				 * condition or we've received at
				 * least one अक्षरacter without RXBRK
				 * being set. In both हालs, the next
				 * RXBRK will indicate start-of-अवरोध.
				 */
				aपंचांगel_uart_ग_लिखोl(port, ATMEL_US_IDR,
						  ATMEL_US_RXBRK);
				status &= ~ATMEL_US_RXBRK;
				aपंचांगel_port->अवरोध_active = 0;
			पूर्ण
		पूर्ण

		aपंचांगel_buffer_rx_अक्षर(port, status, ch);
		status = aपंचांगel_uart_पढ़ोl(port, ATMEL_US_CSR);
	पूर्ण

	aपंचांगel_tasklet_schedule(aपंचांगel_port, &aपंचांगel_port->tasklet_rx);
पूर्ण

/*
 * Transmit अक्षरacters (called from tasklet with TXRDY पूर्णांकerrupt
 * disabled)
 */
अटल व्योम aपंचांगel_tx_अक्षरs(काष्ठा uart_port *port)
अणु
	काष्ठा circ_buf *xmit = &port->state->xmit;
	काष्ठा aपंचांगel_uart_port *aपंचांगel_port = to_aपंचांगel_uart_port(port);

	अगर (port->x_अक्षर &&
	    (aपंचांगel_uart_पढ़ोl(port, ATMEL_US_CSR) & ATMEL_US_TXRDY)) अणु
		aपंचांगel_uart_ग_लिखो_अक्षर(port, port->x_अक्षर);
		port->icount.tx++;
		port->x_अक्षर = 0;
	पूर्ण
	अगर (uart_circ_empty(xmit) || uart_tx_stopped(port))
		वापस;

	जबतक (aपंचांगel_uart_पढ़ोl(port, ATMEL_US_CSR) & ATMEL_US_TXRDY) अणु
		aपंचांगel_uart_ग_लिखो_अक्षर(port, xmit->buf[xmit->tail]);
		xmit->tail = (xmit->tail + 1) & (UART_XMIT_SIZE - 1);
		port->icount.tx++;
		अगर (uart_circ_empty(xmit))
			अवरोध;
	पूर्ण

	अगर (uart_circ_अक्षरs_pending(xmit) < WAKEUP_CHARS)
		uart_ग_लिखो_wakeup(port);

	अगर (!uart_circ_empty(xmit)) अणु
		/* we still have अक्षरacters to transmit, so we should जारी
		 * transmitting them when TX is पढ़ोy, regardless of
		 * mode or duplनिकासy
		 */
		aपंचांगel_port->tx_करोne_mask |= ATMEL_US_TXRDY;

		/* Enable पूर्णांकerrupts */
		aपंचांगel_uart_ग_लिखोl(port, ATMEL_US_IER,
				  aपंचांगel_port->tx_करोne_mask);
	पूर्ण अन्यथा अणु
		अगर (aपंचांगel_uart_is_half_duplex(port))
			aपंचांगel_port->tx_करोne_mask &= ~ATMEL_US_TXRDY;
	पूर्ण
पूर्ण

अटल व्योम aपंचांगel_complete_tx_dma(व्योम *arg)
अणु
	काष्ठा aपंचांगel_uart_port *aपंचांगel_port = arg;
	काष्ठा uart_port *port = &aपंचांगel_port->uart;
	काष्ठा circ_buf *xmit = &port->state->xmit;
	काष्ठा dma_chan *chan = aपंचांगel_port->chan_tx;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&port->lock, flags);

	अगर (chan)
		dmaengine_terminate_all(chan);
	xmit->tail += aपंचांगel_port->tx_len;
	xmit->tail &= UART_XMIT_SIZE - 1;

	port->icount.tx += aपंचांगel_port->tx_len;

	spin_lock_irq(&aपंचांगel_port->lock_tx);
	async_tx_ack(aपंचांगel_port->desc_tx);
	aपंचांगel_port->cookie_tx = -EINVAL;
	aपंचांगel_port->desc_tx = शून्य;
	spin_unlock_irq(&aपंचांगel_port->lock_tx);

	अगर (uart_circ_अक्षरs_pending(xmit) < WAKEUP_CHARS)
		uart_ग_लिखो_wakeup(port);

	/*
	 * xmit is a circular buffer so, अगर we have just send data from
	 * xmit->tail to the end of xmit->buf, now we have to transmit the
	 * reमुख्यing data from the beginning of xmit->buf to xmit->head.
	 */
	अगर (!uart_circ_empty(xmit))
		aपंचांगel_tasklet_schedule(aपंचांगel_port, &aपंचांगel_port->tasklet_tx);
	अन्यथा अगर (aपंचांगel_uart_is_half_duplex(port)) अणु
		/*
		 * DMA करोne, re-enable TXEMPTY and संकेत that we can stop
		 * TX and start RX क्रम RS485
		 */
		aपंचांगel_port->hd_start_rx = true;
		aपंचांगel_uart_ग_लिखोl(port, ATMEL_US_IER,
				  aपंचांगel_port->tx_करोne_mask);
	पूर्ण

	spin_unlock_irqrestore(&port->lock, flags);
पूर्ण

अटल व्योम aपंचांगel_release_tx_dma(काष्ठा uart_port *port)
अणु
	काष्ठा aपंचांगel_uart_port *aपंचांगel_port = to_aपंचांगel_uart_port(port);
	काष्ठा dma_chan *chan = aपंचांगel_port->chan_tx;

	अगर (chan) अणु
		dmaengine_terminate_all(chan);
		dma_release_channel(chan);
		dma_unmap_sg(port->dev, &aपंचांगel_port->sg_tx, 1,
				DMA_TO_DEVICE);
	पूर्ण

	aपंचांगel_port->desc_tx = शून्य;
	aपंचांगel_port->chan_tx = शून्य;
	aपंचांगel_port->cookie_tx = -EINVAL;
पूर्ण

/*
 * Called from tasklet with TXRDY पूर्णांकerrupt is disabled.
 */
अटल व्योम aपंचांगel_tx_dma(काष्ठा uart_port *port)
अणु
	काष्ठा aपंचांगel_uart_port *aपंचांगel_port = to_aपंचांगel_uart_port(port);
	काष्ठा circ_buf *xmit = &port->state->xmit;
	काष्ठा dma_chan *chan = aपंचांगel_port->chan_tx;
	काष्ठा dma_async_tx_descriptor *desc;
	काष्ठा scatterlist sgl[2], *sg, *sg_tx = &aपंचांगel_port->sg_tx;
	अचिन्हित पूर्णांक tx_len, part1_len, part2_len, sg_len;
	dma_addr_t phys_addr;

	/* Make sure we have an idle channel */
	अगर (aपंचांगel_port->desc_tx != शून्य)
		वापस;

	अगर (!uart_circ_empty(xmit) && !uart_tx_stopped(port)) अणु
		/*
		 * DMA is idle now.
		 * Port xmit buffer is alपढ़ोy mapped,
		 * and it is one page... Just adjust
		 * offsets and lengths. Since it is a circular buffer,
		 * we have to transmit till the end, and then the rest.
		 * Take the port lock to get a
		 * consistent xmit buffer state.
		 */
		tx_len = CIRC_CNT_TO_END(xmit->head,
					 xmit->tail,
					 UART_XMIT_SIZE);

		अगर (aपंचांगel_port->fअगरo_size) अणु
			/* multi data mode */
			part1_len = (tx_len & ~0x3); /* DWORD access */
			part2_len = (tx_len & 0x3); /* BYTE access */
		पूर्ण अन्यथा अणु
			/* single data (legacy) mode */
			part1_len = 0;
			part2_len = tx_len; /* BYTE access only */
		पूर्ण

		sg_init_table(sgl, 2);
		sg_len = 0;
		phys_addr = sg_dma_address(sg_tx) + xmit->tail;
		अगर (part1_len) अणु
			sg = &sgl[sg_len++];
			sg_dma_address(sg) = phys_addr;
			sg_dma_len(sg) = part1_len;

			phys_addr += part1_len;
		पूर्ण

		अगर (part2_len) अणु
			sg = &sgl[sg_len++];
			sg_dma_address(sg) = phys_addr;
			sg_dma_len(sg) = part2_len;
		पूर्ण

		/*
		 * save tx_len so aपंचांगel_complete_tx_dma() will increase
		 * xmit->tail correctly
		 */
		aपंचांगel_port->tx_len = tx_len;

		desc = dmaengine_prep_slave_sg(chan,
					       sgl,
					       sg_len,
					       DMA_MEM_TO_DEV,
					       DMA_PREP_INTERRUPT |
					       DMA_CTRL_ACK);
		अगर (!desc) अणु
			dev_err(port->dev, "Failed to send via dma!\n");
			वापस;
		पूर्ण

		dma_sync_sg_क्रम_device(port->dev, sg_tx, 1, DMA_TO_DEVICE);

		aपंचांगel_port->desc_tx = desc;
		desc->callback = aपंचांगel_complete_tx_dma;
		desc->callback_param = aपंचांगel_port;
		aपंचांगel_port->cookie_tx = dmaengine_submit(desc);
	पूर्ण

	अगर (uart_circ_अक्षरs_pending(xmit) < WAKEUP_CHARS)
		uart_ग_लिखो_wakeup(port);
पूर्ण

अटल पूर्णांक aपंचांगel_prepare_tx_dma(काष्ठा uart_port *port)
अणु
	काष्ठा aपंचांगel_uart_port *aपंचांगel_port = to_aपंचांगel_uart_port(port);
	काष्ठा device *mfd_dev = port->dev->parent;
	dma_cap_mask_t		mask;
	काष्ठा dma_slave_config config;
	पूर्णांक ret, nent;

	dma_cap_zero(mask);
	dma_cap_set(DMA_SLAVE, mask);

	aपंचांगel_port->chan_tx = dma_request_slave_channel(mfd_dev, "tx");
	अगर (aपंचांगel_port->chan_tx == शून्य)
		जाओ chan_err;
	dev_info(port->dev, "using %s for tx DMA transfers\n",
		dma_chan_name(aपंचांगel_port->chan_tx));

	spin_lock_init(&aपंचांगel_port->lock_tx);
	sg_init_table(&aपंचांगel_port->sg_tx, 1);
	/* UART circular tx buffer is an aligned page. */
	BUG_ON(!PAGE_ALIGNED(port->state->xmit.buf));
	sg_set_page(&aपंचांगel_port->sg_tx,
			virt_to_page(port->state->xmit.buf),
			UART_XMIT_SIZE,
			offset_in_page(port->state->xmit.buf));
	nent = dma_map_sg(port->dev,
				&aपंचांगel_port->sg_tx,
				1,
				DMA_TO_DEVICE);

	अगर (!nent) अणु
		dev_dbg(port->dev, "need to release resource of dma\n");
		जाओ chan_err;
	पूर्ण अन्यथा अणु
		dev_dbg(port->dev, "%s: mapped %d@%p to %pad\n", __func__,
			sg_dma_len(&aपंचांगel_port->sg_tx),
			port->state->xmit.buf,
			&sg_dma_address(&aपंचांगel_port->sg_tx));
	पूर्ण

	/* Configure the slave DMA */
	स_रखो(&config, 0, माप(config));
	config.direction = DMA_MEM_TO_DEV;
	config.dst_addr_width = (aपंचांगel_port->fअगरo_size) ?
				DMA_SLAVE_BUSWIDTH_4_BYTES :
				DMA_SLAVE_BUSWIDTH_1_BYTE;
	config.dst_addr = port->mapbase + ATMEL_US_THR;
	config.dst_maxburst = 1;

	ret = dmaengine_slave_config(aपंचांगel_port->chan_tx,
				     &config);
	अगर (ret) अणु
		dev_err(port->dev, "DMA tx slave configuration failed\n");
		जाओ chan_err;
	पूर्ण

	वापस 0;

chan_err:
	dev_err(port->dev, "TX channel not available, switch to pio\n");
	aपंचांगel_port->use_dma_tx = false;
	अगर (aपंचांगel_port->chan_tx)
		aपंचांगel_release_tx_dma(port);
	वापस -EINVAL;
पूर्ण

अटल व्योम aपंचांगel_complete_rx_dma(व्योम *arg)
अणु
	काष्ठा uart_port *port = arg;
	काष्ठा aपंचांगel_uart_port *aपंचांगel_port = to_aपंचांगel_uart_port(port);

	aपंचांगel_tasklet_schedule(aपंचांगel_port, &aपंचांगel_port->tasklet_rx);
पूर्ण

अटल व्योम aपंचांगel_release_rx_dma(काष्ठा uart_port *port)
अणु
	काष्ठा aपंचांगel_uart_port *aपंचांगel_port = to_aपंचांगel_uart_port(port);
	काष्ठा dma_chan *chan = aपंचांगel_port->chan_rx;

	अगर (chan) अणु
		dmaengine_terminate_all(chan);
		dma_release_channel(chan);
		dma_unmap_sg(port->dev, &aपंचांगel_port->sg_rx, 1,
				DMA_FROM_DEVICE);
	पूर्ण

	aपंचांगel_port->desc_rx = शून्य;
	aपंचांगel_port->chan_rx = शून्य;
	aपंचांगel_port->cookie_rx = -EINVAL;
पूर्ण

अटल व्योम aपंचांगel_rx_from_dma(काष्ठा uart_port *port)
अणु
	काष्ठा aपंचांगel_uart_port *aपंचांगel_port = to_aपंचांगel_uart_port(port);
	काष्ठा tty_port *tport = &port->state->port;
	काष्ठा circ_buf *ring = &aपंचांगel_port->rx_ring;
	काष्ठा dma_chan *chan = aपंचांगel_port->chan_rx;
	काष्ठा dma_tx_state state;
	क्रमागत dma_status dmastat;
	माप_प्रकार count;


	/* Reset the UART समयout early so that we करोn't miss one */
	aपंचांगel_uart_ग_लिखोl(port, ATMEL_US_CR, ATMEL_US_STTTO);
	dmastat = dmaengine_tx_status(chan,
				aपंचांगel_port->cookie_rx,
				&state);
	/* Restart a new tasklet अगर DMA status is error */
	अगर (dmastat == DMA_ERROR) अणु
		dev_dbg(port->dev, "Get residue error, restart tasklet\n");
		aपंचांगel_uart_ग_लिखोl(port, ATMEL_US_IER, ATMEL_US_TIMEOUT);
		aपंचांगel_tasklet_schedule(aपंचांगel_port, &aपंचांगel_port->tasklet_rx);
		वापस;
	पूर्ण

	/* CPU claims ownership of RX DMA buffer */
	dma_sync_sg_क्रम_cpu(port->dev,
			    &aपंचांगel_port->sg_rx,
			    1,
			    DMA_FROM_DEVICE);

	/*
	 * ring->head poपूर्णांकs to the end of data alपढ़ोy written by the DMA.
	 * ring->tail poपूर्णांकs to the beginning of data to be पढ़ो by the
	 * framework.
	 * The current transfer size should not be larger than the dma buffer
	 * length.
	 */
	ring->head = sg_dma_len(&aपंचांगel_port->sg_rx) - state.residue;
	BUG_ON(ring->head > sg_dma_len(&aपंचांगel_port->sg_rx));
	/*
	 * At this poपूर्णांक ring->head may poपूर्णांक to the first byte right after the
	 * last byte of the dma buffer:
	 * 0 <= ring->head <= sg_dma_len(&aपंचांगel_port->sg_rx)
	 *
	 * However ring->tail must always poपूर्णांकs inside the dma buffer:
	 * 0 <= ring->tail <= sg_dma_len(&aपंचांगel_port->sg_rx) - 1
	 *
	 * Since we use a ring buffer, we have to handle the हाल
	 * where head is lower than tail. In such a हाल, we first पढ़ो from
	 * tail to the end of the buffer then reset tail.
	 */
	अगर (ring->head < ring->tail) अणु
		count = sg_dma_len(&aपंचांगel_port->sg_rx) - ring->tail;

		tty_insert_flip_string(tport, ring->buf + ring->tail, count);
		ring->tail = 0;
		port->icount.rx += count;
	पूर्ण

	/* Finally we पढ़ो data from tail to head */
	अगर (ring->tail < ring->head) अणु
		count = ring->head - ring->tail;

		tty_insert_flip_string(tport, ring->buf + ring->tail, count);
		/* Wrap ring->head अगर needed */
		अगर (ring->head >= sg_dma_len(&aपंचांगel_port->sg_rx))
			ring->head = 0;
		ring->tail = ring->head;
		port->icount.rx += count;
	पूर्ण

	/* USART retreives ownership of RX DMA buffer */
	dma_sync_sg_क्रम_device(port->dev,
			       &aपंचांगel_port->sg_rx,
			       1,
			       DMA_FROM_DEVICE);

	tty_flip_buffer_push(tport);

	aपंचांगel_uart_ग_लिखोl(port, ATMEL_US_IER, ATMEL_US_TIMEOUT);
पूर्ण

अटल पूर्णांक aपंचांगel_prepare_rx_dma(काष्ठा uart_port *port)
अणु
	काष्ठा aपंचांगel_uart_port *aपंचांगel_port = to_aपंचांगel_uart_port(port);
	काष्ठा device *mfd_dev = port->dev->parent;
	काष्ठा dma_async_tx_descriptor *desc;
	dma_cap_mask_t		mask;
	काष्ठा dma_slave_config config;
	काष्ठा circ_buf		*ring;
	पूर्णांक ret, nent;

	ring = &aपंचांगel_port->rx_ring;

	dma_cap_zero(mask);
	dma_cap_set(DMA_CYCLIC, mask);

	aपंचांगel_port->chan_rx = dma_request_slave_channel(mfd_dev, "rx");
	अगर (aपंचांगel_port->chan_rx == शून्य)
		जाओ chan_err;
	dev_info(port->dev, "using %s for rx DMA transfers\n",
		dma_chan_name(aपंचांगel_port->chan_rx));

	spin_lock_init(&aपंचांगel_port->lock_rx);
	sg_init_table(&aपंचांगel_port->sg_rx, 1);
	/* UART circular rx buffer is an aligned page. */
	BUG_ON(!PAGE_ALIGNED(ring->buf));
	sg_set_page(&aपंचांगel_port->sg_rx,
		    virt_to_page(ring->buf),
		    माप(काष्ठा aपंचांगel_uart_अक्षर) * ATMEL_SERIAL_RINGSIZE,
		    offset_in_page(ring->buf));
	nent = dma_map_sg(port->dev,
			  &aपंचांगel_port->sg_rx,
			  1,
			  DMA_FROM_DEVICE);

	अगर (!nent) अणु
		dev_dbg(port->dev, "need to release resource of dma\n");
		जाओ chan_err;
	पूर्ण अन्यथा अणु
		dev_dbg(port->dev, "%s: mapped %d@%p to %pad\n", __func__,
			sg_dma_len(&aपंचांगel_port->sg_rx),
			ring->buf,
			&sg_dma_address(&aपंचांगel_port->sg_rx));
	पूर्ण

	/* Configure the slave DMA */
	स_रखो(&config, 0, माप(config));
	config.direction = DMA_DEV_TO_MEM;
	config.src_addr_width = DMA_SLAVE_BUSWIDTH_1_BYTE;
	config.src_addr = port->mapbase + ATMEL_US_RHR;
	config.src_maxburst = 1;

	ret = dmaengine_slave_config(aपंचांगel_port->chan_rx,
				     &config);
	अगर (ret) अणु
		dev_err(port->dev, "DMA rx slave configuration failed\n");
		जाओ chan_err;
	पूर्ण
	/*
	 * Prepare a cyclic dma transfer, assign 2 descriptors,
	 * each one is half ring buffer size
	 */
	desc = dmaengine_prep_dma_cyclic(aपंचांगel_port->chan_rx,
					 sg_dma_address(&aपंचांगel_port->sg_rx),
					 sg_dma_len(&aपंचांगel_port->sg_rx),
					 sg_dma_len(&aपंचांगel_port->sg_rx)/2,
					 DMA_DEV_TO_MEM,
					 DMA_PREP_INTERRUPT);
	अगर (!desc) अणु
		dev_err(port->dev, "Preparing DMA cyclic failed\n");
		जाओ chan_err;
	पूर्ण
	desc->callback = aपंचांगel_complete_rx_dma;
	desc->callback_param = port;
	aपंचांगel_port->desc_rx = desc;
	aपंचांगel_port->cookie_rx = dmaengine_submit(desc);

	वापस 0;

chan_err:
	dev_err(port->dev, "RX channel not available, switch to pio\n");
	aपंचांगel_port->use_dma_rx = false;
	अगर (aपंचांगel_port->chan_rx)
		aपंचांगel_release_rx_dma(port);
	वापस -EINVAL;
पूर्ण

अटल व्योम aपंचांगel_uart_समयr_callback(काष्ठा समयr_list *t)
अणु
	काष्ठा aपंचांगel_uart_port *aपंचांगel_port = from_समयr(aपंचांगel_port, t,
							uart_समयr);
	काष्ठा uart_port *port = &aपंचांगel_port->uart;

	अगर (!atomic_पढ़ो(&aपंचांगel_port->tasklet_shutकरोwn)) अणु
		tasklet_schedule(&aपंचांगel_port->tasklet_rx);
		mod_समयr(&aपंचांगel_port->uart_समयr,
			  jअगरfies + uart_poll_समयout(port));
	पूर्ण
पूर्ण

/*
 * receive पूर्णांकerrupt handler.
 */
अटल व्योम
aपंचांगel_handle_receive(काष्ठा uart_port *port, अचिन्हित पूर्णांक pending)
अणु
	काष्ठा aपंचांगel_uart_port *aपंचांगel_port = to_aपंचांगel_uart_port(port);

	अगर (aपंचांगel_use_pdc_rx(port)) अणु
		/*
		 * PDC receive. Just schedule the tasklet and let it
		 * figure out the details.
		 *
		 * TODO: We're not handling error flags correctly at
		 * the moment.
		 */
		अगर (pending & (ATMEL_US_ENDRX | ATMEL_US_TIMEOUT)) अणु
			aपंचांगel_uart_ग_लिखोl(port, ATMEL_US_IDR,
					  (ATMEL_US_ENDRX | ATMEL_US_TIMEOUT));
			aपंचांगel_tasklet_schedule(aपंचांगel_port,
					       &aपंचांगel_port->tasklet_rx);
		पूर्ण

		अगर (pending & (ATMEL_US_RXBRK | ATMEL_US_OVRE |
				ATMEL_US_FRAME | ATMEL_US_PARE))
			aपंचांगel_pdc_rxerr(port, pending);
	पूर्ण

	अगर (aपंचांगel_use_dma_rx(port)) अणु
		अगर (pending & ATMEL_US_TIMEOUT) अणु
			aपंचांगel_uart_ग_लिखोl(port, ATMEL_US_IDR,
					  ATMEL_US_TIMEOUT);
			aपंचांगel_tasklet_schedule(aपंचांगel_port,
					       &aपंचांगel_port->tasklet_rx);
		पूर्ण
	पूर्ण

	/* Interrupt receive */
	अगर (pending & ATMEL_US_RXRDY)
		aपंचांगel_rx_अक्षरs(port);
	अन्यथा अगर (pending & ATMEL_US_RXBRK) अणु
		/*
		 * End of अवरोध detected. If it came aदीर्घ with a
		 * अक्षरacter, aपंचांगel_rx_अक्षरs will handle it.
		 */
		aपंचांगel_uart_ग_लिखोl(port, ATMEL_US_CR, ATMEL_US_RSTSTA);
		aपंचांगel_uart_ग_लिखोl(port, ATMEL_US_IDR, ATMEL_US_RXBRK);
		aपंचांगel_port->अवरोध_active = 0;
	पूर्ण
पूर्ण

/*
 * transmit पूर्णांकerrupt handler. (Transmit is IRQF_NODELAY safe)
 */
अटल व्योम
aपंचांगel_handle_transmit(काष्ठा uart_port *port, अचिन्हित पूर्णांक pending)
अणु
	काष्ठा aपंचांगel_uart_port *aपंचांगel_port = to_aपंचांगel_uart_port(port);

	अगर (pending & aपंचांगel_port->tx_करोne_mask) अणु
		aपंचांगel_uart_ग_लिखोl(port, ATMEL_US_IDR,
				  aपंचांगel_port->tx_करोne_mask);

		/* Start RX अगर flag was set and FIFO is empty */
		अगर (aपंचांगel_port->hd_start_rx) अणु
			अगर (!(aपंचांगel_uart_पढ़ोl(port, ATMEL_US_CSR)
					& ATMEL_US_TXEMPTY))
				dev_warn(port->dev, "Should start RX, but TX fifo is not empty\n");

			aपंचांगel_port->hd_start_rx = false;
			aपंचांगel_start_rx(port);
		पूर्ण

		aपंचांगel_tasklet_schedule(aपंचांगel_port, &aपंचांगel_port->tasklet_tx);
	पूर्ण
पूर्ण

/*
 * status flags पूर्णांकerrupt handler.
 */
अटल व्योम
aपंचांगel_handle_status(काष्ठा uart_port *port, अचिन्हित पूर्णांक pending,
		    अचिन्हित पूर्णांक status)
अणु
	काष्ठा aपंचांगel_uart_port *aपंचांगel_port = to_aपंचांगel_uart_port(port);
	अचिन्हित पूर्णांक status_change;

	अगर (pending & (ATMEL_US_RIIC | ATMEL_US_DSRIC | ATMEL_US_DCDIC
				| ATMEL_US_CTSIC)) अणु
		status_change = status ^ aपंचांगel_port->irq_status_prev;
		aपंचांगel_port->irq_status_prev = status;

		अगर (status_change & (ATMEL_US_RI | ATMEL_US_DSR
					| ATMEL_US_DCD | ATMEL_US_CTS)) अणु
			/* TODO: All पढ़ोs to CSR will clear these पूर्णांकerrupts! */
			अगर (status_change & ATMEL_US_RI)
				port->icount.rng++;
			अगर (status_change & ATMEL_US_DSR)
				port->icount.dsr++;
			अगर (status_change & ATMEL_US_DCD)
				uart_handle_dcd_change(port, !(status & ATMEL_US_DCD));
			अगर (status_change & ATMEL_US_CTS)
				uart_handle_cts_change(port, !(status & ATMEL_US_CTS));

			wake_up_पूर्णांकerruptible(&port->state->port.delta_msr_रुको);
		पूर्ण
	पूर्ण

	अगर (pending & (ATMEL_US_NACK | ATMEL_US_ITERATION))
		dev_dbg(port->dev, "ISO7816 ERROR (0x%08x)\n", pending);
पूर्ण

/*
 * Interrupt handler
 */
अटल irqवापस_t aपंचांगel_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा uart_port *port = dev_id;
	काष्ठा aपंचांगel_uart_port *aपंचांगel_port = to_aपंचांगel_uart_port(port);
	अचिन्हित पूर्णांक status, pending, mask, pass_counter = 0;

	spin_lock(&aपंचांगel_port->lock_suspended);

	करो अणु
		status = aपंचांगel_uart_पढ़ोl(port, ATMEL_US_CSR);
		mask = aपंचांगel_uart_पढ़ोl(port, ATMEL_US_IMR);
		pending = status & mask;
		अगर (!pending)
			अवरोध;

		अगर (aपंचांगel_port->suspended) अणु
			aपंचांगel_port->pending |= pending;
			aपंचांगel_port->pending_status = status;
			aपंचांगel_uart_ग_लिखोl(port, ATMEL_US_IDR, mask);
			pm_प्रणाली_wakeup();
			अवरोध;
		पूर्ण

		aपंचांगel_handle_receive(port, pending);
		aपंचांगel_handle_status(port, pending, status);
		aपंचांगel_handle_transmit(port, pending);
	पूर्ण जबतक (pass_counter++ < ATMEL_ISR_PASS_LIMIT);

	spin_unlock(&aपंचांगel_port->lock_suspended);

	वापस pass_counter ? IRQ_HANDLED : IRQ_NONE;
पूर्ण

अटल व्योम aपंचांगel_release_tx_pdc(काष्ठा uart_port *port)
अणु
	काष्ठा aपंचांगel_uart_port *aपंचांगel_port = to_aपंचांगel_uart_port(port);
	काष्ठा aपंचांगel_dma_buffer *pdc = &aपंचांगel_port->pdc_tx;

	dma_unmap_single(port->dev,
			 pdc->dma_addr,
			 pdc->dma_size,
			 DMA_TO_DEVICE);
पूर्ण

/*
 * Called from tasklet with ENDTX and TXBUFE पूर्णांकerrupts disabled.
 */
अटल व्योम aपंचांगel_tx_pdc(काष्ठा uart_port *port)
अणु
	काष्ठा aपंचांगel_uart_port *aपंचांगel_port = to_aपंचांगel_uart_port(port);
	काष्ठा circ_buf *xmit = &port->state->xmit;
	काष्ठा aपंचांगel_dma_buffer *pdc = &aपंचांगel_port->pdc_tx;
	पूर्णांक count;

	/* nothing left to transmit? */
	अगर (aपंचांगel_uart_पढ़ोl(port, ATMEL_PDC_TCR))
		वापस;

	xmit->tail += pdc->ofs;
	xmit->tail &= UART_XMIT_SIZE - 1;

	port->icount.tx += pdc->ofs;
	pdc->ofs = 0;

	/* more to transmit - setup next transfer */

	/* disable PDC transmit */
	aपंचांगel_uart_ग_लिखोl(port, ATMEL_PDC_PTCR, ATMEL_PDC_TXTDIS);

	अगर (!uart_circ_empty(xmit) && !uart_tx_stopped(port)) अणु
		dma_sync_single_क्रम_device(port->dev,
					   pdc->dma_addr,
					   pdc->dma_size,
					   DMA_TO_DEVICE);

		count = CIRC_CNT_TO_END(xmit->head, xmit->tail, UART_XMIT_SIZE);
		pdc->ofs = count;

		aपंचांगel_uart_ग_लिखोl(port, ATMEL_PDC_TPR,
				  pdc->dma_addr + xmit->tail);
		aपंचांगel_uart_ग_लिखोl(port, ATMEL_PDC_TCR, count);
		/* re-enable PDC transmit */
		aपंचांगel_uart_ग_लिखोl(port, ATMEL_PDC_PTCR, ATMEL_PDC_TXTEN);
		/* Enable पूर्णांकerrupts */
		aपंचांगel_uart_ग_लिखोl(port, ATMEL_US_IER,
				  aपंचांगel_port->tx_करोne_mask);
	पूर्ण अन्यथा अणु
		अगर (aपंचांगel_uart_is_half_duplex(port)) अणु
			/* DMA करोne, stop TX, start RX क्रम RS485 */
			aपंचांगel_start_rx(port);
		पूर्ण
	पूर्ण

	अगर (uart_circ_अक्षरs_pending(xmit) < WAKEUP_CHARS)
		uart_ग_लिखो_wakeup(port);
पूर्ण

अटल पूर्णांक aपंचांगel_prepare_tx_pdc(काष्ठा uart_port *port)
अणु
	काष्ठा aपंचांगel_uart_port *aपंचांगel_port = to_aपंचांगel_uart_port(port);
	काष्ठा aपंचांगel_dma_buffer *pdc = &aपंचांगel_port->pdc_tx;
	काष्ठा circ_buf *xmit = &port->state->xmit;

	pdc->buf = xmit->buf;
	pdc->dma_addr = dma_map_single(port->dev,
					pdc->buf,
					UART_XMIT_SIZE,
					DMA_TO_DEVICE);
	pdc->dma_size = UART_XMIT_SIZE;
	pdc->ofs = 0;

	वापस 0;
पूर्ण

अटल व्योम aपंचांगel_rx_from_ring(काष्ठा uart_port *port)
अणु
	काष्ठा aपंचांगel_uart_port *aपंचांगel_port = to_aपंचांगel_uart_port(port);
	काष्ठा circ_buf *ring = &aपंचांगel_port->rx_ring;
	अचिन्हित पूर्णांक flg;
	अचिन्हित पूर्णांक status;

	जबतक (ring->head != ring->tail) अणु
		काष्ठा aपंचांगel_uart_अक्षर c;

		/* Make sure c is loaded after head. */
		smp_rmb();

		c = ((काष्ठा aपंचांगel_uart_अक्षर *)ring->buf)[ring->tail];

		ring->tail = (ring->tail + 1) & (ATMEL_SERIAL_RINGSIZE - 1);

		port->icount.rx++;
		status = c.status;
		flg = TTY_NORMAL;

		/*
		 * note that the error handling code is
		 * out of the मुख्य execution path
		 */
		अगर (unlikely(status & (ATMEL_US_PARE | ATMEL_US_FRAME
				       | ATMEL_US_OVRE | ATMEL_US_RXBRK))) अणु
			अगर (status & ATMEL_US_RXBRK) अणु
				/* ignore side-effect */
				status &= ~(ATMEL_US_PARE | ATMEL_US_FRAME);

				port->icount.brk++;
				अगर (uart_handle_अवरोध(port))
					जारी;
			पूर्ण
			अगर (status & ATMEL_US_PARE)
				port->icount.parity++;
			अगर (status & ATMEL_US_FRAME)
				port->icount.frame++;
			अगर (status & ATMEL_US_OVRE)
				port->icount.overrun++;

			status &= port->पढ़ो_status_mask;

			अगर (status & ATMEL_US_RXBRK)
				flg = TTY_BREAK;
			अन्यथा अगर (status & ATMEL_US_PARE)
				flg = TTY_PARITY;
			अन्यथा अगर (status & ATMEL_US_FRAME)
				flg = TTY_FRAME;
		पूर्ण


		अगर (uart_handle_sysrq_अक्षर(port, c.ch))
			जारी;

		uart_insert_अक्षर(port, status, ATMEL_US_OVRE, c.ch, flg);
	पूर्ण

	tty_flip_buffer_push(&port->state->port);
पूर्ण

अटल व्योम aपंचांगel_release_rx_pdc(काष्ठा uart_port *port)
अणु
	काष्ठा aपंचांगel_uart_port *aपंचांगel_port = to_aपंचांगel_uart_port(port);
	पूर्णांक i;

	क्रम (i = 0; i < 2; i++) अणु
		काष्ठा aपंचांगel_dma_buffer *pdc = &aपंचांगel_port->pdc_rx[i];

		dma_unmap_single(port->dev,
				 pdc->dma_addr,
				 pdc->dma_size,
				 DMA_FROM_DEVICE);
		kमुक्त(pdc->buf);
	पूर्ण
पूर्ण

अटल व्योम aपंचांगel_rx_from_pdc(काष्ठा uart_port *port)
अणु
	काष्ठा aपंचांगel_uart_port *aपंचांगel_port = to_aपंचांगel_uart_port(port);
	काष्ठा tty_port *tport = &port->state->port;
	काष्ठा aपंचांगel_dma_buffer *pdc;
	पूर्णांक rx_idx = aपंचांगel_port->pdc_rx_idx;
	अचिन्हित पूर्णांक head;
	अचिन्हित पूर्णांक tail;
	अचिन्हित पूर्णांक count;

	करो अणु
		/* Reset the UART समयout early so that we करोn't miss one */
		aपंचांगel_uart_ग_लिखोl(port, ATMEL_US_CR, ATMEL_US_STTTO);

		pdc = &aपंचांगel_port->pdc_rx[rx_idx];
		head = aपंचांगel_uart_पढ़ोl(port, ATMEL_PDC_RPR) - pdc->dma_addr;
		tail = pdc->ofs;

		/* If the PDC has चयनed buffers, RPR won't contain
		 * any address within the current buffer. Since head
		 * is अचिन्हित, we just need a one-way comparison to
		 * find out.
		 *
		 * In this हाल, we just need to consume the entire
		 * buffer and resubmit it क्रम DMA. This will clear the
		 * ENDRX bit as well, so that we can safely re-enable
		 * all पूर्णांकerrupts below.
		 */
		head = min(head, pdc->dma_size);

		अगर (likely(head != tail)) अणु
			dma_sync_single_क्रम_cpu(port->dev, pdc->dma_addr,
					pdc->dma_size, DMA_FROM_DEVICE);

			/*
			 * head will only wrap around when we recycle
			 * the DMA buffer, and when that happens, we
			 * explicitly set tail to 0. So head will
			 * always be greater than tail.
			 */
			count = head - tail;

			tty_insert_flip_string(tport, pdc->buf + pdc->ofs,
						count);

			dma_sync_single_क्रम_device(port->dev, pdc->dma_addr,
					pdc->dma_size, DMA_FROM_DEVICE);

			port->icount.rx += count;
			pdc->ofs = head;
		पूर्ण

		/*
		 * If the current buffer is full, we need to check अगर
		 * the next one contains any additional data.
		 */
		अगर (head >= pdc->dma_size) अणु
			pdc->ofs = 0;
			aपंचांगel_uart_ग_लिखोl(port, ATMEL_PDC_RNPR, pdc->dma_addr);
			aपंचांगel_uart_ग_लिखोl(port, ATMEL_PDC_RNCR, pdc->dma_size);

			rx_idx = !rx_idx;
			aपंचांगel_port->pdc_rx_idx = rx_idx;
		पूर्ण
	पूर्ण जबतक (head >= pdc->dma_size);

	tty_flip_buffer_push(tport);

	aपंचांगel_uart_ग_लिखोl(port, ATMEL_US_IER,
			  ATMEL_US_ENDRX | ATMEL_US_TIMEOUT);
पूर्ण

अटल पूर्णांक aपंचांगel_prepare_rx_pdc(काष्ठा uart_port *port)
अणु
	काष्ठा aपंचांगel_uart_port *aपंचांगel_port = to_aपंचांगel_uart_port(port);
	पूर्णांक i;

	क्रम (i = 0; i < 2; i++) अणु
		काष्ठा aपंचांगel_dma_buffer *pdc = &aपंचांगel_port->pdc_rx[i];

		pdc->buf = kदो_स्मृति(PDC_BUFFER_SIZE, GFP_KERNEL);
		अगर (pdc->buf == शून्य) अणु
			अगर (i != 0) अणु
				dma_unmap_single(port->dev,
					aपंचांगel_port->pdc_rx[0].dma_addr,
					PDC_BUFFER_SIZE,
					DMA_FROM_DEVICE);
				kमुक्त(aपंचांगel_port->pdc_rx[0].buf);
			पूर्ण
			aपंचांगel_port->use_pdc_rx = false;
			वापस -ENOMEM;
		पूर्ण
		pdc->dma_addr = dma_map_single(port->dev,
						pdc->buf,
						PDC_BUFFER_SIZE,
						DMA_FROM_DEVICE);
		pdc->dma_size = PDC_BUFFER_SIZE;
		pdc->ofs = 0;
	पूर्ण

	aपंचांगel_port->pdc_rx_idx = 0;

	aपंचांगel_uart_ग_लिखोl(port, ATMEL_PDC_RPR, aपंचांगel_port->pdc_rx[0].dma_addr);
	aपंचांगel_uart_ग_लिखोl(port, ATMEL_PDC_RCR, PDC_BUFFER_SIZE);

	aपंचांगel_uart_ग_लिखोl(port, ATMEL_PDC_RNPR,
			  aपंचांगel_port->pdc_rx[1].dma_addr);
	aपंचांगel_uart_ग_लिखोl(port, ATMEL_PDC_RNCR, PDC_BUFFER_SIZE);

	वापस 0;
पूर्ण

/*
 * tasklet handling tty stuff outside the पूर्णांकerrupt handler.
 */
अटल व्योम aपंचांगel_tasklet_rx_func(काष्ठा tasklet_काष्ठा *t)
अणु
	काष्ठा aपंचांगel_uart_port *aपंचांगel_port = from_tasklet(aपंचांगel_port, t,
							  tasklet_rx);
	काष्ठा uart_port *port = &aपंचांगel_port->uart;

	/* The पूर्णांकerrupt handler करोes not take the lock */
	spin_lock(&port->lock);
	aपंचांगel_port->schedule_rx(port);
	spin_unlock(&port->lock);
पूर्ण

अटल व्योम aपंचांगel_tasklet_tx_func(काष्ठा tasklet_काष्ठा *t)
अणु
	काष्ठा aपंचांगel_uart_port *aपंचांगel_port = from_tasklet(aपंचांगel_port, t,
							  tasklet_tx);
	काष्ठा uart_port *port = &aपंचांगel_port->uart;

	/* The पूर्णांकerrupt handler करोes not take the lock */
	spin_lock(&port->lock);
	aपंचांगel_port->schedule_tx(port);
	spin_unlock(&port->lock);
पूर्ण

अटल व्योम aपंचांगel_init_property(काष्ठा aपंचांगel_uart_port *aपंचांगel_port,
				काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *np = pdev->dev.of_node;

	/* DMA/PDC usage specअगरication */
	अगर (of_property_पढ़ो_bool(np, "atmel,use-dma-rx")) अणु
		अगर (of_property_पढ़ो_bool(np, "dmas")) अणु
			aपंचांगel_port->use_dma_rx  = true;
			aपंचांगel_port->use_pdc_rx  = false;
		पूर्ण अन्यथा अणु
			aपंचांगel_port->use_dma_rx  = false;
			aपंचांगel_port->use_pdc_rx  = true;
		पूर्ण
	पूर्ण अन्यथा अणु
		aपंचांगel_port->use_dma_rx  = false;
		aपंचांगel_port->use_pdc_rx  = false;
	पूर्ण

	अगर (of_property_पढ़ो_bool(np, "atmel,use-dma-tx")) अणु
		अगर (of_property_पढ़ो_bool(np, "dmas")) अणु
			aपंचांगel_port->use_dma_tx  = true;
			aपंचांगel_port->use_pdc_tx  = false;
		पूर्ण अन्यथा अणु
			aपंचांगel_port->use_dma_tx  = false;
			aपंचांगel_port->use_pdc_tx  = true;
		पूर्ण
	पूर्ण अन्यथा अणु
		aपंचांगel_port->use_dma_tx  = false;
		aपंचांगel_port->use_pdc_tx  = false;
	पूर्ण
पूर्ण

अटल व्योम aपंचांगel_set_ops(काष्ठा uart_port *port)
अणु
	काष्ठा aपंचांगel_uart_port *aपंचांगel_port = to_aपंचांगel_uart_port(port);

	अगर (aपंचांगel_use_dma_rx(port)) अणु
		aपंचांगel_port->prepare_rx = &aपंचांगel_prepare_rx_dma;
		aपंचांगel_port->schedule_rx = &aपंचांगel_rx_from_dma;
		aपंचांगel_port->release_rx = &aपंचांगel_release_rx_dma;
	पूर्ण अन्यथा अगर (aपंचांगel_use_pdc_rx(port)) अणु
		aपंचांगel_port->prepare_rx = &aपंचांगel_prepare_rx_pdc;
		aपंचांगel_port->schedule_rx = &aपंचांगel_rx_from_pdc;
		aपंचांगel_port->release_rx = &aपंचांगel_release_rx_pdc;
	पूर्ण अन्यथा अणु
		aपंचांगel_port->prepare_rx = शून्य;
		aपंचांगel_port->schedule_rx = &aपंचांगel_rx_from_ring;
		aपंचांगel_port->release_rx = शून्य;
	पूर्ण

	अगर (aपंचांगel_use_dma_tx(port)) अणु
		aपंचांगel_port->prepare_tx = &aपंचांगel_prepare_tx_dma;
		aपंचांगel_port->schedule_tx = &aपंचांगel_tx_dma;
		aपंचांगel_port->release_tx = &aपंचांगel_release_tx_dma;
	पूर्ण अन्यथा अगर (aपंचांगel_use_pdc_tx(port)) अणु
		aपंचांगel_port->prepare_tx = &aपंचांगel_prepare_tx_pdc;
		aपंचांगel_port->schedule_tx = &aपंचांगel_tx_pdc;
		aपंचांगel_port->release_tx = &aपंचांगel_release_tx_pdc;
	पूर्ण अन्यथा अणु
		aपंचांगel_port->prepare_tx = शून्य;
		aपंचांगel_port->schedule_tx = &aपंचांगel_tx_अक्षरs;
		aपंचांगel_port->release_tx = शून्य;
	पूर्ण
पूर्ण

/*
 * Get ip name usart or uart
 */
अटल व्योम aपंचांगel_get_ip_name(काष्ठा uart_port *port)
अणु
	काष्ठा aपंचांगel_uart_port *aपंचांगel_port = to_aपंचांगel_uart_port(port);
	पूर्णांक name = aपंचांगel_uart_पढ़ोl(port, ATMEL_US_NAME);
	u32 version;
	u32 usart, dbgu_uart, new_uart;
	/* ASCII decoding क्रम IP version */
	usart = 0x55534152;	/* USAR(T) */
	dbgu_uart = 0x44424755;	/* DBGU */
	new_uart = 0x55415254;	/* UART */

	/*
	 * Only USART devices from at91sam9260 SOC implement fractional
	 * baudrate. It is available क्रम all asynchronous modes, with the
	 * following restriction: the sampling घड़ी's duty cycle is not
	 * स्थिरant.
	 */
	aपंचांगel_port->has_frac_baudrate = false;
	aपंचांगel_port->has_hw_समयr = false;

	अगर (name == new_uart) अणु
		dev_dbg(port->dev, "Uart with hw timer");
		aपंचांगel_port->has_hw_समयr = true;
		aपंचांगel_port->rtor = ATMEL_UA_RTOR;
	पूर्ण अन्यथा अगर (name == usart) अणु
		dev_dbg(port->dev, "Usart\n");
		aपंचांगel_port->has_frac_baudrate = true;
		aपंचांगel_port->has_hw_समयr = true;
		aपंचांगel_port->rtor = ATMEL_US_RTOR;
		version = aपंचांगel_uart_पढ़ोl(port, ATMEL_US_VERSION);
		चयन (version) अणु
		हाल 0x814:	/* sama5d2 */
			fallthrough;
		हाल 0x701:	/* sama5d4 */
			aपंचांगel_port->fidi_min = 3;
			aपंचांगel_port->fidi_max = 65535;
			अवरोध;
		हाल 0x502:	/* sam9x5, sama5d3 */
			aपंचांगel_port->fidi_min = 3;
			aपंचांगel_port->fidi_max = 2047;
			अवरोध;
		शेष:
			aपंचांगel_port->fidi_min = 1;
			aपंचांगel_port->fidi_max = 2047;
		पूर्ण
	पूर्ण अन्यथा अगर (name == dbgu_uart) अणु
		dev_dbg(port->dev, "Dbgu or uart without hw timer\n");
	पूर्ण अन्यथा अणु
		/* fallback क्रम older SoCs: use version field */
		version = aपंचांगel_uart_पढ़ोl(port, ATMEL_US_VERSION);
		चयन (version) अणु
		हाल 0x302:
		हाल 0x10213:
		हाल 0x10302:
			dev_dbg(port->dev, "This version is usart\n");
			aपंचांगel_port->has_frac_baudrate = true;
			aपंचांगel_port->has_hw_समयr = true;
			aपंचांगel_port->rtor = ATMEL_US_RTOR;
			अवरोध;
		हाल 0x203:
		हाल 0x10202:
			dev_dbg(port->dev, "This version is uart\n");
			अवरोध;
		शेष:
			dev_err(port->dev, "Not supported ip name nor version, set to uart\n");
		पूर्ण
	पूर्ण
पूर्ण

/*
 * Perक्रमm initialization and enable port क्रम reception
 */
अटल पूर्णांक aपंचांगel_startup(काष्ठा uart_port *port)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(port->dev);
	काष्ठा aपंचांगel_uart_port *aपंचांगel_port = to_aपंचांगel_uart_port(port);
	पूर्णांक retval;

	/*
	 * Ensure that no पूर्णांकerrupts are enabled otherwise when
	 * request_irq() is called we could get stuck trying to
	 * handle an unexpected पूर्णांकerrupt
	 */
	aपंचांगel_uart_ग_लिखोl(port, ATMEL_US_IDR, -1);
	aपंचांगel_port->ms_irq_enabled = false;

	/*
	 * Allocate the IRQ
	 */
	retval = request_irq(port->irq, aपंचांगel_पूर्णांकerrupt,
			     IRQF_SHARED | IRQF_COND_SUSPEND,
			     dev_name(&pdev->dev), port);
	अगर (retval) अणु
		dev_err(port->dev, "atmel_startup - Can't get irq\n");
		वापस retval;
	पूर्ण

	atomic_set(&aपंचांगel_port->tasklet_shutकरोwn, 0);
	tasklet_setup(&aपंचांगel_port->tasklet_rx, aपंचांगel_tasklet_rx_func);
	tasklet_setup(&aपंचांगel_port->tasklet_tx, aपंचांगel_tasklet_tx_func);

	/*
	 * Initialize DMA (अगर necessary)
	 */
	aपंचांगel_init_property(aपंचांगel_port, pdev);
	aपंचांगel_set_ops(port);

	अगर (aपंचांगel_port->prepare_rx) अणु
		retval = aपंचांगel_port->prepare_rx(port);
		अगर (retval < 0)
			aपंचांगel_set_ops(port);
	पूर्ण

	अगर (aपंचांगel_port->prepare_tx) अणु
		retval = aपंचांगel_port->prepare_tx(port);
		अगर (retval < 0)
			aपंचांगel_set_ops(port);
	पूर्ण

	/*
	 * Enable FIFO when available
	 */
	अगर (aपंचांगel_port->fअगरo_size) अणु
		अचिन्हित पूर्णांक txrdym = ATMEL_US_ONE_DATA;
		अचिन्हित पूर्णांक rxrdym = ATMEL_US_ONE_DATA;
		अचिन्हित पूर्णांक fmr;

		aपंचांगel_uart_ग_लिखोl(port, ATMEL_US_CR,
				  ATMEL_US_FIFOEN |
				  ATMEL_US_RXFCLR |
				  ATMEL_US_TXFLCLR);

		अगर (aपंचांगel_use_dma_tx(port))
			txrdym = ATMEL_US_FOUR_DATA;

		fmr = ATMEL_US_TXRDYM(txrdym) | ATMEL_US_RXRDYM(rxrdym);
		अगर (aपंचांगel_port->rts_high &&
		    aपंचांगel_port->rts_low)
			fmr |=	ATMEL_US_FRTSC |
				ATMEL_US_RXFTHRES(aपंचांगel_port->rts_high) |
				ATMEL_US_RXFTHRES2(aपंचांगel_port->rts_low);

		aपंचांगel_uart_ग_लिखोl(port, ATMEL_US_FMR, fmr);
	पूर्ण

	/* Save current CSR क्रम comparison in aपंचांगel_tasklet_func() */
	aपंचांगel_port->irq_status_prev = aपंचांगel_uart_पढ़ोl(port, ATMEL_US_CSR);

	/*
	 * Finally, enable the serial port
	 */
	aपंचांगel_uart_ग_लिखोl(port, ATMEL_US_CR, ATMEL_US_RSTSTA | ATMEL_US_RSTRX);
	/* enable xmit & rcvr */
	aपंचांगel_uart_ग_लिखोl(port, ATMEL_US_CR, ATMEL_US_TXEN | ATMEL_US_RXEN);
	aपंचांगel_port->tx_stopped = false;

	समयr_setup(&aपंचांगel_port->uart_समयr, aपंचांगel_uart_समयr_callback, 0);

	अगर (aपंचांगel_use_pdc_rx(port)) अणु
		/* set UART समयout */
		अगर (!aपंचांगel_port->has_hw_समयr) अणु
			mod_समयr(&aपंचांगel_port->uart_समयr,
					jअगरfies + uart_poll_समयout(port));
		/* set USART समयout */
		पूर्ण अन्यथा अणु
			aपंचांगel_uart_ग_लिखोl(port, aपंचांगel_port->rtor,
					  PDC_RX_TIMEOUT);
			aपंचांगel_uart_ग_लिखोl(port, ATMEL_US_CR, ATMEL_US_STTTO);

			aपंचांगel_uart_ग_लिखोl(port, ATMEL_US_IER,
					  ATMEL_US_ENDRX | ATMEL_US_TIMEOUT);
		पूर्ण
		/* enable PDC controller */
		aपंचांगel_uart_ग_लिखोl(port, ATMEL_PDC_PTCR, ATMEL_PDC_RXTEN);
	पूर्ण अन्यथा अगर (aपंचांगel_use_dma_rx(port)) अणु
		/* set UART समयout */
		अगर (!aपंचांगel_port->has_hw_समयr) अणु
			mod_समयr(&aपंचांगel_port->uart_समयr,
					jअगरfies + uart_poll_समयout(port));
		/* set USART समयout */
		पूर्ण अन्यथा अणु
			aपंचांगel_uart_ग_लिखोl(port, aपंचांगel_port->rtor,
					  PDC_RX_TIMEOUT);
			aपंचांगel_uart_ग_लिखोl(port, ATMEL_US_CR, ATMEL_US_STTTO);

			aपंचांगel_uart_ग_लिखोl(port, ATMEL_US_IER,
					  ATMEL_US_TIMEOUT);
		पूर्ण
	पूर्ण अन्यथा अणु
		/* enable receive only */
		aपंचांगel_uart_ग_लिखोl(port, ATMEL_US_IER, ATMEL_US_RXRDY);
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Flush any TX data submitted क्रम DMA. Called when the TX circular
 * buffer is reset.
 */
अटल व्योम aपंचांगel_flush_buffer(काष्ठा uart_port *port)
अणु
	काष्ठा aपंचांगel_uart_port *aपंचांगel_port = to_aपंचांगel_uart_port(port);

	अगर (aपंचांगel_use_pdc_tx(port)) अणु
		aपंचांगel_uart_ग_लिखोl(port, ATMEL_PDC_TCR, 0);
		aपंचांगel_port->pdc_tx.ofs = 0;
	पूर्ण
	/*
	 * in uart_flush_buffer(), the xmit circular buffer has just
	 * been cleared, so we have to reset tx_len accordingly.
	 */
	aपंचांगel_port->tx_len = 0;
पूर्ण

/*
 * Disable the port
 */
अटल व्योम aपंचांगel_shutकरोwn(काष्ठा uart_port *port)
अणु
	काष्ठा aपंचांगel_uart_port *aपंचांगel_port = to_aपंचांगel_uart_port(port);

	/* Disable modem control lines पूर्णांकerrupts */
	aपंचांगel_disable_ms(port);

	/* Disable पूर्णांकerrupts at device level */
	aपंचांगel_uart_ग_लिखोl(port, ATMEL_US_IDR, -1);

	/* Prevent spurious पूर्णांकerrupts from scheduling the tasklet */
	atomic_inc(&aपंचांगel_port->tasklet_shutकरोwn);

	/*
	 * Prevent any tasklets being scheduled during
	 * cleanup
	 */
	del_समयr_sync(&aपंचांगel_port->uart_समयr);

	/* Make sure that no पूर्णांकerrupt is on the fly */
	synchronize_irq(port->irq);

	/*
	 * Clear out any scheduled tasklets beक्रमe
	 * we destroy the buffers
	 */
	tasklet_समाप्त(&aपंचांगel_port->tasklet_rx);
	tasklet_समाप्त(&aपंचांगel_port->tasklet_tx);

	/*
	 * Ensure everything is stopped and
	 * disable port and अवरोध condition.
	 */
	aपंचांगel_stop_rx(port);
	aपंचांगel_stop_tx(port);

	aपंचांगel_uart_ग_लिखोl(port, ATMEL_US_CR, ATMEL_US_RSTSTA);

	/*
	 * Shut-करोwn the DMA.
	 */
	अगर (aपंचांगel_port->release_rx)
		aपंचांगel_port->release_rx(port);
	अगर (aपंचांगel_port->release_tx)
		aपंचांगel_port->release_tx(port);

	/*
	 * Reset ring buffer poपूर्णांकers
	 */
	aपंचांगel_port->rx_ring.head = 0;
	aपंचांगel_port->rx_ring.tail = 0;

	/*
	 * Free the पूर्णांकerrupts
	 */
	मुक्त_irq(port->irq, port);

	aपंचांगel_flush_buffer(port);
पूर्ण

/*
 * Power / Clock management.
 */
अटल व्योम aपंचांगel_serial_pm(काष्ठा uart_port *port, अचिन्हित पूर्णांक state,
			    अचिन्हित पूर्णांक oldstate)
अणु
	काष्ठा aपंचांगel_uart_port *aपंचांगel_port = to_aपंचांगel_uart_port(port);

	चयन (state) अणु
	हाल 0:
		/*
		 * Enable the peripheral घड़ी क्रम this serial port.
		 * This is called on uart_खोलो() or a resume event.
		 */
		clk_prepare_enable(aपंचांगel_port->clk);

		/* re-enable पूर्णांकerrupts अगर we disabled some on suspend */
		aपंचांगel_uart_ग_लिखोl(port, ATMEL_US_IER, aपंचांगel_port->backup_imr);
		अवरोध;
	हाल 3:
		/* Back up the पूर्णांकerrupt mask and disable all पूर्णांकerrupts */
		aपंचांगel_port->backup_imr = aपंचांगel_uart_पढ़ोl(port, ATMEL_US_IMR);
		aपंचांगel_uart_ग_लिखोl(port, ATMEL_US_IDR, -1);

		/*
		 * Disable the peripheral घड़ी क्रम this serial port.
		 * This is called on uart_बंद() or a suspend event.
		 */
		clk_disable_unprepare(aपंचांगel_port->clk);
		अवरोध;
	शेष:
		dev_err(port->dev, "atmel_serial: unknown pm %d\n", state);
	पूर्ण
पूर्ण

/*
 * Change the port parameters
 */
अटल व्योम aपंचांगel_set_termios(काष्ठा uart_port *port, काष्ठा ktermios *termios,
			      काष्ठा ktermios *old)
अणु
	काष्ठा aपंचांगel_uart_port *aपंचांगel_port = to_aपंचांगel_uart_port(port);
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक old_mode, mode, imr, quot, baud, भाग, cd, fp = 0;

	/* save the current mode रेजिस्टर */
	mode = old_mode = aपंचांगel_uart_पढ़ोl(port, ATMEL_US_MR);

	/* reset the mode, घड़ी भागisor, parity, stop bits and data size */
	mode &= ~(ATMEL_US_USCLKS | ATMEL_US_CHRL | ATMEL_US_NBSTOP |
		  ATMEL_US_PAR | ATMEL_US_USMODE);

	baud = uart_get_baud_rate(port, termios, old, 0, port->uartclk / 16);

	/* byte size */
	चयन (termios->c_cflag & CSIZE) अणु
	हाल CS5:
		mode |= ATMEL_US_CHRL_5;
		अवरोध;
	हाल CS6:
		mode |= ATMEL_US_CHRL_6;
		अवरोध;
	हाल CS7:
		mode |= ATMEL_US_CHRL_7;
		अवरोध;
	शेष:
		mode |= ATMEL_US_CHRL_8;
		अवरोध;
	पूर्ण

	/* stop bits */
	अगर (termios->c_cflag & CSTOPB)
		mode |= ATMEL_US_NBSTOP_2;

	/* parity */
	अगर (termios->c_cflag & PARENB) अणु
		/* Mark or Space parity */
		अगर (termios->c_cflag & CMSPAR) अणु
			अगर (termios->c_cflag & PARODD)
				mode |= ATMEL_US_PAR_MARK;
			अन्यथा
				mode |= ATMEL_US_PAR_SPACE;
		पूर्ण अन्यथा अगर (termios->c_cflag & PARODD)
			mode |= ATMEL_US_PAR_ODD;
		अन्यथा
			mode |= ATMEL_US_PAR_EVEN;
	पूर्ण अन्यथा
		mode |= ATMEL_US_PAR_NONE;

	spin_lock_irqsave(&port->lock, flags);

	port->पढ़ो_status_mask = ATMEL_US_OVRE;
	अगर (termios->c_अगरlag & INPCK)
		port->पढ़ो_status_mask |= (ATMEL_US_FRAME | ATMEL_US_PARE);
	अगर (termios->c_अगरlag & (IGNBRK | BRKINT | PARMRK))
		port->पढ़ो_status_mask |= ATMEL_US_RXBRK;

	अगर (aपंचांगel_use_pdc_rx(port))
		/* need to enable error पूर्णांकerrupts */
		aपंचांगel_uart_ग_लिखोl(port, ATMEL_US_IER, port->पढ़ो_status_mask);

	/*
	 * Characters to ignore
	 */
	port->ignore_status_mask = 0;
	अगर (termios->c_अगरlag & IGNPAR)
		port->ignore_status_mask |= (ATMEL_US_FRAME | ATMEL_US_PARE);
	अगर (termios->c_अगरlag & IGNBRK) अणु
		port->ignore_status_mask |= ATMEL_US_RXBRK;
		/*
		 * If we're ignoring parity and अवरोध indicators,
		 * ignore overruns too (क्रम real raw support).
		 */
		अगर (termios->c_अगरlag & IGNPAR)
			port->ignore_status_mask |= ATMEL_US_OVRE;
	पूर्ण
	/* TODO: Ignore all अक्षरacters अगर CREAD is set.*/

	/* update the per-port समयout */
	uart_update_समयout(port, termios->c_cflag, baud);

	/*
	 * save/disable पूर्णांकerrupts. The tty layer will ensure that the
	 * transmitter is empty अगर requested by the caller, so there's
	 * no need to रुको क्रम it here.
	 */
	imr = aपंचांगel_uart_पढ़ोl(port, ATMEL_US_IMR);
	aपंचांगel_uart_ग_लिखोl(port, ATMEL_US_IDR, -1);

	/* disable receiver and transmitter */
	aपंचांगel_uart_ग_लिखोl(port, ATMEL_US_CR, ATMEL_US_TXDIS | ATMEL_US_RXDIS);
	aपंचांगel_port->tx_stopped = true;

	/* mode */
	अगर (port->rs485.flags & SER_RS485_ENABLED) अणु
		aपंचांगel_uart_ग_लिखोl(port, ATMEL_US_TTGR,
				  port->rs485.delay_rts_after_send);
		mode |= ATMEL_US_USMODE_RS485;
	पूर्ण अन्यथा अगर (port->iso7816.flags & SER_ISO7816_ENABLED) अणु
		aपंचांगel_uart_ग_लिखोl(port, ATMEL_US_TTGR, port->iso7816.tg);
		/* select mck घड़ी, and output  */
		mode |= ATMEL_US_USCLKS_MCK | ATMEL_US_CLKO;
		/* set max iterations */
		mode |= ATMEL_US_MAX_ITER(3);
		अगर ((port->iso7816.flags & SER_ISO7816_T_PARAM)
				== SER_ISO7816_T(0))
			mode |= ATMEL_US_USMODE_ISO7816_T0;
		अन्यथा
			mode |= ATMEL_US_USMODE_ISO7816_T1;
	पूर्ण अन्यथा अगर (termios->c_cflag & CRTSCTS) अणु
		/* RS232 with hardware handshake (RTS/CTS) */
		अगर (aपंचांगel_use_fअगरo(port) &&
		    !mctrl_gpio_to_gpiod(aपंचांगel_port->gpios, UART_GPIO_CTS)) अणु
			/*
			 * with ATMEL_US_USMODE_HWHS set, the controller will
			 * be able to drive the RTS pin high/low when the RX
			 * FIFO is above RXFTHRES/below RXFTHRES2.
			 * It will also disable the transmitter when the CTS
			 * pin is high.
			 * This mode is not activated अगर CTS pin is a GPIO
			 * because in this हाल, the transmitter is always
			 * disabled (there must be an पूर्णांकernal pull-up
			 * responsible क्रम this behaviour).
			 * If the RTS pin is a GPIO, the controller won't be
			 * able to drive it according to the FIFO thresholds,
			 * but it will be handled by the driver.
			 */
			mode |= ATMEL_US_USMODE_HWHS;
		पूर्ण अन्यथा अणु
			/*
			 * For platक्रमms without FIFO, the flow control is
			 * handled by the driver.
			 */
			mode |= ATMEL_US_USMODE_NORMAL;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* RS232 without hadware handshake */
		mode |= ATMEL_US_USMODE_NORMAL;
	पूर्ण

	/*
	 * Set the baud rate:
	 * Fractional baudrate allows to setup output frequency more
	 * accurately. This feature is enabled only when using normal mode.
	 * baudrate = selected घड़ी / (8 * (2 - OVER) * (CD + FP / 8))
	 * Currently, OVER is always set to 0 so we get
	 * baudrate = selected घड़ी / (16 * (CD + FP / 8))
	 * then
	 * 8 CD + FP = selected घड़ी / (2 * baudrate)
	 */
	अगर (aपंचांगel_port->has_frac_baudrate) अणु
		भाग = DIV_ROUND_CLOSEST(port->uartclk, baud * 2);
		cd = भाग >> 3;
		fp = भाग & ATMEL_US_FP_MASK;
	पूर्ण अन्यथा अणु
		cd = uart_get_भागisor(port, baud);
	पूर्ण

	अगर (cd > 65535) अणु	/* BRGR is 16-bit, so चयन to slower घड़ी */
		cd /= 8;
		mode |= ATMEL_US_USCLKS_MCK_DIV8;
	पूर्ण
	quot = cd | fp << ATMEL_US_FP_OFFSET;

	अगर (!(port->iso7816.flags & SER_ISO7816_ENABLED))
		aपंचांगel_uart_ग_लिखोl(port, ATMEL_US_BRGR, quot);

	/* set the mode, घड़ी भागisor, parity, stop bits and data size */
	aपंचांगel_uart_ग_लिखोl(port, ATMEL_US_MR, mode);

	/*
	 * when चयनing the mode, set the RTS line state according to the
	 * new mode, otherwise keep the क्रमmer state
	 */
	अगर ((old_mode & ATMEL_US_USMODE) != (mode & ATMEL_US_USMODE)) अणु
		अचिन्हित पूर्णांक rts_state;

		अगर ((mode & ATMEL_US_USMODE) == ATMEL_US_USMODE_HWHS) अणु
			/* let the hardware control the RTS line */
			rts_state = ATMEL_US_RTSDIS;
		पूर्ण अन्यथा अणु
			/* क्रमce RTS line to low level */
			rts_state = ATMEL_US_RTSEN;
		पूर्ण

		aपंचांगel_uart_ग_लिखोl(port, ATMEL_US_CR, rts_state);
	पूर्ण

	aपंचांगel_uart_ग_लिखोl(port, ATMEL_US_CR, ATMEL_US_RSTSTA | ATMEL_US_RSTRX);
	aपंचांगel_uart_ग_लिखोl(port, ATMEL_US_CR, ATMEL_US_TXEN | ATMEL_US_RXEN);
	aपंचांगel_port->tx_stopped = false;

	/* restore पूर्णांकerrupts */
	aपंचांगel_uart_ग_लिखोl(port, ATMEL_US_IER, imr);

	/* CTS flow-control and modem-status पूर्णांकerrupts */
	अगर (UART_ENABLE_MS(port, termios->c_cflag))
		aपंचांगel_enable_ms(port);
	अन्यथा
		aपंचांगel_disable_ms(port);

	spin_unlock_irqrestore(&port->lock, flags);
पूर्ण

अटल व्योम aपंचांगel_set_ldisc(काष्ठा uart_port *port, काष्ठा ktermios *termios)
अणु
	अगर (termios->c_line == N_PPS) अणु
		port->flags |= UPF_HARDPPS_CD;
		spin_lock_irq(&port->lock);
		aपंचांगel_enable_ms(port);
		spin_unlock_irq(&port->lock);
	पूर्ण अन्यथा अणु
		port->flags &= ~UPF_HARDPPS_CD;
		अगर (!UART_ENABLE_MS(port, termios->c_cflag)) अणु
			spin_lock_irq(&port->lock);
			aपंचांगel_disable_ms(port);
			spin_unlock_irq(&port->lock);
		पूर्ण
	पूर्ण
पूर्ण

/*
 * Return string describing the specअगरied port
 */
अटल स्थिर अक्षर *aपंचांगel_type(काष्ठा uart_port *port)
अणु
	वापस (port->type == PORT_ATMEL) ? "ATMEL_SERIAL" : शून्य;
पूर्ण

/*
 * Release the memory region(s) being used by 'port'.
 */
अटल व्योम aपंचांगel_release_port(काष्ठा uart_port *port)
अणु
	काष्ठा platक्रमm_device *mpdev = to_platक्रमm_device(port->dev->parent);
	पूर्णांक size = resource_size(mpdev->resource);

	release_mem_region(port->mapbase, size);

	अगर (port->flags & UPF_IOREMAP) अणु
		iounmap(port->membase);
		port->membase = शून्य;
	पूर्ण
पूर्ण

/*
 * Request the memory region(s) being used by 'port'.
 */
अटल पूर्णांक aपंचांगel_request_port(काष्ठा uart_port *port)
अणु
	काष्ठा platक्रमm_device *mpdev = to_platक्रमm_device(port->dev->parent);
	पूर्णांक size = resource_size(mpdev->resource);

	अगर (!request_mem_region(port->mapbase, size, "atmel_serial"))
		वापस -EBUSY;

	अगर (port->flags & UPF_IOREMAP) अणु
		port->membase = ioremap(port->mapbase, size);
		अगर (port->membase == शून्य) अणु
			release_mem_region(port->mapbase, size);
			वापस -ENOMEM;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Configure/स्वतःconfigure the port.
 */
अटल व्योम aपंचांगel_config_port(काष्ठा uart_port *port, पूर्णांक flags)
अणु
	अगर (flags & UART_CONFIG_TYPE) अणु
		port->type = PORT_ATMEL;
		aपंचांगel_request_port(port);
	पूर्ण
पूर्ण

/*
 * Verअगरy the new serial_काष्ठा (क्रम TIOCSSERIAL).
 */
अटल पूर्णांक aपंचांगel_verअगरy_port(काष्ठा uart_port *port, काष्ठा serial_काष्ठा *ser)
अणु
	पूर्णांक ret = 0;
	अगर (ser->type != PORT_UNKNOWN && ser->type != PORT_ATMEL)
		ret = -EINVAL;
	अगर (port->irq != ser->irq)
		ret = -EINVAL;
	अगर (ser->io_type != SERIAL_IO_MEM)
		ret = -EINVAL;
	अगर (port->uartclk / 16 != ser->baud_base)
		ret = -EINVAL;
	अगर (port->mapbase != (अचिन्हित दीर्घ)ser->iomem_base)
		ret = -EINVAL;
	अगर (port->iobase != ser->port)
		ret = -EINVAL;
	अगर (ser->hub6 != 0)
		ret = -EINVAL;
	वापस ret;
पूर्ण

#अगर_घोषित CONFIG_CONSOLE_POLL
अटल पूर्णांक aपंचांगel_poll_get_अक्षर(काष्ठा uart_port *port)
अणु
	जबतक (!(aपंचांगel_uart_पढ़ोl(port, ATMEL_US_CSR) & ATMEL_US_RXRDY))
		cpu_relax();

	वापस aपंचांगel_uart_पढ़ो_अक्षर(port);
पूर्ण

अटल व्योम aपंचांगel_poll_put_अक्षर(काष्ठा uart_port *port, अचिन्हित अक्षर ch)
अणु
	जबतक (!(aपंचांगel_uart_पढ़ोl(port, ATMEL_US_CSR) & ATMEL_US_TXRDY))
		cpu_relax();

	aपंचांगel_uart_ग_लिखो_अक्षर(port, ch);
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा uart_ops aपंचांगel_pops = अणु
	.tx_empty	= aपंचांगel_tx_empty,
	.set_mctrl	= aपंचांगel_set_mctrl,
	.get_mctrl	= aपंचांगel_get_mctrl,
	.stop_tx	= aपंचांगel_stop_tx,
	.start_tx	= aपंचांगel_start_tx,
	.stop_rx	= aपंचांगel_stop_rx,
	.enable_ms	= aपंचांगel_enable_ms,
	.अवरोध_ctl	= aपंचांगel_अवरोध_ctl,
	.startup	= aपंचांगel_startup,
	.shutकरोwn	= aपंचांगel_shutकरोwn,
	.flush_buffer	= aपंचांगel_flush_buffer,
	.set_termios	= aपंचांगel_set_termios,
	.set_ldisc	= aपंचांगel_set_ldisc,
	.type		= aपंचांगel_type,
	.release_port	= aपंचांगel_release_port,
	.request_port	= aपंचांगel_request_port,
	.config_port	= aपंचांगel_config_port,
	.verअगरy_port	= aपंचांगel_verअगरy_port,
	.pm		= aपंचांगel_serial_pm,
#अगर_घोषित CONFIG_CONSOLE_POLL
	.poll_get_अक्षर	= aपंचांगel_poll_get_अक्षर,
	.poll_put_अक्षर	= aपंचांगel_poll_put_अक्षर,
#पूर्ण_अगर
पूर्ण;

/*
 * Configure the port from the platक्रमm device resource info.
 */
अटल पूर्णांक aपंचांगel_init_port(काष्ठा aपंचांगel_uart_port *aपंचांगel_port,
				      काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक ret;
	काष्ठा uart_port *port = &aपंचांगel_port->uart;
	काष्ठा platक्रमm_device *mpdev = to_platक्रमm_device(pdev->dev.parent);

	aपंचांगel_init_property(aपंचांगel_port, pdev);
	aपंचांगel_set_ops(port);

	port->iotype		= UPIO_MEM;
	port->flags		= UPF_BOOT_AUTOCONF | UPF_IOREMAP;
	port->ops		= &aपंचांगel_pops;
	port->fअगरosize		= 1;
	port->dev		= &pdev->dev;
	port->mapbase		= mpdev->resource[0].start;
	port->irq		= mpdev->resource[1].start;
	port->rs485_config	= aपंचांगel_config_rs485;
	port->iso7816_config	= aपंचांगel_config_iso7816;
	port->membase		= शून्य;

	स_रखो(&aपंचांगel_port->rx_ring, 0, माप(aपंचांगel_port->rx_ring));

	ret = uart_get_rs485_mode(port);
	अगर (ret)
		वापस ret;

	/* क्रम console, the घड़ी could alपढ़ोy be configured */
	अगर (!aपंचांगel_port->clk) अणु
		aपंचांगel_port->clk = clk_get(&mpdev->dev, "usart");
		अगर (IS_ERR(aपंचांगel_port->clk)) अणु
			ret = PTR_ERR(aपंचांगel_port->clk);
			aपंचांगel_port->clk = शून्य;
			वापस ret;
		पूर्ण
		ret = clk_prepare_enable(aपंचांगel_port->clk);
		अगर (ret) अणु
			clk_put(aपंचांगel_port->clk);
			aपंचांगel_port->clk = शून्य;
			वापस ret;
		पूर्ण
		port->uartclk = clk_get_rate(aपंचांगel_port->clk);
		clk_disable_unprepare(aपंचांगel_port->clk);
		/* only enable घड़ी when USART is in use */
	पूर्ण

	/*
	 * Use TXEMPTY क्रम पूर्णांकerrupt when rs485 or ISO7816 अन्यथा TXRDY or
	 * ENDTX|TXBUFE
	 */
	अगर (aपंचांगel_uart_is_half_duplex(port))
		aपंचांगel_port->tx_करोne_mask = ATMEL_US_TXEMPTY;
	अन्यथा अगर (aपंचांगel_use_pdc_tx(port)) अणु
		port->fअगरosize = PDC_BUFFER_SIZE;
		aपंचांगel_port->tx_करोne_mask = ATMEL_US_ENDTX | ATMEL_US_TXBUFE;
	पूर्ण अन्यथा अणु
		aपंचांगel_port->tx_करोne_mask = ATMEL_US_TXRDY;
	पूर्ण

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_SERIAL_ATMEL_CONSOLE
अटल व्योम aपंचांगel_console_अक्षर_दो(काष्ठा uart_port *port, पूर्णांक ch)
अणु
	जबतक (!(aपंचांगel_uart_पढ़ोl(port, ATMEL_US_CSR) & ATMEL_US_TXRDY))
		cpu_relax();
	aपंचांगel_uart_ग_लिखो_अक्षर(port, ch);
पूर्ण

/*
 * Interrupts are disabled on entering
 */
अटल व्योम aपंचांगel_console_ग_लिखो(काष्ठा console *co, स्थिर अक्षर *s, u_पूर्णांक count)
अणु
	काष्ठा uart_port *port = &aपंचांगel_ports[co->index].uart;
	काष्ठा aपंचांगel_uart_port *aपंचांगel_port = to_aपंचांगel_uart_port(port);
	अचिन्हित पूर्णांक status, imr;
	अचिन्हित पूर्णांक pdc_tx;

	/*
	 * First, save IMR and then disable पूर्णांकerrupts
	 */
	imr = aपंचांगel_uart_पढ़ोl(port, ATMEL_US_IMR);
	aपंचांगel_uart_ग_लिखोl(port, ATMEL_US_IDR,
			  ATMEL_US_RXRDY | aपंचांगel_port->tx_करोne_mask);

	/* Store PDC transmit status and disable it */
	pdc_tx = aपंचांगel_uart_पढ़ोl(port, ATMEL_PDC_PTSR) & ATMEL_PDC_TXTEN;
	aपंचांगel_uart_ग_लिखोl(port, ATMEL_PDC_PTCR, ATMEL_PDC_TXTDIS);

	/* Make sure that tx path is actually able to send अक्षरacters */
	aपंचांगel_uart_ग_लिखोl(port, ATMEL_US_CR, ATMEL_US_TXEN);
	aपंचांगel_port->tx_stopped = false;

	uart_console_ग_लिखो(port, s, count, aपंचांगel_console_अक्षर_दो);

	/*
	 * Finally, रुको क्रम transmitter to become empty
	 * and restore IMR
	 */
	करो अणु
		status = aपंचांगel_uart_पढ़ोl(port, ATMEL_US_CSR);
	पूर्ण जबतक (!(status & ATMEL_US_TXRDY));

	/* Restore PDC transmit status */
	अगर (pdc_tx)
		aपंचांगel_uart_ग_लिखोl(port, ATMEL_PDC_PTCR, ATMEL_PDC_TXTEN);

	/* set पूर्णांकerrupts back the way they were */
	aपंचांगel_uart_ग_लिखोl(port, ATMEL_US_IER, imr);
पूर्ण

/*
 * If the port was alपढ़ोy initialised (eg, by a boot loader),
 * try to determine the current setup.
 */
अटल व्योम __init aपंचांगel_console_get_options(काष्ठा uart_port *port, पूर्णांक *baud,
					     पूर्णांक *parity, पूर्णांक *bits)
अणु
	अचिन्हित पूर्णांक mr, quot;

	/*
	 * If the baud rate generator isn't running, the port wasn't
	 * initialized by the boot loader.
	 */
	quot = aपंचांगel_uart_पढ़ोl(port, ATMEL_US_BRGR) & ATMEL_US_CD;
	अगर (!quot)
		वापस;

	mr = aपंचांगel_uart_पढ़ोl(port, ATMEL_US_MR) & ATMEL_US_CHRL;
	अगर (mr == ATMEL_US_CHRL_8)
		*bits = 8;
	अन्यथा
		*bits = 7;

	mr = aपंचांगel_uart_पढ़ोl(port, ATMEL_US_MR) & ATMEL_US_PAR;
	अगर (mr == ATMEL_US_PAR_EVEN)
		*parity = 'e';
	अन्यथा अगर (mr == ATMEL_US_PAR_ODD)
		*parity = 'o';

	/*
	 * The serial core only rounds करोwn when matching this to a
	 * supported baud rate. Make sure we करोn't end up slightly
	 * lower than one of those, as it would make us fall through
	 * to a much lower baud rate than we really want.
	 */
	*baud = port->uartclk / (16 * (quot - 1));
पूर्ण

अटल पूर्णांक __init aपंचांगel_console_setup(काष्ठा console *co, अक्षर *options)
अणु
	पूर्णांक ret;
	काष्ठा uart_port *port = &aपंचांगel_ports[co->index].uart;
	काष्ठा aपंचांगel_uart_port *aपंचांगel_port = to_aपंचांगel_uart_port(port);
	पूर्णांक baud = 115200;
	पूर्णांक bits = 8;
	पूर्णांक parity = 'n';
	पूर्णांक flow = 'n';

	अगर (port->membase == शून्य) अणु
		/* Port not initialized yet - delay setup */
		वापस -ENODEV;
	पूर्ण

	ret = clk_prepare_enable(aपंचांगel_ports[co->index].clk);
	अगर (ret)
		वापस ret;

	aपंचांगel_uart_ग_लिखोl(port, ATMEL_US_IDR, -1);
	aपंचांगel_uart_ग_लिखोl(port, ATMEL_US_CR, ATMEL_US_RSTSTA | ATMEL_US_RSTRX);
	aपंचांगel_uart_ग_लिखोl(port, ATMEL_US_CR, ATMEL_US_TXEN | ATMEL_US_RXEN);
	aपंचांगel_port->tx_stopped = false;

	अगर (options)
		uart_parse_options(options, &baud, &parity, &bits, &flow);
	अन्यथा
		aपंचांगel_console_get_options(port, &baud, &parity, &bits);

	वापस uart_set_options(port, co, baud, parity, bits, flow);
पूर्ण

अटल काष्ठा uart_driver aपंचांगel_uart;

अटल काष्ठा console aपंचांगel_console = अणु
	.name		= ATMEL_DEVICENAME,
	.ग_लिखो		= aपंचांगel_console_ग_लिखो,
	.device		= uart_console_device,
	.setup		= aपंचांगel_console_setup,
	.flags		= CON_PRINTBUFFER,
	.index		= -1,
	.data		= &aपंचांगel_uart,
पूर्ण;

#घोषणा ATMEL_CONSOLE_DEVICE	(&aपंचांगel_console)

#अन्यथा
#घोषणा ATMEL_CONSOLE_DEVICE	शून्य
#पूर्ण_अगर

अटल काष्ठा uart_driver aपंचांगel_uart = अणु
	.owner		= THIS_MODULE,
	.driver_name	= "atmel_serial",
	.dev_name	= ATMEL_DEVICENAME,
	.major		= SERIAL_ATMEL_MAJOR,
	.minor		= MINOR_START,
	.nr		= ATMEL_MAX_UART,
	.cons		= ATMEL_CONSOLE_DEVICE,
पूर्ण;

#अगर_घोषित CONFIG_PM
अटल bool aपंचांगel_serial_clk_will_stop(व्योम)
अणु
#अगर_घोषित CONFIG_ARCH_AT91
	वापस at91_suspend_entering_slow_घड़ी();
#अन्यथा
	वापस false;
#पूर्ण_अगर
पूर्ण

अटल पूर्णांक aपंचांगel_serial_suspend(काष्ठा platक्रमm_device *pdev,
				pm_message_t state)
अणु
	काष्ठा uart_port *port = platक्रमm_get_drvdata(pdev);
	काष्ठा aपंचांगel_uart_port *aपंचांगel_port = to_aपंचांगel_uart_port(port);

	अगर (uart_console(port) && console_suspend_enabled) अणु
		/* Drain the TX shअगरter */
		जबतक (!(aपंचांगel_uart_पढ़ोl(port, ATMEL_US_CSR) &
			 ATMEL_US_TXEMPTY))
			cpu_relax();
	पूर्ण

	अगर (uart_console(port) && !console_suspend_enabled) अणु
		/* Cache रेजिस्टर values as we won't get a full shutकरोwn/startup
		 * cycle
		 */
		aपंचांगel_port->cache.mr = aपंचांगel_uart_पढ़ोl(port, ATMEL_US_MR);
		aपंचांगel_port->cache.imr = aपंचांगel_uart_पढ़ोl(port, ATMEL_US_IMR);
		aपंचांगel_port->cache.brgr = aपंचांगel_uart_पढ़ोl(port, ATMEL_US_BRGR);
		aपंचांगel_port->cache.rtor = aपंचांगel_uart_पढ़ोl(port,
							  aपंचांगel_port->rtor);
		aपंचांगel_port->cache.ttgr = aपंचांगel_uart_पढ़ोl(port, ATMEL_US_TTGR);
		aपंचांगel_port->cache.fmr = aपंचांगel_uart_पढ़ोl(port, ATMEL_US_FMR);
		aपंचांगel_port->cache.fimr = aपंचांगel_uart_पढ़ोl(port, ATMEL_US_FIMR);
	पूर्ण

	/* we can not wake up अगर we're running on slow घड़ी */
	aपंचांगel_port->may_wakeup = device_may_wakeup(&pdev->dev);
	अगर (aपंचांगel_serial_clk_will_stop()) अणु
		अचिन्हित दीर्घ flags;

		spin_lock_irqsave(&aपंचांगel_port->lock_suspended, flags);
		aपंचांगel_port->suspended = true;
		spin_unlock_irqrestore(&aपंचांगel_port->lock_suspended, flags);
		device_set_wakeup_enable(&pdev->dev, 0);
	पूर्ण

	uart_suspend_port(&aपंचांगel_uart, port);

	वापस 0;
पूर्ण

अटल पूर्णांक aपंचांगel_serial_resume(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा uart_port *port = platक्रमm_get_drvdata(pdev);
	काष्ठा aपंचांगel_uart_port *aपंचांगel_port = to_aपंचांगel_uart_port(port);
	अचिन्हित दीर्घ flags;

	अगर (uart_console(port) && !console_suspend_enabled) अणु
		aपंचांगel_uart_ग_लिखोl(port, ATMEL_US_MR, aपंचांगel_port->cache.mr);
		aपंचांगel_uart_ग_लिखोl(port, ATMEL_US_IER, aपंचांगel_port->cache.imr);
		aपंचांगel_uart_ग_लिखोl(port, ATMEL_US_BRGR, aपंचांगel_port->cache.brgr);
		aपंचांगel_uart_ग_लिखोl(port, aपंचांगel_port->rtor,
				  aपंचांगel_port->cache.rtor);
		aपंचांगel_uart_ग_लिखोl(port, ATMEL_US_TTGR, aपंचांगel_port->cache.ttgr);

		अगर (aपंचांगel_port->fअगरo_size) अणु
			aपंचांगel_uart_ग_लिखोl(port, ATMEL_US_CR, ATMEL_US_FIFOEN |
					  ATMEL_US_RXFCLR | ATMEL_US_TXFLCLR);
			aपंचांगel_uart_ग_लिखोl(port, ATMEL_US_FMR,
					  aपंचांगel_port->cache.fmr);
			aपंचांगel_uart_ग_लिखोl(port, ATMEL_US_FIER,
					  aपंचांगel_port->cache.fimr);
		पूर्ण
		aपंचांगel_start_rx(port);
	पूर्ण

	spin_lock_irqsave(&aपंचांगel_port->lock_suspended, flags);
	अगर (aपंचांगel_port->pending) अणु
		aपंचांगel_handle_receive(port, aपंचांगel_port->pending);
		aपंचांगel_handle_status(port, aपंचांगel_port->pending,
				    aपंचांगel_port->pending_status);
		aपंचांगel_handle_transmit(port, aपंचांगel_port->pending);
		aपंचांगel_port->pending = 0;
	पूर्ण
	aपंचांगel_port->suspended = false;
	spin_unlock_irqrestore(&aपंचांगel_port->lock_suspended, flags);

	uart_resume_port(&aपंचांगel_uart, port);
	device_set_wakeup_enable(&pdev->dev, aपंचांगel_port->may_wakeup);

	वापस 0;
पूर्ण
#अन्यथा
#घोषणा aपंचांगel_serial_suspend शून्य
#घोषणा aपंचांगel_serial_resume शून्य
#पूर्ण_अगर

अटल व्योम aपंचांगel_serial_probe_fअगरos(काष्ठा aपंचांगel_uart_port *aपंचांगel_port,
				     काष्ठा platक्रमm_device *pdev)
अणु
	aपंचांगel_port->fअगरo_size = 0;
	aपंचांगel_port->rts_low = 0;
	aपंचांगel_port->rts_high = 0;

	अगर (of_property_पढ़ो_u32(pdev->dev.of_node,
				 "atmel,fifo-size",
				 &aपंचांगel_port->fअगरo_size))
		वापस;

	अगर (!aपंचांगel_port->fअगरo_size)
		वापस;

	अगर (aपंचांगel_port->fअगरo_size < ATMEL_MIN_FIFO_SIZE) अणु
		aपंचांगel_port->fअगरo_size = 0;
		dev_err(&pdev->dev, "Invalid FIFO size\n");
		वापस;
	पूर्ण

	/*
	 * 0 <= rts_low <= rts_high <= fअगरo_size
	 * Once their CTS line निश्चितed by the remote peer, some x86 UARTs tend
	 * to flush their पूर्णांकernal TX FIFO, commonly up to 16 data, beक्रमe
	 * actually stopping to send new data. So we try to set the RTS High
	 * Threshold to a reasonably high value respecting this 16 data
	 * empirical rule when possible.
	 */
	aपंचांगel_port->rts_high = max_t(पूर्णांक, aपंचांगel_port->fअगरo_size >> 1,
			       aपंचांगel_port->fअगरo_size - ATMEL_RTS_HIGH_OFFSET);
	aपंचांगel_port->rts_low  = max_t(पूर्णांक, aपंचांगel_port->fअगरo_size >> 2,
			       aपंचांगel_port->fअगरo_size - ATMEL_RTS_LOW_OFFSET);

	dev_info(&pdev->dev, "Using FIFO (%u data)\n",
		 aपंचांगel_port->fअगरo_size);
	dev_dbg(&pdev->dev, "RTS High Threshold : %2u data\n",
		aपंचांगel_port->rts_high);
	dev_dbg(&pdev->dev, "RTS Low Threshold  : %2u data\n",
		aपंचांगel_port->rts_low);
पूर्ण

अटल पूर्णांक aपंचांगel_serial_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा aपंचांगel_uart_port *aपंचांगel_port;
	काष्ठा device_node *np = pdev->dev.parent->of_node;
	व्योम *data;
	पूर्णांक ret;
	bool rs485_enabled;

	BUILD_BUG_ON(ATMEL_SERIAL_RINGSIZE & (ATMEL_SERIAL_RINGSIZE - 1));

	/*
	 * In device tree there is no node with "atmel,at91rm9200-usart-serial"
	 * as compatible string. This driver is probed by at91-usart mfd driver
	 * which is just a wrapper over the aपंचांगel_serial driver and
	 * spi-at91-usart driver. All attributes needed by this driver are
	 * found in of_node of parent.
	 */
	pdev->dev.of_node = np;

	ret = of_alias_get_id(np, "serial");
	अगर (ret < 0)
		/* port id not found in platक्रमm data nor device-tree aliases:
		 * स्वतः-क्रमागतerate it */
		ret = find_first_zero_bit(aपंचांगel_ports_in_use, ATMEL_MAX_UART);

	अगर (ret >= ATMEL_MAX_UART) अणु
		ret = -ENODEV;
		जाओ err;
	पूर्ण

	अगर (test_and_set_bit(ret, aपंचांगel_ports_in_use)) अणु
		/* port alपढ़ोy in use */
		ret = -EBUSY;
		जाओ err;
	पूर्ण

	aपंचांगel_port = &aपंचांगel_ports[ret];
	aपंचांगel_port->backup_imr = 0;
	aपंचांगel_port->uart.line = ret;
	aपंचांगel_port->uart.has_sysrq = IS_ENABLED(CONFIG_SERIAL_ATMEL_CONSOLE);
	aपंचांगel_serial_probe_fअगरos(aपंचांगel_port, pdev);

	atomic_set(&aपंचांगel_port->tasklet_shutकरोwn, 0);
	spin_lock_init(&aपंचांगel_port->lock_suspended);

	ret = aपंचांगel_init_port(aपंचांगel_port, pdev);
	अगर (ret)
		जाओ err_clear_bit;

	aपंचांगel_port->gpios = mctrl_gpio_init(&aपंचांगel_port->uart, 0);
	अगर (IS_ERR(aपंचांगel_port->gpios)) अणु
		ret = PTR_ERR(aपंचांगel_port->gpios);
		जाओ err_clear_bit;
	पूर्ण

	अगर (!aपंचांगel_use_pdc_rx(&aपंचांगel_port->uart)) अणु
		ret = -ENOMEM;
		data = kदो_स्मृति_array(ATMEL_SERIAL_RINGSIZE,
				     माप(काष्ठा aपंचांगel_uart_अक्षर),
				     GFP_KERNEL);
		अगर (!data)
			जाओ err_alloc_ring;
		aपंचांगel_port->rx_ring.buf = data;
	पूर्ण

	rs485_enabled = aपंचांगel_port->uart.rs485.flags & SER_RS485_ENABLED;

	ret = uart_add_one_port(&aपंचांगel_uart, &aपंचांगel_port->uart);
	अगर (ret)
		जाओ err_add_port;

#अगर_घोषित CONFIG_SERIAL_ATMEL_CONSOLE
	अगर (uart_console(&aपंचांगel_port->uart)
			&& ATMEL_CONSOLE_DEVICE->flags & CON_ENABLED) अणु
		/*
		 * The serial core enabled the घड़ी क्रम us, so unकरो
		 * the clk_prepare_enable() in aपंचांगel_console_setup()
		 */
		clk_disable_unprepare(aपंचांगel_port->clk);
	पूर्ण
#पूर्ण_अगर

	device_init_wakeup(&pdev->dev, 1);
	platक्रमm_set_drvdata(pdev, aपंचांगel_port);

	/*
	 * The peripheral घड़ी has been disabled by aपंचांगel_init_port():
	 * enable it beक्रमe accessing I/O रेजिस्टरs
	 */
	clk_prepare_enable(aपंचांगel_port->clk);

	अगर (rs485_enabled) अणु
		aपंचांगel_uart_ग_लिखोl(&aपंचांगel_port->uart, ATMEL_US_MR,
				  ATMEL_US_USMODE_NORMAL);
		aपंचांगel_uart_ग_लिखोl(&aपंचांगel_port->uart, ATMEL_US_CR,
				  ATMEL_US_RTSEN);
	पूर्ण

	/*
	 * Get port name of usart or uart
	 */
	aपंचांगel_get_ip_name(&aपंचांगel_port->uart);

	/*
	 * The peripheral घड़ी can now safely be disabled till the port
	 * is used
	 */
	clk_disable_unprepare(aपंचांगel_port->clk);

	वापस 0;

err_add_port:
	kमुक्त(aपंचांगel_port->rx_ring.buf);
	aपंचांगel_port->rx_ring.buf = शून्य;
err_alloc_ring:
	अगर (!uart_console(&aपंचांगel_port->uart)) अणु
		clk_put(aपंचांगel_port->clk);
		aपंचांगel_port->clk = शून्य;
	पूर्ण
err_clear_bit:
	clear_bit(aपंचांगel_port->uart.line, aपंचांगel_ports_in_use);
err:
	वापस ret;
पूर्ण

/*
 * Even अगर the driver is not modular, it makes sense to be able to
 * unbind a device: there can be many bound devices, and there are
 * situations where dynamic binding and unbinding can be useful.
 *
 * For example, a connected device can require a specअगरic firmware update
 * protocol that needs bitbanging on IO lines, but use the regular serial
 * port in the normal हाल.
 */
अटल पूर्णांक aपंचांगel_serial_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा uart_port *port = platक्रमm_get_drvdata(pdev);
	काष्ठा aपंचांगel_uart_port *aपंचांगel_port = to_aपंचांगel_uart_port(port);
	पूर्णांक ret = 0;

	tasklet_समाप्त(&aपंचांगel_port->tasklet_rx);
	tasklet_समाप्त(&aपंचांगel_port->tasklet_tx);

	device_init_wakeup(&pdev->dev, 0);

	ret = uart_हटाओ_one_port(&aपंचांगel_uart, port);

	kमुक्त(aपंचांगel_port->rx_ring.buf);

	/* "port" is allocated अटलally, so we shouldn't मुक्त it */

	clear_bit(port->line, aपंचांगel_ports_in_use);

	clk_put(aपंचांगel_port->clk);
	aपंचांगel_port->clk = शून्य;
	pdev->dev.of_node = शून्य;

	वापस ret;
पूर्ण

अटल काष्ठा platक्रमm_driver aपंचांगel_serial_driver = अणु
	.probe		= aपंचांगel_serial_probe,
	.हटाओ		= aपंचांगel_serial_हटाओ,
	.suspend	= aपंचांगel_serial_suspend,
	.resume		= aपंचांगel_serial_resume,
	.driver		= अणु
		.name			= "atmel_usart_serial",
		.of_match_table		= of_match_ptr(aपंचांगel_serial_dt_ids),
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init aपंचांगel_serial_init(व्योम)
अणु
	पूर्णांक ret;

	ret = uart_रेजिस्टर_driver(&aपंचांगel_uart);
	अगर (ret)
		वापस ret;

	ret = platक्रमm_driver_रेजिस्टर(&aपंचांगel_serial_driver);
	अगर (ret)
		uart_unरेजिस्टर_driver(&aपंचांगel_uart);

	वापस ret;
पूर्ण
device_initcall(aपंचांगel_serial_init);
