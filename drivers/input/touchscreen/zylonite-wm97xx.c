<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * zylonite-wm97xx.c  --  Zylonite Continuous Touch screen driver
 *
 * Copyright 2004, 2007, 2008 Wolfson Microelectronics PLC.
 * Author: Mark Brown <broonie@खोलोsource.wolfsonmicro.com>
 * Parts Copyright : Ian Molton <spyro@f2s.com>
 *                   Andrew Zabolotny <zap@homelink.ru>
 *
 * Notes:
 *     This is a wm97xx extended touch driver supporting पूर्णांकerrupt driven
 *     and continuous operation on Marvell Zylonite development प्रणालीs
 *     (which have a WM9713 on board).
 */

#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/kernel.h>
#समावेश <linux/delay.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/irq.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/wm97xx.h>

#समावेश <mach/hardware.h>
#समावेश <mach/mfp.h>
#समावेश <mach/regs-ac97.h>

काष्ठा continuous अणु
	u16 id;    /* codec id */
	u8 code;   /* continuous code */
	u8 पढ़ोs;  /* number of coord पढ़ोs per पढ़ो cycle */
	u32 speed; /* number of coords per second */
पूर्ण;

#घोषणा WM_READS(sp) ((sp / HZ) + 1)

अटल स्थिर काष्ठा continuous cinfo[] = अणु
	अणु WM9713_ID2, 0, WM_READS(94),  94  पूर्ण,
	अणु WM9713_ID2, 1, WM_READS(120), 120 पूर्ण,
	अणु WM9713_ID2, 2, WM_READS(154), 154 पूर्ण,
	अणु WM9713_ID2, 3, WM_READS(188), 188 पूर्ण,
पूर्ण;

/* continuous speed index */
अटल पूर्णांक sp_idx;

/*
 * Pen sampling frequency (Hz) in continuous mode.
 */
अटल पूर्णांक cont_rate = 200;
module_param(cont_rate, पूर्णांक, 0);
MODULE_PARM_DESC(cont_rate, "Sampling rate in continuous mode (Hz)");

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


/* flush AC97 slot 5 FIFO machines */
अटल व्योम wm97xx_acc_pen_up(काष्ठा wm97xx *wm)
अणु
	पूर्णांक i;

	msleep(1);

	क्रम (i = 0; i < 16; i++)
		MODR;
पूर्ण

अटल पूर्णांक wm97xx_acc_pen_करोwn(काष्ठा wm97xx *wm)
अणु
	u16 x, y, p = 0x100 | WM97XX_ADCSEL_PRES;
	पूर्णांक पढ़ोs = 0;
	अटल u16 last, tries;

	/* When the AC97 queue has been drained we need to allow समय
	 * to buffer up samples otherwise we end up spinning polling
	 * क्रम samples.  The controller can't have a suitably low
	 * threshold set to use the notअगरications it gives.
	 */
	msleep(1);

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
	पूर्णांक idx;

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
		 "zylonite accelerated touchscreen driver, %d samples/sec\n",
		 cinfo[sp_idx].speed);

	वापस 0;
पूर्ण

अटल व्योम wm97xx_irq_enable(काष्ठा wm97xx *wm, पूर्णांक enable)
अणु
	अगर (enable)
		enable_irq(wm->pen_irq);
	अन्यथा
		disable_irq_nosync(wm->pen_irq);
पूर्ण

अटल काष्ठा wm97xx_mach_ops zylonite_mach_ops = अणु
	.acc_enabled	= 1,
	.acc_pen_up	= wm97xx_acc_pen_up,
	.acc_pen_करोwn	= wm97xx_acc_pen_करोwn,
	.acc_startup	= wm97xx_acc_startup,
	.irq_enable	= wm97xx_irq_enable,
	.irq_gpio	= WM97XX_GPIO_2,
पूर्ण;

अटल पूर्णांक zylonite_wm97xx_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा wm97xx *wm = platक्रमm_get_drvdata(pdev);
	पूर्णांक gpio_touch_irq;

	अगर (cpu_is_pxa320())
		gpio_touch_irq = mfp_to_gpio(MFP_PIN_GPIO15);
	अन्यथा
		gpio_touch_irq = mfp_to_gpio(MFP_PIN_GPIO26);

	wm->pen_irq = gpio_to_irq(gpio_touch_irq);
	irq_set_irq_type(wm->pen_irq, IRQ_TYPE_EDGE_BOTH);

	wm97xx_config_gpio(wm, WM97XX_GPIO_13, WM97XX_GPIO_IN,
			   WM97XX_GPIO_POL_HIGH,
			   WM97XX_GPIO_STICKY,
			   WM97XX_GPIO_WAKE);
	wm97xx_config_gpio(wm, WM97XX_GPIO_2, WM97XX_GPIO_OUT,
			   WM97XX_GPIO_POL_HIGH,
			   WM97XX_GPIO_NOTSTICKY,
			   WM97XX_GPIO_NOWAKE);

	वापस wm97xx_रेजिस्टर_mach_ops(wm, &zylonite_mach_ops);
पूर्ण

अटल पूर्णांक zylonite_wm97xx_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा wm97xx *wm = platक्रमm_get_drvdata(pdev);

	wm97xx_unरेजिस्टर_mach_ops(wm);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver zylonite_wm97xx_driver = अणु
	.probe	= zylonite_wm97xx_probe,
	.हटाओ	= zylonite_wm97xx_हटाओ,
	.driver	= अणु
		.name	= "wm97xx-touch",
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(zylonite_wm97xx_driver);

/* Module inक्रमmation */
MODULE_AUTHOR("Mark Brown <broonie@opensource.wolfsonmicro.com>");
MODULE_DESCRIPTION("wm97xx continuous touch driver for Zylonite");
MODULE_LICENSE("GPL");
