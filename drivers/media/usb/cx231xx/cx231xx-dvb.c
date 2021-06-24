<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 DVB device driver क्रम cx231xx

 Copyright (C) 2008 <srinivasa.deevi at conexant करोt com>
		Based on em28xx driver

 */

#समावेश "cx231xx.h"
#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>

#समावेश <media/dvbdev.h>
#समावेश <media/dmxdev.h>
#समावेश <media/dvb_demux.h>
#समावेश <media/dvb_net.h>
#समावेश <media/dvb_frontend.h>
#समावेश <media/v4l2-common.h>
#समावेश <media/tuner.h>

#समावेश "xc5000.h"
#समावेश "s5h1432.h"
#समावेश "tda18271.h"
#समावेश "s5h1411.h"
#समावेश "lgdt3305.h"
#समावेश "si2165.h"
#समावेश "si2168.h"
#समावेश "mb86a20s.h"
#समावेश "si2157.h"
#समावेश "lgdt3306a.h"
#समावेश "r820t.h"
#समावेश "mn88473.h"

MODULE_DESCRIPTION("driver for cx231xx based DVB cards");
MODULE_AUTHOR("Srinivasa Deevi <srinivasa.deevi@conexant.com>");
MODULE_LICENSE("GPL");

अटल अचिन्हित पूर्णांक debug;
module_param(debug, पूर्णांक, 0644);
MODULE_PARM_DESC(debug, "enable debug messages [dvb]");

DVB_DEFINE_MOD_OPT_ADAPTER_NR(adapter_nr);

#घोषणा CX231XX_DVB_NUM_BUFS 5
#घोषणा CX231XX_DVB_MAX_PACKETSIZE 564
#घोषणा CX231XX_DVB_MAX_PACKETS 64
#घोषणा CX231XX_DVB_MAX_FRONTENDS 2

काष्ठा cx231xx_dvb अणु
	काष्ठा dvb_frontend *frontend[CX231XX_DVB_MAX_FRONTENDS];

	/* feed count management */
	काष्ठा mutex lock;
	पूर्णांक nfeeds;

	/* general boilerplate stuff */
	काष्ठा dvb_adapter adapter;
	काष्ठा dvb_demux demux;
	काष्ठा dmxdev dmxdev;
	काष्ठा dmx_frontend fe_hw;
	काष्ठा dmx_frontend fe_mem;
	काष्ठा dvb_net net;
	काष्ठा i2c_client *i2c_client_demod[2];
	काष्ठा i2c_client *i2c_client_tuner;
पूर्ण;

अटल काष्ठा s5h1432_config dvico_s5h1432_config = अणु
	.output_mode   = S5H1432_SERIAL_OUTPUT,
	.gpio          = S5H1432_GPIO_ON,
	.qam_अगर        = S5H1432_IF_4000,
	.vsb_अगर        = S5H1432_IF_4000,
	.inversion     = S5H1432_INVERSION_OFF,
	.status_mode   = S5H1432_DEMODLOCKING,
	.mpeg_timing   = S5H1432_MPEGTIMING_CONTINUOUS_NONINVERTING_CLOCK,
पूर्ण;

अटल काष्ठा tda18271_std_map cnxt_rde253s_tda18271_std_map = अणु
	.dvbt_6   = अणु .अगर_freq = 4000, .agc_mode = 3, .std = 4,
		      .अगर_lvl = 1, .rfagc_top = 0x37, पूर्ण,
	.dvbt_7   = अणु .अगर_freq = 4000, .agc_mode = 3, .std = 5,
		      .अगर_lvl = 1, .rfagc_top = 0x37, पूर्ण,
	.dvbt_8   = अणु .अगर_freq = 4000, .agc_mode = 3, .std = 6,
		      .अगर_lvl = 1, .rfagc_top = 0x37, पूर्ण,
पूर्ण;

अटल काष्ठा tda18271_std_map mb86a20s_tda18271_config = अणु
	.dvbt_6   = अणु .अगर_freq = 4000, .agc_mode = 3, .std = 4,
		      .अगर_lvl = 0, .rfagc_top = 0x37, पूर्ण,
पूर्ण;

अटल काष्ठा tda18271_config cnxt_rde253s_tunerconfig = अणु
	.std_map = &cnxt_rde253s_tda18271_std_map,
	.gate    = TDA18271_GATE_ANALOG,
पूर्ण;

अटल काष्ठा s5h1411_config tda18271_s5h1411_config = अणु
	.output_mode   = S5H1411_SERIAL_OUTPUT,
	.gpio          = S5H1411_GPIO_OFF,
	.vsb_अगर        = S5H1411_IF_3250,
	.qam_अगर        = S5H1411_IF_4000,
	.inversion     = S5H1411_INVERSION_ON,
	.status_mode   = S5H1411_DEMODLOCKING,
	.mpeg_timing   = S5H1411_MPEGTIMING_CONTINUOUS_NONINVERTING_CLOCK,
पूर्ण;
अटल काष्ठा s5h1411_config xc5000_s5h1411_config = अणु
	.output_mode   = S5H1411_SERIAL_OUTPUT,
	.gpio          = S5H1411_GPIO_OFF,
	.vsb_अगर        = S5H1411_IF_3250,
	.qam_अगर        = S5H1411_IF_3250,
	.inversion     = S5H1411_INVERSION_OFF,
	.status_mode   = S5H1411_DEMODLOCKING,
	.mpeg_timing   = S5H1411_MPEGTIMING_CONTINUOUS_NONINVERTING_CLOCK,
पूर्ण;

अटल काष्ठा lgdt3305_config hcw_lgdt3305_config = अणु
	.i2c_addr           = 0x0e,
	.mpeg_mode          = LGDT3305_MPEG_SERIAL,
	.tpclk_edge         = LGDT3305_TPCLK_FALLING_EDGE,
	.tpvalid_polarity   = LGDT3305_TP_VALID_HIGH,
	.deny_i2c_rptr      = 1,
	.spectral_inversion = 1,
	.qam_अगर_khz         = 4000,
	.vsb_अगर_khz         = 3250,
पूर्ण;

अटल काष्ठा tda18271_std_map hauppauge_tda18271_std_map = अणु
	.atsc_6   = अणु .अगर_freq = 3250, .agc_mode = 3, .std = 4,
		      .अगर_lvl = 1, .rfagc_top = 0x58, पूर्ण,
	.qam_6    = अणु .अगर_freq = 4000, .agc_mode = 3, .std = 5,
		      .अगर_lvl = 1, .rfagc_top = 0x58, पूर्ण,
पूर्ण;

अटल काष्ठा tda18271_config hcw_tda18271_config = अणु
	.std_map = &hauppauge_tda18271_std_map,
	.gate    = TDA18271_GATE_DIGITAL,
पूर्ण;

अटल स्थिर काष्ठा mb86a20s_config pv_mb86a20s_config = अणु
	.demod_address = 0x10,
	.is_serial = true,
पूर्ण;

अटल काष्ठा tda18271_config pv_tda18271_config = अणु
	.std_map = &mb86a20s_tda18271_config,
	.gate    = TDA18271_GATE_DIGITAL,
	.small_i2c = TDA18271_03_BYTE_CHUNK_INIT,
पूर्ण;

अटल स्थिर काष्ठा lgdt3306a_config hauppauge_955q_lgdt3306a_config = अणु
	.qam_अगर_khz         = 4000,
	.vsb_अगर_khz         = 3250,
	.spectral_inversion = 1,
	.mpeg_mode          = LGDT3306A_MPEG_SERIAL,
	.tpclk_edge         = LGDT3306A_TPCLK_RISING_EDGE,
	.tpvalid_polarity   = LGDT3306A_TP_VALID_HIGH,
	.xtalMHz            = 25,
पूर्ण;

अटल काष्ठा r820t_config astrometa_t2hybrid_r820t_config = अणु
	.i2c_addr		= 0x3a, /* 0x74 >> 1 */
	.xtal			= 16000000,
	.rafael_chip		= CHIP_R828D,
	.max_i2c_msg_len	= 2,
पूर्ण;

अटल अंतरभूत व्योम prपूर्णांक_err_status(काष्ठा cx231xx *dev, पूर्णांक packet, पूर्णांक status)
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
		dev_dbg(dev->dev,
			"URB status %d [%s].\n", status, errmsg);
	पूर्ण अन्यथा अणु
		dev_dbg(dev->dev,
			"URB packet %d, status %d [%s].\n",
			packet, status, errmsg);
	पूर्ण
पूर्ण

अटल अंतरभूत पूर्णांक dvb_isoc_copy(काष्ठा cx231xx *dev, काष्ठा urb *urb)
अणु
	पूर्णांक i;

	अगर (!dev)
		वापस 0;

	अगर (dev->state & DEV_DISCONNECTED)
		वापस 0;

	अगर (urb->status < 0) अणु
		prपूर्णांक_err_status(dev, -1, urb->status);
		अगर (urb->status == -ENOENT)
			वापस 0;
	पूर्ण

	क्रम (i = 0; i < urb->number_of_packets; i++) अणु
		पूर्णांक status = urb->iso_frame_desc[i].status;

		अगर (status < 0) अणु
			prपूर्णांक_err_status(dev, i, status);
			अगर (urb->iso_frame_desc[i].status != -EPROTO)
				जारी;
		पूर्ण

		dvb_dmx_swfilter(&dev->dvb->demux,
				 urb->transfer_buffer +
				urb->iso_frame_desc[i].offset,
				urb->iso_frame_desc[i].actual_length);
	पूर्ण

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक dvb_bulk_copy(काष्ठा cx231xx *dev, काष्ठा urb *urb)
अणु
	अगर (!dev)
		वापस 0;

	अगर (dev->state & DEV_DISCONNECTED)
		वापस 0;

	अगर (urb->status < 0) अणु
		prपूर्णांक_err_status(dev, -1, urb->status);
		अगर (urb->status == -ENOENT)
			वापस 0;
	पूर्ण

	/* Feed the transport payload पूर्णांकo the kernel demux */
	dvb_dmx_swfilter(&dev->dvb->demux,
		urb->transfer_buffer, urb->actual_length);

	वापस 0;
पूर्ण

अटल पूर्णांक start_streaming(काष्ठा cx231xx_dvb *dvb)
अणु
	पूर्णांक rc;
	काष्ठा cx231xx *dev = dvb->adapter.priv;

	अगर (dev->USE_ISO) अणु
		dev_dbg(dev->dev, "DVB transfer mode is ISO.\n");
		cx231xx_set_alt_setting(dev, INDEX_TS1, 5);
		rc = cx231xx_set_mode(dev, CX231XX_DIGITAL_MODE);
		अगर (rc < 0)
			वापस rc;
		dev->mode_tv = 1;
		वापस cx231xx_init_isoc(dev, CX231XX_DVB_MAX_PACKETS,
					CX231XX_DVB_NUM_BUFS,
					dev->ts1_mode.max_pkt_size,
					dvb_isoc_copy);
	पूर्ण अन्यथा अणु
		dev_dbg(dev->dev, "DVB transfer mode is BULK.\n");
		cx231xx_set_alt_setting(dev, INDEX_TS1, 0);
		rc = cx231xx_set_mode(dev, CX231XX_DIGITAL_MODE);
		अगर (rc < 0)
			वापस rc;
		dev->mode_tv = 1;
		वापस cx231xx_init_bulk(dev, CX231XX_DVB_MAX_PACKETS,
					CX231XX_DVB_NUM_BUFS,
					dev->ts1_mode.max_pkt_size,
					dvb_bulk_copy);
	पूर्ण

पूर्ण

अटल पूर्णांक stop_streaming(काष्ठा cx231xx_dvb *dvb)
अणु
	काष्ठा cx231xx *dev = dvb->adapter.priv;

	अगर (dev->USE_ISO)
		cx231xx_uninit_isoc(dev);
	अन्यथा
		cx231xx_uninit_bulk(dev);

	cx231xx_set_mode(dev, CX231XX_SUSPEND);

	वापस 0;
पूर्ण

अटल पूर्णांक start_feed(काष्ठा dvb_demux_feed *feed)
अणु
	काष्ठा dvb_demux *demux = feed->demux;
	काष्ठा cx231xx_dvb *dvb = demux->priv;
	पूर्णांक rc, ret;

	अगर (!demux->dmx.frontend)
		वापस -EINVAL;

	mutex_lock(&dvb->lock);
	dvb->nfeeds++;
	rc = dvb->nfeeds;

	अगर (dvb->nfeeds == 1) अणु
		ret = start_streaming(dvb);
		अगर (ret < 0)
			rc = ret;
	पूर्ण

	mutex_unlock(&dvb->lock);
	वापस rc;
पूर्ण

अटल पूर्णांक stop_feed(काष्ठा dvb_demux_feed *feed)
अणु
	काष्ठा dvb_demux *demux = feed->demux;
	काष्ठा cx231xx_dvb *dvb = demux->priv;
	पूर्णांक err = 0;

	mutex_lock(&dvb->lock);
	dvb->nfeeds--;

	अगर (0 == dvb->nfeeds)
		err = stop_streaming(dvb);

	mutex_unlock(&dvb->lock);
	वापस err;
पूर्ण

/* ------------------------------------------------------------------ */
अटल पूर्णांक cx231xx_dvb_bus_ctrl(काष्ठा dvb_frontend *fe, पूर्णांक acquire)
अणु
	काष्ठा cx231xx *dev = fe->dvb->priv;

	अगर (acquire)
		वापस cx231xx_set_mode(dev, CX231XX_DIGITAL_MODE);
	अन्यथा
		वापस cx231xx_set_mode(dev, CX231XX_SUSPEND);
पूर्ण

/* ------------------------------------------------------------------ */

अटल काष्ठा xc5000_config cnxt_rde250_tunerconfig = अणु
	.i2c_address = 0x61,
	.अगर_khz = 4000,
पूर्ण;
अटल काष्ठा xc5000_config cnxt_rdu250_tunerconfig = अणु
	.i2c_address = 0x61,
	.अगर_khz = 3250,
पूर्ण;

/* ------------------------------------------------------------------ */
#अगर 0
अटल पूर्णांक attach_xc5000(u8 addr, काष्ठा cx231xx *dev)
अणु

	काष्ठा dvb_frontend *fe;
	काष्ठा xc5000_config cfg;

	स_रखो(&cfg, 0, माप(cfg));
	cfg.i2c_adap = cx231xx_get_i2c_adap(dev, dev->board.tuner_i2c_master);
	cfg.i2c_addr = addr;

	अगर (!dev->dvb->frontend[0]) अणु
		dev_err(dev->dev, "%s/2: dvb frontend not attached. Can't attach xc5000\n",
			dev->name);
		वापस -EINVAL;
	पूर्ण

	fe = dvb_attach(xc5000_attach, dev->dvb->frontend[0], &cfg);
	अगर (!fe) अणु
		dev_err(dev->dev, "%s/2: xc5000 attach failed\n", dev->name);
		dvb_frontend_detach(dev->dvb->frontend[0]);
		dev->dvb->frontend[0] = शून्य;
		वापस -EINVAL;
	पूर्ण

	dev_info(dev->dev, "%s/2: xc5000 attached\n", dev->name);

	वापस 0;
पूर्ण
#पूर्ण_अगर

पूर्णांक cx231xx_set_analog_freq(काष्ठा cx231xx *dev, u32 freq)
अणु
	अगर (dev->dvb && dev->dvb->frontend[0]) अणु

		काष्ठा dvb_tuner_ops *करोps = &dev->dvb->frontend[0]->ops.tuner_ops;

		अगर (करोps->set_analog_params != शून्य) अणु
			काष्ठा analog_parameters params;

			params.frequency = freq;
			params.std = dev->norm;
			params.mode = 0;	/* 0- Air; 1 - cable */
			/*params.audmode = ;       */

			/* Set the analog parameters to set the frequency */
			करोps->set_analog_params(dev->dvb->frontend[0], &params);
		पूर्ण

	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक cx231xx_reset_analog_tuner(काष्ठा cx231xx *dev)
अणु
	पूर्णांक status = 0;

	अगर (dev->dvb && dev->dvb->frontend[0]) अणु

		काष्ठा dvb_tuner_ops *करोps = &dev->dvb->frontend[0]->ops.tuner_ops;

		अगर (करोps->init != शून्य && !dev->xc_fw_load_करोne) अणु

			dev_dbg(dev->dev,
				"Reloading firmware for XC5000\n");
			status = करोps->init(dev->dvb->frontend[0]);
			अगर (status == 0) अणु
				dev->xc_fw_load_करोne = 1;
				dev_dbg(dev->dev,
					"XC5000 firmware download completed\n");
			पूर्ण अन्यथा अणु
				dev->xc_fw_load_करोne = 0;
				dev_dbg(dev->dev,
					"XC5000 firmware download failed !!!\n");
			पूर्ण
		पूर्ण

	पूर्ण

	वापस status;
पूर्ण

/* ------------------------------------------------------------------ */

अटल पूर्णांक रेजिस्टर_dvb(काष्ठा cx231xx_dvb *dvb,
			काष्ठा module *module,
			काष्ठा cx231xx *dev, काष्ठा device *device)
अणु
	पूर्णांक result;

	mutex_init(&dvb->lock);


	/* रेजिस्टर adapter */
	result = dvb_रेजिस्टर_adapter(&dvb->adapter, dev->name, module, device,
				      adapter_nr);
	अगर (result < 0) अणु
		dev_warn(dev->dev,
		       "%s: dvb_register_adapter failed (errno = %d)\n",
		       dev->name, result);
		जाओ fail_adapter;
	पूर्ण
	dvb_रेजिस्टर_media_controller(&dvb->adapter, dev->media_dev);

	/* Ensure all frontends negotiate bus access */
	dvb->frontend[0]->ops.ts_bus_ctrl = cx231xx_dvb_bus_ctrl;
	अगर (dvb->frontend[1])
		dvb->frontend[1]->ops.ts_bus_ctrl = cx231xx_dvb_bus_ctrl;

	dvb->adapter.priv = dev;

	/* रेजिस्टर frontend */
	result = dvb_रेजिस्टर_frontend(&dvb->adapter, dvb->frontend[0]);
	अगर (result < 0) अणु
		dev_warn(dev->dev,
		       "%s: dvb_register_frontend failed (errno = %d)\n",
		       dev->name, result);
		जाओ fail_frontend0;
	पूर्ण

	अगर (dvb->frontend[1]) अणु
		result = dvb_रेजिस्टर_frontend(&dvb->adapter, dvb->frontend[1]);
		अगर (result < 0) अणु
			dev_warn(dev->dev,
				 "%s: 2nd dvb_register_frontend failed (errno = %d)\n",
				dev->name, result);
			जाओ fail_frontend1;
		पूर्ण

		/* MFE lock */
		dvb->adapter.mfe_shared = 1;
	पूर्ण

	/* रेजिस्टर demux stuff */
	dvb->demux.dmx.capabilities =
	    DMX_TS_FILTERING | DMX_SECTION_FILTERING |
	    DMX_MEMORY_BASED_FILTERING;
	dvb->demux.priv = dvb;
	dvb->demux.filternum = 256;
	dvb->demux.feednum = 256;
	dvb->demux.start_feed = start_feed;
	dvb->demux.stop_feed = stop_feed;

	result = dvb_dmx_init(&dvb->demux);
	अगर (result < 0) अणु
		dev_warn(dev->dev,
			 "%s: dvb_dmx_init failed (errno = %d)\n",
		       dev->name, result);
		जाओ fail_dmx;
	पूर्ण

	dvb->dmxdev.filternum = 256;
	dvb->dmxdev.demux = &dvb->demux.dmx;
	dvb->dmxdev.capabilities = 0;
	result = dvb_dmxdev_init(&dvb->dmxdev, &dvb->adapter);
	अगर (result < 0) अणु
		dev_warn(dev->dev,
			 "%s: dvb_dmxdev_init failed (errno = %d)\n",
			 dev->name, result);
		जाओ fail_dmxdev;
	पूर्ण

	dvb->fe_hw.source = DMX_FRONTEND_0;
	result = dvb->demux.dmx.add_frontend(&dvb->demux.dmx, &dvb->fe_hw);
	अगर (result < 0) अणु
		dev_warn(dev->dev,
		       "%s: add_frontend failed (DMX_FRONTEND_0, errno = %d)\n",
		       dev->name, result);
		जाओ fail_fe_hw;
	पूर्ण

	dvb->fe_mem.source = DMX_MEMORY_FE;
	result = dvb->demux.dmx.add_frontend(&dvb->demux.dmx, &dvb->fe_mem);
	अगर (result < 0) अणु
		dev_warn(dev->dev,
			 "%s: add_frontend failed (DMX_MEMORY_FE, errno = %d)\n",
			 dev->name, result);
		जाओ fail_fe_mem;
	पूर्ण

	result = dvb->demux.dmx.connect_frontend(&dvb->demux.dmx, &dvb->fe_hw);
	अगर (result < 0) अणु
		dev_warn(dev->dev,
			 "%s: connect_frontend failed (errno = %d)\n",
			 dev->name, result);
		जाओ fail_fe_conn;
	पूर्ण

	/* रेजिस्टर network adapter */
	dvb_net_init(&dvb->adapter, &dvb->net, &dvb->demux.dmx);
	result = dvb_create_media_graph(&dvb->adapter,
					dev->tuner_type == TUNER_ABSENT);
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
	अगर (dvb->frontend[1])
		dvb_unरेजिस्टर_frontend(dvb->frontend[1]);
	dvb_unरेजिस्टर_frontend(dvb->frontend[0]);
fail_frontend1:
	अगर (dvb->frontend[1])
		dvb_frontend_detach(dvb->frontend[1]);
fail_frontend0:
	dvb_frontend_detach(dvb->frontend[0]);
	dvb_unरेजिस्टर_adapter(&dvb->adapter);
fail_adapter:
	वापस result;
पूर्ण

अटल व्योम unरेजिस्टर_dvb(काष्ठा cx231xx_dvb *dvb)
अणु
	dvb_net_release(&dvb->net);
	dvb->demux.dmx.हटाओ_frontend(&dvb->demux.dmx, &dvb->fe_mem);
	dvb->demux.dmx.हटाओ_frontend(&dvb->demux.dmx, &dvb->fe_hw);
	dvb_dmxdev_release(&dvb->dmxdev);
	dvb_dmx_release(&dvb->demux);
	अगर (dvb->frontend[1])
		dvb_unरेजिस्टर_frontend(dvb->frontend[1]);
	dvb_unरेजिस्टर_frontend(dvb->frontend[0]);
	अगर (dvb->frontend[1])
		dvb_frontend_detach(dvb->frontend[1]);
	dvb_frontend_detach(dvb->frontend[0]);
	dvb_unरेजिस्टर_adapter(&dvb->adapter);

	/* हटाओ I2C tuner */
	dvb_module_release(dvb->i2c_client_tuner);
	dvb->i2c_client_tuner = शून्य;
	/* हटाओ I2C demod(s) */
	dvb_module_release(dvb->i2c_client_demod[1]);
	dvb->i2c_client_demod[1] = शून्य;
	dvb_module_release(dvb->i2c_client_demod[0]);
	dvb->i2c_client_demod[0] = शून्य;
पूर्ण

अटल पूर्णांक dvb_init(काष्ठा cx231xx *dev)
अणु
	पूर्णांक result;
	काष्ठा cx231xx_dvb *dvb;
	काष्ठा i2c_adapter *tuner_i2c;
	काष्ठा i2c_adapter *demod_i2c;
	काष्ठा i2c_client *client;
	काष्ठा i2c_adapter *adapter;

	अगर (!dev->board.has_dvb) अणु
		/* This device करोes not support the extension */
		वापस 0;
	पूर्ण

	dvb = kzalloc(माप(काष्ठा cx231xx_dvb), GFP_KERNEL);

	अगर (dvb == शून्य) अणु
		dev_info(dev->dev,
			 "cx231xx_dvb: memory allocation failed\n");
		वापस -ENOMEM;
	पूर्ण
	dev->dvb = dvb;
	dev->cx231xx_set_analog_freq = cx231xx_set_analog_freq;
	dev->cx231xx_reset_analog_tuner = cx231xx_reset_analog_tuner;

	tuner_i2c = cx231xx_get_i2c_adap(dev, dev->board.tuner_i2c_master);
	demod_i2c = cx231xx_get_i2c_adap(dev, dev->board.demod_i2c_master);
	mutex_lock(&dev->lock);
	cx231xx_set_mode(dev, CX231XX_DIGITAL_MODE);
	cx231xx_demod_reset(dev);
	/* init frontend */
	चयन (dev->model) अणु
	हाल CX231XX_BOARD_CNXT_CARRAERA:
	हाल CX231XX_BOARD_CNXT_RDE_250:

		dev->dvb->frontend[0] = dvb_attach(s5h1432_attach,
					&dvico_s5h1432_config,
					demod_i2c);

		अगर (!dev->dvb->frontend[0]) अणु
			dev_err(dev->dev,
				"Failed to attach s5h1432 front end\n");
			result = -EINVAL;
			जाओ out_मुक्त;
		पूर्ण

		/* define general-purpose callback poपूर्णांकer */
		dvb->frontend[0]->callback = cx231xx_tuner_callback;

		अगर (!dvb_attach(xc5000_attach, dev->dvb->frontend[0],
			       tuner_i2c,
			       &cnxt_rde250_tunerconfig)) अणु
			result = -EINVAL;
			जाओ out_मुक्त;
		पूर्ण

		अवरोध;
	हाल CX231XX_BOARD_CNXT_SHELBY:
	हाल CX231XX_BOARD_CNXT_RDU_250:

		dev->dvb->frontend[0] = dvb_attach(s5h1411_attach,
					       &xc5000_s5h1411_config,
					       demod_i2c);

		अगर (!dev->dvb->frontend[0]) अणु
			dev_err(dev->dev,
				"Failed to attach s5h1411 front end\n");
			result = -EINVAL;
			जाओ out_मुक्त;
		पूर्ण

		/* define general-purpose callback poपूर्णांकer */
		dvb->frontend[0]->callback = cx231xx_tuner_callback;

		अगर (!dvb_attach(xc5000_attach, dev->dvb->frontend[0],
			       tuner_i2c,
			       &cnxt_rdu250_tunerconfig)) अणु
			result = -EINVAL;
			जाओ out_मुक्त;
		पूर्ण
		अवरोध;
	हाल CX231XX_BOARD_CNXT_RDE_253S:

		dev->dvb->frontend[0] = dvb_attach(s5h1432_attach,
					&dvico_s5h1432_config,
					demod_i2c);

		अगर (!dev->dvb->frontend[0]) अणु
			dev_err(dev->dev,
				"Failed to attach s5h1432 front end\n");
			result = -EINVAL;
			जाओ out_मुक्त;
		पूर्ण

		/* define general-purpose callback poपूर्णांकer */
		dvb->frontend[0]->callback = cx231xx_tuner_callback;

		अगर (!dvb_attach(tda18271_attach, dev->dvb->frontend[0],
			       dev->board.tuner_addr, tuner_i2c,
			       &cnxt_rde253s_tunerconfig)) अणु
			result = -EINVAL;
			जाओ out_मुक्त;
		पूर्ण
		अवरोध;
	हाल CX231XX_BOARD_CNXT_RDU_253S:
	हाल CX231XX_BOARD_KWORLD_UB445_USB_HYBRID:

		dev->dvb->frontend[0] = dvb_attach(s5h1411_attach,
					       &tda18271_s5h1411_config,
					       demod_i2c);

		अगर (!dev->dvb->frontend[0]) अणु
			dev_err(dev->dev,
				"Failed to attach s5h1411 front end\n");
			result = -EINVAL;
			जाओ out_मुक्त;
		पूर्ण

		/* define general-purpose callback poपूर्णांकer */
		dvb->frontend[0]->callback = cx231xx_tuner_callback;

		अगर (!dvb_attach(tda18271_attach, dev->dvb->frontend[0],
			       dev->board.tuner_addr, tuner_i2c,
			       &cnxt_rde253s_tunerconfig)) अणु
			result = -EINVAL;
			जाओ out_मुक्त;
		पूर्ण
		अवरोध;
	हाल CX231XX_BOARD_HAUPPAUGE_EXETER:

		dev_info(dev->dev,
			 "%s: looking for tuner / demod on i2c bus: %d\n",
		       __func__, i2c_adapter_id(tuner_i2c));

		dev->dvb->frontend[0] = dvb_attach(lgdt3305_attach,
						&hcw_lgdt3305_config,
						demod_i2c);

		अगर (!dev->dvb->frontend[0]) अणु
			dev_err(dev->dev,
				"Failed to attach LG3305 front end\n");
			result = -EINVAL;
			जाओ out_मुक्त;
		पूर्ण

		/* define general-purpose callback poपूर्णांकer */
		dvb->frontend[0]->callback = cx231xx_tuner_callback;

		dvb_attach(tda18271_attach, dev->dvb->frontend[0],
			   dev->board.tuner_addr, tuner_i2c,
			   &hcw_tda18271_config);
		अवरोध;

	हाल CX231XX_BOARD_HAUPPAUGE_930C_HD_1113xx:
	अणु
		काष्ठा si2165_platक्रमm_data si2165_pdata = अणुपूर्ण;

		/* attach demod */
		si2165_pdata.fe = &dev->dvb->frontend[0];
		si2165_pdata.chip_mode = SI2165_MODE_PLL_XTAL;
		si2165_pdata.ref_freq_hz = 16000000;

		/* perक्रमm probe/init/attach */
		client = dvb_module_probe("si2165", शून्य, demod_i2c,
						dev->board.demod_addr,
						&si2165_pdata);
		अगर (!client) अणु
			result = -ENODEV;
			जाओ out_मुक्त;
		पूर्ण
		dvb->i2c_client_demod[0] = client;

		dev->dvb->frontend[0]->ops.i2c_gate_ctrl = शून्य;

		/* define general-purpose callback poपूर्णांकer */
		dvb->frontend[0]->callback = cx231xx_tuner_callback;

		dvb_attach(tda18271_attach, dev->dvb->frontend[0],
			dev->board.tuner_addr, tuner_i2c,
			&hcw_tda18271_config);

		dev->cx231xx_reset_analog_tuner = शून्य;
		अवरोध;
	पूर्ण
	हाल CX231XX_BOARD_HAUPPAUGE_930C_HD_1114xx:
	अणु
		काष्ठा si2165_platक्रमm_data si2165_pdata = अणुपूर्ण;
		काष्ठा si2157_config si2157_config = अणुपूर्ण;

		/* attach demod */
		si2165_pdata.fe = &dev->dvb->frontend[0];
		si2165_pdata.chip_mode = SI2165_MODE_PLL_EXT;
		si2165_pdata.ref_freq_hz = 24000000;

		/* perक्रमm probe/init/attach */
		client = dvb_module_probe("si2165", शून्य, demod_i2c,
						dev->board.demod_addr,
						&si2165_pdata);
		अगर (!client) अणु
			result = -ENODEV;
			जाओ out_मुक्त;
		पूर्ण
		dvb->i2c_client_demod[0] = client;

		dev->dvb->frontend[0]->ops.i2c_gate_ctrl = शून्य;

		/* define general-purpose callback poपूर्णांकer */
		dvb->frontend[0]->callback = cx231xx_tuner_callback;

		/* attach tuner */
		si2157_config.fe = dev->dvb->frontend[0];
#अगर_घोषित CONFIG_MEDIA_CONTROLLER_DVB
		si2157_config.mdev = dev->media_dev;
#पूर्ण_अगर
		si2157_config.अगर_port = 1;
		si2157_config.inversion = true;

		/* perक्रमm probe/init/attach */
		client = dvb_module_probe("si2157", शून्य, tuner_i2c,
						dev->board.tuner_addr,
						&si2157_config);
		अगर (!client) अणु
			result = -ENODEV;
			जाओ out_मुक्त;
		पूर्ण
		dev->cx231xx_reset_analog_tuner = शून्य;

		dev->dvb->i2c_client_tuner = client;
		अवरोध;
	पूर्ण
	हाल CX231XX_BOARD_HAUPPAUGE_955Q:
	अणु
		काष्ठा si2157_config si2157_config = अणुपूर्ण;
		काष्ठा lgdt3306a_config lgdt3306a_config = अणुपूर्ण;

		lgdt3306a_config = hauppauge_955q_lgdt3306a_config;
		lgdt3306a_config.fe = &dev->dvb->frontend[0];
		lgdt3306a_config.i2c_adapter = &adapter;

		/* perक्रमm probe/init/attach */
		client = dvb_module_probe("lgdt3306a", शून्य, demod_i2c,
						dev->board.demod_addr,
						&lgdt3306a_config);
		अगर (!client) अणु
			result = -ENODEV;
			जाओ out_मुक्त;
		पूर्ण
		dvb->i2c_client_demod[0] = client;

		dev->dvb->frontend[0]->ops.i2c_gate_ctrl = शून्य;

		/* define general-purpose callback poपूर्णांकer */
		dvb->frontend[0]->callback = cx231xx_tuner_callback;

		/* attach tuner */
		si2157_config.fe = dev->dvb->frontend[0];
#अगर_घोषित CONFIG_MEDIA_CONTROLLER_DVB
		si2157_config.mdev = dev->media_dev;
#पूर्ण_अगर
		si2157_config.अगर_port = 1;
		si2157_config.inversion = true;

		/* perक्रमm probe/init/attach */
		client = dvb_module_probe("si2157", शून्य, tuner_i2c,
						dev->board.tuner_addr,
						&si2157_config);
		अगर (!client) अणु
			result = -ENODEV;
			जाओ out_मुक्त;
		पूर्ण
		dev->cx231xx_reset_analog_tuner = शून्य;

		dev->dvb->i2c_client_tuner = client;
		अवरोध;
	पूर्ण
	हाल CX231XX_BOARD_PV_PLAYTV_USB_HYBRID:
	हाल CX231XX_BOARD_KWORLD_UB430_USB_HYBRID:

		dev_info(dev->dev,
			 "%s: looking for demod on i2c bus: %d\n",
			 __func__, i2c_adapter_id(tuner_i2c));

		dev->dvb->frontend[0] = dvb_attach(mb86a20s_attach,
						&pv_mb86a20s_config,
						demod_i2c);

		अगर (!dev->dvb->frontend[0]) अणु
			dev_err(dev->dev,
				"Failed to attach mb86a20s demod\n");
			result = -EINVAL;
			जाओ out_मुक्त;
		पूर्ण

		/* define general-purpose callback poपूर्णांकer */
		dvb->frontend[0]->callback = cx231xx_tuner_callback;

		dvb_attach(tda18271_attach, dev->dvb->frontend[0],
			   dev->board.tuner_addr, tuner_i2c,
			   &pv_tda18271_config);
		अवरोध;

	हाल CX231XX_BOARD_EVROMEDIA_FULL_HYBRID_FULLHD:
	अणु
		काष्ठा si2157_config si2157_config = अणुपूर्ण;
		काष्ठा si2168_config si2168_config = अणुपूर्ण;

		/* attach demodulator chip */
		si2168_config.ts_mode = SI2168_TS_SERIAL; /* from *.inf file */
		si2168_config.fe = &dev->dvb->frontend[0];
		si2168_config.i2c_adapter = &adapter;
		si2168_config.ts_घड़ी_inv = true;

		/* perक्रमm probe/init/attach */
		client = dvb_module_probe("si2168", शून्य, demod_i2c,
						dev->board.demod_addr,
						&si2168_config);
		अगर (!client) अणु
			result = -ENODEV;
			जाओ out_मुक्त;
		पूर्ण
		dvb->i2c_client_demod[0] = client;

		/* attach tuner chip */
		si2157_config.fe = dev->dvb->frontend[0];
#अगर_घोषित CONFIG_MEDIA_CONTROLLER_DVB
		si2157_config.mdev = dev->media_dev;
#पूर्ण_अगर
		si2157_config.अगर_port = 1;
		si2157_config.inversion = false;

		/* perक्रमm probe/init/attach */
		client = dvb_module_probe("si2157", शून्य, tuner_i2c,
						dev->board.tuner_addr,
						&si2157_config);
		अगर (!client) अणु
			result = -ENODEV;
			जाओ out_मुक्त;
		पूर्ण
		dev->cx231xx_reset_analog_tuner = शून्य;
		dev->dvb->i2c_client_tuner = client;
		अवरोध;
	पूर्ण
	हाल CX231XX_BOARD_ASTROMETA_T2HYBRID:
	अणु
		काष्ठा mn88473_config mn88473_config = अणुपूर्ण;

		/* attach demodulator chip */
		mn88473_config.i2c_wr_max = 16;
		mn88473_config.xtal = 25000000;
		mn88473_config.fe = &dev->dvb->frontend[0];

		/* perक्रमm probe/init/attach */
		client = dvb_module_probe("mn88473", शून्य, demod_i2c,
						dev->board.demod_addr,
						&mn88473_config);
		अगर (!client) अणु
			result = -ENODEV;
			जाओ out_मुक्त;
		पूर्ण
		dvb->i2c_client_demod[0] = client;

		/* define general-purpose callback poपूर्णांकer */
		dvb->frontend[0]->callback = cx231xx_tuner_callback;

		/* attach tuner chip */
		dvb_attach(r820t_attach, dev->dvb->frontend[0],
			   tuner_i2c,
			   &astrometa_t2hybrid_r820t_config);
		अवरोध;
	पूर्ण
	हाल CX231XX_BOARD_HAUPPAUGE_935C:
	अणु
		काष्ठा si2157_config si2157_config = अणुपूर्ण;
		काष्ठा si2168_config si2168_config = अणुपूर्ण;

		/* attach demodulator chip */
		si2168_config.ts_mode = SI2168_TS_SERIAL;
		si2168_config.fe = &dev->dvb->frontend[0];
		si2168_config.i2c_adapter = &adapter;
		si2168_config.ts_घड़ी_inv = true;

		/* perक्रमm probe/init/attach */
		client = dvb_module_probe("si2168", शून्य, demod_i2c,
						dev->board.demod_addr,
						&si2168_config);
		अगर (!client) अणु
			result = -ENODEV;
			जाओ out_मुक्त;
		पूर्ण
		dvb->i2c_client_demod[0] = client;
		dev->dvb->frontend[0]->ops.i2c_gate_ctrl = शून्य;

		/* define general-purpose callback poपूर्णांकer */
		dvb->frontend[0]->callback = cx231xx_tuner_callback;

		/* attach tuner */
		si2157_config.fe = dev->dvb->frontend[0];
#अगर_घोषित CONFIG_MEDIA_CONTROLLER_DVB
		si2157_config.mdev = dev->media_dev;
#पूर्ण_अगर
		si2157_config.अगर_port = 1;
		si2157_config.inversion = true;

		/* perक्रमm probe/init/attach */
		client = dvb_module_probe("si2157", शून्य, tuner_i2c,
						dev->board.tuner_addr,
						&si2157_config);
		अगर (!client) अणु
			result = -ENODEV;
			जाओ out_मुक्त;
		पूर्ण
		dev->cx231xx_reset_analog_tuner = शून्य;
		dev->dvb->i2c_client_tuner = client;
		अवरोध;
	पूर्ण
	हाल CX231XX_BOARD_HAUPPAUGE_975:
	अणु
		काष्ठा i2c_adapter *adapter2;
		काष्ठा si2157_config si2157_config = अणुपूर्ण;
		काष्ठा lgdt3306a_config lgdt3306a_config = अणुपूर्ण;
		काष्ठा si2168_config si2168_config = अणुपूर्ण;

		/* attach first demodulator chip */
		lgdt3306a_config = hauppauge_955q_lgdt3306a_config;
		lgdt3306a_config.fe = &dev->dvb->frontend[0];
		lgdt3306a_config.i2c_adapter = &adapter;

		/* perक्रमm probe/init/attach */
		client = dvb_module_probe("lgdt3306a", शून्य, demod_i2c,
						dev->board.demod_addr,
						&lgdt3306a_config);
		अगर (!client) अणु
			result = -ENODEV;
			जाओ out_मुक्त;
		पूर्ण
		dvb->i2c_client_demod[0] = client;

		/* attach second demodulator chip */
		si2168_config.ts_mode = SI2168_TS_SERIAL;
		si2168_config.fe = &dev->dvb->frontend[1];
		si2168_config.i2c_adapter = &adapter2;
		si2168_config.ts_घड़ी_inv = true;

		/* perक्रमm probe/init/attach */
		client = dvb_module_probe("si2168", शून्य, adapter,
						dev->board.demod_addr2,
						&si2168_config);
		अगर (!client) अणु
			result = -ENODEV;
			जाओ out_मुक्त;
		पूर्ण
		dvb->i2c_client_demod[1] = client;
		dvb->frontend[1]->id = 1;

		/* define general-purpose callback poपूर्णांकer */
		dvb->frontend[0]->callback = cx231xx_tuner_callback;
		dvb->frontend[1]->callback = cx231xx_tuner_callback;

		/* attach tuner */
		si2157_config.fe = dev->dvb->frontend[0];
#अगर_घोषित CONFIG_MEDIA_CONTROLLER_DVB
		si2157_config.mdev = dev->media_dev;
#पूर्ण_अगर
		si2157_config.अगर_port = 1;
		si2157_config.inversion = true;

		/* perक्रमm probe/init/attach */
		client = dvb_module_probe("si2157", शून्य, adapter,
						dev->board.tuner_addr,
						&si2157_config);
		अगर (!client) अणु
			result = -ENODEV;
			जाओ out_मुक्त;
		पूर्ण
		dev->cx231xx_reset_analog_tuner = शून्य;
		dvb->i2c_client_tuner = client;

		dvb->frontend[1]->tuner_priv = dvb->frontend[0]->tuner_priv;

		स_नकल(&dvb->frontend[1]->ops.tuner_ops,
			&dvb->frontend[0]->ops.tuner_ops,
			माप(काष्ठा dvb_tuner_ops));
		अवरोध;
	पूर्ण
	शेष:
		dev_err(dev->dev,
			"%s/2: The frontend of your DVB/ATSC card isn't supported yet\n",
			dev->name);
		अवरोध;
	पूर्ण
	अगर (!dvb->frontend[0]) अणु
		dev_err(dev->dev,
		       "%s/2: frontend initialization failed\n", dev->name);
		result = -EINVAL;
		जाओ out_मुक्त;
	पूर्ण

	/* रेजिस्टर everything */
	result = रेजिस्टर_dvb(dvb, THIS_MODULE, dev, dev->dev);

	अगर (result < 0)
		जाओ out_मुक्त;


	dev_info(dev->dev, "Successfully loaded cx231xx-dvb\n");

ret:
	cx231xx_set_mode(dev, CX231XX_SUSPEND);
	mutex_unlock(&dev->lock);
	वापस result;

out_मुक्त:
	/* हटाओ I2C tuner */
	dvb_module_release(dvb->i2c_client_tuner);
	dvb->i2c_client_tuner = शून्य;
	/* हटाओ I2C demod(s) */
	dvb_module_release(dvb->i2c_client_demod[1]);
	dvb->i2c_client_demod[1] = शून्य;
	dvb_module_release(dvb->i2c_client_demod[0]);
	dvb->i2c_client_demod[0] = शून्य;
	kमुक्त(dvb);
	dev->dvb = शून्य;
	जाओ ret;
पूर्ण

अटल पूर्णांक dvb_fini(काष्ठा cx231xx *dev)
अणु
	अगर (!dev->board.has_dvb) अणु
		/* This device करोes not support the extension */
		वापस 0;
	पूर्ण

	अगर (dev->dvb) अणु
		unरेजिस्टर_dvb(dev->dvb);
		kमुक्त(dev->dvb);
		dev->dvb = शून्य;
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा cx231xx_ops dvb_ops = अणु
	.id = CX231XX_DVB,
	.name = "Cx231xx dvb Extension",
	.init = dvb_init,
	.fini = dvb_fini,
पूर्ण;

अटल पूर्णांक __init cx231xx_dvb_रेजिस्टर(व्योम)
अणु
	वापस cx231xx_रेजिस्टर_extension(&dvb_ops);
पूर्ण

अटल व्योम __निकास cx231xx_dvb_unरेजिस्टर(व्योम)
अणु
	cx231xx_unरेजिस्टर_extension(&dvb_ops);
पूर्ण

module_init(cx231xx_dvb_रेजिस्टर);
module_निकास(cx231xx_dvb_unरेजिस्टर);
