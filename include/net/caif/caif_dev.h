<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) ST-Ericsson AB 2010
 * Author:	Sjur Brendeland
 */

#अगर_अघोषित CAIF_DEV_H_
#घोषणा CAIF_DEV_H_

#समावेश <net/caअगर/caअगर_layer.h>
#समावेश <net/caअगर/cfcnfg.h>
#समावेश <net/caअगर/caअगर_device.h>
#समावेश <linux/caअगर/caअगर_socket.h>
#समावेश <linux/अगर.h>
#समावेश <linux/net.h>

/**
 * काष्ठा caअगर_param - CAIF parameters.
 * @size:	Length of data
 * @data:	Binary Data Blob
 */
काष्ठा caअगर_param अणु
	u16  size;
	u8   data[256];
पूर्ण;

/**
 * काष्ठा caअगर_connect_request - Request data क्रम CAIF channel setup.
 * @protocol:		Type of CAIF protocol to use (at, datagram etc)
 * @sockaddr:		Socket address to connect.
 * @priority:		Priority of the connection.
 * @link_selector:	Link selector (high bandwidth or low latency)
 * @अगरindex:		kernel index of the पूर्णांकerface.
 * @param:		Connect Request parameters (CAIF_SO_REQ_PARAM).
 *
 * This काष्ठा is used when connecting a CAIF channel.
 * It contains all CAIF channel configuration options.
 */
काष्ठा caअगर_connect_request अणु
	क्रमागत caअगर_protocol_type protocol;
	काष्ठा sockaddr_caअगर sockaddr;
	क्रमागत caअगर_channel_priority priority;
	क्रमागत caअगर_link_selector link_selector;
	पूर्णांक अगरindex;
	काष्ठा caअगर_param param;
पूर्ण;

/**
 * caअगर_connect_client - Connect a client to CAIF Core Stack.
 * @config:		Channel setup parameters, specअगरying what address
 *			to connect on the Modem.
 * @client_layer:	User implementation of client layer. This layer
 *			MUST have receive and control callback functions
 *			implemented.
 * @अगरindex:		Link layer पूर्णांकerface index used क्रम this connection.
 * @headroom:		Head room needed by CAIF protocol.
 * @tailroom:		Tail room needed by CAIF protocol.
 *
 * This function connects a CAIF channel. The Client must implement
 * the काष्ठा cflayer. This layer represents the Client layer and holds
 * receive functions and control callback functions. Control callback
 * function will receive inक्रमmation about connect/disconnect responses,
 * flow control etc (see क्रमागत caअगर_control).
 * E.g. CAIF Socket will call this function क्रम each socket it connects
 * and have one client_layer instance क्रम each socket.
 */
पूर्णांक caअगर_connect_client(काष्ठा net *net,
			काष्ठा caअगर_connect_request *conn_req,
			काष्ठा cflayer *client_layer, पूर्णांक *अगरindex,
			पूर्णांक *headroom, पूर्णांक *tailroom);

/**
 * caअगर_disconnect_client - Disconnects a client from the CAIF stack.
 *
 * @client_layer: Client layer to be disconnected.
 */
पूर्णांक caअगर_disconnect_client(काष्ठा net *net, काष्ठा cflayer *client_layer);


/**
 * caअगर_client_रेजिस्टर_refcnt - रेजिस्टर ref-count functions provided by client.
 *
 * @adapt_layer: Client layer using CAIF Stack.
 * @hold:	Function provided by client layer increasing ref-count
 * @put:	Function provided by client layer decreasing ref-count
 *
 * Client of the CAIF Stack must रेजिस्टर functions क्रम reference counting.
 * These functions are called by the CAIF Stack क्रम every upstream packet,
 * and must thereक्रमe be implemented efficiently.
 *
 * Client should call caअगर_मुक्त_client when reference count degrease to zero.
 */

व्योम caअगर_client_रेजिस्टर_refcnt(काष्ठा cflayer *adapt_layer,
					व्योम (*hold)(काष्ठा cflayer *lyr),
					व्योम (*put)(काष्ठा cflayer *lyr));
/**
 * caअगर_मुक्त_client - Free memory used to manage the client in the CAIF Stack.
 *
 * @client_layer: Client layer to be हटाओd.
 *
 * This function must be called from client layer in order to मुक्त memory.
 * Caller must guarantee that no packets are in flight upstream when calling
 * this function.
 */
व्योम caअगर_मुक्त_client(काष्ठा cflayer *adap_layer);

/**
 * काष्ठा caअगर_enroll_dev - Enroll a net-device as a CAIF Link layer
 * @dev:		Network device to enroll.
 * @caअगरdev:		Configuration inक्रमmation from CAIF Link Layer
 * @link_support:	Link layer support layer
 * @head_room:		Head room needed by link support layer
 * @layer:		Lowest layer in CAIF stack
 * @rcv_fun:		Receive function क्रम CAIF stack.
 *
 * This function enroll a CAIF link layer पूर्णांकo CAIF Stack and
 * expects the पूर्णांकerface to be able to handle CAIF payload.
 * The link_support layer is used to add any Link Layer specअगरic
 * framing.
 */
पूर्णांक caअगर_enroll_dev(काष्ठा net_device *dev, काष्ठा caअगर_dev_common *caअगरdev,
			काष्ठा cflayer *link_support, पूर्णांक head_room,
			काष्ठा cflayer **layer, पूर्णांक (**rcv_func)(
				काष्ठा sk_buff *, काष्ठा net_device *,
				काष्ठा packet_type *, काष्ठा net_device *));

#पूर्ण_अगर /* CAIF_DEV_H_ */
