<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  पंचांग6000-dvb.c - dvb-t support क्रम TM5600/TM6000/TM6010 USB video capture devices
 *
 *  Copyright (C) 2007 Michel Ludwig <michel.ludwig@gmail.com>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/usb.h>

#समावेश "tm6000.h"
#समावेश "tm6000-regs.h"

#समावेश "zl10353.h"

#समावेश <media/tuner.h>

#समावेश "tuner-xc2028.h"
#समावेश "xc5000.h"

MODULE_DESCRIPTION("DVB driver extension module for tm5600/6000/6010 based TV cards");
MODULE_AUTHOR("Mauro Carvalho Chehab");
MODULE_LICENSE("GPL");

अटल पूर्णांक debug;

module_param(debug, पूर्णांक, 0644);
MODULE_PARM_DESC(debug, "enable debug message");

अटल अंतरभूत व्योम prपूर्णांक_err_status(काष्ठा पंचांग6000_core *dev,
				    पूर्णांक packet, पूर्णांक status)
अणु
	अक्षर *errmsg = "Unknown";

	चयन (status) अणु
	हाल -ENOENT:
		errmsg = "unlinked synchronously";
		अवरोध;
	हाल -ECONNRESET:
		errmsg = "unlinked asynchronously";
		अवरोध;
	हाल -ENOSR:
		errmsg = "Buffer error (overrun)";
		अवरोध;
	हाल -EPIPE:
		errmsg = "Stalled (device not responding)";
		अवरोध;
	हाल -EOVERFLOW:
		errmsg = "Babble (bad cable?)";
		अवरोध;
	हाल -EPROTO:
		errmsg = "Bit-stuff error (bad cable?)";
		अवरोध;
	हाल -EILSEQ:
		errmsg = "CRC/Timeout (could be anything)";
		अवरोध;
	हाल -ETIME:
		errmsg = "Device does not respond";
		अवरोध;
	पूर्ण
	अगर (packet < 0) अणु
		dprपूर्णांकk(dev, 1, "URB status %d [%s].\n",
			status, errmsg);
	पूर्ण अन्यथा अणु
		dprपूर्णांकk(dev, 1, "URB packet %d, status %d [%s].\n",
			packet, status, errmsg);
	पूर्ण
पूर्ण

अटल व्योम पंचांग6000_urb_received(काष्ठा urb *urb)
अणु
	पूर्णांक ret;
	काष्ठा पंचांग6000_core *dev = urb->context;

	चयन (urb->status) अणु
	हाल 0:
	हाल -ETIMEDOUT:
		अवरोध;
	हाल -ENOENT:
	हाल -ECONNRESET:
	हाल -ESHUTDOWN:
		वापस;
	शेष:
		prपूर्णांक_err_status(dev, 0, urb->status);
	पूर्ण

	अगर (urb->actual_length > 0)
		dvb_dmx_swfilter(&dev->dvb->demux, urb->transfer_buffer,
						   urb->actual_length);

	अगर (dev->dvb->streams > 0) अणु
		ret = usb_submit_urb(urb, GFP_ATOMIC);
		अगर (ret < 0) अणु
			prपूर्णांकk(KERN_ERR "tm6000:  error %s\n", __func__);
			kमुक्त(urb->transfer_buffer);
			usb_मुक्त_urb(urb);
			dev->dvb->bulk_urb = शून्य;
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक पंचांग6000_start_stream(काष्ठा पंचांग6000_core *dev)
अणु
	पूर्णांक ret;
	अचिन्हित पूर्णांक pipe, size;
	काष्ठा पंचांग6000_dvb *dvb = dev->dvb;

	prपूर्णांकk(KERN_INFO "tm6000: got start stream request %s\n", __func__);

	अगर (dev->mode != TM6000_MODE_DIGITAL) अणु
		पंचांग6000_init_digital_mode(dev);
		dev->mode = TM6000_MODE_DIGITAL;
	पूर्ण

	dvb->bulk_urb = usb_alloc_urb(0, GFP_KERNEL);
	अगर (!dvb->bulk_urb)
		वापस -ENOMEM;

	pipe = usb_rcvbulkpipe(dev->udev, dev->bulk_in.endp->desc.bEndpoपूर्णांकAddress
							  & USB_ENDPOINT_NUMBER_MASK);

	size = usb_maxpacket(dev->udev, pipe, usb_pipeout(pipe));
	size = size * 15; /* 512 x 8 or 12 or 15 */

	dvb->bulk_urb->transfer_buffer = kzalloc(size, GFP_KERNEL);
	अगर (!dvb->bulk_urb->transfer_buffer) अणु
		usb_मुक्त_urb(dvb->bulk_urb);
		dvb->bulk_urb = शून्य;
		वापस -ENOMEM;
	पूर्ण

	usb_fill_bulk_urb(dvb->bulk_urb, dev->udev, pipe,
						 dvb->bulk_urb->transfer_buffer,
						 size,
						 पंचांग6000_urb_received, dev);

	ret = usb_clear_halt(dev->udev, pipe);
	अगर (ret < 0) अणु
		prपूर्णांकk(KERN_ERR "tm6000: error %i in %s during pipe reset\n",
							ret, __func__);

		kमुक्त(dvb->bulk_urb->transfer_buffer);
		usb_मुक्त_urb(dvb->bulk_urb);
		dvb->bulk_urb = शून्य;
		वापस ret;
	पूर्ण अन्यथा
		prपूर्णांकk(KERN_ERR "tm6000: pipe reset\n");

/*	mutex_lock(&पंचांग6000_driver.खोलो_बंद_mutex); */
	ret = usb_submit_urb(dvb->bulk_urb, GFP_ATOMIC);

/*	mutex_unlock(&पंचांग6000_driver.खोलो_बंद_mutex); */
	अगर (ret) अणु
		prपूर्णांकk(KERN_ERR "tm6000: submit of urb failed (error=%i)\n",
									ret);

		kमुक्त(dvb->bulk_urb->transfer_buffer);
		usb_मुक्त_urb(dvb->bulk_urb);
		dvb->bulk_urb = शून्य;
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम पंचांग6000_stop_stream(काष्ठा पंचांग6000_core *dev)
अणु
	काष्ठा पंचांग6000_dvb *dvb = dev->dvb;

	अगर (dvb->bulk_urb) अणु
		prपूर्णांकk(KERN_INFO "urb killing\n");
		usb_समाप्त_urb(dvb->bulk_urb);
		prपूर्णांकk(KERN_INFO "urb buffer free\n");
		kमुक्त(dvb->bulk_urb->transfer_buffer);
		usb_मुक्त_urb(dvb->bulk_urb);
		dvb->bulk_urb = शून्य;
	पूर्ण
पूर्ण

अटल पूर्णांक पंचांग6000_start_feed(काष्ठा dvb_demux_feed *feed)
अणु
	काष्ठा dvb_demux *demux = feed->demux;
	काष्ठा पंचांग6000_core *dev = demux->priv;
	काष्ठा पंचांग6000_dvb *dvb = dev->dvb;
	prपूर्णांकk(KERN_INFO "tm6000: got start feed request %s\n", __func__);

	mutex_lock(&dvb->mutex);
	अगर (dvb->streams == 0) अणु
		dvb->streams = 1;
/*		mutex_init(&पंचांग6000_dev->streming_mutex); */
		पंचांग6000_start_stream(dev);
	पूर्ण अन्यथा
		++(dvb->streams);
	mutex_unlock(&dvb->mutex);

	वापस 0;
पूर्ण

अटल पूर्णांक पंचांग6000_stop_feed(काष्ठा dvb_demux_feed *feed)
अणु
	काष्ठा dvb_demux *demux = feed->demux;
	काष्ठा पंचांग6000_core *dev = demux->priv;
	काष्ठा पंचांग6000_dvb *dvb = dev->dvb;

	prपूर्णांकk(KERN_INFO "tm6000: got stop feed request %s\n", __func__);

	mutex_lock(&dvb->mutex);

	prपूर्णांकk(KERN_INFO "stream %#x\n", dvb->streams);
	--(dvb->streams);
	अगर (dvb->streams == 0) अणु
		prपूर्णांकk(KERN_INFO "stop stream\n");
		पंचांग6000_stop_stream(dev);
/*		mutex_destroy(&पंचांग6000_dev->streaming_mutex); */
	पूर्ण
	mutex_unlock(&dvb->mutex);
/*	mutex_destroy(&पंचांग6000_dev->streaming_mutex); */

	वापस 0;
पूर्ण

अटल पूर्णांक पंचांग6000_dvb_attach_frontend(काष्ठा पंचांग6000_core *dev)
अणु
	काष्ठा पंचांग6000_dvb *dvb = dev->dvb;

	अगर (dev->caps.has_zl10353) अणु
		काष्ठा zl10353_config config = अणु
				     .demod_address = dev->demod_addr,
				     .no_tuner = 1,
				     .parallel_ts = 1,
				     .अगर2 = 45700,
				     .disable_i2c_gate_ctrl = 1,
				    पूर्ण;

		dvb->frontend = dvb_attach(zl10353_attach, &config,
							   &dev->i2c_adap);
	पूर्ण अन्यथा अणु
		prपूर्णांकk(KERN_ERR "tm6000: no frontend defined for the device!\n");
		वापस -1;
	पूर्ण

	वापस (!dvb->frontend) ? -1 : 0;
पूर्ण

DVB_DEFINE_MOD_OPT_ADAPTER_NR(adapter_nr);

अटल पूर्णांक रेजिस्टर_dvb(काष्ठा पंचांग6000_core *dev)
अणु
	पूर्णांक ret = -1;
	काष्ठा पंचांग6000_dvb *dvb = dev->dvb;

	mutex_init(&dvb->mutex);

	dvb->streams = 0;

	/* attach the frontend */
	ret = पंचांग6000_dvb_attach_frontend(dev);
	अगर (ret < 0) अणु
		prपूर्णांकk(KERN_ERR "tm6000: couldn't attach the frontend!\n");
		जाओ err;
	पूर्ण

	ret = dvb_रेजिस्टर_adapter(&dvb->adapter, "Trident TVMaster 6000 DVB-T",
					THIS_MODULE, &dev->udev->dev, adapter_nr);
	अगर (ret < 0) अणु
		pr_err("tm6000: couldn't register the adapter!\n");
		जाओ err;
	पूर्ण

	dvb->adapter.priv = dev;

	अगर (dvb->frontend) अणु
		चयन (dev->tuner_type) अणु
		हाल TUNER_XC2028: अणु
			काष्ठा xc2028_config cfg = अणु
				.i2c_adap = &dev->i2c_adap,
				.i2c_addr = dev->tuner_addr,
			पूर्ण;

			dvb->frontend->callback = पंचांग6000_tuner_callback;
			ret = dvb_रेजिस्टर_frontend(&dvb->adapter, dvb->frontend);
			अगर (ret < 0) अणु
				prपूर्णांकk(KERN_ERR
					"tm6000: couldn't register frontend\n");
				जाओ adapter_err;
			पूर्ण

			अगर (!dvb_attach(xc2028_attach, dvb->frontend, &cfg)) अणु
				prपूर्णांकk(KERN_ERR "tm6000: couldn't register frontend (xc3028)\n");
				ret = -EINVAL;
				जाओ frontend_err;
			पूर्ण
			prपूर्णांकk(KERN_INFO "tm6000: XC2028/3028 asked to be attached to frontend!\n");
			अवरोध;
			पूर्ण
		हाल TUNER_XC5000: अणु
			काष्ठा xc5000_config cfg = अणु
				.i2c_address = dev->tuner_addr,
			पूर्ण;

			dvb->frontend->callback = पंचांग6000_xc5000_callback;
			ret = dvb_रेजिस्टर_frontend(&dvb->adapter, dvb->frontend);
			अगर (ret < 0) अणु
				prपूर्णांकk(KERN_ERR
					"tm6000: couldn't register frontend\n");
				जाओ adapter_err;
			पूर्ण

			अगर (!dvb_attach(xc5000_attach, dvb->frontend, &dev->i2c_adap, &cfg)) अणु
				prपूर्णांकk(KERN_ERR "tm6000: couldn't register frontend (xc5000)\n");
				ret = -EINVAL;
				जाओ frontend_err;
			पूर्ण
			prपूर्णांकk(KERN_INFO "tm6000: XC5000 asked to be attached to frontend!\n");
			अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा
		prपूर्णांकk(KERN_ERR "tm6000: no frontend found\n");

	dvb->demux.dmx.capabilities = DMX_TS_FILTERING | DMX_SECTION_FILTERING
							    | DMX_MEMORY_BASED_FILTERING;
	dvb->demux.priv = dev;
	dvb->demux.filternum = 8;
	dvb->demux.feednum = 8;
	dvb->demux.start_feed = पंचांग6000_start_feed;
	dvb->demux.stop_feed = पंचांग6000_stop_feed;
	dvb->demux.ग_लिखो_to_decoder = शून्य;
	ret = dvb_dmx_init(&dvb->demux);
	अगर (ret < 0) अणु
		prपूर्णांकk(KERN_ERR "tm6000: dvb_dmx_init failed (errno = %d)\n", ret);
		जाओ frontend_err;
	पूर्ण

	dvb->dmxdev.filternum = dev->dvb->demux.filternum;
	dvb->dmxdev.demux = &dev->dvb->demux.dmx;
	dvb->dmxdev.capabilities = 0;

	ret =  dvb_dmxdev_init(&dvb->dmxdev, &dvb->adapter);
	अगर (ret < 0) अणु
		prपूर्णांकk(KERN_ERR "tm6000: dvb_dmxdev_init failed (errno = %d)\n", ret);
		जाओ dvb_dmx_err;
	पूर्ण

	वापस 0;

dvb_dmx_err:
	dvb_dmx_release(&dvb->demux);
frontend_err:
	अगर (dvb->frontend) अणु
		dvb_unरेजिस्टर_frontend(dvb->frontend);
		dvb_frontend_detach(dvb->frontend);
	पूर्ण
adapter_err:
	dvb_unरेजिस्टर_adapter(&dvb->adapter);
err:
	वापस ret;
पूर्ण

अटल व्योम unरेजिस्टर_dvb(काष्ठा पंचांग6000_core *dev)
अणु
	काष्ठा पंचांग6000_dvb *dvb = dev->dvb;

	अगर (dvb->bulk_urb) अणु
		काष्ठा urb *bulk_urb = dvb->bulk_urb;

		kमुक्त(bulk_urb->transfer_buffer);
		bulk_urb->transfer_buffer = शून्य;
		usb_unlink_urb(bulk_urb);
		usb_मुक्त_urb(bulk_urb);
	पूर्ण

/*	mutex_lock(&पंचांग6000_driver.खोलो_बंद_mutex); */
	अगर (dvb->frontend) अणु
		dvb_unरेजिस्टर_frontend(dvb->frontend);
		dvb_frontend_detach(dvb->frontend);
	पूर्ण

	dvb_dmxdev_release(&dvb->dmxdev);
	dvb_dmx_release(&dvb->demux);
	dvb_unरेजिस्टर_adapter(&dvb->adapter);
	mutex_destroy(&dvb->mutex);
/*	mutex_unlock(&पंचांग6000_driver.खोलो_बंद_mutex); */
पूर्ण

अटल पूर्णांक dvb_init(काष्ठा पंचांग6000_core *dev)
अणु
	काष्ठा पंचांग6000_dvb *dvb;
	पूर्णांक rc;

	अगर (!dev)
		वापस 0;

	अगर (!dev->caps.has_dvb)
		वापस 0;

	अगर (dev->udev->speed == USB_SPEED_FULL) अणु
		prपूर्णांकk(KERN_INFO "This USB2.0 device cannot be run on a USB1.1 port. (it lacks a hardware PID filter)\n");
		वापस 0;
	पूर्ण

	dvb = kzalloc(माप(काष्ठा पंचांग6000_dvb), GFP_KERNEL);
	अगर (!dvb)
		वापस -ENOMEM;

	dev->dvb = dvb;

	rc = रेजिस्टर_dvb(dev);
	अगर (rc < 0) अणु
		kमुक्त(dvb);
		dev->dvb = शून्य;
		वापस 0;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक dvb_fini(काष्ठा पंचांग6000_core *dev)
अणु
	अगर (!dev)
		वापस 0;

	अगर (!dev->caps.has_dvb)
		वापस 0;

	अगर (dev->dvb) अणु
		unरेजिस्टर_dvb(dev);
		kमुक्त(dev->dvb);
		dev->dvb = शून्य;
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा पंचांग6000_ops dvb_ops = अणु
	.type	= TM6000_DVB,
	.name	= "TM6000 dvb Extension",
	.init	= dvb_init,
	.fini	= dvb_fini,
पूर्ण;

अटल पूर्णांक __init पंचांग6000_dvb_रेजिस्टर(व्योम)
अणु
	वापस पंचांग6000_रेजिस्टर_extension(&dvb_ops);
पूर्ण

अटल व्योम __निकास पंचांग6000_dvb_unरेजिस्टर(व्योम)
अणु
	पंचांग6000_unरेजिस्टर_extension(&dvb_ops);
पूर्ण

module_init(पंचांग6000_dvb_रेजिस्टर);
module_निकास(पंचांग6000_dvb_unरेजिस्टर);
