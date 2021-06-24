<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/*
 * uapi/sound/asoc.h -- ALSA SoC Firmware Controls and DAPM
 *
 * Copyright (C) 2012 Texas Instruments Inc.
 * Copyright (C) 2015 Intel Corporation.
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * Simple file API to load FW that includes mixers, coefficients, DAPM graphs,
 * algorithms, equalisers, DAIs, widमाला_लो etc.
*/

#अगर_अघोषित __LINUX_UAPI_SND_ASOC_H
#घोषणा __LINUX_UAPI_SND_ASOC_H

#समावेश <linux/types.h>
#समावेश <sound/asound.h>

/*
 * Maximum number of channels topology kcontrol can represent.
 */
#घोषणा SND_SOC_TPLG_MAX_CHAN		8

/*
 * Maximum number of PCM क्रमmats capability
 */
#घोषणा SND_SOC_TPLG_MAX_FORMATS	16

/*
 * Maximum number of PCM stream configs
 */
#घोषणा SND_SOC_TPLG_STREAM_CONFIG_MAX  8

/*
 * Maximum number of physical link's hardware configs
 */
#घोषणा SND_SOC_TPLG_HW_CONFIG_MAX	8

/* inभागidual kcontrol info types - can be mixed with other types */
#घोषणा SND_SOC_TPLG_CTL_VOLSW		1
#घोषणा SND_SOC_TPLG_CTL_VOLSW_SX	2
#घोषणा SND_SOC_TPLG_CTL_VOLSW_XR_SX	3
#घोषणा SND_SOC_TPLG_CTL_ENUM		4
#घोषणा SND_SOC_TPLG_CTL_BYTES		5
#घोषणा SND_SOC_TPLG_CTL_ENUM_VALUE	6
#घोषणा SND_SOC_TPLG_CTL_RANGE		7
#घोषणा SND_SOC_TPLG_CTL_STROBE		8


/* inभागidual widget kcontrol info types - can be mixed with other types */
#घोषणा SND_SOC_TPLG_DAPM_CTL_VOLSW		64
#घोषणा SND_SOC_TPLG_DAPM_CTL_ENUM_DOUBLE	65
#घोषणा SND_SOC_TPLG_DAPM_CTL_ENUM_VIRT		66
#घोषणा SND_SOC_TPLG_DAPM_CTL_ENUM_VALUE	67
#घोषणा SND_SOC_TPLG_DAPM_CTL_PIN		68

/* DAPM widget types - add new items to the end */
#घोषणा SND_SOC_TPLG_DAPM_INPUT		0
#घोषणा SND_SOC_TPLG_DAPM_OUTPUT	1
#घोषणा SND_SOC_TPLG_DAPM_MUX		2
#घोषणा SND_SOC_TPLG_DAPM_MIXER		3
#घोषणा SND_SOC_TPLG_DAPM_PGA		4
#घोषणा SND_SOC_TPLG_DAPM_OUT_DRV	5
#घोषणा SND_SOC_TPLG_DAPM_ADC		6
#घोषणा SND_SOC_TPLG_DAPM_DAC		7
#घोषणा SND_SOC_TPLG_DAPM_SWITCH	8
#घोषणा SND_SOC_TPLG_DAPM_PRE		9
#घोषणा SND_SOC_TPLG_DAPM_POST		10
#घोषणा SND_SOC_TPLG_DAPM_AIF_IN	11
#घोषणा SND_SOC_TPLG_DAPM_AIF_OUT	12
#घोषणा SND_SOC_TPLG_DAPM_DAI_IN	13
#घोषणा SND_SOC_TPLG_DAPM_DAI_OUT	14
#घोषणा SND_SOC_TPLG_DAPM_DAI_LINK	15
#घोषणा SND_SOC_TPLG_DAPM_BUFFER	16
#घोषणा SND_SOC_TPLG_DAPM_SCHEDULER	17
#घोषणा SND_SOC_TPLG_DAPM_EFFECT	18
#घोषणा SND_SOC_TPLG_DAPM_SIGGEN	19
#घोषणा SND_SOC_TPLG_DAPM_SRC		20
#घोषणा SND_SOC_TPLG_DAPM_ASRC		21
#घोषणा SND_SOC_TPLG_DAPM_ENCODER	22
#घोषणा SND_SOC_TPLG_DAPM_DECODER	23
#घोषणा SND_SOC_TPLG_DAPM_LAST		SND_SOC_TPLG_DAPM_DECODER

/* Header magic number and string sizes */
#घोषणा SND_SOC_TPLG_MAGIC		0x41536F43 /* ASoC */

/* string sizes */
#घोषणा SND_SOC_TPLG_NUM_TEXTS		16

/* ABI version */
#घोषणा SND_SOC_TPLG_ABI_VERSION	0x5	/* current version */
#घोषणा SND_SOC_TPLG_ABI_VERSION_MIN	0x4	/* oldest version supported */

/* Max size of TLV data */
#घोषणा SND_SOC_TPLG_TLV_SIZE		32

/*
 * File and Block header data types.
 * Add new generic and venकरोr types to end of list.
 * Generic types are handled by the core whilst venकरोrs types are passed
 * to the component drivers क्रम handling.
 */
#घोषणा SND_SOC_TPLG_TYPE_MIXER		1
#घोषणा SND_SOC_TPLG_TYPE_BYTES		2
#घोषणा SND_SOC_TPLG_TYPE_ENUM		3
#घोषणा SND_SOC_TPLG_TYPE_DAPM_GRAPH	4
#घोषणा SND_SOC_TPLG_TYPE_DAPM_WIDGET	5
#घोषणा SND_SOC_TPLG_TYPE_DAI_LINK	6
#घोषणा SND_SOC_TPLG_TYPE_PCM		7
#घोषणा SND_SOC_TPLG_TYPE_MANIFEST	8
#घोषणा SND_SOC_TPLG_TYPE_CODEC_LINK	9
#घोषणा SND_SOC_TPLG_TYPE_BACKEND_LINK	10
#घोषणा SND_SOC_TPLG_TYPE_PDATA		11
#घोषणा SND_SOC_TPLG_TYPE_DAI		12
#घोषणा SND_SOC_TPLG_TYPE_MAX		SND_SOC_TPLG_TYPE_DAI

/* venकरोr block IDs - please add new venकरोr types to end */
#घोषणा SND_SOC_TPLG_TYPE_VENDOR_FW	1000
#घोषणा SND_SOC_TPLG_TYPE_VENDOR_CONFIG	1001
#घोषणा SND_SOC_TPLG_TYPE_VENDOR_COEFF	1002
#घोषणा SND_SOC_TPLG_TYPEVENDOR_CODEC	1003

#घोषणा SND_SOC_TPLG_STREAM_PLAYBACK	0
#घोषणा SND_SOC_TPLG_STREAM_CAPTURE	1

/* venकरोr tuple types */
#घोषणा SND_SOC_TPLG_TUPLE_TYPE_UUID	0
#घोषणा SND_SOC_TPLG_TUPLE_TYPE_STRING	1
#घोषणा SND_SOC_TPLG_TUPLE_TYPE_BOOL	2
#घोषणा SND_SOC_TPLG_TUPLE_TYPE_BYTE	3
#घोषणा SND_SOC_TPLG_TUPLE_TYPE_WORD	4
#घोषणा SND_SOC_TPLG_TUPLE_TYPE_SHORT	5

/* DAI flags */
#घोषणा SND_SOC_TPLG_DAI_FLGBIT_SYMMETRIC_RATES         (1 << 0)
#घोषणा SND_SOC_TPLG_DAI_FLGBIT_SYMMETRIC_CHANNELS      (1 << 1)
#घोषणा SND_SOC_TPLG_DAI_FLGBIT_SYMMETRIC_SAMPLEBITS    (1 << 2)

/* DAI घड़ी gating */
#घोषणा SND_SOC_TPLG_DAI_CLK_GATE_UNDEFINED	0
#घोषणा SND_SOC_TPLG_DAI_CLK_GATE_GATED	1
#घोषणा SND_SOC_TPLG_DAI_CLK_GATE_CONT		2

/* DAI mclk_direction */
#घोषणा SND_SOC_TPLG_MCLK_CO            0 /* क्रम codec, mclk is output */
#घोषणा SND_SOC_TPLG_MCLK_CI            1 /* क्रम codec, mclk is input */

/* DAI physical PCM data क्रमmats.
 * Add new क्रमmats to the end of the list.
 */
#घोषणा SND_SOC_DAI_FORMAT_I2S          1 /* I2S mode */
#घोषणा SND_SOC_DAI_FORMAT_RIGHT_J      2 /* Right Justअगरied mode */
#घोषणा SND_SOC_DAI_FORMAT_LEFT_J       3 /* Left Justअगरied mode */
#घोषणा SND_SOC_DAI_FORMAT_DSP_A        4 /* L data MSB after FRM LRC */
#घोषणा SND_SOC_DAI_FORMAT_DSP_B        5 /* L data MSB during FRM LRC */
#घोषणा SND_SOC_DAI_FORMAT_AC97         6 /* AC97 */
#घोषणा SND_SOC_DAI_FORMAT_PDM          7 /* Pulse density modulation */

/* left and right justअगरied also known as MSB and LSB respectively */
#घोषणा SND_SOC_DAI_FORMAT_MSB          SND_SOC_DAI_FORMAT_LEFT_J
#घोषणा SND_SOC_DAI_FORMAT_LSB          SND_SOC_DAI_FORMAT_RIGHT_J

/* DAI link flags */
#घोषणा SND_SOC_TPLG_LNK_FLGBIT_SYMMETRIC_RATES         (1 << 0)
#घोषणा SND_SOC_TPLG_LNK_FLGBIT_SYMMETRIC_CHANNELS      (1 << 1)
#घोषणा SND_SOC_TPLG_LNK_FLGBIT_SYMMETRIC_SAMPLEBITS    (1 << 2)
#घोषणा SND_SOC_TPLG_LNK_FLGBIT_VOICE_WAKEUP            (1 << 3)

/* DAI topology BCLK parameter
 * For the backwards capability, by शेष codec is bclk provider
 */
#घोषणा SND_SOC_TPLG_BCLK_CP         0 /* codec is bclk provider */
#घोषणा SND_SOC_TPLG_BCLK_CC         1 /* codec is bclk consumer */
/* keep previous definitions क्रम compatibility */
#घोषणा SND_SOC_TPLG_BCLK_CM         SND_SOC_TPLG_BCLK_CP
#घोषणा SND_SOC_TPLG_BCLK_CS         SND_SOC_TPLG_BCLK_CC

/* DAI topology FSYNC parameter
 * For the backwards capability, by शेष codec is fsync provider
 */
#घोषणा SND_SOC_TPLG_FSYNC_CP         0 /* codec is fsync provider */
#घोषणा SND_SOC_TPLG_FSYNC_CC         1 /* codec is fsync consumer */
/* keep previous definitions क्रम compatibility */
#घोषणा SND_SOC_TPLG_FSYNC_CM         SND_SOC_TPLG_FSYNC_CP
#घोषणा SND_SOC_TPLG_FSYNC_CS         SND_SOC_TPLG_FSYNC_CC

/*
 * Block Header.
 * This header precedes all object and object arrays below.
 */
काष्ठा snd_soc_tplg_hdr अणु
	__le32 magic;		/* magic number */
	__le32 abi;		/* ABI version */
	__le32 version;		/* optional venकरोr specअगरic version details */
	__le32 type;		/* SND_SOC_TPLG_TYPE_ */
	__le32 size;		/* size of this काष्ठाure */
	__le32 venकरोr_type;	/* optional venकरोr specअगरic type info */
	__le32 payload_size;	/* data bytes, excluding this header */
	__le32 index;		/* identअगरier क्रम block */
	__le32 count;		/* number of elements in block */
पूर्ण __attribute__((packed));

/* venकरोr tuple क्रम uuid */
काष्ठा snd_soc_tplg_venकरोr_uuid_elem अणु
	__le32 token;
	अक्षर uuid[16];
पूर्ण __attribute__((packed));

/* venकरोr tuple क्रम a bool/byte/लघु/word value */
काष्ठा snd_soc_tplg_venकरोr_value_elem अणु
	__le32 token;
	__le32 value;
पूर्ण __attribute__((packed));

/* venकरोr tuple क्रम string */
काष्ठा snd_soc_tplg_venकरोr_string_elem अणु
	__le32 token;
	अक्षर string[SNDRV_CTL_ELEM_ID_NAME_MAXLEN];
पूर्ण __attribute__((packed));

काष्ठा snd_soc_tplg_venकरोr_array अणु
	__le32 size;	/* size in bytes of the array, including all elements */
	__le32 type;	/* SND_SOC_TPLG_TUPLE_TYPE_ */
	__le32 num_elems;	/* number of elements in array */
	जोड़ अणु
		काष्ठा snd_soc_tplg_venकरोr_uuid_elem uuid[0];
		काष्ठा snd_soc_tplg_venकरोr_value_elem value[0];
		काष्ठा snd_soc_tplg_venकरोr_string_elem string[0];
	पूर्ण;
पूर्ण __attribute__((packed));

/*
 * Private data.
 * All topology objects may have निजी data that can be used by the driver or
 * firmware. Core will ignore this data.
 */
काष्ठा snd_soc_tplg_निजी अणु
	__le32 size;	/* in bytes of निजी data */
	जोड़ अणु
		अक्षर data[0];
		काष्ठा snd_soc_tplg_venकरोr_array array[0];
	पूर्ण;
पूर्ण __attribute__((packed));

/*
 * Kcontrol TLV data.
 */
काष्ठा snd_soc_tplg_tlv_dbscale अणु
	__le32 min;
	__le32 step;
	__le32 mute;
पूर्ण __attribute__((packed));

काष्ठा snd_soc_tplg_ctl_tlv अणु
	__le32 size;	/* in bytes of this काष्ठाure */
	__le32 type;	/* SNDRV_CTL_TLVT_*, type of TLV */
	जोड़ अणु
		__le32 data[SND_SOC_TPLG_TLV_SIZE];
		काष्ठा snd_soc_tplg_tlv_dbscale scale;
	पूर्ण;
पूर्ण __attribute__((packed));

/*
 * Kcontrol channel data
 */
काष्ठा snd_soc_tplg_channel अणु
	__le32 size;	/* in bytes of this काष्ठाure */
	__le32 reg;
	__le32 shअगरt;
	__le32 id;	/* ID maps to Left, Right, LFE etc */
पूर्ण __attribute__((packed));

/*
 * Genericl Operations IDs, क्रम binding Kcontrol or Bytes ext ops
 * Kcontrol ops need get/put/info.
 * Bytes ext ops need get/put.
 */
काष्ठा snd_soc_tplg_io_ops अणु
	__le32 get;
	__le32 put;
	__le32 info;
पूर्ण __attribute__((packed));

/*
 * kcontrol header
 */
काष्ठा snd_soc_tplg_ctl_hdr अणु
	__le32 size;	/* in bytes of this काष्ठाure */
	__le32 type;
	अक्षर name[SNDRV_CTL_ELEM_ID_NAME_MAXLEN];
	__le32 access;
	काष्ठा snd_soc_tplg_io_ops ops;
	काष्ठा snd_soc_tplg_ctl_tlv tlv;
पूर्ण __attribute__((packed));

/*
 * Stream Capabilities
 */
काष्ठा snd_soc_tplg_stream_caps अणु
	__le32 size;		/* in bytes of this काष्ठाure */
	अक्षर name[SNDRV_CTL_ELEM_ID_NAME_MAXLEN];
	__le64 क्रमmats;	/* supported क्रमmats SNDRV_PCM_FMTBIT_* */
	__le32 rates;		/* supported rates SNDRV_PCM_RATE_* */
	__le32 rate_min;	/* min rate */
	__le32 rate_max;	/* max rate */
	__le32 channels_min;	/* min channels */
	__le32 channels_max;	/* max channels */
	__le32 periods_min;	/* min number of periods */
	__le32 periods_max;	/* max number of periods */
	__le32 period_size_min;	/* min period size bytes */
	__le32 period_size_max;	/* max period size bytes */
	__le32 buffer_size_min;	/* min buffer size bytes */
	__le32 buffer_size_max;	/* max buffer size bytes */
	__le32 sig_bits;        /* number of bits of content */
पूर्ण __attribute__((packed));

/*
 * FE or BE Stream configuration supported by SW/FW
 */
काष्ठा snd_soc_tplg_stream अणु
	__le32 size;		/* in bytes of this काष्ठाure */
	अक्षर name[SNDRV_CTL_ELEM_ID_NAME_MAXLEN]; /* Name of the stream */
	__le64 क्रमmat;		/* SNDRV_PCM_FMTBIT_* */
	__le32 rate;		/* SNDRV_PCM_RATE_* */
	__le32 period_bytes;	/* size of period in bytes */
	__le32 buffer_bytes;	/* size of buffer in bytes */
	__le32 channels;	/* channels */
पूर्ण __attribute__((packed));


/*
 * Describes a physical link's runसमय supported hardware config,
 * i.e. hardware audio क्रमmats.
 */
काष्ठा snd_soc_tplg_hw_config अणु
	__le32 size;            /* in bytes of this काष्ठाure */
	__le32 id;		/* unique ID - - used to match */
	__le32 fmt;		/* SND_SOC_DAI_FORMAT_ क्रमmat value */
	__u8 घड़ी_gated;	/* SND_SOC_TPLG_DAI_CLK_GATE_ value */
	__u8 invert_bclk;	/* 1 क्रम inverted BCLK, 0 क्रम normal */
	__u8 invert_fsync;	/* 1 क्रम inverted frame घड़ी, 0 क्रम normal */
	__u8 bclk_provider;	/* SND_SOC_TPLG_BCLK_ value */
	__u8 fsync_provider;	/* SND_SOC_TPLG_FSYNC_ value */
	__u8 mclk_direction;    /* SND_SOC_TPLG_MCLK_ value */
	__le16 reserved;	/* क्रम 32bit alignment */
	__le32 mclk_rate;	/* MCLK or SYSCLK freqency in Hz */
	__le32 bclk_rate;	/* BCLK freqency in Hz */
	__le32 fsync_rate;	/* frame घड़ी in Hz */
	__le32 tdm_slots;	/* number of TDM slots in use */
	__le32 tdm_slot_width;	/* width in bits क्रम each slot */
	__le32 tx_slots;	/* bit mask क्रम active Tx slots */
	__le32 rx_slots;	/* bit mask क्रम active Rx slots */
	__le32 tx_channels;	/* number of Tx channels */
	__le32 tx_chanmap[SND_SOC_TPLG_MAX_CHAN]; /* array of slot number */
	__le32 rx_channels;	/* number of Rx channels */
	__le32 rx_chanmap[SND_SOC_TPLG_MAX_CHAN]; /* array of slot number */
पूर्ण __attribute__((packed));

/*
 * Manअगरest. List totals क्रम each payload type. Not used in parsing, but will
 * be passed to the component driver beक्रमe any other objects in order क्रम any
 * global component resource allocations.
 *
 * File block representation क्रम manअगरest :-
 * +-----------------------------------+----+
 * | काष्ठा snd_soc_tplg_hdr           |  1 |
 * +-----------------------------------+----+
 * | काष्ठा snd_soc_tplg_manअगरest      |  1 |
 * +-----------------------------------+----+
 */
काष्ठा snd_soc_tplg_manअगरest अणु
	__le32 size;		/* in bytes of this काष्ठाure */
	__le32 control_elems;	/* number of control elements */
	__le32 widget_elems;	/* number of widget elements */
	__le32 graph_elems;	/* number of graph elements */
	__le32 pcm_elems;	/* number of PCM elements */
	__le32 dai_link_elems;	/* number of DAI link elements */
	__le32 dai_elems;	/* number of physical DAI elements */
	__le32 reserved[20];	/* reserved क्रम new ABI element types */
	काष्ठा snd_soc_tplg_निजी priv;
पूर्ण __attribute__((packed));

/*
 * Mixer kcontrol.
 *
 * File block representation क्रम mixer kcontrol :-
 * +-----------------------------------+----+
 * | काष्ठा snd_soc_tplg_hdr           |  1 |
 * +-----------------------------------+----+
 * | काष्ठा snd_soc_tplg_mixer_control |  N |
 * +-----------------------------------+----+
 */
काष्ठा snd_soc_tplg_mixer_control अणु
	काष्ठा snd_soc_tplg_ctl_hdr hdr;
	__le32 size;	/* in bytes of this काष्ठाure */
	__le32 min;
	__le32 max;
	__le32 platक्रमm_max;
	__le32 invert;
	__le32 num_channels;
	काष्ठा snd_soc_tplg_channel channel[SND_SOC_TPLG_MAX_CHAN];
	काष्ठा snd_soc_tplg_निजी priv;
पूर्ण __attribute__((packed));

/*
 * Enumerated kcontrol
 *
 * File block representation क्रम क्रमागत kcontrol :-
 * +-----------------------------------+----+
 * | काष्ठा snd_soc_tplg_hdr           |  1 |
 * +-----------------------------------+----+
 * | काष्ठा snd_soc_tplg_क्रमागत_control  |  N |
 * +-----------------------------------+----+
 */
काष्ठा snd_soc_tplg_क्रमागत_control अणु
	काष्ठा snd_soc_tplg_ctl_hdr hdr;
	__le32 size;	/* in bytes of this काष्ठाure */
	__le32 num_channels;
	काष्ठा snd_soc_tplg_channel channel[SND_SOC_TPLG_MAX_CHAN];
	__le32 items;
	__le32 mask;
	__le32 count;
	अक्षर texts[SND_SOC_TPLG_NUM_TEXTS][SNDRV_CTL_ELEM_ID_NAME_MAXLEN];
	__le32 values[SND_SOC_TPLG_NUM_TEXTS * SNDRV_CTL_ELEM_ID_NAME_MAXLEN / 4];
	काष्ठा snd_soc_tplg_निजी priv;
पूर्ण __attribute__((packed));

/*
 * Bytes kcontrol
 *
 * File block representation क्रम bytes kcontrol :-
 * +-----------------------------------+----+
 * | काष्ठा snd_soc_tplg_hdr           |  1 |
 * +-----------------------------------+----+
 * | काष्ठा snd_soc_tplg_bytes_control |  N |
 * +-----------------------------------+----+
 */
काष्ठा snd_soc_tplg_bytes_control अणु
	काष्ठा snd_soc_tplg_ctl_hdr hdr;
	__le32 size;	/* in bytes of this काष्ठाure */
	__le32 max;
	__le32 mask;
	__le32 base;
	__le32 num_regs;
	काष्ठा snd_soc_tplg_io_ops ext_ops;
	काष्ठा snd_soc_tplg_निजी priv;
पूर्ण __attribute__((packed));

/*
 * DAPM Graph Element
 *
 * File block representation क्रम DAPM graph elements :-
 * +-------------------------------------+----+
 * | काष्ठा snd_soc_tplg_hdr             |  1 |
 * +-------------------------------------+----+
 * | काष्ठा snd_soc_tplg_dapm_graph_elem |  N |
 * +-------------------------------------+----+
 */
काष्ठा snd_soc_tplg_dapm_graph_elem अणु
	अक्षर sink[SNDRV_CTL_ELEM_ID_NAME_MAXLEN];
	अक्षर control[SNDRV_CTL_ELEM_ID_NAME_MAXLEN];
	अक्षर source[SNDRV_CTL_ELEM_ID_NAME_MAXLEN];
पूर्ण __attribute__((packed));

/*
 * DAPM Widget.
 *
 * File block representation क्रम DAPM widget :-
 * +-------------------------------------+-----+
 * | काष्ठा snd_soc_tplg_hdr             |  1  |
 * +-------------------------------------+-----+
 * | काष्ठा snd_soc_tplg_dapm_widget     |  N  |
 * +-------------------------------------+-----+
 * |   काष्ठा snd_soc_tplg_क्रमागत_control  | 0|1 |
 * |   काष्ठा snd_soc_tplg_mixer_control | 0|N |
 * +-------------------------------------+-----+
 *
 * Optional क्रमागत or mixer control can be appended to the end of each widget
 * in the block.
 */
काष्ठा snd_soc_tplg_dapm_widget अणु
	__le32 size;		/* in bytes of this काष्ठाure */
	__le32 id;		/* SND_SOC_DAPM_CTL */
	अक्षर name[SNDRV_CTL_ELEM_ID_NAME_MAXLEN];
	अक्षर sname[SNDRV_CTL_ELEM_ID_NAME_MAXLEN];

	__le32 reg;		/* negative reg = no direct dapm */
	__le32 shअगरt;		/* bits to shअगरt */
	__le32 mask;		/* non-shअगरted mask */
	__le32 subseq;		/* sort within widget type */
	__le32 invert;		/* invert the घातer bit */
	__le32 ignore_suspend;	/* kept enabled over suspend */
	__le16 event_flags;
	__le16 event_type;
	__le32 num_kcontrols;
	काष्ठा snd_soc_tplg_निजी priv;
	/*
	 * kcontrols that relate to this widget
	 * follow here after widget निजी data
	 */
पूर्ण __attribute__((packed));


/*
 * Describes SW/FW specअगरic features of PCM (FE DAI & DAI link).
 *
 * File block representation क्रम PCM :-
 * +-----------------------------------+-----+
 * | काष्ठा snd_soc_tplg_hdr           |  1  |
 * +-----------------------------------+-----+
 * | काष्ठा snd_soc_tplg_pcm           |  N  |
 * +-----------------------------------+-----+
 */
काष्ठा snd_soc_tplg_pcm अणु
	__le32 size;		/* in bytes of this काष्ठाure */
	अक्षर pcm_name[SNDRV_CTL_ELEM_ID_NAME_MAXLEN];
	अक्षर dai_name[SNDRV_CTL_ELEM_ID_NAME_MAXLEN];
	__le32 pcm_id;		/* unique ID - used to match with DAI link */
	__le32 dai_id;		/* unique ID - used to match */
	__le32 playback;	/* supports playback mode */
	__le32 capture;		/* supports capture mode */
	__le32 compress;	/* 1 = compressed; 0 = PCM */
	काष्ठा snd_soc_tplg_stream stream[SND_SOC_TPLG_STREAM_CONFIG_MAX]; /* क्रम DAI link */
	__le32 num_streams;	/* number of streams */
	काष्ठा snd_soc_tplg_stream_caps caps[2]; /* playback and capture क्रम DAI */
	__le32 flag_mask;       /* biपंचांगask of flags to configure */
	__le32 flags;           /* SND_SOC_TPLG_LNK_FLGBIT_* flag value */
	काष्ठा snd_soc_tplg_निजी priv;
पूर्ण __attribute__((packed));


/*
 * Describes the physical link runसमय supported configs or params
 *
 * File block representation क्रम physical link config :-
 * +-----------------------------------+-----+
 * | काष्ठा snd_soc_tplg_hdr           |  1  |
 * +-----------------------------------+-----+
 * | काष्ठा snd_soc_tplg_link_config   |  N  |
 * +-----------------------------------+-----+
 */
काष्ठा snd_soc_tplg_link_config अणु
	__le32 size;            /* in bytes of this काष्ठाure */
	__le32 id;              /* unique ID - used to match */
	अक्षर name[SNDRV_CTL_ELEM_ID_NAME_MAXLEN]; /* name - used to match */
	अक्षर stream_name[SNDRV_CTL_ELEM_ID_NAME_MAXLEN]; /* stream name - used to match */
	काष्ठा snd_soc_tplg_stream stream[SND_SOC_TPLG_STREAM_CONFIG_MAX]; /* supported configs playback and captrure */
	__le32 num_streams;     /* number of streams */
	काष्ठा snd_soc_tplg_hw_config hw_config[SND_SOC_TPLG_HW_CONFIG_MAX]; /* hw configs */
	__le32 num_hw_configs;         /* number of hw configs */
	__le32 शेष_hw_config_id;   /* शेष hw config ID क्रम init */
	__le32 flag_mask;       /* biपंचांगask of flags to configure */
	__le32 flags;           /* SND_SOC_TPLG_LNK_FLGBIT_* flag value */
	काष्ठा snd_soc_tplg_निजी priv;
पूर्ण __attribute__((packed));

/*
 * Describes SW/FW specअगरic features of physical DAI.
 * It can be used to configure backend DAIs क्रम DPCM.
 *
 * File block representation क्रम physical DAI :-
 * +-----------------------------------+-----+
 * | काष्ठा snd_soc_tplg_hdr           |  1  |
 * +-----------------------------------+-----+
 * | काष्ठा snd_soc_tplg_dai           |  N  |
 * +-----------------------------------+-----+
 */
काष्ठा snd_soc_tplg_dai अणु
	__le32 size;            /* in bytes of this काष्ठाure */
	अक्षर dai_name[SNDRV_CTL_ELEM_ID_NAME_MAXLEN]; /* name - used to match */
	__le32 dai_id;          /* unique ID - used to match */
	__le32 playback;        /* supports playback mode */
	__le32 capture;         /* supports capture mode */
	काष्ठा snd_soc_tplg_stream_caps caps[2]; /* playback and capture क्रम DAI */
	__le32 flag_mask;       /* biपंचांगask of flags to configure */
	__le32 flags;           /* SND_SOC_TPLG_DAI_FLGBIT_* */
	काष्ठा snd_soc_tplg_निजी priv;
पूर्ण __attribute__((packed));

/*
 * Old version of ABI काष्ठाs, supported क्रम backward compatibility.
 */

/* Manअगरest v4 */
काष्ठा snd_soc_tplg_manअगरest_v4 अणु
	__le32 size;		/* in bytes of this काष्ठाure */
	__le32 control_elems;	/* number of control elements */
	__le32 widget_elems;	/* number of widget elements */
	__le32 graph_elems;	/* number of graph elements */
	__le32 pcm_elems;	/* number of PCM elements */
	__le32 dai_link_elems;	/* number of DAI link elements */
	काष्ठा snd_soc_tplg_निजी priv;
पूर्ण __packed;

/* Stream Capabilities v4 */
काष्ठा snd_soc_tplg_stream_caps_v4 अणु
	__le32 size;		/* in bytes of this काष्ठाure */
	अक्षर name[SNDRV_CTL_ELEM_ID_NAME_MAXLEN];
	__le64 क्रमmats;	/* supported क्रमmats SNDRV_PCM_FMTBIT_* */
	__le32 rates;		/* supported rates SNDRV_PCM_RATE_* */
	__le32 rate_min;	/* min rate */
	__le32 rate_max;	/* max rate */
	__le32 channels_min;	/* min channels */
	__le32 channels_max;	/* max channels */
	__le32 periods_min;	/* min number of periods */
	__le32 periods_max;	/* max number of periods */
	__le32 period_size_min;	/* min period size bytes */
	__le32 period_size_max;	/* max period size bytes */
	__le32 buffer_size_min;	/* min buffer size bytes */
	__le32 buffer_size_max;	/* max buffer size bytes */
पूर्ण __packed;

/* PCM v4 */
काष्ठा snd_soc_tplg_pcm_v4 अणु
	__le32 size;		/* in bytes of this काष्ठाure */
	अक्षर pcm_name[SNDRV_CTL_ELEM_ID_NAME_MAXLEN];
	अक्षर dai_name[SNDRV_CTL_ELEM_ID_NAME_MAXLEN];
	__le32 pcm_id;		/* unique ID - used to match with DAI link */
	__le32 dai_id;		/* unique ID - used to match */
	__le32 playback;	/* supports playback mode */
	__le32 capture;		/* supports capture mode */
	__le32 compress;	/* 1 = compressed; 0 = PCM */
	काष्ठा snd_soc_tplg_stream stream[SND_SOC_TPLG_STREAM_CONFIG_MAX]; /* क्रम DAI link */
	__le32 num_streams;	/* number of streams */
	काष्ठा snd_soc_tplg_stream_caps_v4 caps[2]; /* playback and capture क्रम DAI */
पूर्ण __packed;

/* Physical link config v4 */
काष्ठा snd_soc_tplg_link_config_v4 अणु
	__le32 size;            /* in bytes of this काष्ठाure */
	__le32 id;              /* unique ID - used to match */
	काष्ठा snd_soc_tplg_stream stream[SND_SOC_TPLG_STREAM_CONFIG_MAX]; /* supported configs playback and captrure */
	__le32 num_streams;     /* number of streams */
पूर्ण __packed;

#पूर्ण_अगर
