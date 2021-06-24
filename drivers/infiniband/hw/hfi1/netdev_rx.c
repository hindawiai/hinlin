<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0 OR BSD-3-Clause)
/*
 * Copyright(c) 2020 Intel Corporation.
 *
 */

/*
 * This file contains HFI1 support क्रम netdev RX functionality
 */

#समावेश "sdma.h"
#समावेश "verbs.h"
#समावेश "netdev.h"
#समावेश "hfi.h"

#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <rdma/ib_verbs.h>

अटल पूर्णांक hfi1_netdev_setup_ctxt(काष्ठा hfi1_netdev_rx *rx,
				  काष्ठा hfi1_ctxtdata *uctxt)
अणु
	अचिन्हित पूर्णांक rcvctrl_ops;
	काष्ठा hfi1_devdata *dd = rx->dd;
	पूर्णांक ret;

	uctxt->rhf_rcv_function_map = netdev_rhf_rcv_functions;
	uctxt->करो_पूर्णांकerrupt = &handle_receive_पूर्णांकerrupt_napi_sp;

	/* Now allocate the RcvHdr queue and eager buffers. */
	ret = hfi1_create_rcvhdrq(dd, uctxt);
	अगर (ret)
		जाओ करोne;

	ret = hfi1_setup_eagerbufs(uctxt);
	अगर (ret)
		जाओ करोne;

	clear_rcvhdrtail(uctxt);

	rcvctrl_ops = HFI1_RCVCTRL_CTXT_DIS;
	rcvctrl_ops |= HFI1_RCVCTRL_INTRAVAIL_DIS;

	अगर (!HFI1_CAP_KGET_MASK(uctxt->flags, MULTI_PKT_EGR))
		rcvctrl_ops |= HFI1_RCVCTRL_ONE_PKT_EGR_ENB;
	अगर (HFI1_CAP_KGET_MASK(uctxt->flags, NODROP_EGR_FULL))
		rcvctrl_ops |= HFI1_RCVCTRL_NO_EGR_DROP_ENB;
	अगर (HFI1_CAP_KGET_MASK(uctxt->flags, NODROP_RHQ_FULL))
		rcvctrl_ops |= HFI1_RCVCTRL_NO_RHQ_DROP_ENB;
	अगर (HFI1_CAP_KGET_MASK(uctxt->flags, DMA_RTAIL))
		rcvctrl_ops |= HFI1_RCVCTRL_TAILUPD_ENB;

	hfi1_rcvctrl(uctxt->dd, rcvctrl_ops, uctxt);
करोne:
	वापस ret;
पूर्ण

अटल पूर्णांक hfi1_netdev_allocate_ctxt(काष्ठा hfi1_devdata *dd,
				     काष्ठा hfi1_ctxtdata **ctxt)
अणु
	काष्ठा hfi1_ctxtdata *uctxt;
	पूर्णांक ret;

	अगर (dd->flags & HFI1_FROZEN)
		वापस -EIO;

	ret = hfi1_create_ctxtdata(dd->pport, dd->node, &uctxt);
	अगर (ret < 0) अणु
		dd_dev_err(dd, "Unable to create ctxtdata, failing open\n");
		वापस -ENOMEM;
	पूर्ण

	uctxt->flags = HFI1_CAP_KGET(MULTI_PKT_EGR) |
		HFI1_CAP_KGET(NODROP_RHQ_FULL) |
		HFI1_CAP_KGET(NODROP_EGR_FULL) |
		HFI1_CAP_KGET(DMA_RTAIL);
	/* Netdev contexts are always NO_RDMA_RTAIL */
	uctxt->fast_handler = handle_receive_पूर्णांकerrupt_napi_fp;
	uctxt->slow_handler = handle_receive_पूर्णांकerrupt_napi_sp;
	hfi1_set_seq_cnt(uctxt, 1);
	uctxt->is_vnic = true;

	hfi1_stats.sps_ctxts++;

	dd_dev_info(dd, "created netdev context %d\n", uctxt->ctxt);
	*ctxt = uctxt;

	वापस 0;
पूर्ण

अटल व्योम hfi1_netdev_deallocate_ctxt(काष्ठा hfi1_devdata *dd,
					काष्ठा hfi1_ctxtdata *uctxt)
अणु
	flush_wc();

	/*
	 * Disable receive context and पूर्णांकerrupt available, reset all
	 * RcvCtxtCtrl bits to शेष values.
	 */
	hfi1_rcvctrl(dd, HFI1_RCVCTRL_CTXT_DIS |
		     HFI1_RCVCTRL_TIDFLOW_DIS |
		     HFI1_RCVCTRL_INTRAVAIL_DIS |
		     HFI1_RCVCTRL_ONE_PKT_EGR_DIS |
		     HFI1_RCVCTRL_NO_RHQ_DROP_DIS |
		     HFI1_RCVCTRL_NO_EGR_DROP_DIS, uctxt);

	अगर (uctxt->msix_पूर्णांकr != CCE_NUM_MSIX_VECTORS)
		msix_मुक्त_irq(dd, uctxt->msix_पूर्णांकr);

	uctxt->msix_पूर्णांकr = CCE_NUM_MSIX_VECTORS;
	uctxt->event_flags = 0;

	hfi1_clear_tids(uctxt);
	hfi1_clear_ctxt_pkey(dd, uctxt);

	hfi1_stats.sps_ctxts--;

	hfi1_मुक्त_ctxt(uctxt);
पूर्ण

अटल पूर्णांक hfi1_netdev_allot_ctxt(काष्ठा hfi1_netdev_rx *rx,
				  काष्ठा hfi1_ctxtdata **ctxt)
अणु
	पूर्णांक rc;
	काष्ठा hfi1_devdata *dd = rx->dd;

	rc = hfi1_netdev_allocate_ctxt(dd, ctxt);
	अगर (rc) अणु
		dd_dev_err(dd, "netdev ctxt alloc failed %d\n", rc);
		वापस rc;
	पूर्ण

	rc = hfi1_netdev_setup_ctxt(rx, *ctxt);
	अगर (rc) अणु
		dd_dev_err(dd, "netdev ctxt setup failed %d\n", rc);
		hfi1_netdev_deallocate_ctxt(dd, *ctxt);
		*ctxt = शून्य;
	पूर्ण

	वापस rc;
पूर्ण

/**
 * hfi1_num_netdev_contexts - Count of netdev recv contexts to use.
 * @dd: device on which to allocate netdev contexts
 * @available_contexts: count of available receive contexts
 * @cpu_mask: mask of possible cpus to include क्रम contexts
 *
 * Return: count of physical cores on a node or the reमुख्यing available recv
 * contexts क्रम netdev recv context usage up to the maximum of
 * HFI1_MAX_NETDEV_CTXTS.
 * A value of 0 can be वापसed when acceleration is explicitly turned off,
 * a memory allocation error occurs or when there are no available contexts.
 *
 */
u32 hfi1_num_netdev_contexts(काष्ठा hfi1_devdata *dd, u32 available_contexts,
			     काष्ठा cpumask *cpu_mask)
अणु
	cpumask_var_t node_cpu_mask;
	अचिन्हित पूर्णांक available_cpus;

	अगर (!HFI1_CAP_IS_KSET(AIP))
		वापस 0;

	/* Always give user contexts priority over netdev contexts */
	अगर (available_contexts == 0) अणु
		dd_dev_info(dd, "No receive contexts available for netdevs.\n");
		वापस 0;
	पूर्ण

	अगर (!zalloc_cpumask_var(&node_cpu_mask, GFP_KERNEL)) अणु
		dd_dev_err(dd, "Unable to allocate cpu_mask for netdevs.\n");
		वापस 0;
	पूर्ण

	cpumask_and(node_cpu_mask, cpu_mask, cpumask_of_node(dd->node));

	available_cpus = cpumask_weight(node_cpu_mask);

	मुक्त_cpumask_var(node_cpu_mask);

	वापस min3(available_cpus, available_contexts,
		    (u32)HFI1_MAX_NETDEV_CTXTS);
पूर्ण

अटल पूर्णांक hfi1_netdev_rxq_init(काष्ठा hfi1_netdev_rx *rx)
अणु
	पूर्णांक i;
	पूर्णांक rc;
	काष्ठा hfi1_devdata *dd = rx->dd;
	काष्ठा net_device *dev = &rx->rx_napi;

	rx->num_rx_q = dd->num_netdev_contexts;
	rx->rxq = kसुस्मृति_node(rx->num_rx_q, माप(*rx->rxq),
			       GFP_KERNEL, dd->node);

	अगर (!rx->rxq) अणु
		dd_dev_err(dd, "Unable to allocate netdev queue data\n");
		वापस (-ENOMEM);
	पूर्ण

	क्रम (i = 0; i < rx->num_rx_q; i++) अणु
		काष्ठा hfi1_netdev_rxq *rxq = &rx->rxq[i];

		rc = hfi1_netdev_allot_ctxt(rx, &rxq->rcd);
		अगर (rc)
			जाओ bail_context_irq_failure;

		hfi1_rcd_get(rxq->rcd);
		rxq->rx = rx;
		rxq->rcd->napi = &rxq->napi;
		dd_dev_info(dd, "Setting rcv queue %d napi to context %d\n",
			    i, rxq->rcd->ctxt);
		/*
		 * Disable BUSY_POLL on this NAPI as this is not supported
		 * right now.
		 */
		set_bit(NAPI_STATE_NO_BUSY_POLL, &rxq->napi.state);
		netअगर_napi_add(dev, &rxq->napi, hfi1_netdev_rx_napi, 64);
		rc = msix_netdev_request_rcd_irq(rxq->rcd);
		अगर (rc)
			जाओ bail_context_irq_failure;
	पूर्ण

	वापस 0;

bail_context_irq_failure:
	dd_dev_err(dd, "Unable to allot receive context\n");
	क्रम (; i >= 0; i--) अणु
		काष्ठा hfi1_netdev_rxq *rxq = &rx->rxq[i];

		अगर (rxq->rcd) अणु
			hfi1_netdev_deallocate_ctxt(dd, rxq->rcd);
			hfi1_rcd_put(rxq->rcd);
			rxq->rcd = शून्य;
		पूर्ण
	पूर्ण
	kमुक्त(rx->rxq);
	rx->rxq = शून्य;

	वापस rc;
पूर्ण

अटल व्योम hfi1_netdev_rxq_deinit(काष्ठा hfi1_netdev_rx *rx)
अणु
	पूर्णांक i;
	काष्ठा hfi1_devdata *dd = rx->dd;

	क्रम (i = 0; i < rx->num_rx_q; i++) अणु
		काष्ठा hfi1_netdev_rxq *rxq = &rx->rxq[i];

		netअगर_napi_del(&rxq->napi);
		hfi1_netdev_deallocate_ctxt(dd, rxq->rcd);
		hfi1_rcd_put(rxq->rcd);
		rxq->rcd = शून्य;
	पूर्ण

	kमुक्त(rx->rxq);
	rx->rxq = शून्य;
	rx->num_rx_q = 0;
पूर्ण

अटल व्योम enable_queues(काष्ठा hfi1_netdev_rx *rx)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < rx->num_rx_q; i++) अणु
		काष्ठा hfi1_netdev_rxq *rxq = &rx->rxq[i];

		dd_dev_info(rx->dd, "enabling queue %d on context %d\n", i,
			    rxq->rcd->ctxt);
		napi_enable(&rxq->napi);
		hfi1_rcvctrl(rx->dd,
			     HFI1_RCVCTRL_CTXT_ENB | HFI1_RCVCTRL_INTRAVAIL_ENB,
			     rxq->rcd);
	पूर्ण
पूर्ण

अटल व्योम disable_queues(काष्ठा hfi1_netdev_rx *rx)
अणु
	पूर्णांक i;

	msix_netdev_synchronize_irq(rx->dd);

	क्रम (i = 0; i < rx->num_rx_q; i++) अणु
		काष्ठा hfi1_netdev_rxq *rxq = &rx->rxq[i];

		dd_dev_info(rx->dd, "disabling queue %d on context %d\n", i,
			    rxq->rcd->ctxt);

		/* रुको क्रम napi अगर it was scheduled */
		hfi1_rcvctrl(rx->dd,
			     HFI1_RCVCTRL_CTXT_DIS | HFI1_RCVCTRL_INTRAVAIL_DIS,
			     rxq->rcd);
		napi_synchronize(&rxq->napi);
		napi_disable(&rxq->napi);
	पूर्ण
पूर्ण

/**
 * hfi1_netdev_rx_init - Incrememnts netdevs counter. When called first समय,
 * it allocates receive queue data and calls netअगर_napi_add
 * क्रम each queue.
 *
 * @dd: hfi1 dev data
 */
पूर्णांक hfi1_netdev_rx_init(काष्ठा hfi1_devdata *dd)
अणु
	काष्ठा hfi1_netdev_rx *rx = dd->netdev_rx;
	पूर्णांक res;

	अगर (atomic_fetch_inc(&rx->netdevs))
		वापस 0;

	mutex_lock(&hfi1_mutex);
	res = hfi1_netdev_rxq_init(rx);
	mutex_unlock(&hfi1_mutex);
	वापस res;
पूर्ण

/**
 * hfi1_netdev_rx_destroy - Decrements netdevs counter, when it reaches 0
 * napi is deleted and receive queses memory is मुक्तd.
 *
 * @dd: hfi1 dev data
 */
पूर्णांक hfi1_netdev_rx_destroy(काष्ठा hfi1_devdata *dd)
अणु
	काष्ठा hfi1_netdev_rx *rx = dd->netdev_rx;

	/* destroy the RX queues only अगर it is the last netdev going away */
	अगर (atomic_fetch_add_unless(&rx->netdevs, -1, 0) == 1) अणु
		mutex_lock(&hfi1_mutex);
		hfi1_netdev_rxq_deinit(rx);
		mutex_unlock(&hfi1_mutex);
	पूर्ण

	वापस 0;
पूर्ण

/**
 * hfi1_alloc_rx - Allocates the rx support काष्ठाure
 * @dd: hfi1 dev data
 *
 * Allocate the rx काष्ठाure to support gathering the receive
 * resources and the dummy netdev.
 *
 * Updates dd काष्ठा poपूर्णांकer upon success.
 *
 * Return: 0 (success) -error on failure
 *
 */
पूर्णांक hfi1_alloc_rx(काष्ठा hfi1_devdata *dd)
अणु
	काष्ठा hfi1_netdev_rx *rx;

	dd_dev_info(dd, "allocating rx size %ld\n", माप(*rx));
	rx = kzalloc_node(माप(*rx), GFP_KERNEL, dd->node);

	अगर (!rx)
		वापस -ENOMEM;
	rx->dd = dd;
	init_dummy_netdev(&rx->rx_napi);

	xa_init(&rx->dev_tbl);
	atomic_set(&rx->enabled, 0);
	atomic_set(&rx->netdevs, 0);
	dd->netdev_rx = rx;

	वापस 0;
पूर्ण

व्योम hfi1_मुक्त_rx(काष्ठा hfi1_devdata *dd)
अणु
	अगर (dd->netdev_rx) अणु
		dd_dev_info(dd, "hfi1 rx freed\n");
		kमुक्त(dd->netdev_rx);
		dd->netdev_rx = शून्य;
	पूर्ण
पूर्ण

/**
 * hfi1_netdev_enable_queues - This is napi enable function.
 * It enables napi objects associated with queues.
 * When at least one device has called it it increments atomic counter.
 * Disable function decrements counter and when it is 0,
 * calls napi_disable क्रम every queue.
 *
 * @dd: hfi1 dev data
 */
व्योम hfi1_netdev_enable_queues(काष्ठा hfi1_devdata *dd)
अणु
	काष्ठा hfi1_netdev_rx *rx;

	अगर (!dd->netdev_rx)
		वापस;

	rx = dd->netdev_rx;
	अगर (atomic_fetch_inc(&rx->enabled))
		वापस;

	mutex_lock(&hfi1_mutex);
	enable_queues(rx);
	mutex_unlock(&hfi1_mutex);
पूर्ण

व्योम hfi1_netdev_disable_queues(काष्ठा hfi1_devdata *dd)
अणु
	काष्ठा hfi1_netdev_rx *rx;

	अगर (!dd->netdev_rx)
		वापस;

	rx = dd->netdev_rx;
	अगर (atomic_dec_अगर_positive(&rx->enabled))
		वापस;

	mutex_lock(&hfi1_mutex);
	disable_queues(rx);
	mutex_unlock(&hfi1_mutex);
पूर्ण

/**
 * hfi1_netdev_add_data - Registers data with unique identअगरier
 * to be requested later this is needed क्रम VNIC and IPoIB VLANs
 * implementations.
 * This call is रक्षित by mutex idr_lock.
 *
 * @dd: hfi1 dev data
 * @id: requested पूर्णांकeger id up to पूर्णांक_उच्च
 * @data: data to be associated with index
 */
पूर्णांक hfi1_netdev_add_data(काष्ठा hfi1_devdata *dd, पूर्णांक id, व्योम *data)
अणु
	काष्ठा hfi1_netdev_rx *rx = dd->netdev_rx;

	वापस xa_insert(&rx->dev_tbl, id, data, GFP_NOWAIT);
पूर्ण

/**
 * hfi1_netdev_हटाओ_data - Removes data with previously given id.
 * Returns the reference to हटाओd entry.
 *
 * @dd: hfi1 dev data
 * @id: requested पूर्णांकeger id up to पूर्णांक_उच्च
 */
व्योम *hfi1_netdev_हटाओ_data(काष्ठा hfi1_devdata *dd, पूर्णांक id)
अणु
	काष्ठा hfi1_netdev_rx *rx = dd->netdev_rx;

	वापस xa_erase(&rx->dev_tbl, id);
पूर्ण

/**
 * hfi1_netdev_get_data - Gets data with given id
 *
 * @dd: hfi1 dev data
 * @id: requested पूर्णांकeger id up to पूर्णांक_उच्च
 */
व्योम *hfi1_netdev_get_data(काष्ठा hfi1_devdata *dd, पूर्णांक id)
अणु
	काष्ठा hfi1_netdev_rx *rx = dd->netdev_rx;

	वापस xa_load(&rx->dev_tbl, id);
पूर्ण

/**
 * hfi1_netdev_get_first_data - Gets first entry with greater or equal id.
 *
 * @dd: hfi1 dev data
 * @start_id: requested पूर्णांकeger id up to पूर्णांक_उच्च
 */
व्योम *hfi1_netdev_get_first_data(काष्ठा hfi1_devdata *dd, पूर्णांक *start_id)
अणु
	काष्ठा hfi1_netdev_rx *rx = dd->netdev_rx;
	अचिन्हित दीर्घ index = *start_id;
	व्योम *ret;

	ret = xa_find(&rx->dev_tbl, &index, अच_पूर्णांक_उच्च, XA_PRESENT);
	*start_id = (पूर्णांक)index;
	वापस ret;
पूर्ण
