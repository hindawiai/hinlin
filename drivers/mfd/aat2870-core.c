<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * linux/drivers/mfd/aat2870-core.c
 *
 * Copyright (c) 2011, NVIDIA Corporation.
 * Author: Jin Park <jinyoungp@nvidia.com>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/slab.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/i2c.h>
#समावेश <linux/delay.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/mfd/core.h>
#समावेश <linux/mfd/aat2870.h>
#समावेश <linux/regulator/machine.h>

अटल काष्ठा aat2870_रेजिस्टर aat2870_regs[AAT2870_REG_NUM] = अणु
	/* पढ़ोable, ग_लिखोable, value */
	अणु 0, 1, 0x00 पूर्ण,	/* 0x00 AAT2870_BL_CH_EN */
	अणु 0, 1, 0x16 पूर्ण,	/* 0x01 AAT2870_BLM */
	अणु 0, 1, 0x16 पूर्ण,	/* 0x02 AAT2870_BLS */
	अणु 0, 1, 0x56 पूर्ण,	/* 0x03 AAT2870_BL1 */
	अणु 0, 1, 0x56 पूर्ण,	/* 0x04 AAT2870_BL2 */
	अणु 0, 1, 0x56 पूर्ण,	/* 0x05 AAT2870_BL3 */
	अणु 0, 1, 0x56 पूर्ण,	/* 0x06 AAT2870_BL4 */
	अणु 0, 1, 0x56 पूर्ण,	/* 0x07 AAT2870_BL5 */
	अणु 0, 1, 0x56 पूर्ण,	/* 0x08 AAT2870_BL6 */
	अणु 0, 1, 0x56 पूर्ण,	/* 0x09 AAT2870_BL7 */
	अणु 0, 1, 0x56 पूर्ण,	/* 0x0A AAT2870_BL8 */
	अणु 0, 1, 0x00 पूर्ण,	/* 0x0B AAT2870_FLR */
	अणु 0, 1, 0x03 पूर्ण,	/* 0x0C AAT2870_FM */
	अणु 0, 1, 0x03 पूर्ण,	/* 0x0D AAT2870_FS */
	अणु 0, 1, 0x10 पूर्ण,	/* 0x0E AAT2870_ALS_CFG0 */
	अणु 0, 1, 0x06 पूर्ण,	/* 0x0F AAT2870_ALS_CFG1 */
	अणु 0, 1, 0x00 पूर्ण,	/* 0x10 AAT2870_ALS_CFG2 */
	अणु 1, 0, 0x00 पूर्ण,	/* 0x11 AAT2870_AMB */
	अणु 0, 1, 0x00 पूर्ण,	/* 0x12 AAT2870_ALS0 */
	अणु 0, 1, 0x00 पूर्ण,	/* 0x13 AAT2870_ALS1 */
	अणु 0, 1, 0x00 पूर्ण,	/* 0x14 AAT2870_ALS2 */
	अणु 0, 1, 0x00 पूर्ण,	/* 0x15 AAT2870_ALS3 */
	अणु 0, 1, 0x00 पूर्ण,	/* 0x16 AAT2870_ALS4 */
	अणु 0, 1, 0x00 पूर्ण,	/* 0x17 AAT2870_ALS5 */
	अणु 0, 1, 0x00 पूर्ण,	/* 0x18 AAT2870_ALS6 */
	अणु 0, 1, 0x00 पूर्ण,	/* 0x19 AAT2870_ALS7 */
	अणु 0, 1, 0x00 पूर्ण,	/* 0x1A AAT2870_ALS8 */
	अणु 0, 1, 0x00 पूर्ण,	/* 0x1B AAT2870_ALS9 */
	अणु 0, 1, 0x00 पूर्ण,	/* 0x1C AAT2870_ALSA */
	अणु 0, 1, 0x00 पूर्ण,	/* 0x1D AAT2870_ALSB */
	अणु 0, 1, 0x00 पूर्ण,	/* 0x1E AAT2870_ALSC */
	अणु 0, 1, 0x00 पूर्ण,	/* 0x1F AAT2870_ALSD */
	अणु 0, 1, 0x00 पूर्ण,	/* 0x20 AAT2870_ALSE */
	अणु 0, 1, 0x00 पूर्ण,	/* 0x21 AAT2870_ALSF */
	अणु 0, 1, 0x00 पूर्ण,	/* 0x22 AAT2870_SUB_SET */
	अणु 0, 1, 0x00 पूर्ण,	/* 0x23 AAT2870_SUB_CTRL */
	अणु 0, 1, 0x00 पूर्ण,	/* 0x24 AAT2870_LDO_AB */
	अणु 0, 1, 0x00 पूर्ण,	/* 0x25 AAT2870_LDO_CD */
	अणु 0, 1, 0x00 पूर्ण,	/* 0x26 AAT2870_LDO_EN */
पूर्ण;

अटल काष्ठा mfd_cell aat2870_devs[] = अणु
	अणु
		.name = "aat2870-backlight",
		.id = AAT2870_ID_BL,
		.pdata_size = माप(काष्ठा aat2870_bl_platक्रमm_data),
	पूर्ण,
	अणु
		.name = "aat2870-regulator",
		.id = AAT2870_ID_LDOA,
		.pdata_size = माप(काष्ठा regulator_init_data),
	पूर्ण,
	अणु
		.name = "aat2870-regulator",
		.id = AAT2870_ID_LDOB,
		.pdata_size = माप(काष्ठा regulator_init_data),
	पूर्ण,
	अणु
		.name = "aat2870-regulator",
		.id = AAT2870_ID_LDOC,
		.pdata_size = माप(काष्ठा regulator_init_data),
	पूर्ण,
	अणु
		.name = "aat2870-regulator",
		.id = AAT2870_ID_LDOD,
		.pdata_size = माप(काष्ठा regulator_init_data),
	पूर्ण,
पूर्ण;

अटल पूर्णांक __aat2870_पढ़ो(काष्ठा aat2870_data *aat2870, u8 addr, u8 *val)
अणु
	पूर्णांक ret;

	अगर (addr >= AAT2870_REG_NUM) अणु
		dev_err(aat2870->dev, "Invalid address, 0x%02x\n", addr);
		वापस -EINVAL;
	पूर्ण

	अगर (!aat2870->reg_cache[addr].पढ़ोable) अणु
		*val = aat2870->reg_cache[addr].value;
		जाओ out;
	पूर्ण

	ret = i2c_master_send(aat2870->client, &addr, 1);
	अगर (ret < 0)
		वापस ret;
	अगर (ret != 1)
		वापस -EIO;

	ret = i2c_master_recv(aat2870->client, val, 1);
	अगर (ret < 0)
		वापस ret;
	अगर (ret != 1)
		वापस -EIO;

out:
	dev_dbg(aat2870->dev, "read: addr=0x%02x, val=0x%02x\n", addr, *val);
	वापस 0;
पूर्ण

अटल पूर्णांक __aat2870_ग_लिखो(काष्ठा aat2870_data *aat2870, u8 addr, u8 val)
अणु
	u8 msg[2];
	पूर्णांक ret;

	अगर (addr >= AAT2870_REG_NUM) अणु
		dev_err(aat2870->dev, "Invalid address, 0x%02x\n", addr);
		वापस -EINVAL;
	पूर्ण

	अगर (!aat2870->reg_cache[addr].ग_लिखोable) अणु
		dev_err(aat2870->dev, "Address 0x%02x is not writeable\n",
			addr);
		वापस -EINVAL;
	पूर्ण

	msg[0] = addr;
	msg[1] = val;
	ret = i2c_master_send(aat2870->client, msg, 2);
	अगर (ret < 0)
		वापस ret;
	अगर (ret != 2)
		वापस -EIO;

	aat2870->reg_cache[addr].value = val;

	dev_dbg(aat2870->dev, "write: addr=0x%02x, val=0x%02x\n", addr, val);
	वापस 0;
पूर्ण

अटल पूर्णांक aat2870_पढ़ो(काष्ठा aat2870_data *aat2870, u8 addr, u8 *val)
अणु
	पूर्णांक ret;

	mutex_lock(&aat2870->io_lock);
	ret = __aat2870_पढ़ो(aat2870, addr, val);
	mutex_unlock(&aat2870->io_lock);

	वापस ret;
पूर्ण

अटल पूर्णांक aat2870_ग_लिखो(काष्ठा aat2870_data *aat2870, u8 addr, u8 val)
अणु
	पूर्णांक ret;

	mutex_lock(&aat2870->io_lock);
	ret = __aat2870_ग_लिखो(aat2870, addr, val);
	mutex_unlock(&aat2870->io_lock);

	वापस ret;
पूर्ण

अटल पूर्णांक aat2870_update(काष्ठा aat2870_data *aat2870, u8 addr, u8 mask,
			  u8 val)
अणु
	पूर्णांक change;
	u8 old_val, new_val;
	पूर्णांक ret;

	mutex_lock(&aat2870->io_lock);

	ret = __aat2870_पढ़ो(aat2870, addr, &old_val);
	अगर (ret)
		जाओ out_unlock;

	new_val = (old_val & ~mask) | (val & mask);
	change = old_val != new_val;
	अगर (change)
		ret = __aat2870_ग_लिखो(aat2870, addr, new_val);

out_unlock:
	mutex_unlock(&aat2870->io_lock);

	वापस ret;
पूर्ण

अटल अंतरभूत व्योम aat2870_enable(काष्ठा aat2870_data *aat2870)
अणु
	अगर (aat2870->en_pin >= 0)
		gpio_set_value(aat2870->en_pin, 1);

	aat2870->is_enable = 1;
पूर्ण

अटल अंतरभूत व्योम aat2870_disable(काष्ठा aat2870_data *aat2870)
अणु
	अगर (aat2870->en_pin >= 0)
		gpio_set_value(aat2870->en_pin, 0);

	aat2870->is_enable = 0;
पूर्ण

#अगर_घोषित CONFIG_DEBUG_FS
अटल sमाप_प्रकार aat2870_dump_reg(काष्ठा aat2870_data *aat2870, अक्षर *buf)
अणु
	u8 addr, val;
	sमाप_प्रकार count = 0;
	पूर्णांक ret;

	count += प्र_लिखो(buf, "aat2870 registers\n");
	क्रम (addr = 0; addr < AAT2870_REG_NUM; addr++) अणु
		count += snम_लिखो(buf + count, PAGE_SIZE - count, "0x%02x: ", addr);
		अगर (count >= PAGE_SIZE - 1)
			अवरोध;

		ret = aat2870->पढ़ो(aat2870, addr, &val);
		अगर (ret == 0)
			count += snम_लिखो(buf + count, PAGE_SIZE - count,
					  "0x%02x", val);
		अन्यथा
			count += snम_लिखो(buf + count, PAGE_SIZE - count,
					  "<read fail: %d>", ret);

		अगर (count >= PAGE_SIZE - 1)
			अवरोध;

		count += snम_लिखो(buf + count, PAGE_SIZE - count, "\n");
		अगर (count >= PAGE_SIZE - 1)
			अवरोध;
	पूर्ण

	/* Truncate count; min() would cause a warning */
	अगर (count >= PAGE_SIZE)
		count = PAGE_SIZE - 1;

	वापस count;
पूर्ण

अटल sमाप_प्रकार aat2870_reg_पढ़ो_file(काष्ठा file *file, अक्षर __user *user_buf,
				     माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा aat2870_data *aat2870 = file->निजी_data;
	अक्षर *buf;
	sमाप_प्रकार ret;

	buf = kदो_स्मृति(PAGE_SIZE, GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;

	ret = aat2870_dump_reg(aat2870, buf);
	अगर (ret >= 0)
		ret = simple_पढ़ो_from_buffer(user_buf, count, ppos, buf, ret);

	kमुक्त(buf);

	वापस ret;
पूर्ण

अटल sमाप_प्रकार aat2870_reg_ग_लिखो_file(काष्ठा file *file,
				      स्थिर अक्षर __user *user_buf, माप_प्रकार count,
				      loff_t *ppos)
अणु
	काष्ठा aat2870_data *aat2870 = file->निजी_data;
	अक्षर buf[32];
	sमाप_प्रकार buf_size;
	अक्षर *start = buf;
	अचिन्हित दीर्घ addr, val;
	पूर्णांक ret;

	buf_size = min(count, (माप_प्रकार)(माप(buf)-1));
	अगर (copy_from_user(buf, user_buf, buf_size)) अणु
		dev_err(aat2870->dev, "Failed to copy from user\n");
		वापस -EFAULT;
	पूर्ण
	buf[buf_size] = 0;

	जबतक (*start == ' ')
		start++;

	ret = kम_से_अदीर्घ(start, 16, &addr);
	अगर (ret)
		वापस ret;

	अगर (addr >= AAT2870_REG_NUM) अणु
		dev_err(aat2870->dev, "Invalid address, 0x%lx\n", addr);
		वापस -EINVAL;
	पूर्ण

	जबतक (*start == ' ')
		start++;

	ret = kम_से_अदीर्घ(start, 16, &val);
	अगर (ret)
		वापस ret;

	ret = aat2870->ग_लिखो(aat2870, (u8)addr, (u8)val);
	अगर (ret)
		वापस ret;

	वापस buf_size;
पूर्ण

अटल स्थिर काष्ठा file_operations aat2870_reg_fops = अणु
	.खोलो = simple_खोलो,
	.पढ़ो = aat2870_reg_पढ़ो_file,
	.ग_लिखो = aat2870_reg_ग_लिखो_file,
पूर्ण;

अटल व्योम aat2870_init_debugfs(काष्ठा aat2870_data *aat2870)
अणु
	aat2870->dentry_root = debugfs_create_dir("aat2870", शून्य);

	debugfs_create_file("regs", 0644, aat2870->dentry_root, aat2870,
			    &aat2870_reg_fops);
पूर्ण

#अन्यथा
अटल अंतरभूत व्योम aat2870_init_debugfs(काष्ठा aat2870_data *aat2870)
अणु
पूर्ण
#पूर्ण_अगर /* CONFIG_DEBUG_FS */

अटल पूर्णांक aat2870_i2c_probe(काष्ठा i2c_client *client,
			     स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा aat2870_platक्रमm_data *pdata = dev_get_platdata(&client->dev);
	काष्ठा aat2870_data *aat2870;
	पूर्णांक i, j;
	पूर्णांक ret = 0;

	aat2870 = devm_kzalloc(&client->dev, माप(काष्ठा aat2870_data),
				GFP_KERNEL);
	अगर (!aat2870)
		वापस -ENOMEM;

	aat2870->dev = &client->dev;
	dev_set_drvdata(aat2870->dev, aat2870);

	aat2870->client = client;
	i2c_set_clientdata(client, aat2870);

	aat2870->reg_cache = aat2870_regs;

	अगर (pdata->en_pin < 0)
		aat2870->en_pin = -1;
	अन्यथा
		aat2870->en_pin = pdata->en_pin;

	aat2870->init = pdata->init;
	aat2870->uninit = pdata->uninit;
	aat2870->पढ़ो = aat2870_पढ़ो;
	aat2870->ग_लिखो = aat2870_ग_लिखो;
	aat2870->update = aat2870_update;

	mutex_init(&aat2870->io_lock);

	अगर (aat2870->init)
		aat2870->init(aat2870);

	अगर (aat2870->en_pin >= 0) अणु
		ret = devm_gpio_request_one(&client->dev, aat2870->en_pin,
					GPIOF_OUT_INIT_HIGH, "aat2870-en");
		अगर (ret < 0) अणु
			dev_err(&client->dev,
				"Failed to request GPIO %d\n", aat2870->en_pin);
			वापस ret;
		पूर्ण
	पूर्ण

	aat2870_enable(aat2870);

	क्रम (i = 0; i < pdata->num_subdevs; i++) अणु
		क्रम (j = 0; j < ARRAY_SIZE(aat2870_devs); j++) अणु
			अगर ((pdata->subdevs[i].id == aat2870_devs[j].id) &&
					!म_भेद(pdata->subdevs[i].name,
						aat2870_devs[j].name)) अणु
				aat2870_devs[j].platक्रमm_data =
					pdata->subdevs[i].platक्रमm_data;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	ret = mfd_add_devices(aat2870->dev, 0, aat2870_devs,
			      ARRAY_SIZE(aat2870_devs), शून्य, 0, शून्य);
	अगर (ret != 0) अणु
		dev_err(aat2870->dev, "Failed to add subdev: %d\n", ret);
		जाओ out_disable;
	पूर्ण

	aat2870_init_debugfs(aat2870);

	वापस 0;

out_disable:
	aat2870_disable(aat2870);
	वापस ret;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक aat2870_i2c_suspend(काष्ठा device *dev)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा aat2870_data *aat2870 = i2c_get_clientdata(client);

	aat2870_disable(aat2870);

	वापस 0;
पूर्ण

अटल पूर्णांक aat2870_i2c_resume(काष्ठा device *dev)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा aat2870_data *aat2870 = i2c_get_clientdata(client);
	काष्ठा aat2870_रेजिस्टर *reg = शून्य;
	पूर्णांक i;

	aat2870_enable(aat2870);

	/* restore रेजिस्टरs */
	क्रम (i = 0; i < AAT2870_REG_NUM; i++) अणु
		reg = &aat2870->reg_cache[i];
		अगर (reg->ग_लिखोable)
			aat2870->ग_लिखो(aat2870, i, reg->value);
	पूर्ण

	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_PM_SLEEP */

अटल SIMPLE_DEV_PM_OPS(aat2870_pm_ops, aat2870_i2c_suspend,
			 aat2870_i2c_resume);

अटल स्थिर काष्ठा i2c_device_id aat2870_i2c_id_table[] = अणु
	अणु "aat2870", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल काष्ठा i2c_driver aat2870_i2c_driver = अणु
	.driver = अणु
		.name			= "aat2870",
		.pm			= &aat2870_pm_ops,
		.suppress_bind_attrs	= true,
	पूर्ण,
	.probe		= aat2870_i2c_probe,
	.id_table	= aat2870_i2c_id_table,
पूर्ण;

अटल पूर्णांक __init aat2870_init(व्योम)
अणु
	वापस i2c_add_driver(&aat2870_i2c_driver);
पूर्ण
subsys_initcall(aat2870_init);
