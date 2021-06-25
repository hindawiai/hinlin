<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
#अगर_अघोषित __SOUND_RAWMIDI_H
#घोषणा __SOUND_RAWMIDI_H

/*
 *  Abstract layer क्रम MIDI v1.0 stream
 *  Copyright (c) by Jaroslav Kysela <perex@perex.cz>
 */

#समावेश <sound/asound.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/रुको.h>
#समावेश <linux/mutex.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/device.h>

#अगर IS_ENABLED(CONFIG_SND_SEQUENCER)
#समावेश <sound/seq_device.h>
#पूर्ण_अगर

/*
 *  Raw MIDI पूर्णांकerface
 */

#घोषणा SNDRV_RAWMIDI_DEVICES		8

#घोषणा SNDRV_RAWMIDI_LFLG_OUTPUT	(1<<0)
#घोषणा SNDRV_RAWMIDI_LFLG_INPUT	(1<<1)
#घोषणा SNDRV_RAWMIDI_LFLG_OPEN		(3<<0)
#घोषणा SNDRV_RAWMIDI_LFLG_APPEND	(1<<2)

काष्ठा snd_rawmidi;
काष्ठा snd_rawmidi_substream;
काष्ठा snd_seq_port_info;
काष्ठा pid;

काष्ठा snd_rawmidi_ops अणु
	पूर्णांक (*खोलो) (काष्ठा snd_rawmidi_substream * substream);
	पूर्णांक (*बंद) (काष्ठा snd_rawmidi_substream * substream);
	व्योम (*trigger) (काष्ठा snd_rawmidi_substream * substream, पूर्णांक up);
	व्योम (*drain) (काष्ठा snd_rawmidi_substream * substream);
पूर्ण;

काष्ठा snd_rawmidi_global_ops अणु
	पूर्णांक (*dev_रेजिस्टर) (काष्ठा snd_rawmidi * rmidi);
	पूर्णांक (*dev_unरेजिस्टर) (काष्ठा snd_rawmidi * rmidi);
	व्योम (*get_port_info)(काष्ठा snd_rawmidi *rmidi, पूर्णांक number,
			      काष्ठा snd_seq_port_info *info);
पूर्ण;

काष्ठा snd_rawmidi_runसमय अणु
	काष्ठा snd_rawmidi_substream *substream;
	अचिन्हित पूर्णांक drain: 1,	/* drain stage */
		     oss: 1;	/* OSS compatible mode */
	/* midi stream buffer */
	अचिन्हित अक्षर *buffer;	/* buffer क्रम MIDI data */
	माप_प्रकार buffer_size;	/* size of buffer */
	माप_प्रकार appl_ptr;	/* application poपूर्णांकer */
	माप_प्रकार hw_ptr;		/* hardware poपूर्णांकer */
	माप_प्रकार avail_min;	/* min avail क्रम wakeup */
	माप_प्रकार avail;		/* max used buffer क्रम wakeup */
	माप_प्रकार xruns;		/* over/underruns counter */
	पूर्णांक buffer_ref;		/* buffer reference count */
	/* misc */
	spinlock_t lock;
	रुको_queue_head_t sleep;
	/* event handler (new bytes, input only) */
	व्योम (*event)(काष्ठा snd_rawmidi_substream *substream);
	/* defers calls to event [input] or ops->trigger [output] */
	काष्ठा work_काष्ठा event_work;
	/* निजी data */
	व्योम *निजी_data;
	व्योम (*निजी_मुक्त)(काष्ठा snd_rawmidi_substream *substream);
पूर्ण;

काष्ठा snd_rawmidi_substream अणु
	काष्ठा list_head list;		/* list of all substream क्रम given stream */
	पूर्णांक stream;			/* direction */
	पूर्णांक number;			/* substream number */
	bool खोलोed;			/* खोलो flag */
	bool append;			/* append flag (merge more streams) */
	bool active_sensing;		/* send active sensing when बंद */
	पूर्णांक use_count;			/* use counter (क्रम output) */
	माप_प्रकार bytes;
	काष्ठा snd_rawmidi *rmidi;
	काष्ठा snd_rawmidi_str *pstr;
	अक्षर name[32];
	काष्ठा snd_rawmidi_runसमय *runसमय;
	काष्ठा pid *pid;
	/* hardware layer */
	स्थिर काष्ठा snd_rawmidi_ops *ops;
पूर्ण;

काष्ठा snd_rawmidi_file अणु
	काष्ठा snd_rawmidi *rmidi;
	काष्ठा snd_rawmidi_substream *input;
	काष्ठा snd_rawmidi_substream *output;
पूर्ण;

काष्ठा snd_rawmidi_str अणु
	अचिन्हित पूर्णांक substream_count;
	अचिन्हित पूर्णांक substream_खोलोed;
	काष्ठा list_head substreams;
पूर्ण;

काष्ठा snd_rawmidi अणु
	काष्ठा snd_card *card;
	काष्ठा list_head list;
	अचिन्हित पूर्णांक device;		/* device number */
	अचिन्हित पूर्णांक info_flags;	/* SNDRV_RAWMIDI_INFO_XXXX */
	अक्षर id[64];
	अक्षर name[80];

#अगर_घोषित CONFIG_SND_OSSEMUL
	पूर्णांक ossreg;
#पूर्ण_अगर

	स्थिर काष्ठा snd_rawmidi_global_ops *ops;

	काष्ठा snd_rawmidi_str streams[2];

	व्योम *निजी_data;
	व्योम (*निजी_मुक्त) (काष्ठा snd_rawmidi *rmidi);

	काष्ठा mutex खोलो_mutex;
	रुको_queue_head_t खोलो_रुको;

	काष्ठा device dev;

	काष्ठा snd_info_entry *proc_entry;

#अगर IS_ENABLED(CONFIG_SND_SEQUENCER)
	काष्ठा snd_seq_device *seq_dev;
#पूर्ण_अगर
पूर्ण;

/* मुख्य rawmidi functions */

पूर्णांक snd_rawmidi_new(काष्ठा snd_card *card, अक्षर *id, पूर्णांक device,
		    पूर्णांक output_count, पूर्णांक input_count,
		    काष्ठा snd_rawmidi **rmidi);
व्योम snd_rawmidi_set_ops(काष्ठा snd_rawmidi *rmidi, पूर्णांक stream,
			 स्थिर काष्ठा snd_rawmidi_ops *ops);

/* callbacks */

पूर्णांक snd_rawmidi_receive(काष्ठा snd_rawmidi_substream *substream,
			स्थिर अचिन्हित अक्षर *buffer, पूर्णांक count);
पूर्णांक snd_rawmidi_transmit_empty(काष्ठा snd_rawmidi_substream *substream);
पूर्णांक snd_rawmidi_transmit_peek(काष्ठा snd_rawmidi_substream *substream,
			      अचिन्हित अक्षर *buffer, पूर्णांक count);
पूर्णांक snd_rawmidi_transmit_ack(काष्ठा snd_rawmidi_substream *substream, पूर्णांक count);
पूर्णांक snd_rawmidi_transmit(काष्ठा snd_rawmidi_substream *substream,
			 अचिन्हित अक्षर *buffer, पूर्णांक count);
पूर्णांक __snd_rawmidi_transmit_peek(काष्ठा snd_rawmidi_substream *substream,
			      अचिन्हित अक्षर *buffer, पूर्णांक count);
पूर्णांक __snd_rawmidi_transmit_ack(काष्ठा snd_rawmidi_substream *substream,
			       पूर्णांक count);
पूर्णांक snd_rawmidi_proceed(काष्ठा snd_rawmidi_substream *substream);

/* मुख्य midi functions */

पूर्णांक snd_rawmidi_info_select(काष्ठा snd_card *card, काष्ठा snd_rawmidi_info *info);
पूर्णांक snd_rawmidi_kernel_खोलो(काष्ठा snd_card *card, पूर्णांक device, पूर्णांक subdevice,
			    पूर्णांक mode, काष्ठा snd_rawmidi_file *rfile);
पूर्णांक snd_rawmidi_kernel_release(काष्ठा snd_rawmidi_file *rfile);
पूर्णांक snd_rawmidi_output_params(काष्ठा snd_rawmidi_substream *substream,
			      काष्ठा snd_rawmidi_params *params);
पूर्णांक snd_rawmidi_input_params(काष्ठा snd_rawmidi_substream *substream,
			     काष्ठा snd_rawmidi_params *params);
पूर्णांक snd_rawmidi_drop_output(काष्ठा snd_rawmidi_substream *substream);
पूर्णांक snd_rawmidi_drain_output(काष्ठा snd_rawmidi_substream *substream);
पूर्णांक snd_rawmidi_drain_input(काष्ठा snd_rawmidi_substream *substream);
दीर्घ snd_rawmidi_kernel_पढ़ो(काष्ठा snd_rawmidi_substream *substream,
			     अचिन्हित अक्षर *buf, दीर्घ count);
दीर्घ snd_rawmidi_kernel_ग_लिखो(काष्ठा snd_rawmidi_substream *substream,
			      स्थिर अचिन्हित अक्षर *buf, दीर्घ count);

#पूर्ण_अगर /* __SOUND_RAWMIDI_H */
