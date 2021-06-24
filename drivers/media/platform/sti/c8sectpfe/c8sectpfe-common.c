<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * c8sectpfe-common.c - C8SECTPFE STi DVB driver
 *
 * Copyright (c) STMicroelectronics 2015
 *
 *   Author: Peter Grअगरfin <peter.grअगरfin@linaro.org>
 *
 */
#समावेश <linux/completion.h>
#समावेश <linux/delay.h>
#समावेश <linux/device.h>
#समावेश <linux/dvb/dmx.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/ioport.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/समय.स>
#समावेश <linux/रुको.h>

#समावेश <media/dmxdev.h>
#समावेश <media/dvbdev.h>
#समावेश <media/dvb_demux.h>
#समावेश <media/dvb_frontend.h>
#समावेश <media/dvb_net.h>

#समावेश "c8sectpfe-common.h"
#समावेश "c8sectpfe-core.h"
#समावेश "c8sectpfe-dvb.h"

अटल पूर्णांक रेजिस्टर_dvb(काष्ठा stdemux *demux, काष्ठा dvb_adapter *adap,
				व्योम *start_feed, व्योम *stop_feed,
				काष्ठा c8sectpfei *fei)
अणु
	पूर्णांक result;

	demux->dvb_demux.dmx.capabilities = DMX_TS_FILTERING |
					DMX_SECTION_FILTERING |
					DMX_MEMORY_BASED_FILTERING;

	demux->dvb_demux.priv = demux;
	demux->dvb_demux.filternum = C8SECTPFE_MAXCHANNEL;
	demux->dvb_demux.feednum = C8SECTPFE_MAXCHANNEL;

	demux->dvb_demux.start_feed = start_feed;
	demux->dvb_demux.stop_feed = stop_feed;
	demux->dvb_demux.ग_लिखो_to_decoder = शून्य;

	result = dvb_dmx_init(&demux->dvb_demux);
	अगर (result < 0) अणु
		dev_err(fei->dev, "dvb_dmx_init failed (errno = %d)\n",
			result);
		जाओ err_dmx;
	पूर्ण

	demux->dmxdev.filternum = demux->dvb_demux.filternum;
	demux->dmxdev.demux = &demux->dvb_demux.dmx;
	demux->dmxdev.capabilities = 0;

	result = dvb_dmxdev_init(&demux->dmxdev, adap);
	अगर (result < 0) अणु
		dev_err(fei->dev, "dvb_dmxdev_init failed (errno = %d)\n",
			result);

		जाओ err_dmxdev;
	पूर्ण

	demux->hw_frontend.source = DMX_FRONTEND_0 + demux->tsin_index;

	result = demux->dvb_demux.dmx.add_frontend(&demux->dvb_demux.dmx,
						&demux->hw_frontend);
	अगर (result < 0) अणु
		dev_err(fei->dev, "add_frontend failed (errno = %d)\n", result);
		जाओ err_fe_hw;
	पूर्ण

	demux->mem_frontend.source = DMX_MEMORY_FE;
	result = demux->dvb_demux.dmx.add_frontend(&demux->dvb_demux.dmx,
						&demux->mem_frontend);
	अगर (result < 0) अणु
		dev_err(fei->dev, "add_frontend failed (%d)\n", result);
		जाओ err_fe_mem;
	पूर्ण

	result = demux->dvb_demux.dmx.connect_frontend(&demux->dvb_demux.dmx,
							&demux->hw_frontend);
	अगर (result < 0) अणु
		dev_err(fei->dev, "connect_frontend (%d)\n", result);
		जाओ err_fe_con;
	पूर्ण

	वापस 0;

err_fe_con:
	demux->dvb_demux.dmx.हटाओ_frontend(&demux->dvb_demux.dmx,
						     &demux->mem_frontend);
err_fe_mem:
	demux->dvb_demux.dmx.हटाओ_frontend(&demux->dvb_demux.dmx,
						     &demux->hw_frontend);
err_fe_hw:
	dvb_dmxdev_release(&demux->dmxdev);
err_dmxdev:
	dvb_dmx_release(&demux->dvb_demux);
err_dmx:
	वापस result;

पूर्ण

अटल व्योम unरेजिस्टर_dvb(काष्ठा stdemux *demux)
अणु

	demux->dvb_demux.dmx.हटाओ_frontend(&demux->dvb_demux.dmx,
						     &demux->mem_frontend);

	demux->dvb_demux.dmx.हटाओ_frontend(&demux->dvb_demux.dmx,
						     &demux->hw_frontend);

	dvb_dmxdev_release(&demux->dmxdev);

	dvb_dmx_release(&demux->dvb_demux);
पूर्ण

अटल काष्ठा c8sectpfe *c8sectpfe_create(काष्ठा c8sectpfei *fei,
				व्योम *start_feed,
				व्योम *stop_feed)
अणु
	काष्ठा c8sectpfe *c8sectpfe;
	पूर्णांक result;
	पूर्णांक i, j;

	लघु पूर्णांक ids[] = अणु -1 पूर्ण;

	c8sectpfe = kzalloc(माप(काष्ठा c8sectpfe), GFP_KERNEL);
	अगर (!c8sectpfe)
		जाओ err1;

	mutex_init(&c8sectpfe->lock);

	c8sectpfe->device = fei->dev;

	result = dvb_रेजिस्टर_adapter(&c8sectpfe->adapter, "STi c8sectpfe",
					THIS_MODULE, fei->dev, ids);
	अगर (result < 0) अणु
		dev_err(fei->dev, "dvb_register_adapter failed (errno = %d)\n",
			result);
		जाओ err2;
	पूर्ण

	c8sectpfe->adapter.priv = fei;

	क्रम (i = 0; i < fei->tsin_count; i++) अणु

		c8sectpfe->demux[i].tsin_index = i;
		c8sectpfe->demux[i].c8sectpfei = fei;

		result = रेजिस्टर_dvb(&c8sectpfe->demux[i], &c8sectpfe->adapter,
				start_feed, stop_feed, fei);
		अगर (result < 0) अणु
			dev_err(fei->dev,
				"register_dvb feed=%d failed (errno = %d)\n",
				result, i);

			/* we take a all or nothing approach */
			क्रम (j = 0; j < i; j++)
				unरेजिस्टर_dvb(&c8sectpfe->demux[j]);
			जाओ err3;
		पूर्ण
	पूर्ण

	c8sectpfe->num_feeds = fei->tsin_count;

	वापस c8sectpfe;
err3:
	dvb_unरेजिस्टर_adapter(&c8sectpfe->adapter);
err2:
	kमुक्त(c8sectpfe);
err1:
	वापस शून्य;
पूर्ण;

अटल व्योम c8sectpfe_delete(काष्ठा c8sectpfe *c8sectpfe)
अणु
	पूर्णांक i;

	अगर (!c8sectpfe)
		वापस;

	क्रम (i = 0; i < c8sectpfe->num_feeds; i++)
		unरेजिस्टर_dvb(&c8sectpfe->demux[i]);

	dvb_unरेजिस्टर_adapter(&c8sectpfe->adapter);

	kमुक्त(c8sectpfe);
पूर्ण;

व्योम c8sectpfe_tuner_unरेजिस्टर_frontend(काष्ठा c8sectpfe *c8sectpfe,
					काष्ठा c8sectpfei *fei)
अणु
	पूर्णांक n;
	काष्ठा channel_info *tsin;

	क्रम (n = 0; n < fei->tsin_count; n++) अणु

		tsin = fei->channel_data[n];

		अगर (tsin) अणु
			अगर (tsin->frontend) अणु
				dvb_unरेजिस्टर_frontend(tsin->frontend);
				dvb_frontend_detach(tsin->frontend);
			पूर्ण

			i2c_put_adapter(tsin->i2c_adapter);

			अगर (tsin->i2c_client) अणु
				module_put(tsin->i2c_client->dev.driver->owner);
				i2c_unरेजिस्टर_device(tsin->i2c_client);
			पूर्ण
		पूर्ण
	पूर्ण

	c8sectpfe_delete(c8sectpfe);
पूर्ण;

पूर्णांक c8sectpfe_tuner_रेजिस्टर_frontend(काष्ठा c8sectpfe **c8sectpfe,
				काष्ठा c8sectpfei *fei,
				व्योम *start_feed,
				व्योम *stop_feed)
अणु
	काष्ठा channel_info *tsin;
	काष्ठा dvb_frontend *frontend;
	पूर्णांक n, res;

	*c8sectpfe = c8sectpfe_create(fei, start_feed, stop_feed);
	अगर (!*c8sectpfe)
		वापस -ENOMEM;

	क्रम (n = 0; n < fei->tsin_count; n++) अणु
		tsin = fei->channel_data[n];

		res = c8sectpfe_frontend_attach(&frontend, *c8sectpfe, tsin, n);
		अगर (res)
			जाओ err;

		res = dvb_रेजिस्टर_frontend(&c8sectpfe[0]->adapter, frontend);
		अगर (res < 0) अणु
			dev_err(fei->dev, "dvb_register_frontend failed (%d)\n",
				res);
			जाओ err;
		पूर्ण

		tsin->frontend = frontend;
	पूर्ण

	वापस 0;

err:
	c8sectpfe_tuner_unरेजिस्टर_frontend(*c8sectpfe, fei);
	वापस res;
पूर्ण
