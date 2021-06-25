<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* ePAPR hypervisor byte channel device driver
 *
 * Copyright 2009-2011 Freescale Semiconductor, Inc.
 *
 * Author: Timur Tabi <timur@मुक्तscale.com>
 *
 * This driver support three distinct पूर्णांकerfaces, all of which are related to
 * ePAPR hypervisor byte channels.
 *
 * 1) An early-console (udbg) driver.  This provides early console output
 * through a byte channel.  The byte channel handle must be specअगरied in a
 * Kconfig option.
 *
 * 2) A normal console driver.  Output is sent to the byte channel designated
 * क्रम मानक_निकास in the device tree.  The console driver is क्रम handling kernel
 * prपूर्णांकk calls.
 *
 * 3) A tty driver, which is used to handle user-space input and output.  The
 * byte channel used क्रम the console is designated as the शेष tty.
 */

#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/err.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/fs.h>
#समावेश <linux/poll.h>
#समावेश <यंत्र/epapr_hcalls.h>
#समावेश <linux/of.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/cdev.h>
#समावेश <linux/console.h>
#समावेश <linux/tty.h>
#समावेश <linux/tty_flip.h>
#समावेश <linux/circ_buf.h>
#समावेश <यंत्र/udbg.h>

/* The size of the transmit circular buffer.  This must be a घातer of two. */
#घोषणा BUF_SIZE	2048

/* Per-byte channel निजी data */
काष्ठा ehv_bc_data अणु
	काष्ठा device *dev;
	काष्ठा tty_port port;
	uपूर्णांक32_t handle;
	अचिन्हित पूर्णांक rx_irq;
	अचिन्हित पूर्णांक tx_irq;

	spinlock_t lock;	/* lock क्रम transmit buffer */
	अचिन्हित अक्षर buf[BUF_SIZE];	/* transmit circular buffer */
	अचिन्हित पूर्णांक head;	/* circular buffer head */
	अचिन्हित पूर्णांक tail;	/* circular buffer tail */

	पूर्णांक tx_irq_enabled;	/* true == TX पूर्णांकerrupt is enabled */
पूर्ण;

/* Array of byte channel objects */
अटल काष्ठा ehv_bc_data *bcs;

/* Byte channel handle क्रम मानक_निकास (and मानक_निवेश), taken from device tree */
अटल अचिन्हित पूर्णांक मानक_निकास_bc;

/* Virtual IRQ क्रम the byte channel handle क्रम मानक_निवेश, taken from device tree */
अटल अचिन्हित पूर्णांक मानक_निकास_irq;

/**************************** SUPPORT FUNCTIONS ****************************/

/*
 * Enable the transmit पूर्णांकerrupt
 *
 * Unlike a serial device, byte channels have no mechanism क्रम disabling their
 * own receive or transmit पूर्णांकerrupts.  To emulate that feature, we toggle
 * the IRQ in the kernel.
 *
 * We cannot just blindly call enable_irq() or disable_irq(), because these
 * calls are reference counted.  This means that we cannot call enable_irq()
 * अगर पूर्णांकerrupts are alपढ़ोy enabled.  This can happen in two situations:
 *
 * 1. The tty layer makes two back-to-back calls to ehv_bc_tty_ग_लिखो()
 * 2. A transmit पूर्णांकerrupt occurs जबतक executing ehv_bc_tx_dequeue()
 *
 * To work around this, we keep a flag to tell us अगर the IRQ is enabled or not.
 */
अटल व्योम enable_tx_पूर्णांकerrupt(काष्ठा ehv_bc_data *bc)
अणु
	अगर (!bc->tx_irq_enabled) अणु
		enable_irq(bc->tx_irq);
		bc->tx_irq_enabled = 1;
	पूर्ण
पूर्ण

अटल व्योम disable_tx_पूर्णांकerrupt(काष्ठा ehv_bc_data *bc)
अणु
	अगर (bc->tx_irq_enabled) अणु
		disable_irq_nosync(bc->tx_irq);
		bc->tx_irq_enabled = 0;
	पूर्ण
पूर्ण

/*
 * find the byte channel handle to use क्रम the console
 *
 * The byte channel to be used क्रम the console is specअगरied via a "stdout"
 * property in the /chosen node.
 */
अटल पूर्णांक find_console_handle(व्योम)
अणु
	काष्ठा device_node *np = of_मानक_निकास;
	स्थिर uपूर्णांक32_t *iprop;

	/* We करोn't care what the aliased node is actually called.  We only
	 * care अगर it's compatible with "epapr,hv-byte-channel", because that
	 * indicates that it's a byte channel node.
	 */
	अगर (!np || !of_device_is_compatible(np, "epapr,hv-byte-channel"))
		वापस 0;

	मानक_निकास_irq = irq_of_parse_and_map(np, 0);
	अगर (मानक_निकास_irq == NO_IRQ) अणु
		pr_err("ehv-bc: no 'interrupts' property in %pOF node\n", np);
		वापस 0;
	पूर्ण

	/*
	 * The 'hv-handle' property contains the handle क्रम this byte channel.
	 */
	iprop = of_get_property(np, "hv-handle", शून्य);
	अगर (!iprop) अणु
		pr_err("ehv-bc: no 'hv-handle' property in %pOFn node\n",
		       np);
		वापस 0;
	पूर्ण
	मानक_निकास_bc = be32_to_cpu(*iprop);
	वापस 1;
पूर्ण

अटल अचिन्हित पूर्णांक local_ev_byte_channel_send(अचिन्हित पूर्णांक handle,
					       अचिन्हित पूर्णांक *count,
					       स्थिर अक्षर *p)
अणु
	अक्षर buffer[EV_BYTE_CHANNEL_MAX_BYTES];
	अचिन्हित पूर्णांक c = *count;

	अगर (c < माप(buffer)) अणु
		स_नकल(buffer, p, c);
		स_रखो(&buffer[c], 0, माप(buffer) - c);
		p = buffer;
	पूर्ण
	वापस ev_byte_channel_send(handle, count, p);
पूर्ण

/*************************** EARLY CONSOLE DRIVER ***************************/

#अगर_घोषित CONFIG_PPC_EARLY_DEBUG_EHV_BC

/*
 * send a byte to a byte channel, रुको अगर necessary
 *
 * This function sends a byte to a byte channel, and it रुकोs and
 * retries अगर the byte channel is full.  It वापसs अगर the अक्षरacter
 * has been sent, or अगर some error has occurred.
 *
 */
अटल व्योम byte_channel_spin_send(स्थिर अक्षर data)
अणु
	पूर्णांक ret, count;

	करो अणु
		count = 1;
		ret = local_ev_byte_channel_send(CONFIG_PPC_EARLY_DEBUG_EHV_BC_HANDLE,
					   &count, &data);
	पूर्ण जबतक (ret == EV_EAGAIN);
पूर्ण

/*
 * The udbg subप्रणाली calls this function to display a single अक्षरacter.
 * We convert CR to a CR/LF.
 */
अटल व्योम ehv_bc_udbg_अ_दो(अक्षर c)
अणु
	अगर (c == '\n')
		byte_channel_spin_send('\r');

	byte_channel_spin_send(c);
पूर्ण

/*
 * early console initialization
 *
 * PowerPC kernels support an early prपूर्णांकk console, also known as udbg.
 * This function must be called via the ppc_md.init_early function poपूर्णांकer.
 * At this poपूर्णांक, the device tree has been unflattened, so we can obtain the
 * byte channel handle क्रम मानक_निकास.
 *
 * We only support displaying of अक्षरacters (अ_दो).  We करो not support
 * keyboard input.
 */
व्योम __init udbg_init_ehv_bc(व्योम)
अणु
	अचिन्हित पूर्णांक rx_count, tx_count;
	अचिन्हित पूर्णांक ret;

	/* Verअगरy the byte channel handle */
	ret = ev_byte_channel_poll(CONFIG_PPC_EARLY_DEBUG_EHV_BC_HANDLE,
				   &rx_count, &tx_count);
	अगर (ret)
		वापस;

	udbg_अ_दो = ehv_bc_udbg_अ_दो;
	रेजिस्टर_early_udbg_console();

	udbg_म_लिखो("ehv-bc: early console using byte channel handle %u\n",
		    CONFIG_PPC_EARLY_DEBUG_EHV_BC_HANDLE);
पूर्ण

#पूर्ण_अगर

/****************************** CONSOLE DRIVER ******************************/

अटल काष्ठा tty_driver *ehv_bc_driver;

/*
 * Byte channel console sending worker function.
 *
 * For consoles, अगर the output buffer is full, we should just spin until it
 * clears.
 */
अटल पूर्णांक ehv_bc_console_byte_channel_send(अचिन्हित पूर्णांक handle, स्थिर अक्षर *s,
			     अचिन्हित पूर्णांक count)
अणु
	अचिन्हित पूर्णांक len;
	पूर्णांक ret = 0;

	जबतक (count) अणु
		len = min_t(अचिन्हित पूर्णांक, count, EV_BYTE_CHANNEL_MAX_BYTES);
		करो अणु
			ret = local_ev_byte_channel_send(handle, &len, s);
		पूर्ण जबतक (ret == EV_EAGAIN);
		count -= len;
		s += len;
	पूर्ण

	वापस ret;
पूर्ण

/*
 * ग_लिखो a string to the console
 *
 * This function माला_लो called to ग_लिखो a string from the kernel, typically from
 * a prपूर्णांकk().  This function spins until all data is written.
 *
 * We copy the data to a temporary buffer because we need to insert a \ल in
 * front of every \न.  It's more efficient to copy the data to the buffer than
 * it is to make multiple hcalls क्रम each अक्षरacter or each newline.
 */
अटल व्योम ehv_bc_console_ग_लिखो(काष्ठा console *co, स्थिर अक्षर *s,
				 अचिन्हित पूर्णांक count)
अणु
	अक्षर s2[EV_BYTE_CHANNEL_MAX_BYTES];
	अचिन्हित पूर्णांक i, j = 0;
	अक्षर c;

	क्रम (i = 0; i < count; i++) अणु
		c = *s++;

		अगर (c == '\n')
			s2[j++] = '\r';

		s2[j++] = c;
		अगर (j >= (EV_BYTE_CHANNEL_MAX_BYTES - 1)) अणु
			अगर (ehv_bc_console_byte_channel_send(मानक_निकास_bc, s2, j))
				वापस;
			j = 0;
		पूर्ण
	पूर्ण

	अगर (j)
		ehv_bc_console_byte_channel_send(मानक_निकास_bc, s2, j);
पूर्ण

/*
 * When /dev/console is खोलोed, the kernel iterates the console list looking
 * क्रम one with ->device and then calls that method. On success, it expects
 * the passed-in पूर्णांक* to contain the minor number to use.
 */
अटल काष्ठा tty_driver *ehv_bc_console_device(काष्ठा console *co, पूर्णांक *index)
अणु
	*index = co->index;

	वापस ehv_bc_driver;
पूर्ण

अटल काष्ठा console ehv_bc_console = अणु
	.name		= "ttyEHV",
	.ग_लिखो		= ehv_bc_console_ग_लिखो,
	.device		= ehv_bc_console_device,
	.flags		= CON_PRINTBUFFER | CON_ENABLED,
पूर्ण;

/*
 * Console initialization
 *
 * This is the first function that is called after the device tree is
 * available, so here is where we determine the byte channel handle and IRQ क्रम
 * मानक_निकास/मानक_निवेश, even though that inक्रमmation is used by the tty and अक्षरacter
 * drivers.
 */
अटल पूर्णांक __init ehv_bc_console_init(व्योम)
अणु
	अगर (!find_console_handle()) अणु
		pr_debug("ehv-bc: stdout is not a byte channel\n");
		वापस -ENODEV;
	पूर्ण

#अगर_घोषित CONFIG_PPC_EARLY_DEBUG_EHV_BC
	/* Prपूर्णांक a मित्रly warning अगर the user chose the wrong byte channel
	 * handle क्रम udbg.
	 */
	अगर (मानक_निकास_bc != CONFIG_PPC_EARLY_DEBUG_EHV_BC_HANDLE)
		pr_warn("ehv-bc: udbg handle %u is not the stdout handle\n",
			CONFIG_PPC_EARLY_DEBUG_EHV_BC_HANDLE);
#पूर्ण_अगर

	/* add_preferred_console() must be called beक्रमe रेजिस्टर_console(),
	   otherwise it won't work.  However, we don't want to क्रमागतerate all the
	   byte channels here, either, since we only care about one. */

	add_preferred_console(ehv_bc_console.name, ehv_bc_console.index, शून्य);
	रेजिस्टर_console(&ehv_bc_console);

	pr_info("ehv-bc: registered console driver for byte channel %u\n",
		मानक_निकास_bc);

	वापस 0;
पूर्ण
console_initcall(ehv_bc_console_init);

/******************************** TTY DRIVER ********************************/

/*
 * byte channel receive पूर्णांकerrupt handler
 *
 * This ISR is called whenever data is available on a byte channel.
 */
अटल irqवापस_t ehv_bc_tty_rx_isr(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा ehv_bc_data *bc = data;
	अचिन्हित पूर्णांक rx_count, tx_count, len;
	पूर्णांक count;
	अक्षर buffer[EV_BYTE_CHANNEL_MAX_BYTES];
	पूर्णांक ret;

	/* Find out how much data needs to be पढ़ो, and then ask the TTY layer
	 * अगर it can handle that much.  We want to ensure that every byte we
	 * पढ़ो from the byte channel will be accepted by the TTY layer.
	 */
	ev_byte_channel_poll(bc->handle, &rx_count, &tx_count);
	count = tty_buffer_request_room(&bc->port, rx_count);

	/* 'count' is the maximum amount of data the TTY layer can accept at
	 * this समय.  However, during testing, I was never able to get 'count'
	 * to be less than 'rx_count'.  I'm not sure whether I'm calling it
	 * correctly.
	 */

	जबतक (count > 0) अणु
		len = min_t(अचिन्हित पूर्णांक, count, माप(buffer));

		/* Read some data from the byte channel.  This function will
		 * never वापस more than EV_BYTE_CHANNEL_MAX_BYTES bytes.
		 */
		ev_byte_channel_receive(bc->handle, &len, buffer);

		/* 'len' is now the amount of data that's been received. 'len'
		 * can't be zero, and most likely it's equal to one.
		 */

		/* Pass the received data to the tty layer. */
		ret = tty_insert_flip_string(&bc->port, buffer, len);

		/* 'ret' is the number of bytes that the TTY layer accepted.
		 * If it's not equal to 'len', then it means the buffer is
		 * full, which should never happen.  If it करोes happen, we can
		 * निकास gracefully, but we drop the last 'len - ret' अक्षरacters
		 * that we पढ़ो from the byte channel.
		 */
		अगर (ret != len)
			अवरोध;

		count -= len;
	पूर्ण

	/* Tell the tty layer that we're करोne. */
	tty_flip_buffer_push(&bc->port);

	वापस IRQ_HANDLED;
पूर्ण

/*
 * dequeue the transmit buffer to the hypervisor
 *
 * This function, which can be called in पूर्णांकerrupt context, dequeues as much
 * data as possible from the transmit buffer to the byte channel.
 */
अटल व्योम ehv_bc_tx_dequeue(काष्ठा ehv_bc_data *bc)
अणु
	अचिन्हित पूर्णांक count;
	अचिन्हित पूर्णांक len, ret;
	अचिन्हित दीर्घ flags;

	करो अणु
		spin_lock_irqsave(&bc->lock, flags);
		len = min_t(अचिन्हित पूर्णांक,
			    CIRC_CNT_TO_END(bc->head, bc->tail, BUF_SIZE),
			    EV_BYTE_CHANNEL_MAX_BYTES);

		ret = local_ev_byte_channel_send(bc->handle, &len, bc->buf + bc->tail);

		/* 'len' is valid only अगर the वापस code is 0 or EV_EAGAIN */
		अगर (!ret || (ret == EV_EAGAIN))
			bc->tail = (bc->tail + len) & (BUF_SIZE - 1);

		count = CIRC_CNT(bc->head, bc->tail, BUF_SIZE);
		spin_unlock_irqrestore(&bc->lock, flags);
	पूर्ण जबतक (count && !ret);

	spin_lock_irqsave(&bc->lock, flags);
	अगर (CIRC_CNT(bc->head, bc->tail, BUF_SIZE))
		/*
		 * If we haven't emptied the buffer, then enable the TX IRQ.
		 * We'll get an interrupt when there's more room in the
		 * hypervisor's output buffer.
		 */
		enable_tx_पूर्णांकerrupt(bc);
	अन्यथा
		disable_tx_पूर्णांकerrupt(bc);
	spin_unlock_irqrestore(&bc->lock, flags);
पूर्ण

/*
 * byte channel transmit पूर्णांकerrupt handler
 *
 * This ISR is called whenever space becomes available क्रम transmitting
 * अक्षरacters on a byte channel.
 */
अटल irqवापस_t ehv_bc_tty_tx_isr(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा ehv_bc_data *bc = data;

	ehv_bc_tx_dequeue(bc);
	tty_port_tty_wakeup(&bc->port);

	वापस IRQ_HANDLED;
पूर्ण

/*
 * This function is called when the tty layer has data क्रम us send.  We store
 * the data first in a circular buffer, and then dequeue as much of that data
 * as possible.
 *
 * We करोn't need to worry about whether there is enough room in the buffer क्रम
 * all the data.  The purpose of ehv_bc_tty_ग_लिखो_room() is to tell the tty
 * layer how much data it can safely send to us.  We guarantee that
 * ehv_bc_tty_ग_लिखो_room() will never lie, so the tty layer will never send us
 * too much data.
 */
अटल पूर्णांक ehv_bc_tty_ग_लिखो(काष्ठा tty_काष्ठा *ttys, स्थिर अचिन्हित अक्षर *s,
			    पूर्णांक count)
अणु
	काष्ठा ehv_bc_data *bc = ttys->driver_data;
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक len;
	अचिन्हित पूर्णांक written = 0;

	जबतक (1) अणु
		spin_lock_irqsave(&bc->lock, flags);
		len = CIRC_SPACE_TO_END(bc->head, bc->tail, BUF_SIZE);
		अगर (count < len)
			len = count;
		अगर (len) अणु
			स_नकल(bc->buf + bc->head, s, len);
			bc->head = (bc->head + len) & (BUF_SIZE - 1);
		पूर्ण
		spin_unlock_irqrestore(&bc->lock, flags);
		अगर (!len)
			अवरोध;

		s += len;
		count -= len;
		written += len;
	पूर्ण

	ehv_bc_tx_dequeue(bc);

	वापस written;
पूर्ण

/*
 * This function can be called multiple बार क्रम a given tty_काष्ठा, which is
 * why we initialize bc->ttys in ehv_bc_tty_port_activate() instead.
 *
 * The tty layer will still call this function even अगर the device was not
 * रेजिस्टरed (i.e. tty_रेजिस्टर_device() was not called).  This happens
 * because tty_रेजिस्टर_device() is optional and some legacy drivers करोn't
 * use it.  So we need to check क्रम that.
 */
अटल पूर्णांक ehv_bc_tty_खोलो(काष्ठा tty_काष्ठा *ttys, काष्ठा file *filp)
अणु
	काष्ठा ehv_bc_data *bc = &bcs[ttys->index];

	अगर (!bc->dev)
		वापस -ENODEV;

	वापस tty_port_खोलो(&bc->port, ttys, filp);
पूर्ण

/*
 * Amazingly, अगर ehv_bc_tty_खोलो() वापसs an error code, the tty layer will
 * still call this function to बंद the tty device.  So we can't assume that
 * the tty port has been initialized.
 */
अटल व्योम ehv_bc_tty_बंद(काष्ठा tty_काष्ठा *ttys, काष्ठा file *filp)
अणु
	काष्ठा ehv_bc_data *bc = &bcs[ttys->index];

	अगर (bc->dev)
		tty_port_बंद(&bc->port, ttys, filp);
पूर्ण

/*
 * Return the amount of space in the output buffer
 *
 * This is actually a contract between the driver and the tty layer outlining
 * how much ग_लिखो room the driver can guarantee will be sent OR BUFFERED.  This
 * driver MUST honor the वापस value.
 */
अटल पूर्णांक ehv_bc_tty_ग_लिखो_room(काष्ठा tty_काष्ठा *ttys)
अणु
	काष्ठा ehv_bc_data *bc = ttys->driver_data;
	अचिन्हित दीर्घ flags;
	पूर्णांक count;

	spin_lock_irqsave(&bc->lock, flags);
	count = CIRC_SPACE(bc->head, bc->tail, BUF_SIZE);
	spin_unlock_irqrestore(&bc->lock, flags);

	वापस count;
पूर्ण

/*
 * Stop sending data to the tty layer
 *
 * This function is called when the tty layer's input buffers are getting full,
 * so the driver should stop sending it data.  The easiest way to करो this is to
 * disable the RX IRQ, which will prevent ehv_bc_tty_rx_isr() from being
 * called.
 *
 * The hypervisor will जारी to queue up any incoming data.  If there is any
 * data in the queue when the RX पूर्णांकerrupt is enabled, we'll immediately get an
 * RX पूर्णांकerrupt.
 */
अटल व्योम ehv_bc_tty_throttle(काष्ठा tty_काष्ठा *ttys)
अणु
	काष्ठा ehv_bc_data *bc = ttys->driver_data;

	disable_irq(bc->rx_irq);
पूर्ण

/*
 * Resume sending data to the tty layer
 *
 * This function is called after previously calling ehv_bc_tty_throttle().  The
 * tty layer's input buffers now have more room, so the driver can resume
 * sending it data.
 */
अटल व्योम ehv_bc_tty_unthrottle(काष्ठा tty_काष्ठा *ttys)
अणु
	काष्ठा ehv_bc_data *bc = ttys->driver_data;

	/* If there is any data in the queue when the RX पूर्णांकerrupt is enabled,
	 * we'll immediately get an RX पूर्णांकerrupt.
	 */
	enable_irq(bc->rx_irq);
पूर्ण

अटल व्योम ehv_bc_tty_hangup(काष्ठा tty_काष्ठा *ttys)
अणु
	काष्ठा ehv_bc_data *bc = ttys->driver_data;

	ehv_bc_tx_dequeue(bc);
	tty_port_hangup(&bc->port);
पूर्ण

/*
 * TTY driver operations
 *
 * If we could ask the hypervisor how much data is still in the TX buffer, or
 * at least how big the TX buffers are, then we could implement the
 * .रुको_until_sent and .अक्षरs_in_buffer functions.
 */
अटल स्थिर काष्ठा tty_operations ehv_bc_ops = अणु
	.खोलो		= ehv_bc_tty_खोलो,
	.बंद		= ehv_bc_tty_बंद,
	.ग_लिखो		= ehv_bc_tty_ग_लिखो,
	.ग_लिखो_room	= ehv_bc_tty_ग_लिखो_room,
	.throttle	= ehv_bc_tty_throttle,
	.unthrottle	= ehv_bc_tty_unthrottle,
	.hangup		= ehv_bc_tty_hangup,
पूर्ण;

/*
 * initialize the TTY port
 *
 * This function will only be called once, no matter how many बार
 * ehv_bc_tty_खोलो() is called.  That's why we रेजिस्टर the ISR here, and also
 * why we initialize tty_काष्ठा-related variables here.
 */
अटल पूर्णांक ehv_bc_tty_port_activate(काष्ठा tty_port *port,
				    काष्ठा tty_काष्ठा *ttys)
अणु
	काष्ठा ehv_bc_data *bc = container_of(port, काष्ठा ehv_bc_data, port);
	पूर्णांक ret;

	ttys->driver_data = bc;

	ret = request_irq(bc->rx_irq, ehv_bc_tty_rx_isr, 0, "ehv-bc", bc);
	अगर (ret < 0) अणु
		dev_err(bc->dev, "could not request rx irq %u (ret=%i)\n",
		       bc->rx_irq, ret);
		वापस ret;
	पूर्ण

	/* request_irq also enables the IRQ */
	bc->tx_irq_enabled = 1;

	ret = request_irq(bc->tx_irq, ehv_bc_tty_tx_isr, 0, "ehv-bc", bc);
	अगर (ret < 0) अणु
		dev_err(bc->dev, "could not request tx irq %u (ret=%i)\n",
		       bc->tx_irq, ret);
		मुक्त_irq(bc->rx_irq, bc);
		वापस ret;
	पूर्ण

	/* The TX IRQ is enabled only when we can't ग_लिखो all the data to the
	 * byte channel at once, so by शेष it's disabled.
	 */
	disable_tx_पूर्णांकerrupt(bc);

	वापस 0;
पूर्ण

अटल व्योम ehv_bc_tty_port_shutकरोwn(काष्ठा tty_port *port)
अणु
	काष्ठा ehv_bc_data *bc = container_of(port, काष्ठा ehv_bc_data, port);

	मुक्त_irq(bc->tx_irq, bc);
	मुक्त_irq(bc->rx_irq, bc);
पूर्ण

अटल स्थिर काष्ठा tty_port_operations ehv_bc_tty_port_ops = अणु
	.activate = ehv_bc_tty_port_activate,
	.shutकरोwn = ehv_bc_tty_port_shutकरोwn,
पूर्ण;

अटल पूर्णांक ehv_bc_tty_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *np = pdev->dev.of_node;
	काष्ठा ehv_bc_data *bc;
	स्थिर uपूर्णांक32_t *iprop;
	अचिन्हित पूर्णांक handle;
	पूर्णांक ret;
	अटल अचिन्हित पूर्णांक index = 1;
	अचिन्हित पूर्णांक i;

	iprop = of_get_property(np, "hv-handle", शून्य);
	अगर (!iprop) अणु
		dev_err(&pdev->dev, "no 'hv-handle' property in %pOFn node\n",
			np);
		वापस -ENODEV;
	पूर्ण

	/* We alपढ़ोy told the console layer that the index क्रम the console
	 * device is zero, so we need to make sure that we use that index when
	 * we probe the console byte channel node.
	 */
	handle = be32_to_cpu(*iprop);
	i = (handle == मानक_निकास_bc) ? 0 : index++;
	bc = &bcs[i];

	bc->handle = handle;
	bc->head = 0;
	bc->tail = 0;
	spin_lock_init(&bc->lock);

	bc->rx_irq = irq_of_parse_and_map(np, 0);
	bc->tx_irq = irq_of_parse_and_map(np, 1);
	अगर ((bc->rx_irq == NO_IRQ) || (bc->tx_irq == NO_IRQ)) अणु
		dev_err(&pdev->dev, "no 'interrupts' property in %pOFn node\n",
			np);
		ret = -ENODEV;
		जाओ error;
	पूर्ण

	tty_port_init(&bc->port);
	bc->port.ops = &ehv_bc_tty_port_ops;

	bc->dev = tty_port_रेजिस्टर_device(&bc->port, ehv_bc_driver, i,
			&pdev->dev);
	अगर (IS_ERR(bc->dev)) अणु
		ret = PTR_ERR(bc->dev);
		dev_err(&pdev->dev, "could not register tty (ret=%i)\n", ret);
		जाओ error;
	पूर्ण

	dev_set_drvdata(&pdev->dev, bc);

	dev_info(&pdev->dev, "registered /dev/%s%u for byte channel %u\n",
		ehv_bc_driver->name, i, bc->handle);

	वापस 0;

error:
	tty_port_destroy(&bc->port);
	irq_dispose_mapping(bc->tx_irq);
	irq_dispose_mapping(bc->rx_irq);

	स_रखो(bc, 0, माप(काष्ठा ehv_bc_data));
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा of_device_id ehv_bc_tty_of_ids[] = अणु
	अणु .compatible = "epapr,hv-byte-channel" पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल काष्ठा platक्रमm_driver ehv_bc_tty_driver = अणु
	.driver = अणु
		.name = "ehv-bc",
		.of_match_table = ehv_bc_tty_of_ids,
		.suppress_bind_attrs = true,
	पूर्ण,
	.probe		= ehv_bc_tty_probe,
पूर्ण;

/**
 * ehv_bc_init - ePAPR hypervisor byte channel driver initialization
 *
 * This function is called when this driver is loaded.
 */
अटल पूर्णांक __init ehv_bc_init(व्योम)
अणु
	काष्ठा device_node *np;
	अचिन्हित पूर्णांक count = 0; /* Number of elements in bcs[] */
	पूर्णांक ret;

	pr_info("ePAPR hypervisor byte channel driver\n");

	/* Count the number of byte channels */
	क्रम_each_compatible_node(np, शून्य, "epapr,hv-byte-channel")
		count++;

	अगर (!count)
		वापस -ENODEV;

	/* The array index of an element in bcs[] is the same as the tty index
	 * क्रम that element.  If you know the address of an element in the
	 * array, then you can use poपूर्णांकer math (e.g. "bc - bcs") to get its
	 * tty index.
	 */
	bcs = kसुस्मृति(count, माप(काष्ठा ehv_bc_data), GFP_KERNEL);
	अगर (!bcs)
		वापस -ENOMEM;

	ehv_bc_driver = alloc_tty_driver(count);
	अगर (!ehv_bc_driver) अणु
		ret = -ENOMEM;
		जाओ err_मुक्त_bcs;
	पूर्ण

	ehv_bc_driver->driver_name = "ehv-bc";
	ehv_bc_driver->name = ehv_bc_console.name;
	ehv_bc_driver->type = TTY_DRIVER_TYPE_CONSOLE;
	ehv_bc_driver->subtype = SYSTEM_TYPE_CONSOLE;
	ehv_bc_driver->init_termios = tty_std_termios;
	ehv_bc_driver->flags = TTY_DRIVER_REAL_RAW | TTY_DRIVER_DYNAMIC_DEV;
	tty_set_operations(ehv_bc_driver, &ehv_bc_ops);

	ret = tty_रेजिस्टर_driver(ehv_bc_driver);
	अगर (ret) अणु
		pr_err("ehv-bc: could not register tty driver (ret=%i)\n", ret);
		जाओ err_put_tty_driver;
	पूर्ण

	ret = platक्रमm_driver_रेजिस्टर(&ehv_bc_tty_driver);
	अगर (ret) अणु
		pr_err("ehv-bc: could not register platform driver (ret=%i)\n",
		       ret);
		जाओ err_deरेजिस्टर_tty_driver;
	पूर्ण

	वापस 0;

err_deरेजिस्टर_tty_driver:
	tty_unरेजिस्टर_driver(ehv_bc_driver);
err_put_tty_driver:
	put_tty_driver(ehv_bc_driver);
err_मुक्त_bcs:
	kमुक्त(bcs);

	वापस ret;
पूर्ण
device_initcall(ehv_bc_init);
