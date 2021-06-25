<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Xilinx Spartan6 and 7 Series Slave Serial SPI Driver
 *
 * Copyright (C) 2017 DENX Software Engineering
 *
 * Anम_से_दij Gustschin <agust@denx.de>
 *
 * Manage Xilinx FPGA firmware that is loaded over SPI using
 * the slave serial configuration पूर्णांकerface.
 */

#समावेश <linux/delay.h>
#समावेश <linux/device.h>
#समावेश <linux/fpga/fpga-mgr.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/module.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/of.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/sizes.h>

काष्ठा xilinx_spi_conf अणु
	काष्ठा spi_device *spi;
	काष्ठा gpio_desc *prog_b;
	काष्ठा gpio_desc *init_b;
	काष्ठा gpio_desc *करोne;
पूर्ण;

अटल पूर्णांक get_करोne_gpio(काष्ठा fpga_manager *mgr)
अणु
	काष्ठा xilinx_spi_conf *conf = mgr->priv;
	पूर्णांक ret;

	ret = gpiod_get_value(conf->करोne);

	अगर (ret < 0)
		dev_err(&mgr->dev, "Error reading DONE (%d)\n", ret);

	वापस ret;
पूर्ण

अटल क्रमागत fpga_mgr_states xilinx_spi_state(काष्ठा fpga_manager *mgr)
अणु
	अगर (!get_करोne_gpio(mgr))
		वापस FPGA_MGR_STATE_RESET;

	वापस FPGA_MGR_STATE_UNKNOWN;
पूर्ण

/**
 * रुको_क्रम_init_b - रुको क्रम the INIT_B pin to have a given state, or रुको
 * a given delay अगर the pin is unavailable
 *
 * @mgr:        The FPGA manager object
 * @value:      Value INIT_B to रुको क्रम (1 = निश्चितed = low)
 * @alt_udelay: Delay to रुको अगर the INIT_B GPIO is not available
 *
 * Returns 0 when the INIT_B GPIO reached the given state or -ETIMEDOUT अगर
 * too much समय passed रुकोing क्रम that. If no INIT_B GPIO is available
 * then always वापस 0.
 */
अटल पूर्णांक रुको_क्रम_init_b(काष्ठा fpga_manager *mgr, पूर्णांक value,
			   अचिन्हित दीर्घ alt_udelay)
अणु
	काष्ठा xilinx_spi_conf *conf = mgr->priv;
	अचिन्हित दीर्घ समयout = jअगरfies + msecs_to_jअगरfies(1000);

	अगर (conf->init_b) अणु
		जबतक (समय_beक्रमe(jअगरfies, समयout)) अणु
			पूर्णांक ret = gpiod_get_value(conf->init_b);

			अगर (ret == value)
				वापस 0;

			अगर (ret < 0) अणु
				dev_err(&mgr->dev, "Error reading INIT_B (%d)\n", ret);
				वापस ret;
			पूर्ण

			usleep_range(100, 400);
		पूर्ण

		dev_err(&mgr->dev, "Timeout waiting for INIT_B to %s\n",
			value ? "assert" : "deassert");
		वापस -ETIMEDOUT;
	पूर्ण

	udelay(alt_udelay);

	वापस 0;
पूर्ण

अटल पूर्णांक xilinx_spi_ग_लिखो_init(काष्ठा fpga_manager *mgr,
				 काष्ठा fpga_image_info *info,
				 स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा xilinx_spi_conf *conf = mgr->priv;
	पूर्णांक err;

	अगर (info->flags & FPGA_MGR_PARTIAL_RECONFIG) अणु
		dev_err(&mgr->dev, "Partial reconfiguration not supported\n");
		वापस -EINVAL;
	पूर्ण

	gpiod_set_value(conf->prog_b, 1);

	err = रुको_क्रम_init_b(mgr, 1, 1); /* min is 500 ns */
	अगर (err) अणु
		gpiod_set_value(conf->prog_b, 0);
		वापस err;
	पूर्ण

	gpiod_set_value(conf->prog_b, 0);

	err = रुको_क्रम_init_b(mgr, 0, 0);
	अगर (err)
		वापस err;

	अगर (get_करोne_gpio(mgr)) अणु
		dev_err(&mgr->dev, "Unexpected DONE pin state...\n");
		वापस -EIO;
	पूर्ण

	/* program latency */
	usleep_range(7500, 7600);
	वापस 0;
पूर्ण

अटल पूर्णांक xilinx_spi_ग_लिखो(काष्ठा fpga_manager *mgr, स्थिर अक्षर *buf,
			    माप_प्रकार count)
अणु
	काष्ठा xilinx_spi_conf *conf = mgr->priv;
	स्थिर अक्षर *fw_data = buf;
	स्थिर अक्षर *fw_data_end = fw_data + count;

	जबतक (fw_data < fw_data_end) अणु
		माप_प्रकार reमुख्यing, stride;
		पूर्णांक ret;

		reमुख्यing = fw_data_end - fw_data;
		stride = min_t(माप_प्रकार, reमुख्यing, SZ_4K);

		ret = spi_ग_लिखो(conf->spi, fw_data, stride);
		अगर (ret) अणु
			dev_err(&mgr->dev, "SPI error in firmware write: %d\n",
				ret);
			वापस ret;
		पूर्ण
		fw_data += stride;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक xilinx_spi_apply_cclk_cycles(काष्ठा xilinx_spi_conf *conf)
अणु
	काष्ठा spi_device *spi = conf->spi;
	स्थिर u8 din_data[1] = अणु 0xff पूर्ण;
	पूर्णांक ret;

	ret = spi_ग_लिखो(conf->spi, din_data, माप(din_data));
	अगर (ret)
		dev_err(&spi->dev, "applying CCLK cycles failed: %d\n", ret);

	वापस ret;
पूर्ण

अटल पूर्णांक xilinx_spi_ग_लिखो_complete(काष्ठा fpga_manager *mgr,
				     काष्ठा fpga_image_info *info)
अणु
	काष्ठा xilinx_spi_conf *conf = mgr->priv;
	अचिन्हित दीर्घ समयout = jअगरfies + usecs_to_jअगरfies(info->config_complete_समयout_us);
	bool expired = false;
	पूर्णांक करोne;
	पूर्णांक ret;

	/*
	 * This loop is carefully written such that अगर the driver is
	 * scheduled out क्रम more than 'timeout', we still check क्रम DONE
	 * beक्रमe giving up and we apply 8 extra CCLK cycles in all हालs.
	 */
	जबतक (!expired) अणु
		expired = समय_after(jअगरfies, समयout);

		करोne = get_करोne_gpio(mgr);
		अगर (करोne < 0)
			वापस करोne;

		ret = xilinx_spi_apply_cclk_cycles(conf);
		अगर (ret)
			वापस ret;

		अगर (करोne)
			वापस 0;
	पूर्ण

	अगर (conf->init_b) अणु
		ret = gpiod_get_value(conf->init_b);

		अगर (ret < 0) अणु
			dev_err(&mgr->dev, "Error reading INIT_B (%d)\n", ret);
			वापस ret;
		पूर्ण

		dev_err(&mgr->dev,
			ret ? "CRC error or invalid device\n"
			: "Missing sync word or incomplete bitstream\n");
	पूर्ण अन्यथा अणु
		dev_err(&mgr->dev, "Timeout after config data transfer\n");
	पूर्ण

	वापस -ETIMEDOUT;
पूर्ण

अटल स्थिर काष्ठा fpga_manager_ops xilinx_spi_ops = अणु
	.state = xilinx_spi_state,
	.ग_लिखो_init = xilinx_spi_ग_लिखो_init,
	.ग_लिखो = xilinx_spi_ग_लिखो,
	.ग_लिखो_complete = xilinx_spi_ग_लिखो_complete,
पूर्ण;

अटल पूर्णांक xilinx_spi_probe(काष्ठा spi_device *spi)
अणु
	काष्ठा xilinx_spi_conf *conf;
	काष्ठा fpga_manager *mgr;

	conf = devm_kzalloc(&spi->dev, माप(*conf), GFP_KERNEL);
	अगर (!conf)
		वापस -ENOMEM;

	conf->spi = spi;

	/* PROGRAM_B is active low */
	conf->prog_b = devm_gpiod_get(&spi->dev, "prog_b", GPIOD_OUT_LOW);
	अगर (IS_ERR(conf->prog_b))
		वापस dev_err_probe(&spi->dev, PTR_ERR(conf->prog_b),
				     "Failed to get PROGRAM_B gpio\n");

	conf->init_b = devm_gpiod_get_optional(&spi->dev, "init-b", GPIOD_IN);
	अगर (IS_ERR(conf->init_b))
		वापस dev_err_probe(&spi->dev, PTR_ERR(conf->init_b),
				     "Failed to get INIT_B gpio\n");

	conf->करोne = devm_gpiod_get(&spi->dev, "done", GPIOD_IN);
	अगर (IS_ERR(conf->करोne))
		वापस dev_err_probe(&spi->dev, PTR_ERR(conf->करोne),
				     "Failed to get DONE gpio\n");

	mgr = devm_fpga_mgr_create(&spi->dev,
				   "Xilinx Slave Serial FPGA Manager",
				   &xilinx_spi_ops, conf);
	अगर (!mgr)
		वापस -ENOMEM;

	वापस devm_fpga_mgr_रेजिस्टर(&spi->dev, mgr);
पूर्ण

अटल स्थिर काष्ठा of_device_id xlnx_spi_of_match[] = अणु
	अणु .compatible = "xlnx,fpga-slave-serial", पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, xlnx_spi_of_match);

अटल काष्ठा spi_driver xilinx_slave_spi_driver = अणु
	.driver = अणु
		.name = "xlnx-slave-spi",
		.of_match_table = of_match_ptr(xlnx_spi_of_match),
	पूर्ण,
	.probe = xilinx_spi_probe,
पूर्ण;

module_spi_driver(xilinx_slave_spi_driver)

MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Anatolij Gustschin <agust@denx.de>");
MODULE_DESCRIPTION("Load Xilinx FPGA firmware over SPI");
