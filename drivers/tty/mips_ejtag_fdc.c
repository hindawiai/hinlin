<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * TTY driver क्रम MIPS EJTAG Fast Debug Channels.
 *
 * Copyright (C) 2007-2015 Imagination Technologies Ltd
 */

#समावेश <linux/atomic.h>
#समावेश <linux/bitops.h>
#समावेश <linux/completion.h>
#समावेश <linux/console.h>
#समावेश <linux/delay.h>
#समावेश <linux/export.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kernel.h>
#समावेश <linux/kgdb.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/sched.h>
#समावेश <linux/serial.h>
#समावेश <linux/serial_core.h>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/माला.स>
#समावेश <linux/समयr.h>
#समावेश <linux/tty.h>
#समावेश <linux/tty_driver.h>
#समावेश <linux/tty_flip.h>
#समावेश <linux/uaccess.h>

#समावेश <यंत्र/cdmm.h>
#समावेश <यंत्र/irq.h>

/* Register offsets */
#घोषणा REG_FDACSR	0x00	/* FDC Access Control and Status Register */
#घोषणा REG_FDCFG	0x08	/* FDC Configuration Register */
#घोषणा REG_FDSTAT	0x10	/* FDC Status Register */
#घोषणा REG_FDRX	0x18	/* FDC Receive Register */
#घोषणा REG_FDTX(N)	(0x20+0x8*(N))	/* FDC Transmit Register n (0..15) */

/* Register fields */

#घोषणा REG_FDCFG_TXINTTHRES_SHIFT	18
#घोषणा REG_FDCFG_TXINTTHRES		(0x3 << REG_FDCFG_TXINTTHRES_SHIFT)
#घोषणा REG_FDCFG_TXINTTHRES_DISABLED	(0x0 << REG_FDCFG_TXINTTHRES_SHIFT)
#घोषणा REG_FDCFG_TXINTTHRES_EMPTY	(0x1 << REG_FDCFG_TXINTTHRES_SHIFT)
#घोषणा REG_FDCFG_TXINTTHRES_NOTFULL	(0x2 << REG_FDCFG_TXINTTHRES_SHIFT)
#घोषणा REG_FDCFG_TXINTTHRES_NEAREMPTY	(0x3 << REG_FDCFG_TXINTTHRES_SHIFT)
#घोषणा REG_FDCFG_RXINTTHRES_SHIFT	16
#घोषणा REG_FDCFG_RXINTTHRES		(0x3 << REG_FDCFG_RXINTTHRES_SHIFT)
#घोषणा REG_FDCFG_RXINTTHRES_DISABLED	(0x0 << REG_FDCFG_RXINTTHRES_SHIFT)
#घोषणा REG_FDCFG_RXINTTHRES_FULL	(0x1 << REG_FDCFG_RXINTTHRES_SHIFT)
#घोषणा REG_FDCFG_RXINTTHRES_NOTEMPTY	(0x2 << REG_FDCFG_RXINTTHRES_SHIFT)
#घोषणा REG_FDCFG_RXINTTHRES_NEARFULL	(0x3 << REG_FDCFG_RXINTTHRES_SHIFT)
#घोषणा REG_FDCFG_TXFIFOSIZE_SHIFT	8
#घोषणा REG_FDCFG_TXFIFOSIZE		(0xff << REG_FDCFG_TXFIFOSIZE_SHIFT)
#घोषणा REG_FDCFG_RXFIFOSIZE_SHIFT	0
#घोषणा REG_FDCFG_RXFIFOSIZE		(0xff << REG_FDCFG_RXFIFOSIZE_SHIFT)

#घोषणा REG_FDSTAT_TXCOUNT_SHIFT	24
#घोषणा REG_FDSTAT_TXCOUNT		(0xff << REG_FDSTAT_TXCOUNT_SHIFT)
#घोषणा REG_FDSTAT_RXCOUNT_SHIFT	16
#घोषणा REG_FDSTAT_RXCOUNT		(0xff << REG_FDSTAT_RXCOUNT_SHIFT)
#घोषणा REG_FDSTAT_RXCHAN_SHIFT		4
#घोषणा REG_FDSTAT_RXCHAN		(0xf << REG_FDSTAT_RXCHAN_SHIFT)
#घोषणा REG_FDSTAT_RXE			BIT(3)	/* Rx Empty */
#घोषणा REG_FDSTAT_RXF			BIT(2)	/* Rx Full */
#घोषणा REG_FDSTAT_TXE			BIT(1)	/* Tx Empty */
#घोषणा REG_FDSTAT_TXF			BIT(0)	/* Tx Full */

/* Default channel क्रम the early console */
#घोषणा CONSOLE_CHANNEL      1

#घोषणा NUM_TTY_CHANNELS     16

#घोषणा RX_BUF_SIZE 1024

/*
 * When the IRQ is unavailable, the FDC state must be polled क्रम incoming data
 * and space becoming available in TX FIFO.
 */
#घोषणा FDC_TTY_POLL (HZ / 50)

काष्ठा mips_ejtag_fdc_tty;

/**
 * काष्ठा mips_ejtag_fdc_tty_port - Wrapper काष्ठा क्रम FDC tty_port.
 * @port:		TTY port data
 * @driver:		TTY driver.
 * @rx_lock:		Lock क्रम rx_buf.
 *			This protects between the hard पूर्णांकerrupt and user
 *			context. It's also held during पढ़ो SWITCH operations.
 * @rx_buf:		Read buffer.
 * @xmit_lock:		Lock क्रम xmit_*, and port.xmit_buf.
 *			This protects between user context and kernel thपढ़ो.
 *			It is used from अक्षरs_in_buffer()/ग_लिखो_room() TTY
 *			callbacks which are used during रुको operations, so a
 *			mutex is unsuitable.
 * @xmit_cnt:		Size of xmit buffer contents.
 * @xmit_head:		Head of xmit buffer where data is written.
 * @xmit_tail:		Tail of xmit buffer where data is पढ़ो.
 * @xmit_empty:		Completion क्रम xmit buffer being empty.
 */
काष्ठा mips_ejtag_fdc_tty_port अणु
	काष्ठा tty_port			 port;
	काष्ठा mips_ejtag_fdc_tty	*driver;
	raw_spinlock_t			 rx_lock;
	व्योम				*rx_buf;
	spinlock_t			 xmit_lock;
	अचिन्हित पूर्णांक			 xmit_cnt;
	अचिन्हित पूर्णांक			 xmit_head;
	अचिन्हित पूर्णांक			 xmit_tail;
	काष्ठा completion		 xmit_empty;
पूर्ण;

/**
 * काष्ठा mips_ejtag_fdc_tty - Driver data क्रम FDC as a whole.
 * @dev:		FDC device (क्रम dev_*() logging).
 * @driver:		TTY driver.
 * @cpu:		CPU number क्रम this FDC.
 * @fdc_name:		FDC name (not क्रम base of channel names).
 * @driver_name:	Base of driver name.
 * @ports:		Per-channel data.
 * @रुकोqueue:		Wait queue क्रम रुकोing क्रम TX data, or क्रम space in TX
 *			FIFO.
 * @lock:		Lock to protect FDCFG (पूर्णांकerrupt enable).
 * @thपढ़ो:		KThपढ़ो क्रम writing out data to FDC.
 * @reg:		FDC रेजिस्टरs.
 * @tx_fअगरo:		TX FIFO size.
 * @xmit_size:		Size of each port's xmit buffer.
 * @xmit_total:		Total number of bytes (from all ports) to transmit.
 * @xmit_next:		Next port number to transmit from (round robin).
 * @xmit_full:		Indicates TX FIFO is full, we're रुकोing क्रम space.
 * @irq:		IRQ number (negative अगर no IRQ).
 * @removing:		Indicates the device is being हटाओd and @poll_समयr
 *			should not be restarted.
 * @poll_समयr:		Timer क्रम polling क्रम पूर्णांकerrupt events when @irq < 0.
 * @sysrq_pressed:	Whether the magic sysrq key combination has been
 *			detected. See mips_ejtag_fdc_handle().
 */
काष्ठा mips_ejtag_fdc_tty अणु
	काष्ठा device			*dev;
	काष्ठा tty_driver		*driver;
	अचिन्हित पूर्णांक			 cpu;
	अक्षर				 fdc_name[16];
	अक्षर				 driver_name[16];
	काष्ठा mips_ejtag_fdc_tty_port	 ports[NUM_TTY_CHANNELS];
	रुको_queue_head_t		 रुकोqueue;
	raw_spinlock_t			 lock;
	काष्ठा task_काष्ठा		*thपढ़ो;

	व्योम __iomem			*reg;
	u8				 tx_fअगरo;

	अचिन्हित पूर्णांक			 xmit_size;
	atomic_t			 xmit_total;
	अचिन्हित पूर्णांक			 xmit_next;
	bool				 xmit_full;

	पूर्णांक				 irq;
	bool				 removing;
	काष्ठा समयr_list		 poll_समयr;

#अगर_घोषित CONFIG_MAGIC_SYSRQ
	bool				 sysrq_pressed;
#पूर्ण_अगर
पूर्ण;

/* Hardware access */

अटल अंतरभूत व्योम mips_ejtag_fdc_ग_लिखो(काष्ठा mips_ejtag_fdc_tty *priv,
					अचिन्हित पूर्णांक offs, अचिन्हित पूर्णांक data)
अणु
	__raw_ग_लिखोl(data, priv->reg + offs);
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक mips_ejtag_fdc_पढ़ो(काष्ठा mips_ejtag_fdc_tty *priv,
					       अचिन्हित पूर्णांक offs)
अणु
	वापस __raw_पढ़ोl(priv->reg + offs);
पूर्ण

/* Encoding of byte stream in FDC words */

/**
 * काष्ठा fdc_word - FDC word encoding some number of bytes of data.
 * @word:		Raw FDC word.
 * @bytes:		Number of bytes encoded by @word.
 */
काष्ठा fdc_word अणु
	u32		word;
	अचिन्हित पूर्णांक	bytes;
पूर्ण;

/*
 * This is a compact encoding which allows every 1 byte, 2 byte, and 3 byte
 * sequence to be encoded in a single word, जबतक allowing the majority of 4
 * byte sequences (including all ASCII and common binary data) to be encoded in
 * a single word too.
 *    _______________________ _____________
 *   |       FDC Word        |             |
 *   |31-24|23-16|15-8 | 7-0 |    Bytes    |
 *   |_____|_____|_____|_____|_____________|
 *   |     |     |     |     |             |
 *   |0x80 |0x80 |0x80 |  WW | WW          |
 *   |0x81 |0x81 |  XX |  WW | WW XX       |
 *   |0x82 |  YY |  XX |  WW | WW XX YY    |
 *   |  ZZ |  YY |  XX |  WW | WW XX YY ZZ |
 *   |_____|_____|_____|_____|_____________|
 *
 * Note that the 4-byte encoding can only be used where none of the other 3
 * encodings match, otherwise it must fall back to the 3 byte encoding.
 */

/* ranges >= 1 && sizes[0] >= 1 */
अटल काष्ठा fdc_word mips_ejtag_fdc_encode(स्थिर अक्षर **ptrs,
					     अचिन्हित पूर्णांक *sizes,
					     अचिन्हित पूर्णांक ranges)
अणु
	काष्ठा fdc_word word = अणु 0, 0 पूर्ण;
	स्थिर अक्षर **ptrs_end = ptrs + ranges;

	क्रम (; ptrs < ptrs_end; ++ptrs) अणु
		स्थिर अक्षर *ptr = *(ptrs++);
		स्थिर अक्षर *end = ptr + *(sizes++);

		क्रम (; ptr < end; ++ptr) अणु
			word.word |= (u8)*ptr << (8*word.bytes);
			++word.bytes;
			अगर (word.bytes == 4)
				जाओ करोne;
		पूर्ण
	पूर्ण
करोne:
	/* Choose the appropriate encoding */
	चयन (word.bytes) अणु
	हाल 4:
		/* 4 byte encoding, but करोn't match the 1-3 byte encodings */
		अगर ((word.word >> 8) != 0x808080 &&
		    (word.word >> 16) != 0x8181 &&
		    (word.word >> 24) != 0x82)
			अवरोध;
		/* Fall back to a 3 byte encoding */
		word.bytes = 3;
		word.word &= 0x00ffffff;
		fallthrough;
	हाल 3:
		/* 3 byte encoding */
		word.word |= 0x82000000;
		अवरोध;
	हाल 2:
		/* 2 byte encoding */
		word.word |= 0x81810000;
		अवरोध;
	हाल 1:
		/* 1 byte encoding */
		word.word |= 0x80808000;
		अवरोध;
	पूर्ण
	वापस word;
पूर्ण

अटल अचिन्हित पूर्णांक mips_ejtag_fdc_decode(u32 word, अक्षर *buf)
अणु
	buf[0] = (u8)word;
	word >>= 8;
	अगर (word == 0x808080)
		वापस 1;
	buf[1] = (u8)word;
	word >>= 8;
	अगर (word == 0x8181)
		वापस 2;
	buf[2] = (u8)word;
	word >>= 8;
	अगर (word == 0x82)
		वापस 3;
	buf[3] = (u8)word;
	वापस 4;
पूर्ण

/* Console operations */

/**
 * काष्ठा mips_ejtag_fdc_console - Wrapper काष्ठा क्रम FDC consoles.
 * @cons:		Console object.
 * @tty_drv:		TTY driver associated with this console.
 * @lock:		Lock to protect concurrent access to other fields.
 *			This is raw because it may be used very early.
 * @initialised:	Whether the console is initialised.
 * @regs:		Registers base address क्रम each CPU.
 */
काष्ठा mips_ejtag_fdc_console अणु
	काष्ठा console		 cons;
	काष्ठा tty_driver	*tty_drv;
	raw_spinlock_t		 lock;
	bool			 initialised;
	व्योम __iomem		*regs[NR_CPUS];
पूर्ण;

/* Low level console ग_लिखो shared by early console and normal console */
अटल व्योम mips_ejtag_fdc_console_ग_लिखो(काष्ठा console *c, स्थिर अक्षर *s,
					 अचिन्हित पूर्णांक count)
अणु
	काष्ठा mips_ejtag_fdc_console *cons =
		container_of(c, काष्ठा mips_ejtag_fdc_console, cons);
	व्योम __iomem *regs;
	काष्ठा fdc_word word;
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक i, buf_len, cpu;
	bool करोne_cr = false;
	अक्षर buf[4];
	स्थिर अक्षर *buf_ptr = buf;
	/* Number of bytes of input data encoded up to each byte in buf */
	u8 inc[4];

	local_irq_save(flags);
	cpu = smp_processor_id();
	regs = cons->regs[cpu];
	/* First console output on this CPU? */
	अगर (!regs) अणु
		regs = mips_cdmm_early_probe(0xfd);
		cons->regs[cpu] = regs;
	पूर्ण
	/* Alपढ़ोy tried and failed to find FDC on this CPU? */
	अगर (IS_ERR(regs))
		जाओ out;
	जबतक (count) अणु
		/*
		 * Copy the next few अक्षरacters to a buffer so we can inject
		 * carriage वापसs beक्रमe newlines.
		 */
		क्रम (buf_len = 0, i = 0; buf_len < 4 && i < count; ++buf_len) अणु
			अगर (s[i] == '\n' && !करोne_cr) अणु
				buf[buf_len] = '\r';
				करोne_cr = true;
			पूर्ण अन्यथा अणु
				buf[buf_len] = s[i];
				करोne_cr = false;
				++i;
			पूर्ण
			inc[buf_len] = i;
		पूर्ण
		word = mips_ejtag_fdc_encode(&buf_ptr, &buf_len, 1);
		count -= inc[word.bytes - 1];
		s += inc[word.bytes - 1];

		/* Busy रुको until there's space in fअगरo */
		जबतक (__raw_पढ़ोl(regs + REG_FDSTAT) & REG_FDSTAT_TXF)
			;
		__raw_ग_लिखोl(word.word, regs + REG_FDTX(c->index));
	पूर्ण
out:
	local_irq_restore(flags);
पूर्ण

अटल काष्ठा tty_driver *mips_ejtag_fdc_console_device(काष्ठा console *c,
							पूर्णांक *index)
अणु
	काष्ठा mips_ejtag_fdc_console *cons =
		container_of(c, काष्ठा mips_ejtag_fdc_console, cons);

	*index = c->index;
	वापस cons->tty_drv;
पूर्ण

/* Initialise an FDC console (early or normal */
अटल पूर्णांक __init mips_ejtag_fdc_console_init(काष्ठा mips_ejtag_fdc_console *c)
अणु
	व्योम __iomem *regs;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret = 0;

	raw_spin_lock_irqsave(&c->lock, flags);
	/* Don't init twice */
	अगर (c->initialised)
		जाओ out;
	/* Look क्रम the FDC device */
	regs = mips_cdmm_early_probe(0xfd);
	अगर (IS_ERR(regs)) अणु
		ret = PTR_ERR(regs);
		जाओ out;
	पूर्ण

	c->initialised = true;
	c->regs[smp_processor_id()] = regs;
	रेजिस्टर_console(&c->cons);
out:
	raw_spin_unlock_irqrestore(&c->lock, flags);
	वापस ret;
पूर्ण

अटल काष्ठा mips_ejtag_fdc_console mips_ejtag_fdc_con = अणु
	.cons	= अणु
		.name	= "fdc",
		.ग_लिखो	= mips_ejtag_fdc_console_ग_लिखो,
		.device	= mips_ejtag_fdc_console_device,
		.flags	= CON_PRINTBUFFER,
		.index	= -1,
	पूर्ण,
	.lock	= __RAW_SPIN_LOCK_UNLOCKED(mips_ejtag_fdc_con.lock),
पूर्ण;

/* TTY RX/TX operations */

/**
 * mips_ejtag_fdc_put_chan() - Write out a block of channel data.
 * @priv:	Poपूर्णांकer to driver निजी data.
 * @chan:	Channel number.
 *
 * Write a single block of data out to the debug adapter. If the circular buffer
 * is wrapped then only the first block is written.
 *
 * Returns:	The number of bytes that were written.
 */
अटल अचिन्हित पूर्णांक mips_ejtag_fdc_put_chan(काष्ठा mips_ejtag_fdc_tty *priv,
					    अचिन्हित पूर्णांक chan)
अणु
	काष्ठा mips_ejtag_fdc_tty_port *dport;
	काष्ठा tty_काष्ठा *tty;
	स्थिर अक्षर *ptrs[2];
	अचिन्हित पूर्णांक sizes[2] = अणु 0 पूर्ण;
	काष्ठा fdc_word word = अणु .bytes = 0 पूर्ण;
	अचिन्हित दीर्घ flags;

	dport = &priv->ports[chan];
	spin_lock(&dport->xmit_lock);
	अगर (dport->xmit_cnt) अणु
		ptrs[0] = dport->port.xmit_buf + dport->xmit_tail;
		sizes[0] = min_t(अचिन्हित पूर्णांक,
				 priv->xmit_size - dport->xmit_tail,
				 dport->xmit_cnt);
		ptrs[1] = dport->port.xmit_buf;
		sizes[1] = dport->xmit_cnt - sizes[0];
		word = mips_ejtag_fdc_encode(ptrs, sizes, 1 + !!sizes[1]);

		dev_dbg(priv->dev, "%s%u: out %08x: \"%*pE%*pE\"\n",
			priv->driver_name, chan, word.word,
			min_t(पूर्णांक, word.bytes, sizes[0]), ptrs[0],
			max_t(पूर्णांक, 0, word.bytes - sizes[0]), ptrs[1]);

		local_irq_save(flags);
		/* Maybe we raced with the console and TX FIFO is full */
		अगर (mips_ejtag_fdc_पढ़ो(priv, REG_FDSTAT) & REG_FDSTAT_TXF)
			word.bytes = 0;
		अन्यथा
			mips_ejtag_fdc_ग_लिखो(priv, REG_FDTX(chan), word.word);
		local_irq_restore(flags);

		dport->xmit_cnt -= word.bytes;
		अगर (!dport->xmit_cnt) अणु
			/* Reset poपूर्णांकers to aव्योम wraps */
			dport->xmit_head = 0;
			dport->xmit_tail = 0;
			complete(&dport->xmit_empty);
		पूर्ण अन्यथा अणु
			dport->xmit_tail += word.bytes;
			अगर (dport->xmit_tail >= priv->xmit_size)
				dport->xmit_tail -= priv->xmit_size;
		पूर्ण
		atomic_sub(word.bytes, &priv->xmit_total);
	पूर्ण
	spin_unlock(&dport->xmit_lock);

	/* If we've made more data available, wake up tty */
	अगर (sizes[0] && word.bytes) अणु
		tty = tty_port_tty_get(&dport->port);
		अगर (tty) अणु
			tty_wakeup(tty);
			tty_kref_put(tty);
		पूर्ण
	पूर्ण

	वापस word.bytes;
पूर्ण

/**
 * mips_ejtag_fdc_put() - Kernel thपढ़ो to ग_लिखो out channel data to FDC.
 * @arg:	Driver poपूर्णांकer.
 *
 * This kernel thपढ़ो runs जबतक @priv->xmit_total != 0, and round robins the
 * channels writing out blocks of buffered data to the FDC TX FIFO.
 */
अटल पूर्णांक mips_ejtag_fdc_put(व्योम *arg)
अणु
	काष्ठा mips_ejtag_fdc_tty *priv = arg;
	काष्ठा mips_ejtag_fdc_tty_port *dport;
	अचिन्हित पूर्णांक ret;
	u32 cfg;

	__set_current_state(TASK_RUNNING);
	जबतक (!kthपढ़ो_should_stop()) अणु
		/* Wait क्रम data to actually ग_लिखो */
		रुको_event_पूर्णांकerruptible(priv->रुकोqueue,
					 atomic_पढ़ो(&priv->xmit_total) ||
					 kthपढ़ो_should_stop());
		अगर (kthपढ़ो_should_stop())
			अवरोध;

		/* Wait क्रम TX FIFO space to ग_लिखो data */
		raw_spin_lock_irq(&priv->lock);
		अगर (mips_ejtag_fdc_पढ़ो(priv, REG_FDSTAT) & REG_FDSTAT_TXF) अणु
			priv->xmit_full = true;
			अगर (priv->irq >= 0) अणु
				/* Enable TX पूर्णांकerrupt */
				cfg = mips_ejtag_fdc_पढ़ो(priv, REG_FDCFG);
				cfg &= ~REG_FDCFG_TXINTTHRES;
				cfg |= REG_FDCFG_TXINTTHRES_NOTFULL;
				mips_ejtag_fdc_ग_लिखो(priv, REG_FDCFG, cfg);
			पूर्ण
		पूर्ण
		raw_spin_unlock_irq(&priv->lock);
		रुको_event_पूर्णांकerruptible(priv->रुकोqueue,
					 !(mips_ejtag_fdc_पढ़ो(priv, REG_FDSTAT)
					   & REG_FDSTAT_TXF) ||
					 kthपढ़ो_should_stop());
		अगर (kthपढ़ो_should_stop())
			अवरोध;

		/* Find next channel with data to output */
		क्रम (;;) अणु
			dport = &priv->ports[priv->xmit_next];
			spin_lock(&dport->xmit_lock);
			ret = dport->xmit_cnt;
			spin_unlock(&dport->xmit_lock);
			अगर (ret)
				अवरोध;
			/* Round robin */
			++priv->xmit_next;
			अगर (priv->xmit_next >= NUM_TTY_CHANNELS)
				priv->xmit_next = 0;
		पूर्ण

		/* Try writing data to the chosen channel */
		ret = mips_ejtag_fdc_put_chan(priv, priv->xmit_next);

		/*
		 * If anything was output, move on to the next channel so as not
		 * to starve other channels.
		 */
		अगर (ret) अणु
			++priv->xmit_next;
			अगर (priv->xmit_next >= NUM_TTY_CHANNELS)
				priv->xmit_next = 0;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/**
 * mips_ejtag_fdc_handle() - Handle FDC events.
 * @priv:	Poपूर्णांकer to driver निजी data.
 *
 * Handle FDC events, such as new incoming data which needs draining out of the
 * RX FIFO and feeding पूर्णांकo the appropriate TTY ports, and space becoming
 * available in the TX FIFO which would allow more data to be written out.
 */
अटल व्योम mips_ejtag_fdc_handle(काष्ठा mips_ejtag_fdc_tty *priv)
अणु
	काष्ठा mips_ejtag_fdc_tty_port *dport;
	अचिन्हित पूर्णांक stat, channel, data, cfg, i, flipped;
	पूर्णांक len;
	अक्षर buf[4];

	क्रम (;;) अणु
		/* Find which channel the next FDC word is destined क्रम */
		stat = mips_ejtag_fdc_पढ़ो(priv, REG_FDSTAT);
		अगर (stat & REG_FDSTAT_RXE)
			अवरोध;
		channel = (stat & REG_FDSTAT_RXCHAN) >> REG_FDSTAT_RXCHAN_SHIFT;
		dport = &priv->ports[channel];

		/* Read out the FDC word, decode it, and pass to tty layer */
		raw_spin_lock(&dport->rx_lock);
		data = mips_ejtag_fdc_पढ़ो(priv, REG_FDRX);

		len = mips_ejtag_fdc_decode(data, buf);
		dev_dbg(priv->dev, "%s%u: in  %08x: \"%*pE\"\n",
			priv->driver_name, channel, data, len, buf);

		flipped = 0;
		क्रम (i = 0; i < len; ++i) अणु
#अगर_घोषित CONFIG_MAGIC_SYSRQ
#अगर_घोषित CONFIG_MIPS_EJTAG_FDC_KGDB
			/* Support just Ctrl+C with KGDB channel */
			अगर (channel == CONFIG_MIPS_EJTAG_FDC_KGDB_CHAN) अणु
				अगर (buf[i] == '\x03') अणु /* ^C */
					handle_sysrq('g');
					जारी;
				पूर्ण
			पूर्ण
#पूर्ण_अगर
			/* Support Ctrl+O क्रम console channel */
			अगर (channel == mips_ejtag_fdc_con.cons.index) अणु
				अगर (buf[i] == '\x0f') अणु	/* ^O */
					priv->sysrq_pressed =
						!priv->sysrq_pressed;
					अगर (priv->sysrq_pressed)
						जारी;
				पूर्ण अन्यथा अगर (priv->sysrq_pressed) अणु
					handle_sysrq(buf[i]);
					priv->sysrq_pressed = false;
					जारी;
				पूर्ण
			पूर्ण
#पूर्ण_अगर /* CONFIG_MAGIC_SYSRQ */

			/* Check the port isn't being shut करोwn */
			अगर (!dport->rx_buf)
				जारी;

			flipped += tty_insert_flip_अक्षर(&dport->port, buf[i],
							TTY_NORMAL);
		पूर्ण
		अगर (flipped)
			tty_flip_buffer_push(&dport->port);

		raw_spin_unlock(&dport->rx_lock);
	पूर्ण

	/* If TX FIFO no दीर्घer full we may be able to ग_लिखो more data */
	raw_spin_lock(&priv->lock);
	अगर (priv->xmit_full && !(stat & REG_FDSTAT_TXF)) अणु
		priv->xmit_full = false;

		/* Disable TX पूर्णांकerrupt */
		cfg = mips_ejtag_fdc_पढ़ो(priv, REG_FDCFG);
		cfg &= ~REG_FDCFG_TXINTTHRES;
		cfg |= REG_FDCFG_TXINTTHRES_DISABLED;
		mips_ejtag_fdc_ग_लिखो(priv, REG_FDCFG, cfg);

		/* Wait the kthपढ़ो so it can try writing more data */
		wake_up_पूर्णांकerruptible(&priv->रुकोqueue);
	पूर्ण
	raw_spin_unlock(&priv->lock);
पूर्ण

/**
 * mips_ejtag_fdc_isr() - Interrupt handler.
 * @irq:	IRQ number.
 * @dev_id:	Poपूर्णांकer to driver निजी data.
 *
 * This is the पूर्णांकerrupt handler, used when पूर्णांकerrupts are enabled.
 *
 * It simply triggers the common FDC handler code.
 *
 * Returns:	IRQ_HANDLED अगर an FDC पूर्णांकerrupt was pending.
 *		IRQ_NONE otherwise.
 */
अटल irqवापस_t mips_ejtag_fdc_isr(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा mips_ejtag_fdc_tty *priv = dev_id;

	/*
	 * We're not using proper per-cpu IRQs, so we must be careful not to
	 * handle IRQs on CPUs we're not पूर्णांकerested in.
	 *
	 * Ideally proper per-cpu IRQ handlers could be used, but that करोesn't
	 * fit well with the whole sharing of the मुख्य CPU IRQ lines. When we
	 * have something with a GIC that routes the FDC IRQs (i.e. no sharing
	 * between handlers) then support could be added more easily.
	 */
	अगर (smp_processor_id() != priv->cpu)
		वापस IRQ_NONE;

	/* If no FDC पूर्णांकerrupt pending, it wasn't क्रम us */
	अगर (!(पढ़ो_c0_cause() & CAUSEF_FDCI))
		वापस IRQ_NONE;

	mips_ejtag_fdc_handle(priv);
	वापस IRQ_HANDLED;
पूर्ण

/**
 * mips_ejtag_fdc_tty_समयr() - Poll FDC क्रम incoming data.
 * @opaque:	Poपूर्णांकer to driver निजी data.
 *
 * This is the समयr handler क्रम when पूर्णांकerrupts are disabled and polling the
 * FDC state is required.
 *
 * It simply triggers the common FDC handler code and arranges क्रम further
 * polling.
 */
अटल व्योम mips_ejtag_fdc_tty_समयr(काष्ठा समयr_list *t)
अणु
	काष्ठा mips_ejtag_fdc_tty *priv = from_समयr(priv, t, poll_समयr);

	mips_ejtag_fdc_handle(priv);
	अगर (!priv->removing)
		mod_समयr(&priv->poll_समयr, jअगरfies + FDC_TTY_POLL);
पूर्ण

/* TTY Port operations */

अटल पूर्णांक mips_ejtag_fdc_tty_port_activate(काष्ठा tty_port *port,
					    काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा mips_ejtag_fdc_tty_port *dport =
		container_of(port, काष्ठा mips_ejtag_fdc_tty_port, port);
	व्योम *rx_buf;

	/* Allocate the buffer we use क्रम writing data */
	अगर (tty_port_alloc_xmit_buf(port) < 0)
		जाओ err;

	/* Allocate the buffer we use क्रम पढ़ोing data */
	rx_buf = kzalloc(RX_BUF_SIZE, GFP_KERNEL);
	अगर (!rx_buf)
		जाओ err_मुक्त_xmit;

	raw_spin_lock_irq(&dport->rx_lock);
	dport->rx_buf = rx_buf;
	raw_spin_unlock_irq(&dport->rx_lock);

	वापस 0;
err_मुक्त_xmit:
	tty_port_मुक्त_xmit_buf(port);
err:
	वापस -ENOMEM;
पूर्ण

अटल व्योम mips_ejtag_fdc_tty_port_shutकरोwn(काष्ठा tty_port *port)
अणु
	काष्ठा mips_ejtag_fdc_tty_port *dport =
		container_of(port, काष्ठा mips_ejtag_fdc_tty_port, port);
	काष्ठा mips_ejtag_fdc_tty *priv = dport->driver;
	व्योम *rx_buf;
	अचिन्हित पूर्णांक count;

	spin_lock(&dport->xmit_lock);
	count = dport->xmit_cnt;
	spin_unlock(&dport->xmit_lock);
	अगर (count) अणु
		/*
		 * There's still data to ग_लिखो out, so wake and रुको क्रम the
		 * ग_लिखोr thपढ़ो to drain the buffer.
		 */
		wake_up_पूर्णांकerruptible(&priv->रुकोqueue);
		रुको_क्रम_completion(&dport->xmit_empty);
	पूर्ण

	/* Null the पढ़ो buffer (समयr could still be running!) */
	raw_spin_lock_irq(&dport->rx_lock);
	rx_buf = dport->rx_buf;
	dport->rx_buf = शून्य;
	raw_spin_unlock_irq(&dport->rx_lock);
	/* Free the पढ़ो buffer */
	kमुक्त(rx_buf);

	/* Free the ग_लिखो buffer */
	tty_port_मुक्त_xmit_buf(port);
पूर्ण

अटल स्थिर काष्ठा tty_port_operations mips_ejtag_fdc_tty_port_ops = अणु
	.activate	= mips_ejtag_fdc_tty_port_activate,
	.shutकरोwn	= mips_ejtag_fdc_tty_port_shutकरोwn,
पूर्ण;

/* TTY operations */

अटल पूर्णांक mips_ejtag_fdc_tty_install(काष्ठा tty_driver *driver,
				      काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा mips_ejtag_fdc_tty *priv = driver->driver_state;

	tty->driver_data = &priv->ports[tty->index];
	वापस tty_port_install(&priv->ports[tty->index].port, driver, tty);
पूर्ण

अटल पूर्णांक mips_ejtag_fdc_tty_खोलो(काष्ठा tty_काष्ठा *tty, काष्ठा file *filp)
अणु
	वापस tty_port_खोलो(tty->port, tty, filp);
पूर्ण

अटल व्योम mips_ejtag_fdc_tty_बंद(काष्ठा tty_काष्ठा *tty, काष्ठा file *filp)
अणु
	वापस tty_port_बंद(tty->port, tty, filp);
पूर्ण

अटल व्योम mips_ejtag_fdc_tty_hangup(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा mips_ejtag_fdc_tty_port *dport = tty->driver_data;
	काष्ठा mips_ejtag_fdc_tty *priv = dport->driver;

	/* Drop any data in the xmit buffer */
	spin_lock(&dport->xmit_lock);
	अगर (dport->xmit_cnt) अणु
		atomic_sub(dport->xmit_cnt, &priv->xmit_total);
		dport->xmit_cnt = 0;
		dport->xmit_head = 0;
		dport->xmit_tail = 0;
		complete(&dport->xmit_empty);
	पूर्ण
	spin_unlock(&dport->xmit_lock);

	tty_port_hangup(tty->port);
पूर्ण

अटल पूर्णांक mips_ejtag_fdc_tty_ग_लिखो(काष्ठा tty_काष्ठा *tty,
				    स्थिर अचिन्हित अक्षर *buf, पूर्णांक total)
अणु
	पूर्णांक count, block;
	काष्ठा mips_ejtag_fdc_tty_port *dport = tty->driver_data;
	काष्ठा mips_ejtag_fdc_tty *priv = dport->driver;

	/*
	 * Write to output buffer.
	 *
	 * The reason that we asynchronously ग_लिखो the buffer is because अगर we
	 * were to ग_लिखो the buffer synchronously then because the channels are
	 * per-CPU the buffer would be written to the channel of whatever CPU
	 * we're running on.
	 *
	 * What we actually want to happen is have all input and output करोne on
	 * one CPU.
	 */
	spin_lock(&dport->xmit_lock);
	/* Work out how many bytes we can ग_लिखो to the xmit buffer */
	total = min(total, (पूर्णांक)(priv->xmit_size - dport->xmit_cnt));
	atomic_add(total, &priv->xmit_total);
	dport->xmit_cnt += total;
	/* Write the actual bytes (may need splitting अगर it wraps) */
	क्रम (count = total; count; count -= block) अणु
		block = min(count, (पूर्णांक)(priv->xmit_size - dport->xmit_head));
		स_नकल(dport->port.xmit_buf + dport->xmit_head, buf, block);
		dport->xmit_head += block;
		अगर (dport->xmit_head >= priv->xmit_size)
			dport->xmit_head -= priv->xmit_size;
		buf += block;
	पूर्ण
	count = dport->xmit_cnt;
	/* Xmit buffer no दीर्घer empty? */
	अगर (count)
		reinit_completion(&dport->xmit_empty);
	spin_unlock(&dport->xmit_lock);

	/* Wake up the kthपढ़ो */
	अगर (total)
		wake_up_पूर्णांकerruptible(&priv->रुकोqueue);
	वापस total;
पूर्ण

अटल पूर्णांक mips_ejtag_fdc_tty_ग_लिखो_room(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा mips_ejtag_fdc_tty_port *dport = tty->driver_data;
	काष्ठा mips_ejtag_fdc_tty *priv = dport->driver;
	पूर्णांक room;

	/* Report the space in the xmit buffer */
	spin_lock(&dport->xmit_lock);
	room = priv->xmit_size - dport->xmit_cnt;
	spin_unlock(&dport->xmit_lock);

	वापस room;
पूर्ण

अटल पूर्णांक mips_ejtag_fdc_tty_अक्षरs_in_buffer(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा mips_ejtag_fdc_tty_port *dport = tty->driver_data;
	पूर्णांक अक्षरs;

	/* Report the number of bytes in the xmit buffer */
	spin_lock(&dport->xmit_lock);
	अक्षरs = dport->xmit_cnt;
	spin_unlock(&dport->xmit_lock);

	वापस अक्षरs;
पूर्ण

अटल स्थिर काष्ठा tty_operations mips_ejtag_fdc_tty_ops = अणु
	.install		= mips_ejtag_fdc_tty_install,
	.खोलो			= mips_ejtag_fdc_tty_खोलो,
	.बंद			= mips_ejtag_fdc_tty_बंद,
	.hangup			= mips_ejtag_fdc_tty_hangup,
	.ग_लिखो			= mips_ejtag_fdc_tty_ग_लिखो,
	.ग_लिखो_room		= mips_ejtag_fdc_tty_ग_लिखो_room,
	.अक्षरs_in_buffer	= mips_ejtag_fdc_tty_अक्षरs_in_buffer,
पूर्ण;

पूर्णांक __weak get_c0_fdc_पूर्णांक(व्योम)
अणु
	वापस -1;
पूर्ण

अटल पूर्णांक mips_ejtag_fdc_tty_probe(काष्ठा mips_cdmm_device *dev)
अणु
	पूर्णांक ret, nport;
	काष्ठा mips_ejtag_fdc_tty_port *dport;
	काष्ठा mips_ejtag_fdc_tty *priv;
	काष्ठा tty_driver *driver;
	अचिन्हित पूर्णांक cfg, tx_fअगरo;

	priv = devm_kzalloc(&dev->dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;
	priv->cpu = dev->cpu;
	priv->dev = &dev->dev;
	mips_cdmm_set_drvdata(dev, priv);
	atomic_set(&priv->xmit_total, 0);
	raw_spin_lock_init(&priv->lock);

	priv->reg = devm_ioremap(priv->dev, dev->res.start,
					 resource_size(&dev->res));
	अगर (!priv->reg) अणु
		dev_err(priv->dev, "ioremap failed for resource %pR\n",
			&dev->res);
		वापस -ENOMEM;
	पूर्ण

	cfg = mips_ejtag_fdc_पढ़ो(priv, REG_FDCFG);
	tx_fअगरo = (cfg & REG_FDCFG_TXFIFOSIZE) >> REG_FDCFG_TXFIFOSIZE_SHIFT;
	/* Disable पूर्णांकerrupts */
	cfg &= ~(REG_FDCFG_TXINTTHRES | REG_FDCFG_RXINTTHRES);
	cfg |= REG_FDCFG_TXINTTHRES_DISABLED;
	cfg |= REG_FDCFG_RXINTTHRES_DISABLED;
	mips_ejtag_fdc_ग_लिखो(priv, REG_FDCFG, cfg);

	/* Make each port's xmit FIFO big enough to fill FDC TX FIFO */
	priv->xmit_size = min(tx_fअगरo * 4, (अचिन्हित पूर्णांक)SERIAL_XMIT_SIZE);

	driver = tty_alloc_driver(NUM_TTY_CHANNELS, TTY_DRIVER_REAL_RAW);
	अगर (IS_ERR(driver))
		वापस PTR_ERR(driver);
	priv->driver = driver;

	driver->driver_name = "ejtag_fdc";
	snम_लिखो(priv->fdc_name, माप(priv->fdc_name), "ttyFDC%u", dev->cpu);
	snम_लिखो(priv->driver_name, माप(priv->driver_name), "%sc",
		 priv->fdc_name);
	driver->name = priv->driver_name;
	driver->major = 0; /* Auto-allocate */
	driver->minor_start = 0;
	driver->type = TTY_DRIVER_TYPE_SERIAL;
	driver->subtype = SERIAL_TYPE_NORMAL;
	driver->init_termios = tty_std_termios;
	driver->init_termios.c_cflag |= CLOCAL;
	driver->driver_state = priv;

	tty_set_operations(driver, &mips_ejtag_fdc_tty_ops);
	क्रम (nport = 0; nport < NUM_TTY_CHANNELS; nport++) अणु
		dport = &priv->ports[nport];
		dport->driver = priv;
		tty_port_init(&dport->port);
		dport->port.ops = &mips_ejtag_fdc_tty_port_ops;
		raw_spin_lock_init(&dport->rx_lock);
		spin_lock_init(&dport->xmit_lock);
		/* The xmit buffer starts empty, i.e. completely written */
		init_completion(&dport->xmit_empty);
		complete(&dport->xmit_empty);
	पूर्ण

	/* Set up the console */
	mips_ejtag_fdc_con.regs[dev->cpu] = priv->reg;
	अगर (dev->cpu == 0)
		mips_ejtag_fdc_con.tty_drv = driver;

	init_रुकोqueue_head(&priv->रुकोqueue);
	priv->thपढ़ो = kthपढ़ो_create(mips_ejtag_fdc_put, priv, priv->fdc_name);
	अगर (IS_ERR(priv->thपढ़ो)) अणु
		ret = PTR_ERR(priv->thपढ़ो);
		dev_err(priv->dev, "Couldn't create kthread (%d)\n", ret);
		जाओ err_destroy_ports;
	पूर्ण
	/*
	 * Bind the ग_लिखोr thपढ़ो to the right CPU so it can't migrate.
	 * The channels are per-CPU and we want all channel I/O to be on a
	 * single predictable CPU.
	 */
	kthपढ़ो_bind(priv->thपढ़ो, dev->cpu);
	wake_up_process(priv->thपढ़ो);

	/* Look क्रम an FDC IRQ */
	priv->irq = get_c0_fdc_पूर्णांक();

	/* Try requesting the IRQ */
	अगर (priv->irq >= 0) अणु
		/*
		 * IRQF_SHARED, IRQF_COND_SUSPEND: The FDC IRQ may be shared with
		 * other local पूर्णांकerrupts such as the समयr which sets
		 * IRQF_TIMER (including IRQF_NO_SUSPEND).
		 *
		 * IRQF_NO_THREAD: The FDC IRQ isn't inभागidually maskable so it
		 * cannot be deferred and handled by a thपढ़ो on RT kernels. For
		 * this reason any spinlocks used from the ISR are raw.
		 */
		ret = devm_request_irq(priv->dev, priv->irq, mips_ejtag_fdc_isr,
				       IRQF_PERCPU | IRQF_SHARED |
				       IRQF_NO_THREAD | IRQF_COND_SUSPEND,
				       priv->fdc_name, priv);
		अगर (ret)
			priv->irq = -1;
	पूर्ण
	अगर (priv->irq >= 0) अणु
		/* IRQ is usable, enable RX पूर्णांकerrupt */
		raw_spin_lock_irq(&priv->lock);
		cfg = mips_ejtag_fdc_पढ़ो(priv, REG_FDCFG);
		cfg &= ~REG_FDCFG_RXINTTHRES;
		cfg |= REG_FDCFG_RXINTTHRES_NOTEMPTY;
		mips_ejtag_fdc_ग_लिखो(priv, REG_FDCFG, cfg);
		raw_spin_unlock_irq(&priv->lock);
	पूर्ण अन्यथा अणु
		/* If we didn't get an usable IRQ, poll instead */
		समयr_setup(&priv->poll_समयr, mips_ejtag_fdc_tty_समयr,
			    TIMER_PINNED);
		priv->poll_समयr.expires = jअगरfies + FDC_TTY_POLL;
		/*
		 * Always attach the समयr to the right CPU. The channels are
		 * per-CPU so all polling should be from a single CPU.
		 */
		add_समयr_on(&priv->poll_समयr, dev->cpu);

		dev_info(priv->dev, "No usable IRQ, polling enabled\n");
	पूर्ण

	ret = tty_रेजिस्टर_driver(driver);
	अगर (ret < 0) अणु
		dev_err(priv->dev, "Couldn't install tty driver (%d)\n", ret);
		जाओ err_stop_irq;
	पूर्ण

	वापस 0;

err_stop_irq:
	अगर (priv->irq >= 0) अणु
		raw_spin_lock_irq(&priv->lock);
		cfg = mips_ejtag_fdc_पढ़ो(priv, REG_FDCFG);
		/* Disable पूर्णांकerrupts */
		cfg &= ~(REG_FDCFG_TXINTTHRES | REG_FDCFG_RXINTTHRES);
		cfg |= REG_FDCFG_TXINTTHRES_DISABLED;
		cfg |= REG_FDCFG_RXINTTHRES_DISABLED;
		mips_ejtag_fdc_ग_लिखो(priv, REG_FDCFG, cfg);
		raw_spin_unlock_irq(&priv->lock);
	पूर्ण अन्यथा अणु
		priv->removing = true;
		del_समयr_sync(&priv->poll_समयr);
	पूर्ण
	kthपढ़ो_stop(priv->thपढ़ो);
err_destroy_ports:
	अगर (dev->cpu == 0)
		mips_ejtag_fdc_con.tty_drv = शून्य;
	क्रम (nport = 0; nport < NUM_TTY_CHANNELS; nport++) अणु
		dport = &priv->ports[nport];
		tty_port_destroy(&dport->port);
	पूर्ण
	put_tty_driver(priv->driver);
	वापस ret;
पूर्ण

अटल पूर्णांक mips_ejtag_fdc_tty_cpu_करोwn(काष्ठा mips_cdmm_device *dev)
अणु
	काष्ठा mips_ejtag_fdc_tty *priv = mips_cdmm_get_drvdata(dev);
	अचिन्हित पूर्णांक cfg;

	अगर (priv->irq >= 0) अणु
		raw_spin_lock_irq(&priv->lock);
		cfg = mips_ejtag_fdc_पढ़ो(priv, REG_FDCFG);
		/* Disable पूर्णांकerrupts */
		cfg &= ~(REG_FDCFG_TXINTTHRES | REG_FDCFG_RXINTTHRES);
		cfg |= REG_FDCFG_TXINTTHRES_DISABLED;
		cfg |= REG_FDCFG_RXINTTHRES_DISABLED;
		mips_ejtag_fdc_ग_लिखो(priv, REG_FDCFG, cfg);
		raw_spin_unlock_irq(&priv->lock);
	पूर्ण अन्यथा अणु
		priv->removing = true;
		del_समयr_sync(&priv->poll_समयr);
	पूर्ण
	kthपढ़ो_stop(priv->thपढ़ो);

	वापस 0;
पूर्ण

अटल पूर्णांक mips_ejtag_fdc_tty_cpu_up(काष्ठा mips_cdmm_device *dev)
अणु
	काष्ठा mips_ejtag_fdc_tty *priv = mips_cdmm_get_drvdata(dev);
	अचिन्हित पूर्णांक cfg;
	पूर्णांक ret = 0;

	अगर (priv->irq >= 0) अणु
		/*
		 * IRQ is usable, enable RX पूर्णांकerrupt
		 * This must be beक्रमe kthपढ़ो is restarted, as kthपढ़ो may
		 * enable TX पूर्णांकerrupt.
		 */
		raw_spin_lock_irq(&priv->lock);
		cfg = mips_ejtag_fdc_पढ़ो(priv, REG_FDCFG);
		cfg &= ~(REG_FDCFG_TXINTTHRES | REG_FDCFG_RXINTTHRES);
		cfg |= REG_FDCFG_TXINTTHRES_DISABLED;
		cfg |= REG_FDCFG_RXINTTHRES_NOTEMPTY;
		mips_ejtag_fdc_ग_लिखो(priv, REG_FDCFG, cfg);
		raw_spin_unlock_irq(&priv->lock);
	पूर्ण अन्यथा अणु
		/* Restart poll समयr */
		priv->removing = false;
		add_समयr_on(&priv->poll_समयr, dev->cpu);
	पूर्ण

	/* Restart the kthपढ़ो */
	priv->thपढ़ो = kthपढ़ो_create(mips_ejtag_fdc_put, priv, priv->fdc_name);
	अगर (IS_ERR(priv->thपढ़ो)) अणु
		ret = PTR_ERR(priv->thपढ़ो);
		dev_err(priv->dev, "Couldn't re-create kthread (%d)\n", ret);
		जाओ out;
	पूर्ण
	/* Bind it back to the right CPU and set it off */
	kthपढ़ो_bind(priv->thपढ़ो, dev->cpu);
	wake_up_process(priv->thपढ़ो);
out:
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा mips_cdmm_device_id mips_ejtag_fdc_tty_ids[] = अणु
	अणु .type = 0xfd पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल काष्ठा mips_cdmm_driver mips_ejtag_fdc_tty_driver = अणु
	.drv		= अणु
		.name	= "mips_ejtag_fdc",
	पूर्ण,
	.probe		= mips_ejtag_fdc_tty_probe,
	.cpu_करोwn	= mips_ejtag_fdc_tty_cpu_करोwn,
	.cpu_up		= mips_ejtag_fdc_tty_cpu_up,
	.id_table	= mips_ejtag_fdc_tty_ids,
पूर्ण;
builtin_mips_cdmm_driver(mips_ejtag_fdc_tty_driver);

अटल पूर्णांक __init mips_ejtag_fdc_init_console(व्योम)
अणु
	वापस mips_ejtag_fdc_console_init(&mips_ejtag_fdc_con);
पूर्ण
console_initcall(mips_ejtag_fdc_init_console);

#अगर_घोषित CONFIG_MIPS_EJTAG_FDC_EARLYCON
अटल काष्ठा mips_ejtag_fdc_console mips_ejtag_fdc_earlycon = अणु
	.cons	= अणु
		.name	= "early_fdc",
		.ग_लिखो	= mips_ejtag_fdc_console_ग_लिखो,
		.flags	= CON_PRINTBUFFER | CON_BOOT,
		.index	= CONSOLE_CHANNEL,
	पूर्ण,
	.lock	= __RAW_SPIN_LOCK_UNLOCKED(mips_ejtag_fdc_earlycon.lock),
पूर्ण;

पूर्णांक __init setup_early_fdc_console(व्योम)
अणु
	वापस mips_ejtag_fdc_console_init(&mips_ejtag_fdc_earlycon);
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_MIPS_EJTAG_FDC_KGDB

/* पढ़ो buffer to allow decompaction */
अटल अचिन्हित पूर्णांक kgdbfdc_rbuflen;
अटल अचिन्हित पूर्णांक kgdbfdc_rpos;
अटल अक्षर kgdbfdc_rbuf[4];

/* ग_लिखो buffer to allow compaction */
अटल अचिन्हित पूर्णांक kgdbfdc_wbuflen;
अटल अक्षर kgdbfdc_wbuf[4];

अटल व्योम __iomem *kgdbfdc_setup(व्योम)
अणु
	व्योम __iomem *regs;
	अचिन्हित पूर्णांक cpu;

	/* Find address, piggy backing off console percpu regs */
	cpu = smp_processor_id();
	regs = mips_ejtag_fdc_con.regs[cpu];
	/* First console output on this CPU? */
	अगर (!regs) अणु
		regs = mips_cdmm_early_probe(0xfd);
		mips_ejtag_fdc_con.regs[cpu] = regs;
	पूर्ण
	/* Alपढ़ोy tried and failed to find FDC on this CPU? */
	अगर (IS_ERR(regs))
		वापस regs;

	वापस regs;
पूर्ण

/* पढ़ो a अक्षरacter from the पढ़ो buffer, filling from FDC RX FIFO */
अटल पूर्णांक kgdbfdc_पढ़ो_अक्षर(व्योम)
अणु
	अचिन्हित पूर्णांक stat, channel, data;
	व्योम __iomem *regs;

	/* No more data, try and पढ़ो another FDC word from RX FIFO */
	अगर (kgdbfdc_rpos >= kgdbfdc_rbuflen) अणु
		kgdbfdc_rpos = 0;
		kgdbfdc_rbuflen = 0;

		regs = kgdbfdc_setup();
		अगर (IS_ERR(regs))
			वापस NO_POLL_CHAR;

		/* Read next word from KGDB channel */
		करो अणु
			stat = __raw_पढ़ोl(regs + REG_FDSTAT);

			/* No data रुकोing? */
			अगर (stat & REG_FDSTAT_RXE)
				वापस NO_POLL_CHAR;

			/* Read next word */
			channel = (stat & REG_FDSTAT_RXCHAN) >>
					REG_FDSTAT_RXCHAN_SHIFT;
			data = __raw_पढ़ोl(regs + REG_FDRX);
		पूर्ण जबतक (channel != CONFIG_MIPS_EJTAG_FDC_KGDB_CHAN);

		/* Decode पूर्णांकo rbuf */
		kgdbfdc_rbuflen = mips_ejtag_fdc_decode(data, kgdbfdc_rbuf);
	पूर्ण
	pr_devel("kgdbfdc r %c\n", kgdbfdc_rbuf[kgdbfdc_rpos]);
	वापस kgdbfdc_rbuf[kgdbfdc_rpos++];
पूर्ण

/* push an FDC word from ग_लिखो buffer to TX FIFO */
अटल व्योम kgdbfdc_push_one(व्योम)
अणु
	स्थिर अक्षर *bufs[1] = अणु kgdbfdc_wbuf पूर्ण;
	काष्ठा fdc_word word;
	व्योम __iomem *regs;
	अचिन्हित पूर्णांक i;

	/* Conकाष्ठा a word from any data in buffer */
	word = mips_ejtag_fdc_encode(bufs, &kgdbfdc_wbuflen, 1);
	/* Relocate any reमुख्यing data to beginnning of buffer */
	kgdbfdc_wbuflen -= word.bytes;
	क्रम (i = 0; i < kgdbfdc_wbuflen; ++i)
		kgdbfdc_wbuf[i] = kgdbfdc_wbuf[i + word.bytes];

	regs = kgdbfdc_setup();
	अगर (IS_ERR(regs))
		वापस;

	/* Busy रुको until there's space in fअगरo */
	जबतक (__raw_पढ़ोl(regs + REG_FDSTAT) & REG_FDSTAT_TXF)
		;
	__raw_ग_लिखोl(word.word,
		     regs + REG_FDTX(CONFIG_MIPS_EJTAG_FDC_KGDB_CHAN));
पूर्ण

/* flush the whole ग_लिखो buffer to the TX FIFO */
अटल व्योम kgdbfdc_flush(व्योम)
अणु
	जबतक (kgdbfdc_wbuflen)
		kgdbfdc_push_one();
पूर्ण

/* ग_लिखो a अक्षरacter पूर्णांकo the ग_लिखो buffer, writing out अगर full */
अटल व्योम kgdbfdc_ग_लिखो_अक्षर(u8 chr)
अणु
	pr_devel("kgdbfdc w %c\n", chr);
	kgdbfdc_wbuf[kgdbfdc_wbuflen++] = chr;
	अगर (kgdbfdc_wbuflen >= माप(kgdbfdc_wbuf))
		kgdbfdc_push_one();
पूर्ण

अटल काष्ठा kgdb_io kgdbfdc_io_ops = अणु
	.name		= "kgdbfdc",
	.पढ़ो_अक्षर	= kgdbfdc_पढ़ो_अक्षर,
	.ग_लिखो_अक्षर	= kgdbfdc_ग_लिखो_अक्षर,
	.flush		= kgdbfdc_flush,
पूर्ण;

अटल पूर्णांक __init kgdbfdc_init(व्योम)
अणु
	kgdb_रेजिस्टर_io_module(&kgdbfdc_io_ops);
	वापस 0;
पूर्ण
early_initcall(kgdbfdc_init);
#पूर्ण_अगर
