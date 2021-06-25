<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * ISHTP bus layer messages handling
 *
 * Copyright (c) 2003-2016, Intel Corporation.
 */

#अगर_अघोषित _ISHTP_HBM_H_
#घोषणा _ISHTP_HBM_H_

#समावेश <linux/uuid.h>

काष्ठा ishtp_device;
काष्ठा ishtp_msg_hdr;
काष्ठा ishtp_cl;

/*
 * Timeouts in Seconds
 */
#घोषणा ISHTP_INTEROP_TIMEOUT		7 /* Timeout on पढ़ोy message */

#घोषणा ISHTP_CL_CONNECT_TIMEOUT	15 /* HPS: Client Connect Timeout */

/*
 * ISHTP Version
 */
#घोषणा HBM_MINOR_VERSION		0
#घोषणा HBM_MAJOR_VERSION		1

/* Host bus message command opcode */
#घोषणा ISHTP_HBM_CMD_OP_MSK		0x7f
/* Host bus message command RESPONSE */
#घोषणा ISHTP_HBM_CMD_RES_MSK		0x80

/*
 * ISHTP Bus Message Command IDs
 */
#घोषणा HOST_START_REQ_CMD		0x01
#घोषणा HOST_START_RES_CMD		0x81

#घोषणा HOST_STOP_REQ_CMD		0x02
#घोषणा HOST_STOP_RES_CMD		0x82

#घोषणा FW_STOP_REQ_CMD			0x03

#घोषणा HOST_ENUM_REQ_CMD		0x04
#घोषणा HOST_ENUM_RES_CMD		0x84

#घोषणा HOST_CLIENT_PROPERTIES_REQ_CMD	0x05
#घोषणा HOST_CLIENT_PROPERTIES_RES_CMD	0x85

#घोषणा CLIENT_CONNECT_REQ_CMD		0x06
#घोषणा CLIENT_CONNECT_RES_CMD		0x86

#घोषणा CLIENT_DISCONNECT_REQ_CMD	0x07
#घोषणा CLIENT_DISCONNECT_RES_CMD	0x87

#घोषणा ISHTP_FLOW_CONTROL_CMD		0x08

#घोषणा DMA_BUFFER_ALLOC_NOTIFY		0x11
#घोषणा DMA_BUFFER_ALLOC_RESPONSE	0x91

#घोषणा DMA_XFER			0x12
#घोषणा DMA_XFER_ACK			0x92

/*
 * ISHTP Stop Reason
 * used by hbm_host_stop_request.reason
 */
#घोषणा	DRIVER_STOP_REQUEST		0x00

/*
 * ISHTP BUS Interface Section
 */
काष्ठा ishtp_msg_hdr अणु
	uपूर्णांक32_t fw_addr:8;
	uपूर्णांक32_t host_addr:8;
	uपूर्णांक32_t length:9;
	uपूर्णांक32_t reserved:6;
	uपूर्णांक32_t msg_complete:1;
पूर्ण __packed;

काष्ठा ishtp_bus_message अणु
	uपूर्णांक8_t hbm_cmd;
	uपूर्णांक8_t data[];
पूर्ण __packed;

/**
 * काष्ठा hbm_cl_cmd - client specअगरic host bus command
 *	CONNECT, DISCONNECT, and FlOW CONTROL
 *
 * @hbm_cmd - bus message command header
 * @fw_addr - address of the fw client
 * @host_addr - address of the client in the driver
 * @data
 */
काष्ठा ishtp_hbm_cl_cmd अणु
	uपूर्णांक8_t hbm_cmd;
	uपूर्णांक8_t fw_addr;
	uपूर्णांक8_t host_addr;
	uपूर्णांक8_t data;
पूर्ण;

काष्ठा hbm_version अणु
	uपूर्णांक8_t minor_version;
	uपूर्णांक8_t major_version;
पूर्ण __packed;

काष्ठा hbm_host_version_request अणु
	uपूर्णांक8_t hbm_cmd;
	uपूर्णांक8_t reserved;
	काष्ठा hbm_version host_version;
पूर्ण __packed;

काष्ठा hbm_host_version_response अणु
	uपूर्णांक8_t hbm_cmd;
	uपूर्णांक8_t host_version_supported;
	काष्ठा hbm_version fw_max_version;
पूर्ण __packed;

काष्ठा hbm_host_stop_request अणु
	uपूर्णांक8_t hbm_cmd;
	uपूर्णांक8_t reason;
	uपूर्णांक8_t reserved[2];
पूर्ण __packed;

काष्ठा hbm_host_stop_response अणु
	uपूर्णांक8_t hbm_cmd;
	uपूर्णांक8_t reserved[3];
पूर्ण __packed;

काष्ठा hbm_host_क्रमागत_request अणु
	uपूर्णांक8_t hbm_cmd;
	uपूर्णांक8_t reserved[3];
पूर्ण __packed;

काष्ठा hbm_host_क्रमागत_response अणु
	uपूर्णांक8_t hbm_cmd;
	uपूर्णांक8_t reserved[3];
	uपूर्णांक8_t valid_addresses[32];
पूर्ण __packed;

काष्ठा ishtp_client_properties अणु
	guid_t protocol_name;
	uपूर्णांक8_t protocol_version;
	uपूर्णांक8_t max_number_of_connections;
	uपूर्णांक8_t fixed_address;
	uपूर्णांक8_t single_recv_buf;
	uपूर्णांक32_t max_msg_length;
	uपूर्णांक8_t dma_hdr_len;
#घोषणा	ISHTP_CLIENT_DMA_ENABLED	0x80
	uपूर्णांक8_t reserved4;
	uपूर्णांक8_t reserved5;
	uपूर्णांक8_t reserved6;
पूर्ण __packed;

काष्ठा hbm_props_request अणु
	uपूर्णांक8_t hbm_cmd;
	uपूर्णांक8_t address;
	uपूर्णांक8_t reserved[2];
पूर्ण __packed;

काष्ठा hbm_props_response अणु
	uपूर्णांक8_t hbm_cmd;
	uपूर्णांक8_t address;
	uपूर्णांक8_t status;
	uपूर्णांक8_t reserved[1];
	काष्ठा ishtp_client_properties client_properties;
पूर्ण __packed;

/**
 * काष्ठा hbm_client_connect_request - connect/disconnect request
 *
 * @hbm_cmd - bus message command header
 * @fw_addr - address of the fw client
 * @host_addr - address of the client in the driver
 * @reserved
 */
काष्ठा hbm_client_connect_request अणु
	uपूर्णांक8_t hbm_cmd;
	uपूर्णांक8_t fw_addr;
	uपूर्णांक8_t host_addr;
	uपूर्णांक8_t reserved;
पूर्ण __packed;

/**
 * काष्ठा hbm_client_connect_response - connect/disconnect response
 *
 * @hbm_cmd - bus message command header
 * @fw_addr - address of the fw client
 * @host_addr - address of the client in the driver
 * @status - status of the request
 */
काष्ठा hbm_client_connect_response अणु
	uपूर्णांक8_t hbm_cmd;
	uपूर्णांक8_t fw_addr;
	uपूर्णांक8_t host_addr;
	uपूर्णांक8_t status;
पूर्ण __packed;


#घोषणा ISHTP_FC_MESSAGE_RESERVED_LENGTH		5

काष्ठा hbm_flow_control अणु
	uपूर्णांक8_t hbm_cmd;
	uपूर्णांक8_t fw_addr;
	uपूर्णांक8_t host_addr;
	uपूर्णांक8_t reserved[ISHTP_FC_MESSAGE_RESERVED_LENGTH];
पूर्ण __packed;

काष्ठा dma_alloc_notअगरy अणु
	uपूर्णांक8_t hbm;
	uपूर्णांक8_t status;
	uपूर्णांक8_t reserved[2];
	uपूर्णांक32_t buf_size;
	uपूर्णांक64_t buf_address;
	/* [...] May come more size/address pairs */
पूर्ण __packed;

काष्ठा dma_xfer_hbm अणु
	uपूर्णांक8_t hbm;
	uपूर्णांक8_t fw_client_id;
	uपूर्णांक8_t host_client_id;
	uपूर्णांक8_t reserved;
	uपूर्णांक64_t msg_addr;
	uपूर्णांक32_t msg_length;
	uपूर्णांक32_t reserved2;
पूर्ण __packed;

/* System state */
#घोषणा ISHTP_SYSTEM_STATE_CLIENT_ADDR		13

#घोषणा SYSTEM_STATE_SUBSCRIBE			0x1
#घोषणा SYSTEM_STATE_STATUS			0x2
#घोषणा SYSTEM_STATE_QUERY_SUBSCRIBERS		0x3
#घोषणा SYSTEM_STATE_STATE_CHANGE_REQ		0x4
/*indicates suspend and resume states*/
#घोषणा SUSPEND_STATE_BIT			(1<<1)

काष्ठा ish_प्रणाली_states_header अणु
	uपूर्णांक32_t cmd;
	uपूर्णांक32_t cmd_status;	/*responses will have this set*/
पूर्ण __packed;

काष्ठा ish_प्रणाली_states_subscribe अणु
	काष्ठा ish_प्रणाली_states_header hdr;
	uपूर्णांक32_t states;
पूर्ण __packed;

काष्ठा ish_प्रणाली_states_status अणु
	काष्ठा ish_प्रणाली_states_header hdr;
	uपूर्णांक32_t supported_states;
	uपूर्णांक32_t states_status;
पूर्ण __packed;

काष्ठा ish_प्रणाली_states_query_subscribers अणु
	काष्ठा ish_प्रणाली_states_header hdr;
पूर्ण __packed;

काष्ठा ish_प्रणाली_states_state_change_req अणु
	काष्ठा ish_प्रणाली_states_header hdr;
	uपूर्णांक32_t requested_states;
	uपूर्णांक32_t states_status;
पूर्ण __packed;

/**
 * क्रमागत ishtp_hbm_state - host bus message protocol state
 *
 * @ISHTP_HBM_IDLE : protocol not started
 * @ISHTP_HBM_START : start request message was sent
 * @ISHTP_HBM_ENUM_CLIENTS : क्रमागतeration request was sent
 * @ISHTP_HBM_CLIENT_PROPERTIES : acquiring clients properties
 */
क्रमागत ishtp_hbm_state अणु
	ISHTP_HBM_IDLE = 0,
	ISHTP_HBM_START,
	ISHTP_HBM_STARTED,
	ISHTP_HBM_ENUM_CLIENTS,
	ISHTP_HBM_CLIENT_PROPERTIES,
	ISHTP_HBM_WORKING,
	ISHTP_HBM_STOPPED,
पूर्ण;

अटल अंतरभूत व्योम ishtp_hbm_hdr(काष्ठा ishtp_msg_hdr *hdr, माप_प्रकार length)
अणु
	hdr->host_addr = 0;
	hdr->fw_addr = 0;
	hdr->length = length;
	hdr->msg_complete = 1;
	hdr->reserved = 0;
पूर्ण

पूर्णांक ishtp_hbm_start_req(काष्ठा ishtp_device *dev);
पूर्णांक ishtp_hbm_start_रुको(काष्ठा ishtp_device *dev);
पूर्णांक ishtp_hbm_cl_flow_control_req(काष्ठा ishtp_device *dev,
				  काष्ठा ishtp_cl *cl);
पूर्णांक ishtp_hbm_cl_disconnect_req(काष्ठा ishtp_device *dev, काष्ठा ishtp_cl *cl);
पूर्णांक ishtp_hbm_cl_connect_req(काष्ठा ishtp_device *dev, काष्ठा ishtp_cl *cl);
व्योम ishtp_hbm_क्रमागत_clients_req(काष्ठा ishtp_device *dev);
व्योम bh_hbm_work_fn(काष्ठा work_काष्ठा *work);
व्योम recv_hbm(काष्ठा ishtp_device *dev, काष्ठा ishtp_msg_hdr *ishtp_hdr);
व्योम recv_fixed_cl_msg(काष्ठा ishtp_device *dev,
	काष्ठा ishtp_msg_hdr *ishtp_hdr);
व्योम ishtp_hbm_dispatch(काष्ठा ishtp_device *dev,
	काष्ठा ishtp_bus_message *hdr);

व्योम ishtp_query_subscribers(काष्ठा ishtp_device *dev);

/* Exported I/F */
व्योम ishtp_send_suspend(काष्ठा ishtp_device *dev);
व्योम ishtp_send_resume(काष्ठा ishtp_device *dev);

#पूर्ण_अगर /* _ISHTP_HBM_H_ */
