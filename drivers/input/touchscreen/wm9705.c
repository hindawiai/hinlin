<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * wm9705.c  --  Codec driver क्रम Wolfson WM9705 AC97 Codec.
 *
 * Copyright 2003, 2004, 2005, 2006, 2007 Wolfson Microelectronics PLC.
 * Author: Liam Girdwood <lrg@slimlogic.co.uk>
 * Parts Copyright : Ian Molton <spyro@f2s.com>
 *                   Andrew Zabolotny <zap@homelink.ru>
 *                   Russell King <rmk@arm.linux.org.uk>
 */

#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/kernel.h>
#समावेश <linux/input.h>
#समावेश <linux/delay.h>
#समावेश <linux/bitops.h>
#समावेश <linux/wm97xx.h>

#घोषणा TS_NAME			"wm97xx"
#घोषणा WM9705_VERSION		"1.00"
#घोषणा DEFAULT_PRESSURE	0xb0c0

/*
 * Module parameters
 */

/*
 * Set current used क्रम pressure measurement.
 *
 * Set pil = 2 to use 400uA
 *     pil = 1 to use 200uA and
 *     pil = 0 to disable pressure measurement.
 *
 * This is used to increase the range of values वापसed by the adc
 * when measureing touchpanel pressure.
 */
अटल पूर्णांक pil;
module_param(pil, पूर्णांक, 0);
MODULE_PARM_DESC(pil, "Set current used for pressure measurement.");

/*
 * Set threshold क्रम pressure measurement.
 *
 * Pen करोwn pressure below threshold is ignored.
 */
अटल पूर्णांक pressure = DEFAULT_PRESSURE & 0xfff;
module_param(pressure, पूर्णांक, 0);
MODULE_PARM_DESC(pressure, "Set threshold for pressure measurement.");

/*
 * Set adc sample delay.
 *
 * For accurate touchpanel measurements, some settling समय may be
 * required between the चयन matrix applying a voltage across the
 * touchpanel plate and the ADC sampling the संकेत.
 *
 * This delay can be set by setting delay = n, where n is the array
 * position of the delay in the array delay_table below.
 * Long delays > 1ms are supported क्रम completeness, but are not
 * recommended.
 */
अटल पूर्णांक delay = 4;
module_param(delay, पूर्णांक, 0);
MODULE_PARM_DESC(delay, "Set adc sample delay.");

/*
 * Pen detect comparator threshold.
 *
 * 0 to Vmid in 15 steps, 0 = use zero घातer comparator with Vmid threshold
 * i.e. 1 =  Vmid/15 threshold
 *      15 =  Vmid/1 threshold
 *
 * Adjust this value अगर you are having problems with pen detect not
 * detecting any करोwn events.
 */
अटल पूर्णांक pdd = 8;
module_param(pdd, पूर्णांक, 0);
MODULE_PARM_DESC(pdd, "Set pen detect comparator threshold");

/*
 * Set adc mask function.
 *
 * Sources of glitch noise, such as संकेतs driving an LCD display, may feed
 * through to the touch screen plates and affect measurement accuracy. In
 * order to minimise this, a संकेत may be applied to the MASK pin to delay or
 * synchronise the sampling.
 *
 * 0 = No delay or sync
 * 1 = High on pin stops conversions
 * 2 = Edge triggered, edge on pin delays conversion by delay param (above)
 * 3 = Edge triggered, edge on pin starts conversion after delay param
 */
अटल पूर्णांक mask;
module_param(mask, पूर्णांक, 0);
MODULE_PARM_DESC(mask, "Set adc mask function.");

/*
 * ADC sample delay बार in uS
 */
अटल स्थिर पूर्णांक delay_table[] = अणु
	21,    /* 1 AC97 Link frames */
	42,    /* 2                  */
	84,    /* 4                  */
	167,   /* 8                  */
	333,   /* 16                 */
	667,   /* 32                 */
	1000,  /* 48                 */
	1333,  /* 64                 */
	2000,  /* 96                 */
	2667,  /* 128                */
	3333,  /* 160                */
	4000,  /* 192                */
	4667,  /* 224                */
	5333,  /* 256                */
	6000,  /* 288                */
	0      /* No delay, चयन matrix always on */
पूर्ण;

/*
 * Delay after issuing a POLL command.
 *
 * The delay is 3 AC97 link frames + the touchpanel settling delay
 */
अटल अंतरभूत व्योम poll_delay(पूर्णांक d)
अणु
	udelay(3 * AC97_LINK_FRAME + delay_table[d]);
पूर्ण

/*
 * set up the physical settings of the WM9705
 */
अटल व्योम wm9705_phy_init(काष्ठा wm97xx *wm)
अणु
	u16 dig1 = 0, dig2 = WM97XX_RPR;

	/*
	* mute VIDEO and AUX as they share X and Y touchscreen
	* inमाला_दो on the WM9705
	*/
	wm97xx_reg_ग_लिखो(wm, AC97_AUX, 0x8000);
	wm97xx_reg_ग_लिखो(wm, AC97_VIDEO, 0x8000);

	/* touchpanel pressure current*/
	अगर (pil == 2) अणु
		dig2 |= WM9705_PIL;
		dev_dbg(wm->dev,
			"setting pressure measurement current to 400uA.");
	पूर्ण अन्यथा अगर (pil)
		dev_dbg(wm->dev,
			"setting pressure measurement current to 200uA.");
	अगर (!pil)
		pressure = 0;

	/* polling mode sample settling delay */
	अगर (delay != 4) अणु
		अगर (delay < 0 || delay > 15) अणु
			dev_dbg(wm->dev, "supplied delay out of range.");
			delay = 4;
		पूर्ण
	पूर्ण
	dig1 &= 0xff0f;
	dig1 |= WM97XX_DELAY(delay);
	dev_dbg(wm->dev, "setting adc sample delay to %d u Secs.",
		delay_table[delay]);

	/* WM9705 pdd */
	dig2 |= (pdd & 0x000f);
	dev_dbg(wm->dev, "setting pdd to Vmid/%d", 1 - (pdd & 0x000f));

	/* mask */
	dig2 |= ((mask & 0x3) << 4);

	wm97xx_reg_ग_लिखो(wm, AC97_WM97XX_DIGITISER1, dig1);
	wm97xx_reg_ग_लिखो(wm, AC97_WM97XX_DIGITISER2, dig2);
पूर्ण

अटल व्योम wm9705_dig_enable(काष्ठा wm97xx *wm, पूर्णांक enable)
अणु
	अगर (enable) अणु
		wm97xx_reg_ग_लिखो(wm, AC97_WM97XX_DIGITISER2,
				 wm->dig[2] | WM97XX_PRP_DET_DIG);
		wm97xx_reg_पढ़ो(wm, AC97_WM97XX_DIGITISER_RD); /* dummy पढ़ो */
	पूर्ण अन्यथा
		wm97xx_reg_ग_लिखो(wm, AC97_WM97XX_DIGITISER2,
				 wm->dig[2] & ~WM97XX_PRP_DET_DIG);
पूर्ण

अटल व्योम wm9705_aux_prepare(काष्ठा wm97xx *wm)
अणु
	स_नकल(wm->dig_save, wm->dig, माप(wm->dig));
	wm97xx_reg_ग_लिखो(wm, AC97_WM97XX_DIGITISER1, 0);
	wm97xx_reg_ग_लिखो(wm, AC97_WM97XX_DIGITISER2, WM97XX_PRP_DET_DIG);
पूर्ण

अटल व्योम wm9705_dig_restore(काष्ठा wm97xx *wm)
अणु
	wm97xx_reg_ग_लिखो(wm, AC97_WM97XX_DIGITISER1, wm->dig_save[1]);
	wm97xx_reg_ग_लिखो(wm, AC97_WM97XX_DIGITISER2, wm->dig_save[2]);
पूर्ण

अटल अंतरभूत पूर्णांक is_pden(काष्ठा wm97xx *wm)
अणु
	वापस wm->dig[2] & WM9705_PDEN;
पूर्ण

/*
 * Read a sample from the WM9705 adc in polling mode.
 */
अटल पूर्णांक wm9705_poll_sample(काष्ठा wm97xx *wm, पूर्णांक adcsel, पूर्णांक *sample)
अणु
	पूर्णांक समयout = 5 * delay;
	bool wants_pen = adcsel & WM97XX_PEN_DOWN;

	अगर (wants_pen && !wm->pen_probably_करोwn) अणु
		u16 data = wm97xx_reg_पढ़ो(wm, AC97_WM97XX_DIGITISER_RD);
		अगर (!(data & WM97XX_PEN_DOWN))
			वापस RC_PENUP;
		wm->pen_probably_करोwn = 1;
	पूर्ण

	/* set up digitiser */
	अगर (wm->mach_ops && wm->mach_ops->pre_sample)
		wm->mach_ops->pre_sample(adcsel);
	wm97xx_reg_ग_लिखो(wm, AC97_WM97XX_DIGITISER1, (adcsel & WM97XX_ADCSEL_MASK)
				| WM97XX_POLL | WM97XX_DELAY(delay));

	/* रुको 3 AC97 समय slots + delay क्रम conversion */
	poll_delay(delay);

	/* रुको क्रम POLL to go low */
	जबतक ((wm97xx_reg_पढ़ो(wm, AC97_WM97XX_DIGITISER1) & WM97XX_POLL)
	       && समयout) अणु
		udelay(AC97_LINK_FRAME);
		समयout--;
	पूर्ण

	अगर (समयout == 0) अणु
		/* If PDEN is set, we can get a समयout when pen goes up */
		अगर (is_pden(wm))
			wm->pen_probably_करोwn = 0;
		अन्यथा
			dev_dbg(wm->dev, "adc sample timeout");
		वापस RC_PENUP;
	पूर्ण

	*sample = wm97xx_reg_पढ़ो(wm, AC97_WM97XX_DIGITISER_RD);
	अगर (wm->mach_ops && wm->mach_ops->post_sample)
		wm->mach_ops->post_sample(adcsel);

	/* check we have correct sample */
	अगर ((*sample ^ adcsel) & WM97XX_ADCSEL_MASK) अणु
		dev_dbg(wm->dev, "adc wrong sample, wanted %x got %x",
			adcsel & WM97XX_ADCSEL_MASK,
			*sample & WM97XX_ADCSEL_MASK);
		वापस RC_PENUP;
	पूर्ण

	अगर (wants_pen && !(*sample & WM97XX_PEN_DOWN)) अणु
		wm->pen_probably_करोwn = 0;
		वापस RC_PENUP;
	पूर्ण

	वापस RC_VALID;
पूर्ण

/*
 * Sample the WM9705 touchscreen in polling mode
 */
अटल पूर्णांक wm9705_poll_touch(काष्ठा wm97xx *wm, काष्ठा wm97xx_data *data)
अणु
	पूर्णांक rc;

	rc = wm9705_poll_sample(wm, WM97XX_ADCSEL_X | WM97XX_PEN_DOWN, &data->x);
	अगर (rc != RC_VALID)
		वापस rc;
	rc = wm9705_poll_sample(wm, WM97XX_ADCSEL_Y | WM97XX_PEN_DOWN, &data->y);
	अगर (rc != RC_VALID)
		वापस rc;
	अगर (pil) अणु
		rc = wm9705_poll_sample(wm, WM97XX_ADCSEL_PRES | WM97XX_PEN_DOWN, &data->p);
		अगर (rc != RC_VALID)
			वापस rc;
	पूर्ण अन्यथा
		data->p = DEFAULT_PRESSURE;

	वापस RC_VALID;
पूर्ण

/*
 * Enable WM9705 continuous mode, i.e. touch data is streamed across
 * an AC97 slot
 */
अटल पूर्णांक wm9705_acc_enable(काष्ठा wm97xx *wm, पूर्णांक enable)
अणु
	u16 dig1, dig2;
	पूर्णांक ret = 0;

	dig1 = wm->dig[1];
	dig2 = wm->dig[2];

	अगर (enable) अणु
		/* continuous mode */
		अगर (wm->mach_ops->acc_startup &&
		    (ret = wm->mach_ops->acc_startup(wm)) < 0)
			वापस ret;
		dig1 &= ~(WM97XX_CM_RATE_MASK | WM97XX_ADCSEL_MASK |
			  WM97XX_DELAY_MASK | WM97XX_SLT_MASK);
		dig1 |= WM97XX_CTC | WM97XX_COO | WM97XX_SLEN |
			WM97XX_DELAY(delay) |
			WM97XX_SLT(wm->acc_slot) |
			WM97XX_RATE(wm->acc_rate);
		अगर (pil)
			dig1 |= WM97XX_ADCSEL_PRES;
		dig2 |= WM9705_PDEN;
	पूर्ण अन्यथा अणु
		dig1 &= ~(WM97XX_CTC | WM97XX_COO | WM97XX_SLEN);
		dig2 &= ~WM9705_PDEN;
		अगर (wm->mach_ops->acc_shutकरोwn)
			wm->mach_ops->acc_shutकरोwn(wm);
	पूर्ण

	wm97xx_reg_ग_लिखो(wm, AC97_WM97XX_DIGITISER1, dig1);
	wm97xx_reg_ग_लिखो(wm, AC97_WM97XX_DIGITISER2, dig2);

	वापस ret;
पूर्ण

काष्ठा wm97xx_codec_drv wm9705_codec = अणु
	.id = WM9705_ID2,
	.name = "wm9705",
	.poll_sample = wm9705_poll_sample,
	.poll_touch = wm9705_poll_touch,
	.acc_enable = wm9705_acc_enable,
	.phy_init = wm9705_phy_init,
	.dig_enable = wm9705_dig_enable,
	.dig_restore = wm9705_dig_restore,
	.aux_prepare = wm9705_aux_prepare,
पूर्ण;
EXPORT_SYMBOL_GPL(wm9705_codec);

/* Module inक्रमmation */
MODULE_AUTHOR("Liam Girdwood <lrg@slimlogic.co.uk>");
MODULE_DESCRIPTION("WM9705 Touch Screen Driver");
MODULE_LICENSE("GPL");
