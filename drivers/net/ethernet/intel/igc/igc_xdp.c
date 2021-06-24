<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (c) 2020, Intel Corporation. */

#समावेश "igc.h"
#समावेश "igc_xdp.h"

पूर्णांक igc_xdp_set_prog(काष्ठा igc_adapter *adapter, काष्ठा bpf_prog *prog,
		     काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा net_device *dev = adapter->netdev;
	bool अगर_running = netअगर_running(dev);
	काष्ठा bpf_prog *old_prog;

	अगर (dev->mtu > ETH_DATA_LEN) अणु
		/* For now, the driver करोesn't support XDP functionality with
		 * jumbo frames so we वापस error.
		 */
		NL_SET_ERR_MSG_MOD(extack, "Jumbo frames not supported");
		वापस -EOPNOTSUPP;
	पूर्ण

	अगर (अगर_running)
		igc_बंद(dev);

	old_prog = xchg(&adapter->xdp_prog, prog);
	अगर (old_prog)
		bpf_prog_put(old_prog);

	अगर (अगर_running)
		igc_खोलो(dev);

	वापस 0;
पूर्ण

पूर्णांक igc_xdp_रेजिस्टर_rxq_info(काष्ठा igc_ring *ring)
अणु
	काष्ठा net_device *dev = ring->netdev;
	पूर्णांक err;

	err = xdp_rxq_info_reg(&ring->xdp_rxq, dev, ring->queue_index, 0);
	अगर (err) अणु
		netdev_err(dev, "Failed to register xdp rxq info\n");
		वापस err;
	पूर्ण

	err = xdp_rxq_info_reg_mem_model(&ring->xdp_rxq, MEM_TYPE_PAGE_SHARED,
					 शून्य);
	अगर (err) अणु
		netdev_err(dev, "Failed to register xdp rxq mem model\n");
		xdp_rxq_info_unreg(&ring->xdp_rxq);
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

व्योम igc_xdp_unरेजिस्टर_rxq_info(काष्ठा igc_ring *ring)
अणु
	xdp_rxq_info_unreg(&ring->xdp_rxq);
पूर्ण
