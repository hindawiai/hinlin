<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश "radeonfb.h"

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/delay.h>
#समावेश <linux/fb.h>


#समावेश <linux/i2c.h>
#समावेश <linux/i2c-algo-bit.h>

#समावेश <यंत्र/पन.स>

#समावेश <video/radeon.h>
#समावेश "../edid.h"

अटल व्योम radeon_gpio_setscl(व्योम* data, पूर्णांक state)
अणु
	काष्ठा radeon_i2c_chan 	*chan = data;
	काष्ठा radeonfb_info	*rinfo = chan->rinfo;
	u32			val;
	
	val = INREG(chan->ddc_reg) & ~(VGA_DDC_CLK_OUT_EN);
	अगर (!state)
		val |= VGA_DDC_CLK_OUT_EN;

	OUTREG(chan->ddc_reg, val);
	(व्योम)INREG(chan->ddc_reg);
पूर्ण

अटल व्योम radeon_gpio_setsda(व्योम* data, पूर्णांक state)
अणु
	काष्ठा radeon_i2c_chan 	*chan = data;
	काष्ठा radeonfb_info	*rinfo = chan->rinfo;
	u32			val;
	
	val = INREG(chan->ddc_reg) & ~(VGA_DDC_DATA_OUT_EN);
	अगर (!state)
		val |= VGA_DDC_DATA_OUT_EN;

	OUTREG(chan->ddc_reg, val);
	(व्योम)INREG(chan->ddc_reg);
पूर्ण

अटल पूर्णांक radeon_gpio_माला_लोcl(व्योम* data)
अणु
	काष्ठा radeon_i2c_chan 	*chan = data;
	काष्ठा radeonfb_info	*rinfo = chan->rinfo;
	u32			val;
	
	val = INREG(chan->ddc_reg);

	वापस (val & VGA_DDC_CLK_INPUT) ? 1 : 0;
पूर्ण

अटल पूर्णांक radeon_gpio_माला_लोda(व्योम* data)
अणु
	काष्ठा radeon_i2c_chan 	*chan = data;
	काष्ठा radeonfb_info	*rinfo = chan->rinfo;
	u32			val;
	
	val = INREG(chan->ddc_reg);

	वापस (val & VGA_DDC_DATA_INPUT) ? 1 : 0;
पूर्ण

अटल पूर्णांक radeon_setup_i2c_bus(काष्ठा radeon_i2c_chan *chan, स्थिर अक्षर *name)
अणु
	पूर्णांक rc;

	snम_लिखो(chan->adapter.name, माप(chan->adapter.name),
		 "radeonfb %s", name);
	chan->adapter.owner		= THIS_MODULE;
	chan->adapter.algo_data		= &chan->algo;
	chan->adapter.dev.parent	= &chan->rinfo->pdev->dev;
	chan->algo.setsda		= radeon_gpio_setsda;
	chan->algo.setscl		= radeon_gpio_setscl;
	chan->algo.माला_लोda		= radeon_gpio_माला_लोda;
	chan->algo.माला_लोcl		= radeon_gpio_माला_लोcl;
	chan->algo.udelay		= 10;
	chan->algo.समयout		= 20;
	chan->algo.data 		= chan;	
	
	i2c_set_adapdata(&chan->adapter, chan);
	
	/* Raise SCL and SDA */
	radeon_gpio_setsda(chan, 1);
	radeon_gpio_setscl(chan, 1);
	udelay(20);

	rc = i2c_bit_add_bus(&chan->adapter);
	अगर (rc == 0)
		dev_dbg(&chan->rinfo->pdev->dev, "I2C bus %s registered.\n", name);
	अन्यथा
		dev_warn(&chan->rinfo->pdev->dev, "Failed to register I2C bus %s.\n", name);
	वापस rc;
पूर्ण

व्योम radeon_create_i2c_busses(काष्ठा radeonfb_info *rinfo)
अणु
	rinfo->i2c[0].rinfo	= rinfo;
	rinfo->i2c[0].ddc_reg	= GPIO_MONID;
#अगर_अघोषित CONFIG_PPC
	rinfo->i2c[0].adapter.class = I2C_CLASS_HWMON;
#पूर्ण_अगर
	radeon_setup_i2c_bus(&rinfo->i2c[0], "monid");

	rinfo->i2c[1].rinfo	= rinfo;
	rinfo->i2c[1].ddc_reg	= GPIO_DVI_DDC;
	radeon_setup_i2c_bus(&rinfo->i2c[1], "dvi");

	rinfo->i2c[2].rinfo	= rinfo;
	rinfo->i2c[2].ddc_reg	= GPIO_VGA_DDC;
	radeon_setup_i2c_bus(&rinfo->i2c[2], "vga");

	rinfo->i2c[3].rinfo	= rinfo;
	rinfo->i2c[3].ddc_reg	= GPIO_CRT2_DDC;
	radeon_setup_i2c_bus(&rinfo->i2c[3], "crt2");
पूर्ण

व्योम radeon_delete_i2c_busses(काष्ठा radeonfb_info *rinfo)
अणु
	अगर (rinfo->i2c[0].rinfo)
		i2c_del_adapter(&rinfo->i2c[0].adapter);
	rinfo->i2c[0].rinfo = शून्य;

	अगर (rinfo->i2c[1].rinfo)
		i2c_del_adapter(&rinfo->i2c[1].adapter);
	rinfo->i2c[1].rinfo = शून्य;

	अगर (rinfo->i2c[2].rinfo)
		i2c_del_adapter(&rinfo->i2c[2].adapter);
	rinfo->i2c[2].rinfo = शून्य;

	अगर (rinfo->i2c[3].rinfo)
		i2c_del_adapter(&rinfo->i2c[3].adapter);
	rinfo->i2c[3].rinfo = शून्य;
पूर्ण

पूर्णांक radeon_probe_i2c_connector(काष्ठा radeonfb_info *rinfo, पूर्णांक conn,
			       u8 **out_edid)
अणु
	u8 *edid;

	edid = fb_ddc_पढ़ो(&rinfo->i2c[conn-1].adapter);

	अगर (out_edid)
		*out_edid = edid;
	अगर (!edid) अणु
		pr_debug("radeonfb: I2C (port %d) ... not found\n", conn);
		वापस MT_NONE;
	पूर्ण
	अगर (edid[0x14] & 0x80) अणु
		/* Fix detection using BIOS tables */
		अगर (rinfo->is_mobility /*&& conn == ddc_dvi*/ &&
		    (INREG(LVDS_GEN_CNTL) & LVDS_ON)) अणु
			pr_debug("radeonfb: I2C (port %d) ... found LVDS panel\n", conn);
			वापस MT_LCD;
		पूर्ण अन्यथा अणु
			pr_debug("radeonfb: I2C (port %d) ... found TMDS panel\n", conn);
			वापस MT_DFP;
		पूर्ण
	पूर्ण
	pr_debug("radeonfb: I2C (port %d) ... found CRT display\n", conn);
	वापस MT_CRT;
पूर्ण

