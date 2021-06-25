<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright 2003 Vivien Chappelier <vivien.chappelier@linux-mips.org>
 * Copyright 2008 Thomas Bogenकरोerfer <tsbogend@franken.de>
 */

#अगर_अघोषित __SOUND_AD1843_H
#घोषणा __SOUND_AD1843_H

काष्ठा snd_ad1843 अणु
	व्योम *chip;
	पूर्णांक (*पढ़ो)(व्योम *chip, पूर्णांक reg);
	पूर्णांक (*ग_लिखो)(व्योम *chip, पूर्णांक reg, पूर्णांक val);
पूर्ण;

#घोषणा AD1843_GAIN_RECLEV 0
#घोषणा AD1843_GAIN_LINE   1
#घोषणा AD1843_GAIN_LINE_2 2
#घोषणा AD1843_GAIN_MIC    3
#घोषणा AD1843_GAIN_PCM_0  4
#घोषणा AD1843_GAIN_PCM_1  5
#घोषणा AD1843_GAIN_SIZE   (AD1843_GAIN_PCM_1+1)

पूर्णांक ad1843_get_gain_max(काष्ठा snd_ad1843 *ad1843, पूर्णांक id);
पूर्णांक ad1843_get_gain(काष्ठा snd_ad1843 *ad1843, पूर्णांक id);
पूर्णांक ad1843_set_gain(काष्ठा snd_ad1843 *ad1843, पूर्णांक id, पूर्णांक newval);
पूर्णांक ad1843_get_recsrc(काष्ठा snd_ad1843 *ad1843);
पूर्णांक ad1843_set_recsrc(काष्ठा snd_ad1843 *ad1843, पूर्णांक newsrc);
व्योम ad1843_setup_dac(काष्ठा snd_ad1843 *ad1843,
		      अचिन्हित पूर्णांक id,
		      अचिन्हित पूर्णांक framerate,
		      snd_pcm_क्रमmat_t fmt,
		      अचिन्हित पूर्णांक channels);
व्योम ad1843_shutकरोwn_dac(काष्ठा snd_ad1843 *ad1843,
			 अचिन्हित पूर्णांक id);
व्योम ad1843_setup_adc(काष्ठा snd_ad1843 *ad1843,
		      अचिन्हित पूर्णांक framerate,
		      snd_pcm_क्रमmat_t fmt,
		      अचिन्हित पूर्णांक channels);
व्योम ad1843_shutकरोwn_adc(काष्ठा snd_ad1843 *ad1843);
पूर्णांक ad1843_init(काष्ठा snd_ad1843 *ad1843);

#पूर्ण_अगर /* __SOUND_AD1843_H */
