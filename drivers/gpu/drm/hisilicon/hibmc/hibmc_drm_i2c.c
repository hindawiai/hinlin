<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* Hisilicon Hibmc SoC drm driver
 *
 * Based on the bochs drm driver.
 *
 * Copyright (c) 2016 Huawei Limited.
 *
 * Author:
 *      Tian Tao <tiantao6@hisilicon.com>
 */

#समावेश <linux/delay.h>
#समावेश <linux/pci.h>

#समावेश <drm/drm_atomic_helper.h>
#समावेश <drm/drm_probe_helper.h>

#समावेश "hibmc_drm_drv.h"

#घोषणा GPIO_DATA		0x0802A0
#घोषणा GPIO_DATA_सूचीECTION	0x0802A4

#घोषणा I2C_SCL_MASK		BIT(0)
#घोषणा I2C_SDA_MASK		BIT(1)

अटल व्योम hibmc_set_i2c_संकेत(व्योम *data, u32 mask, पूर्णांक value)
अणु
	काष्ठा hibmc_connector *hibmc_connector = data;
	काष्ठा hibmc_drm_निजी *priv = to_hibmc_drm_निजी(hibmc_connector->base.dev);
	u32 पंचांगp_dir = पढ़ोl(priv->mmio + GPIO_DATA_सूचीECTION);

	अगर (value) अणु
		पंचांगp_dir &= ~mask;
		ग_लिखोl(पंचांगp_dir, priv->mmio + GPIO_DATA_सूचीECTION);
	पूर्ण अन्यथा अणु
		u32 पंचांगp_data = पढ़ोl(priv->mmio + GPIO_DATA);

		पंचांगp_data &= ~mask;
		ग_लिखोl(पंचांगp_data, priv->mmio + GPIO_DATA);

		पंचांगp_dir |= mask;
		ग_लिखोl(पंचांगp_dir, priv->mmio + GPIO_DATA_सूचीECTION);
	पूर्ण
पूर्ण

अटल पूर्णांक hibmc_get_i2c_संकेत(व्योम *data, u32 mask)
अणु
	काष्ठा hibmc_connector *hibmc_connector = data;
	काष्ठा hibmc_drm_निजी *priv = to_hibmc_drm_निजी(hibmc_connector->base.dev);
	u32 पंचांगp_dir = पढ़ोl(priv->mmio + GPIO_DATA_सूचीECTION);

	अगर ((पंचांगp_dir & mask) != mask) अणु
		पंचांगp_dir &= ~mask;
		ग_लिखोl(पंचांगp_dir, priv->mmio + GPIO_DATA_सूचीECTION);
	पूर्ण

	वापस (पढ़ोl(priv->mmio + GPIO_DATA) & mask) ? 1 : 0;
पूर्ण

अटल व्योम hibmc_ddc_setsda(व्योम *data, पूर्णांक state)
अणु
	hibmc_set_i2c_संकेत(data, I2C_SDA_MASK, state);
पूर्ण

अटल व्योम hibmc_ddc_setscl(व्योम *data, पूर्णांक state)
अणु
	hibmc_set_i2c_संकेत(data, I2C_SCL_MASK, state);
पूर्ण

अटल पूर्णांक hibmc_ddc_माला_लोda(व्योम *data)
अणु
	वापस hibmc_get_i2c_संकेत(data, I2C_SDA_MASK);
पूर्ण

अटल पूर्णांक hibmc_ddc_माला_लोcl(व्योम *data)
अणु
	वापस hibmc_get_i2c_संकेत(data, I2C_SCL_MASK);
पूर्ण

पूर्णांक hibmc_ddc_create(काष्ठा drm_device *drm_dev,
		     काष्ठा hibmc_connector *connector)
अणु
	connector->adapter.owner = THIS_MODULE;
	connector->adapter.class = I2C_CLASS_DDC;
	snम_लिखो(connector->adapter.name, I2C_NAME_SIZE, "HIS i2c bit bus");
	connector->adapter.dev.parent = drm_dev->dev;
	i2c_set_adapdata(&connector->adapter, connector);
	connector->adapter.algo_data = &connector->bit_data;

	connector->bit_data.udelay = 20;
	connector->bit_data.समयout = usecs_to_jअगरfies(2000);
	connector->bit_data.data = connector;
	connector->bit_data.setsda = hibmc_ddc_setsda;
	connector->bit_data.setscl = hibmc_ddc_setscl;
	connector->bit_data.माला_लोda = hibmc_ddc_माला_लोda;
	connector->bit_data.माला_लोcl = hibmc_ddc_माला_लोcl;

	वापस i2c_bit_add_bus(&connector->adapter);
पूर्ण
