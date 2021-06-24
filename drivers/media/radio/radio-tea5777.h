<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
#अगर_अघोषित __RADIO_TEA5777_H
#घोषणा __RADIO_TEA5777_H

/*
 *   v4l2 driver क्रम TEA5777 Philips AM/FM radio tuner chips
 *
 *	Copyright (c) 2012 Hans de Goede <hdegoede@redhat.com>
 *
 *   Based on the ALSA driver क्रम TEA5757/5759 Philips AM/FM radio tuner chips:
 *
 *	Copyright (c) 2004 Jaroslav Kysela <perex@perex.cz>
 *	Copyright (c) 2012 Hans de Goede <hdegoede@redhat.com>
 */

#समावेश <linux/videodev2.h>
#समावेश <media/v4l2-ctrls.h>
#समावेश <media/v4l2-dev.h>
#समावेश <media/v4l2-device.h>

#घोषणा TEA575X_FMIF	10700
#घोषणा TEA575X_AMIF	  450

काष्ठा radio_tea5777;

काष्ठा radio_tea5777_ops अणु
	/*
	 * Write the 6 bytes large ग_लिखो रेजिस्टर of the tea5777
	 *
	 * val represents the 6 ग_लिखो रेजिस्टरs, with byte 1 from the
	 * datasheet being the most signअगरicant byte (so byte 5 of the u64),
	 * and byte 6 from the datasheet being the least signअगरicant byte.
	 *
	 * वापसs 0 on success.
	 */
	पूर्णांक (*ग_लिखो_reg)(काष्ठा radio_tea5777 *tea, u64 val);
	/*
	 * Read the 3 bytes large पढ़ो रेजिस्टर of the tea5777
	 *
	 * The पढ़ो value माला_लो वापसed in val, akin to ग_लिखो_reg, byte 1 from
	 * the datasheet is stored as the most signअगरicant byte (so byte 2 of
	 * the u32), and byte 3 from the datasheet माला_लो stored as the least
	 * signअगरicant byte (iow byte 0 of the u32).
	 *
	 * वापसs 0 on success.
	 */
	पूर्णांक (*पढ़ो_reg)(काष्ठा radio_tea5777 *tea, u32 *val);
पूर्ण;

काष्ठा radio_tea5777 अणु
	काष्ठा v4l2_device *v4l2_dev;
	काष्ठा v4l2_file_operations fops;
	काष्ठा video_device vd;		/* video device */
	bool has_am;			/* Device can tune to AM freqs */
	bool ग_लिखो_beक्रमe_पढ़ो;		/* must ग_लिखो beक्रमe पढ़ो quirk */
	bool needs_ग_लिखो;		/* क्रम ग_लिखो beक्रमe पढ़ो quirk */
	u32 band;			/* current band */
	u32 freq;			/* current frequency */
	u32 audmode;			/* last set audmode */
	u32 seek_rangelow;		/* current hwseek limits */
	u32 seek_rangehigh;
	u32 पढ़ो_reg;
	u64 ग_लिखो_reg;
	काष्ठा mutex mutex;
	स्थिर काष्ठा radio_tea5777_ops *ops;
	व्योम *निजी_data;
	u8 card[32];
	u8 bus_info[32];
	काष्ठा v4l2_ctrl_handler ctrl_handler;
पूर्ण;

पूर्णांक radio_tea5777_init(काष्ठा radio_tea5777 *tea, काष्ठा module *owner);
व्योम radio_tea5777_निकास(काष्ठा radio_tea5777 *tea);
पूर्णांक radio_tea5777_set_freq(काष्ठा radio_tea5777 *tea);

#पूर्ण_अगर /* __RADIO_TEA5777_H */
