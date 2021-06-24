<शैली गुरु>
/*
 * linux/drivers/video/nvidia/nvidia-i2c.c - nVidia i2c
 *
 * Copyright 2004 Antonino A. Daplas <adaplas @pol.net>
 *
 * Based on rivafb-i2c.c
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

#समावेश "nv_type.h"
#समावेश "nv_local.h"
#समावेश "nv_proto.h"

#समावेश "../edid.h"

अटल व्योम nvidia_gpio_setscl(व्योम *data, पूर्णांक state)
अणु
	काष्ठा nvidia_i2c_chan *chan = data;
	काष्ठा nvidia_par *par = chan->par;
	u32 val;

	val = NVReadCrtc(par, chan->ddc_base + 1) & 0xf0;

	अगर (state)
		val |= 0x20;
	अन्यथा
		val &= ~0x20;

	NVWriteCrtc(par, chan->ddc_base + 1, val | 0x01);
पूर्ण

अटल व्योम nvidia_gpio_setsda(व्योम *data, पूर्णांक state)
अणु
	काष्ठा nvidia_i2c_chan *chan = data;
	काष्ठा nvidia_par *par = chan->par;
	u32 val;

	val = NVReadCrtc(par, chan->ddc_base + 1) & 0xf0;

	अगर (state)
		val |= 0x10;
	अन्यथा
		val &= ~0x10;

	NVWriteCrtc(par, chan->ddc_base + 1, val | 0x01);
पूर्ण

अटल पूर्णांक nvidia_gpio_माला_लोcl(व्योम *data)
अणु
	काष्ठा nvidia_i2c_chan *chan = data;
	काष्ठा nvidia_par *par = chan->par;
	u32 val = 0;

	अगर (NVReadCrtc(par, chan->ddc_base) & 0x04)
		val = 1;

	वापस val;
पूर्ण

अटल पूर्णांक nvidia_gpio_माला_लोda(व्योम *data)
अणु
	काष्ठा nvidia_i2c_chan *chan = data;
	काष्ठा nvidia_par *par = chan->par;
	u32 val = 0;

	अगर (NVReadCrtc(par, chan->ddc_base) & 0x08)
		val = 1;

	वापस val;
पूर्ण

अटल पूर्णांक nvidia_setup_i2c_bus(काष्ठा nvidia_i2c_chan *chan, स्थिर अक्षर *name,
				अचिन्हित पूर्णांक i2c_class)
अणु
	पूर्णांक rc;

	म_नकल(chan->adapter.name, name);
	chan->adapter.owner = THIS_MODULE;
	chan->adapter.class = i2c_class;
	chan->adapter.algo_data = &chan->algo;
	chan->adapter.dev.parent = &chan->par->pci_dev->dev;
	chan->algo.setsda = nvidia_gpio_setsda;
	chan->algo.setscl = nvidia_gpio_setscl;
	chan->algo.माला_लोda = nvidia_gpio_माला_लोda;
	chan->algo.माला_लोcl = nvidia_gpio_माला_लोcl;
	chan->algo.udelay = 40;
	chan->algo.समयout = msecs_to_jअगरfies(2);
	chan->algo.data = chan;

	i2c_set_adapdata(&chan->adapter, chan);

	/* Raise SCL and SDA */
	nvidia_gpio_setsda(chan, 1);
	nvidia_gpio_setscl(chan, 1);
	udelay(20);

	rc = i2c_bit_add_bus(&chan->adapter);
	अगर (rc == 0)
		dev_dbg(&chan->par->pci_dev->dev,
			"I2C bus %s registered.\n", name);
	अन्यथा अणु
		dev_warn(&chan->par->pci_dev->dev,
			 "Failed to register I2C bus %s.\n", name);
		chan->par = शून्य;
	पूर्ण

	वापस rc;
पूर्ण

व्योम nvidia_create_i2c_busses(काष्ठा nvidia_par *par)
अणु
	par->chan[0].par = par;
	par->chan[1].par = par;
	par->chan[2].par = par;

	par->chan[0].ddc_base = (par->reverse_i2c) ? 0x36 : 0x3e;
 	nvidia_setup_i2c_bus(&par->chan[0], "nvidia #0",
			     (par->reverse_i2c) ? I2C_CLASS_HWMON : 0);

	par->chan[1].ddc_base = (par->reverse_i2c) ? 0x3e : 0x36;
 	nvidia_setup_i2c_bus(&par->chan[1], "nvidia #1",
			     (par->reverse_i2c) ? 0 : I2C_CLASS_HWMON);

	par->chan[2].ddc_base = 0x50;
 	nvidia_setup_i2c_bus(&par->chan[2], "nvidia #2", 0);
पूर्ण

व्योम nvidia_delete_i2c_busses(काष्ठा nvidia_par *par)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < 3; i++) अणु
		अगर (!par->chan[i].par)
			जारी;
		i2c_del_adapter(&par->chan[i].adapter);
		par->chan[i].par = शून्य;
	पूर्ण
पूर्ण

पूर्णांक nvidia_probe_i2c_connector(काष्ठा fb_info *info, पूर्णांक conn, u8 **out_edid)
अणु
	काष्ठा nvidia_par *par = info->par;
	u8 *edid = शून्य;

	अगर (par->chan[conn - 1].par)
		edid = fb_ddc_पढ़ो(&par->chan[conn - 1].adapter);

	अगर (!edid && conn == 1) अणु
		/* try to get from firmware */
		स्थिर u8 *e = fb_firmware_edid(info->device);

		अगर (e != शून्य)
			edid = kmemdup(e, EDID_LENGTH, GFP_KERNEL);
	पूर्ण

	*out_edid = edid;

	वापस (edid) ? 0 : 1;
पूर्ण
