<शैली गुरु>
/* SPDX-License-Identअगरier: BSD-3-Clause */
/*
 * Copyright (C) 2021 OpenSynergy GmbH
 */
#अगर_अघोषित VIRTIO_SND_IF_H
#घोषणा VIRTIO_SND_IF_H

#समावेश <linux/virtio_types.h>

/*******************************************************************************
 * CONFIGURATION SPACE
 */
काष्ठा virtio_snd_config अणु
	/* # of available physical jacks */
	__le32 jacks;
	/* # of available PCM streams */
	__le32 streams;
	/* # of available channel maps */
	__le32 chmaps;
पूर्ण;

क्रमागत अणु
	/* device virtqueue indexes */
	VIRTIO_SND_VQ_CONTROL = 0,
	VIRTIO_SND_VQ_EVENT,
	VIRTIO_SND_VQ_TX,
	VIRTIO_SND_VQ_RX,
	/* # of device virtqueues */
	VIRTIO_SND_VQ_MAX
पूर्ण;

/*******************************************************************************
 * COMMON DEFINITIONS
 */

/* supported dataflow directions */
क्रमागत अणु
	VIRTIO_SND_D_OUTPUT = 0,
	VIRTIO_SND_D_INPUT
पूर्ण;

क्रमागत अणु
	/* jack control request types */
	VIRTIO_SND_R_JACK_INFO = 1,
	VIRTIO_SND_R_JACK_REMAP,

	/* PCM control request types */
	VIRTIO_SND_R_PCM_INFO = 0x0100,
	VIRTIO_SND_R_PCM_SET_PARAMS,
	VIRTIO_SND_R_PCM_PREPARE,
	VIRTIO_SND_R_PCM_RELEASE,
	VIRTIO_SND_R_PCM_START,
	VIRTIO_SND_R_PCM_STOP,

	/* channel map control request types */
	VIRTIO_SND_R_CHMAP_INFO = 0x0200,

	/* jack event types */
	VIRTIO_SND_EVT_JACK_CONNECTED = 0x1000,
	VIRTIO_SND_EVT_JACK_DISCONNECTED,

	/* PCM event types */
	VIRTIO_SND_EVT_PCM_PERIOD_ELAPSED = 0x1100,
	VIRTIO_SND_EVT_PCM_XRUN,

	/* common status codes */
	VIRTIO_SND_S_OK = 0x8000,
	VIRTIO_SND_S_BAD_MSG,
	VIRTIO_SND_S_NOT_SUPP,
	VIRTIO_SND_S_IO_ERR
पूर्ण;

/* common header */
काष्ठा virtio_snd_hdr अणु
	__le32 code;
पूर्ण;

/* event notअगरication */
काष्ठा virtio_snd_event अणु
	/* VIRTIO_SND_EVT_XXX */
	काष्ठा virtio_snd_hdr hdr;
	/* optional event data */
	__le32 data;
पूर्ण;

/* common control request to query an item inक्रमmation */
काष्ठा virtio_snd_query_info अणु
	/* VIRTIO_SND_R_XXX_INFO */
	काष्ठा virtio_snd_hdr hdr;
	/* item start identअगरier */
	__le32 start_id;
	/* item count to query */
	__le32 count;
	/* item inक्रमmation size in bytes */
	__le32 size;
पूर्ण;

/* common item inक्रमmation header */
काष्ठा virtio_snd_info अणु
	/* function group node id (High Definition Audio Specअगरication 7.1.2) */
	__le32 hda_fn_nid;
पूर्ण;

/*******************************************************************************
 * JACK CONTROL MESSAGES
 */
काष्ठा virtio_snd_jack_hdr अणु
	/* VIRTIO_SND_R_JACK_XXX */
	काष्ठा virtio_snd_hdr hdr;
	/* 0 ... virtio_snd_config::jacks - 1 */
	__le32 jack_id;
पूर्ण;

/* supported jack features */
क्रमागत अणु
	VIRTIO_SND_JACK_F_REMAP = 0
पूर्ण;

काष्ठा virtio_snd_jack_info अणु
	/* common header */
	काष्ठा virtio_snd_info hdr;
	/* supported feature bit map (1 << VIRTIO_SND_JACK_F_XXX) */
	__le32 features;
	/* pin configuration (High Definition Audio Specअगरication 7.3.3.31) */
	__le32 hda_reg_defconf;
	/* pin capabilities (High Definition Audio Specअगरication 7.3.4.9) */
	__le32 hda_reg_caps;
	/* current jack connection status (0: disconnected, 1: connected) */
	__u8 connected;

	__u8 padding[7];
पूर्ण;

/* jack remapping control request */
काष्ठा virtio_snd_jack_remap अणु
	/* .code = VIRTIO_SND_R_JACK_REMAP */
	काष्ठा virtio_snd_jack_hdr hdr;
	/* selected association number */
	__le32 association;
	/* selected sequence number */
	__le32 sequence;
पूर्ण;

/*******************************************************************************
 * PCM CONTROL MESSAGES
 */
काष्ठा virtio_snd_pcm_hdr अणु
	/* VIRTIO_SND_R_PCM_XXX */
	काष्ठा virtio_snd_hdr hdr;
	/* 0 ... virtio_snd_config::streams - 1 */
	__le32 stream_id;
पूर्ण;

/* supported PCM stream features */
क्रमागत अणु
	VIRTIO_SND_PCM_F_SHMEM_HOST = 0,
	VIRTIO_SND_PCM_F_SHMEM_GUEST,
	VIRTIO_SND_PCM_F_MSG_POLLING,
	VIRTIO_SND_PCM_F_EVT_SHMEM_PERIODS,
	VIRTIO_SND_PCM_F_EVT_XRUNS
पूर्ण;

/* supported PCM sample क्रमmats */
क्रमागत अणु
	/* analog क्रमmats (width / physical width) */
	VIRTIO_SND_PCM_FMT_IMA_ADPCM = 0,	/*  4 /  4 bits */
	VIRTIO_SND_PCM_FMT_MU_LAW,		/*  8 /  8 bits */
	VIRTIO_SND_PCM_FMT_A_LAW,		/*  8 /  8 bits */
	VIRTIO_SND_PCM_FMT_S8,			/*  8 /  8 bits */
	VIRTIO_SND_PCM_FMT_U8,			/*  8 /  8 bits */
	VIRTIO_SND_PCM_FMT_S16,			/* 16 / 16 bits */
	VIRTIO_SND_PCM_FMT_U16,			/* 16 / 16 bits */
	VIRTIO_SND_PCM_FMT_S18_3,		/* 18 / 24 bits */
	VIRTIO_SND_PCM_FMT_U18_3,		/* 18 / 24 bits */
	VIRTIO_SND_PCM_FMT_S20_3,		/* 20 / 24 bits */
	VIRTIO_SND_PCM_FMT_U20_3,		/* 20 / 24 bits */
	VIRTIO_SND_PCM_FMT_S24_3,		/* 24 / 24 bits */
	VIRTIO_SND_PCM_FMT_U24_3,		/* 24 / 24 bits */
	VIRTIO_SND_PCM_FMT_S20,			/* 20 / 32 bits */
	VIRTIO_SND_PCM_FMT_U20,			/* 20 / 32 bits */
	VIRTIO_SND_PCM_FMT_S24,			/* 24 / 32 bits */
	VIRTIO_SND_PCM_FMT_U24,			/* 24 / 32 bits */
	VIRTIO_SND_PCM_FMT_S32,			/* 32 / 32 bits */
	VIRTIO_SND_PCM_FMT_U32,			/* 32 / 32 bits */
	VIRTIO_SND_PCM_FMT_FLOAT,		/* 32 / 32 bits */
	VIRTIO_SND_PCM_FMT_FLOAT64,		/* 64 / 64 bits */
	/* digital क्रमmats (width / physical width) */
	VIRTIO_SND_PCM_FMT_DSD_U8,		/*  8 /  8 bits */
	VIRTIO_SND_PCM_FMT_DSD_U16,		/* 16 / 16 bits */
	VIRTIO_SND_PCM_FMT_DSD_U32,		/* 32 / 32 bits */
	VIRTIO_SND_PCM_FMT_IEC958_SUBFRAME	/* 32 / 32 bits */
पूर्ण;

/* supported PCM frame rates */
क्रमागत अणु
	VIRTIO_SND_PCM_RATE_5512 = 0,
	VIRTIO_SND_PCM_RATE_8000,
	VIRTIO_SND_PCM_RATE_11025,
	VIRTIO_SND_PCM_RATE_16000,
	VIRTIO_SND_PCM_RATE_22050,
	VIRTIO_SND_PCM_RATE_32000,
	VIRTIO_SND_PCM_RATE_44100,
	VIRTIO_SND_PCM_RATE_48000,
	VIRTIO_SND_PCM_RATE_64000,
	VIRTIO_SND_PCM_RATE_88200,
	VIRTIO_SND_PCM_RATE_96000,
	VIRTIO_SND_PCM_RATE_176400,
	VIRTIO_SND_PCM_RATE_192000,
	VIRTIO_SND_PCM_RATE_384000
पूर्ण;

काष्ठा virtio_snd_pcm_info अणु
	/* common header */
	काष्ठा virtio_snd_info hdr;
	/* supported feature bit map (1 << VIRTIO_SND_PCM_F_XXX) */
	__le32 features;
	/* supported sample क्रमmat bit map (1 << VIRTIO_SND_PCM_FMT_XXX) */
	__le64 क्रमmats;
	/* supported frame rate bit map (1 << VIRTIO_SND_PCM_RATE_XXX) */
	__le64 rates;
	/* dataflow direction (VIRTIO_SND_D_XXX) */
	__u8 direction;
	/* minimum # of supported channels */
	__u8 channels_min;
	/* maximum # of supported channels */
	__u8 channels_max;

	__u8 padding[5];
पूर्ण;

/* set PCM stream क्रमmat */
काष्ठा virtio_snd_pcm_set_params अणु
	/* .code = VIRTIO_SND_R_PCM_SET_PARAMS */
	काष्ठा virtio_snd_pcm_hdr hdr;
	/* size of the hardware buffer */
	__le32 buffer_bytes;
	/* size of the hardware period */
	__le32 period_bytes;
	/* selected feature bit map (1 << VIRTIO_SND_PCM_F_XXX) */
	__le32 features;
	/* selected # of channels */
	__u8 channels;
	/* selected sample क्रमmat (VIRTIO_SND_PCM_FMT_XXX) */
	__u8 क्रमmat;
	/* selected frame rate (VIRTIO_SND_PCM_RATE_XXX) */
	__u8 rate;

	__u8 padding;
पूर्ण;

/*******************************************************************************
 * PCM I/O MESSAGES
 */

/* I/O request header */
काष्ठा virtio_snd_pcm_xfer अणु
	/* 0 ... virtio_snd_config::streams - 1 */
	__le32 stream_id;
पूर्ण;

/* I/O request status */
काष्ठा virtio_snd_pcm_status अणु
	/* VIRTIO_SND_S_XXX */
	__le32 status;
	/* current device latency */
	__le32 latency_bytes;
पूर्ण;

/*******************************************************************************
 * CHANNEL MAP CONTROL MESSAGES
 */
काष्ठा virtio_snd_chmap_hdr अणु
	/* VIRTIO_SND_R_CHMAP_XXX */
	काष्ठा virtio_snd_hdr hdr;
	/* 0 ... virtio_snd_config::chmaps - 1 */
	__le32 chmap_id;
पूर्ण;

/* standard channel position definition */
क्रमागत अणु
	VIRTIO_SND_CHMAP_NONE = 0,	/* undefined */
	VIRTIO_SND_CHMAP_NA,		/* silent */
	VIRTIO_SND_CHMAP_MONO,		/* mono stream */
	VIRTIO_SND_CHMAP_FL,		/* front left */
	VIRTIO_SND_CHMAP_FR,		/* front right */
	VIRTIO_SND_CHMAP_RL,		/* rear left */
	VIRTIO_SND_CHMAP_RR,		/* rear right */
	VIRTIO_SND_CHMAP_FC,		/* front center */
	VIRTIO_SND_CHMAP_LFE,		/* low frequency (LFE) */
	VIRTIO_SND_CHMAP_SL,		/* side left */
	VIRTIO_SND_CHMAP_SR,		/* side right */
	VIRTIO_SND_CHMAP_RC,		/* rear center */
	VIRTIO_SND_CHMAP_FLC,		/* front left center */
	VIRTIO_SND_CHMAP_FRC,		/* front right center */
	VIRTIO_SND_CHMAP_RLC,		/* rear left center */
	VIRTIO_SND_CHMAP_RRC,		/* rear right center */
	VIRTIO_SND_CHMAP_FLW,		/* front left wide */
	VIRTIO_SND_CHMAP_FRW,		/* front right wide */
	VIRTIO_SND_CHMAP_FLH,		/* front left high */
	VIRTIO_SND_CHMAP_FCH,		/* front center high */
	VIRTIO_SND_CHMAP_FRH,		/* front right high */
	VIRTIO_SND_CHMAP_TC,		/* top center */
	VIRTIO_SND_CHMAP_TFL,		/* top front left */
	VIRTIO_SND_CHMAP_TFR,		/* top front right */
	VIRTIO_SND_CHMAP_TFC,		/* top front center */
	VIRTIO_SND_CHMAP_TRL,		/* top rear left */
	VIRTIO_SND_CHMAP_TRR,		/* top rear right */
	VIRTIO_SND_CHMAP_TRC,		/* top rear center */
	VIRTIO_SND_CHMAP_TFLC,		/* top front left center */
	VIRTIO_SND_CHMAP_TFRC,		/* top front right center */
	VIRTIO_SND_CHMAP_TSL,		/* top side left */
	VIRTIO_SND_CHMAP_TSR,		/* top side right */
	VIRTIO_SND_CHMAP_LLFE,		/* left LFE */
	VIRTIO_SND_CHMAP_RLFE,		/* right LFE */
	VIRTIO_SND_CHMAP_BC,		/* bottom center */
	VIRTIO_SND_CHMAP_BLC,		/* bottom left center */
	VIRTIO_SND_CHMAP_BRC		/* bottom right center */
पूर्ण;

/* maximum possible number of channels */
#घोषणा VIRTIO_SND_CHMAP_MAX_SIZE	18

काष्ठा virtio_snd_chmap_info अणु
	/* common header */
	काष्ठा virtio_snd_info hdr;
	/* dataflow direction (VIRTIO_SND_D_XXX) */
	__u8 direction;
	/* # of valid channel position values */
	__u8 channels;
	/* channel position values (VIRTIO_SND_CHMAP_XXX) */
	__u8 positions[VIRTIO_SND_CHMAP_MAX_SIZE];
पूर्ण;

#पूर्ण_अगर /* VIRTIO_SND_IF_H */
