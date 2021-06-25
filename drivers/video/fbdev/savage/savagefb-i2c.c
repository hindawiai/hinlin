<शैली गुरु>
/*
 * linux/drivers/video/savage/savagefb-i2c.c - S3 Savage DDC2
 *
 * Copyright 2004 Antonino A. Daplas <adaplas @pol.net>
 *
 * Based partly on rivafb-i2c.c
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file COPYING in the मुख्य directory of this archive
 * क्रम more details.
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/delay.h>
#समावेश <linux/gfp.h>
#समावेश <linux/pci.h>
#समावेश <linux/fb.h>

#समावेश <यंत्र/पन.स>
#समावेश "savagefb.h"

#घोषणा SAVAGE_DDC 	0x50

#घोषणा VGA_CR_IX	0x3d4
#घोषणा VGA_CR_DATA	0x3d5

#घोषणा CR_SERIAL1	0xa0	/* I2C serial communications पूर्णांकerface */
#घोषणा MM_SERIAL1	0xff20
#घोषणा CR_SERIAL2	0xb1	/* DDC2 monitor communications पूर्णांकerface */

/* based on vt8365 करोcumentation */
#घोषणा PROSAVAGE_I2C_ENAB	0x10
#घोषणा PROSAVAGE_I2C_SCL_OUT	0x01
#घोषणा PROSAVAGE_I2C_SDA_OUT	0x02
#घोषणा PROSAVAGE_I2C_SCL_IN	0x04
#घोषणा PROSAVAGE_I2C_SDA_IN	0x08

#घोषणा SAVAGE4_I2C_ENAB	0x00000020
#घोषणा SAVAGE4_I2C_SCL_OUT	0x00000001
#घोषणा SAVAGE4_I2C_SDA_OUT	0x00000002
#घोषणा SAVAGE4_I2C_SCL_IN	0x00000008
#घोषणा SAVAGE4_I2C_SDA_IN	0x00000010

अटल व्योम savage4_gpio_setscl(व्योम *data, पूर्णांक val)
अणु
	काष्ठा savagefb_i2c_chan *chan = data;
	अचिन्हित पूर्णांक r;

	r = पढ़ोl(chan->ioaddr + chan->reg);
	अगर(val)
		r |= SAVAGE4_I2C_SCL_OUT;
	अन्यथा
		r &= ~SAVAGE4_I2C_SCL_OUT;
	ग_लिखोl(r, chan->ioaddr + chan->reg);
	पढ़ोl(chan->ioaddr + chan->reg);	/* flush posted ग_लिखो */
पूर्ण

अटल व्योम savage4_gpio_setsda(व्योम *data, पूर्णांक val)
अणु
	काष्ठा savagefb_i2c_chan *chan = data;

	अचिन्हित पूर्णांक r;
	r = पढ़ोl(chan->ioaddr + chan->reg);
	अगर(val)
		r |= SAVAGE4_I2C_SDA_OUT;
	अन्यथा
		r &= ~SAVAGE4_I2C_SDA_OUT;
	ग_लिखोl(r, chan->ioaddr + chan->reg);
	पढ़ोl(chan->ioaddr + chan->reg);	/* flush posted ग_लिखो */
पूर्ण

अटल पूर्णांक savage4_gpio_माला_लोcl(व्योम *data)
अणु
	काष्ठा savagefb_i2c_chan *chan = data;

	वापस (0 != (पढ़ोl(chan->ioaddr + chan->reg) & SAVAGE4_I2C_SCL_IN));
पूर्ण

अटल पूर्णांक savage4_gpio_माला_लोda(व्योम *data)
अणु
	काष्ठा savagefb_i2c_chan *chan = data;

	वापस (0 != (पढ़ोl(chan->ioaddr + chan->reg) & SAVAGE4_I2C_SDA_IN));
पूर्ण

अटल व्योम prosavage_gpio_setscl(व्योम* data, पूर्णांक val)
अणु
	काष्ठा savagefb_i2c_chan *chan = data;
	u32			  r;

	r = VGArCR(chan->reg, chan->par);
	r |= PROSAVAGE_I2C_ENAB;
	अगर (val) अणु
		r |= PROSAVAGE_I2C_SCL_OUT;
	पूर्ण अन्यथा अणु
		r &= ~PROSAVAGE_I2C_SCL_OUT;
	पूर्ण

	VGAwCR(chan->reg, r, chan->par);
पूर्ण

अटल व्योम prosavage_gpio_setsda(व्योम* data, पूर्णांक val)
अणु
	काष्ठा savagefb_i2c_chan *chan = data;
	अचिन्हित पूर्णांक r;

	r = VGArCR(chan->reg, chan->par);
	r |= PROSAVAGE_I2C_ENAB;
	अगर (val) अणु
		r |= PROSAVAGE_I2C_SDA_OUT;
	पूर्ण अन्यथा अणु
		r &= ~PROSAVAGE_I2C_SDA_OUT;
	पूर्ण

	VGAwCR(chan->reg, r, chan->par);
पूर्ण

अटल पूर्णांक prosavage_gpio_माला_लोcl(व्योम* data)
अणु
	काष्ठा savagefb_i2c_chan *chan = data;

	वापस (VGArCR(chan->reg, chan->par) & PROSAVAGE_I2C_SCL_IN) ? 1 : 0;
पूर्ण

अटल पूर्णांक prosavage_gpio_माला_लोda(व्योम* data)
अणु
	काष्ठा savagefb_i2c_chan *chan = data;

	वापस (VGArCR(chan->reg, chan->par) & PROSAVAGE_I2C_SDA_IN) ? 1 : 0;
पूर्ण

अटल पूर्णांक savage_setup_i2c_bus(काष्ठा savagefb_i2c_chan *chan,
				स्थिर अक्षर *name)
अणु
	पूर्णांक rc = 0;

	अगर (chan->par) अणु
		म_नकल(chan->adapter.name, name);
		chan->adapter.owner		= THIS_MODULE;
		chan->adapter.algo_data		= &chan->algo;
		chan->adapter.dev.parent	= &chan->par->pcidev->dev;
		chan->algo.udelay		= 10;
		chan->algo.समयout		= 20;
		chan->algo.data 		= chan;

		i2c_set_adapdata(&chan->adapter, chan);

		/* Raise SCL and SDA */
		chan->algo.setsda(chan, 1);
		chan->algo.setscl(chan, 1);
		udelay(20);

		rc = i2c_bit_add_bus(&chan->adapter);

		अगर (rc == 0)
			dev_dbg(&chan->par->pcidev->dev,
				"I2C bus %s registered.\n", name);
		अन्यथा
			dev_warn(&chan->par->pcidev->dev,
				 "Failed to register I2C bus %s.\n", name);
	पूर्ण

	वापस rc;
पूर्ण

व्योम savagefb_create_i2c_busses(काष्ठा fb_info *info)
अणु
	काष्ठा savagefb_par *par = info->par;
	par->chan.par	= par;

	चयन (par->chip) अणु
	हाल S3_PROSAVAGE:
	हाल S3_PROSAVAGEDDR:
	हाल S3_TWISTER:
		par->chan.reg         = CR_SERIAL2;
		par->chan.ioaddr      = par->mmio.vbase;
		par->chan.algo.setsda = prosavage_gpio_setsda;
		par->chan.algo.setscl = prosavage_gpio_setscl;
		par->chan.algo.माला_लोda = prosavage_gpio_माला_लोda;
		par->chan.algo.माला_लोcl = prosavage_gpio_माला_लोcl;
		अवरोध;
	हाल S3_SAVAGE4:
		par->chan.reg = CR_SERIAL1;
		अगर (par->pcidev->revision > 1 && !(VGArCR(0xa6, par) & 0x40))
			par->chan.reg = CR_SERIAL2;
		par->chan.ioaddr      = par->mmio.vbase;
		par->chan.algo.setsda = prosavage_gpio_setsda;
		par->chan.algo.setscl = prosavage_gpio_setscl;
		par->chan.algo.माला_लोda = prosavage_gpio_माला_लोda;
		par->chan.algo.माला_लोcl = prosavage_gpio_माला_लोcl;
		अवरोध;
	हाल S3_SAVAGE2000:
		par->chan.reg         = MM_SERIAL1;
		par->chan.ioaddr      = par->mmio.vbase;
		par->chan.algo.setsda = savage4_gpio_setsda;
		par->chan.algo.setscl = savage4_gpio_setscl;
		par->chan.algo.माला_लोda = savage4_gpio_माला_लोda;
		par->chan.algo.माला_लोcl = savage4_gpio_माला_लोcl;
		अवरोध;
	शेष:
		par->chan.par = शून्य;
	पूर्ण

	savage_setup_i2c_bus(&par->chan, "SAVAGE DDC2");
पूर्ण

व्योम savagefb_delete_i2c_busses(काष्ठा fb_info *info)
अणु
	काष्ठा savagefb_par *par = info->par;

	अगर (par->chan.par)
		i2c_del_adapter(&par->chan.adapter);

	par->chan.par = शून्य;
पूर्ण

पूर्णांक savagefb_probe_i2c_connector(काष्ठा fb_info *info, u8 **out_edid)
अणु
	काष्ठा savagefb_par *par = info->par;
	u8 *edid;

	अगर (par->chan.par)
		edid = fb_ddc_पढ़ो(&par->chan.adapter);
	अन्यथा
		edid = शून्य;

	अगर (!edid) अणु
		/* try to get from firmware */
		स्थिर u8 *e = fb_firmware_edid(info->device);

		अगर (e)
			edid = kmemdup(e, EDID_LENGTH, GFP_KERNEL);
	पूर्ण

	*out_edid = edid;

	वापस (edid) ? 0 : 1;
पूर्ण

MODULE_LICENSE("GPL");
