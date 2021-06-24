<शैली गुरु>
/*
 * Copyright (C) 2011 Philippe Rथऊtornaz
 *
 * Based on twl4030-pwrbutton driver by:
 *     Peter De Schrijver <peter.de-schrijver@nokia.com>
 *     Felipe Balbi <felipe.balbi@nokia.com>
 *
 * This file is subject to the terms and conditions of the GNU General
 * Public License. See the file "COPYING" in the मुख्य directory of this
 * archive क्रम more details.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License क्रम more details.
 *
 * You should have received a copy of the GNU General Public License
 * aदीर्घ with this program; अगर not, ग_लिखो to the Free Software
 * Foundation, Inc., 51 Franklin Street, Suite 500, Boston, MA 02110-1335  USA
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/input.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/mfd/mc13783.h>
#समावेश <linux/sched.h>
#समावेश <linux/slab.h>

काष्ठा mc13783_pwrb अणु
	काष्ठा input_dev *pwr;
	काष्ठा mc13xxx *mc13783;
#घोषणा MC13783_PWRB_B1_POL_INVERT	(1 << 0)
#घोषणा MC13783_PWRB_B2_POL_INVERT	(1 << 1)
#घोषणा MC13783_PWRB_B3_POL_INVERT	(1 << 2)
	पूर्णांक flags;
	अचिन्हित लघु keymap[3];
पूर्ण;

#घोषणा MC13783_REG_INTERRUPT_SENSE_1		5
#घोषणा MC13783_IRQSENSE1_ONOFD1S		(1 << 3)
#घोषणा MC13783_IRQSENSE1_ONOFD2S		(1 << 4)
#घोषणा MC13783_IRQSENSE1_ONOFD3S		(1 << 5)

#घोषणा MC13783_REG_POWER_CONTROL_2		15
#घोषणा MC13783_POWER_CONTROL_2_ON1BDBNC	4
#घोषणा MC13783_POWER_CONTROL_2_ON2BDBNC	6
#घोषणा MC13783_POWER_CONTROL_2_ON3BDBNC	8
#घोषणा MC13783_POWER_CONTROL_2_ON1BRSTEN	(1 << 1)
#घोषणा MC13783_POWER_CONTROL_2_ON2BRSTEN	(1 << 2)
#घोषणा MC13783_POWER_CONTROL_2_ON3BRSTEN	(1 << 3)

अटल irqवापस_t button_irq(पूर्णांक irq, व्योम *_priv)
अणु
	काष्ठा mc13783_pwrb *priv = _priv;
	पूर्णांक val;

	mc13xxx_irq_ack(priv->mc13783, irq);
	mc13xxx_reg_पढ़ो(priv->mc13783, MC13783_REG_INTERRUPT_SENSE_1, &val);

	चयन (irq) अणु
	हाल MC13783_IRQ_ONOFD1:
		val = val & MC13783_IRQSENSE1_ONOFD1S ? 1 : 0;
		अगर (priv->flags & MC13783_PWRB_B1_POL_INVERT)
			val ^= 1;
		input_report_key(priv->pwr, priv->keymap[0], val);
		अवरोध;

	हाल MC13783_IRQ_ONOFD2:
		val = val & MC13783_IRQSENSE1_ONOFD2S ? 1 : 0;
		अगर (priv->flags & MC13783_PWRB_B2_POL_INVERT)
			val ^= 1;
		input_report_key(priv->pwr, priv->keymap[1], val);
		अवरोध;

	हाल MC13783_IRQ_ONOFD3:
		val = val & MC13783_IRQSENSE1_ONOFD3S ? 1 : 0;
		अगर (priv->flags & MC13783_PWRB_B3_POL_INVERT)
			val ^= 1;
		input_report_key(priv->pwr, priv->keymap[2], val);
		अवरोध;
	पूर्ण

	input_sync(priv->pwr);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक mc13783_pwrbutton_probe(काष्ठा platक्रमm_device *pdev)
अणु
	स्थिर काष्ठा mc13xxx_buttons_platक्रमm_data *pdata;
	काष्ठा mc13xxx *mc13783 = dev_get_drvdata(pdev->dev.parent);
	काष्ठा input_dev *pwr;
	काष्ठा mc13783_pwrb *priv;
	पूर्णांक err = 0;
	पूर्णांक reg = 0;

	pdata = dev_get_platdata(&pdev->dev);
	अगर (!pdata) अणु
		dev_err(&pdev->dev, "missing platform data\n");
		वापस -ENODEV;
	पूर्ण

	pwr = input_allocate_device();
	अगर (!pwr) अणु
		dev_dbg(&pdev->dev, "Can't allocate power button\n");
		वापस -ENOMEM;
	पूर्ण

	priv = kzalloc(माप(*priv), GFP_KERNEL);
	अगर (!priv) अणु
		err = -ENOMEM;
		dev_dbg(&pdev->dev, "Can't allocate power button\n");
		जाओ मुक्त_input_dev;
	पूर्ण

	reg |= (pdata->b1on_flags & 0x3) << MC13783_POWER_CONTROL_2_ON1BDBNC;
	reg |= (pdata->b2on_flags & 0x3) << MC13783_POWER_CONTROL_2_ON2BDBNC;
	reg |= (pdata->b3on_flags & 0x3) << MC13783_POWER_CONTROL_2_ON3BDBNC;

	priv->pwr = pwr;
	priv->mc13783 = mc13783;

	mc13xxx_lock(mc13783);

	अगर (pdata->b1on_flags & MC13783_BUTTON_ENABLE) अणु
		priv->keymap[0] = pdata->b1on_key;
		अगर (pdata->b1on_key != KEY_RESERVED)
			__set_bit(pdata->b1on_key, pwr->keybit);

		अगर (pdata->b1on_flags & MC13783_BUTTON_POL_INVERT)
			priv->flags |= MC13783_PWRB_B1_POL_INVERT;

		अगर (pdata->b1on_flags & MC13783_BUTTON_RESET_EN)
			reg |= MC13783_POWER_CONTROL_2_ON1BRSTEN;

		err = mc13xxx_irq_request(mc13783, MC13783_IRQ_ONOFD1,
					  button_irq, "b1on", priv);
		अगर (err) अणु
			dev_dbg(&pdev->dev, "Can't request irq\n");
			जाओ मुक्त_priv;
		पूर्ण
	पूर्ण

	अगर (pdata->b2on_flags & MC13783_BUTTON_ENABLE) अणु
		priv->keymap[1] = pdata->b2on_key;
		अगर (pdata->b2on_key != KEY_RESERVED)
			__set_bit(pdata->b2on_key, pwr->keybit);

		अगर (pdata->b2on_flags & MC13783_BUTTON_POL_INVERT)
			priv->flags |= MC13783_PWRB_B2_POL_INVERT;

		अगर (pdata->b2on_flags & MC13783_BUTTON_RESET_EN)
			reg |= MC13783_POWER_CONTROL_2_ON2BRSTEN;

		err = mc13xxx_irq_request(mc13783, MC13783_IRQ_ONOFD2,
					  button_irq, "b2on", priv);
		अगर (err) अणु
			dev_dbg(&pdev->dev, "Can't request irq\n");
			जाओ मुक्त_irq_b1;
		पूर्ण
	पूर्ण

	अगर (pdata->b3on_flags & MC13783_BUTTON_ENABLE) अणु
		priv->keymap[2] = pdata->b3on_key;
		अगर (pdata->b3on_key != KEY_RESERVED)
			__set_bit(pdata->b3on_key, pwr->keybit);

		अगर (pdata->b3on_flags & MC13783_BUTTON_POL_INVERT)
			priv->flags |= MC13783_PWRB_B3_POL_INVERT;

		अगर (pdata->b3on_flags & MC13783_BUTTON_RESET_EN)
			reg |= MC13783_POWER_CONTROL_2_ON3BRSTEN;

		err = mc13xxx_irq_request(mc13783, MC13783_IRQ_ONOFD3,
					  button_irq, "b3on", priv);
		अगर (err) अणु
			dev_dbg(&pdev->dev, "Can't request irq: %d\n", err);
			जाओ मुक्त_irq_b2;
		पूर्ण
	पूर्ण

	mc13xxx_reg_rmw(mc13783, MC13783_REG_POWER_CONTROL_2, 0x3FE, reg);

	mc13xxx_unlock(mc13783);

	pwr->name = "mc13783_pwrbutton";
	pwr->phys = "mc13783_pwrbutton/input0";
	pwr->dev.parent = &pdev->dev;

	pwr->keycode = priv->keymap;
	pwr->keycodemax = ARRAY_SIZE(priv->keymap);
	pwr->keycodesize = माप(priv->keymap[0]);
	__set_bit(EV_KEY, pwr->evbit);

	err = input_रेजिस्टर_device(pwr);
	अगर (err) अणु
		dev_dbg(&pdev->dev, "Can't register power button: %d\n", err);
		जाओ मुक्त_irq;
	पूर्ण

	platक्रमm_set_drvdata(pdev, priv);

	वापस 0;

मुक्त_irq:
	mc13xxx_lock(mc13783);

	अगर (pdata->b3on_flags & MC13783_BUTTON_ENABLE)
		mc13xxx_irq_मुक्त(mc13783, MC13783_IRQ_ONOFD3, priv);

मुक्त_irq_b2:
	अगर (pdata->b2on_flags & MC13783_BUTTON_ENABLE)
		mc13xxx_irq_मुक्त(mc13783, MC13783_IRQ_ONOFD2, priv);

मुक्त_irq_b1:
	अगर (pdata->b1on_flags & MC13783_BUTTON_ENABLE)
		mc13xxx_irq_मुक्त(mc13783, MC13783_IRQ_ONOFD1, priv);

मुक्त_priv:
	mc13xxx_unlock(mc13783);
	kमुक्त(priv);

मुक्त_input_dev:
	input_मुक्त_device(pwr);

	वापस err;
पूर्ण

अटल पूर्णांक mc13783_pwrbutton_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा mc13783_pwrb *priv = platक्रमm_get_drvdata(pdev);
	स्थिर काष्ठा mc13xxx_buttons_platक्रमm_data *pdata;

	pdata = dev_get_platdata(&pdev->dev);

	mc13xxx_lock(priv->mc13783);

	अगर (pdata->b3on_flags & MC13783_BUTTON_ENABLE)
		mc13xxx_irq_मुक्त(priv->mc13783, MC13783_IRQ_ONOFD3, priv);
	अगर (pdata->b2on_flags & MC13783_BUTTON_ENABLE)
		mc13xxx_irq_मुक्त(priv->mc13783, MC13783_IRQ_ONOFD2, priv);
	अगर (pdata->b1on_flags & MC13783_BUTTON_ENABLE)
		mc13xxx_irq_मुक्त(priv->mc13783, MC13783_IRQ_ONOFD1, priv);

	mc13xxx_unlock(priv->mc13783);

	input_unरेजिस्टर_device(priv->pwr);
	kमुक्त(priv);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver mc13783_pwrbutton_driver = अणु
	.probe		= mc13783_pwrbutton_probe,
	.हटाओ		= mc13783_pwrbutton_हटाओ,
	.driver		= अणु
		.name	= "mc13783-pwrbutton",
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(mc13783_pwrbutton_driver);

MODULE_ALIAS("platform:mc13783-pwrbutton");
MODULE_DESCRIPTION("MC13783 Power Button");
MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Philippe Retornaz");
