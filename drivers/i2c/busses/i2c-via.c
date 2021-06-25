<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
    i2c Support क्रम Via Technologies 82C586B South Bridge

    Copyright (c) 1998, 1999 Kyथघsti Mथअlkki <kmalkki@cc.hut.fi>

*/

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/ioport.h>
#समावेश <linux/i2c.h>
#समावेश <linux/i2c-algo-bit.h>
#समावेश <linux/पन.स>

/* Power management रेजिस्टरs */
#घोषणा PM_CFG_REVID	0x08	/* silicon revision code */
#घोषणा PM_CFG_IOBASE0	0x20
#घोषणा PM_CFG_IOBASE1	0x48

#घोषणा I2C_सूची		(pm_io_base+0x40)
#घोषणा I2C_OUT		(pm_io_base+0x42)
#घोषणा I2C_IN		(pm_io_base+0x44)
#घोषणा I2C_SCL		0x02	/* घड़ी bit in सूची/OUT/IN रेजिस्टर */
#घोषणा I2C_SDA		0x04

/* io-region reservation */
#घोषणा IOSPACE		0x06

अटल काष्ठा pci_driver vt586b_driver;
अटल u16 pm_io_base;

/*
   It करोes not appear from the datasheet that the GPIO pins are
   खोलो drain. So a we set a low value by setting the direction to
   output and a high value by setting the direction to input and
   relying on the required I2C pullup. The data value is initialized
   to 0 in via_init() and never changed.
*/
अटल व्योम bit_via_setscl(व्योम *data, पूर्णांक state)
अणु
	outb(state ? inb(I2C_सूची) & ~I2C_SCL : inb(I2C_सूची) | I2C_SCL, I2C_सूची);
पूर्ण

अटल व्योम bit_via_setsda(व्योम *data, पूर्णांक state)
अणु
	outb(state ? inb(I2C_सूची) & ~I2C_SDA : inb(I2C_सूची) | I2C_SDA, I2C_सूची);
पूर्ण

अटल पूर्णांक bit_via_माला_लोcl(व्योम *data)
अणु
	वापस (0 != (inb(I2C_IN) & I2C_SCL));
पूर्ण

अटल पूर्णांक bit_via_माला_लोda(व्योम *data)
अणु
	वापस (0 != (inb(I2C_IN) & I2C_SDA));
पूर्ण


अटल काष्ठा i2c_algo_bit_data bit_data = अणु
	.setsda		= bit_via_setsda,
	.setscl		= bit_via_setscl,
	.माला_लोda		= bit_via_माला_लोda,
	.माला_लोcl		= bit_via_माला_लोcl,
	.udelay		= 5,
	.समयout	= HZ
पूर्ण;

अटल काष्ठा i2c_adapter vt586b_adapter = अणु
	.owner		= THIS_MODULE,
	.class          = I2C_CLASS_HWMON | I2C_CLASS_SPD,
	.name		= "VIA i2c",
	.algo_data	= &bit_data,
पूर्ण;


अटल स्थिर काष्ठा pci_device_id vt586b_ids[] = अणु
	अणु PCI_DEVICE(PCI_VENDOR_ID_VIA, PCI_DEVICE_ID_VIA_82C586_3) पूर्ण,
	अणु 0, पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE (pci, vt586b_ids);

अटल पूर्णांक vt586b_probe(काष्ठा pci_dev *dev, स्थिर काष्ठा pci_device_id *id)
अणु
	u16 base;
	u8 rev;
	पूर्णांक res;

	अगर (pm_io_base) अणु
		dev_err(&dev->dev, "i2c-via: Will only support one host\n");
		वापस -ENODEV;
	पूर्ण

	pci_पढ़ो_config_byte(dev, PM_CFG_REVID, &rev);

	चयन (rev) अणु
	हाल 0x00:
		base = PM_CFG_IOBASE0;
		अवरोध;
	हाल 0x01:
	हाल 0x10:
		base = PM_CFG_IOBASE1;
		अवरोध;

	शेष:
		base = PM_CFG_IOBASE1;
		/* later revision */
	पूर्ण

	pci_पढ़ो_config_word(dev, base, &pm_io_base);
	pm_io_base &= (0xff << 8);

	अगर (!request_region(I2C_सूची, IOSPACE, vt586b_driver.name)) अणु
		dev_err(&dev->dev, "IO 0x%x-0x%x already in use\n", I2C_सूची, I2C_सूची + IOSPACE);
		वापस -ENODEV;
	पूर्ण

	outb(inb(I2C_सूची) & ~(I2C_SDA | I2C_SCL), I2C_सूची);
	outb(inb(I2C_OUT) & ~(I2C_SDA | I2C_SCL), I2C_OUT);

	/* set up the sysfs linkage to our parent device */
	vt586b_adapter.dev.parent = &dev->dev;

	res = i2c_bit_add_bus(&vt586b_adapter);
	अगर ( res < 0 ) अणु
		release_region(I2C_सूची, IOSPACE);
		pm_io_base = 0;
		वापस res;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम vt586b_हटाओ(काष्ठा pci_dev *dev)
अणु
	i2c_del_adapter(&vt586b_adapter);
	release_region(I2C_सूची, IOSPACE);
	pm_io_base = 0;
पूर्ण


अटल काष्ठा pci_driver vt586b_driver = अणु
	.name		= "vt586b_smbus",
	.id_table	= vt586b_ids,
	.probe		= vt586b_probe,
	.हटाओ		= vt586b_हटाओ,
पूर्ण;

module_pci_driver(vt586b_driver);

MODULE_AUTHOR("Kyथघsti Mथअlkki <kmalkki@cc.hut.fi>");
MODULE_DESCRIPTION("i2c for Via vt82c586b southbridge");
MODULE_LICENSE("GPL");
