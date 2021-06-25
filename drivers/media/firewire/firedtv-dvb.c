<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * FireDTV driver (क्रमmerly known as FireSAT)
 *
 * Copyright (C) 2004 Andreas Monitzer <andy@monitzer.com>
 * Copyright (C) 2008 Henrik Kurelid <henrik@kurelid.se>
 */

#समावेश <linux/bitops.h>
#समावेश <linux/device.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/types.h>

#समावेश <media/dmxdev.h>
#समावेश <media/dvb_demux.h>
#समावेश <media/dvbdev.h>
#समावेश <media/dvb_frontend.h>

#समावेश "firedtv.h"

अटल पूर्णांक alloc_channel(काष्ठा firedtv *fdtv)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < 16; i++)
		अगर (!__test_and_set_bit(i, &fdtv->channel_active))
			अवरोध;
	वापस i;
पूर्ण

अटल व्योम collect_channels(काष्ठा firedtv *fdtv, पूर्णांक *pidc, u16 pid[])
अणु
	पूर्णांक i, n;

	क्रम (i = 0, n = 0; i < 16; i++)
		अगर (test_bit(i, &fdtv->channel_active))
			pid[n++] = fdtv->channel_pid[i];
	*pidc = n;
पूर्ण

अटल अंतरभूत व्योम dealloc_channel(काष्ठा firedtv *fdtv, पूर्णांक i)
अणु
	__clear_bit(i, &fdtv->channel_active);
पूर्ण

पूर्णांक fdtv_start_feed(काष्ठा dvb_demux_feed *dvbdmxfeed)
अणु
	काष्ठा firedtv *fdtv = dvbdmxfeed->demux->priv;
	पूर्णांक pidc, c, ret;
	u16 pids[16];

	चयन (dvbdmxfeed->type) अणु
	हाल DMX_TYPE_TS:
	हाल DMX_TYPE_SEC:
		अवरोध;
	शेष:
		dev_err(fdtv->device, "can't start dmx feed: invalid type %u\n",
			dvbdmxfeed->type);
		वापस -EINVAL;
	पूर्ण

	अगर (mutex_lock_पूर्णांकerruptible(&fdtv->demux_mutex))
		वापस -EINTR;

	अगर (dvbdmxfeed->type == DMX_TYPE_TS) अणु
		चयन (dvbdmxfeed->pes_type) अणु
		हाल DMX_PES_VIDEO:
		हाल DMX_PES_AUDIO:
		हाल DMX_PES_TELETEXT:
		हाल DMX_PES_PCR:
		हाल DMX_PES_OTHER:
			c = alloc_channel(fdtv);
			अवरोध;
		शेष:
			dev_err(fdtv->device,
				"can't start dmx feed: invalid pes type %u\n",
				dvbdmxfeed->pes_type);
			ret = -EINVAL;
			जाओ out;
		पूर्ण
	पूर्ण अन्यथा अणु
		c = alloc_channel(fdtv);
	पूर्ण

	अगर (c > 15) अणु
		dev_err(fdtv->device, "can't start dmx feed: busy\n");
		ret = -EBUSY;
		जाओ out;
	पूर्ण

	dvbdmxfeed->priv = (typeof(dvbdmxfeed->priv))(अचिन्हित दीर्घ)c;
	fdtv->channel_pid[c] = dvbdmxfeed->pid;
	collect_channels(fdtv, &pidc, pids);

	अगर (dvbdmxfeed->pid == 8192) अणु
		ret = avc_tuner_get_ts(fdtv);
		अगर (ret) अणु
			dealloc_channel(fdtv, c);
			dev_err(fdtv->device, "can't get TS\n");
			जाओ out;
		पूर्ण
	पूर्ण अन्यथा अणु
		ret = avc_tuner_set_pids(fdtv, pidc, pids);
		अगर (ret) अणु
			dealloc_channel(fdtv, c);
			dev_err(fdtv->device, "can't set PIDs\n");
			जाओ out;
		पूर्ण
	पूर्ण
out:
	mutex_unlock(&fdtv->demux_mutex);

	वापस ret;
पूर्ण

पूर्णांक fdtv_stop_feed(काष्ठा dvb_demux_feed *dvbdmxfeed)
अणु
	काष्ठा dvb_demux *demux = dvbdmxfeed->demux;
	काष्ठा firedtv *fdtv = demux->priv;
	पूर्णांक pidc, c, ret;
	u16 pids[16];

	अगर (dvbdmxfeed->type == DMX_TYPE_TS &&
	    !((dvbdmxfeed->ts_type & TS_PACKET) &&
	      (demux->dmx.frontend->source != DMX_MEMORY_FE))) अणु

		अगर (dvbdmxfeed->ts_type & TS_DECODER) अणु
			अगर (dvbdmxfeed->pes_type >= DMX_PES_OTHER ||
			    !demux->pesfilter[dvbdmxfeed->pes_type])
				वापस -EINVAL;

			demux->pids[dvbdmxfeed->pes_type] |= 0x8000;
			demux->pesfilter[dvbdmxfeed->pes_type] = शून्य;
		पूर्ण

		अगर (!(dvbdmxfeed->ts_type & TS_DECODER &&
		      dvbdmxfeed->pes_type < DMX_PES_OTHER))
			वापस 0;
	पूर्ण

	अगर (mutex_lock_पूर्णांकerruptible(&fdtv->demux_mutex))
		वापस -EINTR;

	c = (अचिन्हित दीर्घ)dvbdmxfeed->priv;
	dealloc_channel(fdtv, c);
	collect_channels(fdtv, &pidc, pids);

	ret = avc_tuner_set_pids(fdtv, pidc, pids);

	mutex_unlock(&fdtv->demux_mutex);

	वापस ret;
पूर्ण

DVB_DEFINE_MOD_OPT_ADAPTER_NR(adapter_nr);

पूर्णांक fdtv_dvb_रेजिस्टर(काष्ठा firedtv *fdtv, स्थिर अक्षर *name)
अणु
	पूर्णांक err;

	err = dvb_रेजिस्टर_adapter(&fdtv->adapter, name,
				   THIS_MODULE, fdtv->device, adapter_nr);
	अगर (err < 0)
		जाओ fail_log;

	/*DMX_TS_FILTERING | DMX_SECTION_FILTERING*/
	fdtv->demux.dmx.capabilities = 0;

	fdtv->demux.priv	= fdtv;
	fdtv->demux.filternum	= 16;
	fdtv->demux.feednum	= 16;
	fdtv->demux.start_feed	= fdtv_start_feed;
	fdtv->demux.stop_feed	= fdtv_stop_feed;
	fdtv->demux.ग_लिखो_to_decoder = शून्य;

	err = dvb_dmx_init(&fdtv->demux);
	अगर (err)
		जाओ fail_unreg_adapter;

	fdtv->dmxdev.filternum    = 16;
	fdtv->dmxdev.demux        = &fdtv->demux.dmx;
	fdtv->dmxdev.capabilities = 0;

	err = dvb_dmxdev_init(&fdtv->dmxdev, &fdtv->adapter);
	अगर (err)
		जाओ fail_dmx_release;

	fdtv->frontend.source = DMX_FRONTEND_0;

	err = fdtv->demux.dmx.add_frontend(&fdtv->demux.dmx, &fdtv->frontend);
	अगर (err)
		जाओ fail_dmxdev_release;

	err = fdtv->demux.dmx.connect_frontend(&fdtv->demux.dmx,
					       &fdtv->frontend);
	अगर (err)
		जाओ fail_rem_frontend;

	err = dvb_net_init(&fdtv->adapter, &fdtv->dvbnet, &fdtv->demux.dmx);
	अगर (err)
		जाओ fail_disconnect_frontend;

	fdtv_frontend_init(fdtv, name);
	err = dvb_रेजिस्टर_frontend(&fdtv->adapter, &fdtv->fe);
	अगर (err)
		जाओ fail_net_release;

	err = fdtv_ca_रेजिस्टर(fdtv);
	अगर (err)
		dev_info(fdtv->device,
			 "Conditional Access Module not enabled\n");
	वापस 0;

fail_net_release:
	dvb_net_release(&fdtv->dvbnet);
fail_disconnect_frontend:
	fdtv->demux.dmx.बंद(&fdtv->demux.dmx);
fail_rem_frontend:
	fdtv->demux.dmx.हटाओ_frontend(&fdtv->demux.dmx, &fdtv->frontend);
fail_dmxdev_release:
	dvb_dmxdev_release(&fdtv->dmxdev);
fail_dmx_release:
	dvb_dmx_release(&fdtv->demux);
fail_unreg_adapter:
	dvb_unरेजिस्टर_adapter(&fdtv->adapter);
fail_log:
	dev_err(fdtv->device, "DVB initialization failed\n");
	वापस err;
पूर्ण

व्योम fdtv_dvb_unरेजिस्टर(काष्ठा firedtv *fdtv)
अणु
	fdtv_ca_release(fdtv);
	dvb_unरेजिस्टर_frontend(&fdtv->fe);
	dvb_net_release(&fdtv->dvbnet);
	fdtv->demux.dmx.बंद(&fdtv->demux.dmx);
	fdtv->demux.dmx.हटाओ_frontend(&fdtv->demux.dmx, &fdtv->frontend);
	dvb_dmxdev_release(&fdtv->dmxdev);
	dvb_dmx_release(&fdtv->demux);
	dvb_unरेजिस्टर_adapter(&fdtv->adapter);
पूर्ण
