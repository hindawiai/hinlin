<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Multiplexer driver क्रम Analog Devices ADG792A/G Triple 4:1 mux
 *
 * Copyright (C) 2017 Axentia Technologies AB
 *
 * Author: Peter Rosin <peda@axentia.se>
 */

#समावेश <linux/err.h>
#समावेश <linux/i2c.h>
#समावेश <linux/module.h>
#समावेश <linux/mux/driver.h>
#समावेश <linux/property.h>

#घोषणा ADG792A_LDSW		BIT(0)
#घोषणा ADG792A_RESETB		BIT(1)
#घोषणा ADG792A_DISABLE(mux)	(0x50 | (mux))
#घोषणा ADG792A_DISABLE_ALL	(0x5f)
#घोषणा ADG792A_MUX(mux, state)	(0xc0 | (((mux) + 1) << 2) | (state))
#घोषणा ADG792A_MUX_ALL(state)	(0xc0 | (state))

अटल पूर्णांक adg792a_ग_लिखो_cmd(काष्ठा i2c_client *i2c, u8 cmd, पूर्णांक reset)
अणु
	u8 data = ADG792A_RESETB | ADG792A_LDSW;

	/* ADG792A_RESETB is active low, the chip resets when it is zero. */
	अगर (reset)
		data &= ~ADG792A_RESETB;

	वापस i2c_smbus_ग_लिखो_byte_data(i2c, cmd, data);
पूर्ण

अटल पूर्णांक adg792a_set(काष्ठा mux_control *mux, पूर्णांक state)
अणु
	काष्ठा i2c_client *i2c = to_i2c_client(mux->chip->dev.parent);
	u8 cmd;

	अगर (mux->chip->controllers == 1) अणु
		/* parallel mux controller operation */
		अगर (state == MUX_IDLE_DISCONNECT)
			cmd = ADG792A_DISABLE_ALL;
		अन्यथा
			cmd = ADG792A_MUX_ALL(state);
	पूर्ण अन्यथा अणु
		अचिन्हित पूर्णांक controller = mux_control_get_index(mux);

		अगर (state == MUX_IDLE_DISCONNECT)
			cmd = ADG792A_DISABLE(controller);
		अन्यथा
			cmd = ADG792A_MUX(controller, state);
	पूर्ण

	वापस adg792a_ग_लिखो_cmd(i2c, cmd, 0);
पूर्ण

अटल स्थिर काष्ठा mux_control_ops adg792a_ops = अणु
	.set = adg792a_set,
पूर्ण;

अटल पूर्णांक adg792a_probe(काष्ठा i2c_client *i2c)
अणु
	काष्ठा device *dev = &i2c->dev;
	काष्ठा mux_chip *mux_chip;
	s32 idle_state[3];
	u32 cells;
	पूर्णांक ret;
	पूर्णांक i;

	अगर (!i2c_check_functionality(i2c->adapter, I2C_FUNC_SMBUS_BYTE_DATA))
		वापस -ENODEV;

	ret = device_property_पढ़ो_u32(dev, "#mux-control-cells", &cells);
	अगर (ret < 0)
		वापस ret;
	अगर (cells >= 2)
		वापस -EINVAL;

	mux_chip = devm_mux_chip_alloc(dev, cells ? 3 : 1, 0);
	अगर (IS_ERR(mux_chip))
		वापस PTR_ERR(mux_chip);

	mux_chip->ops = &adg792a_ops;

	ret = adg792a_ग_लिखो_cmd(i2c, ADG792A_DISABLE_ALL, 1);
	अगर (ret < 0)
		वापस ret;

	ret = device_property_पढ़ो_u32_array(dev, "idle-state",
					     (u32 *)idle_state,
					     mux_chip->controllers);
	अगर (ret < 0) अणु
		idle_state[0] = MUX_IDLE_AS_IS;
		idle_state[1] = MUX_IDLE_AS_IS;
		idle_state[2] = MUX_IDLE_AS_IS;
	पूर्ण

	क्रम (i = 0; i < mux_chip->controllers; ++i) अणु
		काष्ठा mux_control *mux = &mux_chip->mux[i];

		mux->states = 4;

		चयन (idle_state[i]) अणु
		हाल MUX_IDLE_DISCONNECT:
		हाल MUX_IDLE_AS_IS:
		हाल 0 ... 4:
			mux->idle_state = idle_state[i];
			अवरोध;
		शेष:
			dev_err(dev, "invalid idle-state %d\n", idle_state[i]);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	ret = devm_mux_chip_रेजिस्टर(dev, mux_chip);
	अगर (ret < 0)
		वापस ret;

	अगर (cells)
		dev_info(dev, "3x single pole quadruple throw muxes registered\n");
	अन्यथा
		dev_info(dev, "triple pole quadruple throw mux registered\n");

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id adg792a_id[] = अणु
	अणु .name = "adg792a", पूर्ण,
	अणु .name = "adg792g", पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, adg792a_id);

अटल स्थिर काष्ठा of_device_id adg792a_of_match[] = अणु
	अणु .compatible = "adi,adg792a", पूर्ण,
	अणु .compatible = "adi,adg792g", पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, adg792a_of_match);

अटल काष्ठा i2c_driver adg792a_driver = अणु
	.driver		= अणु
		.name		= "adg792a",
		.of_match_table = of_match_ptr(adg792a_of_match),
	पूर्ण,
	.probe_new	= adg792a_probe,
	.id_table	= adg792a_id,
पूर्ण;
module_i2c_driver(adg792a_driver);

MODULE_DESCRIPTION("Analog Devices ADG792A/G Triple 4:1 mux driver");
MODULE_AUTHOR("Peter Rosin <peda@axentia.se>");
MODULE_LICENSE("GPL v2");
