<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  cx18 functions क्रम DVB support
 *
 *  Copyright (c) 2008 Steven Toth <stoth@linuxtv.org>
 *  Copyright (C) 2008  Andy Walls <awalls@md.metrocast.net>
 */

#समावेश "cx18-version.h"
#समावेश "cx18-dvb.h"
#समावेश "cx18-io.h"
#समावेश "cx18-queue.h"
#समावेश "cx18-streams.h"
#समावेश "cx18-cards.h"
#समावेश "cx18-gpio.h"
#समावेश "s5h1409.h"
#समावेश "mxl5005s.h"
#समावेश "s5h1411.h"
#समावेश "tda18271.h"
#समावेश "zl10353.h"

#समावेश <linux/firmware.h>
#समावेश "mt352.h"
#समावेश "mt352_priv.h"
#समावेश "tuner-xc2028.h"

DVB_DEFINE_MOD_OPT_ADAPTER_NR(adapter_nr);

#घोषणा FWखाता "dvb-cx18-mpc718-mt352.fw"

#घोषणा CX18_REG_DMUX_NUM_PORT_0_CONTROL 0xd5a000
#घोषणा CX18_CLOCK_ENABLE2		 0xc71024
#घोषणा CX18_DMUX_CLK_MASK		 0x0080

/*
 * CX18_CARD_HVR_1600_ESMT
 * CX18_CARD_HVR_1600_SAMSUNG
 */

अटल काष्ठा mxl5005s_config hauppauge_hvr1600_tuner = अणु
	.i2c_address     = 0xC6 >> 1,
	.अगर_freq         = IF_FREQ_5380000HZ,
	.xtal_freq       = CRYSTAL_FREQ_16000000HZ,
	.agc_mode        = MXL_SINGLE_AGC,
	.tracking_filter = MXL_TF_C_H,
	.rssi_enable     = MXL_RSSI_ENABLE,
	.cap_select      = MXL_CAP_SEL_ENABLE,
	.भाग_out         = MXL_DIV_OUT_4,
	.घड़ी_out       = MXL_CLOCK_OUT_DISABLE,
	.output_load     = MXL5005S_IF_OUTPUT_LOAD_200_OHM,
	.top		 = MXL5005S_TOP_25P2,
	.mod_mode        = MXL_DIGITAL_MODE,
	.अगर_mode         = MXL_ZERO_IF,
	.qam_gain        = 0x02,
	.AgcMasterByte   = 0x00,
पूर्ण;

अटल काष्ठा s5h1409_config hauppauge_hvr1600_config = अणु
	.demod_address = 0x32 >> 1,
	.output_mode   = S5H1409_SERIAL_OUTPUT,
	.gpio          = S5H1409_GPIO_ON,
	.qam_अगर        = 44000,
	.inversion     = S5H1409_INVERSION_OFF,
	.status_mode   = S5H1409_DEMODLOCKING,
	.mpeg_timing   = S5H1409_MPEGTIMING_CONTINUOUS_NONINVERTING_CLOCK,
	.hvr1600_opt   = S5H1409_HVR1600_OPTIMIZE
पूर्ण;

/*
 * CX18_CARD_HVR_1600_S5H1411
 */
अटल काष्ठा s5h1411_config hcw_s5h1411_config = अणु
	.output_mode   = S5H1411_SERIAL_OUTPUT,
	.gpio          = S5H1411_GPIO_OFF,
	.vsb_अगर        = S5H1411_IF_44000,
	.qam_अगर        = S5H1411_IF_4000,
	.inversion     = S5H1411_INVERSION_ON,
	.status_mode   = S5H1411_DEMODLOCKING,
	.mpeg_timing   = S5H1411_MPEGTIMING_CONTINUOUS_NONINVERTING_CLOCK,
पूर्ण;

अटल काष्ठा tda18271_std_map hauppauge_tda18271_std_map = अणु
	.atsc_6   = अणु .अगर_freq = 5380, .agc_mode = 3, .std = 3,
		      .अगर_lvl = 6, .rfagc_top = 0x37 पूर्ण,
	.qam_6    = अणु .अगर_freq = 4000, .agc_mode = 3, .std = 0,
		      .अगर_lvl = 6, .rfagc_top = 0x37 पूर्ण,
पूर्ण;

अटल काष्ठा tda18271_config hauppauge_tda18271_config = अणु
	.std_map = &hauppauge_tda18271_std_map,
	.gate    = TDA18271_GATE_DIGITAL,
	.output_opt = TDA18271_OUTPUT_LT_OFF,
पूर्ण;

/*
 * CX18_CARD_LEADTEK_DVR3100H
 */
/* Inक्रमmation/confirmation of proper config values provided by Terry Wu */
अटल काष्ठा zl10353_config leadtek_dvr3100h_demod = अणु
	.demod_address         = 0x1e >> 1, /* Datasheet suggested straps */
	.अगर2                   = 45600,     /* 4.560 MHz IF from the XC3028 */
	.parallel_ts           = 1,         /* Not a serial TS */
	.no_tuner              = 1,         /* XC3028 is not behind the gate */
	.disable_i2c_gate_ctrl = 1,         /* Disable the I2C gate */
पूर्ण;

/*
 * CX18_CARD_YUAN_MPC718
 */
/*
 * Due to
 *
 * 1. an असलence of inक्रमmation on how to program the MT352
 * 2. the Linux mt352 module pushing MT352 initialization off onto us here
 *
 * We have to use an init sequence that *you* must extract from the Winकरोws
 * driver (yuanrap.sys) and which we load as a firmware.
 *
 * If someone can provide me with a Zarlink MT352 (Intel CE6352?) Design Manual
 * with chip programming details, then I can हटाओ this annoyance.
 */
अटल पूर्णांक yuan_mpc718_mt352_reqfw(काष्ठा cx18_stream *stream,
				   स्थिर काष्ठा firmware **fw)
अणु
	काष्ठा cx18 *cx = stream->cx;
	स्थिर अक्षर *fn = FWखाता;
	पूर्णांक ret;

	ret = request_firmware(fw, fn, &cx->pci_dev->dev);
	अगर (ret)
		CX18_ERR("Unable to open firmware file %s\n", fn);
	अन्यथा अणु
		माप_प्रकार sz = (*fw)->size;
		अगर (sz < 2 || sz > 64 || (sz % 2) != 0) अणु
			CX18_ERR("Firmware %s has a bad size: %lu bytes\n",
				 fn, (अचिन्हित दीर्घ) sz);
			ret = -EILSEQ;
			release_firmware(*fw);
			*fw = शून्य;
		पूर्ण
	पूर्ण

	अगर (ret) अणु
		CX18_ERR("The MPC718 board variant with the MT352 DVB-T demodulator will not work without it\n");
		CX18_ERR("Run 'linux/scripts/get_dvb_firmware mpc718' if you need the firmware\n");
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक yuan_mpc718_mt352_init(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा cx18_dvb *dvb = container_of(fe->dvb,
					    काष्ठा cx18_dvb, dvb_adapter);
	काष्ठा cx18_stream *stream = dvb->stream;
	स्थिर काष्ठा firmware *fw = शून्य;
	पूर्णांक ret;
	पूर्णांक i;
	u8 buf[3];

	ret = yuan_mpc718_mt352_reqfw(stream, &fw);
	अगर (ret)
		वापस ret;

	/* Loop through all the रेजिस्टर-value pairs in the firmware file */
	क्रम (i = 0; i < fw->size; i += 2) अणु
		buf[0] = fw->data[i];
		/* Intercept a few रेजिस्टरs we want to set ourselves */
		चयन (buf[0]) अणु
		हाल TRL_NOMINAL_RATE_0:
			/* Set our custom OFDM bandwidth in the हाल below */
			अवरोध;
		हाल TRL_NOMINAL_RATE_1:
			/* 6 MHz: 64/7 * 6/8 / 20.48 * 2^16 = 0x55b6.db6 */
			/* 7 MHz: 64/7 * 7/8 / 20.48 * 2^16 = 0x6400 */
			/* 8 MHz: 64/7 * 8/8 / 20.48 * 2^16 = 0x7249.249 */
			buf[1] = 0x72;
			buf[2] = 0x49;
			mt352_ग_लिखो(fe, buf, 3);
			अवरोध;
		हाल INPUT_FREQ_0:
			/* Set our custom IF in the हाल below */
			अवरोध;
		हाल INPUT_FREQ_1:
			/* 4.56 MHz IF: (20.48 - 4.56)/20.48 * 2^14 = 0x31c0 */
			buf[1] = 0x31;
			buf[2] = 0xc0;
			mt352_ग_लिखो(fe, buf, 3);
			अवरोध;
		शेष:
			/* Pass through the रेजिस्टर-value pair from the fw */
			buf[1] = fw->data[i+1];
			mt352_ग_लिखो(fe, buf, 2);
			अवरोध;
		पूर्ण
	पूर्ण

	buf[0] = (u8) TUNER_GO;
	buf[1] = 0x01; /* Go */
	mt352_ग_लिखो(fe, buf, 2);
	release_firmware(fw);
	वापस 0;
पूर्ण

अटल काष्ठा mt352_config yuan_mpc718_mt352_demod = अणु
	.demod_address = 0x1e >> 1,
	.adc_घड़ी     = 20480,     /* 20.480 MHz */
	.अगर2           =  4560,     /*  4.560 MHz */
	.no_tuner      = 1,         /* XC3028 is not behind the gate */
	.demod_init    = yuan_mpc718_mt352_init,
पूर्ण;

अटल काष्ठा zl10353_config yuan_mpc718_zl10353_demod = अणु
	.demod_address         = 0x1e >> 1, /* Datasheet suggested straps */
	.अगर2                   = 45600,     /* 4.560 MHz IF from the XC3028 */
	.parallel_ts           = 1,         /* Not a serial TS */
	.no_tuner              = 1,         /* XC3028 is not behind the gate */
	.disable_i2c_gate_ctrl = 1,         /* Disable the I2C gate */
पूर्ण;

अटल काष्ठा zl10353_config gotview_dvd3_zl10353_demod = अणु
	.demod_address         = 0x1e >> 1, /* Datasheet suggested straps */
	.अगर2                   = 45600,     /* 4.560 MHz IF from the XC3028 */
	.parallel_ts           = 1,         /* Not a serial TS */
	.no_tuner              = 1,         /* XC3028 is not behind the gate */
	.disable_i2c_gate_ctrl = 1,         /* Disable the I2C gate */
पूर्ण;

अटल पूर्णांक dvb_रेजिस्टर(काष्ठा cx18_stream *stream);

/* Kernel DVB framework calls this when the feed needs to start.
 * The CX18 framework should enable the transport DMA handling
 * and queue processing.
 */
अटल पूर्णांक cx18_dvb_start_feed(काष्ठा dvb_demux_feed *feed)
अणु
	काष्ठा dvb_demux *demux = feed->demux;
	काष्ठा cx18_stream *stream = (काष्ठा cx18_stream *) demux->priv;
	काष्ठा cx18 *cx;
	पूर्णांक ret;
	u32 v;

	अगर (!stream)
		वापस -EINVAL;

	cx = stream->cx;
	CX18_DEBUG_INFO("Start feed: pid = 0x%x index = %d\n",
			feed->pid, feed->index);

	mutex_lock(&cx->serialize_lock);
	ret = cx18_init_on_first_खोलो(cx);
	mutex_unlock(&cx->serialize_lock);
	अगर (ret) अणु
		CX18_ERR("Failed to initialize firmware starting DVB feed\n");
		वापस ret;
	पूर्ण
	ret = -EINVAL;

	चयन (cx->card->type) अणु
	हाल CX18_CARD_HVR_1600_ESMT:
	हाल CX18_CARD_HVR_1600_SAMSUNG:
	हाल CX18_CARD_HVR_1600_S5H1411:
		v = cx18_पढ़ो_reg(cx, CX18_REG_DMUX_NUM_PORT_0_CONTROL);
		v |= 0x00400000; /* Serial Mode */
		v |= 0x00002000; /* Data Length - Byte */
		v |= 0x00010000; /* Error - Polarity */
		v |= 0x00020000; /* Error - Passthru */
		v |= 0x000c0000; /* Error - Ignore */
		cx18_ग_लिखो_reg(cx, v, CX18_REG_DMUX_NUM_PORT_0_CONTROL);
		अवरोध;

	हाल CX18_CARD_LEADTEK_DVR3100H:
	हाल CX18_CARD_YUAN_MPC718:
	हाल CX18_CARD_GOTVIEW_PCI_DVD3:
	शेष:
		/* Assumption - Parallel transport - Signalling
		 * undefined or शेष.
		 */
		अवरोध;
	पूर्ण

	अगर (!demux->dmx.frontend)
		वापस -EINVAL;

	mutex_lock(&stream->dvb->feedlock);
	अगर (stream->dvb->feeding++ == 0) अणु
		CX18_DEBUG_INFO("Starting Transport DMA\n");
		mutex_lock(&cx->serialize_lock);
		set_bit(CX18_F_S_STREAMING, &stream->s_flags);
		ret = cx18_start_v4l2_encode_stream(stream);
		अगर (ret < 0) अणु
			CX18_DEBUG_INFO("Failed to start Transport DMA\n");
			stream->dvb->feeding--;
			अगर (stream->dvb->feeding == 0)
				clear_bit(CX18_F_S_STREAMING, &stream->s_flags);
		पूर्ण
		mutex_unlock(&cx->serialize_lock);
	पूर्ण अन्यथा
		ret = 0;
	mutex_unlock(&stream->dvb->feedlock);

	वापस ret;
पूर्ण

/* Kernel DVB framework calls this when the feed needs to stop. */
अटल पूर्णांक cx18_dvb_stop_feed(काष्ठा dvb_demux_feed *feed)
अणु
	काष्ठा dvb_demux *demux = feed->demux;
	काष्ठा cx18_stream *stream = (काष्ठा cx18_stream *)demux->priv;
	काष्ठा cx18 *cx;
	पूर्णांक ret = -EINVAL;

	अगर (stream) अणु
		cx = stream->cx;
		CX18_DEBUG_INFO("Stop feed: pid = 0x%x index = %d\n",
				feed->pid, feed->index);

		mutex_lock(&stream->dvb->feedlock);
		अगर (--stream->dvb->feeding == 0) अणु
			CX18_DEBUG_INFO("Stopping Transport DMA\n");
			mutex_lock(&cx->serialize_lock);
			ret = cx18_stop_v4l2_encode_stream(stream, 0);
			mutex_unlock(&cx->serialize_lock);
		पूर्ण अन्यथा
			ret = 0;
		mutex_unlock(&stream->dvb->feedlock);
	पूर्ण

	वापस ret;
पूर्ण

पूर्णांक cx18_dvb_रेजिस्टर(काष्ठा cx18_stream *stream)
अणु
	काष्ठा cx18 *cx = stream->cx;
	काष्ठा cx18_dvb *dvb = stream->dvb;
	काष्ठा dvb_adapter *dvb_adapter;
	काष्ठा dvb_demux *dvbdemux;
	काष्ठा dmx_demux *dmx;
	पूर्णांक ret;

	अगर (!dvb)
		वापस -EINVAL;

	dvb->enabled = 0;
	dvb->stream = stream;

	ret = dvb_रेजिस्टर_adapter(&dvb->dvb_adapter,
			CX18_DRIVER_NAME,
			THIS_MODULE, &cx->pci_dev->dev, adapter_nr);
	अगर (ret < 0)
		जाओ err_out;

	dvb_adapter = &dvb->dvb_adapter;

	dvbdemux = &dvb->demux;

	dvbdemux->priv = (व्योम *)stream;

	dvbdemux->filternum = 256;
	dvbdemux->feednum = 256;
	dvbdemux->start_feed = cx18_dvb_start_feed;
	dvbdemux->stop_feed = cx18_dvb_stop_feed;
	dvbdemux->dmx.capabilities = (DMX_TS_FILTERING |
		DMX_SECTION_FILTERING | DMX_MEMORY_BASED_FILTERING);
	ret = dvb_dmx_init(dvbdemux);
	अगर (ret < 0)
		जाओ err_dvb_unरेजिस्टर_adapter;

	dmx = &dvbdemux->dmx;

	dvb->hw_frontend.source = DMX_FRONTEND_0;
	dvb->mem_frontend.source = DMX_MEMORY_FE;
	dvb->dmxdev.filternum = 256;
	dvb->dmxdev.demux = dmx;

	ret = dvb_dmxdev_init(&dvb->dmxdev, dvb_adapter);
	अगर (ret < 0)
		जाओ err_dvb_dmx_release;

	ret = dmx->add_frontend(dmx, &dvb->hw_frontend);
	अगर (ret < 0)
		जाओ err_dvb_dmxdev_release;

	ret = dmx->add_frontend(dmx, &dvb->mem_frontend);
	अगर (ret < 0)
		जाओ err_हटाओ_hw_frontend;

	ret = dmx->connect_frontend(dmx, &dvb->hw_frontend);
	अगर (ret < 0)
		जाओ err_हटाओ_mem_frontend;

	ret = dvb_रेजिस्टर(stream);
	अगर (ret < 0)
		जाओ err_disconnect_frontend;

	dvb_net_init(dvb_adapter, &dvb->dvbnet, dmx);

	CX18_INFO("DVB Frontend registered\n");
	CX18_INFO("Registered DVB adapter%d for %s (%d x %d.%02d kB)\n",
		  stream->dvb->dvb_adapter.num, stream->name,
		  stream->buffers, stream->buf_size/1024,
		  (stream->buf_size * 100 / 1024) % 100);

	mutex_init(&dvb->feedlock);
	dvb->enabled = 1;
	वापस ret;

err_disconnect_frontend:
	dmx->disconnect_frontend(dmx);
err_हटाओ_mem_frontend:
	dmx->हटाओ_frontend(dmx, &dvb->mem_frontend);
err_हटाओ_hw_frontend:
	dmx->हटाओ_frontend(dmx, &dvb->hw_frontend);
err_dvb_dmxdev_release:
	dvb_dmxdev_release(&dvb->dmxdev);
err_dvb_dmx_release:
	dvb_dmx_release(dvbdemux);
err_dvb_unरेजिस्टर_adapter:
	dvb_unरेजिस्टर_adapter(dvb_adapter);
err_out:
	वापस ret;
पूर्ण

व्योम cx18_dvb_unरेजिस्टर(काष्ठा cx18_stream *stream)
अणु
	काष्ठा cx18 *cx = stream->cx;
	काष्ठा cx18_dvb *dvb = stream->dvb;
	काष्ठा dvb_adapter *dvb_adapter;
	काष्ठा dvb_demux *dvbdemux;
	काष्ठा dmx_demux *dmx;

	CX18_INFO("unregister DVB\n");

	अगर (dvb == शून्य || !dvb->enabled)
		वापस;

	dvb_adapter = &dvb->dvb_adapter;
	dvbdemux = &dvb->demux;
	dmx = &dvbdemux->dmx;

	dmx->बंद(dmx);
	dvb_net_release(&dvb->dvbnet);
	dmx->हटाओ_frontend(dmx, &dvb->mem_frontend);
	dmx->हटाओ_frontend(dmx, &dvb->hw_frontend);
	dvb_dmxdev_release(&dvb->dmxdev);
	dvb_dmx_release(dvbdemux);
	dvb_unरेजिस्टर_frontend(dvb->fe);
	dvb_frontend_detach(dvb->fe);
	dvb_unरेजिस्टर_adapter(dvb_adapter);
पूर्ण

/* All the DVB attach calls go here, this function माला_लो modअगरied
 * क्रम each new card. cx18_dvb_start_feed() will also need changes.
 */
अटल पूर्णांक dvb_रेजिस्टर(काष्ठा cx18_stream *stream)
अणु
	काष्ठा cx18_dvb *dvb = stream->dvb;
	काष्ठा cx18 *cx = stream->cx;
	पूर्णांक ret = 0;

	चयन (cx->card->type) अणु
	हाल CX18_CARD_HVR_1600_ESMT:
	हाल CX18_CARD_HVR_1600_SAMSUNG:
		dvb->fe = dvb_attach(s5h1409_attach,
			&hauppauge_hvr1600_config,
			&cx->i2c_adap[0]);
		अगर (dvb->fe != शून्य) अणु
			dvb_attach(mxl5005s_attach, dvb->fe,
				&cx->i2c_adap[0],
				&hauppauge_hvr1600_tuner);
			ret = 0;
		पूर्ण
		अवरोध;
	हाल CX18_CARD_HVR_1600_S5H1411:
		dvb->fe = dvb_attach(s5h1411_attach,
				     &hcw_s5h1411_config,
				     &cx->i2c_adap[0]);
		अगर (dvb->fe != शून्य)
			dvb_attach(tda18271_attach, dvb->fe,
				   0x60, &cx->i2c_adap[0],
				   &hauppauge_tda18271_config);
		अवरोध;
	हाल CX18_CARD_LEADTEK_DVR3100H:
		dvb->fe = dvb_attach(zl10353_attach,
				     &leadtek_dvr3100h_demod,
				     &cx->i2c_adap[1]);
		अगर (dvb->fe != शून्य) अणु
			काष्ठा dvb_frontend *fe;
			काष्ठा xc2028_config cfg = अणु
				.i2c_adap = &cx->i2c_adap[1],
				.i2c_addr = 0xc2 >> 1,
				.ctrl = शून्य,
			पूर्ण;
			अटल काष्ठा xc2028_ctrl ctrl = अणु
				.fname   = XC2028_DEFAULT_FIRMWARE,
				.max_len = 64,
				.demod   = XC3028_FE_ZARLINK456,
				.type    = XC2028_AUTO,
			पूर्ण;

			fe = dvb_attach(xc2028_attach, dvb->fe, &cfg);
			अगर (fe != शून्य && fe->ops.tuner_ops.set_config != शून्य)
				fe->ops.tuner_ops.set_config(fe, &ctrl);
		पूर्ण
		अवरोध;
	हाल CX18_CARD_YUAN_MPC718:
		/*
		 * TODO
		 * Apparently, these cards also could instead have a
		 * DiBcom demod supported by one of the db7000 drivers
		 */
		dvb->fe = dvb_attach(mt352_attach,
				     &yuan_mpc718_mt352_demod,
				     &cx->i2c_adap[1]);
		अगर (dvb->fe == शून्य)
			dvb->fe = dvb_attach(zl10353_attach,
					     &yuan_mpc718_zl10353_demod,
					     &cx->i2c_adap[1]);
		अगर (dvb->fe != शून्य) अणु
			काष्ठा dvb_frontend *fe;
			काष्ठा xc2028_config cfg = अणु
				.i2c_adap = &cx->i2c_adap[1],
				.i2c_addr = 0xc2 >> 1,
				.ctrl = शून्य,
			पूर्ण;
			अटल काष्ठा xc2028_ctrl ctrl = अणु
				.fname   = XC2028_DEFAULT_FIRMWARE,
				.max_len = 64,
				.demod   = XC3028_FE_ZARLINK456,
				.type    = XC2028_AUTO,
			पूर्ण;

			fe = dvb_attach(xc2028_attach, dvb->fe, &cfg);
			अगर (fe != शून्य && fe->ops.tuner_ops.set_config != शून्य)
				fe->ops.tuner_ops.set_config(fe, &ctrl);
		पूर्ण
		अवरोध;
	हाल CX18_CARD_GOTVIEW_PCI_DVD3:
			dvb->fe = dvb_attach(zl10353_attach,
					     &gotview_dvd3_zl10353_demod,
					     &cx->i2c_adap[1]);
		अगर (dvb->fe != शून्य) अणु
			काष्ठा dvb_frontend *fe;
			काष्ठा xc2028_config cfg = अणु
				.i2c_adap = &cx->i2c_adap[1],
				.i2c_addr = 0xc2 >> 1,
				.ctrl = शून्य,
			पूर्ण;
			अटल काष्ठा xc2028_ctrl ctrl = अणु
				.fname   = XC2028_DEFAULT_FIRMWARE,
				.max_len = 64,
				.demod   = XC3028_FE_ZARLINK456,
				.type    = XC2028_AUTO,
			पूर्ण;

			fe = dvb_attach(xc2028_attach, dvb->fe, &cfg);
			अगर (fe != शून्य && fe->ops.tuner_ops.set_config != शून्य)
				fe->ops.tuner_ops.set_config(fe, &ctrl);
		पूर्ण
		अवरोध;
	शेष:
		/* No Digital Tv Support */
		अवरोध;
	पूर्ण

	अगर (dvb->fe == शून्य) अणु
		CX18_ERR("frontend initialization failed\n");
		वापस -1;
	पूर्ण

	dvb->fe->callback = cx18_reset_tuner_gpio;

	ret = dvb_रेजिस्टर_frontend(&dvb->dvb_adapter, dvb->fe);
	अगर (ret < 0) अणु
		अगर (dvb->fe->ops.release)
			dvb->fe->ops.release(dvb->fe);
		वापस ret;
	पूर्ण

	/*
	 * The firmware seems to enable the TS DMUX घड़ी
	 * under various circumstances.  However, since we know we
	 * might use it, let's just turn it on ourselves here.
	 */
	cx18_ग_लिखो_reg_expect(cx,
			      (CX18_DMUX_CLK_MASK << 16) | CX18_DMUX_CLK_MASK,
			      CX18_CLOCK_ENABLE2,
			      CX18_DMUX_CLK_MASK,
			      (CX18_DMUX_CLK_MASK << 16) | CX18_DMUX_CLK_MASK);

	वापस ret;
पूर्ण

MODULE_FIRMWARE(FWखाता);
