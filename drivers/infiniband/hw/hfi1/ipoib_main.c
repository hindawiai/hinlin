<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0 OR BSD-3-Clause)
/*
 * Copyright(c) 2020 Intel Corporation.
 *
 */

/*
 * This file contains HFI1 support क्रम ipoib functionality
 */

#समावेश "ipoib.h"
#समावेश "hfi.h"

अटल u32 qpn_from_mac(u8 *mac_arr)
अणु
	वापस (u32)mac_arr[1] << 16 | mac_arr[2] << 8 | mac_arr[3];
पूर्ण

अटल पूर्णांक hfi1_ipoib_dev_init(काष्ठा net_device *dev)
अणु
	काष्ठा hfi1_ipoib_dev_priv *priv = hfi1_ipoib_priv(dev);
	पूर्णांक ret;

	dev->tstats = netdev_alloc_pcpu_stats(काष्ठा pcpu_sw_netstats);

	ret = priv->netdev_ops->nकरो_init(dev);
	अगर (ret)
		वापस ret;

	ret = hfi1_netdev_add_data(priv->dd,
				   qpn_from_mac(priv->netdev->dev_addr),
				   dev);
	अगर (ret < 0) अणु
		priv->netdev_ops->nकरो_uninit(dev);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम hfi1_ipoib_dev_uninit(काष्ठा net_device *dev)
अणु
	काष्ठा hfi1_ipoib_dev_priv *priv = hfi1_ipoib_priv(dev);

	hfi1_netdev_हटाओ_data(priv->dd, qpn_from_mac(priv->netdev->dev_addr));

	priv->netdev_ops->nकरो_uninit(dev);
पूर्ण

अटल पूर्णांक hfi1_ipoib_dev_खोलो(काष्ठा net_device *dev)
अणु
	काष्ठा hfi1_ipoib_dev_priv *priv = hfi1_ipoib_priv(dev);
	पूर्णांक ret;

	ret = priv->netdev_ops->nकरो_खोलो(dev);
	अगर (!ret) अणु
		काष्ठा hfi1_ibport *ibp = to_iport(priv->device,
						   priv->port_num);
		काष्ठा rvt_qp *qp;
		u32 qpn = qpn_from_mac(priv->netdev->dev_addr);

		rcu_पढ़ो_lock();
		qp = rvt_lookup_qpn(ib_to_rvt(priv->device), &ibp->rvp, qpn);
		अगर (!qp) अणु
			rcu_पढ़ो_unlock();
			priv->netdev_ops->nकरो_stop(dev);
			वापस -EINVAL;
		पूर्ण
		rvt_get_qp(qp);
		priv->qp = qp;
		rcu_पढ़ो_unlock();

		hfi1_netdev_enable_queues(priv->dd);
		hfi1_ipoib_napi_tx_enable(dev);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक hfi1_ipoib_dev_stop(काष्ठा net_device *dev)
अणु
	काष्ठा hfi1_ipoib_dev_priv *priv = hfi1_ipoib_priv(dev);

	अगर (!priv->qp)
		वापस 0;

	hfi1_ipoib_napi_tx_disable(dev);
	hfi1_netdev_disable_queues(priv->dd);

	rvt_put_qp(priv->qp);
	priv->qp = शून्य;

	वापस priv->netdev_ops->nकरो_stop(dev);
पूर्ण

अटल स्थिर काष्ठा net_device_ops hfi1_ipoib_netdev_ops = अणु
	.nकरो_init         = hfi1_ipoib_dev_init,
	.nकरो_uninit       = hfi1_ipoib_dev_uninit,
	.nकरो_खोलो         = hfi1_ipoib_dev_खोलो,
	.nकरो_stop         = hfi1_ipoib_dev_stop,
	.nकरो_get_stats64  = dev_get_tstats64,
पूर्ण;

अटल पूर्णांक hfi1_ipoib_mcast_attach(काष्ठा net_device *dev,
				   काष्ठा ib_device *device,
				   जोड़ ib_gid *mgid,
				   u16 mlid,
				   पूर्णांक set_qkey,
				   u32 qkey)
अणु
	काष्ठा hfi1_ipoib_dev_priv *priv = hfi1_ipoib_priv(dev);
	u32 qpn = (u32)qpn_from_mac(priv->netdev->dev_addr);
	काष्ठा hfi1_ibport *ibp = to_iport(priv->device, priv->port_num);
	काष्ठा rvt_qp *qp;
	पूर्णांक ret = -EINVAL;

	rcu_पढ़ो_lock();

	qp = rvt_lookup_qpn(ib_to_rvt(priv->device), &ibp->rvp, qpn);
	अगर (qp) अणु
		rvt_get_qp(qp);
		rcu_पढ़ो_unlock();
		अगर (set_qkey)
			priv->qkey = qkey;

		/* attach QP to multicast group */
		ret = ib_attach_mcast(&qp->ibqp, mgid, mlid);
		rvt_put_qp(qp);
	पूर्ण अन्यथा अणु
		rcu_पढ़ो_unlock();
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक hfi1_ipoib_mcast_detach(काष्ठा net_device *dev,
				   काष्ठा ib_device *device,
				   जोड़ ib_gid *mgid,
				   u16 mlid)
अणु
	काष्ठा hfi1_ipoib_dev_priv *priv = hfi1_ipoib_priv(dev);
	u32 qpn = (u32)qpn_from_mac(priv->netdev->dev_addr);
	काष्ठा hfi1_ibport *ibp = to_iport(priv->device, priv->port_num);
	काष्ठा rvt_qp *qp;
	पूर्णांक ret = -EINVAL;

	rcu_पढ़ो_lock();

	qp = rvt_lookup_qpn(ib_to_rvt(priv->device), &ibp->rvp, qpn);
	अगर (qp) अणु
		rvt_get_qp(qp);
		rcu_पढ़ो_unlock();
		ret = ib_detach_mcast(&qp->ibqp, mgid, mlid);
		rvt_put_qp(qp);
	पूर्ण अन्यथा अणु
		rcu_पढ़ो_unlock();
	पूर्ण
	वापस ret;
पूर्ण

अटल व्योम hfi1_ipoib_netdev_dtor(काष्ठा net_device *dev)
अणु
	काष्ठा hfi1_ipoib_dev_priv *priv = hfi1_ipoib_priv(dev);

	hfi1_ipoib_txreq_deinit(priv);
	hfi1_ipoib_rxq_deinit(priv->netdev);

	मुक्त_percpu(dev->tstats);
पूर्ण

अटल व्योम hfi1_ipoib_मुक्त_rdma_netdev(काष्ठा net_device *dev)
अणु
	hfi1_ipoib_netdev_dtor(dev);
	मुक्त_netdev(dev);
पूर्ण

अटल व्योम hfi1_ipoib_set_id(काष्ठा net_device *dev, पूर्णांक id)
अणु
	काष्ठा hfi1_ipoib_dev_priv *priv = hfi1_ipoib_priv(dev);

	priv->pkey_index = (u16)id;
	ib_query_pkey(priv->device,
		      priv->port_num,
		      priv->pkey_index,
		      &priv->pkey);
पूर्ण

अटल पूर्णांक hfi1_ipoib_setup_rn(काष्ठा ib_device *device,
			       u32 port_num,
			       काष्ठा net_device *netdev,
			       व्योम *param)
अणु
	काष्ठा hfi1_devdata *dd = dd_from_ibdev(device);
	काष्ठा rdma_netdev *rn = netdev_priv(netdev);
	काष्ठा hfi1_ipoib_dev_priv *priv;
	पूर्णांक rc;

	rn->send = hfi1_ipoib_send;
	rn->tx_समयout = hfi1_ipoib_tx_समयout;
	rn->attach_mcast = hfi1_ipoib_mcast_attach;
	rn->detach_mcast = hfi1_ipoib_mcast_detach;
	rn->set_id = hfi1_ipoib_set_id;
	rn->hca = device;
	rn->port_num = port_num;
	rn->mtu = netdev->mtu;

	priv = hfi1_ipoib_priv(netdev);
	priv->dd = dd;
	priv->netdev = netdev;
	priv->device = device;
	priv->port_num = port_num;
	priv->netdev_ops = netdev->netdev_ops;

	netdev->netdev_ops = &hfi1_ipoib_netdev_ops;

	ib_query_pkey(device, port_num, priv->pkey_index, &priv->pkey);

	rc = hfi1_ipoib_txreq_init(priv);
	अगर (rc) अणु
		dd_dev_err(dd, "IPoIB netdev TX init - failed(%d)\n", rc);
		hfi1_ipoib_मुक्त_rdma_netdev(netdev);
		वापस rc;
	पूर्ण

	rc = hfi1_ipoib_rxq_init(netdev);
	अगर (rc) अणु
		dd_dev_err(dd, "IPoIB netdev RX init - failed(%d)\n", rc);
		hfi1_ipoib_मुक्त_rdma_netdev(netdev);
		वापस rc;
	पूर्ण

	netdev->priv_deकाष्ठाor = hfi1_ipoib_netdev_dtor;
	netdev->needs_मुक्त_netdev = true;

	वापस 0;
पूर्ण

पूर्णांक hfi1_ipoib_rn_get_params(काष्ठा ib_device *device,
			     u32 port_num,
			     क्रमागत rdma_netdev_t type,
			     काष्ठा rdma_netdev_alloc_params *params)
अणु
	काष्ठा hfi1_devdata *dd = dd_from_ibdev(device);

	अगर (type != RDMA_NETDEV_IPOIB)
		वापस -EOPNOTSUPP;

	अगर (!HFI1_CAP_IS_KSET(AIP) || !dd->num_netdev_contexts)
		वापस -EOPNOTSUPP;

	अगर (!port_num || port_num > dd->num_pports)
		वापस -EINVAL;

	params->माप_priv = माप(काष्ठा hfi1_ipoib_rdma_netdev);
	params->txqs = dd->num_sdma;
	params->rxqs = dd->num_netdev_contexts;
	params->param = शून्य;
	params->initialize_rdma_netdev = hfi1_ipoib_setup_rn;

	वापस 0;
पूर्ण
