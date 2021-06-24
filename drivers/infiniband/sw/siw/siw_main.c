<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 or BSD-3-Clause

/* Authors: Bernard Metzler <bmt@zurich.ibm.com> */
/* Copyright (c) 2008-2019, IBM Corporation */

#समावेश <linux/init.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/netdevice.h>
#समावेश <linux/inetdevice.h>
#समावेश <net/net_namespace.h>
#समावेश <linux/rtnetlink.h>
#समावेश <linux/अगर_arp.h>
#समावेश <linux/list.h>
#समावेश <linux/kernel.h>
#समावेश <linux/sched.h>
#समावेश <linux/module.h>
#समावेश <linux/dma-mapping.h>

#समावेश <net/addrconf.h>
#समावेश <rdma/ib_verbs.h>
#समावेश <rdma/ib_user_verbs.h>
#समावेश <rdma/rdma_netlink.h>
#समावेश <linux/kthपढ़ो.h>

#समावेश "siw.h"
#समावेश "siw_verbs.h"

MODULE_AUTHOR("Bernard Metzler");
MODULE_DESCRIPTION("Software iWARP Driver");
MODULE_LICENSE("Dual BSD/GPL");

/* transmit from user buffer, अगर possible */
स्थिर bool zcopy_tx = true;

/* Restrict usage of GSO, अगर hardware peer iwarp is unable to process
 * large packets. try_gso = true lets siw try to use local GSO,
 * अगर peer agrees.  Not using GSO severly limits siw maximum tx bandwidth.
 */
स्थिर bool try_gso;

/* Attach siw also with loopback devices */
स्थिर bool loopback_enabled = true;

/* We try to negotiate CRC on, अगर true */
स्थिर bool mpa_crc_required;

/* MPA CRC on/off enक्रमced */
स्थिर bool mpa_crc_strict;

/* Control TCP_NODELAY socket option */
स्थिर bool siw_tcp_nagle;

/* Select MPA version to be used during connection setup */
u_अक्षर mpa_version = MPA_REVISION_2;

/* Selects MPA P2P mode (additional handshake during connection
 * setup, अगर true.
 */
स्थिर bool peer_to_peer;

काष्ठा task_काष्ठा *siw_tx_thपढ़ो[NR_CPUS];
काष्ठा crypto_shash *siw_crypto_shash;

अटल पूर्णांक siw_device_रेजिस्टर(काष्ठा siw_device *sdev, स्थिर अक्षर *name)
अणु
	काष्ठा ib_device *base_dev = &sdev->base_dev;
	अटल पूर्णांक dev_id = 1;
	पूर्णांक rv;

	sdev->venकरोr_part_id = dev_id++;

	rv = ib_रेजिस्टर_device(base_dev, name, शून्य);
	अगर (rv) अणु
		pr_warn("siw: device registration error %d\n", rv);
		वापस rv;
	पूर्ण

	siw_dbg(base_dev, "HWaddr=%pM\n", sdev->netdev->dev_addr);

	वापस 0;
पूर्ण

अटल व्योम siw_device_cleanup(काष्ठा ib_device *base_dev)
अणु
	काष्ठा siw_device *sdev = to_siw_dev(base_dev);

	xa_destroy(&sdev->qp_xa);
	xa_destroy(&sdev->mem_xa);
पूर्ण

अटल पूर्णांक siw_create_tx_thपढ़ोs(व्योम)
अणु
	पूर्णांक cpu, asचिन्हित = 0;

	क्रम_each_online_cpu(cpu) अणु
		/* Skip HT cores */
		अगर (cpu % cpumask_weight(topology_sibling_cpumask(cpu)))
			जारी;

		siw_tx_thपढ़ो[cpu] =
			kthपढ़ो_create(siw_run_sq, (अचिन्हित दीर्घ *)(दीर्घ)cpu,
				       "siw_tx/%d", cpu);
		अगर (IS_ERR(siw_tx_thपढ़ो[cpu])) अणु
			siw_tx_thपढ़ो[cpu] = शून्य;
			जारी;
		पूर्ण
		kthपढ़ो_bind(siw_tx_thपढ़ो[cpu], cpu);

		wake_up_process(siw_tx_thपढ़ो[cpu]);
		asचिन्हित++;
	पूर्ण
	वापस asचिन्हित;
पूर्ण

अटल पूर्णांक siw_dev_qualअगरied(काष्ठा net_device *netdev)
अणु
	/*
	 * Additional hardware support can be added here
	 * (e.g. ARPHRD_FDDI, ARPHRD_ATM, ...) - see
	 * <linux/अगर_arp.h> क्रम type identअगरiers.
	 */
	अगर (netdev->type == ARPHRD_ETHER || netdev->type == ARPHRD_IEEE802 ||
	    (netdev->type == ARPHRD_LOOPBACK && loopback_enabled))
		वापस 1;

	वापस 0;
पूर्ण

अटल DEFINE_PER_CPU(atomic_t, siw_use_cnt);

अटल काष्ठा अणु
	काष्ठा cpumask **tx_valid_cpus;
	पूर्णांक num_nodes;
पूर्ण siw_cpu_info;

अटल पूर्णांक siw_init_cpulist(व्योम)
अणु
	पूर्णांक i, num_nodes = nr_node_ids;

	स_रखो(siw_tx_thपढ़ो, 0, माप(siw_tx_thपढ़ो));

	siw_cpu_info.num_nodes = num_nodes;

	siw_cpu_info.tx_valid_cpus =
		kसुस्मृति(num_nodes, माप(काष्ठा cpumask *), GFP_KERNEL);
	अगर (!siw_cpu_info.tx_valid_cpus) अणु
		siw_cpu_info.num_nodes = 0;
		वापस -ENOMEM;
	पूर्ण
	क्रम (i = 0; i < siw_cpu_info.num_nodes; i++) अणु
		siw_cpu_info.tx_valid_cpus[i] =
			kzalloc(माप(काष्ठा cpumask), GFP_KERNEL);
		अगर (!siw_cpu_info.tx_valid_cpus[i])
			जाओ out_err;

		cpumask_clear(siw_cpu_info.tx_valid_cpus[i]);
	पूर्ण
	क्रम_each_possible_cpu(i)
		cpumask_set_cpu(i, siw_cpu_info.tx_valid_cpus[cpu_to_node(i)]);

	वापस 0;

out_err:
	siw_cpu_info.num_nodes = 0;
	जबतक (--i >= 0)
		kमुक्त(siw_cpu_info.tx_valid_cpus[i]);
	kमुक्त(siw_cpu_info.tx_valid_cpus);
	siw_cpu_info.tx_valid_cpus = शून्य;

	वापस -ENOMEM;
पूर्ण

अटल व्योम siw_destroy_cpulist(व्योम)
अणु
	पूर्णांक i = 0;

	जबतक (i < siw_cpu_info.num_nodes)
		kमुक्त(siw_cpu_info.tx_valid_cpus[i++]);

	kमुक्त(siw_cpu_info.tx_valid_cpus);
पूर्ण

/*
 * Choose CPU with least number of active QP's from NUMA node of
 * TX पूर्णांकerface.
 */
पूर्णांक siw_get_tx_cpu(काष्ठा siw_device *sdev)
अणु
	स्थिर काष्ठा cpumask *tx_cpumask;
	पूर्णांक i, num_cpus, cpu, min_use, node = sdev->numa_node, tx_cpu = -1;

	अगर (node < 0)
		tx_cpumask = cpu_online_mask;
	अन्यथा
		tx_cpumask = siw_cpu_info.tx_valid_cpus[node];

	num_cpus = cpumask_weight(tx_cpumask);
	अगर (!num_cpus) अणु
		/* no CPU on this NUMA node */
		tx_cpumask = cpu_online_mask;
		num_cpus = cpumask_weight(tx_cpumask);
	पूर्ण
	अगर (!num_cpus)
		जाओ out;

	cpu = cpumask_first(tx_cpumask);

	क्रम (i = 0, min_use = SIW_MAX_QP; i < num_cpus;
	     i++, cpu = cpumask_next(cpu, tx_cpumask)) अणु
		पूर्णांक usage;

		/* Skip any cores which have no TX thपढ़ो */
		अगर (!siw_tx_thपढ़ो[cpu])
			जारी;

		usage = atomic_पढ़ो(&per_cpu(siw_use_cnt, cpu));
		अगर (usage <= min_use) अणु
			tx_cpu = cpu;
			min_use = usage;
		पूर्ण
	पूर्ण
	siw_dbg(&sdev->base_dev,
		"tx cpu %d, node %d, %d qp's\n", tx_cpu, node, min_use);

out:
	अगर (tx_cpu >= 0)
		atomic_inc(&per_cpu(siw_use_cnt, tx_cpu));
	अन्यथा
		pr_warn("siw: no tx cpu found\n");

	वापस tx_cpu;
पूर्ण

व्योम siw_put_tx_cpu(पूर्णांक cpu)
अणु
	atomic_dec(&per_cpu(siw_use_cnt, cpu));
पूर्ण

अटल काष्ठा ib_qp *siw_get_base_qp(काष्ठा ib_device *base_dev, पूर्णांक id)
अणु
	काष्ठा siw_qp *qp = siw_qp_id2obj(to_siw_dev(base_dev), id);

	अगर (qp) अणु
		/*
		 * siw_qp_id2obj() increments object reference count
		 */
		siw_qp_put(qp);
		वापस &qp->base_qp;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल स्थिर काष्ठा ib_device_ops siw_device_ops = अणु
	.owner = THIS_MODULE,
	.uverbs_abi_ver = SIW_ABI_VERSION,
	.driver_id = RDMA_DRIVER_SIW,

	.alloc_mr = siw_alloc_mr,
	.alloc_pd = siw_alloc_pd,
	.alloc_ucontext = siw_alloc_ucontext,
	.create_cq = siw_create_cq,
	.create_qp = siw_create_qp,
	.create_srq = siw_create_srq,
	.dealloc_driver = siw_device_cleanup,
	.dealloc_pd = siw_dealloc_pd,
	.dealloc_ucontext = siw_dealloc_ucontext,
	.dereg_mr = siw_dereg_mr,
	.destroy_cq = siw_destroy_cq,
	.destroy_qp = siw_destroy_qp,
	.destroy_srq = siw_destroy_srq,
	.get_dma_mr = siw_get_dma_mr,
	.get_port_immutable = siw_get_port_immutable,
	.iw_accept = siw_accept,
	.iw_add_ref = siw_qp_get_ref,
	.iw_connect = siw_connect,
	.iw_create_listen = siw_create_listen,
	.iw_destroy_listen = siw_destroy_listen,
	.iw_get_qp = siw_get_base_qp,
	.iw_reject = siw_reject,
	.iw_rem_ref = siw_qp_put_ref,
	.map_mr_sg = siw_map_mr_sg,
	.mmap = siw_mmap,
	.mmap_मुक्त = siw_mmap_मुक्त,
	.modअगरy_qp = siw_verbs_modअगरy_qp,
	.modअगरy_srq = siw_modअगरy_srq,
	.poll_cq = siw_poll_cq,
	.post_recv = siw_post_receive,
	.post_send = siw_post_send,
	.post_srq_recv = siw_post_srq_recv,
	.query_device = siw_query_device,
	.query_gid = siw_query_gid,
	.query_port = siw_query_port,
	.query_qp = siw_query_qp,
	.query_srq = siw_query_srq,
	.req_notअगरy_cq = siw_req_notअगरy_cq,
	.reg_user_mr = siw_reg_user_mr,

	INIT_RDMA_OBJ_SIZE(ib_cq, siw_cq, base_cq),
	INIT_RDMA_OBJ_SIZE(ib_pd, siw_pd, base_pd),
	INIT_RDMA_OBJ_SIZE(ib_srq, siw_srq, base_srq),
	INIT_RDMA_OBJ_SIZE(ib_ucontext, siw_ucontext, base_ucontext),
पूर्ण;

अटल काष्ठा siw_device *siw_device_create(काष्ठा net_device *netdev)
अणु
	काष्ठा siw_device *sdev = शून्य;
	काष्ठा ib_device *base_dev;
	पूर्णांक rv;

	sdev = ib_alloc_device(siw_device, base_dev);
	अगर (!sdev)
		वापस शून्य;

	base_dev = &sdev->base_dev;

	sdev->netdev = netdev;

	अगर (netdev->type != ARPHRD_LOOPBACK) अणु
		addrconf_addr_eui48((अचिन्हित अक्षर *)&base_dev->node_guid,
				    netdev->dev_addr);
	पूर्ण अन्यथा अणु
		/*
		 * The loopback device करोes not have a HW address,
		 * but connection mangagement lib expects gid != 0
		 */
		माप_प्रकार len = min_t(माप_प्रकार, म_माप(base_dev->name), 6);
		अक्षर addr[6] = अणु पूर्ण;

		स_नकल(addr, base_dev->name, len);
		addrconf_addr_eui48((अचिन्हित अक्षर *)&base_dev->node_guid,
				    addr);
	पूर्ण

	base_dev->uverbs_cmd_mask |= BIT_ULL(IB_USER_VERBS_CMD_POST_SEND);

	base_dev->node_type = RDMA_NODE_RNIC;
	स_नकल(base_dev->node_desc, SIW_NODE_DESC_COMMON,
	       माप(SIW_NODE_DESC_COMMON));

	/*
	 * Current model (one-to-one device association):
	 * One Softiwarp device per net_device or, equivalently,
	 * per physical port.
	 */
	base_dev->phys_port_cnt = 1;
	base_dev->num_comp_vectors = num_possible_cpus();

	xa_init_flags(&sdev->qp_xa, XA_FLAGS_ALLOC1);
	xa_init_flags(&sdev->mem_xa, XA_FLAGS_ALLOC1);

	ib_set_device_ops(base_dev, &siw_device_ops);
	rv = ib_device_set_netdev(base_dev, netdev, 1);
	अगर (rv)
		जाओ error;

	स_नकल(base_dev->iw_अगरname, netdev->name,
	       माप(base_dev->iw_अगरname));

	/* Disable TCP port mapping */
	base_dev->iw_driver_flags = IW_F_NO_PORT_MAP;

	sdev->attrs.max_qp = SIW_MAX_QP;
	sdev->attrs.max_qp_wr = SIW_MAX_QP_WR;
	sdev->attrs.max_ord = SIW_MAX_ORD_QP;
	sdev->attrs.max_ird = SIW_MAX_IRD_QP;
	sdev->attrs.max_sge = SIW_MAX_SGE;
	sdev->attrs.max_sge_rd = SIW_MAX_SGE_RD;
	sdev->attrs.max_cq = SIW_MAX_CQ;
	sdev->attrs.max_cqe = SIW_MAX_CQE;
	sdev->attrs.max_mr = SIW_MAX_MR;
	sdev->attrs.max_pd = SIW_MAX_PD;
	sdev->attrs.max_mw = SIW_MAX_MW;
	sdev->attrs.max_srq = SIW_MAX_SRQ;
	sdev->attrs.max_srq_wr = SIW_MAX_SRQ_WR;
	sdev->attrs.max_srq_sge = SIW_MAX_SGE;

	INIT_LIST_HEAD(&sdev->cep_list);
	INIT_LIST_HEAD(&sdev->qp_list);

	atomic_set(&sdev->num_ctx, 0);
	atomic_set(&sdev->num_srq, 0);
	atomic_set(&sdev->num_qp, 0);
	atomic_set(&sdev->num_cq, 0);
	atomic_set(&sdev->num_mr, 0);
	atomic_set(&sdev->num_pd, 0);

	sdev->numa_node = dev_to_node(&netdev->dev);
	spin_lock_init(&sdev->lock);

	वापस sdev;
error:
	ib_dealloc_device(base_dev);

	वापस शून्य;
पूर्ण

/*
 * Network link becomes unavailable. Mark all
 * affected QP's accordingly.
 */
अटल व्योम siw_netdev_करोwn(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा siw_device *sdev =
		container_of(work, काष्ठा siw_device, netdev_करोwn);

	काष्ठा siw_qp_attrs qp_attrs;
	काष्ठा list_head *pos, *पंचांगp;

	स_रखो(&qp_attrs, 0, माप(qp_attrs));
	qp_attrs.state = SIW_QP_STATE_ERROR;

	list_क्रम_each_safe(pos, पंचांगp, &sdev->qp_list) अणु
		काष्ठा siw_qp *qp = list_entry(pos, काष्ठा siw_qp, devq);

		करोwn_ग_लिखो(&qp->state_lock);
		WARN_ON(siw_qp_modअगरy(qp, &qp_attrs, SIW_QP_ATTR_STATE));
		up_ग_लिखो(&qp->state_lock);
	पूर्ण
	ib_device_put(&sdev->base_dev);
पूर्ण

अटल व्योम siw_device_goes_करोwn(काष्ठा siw_device *sdev)
अणु
	अगर (ib_device_try_get(&sdev->base_dev)) अणु
		INIT_WORK(&sdev->netdev_करोwn, siw_netdev_करोwn);
		schedule_work(&sdev->netdev_करोwn);
	पूर्ण
पूर्ण

अटल पूर्णांक siw_netdev_event(काष्ठा notअगरier_block *nb, अचिन्हित दीर्घ event,
			    व्योम *arg)
अणु
	काष्ठा net_device *netdev = netdev_notअगरier_info_to_dev(arg);
	काष्ठा ib_device *base_dev;
	काष्ठा siw_device *sdev;

	dev_dbg(&netdev->dev, "siw: event %lu\n", event);

	अगर (dev_net(netdev) != &init_net)
		वापस NOTIFY_OK;

	base_dev = ib_device_get_by_netdev(netdev, RDMA_DRIVER_SIW);
	अगर (!base_dev)
		वापस NOTIFY_OK;

	sdev = to_siw_dev(base_dev);

	चयन (event) अणु
	हाल NETDEV_UP:
		sdev->state = IB_PORT_ACTIVE;
		siw_port_event(sdev, 1, IB_EVENT_PORT_ACTIVE);
		अवरोध;

	हाल NETDEV_GOING_DOWN:
		siw_device_goes_करोwn(sdev);
		अवरोध;

	हाल NETDEV_DOWN:
		sdev->state = IB_PORT_DOWN;
		siw_port_event(sdev, 1, IB_EVENT_PORT_ERR);
		अवरोध;

	हाल NETDEV_REGISTER:
		/*
		 * Device registration now handled only by
		 * rdma netlink commands. So it shall be impossible
		 * to end up here with a valid siw device.
		 */
		siw_dbg(base_dev, "unexpected NETDEV_REGISTER event\n");
		अवरोध;

	हाल NETDEV_UNREGISTER:
		ib_unरेजिस्टर_device_queued(&sdev->base_dev);
		अवरोध;

	हाल NETDEV_CHANGEADDR:
		siw_port_event(sdev, 1, IB_EVENT_LID_CHANGE);
		अवरोध;
	/*
	 * Toकरो: Below netdev events are currently not handled.
	 */
	हाल NETDEV_CHANGEMTU:
	हाल NETDEV_CHANGE:
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण
	ib_device_put(&sdev->base_dev);

	वापस NOTIFY_OK;
पूर्ण

अटल काष्ठा notअगरier_block siw_netdev_nb = अणु
	.notअगरier_call = siw_netdev_event,
पूर्ण;

अटल पूर्णांक siw_newlink(स्थिर अक्षर *basedev_name, काष्ठा net_device *netdev)
अणु
	काष्ठा ib_device *base_dev;
	काष्ठा siw_device *sdev = शून्य;
	पूर्णांक rv = -ENOMEM;

	अगर (!siw_dev_qualअगरied(netdev))
		वापस -EINVAL;

	base_dev = ib_device_get_by_netdev(netdev, RDMA_DRIVER_SIW);
	अगर (base_dev) अणु
		ib_device_put(base_dev);
		वापस -EEXIST;
	पूर्ण
	sdev = siw_device_create(netdev);
	अगर (sdev) अणु
		dev_dbg(&netdev->dev, "siw: new device\n");

		अगर (netअगर_running(netdev) && netअगर_carrier_ok(netdev))
			sdev->state = IB_PORT_ACTIVE;
		अन्यथा
			sdev->state = IB_PORT_DOWN;

		rv = siw_device_रेजिस्टर(sdev, basedev_name);
		अगर (rv)
			ib_dealloc_device(&sdev->base_dev);
	पूर्ण
	वापस rv;
पूर्ण

अटल काष्ठा rdma_link_ops siw_link_ops = अणु
	.type = "siw",
	.newlink = siw_newlink,
पूर्ण;

/*
 * siw_init_module - Initialize Softiwarp module and रेजिस्टर with netdev
 *                   subप्रणाली.
 */
अटल __init पूर्णांक siw_init_module(व्योम)
अणु
	पूर्णांक rv;
	पूर्णांक nr_cpu;

	अगर (SENDPAGE_THRESH < SIW_MAX_INLINE) अणु
		pr_info("siw: sendpage threshold too small: %u\n",
			(पूर्णांक)SENDPAGE_THRESH);
		rv = -EINVAL;
		जाओ out_error;
	पूर्ण
	rv = siw_init_cpulist();
	अगर (rv)
		जाओ out_error;

	rv = siw_cm_init();
	अगर (rv)
		जाओ out_error;

	अगर (!siw_create_tx_thपढ़ोs()) अणु
		pr_info("siw: Could not start any TX thread\n");
		rv = -ENOMEM;
		जाओ out_error;
	पूर्ण
	/*
	 * Locate CRC32 algorithm. If unsuccessful, fail
	 * loading siw only, अगर CRC is required.
	 */
	siw_crypto_shash = crypto_alloc_shash("crc32c", 0, 0);
	अगर (IS_ERR(siw_crypto_shash)) अणु
		pr_info("siw: Loading CRC32c failed: %ld\n",
			PTR_ERR(siw_crypto_shash));
		siw_crypto_shash = शून्य;
		अगर (mpa_crc_required) अणु
			rv = -EOPNOTSUPP;
			जाओ out_error;
		पूर्ण
	पूर्ण
	rv = रेजिस्टर_netdevice_notअगरier(&siw_netdev_nb);
	अगर (rv)
		जाओ out_error;

	rdma_link_रेजिस्टर(&siw_link_ops);

	pr_info("SoftiWARP attached\n");
	वापस 0;

out_error:
	क्रम (nr_cpu = 0; nr_cpu < nr_cpu_ids; nr_cpu++) अणु
		अगर (siw_tx_thपढ़ो[nr_cpu]) अणु
			siw_stop_tx_thपढ़ो(nr_cpu);
			siw_tx_thपढ़ो[nr_cpu] = शून्य;
		पूर्ण
	पूर्ण
	अगर (siw_crypto_shash)
		crypto_मुक्त_shash(siw_crypto_shash);

	pr_info("SoftIWARP attach failed. Error: %d\n", rv);

	siw_cm_निकास();
	siw_destroy_cpulist();

	वापस rv;
पूर्ण

अटल व्योम __निकास siw_निकास_module(व्योम)
अणु
	पूर्णांक cpu;

	क्रम_each_possible_cpu(cpu) अणु
		अगर (siw_tx_thपढ़ो[cpu]) अणु
			siw_stop_tx_thपढ़ो(cpu);
			siw_tx_thपढ़ो[cpu] = शून्य;
		पूर्ण
	पूर्ण
	unरेजिस्टर_netdevice_notअगरier(&siw_netdev_nb);
	rdma_link_unरेजिस्टर(&siw_link_ops);
	ib_unरेजिस्टर_driver(RDMA_DRIVER_SIW);

	siw_cm_निकास();

	siw_destroy_cpulist();

	अगर (siw_crypto_shash)
		crypto_मुक्त_shash(siw_crypto_shash);

	pr_info("SoftiWARP detached\n");
पूर्ण

module_init(siw_init_module);
module_निकास(siw_निकास_module);

MODULE_ALIAS_RDMA_LINK("siw");
