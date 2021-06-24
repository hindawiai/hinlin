<शैली गुरु>
/*
 * linux/drivers/video/riva/fbdev-i2c.c - nVidia i2c
 *
 * Maपूर्णांकained by Ani Joshi <ajoshi@shell.unixbox.com>
 *
 * Copyright 2004 Antonino A. Daplas <adaplas @pol.net>
 *
 * Based on radeonfb-i2c.c
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file COPYING in the मुख्य directory of this archive
 * क्रम more details.
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/delay.h>
#समावेश <linux/pci.h>
#समावेश <linux/fb.h>
#समावेश <linux/jअगरfies.h>

#समावेश <यंत्र/पन.स>

#समावेश "rivafb.h"
#समावेश "../edid.h"

अटल व्योम riva_gpio_setscl(व्योम* data, पूर्णांक state)
अणु
	काष्ठा riva_i2c_chan 	*chan = data;
	काष्ठा riva_par 	*par = chan->par;
	u32			val;

	VGA_WR08(par->riva.PCIO, 0x3d4, chan->ddc_base + 1);
	val = VGA_RD08(par->riva.PCIO, 0x3d5) & 0xf0;

	अगर (state)
		val |= 0x20;
	अन्यथा
		val &= ~0x20;

	VGA_WR08(par->riva.PCIO, 0x3d4, chan->ddc_base + 1);
	VGA_WR08(par->riva.PCIO, 0x3d5, val | 0x1);
पूर्ण

अटल व्योम riva_gpio_setsda(व्योम* data, पूर्णांक state)
अणु
	काष्ठा riva_i2c_chan 	*chan = data;
	काष्ठा riva_par 	*par = chan->par;
	u32			val;

	VGA_WR08(par->riva.PCIO, 0x3d4, chan->ddc_base + 1);
	val = VGA_RD08(par->riva.PCIO, 0x3d5) & 0xf0;

	अगर (state)
		val |= 0x10;
	अन्यथा
		val &= ~0x10;

	VGA_WR08(par->riva.PCIO, 0x3d4, chan->ddc_base + 1);
	VGA_WR08(par->riva.PCIO, 0x3d5, val | 0x1);
पूर्ण

अटल पूर्णांक riva_gpio_माला_लोcl(व्योम* data)
अणु
	काष्ठा riva_i2c_chan 	*chan = data;
	काष्ठा riva_par 	*par = chan->par;
	u32			val = 0;

	VGA_WR08(par->riva.PCIO, 0x3d4, chan->ddc_base);
	अगर (VGA_RD08(par->riva.PCIO, 0x3d5) & 0x04)
		val = 1;

	वापस val;
पूर्ण

अटल पूर्णांक riva_gpio_माला_लोda(व्योम* data)
अणु
	काष्ठा riva_i2c_chan 	*chan = data;
	काष्ठा riva_par 	*par = chan->par;
	u32			val = 0;

	VGA_WR08(par->riva.PCIO, 0x3d4, chan->ddc_base);
	अगर (VGA_RD08(par->riva.PCIO, 0x3d5) & 0x08)
		val = 1;

	वापस val;
पूर्ण

अटल पूर्णांक riva_setup_i2c_bus(काष्ठा riva_i2c_chan *chan, स्थिर अक्षर *name,
			      अचिन्हित पूर्णांक i2c_class)
अणु
	पूर्णांक rc;

	म_नकल(chan->adapter.name, name);
	chan->adapter.owner		= THIS_MODULE;
	chan->adapter.class		= i2c_class;
	chan->adapter.algo_data		= &chan->algo;
	chan->adapter.dev.parent	= &chan->par->pdev->dev;
	chan->algo.setsda		= riva_gpio_setsda;
	chan->algo.setscl		= riva_gpio_setscl;
	chan->algo.माला_लोda		= riva_gpio_माला_लोda;
	chan->algo.माला_लोcl		= riva_gpio_माला_लोcl;
	chan->algo.udelay		= 40;
	chan->algo.समयout		= msecs_to_jअगरfies(2);
	chan->algo.data 		= chan;

	i2c_set_adapdata(&chan->adapter, chan);

	/* Raise SCL and SDA */
	riva_gpio_setsda(chan, 1);
	riva_gpio_setscl(chan, 1);
	udelay(20);

	rc = i2c_bit_add_bus(&chan->adapter);
	अगर (rc == 0)
		dev_dbg(&chan->par->pdev->dev, "I2C bus %s registered.\n", name);
	अन्यथा अणु
		dev_warn(&chan->par->pdev->dev,
			 "Failed to register I2C bus %s.\n", name);
		chan->par = शून्य;
	पूर्ण

	वापस rc;
पूर्ण

व्योम riva_create_i2c_busses(काष्ठा riva_par *par)
अणु
	par->chan[0].par	= par;
	par->chan[1].par	= par;
	par->chan[2].par        = par;

	par->chan[0].ddc_base = 0x36;
	par->chan[1].ddc_base = 0x3e;
	par->chan[2].ddc_base = 0x50;
	riva_setup_i2c_bus(&par->chan[0], "BUS1", I2C_CLASS_HWMON);
	riva_setup_i2c_bus(&par->chan[1], "BUS2", 0);
	riva_setup_i2c_bus(&par->chan[2], "BUS3", 0);
पूर्ण

व्योम riva_delete_i2c_busses(काष्ठा riva_par *par)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < 3; i++) अणु
		अगर (!par->chan[i].par)
			जारी;
		i2c_del_adapter(&par->chan[i].adapter);
		par->chan[i].par = शून्य;
	पूर्ण
पूर्ण

पूर्णांक riva_probe_i2c_connector(काष्ठा riva_par *par, पूर्णांक conn, u8 **out_edid)
अणु
	u8 *edid = शून्य;

	अगर (par->chan[conn].par)
		edid = fb_ddc_पढ़ो(&par->chan[conn].adapter);

	अगर (out_edid)
		*out_edid = edid;
	अगर (!edid)
		वापस 1;

	वापस 0;
पूर्ण

