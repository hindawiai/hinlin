<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright (C) B.A.T.M.A.N. contributors:
 *
 * Marek Lindner, Simon Wunderlich
 */

#अगर_अघोषित _NET_BATMAN_ADV_TVLV_H_
#घोषणा _NET_BATMAN_ADV_TVLV_H_

#समावेश "main.h"

#समावेश <linux/types.h>
#समावेश <uapi/linux/batadv_packet.h>

व्योम batadv_tvlv_container_रेजिस्टर(काष्ठा batadv_priv *bat_priv,
				    u8 type, u8 version,
				    व्योम *tvlv_value, u16 tvlv_value_len);
u16 batadv_tvlv_container_ogm_append(काष्ठा batadv_priv *bat_priv,
				     अचिन्हित अक्षर **packet_buff,
				     पूर्णांक *packet_buff_len, पूर्णांक packet_min_len);
व्योम batadv_tvlv_ogm_receive(काष्ठा batadv_priv *bat_priv,
			     काष्ठा batadv_ogm_packet *batadv_ogm_packet,
			     काष्ठा batadv_orig_node *orig_node);
व्योम batadv_tvlv_container_unरेजिस्टर(काष्ठा batadv_priv *bat_priv,
				      u8 type, u8 version);

व्योम batadv_tvlv_handler_रेजिस्टर(काष्ठा batadv_priv *bat_priv,
				  व्योम (*optr)(काष्ठा batadv_priv *bat_priv,
					       काष्ठा batadv_orig_node *orig,
					       u8 flags,
					       व्योम *tvlv_value,
					       u16 tvlv_value_len),
				  पूर्णांक (*uptr)(काष्ठा batadv_priv *bat_priv,
					      u8 *src, u8 *dst,
					      व्योम *tvlv_value,
					      u16 tvlv_value_len),
				  u8 type, u8 version, u8 flags);
व्योम batadv_tvlv_handler_unरेजिस्टर(काष्ठा batadv_priv *bat_priv,
				    u8 type, u8 version);
पूर्णांक batadv_tvlv_containers_process(काष्ठा batadv_priv *bat_priv,
				   bool ogm_source,
				   काष्ठा batadv_orig_node *orig_node,
				   u8 *src, u8 *dst,
				   व्योम *tvlv_buff, u16 tvlv_buff_len);
व्योम batadv_tvlv_unicast_send(काष्ठा batadv_priv *bat_priv, u8 *src,
			      u8 *dst, u8 type, u8 version,
			      व्योम *tvlv_value, u16 tvlv_value_len);

#पूर्ण_अगर /* _NET_BATMAN_ADV_TVLV_H_ */
