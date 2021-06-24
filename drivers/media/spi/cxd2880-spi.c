<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * cxd2880-spi.c
 * Sony CXD2880 DVB-T2/T tuner + demodulator driver
 * SPI adapter
 *
 * Copyright (C) 2016, 2017, 2018 Sony Semiconductor Solutions Corporation
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": %s: " fmt, __func__

#समावेश <linux/spi/spi.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/kसमय.स>

#समावेश <media/dvb_demux.h>
#समावेश <media/dmxdev.h>
#समावेश <media/dvb_frontend.h>
#समावेश "cxd2880.h"

#घोषणा CXD2880_MAX_FILTER_SIZE 32
#घोषणा BURST_WRITE_MAX 128
#घोषणा MAX_TRANS_PKT 300

काष्ठा cxd2880_ts_buf_info अणु
	u8 पढ़ो_पढ़ोy:1;
	u8 almost_full:1;
	u8 almost_empty:1;
	u8 overflow:1;
	u8 underflow:1;
	u16 pkt_num;
पूर्ण;

काष्ठा cxd2880_pid_config अणु
	u8 is_enable;
	u16 pid;
पूर्ण;

काष्ठा cxd2880_pid_filter_config अणु
	u8 is_negative;
	काष्ठा cxd2880_pid_config pid_config[CXD2880_MAX_FILTER_SIZE];
पूर्ण;

काष्ठा cxd2880_dvb_spi अणु
	काष्ठा dvb_frontend dvb_fe;
	काष्ठा dvb_adapter adapter;
	काष्ठा dvb_demux demux;
	काष्ठा dmxdev dmxdev;
	काष्ठा dmx_frontend dmx_fe;
	काष्ठा task_काष्ठा *cxd2880_ts_पढ़ो_thपढ़ो;
	काष्ठा spi_device *spi;
	काष्ठा mutex spi_mutex; /* For SPI access exclusive control */
	पूर्णांक feed_count;
	पूर्णांक all_pid_feed_count;
	काष्ठा regulator *vcc_supply;
	u8 *ts_buf;
	काष्ठा cxd2880_pid_filter_config filter_config;
पूर्ण;

DVB_DEFINE_MOD_OPT_ADAPTER_NR(adapter_nr);

अटल पूर्णांक cxd2880_ग_लिखो_spi(काष्ठा spi_device *spi, u8 *data, u32 size)
अणु
	काष्ठा spi_message msg;
	काष्ठा spi_transfer tx = अणुपूर्ण;

	अगर (!spi || !data) अणु
		pr_err("invalid arg\n");
		वापस -EINVAL;
	पूर्ण

	tx.tx_buf = data;
	tx.len = size;

	spi_message_init(&msg);
	spi_message_add_tail(&tx, &msg);

	वापस spi_sync(spi, &msg);
पूर्ण

अटल पूर्णांक cxd2880_ग_लिखो_reg(काष्ठा spi_device *spi,
			     u8 sub_address, स्थिर u8 *data, u32 size)
अणु
	u8 send_data[BURST_WRITE_MAX + 4];
	स्थिर u8 *ग_लिखो_data_top = शून्य;
	पूर्णांक ret = 0;

	अगर (!spi || !data) अणु
		pr_err("invalid arg\n");
		वापस -EINVAL;
	पूर्ण
	अगर (size > BURST_WRITE_MAX || size > U8_MAX) अणु
		pr_err("data size > WRITE_MAX\n");
		वापस -EINVAL;
	पूर्ण

	अगर (sub_address + size > 0x100) अणु
		pr_err("out of range\n");
		वापस -EINVAL;
	पूर्ण

	send_data[0] = 0x0e;
	ग_लिखो_data_top = data;

	send_data[1] = sub_address;
	send_data[2] = (u8)size;

	स_नकल(&send_data[3], ग_लिखो_data_top, send_data[2]);

	ret = cxd2880_ग_लिखो_spi(spi, send_data, send_data[2] + 3);
	अगर (ret)
		pr_err("write spi failed %d\n", ret);

	वापस ret;
पूर्ण

अटल पूर्णांक cxd2880_spi_पढ़ो_ts(काष्ठा spi_device *spi,
			       u8 *पढ़ो_data,
			       u32 packet_num)
अणु
	पूर्णांक ret;
	u8 data[3];
	काष्ठा spi_message message;
	काष्ठा spi_transfer transfer[2] = अणुपूर्ण;

	अगर (!spi || !पढ़ो_data || !packet_num) अणु
		pr_err("invalid arg\n");
		वापस -EINVAL;
	पूर्ण
	अगर (packet_num > 0xffff) अणु
		pr_err("packet num > 0xffff\n");
		वापस -EINVAL;
	पूर्ण

	data[0] = 0x10;
	data[1] = packet_num >> 8;
	data[2] = packet_num;

	spi_message_init(&message);

	transfer[0].len = 3;
	transfer[0].tx_buf = data;
	spi_message_add_tail(&transfer[0], &message);
	transfer[1].len = packet_num * 188;
	transfer[1].rx_buf = पढ़ो_data;
	spi_message_add_tail(&transfer[1], &message);

	ret = spi_sync(spi, &message);
	अगर (ret)
		pr_err("spi_write_then_read failed\n");

	वापस ret;
पूर्ण

अटल पूर्णांक cxd2880_spi_पढ़ो_ts_buffer_info(काष्ठा spi_device *spi,
					   काष्ठा cxd2880_ts_buf_info *info)
अणु
	u8 send_data = 0x20;
	u8 recv_data[2];
	पूर्णांक ret;

	अगर (!spi || !info) अणु
		pr_err("invalid arg\n");
		वापस -EINVAL;
	पूर्ण

	ret = spi_ग_लिखो_then_पढ़ो(spi, &send_data, 1,
				  recv_data, माप(recv_data));
	अगर (ret)
		pr_err("spi_write_then_read failed\n");

	info->पढ़ो_पढ़ोy = (recv_data[0] & 0x80) ? 1 : 0;
	info->almost_full = (recv_data[0] & 0x40) ? 1 : 0;
	info->almost_empty = (recv_data[0] & 0x20) ? 1 : 0;
	info->overflow = (recv_data[0] & 0x10) ? 1 : 0;
	info->underflow = (recv_data[0] & 0x08) ? 1 : 0;
	info->pkt_num = ((recv_data[0] & 0x07) << 8) | recv_data[1];

	वापस ret;
पूर्ण

अटल पूर्णांक cxd2880_spi_clear_ts_buffer(काष्ठा spi_device *spi)
अणु
	u8 data = 0x03;
	पूर्णांक ret;

	ret = cxd2880_ग_लिखो_spi(spi, &data, 1);

	अगर (ret)
		pr_err("write spi failed\n");

	वापस ret;
पूर्ण

अटल पूर्णांक cxd2880_set_pid_filter(काष्ठा spi_device *spi,
				  काष्ठा cxd2880_pid_filter_config *cfg)
अणु
	u8 data[65];
	पूर्णांक i;
	u16 pid = 0;
	पूर्णांक ret;

	अगर (!spi) अणु
		pr_err("invalid arg\n");
		वापस -EINVAL;
	पूर्ण

	data[0] = 0x00;
	ret = cxd2880_ग_लिखो_reg(spi, 0x00, &data[0], 1);
	अगर (ret)
		वापस ret;
	अगर (!cfg) अणु
		data[0] = 0x02;
		ret = cxd2880_ग_लिखो_reg(spi, 0x50, &data[0], 1);
	पूर्ण अन्यथा अणु
		data[0] = cfg->is_negative ? 0x01 : 0x00;

		क्रम (i = 0; i < CXD2880_MAX_FILTER_SIZE; i++) अणु
			pid = cfg->pid_config[i].pid;
			अगर (cfg->pid_config[i].is_enable) अणु
				data[1 + (i * 2)] = (pid >> 8) | 0x20;
				data[2 + (i * 2)] = pid & 0xff;
			पूर्ण अन्यथा अणु
				data[1 + (i * 2)] = 0x00;
				data[2 + (i * 2)] = 0x00;
			पूर्ण
		पूर्ण
		ret = cxd2880_ग_लिखो_reg(spi, 0x50, data, 65);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक cxd2880_update_pid_filter(काष्ठा cxd2880_dvb_spi *dvb_spi,
				     काष्ठा cxd2880_pid_filter_config *cfg,
				     bool is_all_pid_filter)
अणु
	पूर्णांक ret;

	अगर (!dvb_spi || !cfg) अणु
		pr_err("invalid arg.\n");
		वापस -EINVAL;
	पूर्ण

	mutex_lock(&dvb_spi->spi_mutex);
	अगर (is_all_pid_filter) अणु
		काष्ठा cxd2880_pid_filter_config पंचांगpcfg;

		स_रखो(&पंचांगpcfg, 0, माप(पंचांगpcfg));
		पंचांगpcfg.is_negative = 1;
		पंचांगpcfg.pid_config[0].is_enable = 1;
		पंचांगpcfg.pid_config[0].pid = 0x1fff;

		ret = cxd2880_set_pid_filter(dvb_spi->spi, &पंचांगpcfg);
	पूर्ण अन्यथा अणु
		ret = cxd2880_set_pid_filter(dvb_spi->spi, cfg);
	पूर्ण
	mutex_unlock(&dvb_spi->spi_mutex);

	अगर (ret)
		pr_err("set_pid_filter failed\n");

	वापस ret;
पूर्ण

अटल पूर्णांक cxd2880_ts_पढ़ो(व्योम *arg)
अणु
	काष्ठा cxd2880_dvb_spi *dvb_spi = शून्य;
	काष्ठा cxd2880_ts_buf_info info;
	kसमय_प्रकार start;
	u32 i;
	पूर्णांक ret;

	dvb_spi = arg;
	अगर (!dvb_spi) अणु
		pr_err("invalid arg\n");
		वापस -EINVAL;
	पूर्ण

	ret = cxd2880_spi_clear_ts_buffer(dvb_spi->spi);
	अगर (ret) अणु
		pr_err("set_clear_ts_buffer failed\n");
		वापस ret;
	पूर्ण

	start = kसमय_get();
	जबतक (!kthपढ़ो_should_stop()) अणु
		ret = cxd2880_spi_पढ़ो_ts_buffer_info(dvb_spi->spi,
						      &info);
		अगर (ret) अणु
			pr_err("spi_read_ts_buffer_info error\n");
			वापस ret;
		पूर्ण

		अगर (info.pkt_num > MAX_TRANS_PKT) अणु
			क्रम (i = 0; i < info.pkt_num / MAX_TRANS_PKT; i++) अणु
				cxd2880_spi_पढ़ो_ts(dvb_spi->spi,
						    dvb_spi->ts_buf,
						    MAX_TRANS_PKT);
				dvb_dmx_swfilter(&dvb_spi->demux,
						 dvb_spi->ts_buf,
						 MAX_TRANS_PKT * 188);
			पूर्ण
			start = kसमय_get();
		पूर्ण अन्यथा अगर ((info.pkt_num > 0) &&
			   (kसमय_प्रकारo_ms(kसमय_sub(kसमय_get(), start)) >= 500)) अणु
			cxd2880_spi_पढ़ो_ts(dvb_spi->spi,
					    dvb_spi->ts_buf,
					    info.pkt_num);
			dvb_dmx_swfilter(&dvb_spi->demux,
					 dvb_spi->ts_buf,
					 info.pkt_num * 188);
			start = kसमय_get();
		पूर्ण अन्यथा अणु
			usleep_range(10000, 11000);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक cxd2880_start_feed(काष्ठा dvb_demux_feed *feed)
अणु
	पूर्णांक ret = 0;
	पूर्णांक i = 0;
	काष्ठा dvb_demux *demux = शून्य;
	काष्ठा cxd2880_dvb_spi *dvb_spi = शून्य;

	अगर (!feed) अणु
		pr_err("invalid arg\n");
		वापस -EINVAL;
	पूर्ण

	demux = feed->demux;
	अगर (!demux) अणु
		pr_err("feed->demux is NULL\n");
		वापस -EINVAL;
	पूर्ण
	dvb_spi = demux->priv;

	अगर (dvb_spi->feed_count == CXD2880_MAX_FILTER_SIZE) अणु
		pr_err("Exceeded maximum PID count (32).");
		pr_err("Selected PID cannot be enabled.\n");
		वापस -EINVAL;
	पूर्ण

	अगर (feed->pid == 0x2000) अणु
		अगर (dvb_spi->all_pid_feed_count == 0) अणु
			ret = cxd2880_update_pid_filter(dvb_spi,
							&dvb_spi->filter_config,
							true);
			अगर (ret) अणु
				pr_err("update pid filter failed\n");
				वापस ret;
			पूर्ण
		पूर्ण
		dvb_spi->all_pid_feed_count++;

		pr_debug("all PID feed (count = %d)\n",
			 dvb_spi->all_pid_feed_count);
	पूर्ण अन्यथा अणु
		काष्ठा cxd2880_pid_filter_config cfgपंचांगp;

		cfgपंचांगp = dvb_spi->filter_config;

		क्रम (i = 0; i < CXD2880_MAX_FILTER_SIZE; i++) अणु
			अगर (cfgपंचांगp.pid_config[i].is_enable == 0) अणु
				cfgपंचांगp.pid_config[i].is_enable = 1;
				cfgपंचांगp.pid_config[i].pid = feed->pid;
				pr_debug("store PID %d to #%d\n",
					 feed->pid, i);
				अवरोध;
			पूर्ण
		पूर्ण
		अगर (i == CXD2880_MAX_FILTER_SIZE) अणु
			pr_err("PID filter is full.\n");
			वापस -EINVAL;
		पूर्ण
		अगर (!dvb_spi->all_pid_feed_count)
			ret = cxd2880_update_pid_filter(dvb_spi,
							&cfgपंचांगp,
							false);
		अगर (ret)
			वापस ret;

		dvb_spi->filter_config = cfgपंचांगp;
	पूर्ण

	अगर (dvb_spi->feed_count == 0) अणु
		dvb_spi->ts_buf =
			kदो_स्मृति(MAX_TRANS_PKT * 188,
				GFP_KERNEL | GFP_DMA);
		अगर (!dvb_spi->ts_buf) अणु
			pr_err("ts buffer allocate failed\n");
			स_रखो(&dvb_spi->filter_config, 0,
			       माप(dvb_spi->filter_config));
			dvb_spi->all_pid_feed_count = 0;
			वापस -ENOMEM;
		पूर्ण
		dvb_spi->cxd2880_ts_पढ़ो_thपढ़ो = kthपढ़ो_run(cxd2880_ts_पढ़ो,
							      dvb_spi,
							      "cxd2880_ts_read");
		अगर (IS_ERR(dvb_spi->cxd2880_ts_पढ़ो_thपढ़ो)) अणु
			pr_err("kthread_run failed/\n");
			kमुक्त(dvb_spi->ts_buf);
			dvb_spi->ts_buf = शून्य;
			स_रखो(&dvb_spi->filter_config, 0,
			       माप(dvb_spi->filter_config));
			dvb_spi->all_pid_feed_count = 0;
			वापस PTR_ERR(dvb_spi->cxd2880_ts_पढ़ो_thपढ़ो);
		पूर्ण
	पूर्ण

	dvb_spi->feed_count++;

	pr_debug("start feed (count %d)\n", dvb_spi->feed_count);
	वापस 0;
पूर्ण

अटल पूर्णांक cxd2880_stop_feed(काष्ठा dvb_demux_feed *feed)
अणु
	पूर्णांक i = 0;
	पूर्णांक ret;
	काष्ठा dvb_demux *demux = शून्य;
	काष्ठा cxd2880_dvb_spi *dvb_spi = शून्य;

	अगर (!feed) अणु
		pr_err("invalid arg\n");
		वापस -EINVAL;
	पूर्ण

	demux = feed->demux;
	अगर (!demux) अणु
		pr_err("feed->demux is NULL\n");
		वापस -EINVAL;
	पूर्ण
	dvb_spi = demux->priv;

	अगर (!dvb_spi->feed_count) अणु
		pr_err("no feed is started\n");
		वापस -EINVAL;
	पूर्ण

	अगर (feed->pid == 0x2000) अणु
		/*
		 * Special PID हाल.
		 * Number of 0x2000 feed request was stored
		 * in dvb_spi->all_pid_feed_count.
		 */
		अगर (dvb_spi->all_pid_feed_count <= 0) अणु
			pr_err("PID %d not found.\n", feed->pid);
			वापस -EINVAL;
		पूर्ण
		dvb_spi->all_pid_feed_count--;
	पूर्ण अन्यथा अणु
		काष्ठा cxd2880_pid_filter_config cfgपंचांगp;

		cfgपंचांगp = dvb_spi->filter_config;

		क्रम (i = 0; i < CXD2880_MAX_FILTER_SIZE; i++) अणु
			अगर (feed->pid == cfgपंचांगp.pid_config[i].pid &&
			    cfgपंचांगp.pid_config[i].is_enable != 0) अणु
				cfgपंचांगp.pid_config[i].is_enable = 0;
				cfgपंचांगp.pid_config[i].pid = 0;
				pr_debug("removed PID %d from #%d\n",
					 feed->pid, i);
				अवरोध;
			पूर्ण
		पूर्ण
		dvb_spi->filter_config = cfgपंचांगp;

		अगर (i == CXD2880_MAX_FILTER_SIZE) अणु
			pr_err("PID %d not found\n", feed->pid);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	ret = cxd2880_update_pid_filter(dvb_spi,
					&dvb_spi->filter_config,
					dvb_spi->all_pid_feed_count > 0);
	dvb_spi->feed_count--;

	अगर (dvb_spi->feed_count == 0) अणु
		पूर्णांक ret_stop = 0;

		ret_stop = kthपढ़ो_stop(dvb_spi->cxd2880_ts_पढ़ो_thपढ़ो);
		अगर (ret_stop) अणु
			pr_err("'kthread_stop failed. (%d)\n", ret_stop);
			ret = ret_stop;
		पूर्ण
		kमुक्त(dvb_spi->ts_buf);
		dvb_spi->ts_buf = शून्य;
	पूर्ण

	pr_debug("stop feed ok.(count %d)\n", dvb_spi->feed_count);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा of_device_id cxd2880_spi_of_match[] = अणु
	अणु .compatible = "sony,cxd2880" पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(of, cxd2880_spi_of_match);

अटल पूर्णांक
cxd2880_spi_probe(काष्ठा spi_device *spi)
अणु
	पूर्णांक ret;
	काष्ठा cxd2880_dvb_spi *dvb_spi = शून्य;
	काष्ठा cxd2880_config config;

	अगर (!spi) अणु
		pr_err("invalid arg.\n");
		वापस -EINVAL;
	पूर्ण

	dvb_spi = kzalloc(माप(काष्ठा cxd2880_dvb_spi), GFP_KERNEL);
	अगर (!dvb_spi)
		वापस -ENOMEM;

	dvb_spi->vcc_supply = devm_regulator_get_optional(&spi->dev, "vcc");
	अगर (IS_ERR(dvb_spi->vcc_supply)) अणु
		अगर (PTR_ERR(dvb_spi->vcc_supply) == -EPROBE_DEFER) अणु
			ret = -EPROBE_DEFER;
			जाओ fail_adapter;
		पूर्ण
		dvb_spi->vcc_supply = शून्य;
	पूर्ण अन्यथा अणु
		ret = regulator_enable(dvb_spi->vcc_supply);
		अगर (ret)
			जाओ fail_adapter;
	पूर्ण

	dvb_spi->spi = spi;
	mutex_init(&dvb_spi->spi_mutex);
	spi_set_drvdata(spi, dvb_spi);
	config.spi = spi;
	config.spi_mutex = &dvb_spi->spi_mutex;

	ret = dvb_रेजिस्टर_adapter(&dvb_spi->adapter,
				   "CXD2880",
				   THIS_MODULE,
				   &spi->dev,
				   adapter_nr);
	अगर (ret < 0) अणु
		pr_err("dvb_register_adapter() failed\n");
		जाओ fail_adapter;
	पूर्ण

	अगर (!dvb_attach(cxd2880_attach, &dvb_spi->dvb_fe, &config)) अणु
		pr_err("cxd2880_attach failed\n");
		ret = -ENODEV;
		जाओ fail_attach;
	पूर्ण

	ret = dvb_रेजिस्टर_frontend(&dvb_spi->adapter,
				    &dvb_spi->dvb_fe);
	अगर (ret < 0) अणु
		pr_err("dvb_register_frontend() failed\n");
		जाओ fail_frontend;
	पूर्ण

	dvb_spi->demux.dmx.capabilities = DMX_TS_FILTERING;
	dvb_spi->demux.priv = dvb_spi;
	dvb_spi->demux.filternum = CXD2880_MAX_FILTER_SIZE;
	dvb_spi->demux.feednum = CXD2880_MAX_FILTER_SIZE;
	dvb_spi->demux.start_feed = cxd2880_start_feed;
	dvb_spi->demux.stop_feed = cxd2880_stop_feed;

	ret = dvb_dmx_init(&dvb_spi->demux);
	अगर (ret < 0) अणु
		pr_err("dvb_dmx_init() failed\n");
		जाओ fail_dmx;
	पूर्ण

	dvb_spi->dmxdev.filternum = CXD2880_MAX_FILTER_SIZE;
	dvb_spi->dmxdev.demux = &dvb_spi->demux.dmx;
	dvb_spi->dmxdev.capabilities = 0;
	ret = dvb_dmxdev_init(&dvb_spi->dmxdev,
			      &dvb_spi->adapter);
	अगर (ret < 0) अणु
		pr_err("dvb_dmxdev_init() failed\n");
		जाओ fail_dmxdev;
	पूर्ण

	dvb_spi->dmx_fe.source = DMX_FRONTEND_0;
	ret = dvb_spi->demux.dmx.add_frontend(&dvb_spi->demux.dmx,
					      &dvb_spi->dmx_fe);
	अगर (ret < 0) अणु
		pr_err("add_frontend() failed\n");
		जाओ fail_dmx_fe;
	पूर्ण

	ret = dvb_spi->demux.dmx.connect_frontend(&dvb_spi->demux.dmx,
						  &dvb_spi->dmx_fe);
	अगर (ret < 0) अणु
		pr_err("dvb_register_frontend() failed\n");
		जाओ fail_fe_conn;
	पूर्ण

	pr_info("Sony CXD2880 has successfully attached.\n");

	वापस 0;

fail_fe_conn:
	dvb_spi->demux.dmx.हटाओ_frontend(&dvb_spi->demux.dmx,
					   &dvb_spi->dmx_fe);
fail_dmx_fe:
	dvb_dmxdev_release(&dvb_spi->dmxdev);
fail_dmxdev:
	dvb_dmx_release(&dvb_spi->demux);
fail_dmx:
	dvb_unरेजिस्टर_frontend(&dvb_spi->dvb_fe);
fail_frontend:
	dvb_frontend_detach(&dvb_spi->dvb_fe);
fail_attach:
	dvb_unरेजिस्टर_adapter(&dvb_spi->adapter);
fail_adapter:
	kमुक्त(dvb_spi);
	वापस ret;
पूर्ण

अटल पूर्णांक
cxd2880_spi_हटाओ(काष्ठा spi_device *spi)
अणु
	काष्ठा cxd2880_dvb_spi *dvb_spi;

	अगर (!spi) अणु
		pr_err("invalid arg\n");
		वापस -EINVAL;
	पूर्ण

	dvb_spi = spi_get_drvdata(spi);

	अगर (!dvb_spi) अणु
		pr_err("failed\n");
		वापस -EINVAL;
	पूर्ण
	dvb_spi->demux.dmx.हटाओ_frontend(&dvb_spi->demux.dmx,
					   &dvb_spi->dmx_fe);
	dvb_dmxdev_release(&dvb_spi->dmxdev);
	dvb_dmx_release(&dvb_spi->demux);
	dvb_unरेजिस्टर_frontend(&dvb_spi->dvb_fe);
	dvb_frontend_detach(&dvb_spi->dvb_fe);
	dvb_unरेजिस्टर_adapter(&dvb_spi->adapter);

	अगर (dvb_spi->vcc_supply)
		regulator_disable(dvb_spi->vcc_supply);

	kमुक्त(dvb_spi);
	pr_info("cxd2880_spi remove ok.\n");

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा spi_device_id cxd2880_spi_id[] = अणु
	अणु "cxd2880", 0 पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(spi, cxd2880_spi_id);

अटल काष्ठा spi_driver cxd2880_spi_driver = अणु
	.driver	= अणु
		.name	= "cxd2880",
		.of_match_table = cxd2880_spi_of_match,
	पूर्ण,
	.id_table = cxd2880_spi_id,
	.probe    = cxd2880_spi_probe,
	.हटाओ   = cxd2880_spi_हटाओ,
पूर्ण;
module_spi_driver(cxd2880_spi_driver);

MODULE_DESCRIPTION("Sony CXD2880 DVB-T2/T tuner + demod driver SPI adapter");
MODULE_AUTHOR("Sony Semiconductor Solutions Corporation");
MODULE_LICENSE("GPL v2");
