<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* Copyright (c) 2019, Microsoft Corporation.
 *
 * Author:
 *   Haiyang Zhang <haiyangz@microsoft.com>
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/bpf.h>
#समावेश <linux/bpf_trace.h>
#समावेश <linux/kernel.h>
#समावेश <net/xdp.h>

#समावेश <linux/mutex.h>
#समावेश <linux/rtnetlink.h>

#समावेश "hyperv_net.h"

u32 netvsc_run_xdp(काष्ठा net_device *ndev, काष्ठा netvsc_channel *nvchan,
		   काष्ठा xdp_buff *xdp)
अणु
	व्योम *data = nvchan->rsc.data[0];
	u32 len = nvchan->rsc.len[0];
	काष्ठा page *page = शून्य;
	काष्ठा bpf_prog *prog;
	u32 act = XDP_PASS;

	xdp->data_hard_start = शून्य;

	rcu_पढ़ो_lock();
	prog = rcu_dereference(nvchan->bpf_prog);

	अगर (!prog)
		जाओ out;

	/* Ensure that the below स_नकल() won't overflow the page buffer. */
	अगर (len > ndev->mtu + ETH_HLEN) अणु
		act = XDP_DROP;
		जाओ out;
	पूर्ण

	/* allocate page buffer क्रम data */
	page = alloc_page(GFP_ATOMIC);
	अगर (!page) अणु
		act = XDP_DROP;
		जाओ out;
	पूर्ण

	xdp_init_buff(xdp, PAGE_SIZE, &nvchan->xdp_rxq);
	xdp_prepare_buff(xdp, page_address(page), NETVSC_XDP_HDRM, len, false);

	स_नकल(xdp->data, data, len);

	act = bpf_prog_run_xdp(prog, xdp);

	चयन (act) अणु
	हाल XDP_PASS:
	हाल XDP_TX:
	हाल XDP_DROP:
		अवरोध;

	हाल XDP_ABORTED:
		trace_xdp_exception(ndev, prog, act);
		अवरोध;

	शेष:
		bpf_warn_invalid_xdp_action(act);
	पूर्ण

out:
	rcu_पढ़ो_unlock();

	अगर (page && act != XDP_PASS && act != XDP_TX) अणु
		__मुक्त_page(page);
		xdp->data_hard_start = शून्य;
	पूर्ण

	वापस act;
पूर्ण

अचिन्हित पूर्णांक netvsc_xdp_fraglen(अचिन्हित पूर्णांक len)
अणु
	वापस SKB_DATA_ALIGN(len) +
	       SKB_DATA_ALIGN(माप(काष्ठा skb_shared_info));
पूर्ण

काष्ठा bpf_prog *netvsc_xdp_get(काष्ठा netvsc_device *nvdev)
अणु
	वापस rtnl_dereference(nvdev->chan_table[0].bpf_prog);
पूर्ण

पूर्णांक netvsc_xdp_set(काष्ठा net_device *dev, काष्ठा bpf_prog *prog,
		   काष्ठा netlink_ext_ack *extack,
		   काष्ठा netvsc_device *nvdev)
अणु
	काष्ठा bpf_prog *old_prog;
	पूर्णांक buf_max, i;

	old_prog = netvsc_xdp_get(nvdev);

	अगर (!old_prog && !prog)
		वापस 0;

	buf_max = NETVSC_XDP_HDRM + netvsc_xdp_fraglen(dev->mtu + ETH_HLEN);
	अगर (prog && buf_max > PAGE_SIZE) अणु
		netdev_err(dev, "XDP: mtu:%u too large, buf_max:%u\n",
			   dev->mtu, buf_max);
		NL_SET_ERR_MSG_MOD(extack, "XDP: mtu too large");

		वापस -EOPNOTSUPP;
	पूर्ण

	अगर (prog && (dev->features & NETIF_F_LRO)) अणु
		netdev_err(dev, "XDP: not support LRO\n");
		NL_SET_ERR_MSG_MOD(extack, "XDP: not support LRO");

		वापस -EOPNOTSUPP;
	पूर्ण

	अगर (prog)
		bpf_prog_add(prog, nvdev->num_chn - 1);

	क्रम (i = 0; i < nvdev->num_chn; i++)
		rcu_assign_poपूर्णांकer(nvdev->chan_table[i].bpf_prog, prog);

	अगर (old_prog)
		क्रम (i = 0; i < nvdev->num_chn; i++)
			bpf_prog_put(old_prog);

	वापस 0;
पूर्ण

पूर्णांक netvsc_vf_setxdp(काष्ठा net_device *vf_netdev, काष्ठा bpf_prog *prog)
अणु
	काष्ठा netdev_bpf xdp;
	bpf_op_t nकरो_bpf;
	पूर्णांक ret;

	ASSERT_RTNL();

	अगर (!vf_netdev)
		वापस 0;

	nकरो_bpf = vf_netdev->netdev_ops->nकरो_bpf;
	अगर (!nकरो_bpf)
		वापस 0;

	स_रखो(&xdp, 0, माप(xdp));

	अगर (prog)
		bpf_prog_inc(prog);

	xdp.command = XDP_SETUP_PROG;
	xdp.prog = prog;

	ret = nकरो_bpf(vf_netdev, &xdp);

	अगर (ret && prog)
		bpf_prog_put(prog);

	वापस ret;
पूर्ण

पूर्णांक netvsc_bpf(काष्ठा net_device *dev, काष्ठा netdev_bpf *bpf)
अणु
	काष्ठा net_device_context *ndevctx = netdev_priv(dev);
	काष्ठा netvsc_device *nvdev = rtnl_dereference(ndevctx->nvdev);
	काष्ठा net_device *vf_netdev = rtnl_dereference(ndevctx->vf_netdev);
	काष्ठा netlink_ext_ack *extack = bpf->extack;
	पूर्णांक ret;

	अगर (!nvdev || nvdev->destroy) अणु
		वापस -ENODEV;
	पूर्ण

	चयन (bpf->command) अणु
	हाल XDP_SETUP_PROG:
		ret = netvsc_xdp_set(dev, bpf->prog, extack, nvdev);

		अगर (ret)
			वापस ret;

		ret = netvsc_vf_setxdp(vf_netdev, bpf->prog);

		अगर (ret) अणु
			netdev_err(dev, "vf_setxdp failed:%d\n", ret);
			NL_SET_ERR_MSG_MOD(extack, "vf_setxdp failed");

			netvsc_xdp_set(dev, शून्य, extack, nvdev);
		पूर्ण

		वापस ret;

	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण
