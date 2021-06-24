<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 *  Copyright (C) 2004-2019 Bernd Porr, mail@berndporr.me.uk
 */

/*
 * Driver: usbduxfast
 * Description: University of Stirling USB DAQ & INCITE Technology Limited
 * Devices: [ITL] USB-DUX-FAST (usbduxfast)
 * Author: Bernd Porr <mail@berndporr.me.uk>
 * Updated: 16 Nov 2019
 * Status: stable
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
 * 1.0: Fixed a rounding error in usbduxfast_ai_cmdtest
 * 0.9: Dropping the first data packet which seems to be from the last transfer.
 *      Buffer overflows in the FX2 are handed over to comedi.
 * 0.92: Dropping now 4 packets. The quad buffer has to be emptied.
 *       Added insn command basically क्रम testing. Sample rate is
 *       1MHz/16ch=62.5kHz
 * 0.99: Ian Abbott poपूर्णांकed out a bug which has been corrected. Thanks!
 * 0.99a: added बाह्यal trigger.
 * 1.00: added firmware kernel request to the driver which fixed
 *       udev coldplug problem
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/input.h>
#समावेश <linux/fcntl.h>
#समावेश <linux/compiler.h>
#समावेश "../comedi_usb.h"

/*
 * समयout क्रम the USB-transfer
 */
#घोषणा EZTIMEOUT	30

/*
 * स्थिरants क्रम "firmware" upload and करोwnload
 */
#घोषणा FIRMWARE		"usbduxfast_firmware.bin"
#घोषणा FIRMWARE_MAX_LEN	0x2000
#घोषणा USBDUXFASTSUB_FIRMWARE	0xA0
#घोषणा VENDOR_सूची_IN		0xC0
#घोषणा VENDOR_सूची_OUT		0x40

/*
 * पूर्णांकernal addresses of the 8051 processor
 */
#घोषणा USBDUXFASTSUB_CPUCS	0xE600

/*
 * max length of the transfer-buffer क्रम software upload
 */
#घोषणा TB_LEN	0x2000

/*
 * input endpoपूर्णांक number
 */
#घोषणा BULKINEP	6

/*
 * endpoपूर्णांक क्रम the A/D channellist: bulk OUT
 */
#घोषणा CHANNELLISTEP	4

/*
 * number of channels
 */
#घोषणा NUMCHANNELS	32

/*
 * size of the waveक्रमm descriptor
 */
#घोषणा WAVESIZE	0x20

/*
 * size of one A/D value
 */
#घोषणा SIZEADIN	(माप(s16))

/*
 * size of the input-buffer IN BYTES
 */
#घोषणा SIZEINBUF	512

/*
 * 16 bytes
 */
#घोषणा SIZEINSNBUF	512

/*
 * size of the buffer क्रम the dux commands in bytes
 */
#घोषणा SIZखातापूर्णDUXBUF	256

/*
 * number of in-URBs which receive the data: min=5
 */
#घोषणा NUMOFINBUFFERSHIGH	10

/*
 * min delay steps क्रम more than one channel
 * basically when the mux gives up ;-)
 *
 * steps at 30MHz in the FX2
 */
#घोषणा MIN_SAMPLING_PERIOD	9

/*
 * max number of 1/30MHz delay steps
 */
#घोषणा MAX_SAMPLING_PERIOD	500

/*
 * number of received packets to ignore beक्रमe we start handing data
 * over to comedi, it's quad buffering and we have to ignore 4 packets
 */
#घोषणा PACKETS_TO_IGNORE	4

/*
 * comedi स्थिरants
 */
अटल स्थिर काष्ठा comedi_lrange range_usbduxfast_ai_range = अणु
	2, अणु
		BIP_RANGE(0.75),
		BIP_RANGE(0.5)
	पूर्ण
पूर्ण;

/*
 * निजी काष्ठाure of one subdevice
 *
 * this is the काष्ठाure which holds all the data of this driver
 * one sub device just now: A/D
 */
काष्ठा usbduxfast_निजी अणु
	काष्ठा urb *urb;	/* BULK-transfer handling: urb */
	u8 *duxbuf;
	s8 *inbuf;
	लघु पूर्णांक ai_cmd_running;	/* asynchronous command is running */
	पूर्णांक ignore;		/* counter which ignores the first buffers */
	काष्ठा mutex mut;
पूर्ण;

/*
 * bulk transfers to usbduxfast
 */
#घोषणा SENDADCOMMANDS            0
#घोषणा SENDINITEP6               1

अटल पूर्णांक usbduxfast_send_cmd(काष्ठा comedi_device *dev, पूर्णांक cmd_type)
अणु
	काष्ठा usb_device *usb = comedi_to_usb_dev(dev);
	काष्ठा usbduxfast_निजी *devpriv = dev->निजी;
	पूर्णांक nsent;
	पूर्णांक ret;

	devpriv->duxbuf[0] = cmd_type;

	ret = usb_bulk_msg(usb, usb_sndbulkpipe(usb, CHANNELLISTEP),
			   devpriv->duxbuf, SIZखातापूर्णDUXBUF,
			   &nsent, 10000);
	अगर (ret < 0)
		dev_err(dev->class_dev,
			"could not transmit command to the usb-device, err=%d\n",
			ret);
	वापस ret;
पूर्ण

अटल व्योम usbduxfast_cmd_data(काष्ठा comedi_device *dev, पूर्णांक index,
				u8 len, u8 op, u8 out, u8 log)
अणु
	काष्ठा usbduxfast_निजी *devpriv = dev->निजी;

	/* Set the GPIF bytes, the first byte is the command byte */
	devpriv->duxbuf[1 + 0x00 + index] = len;
	devpriv->duxbuf[1 + 0x08 + index] = op;
	devpriv->duxbuf[1 + 0x10 + index] = out;
	devpriv->duxbuf[1 + 0x18 + index] = log;
पूर्ण

अटल पूर्णांक usbduxfast_ai_stop(काष्ठा comedi_device *dev, पूर्णांक करो_unlink)
अणु
	काष्ठा usbduxfast_निजी *devpriv = dev->निजी;

	/* stop aquistion */
	devpriv->ai_cmd_running = 0;

	अगर (करो_unlink && devpriv->urb) अणु
		/* समाप्त the running transfer */
		usb_समाप्त_urb(devpriv->urb);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक usbduxfast_ai_cancel(काष्ठा comedi_device *dev,
				काष्ठा comedi_subdevice *s)
अणु
	काष्ठा usbduxfast_निजी *devpriv = dev->निजी;
	पूर्णांक ret;

	mutex_lock(&devpriv->mut);
	ret = usbduxfast_ai_stop(dev, 1);
	mutex_unlock(&devpriv->mut);

	वापस ret;
पूर्ण

अटल व्योम usbduxfast_ai_handle_urb(काष्ठा comedi_device *dev,
				     काष्ठा comedi_subdevice *s,
				     काष्ठा urb *urb)
अणु
	काष्ठा usbduxfast_निजी *devpriv = dev->निजी;
	काष्ठा comedi_async *async = s->async;
	काष्ठा comedi_cmd *cmd = &async->cmd;
	पूर्णांक ret;

	अगर (devpriv->ignore) अणु
		devpriv->ignore--;
	पूर्ण अन्यथा अणु
		अचिन्हित पूर्णांक nsamples;

		nsamples = comedi_bytes_to_samples(s, urb->actual_length);
		nsamples = comedi_nsamples_left(s, nsamples);
		comedi_buf_ग_लिखो_samples(s, urb->transfer_buffer, nsamples);

		अगर (cmd->stop_src == TRIG_COUNT &&
		    async->scans_करोne >= cmd->stop_arg)
			async->events |= COMEDI_CB_EOA;
	पूर्ण

	/* अगर command is still running, resubmit urb क्रम BULK transfer */
	अगर (!(async->events & COMEDI_CB_CANCEL_MASK)) अणु
		urb->dev = comedi_to_usb_dev(dev);
		urb->status = 0;
		ret = usb_submit_urb(urb, GFP_ATOMIC);
		अगर (ret < 0) अणु
			dev_err(dev->class_dev, "urb resubm failed: %d", ret);
			async->events |= COMEDI_CB_ERROR;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम usbduxfast_ai_पूर्णांकerrupt(काष्ठा urb *urb)
अणु
	काष्ठा comedi_device *dev = urb->context;
	काष्ठा comedi_subdevice *s = dev->पढ़ो_subdev;
	काष्ठा comedi_async *async = s->async;
	काष्ठा usbduxfast_निजी *devpriv = dev->निजी;

	/* निकास अगर not running a command, करो not resubmit urb */
	अगर (!devpriv->ai_cmd_running)
		वापस;

	चयन (urb->status) अणु
	हाल 0:
		usbduxfast_ai_handle_urb(dev, s, urb);
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
			"non-zero urb status received in ai intr context: %d\n",
			urb->status);
		async->events |= COMEDI_CB_ERROR;
		अवरोध;
	पूर्ण

	/*
	 * comedi_handle_events() cannot be used in this driver. The (*cancel)
	 * operation would unlink the urb.
	 */
	अगर (async->events & COMEDI_CB_CANCEL_MASK)
		usbduxfast_ai_stop(dev, 0);

	comedi_event(dev, s);
पूर्ण

अटल पूर्णांक usbduxfast_submit_urb(काष्ठा comedi_device *dev)
अणु
	काष्ठा usb_device *usb = comedi_to_usb_dev(dev);
	काष्ठा usbduxfast_निजी *devpriv = dev->निजी;
	पूर्णांक ret;

	usb_fill_bulk_urb(devpriv->urb, usb, usb_rcvbulkpipe(usb, BULKINEP),
			  devpriv->inbuf, SIZEINBUF,
			  usbduxfast_ai_पूर्णांकerrupt, dev);

	ret = usb_submit_urb(devpriv->urb, GFP_ATOMIC);
	अगर (ret) अणु
		dev_err(dev->class_dev, "usb_submit_urb error %d\n", ret);
		वापस ret;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक usbduxfast_ai_check_chanlist(काष्ठा comedi_device *dev,
					काष्ठा comedi_subdevice *s,
					काष्ठा comedi_cmd *cmd)
अणु
	अचिन्हित पूर्णांक gain0 = CR_RANGE(cmd->chanlist[0]);
	पूर्णांक i;

	अगर (cmd->chanlist_len > 3 && cmd->chanlist_len != 16) अणु
		dev_err(dev->class_dev, "unsupported combination of channels\n");
		वापस -EINVAL;
	पूर्ण

	क्रम (i = 0; i < cmd->chanlist_len; ++i) अणु
		अचिन्हित पूर्णांक chan = CR_CHAN(cmd->chanlist[i]);
		अचिन्हित पूर्णांक gain = CR_RANGE(cmd->chanlist[i]);

		अगर (chan != i) अणु
			dev_err(dev->class_dev,
				"channels are not consecutive\n");
			वापस -EINVAL;
		पूर्ण
		अगर (gain != gain0 && cmd->chanlist_len > 3) अणु
			dev_err(dev->class_dev,
				"gain must be the same for all channels\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक usbduxfast_ai_cmdtest(काष्ठा comedi_device *dev,
				 काष्ठा comedi_subdevice *s,
				 काष्ठा comedi_cmd *cmd)
अणु
	पूर्णांक err = 0;
	पूर्णांक err2 = 0;
	अचिन्हित पूर्णांक steps;
	अचिन्हित पूर्णांक arg;

	/* Step 1 : check अगर triggers are trivially valid */

	err |= comedi_check_trigger_src(&cmd->start_src,
					TRIG_NOW | TRIG_EXT | TRIG_INT);
	err |= comedi_check_trigger_src(&cmd->scan_begin_src, TRIG_FOLLOW);
	err |= comedi_check_trigger_src(&cmd->convert_src, TRIG_TIMER);
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

	अगर (!cmd->chanlist_len)
		err |= -EINVAL;

	/* बाह्यal start trigger is only valid क्रम 1 or 16 channels */
	अगर (cmd->start_src == TRIG_EXT &&
	    cmd->chanlist_len != 1 && cmd->chanlist_len != 16)
		err |= -EINVAL;

	err |= comedi_check_trigger_arg_is(&cmd->scan_end_arg,
					   cmd->chanlist_len);

	/*
	 * Validate the conversion timing:
	 * क्रम 1 channel the timing in 30MHz "steps" is:
	 *	steps <= MAX_SAMPLING_PERIOD
	 * क्रम all other chanlist_len it is:
	 *	MIN_SAMPLING_PERIOD <= steps <= MAX_SAMPLING_PERIOD
	 */
	steps = (cmd->convert_arg * 30) / 1000;
	अगर (cmd->chanlist_len !=  1)
		err2 |= comedi_check_trigger_arg_min(&steps,
						     MIN_SAMPLING_PERIOD);
	अन्यथा
		err2 |= comedi_check_trigger_arg_min(&steps, 1);
	err2 |= comedi_check_trigger_arg_max(&steps, MAX_SAMPLING_PERIOD);
	अगर (err2) अणु
		err |= err2;
		arg = (steps * 1000) / 30;
		err |= comedi_check_trigger_arg_is(&cmd->convert_arg, arg);
	पूर्ण

	अगर (cmd->stop_src == TRIG_COUNT)
		err |= comedi_check_trigger_arg_min(&cmd->stop_arg, 1);
	अन्यथा	/* TRIG_NONE */
		err |= comedi_check_trigger_arg_is(&cmd->stop_arg, 0);

	अगर (err)
		वापस 3;

	/* Step 4: fix up any arguments */

	/* Step 5: check channel list अगर it exists */
	अगर (cmd->chanlist && cmd->chanlist_len > 0)
		err |= usbduxfast_ai_check_chanlist(dev, s, cmd);
	अगर (err)
		वापस 5;

	वापस 0;
पूर्ण

अटल पूर्णांक usbduxfast_ai_पूर्णांकtrig(काष्ठा comedi_device *dev,
				 काष्ठा comedi_subdevice *s,
				 अचिन्हित पूर्णांक trig_num)
अणु
	काष्ठा usbduxfast_निजी *devpriv = dev->निजी;
	काष्ठा comedi_cmd *cmd = &s->async->cmd;
	पूर्णांक ret;

	अगर (trig_num != cmd->start_arg)
		वापस -EINVAL;

	mutex_lock(&devpriv->mut);

	अगर (!devpriv->ai_cmd_running) अणु
		devpriv->ai_cmd_running = 1;
		ret = usbduxfast_submit_urb(dev);
		अगर (ret < 0) अणु
			dev_err(dev->class_dev, "urbSubmit: err=%d\n", ret);
			devpriv->ai_cmd_running = 0;
			mutex_unlock(&devpriv->mut);
			वापस ret;
		पूर्ण
		s->async->पूर्णांकtrig = शून्य;
	पूर्ण अन्यथा अणु
		dev_err(dev->class_dev, "ai is already running\n");
	पूर्ण
	mutex_unlock(&devpriv->mut);
	वापस 1;
पूर्ण

अटल पूर्णांक usbduxfast_ai_cmd(काष्ठा comedi_device *dev,
			     काष्ठा comedi_subdevice *s)
अणु
	काष्ठा usbduxfast_निजी *devpriv = dev->निजी;
	काष्ठा comedi_cmd *cmd = &s->async->cmd;
	अचिन्हित पूर्णांक rngmask = 0xff;
	पूर्णांक j, ret;
	दीर्घ steps, steps_पंचांगp;

	mutex_lock(&devpriv->mut);
	अगर (devpriv->ai_cmd_running) अणु
		ret = -EBUSY;
		जाओ cmd_निकास;
	पूर्ण

	/*
	 * ignore the first buffers from the device अगर there
	 * is an error condition
	 */
	devpriv->ignore = PACKETS_TO_IGNORE;

	steps = (cmd->convert_arg * 30) / 1000;

	चयन (cmd->chanlist_len) अणु
	हाल 1:
		/*
		 * one channel
		 */

		अगर (CR_RANGE(cmd->chanlist[0]) > 0)
			rngmask = 0xff - 0x04;
		अन्यथा
			rngmask = 0xff;

		/*
		 * क्रम बाह्यal trigger: looping in this state until
		 * the RDY0 pin becomes zero
		 */

		/* we loop here until पढ़ोy has been set */
		अगर (cmd->start_src == TRIG_EXT) अणु
			/* branch back to state 0 */
			/* deceision state w/o data */
			/* RDY0 = 0 */
			usbduxfast_cmd_data(dev, 0, 0x01, 0x01, rngmask, 0x00);
		पूर्ण अन्यथा अणु	/* we just proceed to state 1 */
			usbduxfast_cmd_data(dev, 0, 0x01, 0x00, rngmask, 0x00);
		पूर्ण

		अगर (steps < MIN_SAMPLING_PERIOD) अणु
			/* क्रम fast single channel aqu without mux */
			अगर (steps <= 1) अणु
				/*
				 * we just stay here at state 1 and rexecute
				 * the same state this gives us 30MHz sampling
				 * rate
				 */

				/* branch back to state 1 */
				/* deceision state with data */
				/* करोesn't matter */
				usbduxfast_cmd_data(dev, 1,
						    0x89, 0x03, rngmask, 0xff);
			पूर्ण अन्यथा अणु
				/*
				 * we loop through two states: data and delay
				 * max rate is 15MHz
				 */
				/* data */
				/* करोesn't matter */
				usbduxfast_cmd_data(dev, 1, steps - 1,
						    0x02, rngmask, 0x00);

				/* branch back to state 1 */
				/* deceision state w/o data */
				/* करोesn't matter */
				usbduxfast_cmd_data(dev, 2,
						    0x09, 0x01, rngmask, 0xff);
			पूर्ण
		पूर्ण अन्यथा अणु
			/*
			 * we loop through 3 states: 2x delay and 1x data
			 * this gives a min sampling rate of 60kHz
			 */

			/* we have 1 state with duration 1 */
			steps = steps - 1;

			/* करो the first part of the delay */
			usbduxfast_cmd_data(dev, 1,
					    steps / 2, 0x00, rngmask, 0x00);

			/* and the second part */
			usbduxfast_cmd_data(dev, 2, steps - steps / 2,
					    0x00, rngmask, 0x00);

			/* get the data and branch back */

			/* branch back to state 1 */
			/* deceision state w data */
			/* करोesn't matter */
			usbduxfast_cmd_data(dev, 3,
					    0x09, 0x03, rngmask, 0xff);
		पूर्ण
		अवरोध;

	हाल 2:
		/*
		 * two channels
		 * commit data to the FIFO
		 */

		अगर (CR_RANGE(cmd->chanlist[0]) > 0)
			rngmask = 0xff - 0x04;
		अन्यथा
			rngmask = 0xff;

		/* data */
		usbduxfast_cmd_data(dev, 0, 0x01, 0x02, rngmask, 0x00);

		/* we have 1 state with duration 1: state 0 */
		steps_पंचांगp = steps - 1;

		अगर (CR_RANGE(cmd->chanlist[1]) > 0)
			rngmask = 0xff - 0x04;
		अन्यथा
			rngmask = 0xff;

		/* करो the first part of the delay */
		/* count */
		usbduxfast_cmd_data(dev, 1, steps_पंचांगp / 2,
				    0x00, 0xfe & rngmask, 0x00);

		/* and the second part */
		usbduxfast_cmd_data(dev, 2, steps_पंचांगp  - steps_पंचांगp / 2,
				    0x00, rngmask, 0x00);

		/* data */
		usbduxfast_cmd_data(dev, 3, 0x01, 0x02, rngmask, 0x00);

		/*
		 * we have 2 states with duration 1: step 6 and
		 * the IDLE state
		 */
		steps_पंचांगp = steps - 2;

		अगर (CR_RANGE(cmd->chanlist[0]) > 0)
			rngmask = 0xff - 0x04;
		अन्यथा
			rngmask = 0xff;

		/* करो the first part of the delay */
		/* reset */
		usbduxfast_cmd_data(dev, 4, steps_पंचांगp / 2,
				    0x00, (0xff - 0x02) & rngmask, 0x00);

		/* and the second part */
		usbduxfast_cmd_data(dev, 5, steps_पंचांगp - steps_पंचांगp / 2,
				    0x00, rngmask, 0x00);

		usbduxfast_cmd_data(dev, 6, 0x01, 0x00, rngmask, 0x00);
		अवरोध;

	हाल 3:
		/*
		 * three channels
		 */
		क्रम (j = 0; j < 1; j++) अणु
			पूर्णांक index = j * 2;

			अगर (CR_RANGE(cmd->chanlist[j]) > 0)
				rngmask = 0xff - 0x04;
			अन्यथा
				rngmask = 0xff;
			/*
			 * commit data to the FIFO and करो the first part
			 * of the delay
			 */
			/* data */
			/* no change */
			usbduxfast_cmd_data(dev, index, steps / 2,
					    0x02, rngmask, 0x00);

			अगर (CR_RANGE(cmd->chanlist[j + 1]) > 0)
				rngmask = 0xff - 0x04;
			अन्यथा
				rngmask = 0xff;

			/* करो the second part of the delay */
			/* no data */
			/* count */
			usbduxfast_cmd_data(dev, index + 1, steps - steps / 2,
					    0x00, 0xfe & rngmask, 0x00);
		पूर्ण

		/* 2 steps with duration 1: the idele step and step 6: */
		steps_पंचांगp = steps - 2;

		/* commit data to the FIFO and करो the first part of the delay */
		/* data */
		usbduxfast_cmd_data(dev, 4, steps_पंचांगp / 2,
				    0x02, rngmask, 0x00);

		अगर (CR_RANGE(cmd->chanlist[0]) > 0)
			rngmask = 0xff - 0x04;
		अन्यथा
			rngmask = 0xff;

		/* करो the second part of the delay */
		/* no data */
		/* reset */
		usbduxfast_cmd_data(dev, 5, steps_पंचांगp - steps_पंचांगp / 2,
				    0x00, (0xff - 0x02) & rngmask, 0x00);

		usbduxfast_cmd_data(dev, 6, 0x01, 0x00, rngmask, 0x00);
		अवरोध;

	हाल 16:
		अगर (CR_RANGE(cmd->chanlist[0]) > 0)
			rngmask = 0xff - 0x04;
		अन्यथा
			rngmask = 0xff;

		अगर (cmd->start_src == TRIG_EXT) अणु
			/*
			 * we loop here until पढ़ोy has been set
			 */

			/* branch back to state 0 */
			/* deceision state w/o data */
			/* reset */
			/* RDY0 = 0 */
			usbduxfast_cmd_data(dev, 0, 0x01, 0x01,
					    (0xff - 0x02) & rngmask, 0x00);
		पूर्ण अन्यथा अणु
			/*
			 * we just proceed to state 1
			 */

			/* 30us reset pulse */
			/* reset */
			usbduxfast_cmd_data(dev, 0, 0xff, 0x00,
					    (0xff - 0x02) & rngmask, 0x00);
		पूर्ण

		/* commit data to the FIFO */
		/* data */
		usbduxfast_cmd_data(dev, 1, 0x01, 0x02, rngmask, 0x00);

		/* we have 2 states with duration 1 */
		steps = steps - 2;

		/* करो the first part of the delay */
		usbduxfast_cmd_data(dev, 2, steps / 2,
				    0x00, 0xfe & rngmask, 0x00);

		/* and the second part */
		usbduxfast_cmd_data(dev, 3, steps - steps / 2,
				    0x00, rngmask, 0x00);

		/* branch back to state 1 */
		/* deceision state w/o data */
		/* करोesn't matter */
		usbduxfast_cmd_data(dev, 4, 0x09, 0x01, rngmask, 0xff);

		अवरोध;
	पूर्ण

	/* 0 means that the AD commands are sent */
	ret = usbduxfast_send_cmd(dev, SENDADCOMMANDS);
	अगर (ret < 0)
		जाओ cmd_निकास;

	अगर ((cmd->start_src == TRIG_NOW) || (cmd->start_src == TRIG_EXT)) अणु
		/* enable this acquisition operation */
		devpriv->ai_cmd_running = 1;
		ret = usbduxfast_submit_urb(dev);
		अगर (ret < 0) अणु
			devpriv->ai_cmd_running = 0;
			/* fixme: unlink here?? */
			जाओ cmd_निकास;
		पूर्ण
		s->async->पूर्णांकtrig = शून्य;
	पूर्ण अन्यथा अणु	/* TRIG_INT */
		s->async->पूर्णांकtrig = usbduxfast_ai_पूर्णांकtrig;
	पूर्ण

cmd_निकास:
	mutex_unlock(&devpriv->mut);

	वापस ret;
पूर्ण

/*
 * Mode 0 is used to get a single conversion on demand.
 */
अटल पूर्णांक usbduxfast_ai_insn_पढ़ो(काष्ठा comedi_device *dev,
				   काष्ठा comedi_subdevice *s,
				   काष्ठा comedi_insn *insn,
				   अचिन्हित पूर्णांक *data)
अणु
	काष्ठा usb_device *usb = comedi_to_usb_dev(dev);
	काष्ठा usbduxfast_निजी *devpriv = dev->निजी;
	अचिन्हित पूर्णांक chan = CR_CHAN(insn->chanspec);
	अचिन्हित पूर्णांक range = CR_RANGE(insn->chanspec);
	u8 rngmask = range ? (0xff - 0x04) : 0xff;
	पूर्णांक i, j, n, actual_length;
	पूर्णांक ret;

	mutex_lock(&devpriv->mut);

	अगर (devpriv->ai_cmd_running) अणु
		dev_err(dev->class_dev,
			"ai_insn_read not possible, async cmd is running\n");
		mutex_unlock(&devpriv->mut);
		वापस -EBUSY;
	पूर्ण

	/* set command क्रम the first channel */

	/* commit data to the FIFO */
	/* data */
	usbduxfast_cmd_data(dev, 0, 0x01, 0x02, rngmask, 0x00);

	/* करो the first part of the delay */
	usbduxfast_cmd_data(dev, 1, 0x0c, 0x00, 0xfe & rngmask, 0x00);
	usbduxfast_cmd_data(dev, 2, 0x01, 0x00, 0xfe & rngmask, 0x00);
	usbduxfast_cmd_data(dev, 3, 0x01, 0x00, 0xfe & rngmask, 0x00);
	usbduxfast_cmd_data(dev, 4, 0x01, 0x00, 0xfe & rngmask, 0x00);

	/* second part */
	usbduxfast_cmd_data(dev, 5, 0x0c, 0x00, rngmask, 0x00);
	usbduxfast_cmd_data(dev, 6, 0x01, 0x00, rngmask, 0x00);

	ret = usbduxfast_send_cmd(dev, SENDADCOMMANDS);
	अगर (ret < 0) अणु
		mutex_unlock(&devpriv->mut);
		वापस ret;
	पूर्ण

	क्रम (i = 0; i < PACKETS_TO_IGNORE; i++) अणु
		ret = usb_bulk_msg(usb, usb_rcvbulkpipe(usb, BULKINEP),
				   devpriv->inbuf, SIZEINBUF,
				   &actual_length, 10000);
		अगर (ret < 0) अणु
			dev_err(dev->class_dev, "insn timeout, no data\n");
			mutex_unlock(&devpriv->mut);
			वापस ret;
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < insn->n;) अणु
		ret = usb_bulk_msg(usb, usb_rcvbulkpipe(usb, BULKINEP),
				   devpriv->inbuf, SIZEINBUF,
				   &actual_length, 10000);
		अगर (ret < 0) अणु
			dev_err(dev->class_dev, "insn data error: %d\n", ret);
			mutex_unlock(&devpriv->mut);
			वापस ret;
		पूर्ण
		n = actual_length / माप(u16);
		अगर ((n % 16) != 0) अणु
			dev_err(dev->class_dev, "insn data packet corrupted\n");
			mutex_unlock(&devpriv->mut);
			वापस -EINVAL;
		पूर्ण
		क्रम (j = chan; (j < n) && (i < insn->n); j = j + 16) अणु
			data[i] = ((u16 *)(devpriv->inbuf))[j];
			i++;
		पूर्ण
	पूर्ण

	mutex_unlock(&devpriv->mut);

	वापस insn->n;
पूर्ण

अटल पूर्णांक usbduxfast_upload_firmware(काष्ठा comedi_device *dev,
				      स्थिर u8 *data, माप_प्रकार size,
				      अचिन्हित दीर्घ context)
अणु
	काष्ठा usb_device *usb = comedi_to_usb_dev(dev);
	u8 *buf;
	अचिन्हित अक्षर *पंचांगp;
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
			      USBDUXFASTSUB_FIRMWARE,
			      VENDOR_सूची_OUT,
			      USBDUXFASTSUB_CPUCS, 0x0000,
			      पंचांगp, 1,
			      EZTIMEOUT);
	अगर (ret < 0) अणु
		dev_err(dev->class_dev, "can not stop firmware\n");
		जाओ करोne;
	पूर्ण

	/* upload the new firmware to the device */
	ret = usb_control_msg(usb, usb_sndctrlpipe(usb, 0),
			      USBDUXFASTSUB_FIRMWARE,
			      VENDOR_सूची_OUT,
			      0, 0x0000,
			      buf, size,
			      EZTIMEOUT);
	अगर (ret < 0) अणु
		dev_err(dev->class_dev, "firmware upload failed\n");
		जाओ करोne;
	पूर्ण

	/* start the new firmware on the device */
	*पंचांगp = 0;	/* 7f92 to zero */
	ret = usb_control_msg(usb, usb_sndctrlpipe(usb, 0),
			      USBDUXFASTSUB_FIRMWARE,
			      VENDOR_सूची_OUT,
			      USBDUXFASTSUB_CPUCS, 0x0000,
			      पंचांगp, 1,
			      EZTIMEOUT);
	अगर (ret < 0)
		dev_err(dev->class_dev, "can not start firmware\n");

करोne:
	kमुक्त(पंचांगp);
	kमुक्त(buf);
	वापस ret;
पूर्ण

अटल पूर्णांक usbduxfast_स्वतः_attach(काष्ठा comedi_device *dev,
				  अचिन्हित दीर्घ context_unused)
अणु
	काष्ठा usb_पूर्णांकerface *पूर्णांकf = comedi_to_usb_पूर्णांकerface(dev);
	काष्ठा usb_device *usb = comedi_to_usb_dev(dev);
	काष्ठा usbduxfast_निजी *devpriv;
	काष्ठा comedi_subdevice *s;
	पूर्णांक ret;

	अगर (usb->speed != USB_SPEED_HIGH) अणु
		dev_err(dev->class_dev,
			"This driver needs USB 2.0 to operate. Aborting...\n");
		वापस -ENODEV;
	पूर्ण

	devpriv = comedi_alloc_devpriv(dev, माप(*devpriv));
	अगर (!devpriv)
		वापस -ENOMEM;

	mutex_init(&devpriv->mut);
	usb_set_पूर्णांकfdata(पूर्णांकf, devpriv);

	devpriv->duxbuf = kदो_स्मृति(SIZखातापूर्णDUXBUF, GFP_KERNEL);
	अगर (!devpriv->duxbuf)
		वापस -ENOMEM;

	ret = usb_set_पूर्णांकerface(usb,
				पूर्णांकf->altsetting->desc.bInterfaceNumber, 1);
	अगर (ret < 0) अणु
		dev_err(dev->class_dev,
			"could not switch to alternate setting 1\n");
		वापस -ENODEV;
	पूर्ण

	devpriv->urb = usb_alloc_urb(0, GFP_KERNEL);
	अगर (!devpriv->urb)
		वापस -ENOMEM;

	devpriv->inbuf = kदो_स्मृति(SIZEINBUF, GFP_KERNEL);
	अगर (!devpriv->inbuf)
		वापस -ENOMEM;

	ret = comedi_load_firmware(dev, &usb->dev, FIRMWARE,
				   usbduxfast_upload_firmware, 0);
	अगर (ret)
		वापस ret;

	ret = comedi_alloc_subdevices(dev, 1);
	अगर (ret)
		वापस ret;

	/* Analog Input subdevice */
	s = &dev->subdevices[0];
	dev->पढ़ो_subdev = s;
	s->type		= COMEDI_SUBD_AI;
	s->subdev_flags	= SDF_READABLE | SDF_GROUND | SDF_CMD_READ;
	s->n_chan	= 16;
	s->maxdata	= 0x1000;	/* 12-bit + 1 overflow bit */
	s->range_table	= &range_usbduxfast_ai_range;
	s->insn_पढ़ो	= usbduxfast_ai_insn_पढ़ो;
	s->len_chanlist	= s->n_chan;
	s->करो_cmdtest	= usbduxfast_ai_cmdtest;
	s->करो_cmd	= usbduxfast_ai_cmd;
	s->cancel	= usbduxfast_ai_cancel;

	वापस 0;
पूर्ण

अटल व्योम usbduxfast_detach(काष्ठा comedi_device *dev)
अणु
	काष्ठा usb_पूर्णांकerface *पूर्णांकf = comedi_to_usb_पूर्णांकerface(dev);
	काष्ठा usbduxfast_निजी *devpriv = dev->निजी;

	अगर (!devpriv)
		वापस;

	mutex_lock(&devpriv->mut);

	usb_set_पूर्णांकfdata(पूर्णांकf, शून्य);

	अगर (devpriv->urb) अणु
		/* रुकोs until a running transfer is over */
		usb_समाप्त_urb(devpriv->urb);

		kमुक्त(devpriv->inbuf);
		usb_मुक्त_urb(devpriv->urb);
	पूर्ण

	kमुक्त(devpriv->duxbuf);

	mutex_unlock(&devpriv->mut);

	mutex_destroy(&devpriv->mut);
पूर्ण

अटल काष्ठा comedi_driver usbduxfast_driver = अणु
	.driver_name	= "usbduxfast",
	.module		= THIS_MODULE,
	.स्वतः_attach	= usbduxfast_स्वतः_attach,
	.detach		= usbduxfast_detach,
पूर्ण;

अटल पूर्णांक usbduxfast_usb_probe(काष्ठा usb_पूर्णांकerface *पूर्णांकf,
				स्थिर काष्ठा usb_device_id *id)
अणु
	वापस comedi_usb_स्वतः_config(पूर्णांकf, &usbduxfast_driver, 0);
पूर्ण

अटल स्थिर काष्ठा usb_device_id usbduxfast_usb_table[] = अणु
	/* अणु USB_DEVICE(0x4b4, 0x8613) पूर्ण, testing */
	अणु USB_DEVICE(0x13d8, 0x0010) पूर्ण,	/* real ID */
	अणु USB_DEVICE(0x13d8, 0x0011) पूर्ण,	/* real ID */
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(usb, usbduxfast_usb_table);

अटल काष्ठा usb_driver usbduxfast_usb_driver = अणु
	.name		= "usbduxfast",
	.probe		= usbduxfast_usb_probe,
	.disconnect	= comedi_usb_स्वतः_unconfig,
	.id_table	= usbduxfast_usb_table,
पूर्ण;
module_comedi_usb_driver(usbduxfast_driver, usbduxfast_usb_driver);

MODULE_AUTHOR("Bernd Porr, BerndPorr@f2s.com");
MODULE_DESCRIPTION("USB-DUXfast, BerndPorr@f2s.com");
MODULE_LICENSE("GPL");
MODULE_FIRMWARE(FIRMWARE);
