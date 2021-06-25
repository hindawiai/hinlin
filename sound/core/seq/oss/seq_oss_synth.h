<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * OSS compatible sequencer driver
 *
 * synth device inक्रमmation
 *
 * Copyright (C) 1998,99 Takashi Iwai <tiwai@suse.de>
 */

#अगर_अघोषित __SEQ_OSS_SYNTH_H
#घोषणा __SEQ_OSS_SYNTH_H

#समावेश "seq_oss_device.h"
#समावेश <sound/seq_oss_legacy.h>
#समावेश <sound/seq_device.h>

व्योम snd_seq_oss_synth_init(व्योम);
पूर्णांक snd_seq_oss_synth_probe(काष्ठा device *dev);
पूर्णांक snd_seq_oss_synth_हटाओ(काष्ठा device *dev);
व्योम snd_seq_oss_synth_setup(काष्ठा seq_oss_devinfo *dp);
व्योम snd_seq_oss_synth_setup_midi(काष्ठा seq_oss_devinfo *dp);
व्योम snd_seq_oss_synth_cleanup(काष्ठा seq_oss_devinfo *dp);

व्योम snd_seq_oss_synth_reset(काष्ठा seq_oss_devinfo *dp, पूर्णांक dev);
पूर्णांक snd_seq_oss_synth_load_patch(काष्ठा seq_oss_devinfo *dp, पूर्णांक dev, पूर्णांक fmt,
				 स्थिर अक्षर __user *buf, पूर्णांक p, पूर्णांक c);
काष्ठा seq_oss_synthinfo *snd_seq_oss_synth_info(काष्ठा seq_oss_devinfo *dp,
						 पूर्णांक dev);
पूर्णांक snd_seq_oss_synth_sysex(काष्ठा seq_oss_devinfo *dp, पूर्णांक dev, अचिन्हित अक्षर *buf,
			    काष्ठा snd_seq_event *ev);
पूर्णांक snd_seq_oss_synth_addr(काष्ठा seq_oss_devinfo *dp, पूर्णांक dev, काष्ठा snd_seq_event *ev);
पूर्णांक snd_seq_oss_synth_ioctl(काष्ठा seq_oss_devinfo *dp, पूर्णांक dev, अचिन्हित पूर्णांक cmd,
			    अचिन्हित दीर्घ addr);
पूर्णांक snd_seq_oss_synth_raw_event(काष्ठा seq_oss_devinfo *dp, पूर्णांक dev,
				अचिन्हित अक्षर *data, काष्ठा snd_seq_event *ev);

पूर्णांक snd_seq_oss_synth_make_info(काष्ठा seq_oss_devinfo *dp, पूर्णांक dev, काष्ठा synth_info *inf);

#पूर्ण_अगर
