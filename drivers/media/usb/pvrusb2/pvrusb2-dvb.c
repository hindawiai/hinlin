<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  pvrusb2-dvb.c - linux-dvb api पूर्णांकerface to the pvrusb2 driver.
 *
 *  Copyright (C) 2007, 2008 Michael Krufky <mkrufky@linuxtv.org>
 */

#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/मुक्तzer.h>
#समावेश <linux/slab.h>
#समावेश <linux/mm.h>
#समावेश <media/dvbdev.h>
#समावेश "pvrusb2-debug.h"
#समावेश "pvrusb2-hdw-internal.h"
#समावेश "pvrusb2-hdw.h"
#समावेश "pvrusb2-io.h"
#समावेश "pvrusb2-dvb.h"

DVB_DEFINE_MOD_OPT_ADAPTER_NR(adapter_nr);

अटल पूर्णांक pvr2_dvb_feed_func(काष्ठा pvr2_dvb_adapter *adap)
अणु
	पूर्णांक ret;
	अचिन्हित पूर्णांक count;
	काष्ठा pvr2_buffer *bp;
	काष्ठा pvr2_stream *stream;

	pvr2_trace(PVR2_TRACE_DVB_FEED, "dvb feed thread started");
	set_मुक्तzable();

	stream = adap->channel.stream->stream;

	क्रम (;;) अणु
		अगर (kthपढ़ो_should_stop()) अवरोध;

		/* Not sure about this... */
		try_to_मुक्तze();

		bp = pvr2_stream_get_पढ़ोy_buffer(stream);
		अगर (bp != शून्य) अणु
			count = pvr2_buffer_get_count(bp);
			अगर (count) अणु
				dvb_dmx_swfilter(
					&adap->demux,
					adap->buffer_storage[
					    pvr2_buffer_get_id(bp)],
					count);
			पूर्ण अन्यथा अणु
				ret = pvr2_buffer_get_status(bp);
				अगर (ret < 0) अवरोध;
			पूर्ण
			ret = pvr2_buffer_queue(bp);
			अगर (ret < 0) अवरोध;

			/* Since we know we did something to a buffer,
			   just go back and try again.  No poपूर्णांक in
			   blocking unless we really ran out of
			   buffers to process. */
			जारी;
		पूर्ण


		/* Wait until more buffers become available or we're
		   told not to रुको any दीर्घer. */
		ret = रुको_event_पूर्णांकerruptible(
		    adap->buffer_रुको_data,
		    (pvr2_stream_get_पढ़ोy_count(stream) > 0) ||
		    kthपढ़ो_should_stop());
		अगर (ret < 0) अवरोध;
	पूर्ण

	/* If we get here and ret is < 0, then an error has occurred.
	   Probably would be a good idea to communicate that to DVB core... */

	pvr2_trace(PVR2_TRACE_DVB_FEED, "dvb feed thread stopped");

	वापस 0;
पूर्ण

अटल पूर्णांक pvr2_dvb_feed_thपढ़ो(व्योम *data)
अणु
	पूर्णांक stat = pvr2_dvb_feed_func(data);
	/* from videobuf-dvb.c: */
	जबतक (!kthपढ़ो_should_stop()) अणु
		set_current_state(TASK_INTERRUPTIBLE);
		schedule();
	पूर्ण
	वापस stat;
पूर्ण

अटल व्योम pvr2_dvb_notअगरy(काष्ठा pvr2_dvb_adapter *adap)
अणु
	wake_up(&adap->buffer_रुको_data);
पूर्ण

अटल व्योम pvr2_dvb_stream_end(काष्ठा pvr2_dvb_adapter *adap)
अणु
	अचिन्हित पूर्णांक idx;
	काष्ठा pvr2_stream *stream;

	अगर (adap->thपढ़ो) अणु
		kthपढ़ो_stop(adap->thपढ़ो);
		adap->thपढ़ो = शून्य;
	पूर्ण

	अगर (adap->channel.stream) अणु
		stream = adap->channel.stream->stream;
	पूर्ण अन्यथा अणु
		stream = शून्य;
	पूर्ण
	अगर (stream) अणु
		pvr2_hdw_set_streaming(adap->channel.hdw, 0);
		pvr2_stream_set_callback(stream, शून्य, शून्य);
		pvr2_stream_समाप्त(stream);
		pvr2_stream_set_buffer_count(stream, 0);
		pvr2_channel_claim_stream(&adap->channel, शून्य);
	पूर्ण

	अगर (adap->stream_run) अणु
		क्रम (idx = 0; idx < PVR2_DVB_BUFFER_COUNT; idx++) अणु
			अगर (!(adap->buffer_storage[idx])) जारी;
			kमुक्त(adap->buffer_storage[idx]);
			adap->buffer_storage[idx] = शून्य;
		पूर्ण
		adap->stream_run = 0;
	पूर्ण
पूर्ण

अटल पूर्णांक pvr2_dvb_stream_करो_start(काष्ठा pvr2_dvb_adapter *adap)
अणु
	काष्ठा pvr2_context *pvr = adap->channel.mc_head;
	अचिन्हित पूर्णांक idx;
	पूर्णांक ret;
	काष्ठा pvr2_buffer *bp;
	काष्ठा pvr2_stream *stream = शून्य;

	अगर (adap->stream_run) वापस -EIO;

	ret = pvr2_channel_claim_stream(&adap->channel, &pvr->video_stream);
	/* somebody अन्यथा alपढ़ोy has the stream */
	अगर (ret < 0) वापस ret;

	stream = adap->channel.stream->stream;

	क्रम (idx = 0; idx < PVR2_DVB_BUFFER_COUNT; idx++) अणु
		adap->buffer_storage[idx] = kदो_स्मृति(PVR2_DVB_BUFFER_SIZE,
						    GFP_KERNEL);
		अगर (!(adap->buffer_storage[idx])) वापस -ENOMEM;
	पूर्ण

	pvr2_stream_set_callback(pvr->video_stream.stream,
				 (pvr2_stream_callback) pvr2_dvb_notअगरy, adap);

	ret = pvr2_stream_set_buffer_count(stream, PVR2_DVB_BUFFER_COUNT);
	अगर (ret < 0) वापस ret;

	क्रम (idx = 0; idx < PVR2_DVB_BUFFER_COUNT; idx++) अणु
		bp = pvr2_stream_get_buffer(stream, idx);
		pvr2_buffer_set_buffer(bp,
				       adap->buffer_storage[idx],
				       PVR2_DVB_BUFFER_SIZE);
	पूर्ण

	ret = pvr2_hdw_set_streaming(adap->channel.hdw, 1);
	अगर (ret < 0) वापस ret;

	जबतक ((bp = pvr2_stream_get_idle_buffer(stream)) != शून्य) अणु
		ret = pvr2_buffer_queue(bp);
		अगर (ret < 0) वापस ret;
	पूर्ण

	adap->thपढ़ो = kthपढ़ो_run(pvr2_dvb_feed_thपढ़ो, adap, "pvrusb2-dvb");

	अगर (IS_ERR(adap->thपढ़ो)) अणु
		ret = PTR_ERR(adap->thपढ़ो);
		adap->thपढ़ो = शून्य;
		वापस ret;
	पूर्ण

	adap->stream_run = !0;

	वापस 0;
पूर्ण

अटल पूर्णांक pvr2_dvb_stream_start(काष्ठा pvr2_dvb_adapter *adap)
अणु
	पूर्णांक ret = pvr2_dvb_stream_करो_start(adap);
	अगर (ret < 0) pvr2_dvb_stream_end(adap);
	वापस ret;
पूर्ण

अटल पूर्णांक pvr2_dvb_ctrl_feed(काष्ठा dvb_demux_feed *dvbdmxfeed, पूर्णांक onoff)
अणु
	काष्ठा pvr2_dvb_adapter *adap = dvbdmxfeed->demux->priv;
	पूर्णांक ret = 0;

	अगर (adap == शून्य) वापस -ENODEV;

	mutex_lock(&adap->lock);
	करो अणु
		अगर (onoff) अणु
			अगर (!adap->feedcount) अणु
				pvr2_trace(PVR2_TRACE_DVB_FEED,
					   "start feeding demux");
				ret = pvr2_dvb_stream_start(adap);
				अगर (ret < 0) अवरोध;
			पूर्ण
			(adap->feedcount)++;
		पूर्ण अन्यथा अगर (adap->feedcount > 0) अणु
			(adap->feedcount)--;
			अगर (!adap->feedcount) अणु
				pvr2_trace(PVR2_TRACE_DVB_FEED,
					   "stop feeding demux");
				pvr2_dvb_stream_end(adap);
			पूर्ण
		पूर्ण
	पूर्ण जबतक (0);
	mutex_unlock(&adap->lock);

	वापस ret;
पूर्ण

अटल पूर्णांक pvr2_dvb_start_feed(काष्ठा dvb_demux_feed *dvbdmxfeed)
अणु
	pvr2_trace(PVR2_TRACE_DVB_FEED, "start pid: 0x%04x", dvbdmxfeed->pid);
	वापस pvr2_dvb_ctrl_feed(dvbdmxfeed, 1);
पूर्ण

अटल पूर्णांक pvr2_dvb_stop_feed(काष्ठा dvb_demux_feed *dvbdmxfeed)
अणु
	pvr2_trace(PVR2_TRACE_DVB_FEED, "stop pid: 0x%04x", dvbdmxfeed->pid);
	वापस pvr2_dvb_ctrl_feed(dvbdmxfeed, 0);
पूर्ण

अटल पूर्णांक pvr2_dvb_bus_ctrl(काष्ठा dvb_frontend *fe, पूर्णांक acquire)
अणु
	काष्ठा pvr2_dvb_adapter *adap = fe->dvb->priv;
	वापस pvr2_channel_limit_inमाला_दो(
	    &adap->channel,
	    (acquire ? (1 << PVR2_CVAL_INPUT_DTV) : 0));
पूर्ण

अटल पूर्णांक pvr2_dvb_adapter_init(काष्ठा pvr2_dvb_adapter *adap)
अणु
	पूर्णांक ret;

	ret = dvb_रेजिस्टर_adapter(&adap->dvb_adap, "pvrusb2-dvb",
				   THIS_MODULE/*&hdw->usb_dev->owner*/,
				   &adap->channel.hdw->usb_dev->dev,
				   adapter_nr);
	अगर (ret < 0) अणु
		pvr2_trace(PVR2_TRACE_ERROR_LEGS,
			   "dvb_register_adapter failed: error %d", ret);
		जाओ err;
	पूर्ण
	adap->dvb_adap.priv = adap;

	adap->demux.dmx.capabilities = DMX_TS_FILTERING |
				       DMX_SECTION_FILTERING |
				       DMX_MEMORY_BASED_FILTERING;
	adap->demux.priv             = adap;
	adap->demux.filternum        = 256;
	adap->demux.feednum          = 256;
	adap->demux.start_feed       = pvr2_dvb_start_feed;
	adap->demux.stop_feed        = pvr2_dvb_stop_feed;
	adap->demux.ग_लिखो_to_decoder = शून्य;

	ret = dvb_dmx_init(&adap->demux);
	अगर (ret < 0) अणु
		pvr2_trace(PVR2_TRACE_ERROR_LEGS,
			   "dvb_dmx_init failed: error %d", ret);
		जाओ err_dmx;
	पूर्ण

	adap->dmxdev.filternum       = adap->demux.filternum;
	adap->dmxdev.demux           = &adap->demux.dmx;
	adap->dmxdev.capabilities    = 0;

	ret = dvb_dmxdev_init(&adap->dmxdev, &adap->dvb_adap);
	अगर (ret < 0) अणु
		pvr2_trace(PVR2_TRACE_ERROR_LEGS,
			   "dvb_dmxdev_init failed: error %d", ret);
		जाओ err_dmx_dev;
	पूर्ण

	dvb_net_init(&adap->dvb_adap, &adap->dvb_net, &adap->demux.dmx);

	वापस 0;

err_dmx_dev:
	dvb_dmx_release(&adap->demux);
err_dmx:
	dvb_unरेजिस्टर_adapter(&adap->dvb_adap);
err:
	वापस ret;
पूर्ण

अटल पूर्णांक pvr2_dvb_adapter_निकास(काष्ठा pvr2_dvb_adapter *adap)
अणु
	pvr2_trace(PVR2_TRACE_INFO, "unregistering DVB devices");
	dvb_net_release(&adap->dvb_net);
	adap->demux.dmx.बंद(&adap->demux.dmx);
	dvb_dmxdev_release(&adap->dmxdev);
	dvb_dmx_release(&adap->demux);
	dvb_unरेजिस्टर_adapter(&adap->dvb_adap);
	वापस 0;
पूर्ण

अटल पूर्णांक pvr2_dvb_frontend_init(काष्ठा pvr2_dvb_adapter *adap)
अणु
	काष्ठा pvr2_hdw *hdw = adap->channel.hdw;
	स्थिर काष्ठा pvr2_dvb_props *dvb_props = hdw->hdw_desc->dvb_props;
	पूर्णांक ret = 0;

	अगर (dvb_props == शून्य) अणु
		pvr2_trace(PVR2_TRACE_ERROR_LEGS, "fe_props not defined!");
		वापस -EINVAL;
	पूर्ण

	ret = pvr2_channel_limit_inमाला_दो(
	    &adap->channel,
	    (1 << PVR2_CVAL_INPUT_DTV));
	अगर (ret) अणु
		pvr2_trace(PVR2_TRACE_ERROR_LEGS,
			   "failed to grab control of dtv input (code=%d)",
		    ret);
		वापस ret;
	पूर्ण

	अगर (dvb_props->frontend_attach == शून्य) अणु
		pvr2_trace(PVR2_TRACE_ERROR_LEGS,
			   "frontend_attach not defined!");
		ret = -EINVAL;
		जाओ करोne;
	पूर्ण

	अगर (dvb_props->frontend_attach(adap) == 0 && adap->fe[0]) अणु
		अगर (dvb_रेजिस्टर_frontend(&adap->dvb_adap, adap->fe[0])) अणु
			pvr2_trace(PVR2_TRACE_ERROR_LEGS,
				   "frontend registration failed!");
			ret = -ENODEV;
			जाओ fail_frontend0;
		पूर्ण
		अगर (adap->fe[0]->ops.analog_ops.standby)
			adap->fe[0]->ops.analog_ops.standby(adap->fe[0]);

		pvr2_trace(PVR2_TRACE_INFO, "transferring fe[%d] ts_bus_ctrl() to pvr2_dvb_bus_ctrl()",
			   adap->fe[0]->id);
		adap->fe[0]->ops.ts_bus_ctrl = pvr2_dvb_bus_ctrl;
	पूर्ण अन्यथा अणु
		pvr2_trace(PVR2_TRACE_ERROR_LEGS,
			   "no frontend was attached!");
		ret = -ENODEV;
		वापस ret;
	पूर्ण

	अगर (dvb_props->tuner_attach && dvb_props->tuner_attach(adap)) अणु
		pvr2_trace(PVR2_TRACE_ERROR_LEGS, "tuner attach failed");
		ret = -ENODEV;
		जाओ fail_tuner;
	पूर्ण

	अगर (adap->fe[1]) अणु
		adap->fe[1]->id = 1;
		adap->fe[1]->tuner_priv = adap->fe[0]->tuner_priv;
		स_नकल(&adap->fe[1]->ops.tuner_ops,
		       &adap->fe[0]->ops.tuner_ops,
		       माप(काष्ठा dvb_tuner_ops));

		अगर (dvb_रेजिस्टर_frontend(&adap->dvb_adap, adap->fe[1])) अणु
			pvr2_trace(PVR2_TRACE_ERROR_LEGS,
				   "frontend registration failed!");
			ret = -ENODEV;
			जाओ fail_frontend1;
		पूर्ण
		/* MFE lock */
		adap->dvb_adap.mfe_shared = 1;

		अगर (adap->fe[1]->ops.analog_ops.standby)
			adap->fe[1]->ops.analog_ops.standby(adap->fe[1]);

		pvr2_trace(PVR2_TRACE_INFO, "transferring fe[%d] ts_bus_ctrl() to pvr2_dvb_bus_ctrl()",
			   adap->fe[1]->id);
		adap->fe[1]->ops.ts_bus_ctrl = pvr2_dvb_bus_ctrl;
	पूर्ण
करोne:
	pvr2_channel_limit_inमाला_दो(&adap->channel, 0);
	वापस ret;

fail_frontend1:
	dvb_frontend_detach(adap->fe[1]);
	adap->fe[1] = शून्य;
fail_tuner:
	dvb_unरेजिस्टर_frontend(adap->fe[0]);
fail_frontend0:
	dvb_frontend_detach(adap->fe[0]);
	adap->fe[0] = शून्य;
	dvb_module_release(adap->i2c_client_tuner);
	dvb_module_release(adap->i2c_client_demod[1]);
	dvb_module_release(adap->i2c_client_demod[0]);

	वापस ret;
पूर्ण

अटल पूर्णांक pvr2_dvb_frontend_निकास(काष्ठा pvr2_dvb_adapter *adap)
अणु
	अगर (adap->fe[1]) अणु
		dvb_unरेजिस्टर_frontend(adap->fe[1]);
		dvb_frontend_detach(adap->fe[1]);
		adap->fe[1] = शून्य;
	पूर्ण
	अगर (adap->fe[0]) अणु
		dvb_unरेजिस्टर_frontend(adap->fe[0]);
		dvb_frontend_detach(adap->fe[0]);
		adap->fe[0] = शून्य;
	पूर्ण

	dvb_module_release(adap->i2c_client_tuner);
	adap->i2c_client_tuner = शून्य;
	dvb_module_release(adap->i2c_client_demod[1]);
	adap->i2c_client_demod[1] = शून्य;
	dvb_module_release(adap->i2c_client_demod[0]);
	adap->i2c_client_demod[0] = शून्य;

	वापस 0;
पूर्ण

अटल व्योम pvr2_dvb_destroy(काष्ठा pvr2_dvb_adapter *adap)
अणु
	pvr2_dvb_stream_end(adap);
	pvr2_dvb_frontend_निकास(adap);
	pvr2_dvb_adapter_निकास(adap);
	pvr2_channel_करोne(&adap->channel);
	kमुक्त(adap);
पूर्ण

अटल व्योम pvr2_dvb_पूर्णांकernal_check(काष्ठा pvr2_channel *chp)
अणु
	काष्ठा pvr2_dvb_adapter *adap;
	adap = container_of(chp, काष्ठा pvr2_dvb_adapter, channel);
	अगर (!adap->channel.mc_head->disconnect_flag) वापस;
	pvr2_dvb_destroy(adap);
पूर्ण

काष्ठा pvr2_dvb_adapter *pvr2_dvb_create(काष्ठा pvr2_context *pvr)
अणु
	पूर्णांक ret = 0;
	काष्ठा pvr2_dvb_adapter *adap;
	अगर (!pvr->hdw->hdw_desc->dvb_props) अणु
		/* Device lacks a digital पूर्णांकerface so करोn't set up
		   the DVB side of the driver either.  For now. */
		वापस शून्य;
	पूर्ण
	adap = kzalloc(माप(*adap), GFP_KERNEL);
	अगर (!adap) वापस adap;
	pvr2_channel_init(&adap->channel, pvr);
	adap->channel.check_func = pvr2_dvb_पूर्णांकernal_check;
	init_रुकोqueue_head(&adap->buffer_रुको_data);
	mutex_init(&adap->lock);
	ret = pvr2_dvb_adapter_init(adap);
	अगर (ret < 0) जाओ fail1;
	ret = pvr2_dvb_frontend_init(adap);
	अगर (ret < 0) जाओ fail2;
	वापस adap;

fail2:
	pvr2_dvb_adapter_निकास(adap);
fail1:
	pvr2_channel_करोne(&adap->channel);
	वापस शून्य;
पूर्ण

