<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Copyright (c) by Jaroslav Kysela <perex@perex.cz>
 *  Routines क्रम control of MPU-401 in UART mode
 *
 *  MPU-401 supports UART mode which is not capable generate transmit
 *  पूर्णांकerrupts thus output is करोne via polling. Without पूर्णांकerrupt,
 *  input is करोne also via polling. Do not expect good perक्रमmance.
 *
 *   13-03-2003:
 *      Added support क्रम dअगरferent kind of hardware I/O. Build in choices
 *      are port and mmio. For other kind of I/O, set mpu->पढ़ो and
 *      mpu->ग_लिखो to your own I/O functions.
 */

#समावेश <linux/पन.स>
#समावेश <linux/delay.h>
#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/ioport.h>
#समावेश <linux/module.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <sound/core.h>
#समावेश <sound/mpu401.h>

MODULE_AUTHOR("Jaroslav Kysela <perex@perex.cz>");
MODULE_DESCRIPTION("Routines for control of MPU-401 in UART mode");
MODULE_LICENSE("GPL");

अटल व्योम snd_mpu401_uart_input_पढ़ो(काष्ठा snd_mpu401 * mpu);
अटल व्योम snd_mpu401_uart_output_ग_लिखो(काष्ठा snd_mpu401 * mpu);

/*

 */

#घोषणा snd_mpu401_input_avail(mpu) \
	(!(mpu->पढ़ो(mpu, MPU401C(mpu)) & MPU401_RX_EMPTY))
#घोषणा snd_mpu401_output_पढ़ोy(mpu) \
	(!(mpu->पढ़ो(mpu, MPU401C(mpu)) & MPU401_TX_FULL))

/* Build in lowlevel io */
अटल व्योम mpu401_ग_लिखो_port(काष्ठा snd_mpu401 *mpu, अचिन्हित अक्षर data,
			      अचिन्हित दीर्घ addr)
अणु
	outb(data, addr);
पूर्ण

अटल अचिन्हित अक्षर mpu401_पढ़ो_port(काष्ठा snd_mpu401 *mpu,
				      अचिन्हित दीर्घ addr)
अणु
	वापस inb(addr);
पूर्ण

अटल व्योम mpu401_ग_लिखो_mmio(काष्ठा snd_mpu401 *mpu, अचिन्हित अक्षर data,
			      अचिन्हित दीर्घ addr)
अणु
	ग_लिखोb(data, (व्योम __iomem *)addr);
पूर्ण

अटल अचिन्हित अक्षर mpu401_पढ़ो_mmio(काष्ठा snd_mpu401 *mpu,
				      अचिन्हित दीर्घ addr)
अणु
	वापस पढ़ोb((व्योम __iomem *)addr);
पूर्ण
/*  */

अटल व्योम snd_mpu401_uart_clear_rx(काष्ठा snd_mpu401 *mpu)
अणु
	पूर्णांक समयout = 100000;
	क्रम (; समयout > 0 && snd_mpu401_input_avail(mpu); समयout--)
		mpu->पढ़ो(mpu, MPU401D(mpu));
#अगर_घोषित CONFIG_SND_DEBUG
	अगर (समयout <= 0)
		snd_prपूर्णांकk(KERN_ERR "cmd: clear rx timeout (status = 0x%x)\n",
			   mpu->पढ़ो(mpu, MPU401C(mpu)));
#पूर्ण_अगर
पूर्ण

अटल व्योम uart_पूर्णांकerrupt_tx(काष्ठा snd_mpu401 *mpu)
अणु
	अचिन्हित दीर्घ flags;

	अगर (test_bit(MPU401_MODE_BIT_OUTPUT, &mpu->mode) &&
	    test_bit(MPU401_MODE_BIT_OUTPUT_TRIGGER, &mpu->mode)) अणु
		spin_lock_irqsave(&mpu->output_lock, flags);
		snd_mpu401_uart_output_ग_लिखो(mpu);
		spin_unlock_irqrestore(&mpu->output_lock, flags);
	पूर्ण
पूर्ण

अटल व्योम _snd_mpu401_uart_पूर्णांकerrupt(काष्ठा snd_mpu401 *mpu)
अणु
	अचिन्हित दीर्घ flags;

	अगर (mpu->info_flags & MPU401_INFO_INPUT) अणु
		spin_lock_irqsave(&mpu->input_lock, flags);
		अगर (test_bit(MPU401_MODE_BIT_INPUT, &mpu->mode))
			snd_mpu401_uart_input_पढ़ो(mpu);
		अन्यथा
			snd_mpu401_uart_clear_rx(mpu);
		spin_unlock_irqrestore(&mpu->input_lock, flags);
	पूर्ण
	अगर (! (mpu->info_flags & MPU401_INFO_TX_IRQ))
		/* ok. क्रम better Tx perक्रमmance try करो some output
		   when input is करोne */
		uart_पूर्णांकerrupt_tx(mpu);
पूर्ण

/**
 * snd_mpu401_uart_पूर्णांकerrupt - generic MPU401-UART पूर्णांकerrupt handler
 * @irq: the irq number
 * @dev_id: mpu401 instance
 *
 * Processes the पूर्णांकerrupt क्रम MPU401-UART i/o.
 *
 * Return: %IRQ_HANDLED अगर the पूर्णांकerrupt was handled. %IRQ_NONE otherwise.
 */
irqवापस_t snd_mpu401_uart_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा snd_mpu401 *mpu = dev_id;
	
	अगर (!mpu)
		वापस IRQ_NONE;
	_snd_mpu401_uart_पूर्णांकerrupt(mpu);
	वापस IRQ_HANDLED;
पूर्ण

EXPORT_SYMBOL(snd_mpu401_uart_पूर्णांकerrupt);

/**
 * snd_mpu401_uart_पूर्णांकerrupt_tx - generic MPU401-UART transmit irq handler
 * @irq: the irq number
 * @dev_id: mpu401 instance
 *
 * Processes the पूर्णांकerrupt क्रम MPU401-UART output.
 *
 * Return: %IRQ_HANDLED अगर the पूर्णांकerrupt was handled. %IRQ_NONE otherwise.
 */
irqवापस_t snd_mpu401_uart_पूर्णांकerrupt_tx(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा snd_mpu401 *mpu = dev_id;
	
	अगर (!mpu)
		वापस IRQ_NONE;
	uart_पूर्णांकerrupt_tx(mpu);
	वापस IRQ_HANDLED;
पूर्ण

EXPORT_SYMBOL(snd_mpu401_uart_पूर्णांकerrupt_tx);

/*
 * समयr callback
 * reprogram the समयr and call the पूर्णांकerrupt job
 */
अटल व्योम snd_mpu401_uart_समयr(काष्ठा समयr_list *t)
अणु
	काष्ठा snd_mpu401 *mpu = from_समयr(mpu, t, समयr);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&mpu->समयr_lock, flags);
	/*mpu->mode |= MPU401_MODE_TIMER;*/
	mod_समयr(&mpu->समयr,  1 + jअगरfies);
	spin_unlock_irqrestore(&mpu->समयr_lock, flags);
	अगर (mpu->rmidi)
		_snd_mpu401_uart_पूर्णांकerrupt(mpu);
पूर्ण

/*
 * initialize the समयr callback अगर not programmed yet
 */
अटल व्योम snd_mpu401_uart_add_समयr (काष्ठा snd_mpu401 *mpu, पूर्णांक input)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave (&mpu->समयr_lock, flags);
	अगर (mpu->समयr_invoked == 0) अणु
		समयr_setup(&mpu->समयr, snd_mpu401_uart_समयr, 0);
		mod_समयr(&mpu->समयr, 1 + jअगरfies);
	पूर्ण 
	mpu->समयr_invoked |= input ? MPU401_MODE_INPUT_TIMER :
		MPU401_MODE_OUTPUT_TIMER;
	spin_unlock_irqrestore (&mpu->समयr_lock, flags);
पूर्ण

/*
 * हटाओ the समयr callback अगर still active
 */
अटल व्योम snd_mpu401_uart_हटाओ_समयr (काष्ठा snd_mpu401 *mpu, पूर्णांक input)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave (&mpu->समयr_lock, flags);
	अगर (mpu->समयr_invoked) अणु
		mpu->समयr_invoked &= input ? ~MPU401_MODE_INPUT_TIMER :
			~MPU401_MODE_OUTPUT_TIMER;
		अगर (! mpu->समयr_invoked)
			del_समयr(&mpu->समयr);
	पूर्ण
	spin_unlock_irqrestore (&mpu->समयr_lock, flags);
पूर्ण

/*
 * send a UART command
 * वापस zero अगर successful, non-zero क्रम some errors
 */

अटल पूर्णांक snd_mpu401_uart_cmd(काष्ठा snd_mpu401 * mpu, अचिन्हित अक्षर cmd,
			       पूर्णांक ack)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक समयout, ok;

	spin_lock_irqsave(&mpu->input_lock, flags);
	अगर (mpu->hardware != MPU401_HW_TRID4DWAVE) अणु
		mpu->ग_लिखो(mpu, 0x00, MPU401D(mpu));
		/*snd_mpu401_uart_clear_rx(mpu);*/
	पूर्ण
	/* ok. standard MPU-401 initialization */
	अगर (mpu->hardware != MPU401_HW_SB) अणु
		क्रम (समयout = 1000; समयout > 0 &&
			     !snd_mpu401_output_पढ़ोy(mpu); समयout--)
			udelay(10);
#अगर_घोषित CONFIG_SND_DEBUG
		अगर (!समयout)
			snd_prपूर्णांकk(KERN_ERR "cmd: tx timeout (status = 0x%x)\n",
				   mpu->पढ़ो(mpu, MPU401C(mpu)));
#पूर्ण_अगर
	पूर्ण
	mpu->ग_लिखो(mpu, cmd, MPU401C(mpu));
	अगर (ack && !(mpu->info_flags & MPU401_INFO_NO_ACK)) अणु
		ok = 0;
		समयout = 10000;
		जबतक (!ok && समयout-- > 0) अणु
			अगर (snd_mpu401_input_avail(mpu)) अणु
				अगर (mpu->पढ़ो(mpu, MPU401D(mpu)) == MPU401_ACK)
					ok = 1;
			पूर्ण
		पूर्ण
		अगर (!ok && mpu->पढ़ो(mpu, MPU401D(mpu)) == MPU401_ACK)
			ok = 1;
	पूर्ण अन्यथा
		ok = 1;
	spin_unlock_irqrestore(&mpu->input_lock, flags);
	अगर (!ok) अणु
		snd_prपूर्णांकk(KERN_ERR "cmd: 0x%x failed at 0x%lx "
			   "(status = 0x%x, data = 0x%x)\n", cmd, mpu->port,
			   mpu->पढ़ो(mpu, MPU401C(mpu)),
			   mpu->पढ़ो(mpu, MPU401D(mpu)));
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक snd_mpu401_करो_reset(काष्ठा snd_mpu401 *mpu)
अणु
	अगर (snd_mpu401_uart_cmd(mpu, MPU401_RESET, 1))
		वापस -EIO;
	अगर (snd_mpu401_uart_cmd(mpu, MPU401_ENTER_UART, 0))
		वापस -EIO;
	वापस 0;
पूर्ण

/*
 * input/output खोलो/बंद - रक्षित by खोलो_mutex in rawmidi.c
 */
अटल पूर्णांक snd_mpu401_uart_input_खोलो(काष्ठा snd_rawmidi_substream *substream)
अणु
	काष्ठा snd_mpu401 *mpu;
	पूर्णांक err;

	mpu = substream->rmidi->निजी_data;
	अगर (mpu->खोलो_input && (err = mpu->खोलो_input(mpu)) < 0)
		वापस err;
	अगर (! test_bit(MPU401_MODE_BIT_OUTPUT, &mpu->mode)) अणु
		अगर (snd_mpu401_करो_reset(mpu) < 0)
			जाओ error_out;
	पूर्ण
	mpu->substream_input = substream;
	set_bit(MPU401_MODE_BIT_INPUT, &mpu->mode);
	वापस 0;

error_out:
	अगर (mpu->खोलो_input && mpu->बंद_input)
		mpu->बंद_input(mpu);
	वापस -EIO;
पूर्ण

अटल पूर्णांक snd_mpu401_uart_output_खोलो(काष्ठा snd_rawmidi_substream *substream)
अणु
	काष्ठा snd_mpu401 *mpu;
	पूर्णांक err;

	mpu = substream->rmidi->निजी_data;
	अगर (mpu->खोलो_output && (err = mpu->खोलो_output(mpu)) < 0)
		वापस err;
	अगर (! test_bit(MPU401_MODE_BIT_INPUT, &mpu->mode)) अणु
		अगर (snd_mpu401_करो_reset(mpu) < 0)
			जाओ error_out;
	पूर्ण
	mpu->substream_output = substream;
	set_bit(MPU401_MODE_BIT_OUTPUT, &mpu->mode);
	वापस 0;

error_out:
	अगर (mpu->खोलो_output && mpu->बंद_output)
		mpu->बंद_output(mpu);
	वापस -EIO;
पूर्ण

अटल पूर्णांक snd_mpu401_uart_input_बंद(काष्ठा snd_rawmidi_substream *substream)
अणु
	काष्ठा snd_mpu401 *mpu;
	पूर्णांक err = 0;

	mpu = substream->rmidi->निजी_data;
	clear_bit(MPU401_MODE_BIT_INPUT, &mpu->mode);
	mpu->substream_input = शून्य;
	अगर (! test_bit(MPU401_MODE_BIT_OUTPUT, &mpu->mode))
		err = snd_mpu401_uart_cmd(mpu, MPU401_RESET, 0);
	अगर (mpu->बंद_input)
		mpu->बंद_input(mpu);
	अगर (err)
		वापस -EIO;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_mpu401_uart_output_बंद(काष्ठा snd_rawmidi_substream *substream)
अणु
	काष्ठा snd_mpu401 *mpu;
	पूर्णांक err = 0;

	mpu = substream->rmidi->निजी_data;
	clear_bit(MPU401_MODE_BIT_OUTPUT, &mpu->mode);
	mpu->substream_output = शून्य;
	अगर (! test_bit(MPU401_MODE_BIT_INPUT, &mpu->mode))
		err = snd_mpu401_uart_cmd(mpu, MPU401_RESET, 0);
	अगर (mpu->बंद_output)
		mpu->बंद_output(mpu);
	अगर (err)
		वापस -EIO;
	वापस 0;
पूर्ण

/*
 * trigger input callback
 */
अटल व्योम
snd_mpu401_uart_input_trigger(काष्ठा snd_rawmidi_substream *substream, पूर्णांक up)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा snd_mpu401 *mpu;
	पूर्णांक max = 64;

	mpu = substream->rmidi->निजी_data;
	अगर (up) अणु
		अगर (! test_and_set_bit(MPU401_MODE_BIT_INPUT_TRIGGER,
				       &mpu->mode)) अणु
			/* first समय - flush FIFO */
			जबतक (max-- > 0)
				mpu->पढ़ो(mpu, MPU401D(mpu));
			अगर (mpu->info_flags & MPU401_INFO_USE_TIMER)
				snd_mpu401_uart_add_समयr(mpu, 1);
		पूर्ण
		
		/* पढ़ो data in advance */
		spin_lock_irqsave(&mpu->input_lock, flags);
		snd_mpu401_uart_input_पढ़ो(mpu);
		spin_unlock_irqrestore(&mpu->input_lock, flags);
	पूर्ण अन्यथा अणु
		अगर (mpu->info_flags & MPU401_INFO_USE_TIMER)
			snd_mpu401_uart_हटाओ_समयr(mpu, 1);
		clear_bit(MPU401_MODE_BIT_INPUT_TRIGGER, &mpu->mode);
	पूर्ण

पूर्ण

/*
 * transfer input pending data
 * call with input_lock spinlock held
 */
अटल व्योम snd_mpu401_uart_input_पढ़ो(काष्ठा snd_mpu401 * mpu)
अणु
	पूर्णांक max = 128;
	अचिन्हित अक्षर byte;

	जबतक (max-- > 0) अणु
		अगर (! snd_mpu401_input_avail(mpu))
			अवरोध; /* input not available */
		byte = mpu->पढ़ो(mpu, MPU401D(mpu));
		अगर (test_bit(MPU401_MODE_BIT_INPUT_TRIGGER, &mpu->mode))
			snd_rawmidi_receive(mpu->substream_input, &byte, 1);
	पूर्ण
पूर्ण

/*
 *  Tx FIFO sizes:
 *    CS4237B			- 16 bytes
 *    AudioDrive ES1688         - 12 bytes
 *    S3 SonicVibes             -  8 bytes
 *    SoundBlaster AWE 64       -  2 bytes (ugly hardware)
 */

/*
 * ग_लिखो output pending bytes
 * call with output_lock spinlock held
 */
अटल व्योम snd_mpu401_uart_output_ग_लिखो(काष्ठा snd_mpu401 * mpu)
अणु
	अचिन्हित अक्षर byte;
	पूर्णांक max = 256;

	करो अणु
		अगर (snd_rawmidi_transmit_peek(mpu->substream_output,
					      &byte, 1) == 1) अणु
			/*
			 * Try twice because there is hardware that insists on
			 * setting the output busy bit after each ग_लिखो.
			 */
			अगर (!snd_mpu401_output_पढ़ोy(mpu) &&
			    !snd_mpu401_output_पढ़ोy(mpu))
				अवरोध;	/* Tx FIFO full - try again later */
			mpu->ग_लिखो(mpu, byte, MPU401D(mpu));
			snd_rawmidi_transmit_ack(mpu->substream_output, 1);
		पूर्ण अन्यथा अणु
			snd_mpu401_uart_हटाओ_समयr (mpu, 0);
			अवरोध;	/* no other data - leave the tx loop */
		पूर्ण
	पूर्ण जबतक (--max > 0);
पूर्ण

/*
 * output trigger callback
 */
अटल व्योम
snd_mpu401_uart_output_trigger(काष्ठा snd_rawmidi_substream *substream, पूर्णांक up)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा snd_mpu401 *mpu;

	mpu = substream->rmidi->निजी_data;
	अगर (up) अणु
		set_bit(MPU401_MODE_BIT_OUTPUT_TRIGGER, &mpu->mode);

		/* try to add the समयr at each output trigger,
		 * since the output समयr might have been हटाओd in
		 * snd_mpu401_uart_output_ग_लिखो().
		 */
		अगर (! (mpu->info_flags & MPU401_INFO_TX_IRQ))
			snd_mpu401_uart_add_समयr(mpu, 0);

		/* output pending data */
		spin_lock_irqsave(&mpu->output_lock, flags);
		snd_mpu401_uart_output_ग_लिखो(mpu);
		spin_unlock_irqrestore(&mpu->output_lock, flags);
	पूर्ण अन्यथा अणु
		अगर (! (mpu->info_flags & MPU401_INFO_TX_IRQ))
			snd_mpu401_uart_हटाओ_समयr(mpu, 0);
		clear_bit(MPU401_MODE_BIT_OUTPUT_TRIGGER, &mpu->mode);
	पूर्ण
पूर्ण

/*

 */

अटल स्थिर काष्ठा snd_rawmidi_ops snd_mpu401_uart_output =
अणु
	.खोलो =		snd_mpu401_uart_output_खोलो,
	.बंद =	snd_mpu401_uart_output_बंद,
	.trigger =	snd_mpu401_uart_output_trigger,
पूर्ण;

अटल स्थिर काष्ठा snd_rawmidi_ops snd_mpu401_uart_input =
अणु
	.खोलो =		snd_mpu401_uart_input_खोलो,
	.बंद =	snd_mpu401_uart_input_बंद,
	.trigger =	snd_mpu401_uart_input_trigger,
पूर्ण;

अटल व्योम snd_mpu401_uart_मुक्त(काष्ठा snd_rawmidi *rmidi)
अणु
	काष्ठा snd_mpu401 *mpu = rmidi->निजी_data;
	अगर (mpu->irq >= 0)
		मुक्त_irq(mpu->irq, (व्योम *) mpu);
	release_and_मुक्त_resource(mpu->res);
	kमुक्त(mpu);
पूर्ण

/**
 * snd_mpu401_uart_new - create an MPU401-UART instance
 * @card: the card instance
 * @device: the device index, zero-based
 * @hardware: the hardware type, MPU401_HW_XXXX
 * @port: the base address of MPU401 port
 * @info_flags: bitflags MPU401_INFO_XXX
 * @irq: the ISA irq number, -1 अगर not to be allocated
 * @rrawmidi: the poपूर्णांकer to store the new rawmidi instance
 *
 * Creates a new MPU-401 instance.
 *
 * Note that the rawmidi instance is वापसed on the rrawmidi argument,
 * not the mpu401 instance itself.  To access to the mpu401 instance,
 * cast from rawmidi->निजी_data (with काष्ठा snd_mpu401 magic-cast).
 *
 * Return: Zero अगर successful, or a negative error code.
 */
पूर्णांक snd_mpu401_uart_new(काष्ठा snd_card *card, पूर्णांक device,
			अचिन्हित लघु hardware,
			अचिन्हित दीर्घ port,
			अचिन्हित पूर्णांक info_flags,
			पूर्णांक irq,
			काष्ठा snd_rawmidi ** rrawmidi)
अणु
	काष्ठा snd_mpu401 *mpu;
	काष्ठा snd_rawmidi *rmidi;
	पूर्णांक in_enable, out_enable;
	पूर्णांक err;

	अगर (rrawmidi)
		*rrawmidi = शून्य;
	अगर (! (info_flags & (MPU401_INFO_INPUT | MPU401_INFO_OUTPUT)))
		info_flags |= MPU401_INFO_INPUT | MPU401_INFO_OUTPUT;
	in_enable = (info_flags & MPU401_INFO_INPUT) ? 1 : 0;
	out_enable = (info_flags & MPU401_INFO_OUTPUT) ? 1 : 0;
	अगर ((err = snd_rawmidi_new(card, "MPU-401U", device,
				   out_enable, in_enable, &rmidi)) < 0)
		वापस err;
	mpu = kzalloc(माप(*mpu), GFP_KERNEL);
	अगर (!mpu) अणु
		err = -ENOMEM;
		जाओ मुक्त_device;
	पूर्ण
	rmidi->निजी_data = mpu;
	rmidi->निजी_मुक्त = snd_mpu401_uart_मुक्त;
	spin_lock_init(&mpu->input_lock);
	spin_lock_init(&mpu->output_lock);
	spin_lock_init(&mpu->समयr_lock);
	mpu->hardware = hardware;
	mpu->irq = -1;
	अगर (! (info_flags & MPU401_INFO_INTEGRATED)) अणु
		पूर्णांक res_size = hardware == MPU401_HW_PC98II ? 4 : 2;
		mpu->res = request_region(port, res_size, "MPU401 UART");
		अगर (!mpu->res) अणु
			snd_prपूर्णांकk(KERN_ERR "mpu401_uart: "
				   "unable to grab port 0x%lx size %d\n",
				   port, res_size);
			err = -EBUSY;
			जाओ मुक्त_device;
		पूर्ण
	पूर्ण
	अगर (info_flags & MPU401_INFO_MMIO) अणु
		mpu->ग_लिखो = mpu401_ग_लिखो_mmio;
		mpu->पढ़ो = mpu401_पढ़ो_mmio;
	पूर्ण अन्यथा अणु
		mpu->ग_लिखो = mpu401_ग_लिखो_port;
		mpu->पढ़ो = mpu401_पढ़ो_port;
	पूर्ण
	mpu->port = port;
	अगर (hardware == MPU401_HW_PC98II)
		mpu->cport = port + 2;
	अन्यथा
		mpu->cport = port + 1;
	अगर (irq >= 0) अणु
		अगर (request_irq(irq, snd_mpu401_uart_पूर्णांकerrupt, 0,
				"MPU401 UART", (व्योम *) mpu)) अणु
			snd_prपूर्णांकk(KERN_ERR "mpu401_uart: "
				   "unable to grab IRQ %d\n", irq);
			err = -EBUSY;
			जाओ मुक्त_device;
		पूर्ण
	पूर्ण
	अगर (irq < 0 && !(info_flags & MPU401_INFO_IRQ_HOOK))
		info_flags |= MPU401_INFO_USE_TIMER;
	mpu->info_flags = info_flags;
	mpu->irq = irq;
	अगर (card->लघुname[0])
		snम_लिखो(rmidi->name, माप(rmidi->name), "%s MIDI",
			 card->लघुname);
	अन्यथा
		प्र_लिखो(rmidi->name, "MPU-401 MIDI %d-%d",card->number, device);
	अगर (out_enable) अणु
		snd_rawmidi_set_ops(rmidi, SNDRV_RAWMIDI_STREAM_OUTPUT,
				    &snd_mpu401_uart_output);
		rmidi->info_flags |= SNDRV_RAWMIDI_INFO_OUTPUT;
	पूर्ण
	अगर (in_enable) अणु
		snd_rawmidi_set_ops(rmidi, SNDRV_RAWMIDI_STREAM_INPUT,
				    &snd_mpu401_uart_input);
		rmidi->info_flags |= SNDRV_RAWMIDI_INFO_INPUT;
		अगर (out_enable)
			rmidi->info_flags |= SNDRV_RAWMIDI_INFO_DUPLEX;
	पूर्ण
	mpu->rmidi = rmidi;
	अगर (rrawmidi)
		*rrawmidi = rmidi;
	वापस 0;
मुक्त_device:
	snd_device_मुक्त(card, rmidi);
	वापस err;
पूर्ण

EXPORT_SYMBOL(snd_mpu401_uart_new);
