<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* Copyright (c) 2013-2018, The Linux Foundation. All rights reserved.
 */

#समावेश <linux/netdevice.h>
#समावेश "rmnet_config.h"
#समावेश "rmnet_map.h"
#समावेश "rmnet_private.h"
#समावेश "rmnet_vnd.h"

अटल u8 rmnet_map_करो_flow_control(काष्ठा sk_buff *skb,
				    काष्ठा rmnet_port *port,
				    पूर्णांक enable)
अणु
	काष्ठा rmnet_map_header *map_header = (व्योम *)skb->data;
	काष्ठा rmnet_endpoपूर्णांक *ep;
	काष्ठा net_device *vnd;
	u8 mux_id;
	पूर्णांक r;

	mux_id = map_header->mux_id;

	अगर (mux_id >= RMNET_MAX_LOGICAL_EP) अणु
		kमुक्त_skb(skb);
		वापस RX_HANDLER_CONSUMED;
	पूर्ण

	ep = rmnet_get_endpoपूर्णांक(port, mux_id);
	अगर (!ep) अणु
		kमुक्त_skb(skb);
		वापस RX_HANDLER_CONSUMED;
	पूर्ण

	vnd = ep->egress_dev;

	/* Ignore the ip family and pass the sequence number क्रम both v4 and v6
	 * sequence. User space करोes not support creating dedicated flows क्रम
	 * the 2 protocols
	 */
	r = rmnet_vnd_करो_flow_control(vnd, enable);
	अगर (r) अणु
		kमुक्त_skb(skb);
		वापस RMNET_MAP_COMMAND_UNSUPPORTED;
	पूर्ण अन्यथा अणु
		वापस RMNET_MAP_COMMAND_ACK;
	पूर्ण
पूर्ण

अटल व्योम rmnet_map_send_ack(काष्ठा sk_buff *skb,
			       अचिन्हित अक्षर type,
			       काष्ठा rmnet_port *port)
अणु
	काष्ठा rmnet_map_header *map_header = (व्योम *)skb->data;
	काष्ठा rmnet_map_control_command *cmd;
	काष्ठा net_device *dev = skb->dev;

	अगर (port->data_क्रमmat & RMNET_FLAGS_INGRESS_MAP_CKSUMV4)
		skb_trim(skb,
			 skb->len - माप(काष्ठा rmnet_map_dl_csum_trailer));

	skb->protocol = htons(ETH_P_MAP);

	/* Command data immediately follows the MAP header */
	cmd = (काष्ठा rmnet_map_control_command *)(map_header + 1);
	cmd->cmd_type = type & 0x03;

	netअगर_tx_lock(dev);
	dev->netdev_ops->nकरो_start_xmit(skb, dev);
	netअगर_tx_unlock(dev);
पूर्ण

/* Process MAP command frame and send N/ACK message as appropriate. Message cmd
 * name is decoded here and appropriate handler is called.
 */
व्योम rmnet_map_command(काष्ठा sk_buff *skb, काष्ठा rmnet_port *port)
अणु
	काष्ठा rmnet_map_header *map_header = (व्योम *)skb->data;
	काष्ठा rmnet_map_control_command *cmd;
	अचिन्हित अक्षर command_name;
	अचिन्हित अक्षर rc = 0;

	/* Command data immediately follows the MAP header */
	cmd = (काष्ठा rmnet_map_control_command *)(map_header + 1);
	command_name = cmd->command_name;

	चयन (command_name) अणु
	हाल RMNET_MAP_COMMAND_FLOW_ENABLE:
		rc = rmnet_map_करो_flow_control(skb, port, 1);
		अवरोध;

	हाल RMNET_MAP_COMMAND_FLOW_DISABLE:
		rc = rmnet_map_करो_flow_control(skb, port, 0);
		अवरोध;

	शेष:
		rc = RMNET_MAP_COMMAND_UNSUPPORTED;
		kमुक्त_skb(skb);
		अवरोध;
	पूर्ण
	अगर (rc == RMNET_MAP_COMMAND_ACK)
		rmnet_map_send_ack(skb, rc, port);
पूर्ण
