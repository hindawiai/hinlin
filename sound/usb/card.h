<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __USBAUDIO_CARD_H
#घोषणा __USBAUDIO_CARD_H

#घोषणा MAX_NR_RATES	1024
#घोषणा MAX_PACKS	6		/* per URB */
#घोषणा MAX_PACKS_HS	(MAX_PACKS * 8)	/* in high speed mode */
#घोषणा MAX_URBS	12
#घोषणा SYNC_URBS	4	/* always four urbs क्रम sync */
#घोषणा MAX_QUEUE	18	/* try not to exceed this queue length, in ms */

काष्ठा audioक्रमmat अणु
	काष्ठा list_head list;
	u64 क्रमmats;			/* ALSA क्रमmat bits */
	अचिन्हित पूर्णांक channels;		/* # channels */
	अचिन्हित पूर्णांक fmt_type;		/* USB audio क्रमmat type (1-3) */
	अचिन्हित पूर्णांक fmt_bits;		/* number of signअगरicant bits */
	अचिन्हित पूर्णांक frame_size;	/* samples per frame क्रम non-audio */
	अचिन्हित अक्षर अगरace;		/* पूर्णांकerface number */
	अचिन्हित अक्षर altsetting;	/* corresponding alternate setting */
	अचिन्हित अक्षर ep_idx;		/* endpoपूर्णांक array index */
	अचिन्हित अक्षर altset_idx;	/* array index of altenate setting */
	अचिन्हित अक्षर attributes;	/* corresponding attributes of cs endpoपूर्णांक */
	अचिन्हित अक्षर endpoपूर्णांक;		/* endpoपूर्णांक */
	अचिन्हित अक्षर ep_attr;		/* endpoपूर्णांक attributes */
	bool implicit_fb;		/* implicit feedback endpoपूर्णांक */
	अचिन्हित अक्षर sync_ep;		/* sync endpoपूर्णांक number */
	अचिन्हित अक्षर sync_अगरace;	/* sync EP पूर्णांकerface */
	अचिन्हित अक्षर sync_altsetting;	/* sync EP alternate setting */
	अचिन्हित अक्षर sync_ep_idx;	/* sync EP array index */
	अचिन्हित अक्षर dataपूर्णांकerval;	/* log_2 of data packet पूर्णांकerval */
	अचिन्हित अक्षर protocol;		/* UAC_VERSION_1/2/3 */
	अचिन्हित पूर्णांक maxpacksize;	/* max. packet size */
	अचिन्हित पूर्णांक rates;		/* rate biपंचांगasks */
	अचिन्हित पूर्णांक rate_min, rate_max;	/* min/max rates */
	अचिन्हित पूर्णांक nr_rates;		/* number of rate table entries */
	अचिन्हित पूर्णांक *rate_table;	/* rate table */
	अचिन्हित अक्षर घड़ी;		/* associated घड़ी */
	काष्ठा snd_pcm_chmap_elem *chmap; /* (optional) channel map */
	bool dsd_करोp;			/* add DOP headers in हाल of DSD samples */
	bool dsd_bitrev;		/* reverse the bits of each DSD sample */
	bool dsd_raw;			/* altsetting is raw DSD */
पूर्ण;

काष्ठा snd_usb_substream;
काष्ठा snd_usb_अगरace_ref;
काष्ठा snd_usb_endpoपूर्णांक;
काष्ठा snd_usb_घातer_करोमुख्य;

काष्ठा snd_urb_ctx अणु
	काष्ठा urb *urb;
	अचिन्हित पूर्णांक buffer_size;	/* size of data buffer, अगर data URB */
	काष्ठा snd_usb_substream *subs;
	काष्ठा snd_usb_endpoपूर्णांक *ep;
	पूर्णांक index;	/* index क्रम urb array */
	पूर्णांक packets;	/* number of packets per urb */
	पूर्णांक packet_size[MAX_PACKS_HS]; /* size of packets क्रम next submission */
	काष्ठा list_head पढ़ोy_list;
पूर्ण;

काष्ठा snd_usb_endpoपूर्णांक अणु
	काष्ठा snd_usb_audio *chip;
	काष्ठा snd_usb_अगरace_ref *अगरace_ref;

	पूर्णांक खोलोed;		/* खोलो refcount; protect with chip->mutex */
	atomic_t running;	/* running status */
	पूर्णांक ep_num;		/* the referenced endpoपूर्णांक number */
	पूर्णांक type;		/* SND_USB_ENDPOINT_TYPE_* */

	अचिन्हित अक्षर अगरace;		/* पूर्णांकerface number */
	अचिन्हित अक्षर altsetting;	/* corresponding alternate setting */
	अचिन्हित अक्षर ep_idx;		/* endpoपूर्णांक array index */

	atomic_t state;		/* running state */

	व्योम (*prepare_data_urb) (काष्ठा snd_usb_substream *subs,
				  काष्ठा urb *urb);
	व्योम (*retire_data_urb) (काष्ठा snd_usb_substream *subs,
				 काष्ठा urb *urb);

	काष्ठा snd_usb_substream *data_subs;
	काष्ठा snd_usb_endpoपूर्णांक *sync_source;
	काष्ठा snd_usb_endpoपूर्णांक *sync_sink;

	काष्ठा snd_urb_ctx urb[MAX_URBS];

	काष्ठा snd_usb_packet_info अणु
		uपूर्णांक32_t packet_size[MAX_PACKS_HS];
		पूर्णांक packets;
	पूर्ण next_packet[MAX_URBS];
	अचिन्हित पूर्णांक next_packet_head;	/* ring buffer offset to पढ़ो */
	अचिन्हित पूर्णांक next_packet_queued; /* queued items in the ring buffer */
	काष्ठा list_head पढ़ोy_playback_urbs; /* playback URB FIFO क्रम implicit fb */

	अचिन्हित पूर्णांक nurbs;		/* # urbs */
	अचिन्हित दीर्घ active_mask;	/* biपंचांगask of active urbs */
	अचिन्हित दीर्घ unlink_mask;	/* biपंचांगask of unlinked urbs */
	अक्षर *syncbuf;			/* sync buffer क्रम all sync URBs */
	dma_addr_t sync_dma;		/* DMA address of syncbuf */

	अचिन्हित पूर्णांक pipe;		/* the data i/o pipe */
	अचिन्हित पूर्णांक packsize[2];	/* small/large packet sizes in samples */
	अचिन्हित पूर्णांक sample_rem;	/* reमुख्यder from भागision fs/pps */
	अचिन्हित पूर्णांक sample_accum;	/* sample accumulator */
	अचिन्हित पूर्णांक pps;		/* packets per second */
	अचिन्हित पूर्णांक freqn;		/* nominal sampling rate in fs/fps in Q16.16 क्रमmat */
	अचिन्हित पूर्णांक freqm;		/* momentary sampling rate in fs/fps in Q16.16 क्रमmat */
	पूर्णांक	   freqshअगरt;		/* how much to shअगरt the feedback value to get Q16.16 */
	अचिन्हित पूर्णांक freqmax;		/* maximum sampling rate, used क्रम buffer management */
	अचिन्हित पूर्णांक phase;		/* phase accumulator */
	अचिन्हित पूर्णांक maxpacksize;	/* max packet size in bytes */
	अचिन्हित पूर्णांक maxframesize;      /* max packet size in frames */
	अचिन्हित पूर्णांक max_urb_frames;	/* max URB size in frames */
	अचिन्हित पूर्णांक curpacksize;	/* current packet size in bytes (क्रम capture) */
	अचिन्हित पूर्णांक curframesize;      /* current packet size in frames (क्रम capture) */
	अचिन्हित पूर्णांक syncmaxsize;	/* sync endpoपूर्णांक packet size */
	अचिन्हित पूर्णांक fill_max:1;	/* fill max packet size always */
	अचिन्हित पूर्णांक tenor_fb_quirk:1;	/* corrupted feedback data */
	अचिन्हित पूर्णांक dataपूर्णांकerval;      /* log_2 of data packet पूर्णांकerval */
	अचिन्हित पूर्णांक syncपूर्णांकerval;	/* P क्रम adaptive mode, 0 otherwise */
	अचिन्हित अक्षर silence_value;
	अचिन्हित पूर्णांक stride;
	पूर्णांक skip_packets;		/* quirks क्रम devices to ignore the first n packets
					   in a stream */
	bool implicit_fb_sync;		/* syncs with implicit feedback */
	bool need_setup;		/* (re-)need क्रम configure? */

	/* क्रम hw स्थिरraपूर्णांकs */
	स्थिर काष्ठा audioक्रमmat *cur_audiofmt;
	अचिन्हित पूर्णांक cur_rate;
	snd_pcm_क्रमmat_t cur_क्रमmat;
	अचिन्हित पूर्णांक cur_channels;
	अचिन्हित पूर्णांक cur_frame_bytes;
	अचिन्हित पूर्णांक cur_period_frames;
	अचिन्हित पूर्णांक cur_period_bytes;
	अचिन्हित पूर्णांक cur_buffer_periods;

	spinlock_t lock;
	काष्ठा list_head list;
पूर्ण;

काष्ठा media_ctl;

काष्ठा snd_usb_substream अणु
	काष्ठा snd_usb_stream *stream;
	काष्ठा usb_device *dev;
	काष्ठा snd_pcm_substream *pcm_substream;
	पूर्णांक direction;	/* playback or capture */
	पूर्णांक endpoपूर्णांक;	/* asचिन्हित endpoपूर्णांक */
	स्थिर काष्ठा audioक्रमmat *cur_audiofmt;	/* current audioक्रमmat poपूर्णांकer (क्रम hw_params callback) */
	काष्ठा snd_usb_घातer_करोमुख्य *str_pd;	/* UAC3 Power Doमुख्य क्रम streaming path */
	अचिन्हित पूर्णांक channels_max;	/* max channels in the all audiofmts */
	अचिन्हित पूर्णांक txfr_quirk:1;	/* allow sub-frame alignment */
	अचिन्हित पूर्णांक tx_length_quirk:1;	/* add length specअगरier to transfers */
	अचिन्हित पूर्णांक fmt_type;		/* USB audio क्रमmat type (1-3) */
	अचिन्हित पूर्णांक pkt_offset_adj;	/* Bytes to drop from beginning of packets (क्रम non-compliant devices) */
	अचिन्हित पूर्णांक stream_offset_adj;	/* Bytes to drop from beginning of stream (क्रम non-compliant devices) */

	अचिन्हित पूर्णांक running: 1;	/* running status */

	अचिन्हित पूर्णांक hwptr_करोne;	/* processed byte position in the buffer */
	अचिन्हित पूर्णांक transfer_करोne;		/* processed frames since last period update */
	अचिन्हित पूर्णांक frame_limit;	/* limits number of packets in URB */

	/* data and sync endpoपूर्णांकs क्रम this stream */
	अचिन्हित पूर्णांक ep_num;		/* the endpoपूर्णांक number */
	काष्ठा snd_usb_endpoपूर्णांक *data_endpoपूर्णांक;
	काष्ठा snd_usb_endpoपूर्णांक *sync_endpoपूर्णांक;
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक speed;		/* USB_SPEED_XXX */

	u64 क्रमmats;			/* क्रमmat biपंचांगasks (all or'ed) */
	अचिन्हित पूर्णांक num_क्रमmats;		/* number of supported audio क्रमmats (list) */
	काष्ठा list_head fmt_list;	/* क्रमmat list */
	spinlock_t lock;

	पूर्णांक last_frame_number;          /* stored frame number */
	पूर्णांक last_delay;                 /* stored delay */

	काष्ठा अणु
		पूर्णांक marker;
		पूर्णांक channel;
		पूर्णांक byte_idx;
	पूर्ण dsd_करोp;

	bool trigger_tstamp_pending_update; /* trigger बारtamp being updated from initial estimate */
	काष्ठा media_ctl *media_ctl;
पूर्ण;

काष्ठा snd_usb_stream अणु
	काष्ठा snd_usb_audio *chip;
	काष्ठा snd_pcm *pcm;
	पूर्णांक pcm_index;
	अचिन्हित पूर्णांक fmt_type;		/* USB audio क्रमmat type (1-3) */
	काष्ठा snd_usb_substream substream[2];
	काष्ठा list_head list;
पूर्ण;

#पूर्ण_अगर /* __USBAUDIO_CARD_H */
