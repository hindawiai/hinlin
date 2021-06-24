<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2020 NovaTech LLC
 * George McCollister <george.mccollister@gmail.com>
 */

#समावेश <linux/bits.h>
#समावेश <linux/i2c.h>
#समावेश <linux/module.h>
#समावेश "xrs700x.h"
#समावेश "xrs700x_reg.h"

काष्ठा xrs700x_i2c_cmd अणु
	__be32 reg;
	__be16 val;
पूर्ण __packed;

अटल पूर्णांक xrs700x_i2c_reg_पढ़ो(व्योम *context, अचिन्हित पूर्णांक reg,
				अचिन्हित पूर्णांक *val)
अणु
	काष्ठा device *dev = context;
	काष्ठा i2c_client *i2c = to_i2c_client(dev);
	काष्ठा xrs700x_i2c_cmd cmd;
	पूर्णांक ret;

	cmd.reg = cpu_to_be32(reg | 1);

	ret = i2c_master_send(i2c, (अक्षर *)&cmd.reg, माप(cmd.reg));
	अगर (ret < 0) अणु
		dev_err(dev, "xrs i2c_master_send returned %d\n", ret);
		वापस ret;
	पूर्ण

	ret = i2c_master_recv(i2c, (अक्षर *)&cmd.val, माप(cmd.val));
	अगर (ret < 0) अणु
		dev_err(dev, "xrs i2c_master_recv returned %d\n", ret);
		वापस ret;
	पूर्ण

	*val = be16_to_cpu(cmd.val);
	वापस 0;
पूर्ण

अटल पूर्णांक xrs700x_i2c_reg_ग_लिखो(व्योम *context, अचिन्हित पूर्णांक reg,
				 अचिन्हित पूर्णांक val)
अणु
	काष्ठा device *dev = context;
	काष्ठा i2c_client *i2c = to_i2c_client(dev);
	काष्ठा xrs700x_i2c_cmd cmd;
	पूर्णांक ret;

	cmd.reg = cpu_to_be32(reg);
	cmd.val = cpu_to_be16(val);

	ret = i2c_master_send(i2c, (अक्षर *)&cmd, माप(cmd));
	अगर (ret < 0) अणु
		dev_err(dev, "xrs i2c_master_send returned %d\n", ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा regmap_config xrs700x_i2c_regmap_config = अणु
	.val_bits = 16,
	.reg_stride = 2,
	.reg_bits = 32,
	.pad_bits = 0,
	.ग_लिखो_flag_mask = 0,
	.पढ़ो_flag_mask = 0,
	.reg_पढ़ो = xrs700x_i2c_reg_पढ़ो,
	.reg_ग_लिखो = xrs700x_i2c_reg_ग_लिखो,
	.max_रेजिस्टर = 0,
	.cache_type = REGCACHE_NONE,
	.reg_क्रमmat_endian = REGMAP_ENDIAN_BIG,
	.val_क्रमmat_endian = REGMAP_ENDIAN_BIG
पूर्ण;

अटल पूर्णांक xrs700x_i2c_probe(काष्ठा i2c_client *i2c,
			     स्थिर काष्ठा i2c_device_id *i2c_id)
अणु
	काष्ठा xrs700x *priv;
	पूर्णांक ret;

	priv = xrs700x_चयन_alloc(&i2c->dev, i2c);
	अगर (!priv)
		वापस -ENOMEM;

	priv->regmap = devm_regmap_init(&i2c->dev, शून्य, &i2c->dev,
					&xrs700x_i2c_regmap_config);
	अगर (IS_ERR(priv->regmap)) अणु
		ret = PTR_ERR(priv->regmap);
		dev_err(&i2c->dev, "Failed to initialize regmap: %d\n", ret);
		वापस ret;
	पूर्ण

	i2c_set_clientdata(i2c, priv);

	ret = xrs700x_चयन_रेजिस्टर(priv);

	/* Main DSA driver may not be started yet. */
	अगर (ret)
		वापस ret;

	वापस 0;
पूर्ण

अटल पूर्णांक xrs700x_i2c_हटाओ(काष्ठा i2c_client *i2c)
अणु
	काष्ठा xrs700x *priv = i2c_get_clientdata(i2c);

	xrs700x_चयन_हटाओ(priv);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id xrs700x_i2c_id[] = अणु
	अणु "xrs700x-switch", 0 पूर्ण,
	अणुपूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(i2c, xrs700x_i2c_id);

अटल स्थिर काष्ठा of_device_id __maybe_unused xrs700x_i2c_dt_ids[] = अणु
	अणु .compatible = "arrow,xrs7003e", .data = &xrs7003e_info पूर्ण,
	अणु .compatible = "arrow,xrs7003f", .data = &xrs7003f_info पूर्ण,
	अणु .compatible = "arrow,xrs7004e", .data = &xrs7004e_info पूर्ण,
	अणु .compatible = "arrow,xrs7004f", .data = &xrs7004f_info पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, xrs700x_i2c_dt_ids);

अटल काष्ठा i2c_driver xrs700x_i2c_driver = अणु
	.driver = अणु
		.name	= "xrs700x-i2c",
		.of_match_table = of_match_ptr(xrs700x_i2c_dt_ids),
	पूर्ण,
	.probe	= xrs700x_i2c_probe,
	.हटाओ	= xrs700x_i2c_हटाओ,
	.id_table = xrs700x_i2c_id,
पूर्ण;

module_i2c_driver(xrs700x_i2c_driver);

MODULE_AUTHOR("George McCollister <george.mccollister@gmail.com>");
MODULE_DESCRIPTION("Arrow SpeedChips XRS700x DSA I2C driver");
MODULE_LICENSE("GPL v2");
