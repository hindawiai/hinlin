<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
#अगर_अघोषित __SOUND_SEQ_VIRMIDI_H
#घोषणा __SOUND_SEQ_VIRMIDI_H

/*
 *  Virtual Raw MIDI client on Sequencer
 *  Copyright (c) 2000 by Takashi Iwai <tiwai@suse.de>,
 *                        Jaroslav Kysela <perex@perex.cz>
 */

#समावेश <sound/rawmidi.h>
#समावेश <sound/seq_midi_event.h>

/*
 * device file instance:
 * This instance is created at each समय the midi device file is
 * खोलोed.  Each instance has its own input buffer and MIDI parser
 * (buffer), and is associated with the device instance.
 */
काष्ठा snd_virmidi अणु
	काष्ठा list_head list;
	पूर्णांक seq_mode;
	पूर्णांक client;
	पूर्णांक port;
	bool trigger;
	काष्ठा snd_midi_event *parser;
	काष्ठा snd_seq_event event;
	काष्ठा snd_virmidi_dev *rdev;
	काष्ठा snd_rawmidi_substream *substream;
	काष्ठा work_काष्ठा output_work;
पूर्ण;

#घोषणा SNDRV_VIRMIDI_SUBSCRIBE		(1<<0)
#घोषणा SNDRV_VIRMIDI_USE		(1<<1)

/*
 * device record:
 * Each भव midi device has one device instance.  It contains
 * common inक्रमmation and the linked-list of खोलोed files, 
 */
काष्ठा snd_virmidi_dev अणु
	काष्ठा snd_card *card;		/* associated card */
	काष्ठा snd_rawmidi *rmidi;		/* rawmidi device */
	पूर्णांक seq_mode;			/* SNDRV_VIRMIDI_XXX */
	पूर्णांक device;			/* sequencer device */
	पूर्णांक client;			/* created/attached client */
	पूर्णांक port;			/* created/attached port */
	अचिन्हित पूर्णांक flags;		/* SNDRV_VIRMIDI_* */
	rwlock_t filelist_lock;
	काष्ठा rw_semaphore filelist_sem;
	काष्ठा list_head filelist;
पूर्ण;

/* sequencer mode:
 * ATTACH = input/output events from midi device are routed to the
 *          attached sequencer port.  sequencer port is not created
 *          by virmidi itself.
 *          the input to rawmidi must be processed by passing the
 *          incoming events via snd_virmidi_receive()
 * DISPATCH = input/output events are routed to subscribers.
 *            sequencer port is created in virmidi.
 */
#घोषणा SNDRV_VIRMIDI_SEQ_NONE		0
#घोषणा SNDRV_VIRMIDI_SEQ_ATTACH	1
#घोषणा SNDRV_VIRMIDI_SEQ_DISPATCH	2

पूर्णांक snd_virmidi_new(काष्ठा snd_card *card, पूर्णांक device, काष्ठा snd_rawmidi **rrmidi);

#पूर्ण_अगर /* __SOUND_SEQ_VIRMIDI */
