<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * I2C driver क्रम stand-alone PCF8584 style adapters on Zorro cards
 *
 * Original ICY करोcumentation can be found on Aminet:
 * https://aminet.net/package/करोcs/hard/icy
 *
 * There has been a modern community re-prपूर्णांक of this design in 2019:
 * https://www.a1k.org/क्रमum/index.php?thपढ़ोs/70106/
 *
 * The card is basically a Philips PCF8584 connected straight to the
 * beginning of the AutoConfig'd address space (रेजिस्टर S1 on base+2),
 * with /INT on /INT2 on the Zorro bus.
 *
 * Copyright (c) 2019 Max Staudt <max@enpas.org>
 *
 * This started as a विभाजन of i2c-elektor.c and has evolved since.
 * Thanks go to its authors क्रम providing a base to grow on.
 *
 *
 * IRQ support is currently not implemented.
 *
 * As it turns out, i2c-algo-pcf is really written with i2c-elektor's
 * edge-triggered ISA पूर्णांकerrupts in mind, जबतक the Amiga's Zorro bus has
 * level-triggered पूर्णांकerrupts. This means that once an पूर्णांकerrupt occurs, we
 * have to tell the PCF8584 to shut up immediately, or it will keep the
 * पूर्णांकerrupt line busy and cause an IRQ storm.

 * However, because of the PCF8584's host-side protocol, there is no good
 * way to just quieten it without side effects. Rather, we have to perक्रमm
 * the next पढ़ो/ग_लिखो operation straight away, which will reset the /INT
 * pin. This entails re-designing the core of i2c-algo-pcf in the future.
 * For now, we never request an IRQ from the PCF8584, and poll it instead.
 */

#समावेश <linux/delay.h>
#समावेश <linux/init.h>
#समावेश <linux/पन.स>
#समावेश <linux/ioport.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>

#समावेश <linux/i2c.h>
#समावेश <linux/i2c-algo-pcf.h>

#समावेश <यंत्र/amigahw.h>
#समावेश <यंत्र/amigaपूर्णांकs.h>
#समावेश <linux/zorro.h>

#समावेश "../algos/i2c-algo-pcf.h"

काष्ठा icy_i2c अणु
	काष्ठा i2c_adapter adapter;

	व्योम __iomem *reg_s0;
	व्योम __iomem *reg_s1;
	काष्ठा i2c_client *ltc2990_client;
पूर्ण;

/*
 * Functions called by i2c-algo-pcf
 */
अटल व्योम icy_pcf_setpcf(व्योम *data, पूर्णांक ctl, पूर्णांक val)
अणु
	काष्ठा icy_i2c *i2c = (काष्ठा icy_i2c *)data;

	u8 __iomem *address = ctl ? i2c->reg_s1 : i2c->reg_s0;

	z_ग_लिखोb(val, address);
पूर्ण

अटल पूर्णांक icy_pcf_getpcf(व्योम *data, पूर्णांक ctl)
अणु
	काष्ठा icy_i2c *i2c = (काष्ठा icy_i2c *)data;

	u8 __iomem *address = ctl ? i2c->reg_s1 : i2c->reg_s0;

	वापस z_पढ़ोb(address);
पूर्ण

अटल पूर्णांक icy_pcf_getown(व्योम *data)
अणु
	वापस 0x55;
पूर्ण

अटल पूर्णांक icy_pcf_अ_लोlock(व्योम *data)
अणु
	वापस 0x1c;
पूर्ण

अटल व्योम icy_pcf_रुकोक्रमpin(व्योम *data)
अणु
	usleep_range(50, 150);
पूर्ण

/*
 * Main i2c-icy part
 */
अटल अचिन्हित लघु स्थिर icy_ltc2990_addresses[] = अणु
	0x4c, 0x4d, 0x4e, 0x4f, I2C_CLIENT_END
पूर्ण;

/*
 * Additional sensors exposed once this property is applied:
 *
 * in1 will be the voltage of the 5V rail, भागided by 2.
 * in2 will be the voltage of the 12V rail, भागided by 4.
 * temp3 will be measured using a PCB loop next the chip.
 */
अटल स्थिर u32 icy_ltc2990_meas_mode[] = अणु0, 3पूर्ण;

अटल स्थिर काष्ठा property_entry icy_ltc2990_props[] = अणु
	PROPERTY_ENTRY_U32_ARRAY("lltc,meas-mode", icy_ltc2990_meas_mode),
	अणु पूर्ण
पूर्ण;

अटल स्थिर काष्ठा software_node icy_ltc2990_node = अणु
	.properties = icy_ltc2990_props,
पूर्ण;

अटल पूर्णांक icy_probe(काष्ठा zorro_dev *z,
		     स्थिर काष्ठा zorro_device_id *ent)
अणु
	काष्ठा icy_i2c *i2c;
	काष्ठा i2c_algo_pcf_data *algo_data;
	काष्ठा i2c_board_info ltc2990_info = अणु
		.type		= "ltc2990",
		.swnode		= &icy_ltc2990_node,
	पूर्ण;

	i2c = devm_kzalloc(&z->dev, माप(*i2c), GFP_KERNEL);
	अगर (!i2c)
		वापस -ENOMEM;

	algo_data = devm_kzalloc(&z->dev, माप(*algo_data), GFP_KERNEL);
	अगर (!algo_data)
		वापस -ENOMEM;

	dev_set_drvdata(&z->dev, i2c);
	i2c->adapter.dev.parent = &z->dev;
	i2c->adapter.owner = THIS_MODULE;
	/* i2c->adapter.algo asचिन्हित by i2c_pcf_add_bus() */
	i2c->adapter.algo_data = algo_data;
	strlcpy(i2c->adapter.name, "ICY I2C Zorro adapter",
		माप(i2c->adapter.name));

	अगर (!devm_request_mem_region(&z->dev,
				     z->resource.start,
				     4, i2c->adapter.name))
		वापस -ENXIO;

	/* Driver निजी data */
	i2c->reg_s0 = ZTWO_VADDR(z->resource.start);
	i2c->reg_s1 = ZTWO_VADDR(z->resource.start + 2);

	algo_data->data = i2c;
	algo_data->setpcf     = icy_pcf_setpcf;
	algo_data->getpcf     = icy_pcf_getpcf;
	algo_data->getown     = icy_pcf_getown;
	algo_data->अ_लोlock   = icy_pcf_अ_लोlock;
	algo_data->रुकोक्रमpin = icy_pcf_रुकोक्रमpin;

	अगर (i2c_pcf_add_bus(&i2c->adapter)) अणु
		dev_err(&z->dev, "i2c_pcf_add_bus() failed\n");
		वापस -ENXIO;
	पूर्ण

	dev_info(&z->dev, "ICY I2C controller at %pa, IRQ not implemented\n",
		 &z->resource.start);

	/*
	 * The 2019 a1k.org PCBs have an LTC2990 at 0x4c, so start
	 * it स्वतःmatically once ltc2990 is modprobed.
	 *
	 * in0 is the voltage of the पूर्णांकernal 5V घातer supply.
	 * temp1 is the temperature inside the chip.
	 *
	 * See property_entry above क्रम in1, in2, temp3.
	 */
	i2c->ltc2990_client = i2c_new_scanned_device(&i2c->adapter,
						     &ltc2990_info,
						     icy_ltc2990_addresses,
						     शून्य);
	वापस 0;
पूर्ण

अटल व्योम icy_हटाओ(काष्ठा zorro_dev *z)
अणु
	काष्ठा icy_i2c *i2c = dev_get_drvdata(&z->dev);

	i2c_unरेजिस्टर_device(i2c->ltc2990_client);
	i2c_del_adapter(&i2c->adapter);
पूर्ण

अटल स्थिर काष्ठा zorro_device_id icy_zorro_tbl[] = अणु
	अणु ZORRO_ID(VMC, 15, 0), पूर्ण,
	अणु 0 पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(zorro, icy_zorro_tbl);

अटल काष्ठा zorro_driver icy_driver = अणु
	.name           = "i2c-icy",
	.id_table       = icy_zorro_tbl,
	.probe          = icy_probe,
	.हटाओ         = icy_हटाओ,
पूर्ण;

module_driver(icy_driver,
	      zorro_रेजिस्टर_driver,
	      zorro_unरेजिस्टर_driver);

MODULE_AUTHOR("Max Staudt <max@enpas.org>");
MODULE_DESCRIPTION("I2C bus via PCF8584 on ICY Zorro card");
MODULE_LICENSE("GPL v2");
