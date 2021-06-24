<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * usbduxsigma.c
 * Copyright (C) 2011-2015 Bernd Porr, mail@berndporr.me.uk
 */

/*
 * Driver: usbduxsigma
 * Description: University of Stirling USB DAQ & INCITE Technology Limited
 * Devices: [ITL] USB-DUX-SIGMA (usbduxsigma)
 * Author: Bernd Porr <mail@berndporr.me.uk>
 * Updated: 20 July 2015
 * Status: stable
 */

/*
 * I must give credit here to Chris Baugher who
 * wrote the driver क्रम AT-MIO-16d. I used some parts of this
 * driver. I also must give credits to David Brownell
 * who supported me with the USB development.
 *
 * Note: the raw data from the A/D converter is 24 bit big endian
 * anything अन्यथा is little endian to/from the dux board
 *
 *
 * Revision history:
 *   0.1: initial version
 *   0.2: all basic functions implemented, digital I/O only क्रम one port
 *   0.3: proper venकरोr ID and driver name
 *   0.4: fixed D/A voltage range
 *   0.5: various bug fixes, health check at startup
 *   0.6: corrected wrong input range
 *   0.7: reग_लिखो code that urb->पूर्णांकerval is always 1
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/input.h>
#समावेश <linux/fcntl.h>
#समावेश <linux/compiler.h>
#समावेश <यंत्र/unaligned.h>

#समावेश "../comedi_usb.h"

/* समयout क्रम the USB-transfer in ms*/
#घोषणा BULK_TIMEOUT 1000

/* स्थिरants क्रम "firmware" upload and करोwnload */
#घोषणा FIRMWARE		"usbduxsigma_firmware.bin"
#घोषणा FIRMWARE_MAX_LEN	0x4000
#घोषणा USBDUXSUB_FIRMWARE	0xa0
#घोषणा VENDOR_सूची_IN		0xc0
#घोषणा VENDOR_सूची_OUT		0x40

/* पूर्णांकernal addresses of the 8051 processor */
#घोषणा USBDUXSUB_CPUCS 0xE600

/* 300Hz max frequ under PWM */
#घोषणा MIN_PWM_PERIOD  ((दीर्घ)(1E9 / 300))

/* Default PWM frequency */
#घोषणा PWM_DEFAULT_PERIOD ((दीर्घ)(1E9 / 100))

/* Number of channels (16 AD and offset)*/
#घोषणा NUMCHANNELS 16

/* Size of one A/D value */
#घोषणा SIZEADIN          ((माप(u32)))

/*
 * Size of the async input-buffer IN BYTES, the DIO state is transmitted
 * as the first byte.
 */
#घोषणा SIZEINBUF         (((NUMCHANNELS + 1) * SIZEADIN))

/* 16 bytes. */
#घोषणा SIZEINSNBUF       16

/* Number of DA channels */
#घोषणा NUMOUTCHANNELS    8

/* size of one value क्रम the D/A converter: channel and value */
#घोषणा SIZEDAOUT          ((माप(u8) + माप(uपूर्णांक16_t)))

/*
 * Size of the output-buffer in bytes
 * Actually only the first 4 triplets are used but क्रम the
 * high speed mode we need to pad it to 8 (microframes).
 */
#घोषणा SIZEOUTBUF         ((8 * SIZEDAOUT))

/*
 * Size of the buffer क्रम the dux commands: just now max size is determined
 * by the analogue out + command byte + panic bytes...
 */
#घोषणा SIZखातापूर्णDUXBUFFER    ((8 * SIZEDAOUT + 2))

/* Number of in-URBs which receive the data: min=2 */
#घोषणा NUMOFINBUFFERSFULL     5

/* Number of out-URBs which send the data: min=2 */
#घोषणा NUMOFOUTBUFFERSFULL    5

/* Number of in-URBs which receive the data: min=5 */
/* must have more buffers due to buggy USB ctr */
#घोषणा NUMOFINBUFFERSHIGH     10

/* Number of out-URBs which send the data: min=5 */
/* must have more buffers due to buggy USB ctr */
#घोषणा NUMOFOUTBUFFERSHIGH    10

/* number of retries to get the right dux command */
#घोषणा RETRIES 10

/* bulk transfer commands to usbduxsigma */
#घोषणा USBBUXSIGMA_AD_CMD		9
#घोषणा USBDUXSIGMA_DA_CMD		1
#घोषणा USBDUXSIGMA_DIO_CFG_CMD		2
#घोषणा USBDUXSIGMA_DIO_BITS_CMD	3
#घोषणा USBDUXSIGMA_SINGLE_AD_CMD	4
#घोषणा USBDUXSIGMA_PWM_ON_CMD		7
#घोषणा USBDUXSIGMA_PWM_OFF_CMD		8

अटल स्थिर काष्ठा comedi_lrange usbduxsigma_ai_range = अणु
	1, अणु
		BIP_RANGE(2.5 * 0x800000 / 0x780000 / 2.0)
	पूर्ण
पूर्ण;

काष्ठा usbduxsigma_निजी अणु
	/* actual number of in-buffers */
	पूर्णांक n_ai_urbs;
	/* actual number of out-buffers */
	पूर्णांक n_ao_urbs;
	/* ISO-transfer handling: buffers */
	काष्ठा urb **ai_urbs;
	काष्ठा urb **ao_urbs;
	/* pwm-transfer handling */
	काष्ठा urb *pwm_urb;
	/* PWM period */
	अचिन्हित पूर्णांक pwm_period;
	/* PWM पूर्णांकernal delay क्रम the GPIF in the FX2 */
	u8 pwm_delay;
	/* size of the PWM buffer which holds the bit pattern */
	पूर्णांक pwm_buf_sz;
	/* input buffer क्रम the ISO-transfer */
	__be32 *in_buf;
	/* input buffer क्रम single insn */
	u8 *insn_buf;

	अचिन्हित high_speed:1;
	अचिन्हित ai_cmd_running:1;
	अचिन्हित ao_cmd_running:1;
	अचिन्हित pwm_cmd_running:1;

	/* समय between samples in units of the समयr */
	अचिन्हित पूर्णांक ai_समयr;
	अचिन्हित पूर्णांक ao_समयr;
	/* counter between acquisitions */
	अचिन्हित पूर्णांक ai_counter;
	अचिन्हित पूर्णांक ao_counter;
	/* पूर्णांकerval in frames/uframes */
	अचिन्हित पूर्णांक ai_पूर्णांकerval;
	/* commands */
	u8 *dux_commands;
	काष्ठा mutex mut;
पूर्ण;

अटल व्योम usbduxsigma_unlink_urbs(काष्ठा urb **urbs, पूर्णांक num_urbs)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < num_urbs; i++)
		usb_समाप्त_urb(urbs[i]);
पूर्ण

अटल व्योम usbduxsigma_ai_stop(काष्ठा comedi_device *dev, पूर्णांक करो_unlink)
अणु
	काष्ठा usbduxsigma_निजी *devpriv = dev->निजी;

	अगर (करो_unlink && devpriv->ai_urbs)
		usbduxsigma_unlink_urbs(devpriv->ai_urbs, devpriv->n_ai_urbs);

	devpriv->ai_cmd_running = 0;
पूर्ण

अटल पूर्णांक usbduxsigma_ai_cancel(काष्ठा comedi_device *dev,
				 काष्ठा comedi_subdevice *s)
अणु
	काष्ठा usbduxsigma_निजी *devpriv = dev->निजी;

	mutex_lock(&devpriv->mut);
	/* unlink only अगर it is really running */
	usbduxsigma_ai_stop(dev, devpriv->ai_cmd_running);
	mutex_unlock(&devpriv->mut);

	वापस 0;
पूर्ण

अटल व्योम usbduxsigma_ai_handle_urb(काष्ठा comedi_device *dev,
				      काष्ठा comedi_subdevice *s,
				      काष्ठा urb *urb)
अणु
	काष्ठा usbduxsigma_निजी *devpriv = dev->निजी;
	काष्ठा comedi_async *async = s->async;
	काष्ठा comedi_cmd *cmd = &async->cmd;
	u32 val;
	पूर्णांक ret;
	पूर्णांक i;

	अगर ((urb->actual_length > 0) && (urb->status != -EXDEV)) अणु
		devpriv->ai_counter--;
		अगर (devpriv->ai_counter == 0) अणु
			devpriv->ai_counter = devpriv->ai_समयr;

			/*
			 * Get the data from the USB bus and hand it over
			 * to comedi. Note, first byte is the DIO state.
			 */
			क्रम (i = 0; i < cmd->chanlist_len; i++) अणु
				val = be32_to_cpu(devpriv->in_buf[i + 1]);
				val &= 0x00ffffff; /* strip status byte */
				val = comedi_offset_munge(s, val);
				अगर (!comedi_buf_ग_लिखो_samples(s, &val, 1))
					वापस;
			पूर्ण

			अगर (cmd->stop_src == TRIG_COUNT &&
			    async->scans_करोne >= cmd->stop_arg)
				async->events |= COMEDI_CB_EOA;
		पूर्ण
	पूर्ण

	/* अगर command is still running, resubmit urb */
	अगर (!(async->events & COMEDI_CB_CANCEL_MASK)) अणु
		urb->dev = comedi_to_usb_dev(dev);
		ret = usb_submit_urb(urb, GFP_ATOMIC);
		अगर (ret < 0) अणु
			dev_err(dev->class_dev, "urb resubmit failed (%d)\n",
				ret);
			अगर (ret == -EL2NSYNC)
				dev_err(dev->class_dev,
					"buggy USB host controller or bug in IRQ handler\n");
			async->events |= COMEDI_CB_ERROR;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम usbduxsigma_ai_urb_complete(काष्ठा urb *urb)
अणु
	काष्ठा comedi_device *dev = urb->context;
	काष्ठा usbduxsigma_निजी *devpriv = dev->निजी;
	काष्ठा comedi_subdevice *s = dev->पढ़ो_subdev;
	काष्ठा comedi_async *async = s->async;

	/* निकास अगर not running a command, करो not resubmit urb */
	अगर (!devpriv->ai_cmd_running)
		वापस;

	चयन (urb->status) अणु
	हाल 0:
		/* copy the result in the transfer buffer */
		स_नकल(devpriv->in_buf, urb->transfer_buffer, SIZEINBUF);
		usbduxsigma_ai_handle_urb(dev, s, urb);
		अवरोध;

	हाल -EILSEQ:
		/*
		 * error in the ISOchronous data
		 * we करोn't copy the data पूर्णांकo the transfer buffer
		 * and recycle the last data byte
		 */
		dev_dbg(dev->class_dev, "CRC error in ISO IN stream\n");
		usbduxsigma_ai_handle_urb(dev, s, urb);
		अवरोध;

	हाल -ECONNRESET:
	हाल -ENOENT:
	हाल -ESHUTDOWN:
	हाल -ECONNABORTED:
		/* happens after an unlink command */
		async->events |= COMEDI_CB_ERROR;
		अवरोध;

	शेष:
		/* a real error */
		dev_err(dev->class_dev, "non-zero urb status (%d)\n",
			urb->status);
		async->events |= COMEDI_CB_ERROR;
		अवरोध;
	पूर्ण

	/*
	 * comedi_handle_events() cannot be used in this driver. The (*cancel)
	 * operation would unlink the urb.
	 */
	अगर (async->events & COMEDI_CB_CANCEL_MASK)
		usbduxsigma_ai_stop(dev, 0);

	comedi_event(dev, s);
पूर्ण

अटल व्योम usbduxsigma_ao_stop(काष्ठा comedi_device *dev, पूर्णांक करो_unlink)
अणु
	काष्ठा usbduxsigma_निजी *devpriv = dev->निजी;

	अगर (करो_unlink && devpriv->ao_urbs)
		usbduxsigma_unlink_urbs(devpriv->ao_urbs, devpriv->n_ao_urbs);

	devpriv->ao_cmd_running = 0;
पूर्ण

अटल पूर्णांक usbduxsigma_ao_cancel(काष्ठा comedi_device *dev,
				 काष्ठा comedi_subdevice *s)
अणु
	काष्ठा usbduxsigma_निजी *devpriv = dev->निजी;

	mutex_lock(&devpriv->mut);
	/* unlink only अगर it is really running */
	usbduxsigma_ao_stop(dev, devpriv->ao_cmd_running);
	mutex_unlock(&devpriv->mut);

	वापस 0;
पूर्ण

अटल व्योम usbduxsigma_ao_handle_urb(काष्ठा comedi_device *dev,
				      काष्ठा comedi_subdevice *s,
				      काष्ठा urb *urb)
अणु
	काष्ठा usbduxsigma_निजी *devpriv = dev->निजी;
	काष्ठा comedi_async *async = s->async;
	काष्ठा comedi_cmd *cmd = &async->cmd;
	u8 *datap;
	पूर्णांक ret;
	पूर्णांक i;

	devpriv->ao_counter--;
	अगर (devpriv->ao_counter == 0) अणु
		devpriv->ao_counter = devpriv->ao_समयr;

		अगर (cmd->stop_src == TRIG_COUNT &&
		    async->scans_करोne >= cmd->stop_arg) अणु
			async->events |= COMEDI_CB_EOA;
			वापस;
		पूर्ण

		/* transmit data to the USB bus */
		datap = urb->transfer_buffer;
		*datap++ = cmd->chanlist_len;
		क्रम (i = 0; i < cmd->chanlist_len; i++) अणु
			अचिन्हित पूर्णांक chan = CR_CHAN(cmd->chanlist[i]);
			अचिन्हित लघु val;

			अगर (!comedi_buf_पढ़ो_samples(s, &val, 1)) अणु
				dev_err(dev->class_dev, "buffer underflow\n");
				async->events |= COMEDI_CB_OVERFLOW;
				वापस;
			पूर्ण

			*datap++ = val;
			*datap++ = chan;
			s->पढ़ोback[chan] = val;
		पूर्ण
	पूर्ण

	/* अगर command is still running, resubmit urb */
	अगर (!(async->events & COMEDI_CB_CANCEL_MASK)) अणु
		urb->transfer_buffer_length = SIZEOUTBUF;
		urb->dev = comedi_to_usb_dev(dev);
		urb->status = 0;
		urb->पूर्णांकerval = 1;	/* (u)frames */
		urb->number_of_packets = 1;
		urb->iso_frame_desc[0].offset = 0;
		urb->iso_frame_desc[0].length = SIZEOUTBUF;
		urb->iso_frame_desc[0].status = 0;
		ret = usb_submit_urb(urb, GFP_ATOMIC);
		अगर (ret < 0) अणु
			dev_err(dev->class_dev, "urb resubmit failed (%d)\n",
				ret);
			अगर (ret == -EL2NSYNC)
				dev_err(dev->class_dev,
					"buggy USB host controller or bug in IRQ handler\n");
			async->events |= COMEDI_CB_ERROR;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम usbduxsigma_ao_urb_complete(काष्ठा urb *urb)
अणु
	काष्ठा comedi_device *dev = urb->context;
	काष्ठा usbduxsigma_निजी *devpriv = dev->निजी;
	काष्ठा comedi_subdevice *s = dev->ग_लिखो_subdev;
	काष्ठा comedi_async *async = s->async;

	/* निकास अगर not running a command, करो not resubmit urb */
	अगर (!devpriv->ao_cmd_running)
		वापस;

	चयन (urb->status) अणु
	हाल 0:
		usbduxsigma_ao_handle_urb(dev, s, urb);
		अवरोध;

	हाल -ECONNRESET:
	हाल -ENOENT:
	हाल -ESHUTDOWN:
	हाल -ECONNABORTED:
		/* happens after an unlink command */
		async->events |= COMEDI_CB_ERROR;
		अवरोध;

	शेष:
		/* a real error */
		dev_err(dev->class_dev, "non-zero urb status (%d)\n",
			urb->status);
		async->events |= COMEDI_CB_ERROR;
		अवरोध;
	पूर्ण

	/*
	 * comedi_handle_events() cannot be used in this driver. The (*cancel)
	 * operation would unlink the urb.
	 */
	अगर (async->events & COMEDI_CB_CANCEL_MASK)
		usbduxsigma_ao_stop(dev, 0);

	comedi_event(dev, s);
पूर्ण

अटल पूर्णांक usbduxsigma_submit_urbs(काष्ठा comedi_device *dev,
				   काष्ठा urb **urbs, पूर्णांक num_urbs,
				   पूर्णांक input_urb)
अणु
	काष्ठा usb_device *usb = comedi_to_usb_dev(dev);
	काष्ठा urb *urb;
	पूर्णांक ret;
	पूर्णांक i;

	/* Submit all URBs and start the transfer on the bus */
	क्रम (i = 0; i < num_urbs; i++) अणु
		urb = urbs[i];

		/* in हाल of a resubmission after an unlink... */
		अगर (input_urb)
			urb->पूर्णांकerval = 1;
		urb->context = dev;
		urb->dev = usb;
		urb->status = 0;
		urb->transfer_flags = URB_ISO_ASAP;

		ret = usb_submit_urb(urb, GFP_ATOMIC);
		अगर (ret)
			वापस ret;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक usbduxsigma_chans_to_पूर्णांकerval(पूर्णांक num_chan)
अणु
	अगर (num_chan <= 2)
		वापस 2;	/* 4kHz */
	अगर (num_chan <= 8)
		वापस 4;	/* 2kHz */
	वापस 8;		/* 1kHz */
पूर्ण

अटल पूर्णांक usbduxsigma_ai_cmdtest(काष्ठा comedi_device *dev,
				  काष्ठा comedi_subdevice *s,
				  काष्ठा comedi_cmd *cmd)
अणु
	काष्ठा usbduxsigma_निजी *devpriv = dev->निजी;
	पूर्णांक high_speed = devpriv->high_speed;
	पूर्णांक पूर्णांकerval = usbduxsigma_chans_to_पूर्णांकerval(cmd->chanlist_len);
	अचिन्हित पूर्णांक पंचांगp;
	पूर्णांक err = 0;

	/* Step 1 : check अगर triggers are trivially valid */

	err |= comedi_check_trigger_src(&cmd->start_src, TRIG_NOW | TRIG_INT);
	err |= comedi_check_trigger_src(&cmd->scan_begin_src, TRIG_TIMER);
	err |= comedi_check_trigger_src(&cmd->convert_src, TRIG_NOW);
	err |= comedi_check_trigger_src(&cmd->scan_end_src, TRIG_COUNT);
	err |= comedi_check_trigger_src(&cmd->stop_src, TRIG_COUNT | TRIG_NONE);

	अगर (err)
		वापस 1;

	/* Step 2a : make sure trigger sources are unique */

	err |= comedi_check_trigger_is_unique(cmd->start_src);
	err |= comedi_check_trigger_is_unique(cmd->stop_src);

	/* Step 2b : and mutually compatible */

	अगर (err)
		वापस 2;

	/* Step 3: check अगर arguments are trivially valid */

	err |= comedi_check_trigger_arg_is(&cmd->start_arg, 0);

	अगर (high_speed) अणु
		/*
		 * In high speed mode microframes are possible.
		 * However, during one microframe we can roughly
		 * sample two channels. Thus, the more channels
		 * are in the channel list the more समय we need.
		 */
		err |= comedi_check_trigger_arg_min(&cmd->scan_begin_arg,
						    (125000 * पूर्णांकerval));
	पूर्ण अन्यथा अणु
		/* full speed */
		/* 1kHz scans every USB frame */
		err |= comedi_check_trigger_arg_min(&cmd->scan_begin_arg,
						    1000000);
	पूर्ण

	err |= comedi_check_trigger_arg_is(&cmd->scan_end_arg,
					   cmd->chanlist_len);

	अगर (cmd->stop_src == TRIG_COUNT)
		err |= comedi_check_trigger_arg_min(&cmd->stop_arg, 1);
	अन्यथा	/* TRIG_NONE */
		err |= comedi_check_trigger_arg_is(&cmd->stop_arg, 0);

	अगर (err)
		वापस 3;

	/* Step 4: fix up any arguments */

	पंचांगp = roundकरोwn(cmd->scan_begin_arg, high_speed ? 125000 : 1000000);
	err |= comedi_check_trigger_arg_is(&cmd->scan_begin_arg, पंचांगp);

	अगर (err)
		वापस 4;

	वापस 0;
पूर्ण

/*
 * creates the ADC command क्रम the MAX1271
 * range is the range value from comedi
 */
अटल व्योम create_adc_command(अचिन्हित पूर्णांक chan,
			       u8 *muxsg0, u8 *muxsg1)
अणु
	अगर (chan < 8)
		(*muxsg0) = (*muxsg0) | (1 << chan);
	अन्यथा अगर (chan < 16)
		(*muxsg1) = (*muxsg1) | (1 << (chan - 8));
पूर्ण

अटल पूर्णांक usbbuxsigma_send_cmd(काष्ठा comedi_device *dev, पूर्णांक cmd_type)
अणु
	काष्ठा usb_device *usb = comedi_to_usb_dev(dev);
	काष्ठा usbduxsigma_निजी *devpriv = dev->निजी;
	पूर्णांक nsent;

	devpriv->dux_commands[0] = cmd_type;

	वापस usb_bulk_msg(usb, usb_sndbulkpipe(usb, 1),
			    devpriv->dux_commands, SIZखातापूर्णDUXBUFFER,
			    &nsent, BULK_TIMEOUT);
पूर्ण

अटल पूर्णांक usbduxsigma_receive_cmd(काष्ठा comedi_device *dev, पूर्णांक command)
अणु
	काष्ठा usb_device *usb = comedi_to_usb_dev(dev);
	काष्ठा usbduxsigma_निजी *devpriv = dev->निजी;
	पूर्णांक nrec;
	पूर्णांक ret;
	पूर्णांक i;

	क्रम (i = 0; i < RETRIES; i++) अणु
		ret = usb_bulk_msg(usb, usb_rcvbulkpipe(usb, 8),
				   devpriv->insn_buf, SIZEINSNBUF,
				   &nrec, BULK_TIMEOUT);
		अगर (ret < 0)
			वापस ret;

		अगर (devpriv->insn_buf[0] == command)
			वापस 0;
	पूर्ण
	/*
	 * This is only reached अगर the data has been requested a
	 * couple of बार and the command was not received.
	 */
	वापस -EFAULT;
पूर्ण

अटल पूर्णांक usbduxsigma_ai_पूर्णांकtrig(काष्ठा comedi_device *dev,
				  काष्ठा comedi_subdevice *s,
				  अचिन्हित पूर्णांक trig_num)
अणु
	काष्ठा usbduxsigma_निजी *devpriv = dev->निजी;
	काष्ठा comedi_cmd *cmd = &s->async->cmd;
	पूर्णांक ret;

	अगर (trig_num != cmd->start_arg)
		वापस -EINVAL;

	mutex_lock(&devpriv->mut);
	अगर (!devpriv->ai_cmd_running) अणु
		devpriv->ai_cmd_running = 1;
		ret = usbduxsigma_submit_urbs(dev, devpriv->ai_urbs,
					      devpriv->n_ai_urbs, 1);
		अगर (ret < 0) अणु
			devpriv->ai_cmd_running = 0;
			mutex_unlock(&devpriv->mut);
			वापस ret;
		पूर्ण
		s->async->पूर्णांकtrig = शून्य;
	पूर्ण
	mutex_unlock(&devpriv->mut);

	वापस 1;
पूर्ण

अटल पूर्णांक usbduxsigma_ai_cmd(काष्ठा comedi_device *dev,
			      काष्ठा comedi_subdevice *s)
अणु
	काष्ठा usbduxsigma_निजी *devpriv = dev->निजी;
	काष्ठा comedi_cmd *cmd = &s->async->cmd;
	अचिन्हित पूर्णांक len = cmd->chanlist_len;
	u8 muxsg0 = 0;
	u8 muxsg1 = 0;
	u8 sysred = 0;
	पूर्णांक ret;
	पूर्णांक i;

	mutex_lock(&devpriv->mut);

	अगर (devpriv->high_speed) अणु
		/*
		 * every 2 channels get a समय winकरोw of 125us. Thus, अगर we
		 * sample all 16 channels we need 1ms. If we sample only one
		 * channel we need only 125us
		 */
		अचिन्हित पूर्णांक पूर्णांकerval = usbduxsigma_chans_to_पूर्णांकerval(len);

		devpriv->ai_पूर्णांकerval = पूर्णांकerval;
		devpriv->ai_समयr = cmd->scan_begin_arg / (125000 * पूर्णांकerval);
	पूर्ण अन्यथा अणु
		/* पूर्णांकerval always 1ms */
		devpriv->ai_पूर्णांकerval = 1;
		devpriv->ai_समयr = cmd->scan_begin_arg / 1000000;
	पूर्ण

	क्रम (i = 0; i < len; i++) अणु
		अचिन्हित पूर्णांक chan  = CR_CHAN(cmd->chanlist[i]);

		create_adc_command(chan, &muxsg0, &muxsg1);
	पूर्ण

	devpriv->dux_commands[1] = devpriv->ai_पूर्णांकerval;
	devpriv->dux_commands[2] = len;  /* num channels per समय step */
	devpriv->dux_commands[3] = 0x12; /* CONFIG0 */
	devpriv->dux_commands[4] = 0x03; /* CONFIG1: 23kHz sample, delay 0us */
	devpriv->dux_commands[5] = 0x00; /* CONFIG3: dअगरf. channels off */
	devpriv->dux_commands[6] = muxsg0;
	devpriv->dux_commands[7] = muxsg1;
	devpriv->dux_commands[8] = sysred;

	ret = usbbuxsigma_send_cmd(dev, USBBUXSIGMA_AD_CMD);
	अगर (ret < 0) अणु
		mutex_unlock(&devpriv->mut);
		वापस ret;
	पूर्ण

	devpriv->ai_counter = devpriv->ai_समयr;

	अगर (cmd->start_src == TRIG_NOW) अणु
		/* enable this acquisition operation */
		devpriv->ai_cmd_running = 1;
		ret = usbduxsigma_submit_urbs(dev, devpriv->ai_urbs,
					      devpriv->n_ai_urbs, 1);
		अगर (ret < 0) अणु
			devpriv->ai_cmd_running = 0;
			mutex_unlock(&devpriv->mut);
			वापस ret;
		पूर्ण
		s->async->पूर्णांकtrig = शून्य;
	पूर्ण अन्यथा अणु	/* TRIG_INT */
		s->async->पूर्णांकtrig = usbduxsigma_ai_पूर्णांकtrig;
	पूर्ण

	mutex_unlock(&devpriv->mut);

	वापस 0;
पूर्ण

अटल पूर्णांक usbduxsigma_ai_insn_पढ़ो(काष्ठा comedi_device *dev,
				    काष्ठा comedi_subdevice *s,
				    काष्ठा comedi_insn *insn,
				    अचिन्हित पूर्णांक *data)
अणु
	काष्ठा usbduxsigma_निजी *devpriv = dev->निजी;
	अचिन्हित पूर्णांक chan = CR_CHAN(insn->chanspec);
	u8 muxsg0 = 0;
	u8 muxsg1 = 0;
	u8 sysred = 0;
	पूर्णांक ret;
	पूर्णांक i;

	mutex_lock(&devpriv->mut);
	अगर (devpriv->ai_cmd_running) अणु
		mutex_unlock(&devpriv->mut);
		वापस -EBUSY;
	पूर्ण

	create_adc_command(chan, &muxsg0, &muxsg1);

	/* Mode 0 is used to get a single conversion on demand */
	devpriv->dux_commands[1] = 0x16; /* CONFIG0: chopper on */
	devpriv->dux_commands[2] = 0x80; /* CONFIG1: 2kHz sampling rate */
	devpriv->dux_commands[3] = 0x00; /* CONFIG3: dअगरf. channels off */
	devpriv->dux_commands[4] = muxsg0;
	devpriv->dux_commands[5] = muxsg1;
	devpriv->dux_commands[6] = sysred;

	/* adc commands */
	ret = usbbuxsigma_send_cmd(dev, USBDUXSIGMA_SINGLE_AD_CMD);
	अगर (ret < 0) अणु
		mutex_unlock(&devpriv->mut);
		वापस ret;
	पूर्ण

	क्रम (i = 0; i < insn->n; i++) अणु
		u32 val;

		ret = usbduxsigma_receive_cmd(dev, USBDUXSIGMA_SINGLE_AD_CMD);
		अगर (ret < 0) अणु
			mutex_unlock(&devpriv->mut);
			वापस ret;
		पूर्ण

		/* 32 bits big endian from the A/D converter */
		val = be32_to_cpu(get_unaligned((__be32
						 *)(devpriv->insn_buf + 1)));
		val &= 0x00ffffff;	/* strip status byte */
		data[i] = comedi_offset_munge(s, val);
	पूर्ण
	mutex_unlock(&devpriv->mut);

	वापस insn->n;
पूर्ण

अटल पूर्णांक usbduxsigma_ao_insn_पढ़ो(काष्ठा comedi_device *dev,
				    काष्ठा comedi_subdevice *s,
				    काष्ठा comedi_insn *insn,
				    अचिन्हित पूर्णांक *data)
अणु
	काष्ठा usbduxsigma_निजी *devpriv = dev->निजी;
	पूर्णांक ret;

	mutex_lock(&devpriv->mut);
	ret = comedi_पढ़ोback_insn_पढ़ो(dev, s, insn, data);
	mutex_unlock(&devpriv->mut);

	वापस ret;
पूर्ण

अटल पूर्णांक usbduxsigma_ao_insn_ग_लिखो(काष्ठा comedi_device *dev,
				     काष्ठा comedi_subdevice *s,
				     काष्ठा comedi_insn *insn,
				     अचिन्हित पूर्णांक *data)
अणु
	काष्ठा usbduxsigma_निजी *devpriv = dev->निजी;
	अचिन्हित पूर्णांक chan = CR_CHAN(insn->chanspec);
	पूर्णांक ret;
	पूर्णांक i;

	mutex_lock(&devpriv->mut);
	अगर (devpriv->ao_cmd_running) अणु
		mutex_unlock(&devpriv->mut);
		वापस -EBUSY;
	पूर्ण

	क्रम (i = 0; i < insn->n; i++) अणु
		devpriv->dux_commands[1] = 1;		/* num channels */
		devpriv->dux_commands[2] = data[i];	/* value */
		devpriv->dux_commands[3] = chan;	/* channel number */
		ret = usbbuxsigma_send_cmd(dev, USBDUXSIGMA_DA_CMD);
		अगर (ret < 0) अणु
			mutex_unlock(&devpriv->mut);
			वापस ret;
		पूर्ण
		s->पढ़ोback[chan] = data[i];
	पूर्ण
	mutex_unlock(&devpriv->mut);

	वापस insn->n;
पूर्ण

अटल पूर्णांक usbduxsigma_ao_पूर्णांकtrig(काष्ठा comedi_device *dev,
				  काष्ठा comedi_subdevice *s,
				  अचिन्हित पूर्णांक trig_num)
अणु
	काष्ठा usbduxsigma_निजी *devpriv = dev->निजी;
	काष्ठा comedi_cmd *cmd = &s->async->cmd;
	पूर्णांक ret;

	अगर (trig_num != cmd->start_arg)
		वापस -EINVAL;

	mutex_lock(&devpriv->mut);
	अगर (!devpriv->ao_cmd_running) अणु
		devpriv->ao_cmd_running = 1;
		ret = usbduxsigma_submit_urbs(dev, devpriv->ao_urbs,
					      devpriv->n_ao_urbs, 0);
		अगर (ret < 0) अणु
			devpriv->ao_cmd_running = 0;
			mutex_unlock(&devpriv->mut);
			वापस ret;
		पूर्ण
		s->async->पूर्णांकtrig = शून्य;
	पूर्ण
	mutex_unlock(&devpriv->mut);

	वापस 1;
पूर्ण

अटल पूर्णांक usbduxsigma_ao_cmdtest(काष्ठा comedi_device *dev,
				  काष्ठा comedi_subdevice *s,
				  काष्ठा comedi_cmd *cmd)
अणु
	काष्ठा usbduxsigma_निजी *devpriv = dev->निजी;
	अचिन्हित पूर्णांक पंचांगp;
	पूर्णांक err = 0;

	/* Step 1 : check अगर triggers are trivially valid */

	err |= comedi_check_trigger_src(&cmd->start_src, TRIG_NOW | TRIG_INT);

	/*
	 * For now, always use "scan" timing with all channels updated at once
	 * (cmd->scan_begin_src == TRIG_TIMER, cmd->convert_src == TRIG_NOW).
	 *
	 * In a future version, "convert" timing with channels updated
	 * inभागually may be supported in high speed mode
	 * (cmd->scan_begin_src == TRIG_FOLLOW, cmd->convert_src == TRIG_TIMER).
	 */
	err |= comedi_check_trigger_src(&cmd->scan_begin_src, TRIG_TIMER);
	err |= comedi_check_trigger_src(&cmd->convert_src, TRIG_NOW);
	err |= comedi_check_trigger_src(&cmd->scan_end_src, TRIG_COUNT);
	err |= comedi_check_trigger_src(&cmd->stop_src, TRIG_COUNT | TRIG_NONE);

	अगर (err) अणु
		mutex_unlock(&devpriv->mut);
		वापस 1;
	पूर्ण

	/* Step 2a : make sure trigger sources are unique */

	err |= comedi_check_trigger_is_unique(cmd->start_src);
	err |= comedi_check_trigger_is_unique(cmd->stop_src);

	/* Step 2b : and mutually compatible */

	अगर (err)
		वापस 2;

	/* Step 3: check अगर arguments are trivially valid */

	err |= comedi_check_trigger_arg_is(&cmd->start_arg, 0);

	err |= comedi_check_trigger_arg_min(&cmd->scan_begin_arg, 1000000);

	err |= comedi_check_trigger_arg_is(&cmd->scan_end_arg,
					   cmd->chanlist_len);

	अगर (cmd->stop_src == TRIG_COUNT)
		err |= comedi_check_trigger_arg_min(&cmd->stop_arg, 1);
	अन्यथा	/* TRIG_NONE */
		err |= comedi_check_trigger_arg_is(&cmd->stop_arg, 0);

	अगर (err)
		वापस 3;

	/* Step 4: fix up any arguments */

	पंचांगp = roundकरोwn(cmd->scan_begin_arg, 1000000);
	err |= comedi_check_trigger_arg_is(&cmd->scan_begin_arg, पंचांगp);

	अगर (err)
		वापस 4;

	वापस 0;
पूर्ण

अटल पूर्णांक usbduxsigma_ao_cmd(काष्ठा comedi_device *dev,
			      काष्ठा comedi_subdevice *s)
अणु
	काष्ठा usbduxsigma_निजी *devpriv = dev->निजी;
	काष्ठा comedi_cmd *cmd = &s->async->cmd;
	पूर्णांक ret;

	mutex_lock(&devpriv->mut);

	/*
	 * For now, only "scan" timing is supported.  A future version may
	 * support "convert" timing in high speed mode.
	 *
	 * Timing of the scan: every 1ms all channels updated at once.
	 */
	devpriv->ao_समयr = cmd->scan_begin_arg / 1000000;

	devpriv->ao_counter = devpriv->ao_समयr;

	अगर (cmd->start_src == TRIG_NOW) अणु
		/* enable this acquisition operation */
		devpriv->ao_cmd_running = 1;
		ret = usbduxsigma_submit_urbs(dev, devpriv->ao_urbs,
					      devpriv->n_ao_urbs, 0);
		अगर (ret < 0) अणु
			devpriv->ao_cmd_running = 0;
			mutex_unlock(&devpriv->mut);
			वापस ret;
		पूर्ण
		s->async->पूर्णांकtrig = शून्य;
	पूर्ण अन्यथा अणु	/* TRIG_INT */
		s->async->पूर्णांकtrig = usbduxsigma_ao_पूर्णांकtrig;
	पूर्ण

	mutex_unlock(&devpriv->mut);

	वापस 0;
पूर्ण

अटल पूर्णांक usbduxsigma_dio_insn_config(काष्ठा comedi_device *dev,
				       काष्ठा comedi_subdevice *s,
				       काष्ठा comedi_insn *insn,
				       अचिन्हित पूर्णांक *data)
अणु
	पूर्णांक ret;

	ret = comedi_dio_insn_config(dev, s, insn, data, 0);
	अगर (ret)
		वापस ret;

	/*
	 * We करोn't tell the firmware here as it would take 8 frames
	 * to submit the inक्रमmation. We करो it in the (*insn_bits).
	 */
	वापस insn->n;
पूर्ण

अटल पूर्णांक usbduxsigma_dio_insn_bits(काष्ठा comedi_device *dev,
				     काष्ठा comedi_subdevice *s,
				     काष्ठा comedi_insn *insn,
				     अचिन्हित पूर्णांक *data)
अणु
	काष्ठा usbduxsigma_निजी *devpriv = dev->निजी;
	पूर्णांक ret;

	mutex_lock(&devpriv->mut);

	comedi_dio_update_state(s, data);

	/* Always update the hardware. See the (*insn_config). */
	devpriv->dux_commands[1] = s->io_bits & 0xff;
	devpriv->dux_commands[4] = s->state & 0xff;
	devpriv->dux_commands[2] = (s->io_bits >> 8) & 0xff;
	devpriv->dux_commands[5] = (s->state >> 8) & 0xff;
	devpriv->dux_commands[3] = (s->io_bits >> 16) & 0xff;
	devpriv->dux_commands[6] = (s->state >> 16) & 0xff;

	ret = usbbuxsigma_send_cmd(dev, USBDUXSIGMA_DIO_BITS_CMD);
	अगर (ret < 0)
		जाओ करोne;
	ret = usbduxsigma_receive_cmd(dev, USBDUXSIGMA_DIO_BITS_CMD);
	अगर (ret < 0)
		जाओ करोne;

	s->state = devpriv->insn_buf[1] |
		   (devpriv->insn_buf[2] << 8) |
		   (devpriv->insn_buf[3] << 16);

	data[1] = s->state;
	ret = insn->n;

करोne:
	mutex_unlock(&devpriv->mut);

	वापस ret;
पूर्ण

अटल व्योम usbduxsigma_pwm_stop(काष्ठा comedi_device *dev, पूर्णांक करो_unlink)
अणु
	काष्ठा usbduxsigma_निजी *devpriv = dev->निजी;

	अगर (करो_unlink) अणु
		अगर (devpriv->pwm_urb)
			usb_समाप्त_urb(devpriv->pwm_urb);
	पूर्ण

	devpriv->pwm_cmd_running = 0;
पूर्ण

अटल पूर्णांक usbduxsigma_pwm_cancel(काष्ठा comedi_device *dev,
				  काष्ठा comedi_subdevice *s)
अणु
	काष्ठा usbduxsigma_निजी *devpriv = dev->निजी;

	/* unlink only अगर it is really running */
	usbduxsigma_pwm_stop(dev, devpriv->pwm_cmd_running);

	वापस usbbuxsigma_send_cmd(dev, USBDUXSIGMA_PWM_OFF_CMD);
पूर्ण

अटल व्योम usbduxsigma_pwm_urb_complete(काष्ठा urb *urb)
अणु
	काष्ठा comedi_device *dev = urb->context;
	काष्ठा usbduxsigma_निजी *devpriv = dev->निजी;
	पूर्णांक ret;

	चयन (urb->status) अणु
	हाल 0:
		/* success */
		अवरोध;

	हाल -ECONNRESET:
	हाल -ENOENT:
	हाल -ESHUTDOWN:
	हाल -ECONNABORTED:
		/* happens after an unlink command */
		अगर (devpriv->pwm_cmd_running)
			usbduxsigma_pwm_stop(dev, 0);	/* w/o unlink */
		वापस;

	शेष:
		/* a real error */
		अगर (devpriv->pwm_cmd_running) अणु
			dev_err(dev->class_dev, "non-zero urb status (%d)\n",
				urb->status);
			usbduxsigma_pwm_stop(dev, 0);	/* w/o unlink */
		पूर्ण
		वापस;
	पूर्ण

	अगर (!devpriv->pwm_cmd_running)
		वापस;

	urb->transfer_buffer_length = devpriv->pwm_buf_sz;
	urb->dev = comedi_to_usb_dev(dev);
	urb->status = 0;
	ret = usb_submit_urb(urb, GFP_ATOMIC);
	अगर (ret < 0) अणु
		dev_err(dev->class_dev, "urb resubmit failed (%d)\n", ret);
		अगर (ret == -EL2NSYNC)
			dev_err(dev->class_dev,
				"buggy USB host controller or bug in IRQ handler\n");
		usbduxsigma_pwm_stop(dev, 0);	/* w/o unlink */
	पूर्ण
पूर्ण

अटल पूर्णांक usbduxsigma_submit_pwm_urb(काष्ठा comedi_device *dev)
अणु
	काष्ठा usb_device *usb = comedi_to_usb_dev(dev);
	काष्ठा usbduxsigma_निजी *devpriv = dev->निजी;
	काष्ठा urb *urb = devpriv->pwm_urb;

	/* in हाल of a resubmission after an unlink... */
	usb_fill_bulk_urb(urb, usb, usb_sndbulkpipe(usb, 4),
			  urb->transfer_buffer, devpriv->pwm_buf_sz,
			  usbduxsigma_pwm_urb_complete, dev);

	वापस usb_submit_urb(urb, GFP_ATOMIC);
पूर्ण

अटल पूर्णांक usbduxsigma_pwm_period(काष्ठा comedi_device *dev,
				  काष्ठा comedi_subdevice *s,
				  अचिन्हित पूर्णांक period)
अणु
	काष्ठा usbduxsigma_निजी *devpriv = dev->निजी;
	पूर्णांक fx2delay;

	अगर (period < MIN_PWM_PERIOD)
		वापस -EAGAIN;

	fx2delay = (period / (6 * 512 * 1000 / 33)) - 6;
	अगर (fx2delay > 255)
		वापस -EAGAIN;

	devpriv->pwm_delay = fx2delay;
	devpriv->pwm_period = period;
	वापस 0;
पूर्ण

अटल पूर्णांक usbduxsigma_pwm_start(काष्ठा comedi_device *dev,
				 काष्ठा comedi_subdevice *s)
अणु
	काष्ठा usbduxsigma_निजी *devpriv = dev->निजी;
	पूर्णांक ret;

	अगर (devpriv->pwm_cmd_running)
		वापस 0;

	devpriv->dux_commands[1] = devpriv->pwm_delay;
	ret = usbbuxsigma_send_cmd(dev, USBDUXSIGMA_PWM_ON_CMD);
	अगर (ret < 0)
		वापस ret;

	स_रखो(devpriv->pwm_urb->transfer_buffer, 0, devpriv->pwm_buf_sz);

	devpriv->pwm_cmd_running = 1;
	ret = usbduxsigma_submit_pwm_urb(dev);
	अगर (ret < 0) अणु
		devpriv->pwm_cmd_running = 0;
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम usbduxsigma_pwm_pattern(काष्ठा comedi_device *dev,
				    काष्ठा comedi_subdevice *s,
				    अचिन्हित पूर्णांक chan,
				    अचिन्हित पूर्णांक value,
				    अचिन्हित पूर्णांक sign)
अणु
	काष्ठा usbduxsigma_निजी *devpriv = dev->निजी;
	अक्षर pwm_mask = (1 << chan);	/* DIO bit क्रम the PWM data */
	अक्षर sgn_mask = (16 << chan);	/* DIO bit क्रम the sign */
	अक्षर *buf = (अक्षर *)(devpriv->pwm_urb->transfer_buffer);
	पूर्णांक szbuf = devpriv->pwm_buf_sz;
	पूर्णांक i;

	क्रम (i = 0; i < szbuf; i++) अणु
		अक्षर c = *buf;

		c &= ~pwm_mask;
		अगर (i < value)
			c |= pwm_mask;
		अगर (!sign)
			c &= ~sgn_mask;
		अन्यथा
			c |= sgn_mask;
		*buf++ = c;
	पूर्ण
पूर्ण

अटल पूर्णांक usbduxsigma_pwm_ग_लिखो(काष्ठा comedi_device *dev,
				 काष्ठा comedi_subdevice *s,
				 काष्ठा comedi_insn *insn,
				 अचिन्हित पूर्णांक *data)
अणु
	अचिन्हित पूर्णांक chan = CR_CHAN(insn->chanspec);

	/*
	 * It करोesn't make sense to support more than one value here
	 * because it would just overग_लिखो the PWM buffer.
	 */
	अगर (insn->n != 1)
		वापस -EINVAL;

	/*
	 * The sign is set via a special INSN only, this gives us 8 bits
	 * क्रम normal operation, sign is 0 by शेष.
	 */
	usbduxsigma_pwm_pattern(dev, s, chan, data[0], 0);

	वापस insn->n;
पूर्ण

अटल पूर्णांक usbduxsigma_pwm_config(काष्ठा comedi_device *dev,
				  काष्ठा comedi_subdevice *s,
				  काष्ठा comedi_insn *insn,
				  अचिन्हित पूर्णांक *data)
अणु
	काष्ठा usbduxsigma_निजी *devpriv = dev->निजी;
	अचिन्हित पूर्णांक chan = CR_CHAN(insn->chanspec);

	चयन (data[0]) अणु
	हाल INSN_CONFIG_ARM:
		/*
		 * अगर not zero the PWM is limited to a certain समय which is
		 * not supported here
		 */
		अगर (data[1] != 0)
			वापस -EINVAL;
		वापस usbduxsigma_pwm_start(dev, s);
	हाल INSN_CONFIG_DISARM:
		वापस usbduxsigma_pwm_cancel(dev, s);
	हाल INSN_CONFIG_GET_PWM_STATUS:
		data[1] = devpriv->pwm_cmd_running;
		वापस 0;
	हाल INSN_CONFIG_PWM_SET_PERIOD:
		वापस usbduxsigma_pwm_period(dev, s, data[1]);
	हाल INSN_CONFIG_PWM_GET_PERIOD:
		data[1] = devpriv->pwm_period;
		वापस 0;
	हाल INSN_CONFIG_PWM_SET_H_BRIDGE:
		/*
		 * data[1] = value
		 * data[2] = sign (क्रम a relay)
		 */
		usbduxsigma_pwm_pattern(dev, s, chan, data[1], (data[2] != 0));
		वापस 0;
	हाल INSN_CONFIG_PWM_GET_H_BRIDGE:
		/* values are not kept in this driver, nothing to वापस */
		वापस -EINVAL;
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक usbduxsigma_माला_लोtatusinfo(काष्ठा comedi_device *dev, पूर्णांक chan)
अणु
	काष्ठा comedi_subdevice *s = dev->पढ़ो_subdev;
	काष्ठा usbduxsigma_निजी *devpriv = dev->निजी;
	u8 sysred;
	u32 val;
	पूर्णांक ret;

	चयन (chan) अणु
	शेष:
	हाल 0:
		sysred = 0;		/* ADC zero */
		अवरोध;
	हाल 1:
		sysred = 1;		/* ADC offset */
		अवरोध;
	हाल 2:
		sysred = 4;		/* VCC */
		अवरोध;
	हाल 3:
		sysred = 8;		/* temperature */
		अवरोध;
	हाल 4:
		sysred = 16;		/* gain */
		अवरोध;
	हाल 5:
		sysred =  32;		/* ref */
		अवरोध;
	पूर्ण

	devpriv->dux_commands[1] = 0x12; /* CONFIG0 */
	devpriv->dux_commands[2] = 0x80; /* CONFIG1: 2kHz sampling rate */
	devpriv->dux_commands[3] = 0x00; /* CONFIG3: dअगरf. channels off */
	devpriv->dux_commands[4] = 0;
	devpriv->dux_commands[5] = 0;
	devpriv->dux_commands[6] = sysred;
	ret = usbbuxsigma_send_cmd(dev, USBDUXSIGMA_SINGLE_AD_CMD);
	अगर (ret < 0)
		वापस ret;

	ret = usbduxsigma_receive_cmd(dev, USBDUXSIGMA_SINGLE_AD_CMD);
	अगर (ret < 0)
		वापस ret;

	/* 32 bits big endian from the A/D converter */
	val = be32_to_cpu(get_unaligned((__be32 *)(devpriv->insn_buf + 1)));
	val &= 0x00ffffff;	/* strip status byte */

	वापस (पूर्णांक)comedi_offset_munge(s, val);
पूर्ण

अटल पूर्णांक usbduxsigma_firmware_upload(काष्ठा comedi_device *dev,
				       स्थिर u8 *data, माप_प्रकार size,
				       अचिन्हित दीर्घ context)
अणु
	काष्ठा usb_device *usb = comedi_to_usb_dev(dev);
	u8 *buf;
	u8 *पंचांगp;
	पूर्णांक ret;

	अगर (!data)
		वापस 0;

	अगर (size > FIRMWARE_MAX_LEN) अणु
		dev_err(dev->class_dev, "firmware binary too large for FX2\n");
		वापस -ENOMEM;
	पूर्ण

	/* we generate a local buffer क्रम the firmware */
	buf = kmemdup(data, size, GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;

	/* we need a दो_स्मृति'ed buffer क्रम usb_control_msg() */
	पंचांगp = kदो_स्मृति(1, GFP_KERNEL);
	अगर (!पंचांगp) अणु
		kमुक्त(buf);
		वापस -ENOMEM;
	पूर्ण

	/* stop the current firmware on the device */
	*पंचांगp = 1;	/* 7f92 to one */
	ret = usb_control_msg(usb, usb_sndctrlpipe(usb, 0),
			      USBDUXSUB_FIRMWARE,
			      VENDOR_सूची_OUT,
			      USBDUXSUB_CPUCS, 0x0000,
			      पंचांगp, 1,
			      BULK_TIMEOUT);
	अगर (ret < 0) अणु
		dev_err(dev->class_dev, "can not stop firmware\n");
		जाओ करोne;
	पूर्ण

	/* upload the new firmware to the device */
	ret = usb_control_msg(usb, usb_sndctrlpipe(usb, 0),
			      USBDUXSUB_FIRMWARE,
			      VENDOR_सूची_OUT,
			      0, 0x0000,
			      buf, size,
			      BULK_TIMEOUT);
	अगर (ret < 0) अणु
		dev_err(dev->class_dev, "firmware upload failed\n");
		जाओ करोne;
	पूर्ण

	/* start the new firmware on the device */
	*पंचांगp = 0;	/* 7f92 to zero */
	ret = usb_control_msg(usb, usb_sndctrlpipe(usb, 0),
			      USBDUXSUB_FIRMWARE,
			      VENDOR_सूची_OUT,
			      USBDUXSUB_CPUCS, 0x0000,
			      पंचांगp, 1,
			      BULK_TIMEOUT);
	अगर (ret < 0)
		dev_err(dev->class_dev, "can not start firmware\n");

करोne:
	kमुक्त(पंचांगp);
	kमुक्त(buf);
	वापस ret;
पूर्ण

अटल पूर्णांक usbduxsigma_alloc_usb_buffers(काष्ठा comedi_device *dev)
अणु
	काष्ठा usb_device *usb = comedi_to_usb_dev(dev);
	काष्ठा usbduxsigma_निजी *devpriv = dev->निजी;
	काष्ठा urb *urb;
	पूर्णांक i;

	devpriv->dux_commands = kzalloc(SIZखातापूर्णDUXBUFFER, GFP_KERNEL);
	devpriv->in_buf = kzalloc(SIZEINBUF, GFP_KERNEL);
	devpriv->insn_buf = kzalloc(SIZEINSNBUF, GFP_KERNEL);
	devpriv->ai_urbs = kसुस्मृति(devpriv->n_ai_urbs, माप(urb), GFP_KERNEL);
	devpriv->ao_urbs = kसुस्मृति(devpriv->n_ao_urbs, माप(urb), GFP_KERNEL);
	अगर (!devpriv->dux_commands || !devpriv->in_buf || !devpriv->insn_buf ||
	    !devpriv->ai_urbs || !devpriv->ao_urbs)
		वापस -ENOMEM;

	क्रम (i = 0; i < devpriv->n_ai_urbs; i++) अणु
		/* one frame: 1ms */
		urb = usb_alloc_urb(1, GFP_KERNEL);
		अगर (!urb)
			वापस -ENOMEM;
		devpriv->ai_urbs[i] = urb;
		urb->dev = usb;
		/* will be filled later with a poपूर्णांकer to the comedi-device */
		/* and ONLY then the urb should be submitted */
		urb->context = शून्य;
		urb->pipe = usb_rcvisocpipe(usb, 6);
		urb->transfer_flags = URB_ISO_ASAP;
		urb->transfer_buffer = kzalloc(SIZEINBUF, GFP_KERNEL);
		अगर (!urb->transfer_buffer)
			वापस -ENOMEM;
		urb->complete = usbduxsigma_ai_urb_complete;
		urb->number_of_packets = 1;
		urb->transfer_buffer_length = SIZEINBUF;
		urb->iso_frame_desc[0].offset = 0;
		urb->iso_frame_desc[0].length = SIZEINBUF;
	पूर्ण

	क्रम (i = 0; i < devpriv->n_ao_urbs; i++) अणु
		/* one frame: 1ms */
		urb = usb_alloc_urb(1, GFP_KERNEL);
		अगर (!urb)
			वापस -ENOMEM;
		devpriv->ao_urbs[i] = urb;
		urb->dev = usb;
		/* will be filled later with a poपूर्णांकer to the comedi-device */
		/* and ONLY then the urb should be submitted */
		urb->context = शून्य;
		urb->pipe = usb_sndisocpipe(usb, 2);
		urb->transfer_flags = URB_ISO_ASAP;
		urb->transfer_buffer = kzalloc(SIZEOUTBUF, GFP_KERNEL);
		अगर (!urb->transfer_buffer)
			वापस -ENOMEM;
		urb->complete = usbduxsigma_ao_urb_complete;
		urb->number_of_packets = 1;
		urb->transfer_buffer_length = SIZEOUTBUF;
		urb->iso_frame_desc[0].offset = 0;
		urb->iso_frame_desc[0].length = SIZEOUTBUF;
		urb->पूर्णांकerval = 1;	/* (u)frames */
	पूर्ण

	अगर (devpriv->pwm_buf_sz) अणु
		urb = usb_alloc_urb(0, GFP_KERNEL);
		अगर (!urb)
			वापस -ENOMEM;
		devpriv->pwm_urb = urb;

		urb->transfer_buffer = kzalloc(devpriv->pwm_buf_sz,
					       GFP_KERNEL);
		अगर (!urb->transfer_buffer)
			वापस -ENOMEM;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम usbduxsigma_मुक्त_usb_buffers(काष्ठा comedi_device *dev)
अणु
	काष्ठा usbduxsigma_निजी *devpriv = dev->निजी;
	काष्ठा urb *urb;
	पूर्णांक i;

	urb = devpriv->pwm_urb;
	अगर (urb) अणु
		kमुक्त(urb->transfer_buffer);
		usb_मुक्त_urb(urb);
	पूर्ण
	अगर (devpriv->ao_urbs) अणु
		क्रम (i = 0; i < devpriv->n_ao_urbs; i++) अणु
			urb = devpriv->ao_urbs[i];
			अगर (urb) अणु
				kमुक्त(urb->transfer_buffer);
				usb_मुक्त_urb(urb);
			पूर्ण
		पूर्ण
		kमुक्त(devpriv->ao_urbs);
	पूर्ण
	अगर (devpriv->ai_urbs) अणु
		क्रम (i = 0; i < devpriv->n_ai_urbs; i++) अणु
			urb = devpriv->ai_urbs[i];
			अगर (urb) अणु
				kमुक्त(urb->transfer_buffer);
				usb_मुक्त_urb(urb);
			पूर्ण
		पूर्ण
		kमुक्त(devpriv->ai_urbs);
	पूर्ण
	kमुक्त(devpriv->insn_buf);
	kमुक्त(devpriv->in_buf);
	kमुक्त(devpriv->dux_commands);
पूर्ण

अटल पूर्णांक usbduxsigma_स्वतः_attach(काष्ठा comedi_device *dev,
				   अचिन्हित दीर्घ context_unused)
अणु
	काष्ठा usb_पूर्णांकerface *पूर्णांकf = comedi_to_usb_पूर्णांकerface(dev);
	काष्ठा usb_device *usb = comedi_to_usb_dev(dev);
	काष्ठा usbduxsigma_निजी *devpriv;
	काष्ठा comedi_subdevice *s;
	पूर्णांक offset;
	पूर्णांक ret;

	devpriv = comedi_alloc_devpriv(dev, माप(*devpriv));
	अगर (!devpriv)
		वापस -ENOMEM;

	mutex_init(&devpriv->mut);

	usb_set_पूर्णांकfdata(पूर्णांकf, devpriv);

	devpriv->high_speed = (usb->speed == USB_SPEED_HIGH);
	अगर (devpriv->high_speed) अणु
		devpriv->n_ai_urbs = NUMOFINBUFFERSHIGH;
		devpriv->n_ao_urbs = NUMOFOUTBUFFERSHIGH;
		devpriv->pwm_buf_sz = 512;
	पूर्ण अन्यथा अणु
		devpriv->n_ai_urbs = NUMOFINBUFFERSFULL;
		devpriv->n_ao_urbs = NUMOFOUTBUFFERSFULL;
	पूर्ण

	ret = usbduxsigma_alloc_usb_buffers(dev);
	अगर (ret)
		वापस ret;

	/* setting to alternate setting 3: enabling iso ep and bulk ep. */
	ret = usb_set_पूर्णांकerface(usb, पूर्णांकf->altsetting->desc.bInterfaceNumber,
				3);
	अगर (ret < 0) अणु
		dev_err(dev->class_dev,
			"could not set alternate setting 3 in high speed\n");
		वापस ret;
	पूर्ण

	ret = comedi_load_firmware(dev, &usb->dev, FIRMWARE,
				   usbduxsigma_firmware_upload, 0);
	अगर (ret)
		वापस ret;

	ret = comedi_alloc_subdevices(dev, (devpriv->high_speed) ? 4 : 3);
	अगर (ret)
		वापस ret;

	/* Analog Input subdevice */
	s = &dev->subdevices[0];
	dev->पढ़ो_subdev = s;
	s->type		= COMEDI_SUBD_AI;
	s->subdev_flags	= SDF_READABLE | SDF_GROUND | SDF_CMD_READ | SDF_LSAMPL;
	s->n_chan	= NUMCHANNELS;
	s->len_chanlist	= NUMCHANNELS;
	s->maxdata	= 0x00ffffff;
	s->range_table	= &usbduxsigma_ai_range;
	s->insn_पढ़ो	= usbduxsigma_ai_insn_पढ़ो;
	s->करो_cmdtest	= usbduxsigma_ai_cmdtest;
	s->करो_cmd	= usbduxsigma_ai_cmd;
	s->cancel	= usbduxsigma_ai_cancel;

	/* Analog Output subdevice */
	s = &dev->subdevices[1];
	dev->ग_लिखो_subdev = s;
	s->type		= COMEDI_SUBD_AO;
	s->subdev_flags	= SDF_WRITABLE | SDF_GROUND | SDF_CMD_WRITE;
	s->n_chan	= 4;
	s->len_chanlist	= s->n_chan;
	s->maxdata	= 0x00ff;
	s->range_table	= &range_unipolar2_5;
	s->insn_ग_लिखो	= usbduxsigma_ao_insn_ग_लिखो;
	s->insn_पढ़ो	= usbduxsigma_ao_insn_पढ़ो;
	s->करो_cmdtest	= usbduxsigma_ao_cmdtest;
	s->करो_cmd	= usbduxsigma_ao_cmd;
	s->cancel	= usbduxsigma_ao_cancel;

	ret = comedi_alloc_subdev_पढ़ोback(s);
	अगर (ret)
		वापस ret;

	/* Digital I/O subdevice */
	s = &dev->subdevices[2];
	s->type		= COMEDI_SUBD_DIO;
	s->subdev_flags	= SDF_READABLE | SDF_WRITABLE;
	s->n_chan	= 24;
	s->maxdata	= 1;
	s->range_table	= &range_digital;
	s->insn_bits	= usbduxsigma_dio_insn_bits;
	s->insn_config	= usbduxsigma_dio_insn_config;

	अगर (devpriv->high_speed) अणु
		/* Timer / pwm subdevice */
		s = &dev->subdevices[3];
		s->type		= COMEDI_SUBD_PWM;
		s->subdev_flags	= SDF_WRITABLE | SDF_PWM_HBRIDGE;
		s->n_chan	= 8;
		s->maxdata	= devpriv->pwm_buf_sz;
		s->insn_ग_लिखो	= usbduxsigma_pwm_ग_लिखो;
		s->insn_config	= usbduxsigma_pwm_config;

		usbduxsigma_pwm_period(dev, s, PWM_DEFAULT_PERIOD);
	पूर्ण

	offset = usbduxsigma_माला_लोtatusinfo(dev, 0);
	अगर (offset < 0) अणु
		dev_err(dev->class_dev,
			"Communication to USBDUXSIGMA failed! Check firmware and cabling.\n");
		वापस offset;
	पूर्ण

	dev_info(dev->class_dev, "ADC_zero = %x\n", offset);

	वापस 0;
पूर्ण

अटल व्योम usbduxsigma_detach(काष्ठा comedi_device *dev)
अणु
	काष्ठा usb_पूर्णांकerface *पूर्णांकf = comedi_to_usb_पूर्णांकerface(dev);
	काष्ठा usbduxsigma_निजी *devpriv = dev->निजी;

	usb_set_पूर्णांकfdata(पूर्णांकf, शून्य);

	अगर (!devpriv)
		वापस;

	mutex_lock(&devpriv->mut);

	/* क्रमce unlink all urbs */
	usbduxsigma_ai_stop(dev, 1);
	usbduxsigma_ao_stop(dev, 1);
	usbduxsigma_pwm_stop(dev, 1);

	usbduxsigma_मुक्त_usb_buffers(dev);

	mutex_unlock(&devpriv->mut);

	mutex_destroy(&devpriv->mut);
पूर्ण

अटल काष्ठा comedi_driver usbduxsigma_driver = अणु
	.driver_name	= "usbduxsigma",
	.module		= THIS_MODULE,
	.स्वतः_attach	= usbduxsigma_स्वतः_attach,
	.detach		= usbduxsigma_detach,
पूर्ण;

अटल पूर्णांक usbduxsigma_usb_probe(काष्ठा usb_पूर्णांकerface *पूर्णांकf,
				 स्थिर काष्ठा usb_device_id *id)
अणु
	वापस comedi_usb_स्वतः_config(पूर्णांकf, &usbduxsigma_driver, 0);
पूर्ण

अटल स्थिर काष्ठा usb_device_id usbduxsigma_usb_table[] = अणु
	अणु USB_DEVICE(0x13d8, 0x0020) पूर्ण,
	अणु USB_DEVICE(0x13d8, 0x0021) पूर्ण,
	अणु USB_DEVICE(0x13d8, 0x0022) पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(usb, usbduxsigma_usb_table);

अटल काष्ठा usb_driver usbduxsigma_usb_driver = अणु
	.name		= "usbduxsigma",
	.probe		= usbduxsigma_usb_probe,
	.disconnect	= comedi_usb_स्वतः_unconfig,
	.id_table	= usbduxsigma_usb_table,
पूर्ण;
module_comedi_usb_driver(usbduxsigma_driver, usbduxsigma_usb_driver);

MODULE_AUTHOR("Bernd Porr, mail@berndporr.me.uk");
MODULE_DESCRIPTION("Stirling/ITL USB-DUX SIGMA -- mail@berndporr.me.uk");
MODULE_LICENSE("GPL");
MODULE_FIRMWARE(FIRMWARE);
