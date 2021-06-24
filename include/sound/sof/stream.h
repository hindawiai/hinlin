<शैली गुरु>
/* SPDX-License-Identअगरier: (GPL-2.0-only OR BSD-3-Clause) */
/*
 * This file is provided under a dual BSD/GPLv2 license.  When using or
 * redistributing this file, you may करो so under either license.
 *
 * Copyright(c) 2018 Intel Corporation. All rights reserved.
 */

#अगर_अघोषित __INCLUDE_SOUND_SOF_STREAM_H__
#घोषणा __INCLUDE_SOUND_SOF_STREAM_H__

#समावेश <sound/sof/header.h>

/*
 * Stream configuration.
 */

#घोषणा SOF_IPC_MAX_CHANNELS			8

/* common sample rates क्रम use in masks */
#घोषणा SOF_RATE_8000		(1 <<  0) /**< 8000Hz  */
#घोषणा SOF_RATE_11025		(1 <<  1) /**< 11025Hz */
#घोषणा SOF_RATE_12000		(1 <<  2) /**< 12000Hz */
#घोषणा SOF_RATE_16000		(1 <<  3) /**< 16000Hz */
#घोषणा SOF_RATE_22050		(1 <<  4) /**< 22050Hz */
#घोषणा SOF_RATE_24000		(1 <<  5) /**< 24000Hz */
#घोषणा SOF_RATE_32000		(1 <<  6) /**< 32000Hz */
#घोषणा SOF_RATE_44100		(1 <<  7) /**< 44100Hz */
#घोषणा SOF_RATE_48000		(1 <<  8) /**< 48000Hz */
#घोषणा SOF_RATE_64000		(1 <<  9) /**< 64000Hz */
#घोषणा SOF_RATE_88200		(1 << 10) /**< 88200Hz */
#घोषणा SOF_RATE_96000		(1 << 11) /**< 96000Hz */
#घोषणा SOF_RATE_176400		(1 << 12) /**< 176400Hz */
#घोषणा SOF_RATE_192000		(1 << 13) /**< 192000Hz */

/* continuous and non-standard rates क्रम flexibility */
#घोषणा SOF_RATE_CONTINUOUS	(1 << 30)  /**< range */
#घोषणा SOF_RATE_KNOT		(1 << 31)  /**< non-continuous */

/* generic PCM flags क्रम runसमय settings */
#घोषणा SOF_PCM_FLAG_XRUN_STOP	(1 << 0) /**< Stop on any XRUN */

/* stream PCM frame क्रमmat */
क्रमागत sof_ipc_frame अणु
	SOF_IPC_FRAME_S16_LE = 0,
	SOF_IPC_FRAME_S24_4LE,
	SOF_IPC_FRAME_S32_LE,
	SOF_IPC_FRAME_FLOAT,
	/* other क्रमmats here */
पूर्ण;

/* stream buffer क्रमmat */
क्रमागत sof_ipc_buffer_क्रमmat अणु
	SOF_IPC_BUFFER_INTERLEAVED,
	SOF_IPC_BUFFER_NONINTERLEAVED,
	/* other क्रमmats here */
पूर्ण;

/* stream direction */
क्रमागत sof_ipc_stream_direction अणु
	SOF_IPC_STREAM_PLAYBACK = 0,
	SOF_IPC_STREAM_CAPTURE,
पूर्ण;

/* stream ring info */
काष्ठा sof_ipc_host_buffer अणु
	काष्ठा sof_ipc_hdr hdr;
	uपूर्णांक32_t phy_addr;
	uपूर्णांक32_t pages;
	uपूर्णांक32_t size;
	uपूर्णांक32_t reserved[3];
पूर्ण __packed;

काष्ठा sof_ipc_stream_params अणु
	काष्ठा sof_ipc_hdr hdr;
	काष्ठा sof_ipc_host_buffer buffer;
	uपूर्णांक32_t direction;	/**< क्रमागत sof_ipc_stream_direction */
	uपूर्णांक32_t frame_fmt;	/**< क्रमागत sof_ipc_frame */
	uपूर्णांक32_t buffer_fmt;	/**< क्रमागत sof_ipc_buffer_क्रमmat */
	uपूर्णांक32_t rate;
	uपूर्णांक16_t stream_tag;
	uपूर्णांक16_t channels;
	uपूर्णांक16_t sample_valid_bytes;
	uपूर्णांक16_t sample_container_bytes;

	uपूर्णांक32_t host_period_bytes;
	uपूर्णांक16_t no_stream_position; /**< 1 means करोn't send stream position */

	uपूर्णांक16_t reserved[3];
	uपूर्णांक16_t chmap[SOF_IPC_MAX_CHANNELS];	/**< channel map - SOF_CHMAP_ */
पूर्ण __packed;

/* PCM params info - SOF_IPC_STREAM_PCM_PARAMS */
काष्ठा sof_ipc_pcm_params अणु
	काष्ठा sof_ipc_cmd_hdr hdr;
	uपूर्णांक32_t comp_id;
	uपूर्णांक32_t flags;		/**< generic PCM flags - SOF_PCM_FLAG_ */
	uपूर्णांक32_t reserved[2];
	काष्ठा sof_ipc_stream_params params;
पूर्ण  __packed;

/* PCM params info reply - SOF_IPC_STREAM_PCM_PARAMS_REPLY */
काष्ठा sof_ipc_pcm_params_reply अणु
	काष्ठा sof_ipc_reply rhdr;
	uपूर्णांक32_t comp_id;
	uपूर्णांक32_t posn_offset;
पूर्ण __packed;

/* मुक्त stream - SOF_IPC_STREAM_PCM_PARAMS */
काष्ठा sof_ipc_stream अणु
	काष्ठा sof_ipc_cmd_hdr hdr;
	uपूर्णांक32_t comp_id;
पूर्ण __packed;

/* flags indicating which समय stamps are in sync with each other */
#घोषणा	SOF_TIME_HOST_SYNC	(1 << 0)
#घोषणा	SOF_TIME_DAI_SYNC	(1 << 1)
#घोषणा	SOF_TIME_WALL_SYNC	(1 << 2)
#घोषणा	SOF_TIME_STAMP_SYNC	(1 << 3)

/* flags indicating which समय stamps are valid */
#घोषणा	SOF_TIME_HOST_VALID	(1 << 8)
#घोषणा	SOF_TIME_DAI_VALID	(1 << 9)
#घोषणा	SOF_TIME_WALL_VALID	(1 << 10)
#घोषणा	SOF_TIME_STAMP_VALID	(1 << 11)

/* flags indicating समय stamps are 64bit अन्यथा 3use low 32bit */
#घोषणा	SOF_TIME_HOST_64	(1 << 16)
#घोषणा	SOF_TIME_DAI_64		(1 << 17)
#घोषणा	SOF_TIME_WALL_64	(1 << 18)
#घोषणा	SOF_TIME_STAMP_64	(1 << 19)

काष्ठा sof_ipc_stream_posn अणु
	काष्ठा sof_ipc_reply rhdr;
	uपूर्णांक32_t comp_id;	/**< host component ID */
	uपूर्णांक32_t flags;		/**< SOF_TIME_ */
	uपूर्णांक32_t wallघड़ी_hz;	/**< frequency of wallघड़ी in Hz */
	uपूर्णांक32_t बारtamp_ns;	/**< resolution of बारtamp in ns */
	uपूर्णांक64_t host_posn;	/**< host DMA position in bytes */
	uपूर्णांक64_t dai_posn;	/**< DAI DMA position in bytes */
	uपूर्णांक64_t comp_posn;	/**< comp position in bytes */
	uपूर्णांक64_t wallघड़ी;	/**< audio wall घड़ी */
	uपूर्णांक64_t बारtamp;	/**< प्रणाली समय stamp */
	uपूर्णांक32_t xrun_comp_id;	/**< comp ID of XRUN component */
	पूर्णांक32_t xrun_size;	/**< XRUN size in bytes */
पूर्ण  __packed;

#पूर्ण_अगर
