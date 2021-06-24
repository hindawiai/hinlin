<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// Register map access API - SPI support
//
// Copyright 2011 Wolfson Microelectronics plc
//
// Author: Mark Brown <broonie@खोलोsource.wolfsonmicro.com>

#समावेश <linux/regmap.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/module.h>

#समावेश "internal.h"

काष्ठा regmap_async_spi अणु
	काष्ठा regmap_async core;
	काष्ठा spi_message m;
	काष्ठा spi_transfer t[2];
पूर्ण;

अटल व्योम regmap_spi_complete(व्योम *data)
अणु
	काष्ठा regmap_async_spi *async = data;

	regmap_async_complete_cb(&async->core, async->m.status);
पूर्ण

अटल पूर्णांक regmap_spi_ग_लिखो(व्योम *context, स्थिर व्योम *data, माप_प्रकार count)
अणु
	काष्ठा device *dev = context;
	काष्ठा spi_device *spi = to_spi_device(dev);

	वापस spi_ग_लिखो(spi, data, count);
पूर्ण

अटल पूर्णांक regmap_spi_gather_ग_लिखो(व्योम *context,
				   स्थिर व्योम *reg, माप_प्रकार reg_len,
				   स्थिर व्योम *val, माप_प्रकार val_len)
अणु
	काष्ठा device *dev = context;
	काष्ठा spi_device *spi = to_spi_device(dev);
	काष्ठा spi_message m;
	काष्ठा spi_transfer t[2] = अणु अणु .tx_buf = reg, .len = reg_len, पूर्ण,
				     अणु .tx_buf = val, .len = val_len, पूर्ण, पूर्ण;

	spi_message_init(&m);
	spi_message_add_tail(&t[0], &m);
	spi_message_add_tail(&t[1], &m);

	वापस spi_sync(spi, &m);
पूर्ण

अटल पूर्णांक regmap_spi_async_ग_लिखो(व्योम *context,
				  स्थिर व्योम *reg, माप_प्रकार reg_len,
				  स्थिर व्योम *val, माप_प्रकार val_len,
				  काष्ठा regmap_async *a)
अणु
	काष्ठा regmap_async_spi *async = container_of(a,
						      काष्ठा regmap_async_spi,
						      core);
	काष्ठा device *dev = context;
	काष्ठा spi_device *spi = to_spi_device(dev);

	async->t[0].tx_buf = reg;
	async->t[0].len = reg_len;
	async->t[1].tx_buf = val;
	async->t[1].len = val_len;

	spi_message_init(&async->m);
	spi_message_add_tail(&async->t[0], &async->m);
	अगर (val)
		spi_message_add_tail(&async->t[1], &async->m);

	async->m.complete = regmap_spi_complete;
	async->m.context = async;

	वापस spi_async(spi, &async->m);
पूर्ण

अटल काष्ठा regmap_async *regmap_spi_async_alloc(व्योम)
अणु
	काष्ठा regmap_async_spi *async_spi;

	async_spi = kzalloc(माप(*async_spi), GFP_KERNEL);
	अगर (!async_spi)
		वापस शून्य;

	वापस &async_spi->core;
पूर्ण

अटल पूर्णांक regmap_spi_पढ़ो(व्योम *context,
			   स्थिर व्योम *reg, माप_प्रकार reg_size,
			   व्योम *val, माप_प्रकार val_size)
अणु
	काष्ठा device *dev = context;
	काष्ठा spi_device *spi = to_spi_device(dev);

	वापस spi_ग_लिखो_then_पढ़ो(spi, reg, reg_size, val, val_size);
पूर्ण

अटल स्थिर काष्ठा regmap_bus regmap_spi = अणु
	.ग_लिखो = regmap_spi_ग_लिखो,
	.gather_ग_लिखो = regmap_spi_gather_ग_लिखो,
	.async_ग_लिखो = regmap_spi_async_ग_लिखो,
	.async_alloc = regmap_spi_async_alloc,
	.पढ़ो = regmap_spi_पढ़ो,
	.पढ़ो_flag_mask = 0x80,
	.reg_क्रमmat_endian_शेष = REGMAP_ENDIAN_BIG,
	.val_क्रमmat_endian_शेष = REGMAP_ENDIAN_BIG,
पूर्ण;

काष्ठा regmap *__regmap_init_spi(काष्ठा spi_device *spi,
				 स्थिर काष्ठा regmap_config *config,
				 काष्ठा lock_class_key *lock_key,
				 स्थिर अक्षर *lock_name)
अणु
	वापस __regmap_init(&spi->dev, &regmap_spi, &spi->dev, config,
			     lock_key, lock_name);
पूर्ण
EXPORT_SYMBOL_GPL(__regmap_init_spi);

काष्ठा regmap *__devm_regmap_init_spi(काष्ठा spi_device *spi,
				      स्थिर काष्ठा regmap_config *config,
				      काष्ठा lock_class_key *lock_key,
				      स्थिर अक्षर *lock_name)
अणु
	वापस __devm_regmap_init(&spi->dev, &regmap_spi, &spi->dev, config,
				  lock_key, lock_name);
पूर्ण
EXPORT_SYMBOL_GPL(__devm_regmap_init_spi);

MODULE_LICENSE("GPL");
