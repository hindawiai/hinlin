<शैली गुरु>
/* SPDX-License-Identअगरier: (GPL-2.0-only OR BSD-3-Clause) */
/*
 * This file is provided under a dual BSD/GPLv2 license.  When using or
 * redistributing this file, you may करो so under either license.
 *
 * Copyright(c) 2018 Intel Corporation. All rights reserved.
 */

#अगर_अघोषित __INCLUDE_SOUND_SOF_CONTROL_H__
#घोषणा __INCLUDE_SOUND_SOF_CONTROL_H__

#समावेश <uapi/sound/sof/header.h>
#समावेश <sound/sof/header.h>

/*
 * Component Mixers and Controls
 */

/* channel positions - uses same values as ALSA */
क्रमागत sof_ipc_chmap अणु
	SOF_CHMAP_UNKNOWN = 0,
	SOF_CHMAP_NA,		/**< N/A, silent */
	SOF_CHMAP_MONO,		/**< mono stream */
	SOF_CHMAP_FL,		/**< front left */
	SOF_CHMAP_FR,		/**< front right */
	SOF_CHMAP_RL,		/**< rear left */
	SOF_CHMAP_RR,		/**< rear right */
	SOF_CHMAP_FC,		/**< front centre */
	SOF_CHMAP_LFE,		/**< LFE */
	SOF_CHMAP_SL,		/**< side left */
	SOF_CHMAP_SR,		/**< side right */
	SOF_CHMAP_RC,		/**< rear centre */
	SOF_CHMAP_FLC,		/**< front left centre */
	SOF_CHMAP_FRC,		/**< front right centre */
	SOF_CHMAP_RLC,		/**< rear left centre */
	SOF_CHMAP_RRC,		/**< rear right centre */
	SOF_CHMAP_FLW,		/**< front left wide */
	SOF_CHMAP_FRW,		/**< front right wide */
	SOF_CHMAP_FLH,		/**< front left high */
	SOF_CHMAP_FCH,		/**< front centre high */
	SOF_CHMAP_FRH,		/**< front right high */
	SOF_CHMAP_TC,		/**< top centre */
	SOF_CHMAP_TFL,		/**< top front left */
	SOF_CHMAP_TFR,		/**< top front right */
	SOF_CHMAP_TFC,		/**< top front centre */
	SOF_CHMAP_TRL,		/**< top rear left */
	SOF_CHMAP_TRR,		/**< top rear right */
	SOF_CHMAP_TRC,		/**< top rear centre */
	SOF_CHMAP_TFLC,		/**< top front left centre */
	SOF_CHMAP_TFRC,		/**< top front right centre */
	SOF_CHMAP_TSL,		/**< top side left */
	SOF_CHMAP_TSR,		/**< top side right */
	SOF_CHMAP_LLFE,		/**< left LFE */
	SOF_CHMAP_RLFE,		/**< right LFE */
	SOF_CHMAP_BC,		/**< bottom centre */
	SOF_CHMAP_BLC,		/**< bottom left centre */
	SOF_CHMAP_BRC,		/**< bottom right centre */
	SOF_CHMAP_LAST = SOF_CHMAP_BRC,
पूर्ण;

/* control data type and direction */
क्रमागत sof_ipc_ctrl_type अणु
	/*  per channel data - uses काष्ठा sof_ipc_ctrl_value_chan */
	SOF_CTRL_TYPE_VALUE_CHAN_GET = 0,
	SOF_CTRL_TYPE_VALUE_CHAN_SET,
	/* component data - uses काष्ठा sof_ipc_ctrl_value_comp */
	SOF_CTRL_TYPE_VALUE_COMP_GET,
	SOF_CTRL_TYPE_VALUE_COMP_SET,
	/* bespoke data - uses काष्ठा sof_abi_hdr */
	SOF_CTRL_TYPE_DATA_GET,
	SOF_CTRL_TYPE_DATA_SET,
पूर्ण;

/* control command type */
क्रमागत sof_ipc_ctrl_cmd अणु
	SOF_CTRL_CMD_VOLUME = 0, /**< maps to ALSA volume style controls */
	SOF_CTRL_CMD_ENUM,	/**< maps to ALSA क्रमागत style controls */
	SOF_CTRL_CMD_SWITCH,	/**< maps to ALSA चयन style controls */
	SOF_CTRL_CMD_BINARY,	/**< maps to ALSA binary style controls */
पूर्ण;

/* generic channel mapped value data */
काष्ठा sof_ipc_ctrl_value_chan अणु
	uपूर्णांक32_t channel;	/**< channel map - क्रमागत sof_ipc_chmap */
	uपूर्णांक32_t value;
पूर्ण __packed;

/* generic component mapped value data */
काष्ठा sof_ipc_ctrl_value_comp अणु
	uपूर्णांक32_t index;	/**< component source/sink/control index in control */
	जोड़ अणु
		uपूर्णांक32_t uvalue;
		पूर्णांक32_t svalue;
	पूर्ण;
पूर्ण __packed;

/* generic control data */
काष्ठा sof_ipc_ctrl_data अणु
	काष्ठा sof_ipc_reply rhdr;
	uपूर्णांक32_t comp_id;

	/* control access and data type */
	uपूर्णांक32_t type;		/**< क्रमागत sof_ipc_ctrl_type */
	uपूर्णांक32_t cmd;		/**< क्रमागत sof_ipc_ctrl_cmd */
	uपूर्णांक32_t index;		/**< control index क्रम comps > 1 control */

	/* control data - can either be appended or DMAed from host */
	काष्ठा sof_ipc_host_buffer buffer;
	uपूर्णांक32_t num_elems;	/**< in array elems or bytes क्रम data type */
	uपूर्णांक32_t elems_reमुख्यing;	/**< elems reमुख्यing अगर sent in parts */

	uपूर्णांक32_t msg_index;	/**< क्रम large messages sent in parts */

	/* reserved क्रम future use */
	uपूर्णांक32_t reserved[6];

	/* control data - add new types अगर needed */
	जोड़ अणु
		/* channel values can be used by volume type controls */
		काष्ठा sof_ipc_ctrl_value_chan chanv[0];
		/* component values used by routing controls like mux, mixer */
		काष्ठा sof_ipc_ctrl_value_comp compv[0];
		/* data can be used by binary controls */
		काष्ठा sof_abi_hdr data[0];
	पूर्ण;
पूर्ण __packed;

/** Event type */
क्रमागत sof_ipc_ctrl_event_type अणु
	SOF_CTRL_EVENT_GENERIC = 0,	/**< generic event */
	SOF_CTRL_EVENT_GENERIC_METADATA,	/**< generic event with metadata */
	SOF_CTRL_EVENT_KD,	/**< keyword detection event */
	SOF_CTRL_EVENT_VAD,	/**< voice activity detection event */
पूर्ण;

/**
 * Generic notअगरication data.
 */
काष्ठा sof_ipc_comp_event अणु
	काष्ठा sof_ipc_reply rhdr;
	uपूर्णांक16_t src_comp_type;	/**< COMP_TYPE_ */
	uपूर्णांक32_t src_comp_id;	/**< source component id */
	uपूर्णांक32_t event_type;	/**< event type - SOF_CTRL_EVENT_* */
	uपूर्णांक32_t num_elems;	/**< in array elems or bytes क्रम data type */

	/* reserved क्रम future use */
	uपूर्णांक32_t reserved[8];

	/* control data - add new types अगर needed */
	जोड़ अणु
		/* data can be used by binary controls */
		काष्ठा sof_abi_hdr data[0];
		/* event specअगरic values */
		uपूर्णांक32_t event_value;
	पूर्ण;
पूर्ण __packed;

#पूर्ण_अगर
