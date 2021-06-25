<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Earthsoft PT3 driver
 *
 * Copyright (C) 2014 Akihiro Tsukada <tskd08@gmail.com>
 */

#समावेश <linux/मुक्तzer.h>
#समावेश <linux/kernel.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/mutex.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/माला.स>
#समावेश <linux/sched/संकेत.स>

#समावेश <media/dmxdev.h>
#समावेश <media/dvbdev.h>
#समावेश <media/dvb_demux.h>
#समावेश <media/dvb_frontend.h>

#समावेश "pt3.h"

DVB_DEFINE_MOD_OPT_ADAPTER_NR(adapter_nr);

अटल bool one_adapter;
module_param(one_adapter, bool, 0444);
MODULE_PARM_DESC(one_adapter, "Place FE's together under one adapter.");

अटल पूर्णांक num_bufs = 4;
module_param(num_bufs, पूर्णांक, 0444);
MODULE_PARM_DESC(num_bufs, "Number of DMA buffer (188KiB) per FE.");


अटल स्थिर काष्ठा i2c_algorithm pt3_i2c_algo = अणु
	.master_xfer   = &pt3_i2c_master_xfer,
	.functionality = &pt3_i2c_functionality,
पूर्ण;

अटल स्थिर काष्ठा pt3_adap_config adap_conf[PT3_NUM_FE] = अणु
	अणु
		.demod_info = अणु
			I2C_BOARD_INFO(TC90522_I2C_DEV_SAT, 0x11),
		पूर्ण,
		.tuner_info = अणु
			I2C_BOARD_INFO("qm1d1c0042", 0x63),
		पूर्ण,
		.tuner_cfg.qm1d1c0042 = अणु
			.lpf = 1,
		पूर्ण,
		.init_freq = 1049480 - 300,
	पूर्ण,
	अणु
		.demod_info = अणु
			I2C_BOARD_INFO(TC90522_I2C_DEV_TER, 0x10),
		पूर्ण,
		.tuner_info = अणु
			I2C_BOARD_INFO("mxl301rf", 0x62),
		पूर्ण,
		.init_freq = 515142857,
	पूर्ण,
	अणु
		.demod_info = अणु
			I2C_BOARD_INFO(TC90522_I2C_DEV_SAT, 0x13),
		पूर्ण,
		.tuner_info = अणु
			I2C_BOARD_INFO("qm1d1c0042", 0x60),
		पूर्ण,
		.tuner_cfg.qm1d1c0042 = अणु
			.lpf = 1,
		पूर्ण,
		.init_freq = 1049480 + 300,
	पूर्ण,
	अणु
		.demod_info = अणु
			I2C_BOARD_INFO(TC90522_I2C_DEV_TER, 0x12),
		पूर्ण,
		.tuner_info = अणु
			I2C_BOARD_INFO("mxl301rf", 0x61),
		पूर्ण,
		.init_freq = 521142857,
	पूर्ण,
पूर्ण;


काष्ठा reg_val अणु
	u8 reg;
	u8 val;
पूर्ण;

अटल पूर्णांक
pt3_demod_ग_लिखो(काष्ठा pt3_adapter *adap, स्थिर काष्ठा reg_val *data, पूर्णांक num)
अणु
	काष्ठा i2c_msg msg;
	पूर्णांक i, ret;

	ret = 0;
	msg.addr = adap->i2c_demod->addr;
	msg.flags = 0;
	msg.len = 2;
	क्रम (i = 0; i < num; i++) अणु
		msg.buf = (u8 *)&data[i];
		ret = i2c_transfer(adap->i2c_demod->adapter, &msg, 1);
		अगर (ret == 0)
			ret = -EREMOTE;
		अगर (ret < 0)
			वापस ret;
	पूर्ण
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम pt3_lnb_ctrl(काष्ठा pt3_board *pt3, bool on)
अणु
	ioग_लिखो32((on ? 0x0f : 0x0c), pt3->regs[0] + REG_SYSTEM_W);
पूर्ण

अटल अंतरभूत काष्ठा pt3_adapter *pt3_find_adapter(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा pt3_board *pt3;
	पूर्णांक i;

	अगर (one_adapter) अणु
		pt3 = fe->dvb->priv;
		क्रम (i = 0; i < PT3_NUM_FE; i++)
			अगर (pt3->adaps[i]->fe == fe)
				वापस pt3->adaps[i];
	पूर्ण
	वापस container_of(fe->dvb, काष्ठा pt3_adapter, dvb_adap);
पूर्ण

/*
 * all 4 tuners in PT3 are packaged in a can module (Sharp VA4M6JC2103).
 * it seems that they share the घातer lines and Amp घातer line and
 * adaps[3] controls those घातers.
 */
अटल पूर्णांक
pt3_set_tuner_घातer(काष्ठा pt3_board *pt3, bool tuner_on, bool amp_on)
अणु
	काष्ठा reg_val rv = अणु 0x1e, 0x99 पूर्ण;

	अगर (tuner_on)
		rv.val |= 0x40;
	अगर (amp_on)
		rv.val |= 0x04;
	वापस pt3_demod_ग_लिखो(pt3->adaps[PT3_NUM_FE - 1], &rv, 1);
पूर्ण

अटल पूर्णांक pt3_set_lna(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा pt3_adapter *adap;
	काष्ठा pt3_board *pt3;
	u32 val;
	पूर्णांक ret;

	/* LNA is shared btw. 2 TERR-tuners */

	adap = pt3_find_adapter(fe);
	val = fe->dtv_property_cache.lna;
	अगर (val == LNA_AUTO || val == adap->cur_lna)
		वापस 0;

	pt3 = adap->dvb_adap.priv;
	अगर (mutex_lock_पूर्णांकerruptible(&pt3->lock))
		वापस -ERESTARTSYS;
	अगर (val)
		pt3->lna_on_cnt++;
	अन्यथा
		pt3->lna_on_cnt--;

	अगर (val && pt3->lna_on_cnt <= 1) अणु
		pt3->lna_on_cnt = 1;
		ret = pt3_set_tuner_घातer(pt3, true, true);
	पूर्ण अन्यथा अगर (!val && pt3->lna_on_cnt <= 0) अणु
		pt3->lna_on_cnt = 0;
		ret = pt3_set_tuner_घातer(pt3, true, false);
	पूर्ण अन्यथा
		ret = 0;
	mutex_unlock(&pt3->lock);
	adap->cur_lna = (val != 0);
	वापस ret;
पूर्ण

अटल पूर्णांक pt3_set_voltage(काष्ठा dvb_frontend *fe, क्रमागत fe_sec_voltage volt)
अणु
	काष्ठा pt3_adapter *adap;
	काष्ठा pt3_board *pt3;
	bool on;

	/* LNB घातer is shared btw. 2 SAT-tuners */

	adap = pt3_find_adapter(fe);
	on = (volt != SEC_VOLTAGE_OFF);
	अगर (on == adap->cur_lnb)
		वापस 0;
	adap->cur_lnb = on;
	pt3 = adap->dvb_adap.priv;
	अगर (mutex_lock_पूर्णांकerruptible(&pt3->lock))
		वापस -ERESTARTSYS;
	अगर (on)
		pt3->lnb_on_cnt++;
	अन्यथा
		pt3->lnb_on_cnt--;

	अगर (on && pt3->lnb_on_cnt <= 1) अणु
		pt3->lnb_on_cnt = 1;
		pt3_lnb_ctrl(pt3, true);
	पूर्ण अन्यथा अगर (!on && pt3->lnb_on_cnt <= 0) अणु
		pt3->lnb_on_cnt = 0;
		pt3_lnb_ctrl(pt3, false);
	पूर्ण
	mutex_unlock(&pt3->lock);
	वापस 0;
पूर्ण

/* रेजिस्टर values used in pt3_fe_init() */

अटल स्थिर काष्ठा reg_val init0_sat[] = अणु
	अणु 0x03, 0x01 पूर्ण,
	अणु 0x1e, 0x10 पूर्ण,
पूर्ण;
अटल स्थिर काष्ठा reg_val init0_ter[] = अणु
	अणु 0x01, 0x40 पूर्ण,
	अणु 0x1c, 0x10 पूर्ण,
पूर्ण;
अटल स्थिर काष्ठा reg_val cfg_sat[] = अणु
	अणु 0x1c, 0x15 पूर्ण,
	अणु 0x1f, 0x04 पूर्ण,
पूर्ण;
अटल स्थिर काष्ठा reg_val cfg_ter[] = अणु
	अणु 0x1d, 0x01 पूर्ण,
पूर्ण;

/*
 * pt3_fe_init: initialize demod sub modules and ISDB-T tuners all at once.
 *
 * As क्रम demod IC (TC90522) and ISDB-T tuners (MxL301RF),
 * the i2c sequences क्रम init'ing them are not खुला and hidden in a ROM,
 * and include the board specअगरic configurations as well.
 * They are stored in a lump and cannot be taken out / accessed separately,
 * thus cannot be moved to the FE/tuner driver.
 */
अटल पूर्णांक pt3_fe_init(काष्ठा pt3_board *pt3)
अणु
	पूर्णांक i, ret;
	काष्ठा dvb_frontend *fe;

	pt3_i2c_reset(pt3);
	ret = pt3_init_all_demods(pt3);
	अगर (ret < 0) अणु
		dev_warn(&pt3->pdev->dev, "Failed to init demod chips\n");
		वापस ret;
	पूर्ण

	/* additional config? */
	क्रम (i = 0; i < PT3_NUM_FE; i++) अणु
		fe = pt3->adaps[i]->fe;

		अगर (fe->ops.delsys[0] == SYS_ISDBS)
			ret = pt3_demod_ग_लिखो(pt3->adaps[i],
					      init0_sat, ARRAY_SIZE(init0_sat));
		अन्यथा
			ret = pt3_demod_ग_लिखो(pt3->adaps[i],
					      init0_ter, ARRAY_SIZE(init0_ter));
		अगर (ret < 0) अणु
			dev_warn(&pt3->pdev->dev,
				 "demod[%d] failed in init sequence0\n", i);
			वापस ret;
		पूर्ण
		ret = fe->ops.init(fe);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	usleep_range(2000, 4000);
	ret = pt3_set_tuner_घातer(pt3, true, false);
	अगर (ret < 0) अणु
		dev_warn(&pt3->pdev->dev, "Failed to control tuner module\n");
		वापस ret;
	पूर्ण

	/* output pin configuration */
	क्रम (i = 0; i < PT3_NUM_FE; i++) अणु
		fe = pt3->adaps[i]->fe;
		अगर (fe->ops.delsys[0] == SYS_ISDBS)
			ret = pt3_demod_ग_लिखो(pt3->adaps[i],
						cfg_sat, ARRAY_SIZE(cfg_sat));
		अन्यथा
			ret = pt3_demod_ग_लिखो(pt3->adaps[i],
						cfg_ter, ARRAY_SIZE(cfg_ter));
		अगर (ret < 0) अणु
			dev_warn(&pt3->pdev->dev,
				 "demod[%d] failed in init sequence1\n", i);
			वापस ret;
		पूर्ण
	पूर्ण
	usleep_range(4000, 6000);

	क्रम (i = 0; i < PT3_NUM_FE; i++) अणु
		fe = pt3->adaps[i]->fe;
		अगर (fe->ops.delsys[0] != SYS_ISDBS)
			जारी;
		/* init and wake-up ISDB-S tuners */
		ret = fe->ops.tuner_ops.init(fe);
		अगर (ret < 0) अणु
			dev_warn(&pt3->pdev->dev,
				 "Failed to init SAT-tuner[%d]\n", i);
			वापस ret;
		पूर्ण
	पूर्ण
	ret = pt3_init_all_mxl301rf(pt3);
	अगर (ret < 0) अणु
		dev_warn(&pt3->pdev->dev, "Failed to init TERR-tuners\n");
		वापस ret;
	पूर्ण

	ret = pt3_set_tuner_घातer(pt3, true, true);
	अगर (ret < 0) अणु
		dev_warn(&pt3->pdev->dev, "Failed to control tuner module\n");
		वापस ret;
	पूर्ण

	/* Wake up all tuners and make an initial tuning,
	 * in order to aव्योम पूर्णांकerference among the tuners in the module,
	 * according to the करोc from the manufacturer.
	 */
	क्रम (i = 0; i < PT3_NUM_FE; i++) अणु
		fe = pt3->adaps[i]->fe;
		ret = 0;
		अगर (fe->ops.delsys[0] == SYS_ISDBT)
			ret = fe->ops.tuner_ops.init(fe);
		/* set only when called from pt3_probe(), not resume() */
		अगर (ret == 0 && fe->dtv_property_cache.frequency == 0) अणु
			fe->dtv_property_cache.frequency =
						adap_conf[i].init_freq;
			ret = fe->ops.tuner_ops.set_params(fe);
		पूर्ण
		अगर (ret < 0) अणु
			dev_warn(&pt3->pdev->dev,
				 "Failed in initial tuning of tuner[%d]\n", i);
			वापस ret;
		पूर्ण
	पूर्ण

	/* and sleep again, रुकोing to be खोलोed by users. */
	क्रम (i = 0; i < PT3_NUM_FE; i++) अणु
		fe = pt3->adaps[i]->fe;
		अगर (fe->ops.tuner_ops.sleep)
			ret = fe->ops.tuner_ops.sleep(fe);
		अगर (ret < 0)
			अवरोध;
		अगर (fe->ops.sleep)
			ret = fe->ops.sleep(fe);
		अगर (ret < 0)
			अवरोध;
		अगर (fe->ops.delsys[0] == SYS_ISDBS)
			fe->ops.set_voltage = &pt3_set_voltage;
		अन्यथा
			fe->ops.set_lna = &pt3_set_lna;
	पूर्ण
	अगर (i < PT3_NUM_FE) अणु
		dev_warn(&pt3->pdev->dev, "FE[%d] failed to standby\n", i);
		वापस ret;
	पूर्ण
	वापस 0;
पूर्ण


अटल पूर्णांक pt3_attach_fe(काष्ठा pt3_board *pt3, पूर्णांक i)
अणु
	स्थिर काष्ठा i2c_board_info *info;
	काष्ठा tc90522_config cfg;
	काष्ठा i2c_client *cl;
	काष्ठा dvb_adapter *dvb_adap;
	पूर्णांक ret;

	info = &adap_conf[i].demod_info;
	cfg = adap_conf[i].demod_cfg;
	cfg.tuner_i2c = शून्य;

	ret = -ENODEV;
	cl = dvb_module_probe("tc90522", info->type, &pt3->i2c_adap,
			      info->addr, &cfg);
	अगर (!cl)
		वापस -ENODEV;
	pt3->adaps[i]->i2c_demod = cl;

	अगर (!म_भेदन(cl->name, TC90522_I2C_DEV_SAT,
		     म_माप(TC90522_I2C_DEV_SAT))) अणु
		काष्ठा qm1d1c0042_config tcfg;

		tcfg = adap_conf[i].tuner_cfg.qm1d1c0042;
		tcfg.fe = cfg.fe;
		info = &adap_conf[i].tuner_info;
		cl = dvb_module_probe("qm1d1c0042", info->type, cfg.tuner_i2c,
				      info->addr, &tcfg);
	पूर्ण अन्यथा अणु
		काष्ठा mxl301rf_config tcfg;

		tcfg = adap_conf[i].tuner_cfg.mxl301rf;
		tcfg.fe = cfg.fe;
		info = &adap_conf[i].tuner_info;
		cl = dvb_module_probe("mxl301rf", info->type, cfg.tuner_i2c,
				      info->addr, &tcfg);
	पूर्ण
	अगर (!cl)
		जाओ err_demod_module_release;
	pt3->adaps[i]->i2c_tuner = cl;

	dvb_adap = &pt3->adaps[one_adapter ? 0 : i]->dvb_adap;
	ret = dvb_रेजिस्टर_frontend(dvb_adap, cfg.fe);
	अगर (ret < 0)
		जाओ err_tuner_module_release;
	pt3->adaps[i]->fe = cfg.fe;
	वापस 0;

err_tuner_module_release:
	dvb_module_release(pt3->adaps[i]->i2c_tuner);
err_demod_module_release:
	dvb_module_release(pt3->adaps[i]->i2c_demod);

	वापस ret;
पूर्ण


अटल पूर्णांक pt3_fetch_thपढ़ो(व्योम *data)
अणु
	काष्ठा pt3_adapter *adap = data;
	kसमय_प्रकार delay;
	bool was_frozen;

#घोषणा PT3_INITIAL_BUF_DROPS 4
#घोषणा PT3_FETCH_DELAY 10
#घोषणा PT3_FETCH_DELAY_DELTA 2

	pt3_init_dmabuf(adap);
	adap->num_discard = PT3_INITIAL_BUF_DROPS;

	dev_dbg(adap->dvb_adap.device, "PT3: [%s] started\n",
		adap->thपढ़ो->comm);
	set_मुक्तzable();
	जबतक (!kthपढ़ो_मुक्तzable_should_stop(&was_frozen)) अणु
		अगर (was_frozen)
			adap->num_discard = PT3_INITIAL_BUF_DROPS;

		pt3_proc_dma(adap);

		delay = kसमय_set(0, PT3_FETCH_DELAY * NSEC_PER_MSEC);
		set_current_state(TASK_UNINTERRUPTIBLE);
		मुक्तzable_schedule_hrसमयout_range(&delay,
					PT3_FETCH_DELAY_DELTA * NSEC_PER_MSEC,
					HRTIMER_MODE_REL);
	पूर्ण
	dev_dbg(adap->dvb_adap.device, "PT3: [%s] exited\n",
		adap->thपढ़ो->comm);
	वापस 0;
पूर्ण

अटल पूर्णांक pt3_start_streaming(काष्ठा pt3_adapter *adap)
अणु
	काष्ठा task_काष्ठा *thपढ़ो;

	/* start fetching thपढ़ो */
	thपढ़ो = kthपढ़ो_run(pt3_fetch_thपढ़ो, adap, "pt3-ad%i-dmx%i",
				adap->dvb_adap.num, adap->dmxdev.dvbdev->id);
	अगर (IS_ERR(thपढ़ो)) अणु
		पूर्णांक ret = PTR_ERR(thपढ़ो);

		adap->thपढ़ो = शून्य;
		dev_warn(adap->dvb_adap.device,
			 "PT3 (adap:%d, dmx:%d): failed to start kthread\n",
			 adap->dvb_adap.num, adap->dmxdev.dvbdev->id);
		वापस ret;
	पूर्ण
	adap->thपढ़ो = thपढ़ो;

	वापस pt3_start_dma(adap);
पूर्ण

अटल पूर्णांक pt3_stop_streaming(काष्ठा pt3_adapter *adap)
अणु
	पूर्णांक ret;

	ret = pt3_stop_dma(adap);
	अगर (ret)
		dev_warn(adap->dvb_adap.device,
			 "PT3: failed to stop streaming of adap:%d/FE:%d\n",
			 adap->dvb_adap.num, adap->fe->id);

	/* समाप्त the fetching thपढ़ो */
	ret = kthपढ़ो_stop(adap->thपढ़ो);
	adap->thपढ़ो = शून्य;
	वापस ret;
पूर्ण

अटल पूर्णांक pt3_start_feed(काष्ठा dvb_demux_feed *feed)
अणु
	काष्ठा pt3_adapter *adap;

	अगर (संकेत_pending(current))
		वापस -EINTR;

	adap = container_of(feed->demux, काष्ठा pt3_adapter, demux);
	adap->num_feeds++;
	अगर (adap->num_feeds > 1)
		वापस 0;

	वापस pt3_start_streaming(adap);

पूर्ण

अटल पूर्णांक pt3_stop_feed(काष्ठा dvb_demux_feed *feed)
अणु
	काष्ठा pt3_adapter *adap;

	adap = container_of(feed->demux, काष्ठा pt3_adapter, demux);

	adap->num_feeds--;
	अगर (adap->num_feeds > 0 || !adap->thपढ़ो)
		वापस 0;
	adap->num_feeds = 0;

	वापस pt3_stop_streaming(adap);
पूर्ण


अटल पूर्णांक pt3_alloc_adapter(काष्ठा pt3_board *pt3, पूर्णांक index)
अणु
	पूर्णांक ret;
	काष्ठा pt3_adapter *adap;
	काष्ठा dvb_adapter *da;

	adap = kzalloc(माप(*adap), GFP_KERNEL);
	अगर (!adap)
		वापस -ENOMEM;

	pt3->adaps[index] = adap;
	adap->adap_idx = index;

	अगर (index == 0 || !one_adapter) अणु
		ret = dvb_रेजिस्टर_adapter(&adap->dvb_adap, "PT3 DVB",
				THIS_MODULE, &pt3->pdev->dev, adapter_nr);
		अगर (ret < 0) अणु
			dev_err(&pt3->pdev->dev,
				"failed to register adapter dev\n");
			जाओ err_mem;
		पूर्ण
		da = &adap->dvb_adap;
	पूर्ण अन्यथा
		da = &pt3->adaps[0]->dvb_adap;

	adap->dvb_adap.priv = pt3;
	adap->demux.dmx.capabilities = DMX_TS_FILTERING | DMX_SECTION_FILTERING;
	adap->demux.priv = adap;
	adap->demux.feednum = 256;
	adap->demux.filternum = 256;
	adap->demux.start_feed = pt3_start_feed;
	adap->demux.stop_feed = pt3_stop_feed;
	ret = dvb_dmx_init(&adap->demux);
	अगर (ret < 0) अणु
		dev_err(&pt3->pdev->dev, "failed to init dmx dev\n");
		जाओ err_adap;
	पूर्ण

	adap->dmxdev.filternum = 256;
	adap->dmxdev.demux = &adap->demux.dmx;
	ret = dvb_dmxdev_init(&adap->dmxdev, da);
	अगर (ret < 0) अणु
		dev_err(&pt3->pdev->dev, "failed to init dmxdev\n");
		जाओ err_demux;
	पूर्ण

	ret = pt3_alloc_dmabuf(adap);
	अगर (ret) अणु
		dev_err(&pt3->pdev->dev, "failed to alloc DMA buffers\n");
		जाओ err_dmabuf;
	पूर्ण

	वापस 0;

err_dmabuf:
	pt3_मुक्त_dmabuf(adap);
	dvb_dmxdev_release(&adap->dmxdev);
err_demux:
	dvb_dmx_release(&adap->demux);
err_adap:
	अगर (index == 0 || !one_adapter)
		dvb_unरेजिस्टर_adapter(da);
err_mem:
	kमुक्त(adap);
	pt3->adaps[index] = शून्य;
	वापस ret;
पूर्ण

अटल व्योम pt3_cleanup_adapter(काष्ठा pt3_board *pt3, पूर्णांक index)
अणु
	काष्ठा pt3_adapter *adap;
	काष्ठा dmx_demux *dmx;

	adap = pt3->adaps[index];
	अगर (adap == शून्य)
		वापस;

	/* stop demux kthपढ़ो */
	अगर (adap->thपढ़ो)
		pt3_stop_streaming(adap);

	dmx = &adap->demux.dmx;
	dmx->बंद(dmx);
	अगर (adap->fe) अणु
		adap->fe->callback = शून्य;
		अगर (adap->fe->frontend_priv)
			dvb_unरेजिस्टर_frontend(adap->fe);
		dvb_module_release(adap->i2c_tuner);
		dvb_module_release(adap->i2c_demod);
	पूर्ण
	pt3_मुक्त_dmabuf(adap);
	dvb_dmxdev_release(&adap->dmxdev);
	dvb_dmx_release(&adap->demux);
	अगर (index == 0 || !one_adapter)
		dvb_unरेजिस्टर_adapter(&adap->dvb_adap);
	kमुक्त(adap);
	pt3->adaps[index] = शून्य;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP

अटल पूर्णांक pt3_suspend(काष्ठा device *dev)
अणु
	काष्ठा pt3_board *pt3 = dev_get_drvdata(dev);
	पूर्णांक i;
	काष्ठा pt3_adapter *adap;

	क्रम (i = 0; i < PT3_NUM_FE; i++) अणु
		adap = pt3->adaps[i];
		अगर (adap->num_feeds > 0)
			pt3_stop_dma(adap);
		dvb_frontend_suspend(adap->fe);
		pt3_मुक्त_dmabuf(adap);
	पूर्ण

	pt3_lnb_ctrl(pt3, false);
	pt3_set_tuner_घातer(pt3, false, false);
	वापस 0;
पूर्ण

अटल पूर्णांक pt3_resume(काष्ठा device *dev)
अणु
	काष्ठा pt3_board *pt3 = dev_get_drvdata(dev);
	पूर्णांक i, ret;
	काष्ठा pt3_adapter *adap;

	ret = pt3_fe_init(pt3);
	अगर (ret)
		वापस ret;

	अगर (pt3->lna_on_cnt > 0)
		pt3_set_tuner_घातer(pt3, true, true);
	अगर (pt3->lnb_on_cnt > 0)
		pt3_lnb_ctrl(pt3, true);

	क्रम (i = 0; i < PT3_NUM_FE; i++) अणु
		adap = pt3->adaps[i];
		dvb_frontend_resume(adap->fe);
		ret = pt3_alloc_dmabuf(adap);
		अगर (ret) अणु
			dev_err(&pt3->pdev->dev, "failed to alloc DMA bufs\n");
			जारी;
		पूर्ण
		अगर (adap->num_feeds > 0)
			pt3_start_dma(adap);
	पूर्ण

	वापस 0;
पूर्ण

#पूर्ण_अगर /* CONFIG_PM_SLEEP */


अटल व्योम pt3_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा pt3_board *pt3;
	पूर्णांक i;

	pt3 = pci_get_drvdata(pdev);
	क्रम (i = PT3_NUM_FE - 1; i >= 0; i--)
		pt3_cleanup_adapter(pt3, i);
	i2c_del_adapter(&pt3->i2c_adap);
	kमुक्त(pt3->i2c_buf);
	pci_iounmap(pt3->pdev, pt3->regs[0]);
	pci_iounmap(pt3->pdev, pt3->regs[1]);
	pci_release_regions(pdev);
	pci_disable_device(pdev);
	kमुक्त(pt3);
पूर्ण

अटल पूर्णांक pt3_probe(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *ent)
अणु
	u8 rev;
	u32 ver;
	पूर्णांक i, ret;
	काष्ठा pt3_board *pt3;
	काष्ठा i2c_adapter *i2c;

	अगर (pci_पढ़ो_config_byte(pdev, PCI_REVISION_ID, &rev) || rev != 1)
		वापस -ENODEV;

	ret = pci_enable_device(pdev);
	अगर (ret < 0)
		वापस -ENODEV;
	pci_set_master(pdev);

	ret = pci_request_regions(pdev, DRV_NAME);
	अगर (ret < 0)
		जाओ err_disable_device;

	ret = dma_set_mask(&pdev->dev, DMA_BIT_MASK(64));
	अगर (ret == 0)
		dma_set_coherent_mask(&pdev->dev, DMA_BIT_MASK(64));
	अन्यथा अणु
		ret = dma_set_mask(&pdev->dev, DMA_BIT_MASK(32));
		अगर (ret == 0)
			dma_set_coherent_mask(&pdev->dev, DMA_BIT_MASK(32));
		अन्यथा अणु
			dev_err(&pdev->dev, "Failed to set DMA mask\n");
			जाओ err_release_regions;
		पूर्ण
		dev_info(&pdev->dev, "Use 32bit DMA\n");
	पूर्ण

	pt3 = kzalloc(माप(*pt3), GFP_KERNEL);
	अगर (!pt3) अणु
		ret = -ENOMEM;
		जाओ err_release_regions;
	पूर्ण
	pci_set_drvdata(pdev, pt3);
	pt3->pdev = pdev;
	mutex_init(&pt3->lock);
	pt3->regs[0] = pci_ioremap_bar(pdev, 0);
	pt3->regs[1] = pci_ioremap_bar(pdev, 2);
	अगर (pt3->regs[0] == शून्य || pt3->regs[1] == शून्य) अणु
		dev_err(&pdev->dev, "Failed to ioremap\n");
		ret = -ENOMEM;
		जाओ err_kमुक्त;
	पूर्ण

	ver = ioपढ़ो32(pt3->regs[0] + REG_VERSION);
	अगर ((ver >> 16) != 0x0301) अणु
		dev_warn(&pdev->dev, "PT%d, I/F-ver.:%d not supported\n",
			 ver >> 24, (ver & 0x00ff0000) >> 16);
		ret = -ENODEV;
		जाओ err_iounmap;
	पूर्ण

	pt3->num_bufs = clamp_val(num_bufs, MIN_DATA_BUFS, MAX_DATA_BUFS);

	pt3->i2c_buf = kदो_स्मृति(माप(*pt3->i2c_buf), GFP_KERNEL);
	अगर (pt3->i2c_buf == शून्य) अणु
		ret = -ENOMEM;
		जाओ err_iounmap;
	पूर्ण
	i2c = &pt3->i2c_adap;
	i2c->owner = THIS_MODULE;
	i2c->algo = &pt3_i2c_algo;
	i2c->algo_data = शून्य;
	i2c->dev.parent = &pdev->dev;
	strscpy(i2c->name, DRV_NAME, माप(i2c->name));
	i2c_set_adapdata(i2c, pt3);
	ret = i2c_add_adapter(i2c);
	अगर (ret < 0)
		जाओ err_i2cbuf;

	क्रम (i = 0; i < PT3_NUM_FE; i++) अणु
		ret = pt3_alloc_adapter(pt3, i);
		अगर (ret < 0)
			अवरोध;

		ret = pt3_attach_fe(pt3, i);
		अगर (ret < 0)
			अवरोध;
	पूर्ण
	अगर (i < PT3_NUM_FE) अणु
		dev_err(&pdev->dev, "Failed to create FE%d\n", i);
		जाओ err_cleanup_adapters;
	पूर्ण

	ret = pt3_fe_init(pt3);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "Failed to init frontends\n");
		i = PT3_NUM_FE - 1;
		जाओ err_cleanup_adapters;
	पूर्ण

	dev_info(&pdev->dev,
		 "successfully init'ed PT%d (fw:0x%02x, I/F:0x%02x)\n",
		 ver >> 24, (ver >> 8) & 0xff, (ver >> 16) & 0xff);
	वापस 0;

err_cleanup_adapters:
	जबतक (i >= 0)
		pt3_cleanup_adapter(pt3, i--);
	i2c_del_adapter(i2c);
err_i2cbuf:
	kमुक्त(pt3->i2c_buf);
err_iounmap:
	अगर (pt3->regs[0])
		pci_iounmap(pdev, pt3->regs[0]);
	अगर (pt3->regs[1])
		pci_iounmap(pdev, pt3->regs[1]);
err_kमुक्त:
	kमुक्त(pt3);
err_release_regions:
	pci_release_regions(pdev);
err_disable_device:
	pci_disable_device(pdev);
	वापस ret;

पूर्ण

अटल स्थिर काष्ठा pci_device_id pt3_id_table[] = अणु
	अणु PCI_DEVICE_SUB(0x1172, 0x4c15, 0xee8d, 0x0368) पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(pci, pt3_id_table);

अटल SIMPLE_DEV_PM_OPS(pt3_pm_ops, pt3_suspend, pt3_resume);

अटल काष्ठा pci_driver pt3_driver = अणु
	.name		= DRV_NAME,
	.probe		= pt3_probe,
	.हटाओ		= pt3_हटाओ,
	.id_table	= pt3_id_table,

	.driver.pm	= &pt3_pm_ops,
पूर्ण;

module_pci_driver(pt3_driver);

MODULE_DESCRIPTION("Earthsoft PT3 Driver");
MODULE_AUTHOR("Akihiro TSUKADA");
MODULE_LICENSE("GPL");
