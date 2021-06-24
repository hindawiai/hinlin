<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*****************************************************************************
 *
 * Copyright (C) 2008 Cedric Bregardis <cedric.bregardis@मुक्त.fr> and
 * Jean-Christian Hassler <jhassler@मुक्त.fr>
 *
 * This file is part of the Audiowerk2 ALSA driver
 *
 *****************************************************************************/

#अगर_अघोषित AW2_SAA7146_H
#घोषणा AW2_SAA7146_H

#घोषणा NB_STREAM_PLAYBACK 2
#घोषणा NB_STREAM_CAPTURE 1

#घोषणा NUM_STREAM_PLAYBACK_ANA 0
#घोषणा NUM_STREAM_PLAYBACK_DIG 1

#घोषणा NUM_STREAM_CAPTURE_ANA 0

प्रकार व्योम (*snd_aw2_saa7146_it_cb) (व्योम *);

काष्ठा snd_aw2_saa7146_cb_param अणु
	snd_aw2_saa7146_it_cb p_it_callback;
	व्योम *p_callback_param;
पूर्ण;

/* definition of the chip-specअगरic record */

काष्ठा snd_aw2_saa7146 अणु
	व्योम __iomem *base_addr;
पूर्ण;

बाह्य व्योम snd_aw2_saa7146_setup(काष्ठा snd_aw2_saa7146 *chip,
				  व्योम __iomem *pci_base_addr);
बाह्य पूर्णांक snd_aw2_saa7146_मुक्त(काष्ठा snd_aw2_saa7146 *chip);

बाह्य व्योम snd_aw2_saa7146_pcm_init_playback(काष्ठा snd_aw2_saa7146 *chip,
					      पूर्णांक stream_number,
					      अचिन्हित दीर्घ dma_addr,
					      अचिन्हित दीर्घ period_size,
					      अचिन्हित दीर्घ buffer_size);
बाह्य व्योम snd_aw2_saa7146_pcm_init_capture(काष्ठा snd_aw2_saa7146 *chip,
					     पूर्णांक stream_number,
					     अचिन्हित दीर्घ dma_addr,
					     अचिन्हित दीर्घ period_size,
					     अचिन्हित दीर्घ buffer_size);
बाह्य व्योम snd_aw2_saa7146_define_it_playback_callback(अचिन्हित पूर्णांक
							stream_number,
							snd_aw2_saa7146_it_cb
							p_it_callback,
							व्योम *p_callback_param);
बाह्य व्योम snd_aw2_saa7146_define_it_capture_callback(अचिन्हित पूर्णांक
						       stream_number,
						       snd_aw2_saa7146_it_cb
						       p_it_callback,
						       व्योम *p_callback_param);
बाह्य व्योम snd_aw2_saa7146_pcm_trigger_start_capture(काष्ठा snd_aw2_saa7146
						      *chip, पूर्णांक stream_number);
बाह्य व्योम snd_aw2_saa7146_pcm_trigger_stop_capture(काष्ठा snd_aw2_saa7146
						     *chip, पूर्णांक stream_number);

बाह्य व्योम snd_aw2_saa7146_pcm_trigger_start_playback(काष्ठा snd_aw2_saa7146
						       *chip,
						       पूर्णांक stream_number);
बाह्य व्योम snd_aw2_saa7146_pcm_trigger_stop_playback(काष्ठा snd_aw2_saa7146
						      *chip, पूर्णांक stream_number);

बाह्य irqवापस_t snd_aw2_saa7146_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id);
बाह्य अचिन्हित पूर्णांक snd_aw2_saa7146_get_hw_ptr_playback(काष्ठा snd_aw2_saa7146
							*chip,
							पूर्णांक stream_number,
							अचिन्हित अक्षर
							*start_addr,
							अचिन्हित पूर्णांक
							buffer_size);
बाह्य अचिन्हित पूर्णांक snd_aw2_saa7146_get_hw_ptr_capture(काष्ठा snd_aw2_saa7146
						       *chip,
						       पूर्णांक stream_number,
						       अचिन्हित अक्षर
						       *start_addr,
						       अचिन्हित पूर्णांक
						       buffer_size);

बाह्य व्योम snd_aw2_saa7146_use_digital_input(काष्ठा snd_aw2_saa7146 *chip,
					      पूर्णांक use_digital);

बाह्य पूर्णांक snd_aw2_saa7146_is_using_digital_input(काष्ठा snd_aw2_saa7146
						  *chip);

#पूर्ण_अगर
