<शैली गुरु>
/*
 * Copyright 2012 Red Hat Inc.
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modअगरy, merge, publish,
 * distribute, sub license, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to करो so, subject to
 * the following conditions:
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. IN NO EVENT SHALL
 * THE COPYRIGHT HOLDERS, AUTHORS AND/OR ITS SUPPLIERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
 * OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE
 * USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * The above copyright notice and this permission notice (including the
 * next paragraph) shall be included in all copies or substantial portions
 * of the Software.
 *
 */
/*
 * Authors: Dave Airlie <airlied@redhat.com>
 */

#समावेश <linux/export.h>
#समावेश <linux/i2c-algo-bit.h>
#समावेश <linux/i2c.h>
#समावेश <linux/pci.h>

#समावेश "mgag200_drv.h"

अटल पूर्णांक mga_i2c_पढ़ो_gpio(काष्ठा mga_device *mdev)
अणु
	WREG8(DAC_INDEX, MGA1064_GEN_IO_DATA);
	वापस RREG8(DAC_DATA);
पूर्ण

अटल व्योम mga_i2c_set_gpio(काष्ठा mga_device *mdev, पूर्णांक mask, पूर्णांक val)
अणु
	पूर्णांक पंचांगp;

	WREG8(DAC_INDEX, MGA1064_GEN_IO_CTL);
	पंचांगp = (RREG8(DAC_DATA) & mask) | val;
	WREG_DAC(MGA1064_GEN_IO_CTL, पंचांगp);
	WREG_DAC(MGA1064_GEN_IO_DATA, 0);
पूर्ण

अटल अंतरभूत व्योम mga_i2c_set(काष्ठा mga_device *mdev, पूर्णांक mask, पूर्णांक state)
अणु
	अगर (state)
		state = 0;
	अन्यथा
		state = mask;
	mga_i2c_set_gpio(mdev, ~mask, state);
पूर्ण

अटल व्योम mga_gpio_setsda(व्योम *data, पूर्णांक state)
अणु
	काष्ठा mga_i2c_chan *i2c = data;
	काष्ठा mga_device *mdev = to_mga_device(i2c->dev);
	mga_i2c_set(mdev, i2c->data, state);
पूर्ण

अटल व्योम mga_gpio_setscl(व्योम *data, पूर्णांक state)
अणु
	काष्ठा mga_i2c_chan *i2c = data;
	काष्ठा mga_device *mdev = to_mga_device(i2c->dev);
	mga_i2c_set(mdev, i2c->घड़ी, state);
पूर्ण

अटल पूर्णांक mga_gpio_माला_लोda(व्योम *data)
अणु
	काष्ठा mga_i2c_chan *i2c = data;
	काष्ठा mga_device *mdev = to_mga_device(i2c->dev);
	वापस (mga_i2c_पढ़ो_gpio(mdev) & i2c->data) ? 1 : 0;
पूर्ण

अटल पूर्णांक mga_gpio_माला_लोcl(व्योम *data)
अणु
	काष्ठा mga_i2c_chan *i2c = data;
	काष्ठा mga_device *mdev = to_mga_device(i2c->dev);
	वापस (mga_i2c_पढ़ो_gpio(mdev) & i2c->घड़ी) ? 1 : 0;
पूर्ण

काष्ठा mga_i2c_chan *mgag200_i2c_create(काष्ठा drm_device *dev)
अणु
	काष्ठा mga_device *mdev = to_mga_device(dev);
	काष्ठा mga_i2c_chan *i2c;
	पूर्णांक ret;
	पूर्णांक data, घड़ी;

	WREG_DAC(MGA1064_GEN_IO_CTL2, 1);
	WREG_DAC(MGA1064_GEN_IO_DATA, 0xff);
	WREG_DAC(MGA1064_GEN_IO_CTL, 0);

	चयन (mdev->type) अणु
	हाल G200_SE_A:
	हाल G200_SE_B:
	हाल G200_EV:
	हाल G200_WB:
	हाल G200_EW3:
		data = 1;
		घड़ी = 2;
		अवरोध;
	हाल G200_EH:
	हाल G200_EH3:
	हाल G200_ER:
		data = 2;
		घड़ी = 1;
		अवरोध;
	शेष:
		data = 2;
		घड़ी = 8;
		अवरोध;
	पूर्ण

	i2c = kzalloc(माप(काष्ठा mga_i2c_chan), GFP_KERNEL);
	अगर (!i2c)
		वापस शून्य;

	i2c->data = data;
	i2c->घड़ी = घड़ी;
	i2c->adapter.owner = THIS_MODULE;
	i2c->adapter.class = I2C_CLASS_DDC;
	i2c->adapter.dev.parent = dev->dev;
	i2c->dev = dev;
	i2c_set_adapdata(&i2c->adapter, i2c);
	snम_लिखो(i2c->adapter.name, माप(i2c->adapter.name), "mga i2c");

	i2c->adapter.algo_data = &i2c->bit;

	i2c->bit.udelay = 10;
	i2c->bit.समयout = 2;
	i2c->bit.data = i2c;
	i2c->bit.setsda		= mga_gpio_setsda;
	i2c->bit.setscl		= mga_gpio_setscl;
	i2c->bit.माला_लोda		= mga_gpio_माला_लोda;
	i2c->bit.माला_लोcl		= mga_gpio_माला_लोcl;

	ret = i2c_bit_add_bus(&i2c->adapter);
	अगर (ret) अणु
		kमुक्त(i2c);
		i2c = शून्य;
	पूर्ण
	वापस i2c;
पूर्ण

व्योम mgag200_i2c_destroy(काष्ठा mga_i2c_chan *i2c)
अणु
	अगर (!i2c)
		वापस;
	i2c_del_adapter(&i2c->adapter);
	kमुक्त(i2c);
पूर्ण

