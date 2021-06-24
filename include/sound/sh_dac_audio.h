<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * SH_DAC specअगरic configuration, क्रम the dac_audio platक्रमm_device
 *
 * Copyright (C) 2009 Rafael Ignacio Zurita <rizurita@yahoo.com>
 */

#अगर_अघोषित __INCLUDE_SH_DAC_AUDIO_H
#घोषणा __INCLUDE_SH_DAC_AUDIO_H

काष्ठा dac_audio_pdata अणु
	पूर्णांक buffer_size;
	पूर्णांक channel;
	व्योम (*start)(काष्ठा dac_audio_pdata *pd);
	व्योम (*stop)(काष्ठा dac_audio_pdata *pd);
पूर्ण;

#पूर्ण_अगर /* __INCLUDE_SH_DAC_AUDIO_H */
