<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * OSS compatible sequencer driver
 *
 * midi device inक्रमmation
 *
 * Copyright (C) 1998,99 Takashi Iwai <tiwai@suse.de>
 */

#अगर_अघोषित __SEQ_OSS_MIDI_H
#घोषणा __SEQ_OSS_MIDI_H

#समावेश "seq_oss_device.h"
#समावेश <sound/seq_oss_legacy.h>

पूर्णांक snd_seq_oss_midi_lookup_ports(पूर्णांक client);
पूर्णांक snd_seq_oss_midi_check_new_port(काष्ठा snd_seq_port_info *pinfo);
पूर्णांक snd_seq_oss_midi_check_निकास_port(पूर्णांक client, पूर्णांक port);
व्योम snd_seq_oss_midi_clear_all(व्योम);

व्योम snd_seq_oss_midi_setup(काष्ठा seq_oss_devinfo *dp);
व्योम snd_seq_oss_midi_cleanup(काष्ठा seq_oss_devinfo *dp);

पूर्णांक snd_seq_oss_midi_खोलो(काष्ठा seq_oss_devinfo *dp, पूर्णांक dev, पूर्णांक file_mode);
व्योम snd_seq_oss_midi_खोलो_all(काष्ठा seq_oss_devinfo *dp, पूर्णांक file_mode);
पूर्णांक snd_seq_oss_midi_बंद(काष्ठा seq_oss_devinfo *dp, पूर्णांक dev);
व्योम snd_seq_oss_midi_reset(काष्ठा seq_oss_devinfo *dp, पूर्णांक dev);
पूर्णांक snd_seq_oss_midi_अ_दो(काष्ठा seq_oss_devinfo *dp, पूर्णांक dev, अचिन्हित अक्षर c,
			  काष्ठा snd_seq_event *ev);
पूर्णांक snd_seq_oss_midi_input(काष्ठा snd_seq_event *ev, पूर्णांक direct, व्योम *निजी);
पूर्णांक snd_seq_oss_midi_filemode(काष्ठा seq_oss_devinfo *dp, पूर्णांक dev);
पूर्णांक snd_seq_oss_midi_make_info(काष्ठा seq_oss_devinfo *dp, पूर्णांक dev, काष्ठा midi_info *inf);
व्योम snd_seq_oss_midi_get_addr(काष्ठा seq_oss_devinfo *dp, पूर्णांक dev, काष्ठा snd_seq_addr *addr);

#पूर्ण_अगर
