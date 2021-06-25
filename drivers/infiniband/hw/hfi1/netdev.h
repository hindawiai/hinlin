<शैली गुरु>
/* SPDX-License-Identअगरier: (GPL-2.0 OR BSD-3-Clause) */
/*
 * Copyright(c) 2020 Intel Corporation.
 *
 */

#अगर_अघोषित HFI1_NETDEV_H
#घोषणा HFI1_NETDEV_H

#समावेश "hfi.h"

#समावेश <linux/netdevice.h>
#समावेश <linux/xarray.h>

/**
 * काष्ठा hfi1_netdev_rxq - Receive Queue क्रम HFI
 * Both IPoIB and VNIC netdevices will be working on the rx असलtraction.
 * @napi: napi object
 * @rx: ptr to netdev_rx
 * @rcd:  ptr to receive context data
 */
काष्ठा hfi1_netdev_rxq अणु
	काष्ठा napi_काष्ठा napi;
	काष्ठा hfi1_netdev_rx *rx;
	काष्ठा hfi1_ctxtdata *rcd;
पूर्ण;

/*
 * Number of netdev contexts used. Ensure it is less than or equal to
 * max queues supported by VNIC (HFI1_VNIC_MAX_QUEUE).
 */
#घोषणा HFI1_MAX_NETDEV_CTXTS   8

/* Number of NETDEV RSM entries */
#घोषणा NUM_NETDEV_MAP_ENTRIES HFI1_MAX_NETDEV_CTXTS

/**
 * काष्ठा hfi1_netdev_rx: data required to setup and run HFI netdev.
 * @rx_napi:	the dummy netdevice to support "polling" the receive contexts
 * @dd:		hfi1_devdata
 * @rxq:	poपूर्णांकer to dummy netdev receive queues.
 * @num_rx_q:	number of receive queues
 * @rmt_index:	first मुक्त index in RMT Array
 * @msix_start: first मुक्त MSI-X पूर्णांकerrupt vector.
 * @dev_tbl:	netdev table क्रम unique identअगरier VNIC and IPoIb VLANs.
 * @enabled:	atomic counter of netdevs enabling receive queues.
 *		When 0 NAPI will be disabled.
 * @netdevs:	atomic counter of netdevs using dummy netdev.
 *		When 0 receive queues will be मुक्तd.
 */
काष्ठा hfi1_netdev_rx अणु
	काष्ठा net_device rx_napi;
	काष्ठा hfi1_devdata *dd;
	काष्ठा hfi1_netdev_rxq *rxq;
	पूर्णांक num_rx_q;
	पूर्णांक rmt_start;
	काष्ठा xarray dev_tbl;
	/* count of enabled napi polls */
	atomic_t enabled;
	/* count of netdevs on top */
	atomic_t netdevs;
पूर्ण;

अटल अंतरभूत
पूर्णांक hfi1_netdev_ctxt_count(काष्ठा hfi1_devdata *dd)
अणु
	वापस dd->netdev_rx->num_rx_q;
पूर्ण

अटल अंतरभूत
काष्ठा hfi1_ctxtdata *hfi1_netdev_get_ctxt(काष्ठा hfi1_devdata *dd, पूर्णांक ctxt)
अणु
	वापस dd->netdev_rx->rxq[ctxt].rcd;
पूर्ण

अटल अंतरभूत
पूर्णांक hfi1_netdev_get_मुक्त_rmt_idx(काष्ठा hfi1_devdata *dd)
अणु
	वापस dd->netdev_rx->rmt_start;
पूर्ण

अटल अंतरभूत
व्योम hfi1_netdev_set_मुक्त_rmt_idx(काष्ठा hfi1_devdata *dd, पूर्णांक rmt_idx)
अणु
	dd->netdev_rx->rmt_start = rmt_idx;
पूर्ण

u32 hfi1_num_netdev_contexts(काष्ठा hfi1_devdata *dd, u32 available_contexts,
			     काष्ठा cpumask *cpu_mask);

व्योम hfi1_netdev_enable_queues(काष्ठा hfi1_devdata *dd);
व्योम hfi1_netdev_disable_queues(काष्ठा hfi1_devdata *dd);
पूर्णांक hfi1_netdev_rx_init(काष्ठा hfi1_devdata *dd);
पूर्णांक hfi1_netdev_rx_destroy(काष्ठा hfi1_devdata *dd);
पूर्णांक hfi1_alloc_rx(काष्ठा hfi1_devdata *dd);
व्योम hfi1_मुक्त_rx(काष्ठा hfi1_devdata *dd);
पूर्णांक hfi1_netdev_add_data(काष्ठा hfi1_devdata *dd, पूर्णांक id, व्योम *data);
व्योम *hfi1_netdev_हटाओ_data(काष्ठा hfi1_devdata *dd, पूर्णांक id);
व्योम *hfi1_netdev_get_data(काष्ठा hfi1_devdata *dd, पूर्णांक id);
व्योम *hfi1_netdev_get_first_data(काष्ठा hfi1_devdata *dd, पूर्णांक *start_id);

/* chip.c  */
पूर्णांक hfi1_netdev_rx_napi(काष्ठा napi_काष्ठा *napi, पूर्णांक budget);

#पूर्ण_अगर /* HFI1_NETDEV_H */
