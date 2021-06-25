<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * gpio-max3191x.c - GPIO driver क्रम Maxim MAX3191x industrial serializer
 *
 * Copyright (C) 2017 KUNBUS GmbH
 *
 * The MAX3191x makes 8 digital 24V inमाला_दो available via SPI.
 * Multiple chips can be daisy-chained, the spec करोes not impose
 * a limit on the number of chips and neither करोes this driver.
 *
 * Either of two modes is selectable: In 8-bit mode, only the state
 * of the inमाला_दो is घड़ीed out to achieve high पढ़ोout speeds;
 * In 16-bit mode, an additional status byte is घड़ीed out with
 * a CRC and indicator bits क्रम undervoltage and overtemperature.
 * The driver वापसs an error instead of potentially bogus data
 * अगर any of these fault conditions occur.  However it करोes allow
 * पढ़ोout of non-faulting chips in the same daisy-chain.
 *
 * MAX3191x supports four debounce settings and the driver is
 * capable of configuring these dअगरferently क्रम each chip in the
 * daisy-chain.
 *
 * If the chips are hardwired to 8-bit mode ("modesel" pulled high),
 * gpio-pisosr.c can be used alternatively to this driver.
 *
 * https://datasheets.maximपूर्णांकegrated.com/en/ds/MAX31910.pdf
 * https://datasheets.maximपूर्णांकegrated.com/en/ds/MAX31911.pdf
 * https://datasheets.maximपूर्णांकegrated.com/en/ds/MAX31912.pdf
 * https://datasheets.maximपूर्णांकegrated.com/en/ds/MAX31913.pdf
 * https://datasheets.maximपूर्णांकegrated.com/en/ds/MAX31953-MAX31963.pdf
 */

#समावेश <linux/biपंचांगap.h>
#समावेश <linux/bitops.h>
#समावेश <linux/crc8.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/gpio/driver.h>
#समावेश <linux/module.h>
#समावेश <linux/spi/spi.h>

क्रमागत max3191x_mode अणु
	STATUS_BYTE_ENABLED,
	STATUS_BYTE_DISABLED,
पूर्ण;

/**
 * काष्ठा max3191x_chip - max3191x daisy-chain
 * @gpio: GPIO controller काष्ठा
 * @lock: protects पढ़ो sequences
 * @nchips: number of chips in the daisy-chain
 * @mode: current mode, 0 क्रम 16-bit, 1 क्रम 8-bit;
 *	क्रम simplicity, all chips in the daisy-chain are assumed
 *	to use the same mode
 * @modesel_pins: GPIO pins to configure modesel of each chip
 * @fault_pins: GPIO pins to detect fault of each chip
 * @db0_pins: GPIO pins to configure debounce of each chip
 * @db1_pins: GPIO pins to configure debounce of each chip
 * @mesg: SPI message to perक्रमm a पढ़ोout
 * @xfer: SPI transfer used by @mesg
 * @crc_error: biपंचांगap संकेतing CRC error क्रम each chip
 * @overtemp: biपंचांगap संकेतing overtemperature alarm क्रम each chip
 * @undervolt1: biपंचांगap संकेतing undervoltage alarm क्रम each chip
 * @undervolt2: biपंचांगap संकेतing undervoltage warning क्रम each chip
 * @fault: biपंचांगap संकेतing निश्चितion of @fault_pins क्रम each chip
 * @ignore_uv: whether to ignore undervoltage alarms;
 *	set by a device property अगर the chips are घातered through
 *	5VOUT instead of VCC24V, in which हाल they will स्थिरantly
 *	संकेत undervoltage;
 *	क्रम simplicity, all chips in the daisy-chain are assumed
 *	to be घातered the same way
 */
काष्ठा max3191x_chip अणु
	काष्ठा gpio_chip gpio;
	काष्ठा mutex lock;
	u32 nchips;
	क्रमागत max3191x_mode mode;
	काष्ठा gpio_descs *modesel_pins;
	काष्ठा gpio_descs *fault_pins;
	काष्ठा gpio_descs *db0_pins;
	काष्ठा gpio_descs *db1_pins;
	काष्ठा spi_message mesg;
	काष्ठा spi_transfer xfer;
	अचिन्हित दीर्घ *crc_error;
	अचिन्हित दीर्घ *overtemp;
	अचिन्हित दीर्घ *undervolt1;
	अचिन्हित दीर्घ *undervolt2;
	अचिन्हित दीर्घ *fault;
	bool ignore_uv;
पूर्ण;

#घोषणा MAX3191X_NGPIO 8
#घोषणा MAX3191X_CRC8_POLYNOMIAL 0xa8 /* (x^5) + x^4 + x^2 + x^0 */

DECLARE_CRC8_TABLE(max3191x_crc8);

अटल पूर्णांक max3191x_get_direction(काष्ठा gpio_chip *gpio, अचिन्हित पूर्णांक offset)
अणु
	वापस GPIO_LINE_सूचीECTION_IN; /* always in */
पूर्ण

अटल पूर्णांक max3191x_direction_input(काष्ठा gpio_chip *gpio, अचिन्हित पूर्णांक offset)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक max3191x_direction_output(काष्ठा gpio_chip *gpio,
				     अचिन्हित पूर्णांक offset, पूर्णांक value)
अणु
	वापस -EINVAL;
पूर्ण

अटल व्योम max3191x_set(काष्ठा gpio_chip *gpio, अचिन्हित पूर्णांक offset, पूर्णांक value)
अणु पूर्ण

अटल व्योम max3191x_set_multiple(काष्ठा gpio_chip *gpio, अचिन्हित दीर्घ *mask,
				  अचिन्हित दीर्घ *bits)
अणु पूर्ण

अटल अचिन्हित पूर्णांक max3191x_wordlen(काष्ठा max3191x_chip *max3191x)
अणु
	वापस max3191x->mode == STATUS_BYTE_ENABLED ? 2 : 1;
पूर्ण

अटल पूर्णांक max3191x_पढ़ोout_locked(काष्ठा max3191x_chip *max3191x)
अणु
	काष्ठा device *dev = max3191x->gpio.parent;
	काष्ठा spi_device *spi = to_spi_device(dev);
	पूर्णांक val, i, ot = 0, uv1 = 0;

	val = spi_sync(spi, &max3191x->mesg);
	अगर (val) अणु
		dev_err_ratelimited(dev, "SPI receive error %d\n", val);
		वापस val;
	पूर्ण

	क्रम (i = 0; i < max3191x->nchips; i++) अणु
		अगर (max3191x->mode == STATUS_BYTE_ENABLED) अणु
			u8 in	  = ((u8 *)max3191x->xfer.rx_buf)[i * 2];
			u8 status = ((u8 *)max3191x->xfer.rx_buf)[i * 2 + 1];

			val = (status & 0xf8) != crc8(max3191x_crc8, &in, 1, 0);
			__assign_bit(i, max3191x->crc_error, val);
			अगर (val)
				dev_err_ratelimited(dev,
					"chip %d: CRC error\n", i);

			ot  = (status >> 1) & 1;
			__assign_bit(i, max3191x->overtemp, ot);
			अगर (ot)
				dev_err_ratelimited(dev,
					"chip %d: overtemperature\n", i);

			अगर (!max3191x->ignore_uv) अणु
				uv1 = !((status >> 2) & 1);
				__assign_bit(i, max3191x->undervolt1, uv1);
				अगर (uv1)
					dev_err_ratelimited(dev,
						"chip %d: undervoltage\n", i);

				val = !(status & 1);
				__assign_bit(i, max3191x->undervolt2, val);
				अगर (val && !uv1)
					dev_warn_ratelimited(dev,
						"chip %d: voltage warn\n", i);
			पूर्ण
		पूर्ण

		अगर (max3191x->fault_pins && !max3191x->ignore_uv) अणु
			/* fault pin shared by all chips or per chip */
			काष्ठा gpio_desc *fault_pin =
				(max3191x->fault_pins->ndescs == 1)
					? max3191x->fault_pins->desc[0]
					: max3191x->fault_pins->desc[i];

			val = gpiod_get_value_cansleep(fault_pin);
			अगर (val < 0) अणु
				dev_err_ratelimited(dev,
					"GPIO read error %d\n", val);
				वापस val;
			पूर्ण
			__assign_bit(i, max3191x->fault, val);
			अगर (val && !uv1 && !ot)
				dev_err_ratelimited(dev,
					"chip %d: fault\n", i);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल bool max3191x_chip_is_faulting(काष्ठा max3191x_chip *max3191x,
				      अचिन्हित पूर्णांक chipnum)
अणु
	/* without status byte the only diagnostic is the fault pin */
	अगर (!max3191x->ignore_uv && test_bit(chipnum, max3191x->fault))
		वापस true;

	अगर (max3191x->mode == STATUS_BYTE_DISABLED)
		वापस false;

	वापस test_bit(chipnum, max3191x->crc_error) ||
	       test_bit(chipnum, max3191x->overtemp)  ||
	       (!max3191x->ignore_uv &&
		test_bit(chipnum, max3191x->undervolt1));
पूर्ण

अटल पूर्णांक max3191x_get(काष्ठा gpio_chip *gpio, अचिन्हित पूर्णांक offset)
अणु
	काष्ठा max3191x_chip *max3191x = gpiochip_get_data(gpio);
	पूर्णांक ret, chipnum, wordlen = max3191x_wordlen(max3191x);
	u8 in;

	mutex_lock(&max3191x->lock);
	ret = max3191x_पढ़ोout_locked(max3191x);
	अगर (ret)
		जाओ out_unlock;

	chipnum = offset / MAX3191X_NGPIO;
	अगर (max3191x_chip_is_faulting(max3191x, chipnum)) अणु
		ret = -EIO;
		जाओ out_unlock;
	पूर्ण

	in = ((u8 *)max3191x->xfer.rx_buf)[chipnum * wordlen];
	ret = (in >> (offset % MAX3191X_NGPIO)) & 1;

out_unlock:
	mutex_unlock(&max3191x->lock);
	वापस ret;
पूर्ण

अटल पूर्णांक max3191x_get_multiple(काष्ठा gpio_chip *gpio, अचिन्हित दीर्घ *mask,
				 अचिन्हित दीर्घ *bits)
अणु
	काष्ठा max3191x_chip *max3191x = gpiochip_get_data(gpio);
	स्थिर अचिन्हित पूर्णांक wordlen = max3191x_wordlen(max3191x);
	पूर्णांक ret;
	अचिन्हित दीर्घ bit;
	अचिन्हित दीर्घ gpio_mask;
	अचिन्हित दीर्घ in;

	mutex_lock(&max3191x->lock);
	ret = max3191x_पढ़ोout_locked(max3191x);
	अगर (ret)
		जाओ out_unlock;

	biपंचांगap_zero(bits, gpio->ngpio);
	क्रम_each_set_clump8(bit, gpio_mask, mask, gpio->ngpio) अणु
		अचिन्हित पूर्णांक chipnum = bit / MAX3191X_NGPIO;

		अगर (max3191x_chip_is_faulting(max3191x, chipnum)) अणु
			ret = -EIO;
			जाओ out_unlock;
		पूर्ण

		in = ((u8 *)max3191x->xfer.rx_buf)[chipnum * wordlen];
		in &= gpio_mask;
		biपंचांगap_set_value8(bits, in, bit);
	पूर्ण

out_unlock:
	mutex_unlock(&max3191x->lock);
	वापस ret;
पूर्ण

अटल पूर्णांक max3191x_set_config(काष्ठा gpio_chip *gpio, अचिन्हित पूर्णांक offset,
			       अचिन्हित दीर्घ config)
अणु
	काष्ठा max3191x_chip *max3191x = gpiochip_get_data(gpio);
	u32 debounce, chipnum, db0_val, db1_val;

	अगर (pinconf_to_config_param(config) != PIN_CONFIG_INPUT_DEBOUNCE)
		वापस -ENOTSUPP;

	अगर (!max3191x->db0_pins || !max3191x->db1_pins)
		वापस -EINVAL;

	debounce = pinconf_to_config_argument(config);
	चयन (debounce) अणु
	हाल 0:
		db0_val = 0;
		db1_val = 0;
		अवरोध;
	हाल 1 ... 25:
		db0_val = 0;
		db1_val = 1;
		अवरोध;
	हाल 26 ... 750:
		db0_val = 1;
		db1_val = 0;
		अवरोध;
	हाल 751 ... 3000:
		db0_val = 1;
		db1_val = 1;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर (max3191x->db0_pins->ndescs == 1)
		chipnum = 0; /* all chips use the same pair of debounce pins */
	अन्यथा
		chipnum = offset / MAX3191X_NGPIO; /* per chip debounce pins */

	mutex_lock(&max3191x->lock);
	gpiod_set_value_cansleep(max3191x->db0_pins->desc[chipnum], db0_val);
	gpiod_set_value_cansleep(max3191x->db1_pins->desc[chipnum], db1_val);
	mutex_unlock(&max3191x->lock);
	वापस 0;
पूर्ण

अटल व्योम gpiod_set_array_single_value_cansleep(अचिन्हित पूर्णांक ndescs,
						  काष्ठा gpio_desc **desc,
						  काष्ठा gpio_array *info,
						  पूर्णांक value)
अणु
	अचिन्हित दीर्घ *values;

	values = biपंचांगap_alloc(ndescs, GFP_KERNEL);
	अगर (!values)
		वापस;

	अगर (value)
		biपंचांगap_fill(values, ndescs);
	अन्यथा
		biपंचांगap_zero(values, ndescs);

	gpiod_set_array_value_cansleep(ndescs, desc, info, values);
	kमुक्त(values);
पूर्ण

अटल काष्ठा gpio_descs *devm_gpiod_get_array_optional_count(
				काष्ठा device *dev, स्थिर अक्षर *con_id,
				क्रमागत gpiod_flags flags, अचिन्हित पूर्णांक expected)
अणु
	काष्ठा gpio_descs *descs;
	पूर्णांक found = gpiod_count(dev, con_id);

	अगर (found == -ENOENT)
		वापस शून्य;

	अगर (found != expected && found != 1) अणु
		dev_err(dev, "ignoring %s-gpios: found %d, expected %u or 1\n",
			con_id, found, expected);
		वापस शून्य;
	पूर्ण

	descs = devm_gpiod_get_array_optional(dev, con_id, flags);

	अगर (IS_ERR(descs)) अणु
		dev_err(dev, "failed to get %s-gpios: %ld\n",
			con_id, PTR_ERR(descs));
		वापस शून्य;
	पूर्ण

	वापस descs;
पूर्ण

अटल पूर्णांक max3191x_probe(काष्ठा spi_device *spi)
अणु
	काष्ठा device *dev = &spi->dev;
	काष्ठा max3191x_chip *max3191x;
	पूर्णांक n, ret;

	max3191x = devm_kzalloc(dev, माप(*max3191x), GFP_KERNEL);
	अगर (!max3191x)
		वापस -ENOMEM;
	spi_set_drvdata(spi, max3191x);

	max3191x->nchips = 1;
	device_property_पढ़ो_u32(dev, "#daisy-chained-devices",
				 &max3191x->nchips);

	n = BITS_TO_LONGS(max3191x->nchips);
	max3191x->crc_error   = devm_kसुस्मृति(dev, n, माप(दीर्घ), GFP_KERNEL);
	max3191x->undervolt1  = devm_kसुस्मृति(dev, n, माप(दीर्घ), GFP_KERNEL);
	max3191x->undervolt2  = devm_kसुस्मृति(dev, n, माप(दीर्घ), GFP_KERNEL);
	max3191x->overtemp    = devm_kसुस्मृति(dev, n, माप(दीर्घ), GFP_KERNEL);
	max3191x->fault       = devm_kसुस्मृति(dev, n, माप(दीर्घ), GFP_KERNEL);
	max3191x->xfer.rx_buf = devm_kसुस्मृति(dev, max3191x->nchips,
								2, GFP_KERNEL);
	अगर (!max3191x->crc_error || !max3191x->undervolt1 ||
	    !max3191x->overtemp  || !max3191x->undervolt2 ||
	    !max3191x->fault     || !max3191x->xfer.rx_buf)
		वापस -ENOMEM;

	max3191x->modesel_pins = devm_gpiod_get_array_optional_count(dev,
				 "maxim,modesel", GPIOD_ASIS, max3191x->nchips);
	max3191x->fault_pins   = devm_gpiod_get_array_optional_count(dev,
				 "maxim,fault", GPIOD_IN, max3191x->nchips);
	max3191x->db0_pins     = devm_gpiod_get_array_optional_count(dev,
				 "maxim,db0", GPIOD_OUT_LOW, max3191x->nchips);
	max3191x->db1_pins     = devm_gpiod_get_array_optional_count(dev,
				 "maxim,db1", GPIOD_OUT_LOW, max3191x->nchips);

	max3191x->mode = device_property_पढ़ो_bool(dev, "maxim,modesel-8bit")
				 ? STATUS_BYTE_DISABLED : STATUS_BYTE_ENABLED;
	अगर (max3191x->modesel_pins)
		gpiod_set_array_single_value_cansleep(
				 max3191x->modesel_pins->ndescs,
				 max3191x->modesel_pins->desc,
				 max3191x->modesel_pins->info, max3191x->mode);

	max3191x->ignore_uv = device_property_पढ़ो_bool(dev,
						  "maxim,ignore-undervoltage");

	अगर (max3191x->db0_pins && max3191x->db1_pins &&
	    max3191x->db0_pins->ndescs != max3191x->db1_pins->ndescs) अणु
		dev_err(dev, "ignoring maxim,db*-gpios: array len mismatch\n");
		devm_gpiod_put_array(dev, max3191x->db0_pins);
		devm_gpiod_put_array(dev, max3191x->db1_pins);
		max3191x->db0_pins = शून्य;
		max3191x->db1_pins = शून्य;
	पूर्ण

	max3191x->xfer.len = max3191x->nchips * max3191x_wordlen(max3191x);
	spi_message_init_with_transfers(&max3191x->mesg, &max3191x->xfer, 1);

	max3191x->gpio.label = spi->modalias;
	max3191x->gpio.owner = THIS_MODULE;
	max3191x->gpio.parent = dev;
	max3191x->gpio.base = -1;
	max3191x->gpio.ngpio = max3191x->nchips * MAX3191X_NGPIO;
	max3191x->gpio.can_sleep = true;

	max3191x->gpio.get_direction = max3191x_get_direction;
	max3191x->gpio.direction_input = max3191x_direction_input;
	max3191x->gpio.direction_output = max3191x_direction_output;
	max3191x->gpio.set = max3191x_set;
	max3191x->gpio.set_multiple = max3191x_set_multiple;
	max3191x->gpio.get = max3191x_get;
	max3191x->gpio.get_multiple = max3191x_get_multiple;
	max3191x->gpio.set_config = max3191x_set_config;

	mutex_init(&max3191x->lock);

	ret = gpiochip_add_data(&max3191x->gpio, max3191x);
	अगर (ret) अणु
		mutex_destroy(&max3191x->lock);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक max3191x_हटाओ(काष्ठा spi_device *spi)
अणु
	काष्ठा max3191x_chip *max3191x = spi_get_drvdata(spi);

	gpiochip_हटाओ(&max3191x->gpio);
	mutex_destroy(&max3191x->lock);

	वापस 0;
पूर्ण

अटल पूर्णांक __init max3191x_रेजिस्टर_driver(काष्ठा spi_driver *sdrv)
अणु
	crc8_populate_msb(max3191x_crc8, MAX3191X_CRC8_POLYNOMIAL);
	वापस spi_रेजिस्टर_driver(sdrv);
पूर्ण

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id max3191x_of_id[] = अणु
	अणु .compatible = "maxim,max31910" पूर्ण,
	अणु .compatible = "maxim,max31911" पूर्ण,
	अणु .compatible = "maxim,max31912" पूर्ण,
	अणु .compatible = "maxim,max31913" पूर्ण,
	अणु .compatible = "maxim,max31953" पूर्ण,
	अणु .compatible = "maxim,max31963" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, max3191x_of_id);
#पूर्ण_अगर

अटल स्थिर काष्ठा spi_device_id max3191x_spi_id[] = अणु
	अणु "max31910" पूर्ण,
	अणु "max31911" पूर्ण,
	अणु "max31912" पूर्ण,
	अणु "max31913" पूर्ण,
	अणु "max31953" पूर्ण,
	अणु "max31963" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(spi, max3191x_spi_id);

अटल काष्ठा spi_driver max3191x_driver = अणु
	.driver = अणु
		.name		= "max3191x",
		.of_match_table	= of_match_ptr(max3191x_of_id),
	पूर्ण,
	.probe	  = max3191x_probe,
	.हटाओ	  = max3191x_हटाओ,
	.id_table = max3191x_spi_id,
पूर्ण;
module_driver(max3191x_driver, max3191x_रेजिस्टर_driver, spi_unरेजिस्टर_driver);

MODULE_AUTHOR("Lukas Wunner <lukas@wunner.de>");
MODULE_DESCRIPTION("GPIO driver for Maxim MAX3191x industrial serializer");
MODULE_LICENSE("GPL v2");
