<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * usbdux.c
 * Copyright (C) 2003-2014 Bernd Porr, mail@berndporr.me.uk
 */

/*
 * Driver: usbdux
 * Description: University of Stirling USB DAQ & INCITE Technology Limited
 * Devices: [ITL] USB-DUX (usbdux)
 * Author: Bernd Porr <mail@berndporr.me.uk>
 * Updated: 10 Oct 2014
 * Status: Stable
 *
 * Connection scheme क्रम the counter at the digital port:
 * 0=/CLK0, 1=UP/DOWN0, 2=RESET0, 4=/CLK1, 5=UP/DOWN1, 6=RESET1.
 * The sampling rate of the counter is approximately 500Hz.
 *
 * Note that under USB2.0 the length of the channel list determines
 * the max sampling rate. If you sample only one channel you get 8kHz
 * sampling rate. If you sample two channels you get 4kHz and so on.
 */

/*
 * I must give credit here to Chris Baugher who
 * wrote the driver क्रम AT-MIO-16d. I used some parts of this
 * driver. I also must give credits to David Brownell
 * who supported me with the USB development.
 *
 * Bernd Porr
 *
 *
 * Revision history:
 * 0.94: D/A output should work now with any channel list combinations
 * 0.95: .owner commented out क्रम kernel vers below 2.4.19
 *       sanity checks in ai/ao_cmd
 * 0.96: trying to get it working with 2.6, moved all memory alloc to comedi's
 *       attach final USB IDs
 *       moved memory allocation completely to the corresponding comedi
 *       functions firmware upload is by fxload and no दीर्घer by comedi (due to
 *       क्रमागतeration)
 * 0.97: USB IDs received, adjusted table
 * 0.98: SMP, locking, memory alloc: moved all usb memory alloc
 *       to the usb subप्रणाली and moved all comedi related memory
 *       alloc to comedi.
 *       | kernel | registration | usbdux-usb | usbdux-comedi | comedi |
 * 0.99: USB 2.0: changed protocol to isochronous transfer
 *                IRQ transfer is too buggy and too risky in 2.0
 *                क्रम the high speed ISO transfer is now a working version
 *                available
 * 0.99b: Increased the iso transfer buffer क्रम high sp.to 10 buffers. Some VIA
 *        chipsets miss out IRQs. Deeper buffering is needed.
 * 1.00: full USB 2.0 support क्रम the A/D converter. Now: max 8kHz sampling
 *       rate.
 *       Firmware vers 1.00 is needed क्रम this.
 *       Two 16 bit up/करोwn/reset counter with a sampling rate of 1kHz
 *       And loads of cleaning up, in particular streamlining the
 *       bulk transfers.
 * 1.1:  moved EP4 transfers to EP1 to make space क्रम a PWM output on EP4
 * 1.2:  added PWM support via EP4
 * 2.0:  PWM seems to be stable and is not पूर्णांकerfering with the other functions
 * 2.1:  changed PWM API
 * 2.2:  added firmware kernel request to fix an udev problem
 * 2.3:  corrected a bug in bulk समयouts which were far too लघु
 * 2.4:  fixed a bug which causes the driver to hang when it ran out of data.
 *       Thanks to Jan-Matthias Braun and Ian to spot the bug and fix it.
 *
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/input.h>
#समावेश <linux/fcntl.h>
#समावेश <linux/compiler.h>

#समावेश "../comedi_usb.h"

/* स्थिरants क्रम firmware upload and करोwnload */
#घोषणा USBDUX_FIRMWARE		"usbdux_firmware.bin"
#घोषणा USBDUX_FIRMWARE_MAX_LEN	0x2000
#घोषणा USBDUX_FIRMWARE_CMD	0xa0
#घोषणा VENDOR_सूची_IN		0xc0
#घोषणा VENDOR_सूची_OUT		0x40
#घोषणा USBDUX_CPU_CS		0xe600

/* usbdux bulk transfer commands */
#घोषणा USBDUX_CMD_MULT_AI	0
#घोषणा USBDUX_CMD_AO		1
#घोषणा USBDUX_CMD_DIO_CFG	2
#घोषणा USBDUX_CMD_DIO_BITS	3
#घोषणा USBDUX_CMD_SINGLE_AI	4
#घोषणा USBDUX_CMD_TIMER_RD	5
#घोषणा USBDUX_CMD_TIMER_WR	6
#घोषणा USBDUX_CMD_PWM_ON	7
#घोषणा USBDUX_CMD_PWM_OFF	8

/* समयout क्रम the USB-transfer in ms */
#घोषणा BULK_TIMEOUT		1000

/* 300Hz max frequ under PWM */
#घोषणा MIN_PWM_PERIOD		((दीर्घ)(1E9 / 300))

/* Default PWM frequency */
#घोषणा PWM_DEFAULT_PERIOD	((दीर्घ)(1E9 / 100))

/* Size of one A/D value */
#घोषणा SIZEADIN		((माप(u16)))

/*
 * Size of the input-buffer IN BYTES
 * Always multiple of 8 क्रम 8 microframes which is needed in the highspeed mode
 */
#घोषणा SIZEINBUF		(8 * SIZEADIN)

/* 16 bytes. */
#घोषणा SIZEINSNBUF		16

/* size of one value क्रम the D/A converter: channel and value */
#घोषणा SIZEDAOUT		((माप(u8) + माप(u16)))

/*
 * Size of the output-buffer in bytes
 * Actually only the first 4 triplets are used but क्रम the
 * high speed mode we need to pad it to 8 (microframes).
 */
#घोषणा SIZEOUTBUF		(8 * SIZEDAOUT)

/*
 * Size of the buffer क्रम the dux commands: just now max size is determined
 * by the analogue out + command byte + panic bytes...
 */
#घोषणा SIZखातापूर्णDUXBUFFER		(8 * SIZEDAOUT + 2)

/* Number of in-URBs which receive the data: min=2 */
#घोषणा NUMOFINBUFFERSFULL	5

/* Number of out-URBs which send the data: min=2 */
#घोषणा NUMOFOUTBUFFERSFULL	5

/* Number of in-URBs which receive the data: min=5 */
/* must have more buffers due to buggy USB ctr */
#घोषणा NUMOFINBUFFERSHIGH	10

/* Number of out-URBs which send the data: min=5 */
/* must have more buffers due to buggy USB ctr */
#घोषणा NUMOFOUTBUFFERSHIGH	10

/* number of retries to get the right dux command */
#घोषणा RETRIES			10

अटल स्थिर काष्ठा comedi_lrange range_usbdux_ai_range = अणु
	4, अणु
		BIP_RANGE(4.096),
		BIP_RANGE(4.096 / 2),
		UNI_RANGE(4.096),
		UNI_RANGE(4.096 / 2)
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा comedi_lrange range_usbdux_ao_range = अणु
	2, अणु
		BIP_RANGE(4.096),
		UNI_RANGE(4.096)
	पूर्ण
पूर्ण;

काष्ठा usbdux_निजी अणु
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
	__le16 *in_buf;
	/* input buffer क्रम single insn */
	__le16 *insn_buf;

	अचिन्हित पूर्णांक high_speed:1;
	अचिन्हित पूर्णांक ai_cmd_running:1;
	अचिन्हित पूर्णांक ao_cmd_running:1;
	अचिन्हित पूर्णांक pwm_cmd_running:1;

	/* समय between samples in units of the समयr */
	अचिन्हित पूर्णांक ai_समयr;
	अचिन्हित पूर्णांक ao_समयr;
	/* counter between aquisitions */
	अचिन्हित पूर्णांक ai_counter;
	अचिन्हित पूर्णांक ao_counter;
	/* पूर्णांकerval in frames/uframes */
	अचिन्हित पूर्णांक ai_पूर्णांकerval;
	/* commands */
	u8 *dux_commands;
	काष्ठा mutex mut;
पूर्ण;

अटल व्योम usbdux_unlink_urbs(काष्ठा urb **urbs, पूर्णांक num_urbs)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < num_urbs; i++)
		usb_समाप्त_urb(urbs[i]);
पूर्ण

अटल व्योम usbdux_ai_stop(काष्ठा comedi_device *dev, पूर्णांक करो_unlink)
अणु
	काष्ठा usbdux_निजी *devpriv = dev->निजी;

	अगर (करो_unlink && devpriv->ai_urbs)
		usbdux_unlink_urbs(devpriv->ai_urbs, devpriv->n_ai_urbs);

	devpriv->ai_cmd_running = 0;
पूर्ण

अटल पूर्णांक usbdux_ai_cancel(काष्ठा comedi_device *dev,
			    काष्ठा comedi_subdevice *s)
अणु
	काष्ठा usbdux_निजी *devpriv = dev->निजी;

	/* prevent other CPUs from submitting new commands just now */
	mutex_lock(&devpriv->mut);
	/* unlink only अगर the urb really has been submitted */
	usbdux_ai_stop(dev, devpriv->ai_cmd_running);
	mutex_unlock(&devpriv->mut);

	वापस 0;
पूर्ण

अटल व्योम usbduxsub_ai_handle_urb(काष्ठा comedi_device *dev,
				    काष्ठा comedi_subdevice *s,
				    काष्ठा urb *urb)
अणु
	काष्ठा usbdux_निजी *devpriv = dev->निजी;
	काष्ठा comedi_async *async = s->async;
	काष्ठा comedi_cmd *cmd = &async->cmd;
	पूर्णांक ret;
	पूर्णांक i;

	devpriv->ai_counter--;
	अगर (devpriv->ai_counter == 0) अणु
		devpriv->ai_counter = devpriv->ai_समयr;

		/* get the data from the USB bus and hand it over to comedi */
		क्रम (i = 0; i < cmd->chanlist_len; i++) अणु
			अचिन्हित पूर्णांक range = CR_RANGE(cmd->chanlist[i]);
			u16 val = le16_to_cpu(devpriv->in_buf[i]);

			/* bipolar data is two's-complement */
			अगर (comedi_range_is_bipolar(s, range))
				val = comedi_offset_munge(s, val);

			/* transfer data */
			अगर (!comedi_buf_ग_लिखो_samples(s, &val, 1))
				वापस;
		पूर्ण

		अगर (cmd->stop_src == TRIG_COUNT &&
		    async->scans_करोne >= cmd->stop_arg)
			async->events |= COMEDI_CB_EOA;
	पूर्ण

	/* अगर command is still running, resubmit urb */
	अगर (!(async->events & COMEDI_CB_CANCEL_MASK)) अणु
		urb->dev = comedi_to_usb_dev(dev);
		ret = usb_submit_urb(urb, GFP_ATOMIC);
		अगर (ret < 0) अणु
			dev_err(dev->class_dev,
				"urb resubmit failed in int-context! err=%d\n",
				ret);
			अगर (ret == -EL2NSYNC)
				dev_err(dev->class_dev,
					"buggy USB host controller or bug in IRQ handler!\n");
			async->events |= COMEDI_CB_ERROR;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम usbduxsub_ai_isoc_irq(काष्ठा urb *urb)
अणु
	काष्ठा comedi_device *dev = urb->context;
	काष्ठा comedi_subdevice *s = dev->पढ़ो_subdev;
	काष्ठा comedi_async *async = s->async;
	काष्ठा usbdux_निजी *devpriv = dev->निजी;

	/* निकास अगर not running a command, करो not resubmit urb */
	अगर (!devpriv->ai_cmd_running)
		वापस;

	चयन (urb->status) अणु
	हाल 0:
		/* copy the result in the transfer buffer */
		स_नकल(devpriv->in_buf, urb->transfer_buffer, SIZEINBUF);
		usbduxsub_ai_handle_urb(dev, s, urb);
		अवरोध;

	हाल -EILSEQ:
		/*
		 * error in the ISOchronous data
		 * we करोn't copy the data पूर्णांकo the transfer buffer
		 * and recycle the last data byte
		 */
		dev_dbg(dev->class_dev, "CRC error in ISO IN stream\n");
		usbduxsub_ai_handle_urb(dev, s, urb);
		अवरोध;

	हाल -ECONNRESET:
	हाल -ENOENT:
	हाल -ESHUTDOWN:
	हाल -ECONNABORTED:
		/* after an unlink command, unplug, ... etc */
		async->events |= COMEDI_CB_ERROR;
		अवरोध;

	शेष:
		/* a real error */
		dev_err(dev->class_dev,
			"Non-zero urb status received in ai intr context: %d\n",
			urb->status);
		async->events |= COMEDI_CB_ERROR;
		अवरोध;
	पूर्ण

	/*
	 * comedi_handle_events() cannot be used in this driver. The (*cancel)
	 * operation would unlink the urb.
	 */
	अगर (async->events & COMEDI_CB_CANCEL_MASK)
		usbdux_ai_stop(dev, 0);

	comedi_event(dev, s);
पूर्ण

अटल व्योम usbdux_ao_stop(काष्ठा comedi_device *dev, पूर्णांक करो_unlink)
अणु
	काष्ठा usbdux_निजी *devpriv = dev->निजी;

	अगर (करो_unlink && devpriv->ao_urbs)
		usbdux_unlink_urbs(devpriv->ao_urbs, devpriv->n_ao_urbs);

	devpriv->ao_cmd_running = 0;
पूर्ण

अटल पूर्णांक usbdux_ao_cancel(काष्ठा comedi_device *dev,
			    काष्ठा comedi_subdevice *s)
अणु
	काष्ठा usbdux_निजी *devpriv = dev->निजी;

	/* prevent other CPUs from submitting a command just now */
	mutex_lock(&devpriv->mut);
	/* unlink only अगर it is really running */
	usbdux_ao_stop(dev, devpriv->ao_cmd_running);
	mutex_unlock(&devpriv->mut);

	वापस 0;
पूर्ण

अटल व्योम usbduxsub_ao_handle_urb(काष्ठा comedi_device *dev,
				    काष्ठा comedi_subdevice *s,
				    काष्ठा urb *urb)
अणु
	काष्ठा usbdux_निजी *devpriv = dev->निजी;
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

			/* poपूर्णांकer to the DA */
			*datap++ = val & 0xff;
			*datap++ = (val >> 8) & 0xff;
			*datap++ = chan << 6;
			s->पढ़ोback[chan] = val;
		पूर्ण
	पूर्ण

	/* अगर command is still running, resubmit urb क्रम BULK transfer */
	अगर (!(async->events & COMEDI_CB_CANCEL_MASK)) अणु
		urb->transfer_buffer_length = SIZEOUTBUF;
		urb->dev = comedi_to_usb_dev(dev);
		urb->status = 0;
		अगर (devpriv->high_speed)
			urb->पूर्णांकerval = 8;	/* uframes */
		अन्यथा
			urb->पूर्णांकerval = 1;	/* frames */
		urb->number_of_packets = 1;
		urb->iso_frame_desc[0].offset = 0;
		urb->iso_frame_desc[0].length = SIZEOUTBUF;
		urb->iso_frame_desc[0].status = 0;
		ret = usb_submit_urb(urb, GFP_ATOMIC);
		अगर (ret < 0) अणु
			dev_err(dev->class_dev,
				"ao urb resubm failed in int-cont. ret=%d",
				ret);
			अगर (ret == -EL2NSYNC)
				dev_err(dev->class_dev,
					"buggy USB host controller or bug in IRQ handling!\n");
			async->events |= COMEDI_CB_ERROR;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम usbduxsub_ao_isoc_irq(काष्ठा urb *urb)
अणु
	काष्ठा comedi_device *dev = urb->context;
	काष्ठा comedi_subdevice *s = dev->ग_लिखो_subdev;
	काष्ठा comedi_async *async = s->async;
	काष्ठा usbdux_निजी *devpriv = dev->निजी;

	/* निकास अगर not running a command, करो not resubmit urb */
	अगर (!devpriv->ao_cmd_running)
		वापस;

	चयन (urb->status) अणु
	हाल 0:
		usbduxsub_ao_handle_urb(dev, s, urb);
		अवरोध;

	हाल -ECONNRESET:
	हाल -ENOENT:
	हाल -ESHUTDOWN:
	हाल -ECONNABORTED:
		/* after an unlink command, unplug, ... etc */
		async->events |= COMEDI_CB_ERROR;
		अवरोध;

	शेष:
		/* a real error */
		dev_err(dev->class_dev,
			"Non-zero urb status received in ao intr context: %d\n",
			urb->status);
		async->events |= COMEDI_CB_ERROR;
		अवरोध;
	पूर्ण

	/*
	 * comedi_handle_events() cannot be used in this driver. The (*cancel)
	 * operation would unlink the urb.
	 */
	अगर (async->events & COMEDI_CB_CANCEL_MASK)
		usbdux_ao_stop(dev, 0);

	comedi_event(dev, s);
पूर्ण

अटल पूर्णांक usbdux_submit_urbs(काष्ठा comedi_device *dev,
			      काष्ठा urb **urbs, पूर्णांक num_urbs,
			      पूर्णांक input_urb)
अणु
	काष्ठा usb_device *usb = comedi_to_usb_dev(dev);
	काष्ठा usbdux_निजी *devpriv = dev->निजी;
	काष्ठा urb *urb;
	पूर्णांक ret;
	पूर्णांक i;

	/* Submit all URBs and start the transfer on the bus */
	क्रम (i = 0; i < num_urbs; i++) अणु
		urb = urbs[i];

		/* in हाल of a resubmission after an unlink... */
		अगर (input_urb)
			urb->पूर्णांकerval = devpriv->ai_पूर्णांकerval;
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

अटल पूर्णांक usbdux_ai_cmdtest(काष्ठा comedi_device *dev,
			     काष्ठा comedi_subdevice *s, काष्ठा comedi_cmd *cmd)
अणु
	काष्ठा usbdux_निजी *devpriv = dev->निजी;
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

	अगर (cmd->scan_begin_src == TRIG_FOLLOW)	/* पूर्णांकernal trigger */
		err |= comedi_check_trigger_arg_is(&cmd->scan_begin_arg, 0);

	अगर (cmd->scan_begin_src == TRIG_TIMER) अणु
		/* full speed करोes 1kHz scans every USB frame */
		अचिन्हित पूर्णांक arg = 1000000;
		अचिन्हित पूर्णांक min_arg = arg;

		अगर (devpriv->high_speed) अणु
			/*
			 * In high speed mode microframes are possible.
			 * However, during one microframe we can roughly
			 * sample one channel. Thus, the more channels
			 * are in the channel list the more समय we need.
			 */
			पूर्णांक i = 1;

			/* find a घातer of 2 क्रम the number of channels */
			जबतक (i < cmd->chanlist_len)
				i = i * 2;

			arg /= 8;
			min_arg = arg * i;
		पूर्ण
		err |= comedi_check_trigger_arg_min(&cmd->scan_begin_arg,
						    min_arg);
		/* calc the real sampling rate with the rounding errors */
		arg = (cmd->scan_begin_arg / arg) * arg;
		err |= comedi_check_trigger_arg_is(&cmd->scan_begin_arg, arg);
	पूर्ण

	err |= comedi_check_trigger_arg_is(&cmd->scan_end_arg,
					   cmd->chanlist_len);

	अगर (cmd->stop_src == TRIG_COUNT)
		err |= comedi_check_trigger_arg_min(&cmd->stop_arg, 1);
	अन्यथा	/* TRIG_NONE */
		err |= comedi_check_trigger_arg_is(&cmd->stop_arg, 0);

	अगर (err)
		वापस 3;

	वापस 0;
पूर्ण

/*
 * creates the ADC command क्रम the MAX1271
 * range is the range value from comedi
 */
अटल u8 create_adc_command(अचिन्हित पूर्णांक chan, अचिन्हित पूर्णांक range)
अणु
	u8 p = (range <= 1);
	u8 r = ((range % 2) == 0);

	वापस (chan << 4) | ((p == 1) << 2) | ((r == 1) << 3);
पूर्ण

अटल पूर्णांक send_dux_commands(काष्ठा comedi_device *dev, अचिन्हित पूर्णांक cmd_type)
अणु
	काष्ठा usb_device *usb = comedi_to_usb_dev(dev);
	काष्ठा usbdux_निजी *devpriv = dev->निजी;
	पूर्णांक nsent;

	devpriv->dux_commands[0] = cmd_type;

	वापस usb_bulk_msg(usb, usb_sndbulkpipe(usb, 1),
			    devpriv->dux_commands, SIZखातापूर्णDUXBUFFER,
			    &nsent, BULK_TIMEOUT);
पूर्ण

अटल पूर्णांक receive_dux_commands(काष्ठा comedi_device *dev, अचिन्हित पूर्णांक command)
अणु
	काष्ठा usb_device *usb = comedi_to_usb_dev(dev);
	काष्ठा usbdux_निजी *devpriv = dev->निजी;
	पूर्णांक ret;
	पूर्णांक nrec;
	पूर्णांक i;

	क्रम (i = 0; i < RETRIES; i++) अणु
		ret = usb_bulk_msg(usb, usb_rcvbulkpipe(usb, 8),
				   devpriv->insn_buf, SIZEINSNBUF,
				   &nrec, BULK_TIMEOUT);
		अगर (ret < 0)
			वापस ret;
		अगर (le16_to_cpu(devpriv->insn_buf[0]) == command)
			वापस ret;
	पूर्ण
	/* command not received */
	वापस -EFAULT;
पूर्ण

अटल पूर्णांक usbdux_ai_पूर्णांकtrig(काष्ठा comedi_device *dev,
			     काष्ठा comedi_subdevice *s,
			     अचिन्हित पूर्णांक trig_num)
अणु
	काष्ठा usbdux_निजी *devpriv = dev->निजी;
	काष्ठा comedi_cmd *cmd = &s->async->cmd;
	पूर्णांक ret;

	अगर (trig_num != cmd->start_arg)
		वापस -EINVAL;

	mutex_lock(&devpriv->mut);

	अगर (!devpriv->ai_cmd_running) अणु
		devpriv->ai_cmd_running = 1;
		ret = usbdux_submit_urbs(dev, devpriv->ai_urbs,
					 devpriv->n_ai_urbs, 1);
		अगर (ret < 0) अणु
			devpriv->ai_cmd_running = 0;
			जाओ ai_trig_निकास;
		पूर्ण
		s->async->पूर्णांकtrig = शून्य;
	पूर्ण अन्यथा अणु
		ret = -EBUSY;
	पूर्ण

ai_trig_निकास:
	mutex_unlock(&devpriv->mut);
	वापस ret;
पूर्ण

अटल पूर्णांक usbdux_ai_cmd(काष्ठा comedi_device *dev, काष्ठा comedi_subdevice *s)
अणु
	काष्ठा usbdux_निजी *devpriv = dev->निजी;
	काष्ठा comedi_cmd *cmd = &s->async->cmd;
	पूर्णांक len = cmd->chanlist_len;
	पूर्णांक ret = -EBUSY;
	पूर्णांक i;

	/* block other CPUs from starting an ai_cmd */
	mutex_lock(&devpriv->mut);

	अगर (devpriv->ai_cmd_running)
		जाओ ai_cmd_निकास;

	devpriv->dux_commands[1] = len;
	क्रम (i = 0; i < len; ++i) अणु
		अचिन्हित पूर्णांक chan = CR_CHAN(cmd->chanlist[i]);
		अचिन्हित पूर्णांक range = CR_RANGE(cmd->chanlist[i]);

		devpriv->dux_commands[i + 2] = create_adc_command(chan, range);
	पूर्ण

	ret = send_dux_commands(dev, USBDUX_CMD_MULT_AI);
	अगर (ret < 0)
		जाओ ai_cmd_निकास;

	अगर (devpriv->high_speed) अणु
		/*
		 * every channel माला_लो a समय winकरोw of 125us. Thus, अगर we
		 * sample all 8 channels we need 1ms. If we sample only one
		 * channel we need only 125us
		 */
		devpriv->ai_पूर्णांकerval = 1;
		/* find a घातer of 2 क्रम the पूर्णांकerval */
		जबतक (devpriv->ai_पूर्णांकerval < len)
			devpriv->ai_पूर्णांकerval *= 2;

		devpriv->ai_समयr = cmd->scan_begin_arg /
				    (125000 * devpriv->ai_पूर्णांकerval);
	पूर्ण अन्यथा अणु
		/* पूर्णांकerval always 1ms */
		devpriv->ai_पूर्णांकerval = 1;
		devpriv->ai_समयr = cmd->scan_begin_arg / 1000000;
	पूर्ण
	अगर (devpriv->ai_समयr < 1) अणु
		ret = -EINVAL;
		जाओ ai_cmd_निकास;
	पूर्ण

	devpriv->ai_counter = devpriv->ai_समयr;

	अगर (cmd->start_src == TRIG_NOW) अणु
		/* enable this acquisition operation */
		devpriv->ai_cmd_running = 1;
		ret = usbdux_submit_urbs(dev, devpriv->ai_urbs,
					 devpriv->n_ai_urbs, 1);
		अगर (ret < 0) अणु
			devpriv->ai_cmd_running = 0;
			/* fixme: unlink here?? */
			जाओ ai_cmd_निकास;
		पूर्ण
		s->async->पूर्णांकtrig = शून्य;
	पूर्ण अन्यथा अणु
		/* TRIG_INT */
		/* करोn't enable the acquision operation */
		/* रुको क्रम an पूर्णांकernal संकेत */
		s->async->पूर्णांकtrig = usbdux_ai_पूर्णांकtrig;
	पूर्ण

ai_cmd_निकास:
	mutex_unlock(&devpriv->mut);

	वापस ret;
पूर्ण

/* Mode 0 is used to get a single conversion on demand */
अटल पूर्णांक usbdux_ai_insn_पढ़ो(काष्ठा comedi_device *dev,
			       काष्ठा comedi_subdevice *s,
			       काष्ठा comedi_insn *insn,
			       अचिन्हित पूर्णांक *data)
अणु
	काष्ठा usbdux_निजी *devpriv = dev->निजी;
	अचिन्हित पूर्णांक chan = CR_CHAN(insn->chanspec);
	अचिन्हित पूर्णांक range = CR_RANGE(insn->chanspec);
	अचिन्हित पूर्णांक val;
	पूर्णांक ret = -EBUSY;
	पूर्णांक i;

	mutex_lock(&devpriv->mut);

	अगर (devpriv->ai_cmd_running)
		जाओ ai_पढ़ो_निकास;

	/* set command क्रम the first channel */
	devpriv->dux_commands[1] = create_adc_command(chan, range);

	/* adc commands */
	ret = send_dux_commands(dev, USBDUX_CMD_SINGLE_AI);
	अगर (ret < 0)
		जाओ ai_पढ़ो_निकास;

	क्रम (i = 0; i < insn->n; i++) अणु
		ret = receive_dux_commands(dev, USBDUX_CMD_SINGLE_AI);
		अगर (ret < 0)
			जाओ ai_पढ़ो_निकास;

		val = le16_to_cpu(devpriv->insn_buf[1]);

		/* bipolar data is two's-complement */
		अगर (comedi_range_is_bipolar(s, range))
			val = comedi_offset_munge(s, val);

		data[i] = val;
	पूर्ण

ai_पढ़ो_निकास:
	mutex_unlock(&devpriv->mut);

	वापस ret ? ret : insn->n;
पूर्ण

अटल पूर्णांक usbdux_ao_insn_पढ़ो(काष्ठा comedi_device *dev,
			       काष्ठा comedi_subdevice *s,
			       काष्ठा comedi_insn *insn,
			       अचिन्हित पूर्णांक *data)
अणु
	काष्ठा usbdux_निजी *devpriv = dev->निजी;
	पूर्णांक ret;

	mutex_lock(&devpriv->mut);
	ret = comedi_पढ़ोback_insn_पढ़ो(dev, s, insn, data);
	mutex_unlock(&devpriv->mut);

	वापस ret;
पूर्ण

अटल पूर्णांक usbdux_ao_insn_ग_लिखो(काष्ठा comedi_device *dev,
				काष्ठा comedi_subdevice *s,
				काष्ठा comedi_insn *insn,
				अचिन्हित पूर्णांक *data)
अणु
	काष्ठा usbdux_निजी *devpriv = dev->निजी;
	अचिन्हित पूर्णांक chan = CR_CHAN(insn->chanspec);
	__le16 *p = (__le16 *)&devpriv->dux_commands[2];
	पूर्णांक ret = -EBUSY;
	पूर्णांक i;

	mutex_lock(&devpriv->mut);

	अगर (devpriv->ao_cmd_running)
		जाओ ao_ग_लिखो_निकास;

	/* number of channels: 1 */
	devpriv->dux_commands[1] = 1;
	/* channel number */
	devpriv->dux_commands[4] = chan << 6;

	क्रम (i = 0; i < insn->n; i++) अणु
		अचिन्हित पूर्णांक val = data[i];

		/* one 16 bit value */
		*p = cpu_to_le16(val);

		ret = send_dux_commands(dev, USBDUX_CMD_AO);
		अगर (ret < 0)
			जाओ ao_ग_लिखो_निकास;

		s->पढ़ोback[chan] = val;
	पूर्ण

ao_ग_लिखो_निकास:
	mutex_unlock(&devpriv->mut);

	वापस ret ? ret : insn->n;
पूर्ण

अटल पूर्णांक usbdux_ao_पूर्णांकtrig(काष्ठा comedi_device *dev,
			     काष्ठा comedi_subdevice *s,
			     अचिन्हित पूर्णांक trig_num)
अणु
	काष्ठा usbdux_निजी *devpriv = dev->निजी;
	काष्ठा comedi_cmd *cmd = &s->async->cmd;
	पूर्णांक ret;

	अगर (trig_num != cmd->start_arg)
		वापस -EINVAL;

	mutex_lock(&devpriv->mut);

	अगर (!devpriv->ao_cmd_running) अणु
		devpriv->ao_cmd_running = 1;
		ret = usbdux_submit_urbs(dev, devpriv->ao_urbs,
					 devpriv->n_ao_urbs, 0);
		अगर (ret < 0) अणु
			devpriv->ao_cmd_running = 0;
			जाओ ao_trig_निकास;
		पूर्ण
		s->async->पूर्णांकtrig = शून्य;
	पूर्ण अन्यथा अणु
		ret = -EBUSY;
	पूर्ण

ao_trig_निकास:
	mutex_unlock(&devpriv->mut);
	वापस ret;
पूर्ण

अटल पूर्णांक usbdux_ao_cmdtest(काष्ठा comedi_device *dev,
			     काष्ठा comedi_subdevice *s, काष्ठा comedi_cmd *cmd)
अणु
	पूर्णांक err = 0;
	अचिन्हित पूर्णांक flags;

	/* Step 1 : check अगर triggers are trivially valid */

	err |= comedi_check_trigger_src(&cmd->start_src, TRIG_NOW | TRIG_INT);

	अगर (0) अणु		/* (devpriv->high_speed) */
		/* the sampling rate is set by the coversion rate */
		flags = TRIG_FOLLOW;
	पूर्ण अन्यथा अणु
		/* start a new scan (output at once) with a समयr */
		flags = TRIG_TIMER;
	पूर्ण
	err |= comedi_check_trigger_src(&cmd->scan_begin_src, flags);

	अगर (0) अणु		/* (devpriv->high_speed) */
		/*
		 * in usb-2.0 only one conversion it transmitted
		 * but with 8kHz/n
		 */
		flags = TRIG_TIMER;
	पूर्ण अन्यथा अणु
		/*
		 * all conversion events happen simultaneously with
		 * a rate of 1kHz/n
		 */
		flags = TRIG_NOW;
	पूर्ण
	err |= comedi_check_trigger_src(&cmd->convert_src, flags);

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

	अगर (cmd->scan_begin_src == TRIG_FOLLOW)	/* पूर्णांकernal trigger */
		err |= comedi_check_trigger_arg_is(&cmd->scan_begin_arg, 0);

	अगर (cmd->scan_begin_src == TRIG_TIMER) अणु
		err |= comedi_check_trigger_arg_min(&cmd->scan_begin_arg,
						    1000000);
	पूर्ण

	/* not used now, is क्रम later use */
	अगर (cmd->convert_src == TRIG_TIMER)
		err |= comedi_check_trigger_arg_min(&cmd->convert_arg, 125000);

	err |= comedi_check_trigger_arg_is(&cmd->scan_end_arg,
					   cmd->chanlist_len);

	अगर (cmd->stop_src == TRIG_COUNT)
		err |= comedi_check_trigger_arg_min(&cmd->stop_arg, 1);
	अन्यथा	/* TRIG_NONE */
		err |= comedi_check_trigger_arg_is(&cmd->stop_arg, 0);

	अगर (err)
		वापस 3;

	वापस 0;
पूर्ण

अटल पूर्णांक usbdux_ao_cmd(काष्ठा comedi_device *dev, काष्ठा comedi_subdevice *s)
अणु
	काष्ठा usbdux_निजी *devpriv = dev->निजी;
	काष्ठा comedi_cmd *cmd = &s->async->cmd;
	पूर्णांक ret = -EBUSY;

	mutex_lock(&devpriv->mut);

	अगर (devpriv->ao_cmd_running)
		जाओ ao_cmd_निकास;

	/* we count in steps of 1ms (125us) */
	/* 125us mode not used yet */
	अगर (0) अणु		/* (devpriv->high_speed) */
		/* 125us */
		/* timing of the conversion itself: every 125 us */
		devpriv->ao_समयr = cmd->convert_arg / 125000;
	पूर्ण अन्यथा अणु
		/* 1ms */
		/* timing of the scan: we get all channels at once */
		devpriv->ao_समयr = cmd->scan_begin_arg / 1000000;
		अगर (devpriv->ao_समयr < 1) अणु
			ret = -EINVAL;
			जाओ ao_cmd_निकास;
		पूर्ण
	पूर्ण

	devpriv->ao_counter = devpriv->ao_समयr;

	अगर (cmd->start_src == TRIG_NOW) अणु
		/* enable this acquisition operation */
		devpriv->ao_cmd_running = 1;
		ret = usbdux_submit_urbs(dev, devpriv->ao_urbs,
					 devpriv->n_ao_urbs, 0);
		अगर (ret < 0) अणु
			devpriv->ao_cmd_running = 0;
			/* fixme: unlink here?? */
			जाओ ao_cmd_निकास;
		पूर्ण
		s->async->पूर्णांकtrig = शून्य;
	पूर्ण अन्यथा अणु
		/* TRIG_INT */
		/* submit the urbs later */
		/* रुको क्रम an पूर्णांकernal संकेत */
		s->async->पूर्णांकtrig = usbdux_ao_पूर्णांकtrig;
	पूर्ण

ao_cmd_निकास:
	mutex_unlock(&devpriv->mut);

	वापस ret;
पूर्ण

अटल पूर्णांक usbdux_dio_insn_config(काष्ठा comedi_device *dev,
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
	 * to submit the inक्रमmation. We करो it in the insn_bits.
	 */
	वापस insn->n;
पूर्ण

अटल पूर्णांक usbdux_dio_insn_bits(काष्ठा comedi_device *dev,
				काष्ठा comedi_subdevice *s,
				काष्ठा comedi_insn *insn,
				अचिन्हित पूर्णांक *data)
अणु
	काष्ठा usbdux_निजी *devpriv = dev->निजी;
	पूर्णांक ret;

	mutex_lock(&devpriv->mut);

	comedi_dio_update_state(s, data);

	/* Always update the hardware. See the (*insn_config). */
	devpriv->dux_commands[1] = s->io_bits;
	devpriv->dux_commands[2] = s->state;

	/*
	 * This command also tells the firmware to वापस
	 * the digital input lines.
	 */
	ret = send_dux_commands(dev, USBDUX_CMD_DIO_BITS);
	अगर (ret < 0)
		जाओ dio_निकास;
	ret = receive_dux_commands(dev, USBDUX_CMD_DIO_BITS);
	अगर (ret < 0)
		जाओ dio_निकास;

	data[1] = le16_to_cpu(devpriv->insn_buf[1]);

dio_निकास:
	mutex_unlock(&devpriv->mut);

	वापस ret ? ret : insn->n;
पूर्ण

अटल पूर्णांक usbdux_counter_पढ़ो(काष्ठा comedi_device *dev,
			       काष्ठा comedi_subdevice *s,
			       काष्ठा comedi_insn *insn,
			       अचिन्हित पूर्णांक *data)
अणु
	काष्ठा usbdux_निजी *devpriv = dev->निजी;
	अचिन्हित पूर्णांक chan = CR_CHAN(insn->chanspec);
	पूर्णांक ret = 0;
	पूर्णांक i;

	mutex_lock(&devpriv->mut);

	क्रम (i = 0; i < insn->n; i++) अणु
		ret = send_dux_commands(dev, USBDUX_CMD_TIMER_RD);
		अगर (ret < 0)
			जाओ counter_पढ़ो_निकास;
		ret = receive_dux_commands(dev, USBDUX_CMD_TIMER_RD);
		अगर (ret < 0)
			जाओ counter_पढ़ो_निकास;

		data[i] = le16_to_cpu(devpriv->insn_buf[chan + 1]);
	पूर्ण

counter_पढ़ो_निकास:
	mutex_unlock(&devpriv->mut);

	वापस ret ? ret : insn->n;
पूर्ण

अटल पूर्णांक usbdux_counter_ग_लिखो(काष्ठा comedi_device *dev,
				काष्ठा comedi_subdevice *s,
				काष्ठा comedi_insn *insn,
				अचिन्हित पूर्णांक *data)
अणु
	काष्ठा usbdux_निजी *devpriv = dev->निजी;
	अचिन्हित पूर्णांक chan = CR_CHAN(insn->chanspec);
	__le16 *p = (__le16 *)&devpriv->dux_commands[2];
	पूर्णांक ret = 0;
	पूर्णांक i;

	mutex_lock(&devpriv->mut);

	devpriv->dux_commands[1] = chan;

	क्रम (i = 0; i < insn->n; i++) अणु
		*p = cpu_to_le16(data[i]);

		ret = send_dux_commands(dev, USBDUX_CMD_TIMER_WR);
		अगर (ret < 0)
			अवरोध;
	पूर्ण

	mutex_unlock(&devpriv->mut);

	वापस ret ? ret : insn->n;
पूर्ण

अटल पूर्णांक usbdux_counter_config(काष्ठा comedi_device *dev,
				 काष्ठा comedi_subdevice *s,
				 काष्ठा comedi_insn *insn, अचिन्हित पूर्णांक *data)
अणु
	/* nothing to करो so far */
	वापस 2;
पूर्ण

अटल व्योम usbduxsub_unlink_pwm_urbs(काष्ठा comedi_device *dev)
अणु
	काष्ठा usbdux_निजी *devpriv = dev->निजी;

	usb_समाप्त_urb(devpriv->pwm_urb);
पूर्ण

अटल व्योम usbdux_pwm_stop(काष्ठा comedi_device *dev, पूर्णांक करो_unlink)
अणु
	काष्ठा usbdux_निजी *devpriv = dev->निजी;

	अगर (करो_unlink)
		usbduxsub_unlink_pwm_urbs(dev);

	devpriv->pwm_cmd_running = 0;
पूर्ण

अटल पूर्णांक usbdux_pwm_cancel(काष्ठा comedi_device *dev,
			     काष्ठा comedi_subdevice *s)
अणु
	काष्ठा usbdux_निजी *devpriv = dev->निजी;
	पूर्णांक ret;

	mutex_lock(&devpriv->mut);
	/* unlink only अगर it is really running */
	usbdux_pwm_stop(dev, devpriv->pwm_cmd_running);
	ret = send_dux_commands(dev, USBDUX_CMD_PWM_OFF);
	mutex_unlock(&devpriv->mut);

	वापस ret;
पूर्ण

अटल व्योम usbduxsub_pwm_irq(काष्ठा urb *urb)
अणु
	काष्ठा comedi_device *dev = urb->context;
	काष्ठा usbdux_निजी *devpriv = dev->निजी;
	पूर्णांक ret;

	चयन (urb->status) अणु
	हाल 0:
		/* success */
		अवरोध;

	हाल -ECONNRESET:
	हाल -ENOENT:
	हाल -ESHUTDOWN:
	हाल -ECONNABORTED:
		/*
		 * after an unlink command, unplug, ... etc
		 * no unlink needed here. Alपढ़ोy shutting करोwn.
		 */
		अगर (devpriv->pwm_cmd_running)
			usbdux_pwm_stop(dev, 0);

		वापस;

	शेष:
		/* a real error */
		अगर (devpriv->pwm_cmd_running) अणु
			dev_err(dev->class_dev,
				"Non-zero urb status received in pwm intr context: %d\n",
				urb->status);
			usbdux_pwm_stop(dev, 0);
		पूर्ण
		वापस;
	पूर्ण

	/* are we actually running? */
	अगर (!devpriv->pwm_cmd_running)
		वापस;

	urb->transfer_buffer_length = devpriv->pwm_buf_sz;
	urb->dev = comedi_to_usb_dev(dev);
	urb->status = 0;
	अगर (devpriv->pwm_cmd_running) अणु
		ret = usb_submit_urb(urb, GFP_ATOMIC);
		अगर (ret < 0) अणु
			dev_err(dev->class_dev,
				"pwm urb resubm failed in int-cont. ret=%d",
				ret);
			अगर (ret == -EL2NSYNC)
				dev_err(dev->class_dev,
					"buggy USB host controller or bug in IRQ handling!\n");

			/* करोn't करो an unlink here */
			usbdux_pwm_stop(dev, 0);
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक usbduxsub_submit_pwm_urbs(काष्ठा comedi_device *dev)
अणु
	काष्ठा usb_device *usb = comedi_to_usb_dev(dev);
	काष्ठा usbdux_निजी *devpriv = dev->निजी;
	काष्ठा urb *urb = devpriv->pwm_urb;

	/* in हाल of a resubmission after an unlink... */
	usb_fill_bulk_urb(urb, usb, usb_sndbulkpipe(usb, 4),
			  urb->transfer_buffer,
			  devpriv->pwm_buf_sz,
			  usbduxsub_pwm_irq,
			  dev);

	वापस usb_submit_urb(urb, GFP_ATOMIC);
पूर्ण

अटल पूर्णांक usbdux_pwm_period(काष्ठा comedi_device *dev,
			     काष्ठा comedi_subdevice *s,
			     अचिन्हित पूर्णांक period)
अणु
	काष्ठा usbdux_निजी *devpriv = dev->निजी;
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

अटल पूर्णांक usbdux_pwm_start(काष्ठा comedi_device *dev,
			    काष्ठा comedi_subdevice *s)
अणु
	काष्ठा usbdux_निजी *devpriv = dev->निजी;
	पूर्णांक ret = 0;

	mutex_lock(&devpriv->mut);

	अगर (devpriv->pwm_cmd_running)
		जाओ pwm_start_निकास;

	devpriv->dux_commands[1] = devpriv->pwm_delay;
	ret = send_dux_commands(dev, USBDUX_CMD_PWM_ON);
	अगर (ret < 0)
		जाओ pwm_start_निकास;

	/* initialise the buffer */
	स_रखो(devpriv->pwm_urb->transfer_buffer, 0, devpriv->pwm_buf_sz);

	devpriv->pwm_cmd_running = 1;
	ret = usbduxsub_submit_pwm_urbs(dev);
	अगर (ret < 0)
		devpriv->pwm_cmd_running = 0;

pwm_start_निकास:
	mutex_unlock(&devpriv->mut);

	वापस ret;
पूर्ण

अटल व्योम usbdux_pwm_pattern(काष्ठा comedi_device *dev,
			       काष्ठा comedi_subdevice *s,
			       अचिन्हित पूर्णांक chan,
			       अचिन्हित पूर्णांक value,
			       अचिन्हित पूर्णांक sign)
अणु
	काष्ठा usbdux_निजी *devpriv = dev->निजी;
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

अटल पूर्णांक usbdux_pwm_ग_लिखो(काष्ठा comedi_device *dev,
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
	usbdux_pwm_pattern(dev, s, chan, data[0], 0);

	वापस insn->n;
पूर्ण

अटल पूर्णांक usbdux_pwm_config(काष्ठा comedi_device *dev,
			     काष्ठा comedi_subdevice *s,
			     काष्ठा comedi_insn *insn,
			     अचिन्हित पूर्णांक *data)
अणु
	काष्ठा usbdux_निजी *devpriv = dev->निजी;
	अचिन्हित पूर्णांक chan = CR_CHAN(insn->chanspec);

	चयन (data[0]) अणु
	हाल INSN_CONFIG_ARM:
		/*
		 * अगर not zero the PWM is limited to a certain समय which is
		 * not supported here
		 */
		अगर (data[1] != 0)
			वापस -EINVAL;
		वापस usbdux_pwm_start(dev, s);
	हाल INSN_CONFIG_DISARM:
		वापस usbdux_pwm_cancel(dev, s);
	हाल INSN_CONFIG_GET_PWM_STATUS:
		data[1] = devpriv->pwm_cmd_running;
		वापस 0;
	हाल INSN_CONFIG_PWM_SET_PERIOD:
		वापस usbdux_pwm_period(dev, s, data[1]);
	हाल INSN_CONFIG_PWM_GET_PERIOD:
		data[1] = devpriv->pwm_period;
		वापस 0;
	हाल INSN_CONFIG_PWM_SET_H_BRIDGE:
		/*
		 * data[1] = value
		 * data[2] = sign (क्रम a relay)
		 */
		usbdux_pwm_pattern(dev, s, chan, data[1], (data[2] != 0));
		वापस 0;
	हाल INSN_CONFIG_PWM_GET_H_BRIDGE:
		/* values are not kept in this driver, nothing to वापस here */
		वापस -EINVAL;
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक usbdux_firmware_upload(काष्ठा comedi_device *dev,
				  स्थिर u8 *data, माप_प्रकार size,
				  अचिन्हित दीर्घ context)
अणु
	काष्ठा usb_device *usb = comedi_to_usb_dev(dev);
	u8 *buf;
	u8 *पंचांगp;
	पूर्णांक ret;

	अगर (!data)
		वापस 0;

	अगर (size > USBDUX_FIRMWARE_MAX_LEN) अणु
		dev_err(dev->class_dev,
			"usbdux firmware binary it too large for FX2.\n");
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
			      USBDUX_FIRMWARE_CMD,
			      VENDOR_सूची_OUT,
			      USBDUX_CPU_CS, 0x0000,
			      पंचांगp, 1,
			      BULK_TIMEOUT);
	अगर (ret < 0) अणु
		dev_err(dev->class_dev, "can not stop firmware\n");
		जाओ करोne;
	पूर्ण

	/* upload the new firmware to the device */
	ret = usb_control_msg(usb, usb_sndctrlpipe(usb, 0),
			      USBDUX_FIRMWARE_CMD,
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
			      USBDUX_FIRMWARE_CMD,
			      VENDOR_सूची_OUT,
			      USBDUX_CPU_CS, 0x0000,
			      पंचांगp, 1,
			      BULK_TIMEOUT);
	अगर (ret < 0)
		dev_err(dev->class_dev, "can not start firmware\n");

करोne:
	kमुक्त(पंचांगp);
	kमुक्त(buf);
	वापस ret;
पूर्ण

अटल पूर्णांक usbdux_alloc_usb_buffers(काष्ठा comedi_device *dev)
अणु
	काष्ठा usb_device *usb = comedi_to_usb_dev(dev);
	काष्ठा usbdux_निजी *devpriv = dev->निजी;
	काष्ठा urb *urb;
	पूर्णांक i;

	devpriv->dux_commands = kzalloc(SIZखातापूर्णDUXBUFFER, GFP_KERNEL);
	devpriv->in_buf = kzalloc(SIZEINBUF, GFP_KERNEL);
	devpriv->insn_buf = kzalloc(SIZEINSNBUF, GFP_KERNEL);
	devpriv->ai_urbs = kसुस्मृति(devpriv->n_ai_urbs, माप(व्योम *),
				   GFP_KERNEL);
	devpriv->ao_urbs = kसुस्मृति(devpriv->n_ao_urbs, माप(व्योम *),
				   GFP_KERNEL);
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
		urb->context = dev;
		urb->pipe = usb_rcvisocpipe(usb, 6);
		urb->transfer_flags = URB_ISO_ASAP;
		urb->transfer_buffer = kzalloc(SIZEINBUF, GFP_KERNEL);
		अगर (!urb->transfer_buffer)
			वापस -ENOMEM;

		urb->complete = usbduxsub_ai_isoc_irq;
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
		urb->context = dev;
		urb->pipe = usb_sndisocpipe(usb, 2);
		urb->transfer_flags = URB_ISO_ASAP;
		urb->transfer_buffer = kzalloc(SIZEOUTBUF, GFP_KERNEL);
		अगर (!urb->transfer_buffer)
			वापस -ENOMEM;

		urb->complete = usbduxsub_ao_isoc_irq;
		urb->number_of_packets = 1;
		urb->transfer_buffer_length = SIZEOUTBUF;
		urb->iso_frame_desc[0].offset = 0;
		urb->iso_frame_desc[0].length = SIZEOUTBUF;
		अगर (devpriv->high_speed)
			urb->पूर्णांकerval = 8;	/* uframes */
		अन्यथा
			urb->पूर्णांकerval = 1;	/* frames */
	पूर्ण

	/* pwm */
	अगर (devpriv->pwm_buf_sz) अणु
		urb = usb_alloc_urb(0, GFP_KERNEL);
		अगर (!urb)
			वापस -ENOMEM;
		devpriv->pwm_urb = urb;

		/* max bulk ep size in high speed */
		urb->transfer_buffer = kzalloc(devpriv->pwm_buf_sz,
					       GFP_KERNEL);
		अगर (!urb->transfer_buffer)
			वापस -ENOMEM;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम usbdux_मुक्त_usb_buffers(काष्ठा comedi_device *dev)
अणु
	काष्ठा usbdux_निजी *devpriv = dev->निजी;
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

अटल पूर्णांक usbdux_स्वतः_attach(काष्ठा comedi_device *dev,
			      अचिन्हित दीर्घ context_unused)
अणु
	काष्ठा usb_पूर्णांकerface *पूर्णांकf = comedi_to_usb_पूर्णांकerface(dev);
	काष्ठा usb_device *usb = comedi_to_usb_dev(dev);
	काष्ठा usbdux_निजी *devpriv;
	काष्ठा comedi_subdevice *s;
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

	ret = usbdux_alloc_usb_buffers(dev);
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

	ret = comedi_load_firmware(dev, &usb->dev, USBDUX_FIRMWARE,
				   usbdux_firmware_upload, 0);
	अगर (ret < 0)
		वापस ret;

	ret = comedi_alloc_subdevices(dev, (devpriv->high_speed) ? 5 : 4);
	अगर (ret)
		वापस ret;

	/* Analog Input subdevice */
	s = &dev->subdevices[0];
	dev->पढ़ो_subdev = s;
	s->type		= COMEDI_SUBD_AI;
	s->subdev_flags	= SDF_READABLE | SDF_GROUND | SDF_CMD_READ;
	s->n_chan	= 8;
	s->maxdata	= 0x0fff;
	s->len_chanlist	= 8;
	s->range_table	= &range_usbdux_ai_range;
	s->insn_पढ़ो	= usbdux_ai_insn_पढ़ो;
	s->करो_cmdtest	= usbdux_ai_cmdtest;
	s->करो_cmd	= usbdux_ai_cmd;
	s->cancel	= usbdux_ai_cancel;

	/* Analog Output subdevice */
	s = &dev->subdevices[1];
	dev->ग_लिखो_subdev = s;
	s->type		= COMEDI_SUBD_AO;
	s->subdev_flags	= SDF_WRITABLE | SDF_GROUND | SDF_CMD_WRITE;
	s->n_chan	= 4;
	s->maxdata	= 0x0fff;
	s->len_chanlist	= s->n_chan;
	s->range_table	= &range_usbdux_ao_range;
	s->करो_cmdtest	= usbdux_ao_cmdtest;
	s->करो_cmd	= usbdux_ao_cmd;
	s->cancel	= usbdux_ao_cancel;
	s->insn_पढ़ो	= usbdux_ao_insn_पढ़ो;
	s->insn_ग_लिखो	= usbdux_ao_insn_ग_लिखो;

	ret = comedi_alloc_subdev_पढ़ोback(s);
	अगर (ret)
		वापस ret;

	/* Digital I/O subdevice */
	s = &dev->subdevices[2];
	s->type		= COMEDI_SUBD_DIO;
	s->subdev_flags	= SDF_READABLE | SDF_WRITABLE;
	s->n_chan	= 8;
	s->maxdata	= 1;
	s->range_table	= &range_digital;
	s->insn_bits	= usbdux_dio_insn_bits;
	s->insn_config	= usbdux_dio_insn_config;

	/* Counter subdevice */
	s = &dev->subdevices[3];
	s->type		= COMEDI_SUBD_COUNTER;
	s->subdev_flags	= SDF_WRITABLE | SDF_READABLE;
	s->n_chan	= 4;
	s->maxdata	= 0xffff;
	s->insn_पढ़ो	= usbdux_counter_पढ़ो;
	s->insn_ग_लिखो	= usbdux_counter_ग_लिखो;
	s->insn_config	= usbdux_counter_config;

	अगर (devpriv->high_speed) अणु
		/* PWM subdevice */
		s = &dev->subdevices[4];
		s->type		= COMEDI_SUBD_PWM;
		s->subdev_flags	= SDF_WRITABLE | SDF_PWM_HBRIDGE;
		s->n_chan	= 8;
		s->maxdata	= devpriv->pwm_buf_sz;
		s->insn_ग_लिखो	= usbdux_pwm_ग_लिखो;
		s->insn_config	= usbdux_pwm_config;

		usbdux_pwm_period(dev, s, PWM_DEFAULT_PERIOD);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम usbdux_detach(काष्ठा comedi_device *dev)
अणु
	काष्ठा usb_पूर्णांकerface *पूर्णांकf = comedi_to_usb_पूर्णांकerface(dev);
	काष्ठा usbdux_निजी *devpriv = dev->निजी;

	usb_set_पूर्णांकfdata(पूर्णांकf, शून्य);

	अगर (!devpriv)
		वापस;

	mutex_lock(&devpriv->mut);

	/* क्रमce unlink all urbs */
	usbdux_pwm_stop(dev, 1);
	usbdux_ao_stop(dev, 1);
	usbdux_ai_stop(dev, 1);

	usbdux_मुक्त_usb_buffers(dev);

	mutex_unlock(&devpriv->mut);

	mutex_destroy(&devpriv->mut);
पूर्ण

अटल काष्ठा comedi_driver usbdux_driver = अणु
	.driver_name	= "usbdux",
	.module		= THIS_MODULE,
	.स्वतः_attach	= usbdux_स्वतः_attach,
	.detach		= usbdux_detach,
पूर्ण;

अटल पूर्णांक usbdux_usb_probe(काष्ठा usb_पूर्णांकerface *पूर्णांकf,
			    स्थिर काष्ठा usb_device_id *id)
अणु
	वापस comedi_usb_स्वतः_config(पूर्णांकf, &usbdux_driver, 0);
पूर्ण

अटल स्थिर काष्ठा usb_device_id usbdux_usb_table[] = अणु
	अणु USB_DEVICE(0x13d8, 0x0001) पूर्ण,
	अणु USB_DEVICE(0x13d8, 0x0002) पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(usb, usbdux_usb_table);

अटल काष्ठा usb_driver usbdux_usb_driver = अणु
	.name		= "usbdux",
	.probe		= usbdux_usb_probe,
	.disconnect	= comedi_usb_स्वतः_unconfig,
	.id_table	= usbdux_usb_table,
पूर्ण;
module_comedi_usb_driver(usbdux_driver, usbdux_usb_driver);

MODULE_AUTHOR("Bernd Porr, BerndPorr@f2s.com");
MODULE_DESCRIPTION("Stirling/ITL USB-DUX -- Bernd.Porr@f2s.com");
MODULE_LICENSE("GPL");
MODULE_FIRMWARE(USBDUX_FIRMWARE);
