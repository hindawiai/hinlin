<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *   ALSA driver क्रम TEA5757/5759 Philips AM/FM radio tuner chips
 *
 *	Copyright (c) 2004 Jaroslav Kysela <perex@perex.cz>
 */

#समावेश <linux/delay.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/sched.h>
#समावेश <यंत्र/पन.स>
#समावेश <media/v4l2-device.h>
#समावेश <media/v4l2-dev.h>
#समावेश <media/v4l2-fh.h>
#समावेश <media/v4l2-ioctl.h>
#समावेश <media/v4l2-event.h>
#समावेश <media/drv-पूर्णांकf/tea575x.h>

MODULE_AUTHOR("Jaroslav Kysela <perex@perex.cz>");
MODULE_DESCRIPTION("Routines for control of TEA5757/5759 Philips AM/FM radio tuner chips");
MODULE_LICENSE("GPL");

/*
 * definitions
 */

#घोषणा TEA575X_BIT_SEARCH	(1<<24)		/* 1 = search action, 0 = tuned */
#घोषणा TEA575X_BIT_UPDOWN	(1<<23)		/* 0 = search करोwn, 1 = search up */
#घोषणा TEA575X_BIT_MONO	(1<<22)		/* 0 = stereo, 1 = mono */
#घोषणा TEA575X_BIT_BAND_MASK	(3<<20)
#घोषणा TEA575X_BIT_BAND_FM	(0<<20)
#घोषणा TEA575X_BIT_BAND_MW	(1<<20)
#घोषणा TEA575X_BIT_BAND_LW	(2<<20)
#घोषणा TEA575X_BIT_BAND_SW	(3<<20)
#घोषणा TEA575X_BIT_PORT_0	(1<<19)		/* user bit */
#घोषणा TEA575X_BIT_PORT_1	(1<<18)		/* user bit */
#घोषणा TEA575X_BIT_SEARCH_MASK	(3<<16)		/* search level */
#घोषणा TEA575X_BIT_SEARCH_5_28	     (0<<16)	/* FM >5uV, AM >28uV */
#घोषणा TEA575X_BIT_SEARCH_10_40     (1<<16)	/* FM >10uV, AM > 40uV */
#घोषणा TEA575X_BIT_SEARCH_30_63     (2<<16)	/* FM >30uV, AM > 63uV */
#घोषणा TEA575X_BIT_SEARCH_150_1000  (3<<16)	/* FM > 150uV, AM > 1000uV */
#घोषणा TEA575X_BIT_DUMMY	(1<<15)		/* buffer */
#घोषणा TEA575X_BIT_FREQ_MASK	0x7fff

क्रमागत अणु BAND_FM, BAND_FM_JAPAN, BAND_AM पूर्ण;

अटल स्थिर काष्ठा v4l2_frequency_band bands[] = अणु
	अणु
		.type = V4L2_TUNER_RADIO,
		.index = 0,
		.capability = V4L2_TUNER_CAP_LOW | V4L2_TUNER_CAP_STEREO |
			      V4L2_TUNER_CAP_FREQ_BANDS,
		.rangelow   =  87500 * 16,
		.rangehigh  = 108000 * 16,
		.modulation = V4L2_BAND_MODULATION_FM,
	पूर्ण,
	अणु
		.type = V4L2_TUNER_RADIO,
		.index = 0,
		.capability = V4L2_TUNER_CAP_LOW | V4L2_TUNER_CAP_STEREO |
			      V4L2_TUNER_CAP_FREQ_BANDS,
		.rangelow   = 76000 * 16,
		.rangehigh  = 91000 * 16,
		.modulation = V4L2_BAND_MODULATION_FM,
	पूर्ण,
	अणु
		.type = V4L2_TUNER_RADIO,
		.index = 1,
		.capability = V4L2_TUNER_CAP_LOW | V4L2_TUNER_CAP_FREQ_BANDS,
		.rangelow   =  530 * 16,
		.rangehigh  = 1710 * 16,
		.modulation = V4L2_BAND_MODULATION_AM,
	पूर्ण,
पूर्ण;

/*
 * lowlevel part
 */

अटल व्योम snd_tea575x_ग_लिखो(काष्ठा snd_tea575x *tea, अचिन्हित पूर्णांक val)
अणु
	u16 l;
	u8 data;

	अगर (tea->ops->ग_लिखो_val)
		वापस tea->ops->ग_लिखो_val(tea, val);

	tea->ops->set_direction(tea, 1);
	udelay(16);

	क्रम (l = 25; l > 0; l--) अणु
		data = (val >> 24) & TEA575X_DATA;
		val <<= 1;			/* shअगरt data */
		tea->ops->set_pins(tea, data | TEA575X_WREN);
		udelay(2);
		tea->ops->set_pins(tea, data | TEA575X_WREN | TEA575X_CLK);
		udelay(2);
		tea->ops->set_pins(tea, data | TEA575X_WREN);
		udelay(2);
	पूर्ण

	अगर (!tea->mute)
		tea->ops->set_pins(tea, 0);
पूर्ण

अटल u32 snd_tea575x_पढ़ो(काष्ठा snd_tea575x *tea)
अणु
	u16 l, rdata;
	u32 data = 0;

	अगर (tea->ops->पढ़ो_val)
		वापस tea->ops->पढ़ो_val(tea);

	tea->ops->set_direction(tea, 0);
	tea->ops->set_pins(tea, 0);
	udelay(16);

	क्रम (l = 24; l--;) अणु
		tea->ops->set_pins(tea, TEA575X_CLK);
		udelay(2);
		अगर (!l)
			tea->tuned = tea->ops->get_pins(tea) & TEA575X_MOST ? 0 : 1;
		tea->ops->set_pins(tea, 0);
		udelay(2);
		data <<= 1;			/* shअगरt data */
		rdata = tea->ops->get_pins(tea);
		अगर (!l)
			tea->stereo = (rdata & TEA575X_MOST) ?  0 : 1;
		अगर (rdata & TEA575X_DATA)
			data++;
		udelay(2);
	पूर्ण

	अगर (tea->mute)
		tea->ops->set_pins(tea, TEA575X_WREN);

	वापस data;
पूर्ण

अटल u32 snd_tea575x_val_to_freq(काष्ठा snd_tea575x *tea, u32 val)
अणु
	u32 freq = val & TEA575X_BIT_FREQ_MASK;

	अगर (freq == 0)
		वापस freq;

	चयन (tea->band) अणु
	हाल BAND_FM:
		/* freq *= 12.5 */
		freq *= 125;
		freq /= 10;
		/* crystal fixup */
		freq -= TEA575X_FMIF;
		अवरोध;
	हाल BAND_FM_JAPAN:
		/* freq *= 12.5 */
		freq *= 125;
		freq /= 10;
		/* crystal fixup */
		freq += TEA575X_FMIF;
		अवरोध;
	हाल BAND_AM:
		/* crystal fixup */
		freq -= TEA575X_AMIF;
		अवरोध;
	पूर्ण

	वापस clamp(freq * 16, bands[tea->band].rangelow,
				bands[tea->band].rangehigh); /* from kHz */
पूर्ण

अटल u32 snd_tea575x_get_freq(काष्ठा snd_tea575x *tea)
अणु
	वापस snd_tea575x_val_to_freq(tea, snd_tea575x_पढ़ो(tea));
पूर्ण

व्योम snd_tea575x_set_freq(काष्ठा snd_tea575x *tea)
अणु
	u32 freq = tea->freq / 16;	/* to kHz */
	u32 band = 0;

	चयन (tea->band) अणु
	हाल BAND_FM:
		band = TEA575X_BIT_BAND_FM;
		/* crystal fixup */
		freq += TEA575X_FMIF;
		/* freq /= 12.5 */
		freq *= 10;
		freq /= 125;
		अवरोध;
	हाल BAND_FM_JAPAN:
		band = TEA575X_BIT_BAND_FM;
		/* crystal fixup */
		freq -= TEA575X_FMIF;
		/* freq /= 12.5 */
		freq *= 10;
		freq /= 125;
		अवरोध;
	हाल BAND_AM:
		band = TEA575X_BIT_BAND_MW;
		/* crystal fixup */
		freq += TEA575X_AMIF;
		अवरोध;
	पूर्ण

	tea->val &= ~(TEA575X_BIT_FREQ_MASK | TEA575X_BIT_BAND_MASK);
	tea->val |= band;
	tea->val |= freq & TEA575X_BIT_FREQ_MASK;
	snd_tea575x_ग_लिखो(tea, tea->val);
	tea->freq = snd_tea575x_val_to_freq(tea, tea->val);
पूर्ण
EXPORT_SYMBOL(snd_tea575x_set_freq);

/*
 * Linux Video पूर्णांकerface
 */

अटल पूर्णांक vidioc_querycap(काष्ठा file *file, व्योम  *priv,
					काष्ठा v4l2_capability *v)
अणु
	काष्ठा snd_tea575x *tea = video_drvdata(file);

	strscpy(v->driver, tea->v4l2_dev->name, माप(v->driver));
	strscpy(v->card, tea->card, माप(v->card));
	strlcat(v->card, tea->tea5759 ? " TEA5759" : " TEA5757", माप(v->card));
	strscpy(v->bus_info, tea->bus_info, माप(v->bus_info));
	वापस 0;
पूर्ण

पूर्णांक snd_tea575x_क्रमागत_freq_bands(काष्ठा snd_tea575x *tea,
					काष्ठा v4l2_frequency_band *band)
अणु
	पूर्णांक index;

	अगर (band->tuner != 0)
		वापस -EINVAL;

	चयन (band->index) अणु
	हाल 0:
		अगर (tea->tea5759)
			index = BAND_FM_JAPAN;
		अन्यथा
			index = BAND_FM;
		अवरोध;
	हाल 1:
		अगर (tea->has_am) अणु
			index = BAND_AM;
			अवरोध;
		पूर्ण
		fallthrough;
	शेष:
		वापस -EINVAL;
	पूर्ण

	*band = bands[index];
	अगर (!tea->cannot_पढ़ो_data)
		band->capability |= V4L2_TUNER_CAP_HWSEEK_BOUNDED;

	वापस 0;
पूर्ण
EXPORT_SYMBOL(snd_tea575x_क्रमागत_freq_bands);

अटल पूर्णांक vidioc_क्रमागत_freq_bands(काष्ठा file *file, व्योम *priv,
					 काष्ठा v4l2_frequency_band *band)
अणु
	काष्ठा snd_tea575x *tea = video_drvdata(file);

	वापस snd_tea575x_क्रमागत_freq_bands(tea, band);
पूर्ण

पूर्णांक snd_tea575x_g_tuner(काष्ठा snd_tea575x *tea, काष्ठा v4l2_tuner *v)
अणु
	काष्ठा v4l2_frequency_band band_fm = अणु 0, पूर्ण;

	अगर (v->index > 0)
		वापस -EINVAL;

	snd_tea575x_पढ़ो(tea);
	snd_tea575x_क्रमागत_freq_bands(tea, &band_fm);

	स_रखो(v, 0, माप(*v));
	strscpy(v->name, tea->has_am ? "FM/AM" : "FM", माप(v->name));
	v->type = V4L2_TUNER_RADIO;
	v->capability = band_fm.capability;
	v->rangelow = tea->has_am ? bands[BAND_AM].rangelow : band_fm.rangelow;
	v->rangehigh = band_fm.rangehigh;
	v->rxsubchans = tea->stereo ? V4L2_TUNER_SUB_STEREO : V4L2_TUNER_SUB_MONO;
	v->audmode = (tea->val & TEA575X_BIT_MONO) ?
		V4L2_TUNER_MODE_MONO : V4L2_TUNER_MODE_STEREO;
	v->संकेत = tea->tuned ? 0xffff : 0;
	वापस 0;
पूर्ण
EXPORT_SYMBOL(snd_tea575x_g_tuner);

अटल पूर्णांक vidioc_g_tuner(काष्ठा file *file, व्योम *priv,
					काष्ठा v4l2_tuner *v)
अणु
	काष्ठा snd_tea575x *tea = video_drvdata(file);

	वापस snd_tea575x_g_tuner(tea, v);
पूर्ण

अटल पूर्णांक vidioc_s_tuner(काष्ठा file *file, व्योम *priv,
					स्थिर काष्ठा v4l2_tuner *v)
अणु
	काष्ठा snd_tea575x *tea = video_drvdata(file);
	u32 orig_val = tea->val;

	अगर (v->index)
		वापस -EINVAL;
	tea->val &= ~TEA575X_BIT_MONO;
	अगर (v->audmode == V4L2_TUNER_MODE_MONO)
		tea->val |= TEA575X_BIT_MONO;
	/* Only apply changes अगर currently tuning FM */
	अगर (tea->band != BAND_AM && tea->val != orig_val)
		snd_tea575x_set_freq(tea);

	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_g_frequency(काष्ठा file *file, व्योम *priv,
					काष्ठा v4l2_frequency *f)
अणु
	काष्ठा snd_tea575x *tea = video_drvdata(file);

	अगर (f->tuner != 0)
		वापस -EINVAL;
	f->type = V4L2_TUNER_RADIO;
	f->frequency = tea->freq;
	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_s_frequency(काष्ठा file *file, व्योम *priv,
					स्थिर काष्ठा v4l2_frequency *f)
अणु
	काष्ठा snd_tea575x *tea = video_drvdata(file);

	अगर (f->tuner != 0 || f->type != V4L2_TUNER_RADIO)
		वापस -EINVAL;

	अगर (tea->has_am && f->frequency < (20000 * 16))
		tea->band = BAND_AM;
	अन्यथा अगर (tea->tea5759)
		tea->band = BAND_FM_JAPAN;
	अन्यथा
		tea->band = BAND_FM;

	tea->freq = clamp_t(u32, f->frequency, bands[tea->band].rangelow,
					bands[tea->band].rangehigh);
	snd_tea575x_set_freq(tea);
	वापस 0;
पूर्ण

पूर्णांक snd_tea575x_s_hw_freq_seek(काष्ठा file *file, काष्ठा snd_tea575x *tea,
				स्थिर काष्ठा v4l2_hw_freq_seek *a)
अणु
	अचिन्हित दीर्घ समयout;
	पूर्णांक i, spacing;

	अगर (tea->cannot_पढ़ो_data)
		वापस -ENOTTY;
	अगर (a->tuner || a->wrap_around)
		वापस -EINVAL;

	अगर (file->f_flags & O_NONBLOCK)
		वापस -EWOULDBLOCK;

	अगर (a->rangelow || a->rangehigh) अणु
		क्रम (i = 0; i < ARRAY_SIZE(bands); i++) अणु
			अगर ((i == BAND_FM && tea->tea5759) ||
			    (i == BAND_FM_JAPAN && !tea->tea5759) ||
			    (i == BAND_AM && !tea->has_am))
				जारी;
			अगर (bands[i].rangelow  == a->rangelow &&
			    bands[i].rangehigh == a->rangehigh)
				अवरोध;
		पूर्ण
		अगर (i == ARRAY_SIZE(bands))
			वापस -EINVAL; /* No matching band found */
		अगर (i != tea->band) अणु
			tea->band = i;
			tea->freq = clamp(tea->freq, bands[i].rangelow,
						     bands[i].rangehigh);
			snd_tea575x_set_freq(tea);
		पूर्ण
	पूर्ण

	spacing = (tea->band == BAND_AM) ? 5 : 50; /* kHz */

	/* clear the frequency, HW will fill it in */
	tea->val &= ~TEA575X_BIT_FREQ_MASK;
	tea->val |= TEA575X_BIT_SEARCH;
	अगर (a->seek_upward)
		tea->val |= TEA575X_BIT_UPDOWN;
	अन्यथा
		tea->val &= ~TEA575X_BIT_UPDOWN;
	snd_tea575x_ग_लिखो(tea, tea->val);
	समयout = jअगरfies + msecs_to_jअगरfies(10000);
	क्रम (;;) अणु
		अगर (समय_after(jअगरfies, समयout))
			अवरोध;
		अगर (schedule_समयout_पूर्णांकerruptible(msecs_to_jअगरfies(10))) अणु
			/* some संकेत arrived, stop search */
			tea->val &= ~TEA575X_BIT_SEARCH;
			snd_tea575x_set_freq(tea);
			वापस -ERESTARTSYS;
		पूर्ण
		अगर (!(snd_tea575x_पढ़ो(tea) & TEA575X_BIT_SEARCH)) अणु
			u32 freq;

			/* Found a frequency, रुको until it can be पढ़ो */
			क्रम (i = 0; i < 100; i++) अणु
				msleep(10);
				freq = snd_tea575x_get_freq(tea);
				अगर (freq) /* available */
					अवरोध;
			पूर्ण
			अगर (freq == 0) /* shouldn't happen */
				अवरोध;
			/*
			 * अगर we moved by less than the spacing, or in the
			 * wrong direction, जारी seeking
			 */
			अगर (असल(tea->freq - freq) < 16 * spacing ||
					(a->seek_upward && freq < tea->freq) ||
					(!a->seek_upward && freq > tea->freq)) अणु
				snd_tea575x_ग_लिखो(tea, tea->val);
				जारी;
			पूर्ण
			tea->freq = freq;
			tea->val &= ~TEA575X_BIT_SEARCH;
			वापस 0;
		पूर्ण
	पूर्ण
	tea->val &= ~TEA575X_BIT_SEARCH;
	snd_tea575x_set_freq(tea);
	वापस -ENODATA;
पूर्ण
EXPORT_SYMBOL(snd_tea575x_s_hw_freq_seek);

अटल पूर्णांक vidioc_s_hw_freq_seek(काष्ठा file *file, व्योम *fh,
					स्थिर काष्ठा v4l2_hw_freq_seek *a)
अणु
	काष्ठा snd_tea575x *tea = video_drvdata(file);

	वापस snd_tea575x_s_hw_freq_seek(file, tea, a);
पूर्ण

अटल पूर्णांक tea575x_s_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा snd_tea575x *tea = container_of(ctrl->handler, काष्ठा snd_tea575x, ctrl_handler);

	चयन (ctrl->id) अणु
	हाल V4L2_CID_AUDIO_MUTE:
		tea->mute = ctrl->val;
		snd_tea575x_set_freq(tea);
		वापस 0;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल स्थिर काष्ठा v4l2_file_operations tea575x_fops = अणु
	.unlocked_ioctl	= video_ioctl2,
	.खोलो           = v4l2_fh_खोलो,
	.release        = v4l2_fh_release,
	.poll           = v4l2_ctrl_poll,
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
	.release        = video_device_release_empty,
पूर्ण;

अटल स्थिर काष्ठा v4l2_ctrl_ops tea575x_ctrl_ops = अणु
	.s_ctrl = tea575x_s_ctrl,
पूर्ण;


पूर्णांक snd_tea575x_hw_init(काष्ठा snd_tea575x *tea)
अणु
	tea->mute = true;

	/* Not all devices can or know how to पढ़ो the data back.
	   Such devices can set cannot_पढ़ो_data to true. */
	अगर (!tea->cannot_पढ़ो_data) अणु
		snd_tea575x_ग_लिखो(tea, 0x55AA);
		अगर (snd_tea575x_पढ़ो(tea) != 0x55AA)
			वापस -ENODEV;
	पूर्ण

	tea->val = TEA575X_BIT_BAND_FM | TEA575X_BIT_SEARCH_5_28;
	tea->freq = 90500 * 16;		/* 90.5Mhz शेष */
	snd_tea575x_set_freq(tea);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(snd_tea575x_hw_init);

पूर्णांक snd_tea575x_init(काष्ठा snd_tea575x *tea, काष्ठा module *owner)
अणु
	पूर्णांक retval = snd_tea575x_hw_init(tea);

	अगर (retval)
		वापस retval;

	tea->vd = tea575x_radio;
	video_set_drvdata(&tea->vd, tea);
	mutex_init(&tea->mutex);
	strscpy(tea->vd.name, tea->v4l2_dev->name, माप(tea->vd.name));
	tea->vd.lock = &tea->mutex;
	tea->vd.v4l2_dev = tea->v4l2_dev;
	tea->vd.device_caps = V4L2_CAP_TUNER | V4L2_CAP_RADIO;
	अगर (!tea->cannot_पढ़ो_data)
		tea->vd.device_caps |= V4L2_CAP_HW_FREQ_SEEK;
	tea->fops = tea575x_fops;
	tea->fops.owner = owner;
	tea->vd.fops = &tea->fops;
	/* disable hw_freq_seek अगर we can't use it */
	अगर (tea->cannot_पढ़ो_data)
		v4l2_disable_ioctl(&tea->vd, VIDIOC_S_HW_FREQ_SEEK);

	अगर (!tea->cannot_mute) अणु
		tea->vd.ctrl_handler = &tea->ctrl_handler;
		v4l2_ctrl_handler_init(&tea->ctrl_handler, 1);
		v4l2_ctrl_new_std(&tea->ctrl_handler, &tea575x_ctrl_ops,
				  V4L2_CID_AUDIO_MUTE, 0, 1, 1, 1);
		retval = tea->ctrl_handler.error;
		अगर (retval) अणु
			v4l2_err(tea->v4l2_dev, "can't initialize controls\n");
			v4l2_ctrl_handler_मुक्त(&tea->ctrl_handler);
			वापस retval;
		पूर्ण

		अगर (tea->ext_init) अणु
			retval = tea->ext_init(tea);
			अगर (retval) अणु
				v4l2_ctrl_handler_मुक्त(&tea->ctrl_handler);
				वापस retval;
			पूर्ण
		पूर्ण

		v4l2_ctrl_handler_setup(&tea->ctrl_handler);
	पूर्ण

	retval = video_रेजिस्टर_device(&tea->vd, VFL_TYPE_RADIO, tea->radio_nr);
	अगर (retval) अणु
		v4l2_err(tea->v4l2_dev, "can't register video device!\n");
		v4l2_ctrl_handler_मुक्त(tea->vd.ctrl_handler);
		वापस retval;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL(snd_tea575x_init);

व्योम snd_tea575x_निकास(काष्ठा snd_tea575x *tea)
अणु
	video_unरेजिस्टर_device(&tea->vd);
	v4l2_ctrl_handler_मुक्त(tea->vd.ctrl_handler);
पूर्ण
EXPORT_SYMBOL(snd_tea575x_निकास);
