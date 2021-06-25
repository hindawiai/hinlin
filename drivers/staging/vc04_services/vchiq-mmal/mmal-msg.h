<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Broadcom BM2835 V4L2 driver
 *
 * Copyright तऊ 2013 Raspberry Pi (Trading) Ltd.
 *
 * Authors: Vincent Sanders @ Collabora
 *          Dave Stevenson @ Broadcom
 *		(now dave.stevenson@raspberrypi.org)
 *          Simon Mellor @ Broadcom
 *          Luke Diamand @ Broadcom
 */

/*
 * all the data काष्ठाures which serialise the MMAL protocol. note
 * these are directly mapped onto the recived message data.
 *
 * BEWARE: They seem to *assume* poपूर्णांकers are u32 and that there is no
 * काष्ठाure padding!
 *
 * NOTE: this implementation uses kernel types to ensure sizes. Rather
 * than assigning values to क्रमागतs to क्रमce their size the
 * implementation uses fixed size types and not the क्रमागतs (though the
 * comments have the actual क्रमागत type
 */
#अगर_अघोषित MMAL_MSG_H
#घोषणा MMAL_MSG_H

#घोषणा VC_MMAL_VER 15
#घोषणा VC_MMAL_MIN_VER 10

/* max total message size is 512 bytes */
#घोषणा MMAL_MSG_MAX_SIZE 512
/* with six 32bit header elements max payload is thereक्रमe 488 bytes */
#घोषणा MMAL_MSG_MAX_PAYLOAD 488

#समावेश "mmal-msg-common.h"
#समावेश "mmal-msg-format.h"
#समावेश "mmal-msg-port.h"
#समावेश "mmal-vchiq.h"

क्रमागत mmal_msg_type अणु
	MMAL_MSG_TYPE_QUIT = 1,
	MMAL_MSG_TYPE_SERVICE_CLOSED,
	MMAL_MSG_TYPE_GET_VERSION,
	MMAL_MSG_TYPE_COMPONENT_CREATE,
	MMAL_MSG_TYPE_COMPONENT_DESTROY,	/* 5 */
	MMAL_MSG_TYPE_COMPONENT_ENABLE,
	MMAL_MSG_TYPE_COMPONENT_DISABLE,
	MMAL_MSG_TYPE_PORT_INFO_GET,
	MMAL_MSG_TYPE_PORT_INFO_SET,
	MMAL_MSG_TYPE_PORT_ACTION,		/* 10 */
	MMAL_MSG_TYPE_BUFFER_FROM_HOST,
	MMAL_MSG_TYPE_BUFFER_TO_HOST,
	MMAL_MSG_TYPE_GET_STATS,
	MMAL_MSG_TYPE_PORT_PARAMETER_SET,
	MMAL_MSG_TYPE_PORT_PARAMETER_GET,	/* 15 */
	MMAL_MSG_TYPE_EVENT_TO_HOST,
	MMAL_MSG_TYPE_GET_CORE_STATS_FOR_PORT,
	MMAL_MSG_TYPE_OPAQUE_ALLOCATOR,
	MMAL_MSG_TYPE_CONSUME_MEM,
	MMAL_MSG_TYPE_LMK,			/* 20 */
	MMAL_MSG_TYPE_OPAQUE_ALLOCATOR_DESC,
	MMAL_MSG_TYPE_DRM_GET_LHS32,
	MMAL_MSG_TYPE_DRM_GET_TIME,
	MMAL_MSG_TYPE_BUFFER_FROM_HOST_ZEROLEN,
	MMAL_MSG_TYPE_PORT_FLUSH,		/* 25 */
	MMAL_MSG_TYPE_HOST_LOG,
	MMAL_MSG_TYPE_MSG_LAST
पूर्ण;

/* port action request messages dअगरfer depending on the action type */
क्रमागत mmal_msg_port_action_type अणु
	MMAL_MSG_PORT_ACTION_TYPE_UNKNOWN = 0,	/* Unknown action */
	MMAL_MSG_PORT_ACTION_TYPE_ENABLE,	/* Enable a port */
	MMAL_MSG_PORT_ACTION_TYPE_DISABLE,	/* Disable a port */
	MMAL_MSG_PORT_ACTION_TYPE_FLUSH,	/* Flush a port */
	MMAL_MSG_PORT_ACTION_TYPE_CONNECT,	/* Connect ports */
	MMAL_MSG_PORT_ACTION_TYPE_DISCONNECT,	/* Disconnect ports */
	MMAL_MSG_PORT_ACTION_TYPE_SET_REQUIREMENTS, /* Set buffer requirements*/
पूर्ण;

काष्ठा mmal_msg_header अणु
	u32 magic;
	u32 type;	/* क्रमागत mmal_msg_type */

	/* Opaque handle to the control service */
	u32 control_service;

	u32 context;	/* a u32 per message context */
	u32 status;	/* The status of the vchiq operation */
	u32 padding;
पूर्ण;

/* Send from VC to host to report version */
काष्ठा mmal_msg_version अणु
	u32 flags;
	u32 major;
	u32 minor;
	u32 minimum;
पूर्ण;

/* request to VC to create component */
काष्ठा mmal_msg_component_create अणु
	u32 client_component;	/* component context */
	अक्षर name[128];
	u32 pid;		/* For debug */
पूर्ण;

/* reply from VC to component creation request */
काष्ठा mmal_msg_component_create_reply अणु
	u32 status;	/* क्रमागत mmal_msg_status - how करोes this dअगरfer to
			 * the one in the header?
			 */
	u32 component_handle; /* VideoCore handle क्रम component */
	u32 input_num;        /* Number of input ports */
	u32 output_num;       /* Number of output ports */
	u32 घड़ी_num;        /* Number of घड़ी ports */
पूर्ण;

/* request to VC to destroy a component */
काष्ठा mmal_msg_component_destroy अणु
	u32 component_handle;
पूर्ण;

काष्ठा mmal_msg_component_destroy_reply अणु
	u32 status; /* The component deकाष्ठाion status */
पूर्ण;

/* request and reply to VC to enable a component */
काष्ठा mmal_msg_component_enable अणु
	u32 component_handle;
पूर्ण;

काष्ठा mmal_msg_component_enable_reply अणु
	u32 status; /* The component enable status */
पूर्ण;

/* request and reply to VC to disable a component */
काष्ठा mmal_msg_component_disable अणु
	u32 component_handle;
पूर्ण;

काष्ठा mmal_msg_component_disable_reply अणु
	u32 status; /* The component disable status */
पूर्ण;

/* request to VC to get port inक्रमmation */
काष्ठा mmal_msg_port_info_get अणु
	u32 component_handle;  /* component handle port is associated with */
	u32 port_type;         /* क्रमागत mmal_msg_port_type */
	u32 index;             /* port index to query */
पूर्ण;

/* reply from VC to get port info request */
काष्ठा mmal_msg_port_info_get_reply अणु
	u32 status;		/* क्रमागत mmal_msg_status */
	u32 component_handle;	/* component handle port is associated with */
	u32 port_type;		/* क्रमागत mmal_msg_port_type */
	u32 port_index;		/* port indexed in query */
	s32 found;		/* unused */
	u32 port_handle;	/* Handle to use क्रम this port */
	काष्ठा mmal_port port;
	काष्ठा mmal_es_क्रमmat क्रमmat; /* elementary stream क्रमmat */
	जोड़ mmal_es_specअगरic_क्रमmat es; /* es type specअगरic data */
	u8 extradata[MMAL_FORMAT_EXTRADATA_MAX_SIZE]; /* es extra data */
पूर्ण;

/* request to VC to set port inक्रमmation */
काष्ठा mmal_msg_port_info_set अणु
	u32 component_handle;
	u32 port_type;		/* क्रमागत mmal_msg_port_type */
	u32 port_index;		/* port indexed in query */
	काष्ठा mmal_port port;
	काष्ठा mmal_es_क्रमmat क्रमmat;
	जोड़ mmal_es_specअगरic_क्रमmat es;
	u8 extradata[MMAL_FORMAT_EXTRADATA_MAX_SIZE];
पूर्ण;

/* reply from VC to port info set request */
काष्ठा mmal_msg_port_info_set_reply अणु
	u32 status;
	u32 component_handle;	/* component handle port is associated with */
	u32 port_type;		/* क्रमागत mmal_msg_port_type */
	u32 index;		/* port indexed in query */
	s32 found;		/* unused */
	u32 port_handle;	/* Handle to use क्रम this port */
	काष्ठा mmal_port port;
	काष्ठा mmal_es_क्रमmat क्रमmat;
	जोड़ mmal_es_specअगरic_क्रमmat es;
	u8 extradata[MMAL_FORMAT_EXTRADATA_MAX_SIZE];
पूर्ण;

/* port action requests that take a mmal_port as a parameter */
काष्ठा mmal_msg_port_action_port अणु
	u32 component_handle;
	u32 port_handle;
	u32 action;		/* क्रमागत mmal_msg_port_action_type */
	काष्ठा mmal_port port;
पूर्ण;

/* port action requests that take handles as a parameter */
काष्ठा mmal_msg_port_action_handle अणु
	u32 component_handle;
	u32 port_handle;
	u32 action;		/* क्रमागत mmal_msg_port_action_type */
	u32 connect_component_handle;
	u32 connect_port_handle;
पूर्ण;

काष्ठा mmal_msg_port_action_reply अणु
	u32 status;	/* The port action operation status */
पूर्ण;

/* MMAL buffer transfer */

/* Size of space reserved in a buffer message क्रम लघु messages. */
#घोषणा MMAL_VC_SHORT_DATA 128

/* Signals that the current payload is the end of the stream of data */
#घोषणा MMAL_BUFFER_HEADER_FLAG_EOS                    BIT(0)
/* Signals that the start of the current payload starts a frame */
#घोषणा MMAL_BUFFER_HEADER_FLAG_FRAME_START            BIT(1)
/* Signals that the end of the current payload ends a frame */
#घोषणा MMAL_BUFFER_HEADER_FLAG_FRAME_END              BIT(2)
/* Signals that the current payload contains only complete frames (>1) */
#घोषणा MMAL_BUFFER_HEADER_FLAG_FRAME                  \
	(MMAL_BUFFER_HEADER_FLAG_FRAME_START | \
	 MMAL_BUFFER_HEADER_FLAG_FRAME_END)
/* Signals that the current payload is a keyframe (i.e. self decodable) */
#घोषणा MMAL_BUFFER_HEADER_FLAG_KEYFRAME               BIT(3)
/*
 * Signals a discontinuity in the stream of data (e.g. after a seek).
 * Can be used क्रम instance by a decoder to reset its state
 */
#घोषणा MMAL_BUFFER_HEADER_FLAG_DISCONTINUITY          BIT(4)
/*
 * Signals a buffer containing some kind of config data क्रम the component
 * (e.g. codec config data)
 */
#घोषणा MMAL_BUFFER_HEADER_FLAG_CONFIG                 BIT(5)
/* Signals an encrypted payload */
#घोषणा MMAL_BUFFER_HEADER_FLAG_ENCRYPTED              BIT(6)
/* Signals a buffer containing side inक्रमmation */
#घोषणा MMAL_BUFFER_HEADER_FLAG_CODECSIDEINFO          BIT(7)
/*
 * Signals a buffer which is the snapshot/postview image from a stills
 * capture
 */
#घोषणा MMAL_BUFFER_HEADER_FLAGS_SNAPSHOT              BIT(8)
/* Signals a buffer which contains data known to be corrupted */
#घोषणा MMAL_BUFFER_HEADER_FLAG_CORRUPTED              BIT(9)
/* Signals that a buffer failed to be transmitted */
#घोषणा MMAL_BUFFER_HEADER_FLAG_TRANSMISSION_FAILED    BIT(10)

काष्ठा mmal_driver_buffer अणु
	u32 magic;
	u32 component_handle;
	u32 port_handle;
	u32 client_context;
पूर्ण;

/* buffer header */
काष्ठा mmal_buffer_header अणु
	u32 next;	/* next header */
	u32 priv;	/* framework निजी data */
	u32 cmd;
	u32 data;
	u32 alloc_size;
	u32 length;
	u32 offset;
	u32 flags;
	s64 pts;
	s64 dts;
	u32 type;
	u32 user_data;
पूर्ण;

काष्ठा mmal_buffer_header_type_specअगरic अणु
	जोड़ अणु
		काष्ठा अणु
		u32 planes;
		u32 offset[4];
		u32 pitch[4];
		u32 flags;
		पूर्ण video;
	पूर्ण u;
पूर्ण;

काष्ठा mmal_msg_buffer_from_host अणु
	/*
	 *The front 32 bytes of the buffer header are copied
	 * back to us in the reply to allow क्रम context. This
	 * area is used to store two mmal_driver_buffer काष्ठाures to
	 * allow क्रम multiple concurrent service users.
	 */
	/* control data */
	काष्ठा mmal_driver_buffer drvbuf;

	/* referenced control data क्रम passthrough buffer management */
	काष्ठा mmal_driver_buffer drvbuf_ref;
	काष्ठा mmal_buffer_header buffer_header; /* buffer header itself */
	काष्ठा mmal_buffer_header_type_specअगरic buffer_header_type_specअगरic;
	s32 is_zero_copy;
	s32 has_reference;

	/* allows लघु data to be xfered in control message */
	u32 payload_in_message;
	u8 लघु_data[MMAL_VC_SHORT_DATA];
पूर्ण;

/* port parameter setting */

#घोषणा MMAL_WORKER_PORT_PARAMETER_SPACE      96

काष्ठा mmal_msg_port_parameter_set अणु
	u32 component_handle;	/* component */
	u32 port_handle;	/* port */
	u32 id;			/* Parameter ID  */
	u32 size;		/* Parameter size */
	u32 value[MMAL_WORKER_PORT_PARAMETER_SPACE];
पूर्ण;

काष्ठा mmal_msg_port_parameter_set_reply अणु
	u32 status;	/* क्रमागत mmal_msg_status toकरो: how करोes this
			 * dअगरfer to the one in the header?
			 */
पूर्ण;

/* port parameter getting */

काष्ठा mmal_msg_port_parameter_get अणु
	u32 component_handle;	/* component */
	u32 port_handle;	/* port */
	u32 id;			/* Parameter ID  */
	u32 size;		/* Parameter size */
पूर्ण;

काष्ठा mmal_msg_port_parameter_get_reply अणु
	u32 status;		/* Status of mmal_port_parameter_get call */
	u32 id;			/* Parameter ID  */
	u32 size;		/* Parameter size */
	u32 value[MMAL_WORKER_PORT_PARAMETER_SPACE];
पूर्ण;

/* event messages */
#घोषणा MMAL_WORKER_EVENT_SPACE 256

काष्ठा mmal_msg_event_to_host अणु
	u32 client_component;	/* component context */

	u32 port_type;
	u32 port_num;

	u32 cmd;
	u32 length;
	u8 data[MMAL_WORKER_EVENT_SPACE];
	u32 delayed_buffer;
पूर्ण;

/* all mmal messages are serialised through this काष्ठाure */
काष्ठा mmal_msg अणु
	/* header */
	काष्ठा mmal_msg_header h;
	/* payload */
	जोड़ अणु
		काष्ठा mmal_msg_version version;

		काष्ठा mmal_msg_component_create component_create;
		काष्ठा mmal_msg_component_create_reply component_create_reply;

		काष्ठा mmal_msg_component_destroy component_destroy;
		काष्ठा mmal_msg_component_destroy_reply component_destroy_reply;

		काष्ठा mmal_msg_component_enable component_enable;
		काष्ठा mmal_msg_component_enable_reply component_enable_reply;

		काष्ठा mmal_msg_component_disable component_disable;
		काष्ठा mmal_msg_component_disable_reply component_disable_reply;

		काष्ठा mmal_msg_port_info_get port_info_get;
		काष्ठा mmal_msg_port_info_get_reply port_info_get_reply;

		काष्ठा mmal_msg_port_info_set port_info_set;
		काष्ठा mmal_msg_port_info_set_reply port_info_set_reply;

		काष्ठा mmal_msg_port_action_port port_action_port;
		काष्ठा mmal_msg_port_action_handle port_action_handle;
		काष्ठा mmal_msg_port_action_reply port_action_reply;

		काष्ठा mmal_msg_buffer_from_host buffer_from_host;

		काष्ठा mmal_msg_port_parameter_set port_parameter_set;
		काष्ठा mmal_msg_port_parameter_set_reply
			port_parameter_set_reply;
		काष्ठा mmal_msg_port_parameter_get
			port_parameter_get;
		काष्ठा mmal_msg_port_parameter_get_reply
			port_parameter_get_reply;

		काष्ठा mmal_msg_event_to_host event_to_host;

		u8 payload[MMAL_MSG_MAX_PAYLOAD];
	पूर्ण u;
पूर्ण;
#पूर्ण_अगर
