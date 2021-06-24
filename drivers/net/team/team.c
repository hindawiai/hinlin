<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * drivers/net/team/team.c - Network team device driver
 * Copyright (c) 2011 Jiri Pirko <jpirko@redhat.com>
 */

#समावेश <linux/ethtool.h>
#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/rcupdate.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/प्रकार.स>
#समावेश <linux/notअगरier.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/netpoll.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <linux/अगर_arp.h>
#समावेश <linux/socket.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/rtnetlink.h>
#समावेश <net/rtnetlink.h>
#समावेश <net/genetlink.h>
#समावेश <net/netlink.h>
#समावेश <net/sch_generic.h>
#समावेश <generated/utsrelease.h>
#समावेश <linux/अगर_team.h>

#घोषणा DRV_NAME "team"


/**********
 * Helpers
 **********/

अटल काष्ठा team_port *team_port_get_rtnl(स्थिर काष्ठा net_device *dev)
अणु
	काष्ठा team_port *port = rtnl_dereference(dev->rx_handler_data);

	वापस netअगर_is_team_port(dev) ? port : शून्य;
पूर्ण

/*
 * Since the ability to change device address क्रम खोलो port device is tested in
 * team_port_add, this function can be called without control of वापस value
 */
अटल पूर्णांक __set_port_dev_addr(काष्ठा net_device *port_dev,
			       स्थिर अचिन्हित अक्षर *dev_addr)
अणु
	काष्ठा sockaddr_storage addr;

	स_नकल(addr.__data, dev_addr, port_dev->addr_len);
	addr.ss_family = port_dev->type;
	वापस dev_set_mac_address(port_dev, (काष्ठा sockaddr *)&addr, शून्य);
पूर्ण

अटल पूर्णांक team_port_set_orig_dev_addr(काष्ठा team_port *port)
अणु
	वापस __set_port_dev_addr(port->dev, port->orig.dev_addr);
पूर्ण

अटल पूर्णांक team_port_set_team_dev_addr(काष्ठा team *team,
				       काष्ठा team_port *port)
अणु
	वापस __set_port_dev_addr(port->dev, team->dev->dev_addr);
पूर्ण

पूर्णांक team_modeop_port_enter(काष्ठा team *team, काष्ठा team_port *port)
अणु
	वापस team_port_set_team_dev_addr(team, port);
पूर्ण
EXPORT_SYMBOL(team_modeop_port_enter);

व्योम team_modeop_port_change_dev_addr(काष्ठा team *team,
				      काष्ठा team_port *port)
अणु
	team_port_set_team_dev_addr(team, port);
पूर्ण
EXPORT_SYMBOL(team_modeop_port_change_dev_addr);

अटल व्योम team_lower_state_changed(काष्ठा team_port *port)
अणु
	काष्ठा netdev_lag_lower_state_info info;

	info.link_up = port->linkup;
	info.tx_enabled = team_port_enabled(port);
	netdev_lower_state_changed(port->dev, &info);
पूर्ण

अटल व्योम team_refresh_port_linkup(काष्ठा team_port *port)
अणु
	bool new_linkup = port->user.linkup_enabled ? port->user.linkup :
						      port->state.linkup;

	अगर (port->linkup != new_linkup) अणु
		port->linkup = new_linkup;
		team_lower_state_changed(port);
	पूर्ण
पूर्ण


/*******************
 * Options handling
 *******************/

काष्ठा team_option_inst अणु /* One क्रम each option instance */
	काष्ठा list_head list;
	काष्ठा list_head पंचांगp_list;
	काष्ठा team_option *option;
	काष्ठा team_option_inst_info info;
	bool changed;
	bool हटाओd;
पूर्ण;

अटल काष्ठा team_option *__team_find_option(काष्ठा team *team,
					      स्थिर अक्षर *opt_name)
अणु
	काष्ठा team_option *option;

	list_क्रम_each_entry(option, &team->option_list, list) अणु
		अगर (म_भेद(option->name, opt_name) == 0)
			वापस option;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल व्योम __team_option_inst_del(काष्ठा team_option_inst *opt_inst)
अणु
	list_del(&opt_inst->list);
	kमुक्त(opt_inst);
पूर्ण

अटल व्योम __team_option_inst_del_option(काष्ठा team *team,
					  काष्ठा team_option *option)
अणु
	काष्ठा team_option_inst *opt_inst, *पंचांगp;

	list_क्रम_each_entry_safe(opt_inst, पंचांगp, &team->option_inst_list, list) अणु
		अगर (opt_inst->option == option)
			__team_option_inst_del(opt_inst);
	पूर्ण
पूर्ण

अटल पूर्णांक __team_option_inst_add(काष्ठा team *team, काष्ठा team_option *option,
				  काष्ठा team_port *port)
अणु
	काष्ठा team_option_inst *opt_inst;
	अचिन्हित पूर्णांक array_size;
	अचिन्हित पूर्णांक i;
	पूर्णांक err;

	array_size = option->array_size;
	अगर (!array_size)
		array_size = 1; /* No array but still need one instance */

	क्रम (i = 0; i < array_size; i++) अणु
		opt_inst = kदो_स्मृति(माप(*opt_inst), GFP_KERNEL);
		अगर (!opt_inst)
			वापस -ENOMEM;
		opt_inst->option = option;
		opt_inst->info.port = port;
		opt_inst->info.array_index = i;
		opt_inst->changed = true;
		opt_inst->हटाओd = false;
		list_add_tail(&opt_inst->list, &team->option_inst_list);
		अगर (option->init) अणु
			err = option->init(team, &opt_inst->info);
			अगर (err)
				वापस err;
		पूर्ण

	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक __team_option_inst_add_option(काष्ठा team *team,
					 काष्ठा team_option *option)
अणु
	पूर्णांक err;

	अगर (!option->per_port) अणु
		err = __team_option_inst_add(team, option, शून्य);
		अगर (err)
			जाओ inst_del_option;
	पूर्ण
	वापस 0;

inst_del_option:
	__team_option_inst_del_option(team, option);
	वापस err;
पूर्ण

अटल व्योम __team_option_inst_mark_हटाओd_option(काष्ठा team *team,
						   काष्ठा team_option *option)
अणु
	काष्ठा team_option_inst *opt_inst;

	list_क्रम_each_entry(opt_inst, &team->option_inst_list, list) अणु
		अगर (opt_inst->option == option) अणु
			opt_inst->changed = true;
			opt_inst->हटाओd = true;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम __team_option_inst_del_port(काष्ठा team *team,
					काष्ठा team_port *port)
अणु
	काष्ठा team_option_inst *opt_inst, *पंचांगp;

	list_क्रम_each_entry_safe(opt_inst, पंचांगp, &team->option_inst_list, list) अणु
		अगर (opt_inst->option->per_port &&
		    opt_inst->info.port == port)
			__team_option_inst_del(opt_inst);
	पूर्ण
पूर्ण

अटल पूर्णांक __team_option_inst_add_port(काष्ठा team *team,
				       काष्ठा team_port *port)
अणु
	काष्ठा team_option *option;
	पूर्णांक err;

	list_क्रम_each_entry(option, &team->option_list, list) अणु
		अगर (!option->per_port)
			जारी;
		err = __team_option_inst_add(team, option, port);
		अगर (err)
			जाओ inst_del_port;
	पूर्ण
	वापस 0;

inst_del_port:
	__team_option_inst_del_port(team, port);
	वापस err;
पूर्ण

अटल व्योम __team_option_inst_mark_हटाओd_port(काष्ठा team *team,
						 काष्ठा team_port *port)
अणु
	काष्ठा team_option_inst *opt_inst;

	list_क्रम_each_entry(opt_inst, &team->option_inst_list, list) अणु
		अगर (opt_inst->info.port == port) अणु
			opt_inst->changed = true;
			opt_inst->हटाओd = true;
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक __team_options_रेजिस्टर(काष्ठा team *team,
				   स्थिर काष्ठा team_option *option,
				   माप_प्रकार option_count)
अणु
	पूर्णांक i;
	काष्ठा team_option **dst_opts;
	पूर्णांक err;

	dst_opts = kसुस्मृति(option_count, माप(काष्ठा team_option *),
			   GFP_KERNEL);
	अगर (!dst_opts)
		वापस -ENOMEM;
	क्रम (i = 0; i < option_count; i++, option++) अणु
		अगर (__team_find_option(team, option->name)) अणु
			err = -EEXIST;
			जाओ alloc_rollback;
		पूर्ण
		dst_opts[i] = kmemdup(option, माप(*option), GFP_KERNEL);
		अगर (!dst_opts[i]) अणु
			err = -ENOMEM;
			जाओ alloc_rollback;
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < option_count; i++) अणु
		err = __team_option_inst_add_option(team, dst_opts[i]);
		अगर (err)
			जाओ inst_rollback;
		list_add_tail(&dst_opts[i]->list, &team->option_list);
	पूर्ण

	kमुक्त(dst_opts);
	वापस 0;

inst_rollback:
	क्रम (i--; i >= 0; i--)
		__team_option_inst_del_option(team, dst_opts[i]);

	i = option_count;
alloc_rollback:
	क्रम (i--; i >= 0; i--)
		kमुक्त(dst_opts[i]);

	kमुक्त(dst_opts);
	वापस err;
पूर्ण

अटल व्योम __team_options_mark_हटाओd(काष्ठा team *team,
					स्थिर काष्ठा team_option *option,
					माप_प्रकार option_count)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < option_count; i++, option++) अणु
		काष्ठा team_option *del_opt;

		del_opt = __team_find_option(team, option->name);
		अगर (del_opt)
			__team_option_inst_mark_हटाओd_option(team, del_opt);
	पूर्ण
पूर्ण

अटल व्योम __team_options_unरेजिस्टर(काष्ठा team *team,
				      स्थिर काष्ठा team_option *option,
				      माप_प्रकार option_count)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < option_count; i++, option++) अणु
		काष्ठा team_option *del_opt;

		del_opt = __team_find_option(team, option->name);
		अगर (del_opt) अणु
			__team_option_inst_del_option(team, del_opt);
			list_del(&del_opt->list);
			kमुक्त(del_opt);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम __team_options_change_check(काष्ठा team *team);

पूर्णांक team_options_रेजिस्टर(काष्ठा team *team,
			  स्थिर काष्ठा team_option *option,
			  माप_प्रकार option_count)
अणु
	पूर्णांक err;

	err = __team_options_रेजिस्टर(team, option, option_count);
	अगर (err)
		वापस err;
	__team_options_change_check(team);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(team_options_रेजिस्टर);

व्योम team_options_unरेजिस्टर(काष्ठा team *team,
			     स्थिर काष्ठा team_option *option,
			     माप_प्रकार option_count)
अणु
	__team_options_mark_हटाओd(team, option, option_count);
	__team_options_change_check(team);
	__team_options_unरेजिस्टर(team, option, option_count);
पूर्ण
EXPORT_SYMBOL(team_options_unरेजिस्टर);

अटल पूर्णांक team_option_get(काष्ठा team *team,
			   काष्ठा team_option_inst *opt_inst,
			   काष्ठा team_gsetter_ctx *ctx)
अणु
	अगर (!opt_inst->option->getter)
		वापस -EOPNOTSUPP;
	वापस opt_inst->option->getter(team, ctx);
पूर्ण

अटल पूर्णांक team_option_set(काष्ठा team *team,
			   काष्ठा team_option_inst *opt_inst,
			   काष्ठा team_gsetter_ctx *ctx)
अणु
	अगर (!opt_inst->option->setter)
		वापस -EOPNOTSUPP;
	वापस opt_inst->option->setter(team, ctx);
पूर्ण

व्योम team_option_inst_set_change(काष्ठा team_option_inst_info *opt_inst_info)
अणु
	काष्ठा team_option_inst *opt_inst;

	opt_inst = container_of(opt_inst_info, काष्ठा team_option_inst, info);
	opt_inst->changed = true;
पूर्ण
EXPORT_SYMBOL(team_option_inst_set_change);

व्योम team_options_change_check(काष्ठा team *team)
अणु
	__team_options_change_check(team);
पूर्ण
EXPORT_SYMBOL(team_options_change_check);


/****************
 * Mode handling
 ****************/

अटल LIST_HEAD(mode_list);
अटल DEFINE_SPINLOCK(mode_list_lock);

काष्ठा team_mode_item अणु
	काष्ठा list_head list;
	स्थिर काष्ठा team_mode *mode;
पूर्ण;

अटल काष्ठा team_mode_item *__find_mode(स्थिर अक्षर *kind)
अणु
	काष्ठा team_mode_item *mitem;

	list_क्रम_each_entry(mitem, &mode_list, list) अणु
		अगर (म_भेद(mitem->mode->kind, kind) == 0)
			वापस mitem;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल bool is_good_mode_name(स्थिर अक्षर *name)
अणु
	जबतक (*name != '\0') अणु
		अगर (!है_अक्षर(*name) && !है_अंक(*name) && *name != '_')
			वापस false;
		name++;
	पूर्ण
	वापस true;
पूर्ण

पूर्णांक team_mode_रेजिस्टर(स्थिर काष्ठा team_mode *mode)
अणु
	पूर्णांक err = 0;
	काष्ठा team_mode_item *mitem;

	अगर (!is_good_mode_name(mode->kind) ||
	    mode->priv_size > TEAM_MODE_PRIV_SIZE)
		वापस -EINVAL;

	mitem = kदो_स्मृति(माप(*mitem), GFP_KERNEL);
	अगर (!mitem)
		वापस -ENOMEM;

	spin_lock(&mode_list_lock);
	अगर (__find_mode(mode->kind)) अणु
		err = -EEXIST;
		kमुक्त(mitem);
		जाओ unlock;
	पूर्ण
	mitem->mode = mode;
	list_add_tail(&mitem->list, &mode_list);
unlock:
	spin_unlock(&mode_list_lock);
	वापस err;
पूर्ण
EXPORT_SYMBOL(team_mode_रेजिस्टर);

व्योम team_mode_unरेजिस्टर(स्थिर काष्ठा team_mode *mode)
अणु
	काष्ठा team_mode_item *mitem;

	spin_lock(&mode_list_lock);
	mitem = __find_mode(mode->kind);
	अगर (mitem) अणु
		list_del_init(&mitem->list);
		kमुक्त(mitem);
	पूर्ण
	spin_unlock(&mode_list_lock);
पूर्ण
EXPORT_SYMBOL(team_mode_unरेजिस्टर);

अटल स्थिर काष्ठा team_mode *team_mode_get(स्थिर अक्षर *kind)
अणु
	काष्ठा team_mode_item *mitem;
	स्थिर काष्ठा team_mode *mode = शून्य;

	अगर (!try_module_get(THIS_MODULE))
		वापस शून्य;

	spin_lock(&mode_list_lock);
	mitem = __find_mode(kind);
	अगर (!mitem) अणु
		spin_unlock(&mode_list_lock);
		request_module("team-mode-%s", kind);
		spin_lock(&mode_list_lock);
		mitem = __find_mode(kind);
	पूर्ण
	अगर (mitem) अणु
		mode = mitem->mode;
		अगर (!try_module_get(mode->owner))
			mode = शून्य;
	पूर्ण

	spin_unlock(&mode_list_lock);
	module_put(THIS_MODULE);
	वापस mode;
पूर्ण

अटल व्योम team_mode_put(स्थिर काष्ठा team_mode *mode)
अणु
	module_put(mode->owner);
पूर्ण

अटल bool team_dummy_transmit(काष्ठा team *team, काष्ठा sk_buff *skb)
अणु
	dev_kमुक्त_skb_any(skb);
	वापस false;
पूर्ण

अटल rx_handler_result_t team_dummy_receive(काष्ठा team *team,
					      काष्ठा team_port *port,
					      काष्ठा sk_buff *skb)
अणु
	वापस RX_HANDLER_ANOTHER;
पूर्ण

अटल स्थिर काष्ठा team_mode __team_no_mode = अणु
	.kind		= "*NOMODE*",
पूर्ण;

अटल bool team_is_mode_set(काष्ठा team *team)
अणु
	वापस team->mode != &__team_no_mode;
पूर्ण

अटल व्योम team_set_no_mode(काष्ठा team *team)
अणु
	team->user_carrier_enabled = false;
	team->mode = &__team_no_mode;
पूर्ण

अटल व्योम team_adjust_ops(काष्ठा team *team)
अणु
	/*
	 * To aव्योम checks in rx/tx skb paths, ensure here that non-null and
	 * correct ops are always set.
	 */

	अगर (!team->en_port_count || !team_is_mode_set(team) ||
	    !team->mode->ops->transmit)
		team->ops.transmit = team_dummy_transmit;
	अन्यथा
		team->ops.transmit = team->mode->ops->transmit;

	अगर (!team->en_port_count || !team_is_mode_set(team) ||
	    !team->mode->ops->receive)
		team->ops.receive = team_dummy_receive;
	अन्यथा
		team->ops.receive = team->mode->ops->receive;
पूर्ण

/*
 * We can benefit from the fact that it's ensured no port is present
 * at the समय of mode change. Thereक्रमe no packets are in fly so there's no
 * need to set mode operations in any special way.
 */
अटल पूर्णांक __team_change_mode(काष्ठा team *team,
			      स्थिर काष्ठा team_mode *new_mode)
अणु
	/* Check अगर mode was previously set and करो cleanup अगर so */
	अगर (team_is_mode_set(team)) अणु
		व्योम (*निकास_op)(काष्ठा team *team) = team->ops.निकास;

		/* Clear ops area so no callback is called any दीर्घer */
		स_रखो(&team->ops, 0, माप(काष्ठा team_mode_ops));
		team_adjust_ops(team);

		अगर (निकास_op)
			निकास_op(team);
		team_mode_put(team->mode);
		team_set_no_mode(team);
		/* zero निजी data area */
		स_रखो(&team->mode_priv, 0,
		       माप(काष्ठा team) - दुरत्व(काष्ठा team, mode_priv));
	पूर्ण

	अगर (!new_mode)
		वापस 0;

	अगर (new_mode->ops->init) अणु
		पूर्णांक err;

		err = new_mode->ops->init(team);
		अगर (err)
			वापस err;
	पूर्ण

	team->mode = new_mode;
	स_नकल(&team->ops, new_mode->ops, माप(काष्ठा team_mode_ops));
	team_adjust_ops(team);

	वापस 0;
पूर्ण

अटल पूर्णांक team_change_mode(काष्ठा team *team, स्थिर अक्षर *kind)
अणु
	स्थिर काष्ठा team_mode *new_mode;
	काष्ठा net_device *dev = team->dev;
	पूर्णांक err;

	अगर (!list_empty(&team->port_list)) अणु
		netdev_err(dev, "No ports can be present during mode change\n");
		वापस -EBUSY;
	पूर्ण

	अगर (team_is_mode_set(team) && म_भेद(team->mode->kind, kind) == 0) अणु
		netdev_err(dev, "Unable to change to the same mode the team is in\n");
		वापस -EINVAL;
	पूर्ण

	new_mode = team_mode_get(kind);
	अगर (!new_mode) अणु
		netdev_err(dev, "Mode \"%s\" not found\n", kind);
		वापस -EINVAL;
	पूर्ण

	err = __team_change_mode(team, new_mode);
	अगर (err) अणु
		netdev_err(dev, "Failed to change to mode \"%s\"\n", kind);
		team_mode_put(new_mode);
		वापस err;
	पूर्ण

	netdev_info(dev, "Mode changed to \"%s\"\n", kind);
	वापस 0;
पूर्ण


/*********************
 * Peers notअगरication
 *********************/

अटल व्योम team_notअगरy_peers_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा team *team;
	पूर्णांक val;

	team = container_of(work, काष्ठा team, notअगरy_peers.dw.work);

	अगर (!rtnl_trylock()) अणु
		schedule_delayed_work(&team->notअगरy_peers.dw, 0);
		वापस;
	पूर्ण
	val = atomic_dec_अगर_positive(&team->notअगरy_peers.count_pending);
	अगर (val < 0) अणु
		rtnl_unlock();
		वापस;
	पूर्ण
	call_netdevice_notअगरiers(NETDEV_NOTIFY_PEERS, team->dev);
	rtnl_unlock();
	अगर (val)
		schedule_delayed_work(&team->notअगरy_peers.dw,
				      msecs_to_jअगरfies(team->notअगरy_peers.पूर्णांकerval));
पूर्ण

अटल व्योम team_notअगरy_peers(काष्ठा team *team)
अणु
	अगर (!team->notअगरy_peers.count || !netअगर_running(team->dev))
		वापस;
	atomic_add(team->notअगरy_peers.count, &team->notअगरy_peers.count_pending);
	schedule_delayed_work(&team->notअगरy_peers.dw, 0);
पूर्ण

अटल व्योम team_notअगरy_peers_init(काष्ठा team *team)
अणु
	INIT_DELAYED_WORK(&team->notअगरy_peers.dw, team_notअगरy_peers_work);
पूर्ण

अटल व्योम team_notअगरy_peers_fini(काष्ठा team *team)
अणु
	cancel_delayed_work_sync(&team->notअगरy_peers.dw);
पूर्ण


/*******************************
 * Send multicast group rejoins
 *******************************/

अटल व्योम team_mcast_rejoin_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा team *team;
	पूर्णांक val;

	team = container_of(work, काष्ठा team, mcast_rejoin.dw.work);

	अगर (!rtnl_trylock()) अणु
		schedule_delayed_work(&team->mcast_rejoin.dw, 0);
		वापस;
	पूर्ण
	val = atomic_dec_अगर_positive(&team->mcast_rejoin.count_pending);
	अगर (val < 0) अणु
		rtnl_unlock();
		वापस;
	पूर्ण
	call_netdevice_notअगरiers(NETDEV_RESEND_IGMP, team->dev);
	rtnl_unlock();
	अगर (val)
		schedule_delayed_work(&team->mcast_rejoin.dw,
				      msecs_to_jअगरfies(team->mcast_rejoin.पूर्णांकerval));
पूर्ण

अटल व्योम team_mcast_rejoin(काष्ठा team *team)
अणु
	अगर (!team->mcast_rejoin.count || !netअगर_running(team->dev))
		वापस;
	atomic_add(team->mcast_rejoin.count, &team->mcast_rejoin.count_pending);
	schedule_delayed_work(&team->mcast_rejoin.dw, 0);
पूर्ण

अटल व्योम team_mcast_rejoin_init(काष्ठा team *team)
अणु
	INIT_DELAYED_WORK(&team->mcast_rejoin.dw, team_mcast_rejoin_work);
पूर्ण

अटल व्योम team_mcast_rejoin_fini(काष्ठा team *team)
अणु
	cancel_delayed_work_sync(&team->mcast_rejoin.dw);
पूर्ण


/************************
 * Rx path frame handler
 ************************/

/* note: alपढ़ोy called with rcu_पढ़ो_lock */
अटल rx_handler_result_t team_handle_frame(काष्ठा sk_buff **pskb)
अणु
	काष्ठा sk_buff *skb = *pskb;
	काष्ठा team_port *port;
	काष्ठा team *team;
	rx_handler_result_t res;

	skb = skb_share_check(skb, GFP_ATOMIC);
	अगर (!skb)
		वापस RX_HANDLER_CONSUMED;

	*pskb = skb;

	port = team_port_get_rcu(skb->dev);
	team = port->team;
	अगर (!team_port_enabled(port)) अणु
		/* allow exact match delivery क्रम disabled ports */
		res = RX_HANDLER_EXACT;
	पूर्ण अन्यथा अणु
		res = team->ops.receive(team, port, skb);
	पूर्ण
	अगर (res == RX_HANDLER_ANOTHER) अणु
		काष्ठा team_pcpu_stats *pcpu_stats;

		pcpu_stats = this_cpu_ptr(team->pcpu_stats);
		u64_stats_update_begin(&pcpu_stats->syncp);
		pcpu_stats->rx_packets++;
		pcpu_stats->rx_bytes += skb->len;
		अगर (skb->pkt_type == PACKET_MULTICAST)
			pcpu_stats->rx_multicast++;
		u64_stats_update_end(&pcpu_stats->syncp);

		skb->dev = team->dev;
	पूर्ण अन्यथा अगर (res == RX_HANDLER_EXACT) अणु
		this_cpu_inc(team->pcpu_stats->rx_nohandler);
	पूर्ण अन्यथा अणु
		this_cpu_inc(team->pcpu_stats->rx_dropped);
	पूर्ण

	वापस res;
पूर्ण


/*************************************
 * Multiqueue Tx port select override
 *************************************/

अटल पूर्णांक team_queue_override_init(काष्ठा team *team)
अणु
	काष्ठा list_head *listarr;
	अचिन्हित पूर्णांक queue_cnt = team->dev->num_tx_queues - 1;
	अचिन्हित पूर्णांक i;

	अगर (!queue_cnt)
		वापस 0;
	listarr = kदो_स्मृति_array(queue_cnt, माप(काष्ठा list_head),
				GFP_KERNEL);
	अगर (!listarr)
		वापस -ENOMEM;
	team->qom_lists = listarr;
	क्रम (i = 0; i < queue_cnt; i++)
		INIT_LIST_HEAD(listarr++);
	वापस 0;
पूर्ण

अटल व्योम team_queue_override_fini(काष्ठा team *team)
अणु
	kमुक्त(team->qom_lists);
पूर्ण

अटल काष्ठा list_head *__team_get_qom_list(काष्ठा team *team, u16 queue_id)
अणु
	वापस &team->qom_lists[queue_id - 1];
पूर्ण

/*
 * note: alपढ़ोy called with rcu_पढ़ो_lock
 */
अटल bool team_queue_override_transmit(काष्ठा team *team, काष्ठा sk_buff *skb)
अणु
	काष्ठा list_head *qom_list;
	काष्ठा team_port *port;

	अगर (!team->queue_override_enabled || !skb->queue_mapping)
		वापस false;
	qom_list = __team_get_qom_list(team, skb->queue_mapping);
	list_क्रम_each_entry_rcu(port, qom_list, qom_list) अणु
		अगर (!team_dev_queue_xmit(team, port, skb))
			वापस true;
	पूर्ण
	वापस false;
पूर्ण

अटल व्योम __team_queue_override_port_del(काष्ठा team *team,
					   काष्ठा team_port *port)
अणु
	अगर (!port->queue_id)
		वापस;
	list_del_rcu(&port->qom_list);
पूर्ण

अटल bool team_queue_override_port_has_gt_prio_than(काष्ठा team_port *port,
						      काष्ठा team_port *cur)
अणु
	अगर (port->priority < cur->priority)
		वापस true;
	अगर (port->priority > cur->priority)
		वापस false;
	अगर (port->index < cur->index)
		वापस true;
	वापस false;
पूर्ण

अटल व्योम __team_queue_override_port_add(काष्ठा team *team,
					   काष्ठा team_port *port)
अणु
	काष्ठा team_port *cur;
	काष्ठा list_head *qom_list;
	काष्ठा list_head *node;

	अगर (!port->queue_id)
		वापस;
	qom_list = __team_get_qom_list(team, port->queue_id);
	node = qom_list;
	list_क्रम_each_entry(cur, qom_list, qom_list) अणु
		अगर (team_queue_override_port_has_gt_prio_than(port, cur))
			अवरोध;
		node = &cur->qom_list;
	पूर्ण
	list_add_tail_rcu(&port->qom_list, node);
पूर्ण

अटल व्योम __team_queue_override_enabled_check(काष्ठा team *team)
अणु
	काष्ठा team_port *port;
	bool enabled = false;

	list_क्रम_each_entry(port, &team->port_list, list) अणु
		अगर (port->queue_id) अणु
			enabled = true;
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (enabled == team->queue_override_enabled)
		वापस;
	netdev_dbg(team->dev, "%s queue override\n",
		   enabled ? "Enabling" : "Disabling");
	team->queue_override_enabled = enabled;
पूर्ण

अटल व्योम team_queue_override_port_prio_changed(काष्ठा team *team,
						  काष्ठा team_port *port)
अणु
	अगर (!port->queue_id || team_port_enabled(port))
		वापस;
	__team_queue_override_port_del(team, port);
	__team_queue_override_port_add(team, port);
	__team_queue_override_enabled_check(team);
पूर्ण

अटल व्योम team_queue_override_port_change_queue_id(काष्ठा team *team,
						     काष्ठा team_port *port,
						     u16 new_queue_id)
अणु
	अगर (team_port_enabled(port)) अणु
		__team_queue_override_port_del(team, port);
		port->queue_id = new_queue_id;
		__team_queue_override_port_add(team, port);
		__team_queue_override_enabled_check(team);
	पूर्ण अन्यथा अणु
		port->queue_id = new_queue_id;
	पूर्ण
पूर्ण

अटल व्योम team_queue_override_port_add(काष्ठा team *team,
					 काष्ठा team_port *port)
अणु
	__team_queue_override_port_add(team, port);
	__team_queue_override_enabled_check(team);
पूर्ण

अटल व्योम team_queue_override_port_del(काष्ठा team *team,
					 काष्ठा team_port *port)
अणु
	__team_queue_override_port_del(team, port);
	__team_queue_override_enabled_check(team);
पूर्ण


/****************
 * Port handling
 ****************/

अटल bool team_port_find(स्थिर काष्ठा team *team,
			   स्थिर काष्ठा team_port *port)
अणु
	काष्ठा team_port *cur;

	list_क्रम_each_entry(cur, &team->port_list, list)
		अगर (cur == port)
			वापस true;
	वापस false;
पूर्ण

/*
 * Enable/disable port by adding to enabled port hashlist and setting
 * port->index (Might be racy so पढ़ोer could see incorrect अगरindex when
 * processing a flying packet, but that is not a problem). Write guarded
 * by team->lock.
 */
अटल व्योम team_port_enable(काष्ठा team *team,
			     काष्ठा team_port *port)
अणु
	अगर (team_port_enabled(port))
		वापस;
	port->index = team->en_port_count++;
	hlist_add_head_rcu(&port->hlist,
			   team_port_index_hash(team, port->index));
	team_adjust_ops(team);
	team_queue_override_port_add(team, port);
	अगर (team->ops.port_enabled)
		team->ops.port_enabled(team, port);
	team_notअगरy_peers(team);
	team_mcast_rejoin(team);
	team_lower_state_changed(port);
पूर्ण

अटल व्योम __reस्थिरruct_port_hlist(काष्ठा team *team, पूर्णांक rm_index)
अणु
	पूर्णांक i;
	काष्ठा team_port *port;

	क्रम (i = rm_index + 1; i < team->en_port_count; i++) अणु
		port = team_get_port_by_index(team, i);
		hlist_del_rcu(&port->hlist);
		port->index--;
		hlist_add_head_rcu(&port->hlist,
				   team_port_index_hash(team, port->index));
	पूर्ण
पूर्ण

अटल व्योम team_port_disable(काष्ठा team *team,
			      काष्ठा team_port *port)
अणु
	अगर (!team_port_enabled(port))
		वापस;
	अगर (team->ops.port_disabled)
		team->ops.port_disabled(team, port);
	hlist_del_rcu(&port->hlist);
	__reस्थिरruct_port_hlist(team, port->index);
	port->index = -1;
	team->en_port_count--;
	team_queue_override_port_del(team, port);
	team_adjust_ops(team);
	team_lower_state_changed(port);
पूर्ण

#घोषणा TEAM_VLAN_FEATURES (NETIF_F_HW_CSUM | NETIF_F_SG | \
			    NETIF_F_FRAGLIST | NETIF_F_GSO_SOFTWARE | \
			    NETIF_F_HIGHDMA | NETIF_F_LRO)

#घोषणा TEAM_ENC_FEATURES	(NETIF_F_HW_CSUM | NETIF_F_SG | \
				 NETIF_F_RXCSUM | NETIF_F_GSO_SOFTWARE)

अटल व्योम __team_compute_features(काष्ठा team *team)
अणु
	काष्ठा team_port *port;
	netdev_features_t vlan_features = TEAM_VLAN_FEATURES &
					  NETIF_F_ALL_FOR_ALL;
	netdev_features_t enc_features  = TEAM_ENC_FEATURES;
	अचिन्हित लघु max_hard_header_len = ETH_HLEN;
	अचिन्हित पूर्णांक dst_release_flag = IFF_XMIT_DST_RELEASE |
					IFF_XMIT_DST_RELEASE_PERM;

	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(port, &team->port_list, list) अणु
		vlan_features = netdev_increment_features(vlan_features,
					port->dev->vlan_features,
					TEAM_VLAN_FEATURES);
		enc_features =
			netdev_increment_features(enc_features,
						  port->dev->hw_enc_features,
						  TEAM_ENC_FEATURES);


		dst_release_flag &= port->dev->priv_flags;
		अगर (port->dev->hard_header_len > max_hard_header_len)
			max_hard_header_len = port->dev->hard_header_len;
	पूर्ण
	rcu_पढ़ो_unlock();

	team->dev->vlan_features = vlan_features;
	team->dev->hw_enc_features = enc_features | NETIF_F_GSO_ENCAP_ALL |
				     NETIF_F_HW_VLAN_CTAG_TX |
				     NETIF_F_HW_VLAN_STAG_TX;
	team->dev->hard_header_len = max_hard_header_len;

	team->dev->priv_flags &= ~IFF_XMIT_DST_RELEASE;
	अगर (dst_release_flag == (IFF_XMIT_DST_RELEASE | IFF_XMIT_DST_RELEASE_PERM))
		team->dev->priv_flags |= IFF_XMIT_DST_RELEASE;
पूर्ण

अटल व्योम team_compute_features(काष्ठा team *team)
अणु
	__team_compute_features(team);
	netdev_change_features(team->dev);
पूर्ण

अटल पूर्णांक team_port_enter(काष्ठा team *team, काष्ठा team_port *port)
अणु
	पूर्णांक err = 0;

	dev_hold(team->dev);
	अगर (team->ops.port_enter) अणु
		err = team->ops.port_enter(team, port);
		अगर (err) अणु
			netdev_err(team->dev, "Device %s failed to enter team mode\n",
				   port->dev->name);
			जाओ err_port_enter;
		पूर्ण
	पूर्ण

	वापस 0;

err_port_enter:
	dev_put(team->dev);

	वापस err;
पूर्ण

अटल व्योम team_port_leave(काष्ठा team *team, काष्ठा team_port *port)
अणु
	अगर (team->ops.port_leave)
		team->ops.port_leave(team, port);
	dev_put(team->dev);
पूर्ण

#अगर_घोषित CONFIG_NET_POLL_CONTROLLER
अटल पूर्णांक __team_port_enable_netpoll(काष्ठा team_port *port)
अणु
	काष्ठा netpoll *np;
	पूर्णांक err;

	np = kzalloc(माप(*np), GFP_KERNEL);
	अगर (!np)
		वापस -ENOMEM;

	err = __netpoll_setup(np, port->dev);
	अगर (err) अणु
		kमुक्त(np);
		वापस err;
	पूर्ण
	port->np = np;
	वापस err;
पूर्ण

अटल पूर्णांक team_port_enable_netpoll(काष्ठा team_port *port)
अणु
	अगर (!port->team->dev->npinfo)
		वापस 0;

	वापस __team_port_enable_netpoll(port);
पूर्ण

अटल व्योम team_port_disable_netpoll(काष्ठा team_port *port)
अणु
	काष्ठा netpoll *np = port->np;

	अगर (!np)
		वापस;
	port->np = शून्य;

	__netpoll_मुक्त(np);
पूर्ण
#अन्यथा
अटल पूर्णांक team_port_enable_netpoll(काष्ठा team_port *port)
अणु
	वापस 0;
पूर्ण
अटल व्योम team_port_disable_netpoll(काष्ठा team_port *port)
अणु
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक team_upper_dev_link(काष्ठा team *team, काष्ठा team_port *port,
			       काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा netdev_lag_upper_info lag_upper_info;
	पूर्णांक err;

	lag_upper_info.tx_type = team->mode->lag_tx_type;
	lag_upper_info.hash_type = NETDEV_LAG_HASH_UNKNOWN;
	err = netdev_master_upper_dev_link(port->dev, team->dev, शून्य,
					   &lag_upper_info, extack);
	अगर (err)
		वापस err;
	port->dev->priv_flags |= IFF_TEAM_PORT;
	वापस 0;
पूर्ण

अटल व्योम team_upper_dev_unlink(काष्ठा team *team, काष्ठा team_port *port)
अणु
	netdev_upper_dev_unlink(port->dev, team->dev);
	port->dev->priv_flags &= ~IFF_TEAM_PORT;
पूर्ण

अटल व्योम __team_port_change_port_added(काष्ठा team_port *port, bool linkup);
अटल पूर्णांक team_dev_type_check_change(काष्ठा net_device *dev,
				      काष्ठा net_device *port_dev);

अटल पूर्णांक team_port_add(काष्ठा team *team, काष्ठा net_device *port_dev,
			 काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा net_device *dev = team->dev;
	काष्ठा team_port *port;
	अक्षर *portname = port_dev->name;
	पूर्णांक err;

	अगर (port_dev->flags & IFF_LOOPBACK) अणु
		NL_SET_ERR_MSG(extack, "Loopback device can't be added as a team port");
		netdev_err(dev, "Device %s is loopback device. Loopback devices can't be added as a team port\n",
			   portname);
		वापस -EINVAL;
	पूर्ण

	अगर (netअगर_is_team_port(port_dev)) अणु
		NL_SET_ERR_MSG(extack, "Device is already a port of a team device");
		netdev_err(dev, "Device %s is already a port "
				"of a team device\n", portname);
		वापस -EBUSY;
	पूर्ण

	अगर (dev == port_dev) अणु
		NL_SET_ERR_MSG(extack, "Cannot enslave team device to itself");
		netdev_err(dev, "Cannot enslave team device to itself\n");
		वापस -EINVAL;
	पूर्ण

	अगर (netdev_has_upper_dev(dev, port_dev)) अणु
		NL_SET_ERR_MSG(extack, "Device is already an upper device of the team interface");
		netdev_err(dev, "Device %s is already an upper device of the team interface\n",
			   portname);
		वापस -EBUSY;
	पूर्ण

	अगर (port_dev->features & NETIF_F_VLAN_CHALLENGED &&
	    vlan_uses_dev(dev)) अणु
		NL_SET_ERR_MSG(extack, "Device is VLAN challenged and team device has VLAN set up");
		netdev_err(dev, "Device %s is VLAN challenged and team device has VLAN set up\n",
			   portname);
		वापस -EPERM;
	पूर्ण

	err = team_dev_type_check_change(dev, port_dev);
	अगर (err)
		वापस err;

	अगर (port_dev->flags & IFF_UP) अणु
		NL_SET_ERR_MSG(extack, "Device is up. Set it down before adding it as a team port");
		netdev_err(dev, "Device %s is up. Set it down before adding it as a team port\n",
			   portname);
		वापस -EBUSY;
	पूर्ण

	port = kzalloc(माप(काष्ठा team_port) + team->mode->port_priv_size,
		       GFP_KERNEL);
	अगर (!port)
		वापस -ENOMEM;

	port->dev = port_dev;
	port->team = team;
	INIT_LIST_HEAD(&port->qom_list);

	port->orig.mtu = port_dev->mtu;
	err = dev_set_mtu(port_dev, dev->mtu);
	अगर (err) अणु
		netdev_dbg(dev, "Error %d calling dev_set_mtu\n", err);
		जाओ err_set_mtu;
	पूर्ण

	स_नकल(port->orig.dev_addr, port_dev->dev_addr, port_dev->addr_len);

	err = team_port_enter(team, port);
	अगर (err) अणु
		netdev_err(dev, "Device %s failed to enter team mode\n",
			   portname);
		जाओ err_port_enter;
	पूर्ण

	err = dev_खोलो(port_dev, extack);
	अगर (err) अणु
		netdev_dbg(dev, "Device %s opening failed\n",
			   portname);
		जाओ err_dev_खोलो;
	पूर्ण

	err = vlan_vids_add_by_dev(port_dev, dev);
	अगर (err) अणु
		netdev_err(dev, "Failed to add vlan ids to device %s\n",
				portname);
		जाओ err_vids_add;
	पूर्ण

	err = team_port_enable_netpoll(port);
	अगर (err) अणु
		netdev_err(dev, "Failed to enable netpoll on device %s\n",
			   portname);
		जाओ err_enable_netpoll;
	पूर्ण

	अगर (!(dev->features & NETIF_F_LRO))
		dev_disable_lro(port_dev);

	err = netdev_rx_handler_रेजिस्टर(port_dev, team_handle_frame,
					 port);
	अगर (err) अणु
		netdev_err(dev, "Device %s failed to register rx_handler\n",
			   portname);
		जाओ err_handler_रेजिस्टर;
	पूर्ण

	err = team_upper_dev_link(team, port, extack);
	अगर (err) अणु
		netdev_err(dev, "Device %s failed to set upper link\n",
			   portname);
		जाओ err_set_upper_link;
	पूर्ण

	err = __team_option_inst_add_port(team, port);
	अगर (err) अणु
		netdev_err(dev, "Device %s failed to add per-port options\n",
			   portname);
		जाओ err_option_port_add;
	पूर्ण

	/* set promiscuity level to new slave */
	अगर (dev->flags & IFF_PROMISC) अणु
		err = dev_set_promiscuity(port_dev, 1);
		अगर (err)
			जाओ err_set_slave_promisc;
	पूर्ण

	/* set allmulti level to new slave */
	अगर (dev->flags & IFF_ALLMULTI) अणु
		err = dev_set_allmulti(port_dev, 1);
		अगर (err) अणु
			अगर (dev->flags & IFF_PROMISC)
				dev_set_promiscuity(port_dev, -1);
			जाओ err_set_slave_promisc;
		पूर्ण
	पूर्ण

	netअगर_addr_lock_bh(dev);
	dev_uc_sync_multiple(port_dev, dev);
	dev_mc_sync_multiple(port_dev, dev);
	netअगर_addr_unlock_bh(dev);

	port->index = -1;
	list_add_tail_rcu(&port->list, &team->port_list);
	team_port_enable(team, port);
	__team_compute_features(team);
	__team_port_change_port_added(port, !!netअगर_oper_up(port_dev));
	__team_options_change_check(team);

	netdev_info(dev, "Port device %s added\n", portname);

	वापस 0;

err_set_slave_promisc:
	__team_option_inst_del_port(team, port);

err_option_port_add:
	team_upper_dev_unlink(team, port);

err_set_upper_link:
	netdev_rx_handler_unरेजिस्टर(port_dev);

err_handler_रेजिस्टर:
	team_port_disable_netpoll(port);

err_enable_netpoll:
	vlan_vids_del_by_dev(port_dev, dev);

err_vids_add:
	dev_बंद(port_dev);

err_dev_खोलो:
	team_port_leave(team, port);
	team_port_set_orig_dev_addr(port);

err_port_enter:
	dev_set_mtu(port_dev, port->orig.mtu);

err_set_mtu:
	kमुक्त(port);

	वापस err;
पूर्ण

अटल व्योम __team_port_change_port_हटाओd(काष्ठा team_port *port);

अटल पूर्णांक team_port_del(काष्ठा team *team, काष्ठा net_device *port_dev)
अणु
	काष्ठा net_device *dev = team->dev;
	काष्ठा team_port *port;
	अक्षर *portname = port_dev->name;

	port = team_port_get_rtnl(port_dev);
	अगर (!port || !team_port_find(team, port)) अणु
		netdev_err(dev, "Device %s does not act as a port of this team\n",
			   portname);
		वापस -ENOENT;
	पूर्ण

	team_port_disable(team, port);
	list_del_rcu(&port->list);

	अगर (dev->flags & IFF_PROMISC)
		dev_set_promiscuity(port_dev, -1);
	अगर (dev->flags & IFF_ALLMULTI)
		dev_set_allmulti(port_dev, -1);

	team_upper_dev_unlink(team, port);
	netdev_rx_handler_unरेजिस्टर(port_dev);
	team_port_disable_netpoll(port);
	vlan_vids_del_by_dev(port_dev, dev);
	dev_uc_unsync(port_dev, dev);
	dev_mc_unsync(port_dev, dev);
	dev_बंद(port_dev);
	team_port_leave(team, port);

	__team_option_inst_mark_हटाओd_port(team, port);
	__team_options_change_check(team);
	__team_option_inst_del_port(team, port);
	__team_port_change_port_हटाओd(port);

	team_port_set_orig_dev_addr(port);
	dev_set_mtu(port_dev, port->orig.mtu);
	kमुक्त_rcu(port, rcu);
	netdev_info(dev, "Port device %s removed\n", portname);
	__team_compute_features(team);

	वापस 0;
पूर्ण


/*****************
 * Net device ops
 *****************/

अटल पूर्णांक team_mode_option_get(काष्ठा team *team, काष्ठा team_gsetter_ctx *ctx)
अणु
	ctx->data.str_val = team->mode->kind;
	वापस 0;
पूर्ण

अटल पूर्णांक team_mode_option_set(काष्ठा team *team, काष्ठा team_gsetter_ctx *ctx)
अणु
	वापस team_change_mode(team, ctx->data.str_val);
पूर्ण

अटल पूर्णांक team_notअगरy_peers_count_get(काष्ठा team *team,
				       काष्ठा team_gsetter_ctx *ctx)
अणु
	ctx->data.u32_val = team->notअगरy_peers.count;
	वापस 0;
पूर्ण

अटल पूर्णांक team_notअगरy_peers_count_set(काष्ठा team *team,
				       काष्ठा team_gsetter_ctx *ctx)
अणु
	team->notअगरy_peers.count = ctx->data.u32_val;
	वापस 0;
पूर्ण

अटल पूर्णांक team_notअगरy_peers_पूर्णांकerval_get(काष्ठा team *team,
					  काष्ठा team_gsetter_ctx *ctx)
अणु
	ctx->data.u32_val = team->notअगरy_peers.पूर्णांकerval;
	वापस 0;
पूर्ण

अटल पूर्णांक team_notअगरy_peers_पूर्णांकerval_set(काष्ठा team *team,
					  काष्ठा team_gsetter_ctx *ctx)
अणु
	team->notअगरy_peers.पूर्णांकerval = ctx->data.u32_val;
	वापस 0;
पूर्ण

अटल पूर्णांक team_mcast_rejoin_count_get(काष्ठा team *team,
				       काष्ठा team_gsetter_ctx *ctx)
अणु
	ctx->data.u32_val = team->mcast_rejoin.count;
	वापस 0;
पूर्ण

अटल पूर्णांक team_mcast_rejoin_count_set(काष्ठा team *team,
				       काष्ठा team_gsetter_ctx *ctx)
अणु
	team->mcast_rejoin.count = ctx->data.u32_val;
	वापस 0;
पूर्ण

अटल पूर्णांक team_mcast_rejoin_पूर्णांकerval_get(काष्ठा team *team,
					  काष्ठा team_gsetter_ctx *ctx)
अणु
	ctx->data.u32_val = team->mcast_rejoin.पूर्णांकerval;
	वापस 0;
पूर्ण

अटल पूर्णांक team_mcast_rejoin_पूर्णांकerval_set(काष्ठा team *team,
					  काष्ठा team_gsetter_ctx *ctx)
अणु
	team->mcast_rejoin.पूर्णांकerval = ctx->data.u32_val;
	वापस 0;
पूर्ण

अटल पूर्णांक team_port_en_option_get(काष्ठा team *team,
				   काष्ठा team_gsetter_ctx *ctx)
अणु
	काष्ठा team_port *port = ctx->info->port;

	ctx->data.bool_val = team_port_enabled(port);
	वापस 0;
पूर्ण

अटल पूर्णांक team_port_en_option_set(काष्ठा team *team,
				   काष्ठा team_gsetter_ctx *ctx)
अणु
	काष्ठा team_port *port = ctx->info->port;

	अगर (ctx->data.bool_val)
		team_port_enable(team, port);
	अन्यथा
		team_port_disable(team, port);
	वापस 0;
पूर्ण

अटल पूर्णांक team_user_linkup_option_get(काष्ठा team *team,
				       काष्ठा team_gsetter_ctx *ctx)
अणु
	काष्ठा team_port *port = ctx->info->port;

	ctx->data.bool_val = port->user.linkup;
	वापस 0;
पूर्ण

अटल व्योम __team_carrier_check(काष्ठा team *team);

अटल पूर्णांक team_user_linkup_option_set(काष्ठा team *team,
				       काष्ठा team_gsetter_ctx *ctx)
अणु
	काष्ठा team_port *port = ctx->info->port;

	port->user.linkup = ctx->data.bool_val;
	team_refresh_port_linkup(port);
	__team_carrier_check(port->team);
	वापस 0;
पूर्ण

अटल पूर्णांक team_user_linkup_en_option_get(काष्ठा team *team,
					  काष्ठा team_gsetter_ctx *ctx)
अणु
	काष्ठा team_port *port = ctx->info->port;

	ctx->data.bool_val = port->user.linkup_enabled;
	वापस 0;
पूर्ण

अटल पूर्णांक team_user_linkup_en_option_set(काष्ठा team *team,
					  काष्ठा team_gsetter_ctx *ctx)
अणु
	काष्ठा team_port *port = ctx->info->port;

	port->user.linkup_enabled = ctx->data.bool_val;
	team_refresh_port_linkup(port);
	__team_carrier_check(port->team);
	वापस 0;
पूर्ण

अटल पूर्णांक team_priority_option_get(काष्ठा team *team,
				    काष्ठा team_gsetter_ctx *ctx)
अणु
	काष्ठा team_port *port = ctx->info->port;

	ctx->data.s32_val = port->priority;
	वापस 0;
पूर्ण

अटल पूर्णांक team_priority_option_set(काष्ठा team *team,
				    काष्ठा team_gsetter_ctx *ctx)
अणु
	काष्ठा team_port *port = ctx->info->port;
	s32 priority = ctx->data.s32_val;

	अगर (port->priority == priority)
		वापस 0;
	port->priority = priority;
	team_queue_override_port_prio_changed(team, port);
	वापस 0;
पूर्ण

अटल पूर्णांक team_queue_id_option_get(काष्ठा team *team,
				    काष्ठा team_gsetter_ctx *ctx)
अणु
	काष्ठा team_port *port = ctx->info->port;

	ctx->data.u32_val = port->queue_id;
	वापस 0;
पूर्ण

अटल पूर्णांक team_queue_id_option_set(काष्ठा team *team,
				    काष्ठा team_gsetter_ctx *ctx)
अणु
	काष्ठा team_port *port = ctx->info->port;
	u16 new_queue_id = ctx->data.u32_val;

	अगर (port->queue_id == new_queue_id)
		वापस 0;
	अगर (new_queue_id >= team->dev->real_num_tx_queues)
		वापस -EINVAL;
	team_queue_override_port_change_queue_id(team, port, new_queue_id);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा team_option team_options[] = अणु
	अणु
		.name = "mode",
		.type = TEAM_OPTION_TYPE_STRING,
		.getter = team_mode_option_get,
		.setter = team_mode_option_set,
	पूर्ण,
	अणु
		.name = "notify_peers_count",
		.type = TEAM_OPTION_TYPE_U32,
		.getter = team_notअगरy_peers_count_get,
		.setter = team_notअगरy_peers_count_set,
	पूर्ण,
	अणु
		.name = "notify_peers_interval",
		.type = TEAM_OPTION_TYPE_U32,
		.getter = team_notअगरy_peers_पूर्णांकerval_get,
		.setter = team_notअगरy_peers_पूर्णांकerval_set,
	पूर्ण,
	अणु
		.name = "mcast_rejoin_count",
		.type = TEAM_OPTION_TYPE_U32,
		.getter = team_mcast_rejoin_count_get,
		.setter = team_mcast_rejoin_count_set,
	पूर्ण,
	अणु
		.name = "mcast_rejoin_interval",
		.type = TEAM_OPTION_TYPE_U32,
		.getter = team_mcast_rejoin_पूर्णांकerval_get,
		.setter = team_mcast_rejoin_पूर्णांकerval_set,
	पूर्ण,
	अणु
		.name = "enabled",
		.type = TEAM_OPTION_TYPE_BOOL,
		.per_port = true,
		.getter = team_port_en_option_get,
		.setter = team_port_en_option_set,
	पूर्ण,
	अणु
		.name = "user_linkup",
		.type = TEAM_OPTION_TYPE_BOOL,
		.per_port = true,
		.getter = team_user_linkup_option_get,
		.setter = team_user_linkup_option_set,
	पूर्ण,
	अणु
		.name = "user_linkup_enabled",
		.type = TEAM_OPTION_TYPE_BOOL,
		.per_port = true,
		.getter = team_user_linkup_en_option_get,
		.setter = team_user_linkup_en_option_set,
	पूर्ण,
	अणु
		.name = "priority",
		.type = TEAM_OPTION_TYPE_S32,
		.per_port = true,
		.getter = team_priority_option_get,
		.setter = team_priority_option_set,
	पूर्ण,
	अणु
		.name = "queue_id",
		.type = TEAM_OPTION_TYPE_U32,
		.per_port = true,
		.getter = team_queue_id_option_get,
		.setter = team_queue_id_option_set,
	पूर्ण,
पूर्ण;


अटल पूर्णांक team_init(काष्ठा net_device *dev)
अणु
	काष्ठा team *team = netdev_priv(dev);
	पूर्णांक i;
	पूर्णांक err;

	team->dev = dev;
	team_set_no_mode(team);

	team->pcpu_stats = netdev_alloc_pcpu_stats(काष्ठा team_pcpu_stats);
	अगर (!team->pcpu_stats)
		वापस -ENOMEM;

	क्रम (i = 0; i < TEAM_PORT_HASHENTRIES; i++)
		INIT_HLIST_HEAD(&team->en_port_hlist[i]);
	INIT_LIST_HEAD(&team->port_list);
	err = team_queue_override_init(team);
	अगर (err)
		जाओ err_team_queue_override_init;

	team_adjust_ops(team);

	INIT_LIST_HEAD(&team->option_list);
	INIT_LIST_HEAD(&team->option_inst_list);

	team_notअगरy_peers_init(team);
	team_mcast_rejoin_init(team);

	err = team_options_रेजिस्टर(team, team_options, ARRAY_SIZE(team_options));
	अगर (err)
		जाओ err_options_रेजिस्टर;
	netअगर_carrier_off(dev);

	lockdep_रेजिस्टर_key(&team->team_lock_key);
	__mutex_init(&team->lock, "team->team_lock_key", &team->team_lock_key);
	netdev_lockdep_set_classes(dev);

	वापस 0;

err_options_रेजिस्टर:
	team_mcast_rejoin_fini(team);
	team_notअगरy_peers_fini(team);
	team_queue_override_fini(team);
err_team_queue_override_init:
	मुक्त_percpu(team->pcpu_stats);

	वापस err;
पूर्ण

अटल व्योम team_uninit(काष्ठा net_device *dev)
अणु
	काष्ठा team *team = netdev_priv(dev);
	काष्ठा team_port *port;
	काष्ठा team_port *पंचांगp;

	mutex_lock(&team->lock);
	list_क्रम_each_entry_safe(port, पंचांगp, &team->port_list, list)
		team_port_del(team, port->dev);

	__team_change_mode(team, शून्य); /* cleanup */
	__team_options_unरेजिस्टर(team, team_options, ARRAY_SIZE(team_options));
	team_mcast_rejoin_fini(team);
	team_notअगरy_peers_fini(team);
	team_queue_override_fini(team);
	mutex_unlock(&team->lock);
	netdev_change_features(dev);
	lockdep_unरेजिस्टर_key(&team->team_lock_key);
पूर्ण

अटल व्योम team_deकाष्ठाor(काष्ठा net_device *dev)
अणु
	काष्ठा team *team = netdev_priv(dev);

	मुक्त_percpu(team->pcpu_stats);
पूर्ण

अटल पूर्णांक team_खोलो(काष्ठा net_device *dev)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक team_बंद(काष्ठा net_device *dev)
अणु
	वापस 0;
पूर्ण

/*
 * note: alपढ़ोy called with rcu_पढ़ो_lock
 */
अटल netdev_tx_t team_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *dev)
अणु
	काष्ठा team *team = netdev_priv(dev);
	bool tx_success;
	अचिन्हित पूर्णांक len = skb->len;

	tx_success = team_queue_override_transmit(team, skb);
	अगर (!tx_success)
		tx_success = team->ops.transmit(team, skb);
	अगर (tx_success) अणु
		काष्ठा team_pcpu_stats *pcpu_stats;

		pcpu_stats = this_cpu_ptr(team->pcpu_stats);
		u64_stats_update_begin(&pcpu_stats->syncp);
		pcpu_stats->tx_packets++;
		pcpu_stats->tx_bytes += len;
		u64_stats_update_end(&pcpu_stats->syncp);
	पूर्ण अन्यथा अणु
		this_cpu_inc(team->pcpu_stats->tx_dropped);
	पूर्ण

	वापस NETDEV_TX_OK;
पूर्ण

अटल u16 team_select_queue(काष्ठा net_device *dev, काष्ठा sk_buff *skb,
			     काष्ठा net_device *sb_dev)
अणु
	/*
	 * This helper function exists to help dev_pick_tx get the correct
	 * destination queue.  Using a helper function skips a call to
	 * skb_tx_hash and will put the skbs in the queue we expect on their
	 * way करोwn to the team driver.
	 */
	u16 txq = skb_rx_queue_recorded(skb) ? skb_get_rx_queue(skb) : 0;

	/*
	 * Save the original txq to restore beक्रमe passing to the driver
	 */
	qdisc_skb_cb(skb)->slave_dev_queue_mapping = skb->queue_mapping;

	अगर (unlikely(txq >= dev->real_num_tx_queues)) अणु
		करो अणु
			txq -= dev->real_num_tx_queues;
		पूर्ण जबतक (txq >= dev->real_num_tx_queues);
	पूर्ण
	वापस txq;
पूर्ण

अटल व्योम team_change_rx_flags(काष्ठा net_device *dev, पूर्णांक change)
अणु
	काष्ठा team *team = netdev_priv(dev);
	काष्ठा team_port *port;
	पूर्णांक inc;

	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(port, &team->port_list, list) अणु
		अगर (change & IFF_PROMISC) अणु
			inc = dev->flags & IFF_PROMISC ? 1 : -1;
			dev_set_promiscuity(port->dev, inc);
		पूर्ण
		अगर (change & IFF_ALLMULTI) अणु
			inc = dev->flags & IFF_ALLMULTI ? 1 : -1;
			dev_set_allmulti(port->dev, inc);
		पूर्ण
	पूर्ण
	rcu_पढ़ो_unlock();
पूर्ण

अटल व्योम team_set_rx_mode(काष्ठा net_device *dev)
अणु
	काष्ठा team *team = netdev_priv(dev);
	काष्ठा team_port *port;

	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(port, &team->port_list, list) अणु
		dev_uc_sync_multiple(port->dev, dev);
		dev_mc_sync_multiple(port->dev, dev);
	पूर्ण
	rcu_पढ़ो_unlock();
पूर्ण

अटल पूर्णांक team_set_mac_address(काष्ठा net_device *dev, व्योम *p)
अणु
	काष्ठा sockaddr *addr = p;
	काष्ठा team *team = netdev_priv(dev);
	काष्ठा team_port *port;

	अगर (dev->type == ARPHRD_ETHER && !is_valid_ether_addr(addr->sa_data))
		वापस -EADDRNOTAVAIL;
	स_नकल(dev->dev_addr, addr->sa_data, dev->addr_len);
	mutex_lock(&team->lock);
	list_क्रम_each_entry(port, &team->port_list, list)
		अगर (team->ops.port_change_dev_addr)
			team->ops.port_change_dev_addr(team, port);
	mutex_unlock(&team->lock);
	वापस 0;
पूर्ण

अटल पूर्णांक team_change_mtu(काष्ठा net_device *dev, पूर्णांक new_mtu)
अणु
	काष्ठा team *team = netdev_priv(dev);
	काष्ठा team_port *port;
	पूर्णांक err;

	/*
	 * Alhough this is पढ़ोer, it's guarded by team lock. It's not possible
	 * to traverse list in reverse under rcu_पढ़ो_lock
	 */
	mutex_lock(&team->lock);
	team->port_mtu_change_allowed = true;
	list_क्रम_each_entry(port, &team->port_list, list) अणु
		err = dev_set_mtu(port->dev, new_mtu);
		अगर (err) अणु
			netdev_err(dev, "Device %s failed to change mtu",
				   port->dev->name);
			जाओ unwind;
		पूर्ण
	पूर्ण
	team->port_mtu_change_allowed = false;
	mutex_unlock(&team->lock);

	dev->mtu = new_mtu;

	वापस 0;

unwind:
	list_क्रम_each_entry_जारी_reverse(port, &team->port_list, list)
		dev_set_mtu(port->dev, dev->mtu);
	team->port_mtu_change_allowed = false;
	mutex_unlock(&team->lock);

	वापस err;
पूर्ण

अटल व्योम
team_get_stats64(काष्ठा net_device *dev, काष्ठा rtnl_link_stats64 *stats)
अणु
	काष्ठा team *team = netdev_priv(dev);
	काष्ठा team_pcpu_stats *p;
	u64 rx_packets, rx_bytes, rx_multicast, tx_packets, tx_bytes;
	u32 rx_dropped = 0, tx_dropped = 0, rx_nohandler = 0;
	अचिन्हित पूर्णांक start;
	पूर्णांक i;

	क्रम_each_possible_cpu(i) अणु
		p = per_cpu_ptr(team->pcpu_stats, i);
		करो अणु
			start = u64_stats_fetch_begin_irq(&p->syncp);
			rx_packets	= p->rx_packets;
			rx_bytes	= p->rx_bytes;
			rx_multicast	= p->rx_multicast;
			tx_packets	= p->tx_packets;
			tx_bytes	= p->tx_bytes;
		पूर्ण जबतक (u64_stats_fetch_retry_irq(&p->syncp, start));

		stats->rx_packets	+= rx_packets;
		stats->rx_bytes		+= rx_bytes;
		stats->multicast	+= rx_multicast;
		stats->tx_packets	+= tx_packets;
		stats->tx_bytes		+= tx_bytes;
		/*
		 * rx_dropped, tx_dropped & rx_nohandler are u32,
		 * updated without syncp protection.
		 */
		rx_dropped	+= p->rx_dropped;
		tx_dropped	+= p->tx_dropped;
		rx_nohandler	+= p->rx_nohandler;
	पूर्ण
	stats->rx_dropped	= rx_dropped;
	stats->tx_dropped	= tx_dropped;
	stats->rx_nohandler	= rx_nohandler;
पूर्ण

अटल पूर्णांक team_vlan_rx_add_vid(काष्ठा net_device *dev, __be16 proto, u16 vid)
अणु
	काष्ठा team *team = netdev_priv(dev);
	काष्ठा team_port *port;
	पूर्णांक err;

	/*
	 * Alhough this is पढ़ोer, it's guarded by team lock. It's not possible
	 * to traverse list in reverse under rcu_पढ़ो_lock
	 */
	mutex_lock(&team->lock);
	list_क्रम_each_entry(port, &team->port_list, list) अणु
		err = vlan_vid_add(port->dev, proto, vid);
		अगर (err)
			जाओ unwind;
	पूर्ण
	mutex_unlock(&team->lock);

	वापस 0;

unwind:
	list_क्रम_each_entry_जारी_reverse(port, &team->port_list, list)
		vlan_vid_del(port->dev, proto, vid);
	mutex_unlock(&team->lock);

	वापस err;
पूर्ण

अटल पूर्णांक team_vlan_rx_समाप्त_vid(काष्ठा net_device *dev, __be16 proto, u16 vid)
अणु
	काष्ठा team *team = netdev_priv(dev);
	काष्ठा team_port *port;

	mutex_lock(&team->lock);
	list_क्रम_each_entry(port, &team->port_list, list)
		vlan_vid_del(port->dev, proto, vid);
	mutex_unlock(&team->lock);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_NET_POLL_CONTROLLER
अटल व्योम team_poll_controller(काष्ठा net_device *dev)
अणु
पूर्ण

अटल व्योम __team_netpoll_cleanup(काष्ठा team *team)
अणु
	काष्ठा team_port *port;

	list_क्रम_each_entry(port, &team->port_list, list)
		team_port_disable_netpoll(port);
पूर्ण

अटल व्योम team_netpoll_cleanup(काष्ठा net_device *dev)
अणु
	काष्ठा team *team = netdev_priv(dev);

	mutex_lock(&team->lock);
	__team_netpoll_cleanup(team);
	mutex_unlock(&team->lock);
पूर्ण

अटल पूर्णांक team_netpoll_setup(काष्ठा net_device *dev,
			      काष्ठा netpoll_info *npअगरo)
अणु
	काष्ठा team *team = netdev_priv(dev);
	काष्ठा team_port *port;
	पूर्णांक err = 0;

	mutex_lock(&team->lock);
	list_क्रम_each_entry(port, &team->port_list, list) अणु
		err = __team_port_enable_netpoll(port);
		अगर (err) अणु
			__team_netpoll_cleanup(team);
			अवरोध;
		पूर्ण
	पूर्ण
	mutex_unlock(&team->lock);
	वापस err;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक team_add_slave(काष्ठा net_device *dev, काष्ठा net_device *port_dev,
			  काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा team *team = netdev_priv(dev);
	पूर्णांक err;

	mutex_lock(&team->lock);
	err = team_port_add(team, port_dev, extack);
	mutex_unlock(&team->lock);

	अगर (!err)
		netdev_change_features(dev);

	वापस err;
पूर्ण

अटल पूर्णांक team_del_slave(काष्ठा net_device *dev, काष्ठा net_device *port_dev)
अणु
	काष्ठा team *team = netdev_priv(dev);
	पूर्णांक err;

	mutex_lock(&team->lock);
	err = team_port_del(team, port_dev);
	mutex_unlock(&team->lock);

	अगर (err)
		वापस err;

	अगर (netअगर_is_team_master(port_dev)) अणु
		lockdep_unरेजिस्टर_key(&team->team_lock_key);
		lockdep_रेजिस्टर_key(&team->team_lock_key);
		lockdep_set_class(&team->lock, &team->team_lock_key);
	पूर्ण
	netdev_change_features(dev);

	वापस err;
पूर्ण

अटल netdev_features_t team_fix_features(काष्ठा net_device *dev,
					   netdev_features_t features)
अणु
	काष्ठा team_port *port;
	काष्ठा team *team = netdev_priv(dev);
	netdev_features_t mask;

	mask = features;
	features &= ~NETIF_F_ONE_FOR_ALL;
	features |= NETIF_F_ALL_FOR_ALL;

	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(port, &team->port_list, list) अणु
		features = netdev_increment_features(features,
						     port->dev->features,
						     mask);
	पूर्ण
	rcu_पढ़ो_unlock();

	features = netdev_add_tso_features(features, mask);

	वापस features;
पूर्ण

अटल पूर्णांक team_change_carrier(काष्ठा net_device *dev, bool new_carrier)
अणु
	काष्ठा team *team = netdev_priv(dev);

	team->user_carrier_enabled = true;

	अगर (new_carrier)
		netअगर_carrier_on(dev);
	अन्यथा
		netअगर_carrier_off(dev);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा net_device_ops team_netdev_ops = अणु
	.nकरो_init		= team_init,
	.nकरो_uninit		= team_uninit,
	.nकरो_खोलो		= team_खोलो,
	.nकरो_stop		= team_बंद,
	.nकरो_start_xmit		= team_xmit,
	.nकरो_select_queue	= team_select_queue,
	.nकरो_change_rx_flags	= team_change_rx_flags,
	.nकरो_set_rx_mode	= team_set_rx_mode,
	.nकरो_set_mac_address	= team_set_mac_address,
	.nकरो_change_mtu		= team_change_mtu,
	.nकरो_get_stats64	= team_get_stats64,
	.nकरो_vlan_rx_add_vid	= team_vlan_rx_add_vid,
	.nकरो_vlan_rx_समाप्त_vid	= team_vlan_rx_समाप्त_vid,
#अगर_घोषित CONFIG_NET_POLL_CONTROLLER
	.nकरो_poll_controller	= team_poll_controller,
	.nकरो_netpoll_setup	= team_netpoll_setup,
	.nकरो_netpoll_cleanup	= team_netpoll_cleanup,
#पूर्ण_अगर
	.nकरो_add_slave		= team_add_slave,
	.nकरो_del_slave		= team_del_slave,
	.nकरो_fix_features	= team_fix_features,
	.nकरो_change_carrier     = team_change_carrier,
	.nकरो_features_check	= passthru_features_check,
पूर्ण;

/***********************
 * ethtool पूर्णांकerface
 ***********************/

अटल व्योम team_ethtool_get_drvinfo(काष्ठा net_device *dev,
				     काष्ठा ethtool_drvinfo *drvinfo)
अणु
	strlcpy(drvinfo->driver, DRV_NAME, माप(drvinfo->driver));
	strlcpy(drvinfo->version, UTS_RELEASE, माप(drvinfo->version));
पूर्ण

अटल पूर्णांक team_ethtool_get_link_ksettings(काष्ठा net_device *dev,
					   काष्ठा ethtool_link_ksettings *cmd)
अणु
	काष्ठा team *team= netdev_priv(dev);
	अचिन्हित दीर्घ speed = 0;
	काष्ठा team_port *port;

	cmd->base.duplex = DUPLEX_UNKNOWN;
	cmd->base.port = PORT_OTHER;

	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(port, &team->port_list, list) अणु
		अगर (team_port_txable(port)) अणु
			अगर (port->state.speed != SPEED_UNKNOWN)
				speed += port->state.speed;
			अगर (cmd->base.duplex == DUPLEX_UNKNOWN &&
			    port->state.duplex != DUPLEX_UNKNOWN)
				cmd->base.duplex = port->state.duplex;
		पूर्ण
	पूर्ण
	rcu_पढ़ो_unlock();

	cmd->base.speed = speed ? : SPEED_UNKNOWN;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा ethtool_ops team_ethtool_ops = अणु
	.get_drvinfo		= team_ethtool_get_drvinfo,
	.get_link		= ethtool_op_get_link,
	.get_link_ksettings	= team_ethtool_get_link_ksettings,
पूर्ण;

/***********************
 * rt netlink पूर्णांकerface
 ***********************/

अटल व्योम team_setup_by_port(काष्ठा net_device *dev,
			       काष्ठा net_device *port_dev)
अणु
	dev->header_ops	= port_dev->header_ops;
	dev->type = port_dev->type;
	dev->hard_header_len = port_dev->hard_header_len;
	dev->needed_headroom = port_dev->needed_headroom;
	dev->addr_len = port_dev->addr_len;
	dev->mtu = port_dev->mtu;
	स_नकल(dev->broadcast, port_dev->broadcast, port_dev->addr_len);
	eth_hw_addr_inherit(dev, port_dev);
पूर्ण

अटल पूर्णांक team_dev_type_check_change(काष्ठा net_device *dev,
				      काष्ठा net_device *port_dev)
अणु
	काष्ठा team *team = netdev_priv(dev);
	अक्षर *portname = port_dev->name;
	पूर्णांक err;

	अगर (dev->type == port_dev->type)
		वापस 0;
	अगर (!list_empty(&team->port_list)) अणु
		netdev_err(dev, "Device %s is of different type\n", portname);
		वापस -EBUSY;
	पूर्ण
	err = call_netdevice_notअगरiers(NETDEV_PRE_TYPE_CHANGE, dev);
	err = notअगरier_to_त्रुटि_सं(err);
	अगर (err) अणु
		netdev_err(dev, "Refused to change device type\n");
		वापस err;
	पूर्ण
	dev_uc_flush(dev);
	dev_mc_flush(dev);
	team_setup_by_port(dev, port_dev);
	call_netdevice_notअगरiers(NETDEV_POST_TYPE_CHANGE, dev);
	वापस 0;
पूर्ण

अटल व्योम team_setup(काष्ठा net_device *dev)
अणु
	ether_setup(dev);
	dev->max_mtu = ETH_MAX_MTU;

	dev->netdev_ops = &team_netdev_ops;
	dev->ethtool_ops = &team_ethtool_ops;
	dev->needs_मुक्त_netdev = true;
	dev->priv_deकाष्ठाor = team_deकाष्ठाor;
	dev->priv_flags &= ~(IFF_XMIT_DST_RELEASE | IFF_TX_SKB_SHARING);
	dev->priv_flags |= IFF_NO_QUEUE;
	dev->priv_flags |= IFF_TEAM;

	/*
	 * Indicate we support unicast address filtering. That way core won't
	 * bring us to promisc mode in हाल a unicast addr is added.
	 * Let this up to underlay drivers.
	 */
	dev->priv_flags |= IFF_UNICAST_FLT | IFF_LIVE_ADDR_CHANGE;

	dev->features |= NETIF_F_LLTX;
	dev->features |= NETIF_F_GRO;

	/* Don't allow team devices to change network namespaces. */
	dev->features |= NETIF_F_NETNS_LOCAL;

	dev->hw_features = TEAM_VLAN_FEATURES |
			   NETIF_F_HW_VLAN_CTAG_RX |
			   NETIF_F_HW_VLAN_CTAG_FILTER;

	dev->hw_features |= NETIF_F_GSO_ENCAP_ALL;
	dev->features |= dev->hw_features;
	dev->features |= NETIF_F_HW_VLAN_CTAG_TX | NETIF_F_HW_VLAN_STAG_TX;
पूर्ण

अटल पूर्णांक team_newlink(काष्ठा net *src_net, काष्ठा net_device *dev,
			काष्ठा nlattr *tb[], काष्ठा nlattr *data[],
			काष्ठा netlink_ext_ack *extack)
अणु
	अगर (tb[IFLA_ADDRESS] == शून्य)
		eth_hw_addr_अक्रमom(dev);

	वापस रेजिस्टर_netdevice(dev);
पूर्ण

अटल पूर्णांक team_validate(काष्ठा nlattr *tb[], काष्ठा nlattr *data[],
			 काष्ठा netlink_ext_ack *extack)
अणु
	अगर (tb[IFLA_ADDRESS]) अणु
		अगर (nla_len(tb[IFLA_ADDRESS]) != ETH_ALEN)
			वापस -EINVAL;
		अगर (!is_valid_ether_addr(nla_data(tb[IFLA_ADDRESS])))
			वापस -EADDRNOTAVAIL;
	पूर्ण
	वापस 0;
पूर्ण

अटल अचिन्हित पूर्णांक team_get_num_tx_queues(व्योम)
अणु
	वापस TEAM_DEFAULT_NUM_TX_QUEUES;
पूर्ण

अटल अचिन्हित पूर्णांक team_get_num_rx_queues(व्योम)
अणु
	वापस TEAM_DEFAULT_NUM_RX_QUEUES;
पूर्ण

अटल काष्ठा rtnl_link_ops team_link_ops __पढ़ो_mostly = अणु
	.kind			= DRV_NAME,
	.priv_size		= माप(काष्ठा team),
	.setup			= team_setup,
	.newlink		= team_newlink,
	.validate		= team_validate,
	.get_num_tx_queues	= team_get_num_tx_queues,
	.get_num_rx_queues	= team_get_num_rx_queues,
पूर्ण;


/***********************************
 * Generic netlink custom पूर्णांकerface
 ***********************************/

अटल काष्ठा genl_family team_nl_family;

अटल स्थिर काष्ठा nla_policy team_nl_policy[TEAM_ATTR_MAX + 1] = अणु
	[TEAM_ATTR_UNSPEC]			= अणु .type = NLA_UNSPEC, पूर्ण,
	[TEAM_ATTR_TEAM_IFINDEX]		= अणु .type = NLA_U32 पूर्ण,
	[TEAM_ATTR_LIST_OPTION]			= अणु .type = NLA_NESTED पूर्ण,
	[TEAM_ATTR_LIST_PORT]			= अणु .type = NLA_NESTED पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा nla_policy
team_nl_option_policy[TEAM_ATTR_OPTION_MAX + 1] = अणु
	[TEAM_ATTR_OPTION_UNSPEC]		= अणु .type = NLA_UNSPEC, पूर्ण,
	[TEAM_ATTR_OPTION_NAME] = अणु
		.type = NLA_STRING,
		.len = TEAM_STRING_MAX_LEN,
	पूर्ण,
	[TEAM_ATTR_OPTION_CHANGED]		= अणु .type = NLA_FLAG पूर्ण,
	[TEAM_ATTR_OPTION_TYPE]			= अणु .type = NLA_U8 पूर्ण,
	[TEAM_ATTR_OPTION_DATA]			= अणु .type = NLA_BINARY पूर्ण,
	[TEAM_ATTR_OPTION_PORT_IFINDEX]		= अणु .type = NLA_U32 पूर्ण,
	[TEAM_ATTR_OPTION_ARRAY_INDEX]		= अणु .type = NLA_U32 पूर्ण,
पूर्ण;

अटल पूर्णांक team_nl_cmd_noop(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	काष्ठा sk_buff *msg;
	व्योम *hdr;
	पूर्णांक err;

	msg = nlmsg_new(NLMSG_DEFAULT_SIZE, GFP_KERNEL);
	अगर (!msg)
		वापस -ENOMEM;

	hdr = genlmsg_put(msg, info->snd_portid, info->snd_seq,
			  &team_nl_family, 0, TEAM_CMD_NOOP);
	अगर (!hdr) अणु
		err = -EMSGSIZE;
		जाओ err_msg_put;
	पूर्ण

	genlmsg_end(msg, hdr);

	वापस genlmsg_unicast(genl_info_net(info), msg, info->snd_portid);

err_msg_put:
	nlmsg_मुक्त(msg);

	वापस err;
पूर्ण

/*
 * Netlink cmd functions should be locked by following two functions.
 * Since dev माला_लो held here, that ensures dev won't disappear in between.
 */
अटल काष्ठा team *team_nl_team_get(काष्ठा genl_info *info)
अणु
	काष्ठा net *net = genl_info_net(info);
	पूर्णांक अगरindex;
	काष्ठा net_device *dev;
	काष्ठा team *team;

	अगर (!info->attrs[TEAM_ATTR_TEAM_IFINDEX])
		वापस शून्य;

	अगरindex = nla_get_u32(info->attrs[TEAM_ATTR_TEAM_IFINDEX]);
	dev = dev_get_by_index(net, अगरindex);
	अगर (!dev || dev->netdev_ops != &team_netdev_ops) अणु
		अगर (dev)
			dev_put(dev);
		वापस शून्य;
	पूर्ण

	team = netdev_priv(dev);
	mutex_lock(&team->lock);
	वापस team;
पूर्ण

अटल व्योम team_nl_team_put(काष्ठा team *team)
अणु
	mutex_unlock(&team->lock);
	dev_put(team->dev);
पूर्ण

प्रकार पूर्णांक team_nl_send_func_t(काष्ठा sk_buff *skb,
				काष्ठा team *team, u32 portid);

अटल पूर्णांक team_nl_send_unicast(काष्ठा sk_buff *skb, काष्ठा team *team, u32 portid)
अणु
	वापस genlmsg_unicast(dev_net(team->dev), skb, portid);
पूर्ण

अटल पूर्णांक team_nl_fill_one_option_get(काष्ठा sk_buff *skb, काष्ठा team *team,
				       काष्ठा team_option_inst *opt_inst)
अणु
	काष्ठा nlattr *option_item;
	काष्ठा team_option *option = opt_inst->option;
	काष्ठा team_option_inst_info *opt_inst_info = &opt_inst->info;
	काष्ठा team_gsetter_ctx ctx;
	पूर्णांक err;

	ctx.info = opt_inst_info;
	err = team_option_get(team, opt_inst, &ctx);
	अगर (err)
		वापस err;

	option_item = nla_nest_start_noflag(skb, TEAM_ATTR_ITEM_OPTION);
	अगर (!option_item)
		वापस -EMSGSIZE;

	अगर (nla_put_string(skb, TEAM_ATTR_OPTION_NAME, option->name))
		जाओ nest_cancel;
	अगर (opt_inst_info->port &&
	    nla_put_u32(skb, TEAM_ATTR_OPTION_PORT_IFINDEX,
			opt_inst_info->port->dev->अगरindex))
		जाओ nest_cancel;
	अगर (opt_inst->option->array_size &&
	    nla_put_u32(skb, TEAM_ATTR_OPTION_ARRAY_INDEX,
			opt_inst_info->array_index))
		जाओ nest_cancel;

	चयन (option->type) अणु
	हाल TEAM_OPTION_TYPE_U32:
		अगर (nla_put_u8(skb, TEAM_ATTR_OPTION_TYPE, NLA_U32))
			जाओ nest_cancel;
		अगर (nla_put_u32(skb, TEAM_ATTR_OPTION_DATA, ctx.data.u32_val))
			जाओ nest_cancel;
		अवरोध;
	हाल TEAM_OPTION_TYPE_STRING:
		अगर (nla_put_u8(skb, TEAM_ATTR_OPTION_TYPE, NLA_STRING))
			जाओ nest_cancel;
		अगर (nla_put_string(skb, TEAM_ATTR_OPTION_DATA,
				   ctx.data.str_val))
			जाओ nest_cancel;
		अवरोध;
	हाल TEAM_OPTION_TYPE_BINARY:
		अगर (nla_put_u8(skb, TEAM_ATTR_OPTION_TYPE, NLA_BINARY))
			जाओ nest_cancel;
		अगर (nla_put(skb, TEAM_ATTR_OPTION_DATA, ctx.data.bin_val.len,
			    ctx.data.bin_val.ptr))
			जाओ nest_cancel;
		अवरोध;
	हाल TEAM_OPTION_TYPE_BOOL:
		अगर (nla_put_u8(skb, TEAM_ATTR_OPTION_TYPE, NLA_FLAG))
			जाओ nest_cancel;
		अगर (ctx.data.bool_val &&
		    nla_put_flag(skb, TEAM_ATTR_OPTION_DATA))
			जाओ nest_cancel;
		अवरोध;
	हाल TEAM_OPTION_TYPE_S32:
		अगर (nla_put_u8(skb, TEAM_ATTR_OPTION_TYPE, NLA_S32))
			जाओ nest_cancel;
		अगर (nla_put_s32(skb, TEAM_ATTR_OPTION_DATA, ctx.data.s32_val))
			जाओ nest_cancel;
		अवरोध;
	शेष:
		BUG();
	पूर्ण
	अगर (opt_inst->हटाओd && nla_put_flag(skb, TEAM_ATTR_OPTION_REMOVED))
		जाओ nest_cancel;
	अगर (opt_inst->changed) अणु
		अगर (nla_put_flag(skb, TEAM_ATTR_OPTION_CHANGED))
			जाओ nest_cancel;
		opt_inst->changed = false;
	पूर्ण
	nla_nest_end(skb, option_item);
	वापस 0;

nest_cancel:
	nla_nest_cancel(skb, option_item);
	वापस -EMSGSIZE;
पूर्ण

अटल पूर्णांक __send_and_alloc_skb(काष्ठा sk_buff **pskb,
				काष्ठा team *team, u32 portid,
				team_nl_send_func_t *send_func)
अणु
	पूर्णांक err;

	अगर (*pskb) अणु
		err = send_func(*pskb, team, portid);
		अगर (err)
			वापस err;
	पूर्ण
	*pskb = genlmsg_new(GENLMSG_DEFAULT_SIZE, GFP_KERNEL);
	अगर (!*pskb)
		वापस -ENOMEM;
	वापस 0;
पूर्ण

अटल पूर्णांक team_nl_send_options_get(काष्ठा team *team, u32 portid, u32 seq,
				    पूर्णांक flags, team_nl_send_func_t *send_func,
				    काष्ठा list_head *sel_opt_inst_list)
अणु
	काष्ठा nlattr *option_list;
	काष्ठा nlmsghdr *nlh;
	व्योम *hdr;
	काष्ठा team_option_inst *opt_inst;
	पूर्णांक err;
	काष्ठा sk_buff *skb = शून्य;
	bool incomplete;
	पूर्णांक i;

	opt_inst = list_first_entry(sel_opt_inst_list,
				    काष्ठा team_option_inst, पंचांगp_list);

start_again:
	err = __send_and_alloc_skb(&skb, team, portid, send_func);
	अगर (err)
		वापस err;

	hdr = genlmsg_put(skb, portid, seq, &team_nl_family, flags | NLM_F_MULTI,
			  TEAM_CMD_OPTIONS_GET);
	अगर (!hdr) अणु
		nlmsg_मुक्त(skb);
		वापस -EMSGSIZE;
	पूर्ण

	अगर (nla_put_u32(skb, TEAM_ATTR_TEAM_IFINDEX, team->dev->अगरindex))
		जाओ nla_put_failure;
	option_list = nla_nest_start_noflag(skb, TEAM_ATTR_LIST_OPTION);
	अगर (!option_list)
		जाओ nla_put_failure;

	i = 0;
	incomplete = false;
	list_क्रम_each_entry_from(opt_inst, sel_opt_inst_list, पंचांगp_list) अणु
		err = team_nl_fill_one_option_get(skb, team, opt_inst);
		अगर (err) अणु
			अगर (err == -EMSGSIZE) अणु
				अगर (!i)
					जाओ errout;
				incomplete = true;
				अवरोध;
			पूर्ण
			जाओ errout;
		पूर्ण
		i++;
	पूर्ण

	nla_nest_end(skb, option_list);
	genlmsg_end(skb, hdr);
	अगर (incomplete)
		जाओ start_again;

send_करोne:
	nlh = nlmsg_put(skb, portid, seq, NLMSG_DONE, 0, flags | NLM_F_MULTI);
	अगर (!nlh) अणु
		err = __send_and_alloc_skb(&skb, team, portid, send_func);
		अगर (err)
			वापस err;
		जाओ send_करोne;
	पूर्ण

	वापस send_func(skb, team, portid);

nla_put_failure:
	err = -EMSGSIZE;
errout:
	nlmsg_मुक्त(skb);
	वापस err;
पूर्ण

अटल पूर्णांक team_nl_cmd_options_get(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	काष्ठा team *team;
	काष्ठा team_option_inst *opt_inst;
	पूर्णांक err;
	LIST_HEAD(sel_opt_inst_list);

	team = team_nl_team_get(info);
	अगर (!team)
		वापस -EINVAL;

	list_क्रम_each_entry(opt_inst, &team->option_inst_list, list)
		list_add_tail(&opt_inst->पंचांगp_list, &sel_opt_inst_list);
	err = team_nl_send_options_get(team, info->snd_portid, info->snd_seq,
				       NLM_F_ACK, team_nl_send_unicast,
				       &sel_opt_inst_list);

	team_nl_team_put(team);

	वापस err;
पूर्ण

अटल पूर्णांक team_nl_send_event_options_get(काष्ठा team *team,
					  काष्ठा list_head *sel_opt_inst_list);

अटल पूर्णांक team_nl_cmd_options_set(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	काष्ठा team *team;
	पूर्णांक err = 0;
	पूर्णांक i;
	काष्ठा nlattr *nl_option;

	rtnl_lock();

	team = team_nl_team_get(info);
	अगर (!team) अणु
		err = -EINVAL;
		जाओ rtnl_unlock;
	पूर्ण

	err = -EINVAL;
	अगर (!info->attrs[TEAM_ATTR_LIST_OPTION]) अणु
		err = -EINVAL;
		जाओ team_put;
	पूर्ण

	nla_क्रम_each_nested(nl_option, info->attrs[TEAM_ATTR_LIST_OPTION], i) अणु
		काष्ठा nlattr *opt_attrs[TEAM_ATTR_OPTION_MAX + 1];
		काष्ठा nlattr *attr;
		काष्ठा nlattr *attr_data;
		LIST_HEAD(opt_inst_list);
		क्रमागत team_option_type opt_type;
		पूर्णांक opt_port_अगरindex = 0; /* != 0 क्रम per-port options */
		u32 opt_array_index = 0;
		bool opt_is_array = false;
		काष्ठा team_option_inst *opt_inst;
		अक्षर *opt_name;
		bool opt_found = false;

		अगर (nla_type(nl_option) != TEAM_ATTR_ITEM_OPTION) अणु
			err = -EINVAL;
			जाओ team_put;
		पूर्ण
		err = nla_parse_nested_deprecated(opt_attrs,
						  TEAM_ATTR_OPTION_MAX,
						  nl_option,
						  team_nl_option_policy,
						  info->extack);
		अगर (err)
			जाओ team_put;
		अगर (!opt_attrs[TEAM_ATTR_OPTION_NAME] ||
		    !opt_attrs[TEAM_ATTR_OPTION_TYPE]) अणु
			err = -EINVAL;
			जाओ team_put;
		पूर्ण
		चयन (nla_get_u8(opt_attrs[TEAM_ATTR_OPTION_TYPE])) अणु
		हाल NLA_U32:
			opt_type = TEAM_OPTION_TYPE_U32;
			अवरोध;
		हाल NLA_STRING:
			opt_type = TEAM_OPTION_TYPE_STRING;
			अवरोध;
		हाल NLA_BINARY:
			opt_type = TEAM_OPTION_TYPE_BINARY;
			अवरोध;
		हाल NLA_FLAG:
			opt_type = TEAM_OPTION_TYPE_BOOL;
			अवरोध;
		हाल NLA_S32:
			opt_type = TEAM_OPTION_TYPE_S32;
			अवरोध;
		शेष:
			जाओ team_put;
		पूर्ण

		attr_data = opt_attrs[TEAM_ATTR_OPTION_DATA];
		अगर (opt_type != TEAM_OPTION_TYPE_BOOL && !attr_data) अणु
			err = -EINVAL;
			जाओ team_put;
		पूर्ण

		opt_name = nla_data(opt_attrs[TEAM_ATTR_OPTION_NAME]);
		attr = opt_attrs[TEAM_ATTR_OPTION_PORT_IFINDEX];
		अगर (attr)
			opt_port_अगरindex = nla_get_u32(attr);

		attr = opt_attrs[TEAM_ATTR_OPTION_ARRAY_INDEX];
		अगर (attr) अणु
			opt_is_array = true;
			opt_array_index = nla_get_u32(attr);
		पूर्ण

		list_क्रम_each_entry(opt_inst, &team->option_inst_list, list) अणु
			काष्ठा team_option *option = opt_inst->option;
			काष्ठा team_gsetter_ctx ctx;
			काष्ठा team_option_inst_info *opt_inst_info;
			पूर्णांक पंचांगp_अगरindex;

			opt_inst_info = &opt_inst->info;
			पंचांगp_अगरindex = opt_inst_info->port ?
				      opt_inst_info->port->dev->अगरindex : 0;
			अगर (option->type != opt_type ||
			    म_भेद(option->name, opt_name) ||
			    पंचांगp_अगरindex != opt_port_अगरindex ||
			    (option->array_size && !opt_is_array) ||
			    opt_inst_info->array_index != opt_array_index)
				जारी;
			opt_found = true;
			ctx.info = opt_inst_info;
			चयन (opt_type) अणु
			हाल TEAM_OPTION_TYPE_U32:
				ctx.data.u32_val = nla_get_u32(attr_data);
				अवरोध;
			हाल TEAM_OPTION_TYPE_STRING:
				अगर (nla_len(attr_data) > TEAM_STRING_MAX_LEN) अणु
					err = -EINVAL;
					जाओ team_put;
				पूर्ण
				ctx.data.str_val = nla_data(attr_data);
				अवरोध;
			हाल TEAM_OPTION_TYPE_BINARY:
				ctx.data.bin_val.len = nla_len(attr_data);
				ctx.data.bin_val.ptr = nla_data(attr_data);
				अवरोध;
			हाल TEAM_OPTION_TYPE_BOOL:
				ctx.data.bool_val = attr_data ? true : false;
				अवरोध;
			हाल TEAM_OPTION_TYPE_S32:
				ctx.data.s32_val = nla_get_s32(attr_data);
				अवरोध;
			शेष:
				BUG();
			पूर्ण
			err = team_option_set(team, opt_inst, &ctx);
			अगर (err)
				जाओ team_put;
			opt_inst->changed = true;
			list_add(&opt_inst->पंचांगp_list, &opt_inst_list);
		पूर्ण
		अगर (!opt_found) अणु
			err = -ENOENT;
			जाओ team_put;
		पूर्ण

		err = team_nl_send_event_options_get(team, &opt_inst_list);
		अगर (err)
			अवरोध;
	पूर्ण

team_put:
	team_nl_team_put(team);
rtnl_unlock:
	rtnl_unlock();
	वापस err;
पूर्ण

अटल पूर्णांक team_nl_fill_one_port_get(काष्ठा sk_buff *skb,
				     काष्ठा team_port *port)
अणु
	काष्ठा nlattr *port_item;

	port_item = nla_nest_start_noflag(skb, TEAM_ATTR_ITEM_PORT);
	अगर (!port_item)
		जाओ nest_cancel;
	अगर (nla_put_u32(skb, TEAM_ATTR_PORT_IFINDEX, port->dev->अगरindex))
		जाओ nest_cancel;
	अगर (port->changed) अणु
		अगर (nla_put_flag(skb, TEAM_ATTR_PORT_CHANGED))
			जाओ nest_cancel;
		port->changed = false;
	पूर्ण
	अगर ((port->हटाओd &&
	     nla_put_flag(skb, TEAM_ATTR_PORT_REMOVED)) ||
	    (port->state.linkup &&
	     nla_put_flag(skb, TEAM_ATTR_PORT_LINKUP)) ||
	    nla_put_u32(skb, TEAM_ATTR_PORT_SPEED, port->state.speed) ||
	    nla_put_u8(skb, TEAM_ATTR_PORT_DUPLEX, port->state.duplex))
		जाओ nest_cancel;
	nla_nest_end(skb, port_item);
	वापस 0;

nest_cancel:
	nla_nest_cancel(skb, port_item);
	वापस -EMSGSIZE;
पूर्ण

अटल पूर्णांक team_nl_send_port_list_get(काष्ठा team *team, u32 portid, u32 seq,
				      पूर्णांक flags, team_nl_send_func_t *send_func,
				      काष्ठा team_port *one_port)
अणु
	काष्ठा nlattr *port_list;
	काष्ठा nlmsghdr *nlh;
	व्योम *hdr;
	काष्ठा team_port *port;
	पूर्णांक err;
	काष्ठा sk_buff *skb = शून्य;
	bool incomplete;
	पूर्णांक i;

	port = list_first_entry_or_null(&team->port_list,
					काष्ठा team_port, list);

start_again:
	err = __send_and_alloc_skb(&skb, team, portid, send_func);
	अगर (err)
		वापस err;

	hdr = genlmsg_put(skb, portid, seq, &team_nl_family, flags | NLM_F_MULTI,
			  TEAM_CMD_PORT_LIST_GET);
	अगर (!hdr) अणु
		nlmsg_मुक्त(skb);
		वापस -EMSGSIZE;
	पूर्ण

	अगर (nla_put_u32(skb, TEAM_ATTR_TEAM_IFINDEX, team->dev->अगरindex))
		जाओ nla_put_failure;
	port_list = nla_nest_start_noflag(skb, TEAM_ATTR_LIST_PORT);
	अगर (!port_list)
		जाओ nla_put_failure;

	i = 0;
	incomplete = false;

	/* If one port is selected, called wants to send port list containing
	 * only this port. Otherwise go through all listed ports and send all
	 */
	अगर (one_port) अणु
		err = team_nl_fill_one_port_get(skb, one_port);
		अगर (err)
			जाओ errout;
	पूर्ण अन्यथा अगर (port) अणु
		list_क्रम_each_entry_from(port, &team->port_list, list) अणु
			err = team_nl_fill_one_port_get(skb, port);
			अगर (err) अणु
				अगर (err == -EMSGSIZE) अणु
					अगर (!i)
						जाओ errout;
					incomplete = true;
					अवरोध;
				पूर्ण
				जाओ errout;
			पूर्ण
			i++;
		पूर्ण
	पूर्ण

	nla_nest_end(skb, port_list);
	genlmsg_end(skb, hdr);
	अगर (incomplete)
		जाओ start_again;

send_करोne:
	nlh = nlmsg_put(skb, portid, seq, NLMSG_DONE, 0, flags | NLM_F_MULTI);
	अगर (!nlh) अणु
		err = __send_and_alloc_skb(&skb, team, portid, send_func);
		अगर (err)
			वापस err;
		जाओ send_करोne;
	पूर्ण

	वापस send_func(skb, team, portid);

nla_put_failure:
	err = -EMSGSIZE;
errout:
	nlmsg_मुक्त(skb);
	वापस err;
पूर्ण

अटल पूर्णांक team_nl_cmd_port_list_get(काष्ठा sk_buff *skb,
				     काष्ठा genl_info *info)
अणु
	काष्ठा team *team;
	पूर्णांक err;

	team = team_nl_team_get(info);
	अगर (!team)
		वापस -EINVAL;

	err = team_nl_send_port_list_get(team, info->snd_portid, info->snd_seq,
					 NLM_F_ACK, team_nl_send_unicast, शून्य);

	team_nl_team_put(team);

	वापस err;
पूर्ण

अटल स्थिर काष्ठा genl_small_ops team_nl_ops[] = अणु
	अणु
		.cmd = TEAM_CMD_NOOP,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.करोit = team_nl_cmd_noop,
	पूर्ण,
	अणु
		.cmd = TEAM_CMD_OPTIONS_SET,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.करोit = team_nl_cmd_options_set,
		.flags = GENL_ADMIN_PERM,
	पूर्ण,
	अणु
		.cmd = TEAM_CMD_OPTIONS_GET,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.करोit = team_nl_cmd_options_get,
		.flags = GENL_ADMIN_PERM,
	पूर्ण,
	अणु
		.cmd = TEAM_CMD_PORT_LIST_GET,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.करोit = team_nl_cmd_port_list_get,
		.flags = GENL_ADMIN_PERM,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा genl_multicast_group team_nl_mcgrps[] = अणु
	अणु .name = TEAM_GENL_CHANGE_EVENT_MC_GRP_NAME, पूर्ण,
पूर्ण;

अटल काष्ठा genl_family team_nl_family __ro_after_init = अणु
	.name		= TEAM_GENL_NAME,
	.version	= TEAM_GENL_VERSION,
	.maxattr	= TEAM_ATTR_MAX,
	.policy = team_nl_policy,
	.netnsok	= true,
	.module		= THIS_MODULE,
	.small_ops	= team_nl_ops,
	.n_small_ops	= ARRAY_SIZE(team_nl_ops),
	.mcgrps		= team_nl_mcgrps,
	.n_mcgrps	= ARRAY_SIZE(team_nl_mcgrps),
पूर्ण;

अटल पूर्णांक team_nl_send_multicast(काष्ठा sk_buff *skb,
				  काष्ठा team *team, u32 portid)
अणु
	वापस genlmsg_multicast_netns(&team_nl_family, dev_net(team->dev),
				       skb, 0, 0, GFP_KERNEL);
पूर्ण

अटल पूर्णांक team_nl_send_event_options_get(काष्ठा team *team,
					  काष्ठा list_head *sel_opt_inst_list)
अणु
	वापस team_nl_send_options_get(team, 0, 0, 0, team_nl_send_multicast,
					sel_opt_inst_list);
पूर्ण

अटल पूर्णांक team_nl_send_event_port_get(काष्ठा team *team,
				       काष्ठा team_port *port)
अणु
	वापस team_nl_send_port_list_get(team, 0, 0, 0, team_nl_send_multicast,
					  port);
पूर्ण

अटल पूर्णांक __init team_nl_init(व्योम)
अणु
	वापस genl_रेजिस्टर_family(&team_nl_family);
पूर्ण

अटल व्योम team_nl_fini(व्योम)
अणु
	genl_unरेजिस्टर_family(&team_nl_family);
पूर्ण


/******************
 * Change checkers
 ******************/

अटल व्योम __team_options_change_check(काष्ठा team *team)
अणु
	पूर्णांक err;
	काष्ठा team_option_inst *opt_inst;
	LIST_HEAD(sel_opt_inst_list);

	list_क्रम_each_entry(opt_inst, &team->option_inst_list, list) अणु
		अगर (opt_inst->changed)
			list_add_tail(&opt_inst->पंचांगp_list, &sel_opt_inst_list);
	पूर्ण
	err = team_nl_send_event_options_get(team, &sel_opt_inst_list);
	अगर (err && err != -ESRCH)
		netdev_warn(team->dev, "Failed to send options change via netlink (err %d)\n",
			    err);
पूर्ण

/* rtnl lock is held */

अटल व्योम __team_port_change_send(काष्ठा team_port *port, bool linkup)
अणु
	पूर्णांक err;

	port->changed = true;
	port->state.linkup = linkup;
	team_refresh_port_linkup(port);
	अगर (linkup) अणु
		काष्ठा ethtool_link_ksettings ecmd;

		err = __ethtool_get_link_ksettings(port->dev, &ecmd);
		अगर (!err) अणु
			port->state.speed = ecmd.base.speed;
			port->state.duplex = ecmd.base.duplex;
			जाओ send_event;
		पूर्ण
	पूर्ण
	port->state.speed = 0;
	port->state.duplex = 0;

send_event:
	err = team_nl_send_event_port_get(port->team, port);
	अगर (err && err != -ESRCH)
		netdev_warn(port->team->dev, "Failed to send port change of device %s via netlink (err %d)\n",
			    port->dev->name, err);

पूर्ण

अटल व्योम __team_carrier_check(काष्ठा team *team)
अणु
	काष्ठा team_port *port;
	bool team_linkup;

	अगर (team->user_carrier_enabled)
		वापस;

	team_linkup = false;
	list_क्रम_each_entry(port, &team->port_list, list) अणु
		अगर (port->linkup) अणु
			team_linkup = true;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (team_linkup)
		netअगर_carrier_on(team->dev);
	अन्यथा
		netअगर_carrier_off(team->dev);
पूर्ण

अटल व्योम __team_port_change_check(काष्ठा team_port *port, bool linkup)
अणु
	अगर (port->state.linkup != linkup)
		__team_port_change_send(port, linkup);
	__team_carrier_check(port->team);
पूर्ण

अटल व्योम __team_port_change_port_added(काष्ठा team_port *port, bool linkup)
अणु
	__team_port_change_send(port, linkup);
	__team_carrier_check(port->team);
पूर्ण

अटल व्योम __team_port_change_port_हटाओd(काष्ठा team_port *port)
अणु
	port->हटाओd = true;
	__team_port_change_send(port, false);
	__team_carrier_check(port->team);
पूर्ण

अटल व्योम team_port_change_check(काष्ठा team_port *port, bool linkup)
अणु
	काष्ठा team *team = port->team;

	mutex_lock(&team->lock);
	__team_port_change_check(port, linkup);
	mutex_unlock(&team->lock);
पूर्ण


/************************************
 * Net device notअगरier event handler
 ************************************/

अटल पूर्णांक team_device_event(काष्ठा notअगरier_block *unused,
			     अचिन्हित दीर्घ event, व्योम *ptr)
अणु
	काष्ठा net_device *dev = netdev_notअगरier_info_to_dev(ptr);
	काष्ठा team_port *port;

	port = team_port_get_rtnl(dev);
	अगर (!port)
		वापस NOTIFY_DONE;

	चयन (event) अणु
	हाल NETDEV_UP:
		अगर (netअगर_oper_up(dev))
			team_port_change_check(port, true);
		अवरोध;
	हाल NETDEV_DOWN:
		team_port_change_check(port, false);
		अवरोध;
	हाल NETDEV_CHANGE:
		अगर (netअगर_running(port->dev))
			team_port_change_check(port,
					       !!netअगर_oper_up(port->dev));
		अवरोध;
	हाल NETDEV_UNREGISTER:
		team_del_slave(port->team->dev, dev);
		अवरोध;
	हाल NETDEV_FEAT_CHANGE:
		team_compute_features(port->team);
		अवरोध;
	हाल NETDEV_PRECHANGEMTU:
		/* Forbid to change mtu of underlaying device */
		अगर (!port->team->port_mtu_change_allowed)
			वापस NOTIFY_BAD;
		अवरोध;
	हाल NETDEV_PRE_TYPE_CHANGE:
		/* Forbid to change type of underlaying device */
		वापस NOTIFY_BAD;
	हाल NETDEV_RESEND_IGMP:
		/* Propagate to master device */
		call_netdevice_notअगरiers(event, port->team->dev);
		अवरोध;
	पूर्ण
	वापस NOTIFY_DONE;
पूर्ण

अटल काष्ठा notअगरier_block team_notअगरier_block __पढ़ो_mostly = अणु
	.notअगरier_call = team_device_event,
पूर्ण;


/***********************
 * Module init and निकास
 ***********************/

अटल पूर्णांक __init team_module_init(व्योम)
अणु
	पूर्णांक err;

	रेजिस्टर_netdevice_notअगरier(&team_notअगरier_block);

	err = rtnl_link_रेजिस्टर(&team_link_ops);
	अगर (err)
		जाओ err_rtnl_reg;

	err = team_nl_init();
	अगर (err)
		जाओ err_nl_init;

	वापस 0;

err_nl_init:
	rtnl_link_unरेजिस्टर(&team_link_ops);

err_rtnl_reg:
	unरेजिस्टर_netdevice_notअगरier(&team_notअगरier_block);

	वापस err;
पूर्ण

अटल व्योम __निकास team_module_निकास(व्योम)
अणु
	team_nl_fini();
	rtnl_link_unरेजिस्टर(&team_link_ops);
	unरेजिस्टर_netdevice_notअगरier(&team_notअगरier_block);
पूर्ण

module_init(team_module_init);
module_निकास(team_module_निकास);

MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Jiri Pirko <jpirko@redhat.com>");
MODULE_DESCRIPTION("Ethernet team device driver");
MODULE_ALIAS_RTNL_LINK(DRV_NAME);
