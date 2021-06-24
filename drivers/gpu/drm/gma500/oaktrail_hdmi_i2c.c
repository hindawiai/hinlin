<शैली गुरु>
/*
 * Copyright तऊ 2010 Intel Corporation
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the next
 * paragraph) shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 * Authors:
 *	Li Peng <peng.li@पूर्णांकel.com>
 */

#समावेश <linux/export.h>
#समावेश <linux/mutex.h>
#समावेश <linux/pci.h>
#समावेश <linux/i2c.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/delay.h>
#समावेश "psb_drv.h"

#घोषणा HDMI_READ(reg)		पढ़ोl(hdmi_dev->regs + (reg))
#घोषणा HDMI_WRITE(reg, val)	ग_लिखोl(val, hdmi_dev->regs + (reg))

#घोषणा HDMI_HCR	0x1000
#घोषणा HCR_DETECT_HDP		(1 << 6)
#घोषणा HCR_ENABLE_HDCP		(1 << 5)
#घोषणा HCR_ENABLE_AUDIO	(1 << 2)
#घोषणा HCR_ENABLE_PIXEL	(1 << 1)
#घोषणा HCR_ENABLE_TMDS		(1 << 0)
#घोषणा HDMI_HICR	0x1004
#घोषणा HDMI_INTR_I2C_ERROR	(1 << 4)
#घोषणा HDMI_INTR_I2C_FULL	(1 << 3)
#घोषणा HDMI_INTR_I2C_DONE	(1 << 2)
#घोषणा HDMI_INTR_HPD		(1 << 0)
#घोषणा HDMI_HSR	0x1008
#घोषणा HDMI_HISR	0x100C
#घोषणा HDMI_HI2CRDB0	0x1200
#घोषणा HDMI_HI2CHCR	0x1240
#घोषणा HI2C_HDCP_WRITE		(0 << 2)
#घोषणा HI2C_HDCP_RI_READ	(1 << 2)
#घोषणा HI2C_HDCP_READ		(2 << 2)
#घोषणा HI2C_EDID_READ		(3 << 2)
#घोषणा HI2C_READ_CONTINUE	(1 << 1)
#घोषणा HI2C_ENABLE_TRANSACTION	(1 << 0)

#घोषणा HDMI_ICRH	0x1100
#घोषणा HDMI_HI2CTDR0	0x1244
#घोषणा HDMI_HI2CTDR1	0x1248

#घोषणा I2C_STAT_INIT		0
#घोषणा I2C_READ_DONE		1
#घोषणा I2C_TRANSACTION_DONE	2

काष्ठा hdmi_i2c_dev अणु
	काष्ठा i2c_adapter *adap;
	काष्ठा mutex i2c_lock;
	काष्ठा completion complete;
	पूर्णांक status;
	काष्ठा i2c_msg *msg;
	पूर्णांक buf_offset;
पूर्ण;

अटल व्योम hdmi_i2c_irq_enable(काष्ठा oaktrail_hdmi_dev *hdmi_dev)
अणु
	u32 temp;

	temp = HDMI_READ(HDMI_HICR);
	temp |= (HDMI_INTR_I2C_ERROR | HDMI_INTR_I2C_FULL | HDMI_INTR_I2C_DONE);
	HDMI_WRITE(HDMI_HICR, temp);
	HDMI_READ(HDMI_HICR);
पूर्ण

अटल व्योम hdmi_i2c_irq_disable(काष्ठा oaktrail_hdmi_dev *hdmi_dev)
अणु
	HDMI_WRITE(HDMI_HICR, 0x0);
	HDMI_READ(HDMI_HICR);
पूर्ण

अटल पूर्णांक xfer_पढ़ो(काष्ठा i2c_adapter *adap, काष्ठा i2c_msg *pmsg)
अणु
	काष्ठा oaktrail_hdmi_dev *hdmi_dev = i2c_get_adapdata(adap);
	काष्ठा hdmi_i2c_dev *i2c_dev = hdmi_dev->i2c_dev;
	u32 temp;

	i2c_dev->status = I2C_STAT_INIT;
	i2c_dev->msg = pmsg;
	i2c_dev->buf_offset = 0;
	reinit_completion(&i2c_dev->complete);

	/* Enable I2C transaction */
	temp = ((pmsg->len) << 20) | HI2C_EDID_READ | HI2C_ENABLE_TRANSACTION;
	HDMI_WRITE(HDMI_HI2CHCR, temp);
	HDMI_READ(HDMI_HI2CHCR);

	जबतक (i2c_dev->status != I2C_TRANSACTION_DONE)
		रुको_क्रम_completion_पूर्णांकerruptible_समयout(&i2c_dev->complete,
								10 * HZ);

	वापस 0;
पूर्ण

अटल पूर्णांक xfer_ग_लिखो(काष्ठा i2c_adapter *adap, काष्ठा i2c_msg *pmsg)
अणु
	/*
	 * XXX: i2c ग_लिखो seems isn't useful for EDID probe, don't करो anything
	 */
	वापस 0;
पूर्ण

अटल पूर्णांक oaktrail_hdmi_i2c_access(काष्ठा i2c_adapter *adap,
				काष्ठा i2c_msg *pmsg,
				पूर्णांक num)
अणु
	काष्ठा oaktrail_hdmi_dev *hdmi_dev = i2c_get_adapdata(adap);
	काष्ठा hdmi_i2c_dev *i2c_dev = hdmi_dev->i2c_dev;
	पूर्णांक i;

	mutex_lock(&i2c_dev->i2c_lock);

	/* Enable i2c unit */
	HDMI_WRITE(HDMI_ICRH, 0x00008760);

	/* Enable irq */
	hdmi_i2c_irq_enable(hdmi_dev);
	क्रम (i = 0; i < num; i++) अणु
		अगर (pmsg->len && pmsg->buf) अणु
			अगर (pmsg->flags & I2C_M_RD)
				xfer_पढ़ो(adap, pmsg);
			अन्यथा
				xfer_ग_लिखो(adap, pmsg);
		पूर्ण
		pmsg++;         /* next message */
	पूर्ण

	/* Disable irq */
	hdmi_i2c_irq_disable(hdmi_dev);

	mutex_unlock(&i2c_dev->i2c_lock);

	वापस i;
पूर्ण

अटल u32 oaktrail_hdmi_i2c_func(काष्ठा i2c_adapter *adapter)
अणु
	वापस I2C_FUNC_I2C | I2C_FUNC_10BIT_ADDR;
पूर्ण

अटल स्थिर काष्ठा i2c_algorithm oaktrail_hdmi_i2c_algorithm = अणु
	.master_xfer	= oaktrail_hdmi_i2c_access,
	.functionality  = oaktrail_hdmi_i2c_func,
पूर्ण;

अटल काष्ठा i2c_adapter oaktrail_hdmi_i2c_adapter = अणु
	.name		= "oaktrail_hdmi_i2c",
	.nr		= 3,
	.owner		= THIS_MODULE,
	.class		= I2C_CLASS_DDC,
	.algo		= &oaktrail_hdmi_i2c_algorithm,
पूर्ण;

अटल व्योम hdmi_i2c_पढ़ो(काष्ठा oaktrail_hdmi_dev *hdmi_dev)
अणु
	काष्ठा hdmi_i2c_dev *i2c_dev = hdmi_dev->i2c_dev;
	काष्ठा i2c_msg *msg = i2c_dev->msg;
	u8 *buf = msg->buf;
	u32 temp;
	पूर्णांक i, offset;

	offset = i2c_dev->buf_offset;
	क्रम (i = 0; i < 0x10; i++) अणु
		temp = HDMI_READ(HDMI_HI2CRDB0 + (i * 4));
		स_नकल(buf + (offset + i * 4), &temp, 4);
	पूर्ण
	i2c_dev->buf_offset += (0x10 * 4);

	/* clearing पढ़ो buffer full पूर्णांकr */
	temp = HDMI_READ(HDMI_HISR);
	HDMI_WRITE(HDMI_HISR, temp | HDMI_INTR_I2C_FULL);
	HDMI_READ(HDMI_HISR);

	/* जारी पढ़ो transaction */
	temp = HDMI_READ(HDMI_HI2CHCR);
	HDMI_WRITE(HDMI_HI2CHCR, temp | HI2C_READ_CONTINUE);
	HDMI_READ(HDMI_HI2CHCR);

	i2c_dev->status = I2C_READ_DONE;
	वापस;
पूर्ण

अटल व्योम hdmi_i2c_transaction_करोne(काष्ठा oaktrail_hdmi_dev *hdmi_dev)
अणु
	काष्ठा hdmi_i2c_dev *i2c_dev = hdmi_dev->i2c_dev;
	u32 temp;

	/* clear transaction करोne पूर्णांकr */
	temp = HDMI_READ(HDMI_HISR);
	HDMI_WRITE(HDMI_HISR, temp | HDMI_INTR_I2C_DONE);
	HDMI_READ(HDMI_HISR);


	temp = HDMI_READ(HDMI_HI2CHCR);
	HDMI_WRITE(HDMI_HI2CHCR, temp & ~HI2C_ENABLE_TRANSACTION);
	HDMI_READ(HDMI_HI2CHCR);

	i2c_dev->status = I2C_TRANSACTION_DONE;
	वापस;
पूर्ण

अटल irqवापस_t oaktrail_hdmi_i2c_handler(पूर्णांक this_irq, व्योम *dev)
अणु
	काष्ठा oaktrail_hdmi_dev *hdmi_dev = dev;
	काष्ठा hdmi_i2c_dev *i2c_dev = hdmi_dev->i2c_dev;
	u32 stat;

	stat = HDMI_READ(HDMI_HISR);

	अगर (stat & HDMI_INTR_HPD) अणु
		HDMI_WRITE(HDMI_HISR, stat | HDMI_INTR_HPD);
		HDMI_READ(HDMI_HISR);
	पूर्ण

	अगर (stat & HDMI_INTR_I2C_FULL)
		hdmi_i2c_पढ़ो(hdmi_dev);

	अगर (stat & HDMI_INTR_I2C_DONE)
		hdmi_i2c_transaction_करोne(hdmi_dev);

	complete(&i2c_dev->complete);

	वापस IRQ_HANDLED;
पूर्ण

/*
 * choose alternate function 2 of GPIO pin 52, 53,
 * which is used by HDMI I2C logic
 */
अटल व्योम oaktrail_hdmi_i2c_gpio_fix(व्योम)
अणु
	व्योम __iomem *base;
	अचिन्हित पूर्णांक gpio_base = 0xff12c000;
	पूर्णांक gpio_len = 0x1000;
	u32 temp;

	base = ioremap((resource_माप_प्रकार)gpio_base, gpio_len);
	अगर (base == शून्य) अणु
		DRM_ERROR("gpio ioremap fail\n");
		वापस;
	पूर्ण

	temp = पढ़ोl(base + 0x44);
	DRM_DEBUG_DRIVER("old gpio val %x\n", temp);
	ग_लिखोl((temp | 0x00000a00), (base +  0x44));
	temp = पढ़ोl(base + 0x44);
	DRM_DEBUG_DRIVER("new gpio val %x\n", temp);

	iounmap(base);
पूर्ण

पूर्णांक oaktrail_hdmi_i2c_init(काष्ठा pci_dev *dev)
अणु
	काष्ठा oaktrail_hdmi_dev *hdmi_dev;
	काष्ठा hdmi_i2c_dev *i2c_dev;
	पूर्णांक ret;

	hdmi_dev = pci_get_drvdata(dev);

	i2c_dev = kzalloc(माप(काष्ठा hdmi_i2c_dev), GFP_KERNEL);
	अगर (!i2c_dev)
		वापस -ENOMEM;

	i2c_dev->adap = &oaktrail_hdmi_i2c_adapter;
	i2c_dev->status = I2C_STAT_INIT;
	init_completion(&i2c_dev->complete);
	mutex_init(&i2c_dev->i2c_lock);
	i2c_set_adapdata(&oaktrail_hdmi_i2c_adapter, hdmi_dev);
	hdmi_dev->i2c_dev = i2c_dev;

	/* Enable HDMI I2C function on gpio */
	oaktrail_hdmi_i2c_gpio_fix();

	/* request irq */
	ret = request_irq(dev->irq, oaktrail_hdmi_i2c_handler, IRQF_SHARED,
			  oaktrail_hdmi_i2c_adapter.name, hdmi_dev);
	अगर (ret) अणु
		DRM_ERROR("Failed to request IRQ for I2C controller\n");
		जाओ मुक्त_dev;
	पूर्ण

	/* Adapter registration */
	ret = i2c_add_numbered_adapter(&oaktrail_hdmi_i2c_adapter);
	अगर (ret) अणु
		DRM_ERROR("Failed to add I2C adapter\n");
		जाओ मुक्त_irq;
	पूर्ण

	वापस 0;

मुक्त_irq:
	मुक्त_irq(dev->irq, hdmi_dev);
मुक्त_dev:
	kमुक्त(i2c_dev);

	वापस ret;
पूर्ण

व्योम oaktrail_hdmi_i2c_निकास(काष्ठा pci_dev *dev)
अणु
	काष्ठा oaktrail_hdmi_dev *hdmi_dev;
	काष्ठा hdmi_i2c_dev *i2c_dev;

	hdmi_dev = pci_get_drvdata(dev);
	i2c_del_adapter(&oaktrail_hdmi_i2c_adapter);

	i2c_dev = hdmi_dev->i2c_dev;
	kमुक्त(i2c_dev);
	मुक्त_irq(dev->irq, hdmi_dev);
पूर्ण
