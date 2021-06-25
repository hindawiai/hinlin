<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (c) 2003-2020, Intel Corporation. All rights reserved
 * Intel Management Engine Interface (Intel MEI) Linux driver
 */

#अगर_अघोषित _MEI_HW_TYPES_H_
#घोषणा _MEI_HW_TYPES_H_

#समावेश <linux/uuid.h>

/*
 * Timeouts in Seconds
 */
#घोषणा MEI_HW_READY_TIMEOUT        2  /* Timeout on पढ़ोy message */
#घोषणा MEI_CONNECT_TIMEOUT         3  /* HPS: at least 2 seconds */

#घोषणा MEI_CL_CONNECT_TIMEOUT     15  /* HPS: Client Connect Timeout */
#घोषणा MEI_CLIENTS_INIT_TIMEOUT   15  /* HPS: Clients Enumeration Timeout */

#घोषणा MEI_PGI_TIMEOUT             1  /* PG Isolation समय response 1 sec */
#घोषणा MEI_D0I3_TIMEOUT            5  /* D0i3 set/unset max response समय */
#घोषणा MEI_HBM_TIMEOUT             1  /* 1 second */

/*
 * MEI Version
 */
#घोषणा HBM_MINOR_VERSION                   2
#घोषणा HBM_MAJOR_VERSION                   2

/*
 * MEI version with PGI support
 */
#घोषणा HBM_MINOR_VERSION_PGI               1
#घोषणा HBM_MAJOR_VERSION_PGI               1

/*
 * MEI version with Dynamic clients support
 */
#घोषणा HBM_MINOR_VERSION_DC               0
#घोषणा HBM_MAJOR_VERSION_DC               2

/*
 * MEI version with immediate reply to क्रमागत request support
 */
#घोषणा HBM_MINOR_VERSION_IE               0
#घोषणा HBM_MAJOR_VERSION_IE               2

/*
 * MEI version with disconnect on connection समयout support
 */
#घोषणा HBM_MINOR_VERSION_DOT              0
#घोषणा HBM_MAJOR_VERSION_DOT              2

/*
 * MEI version with notअगरication support
 */
#घोषणा HBM_MINOR_VERSION_EV               0
#घोषणा HBM_MAJOR_VERSION_EV               2

/*
 * MEI version with fixed address client support
 */
#घोषणा HBM_MINOR_VERSION_FA               0
#घोषणा HBM_MAJOR_VERSION_FA               2

/*
 * MEI version with OS ver message support
 */
#घोषणा HBM_MINOR_VERSION_OS               0
#घोषणा HBM_MAJOR_VERSION_OS               2

/*
 * MEI version with dma ring support
 */
#घोषणा HBM_MINOR_VERSION_DR               1
#घोषणा HBM_MAJOR_VERSION_DR               2

/*
 * MEI version with vm tag support
 */
#घोषणा HBM_MINOR_VERSION_VT               2
#घोषणा HBM_MAJOR_VERSION_VT               2

/*
 * MEI version with capabilities message support
 */
#घोषणा HBM_MINOR_VERSION_CAP              2
#घोषणा HBM_MAJOR_VERSION_CAP              2

/*
 * MEI version with client DMA support
 */
#घोषणा HBM_MINOR_VERSION_CD               2
#घोषणा HBM_MAJOR_VERSION_CD               2

/* Host bus message command opcode */
#घोषणा MEI_HBM_CMD_OP_MSK                  0x7f
/* Host bus message command RESPONSE */
#घोषणा MEI_HBM_CMD_RES_MSK                 0x80

/*
 * MEI Bus Message Command IDs
 */
#घोषणा HOST_START_REQ_CMD                  0x01
#घोषणा HOST_START_RES_CMD                  0x81

#घोषणा HOST_STOP_REQ_CMD                   0x02
#घोषणा HOST_STOP_RES_CMD                   0x82

#घोषणा ME_STOP_REQ_CMD                     0x03

#घोषणा HOST_ENUM_REQ_CMD                   0x04
#घोषणा HOST_ENUM_RES_CMD                   0x84

#घोषणा HOST_CLIENT_PROPERTIES_REQ_CMD      0x05
#घोषणा HOST_CLIENT_PROPERTIES_RES_CMD      0x85

#घोषणा CLIENT_CONNECT_REQ_CMD              0x06
#घोषणा CLIENT_CONNECT_RES_CMD              0x86

#घोषणा CLIENT_DISCONNECT_REQ_CMD           0x07
#घोषणा CLIENT_DISCONNECT_RES_CMD           0x87

#घोषणा MEI_FLOW_CONTROL_CMD                0x08

#घोषणा MEI_PG_ISOLATION_ENTRY_REQ_CMD      0x0a
#घोषणा MEI_PG_ISOLATION_ENTRY_RES_CMD      0x8a
#घोषणा MEI_PG_ISOLATION_EXIT_REQ_CMD       0x0b
#घोषणा MEI_PG_ISOLATION_EXIT_RES_CMD       0x8b

#घोषणा MEI_HBM_ADD_CLIENT_REQ_CMD          0x0f
#घोषणा MEI_HBM_ADD_CLIENT_RES_CMD          0x8f

#घोषणा MEI_HBM_NOTIFY_REQ_CMD              0x10
#घोषणा MEI_HBM_NOTIFY_RES_CMD              0x90
#घोषणा MEI_HBM_NOTIFICATION_CMD            0x11

#घोषणा MEI_HBM_DMA_SETUP_REQ_CMD           0x12
#घोषणा MEI_HBM_DMA_SETUP_RES_CMD           0x92

#घोषणा MEI_HBM_CAPABILITIES_REQ_CMD        0x13
#घोषणा MEI_HBM_CAPABILITIES_RES_CMD        0x93

#घोषणा MEI_HBM_CLIENT_DMA_MAP_REQ_CMD      0x14
#घोषणा MEI_HBM_CLIENT_DMA_MAP_RES_CMD      0x94

#घोषणा MEI_HBM_CLIENT_DMA_UNMAP_REQ_CMD    0x15
#घोषणा MEI_HBM_CLIENT_DMA_UNMAP_RES_CMD    0x95

/*
 * MEI Stop Reason
 * used by hbm_host_stop_request.reason
 */
क्रमागत mei_stop_reason_types अणु
	DRIVER_STOP_REQUEST = 0x00,
	DEVICE_D1_ENTRY = 0x01,
	DEVICE_D2_ENTRY = 0x02,
	DEVICE_D3_ENTRY = 0x03,
	SYSTEM_S1_ENTRY = 0x04,
	SYSTEM_S2_ENTRY = 0x05,
	SYSTEM_S3_ENTRY = 0x06,
	SYSTEM_S4_ENTRY = 0x07,
	SYSTEM_S5_ENTRY = 0x08
पूर्ण;


/**
 * क्रमागत mei_hbm_status  - mei host bus messages वापस values
 *
 * @MEI_HBMS_SUCCESS           : status success
 * @MEI_HBMS_CLIENT_NOT_FOUND  : client not found
 * @MEI_HBMS_ALREADY_EXISTS    : connection alपढ़ोy established
 * @MEI_HBMS_REJECTED          : connection is rejected
 * @MEI_HBMS_INVALID_PARAMETER : invalid parameter
 * @MEI_HBMS_NOT_ALLOWED       : operation not allowed
 * @MEI_HBMS_ALREADY_STARTED   : प्रणाली is alपढ़ोy started
 * @MEI_HBMS_NOT_STARTED       : प्रणाली not started
 *
 * @MEI_HBMS_MAX               : sentinel
 */
क्रमागत mei_hbm_status अणु
	MEI_HBMS_SUCCESS           = 0,
	MEI_HBMS_CLIENT_NOT_FOUND  = 1,
	MEI_HBMS_ALREADY_EXISTS    = 2,
	MEI_HBMS_REJECTED          = 3,
	MEI_HBMS_INVALID_PARAMETER = 4,
	MEI_HBMS_NOT_ALLOWED       = 5,
	MEI_HBMS_ALREADY_STARTED   = 6,
	MEI_HBMS_NOT_STARTED       = 7,

	MEI_HBMS_MAX
पूर्ण;


/*
 * Client Connect Status
 * used by hbm_client_connect_response.status
 */
क्रमागत mei_cl_connect_status अणु
	MEI_CL_CONN_SUCCESS          = MEI_HBMS_SUCCESS,
	MEI_CL_CONN_NOT_FOUND        = MEI_HBMS_CLIENT_NOT_FOUND,
	MEI_CL_CONN_ALREADY_STARTED  = MEI_HBMS_ALREADY_EXISTS,
	MEI_CL_CONN_OUT_OF_RESOURCES = MEI_HBMS_REJECTED,
	MEI_CL_CONN_MESSAGE_SMALL    = MEI_HBMS_INVALID_PARAMETER,
	MEI_CL_CONN_NOT_ALLOWED      = MEI_HBMS_NOT_ALLOWED,
पूर्ण;

/*
 * Client Disconnect Status
 */
क्रमागत mei_cl_disconnect_status अणु
	MEI_CL_DISCONN_SUCCESS = MEI_HBMS_SUCCESS
पूर्ण;

/**
 * क्रमागत mei_ext_hdr_type - extended header type used in
 *    extended header TLV
 *
 * @MEI_EXT_HDR_NONE: sentinel
 * @MEI_EXT_HDR_VTAG: vtag header
 */
क्रमागत mei_ext_hdr_type अणु
	MEI_EXT_HDR_NONE = 0,
	MEI_EXT_HDR_VTAG = 1,
पूर्ण;

/**
 * काष्ठा mei_ext_hdr - extend header descriptor (TLV)
 * @type: क्रमागत mei_ext_hdr_type
 * @length: length excluding descriptor
 * @ext_payload: payload of the specअगरic extended header
 * @hdr: place holder क्रम actual header
 */
काष्ठा mei_ext_hdr अणु
	u8 type;
	u8 length;
	u8 ext_payload[2];
	u8 hdr[];
पूर्ण;

/**
 * काष्ठा mei_ext_meta_hdr - extend header meta data
 * @count: number of headers
 * @size: total size of the extended header list excluding meta header
 * @reserved: reserved
 * @hdrs: extended headers TLV list
 */
काष्ठा mei_ext_meta_hdr अणु
	u8 count;
	u8 size;
	u8 reserved[2];
	काष्ठा mei_ext_hdr hdrs[];
पूर्ण;

/*
 * Extended header iterator functions
 */
/**
 * mei_ext_hdr - extended header iterator begin
 *
 * @meta: meta header of the extended header list
 *
 * Return:
 *     The first extended header
 */
अटल अंतरभूत काष्ठा mei_ext_hdr *mei_ext_begin(काष्ठा mei_ext_meta_hdr *meta)
अणु
	वापस meta->hdrs;
पूर्ण

/**
 * mei_ext_last - check अगर the ext is the last one in the TLV list
 *
 * @meta: meta header of the extended header list
 * @ext: a meta header on the list
 *
 * Return: true अगर ext is the last header on the list
 */
अटल अंतरभूत bool mei_ext_last(काष्ठा mei_ext_meta_hdr *meta,
				काष्ठा mei_ext_hdr *ext)
अणु
	वापस (u8 *)ext >= (u8 *)meta + माप(*meta) + (meta->size * 4);
पूर्ण

/**
 *mei_ext_next - following extended header on the TLV list
 *
 * @ext: current extend header
 *
 * Context: The function करोes not check क्रम the overflows,
 *          one should call mei_ext_last beक्रमe.
 *
 * Return: The following extend header after @ext
 */
अटल अंतरभूत काष्ठा mei_ext_hdr *mei_ext_next(काष्ठा mei_ext_hdr *ext)
अणु
	वापस (काष्ठा mei_ext_hdr *)(ext->hdr + (ext->length * 4));
पूर्ण

/**
 * काष्ठा mei_msg_hdr - MEI BUS Interface Section
 *
 * @me_addr: device address
 * @host_addr: host address
 * @length: message length
 * @reserved: reserved
 * @extended: message has extended header
 * @dma_ring: message is on dma ring
 * @पूर्णांकernal: message is पूर्णांकernal
 * @msg_complete: last packet of the message
 * @extension: extension of the header
 */
काष्ठा mei_msg_hdr अणु
	u32 me_addr:8;
	u32 host_addr:8;
	u32 length:9;
	u32 reserved:3;
	u32 extended:1;
	u32 dma_ring:1;
	u32 पूर्णांकernal:1;
	u32 msg_complete:1;
	u32 extension[];
पूर्ण __packed;

/* The length is up to 9 bits */
#घोषणा MEI_MSG_MAX_LEN_MASK GENMASK(9, 0)

काष्ठा mei_bus_message अणु
	u8 hbm_cmd;
	u8 data[];
पूर्ण __packed;

/**
 * काष्ठा hbm_cl_cmd - client specअगरic host bus command
 *	CONNECT, DISCONNECT, and FlOW CONTROL
 *
 * @hbm_cmd: bus message command header
 * @me_addr: address of the client in ME
 * @host_addr: address of the client in the driver
 * @data: generic data
 */
काष्ठा mei_hbm_cl_cmd अणु
	u8 hbm_cmd;
	u8 me_addr;
	u8 host_addr;
	u8 data;
पूर्ण;

काष्ठा hbm_version अणु
	u8 minor_version;
	u8 major_version;
पूर्ण __packed;

काष्ठा hbm_host_version_request अणु
	u8 hbm_cmd;
	u8 reserved;
	काष्ठा hbm_version host_version;
पूर्ण __packed;

काष्ठा hbm_host_version_response अणु
	u8 hbm_cmd;
	u8 host_version_supported;
	काष्ठा hbm_version me_max_version;
पूर्ण __packed;

काष्ठा hbm_host_stop_request अणु
	u8 hbm_cmd;
	u8 reason;
	u8 reserved[2];
पूर्ण __packed;

काष्ठा hbm_host_stop_response अणु
	u8 hbm_cmd;
	u8 reserved[3];
पूर्ण __packed;

काष्ठा hbm_me_stop_request अणु
	u8 hbm_cmd;
	u8 reason;
	u8 reserved[2];
पूर्ण __packed;

/**
 * क्रमागत hbm_host_क्रमागत_flags - क्रमागतeration request flags (HBM version >= 2.0)
 *
 * @MEI_HBM_ENUM_F_ALLOW_ADD: allow dynamic clients add
 * @MEI_HBM_ENUM_F_IMMEDIATE_ENUM: allow FW to send answer immediately
 */
क्रमागत hbm_host_क्रमागत_flags अणु
	MEI_HBM_ENUM_F_ALLOW_ADD = BIT(0),
	MEI_HBM_ENUM_F_IMMEDIATE_ENUM = BIT(1),
पूर्ण;

/**
 * काष्ठा hbm_host_क्रमागत_request - क्रमागतeration request from host to fw
 *
 * @hbm_cmd : bus message command header
 * @flags   : request flags
 * @reserved: reserved
 */
काष्ठा hbm_host_क्रमागत_request अणु
	u8 hbm_cmd;
	u8 flags;
	u8 reserved[2];
पूर्ण __packed;

काष्ठा hbm_host_क्रमागत_response अणु
	u8 hbm_cmd;
	u8 reserved[3];
	u8 valid_addresses[32];
पूर्ण __packed;

/**
 * काष्ठा mei_client_properties - mei client properties
 *
 * @protocol_name: guid of the client
 * @protocol_version: client protocol version
 * @max_number_of_connections: number of possible connections.
 * @fixed_address: fixed me address (0 अगर the client is dynamic)
 * @single_recv_buf: 1 अगर all connections share a single receive buffer.
 * @vt_supported: the client support vtag
 * @reserved: reserved
 * @max_msg_length: MTU of the client
 */
काष्ठा mei_client_properties अणु
	uuid_le protocol_name;
	u8 protocol_version;
	u8 max_number_of_connections;
	u8 fixed_address;
	u8 single_recv_buf:1;
	u8 vt_supported:1;
	u8 reserved:6;
	u32 max_msg_length;
पूर्ण __packed;

काष्ठा hbm_props_request अणु
	u8 hbm_cmd;
	u8 me_addr;
	u8 reserved[2];
पूर्ण __packed;

काष्ठा hbm_props_response अणु
	u8 hbm_cmd;
	u8 me_addr;
	u8 status;
	u8 reserved;
	काष्ठा mei_client_properties client_properties;
पूर्ण __packed;

/**
 * काष्ठा hbm_add_client_request - request to add a client
 *     might be sent by fw after क्रमागतeration has alपढ़ोy completed
 *
 * @hbm_cmd: bus message command header
 * @me_addr: address of the client in ME
 * @reserved: reserved
 * @client_properties: client properties
 */
काष्ठा hbm_add_client_request अणु
	u8 hbm_cmd;
	u8 me_addr;
	u8 reserved[2];
	काष्ठा mei_client_properties client_properties;
पूर्ण __packed;

/**
 * काष्ठा hbm_add_client_response - response to add a client
 *     sent by the host to report client addition status to fw
 *
 * @hbm_cmd: bus message command header
 * @me_addr: address of the client in ME
 * @status: अगर HBMS_SUCCESS then the client can now accept connections.
 * @reserved: reserved
 */
काष्ठा hbm_add_client_response अणु
	u8 hbm_cmd;
	u8 me_addr;
	u8 status;
	u8 reserved;
पूर्ण __packed;

/**
 * काष्ठा hbm_घातer_gate - घातer gate request/response
 *
 * @hbm_cmd: bus message command header
 * @reserved: reserved
 */
काष्ठा hbm_घातer_gate अणु
	u8 hbm_cmd;
	u8 reserved[3];
पूर्ण __packed;

/**
 * काष्ठा hbm_client_connect_request - connect/disconnect request
 *
 * @hbm_cmd: bus message command header
 * @me_addr: address of the client in ME
 * @host_addr: address of the client in the driver
 * @reserved: reserved
 */
काष्ठा hbm_client_connect_request अणु
	u8 hbm_cmd;
	u8 me_addr;
	u8 host_addr;
	u8 reserved;
पूर्ण __packed;

/**
 * काष्ठा hbm_client_connect_response - connect/disconnect response
 *
 * @hbm_cmd: bus message command header
 * @me_addr: address of the client in ME
 * @host_addr: address of the client in the driver
 * @status: status of the request
 */
काष्ठा hbm_client_connect_response अणु
	u8 hbm_cmd;
	u8 me_addr;
	u8 host_addr;
	u8 status;
पूर्ण __packed;


#घोषणा MEI_FC_MESSAGE_RESERVED_LENGTH           5

काष्ठा hbm_flow_control अणु
	u8 hbm_cmd;
	u8 me_addr;
	u8 host_addr;
	u8 reserved[MEI_FC_MESSAGE_RESERVED_LENGTH];
पूर्ण __packed;

#घोषणा MEI_HBM_NOTIFICATION_START 1
#घोषणा MEI_HBM_NOTIFICATION_STOP  0
/**
 * काष्ठा hbm_notअगरication_request - start/stop notअगरication request
 *
 * @hbm_cmd: bus message command header
 * @me_addr: address of the client in ME
 * @host_addr: address of the client in the driver
 * @start:  start = 1 or stop = 0 asynchronous notअगरications
 */
काष्ठा hbm_notअगरication_request अणु
	u8 hbm_cmd;
	u8 me_addr;
	u8 host_addr;
	u8 start;
पूर्ण __packed;

/**
 * काष्ठा hbm_notअगरication_response - start/stop notअगरication response
 *
 * @hbm_cmd: bus message command header
 * @me_addr: address of the client in ME
 * @host_addr: - address of the client in the driver
 * @status: (mei_hbm_status) response status क्रम the request
 *  - MEI_HBMS_SUCCESS: successful stop/start
 *  - MEI_HBMS_CLIENT_NOT_FOUND: अगर the connection could not be found.
 *  - MEI_HBMS_ALREADY_STARTED: क्रम start requests क्रम a previously
 *                         started notअगरication.
 *  - MEI_HBMS_NOT_STARTED: क्रम stop request क्रम a connected client क्रम whom
 *                         asynchronous notअगरications are currently disabled.
 *
 * @start:  start = 1 or stop = 0 asynchronous notअगरications
 * @reserved: reserved
 */
काष्ठा hbm_notअगरication_response अणु
	u8 hbm_cmd;
	u8 me_addr;
	u8 host_addr;
	u8 status;
	u8 start;
	u8 reserved[3];
पूर्ण __packed;

/**
 * काष्ठा hbm_notअगरication - notअगरication event
 *
 * @hbm_cmd: bus message command header
 * @me_addr:  address of the client in ME
 * @host_addr:  address of the client in the driver
 * @reserved: reserved क्रम alignment
 */
काष्ठा hbm_notअगरication अणु
	u8 hbm_cmd;
	u8 me_addr;
	u8 host_addr;
	u8 reserved;
पूर्ण __packed;

/**
 * काष्ठा hbm_dma_mem_dscr - dma ring
 *
 * @addr_hi: the high 32bits of 64 bit address
 * @addr_lo: the low  32bits of 64 bit address
 * @size   : size in bytes (must be घातer of 2)
 */
काष्ठा hbm_dma_mem_dscr अणु
	u32 addr_hi;
	u32 addr_lo;
	u32 size;
पूर्ण __packed;

क्रमागत अणु
	DMA_DSCR_HOST = 0,
	DMA_DSCR_DEVICE = 1,
	DMA_DSCR_CTRL = 2,
	DMA_DSCR_NUM,
पूर्ण;

/**
 * काष्ठा hbm_dma_setup_request - dma setup request
 *
 * @hbm_cmd: bus message command header
 * @reserved: reserved क्रम alignment
 * @dma_dscr: dma descriptor क्रम HOST, DEVICE, and CTRL
 */
काष्ठा hbm_dma_setup_request अणु
	u8 hbm_cmd;
	u8 reserved[3];
	काष्ठा hbm_dma_mem_dscr dma_dscr[DMA_DSCR_NUM];
पूर्ण __packed;

/**
 * काष्ठा hbm_dma_setup_response - dma setup response
 *
 * @hbm_cmd: bus message command header
 * @status: 0 on success; otherwise DMA setup failed.
 * @reserved: reserved क्रम alignment
 */
काष्ठा hbm_dma_setup_response अणु
	u8 hbm_cmd;
	u8 status;
	u8 reserved[2];
पूर्ण __packed;

/**
 * काष्ठा mei_dma_ring_ctrl - dma ring control block
 *
 * @hbuf_wr_idx: host circular buffer ग_लिखो index in slots
 * @reserved1: reserved क्रम alignment
 * @hbuf_rd_idx: host circular buffer पढ़ो index in slots
 * @reserved2: reserved क्रम alignment
 * @dbuf_wr_idx: device circular buffer ग_लिखो index in slots
 * @reserved3: reserved क्रम alignment
 * @dbuf_rd_idx: device circular buffer पढ़ो index in slots
 * @reserved4: reserved क्रम alignment
 */
काष्ठा hbm_dma_ring_ctrl अणु
	u32 hbuf_wr_idx;
	u32 reserved1;
	u32 hbuf_rd_idx;
	u32 reserved2;
	u32 dbuf_wr_idx;
	u32 reserved3;
	u32 dbuf_rd_idx;
	u32 reserved4;
पूर्ण __packed;

/* भव tag supported */
#घोषणा HBM_CAP_VT BIT(0)
/* client dma supported */
#घोषणा HBM_CAP_CD BIT(2)

/**
 * काष्ठा hbm_capability_request - capability request from host to fw
 *
 * @hbm_cmd : bus message command header
 * @capability_requested: biपंचांगask of capabilities requested by host
 */
काष्ठा hbm_capability_request अणु
	u8 hbm_cmd;
	u8 capability_requested[3];
पूर्ण __packed;

/**
 * काष्ठा hbm_capability_response - capability response from fw to host
 *
 * @hbm_cmd : bus message command header
 * @capability_granted: biपंचांगask of capabilities granted by FW
 */
काष्ठा hbm_capability_response अणु
	u8 hbm_cmd;
	u8 capability_granted[3];
पूर्ण __packed;

/**
 * काष्ठा hbm_client_dma_map_request - client dma map request from host to fw
 *
 * @hbm_cmd: bus message command header
 * @client_buffer_id: client buffer id
 * @reserved: reserved
 * @address_lsb: DMA address LSB
 * @address_msb: DMA address MSB
 * @size: DMA size
 */
काष्ठा hbm_client_dma_map_request अणु
	u8 hbm_cmd;
	u8 client_buffer_id;
	u8 reserved[2];
	u32 address_lsb;
	u32 address_msb;
	u32 size;
पूर्ण __packed;

/**
 * काष्ठा hbm_client_dma_unmap_request
 *    client dma unmap request from the host to the firmware
 *
 * @hbm_cmd: bus message command header
 * @status: unmap status
 * @client_buffer_id: client buffer id
 * @reserved: reserved
 */
काष्ठा hbm_client_dma_unmap_request अणु
	u8 hbm_cmd;
	u8 status;
	u8 client_buffer_id;
	u8 reserved;
पूर्ण __packed;

/**
 * काष्ठा hbm_client_dma_response
 *   client dma unmap response from the firmware to the host
 *
 * @hbm_cmd: bus message command header
 * @status: command status
 */
काष्ठा hbm_client_dma_response अणु
	u8 hbm_cmd;
	u8 status;
पूर्ण __packed;

#पूर्ण_अगर
