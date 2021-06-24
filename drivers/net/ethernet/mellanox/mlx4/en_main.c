<शैली गुरु>
/*
 * Copyright (c) 2007 Mellanox Technologies. All rights reserved.
 *
 * This software is available to you under a choice of one of two
 * licenses.  You may choose to be licensed under the terms of the GNU
 * General Public License (GPL) Version 2, available from the file
 * COPYING in the मुख्य directory of this source tree, or the
 * OpenIB.org BSD license below:
 *
 *     Redistribution and use in source and binary क्रमms, with or
 *     without modअगरication, are permitted provided that the following
 *     conditions are met:
 *
 *      - Redistributions of source code must retain the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer.
 *
 *      - Redistributions in binary क्रमm must reproduce the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer in the करोcumentation and/or other materials
 *        provided with the distribution.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 */

#समावेश <linux/cpumask.h>
#समावेश <linux/module.h>
#समावेश <linux/delay.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/slab.h>

#समावेश <linux/mlx4/driver.h>
#समावेश <linux/mlx4/device.h>
#समावेश <linux/mlx4/cmd.h>

#समावेश "mlx4_en.h"

MODULE_AUTHOR("Liran Liss, Yevgeny Petrilin");
MODULE_DESCRIPTION("Mellanox ConnectX HCA Ethernet driver");
MODULE_LICENSE("Dual BSD/GPL");
MODULE_VERSION(DRV_VERSION);

अटल स्थिर अक्षर mlx4_en_version[] =
	DRV_NAME ": Mellanox ConnectX HCA Ethernet driver v"
	DRV_VERSION "\n";

#घोषणा MLX4_EN_PARM_INT(X, def_val, desc) \
	अटल अचिन्हित पूर्णांक X = def_val;\
	module_param(X , uपूर्णांक, 0444); \
	MODULE_PARM_DESC(X, desc);


/*
 * Device scope module parameters
 */

/* Enable RSS UDP traffic */
MLX4_EN_PARM_INT(udp_rss, 1,
		 "Enable RSS for incoming UDP traffic or disabled (0)");

/* Priority pausing */
MLX4_EN_PARM_INT(pfctx, 0, "Priority based Flow Control policy on TX[7:0]."
			   " Per priority bit mask");
MLX4_EN_PARM_INT(pfcrx, 0, "Priority based Flow Control policy on RX[7:0]."
			   " Per priority bit mask");

MLX4_EN_PARM_INT(अंतरभूत_thold, MAX_INLINE,
		 "Threshold for using inline data (range: 17-104, default: 104)");

#घोषणा MAX_PFC_TX     0xff
#घोषणा MAX_PFC_RX     0xff

व्योम en_prपूर्णांक(स्थिर अक्षर *level, स्थिर काष्ठा mlx4_en_priv *priv,
	      स्थिर अक्षर *क्रमmat, ...)
अणु
	बहु_सूची args;
	काष्ठा va_क्रमmat vaf;

	बहु_शुरू(args, क्रमmat);

	vaf.fmt = क्रमmat;
	vaf.va = &args;
	अगर (priv->रेजिस्टरed)
		prपूर्णांकk("%s%s: %s: %pV",
		       level, DRV_NAME, priv->dev->name, &vaf);
	अन्यथा
		prपूर्णांकk("%s%s: %s: Port %d: %pV",
		       level, DRV_NAME, dev_name(&priv->mdev->pdev->dev),
		       priv->port, &vaf);
	बहु_पूर्ण(args);
पूर्ण

व्योम mlx4_en_update_loopback_state(काष्ठा net_device *dev,
				   netdev_features_t features)
अणु
	काष्ठा mlx4_en_priv *priv = netdev_priv(dev);

	अगर (features & NETIF_F_LOOPBACK)
		priv->ctrl_flags |= cpu_to_be32(MLX4_WQE_CTRL_FORCE_LOOPBACK);
	अन्यथा
		priv->ctrl_flags &= cpu_to_be32(~MLX4_WQE_CTRL_FORCE_LOOPBACK);

	priv->flags &= ~(MLX4_EN_FLAG_RX_FILTER_NEEDED|
			MLX4_EN_FLAG_ENABLE_HW_LOOPBACK);

	/* Drop the packet अगर SRIOV is not enabled
	 * and not perक्रमming the selftest or flb disabled
	 */
	अगर (mlx4_is_mfunc(priv->mdev->dev) &&
	    !(features & NETIF_F_LOOPBACK) && !priv->validate_loopback)
		priv->flags |= MLX4_EN_FLAG_RX_FILTER_NEEDED;

	/* Set dmac in Tx WQE अगर we are in SRIOV mode or अगर loopback selftest
	 * is requested
	 */
	अगर (mlx4_is_mfunc(priv->mdev->dev) || priv->validate_loopback)
		priv->flags |= MLX4_EN_FLAG_ENABLE_HW_LOOPBACK;

	mutex_lock(&priv->mdev->state_lock);
	अगर ((priv->mdev->dev->caps.flags2 &
	     MLX4_DEV_CAP_FLAG2_UPDATE_QP_SRC_CHECK_LB) &&
	    priv->rss_map.indir_qp && priv->rss_map.indir_qp->qpn) अणु
		पूर्णांक i;
		पूर्णांक err = 0;
		पूर्णांक loopback = !!(features & NETIF_F_LOOPBACK);

		क्रम (i = 0; i < priv->rx_ring_num; i++) अणु
			पूर्णांक ret;

			ret = mlx4_en_change_mcast_lb(priv,
						      &priv->rss_map.qps[i],
						      loopback);
			अगर (!err)
				err = ret;
		पूर्ण
		अगर (err)
			mlx4_warn(priv->mdev, "failed to change mcast loopback\n");
	पूर्ण
	mutex_unlock(&priv->mdev->state_lock);
पूर्ण

अटल व्योम mlx4_en_get_profile(काष्ठा mlx4_en_dev *mdev)
अणु
	काष्ठा mlx4_en_profile *params = &mdev->profile;
	पूर्णांक i;

	params->udp_rss = udp_rss;
	params->max_num_tx_rings_p_up = mlx4_low_memory_profile() ?
		MLX4_EN_MIN_TX_RING_P_UP :
		min_t(पूर्णांक, num_online_cpus(), MLX4_EN_MAX_TX_RING_P_UP);

	अगर (params->udp_rss && !(mdev->dev->caps.flags
					& MLX4_DEV_CAP_FLAG_UDP_RSS)) अणु
		mlx4_warn(mdev, "UDP RSS is not supported on this device\n");
		params->udp_rss = 0;
	पूर्ण
	क्रम (i = 1; i <= MLX4_MAX_PORTS; i++) अणु
		params->prof[i].rx_छोड़ो = !(pfcrx || pfctx);
		params->prof[i].rx_ppp = pfcrx;
		params->prof[i].tx_छोड़ो = !(pfcrx || pfctx);
		params->prof[i].tx_ppp = pfctx;
		अगर (mlx4_low_memory_profile()) अणु
			params->prof[i].tx_ring_size = MLX4_EN_MIN_TX_SIZE;
			params->prof[i].rx_ring_size = MLX4_EN_MIN_RX_SIZE;
		पूर्ण अन्यथा अणु
			params->prof[i].tx_ring_size = MLX4_EN_DEF_TX_RING_SIZE;
			params->prof[i].rx_ring_size = MLX4_EN_DEF_RX_RING_SIZE;
		पूर्ण
		params->prof[i].num_up = MLX4_EN_NUM_UP_LOW;
		params->prof[i].num_tx_rings_p_up = params->max_num_tx_rings_p_up;
		params->prof[i].tx_ring_num[TX] = params->max_num_tx_rings_p_up *
			params->prof[i].num_up;
		params->prof[i].rss_rings = 0;
		params->prof[i].अंतरभूत_thold = अंतरभूत_thold;
	पूर्ण
पूर्ण

अटल व्योम *mlx4_en_get_netdev(काष्ठा mlx4_dev *dev, व्योम *ctx, u8 port)
अणु
	काष्ठा mlx4_en_dev *endev = ctx;

	वापस endev->pndev[port];
पूर्ण

अटल व्योम mlx4_en_event(काष्ठा mlx4_dev *dev, व्योम *endev_ptr,
			  क्रमागत mlx4_dev_event event, अचिन्हित दीर्घ port)
अणु
	काष्ठा mlx4_en_dev *mdev = (काष्ठा mlx4_en_dev *) endev_ptr;
	काष्ठा mlx4_en_priv *priv;

	चयन (event) अणु
	हाल MLX4_DEV_EVENT_PORT_UP:
	हाल MLX4_DEV_EVENT_PORT_DOWN:
		अगर (!mdev->pndev[port])
			वापस;
		priv = netdev_priv(mdev->pndev[port]);
		/* To prevent races, we poll the link state in a separate
		  task rather than changing it here */
		priv->link_state = event;
		queue_work(mdev->workqueue, &priv->linkstate_task);
		अवरोध;

	हाल MLX4_DEV_EVENT_CATASTROPHIC_ERROR:
		mlx4_err(mdev, "Internal error detected, restarting device\n");
		अवरोध;

	हाल MLX4_DEV_EVENT_SLAVE_INIT:
	हाल MLX4_DEV_EVENT_SLAVE_SHUTDOWN:
		अवरोध;
	शेष:
		अगर (port < 1 || port > dev->caps.num_ports ||
		    !mdev->pndev[port])
			वापस;
		mlx4_warn(mdev, "Unhandled event %d for port %d\n", event,
			  (पूर्णांक) port);
	पूर्ण
पूर्ण

अटल व्योम mlx4_en_हटाओ(काष्ठा mlx4_dev *dev, व्योम *endev_ptr)
अणु
	काष्ठा mlx4_en_dev *mdev = endev_ptr;
	पूर्णांक i;

	mutex_lock(&mdev->state_lock);
	mdev->device_up = false;
	mutex_unlock(&mdev->state_lock);

	mlx4_क्रमeach_port(i, dev, MLX4_PORT_TYPE_ETH)
		अगर (mdev->pndev[i])
			mlx4_en_destroy_netdev(mdev->pndev[i]);

	flush_workqueue(mdev->workqueue);
	destroy_workqueue(mdev->workqueue);
	(व्योम) mlx4_mr_मुक्त(dev, &mdev->mr);
	iounmap(mdev->uar_map);
	mlx4_uar_मुक्त(dev, &mdev->priv_uar);
	mlx4_pd_मुक्त(dev, mdev->priv_pdn);
	अगर (mdev->nb.notअगरier_call)
		unरेजिस्टर_netdevice_notअगरier(&mdev->nb);
	kमुक्त(mdev);
पूर्ण

अटल व्योम mlx4_en_activate(काष्ठा mlx4_dev *dev, व्योम *ctx)
अणु
	पूर्णांक i;
	काष्ठा mlx4_en_dev *mdev = ctx;

	/* Create a netdev क्रम each port */
	mlx4_क्रमeach_port(i, dev, MLX4_PORT_TYPE_ETH) अणु
		mlx4_info(mdev, "Activating port:%d\n", i);
		अगर (mlx4_en_init_netdev(mdev, i, &mdev->profile.prof[i]))
			mdev->pndev[i] = शून्य;
	पूर्ण

	/* रेजिस्टर notअगरier */
	mdev->nb.notअगरier_call = mlx4_en_netdev_event;
	अगर (रेजिस्टर_netdevice_notअगरier(&mdev->nb)) अणु
		mdev->nb.notअगरier_call = शून्य;
		mlx4_err(mdev, "Failed to create notifier\n");
	पूर्ण
पूर्ण

अटल व्योम *mlx4_en_add(काष्ठा mlx4_dev *dev)
अणु
	काष्ठा mlx4_en_dev *mdev;
	पूर्णांक i;

	prपूर्णांकk_once(KERN_INFO "%s", mlx4_en_version);

	mdev = kzalloc(माप(*mdev), GFP_KERNEL);
	अगर (!mdev)
		जाओ err_मुक्त_res;

	अगर (mlx4_pd_alloc(dev, &mdev->priv_pdn))
		जाओ err_मुक्त_dev;

	अगर (mlx4_uar_alloc(dev, &mdev->priv_uar))
		जाओ err_pd;

	mdev->uar_map = ioremap((phys_addr_t) mdev->priv_uar.pfn << PAGE_SHIFT,
				PAGE_SIZE);
	अगर (!mdev->uar_map)
		जाओ err_uar;
	spin_lock_init(&mdev->uar_lock);

	mdev->dev = dev;
	mdev->dma_device = &dev->persist->pdev->dev;
	mdev->pdev = dev->persist->pdev;
	mdev->device_up = false;

	mdev->LSO_support = !!(dev->caps.flags & (1 << 15));
	अगर (!mdev->LSO_support)
		mlx4_warn(mdev, "LSO not supported, please upgrade to later FW version to enable LSO\n");

	अगर (mlx4_mr_alloc(mdev->dev, mdev->priv_pdn, 0, ~0ull,
			 MLX4_PERM_LOCAL_WRITE |  MLX4_PERM_LOCAL_READ,
			 0, 0, &mdev->mr)) अणु
		mlx4_err(mdev, "Failed allocating memory region\n");
		जाओ err_map;
	पूर्ण
	अगर (mlx4_mr_enable(mdev->dev, &mdev->mr)) अणु
		mlx4_err(mdev, "Failed enabling memory region\n");
		जाओ err_mr;
	पूर्ण

	/* Build device profile according to supplied module parameters */
	mlx4_en_get_profile(mdev);

	/* Configure which ports to start according to module parameters */
	mdev->port_cnt = 0;
	mlx4_क्रमeach_port(i, dev, MLX4_PORT_TYPE_ETH)
		mdev->port_cnt++;

	/* Set शेष number of RX rings*/
	mlx4_en_set_num_rx_rings(mdev);

	/* Create our own workqueue क्रम reset/multicast tasks
	 * Note: we cannot use the shared workqueue because of deadlocks caused
	 *       by the rtnl lock */
	mdev->workqueue = create_singlethपढ़ो_workqueue("mlx4_en");
	अगर (!mdev->workqueue)
		जाओ err_mr;

	/* At this stage all non-port specअगरic tasks are complete:
	 * mark the card state as up */
	mutex_init(&mdev->state_lock);
	mdev->device_up = true;

	वापस mdev;

err_mr:
	(व्योम) mlx4_mr_मुक्त(dev, &mdev->mr);
err_map:
	अगर (mdev->uar_map)
		iounmap(mdev->uar_map);
err_uar:
	mlx4_uar_मुक्त(dev, &mdev->priv_uar);
err_pd:
	mlx4_pd_मुक्त(dev, mdev->priv_pdn);
err_मुक्त_dev:
	kमुक्त(mdev);
err_मुक्त_res:
	वापस शून्य;
पूर्ण

अटल काष्ठा mlx4_पूर्णांकerface mlx4_en_पूर्णांकerface = अणु
	.add		= mlx4_en_add,
	.हटाओ		= mlx4_en_हटाओ,
	.event		= mlx4_en_event,
	.get_dev	= mlx4_en_get_netdev,
	.protocol	= MLX4_PROT_ETH,
	.activate	= mlx4_en_activate,
पूर्ण;

अटल व्योम mlx4_en_verअगरy_params(व्योम)
अणु
	अगर (pfctx > MAX_PFC_TX) अणु
		pr_warn("mlx4_en: WARNING: illegal module parameter pfctx 0x%x - should be in range 0-0x%x, will be changed to default (0)\n",
			pfctx, MAX_PFC_TX);
		pfctx = 0;
	पूर्ण

	अगर (pfcrx > MAX_PFC_RX) अणु
		pr_warn("mlx4_en: WARNING: illegal module parameter pfcrx 0x%x - should be in range 0-0x%x, will be changed to default (0)\n",
			pfcrx, MAX_PFC_RX);
		pfcrx = 0;
	पूर्ण

	अगर (अंतरभूत_thold < MIN_PKT_LEN || अंतरभूत_thold > MAX_INLINE) अणु
		pr_warn("mlx4_en: WARNING: illegal module parameter inline_thold %d - should be in range %d-%d, will be changed to default (%d)\n",
			अंतरभूत_thold, MIN_PKT_LEN, MAX_INLINE, MAX_INLINE);
		अंतरभूत_thold = MAX_INLINE;
	पूर्ण
पूर्ण

अटल पूर्णांक __init mlx4_en_init(व्योम)
अणु
	mlx4_en_verअगरy_params();
	mlx4_en_init_ptys2ethtool_map();

	वापस mlx4_रेजिस्टर_पूर्णांकerface(&mlx4_en_पूर्णांकerface);
पूर्ण

अटल व्योम __निकास mlx4_en_cleanup(व्योम)
अणु
	mlx4_unरेजिस्टर_पूर्णांकerface(&mlx4_en_पूर्णांकerface);
पूर्ण

module_init(mlx4_en_init);
module_निकास(mlx4_en_cleanup);

