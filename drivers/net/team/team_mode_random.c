<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * drivers/net/team/team_mode_अक्रमom.c - Ranकरोm mode क्रम team
 * Copyright (c) 2013 Jiri Pirko <jiri@resnulli.us>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/अगर_team.h>

अटल bool rnd_transmit(काष्ठा team *team, काष्ठा sk_buff *skb)
अणु
	काष्ठा team_port *port;
	पूर्णांक port_index;

	port_index = pअक्रमom_u32_max(team->en_port_count);
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

अटल स्थिर काष्ठा team_mode_ops rnd_mode_ops = अणु
	.transmit		= rnd_transmit,
	.port_enter		= team_modeop_port_enter,
	.port_change_dev_addr	= team_modeop_port_change_dev_addr,
पूर्ण;

अटल स्थिर काष्ठा team_mode rnd_mode = अणु
	.kind		= "random",
	.owner		= THIS_MODULE,
	.ops		= &rnd_mode_ops,
	.lag_tx_type	= NETDEV_LAG_TX_TYPE_RANDOM,
पूर्ण;

अटल पूर्णांक __init rnd_init_module(व्योम)
अणु
	वापस team_mode_रेजिस्टर(&rnd_mode);
पूर्ण

अटल व्योम __निकास rnd_cleanup_module(व्योम)
अणु
	team_mode_unरेजिस्टर(&rnd_mode);
पूर्ण

module_init(rnd_init_module);
module_निकास(rnd_cleanup_module);

MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Jiri Pirko <jiri@resnulli.us>");
MODULE_DESCRIPTION("Random mode for team");
MODULE_ALIAS_TEAM_MODE("random");
