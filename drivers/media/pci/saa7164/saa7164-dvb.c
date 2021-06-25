<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Driver क्रम the NXP SAA7164 PCIe bridge
 *
 *  Copyright (c) 2010-2015 Steven Toth <stoth@kernelद_असल.com>
 */

#समावेश "saa7164.h"

#समावेश "tda10048.h"
#समावेश "tda18271.h"
#समावेश "s5h1411.h"
#समावेश "si2157.h"
#समावेश "si2168.h"
#समावेश "lgdt3306a.h"

#घोषणा DRIVER_NAME "saa7164"

DVB_DEFINE_MOD_OPT_ADAPTER_NR(adapter_nr);

/* addr is in the card काष्ठा, get it from there */
अटल काष्ठा tda10048_config hauppauge_hvr2200_1_config = अणु
	.demod_address    = 0x10 >> 1,
	.output_mode      = TDA10048_SERIAL_OUTPUT,
	.fwbulkग_लिखोlen   = TDA10048_BULKWRITE_200,
	.inversion        = TDA10048_INVERSION_ON,
	.dtv6_अगर_freq_khz = TDA10048_IF_3300,
	.dtv7_अगर_freq_khz = TDA10048_IF_3500,
	.dtv8_अगर_freq_khz = TDA10048_IF_4000,
	.clk_freq_khz     = TDA10048_CLK_16000,
पूर्ण;
अटल काष्ठा tda10048_config hauppauge_hvr2200_2_config = अणु
	.demod_address    = 0x12 >> 1,
	.output_mode      = TDA10048_SERIAL_OUTPUT,
	.fwbulkग_लिखोlen   = TDA10048_BULKWRITE_200,
	.inversion        = TDA10048_INVERSION_ON,
	.dtv6_अगर_freq_khz = TDA10048_IF_3300,
	.dtv7_अगर_freq_khz = TDA10048_IF_3500,
	.dtv8_अगर_freq_khz = TDA10048_IF_4000,
	.clk_freq_khz     = TDA10048_CLK_16000,
पूर्ण;

अटल काष्ठा tda18271_std_map hauppauge_tda18271_std_map = अणु
	.atsc_6   = अणु .अगर_freq = 3250, .agc_mode = 3, .std = 3,
		      .अगर_lvl = 6, .rfagc_top = 0x37 पूर्ण,
	.qam_6    = अणु .अगर_freq = 4000, .agc_mode = 3, .std = 0,
		      .अगर_lvl = 6, .rfagc_top = 0x37 पूर्ण,
पूर्ण;

अटल काष्ठा tda18271_config hauppauge_hvr22x0_tuner_config = अणु
	.std_map	= &hauppauge_tda18271_std_map,
	.gate		= TDA18271_GATE_ANALOG,
	.role		= TDA18271_MASTER,
पूर्ण;

अटल काष्ठा tda18271_config hauppauge_hvr22x0s_tuner_config = अणु
	.std_map	= &hauppauge_tda18271_std_map,
	.gate		= TDA18271_GATE_ANALOG,
	.role		= TDA18271_SLAVE,
	.output_opt     = TDA18271_OUTPUT_LT_OFF,
	.rf_cal_on_startup = 1
पूर्ण;

अटल काष्ठा s5h1411_config hauppauge_s5h1411_config = अणु
	.output_mode   = S5H1411_SERIAL_OUTPUT,
	.gpio          = S5H1411_GPIO_ON,
	.qam_अगर        = S5H1411_IF_4000,
	.vsb_अगर        = S5H1411_IF_3250,
	.inversion     = S5H1411_INVERSION_ON,
	.status_mode   = S5H1411_DEMODLOCKING,
	.mpeg_timing   = S5H1411_MPEGTIMING_CONTINUOUS_NONINVERTING_CLOCK,
पूर्ण;

अटल काष्ठा lgdt3306a_config hauppauge_hvr2255a_config = अणु
	.i2c_addr               = 0xb2 >> 1,
	.qam_अगर_khz             = 4000,
	.vsb_अगर_khz             = 3250,
	.deny_i2c_rptr          = 1, /* Disabled */
	.spectral_inversion     = 0, /* Disabled */
	.mpeg_mode              = LGDT3306A_MPEG_SERIAL,
	.tpclk_edge             = LGDT3306A_TPCLK_RISING_EDGE,
	.tpvalid_polarity       = LGDT3306A_TP_VALID_HIGH,
	.xtalMHz                = 25, /* 24 or 25 */
पूर्ण;

अटल काष्ठा lgdt3306a_config hauppauge_hvr2255b_config = अणु
	.i2c_addr               = 0x1c >> 1,
	.qam_अगर_khz             = 4000,
	.vsb_अगर_khz             = 3250,
	.deny_i2c_rptr          = 1, /* Disabled */
	.spectral_inversion     = 0, /* Disabled */
	.mpeg_mode              = LGDT3306A_MPEG_SERIAL,
	.tpclk_edge             = LGDT3306A_TPCLK_RISING_EDGE,
	.tpvalid_polarity       = LGDT3306A_TP_VALID_HIGH,
	.xtalMHz                = 25, /* 24 or 25 */
पूर्ण;

अटल काष्ठा si2157_config hauppauge_hvr2255_tuner_config = अणु
	.inversion = 1,
	.अगर_port = 1,
पूर्ण;

अटल पूर्णांक si2157_attach(काष्ठा saa7164_port *port, काष्ठा i2c_adapter *adapter,
	काष्ठा dvb_frontend *fe, u8 addr8bit, काष्ठा si2157_config *cfg)
अणु
	काष्ठा i2c_board_info bi;
	काष्ठा i2c_client *tuner;

	cfg->fe = fe;

	स_रखो(&bi, 0, माप(bi));

	strscpy(bi.type, "si2157", I2C_NAME_SIZE);
	bi.platक्रमm_data = cfg;
	bi.addr = addr8bit >> 1;

	request_module(bi.type);

	tuner = i2c_new_client_device(adapter, &bi);
	अगर (!i2c_client_has_driver(tuner))
		वापस -ENODEV;

	अगर (!try_module_get(tuner->dev.driver->owner)) अणु
		i2c_unरेजिस्टर_device(tuner);
		वापस -ENODEV;
	पूर्ण

	port->i2c_client_tuner = tuner;

	वापस 0;
पूर्ण

अटल पूर्णांक saa7164_dvb_stop_port(काष्ठा saa7164_port *port)
अणु
	काष्ठा saa7164_dev *dev = port->dev;
	पूर्णांक ret;

	ret = saa7164_api_transition_port(port, SAA_DMASTATE_STOP);
	अगर ((ret != SAA_OK) && (ret != SAA_ERR_ALREADY_STOPPED)) अणु
		prपूर्णांकk(KERN_ERR "%s() stop transition failed, ret = 0x%x\n",
			__func__, ret);
		ret = -EIO;
	पूर्ण अन्यथा अणु
		dprपूर्णांकk(DBGLVL_DVB, "%s()    Stopped\n", __func__);
		ret = 0;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक saa7164_dvb_acquire_port(काष्ठा saa7164_port *port)
अणु
	काष्ठा saa7164_dev *dev = port->dev;
	पूर्णांक ret;

	ret = saa7164_api_transition_port(port, SAA_DMASTATE_ACQUIRE);
	अगर ((ret != SAA_OK) && (ret != SAA_ERR_ALREADY_STOPPED)) अणु
		prपूर्णांकk(KERN_ERR "%s() acquire transition failed, ret = 0x%x\n",
			__func__, ret);
		ret = -EIO;
	पूर्ण अन्यथा अणु
		dprपूर्णांकk(DBGLVL_DVB, "%s() Acquired\n", __func__);
		ret = 0;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक saa7164_dvb_छोड़ो_port(काष्ठा saa7164_port *port)
अणु
	काष्ठा saa7164_dev *dev = port->dev;
	पूर्णांक ret;

	ret = saa7164_api_transition_port(port, SAA_DMASTATE_PAUSE);
	अगर ((ret != SAA_OK) && (ret != SAA_ERR_ALREADY_STOPPED)) अणु
		prपूर्णांकk(KERN_ERR "%s() pause transition failed, ret = 0x%x\n",
			__func__, ret);
		ret = -EIO;
	पूर्ण अन्यथा अणु
		dprपूर्णांकk(DBGLVL_DVB, "%s()   Paused\n", __func__);
		ret = 0;
	पूर्ण

	वापस ret;
पूर्ण

/* Firmware is very winकरोws centric, meaning you have to transition
 * the part through AVStream / KS Winकरोws stages, क्रमwards or backwards.
 * States are: stopped, acquired (h/w), छोड़ोd, started.
 */
अटल पूर्णांक saa7164_dvb_stop_streaming(काष्ठा saa7164_port *port)
अणु
	काष्ठा saa7164_dev *dev = port->dev;
	काष्ठा saa7164_buffer *buf;
	काष्ठा list_head *p, *q;
	पूर्णांक ret;

	dprपूर्णांकk(DBGLVL_DVB, "%s(port=%d)\n", __func__, port->nr);

	ret = saa7164_dvb_छोड़ो_port(port);
	ret = saa7164_dvb_acquire_port(port);
	ret = saa7164_dvb_stop_port(port);

	/* Mark the hardware buffers as मुक्त */
	mutex_lock(&port->dmaqueue_lock);
	list_क्रम_each_safe(p, q, &port->dmaqueue.list) अणु
		buf = list_entry(p, काष्ठा saa7164_buffer, list);
		buf->flags = SAA7164_BUFFER_FREE;
	पूर्ण
	mutex_unlock(&port->dmaqueue_lock);

	वापस ret;
पूर्ण

अटल पूर्णांक saa7164_dvb_start_port(काष्ठा saa7164_port *port)
अणु
	काष्ठा saa7164_dev *dev = port->dev;
	पूर्णांक ret = 0, result;

	dprपूर्णांकk(DBGLVL_DVB, "%s(port=%d)\n", __func__, port->nr);

	saa7164_buffer_cfg_port(port);

	/* Acquire the hardware */
	result = saa7164_api_transition_port(port, SAA_DMASTATE_ACQUIRE);
	अगर ((result != SAA_OK) && (result != SAA_ERR_ALREADY_STOPPED)) अणु
		prपूर्णांकk(KERN_ERR "%s() acquire transition failed, res = 0x%x\n",
			__func__, result);

		/* Stop the hardware, regardless */
		result = saa7164_api_transition_port(port, SAA_DMASTATE_STOP);
		अगर ((result != SAA_OK) && (result != SAA_ERR_ALREADY_STOPPED)) अणु
			prपूर्णांकk(KERN_ERR "%s() acquire/forced stop transition failed, res = 0x%x\n",
			       __func__, result);
		पूर्ण
		ret = -EIO;
		जाओ out;
	पूर्ण अन्यथा
		dprपूर्णांकk(DBGLVL_DVB, "%s()   Acquired\n", __func__);

	/* Pause the hardware */
	result = saa7164_api_transition_port(port, SAA_DMASTATE_PAUSE);
	अगर ((result != SAA_OK) && (result != SAA_ERR_ALREADY_STOPPED)) अणु
		prपूर्णांकk(KERN_ERR "%s() pause transition failed, res = 0x%x\n",
				__func__, result);

		/* Stop the hardware, regardless */
		result = saa7164_api_transition_port(port, SAA_DMASTATE_STOP);
		अगर ((result != SAA_OK) && (result != SAA_ERR_ALREADY_STOPPED)) अणु
			prपूर्णांकk(KERN_ERR "%s() pause/forced stop transition failed, res = 0x%x\n",
			       __func__, result);
		पूर्ण

		ret = -EIO;
		जाओ out;
	पूर्ण अन्यथा
		dprपूर्णांकk(DBGLVL_DVB, "%s()   Paused\n", __func__);

	/* Start the hardware */
	result = saa7164_api_transition_port(port, SAA_DMASTATE_RUN);
	अगर ((result != SAA_OK) && (result != SAA_ERR_ALREADY_STOPPED)) अणु
		prपूर्णांकk(KERN_ERR "%s() run transition failed, result = 0x%x\n",
				__func__, result);

		/* Stop the hardware, regardless */
		result = saa7164_api_transition_port(port, SAA_DMASTATE_STOP);
		अगर ((result != SAA_OK) && (result != SAA_ERR_ALREADY_STOPPED)) अणु
			prपूर्णांकk(KERN_ERR "%s() run/forced stop transition failed, res = 0x%x\n",
			       __func__, result);
		पूर्ण

		ret = -EIO;
	पूर्ण अन्यथा
		dprपूर्णांकk(DBGLVL_DVB, "%s()   Running\n", __func__);

out:
	वापस ret;
पूर्ण

अटल पूर्णांक saa7164_dvb_start_feed(काष्ठा dvb_demux_feed *feed)
अणु
	काष्ठा dvb_demux *demux = feed->demux;
	काष्ठा saa7164_port *port = (काष्ठा saa7164_port *) demux->priv;
	काष्ठा saa7164_dvb *dvb = &port->dvb;
	काष्ठा saa7164_dev *dev = port->dev;
	पूर्णांक ret = 0;

	dprपूर्णांकk(DBGLVL_DVB, "%s(port=%d)\n", __func__, port->nr);

	अगर (!demux->dmx.frontend)
		वापस -EINVAL;

	अगर (dvb) अणु
		mutex_lock(&dvb->lock);
		अगर (dvb->feeding++ == 0) अणु
			/* Start transport */
			ret = saa7164_dvb_start_port(port);
		पूर्ण
		mutex_unlock(&dvb->lock);
		dprपूर्णांकk(DBGLVL_DVB, "%s(port=%d) now feeding = %d\n",
			__func__, port->nr, dvb->feeding);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक saa7164_dvb_stop_feed(काष्ठा dvb_demux_feed *feed)
अणु
	काष्ठा dvb_demux *demux = feed->demux;
	काष्ठा saa7164_port *port = (काष्ठा saa7164_port *) demux->priv;
	काष्ठा saa7164_dvb *dvb = &port->dvb;
	काष्ठा saa7164_dev *dev = port->dev;
	पूर्णांक ret = 0;

	dprपूर्णांकk(DBGLVL_DVB, "%s(port=%d)\n", __func__, port->nr);

	अगर (dvb) अणु
		mutex_lock(&dvb->lock);
		अगर (--dvb->feeding == 0) अणु
			/* Stop transport */
			ret = saa7164_dvb_stop_streaming(port);
		पूर्ण
		mutex_unlock(&dvb->lock);
		dprपूर्णांकk(DBGLVL_DVB, "%s(port=%d) now feeding = %d\n",
			__func__, port->nr, dvb->feeding);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक dvb_रेजिस्टर(काष्ठा saa7164_port *port)
अणु
	काष्ठा saa7164_dvb *dvb = &port->dvb;
	काष्ठा saa7164_dev *dev = port->dev;
	काष्ठा saa7164_buffer *buf;
	पूर्णांक result, i;

	dprपूर्णांकk(DBGLVL_DVB, "%s(port=%d)\n", __func__, port->nr);

	BUG_ON(port->type != SAA7164_MPEG_DVB);

	/* Sanity check that the PCI configuration space is active */
	अगर (port->hwcfg.BARLocation == 0) अणु
		result = -ENOMEM;
		prपूर्णांकk(KERN_ERR "%s: dvb_register_adapter failed (errno = %d), NO PCI configuration\n",
			DRIVER_NAME, result);
		जाओ fail_adapter;
	पूर्ण

	/* Init and establish शेषs */
	port->hw_streamingparams.bitspersample = 8;
	port->hw_streamingparams.samplesperline = 188;
	port->hw_streamingparams.numberoflines =
		(SAA7164_TS_NUMBER_OF_LINES * 188) / 188;

	port->hw_streamingparams.pitch = 188;
	port->hw_streamingparams.linethreshold = 0;
	port->hw_streamingparams.pagetablelistvirt = शून्य;
	port->hw_streamingparams.pagetablelistphys = शून्य;
	port->hw_streamingparams.numpagetables = 2 +
		((SAA7164_TS_NUMBER_OF_LINES * 188) / PAGE_SIZE);

	port->hw_streamingparams.numpagetableentries = port->hwcfg.buffercount;

	/* Allocate the PCI resources */
	क्रम (i = 0; i < port->hwcfg.buffercount; i++) अणु
		buf = saa7164_buffer_alloc(port,
			port->hw_streamingparams.numberoflines *
			port->hw_streamingparams.pitch);

		अगर (!buf) अणु
			result = -ENOMEM;
			prपूर्णांकk(KERN_ERR "%s: dvb_register_adapter failed (errno = %d), unable to allocate buffers\n",
				DRIVER_NAME, result);
			जाओ fail_adapter;
		पूर्ण

		mutex_lock(&port->dmaqueue_lock);
		list_add_tail(&buf->list, &port->dmaqueue.list);
		mutex_unlock(&port->dmaqueue_lock);
	पूर्ण

	/* रेजिस्टर adapter */
	result = dvb_रेजिस्टर_adapter(&dvb->adapter, DRIVER_NAME, THIS_MODULE,
			&dev->pci->dev, adapter_nr);
	अगर (result < 0) अणु
		prपूर्णांकk(KERN_ERR "%s: dvb_register_adapter failed (errno = %d)\n",
		       DRIVER_NAME, result);
		जाओ fail_adapter;
	पूर्ण
	dvb->adapter.priv = port;

	/* रेजिस्टर frontend */
	result = dvb_रेजिस्टर_frontend(&dvb->adapter, dvb->frontend);
	अगर (result < 0) अणु
		prपूर्णांकk(KERN_ERR "%s: dvb_register_frontend failed (errno = %d)\n",
		       DRIVER_NAME, result);
		जाओ fail_frontend;
	पूर्ण

	/* रेजिस्टर demux stuff */
	dvb->demux.dmx.capabilities =
		DMX_TS_FILTERING | DMX_SECTION_FILTERING |
		DMX_MEMORY_BASED_FILTERING;
	dvb->demux.priv       = port;
	dvb->demux.filternum  = 256;
	dvb->demux.feednum    = 256;
	dvb->demux.start_feed = saa7164_dvb_start_feed;
	dvb->demux.stop_feed  = saa7164_dvb_stop_feed;
	result = dvb_dmx_init(&dvb->demux);
	अगर (result < 0) अणु
		prपूर्णांकk(KERN_ERR "%s: dvb_dmx_init failed (errno = %d)\n",
		       DRIVER_NAME, result);
		जाओ fail_dmx;
	पूर्ण

	dvb->dmxdev.filternum    = 256;
	dvb->dmxdev.demux        = &dvb->demux.dmx;
	dvb->dmxdev.capabilities = 0;
	result = dvb_dmxdev_init(&dvb->dmxdev, &dvb->adapter);
	अगर (result < 0) अणु
		prपूर्णांकk(KERN_ERR "%s: dvb_dmxdev_init failed (errno = %d)\n",
		       DRIVER_NAME, result);
		जाओ fail_dmxdev;
	पूर्ण

	dvb->fe_hw.source = DMX_FRONTEND_0;
	result = dvb->demux.dmx.add_frontend(&dvb->demux.dmx, &dvb->fe_hw);
	अगर (result < 0) अणु
		prपूर्णांकk(KERN_ERR "%s: add_frontend failed (DMX_FRONTEND_0, errno = %d)\n",
		       DRIVER_NAME, result);
		जाओ fail_fe_hw;
	पूर्ण

	dvb->fe_mem.source = DMX_MEMORY_FE;
	result = dvb->demux.dmx.add_frontend(&dvb->demux.dmx, &dvb->fe_mem);
	अगर (result < 0) अणु
		prपूर्णांकk(KERN_ERR "%s: add_frontend failed (DMX_MEMORY_FE, errno = %d)\n",
		       DRIVER_NAME, result);
		जाओ fail_fe_mem;
	पूर्ण

	result = dvb->demux.dmx.connect_frontend(&dvb->demux.dmx, &dvb->fe_hw);
	अगर (result < 0) अणु
		prपूर्णांकk(KERN_ERR "%s: connect_frontend failed (errno = %d)\n",
		       DRIVER_NAME, result);
		जाओ fail_fe_conn;
	पूर्ण

	/* रेजिस्टर network adapter */
	dvb_net_init(&dvb->adapter, &dvb->net, &dvb->demux.dmx);
	वापस 0;

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
	वापस result;
पूर्ण

पूर्णांक saa7164_dvb_unरेजिस्टर(काष्ठा saa7164_port *port)
अणु
	काष्ठा saa7164_dvb *dvb = &port->dvb;
	काष्ठा saa7164_dev *dev = port->dev;
	काष्ठा saa7164_buffer *b;
	काष्ठा list_head *c, *n;
	काष्ठा i2c_client *client;

	dprपूर्णांकk(DBGLVL_DVB, "%s()\n", __func__);

	BUG_ON(port->type != SAA7164_MPEG_DVB);

	/* Remove any allocated buffers */
	mutex_lock(&port->dmaqueue_lock);
	list_क्रम_each_safe(c, n, &port->dmaqueue.list) अणु
		b = list_entry(c, काष्ठा saa7164_buffer, list);
		list_del(c);
		saa7164_buffer_dealloc(b);
	पूर्ण
	mutex_unlock(&port->dmaqueue_lock);

	अगर (dvb->frontend == शून्य)
		वापस 0;

	/* हटाओ I2C client क्रम tuner */
	client = port->i2c_client_tuner;
	अगर (client) अणु
		module_put(client->dev.driver->owner);
		i2c_unरेजिस्टर_device(client);
	पूर्ण

	/* हटाओ I2C client क्रम demodulator */
	client = port->i2c_client_demod;
	अगर (client) अणु
		module_put(client->dev.driver->owner);
		i2c_unरेजिस्टर_device(client);
	पूर्ण

	dvb_net_release(&dvb->net);
	dvb->demux.dmx.हटाओ_frontend(&dvb->demux.dmx, &dvb->fe_mem);
	dvb->demux.dmx.हटाओ_frontend(&dvb->demux.dmx, &dvb->fe_hw);
	dvb_dmxdev_release(&dvb->dmxdev);
	dvb_dmx_release(&dvb->demux);
	dvb_unरेजिस्टर_frontend(dvb->frontend);
	dvb_frontend_detach(dvb->frontend);
	dvb_unरेजिस्टर_adapter(&dvb->adapter);
	वापस 0;
पूर्ण

/* All the DVB attach calls go here, this function माला_लो modअगरied
 * क्रम each new card.
 */
पूर्णांक saa7164_dvb_रेजिस्टर(काष्ठा saa7164_port *port)
अणु
	काष्ठा saa7164_dev *dev = port->dev;
	काष्ठा saa7164_dvb *dvb = &port->dvb;
	काष्ठा saa7164_i2c *i2c_bus = शून्य;
	काष्ठा si2168_config si2168_config;
	काष्ठा si2157_config si2157_config;
	काष्ठा i2c_adapter *adapter;
	काष्ठा i2c_board_info info;
	काष्ठा i2c_client *client_demod;
	काष्ठा i2c_client *client_tuner;
	पूर्णांक ret;

	dprपूर्णांकk(DBGLVL_DVB, "%s()\n", __func__);

	/* init frontend */
	चयन (dev->board) अणु
	हाल SAA7164_BOARD_HAUPPAUGE_HVR2200:
	हाल SAA7164_BOARD_HAUPPAUGE_HVR2200_2:
	हाल SAA7164_BOARD_HAUPPAUGE_HVR2200_3:
	हाल SAA7164_BOARD_HAUPPAUGE_HVR2200_4:
	हाल SAA7164_BOARD_HAUPPAUGE_HVR2200_5:
		i2c_bus = &dev->i2c_bus[port->nr + 1];
		चयन (port->nr) अणु
		हाल 0:
			port->dvb.frontend = dvb_attach(tda10048_attach,
				&hauppauge_hvr2200_1_config,
				&i2c_bus->i2c_adap);

			अगर (port->dvb.frontend != शून्य) अणु
				/* TODO: addr is in the card काष्ठा */
				dvb_attach(tda18271_attach, port->dvb.frontend,
					0xc0 >> 1, &i2c_bus->i2c_adap,
					&hauppauge_hvr22x0_tuner_config);
			पूर्ण

			अवरोध;
		हाल 1:
			port->dvb.frontend = dvb_attach(tda10048_attach,
				&hauppauge_hvr2200_2_config,
				&i2c_bus->i2c_adap);

			अगर (port->dvb.frontend != शून्य) अणु
				/* TODO: addr is in the card काष्ठा */
				dvb_attach(tda18271_attach, port->dvb.frontend,
					0xc0 >> 1, &i2c_bus->i2c_adap,
					&hauppauge_hvr22x0s_tuner_config);
			पूर्ण

			अवरोध;
		पूर्ण
		अवरोध;
	हाल SAA7164_BOARD_HAUPPAUGE_HVR2250:
	हाल SAA7164_BOARD_HAUPPAUGE_HVR2250_2:
	हाल SAA7164_BOARD_HAUPPAUGE_HVR2250_3:
		i2c_bus = &dev->i2c_bus[port->nr + 1];

		port->dvb.frontend = dvb_attach(s5h1411_attach,
			&hauppauge_s5h1411_config,
			&i2c_bus->i2c_adap);

		अगर (port->dvb.frontend != शून्य) अणु
			अगर (port->nr == 0) अणु
				/* Master TDA18271 */
				/* TODO: addr is in the card काष्ठा */
				dvb_attach(tda18271_attach, port->dvb.frontend,
					0xc0 >> 1, &i2c_bus->i2c_adap,
					&hauppauge_hvr22x0_tuner_config);
			पूर्ण अन्यथा अणु
				/* Slave TDA18271 */
				dvb_attach(tda18271_attach, port->dvb.frontend,
					0xc0 >> 1, &i2c_bus->i2c_adap,
					&hauppauge_hvr22x0s_tuner_config);
			पूर्ण
		पूर्ण

		अवरोध;
	हाल SAA7164_BOARD_HAUPPAUGE_HVR2255proto:
	हाल SAA7164_BOARD_HAUPPAUGE_HVR2255:
		i2c_bus = &dev->i2c_bus[2];

		अगर (port->nr == 0) अणु
			port->dvb.frontend = dvb_attach(lgdt3306a_attach,
				&hauppauge_hvr2255a_config, &i2c_bus->i2c_adap);
		पूर्ण अन्यथा अणु
			port->dvb.frontend = dvb_attach(lgdt3306a_attach,
				&hauppauge_hvr2255b_config, &i2c_bus->i2c_adap);
		पूर्ण

		अगर (port->dvb.frontend != शून्य) अणु

			अगर (port->nr == 0) अणु
				si2157_attach(port, &dev->i2c_bus[0].i2c_adap,
					      port->dvb.frontend, 0xc0,
					      &hauppauge_hvr2255_tuner_config);
			पूर्ण अन्यथा अणु
				si2157_attach(port, &dev->i2c_bus[1].i2c_adap,
					      port->dvb.frontend, 0xc0,
					      &hauppauge_hvr2255_tuner_config);
			पूर्ण
		पूर्ण
		अवरोध;
	हाल SAA7164_BOARD_HAUPPAUGE_HVR2205:

		अगर (port->nr == 0) अणु
			/* attach frontend */
			स_रखो(&si2168_config, 0, माप(si2168_config));
			si2168_config.i2c_adapter = &adapter;
			si2168_config.fe = &port->dvb.frontend;
			si2168_config.ts_mode = SI2168_TS_SERIAL;
			स_रखो(&info, 0, माप(काष्ठा i2c_board_info));
			strscpy(info.type, "si2168", I2C_NAME_SIZE);
			info.addr = 0xc8 >> 1;
			info.platक्रमm_data = &si2168_config;
			request_module(info.type);
			client_demod = i2c_new_client_device(&dev->i2c_bus[2].i2c_adap, &info);
			अगर (!i2c_client_has_driver(client_demod))
				जाओ frontend_detach;

			अगर (!try_module_get(client_demod->dev.driver->owner)) अणु
				i2c_unरेजिस्टर_device(client_demod);
				जाओ frontend_detach;
			पूर्ण
			port->i2c_client_demod = client_demod;

			/* attach tuner */
			स_रखो(&si2157_config, 0, माप(si2157_config));
			si2157_config.अगर_port = 1;
			si2157_config.fe = port->dvb.frontend;
			स_रखो(&info, 0, माप(काष्ठा i2c_board_info));
			strscpy(info.type, "si2157", I2C_NAME_SIZE);
			info.addr = 0xc0 >> 1;
			info.platक्रमm_data = &si2157_config;
			request_module(info.type);
			client_tuner = i2c_new_client_device(&dev->i2c_bus[0].i2c_adap, &info);
			अगर (!i2c_client_has_driver(client_tuner)) अणु
				module_put(client_demod->dev.driver->owner);
				i2c_unरेजिस्टर_device(client_demod);
				जाओ frontend_detach;
			पूर्ण
			अगर (!try_module_get(client_tuner->dev.driver->owner)) अणु
				i2c_unरेजिस्टर_device(client_tuner);
				module_put(client_demod->dev.driver->owner);
				i2c_unरेजिस्टर_device(client_demod);
				जाओ frontend_detach;
			पूर्ण
			port->i2c_client_tuner = client_tuner;
		पूर्ण अन्यथा अणु
			/* attach frontend */
			स_रखो(&si2168_config, 0, माप(si2168_config));
			si2168_config.i2c_adapter = &adapter;
			si2168_config.fe = &port->dvb.frontend;
			si2168_config.ts_mode = SI2168_TS_SERIAL;
			स_रखो(&info, 0, माप(काष्ठा i2c_board_info));
			strscpy(info.type, "si2168", I2C_NAME_SIZE);
			info.addr = 0xcc >> 1;
			info.platक्रमm_data = &si2168_config;
			request_module(info.type);
			client_demod = i2c_new_client_device(&dev->i2c_bus[2].i2c_adap, &info);
			अगर (!i2c_client_has_driver(client_demod))
				जाओ frontend_detach;

			अगर (!try_module_get(client_demod->dev.driver->owner)) अणु
				i2c_unरेजिस्टर_device(client_demod);
				जाओ frontend_detach;
			पूर्ण
			port->i2c_client_demod = client_demod;

			/* attach tuner */
			स_रखो(&si2157_config, 0, माप(si2157_config));
			si2157_config.fe = port->dvb.frontend;
			si2157_config.अगर_port = 1;
			स_रखो(&info, 0, माप(काष्ठा i2c_board_info));
			strscpy(info.type, "si2157", I2C_NAME_SIZE);
			info.addr = 0xc0 >> 1;
			info.platक्रमm_data = &si2157_config;
			request_module(info.type);
			client_tuner = i2c_new_client_device(&dev->i2c_bus[1].i2c_adap, &info);
			अगर (!i2c_client_has_driver(client_tuner)) अणु
				module_put(client_demod->dev.driver->owner);
				i2c_unरेजिस्टर_device(client_demod);
				जाओ frontend_detach;
			पूर्ण
			अगर (!try_module_get(client_tuner->dev.driver->owner)) अणु
				i2c_unरेजिस्टर_device(client_tuner);
				module_put(client_demod->dev.driver->owner);
				i2c_unरेजिस्टर_device(client_demod);
				जाओ frontend_detach;
			पूर्ण
			port->i2c_client_tuner = client_tuner;
		पूर्ण

		अवरोध;
	शेष:
		prपूर्णांकk(KERN_ERR "%s: The frontend isn't supported\n",
		       dev->name);
		अवरोध;
	पूर्ण
	अगर (शून्य == dvb->frontend) अणु
		prपूर्णांकk(KERN_ERR "%s() Frontend initialization failed\n",
		       __func__);
		वापस -1;
	पूर्ण

	/* रेजिस्टर everything */
	ret = dvb_रेजिस्टर(port);
	अगर (ret < 0) अणु
		अगर (dvb->frontend->ops.release)
			dvb->frontend->ops.release(dvb->frontend);
		वापस ret;
	पूर्ण

	वापस 0;

frontend_detach:
	prपूर्णांकk(KERN_ERR "%s() Frontend/I2C initialization failed\n", __func__);
	वापस -1;
पूर्ण
