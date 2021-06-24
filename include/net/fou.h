<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __NET_FOU_H
#घोषणा __NET_FOU_H

#समावेश <linux/skbuff.h>

#समावेश <net/flow.h>
#समावेश <net/gue.h>
#समावेश <net/ip_tunnels.h>
#समावेश <net/udp.h>

माप_प्रकार fou_encap_hlen(काष्ठा ip_tunnel_encap *e);
माप_प्रकार gue_encap_hlen(काष्ठा ip_tunnel_encap *e);

पूर्णांक __fou_build_header(काष्ठा sk_buff *skb, काष्ठा ip_tunnel_encap *e,
		       u8 *protocol, __be16 *sport, पूर्णांक type);
पूर्णांक __gue_build_header(काष्ठा sk_buff *skb, काष्ठा ip_tunnel_encap *e,
		       u8 *protocol, __be16 *sport, पूर्णांक type);

#पूर्ण_अगर
