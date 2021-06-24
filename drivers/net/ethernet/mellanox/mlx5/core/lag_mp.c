<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR Linux-OpenIB
/* Copyright (c) 2019 Mellanox Technologies. */

#समावेश <linux/netdevice.h>
#समावेश <net/nexthop.h>
#समावेश "lag.h"
#समावेश "lag_mp.h"
#समावेश "mlx5_core.h"
#समावेश "eswitch.h"
#समावेश "lib/mlx5.h"

अटल bool mlx5_lag_multipath_check_prereq(काष्ठा mlx5_lag *ldev)
अणु
	अगर (!mlx5_lag_is_पढ़ोy(ldev))
		वापस false;

	वापस mlx5_esw_multipath_prereq(ldev->pf[MLX5_LAG_P1].dev,
					 ldev->pf[MLX5_LAG_P2].dev);
पूर्ण

अटल bool __mlx5_lag_is_multipath(काष्ठा mlx5_lag *ldev)
अणु
	वापस !!(ldev->flags & MLX5_LAG_FLAG_MULTIPATH);
पूर्ण

bool mlx5_lag_is_multipath(काष्ठा mlx5_core_dev *dev)
अणु
	काष्ठा mlx5_lag *ldev;
	bool res;

	ldev = mlx5_lag_dev_get(dev);
	res  = ldev && __mlx5_lag_is_multipath(ldev);

	वापस res;
पूर्ण

/**
 * mlx5_lag_set_port_affinity
 *
 * @ldev: lag device
 * @port:
 *     0 - set normal affinity.
 *     1 - set affinity to port 1.
 *     2 - set affinity to port 2.
 *
 **/
अटल व्योम mlx5_lag_set_port_affinity(काष्ठा mlx5_lag *ldev,
				       क्रमागत mlx5_lag_port_affinity port)
अणु
	काष्ठा lag_tracker tracker;

	अगर (!__mlx5_lag_is_multipath(ldev))
		वापस;

	चयन (port) अणु
	हाल MLX5_LAG_NORMAL_AFFINITY:
		tracker.netdev_state[MLX5_LAG_P1].tx_enabled = true;
		tracker.netdev_state[MLX5_LAG_P2].tx_enabled = true;
		tracker.netdev_state[MLX5_LAG_P1].link_up = true;
		tracker.netdev_state[MLX5_LAG_P2].link_up = true;
		अवरोध;
	हाल MLX5_LAG_P1_AFFINITY:
		tracker.netdev_state[MLX5_LAG_P1].tx_enabled = true;
		tracker.netdev_state[MLX5_LAG_P1].link_up = true;
		tracker.netdev_state[MLX5_LAG_P2].tx_enabled = false;
		tracker.netdev_state[MLX5_LAG_P2].link_up = false;
		अवरोध;
	हाल MLX5_LAG_P2_AFFINITY:
		tracker.netdev_state[MLX5_LAG_P1].tx_enabled = false;
		tracker.netdev_state[MLX5_LAG_P1].link_up = false;
		tracker.netdev_state[MLX5_LAG_P2].tx_enabled = true;
		tracker.netdev_state[MLX5_LAG_P2].link_up = true;
		अवरोध;
	शेष:
		mlx5_core_warn(ldev->pf[MLX5_LAG_P1].dev,
			       "Invalid affinity port %d", port);
		वापस;
	पूर्ण

	अगर (tracker.netdev_state[MLX5_LAG_P1].tx_enabled)
		mlx5_notअगरier_call_chain(ldev->pf[MLX5_LAG_P1].dev->priv.events,
					 MLX5_DEV_EVENT_PORT_AFFINITY,
					 (व्योम *)0);

	अगर (tracker.netdev_state[MLX5_LAG_P2].tx_enabled)
		mlx5_notअगरier_call_chain(ldev->pf[MLX5_LAG_P2].dev->priv.events,
					 MLX5_DEV_EVENT_PORT_AFFINITY,
					 (व्योम *)0);

	mlx5_modअगरy_lag(ldev, &tracker);
पूर्ण

अटल व्योम mlx5_lag_fib_event_flush(काष्ठा notअगरier_block *nb)
अणु
	काष्ठा lag_mp *mp = container_of(nb, काष्ठा lag_mp, fib_nb);

	flush_workqueue(mp->wq);
पूर्ण

काष्ठा mlx5_fib_event_work अणु
	काष्ठा work_काष्ठा work;
	काष्ठा mlx5_lag *ldev;
	अचिन्हित दीर्घ event;
	जोड़ अणु
		काष्ठा fib_entry_notअगरier_info fen_info;
		काष्ठा fib_nh_notअगरier_info fnh_info;
	पूर्ण;
पूर्ण;

अटल व्योम mlx5_lag_fib_route_event(काष्ठा mlx5_lag *ldev,
				     अचिन्हित दीर्घ event,
				     काष्ठा fib_info *fi)
अणु
	काष्ठा lag_mp *mp = &ldev->lag_mp;
	काष्ठा fib_nh *fib_nh0, *fib_nh1;
	अचिन्हित पूर्णांक nhs;

	/* Handle delete event */
	अगर (event == FIB_EVENT_ENTRY_DEL) अणु
		/* stop track */
		अगर (mp->mfi == fi)
			mp->mfi = शून्य;
		वापस;
	पूर्ण

	/* Handle add/replace event */
	nhs = fib_info_num_path(fi);
	अगर (nhs == 1) अणु
		अगर (__mlx5_lag_is_active(ldev)) अणु
			काष्ठा fib_nh *nh = fib_info_nh(fi, 0);
			काष्ठा net_device *nh_dev = nh->fib_nh_dev;
			पूर्णांक i = mlx5_lag_dev_get_netdev_idx(ldev, nh_dev);

			अगर (i < 0)
				i = MLX5_LAG_NORMAL_AFFINITY;
			अन्यथा
				++i;

			mlx5_lag_set_port_affinity(ldev, i);
		पूर्ण
		वापस;
	पूर्ण

	अगर (nhs != 2)
		वापस;

	/* Verअगरy next hops are ports of the same hca */
	fib_nh0 = fib_info_nh(fi, 0);
	fib_nh1 = fib_info_nh(fi, 1);
	अगर (!(fib_nh0->fib_nh_dev == ldev->pf[MLX5_LAG_P1].netdev &&
	      fib_nh1->fib_nh_dev == ldev->pf[MLX5_LAG_P2].netdev) &&
	    !(fib_nh0->fib_nh_dev == ldev->pf[MLX5_LAG_P2].netdev &&
	      fib_nh1->fib_nh_dev == ldev->pf[MLX5_LAG_P1].netdev)) अणु
		mlx5_core_warn(ldev->pf[MLX5_LAG_P1].dev,
			       "Multipath offload require two ports of the same HCA\n");
		वापस;
	पूर्ण

	/* First समय we see multipath route */
	अगर (!mp->mfi && !__mlx5_lag_is_active(ldev)) अणु
		काष्ठा lag_tracker tracker;

		tracker = ldev->tracker;
		mlx5_activate_lag(ldev, &tracker, MLX5_LAG_FLAG_MULTIPATH);
	पूर्ण

	mlx5_lag_set_port_affinity(ldev, MLX5_LAG_NORMAL_AFFINITY);
	mp->mfi = fi;
पूर्ण

अटल व्योम mlx5_lag_fib_nexthop_event(काष्ठा mlx5_lag *ldev,
				       अचिन्हित दीर्घ event,
				       काष्ठा fib_nh *fib_nh,
				       काष्ठा fib_info *fi)
अणु
	काष्ठा lag_mp *mp = &ldev->lag_mp;

	/* Check the nh event is related to the route */
	अगर (!mp->mfi || mp->mfi != fi)
		वापस;

	/* nh added/हटाओd */
	अगर (event == FIB_EVENT_NH_DEL) अणु
		पूर्णांक i = mlx5_lag_dev_get_netdev_idx(ldev, fib_nh->fib_nh_dev);

		अगर (i >= 0) अणु
			i = (i + 1) % 2 + 1; /* peer port */
			mlx5_lag_set_port_affinity(ldev, i);
		पूर्ण
	पूर्ण अन्यथा अगर (event == FIB_EVENT_NH_ADD &&
		   fib_info_num_path(fi) == 2) अणु
		mlx5_lag_set_port_affinity(ldev, MLX5_LAG_NORMAL_AFFINITY);
	पूर्ण
पूर्ण

अटल व्योम mlx5_lag_fib_update(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा mlx5_fib_event_work *fib_work =
		container_of(work, काष्ठा mlx5_fib_event_work, work);
	काष्ठा mlx5_lag *ldev = fib_work->ldev;
	काष्ठा fib_nh *fib_nh;

	/* Protect पूर्णांकernal काष्ठाures from changes */
	rtnl_lock();
	चयन (fib_work->event) अणु
	हाल FIB_EVENT_ENTRY_REPLACE:
	हाल FIB_EVENT_ENTRY_DEL:
		mlx5_lag_fib_route_event(ldev, fib_work->event,
					 fib_work->fen_info.fi);
		fib_info_put(fib_work->fen_info.fi);
		अवरोध;
	हाल FIB_EVENT_NH_ADD:
	हाल FIB_EVENT_NH_DEL:
		fib_nh = fib_work->fnh_info.fib_nh;
		mlx5_lag_fib_nexthop_event(ldev,
					   fib_work->event,
					   fib_work->fnh_info.fib_nh,
					   fib_nh->nh_parent);
		fib_info_put(fib_work->fnh_info.fib_nh->nh_parent);
		अवरोध;
	पूर्ण

	rtnl_unlock();
	kमुक्त(fib_work);
पूर्ण

अटल काष्ठा mlx5_fib_event_work *
mlx5_lag_init_fib_work(काष्ठा mlx5_lag *ldev, अचिन्हित दीर्घ event)
अणु
	काष्ठा mlx5_fib_event_work *fib_work;

	fib_work = kzalloc(माप(*fib_work), GFP_ATOMIC);
	अगर (WARN_ON(!fib_work))
		वापस शून्य;

	INIT_WORK(&fib_work->work, mlx5_lag_fib_update);
	fib_work->ldev = ldev;
	fib_work->event = event;

	वापस fib_work;
पूर्ण

अटल पूर्णांक mlx5_lag_fib_event(काष्ठा notअगरier_block *nb,
			      अचिन्हित दीर्घ event,
			      व्योम *ptr)
अणु
	काष्ठा lag_mp *mp = container_of(nb, काष्ठा lag_mp, fib_nb);
	काष्ठा mlx5_lag *ldev = container_of(mp, काष्ठा mlx5_lag, lag_mp);
	काष्ठा fib_notअगरier_info *info = ptr;
	काष्ठा mlx5_fib_event_work *fib_work;
	काष्ठा fib_entry_notअगरier_info *fen_info;
	काष्ठा fib_nh_notअगरier_info *fnh_info;
	काष्ठा net_device *fib_dev;
	काष्ठा fib_info *fi;

	अगर (info->family != AF_INET)
		वापस NOTIFY_DONE;

	अगर (!mlx5_lag_multipath_check_prereq(ldev))
		वापस NOTIFY_DONE;

	चयन (event) अणु
	हाल FIB_EVENT_ENTRY_REPLACE:
	हाल FIB_EVENT_ENTRY_DEL:
		fen_info = container_of(info, काष्ठा fib_entry_notअगरier_info,
					info);
		fi = fen_info->fi;
		अगर (fi->nh) अणु
			NL_SET_ERR_MSG_MOD(info->extack, "IPv4 route with nexthop objects is not supported");
			वापस notअगरier_from_त्रुटि_सं(-EINVAL);
		पूर्ण
		fib_dev = fib_info_nh(fen_info->fi, 0)->fib_nh_dev;
		अगर (fib_dev != ldev->pf[MLX5_LAG_P1].netdev &&
		    fib_dev != ldev->pf[MLX5_LAG_P2].netdev) अणु
			वापस NOTIFY_DONE;
		पूर्ण
		fib_work = mlx5_lag_init_fib_work(ldev, event);
		अगर (!fib_work)
			वापस NOTIFY_DONE;
		fib_work->fen_info = *fen_info;
		/* Take reference on fib_info to prevent it from being
		 * मुक्तd जबतक work is queued. Release it afterwards.
		 */
		fib_info_hold(fib_work->fen_info.fi);
		अवरोध;
	हाल FIB_EVENT_NH_ADD:
	हाल FIB_EVENT_NH_DEL:
		fnh_info = container_of(info, काष्ठा fib_nh_notअगरier_info,
					info);
		fib_work = mlx5_lag_init_fib_work(ldev, event);
		अगर (!fib_work)
			वापस NOTIFY_DONE;
		fib_work->fnh_info = *fnh_info;
		fib_info_hold(fib_work->fnh_info.fib_nh->nh_parent);
		अवरोध;
	शेष:
		वापस NOTIFY_DONE;
	पूर्ण

	queue_work(mp->wq, &fib_work->work);

	वापस NOTIFY_DONE;
पूर्ण

पूर्णांक mlx5_lag_mp_init(काष्ठा mlx5_lag *ldev)
अणु
	काष्ठा lag_mp *mp = &ldev->lag_mp;
	पूर्णांक err;

	/* always clear mfi, as it might become stale when a route delete event
	 * has been missed
	 */
	mp->mfi = शून्य;

	अगर (mp->fib_nb.notअगरier_call)
		वापस 0;

	mp->wq = create_singlethपढ़ो_workqueue("mlx5_lag_mp");
	अगर (!mp->wq)
		वापस -ENOMEM;

	mp->fib_nb.notअगरier_call = mlx5_lag_fib_event;
	err = रेजिस्टर_fib_notअगरier(&init_net, &mp->fib_nb,
				    mlx5_lag_fib_event_flush, शून्य);
	अगर (err) अणु
		destroy_workqueue(mp->wq);
		mp->fib_nb.notअगरier_call = शून्य;
	पूर्ण

	वापस err;
पूर्ण

व्योम mlx5_lag_mp_cleanup(काष्ठा mlx5_lag *ldev)
अणु
	काष्ठा lag_mp *mp = &ldev->lag_mp;

	अगर (!mp->fib_nb.notअगरier_call)
		वापस;

	unरेजिस्टर_fib_notअगरier(&init_net, &mp->fib_nb);
	destroy_workqueue(mp->wq);
	mp->fib_nb.notअगरier_call = शून्य;
	mp->mfi = शून्य;
पूर्ण
