<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Driver क्रम the Auvitek USB bridge
 *
 *  Copyright (c) 2008 Steven Toth <stoth@linuxtv.org>
 */

#समावेश "au0828.h"

#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/init.h>
#समावेश <linux/device.h>
#समावेश <media/v4l2-common.h>
#समावेश <media/tuner.h>

#समावेश "au8522.h"
#समावेश "xc5000.h"
#समावेश "mxl5007t.h"
#समावेश "tda18271.h"

अटल पूर्णांक pपुनः_स्मृतिate_big_buffers;
module_param_named(pपुनः_स्मृतिate_big_buffers, pपुनः_स्मृतिate_big_buffers, पूर्णांक, 0644);
MODULE_PARM_DESC(pपुनः_स्मृतिate_big_buffers, "Preallocate the larger transfer buffers at module load time");

DVB_DEFINE_MOD_OPT_ADAPTER_NR(adapter_nr);

#घोषणा _AU0828_BULKPIPE 0x83
#घोषणा _BULKPIPESIZE 0xe522

अटल u8 hauppauge_hvr950q_led_states[] = अणु
	0x00, /* off */
	0x02, /* yellow */
	0x04, /* green */
पूर्ण;

अटल काष्ठा au8522_led_config hauppauge_hvr950q_led_cfg = अणु
	.gpio_output = 0x00e0,
	.gpio_output_enable  = 0x6006,
	.gpio_output_disable = 0x0660,

	.gpio_leds = 0x00e2,
	.led_states  = hauppauge_hvr950q_led_states,
	.num_led_states = माप(hauppauge_hvr950q_led_states),

	.vsb8_strong   = 20 /* dB */ * 10,
	.qam64_strong  = 25 /* dB */ * 10,
	.qam256_strong = 32 /* dB */ * 10,
पूर्ण;

अटल काष्ठा au8522_config hauppauge_hvr950q_config = अणु
	.demod_address = 0x8e >> 1,
	.status_mode   = AU8522_DEMODLOCKING,
	.qam_अगर        = AU8522_IF_6MHZ,
	.vsb_अगर        = AU8522_IF_6MHZ,
	.led_cfg       = &hauppauge_hvr950q_led_cfg,
पूर्ण;

अटल काष्ठा au8522_config fusionhdtv7usb_config = अणु
	.demod_address = 0x8e >> 1,
	.status_mode   = AU8522_DEMODLOCKING,
	.qam_अगर        = AU8522_IF_6MHZ,
	.vsb_अगर        = AU8522_IF_6MHZ,
पूर्ण;

अटल काष्ठा au8522_config hauppauge_woodbury_config = अणु
	.demod_address = 0x8e >> 1,
	.status_mode   = AU8522_DEMODLOCKING,
	.qam_अगर        = AU8522_IF_4MHZ,
	.vsb_अगर        = AU8522_IF_3_25MHZ,
पूर्ण;

अटल काष्ठा xc5000_config hauppauge_xc5000a_config = अणु
	.i2c_address      = 0x61,
	.अगर_khz           = 6000,
	.chip_id          = XC5000A,
	.output_amp       = 0x8f,
पूर्ण;

अटल काष्ठा xc5000_config hauppauge_xc5000c_config = अणु
	.i2c_address      = 0x61,
	.अगर_khz           = 6000,
	.chip_id          = XC5000C,
	.output_amp       = 0x8f,
पूर्ण;

अटल काष्ठा mxl5007t_config mxl5007t_hvr950q_config = अणु
	.xtal_freq_hz = MxL_XTAL_24_MHZ,
	.अगर_freq_hz = MxL_IF_6_MHZ,
पूर्ण;

अटल काष्ठा tda18271_config hauppauge_woodbury_tunerconfig = अणु
	.gate    = TDA18271_GATE_DIGITAL,
पूर्ण;

अटल व्योम au0828_restart_dvb_streaming(काष्ठा work_काष्ठा *work);

अटल व्योम au0828_bulk_समयout(काष्ठा समयr_list *t)
अणु
	काष्ठा au0828_dev *dev = from_समयr(dev, t, bulk_समयout);

	dprपूर्णांकk(1, "%s called\n", __func__);
	dev->bulk_समयout_running = 0;
	schedule_work(&dev->restart_streaming);
पूर्ण

/*-------------------------------------------------------------------*/
अटल व्योम urb_completion(काष्ठा urb *purb)
अणु
	काष्ठा au0828_dev *dev = purb->context;
	पूर्णांक ptype = usb_pipetype(purb->pipe);
	अचिन्हित अक्षर *ptr;

	dprपूर्णांकk(2, "%s: %d\n", __func__, purb->actual_length);

	अगर (!dev) अणु
		dprपूर्णांकk(2, "%s: no dev!\n", __func__);
		वापस;
	पूर्ण

	अगर (!dev->urb_streaming) अणु
		dprपूर्णांकk(2, "%s: not streaming!\n", __func__);
		वापस;
	पूर्ण

	अगर (ptype != PIPE_BULK) अणु
		pr_err("%s: Unsupported URB type %d\n",
		       __func__, ptype);
		वापस;
	पूर्ण

	/* See अगर the stream is corrupted (to work around a hardware
	   bug where the stream माला_लो misaligned */
	ptr = purb->transfer_buffer;
	अगर (purb->actual_length > 0 && ptr[0] != 0x47) अणु
		dprपूर्णांकk(1, "Need to restart streaming %02x len=%d!\n",
			ptr[0], purb->actual_length);
		schedule_work(&dev->restart_streaming);
		वापस;
	पूर्ण अन्यथा अगर (dev->bulk_समयout_running == 1) अणु
		/* The URB handler has fired, so cancel समयr which would
		 * restart endpoपूर्णांक अगर we hadn't
		 */
		dprपूर्णांकk(1, "%s cancelling bulk timeout\n", __func__);
		dev->bulk_समयout_running = 0;
		del_समयr(&dev->bulk_समयout);
	पूर्ण

	/* Feed the transport payload पूर्णांकo the kernel demux */
	dvb_dmx_swfilter_packets(&dev->dvb.demux,
		purb->transfer_buffer, purb->actual_length / 188);

	/* Clean the buffer beक्रमe we requeue */
	स_रखो(purb->transfer_buffer, 0, URB_बफ_मानE);

	/* Requeue URB */
	usb_submit_urb(purb, GFP_ATOMIC);
पूर्ण

अटल पूर्णांक stop_urb_transfer(काष्ठा au0828_dev *dev)
अणु
	पूर्णांक i;

	dprपूर्णांकk(2, "%s()\n", __func__);

	अगर (!dev->urb_streaming)
		वापस 0;

	अगर (dev->bulk_समयout_running == 1) अणु
		dev->bulk_समयout_running = 0;
		del_समयr(&dev->bulk_समयout);
	पूर्ण

	dev->urb_streaming = false;
	क्रम (i = 0; i < URB_COUNT; i++) अणु
		अगर (dev->urbs[i]) अणु
			usb_समाप्त_urb(dev->urbs[i]);
			अगर (!pपुनः_स्मृतिate_big_buffers)
				kमुक्त(dev->urbs[i]->transfer_buffer);

			usb_मुक्त_urb(dev->urbs[i]);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक start_urb_transfer(काष्ठा au0828_dev *dev)
अणु
	काष्ठा urb *purb;
	पूर्णांक i, ret;

	dprपूर्णांकk(2, "%s()\n", __func__);

	अगर (dev->urb_streaming) अणु
		dprपूर्णांकk(2, "%s: bulk xfer already running!\n", __func__);
		वापस 0;
	पूर्ण

	क्रम (i = 0; i < URB_COUNT; i++) अणु

		dev->urbs[i] = usb_alloc_urb(0, GFP_KERNEL);
		अगर (!dev->urbs[i])
			वापस -ENOMEM;

		purb = dev->urbs[i];

		अगर (pपुनः_स्मृतिate_big_buffers)
			purb->transfer_buffer = dev->dig_transfer_buffer[i];
		अन्यथा
			purb->transfer_buffer = kzalloc(URB_बफ_मानE,
					GFP_KERNEL);

		अगर (!purb->transfer_buffer) अणु
			usb_मुक्त_urb(purb);
			dev->urbs[i] = शून्य;
			ret = -ENOMEM;
			pr_err("%s: failed big buffer allocation, err = %d\n",
			       __func__, ret);
			वापस ret;
		पूर्ण

		purb->status = -EINPROGRESS;
		usb_fill_bulk_urb(purb,
				  dev->usbdev,
				  usb_rcvbulkpipe(dev->usbdev,
					_AU0828_BULKPIPE),
				  purb->transfer_buffer,
				  URB_बफ_मानE,
				  urb_completion,
				  dev);

	पूर्ण

	क्रम (i = 0; i < URB_COUNT; i++) अणु
		ret = usb_submit_urb(dev->urbs[i], GFP_ATOMIC);
		अगर (ret != 0) अणु
			stop_urb_transfer(dev);
			pr_err("%s: failed urb submission, err = %d\n",
			       __func__, ret);
			वापस ret;
		पूर्ण
	पूर्ण

	dev->urb_streaming = true;

	/* If we करोn't valid data within 1 second, restart stream */
	mod_समयr(&dev->bulk_समयout, jअगरfies + (HZ));
	dev->bulk_समयout_running = 1;

	वापस 0;
पूर्ण

अटल व्योम au0828_start_transport(काष्ठा au0828_dev *dev)
अणु
	au0828_ग_लिखो(dev, 0x608, 0x90);
	au0828_ग_लिखो(dev, 0x609, 0x72);
	au0828_ग_लिखो(dev, 0x60a, 0x71);
	au0828_ग_लिखो(dev, 0x60b, 0x01);

पूर्ण

अटल व्योम au0828_stop_transport(काष्ठा au0828_dev *dev, पूर्णांक full_stop)
अणु
	अगर (full_stop) अणु
		au0828_ग_लिखो(dev, 0x608, 0x00);
		au0828_ग_लिखो(dev, 0x609, 0x00);
		au0828_ग_लिखो(dev, 0x60a, 0x00);
	पूर्ण
	au0828_ग_लिखो(dev, 0x60b, 0x00);
पूर्ण

अटल पूर्णांक au0828_dvb_start_feed(काष्ठा dvb_demux_feed *feed)
अणु
	काष्ठा dvb_demux *demux = feed->demux;
	काष्ठा au0828_dev *dev = (काष्ठा au0828_dev *) demux->priv;
	काष्ठा au0828_dvb *dvb = &dev->dvb;
	पूर्णांक ret = 0;

	dprपूर्णांकk(1, "%s()\n", __func__);

	अगर (!demux->dmx.frontend)
		वापस -EINVAL;

	अगर (dvb->frontend) अणु
		mutex_lock(&dvb->lock);
		dvb->start_count++;
		dprपूर्णांकk(1, "%s(), start_count: %d, stop_count: %d\n", __func__,
			dvb->start_count, dvb->stop_count);
		अगर (dvb->feeding++ == 0) अणु
			/* Start transport */
			au0828_start_transport(dev);
			ret = start_urb_transfer(dev);
			अगर (ret < 0) अणु
				au0828_stop_transport(dev, 0);
				dvb->feeding--;	/* We ran out of memory... */
			पूर्ण
		पूर्ण
		mutex_unlock(&dvb->lock);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक au0828_dvb_stop_feed(काष्ठा dvb_demux_feed *feed)
अणु
	काष्ठा dvb_demux *demux = feed->demux;
	काष्ठा au0828_dev *dev = (काष्ठा au0828_dev *) demux->priv;
	काष्ठा au0828_dvb *dvb = &dev->dvb;
	पूर्णांक ret = 0;

	dprपूर्णांकk(1, "%s()\n", __func__);

	अगर (dvb->frontend) अणु
		cancel_work_sync(&dev->restart_streaming);

		mutex_lock(&dvb->lock);
		dvb->stop_count++;
		dprपूर्णांकk(1, "%s(), start_count: %d, stop_count: %d\n", __func__,
			dvb->start_count, dvb->stop_count);
		अगर (dvb->feeding > 0) अणु
			dvb->feeding--;
			अगर (dvb->feeding == 0) अणु
				/* Stop transport */
				ret = stop_urb_transfer(dev);
				au0828_stop_transport(dev, 0);
			पूर्ण
		पूर्ण
		mutex_unlock(&dvb->lock);
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम au0828_restart_dvb_streaming(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा au0828_dev *dev = container_of(work, काष्ठा au0828_dev,
					      restart_streaming);
	काष्ठा au0828_dvb *dvb = &dev->dvb;

	अगर (!dev->urb_streaming)
		वापस;

	dprपूर्णांकk(1, "Restarting streaming...!\n");

	mutex_lock(&dvb->lock);

	/* Stop transport */
	stop_urb_transfer(dev);
	au0828_stop_transport(dev, 1);

	/* Start transport */
	au0828_start_transport(dev);
	start_urb_transfer(dev);

	mutex_unlock(&dvb->lock);
पूर्ण

अटल पूर्णांक au0828_set_frontend(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा au0828_dev *dev = fe->dvb->priv;
	काष्ठा au0828_dvb *dvb = &dev->dvb;
	पूर्णांक ret, was_streaming;

	mutex_lock(&dvb->lock);
	was_streaming = dev->urb_streaming;
	अगर (was_streaming) अणु
		au0828_stop_transport(dev, 1);

		/*
		 * We can't hold a mutex here, as the restart_streaming
		 * kthपढ़ो may also hold it.
		 */
		mutex_unlock(&dvb->lock);
		cancel_work_sync(&dev->restart_streaming);
		mutex_lock(&dvb->lock);

		stop_urb_transfer(dev);
	पूर्ण
	mutex_unlock(&dvb->lock);

	ret = dvb->set_frontend(fe);

	अगर (was_streaming) अणु
		mutex_lock(&dvb->lock);
		au0828_start_transport(dev);
		start_urb_transfer(dev);
		mutex_unlock(&dvb->lock);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक dvb_रेजिस्टर(काष्ठा au0828_dev *dev)
अणु
	काष्ठा au0828_dvb *dvb = &dev->dvb;
	पूर्णांक result;

	dprपूर्णांकk(1, "%s()\n", __func__);

	अगर (pपुनः_स्मृतिate_big_buffers) अणु
		पूर्णांक i;
		क्रम (i = 0; i < URB_COUNT; i++) अणु
			dev->dig_transfer_buffer[i] = kzalloc(URB_बफ_मानE,
					GFP_KERNEL);

			अगर (!dev->dig_transfer_buffer[i]) अणु
				result = -ENOMEM;

				pr_err("failed buffer allocation (errno = %d)\n",
				       result);
				जाओ fail_adapter;
			पूर्ण
		पूर्ण
	पूर्ण

	INIT_WORK(&dev->restart_streaming, au0828_restart_dvb_streaming);

	/* रेजिस्टर adapter */
	result = dvb_रेजिस्टर_adapter(&dvb->adapter,
				      KBUILD_MODNAME, THIS_MODULE,
				      &dev->usbdev->dev, adapter_nr);
	अगर (result < 0) अणु
		pr_err("dvb_register_adapter failed (errno = %d)\n",
		       result);
		जाओ fail_adapter;
	पूर्ण

#अगर_घोषित CONFIG_MEDIA_CONTROLLER_DVB
	dvb->adapter.mdev = dev->media_dev;
#पूर्ण_अगर

	dvb->adapter.priv = dev;

	/* रेजिस्टर frontend */
	result = dvb_रेजिस्टर_frontend(&dvb->adapter, dvb->frontend);
	अगर (result < 0) अणु
		pr_err("dvb_register_frontend failed (errno = %d)\n",
		       result);
		जाओ fail_frontend;
	पूर्ण

	/* Hook dvb frontend */
	dvb->set_frontend = dvb->frontend->ops.set_frontend;
	dvb->frontend->ops.set_frontend = au0828_set_frontend;

	/* रेजिस्टर demux stuff */
	dvb->demux.dmx.capabilities =
		DMX_TS_FILTERING | DMX_SECTION_FILTERING |
		DMX_MEMORY_BASED_FILTERING;
	dvb->demux.priv       = dev;
	dvb->demux.filternum  = 256;
	dvb->demux.feednum    = 256;
	dvb->demux.start_feed = au0828_dvb_start_feed;
	dvb->demux.stop_feed  = au0828_dvb_stop_feed;
	result = dvb_dmx_init(&dvb->demux);
	अगर (result < 0) अणु
		pr_err("dvb_dmx_init failed (errno = %d)\n", result);
		जाओ fail_dmx;
	पूर्ण

	dvb->dmxdev.filternum    = 256;
	dvb->dmxdev.demux        = &dvb->demux.dmx;
	dvb->dmxdev.capabilities = 0;
	result = dvb_dmxdev_init(&dvb->dmxdev, &dvb->adapter);
	अगर (result < 0) अणु
		pr_err("dvb_dmxdev_init failed (errno = %d)\n", result);
		जाओ fail_dmxdev;
	पूर्ण

	dvb->fe_hw.source = DMX_FRONTEND_0;
	result = dvb->demux.dmx.add_frontend(&dvb->demux.dmx, &dvb->fe_hw);
	अगर (result < 0) अणु
		pr_err("add_frontend failed (DMX_FRONTEND_0, errno = %d)\n",
		       result);
		जाओ fail_fe_hw;
	पूर्ण

	dvb->fe_mem.source = DMX_MEMORY_FE;
	result = dvb->demux.dmx.add_frontend(&dvb->demux.dmx, &dvb->fe_mem);
	अगर (result < 0) अणु
		pr_err("add_frontend failed (DMX_MEMORY_FE, errno = %d)\n",
		       result);
		जाओ fail_fe_mem;
	पूर्ण

	result = dvb->demux.dmx.connect_frontend(&dvb->demux.dmx, &dvb->fe_hw);
	अगर (result < 0) अणु
		pr_err("connect_frontend failed (errno = %d)\n", result);
		जाओ fail_fe_conn;
	पूर्ण

	/* रेजिस्टर network adapter */
	dvb_net_init(&dvb->adapter, &dvb->net, &dvb->demux.dmx);

	dvb->start_count = 0;
	dvb->stop_count = 0;

	result = dvb_create_media_graph(&dvb->adapter, false);
	अगर (result < 0)
		जाओ fail_create_graph;

	वापस 0;

fail_create_graph:
	dvb_net_release(&dvb->net);
fail_fe_conn:
	dvb->demux.dmx.हटाओ_frontend(&dvb->demux.dmx, &dvb->fe_mem);
fail_fe_mem:
	dvb->demux.dmx.हटाओ_frontend(&dvb->demux.dmx, &dvb->fe_hw);
fail_fe_hw:
	dvb_dmxdev_release(&dvb->dmxdev);
fail_dmxdev:
	dvb_dmx_release(&dvb->demux);
fail_dmx:
	dvb_unरेजिस्टर_frontend(dvb->frontend);
fail_frontend:
	dvb_frontend_detach(dvb->frontend);
	dvb_unरेजिस्टर_adapter(&dvb->adapter);
fail_adapter:

	अगर (pपुनः_स्मृतिate_big_buffers) अणु
		पूर्णांक i;
		क्रम (i = 0; i < URB_COUNT; i++)
			kमुक्त(dev->dig_transfer_buffer[i]);
	पूर्ण

	वापस result;
पूर्ण

व्योम au0828_dvb_unरेजिस्टर(काष्ठा au0828_dev *dev)
अणु
	काष्ठा au0828_dvb *dvb = &dev->dvb;

	dprपूर्णांकk(1, "%s()\n", __func__);

	अगर (dvb->frontend == शून्य)
		वापस;

	cancel_work_sync(&dev->restart_streaming);

	dvb_net_release(&dvb->net);
	dvb->demux.dmx.हटाओ_frontend(&dvb->demux.dmx, &dvb->fe_mem);
	dvb->demux.dmx.हटाओ_frontend(&dvb->demux.dmx, &dvb->fe_hw);
	dvb_dmxdev_release(&dvb->dmxdev);
	dvb_dmx_release(&dvb->demux);
	dvb_unरेजिस्टर_frontend(dvb->frontend);
	dvb_frontend_detach(dvb->frontend);
	dvb_unरेजिस्टर_adapter(&dvb->adapter);

	अगर (pपुनः_स्मृतिate_big_buffers) अणु
		पूर्णांक i;
		क्रम (i = 0; i < URB_COUNT; i++)
			kमुक्त(dev->dig_transfer_buffer[i]);
	पूर्ण
	dvb->frontend = शून्य;
पूर्ण

/* All the DVB attach calls go here, this function माला_लो modअगरied
 * क्रम each new card. No other function in this file needs
 * to change.
 */
पूर्णांक au0828_dvb_रेजिस्टर(काष्ठा au0828_dev *dev)
अणु
	काष्ठा au0828_dvb *dvb = &dev->dvb;
	पूर्णांक ret;

	dprपूर्णांकk(1, "%s()\n", __func__);

	/* init frontend */
	चयन (dev->boardnr) अणु
	हाल AU0828_BOARD_HAUPPAUGE_HVR850:
	हाल AU0828_BOARD_HAUPPAUGE_HVR950Q:
		dvb->frontend = dvb_attach(au8522_attach,
				&hauppauge_hvr950q_config,
				&dev->i2c_adap);
		अगर (dvb->frontend != शून्य)
			चयन (dev->board.tuner_type) अणु
			शेष:
			हाल TUNER_XC5000:
				dvb_attach(xc5000_attach, dvb->frontend,
					   &dev->i2c_adap,
					   &hauppauge_xc5000a_config);
				अवरोध;
			हाल TUNER_XC5000C:
				dvb_attach(xc5000_attach, dvb->frontend,
					   &dev->i2c_adap,
					   &hauppauge_xc5000c_config);
				अवरोध;
			पूर्ण
		अवरोध;
	हाल AU0828_BOARD_HAUPPAUGE_HVR950Q_MXL:
		dvb->frontend = dvb_attach(au8522_attach,
				&hauppauge_hvr950q_config,
				&dev->i2c_adap);
		अगर (dvb->frontend != शून्य)
			dvb_attach(mxl5007t_attach, dvb->frontend,
				   &dev->i2c_adap, 0x60,
				   &mxl5007t_hvr950q_config);
		अवरोध;
	हाल AU0828_BOARD_HAUPPAUGE_WOODBURY:
		dvb->frontend = dvb_attach(au8522_attach,
				&hauppauge_woodbury_config,
				&dev->i2c_adap);
		अगर (dvb->frontend != शून्य)
			dvb_attach(tda18271_attach, dvb->frontend,
				   0x60, &dev->i2c_adap,
				   &hauppauge_woodbury_tunerconfig);
		अवरोध;
	हाल AU0828_BOARD_DVICO_FUSIONHDTV7:
		dvb->frontend = dvb_attach(au8522_attach,
				&fusionhdtv7usb_config,
				&dev->i2c_adap);
		अगर (dvb->frontend != शून्य) अणु
			dvb_attach(xc5000_attach, dvb->frontend,
				&dev->i2c_adap,
				&hauppauge_xc5000a_config);
		पूर्ण
		अवरोध;
	शेष:
		pr_warn("The frontend of your DVB/ATSC card isn't supported yet\n");
		अवरोध;
	पूर्ण
	अगर (शून्य == dvb->frontend) अणु
		pr_err("%s() Frontend initialization failed\n",
		       __func__);
		वापस -1;
	पूर्ण
	/* define general-purpose callback poपूर्णांकer */
	dvb->frontend->callback = au0828_tuner_callback;

	/* रेजिस्टर everything */
	ret = dvb_रेजिस्टर(dev);
	अगर (ret < 0) अणु
		अगर (dvb->frontend->ops.release)
			dvb->frontend->ops.release(dvb->frontend);
		dvb->frontend = शून्य;
		वापस ret;
	पूर्ण

	समयr_setup(&dev->bulk_समयout, au0828_bulk_समयout, 0);

	वापस 0;
पूर्ण

व्योम au0828_dvb_suspend(काष्ठा au0828_dev *dev)
अणु
	काष्ठा au0828_dvb *dvb = &dev->dvb;
	पूर्णांक rc;

	अगर (dvb->frontend) अणु
		अगर (dev->urb_streaming) अणु
			cancel_work_sync(&dev->restart_streaming);
			/* Stop transport */
			mutex_lock(&dvb->lock);
			stop_urb_transfer(dev);
			au0828_stop_transport(dev, 1);
			mutex_unlock(&dvb->lock);
			dev->need_urb_start = true;
		पूर्ण
		/* suspend frontend - करोes tuner and fe to sleep */
		rc = dvb_frontend_suspend(dvb->frontend);
		pr_info("au0828_dvb_suspend(): Suspending DVB fe %d\n", rc);
	पूर्ण
पूर्ण

व्योम au0828_dvb_resume(काष्ठा au0828_dev *dev)
अणु
	काष्ठा au0828_dvb *dvb = &dev->dvb;
	पूर्णांक rc;

	अगर (dvb->frontend) अणु
		/* resume frontend - करोes fe and tuner init */
		rc = dvb_frontend_resume(dvb->frontend);
		pr_info("au0828_dvb_resume(): Resuming DVB fe %d\n", rc);
		अगर (dev->need_urb_start) अणु
			/* Start transport */
			mutex_lock(&dvb->lock);
			au0828_start_transport(dev);
			start_urb_transfer(dev);
			mutex_unlock(&dvb->lock);
		पूर्ण
	पूर्ण
पूर्ण
