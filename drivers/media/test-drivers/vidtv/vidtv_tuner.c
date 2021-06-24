<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * The Virtual DVB test driver serves as a reference DVB driver and helps
 * validate the existing APIs in the media subप्रणाली. It can also aid
 * developers working on userspace applications.
 *
 * The vidtv tuner should support common TV standards such as
 * DVB-T/T2/S/S2, ISDB-T and ATSC when completed.
 *
 * Copyright (C) 2020 Daniel W. S. Almeida
 */

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/i2c.h>
#समावेश <linux/module.h>
#समावेश <linux/prपूर्णांकk.h>
#समावेश <linux/ratelimit.h>
#समावेश <linux/slab.h>
#समावेश <linux/types.h>

#समावेश <media/dvb_frontend.h>

#समावेश "vidtv_tuner.h"

काष्ठा vidtv_tuner_cnr_to_qual_s अणु
	/* attempt to use the same values as libdvbv5 */
	u32 modulation;
	u32 fec;
	u32 cnr_ok;
	u32 cnr_good;
पूर्ण;

अटल स्थिर काष्ठा vidtv_tuner_cnr_to_qual_s vidtv_tuner_c_cnr_2_qual[] = अणु
	/* from libdvbv5 source code, in milli db */
	अणु QAM_256, FEC_NONE,  34000, 38000पूर्ण,
	अणु QAM_64,  FEC_NONE,  30000, 34000पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा vidtv_tuner_cnr_to_qual_s vidtv_tuner_s_cnr_2_qual[] = अणु
	/* from libdvbv5 source code, in milli db */
	अणु QPSK, FEC_1_2,  7000, 10000पूर्ण,
	अणु QPSK, FEC_2_3,  9000, 12000पूर्ण,
	अणु QPSK, FEC_3_4, 10000, 13000पूर्ण,
	अणु QPSK, FEC_5_6, 11000, 14000पूर्ण,
	अणु QPSK, FEC_7_8, 12000, 15000पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा vidtv_tuner_cnr_to_qual_s vidtv_tuner_s2_cnr_2_qual[] = अणु
	/* from libdvbv5 source code, in milli db */
	अणु QPSK,  FEC_1_2,   9000,  12000पूर्ण,
	अणु QPSK,  FEC_2_3,  11000,  14000पूर्ण,
	अणु QPSK,  FEC_3_4,  12000,  15000पूर्ण,
	अणु QPSK,  FEC_5_6,  12000,  15000पूर्ण,
	अणु QPSK,  FEC_8_9,  13000,  16000पूर्ण,
	अणु QPSK,  FEC_9_10, 13500,  16500पूर्ण,
	अणु PSK_8, FEC_2_3,  14500,  17500पूर्ण,
	अणु PSK_8, FEC_3_4,  16000,  19000पूर्ण,
	अणु PSK_8, FEC_5_6,  17500,  20500पूर्ण,
	अणु PSK_8, FEC_8_9,  19000,  22000पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा vidtv_tuner_cnr_to_qual_s vidtv_tuner_t_cnr_2_qual[] = अणु
	/* from libdvbv5 source code, in milli db*/
	अणु   QPSK, FEC_1_2,  4100,  5900पूर्ण,
	अणु   QPSK, FEC_2_3,  6100,  9600पूर्ण,
	अणु   QPSK, FEC_3_4,  7200, 12400पूर्ण,
	अणु   QPSK, FEC_5_6,  8500, 15600पूर्ण,
	अणु   QPSK, FEC_7_8,  9200, 17500पूर्ण,
	अणु QAM_16, FEC_1_2,  9800, 11800पूर्ण,
	अणु QAM_16, FEC_2_3, 12100, 15300पूर्ण,
	अणु QAM_16, FEC_3_4, 13400, 18100पूर्ण,
	अणु QAM_16, FEC_5_6, 14800, 21300पूर्ण,
	अणु QAM_16, FEC_7_8, 15700, 23600पूर्ण,
	अणु QAM_64, FEC_1_2, 14000, 16000पूर्ण,
	अणु QAM_64, FEC_2_3, 19900, 25400पूर्ण,
	अणु QAM_64, FEC_3_4, 24900, 27900पूर्ण,
	अणु QAM_64, FEC_5_6, 21300, 23300पूर्ण,
	अणु QAM_64, FEC_7_8, 22000, 24000पूर्ण,
पूर्ण;

/**
 * काष्ठा vidtv_tuner_hardware_state - Simulate the tuner hardware status
 * @asleep: whether the tuner is asleep, i.e whether _sleep() or _suspend() was
 * called.
 * @lock_status: Whether the tuner has managed to lock on the requested
 * frequency.
 * @अगर_frequency: The tuner's पूर्णांकermediate frequency. Hardcoded क्रम the purposes
 * of simulation.
 * @tuned_frequency: The actual tuned frequency.
 * @bandwidth: The actual bandwidth.
 *
 * This काष्ठाure is meant to simulate the status of the tuner hardware, as अगर
 * we had a physical tuner hardware.
 */
काष्ठा vidtv_tuner_hardware_state अणु
	bool asleep;
	u32 lock_status;
	u32 अगर_frequency;
	u32 tuned_frequency;
	u32 bandwidth;
पूर्ण;

/**
 * काष्ठा vidtv_tuner_dev - The tuner काष्ठा
 * @fe: A poपूर्णांकer to the dvb_frontend काष्ठाure allocated by vidtv_demod
 * @hw_state: A काष्ठा to simulate the tuner's hardware state as अगर we had a
 * physical tuner hardware.
 * @config: The configuration used to start the tuner module, usually filled
 * by a bridge driver. For vidtv, this is filled by vidtv_bridge beक्रमe the
 * tuner module is probed.
 */
काष्ठा vidtv_tuner_dev अणु
	काष्ठा dvb_frontend *fe;
	काष्ठा vidtv_tuner_hardware_state hw_state;
	काष्ठा vidtv_tuner_config config;
पूर्ण;

अटल काष्ठा vidtv_tuner_dev*
vidtv_tuner_get_dev(काष्ठा dvb_frontend *fe)
अणु
	वापस i2c_get_clientdata(fe->tuner_priv);
पूर्ण

अटल पूर्णांक vidtv_tuner_check_frequency_shअगरt(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा vidtv_tuner_dev *tuner_dev = vidtv_tuner_get_dev(fe);
	काष्ठा dtv_frontend_properties *c = &fe->dtv_property_cache;
	काष्ठा vidtv_tuner_config config  = tuner_dev->config;
	u32 *valid_freqs = शून्य;
	u32 array_sz = 0;
	u32 i;
	u32 shअगरt;

	चयन (c->delivery_प्रणाली) अणु
	हाल SYS_DVBT:
	हाल SYS_DVBT2:
		valid_freqs = config.vidtv_valid_dvb_t_freqs;
		array_sz    = ARRAY_SIZE(config.vidtv_valid_dvb_t_freqs);
		अवरोध;
	हाल SYS_DVBS:
	हाल SYS_DVBS2:
		valid_freqs = config.vidtv_valid_dvb_s_freqs;
		array_sz    = ARRAY_SIZE(config.vidtv_valid_dvb_s_freqs);
		अवरोध;
	हाल SYS_DVBC_ANNEX_A:
		valid_freqs = config.vidtv_valid_dvb_c_freqs;
		array_sz    = ARRAY_SIZE(config.vidtv_valid_dvb_c_freqs);
		अवरोध;

	शेष:
		dev_warn(fe->dvb->device,
			 "%s: unsupported delivery system: %u\n",
			 __func__,
			 c->delivery_प्रणाली);

		वापस -EINVAL;
	पूर्ण

	क्रम (i = 0; i < array_sz; i++) अणु
		अगर (!valid_freqs[i])
			अवरोध;
		shअगरt = असल(c->frequency - valid_freqs[i]);

		अगर (!shअगरt)
			वापस 0;

		/*
		 * This will provide a value from 0 to 100 that would
		 * indicate how far is the tuned frequency from the
		 * right one.
		 */
		अगर (shअगरt < config.max_frequency_shअगरt_hz)
			वापस shअगरt * 100 / config.max_frequency_shअगरt_hz;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक
vidtv_tuner_get_संकेत_strength(काष्ठा dvb_frontend *fe, u16 *strength)
अणु
	काष्ठा dtv_frontend_properties *c = &fe->dtv_property_cache;
	काष्ठा vidtv_tuner_dev *tuner_dev = vidtv_tuner_get_dev(fe);
	स्थिर काष्ठा vidtv_tuner_cnr_to_qual_s *cnr2qual = शून्य;
	काष्ठा device *dev = fe->dvb->device;
	u32 array_size = 0;
	s32 shअगरt;
	u32 i;

	shअगरt = vidtv_tuner_check_frequency_shअगरt(fe);
	अगर (shअगरt < 0) अणु
		tuner_dev->hw_state.lock_status = 0;
		*strength = 0;
		वापस 0;
	पूर्ण

	चयन (c->delivery_प्रणाली) अणु
	हाल SYS_DVBT:
	हाल SYS_DVBT2:
		cnr2qual   = vidtv_tuner_t_cnr_2_qual;
		array_size = ARRAY_SIZE(vidtv_tuner_t_cnr_2_qual);
		अवरोध;

	हाल SYS_DVBS:
		cnr2qual   = vidtv_tuner_s_cnr_2_qual;
		array_size = ARRAY_SIZE(vidtv_tuner_s_cnr_2_qual);
		अवरोध;

	हाल SYS_DVBS2:
		cnr2qual   = vidtv_tuner_s2_cnr_2_qual;
		array_size = ARRAY_SIZE(vidtv_tuner_s2_cnr_2_qual);
		अवरोध;

	हाल SYS_DVBC_ANNEX_A:
		cnr2qual   = vidtv_tuner_c_cnr_2_qual;
		array_size = ARRAY_SIZE(vidtv_tuner_c_cnr_2_qual);
		अवरोध;

	शेष:
		dev_warn_ratelimited(dev,
				     "%s: unsupported delivery system: %u\n",
				     __func__,
				     c->delivery_प्रणाली);
		वापस -EINVAL;
	पूर्ण

	क्रम (i = 0; i < array_size; i++) अणु
		अगर (cnr2qual[i].modulation != c->modulation ||
		    cnr2qual[i].fec != c->fec_inner)
			जारी;

		अगर (!shअगरt) अणु
			*strength = cnr2qual[i].cnr_good;
			वापस 0;
		पूर्ण
		/*
		 * Channel tuned at wrong frequency. Simulate that the
		 * Carrier S/N ratio is not too good.
		 */

		*strength = cnr2qual[i].cnr_ok -
			    (cnr2qual[i].cnr_good - cnr2qual[i].cnr_ok);
		वापस 0;
	पूर्ण

	/*
	 * करो a linear पूर्णांकerpolation between 34dB and 10dB अगर we can't
	 * match against the table
	 */
	*strength = 34000 - 24000 * shअगरt / 100;
	वापस 0;
पूर्ण

अटल पूर्णांक vidtv_tuner_init(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा vidtv_tuner_dev *tuner_dev = vidtv_tuner_get_dev(fe);
	काष्ठा vidtv_tuner_config config  = tuner_dev->config;

	msleep_पूर्णांकerruptible(config.mock_घातer_up_delay_msec);

	tuner_dev->hw_state.asleep = false;
	tuner_dev->hw_state.अगर_frequency = 5000;

	वापस 0;
पूर्ण

अटल पूर्णांक vidtv_tuner_sleep(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा vidtv_tuner_dev *tuner_dev = vidtv_tuner_get_dev(fe);

	tuner_dev->hw_state.asleep = true;
	वापस 0;
पूर्ण

अटल पूर्णांक vidtv_tuner_suspend(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा vidtv_tuner_dev *tuner_dev = vidtv_tuner_get_dev(fe);

	tuner_dev->hw_state.asleep = true;
	वापस 0;
पूर्ण

अटल पूर्णांक vidtv_tuner_resume(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा vidtv_tuner_dev *tuner_dev = vidtv_tuner_get_dev(fe);

	tuner_dev->hw_state.asleep = false;
	वापस 0;
पूर्ण

अटल पूर्णांक vidtv_tuner_set_params(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा vidtv_tuner_dev *tuner_dev = vidtv_tuner_get_dev(fe);
	काष्ठा vidtv_tuner_config config  = tuner_dev->config;
	काष्ठा dtv_frontend_properties *c = &fe->dtv_property_cache;
	s32 shअगरt;

	u32 min_freq = fe->ops.tuner_ops.info.frequency_min_hz;
	u32 max_freq = fe->ops.tuner_ops.info.frequency_max_hz;
	u32 min_bw = fe->ops.tuner_ops.info.bandwidth_min;
	u32 max_bw = fe->ops.tuner_ops.info.bandwidth_max;

	अगर (c->frequency < min_freq  || c->frequency > max_freq  ||
	    c->bandwidth_hz < min_bw || c->bandwidth_hz > max_bw) अणु
		tuner_dev->hw_state.lock_status = 0;
		वापस -EINVAL;
	पूर्ण

	tuner_dev->hw_state.tuned_frequency = c->frequency;
	tuner_dev->hw_state.bandwidth = c->bandwidth_hz;
	tuner_dev->hw_state.lock_status = TUNER_STATUS_LOCKED;

	msleep_पूर्णांकerruptible(config.mock_tune_delay_msec);

	shअगरt = vidtv_tuner_check_frequency_shअगरt(fe);
	अगर (shअगरt < 0) अणु
		tuner_dev->hw_state.lock_status = 0;
		वापस shअगरt;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक vidtv_tuner_set_config(काष्ठा dvb_frontend *fe,
				  व्योम *priv_cfg)
अणु
	काष्ठा vidtv_tuner_dev *tuner_dev = vidtv_tuner_get_dev(fe);

	स_नकल(&tuner_dev->config, priv_cfg, माप(tuner_dev->config));

	वापस 0;
पूर्ण

अटल पूर्णांक vidtv_tuner_get_frequency(काष्ठा dvb_frontend *fe,
				     u32 *frequency)
अणु
	काष्ठा vidtv_tuner_dev *tuner_dev = vidtv_tuner_get_dev(fe);

	*frequency = tuner_dev->hw_state.tuned_frequency;

	वापस 0;
पूर्ण

अटल पूर्णांक vidtv_tuner_get_bandwidth(काष्ठा dvb_frontend *fe,
				     u32 *bandwidth)
अणु
	काष्ठा vidtv_tuner_dev *tuner_dev = vidtv_tuner_get_dev(fe);

	*bandwidth = tuner_dev->hw_state.bandwidth;

	वापस 0;
पूर्ण

अटल पूर्णांक vidtv_tuner_get_अगर_frequency(काष्ठा dvb_frontend *fe,
					u32 *frequency)
अणु
	काष्ठा vidtv_tuner_dev *tuner_dev = vidtv_tuner_get_dev(fe);

	*frequency = tuner_dev->hw_state.अगर_frequency;

	वापस 0;
पूर्ण

अटल पूर्णांक vidtv_tuner_get_status(काष्ठा dvb_frontend *fe, u32 *status)
अणु
	काष्ठा vidtv_tuner_dev *tuner_dev = vidtv_tuner_get_dev(fe);

	*status = tuner_dev->hw_state.lock_status;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dvb_tuner_ops vidtv_tuner_ops = अणु
	.init             = vidtv_tuner_init,
	.sleep            = vidtv_tuner_sleep,
	.suspend          = vidtv_tuner_suspend,
	.resume           = vidtv_tuner_resume,
	.set_params       = vidtv_tuner_set_params,
	.set_config       = vidtv_tuner_set_config,
	.get_bandwidth    = vidtv_tuner_get_bandwidth,
	.get_frequency    = vidtv_tuner_get_frequency,
	.get_अगर_frequency = vidtv_tuner_get_अगर_frequency,
	.get_status       = vidtv_tuner_get_status,
	.get_rf_strength  = vidtv_tuner_get_संकेत_strength
पूर्ण;

अटल स्थिर काष्ठा i2c_device_id vidtv_tuner_i2c_id_table[] = अणु
	अणु"dvb_vidtv_tuner", 0पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, vidtv_tuner_i2c_id_table);

अटल पूर्णांक vidtv_tuner_i2c_probe(काष्ठा i2c_client *client,
				 स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा vidtv_tuner_config *config = client->dev.platक्रमm_data;
	काष्ठा dvb_frontend *fe           = config->fe;
	काष्ठा vidtv_tuner_dev *tuner_dev = शून्य;

	tuner_dev = kzalloc(माप(*tuner_dev), GFP_KERNEL);
	अगर (!tuner_dev)
		वापस -ENOMEM;

	tuner_dev->fe = config->fe;
	i2c_set_clientdata(client, tuner_dev);

	स_नकल(&fe->ops.tuner_ops,
	       &vidtv_tuner_ops,
	       माप(काष्ठा dvb_tuner_ops));

	स_नकल(&tuner_dev->config, config, माप(tuner_dev->config));
	fe->tuner_priv = client;

	वापस 0;
पूर्ण

अटल पूर्णांक vidtv_tuner_i2c_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा vidtv_tuner_dev *tuner_dev = i2c_get_clientdata(client);

	kमुक्त(tuner_dev);

	वापस 0;
पूर्ण

अटल काष्ठा i2c_driver vidtv_tuner_i2c_driver = अणु
	.driver = अणु
		.name                = "dvb_vidtv_tuner",
		.suppress_bind_attrs = true,
	पूर्ण,
	.probe    = vidtv_tuner_i2c_probe,
	.हटाओ   = vidtv_tuner_i2c_हटाओ,
	.id_table = vidtv_tuner_i2c_id_table,
पूर्ण;
module_i2c_driver(vidtv_tuner_i2c_driver);

MODULE_DESCRIPTION("Virtual DVB Tuner");
MODULE_AUTHOR("Daniel W. S. Almeida");
MODULE_LICENSE("GPL");
