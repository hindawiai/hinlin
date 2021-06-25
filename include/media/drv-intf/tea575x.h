<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
#अगर_अघोषित __SOUND_TEA575X_TUNER_H
#घोषणा __SOUND_TEA575X_TUNER_H

/*
 *   ALSA driver क्रम TEA5757/5759 Philips AM/FM tuner chips
 *
 *	Copyright (c) 2004 Jaroslav Kysela <perex@perex.cz>
 */

#समावेश <linux/videodev2.h>
#समावेश <media/v4l2-ctrls.h>
#समावेश <media/v4l2-dev.h>
#समावेश <media/v4l2-device.h>

#घोषणा TEA575X_FMIF	10700
#घोषणा TEA575X_AMIF	  450

#घोषणा TEA575X_DATA	(1 << 0)
#घोषणा TEA575X_CLK	(1 << 1)
#घोषणा TEA575X_WREN	(1 << 2)
#घोषणा TEA575X_MOST	(1 << 3)

काष्ठा snd_tea575x;

काष्ठा snd_tea575x_ops अणु
	/* Drivers using snd_tea575x must either define पढ़ो_ and ग_लिखो_val */
	व्योम (*ग_लिखो_val)(काष्ठा snd_tea575x *tea, u32 val);
	u32 (*पढ़ो_val)(काष्ठा snd_tea575x *tea);
	/* Or define the 3 pin functions */
	व्योम (*set_pins)(काष्ठा snd_tea575x *tea, u8 pins);
	u8 (*get_pins)(काष्ठा snd_tea575x *tea);
	व्योम (*set_direction)(काष्ठा snd_tea575x *tea, bool output);
पूर्ण;

काष्ठा snd_tea575x अणु
	काष्ठा v4l2_device *v4l2_dev;
	काष्ठा v4l2_file_operations fops;
	काष्ठा video_device vd;		/* video device */
	पूर्णांक radio_nr;			/* radio_nr */
	bool tea5759;			/* 5759 chip is present */
	bool has_am;			/* Device can tune to AM freqs */
	bool cannot_पढ़ो_data;		/* Device cannot पढ़ो the data pin */
	bool cannot_mute;		/* Device cannot mute */
	bool mute;			/* Device is muted? */
	bool stereo;			/* receiving stereo */
	bool tuned;			/* tuned to a station */
	अचिन्हित पूर्णांक val;		/* hw value */
	u32 band;			/* 0: FM, 1: FM-Japan, 2: AM */
	u32 freq;			/* frequency */
	काष्ठा mutex mutex;
	स्थिर काष्ठा snd_tea575x_ops *ops;
	व्योम *निजी_data;
	u8 card[32];
	u8 bus_info[32];
	काष्ठा v4l2_ctrl_handler ctrl_handler;
	पूर्णांक (*ext_init)(काष्ठा snd_tea575x *tea);
पूर्ण;

पूर्णांक snd_tea575x_क्रमागत_freq_bands(काष्ठा snd_tea575x *tea,
					काष्ठा v4l2_frequency_band *band);
पूर्णांक snd_tea575x_g_tuner(काष्ठा snd_tea575x *tea, काष्ठा v4l2_tuner *v);
पूर्णांक snd_tea575x_s_hw_freq_seek(काष्ठा file *file, काष्ठा snd_tea575x *tea,
				स्थिर काष्ठा v4l2_hw_freq_seek *a);
पूर्णांक snd_tea575x_hw_init(काष्ठा snd_tea575x *tea);
पूर्णांक snd_tea575x_init(काष्ठा snd_tea575x *tea, काष्ठा module *owner);
व्योम snd_tea575x_निकास(काष्ठा snd_tea575x *tea);
व्योम snd_tea575x_set_freq(काष्ठा snd_tea575x *tea);

#पूर्ण_अगर /* __SOUND_TEA575X_TUNER_H */
