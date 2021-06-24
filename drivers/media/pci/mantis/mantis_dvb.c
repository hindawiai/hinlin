<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
	Mantis PCI bridge driver
	Copyright (C) Manu Abraham (abraham.manu@gmail.com)

*/

#समावेश <linux/kernel.h>
#समावेश <linux/bitops.h>

#समावेश <linux/संकेत.स>
#समावेश <linux/sched.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/pci.h>
#समावेश <linux/i2c.h>

#समावेश <media/dmxdev.h>
#समावेश <media/dvbdev.h>
#समावेश <media/dvb_demux.h>
#समावेश <media/dvb_frontend.h>
#समावेश <media/dvb_net.h>

#समावेश "mantis_common.h"
#समावेश "mantis_dma.h"
#समावेश "mantis_ca.h"
#समावेश "mantis_ioc.h"
#समावेश "mantis_dvb.h"

DVB_DEFINE_MOD_OPT_ADAPTER_NR(adapter_nr);

पूर्णांक mantis_frontend_घातer(काष्ठा mantis_pci *mantis, क्रमागत mantis_घातer घातer)
अणु
	काष्ठा mantis_hwconfig *config = mantis->hwconfig;

	चयन (घातer) अणु
	हाल POWER_ON:
		dprपूर्णांकk(MANTIS_DEBUG, 1, "Power ON");
		mantis_gpio_set_bits(mantis, config->घातer, POWER_ON);
		msleep(100);
		mantis_gpio_set_bits(mantis, config->घातer, POWER_ON);
		msleep(100);
		अवरोध;

	हाल POWER_OFF:
		dprपूर्णांकk(MANTIS_DEBUG, 1, "Power OFF");
		mantis_gpio_set_bits(mantis, config->घातer, POWER_OFF);
		msleep(100);
		अवरोध;

	शेष:
		dprपूर्णांकk(MANTIS_DEBUG, 1, "Unknown state <%02x>", घातer);
		वापस -1;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(mantis_frontend_घातer);

व्योम mantis_frontend_soft_reset(काष्ठा mantis_pci *mantis)
अणु
	काष्ठा mantis_hwconfig *config = mantis->hwconfig;

	dprपूर्णांकk(MANTIS_DEBUG, 1, "Frontend RESET");
	mantis_gpio_set_bits(mantis, config->reset, 0);
	msleep(100);
	mantis_gpio_set_bits(mantis, config->reset, 0);
	msleep(100);
	mantis_gpio_set_bits(mantis, config->reset, 1);
	msleep(100);
	mantis_gpio_set_bits(mantis, config->reset, 1);
	msleep(100);

	वापस;
पूर्ण
EXPORT_SYMBOL_GPL(mantis_frontend_soft_reset);

अटल पूर्णांक mantis_frontend_shutकरोwn(काष्ठा mantis_pci *mantis)
अणु
	पूर्णांक err;

	mantis_frontend_soft_reset(mantis);
	err = mantis_frontend_घातer(mantis, POWER_OFF);
	अगर (err != 0) अणु
		dprपूर्णांकk(MANTIS_ERROR, 1, "Frontend POWER OFF failed! <%d>", err);
		वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mantis_dvb_start_feed(काष्ठा dvb_demux_feed *dvbdmxfeed)
अणु
	काष्ठा dvb_demux *dvbdmx = dvbdmxfeed->demux;
	काष्ठा mantis_pci *mantis = dvbdmx->priv;

	dprपूर्णांकk(MANTIS_DEBUG, 1, "Mantis DVB Start feed");
	अगर (!dvbdmx->dmx.frontend) अणु
		dprपूर्णांकk(MANTIS_DEBUG, 1, "no frontend ?");
		वापस -EINVAL;
	पूर्ण

	mantis->feeds++;
	dprपूर्णांकk(MANTIS_DEBUG, 1, "mantis start feed, feeds=%d",	mantis->feeds);

	अगर (mantis->feeds == 1)	 अणु
		dprपूर्णांकk(MANTIS_DEBUG, 1, "mantis start feed & dma");
		mantis_dma_start(mantis);
		tasklet_enable(&mantis->tasklet);
	पूर्ण

	वापस mantis->feeds;
पूर्ण

अटल पूर्णांक mantis_dvb_stop_feed(काष्ठा dvb_demux_feed *dvbdmxfeed)
अणु
	काष्ठा dvb_demux *dvbdmx = dvbdmxfeed->demux;
	काष्ठा mantis_pci *mantis = dvbdmx->priv;

	dprपूर्णांकk(MANTIS_DEBUG, 1, "Mantis DVB Stop feed");
	अगर (!dvbdmx->dmx.frontend) अणु
		dprपूर्णांकk(MANTIS_DEBUG, 1, "no frontend ?");
		वापस -EINVAL;
	पूर्ण

	mantis->feeds--;
	अगर (mantis->feeds == 0) अणु
		dprपूर्णांकk(MANTIS_DEBUG, 1, "mantis stop feed and dma");
		tasklet_disable(&mantis->tasklet);
		mantis_dma_stop(mantis);
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक mantis_dvb_init(काष्ठा mantis_pci *mantis)
अणु
	काष्ठा mantis_hwconfig *config = mantis->hwconfig;
	पूर्णांक result;

	dprपूर्णांकk(MANTIS_DEBUG, 1, "dvb_register_adapter");

	result = dvb_रेजिस्टर_adapter(&mantis->dvb_adapter,
				      "Mantis DVB adapter",
				      THIS_MODULE,
				      &mantis->pdev->dev,
				      adapter_nr);

	अगर (result < 0) अणु

		dprपूर्णांकk(MANTIS_ERROR, 1, "Error registering adapter");
		वापस -ENODEV;
	पूर्ण

	mantis->dvb_adapter.priv	= mantis;
	mantis->demux.dmx.capabilities	= DMX_TS_FILTERING	|
					 DMX_SECTION_FILTERING	|
					 DMX_MEMORY_BASED_FILTERING;

	mantis->demux.priv		= mantis;
	mantis->demux.filternum		= 256;
	mantis->demux.feednum		= 256;
	mantis->demux.start_feed	= mantis_dvb_start_feed;
	mantis->demux.stop_feed		= mantis_dvb_stop_feed;
	mantis->demux.ग_लिखो_to_decoder	= शून्य;

	dprपूर्णांकk(MANTIS_DEBUG, 1, "dvb_dmx_init");
	result = dvb_dmx_init(&mantis->demux);
	अगर (result < 0) अणु
		dprपूर्णांकk(MANTIS_ERROR, 1, "dvb_dmx_init failed, ERROR=%d", result);

		जाओ err0;
	पूर्ण

	mantis->dmxdev.filternum	= 256;
	mantis->dmxdev.demux		= &mantis->demux.dmx;
	mantis->dmxdev.capabilities	= 0;
	dprपूर्णांकk(MANTIS_DEBUG, 1, "dvb_dmxdev_init");

	result = dvb_dmxdev_init(&mantis->dmxdev, &mantis->dvb_adapter);
	अगर (result < 0) अणु

		dprपूर्णांकk(MANTIS_ERROR, 1, "dvb_dmxdev_init failed, ERROR=%d", result);
		जाओ err1;
	पूर्ण

	mantis->fe_hw.source		= DMX_FRONTEND_0;
	result = mantis->demux.dmx.add_frontend(&mantis->demux.dmx, &mantis->fe_hw);
	अगर (result < 0) अणु

		dprपूर्णांकk(MANTIS_ERROR, 1, "dvb_dmx_init failed, ERROR=%d", result);
		जाओ err2;
	पूर्ण

	mantis->fe_mem.source		= DMX_MEMORY_FE;
	result = mantis->demux.dmx.add_frontend(&mantis->demux.dmx, &mantis->fe_mem);
	अगर (result < 0) अणु
		dprपूर्णांकk(MANTIS_ERROR, 1, "dvb_dmx_init failed, ERROR=%d", result);
		जाओ err3;
	पूर्ण

	result = mantis->demux.dmx.connect_frontend(&mantis->demux.dmx, &mantis->fe_hw);
	अगर (result < 0) अणु
		dprपूर्णांकk(MANTIS_ERROR, 1, "dvb_dmx_init failed, ERROR=%d", result);
		जाओ err4;
	पूर्ण

	dvb_net_init(&mantis->dvb_adapter, &mantis->dvbnet, &mantis->demux.dmx);
	tasklet_setup(&mantis->tasklet, mantis_dma_xfer);
	tasklet_disable(&mantis->tasklet);
	अगर (mantis->hwconfig) अणु
		result = config->frontend_init(mantis, mantis->fe);
		अगर (result < 0) अणु
			dprपूर्णांकk(MANTIS_ERROR, 1, "!!! NO Frontends found !!!");
			जाओ err5;
		पूर्ण अन्यथा अणु
			अगर (mantis->fe == शून्य) अणु
				result = -ENOMEM;
				dprपूर्णांकk(MANTIS_ERROR, 1, "FE <NULL>");
				जाओ err5;
			पूर्ण
			result = dvb_रेजिस्टर_frontend(&mantis->dvb_adapter, mantis->fe);
			अगर (result) अणु
				dprपूर्णांकk(MANTIS_ERROR, 1, "ERROR: Frontend registration failed");

				अगर (mantis->fe->ops.release)
					mantis->fe->ops.release(mantis->fe);

				mantis->fe = शून्य;
				जाओ err5;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस 0;

	/* Error conditions ..	*/
err5:
	tasklet_समाप्त(&mantis->tasklet);
	dvb_net_release(&mantis->dvbnet);
	अगर (mantis->fe) अणु
		dvb_unरेजिस्टर_frontend(mantis->fe);
		dvb_frontend_detach(mantis->fe);
	पूर्ण
err4:
	mantis->demux.dmx.हटाओ_frontend(&mantis->demux.dmx, &mantis->fe_mem);

err3:
	mantis->demux.dmx.हटाओ_frontend(&mantis->demux.dmx, &mantis->fe_hw);

err2:
	dvb_dmxdev_release(&mantis->dmxdev);

err1:
	dvb_dmx_release(&mantis->demux);

err0:
	dvb_unरेजिस्टर_adapter(&mantis->dvb_adapter);

	वापस result;
पूर्ण
EXPORT_SYMBOL_GPL(mantis_dvb_init);

पूर्णांक mantis_dvb_निकास(काष्ठा mantis_pci *mantis)
अणु
	पूर्णांक err;

	अगर (mantis->fe) अणु
		/* mantis_ca_निकास(mantis); */
		err = mantis_frontend_shutकरोwn(mantis);
		अगर (err != 0)
			dprपूर्णांकk(MANTIS_ERROR, 1, "Frontend exit while POWER ON! <%d>", err);
		dvb_unरेजिस्टर_frontend(mantis->fe);
		dvb_frontend_detach(mantis->fe);
	पूर्ण

	tasklet_समाप्त(&mantis->tasklet);
	dvb_net_release(&mantis->dvbnet);

	mantis->demux.dmx.हटाओ_frontend(&mantis->demux.dmx, &mantis->fe_mem);
	mantis->demux.dmx.हटाओ_frontend(&mantis->demux.dmx, &mantis->fe_hw);

	dvb_dmxdev_release(&mantis->dmxdev);
	dvb_dmx_release(&mantis->demux);

	dprपूर्णांकk(MANTIS_DEBUG, 1, "dvb_unregister_adapter");
	dvb_unरेजिस्टर_adapter(&mantis->dvb_adapter);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(mantis_dvb_निकास);
