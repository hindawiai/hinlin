<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * The Virtual DTV test driver serves as a reference DVB driver and helps
 * validate the existing APIs in the media subप्रणाली. It can also aid
 * developers working on userspace applications.
 *
 * When this module is loaded, it will attempt to modprobe 'dvb_vidtv_tuner'
 * and 'dvb_vidtv_demod'.
 *
 * Copyright (C) 2020 Daniel W. S. Almeida
 */

#समावेश <linux/dev_prपूर्णांकk.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/mutex.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/समय.स>
#समावेश <linux/types.h>
#समावेश <linux/workqueue.h>
#समावेश <media/dvbdev.h>
#समावेश <media/media-device.h>

#समावेश "vidtv_bridge.h"
#समावेश "vidtv_common.h"
#समावेश "vidtv_demod.h"
#समावेश "vidtv_mux.h"
#समावेश "vidtv_ts.h"
#समावेश "vidtv_tuner.h"

#घोषणा MUX_BUF_MIN_SZ 90164
#घोषणा MUX_BUF_MAX_SZ (MUX_BUF_MIN_SZ * 10)
#घोषणा TUNER_DEFAULT_ADDR 0x68
#घोषणा DEMOD_DEFAULT_ADDR 0x60
#घोषणा VIDTV_DEFAULT_NETWORK_ID 0xff44
#घोषणा VIDTV_DEFAULT_NETWORK_NAME "LinuxTV.org"
#घोषणा VIDTV_DEFAULT_TS_ID 0x4081

/*
 * The LNBf fake parameters here are the ranges used by an
 * Universal (extended) European LNBf, which is likely the most common LNBf
 * found on Satellite digital TV प्रणाली nowadays.
 */
#घोषणा LNB_CUT_FREQUENCY	11700000	/* high IF frequency */
#घोषणा LNB_LOW_FREQ		9750000		/* low IF frequency */
#घोषणा LNB_HIGH_FREQ		10600000	/* transition frequency */

अटल अचिन्हित पूर्णांक drop_tslock_prob_on_low_snr;
module_param(drop_tslock_prob_on_low_snr, uपूर्णांक, 0);
MODULE_PARM_DESC(drop_tslock_prob_on_low_snr,
		 "Probability of losing the TS lock if the signal quality is bad");

अटल अचिन्हित पूर्णांक recover_tslock_prob_on_good_snr;
module_param(recover_tslock_prob_on_good_snr, uपूर्णांक, 0);
MODULE_PARM_DESC(recover_tslock_prob_on_good_snr,
		 "Probability recovering the TS lock when the signal improves");

अटल अचिन्हित पूर्णांक mock_घातer_up_delay_msec;
module_param(mock_घातer_up_delay_msec, uपूर्णांक, 0);
MODULE_PARM_DESC(mock_घातer_up_delay_msec, "Simulate a power up delay");

अटल अचिन्हित पूर्णांक mock_tune_delay_msec;
module_param(mock_tune_delay_msec, uपूर्णांक, 0);
MODULE_PARM_DESC(mock_tune_delay_msec, "Simulate a tune delay");

अटल अचिन्हित पूर्णांक vidtv_valid_dvb_t_freqs[NUM_VALID_TUNER_FREQS] = अणु
	474000000
पूर्ण;

module_param_array(vidtv_valid_dvb_t_freqs, uपूर्णांक, शून्य, 0);
MODULE_PARM_DESC(vidtv_valid_dvb_t_freqs,
		 "Valid DVB-T frequencies to simulate, in Hz");

अटल अचिन्हित पूर्णांक vidtv_valid_dvb_c_freqs[NUM_VALID_TUNER_FREQS] = अणु
	474000000
पूर्ण;

module_param_array(vidtv_valid_dvb_c_freqs, uपूर्णांक, शून्य, 0);
MODULE_PARM_DESC(vidtv_valid_dvb_c_freqs,
		 "Valid DVB-C frequencies to simulate, in Hz");

अटल अचिन्हित पूर्णांक vidtv_valid_dvb_s_freqs[NUM_VALID_TUNER_FREQS] = अणु
	11362000
पूर्ण;
module_param_array(vidtv_valid_dvb_s_freqs, uपूर्णांक, शून्य, 0);
MODULE_PARM_DESC(vidtv_valid_dvb_s_freqs,
		 "Valid DVB-S/S2 frequencies to simulate at Ku-Band, in kHz");

अटल अचिन्हित पूर्णांक max_frequency_shअगरt_hz;
module_param(max_frequency_shअगरt_hz, uपूर्णांक, 0);
MODULE_PARM_DESC(max_frequency_shअगरt_hz,
		 "Maximum shift in HZ allowed when tuning in a channel");

DVB_DEFINE_MOD_OPT_ADAPTER_NR(adapter_nums);

/*
 * Influences the संकेत acquisition समय. See ISO/IEC 13818-1 : 2000. p. 113.
 */
अटल अचिन्हित पूर्णांक si_period_msec = 40;
module_param(si_period_msec, uपूर्णांक, 0);
MODULE_PARM_DESC(si_period_msec, "How often to send SI packets. Default: 40ms");

अटल अचिन्हित पूर्णांक pcr_period_msec = 40;
module_param(pcr_period_msec, uपूर्णांक, 0);
MODULE_PARM_DESC(pcr_period_msec,
		 "How often to send PCR packets. Default: 40ms");

अटल अचिन्हित पूर्णांक mux_rate_kbytes_sec = 4096;
module_param(mux_rate_kbytes_sec, uपूर्णांक, 0);
MODULE_PARM_DESC(mux_rate_kbytes_sec, "Mux rate: will pad stream if below");

अटल अचिन्हित पूर्णांक pcr_pid = 0x200;
module_param(pcr_pid, uपूर्णांक, 0);
MODULE_PARM_DESC(pcr_pid, "PCR PID for all channels: defaults to 0x200");

अटल अचिन्हित पूर्णांक mux_buf_sz_pkts;
module_param(mux_buf_sz_pkts, uपूर्णांक, 0);
MODULE_PARM_DESC(mux_buf_sz_pkts,
		 "Size for the internal mux buffer in multiples of 188 bytes");

अटल u32 vidtv_bridge_mux_buf_sz_क्रम_mux_rate(व्योम)
अणु
	u32 max_elapsed_समय_msecs =  VIDTV_MAX_SLEEP_USECS / USEC_PER_MSEC;
	u32 mux_buf_sz = mux_buf_sz_pkts * TS_PACKET_LEN;
	u32 nbytes_expected;

	nbytes_expected = mux_rate_kbytes_sec;
	nbytes_expected *= max_elapsed_समय_msecs;

	mux_buf_sz = roundup(nbytes_expected, TS_PACKET_LEN);
	mux_buf_sz += mux_buf_sz / 10;

	अगर (mux_buf_sz < MUX_BUF_MIN_SZ)
		mux_buf_sz = MUX_BUF_MIN_SZ;

	अगर (mux_buf_sz > MUX_BUF_MAX_SZ)
		mux_buf_sz = MUX_BUF_MAX_SZ;

	वापस mux_buf_sz;
पूर्ण

अटल bool vidtv_bridge_check_demod_lock(काष्ठा vidtv_dvb *dvb, u32 n)
अणु
	क्रमागत fe_status status;

	dvb->fe[n]->ops.पढ़ो_status(dvb->fe[n], &status);

	वापस status == (FE_HAS_SIGNAL  |
			  FE_HAS_CARRIER |
			  FE_HAS_VITERBI |
			  FE_HAS_SYNC    |
			  FE_HAS_LOCK);
पूर्ण

/*
 * called on a separate thपढ़ो by the mux when new packets become available
 */
अटल व्योम vidtv_bridge_on_new_pkts_avail(व्योम *priv, u8 *buf, u32 npkts)
अणु
	काष्ठा vidtv_dvb *dvb = priv;

	/* drop packets अगर we lose the lock */
	अगर (vidtv_bridge_check_demod_lock(dvb, 0))
		dvb_dmx_swfilter_packets(&dvb->demux, buf, npkts);
पूर्ण

अटल पूर्णांक vidtv_start_streaming(काष्ठा vidtv_dvb *dvb)
अणु
	काष्ठा vidtv_mux_init_args mux_args = अणु
		.mux_rate_kbytes_sec         = mux_rate_kbytes_sec,
		.on_new_packets_available_cb = vidtv_bridge_on_new_pkts_avail,
		.pcr_period_usecs            = pcr_period_msec * USEC_PER_MSEC,
		.si_period_usecs             = si_period_msec * USEC_PER_MSEC,
		.pcr_pid                     = pcr_pid,
		.transport_stream_id         = VIDTV_DEFAULT_TS_ID,
		.network_id                  = VIDTV_DEFAULT_NETWORK_ID,
		.network_name                = VIDTV_DEFAULT_NETWORK_NAME,
		.priv                        = dvb,
	पूर्ण;
	काष्ठा device *dev = &dvb->pdev->dev;
	u32 mux_buf_sz;

	अगर (dvb->streaming) अणु
		dev_warn_ratelimited(dev, "Already streaming. Skipping.\n");
		वापस 0;
	पूर्ण

	अगर (mux_buf_sz_pkts)
		mux_buf_sz = mux_buf_sz_pkts;
	अन्यथा
		mux_buf_sz = vidtv_bridge_mux_buf_sz_क्रम_mux_rate();

	mux_args.mux_buf_sz  = mux_buf_sz;

	dvb->streaming = true;
	dvb->mux = vidtv_mux_init(dvb->fe[0], dev, &mux_args);
	अगर (!dvb->mux)
		वापस -ENOMEM;
	vidtv_mux_start_thपढ़ो(dvb->mux);

	dev_dbg_ratelimited(dev, "Started streaming\n");
	वापस 0;
पूर्ण

अटल पूर्णांक vidtv_stop_streaming(काष्ठा vidtv_dvb *dvb)
अणु
	काष्ठा device *dev = &dvb->pdev->dev;

	dvb->streaming = false;
	vidtv_mux_stop_thपढ़ो(dvb->mux);
	vidtv_mux_destroy(dvb->mux);
	dvb->mux = शून्य;

	dev_dbg_ratelimited(dev, "Stopped streaming\n");
	वापस 0;
पूर्ण

अटल पूर्णांक vidtv_start_feed(काष्ठा dvb_demux_feed *feed)
अणु
	काष्ठा dvb_demux *demux = feed->demux;
	काष्ठा vidtv_dvb *dvb   = demux->priv;
	पूर्णांक ret;
	पूर्णांक rc;

	अगर (!demux->dmx.frontend)
		वापस -EINVAL;

	mutex_lock(&dvb->feed_lock);

	dvb->nfeeds++;
	rc = dvb->nfeeds;

	अगर (dvb->nfeeds == 1) अणु
		ret = vidtv_start_streaming(dvb);
		अगर (ret < 0)
			rc = ret;
	पूर्ण

	mutex_unlock(&dvb->feed_lock);
	वापस rc;
पूर्ण

अटल पूर्णांक vidtv_stop_feed(काष्ठा dvb_demux_feed *feed)
अणु
	काष्ठा dvb_demux *demux = feed->demux;
	काष्ठा vidtv_dvb *dvb   = demux->priv;
	पूर्णांक err = 0;

	mutex_lock(&dvb->feed_lock);
	dvb->nfeeds--;

	अगर (!dvb->nfeeds)
		err = vidtv_stop_streaming(dvb);

	mutex_unlock(&dvb->feed_lock);
	वापस err;
पूर्ण

अटल काष्ठा dvb_frontend *vidtv_get_frontend_ptr(काष्ठा i2c_client *c)
अणु
	काष्ठा vidtv_demod_state *state = i2c_get_clientdata(c);

	/* the demod will set this when its probe function runs */
	वापस &state->frontend;
पूर्ण

अटल पूर्णांक vidtv_master_xfer(काष्ठा i2c_adapter *i2c_adap,
			     काष्ठा i2c_msg msgs[],
			     पूर्णांक num)
अणु
	/*
	 * Right now, this भव driver करोesn't really send or receive
	 * messages from I2C. A real driver will require an implementation
	 * here.
	 */
	वापस 0;
पूर्ण

अटल u32 vidtv_i2c_func(काष्ठा i2c_adapter *adapter)
अणु
	वापस I2C_FUNC_I2C;
पूर्ण

अटल स्थिर काष्ठा i2c_algorithm vidtv_i2c_algorithm = अणु
	.master_xfer   = vidtv_master_xfer,
	.functionality = vidtv_i2c_func,
पूर्ण;

अटल पूर्णांक vidtv_bridge_i2c_रेजिस्टर_adap(काष्ठा vidtv_dvb *dvb)
अणु
	काष्ठा i2c_adapter *i2c_adapter = &dvb->i2c_adapter;

	strscpy(i2c_adapter->name, "vidtv_i2c", माप(i2c_adapter->name));
	i2c_adapter->owner      = THIS_MODULE;
	i2c_adapter->algo       = &vidtv_i2c_algorithm;
	i2c_adapter->algo_data  = शून्य;
	i2c_adapter->समयout    = 500;
	i2c_adapter->retries    = 3;
	i2c_adapter->dev.parent = &dvb->pdev->dev;

	i2c_set_adapdata(i2c_adapter, dvb);
	वापस i2c_add_adapter(&dvb->i2c_adapter);
पूर्ण

अटल पूर्णांक vidtv_bridge_रेजिस्टर_adap(काष्ठा vidtv_dvb *dvb)
अणु
	पूर्णांक ret = 0;

	ret = dvb_रेजिस्टर_adapter(&dvb->adapter,
				   KBUILD_MODNAME,
				   THIS_MODULE,
				   &dvb->i2c_adapter.dev,
				   adapter_nums);

	वापस ret;
पूर्ण

अटल पूर्णांक vidtv_bridge_dmx_init(काष्ठा vidtv_dvb *dvb)
अणु
	dvb->demux.dmx.capabilities = DMX_TS_FILTERING |
				      DMX_SECTION_FILTERING;

	dvb->demux.priv       = dvb;
	dvb->demux.filternum  = 256;
	dvb->demux.feednum    = 256;
	dvb->demux.start_feed = vidtv_start_feed;
	dvb->demux.stop_feed  = vidtv_stop_feed;

	वापस dvb_dmx_init(&dvb->demux);
पूर्ण

अटल पूर्णांक vidtv_bridge_dmxdev_init(काष्ठा vidtv_dvb *dvb)
अणु
	dvb->dmx_dev.filternum    = 256;
	dvb->dmx_dev.demux        = &dvb->demux.dmx;
	dvb->dmx_dev.capabilities = 0;

	वापस dvb_dmxdev_init(&dvb->dmx_dev, &dvb->adapter);
पूर्ण

अटल पूर्णांक vidtv_bridge_probe_demod(काष्ठा vidtv_dvb *dvb, u32 n)
अणु
	काष्ठा vidtv_demod_config cfg = अणु
		.drop_tslock_prob_on_low_snr     = drop_tslock_prob_on_low_snr,
		.recover_tslock_prob_on_good_snr = recover_tslock_prob_on_good_snr,
	पूर्ण;
	dvb->i2c_client_demod[n] = dvb_module_probe("dvb_vidtv_demod",
						    शून्य,
						    &dvb->i2c_adapter,
						    DEMOD_DEFAULT_ADDR,
						    &cfg);

	/* driver will not work anyways so bail out */
	अगर (!dvb->i2c_client_demod[n])
		वापस -ENODEV;

	/* retrieve a ptr to the frontend state */
	dvb->fe[n] = vidtv_get_frontend_ptr(dvb->i2c_client_demod[n]);

	वापस 0;
पूर्ण

अटल पूर्णांक vidtv_bridge_probe_tuner(काष्ठा vidtv_dvb *dvb, u32 n)
अणु
	काष्ठा vidtv_tuner_config cfg = अणु
		.fe                       = dvb->fe[n],
		.mock_घातer_up_delay_msec = mock_घातer_up_delay_msec,
		.mock_tune_delay_msec     = mock_tune_delay_msec,
	पूर्ण;
	u32 freq;
	पूर्णांक i;

	/* TODO: check अगर the frequencies are at a valid range */

	स_नकल(cfg.vidtv_valid_dvb_t_freqs,
	       vidtv_valid_dvb_t_freqs,
	       माप(vidtv_valid_dvb_t_freqs));

	स_नकल(cfg.vidtv_valid_dvb_c_freqs,
	       vidtv_valid_dvb_c_freqs,
	       माप(vidtv_valid_dvb_c_freqs));

	/*
	 * Convert Satellite frequencies from Ku-band in kHZ पूर्णांकo S-band
	 * frequencies in Hz.
	 */
	क्रम (i = 0; i < ARRAY_SIZE(vidtv_valid_dvb_s_freqs); i++) अणु
		freq = vidtv_valid_dvb_s_freqs[i];
		अगर (freq) अणु
			अगर (freq < LNB_CUT_FREQUENCY)
				freq = असल(freq - LNB_LOW_FREQ);
			अन्यथा
				freq = असल(freq - LNB_HIGH_FREQ);
		पूर्ण
		cfg.vidtv_valid_dvb_s_freqs[i] = freq;
	पूर्ण

	cfg.max_frequency_shअगरt_hz = max_frequency_shअगरt_hz;

	dvb->i2c_client_tuner[n] = dvb_module_probe("dvb_vidtv_tuner",
						    शून्य,
						    &dvb->i2c_adapter,
						    TUNER_DEFAULT_ADDR,
						    &cfg);

	वापस (dvb->i2c_client_tuner[n]) ? 0 : -ENODEV;
पूर्ण

अटल पूर्णांक vidtv_bridge_dvb_init(काष्ठा vidtv_dvb *dvb)
अणु
	पूर्णांक ret, i, j;

	ret = vidtv_bridge_i2c_रेजिस्टर_adap(dvb);
	अगर (ret < 0)
		जाओ fail_i2c;

	ret = vidtv_bridge_रेजिस्टर_adap(dvb);
	अगर (ret < 0)
		जाओ fail_adapter;
	dvb_रेजिस्टर_media_controller(&dvb->adapter, &dvb->mdev);

	क्रम (i = 0; i < NUM_FE; ++i) अणु
		ret = vidtv_bridge_probe_demod(dvb, i);
		अगर (ret < 0)
			जाओ fail_demod_probe;

		ret = vidtv_bridge_probe_tuner(dvb, i);
		अगर (ret < 0)
			जाओ fail_tuner_probe;

		ret = dvb_रेजिस्टर_frontend(&dvb->adapter, dvb->fe[i]);
		अगर (ret < 0)
			जाओ fail_fe;
	पूर्ण

	ret = vidtv_bridge_dmx_init(dvb);
	अगर (ret < 0)
		जाओ fail_dmx;

	ret = vidtv_bridge_dmxdev_init(dvb);
	अगर (ret < 0)
		जाओ fail_dmx_dev;

	क्रम (j = 0; j < NUM_FE; ++j) अणु
		ret = dvb->demux.dmx.connect_frontend(&dvb->demux.dmx,
						      &dvb->dmx_fe[j]);
		अगर (ret < 0)
			जाओ fail_dmx_conn;

		/*
		 * The source of the demux is a frontend connected
		 * to the demux.
		 */
		dvb->dmx_fe[j].source = DMX_FRONTEND_0;
	पूर्ण

	वापस ret;

fail_dmx_conn:
	क्रम (j = j - 1; j >= 0; --j)
		dvb->demux.dmx.हटाओ_frontend(&dvb->demux.dmx,
					       &dvb->dmx_fe[j]);
fail_dmx_dev:
	dvb_dmxdev_release(&dvb->dmx_dev);
fail_dmx:
	dvb_dmx_release(&dvb->demux);
fail_fe:
	क्रम (j = i; j >= 0; --j)
		dvb_unरेजिस्टर_frontend(dvb->fe[j]);
fail_tuner_probe:
	क्रम (j = i; j >= 0; --j)
		अगर (dvb->i2c_client_tuner[j])
			dvb_module_release(dvb->i2c_client_tuner[j]);

fail_demod_probe:
	क्रम (j = i; j >= 0; --j)
		अगर (dvb->i2c_client_demod[j])
			dvb_module_release(dvb->i2c_client_demod[j]);

fail_adapter:
	dvb_unरेजिस्टर_adapter(&dvb->adapter);

fail_i2c:
	i2c_del_adapter(&dvb->i2c_adapter);

	वापस ret;
पूर्ण

अटल पूर्णांक vidtv_bridge_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा vidtv_dvb *dvb;
	पूर्णांक ret;

	dvb = kzalloc(माप(*dvb), GFP_KERNEL);
	अगर (!dvb)
		वापस -ENOMEM;

	dvb->pdev = pdev;

#अगर_घोषित CONFIG_MEDIA_CONTROLLER_DVB
	dvb->mdev.dev = &pdev->dev;

	strscpy(dvb->mdev.model, "vidtv", माप(dvb->mdev.model));
	strscpy(dvb->mdev.bus_info, "platform:vidtv", माप(dvb->mdev.bus_info));

	media_device_init(&dvb->mdev);
#पूर्ण_अगर

	ret = vidtv_bridge_dvb_init(dvb);
	अगर (ret < 0)
		जाओ err_dvb;

	mutex_init(&dvb->feed_lock);

	platक्रमm_set_drvdata(pdev, dvb);

#अगर_घोषित CONFIG_MEDIA_CONTROLLER_DVB
	ret = media_device_रेजिस्टर(&dvb->mdev);
	अगर (ret) अणु
		dev_err(dvb->mdev.dev,
			"media device register failed (err=%d)\n", ret);
		जाओ err_media_device_रेजिस्टर;
	पूर्ण
#पूर्ण_अगर /* CONFIG_MEDIA_CONTROLLER_DVB */

	dev_info(&pdev->dev, "Successfully initialized vidtv!\n");
	वापस ret;

#अगर_घोषित CONFIG_MEDIA_CONTROLLER_DVB
err_media_device_रेजिस्टर:
	media_device_cleanup(&dvb->mdev);
#पूर्ण_अगर /* CONFIG_MEDIA_CONTROLLER_DVB */
err_dvb:
	kमुक्त(dvb);
	वापस ret;
पूर्ण

अटल पूर्णांक vidtv_bridge_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा vidtv_dvb *dvb;
	u32 i;

	dvb = platक्रमm_get_drvdata(pdev);

#अगर_घोषित CONFIG_MEDIA_CONTROLLER_DVB
	media_device_unरेजिस्टर(&dvb->mdev);
	media_device_cleanup(&dvb->mdev);
#पूर्ण_अगर /* CONFIG_MEDIA_CONTROLLER_DVB */

	mutex_destroy(&dvb->feed_lock);

	क्रम (i = 0; i < NUM_FE; ++i) अणु
		dvb_unरेजिस्टर_frontend(dvb->fe[i]);
		dvb_module_release(dvb->i2c_client_tuner[i]);
		dvb_module_release(dvb->i2c_client_demod[i]);
	पूर्ण

	dvb_dmxdev_release(&dvb->dmx_dev);
	dvb_dmx_release(&dvb->demux);
	dvb_unरेजिस्टर_adapter(&dvb->adapter);
	dev_info(&pdev->dev, "Successfully removed vidtv\n");

	वापस 0;
पूर्ण

अटल व्योम vidtv_bridge_dev_release(काष्ठा device *dev)
अणु
पूर्ण

अटल काष्ठा platक्रमm_device vidtv_bridge_dev = अणु
	.name		= VIDTV_PDEV_NAME,
	.dev.release	= vidtv_bridge_dev_release,
पूर्ण;

अटल काष्ठा platक्रमm_driver vidtv_bridge_driver = अणु
	.driver = अणु
		.name = VIDTV_PDEV_NAME,
	पूर्ण,
	.probe    = vidtv_bridge_probe,
	.हटाओ   = vidtv_bridge_हटाओ,
पूर्ण;

अटल व्योम __निकास vidtv_bridge_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&vidtv_bridge_driver);
	platक्रमm_device_unरेजिस्टर(&vidtv_bridge_dev);
पूर्ण

अटल पूर्णांक __init vidtv_bridge_init(व्योम)
अणु
	पूर्णांक ret;

	ret = platक्रमm_device_रेजिस्टर(&vidtv_bridge_dev);
	अगर (ret)
		वापस ret;

	ret = platक्रमm_driver_रेजिस्टर(&vidtv_bridge_driver);
	अगर (ret)
		platक्रमm_device_unरेजिस्टर(&vidtv_bridge_dev);

	वापस ret;
पूर्ण

module_init(vidtv_bridge_init);
module_निकास(vidtv_bridge_निकास);

MODULE_DESCRIPTION("Virtual Digital TV Test Driver");
MODULE_AUTHOR("Daniel W. S. Almeida");
MODULE_LICENSE("GPL");
MODULE_ALIAS("vidtv");
MODULE_ALIAS("dvb_vidtv");
