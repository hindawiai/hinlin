<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * drivers/net/team/team_mode_broadcast.c - Broadcast mode क्रम team
 * Copyright (c) 2012 Jiri Pirko <jpirko@redhat.com>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/netdevice.h>
#समावेश <linux/अगर_team.h>

अटल bool bc_transmit(काष्ठा team *team, काष्ठा sk_buff *skb)
अणु
	काष्ठा team_port *cur;
	काष्ठा team_port *last = शून्य;
	काष्ठा sk_buff *skb2;
	bool ret;
	bool sum_ret = false;

	list_क्रम_each_entry_rcu(cur, &team->port_list, list) अणु
		अगर (team_port_txable(cur)) अणु
			अगर (last) अणु
				skb2 = skb_clone(skb, GFP_ATOMIC);
				अगर (skb2) अणु
					ret = !team_dev_queue_xmit(team, last,
								   skb2);
					अगर (!sum_ret)
						sum_ret = ret;
				पूर्ण
			पूर्ण
			last = cur;
		पूर्ण
	पूर्ण
	अगर (last) अणु
		ret = !team_dev_queue_xmit(team, last, skb);
		अगर (!sum_ret)
			sum_ret = ret;
	पूर्ण
	वापस sum_ret;
पूर्ण

अटल स्थिर काष्ठा team_mode_ops bc_mode_ops = अणु
	.transmit		= bc_transmit,
	.port_enter		= team_modeop_port_enter,
	.port_change_dev_addr	= team_modeop_port_change_dev_addr,
पूर्ण;

अटल स्थिर काष्ठा team_mode bc_mode = अणु
	.kind		= "broadcast",
	.owner		= THIS_MODULE,
	.ops		= &bc_mode_ops,
	.lag_tx_type	= NETDEV_LAG_TX_TYPE_BROADCAST,
पूर्ण;

अटल पूर्णांक __init bc_init_module(व्योम)
अणु
	वापस team_mode_रेजिस्टर(&bc_mode);
पूर्ण

अटल व्योम __निकास bc_cleanup_module(व्योम)
अणु
	team_mode_unरेजिस्टर(&bc_mode);
पूर्ण

module_init(bc_init_module);
module_निकास(bc_cleanup_module);

MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Jiri Pirko <jpirko@redhat.com>");
MODULE_DESCRIPTION("Broadcast mode for team");
MODULE_ALIAS_TEAM_MODE("broadcast");
