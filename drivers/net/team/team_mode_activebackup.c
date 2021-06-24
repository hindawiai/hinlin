<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * drivers/net/team/team_mode_activebackup.c - Active-backup mode क्रम team
 * Copyright (c) 2011 Jiri Pirko <jpirko@redhat.com>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/netdevice.h>
#समावेश <net/rtnetlink.h>
#समावेश <linux/अगर_team.h>

काष्ठा ab_priv अणु
	काष्ठा team_port __rcu *active_port;
	काष्ठा team_option_inst_info *ap_opt_inst_info;
पूर्ण;

अटल काष्ठा ab_priv *ab_priv(काष्ठा team *team)
अणु
	वापस (काष्ठा ab_priv *) &team->mode_priv;
पूर्ण

अटल rx_handler_result_t ab_receive(काष्ठा team *team, काष्ठा team_port *port,
				      काष्ठा sk_buff *skb) अणु
	काष्ठा team_port *active_port;

	active_port = rcu_dereference(ab_priv(team)->active_port);
	अगर (active_port != port)
		वापस RX_HANDLER_EXACT;
	वापस RX_HANDLER_ANOTHER;
पूर्ण

अटल bool ab_transmit(काष्ठा team *team, काष्ठा sk_buff *skb)
अणु
	काष्ठा team_port *active_port;

	active_port = rcu_dereference_bh(ab_priv(team)->active_port);
	अगर (unlikely(!active_port))
		जाओ drop;
	अगर (team_dev_queue_xmit(team, active_port, skb))
		वापस false;
	वापस true;

drop:
	dev_kमुक्त_skb_any(skb);
	वापस false;
पूर्ण

अटल व्योम ab_port_leave(काष्ठा team *team, काष्ठा team_port *port)
अणु
	अगर (ab_priv(team)->active_port == port) अणु
		RCU_INIT_POINTER(ab_priv(team)->active_port, शून्य);
		team_option_inst_set_change(ab_priv(team)->ap_opt_inst_info);
	पूर्ण
पूर्ण

अटल पूर्णांक ab_active_port_init(काष्ठा team *team,
			       काष्ठा team_option_inst_info *info)
अणु
	ab_priv(team)->ap_opt_inst_info = info;
	वापस 0;
पूर्ण

अटल पूर्णांक ab_active_port_get(काष्ठा team *team, काष्ठा team_gsetter_ctx *ctx)
अणु
	काष्ठा team_port *active_port;

	active_port = rcu_dereference_रक्षित(ab_priv(team)->active_port,
						lockdep_is_held(&team->lock));
	अगर (active_port)
		ctx->data.u32_val = active_port->dev->अगरindex;
	अन्यथा
		ctx->data.u32_val = 0;
	वापस 0;
पूर्ण

अटल पूर्णांक ab_active_port_set(काष्ठा team *team, काष्ठा team_gsetter_ctx *ctx)
अणु
	काष्ठा team_port *port;

	list_क्रम_each_entry(port, &team->port_list, list) अणु
		अगर (port->dev->अगरindex == ctx->data.u32_val) अणु
			rcu_assign_poपूर्णांकer(ab_priv(team)->active_port, port);
			वापस 0;
		पूर्ण
	पूर्ण
	वापस -ENOENT;
पूर्ण

अटल स्थिर काष्ठा team_option ab_options[] = अणु
	अणु
		.name = "activeport",
		.type = TEAM_OPTION_TYPE_U32,
		.init = ab_active_port_init,
		.getter = ab_active_port_get,
		.setter = ab_active_port_set,
	पूर्ण,
पूर्ण;

अटल पूर्णांक ab_init(काष्ठा team *team)
अणु
	वापस team_options_रेजिस्टर(team, ab_options, ARRAY_SIZE(ab_options));
पूर्ण

अटल व्योम ab_निकास(काष्ठा team *team)
अणु
	team_options_unरेजिस्टर(team, ab_options, ARRAY_SIZE(ab_options));
पूर्ण

अटल स्थिर काष्ठा team_mode_ops ab_mode_ops = अणु
	.init			= ab_init,
	.निकास			= ab_निकास,
	.receive		= ab_receive,
	.transmit		= ab_transmit,
	.port_leave		= ab_port_leave,
पूर्ण;

अटल स्थिर काष्ठा team_mode ab_mode = अणु
	.kind		= "activebackup",
	.owner		= THIS_MODULE,
	.priv_size	= माप(काष्ठा ab_priv),
	.ops		= &ab_mode_ops,
	.lag_tx_type	= NETDEV_LAG_TX_TYPE_ACTIVEBACKUP,
पूर्ण;

अटल पूर्णांक __init ab_init_module(व्योम)
अणु
	वापस team_mode_रेजिस्टर(&ab_mode);
पूर्ण

अटल व्योम __निकास ab_cleanup_module(व्योम)
अणु
	team_mode_unरेजिस्टर(&ab_mode);
पूर्ण

module_init(ab_init_module);
module_निकास(ab_cleanup_module);

MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Jiri Pirko <jpirko@redhat.com>");
MODULE_DESCRIPTION("Active-backup mode for team");
MODULE_ALIAS_TEAM_MODE("activebackup");
