<शैली गुरु>
 /*-*- linux-c -*-
 *  linux/drivers/video/i810-i2c.c -- Intel 810/815 I2C support
 *
 *      Copyright (C) 2004 Antonino Daplas<adaplas@pol.net>
 *      All Rights Reserved
 *
 *  This file is subject to the terms and conditions of the GNU General Public
 *  License. See the file COPYING in the मुख्य directory of this archive क्रम
 *  more details.
 */
#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/delay.h>
#समावेश <linux/gfp.h>
#समावेश <linux/pci.h>
#समावेश <linux/fb.h>
#समावेश "i810.h"
#समावेश "i810_regs.h"
#समावेश "i810_main.h"
#समावेश "../edid.h"

/* bit locations in the रेजिस्टरs */
#घोषणा SCL_सूची_MASK		0x0001
#घोषणा SCL_सूची			0x0002
#घोषणा SCL_VAL_MASK		0x0004
#घोषणा SCL_VAL_OUT		0x0008
#घोषणा SCL_VAL_IN		0x0010
#घोषणा SDA_सूची_MASK		0x0100
#घोषणा SDA_सूची			0x0200
#घोषणा SDA_VAL_MASK		0x0400
#घोषणा SDA_VAL_OUT		0x0800
#घोषणा SDA_VAL_IN		0x1000

#घोषणा DEBUG  /* define this क्रम verbose EDID parsing output */

#अगर_घोषित DEBUG
#घोषणा DPRINTK(fmt, args...) prपूर्णांकk(fmt,## args)
#अन्यथा
#घोषणा DPRINTK(fmt, args...)
#पूर्ण_अगर

अटल व्योम i810i2c_setscl(व्योम *data, पूर्णांक state)
अणु
        काष्ठा i810fb_i2c_chan    *chan = data;
        काष्ठा i810fb_par         *par = chan->par;
	u8                        __iomem *mmio = par->mmio_start_भव;

	अगर (state)
		i810_ग_लिखोl(mmio, chan->ddc_base, SCL_सूची_MASK | SCL_VAL_MASK);
	अन्यथा
		i810_ग_लिखोl(mmio, chan->ddc_base, SCL_सूची | SCL_सूची_MASK | SCL_VAL_MASK);
	i810_पढ़ोl(mmio, chan->ddc_base);	/* flush posted ग_लिखो */
पूर्ण

अटल व्योम i810i2c_setsda(व्योम *data, पूर्णांक state)
अणु
        काष्ठा i810fb_i2c_chan    *chan = data;
        काष्ठा i810fb_par         *par = chan->par;
	u8                        __iomem *mmio = par->mmio_start_भव;

	अगर (state)
		i810_ग_लिखोl(mmio, chan->ddc_base, SDA_सूची_MASK | SDA_VAL_MASK);
	अन्यथा
		i810_ग_लिखोl(mmio, chan->ddc_base, SDA_सूची | SDA_सूची_MASK | SDA_VAL_MASK);
	i810_पढ़ोl(mmio, chan->ddc_base);	/* flush posted ग_लिखो */
पूर्ण

अटल पूर्णांक i810i2c_माला_लोcl(व्योम *data)
अणु
        काष्ठा i810fb_i2c_chan    *chan = data;
        काष्ठा i810fb_par         *par = chan->par;
	u8                        __iomem *mmio = par->mmio_start_भव;

	i810_ग_लिखोl(mmio, chan->ddc_base, SCL_सूची_MASK);
	i810_ग_लिखोl(mmio, chan->ddc_base, 0);
	वापस ((i810_पढ़ोl(mmio, chan->ddc_base) & SCL_VAL_IN) != 0);
पूर्ण

अटल पूर्णांक i810i2c_माला_लोda(व्योम *data)
अणु
        काष्ठा i810fb_i2c_chan    *chan = data;
        काष्ठा i810fb_par         *par = chan->par;
	u8                        __iomem *mmio = par->mmio_start_भव;

	i810_ग_लिखोl(mmio, chan->ddc_base, SDA_सूची_MASK);
	i810_ग_लिखोl(mmio, chan->ddc_base, 0);
	वापस ((i810_पढ़ोl(mmio, chan->ddc_base) & SDA_VAL_IN) != 0);
पूर्ण

अटल पूर्णांक i810_setup_i2c_bus(काष्ठा i810fb_i2c_chan *chan, स्थिर अक्षर *name)
अणु
        पूर्णांक rc;

        म_नकल(chan->adapter.name, name);
        chan->adapter.owner             = THIS_MODULE;
        chan->adapter.algo_data         = &chan->algo;
        chan->adapter.dev.parent        = &chan->par->dev->dev;
	chan->algo.setsda               = i810i2c_setsda;
	chan->algo.setscl               = i810i2c_setscl;
	chan->algo.माला_लोda               = i810i2c_माला_लोda;
	chan->algo.माला_लोcl               = i810i2c_माला_लोcl;
	chan->algo.udelay               = 10;
        chan->algo.समयout              = (HZ/2);
        chan->algo.data                 = chan;

        i2c_set_adapdata(&chan->adapter, chan);

        /* Raise SCL and SDA */
        chan->algo.setsda(chan, 1);
        chan->algo.setscl(chan, 1);
        udelay(20);

        rc = i2c_bit_add_bus(&chan->adapter);

        अगर (rc == 0)
                dev_dbg(&chan->par->dev->dev, "I2C bus %s registered.\n",name);
        अन्यथा अणु
                dev_warn(&chan->par->dev->dev, "Failed to register I2C bus "
			 "%s.\n", name);
		chan->par = शून्य;
	पूर्ण

        वापस rc;
पूर्ण

व्योम i810_create_i2c_busses(काष्ठा i810fb_par *par)
अणु
        par->chan[0].par        = par;
	par->chan[1].par        = par;
	par->chan[2].par        = par;

	par->chan[0].ddc_base = GPIOA;
	i810_setup_i2c_bus(&par->chan[0], "I810-DDC");
	par->chan[1].ddc_base = GPIOB;
	i810_setup_i2c_bus(&par->chan[1], "I810-I2C");
	par->chan[2].ddc_base = GPIOC;
	i810_setup_i2c_bus(&par->chan[2], "I810-GPIOC");
पूर्ण

व्योम i810_delete_i2c_busses(काष्ठा i810fb_par *par)
अणु
        अगर (par->chan[0].par)
		i2c_del_adapter(&par->chan[0].adapter);
        par->chan[0].par = शून्य;

	अगर (par->chan[1].par)
		i2c_del_adapter(&par->chan[1].adapter);
	par->chan[1].par = शून्य;

	अगर (par->chan[2].par)
		i2c_del_adapter(&par->chan[2].adapter);
	par->chan[2].par = शून्य;
पूर्ण

पूर्णांक i810_probe_i2c_connector(काष्ठा fb_info *info, u8 **out_edid, पूर्णांक conn)
अणु
	काष्ठा i810fb_par *par = info->par;
        u8 *edid = शून्य;

	DPRINTK("i810-i2c: Probe DDC%i Bus\n", conn+1);
	अगर (conn < par->ddc_num) अणु
		edid = fb_ddc_पढ़ो(&par->chan[conn].adapter);
	पूर्ण अन्यथा अणु
		स्थिर u8 *e = fb_firmware_edid(info->device);

		अगर (e != शून्य) अणु
			DPRINTK("i810-i2c: Getting EDID from BIOS\n");
			edid = kmemdup(e, EDID_LENGTH, GFP_KERNEL);
		पूर्ण
	पूर्ण

	*out_edid = edid;

        वापस (edid) ? 0 : 1;
पूर्ण
