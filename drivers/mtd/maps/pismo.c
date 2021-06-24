<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * PISMO memory driver - http://www.pismoworld.org/
 *
 * For ARM Realview and Versatile platक्रमms
 */
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/i2c.h>
#समावेश <linux/slab.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/mutex.h>
#समावेश <linux/mtd/physmap.h>
#समावेश <linux/mtd/plat-ram.h>
#समावेश <linux/mtd/pismo.h>

#घोषणा PISMO_NUM_CS	5

काष्ठा pismo_cs_block अणु
	u8	type;
	u8	width;
	__le16	access;
	__le32	size;
	u32	reserved[2];
	अक्षर	device[32];
पूर्ण __packed;

काष्ठा pismo_eeprom अणु
	काष्ठा pismo_cs_block cs[PISMO_NUM_CS];
	अक्षर	board[15];
	u8	sum;
पूर्ण __packed;

काष्ठा pismo_mem अणु
	phys_addr_t base;
	u32	size;
	u16	access;
	u8	width;
	u8	type;
पूर्ण;

काष्ठा pismo_data अणु
	काष्ठा i2c_client	*client;
	व्योम			(*vpp)(व्योम *, पूर्णांक);
	व्योम			*vpp_data;
	काष्ठा platक्रमm_device	*dev[PISMO_NUM_CS];
पूर्ण;

अटल व्योम pismo_set_vpp(काष्ठा platक्रमm_device *pdev, पूर्णांक on)
अणु
	काष्ठा i2c_client *client = to_i2c_client(pdev->dev.parent);
	काष्ठा pismo_data *pismo = i2c_get_clientdata(client);

	pismo->vpp(pismo->vpp_data, on);
पूर्ण

अटल अचिन्हित पूर्णांक pismo_width_to_bytes(अचिन्हित पूर्णांक width)
अणु
	width &= 15;
	अगर (width > 2)
		वापस 0;
	वापस 1 << width;
पूर्ण

अटल पूर्णांक pismo_eeprom_पढ़ो(काष्ठा i2c_client *client, व्योम *buf, u8 addr,
			     माप_प्रकार size)
अणु
	पूर्णांक ret;
	काष्ठा i2c_msg msg[] = अणु
		अणु
			.addr = client->addr,
			.len = माप(addr),
			.buf = &addr,
		पूर्ण, अणु
			.addr = client->addr,
			.flags = I2C_M_RD,
			.len = size,
			.buf = buf,
		पूर्ण,
	पूर्ण;

	ret = i2c_transfer(client->adapter, msg, ARRAY_SIZE(msg));

	वापस ret == ARRAY_SIZE(msg) ? size : -EIO;
पूर्ण

अटल पूर्णांक pismo_add_device(काष्ठा pismo_data *pismo, पूर्णांक i,
			    काष्ठा pismo_mem *region, स्थिर अक्षर *name,
			    व्योम *pdata, माप_प्रकार psize)
अणु
	काष्ठा platक्रमm_device *dev;
	काष्ठा resource res = अणु पूर्ण;
	phys_addr_t base = region->base;
	पूर्णांक ret;

	अगर (base == ~0)
		वापस -ENXIO;

	res.start = base;
	res.end = base + region->size - 1;
	res.flags = IORESOURCE_MEM;

	dev = platक्रमm_device_alloc(name, i);
	अगर (!dev)
		वापस -ENOMEM;
	dev->dev.parent = &pismo->client->dev;

	करो अणु
		ret = platक्रमm_device_add_resources(dev, &res, 1);
		अगर (ret)
			अवरोध;

		ret = platक्रमm_device_add_data(dev, pdata, psize);
		अगर (ret)
			अवरोध;

		ret = platक्रमm_device_add(dev);
		अगर (ret)
			अवरोध;

		pismo->dev[i] = dev;
		वापस 0;
	पूर्ण जबतक (0);

	platक्रमm_device_put(dev);
	वापस ret;
पूर्ण

अटल पूर्णांक pismo_add_nor(काष्ठा pismo_data *pismo, पूर्णांक i,
			 काष्ठा pismo_mem *region)
अणु
	काष्ठा physmap_flash_data data = अणु
		.width = region->width,
	पूर्ण;

	अगर (pismo->vpp)
		data.set_vpp = pismo_set_vpp;

	वापस pismo_add_device(pismo, i, region, "physmap-flash",
		&data, माप(data));
पूर्ण

अटल पूर्णांक pismo_add_sram(काष्ठा pismo_data *pismo, पूर्णांक i,
			  काष्ठा pismo_mem *region)
अणु
	काष्ठा platdata_mtd_ram data = अणु
		.bankwidth = region->width,
	पूर्ण;

	वापस pismo_add_device(pismo, i, region, "mtd-ram",
		&data, माप(data));
पूर्ण

अटल व्योम pismo_add_one(काष्ठा pismo_data *pismo, पूर्णांक i,
			  स्थिर काष्ठा pismo_cs_block *cs, phys_addr_t base)
अणु
	काष्ठा device *dev = &pismo->client->dev;
	काष्ठा pismo_mem region;

	region.base = base;
	region.type = cs->type;
	region.width = pismo_width_to_bytes(cs->width);
	region.access = le16_to_cpu(cs->access);
	region.size = le32_to_cpu(cs->size);

	अगर (region.width == 0) अणु
		dev_err(dev, "cs%u: bad width: %02x, ignoring\n", i, cs->width);
		वापस;
	पूर्ण

	/*
	 * FIXME: may need to the platक्रमms memory controller here, but at
	 * the moment we assume that it has alपढ़ोy been correctly setup.
	 * The memory controller can also tell us the base address as well.
	 */

	dev_info(dev, "cs%u: %.32s: type %02x access %u00ps size %uK\n",
		i, cs->device, region.type, region.access, region.size / 1024);

	चयन (region.type) अणु
	हाल 0:
		अवरोध;
	हाल 1:
		/* अटल DOC */
		अवरोध;
	हाल 2:
		/* अटल NOR */
		pismo_add_nor(pismo, i, &region);
		अवरोध;
	हाल 3:
		/* अटल RAM */
		pismo_add_sram(pismo, i, &region);
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक pismo_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा pismo_data *pismo = i2c_get_clientdata(client);
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(pismo->dev); i++)
		platक्रमm_device_unरेजिस्टर(pismo->dev[i]);

	kमुक्त(pismo);

	वापस 0;
पूर्ण

अटल पूर्णांक pismo_probe(काष्ठा i2c_client *client,
		       स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा pismo_pdata *pdata = client->dev.platक्रमm_data;
	काष्ठा pismo_eeprom eeprom;
	काष्ठा pismo_data *pismo;
	पूर्णांक ret, i;

	अगर (!i2c_check_functionality(client->adapter, I2C_FUNC_I2C)) अणु
		dev_err(&client->dev, "functionality mismatch\n");
		वापस -EIO;
	पूर्ण

	pismo = kzalloc(माप(*pismo), GFP_KERNEL);
	अगर (!pismo)
		वापस -ENOMEM;

	pismo->client = client;
	अगर (pdata) अणु
		pismo->vpp = pdata->set_vpp;
		pismo->vpp_data = pdata->vpp_data;
	पूर्ण
	i2c_set_clientdata(client, pismo);

	ret = pismo_eeprom_पढ़ो(client, &eeprom, 0, माप(eeprom));
	अगर (ret < 0) अणु
		dev_err(&client->dev, "error reading EEPROM: %d\n", ret);
		जाओ निकास_मुक्त;
	पूर्ण

	dev_info(&client->dev, "%.15s board found\n", eeprom.board);

	क्रम (i = 0; i < ARRAY_SIZE(eeprom.cs); i++)
		अगर (eeprom.cs[i].type != 0xff)
			pismo_add_one(pismo, i, &eeprom.cs[i],
				      pdata->cs_addrs[i]);

	वापस 0;

 निकास_मुक्त:
	kमुक्त(pismo);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id pismo_id[] = अणु
	अणु "pismo" पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(i2c, pismo_id);

अटल काष्ठा i2c_driver pismo_driver = अणु
	.driver	= अणु
		.name	= "pismo",
	पूर्ण,
	.probe		= pismo_probe,
	.हटाओ		= pismo_हटाओ,
	.id_table	= pismo_id,
पूर्ण;

अटल पूर्णांक __init pismo_init(व्योम)
अणु
	BUILD_BUG_ON(माप(काष्ठा pismo_cs_block) != 48);
	BUILD_BUG_ON(माप(काष्ठा pismo_eeprom) != 256);

	वापस i2c_add_driver(&pismo_driver);
पूर्ण
module_init(pismo_init);

अटल व्योम __निकास pismo_निकास(व्योम)
अणु
	i2c_del_driver(&pismo_driver);
पूर्ण
module_निकास(pismo_निकास);

MODULE_AUTHOR("Russell King <linux@arm.linux.org.uk>");
MODULE_DESCRIPTION("PISMO memory driver");
MODULE_LICENSE("GPL");
