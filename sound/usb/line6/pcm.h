<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Line 6 Linux USB driver
 *
 * Copyright (C) 2004-2010 Markus Grabner (grabner@icg.tugraz.at)
 */

/*
	PCM पूर्णांकerface to POD series devices.
*/

#अगर_अघोषित PCM_H
#घोषणा PCM_H

#समावेश <sound/pcm.h>

#समावेश "driver.h"

/*
	number of USB frames per URB
	The Line 6 Winकरोws driver always transmits two frames per packet, but
	the Linux driver perक्रमms signअगरicantly better (i.e., lower latency)
	with only one frame per packet.
*/
#घोषणा LINE6_ISO_PACKETS	1

/* in a "full speed" device (such as the PODxt Pro) this means 1ms,
 *  क्रम "high speed" it's 1/8ms
 */
#घोषणा LINE6_ISO_INTERVAL	1

#घोषणा LINE6_IMPULSE_DEFAULT_PERIOD 100

/*
	Get substream from Line 6 PCM data काष्ठाure
*/
#घोषणा get_substream(line6pcm, stream)	\
		(line6pcm->pcm->streams[stream].substream)

/*
	PCM mode bits.

	There are several features of the Line 6 USB driver which require PCM
	data to be exchanged with the device:
	*) PCM playback and capture via ALSA
	*) software monitoring (क्रम devices without hardware monitoring)
	*) optional impulse response measurement
	However, from the device's poपूर्णांक of view, there is just a single
	capture and playback stream, which must be shared between these
	subप्रणालीs. It is thereक्रमe necessary to मुख्यtain the state of the
	subप्रणालीs with respect to PCM usage.

	We define two bit flags, "opened" and "running", क्रम each playback
	or capture stream.  Both can contain the bit flag corresponding to
	LINE6_STREAM_* type,
	  LINE6_STREAM_PCM = ALSA PCM playback or capture
	  LINE6_STREAM_MONITOR = software monitoring
	  IMPULSE = optional impulse response measurement
	The खोलोed flag indicates whether the buffer is allocated जबतक
	the running flag indicates whether the stream is running.

	For monitor or impulse operations, the driver needs to call
	line6_pcm_acquire() or line6_pcm_release() with the appropriate
	LINE6_STREAM_* flag.
*/

/* stream types */
क्रमागत अणु
	LINE6_STREAM_PCM,
	LINE6_STREAM_MONITOR,
	LINE6_STREAM_IMPULSE,
	LINE6_STREAM_CAPTURE_HELPER,
पूर्ण;

/* misc bit flags क्रम PCM operation */
क्रमागत अणु
	LINE6_FLAG_PAUSE_PLAYBACK,
	LINE6_FLAG_PREPARED,
पूर्ण;

काष्ठा line6_pcm_properties अणु
	काष्ठा snd_pcm_hardware playback_hw, capture_hw;
	काष्ठा snd_pcm_hw_स्थिरraपूर्णांक_ratdens rates;
	पूर्णांक bytes_per_channel;
पूर्ण;

काष्ठा line6_pcm_stream अणु
	/* allocated URBs */
	काष्ठा urb **urbs;

	/* Temporary buffer;
	 * Since the packet size is not known in advance, this buffer is
	 * large enough to store maximum size packets.
	 */
	अचिन्हित अक्षर *buffer;

	/* Free frame position in the buffer. */
	snd_pcm_uframes_t pos;

	/* Count processed bytes;
	 * This is modulo period size (to determine when a period is finished).
	 */
	अचिन्हित bytes;

	/* Counter to create desired sample rate */
	अचिन्हित count;

	/* period size in bytes */
	अचिन्हित period;

	/* Processed frame position in the buffer;
	 * The contents of the ring buffer have been consumed by the USB
	 * subप्रणाली (i.e., sent to the USB device) up to this position.
	 */
	snd_pcm_uframes_t pos_करोne;

	/* Bit mask of active URBs */
	अचिन्हित दीर्घ active_urbs;

	/* Bit mask of URBs currently being unlinked */
	अचिन्हित दीर्घ unlink_urbs;

	/* Spin lock to protect updates of the buffer positions (not contents)
	 */
	spinlock_t lock;

	/* Bit flags क्रम operational stream types */
	अचिन्हित दीर्घ खोलोed;

	/* Bit flags क्रम running stream types */
	अचिन्हित दीर्घ running;

	पूर्णांक last_frame;
पूर्ण;

काष्ठा snd_line6_pcm अणु
	/* Poपूर्णांकer back to the Line 6 driver data काष्ठाure */
	काष्ठा usb_line6 *line6;

	/* Properties. */
	काष्ठा line6_pcm_properties *properties;

	/* ALSA pcm stream */
	काष्ठा snd_pcm *pcm;

	/* protection to state changes of in/out streams */
	काष्ठा mutex state_mutex;

	/* Capture and playback streams */
	काष्ठा line6_pcm_stream in;
	काष्ठा line6_pcm_stream out;

	/* Previously captured frame (क्रम software monitoring) */
	अचिन्हित अक्षर *prev_fbuf;

	/* Size of previously captured frame (क्रम software monitoring/sync) */
	पूर्णांक prev_fsize;

	/* Maximum size of USB packet */
	पूर्णांक max_packet_size_in;
	पूर्णांक max_packet_size_out;

	/* PCM playback volume (left and right) */
	पूर्णांक volume_playback[2];

	/* PCM monitor volume */
	पूर्णांक volume_monitor;

	/* Volume of impulse response test संकेत (अगर zero, test is disabled) */
	पूर्णांक impulse_volume;

	/* Period of impulse response test संकेत */
	पूर्णांक impulse_period;

	/* Counter क्रम impulse response test संकेत */
	पूर्णांक impulse_count;

	/* Several status bits (see LINE6_FLAG_*) */
	अचिन्हित दीर्घ flags;
पूर्ण;

बाह्य पूर्णांक line6_init_pcm(काष्ठा usb_line6 *line6,
			  काष्ठा line6_pcm_properties *properties);
बाह्य पूर्णांक snd_line6_trigger(काष्ठा snd_pcm_substream *substream, पूर्णांक cmd);
बाह्य पूर्णांक snd_line6_prepare(काष्ठा snd_pcm_substream *substream);
बाह्य पूर्णांक snd_line6_hw_params(काष्ठा snd_pcm_substream *substream,
			       काष्ठा snd_pcm_hw_params *hw_params);
बाह्य पूर्णांक snd_line6_hw_मुक्त(काष्ठा snd_pcm_substream *substream);
बाह्य snd_pcm_uframes_t snd_line6_poपूर्णांकer(काष्ठा snd_pcm_substream *substream);
बाह्य व्योम line6_pcm_disconnect(काष्ठा snd_line6_pcm *line6pcm);
बाह्य पूर्णांक line6_pcm_acquire(काष्ठा snd_line6_pcm *line6pcm, पूर्णांक type,
			       bool start);
बाह्य व्योम line6_pcm_release(काष्ठा snd_line6_pcm *line6pcm, पूर्णांक type);

#पूर्ण_अगर
