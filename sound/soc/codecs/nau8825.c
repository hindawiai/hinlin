<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Nuvoton NAU8825 audio codec driver
 *
 * Copyright 2015 Google Chromium project.
 *  Author: Anम_से_द Pomozov <anम_से_द@chromium.org>
 * Copyright 2015 Nuvoton Technology Corp.
 *  Co-author: Meng-Huang Kuo <mhkuo@nuvoton.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/delay.h>
#समावेश <linux/init.h>
#समावेश <linux/i2c.h>
#समावेश <linux/regmap.h>
#समावेश <linux/slab.h>
#समावेश <linux/clk.h>
#समावेश <linux/acpi.h>
#समावेश <linux/math64.h>
#समावेश <linux/semaphore.h>

#समावेश <sound/initval.h>
#समावेश <sound/tlv.h>
#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/soc.h>
#समावेश <sound/jack.h>


#समावेश "nau8825.h"


#घोषणा NUVOTON_CODEC_DAI "nau8825-hifi"

#घोषणा NAU_FREF_MAX 13500000
#घोषणा NAU_FVCO_MAX 124000000
#घोषणा NAU_FVCO_MIN 90000000

/* cross talk suppression detection */
#घोषणा LOG10_MAGIC 646456993
#घोषणा GAIN_AUGMENT 22500
#घोषणा SIDETONE_BASE 207000

/* the maximum frequency of CLK_ADC and CLK_DAC */
#घोषणा CLK_DA_AD_MAX 6144000

अटल पूर्णांक nau8825_configure_sysclk(काष्ठा nau8825 *nau8825,
		पूर्णांक clk_id, अचिन्हित पूर्णांक freq);

काष्ठा nau8825_fll अणु
	पूर्णांक mclk_src;
	पूर्णांक ratio;
	पूर्णांक fll_frac;
	पूर्णांक fll_पूर्णांक;
	पूर्णांक clk_ref_भाग;
पूर्ण;

काष्ठा nau8825_fll_attr अणु
	अचिन्हित पूर्णांक param;
	अचिन्हित पूर्णांक val;
पूर्ण;

/* scaling क्रम mclk from sysclk_src output */
अटल स्थिर काष्ठा nau8825_fll_attr mclk_src_scaling[] = अणु
	अणु 1, 0x0 पूर्ण,
	अणु 2, 0x2 पूर्ण,
	अणु 4, 0x3 पूर्ण,
	अणु 8, 0x4 पूर्ण,
	अणु 16, 0x5 पूर्ण,
	अणु 32, 0x6 पूर्ण,
	अणु 3, 0x7 पूर्ण,
	अणु 6, 0xa पूर्ण,
	अणु 12, 0xb पूर्ण,
	अणु 24, 0xc पूर्ण,
	अणु 48, 0xd पूर्ण,
	अणु 96, 0xe पूर्ण,
	अणु 5, 0xf पूर्ण,
पूर्ण;

/* ratio क्रम input clk freq */
अटल स्थिर काष्ठा nau8825_fll_attr fll_ratio[] = अणु
	अणु 512000, 0x01 पूर्ण,
	अणु 256000, 0x02 पूर्ण,
	अणु 128000, 0x04 पूर्ण,
	अणु 64000, 0x08 पूर्ण,
	अणु 32000, 0x10 पूर्ण,
	अणु 8000, 0x20 पूर्ण,
	अणु 4000, 0x40 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा nau8825_fll_attr fll_pre_scalar[] = अणु
	अणु 1, 0x0 पूर्ण,
	अणु 2, 0x1 पूर्ण,
	अणु 4, 0x2 पूर्ण,
	अणु 8, 0x3 पूर्ण,
पूर्ण;

/* over sampling rate */
काष्ठा nau8825_osr_attr अणु
	अचिन्हित पूर्णांक osr;
	अचिन्हित पूर्णांक clk_src;
पूर्ण;

अटल स्थिर काष्ठा nau8825_osr_attr osr_dac_sel[] = अणु
	अणु 64, 2 पूर्ण,	/* OSR 64, SRC 1/4 */
	अणु 256, 0 पूर्ण,	/* OSR 256, SRC 1 */
	अणु 128, 1 पूर्ण,	/* OSR 128, SRC 1/2 */
	अणु 0, 0 पूर्ण,
	अणु 32, 3 पूर्ण,	/* OSR 32, SRC 1/8 */
पूर्ण;

अटल स्थिर काष्ठा nau8825_osr_attr osr_adc_sel[] = अणु
	अणु 32, 3 पूर्ण,	/* OSR 32, SRC 1/8 */
	अणु 64, 2 पूर्ण,	/* OSR 64, SRC 1/4 */
	अणु 128, 1 पूर्ण,	/* OSR 128, SRC 1/2 */
	अणु 256, 0 पूर्ण,	/* OSR 256, SRC 1 */
पूर्ण;

अटल स्थिर काष्ठा reg_शेष nau8825_reg_शेषs[] = अणु
	अणु NAU8825_REG_ENA_CTRL, 0x00ff पूर्ण,
	अणु NAU8825_REG_IIC_ADDR_SET, 0x0 पूर्ण,
	अणु NAU8825_REG_CLK_DIVIDER, 0x0050 पूर्ण,
	अणु NAU8825_REG_FLL1, 0x0 पूर्ण,
	अणु NAU8825_REG_FLL2, 0x3126 पूर्ण,
	अणु NAU8825_REG_FLL3, 0x0008 पूर्ण,
	अणु NAU8825_REG_FLL4, 0x0010 पूर्ण,
	अणु NAU8825_REG_FLL5, 0x0 पूर्ण,
	अणु NAU8825_REG_FLL6, 0x6000 पूर्ण,
	अणु NAU8825_REG_FLL_VCO_RSV, 0xf13c पूर्ण,
	अणु NAU8825_REG_HSD_CTRL, 0x000c पूर्ण,
	अणु NAU8825_REG_JACK_DET_CTRL, 0x0 पूर्ण,
	अणु NAU8825_REG_INTERRUPT_MASK, 0x0 पूर्ण,
	अणु NAU8825_REG_INTERRUPT_DIS_CTRL, 0xffff पूर्ण,
	अणु NAU8825_REG_SAR_CTRL, 0x0015 पूर्ण,
	अणु NAU8825_REG_KEYDET_CTRL, 0x0110 पूर्ण,
	अणु NAU8825_REG_VDET_THRESHOLD_1, 0x0 पूर्ण,
	अणु NAU8825_REG_VDET_THRESHOLD_2, 0x0 पूर्ण,
	अणु NAU8825_REG_VDET_THRESHOLD_3, 0x0 पूर्ण,
	अणु NAU8825_REG_VDET_THRESHOLD_4, 0x0 पूर्ण,
	अणु NAU8825_REG_GPIO34_CTRL, 0x0 पूर्ण,
	अणु NAU8825_REG_GPIO12_CTRL, 0x0 पूर्ण,
	अणु NAU8825_REG_TDM_CTRL, 0x0 पूर्ण,
	अणु NAU8825_REG_I2S_PCM_CTRL1, 0x000b पूर्ण,
	अणु NAU8825_REG_I2S_PCM_CTRL2, 0x8010 पूर्ण,
	अणु NAU8825_REG_LEFT_TIME_SLOT, 0x0 पूर्ण,
	अणु NAU8825_REG_RIGHT_TIME_SLOT, 0x0 पूर्ण,
	अणु NAU8825_REG_BIQ_CTRL, 0x0 पूर्ण,
	अणु NAU8825_REG_BIQ_COF1, 0x0 पूर्ण,
	अणु NAU8825_REG_BIQ_COF2, 0x0 पूर्ण,
	अणु NAU8825_REG_BIQ_COF3, 0x0 पूर्ण,
	अणु NAU8825_REG_BIQ_COF4, 0x0 पूर्ण,
	अणु NAU8825_REG_BIQ_COF5, 0x0 पूर्ण,
	अणु NAU8825_REG_BIQ_COF6, 0x0 पूर्ण,
	अणु NAU8825_REG_BIQ_COF7, 0x0 पूर्ण,
	अणु NAU8825_REG_BIQ_COF8, 0x0 पूर्ण,
	अणु NAU8825_REG_BIQ_COF9, 0x0 पूर्ण,
	अणु NAU8825_REG_BIQ_COF10, 0x0 पूर्ण,
	अणु NAU8825_REG_ADC_RATE, 0x0010 पूर्ण,
	अणु NAU8825_REG_DAC_CTRL1, 0x0001 पूर्ण,
	अणु NAU8825_REG_DAC_CTRL2, 0x0 पूर्ण,
	अणु NAU8825_REG_DAC_DGAIN_CTRL, 0x0 पूर्ण,
	अणु NAU8825_REG_ADC_DGAIN_CTRL, 0x00cf पूर्ण,
	अणु NAU8825_REG_MUTE_CTRL, 0x0 पूर्ण,
	अणु NAU8825_REG_HSVOL_CTRL, 0x0 पूर्ण,
	अणु NAU8825_REG_DACL_CTRL, 0x02cf पूर्ण,
	अणु NAU8825_REG_DACR_CTRL, 0x00cf पूर्ण,
	अणु NAU8825_REG_ADC_DRC_KNEE_IP12, 0x1486 पूर्ण,
	अणु NAU8825_REG_ADC_DRC_KNEE_IP34, 0x0f12 पूर्ण,
	अणु NAU8825_REG_ADC_DRC_SLOPES, 0x25ff पूर्ण,
	अणु NAU8825_REG_ADC_DRC_ATKDCY, 0x3457 पूर्ण,
	अणु NAU8825_REG_DAC_DRC_KNEE_IP12, 0x1486 पूर्ण,
	अणु NAU8825_REG_DAC_DRC_KNEE_IP34, 0x0f12 पूर्ण,
	अणु NAU8825_REG_DAC_DRC_SLOPES, 0x25f9 पूर्ण,
	अणु NAU8825_REG_DAC_DRC_ATKDCY, 0x3457 पूर्ण,
	अणु NAU8825_REG_IMM_MODE_CTRL, 0x0 पूर्ण,
	अणु NAU8825_REG_CLASSG_CTRL, 0x0 पूर्ण,
	अणु NAU8825_REG_OPT_EFUSE_CTRL, 0x0 पूर्ण,
	अणु NAU8825_REG_MISC_CTRL, 0x0 पूर्ण,
	अणु NAU8825_REG_BIAS_ADJ, 0x0 पूर्ण,
	अणु NAU8825_REG_TRIM_SETTINGS, 0x0 पूर्ण,
	अणु NAU8825_REG_ANALOG_CONTROL_1, 0x0 पूर्ण,
	अणु NAU8825_REG_ANALOG_CONTROL_2, 0x0 पूर्ण,
	अणु NAU8825_REG_ANALOG_ADC_1, 0x0011 पूर्ण,
	अणु NAU8825_REG_ANALOG_ADC_2, 0x0020 पूर्ण,
	अणु NAU8825_REG_RDAC, 0x0008 पूर्ण,
	अणु NAU8825_REG_MIC_BIAS, 0x0006 पूर्ण,
	अणु NAU8825_REG_BOOST, 0x0 पूर्ण,
	अणु NAU8825_REG_FEPGA, 0x0 पूर्ण,
	अणु NAU8825_REG_POWER_UP_CONTROL, 0x0 पूर्ण,
	अणु NAU8825_REG_CHARGE_PUMP, 0x0 पूर्ण,
पूर्ण;

/* रेजिस्टर backup table when cross talk detection */
अटल काष्ठा reg_शेष nau8825_xtalk_baktab[] = अणु
	अणु NAU8825_REG_ADC_DGAIN_CTRL, 0x00cf पूर्ण,
	अणु NAU8825_REG_HSVOL_CTRL, 0 पूर्ण,
	अणु NAU8825_REG_DACL_CTRL, 0x00cf पूर्ण,
	अणु NAU8825_REG_DACR_CTRL, 0x02cf पूर्ण,
पूर्ण;

अटल स्थिर अचिन्हित लघु logtable[256] = अणु
	0x0000, 0x0171, 0x02e0, 0x044e, 0x05ba, 0x0725, 0x088e, 0x09f7,
	0x0b5d, 0x0cc3, 0x0e27, 0x0f8a, 0x10eb, 0x124b, 0x13aa, 0x1508,
	0x1664, 0x17bf, 0x1919, 0x1a71, 0x1bc8, 0x1d1e, 0x1e73, 0x1fc6,
	0x2119, 0x226a, 0x23ba, 0x2508, 0x2656, 0x27a2, 0x28ed, 0x2a37,
	0x2b80, 0x2cc8, 0x2e0f, 0x2f54, 0x3098, 0x31dc, 0x331e, 0x345f,
	0x359f, 0x36de, 0x381b, 0x3958, 0x3a94, 0x3bce, 0x3d08, 0x3e41,
	0x3f78, 0x40af, 0x41e4, 0x4319, 0x444c, 0x457f, 0x46b0, 0x47e1,
	0x4910, 0x4a3f, 0x4b6c, 0x4c99, 0x4dc5, 0x4eef, 0x5019, 0x5142,
	0x526a, 0x5391, 0x54b7, 0x55dc, 0x5700, 0x5824, 0x5946, 0x5a68,
	0x5b89, 0x5ca8, 0x5dc7, 0x5ee5, 0x6003, 0x611f, 0x623a, 0x6355,
	0x646f, 0x6588, 0x66a0, 0x67b7, 0x68ce, 0x69e4, 0x6af8, 0x6c0c,
	0x6d20, 0x6e32, 0x6f44, 0x7055, 0x7165, 0x7274, 0x7383, 0x7490,
	0x759d, 0x76aa, 0x77b5, 0x78c0, 0x79ca, 0x7ad3, 0x7bdb, 0x7ce3,
	0x7dea, 0x7ef0, 0x7ff6, 0x80fb, 0x81ff, 0x8302, 0x8405, 0x8507,
	0x8608, 0x8709, 0x8809, 0x8908, 0x8a06, 0x8b04, 0x8c01, 0x8cfe,
	0x8dfa, 0x8ef5, 0x8fef, 0x90e9, 0x91e2, 0x92db, 0x93d2, 0x94ca,
	0x95c0, 0x96b6, 0x97ab, 0x98a0, 0x9994, 0x9a87, 0x9b7a, 0x9c6c,
	0x9d5e, 0x9e4f, 0x9f3f, 0xa02e, 0xa11e, 0xa20c, 0xa2fa, 0xa3e7,
	0xa4d4, 0xa5c0, 0xa6ab, 0xa796, 0xa881, 0xa96a, 0xaa53, 0xab3c,
	0xac24, 0xad0c, 0xadf2, 0xaed9, 0xafbe, 0xb0a4, 0xb188, 0xb26c,
	0xb350, 0xb433, 0xb515, 0xb5f7, 0xb6d9, 0xb7ba, 0xb89a, 0xb97a,
	0xba59, 0xbb38, 0xbc16, 0xbcf4, 0xbdd1, 0xbead, 0xbf8a, 0xc065,
	0xc140, 0xc21b, 0xc2f5, 0xc3cf, 0xc4a8, 0xc580, 0xc658, 0xc730,
	0xc807, 0xc8de, 0xc9b4, 0xca8a, 0xcb5f, 0xcc34, 0xcd08, 0xcddc,
	0xceaf, 0xcf82, 0xd054, 0xd126, 0xd1f7, 0xd2c8, 0xd399, 0xd469,
	0xd538, 0xd607, 0xd6d6, 0xd7a4, 0xd872, 0xd93f, 0xda0c, 0xdad9,
	0xdba5, 0xdc70, 0xdd3b, 0xde06, 0xded0, 0xdf9a, 0xe063, 0xe12c,
	0xe1f5, 0xe2bd, 0xe385, 0xe44c, 0xe513, 0xe5d9, 0xe69f, 0xe765,
	0xe82a, 0xe8ef, 0xe9b3, 0xea77, 0xeb3b, 0xebfe, 0xecc1, 0xed83,
	0xee45, 0xef06, 0xefc8, 0xf088, 0xf149, 0xf209, 0xf2c8, 0xf387,
	0xf446, 0xf505, 0xf5c3, 0xf680, 0xf73e, 0xf7fb, 0xf8b7, 0xf973,
	0xfa2f, 0xfaea, 0xfba5, 0xfc60, 0xfd1a, 0xfdd4, 0xfe8e, 0xff47
पूर्ण;

/**
 * nau8825_sema_acquire - acquire the semaphore of nau88l25
 * @nau8825:  component to रेजिस्टर the codec निजी data with
 * @समयout: how दीर्घ in jअगरfies to रुको beक्रमe failure or zero to रुको
 * until release
 *
 * Attempts to acquire the semaphore with number of jअगरfies. If no more
 * tasks are allowed to acquire the semaphore, calling this function will
 * put the task to sleep. If the semaphore is not released within the
 * specअगरied number of jअगरfies, this function वापसs.
 * If the semaphore is not released within the specअगरied number of jअगरfies,
 * this function वापसs -ETIME. If the sleep is पूर्णांकerrupted by a संकेत,
 * this function will वापस -EINTR. It वापसs 0 अगर the semaphore was
 * acquired successfully.
 *
 * Acquires the semaphore without jअगरfies. Try to acquire the semaphore
 * atomically. Returns 0 अगर the semaphore has been acquired successfully
 * or 1 अगर it cannot be acquired.
 */
अटल पूर्णांक nau8825_sema_acquire(काष्ठा nau8825 *nau8825, दीर्घ समयout)
अणु
	पूर्णांक ret;

	अगर (समयout) अणु
		ret = करोwn_समयout(&nau8825->xtalk_sem, समयout);
		अगर (ret < 0)
			dev_warn(nau8825->dev, "Acquire semaphore timeout\n");
	पूर्ण अन्यथा अणु
		ret = करोwn_trylock(&nau8825->xtalk_sem);
		अगर (ret)
			dev_warn(nau8825->dev, "Acquire semaphore fail\n");
	पूर्ण

	वापस ret;
पूर्ण

/**
 * nau8825_sema_release - release the semaphore of nau88l25
 * @nau8825:  component to रेजिस्टर the codec निजी data with
 *
 * Release the semaphore which may be called from any context and
 * even by tasks which have never called करोwn().
 */
अटल अंतरभूत व्योम nau8825_sema_release(काष्ठा nau8825 *nau8825)
अणु
	up(&nau8825->xtalk_sem);
पूर्ण

/**
 * nau8825_sema_reset - reset the semaphore क्रम nau88l25
 * @nau8825:  component to रेजिस्टर the codec निजी data with
 *
 * Reset the counter of the semaphore. Call this function to restart
 * a new round task management.
 */
अटल अंतरभूत व्योम nau8825_sema_reset(काष्ठा nau8825 *nau8825)
अणु
	nau8825->xtalk_sem.count = 1;
पूर्ण

/**
 * nau8825_hpvol_ramp - Ramp up the headphone volume change gradually to target level.
 *
 * @nau8825:  component to रेजिस्टर the codec निजी data with
 * @vol_from: the volume to start up
 * @vol_to: the target volume
 * @step: the volume span to move on
 *
 * The headphone volume is from 0dB to minimum -54dB and -1dB per step.
 * If the volume changes sharp, there is a pop noise heard in headphone. We
 * provide the function to ramp up the volume up or करोwn by delaying 10ms
 * per step.
 */
अटल व्योम nau8825_hpvol_ramp(काष्ठा nau8825 *nau8825,
	अचिन्हित पूर्णांक vol_from, अचिन्हित पूर्णांक vol_to, अचिन्हित पूर्णांक step)
अणु
	अचिन्हित पूर्णांक value, volume, ramp_up, from, to;

	अगर (vol_from == vol_to || step == 0) अणु
		वापस;
	पूर्ण अन्यथा अगर (vol_from < vol_to) अणु
		ramp_up = true;
		from = vol_from;
		to = vol_to;
	पूर्ण अन्यथा अणु
		ramp_up = false;
		from = vol_to;
		to = vol_from;
	पूर्ण
	/* only handle volume from 0dB to minimum -54dB */
	अगर (to > NAU8825_HP_VOL_MIN)
		to = NAU8825_HP_VOL_MIN;

	क्रम (volume = from; volume < to; volume += step) अणु
		अगर (ramp_up)
			value = volume;
		अन्यथा
			value = to - volume + from;
		regmap_update_bits(nau8825->regmap, NAU8825_REG_HSVOL_CTRL,
			NAU8825_HPL_VOL_MASK | NAU8825_HPR_VOL_MASK,
			(value << NAU8825_HPL_VOL_SFT) | value);
		usleep_range(10000, 10500);
	पूर्ण
	अगर (ramp_up)
		value = to;
	अन्यथा
		value = from;
	regmap_update_bits(nau8825->regmap, NAU8825_REG_HSVOL_CTRL,
		NAU8825_HPL_VOL_MASK | NAU8825_HPR_VOL_MASK,
		(value << NAU8825_HPL_VOL_SFT) | value);
पूर्ण

/**
 * nau8825_पूर्णांकlog10_dec3 - Computes log10 of a value
 * the result is round off to 3 decimal. This function takes reference to
 * dvb-math. The source code locates as the following.
 * Linux/drivers/media/dvb-core/dvb_math.c
 * @value:  input क्रम log10
 *
 * वापस log10(value) * 1000
 */
अटल u32 nau8825_पूर्णांकlog10_dec3(u32 value)
अणु
	u32 msb, logentry, signअगरicand, पूर्णांकerpolation, log10val;
	u64 log2val;

	/* first detect the msb (count begins at 0) */
	msb = fls(value) - 1;
	/**
	 *      now we use a logtable after the following method:
	 *
	 *      log2(2^x * y) * 2^24 = x * 2^24 + log2(y) * 2^24
	 *      where x = msb and thereक्रमe 1 <= y < 2
	 *      first y is determined by shअगरting the value left
	 *      so that msb is bit 31
	 *              0x00231f56 -> 0x8C7D5800
	 *      the result is y * 2^31 -> "significand"
	 *      then the highest 9 bits are used क्रम a table lookup
	 *      the highest bit is discarded because it's always set
	 *      the highest nine bits in our example are 100011000
	 *      so we would use the entry 0x18
	 */
	signअगरicand = value << (31 - msb);
	logentry = (signअगरicand >> 23) & 0xff;
	/**
	 *      last step we करो is पूर्णांकerpolation because of the
	 *      limitations of the log table the error is that part of
	 *      the signअगरicand which isn't used क्रम lookup then we
	 *      compute the ratio between the error and the next table entry
	 *      and पूर्णांकerpolate it between the log table entry used and the
	 *      next one the biggest error possible is 0x7fffff
	 *      (in our example it's 0x7D5800)
	 *      needed value क्रम next table entry is 0x800000
	 *      so the पूर्णांकerpolation is
	 *      (error / 0x800000) * (logtable_next - logtable_current)
	 *      in the implementation the भागision is moved to the end क्रम
	 *      better accuracy there is also an overflow correction अगर
	 *      logtable_next is 256
	 */
	पूर्णांकerpolation = ((signअगरicand & 0x7fffff) *
		((logtable[(logentry + 1) & 0xff] -
		logtable[logentry]) & 0xffff)) >> 15;

	log2val = ((msb << 24) + (logtable[logentry] << 8) + पूर्णांकerpolation);
	/**
	 *      log10(x) = log2(x) * log10(2)
	 */
	log10val = (log2val * LOG10_MAGIC) >> 31;
	/**
	 *      the result is round off to 3 decimal
	 */
	वापस log10val / ((1 << 24) / 1000);
पूर्ण

/**
 * nau8825_xtalk_sidetone - computes cross talk suppression sidetone gain.
 *
 * @sig_org: orignal संकेत level
 * @sig_cros: cross talk संकेत level
 *
 * The orignal and cross talk संकेत vlues need to be अक्षरacterized.
 * Once these values have been अक्षरacterized, this sidetone value
 * can be converted to decibel with the equation below.
 * sidetone = 20 * log (original संकेत level / crosstalk संकेत level)
 *
 * वापस cross talk sidetone gain
 */
अटल u32 nau8825_xtalk_sidetone(u32 sig_org, u32 sig_cros)
अणु
	u32 gain, sidetone;

	अगर (WARN_ON(sig_org == 0 || sig_cros == 0))
		वापस 0;

	sig_org = nau8825_पूर्णांकlog10_dec3(sig_org);
	sig_cros = nau8825_पूर्णांकlog10_dec3(sig_cros);
	अगर (sig_org >= sig_cros)
		gain = (sig_org - sig_cros) * 20 + GAIN_AUGMENT;
	अन्यथा
		gain = (sig_cros - sig_org) * 20 + GAIN_AUGMENT;
	sidetone = SIDETONE_BASE - gain * 2;
	sidetone /= 1000;

	वापस sidetone;
पूर्ण

अटल पूर्णांक nau8825_xtalk_baktab_index_by_reg(अचिन्हित पूर्णांक reg)
अणु
	पूर्णांक index;

	क्रम (index = 0; index < ARRAY_SIZE(nau8825_xtalk_baktab); index++)
		अगर (nau8825_xtalk_baktab[index].reg == reg)
			वापस index;
	वापस -EINVAL;
पूर्ण

अटल व्योम nau8825_xtalk_backup(काष्ठा nau8825 *nau8825)
अणु
	पूर्णांक i;

	अगर (nau8825->xtalk_baktab_initialized)
		वापस;

	/* Backup some रेजिस्टर values to backup table */
	क्रम (i = 0; i < ARRAY_SIZE(nau8825_xtalk_baktab); i++)
		regmap_पढ़ो(nau8825->regmap, nau8825_xtalk_baktab[i].reg,
				&nau8825_xtalk_baktab[i].def);

	nau8825->xtalk_baktab_initialized = true;
पूर्ण

अटल व्योम nau8825_xtalk_restore(काष्ठा nau8825 *nau8825, bool cause_cancel)
अणु
	पूर्णांक i, volume;

	अगर (!nau8825->xtalk_baktab_initialized)
		वापस;

	/* Restore रेजिस्टर values from backup table; When the driver restores
	 * the headphone volume in XTALK_DONE state, it needs recover to
	 * original level gradually with 3dB per step क्रम less pop noise.
	 * Otherwise, the restore should करो ASAP.
	 */
	क्रम (i = 0; i < ARRAY_SIZE(nau8825_xtalk_baktab); i++) अणु
		अगर (!cause_cancel && nau8825_xtalk_baktab[i].reg ==
			NAU8825_REG_HSVOL_CTRL) अणु
			/* Ramping up the volume change to reduce pop noise */
			volume = nau8825_xtalk_baktab[i].def &
				NAU8825_HPR_VOL_MASK;
			nau8825_hpvol_ramp(nau8825, 0, volume, 3);
			जारी;
		पूर्ण
		regmap_ग_लिखो(nau8825->regmap, nau8825_xtalk_baktab[i].reg,
				nau8825_xtalk_baktab[i].def);
	पूर्ण

	nau8825->xtalk_baktab_initialized = false;
पूर्ण

अटल व्योम nau8825_xtalk_prepare_dac(काष्ठा nau8825 *nau8825)
अणु
	/* Enable घातer of DAC path */
	regmap_update_bits(nau8825->regmap, NAU8825_REG_ENA_CTRL,
		NAU8825_ENABLE_DACR | NAU8825_ENABLE_DACL |
		NAU8825_ENABLE_ADC | NAU8825_ENABLE_ADC_CLK |
		NAU8825_ENABLE_DAC_CLK, NAU8825_ENABLE_DACR |
		NAU8825_ENABLE_DACL | NAU8825_ENABLE_ADC |
		NAU8825_ENABLE_ADC_CLK | NAU8825_ENABLE_DAC_CLK);
	/* Prevent startup click by letting अक्षरge pump to ramp up and
	 * change bump enable
	 */
	regmap_update_bits(nau8825->regmap, NAU8825_REG_CHARGE_PUMP,
		NAU8825_JAMNODCLOW | NAU8825_CHANRGE_PUMP_EN,
		NAU8825_JAMNODCLOW | NAU8825_CHANRGE_PUMP_EN);
	/* Enable घड़ी sync of DAC and DAC घड़ी */
	regmap_update_bits(nau8825->regmap, NAU8825_REG_RDAC,
		NAU8825_RDAC_EN | NAU8825_RDAC_CLK_EN |
		NAU8825_RDAC_FS_BCLK_ENB,
		NAU8825_RDAC_EN | NAU8825_RDAC_CLK_EN);
	/* Power up output driver with 2 stage */
	regmap_update_bits(nau8825->regmap, NAU8825_REG_POWER_UP_CONTROL,
		NAU8825_POWERUP_INTEGR_R | NAU8825_POWERUP_INTEGR_L |
		NAU8825_POWERUP_DRV_IN_R | NAU8825_POWERUP_DRV_IN_L,
		NAU8825_POWERUP_INTEGR_R | NAU8825_POWERUP_INTEGR_L |
		NAU8825_POWERUP_DRV_IN_R | NAU8825_POWERUP_DRV_IN_L);
	regmap_update_bits(nau8825->regmap, NAU8825_REG_POWER_UP_CONTROL,
		NAU8825_POWERUP_HP_DRV_R | NAU8825_POWERUP_HP_DRV_L,
		NAU8825_POWERUP_HP_DRV_R | NAU8825_POWERUP_HP_DRV_L);
	/* HP outमाला_दो not shouted to ground  */
	regmap_update_bits(nau8825->regmap, NAU8825_REG_HSD_CTRL,
		NAU8825_SPKR_DWN1R | NAU8825_SPKR_DWN1L, 0);
	/* Enable HP boost driver */
	regmap_update_bits(nau8825->regmap, NAU8825_REG_BOOST,
		NAU8825_HP_BOOST_DIS, NAU8825_HP_BOOST_DIS);
	/* Enable class G compare path to supply 1.8V or 0.9V. */
	regmap_update_bits(nau8825->regmap, NAU8825_REG_CLASSG_CTRL,
		NAU8825_CLASSG_LDAC_EN | NAU8825_CLASSG_RDAC_EN,
		NAU8825_CLASSG_LDAC_EN | NAU8825_CLASSG_RDAC_EN);
पूर्ण

अटल व्योम nau8825_xtalk_prepare_adc(काष्ठा nau8825 *nau8825)
अणु
	/* Power up left ADC and उठाओ 5dB than Vmid क्रम Vref  */
	regmap_update_bits(nau8825->regmap, NAU8825_REG_ANALOG_ADC_2,
		NAU8825_POWERUP_ADCL | NAU8825_ADC_VREFSEL_MASK,
		NAU8825_POWERUP_ADCL | NAU8825_ADC_VREFSEL_VMID_PLUS_0_5DB);
पूर्ण

अटल व्योम nau8825_xtalk_घड़ी(काष्ठा nau8825 *nau8825)
अणु
	/* Recover FLL शेष value */
	regmap_ग_लिखो(nau8825->regmap, NAU8825_REG_FLL1, 0x0);
	regmap_ग_लिखो(nau8825->regmap, NAU8825_REG_FLL2, 0x3126);
	regmap_ग_लिखो(nau8825->regmap, NAU8825_REG_FLL3, 0x0008);
	regmap_ग_लिखो(nau8825->regmap, NAU8825_REG_FLL4, 0x0010);
	regmap_ग_लिखो(nau8825->regmap, NAU8825_REG_FLL5, 0x0);
	regmap_ग_लिखो(nau8825->regmap, NAU8825_REG_FLL6, 0x6000);
	/* Enable पूर्णांकernal VCO घड़ी क्रम detection संकेत generated */
	regmap_update_bits(nau8825->regmap, NAU8825_REG_CLK_DIVIDER,
		NAU8825_CLK_SRC_MASK, NAU8825_CLK_SRC_VCO);
	regmap_update_bits(nau8825->regmap, NAU8825_REG_FLL6, NAU8825_DCO_EN,
		NAU8825_DCO_EN);
	/* Given specअगरic घड़ी frequency of पूर्णांकernal घड़ी to
	 * generate संकेत.
	 */
	regmap_update_bits(nau8825->regmap, NAU8825_REG_CLK_DIVIDER,
		NAU8825_CLK_MCLK_SRC_MASK, 0xf);
	regmap_update_bits(nau8825->regmap, NAU8825_REG_FLL1,
		NAU8825_FLL_RATIO_MASK, 0x10);
पूर्ण

अटल व्योम nau8825_xtalk_prepare(काष्ठा nau8825 *nau8825)
अणु
	पूर्णांक volume, index;

	/* Backup those रेजिस्टरs changed by cross talk detection */
	nau8825_xtalk_backup(nau8825);
	/* Config IIS as master to output संकेत by codec */
	regmap_update_bits(nau8825->regmap, NAU8825_REG_I2S_PCM_CTRL2,
		NAU8825_I2S_MS_MASK | NAU8825_I2S_LRC_DIV_MASK |
		NAU8825_I2S_BLK_DIV_MASK, NAU8825_I2S_MS_MASTER |
		(0x2 << NAU8825_I2S_LRC_DIV_SFT) | 0x1);
	/* Ramp up headphone volume to 0dB to get better perक्रमmance and
	 * aव्योम pop noise in headphone.
	 */
	index = nau8825_xtalk_baktab_index_by_reg(NAU8825_REG_HSVOL_CTRL);
	अगर (index != -EINVAL) अणु
		volume = nau8825_xtalk_baktab[index].def &
				NAU8825_HPR_VOL_MASK;
		nau8825_hpvol_ramp(nau8825, volume, 0, 3);
	पूर्ण
	nau8825_xtalk_घड़ी(nau8825);
	nau8825_xtalk_prepare_dac(nau8825);
	nau8825_xtalk_prepare_adc(nau8825);
	/* Config channel path and digital gain */
	regmap_update_bits(nau8825->regmap, NAU8825_REG_DACL_CTRL,
		NAU8825_DACL_CH_SEL_MASK | NAU8825_DACL_CH_VOL_MASK,
		NAU8825_DACL_CH_SEL_L | 0xab);
	regmap_update_bits(nau8825->regmap, NAU8825_REG_DACR_CTRL,
		NAU8825_DACR_CH_SEL_MASK | NAU8825_DACR_CH_VOL_MASK,
		NAU8825_DACR_CH_SEL_R | 0xab);
	/* Config cross talk parameters and generate the 23Hz sine wave with
	 * 1/16 full scale of संकेत level क्रम impedance measurement.
	 */
	regmap_update_bits(nau8825->regmap, NAU8825_REG_IMM_MODE_CTRL,
		NAU8825_IMM_THD_MASK | NAU8825_IMM_GEN_VOL_MASK |
		NAU8825_IMM_CYC_MASK | NAU8825_IMM_DAC_SRC_MASK,
		(0x9 << NAU8825_IMM_THD_SFT) | NAU8825_IMM_GEN_VOL_1_16th |
		NAU8825_IMM_CYC_8192 | NAU8825_IMM_DAC_SRC_SIN);
	/* RMS पूर्णांकrruption enable */
	regmap_update_bits(nau8825->regmap,
		NAU8825_REG_INTERRUPT_MASK, NAU8825_IRQ_RMS_EN, 0);
	/* Power up left and right DAC */
	regmap_update_bits(nau8825->regmap, NAU8825_REG_CHARGE_PUMP,
		NAU8825_POWER_DOWN_DACR | NAU8825_POWER_DOWN_DACL, 0);
पूर्ण

अटल व्योम nau8825_xtalk_clean_dac(काष्ठा nau8825 *nau8825)
अणु
	/* Disable HP boost driver */
	regmap_update_bits(nau8825->regmap, NAU8825_REG_BOOST,
		NAU8825_HP_BOOST_DIS, 0);
	/* HP outमाला_दो shouted to ground  */
	regmap_update_bits(nau8825->regmap, NAU8825_REG_HSD_CTRL,
		NAU8825_SPKR_DWN1R | NAU8825_SPKR_DWN1L,
		NAU8825_SPKR_DWN1R | NAU8825_SPKR_DWN1L);
	/* Power करोwn left and right DAC */
	regmap_update_bits(nau8825->regmap, NAU8825_REG_CHARGE_PUMP,
		NAU8825_POWER_DOWN_DACR | NAU8825_POWER_DOWN_DACL,
		NAU8825_POWER_DOWN_DACR | NAU8825_POWER_DOWN_DACL);
	/* Enable the TESTDAC and  disable L/R HP impedance */
	regmap_update_bits(nau8825->regmap, NAU8825_REG_BIAS_ADJ,
		NAU8825_BIAS_HPR_IMP | NAU8825_BIAS_HPL_IMP |
		NAU8825_BIAS_TESTDAC_EN, NAU8825_BIAS_TESTDAC_EN);
	/* Power करोwn output driver with 2 stage */
	regmap_update_bits(nau8825->regmap, NAU8825_REG_POWER_UP_CONTROL,
		NAU8825_POWERUP_HP_DRV_R | NAU8825_POWERUP_HP_DRV_L, 0);
	regmap_update_bits(nau8825->regmap, NAU8825_REG_POWER_UP_CONTROL,
		NAU8825_POWERUP_INTEGR_R | NAU8825_POWERUP_INTEGR_L |
		NAU8825_POWERUP_DRV_IN_R | NAU8825_POWERUP_DRV_IN_L, 0);
	/* Disable घड़ी sync of DAC and DAC घड़ी */
	regmap_update_bits(nau8825->regmap, NAU8825_REG_RDAC,
		NAU8825_RDAC_EN | NAU8825_RDAC_CLK_EN, 0);
	/* Disable अक्षरge pump ramp up function and change bump */
	regmap_update_bits(nau8825->regmap, NAU8825_REG_CHARGE_PUMP,
		NAU8825_JAMNODCLOW | NAU8825_CHANRGE_PUMP_EN, 0);
	/* Disable घातer of DAC path */
	regmap_update_bits(nau8825->regmap, NAU8825_REG_ENA_CTRL,
		NAU8825_ENABLE_DACR | NAU8825_ENABLE_DACL |
		NAU8825_ENABLE_ADC_CLK | NAU8825_ENABLE_DAC_CLK, 0);
	अगर (!nau8825->irq)
		regmap_update_bits(nau8825->regmap,
			NAU8825_REG_ENA_CTRL, NAU8825_ENABLE_ADC, 0);
पूर्ण

अटल व्योम nau8825_xtalk_clean_adc(काष्ठा nau8825 *nau8825)
अणु
	/* Power करोwn left ADC and restore voltage to Vmid */
	regmap_update_bits(nau8825->regmap, NAU8825_REG_ANALOG_ADC_2,
		NAU8825_POWERUP_ADCL | NAU8825_ADC_VREFSEL_MASK, 0);
पूर्ण

अटल व्योम nau8825_xtalk_clean(काष्ठा nau8825 *nau8825, bool cause_cancel)
अणु
	/* Enable पूर्णांकernal VCO needed क्रम पूर्णांकerruptions */
	nau8825_configure_sysclk(nau8825, NAU8825_CLK_INTERNAL, 0);
	nau8825_xtalk_clean_dac(nau8825);
	nau8825_xtalk_clean_adc(nau8825);
	/* Clear cross talk parameters and disable */
	regmap_ग_लिखो(nau8825->regmap, NAU8825_REG_IMM_MODE_CTRL, 0);
	/* RMS पूर्णांकrruption disable */
	regmap_update_bits(nau8825->regmap, NAU8825_REG_INTERRUPT_MASK,
		NAU8825_IRQ_RMS_EN, NAU8825_IRQ_RMS_EN);
	/* Recover शेष value क्रम IIS */
	regmap_update_bits(nau8825->regmap, NAU8825_REG_I2S_PCM_CTRL2,
		NAU8825_I2S_MS_MASK | NAU8825_I2S_LRC_DIV_MASK |
		NAU8825_I2S_BLK_DIV_MASK, NAU8825_I2S_MS_SLAVE);
	/* Restore value of specअगरic रेजिस्टर क्रम cross talk */
	nau8825_xtalk_restore(nau8825, cause_cancel);
पूर्ण

अटल व्योम nau8825_xtalk_imm_start(काष्ठा nau8825 *nau8825, पूर्णांक vol)
अणु
	/* Apply ADC volume क्रम better cross talk perक्रमmance */
	regmap_update_bits(nau8825->regmap, NAU8825_REG_ADC_DGAIN_CTRL,
				NAU8825_ADC_DIG_VOL_MASK, vol);
	/* Disables JKTIP(HPL) DAC channel क्रम right to left measurement.
	 * Do it beक्रमe sending संकेत in order to erase pop noise.
	 */
	regmap_update_bits(nau8825->regmap, NAU8825_REG_BIAS_ADJ,
		NAU8825_BIAS_TESTDACR_EN | NAU8825_BIAS_TESTDACL_EN,
		NAU8825_BIAS_TESTDACL_EN);
	चयन (nau8825->xtalk_state) अणु
	हाल NAU8825_XTALK_HPR_R2L:
		/* Enable right headphone impedance */
		regmap_update_bits(nau8825->regmap, NAU8825_REG_BIAS_ADJ,
			NAU8825_BIAS_HPR_IMP | NAU8825_BIAS_HPL_IMP,
			NAU8825_BIAS_HPR_IMP);
		अवरोध;
	हाल NAU8825_XTALK_HPL_R2L:
		/* Enable left headphone impedance */
		regmap_update_bits(nau8825->regmap, NAU8825_REG_BIAS_ADJ,
			NAU8825_BIAS_HPR_IMP | NAU8825_BIAS_HPL_IMP,
			NAU8825_BIAS_HPL_IMP);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	msleep(100);
	/* Impedance measurement mode enable */
	regmap_update_bits(nau8825->regmap, NAU8825_REG_IMM_MODE_CTRL,
				NAU8825_IMM_EN, NAU8825_IMM_EN);
पूर्ण

अटल व्योम nau8825_xtalk_imm_stop(काष्ठा nau8825 *nau8825)
अणु
	/* Impedance measurement mode disable */
	regmap_update_bits(nau8825->regmap,
		NAU8825_REG_IMM_MODE_CTRL, NAU8825_IMM_EN, 0);
पूर्ण

/* The cross talk measurement function can reduce cross talk across the
 * JKTIP(HPL) and JKR1(HPR) outमाला_दो which measures the cross talk संकेत
 * level to determine what cross talk reduction gain is. This प्रणाली works by
 * sending a 23Hz -24dBV sine wave पूर्णांकo the headset output DAC and through
 * the PGA. The output of the PGA is then connected to an पूर्णांकernal current
 * sense which measures the attenuated 23Hz संकेत and passing the output to
 * an ADC which converts the measurement to a binary code. With two separated
 * measurement, one क्रम JKR1(HPR) and the other JKTIP(HPL), measurement data
 * can be separated पढ़ो in IMM_RMS_L क्रम HSR and HSL after each measurement.
 * Thus, the measurement function has four states to complete whole sequence.
 * 1. Prepare state : Prepare the resource क्रम detection and transfer to HPR
 *     IMM stat to make JKR1(HPR) impedance measure.
 * 2. HPR IMM state : Read out orignal संकेत level of JKR1(HPR) and transfer
 *     to HPL IMM state to make JKTIP(HPL) impedance measure.
 * 3. HPL IMM state : Read out cross talk संकेत level of JKTIP(HPL) and
 *     transfer to IMM state to determine suppression sidetone gain.
 * 4. IMM state : Computes cross talk suppression sidetone gain with orignal
 *     and cross talk संकेत level. Apply this gain and then restore codec
 *     configuration. Then transfer to Done state क्रम ending.
 */
अटल व्योम nau8825_xtalk_measure(काष्ठा nau8825 *nau8825)
अणु
	u32 sidetone;

	चयन (nau8825->xtalk_state) अणु
	हाल NAU8825_XTALK_PREPARE:
		/* In prepare state, set up घड़ी, पूर्णांकrruption, DAC path, ADC
		 * path and cross talk detection parameters क्रम preparation.
		 */
		nau8825_xtalk_prepare(nau8825);
		msleep(280);
		/* Trigger right headphone impedance detection */
		nau8825->xtalk_state = NAU8825_XTALK_HPR_R2L;
		nau8825_xtalk_imm_start(nau8825, 0x00d2);
		अवरोध;
	हाल NAU8825_XTALK_HPR_R2L:
		/* In right headphone IMM state, पढ़ो out right headphone
		 * impedance measure result, and then start up left side.
		 */
		regmap_पढ़ो(nau8825->regmap, NAU8825_REG_IMM_RMS_L,
			&nau8825->imp_rms[NAU8825_XTALK_HPR_R2L]);
		dev_dbg(nau8825->dev, "HPR_R2L imm: %x\n",
			nau8825->imp_rms[NAU8825_XTALK_HPR_R2L]);
		/* Disable then re-enable IMM mode to update */
		nau8825_xtalk_imm_stop(nau8825);
		/* Trigger left headphone impedance detection */
		nau8825->xtalk_state = NAU8825_XTALK_HPL_R2L;
		nau8825_xtalk_imm_start(nau8825, 0x00ff);
		अवरोध;
	हाल NAU8825_XTALK_HPL_R2L:
		/* In left headphone IMM state, पढ़ो out left headphone
		 * impedance measure result, and delay some समय to रुको
		 * detection sine wave output finish. Then, we can calculate
		 * the cross talk suppresstion side tone according to the L/R
		 * headphone imedance.
		 */
		regmap_पढ़ो(nau8825->regmap, NAU8825_REG_IMM_RMS_L,
			&nau8825->imp_rms[NAU8825_XTALK_HPL_R2L]);
		dev_dbg(nau8825->dev, "HPL_R2L imm: %x\n",
			nau8825->imp_rms[NAU8825_XTALK_HPL_R2L]);
		nau8825_xtalk_imm_stop(nau8825);
		msleep(150);
		nau8825->xtalk_state = NAU8825_XTALK_IMM;
		अवरोध;
	हाल NAU8825_XTALK_IMM:
		/* In impedance measure state, the orignal and cross talk
		 * संकेत level vlues are पढ़ोy. The side tone gain is deter-
		 * mined with these संकेत level. After all, restore codec
		 * configuration.
		 */
		sidetone = nau8825_xtalk_sidetone(
			nau8825->imp_rms[NAU8825_XTALK_HPR_R2L],
			nau8825->imp_rms[NAU8825_XTALK_HPL_R2L]);
		dev_dbg(nau8825->dev, "cross talk sidetone: %x\n", sidetone);
		regmap_ग_लिखो(nau8825->regmap, NAU8825_REG_DAC_DGAIN_CTRL,
					(sidetone << 8) | sidetone);
		nau8825_xtalk_clean(nau8825, false);
		nau8825->xtalk_state = NAU8825_XTALK_DONE;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम nau8825_xtalk_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा nau8825 *nau8825 = container_of(
		work, काष्ठा nau8825, xtalk_work);

	nau8825_xtalk_measure(nau8825);
	/* To determine the cross talk side tone gain when reach
	 * the impedance measure state.
	 */
	अगर (nau8825->xtalk_state == NAU8825_XTALK_IMM)
		nau8825_xtalk_measure(nau8825);

	/* Delay jack report until cross talk detection process
	 * completed. It can aव्योम application to करो playback
	 * preparation beक्रमe cross talk detection is still working.
	 * Meanजबतक, the protection of the cross talk detection
	 * is released.
	 */
	अगर (nau8825->xtalk_state == NAU8825_XTALK_DONE) अणु
		snd_soc_jack_report(nau8825->jack, nau8825->xtalk_event,
				nau8825->xtalk_event_mask);
		nau8825_sema_release(nau8825);
		nau8825->xtalk_protect = false;
	पूर्ण
पूर्ण

अटल व्योम nau8825_xtalk_cancel(काष्ठा nau8825 *nau8825)
अणु
	/* If the crosstalk is eanbled and the process is on going,
	 * the driver क्रमces to cancel the crosstalk task and
	 * restores the configuration to original status.
	 */
	अगर (nau8825->xtalk_enable && nau8825->xtalk_state !=
		NAU8825_XTALK_DONE) अणु
		cancel_work_sync(&nau8825->xtalk_work);
		nau8825_xtalk_clean(nau8825, true);
	पूर्ण
	/* Reset parameters क्रम cross talk suppression function */
	nau8825_sema_reset(nau8825);
	nau8825->xtalk_state = NAU8825_XTALK_DONE;
	nau8825->xtalk_protect = false;
पूर्ण

अटल bool nau8825_पढ़ोable_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल NAU8825_REG_ENA_CTRL ... NAU8825_REG_FLL_VCO_RSV:
	हाल NAU8825_REG_HSD_CTRL ... NAU8825_REG_JACK_DET_CTRL:
	हाल NAU8825_REG_INTERRUPT_MASK ... NAU8825_REG_KEYDET_CTRL:
	हाल NAU8825_REG_VDET_THRESHOLD_1 ... NAU8825_REG_DACR_CTRL:
	हाल NAU8825_REG_ADC_DRC_KNEE_IP12 ... NAU8825_REG_ADC_DRC_ATKDCY:
	हाल NAU8825_REG_DAC_DRC_KNEE_IP12 ... NAU8825_REG_DAC_DRC_ATKDCY:
	हाल NAU8825_REG_IMM_MODE_CTRL ... NAU8825_REG_IMM_RMS_R:
	हाल NAU8825_REG_CLASSG_CTRL ... NAU8825_REG_OPT_EFUSE_CTRL:
	हाल NAU8825_REG_MISC_CTRL:
	हाल NAU8825_REG_I2C_DEVICE_ID ... NAU8825_REG_SARDOUT_RAM_STATUS:
	हाल NAU8825_REG_BIAS_ADJ:
	हाल NAU8825_REG_TRIM_SETTINGS ... NAU8825_REG_ANALOG_CONTROL_2:
	हाल NAU8825_REG_ANALOG_ADC_1 ... NAU8825_REG_MIC_BIAS:
	हाल NAU8825_REG_BOOST ... NAU8825_REG_FEPGA:
	हाल NAU8825_REG_POWER_UP_CONTROL ... NAU8825_REG_GENERAL_STATUS:
		वापस true;
	शेष:
		वापस false;
	पूर्ण

पूर्ण

अटल bool nau8825_ग_लिखोable_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल NAU8825_REG_RESET ... NAU8825_REG_FLL_VCO_RSV:
	हाल NAU8825_REG_HSD_CTRL ... NAU8825_REG_JACK_DET_CTRL:
	हाल NAU8825_REG_INTERRUPT_MASK:
	हाल NAU8825_REG_INT_CLR_KEY_STATUS ... NAU8825_REG_KEYDET_CTRL:
	हाल NAU8825_REG_VDET_THRESHOLD_1 ... NAU8825_REG_DACR_CTRL:
	हाल NAU8825_REG_ADC_DRC_KNEE_IP12 ... NAU8825_REG_ADC_DRC_ATKDCY:
	हाल NAU8825_REG_DAC_DRC_KNEE_IP12 ... NAU8825_REG_DAC_DRC_ATKDCY:
	हाल NAU8825_REG_IMM_MODE_CTRL:
	हाल NAU8825_REG_CLASSG_CTRL ... NAU8825_REG_OPT_EFUSE_CTRL:
	हाल NAU8825_REG_MISC_CTRL:
	हाल NAU8825_REG_BIAS_ADJ:
	हाल NAU8825_REG_TRIM_SETTINGS ... NAU8825_REG_ANALOG_CONTROL_2:
	हाल NAU8825_REG_ANALOG_ADC_1 ... NAU8825_REG_MIC_BIAS:
	हाल NAU8825_REG_BOOST ... NAU8825_REG_FEPGA:
	हाल NAU8825_REG_POWER_UP_CONTROL ... NAU8825_REG_CHARGE_PUMP:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल bool nau8825_अस्थिर_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल NAU8825_REG_RESET:
	हाल NAU8825_REG_IRQ_STATUS:
	हाल NAU8825_REG_INT_CLR_KEY_STATUS:
	हाल NAU8825_REG_IMM_RMS_L:
	हाल NAU8825_REG_IMM_RMS_R:
	हाल NAU8825_REG_I2C_DEVICE_ID:
	हाल NAU8825_REG_SARDOUT_RAM_STATUS:
	हाल NAU8825_REG_CHARGE_PUMP_INPUT_READ:
	हाल NAU8825_REG_GENERAL_STATUS:
	हाल NAU8825_REG_BIQ_CTRL ... NAU8825_REG_BIQ_COF10:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल पूर्णांक nau8825_adc_event(काष्ठा snd_soc_dapm_widget *w,
		काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	काष्ठा snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	काष्ठा nau8825 *nau8825 = snd_soc_component_get_drvdata(component);

	चयन (event) अणु
	हाल SND_SOC_DAPM_POST_PMU:
		msleep(125);
		regmap_update_bits(nau8825->regmap, NAU8825_REG_ENA_CTRL,
			NAU8825_ENABLE_ADC, NAU8825_ENABLE_ADC);
		अवरोध;
	हाल SND_SOC_DAPM_POST_PMD:
		अगर (!nau8825->irq)
			regmap_update_bits(nau8825->regmap,
				NAU8825_REG_ENA_CTRL, NAU8825_ENABLE_ADC, 0);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक nau8825_pump_event(काष्ठा snd_soc_dapm_widget *w,
	काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	काष्ठा snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	काष्ठा nau8825 *nau8825 = snd_soc_component_get_drvdata(component);

	चयन (event) अणु
	हाल SND_SOC_DAPM_POST_PMU:
		/* Prevent startup click by letting अक्षरge pump to ramp up */
		msleep(10);
		regmap_update_bits(nau8825->regmap, NAU8825_REG_CHARGE_PUMP,
			NAU8825_JAMNODCLOW, NAU8825_JAMNODCLOW);
		अवरोध;
	हाल SND_SOC_DAPM_PRE_PMD:
		regmap_update_bits(nau8825->regmap, NAU8825_REG_CHARGE_PUMP,
			NAU8825_JAMNODCLOW, 0);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक nau8825_output_dac_event(काष्ठा snd_soc_dapm_widget *w,
	काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	काष्ठा snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	काष्ठा nau8825 *nau8825 = snd_soc_component_get_drvdata(component);

	चयन (event) अणु
	हाल SND_SOC_DAPM_PRE_PMU:
		/* Disables the TESTDAC to let DAC संकेत pass through. */
		regmap_update_bits(nau8825->regmap, NAU8825_REG_BIAS_ADJ,
			NAU8825_BIAS_TESTDAC_EN, 0);
		अवरोध;
	हाल SND_SOC_DAPM_POST_PMD:
		regmap_update_bits(nau8825->regmap, NAU8825_REG_BIAS_ADJ,
			NAU8825_BIAS_TESTDAC_EN, NAU8825_BIAS_TESTDAC_EN);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक nau8825_biq_coeff_get(काष्ठा snd_kcontrol *kcontrol,
				     काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component = snd_kcontrol_chip(kcontrol);
	काष्ठा soc_bytes_ext *params = (व्योम *)kcontrol->निजी_value;

	अगर (!component->regmap)
		वापस -EINVAL;

	regmap_raw_पढ़ो(component->regmap, NAU8825_REG_BIQ_COF1,
		ucontrol->value.bytes.data, params->max);
	वापस 0;
पूर्ण

अटल पूर्णांक nau8825_biq_coeff_put(काष्ठा snd_kcontrol *kcontrol,
				     काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component = snd_kcontrol_chip(kcontrol);
	काष्ठा soc_bytes_ext *params = (व्योम *)kcontrol->निजी_value;
	व्योम *data;

	अगर (!component->regmap)
		वापस -EINVAL;

	data = kmemdup(ucontrol->value.bytes.data,
		params->max, GFP_KERNEL | GFP_DMA);
	अगर (!data)
		वापस -ENOMEM;

	regmap_update_bits(component->regmap, NAU8825_REG_BIQ_CTRL,
		NAU8825_BIQ_WRT_EN, 0);
	regmap_raw_ग_लिखो(component->regmap, NAU8825_REG_BIQ_COF1,
		data, params->max);
	regmap_update_bits(component->regmap, NAU8825_REG_BIQ_CTRL,
		NAU8825_BIQ_WRT_EN, NAU8825_BIQ_WRT_EN);

	kमुक्त(data);
	वापस 0;
पूर्ण

अटल स्थिर अक्षर * स्थिर nau8825_biq_path[] = अणु
	"ADC", "DAC"
पूर्ण;

अटल स्थिर काष्ठा soc_क्रमागत nau8825_biq_path_क्रमागत =
	SOC_ENUM_SINGLE(NAU8825_REG_BIQ_CTRL, NAU8825_BIQ_PATH_SFT,
		ARRAY_SIZE(nau8825_biq_path), nau8825_biq_path);

अटल स्थिर अक्षर * स्थिर nau8825_adc_decimation[] = अणु
	"32", "64", "128", "256"
पूर्ण;

अटल स्थिर काष्ठा soc_क्रमागत nau8825_adc_decimation_क्रमागत =
	SOC_ENUM_SINGLE(NAU8825_REG_ADC_RATE, NAU8825_ADC_SYNC_DOWN_SFT,
		ARRAY_SIZE(nau8825_adc_decimation), nau8825_adc_decimation);

अटल स्थिर अक्षर * स्थिर nau8825_dac_oversampl[] = अणु
	"64", "256", "128", "", "32"
पूर्ण;

अटल स्थिर काष्ठा soc_क्रमागत nau8825_dac_oversampl_क्रमागत =
	SOC_ENUM_SINGLE(NAU8825_REG_DAC_CTRL1, NAU8825_DAC_OVERSAMPLE_SFT,
		ARRAY_SIZE(nau8825_dac_oversampl), nau8825_dac_oversampl);

अटल स्थिर DECLARE_TLV_DB_MINMAX_MUTE(adc_vol_tlv, -10300, 2400);
अटल स्थिर DECLARE_TLV_DB_MINMAX_MUTE(sidetone_vol_tlv, -4200, 0);
अटल स्थिर DECLARE_TLV_DB_MINMAX(dac_vol_tlv, -5400, 0);
अटल स्थिर DECLARE_TLV_DB_MINMAX(fepga_gain_tlv, -100, 3600);
अटल स्थिर DECLARE_TLV_DB_MINMAX_MUTE(crosstalk_vol_tlv, -9600, 2400);

अटल स्थिर काष्ठा snd_kcontrol_new nau8825_controls[] = अणु
	SOC_SINGLE_TLV("Mic Volume", NAU8825_REG_ADC_DGAIN_CTRL,
		0, 0xff, 0, adc_vol_tlv),
	SOC_DOUBLE_TLV("Headphone Bypass Volume", NAU8825_REG_ADC_DGAIN_CTRL,
		12, 8, 0x0f, 0, sidetone_vol_tlv),
	SOC_DOUBLE_TLV("Headphone Volume", NAU8825_REG_HSVOL_CTRL,
		6, 0, 0x3f, 1, dac_vol_tlv),
	SOC_SINGLE_TLV("Frontend PGA Volume", NAU8825_REG_POWER_UP_CONTROL,
		8, 37, 0, fepga_gain_tlv),
	SOC_DOUBLE_TLV("Headphone Crosstalk Volume", NAU8825_REG_DAC_DGAIN_CTRL,
		0, 8, 0xff, 0, crosstalk_vol_tlv),

	SOC_ENUM("ADC Decimation Rate", nau8825_adc_decimation_क्रमागत),
	SOC_ENUM("DAC Oversampling Rate", nau8825_dac_oversampl_क्रमागत),
	/* programmable biquad filter */
	SOC_ENUM("BIQ Path Select", nau8825_biq_path_क्रमागत),
	SND_SOC_BYTES_EXT("BIQ Coefficients", 20,
		  nau8825_biq_coeff_get, nau8825_biq_coeff_put),
पूर्ण;

/* DAC Mux 0x33[9] and 0x34[9] */
अटल स्थिर अक्षर * स्थिर nau8825_dac_src[] = अणु
	"DACL", "DACR",
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(
	nau8825_dacl_क्रमागत, NAU8825_REG_DACL_CTRL,
	NAU8825_DACL_CH_SEL_SFT, nau8825_dac_src);

अटल SOC_ENUM_SINGLE_DECL(
	nau8825_dacr_क्रमागत, NAU8825_REG_DACR_CTRL,
	NAU8825_DACR_CH_SEL_SFT, nau8825_dac_src);

अटल स्थिर काष्ठा snd_kcontrol_new nau8825_dacl_mux =
	SOC_DAPM_ENUM("DACL Source", nau8825_dacl_क्रमागत);

अटल स्थिर काष्ठा snd_kcontrol_new nau8825_dacr_mux =
	SOC_DAPM_ENUM("DACR Source", nau8825_dacr_क्रमागत);


अटल स्थिर काष्ठा snd_soc_dapm_widget nau8825_dapm_widमाला_लो[] = अणु
	SND_SOC_DAPM_AIF_OUT("AIFTX", "Capture", 0, NAU8825_REG_I2S_PCM_CTRL2,
		15, 1),

	SND_SOC_DAPM_INPUT("MIC"),
	SND_SOC_DAPM_MICBIAS("MICBIAS", NAU8825_REG_MIC_BIAS, 8, 0),

	SND_SOC_DAPM_PGA("Frontend PGA", NAU8825_REG_POWER_UP_CONTROL, 14, 0,
		शून्य, 0),

	SND_SOC_DAPM_ADC_E("ADC", शून्य, SND_SOC_NOPM, 0, 0,
		nau8825_adc_event, SND_SOC_DAPM_POST_PMU |
		SND_SOC_DAPM_POST_PMD),
	SND_SOC_DAPM_SUPPLY("ADC Clock", NAU8825_REG_ENA_CTRL, 7, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("ADC Power", NAU8825_REG_ANALOG_ADC_2, 6, 0, शून्य,
		0),

	/* ADC क्रम button press detection. A dapm supply widget is used to
	 * prevent dapm_घातer_widमाला_लो keeping the codec at SND_SOC_BIAS_ON
	 * during suspend.
	 */
	SND_SOC_DAPM_SUPPLY("SAR", NAU8825_REG_SAR_CTRL,
		NAU8825_SAR_ADC_EN_SFT, 0, शून्य, 0),

	SND_SOC_DAPM_PGA_S("ADACL", 2, NAU8825_REG_RDAC, 12, 0, शून्य, 0),
	SND_SOC_DAPM_PGA_S("ADACR", 2, NAU8825_REG_RDAC, 13, 0, शून्य, 0),
	SND_SOC_DAPM_PGA_S("ADACL Clock", 3, NAU8825_REG_RDAC, 8, 0, शून्य, 0),
	SND_SOC_DAPM_PGA_S("ADACR Clock", 3, NAU8825_REG_RDAC, 9, 0, शून्य, 0),

	SND_SOC_DAPM_DAC("DDACR", शून्य, NAU8825_REG_ENA_CTRL,
		NAU8825_ENABLE_DACR_SFT, 0),
	SND_SOC_DAPM_DAC("DDACL", शून्य, NAU8825_REG_ENA_CTRL,
		NAU8825_ENABLE_DACL_SFT, 0),
	SND_SOC_DAPM_SUPPLY("DDAC Clock", NAU8825_REG_ENA_CTRL, 6, 0, शून्य, 0),

	SND_SOC_DAPM_MUX("DACL Mux", SND_SOC_NOPM, 0, 0, &nau8825_dacl_mux),
	SND_SOC_DAPM_MUX("DACR Mux", SND_SOC_NOPM, 0, 0, &nau8825_dacr_mux),

	SND_SOC_DAPM_PGA_S("HP amp L", 0,
		NAU8825_REG_CLASSG_CTRL, 1, 0, शून्य, 0),
	SND_SOC_DAPM_PGA_S("HP amp R", 0,
		NAU8825_REG_CLASSG_CTRL, 2, 0, शून्य, 0),

	SND_SOC_DAPM_PGA_S("Charge Pump", 1, NAU8825_REG_CHARGE_PUMP, 5, 0,
		nau8825_pump_event, SND_SOC_DAPM_POST_PMU |
		SND_SOC_DAPM_PRE_PMD),

	SND_SOC_DAPM_PGA_S("Output Driver R Stage 1", 4,
		NAU8825_REG_POWER_UP_CONTROL, 5, 0, शून्य, 0),
	SND_SOC_DAPM_PGA_S("Output Driver L Stage 1", 4,
		NAU8825_REG_POWER_UP_CONTROL, 4, 0, शून्य, 0),
	SND_SOC_DAPM_PGA_S("Output Driver R Stage 2", 5,
		NAU8825_REG_POWER_UP_CONTROL, 3, 0, शून्य, 0),
	SND_SOC_DAPM_PGA_S("Output Driver L Stage 2", 5,
		NAU8825_REG_POWER_UP_CONTROL, 2, 0, शून्य, 0),
	SND_SOC_DAPM_PGA_S("Output Driver R Stage 3", 6,
		NAU8825_REG_POWER_UP_CONTROL, 1, 0, शून्य, 0),
	SND_SOC_DAPM_PGA_S("Output Driver L Stage 3", 6,
		NAU8825_REG_POWER_UP_CONTROL, 0, 0, शून्य, 0),

	SND_SOC_DAPM_PGA_S("Output DACL", 7,
		NAU8825_REG_CHARGE_PUMP, 8, 1, nau8825_output_dac_event,
		SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMD),
	SND_SOC_DAPM_PGA_S("Output DACR", 7,
		NAU8825_REG_CHARGE_PUMP, 9, 1, nau8825_output_dac_event,
		SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMD),

	/* HPOL/R are ungrounded by disabling 16 Ohm pull-करोwns on playback */
	SND_SOC_DAPM_PGA_S("HPOL Pulldown", 8,
		NAU8825_REG_HSD_CTRL, 0, 1, शून्य, 0),
	SND_SOC_DAPM_PGA_S("HPOR Pulldown", 8,
		NAU8825_REG_HSD_CTRL, 1, 1, शून्य, 0),

	/* High current HPOL/R boost driver */
	SND_SOC_DAPM_PGA_S("HP Boost Driver", 9,
		NAU8825_REG_BOOST, 9, 1, शून्य, 0),

	/* Class G operation control*/
	SND_SOC_DAPM_PGA_S("Class G", 10,
		NAU8825_REG_CLASSG_CTRL, 0, 0, शून्य, 0),

	SND_SOC_DAPM_OUTPUT("HPOL"),
	SND_SOC_DAPM_OUTPUT("HPOR"),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route nau8825_dapm_routes[] = अणु
	अणु"Frontend PGA", शून्य, "MIC"पूर्ण,
	अणु"ADC", शून्य, "Frontend PGA"पूर्ण,
	अणु"ADC", शून्य, "ADC Clock"पूर्ण,
	अणु"ADC", शून्य, "ADC Power"पूर्ण,
	अणु"AIFTX", शून्य, "ADC"पूर्ण,

	अणु"DDACL", शून्य, "Playback"पूर्ण,
	अणु"DDACR", शून्य, "Playback"पूर्ण,
	अणु"DDACL", शून्य, "DDAC Clock"पूर्ण,
	अणु"DDACR", शून्य, "DDAC Clock"पूर्ण,
	अणु"DACL Mux", "DACL", "DDACL"पूर्ण,
	अणु"DACL Mux", "DACR", "DDACR"पूर्ण,
	अणु"DACR Mux", "DACL", "DDACL"पूर्ण,
	अणु"DACR Mux", "DACR", "DDACR"पूर्ण,
	अणु"HP amp L", शून्य, "DACL Mux"पूर्ण,
	अणु"HP amp R", शून्य, "DACR Mux"पूर्ण,
	अणु"Charge Pump", शून्य, "HP amp L"पूर्ण,
	अणु"Charge Pump", शून्य, "HP amp R"पूर्ण,
	अणु"ADACL", शून्य, "Charge Pump"पूर्ण,
	अणु"ADACR", शून्य, "Charge Pump"पूर्ण,
	अणु"ADACL Clock", शून्य, "ADACL"पूर्ण,
	अणु"ADACR Clock", शून्य, "ADACR"पूर्ण,
	अणु"Output Driver L Stage 1", शून्य, "ADACL Clock"पूर्ण,
	अणु"Output Driver R Stage 1", शून्य, "ADACR Clock"पूर्ण,
	अणु"Output Driver L Stage 2", शून्य, "Output Driver L Stage 1"पूर्ण,
	अणु"Output Driver R Stage 2", शून्य, "Output Driver R Stage 1"पूर्ण,
	अणु"Output Driver L Stage 3", शून्य, "Output Driver L Stage 2"पूर्ण,
	अणु"Output Driver R Stage 3", शून्य, "Output Driver R Stage 2"पूर्ण,
	अणु"Output DACL", शून्य, "Output Driver L Stage 3"पूर्ण,
	अणु"Output DACR", शून्य, "Output Driver R Stage 3"पूर्ण,
	अणु"HPOL Pulldown", शून्य, "Output DACL"पूर्ण,
	अणु"HPOR Pulldown", शून्य, "Output DACR"पूर्ण,
	अणु"HP Boost Driver", शून्य, "HPOL Pulldown"पूर्ण,
	अणु"HP Boost Driver", शून्य, "HPOR Pulldown"पूर्ण,
	अणु"Class G", शून्य, "HP Boost Driver"पूर्ण,
	अणु"HPOL", शून्य, "Class G"पूर्ण,
	अणु"HPOR", शून्य, "Class G"पूर्ण,
पूर्ण;

अटल पूर्णांक nau8825_घड़ी_check(काष्ठा nau8825 *nau8825,
	पूर्णांक stream, पूर्णांक rate, पूर्णांक osr)
अणु
	पूर्णांक osrate;

	अगर (stream == SNDRV_PCM_STREAM_PLAYBACK) अणु
		अगर (osr >= ARRAY_SIZE(osr_dac_sel))
			वापस -EINVAL;
		osrate = osr_dac_sel[osr].osr;
	पूर्ण अन्यथा अणु
		अगर (osr >= ARRAY_SIZE(osr_adc_sel))
			वापस -EINVAL;
		osrate = osr_adc_sel[osr].osr;
	पूर्ण

	अगर (!osrate || rate * osr > CLK_DA_AD_MAX) अणु
		dev_err(nau8825->dev, "exceed the maximum frequency of CLK_ADC or CLK_DAC\n");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक nau8825_hw_params(काष्ठा snd_pcm_substream *substream,
				काष्ठा snd_pcm_hw_params *params,
				काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा nau8825 *nau8825 = snd_soc_component_get_drvdata(component);
	अचिन्हित पूर्णांक val_len = 0, osr, ctrl_val, bclk_fs, bclk_भाग;

	nau8825_sema_acquire(nau8825, 3 * HZ);

	/* CLK_DAC or CLK_ADC = OSR * FS
	 * DAC or ADC घड़ी frequency is defined as Over Sampling Rate (OSR)
	 * multiplied by the audio sample rate (Fs). Note that the OSR and Fs
	 * values must be selected such that the maximum frequency is less
	 * than 6.144 MHz.
	 */
	अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK) अणु
		regmap_पढ़ो(nau8825->regmap, NAU8825_REG_DAC_CTRL1, &osr);
		osr &= NAU8825_DAC_OVERSAMPLE_MASK;
		अगर (nau8825_घड़ी_check(nau8825, substream->stream,
			params_rate(params), osr)) अणु
			nau8825_sema_release(nau8825);
			वापस -EINVAL;
		पूर्ण
		regmap_update_bits(nau8825->regmap, NAU8825_REG_CLK_DIVIDER,
			NAU8825_CLK_DAC_SRC_MASK,
			osr_dac_sel[osr].clk_src << NAU8825_CLK_DAC_SRC_SFT);
	पूर्ण अन्यथा अणु
		regmap_पढ़ो(nau8825->regmap, NAU8825_REG_ADC_RATE, &osr);
		osr &= NAU8825_ADC_SYNC_DOWN_MASK;
		अगर (nau8825_घड़ी_check(nau8825, substream->stream,
			params_rate(params), osr)) अणु
			nau8825_sema_release(nau8825);
			वापस -EINVAL;
		पूर्ण
		regmap_update_bits(nau8825->regmap, NAU8825_REG_CLK_DIVIDER,
			NAU8825_CLK_ADC_SRC_MASK,
			osr_adc_sel[osr].clk_src << NAU8825_CLK_ADC_SRC_SFT);
	पूर्ण

	/* make BCLK and LRC भागde configuration अगर the codec as master. */
	regmap_पढ़ो(nau8825->regmap, NAU8825_REG_I2S_PCM_CTRL2, &ctrl_val);
	अगर (ctrl_val & NAU8825_I2S_MS_MASTER) अणु
		/* get the bclk and fs ratio */
		bclk_fs = snd_soc_params_to_bclk(params) / params_rate(params);
		अगर (bclk_fs <= 32)
			bclk_भाग = 2;
		अन्यथा अगर (bclk_fs <= 64)
			bclk_भाग = 1;
		अन्यथा अगर (bclk_fs <= 128)
			bclk_भाग = 0;
		अन्यथा अणु
			nau8825_sema_release(nau8825);
			वापस -EINVAL;
		पूर्ण
		regmap_update_bits(nau8825->regmap, NAU8825_REG_I2S_PCM_CTRL2,
			NAU8825_I2S_LRC_DIV_MASK | NAU8825_I2S_BLK_DIV_MASK,
			((bclk_भाग + 1) << NAU8825_I2S_LRC_DIV_SFT) | bclk_भाग);
	पूर्ण

	चयन (params_width(params)) अणु
	हाल 16:
		val_len |= NAU8825_I2S_DL_16;
		अवरोध;
	हाल 20:
		val_len |= NAU8825_I2S_DL_20;
		अवरोध;
	हाल 24:
		val_len |= NAU8825_I2S_DL_24;
		अवरोध;
	हाल 32:
		val_len |= NAU8825_I2S_DL_32;
		अवरोध;
	शेष:
		nau8825_sema_release(nau8825);
		वापस -EINVAL;
	पूर्ण

	regmap_update_bits(nau8825->regmap, NAU8825_REG_I2S_PCM_CTRL1,
		NAU8825_I2S_DL_MASK, val_len);

	/* Release the semaphore. */
	nau8825_sema_release(nau8825);

	वापस 0;
पूर्ण

अटल पूर्णांक nau8825_set_dai_fmt(काष्ठा snd_soc_dai *codec_dai, अचिन्हित पूर्णांक fmt)
अणु
	काष्ठा snd_soc_component *component = codec_dai->component;
	काष्ठा nau8825 *nau8825 = snd_soc_component_get_drvdata(component);
	अचिन्हित पूर्णांक ctrl1_val = 0, ctrl2_val = 0;

	चयन (fmt & SND_SOC_DAIFMT_MASTER_MASK) अणु
	हाल SND_SOC_DAIFMT_CBM_CFM:
		ctrl2_val |= NAU8825_I2S_MS_MASTER;
		अवरोध;
	हाल SND_SOC_DAIFMT_CBS_CFS:
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	चयन (fmt & SND_SOC_DAIFMT_INV_MASK) अणु
	हाल SND_SOC_DAIFMT_NB_NF:
		अवरोध;
	हाल SND_SOC_DAIFMT_IB_NF:
		ctrl1_val |= NAU8825_I2S_BP_INV;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	चयन (fmt & SND_SOC_DAIFMT_FORMAT_MASK) अणु
	हाल SND_SOC_DAIFMT_I2S:
		ctrl1_val |= NAU8825_I2S_DF_I2S;
		अवरोध;
	हाल SND_SOC_DAIFMT_LEFT_J:
		ctrl1_val |= NAU8825_I2S_DF_LEFT;
		अवरोध;
	हाल SND_SOC_DAIFMT_RIGHT_J:
		ctrl1_val |= NAU8825_I2S_DF_RIGTH;
		अवरोध;
	हाल SND_SOC_DAIFMT_DSP_A:
		ctrl1_val |= NAU8825_I2S_DF_PCM_AB;
		अवरोध;
	हाल SND_SOC_DAIFMT_DSP_B:
		ctrl1_val |= NAU8825_I2S_DF_PCM_AB;
		ctrl1_val |= NAU8825_I2S_PCMB_EN;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	nau8825_sema_acquire(nau8825, 3 * HZ);

	regmap_update_bits(nau8825->regmap, NAU8825_REG_I2S_PCM_CTRL1,
		NAU8825_I2S_DL_MASK | NAU8825_I2S_DF_MASK |
		NAU8825_I2S_BP_MASK | NAU8825_I2S_PCMB_MASK,
		ctrl1_val);
	regmap_update_bits(nau8825->regmap, NAU8825_REG_I2S_PCM_CTRL2,
		NAU8825_I2S_MS_MASK, ctrl2_val);

	/* Release the semaphore. */
	nau8825_sema_release(nau8825);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_dai_ops nau8825_dai_ops = अणु
	.hw_params	= nau8825_hw_params,
	.set_fmt	= nau8825_set_dai_fmt,
पूर्ण;

#घोषणा NAU8825_RATES	SNDRV_PCM_RATE_8000_192000
#घोषणा NAU8825_FORMATS	(SNDRV_PCM_FMTBIT_S16_LE | SNDRV_PCM_FMTBIT_S20_3LE \
			 | SNDRV_PCM_FMTBIT_S24_3LE | SNDRV_PCM_FMTBIT_S32_LE)

अटल काष्ठा snd_soc_dai_driver nau8825_dai = अणु
	.name = "nau8825-hifi",
	.playback = अणु
		.stream_name	 = "Playback",
		.channels_min	 = 1,
		.channels_max	 = 2,
		.rates		 = NAU8825_RATES,
		.क्रमmats	 = NAU8825_FORMATS,
	पूर्ण,
	.capture = अणु
		.stream_name	 = "Capture",
		.channels_min	 = 1,
		.channels_max	 = 1,
		.rates		 = NAU8825_RATES,
		.क्रमmats	 = NAU8825_FORMATS,
	पूर्ण,
	.ops = &nau8825_dai_ops,
पूर्ण;

/**
 * nau8825_enable_jack_detect - Specअगरy a jack क्रम event reporting
 *
 * @component:  component to रेजिस्टर the jack with
 * @jack: jack to use to report headset and button events on
 *
 * After this function has been called the headset insert/हटाओ and button
 * events will be routed to the given jack.  Jack can be null to stop
 * reporting.
 */
पूर्णांक nau8825_enable_jack_detect(काष्ठा snd_soc_component *component,
				काष्ठा snd_soc_jack *jack)
अणु
	काष्ठा nau8825 *nau8825 = snd_soc_component_get_drvdata(component);
	काष्ठा regmap *regmap = nau8825->regmap;

	nau8825->jack = jack;

	/* Ground HP Outमाला_दो[1:0], needed क्रम headset स्वतः detection
	 * Enable Automatic Mic/Gnd चयनing पढ़ोing on insert पूर्णांकerrupt[6]
	 */
	regmap_update_bits(regmap, NAU8825_REG_HSD_CTRL,
		NAU8825_HSD_AUTO_MODE | NAU8825_SPKR_DWN1R | NAU8825_SPKR_DWN1L,
		NAU8825_HSD_AUTO_MODE | NAU8825_SPKR_DWN1R | NAU8825_SPKR_DWN1L);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(nau8825_enable_jack_detect);


अटल bool nau8825_is_jack_inserted(काष्ठा regmap *regmap)
अणु
	bool active_high, is_high;
	पूर्णांक status, jkdet;

	regmap_पढ़ो(regmap, NAU8825_REG_JACK_DET_CTRL, &jkdet);
	active_high = jkdet & NAU8825_JACK_POLARITY;
	regmap_पढ़ो(regmap, NAU8825_REG_I2C_DEVICE_ID, &status);
	is_high = status & NAU8825_GPIO2JD1;
	/* वापस jack connection status according to jack insertion logic
	 * active high or active low.
	 */
	वापस active_high == is_high;
पूर्ण

अटल व्योम nau8825_restart_jack_detection(काष्ठा regmap *regmap)
अणु
	/* this will restart the entire jack detection process including MIC/GND
	 * चयनing and create पूर्णांकerrupts. We have to go from 0 to 1 and back
	 * to 0 to restart.
	 */
	regmap_update_bits(regmap, NAU8825_REG_JACK_DET_CTRL,
		NAU8825_JACK_DET_RESTART, NAU8825_JACK_DET_RESTART);
	regmap_update_bits(regmap, NAU8825_REG_JACK_DET_CTRL,
		NAU8825_JACK_DET_RESTART, 0);
पूर्ण

अटल व्योम nau8825_पूर्णांक_status_clear_all(काष्ठा regmap *regmap)
अणु
	पूर्णांक active_irq, clear_irq, i;

	/* Reset the पूर्णांकrruption status from righपंचांगost bit अगर the corres-
	 * ponding irq event occurs.
	 */
	regmap_पढ़ो(regmap, NAU8825_REG_IRQ_STATUS, &active_irq);
	क्रम (i = 0; i < NAU8825_REG_DATA_LEN; i++) अणु
		clear_irq = (0x1 << i);
		अगर (active_irq & clear_irq)
			regmap_ग_लिखो(regmap,
				NAU8825_REG_INT_CLR_KEY_STATUS, clear_irq);
	पूर्ण
पूर्ण

अटल व्योम nau8825_eject_jack(काष्ठा nau8825 *nau8825)
अणु
	काष्ठा snd_soc_dapm_context *dapm = nau8825->dapm;
	काष्ठा regmap *regmap = nau8825->regmap;

	/* Force to cancel the cross talk detection process */
	nau8825_xtalk_cancel(nau8825);

	snd_soc_dapm_disable_pin(dapm, "SAR");
	snd_soc_dapm_disable_pin(dapm, "MICBIAS");
	/* Detach 2kOhm Resistors from MICBIAS to MICGND1/2 */
	regmap_update_bits(regmap, NAU8825_REG_MIC_BIAS,
		NAU8825_MICBIAS_JKSLV | NAU8825_MICBIAS_JKR2, 0);
	/* ground HPL/HPR, MICGRND1/2 */
	regmap_update_bits(regmap, NAU8825_REG_HSD_CTRL, 0xf, 0xf);

	snd_soc_dapm_sync(dapm);

	/* Clear all पूर्णांकerruption status */
	nau8825_पूर्णांक_status_clear_all(regmap);

	/* Enable the insertion पूर्णांकerruption, disable the ejection पूर्णांकer-
	 * ruption, and then bypass de-bounce circuit.
	 */
	regmap_update_bits(regmap, NAU8825_REG_INTERRUPT_DIS_CTRL,
		NAU8825_IRQ_EJECT_DIS | NAU8825_IRQ_INSERT_DIS,
		NAU8825_IRQ_EJECT_DIS);
	regmap_update_bits(regmap, NAU8825_REG_INTERRUPT_MASK,
		NAU8825_IRQ_OUTPUT_EN | NAU8825_IRQ_EJECT_EN |
		NAU8825_IRQ_HEADSET_COMPLETE_EN | NAU8825_IRQ_INSERT_EN,
		NAU8825_IRQ_OUTPUT_EN | NAU8825_IRQ_EJECT_EN |
		NAU8825_IRQ_HEADSET_COMPLETE_EN);
	regmap_update_bits(regmap, NAU8825_REG_JACK_DET_CTRL,
		NAU8825_JACK_DET_DB_BYPASS, NAU8825_JACK_DET_DB_BYPASS);

	/* Disable ADC needed क्रम पूर्णांकerruptions at auकरो mode */
	regmap_update_bits(regmap, NAU8825_REG_ENA_CTRL,
		NAU8825_ENABLE_ADC, 0);

	/* Close घड़ी क्रम jack type detection at manual mode */
	nau8825_configure_sysclk(nau8825, NAU8825_CLK_DIS, 0);
पूर्ण

/* Enable auकरो mode पूर्णांकerruptions with पूर्णांकernal घड़ी. */
अटल व्योम nau8825_setup_स्वतः_irq(काष्ठा nau8825 *nau8825)
अणु
	काष्ठा regmap *regmap = nau8825->regmap;

	/* Enable headset jack type detection complete पूर्णांकerruption and
	 * jack ejection पूर्णांकerruption.
	 */
	regmap_update_bits(regmap, NAU8825_REG_INTERRUPT_MASK,
		NAU8825_IRQ_HEADSET_COMPLETE_EN | NAU8825_IRQ_EJECT_EN, 0);

	/* Enable पूर्णांकernal VCO needed क्रम पूर्णांकerruptions */
	nau8825_configure_sysclk(nau8825, NAU8825_CLK_INTERNAL, 0);

	/* Enable ADC needed क्रम पूर्णांकerruptions */
	regmap_update_bits(regmap, NAU8825_REG_ENA_CTRL,
		NAU8825_ENABLE_ADC, NAU8825_ENABLE_ADC);

	/* Chip needs one FSCLK cycle in order to generate पूर्णांकerruptions,
	 * as we cannot guarantee one will be provided by the प्रणाली. Turning
	 * master mode on then off enables us to generate that FSCLK cycle
	 * with a minimum of contention on the घड़ी bus.
	 */
	regmap_update_bits(regmap, NAU8825_REG_I2S_PCM_CTRL2,
		NAU8825_I2S_MS_MASK, NAU8825_I2S_MS_MASTER);
	regmap_update_bits(regmap, NAU8825_REG_I2S_PCM_CTRL2,
		NAU8825_I2S_MS_MASK, NAU8825_I2S_MS_SLAVE);

	/* Not bypass de-bounce circuit */
	regmap_update_bits(regmap, NAU8825_REG_JACK_DET_CTRL,
		NAU8825_JACK_DET_DB_BYPASS, 0);

	/* Unmask all पूर्णांकerruptions */
	regmap_ग_लिखो(regmap, NAU8825_REG_INTERRUPT_DIS_CTRL, 0);

	/* Restart the jack detection process at स्वतः mode */
	nau8825_restart_jack_detection(regmap);
पूर्ण

अटल पूर्णांक nau8825_button_decode(पूर्णांक value)
अणु
	पूर्णांक buttons = 0;

	/* The chip supports up to 8 buttons, but ALSA defines only 6 buttons */
	अगर (value & BIT(0))
		buttons |= SND_JACK_BTN_0;
	अगर (value & BIT(1))
		buttons |= SND_JACK_BTN_1;
	अगर (value & BIT(2))
		buttons |= SND_JACK_BTN_2;
	अगर (value & BIT(3))
		buttons |= SND_JACK_BTN_3;
	अगर (value & BIT(4))
		buttons |= SND_JACK_BTN_4;
	अगर (value & BIT(5))
		buttons |= SND_JACK_BTN_5;

	वापस buttons;
पूर्ण

अटल पूर्णांक nau8825_jack_insert(काष्ठा nau8825 *nau8825)
अणु
	काष्ठा regmap *regmap = nau8825->regmap;
	काष्ठा snd_soc_dapm_context *dapm = nau8825->dapm;
	पूर्णांक jack_status_reg, mic_detected;
	पूर्णांक type = 0;

	regmap_पढ़ो(regmap, NAU8825_REG_GENERAL_STATUS, &jack_status_reg);
	mic_detected = (jack_status_reg >> 10) & 3;
	/* The JKSLV and JKR2 all detected in high impedance headset */
	अगर (mic_detected == 0x3)
		nau8825->high_imped = true;
	अन्यथा
		nau8825->high_imped = false;

	चयन (mic_detected) अणु
	हाल 0:
		/* no mic */
		type = SND_JACK_HEADPHONE;
		अवरोध;
	हाल 1:
		dev_dbg(nau8825->dev, "OMTP (micgnd1) mic connected\n");
		type = SND_JACK_HEADSET;

		/* Unground MICGND1 */
		regmap_update_bits(regmap, NAU8825_REG_HSD_CTRL, 3 << 2,
			1 << 2);
		/* Attach 2kOhm Resistor from MICBIAS to MICGND1 */
		regmap_update_bits(regmap, NAU8825_REG_MIC_BIAS,
			NAU8825_MICBIAS_JKSLV | NAU8825_MICBIAS_JKR2,
			NAU8825_MICBIAS_JKR2);
		/* Attach SARADC to MICGND1 */
		regmap_update_bits(regmap, NAU8825_REG_SAR_CTRL,
			NAU8825_SAR_INPUT_MASK,
			NAU8825_SAR_INPUT_JKR2);

		snd_soc_dapm_क्रमce_enable_pin(dapm, "MICBIAS");
		snd_soc_dapm_क्रमce_enable_pin(dapm, "SAR");
		snd_soc_dapm_sync(dapm);
		अवरोध;
	हाल 2:
		dev_dbg(nau8825->dev, "CTIA (micgnd2) mic connected\n");
		type = SND_JACK_HEADSET;

		/* Unground MICGND2 */
		regmap_update_bits(regmap, NAU8825_REG_HSD_CTRL, 3 << 2,
			2 << 2);
		/* Attach 2kOhm Resistor from MICBIAS to MICGND2 */
		regmap_update_bits(regmap, NAU8825_REG_MIC_BIAS,
			NAU8825_MICBIAS_JKSLV | NAU8825_MICBIAS_JKR2,
			NAU8825_MICBIAS_JKSLV);
		/* Attach SARADC to MICGND2 */
		regmap_update_bits(regmap, NAU8825_REG_SAR_CTRL,
			NAU8825_SAR_INPUT_MASK,
			NAU8825_SAR_INPUT_JKSLV);

		snd_soc_dapm_क्रमce_enable_pin(dapm, "MICBIAS");
		snd_soc_dapm_क्रमce_enable_pin(dapm, "SAR");
		snd_soc_dapm_sync(dapm);
		अवरोध;
	हाल 3:
		/* detect error हाल */
		dev_err(nau8825->dev, "detection error; disable mic function\n");
		type = SND_JACK_HEADPHONE;
		अवरोध;
	पूर्ण

	/* Leaving HPOL/R grounded after jack insert by शेष. They will be
	 * ungrounded as part of the widget घातer up sequence at the beginning
	 * of playback to reduce pop.
	 */
	वापस type;
पूर्ण

#घोषणा NAU8825_BUTTONS (SND_JACK_BTN_0 | SND_JACK_BTN_1 | \
		SND_JACK_BTN_2 | SND_JACK_BTN_3)

अटल irqवापस_t nau8825_पूर्णांकerrupt(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा nau8825 *nau8825 = (काष्ठा nau8825 *)data;
	काष्ठा regmap *regmap = nau8825->regmap;
	पूर्णांक active_irq, clear_irq = 0, event = 0, event_mask = 0;

	अगर (regmap_पढ़ो(regmap, NAU8825_REG_IRQ_STATUS, &active_irq)) अणु
		dev_err(nau8825->dev, "failed to read irq status\n");
		वापस IRQ_NONE;
	पूर्ण

	अगर ((active_irq & NAU8825_JACK_EJECTION_IRQ_MASK) ==
		NAU8825_JACK_EJECTION_DETECTED) अणु

		nau8825_eject_jack(nau8825);
		event_mask |= SND_JACK_HEADSET;
		clear_irq = NAU8825_JACK_EJECTION_IRQ_MASK;
	पूर्ण अन्यथा अगर (active_irq & NAU8825_KEY_SHORT_PRESS_IRQ) अणु
		पूर्णांक key_status;

		regmap_पढ़ो(regmap, NAU8825_REG_INT_CLR_KEY_STATUS,
			&key_status);

		/* upper 8 bits of the रेजिस्टर are क्रम लघु pressed keys,
		 * lower 8 bits - क्रम दीर्घ pressed buttons
		 */
		nau8825->button_pressed = nau8825_button_decode(
			key_status >> 8);

		event |= nau8825->button_pressed;
		event_mask |= NAU8825_BUTTONS;
		clear_irq = NAU8825_KEY_SHORT_PRESS_IRQ;
	पूर्ण अन्यथा अगर (active_irq & NAU8825_KEY_RELEASE_IRQ) अणु
		event_mask = NAU8825_BUTTONS;
		clear_irq = NAU8825_KEY_RELEASE_IRQ;
	पूर्ण अन्यथा अगर (active_irq & NAU8825_HEADSET_COMPLETION_IRQ) अणु
		अगर (nau8825_is_jack_inserted(regmap)) अणु
			event |= nau8825_jack_insert(nau8825);
			अगर (nau8825->xtalk_enable && !nau8825->high_imped) अणु
				/* Apply the cross talk suppression in the
				 * headset without high impedance.
				 */
				अगर (!nau8825->xtalk_protect) अणु
					/* Raise protection क्रम cross talk de-
					 * tection अगर no protection beक्रमe.
					 * The driver has to cancel the pro-
					 * cess and restore changes अगर process
					 * is ongoing when ejection.
					 */
					पूर्णांक ret;
					nau8825->xtalk_protect = true;
					ret = nau8825_sema_acquire(nau8825, 0);
					अगर (ret)
						nau8825->xtalk_protect = false;
				पूर्ण
				/* Startup cross talk detection process */
				अगर (nau8825->xtalk_protect) अणु
					nau8825->xtalk_state =
						NAU8825_XTALK_PREPARE;
					schedule_work(&nau8825->xtalk_work);
				पूर्ण
			पूर्ण अन्यथा अणु
				/* The cross talk suppression shouldn't apply
				 * in the headset with high impedance. Thus,
				 * relieve the protection उठाओd beक्रमe.
				 */
				अगर (nau8825->xtalk_protect) अणु
					nau8825_sema_release(nau8825);
					nau8825->xtalk_protect = false;
				पूर्ण
			पूर्ण
		पूर्ण अन्यथा अणु
			dev_warn(nau8825->dev, "Headset completion IRQ fired but no headset connected\n");
			nau8825_eject_jack(nau8825);
		पूर्ण

		event_mask |= SND_JACK_HEADSET;
		clear_irq = NAU8825_HEADSET_COMPLETION_IRQ;
		/* Record the पूर्णांकerruption report event क्रम driver to report
		 * the event later. The jack report will delay until cross
		 * talk detection process is करोne.
		 */
		अगर (nau8825->xtalk_state == NAU8825_XTALK_PREPARE) अणु
			nau8825->xtalk_event = event;
			nau8825->xtalk_event_mask = event_mask;
		पूर्ण
	पूर्ण अन्यथा अगर (active_irq & NAU8825_IMPEDANCE_MEAS_IRQ) अणु
		/* crosstalk detection enable and process on going */
		अगर (nau8825->xtalk_enable && nau8825->xtalk_protect)
			schedule_work(&nau8825->xtalk_work);
		clear_irq = NAU8825_IMPEDANCE_MEAS_IRQ;
	पूर्ण अन्यथा अगर ((active_irq & NAU8825_JACK_INSERTION_IRQ_MASK) ==
		NAU8825_JACK_INSERTION_DETECTED) अणु
		/* One more step to check GPIO status directly. Thus, the
		 * driver can confirm the real insertion पूर्णांकerruption because
		 * the पूर्णांकrruption at manual mode has bypassed debounce
		 * circuit which can get rid of unstable status.
		 */
		अगर (nau8825_is_jack_inserted(regmap)) अणु
			/* Turn off insertion पूर्णांकerruption at manual mode */
			regmap_update_bits(regmap,
				NAU8825_REG_INTERRUPT_DIS_CTRL,
				NAU8825_IRQ_INSERT_DIS,
				NAU8825_IRQ_INSERT_DIS);
			regmap_update_bits(regmap, NAU8825_REG_INTERRUPT_MASK,
				NAU8825_IRQ_INSERT_EN, NAU8825_IRQ_INSERT_EN);
			/* Enable पूर्णांकerruption क्रम jack type detection at auकरो
			 * mode which can detect microphone and jack type.
			 */
			nau8825_setup_स्वतः_irq(nau8825);
		पूर्ण
	पूर्ण

	अगर (!clear_irq)
		clear_irq = active_irq;
	/* clears the righपंचांगost पूर्णांकerruption */
	regmap_ग_लिखो(regmap, NAU8825_REG_INT_CLR_KEY_STATUS, clear_irq);

	/* Delay jack report until cross talk detection is करोne. It can aव्योम
	 * application to करो playback preparation when cross talk detection
	 * process is still working. Otherwise, the resource like घड़ी and
	 * घातer will be issued by them at the same समय and conflict happens.
	 */
	अगर (event_mask && nau8825->xtalk_state == NAU8825_XTALK_DONE)
		snd_soc_jack_report(nau8825->jack, event, event_mask);

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम nau8825_setup_buttons(काष्ठा nau8825 *nau8825)
अणु
	काष्ठा regmap *regmap = nau8825->regmap;

	regmap_update_bits(regmap, NAU8825_REG_SAR_CTRL,
		NAU8825_SAR_TRACKING_GAIN_MASK,
		nau8825->sar_voltage << NAU8825_SAR_TRACKING_GAIN_SFT);
	regmap_update_bits(regmap, NAU8825_REG_SAR_CTRL,
		NAU8825_SAR_COMPARE_TIME_MASK,
		nau8825->sar_compare_समय << NAU8825_SAR_COMPARE_TIME_SFT);
	regmap_update_bits(regmap, NAU8825_REG_SAR_CTRL,
		NAU8825_SAR_SAMPLING_TIME_MASK,
		nau8825->sar_sampling_समय << NAU8825_SAR_SAMPLING_TIME_SFT);

	regmap_update_bits(regmap, NAU8825_REG_KEYDET_CTRL,
		NAU8825_KEYDET_LEVELS_NR_MASK,
		(nau8825->sar_threshold_num - 1) << NAU8825_KEYDET_LEVELS_NR_SFT);
	regmap_update_bits(regmap, NAU8825_REG_KEYDET_CTRL,
		NAU8825_KEYDET_HYSTERESIS_MASK,
		nau8825->sar_hysteresis << NAU8825_KEYDET_HYSTERESIS_SFT);
	regmap_update_bits(regmap, NAU8825_REG_KEYDET_CTRL,
		NAU8825_KEYDET_SHORTKEY_DEBOUNCE_MASK,
		nau8825->key_debounce << NAU8825_KEYDET_SHORTKEY_DEBOUNCE_SFT);

	regmap_ग_लिखो(regmap, NAU8825_REG_VDET_THRESHOLD_1,
		(nau8825->sar_threshold[0] << 8) | nau8825->sar_threshold[1]);
	regmap_ग_लिखो(regmap, NAU8825_REG_VDET_THRESHOLD_2,
		(nau8825->sar_threshold[2] << 8) | nau8825->sar_threshold[3]);
	regmap_ग_लिखो(regmap, NAU8825_REG_VDET_THRESHOLD_3,
		(nau8825->sar_threshold[4] << 8) | nau8825->sar_threshold[5]);
	regmap_ग_लिखो(regmap, NAU8825_REG_VDET_THRESHOLD_4,
		(nau8825->sar_threshold[6] << 8) | nau8825->sar_threshold[7]);

	/* Enable लघु press and release पूर्णांकerruptions */
	regmap_update_bits(regmap, NAU8825_REG_INTERRUPT_MASK,
		NAU8825_IRQ_KEY_SHORT_PRESS_EN | NAU8825_IRQ_KEY_RELEASE_EN,
		0);
पूर्ण

अटल व्योम nau8825_init_regs(काष्ठा nau8825 *nau8825)
अणु
	काष्ठा regmap *regmap = nau8825->regmap;

	/* Latch IIC LSB value */
	regmap_ग_लिखो(regmap, NAU8825_REG_IIC_ADDR_SET, 0x0001);
	/* Enable Bias/Vmid */
	regmap_update_bits(nau8825->regmap, NAU8825_REG_BIAS_ADJ,
		NAU8825_BIAS_VMID, NAU8825_BIAS_VMID);
	regmap_update_bits(nau8825->regmap, NAU8825_REG_BOOST,
		NAU8825_GLOBAL_BIAS_EN, NAU8825_GLOBAL_BIAS_EN);

	/* VMID Tieoff */
	regmap_update_bits(regmap, NAU8825_REG_BIAS_ADJ,
		NAU8825_BIAS_VMID_SEL_MASK,
		nau8825->vref_impedance << NAU8825_BIAS_VMID_SEL_SFT);
	/* Disable Boost Driver, Automatic Short circuit protection enable */
	regmap_update_bits(regmap, NAU8825_REG_BOOST,
		NAU8825_PRECHARGE_DIS | NAU8825_HP_BOOST_DIS |
		NAU8825_HP_BOOST_G_DIS | NAU8825_SHORT_SHUTDOWN_EN,
		NAU8825_PRECHARGE_DIS | NAU8825_HP_BOOST_DIS |
		NAU8825_HP_BOOST_G_DIS | NAU8825_SHORT_SHUTDOWN_EN);

	regmap_update_bits(regmap, NAU8825_REG_GPIO12_CTRL,
		NAU8825_JKDET_OUTPUT_EN,
		nau8825->jkdet_enable ? 0 : NAU8825_JKDET_OUTPUT_EN);
	regmap_update_bits(regmap, NAU8825_REG_GPIO12_CTRL,
		NAU8825_JKDET_PULL_EN,
		nau8825->jkdet_pull_enable ? 0 : NAU8825_JKDET_PULL_EN);
	regmap_update_bits(regmap, NAU8825_REG_GPIO12_CTRL,
		NAU8825_JKDET_PULL_UP,
		nau8825->jkdet_pull_up ? NAU8825_JKDET_PULL_UP : 0);
	regmap_update_bits(regmap, NAU8825_REG_JACK_DET_CTRL,
		NAU8825_JACK_POLARITY,
		/* jkdet_polarity - 1  is क्रम active-low */
		nau8825->jkdet_polarity ? 0 : NAU8825_JACK_POLARITY);

	regmap_update_bits(regmap, NAU8825_REG_JACK_DET_CTRL,
		NAU8825_JACK_INSERT_DEBOUNCE_MASK,
		nau8825->jack_insert_debounce << NAU8825_JACK_INSERT_DEBOUNCE_SFT);
	regmap_update_bits(regmap, NAU8825_REG_JACK_DET_CTRL,
		NAU8825_JACK_EJECT_DEBOUNCE_MASK,
		nau8825->jack_eject_debounce << NAU8825_JACK_EJECT_DEBOUNCE_SFT);

	/* Pull up IRQ pin */
	regmap_update_bits(regmap, NAU8825_REG_INTERRUPT_MASK,
		NAU8825_IRQ_PIN_PULLUP | NAU8825_IRQ_PIN_PULL_EN,
		NAU8825_IRQ_PIN_PULLUP | NAU8825_IRQ_PIN_PULL_EN);
	/* Mask unneeded IRQs: 1 - disable, 0 - enable */
	regmap_update_bits(regmap, NAU8825_REG_INTERRUPT_MASK, 0x7ff, 0x7ff);

	regmap_update_bits(regmap, NAU8825_REG_MIC_BIAS,
		NAU8825_MICBIAS_VOLTAGE_MASK, nau8825->micbias_voltage);

	अगर (nau8825->sar_threshold_num)
		nau8825_setup_buttons(nau8825);

	/* Default oversampling/decimations settings are unusable
	 * (audible hiss). Set it to something better.
	 */
	regmap_update_bits(regmap, NAU8825_REG_ADC_RATE,
		NAU8825_ADC_SYNC_DOWN_MASK | NAU8825_ADC_SINC4_EN,
		NAU8825_ADC_SYNC_DOWN_64);
	regmap_update_bits(regmap, NAU8825_REG_DAC_CTRL1,
		NAU8825_DAC_OVERSAMPLE_MASK, NAU8825_DAC_OVERSAMPLE_64);
	/* Disable DACR/L घातer */
	regmap_update_bits(regmap, NAU8825_REG_CHARGE_PUMP,
		NAU8825_POWER_DOWN_DACR | NAU8825_POWER_DOWN_DACL,
		NAU8825_POWER_DOWN_DACR | NAU8825_POWER_DOWN_DACL);
	/* Enable TESTDAC. This sets the analog DAC inमाला_दो to a '0' input
	 * संकेत to aव्योम any glitches due to घातer up transients in both
	 * the analog and digital DAC circuit.
	 */
	regmap_update_bits(nau8825->regmap, NAU8825_REG_BIAS_ADJ,
		NAU8825_BIAS_TESTDAC_EN, NAU8825_BIAS_TESTDAC_EN);
	/* CICCLP off */
	regmap_update_bits(regmap, NAU8825_REG_DAC_CTRL1,
		NAU8825_DAC_CLIP_OFF, NAU8825_DAC_CLIP_OFF);

	/* Class AB bias current to 2x, DAC Capacitor enable MSB/LSB */
	regmap_update_bits(regmap, NAU8825_REG_ANALOG_CONTROL_2,
		NAU8825_HP_NON_CLASSG_CURRENT_2xADJ |
		NAU8825_DAC_CAPACITOR_MSB | NAU8825_DAC_CAPACITOR_LSB,
		NAU8825_HP_NON_CLASSG_CURRENT_2xADJ |
		NAU8825_DAC_CAPACITOR_MSB | NAU8825_DAC_CAPACITOR_LSB);
	/* Class G समयr 64ms */
	regmap_update_bits(regmap, NAU8825_REG_CLASSG_CTRL,
		NAU8825_CLASSG_TIMER_MASK,
		0x20 << NAU8825_CLASSG_TIMER_SFT);
	/* DAC घड़ी delay 2ns, VREF */
	regmap_update_bits(regmap, NAU8825_REG_RDAC,
		NAU8825_RDAC_CLK_DELAY_MASK | NAU8825_RDAC_VREF_MASK,
		(0x2 << NAU8825_RDAC_CLK_DELAY_SFT) |
		(0x3 << NAU8825_RDAC_VREF_SFT));
	/* Config L/R channel */
	regmap_update_bits(nau8825->regmap, NAU8825_REG_DACL_CTRL,
		NAU8825_DACL_CH_SEL_MASK, NAU8825_DACL_CH_SEL_L);
	regmap_update_bits(nau8825->regmap, NAU8825_REG_DACR_CTRL,
		NAU8825_DACL_CH_SEL_MASK, NAU8825_DACL_CH_SEL_R);
	/* Disable लघु Frame Sync detection logic */
	regmap_update_bits(regmap, NAU8825_REG_LEFT_TIME_SLOT,
		NAU8825_DIS_FS_SHORT_DET, NAU8825_DIS_FS_SHORT_DET);
पूर्ण

अटल स्थिर काष्ठा regmap_config nau8825_regmap_config = अणु
	.val_bits = NAU8825_REG_DATA_LEN,
	.reg_bits = NAU8825_REG_ADDR_LEN,

	.max_रेजिस्टर = NAU8825_REG_MAX,
	.पढ़ोable_reg = nau8825_पढ़ोable_reg,
	.ग_लिखोable_reg = nau8825_ग_लिखोable_reg,
	.अस्थिर_reg = nau8825_अस्थिर_reg,

	.cache_type = REGCACHE_RBTREE,
	.reg_शेषs = nau8825_reg_शेषs,
	.num_reg_शेषs = ARRAY_SIZE(nau8825_reg_शेषs),
पूर्ण;

अटल पूर्णांक nau8825_component_probe(काष्ठा snd_soc_component *component)
अणु
	काष्ठा nau8825 *nau8825 = snd_soc_component_get_drvdata(component);
	काष्ठा snd_soc_dapm_context *dapm = snd_soc_component_get_dapm(component);

	nau8825->dapm = dapm;

	वापस 0;
पूर्ण

अटल व्योम nau8825_component_हटाओ(काष्ठा snd_soc_component *component)
अणु
	काष्ठा nau8825 *nau8825 = snd_soc_component_get_drvdata(component);

	/* Cancel and reset cross tak suppresstion detection funciton */
	nau8825_xtalk_cancel(nau8825);
पूर्ण

/**
 * nau8825_calc_fll_param - Calculate FLL parameters.
 * @fll_in: बाह्यal घड़ी provided to codec.
 * @fs: sampling rate.
 * @fll_param: Poपूर्णांकer to काष्ठाure of FLL parameters.
 *
 * Calculate FLL parameters to configure codec.
 *
 * Returns 0 क्रम success or negative error code.
 */
अटल पूर्णांक nau8825_calc_fll_param(अचिन्हित पूर्णांक fll_in, अचिन्हित पूर्णांक fs,
		काष्ठा nau8825_fll *fll_param)
अणु
	u64 fvco, fvco_max;
	अचिन्हित पूर्णांक fref, i, fvco_sel;

	/* Ensure the reference घड़ी frequency (FREF) is <= 13.5MHz by भागiding
	 * freq_in by 1, 2, 4, or 8 using FLL pre-scalar.
	 * FREF = freq_in / NAU8825_FLL_REF_DIV_MASK
	 */
	क्रम (i = 0; i < ARRAY_SIZE(fll_pre_scalar); i++) अणु
		fref = fll_in / fll_pre_scalar[i].param;
		अगर (fref <= NAU_FREF_MAX)
			अवरोध;
	पूर्ण
	अगर (i == ARRAY_SIZE(fll_pre_scalar))
		वापस -EINVAL;
	fll_param->clk_ref_भाग = fll_pre_scalar[i].val;

	/* Choose the FLL ratio based on FREF */
	क्रम (i = 0; i < ARRAY_SIZE(fll_ratio); i++) अणु
		अगर (fref >= fll_ratio[i].param)
			अवरोध;
	पूर्ण
	अगर (i == ARRAY_SIZE(fll_ratio))
		वापस -EINVAL;
	fll_param->ratio = fll_ratio[i].val;

	/* Calculate the frequency of DCO (FDCO) given freq_out = 256 * Fs.
	 * FDCO must be within the 90MHz - 124MHz or the FFL cannot be
	 * guaranteed across the full range of operation.
	 * FDCO = freq_out * 2 * mclk_src_scaling
	 */
	fvco_max = 0;
	fvco_sel = ARRAY_SIZE(mclk_src_scaling);
	क्रम (i = 0; i < ARRAY_SIZE(mclk_src_scaling); i++) अणु
		fvco = 256ULL * fs * 2 * mclk_src_scaling[i].param;
		अगर (fvco > NAU_FVCO_MIN && fvco < NAU_FVCO_MAX &&
			fvco_max < fvco) अणु
			fvco_max = fvco;
			fvco_sel = i;
		पूर्ण
	पूर्ण
	अगर (ARRAY_SIZE(mclk_src_scaling) == fvco_sel)
		वापस -EINVAL;
	fll_param->mclk_src = mclk_src_scaling[fvco_sel].val;

	/* Calculate the FLL 10-bit पूर्णांकeger input and the FLL 16-bit fractional
	 * input based on FDCO, FREF and FLL ratio.
	 */
	fvco = भाग_u64(fvco_max << 16, fref * fll_param->ratio);
	fll_param->fll_पूर्णांक = (fvco >> 16) & 0x3FF;
	fll_param->fll_frac = fvco & 0xFFFF;
	वापस 0;
पूर्ण

अटल व्योम nau8825_fll_apply(काष्ठा nau8825 *nau8825,
		काष्ठा nau8825_fll *fll_param)
अणु
	regmap_update_bits(nau8825->regmap, NAU8825_REG_CLK_DIVIDER,
		NAU8825_CLK_SRC_MASK | NAU8825_CLK_MCLK_SRC_MASK,
		NAU8825_CLK_SRC_MCLK | fll_param->mclk_src);
	/* Make DSP operate at high speed क्रम better perक्रमmance. */
	regmap_update_bits(nau8825->regmap, NAU8825_REG_FLL1,
		NAU8825_FLL_RATIO_MASK | NAU8825_ICTRL_LATCH_MASK,
		fll_param->ratio | (0x6 << NAU8825_ICTRL_LATCH_SFT));
	/* FLL 16-bit fractional input */
	regmap_ग_लिखो(nau8825->regmap, NAU8825_REG_FLL2, fll_param->fll_frac);
	/* FLL 10-bit पूर्णांकeger input */
	regmap_update_bits(nau8825->regmap, NAU8825_REG_FLL3,
			NAU8825_FLL_INTEGER_MASK, fll_param->fll_पूर्णांक);
	/* FLL pre-scaler */
	regmap_update_bits(nau8825->regmap, NAU8825_REG_FLL4,
			NAU8825_FLL_REF_DIV_MASK,
			fll_param->clk_ref_भाग << NAU8825_FLL_REF_DIV_SFT);
	/* select भागided VCO input */
	regmap_update_bits(nau8825->regmap, NAU8825_REG_FLL5,
		NAU8825_FLL_CLK_SW_MASK, NAU8825_FLL_CLK_SW_REF);
	/* Disable मुक्त-running mode */
	regmap_update_bits(nau8825->regmap,
		NAU8825_REG_FLL6, NAU8825_DCO_EN, 0);
	अगर (fll_param->fll_frac) अणु
		/* set FLL loop filter enable and cutoff frequency at 500Khz */
		regmap_update_bits(nau8825->regmap, NAU8825_REG_FLL5,
			NAU8825_FLL_PDB_DAC_EN | NAU8825_FLL_LOOP_FTR_EN |
			NAU8825_FLL_FTR_SW_MASK,
			NAU8825_FLL_PDB_DAC_EN | NAU8825_FLL_LOOP_FTR_EN |
			NAU8825_FLL_FTR_SW_FILTER);
		regmap_update_bits(nau8825->regmap, NAU8825_REG_FLL6,
			NAU8825_SDM_EN | NAU8825_CUTOFF500,
			NAU8825_SDM_EN | NAU8825_CUTOFF500);
	पूर्ण अन्यथा अणु
		/* disable FLL loop filter and cutoff frequency */
		regmap_update_bits(nau8825->regmap, NAU8825_REG_FLL5,
			NAU8825_FLL_PDB_DAC_EN | NAU8825_FLL_LOOP_FTR_EN |
			NAU8825_FLL_FTR_SW_MASK, NAU8825_FLL_FTR_SW_ACCU);
		regmap_update_bits(nau8825->regmap, NAU8825_REG_FLL6,
			NAU8825_SDM_EN | NAU8825_CUTOFF500, 0);
	पूर्ण
पूर्ण

/* freq_out must be 256*Fs in order to achieve the best perक्रमmance */
अटल पूर्णांक nau8825_set_pll(काष्ठा snd_soc_component *component, पूर्णांक pll_id, पूर्णांक source,
		अचिन्हित पूर्णांक freq_in, अचिन्हित पूर्णांक freq_out)
अणु
	काष्ठा nau8825 *nau8825 = snd_soc_component_get_drvdata(component);
	काष्ठा nau8825_fll fll_param;
	पूर्णांक ret, fs;

	fs = freq_out / 256;
	ret = nau8825_calc_fll_param(freq_in, fs, &fll_param);
	अगर (ret < 0) अणु
		dev_err(component->dev, "Unsupported input clock %d\n", freq_in);
		वापस ret;
	पूर्ण
	dev_dbg(component->dev, "mclk_src=%x ratio=%x fll_frac=%x fll_int=%x clk_ref_div=%x\n",
		fll_param.mclk_src, fll_param.ratio, fll_param.fll_frac,
		fll_param.fll_पूर्णांक, fll_param.clk_ref_भाग);

	nau8825_fll_apply(nau8825, &fll_param);
	mdelay(2);
	regmap_update_bits(nau8825->regmap, NAU8825_REG_CLK_DIVIDER,
			NAU8825_CLK_SRC_MASK, NAU8825_CLK_SRC_VCO);
	वापस 0;
पूर्ण

अटल पूर्णांक nau8825_mclk_prepare(काष्ठा nau8825 *nau8825, अचिन्हित पूर्णांक freq)
अणु
	पूर्णांक ret;

	nau8825->mclk = devm_clk_get(nau8825->dev, "mclk");
	अगर (IS_ERR(nau8825->mclk)) अणु
		dev_info(nau8825->dev, "No 'mclk' clock found, assume MCLK is managed externally");
		वापस 0;
	पूर्ण

	अगर (!nau8825->mclk_freq) अणु
		ret = clk_prepare_enable(nau8825->mclk);
		अगर (ret) अणु
			dev_err(nau8825->dev, "Unable to prepare codec mclk\n");
			वापस ret;
		पूर्ण
	पूर्ण

	अगर (nau8825->mclk_freq != freq) अणु
		freq = clk_round_rate(nau8825->mclk, freq);
		ret = clk_set_rate(nau8825->mclk, freq);
		अगर (ret) अणु
			dev_err(nau8825->dev, "Unable to set mclk rate\n");
			वापस ret;
		पूर्ण
		nau8825->mclk_freq = freq;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम nau8825_configure_mclk_as_sysclk(काष्ठा regmap *regmap)
अणु
	regmap_update_bits(regmap, NAU8825_REG_CLK_DIVIDER,
		NAU8825_CLK_SRC_MASK, NAU8825_CLK_SRC_MCLK);
	regmap_update_bits(regmap, NAU8825_REG_FLL6,
		NAU8825_DCO_EN, 0);
	/* Make DSP operate as शेष setting क्रम घातer saving. */
	regmap_update_bits(regmap, NAU8825_REG_FLL1,
		NAU8825_ICTRL_LATCH_MASK, 0);
पूर्ण

अटल पूर्णांक nau8825_configure_sysclk(काष्ठा nau8825 *nau8825, पूर्णांक clk_id,
	अचिन्हित पूर्णांक freq)
अणु
	काष्ठा regmap *regmap = nau8825->regmap;
	पूर्णांक ret;

	चयन (clk_id) अणु
	हाल NAU8825_CLK_DIS:
		/* Clock provided बाह्यally and disable पूर्णांकernal VCO घड़ी */
		nau8825_configure_mclk_as_sysclk(regmap);
		अगर (nau8825->mclk_freq) अणु
			clk_disable_unprepare(nau8825->mclk);
			nau8825->mclk_freq = 0;
		पूर्ण

		अवरोध;
	हाल NAU8825_CLK_MCLK:
		/* Acquire the semaphore to synchronize the playback and
		 * पूर्णांकerrupt handler. In order to aव्योम the playback पूर्णांकer-
		 * fered by cross talk process, the driver make the playback
		 * preparation halted until cross talk process finish.
		 */
		nau8825_sema_acquire(nau8825, 3 * HZ);
		nau8825_configure_mclk_as_sysclk(regmap);
		/* MCLK not changed by घड़ी tree */
		regmap_update_bits(regmap, NAU8825_REG_CLK_DIVIDER,
			NAU8825_CLK_MCLK_SRC_MASK, 0);
		/* Release the semaphore. */
		nau8825_sema_release(nau8825);

		ret = nau8825_mclk_prepare(nau8825, freq);
		अगर (ret)
			वापस ret;

		अवरोध;
	हाल NAU8825_CLK_INTERNAL:
		अगर (nau8825_is_jack_inserted(nau8825->regmap)) अणु
			regmap_update_bits(regmap, NAU8825_REG_FLL6,
				NAU8825_DCO_EN, NAU8825_DCO_EN);
			regmap_update_bits(regmap, NAU8825_REG_CLK_DIVIDER,
				NAU8825_CLK_SRC_MASK, NAU8825_CLK_SRC_VCO);
			/* Decrease the VCO frequency and make DSP operate
			 * as शेष setting क्रम घातer saving.
			 */
			regmap_update_bits(regmap, NAU8825_REG_CLK_DIVIDER,
				NAU8825_CLK_MCLK_SRC_MASK, 0xf);
			regmap_update_bits(regmap, NAU8825_REG_FLL1,
				NAU8825_ICTRL_LATCH_MASK |
				NAU8825_FLL_RATIO_MASK, 0x10);
			regmap_update_bits(regmap, NAU8825_REG_FLL6,
				NAU8825_SDM_EN, NAU8825_SDM_EN);
		पूर्ण अन्यथा अणु
			/* The घड़ी turns off पूर्णांकentionally क्रम घातer saving
			 * when no headset connected.
			 */
			nau8825_configure_mclk_as_sysclk(regmap);
			dev_warn(nau8825->dev, "Disable clock for power saving when no headset connected\n");
		पूर्ण
		अगर (nau8825->mclk_freq) अणु
			clk_disable_unprepare(nau8825->mclk);
			nau8825->mclk_freq = 0;
		पूर्ण

		अवरोध;
	हाल NAU8825_CLK_FLL_MCLK:
		/* Acquire the semaphore to synchronize the playback and
		 * पूर्णांकerrupt handler. In order to aव्योम the playback पूर्णांकer-
		 * fered by cross talk process, the driver make the playback
		 * preparation halted until cross talk process finish.
		 */
		nau8825_sema_acquire(nau8825, 3 * HZ);
		/* Higher FLL reference input frequency can only set lower
		 * gain error, such as 0000 क्रम input reference from MCLK
		 * 12.288Mhz.
		 */
		regmap_update_bits(regmap, NAU8825_REG_FLL3,
			NAU8825_FLL_CLK_SRC_MASK | NAU8825_GAIN_ERR_MASK,
			NAU8825_FLL_CLK_SRC_MCLK | 0);
		/* Release the semaphore. */
		nau8825_sema_release(nau8825);

		ret = nau8825_mclk_prepare(nau8825, freq);
		अगर (ret)
			वापस ret;

		अवरोध;
	हाल NAU8825_CLK_FLL_BLK:
		/* Acquire the semaphore to synchronize the playback and
		 * पूर्णांकerrupt handler. In order to aव्योम the playback पूर्णांकer-
		 * fered by cross talk process, the driver make the playback
		 * preparation halted until cross talk process finish.
		 */
		nau8825_sema_acquire(nau8825, 3 * HZ);
		/* If FLL reference input is from low frequency source,
		 * higher error gain can apply such as 0xf which has
		 * the most sensitive gain error correction threshold,
		 * Thereक्रमe, FLL has the most accurate DCO to
		 * target frequency.
		 */
		regmap_update_bits(regmap, NAU8825_REG_FLL3,
			NAU8825_FLL_CLK_SRC_MASK | NAU8825_GAIN_ERR_MASK,
			NAU8825_FLL_CLK_SRC_BLK |
			(0xf << NAU8825_GAIN_ERR_SFT));
		/* Release the semaphore. */
		nau8825_sema_release(nau8825);

		अगर (nau8825->mclk_freq) अणु
			clk_disable_unprepare(nau8825->mclk);
			nau8825->mclk_freq = 0;
		पूर्ण

		अवरोध;
	हाल NAU8825_CLK_FLL_FS:
		/* Acquire the semaphore to synchronize the playback and
		 * पूर्णांकerrupt handler. In order to aव्योम the playback पूर्णांकer-
		 * fered by cross talk process, the driver make the playback
		 * preparation halted until cross talk process finish.
		 */
		nau8825_sema_acquire(nau8825, 3 * HZ);
		/* If FLL reference input is from low frequency source,
		 * higher error gain can apply such as 0xf which has
		 * the most sensitive gain error correction threshold,
		 * Thereक्रमe, FLL has the most accurate DCO to
		 * target frequency.
		 */
		regmap_update_bits(regmap, NAU8825_REG_FLL3,
			NAU8825_FLL_CLK_SRC_MASK | NAU8825_GAIN_ERR_MASK,
			NAU8825_FLL_CLK_SRC_FS |
			(0xf << NAU8825_GAIN_ERR_SFT));
		/* Release the semaphore. */
		nau8825_sema_release(nau8825);

		अगर (nau8825->mclk_freq) अणु
			clk_disable_unprepare(nau8825->mclk);
			nau8825->mclk_freq = 0;
		पूर्ण

		अवरोध;
	शेष:
		dev_err(nau8825->dev, "Invalid clock id (%d)\n", clk_id);
		वापस -EINVAL;
	पूर्ण

	dev_dbg(nau8825->dev, "Sysclk is %dHz and clock id is %d\n", freq,
		clk_id);
	वापस 0;
पूर्ण

अटल पूर्णांक nau8825_set_sysclk(काष्ठा snd_soc_component *component, पूर्णांक clk_id,
	पूर्णांक source, अचिन्हित पूर्णांक freq, पूर्णांक dir)
अणु
	काष्ठा nau8825 *nau8825 = snd_soc_component_get_drvdata(component);

	वापस nau8825_configure_sysclk(nau8825, clk_id, freq);
पूर्ण

अटल पूर्णांक nau8825_resume_setup(काष्ठा nau8825 *nau8825)
अणु
	काष्ठा regmap *regmap = nau8825->regmap;

	/* Close घड़ी when jack type detection at manual mode */
	nau8825_configure_sysclk(nau8825, NAU8825_CLK_DIS, 0);

	/* Clear all पूर्णांकerruption status */
	nau8825_पूर्णांक_status_clear_all(regmap);

	/* Enable both insertion and ejection पूर्णांकerruptions, and then
	 * bypass de-bounce circuit.
	 */
	regmap_update_bits(regmap, NAU8825_REG_INTERRUPT_MASK,
		NAU8825_IRQ_OUTPUT_EN | NAU8825_IRQ_HEADSET_COMPLETE_EN |
		NAU8825_IRQ_EJECT_EN | NAU8825_IRQ_INSERT_EN,
		NAU8825_IRQ_OUTPUT_EN | NAU8825_IRQ_HEADSET_COMPLETE_EN);
	regmap_update_bits(regmap, NAU8825_REG_JACK_DET_CTRL,
		NAU8825_JACK_DET_DB_BYPASS, NAU8825_JACK_DET_DB_BYPASS);
	regmap_update_bits(regmap, NAU8825_REG_INTERRUPT_DIS_CTRL,
		NAU8825_IRQ_INSERT_DIS | NAU8825_IRQ_EJECT_DIS, 0);

	वापस 0;
पूर्ण

अटल पूर्णांक nau8825_set_bias_level(काष्ठा snd_soc_component *component,
				   क्रमागत snd_soc_bias_level level)
अणु
	काष्ठा nau8825 *nau8825 = snd_soc_component_get_drvdata(component);
	पूर्णांक ret;

	चयन (level) अणु
	हाल SND_SOC_BIAS_ON:
		अवरोध;

	हाल SND_SOC_BIAS_PREPARE:
		अवरोध;

	हाल SND_SOC_BIAS_STANDBY:
		अगर (snd_soc_component_get_bias_level(component) == SND_SOC_BIAS_OFF) अणु
			अगर (nau8825->mclk_freq) अणु
				ret = clk_prepare_enable(nau8825->mclk);
				अगर (ret) अणु
					dev_err(nau8825->dev, "Unable to prepare component mclk\n");
					वापस ret;
				पूर्ण
			पूर्ण
			/* Setup codec configuration after resume */
			nau8825_resume_setup(nau8825);
		पूर्ण
		अवरोध;

	हाल SND_SOC_BIAS_OFF:
		/* Reset the configuration of jack type क्रम detection */
		/* Detach 2kOhm Resistors from MICBIAS to MICGND1/2 */
		regmap_update_bits(nau8825->regmap, NAU8825_REG_MIC_BIAS,
			NAU8825_MICBIAS_JKSLV | NAU8825_MICBIAS_JKR2, 0);
		/* ground HPL/HPR, MICGRND1/2 */
		regmap_update_bits(nau8825->regmap,
			NAU8825_REG_HSD_CTRL, 0xf, 0xf);
		/* Cancel and reset cross talk detection funciton */
		nau8825_xtalk_cancel(nau8825);
		/* Turn off all पूर्णांकerruptions beक्रमe प्रणाली shutकरोwn. Keep the
		 * पूर्णांकerruption quiet beक्रमe resume setup completes.
		 */
		regmap_ग_लिखो(nau8825->regmap,
			NAU8825_REG_INTERRUPT_DIS_CTRL, 0xffff);
		/* Disable ADC needed क्रम पूर्णांकerruptions at auकरो mode */
		regmap_update_bits(nau8825->regmap, NAU8825_REG_ENA_CTRL,
			NAU8825_ENABLE_ADC, 0);
		अगर (nau8825->mclk_freq)
			clk_disable_unprepare(nau8825->mclk);
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused nau8825_suspend(काष्ठा snd_soc_component *component)
अणु
	काष्ठा nau8825 *nau8825 = snd_soc_component_get_drvdata(component);

	disable_irq(nau8825->irq);
	snd_soc_component_क्रमce_bias_level(component, SND_SOC_BIAS_OFF);
	/* Power करोwn codec घातer; करोn't suppoet button wakeup */
	snd_soc_dapm_disable_pin(nau8825->dapm, "SAR");
	snd_soc_dapm_disable_pin(nau8825->dapm, "MICBIAS");
	snd_soc_dapm_sync(nau8825->dapm);
	regcache_cache_only(nau8825->regmap, true);
	regcache_mark_dirty(nau8825->regmap);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused nau8825_resume(काष्ठा snd_soc_component *component)
अणु
	काष्ठा nau8825 *nau8825 = snd_soc_component_get_drvdata(component);
	पूर्णांक ret;

	regcache_cache_only(nau8825->regmap, false);
	regcache_sync(nau8825->regmap);
	nau8825->xtalk_protect = true;
	ret = nau8825_sema_acquire(nau8825, 0);
	अगर (ret)
		nau8825->xtalk_protect = false;
	enable_irq(nau8825->irq);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_component_driver nau8825_component_driver = अणु
	.probe			= nau8825_component_probe,
	.हटाओ			= nau8825_component_हटाओ,
	.set_sysclk		= nau8825_set_sysclk,
	.set_pll		= nau8825_set_pll,
	.set_bias_level		= nau8825_set_bias_level,
	.suspend		= nau8825_suspend,
	.resume			= nau8825_resume,
	.controls		= nau8825_controls,
	.num_controls		= ARRAY_SIZE(nau8825_controls),
	.dapm_widमाला_लो		= nau8825_dapm_widमाला_लो,
	.num_dapm_widमाला_लो	= ARRAY_SIZE(nau8825_dapm_widमाला_लो),
	.dapm_routes		= nau8825_dapm_routes,
	.num_dapm_routes	= ARRAY_SIZE(nau8825_dapm_routes),
	.suspend_bias_off	= 1,
	.idle_bias_on		= 1,
	.use_pmकरोwn_समय	= 1,
	.endianness		= 1,
	.non_legacy_dai_naming	= 1,
पूर्ण;

अटल व्योम nau8825_reset_chip(काष्ठा regmap *regmap)
अणु
	regmap_ग_लिखो(regmap, NAU8825_REG_RESET, 0x00);
	regmap_ग_लिखो(regmap, NAU8825_REG_RESET, 0x00);
पूर्ण

अटल व्योम nau8825_prपूर्णांक_device_properties(काष्ठा nau8825 *nau8825)
अणु
	पूर्णांक i;
	काष्ठा device *dev = nau8825->dev;

	dev_dbg(dev, "jkdet-enable:         %d\n", nau8825->jkdet_enable);
	dev_dbg(dev, "jkdet-pull-enable:    %d\n", nau8825->jkdet_pull_enable);
	dev_dbg(dev, "jkdet-pull-up:        %d\n", nau8825->jkdet_pull_up);
	dev_dbg(dev, "jkdet-polarity:       %d\n", nau8825->jkdet_polarity);
	dev_dbg(dev, "micbias-voltage:      %d\n", nau8825->micbias_voltage);
	dev_dbg(dev, "vref-impedance:       %d\n", nau8825->vref_impedance);

	dev_dbg(dev, "sar-threshold-num:    %d\n", nau8825->sar_threshold_num);
	क्रम (i = 0; i < nau8825->sar_threshold_num; i++)
		dev_dbg(dev, "sar-threshold[%d]=%d\n", i,
				nau8825->sar_threshold[i]);

	dev_dbg(dev, "sar-hysteresis:       %d\n", nau8825->sar_hysteresis);
	dev_dbg(dev, "sar-voltage:          %d\n", nau8825->sar_voltage);
	dev_dbg(dev, "sar-compare-time:     %d\n", nau8825->sar_compare_समय);
	dev_dbg(dev, "sar-sampling-time:    %d\n", nau8825->sar_sampling_समय);
	dev_dbg(dev, "short-key-debounce:   %d\n", nau8825->key_debounce);
	dev_dbg(dev, "jack-insert-debounce: %d\n",
			nau8825->jack_insert_debounce);
	dev_dbg(dev, "jack-eject-debounce:  %d\n",
			nau8825->jack_eject_debounce);
	dev_dbg(dev, "crosstalk-enable:     %d\n",
			nau8825->xtalk_enable);
पूर्ण

अटल पूर्णांक nau8825_पढ़ो_device_properties(काष्ठा device *dev,
	काष्ठा nau8825 *nau8825) अणु
	पूर्णांक ret;

	nau8825->jkdet_enable = device_property_पढ़ो_bool(dev,
		"nuvoton,jkdet-enable");
	nau8825->jkdet_pull_enable = device_property_पढ़ो_bool(dev,
		"nuvoton,jkdet-pull-enable");
	nau8825->jkdet_pull_up = device_property_पढ़ो_bool(dev,
		"nuvoton,jkdet-pull-up");
	ret = device_property_पढ़ो_u32(dev, "nuvoton,jkdet-polarity",
		&nau8825->jkdet_polarity);
	अगर (ret)
		nau8825->jkdet_polarity = 1;
	ret = device_property_पढ़ो_u32(dev, "nuvoton,micbias-voltage",
		&nau8825->micbias_voltage);
	अगर (ret)
		nau8825->micbias_voltage = 6;
	ret = device_property_पढ़ो_u32(dev, "nuvoton,vref-impedance",
		&nau8825->vref_impedance);
	अगर (ret)
		nau8825->vref_impedance = 2;
	ret = device_property_पढ़ो_u32(dev, "nuvoton,sar-threshold-num",
		&nau8825->sar_threshold_num);
	अगर (ret)
		nau8825->sar_threshold_num = 4;
	ret = device_property_पढ़ो_u32_array(dev, "nuvoton,sar-threshold",
		nau8825->sar_threshold, nau8825->sar_threshold_num);
	अगर (ret) अणु
		nau8825->sar_threshold[0] = 0x08;
		nau8825->sar_threshold[1] = 0x12;
		nau8825->sar_threshold[2] = 0x26;
		nau8825->sar_threshold[3] = 0x73;
	पूर्ण
	ret = device_property_पढ़ो_u32(dev, "nuvoton,sar-hysteresis",
		&nau8825->sar_hysteresis);
	अगर (ret)
		nau8825->sar_hysteresis = 0;
	ret = device_property_पढ़ो_u32(dev, "nuvoton,sar-voltage",
		&nau8825->sar_voltage);
	अगर (ret)
		nau8825->sar_voltage = 6;
	ret = device_property_पढ़ो_u32(dev, "nuvoton,sar-compare-time",
		&nau8825->sar_compare_समय);
	अगर (ret)
		nau8825->sar_compare_समय = 1;
	ret = device_property_पढ़ो_u32(dev, "nuvoton,sar-sampling-time",
		&nau8825->sar_sampling_समय);
	अगर (ret)
		nau8825->sar_sampling_समय = 1;
	ret = device_property_पढ़ो_u32(dev, "nuvoton,short-key-debounce",
		&nau8825->key_debounce);
	अगर (ret)
		nau8825->key_debounce = 3;
	ret = device_property_पढ़ो_u32(dev, "nuvoton,jack-insert-debounce",
		&nau8825->jack_insert_debounce);
	अगर (ret)
		nau8825->jack_insert_debounce = 7;
	ret = device_property_पढ़ो_u32(dev, "nuvoton,jack-eject-debounce",
		&nau8825->jack_eject_debounce);
	अगर (ret)
		nau8825->jack_eject_debounce = 0;
	nau8825->xtalk_enable = device_property_पढ़ो_bool(dev,
		"nuvoton,crosstalk-enable");

	nau8825->mclk = devm_clk_get(dev, "mclk");
	अगर (PTR_ERR(nau8825->mclk) == -EPROBE_DEFER) अणु
		वापस -EPROBE_DEFER;
	पूर्ण अन्यथा अगर (PTR_ERR(nau8825->mclk) == -ENOENT) अणु
		/* The MCLK is managed बाह्यally or not used at all */
		nau8825->mclk = शून्य;
		dev_info(dev, "No 'mclk' clock found, assume MCLK is managed externally");
	पूर्ण अन्यथा अगर (IS_ERR(nau8825->mclk)) अणु
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक nau8825_setup_irq(काष्ठा nau8825 *nau8825)
अणु
	पूर्णांक ret;

	ret = devm_request_thपढ़ोed_irq(nau8825->dev, nau8825->irq, शून्य,
		nau8825_पूर्णांकerrupt, IRQF_TRIGGER_LOW | IRQF_ONESHOT,
		"nau8825", nau8825);

	अगर (ret) अणु
		dev_err(nau8825->dev, "Cannot request irq %d (%d)\n",
			nau8825->irq, ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक nau8825_i2c_probe(काष्ठा i2c_client *i2c,
	स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा device *dev = &i2c->dev;
	काष्ठा nau8825 *nau8825 = dev_get_platdata(&i2c->dev);
	पूर्णांक ret, value;

	अगर (!nau8825) अणु
		nau8825 = devm_kzalloc(dev, माप(*nau8825), GFP_KERNEL);
		अगर (!nau8825)
			वापस -ENOMEM;
		ret = nau8825_पढ़ो_device_properties(dev, nau8825);
		अगर (ret)
			वापस ret;
	पूर्ण

	i2c_set_clientdata(i2c, nau8825);

	nau8825->regmap = devm_regmap_init_i2c(i2c, &nau8825_regmap_config);
	अगर (IS_ERR(nau8825->regmap))
		वापस PTR_ERR(nau8825->regmap);
	nau8825->dev = dev;
	nau8825->irq = i2c->irq;
	/* Initiate parameters, semaphore and work queue which are needed in
	 * cross talk suppression measurment function.
	 */
	nau8825->xtalk_state = NAU8825_XTALK_DONE;
	nau8825->xtalk_protect = false;
	nau8825->xtalk_baktab_initialized = false;
	sema_init(&nau8825->xtalk_sem, 1);
	INIT_WORK(&nau8825->xtalk_work, nau8825_xtalk_work);

	nau8825_prपूर्णांक_device_properties(nau8825);

	nau8825_reset_chip(nau8825->regmap);
	ret = regmap_पढ़ो(nau8825->regmap, NAU8825_REG_I2C_DEVICE_ID, &value);
	अगर (ret < 0) अणु
		dev_err(dev, "Failed to read device id from the NAU8825: %d\n",
			ret);
		वापस ret;
	पूर्ण
	अगर ((value & NAU8825_SOFTWARE_ID_MASK) !=
			NAU8825_SOFTWARE_ID_NAU8825) अणु
		dev_err(dev, "Not a NAU8825 chip\n");
		वापस -ENODEV;
	पूर्ण

	nau8825_init_regs(nau8825);

	अगर (i2c->irq)
		nau8825_setup_irq(nau8825);

	वापस devm_snd_soc_रेजिस्टर_component(&i2c->dev,
		&nau8825_component_driver,
		&nau8825_dai, 1);
पूर्ण

अटल पूर्णांक nau8825_i2c_हटाओ(काष्ठा i2c_client *client)
अणु
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id nau8825_i2c_ids[] = अणु
	अणु "nau8825", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, nau8825_i2c_ids);

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id nau8825_of_ids[] = अणु
	अणु .compatible = "nuvoton,nau8825", पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, nau8825_of_ids);
#पूर्ण_अगर

#अगर_घोषित CONFIG_ACPI
अटल स्थिर काष्ठा acpi_device_id nau8825_acpi_match[] = अणु
	अणु "10508825", 0 पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(acpi, nau8825_acpi_match);
#पूर्ण_अगर

अटल काष्ठा i2c_driver nau8825_driver = अणु
	.driver = अणु
		.name = "nau8825",
		.of_match_table = of_match_ptr(nau8825_of_ids),
		.acpi_match_table = ACPI_PTR(nau8825_acpi_match),
	पूर्ण,
	.probe = nau8825_i2c_probe,
	.हटाओ = nau8825_i2c_हटाओ,
	.id_table = nau8825_i2c_ids,
पूर्ण;
module_i2c_driver(nau8825_driver);

MODULE_DESCRIPTION("ASoC nau8825 driver");
MODULE_AUTHOR("Anatol Pomozov <anatol@chromium.org>");
MODULE_LICENSE("GPL");
