<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) ST-Ericsson AB 2010
 * Author:	Sjur Brendeland
 */

#अगर_अघोषित CAIF_LAYER_H_
#घोषणा CAIF_LAYER_H_

#समावेश <linux/list.h>

काष्ठा cflayer;
काष्ठा cfpkt;
काष्ठा cfpktq;
काष्ठा caअगर_payload_info;
काष्ठा caअगर_packet_funcs;

#घोषणा CAIF_LAYER_NAME_SZ 16

/**
 * caअगर_निश्चित() - Assert function क्रम CAIF.
 * @निश्चित: expression to evaluate.
 *
 * This function will prपूर्णांक a error message and a करो WARN_ON अगर the
 * निश्चितion failes. Normally this will करो a stack up at the current location.
 */
#घोषणा caअगर_निश्चित(निश्चित)					\
करो अणु								\
	अगर (!(निश्चित)) अणु					\
		pr_err("caif:Assert detected:'%s'\n", #निश्चित); \
		WARN_ON(!(निश्चित));				\
	पूर्ण							\
पूर्ण जबतक (0)

/**
 * क्रमागत caअगर_ctrlcmd - CAIF Stack Control Signaling sent in layer.ctrlcmd().
 *
 * @CAIF_CTRLCMD_FLOW_OFF_IND:		Flow Control is OFF, transmit function
 *					should stop sending data
 *
 * @CAIF_CTRLCMD_FLOW_ON_IND:		Flow Control is ON, transmit function
 *					can start sending data
 *
 * @CAIF_CTRLCMD_REMOTE_SHUTDOWN_IND:	Remote end modem has decided to बंद
 *					करोwn channel
 *
 * @CAIF_CTRLCMD_INIT_RSP:		Called initially when the layer below
 *					has finished initialization
 *
 * @CAIF_CTRLCMD_DEINIT_RSP:		Called when de-initialization is
 *					complete
 *
 * @CAIF_CTRLCMD_INIT_FAIL_RSP:		Called अगर initialization fails
 *
 * @_CAIF_CTRLCMD_PHYIF_FLOW_OFF_IND:	CAIF Link layer temporarily cannot
 *					send more packets.
 * @_CAIF_CTRLCMD_PHYIF_FLOW_ON_IND:	Called अगर CAIF Link layer is able
 *					to send packets again.
 * @_CAIF_CTRLCMD_PHYIF_DOWN_IND:	Called अगर CAIF Link layer is going
 *					करोwn.
 *
 * These commands are sent upwards in the CAIF stack to the CAIF Client.
 * They are used क्रम संकेतing originating from the modem or CAIF Link Layer.
 * These are either responses (*_RSP) or events (*_IND).
 */
क्रमागत caअगर_ctrlcmd अणु
	CAIF_CTRLCMD_FLOW_OFF_IND,
	CAIF_CTRLCMD_FLOW_ON_IND,
	CAIF_CTRLCMD_REMOTE_SHUTDOWN_IND,
	CAIF_CTRLCMD_INIT_RSP,
	CAIF_CTRLCMD_DEINIT_RSP,
	CAIF_CTRLCMD_INIT_FAIL_RSP,
	_CAIF_CTRLCMD_PHYIF_FLOW_OFF_IND,
	_CAIF_CTRLCMD_PHYIF_FLOW_ON_IND,
	_CAIF_CTRLCMD_PHYIF_DOWN_IND,
पूर्ण;

/**
 * क्रमागत caअगर_modemcmd -	 Modem Control Signaling, sent from CAIF Client
 *			 to the CAIF Link Layer or modem.
 *
 * @CAIF_MODEMCMD_FLOW_ON_REQ:		Flow Control is ON, transmit function
 *					can start sending data.
 *
 * @CAIF_MODEMCMD_FLOW_OFF_REQ:		Flow Control is OFF, transmit function
 *					should stop sending data.
 *
 * @_CAIF_MODEMCMD_PHYIF_USEFULL:	Notअगरy physical layer that it is in use
 *
 * @_CAIF_MODEMCMD_PHYIF_USELESS:	Notअगरy physical layer that it is
 *					no दीर्घer in use.
 *
 * These are requests sent 'downwards' in the stack.
 * Flow ON, OFF can be indicated to the modem.
 */
क्रमागत caअगर_modemcmd अणु
	CAIF_MODEMCMD_FLOW_ON_REQ = 0,
	CAIF_MODEMCMD_FLOW_OFF_REQ = 1,
	_CAIF_MODEMCMD_PHYIF_USEFULL = 3,
	_CAIF_MODEMCMD_PHYIF_USELESS = 4
पूर्ण;

/**
 * क्रमागत caअगर_direction - CAIF Packet Direction.
 * Indicate अगर a packet is to be sent out or to be received in.
 * @CAIF_सूची_IN:		Incoming packet received.
 * @CAIF_सूची_OUT:		Outgoing packet to be transmitted.
 */
क्रमागत caअगर_direction अणु
	CAIF_सूची_IN = 0,
	CAIF_सूची_OUT = 1
पूर्ण;

/**
 * काष्ठा cflayer - CAIF Stack layer.
 * Defines the framework क्रम the CAIF Core Stack.
 * @up:		Poपूर्णांकer up to the layer above.
 * @dn:		Poपूर्णांकer करोwn to the layer below.
 * @node:	List node used when layer participate in a list.
 * @receive:	Packet receive function.
 * @transmit:	Packet transmit funciton.
 * @ctrlcmd:	Used क्रम control संकेतling upwards in the stack.
 * @modemcmd:	Used क्रम control संकेतing करोwnwards in the stack.
 * @id:		The identity of this layer
 * @name:	Name of the layer.
 *
 *  This काष्ठाure defines the layered काष्ठाure in CAIF.
 *
 *  It defines CAIF layering काष्ठाure, used by all CAIF Layers and the
 *  layers पूर्णांकerfacing CAIF.
 *
 *  In order to पूर्णांकegrate with CAIF an adaptation layer on top of the CAIF stack
 *  and PHY layer below the CAIF stack
 *  must be implemented. These layer must follow the design principles below.
 *
 *  Principles क्रम layering of protocol layers:
 *    - All layers must use this काष्ठाure. If embedding it, then place this
 *	काष्ठाure first in the layer specअगरic काष्ठाure.
 *
 *    - Each layer should not depend on any others layer's निजी data.
 *
 *    - In order to send data upwards करो
 *	layer->up->receive(layer->up, packet);
 *
 *    - In order to send data करोwnwards करो
 *	layer->dn->transmit(layer->dn, info, packet);
 */
काष्ठा cflayer अणु
	काष्ठा cflayer *up;
	काष्ठा cflayer *dn;
	काष्ठा list_head node;

	/*
	 *  receive() - Receive Function (non-blocking).
	 *  Contract: Each layer must implement a receive function passing the
	 *  CAIF packets upwards in the stack.
	 *	Packet handling rules:
	 *	      - The CAIF packet (cfpkt) ownership is passed to the
	 *		called receive function. This means that the
	 *		packet cannot be accessed after passing it to the
	 *		above layer using up->receive().
	 *
	 *	      - If parsing of the packet fails, the packet must be
	 *		destroyed and negative error code वापसed
	 *		from the function.
	 *		EXCEPTION: If the framing layer (cffrml) वापसs
	 *			-EILSEQ, the packet is not मुक्तd.
	 *
	 *	      - If parsing succeeds (and above layers वापस OK) then
	 *		      the function must वापस a value >= 0.
	 *
	 *  Returns result < 0 indicates an error, 0 or positive value
	 *	     indicates success.
	 *
	 *  @layr: Poपूर्णांकer to the current layer the receive function is
	 *		implemented क्रम (this poपूर्णांकer).
	 *  @cfpkt: Poपूर्णांकer to CaअगरPacket to be handled.
	 */
	पूर्णांक (*receive)(काष्ठा cflayer *layr, काष्ठा cfpkt *cfpkt);

	/*
	 *  transmit() - Transmit Function (non-blocking).
	 *  Contract: Each layer must implement a transmit function passing the
	 *	CAIF packet करोwnwards in the stack.
	 *	Packet handling rules:
	 *	      - The CAIF packet (cfpkt) ownership is passed to the
	 *		transmit function. This means that the packet
	 *		cannot be accessed after passing it to the below
	 *		layer using dn->transmit().
	 *
	 *	      - Upon error the packet ownership is still passed on,
	 *		so the packet shall be मुक्तd where error is detected.
	 *		Callers of the transmit function shall not मुक्त packets,
	 *		but errors shall be वापसed.
	 *
	 *	      - Return value less than zero means error, zero or
	 *		greater than zero means OK.
	 *
	 *  Returns result < 0 indicates an error, 0 or positive value
	 *		indicates success.
	 *
	 *  @layr:	Poपूर्णांकer to the current layer the receive function
	 *		isimplemented क्रम (this poपूर्णांकer).
	 *  @cfpkt:	 Poपूर्णांकer to CaअगरPacket to be handled.
	 */
	पूर्णांक (*transmit) (काष्ठा cflayer *layr, काष्ठा cfpkt *cfpkt);

	/*
	 *  cttrlcmd() - Control Function upwards in CAIF Stack  (non-blocking).
	 *  Used क्रम संकेतing responses (CAIF_CTRLCMD_*_RSP)
	 *  and asynchronous events from the modem  (CAIF_CTRLCMD_*_IND)
	 *
	 *  @layr:	Poपूर्णांकer to the current layer the receive function
	 *		is implemented क्रम (this poपूर्णांकer).
	 *  @ctrl:	Control Command.
	 */
	व्योम (*ctrlcmd) (काष्ठा cflayer *layr, क्रमागत caअगर_ctrlcmd ctrl,
			 पूर्णांक phyid);

	/*
	 *  modemctrl() - Control Function used क्रम controlling the modem.
	 *  Used to संकेत करोwn-wards in the CAIF stack.
	 *  Returns 0 on success, < 0 upon failure.
	 *
	 *  @layr:	Poपूर्णांकer to the current layer the receive function
	 *		is implemented क्रम (this poपूर्णांकer).
	 *  @ctrl:  Control Command.
	 */
	पूर्णांक (*modemcmd) (काष्ठा cflayer *layr, क्रमागत caअगर_modemcmd ctrl);

	अचिन्हित पूर्णांक id;
	अक्षर name[CAIF_LAYER_NAME_SZ];
पूर्ण;

/**
 * layer_set_up() - Set the up poपूर्णांकer क्रम a specअगरied layer.
 *  @layr: Layer where up poपूर्णांकer shall be set.
 *  @above: Layer above.
 */
#घोषणा layer_set_up(layr, above) ((layr)->up = (काष्ठा cflayer *)(above))

/**
 *  layer_set_dn() - Set the करोwn poपूर्णांकer क्रम a specअगरied layer.
 *  @layr:  Layer where करोwn poपूर्णांकer shall be set.
 *  @below: Layer below.
 */
#घोषणा layer_set_dn(layr, below) ((layr)->dn = (काष्ठा cflayer *)(below))

/**
 * काष्ठा dev_info - Physical Device info inक्रमmation about physical layer.
 * @dev:	Poपूर्णांकer to native physical device.
 * @id:		Physical ID of the physical connection used by the
 *		logical CAIF connection. Used by service layers to
 *		identअगरy their physical id to Caअगर MUX (CFMUXL)so
 *		that the MUX can add the correct physical ID to the
 *		packet.
 */
काष्ठा dev_info अणु
	व्योम *dev;
	अचिन्हित पूर्णांक id;
पूर्ण;

/**
 * काष्ठा caअगर_payload_info - Payload inक्रमmation embedded in packet (sk_buff).
 *
 * @dev_info:	Inक्रमmation about the receiving device.
 *
 * @hdr_len:	Header length, used to align pay load on 32bit boundary.
 *
 * @channel_id: Channel ID of the logical CAIF connection.
 *		Used by mux to insert channel id पूर्णांकo the caअगर packet.
 */
काष्ठा caअगर_payload_info अणु
	काष्ठा dev_info *dev_info;
	अचिन्हित लघु hdr_len;
	अचिन्हित लघु channel_id;
पूर्ण;

#पूर्ण_अगर	/* CAIF_LAYER_H_ */
