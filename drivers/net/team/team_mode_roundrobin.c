<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * drivers/net/team/team_mode_roundrobin.c - Round-robin mode क्रम team
 * Copyright (c) 2011 Jiri Pirko <jpirko@redhat.com>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/netdevice.h>
#समावेश <linux/अगर_team.h>

काष्ठा rr_priv अणु
	अचिन्हित पूर्णांक sent_packets;
पूर्ण;

अटल काष्ठा rr_priv *rr_priv(काष्ठा team *team)
अणु
	वापस (काष्ठा rr_priv *) &team->mode_priv;
पूर्ण

अटल bool rr_transmit(काष्ठा team *team, काष्ठा sk_buff *skb)
अणु
	काष्ठा team_port *port;
	पूर्णांक port_index;

	port_index = team_num_to_port_index(team,
					    rr_priv(team)->sent_packets++);
	port = team_get_port_by_index_rcu(team, port_index);
	अगर (unlikely(!port))
		जाओ drop;
	port = team_get_first_port_txable_rcu(team, port);
	अगर (unlikely(!port))
		जाओ drop;
	अगर (team_dev_queue_xmit(team, port, skb))
		वापस false;
	वापस true;

drop:
	dev_kमुक्त_skb_any(skb);
	वापस false;
पूर्ण

अटल स्थिर काष्ठा team_mode_ops rr_mode_ops = अणु
	.transmit		= rr_transmit,
	.port_enter		= team_modeop_port_enter,
	.port_change_dev_addr	= team_modeop_port_change_dev_addr,
पूर्ण;

अटल स्थिर काष्ठा team_mode rr_mode = अणु
	.kind		= "roundrobin",
	.owner		= THIS_MODULE,
	.priv_size	= माप(काष्ठा rr_priv),
	.ops		= &rr_mode_ops,
	.lag_tx_type	= NETDEV_LAG_TX_TYPE_ROUNDROBIN,
पूर्ण;

अटल पूर्णांक __init rr_init_module(व्योम)
अणु
	वापस team_mode_रेजिस्टर(&rr_mode);
पूर्ण

अटल व्योम __निकास rr_cleanup_module(व्योम)
अणु
	team_mode_unरेजिस्टर(&rr_mode);
पूर्ण

module_init(rr_init_module);
module_निकास(rr_cleanup_module);

MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Jiri Pirko <jpirko@redhat.com>");
MODULE_DESCRIPTION("Round-robin mode for team");
MODULE_ALIAS_TEAM_MODE("roundrobin");
