<शैली गुरु>
/*
 * Copyright (C) 2016 Intel Corporation
 *  Authors:	Sailaja Bandarupalli <sailaja.bandarupalli@पूर्णांकel.com>
 *		Ramesh Babu K V	<ramesh.babu@पूर्णांकel.com>
 *		Vaibhav Agarwal <vaibhav.agarwal@पूर्णांकel.com>
 *		Jerome Anand <jerome.anand@पूर्णांकel.com>
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining
 * a copy of this software and associated करोcumentation files
 * (the "Software"), to deal in the Software without restriction,
 * including without limitation the rights to use, copy, modअगरy, merge,
 * publish, distribute, sublicense, and/or sell copies of the Software,
 * and to permit persons to whom the Software is furnished to करो so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the
 * next paragraph) shall be included in all copies or substantial
 * portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT.  IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#अगर_अघोषित _INTEL_HDMI_AUDIO_H_
#घोषणा _INTEL_HDMI_AUDIO_H_

#समावेश "intel_hdmi_lpe_audio.h"

#घोषणा MAX_PB_STREAMS		1
#घोषणा MAX_CAP_STREAMS		0
#घोषणा BYTES_PER_WORD		0x4
#घोषणा INTEL_HAD		"HdmiLpeAudio"

/*
 *	CEA speaker placement:
 *
 *	FL  FLC   FC   FRC   FR
 *
 *						LFE
 *
 *	RL  RLC   RC   RRC   RR
 *
 *	The Left/Right Surround channel _notions_ LS/RS in SMPTE 320M
 *	corresponds to CEA RL/RR; The SMPTE channel _assignment_ C/LFE is
 *	swapped to CEA LFE/FC.
 */
क्रमागत cea_speaker_placement अणु
	FL  = (1 <<  0),        /* Front Left           */
	FC  = (1 <<  1),        /* Front Center         */
	FR  = (1 <<  2),        /* Front Right          */
	FLC = (1 <<  3),        /* Front Left Center    */
	FRC = (1 <<  4),        /* Front Right Center   */
	RL  = (1 <<  5),        /* Rear Left            */
	RC  = (1 <<  6),        /* Rear Center          */
	RR  = (1 <<  7),        /* Rear Right           */
	RLC = (1 <<  8),        /* Rear Left Center     */
	RRC = (1 <<  9),        /* Rear Right Center    */
	LFE = (1 << 10),        /* Low Frequency Effect */
पूर्ण;

काष्ठा cea_channel_speaker_allocation अणु
	पूर्णांक ca_index;
	पूर्णांक speakers[8];

	/* derived values, just क्रम convenience */
	पूर्णांक channels;
	पूर्णांक spk_mask;
पूर्ण;

काष्ठा channel_map_table अणु
	अचिन्हित अक्षर map;              /* ALSA API channel map position */
	अचिन्हित अक्षर cea_slot;         /* CEA slot value */
	पूर्णांक spk_mask;                   /* speaker position bit mask */
पूर्ण;

काष्ठा pcm_stream_info अणु
	काष्ठा snd_pcm_substream *substream;
	पूर्णांक substream_refcount;
पूर्ण;

/*
 * काष्ठा snd_पूर्णांकelhad - पूर्णांकelhad driver काष्ठाure
 *
 * @card: ptr to hold card details
 * @connected: the monitor connection status
 * @stream_info: stream inक्रमmation
 * @eld: holds ELD info
 * @curr_buf: poपूर्णांकer to hold current active ring buf
 * @valid_buf_cnt: ring buffer count क्रम stream
 * @had_spinlock: driver lock
 * @aes_bits: IEC958 status bits
 * @buff_करोne: id of current buffer करोne पूर्णांकr
 * @dev: plम_से_भorm device handle
 * @chmap: holds channel map info
 */
काष्ठा snd_पूर्णांकelhad अणु
	काष्ठा snd_पूर्णांकelhad_card *card_ctx;
	bool		connected;
	काष्ठा		pcm_stream_info stream_info;
	अचिन्हित अक्षर	eld[HDMI_MAX_ELD_BYTES];
	bool dp_output;
	अचिन्हित पूर्णांक	aes_bits;
	spinlock_t had_spinlock;
	काष्ठा device *dev;
	काष्ठा snd_pcm_chmap *chmap;
	पूर्णांक पंचांगds_घड़ी_speed;
	पूर्णांक link_rate;
	पूर्णांक port; /* fixed */
	पूर्णांक pipe; /* can change dynamically */

	/* ring buffer (BD) position index */
	अचिन्हित पूर्णांक bd_head;
	/* PCM buffer position indices */
	अचिन्हित पूर्णांक pcmbuf_head;	/* being processed */
	अचिन्हित पूर्णांक pcmbuf_filled;	/* to be filled */

	अचिन्हित पूर्णांक num_bds;		/* number of BDs */
	अचिन्हित पूर्णांक period_bytes;	/* PCM period size in bytes */

	/* पूर्णांकernal stuff */
	जोड़ aud_cfg aud_config;	/* AUD_CONFIG reg value cache */
	काष्ठा work_काष्ठा hdmi_audio_wq;
	काष्ठा mutex mutex; /* क्रम protecting chmap and eld */
	bool need_reset;
	काष्ठा snd_jack *jack;
पूर्ण;

काष्ठा snd_पूर्णांकelhad_card अणु
	काष्ठा snd_card	*card;
	काष्ठा device *dev;

	/* पूर्णांकernal stuff */
	पूर्णांक irq;
	व्योम __iomem *mmio_start;
	पूर्णांक num_pipes;
	पूर्णांक num_ports;
	काष्ठा snd_पूर्णांकelhad pcm_ctx[3]; /* one क्रम each port */
पूर्ण;

#पूर्ण_अगर /* _INTEL_HDMI_AUDIO_ */
