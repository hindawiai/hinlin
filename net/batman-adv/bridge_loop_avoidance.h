<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright (C) B.A.T.M.A.N. contributors:
 *
 * Simon Wunderlich
 */

#अगर_अघोषित _NET_BATMAN_ADV_BLA_H_
#घोषणा _NET_BATMAN_ADV_BLA_H_

#समावेश "main.h"

#समावेश <linux/compiler.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/netlink.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/मानकघोष.स>
#समावेश <linux/types.h>

/**
 * batadv_bla_is_loopdetect_mac() - check अगर the mac address is from a loop
 *  detect frame sent by bridge loop aव्योमance
 * @mac: mac address to check
 *
 * Return: true अगर the it looks like a loop detect frame
 * (mac starts with BA:BE), false otherwise
 */
अटल अंतरभूत bool batadv_bla_is_loopdetect_mac(स्थिर uपूर्णांक8_t *mac)
अणु
	अगर (mac[0] == 0xba && mac[1] == 0xbe)
		वापस true;

	वापस false;
पूर्ण

#अगर_घोषित CONFIG_BATMAN_ADV_BLA
bool batadv_bla_rx(काष्ठा batadv_priv *bat_priv, काष्ठा sk_buff *skb,
		   अचिन्हित लघु vid, पूर्णांक packet_type);
bool batadv_bla_tx(काष्ठा batadv_priv *bat_priv, काष्ठा sk_buff *skb,
		   अचिन्हित लघु vid);
bool batadv_bla_is_backbone_gw(काष्ठा sk_buff *skb,
			       काष्ठा batadv_orig_node *orig_node,
			       पूर्णांक hdr_size);
पूर्णांक batadv_bla_claim_dump(काष्ठा sk_buff *msg, काष्ठा netlink_callback *cb);
पूर्णांक batadv_bla_backbone_dump(काष्ठा sk_buff *msg, काष्ठा netlink_callback *cb);
bool batadv_bla_is_backbone_gw_orig(काष्ठा batadv_priv *bat_priv, u8 *orig,
				    अचिन्हित लघु vid);
bool batadv_bla_check_bcast_duplist(काष्ठा batadv_priv *bat_priv,
				    काष्ठा sk_buff *skb);
व्योम batadv_bla_update_orig_address(काष्ठा batadv_priv *bat_priv,
				    काष्ठा batadv_hard_अगरace *primary_अगर,
				    काष्ठा batadv_hard_अगरace *oldअगर);
व्योम batadv_bla_status_update(काष्ठा net_device *net_dev);
पूर्णांक batadv_bla_init(काष्ठा batadv_priv *bat_priv);
व्योम batadv_bla_मुक्त(काष्ठा batadv_priv *bat_priv);
पूर्णांक batadv_bla_claim_dump(काष्ठा sk_buff *msg, काष्ठा netlink_callback *cb);
#अगर_घोषित CONFIG_BATMAN_ADV_DAT
bool batadv_bla_check_claim(काष्ठा batadv_priv *bat_priv, u8 *addr,
			    अचिन्हित लघु vid);
#पूर्ण_अगर
#घोषणा BATADV_BLA_CRC_INIT	0
#अन्यथा /* अगरdef CONFIG_BATMAN_ADV_BLA */

अटल अंतरभूत bool batadv_bla_rx(काष्ठा batadv_priv *bat_priv,
				 काष्ठा sk_buff *skb, अचिन्हित लघु vid,
				 पूर्णांक packet_type)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत bool batadv_bla_tx(काष्ठा batadv_priv *bat_priv,
				 काष्ठा sk_buff *skb, अचिन्हित लघु vid)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत bool batadv_bla_is_backbone_gw(काष्ठा sk_buff *skb,
					     काष्ठा batadv_orig_node *orig_node,
					     पूर्णांक hdr_size)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत bool batadv_bla_is_backbone_gw_orig(काष्ठा batadv_priv *bat_priv,
						  u8 *orig, अचिन्हित लघु vid)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत bool
batadv_bla_check_bcast_duplist(काष्ठा batadv_priv *bat_priv,
			       काष्ठा sk_buff *skb)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत व्योम
batadv_bla_update_orig_address(काष्ठा batadv_priv *bat_priv,
			       काष्ठा batadv_hard_अगरace *primary_अगर,
			       काष्ठा batadv_hard_अगरace *oldअगर)
अणु
पूर्ण

अटल अंतरभूत पूर्णांक batadv_bla_init(काष्ठा batadv_priv *bat_priv)
अणु
	वापस 1;
पूर्ण

अटल अंतरभूत व्योम batadv_bla_मुक्त(काष्ठा batadv_priv *bat_priv)
अणु
पूर्ण

अटल अंतरभूत पूर्णांक batadv_bla_claim_dump(काष्ठा sk_buff *msg,
					काष्ठा netlink_callback *cb)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल अंतरभूत पूर्णांक batadv_bla_backbone_dump(काष्ठा sk_buff *msg,
					   काष्ठा netlink_callback *cb)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल अंतरभूत
bool batadv_bla_check_claim(काष्ठा batadv_priv *bat_priv, u8 *addr,
			    अचिन्हित लघु vid)
अणु
	वापस true;
पूर्ण

#पूर्ण_अगर /* अगरdef CONFIG_BATMAN_ADV_BLA */

#पूर्ण_अगर /* अगरndef _NET_BATMAN_ADV_BLA_H_ */
