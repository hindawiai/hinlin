<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Hardware monitoring driver क्रम the STPDDC60 controller
 *
 * Copyright (c) 2021 Flextronics International Sweden AB.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/err.h>
#समावेश <linux/i2c.h>
#समावेश <linux/pmbus.h>
#समावेश "pmbus.h"

#घोषणा STPDDC60_MFR_READ_VOUT		0xd2
#घोषणा STPDDC60_MFR_OV_LIMIT_OFFSET	0xe5
#घोषणा STPDDC60_MFR_UV_LIMIT_OFFSET	0xe6

अटल स्थिर काष्ठा i2c_device_id stpddc60_id[] = अणु
	अणु"stpddc60", 0पूर्ण,
	अणु"bmr481", 0पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, stpddc60_id);

अटल काष्ठा pmbus_driver_info stpddc60_info = अणु
	.pages = 1,
	.func[0] = PMBUS_HAVE_VOUT | PMBUS_HAVE_STATUS_VOUT
		| PMBUS_HAVE_VIN | PMBUS_HAVE_STATUS_INPUT
		| PMBUS_HAVE_TEMP | PMBUS_HAVE_STATUS_TEMP
		| PMBUS_HAVE_IOUT | PMBUS_HAVE_STATUS_IOUT
		| PMBUS_HAVE_POUT,
पूर्ण;

/*
 * Calculate the बंदst असलolute offset between commanded vout value
 * and limit value in steps of 50mv in the range 0 (50mv) to 7 (400mv).
 * Return 0 अगर the upper limit is lower than vout or अगर the lower limit
 * is higher than vout.
 */
अटल u8 stpddc60_get_offset(पूर्णांक vout, u16 limit, bool over)
अणु
	पूर्णांक offset;
	दीर्घ v, l;

	v = 250 + (vout - 1) * 5; /* Convert VID to mv */
	l = (limit * 1000L) >> 8; /* Convert LINEAR to mv */

	अगर (over == (l < v))
		वापस 0;

	offset = DIV_ROUND_CLOSEST(असल(l - v), 50);

	अगर (offset > 0)
		offset--;

	वापस clamp_val(offset, 0, 7);
पूर्ण

/*
 * Adjust the linear क्रमmat word to use the given fixed exponent.
 */
अटल u16 stpddc60_adjust_linear(u16 word, s16 fixed)
अणु
	s16 e, m, d;

	e = ((s16)word) >> 11;
	m = ((s16)((word & 0x7ff) << 5)) >> 5;
	d = e - fixed;

	अगर (d >= 0)
		m <<= d;
	अन्यथा
		m >>= -d;

	वापस clamp_val(m, 0, 0x3ff) | ((fixed << 11) & 0xf800);
पूर्ण

/*
 * The VOUT_COMMAND रेजिस्टर uses the VID क्रमmat but the vout alarm limit
 * रेजिस्टरs use the LINEAR क्रमmat so we override VOUT_MODE here to क्रमce
 * LINEAR क्रमmat क्रम all रेजिस्टरs.
 */
अटल पूर्णांक stpddc60_पढ़ो_byte_data(काष्ठा i2c_client *client, पूर्णांक page, पूर्णांक reg)
अणु
	पूर्णांक ret;

	अगर (page > 0)
		वापस -ENXIO;

	चयन (reg) अणु
	हाल PMBUS_VOUT_MODE:
		ret = 0x18;
		अवरोध;
	शेष:
		ret = -ENODATA;
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

/*
 * The vout related रेजिस्टरs वापस values in LINEAR11 क्रमmat when LINEAR16
 * is expected. Clear the top 5 bits to set the exponent part to zero to
 * convert the value to LINEAR16 क्रमmat.
 */
अटल पूर्णांक stpddc60_पढ़ो_word_data(काष्ठा i2c_client *client, पूर्णांक page,
				   पूर्णांक phase, पूर्णांक reg)
अणु
	पूर्णांक ret;

	अगर (page > 0)
		वापस -ENXIO;

	चयन (reg) अणु
	हाल PMBUS_READ_VOUT:
		ret = pmbus_पढ़ो_word_data(client, page, phase,
					   STPDDC60_MFR_READ_VOUT);
		अगर (ret < 0)
			वापस ret;
		ret &= 0x7ff;
		अवरोध;
	हाल PMBUS_VOUT_OV_FAULT_LIMIT:
	हाल PMBUS_VOUT_UV_FAULT_LIMIT:
		ret = pmbus_पढ़ो_word_data(client, page, phase, reg);
		अगर (ret < 0)
			वापस ret;
		ret &= 0x7ff;
		अवरोध;
	शेष:
		ret = -ENODATA;
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

/*
 * The vout under- and over-voltage limits are set as an offset relative to
 * the commanded vout voltage. The vin, iout, pout and temp limits must use
 * the same fixed exponent the chip uses to encode the data when पढ़ो.
 */
अटल पूर्णांक stpddc60_ग_लिखो_word_data(काष्ठा i2c_client *client, पूर्णांक page,
				    पूर्णांक reg, u16 word)
अणु
	पूर्णांक ret;
	u8 offset;

	अगर (page > 0)
		वापस -ENXIO;

	चयन (reg) अणु
	हाल PMBUS_VOUT_OV_FAULT_LIMIT:
		ret = pmbus_पढ़ो_word_data(client, page, 0xff,
					   PMBUS_VOUT_COMMAND);
		अगर (ret < 0)
			वापस ret;
		offset = stpddc60_get_offset(ret, word, true);
		ret = pmbus_ग_लिखो_byte_data(client, page,
					    STPDDC60_MFR_OV_LIMIT_OFFSET,
					    offset);
		अवरोध;
	हाल PMBUS_VOUT_UV_FAULT_LIMIT:
		ret = pmbus_पढ़ो_word_data(client, page, 0xff,
					   PMBUS_VOUT_COMMAND);
		अगर (ret < 0)
			वापस ret;
		offset = stpddc60_get_offset(ret, word, false);
		ret = pmbus_ग_लिखो_byte_data(client, page,
					    STPDDC60_MFR_UV_LIMIT_OFFSET,
					    offset);
		अवरोध;
	हाल PMBUS_VIN_OV_FAULT_LIMIT:
	हाल PMBUS_VIN_UV_FAULT_LIMIT:
	हाल PMBUS_OT_FAULT_LIMIT:
	हाल PMBUS_OT_WARN_LIMIT:
	हाल PMBUS_IOUT_OC_FAULT_LIMIT:
	हाल PMBUS_IOUT_OC_WARN_LIMIT:
	हाल PMBUS_POUT_OP_FAULT_LIMIT:
		ret = pmbus_पढ़ो_word_data(client, page, 0xff, reg);
		अगर (ret < 0)
			वापस ret;
		word = stpddc60_adjust_linear(word, ret >> 11);
		ret = pmbus_ग_लिखो_word_data(client, page, reg, word);
		अवरोध;
	शेष:
		ret = -ENODATA;
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक stpddc60_probe(काष्ठा i2c_client *client)
अणु
	पूर्णांक status;
	u8 device_id[I2C_SMBUS_BLOCK_MAX + 1];
	स्थिर काष्ठा i2c_device_id *mid;
	काष्ठा pmbus_driver_info *info = &stpddc60_info;

	अगर (!i2c_check_functionality(client->adapter,
				     I2C_FUNC_SMBUS_READ_BYTE_DATA
				     | I2C_FUNC_SMBUS_BLOCK_DATA))
		वापस -ENODEV;

	status = i2c_smbus_पढ़ो_block_data(client, PMBUS_MFR_MODEL, device_id);
	अगर (status < 0) अणु
		dev_err(&client->dev, "Failed to read Manufacturer Model\n");
		वापस status;
	पूर्ण
	क्रम (mid = stpddc60_id; mid->name[0]; mid++) अणु
		अगर (!strnहालcmp(mid->name, device_id, म_माप(mid->name)))
			अवरोध;
	पूर्ण
	अगर (!mid->name[0]) अणु
		dev_err(&client->dev, "Unsupported device\n");
		वापस -ENODEV;
	पूर्ण

	info->पढ़ो_byte_data = stpddc60_पढ़ो_byte_data;
	info->पढ़ो_word_data = stpddc60_पढ़ो_word_data;
	info->ग_लिखो_word_data = stpddc60_ग_लिखो_word_data;

	status = pmbus_करो_probe(client, info);
	अगर (status < 0)
		वापस status;

	pmbus_set_update(client, PMBUS_VOUT_OV_FAULT_LIMIT, true);
	pmbus_set_update(client, PMBUS_VOUT_UV_FAULT_LIMIT, true);

	वापस 0;
पूर्ण

अटल काष्ठा i2c_driver stpddc60_driver = अणु
	.driver = अणु
		   .name = "stpddc60",
		   पूर्ण,
	.probe_new = stpddc60_probe,
	.id_table = stpddc60_id,
पूर्ण;

module_i2c_driver(stpddc60_driver);

MODULE_AUTHOR("Erik Rosen <erik.rosen@metormote.com>");
MODULE_DESCRIPTION("PMBus driver for ST STPDDC60");
MODULE_LICENSE("GPL");
MODULE_IMPORT_NS(PMBUS);
