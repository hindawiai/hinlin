<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// Register map access API - SPMI support
//
// Copyright (c) 2012-2013, The Linux Foundation. All rights reserved.
//
// Based on regmap-i2c.c:
// Copyright 2011 Wolfson Microelectronics plc
// Author: Mark Brown <broonie@खोलोsource.wolfsonmicro.com>

#समावेश <linux/regmap.h>
#समावेश <linux/spmi.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>

अटल पूर्णांक regmap_spmi_base_पढ़ो(व्योम *context,
				 स्थिर व्योम *reg, माप_प्रकार reg_size,
				 व्योम *val, माप_प्रकार val_size)
अणु
	u8 addr = *(u8 *)reg;
	पूर्णांक err = 0;

	BUG_ON(reg_size != 1);

	जबतक (val_size-- && !err)
		err = spmi_रेजिस्टर_पढ़ो(context, addr++, val++);

	वापस err;
पूर्ण

अटल पूर्णांक regmap_spmi_base_gather_ग_लिखो(व्योम *context,
					 स्थिर व्योम *reg, माप_प्रकार reg_size,
					 स्थिर व्योम *val, माप_प्रकार val_size)
अणु
	स्थिर u8 *data = val;
	u8 addr = *(u8 *)reg;
	पूर्णांक err = 0;

	BUG_ON(reg_size != 1);

	/*
	 * SPMI defines a more bandwidth-efficient 'Register 0 Write' sequence,
	 * use it when possible.
	 */
	अगर (addr == 0 && val_size) अणु
		err = spmi_रेजिस्टर_zero_ग_लिखो(context, *data);
		अगर (err)
			जाओ err_out;

		data++;
		addr++;
		val_size--;
	पूर्ण

	जबतक (val_size) अणु
		err = spmi_रेजिस्टर_ग_लिखो(context, addr, *data);
		अगर (err)
			जाओ err_out;

		data++;
		addr++;
		val_size--;
	पूर्ण

err_out:
	वापस err;
पूर्ण

अटल पूर्णांक regmap_spmi_base_ग_लिखो(व्योम *context, स्थिर व्योम *data,
				  माप_प्रकार count)
अणु
	BUG_ON(count < 1);
	वापस regmap_spmi_base_gather_ग_लिखो(context, data, 1, data + 1,
					     count - 1);
पूर्ण

अटल स्थिर काष्ठा regmap_bus regmap_spmi_base = अणु
	.पढ़ो				= regmap_spmi_base_पढ़ो,
	.ग_लिखो				= regmap_spmi_base_ग_लिखो,
	.gather_ग_लिखो			= regmap_spmi_base_gather_ग_लिखो,
	.reg_क्रमmat_endian_शेष	= REGMAP_ENDIAN_NATIVE,
	.val_क्रमmat_endian_शेष	= REGMAP_ENDIAN_NATIVE,
पूर्ण;

काष्ठा regmap *__regmap_init_spmi_base(काष्ठा spmi_device *sdev,
				       स्थिर काष्ठा regmap_config *config,
				       काष्ठा lock_class_key *lock_key,
				       स्थिर अक्षर *lock_name)
अणु
	वापस __regmap_init(&sdev->dev, &regmap_spmi_base, sdev, config,
			     lock_key, lock_name);
पूर्ण
EXPORT_SYMBOL_GPL(__regmap_init_spmi_base);

काष्ठा regmap *__devm_regmap_init_spmi_base(काष्ठा spmi_device *sdev,
					    स्थिर काष्ठा regmap_config *config,
					    काष्ठा lock_class_key *lock_key,
					    स्थिर अक्षर *lock_name)
अणु
	वापस __devm_regmap_init(&sdev->dev, &regmap_spmi_base, sdev, config,
				  lock_key, lock_name);
पूर्ण
EXPORT_SYMBOL_GPL(__devm_regmap_init_spmi_base);

अटल पूर्णांक regmap_spmi_ext_पढ़ो(व्योम *context,
				स्थिर व्योम *reg, माप_प्रकार reg_size,
				व्योम *val, माप_प्रकार val_size)
अणु
	पूर्णांक err = 0;
	माप_प्रकार len;
	u16 addr;

	BUG_ON(reg_size != 2);

	addr = *(u16 *)reg;

	/*
	 * Split accesses पूर्णांकo two to take advantage of the more
	 * bandwidth-efficient 'Extended Register Read' command when possible
	 */
	जबतक (addr <= 0xFF && val_size) अणु
		len = min_t(माप_प्रकार, val_size, 16);

		err = spmi_ext_रेजिस्टर_पढ़ो(context, addr, val, len);
		अगर (err)
			जाओ err_out;

		addr += len;
		val += len;
		val_size -= len;
	पूर्ण

	जबतक (val_size) अणु
		len = min_t(माप_प्रकार, val_size, 8);

		err = spmi_ext_रेजिस्टर_पढ़ोl(context, addr, val, len);
		अगर (err)
			जाओ err_out;

		addr += len;
		val += len;
		val_size -= len;
	पूर्ण

err_out:
	वापस err;
पूर्ण

अटल पूर्णांक regmap_spmi_ext_gather_ग_लिखो(व्योम *context,
					स्थिर व्योम *reg, माप_प्रकार reg_size,
					स्थिर व्योम *val, माप_प्रकार val_size)
अणु
	पूर्णांक err = 0;
	माप_प्रकार len;
	u16 addr;

	BUG_ON(reg_size != 2);

	addr = *(u16 *)reg;

	जबतक (addr <= 0xFF && val_size) अणु
		len = min_t(माप_प्रकार, val_size, 16);

		err = spmi_ext_रेजिस्टर_ग_लिखो(context, addr, val, len);
		अगर (err)
			जाओ err_out;

		addr += len;
		val += len;
		val_size -= len;
	पूर्ण

	जबतक (val_size) अणु
		len = min_t(माप_प्रकार, val_size, 8);

		err = spmi_ext_रेजिस्टर_ग_लिखोl(context, addr, val, len);
		अगर (err)
			जाओ err_out;

		addr += len;
		val += len;
		val_size -= len;
	पूर्ण

err_out:
	वापस err;
पूर्ण

अटल पूर्णांक regmap_spmi_ext_ग_लिखो(व्योम *context, स्थिर व्योम *data,
				 माप_प्रकार count)
अणु
	BUG_ON(count < 2);
	वापस regmap_spmi_ext_gather_ग_लिखो(context, data, 2, data + 2,
					    count - 2);
पूर्ण

अटल स्थिर काष्ठा regmap_bus regmap_spmi_ext = अणु
	.पढ़ो				= regmap_spmi_ext_पढ़ो,
	.ग_लिखो				= regmap_spmi_ext_ग_लिखो,
	.gather_ग_लिखो			= regmap_spmi_ext_gather_ग_लिखो,
	.reg_क्रमmat_endian_शेष	= REGMAP_ENDIAN_NATIVE,
	.val_क्रमmat_endian_शेष	= REGMAP_ENDIAN_NATIVE,
पूर्ण;

काष्ठा regmap *__regmap_init_spmi_ext(काष्ठा spmi_device *sdev,
				      स्थिर काष्ठा regmap_config *config,
				      काष्ठा lock_class_key *lock_key,
				      स्थिर अक्षर *lock_name)
अणु
	वापस __regmap_init(&sdev->dev, &regmap_spmi_ext, sdev, config,
			     lock_key, lock_name);
पूर्ण
EXPORT_SYMBOL_GPL(__regmap_init_spmi_ext);

काष्ठा regmap *__devm_regmap_init_spmi_ext(काष्ठा spmi_device *sdev,
					   स्थिर काष्ठा regmap_config *config,
					   काष्ठा lock_class_key *lock_key,
					   स्थिर अक्षर *lock_name)
अणु
	वापस __devm_regmap_init(&sdev->dev, &regmap_spmi_ext, sdev, config,
				  lock_key, lock_name);
पूर्ण
EXPORT_SYMBOL_GPL(__devm_regmap_init_spmi_ext);

MODULE_LICENSE("GPL");
