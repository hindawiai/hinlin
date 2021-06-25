<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Driver क्रम ITE Tech Inc. IT8712F/IT8512 CIR
 *
 * Copyright (C) 2010 Juan Jesथजs Garcथऐa de Soria <skandalfo@gmail.com>
 *
 * Inspired by the original lirc_it87 and lirc_ite8709 drivers, on top of the
 * skeleton provided by the nuvoton-cir driver.
 *
 * The lirc_it87 driver was originally written by Hans-Gunter Lutke Uphues
 * <hg_lu@web.de> in 2001, with enhancements by Christoph Bartelmus
 * <lirc@bartelmus.de>, Andrew Calkin <r_tay@hoपंचांगail.com> and James Edwards
 * <jimbo-lirc@edwardsclan.net>.
 *
 * The lirc_ite8709 driver was written by Grथऊgory Lardiथउre
 * <spmf2004-lirc@yahoo.fr> in 2008.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/pnp.h>
#समावेश <linux/पन.स>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/sched.h>
#समावेश <linux/delay.h>
#समावेश <linux/slab.h>
#समावेश <linux/input.h>
#समावेश <linux/bitops.h>
#समावेश <media/rc-core.h>
#समावेश <linux/pci_ids.h>

#समावेश "ite-cir.h"

/* module parameters */

/* शेष sample period */
अटल दीर्घ sample_period = NSEC_PER_SEC / 115200;
module_param(sample_period, दीर्घ, S_IRUGO | S_IWUSR);
MODULE_PARM_DESC(sample_period, "sample period");

/* override detected model id */
अटल पूर्णांक model_number = -1;
module_param(model_number, पूर्णांक, S_IRUGO | S_IWUSR);
MODULE_PARM_DESC(model_number, "Use this model number, don't autodetect");


/* HW-independent code functions */

/* check whether carrier frequency is high frequency */
अटल अंतरभूत bool ite_is_high_carrier_freq(अचिन्हित पूर्णांक freq)
अणु
	वापस freq >= ITE_HCF_MIN_CARRIER_FREQ;
पूर्ण

/* get the bits required to program the carrier frequency in CFQ bits,
 * unshअगरted */
अटल u8 ite_get_carrier_freq_bits(अचिन्हित पूर्णांक freq)
अणु
	अगर (ite_is_high_carrier_freq(freq)) अणु
		अगर (freq < 425000)
			वापस ITE_CFQ_400;

		अन्यथा अगर (freq < 465000)
			वापस ITE_CFQ_450;

		अन्यथा अगर (freq < 490000)
			वापस ITE_CFQ_480;

		अन्यथा
			वापस ITE_CFQ_500;
	पूर्ण अन्यथा अणु
			/* trim to limits */
		अगर (freq < ITE_LCF_MIN_CARRIER_FREQ)
			freq = ITE_LCF_MIN_CARRIER_FREQ;
		अगर (freq > ITE_LCF_MAX_CARRIER_FREQ)
			freq = ITE_LCF_MAX_CARRIER_FREQ;

		/* convert to kHz and subtract the base freq */
		freq = DIV_ROUND_CLOSEST(freq - ITE_LCF_MIN_CARRIER_FREQ, 1000);

		वापस (u8) freq;
	पूर्ण
पूर्ण

/* get the bits required to program the pulse with in TXMPW */
अटल u8 ite_get_pulse_width_bits(अचिन्हित पूर्णांक freq, पूर्णांक duty_cycle)
अणु
	अचिन्हित दीर्घ period_ns, on_ns;

	/* sanitize freq पूर्णांकo range */
	अगर (freq < ITE_LCF_MIN_CARRIER_FREQ)
		freq = ITE_LCF_MIN_CARRIER_FREQ;
	अगर (freq > ITE_HCF_MAX_CARRIER_FREQ)
		freq = ITE_HCF_MAX_CARRIER_FREQ;

	period_ns = 1000000000UL / freq;
	on_ns = period_ns * duty_cycle / 100;

	अगर (ite_is_high_carrier_freq(freq)) अणु
		अगर (on_ns < 750)
			वापस ITE_TXMPW_A;

		अन्यथा अगर (on_ns < 850)
			वापस ITE_TXMPW_B;

		अन्यथा अगर (on_ns < 950)
			वापस ITE_TXMPW_C;

		अन्यथा अगर (on_ns < 1080)
			वापस ITE_TXMPW_D;

		अन्यथा
			वापस ITE_TXMPW_E;
	पूर्ण अन्यथा अणु
		अगर (on_ns < 6500)
			वापस ITE_TXMPW_A;

		अन्यथा अगर (on_ns < 7850)
			वापस ITE_TXMPW_B;

		अन्यथा अगर (on_ns < 9650)
			वापस ITE_TXMPW_C;

		अन्यथा अगर (on_ns < 11950)
			वापस ITE_TXMPW_D;

		अन्यथा
			वापस ITE_TXMPW_E;
	पूर्ण
पूर्ण

/* decode raw bytes as received by the hardware, and push them to the ir-core
 * layer */
अटल व्योम ite_decode_bytes(काष्ठा ite_dev *dev, स्थिर u8 * data, पूर्णांक
			     length)
अणु
	अचिन्हित दीर्घ *ldata;
	अचिन्हित पूर्णांक next_one, next_zero, size;
	काष्ठा ir_raw_event ev = अणुपूर्ण;

	अगर (length == 0)
		वापस;

	ldata = (अचिन्हित दीर्घ *)data;
	size = length << 3;
	next_one = find_next_bit_le(ldata, size, 0);
	अगर (next_one > 0) अणु
		ev.pulse = true;
		ev.duration = ITE_BITS_TO_US(next_one, sample_period);
		ir_raw_event_store_with_filter(dev->rdev, &ev);
	पूर्ण

	जबतक (next_one < size) अणु
		next_zero = find_next_zero_bit_le(ldata, size, next_one + 1);
		ev.pulse = false;
		ev.duration = ITE_BITS_TO_US(next_zero - next_one, sample_period);
		ir_raw_event_store_with_filter(dev->rdev, &ev);

		अगर (next_zero < size) अणु
			next_one = find_next_bit_le(ldata, size, next_zero + 1);
			ev.pulse = true;
			ev.duration = ITE_BITS_TO_US(next_one - next_zero,
						     sample_period);
			ir_raw_event_store_with_filter(dev->rdev, &ev);
		पूर्ण अन्यथा
			next_one = size;
	पूर्ण

	ir_raw_event_handle(dev->rdev);

	dev_dbg(&dev->rdev->dev, "decoded %d bytes\n", length);
पूर्ण

/* set all the rx/tx carrier parameters; this must be called with the device
 * spinlock held */
अटल व्योम ite_set_carrier_params(काष्ठा ite_dev *dev)
अणु
	अचिन्हित पूर्णांक freq, low_freq, high_freq;
	पूर्णांक allowance;
	bool use_demodulator;
	bool क्रम_tx = dev->transmitting;

	अगर (क्रम_tx) अणु
		/* we करोn't need no stinking calculations */
		freq = dev->tx_carrier_freq;
		allowance = ITE_RXDCR_DEFAULT;
		use_demodulator = false;
	पूर्ण अन्यथा अणु
		low_freq = dev->rx_low_carrier_freq;
		high_freq = dev->rx_high_carrier_freq;

		अगर (low_freq == 0) अणु
			/* करोn't demodulate */
			freq = ITE_DEFAULT_CARRIER_FREQ;
			allowance = ITE_RXDCR_DEFAULT;
			use_demodulator = false;
		पूर्ण अन्यथा अणु
			/* calculate the middle freq */
			freq = (low_freq + high_freq) / 2;

			/* calculate the allowance */
			allowance =
			    DIV_ROUND_CLOSEST(10000 * (high_freq - low_freq),
					      ITE_RXDCR_PER_10000_STEP
					      * (high_freq + low_freq));

			अगर (allowance < 1)
				allowance = 1;

			अगर (allowance > ITE_RXDCR_MAX)
				allowance = ITE_RXDCR_MAX;

			use_demodulator = true;
		पूर्ण
	पूर्ण

	/* set the carrier parameters in a device-dependent way */
	dev->params->set_carrier_params(dev, ite_is_high_carrier_freq(freq),
		 use_demodulator, ite_get_carrier_freq_bits(freq), allowance,
		 ite_get_pulse_width_bits(freq, dev->tx_duty_cycle));
पूर्ण

/* पूर्णांकerrupt service routine क्रम incoming and outgoing CIR data */
अटल irqवापस_t ite_cir_isr(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा ite_dev *dev = data;
	irqवापस_t ret = IRQ_RETVAL(IRQ_NONE);
	u8 rx_buf[ITE_RX_FIFO_LEN];
	पूर्णांक rx_bytes;
	पूर्णांक अगरlags;

	/* grab the spinlock */
	spin_lock(&dev->lock);

	/* पढ़ो the पूर्णांकerrupt flags */
	अगरlags = dev->params->get_irq_causes(dev);

	/* Check क्रम RX overflow */
	अगर (अगरlags & ITE_IRQ_RX_FIFO_OVERRUN) अणु
		dev_warn(&dev->rdev->dev, "receive overflow\n");
		ir_raw_event_reset(dev->rdev);
	पूर्ण

	/* check क्रम the receive पूर्णांकerrupt */
	अगर (अगरlags & ITE_IRQ_RX_FIFO) अणु
		/* पढ़ो the FIFO bytes */
		rx_bytes = dev->params->get_rx_bytes(dev, rx_buf,
						    ITE_RX_FIFO_LEN);

		dev_dbg(&dev->rdev->dev, "interrupt %d RX bytes\n", rx_bytes);

		अगर (rx_bytes > 0) अणु
			/* drop the spinlock, since the ir-core layer
			 * may call us back again through
			 * ite_s_idle() */
			spin_unlock(&dev->lock);

			/* decode the data we've just received */
			ite_decode_bytes(dev, rx_buf, rx_bytes);

			/* reacquire the spinlock */
			spin_lock(&dev->lock);

			/* mark the पूर्णांकerrupt as serviced */
			ret = IRQ_RETVAL(IRQ_HANDLED);
		पूर्ण
	पूर्ण अन्यथा अगर (अगरlags & ITE_IRQ_TX_FIFO) अणु
		/* FIFO space available पूर्णांकerrupt */
		dev_dbg(&dev->rdev->dev, "interrupt TX FIFO\n");

		/* wake any sleeping transmitter */
		wake_up_पूर्णांकerruptible(&dev->tx_queue);

		/* mark the पूर्णांकerrupt as serviced */
		ret = IRQ_RETVAL(IRQ_HANDLED);
	पूर्ण

	/* drop the spinlock */
	spin_unlock(&dev->lock);

	वापस ret;
पूर्ण

/* set the rx carrier freq range, guess it's in Hz... */
अटल पूर्णांक ite_set_rx_carrier_range(काष्ठा rc_dev *rcdev, u32 carrier_low, u32
				    carrier_high)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा ite_dev *dev = rcdev->priv;

	spin_lock_irqsave(&dev->lock, flags);
	dev->rx_low_carrier_freq = carrier_low;
	dev->rx_high_carrier_freq = carrier_high;
	ite_set_carrier_params(dev);
	spin_unlock_irqrestore(&dev->lock, flags);

	वापस 0;
पूर्ण

/* set the tx carrier freq, guess it's in Hz... */
अटल पूर्णांक ite_set_tx_carrier(काष्ठा rc_dev *rcdev, u32 carrier)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा ite_dev *dev = rcdev->priv;

	spin_lock_irqsave(&dev->lock, flags);
	dev->tx_carrier_freq = carrier;
	ite_set_carrier_params(dev);
	spin_unlock_irqrestore(&dev->lock, flags);

	वापस 0;
पूर्ण

/* set the tx duty cycle by controlling the pulse width */
अटल पूर्णांक ite_set_tx_duty_cycle(काष्ठा rc_dev *rcdev, u32 duty_cycle)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा ite_dev *dev = rcdev->priv;

	spin_lock_irqsave(&dev->lock, flags);
	dev->tx_duty_cycle = duty_cycle;
	ite_set_carrier_params(dev);
	spin_unlock_irqrestore(&dev->lock, flags);

	वापस 0;
पूर्ण

/* transmit out IR pulses; what you get here is a batch of alternating
 * pulse/space/pulse/space lengths that we should ग_लिखो out completely through
 * the FIFO, blocking on a full FIFO */
अटल पूर्णांक ite_tx_ir(काष्ठा rc_dev *rcdev, अचिन्हित *txbuf, अचिन्हित n)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा ite_dev *dev = rcdev->priv;
	bool is_pulse = false;
	पूर्णांक reमुख्यing_us, fअगरo_avail, fअगरo_reमुख्यing, last_idx = 0;
	पूर्णांक max_rle_us, next_rle_us;
	पूर्णांक ret = n;
	u8 last_sent[ITE_TX_FIFO_LEN];
	u8 val;

	/* clear the array just in हाल */
	स_रखो(last_sent, 0, माप(last_sent));

	spin_lock_irqsave(&dev->lock, flags);

	/* let everybody know we're now transmitting */
	dev->transmitting = true;

	/* and set the carrier values क्रम transmission */
	ite_set_carrier_params(dev);

	/* calculate how much समय we can send in one byte */
	max_rle_us =
	    (ITE_BAUDRATE_DIVISOR * sample_period *
	     ITE_TX_MAX_RLE) / 1000;

	/* disable the receiver */
	dev->params->disable_rx(dev);

	/* this is where we'll begin filling in the FIFO, until it's full.
	 * then we'll just activate the पूर्णांकerrupt, रुको क्रम it to wake us up
	 * again, disable it, जारी filling the FIFO... until everything
	 * has been pushed out */
	fअगरo_avail = ITE_TX_FIFO_LEN - dev->params->get_tx_used_slots(dev);

	जबतक (n > 0) अणु
		/* transmit the next sample */
		is_pulse = !is_pulse;
		reमुख्यing_us = *(txbuf++);
		n--;

		dev_dbg(&dev->rdev->dev, "%s: %d\n",
			is_pulse ? "pulse" : "space", reमुख्यing_us);

		/* repeat जबतक the pulse is non-zero length */
		जबतक (reमुख्यing_us > 0) अणु
			अगर (reमुख्यing_us > max_rle_us)
				next_rle_us = max_rle_us;

			अन्यथा
				next_rle_us = reमुख्यing_us;

			reमुख्यing_us -= next_rle_us;

			/* check what's the length we have to pump out */
			val = (ITE_TX_MAX_RLE * next_rle_us) / max_rle_us;

			/* put it पूर्णांकo the sent buffer */
			last_sent[last_idx++] = val;
			last_idx &= (ITE_TX_FIFO_LEN);

			/* encode it क्रम 7 bits */
			val = (val - 1) & ITE_TX_RLE_MASK;

			/* take पूर्णांकo account pulse/space prefix */
			अगर (is_pulse)
				val |= ITE_TX_PULSE;

			अन्यथा
				val |= ITE_TX_SPACE;

			/*
			 * अगर we get to 0 available, पढ़ो again, just in हाल
			 * some other slot got मुक्तd
			 */
			अगर (fअगरo_avail <= 0)
				fअगरo_avail = ITE_TX_FIFO_LEN - dev->params->get_tx_used_slots(dev);

			/* अगर it's still full */
			अगर (fअगरo_avail <= 0) अणु
				/* enable the tx पूर्णांकerrupt */
				dev->params->enable_tx_पूर्णांकerrupt(dev);

				/* drop the spinlock */
				spin_unlock_irqrestore(&dev->lock, flags);

				/* रुको क्रम the FIFO to empty enough */
				रुको_event_पूर्णांकerruptible(dev->tx_queue,
					(fअगरo_avail = ITE_TX_FIFO_LEN - dev->params->get_tx_used_slots(dev)) >= 8);

				/* get the spinlock again */
				spin_lock_irqsave(&dev->lock, flags);

				/* disable the tx पूर्णांकerrupt again. */
				dev->params->disable_tx_पूर्णांकerrupt(dev);
			पूर्ण

			/* now send the byte through the FIFO */
			dev->params->put_tx_byte(dev, val);
			fअगरo_avail--;
		पूर्ण
	पूर्ण

	/* रुको and करोn't वापस until the whole FIFO has been sent out;
	 * otherwise we could configure the RX carrier params instead of the
	 * TX ones जबतक the transmission is still being perक्रमmed! */
	fअगरo_reमुख्यing = dev->params->get_tx_used_slots(dev);
	reमुख्यing_us = 0;
	जबतक (fअगरo_reमुख्यing > 0) अणु
		fअगरo_reमुख्यing--;
		last_idx--;
		last_idx &= (ITE_TX_FIFO_LEN - 1);
		reमुख्यing_us += last_sent[last_idx];
	पूर्ण
	reमुख्यing_us = (reमुख्यing_us * max_rle_us) / (ITE_TX_MAX_RLE);

	/* drop the spinlock जबतक we sleep */
	spin_unlock_irqrestore(&dev->lock, flags);

	/* sleep reमुख्यing_us microseconds */
	mdelay(DIV_ROUND_UP(reमुख्यing_us, 1000));

	/* reacquire the spinlock */
	spin_lock_irqsave(&dev->lock, flags);

	/* now we're not transmitting anymore */
	dev->transmitting = false;

	/* and set the carrier values क्रम reception */
	ite_set_carrier_params(dev);

	/* re-enable the receiver */
	dev->params->enable_rx(dev);

	/* notअगरy transmission end */
	wake_up_पूर्णांकerruptible(&dev->tx_ended);

	spin_unlock_irqrestore(&dev->lock, flags);

	वापस ret;
पूर्ण

/* idle the receiver अगर needed */
अटल व्योम ite_s_idle(काष्ठा rc_dev *rcdev, bool enable)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा ite_dev *dev = rcdev->priv;

	अगर (enable) अणु
		spin_lock_irqsave(&dev->lock, flags);
		dev->params->idle_rx(dev);
		spin_unlock_irqrestore(&dev->lock, flags);
	पूर्ण
पूर्ण


/* IT8712F HW-specअगरic functions */

/* retrieve a biपंचांगask of the current causes क्रम a pending पूर्णांकerrupt; this may
 * be composed of ITE_IRQ_TX_FIFO, ITE_IRQ_RX_FIFO and ITE_IRQ_RX_FIFO_OVERRUN
 * */
अटल पूर्णांक it87_get_irq_causes(काष्ठा ite_dev *dev)
अणु
	u8 अगरlags;
	पूर्णांक ret = 0;

	/* पढ़ो the पूर्णांकerrupt flags */
	अगरlags = inb(dev->cir_addr + IT87_IIR) & IT87_II;

	चयन (अगरlags) अणु
	हाल IT87_II_RXDS:
		ret = ITE_IRQ_RX_FIFO;
		अवरोध;
	हाल IT87_II_RXFO:
		ret = ITE_IRQ_RX_FIFO_OVERRUN;
		अवरोध;
	हाल IT87_II_TXLDL:
		ret = ITE_IRQ_TX_FIFO;
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

/* set the carrier parameters; to be called with the spinlock held */
अटल व्योम it87_set_carrier_params(काष्ठा ite_dev *dev, bool high_freq,
				    bool use_demodulator,
				    u8 carrier_freq_bits, u8 allowance_bits,
				    u8 pulse_width_bits)
अणु
	u8 val;

	/* program the RCR रेजिस्टर */
	val = inb(dev->cir_addr + IT87_RCR)
		& ~(IT87_HCFS | IT87_RXEND | IT87_RXDCR);

	अगर (high_freq)
		val |= IT87_HCFS;

	अगर (use_demodulator)
		val |= IT87_RXEND;

	val |= allowance_bits;

	outb(val, dev->cir_addr + IT87_RCR);

	/* program the TCR2 रेजिस्टर */
	outb((carrier_freq_bits << IT87_CFQ_SHIFT) | pulse_width_bits,
		dev->cir_addr + IT87_TCR2);
पूर्ण

/* पढ़ो up to buf_size bytes from the RX FIFO; to be called with the spinlock
 * held */
अटल पूर्णांक it87_get_rx_bytes(काष्ठा ite_dev *dev, u8 * buf, पूर्णांक buf_size)
अणु
	पूर्णांक fअगरo, पढ़ो = 0;

	/* पढ़ो how many bytes are still in the FIFO */
	fअगरo = inb(dev->cir_addr + IT87_RSR) & IT87_RXFBC;

	जबतक (fअगरo > 0 && buf_size > 0) अणु
		*(buf++) = inb(dev->cir_addr + IT87_DR);
		fअगरo--;
		पढ़ो++;
		buf_size--;
	पूर्ण

	वापस पढ़ो;
पूर्ण

/* वापस how many bytes are still in the FIFO; this will be called
 * with the device spinlock NOT HELD जबतक रुकोing क्रम the TX FIFO to get
 * empty; let's expect this won't be a problem */
अटल पूर्णांक it87_get_tx_used_slots(काष्ठा ite_dev *dev)
अणु
	वापस inb(dev->cir_addr + IT87_TSR) & IT87_TXFBC;
पूर्ण

/* put a byte to the TX fअगरo; this should be called with the spinlock held */
अटल व्योम it87_put_tx_byte(काष्ठा ite_dev *dev, u8 value)
अणु
	outb(value, dev->cir_addr + IT87_DR);
पूर्ण

/* idle the receiver so that we won't receive samples until another
  pulse is detected; this must be called with the device spinlock held */
अटल व्योम it87_idle_rx(काष्ठा ite_dev *dev)
अणु
	/* disable streaming by clearing RXACT writing it as 1 */
	outb(inb(dev->cir_addr + IT87_RCR) | IT87_RXACT,
		dev->cir_addr + IT87_RCR);

	/* clear the FIFO */
	outb(inb(dev->cir_addr + IT87_TCR1) | IT87_FIFOCLR,
		dev->cir_addr + IT87_TCR1);
पूर्ण

/* disable the receiver; this must be called with the device spinlock held */
अटल व्योम it87_disable_rx(काष्ठा ite_dev *dev)
अणु
	/* disable the receiver पूर्णांकerrupts */
	outb(inb(dev->cir_addr + IT87_IER) & ~(IT87_RDAIE | IT87_RFOIE),
		dev->cir_addr + IT87_IER);

	/* disable the receiver */
	outb(inb(dev->cir_addr + IT87_RCR) & ~IT87_RXEN,
		dev->cir_addr + IT87_RCR);

	/* clear the FIFO and RXACT (actually RXACT should have been cleared
	* in the previous outb() call) */
	it87_idle_rx(dev);
पूर्ण

/* enable the receiver; this must be called with the device spinlock held */
अटल व्योम it87_enable_rx(काष्ठा ite_dev *dev)
अणु
	/* enable the receiver by setting RXEN */
	outb(inb(dev->cir_addr + IT87_RCR) | IT87_RXEN,
		dev->cir_addr + IT87_RCR);

	/* just prepare it to idle क्रम the next reception */
	it87_idle_rx(dev);

	/* enable the receiver पूर्णांकerrupts and master enable flag */
	outb(inb(dev->cir_addr + IT87_IER) | IT87_RDAIE | IT87_RFOIE | IT87_IEC,
		dev->cir_addr + IT87_IER);
पूर्ण

/* disable the transmitter पूर्णांकerrupt; this must be called with the device
 * spinlock held */
अटल व्योम it87_disable_tx_पूर्णांकerrupt(काष्ठा ite_dev *dev)
अणु
	/* disable the transmitter पूर्णांकerrupts */
	outb(inb(dev->cir_addr + IT87_IER) & ~IT87_TLDLIE,
		dev->cir_addr + IT87_IER);
पूर्ण

/* enable the transmitter पूर्णांकerrupt; this must be called with the device
 * spinlock held */
अटल व्योम it87_enable_tx_पूर्णांकerrupt(काष्ठा ite_dev *dev)
अणु
	/* enable the transmitter पूर्णांकerrupts and master enable flag */
	outb(inb(dev->cir_addr + IT87_IER) | IT87_TLDLIE | IT87_IEC,
		dev->cir_addr + IT87_IER);
पूर्ण

/* disable the device; this must be called with the device spinlock held */
अटल व्योम it87_disable(काष्ठा ite_dev *dev)
अणु
	/* clear out all पूर्णांकerrupt enable flags */
	outb(inb(dev->cir_addr + IT87_IER) &
		~(IT87_IEC | IT87_RFOIE | IT87_RDAIE | IT87_TLDLIE),
		dev->cir_addr + IT87_IER);

	/* disable the receiver */
	it87_disable_rx(dev);

	/* erase the FIFO */
	outb(IT87_FIFOCLR | inb(dev->cir_addr + IT87_TCR1),
		dev->cir_addr + IT87_TCR1);
पूर्ण

/* initialize the hardware */
अटल व्योम it87_init_hardware(काष्ठा ite_dev *dev)
अणु
	/* enable just the baud rate भागisor रेजिस्टर,
	disabling all the पूर्णांकerrupts at the same समय */
	outb((inb(dev->cir_addr + IT87_IER) &
		~(IT87_IEC | IT87_RFOIE | IT87_RDAIE | IT87_TLDLIE)) | IT87_BR,
		dev->cir_addr + IT87_IER);

	/* ग_लिखो out the baud rate भागisor */
	outb(ITE_BAUDRATE_DIVISOR & 0xff, dev->cir_addr + IT87_BDLR);
	outb((ITE_BAUDRATE_DIVISOR >> 8) & 0xff, dev->cir_addr + IT87_BDHR);

	/* disable the baud rate भागisor रेजिस्टर again */
	outb(inb(dev->cir_addr + IT87_IER) & ~IT87_BR,
		dev->cir_addr + IT87_IER);

	/* program the RCR रेजिस्टर शेषs */
	outb(ITE_RXDCR_DEFAULT, dev->cir_addr + IT87_RCR);

	/* program the TCR1 रेजिस्टर */
	outb(IT87_TXMPM_DEFAULT | IT87_TXENDF | IT87_TXRLE
		| IT87_FIFOTL_DEFAULT | IT87_FIFOCLR,
		dev->cir_addr + IT87_TCR1);

	/* program the carrier parameters */
	ite_set_carrier_params(dev);
पूर्ण

/* IT8512F on ITE8708 HW-specअगरic functions */

/* retrieve a biपंचांगask of the current causes क्रम a pending पूर्णांकerrupt; this may
 * be composed of ITE_IRQ_TX_FIFO, ITE_IRQ_RX_FIFO and ITE_IRQ_RX_FIFO_OVERRUN
 * */
अटल पूर्णांक it8708_get_irq_causes(काष्ठा ite_dev *dev)
अणु
	u8 अगरlags;
	पूर्णांक ret = 0;

	/* पढ़ो the पूर्णांकerrupt flags */
	अगरlags = inb(dev->cir_addr + IT8708_C0IIR);

	अगर (अगरlags & IT85_TLDLI)
		ret |= ITE_IRQ_TX_FIFO;
	अगर (अगरlags & IT85_RDAI)
		ret |= ITE_IRQ_RX_FIFO;
	अगर (अगरlags & IT85_RFOI)
		ret |= ITE_IRQ_RX_FIFO_OVERRUN;

	वापस ret;
पूर्ण

/* set the carrier parameters; to be called with the spinlock held */
अटल व्योम it8708_set_carrier_params(काष्ठा ite_dev *dev, bool high_freq,
				      bool use_demodulator,
				      u8 carrier_freq_bits, u8 allowance_bits,
				      u8 pulse_width_bits)
अणु
	u8 val;

	/* program the C0CFR रेजिस्टर, with HRAE=1 */
	outb(inb(dev->cir_addr + IT8708_BANKSEL) | IT8708_HRAE,
		dev->cir_addr + IT8708_BANKSEL);

	val = (inb(dev->cir_addr + IT8708_C0CFR)
		& ~(IT85_HCFS | IT85_CFQ)) | carrier_freq_bits;

	अगर (high_freq)
		val |= IT85_HCFS;

	outb(val, dev->cir_addr + IT8708_C0CFR);

	outb(inb(dev->cir_addr + IT8708_BANKSEL) & ~IT8708_HRAE,
		   dev->cir_addr + IT8708_BANKSEL);

	/* program the C0RCR रेजिस्टर */
	val = inb(dev->cir_addr + IT8708_C0RCR)
		& ~(IT85_RXEND | IT85_RXDCR);

	अगर (use_demodulator)
		val |= IT85_RXEND;

	val |= allowance_bits;

	outb(val, dev->cir_addr + IT8708_C0RCR);

	/* program the C0TCR रेजिस्टर */
	val = inb(dev->cir_addr + IT8708_C0TCR) & ~IT85_TXMPW;
	val |= pulse_width_bits;
	outb(val, dev->cir_addr + IT8708_C0TCR);
पूर्ण

/* पढ़ो up to buf_size bytes from the RX FIFO; to be called with the spinlock
 * held */
अटल पूर्णांक it8708_get_rx_bytes(काष्ठा ite_dev *dev, u8 * buf, पूर्णांक buf_size)
अणु
	पूर्णांक fअगरo, पढ़ो = 0;

	/* पढ़ो how many bytes are still in the FIFO */
	fअगरo = inb(dev->cir_addr + IT8708_C0RFSR) & IT85_RXFBC;

	जबतक (fअगरo > 0 && buf_size > 0) अणु
		*(buf++) = inb(dev->cir_addr + IT8708_C0DR);
		fअगरo--;
		पढ़ो++;
		buf_size--;
	पूर्ण

	वापस पढ़ो;
पूर्ण

/* वापस how many bytes are still in the FIFO; this will be called
 * with the device spinlock NOT HELD जबतक रुकोing क्रम the TX FIFO to get
 * empty; let's expect this won't be a problem */
अटल पूर्णांक it8708_get_tx_used_slots(काष्ठा ite_dev *dev)
अणु
	वापस inb(dev->cir_addr + IT8708_C0TFSR) & IT85_TXFBC;
पूर्ण

/* put a byte to the TX fअगरo; this should be called with the spinlock held */
अटल व्योम it8708_put_tx_byte(काष्ठा ite_dev *dev, u8 value)
अणु
	outb(value, dev->cir_addr + IT8708_C0DR);
पूर्ण

/* idle the receiver so that we won't receive samples until another
  pulse is detected; this must be called with the device spinlock held */
अटल व्योम it8708_idle_rx(काष्ठा ite_dev *dev)
अणु
	/* disable streaming by clearing RXACT writing it as 1 */
	outb(inb(dev->cir_addr + IT8708_C0RCR) | IT85_RXACT,
		dev->cir_addr + IT8708_C0RCR);

	/* clear the FIFO */
	outb(inb(dev->cir_addr + IT8708_C0MSTCR) | IT85_FIFOCLR,
		dev->cir_addr + IT8708_C0MSTCR);
पूर्ण

/* disable the receiver; this must be called with the device spinlock held */
अटल व्योम it8708_disable_rx(काष्ठा ite_dev *dev)
अणु
	/* disable the receiver पूर्णांकerrupts */
	outb(inb(dev->cir_addr + IT8708_C0IER) &
		~(IT85_RDAIE | IT85_RFOIE),
		dev->cir_addr + IT8708_C0IER);

	/* disable the receiver */
	outb(inb(dev->cir_addr + IT8708_C0RCR) & ~IT85_RXEN,
		dev->cir_addr + IT8708_C0RCR);

	/* clear the FIFO and RXACT (actually RXACT should have been cleared
	 * in the previous outb() call) */
	it8708_idle_rx(dev);
पूर्ण

/* enable the receiver; this must be called with the device spinlock held */
अटल व्योम it8708_enable_rx(काष्ठा ite_dev *dev)
अणु
	/* enable the receiver by setting RXEN */
	outb(inb(dev->cir_addr + IT8708_C0RCR) | IT85_RXEN,
		dev->cir_addr + IT8708_C0RCR);

	/* just prepare it to idle क्रम the next reception */
	it8708_idle_rx(dev);

	/* enable the receiver पूर्णांकerrupts and master enable flag */
	outb(inb(dev->cir_addr + IT8708_C0IER)
		|IT85_RDAIE | IT85_RFOIE | IT85_IEC,
		dev->cir_addr + IT8708_C0IER);
पूर्ण

/* disable the transmitter पूर्णांकerrupt; this must be called with the device
 * spinlock held */
अटल व्योम it8708_disable_tx_पूर्णांकerrupt(काष्ठा ite_dev *dev)
अणु
	/* disable the transmitter पूर्णांकerrupts */
	outb(inb(dev->cir_addr + IT8708_C0IER) & ~IT85_TLDLIE,
		dev->cir_addr + IT8708_C0IER);
पूर्ण

/* enable the transmitter पूर्णांकerrupt; this must be called with the device
 * spinlock held */
अटल व्योम it8708_enable_tx_पूर्णांकerrupt(काष्ठा ite_dev *dev)
अणु
	/* enable the transmitter पूर्णांकerrupts and master enable flag */
	outb(inb(dev->cir_addr + IT8708_C0IER)
		|IT85_TLDLIE | IT85_IEC,
		dev->cir_addr + IT8708_C0IER);
पूर्ण

/* disable the device; this must be called with the device spinlock held */
अटल व्योम it8708_disable(काष्ठा ite_dev *dev)
अणु
	/* clear out all पूर्णांकerrupt enable flags */
	outb(inb(dev->cir_addr + IT8708_C0IER) &
		~(IT85_IEC | IT85_RFOIE | IT85_RDAIE | IT85_TLDLIE),
		dev->cir_addr + IT8708_C0IER);

	/* disable the receiver */
	it8708_disable_rx(dev);

	/* erase the FIFO */
	outb(IT85_FIFOCLR | inb(dev->cir_addr + IT8708_C0MSTCR),
		dev->cir_addr + IT8708_C0MSTCR);
पूर्ण

/* initialize the hardware */
अटल व्योम it8708_init_hardware(काष्ठा ite_dev *dev)
अणु
	/* disable all the पूर्णांकerrupts */
	outb(inb(dev->cir_addr + IT8708_C0IER) &
		~(IT85_IEC | IT85_RFOIE | IT85_RDAIE | IT85_TLDLIE),
		dev->cir_addr + IT8708_C0IER);

	/* program the baud rate भागisor */
	outb(inb(dev->cir_addr + IT8708_BANKSEL) | IT8708_HRAE,
		dev->cir_addr + IT8708_BANKSEL);

	outb(ITE_BAUDRATE_DIVISOR & 0xff, dev->cir_addr + IT8708_C0BDLR);
	outb((ITE_BAUDRATE_DIVISOR >> 8) & 0xff,
		   dev->cir_addr + IT8708_C0BDHR);

	outb(inb(dev->cir_addr + IT8708_BANKSEL) & ~IT8708_HRAE,
		   dev->cir_addr + IT8708_BANKSEL);

	/* program the C0MSTCR रेजिस्टर शेषs */
	outb((inb(dev->cir_addr + IT8708_C0MSTCR) &
			~(IT85_ILSEL | IT85_ILE | IT85_FIFOTL |
			  IT85_FIFOCLR | IT85_RESET)) |
		       IT85_FIFOTL_DEFAULT,
		       dev->cir_addr + IT8708_C0MSTCR);

	/* program the C0RCR रेजिस्टर शेषs */
	outb((inb(dev->cir_addr + IT8708_C0RCR) &
			~(IT85_RXEN | IT85_RDWOS | IT85_RXEND |
			  IT85_RXACT | IT85_RXDCR)) |
		       ITE_RXDCR_DEFAULT,
		       dev->cir_addr + IT8708_C0RCR);

	/* program the C0TCR रेजिस्टर शेषs */
	outb((inb(dev->cir_addr + IT8708_C0TCR) &
			~(IT85_TXMPM | IT85_TXMPW))
		       |IT85_TXRLE | IT85_TXENDF |
		       IT85_TXMPM_DEFAULT | IT85_TXMPW_DEFAULT,
		       dev->cir_addr + IT8708_C0TCR);

	/* program the carrier parameters */
	ite_set_carrier_params(dev);
पूर्ण

/* IT8512F on ITE8709 HW-specअगरic functions */

/* पढ़ो a byte from the SRAM module */
अटल अंतरभूत u8 it8709_rm(काष्ठा ite_dev *dev, पूर्णांक index)
अणु
	outb(index, dev->cir_addr + IT8709_RAM_IDX);
	वापस inb(dev->cir_addr + IT8709_RAM_VAL);
पूर्ण

/* ग_लिखो a byte to the SRAM module */
अटल अंतरभूत व्योम it8709_wm(काष्ठा ite_dev *dev, u8 val, पूर्णांक index)
अणु
	outb(index, dev->cir_addr + IT8709_RAM_IDX);
	outb(val, dev->cir_addr + IT8709_RAM_VAL);
पूर्ण

अटल व्योम it8709_रुको(काष्ठा ite_dev *dev)
अणु
	पूर्णांक i = 0;
	/*
	 * loop until device tells it's पढ़ोy to जारी
	 * iterations count is usually ~750 but can someबार achieve 13000
	 */
	क्रम (i = 0; i < 15000; i++) अणु
		udelay(2);
		अगर (it8709_rm(dev, IT8709_MODE) == IT8709_IDLE)
			अवरोध;
	पूर्ण
पूर्ण

/* पढ़ो the value of a CIR रेजिस्टर */
अटल u8 it8709_rr(काष्ठा ite_dev *dev, पूर्णांक index)
अणु
	/* just रुको in हाल the previous access was a ग_लिखो */
	it8709_रुको(dev);
	it8709_wm(dev, index, IT8709_REG_IDX);
	it8709_wm(dev, IT8709_READ, IT8709_MODE);

	/* रुको क्रम the पढ़ो data to be available */
	it8709_रुको(dev);

	/* वापस the पढ़ो value */
	वापस it8709_rm(dev, IT8709_REG_VAL);
पूर्ण

/* ग_लिखो the value of a CIR रेजिस्टर */
अटल व्योम it8709_wr(काष्ठा ite_dev *dev, u8 val, पूर्णांक index)
अणु
	/* we रुको beक्रमe writing, and not afterwards, since this allows us to
	 * pipeline the host CPU with the microcontroller */
	it8709_रुको(dev);
	it8709_wm(dev, val, IT8709_REG_VAL);
	it8709_wm(dev, index, IT8709_REG_IDX);
	it8709_wm(dev, IT8709_WRITE, IT8709_MODE);
पूर्ण

/* retrieve a biपंचांगask of the current causes क्रम a pending पूर्णांकerrupt; this may
 * be composed of ITE_IRQ_TX_FIFO, ITE_IRQ_RX_FIFO and ITE_IRQ_RX_FIFO_OVERRUN
 * */
अटल पूर्णांक it8709_get_irq_causes(काष्ठा ite_dev *dev)
अणु
	u8 अगरlags;
	पूर्णांक ret = 0;

	/* पढ़ो the पूर्णांकerrupt flags */
	अगरlags = it8709_rm(dev, IT8709_IIR);

	अगर (अगरlags & IT85_TLDLI)
		ret |= ITE_IRQ_TX_FIFO;
	अगर (अगरlags & IT85_RDAI)
		ret |= ITE_IRQ_RX_FIFO;
	अगर (अगरlags & IT85_RFOI)
		ret |= ITE_IRQ_RX_FIFO_OVERRUN;

	वापस ret;
पूर्ण

/* set the carrier parameters; to be called with the spinlock held */
अटल व्योम it8709_set_carrier_params(काष्ठा ite_dev *dev, bool high_freq,
				      bool use_demodulator,
				      u8 carrier_freq_bits, u8 allowance_bits,
				      u8 pulse_width_bits)
अणु
	u8 val;

	val = (it8709_rr(dev, IT85_C0CFR)
		     &~(IT85_HCFS | IT85_CFQ)) |
	    carrier_freq_bits;

	अगर (high_freq)
		val |= IT85_HCFS;

	it8709_wr(dev, val, IT85_C0CFR);

	/* program the C0RCR रेजिस्टर */
	val = it8709_rr(dev, IT85_C0RCR)
		& ~(IT85_RXEND | IT85_RXDCR);

	अगर (use_demodulator)
		val |= IT85_RXEND;

	val |= allowance_bits;

	it8709_wr(dev, val, IT85_C0RCR);

	/* program the C0TCR रेजिस्टर */
	val = it8709_rr(dev, IT85_C0TCR) & ~IT85_TXMPW;
	val |= pulse_width_bits;
	it8709_wr(dev, val, IT85_C0TCR);
पूर्ण

/* पढ़ो up to buf_size bytes from the RX FIFO; to be called with the spinlock
 * held */
अटल पूर्णांक it8709_get_rx_bytes(काष्ठा ite_dev *dev, u8 * buf, पूर्णांक buf_size)
अणु
	पूर्णांक fअगरo, पढ़ो = 0;

	/* पढ़ो how many bytes are still in the FIFO */
	fअगरo = it8709_rm(dev, IT8709_RFSR) & IT85_RXFBC;

	जबतक (fअगरo > 0 && buf_size > 0) अणु
		*(buf++) = it8709_rm(dev, IT8709_FIFO + पढ़ो);
		fअगरo--;
		पढ़ो++;
		buf_size--;
	पूर्ण

	/* 'clear' the FIFO by setting the writing index to 0; this is
	 * completely bound to be racy, but we can't help it, since it's a
	 * limitation of the protocol */
	it8709_wm(dev, 0, IT8709_RFSR);

	वापस पढ़ो;
पूर्ण

/* वापस how many bytes are still in the FIFO; this will be called
 * with the device spinlock NOT HELD जबतक रुकोing क्रम the TX FIFO to get
 * empty; let's expect this won't be a problem */
अटल पूर्णांक it8709_get_tx_used_slots(काष्ठा ite_dev *dev)
अणु
	वापस it8709_rr(dev, IT85_C0TFSR) & IT85_TXFBC;
पूर्ण

/* put a byte to the TX fअगरo; this should be called with the spinlock held */
अटल व्योम it8709_put_tx_byte(काष्ठा ite_dev *dev, u8 value)
अणु
	it8709_wr(dev, value, IT85_C0DR);
पूर्ण

/* idle the receiver so that we won't receive samples until another
  pulse is detected; this must be called with the device spinlock held */
अटल व्योम it8709_idle_rx(काष्ठा ite_dev *dev)
अणु
	/* disable streaming by clearing RXACT writing it as 1 */
	it8709_wr(dev, it8709_rr(dev, IT85_C0RCR) | IT85_RXACT,
			    IT85_C0RCR);

	/* clear the FIFO */
	it8709_wr(dev, it8709_rr(dev, IT85_C0MSTCR) | IT85_FIFOCLR,
			    IT85_C0MSTCR);
पूर्ण

/* disable the receiver; this must be called with the device spinlock held */
अटल व्योम it8709_disable_rx(काष्ठा ite_dev *dev)
अणु
	/* disable the receiver पूर्णांकerrupts */
	it8709_wr(dev, it8709_rr(dev, IT85_C0IER) &
			    ~(IT85_RDAIE | IT85_RFOIE),
			    IT85_C0IER);

	/* disable the receiver */
	it8709_wr(dev, it8709_rr(dev, IT85_C0RCR) & ~IT85_RXEN,
			    IT85_C0RCR);

	/* clear the FIFO and RXACT (actually RXACT should have been cleared
	 * in the previous it8709_wr(dev, ) call) */
	it8709_idle_rx(dev);
पूर्ण

/* enable the receiver; this must be called with the device spinlock held */
अटल व्योम it8709_enable_rx(काष्ठा ite_dev *dev)
अणु
	/* enable the receiver by setting RXEN */
	it8709_wr(dev, it8709_rr(dev, IT85_C0RCR) | IT85_RXEN,
			    IT85_C0RCR);

	/* just prepare it to idle क्रम the next reception */
	it8709_idle_rx(dev);

	/* enable the receiver पूर्णांकerrupts and master enable flag */
	it8709_wr(dev, it8709_rr(dev, IT85_C0IER)
			    |IT85_RDAIE | IT85_RFOIE | IT85_IEC,
			    IT85_C0IER);
पूर्ण

/* disable the transmitter पूर्णांकerrupt; this must be called with the device
 * spinlock held */
अटल व्योम it8709_disable_tx_पूर्णांकerrupt(काष्ठा ite_dev *dev)
अणु
	/* disable the transmitter पूर्णांकerrupts */
	it8709_wr(dev, it8709_rr(dev, IT85_C0IER) & ~IT85_TLDLIE,
			    IT85_C0IER);
पूर्ण

/* enable the transmitter पूर्णांकerrupt; this must be called with the device
 * spinlock held */
अटल व्योम it8709_enable_tx_पूर्णांकerrupt(काष्ठा ite_dev *dev)
अणु
	/* enable the transmitter पूर्णांकerrupts and master enable flag */
	it8709_wr(dev, it8709_rr(dev, IT85_C0IER)
			    |IT85_TLDLIE | IT85_IEC,
			    IT85_C0IER);
पूर्ण

/* disable the device; this must be called with the device spinlock held */
अटल व्योम it8709_disable(काष्ठा ite_dev *dev)
अणु
	/* clear out all पूर्णांकerrupt enable flags */
	it8709_wr(dev, it8709_rr(dev, IT85_C0IER) &
			~(IT85_IEC | IT85_RFOIE | IT85_RDAIE | IT85_TLDLIE),
		  IT85_C0IER);

	/* disable the receiver */
	it8709_disable_rx(dev);

	/* erase the FIFO */
	it8709_wr(dev, IT85_FIFOCLR | it8709_rr(dev, IT85_C0MSTCR),
			    IT85_C0MSTCR);
पूर्ण

/* initialize the hardware */
अटल व्योम it8709_init_hardware(काष्ठा ite_dev *dev)
अणु
	/* disable all the पूर्णांकerrupts */
	it8709_wr(dev, it8709_rr(dev, IT85_C0IER) &
			~(IT85_IEC | IT85_RFOIE | IT85_RDAIE | IT85_TLDLIE),
		  IT85_C0IER);

	/* program the baud rate भागisor */
	it8709_wr(dev, ITE_BAUDRATE_DIVISOR & 0xff, IT85_C0BDLR);
	it8709_wr(dev, (ITE_BAUDRATE_DIVISOR >> 8) & 0xff,
			IT85_C0BDHR);

	/* program the C0MSTCR रेजिस्टर शेषs */
	it8709_wr(dev, (it8709_rr(dev, IT85_C0MSTCR) &
			~(IT85_ILSEL | IT85_ILE | IT85_FIFOTL
			  | IT85_FIFOCLR | IT85_RESET)) | IT85_FIFOTL_DEFAULT,
		  IT85_C0MSTCR);

	/* program the C0RCR रेजिस्टर शेषs */
	it8709_wr(dev, (it8709_rr(dev, IT85_C0RCR) &
			~(IT85_RXEN | IT85_RDWOS | IT85_RXEND | IT85_RXACT
			  | IT85_RXDCR)) | ITE_RXDCR_DEFAULT,
		  IT85_C0RCR);

	/* program the C0TCR रेजिस्टर शेषs */
	it8709_wr(dev, (it8709_rr(dev, IT85_C0TCR) & ~(IT85_TXMPM | IT85_TXMPW))
			| IT85_TXRLE | IT85_TXENDF | IT85_TXMPM_DEFAULT
			| IT85_TXMPW_DEFAULT,
		  IT85_C0TCR);

	/* program the carrier parameters */
	ite_set_carrier_params(dev);
पूर्ण


/* generic hardware setup/tearकरोwn code */

/* activate the device क्रम use */
अटल पूर्णांक ite_खोलो(काष्ठा rc_dev *rcdev)
अणु
	काष्ठा ite_dev *dev = rcdev->priv;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&dev->lock, flags);

	/* enable the receiver */
	dev->params->enable_rx(dev);

	spin_unlock_irqrestore(&dev->lock, flags);

	वापस 0;
पूर्ण

/* deactivate the device क्रम use */
अटल व्योम ite_बंद(काष्ठा rc_dev *rcdev)
अणु
	काष्ठा ite_dev *dev = rcdev->priv;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&dev->lock, flags);

	/* रुको क्रम any transmission to end */
	spin_unlock_irqrestore(&dev->lock, flags);
	रुको_event_पूर्णांकerruptible(dev->tx_ended, !dev->transmitting);
	spin_lock_irqsave(&dev->lock, flags);

	dev->params->disable(dev);

	spin_unlock_irqrestore(&dev->lock, flags);
पूर्ण

/* supported models and their parameters */
अटल स्थिर काष्ठा ite_dev_params ite_dev_descs[] = अणु
	अणु	/* 0: ITE8704 */
	       .model = "ITE8704 CIR transceiver",
	       .io_region_size = IT87_IOREG_LENGTH,
	       .io_rsrc_no = 0,

		/* operations */
	       .get_irq_causes = it87_get_irq_causes,
	       .enable_rx = it87_enable_rx,
	       .idle_rx = it87_idle_rx,
	       .disable_rx = it87_idle_rx,
	       .get_rx_bytes = it87_get_rx_bytes,
	       .enable_tx_पूर्णांकerrupt = it87_enable_tx_पूर्णांकerrupt,
	       .disable_tx_पूर्णांकerrupt = it87_disable_tx_पूर्णांकerrupt,
	       .get_tx_used_slots = it87_get_tx_used_slots,
	       .put_tx_byte = it87_put_tx_byte,
	       .disable = it87_disable,
	       .init_hardware = it87_init_hardware,
	       .set_carrier_params = it87_set_carrier_params,
	       पूर्ण,
	अणु	/* 1: ITE8713 */
	       .model = "ITE8713 CIR transceiver",
	       .io_region_size = IT87_IOREG_LENGTH,
	       .io_rsrc_no = 0,

		/* operations */
	       .get_irq_causes = it87_get_irq_causes,
	       .enable_rx = it87_enable_rx,
	       .idle_rx = it87_idle_rx,
	       .disable_rx = it87_idle_rx,
	       .get_rx_bytes = it87_get_rx_bytes,
	       .enable_tx_पूर्णांकerrupt = it87_enable_tx_पूर्णांकerrupt,
	       .disable_tx_पूर्णांकerrupt = it87_disable_tx_पूर्णांकerrupt,
	       .get_tx_used_slots = it87_get_tx_used_slots,
	       .put_tx_byte = it87_put_tx_byte,
	       .disable = it87_disable,
	       .init_hardware = it87_init_hardware,
	       .set_carrier_params = it87_set_carrier_params,
	       पूर्ण,
	अणु	/* 2: ITE8708 */
	       .model = "ITE8708 CIR transceiver",
	       .io_region_size = IT8708_IOREG_LENGTH,
	       .io_rsrc_no = 0,

		/* operations */
	       .get_irq_causes = it8708_get_irq_causes,
	       .enable_rx = it8708_enable_rx,
	       .idle_rx = it8708_idle_rx,
	       .disable_rx = it8708_idle_rx,
	       .get_rx_bytes = it8708_get_rx_bytes,
	       .enable_tx_पूर्णांकerrupt = it8708_enable_tx_पूर्णांकerrupt,
	       .disable_tx_पूर्णांकerrupt =
	       it8708_disable_tx_पूर्णांकerrupt,
	       .get_tx_used_slots = it8708_get_tx_used_slots,
	       .put_tx_byte = it8708_put_tx_byte,
	       .disable = it8708_disable,
	       .init_hardware = it8708_init_hardware,
	       .set_carrier_params = it8708_set_carrier_params,
	       पूर्ण,
	अणु	/* 3: ITE8709 */
	       .model = "ITE8709 CIR transceiver",
	       .io_region_size = IT8709_IOREG_LENGTH,
	       .io_rsrc_no = 2,

		/* operations */
	       .get_irq_causes = it8709_get_irq_causes,
	       .enable_rx = it8709_enable_rx,
	       .idle_rx = it8709_idle_rx,
	       .disable_rx = it8709_idle_rx,
	       .get_rx_bytes = it8709_get_rx_bytes,
	       .enable_tx_पूर्णांकerrupt = it8709_enable_tx_पूर्णांकerrupt,
	       .disable_tx_पूर्णांकerrupt =
	       it8709_disable_tx_पूर्णांकerrupt,
	       .get_tx_used_slots = it8709_get_tx_used_slots,
	       .put_tx_byte = it8709_put_tx_byte,
	       .disable = it8709_disable,
	       .init_hardware = it8709_init_hardware,
	       .set_carrier_params = it8709_set_carrier_params,
	       पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा pnp_device_id ite_ids[] = अणु
	अणु"ITE8704", 0पूर्ण,		/* Default model */
	अणु"ITE8713", 1पूर्ण,		/* CIR found in EEEBox 1501U */
	अणु"ITE8708", 2पूर्ण,		/* Bridged IT8512 */
	अणु"ITE8709", 3पूर्ण,		/* SRAM-Bridged IT8512 */
	अणु"", 0पूर्ण,
पूर्ण;

/* allocate memory, probe hardware, and initialize everything */
अटल पूर्णांक ite_probe(काष्ठा pnp_dev *pdev, स्थिर काष्ठा pnp_device_id
		     *dev_id)
अणु
	स्थिर काष्ठा ite_dev_params *dev_desc = शून्य;
	काष्ठा ite_dev *itdev = शून्य;
	काष्ठा rc_dev *rdev = शून्य;
	पूर्णांक ret = -ENOMEM;
	पूर्णांक model_no;
	पूर्णांक io_rsrc_no;

	itdev = kzalloc(माप(काष्ठा ite_dev), GFP_KERNEL);
	अगर (!itdev)
		वापस ret;

	/* input device क्रम IR remote (and tx) */
	rdev = rc_allocate_device(RC_DRIVER_IR_RAW);
	अगर (!rdev)
		जाओ निकास_मुक्त_dev_rdev;
	itdev->rdev = rdev;

	ret = -ENODEV;

	/* get the model number */
	model_no = (पूर्णांक)dev_id->driver_data;
	dev_dbg(&pdev->dev, "Auto-detected model: %s\n",
		ite_dev_descs[model_no].model);

	अगर (model_number >= 0 && model_number < ARRAY_SIZE(ite_dev_descs)) अणु
		model_no = model_number;
		dev_info(&pdev->dev, "model has been forced to: %s",
			 ite_dev_descs[model_no].model);
	पूर्ण

	/* get the description क्रम the device */
	dev_desc = &ite_dev_descs[model_no];
	io_rsrc_no = dev_desc->io_rsrc_no;

	/* validate pnp resources */
	अगर (!pnp_port_valid(pdev, io_rsrc_no) ||
	    pnp_port_len(pdev, io_rsrc_no) < dev_desc->io_region_size) अणु
		dev_err(&pdev->dev, "IR PNP Port not valid!\n");
		जाओ निकास_मुक्त_dev_rdev;
	पूर्ण

	अगर (!pnp_irq_valid(pdev, 0)) अणु
		dev_err(&pdev->dev, "PNP IRQ not valid!\n");
		जाओ निकास_मुक्त_dev_rdev;
	पूर्ण

	/* store resource values */
	itdev->cir_addr = pnp_port_start(pdev, io_rsrc_no);
	itdev->cir_irq = pnp_irq(pdev, 0);

	/* initialize spinlocks */
	spin_lock_init(&itdev->lock);

	/* set driver data पूर्णांकo the pnp device */
	pnp_set_drvdata(pdev, itdev);
	itdev->pdev = pdev;

	/* initialize रुकोqueues क्रम transmission */
	init_रुकोqueue_head(&itdev->tx_queue);
	init_रुकोqueue_head(&itdev->tx_ended);

	/* Set model-specअगरic parameters */
	itdev->params = dev_desc;

	/* set up hardware initial state */
	itdev->tx_duty_cycle = 33;
	itdev->tx_carrier_freq = ITE_DEFAULT_CARRIER_FREQ;
	itdev->params->init_hardware(itdev);

	/* set up ir-core props */
	rdev->priv = itdev;
	rdev->dev.parent = &pdev->dev;
	rdev->allowed_protocols = RC_PROTO_BIT_ALL_IR_DECODER;
	rdev->खोलो = ite_खोलो;
	rdev->बंद = ite_बंद;
	rdev->s_idle = ite_s_idle;
	rdev->s_rx_carrier_range = ite_set_rx_carrier_range;
	/* FIFO threshold is 17 bytes, so 17 * 8 samples minimum */
	rdev->min_समयout = 17 * 8 * ITE_BAUDRATE_DIVISOR *
			    sample_period / 1000;
	rdev->समयout = IR_DEFAULT_TIMEOUT;
	rdev->max_समयout = 10 * IR_DEFAULT_TIMEOUT;
	rdev->rx_resolution = ITE_BAUDRATE_DIVISOR * sample_period / 1000;
	rdev->tx_resolution = ITE_BAUDRATE_DIVISOR * sample_period / 1000;

	/* set up transmitter related values */
	rdev->tx_ir = ite_tx_ir;
	rdev->s_tx_carrier = ite_set_tx_carrier;
	rdev->s_tx_duty_cycle = ite_set_tx_duty_cycle;

	rdev->device_name = dev_desc->model;
	rdev->input_id.bustype = BUS_HOST;
	rdev->input_id.venकरोr = PCI_VENDOR_ID_ITE;
	rdev->input_id.product = 0;
	rdev->input_id.version = 0;
	rdev->driver_name = ITE_DRIVER_NAME;
	rdev->map_name = RC_MAP_RC6_MCE;

	ret = rc_रेजिस्टर_device(rdev);
	अगर (ret)
		जाओ निकास_मुक्त_dev_rdev;

	ret = -EBUSY;
	/* now claim resources */
	अगर (!request_region(itdev->cir_addr,
				dev_desc->io_region_size, ITE_DRIVER_NAME))
		जाओ निकास_unरेजिस्टर_device;

	अगर (request_irq(itdev->cir_irq, ite_cir_isr, IRQF_SHARED,
			ITE_DRIVER_NAME, (व्योम *)itdev))
		जाओ निकास_release_cir_addr;

	वापस 0;

निकास_release_cir_addr:
	release_region(itdev->cir_addr, itdev->params->io_region_size);
निकास_unरेजिस्टर_device:
	rc_unरेजिस्टर_device(rdev);
	rdev = शून्य;
निकास_मुक्त_dev_rdev:
	rc_मुक्त_device(rdev);
	kमुक्त(itdev);

	वापस ret;
पूर्ण

अटल व्योम ite_हटाओ(काष्ठा pnp_dev *pdev)
अणु
	काष्ठा ite_dev *dev = pnp_get_drvdata(pdev);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&dev->lock, flags);

	/* disable hardware */
	dev->params->disable(dev);

	spin_unlock_irqrestore(&dev->lock, flags);

	/* मुक्त resources */
	मुक्त_irq(dev->cir_irq, dev);
	release_region(dev->cir_addr, dev->params->io_region_size);

	rc_unरेजिस्टर_device(dev->rdev);

	kमुक्त(dev);
पूर्ण

अटल पूर्णांक ite_suspend(काष्ठा pnp_dev *pdev, pm_message_t state)
अणु
	काष्ठा ite_dev *dev = pnp_get_drvdata(pdev);
	अचिन्हित दीर्घ flags;

	/* रुको क्रम any transmission to end */
	रुको_event_पूर्णांकerruptible(dev->tx_ended, !dev->transmitting);

	spin_lock_irqsave(&dev->lock, flags);

	/* disable all पूर्णांकerrupts */
	dev->params->disable(dev);

	spin_unlock_irqrestore(&dev->lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक ite_resume(काष्ठा pnp_dev *pdev)
अणु
	काष्ठा ite_dev *dev = pnp_get_drvdata(pdev);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&dev->lock, flags);

	/* reinitialize hardware config रेजिस्टरs */
	dev->params->init_hardware(dev);
	/* enable the receiver */
	dev->params->enable_rx(dev);

	spin_unlock_irqrestore(&dev->lock, flags);

	वापस 0;
पूर्ण

अटल व्योम ite_shutकरोwn(काष्ठा pnp_dev *pdev)
अणु
	काष्ठा ite_dev *dev = pnp_get_drvdata(pdev);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&dev->lock, flags);

	/* disable all पूर्णांकerrupts */
	dev->params->disable(dev);

	spin_unlock_irqrestore(&dev->lock, flags);
पूर्ण

अटल काष्ठा pnp_driver ite_driver = अणु
	.name		= ITE_DRIVER_NAME,
	.id_table	= ite_ids,
	.probe		= ite_probe,
	.हटाओ		= ite_हटाओ,
	.suspend	= ite_suspend,
	.resume		= ite_resume,
	.shutकरोwn	= ite_shutकरोwn,
पूर्ण;

MODULE_DEVICE_TABLE(pnp, ite_ids);
MODULE_DESCRIPTION("ITE Tech Inc. IT8712F/ITE8512F CIR driver");

MODULE_AUTHOR("Juan J. Garcia de Soria <skandalfo@gmail.com>");
MODULE_LICENSE("GPL");

module_pnp_driver(ite_driver);
