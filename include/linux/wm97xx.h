<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */

/*
 * Register bits and API क्रम Wolfson WM97xx series of codecs
 */

#अगर_अघोषित _LINUX_WM97XX_H
#घोषणा _LINUX_WM97XX_H

#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश <sound/ac97_codec.h>
#समावेश <sound/initval.h>
#समावेश <linux/types.h>
#समावेश <linux/list.h>
#समावेश <linux/input.h>	/* Input device layer */
#समावेश <linux/platक्रमm_device.h>

/*
 * WM97xx variants
 */
#घोषणा	WM97xx_GENERIC			0x0000
#घोषणा	WM97xx_WM1613			0x1613

/*
 * WM97xx AC97 Touchscreen रेजिस्टरs
 */
#घोषणा AC97_WM97XX_DIGITISER1		0x76
#घोषणा AC97_WM97XX_DIGITISER2		0x78
#घोषणा AC97_WM97XX_DIGITISER_RD 	0x7a
#घोषणा AC97_WM9713_DIG1		0x74
#घोषणा AC97_WM9713_DIG2		AC97_WM97XX_DIGITISER1
#घोषणा AC97_WM9713_DIG3		AC97_WM97XX_DIGITISER2

/*
 * WM97xx रेजिस्टर bits
 */
#घोषणा WM97XX_POLL		0x8000	/* initiate a polling measurement */
#घोषणा WM97XX_ADCSEL_X		0x1000	/* x coord measurement */
#घोषणा WM97XX_ADCSEL_Y		0x2000	/* y coord measurement */
#घोषणा WM97XX_ADCSEL_PRES	0x3000	/* pressure measurement */
#घोषणा WM97XX_AUX_ID1		0x4000
#घोषणा WM97XX_AUX_ID2		0x5000
#घोषणा WM97XX_AUX_ID3		0x6000
#घोषणा WM97XX_AUX_ID4		0x7000
#घोषणा WM97XX_ADCSEL_MASK	0x7000	/* ADC selection mask */
#घोषणा WM97XX_COO		0x0800	/* enable coordinate mode */
#घोषणा WM97XX_CTC		0x0400	/* enable continuous mode */
#घोषणा WM97XX_CM_RATE_93	0x0000	/* 93.75Hz continuous rate */
#घोषणा WM97XX_CM_RATE_187	0x0100	/* 187.5Hz continuous rate */
#घोषणा WM97XX_CM_RATE_375	0x0200	/* 375Hz continuous rate */
#घोषणा WM97XX_CM_RATE_750	0x0300	/* 750Hz continuous rate */
#घोषणा WM97XX_CM_RATE_8K	0x00f0	/* 8kHz continuous rate */
#घोषणा WM97XX_CM_RATE_12K	0x01f0	/* 12kHz continuous rate */
#घोषणा WM97XX_CM_RATE_24K	0x02f0	/* 24kHz continuous rate */
#घोषणा WM97XX_CM_RATE_48K	0x03f0	/* 48kHz continuous rate */
#घोषणा WM97XX_CM_RATE_MASK	0x03f0
#घोषणा WM97XX_RATE(i)		(((i & 3) << 8) | ((i & 4) ? 0xf0 : 0))
#घोषणा WM97XX_DELAY(i)		((i << 4) & 0x00f0)	/* sample delay बार */
#घोषणा WM97XX_DELAY_MASK	0x00f0
#घोषणा WM97XX_SLEN		0x0008	/* slot पढ़ो back enable */
#घोषणा WM97XX_SLT(i)		((i - 5) & 0x7)	/* panel slot (5-11) */
#घोषणा WM97XX_SLT_MASK		0x0007
#घोषणा WM97XX_PRP_DETW		0x4000	/* detect on, digitise off, wake */
#घोषणा WM97XX_PRP_DET		0x8000	/* detect on, digitise off, no wake */
#घोषणा WM97XX_PRP_DET_DIG	0xc000	/* setect on, digitise on */
#घोषणा WM97XX_RPR		0x2000	/* wake up on pen करोwn */
#घोषणा WM97XX_PEN_DOWN		0x8000	/* pen is करोwn */

/* WM9712 Bits */
#घोषणा WM9712_45W		0x1000	/* set क्रम 5-wire touchscreen */
#घोषणा WM9712_PDEN		0x0800	/* measure only when pen करोwn */
#घोषणा WM9712_WAIT		0x0200	/* रुको until adc is पढ़ो beक्रमe next sample */
#घोषणा WM9712_PIL		0x0100	/* current used क्रम pressure measurement. set 400uA अन्यथा 200uA */
#घोषणा WM9712_MASK_HI		0x0040	/* hi on mask pin (47) stops conversions */
#घोषणा WM9712_MASK_EDGE	0x0080	/* rising/falling edge on pin delays sample */
#घोषणा	WM9712_MASK_SYNC	0x00c0	/* rising/falling edge on mask initiates sample */
#घोषणा WM9712_RPU(i)		(i&0x3f)	/* पूर्णांकernal pull up on pen detect (64k / rpu) */
#घोषणा WM9712_PD(i)		(0x1 << i)	/* घातer management */

/* WM9712 Registers */
#घोषणा AC97_WM9712_POWER	0x24
#घोषणा AC97_WM9712_REV		0x58

/* WM9705 Bits */
#घोषणा WM9705_PDEN		0x1000	/* measure only when pen is करोwn */
#घोषणा WM9705_PINV		0x0800	/* inverts sense of pen करोwn output */
#घोषणा WM9705_BSEN		0x0400	/* BUSY flag enable, pin47 is 1 when busy */
#घोषणा WM9705_BINV		0x0200	/* invert BUSY (pin47) output */
#घोषणा WM9705_WAIT		0x0100	/* रुको until adc is पढ़ो beक्रमe next sample */
#घोषणा WM9705_PIL		0x0080	/* current used क्रम pressure measurement. set 400uA अन्यथा 200uA */
#घोषणा WM9705_PHIZ		0x0040	/* set PHONE and PCBEEP inमाला_दो to high impedance */
#घोषणा WM9705_MASK_HI		0x0010	/* hi on mask stops conversions */
#घोषणा WM9705_MASK_EDGE	0x0020	/* rising/falling edge on pin delays sample */
#घोषणा	WM9705_MASK_SYNC	0x0030	/* rising/falling edge on mask initiates sample */
#घोषणा WM9705_PDD(i)		(i & 0x000f)	/* pen detect comparator threshold */


/* WM9713 Bits */
#घोषणा WM9713_PDPOL		0x0400	/* Pen करोwn polarity */
#घोषणा WM9713_POLL		0x0200	/* initiate a polling measurement */
#घोषणा WM9713_CTC		0x0100	/* enable continuous mode */
#घोषणा WM9713_ADCSEL_X		0x0002	/* X measurement */
#घोषणा WM9713_ADCSEL_Y		0x0004	/* Y measurement */
#घोषणा WM9713_ADCSEL_PRES	0x0008	/* Pressure measurement */
#घोषणा WM9713_COO		0x0001	/* enable coordinate mode */
#घोषणा WM9713_45W		0x1000  /* set क्रम 5 wire panel */
#घोषणा WM9713_PDEN		0x0800	/* measure only when pen करोwn */
#घोषणा WM9713_ADCSEL_MASK	0x00fe	/* ADC selection mask */
#घोषणा WM9713_WAIT		0x0200	/* coordinate रुको */

/* AUX ADC ID's */
#घोषणा TS_COMP1		0x0
#घोषणा TS_COMP2		0x1
#घोषणा TS_BMON			0x2
#घोषणा TS_WIPER		0x3

/* ID numbers */
#घोषणा WM97XX_ID1		0x574d
#घोषणा WM9712_ID2		0x4c12
#घोषणा WM9705_ID2		0x4c05
#घोषणा WM9713_ID2		0x4c13

/* Codec GPIO's */
#घोषणा WM97XX_MAX_GPIO		16
#घोषणा WM97XX_GPIO_1		(1 << 1)
#घोषणा WM97XX_GPIO_2		(1 << 2)
#घोषणा WM97XX_GPIO_3		(1 << 3)
#घोषणा WM97XX_GPIO_4		(1 << 4)
#घोषणा WM97XX_GPIO_5		(1 << 5)
#घोषणा WM97XX_GPIO_6		(1 << 6)
#घोषणा WM97XX_GPIO_7		(1 << 7)
#घोषणा WM97XX_GPIO_8		(1 << 8)
#घोषणा WM97XX_GPIO_9		(1 << 9)
#घोषणा WM97XX_GPIO_10		(1 << 10)
#घोषणा WM97XX_GPIO_11		(1 << 11)
#घोषणा WM97XX_GPIO_12		(1 << 12)
#घोषणा WM97XX_GPIO_13		(1 << 13)
#घोषणा WM97XX_GPIO_14		(1 << 14)
#घोषणा WM97XX_GPIO_15		(1 << 15)


#घोषणा AC97_LINK_FRAME		21	/* समय in uS क्रम AC97 link frame */


/*---------------- Return codes from sample पढ़ोing functions ---------------*/

/* More data is available; call the sample gathering function again */
#घोषणा RC_AGAIN			0x00000001
/* The वापसed sample is valid */
#घोषणा RC_VALID			0x00000002
/* The pen is up (the first RC_VALID without RC_PENUP means pen is करोwn) */
#घोषणा RC_PENUP			0x00000004
/* The pen is करोwn (RC_VALID implies RC_PENDOWN, but someबार it is helpful
   to tell the handler that the pen is करोwn but we करोn't know yet his coords,
   so the handler should not sleep or रुको क्रम penकरोwn irq) */
#घोषणा RC_PENDOWN			0x00000008

/*
 * The wm97xx driver provides a निजी API क्रम writing platक्रमm-specअगरic
 * drivers.
 */

/* The काष्ठाure used to वापस arch specअगरic sampled data पूर्णांकo */
काष्ठा wm97xx_data अणु
    पूर्णांक x;
    पूर्णांक y;
    पूर्णांक p;
पूर्ण;

/*
 * Codec GPIO status
 */
क्रमागत wm97xx_gpio_status अणु
    WM97XX_GPIO_HIGH,
    WM97XX_GPIO_LOW
पूर्ण;

/*
 * Codec GPIO direction
 */
क्रमागत wm97xx_gpio_dir अणु
    WM97XX_GPIO_IN,
    WM97XX_GPIO_OUT
पूर्ण;

/*
 * Codec GPIO polarity
 */
क्रमागत wm97xx_gpio_pol अणु
    WM97XX_GPIO_POL_HIGH,
    WM97XX_GPIO_POL_LOW
पूर्ण;

/*
 * Codec GPIO sticky
 */
क्रमागत wm97xx_gpio_sticky अणु
    WM97XX_GPIO_STICKY,
    WM97XX_GPIO_NOTSTICKY
पूर्ण;

/*
 * Codec GPIO wake
 */
क्रमागत wm97xx_gpio_wake अणु
    WM97XX_GPIO_WAKE,
    WM97XX_GPIO_NOWAKE
पूर्ण;

/*
 * Digitiser ioctl commands
 */
#घोषणा WM97XX_DIG_START	0x1
#घोषणा WM97XX_DIG_STOP		0x2
#घोषणा WM97XX_PHY_INIT		0x3
#घोषणा WM97XX_AUX_PREPARE	0x4
#घोषणा WM97XX_DIG_RESTORE	0x5

काष्ठा wm97xx;

बाह्य काष्ठा wm97xx_codec_drv wm9705_codec;
बाह्य काष्ठा wm97xx_codec_drv wm9712_codec;
बाह्य काष्ठा wm97xx_codec_drv wm9713_codec;

/*
 * Codec driver पूर्णांकerface - allows mapping to WM9705/12/13 and newer codecs
 */
काष्ठा wm97xx_codec_drv अणु
	u16 id;
	अक्षर *name;

	/* पढ़ो 1 sample */
	पूर्णांक (*poll_sample) (काष्ठा wm97xx *, पूर्णांक adcsel, पूर्णांक *sample);

	/* पढ़ो X,Y,[P] in poll */
	पूर्णांक (*poll_touch) (काष्ठा wm97xx *, काष्ठा wm97xx_data *);

	पूर्णांक (*acc_enable) (काष्ठा wm97xx *, पूर्णांक enable);
	व्योम (*phy_init) (काष्ठा wm97xx *);
	व्योम (*dig_enable) (काष्ठा wm97xx *, पूर्णांक enable);
	व्योम (*dig_restore) (काष्ठा wm97xx *);
	व्योम (*aux_prepare) (काष्ठा wm97xx *);
पूर्ण;


/* Machine specअगरic and accelerated touch operations */
काष्ठा wm97xx_mach_ops अणु

	/* accelerated touch पढ़ोback - coords are transmited on AC97 link */
	पूर्णांक acc_enabled;
	व्योम (*acc_pen_up) (काष्ठा wm97xx *);
	पूर्णांक (*acc_pen_करोwn) (काष्ठा wm97xx *);
	पूर्णांक (*acc_startup) (काष्ठा wm97xx *);
	व्योम (*acc_shutकरोwn) (काष्ठा wm97xx *);

	/* पूर्णांकerrupt mask control - required क्रम accelerated operation */
	व्योम (*irq_enable) (काष्ठा wm97xx *, पूर्णांक enable);

	/* GPIO pin used क्रम accelerated operation */
	पूर्णांक irq_gpio;

	/* pre and post sample - can be used to minimise any analog noise */
	व्योम (*pre_sample) (पूर्णांक);  /* function to run beक्रमe sampling */
	व्योम (*post_sample) (पूर्णांक);  /* function to run after sampling */
पूर्ण;

काष्ठा wm97xx अणु
	u16 dig[3], id, gpio[6], misc;	/* Cached codec रेजिस्टरs */
	u16 dig_save[3];		/* saved during aux पढ़ोing */
	काष्ठा wm97xx_codec_drv *codec;	/* attached codec driver*/
	काष्ठा input_dev *input_dev;	/* touchscreen input device */
	काष्ठा snd_ac97 *ac97;		/* ALSA codec access */
	काष्ठा device *dev;		/* ALSA device */
	काष्ठा platक्रमm_device *battery_dev;
	काष्ठा platक्रमm_device *touch_dev;
	काष्ठा wm97xx_mach_ops *mach_ops;
	काष्ठा mutex codec_mutex;
	काष्ठा delayed_work ts_पढ़ोer;  /* Used to poll touchscreen */
	अचिन्हित दीर्घ ts_पढ़ोer_पूर्णांकerval; /* Current पूर्णांकerval क्रम समयr */
	अचिन्हित दीर्घ ts_पढ़ोer_min_पूर्णांकerval; /* Minimum पूर्णांकerval */
	अचिन्हित पूर्णांक pen_irq;		/* Pen IRQ number in use */
	काष्ठा workqueue_काष्ठा *ts_workq;
	काष्ठा work_काष्ठा pen_event_work;
	u16 acc_slot;			/* AC97 slot used क्रम acc touch data */
	u16 acc_rate;			/* acc touch data rate */
	अचिन्हित pen_is_करोwn:1;		/* Pen is करोwn */
	अचिन्हित aux_रुकोing:1;		/* aux measurement रुकोing */
	अचिन्हित pen_probably_करोwn:1;	/* used in polling mode */
	u16 variant;			/* WM97xx chip variant */
	u16 suspend_mode;               /* PRP in suspend mode */
पूर्ण;

काष्ठा wm97xx_batt_pdata अणु
	पूर्णांक	batt_aux;
	पूर्णांक	temp_aux;
	पूर्णांक	min_voltage;
	पूर्णांक	max_voltage;
	पूर्णांक	batt_भाग;
	पूर्णांक	batt_mult;
	पूर्णांक	temp_भाग;
	पूर्णांक	temp_mult;
	पूर्णांक	batt_tech;
	अक्षर	*batt_name;
पूर्ण;

काष्ठा wm97xx_pdata अणु
	काष्ठा wm97xx_batt_pdata	*batt_pdata;	/* battery data */
पूर्ण;

/*
 * Codec GPIO access (not supported on WM9705)
 * This can be used to set/get codec GPIO and Virtual GPIO status.
 */
क्रमागत wm97xx_gpio_status wm97xx_get_gpio(काष्ठा wm97xx *wm, u32 gpio);
व्योम wm97xx_set_gpio(काष्ठा wm97xx *wm, u32 gpio,
			  क्रमागत wm97xx_gpio_status status);
व्योम wm97xx_config_gpio(काष्ठा wm97xx *wm, u32 gpio,
				     क्रमागत wm97xx_gpio_dir dir,
				     क्रमागत wm97xx_gpio_pol pol,
				     क्रमागत wm97xx_gpio_sticky sticky,
				     क्रमागत wm97xx_gpio_wake wake);

व्योम wm97xx_set_suspend_mode(काष्ठा wm97xx *wm, u16 mode);

/* codec AC97 IO access */
पूर्णांक wm97xx_reg_पढ़ो(काष्ठा wm97xx *wm, u16 reg);
व्योम wm97xx_reg_ग_लिखो(काष्ठा wm97xx *wm, u16 reg, u16 val);

/* aux adc पढ़ोback */
पूर्णांक wm97xx_पढ़ो_aux_adc(काष्ठा wm97xx *wm, u16 adcsel);

/* machine ops */
पूर्णांक wm97xx_रेजिस्टर_mach_ops(काष्ठा wm97xx *, काष्ठा wm97xx_mach_ops *);
व्योम wm97xx_unरेजिस्टर_mach_ops(काष्ठा wm97xx *);

#पूर्ण_अगर
