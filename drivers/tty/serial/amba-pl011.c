<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 *  Driver क्रम AMBA serial ports
 *
 *  Based on drivers/अक्षर/serial.c, by Linus Torvalds, Theoकरोre Ts'o.
 *
 *  Copyright 1999 ARM Limited
 *  Copyright (C) 2000 Deep Blue Solutions Ltd.
 *  Copyright (C) 2010 ST-Ericsson SA
 *
 * This is a generic driver क्रम ARM AMBA-type serial ports.  They
 * have a lot of 16550-like features, but are not रेजिस्टर compatible.
 * Note that although they करो have CTS, DCD and DSR inमाला_दो, they करो
 * not have an RI input, nor करो they have DTR or RTS outमाला_दो.  If
 * required, these have to be supplied via some other means (eg, GPIO)
 * and hooked पूर्णांकo this driver.
 */

#समावेश <linux/module.h>
#समावेश <linux/ioport.h>
#समावेश <linux/init.h>
#समावेश <linux/console.h>
#समावेश <linux/sysrq.h>
#समावेश <linux/device.h>
#समावेश <linux/tty.h>
#समावेश <linux/tty_flip.h>
#समावेश <linux/serial_core.h>
#समावेश <linux/serial.h>
#समावेश <linux/amba/bus.h>
#समावेश <linux/amba/serial.h>
#समावेश <linux/clk.h>
#समावेश <linux/slab.h>
#समावेश <linux/dmaengine.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/scatterlist.h>
#समावेश <linux/delay.h>
#समावेश <linux/types.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/pinctrl/consumer.h>
#समावेश <linux/sizes.h>
#समावेश <linux/पन.स>
#समावेश <linux/acpi.h>

#समावेश "amba-pl011.h"

#घोषणा UART_NR			14

#घोषणा SERIAL_AMBA_MAJOR	204
#घोषणा SERIAL_AMBA_MINOR	64
#घोषणा SERIAL_AMBA_NR		UART_NR

#घोषणा AMBA_ISR_PASS_LIMIT	256

#घोषणा UART_DR_ERROR		(UART011_DR_OE|UART011_DR_BE|UART011_DR_PE|UART011_DR_FE)
#घोषणा UART_DUMMY_DR_RX	(1 << 16)

अटल u16 pl011_std_offsets[REG_ARRAY_SIZE] = अणु
	[REG_DR] = UART01x_DR,
	[REG_FR] = UART01x_FR,
	[REG_LCRH_RX] = UART011_LCRH,
	[REG_LCRH_TX] = UART011_LCRH,
	[REG_IBRD] = UART011_IBRD,
	[REG_FBRD] = UART011_FBRD,
	[REG_CR] = UART011_CR,
	[REG_IFLS] = UART011_IFLS,
	[REG_IMSC] = UART011_IMSC,
	[REG_RIS] = UART011_RIS,
	[REG_MIS] = UART011_MIS,
	[REG_ICR] = UART011_ICR,
	[REG_DMACR] = UART011_DMACR,
पूर्ण;

/* There is by now at least one venकरोr with dअगरfering details, so handle it */
काष्ठा venकरोr_data अणु
	स्थिर u16		*reg_offset;
	अचिन्हित पूर्णांक		अगरls;
	अचिन्हित पूर्णांक		fr_busy;
	अचिन्हित पूर्णांक		fr_dsr;
	अचिन्हित पूर्णांक		fr_cts;
	अचिन्हित पूर्णांक		fr_ri;
	अचिन्हित पूर्णांक		inv_fr;
	bool			access_32b;
	bool			oversampling;
	bool			dma_threshold;
	bool			cts_event_workaround;
	bool			always_enabled;
	bool			fixed_options;

	अचिन्हित पूर्णांक (*get_fअगरosize)(काष्ठा amba_device *dev);
पूर्ण;

अटल अचिन्हित पूर्णांक get_fअगरosize_arm(काष्ठा amba_device *dev)
अणु
	वापस amba_rev(dev) < 3 ? 16 : 32;
पूर्ण

अटल काष्ठा venकरोr_data venकरोr_arm = अणु
	.reg_offset		= pl011_std_offsets,
	.अगरls			= UART011_IFLS_RX4_8|UART011_IFLS_TX4_8,
	.fr_busy		= UART01x_FR_BUSY,
	.fr_dsr			= UART01x_FR_DSR,
	.fr_cts			= UART01x_FR_CTS,
	.fr_ri			= UART011_FR_RI,
	.oversampling		= false,
	.dma_threshold		= false,
	.cts_event_workaround	= false,
	.always_enabled		= false,
	.fixed_options		= false,
	.get_fअगरosize		= get_fअगरosize_arm,
पूर्ण;

अटल स्थिर काष्ठा venकरोr_data venकरोr_sbsa = अणु
	.reg_offset		= pl011_std_offsets,
	.fr_busy		= UART01x_FR_BUSY,
	.fr_dsr			= UART01x_FR_DSR,
	.fr_cts			= UART01x_FR_CTS,
	.fr_ri			= UART011_FR_RI,
	.access_32b		= true,
	.oversampling		= false,
	.dma_threshold		= false,
	.cts_event_workaround	= false,
	.always_enabled		= true,
	.fixed_options		= true,
पूर्ण;

#अगर_घोषित CONFIG_ACPI_SPCR_TABLE
अटल स्थिर काष्ठा venकरोr_data venकरोr_qdt_qdf2400_e44 = अणु
	.reg_offset		= pl011_std_offsets,
	.fr_busy		= UART011_FR_TXFE,
	.fr_dsr			= UART01x_FR_DSR,
	.fr_cts			= UART01x_FR_CTS,
	.fr_ri			= UART011_FR_RI,
	.inv_fr			= UART011_FR_TXFE,
	.access_32b		= true,
	.oversampling		= false,
	.dma_threshold		= false,
	.cts_event_workaround	= false,
	.always_enabled		= true,
	.fixed_options		= true,
पूर्ण;
#पूर्ण_अगर

अटल u16 pl011_st_offsets[REG_ARRAY_SIZE] = अणु
	[REG_DR] = UART01x_DR,
	[REG_ST_DMAWM] = ST_UART011_DMAWM,
	[REG_ST_TIMEOUT] = ST_UART011_TIMEOUT,
	[REG_FR] = UART01x_FR,
	[REG_LCRH_RX] = ST_UART011_LCRH_RX,
	[REG_LCRH_TX] = ST_UART011_LCRH_TX,
	[REG_IBRD] = UART011_IBRD,
	[REG_FBRD] = UART011_FBRD,
	[REG_CR] = UART011_CR,
	[REG_IFLS] = UART011_IFLS,
	[REG_IMSC] = UART011_IMSC,
	[REG_RIS] = UART011_RIS,
	[REG_MIS] = UART011_MIS,
	[REG_ICR] = UART011_ICR,
	[REG_DMACR] = UART011_DMACR,
	[REG_ST_XFCR] = ST_UART011_XFCR,
	[REG_ST_XON1] = ST_UART011_XON1,
	[REG_ST_XON2] = ST_UART011_XON2,
	[REG_ST_XOFF1] = ST_UART011_XOFF1,
	[REG_ST_XOFF2] = ST_UART011_XOFF2,
	[REG_ST_ITCR] = ST_UART011_ITCR,
	[REG_ST_ITIP] = ST_UART011_ITIP,
	[REG_ST_ABCR] = ST_UART011_ABCR,
	[REG_ST_ABIMSC] = ST_UART011_ABIMSC,
पूर्ण;

अटल अचिन्हित पूर्णांक get_fअगरosize_st(काष्ठा amba_device *dev)
अणु
	वापस 64;
पूर्ण

अटल काष्ठा venकरोr_data venकरोr_st = अणु
	.reg_offset		= pl011_st_offsets,
	.अगरls			= UART011_IFLS_RX_HALF|UART011_IFLS_TX_HALF,
	.fr_busy		= UART01x_FR_BUSY,
	.fr_dsr			= UART01x_FR_DSR,
	.fr_cts			= UART01x_FR_CTS,
	.fr_ri			= UART011_FR_RI,
	.oversampling		= true,
	.dma_threshold		= true,
	.cts_event_workaround	= true,
	.always_enabled		= false,
	.fixed_options		= false,
	.get_fअगरosize		= get_fअगरosize_st,
पूर्ण;

अटल स्थिर u16 pl011_zte_offsets[REG_ARRAY_SIZE] = अणु
	[REG_DR] = ZX_UART011_DR,
	[REG_FR] = ZX_UART011_FR,
	[REG_LCRH_RX] = ZX_UART011_LCRH,
	[REG_LCRH_TX] = ZX_UART011_LCRH,
	[REG_IBRD] = ZX_UART011_IBRD,
	[REG_FBRD] = ZX_UART011_FBRD,
	[REG_CR] = ZX_UART011_CR,
	[REG_IFLS] = ZX_UART011_IFLS,
	[REG_IMSC] = ZX_UART011_IMSC,
	[REG_RIS] = ZX_UART011_RIS,
	[REG_MIS] = ZX_UART011_MIS,
	[REG_ICR] = ZX_UART011_ICR,
	[REG_DMACR] = ZX_UART011_DMACR,
पूर्ण;

अटल अचिन्हित पूर्णांक get_fअगरosize_zte(काष्ठा amba_device *dev)
अणु
	वापस 16;
पूर्ण

अटल काष्ठा venकरोr_data venकरोr_zte = अणु
	.reg_offset		= pl011_zte_offsets,
	.access_32b		= true,
	.अगरls			= UART011_IFLS_RX4_8|UART011_IFLS_TX4_8,
	.fr_busy		= ZX_UART01x_FR_BUSY,
	.fr_dsr			= ZX_UART01x_FR_DSR,
	.fr_cts			= ZX_UART01x_FR_CTS,
	.fr_ri			= ZX_UART011_FR_RI,
	.get_fअगरosize		= get_fअगरosize_zte,
पूर्ण;

/* Deals with DMA transactions */

काष्ठा pl011_sgbuf अणु
	काष्ठा scatterlist sg;
	अक्षर *buf;
पूर्ण;

काष्ठा pl011_dmarx_data अणु
	काष्ठा dma_chan		*chan;
	काष्ठा completion	complete;
	bool			use_buf_b;
	काष्ठा pl011_sgbuf	sgbuf_a;
	काष्ठा pl011_sgbuf	sgbuf_b;
	dma_cookie_t		cookie;
	bool			running;
	काष्ठा समयr_list	समयr;
	अचिन्हित पूर्णांक last_residue;
	अचिन्हित दीर्घ last_jअगरfies;
	bool स्वतः_poll_rate;
	अचिन्हित पूर्णांक poll_rate;
	अचिन्हित पूर्णांक poll_समयout;
पूर्ण;

काष्ठा pl011_dmatx_data अणु
	काष्ठा dma_chan		*chan;
	काष्ठा scatterlist	sg;
	अक्षर			*buf;
	bool			queued;
पूर्ण;

/*
 * We wrap our port काष्ठाure around the generic uart_port.
 */
काष्ठा uart_amba_port अणु
	काष्ठा uart_port	port;
	स्थिर u16		*reg_offset;
	काष्ठा clk		*clk;
	स्थिर काष्ठा venकरोr_data *venकरोr;
	अचिन्हित पूर्णांक		dmacr;		/* dma control reg */
	अचिन्हित पूर्णांक		im;		/* पूर्णांकerrupt mask */
	अचिन्हित पूर्णांक		old_status;
	अचिन्हित पूर्णांक		fअगरosize;	/* venकरोr-specअगरic */
	अचिन्हित पूर्णांक		old_cr;		/* state during shutकरोwn */
	अचिन्हित पूर्णांक		fixed_baud;	/* venकरोr-set fixed baud rate */
	अक्षर			type[12];
#अगर_घोषित CONFIG_DMA_ENGINE
	/* DMA stuff */
	bool			using_tx_dma;
	bool			using_rx_dma;
	काष्ठा pl011_dmarx_data dmarx;
	काष्ठा pl011_dmatx_data	dmatx;
	bool			dma_probed;
#पूर्ण_अगर
पूर्ण;

अटल अचिन्हित पूर्णांक pl011_reg_to_offset(स्थिर काष्ठा uart_amba_port *uap,
	अचिन्हित पूर्णांक reg)
अणु
	वापस uap->reg_offset[reg];
पूर्ण

अटल अचिन्हित पूर्णांक pl011_पढ़ो(स्थिर काष्ठा uart_amba_port *uap,
	अचिन्हित पूर्णांक reg)
अणु
	व्योम __iomem *addr = uap->port.membase + pl011_reg_to_offset(uap, reg);

	वापस (uap->port.iotype == UPIO_MEM32) ?
		पढ़ोl_relaxed(addr) : पढ़ोw_relaxed(addr);
पूर्ण

अटल व्योम pl011_ग_लिखो(अचिन्हित पूर्णांक val, स्थिर काष्ठा uart_amba_port *uap,
	अचिन्हित पूर्णांक reg)
अणु
	व्योम __iomem *addr = uap->port.membase + pl011_reg_to_offset(uap, reg);

	अगर (uap->port.iotype == UPIO_MEM32)
		ग_लिखोl_relaxed(val, addr);
	अन्यथा
		ग_लिखोw_relaxed(val, addr);
पूर्ण

/*
 * Reads up to 256 अक्षरacters from the FIFO or until it's empty and
 * inserts them पूर्णांकo the TTY layer. Returns the number of अक्षरacters
 * पढ़ो from the FIFO.
 */
अटल पूर्णांक pl011_fअगरo_to_tty(काष्ठा uart_amba_port *uap)
अणु
	अचिन्हित पूर्णांक ch, flag, fअगरotaken;
	पूर्णांक sysrq;
	u16 status;

	क्रम (fअगरotaken = 0; fअगरotaken != 256; fअगरotaken++) अणु
		status = pl011_पढ़ो(uap, REG_FR);
		अगर (status & UART01x_FR_RXFE)
			अवरोध;

		/* Take अक्षरs from the FIFO and update status */
		ch = pl011_पढ़ो(uap, REG_DR) | UART_DUMMY_DR_RX;
		flag = TTY_NORMAL;
		uap->port.icount.rx++;

		अगर (unlikely(ch & UART_DR_ERROR)) अणु
			अगर (ch & UART011_DR_BE) अणु
				ch &= ~(UART011_DR_FE | UART011_DR_PE);
				uap->port.icount.brk++;
				अगर (uart_handle_अवरोध(&uap->port))
					जारी;
			पूर्ण अन्यथा अगर (ch & UART011_DR_PE)
				uap->port.icount.parity++;
			अन्यथा अगर (ch & UART011_DR_FE)
				uap->port.icount.frame++;
			अगर (ch & UART011_DR_OE)
				uap->port.icount.overrun++;

			ch &= uap->port.पढ़ो_status_mask;

			अगर (ch & UART011_DR_BE)
				flag = TTY_BREAK;
			अन्यथा अगर (ch & UART011_DR_PE)
				flag = TTY_PARITY;
			अन्यथा अगर (ch & UART011_DR_FE)
				flag = TTY_FRAME;
		पूर्ण

		spin_unlock(&uap->port.lock);
		sysrq = uart_handle_sysrq_अक्षर(&uap->port, ch & 255);
		spin_lock(&uap->port.lock);

		अगर (!sysrq)
			uart_insert_अक्षर(&uap->port, ch, UART011_DR_OE, ch, flag);
	पूर्ण

	वापस fअगरotaken;
पूर्ण


/*
 * All the DMA operation mode stuff goes inside this अगरdef.
 * This assumes that you have a generic DMA device पूर्णांकerface,
 * no custom DMA पूर्णांकerfaces are supported.
 */
#अगर_घोषित CONFIG_DMA_ENGINE

#घोषणा PL011_DMA_BUFFER_SIZE PAGE_SIZE

अटल पूर्णांक pl011_sgbuf_init(काष्ठा dma_chan *chan, काष्ठा pl011_sgbuf *sg,
	क्रमागत dma_data_direction dir)
अणु
	dma_addr_t dma_addr;

	sg->buf = dma_alloc_coherent(chan->device->dev,
		PL011_DMA_BUFFER_SIZE, &dma_addr, GFP_KERNEL);
	अगर (!sg->buf)
		वापस -ENOMEM;

	sg_init_table(&sg->sg, 1);
	sg_set_page(&sg->sg, phys_to_page(dma_addr),
		PL011_DMA_BUFFER_SIZE, offset_in_page(dma_addr));
	sg_dma_address(&sg->sg) = dma_addr;
	sg_dma_len(&sg->sg) = PL011_DMA_BUFFER_SIZE;

	वापस 0;
पूर्ण

अटल व्योम pl011_sgbuf_मुक्त(काष्ठा dma_chan *chan, काष्ठा pl011_sgbuf *sg,
	क्रमागत dma_data_direction dir)
अणु
	अगर (sg->buf) अणु
		dma_मुक्त_coherent(chan->device->dev,
			PL011_DMA_BUFFER_SIZE, sg->buf,
			sg_dma_address(&sg->sg));
	पूर्ण
पूर्ण

अटल व्योम pl011_dma_probe(काष्ठा uart_amba_port *uap)
अणु
	/* DMA is the sole user of the platक्रमm data right now */
	काष्ठा amba_pl011_data *plat = dev_get_platdata(uap->port.dev);
	काष्ठा device *dev = uap->port.dev;
	काष्ठा dma_slave_config tx_conf = अणु
		.dst_addr = uap->port.mapbase +
				 pl011_reg_to_offset(uap, REG_DR),
		.dst_addr_width = DMA_SLAVE_BUSWIDTH_1_BYTE,
		.direction = DMA_MEM_TO_DEV,
		.dst_maxburst = uap->fअगरosize >> 1,
		.device_fc = false,
	पूर्ण;
	काष्ठा dma_chan *chan;
	dma_cap_mask_t mask;

	uap->dma_probed = true;
	chan = dma_request_chan(dev, "tx");
	अगर (IS_ERR(chan)) अणु
		अगर (PTR_ERR(chan) == -EPROBE_DEFER) अणु
			uap->dma_probed = false;
			वापस;
		पूर्ण

		/* We need platक्रमm data */
		अगर (!plat || !plat->dma_filter) अणु
			dev_info(uap->port.dev, "no DMA platform data\n");
			वापस;
		पूर्ण

		/* Try to acquire a generic DMA engine slave TX channel */
		dma_cap_zero(mask);
		dma_cap_set(DMA_SLAVE, mask);

		chan = dma_request_channel(mask, plat->dma_filter,
						plat->dma_tx_param);
		अगर (!chan) अणु
			dev_err(uap->port.dev, "no TX DMA channel!\n");
			वापस;
		पूर्ण
	पूर्ण

	dmaengine_slave_config(chan, &tx_conf);
	uap->dmatx.chan = chan;

	dev_info(uap->port.dev, "DMA channel TX %s\n",
		 dma_chan_name(uap->dmatx.chan));

	/* Optionally make use of an RX channel as well */
	chan = dma_request_slave_channel(dev, "rx");

	अगर (!chan && plat && plat->dma_rx_param) अणु
		chan = dma_request_channel(mask, plat->dma_filter, plat->dma_rx_param);

		अगर (!chan) अणु
			dev_err(uap->port.dev, "no RX DMA channel!\n");
			वापस;
		पूर्ण
	पूर्ण

	अगर (chan) अणु
		काष्ठा dma_slave_config rx_conf = अणु
			.src_addr = uap->port.mapbase +
				pl011_reg_to_offset(uap, REG_DR),
			.src_addr_width = DMA_SLAVE_BUSWIDTH_1_BYTE,
			.direction = DMA_DEV_TO_MEM,
			.src_maxburst = uap->fअगरosize >> 2,
			.device_fc = false,
		पूर्ण;
		काष्ठा dma_slave_caps caps;

		/*
		 * Some DMA controllers provide inक्रमmation on their capabilities.
		 * If the controller करोes, check क्रम suitable residue processing
		 * otherwise assime all is well.
		 */
		अगर (0 == dma_get_slave_caps(chan, &caps)) अणु
			अगर (caps.residue_granularity ==
					DMA_RESIDUE_GRANULARITY_DESCRIPTOR) अणु
				dma_release_channel(chan);
				dev_info(uap->port.dev,
					"RX DMA disabled - no residue processing\n");
				वापस;
			पूर्ण
		पूर्ण
		dmaengine_slave_config(chan, &rx_conf);
		uap->dmarx.chan = chan;

		uap->dmarx.स्वतः_poll_rate = false;
		अगर (plat && plat->dma_rx_poll_enable) अणु
			/* Set poll rate अगर specअगरied. */
			अगर (plat->dma_rx_poll_rate) अणु
				uap->dmarx.स्वतः_poll_rate = false;
				uap->dmarx.poll_rate = plat->dma_rx_poll_rate;
			पूर्ण अन्यथा अणु
				/*
				 * 100 ms शेषs to poll rate अगर not
				 * specअगरied. This will be adjusted with
				 * the baud rate at set_termios.
				 */
				uap->dmarx.स्वतः_poll_rate = true;
				uap->dmarx.poll_rate =  100;
			पूर्ण
			/* 3 secs शेषs poll_समयout अगर not specअगरied. */
			अगर (plat->dma_rx_poll_समयout)
				uap->dmarx.poll_समयout =
					plat->dma_rx_poll_समयout;
			अन्यथा
				uap->dmarx.poll_समयout = 3000;
		पूर्ण अन्यथा अगर (!plat && dev->of_node) अणु
			uap->dmarx.स्वतः_poll_rate = of_property_पढ़ो_bool(
						dev->of_node, "auto-poll");
			अगर (uap->dmarx.स्वतः_poll_rate) अणु
				u32 x;

				अगर (0 == of_property_पढ़ो_u32(dev->of_node,
						"poll-rate-ms", &x))
					uap->dmarx.poll_rate = x;
				अन्यथा
					uap->dmarx.poll_rate = 100;
				अगर (0 == of_property_पढ़ो_u32(dev->of_node,
						"poll-timeout-ms", &x))
					uap->dmarx.poll_समयout = x;
				अन्यथा
					uap->dmarx.poll_समयout = 3000;
			पूर्ण
		पूर्ण
		dev_info(uap->port.dev, "DMA channel RX %s\n",
			 dma_chan_name(uap->dmarx.chan));
	पूर्ण
पूर्ण

अटल व्योम pl011_dma_हटाओ(काष्ठा uart_amba_port *uap)
अणु
	अगर (uap->dmatx.chan)
		dma_release_channel(uap->dmatx.chan);
	अगर (uap->dmarx.chan)
		dma_release_channel(uap->dmarx.chan);
पूर्ण

/* Forward declare these क्रम the refill routine */
अटल पूर्णांक pl011_dma_tx_refill(काष्ठा uart_amba_port *uap);
अटल व्योम pl011_start_tx_pio(काष्ठा uart_amba_port *uap);

/*
 * The current DMA TX buffer has been sent.
 * Try to queue up another DMA buffer.
 */
अटल व्योम pl011_dma_tx_callback(व्योम *data)
अणु
	काष्ठा uart_amba_port *uap = data;
	काष्ठा pl011_dmatx_data *dmatx = &uap->dmatx;
	अचिन्हित दीर्घ flags;
	u16 dmacr;

	spin_lock_irqsave(&uap->port.lock, flags);
	अगर (uap->dmatx.queued)
		dma_unmap_sg(dmatx->chan->device->dev, &dmatx->sg, 1,
			     DMA_TO_DEVICE);

	dmacr = uap->dmacr;
	uap->dmacr = dmacr & ~UART011_TXDMAE;
	pl011_ग_लिखो(uap->dmacr, uap, REG_DMACR);

	/*
	 * If TX DMA was disabled, it means that we've stopped the DMA क्रम
	 * some reason (eg, XOFF received, or we want to send an X-अक्षर.)
	 *
	 * Note: we need to be careful here of a potential race between DMA
	 * and the rest of the driver - अगर the driver disables TX DMA जबतक
	 * a TX buffer completing, we must update the tx queued status to
	 * get further refills (hence we check dmacr).
	 */
	अगर (!(dmacr & UART011_TXDMAE) || uart_tx_stopped(&uap->port) ||
	    uart_circ_empty(&uap->port.state->xmit)) अणु
		uap->dmatx.queued = false;
		spin_unlock_irqrestore(&uap->port.lock, flags);
		वापस;
	पूर्ण

	अगर (pl011_dma_tx_refill(uap) <= 0)
		/*
		 * We didn't queue a DMA buffer क्रम some reason, but we
		 * have data pending to be sent.  Re-enable the TX IRQ.
		 */
		pl011_start_tx_pio(uap);

	spin_unlock_irqrestore(&uap->port.lock, flags);
पूर्ण

/*
 * Try to refill the TX DMA buffer.
 * Locking: called with port lock held and IRQs disabled.
 * Returns:
 *   1 अगर we queued up a TX DMA buffer.
 *   0 अगर we didn't want to handle this by DMA
 *  <0 on error
 */
अटल पूर्णांक pl011_dma_tx_refill(काष्ठा uart_amba_port *uap)
अणु
	काष्ठा pl011_dmatx_data *dmatx = &uap->dmatx;
	काष्ठा dma_chan *chan = dmatx->chan;
	काष्ठा dma_device *dma_dev = chan->device;
	काष्ठा dma_async_tx_descriptor *desc;
	काष्ठा circ_buf *xmit = &uap->port.state->xmit;
	अचिन्हित पूर्णांक count;

	/*
	 * Try to aव्योम the overhead involved in using DMA अगर the
	 * transaction fits in the first half of the FIFO, by using
	 * the standard पूर्णांकerrupt handling.  This ensures that we
	 * issue a uart_ग_लिखो_wakeup() at the appropriate समय.
	 */
	count = uart_circ_अक्षरs_pending(xmit);
	अगर (count < (uap->fअगरosize >> 1)) अणु
		uap->dmatx.queued = false;
		वापस 0;
	पूर्ण

	/*
	 * Bodge: करोn't send the last अक्षरacter by DMA, as this
	 * will prevent XON from notअगरying us to restart DMA.
	 */
	count -= 1;

	/* Else proceed to copy the TX अक्षरs to the DMA buffer and fire DMA */
	अगर (count > PL011_DMA_BUFFER_SIZE)
		count = PL011_DMA_BUFFER_SIZE;

	अगर (xmit->tail < xmit->head)
		स_नकल(&dmatx->buf[0], &xmit->buf[xmit->tail], count);
	अन्यथा अणु
		माप_प्रकार first = UART_XMIT_SIZE - xmit->tail;
		माप_प्रकार second;

		अगर (first > count)
			first = count;
		second = count - first;

		स_नकल(&dmatx->buf[0], &xmit->buf[xmit->tail], first);
		अगर (second)
			स_नकल(&dmatx->buf[first], &xmit->buf[0], second);
	पूर्ण

	dmatx->sg.length = count;

	अगर (dma_map_sg(dma_dev->dev, &dmatx->sg, 1, DMA_TO_DEVICE) != 1) अणु
		uap->dmatx.queued = false;
		dev_dbg(uap->port.dev, "unable to map TX DMA\n");
		वापस -EBUSY;
	पूर्ण

	desc = dmaengine_prep_slave_sg(chan, &dmatx->sg, 1, DMA_MEM_TO_DEV,
					     DMA_PREP_INTERRUPT | DMA_CTRL_ACK);
	अगर (!desc) अणु
		dma_unmap_sg(dma_dev->dev, &dmatx->sg, 1, DMA_TO_DEVICE);
		uap->dmatx.queued = false;
		/*
		 * If DMA cannot be used right now, we complete this
		 * transaction via IRQ and let the TTY layer retry.
		 */
		dev_dbg(uap->port.dev, "TX DMA busy\n");
		वापस -EBUSY;
	पूर्ण

	/* Some data to go aदीर्घ to the callback */
	desc->callback = pl011_dma_tx_callback;
	desc->callback_param = uap;

	/* All errors should happen at prepare समय */
	dmaengine_submit(desc);

	/* Fire the DMA transaction */
	dma_dev->device_issue_pending(chan);

	uap->dmacr |= UART011_TXDMAE;
	pl011_ग_लिखो(uap->dmacr, uap, REG_DMACR);
	uap->dmatx.queued = true;

	/*
	 * Now we know that DMA will fire, so advance the ring buffer
	 * with the stuff we just dispatched.
	 */
	xmit->tail = (xmit->tail + count) & (UART_XMIT_SIZE - 1);
	uap->port.icount.tx += count;

	अगर (uart_circ_अक्षरs_pending(xmit) < WAKEUP_CHARS)
		uart_ग_लिखो_wakeup(&uap->port);

	वापस 1;
पूर्ण

/*
 * We received a transmit पूर्णांकerrupt without a pending X-अक्षर but with
 * pending अक्षरacters.
 * Locking: called with port lock held and IRQs disabled.
 * Returns:
 *   false अगर we want to use PIO to transmit
 *   true अगर we queued a DMA buffer
 */
अटल bool pl011_dma_tx_irq(काष्ठा uart_amba_port *uap)
अणु
	अगर (!uap->using_tx_dma)
		वापस false;

	/*
	 * If we alपढ़ोy have a TX buffer queued, but received a
	 * TX पूर्णांकerrupt, it will be because we've just sent an X-अक्षर.
	 * Ensure the TX DMA is enabled and the TX IRQ is disabled.
	 */
	अगर (uap->dmatx.queued) अणु
		uap->dmacr |= UART011_TXDMAE;
		pl011_ग_लिखो(uap->dmacr, uap, REG_DMACR);
		uap->im &= ~UART011_TXIM;
		pl011_ग_लिखो(uap->im, uap, REG_IMSC);
		वापस true;
	पूर्ण

	/*
	 * We करोn't have a TX buffer queued, so try to queue one.
	 * If we successfully queued a buffer, mask the TX IRQ.
	 */
	अगर (pl011_dma_tx_refill(uap) > 0) अणु
		uap->im &= ~UART011_TXIM;
		pl011_ग_लिखो(uap->im, uap, REG_IMSC);
		वापस true;
	पूर्ण
	वापस false;
पूर्ण

/*
 * Stop the DMA transmit (eg, due to received XOFF).
 * Locking: called with port lock held and IRQs disabled.
 */
अटल अंतरभूत व्योम pl011_dma_tx_stop(काष्ठा uart_amba_port *uap)
अणु
	अगर (uap->dmatx.queued) अणु
		uap->dmacr &= ~UART011_TXDMAE;
		pl011_ग_लिखो(uap->dmacr, uap, REG_DMACR);
	पूर्ण
पूर्ण

/*
 * Try to start a DMA transmit, or in the हाल of an XON/OFF
 * अक्षरacter queued क्रम send, try to get that अक्षरacter out ASAP.
 * Locking: called with port lock held and IRQs disabled.
 * Returns:
 *   false अगर we want the TX IRQ to be enabled
 *   true अगर we have a buffer queued
 */
अटल अंतरभूत bool pl011_dma_tx_start(काष्ठा uart_amba_port *uap)
अणु
	u16 dmacr;

	अगर (!uap->using_tx_dma)
		वापस false;

	अगर (!uap->port.x_अक्षर) अणु
		/* no X-अक्षर, try to push अक्षरs out in DMA mode */
		bool ret = true;

		अगर (!uap->dmatx.queued) अणु
			अगर (pl011_dma_tx_refill(uap) > 0) अणु
				uap->im &= ~UART011_TXIM;
				pl011_ग_लिखो(uap->im, uap, REG_IMSC);
			पूर्ण अन्यथा
				ret = false;
		पूर्ण अन्यथा अगर (!(uap->dmacr & UART011_TXDMAE)) अणु
			uap->dmacr |= UART011_TXDMAE;
			pl011_ग_लिखो(uap->dmacr, uap, REG_DMACR);
		पूर्ण
		वापस ret;
	पूर्ण

	/*
	 * We have an X-अक्षर to send.  Disable DMA to prevent it loading
	 * the TX fअगरo, and then see अगर we can stuff it पूर्णांकo the FIFO.
	 */
	dmacr = uap->dmacr;
	uap->dmacr &= ~UART011_TXDMAE;
	pl011_ग_लिखो(uap->dmacr, uap, REG_DMACR);

	अगर (pl011_पढ़ो(uap, REG_FR) & UART01x_FR_TXFF) अणु
		/*
		 * No space in the FIFO, so enable the transmit पूर्णांकerrupt
		 * so we know when there is space.  Note that once we've
		 * loaded the अक्षरacter, we should just re-enable DMA.
		 */
		वापस false;
	पूर्ण

	pl011_ग_लिखो(uap->port.x_अक्षर, uap, REG_DR);
	uap->port.icount.tx++;
	uap->port.x_अक्षर = 0;

	/* Success - restore the DMA state */
	uap->dmacr = dmacr;
	pl011_ग_लिखो(dmacr, uap, REG_DMACR);

	वापस true;
पूर्ण

/*
 * Flush the transmit buffer.
 * Locking: called with port lock held and IRQs disabled.
 */
अटल व्योम pl011_dma_flush_buffer(काष्ठा uart_port *port)
__releases(&uap->port.lock)
__acquires(&uap->port.lock)
अणु
	काष्ठा uart_amba_port *uap =
	    container_of(port, काष्ठा uart_amba_port, port);

	अगर (!uap->using_tx_dma)
		वापस;

	dmaengine_terminate_async(uap->dmatx.chan);

	अगर (uap->dmatx.queued) अणु
		dma_unmap_sg(uap->dmatx.chan->device->dev, &uap->dmatx.sg, 1,
			     DMA_TO_DEVICE);
		uap->dmatx.queued = false;
		uap->dmacr &= ~UART011_TXDMAE;
		pl011_ग_लिखो(uap->dmacr, uap, REG_DMACR);
	पूर्ण
पूर्ण

अटल व्योम pl011_dma_rx_callback(व्योम *data);

अटल पूर्णांक pl011_dma_rx_trigger_dma(काष्ठा uart_amba_port *uap)
अणु
	काष्ठा dma_chan *rxchan = uap->dmarx.chan;
	काष्ठा pl011_dmarx_data *dmarx = &uap->dmarx;
	काष्ठा dma_async_tx_descriptor *desc;
	काष्ठा pl011_sgbuf *sgbuf;

	अगर (!rxchan)
		वापस -EIO;

	/* Start the RX DMA job */
	sgbuf = uap->dmarx.use_buf_b ?
		&uap->dmarx.sgbuf_b : &uap->dmarx.sgbuf_a;
	desc = dmaengine_prep_slave_sg(rxchan, &sgbuf->sg, 1,
					DMA_DEV_TO_MEM,
					DMA_PREP_INTERRUPT | DMA_CTRL_ACK);
	/*
	 * If the DMA engine is busy and cannot prepare a
	 * channel, no big deal, the driver will fall back
	 * to पूर्णांकerrupt mode as a result of this error code.
	 */
	अगर (!desc) अणु
		uap->dmarx.running = false;
		dmaengine_terminate_all(rxchan);
		वापस -EBUSY;
	पूर्ण

	/* Some data to go aदीर्घ to the callback */
	desc->callback = pl011_dma_rx_callback;
	desc->callback_param = uap;
	dmarx->cookie = dmaengine_submit(desc);
	dma_async_issue_pending(rxchan);

	uap->dmacr |= UART011_RXDMAE;
	pl011_ग_लिखो(uap->dmacr, uap, REG_DMACR);
	uap->dmarx.running = true;

	uap->im &= ~UART011_RXIM;
	pl011_ग_लिखो(uap->im, uap, REG_IMSC);

	वापस 0;
पूर्ण

/*
 * This is called when either the DMA job is complete, or
 * the FIFO समयout पूर्णांकerrupt occurred. This must be called
 * with the port spinlock uap->port.lock held.
 */
अटल व्योम pl011_dma_rx_अक्षरs(काष्ठा uart_amba_port *uap,
			       u32 pending, bool use_buf_b,
			       bool पढ़ोfअगरo)
अणु
	काष्ठा tty_port *port = &uap->port.state->port;
	काष्ठा pl011_sgbuf *sgbuf = use_buf_b ?
		&uap->dmarx.sgbuf_b : &uap->dmarx.sgbuf_a;
	पूर्णांक dma_count = 0;
	u32 fअगरotaken = 0; /* only used क्रम vdbg() */

	काष्ठा pl011_dmarx_data *dmarx = &uap->dmarx;
	पूर्णांक dmataken = 0;

	अगर (uap->dmarx.poll_rate) अणु
		/* The data can be taken by polling */
		dmataken = sgbuf->sg.length - dmarx->last_residue;
		/* Recalculate the pending size */
		अगर (pending >= dmataken)
			pending -= dmataken;
	पूर्ण

	/* Pick the reमुख्य data from the DMA */
	अगर (pending) अणु

		/*
		 * First take all अक्षरs in the DMA pipe, then look in the FIFO.
		 * Note that tty_insert_flip_buf() tries to take as many अक्षरs
		 * as it can.
		 */
		dma_count = tty_insert_flip_string(port, sgbuf->buf + dmataken,
				pending);

		uap->port.icount.rx += dma_count;
		अगर (dma_count < pending)
			dev_warn(uap->port.dev,
				 "couldn't insert all characters (TTY is full?)\n");
	पूर्ण

	/* Reset the last_residue क्रम Rx DMA poll */
	अगर (uap->dmarx.poll_rate)
		dmarx->last_residue = sgbuf->sg.length;

	/*
	 * Only जारी with trying to पढ़ो the FIFO अगर all DMA अक्षरs have
	 * been taken first.
	 */
	अगर (dma_count == pending && पढ़ोfअगरo) अणु
		/* Clear any error flags */
		pl011_ग_लिखो(UART011_OEIS | UART011_BEIS | UART011_PEIS |
			    UART011_FEIS, uap, REG_ICR);

		/*
		 * If we पढ़ो all the DMA'd अक्षरacters, and we had an
		 * incomplete buffer, that could be due to an rx error, or
		 * maybe we just समयd out. Read any pending अक्षरs and check
		 * the error status.
		 *
		 * Error conditions will only occur in the FIFO, these will
		 * trigger an immediate पूर्णांकerrupt and stop the DMA job, so we
		 * will always find the error in the FIFO, never in the DMA
		 * buffer.
		 */
		fअगरotaken = pl011_fअगरo_to_tty(uap);
	पूर्ण

	dev_vdbg(uap->port.dev,
		 "Took %d chars from DMA buffer and %d chars from the FIFO\n",
		 dma_count, fअगरotaken);
	tty_flip_buffer_push(port);
पूर्ण

अटल व्योम pl011_dma_rx_irq(काष्ठा uart_amba_port *uap)
अणु
	काष्ठा pl011_dmarx_data *dmarx = &uap->dmarx;
	काष्ठा dma_chan *rxchan = dmarx->chan;
	काष्ठा pl011_sgbuf *sgbuf = dmarx->use_buf_b ?
		&dmarx->sgbuf_b : &dmarx->sgbuf_a;
	माप_प्रकार pending;
	काष्ठा dma_tx_state state;
	क्रमागत dma_status dmastat;

	/*
	 * Pause the transfer so we can trust the current counter,
	 * करो this beक्रमe we छोड़ो the PL011 block, अन्यथा we may
	 * overflow the FIFO.
	 */
	अगर (dmaengine_छोड़ो(rxchan))
		dev_err(uap->port.dev, "unable to pause DMA transfer\n");
	dmastat = rxchan->device->device_tx_status(rxchan,
						   dmarx->cookie, &state);
	अगर (dmastat != DMA_PAUSED)
		dev_err(uap->port.dev, "unable to pause DMA transfer\n");

	/* Disable RX DMA - incoming data will रुको in the FIFO */
	uap->dmacr &= ~UART011_RXDMAE;
	pl011_ग_लिखो(uap->dmacr, uap, REG_DMACR);
	uap->dmarx.running = false;

	pending = sgbuf->sg.length - state.residue;
	BUG_ON(pending > PL011_DMA_BUFFER_SIZE);
	/* Then we terminate the transfer - we now know our residue */
	dmaengine_terminate_all(rxchan);

	/*
	 * This will take the अक्षरs we have so far and insert
	 * पूर्णांकo the framework.
	 */
	pl011_dma_rx_अक्षरs(uap, pending, dmarx->use_buf_b, true);

	/* Switch buffer & re-trigger DMA job */
	dmarx->use_buf_b = !dmarx->use_buf_b;
	अगर (pl011_dma_rx_trigger_dma(uap)) अणु
		dev_dbg(uap->port.dev, "could not retrigger RX DMA job "
			"fall back to interrupt mode\n");
		uap->im |= UART011_RXIM;
		pl011_ग_लिखो(uap->im, uap, REG_IMSC);
	पूर्ण
पूर्ण

अटल व्योम pl011_dma_rx_callback(व्योम *data)
अणु
	काष्ठा uart_amba_port *uap = data;
	काष्ठा pl011_dmarx_data *dmarx = &uap->dmarx;
	काष्ठा dma_chan *rxchan = dmarx->chan;
	bool lastbuf = dmarx->use_buf_b;
	काष्ठा pl011_sgbuf *sgbuf = dmarx->use_buf_b ?
		&dmarx->sgbuf_b : &dmarx->sgbuf_a;
	माप_प्रकार pending;
	काष्ठा dma_tx_state state;
	पूर्णांक ret;

	/*
	 * This completion पूर्णांकerrupt occurs typically when the
	 * RX buffer is totally stuffed but no समयout has yet
	 * occurred. When that happens, we just want the RX
	 * routine to flush out the secondary DMA buffer जबतक
	 * we immediately trigger the next DMA job.
	 */
	spin_lock_irq(&uap->port.lock);
	/*
	 * Rx data can be taken by the UART पूर्णांकerrupts during
	 * the DMA irq handler. So we check the residue here.
	 */
	rxchan->device->device_tx_status(rxchan, dmarx->cookie, &state);
	pending = sgbuf->sg.length - state.residue;
	BUG_ON(pending > PL011_DMA_BUFFER_SIZE);
	/* Then we terminate the transfer - we now know our residue */
	dmaengine_terminate_all(rxchan);

	uap->dmarx.running = false;
	dmarx->use_buf_b = !lastbuf;
	ret = pl011_dma_rx_trigger_dma(uap);

	pl011_dma_rx_अक्षरs(uap, pending, lastbuf, false);
	spin_unlock_irq(&uap->port.lock);
	/*
	 * Do this check after we picked the DMA अक्षरs so we करोn't
	 * get some IRQ immediately from RX.
	 */
	अगर (ret) अणु
		dev_dbg(uap->port.dev, "could not retrigger RX DMA job "
			"fall back to interrupt mode\n");
		uap->im |= UART011_RXIM;
		pl011_ग_लिखो(uap->im, uap, REG_IMSC);
	पूर्ण
पूर्ण

/*
 * Stop accepting received अक्षरacters, when we're shutting करोwn or
 * suspending this port.
 * Locking: called with port lock held and IRQs disabled.
 */
अटल अंतरभूत व्योम pl011_dma_rx_stop(काष्ठा uart_amba_port *uap)
अणु
	/* FIXME.  Just disable the DMA enable */
	uap->dmacr &= ~UART011_RXDMAE;
	pl011_ग_लिखो(uap->dmacr, uap, REG_DMACR);
पूर्ण

/*
 * Timer handler क्रम Rx DMA polling.
 * Every polling, It checks the residue in the dma buffer and transfer
 * data to the tty. Also, last_residue is updated क्रम the next polling.
 */
अटल व्योम pl011_dma_rx_poll(काष्ठा समयr_list *t)
अणु
	काष्ठा uart_amba_port *uap = from_समयr(uap, t, dmarx.समयr);
	काष्ठा tty_port *port = &uap->port.state->port;
	काष्ठा pl011_dmarx_data *dmarx = &uap->dmarx;
	काष्ठा dma_chan *rxchan = uap->dmarx.chan;
	अचिन्हित दीर्घ flags = 0;
	अचिन्हित पूर्णांक dmataken = 0;
	अचिन्हित पूर्णांक size = 0;
	काष्ठा pl011_sgbuf *sgbuf;
	पूर्णांक dma_count;
	काष्ठा dma_tx_state state;

	sgbuf = dmarx->use_buf_b ? &uap->dmarx.sgbuf_b : &uap->dmarx.sgbuf_a;
	rxchan->device->device_tx_status(rxchan, dmarx->cookie, &state);
	अगर (likely(state.residue < dmarx->last_residue)) अणु
		dmataken = sgbuf->sg.length - dmarx->last_residue;
		size = dmarx->last_residue - state.residue;
		dma_count = tty_insert_flip_string(port, sgbuf->buf + dmataken,
				size);
		अगर (dma_count == size)
			dmarx->last_residue =  state.residue;
		dmarx->last_jअगरfies = jअगरfies;
	पूर्ण
	tty_flip_buffer_push(port);

	/*
	 * If no data is received in poll_समयout, the driver will fall back
	 * to पूर्णांकerrupt mode. We will retrigger DMA at the first पूर्णांकerrupt.
	 */
	अगर (jअगरfies_to_msecs(jअगरfies - dmarx->last_jअगरfies)
			> uap->dmarx.poll_समयout) अणु

		spin_lock_irqsave(&uap->port.lock, flags);
		pl011_dma_rx_stop(uap);
		uap->im |= UART011_RXIM;
		pl011_ग_लिखो(uap->im, uap, REG_IMSC);
		spin_unlock_irqrestore(&uap->port.lock, flags);

		uap->dmarx.running = false;
		dmaengine_terminate_all(rxchan);
		del_समयr(&uap->dmarx.समयr);
	पूर्ण अन्यथा अणु
		mod_समयr(&uap->dmarx.समयr,
			jअगरfies + msecs_to_jअगरfies(uap->dmarx.poll_rate));
	पूर्ण
पूर्ण

अटल व्योम pl011_dma_startup(काष्ठा uart_amba_port *uap)
अणु
	पूर्णांक ret;

	अगर (!uap->dma_probed)
		pl011_dma_probe(uap);

	अगर (!uap->dmatx.chan)
		वापस;

	uap->dmatx.buf = kदो_स्मृति(PL011_DMA_BUFFER_SIZE, GFP_KERNEL | __GFP_DMA);
	अगर (!uap->dmatx.buf) अणु
		dev_err(uap->port.dev, "no memory for DMA TX buffer\n");
		uap->port.fअगरosize = uap->fअगरosize;
		वापस;
	पूर्ण

	sg_init_one(&uap->dmatx.sg, uap->dmatx.buf, PL011_DMA_BUFFER_SIZE);

	/* The DMA buffer is now the FIFO the TTY subप्रणाली can use */
	uap->port.fअगरosize = PL011_DMA_BUFFER_SIZE;
	uap->using_tx_dma = true;

	अगर (!uap->dmarx.chan)
		जाओ skip_rx;

	/* Allocate and map DMA RX buffers */
	ret = pl011_sgbuf_init(uap->dmarx.chan, &uap->dmarx.sgbuf_a,
			       DMA_FROM_DEVICE);
	अगर (ret) अणु
		dev_err(uap->port.dev, "failed to init DMA %s: %d\n",
			"RX buffer A", ret);
		जाओ skip_rx;
	पूर्ण

	ret = pl011_sgbuf_init(uap->dmarx.chan, &uap->dmarx.sgbuf_b,
			       DMA_FROM_DEVICE);
	अगर (ret) अणु
		dev_err(uap->port.dev, "failed to init DMA %s: %d\n",
			"RX buffer B", ret);
		pl011_sgbuf_मुक्त(uap->dmarx.chan, &uap->dmarx.sgbuf_a,
				 DMA_FROM_DEVICE);
		जाओ skip_rx;
	पूर्ण

	uap->using_rx_dma = true;

skip_rx:
	/* Turn on DMA error (RX/TX will be enabled on demand) */
	uap->dmacr |= UART011_DMAONERR;
	pl011_ग_लिखो(uap->dmacr, uap, REG_DMACR);

	/*
	 * ST Micro variants has some specअगरic dma burst threshold
	 * compensation. Set this to 16 bytes, so burst will only
	 * be issued above/below 16 bytes.
	 */
	अगर (uap->venकरोr->dma_threshold)
		pl011_ग_लिखो(ST_UART011_DMAWM_RX_16 | ST_UART011_DMAWM_TX_16,
			    uap, REG_ST_DMAWM);

	अगर (uap->using_rx_dma) अणु
		अगर (pl011_dma_rx_trigger_dma(uap))
			dev_dbg(uap->port.dev, "could not trigger initial "
				"RX DMA job, fall back to interrupt mode\n");
		अगर (uap->dmarx.poll_rate) अणु
			समयr_setup(&uap->dmarx.समयr, pl011_dma_rx_poll, 0);
			mod_समयr(&uap->dmarx.समयr,
				jअगरfies +
				msecs_to_jअगरfies(uap->dmarx.poll_rate));
			uap->dmarx.last_residue = PL011_DMA_BUFFER_SIZE;
			uap->dmarx.last_jअगरfies = jअगरfies;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम pl011_dma_shutकरोwn(काष्ठा uart_amba_port *uap)
अणु
	अगर (!(uap->using_tx_dma || uap->using_rx_dma))
		वापस;

	/* Disable RX and TX DMA */
	जबतक (pl011_पढ़ो(uap, REG_FR) & uap->venकरोr->fr_busy)
		cpu_relax();

	spin_lock_irq(&uap->port.lock);
	uap->dmacr &= ~(UART011_DMAONERR | UART011_RXDMAE | UART011_TXDMAE);
	pl011_ग_लिखो(uap->dmacr, uap, REG_DMACR);
	spin_unlock_irq(&uap->port.lock);

	अगर (uap->using_tx_dma) अणु
		/* In theory, this should alपढ़ोy be करोne by pl011_dma_flush_buffer */
		dmaengine_terminate_all(uap->dmatx.chan);
		अगर (uap->dmatx.queued) अणु
			dma_unmap_sg(uap->dmatx.chan->device->dev, &uap->dmatx.sg, 1,
				     DMA_TO_DEVICE);
			uap->dmatx.queued = false;
		पूर्ण

		kमुक्त(uap->dmatx.buf);
		uap->using_tx_dma = false;
	पूर्ण

	अगर (uap->using_rx_dma) अणु
		dmaengine_terminate_all(uap->dmarx.chan);
		/* Clean up the RX DMA */
		pl011_sgbuf_मुक्त(uap->dmarx.chan, &uap->dmarx.sgbuf_a, DMA_FROM_DEVICE);
		pl011_sgbuf_मुक्त(uap->dmarx.chan, &uap->dmarx.sgbuf_b, DMA_FROM_DEVICE);
		अगर (uap->dmarx.poll_rate)
			del_समयr_sync(&uap->dmarx.समयr);
		uap->using_rx_dma = false;
	पूर्ण
पूर्ण

अटल अंतरभूत bool pl011_dma_rx_available(काष्ठा uart_amba_port *uap)
अणु
	वापस uap->using_rx_dma;
पूर्ण

अटल अंतरभूत bool pl011_dma_rx_running(काष्ठा uart_amba_port *uap)
अणु
	वापस uap->using_rx_dma && uap->dmarx.running;
पूर्ण

#अन्यथा
/* Blank functions अगर the DMA engine is not available */
अटल अंतरभूत व्योम pl011_dma_हटाओ(काष्ठा uart_amba_port *uap)
अणु
पूर्ण

अटल अंतरभूत व्योम pl011_dma_startup(काष्ठा uart_amba_port *uap)
अणु
पूर्ण

अटल अंतरभूत व्योम pl011_dma_shutकरोwn(काष्ठा uart_amba_port *uap)
अणु
पूर्ण

अटल अंतरभूत bool pl011_dma_tx_irq(काष्ठा uart_amba_port *uap)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत व्योम pl011_dma_tx_stop(काष्ठा uart_amba_port *uap)
अणु
पूर्ण

अटल अंतरभूत bool pl011_dma_tx_start(काष्ठा uart_amba_port *uap)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत व्योम pl011_dma_rx_irq(काष्ठा uart_amba_port *uap)
अणु
पूर्ण

अटल अंतरभूत व्योम pl011_dma_rx_stop(काष्ठा uart_amba_port *uap)
अणु
पूर्ण

अटल अंतरभूत पूर्णांक pl011_dma_rx_trigger_dma(काष्ठा uart_amba_port *uap)
अणु
	वापस -EIO;
पूर्ण

अटल अंतरभूत bool pl011_dma_rx_available(काष्ठा uart_amba_port *uap)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत bool pl011_dma_rx_running(काष्ठा uart_amba_port *uap)
अणु
	वापस false;
पूर्ण

#घोषणा pl011_dma_flush_buffer	शून्य
#पूर्ण_अगर

अटल व्योम pl011_stop_tx(काष्ठा uart_port *port)
अणु
	काष्ठा uart_amba_port *uap =
	    container_of(port, काष्ठा uart_amba_port, port);

	uap->im &= ~UART011_TXIM;
	pl011_ग_लिखो(uap->im, uap, REG_IMSC);
	pl011_dma_tx_stop(uap);
पूर्ण

अटल bool pl011_tx_अक्षरs(काष्ठा uart_amba_port *uap, bool from_irq);

/* Start TX with programmed I/O only (no DMA) */
अटल व्योम pl011_start_tx_pio(काष्ठा uart_amba_port *uap)
अणु
	अगर (pl011_tx_अक्षरs(uap, false)) अणु
		uap->im |= UART011_TXIM;
		pl011_ग_लिखो(uap->im, uap, REG_IMSC);
	पूर्ण
पूर्ण

अटल व्योम pl011_start_tx(काष्ठा uart_port *port)
अणु
	काष्ठा uart_amba_port *uap =
	    container_of(port, काष्ठा uart_amba_port, port);

	अगर (!pl011_dma_tx_start(uap))
		pl011_start_tx_pio(uap);
पूर्ण

अटल व्योम pl011_stop_rx(काष्ठा uart_port *port)
अणु
	काष्ठा uart_amba_port *uap =
	    container_of(port, काष्ठा uart_amba_port, port);

	uap->im &= ~(UART011_RXIM|UART011_RTIM|UART011_FEIM|
		     UART011_PEIM|UART011_BEIM|UART011_OEIM);
	pl011_ग_लिखो(uap->im, uap, REG_IMSC);

	pl011_dma_rx_stop(uap);
पूर्ण

अटल व्योम pl011_enable_ms(काष्ठा uart_port *port)
अणु
	काष्ठा uart_amba_port *uap =
	    container_of(port, काष्ठा uart_amba_port, port);

	uap->im |= UART011_RIMIM|UART011_CTSMIM|UART011_DCDMIM|UART011_DSRMIM;
	pl011_ग_लिखो(uap->im, uap, REG_IMSC);
पूर्ण

अटल व्योम pl011_rx_अक्षरs(काष्ठा uart_amba_port *uap)
__releases(&uap->port.lock)
__acquires(&uap->port.lock)
अणु
	pl011_fअगरo_to_tty(uap);

	spin_unlock(&uap->port.lock);
	tty_flip_buffer_push(&uap->port.state->port);
	/*
	 * If we were temporarily out of DMA mode क्रम a जबतक,
	 * attempt to चयन back to DMA mode again.
	 */
	अगर (pl011_dma_rx_available(uap)) अणु
		अगर (pl011_dma_rx_trigger_dma(uap)) अणु
			dev_dbg(uap->port.dev, "could not trigger RX DMA job "
				"fall back to interrupt mode again\n");
			uap->im |= UART011_RXIM;
			pl011_ग_लिखो(uap->im, uap, REG_IMSC);
		पूर्ण अन्यथा अणु
#अगर_घोषित CONFIG_DMA_ENGINE
			/* Start Rx DMA poll */
			अगर (uap->dmarx.poll_rate) अणु
				uap->dmarx.last_jअगरfies = jअगरfies;
				uap->dmarx.last_residue	= PL011_DMA_BUFFER_SIZE;
				mod_समयr(&uap->dmarx.समयr,
					jअगरfies +
					msecs_to_jअगरfies(uap->dmarx.poll_rate));
			पूर्ण
#पूर्ण_अगर
		पूर्ण
	पूर्ण
	spin_lock(&uap->port.lock);
पूर्ण

अटल bool pl011_tx_अक्षर(काष्ठा uart_amba_port *uap, अचिन्हित अक्षर c,
			  bool from_irq)
अणु
	अगर (unlikely(!from_irq) &&
	    pl011_पढ़ो(uap, REG_FR) & UART01x_FR_TXFF)
		वापस false; /* unable to transmit अक्षरacter */

	pl011_ग_लिखो(c, uap, REG_DR);
	uap->port.icount.tx++;

	वापस true;
पूर्ण

/* Returns true अगर tx पूर्णांकerrupts have to be (kept) enabled  */
अटल bool pl011_tx_अक्षरs(काष्ठा uart_amba_port *uap, bool from_irq)
अणु
	काष्ठा circ_buf *xmit = &uap->port.state->xmit;
	पूर्णांक count = uap->fअगरosize >> 1;

	अगर (uap->port.x_अक्षर) अणु
		अगर (!pl011_tx_अक्षर(uap, uap->port.x_अक्षर, from_irq))
			वापस true;
		uap->port.x_अक्षर = 0;
		--count;
	पूर्ण
	अगर (uart_circ_empty(xmit) || uart_tx_stopped(&uap->port)) अणु
		pl011_stop_tx(&uap->port);
		वापस false;
	पूर्ण

	/* If we are using DMA mode, try to send some अक्षरacters. */
	अगर (pl011_dma_tx_irq(uap))
		वापस true;

	करो अणु
		अगर (likely(from_irq) && count-- == 0)
			अवरोध;

		अगर (!pl011_tx_अक्षर(uap, xmit->buf[xmit->tail], from_irq))
			अवरोध;

		xmit->tail = (xmit->tail + 1) & (UART_XMIT_SIZE - 1);
	पूर्ण जबतक (!uart_circ_empty(xmit));

	अगर (uart_circ_अक्षरs_pending(xmit) < WAKEUP_CHARS)
		uart_ग_लिखो_wakeup(&uap->port);

	अगर (uart_circ_empty(xmit)) अणु
		pl011_stop_tx(&uap->port);
		वापस false;
	पूर्ण
	वापस true;
पूर्ण

अटल व्योम pl011_modem_status(काष्ठा uart_amba_port *uap)
अणु
	अचिन्हित पूर्णांक status, delta;

	status = pl011_पढ़ो(uap, REG_FR) & UART01x_FR_MODEM_ANY;

	delta = status ^ uap->old_status;
	uap->old_status = status;

	अगर (!delta)
		वापस;

	अगर (delta & UART01x_FR_DCD)
		uart_handle_dcd_change(&uap->port, status & UART01x_FR_DCD);

	अगर (delta & uap->venकरोr->fr_dsr)
		uap->port.icount.dsr++;

	अगर (delta & uap->venकरोr->fr_cts)
		uart_handle_cts_change(&uap->port,
				       status & uap->venकरोr->fr_cts);

	wake_up_पूर्णांकerruptible(&uap->port.state->port.delta_msr_रुको);
पूर्ण

अटल व्योम check_apply_cts_event_workaround(काष्ठा uart_amba_port *uap)
अणु
	अगर (!uap->venकरोr->cts_event_workaround)
		वापस;

	/* workaround to make sure that all bits are unlocked.. */
	pl011_ग_लिखो(0x00, uap, REG_ICR);

	/*
	 * WA: पूर्णांकroduce 26ns(1 uart clk) delay beक्रमe W1C;
	 * single apb access will incur 2 pclk(133.12Mhz) delay,
	 * so add 2 dummy पढ़ोs
	 */
	pl011_पढ़ो(uap, REG_ICR);
	pl011_पढ़ो(uap, REG_ICR);
पूर्ण

अटल irqवापस_t pl011_पूर्णांक(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा uart_amba_port *uap = dev_id;
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक status, pass_counter = AMBA_ISR_PASS_LIMIT;
	पूर्णांक handled = 0;

	spin_lock_irqsave(&uap->port.lock, flags);
	status = pl011_पढ़ो(uap, REG_RIS) & uap->im;
	अगर (status) अणु
		करो अणु
			check_apply_cts_event_workaround(uap);

			pl011_ग_लिखो(status & ~(UART011_TXIS|UART011_RTIS|
					       UART011_RXIS),
				    uap, REG_ICR);

			अगर (status & (UART011_RTIS|UART011_RXIS)) अणु
				अगर (pl011_dma_rx_running(uap))
					pl011_dma_rx_irq(uap);
				अन्यथा
					pl011_rx_अक्षरs(uap);
			पूर्ण
			अगर (status & (UART011_DSRMIS|UART011_DCDMIS|
				      UART011_CTSMIS|UART011_RIMIS))
				pl011_modem_status(uap);
			अगर (status & UART011_TXIS)
				pl011_tx_अक्षरs(uap, true);

			अगर (pass_counter-- == 0)
				अवरोध;

			status = pl011_पढ़ो(uap, REG_RIS) & uap->im;
		पूर्ण जबतक (status != 0);
		handled = 1;
	पूर्ण

	spin_unlock_irqrestore(&uap->port.lock, flags);

	वापस IRQ_RETVAL(handled);
पूर्ण

अटल अचिन्हित पूर्णांक pl011_tx_empty(काष्ठा uart_port *port)
अणु
	काष्ठा uart_amba_port *uap =
	    container_of(port, काष्ठा uart_amba_port, port);

	/* Allow feature रेजिस्टर bits to be inverted to work around errata */
	अचिन्हित पूर्णांक status = pl011_पढ़ो(uap, REG_FR) ^ uap->venकरोr->inv_fr;

	वापस status & (uap->venकरोr->fr_busy | UART01x_FR_TXFF) ?
							0 : TIOCSER_TEMT;
पूर्ण

अटल अचिन्हित पूर्णांक pl011_get_mctrl(काष्ठा uart_port *port)
अणु
	काष्ठा uart_amba_port *uap =
	    container_of(port, काष्ठा uart_amba_port, port);
	अचिन्हित पूर्णांक result = 0;
	अचिन्हित पूर्णांक status = pl011_पढ़ो(uap, REG_FR);

#घोषणा TIOCMBIT(uartbit, tiocmbit)	\
	अगर (status & uartbit)		\
		result |= tiocmbit

	TIOCMBIT(UART01x_FR_DCD, TIOCM_CAR);
	TIOCMBIT(uap->venकरोr->fr_dsr, TIOCM_DSR);
	TIOCMBIT(uap->venकरोr->fr_cts, TIOCM_CTS);
	TIOCMBIT(uap->venकरोr->fr_ri, TIOCM_RNG);
#अघोषित TIOCMBIT
	वापस result;
पूर्ण

अटल व्योम pl011_set_mctrl(काष्ठा uart_port *port, अचिन्हित पूर्णांक mctrl)
अणु
	काष्ठा uart_amba_port *uap =
	    container_of(port, काष्ठा uart_amba_port, port);
	अचिन्हित पूर्णांक cr;

	cr = pl011_पढ़ो(uap, REG_CR);

#घोषणा	TIOCMBIT(tiocmbit, uartbit)		\
	अगर (mctrl & tiocmbit)		\
		cr |= uartbit;		\
	अन्यथा				\
		cr &= ~uartbit

	TIOCMBIT(TIOCM_RTS, UART011_CR_RTS);
	TIOCMBIT(TIOCM_DTR, UART011_CR_DTR);
	TIOCMBIT(TIOCM_OUT1, UART011_CR_OUT1);
	TIOCMBIT(TIOCM_OUT2, UART011_CR_OUT2);
	TIOCMBIT(TIOCM_LOOP, UART011_CR_LBE);

	अगर (port->status & UPSTAT_AUTORTS) अणु
		/* We need to disable स्वतः-RTS अगर we want to turn RTS off */
		TIOCMBIT(TIOCM_RTS, UART011_CR_RTSEN);
	पूर्ण
#अघोषित TIOCMBIT

	pl011_ग_लिखो(cr, uap, REG_CR);
पूर्ण

अटल व्योम pl011_अवरोध_ctl(काष्ठा uart_port *port, पूर्णांक अवरोध_state)
अणु
	काष्ठा uart_amba_port *uap =
	    container_of(port, काष्ठा uart_amba_port, port);
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक lcr_h;

	spin_lock_irqsave(&uap->port.lock, flags);
	lcr_h = pl011_पढ़ो(uap, REG_LCRH_TX);
	अगर (अवरोध_state == -1)
		lcr_h |= UART01x_LCRH_BRK;
	अन्यथा
		lcr_h &= ~UART01x_LCRH_BRK;
	pl011_ग_लिखो(lcr_h, uap, REG_LCRH_TX);
	spin_unlock_irqrestore(&uap->port.lock, flags);
पूर्ण

#अगर_घोषित CONFIG_CONSOLE_POLL

अटल व्योम pl011_quiesce_irqs(काष्ठा uart_port *port)
अणु
	काष्ठा uart_amba_port *uap =
	    container_of(port, काष्ठा uart_amba_port, port);

	pl011_ग_लिखो(pl011_पढ़ो(uap, REG_MIS), uap, REG_ICR);
	/*
	 * There is no way to clear TXIM as this is "ready to transmit IRQ", so
	 * we simply mask it. start_tx() will unmask it.
	 *
	 * Note we can race with start_tx(), and अगर the race happens, the
	 * polling user might get another पूर्णांकerrupt just after we clear it.
	 * But it should be OK and can happen even w/o the race, e.g.
	 * controller immediately got some new data and उठाओd the IRQ.
	 *
	 * And whoever uses polling routines assumes that it manages the device
	 * (including tx queue), so we're also fine with start_tx()'s caller
	 * side.
	 */
	pl011_ग_लिखो(pl011_पढ़ो(uap, REG_IMSC) & ~UART011_TXIM, uap,
		    REG_IMSC);
पूर्ण

अटल पूर्णांक pl011_get_poll_अक्षर(काष्ठा uart_port *port)
अणु
	काष्ठा uart_amba_port *uap =
	    container_of(port, काष्ठा uart_amba_port, port);
	अचिन्हित पूर्णांक status;

	/*
	 * The caller might need IRQs lowered, e.g. अगर used with KDB NMI
	 * debugger.
	 */
	pl011_quiesce_irqs(port);

	status = pl011_पढ़ो(uap, REG_FR);
	अगर (status & UART01x_FR_RXFE)
		वापस NO_POLL_CHAR;

	वापस pl011_पढ़ो(uap, REG_DR);
पूर्ण

अटल व्योम pl011_put_poll_अक्षर(काष्ठा uart_port *port,
			 अचिन्हित अक्षर ch)
अणु
	काष्ठा uart_amba_port *uap =
	    container_of(port, काष्ठा uart_amba_port, port);

	जबतक (pl011_पढ़ो(uap, REG_FR) & UART01x_FR_TXFF)
		cpu_relax();

	pl011_ग_लिखो(ch, uap, REG_DR);
पूर्ण

#पूर्ण_अगर /* CONFIG_CONSOLE_POLL */

अटल पूर्णांक pl011_hwinit(काष्ठा uart_port *port)
अणु
	काष्ठा uart_amba_port *uap =
	    container_of(port, काष्ठा uart_amba_port, port);
	पूर्णांक retval;

	/* Optionaly enable pins to be muxed in and configured */
	pinctrl_pm_select_शेष_state(port->dev);

	/*
	 * Try to enable the घड़ी producer.
	 */
	retval = clk_prepare_enable(uap->clk);
	अगर (retval)
		वापस retval;

	uap->port.uartclk = clk_get_rate(uap->clk);

	/* Clear pending error and receive पूर्णांकerrupts */
	pl011_ग_लिखो(UART011_OEIS | UART011_BEIS | UART011_PEIS |
		    UART011_FEIS | UART011_RTIS | UART011_RXIS,
		    uap, REG_ICR);

	/*
	 * Save पूर्णांकerrupts enable mask, and enable RX पूर्णांकerrupts in हाल अगर
	 * the पूर्णांकerrupt is used क्रम NMI entry.
	 */
	uap->im = pl011_पढ़ो(uap, REG_IMSC);
	pl011_ग_लिखो(UART011_RTIM | UART011_RXIM, uap, REG_IMSC);

	अगर (dev_get_platdata(uap->port.dev)) अणु
		काष्ठा amba_pl011_data *plat;

		plat = dev_get_platdata(uap->port.dev);
		अगर (plat->init)
			plat->init();
	पूर्ण
	वापस 0;
पूर्ण

अटल bool pl011_split_lcrh(स्थिर काष्ठा uart_amba_port *uap)
अणु
	वापस pl011_reg_to_offset(uap, REG_LCRH_RX) !=
	       pl011_reg_to_offset(uap, REG_LCRH_TX);
पूर्ण

अटल व्योम pl011_ग_लिखो_lcr_h(काष्ठा uart_amba_port *uap, अचिन्हित पूर्णांक lcr_h)
अणु
	pl011_ग_लिखो(lcr_h, uap, REG_LCRH_RX);
	अगर (pl011_split_lcrh(uap)) अणु
		पूर्णांक i;
		/*
		 * Wait 10 PCLKs beक्रमe writing LCRH_TX रेजिस्टर,
		 * to get this delay ग_लिखो पढ़ो only रेजिस्टर 10 बार
		 */
		क्रम (i = 0; i < 10; ++i)
			pl011_ग_लिखो(0xff, uap, REG_MIS);
		pl011_ग_लिखो(lcr_h, uap, REG_LCRH_TX);
	पूर्ण
पूर्ण

अटल पूर्णांक pl011_allocate_irq(काष्ठा uart_amba_port *uap)
अणु
	pl011_ग_लिखो(uap->im, uap, REG_IMSC);

	वापस request_irq(uap->port.irq, pl011_पूर्णांक, IRQF_SHARED, "uart-pl011", uap);
पूर्ण

/*
 * Enable पूर्णांकerrupts, only समयouts when using DMA
 * अगर initial RX DMA job failed, start in पूर्णांकerrupt mode
 * as well.
 */
अटल व्योम pl011_enable_पूर्णांकerrupts(काष्ठा uart_amba_port *uap)
अणु
	अचिन्हित पूर्णांक i;

	spin_lock_irq(&uap->port.lock);

	/* Clear out any spuriously appearing RX पूर्णांकerrupts */
	pl011_ग_लिखो(UART011_RTIS | UART011_RXIS, uap, REG_ICR);

	/*
	 * RXIS is निश्चितed only when the RX FIFO transitions from below
	 * to above the trigger threshold.  If the RX FIFO is alपढ़ोy
	 * full to the threshold this can't happen and RXIS will now be
	 * stuck off.  Drain the RX FIFO explicitly to fix this:
	 */
	क्रम (i = 0; i < uap->fअगरosize * 2; ++i) अणु
		अगर (pl011_पढ़ो(uap, REG_FR) & UART01x_FR_RXFE)
			अवरोध;

		pl011_पढ़ो(uap, REG_DR);
	पूर्ण

	uap->im = UART011_RTIM;
	अगर (!pl011_dma_rx_running(uap))
		uap->im |= UART011_RXIM;
	pl011_ग_लिखो(uap->im, uap, REG_IMSC);
	spin_unlock_irq(&uap->port.lock);
पूर्ण

अटल पूर्णांक pl011_startup(काष्ठा uart_port *port)
अणु
	काष्ठा uart_amba_port *uap =
	    container_of(port, काष्ठा uart_amba_port, port);
	अचिन्हित पूर्णांक cr;
	पूर्णांक retval;

	retval = pl011_hwinit(port);
	अगर (retval)
		जाओ clk_dis;

	retval = pl011_allocate_irq(uap);
	अगर (retval)
		जाओ clk_dis;

	pl011_ग_लिखो(uap->venकरोr->अगरls, uap, REG_IFLS);

	spin_lock_irq(&uap->port.lock);

	/* restore RTS and DTR */
	cr = uap->old_cr & (UART011_CR_RTS | UART011_CR_DTR);
	cr |= UART01x_CR_UARTEN | UART011_CR_RXE | UART011_CR_TXE;
	pl011_ग_लिखो(cr, uap, REG_CR);

	spin_unlock_irq(&uap->port.lock);

	/*
	 * initialise the old status of the modem संकेतs
	 */
	uap->old_status = pl011_पढ़ो(uap, REG_FR) & UART01x_FR_MODEM_ANY;

	/* Startup DMA */
	pl011_dma_startup(uap);

	pl011_enable_पूर्णांकerrupts(uap);

	वापस 0;

 clk_dis:
	clk_disable_unprepare(uap->clk);
	वापस retval;
पूर्ण

अटल पूर्णांक sbsa_uart_startup(काष्ठा uart_port *port)
अणु
	काष्ठा uart_amba_port *uap =
		container_of(port, काष्ठा uart_amba_port, port);
	पूर्णांक retval;

	retval = pl011_hwinit(port);
	अगर (retval)
		वापस retval;

	retval = pl011_allocate_irq(uap);
	अगर (retval)
		वापस retval;

	/* The SBSA UART करोes not support any modem status lines. */
	uap->old_status = 0;

	pl011_enable_पूर्णांकerrupts(uap);

	वापस 0;
पूर्ण

अटल व्योम pl011_shutकरोwn_channel(काष्ठा uart_amba_port *uap,
					अचिन्हित पूर्णांक lcrh)
अणु
      अचिन्हित दीर्घ val;

      val = pl011_पढ़ो(uap, lcrh);
      val &= ~(UART01x_LCRH_BRK | UART01x_LCRH_FEN);
      pl011_ग_लिखो(val, uap, lcrh);
पूर्ण

/*
 * disable the port. It should not disable RTS and DTR.
 * Also RTS and DTR state should be preserved to restore
 * it during startup().
 */
अटल व्योम pl011_disable_uart(काष्ठा uart_amba_port *uap)
अणु
	अचिन्हित पूर्णांक cr;

	uap->port.status &= ~(UPSTAT_AUTOCTS | UPSTAT_AUTORTS);
	spin_lock_irq(&uap->port.lock);
	cr = pl011_पढ़ो(uap, REG_CR);
	uap->old_cr = cr;
	cr &= UART011_CR_RTS | UART011_CR_DTR;
	cr |= UART01x_CR_UARTEN | UART011_CR_TXE;
	pl011_ग_लिखो(cr, uap, REG_CR);
	spin_unlock_irq(&uap->port.lock);

	/*
	 * disable अवरोध condition and fअगरos
	 */
	pl011_shutकरोwn_channel(uap, REG_LCRH_RX);
	अगर (pl011_split_lcrh(uap))
		pl011_shutकरोwn_channel(uap, REG_LCRH_TX);
पूर्ण

अटल व्योम pl011_disable_पूर्णांकerrupts(काष्ठा uart_amba_port *uap)
अणु
	spin_lock_irq(&uap->port.lock);

	/* mask all पूर्णांकerrupts and clear all pending ones */
	uap->im = 0;
	pl011_ग_लिखो(uap->im, uap, REG_IMSC);
	pl011_ग_लिखो(0xffff, uap, REG_ICR);

	spin_unlock_irq(&uap->port.lock);
पूर्ण

अटल व्योम pl011_shutकरोwn(काष्ठा uart_port *port)
अणु
	काष्ठा uart_amba_port *uap =
		container_of(port, काष्ठा uart_amba_port, port);

	pl011_disable_पूर्णांकerrupts(uap);

	pl011_dma_shutकरोwn(uap);

	मुक्त_irq(uap->port.irq, uap);

	pl011_disable_uart(uap);

	/*
	 * Shut करोwn the घड़ी producer
	 */
	clk_disable_unprepare(uap->clk);
	/* Optionally let pins go पूर्णांकo sleep states */
	pinctrl_pm_select_sleep_state(port->dev);

	अगर (dev_get_platdata(uap->port.dev)) अणु
		काष्ठा amba_pl011_data *plat;

		plat = dev_get_platdata(uap->port.dev);
		अगर (plat->निकास)
			plat->निकास();
	पूर्ण

	अगर (uap->port.ops->flush_buffer)
		uap->port.ops->flush_buffer(port);
पूर्ण

अटल व्योम sbsa_uart_shutकरोwn(काष्ठा uart_port *port)
अणु
	काष्ठा uart_amba_port *uap =
		container_of(port, काष्ठा uart_amba_port, port);

	pl011_disable_पूर्णांकerrupts(uap);

	मुक्त_irq(uap->port.irq, uap);

	अगर (uap->port.ops->flush_buffer)
		uap->port.ops->flush_buffer(port);
पूर्ण

अटल व्योम
pl011_setup_status_masks(काष्ठा uart_port *port, काष्ठा ktermios *termios)
अणु
	port->पढ़ो_status_mask = UART011_DR_OE | 255;
	अगर (termios->c_अगरlag & INPCK)
		port->पढ़ो_status_mask |= UART011_DR_FE | UART011_DR_PE;
	अगर (termios->c_अगरlag & (IGNBRK | BRKINT | PARMRK))
		port->पढ़ो_status_mask |= UART011_DR_BE;

	/*
	 * Characters to ignore
	 */
	port->ignore_status_mask = 0;
	अगर (termios->c_अगरlag & IGNPAR)
		port->ignore_status_mask |= UART011_DR_FE | UART011_DR_PE;
	अगर (termios->c_अगरlag & IGNBRK) अणु
		port->ignore_status_mask |= UART011_DR_BE;
		/*
		 * If we're ignoring parity and अवरोध indicators,
		 * ignore overruns too (क्रम real raw support).
		 */
		अगर (termios->c_अगरlag & IGNPAR)
			port->ignore_status_mask |= UART011_DR_OE;
	पूर्ण

	/*
	 * Ignore all अक्षरacters अगर CREAD is not set.
	 */
	अगर ((termios->c_cflag & CREAD) == 0)
		port->ignore_status_mask |= UART_DUMMY_DR_RX;
पूर्ण

अटल व्योम
pl011_set_termios(काष्ठा uart_port *port, काष्ठा ktermios *termios,
		     काष्ठा ktermios *old)
अणु
	काष्ठा uart_amba_port *uap =
	    container_of(port, काष्ठा uart_amba_port, port);
	अचिन्हित पूर्णांक lcr_h, old_cr;
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक baud, quot, clkभाग;

	अगर (uap->venकरोr->oversampling)
		clkभाग = 8;
	अन्यथा
		clkभाग = 16;

	/*
	 * Ask the core to calculate the भागisor क्रम us.
	 */
	baud = uart_get_baud_rate(port, termios, old, 0,
				  port->uartclk / clkभाग);
#अगर_घोषित CONFIG_DMA_ENGINE
	/*
	 * Adjust RX DMA polling rate with baud rate अगर not specअगरied.
	 */
	अगर (uap->dmarx.स्वतः_poll_rate)
		uap->dmarx.poll_rate = DIV_ROUND_UP(10000000, baud);
#पूर्ण_अगर

	अगर (baud > port->uartclk/16)
		quot = DIV_ROUND_CLOSEST(port->uartclk * 8, baud);
	अन्यथा
		quot = DIV_ROUND_CLOSEST(port->uartclk * 4, baud);

	चयन (termios->c_cflag & CSIZE) अणु
	हाल CS5:
		lcr_h = UART01x_LCRH_WLEN_5;
		अवरोध;
	हाल CS6:
		lcr_h = UART01x_LCRH_WLEN_6;
		अवरोध;
	हाल CS7:
		lcr_h = UART01x_LCRH_WLEN_7;
		अवरोध;
	शेष: // CS8
		lcr_h = UART01x_LCRH_WLEN_8;
		अवरोध;
	पूर्ण
	अगर (termios->c_cflag & CSTOPB)
		lcr_h |= UART01x_LCRH_STP2;
	अगर (termios->c_cflag & PARENB) अणु
		lcr_h |= UART01x_LCRH_PEN;
		अगर (!(termios->c_cflag & PARODD))
			lcr_h |= UART01x_LCRH_EPS;
		अगर (termios->c_cflag & CMSPAR)
			lcr_h |= UART011_LCRH_SPS;
	पूर्ण
	अगर (uap->fअगरosize > 1)
		lcr_h |= UART01x_LCRH_FEN;

	spin_lock_irqsave(&port->lock, flags);

	/*
	 * Update the per-port समयout.
	 */
	uart_update_समयout(port, termios->c_cflag, baud);

	pl011_setup_status_masks(port, termios);

	अगर (UART_ENABLE_MS(port, termios->c_cflag))
		pl011_enable_ms(port);

	/* first, disable everything */
	old_cr = pl011_पढ़ो(uap, REG_CR);
	pl011_ग_लिखो(0, uap, REG_CR);

	अगर (termios->c_cflag & CRTSCTS) अणु
		अगर (old_cr & UART011_CR_RTS)
			old_cr |= UART011_CR_RTSEN;

		old_cr |= UART011_CR_CTSEN;
		port->status |= UPSTAT_AUTOCTS | UPSTAT_AUTORTS;
	पूर्ण अन्यथा अणु
		old_cr &= ~(UART011_CR_CTSEN | UART011_CR_RTSEN);
		port->status &= ~(UPSTAT_AUTOCTS | UPSTAT_AUTORTS);
	पूर्ण

	अगर (uap->venकरोr->oversampling) अणु
		अगर (baud > port->uartclk / 16)
			old_cr |= ST_UART011_CR_OVSFACT;
		अन्यथा
			old_cr &= ~ST_UART011_CR_OVSFACT;
	पूर्ण

	/*
	 * Workaround क्रम the ST Micro oversampling variants to
	 * increase the bitrate slightly, by lowering the भागisor,
	 * to aव्योम delayed sampling of start bit at high speeds,
	 * अन्यथा we see data corruption.
	 */
	अगर (uap->venकरोr->oversampling) अणु
		अगर ((baud >= 3000000) && (baud < 3250000) && (quot > 1))
			quot -= 1;
		अन्यथा अगर ((baud > 3250000) && (quot > 2))
			quot -= 2;
	पूर्ण
	/* Set baud rate */
	pl011_ग_लिखो(quot & 0x3f, uap, REG_FBRD);
	pl011_ग_लिखो(quot >> 6, uap, REG_IBRD);

	/*
	 * ----------v----------v----------v----------v-----
	 * NOTE: REG_LCRH_TX and REG_LCRH_RX MUST BE WRITTEN AFTER
	 * REG_FBRD & REG_IBRD.
	 * ----------^----------^----------^----------^-----
	 */
	pl011_ग_लिखो_lcr_h(uap, lcr_h);
	pl011_ग_लिखो(old_cr, uap, REG_CR);

	spin_unlock_irqrestore(&port->lock, flags);
पूर्ण

अटल व्योम
sbsa_uart_set_termios(काष्ठा uart_port *port, काष्ठा ktermios *termios,
		      काष्ठा ktermios *old)
अणु
	काष्ठा uart_amba_port *uap =
	    container_of(port, काष्ठा uart_amba_port, port);
	अचिन्हित दीर्घ flags;

	tty_termios_encode_baud_rate(termios, uap->fixed_baud, uap->fixed_baud);

	/* The SBSA UART only supports 8n1 without hardware flow control. */
	termios->c_cflag &= ~(CSIZE | CSTOPB | PARENB | PARODD);
	termios->c_cflag &= ~(CMSPAR | CRTSCTS);
	termios->c_cflag |= CS8 | CLOCAL;

	spin_lock_irqsave(&port->lock, flags);
	uart_update_समयout(port, CS8, uap->fixed_baud);
	pl011_setup_status_masks(port, termios);
	spin_unlock_irqrestore(&port->lock, flags);
पूर्ण

अटल स्थिर अक्षर *pl011_type(काष्ठा uart_port *port)
अणु
	काष्ठा uart_amba_port *uap =
	    container_of(port, काष्ठा uart_amba_port, port);
	वापस uap->port.type == PORT_AMBA ? uap->type : शून्य;
पूर्ण

/*
 * Release the memory region(s) being used by 'port'
 */
अटल व्योम pl011_release_port(काष्ठा uart_port *port)
अणु
	release_mem_region(port->mapbase, SZ_4K);
पूर्ण

/*
 * Request the memory region(s) being used by 'port'
 */
अटल पूर्णांक pl011_request_port(काष्ठा uart_port *port)
अणु
	वापस request_mem_region(port->mapbase, SZ_4K, "uart-pl011")
			!= शून्य ? 0 : -EBUSY;
पूर्ण

/*
 * Configure/स्वतःconfigure the port.
 */
अटल व्योम pl011_config_port(काष्ठा uart_port *port, पूर्णांक flags)
अणु
	अगर (flags & UART_CONFIG_TYPE) अणु
		port->type = PORT_AMBA;
		pl011_request_port(port);
	पूर्ण
पूर्ण

/*
 * verअगरy the new serial_काष्ठा (क्रम TIOCSSERIAL).
 */
अटल पूर्णांक pl011_verअगरy_port(काष्ठा uart_port *port, काष्ठा serial_काष्ठा *ser)
अणु
	पूर्णांक ret = 0;
	अगर (ser->type != PORT_UNKNOWN && ser->type != PORT_AMBA)
		ret = -EINVAL;
	अगर (ser->irq < 0 || ser->irq >= nr_irqs)
		ret = -EINVAL;
	अगर (ser->baud_base < 9600)
		ret = -EINVAL;
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा uart_ops amba_pl011_pops = अणु
	.tx_empty	= pl011_tx_empty,
	.set_mctrl	= pl011_set_mctrl,
	.get_mctrl	= pl011_get_mctrl,
	.stop_tx	= pl011_stop_tx,
	.start_tx	= pl011_start_tx,
	.stop_rx	= pl011_stop_rx,
	.enable_ms	= pl011_enable_ms,
	.अवरोध_ctl	= pl011_अवरोध_ctl,
	.startup	= pl011_startup,
	.shutकरोwn	= pl011_shutकरोwn,
	.flush_buffer	= pl011_dma_flush_buffer,
	.set_termios	= pl011_set_termios,
	.type		= pl011_type,
	.release_port	= pl011_release_port,
	.request_port	= pl011_request_port,
	.config_port	= pl011_config_port,
	.verअगरy_port	= pl011_verअगरy_port,
#अगर_घोषित CONFIG_CONSOLE_POLL
	.poll_init     = pl011_hwinit,
	.poll_get_अक्षर = pl011_get_poll_अक्षर,
	.poll_put_अक्षर = pl011_put_poll_अक्षर,
#पूर्ण_अगर
पूर्ण;

अटल व्योम sbsa_uart_set_mctrl(काष्ठा uart_port *port, अचिन्हित पूर्णांक mctrl)
अणु
पूर्ण

अटल अचिन्हित पूर्णांक sbsa_uart_get_mctrl(काष्ठा uart_port *port)
अणु
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा uart_ops sbsa_uart_pops = अणु
	.tx_empty	= pl011_tx_empty,
	.set_mctrl	= sbsa_uart_set_mctrl,
	.get_mctrl	= sbsa_uart_get_mctrl,
	.stop_tx	= pl011_stop_tx,
	.start_tx	= pl011_start_tx,
	.stop_rx	= pl011_stop_rx,
	.startup	= sbsa_uart_startup,
	.shutकरोwn	= sbsa_uart_shutकरोwn,
	.set_termios	= sbsa_uart_set_termios,
	.type		= pl011_type,
	.release_port	= pl011_release_port,
	.request_port	= pl011_request_port,
	.config_port	= pl011_config_port,
	.verअगरy_port	= pl011_verअगरy_port,
#अगर_घोषित CONFIG_CONSOLE_POLL
	.poll_init     = pl011_hwinit,
	.poll_get_अक्षर = pl011_get_poll_अक्षर,
	.poll_put_अक्षर = pl011_put_poll_अक्षर,
#पूर्ण_अगर
पूर्ण;

अटल काष्ठा uart_amba_port *amba_ports[UART_NR];

#अगर_घोषित CONFIG_SERIAL_AMBA_PL011_CONSOLE

अटल व्योम pl011_console_अक्षर_दो(काष्ठा uart_port *port, पूर्णांक ch)
अणु
	काष्ठा uart_amba_port *uap =
	    container_of(port, काष्ठा uart_amba_port, port);

	जबतक (pl011_पढ़ो(uap, REG_FR) & UART01x_FR_TXFF)
		cpu_relax();
	pl011_ग_लिखो(ch, uap, REG_DR);
पूर्ण

अटल व्योम
pl011_console_ग_लिखो(काष्ठा console *co, स्थिर अक्षर *s, अचिन्हित पूर्णांक count)
अणु
	काष्ठा uart_amba_port *uap = amba_ports[co->index];
	अचिन्हित पूर्णांक old_cr = 0, new_cr;
	अचिन्हित दीर्घ flags;
	पूर्णांक locked = 1;

	clk_enable(uap->clk);

	local_irq_save(flags);
	अगर (uap->port.sysrq)
		locked = 0;
	अन्यथा अगर (oops_in_progress)
		locked = spin_trylock(&uap->port.lock);
	अन्यथा
		spin_lock(&uap->port.lock);

	/*
	 *	First save the CR then disable the पूर्णांकerrupts
	 */
	अगर (!uap->venकरोr->always_enabled) अणु
		old_cr = pl011_पढ़ो(uap, REG_CR);
		new_cr = old_cr & ~UART011_CR_CTSEN;
		new_cr |= UART01x_CR_UARTEN | UART011_CR_TXE;
		pl011_ग_लिखो(new_cr, uap, REG_CR);
	पूर्ण

	uart_console_ग_लिखो(&uap->port, s, count, pl011_console_अक्षर_दो);

	/*
	 *	Finally, रुको क्रम transmitter to become empty and restore the
	 *	TCR. Allow feature रेजिस्टर bits to be inverted to work around
	 *	errata.
	 */
	जबतक ((pl011_पढ़ो(uap, REG_FR) ^ uap->venकरोr->inv_fr)
						& uap->venकरोr->fr_busy)
		cpu_relax();
	अगर (!uap->venकरोr->always_enabled)
		pl011_ग_लिखो(old_cr, uap, REG_CR);

	अगर (locked)
		spin_unlock(&uap->port.lock);
	local_irq_restore(flags);

	clk_disable(uap->clk);
पूर्ण

अटल व्योम pl011_console_get_options(काष्ठा uart_amba_port *uap, पूर्णांक *baud,
				      पूर्णांक *parity, पूर्णांक *bits)
अणु
	अगर (pl011_पढ़ो(uap, REG_CR) & UART01x_CR_UARTEN) अणु
		अचिन्हित पूर्णांक lcr_h, ibrd, fbrd;

		lcr_h = pl011_पढ़ो(uap, REG_LCRH_TX);

		*parity = 'n';
		अगर (lcr_h & UART01x_LCRH_PEN) अणु
			अगर (lcr_h & UART01x_LCRH_EPS)
				*parity = 'e';
			अन्यथा
				*parity = 'o';
		पूर्ण

		अगर ((lcr_h & 0x60) == UART01x_LCRH_WLEN_7)
			*bits = 7;
		अन्यथा
			*bits = 8;

		ibrd = pl011_पढ़ो(uap, REG_IBRD);
		fbrd = pl011_पढ़ो(uap, REG_FBRD);

		*baud = uap->port.uartclk * 4 / (64 * ibrd + fbrd);

		अगर (uap->venकरोr->oversampling) अणु
			अगर (pl011_पढ़ो(uap, REG_CR)
				  & ST_UART011_CR_OVSFACT)
				*baud *= 2;
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक pl011_console_setup(काष्ठा console *co, अक्षर *options)
अणु
	काष्ठा uart_amba_port *uap;
	पूर्णांक baud = 38400;
	पूर्णांक bits = 8;
	पूर्णांक parity = 'n';
	पूर्णांक flow = 'n';
	पूर्णांक ret;

	/*
	 * Check whether an invalid uart number has been specअगरied, and
	 * अगर so, search क्रम the first available port that करोes have
	 * console support.
	 */
	अगर (co->index >= UART_NR)
		co->index = 0;
	uap = amba_ports[co->index];
	अगर (!uap)
		वापस -ENODEV;

	/* Allow pins to be muxed in and configured */
	pinctrl_pm_select_शेष_state(uap->port.dev);

	ret = clk_prepare(uap->clk);
	अगर (ret)
		वापस ret;

	अगर (dev_get_platdata(uap->port.dev)) अणु
		काष्ठा amba_pl011_data *plat;

		plat = dev_get_platdata(uap->port.dev);
		अगर (plat->init)
			plat->init();
	पूर्ण

	uap->port.uartclk = clk_get_rate(uap->clk);

	अगर (uap->venकरोr->fixed_options) अणु
		baud = uap->fixed_baud;
	पूर्ण अन्यथा अणु
		अगर (options)
			uart_parse_options(options,
					   &baud, &parity, &bits, &flow);
		अन्यथा
			pl011_console_get_options(uap, &baud, &parity, &bits);
	पूर्ण

	वापस uart_set_options(&uap->port, co, baud, parity, bits, flow);
पूर्ण

/**
 *	pl011_console_match - non-standard console matching
 *	@co:	  रेजिस्टरing console
 *	@name:	  name from console command line
 *	@idx:	  index from console command line
 *	@options: ptr to option string from console command line
 *
 *	Only attempts to match console command lines of the क्रमm:
 *	    console=pl011,mmio|mmio32,<addr>[,<options>]
 *	    console=pl011,0x<addr>[,<options>]
 *	This क्रमm is used to रेजिस्टर an initial earlycon boot console and
 *	replace it with the amba_console at pl011 driver init.
 *
 *	Perक्रमms console setup क्रम a match (as required by पूर्णांकerface)
 *	If no <options> are specअगरied, then assume the h/w is alपढ़ोy setup.
 *
 *	Returns 0 अगर console matches; otherwise non-zero to use शेष matching
 */
अटल पूर्णांक pl011_console_match(काष्ठा console *co, अक्षर *name, पूर्णांक idx,
			       अक्षर *options)
अणु
	अचिन्हित अक्षर iotype;
	resource_माप_प्रकार addr;
	पूर्णांक i;

	/*
	 * Systems affected by the Qualcomm Technologies QDF2400 E44 erratum
	 * have a distinct console name, so make sure we check क्रम that.
	 * The actual implementation of the erratum occurs in the probe
	 * function.
	 */
	अगर ((म_भेद(name, "qdf2400_e44") != 0) && (म_भेद(name, "pl011") != 0))
		वापस -ENODEV;

	अगर (uart_parse_earlycon(options, &iotype, &addr, &options))
		वापस -ENODEV;

	अगर (iotype != UPIO_MEM && iotype != UPIO_MEM32)
		वापस -ENODEV;

	/* try to match the port specअगरied on the command line */
	क्रम (i = 0; i < ARRAY_SIZE(amba_ports); i++) अणु
		काष्ठा uart_port *port;

		अगर (!amba_ports[i])
			जारी;

		port = &amba_ports[i]->port;

		अगर (port->mapbase != addr)
			जारी;

		co->index = i;
		port->cons = co;
		वापस pl011_console_setup(co, options);
	पूर्ण

	वापस -ENODEV;
पूर्ण

अटल काष्ठा uart_driver amba_reg;
अटल काष्ठा console amba_console = अणु
	.name		= "ttyAMA",
	.ग_लिखो		= pl011_console_ग_लिखो,
	.device		= uart_console_device,
	.setup		= pl011_console_setup,
	.match		= pl011_console_match,
	.flags		= CON_PRINTBUFFER | CON_ANYTIME,
	.index		= -1,
	.data		= &amba_reg,
पूर्ण;

#घोषणा AMBA_CONSOLE	(&amba_console)

अटल व्योम qdf2400_e44_अ_दो(काष्ठा uart_port *port, पूर्णांक c)
अणु
	जबतक (पढ़ोl(port->membase + UART01x_FR) & UART01x_FR_TXFF)
		cpu_relax();
	ग_लिखोl(c, port->membase + UART01x_DR);
	जबतक (!(पढ़ोl(port->membase + UART01x_FR) & UART011_FR_TXFE))
		cpu_relax();
पूर्ण

अटल व्योम qdf2400_e44_early_ग_लिखो(काष्ठा console *con, स्थिर अक्षर *s, अचिन्हित n)
अणु
	काष्ठा earlycon_device *dev = con->data;

	uart_console_ग_लिखो(&dev->port, s, n, qdf2400_e44_अ_दो);
पूर्ण

अटल व्योम pl011_अ_दो(काष्ठा uart_port *port, पूर्णांक c)
अणु
	जबतक (पढ़ोl(port->membase + UART01x_FR) & UART01x_FR_TXFF)
		cpu_relax();
	अगर (port->iotype == UPIO_MEM32)
		ग_लिखोl(c, port->membase + UART01x_DR);
	अन्यथा
		ग_लिखोb(c, port->membase + UART01x_DR);
	जबतक (पढ़ोl(port->membase + UART01x_FR) & UART01x_FR_BUSY)
		cpu_relax();
पूर्ण

अटल व्योम pl011_early_ग_लिखो(काष्ठा console *con, स्थिर अक्षर *s, अचिन्हित n)
अणु
	काष्ठा earlycon_device *dev = con->data;

	uart_console_ग_लिखो(&dev->port, s, n, pl011_अ_दो);
पूर्ण

#अगर_घोषित CONFIG_CONSOLE_POLL
अटल पूर्णांक pl011_अ_लो(काष्ठा uart_port *port)
अणु
	अगर (पढ़ोl(port->membase + UART01x_FR) & UART01x_FR_RXFE)
		वापस NO_POLL_CHAR;

	अगर (port->iotype == UPIO_MEM32)
		वापस पढ़ोl(port->membase + UART01x_DR);
	अन्यथा
		वापस पढ़ोb(port->membase + UART01x_DR);
पूर्ण

अटल पूर्णांक pl011_early_पढ़ो(काष्ठा console *con, अक्षर *s, अचिन्हित पूर्णांक n)
अणु
	काष्ठा earlycon_device *dev = con->data;
	पूर्णांक ch, num_पढ़ो = 0;

	जबतक (num_पढ़ो < n) अणु
		ch = pl011_अ_लो(&dev->port);
		अगर (ch == NO_POLL_CHAR)
			अवरोध;

		s[num_पढ़ो++] = ch;
	पूर्ण

	वापस num_पढ़ो;
पूर्ण
#अन्यथा
#घोषणा pl011_early_पढ़ो शून्य
#पूर्ण_अगर

/*
 * On non-ACPI प्रणालीs, earlycon is enabled by specअगरying
 * "earlycon=pl011,<address>" on the kernel command line.
 *
 * On ACPI ARM64 प्रणालीs, an "early" console is enabled via the SPCR table,
 * by specअगरying only "earlycon" on the command line.  Because it requires
 * SPCR, the console starts after ACPI is parsed, which is later than a
 * traditional early console.
 *
 * To get the traditional early console that starts beक्रमe ACPI is parsed,
 * specअगरy the full "earlycon=pl011,<address>" option.
 */
अटल पूर्णांक __init pl011_early_console_setup(काष्ठा earlycon_device *device,
					    स्थिर अक्षर *opt)
अणु
	अगर (!device->port.membase)
		वापस -ENODEV;

	device->con->ग_लिखो = pl011_early_ग_लिखो;
	device->con->पढ़ो = pl011_early_पढ़ो;

	वापस 0;
पूर्ण
OF_EARLYCON_DECLARE(pl011, "arm,pl011", pl011_early_console_setup);
OF_EARLYCON_DECLARE(pl011, "arm,sbsa-uart", pl011_early_console_setup);

/*
 * On Qualcomm Datacenter Technologies QDF2400 SOCs affected by
 * Erratum 44, traditional earlycon can be enabled by specअगरying
 * "earlycon=qdf2400_e44,<address>".  Any options are ignored.
 *
 * Alternatively, you can just specअगरy "earlycon", and the early console
 * will be enabled with the inक्रमmation from the SPCR table.  In this
 * हाल, the SPCR code will detect the need क्रम the E44 work-around,
 * and set the console name to "qdf2400_e44".
 */
अटल पूर्णांक __init
qdf2400_e44_early_console_setup(काष्ठा earlycon_device *device,
				स्थिर अक्षर *opt)
अणु
	अगर (!device->port.membase)
		वापस -ENODEV;

	device->con->ग_लिखो = qdf2400_e44_early_ग_लिखो;
	वापस 0;
पूर्ण
EARLYCON_DECLARE(qdf2400_e44, qdf2400_e44_early_console_setup);

#अन्यथा
#घोषणा AMBA_CONSOLE	शून्य
#पूर्ण_अगर

अटल काष्ठा uart_driver amba_reg = अणु
	.owner			= THIS_MODULE,
	.driver_name		= "ttyAMA",
	.dev_name		= "ttyAMA",
	.major			= SERIAL_AMBA_MAJOR,
	.minor			= SERIAL_AMBA_MINOR,
	.nr			= UART_NR,
	.cons			= AMBA_CONSOLE,
पूर्ण;

अटल पूर्णांक pl011_probe_dt_alias(पूर्णांक index, काष्ठा device *dev)
अणु
	काष्ठा device_node *np;
	अटल bool seen_dev_with_alias = false;
	अटल bool seen_dev_without_alias = false;
	पूर्णांक ret = index;

	अगर (!IS_ENABLED(CONFIG_OF))
		वापस ret;

	np = dev->of_node;
	अगर (!np)
		वापस ret;

	ret = of_alias_get_id(np, "serial");
	अगर (ret < 0) अणु
		seen_dev_without_alias = true;
		ret = index;
	पूर्ण अन्यथा अणु
		seen_dev_with_alias = true;
		अगर (ret >= ARRAY_SIZE(amba_ports) || amba_ports[ret] != शून्य) अणु
			dev_warn(dev, "requested serial port %d  not available.\n", ret);
			ret = index;
		पूर्ण
	पूर्ण

	अगर (seen_dev_with_alias && seen_dev_without_alias)
		dev_warn(dev, "aliased and non-aliased serial devices found in device tree. Serial port enumeration may be unpredictable.\n");

	वापस ret;
पूर्ण

/* unरेजिस्टरs the driver also अगर no more ports are left */
अटल व्योम pl011_unरेजिस्टर_port(काष्ठा uart_amba_port *uap)
अणु
	पूर्णांक i;
	bool busy = false;

	क्रम (i = 0; i < ARRAY_SIZE(amba_ports); i++) अणु
		अगर (amba_ports[i] == uap)
			amba_ports[i] = शून्य;
		अन्यथा अगर (amba_ports[i])
			busy = true;
	पूर्ण
	pl011_dma_हटाओ(uap);
	अगर (!busy)
		uart_unरेजिस्टर_driver(&amba_reg);
पूर्ण

अटल पूर्णांक pl011_find_मुक्त_port(व्योम)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(amba_ports); i++)
		अगर (amba_ports[i] == शून्य)
			वापस i;

	वापस -EBUSY;
पूर्ण

अटल पूर्णांक pl011_setup_port(काष्ठा device *dev, काष्ठा uart_amba_port *uap,
			    काष्ठा resource *mmiobase, पूर्णांक index)
अणु
	व्योम __iomem *base;

	base = devm_ioremap_resource(dev, mmiobase);
	अगर (IS_ERR(base))
		वापस PTR_ERR(base);

	index = pl011_probe_dt_alias(index, dev);

	uap->old_cr = 0;
	uap->port.dev = dev;
	uap->port.mapbase = mmiobase->start;
	uap->port.membase = base;
	uap->port.fअगरosize = uap->fअगरosize;
	uap->port.has_sysrq = IS_ENABLED(CONFIG_SERIAL_AMBA_PL011_CONSOLE);
	uap->port.flags = UPF_BOOT_AUTOCONF;
	uap->port.line = index;

	amba_ports[index] = uap;

	वापस 0;
पूर्ण

अटल पूर्णांक pl011_रेजिस्टर_port(काष्ठा uart_amba_port *uap)
अणु
	पूर्णांक ret, i;

	/* Ensure पूर्णांकerrupts from this UART are masked and cleared */
	pl011_ग_लिखो(0, uap, REG_IMSC);
	pl011_ग_लिखो(0xffff, uap, REG_ICR);

	अगर (!amba_reg.state) अणु
		ret = uart_रेजिस्टर_driver(&amba_reg);
		अगर (ret < 0) अणु
			dev_err(uap->port.dev,
				"Failed to register AMBA-PL011 driver\n");
			क्रम (i = 0; i < ARRAY_SIZE(amba_ports); i++)
				अगर (amba_ports[i] == uap)
					amba_ports[i] = शून्य;
			वापस ret;
		पूर्ण
	पूर्ण

	ret = uart_add_one_port(&amba_reg, &uap->port);
	अगर (ret)
		pl011_unरेजिस्टर_port(uap);

	वापस ret;
पूर्ण

अटल पूर्णांक pl011_probe(काष्ठा amba_device *dev, स्थिर काष्ठा amba_id *id)
अणु
	काष्ठा uart_amba_port *uap;
	काष्ठा venकरोr_data *venकरोr = id->data;
	पूर्णांक portnr, ret;

	portnr = pl011_find_मुक्त_port();
	अगर (portnr < 0)
		वापस portnr;

	uap = devm_kzalloc(&dev->dev, माप(काष्ठा uart_amba_port),
			   GFP_KERNEL);
	अगर (!uap)
		वापस -ENOMEM;

	uap->clk = devm_clk_get(&dev->dev, शून्य);
	अगर (IS_ERR(uap->clk))
		वापस PTR_ERR(uap->clk);

	uap->reg_offset = venकरोr->reg_offset;
	uap->venकरोr = venकरोr;
	uap->fअगरosize = venकरोr->get_fअगरosize(dev);
	uap->port.iotype = venकरोr->access_32b ? UPIO_MEM32 : UPIO_MEM;
	uap->port.irq = dev->irq[0];
	uap->port.ops = &amba_pl011_pops;

	snम_लिखो(uap->type, माप(uap->type), "PL011 rev%u", amba_rev(dev));

	ret = pl011_setup_port(&dev->dev, uap, &dev->res, portnr);
	अगर (ret)
		वापस ret;

	amba_set_drvdata(dev, uap);

	वापस pl011_रेजिस्टर_port(uap);
पूर्ण

अटल व्योम pl011_हटाओ(काष्ठा amba_device *dev)
अणु
	काष्ठा uart_amba_port *uap = amba_get_drvdata(dev);

	uart_हटाओ_one_port(&amba_reg, &uap->port);
	pl011_unरेजिस्टर_port(uap);
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक pl011_suspend(काष्ठा device *dev)
अणु
	काष्ठा uart_amba_port *uap = dev_get_drvdata(dev);

	अगर (!uap)
		वापस -EINVAL;

	वापस uart_suspend_port(&amba_reg, &uap->port);
पूर्ण

अटल पूर्णांक pl011_resume(काष्ठा device *dev)
अणु
	काष्ठा uart_amba_port *uap = dev_get_drvdata(dev);

	अगर (!uap)
		वापस -EINVAL;

	वापस uart_resume_port(&amba_reg, &uap->port);
पूर्ण
#पूर्ण_अगर

अटल SIMPLE_DEV_PM_OPS(pl011_dev_pm_ops, pl011_suspend, pl011_resume);

अटल पूर्णांक sbsa_uart_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा uart_amba_port *uap;
	काष्ठा resource *r;
	पूर्णांक portnr, ret;
	पूर्णांक baudrate;

	/*
	 * Check the mandatory baud rate parameter in the DT node early
	 * so that we can easily निकास with the error.
	 */
	अगर (pdev->dev.of_node) अणु
		काष्ठा device_node *np = pdev->dev.of_node;

		ret = of_property_पढ़ो_u32(np, "current-speed", &baudrate);
		अगर (ret)
			वापस ret;
	पूर्ण अन्यथा अणु
		baudrate = 115200;
	पूर्ण

	portnr = pl011_find_मुक्त_port();
	अगर (portnr < 0)
		वापस portnr;

	uap = devm_kzalloc(&pdev->dev, माप(काष्ठा uart_amba_port),
			   GFP_KERNEL);
	अगर (!uap)
		वापस -ENOMEM;

	ret = platक्रमm_get_irq(pdev, 0);
	अगर (ret < 0)
		वापस ret;
	uap->port.irq	= ret;

#अगर_घोषित CONFIG_ACPI_SPCR_TABLE
	अगर (qdf2400_e44_present) अणु
		dev_info(&pdev->dev, "working around QDF2400 SoC erratum 44\n");
		uap->venकरोr = &venकरोr_qdt_qdf2400_e44;
	पूर्ण अन्यथा
#पूर्ण_अगर
		uap->venकरोr = &venकरोr_sbsa;

	uap->reg_offset	= uap->venकरोr->reg_offset;
	uap->fअगरosize	= 32;
	uap->port.iotype = uap->venकरोr->access_32b ? UPIO_MEM32 : UPIO_MEM;
	uap->port.ops	= &sbsa_uart_pops;
	uap->fixed_baud = baudrate;

	snम_लिखो(uap->type, माप(uap->type), "SBSA");

	r = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);

	ret = pl011_setup_port(&pdev->dev, uap, r, portnr);
	अगर (ret)
		वापस ret;

	platक्रमm_set_drvdata(pdev, uap);

	वापस pl011_रेजिस्टर_port(uap);
पूर्ण

अटल पूर्णांक sbsa_uart_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा uart_amba_port *uap = platक्रमm_get_drvdata(pdev);

	uart_हटाओ_one_port(&amba_reg, &uap->port);
	pl011_unरेजिस्टर_port(uap);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id sbsa_uart_of_match[] = अणु
	अणु .compatible = "arm,sbsa-uart", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, sbsa_uart_of_match);

अटल स्थिर काष्ठा acpi_device_id __maybe_unused sbsa_uart_acpi_match[] = अणु
	अणु "ARMH0011", 0 पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(acpi, sbsa_uart_acpi_match);

अटल काष्ठा platक्रमm_driver arm_sbsa_uart_platक्रमm_driver = अणु
	.probe		= sbsa_uart_probe,
	.हटाओ		= sbsa_uart_हटाओ,
	.driver	= अणु
		.name	= "sbsa-uart",
		.pm	= &pl011_dev_pm_ops,
		.of_match_table = of_match_ptr(sbsa_uart_of_match),
		.acpi_match_table = ACPI_PTR(sbsa_uart_acpi_match),
		.suppress_bind_attrs = IS_BUILTIN(CONFIG_SERIAL_AMBA_PL011),
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा amba_id pl011_ids[] = अणु
	अणु
		.id	= 0x00041011,
		.mask	= 0x000fffff,
		.data	= &venकरोr_arm,
	पूर्ण,
	अणु
		.id	= 0x00380802,
		.mask	= 0x00ffffff,
		.data	= &venकरोr_st,
	पूर्ण,
	अणु
		.id	= AMBA_LINUX_ID(0x00, 0x1, 0xffe),
		.mask	= 0x00ffffff,
		.data	= &venकरोr_zte,
	पूर्ण,
	अणु 0, 0 पूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(amba, pl011_ids);

अटल काष्ठा amba_driver pl011_driver = अणु
	.drv = अणु
		.name	= "uart-pl011",
		.pm	= &pl011_dev_pm_ops,
		.suppress_bind_attrs = IS_BUILTIN(CONFIG_SERIAL_AMBA_PL011),
	पूर्ण,
	.id_table	= pl011_ids,
	.probe		= pl011_probe,
	.हटाओ		= pl011_हटाओ,
पूर्ण;

अटल पूर्णांक __init pl011_init(व्योम)
अणु
	prपूर्णांकk(KERN_INFO "Serial: AMBA PL011 UART driver\n");

	अगर (platक्रमm_driver_रेजिस्टर(&arm_sbsa_uart_platक्रमm_driver))
		pr_warn("could not register SBSA UART platform driver\n");
	वापस amba_driver_रेजिस्टर(&pl011_driver);
पूर्ण

अटल व्योम __निकास pl011_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&arm_sbsa_uart_platक्रमm_driver);
	amba_driver_unरेजिस्टर(&pl011_driver);
पूर्ण

/*
 * While this can be a module, अगर builtin it's most likely the console
 * So let's leave module_निकास but move module_init to an earlier place
 */
arch_initcall(pl011_init);
module_निकास(pl011_निकास);

MODULE_AUTHOR("ARM Ltd/Deep Blue Solutions Ltd");
MODULE_DESCRIPTION("ARM AMBA serial port driver");
MODULE_LICENSE("GPL");
