<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * BQ27xxx battery monitor HDQ/1-wire driver
 *
 * Copyright (C) 2007-2017 Texas Instruments Incorporated - https://www.ti.com/
 *
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/device.h>
#समावेश <linux/types.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/mutex.h>
#समावेश <linux/घातer/bq27xxx_battery.h>

#समावेश <linux/w1.h>

#घोषणा W1_FAMILY_BQ27000	0x01

#घोषणा HDQ_CMD_READ	(0 << 7)
#घोषणा HDQ_CMD_WRITE	(1 << 7)

अटल पूर्णांक F_ID;
module_param(F_ID, पूर्णांक, S_IRUSR);
MODULE_PARM_DESC(F_ID, "1-wire slave FID for BQ27xxx device");

अटल पूर्णांक w1_bq27000_पढ़ो(काष्ठा w1_slave *sl, अचिन्हित पूर्णांक reg)
अणु
	u8 val;

	mutex_lock(&sl->master->bus_mutex);
	w1_ग_लिखो_8(sl->master, HDQ_CMD_READ | reg);
	val = w1_पढ़ो_8(sl->master);
	mutex_unlock(&sl->master->bus_mutex);

	वापस val;
पूर्ण

अटल पूर्णांक bq27xxx_battery_hdq_पढ़ो(काष्ठा bq27xxx_device_info *di, u8 reg,
				    bool single)
अणु
	काष्ठा w1_slave *sl = dev_to_w1_slave(di->dev);
	अचिन्हित पूर्णांक समयout = 3;
	पूर्णांक upper, lower;
	पूर्णांक temp;

	अगर (!single) अणु
		/*
		 * Make sure the value has not changed in between पढ़ोing the
		 * lower and the upper part
		 */
		upper = w1_bq27000_पढ़ो(sl, reg + 1);
		करो अणु
			temp = upper;
			अगर (upper < 0)
				वापस upper;

			lower = w1_bq27000_पढ़ो(sl, reg);
			अगर (lower < 0)
				वापस lower;

			upper = w1_bq27000_पढ़ो(sl, reg + 1);
		पूर्ण जबतक (temp != upper && --समयout);

		अगर (समयout == 0)
			वापस -EIO;

		वापस (upper << 8) | lower;
	पूर्ण

	वापस w1_bq27000_पढ़ो(sl, reg);
पूर्ण

अटल पूर्णांक bq27xxx_battery_hdq_add_slave(काष्ठा w1_slave *sl)
अणु
	काष्ठा bq27xxx_device_info *di;

	di = devm_kzalloc(&sl->dev, माप(*di), GFP_KERNEL);
	अगर (!di)
		वापस -ENOMEM;

	dev_set_drvdata(&sl->dev, di);

	di->dev = &sl->dev;
	di->chip = BQ27000;
	di->name = "bq27000-battery";
	di->bus.पढ़ो = bq27xxx_battery_hdq_पढ़ो;

	वापस bq27xxx_battery_setup(di);
पूर्ण

अटल व्योम bq27xxx_battery_hdq_हटाओ_slave(काष्ठा w1_slave *sl)
अणु
	काष्ठा bq27xxx_device_info *di = dev_get_drvdata(&sl->dev);

	bq27xxx_battery_tearकरोwn(di);
पूर्ण

अटल स्थिर काष्ठा w1_family_ops bq27xxx_battery_hdq_fops = अणु
	.add_slave	= bq27xxx_battery_hdq_add_slave,
	.हटाओ_slave	= bq27xxx_battery_hdq_हटाओ_slave,
पूर्ण;

अटल काष्ठा w1_family bq27xxx_battery_hdq_family = अणु
	.fid = W1_FAMILY_BQ27000,
	.fops = &bq27xxx_battery_hdq_fops,
पूर्ण;

अटल पूर्णांक __init bq27xxx_battery_hdq_init(व्योम)
अणु
	अगर (F_ID)
		bq27xxx_battery_hdq_family.fid = F_ID;

	वापस w1_रेजिस्टर_family(&bq27xxx_battery_hdq_family);
पूर्ण
module_init(bq27xxx_battery_hdq_init);

अटल व्योम __निकास bq27xxx_battery_hdq_निकास(व्योम)
अणु
	w1_unरेजिस्टर_family(&bq27xxx_battery_hdq_family);
पूर्ण
module_निकास(bq27xxx_battery_hdq_निकास);

MODULE_AUTHOR("Texas Instruments Ltd");
MODULE_DESCRIPTION("BQ27xxx battery monitor HDQ/1-wire driver");
MODULE_LICENSE("GPL");
MODULE_ALIAS("w1-family-" __stringअगरy(W1_FAMILY_BQ27000));
