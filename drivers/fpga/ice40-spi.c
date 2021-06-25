<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * FPGA Manager Driver क्रम Lattice iCE40.
 *
 *  Copyright (c) 2016 Joel Holdsworth
 *
 * This driver adds support to the FPGA manager क्रम configuring the SRAM of
 * Lattice iCE40 FPGAs through slave SPI.
 */

#समावेश <linux/fpga/fpga-mgr.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/module.h>
#समावेश <linux/of_gpपन.स>
#समावेश <linux/spi/spi.h>
#समावेश <linux/stringअगरy.h>

#घोषणा ICE40_SPI_MAX_SPEED 25000000 /* Hz */
#घोषणा ICE40_SPI_MIN_SPEED 1000000 /* Hz */

#घोषणा ICE40_SPI_RESET_DELAY 1 /* us (>200ns) */
#घोषणा ICE40_SPI_HOUSEKEEPING_DELAY 1200 /* us */

#घोषणा ICE40_SPI_NUM_ACTIVATION_BYTES DIV_ROUND_UP(49, 8)

काष्ठा ice40_fpga_priv अणु
	काष्ठा spi_device *dev;
	काष्ठा gpio_desc *reset;
	काष्ठा gpio_desc *cकरोne;
पूर्ण;

अटल क्रमागत fpga_mgr_states ice40_fpga_ops_state(काष्ठा fpga_manager *mgr)
अणु
	काष्ठा ice40_fpga_priv *priv = mgr->priv;

	वापस gpiod_get_value(priv->cकरोne) ? FPGA_MGR_STATE_OPERATING :
		FPGA_MGR_STATE_UNKNOWN;
पूर्ण

अटल पूर्णांक ice40_fpga_ops_ग_लिखो_init(काष्ठा fpga_manager *mgr,
				     काष्ठा fpga_image_info *info,
				     स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा ice40_fpga_priv *priv = mgr->priv;
	काष्ठा spi_device *dev = priv->dev;
	काष्ठा spi_message message;
	काष्ठा spi_transfer निश्चित_cs_then_reset_delay = अणु
		.cs_change   = 1,
		.delay = अणु
			.value = ICE40_SPI_RESET_DELAY,
			.unit = SPI_DELAY_UNIT_USECS
		पूर्ण
	पूर्ण;
	काष्ठा spi_transfer housekeeping_delay_then_release_cs = अणु
		.delay = अणु
			.value = ICE40_SPI_HOUSEKEEPING_DELAY,
			.unit = SPI_DELAY_UNIT_USECS
		पूर्ण
	पूर्ण;
	पूर्णांक ret;

	अगर ((info->flags & FPGA_MGR_PARTIAL_RECONFIG)) अणु
		dev_err(&dev->dev,
			"Partial reconfiguration is not supported\n");
		वापस -ENOTSUPP;
	पूर्ण

	/* Lock the bus, निश्चित CRESET_B and SS_B and delay >200ns */
	spi_bus_lock(dev->master);

	gpiod_set_value(priv->reset, 1);

	spi_message_init(&message);
	spi_message_add_tail(&निश्चित_cs_then_reset_delay, &message);
	ret = spi_sync_locked(dev, &message);

	/* Come out of reset */
	gpiod_set_value(priv->reset, 0);

	/* Abort अगर the chip-select failed */
	अगर (ret)
		जाओ fail;

	/* Check CDONE is de-निश्चितed i.e. the FPGA is reset */
	अगर (gpiod_get_value(priv->cकरोne)) अणु
		dev_err(&dev->dev, "Device reset failed, CDONE is asserted\n");
		ret = -EIO;
		जाओ fail;
	पूर्ण

	/* Wait क्रम the housekeeping to complete, and release SS_B */
	spi_message_init(&message);
	spi_message_add_tail(&housekeeping_delay_then_release_cs, &message);
	ret = spi_sync_locked(dev, &message);

fail:
	spi_bus_unlock(dev->master);

	वापस ret;
पूर्ण

अटल पूर्णांक ice40_fpga_ops_ग_लिखो(काष्ठा fpga_manager *mgr,
				स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा ice40_fpga_priv *priv = mgr->priv;

	वापस spi_ग_लिखो(priv->dev, buf, count);
पूर्ण

अटल पूर्णांक ice40_fpga_ops_ग_लिखो_complete(काष्ठा fpga_manager *mgr,
					 काष्ठा fpga_image_info *info)
अणु
	काष्ठा ice40_fpga_priv *priv = mgr->priv;
	काष्ठा spi_device *dev = priv->dev;
	स्थिर u8 padding[ICE40_SPI_NUM_ACTIVATION_BYTES] = अणु0पूर्ण;

	/* Check CDONE is निश्चितed */
	अगर (!gpiod_get_value(priv->cकरोne)) अणु
		dev_err(&dev->dev,
			"CDONE was not asserted after firmware transfer\n");
		वापस -EIO;
	पूर्ण

	/* Send of zero-padding to activate the firmware */
	वापस spi_ग_लिखो(dev, padding, माप(padding));
पूर्ण

अटल स्थिर काष्ठा fpga_manager_ops ice40_fpga_ops = अणु
	.state = ice40_fpga_ops_state,
	.ग_लिखो_init = ice40_fpga_ops_ग_लिखो_init,
	.ग_लिखो = ice40_fpga_ops_ग_लिखो,
	.ग_लिखो_complete = ice40_fpga_ops_ग_लिखो_complete,
पूर्ण;

अटल पूर्णांक ice40_fpga_probe(काष्ठा spi_device *spi)
अणु
	काष्ठा device *dev = &spi->dev;
	काष्ठा ice40_fpga_priv *priv;
	काष्ठा fpga_manager *mgr;
	पूर्णांक ret;

	priv = devm_kzalloc(&spi->dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	priv->dev = spi;

	/* Check board setup data. */
	अगर (spi->max_speed_hz > ICE40_SPI_MAX_SPEED) अणु
		dev_err(dev, "SPI speed is too high, maximum speed is "
			__stringअगरy(ICE40_SPI_MAX_SPEED) "\n");
		वापस -EINVAL;
	पूर्ण

	अगर (spi->max_speed_hz < ICE40_SPI_MIN_SPEED) अणु
		dev_err(dev, "SPI speed is too low, minimum speed is "
			__stringअगरy(ICE40_SPI_MIN_SPEED) "\n");
		वापस -EINVAL;
	पूर्ण

	अगर (spi->mode & SPI_CPHA) अणु
		dev_err(dev, "Bad SPI mode, CPHA not supported\n");
		वापस -EINVAL;
	पूर्ण

	/* Set up the GPIOs */
	priv->cकरोne = devm_gpiod_get(dev, "cdone", GPIOD_IN);
	अगर (IS_ERR(priv->cकरोne)) अणु
		ret = PTR_ERR(priv->cकरोne);
		dev_err(dev, "Failed to get CDONE GPIO: %d\n", ret);
		वापस ret;
	पूर्ण

	priv->reset = devm_gpiod_get(dev, "reset", GPIOD_OUT_HIGH);
	अगर (IS_ERR(priv->reset)) अणु
		ret = PTR_ERR(priv->reset);
		dev_err(dev, "Failed to get CRESET_B GPIO: %d\n", ret);
		वापस ret;
	पूर्ण

	mgr = devm_fpga_mgr_create(dev, "Lattice iCE40 FPGA Manager",
				   &ice40_fpga_ops, priv);
	अगर (!mgr)
		वापस -ENOMEM;

	वापस devm_fpga_mgr_रेजिस्टर(dev, mgr);
पूर्ण

अटल स्थिर काष्ठा of_device_id ice40_fpga_of_match[] = अणु
	अणु .compatible = "lattice,ice40-fpga-mgr", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, ice40_fpga_of_match);

अटल काष्ठा spi_driver ice40_fpga_driver = अणु
	.probe = ice40_fpga_probe,
	.driver = अणु
		.name = "ice40spi",
		.of_match_table = of_match_ptr(ice40_fpga_of_match),
	पूर्ण,
पूर्ण;

module_spi_driver(ice40_fpga_driver);

MODULE_AUTHOR("Joel Holdsworth <joel@airwebreathe.org.uk>");
MODULE_DESCRIPTION("Lattice iCE40 FPGA Manager");
MODULE_LICENSE("GPL v2");
