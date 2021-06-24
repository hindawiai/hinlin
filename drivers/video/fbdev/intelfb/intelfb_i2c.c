<शैली गुरु>
/**************************************************************************

 Copyright 2006 Dave Airlie <airlied@linux.ie>

All Rights Reserved.

Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
copy of this software and associated करोcumentation files (the "Software"),
to deal in the Software without restriction, including without limitation
on the rights to use, copy, modअगरy, merge, publish, distribute, sub
license, and/or sell copies of the Software, and to permit persons to whom
the Software is furnished to करो so, subject to the following conditions:

The above copyright notice and this permission notice (including the next
paragraph) shall be included in all copies or substantial portions of the
Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. IN NO EVENT SHALL
THE COPYRIGHT HOLDERS AND/OR THEIR SUPPLIERS BE LIABLE FOR ANY CLAIM,
DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE
USE OR OTHER DEALINGS IN THE SOFTWARE.

**************************************************************************/

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/delay.h>
#समावेश <linux/pci.h>
#समावेश <linux/fb.h>

#समावेश <linux/i2c.h>
#समावेश <linux/i2c-algo-bit.h>

#समावेश <यंत्र/पन.स>

#समावेश "intelfb.h"
#समावेश "intelfbhw.h"

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

अटल व्योम पूर्णांकelfb_gpio_setscl(व्योम *data, पूर्णांक state)
अणु
	काष्ठा पूर्णांकelfb_i2c_chan *chan = data;
	काष्ठा पूर्णांकelfb_info *dinfo = chan->dinfo;
	u32 val;

	OUTREG(chan->reg, (state ? SCL_VAL_OUT : 0) |
	       SCL_सूची | SCL_सूची_MASK | SCL_VAL_MASK);
	val = INREG(chan->reg);
पूर्ण

अटल व्योम पूर्णांकelfb_gpio_setsda(व्योम *data, पूर्णांक state)
अणु
	काष्ठा पूर्णांकelfb_i2c_chan *chan = data;
	काष्ठा पूर्णांकelfb_info *dinfo = chan->dinfo;
	u32 val;

	OUTREG(chan->reg, (state ? SDA_VAL_OUT : 0) |
	       SDA_सूची | SDA_सूची_MASK | SDA_VAL_MASK);
	val = INREG(chan->reg);
पूर्ण

अटल पूर्णांक पूर्णांकelfb_gpio_माला_लोcl(व्योम *data)
अणु
	काष्ठा पूर्णांकelfb_i2c_chan *chan = data;
	काष्ठा पूर्णांकelfb_info *dinfo = chan->dinfo;
	u32 val;

	OUTREG(chan->reg, SCL_सूची_MASK);
	OUTREG(chan->reg, 0);
	val = INREG(chan->reg);
	वापस ((val & SCL_VAL_IN) != 0);
पूर्ण

अटल पूर्णांक पूर्णांकelfb_gpio_माला_लोda(व्योम *data)
अणु
	काष्ठा पूर्णांकelfb_i2c_chan *chan = data;
	काष्ठा पूर्णांकelfb_info *dinfo = chan->dinfo;
	u32 val;

	OUTREG(chan->reg, SDA_सूची_MASK);
	OUTREG(chan->reg, 0);
	val = INREG(chan->reg);
	वापस ((val & SDA_VAL_IN) != 0);
पूर्ण

अटल पूर्णांक पूर्णांकelfb_setup_i2c_bus(काष्ठा पूर्णांकelfb_info *dinfo,
				 काष्ठा पूर्णांकelfb_i2c_chan *chan,
				 स्थिर u32 reg, स्थिर अक्षर *name,
				 पूर्णांक class)
अणु
	पूर्णांक rc;

	chan->dinfo			= dinfo;
	chan->reg			= reg;
	snम_लिखो(chan->adapter.name, माप(chan->adapter.name),
		 "intelfb %s", name);
	chan->adapter.class		= class;
	chan->adapter.owner		= THIS_MODULE;
	chan->adapter.algo_data		= &chan->algo;
	chan->adapter.dev.parent	= &chan->dinfo->pdev->dev;
	chan->algo.setsda		= पूर्णांकelfb_gpio_setsda;
	chan->algo.setscl		= पूर्णांकelfb_gpio_setscl;
	chan->algo.माला_लोda		= पूर्णांकelfb_gpio_माला_लोda;
	chan->algo.माला_लोcl		= पूर्णांकelfb_gpio_माला_लोcl;
	chan->algo.udelay		= 40;
	chan->algo.समयout		= 20;
	chan->algo.data			= chan;

	i2c_set_adapdata(&chan->adapter, chan);

	/* Raise SCL and SDA */
	पूर्णांकelfb_gpio_setsda(chan, 1);
	पूर्णांकelfb_gpio_setscl(chan, 1);
	udelay(20);

	rc = i2c_bit_add_bus(&chan->adapter);
	अगर (rc == 0)
		DBG_MSG("I2C bus %s registered.\n", name);
	अन्यथा
		WRN_MSG("Failed to register I2C bus %s.\n", name);
	वापस rc;
पूर्ण

व्योम पूर्णांकelfb_create_i2c_busses(काष्ठा पूर्णांकelfb_info *dinfo)
अणु
	पूर्णांक i = 0;

	/* everyone has at least a single analog output */
	dinfo->num_outमाला_दो = 1;
	dinfo->output[i].type = INTELFB_OUTPUT_ANALOG;

	/* setup the DDC bus क्रम analog output */
	पूर्णांकelfb_setup_i2c_bus(dinfo, &dinfo->output[i].ddc_bus, GPIOA,
			      "CRTDDC_A", I2C_CLASS_DDC);
	i++;

	/* need to add the output busses क्रम each device
	   - this function is very incomplete
	   - i915GM has LVDS and TVOUT क्रम example
	*/
	चयन(dinfo->chipset) अणु
	हाल INTEL_830M:
	हाल INTEL_845G:
	हाल INTEL_854:
	हाल INTEL_855GM:
	हाल INTEL_865G:
		dinfo->output[i].type = INTELFB_OUTPUT_DVO;
		पूर्णांकelfb_setup_i2c_bus(dinfo, &dinfo->output[i].ddc_bus,
				      GPIOD, "DVODDC_D", I2C_CLASS_DDC);
		पूर्णांकelfb_setup_i2c_bus(dinfo, &dinfo->output[i].i2c_bus,
				      GPIOE, "DVOI2C_E", 0);
		i++;
		अवरोध;
	हाल INTEL_915G:
	हाल INTEL_915GM:
		/* has some LVDS + tv-out */
	हाल INTEL_945G:
	हाल INTEL_945GM:
	हाल INTEL_945GME:
	हाल INTEL_965G:
	हाल INTEL_965GM:
		/* SDVO ports have a single control bus - 2 devices */
		dinfo->output[i].type = INTELFB_OUTPUT_SDVO;
		पूर्णांकelfb_setup_i2c_bus(dinfo, &dinfo->output[i].i2c_bus,
				      GPIOE, "SDVOCTRL_E", 0);
		/* TODO: initialize the SDVO */
		/* I830SDVOInit(pScrn, i, DVOB); */
		i++;

		/* set up SDVOC */
		dinfo->output[i].type = INTELFB_OUTPUT_SDVO;
		dinfo->output[i].i2c_bus = dinfo->output[i - 1].i2c_bus;
		/* TODO: initialize the SDVO */
		/* I830SDVOInit(pScrn, i, DVOC); */
		i++;
		अवरोध;
	पूर्ण
	dinfo->num_outमाला_दो = i;
पूर्ण

व्योम पूर्णांकelfb_delete_i2c_busses(काष्ठा पूर्णांकelfb_info *dinfo)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < MAX_OUTPUTS; i++) अणु
		अगर (dinfo->output[i].i2c_bus.dinfo) अणु
			i2c_del_adapter(&dinfo->output[i].i2c_bus.adapter);
			dinfo->output[i].i2c_bus.dinfo = शून्य;
		पूर्ण
		अगर (dinfo->output[i].ddc_bus.dinfo) अणु
			i2c_del_adapter(&dinfo->output[i].ddc_bus.adapter);
			dinfo->output[i].ddc_bus.dinfo = शून्य;
		पूर्ण
	पूर्ण
पूर्ण
