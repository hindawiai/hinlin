<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * RNDIS	Definitions क्रम Remote NDIS
 *
 * Authors:	Benedikt Spranger, Pengutronix
 *		Robert Schwebel, Pengutronix
 *
 *		This software was originally developed in conक्रमmance with
 *		Microsoft's Remote NDIS Specअगरication License Agreement.
 */

#अगर_अघोषित _LINUX_RNDIS_H
#घोषणा _LINUX_RNDIS_H

#समावेश <linux/rndis.h>
#समावेश "u_ether.h"
#समावेश "ndis.h"

#घोषणा RNDIS_MAXIMUM_FRAME_SIZE	1518
#घोषणा RNDIS_MAX_TOTAL_SIZE		1558

प्रकार काष्ठा rndis_init_msg_type अणु
	__le32	MessageType;
	__le32	MessageLength;
	__le32	RequestID;
	__le32	MajorVersion;
	__le32	MinorVersion;
	__le32	MaxTransferSize;
पूर्ण rndis_init_msg_type;

प्रकार काष्ठा rndis_init_cmplt_type अणु
	__le32	MessageType;
	__le32	MessageLength;
	__le32	RequestID;
	__le32	Status;
	__le32	MajorVersion;
	__le32	MinorVersion;
	__le32	DeviceFlags;
	__le32	Medium;
	__le32	MaxPacketsPerTransfer;
	__le32	MaxTransferSize;
	__le32	PacketAlignmentFactor;
	__le32	AFListOffset;
	__le32	AFListSize;
पूर्ण rndis_init_cmplt_type;

प्रकार काष्ठा rndis_halt_msg_type अणु
	__le32	MessageType;
	__le32	MessageLength;
	__le32	RequestID;
पूर्ण rndis_halt_msg_type;

प्रकार काष्ठा rndis_query_msg_type अणु
	__le32	MessageType;
	__le32	MessageLength;
	__le32	RequestID;
	__le32	OID;
	__le32	Inक्रमmationBufferLength;
	__le32	Inक्रमmationBufferOffset;
	__le32	DeviceVcHandle;
पूर्ण rndis_query_msg_type;

प्रकार काष्ठा rndis_query_cmplt_type अणु
	__le32	MessageType;
	__le32	MessageLength;
	__le32	RequestID;
	__le32	Status;
	__le32	Inक्रमmationBufferLength;
	__le32	Inक्रमmationBufferOffset;
पूर्ण rndis_query_cmplt_type;

प्रकार काष्ठा rndis_set_msg_type अणु
	__le32	MessageType;
	__le32	MessageLength;
	__le32	RequestID;
	__le32	OID;
	__le32	Inक्रमmationBufferLength;
	__le32	Inक्रमmationBufferOffset;
	__le32	DeviceVcHandle;
पूर्ण rndis_set_msg_type;

प्रकार काष्ठा rndis_set_cmplt_type अणु
	__le32	MessageType;
	__le32	MessageLength;
	__le32	RequestID;
	__le32	Status;
पूर्ण rndis_set_cmplt_type;

प्रकार काष्ठा rndis_reset_msg_type अणु
	__le32	MessageType;
	__le32	MessageLength;
	__le32	Reserved;
पूर्ण rndis_reset_msg_type;

प्रकार काष्ठा rndis_reset_cmplt_type अणु
	__le32	MessageType;
	__le32	MessageLength;
	__le32	Status;
	__le32	AddressingReset;
पूर्ण rndis_reset_cmplt_type;

प्रकार काष्ठा rndis_indicate_status_msg_type अणु
	__le32	MessageType;
	__le32	MessageLength;
	__le32	Status;
	__le32	StatusBufferLength;
	__le32	StatusBufferOffset;
पूर्ण rndis_indicate_status_msg_type;

प्रकार काष्ठा rndis_keepalive_msg_type अणु
	__le32	MessageType;
	__le32	MessageLength;
	__le32	RequestID;
पूर्ण rndis_keepalive_msg_type;

प्रकार काष्ठा rndis_keepalive_cmplt_type अणु
	__le32	MessageType;
	__le32	MessageLength;
	__le32	RequestID;
	__le32	Status;
पूर्ण rndis_keepalive_cmplt_type;

काष्ठा rndis_packet_msg_type अणु
	__le32	MessageType;
	__le32	MessageLength;
	__le32	DataOffset;
	__le32	DataLength;
	__le32	OOBDataOffset;
	__le32	OOBDataLength;
	__le32	NumOOBDataElements;
	__le32	PerPacketInfoOffset;
	__le32	PerPacketInfoLength;
	__le32	VcHandle;
	__le32	Reserved;
पूर्ण __attribute__ ((packed));

काष्ठा rndis_config_parameter अणु
	__le32	ParameterNameOffset;
	__le32	ParameterNameLength;
	__le32	ParameterType;
	__le32	ParameterValueOffset;
	__le32	ParameterValueLength;
पूर्ण;

/* implementation specअगरic */
क्रमागत rndis_state अणु
	RNDIS_UNINITIALIZED,
	RNDIS_INITIALIZED,
	RNDIS_DATA_INITIALIZED,
पूर्ण;

प्रकार काष्ठा rndis_resp_t अणु
	काष्ठा list_head	list;
	u8			*buf;
	u32			length;
	पूर्णांक			send;
पूर्ण rndis_resp_t;

प्रकार काष्ठा rndis_params अणु
	पूर्णांक			confignr;
	u8			used;
	u16			saved_filter;
	क्रमागत rndis_state	state;
	u32			medium;
	u32			speed;
	u32			media_state;

	स्थिर u8		*host_mac;
	u16			*filter;
	काष्ठा net_device	*dev;

	u32			venकरोrID;
	स्थिर अक्षर		*venकरोrDescr;
	व्योम			(*resp_avail)(व्योम *v);
	व्योम			*v;
	काष्ठा list_head	resp_queue;
पूर्ण rndis_params;

/* RNDIS Message parser and other useless functions */
पूर्णांक  rndis_msg_parser(काष्ठा rndis_params *params, u8 *buf);
काष्ठा rndis_params *rndis_रेजिस्टर(व्योम (*resp_avail)(व्योम *v), व्योम *v);
व्योम rndis_deरेजिस्टर(काष्ठा rndis_params *params);
पूर्णांक  rndis_set_param_dev(काष्ठा rndis_params *params, काष्ठा net_device *dev,
			 u16 *cdc_filter);
पूर्णांक  rndis_set_param_venकरोr(काष्ठा rndis_params *params, u32 venकरोrID,
			    स्थिर अक्षर *venकरोrDescr);
पूर्णांक  rndis_set_param_medium(काष्ठा rndis_params *params, u32 medium,
			     u32 speed);
व्योम rndis_add_hdr(काष्ठा sk_buff *skb);
पूर्णांक rndis_rm_hdr(काष्ठा gether *port, काष्ठा sk_buff *skb,
			काष्ठा sk_buff_head *list);
u8   *rndis_get_next_response(काष्ठा rndis_params *params, u32 *length);
व्योम rndis_मुक्त_response(काष्ठा rndis_params *params, u8 *buf);

व्योम rndis_uninit(काष्ठा rndis_params *params);
पूर्णांक  rndis_संकेत_connect(काष्ठा rndis_params *params);
पूर्णांक  rndis_संकेत_disconnect(काष्ठा rndis_params *params);
पूर्णांक  rndis_state(काष्ठा rndis_params *params);
बाह्य व्योम rndis_set_host_mac(काष्ठा rndis_params *params, स्थिर u8 *addr);

#पूर्ण_अगर  /* _LINUX_RNDIS_H */
