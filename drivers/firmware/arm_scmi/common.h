<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * System Control and Management Interface (SCMI) Message Protocol
 * driver common header file containing some definitions, काष्ठाures
 * and function prototypes used in all the dअगरferent SCMI protocols.
 *
 * Copyright (C) 2018-2021 ARM Ltd.
 */
#अगर_अघोषित _SCMI_COMMON_H
#घोषणा _SCMI_COMMON_H

#समावेश <linux/bitfield.h>
#समावेश <linux/completion.h>
#समावेश <linux/device.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/scmi_protocol.h>
#समावेश <linux/types.h>

#समावेश <यंत्र/unaligned.h>

#समावेश "notify.h"

#घोषणा PROTOCOL_REV_MINOR_MASK	GENMASK(15, 0)
#घोषणा PROTOCOL_REV_MAJOR_MASK	GENMASK(31, 16)
#घोषणा PROTOCOL_REV_MAJOR(x)	(u16)(FIELD_GET(PROTOCOL_REV_MAJOR_MASK, (x)))
#घोषणा PROTOCOL_REV_MINOR(x)	(u16)(FIELD_GET(PROTOCOL_REV_MINOR_MASK, (x)))
#घोषणा MAX_PROTOCOLS_IMP	16
#घोषणा MAX_OPPS		16

क्रमागत scmi_common_cmd अणु
	PROTOCOL_VERSION = 0x0,
	PROTOCOL_ATTRIBUTES = 0x1,
	PROTOCOL_MESSAGE_ATTRIBUTES = 0x2,
पूर्ण;

/**
 * काष्ठा scmi_msg_resp_prot_version - Response क्रम a message
 *
 * @minor_version: Minor version of the ABI that firmware supports
 * @major_version: Major version of the ABI that firmware supports
 *
 * In general, ABI version changes follow the rule that minor version increments
 * are backward compatible. Major revision changes in ABI may not be
 * backward compatible.
 *
 * Response to a generic message with message type SCMI_MSG_VERSION
 */
काष्ठा scmi_msg_resp_prot_version अणु
	__le16 minor_version;
	__le16 major_version;
पूर्ण;

#घोषणा MSG_ID_MASK		GENMASK(7, 0)
#घोषणा MSG_XTRACT_ID(hdr)	FIELD_GET(MSG_ID_MASK, (hdr))
#घोषणा MSG_TYPE_MASK		GENMASK(9, 8)
#घोषणा MSG_XTRACT_TYPE(hdr)	FIELD_GET(MSG_TYPE_MASK, (hdr))
#घोषणा MSG_TYPE_COMMAND	0
#घोषणा MSG_TYPE_DELAYED_RESP	2
#घोषणा MSG_TYPE_NOTIFICATION	3
#घोषणा MSG_PROTOCOL_ID_MASK	GENMASK(17, 10)
#घोषणा MSG_XTRACT_PROT_ID(hdr)	FIELD_GET(MSG_PROTOCOL_ID_MASK, (hdr))
#घोषणा MSG_TOKEN_ID_MASK	GENMASK(27, 18)
#घोषणा MSG_XTRACT_TOKEN(hdr)	FIELD_GET(MSG_TOKEN_ID_MASK, (hdr))
#घोषणा MSG_TOKEN_MAX		(MSG_XTRACT_TOKEN(MSG_TOKEN_ID_MASK) + 1)

/**
 * काष्ठा scmi_msg_hdr - Message(Tx/Rx) header
 *
 * @id: The identअगरier of the message being sent
 * @protocol_id: The identअगरier of the protocol used to send @id message
 * @seq: The token to identअगरy the message. When a message वापसs, the
 *	platक्रमm वापसs the whole message header unmodअगरied including the
 *	token
 * @status: Status of the transfer once it's complete
 * @poll_completion: Indicate अगर the transfer needs to be polled क्रम
 *	completion or पूर्णांकerrupt mode is used
 */
काष्ठा scmi_msg_hdr अणु
	u8 id;
	u8 protocol_id;
	u16 seq;
	u32 status;
	bool poll_completion;
पूर्ण;

/**
 * pack_scmi_header() - packs and वापसs 32-bit header
 *
 * @hdr: poपूर्णांकer to header containing all the inक्रमmation on message id,
 *	protocol id and sequence id.
 *
 * Return: 32-bit packed message header to be sent to the platक्रमm.
 */
अटल अंतरभूत u32 pack_scmi_header(काष्ठा scmi_msg_hdr *hdr)
अणु
	वापस FIELD_PREP(MSG_ID_MASK, hdr->id) |
		FIELD_PREP(MSG_TOKEN_ID_MASK, hdr->seq) |
		FIELD_PREP(MSG_PROTOCOL_ID_MASK, hdr->protocol_id);
पूर्ण

/**
 * unpack_scmi_header() - unpacks and records message and protocol id
 *
 * @msg_hdr: 32-bit packed message header sent from the platक्रमm
 * @hdr: poपूर्णांकer to header to fetch message and protocol id.
 */
अटल अंतरभूत व्योम unpack_scmi_header(u32 msg_hdr, काष्ठा scmi_msg_hdr *hdr)
अणु
	hdr->id = MSG_XTRACT_ID(msg_hdr);
	hdr->protocol_id = MSG_XTRACT_PROT_ID(msg_hdr);
पूर्ण

/**
 * काष्ठा scmi_msg - Message(Tx/Rx) काष्ठाure
 *
 * @buf: Buffer poपूर्णांकer
 * @len: Length of data in the Buffer
 */
काष्ठा scmi_msg अणु
	व्योम *buf;
	माप_प्रकार len;
पूर्ण;

/**
 * काष्ठा scmi_xfer - Structure representing a message flow
 *
 * @transfer_id: Unique ID क्रम debug & profiling purpose
 * @hdr: Transmit message header
 * @tx: Transmit message
 * @rx: Receive message, the buffer should be pre-allocated to store
 *	message. If request-ACK protocol is used, we can reuse the same
 *	buffer क्रम the rx path as we use क्रम the tx path.
 * @करोne: command message transmit completion event
 * @async_करोne: poपूर्णांकer to delayed response message received event completion
 */
काष्ठा scmi_xfer अणु
	पूर्णांक transfer_id;
	काष्ठा scmi_msg_hdr hdr;
	काष्ठा scmi_msg tx;
	काष्ठा scmi_msg rx;
	काष्ठा completion करोne;
	काष्ठा completion *async_करोne;
पूर्ण;

काष्ठा scmi_xfer_ops;

/**
 * काष्ठा scmi_protocol_handle  - Reference to an initialized protocol instance
 *
 * @dev: A reference to the associated SCMI instance device (handle->dev).
 * @xops: A reference to a काष्ठा holding refs to the core xfer operations that
 *	  can be used by the protocol implementation to generate SCMI messages.
 * @set_priv: A method to set protocol निजी data क्रम this instance.
 * @get_priv: A method to get protocol निजी data previously set.
 *
 * This काष्ठाure represents a protocol initialized against specअगरic SCMI
 * instance and it will be used as follows:
 * - as a parameter fed from the core to the protocol initialization code so
 *   that it can access the core xfer operations to build and generate SCMI
 *   messages exclusively क्रम the specअगरic underlying protocol instance.
 * - as an opaque handle fed by an SCMI driver user when it tries to access
 *   this protocol through its own protocol operations.
 *   In this हाल this handle will be वापसed as an opaque object together
 *   with the related protocol operations when the SCMI driver tries to access
 *   the protocol.
 */
काष्ठा scmi_protocol_handle अणु
	काष्ठा device *dev;
	स्थिर काष्ठा scmi_xfer_ops *xops;
	पूर्णांक (*set_priv)(स्थिर काष्ठा scmi_protocol_handle *ph, व्योम *priv);
	व्योम *(*get_priv)(स्थिर काष्ठा scmi_protocol_handle *ph);
पूर्ण;

/**
 * काष्ठा scmi_xfer_ops  - References to the core SCMI xfer operations.
 * @version_get: Get this version protocol.
 * @xfer_get_init: Initialize one काष्ठा xfer अगर any xfer slot is मुक्त.
 * @reset_rx_to_maxsz: Reset rx size to max transport size.
 * @करो_xfer: Do the SCMI transfer.
 * @करो_xfer_with_response: Do the SCMI transfer रुकोing क्रम a response.
 * @xfer_put: Free the xfer slot.
 *
 * Note that all this operations expect a protocol handle as first parameter;
 * they then पूर्णांकernally use it to infer the underlying protocol number: this
 * way is not possible क्रम a protocol implementation to क्रमge messages क्रम
 * another protocol.
 */
काष्ठा scmi_xfer_ops अणु
	पूर्णांक (*version_get)(स्थिर काष्ठा scmi_protocol_handle *ph, u32 *version);
	पूर्णांक (*xfer_get_init)(स्थिर काष्ठा scmi_protocol_handle *ph, u8 msg_id,
			     माप_प्रकार tx_size, माप_प्रकार rx_size,
			     काष्ठा scmi_xfer **p);
	व्योम (*reset_rx_to_maxsz)(स्थिर काष्ठा scmi_protocol_handle *ph,
				  काष्ठा scmi_xfer *xfer);
	पूर्णांक (*करो_xfer)(स्थिर काष्ठा scmi_protocol_handle *ph,
		       काष्ठा scmi_xfer *xfer);
	पूर्णांक (*करो_xfer_with_response)(स्थिर काष्ठा scmi_protocol_handle *ph,
				     काष्ठा scmi_xfer *xfer);
	व्योम (*xfer_put)(स्थिर काष्ठा scmi_protocol_handle *ph,
			 काष्ठा scmi_xfer *xfer);
पूर्ण;

काष्ठा scmi_revision_info *
scmi_revision_area_get(स्थिर काष्ठा scmi_protocol_handle *ph);
पूर्णांक scmi_handle_put(स्थिर काष्ठा scmi_handle *handle);
काष्ठा scmi_handle *scmi_handle_get(काष्ठा device *dev);
व्योम scmi_set_handle(काष्ठा scmi_device *scmi_dev);
व्योम scmi_setup_protocol_implemented(स्थिर काष्ठा scmi_protocol_handle *ph,
				     u8 *prot_imp);

प्रकार पूर्णांक (*scmi_prot_init_ph_fn_t)(स्थिर काष्ठा scmi_protocol_handle *);

/**
 * काष्ठा scmi_protocol  - Protocol descriptor
 * @id: Protocol ID.
 * @owner: Module reference अगर any.
 * @instance_init: Mandatory protocol initialization function.
 * @instance_deinit: Optional protocol de-initialization function.
 * @ops: Optional reference to the operations provided by the protocol and
 *	 exposed in scmi_protocol.h.
 * @events: An optional reference to the events supported by this protocol.
 */
काष्ठा scmi_protocol अणु
	स्थिर u8				id;
	काष्ठा module				*owner;
	स्थिर scmi_prot_init_ph_fn_t		instance_init;
	स्थिर scmi_prot_init_ph_fn_t		instance_deinit;
	स्थिर व्योम				*ops;
	स्थिर काष्ठा scmi_protocol_events	*events;
पूर्ण;

पूर्णांक __init scmi_bus_init(व्योम);
व्योम __निकास scmi_bus_निकास(व्योम);

#घोषणा DECLARE_SCMI_REGISTER_UNREGISTER(func)		\
	पूर्णांक __init scmi_##func##_रेजिस्टर(व्योम);	\
	व्योम __निकास scmi_##func##_unरेजिस्टर(व्योम)
DECLARE_SCMI_REGISTER_UNREGISTER(base);
DECLARE_SCMI_REGISTER_UNREGISTER(घड़ी);
DECLARE_SCMI_REGISTER_UNREGISTER(perf);
DECLARE_SCMI_REGISTER_UNREGISTER(घातer);
DECLARE_SCMI_REGISTER_UNREGISTER(reset);
DECLARE_SCMI_REGISTER_UNREGISTER(sensors);
DECLARE_SCMI_REGISTER_UNREGISTER(voltage);
DECLARE_SCMI_REGISTER_UNREGISTER(प्रणाली);

#घोषणा DEFINE_SCMI_PROTOCOL_REGISTER_UNREGISTER(name, proto)	\
अटल स्थिर काष्ठा scmi_protocol *__this_proto = &(proto);	\
								\
पूर्णांक __init scmi_##name##_रेजिस्टर(व्योम)				\
अणु								\
	वापस scmi_protocol_रेजिस्टर(__this_proto);		\
पूर्ण								\
								\
व्योम __निकास scmi_##name##_unरेजिस्टर(व्योम)			\
अणु								\
	scmi_protocol_unरेजिस्टर(__this_proto);			\
पूर्ण

स्थिर काष्ठा scmi_protocol *scmi_protocol_get(पूर्णांक protocol_id);
व्योम scmi_protocol_put(पूर्णांक protocol_id);

पूर्णांक scmi_protocol_acquire(स्थिर काष्ठा scmi_handle *handle, u8 protocol_id);
व्योम scmi_protocol_release(स्थिर काष्ठा scmi_handle *handle, u8 protocol_id);

/* SCMI Transport */
/**
 * काष्ठा scmi_chan_info - Structure representing a SCMI channel inक्रमmation
 *
 * @dev: Reference to device in the SCMI hierarchy corresponding to this
 *	 channel
 * @handle: Poपूर्णांकer to SCMI entity handle
 * @transport_info: Transport layer related inक्रमmation
 */
काष्ठा scmi_chan_info अणु
	काष्ठा device *dev;
	काष्ठा scmi_handle *handle;
	व्योम *transport_info;
पूर्ण;

/**
 * काष्ठा scmi_transport_ops - Structure representing a SCMI transport ops
 *
 * @chan_available: Callback to check अगर channel is available or not
 * @chan_setup: Callback to allocate and setup a channel
 * @chan_मुक्त: Callback to मुक्त a channel
 * @send_message: Callback to send a message
 * @mark_txकरोne: Callback to mark tx as करोne
 * @fetch_response: Callback to fetch response
 * @fetch_notअगरication: Callback to fetch notअगरication
 * @clear_channel: Callback to clear a channel
 * @poll_करोne: Callback to poll transfer status
 */
काष्ठा scmi_transport_ops अणु
	bool (*chan_available)(काष्ठा device *dev, पूर्णांक idx);
	पूर्णांक (*chan_setup)(काष्ठा scmi_chan_info *cinfo, काष्ठा device *dev,
			  bool tx);
	पूर्णांक (*chan_मुक्त)(पूर्णांक id, व्योम *p, व्योम *data);
	पूर्णांक (*send_message)(काष्ठा scmi_chan_info *cinfo,
			    काष्ठा scmi_xfer *xfer);
	व्योम (*mark_txकरोne)(काष्ठा scmi_chan_info *cinfo, पूर्णांक ret);
	व्योम (*fetch_response)(काष्ठा scmi_chan_info *cinfo,
			       काष्ठा scmi_xfer *xfer);
	व्योम (*fetch_notअगरication)(काष्ठा scmi_chan_info *cinfo,
				   माप_प्रकार max_len, काष्ठा scmi_xfer *xfer);
	व्योम (*clear_channel)(काष्ठा scmi_chan_info *cinfo);
	bool (*poll_करोne)(काष्ठा scmi_chan_info *cinfo, काष्ठा scmi_xfer *xfer);
पूर्ण;

पूर्णांक scmi_protocol_device_request(स्थिर काष्ठा scmi_device_id *id_table);
व्योम scmi_protocol_device_unrequest(स्थिर काष्ठा scmi_device_id *id_table);
काष्ठा scmi_device *scmi_child_dev_find(काष्ठा device *parent,
					पूर्णांक prot_id, स्थिर अक्षर *name);

/**
 * काष्ठा scmi_desc - Description of SoC पूर्णांकegration
 *
 * @ops: Poपूर्णांकer to the transport specअगरic ops काष्ठाure
 * @max_rx_समयout_ms: Timeout क्रम communication with SoC (in Milliseconds)
 * @max_msg: Maximum number of messages that can be pending
 *	simultaneously in the प्रणाली
 * @max_msg_size: Maximum size of data per message that can be handled.
 */
काष्ठा scmi_desc अणु
	स्थिर काष्ठा scmi_transport_ops *ops;
	पूर्णांक max_rx_समयout_ms;
	पूर्णांक max_msg;
	पूर्णांक max_msg_size;
पूर्ण;

बाह्य स्थिर काष्ठा scmi_desc scmi_mailbox_desc;
#अगर_घोषित CONFIG_HAVE_ARM_SMCCC
बाह्य स्थिर काष्ठा scmi_desc scmi_smc_desc;
#पूर्ण_अगर

व्योम scmi_rx_callback(काष्ठा scmi_chan_info *cinfo, u32 msg_hdr);
व्योम scmi_मुक्त_channel(काष्ठा scmi_chan_info *cinfo, काष्ठा idr *idr, पूर्णांक id);

/* shmem related declarations */
काष्ठा scmi_shared_mem;

व्योम shmem_tx_prepare(काष्ठा scmi_shared_mem __iomem *shmem,
		      काष्ठा scmi_xfer *xfer);
u32 shmem_पढ़ो_header(काष्ठा scmi_shared_mem __iomem *shmem);
व्योम shmem_fetch_response(काष्ठा scmi_shared_mem __iomem *shmem,
			  काष्ठा scmi_xfer *xfer);
व्योम shmem_fetch_notअगरication(काष्ठा scmi_shared_mem __iomem *shmem,
			      माप_प्रकार max_len, काष्ठा scmi_xfer *xfer);
व्योम shmem_clear_channel(काष्ठा scmi_shared_mem __iomem *shmem);
bool shmem_poll_करोne(काष्ठा scmi_shared_mem __iomem *shmem,
		     काष्ठा scmi_xfer *xfer);

व्योम scmi_notअगरication_instance_data_set(स्थिर काष्ठा scmi_handle *handle,
					 व्योम *priv);
व्योम *scmi_notअगरication_instance_data_get(स्थिर काष्ठा scmi_handle *handle);

#पूर्ण_अगर /* _SCMI_COMMON_H */
