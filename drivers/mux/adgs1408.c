<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * ADGS1408/ADGS1409 SPI MUX driver
 *
 * Copyright 2018 Analog Devices Inc.
 */

#समावेश <linux/err.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/module.h>
#समावेश <linux/mux/driver.h>
#समावेश <linux/property.h>
#समावेश <linux/spi/spi.h>

#घोषणा ADGS1408_SW_DATA       (0x01)
#घोषणा ADGS1408_REG_READ(reg) ((reg) | 0x80)
#घोषणा ADGS1408_DISABLE       (0x00)
#घोषणा ADGS1408_MUX(state)    (((state) << 1) | 1)

क्रमागत adgs1408_chip_id अणु
	ADGS1408 = 1,
	ADGS1409,
पूर्ण;

अटल पूर्णांक adgs1408_spi_reg_ग_लिखो(काष्ठा spi_device *spi,
				  u8 reg_addr, u8 reg_data)
अणु
	u8 tx_buf[2];

	tx_buf[0] = reg_addr;
	tx_buf[1] = reg_data;

	वापस spi_ग_लिखो_then_पढ़ो(spi, tx_buf, माप(tx_buf), शून्य, 0);
पूर्ण

अटल पूर्णांक adgs1408_set(काष्ठा mux_control *mux, पूर्णांक state)
अणु
	काष्ठा spi_device *spi = to_spi_device(mux->chip->dev.parent);
	u8 reg;

	अगर (state == MUX_IDLE_DISCONNECT)
		reg = ADGS1408_DISABLE;
	अन्यथा
		reg = ADGS1408_MUX(state);

	वापस adgs1408_spi_reg_ग_लिखो(spi, ADGS1408_SW_DATA, reg);
पूर्ण

अटल स्थिर काष्ठा mux_control_ops adgs1408_ops = अणु
	.set = adgs1408_set,
पूर्ण;

अटल पूर्णांक adgs1408_probe(काष्ठा spi_device *spi)
अणु
	काष्ठा device *dev = &spi->dev;
	क्रमागत adgs1408_chip_id chip_id;
	काष्ठा mux_chip *mux_chip;
	काष्ठा mux_control *mux;
	s32 idle_state;
	पूर्णांक ret;

	chip_id = (क्रमागत adgs1408_chip_id)device_get_match_data(dev);
	अगर (!chip_id)
		chip_id = spi_get_device_id(spi)->driver_data;

	mux_chip = devm_mux_chip_alloc(dev, 1, 0);
	अगर (IS_ERR(mux_chip))
		वापस PTR_ERR(mux_chip);

	mux_chip->ops = &adgs1408_ops;

	ret = adgs1408_spi_reg_ग_लिखो(spi, ADGS1408_SW_DATA, ADGS1408_DISABLE);
	अगर (ret < 0)
		वापस ret;

	ret = device_property_पढ़ो_u32(dev, "idle-state", (u32 *)&idle_state);
	अगर (ret < 0)
		idle_state = MUX_IDLE_AS_IS;

	mux = mux_chip->mux;

	अगर (chip_id == ADGS1408)
		mux->states = 8;
	अन्यथा
		mux->states = 4;

	चयन (idle_state) अणु
	हाल MUX_IDLE_DISCONNECT:
	हाल MUX_IDLE_AS_IS:
	हाल 0 ... 7:
		/* adgs1409 supports only 4 states */
		अगर (idle_state < mux->states) अणु
			mux->idle_state = idle_state;
			अवरोध;
		पूर्ण
		fallthrough;
	शेष:
		dev_err(dev, "invalid idle-state %d\n", idle_state);
		वापस -EINVAL;
	पूर्ण

	वापस devm_mux_chip_रेजिस्टर(dev, mux_chip);
पूर्ण

अटल स्थिर काष्ठा spi_device_id adgs1408_spi_id[] = अणु
	अणु "adgs1408", ADGS1408 पूर्ण,
	अणु "adgs1409", ADGS1409 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(spi, adgs1408_spi_id);

अटल स्थिर काष्ठा of_device_id adgs1408_of_match[] = अणु
	अणु .compatible = "adi,adgs1408", .data = (व्योम *)ADGS1408, पूर्ण,
	अणु .compatible = "adi,adgs1409", .data = (व्योम *)ADGS1409, पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, adgs1408_of_match);

अटल काष्ठा spi_driver adgs1408_driver = अणु
	.driver = अणु
		.name = "adgs1408",
		.of_match_table = adgs1408_of_match,
	पूर्ण,
	.probe = adgs1408_probe,
	.id_table = adgs1408_spi_id,
पूर्ण;
module_spi_driver(adgs1408_driver);

MODULE_AUTHOR("Mircea Caprioru <mircea.caprioru@analog.com>");
MODULE_DESCRIPTION("Analog Devices ADGS1408 MUX driver");
MODULE_LICENSE("GPL");
