<शैली गुरु>
/*
 * Copyright (c) 2002-2010, Intel Corporation.
 * Copyright (c) 2014 ATRON electronic GmbH
 *   Author: Jan Safrata <jan.nikitenko@gmail.com>
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a copy
 * of this software and associated करोcumentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modअगरy, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 */

#समावेश <linux/delay.h>
#समावेश <linux/i2c-algo-bit.h>
#समावेश <linux/i2c.h>
#समावेश <linux/init.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/types.h>

#समावेश "psb_drv.h"
#समावेश "psb_intel_reg.h"


/*
 * LPC GPIO based I2C bus क्रम LVDS of Atom E6xx
 */

/*-----------------------------------------------------------------------------
 * LPC Register Offsets. Used क्रम LVDS GPIO Bit Bashing. Registers are part
 * Atom E6xx [D31:F0]
 ----------------------------------------------------------------------------*/
#घोषणा RGEN    0x20
#घोषणा RGIO    0x24
#घोषणा RGLVL   0x28
#घोषणा RGTPE   0x2C
#घोषणा RGTNE   0x30
#घोषणा RGGPE   0x34
#घोषणा RGSMI   0x38
#घोषणा RGTS    0x3C

/* The LVDS GPIO घड़ी lines are GPIOSUS[3]
 * The LVDS GPIO data lines are GPIOSUS[4]
 */
#घोषणा GPIO_CLOCK	0x08
#घोषणा GPIO_DATA	0x10

#घोषणा LPC_READ_REG(chan, r) inl((chan)->reg + (r))
#घोषणा LPC_WRITE_REG(chan, r, val) outl((val), (chan)->reg + (r))

अटल पूर्णांक get_घड़ी(व्योम *data)
अणु
	काष्ठा psb_पूर्णांकel_i2c_chan *chan = data;
	u32 val;

	val = LPC_READ_REG(chan, RGIO);
	val |= GPIO_CLOCK;
	LPC_WRITE_REG(chan, RGIO, val);
	LPC_READ_REG(chan, RGLVL);
	val = (LPC_READ_REG(chan, RGLVL) & GPIO_CLOCK) ? 1 : 0;

	वापस val;
पूर्ण

अटल पूर्णांक get_data(व्योम *data)
अणु
	काष्ठा psb_पूर्णांकel_i2c_chan *chan = data;
	u32 val;

	val = LPC_READ_REG(chan, RGIO);
	val |= GPIO_DATA;
	LPC_WRITE_REG(chan, RGIO, val);
	LPC_READ_REG(chan, RGLVL);
	val = (LPC_READ_REG(chan, RGLVL) & GPIO_DATA) ? 1 : 0;

	वापस val;
पूर्ण

अटल व्योम set_घड़ी(व्योम *data, पूर्णांक state_high)
अणु
	काष्ठा psb_पूर्णांकel_i2c_chan *chan = data;
	u32 val;

	अगर (state_high) अणु
		val = LPC_READ_REG(chan, RGIO);
		val |= GPIO_CLOCK;
		LPC_WRITE_REG(chan, RGIO, val);
	पूर्ण अन्यथा अणु
		val = LPC_READ_REG(chan, RGIO);
		val &= ~GPIO_CLOCK;
		LPC_WRITE_REG(chan, RGIO, val);
		val = LPC_READ_REG(chan, RGLVL);
		val &= ~GPIO_CLOCK;
		LPC_WRITE_REG(chan, RGLVL, val);
	पूर्ण
पूर्ण

अटल व्योम set_data(व्योम *data, पूर्णांक state_high)
अणु
	काष्ठा psb_पूर्णांकel_i2c_chan *chan = data;
	u32 val;

	अगर (state_high) अणु
		val = LPC_READ_REG(chan, RGIO);
		val |= GPIO_DATA;
		LPC_WRITE_REG(chan, RGIO, val);
	पूर्ण अन्यथा अणु
		val = LPC_READ_REG(chan, RGIO);
		val &= ~GPIO_DATA;
		LPC_WRITE_REG(chan, RGIO, val);
		val = LPC_READ_REG(chan, RGLVL);
		val &= ~GPIO_DATA;
		LPC_WRITE_REG(chan, RGLVL, val);
	पूर्ण
पूर्ण

व्योम oaktrail_lvds_i2c_init(काष्ठा drm_encoder *encoder)
अणु
	काष्ठा drm_device *dev = encoder->dev;
	काष्ठा gma_encoder *gma_encoder = to_gma_encoder(encoder);
	काष्ठा drm_psb_निजी *dev_priv = dev->dev_निजी;
	काष्ठा psb_पूर्णांकel_i2c_chan *chan;

	chan = kzalloc(माप(काष्ठा psb_पूर्णांकel_i2c_chan), GFP_KERNEL);
	अगर (!chan)
		वापस;

	chan->drm_dev = dev;
	chan->reg = dev_priv->lpc_gpio_base;
	म_नकलन(chan->adapter.name, "gma500 LPC",  I2C_NAME_SIZE - 1);
	chan->adapter.owner = THIS_MODULE;
	chan->adapter.algo_data = &chan->algo;
	chan->adapter.dev.parent = dev->dev;
	chan->algo.setsda = set_data;
	chan->algo.setscl = set_घड़ी;
	chan->algo.माला_लोda = get_data;
	chan->algo.माला_लोcl = get_घड़ी;
	chan->algo.udelay = 100;
	chan->algo.समयout = usecs_to_jअगरfies(2200);
	chan->algo.data = chan;

	i2c_set_adapdata(&chan->adapter, chan);

	set_data(chan, 1);
	set_घड़ी(chan, 1);
	udelay(50);

	अगर (i2c_bit_add_bus(&chan->adapter)) अणु
		kमुक्त(chan);
		वापस;
	पूर्ण

	gma_encoder->ddc_bus = chan;
पूर्ण
