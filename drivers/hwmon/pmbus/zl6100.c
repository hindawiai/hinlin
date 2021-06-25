<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Hardware monitoring driver क्रम ZL6100 and compatibles
 *
 * Copyright (c) 2011 Ericsson AB.
 * Copyright (c) 2012 Guenter Roeck
 */

#समावेश <linux/bitops.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/err.h>
#समावेश <linux/slab.h>
#समावेश <linux/i2c.h>
#समावेश <linux/kसमय.स>
#समावेश <linux/delay.h>
#समावेश "pmbus.h"

क्रमागत chips अणु zl2004, zl2005, zl2006, zl2008, zl2105, zl2106, zl6100, zl6105,
	     zl9101, zl9117 पूर्ण;

काष्ठा zl6100_data अणु
	पूर्णांक id;
	kसमय_प्रकार access;		/* chip access समय */
	पूर्णांक delay;		/* Delay between chip accesses in uS */
	काष्ठा pmbus_driver_info info;
पूर्ण;

#घोषणा to_zl6100_data(x)  container_of(x, काष्ठा zl6100_data, info)

#घोषणा ZL6100_MFR_CONFIG		0xd0
#घोषणा ZL6100_DEVICE_ID		0xe4

#घोषणा ZL6100_MFR_XTEMP_ENABLE		BIT(7)

#घोषणा MFR_VMON_OV_FAULT_LIMIT		0xf5
#घोषणा MFR_VMON_UV_FAULT_LIMIT		0xf6
#घोषणा MFR_READ_VMON			0xf7

#घोषणा VMON_UV_WARNING			BIT(5)
#घोषणा VMON_OV_WARNING			BIT(4)
#घोषणा VMON_UV_FAULT			BIT(1)
#घोषणा VMON_OV_FAULT			BIT(0)

#घोषणा ZL6100_WAIT_TIME		1000	/* uS	*/

अटल uलघु delay = ZL6100_WAIT_TIME;
module_param(delay, uलघु, 0644);
MODULE_PARM_DESC(delay, "Delay between chip accesses in uS");

/* Convert linear sensor value to milli-units */
अटल दीर्घ zl6100_l2d(s16 l)
अणु
	s16 exponent;
	s32 mantissa;
	दीर्घ val;

	exponent = l >> 11;
	mantissa = ((s16)((l & 0x7ff) << 5)) >> 5;

	val = mantissa;

	/* scale result to milli-units */
	val = val * 1000L;

	अगर (exponent >= 0)
		val <<= exponent;
	अन्यथा
		val >>= -exponent;

	वापस val;
पूर्ण

#घोषणा MAX_MANTISSA	(1023 * 1000)
#घोषणा MIN_MANTISSA	(511 * 1000)

अटल u16 zl6100_d2l(दीर्घ val)
अणु
	s16 exponent = 0, mantissa;
	bool negative = false;

	/* simple हाल */
	अगर (val == 0)
		वापस 0;

	अगर (val < 0) अणु
		negative = true;
		val = -val;
	पूर्ण

	/* Reduce large mantissa until it fits पूर्णांकo 10 bit */
	जबतक (val >= MAX_MANTISSA && exponent < 15) अणु
		exponent++;
		val >>= 1;
	पूर्ण
	/* Increase small mantissa to improve precision */
	जबतक (val < MIN_MANTISSA && exponent > -15) अणु
		exponent--;
		val <<= 1;
	पूर्ण

	/* Convert mantissa from milli-units to units */
	mantissa = DIV_ROUND_CLOSEST(val, 1000);

	/* Ensure that resulting number is within range */
	अगर (mantissa > 0x3ff)
		mantissa = 0x3ff;

	/* restore sign */
	अगर (negative)
		mantissa = -mantissa;

	/* Convert to 5 bit exponent, 11 bit mantissa */
	वापस (mantissa & 0x7ff) | ((exponent << 11) & 0xf800);
पूर्ण

/* Some chips need a delay between accesses */
अटल अंतरभूत व्योम zl6100_रुको(स्थिर काष्ठा zl6100_data *data)
अणु
	अगर (data->delay) अणु
		s64 delta = kसमय_us_delta(kसमय_get(), data->access);
		अगर (delta < data->delay)
			udelay(data->delay - delta);
	पूर्ण
पूर्ण

अटल पूर्णांक zl6100_पढ़ो_word_data(काष्ठा i2c_client *client, पूर्णांक page,
				 पूर्णांक phase, पूर्णांक reg)
अणु
	स्थिर काष्ठा pmbus_driver_info *info = pmbus_get_driver_info(client);
	काष्ठा zl6100_data *data = to_zl6100_data(info);
	पूर्णांक ret, vreg;

	अगर (page > 0)
		वापस -ENXIO;

	अगर (data->id == zl2005) अणु
		/*
		 * Limit रेजिस्टर detection is not reliable on ZL2005.
		 * Make sure रेजिस्टरs are not erroneously detected.
		 */
		चयन (reg) अणु
		हाल PMBUS_VOUT_OV_WARN_LIMIT:
		हाल PMBUS_VOUT_UV_WARN_LIMIT:
		हाल PMBUS_IOUT_OC_WARN_LIMIT:
			वापस -ENXIO;
		पूर्ण
	पूर्ण

	चयन (reg) अणु
	हाल PMBUS_VIRT_READ_VMON:
		vreg = MFR_READ_VMON;
		अवरोध;
	हाल PMBUS_VIRT_VMON_OV_WARN_LIMIT:
	हाल PMBUS_VIRT_VMON_OV_FAULT_LIMIT:
		vreg = MFR_VMON_OV_FAULT_LIMIT;
		अवरोध;
	हाल PMBUS_VIRT_VMON_UV_WARN_LIMIT:
	हाल PMBUS_VIRT_VMON_UV_FAULT_LIMIT:
		vreg = MFR_VMON_UV_FAULT_LIMIT;
		अवरोध;
	शेष:
		अगर (reg >= PMBUS_VIRT_BASE)
			वापस -ENXIO;
		vreg = reg;
		अवरोध;
	पूर्ण

	zl6100_रुको(data);
	ret = pmbus_पढ़ो_word_data(client, page, phase, vreg);
	data->access = kसमय_get();
	अगर (ret < 0)
		वापस ret;

	चयन (reg) अणु
	हाल PMBUS_VIRT_VMON_OV_WARN_LIMIT:
		ret = zl6100_d2l(DIV_ROUND_CLOSEST(zl6100_l2d(ret) * 9, 10));
		अवरोध;
	हाल PMBUS_VIRT_VMON_UV_WARN_LIMIT:
		ret = zl6100_d2l(DIV_ROUND_CLOSEST(zl6100_l2d(ret) * 11, 10));
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक zl6100_पढ़ो_byte_data(काष्ठा i2c_client *client, पूर्णांक page, पूर्णांक reg)
अणु
	स्थिर काष्ठा pmbus_driver_info *info = pmbus_get_driver_info(client);
	काष्ठा zl6100_data *data = to_zl6100_data(info);
	पूर्णांक ret, status;

	अगर (page > 0)
		वापस -ENXIO;

	zl6100_रुको(data);

	चयन (reg) अणु
	हाल PMBUS_VIRT_STATUS_VMON:
		ret = pmbus_पढ़ो_byte_data(client, 0,
					   PMBUS_STATUS_MFR_SPECIFIC);
		अगर (ret < 0)
			अवरोध;

		status = 0;
		अगर (ret & VMON_UV_WARNING)
			status |= PB_VOLTAGE_UV_WARNING;
		अगर (ret & VMON_OV_WARNING)
			status |= PB_VOLTAGE_OV_WARNING;
		अगर (ret & VMON_UV_FAULT)
			status |= PB_VOLTAGE_UV_FAULT;
		अगर (ret & VMON_OV_FAULT)
			status |= PB_VOLTAGE_OV_FAULT;
		ret = status;
		अवरोध;
	शेष:
		ret = pmbus_पढ़ो_byte_data(client, page, reg);
		अवरोध;
	पूर्ण
	data->access = kसमय_get();

	वापस ret;
पूर्ण

अटल पूर्णांक zl6100_ग_लिखो_word_data(काष्ठा i2c_client *client, पूर्णांक page, पूर्णांक reg,
				  u16 word)
अणु
	स्थिर काष्ठा pmbus_driver_info *info = pmbus_get_driver_info(client);
	काष्ठा zl6100_data *data = to_zl6100_data(info);
	पूर्णांक ret, vreg;

	अगर (page > 0)
		वापस -ENXIO;

	चयन (reg) अणु
	हाल PMBUS_VIRT_VMON_OV_WARN_LIMIT:
		word = zl6100_d2l(DIV_ROUND_CLOSEST(zl6100_l2d(word) * 10, 9));
		vreg = MFR_VMON_OV_FAULT_LIMIT;
		pmbus_clear_cache(client);
		अवरोध;
	हाल PMBUS_VIRT_VMON_OV_FAULT_LIMIT:
		vreg = MFR_VMON_OV_FAULT_LIMIT;
		pmbus_clear_cache(client);
		अवरोध;
	हाल PMBUS_VIRT_VMON_UV_WARN_LIMIT:
		word = zl6100_d2l(DIV_ROUND_CLOSEST(zl6100_l2d(word) * 10, 11));
		vreg = MFR_VMON_UV_FAULT_LIMIT;
		pmbus_clear_cache(client);
		अवरोध;
	हाल PMBUS_VIRT_VMON_UV_FAULT_LIMIT:
		vreg = MFR_VMON_UV_FAULT_LIMIT;
		pmbus_clear_cache(client);
		अवरोध;
	शेष:
		अगर (reg >= PMBUS_VIRT_BASE)
			वापस -ENXIO;
		vreg = reg;
	पूर्ण

	zl6100_रुको(data);
	ret = pmbus_ग_लिखो_word_data(client, page, vreg, word);
	data->access = kसमय_get();

	वापस ret;
पूर्ण

अटल पूर्णांक zl6100_ग_लिखो_byte(काष्ठा i2c_client *client, पूर्णांक page, u8 value)
अणु
	स्थिर काष्ठा pmbus_driver_info *info = pmbus_get_driver_info(client);
	काष्ठा zl6100_data *data = to_zl6100_data(info);
	पूर्णांक ret;

	अगर (page > 0)
		वापस -ENXIO;

	zl6100_रुको(data);
	ret = pmbus_ग_लिखो_byte(client, page, value);
	data->access = kसमय_get();

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id zl6100_id[] = अणु
	अणु"bmr450", zl2005पूर्ण,
	अणु"bmr451", zl2005पूर्ण,
	अणु"bmr462", zl2008पूर्ण,
	अणु"bmr463", zl2008पूर्ण,
	अणु"bmr464", zl2008पूर्ण,
	अणु"zl2004", zl2004पूर्ण,
	अणु"zl2005", zl2005पूर्ण,
	अणु"zl2006", zl2006पूर्ण,
	अणु"zl2008", zl2008पूर्ण,
	अणु"zl2105", zl2105पूर्ण,
	अणु"zl2106", zl2106पूर्ण,
	अणु"zl6100", zl6100पूर्ण,
	अणु"zl6105", zl6105पूर्ण,
	अणु"zl9101", zl9101पूर्ण,
	अणु"zl9117", zl9117पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, zl6100_id);

अटल पूर्णांक zl6100_probe(काष्ठा i2c_client *client)
अणु
	पूर्णांक ret;
	काष्ठा zl6100_data *data;
	काष्ठा pmbus_driver_info *info;
	u8 device_id[I2C_SMBUS_BLOCK_MAX + 1];
	स्थिर काष्ठा i2c_device_id *mid;

	अगर (!i2c_check_functionality(client->adapter,
				     I2C_FUNC_SMBUS_READ_WORD_DATA
				     | I2C_FUNC_SMBUS_READ_BLOCK_DATA))
		वापस -ENODEV;

	ret = i2c_smbus_पढ़ो_block_data(client, ZL6100_DEVICE_ID,
					device_id);
	अगर (ret < 0) अणु
		dev_err(&client->dev, "Failed to read device ID\n");
		वापस ret;
	पूर्ण
	device_id[ret] = '\0';
	dev_info(&client->dev, "Device ID %s\n", device_id);

	mid = शून्य;
	क्रम (mid = zl6100_id; mid->name[0]; mid++) अणु
		अगर (!strnहालcmp(mid->name, device_id, म_माप(mid->name)))
			अवरोध;
	पूर्ण
	अगर (!mid->name[0]) अणु
		dev_err(&client->dev, "Unsupported device\n");
		वापस -ENODEV;
	पूर्ण
	अगर (म_भेद(client->name, mid->name) != 0)
		dev_notice(&client->dev,
			   "Device mismatch: Configured %s, detected %s\n",
			   client->name, mid->name);

	data = devm_kzalloc(&client->dev, माप(काष्ठा zl6100_data),
			    GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	data->id = mid->driver_data;

	/*
	 * According to inक्रमmation from the chip venकरोr, all currently
	 * supported chips are known to require a रुको समय between I2C
	 * accesses.
	 */
	data->delay = delay;

	/*
	 * Since there was a direct I2C device access above, रुको beक्रमe
	 * accessing the chip again.
	 */
	data->access = kसमय_get();
	zl6100_रुको(data);

	info = &data->info;

	info->pages = 1;
	info->func[0] = PMBUS_HAVE_VIN | PMBUS_HAVE_STATUS_INPUT
	  | PMBUS_HAVE_VOUT | PMBUS_HAVE_STATUS_VOUT
	  | PMBUS_HAVE_IOUT | PMBUS_HAVE_STATUS_IOUT
	  | PMBUS_HAVE_TEMP | PMBUS_HAVE_STATUS_TEMP;

	/*
	 * ZL2004, ZL9101M, and ZL9117M support monitoring an extra voltage
	 * (VMON क्रम ZL2004, VDRV क्रम ZL9101M and ZL9117M). Report it as vmon.
	 */
	अगर (data->id == zl2004 || data->id == zl9101 || data->id == zl9117)
		info->func[0] |= PMBUS_HAVE_VMON | PMBUS_HAVE_STATUS_VMON;

	ret = i2c_smbus_पढ़ो_word_data(client, ZL6100_MFR_CONFIG);
	अगर (ret < 0)
		वापस ret;

	अगर (ret & ZL6100_MFR_XTEMP_ENABLE)
		info->func[0] |= PMBUS_HAVE_TEMP2;

	data->access = kसमय_get();
	zl6100_रुको(data);

	info->पढ़ो_word_data = zl6100_पढ़ो_word_data;
	info->पढ़ो_byte_data = zl6100_पढ़ो_byte_data;
	info->ग_लिखो_word_data = zl6100_ग_लिखो_word_data;
	info->ग_लिखो_byte = zl6100_ग_लिखो_byte;

	वापस pmbus_करो_probe(client, info);
पूर्ण

अटल काष्ठा i2c_driver zl6100_driver = अणु
	.driver = अणु
		   .name = "zl6100",
		   पूर्ण,
	.probe_new = zl6100_probe,
	.id_table = zl6100_id,
पूर्ण;

module_i2c_driver(zl6100_driver);

MODULE_AUTHOR("Guenter Roeck");
MODULE_DESCRIPTION("PMBus driver for ZL6100 and compatibles");
MODULE_LICENSE("GPL");
MODULE_IMPORT_NS(PMBUS);
