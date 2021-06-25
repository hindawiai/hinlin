<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * मुख्यstone-wm97xx.c  --  Mainstone Continuous Touch screen driver क्रम
 *                         Wolfson WM97xx AC97 Codecs.
 *
 * Copyright 2004, 2007 Wolfson Microelectronics PLC.
 * Author: Liam Girdwood <lrg@slimlogic.co.uk>
 * Parts Copyright : Ian Molton <spyro@f2s.com>
 *                   Andrew Zabolotny <zap@homelink.ru>
 *
 * Notes:
 *     This is a wm97xx extended touch driver to capture touch
 *     data in a continuous manner on the Intel XScale architecture
 *
 *  Features:
 *       - codecs supported:- WM9705, WM9712, WM9713
 *       - processors supported:- Intel XScale PXA25x, PXA26x, PXA27x
 */

#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/kernel.h>
#समावेश <linux/delay.h>
#समावेश <linux/irq.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/wm97xx.h>
#समावेश <linux/पन.स>
#समावेश <linux/gpपन.स>

#समावेश <mach/regs-ac97.h>

#समावेश <यंत्र/mach-types.h>

काष्ठा continuous अणु
	u16 id;    /* codec id */
	u8 code;   /* continuous code */
	u8 पढ़ोs;  /* number of coord पढ़ोs per पढ़ो cycle */
	u32 speed; /* number of coords per second */
पूर्ण;

#घोषणा WM_READS(sp) ((sp / HZ) + 1)

अटल स्थिर काष्ठा continuous cinfo[] = अणु
	अणुWM9705_ID2, 0, WM_READS(94), 94पूर्ण,
	अणुWM9705_ID2, 1, WM_READS(188), 188पूर्ण,
	अणुWM9705_ID2, 2, WM_READS(375), 375पूर्ण,
	अणुWM9705_ID2, 3, WM_READS(750), 750पूर्ण,
	अणुWM9712_ID2, 0, WM_READS(94), 94पूर्ण,
	अणुWM9712_ID2, 1, WM_READS(188), 188पूर्ण,
	अणुWM9712_ID2, 2, WM_READS(375), 375पूर्ण,
	अणुWM9712_ID2, 3, WM_READS(750), 750पूर्ण,
	अणुWM9713_ID2, 0, WM_READS(94), 94पूर्ण,
	अणुWM9713_ID2, 1, WM_READS(120), 120पूर्ण,
	अणुWM9713_ID2, 2, WM_READS(154), 154पूर्ण,
	अणुWM9713_ID2, 3, WM_READS(188), 188पूर्ण,
पूर्ण;

/* continuous speed index */
अटल पूर्णांक sp_idx;
अटल u16 last, tries;
अटल पूर्णांक irq;

/*
 * Pen sampling frequency (Hz) in continuous mode.
 */
अटल पूर्णांक cont_rate = 200;
module_param(cont_rate, पूर्णांक, 0);
MODULE_PARM_DESC(cont_rate, "Sampling rate in continuous mode (Hz)");

/*
 * Pen करोwn detection.
 *
 * This driver can either poll or use an पूर्णांकerrupt to indicate a pen करोwn
 * event. If the irq request fails then it will fall back to polling mode.
 */
अटल पूर्णांक pen_पूर्णांक;
module_param(pen_पूर्णांक, पूर्णांक, 0);
MODULE_PARM_DESC(pen_पूर्णांक, "Pen down detection (1 = interrupt, 0 = polling)");

/*
 * Pressure पढ़ोback.
 *
 * Set to 1 to पढ़ो back pen करोwn pressure
 */
अटल पूर्णांक pressure;
module_param(pressure, पूर्णांक, 0);
MODULE_PARM_DESC(pressure, "Pressure readback (1 = pressure, 0 = no pressure)");

/*
 * AC97 touch data slot.
 *
 * Touch screen पढ़ोback data ac97 slot
 */
अटल पूर्णांक ac97_touch_slot = 5;
module_param(ac97_touch_slot, पूर्णांक, 0);
MODULE_PARM_DESC(ac97_touch_slot, "Touch screen data slot AC97 number");


/* flush AC97 slot 5 FIFO on pxa machines */
#अगर_घोषित CONFIG_PXA27x
अटल व्योम wm97xx_acc_pen_up(काष्ठा wm97xx *wm)
अणु
	schedule_समयout_unपूर्णांकerruptible(1);

	जबतक (MISR & (1 << 2))
		MODR;
पूर्ण
#अन्यथा
अटल व्योम wm97xx_acc_pen_up(काष्ठा wm97xx *wm)
अणु
	अचिन्हित पूर्णांक count;

	schedule_समयout_unपूर्णांकerruptible(1);

	क्रम (count = 0; count < 16; count++)
		MODR;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक wm97xx_acc_pen_करोwn(काष्ठा wm97xx *wm)
अणु
	u16 x, y, p = 0x100 | WM97XX_ADCSEL_PRES;
	पूर्णांक पढ़ोs = 0;

	/* When the AC97 queue has been drained we need to allow समय
	 * to buffer up samples otherwise we end up spinning polling
	 * क्रम samples.  The controller can't have a suitably low
	 * threshold set to use the notअगरications it gives.
	 */
	schedule_समयout_unपूर्णांकerruptible(1);

	अगर (tries > 5) अणु
		tries = 0;
		वापस RC_PENUP;
	पूर्ण

	x = MODR;
	अगर (x == last) अणु
		tries++;
		वापस RC_AGAIN;
	पूर्ण
	last = x;
	करो अणु
		अगर (पढ़ोs)
			x = MODR;
		y = MODR;
		अगर (pressure)
			p = MODR;

		dev_dbg(wm->dev, "Raw coordinates: x=%x, y=%x, p=%x\n",
			x, y, p);

		/* are samples valid */
		अगर ((x & WM97XX_ADCSEL_MASK) != WM97XX_ADCSEL_X ||
		    (y & WM97XX_ADCSEL_MASK) != WM97XX_ADCSEL_Y ||
		    (p & WM97XX_ADCSEL_MASK) != WM97XX_ADCSEL_PRES)
			जाओ up;

		/* coordinate is good */
		tries = 0;
		input_report_असल(wm->input_dev, ABS_X, x & 0xfff);
		input_report_असल(wm->input_dev, ABS_Y, y & 0xfff);
		input_report_असल(wm->input_dev, ABS_PRESSURE, p & 0xfff);
		input_report_key(wm->input_dev, BTN_TOUCH, (p != 0));
		input_sync(wm->input_dev);
		पढ़ोs++;
	पूर्ण जबतक (पढ़ोs < cinfo[sp_idx].पढ़ोs);
up:
	वापस RC_PENDOWN | RC_AGAIN;
पूर्ण

अटल पूर्णांक wm97xx_acc_startup(काष्ठा wm97xx *wm)
अणु
	पूर्णांक idx = 0, ret = 0;

	/* check we have a codec */
	अगर (wm->ac97 == शून्य)
		वापस -ENODEV;

	/* Go you big red fire engine */
	क्रम (idx = 0; idx < ARRAY_SIZE(cinfo); idx++) अणु
		अगर (wm->id != cinfo[idx].id)
			जारी;
		sp_idx = idx;
		अगर (cont_rate <= cinfo[idx].speed)
			अवरोध;
	पूर्ण
	wm->acc_rate = cinfo[sp_idx].code;
	wm->acc_slot = ac97_touch_slot;
	dev_info(wm->dev,
		 "mainstone accelerated touchscreen driver, %d samples/sec\n",
		 cinfo[sp_idx].speed);

	/* IRQ driven touchscreen is used on Palm hardware */
	अगर (machine_is_palmt5() || machine_is_palmtx() || machine_is_palmld()) अणु
		pen_पूर्णांक = 1;
		irq = 27;
		/* There is some obscure mutant of WM9712 पूर्णांकerbred with WM9713
		 * used on Palm HW */
		wm->variant = WM97xx_WM1613;
	पूर्ण अन्यथा अगर (machine_is_मुख्यstone() && pen_पूर्णांक)
		irq = 4;

	अगर (irq) अणु
		ret = gpio_request(irq, "Touchscreen IRQ");
		अगर (ret)
			जाओ out;

		ret = gpio_direction_input(irq);
		अगर (ret) अणु
			gpio_मुक्त(irq);
			जाओ out;
		पूर्ण

		wm->pen_irq = gpio_to_irq(irq);
		irq_set_irq_type(wm->pen_irq, IRQ_TYPE_EDGE_BOTH);
	पूर्ण अन्यथा /* pen irq not supported */
		pen_पूर्णांक = 0;

	/* codec specअगरic irq config */
	अगर (pen_पूर्णांक) अणु
		चयन (wm->id) अणु
		हाल WM9705_ID2:
			अवरोध;
		हाल WM9712_ID2:
		हाल WM9713_ID2:
			/* use PEN_DOWN GPIO 13 to निश्चित IRQ on GPIO line 2 */
			wm97xx_config_gpio(wm, WM97XX_GPIO_13, WM97XX_GPIO_IN,
					   WM97XX_GPIO_POL_HIGH,
					   WM97XX_GPIO_STICKY,
					   WM97XX_GPIO_WAKE);
			wm97xx_config_gpio(wm, WM97XX_GPIO_2, WM97XX_GPIO_OUT,
					   WM97XX_GPIO_POL_HIGH,
					   WM97XX_GPIO_NOTSTICKY,
					   WM97XX_GPIO_NOWAKE);
			अवरोध;
		शेष:
			dev_err(wm->dev,
				"pen down irq not supported on this device\n");
			pen_पूर्णांक = 0;
			अवरोध;
		पूर्ण
	पूर्ण

out:
	वापस ret;
पूर्ण

अटल व्योम wm97xx_acc_shutकरोwn(काष्ठा wm97xx *wm)
अणु
	/* codec specअगरic deconfig */
	अगर (pen_पूर्णांक) अणु
		अगर (irq)
			gpio_मुक्त(irq);
		wm->pen_irq = 0;
	पूर्ण
पूर्ण

अटल व्योम wm97xx_irq_enable(काष्ठा wm97xx *wm, पूर्णांक enable)
अणु
	अगर (enable)
		enable_irq(wm->pen_irq);
	अन्यथा
		disable_irq_nosync(wm->pen_irq);
पूर्ण

अटल काष्ठा wm97xx_mach_ops मुख्यstone_mach_ops = अणु
	.acc_enabled = 1,
	.acc_pen_up = wm97xx_acc_pen_up,
	.acc_pen_करोwn = wm97xx_acc_pen_करोwn,
	.acc_startup = wm97xx_acc_startup,
	.acc_shutकरोwn = wm97xx_acc_shutकरोwn,
	.irq_enable = wm97xx_irq_enable,
	.irq_gpio = WM97XX_GPIO_2,
पूर्ण;

अटल पूर्णांक मुख्यstone_wm97xx_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा wm97xx *wm = platक्रमm_get_drvdata(pdev);

	वापस wm97xx_रेजिस्टर_mach_ops(wm, &मुख्यstone_mach_ops);
पूर्ण

अटल पूर्णांक मुख्यstone_wm97xx_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा wm97xx *wm = platक्रमm_get_drvdata(pdev);

	wm97xx_unरेजिस्टर_mach_ops(wm);
	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver मुख्यstone_wm97xx_driver = अणु
	.probe = मुख्यstone_wm97xx_probe,
	.हटाओ = मुख्यstone_wm97xx_हटाओ,
	.driver = अणु
		.name = "wm97xx-touch",
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(मुख्यstone_wm97xx_driver);

/* Module inक्रमmation */
MODULE_AUTHOR("Liam Girdwood <lrg@slimlogic.co.uk>");
MODULE_DESCRIPTION("wm97xx continuous touch driver for mainstone");
MODULE_LICENSE("GPL");
