<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
#समावेश <linux/input.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/delay.h>
#समावेश <यंत्र/adc.h>
#समावेश <mach/hp6xx.h>

#घोषणा MODNAME "hp680_ts_input"

#घोषणा HP680_TS_ABS_X_MIN	40
#घोषणा HP680_TS_ABS_X_MAX	950
#घोषणा HP680_TS_ABS_Y_MIN	80
#घोषणा HP680_TS_ABS_Y_MAX	910

#घोषणा	PHDR	0xa400012e
#घोषणा SCPDR	0xa4000136

अटल व्योम करो_softपूर्णांक(काष्ठा work_काष्ठा *work);

अटल काष्ठा input_dev *hp680_ts_dev;
अटल DECLARE_DELAYED_WORK(work, करो_softपूर्णांक);

अटल व्योम करो_softपूर्णांक(काष्ठा work_काष्ठा *work)
अणु
	पूर्णांक असलx = 0, असलy = 0;
	u8 scpdr;
	पूर्णांक touched = 0;

	अगर (__raw_पढ़ोb(PHDR) & PHDR_TS_PEN_DOWN) अणु
		scpdr = __raw_पढ़ोb(SCPDR);
		scpdr |= SCPDR_TS_SCAN_ENABLE;
		scpdr &= ~SCPDR_TS_SCAN_Y;
		__raw_ग_लिखोb(scpdr, SCPDR);
		udelay(30);

		असलy = adc_single(ADC_CHANNEL_TS_Y);

		scpdr = __raw_पढ़ोb(SCPDR);
		scpdr |= SCPDR_TS_SCAN_Y;
		scpdr &= ~SCPDR_TS_SCAN_X;
		__raw_ग_लिखोb(scpdr, SCPDR);
		udelay(30);

		असलx = adc_single(ADC_CHANNEL_TS_X);

		scpdr = __raw_पढ़ोb(SCPDR);
		scpdr |= SCPDR_TS_SCAN_X;
		scpdr &= ~SCPDR_TS_SCAN_ENABLE;
		__raw_ग_लिखोb(scpdr, SCPDR);
		udelay(100);
		touched = __raw_पढ़ोb(PHDR) & PHDR_TS_PEN_DOWN;
	पूर्ण

	अगर (touched) अणु
		input_report_key(hp680_ts_dev, BTN_TOUCH, 1);
		input_report_असल(hp680_ts_dev, ABS_X, असलx);
		input_report_असल(hp680_ts_dev, ABS_Y, असलy);
	पूर्ण अन्यथा अणु
		input_report_key(hp680_ts_dev, BTN_TOUCH, 0);
	पूर्ण

	input_sync(hp680_ts_dev);
	enable_irq(HP680_TS_IRQ);
पूर्ण

अटल irqवापस_t hp680_ts_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev)
अणु
	disable_irq_nosync(irq);
	schedule_delayed_work(&work, HZ / 20);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक __init hp680_ts_init(व्योम)
अणु
	पूर्णांक err;

	hp680_ts_dev = input_allocate_device();
	अगर (!hp680_ts_dev)
		वापस -ENOMEM;

	hp680_ts_dev->evbit[0] = BIT_MASK(EV_ABS) | BIT_MASK(EV_KEY);
	hp680_ts_dev->keybit[BIT_WORD(BTN_TOUCH)] = BIT_MASK(BTN_TOUCH);

	input_set_असल_params(hp680_ts_dev, ABS_X,
		HP680_TS_ABS_X_MIN, HP680_TS_ABS_X_MAX, 0, 0);
	input_set_असल_params(hp680_ts_dev, ABS_Y,
		HP680_TS_ABS_Y_MIN, HP680_TS_ABS_Y_MAX, 0, 0);

	hp680_ts_dev->name = "HP Jornada touchscreen";
	hp680_ts_dev->phys = "hp680_ts/input0";

	अगर (request_irq(HP680_TS_IRQ, hp680_ts_पूर्णांकerrupt,
			0, MODNAME, शून्य) < 0) अणु
		prपूर्णांकk(KERN_ERR "hp680_touchscreen.c: Can't allocate irq %d\n",
		       HP680_TS_IRQ);
		err = -EBUSY;
		जाओ fail1;
	पूर्ण

	err = input_रेजिस्टर_device(hp680_ts_dev);
	अगर (err)
		जाओ fail2;

	वापस 0;

 fail2:	मुक्त_irq(HP680_TS_IRQ, शून्य);
	cancel_delayed_work_sync(&work);
 fail1:	input_मुक्त_device(hp680_ts_dev);
	वापस err;
पूर्ण

अटल व्योम __निकास hp680_ts_निकास(व्योम)
अणु
	मुक्त_irq(HP680_TS_IRQ, शून्य);
	cancel_delayed_work_sync(&work);
	input_unरेजिस्टर_device(hp680_ts_dev);
पूर्ण

module_init(hp680_ts_init);
module_निकास(hp680_ts_निकास);

MODULE_AUTHOR("Andriy Skulysh, askulysh@image.kiev.ua");
MODULE_DESCRIPTION("HP Jornada 680 touchscreen driver");
MODULE_LICENSE("GPL");
