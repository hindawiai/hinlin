<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0-only OR BSD-2-Clause)
/* Copyright (C) 2017-2018 Netronome Systems, Inc. */

#समावेश <linux/bug.h>
#समावेश <linux/lockdep.h>
#समावेश <linux/rcupdate.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/slab.h>

#समावेश "nfpcore/nfp_cpp.h"
#समावेश "nfpcore/nfp_nffw.h"
#समावेश "nfp_app.h"
#समावेश "nfp_main.h"
#समावेश "nfp_net.h"
#समावेश "nfp_net_repr.h"
#समावेश "nfp_port.h"

अटल स्थिर काष्ठा nfp_app_type *apps[] = अणु
	[NFP_APP_CORE_NIC]	= &app_nic,
#अगर_घोषित CONFIG_BPF_SYSCALL
	[NFP_APP_BPF_NIC]	= &app_bpf,
#अन्यथा
	[NFP_APP_BPF_NIC]	= &app_nic,
#पूर्ण_अगर
#अगर_घोषित CONFIG_NFP_APP_FLOWER
	[NFP_APP_FLOWER_NIC]	= &app_flower,
#पूर्ण_अगर
#अगर_घोषित CONFIG_NFP_APP_ABM_NIC
	[NFP_APP_ACTIVE_BUFFER_MGMT_NIC] = &app_abm,
#पूर्ण_अगर
पूर्ण;

व्योम nfp_check_rhashtable_empty(व्योम *ptr, व्योम *arg)
अणु
	WARN_ON_ONCE(1);
पूर्ण

काष्ठा nfp_app *nfp_app_from_netdev(काष्ठा net_device *netdev)
अणु
	अगर (nfp_netdev_is_nfp_net(netdev)) अणु
		काष्ठा nfp_net *nn = netdev_priv(netdev);

		वापस nn->app;
	पूर्ण

	अगर (nfp_netdev_is_nfp_repr(netdev)) अणु
		काष्ठा nfp_repr *repr = netdev_priv(netdev);

		वापस repr->app;
	पूर्ण

	WARN(1, "Unknown netdev type for nfp_app\n");

	वापस शून्य;
पूर्ण

स्थिर अक्षर *nfp_app_mip_name(काष्ठा nfp_app *app)
अणु
	अगर (!app || !app->pf->mip)
		वापस "";
	वापस nfp_mip_name(app->pf->mip);
पूर्ण

पूर्णांक nfp_app_nकरो_init(काष्ठा net_device *netdev)
अणु
	काष्ठा nfp_app *app = nfp_app_from_netdev(netdev);

	अगर (!app || !app->type->nकरो_init)
		वापस 0;
	वापस app->type->nकरो_init(app, netdev);
पूर्ण

व्योम nfp_app_nकरो_uninit(काष्ठा net_device *netdev)
अणु
	काष्ठा nfp_app *app = nfp_app_from_netdev(netdev);

	अगर (app && app->type->nकरो_uninit)
		app->type->nकरो_uninit(app, netdev);
पूर्ण

u64 *nfp_app_port_get_stats(काष्ठा nfp_port *port, u64 *data)
अणु
	अगर (!port || !port->app || !port->app->type->port_get_stats)
		वापस data;
	वापस port->app->type->port_get_stats(port->app, port, data);
पूर्ण

पूर्णांक nfp_app_port_get_stats_count(काष्ठा nfp_port *port)
अणु
	अगर (!port || !port->app || !port->app->type->port_get_stats_count)
		वापस 0;
	वापस port->app->type->port_get_stats_count(port->app, port);
पूर्ण

u8 *nfp_app_port_get_stats_strings(काष्ठा nfp_port *port, u8 *data)
अणु
	अगर (!port || !port->app || !port->app->type->port_get_stats_strings)
		वापस data;
	वापस port->app->type->port_get_stats_strings(port->app, port, data);
पूर्ण

काष्ठा sk_buff *
nfp_app_ctrl_msg_alloc(काष्ठा nfp_app *app, अचिन्हित पूर्णांक size, gfp_t priority)
अणु
	काष्ठा sk_buff *skb;

	अगर (nfp_app_ctrl_has_meta(app))
		size += 8;

	skb = alloc_skb(size, priority);
	अगर (!skb)
		वापस शून्य;

	अगर (nfp_app_ctrl_has_meta(app))
		skb_reserve(skb, 8);

	वापस skb;
पूर्ण

काष्ठा nfp_reprs *
nfp_reprs_get_locked(काष्ठा nfp_app *app, क्रमागत nfp_repr_type type)
अणु
	वापस rcu_dereference_रक्षित(app->reprs[type],
					 lockdep_is_held(&app->pf->lock));
पूर्ण

काष्ठा nfp_reprs *
nfp_app_reprs_set(काष्ठा nfp_app *app, क्रमागत nfp_repr_type type,
		  काष्ठा nfp_reprs *reprs)
अणु
	काष्ठा nfp_reprs *old;

	old = nfp_reprs_get_locked(app, type);
	rtnl_lock();
	rcu_assign_poपूर्णांकer(app->reprs[type], reprs);
	rtnl_unlock();

	वापस old;
पूर्ण

अटल व्योम
nfp_app_netdev_feat_change(काष्ठा nfp_app *app, काष्ठा net_device *netdev)
अणु
	काष्ठा nfp_net *nn;
	अचिन्हित पूर्णांक type;

	अगर (!nfp_netdev_is_nfp_net(netdev))
		वापस;
	nn = netdev_priv(netdev);
	अगर (nn->app != app)
		वापस;

	क्रम (type = 0; type < __NFP_REPR_TYPE_MAX; type++) अणु
		काष्ठा nfp_reprs *reprs;
		अचिन्हित पूर्णांक i;

		reprs = rtnl_dereference(app->reprs[type]);
		अगर (!reprs)
			जारी;

		क्रम (i = 0; i < reprs->num_reprs; i++) अणु
			काष्ठा net_device *repr;

			repr = rtnl_dereference(reprs->reprs[i]);
			अगर (!repr)
				जारी;

			nfp_repr_transfer_features(repr, netdev);
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक
nfp_app_netdev_event(काष्ठा notअगरier_block *nb, अचिन्हित दीर्घ event, व्योम *ptr)
अणु
	काष्ठा net_device *netdev;
	काष्ठा nfp_app *app;

	netdev = netdev_notअगरier_info_to_dev(ptr);
	app = container_of(nb, काष्ठा nfp_app, netdev_nb);

	/* Handle events common code is पूर्णांकerested in */
	चयन (event) अणु
	हाल NETDEV_FEAT_CHANGE:
		nfp_app_netdev_feat_change(app, netdev);
		अवरोध;
	पूर्ण

	/* Call offload specअगरic handlers */
	अगर (app->type->netdev_event)
		वापस app->type->netdev_event(app, netdev, event, ptr);
	वापस NOTIFY_DONE;
पूर्ण

पूर्णांक nfp_app_start(काष्ठा nfp_app *app, काष्ठा nfp_net *ctrl)
अणु
	पूर्णांक err;

	app->ctrl = ctrl;

	अगर (app->type->start) अणु
		err = app->type->start(app);
		अगर (err)
			वापस err;
	पूर्ण

	app->netdev_nb.notअगरier_call = nfp_app_netdev_event;
	err = रेजिस्टर_netdevice_notअगरier(&app->netdev_nb);
	अगर (err)
		जाओ err_app_stop;

	वापस 0;

err_app_stop:
	अगर (app->type->stop)
		app->type->stop(app);
	वापस err;
पूर्ण

व्योम nfp_app_stop(काष्ठा nfp_app *app)
अणु
	unरेजिस्टर_netdevice_notअगरier(&app->netdev_nb);

	अगर (app->type->stop)
		app->type->stop(app);
पूर्ण

काष्ठा nfp_app *nfp_app_alloc(काष्ठा nfp_pf *pf, क्रमागत nfp_app_id id)
अणु
	काष्ठा nfp_app *app;

	अगर (id >= ARRAY_SIZE(apps) || !apps[id]) अणु
		nfp_err(pf->cpp, "unknown FW app ID 0x%02hhx, driver too old or support for FW not built in\n", id);
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	अगर (WARN_ON(!apps[id]->name || !apps[id]->vnic_alloc))
		वापस ERR_PTR(-EINVAL);
	अगर (WARN_ON(!apps[id]->ctrl_msg_rx && apps[id]->ctrl_msg_rx_raw))
		वापस ERR_PTR(-EINVAL);

	app = kzalloc(माप(*app), GFP_KERNEL);
	अगर (!app)
		वापस ERR_PTR(-ENOMEM);

	app->pf = pf;
	app->cpp = pf->cpp;
	app->pdev = pf->pdev;
	app->type = apps[id];

	वापस app;
पूर्ण

व्योम nfp_app_मुक्त(काष्ठा nfp_app *app)
अणु
	kमुक्त(app);
पूर्ण
