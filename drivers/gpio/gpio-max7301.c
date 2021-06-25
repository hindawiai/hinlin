<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2006 Juergen Beisert, Pengutronix
 * Copyright (C) 2008 Guennadi Liakhovetski, Pengutronix
 * Copyright (C) 2009 Wolfram Sang, Pengutronix
 *
 * Check max730x.c क्रम further details.
 */

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/mutex.h>
#समावेश <linux/slab.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/spi/max7301.h>

/* A ग_लिखो to the MAX7301 means one message with one transfer */
अटल पूर्णांक max7301_spi_ग_लिखो(काष्ठा device *dev, अचिन्हित पूर्णांक reg,
				अचिन्हित पूर्णांक val)
अणु
	काष्ठा spi_device *spi = to_spi_device(dev);
	u16 word = ((reg & 0x7F) << 8) | (val & 0xFF);

	वापस spi_ग_लिखो_then_पढ़ो(spi, &word, माप(word), शून्य, 0);
पूर्ण

/* A पढ़ो from the MAX7301 means two transfers; here, one message each */

अटल पूर्णांक max7301_spi_पढ़ो(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	पूर्णांक ret;
	u16 word;
	काष्ठा spi_device *spi = to_spi_device(dev);

	word = 0x8000 | (reg << 8);
	ret = spi_ग_लिखो_then_पढ़ो(spi, &word, माप(word), &word,
				  माप(word));
	अगर (ret)
		वापस ret;
	वापस word & 0xff;
पूर्ण

अटल पूर्णांक max7301_probe(काष्ठा spi_device *spi)
अणु
	काष्ठा max7301 *ts;
	पूर्णांक ret;

	/* bits_per_word cannot be configured in platक्रमm data */
	spi->bits_per_word = 16;
	ret = spi_setup(spi);
	अगर (ret < 0)
		वापस ret;

	ts = devm_kzalloc(&spi->dev, माप(काष्ठा max7301), GFP_KERNEL);
	अगर (!ts)
		वापस -ENOMEM;

	ts->पढ़ो = max7301_spi_पढ़ो;
	ts->ग_लिखो = max7301_spi_ग_लिखो;
	ts->dev = &spi->dev;

	ret = __max730x_probe(ts);
	वापस ret;
पूर्ण

अटल पूर्णांक max7301_हटाओ(काष्ठा spi_device *spi)
अणु
	वापस __max730x_हटाओ(&spi->dev);
पूर्ण

अटल स्थिर काष्ठा spi_device_id max7301_id[] = अणु
	अणु "max7301", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(spi, max7301_id);

अटल काष्ठा spi_driver max7301_driver = अणु
	.driver = अणु
		.name = "max7301",
	पूर्ण,
	.probe = max7301_probe,
	.हटाओ = max7301_हटाओ,
	.id_table = max7301_id,
पूर्ण;

अटल पूर्णांक __init max7301_init(व्योम)
अणु
	वापस spi_रेजिस्टर_driver(&max7301_driver);
पूर्ण
/* रेजिस्टर after spi postcore initcall and beक्रमe
 * subsys initcalls that may rely on these GPIOs
 */
subsys_initcall(max7301_init);

अटल व्योम __निकास max7301_निकास(व्योम)
अणु
	spi_unरेजिस्टर_driver(&max7301_driver);
पूर्ण
module_निकास(max7301_निकास);

MODULE_AUTHOR("Juergen Beisert, Wolfram Sang");
MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("MAX7301 GPIO-Expander");
