<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Line 6 Linux USB driver
 *
 * Copyright (C) 2004-2010 Markus Grabner (grabner@icg.tugraz.at)
 */

#अगर_अघोषित CAPTURE_H
#घोषणा CAPTURE_H

#समावेश <sound/pcm.h>

#समावेश "driver.h"
#समावेश "pcm.h"

बाह्य स्थिर काष्ठा snd_pcm_ops snd_line6_capture_ops;

बाह्य व्योम line6_capture_copy(काष्ठा snd_line6_pcm *line6pcm, अक्षर *fbuf,
			       पूर्णांक fsize);
बाह्य व्योम line6_capture_check_period(काष्ठा snd_line6_pcm *line6pcm,
				       पूर्णांक length);
बाह्य पूर्णांक line6_create_audio_in_urbs(काष्ठा snd_line6_pcm *line6pcm);
बाह्य पूर्णांक line6_submit_audio_in_all_urbs(काष्ठा snd_line6_pcm *line6pcm);

#पूर्ण_अगर
