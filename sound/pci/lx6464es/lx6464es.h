<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/* -*- linux-c -*- *
 *
 * ALSA driver क्रम the digigram lx6464es पूर्णांकerface
 *
 * Copyright (c) 2009 Tim Blechmann <tim@klingt.org>
 */

#अगर_अघोषित LX6464ES_H
#घोषणा LX6464ES_H

#समावेश <linux/spinlock.h>
#समावेश <linux/atomic.h>

#समावेश <sound/core.h>
#समावेश <sound/pcm.h>

#समावेश "lx_core.h"

#घोषणा LXP "LX6464ES: "

क्रमागत अणु
    ES_cmd_मुक्त         = 0,    /* no command executing */
    ES_cmd_processing   = 1,	/* execution of a पढ़ो/ग_लिखो command */
    ES_पढ़ो_pending     = 2,    /* a asynchron पढ़ो command is pending */
    ES_पढ़ो_finishing   = 3,    /* a पढ़ो command has finished रुकोing (set by
				 * Interrupt or CancelIrp) */
पूर्ण;

क्रमागत lx_stream_status अणु
	LX_STREAM_STATUS_FREE,
/* 	LX_STREAM_STATUS_OPEN, */
	LX_STREAM_STATUS_SCHEDULE_RUN,
/* 	LX_STREAM_STATUS_STARTED, */
	LX_STREAM_STATUS_RUNNING,
	LX_STREAM_STATUS_SCHEDULE_STOP,
/* 	LX_STREAM_STATUS_STOPPED, */
/* 	LX_STREAM_STATUS_PAUSED */
पूर्ण;


काष्ठा lx_stream अणु
	काष्ठा snd_pcm_substream  *stream;
	snd_pcm_uframes_t          frame_pos;
	क्रमागत lx_stream_status      status; /* मुक्त, खोलो, running, draining
					    * छोड़ो */
	अचिन्हित पूर्णांक               is_capture:1;
पूर्ण;


काष्ठा lx6464es अणु
	काष्ठा snd_card        *card;
	काष्ठा pci_dev         *pci;
	पूर्णांक			irq;

	u8			mac_address[6];

	काष्ठा mutex		lock;        /* पूर्णांकerrupt lock */
	काष्ठा mutex            setup_mutex; /* mutex used in hw_params, खोलो
					      * and बंद */

	/* ports */
	अचिन्हित दीर्घ		port_plx;	   /* io port (size=256) */
	व्योम __iomem           *port_plx_remapped; /* remapped plx port */
	व्योम __iomem           *port_dsp_bar;      /* memory port (32-bit,
						    * non-prefetchable,
						    * size=8K) */

	/* messaging */
	काष्ठा mutex		msg_lock;          /* message lock */
	काष्ठा lx_rmh           rmh;
	u32			irqsrc;

	/* configuration */
	uपूर्णांक			freq_ratio : 2;
	uपूर्णांक                    playback_mute : 1;
	uपूर्णांक                    hardware_running[2];
	u32                     board_sample_rate; /* sample rate पढ़ो from
						    * board */
	u16                     pcm_granularity;   /* board blocksize */

	/* dma */
	काष्ठा snd_dma_buffer   capture_dma_buf;
	काष्ठा snd_dma_buffer   playback_dma_buf;

	/* pcm */
	काष्ठा snd_pcm         *pcm;

	/* streams */
	काष्ठा lx_stream        capture_stream;
	काष्ठा lx_stream        playback_stream;
पूर्ण;


#पूर्ण_अगर /* LX6464ES_H */
