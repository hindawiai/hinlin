<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
#अगर_अघोषित __SOUND_SEQ_OSS_H
#घोषणा __SOUND_SEQ_OSS_H

/*
 * OSS compatible sequencer driver
 *
 * Copyright (C) 1998,99 Takashi Iwai
 */

#समावेश <sound/asequencer.h>
#समावेश <sound/seq_kernel.h>

/*
 * argument काष्ठाure क्रम synthesizer operations
 */
काष्ठा snd_seq_oss_arg अणु
	/* given by OSS sequencer */
	पूर्णांक app_index;	/* application unique index */
	पूर्णांक file_mode;	/* file mode - see below */
	पूर्णांक seq_mode;	/* sequencer mode - see below */

	/* following must be initialized in खोलो callback */
	काष्ठा snd_seq_addr addr;	/* खोलोed port address */
	व्योम *निजी_data;	/* निजी data क्रम lowlevel drivers */

	/* note-on event passing mode: initially given by OSS seq,
	 * but configurable by drivers - see below
	 */
	पूर्णांक event_passing;
पूर्ण;


/*
 * synthesizer operation callbacks
 */
काष्ठा snd_seq_oss_callback अणु
	काष्ठा module *owner;
	पूर्णांक (*खोलो)(काष्ठा snd_seq_oss_arg *p, व्योम *closure);
	पूर्णांक (*बंद)(काष्ठा snd_seq_oss_arg *p);
	पूर्णांक (*ioctl)(काष्ठा snd_seq_oss_arg *p, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg);
	पूर्णांक (*load_patch)(काष्ठा snd_seq_oss_arg *p, पूर्णांक क्रमmat, स्थिर अक्षर __user *buf, पूर्णांक offs, पूर्णांक count);
	पूर्णांक (*reset)(काष्ठा snd_seq_oss_arg *p);
	पूर्णांक (*raw_event)(काष्ठा snd_seq_oss_arg *p, अचिन्हित अक्षर *data);
पूर्ण;

/* flag: file_mode */
#घोषणा SNDRV_SEQ_OSS_खाता_ACMODE		3
#घोषणा SNDRV_SEQ_OSS_खाता_READ		1
#घोषणा SNDRV_SEQ_OSS_खाता_WRITE		2
#घोषणा SNDRV_SEQ_OSS_खाता_NONBLOCK	4

/* flag: seq_mode */
#घोषणा SNDRV_SEQ_OSS_MODE_SYNTH		0
#घोषणा SNDRV_SEQ_OSS_MODE_MUSIC		1

/* flag: event_passing */
#घोषणा SNDRV_SEQ_OSS_PROCESS_EVENTS	0	/* key == 255 is processed as velocity change */
#घोषणा SNDRV_SEQ_OSS_PASS_EVENTS		1	/* pass all events to callback */
#घोषणा SNDRV_SEQ_OSS_PROCESS_KEYPRESS	2	/* key >= 128 will be processed as key-pressure */

/* शेष control rate: fixed */
#घोषणा SNDRV_SEQ_OSS_CTRLRATE		100

/* शेष max queue length: configurable by module option */
#घोषणा SNDRV_SEQ_OSS_MAX_QLEN		1024


/*
 * data poपूर्णांकer to snd_seq_रेजिस्टर_device
 */
काष्ठा snd_seq_oss_reg अणु
	पूर्णांक type;
	पूर्णांक subtype;
	पूर्णांक nvoices;
	काष्ठा snd_seq_oss_callback oper;
	व्योम *निजी_data;
पूर्ण;

/* device id */
#घोषणा SNDRV_SEQ_DEV_ID_OSS		"seq-oss"

#पूर्ण_अगर /* __SOUND_SEQ_OSS_H */
