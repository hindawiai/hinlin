<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * wm9713.c  --  Codec touch driver क्रम Wolfson WM9713 AC97 Codec.
 *
 * Copyright 2003, 2004, 2005, 2006, 2007, 2008 Wolfson Microelectronics PLC.
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
#घोषणा WM9713_VERSION		"1.00"
#घोषणा DEFAULT_PRESSURE	0xb0c0

/*
 * Module parameters
 */

/*
 * Set पूर्णांकernal pull up क्रम pen detect.
 *
 * Pull up is in the range 1.02k (least sensitive) to 64k (most sensitive)
 * i.e. pull up resistance = 64k Ohms / rpu.
 *
 * Adjust this value अगर you are having problems with pen detect not
 * detecting any करोwn event.
 */
अटल पूर्णांक rpu = 8;
module_param(rpu, पूर्णांक, 0);
MODULE_PARM_DESC(rpu, "Set internal pull up resistor for pen detect.");

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
 * Set five_wire = 1 to use a 5 wire touchscreen.
 *
 * NOTE: Five wire mode करोes not allow क्रम पढ़ोback of pressure.
 */
अटल पूर्णांक five_wire;
module_param(five_wire, पूर्णांक, 0);
MODULE_PARM_DESC(five_wire, "Set to '1' to use 5-wire touchscreen.");

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
 * Coordinate Polling Enable.
 *
 * Set to 1 to enable coordinate polling. e.g. x,y[,p] is sampled together
 * क्रम every poll.
 */
अटल पूर्णांक coord;
module_param(coord, पूर्णांक, 0);
MODULE_PARM_DESC(coord, "Polling coordinate mode");

/*
 * ADC sample delay बार in uS
 */
अटल स्थिर पूर्णांक delay_table[] = अणु
	21,    /* 1 AC97 Link frames */
	42,    /* 2 */
	84,    /* 4 */
	167,   /* 8 */
	333,   /* 16 */
	667,   /* 32 */
	1000,  /* 48 */
	1333,  /* 64 */
	2000,  /* 96 */
	2667,  /* 128 */
	3333,  /* 160 */
	4000,  /* 192 */
	4667,  /* 224 */
	5333,  /* 256 */
	6000,  /* 288 */
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
 * set up the physical settings of the WM9713
 */
अटल व्योम wm9713_phy_init(काष्ठा wm97xx *wm)
अणु
	u16 dig1 = 0, dig2, dig3;

	/* शेष values */
	dig2 = WM97XX_DELAY(4) | WM97XX_SLT(5);
	dig3 = WM9712_RPU(1);

	/* rpu */
	अगर (rpu) अणु
		dig3 &= 0xffc0;
		dig3 |= WM9712_RPU(rpu);
		dev_info(wm->dev, "setting pen detect pull-up to %d Ohms\n",
			 64000 / rpu);
	पूर्ण

	/* Five wire panel? */
	अगर (five_wire) अणु
		dig3 |= WM9713_45W;
		dev_info(wm->dev, "setting 5-wire touchscreen mode.");

		अगर (pil) अणु
			dev_warn(wm->dev,
				 "Pressure measurement not supported in 5 "
				 "wire mode, disabling\n");
			pil = 0;
		पूर्ण
	पूर्ण

	/* touchpanel pressure */
	अगर (pil == 2) अणु
		dig3 |= WM9712_PIL;
		dev_info(wm->dev,
			 "setting pressure measurement current to 400uA.");
	पूर्ण अन्यथा अगर (pil)
		dev_info(wm->dev,
			 "setting pressure measurement current to 200uA.");
	अगर (!pil)
		pressure = 0;

	/* sample settling delay */
	अगर (delay < 0 || delay > 15) अणु
		dev_info(wm->dev, "supplied delay out of range.");
		delay = 4;
		dev_info(wm->dev, "setting adc sample delay to %d u Secs.",
			 delay_table[delay]);
	पूर्ण
	dig2 &= 0xff0f;
	dig2 |= WM97XX_DELAY(delay);

	/* mask */
	dig3 |= ((mask & 0x3) << 4);
	अगर (coord)
		dig3 |= WM9713_WAIT;

	wm->misc = wm97xx_reg_पढ़ो(wm, 0x5a);

	wm97xx_reg_ग_लिखो(wm, AC97_WM9713_DIG1, dig1);
	wm97xx_reg_ग_लिखो(wm, AC97_WM9713_DIG2, dig2);
	wm97xx_reg_ग_लिखो(wm, AC97_WM9713_DIG3, dig3);
	wm97xx_reg_ग_लिखो(wm, AC97_GPIO_STICKY, 0x0);
पूर्ण

अटल व्योम wm9713_dig_enable(काष्ठा wm97xx *wm, पूर्णांक enable)
अणु
	u16 val;

	अगर (enable) अणु
		val = wm97xx_reg_पढ़ो(wm, AC97_EXTENDED_MID);
		wm97xx_reg_ग_लिखो(wm, AC97_EXTENDED_MID, val & 0x7fff);
		wm97xx_reg_ग_लिखो(wm, AC97_WM9713_DIG3, wm->dig[2] |
				 WM97XX_PRP_DET_DIG);
		wm97xx_reg_पढ़ो(wm, AC97_WM97XX_DIGITISER_RD); /* dummy पढ़ो */
	पूर्ण अन्यथा अणु
		wm97xx_reg_ग_लिखो(wm, AC97_WM9713_DIG3, wm->dig[2] &
					~WM97XX_PRP_DET_DIG);
		val = wm97xx_reg_पढ़ो(wm, AC97_EXTENDED_MID);
		wm97xx_reg_ग_लिखो(wm, AC97_EXTENDED_MID, val | 0x8000);
	पूर्ण
पूर्ण

अटल व्योम wm9713_dig_restore(काष्ठा wm97xx *wm)
अणु
	wm97xx_reg_ग_लिखो(wm, AC97_WM9713_DIG1, wm->dig_save[0]);
	wm97xx_reg_ग_लिखो(wm, AC97_WM9713_DIG2, wm->dig_save[1]);
	wm97xx_reg_ग_लिखो(wm, AC97_WM9713_DIG3, wm->dig_save[2]);
पूर्ण

अटल व्योम wm9713_aux_prepare(काष्ठा wm97xx *wm)
अणु
	स_नकल(wm->dig_save, wm->dig, माप(wm->dig));
	wm97xx_reg_ग_लिखो(wm, AC97_WM9713_DIG1, 0);
	wm97xx_reg_ग_लिखो(wm, AC97_WM9713_DIG2, 0);
	wm97xx_reg_ग_लिखो(wm, AC97_WM9713_DIG3, WM97XX_PRP_DET_DIG);
पूर्ण

अटल अंतरभूत पूर्णांक is_pden(काष्ठा wm97xx *wm)
अणु
	वापस wm->dig[2] & WM9713_PDEN;
पूर्ण

/*
 * Read a sample from the WM9713 adc in polling mode.
 */
अटल पूर्णांक wm9713_poll_sample(काष्ठा wm97xx *wm, पूर्णांक adcsel, पूर्णांक *sample)
अणु
	u16 dig1;
	पूर्णांक समयout = 5 * delay;
	bool wants_pen = adcsel & WM97XX_PEN_DOWN;

	अगर (wants_pen && !wm->pen_probably_करोwn) अणु
		u16 data = wm97xx_reg_पढ़ो(wm, AC97_WM97XX_DIGITISER_RD);
		अगर (!(data & WM97XX_PEN_DOWN))
			वापस RC_PENUP;
		wm->pen_probably_करोwn = 1;
	पूर्ण

	/* set up digitiser */
	dig1 = wm97xx_reg_पढ़ो(wm, AC97_WM9713_DIG1);
	dig1 &= ~WM9713_ADCSEL_MASK;
	/* WM97XX_ADCSEL_* channels need to be converted to WM9713 क्रमmat */
	dig1 |= 1 << ((adcsel & WM97XX_ADCSEL_MASK) >> 12);

	अगर (wm->mach_ops && wm->mach_ops->pre_sample)
		wm->mach_ops->pre_sample(adcsel);
	wm97xx_reg_ग_लिखो(wm, AC97_WM9713_DIG1, dig1 | WM9713_POLL);

	/* रुको 3 AC97 समय slots + delay क्रम conversion */
	poll_delay(delay);

	/* रुको क्रम POLL to go low */
	जबतक ((wm97xx_reg_पढ़ो(wm, AC97_WM9713_DIG1) & WM9713_POLL) &&
		समयout) अणु
		udelay(AC97_LINK_FRAME);
		समयout--;
	पूर्ण

	अगर (समयout <= 0) अणु
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
 * Read a coordinate from the WM9713 adc in polling mode.
 */
अटल पूर्णांक wm9713_poll_coord(काष्ठा wm97xx *wm, काष्ठा wm97xx_data *data)
अणु
	u16 dig1;
	पूर्णांक समयout = 5 * delay;

	अगर (!wm->pen_probably_करोwn) अणु
		u16 val = wm97xx_reg_पढ़ो(wm, AC97_WM97XX_DIGITISER_RD);
		अगर (!(val & WM97XX_PEN_DOWN))
			वापस RC_PENUP;
		wm->pen_probably_करोwn = 1;
	पूर्ण

	/* set up digitiser */
	dig1 = wm97xx_reg_पढ़ो(wm, AC97_WM9713_DIG1);
	dig1 &= ~WM9713_ADCSEL_MASK;
	अगर (pil)
		dig1 |= WM9713_ADCSEL_PRES;

	अगर (wm->mach_ops && wm->mach_ops->pre_sample)
		wm->mach_ops->pre_sample(WM97XX_ADCSEL_X | WM97XX_ADCSEL_Y);
	wm97xx_reg_ग_लिखो(wm, AC97_WM9713_DIG1,
			 dig1 | WM9713_POLL | WM9713_COO);

	/* रुको 3 AC97 समय slots + delay क्रम conversion */
	poll_delay(delay);
	data->x = wm97xx_reg_पढ़ो(wm, AC97_WM97XX_DIGITISER_RD);
	/* रुको क्रम POLL to go low */
	जबतक ((wm97xx_reg_पढ़ो(wm, AC97_WM9713_DIG1) & WM9713_POLL)
	       && समयout) अणु
		udelay(AC97_LINK_FRAME);
		समयout--;
	पूर्ण

	अगर (समयout <= 0) अणु
		/* If PDEN is set, we can get a समयout when pen goes up */
		अगर (is_pden(wm))
			wm->pen_probably_करोwn = 0;
		अन्यथा
			dev_dbg(wm->dev, "adc sample timeout");
		वापस RC_PENUP;
	पूर्ण

	/* पढ़ो back data */
	data->y = wm97xx_reg_पढ़ो(wm, AC97_WM97XX_DIGITISER_RD);
	अगर (pil)
		data->p = wm97xx_reg_पढ़ो(wm, AC97_WM97XX_DIGITISER_RD);
	अन्यथा
		data->p = DEFAULT_PRESSURE;

	अगर (wm->mach_ops && wm->mach_ops->post_sample)
		wm->mach_ops->post_sample(WM97XX_ADCSEL_X | WM97XX_ADCSEL_Y);

	/* check we have correct sample */
	अगर (!(data->x & WM97XX_ADCSEL_X) || !(data->y & WM97XX_ADCSEL_Y))
		जाओ err;
	अगर (pil && !(data->p & WM97XX_ADCSEL_PRES))
		जाओ err;

	अगर (!(data->x & WM97XX_PEN_DOWN) || !(data->y & WM97XX_PEN_DOWN)) अणु
		wm->pen_probably_करोwn = 0;
		वापस RC_PENUP;
	पूर्ण
	वापस RC_VALID;
err:
	वापस 0;
पूर्ण

/*
 * Sample the WM9713 touchscreen in polling mode
 */
अटल पूर्णांक wm9713_poll_touch(काष्ठा wm97xx *wm, काष्ठा wm97xx_data *data)
अणु
	पूर्णांक rc;

	अगर (coord) अणु
		rc = wm9713_poll_coord(wm, data);
		अगर (rc != RC_VALID)
			वापस rc;
	पूर्ण अन्यथा अणु
		rc = wm9713_poll_sample(wm, WM97XX_ADCSEL_X | WM97XX_PEN_DOWN, &data->x);
		अगर (rc != RC_VALID)
			वापस rc;
		rc = wm9713_poll_sample(wm, WM97XX_ADCSEL_Y | WM97XX_PEN_DOWN, &data->y);
		अगर (rc != RC_VALID)
			वापस rc;
		अगर (pil) अणु
			rc = wm9713_poll_sample(wm, WM97XX_ADCSEL_PRES | WM97XX_PEN_DOWN,
						&data->p);
			अगर (rc != RC_VALID)
				वापस rc;
		पूर्ण अन्यथा
			data->p = DEFAULT_PRESSURE;
	पूर्ण
	वापस RC_VALID;
पूर्ण

/*
 * Enable WM9713 continuous mode, i.e. touch data is streamed across
 * an AC97 slot
 */
अटल पूर्णांक wm9713_acc_enable(काष्ठा wm97xx *wm, पूर्णांक enable)
अणु
	u16 dig1, dig2, dig3;
	पूर्णांक ret = 0;

	dig1 = wm->dig[0];
	dig2 = wm->dig[1];
	dig3 = wm->dig[2];

	अगर (enable) अणु
		/* continuous mode */
		अगर (wm->mach_ops->acc_startup &&
			(ret = wm->mach_ops->acc_startup(wm)) < 0)
			वापस ret;

		dig1 &= ~WM9713_ADCSEL_MASK;
		dig1 |= WM9713_CTC | WM9713_COO | WM9713_ADCSEL_X |
			WM9713_ADCSEL_Y;
		अगर (pil)
			dig1 |= WM9713_ADCSEL_PRES;
		dig2 &= ~(WM97XX_DELAY_MASK | WM97XX_SLT_MASK  |
			WM97XX_CM_RATE_MASK);
		dig2 |= WM97XX_SLEN | WM97XX_DELAY(delay) |
		WM97XX_SLT(wm->acc_slot) | WM97XX_RATE(wm->acc_rate);
		dig3 |= WM9713_PDEN;
	पूर्ण अन्यथा अणु
		dig1 &= ~(WM9713_CTC | WM9713_COO);
		dig2 &= ~WM97XX_SLEN;
		dig3 &= ~WM9713_PDEN;
		अगर (wm->mach_ops->acc_shutकरोwn)
			wm->mach_ops->acc_shutकरोwn(wm);
	पूर्ण

	wm97xx_reg_ग_लिखो(wm, AC97_WM9713_DIG1, dig1);
	wm97xx_reg_ग_लिखो(wm, AC97_WM9713_DIG2, dig2);
	wm97xx_reg_ग_लिखो(wm, AC97_WM9713_DIG3, dig3);

	वापस ret;
पूर्ण

काष्ठा wm97xx_codec_drv wm9713_codec = अणु
	.id = WM9713_ID2,
	.name = "wm9713",
	.poll_sample = wm9713_poll_sample,
	.poll_touch = wm9713_poll_touch,
	.acc_enable = wm9713_acc_enable,
	.phy_init = wm9713_phy_init,
	.dig_enable = wm9713_dig_enable,
	.dig_restore = wm9713_dig_restore,
	.aux_prepare = wm9713_aux_prepare,
पूर्ण;
EXPORT_SYMBOL_GPL(wm9713_codec);

/* Module inक्रमmation */
MODULE_AUTHOR("Liam Girdwood <lrg@slimlogic.co.uk>");
MODULE_DESCRIPTION("WM9713 Touch Screen Driver");
MODULE_LICENSE("GPL");
