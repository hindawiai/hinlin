<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
#अगर_अघोषित __SOUND_SEQ_KERNEL_H
#घोषणा __SOUND_SEQ_KERNEL_H

/*
 *  Main kernel header file क्रम the ALSA sequencer
 *  Copyright (c) 1998 by Frank van de Pol <fvdpol@coil.demon.nl>
 */
#समावेश <linux/समय.स>
#समावेश <sound/asequencer.h>

प्रकार काष्ठा snd_seq_real_समय snd_seq_real_समय_प्रकार;
प्रकार जोड़ snd_seq_बारtamp snd_seq_बारtamp_t;

/* maximum number of queues */
#घोषणा SNDRV_SEQ_MAX_QUEUES		32

/* max number of concurrent clients */
#घोषणा SNDRV_SEQ_MAX_CLIENTS 		192

/* max number of concurrent ports */
#घोषणा SNDRV_SEQ_MAX_PORTS 		254

/* max number of events in memory pool */
#घोषणा SNDRV_SEQ_MAX_EVENTS		2000

/* शेष number of events in memory pool */
#घोषणा SNDRV_SEQ_DEFAULT_EVENTS	500

/* max number of events in memory pool क्रम one client (outqueue) */
#घोषणा SNDRV_SEQ_MAX_CLIENT_EVENTS	2000

/* शेष number of events in memory pool क्रम one client (outqueue) */
#घोषणा SNDRV_SEQ_DEFAULT_CLIENT_EVENTS	200

/* max delivery path length */
/* NOTE: this shouldn't be greater than MAX_LOCKDEP_SUBCLASSES */
#घोषणा SNDRV_SEQ_MAX_HOPS		8

/* max size of event size */
#घोषणा SNDRV_SEQ_MAX_EVENT_LEN		0x3fffffff

/* call-backs क्रम kernel port */
काष्ठा snd_seq_port_callback अणु
	काष्ठा module *owner;
	व्योम *निजी_data;
	पूर्णांक (*subscribe)(व्योम *निजी_data, काष्ठा snd_seq_port_subscribe *info);
	पूर्णांक (*unsubscribe)(व्योम *निजी_data, काष्ठा snd_seq_port_subscribe *info);
	पूर्णांक (*use)(व्योम *निजी_data, काष्ठा snd_seq_port_subscribe *info);
	पूर्णांक (*unuse)(व्योम *निजी_data, काष्ठा snd_seq_port_subscribe *info);
	पूर्णांक (*event_input)(काष्ठा snd_seq_event *ev, पूर्णांक direct, व्योम *निजी_data, पूर्णांक atomic, पूर्णांक hop);
	व्योम (*निजी_मुक्त)(व्योम *निजी_data);
	/*...*/
पूर्ण;

/* पूर्णांकerface क्रम kernel client */
__म_लिखो(3, 4)
पूर्णांक snd_seq_create_kernel_client(काष्ठा snd_card *card, पूर्णांक client_index,
				 स्थिर अक्षर *name_fmt, ...);
पूर्णांक snd_seq_delete_kernel_client(पूर्णांक client);
पूर्णांक snd_seq_kernel_client_enqueue(पूर्णांक client, काष्ठा snd_seq_event *ev,
				  काष्ठा file *file, bool blocking);
पूर्णांक snd_seq_kernel_client_dispatch(पूर्णांक client, काष्ठा snd_seq_event *ev, पूर्णांक atomic, पूर्णांक hop);
पूर्णांक snd_seq_kernel_client_ctl(पूर्णांक client, अचिन्हित पूर्णांक cmd, व्योम *arg);

#घोषणा SNDRV_SEQ_EXT_MASK	0xc0000000
#घोषणा SNDRV_SEQ_EXT_USRPTR	0x80000000
#घोषणा SNDRV_SEQ_EXT_CHAINED	0x40000000

प्रकार पूर्णांक (*snd_seq_dump_func_t)(व्योम *ptr, व्योम *buf, पूर्णांक count);
पूर्णांक snd_seq_expand_var_event(स्थिर काष्ठा snd_seq_event *event, पूर्णांक count, अक्षर *buf,
			     पूर्णांक in_kernel, पूर्णांक size_aligned);
पूर्णांक snd_seq_dump_var_event(स्थिर काष्ठा snd_seq_event *event,
			   snd_seq_dump_func_t func, व्योम *निजी_data);

/* पूर्णांकerface क्रम OSS emulation */
पूर्णांक snd_seq_set_queue_tempo(पूर्णांक client, काष्ठा snd_seq_queue_tempo *tempo);

/* port callback routines */
व्योम snd_port_init_callback(काष्ठा snd_seq_port_callback *p);
काष्ठा snd_seq_port_callback *snd_port_alloc_callback(व्योम);

/* port attach/detach */
पूर्णांक snd_seq_event_port_attach(पूर्णांक client, काष्ठा snd_seq_port_callback *pcbp,
			      पूर्णांक cap, पूर्णांक type, पूर्णांक midi_channels, पूर्णांक midi_voices, अक्षर *portname);
पूर्णांक snd_seq_event_port_detach(पूर्णांक client, पूर्णांक port);

#अगर_घोषित CONFIG_MODULES
व्योम snd_seq_स्वतःload_init(व्योम);
व्योम snd_seq_स्वतःload_निकास(व्योम);
#अन्यथा
#घोषणा snd_seq_स्वतःload_init()
#घोषणा snd_seq_स्वतःload_निकास()
#पूर्ण_अगर

#पूर्ण_अगर /* __SOUND_SEQ_KERNEL_H */
