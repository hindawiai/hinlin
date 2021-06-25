<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ WITH Linux-syscall-note */
/*
 *  Main header file क्रम the ALSA sequencer
 *  Copyright (c) 1998-1999 by Frank van de Pol <fvdpol@coil.demon.nl>
 *            (c) 1998-1999 by Jaroslav Kysela <perex@perex.cz>
 *
 *
 *   This program is मुक्त software; you can redistribute it and/or modअगरy
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation; either version 2 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License क्रम more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   aदीर्घ with this program; अगर not, ग_लिखो to the Free Software
 *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA
 *
 */
#अगर_अघोषित _UAPI__SOUND_ASEQUENCER_H
#घोषणा _UAPI__SOUND_ASEQUENCER_H

#समावेश <sound/asound.h>

/** version of the sequencer */
#घोषणा SNDRV_SEQ_VERSION SNDRV_PROTOCOL_VERSION(1, 0, 2)

/**
 * definition of sequencer event types
 */

/** प्रणाली messages
 * event data type = #snd_seq_result
 */
#घोषणा SNDRV_SEQ_EVENT_SYSTEM		0
#घोषणा SNDRV_SEQ_EVENT_RESULT		1

/** note messages (channel specअगरic)
 * event data type = #snd_seq_ev_note
 */
#घोषणा SNDRV_SEQ_EVENT_NOTE		5
#घोषणा SNDRV_SEQ_EVENT_NOTEON		6
#घोषणा SNDRV_SEQ_EVENT_NOTखातापूर्णF		7
#घोषणा SNDRV_SEQ_EVENT_KEYPRESS	8
	
/** control messages (channel specअगरic)
 * event data type = #snd_seq_ev_ctrl
 */
#घोषणा SNDRV_SEQ_EVENT_CONTROLLER	10
#घोषणा SNDRV_SEQ_EVENT_PGMCHANGE	11
#घोषणा SNDRV_SEQ_EVENT_CHANPRESS	12
#घोषणा SNDRV_SEQ_EVENT_PITCHBEND	13	/**< from -8192 to 8191 */
#घोषणा SNDRV_SEQ_EVENT_CONTROL14	14	/**< 14 bit controller value */
#घोषणा SNDRV_SEQ_EVENT_NONREGPARAM	15	/**< 14 bit NRPN address + 14 bit अचिन्हित value */
#घोषणा SNDRV_SEQ_EVENT_REGPARAM	16	/**< 14 bit RPN address + 14 bit अचिन्हित value */

/** synchronisation messages
 * event data type = #snd_seq_ev_ctrl
 */
#घोषणा SNDRV_SEQ_EVENT_SONGPOS		20	/* Song Position Poपूर्णांकer with LSB and MSB values */
#घोषणा SNDRV_SEQ_EVENT_SONGSEL		21	/* Song Select with song ID number */
#घोषणा SNDRV_SEQ_EVENT_QFRAME		22	/* midi समय code quarter frame */
#घोषणा SNDRV_SEQ_EVENT_TIMESIGN	23	/* SMF Time Signature event */
#घोषणा SNDRV_SEQ_EVENT_KEYSIGN		24	/* SMF Key Signature event */
	        
/** समयr messages
 * event data type = snd_seq_ev_queue_control
 */
#घोषणा SNDRV_SEQ_EVENT_START		30	/* midi Real Time Start message */
#घोषणा SNDRV_SEQ_EVENT_CONTINUE	31	/* midi Real Time Continue message */
#घोषणा SNDRV_SEQ_EVENT_STOP		32	/* midi Real Time Stop message */	
#घोषणा	SNDRV_SEQ_EVENT_SETPOS_TICK	33	/* set tick queue position */
#घोषणा SNDRV_SEQ_EVENT_SETPOS_TIME	34	/* set realसमय queue position */
#घोषणा SNDRV_SEQ_EVENT_TEMPO		35	/* (SMF) Tempo event */
#घोषणा SNDRV_SEQ_EVENT_CLOCK		36	/* midi Real Time Clock message */
#घोषणा SNDRV_SEQ_EVENT_TICK		37	/* midi Real Time Tick message */
#घोषणा SNDRV_SEQ_EVENT_QUEUE_SKEW	38	/* skew queue tempo */

/** others
 * event data type = none
 */
#घोषणा SNDRV_SEQ_EVENT_TUNE_REQUEST	40	/* tune request */
#घोषणा SNDRV_SEQ_EVENT_RESET		41	/* reset to घातer-on state */
#घोषणा SNDRV_SEQ_EVENT_SENSING		42	/* "active sensing" event */

/** echo back, kernel निजी messages
 * event data type = any type
 */
#घोषणा SNDRV_SEQ_EVENT_ECHO		50	/* echo event */
#घोषणा SNDRV_SEQ_EVENT_OSS		51	/* OSS raw event */

/** प्रणाली status messages (broadcast क्रम subscribers)
 * event data type = snd_seq_addr
 */
#घोषणा SNDRV_SEQ_EVENT_CLIENT_START	60	/* new client has connected */
#घोषणा SNDRV_SEQ_EVENT_CLIENT_EXIT	61	/* client has left the प्रणाली */
#घोषणा SNDRV_SEQ_EVENT_CLIENT_CHANGE	62	/* client status/info has changed */
#घोषणा SNDRV_SEQ_EVENT_PORT_START	63	/* new port was created */
#घोषणा SNDRV_SEQ_EVENT_PORT_EXIT	64	/* port was deleted from प्रणाली */
#घोषणा SNDRV_SEQ_EVENT_PORT_CHANGE	65	/* port status/info has changed */

/** port connection changes
 * event data type = snd_seq_connect
 */
#घोषणा SNDRV_SEQ_EVENT_PORT_SUBSCRIBED	66	/* ports connected */
#घोषणा SNDRV_SEQ_EVENT_PORT_UNSUBSCRIBED 67	/* ports disconnected */

/* 70-89:  synthesizer events - obsoleted */

/** user-defined events with fixed length
 * event data type = any
 */
#घोषणा SNDRV_SEQ_EVENT_USR0		90
#घोषणा SNDRV_SEQ_EVENT_USR1		91
#घोषणा SNDRV_SEQ_EVENT_USR2		92
#घोषणा SNDRV_SEQ_EVENT_USR3		93
#घोषणा SNDRV_SEQ_EVENT_USR4		94
#घोषणा SNDRV_SEQ_EVENT_USR5		95
#घोषणा SNDRV_SEQ_EVENT_USR6		96
#घोषणा SNDRV_SEQ_EVENT_USR7		97
#घोषणा SNDRV_SEQ_EVENT_USR8		98
#घोषणा SNDRV_SEQ_EVENT_USR9		99

/* 100-118: instrument layer - obsoleted */
/* 119-129: reserved */

/* 130-139: variable length events
 * event data type = snd_seq_ev_ext
 * (SNDRV_SEQ_EVENT_LENGTH_VARIABLE must be set)
 */
#घोषणा SNDRV_SEQ_EVENT_SYSEX		130	/* प्रणाली exclusive data (variable length) */
#घोषणा SNDRV_SEQ_EVENT_BOUNCE		131	/* error event */
/* 132-134: reserved */
#घोषणा SNDRV_SEQ_EVENT_USR_VAR0	135
#घोषणा SNDRV_SEQ_EVENT_USR_VAR1	136
#घोषणा SNDRV_SEQ_EVENT_USR_VAR2	137
#घोषणा SNDRV_SEQ_EVENT_USR_VAR3	138
#घोषणा SNDRV_SEQ_EVENT_USR_VAR4	139

/* 150-151: kernel events with quote - DO NOT use in user clients */
#घोषणा SNDRV_SEQ_EVENT_KERNEL_ERROR	150
#घोषणा SNDRV_SEQ_EVENT_KERNEL_QUOTE	151	/* obsolete */

/* 152-191: reserved */

/* 192-254: hardware specअगरic events */

/* 255: special event */
#घोषणा SNDRV_SEQ_EVENT_NONE		255


प्रकार अचिन्हित अक्षर snd_seq_event_type_t;

/** event address */
काष्ठा snd_seq_addr अणु
	अचिन्हित अक्षर client;	/**< Client number:         0..255, 255 = broadcast to all clients */
	अचिन्हित अक्षर port;	/**< Port within client:    0..255, 255 = broadcast to all ports */
पूर्ण;

/** port connection */
काष्ठा snd_seq_connect अणु
	काष्ठा snd_seq_addr sender;
	काष्ठा snd_seq_addr dest;
पूर्ण;


#घोषणा SNDRV_SEQ_ADDRESS_UNKNOWN	253	/* unknown source */
#घोषणा SNDRV_SEQ_ADDRESS_SUBSCRIBERS	254	/* send event to all subscribed ports */
#घोषणा SNDRV_SEQ_ADDRESS_BROADCAST	255	/* send event to all queues/clients/ports/channels */
#घोषणा SNDRV_SEQ_QUEUE_सूचीECT		253	/* direct dispatch */

	/* event mode flag - NOTE: only 8 bits available! */
#घोषणा SNDRV_SEQ_TIME_STAMP_TICK	(0<<0) /* बारtamp in घड़ी ticks */
#घोषणा SNDRV_SEQ_TIME_STAMP_REAL	(1<<0) /* बारtamp in real समय */
#घोषणा SNDRV_SEQ_TIME_STAMP_MASK	(1<<0)

#घोषणा SNDRV_SEQ_TIME_MODE_ABS		(0<<1)	/* असलolute बारtamp */
#घोषणा SNDRV_SEQ_TIME_MODE_REL		(1<<1)	/* relative to current समय */
#घोषणा SNDRV_SEQ_TIME_MODE_MASK	(1<<1)

#घोषणा SNDRV_SEQ_EVENT_LENGTH_FIXED	(0<<2)	/* fixed event size */
#घोषणा SNDRV_SEQ_EVENT_LENGTH_VARIABLE	(1<<2)	/* variable event size */
#घोषणा SNDRV_SEQ_EVENT_LENGTH_VARUSR	(2<<2)	/* variable event size - user memory space */
#घोषणा SNDRV_SEQ_EVENT_LENGTH_MASK	(3<<2)

#घोषणा SNDRV_SEQ_PRIORITY_NORMAL	(0<<4)	/* normal priority */
#घोषणा SNDRV_SEQ_PRIORITY_HIGH		(1<<4)	/* event should be processed beक्रमe others */
#घोषणा SNDRV_SEQ_PRIORITY_MASK		(1<<4)


	/* note event */
काष्ठा snd_seq_ev_note अणु
	अचिन्हित अक्षर channel;
	अचिन्हित अक्षर note;
	अचिन्हित अक्षर velocity;
	अचिन्हित अक्षर off_velocity;	/* only क्रम SNDRV_SEQ_EVENT_NOTE */
	अचिन्हित पूर्णांक duration;		/* only क्रम SNDRV_SEQ_EVENT_NOTE */
पूर्ण;

	/* controller event */
काष्ठा snd_seq_ev_ctrl अणु
	अचिन्हित अक्षर channel;
	अचिन्हित अक्षर unused1, unused2, unused3;	/* pad */
	अचिन्हित पूर्णांक param;
	चिन्हित पूर्णांक value;
पूर्ण;

	/* generic set of bytes (12x8 bit) */
काष्ठा snd_seq_ev_raw8 अणु
	अचिन्हित अक्षर d[12];	/* 8 bit value */
पूर्ण;

	/* generic set of पूर्णांकegers (3x32 bit) */
काष्ठा snd_seq_ev_raw32 अणु
	अचिन्हित पूर्णांक d[3];	/* 32 bit value */
पूर्ण;

	/* बाह्यal stored data */
काष्ठा snd_seq_ev_ext अणु
	अचिन्हित पूर्णांक len;	/* length of data */
	व्योम *ptr;		/* poपूर्णांकer to data (note: maybe 64-bit) */
पूर्ण __attribute__((packed));

काष्ठा snd_seq_result अणु
	पूर्णांक event;		/* processed event type */
	पूर्णांक result;
पूर्ण;


काष्ठा snd_seq_real_समय अणु
	अचिन्हित पूर्णांक tv_sec;	/* seconds */
	अचिन्हित पूर्णांक tv_nsec;	/* nanoseconds */
पूर्ण;

प्रकार अचिन्हित पूर्णांक snd_seq_tick_समय_प्रकार;	/* midi ticks */

जोड़ snd_seq_बारtamp अणु
	snd_seq_tick_समय_प्रकार tick;
	काष्ठा snd_seq_real_समय समय;
पूर्ण;

काष्ठा snd_seq_queue_skew अणु
	अचिन्हित पूर्णांक value;
	अचिन्हित पूर्णांक base;
पूर्ण;

	/* queue समयr control */
काष्ठा snd_seq_ev_queue_control अणु
	अचिन्हित अक्षर queue;			/* affected queue */
	अचिन्हित अक्षर pad[3];			/* reserved */
	जोड़ अणु
		चिन्हित पूर्णांक value;		/* affected value (e.g. tempo) */
		जोड़ snd_seq_बारtamp समय;	/* समय */
		अचिन्हित पूर्णांक position;		/* sync position */
		काष्ठा snd_seq_queue_skew skew;
		अचिन्हित पूर्णांक d32[2];
		अचिन्हित अक्षर d8[8];
	पूर्ण param;
पूर्ण;

	/* quoted event - inside the kernel only */
काष्ठा snd_seq_ev_quote अणु
	काष्ठा snd_seq_addr origin;		/* original sender */
	अचिन्हित लघु value;		/* optional data */
	काष्ठा snd_seq_event *event;		/* quoted event */
पूर्ण __attribute__((packed));


	/* sequencer event */
काष्ठा snd_seq_event अणु
	snd_seq_event_type_t type;	/* event type */
	अचिन्हित अक्षर flags;		/* event flags */
	अक्षर tag;
	
	अचिन्हित अक्षर queue;		/* schedule queue */
	जोड़ snd_seq_बारtamp समय;	/* schedule समय */


	काष्ठा snd_seq_addr source;	/* source address */
	काष्ठा snd_seq_addr dest;	/* destination address */

	जोड़ अणु				/* event data... */
		काष्ठा snd_seq_ev_note note;
		काष्ठा snd_seq_ev_ctrl control;
		काष्ठा snd_seq_ev_raw8 raw8;
		काष्ठा snd_seq_ev_raw32 raw32;
		काष्ठा snd_seq_ev_ext ext;
		काष्ठा snd_seq_ev_queue_control queue;
		जोड़ snd_seq_बारtamp समय;
		काष्ठा snd_seq_addr addr;
		काष्ठा snd_seq_connect connect;
		काष्ठा snd_seq_result result;
		काष्ठा snd_seq_ev_quote quote;
	पूर्ण data;
पूर्ण;


/*
 * bounce event - stored as variable size data
 */
काष्ठा snd_seq_event_bounce अणु
	पूर्णांक err;
	काष्ठा snd_seq_event event;
	/* बाह्यal data follows here. */
पूर्ण;


	/* प्रणाली inक्रमmation */
काष्ठा snd_seq_प्रणाली_info अणु
	पूर्णांक queues;			/* maximum queues count */
	पूर्णांक clients;			/* maximum clients count */
	पूर्णांक ports;			/* maximum ports per client */
	पूर्णांक channels;			/* maximum channels per port */
	पूर्णांक cur_clients;		/* current clients */
	पूर्णांक cur_queues;			/* current queues */
	अक्षर reserved[24];
पूर्ण;


	/* प्रणाली running inक्रमmation */
काष्ठा snd_seq_running_info अणु
	अचिन्हित अक्षर client;		/* client id */
	अचिन्हित अक्षर big_endian;	/* 1 = big-endian */
	अचिन्हित अक्षर cpu_mode;		/* 4 = 32bit, 8 = 64bit */
	अचिन्हित अक्षर pad;		/* reserved */
	अचिन्हित अक्षर reserved[12];
पूर्ण;


	/* known client numbers */
#घोषणा SNDRV_SEQ_CLIENT_SYSTEM		0
	/* पूर्णांकernal client numbers */
#घोषणा SNDRV_SEQ_CLIENT_DUMMY		14	/* midi through */
#घोषणा SNDRV_SEQ_CLIENT_OSS		15	/* oss sequencer emulator */


	/* client types */
प्रकार पूर्णांक __bitwise snd_seq_client_type_t;
#घोषणा	NO_CLIENT	((__क्रमce snd_seq_client_type_t) 0)
#घोषणा	USER_CLIENT	((__क्रमce snd_seq_client_type_t) 1)
#घोषणा	KERNEL_CLIENT	((__क्रमce snd_seq_client_type_t) 2)
                        
	/* event filter flags */
#घोषणा SNDRV_SEQ_FILTER_BROADCAST	(1<<0)	/* accept broadcast messages */
#घोषणा SNDRV_SEQ_FILTER_MULTICAST	(1<<1)	/* accept multicast messages */
#घोषणा SNDRV_SEQ_FILTER_BOUNCE		(1<<2)	/* accept bounce event in error */
#घोषणा SNDRV_SEQ_FILTER_USE_EVENT	(1<<31)	/* use event filter */

काष्ठा snd_seq_client_info अणु
	पूर्णांक client;			/* client number to inquire */
	snd_seq_client_type_t type;	/* client type */
	अक्षर name[64];			/* client name */
	अचिन्हित पूर्णांक filter;		/* filter flags */
	अचिन्हित अक्षर multicast_filter[8]; /* multicast filter biपंचांगap */
	अचिन्हित अक्षर event_filter[32];	/* event filter biपंचांगap */
	पूर्णांक num_ports;			/* RO: number of ports */
	पूर्णांक event_lost;			/* number of lost events */
	पूर्णांक card;			/* RO: card number[kernel] */
	पूर्णांक pid;			/* RO: pid[user] */
	अक्षर reserved[56];		/* क्रम future use */
पूर्ण;


/* client pool size */
काष्ठा snd_seq_client_pool अणु
	पूर्णांक client;			/* client number to inquire */
	पूर्णांक output_pool;		/* outgoing (ग_लिखो) pool size */
	पूर्णांक input_pool;			/* incoming (पढ़ो) pool size */
	पूर्णांक output_room;		/* minimum मुक्त pool size क्रम select/blocking mode */
	पूर्णांक output_मुक्त;		/* unused size */
	पूर्णांक input_मुक्त;			/* unused size */
	अक्षर reserved[64];
पूर्ण;


/* Remove events by specअगरied criteria */

#घोषणा SNDRV_SEQ_REMOVE_INPUT		(1<<0)	/* Flush input queues */
#घोषणा SNDRV_SEQ_REMOVE_OUTPUT		(1<<1)	/* Flush output queues */
#घोषणा SNDRV_SEQ_REMOVE_DEST		(1<<2)	/* Restrict by destination q:client:port */
#घोषणा SNDRV_SEQ_REMOVE_DEST_CHANNEL	(1<<3)	/* Restrict by channel */
#घोषणा SNDRV_SEQ_REMOVE_TIME_BEFORE	(1<<4)	/* Restrict to beक्रमe समय */
#घोषणा SNDRV_SEQ_REMOVE_TIME_AFTER	(1<<5)	/* Restrict to समय or after */
#घोषणा SNDRV_SEQ_REMOVE_TIME_TICK	(1<<6)	/* Time is in ticks */
#घोषणा SNDRV_SEQ_REMOVE_EVENT_TYPE	(1<<7)	/* Restrict to event type */
#घोषणा SNDRV_SEQ_REMOVE_IGNORE_OFF 	(1<<8)	/* Do not flush off events */
#घोषणा SNDRV_SEQ_REMOVE_TAG_MATCH 	(1<<9)	/* Restrict to events with given tag */

काष्ठा snd_seq_हटाओ_events अणु
	अचिन्हित पूर्णांक  हटाओ_mode;	/* Flags that determine what माला_लो हटाओd */

	जोड़ snd_seq_बारtamp समय;

	अचिन्हित अक्षर queue;	/* Queue क्रम REMOVE_DEST */
	काष्ठा snd_seq_addr dest;	/* Address क्रम REMOVE_DEST */
	अचिन्हित अक्षर channel;	/* Channel क्रम REMOVE_DEST */

	पूर्णांक  type;	/* For REMOVE_EVENT_TYPE */
	अक्षर  tag;	/* Tag क्रम REMOVE_TAG */

	पूर्णांक  reserved[10];	/* To allow क्रम future binary compatibility */

पूर्ण;


	/* known port numbers */
#घोषणा SNDRV_SEQ_PORT_SYSTEM_TIMER	0
#घोषणा SNDRV_SEQ_PORT_SYSTEM_ANNOUNCE	1

	/* port capabilities (32 bits) */
#घोषणा SNDRV_SEQ_PORT_CAP_READ		(1<<0)	/* पढ़ोable from this port */
#घोषणा SNDRV_SEQ_PORT_CAP_WRITE	(1<<1)	/* writable to this port */

#घोषणा SNDRV_SEQ_PORT_CAP_SYNC_READ	(1<<2)
#घोषणा SNDRV_SEQ_PORT_CAP_SYNC_WRITE	(1<<3)

#घोषणा SNDRV_SEQ_PORT_CAP_DUPLEX	(1<<4)

#घोषणा SNDRV_SEQ_PORT_CAP_SUBS_READ	(1<<5)	/* allow पढ़ो subscription */
#घोषणा SNDRV_SEQ_PORT_CAP_SUBS_WRITE	(1<<6)	/* allow ग_लिखो subscription */
#घोषणा SNDRV_SEQ_PORT_CAP_NO_EXPORT	(1<<7)	/* routing not allowed */

	/* port type */
#घोषणा SNDRV_SEQ_PORT_TYPE_SPECIFIC	(1<<0)	/* hardware specअगरic */
#घोषणा SNDRV_SEQ_PORT_TYPE_MIDI_GENERIC (1<<1)	/* generic MIDI device */
#घोषणा SNDRV_SEQ_PORT_TYPE_MIDI_GM	(1<<2)	/* General MIDI compatible device */
#घोषणा SNDRV_SEQ_PORT_TYPE_MIDI_GS	(1<<3)	/* GS compatible device */
#घोषणा SNDRV_SEQ_PORT_TYPE_MIDI_XG	(1<<4)	/* XG compatible device */
#घोषणा SNDRV_SEQ_PORT_TYPE_MIDI_MT32	(1<<5)	/* MT-32 compatible device */
#घोषणा SNDRV_SEQ_PORT_TYPE_MIDI_GM2	(1<<6)	/* General MIDI 2 compatible device */

/* other standards...*/
#घोषणा SNDRV_SEQ_PORT_TYPE_SYNTH	(1<<10)	/* Synth device (no MIDI compatible - direct wavetable) */
#घोषणा SNDRV_SEQ_PORT_TYPE_सूचीECT_SAMPLE (1<<11)	/* Sampling device (support sample करोwnload) */
#घोषणा SNDRV_SEQ_PORT_TYPE_SAMPLE	(1<<12)	/* Sampling device (sample can be करोwnloaded at any समय) */
/*...*/
#घोषणा SNDRV_SEQ_PORT_TYPE_HARDWARE	(1<<16)	/* driver क्रम a hardware device */
#घोषणा SNDRV_SEQ_PORT_TYPE_SOFTWARE	(1<<17)	/* implemented in software */
#घोषणा SNDRV_SEQ_PORT_TYPE_SYNTHESIZER	(1<<18)	/* generates sound */
#घोषणा SNDRV_SEQ_PORT_TYPE_PORT	(1<<19)	/* connects to other device(s) */
#घोषणा SNDRV_SEQ_PORT_TYPE_APPLICATION	(1<<20)	/* application (sequencer/editor) */

/* misc. conditioning flags */
#घोषणा SNDRV_SEQ_PORT_FLG_GIVEN_PORT	(1<<0)
#घोषणा SNDRV_SEQ_PORT_FLG_TIMESTAMP	(1<<1)
#घोषणा SNDRV_SEQ_PORT_FLG_TIME_REAL	(1<<2)

काष्ठा snd_seq_port_info अणु
	काष्ठा snd_seq_addr addr;	/* client/port numbers */
	अक्षर name[64];			/* port name */

	अचिन्हित पूर्णांक capability;	/* port capability bits */
	अचिन्हित पूर्णांक type;		/* port type bits */
	पूर्णांक midi_channels;		/* channels per MIDI port */
	पूर्णांक midi_voices;		/* voices per MIDI port */
	पूर्णांक synth_voices;		/* voices per SYNTH port */

	पूर्णांक पढ़ो_use;			/* R/O: subscribers क्रम output (from this port) */
	पूर्णांक ग_लिखो_use;			/* R/O: subscribers क्रम input (to this port) */

	व्योम *kernel;			/* reserved क्रम kernel use (must be शून्य) */
	अचिन्हित पूर्णांक flags;		/* misc. conditioning */
	अचिन्हित अक्षर समय_queue;	/* queue # क्रम बारtamping */
	अक्षर reserved[59];		/* क्रम future use */
पूर्ण;


/* queue flags */
#घोषणा SNDRV_SEQ_QUEUE_FLG_SYNC	(1<<0)	/* sync enabled */

/* queue inक्रमmation */
काष्ठा snd_seq_queue_info अणु
	पूर्णांक queue;		/* queue id */

	/*
	 *  security settings, only owner of this queue can start/stop समयr
	 *  etc. अगर the queue is locked क्रम other clients
	 */
	पूर्णांक owner;		/* client id क्रम owner of the queue */
	अचिन्हित locked:1;	/* timing queue locked क्रम other queues */
	अक्षर name[64];		/* name of this queue */
	अचिन्हित पूर्णांक flags;	/* flags */
	अक्षर reserved[60];	/* क्रम future use */

पूर्ण;

/* queue info/status */
काष्ठा snd_seq_queue_status अणु
	पूर्णांक queue;			/* queue id */
	पूर्णांक events;			/* पढ़ो-only - queue size */
	snd_seq_tick_समय_प्रकार tick;	/* current tick */
	काष्ठा snd_seq_real_समय समय;	/* current समय */
	पूर्णांक running;			/* running state of queue */
	पूर्णांक flags;			/* various flags */
	अक्षर reserved[64];		/* क्रम the future */
पूर्ण;


/* queue tempo */
काष्ठा snd_seq_queue_tempo अणु
	पूर्णांक queue;			/* sequencer queue */
	अचिन्हित पूर्णांक tempo;		/* current tempo, us/tick */
	पूर्णांक ppq;			/* समय resolution, ticks/quarter */
	अचिन्हित पूर्णांक skew_value;	/* queue skew */
	अचिन्हित पूर्णांक skew_base;		/* queue skew base */
	अक्षर reserved[24];		/* क्रम the future */
पूर्ण;


/* sequencer समयr sources */
#घोषणा SNDRV_SEQ_TIMER_ALSA		0	/* ALSA समयr */
#घोषणा SNDRV_SEQ_TIMER_MIDI_CLOCK	1	/* Midi Clock (CLOCK event) */
#घोषणा SNDRV_SEQ_TIMER_MIDI_TICK	2	/* Midi Timer Tick (TICK event) */

/* queue समयr info */
काष्ठा snd_seq_queue_समयr अणु
	पूर्णांक queue;			/* sequencer queue */
	पूर्णांक type;			/* source समयr type */
	जोड़ अणु
		काष्ठा अणु
			काष्ठा snd_समयr_id id;	/* ALSA's समयr ID */
			अचिन्हित पूर्णांक resolution;	/* resolution in Hz */
		पूर्ण alsa;
	पूर्ण u;
	अक्षर reserved[64];		/* क्रम the future use */
पूर्ण;


काष्ठा snd_seq_queue_client अणु
	पूर्णांक queue;		/* sequencer queue */
	पूर्णांक client;		/* sequencer client */
	पूर्णांक used;		/* queue is used with this client
				   (must be set क्रम accepting events) */
	/* per client watermarks */
	अक्षर reserved[64];	/* क्रम future use */
पूर्ण;


#घोषणा SNDRV_SEQ_PORT_SUBS_EXCLUSIVE	(1<<0)	/* exclusive connection */
#घोषणा SNDRV_SEQ_PORT_SUBS_TIMESTAMP	(1<<1)
#घोषणा SNDRV_SEQ_PORT_SUBS_TIME_REAL	(1<<2)

काष्ठा snd_seq_port_subscribe अणु
	काष्ठा snd_seq_addr sender;	/* sender address */
	काष्ठा snd_seq_addr dest;	/* destination address */
	अचिन्हित पूर्णांक voices;		/* number of voices to be allocated (0 = करोn't care) */
	अचिन्हित पूर्णांक flags;		/* modes */
	अचिन्हित अक्षर queue;		/* input समय-stamp queue (optional) */
	अचिन्हित अक्षर pad[3];		/* reserved */
	अक्षर reserved[64];
पूर्ण;

/* type of query subscription */
#घोषणा SNDRV_SEQ_QUERY_SUBS_READ	0
#घोषणा SNDRV_SEQ_QUERY_SUBS_WRITE	1

काष्ठा snd_seq_query_subs अणु
	काष्ठा snd_seq_addr root;	/* client/port id to be searched */
	पूर्णांक type;		/* READ or WRITE */
	पूर्णांक index;		/* 0..N-1 */
	पूर्णांक num_subs;		/* R/O: number of subscriptions on this port */
	काष्ठा snd_seq_addr addr;	/* R/O: result */
	अचिन्हित अक्षर queue;	/* R/O: result */
	अचिन्हित पूर्णांक flags;	/* R/O: result */
	अक्षर reserved[64];	/* क्रम future use */
पूर्ण;


/*
 *  IOCTL commands
 */

#घोषणा SNDRV_SEQ_IOCTL_PVERSION	_IOR ('S', 0x00, पूर्णांक)
#घोषणा SNDRV_SEQ_IOCTL_CLIENT_ID	_IOR ('S', 0x01, पूर्णांक)
#घोषणा SNDRV_SEQ_IOCTL_SYSTEM_INFO	_IOWR('S', 0x02, काष्ठा snd_seq_प्रणाली_info)
#घोषणा SNDRV_SEQ_IOCTL_RUNNING_MODE	_IOWR('S', 0x03, काष्ठा snd_seq_running_info)

#घोषणा SNDRV_SEQ_IOCTL_GET_CLIENT_INFO	_IOWR('S', 0x10, काष्ठा snd_seq_client_info)
#घोषणा SNDRV_SEQ_IOCTL_SET_CLIENT_INFO	_IOW ('S', 0x11, काष्ठा snd_seq_client_info)

#घोषणा SNDRV_SEQ_IOCTL_CREATE_PORT	_IOWR('S', 0x20, काष्ठा snd_seq_port_info)
#घोषणा SNDRV_SEQ_IOCTL_DELETE_PORT	_IOW ('S', 0x21, काष्ठा snd_seq_port_info)
#घोषणा SNDRV_SEQ_IOCTL_GET_PORT_INFO	_IOWR('S', 0x22, काष्ठा snd_seq_port_info)
#घोषणा SNDRV_SEQ_IOCTL_SET_PORT_INFO	_IOW ('S', 0x23, काष्ठा snd_seq_port_info)

#घोषणा SNDRV_SEQ_IOCTL_SUBSCRIBE_PORT	_IOW ('S', 0x30, काष्ठा snd_seq_port_subscribe)
#घोषणा SNDRV_SEQ_IOCTL_UNSUBSCRIBE_PORT _IOW ('S', 0x31, काष्ठा snd_seq_port_subscribe)

#घोषणा SNDRV_SEQ_IOCTL_CREATE_QUEUE	_IOWR('S', 0x32, काष्ठा snd_seq_queue_info)
#घोषणा SNDRV_SEQ_IOCTL_DELETE_QUEUE	_IOW ('S', 0x33, काष्ठा snd_seq_queue_info)
#घोषणा SNDRV_SEQ_IOCTL_GET_QUEUE_INFO	_IOWR('S', 0x34, काष्ठा snd_seq_queue_info)
#घोषणा SNDRV_SEQ_IOCTL_SET_QUEUE_INFO	_IOWR('S', 0x35, काष्ठा snd_seq_queue_info)
#घोषणा SNDRV_SEQ_IOCTL_GET_NAMED_QUEUE	_IOWR('S', 0x36, काष्ठा snd_seq_queue_info)
#घोषणा SNDRV_SEQ_IOCTL_GET_QUEUE_STATUS _IOWR('S', 0x40, काष्ठा snd_seq_queue_status)
#घोषणा SNDRV_SEQ_IOCTL_GET_QUEUE_TEMPO	_IOWR('S', 0x41, काष्ठा snd_seq_queue_tempo)
#घोषणा SNDRV_SEQ_IOCTL_SET_QUEUE_TEMPO	_IOW ('S', 0x42, काष्ठा snd_seq_queue_tempo)
#घोषणा SNDRV_SEQ_IOCTL_GET_QUEUE_TIMER	_IOWR('S', 0x45, काष्ठा snd_seq_queue_समयr)
#घोषणा SNDRV_SEQ_IOCTL_SET_QUEUE_TIMER	_IOW ('S', 0x46, काष्ठा snd_seq_queue_समयr)
#घोषणा SNDRV_SEQ_IOCTL_GET_QUEUE_CLIENT	_IOWR('S', 0x49, काष्ठा snd_seq_queue_client)
#घोषणा SNDRV_SEQ_IOCTL_SET_QUEUE_CLIENT	_IOW ('S', 0x4a, काष्ठा snd_seq_queue_client)
#घोषणा SNDRV_SEQ_IOCTL_GET_CLIENT_POOL	_IOWR('S', 0x4b, काष्ठा snd_seq_client_pool)
#घोषणा SNDRV_SEQ_IOCTL_SET_CLIENT_POOL	_IOW ('S', 0x4c, काष्ठा snd_seq_client_pool)
#घोषणा SNDRV_SEQ_IOCTL_REMOVE_EVENTS	_IOW ('S', 0x4e, काष्ठा snd_seq_हटाओ_events)
#घोषणा SNDRV_SEQ_IOCTL_QUERY_SUBS	_IOWR('S', 0x4f, काष्ठा snd_seq_query_subs)
#घोषणा SNDRV_SEQ_IOCTL_GET_SUBSCRIPTION	_IOWR('S', 0x50, काष्ठा snd_seq_port_subscribe)
#घोषणा SNDRV_SEQ_IOCTL_QUERY_NEXT_CLIENT	_IOWR('S', 0x51, काष्ठा snd_seq_client_info)
#घोषणा SNDRV_SEQ_IOCTL_QUERY_NEXT_PORT	_IOWR('S', 0x52, काष्ठा snd_seq_port_info)

#पूर्ण_अगर /* _UAPI__SOUND_ASEQUENCER_H */
