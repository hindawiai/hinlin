<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *   v4l2 driver क्रम TEA5777 Philips AM/FM radio tuner chips
 *
 *	Copyright (c) 2012 Hans de Goede <hdegoede@redhat.com>
 *
 *   Based on the ALSA driver क्रम TEA5757/5759 Philips AM/FM radio tuner chips:
 *
 *	Copyright (c) 2004 Jaroslav Kysela <perex@perex.cz>
 */

#समावेश <linux/delay.h>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/sched.h>
#समावेश <linux/slab.h>
#समावेश <media/v4l2-device.h>
#समावेश <media/v4l2-dev.h>
#समावेश <media/v4l2-fh.h>
#समावेश <media/v4l2-ioctl.h>
#समावेश <media/v4l2-event.h>
#समावेश "radio-tea5777.h"

MODULE_AUTHOR("Hans de Goede <perex@perex.cz>");
MODULE_DESCRIPTION("Routines for control of TEA5777 Philips AM/FM radio tuner chips");
MODULE_LICENSE("GPL");

#घोषणा TEA5777_FM_IF			150 /* kHz */
#घोषणा TEA5777_FM_FREQ_STEP		50  /* kHz */

#घोषणा TEA5777_AM_IF			21  /* kHz */
#घोषणा TEA5777_AM_FREQ_STEP		1   /* kHz */

/* Write reg, common bits */
#घोषणा TEA5777_W_MUTE_MASK		(1LL << 47)
#घोषणा TEA5777_W_MUTE_SHIFT		47
#घोषणा TEA5777_W_AM_FM_MASK		(1LL << 46)
#घोषणा TEA5777_W_AM_FM_SHIFT		46
#घोषणा TEA5777_W_STB_MASK		(1LL << 45)
#घोषणा TEA5777_W_STB_SHIFT		45

#घोषणा TEA5777_W_IFCE_MASK		(1LL << 29)
#घोषणा TEA5777_W_IFCE_SHIFT		29
#घोषणा TEA5777_W_IFW_MASK		(1LL << 28)
#घोषणा TEA5777_W_IFW_SHIFT		28
#घोषणा TEA5777_W_HILO_MASK		(1LL << 27)
#घोषणा TEA5777_W_HILO_SHIFT		27
#घोषणा TEA5777_W_DBUS_MASK		(1LL << 26)
#घोषणा TEA5777_W_DBUS_SHIFT		26

#घोषणा TEA5777_W_INTEXT_MASK		(1LL << 24)
#घोषणा TEA5777_W_INTEXT_SHIFT		24
#घोषणा TEA5777_W_P1_MASK		(1LL << 23)
#घोषणा TEA5777_W_P1_SHIFT		23
#घोषणा TEA5777_W_P0_MASK		(1LL << 22)
#घोषणा TEA5777_W_P0_SHIFT		22
#घोषणा TEA5777_W_PEN1_MASK		(1LL << 21)
#घोषणा TEA5777_W_PEN1_SHIFT		21
#घोषणा TEA5777_W_PEN0_MASK		(1LL << 20)
#घोषणा TEA5777_W_PEN0_SHIFT		20

#घोषणा TEA5777_W_CHP0_MASK		(1LL << 18)
#घोषणा TEA5777_W_CHP0_SHIFT		18
#घोषणा TEA5777_W_DEEM_MASK		(1LL << 17)
#घोषणा TEA5777_W_DEEM_SHIFT		17

#घोषणा TEA5777_W_SEARCH_MASK		(1LL << 7)
#घोषणा TEA5777_W_SEARCH_SHIFT		7
#घोषणा TEA5777_W_PROGBLIM_MASK		(1LL << 6)
#घोषणा TEA5777_W_PROGBLIM_SHIFT	6
#घोषणा TEA5777_W_UPDWN_MASK		(1LL << 5)
#घोषणा TEA5777_W_UPDWN_SHIFT		5
#घोषणा TEA5777_W_SLEV_MASK		(3LL << 3)
#घोषणा TEA5777_W_SLEV_SHIFT		3

/* Write reg, FM specअगरic bits */
#घोषणा TEA5777_W_FM_PLL_MASK		(0x1fffLL << 32)
#घोषणा TEA5777_W_FM_PLL_SHIFT		32
#घोषणा TEA5777_W_FM_FREF_MASK		(0x03LL << 30)
#घोषणा TEA5777_W_FM_FREF_SHIFT		30
#घोषणा TEA5777_W_FM_FREF_VALUE		0LL /* 50k steps, 150k IF */

#घोषणा TEA5777_W_FM_FORCEMONO_MASK	(1LL << 15)
#घोषणा TEA5777_W_FM_FORCEMONO_SHIFT	15
#घोषणा TEA5777_W_FM_SDSOFF_MASK	(1LL << 14)
#घोषणा TEA5777_W_FM_SDSOFF_SHIFT	14
#घोषणा TEA5777_W_FM_DOFF_MASK		(1LL << 13)
#घोषणा TEA5777_W_FM_DOFF_SHIFT		13

#घोषणा TEA5777_W_FM_STEP_MASK		(3LL << 1)
#घोषणा TEA5777_W_FM_STEP_SHIFT		1

/* Write reg, AM specअगरic bits */
#घोषणा TEA5777_W_AM_PLL_MASK		(0x7ffLL << 34)
#घोषणा TEA5777_W_AM_PLL_SHIFT		34
#घोषणा TEA5777_W_AM_AGCRF_MASK		(1LL << 33)
#घोषणा TEA5777_W_AM_AGCRF_SHIFT	33
#घोषणा TEA5777_W_AM_AGCIF_MASK		(1LL << 32)
#घोषणा TEA5777_W_AM_AGCIF_SHIFT	32
#घोषणा TEA5777_W_AM_MWLW_MASK		(1LL << 31)
#घोषणा TEA5777_W_AM_MWLW_SHIFT		31
#घोषणा TEA5777_W_AM_LW			0LL
#घोषणा TEA5777_W_AM_MW			1LL
#घोषणा TEA5777_W_AM_LNA_MASK		(1LL << 30)
#घोषणा TEA5777_W_AM_LNA_SHIFT		30

#घोषणा TEA5777_W_AM_PEAK_MASK		(1LL << 25)
#घोषणा TEA5777_W_AM_PEAK_SHIFT		25

#घोषणा TEA5777_W_AM_RFB_MASK		(1LL << 16)
#घोषणा TEA5777_W_AM_RFB_SHIFT		16
#घोषणा TEA5777_W_AM_CALLIGN_MASK	(1LL << 15)
#घोषणा TEA5777_W_AM_CALLIGN_SHIFT	15
#घोषणा TEA5777_W_AM_CBANK_MASK		(0x7fLL << 8)
#घोषणा TEA5777_W_AM_CBANK_SHIFT	8

#घोषणा TEA5777_W_AM_DELAY_MASK		(1LL << 2)
#घोषणा TEA5777_W_AM_DELAY_SHIFT	2
#घोषणा TEA5777_W_AM_STEP_MASK		(1LL << 1)
#घोषणा TEA5777_W_AM_STEP_SHIFT		1

/* Read reg, common bits */
#घोषणा TEA5777_R_LEVEL_MASK		(0x0f << 17)
#घोषणा TEA5777_R_LEVEL_SHIFT		17
#घोषणा TEA5777_R_SFOUND_MASK		(0x01 << 16)
#घोषणा TEA5777_R_SFOUND_SHIFT		16
#घोषणा TEA5777_R_BLIM_MASK		(0x01 << 15)
#घोषणा TEA5777_R_BLIM_SHIFT		15

/* Read reg, FM specअगरic bits */
#घोषणा TEA5777_R_FM_STEREO_MASK	(0x01 << 21)
#घोषणा TEA5777_R_FM_STEREO_SHIFT	21
#घोषणा TEA5777_R_FM_PLL_MASK		0x1fff
#घोषणा TEA5777_R_FM_PLL_SHIFT		0

क्रमागत अणु BAND_FM, BAND_AM पूर्ण;

अटल स्थिर काष्ठा v4l2_frequency_band bands[] = अणु
	अणु
		.type = V4L2_TUNER_RADIO,
		.index = 0,
		.capability = V4L2_TUNER_CAP_LOW | V4L2_TUNER_CAP_STEREO |
			      V4L2_TUNER_CAP_FREQ_BANDS |
			      V4L2_TUNER_CAP_HWSEEK_BOUNDED |
			      V4L2_TUNER_CAP_HWSEEK_PROG_LIM,
		.rangelow   =  76000 * 16,
		.rangehigh  = 108000 * 16,
		.modulation = V4L2_BAND_MODULATION_FM,
	पूर्ण,
	अणु
		.type = V4L2_TUNER_RADIO,
		.index = 1,
		.capability = V4L2_TUNER_CAP_LOW | V4L2_TUNER_CAP_FREQ_BANDS |
			      V4L2_TUNER_CAP_HWSEEK_BOUNDED |
			      V4L2_TUNER_CAP_HWSEEK_PROG_LIM,
		.rangelow   =  530 * 16,
		.rangehigh  = 1710 * 16,
		.modulation = V4L2_BAND_MODULATION_AM,
	पूर्ण,
पूर्ण;

अटल u32 tea5777_freq_to_v4l2_freq(काष्ठा radio_tea5777 *tea, u32 freq)
अणु
	चयन (tea->band) अणु
	हाल BAND_FM:
		वापस (freq * TEA5777_FM_FREQ_STEP + TEA5777_FM_IF) * 16;
	हाल BAND_AM:
		वापस (freq * TEA5777_AM_FREQ_STEP + TEA5777_AM_IF) * 16;
	पूर्ण
	वापस 0; /* Never reached */
पूर्ण

पूर्णांक radio_tea5777_set_freq(काष्ठा radio_tea5777 *tea)
अणु
	u32 freq;
	पूर्णांक res;

	freq = clamp(tea->freq, bands[tea->band].rangelow,
				bands[tea->band].rangehigh);
	freq = (freq + 8) / 16; /* to kHz */

	चयन (tea->band) अणु
	हाल BAND_FM:
		tea->ग_लिखो_reg &= ~TEA5777_W_AM_FM_MASK;
		freq = (freq - TEA5777_FM_IF) / TEA5777_FM_FREQ_STEP;
		tea->ग_लिखो_reg &= ~TEA5777_W_FM_PLL_MASK;
		tea->ग_लिखो_reg |= (u64)freq << TEA5777_W_FM_PLL_SHIFT;
		tea->ग_लिखो_reg &= ~TEA5777_W_FM_FREF_MASK;
		tea->ग_लिखो_reg |= TEA5777_W_FM_FREF_VALUE <<
				  TEA5777_W_FM_FREF_SHIFT;
		tea->ग_लिखो_reg &= ~TEA5777_W_FM_FORCEMONO_MASK;
		अगर (tea->audmode == V4L2_TUNER_MODE_MONO)
			tea->ग_लिखो_reg |= 1LL << TEA5777_W_FM_FORCEMONO_SHIFT;
		अवरोध;
	हाल BAND_AM:
		tea->ग_लिखो_reg &= ~TEA5777_W_AM_FM_MASK;
		tea->ग_लिखो_reg |= (1LL << TEA5777_W_AM_FM_SHIFT);
		freq = (freq - TEA5777_AM_IF) / TEA5777_AM_FREQ_STEP;
		tea->ग_लिखो_reg &= ~TEA5777_W_AM_PLL_MASK;
		tea->ग_लिखो_reg |= (u64)freq << TEA5777_W_AM_PLL_SHIFT;
		tea->ग_लिखो_reg &= ~TEA5777_W_AM_AGCRF_MASK;
		tea->ग_लिखो_reg &= ~TEA5777_W_AM_AGCRF_MASK;
		tea->ग_लिखो_reg &= ~TEA5777_W_AM_MWLW_MASK;
		tea->ग_लिखो_reg |= TEA5777_W_AM_MW << TEA5777_W_AM_MWLW_SHIFT;
		tea->ग_लिखो_reg &= ~TEA5777_W_AM_LNA_MASK;
		tea->ग_लिखो_reg |= 1LL << TEA5777_W_AM_LNA_SHIFT;
		tea->ग_लिखो_reg &= ~TEA5777_W_AM_PEAK_MASK;
		tea->ग_लिखो_reg |= 1LL << TEA5777_W_AM_PEAK_SHIFT;
		tea->ग_लिखो_reg &= ~TEA5777_W_AM_CALLIGN_MASK;
		अवरोध;
	पूर्ण

	res = tea->ops->ग_लिखो_reg(tea, tea->ग_लिखो_reg);
	अगर (res)
		वापस res;

	tea->needs_ग_लिखो = false;
	tea->पढ़ो_reg = -1;
	tea->freq = tea5777_freq_to_v4l2_freq(tea, freq);

	वापस 0;
पूर्ण

अटल पूर्णांक radio_tea5777_update_पढ़ो_reg(काष्ठा radio_tea5777 *tea, पूर्णांक रुको)
अणु
	पूर्णांक res;

	अगर (tea->पढ़ो_reg != -1)
		वापस 0;

	अगर (tea->ग_लिखो_beक्रमe_पढ़ो && tea->needs_ग_लिखो) अणु
		res = radio_tea5777_set_freq(tea);
		अगर (res)
			वापस res;
	पूर्ण

	अगर (रुको) अणु
		अगर (schedule_समयout_पूर्णांकerruptible(msecs_to_jअगरfies(रुको)))
			वापस -ERESTARTSYS;
	पूर्ण

	res = tea->ops->पढ़ो_reg(tea, &tea->पढ़ो_reg);
	अगर (res)
		वापस res;

	tea->needs_ग_लिखो = true;
	वापस 0;
पूर्ण

/*
 * Linux Video पूर्णांकerface
 */

अटल पूर्णांक vidioc_querycap(काष्ठा file *file, व्योम  *priv,
					काष्ठा v4l2_capability *v)
अणु
	काष्ठा radio_tea5777 *tea = video_drvdata(file);

	strscpy(v->driver, tea->v4l2_dev->name, माप(v->driver));
	strscpy(v->card, tea->card, माप(v->card));
	strlcat(v->card, " TEA5777", माप(v->card));
	strscpy(v->bus_info, tea->bus_info, माप(v->bus_info));
	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_क्रमागत_freq_bands(काष्ठा file *file, व्योम *priv,
					 काष्ठा v4l2_frequency_band *band)
अणु
	काष्ठा radio_tea5777 *tea = video_drvdata(file);

	अगर (band->tuner != 0 || band->index >= ARRAY_SIZE(bands) ||
	    (!tea->has_am && band->index == BAND_AM))
		वापस -EINVAL;

	*band = bands[band->index];
	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_g_tuner(काष्ठा file *file, व्योम *priv,
					काष्ठा v4l2_tuner *v)
अणु
	काष्ठा radio_tea5777 *tea = video_drvdata(file);
	पूर्णांक res;

	अगर (v->index > 0)
		वापस -EINVAL;

	res = radio_tea5777_update_पढ़ो_reg(tea, 0);
	अगर (res)
		वापस res;

	स_रखो(v, 0, माप(*v));
	अगर (tea->has_am)
		strscpy(v->name, "AM/FM", माप(v->name));
	अन्यथा
		strscpy(v->name, "FM", माप(v->name));
	v->type = V4L2_TUNER_RADIO;
	v->capability = V4L2_TUNER_CAP_LOW | V4L2_TUNER_CAP_STEREO |
			V4L2_TUNER_CAP_FREQ_BANDS |
			V4L2_TUNER_CAP_HWSEEK_BOUNDED |
			V4L2_TUNER_CAP_HWSEEK_PROG_LIM;
	v->rangelow   = tea->has_am ? bands[BAND_AM].rangelow :
				      bands[BAND_FM].rangelow;
	v->rangehigh  = bands[BAND_FM].rangehigh;
	अगर (tea->band == BAND_FM &&
			(tea->पढ़ो_reg & TEA5777_R_FM_STEREO_MASK))
		v->rxsubchans = V4L2_TUNER_SUB_STEREO;
	अन्यथा
		v->rxsubchans = V4L2_TUNER_SUB_MONO;
	v->audmode = tea->audmode;
	/* shअगरt - 12 to convert 4-bits (0-15) scale to 16-bits (0-65535) */
	v->संकेत = (tea->पढ़ो_reg & TEA5777_R_LEVEL_MASK) >>
		    (TEA5777_R_LEVEL_SHIFT - 12);

	/* Invalidate पढ़ो_reg, so that next call we वापस up2date संकेत */
	tea->पढ़ो_reg = -1;

	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_s_tuner(काष्ठा file *file, व्योम *priv,
					स्थिर काष्ठा v4l2_tuner *v)
अणु
	काष्ठा radio_tea5777 *tea = video_drvdata(file);
	u32 orig_audmode = tea->audmode;

	अगर (v->index)
		वापस -EINVAL;

	tea->audmode = v->audmode;
	अगर (tea->audmode > V4L2_TUNER_MODE_STEREO)
		tea->audmode = V4L2_TUNER_MODE_STEREO;

	अगर (tea->audmode != orig_audmode && tea->band == BAND_FM)
		वापस radio_tea5777_set_freq(tea);

	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_g_frequency(काष्ठा file *file, व्योम *priv,
					काष्ठा v4l2_frequency *f)
अणु
	काष्ठा radio_tea5777 *tea = video_drvdata(file);

	अगर (f->tuner != 0)
		वापस -EINVAL;
	f->type = V4L2_TUNER_RADIO;
	f->frequency = tea->freq;
	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_s_frequency(काष्ठा file *file, व्योम *priv,
					स्थिर काष्ठा v4l2_frequency *f)
अणु
	काष्ठा radio_tea5777 *tea = video_drvdata(file);

	अगर (f->tuner != 0 || f->type != V4L2_TUNER_RADIO)
		वापस -EINVAL;

	अगर (tea->has_am && f->frequency < (20000 * 16))
		tea->band = BAND_AM;
	अन्यथा
		tea->band = BAND_FM;

	tea->freq = f->frequency;
	वापस radio_tea5777_set_freq(tea);
पूर्ण

अटल पूर्णांक vidioc_s_hw_freq_seek(काष्ठा file *file, व्योम *fh,
					स्थिर काष्ठा v4l2_hw_freq_seek *a)
अणु
	काष्ठा radio_tea5777 *tea = video_drvdata(file);
	अचिन्हित दीर्घ समयout;
	u32 rangelow = a->rangelow;
	u32 rangehigh = a->rangehigh;
	पूर्णांक i, res, spacing;
	u32 orig_freq;

	अगर (a->tuner || a->wrap_around)
		वापस -EINVAL;

	अगर (file->f_flags & O_NONBLOCK)
		वापस -EWOULDBLOCK;

	अगर (rangelow || rangehigh) अणु
		क्रम (i = 0; i < ARRAY_SIZE(bands); i++) अणु
			अगर (i == BAND_AM && !tea->has_am)
				जारी;
			अगर (bands[i].rangelow  >= rangelow &&
			    bands[i].rangehigh <= rangehigh)
				अवरोध;
		पूर्ण
		अगर (i == ARRAY_SIZE(bands))
			वापस -EINVAL; /* No matching band found */

		tea->band = i;
		अगर (tea->freq < rangelow || tea->freq > rangehigh) अणु
			tea->freq = clamp(tea->freq, rangelow,
						     rangehigh);
			res = radio_tea5777_set_freq(tea);
			अगर (res)
				वापस res;
		पूर्ण
	पूर्ण अन्यथा अणु
		rangelow  = bands[tea->band].rangelow;
		rangehigh = bands[tea->band].rangehigh;
	पूर्ण

	spacing   = (tea->band == BAND_AM) ? (5 * 16) : (200 * 16); /* kHz */
	orig_freq = tea->freq;

	tea->ग_लिखो_reg |= TEA5777_W_PROGBLIM_MASK;
	अगर (tea->seek_rangelow != rangelow) अणु
		tea->ग_लिखो_reg &= ~TEA5777_W_UPDWN_MASK;
		tea->freq = rangelow;
		res = radio_tea5777_set_freq(tea);
		अगर (res)
			जाओ leave;
		tea->seek_rangelow = rangelow;
	पूर्ण
	अगर (tea->seek_rangehigh != rangehigh) अणु
		tea->ग_लिखो_reg |= TEA5777_W_UPDWN_MASK;
		tea->freq = rangehigh;
		res = radio_tea5777_set_freq(tea);
		अगर (res)
			जाओ leave;
		tea->seek_rangehigh = rangehigh;
	पूर्ण
	tea->ग_लिखो_reg &= ~TEA5777_W_PROGBLIM_MASK;

	tea->ग_लिखो_reg |= TEA5777_W_SEARCH_MASK;
	अगर (a->seek_upward) अणु
		tea->ग_लिखो_reg |= TEA5777_W_UPDWN_MASK;
		tea->freq = orig_freq + spacing;
	पूर्ण अन्यथा अणु
		tea->ग_लिखो_reg &= ~TEA5777_W_UPDWN_MASK;
		tea->freq = orig_freq - spacing;
	पूर्ण
	res = radio_tea5777_set_freq(tea);
	अगर (res)
		जाओ leave;

	समयout = jअगरfies + msecs_to_jअगरfies(5000);
	क्रम (;;) अणु
		अगर (समय_after(jअगरfies, समयout)) अणु
			res = -ENODATA;
			अवरोध;
		पूर्ण

		res = radio_tea5777_update_पढ़ो_reg(tea, 100);
		अगर (res)
			अवरोध;

		/*
		 * Note we use tea->freq to track how far we've searched sofar
		 * this is necessary to ensure we जारी seeking at the right
		 * poपूर्णांक, in the ग_लिखो_beक्रमe_पढ़ो हाल.
		 */
		tea->freq = (tea->पढ़ो_reg & TEA5777_R_FM_PLL_MASK);
		tea->freq = tea5777_freq_to_v4l2_freq(tea, tea->freq);

		अगर ((tea->पढ़ो_reg & TEA5777_R_SFOUND_MASK)) अणु
			tea->ग_लिखो_reg &= ~TEA5777_W_SEARCH_MASK;
			वापस 0;
		पूर्ण

		अगर (tea->पढ़ो_reg & TEA5777_R_BLIM_MASK) अणु
			res = -ENODATA;
			अवरोध;
		पूर्ण

		/* Force पढ़ो_reg update */
		tea->पढ़ो_reg = -1;
	पूर्ण
leave:
	tea->ग_लिखो_reg &= ~TEA5777_W_PROGBLIM_MASK;
	tea->ग_लिखो_reg &= ~TEA5777_W_SEARCH_MASK;
	tea->freq = orig_freq;
	radio_tea5777_set_freq(tea);
	वापस res;
पूर्ण

अटल पूर्णांक tea575x_s_ctrl(काष्ठा v4l2_ctrl *c)
अणु
	काष्ठा radio_tea5777 *tea =
		container_of(c->handler, काष्ठा radio_tea5777, ctrl_handler);

	चयन (c->id) अणु
	हाल V4L2_CID_AUDIO_MUTE:
		अगर (c->val)
			tea->ग_लिखो_reg |= TEA5777_W_MUTE_MASK;
		अन्यथा
			tea->ग_लिखो_reg &= ~TEA5777_W_MUTE_MASK;

		वापस radio_tea5777_set_freq(tea);
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल स्थिर काष्ठा v4l2_file_operations tea575x_fops = अणु
	.unlocked_ioctl	= video_ioctl2,
	.खोलो		= v4l2_fh_खोलो,
	.release	= v4l2_fh_release,
	.poll		= v4l2_ctrl_poll,
पूर्ण;

अटल स्थिर काष्ठा v4l2_ioctl_ops tea575x_ioctl_ops = अणु
	.vidioc_querycap    = vidioc_querycap,
	.vidioc_g_tuner     = vidioc_g_tuner,
	.vidioc_s_tuner     = vidioc_s_tuner,
	.vidioc_g_frequency = vidioc_g_frequency,
	.vidioc_s_frequency = vidioc_s_frequency,
	.vidioc_s_hw_freq_seek = vidioc_s_hw_freq_seek,
	.vidioc_क्रमागत_freq_bands = vidioc_क्रमागत_freq_bands,
	.vidioc_log_status  = v4l2_ctrl_log_status,
	.vidioc_subscribe_event = v4l2_ctrl_subscribe_event,
	.vidioc_unsubscribe_event = v4l2_event_unsubscribe,
पूर्ण;

अटल स्थिर काष्ठा video_device tea575x_radio = अणु
	.ioctl_ops	= &tea575x_ioctl_ops,
	.release	= video_device_release_empty,
पूर्ण;

अटल स्थिर काष्ठा v4l2_ctrl_ops tea575x_ctrl_ops = अणु
	.s_ctrl = tea575x_s_ctrl,
पूर्ण;

पूर्णांक radio_tea5777_init(काष्ठा radio_tea5777 *tea, काष्ठा module *owner)
अणु
	पूर्णांक res;

	tea->ग_लिखो_reg = (1LL << TEA5777_W_IFCE_SHIFT) |
			 (1LL << TEA5777_W_IFW_SHIFT) |
			 (1LL << TEA5777_W_INTEXT_SHIFT) |
			 (1LL << TEA5777_W_CHP0_SHIFT) |
			 (1LL << TEA5777_W_SLEV_SHIFT);
	tea->freq = 90500 * 16;	/* 90.5Mhz शेष */
	tea->audmode = V4L2_TUNER_MODE_STEREO;
	res = radio_tea5777_set_freq(tea);
	अगर (res) अणु
		v4l2_err(tea->v4l2_dev, "can't set initial freq (%d)\n", res);
		वापस res;
	पूर्ण

	tea->vd = tea575x_radio;
	video_set_drvdata(&tea->vd, tea);
	mutex_init(&tea->mutex);
	strscpy(tea->vd.name, tea->v4l2_dev->name, माप(tea->vd.name));
	tea->vd.lock = &tea->mutex;
	tea->vd.v4l2_dev = tea->v4l2_dev;
	tea->vd.device_caps = V4L2_CAP_TUNER | V4L2_CAP_RADIO |
			      V4L2_CAP_HW_FREQ_SEEK;
	tea->fops = tea575x_fops;
	tea->fops.owner = owner;
	tea->vd.fops = &tea->fops;

	tea->vd.ctrl_handler = &tea->ctrl_handler;
	v4l2_ctrl_handler_init(&tea->ctrl_handler, 1);
	v4l2_ctrl_new_std(&tea->ctrl_handler, &tea575x_ctrl_ops,
			  V4L2_CID_AUDIO_MUTE, 0, 1, 1, 1);
	res = tea->ctrl_handler.error;
	अगर (res) अणु
		v4l2_err(tea->v4l2_dev, "can't initialize controls\n");
		v4l2_ctrl_handler_मुक्त(&tea->ctrl_handler);
		वापस res;
	पूर्ण
	v4l2_ctrl_handler_setup(&tea->ctrl_handler);

	res = video_रेजिस्टर_device(&tea->vd, VFL_TYPE_RADIO, -1);
	अगर (res) अणु
		v4l2_err(tea->v4l2_dev, "can't register video device!\n");
		v4l2_ctrl_handler_मुक्त(tea->vd.ctrl_handler);
		वापस res;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(radio_tea5777_init);

व्योम radio_tea5777_निकास(काष्ठा radio_tea5777 *tea)
अणु
	video_unरेजिस्टर_device(&tea->vd);
	v4l2_ctrl_handler_मुक्त(tea->vd.ctrl_handler);
पूर्ण
EXPORT_SYMBOL_GPL(radio_tea5777_निकास);
