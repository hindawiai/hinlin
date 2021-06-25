<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * OSS compatible sequencer driver
 *
 * Copyright (C) 1998,99 Takashi Iwai <tiwai@suse.de>
 */

#अगर_अघोषित __SEQ_OSS_DEVICE_H
#घोषणा __SEQ_OSS_DEVICE_H

#समावेश <linux/समय.स>
#समावेश <linux/रुको.h>
#समावेश <linux/slab.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <sound/core.h>
#समावेश <sound/seq_oss.h>
#समावेश <sound/rawmidi.h>
#समावेश <sound/seq_kernel.h>
#समावेश <sound/info.h>
#समावेश "../seq_clientmgr.h"

/* max. applications */
#घोषणा SNDRV_SEQ_OSS_MAX_CLIENTS	16
#घोषणा SNDRV_SEQ_OSS_MAX_SYNTH_DEVS	16
#घोषणा SNDRV_SEQ_OSS_MAX_MIDI_DEVS	32

/* version */
#घोषणा SNDRV_SEQ_OSS_MAJOR_VERSION	0
#घोषणा SNDRV_SEQ_OSS_MINOR_VERSION	1
#घोषणा SNDRV_SEQ_OSS_TINY_VERSION	8
#घोषणा SNDRV_SEQ_OSS_VERSION_STR	"0.1.8"

/* device and proc पूर्णांकerface name */
#घोषणा SNDRV_SEQ_OSS_PROCNAME		"oss"


/*
 * type definitions
 */

प्रकार अचिन्हित पूर्णांक relसमय_प्रकार;
प्रकार अचिन्हित पूर्णांक असलसमय_प्रकार;


/*
 * synthesizer channel inक्रमmation
 */
काष्ठा seq_oss_chinfo अणु
	पूर्णांक note, vel;
पूर्ण;

/*
 * synthesizer inक्रमmation
 */
काष्ठा seq_oss_synthinfo अणु
	काष्ठा snd_seq_oss_arg arg;
	काष्ठा seq_oss_chinfo *ch;
	काष्ठा seq_oss_synth_sysex *sysex;
	पूर्णांक nr_voices;
	पूर्णांक खोलोed;
	पूर्णांक is_midi;
	पूर्णांक midi_mapped;
पूर्ण;


/*
 * sequencer client inक्रमmation
 */

काष्ठा seq_oss_devinfo अणु

	पूर्णांक index;	/* application index */
	पूर्णांक cseq;	/* sequencer client number */
	पूर्णांक port;	/* sequencer port number */
	पूर्णांक queue;	/* sequencer queue number */

	काष्ठा snd_seq_addr addr;	/* address of this device */

	पूर्णांक seq_mode;	/* sequencer mode */
	पूर्णांक file_mode;	/* file access */

	/* midi device table */
	पूर्णांक max_mididev;

	/* synth device table */
	पूर्णांक max_synthdev;
	काष्ठा seq_oss_synthinfo synths[SNDRV_SEQ_OSS_MAX_SYNTH_DEVS];
	पूर्णांक synth_खोलोed;

	/* output queue */
	काष्ठा seq_oss_ग_लिखोq *ग_लिखोq;

	/* midi input queue */
	काष्ठा seq_oss_पढ़ोq *पढ़ोq;

	/* समयr */
	काष्ठा seq_oss_समयr *समयr;
पूर्ण;


/*
 * function prototypes
 */

/* create/delete OSS sequencer client */
पूर्णांक snd_seq_oss_create_client(व्योम);
पूर्णांक snd_seq_oss_delete_client(व्योम);

/* device file पूर्णांकerface */
पूर्णांक snd_seq_oss_खोलो(काष्ठा file *file, पूर्णांक level);
व्योम snd_seq_oss_release(काष्ठा seq_oss_devinfo *dp);
पूर्णांक snd_seq_oss_ioctl(काष्ठा seq_oss_devinfo *dp, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg);
पूर्णांक snd_seq_oss_पढ़ो(काष्ठा seq_oss_devinfo *dev, अक्षर __user *buf, पूर्णांक count);
पूर्णांक snd_seq_oss_ग_लिखो(काष्ठा seq_oss_devinfo *dp, स्थिर अक्षर __user *buf, पूर्णांक count, काष्ठा file *opt);
__poll_t snd_seq_oss_poll(काष्ठा seq_oss_devinfo *dp, काष्ठा file *file, poll_table * रुको);

व्योम snd_seq_oss_reset(काष्ठा seq_oss_devinfo *dp);

/* */
व्योम snd_seq_oss_process_queue(काष्ठा seq_oss_devinfo *dp, असलसमय_प्रकार समय);


/* proc पूर्णांकerface */
व्योम snd_seq_oss_प्रणाली_info_पढ़ो(काष्ठा snd_info_buffer *buf);
व्योम snd_seq_oss_midi_info_पढ़ो(काष्ठा snd_info_buffer *buf);
व्योम snd_seq_oss_synth_info_पढ़ो(काष्ठा snd_info_buffer *buf);
व्योम snd_seq_oss_पढ़ोq_info_पढ़ो(काष्ठा seq_oss_पढ़ोq *q, काष्ठा snd_info_buffer *buf);

/* file mode macros */
#घोषणा is_पढ़ो_mode(mode)	((mode) & SNDRV_SEQ_OSS_खाता_READ)
#घोषणा is_ग_लिखो_mode(mode)	((mode) & SNDRV_SEQ_OSS_खाता_WRITE)
#घोषणा is_nonblock_mode(mode)	((mode) & SNDRV_SEQ_OSS_खाता_NONBLOCK)

/* dispatch event */
अटल अंतरभूत पूर्णांक
snd_seq_oss_dispatch(काष्ठा seq_oss_devinfo *dp, काष्ठा snd_seq_event *ev, पूर्णांक atomic, पूर्णांक hop)
अणु
	वापस snd_seq_kernel_client_dispatch(dp->cseq, ev, atomic, hop);
पूर्ण

/* ioctl क्रम ग_लिखोq */
अटल अंतरभूत पूर्णांक
snd_seq_oss_control(काष्ठा seq_oss_devinfo *dp, अचिन्हित पूर्णांक type, व्योम *arg)
अणु
	पूर्णांक err;

	snd_seq_client_ioctl_lock(dp->cseq);
	err = snd_seq_kernel_client_ctl(dp->cseq, type, arg);
	snd_seq_client_ioctl_unlock(dp->cseq);
	वापस err;
पूर्ण

/* fill the addresses in header */
अटल अंतरभूत व्योम
snd_seq_oss_fill_addr(काष्ठा seq_oss_devinfo *dp, काष्ठा snd_seq_event *ev,
		     पूर्णांक dest_client, पूर्णांक dest_port)
अणु
	ev->queue = dp->queue;
	ev->source = dp->addr;
	ev->dest.client = dest_client;
	ev->dest.port = dest_port;
पूर्ण


/* misc. functions क्रम proc पूर्णांकerface */
अक्षर *enabled_str(पूर्णांक bool);

#पूर्ण_अगर /* __SEQ_OSS_DEVICE_H */
