<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Altera Passive Serial SPI Driver
 *
 *  Copyright (c) 2017 United Western Technologies, Corporation
 *
 *  Joshua Clayton <stillcompiling@gmail.com>
 *
 * Manage Altera FPGA firmware that is loaded over SPI using the passive
 * serial configuration method.
 * Firmware must be in binary "rbf" क्रमmat.
 * Works on Arria 10, Cyclone V and Stratix V. Should work on Cyclone series.
 * May work on other Altera FPGAs.
 */

#समावेश <linux/bitrev.h>
#समावेश <linux/delay.h>
#समावेश <linux/fpga/fpga-mgr.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/module.h>
#समावेश <linux/of_gpपन.स>
#समावेश <linux/of_device.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/sizes.h>

क्रमागत altera_ps_devtype अणु
	CYCLONE5,
	ARRIA10,
पूर्ण;

काष्ठा altera_ps_data अणु
	क्रमागत altera_ps_devtype devtype;
	पूर्णांक status_रुको_min_us;
	पूर्णांक status_रुको_max_us;
	पूर्णांक t_cfg_us;
	पूर्णांक t_st2ck_us;
पूर्ण;

काष्ठा altera_ps_conf अणु
	काष्ठा gpio_desc *config;
	काष्ठा gpio_desc *confd;
	काष्ठा gpio_desc *status;
	काष्ठा spi_device *spi;
	स्थिर काष्ठा altera_ps_data *data;
	u32 info_flags;
	अक्षर mgr_name[64];
पूर्ण;

/*          |   Arria 10  |   Cyclone5  |   Stratix5  |
 * t_CF2ST0 |     [; 600] |     [; 600] |     [; 600] |ns
 * t_CFG    |        [2;] |        [2;] |        [2;] |तगs
 * t_STATUS | [268; 3000] | [268; 1506] | [268; 1506] |तगs
 * t_CF2ST1 |    [; 3000] |    [; 1506] |    [; 1506] |तगs
 * t_CF2CK  |     [3010;] |     [1506;] |     [1506;] |तगs
 * t_ST2CK  |       [10;] |        [2;] |        [2;] |तगs
 * t_CD2UM  |  [175; 830] |  [175; 437] |  [175; 437] |तगs
 */
अटल काष्ठा altera_ps_data c5_data = अणु
	/* these values क्रम Cyclone5 are compatible with Stratix5 */
	.devtype = CYCLONE5,
	.status_रुको_min_us = 268,
	.status_रुको_max_us = 1506,
	.t_cfg_us = 2,
	.t_st2ck_us = 2,
पूर्ण;

अटल काष्ठा altera_ps_data a10_data = अणु
	.devtype = ARRIA10,
	.status_रुको_min_us = 268,  /* min(t_STATUS) */
	.status_रुको_max_us = 3000, /* max(t_CF2ST1) */
	.t_cfg_us = 2,    /* max अणु min(t_CFG), max(tCF2ST0) पूर्ण */
	.t_st2ck_us = 10, /* min(t_ST2CK) */
पूर्ण;

/* Array index is क्रमागत altera_ps_devtype */
अटल स्थिर काष्ठा altera_ps_data *altera_ps_data_map[] = अणु
	&c5_data,
	&a10_data,
पूर्ण;

अटल स्थिर काष्ठा of_device_id of_ef_match[] = अणु
	अणु .compatible = "altr,fpga-passive-serial", .data = &c5_data पूर्ण,
	अणु .compatible = "altr,fpga-arria10-passive-serial", .data = &a10_data पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, of_ef_match);

अटल क्रमागत fpga_mgr_states altera_ps_state(काष्ठा fpga_manager *mgr)
अणु
	काष्ठा altera_ps_conf *conf = mgr->priv;

	अगर (gpiod_get_value_cansleep(conf->status))
		वापस FPGA_MGR_STATE_RESET;

	वापस FPGA_MGR_STATE_UNKNOWN;
पूर्ण

अटल अंतरभूत व्योम altera_ps_delay(पूर्णांक delay_us)
अणु
	अगर (delay_us > 10)
		usleep_range(delay_us, delay_us + 5);
	अन्यथा
		udelay(delay_us);
पूर्ण

अटल पूर्णांक altera_ps_ग_लिखो_init(काष्ठा fpga_manager *mgr,
				काष्ठा fpga_image_info *info,
				स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा altera_ps_conf *conf = mgr->priv;
	पूर्णांक min, max, रुकोs;
	पूर्णांक i;

	conf->info_flags = info->flags;

	अगर (info->flags & FPGA_MGR_PARTIAL_RECONFIG) अणु
		dev_err(&mgr->dev, "Partial reconfiguration not supported.\n");
		वापस -EINVAL;
	पूर्ण

	gpiod_set_value_cansleep(conf->config, 1);

	/* रुको min reset pulse समय */
	altera_ps_delay(conf->data->t_cfg_us);

	अगर (!gpiod_get_value_cansleep(conf->status)) अणु
		dev_err(&mgr->dev, "Status pin failed to show a reset\n");
		वापस -EIO;
	पूर्ण

	gpiod_set_value_cansleep(conf->config, 0);

	min = conf->data->status_रुको_min_us;
	max = conf->data->status_रुको_max_us;
	रुकोs = max / min;
	अगर (max % min)
		रुकोs++;

	/* रुको क्रम max अणु max(t_STATUS), max(t_CF2ST1) पूर्ण */
	क्रम (i = 0; i < रुकोs; i++) अणु
		usleep_range(min, min + 10);
		अगर (!gpiod_get_value_cansleep(conf->status)) अणु
			/* रुको क्रम min(t_ST2CK)*/
			altera_ps_delay(conf->data->t_st2ck_us);
			वापस 0;
		पूर्ण
	पूर्ण

	dev_err(&mgr->dev, "Status pin not ready.\n");
	वापस -EIO;
पूर्ण

अटल व्योम rev_buf(अक्षर *buf, माप_प्रकार len)
अणु
	u32 *fw32 = (u32 *)buf;
	माप_प्रकार extra_bytes = (len & 0x03);
	स्थिर u32 *fw_end = (u32 *)(buf + len - extra_bytes);

	/* set buffer to lsb first */
	जबतक (fw32 < fw_end) अणु
		*fw32 = bitrev8x4(*fw32);
		fw32++;
	पूर्ण

	अगर (extra_bytes) अणु
		buf = (अक्षर *)fw_end;
		जबतक (extra_bytes) अणु
			*buf = bitrev8(*buf);
			buf++;
			extra_bytes--;
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक altera_ps_ग_लिखो(काष्ठा fpga_manager *mgr, स्थिर अक्षर *buf,
			   माप_प्रकार count)
अणु
	काष्ठा altera_ps_conf *conf = mgr->priv;
	स्थिर अक्षर *fw_data = buf;
	स्थिर अक्षर *fw_data_end = fw_data + count;

	जबतक (fw_data < fw_data_end) अणु
		पूर्णांक ret;
		माप_प्रकार stride = min_t(माप_प्रकार, fw_data_end - fw_data, SZ_4K);

		अगर (!(conf->info_flags & FPGA_MGR_BITSTREAM_LSB_FIRST))
			rev_buf((अक्षर *)fw_data, stride);

		ret = spi_ग_लिखो(conf->spi, fw_data, stride);
		अगर (ret) अणु
			dev_err(&mgr->dev, "spi error in firmware write: %d\n",
				ret);
			वापस ret;
		पूर्ण
		fw_data += stride;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक altera_ps_ग_लिखो_complete(काष्ठा fpga_manager *mgr,
				    काष्ठा fpga_image_info *info)
अणु
	काष्ठा altera_ps_conf *conf = mgr->priv;
	अटल स्थिर अक्षर dummy[] = अणु0पूर्ण;
	पूर्णांक ret;

	अगर (gpiod_get_value_cansleep(conf->status)) अणु
		dev_err(&mgr->dev, "Error during configuration.\n");
		वापस -EIO;
	पूर्ण

	अगर (conf->confd) अणु
		अगर (!gpiod_get_raw_value_cansleep(conf->confd)) अणु
			dev_err(&mgr->dev, "CONF_DONE is inactive!\n");
			वापस -EIO;
		पूर्ण
	पूर्ण

	/*
	 * After CONF_DONE goes high, send two additional falling edges on DCLK
	 * to begin initialization and enter user mode
	 */
	ret = spi_ग_लिखो(conf->spi, dummy, 1);
	अगर (ret) अणु
		dev_err(&mgr->dev, "spi error during end sequence: %d\n", ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा fpga_manager_ops altera_ps_ops = अणु
	.state = altera_ps_state,
	.ग_लिखो_init = altera_ps_ग_लिखो_init,
	.ग_लिखो = altera_ps_ग_लिखो,
	.ग_लिखो_complete = altera_ps_ग_लिखो_complete,
पूर्ण;

अटल स्थिर काष्ठा altera_ps_data *id_to_data(स्थिर काष्ठा spi_device_id *id)
अणु
	kernel_uदीर्घ_t devtype = id->driver_data;
	स्थिर काष्ठा altera_ps_data *data;

	/* someone added a altera_ps_devtype without adding to the map array */
	अगर (devtype >= ARRAY_SIZE(altera_ps_data_map))
		वापस शून्य;

	data = altera_ps_data_map[devtype];
	अगर (!data || data->devtype != devtype)
		वापस शून्य;

	वापस data;
पूर्ण

अटल पूर्णांक altera_ps_probe(काष्ठा spi_device *spi)
अणु
	काष्ठा altera_ps_conf *conf;
	स्थिर काष्ठा of_device_id *of_id;
	काष्ठा fpga_manager *mgr;

	conf = devm_kzalloc(&spi->dev, माप(*conf), GFP_KERNEL);
	अगर (!conf)
		वापस -ENOMEM;

	अगर (spi->dev.of_node) अणु
		of_id = of_match_device(of_ef_match, &spi->dev);
		अगर (!of_id)
			वापस -ENODEV;
		conf->data = of_id->data;
	पूर्ण अन्यथा अणु
		conf->data = id_to_data(spi_get_device_id(spi));
		अगर (!conf->data)
			वापस -ENODEV;
	पूर्ण

	conf->spi = spi;
	conf->config = devm_gpiod_get(&spi->dev, "nconfig", GPIOD_OUT_LOW);
	अगर (IS_ERR(conf->config)) अणु
		dev_err(&spi->dev, "Failed to get config gpio: %ld\n",
			PTR_ERR(conf->config));
		वापस PTR_ERR(conf->config);
	पूर्ण

	conf->status = devm_gpiod_get(&spi->dev, "nstat", GPIOD_IN);
	अगर (IS_ERR(conf->status)) अणु
		dev_err(&spi->dev, "Failed to get status gpio: %ld\n",
			PTR_ERR(conf->status));
		वापस PTR_ERR(conf->status);
	पूर्ण

	conf->confd = devm_gpiod_get_optional(&spi->dev, "confd", GPIOD_IN);
	अगर (IS_ERR(conf->confd)) अणु
		dev_err(&spi->dev, "Failed to get confd gpio: %ld\n",
			PTR_ERR(conf->confd));
		वापस PTR_ERR(conf->confd);
	पूर्ण अन्यथा अगर (!conf->confd) अणु
		dev_warn(&spi->dev, "Not using confd gpio");
	पूर्ण

	/* Register manager with unique name */
	snम_लिखो(conf->mgr_name, माप(conf->mgr_name), "%s %s",
		 dev_driver_string(&spi->dev), dev_name(&spi->dev));

	mgr = devm_fpga_mgr_create(&spi->dev, conf->mgr_name,
				   &altera_ps_ops, conf);
	अगर (!mgr)
		वापस -ENOMEM;

	वापस devm_fpga_mgr_रेजिस्टर(&spi->dev, mgr);
पूर्ण

अटल स्थिर काष्ठा spi_device_id altera_ps_spi_ids[] = अणु
	अणु "cyclone-ps-spi", CYCLONE5 पूर्ण,
	अणु "fpga-passive-serial", CYCLONE5 पूर्ण,
	अणु "fpga-arria10-passive-serial", ARRIA10 पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(spi, altera_ps_spi_ids);

अटल काष्ठा spi_driver altera_ps_driver = अणु
	.driver = अणु
		.name = "altera-ps-spi",
		.owner = THIS_MODULE,
		.of_match_table = of_match_ptr(of_ef_match),
	पूर्ण,
	.id_table = altera_ps_spi_ids,
	.probe = altera_ps_probe,
पूर्ण;

module_spi_driver(altera_ps_driver)

MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Joshua Clayton <stillcompiling@gmail.com>");
MODULE_DESCRIPTION("Module to load Altera FPGA firmware over SPI");
