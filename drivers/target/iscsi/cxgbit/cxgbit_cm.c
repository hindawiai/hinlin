<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2016 Chelsio Communications, Inc.
 */

#समावेश <linux/module.h>
#समावेश <linux/list.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/समयr.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/inetdevice.h>
#समावेश <linux/ip.h>
#समावेश <linux/tcp.h>
#समावेश <linux/अगर_vlan.h>

#समावेश <net/neighbour.h>
#समावेश <net/netevent.h>
#समावेश <net/route.h>
#समावेश <net/tcp.h>
#समावेश <net/ip6_route.h>
#समावेश <net/addrconf.h>

#समावेश <libcxgb_cm.h>
#समावेश "cxgbit.h"
#समावेश "clip_tbl.h"

अटल व्योम cxgbit_init_wr_रुको(काष्ठा cxgbit_wr_रुको *wr_रुकोp)
अणु
	wr_रुकोp->ret = 0;
	reinit_completion(&wr_रुकोp->completion);
पूर्ण

अटल व्योम
cxgbit_wake_up(काष्ठा cxgbit_wr_रुको *wr_रुकोp, स्थिर अक्षर *func, u8 ret)
अणु
	अगर (ret == CPL_ERR_NONE)
		wr_रुकोp->ret = 0;
	अन्यथा
		wr_रुकोp->ret = -EIO;

	अगर (wr_रुकोp->ret)
		pr_err("%s: err:%u", func, ret);

	complete(&wr_रुकोp->completion);
पूर्ण

अटल पूर्णांक
cxgbit_रुको_क्रम_reply(काष्ठा cxgbit_device *cdev,
		      काष्ठा cxgbit_wr_रुको *wr_रुकोp, u32 tid, u32 समयout,
		      स्थिर अक्षर *func)
अणु
	पूर्णांक ret;

	अगर (!test_bit(CDEV_STATE_UP, &cdev->flags)) अणु
		wr_रुकोp->ret = -EIO;
		जाओ out;
	पूर्ण

	ret = रुको_क्रम_completion_समयout(&wr_रुकोp->completion, समयout * HZ);
	अगर (!ret) अणु
		pr_info("%s - Device %s not responding tid %u\n",
			func, pci_name(cdev->lldi.pdev), tid);
		wr_रुकोp->ret = -ETIMEDOUT;
	पूर्ण
out:
	अगर (wr_रुकोp->ret)
		pr_info("%s: FW reply %d tid %u\n",
			pci_name(cdev->lldi.pdev), wr_रुकोp->ret, tid);
	वापस wr_रुकोp->ret;
पूर्ण

अटल पूर्णांक cxgbit_np_hashfn(स्थिर काष्ठा cxgbit_np *cnp)
अणु
	वापस ((अचिन्हित दीर्घ)cnp >> 10) & (NP_INFO_HASH_SIZE - 1);
पूर्ण

अटल काष्ठा np_info *
cxgbit_np_hash_add(काष्ठा cxgbit_device *cdev, काष्ठा cxgbit_np *cnp,
		   अचिन्हित पूर्णांक stid)
अणु
	काष्ठा np_info *p = kzalloc(माप(*p), GFP_KERNEL);

	अगर (p) अणु
		पूर्णांक bucket = cxgbit_np_hashfn(cnp);

		p->cnp = cnp;
		p->stid = stid;
		spin_lock(&cdev->np_lock);
		p->next = cdev->np_hash_tab[bucket];
		cdev->np_hash_tab[bucket] = p;
		spin_unlock(&cdev->np_lock);
	पूर्ण

	वापस p;
पूर्ण

अटल पूर्णांक
cxgbit_np_hash_find(काष्ठा cxgbit_device *cdev, काष्ठा cxgbit_np *cnp)
अणु
	पूर्णांक stid = -1, bucket = cxgbit_np_hashfn(cnp);
	काष्ठा np_info *p;

	spin_lock(&cdev->np_lock);
	क्रम (p = cdev->np_hash_tab[bucket]; p; p = p->next) अणु
		अगर (p->cnp == cnp) अणु
			stid = p->stid;
			अवरोध;
		पूर्ण
	पूर्ण
	spin_unlock(&cdev->np_lock);

	वापस stid;
पूर्ण

अटल पूर्णांक cxgbit_np_hash_del(काष्ठा cxgbit_device *cdev, काष्ठा cxgbit_np *cnp)
अणु
	पूर्णांक stid = -1, bucket = cxgbit_np_hashfn(cnp);
	काष्ठा np_info *p, **prev = &cdev->np_hash_tab[bucket];

	spin_lock(&cdev->np_lock);
	क्रम (p = *prev; p; prev = &p->next, p = p->next) अणु
		अगर (p->cnp == cnp) अणु
			stid = p->stid;
			*prev = p->next;
			kमुक्त(p);
			अवरोध;
		पूर्ण
	पूर्ण
	spin_unlock(&cdev->np_lock);

	वापस stid;
पूर्ण

व्योम _cxgbit_मुक्त_cnp(काष्ठा kref *kref)
अणु
	काष्ठा cxgbit_np *cnp;

	cnp = container_of(kref, काष्ठा cxgbit_np, kref);
	kमुक्त(cnp);
पूर्ण

अटल पूर्णांक
cxgbit_create_server6(काष्ठा cxgbit_device *cdev, अचिन्हित पूर्णांक stid,
		      काष्ठा cxgbit_np *cnp)
अणु
	काष्ठा sockaddr_in6 *sin6 = (काष्ठा sockaddr_in6 *)
				     &cnp->com.local_addr;
	पूर्णांक addr_type;
	पूर्णांक ret;

	pr_debug("%s: dev = %s; stid = %u; sin6_port = %u\n",
		 __func__, cdev->lldi.ports[0]->name, stid, sin6->sin6_port);

	addr_type = ipv6_addr_type((स्थिर काष्ठा in6_addr *)
				   &sin6->sin6_addr);
	अगर (addr_type != IPV6_ADDR_ANY) अणु
		ret = cxgb4_clip_get(cdev->lldi.ports[0],
				     (स्थिर u32 *)&sin6->sin6_addr.s6_addr, 1);
		अगर (ret) अणु
			pr_err("Unable to find clip table entry. laddr %pI6. Error:%d.\n",
			       sin6->sin6_addr.s6_addr, ret);
			वापस -ENOMEM;
		पूर्ण
	पूर्ण

	cxgbit_get_cnp(cnp);
	cxgbit_init_wr_रुको(&cnp->com.wr_रुको);

	ret = cxgb4_create_server6(cdev->lldi.ports[0],
				   stid, &sin6->sin6_addr,
				   sin6->sin6_port,
				   cdev->lldi.rxq_ids[0]);
	अगर (!ret)
		ret = cxgbit_रुको_क्रम_reply(cdev, &cnp->com.wr_रुको,
					    0, 10, __func__);
	अन्यथा अगर (ret > 0)
		ret = net_xmit_त्रुटि_सं(ret);
	अन्यथा
		cxgbit_put_cnp(cnp);

	अगर (ret) अणु
		अगर (ret != -ETIMEDOUT)
			cxgb4_clip_release(cdev->lldi.ports[0],
				   (स्थिर u32 *)&sin6->sin6_addr.s6_addr, 1);

		pr_err("create server6 err %d stid %d laddr %pI6 lport %d\n",
		       ret, stid, sin6->sin6_addr.s6_addr,
		       ntohs(sin6->sin6_port));
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक
cxgbit_create_server4(काष्ठा cxgbit_device *cdev, अचिन्हित पूर्णांक stid,
		      काष्ठा cxgbit_np *cnp)
अणु
	काष्ठा sockaddr_in *sin = (काष्ठा sockaddr_in *)
				   &cnp->com.local_addr;
	पूर्णांक ret;

	pr_debug("%s: dev = %s; stid = %u; sin_port = %u\n",
		 __func__, cdev->lldi.ports[0]->name, stid, sin->sin_port);

	cxgbit_get_cnp(cnp);
	cxgbit_init_wr_रुको(&cnp->com.wr_रुको);

	ret = cxgb4_create_server(cdev->lldi.ports[0],
				  stid, sin->sin_addr.s_addr,
				  sin->sin_port, 0,
				  cdev->lldi.rxq_ids[0]);
	अगर (!ret)
		ret = cxgbit_रुको_क्रम_reply(cdev,
					    &cnp->com.wr_रुको,
					    0, 10, __func__);
	अन्यथा अगर (ret > 0)
		ret = net_xmit_त्रुटि_सं(ret);
	अन्यथा
		cxgbit_put_cnp(cnp);

	अगर (ret)
		pr_err("create server failed err %d stid %d laddr %pI4 lport %d\n",
		       ret, stid, &sin->sin_addr, ntohs(sin->sin_port));
	वापस ret;
पूर्ण

काष्ठा cxgbit_device *cxgbit_find_device(काष्ठा net_device *ndev, u8 *port_id)
अणु
	काष्ठा cxgbit_device *cdev;
	u8 i;

	list_क्रम_each_entry(cdev, &cdev_list_head, list) अणु
		काष्ठा cxgb4_lld_info *lldi = &cdev->lldi;

		क्रम (i = 0; i < lldi->nports; i++) अणु
			अगर (lldi->ports[i] == ndev) अणु
				अगर (port_id)
					*port_id = i;
				वापस cdev;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस शून्य;
पूर्ण

अटल काष्ठा net_device *cxgbit_get_real_dev(काष्ठा net_device *ndev)
अणु
	अगर (ndev->priv_flags & IFF_BONDING) अणु
		pr_err("Bond devices are not supported. Interface:%s\n",
		       ndev->name);
		वापस शून्य;
	पूर्ण

	अगर (is_vlan_dev(ndev))
		वापस vlan_dev_real_dev(ndev);

	वापस ndev;
पूर्ण

अटल काष्ठा net_device *cxgbit_ipv4_netdev(__be32 saddr)
अणु
	काष्ठा net_device *ndev;

	ndev = __ip_dev_find(&init_net, saddr, false);
	अगर (!ndev)
		वापस शून्य;

	वापस cxgbit_get_real_dev(ndev);
पूर्ण

अटल काष्ठा net_device *cxgbit_ipv6_netdev(काष्ठा in6_addr *addr6)
अणु
	काष्ठा net_device *ndev = शून्य;
	bool found = false;

	अगर (IS_ENABLED(CONFIG_IPV6)) अणु
		क्रम_each_netdev_rcu(&init_net, ndev)
			अगर (ipv6_chk_addr(&init_net, addr6, ndev, 1)) अणु
				found = true;
				अवरोध;
			पूर्ण
	पूर्ण
	अगर (!found)
		वापस शून्य;
	वापस cxgbit_get_real_dev(ndev);
पूर्ण

अटल काष्ठा cxgbit_device *cxgbit_find_np_cdev(काष्ठा cxgbit_np *cnp)
अणु
	काष्ठा sockaddr_storage *sockaddr = &cnp->com.local_addr;
	पूर्णांक ss_family = sockaddr->ss_family;
	काष्ठा net_device *ndev = शून्य;
	काष्ठा cxgbit_device *cdev = शून्य;

	rcu_पढ़ो_lock();
	अगर (ss_family == AF_INET) अणु
		काष्ठा sockaddr_in *sin;

		sin = (काष्ठा sockaddr_in *)sockaddr;
		ndev = cxgbit_ipv4_netdev(sin->sin_addr.s_addr);
	पूर्ण अन्यथा अगर (ss_family == AF_INET6) अणु
		काष्ठा sockaddr_in6 *sin6;

		sin6 = (काष्ठा sockaddr_in6 *)sockaddr;
		ndev = cxgbit_ipv6_netdev(&sin6->sin6_addr);
	पूर्ण
	अगर (!ndev)
		जाओ out;

	cdev = cxgbit_find_device(ndev, शून्य);
out:
	rcu_पढ़ो_unlock();
	वापस cdev;
पूर्ण

अटल bool cxgbit_inaddr_any(काष्ठा cxgbit_np *cnp)
अणु
	काष्ठा sockaddr_storage *sockaddr = &cnp->com.local_addr;
	पूर्णांक ss_family = sockaddr->ss_family;
	पूर्णांक addr_type;

	अगर (ss_family == AF_INET) अणु
		काष्ठा sockaddr_in *sin;

		sin = (काष्ठा sockaddr_in *)sockaddr;
		अगर (sin->sin_addr.s_addr == htonl(INADDR_ANY))
			वापस true;
	पूर्ण अन्यथा अगर (ss_family == AF_INET6) अणु
		काष्ठा sockaddr_in6 *sin6;

		sin6 = (काष्ठा sockaddr_in6 *)sockaddr;
		addr_type = ipv6_addr_type((स्थिर काष्ठा in6_addr *)
				&sin6->sin6_addr);
		अगर (addr_type == IPV6_ADDR_ANY)
			वापस true;
	पूर्ण
	वापस false;
पूर्ण

अटल पूर्णांक
__cxgbit_setup_cdev_np(काष्ठा cxgbit_device *cdev, काष्ठा cxgbit_np *cnp)
अणु
	पूर्णांक stid, ret;
	पूर्णांक ss_family = cnp->com.local_addr.ss_family;

	अगर (!test_bit(CDEV_STATE_UP, &cdev->flags))
		वापस -EINVAL;

	stid = cxgb4_alloc_stid(cdev->lldi.tids, ss_family, cnp);
	अगर (stid < 0)
		वापस -EINVAL;

	अगर (!cxgbit_np_hash_add(cdev, cnp, stid)) अणु
		cxgb4_मुक्त_stid(cdev->lldi.tids, stid, ss_family);
		वापस -EINVAL;
	पूर्ण

	अगर (ss_family == AF_INET)
		ret = cxgbit_create_server4(cdev, stid, cnp);
	अन्यथा
		ret = cxgbit_create_server6(cdev, stid, cnp);

	अगर (ret) अणु
		अगर (ret != -ETIMEDOUT)
			cxgb4_मुक्त_stid(cdev->lldi.tids, stid,
					ss_family);
		cxgbit_np_hash_del(cdev, cnp);
		वापस ret;
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक cxgbit_setup_cdev_np(काष्ठा cxgbit_np *cnp)
अणु
	काष्ठा cxgbit_device *cdev;
	पूर्णांक ret = -1;

	mutex_lock(&cdev_list_lock);
	cdev = cxgbit_find_np_cdev(cnp);
	अगर (!cdev)
		जाओ out;

	अगर (cxgbit_np_hash_find(cdev, cnp) >= 0)
		जाओ out;

	अगर (__cxgbit_setup_cdev_np(cdev, cnp))
		जाओ out;

	cnp->com.cdev = cdev;
	ret = 0;
out:
	mutex_unlock(&cdev_list_lock);
	वापस ret;
पूर्ण

अटल पूर्णांक cxgbit_setup_all_np(काष्ठा cxgbit_np *cnp)
अणु
	काष्ठा cxgbit_device *cdev;
	पूर्णांक ret;
	u32 count = 0;

	mutex_lock(&cdev_list_lock);
	list_क्रम_each_entry(cdev, &cdev_list_head, list) अणु
		अगर (cxgbit_np_hash_find(cdev, cnp) >= 0) अणु
			mutex_unlock(&cdev_list_lock);
			वापस -1;
		पूर्ण
	पूर्ण

	list_क्रम_each_entry(cdev, &cdev_list_head, list) अणु
		ret = __cxgbit_setup_cdev_np(cdev, cnp);
		अगर (ret == -ETIMEDOUT)
			अवरोध;
		अगर (ret != 0)
			जारी;
		count++;
	पूर्ण
	mutex_unlock(&cdev_list_lock);

	वापस count ? 0 : -1;
पूर्ण

पूर्णांक cxgbit_setup_np(काष्ठा iscsi_np *np, काष्ठा sockaddr_storage *ksockaddr)
अणु
	काष्ठा cxgbit_np *cnp;
	पूर्णांक ret;

	अगर ((ksockaddr->ss_family != AF_INET) &&
	    (ksockaddr->ss_family != AF_INET6))
		वापस -EINVAL;

	cnp = kzalloc(माप(*cnp), GFP_KERNEL);
	अगर (!cnp)
		वापस -ENOMEM;

	init_रुकोqueue_head(&cnp->accept_रुको);
	init_completion(&cnp->com.wr_रुको.completion);
	init_completion(&cnp->accept_comp);
	INIT_LIST_HEAD(&cnp->np_accept_list);
	spin_lock_init(&cnp->np_accept_lock);
	kref_init(&cnp->kref);
	स_नकल(&np->np_sockaddr, ksockaddr,
	       माप(काष्ठा sockaddr_storage));
	स_नकल(&cnp->com.local_addr, &np->np_sockaddr,
	       माप(cnp->com.local_addr));

	cnp->np = np;
	cnp->com.cdev = शून्य;

	अगर (cxgbit_inaddr_any(cnp))
		ret = cxgbit_setup_all_np(cnp);
	अन्यथा
		ret = cxgbit_setup_cdev_np(cnp);

	अगर (ret) अणु
		cxgbit_put_cnp(cnp);
		वापस -EINVAL;
	पूर्ण

	np->np_context = cnp;
	cnp->com.state = CSK_STATE_LISTEN;
	वापस 0;
पूर्ण

अटल व्योम
cxgbit_set_conn_info(काष्ठा iscsi_np *np, काष्ठा iscsi_conn *conn,
		     काष्ठा cxgbit_sock *csk)
अणु
	conn->login_family = np->np_sockaddr.ss_family;
	conn->login_sockaddr = csk->com.remote_addr;
	conn->local_sockaddr = csk->com.local_addr;
पूर्ण

पूर्णांक cxgbit_accept_np(काष्ठा iscsi_np *np, काष्ठा iscsi_conn *conn)
अणु
	काष्ठा cxgbit_np *cnp = np->np_context;
	काष्ठा cxgbit_sock *csk;
	पूर्णांक ret = 0;

accept_रुको:
	ret = रुको_क्रम_completion_पूर्णांकerruptible(&cnp->accept_comp);
	अगर (ret)
		वापस -ENODEV;

	spin_lock_bh(&np->np_thपढ़ो_lock);
	अगर (np->np_thपढ़ो_state >= ISCSI_NP_THREAD_RESET) अणु
		spin_unlock_bh(&np->np_thपढ़ो_lock);
		/**
		 * No poपूर्णांक in stalling here when np_thपढ़ो
		 * is in state RESET/SHUTDOWN/EXIT - bail
		 **/
		वापस -ENODEV;
	पूर्ण
	spin_unlock_bh(&np->np_thपढ़ो_lock);

	spin_lock_bh(&cnp->np_accept_lock);
	अगर (list_empty(&cnp->np_accept_list)) अणु
		spin_unlock_bh(&cnp->np_accept_lock);
		जाओ accept_रुको;
	पूर्ण

	csk = list_first_entry(&cnp->np_accept_list,
			       काष्ठा cxgbit_sock,
			       accept_node);

	list_del_init(&csk->accept_node);
	spin_unlock_bh(&cnp->np_accept_lock);
	conn->context = csk;
	csk->conn = conn;

	cxgbit_set_conn_info(np, conn, csk);
	वापस 0;
पूर्ण

अटल पूर्णांक
__cxgbit_मुक्त_cdev_np(काष्ठा cxgbit_device *cdev, काष्ठा cxgbit_np *cnp)
अणु
	पूर्णांक stid, ret;
	bool ipv6 = false;

	stid = cxgbit_np_hash_del(cdev, cnp);
	अगर (stid < 0)
		वापस -EINVAL;
	अगर (!test_bit(CDEV_STATE_UP, &cdev->flags))
		वापस -EINVAL;

	अगर (cnp->np->np_sockaddr.ss_family == AF_INET6)
		ipv6 = true;

	cxgbit_get_cnp(cnp);
	cxgbit_init_wr_रुको(&cnp->com.wr_रुको);
	ret = cxgb4_हटाओ_server(cdev->lldi.ports[0], stid,
				  cdev->lldi.rxq_ids[0], ipv6);

	अगर (ret > 0)
		ret = net_xmit_त्रुटि_सं(ret);

	अगर (ret) अणु
		cxgbit_put_cnp(cnp);
		वापस ret;
	पूर्ण

	ret = cxgbit_रुको_क्रम_reply(cdev, &cnp->com.wr_रुको,
				    0, 10, __func__);
	अगर (ret == -ETIMEDOUT)
		वापस ret;

	अगर (ipv6 && cnp->com.cdev) अणु
		काष्ठा sockaddr_in6 *sin6;

		sin6 = (काष्ठा sockaddr_in6 *)&cnp->com.local_addr;
		cxgb4_clip_release(cdev->lldi.ports[0],
				   (स्थिर u32 *)&sin6->sin6_addr.s6_addr,
				   1);
	पूर्ण

	cxgb4_मुक्त_stid(cdev->lldi.tids, stid,
			cnp->com.local_addr.ss_family);
	वापस 0;
पूर्ण

अटल व्योम cxgbit_मुक्त_all_np(काष्ठा cxgbit_np *cnp)
अणु
	काष्ठा cxgbit_device *cdev;
	पूर्णांक ret;

	mutex_lock(&cdev_list_lock);
	list_क्रम_each_entry(cdev, &cdev_list_head, list) अणु
		ret = __cxgbit_मुक्त_cdev_np(cdev, cnp);
		अगर (ret == -ETIMEDOUT)
			अवरोध;
	पूर्ण
	mutex_unlock(&cdev_list_lock);
पूर्ण

अटल व्योम cxgbit_मुक्त_cdev_np(काष्ठा cxgbit_np *cnp)
अणु
	काष्ठा cxgbit_device *cdev;
	bool found = false;

	mutex_lock(&cdev_list_lock);
	list_क्रम_each_entry(cdev, &cdev_list_head, list) अणु
		अगर (cdev == cnp->com.cdev) अणु
			found = true;
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (!found)
		जाओ out;

	__cxgbit_मुक्त_cdev_np(cdev, cnp);
out:
	mutex_unlock(&cdev_list_lock);
पूर्ण

अटल व्योम __cxgbit_मुक्त_conn(काष्ठा cxgbit_sock *csk);

व्योम cxgbit_मुक्त_np(काष्ठा iscsi_np *np)
अणु
	काष्ठा cxgbit_np *cnp = np->np_context;
	काष्ठा cxgbit_sock *csk, *पंचांगp;

	cnp->com.state = CSK_STATE_DEAD;
	अगर (cnp->com.cdev)
		cxgbit_मुक्त_cdev_np(cnp);
	अन्यथा
		cxgbit_मुक्त_all_np(cnp);

	spin_lock_bh(&cnp->np_accept_lock);
	list_क्रम_each_entry_safe(csk, पंचांगp, &cnp->np_accept_list, accept_node) अणु
		list_del_init(&csk->accept_node);
		__cxgbit_मुक्त_conn(csk);
	पूर्ण
	spin_unlock_bh(&cnp->np_accept_lock);

	np->np_context = शून्य;
	cxgbit_put_cnp(cnp);
पूर्ण

अटल व्योम cxgbit_send_halख_बंद(काष्ठा cxgbit_sock *csk)
अणु
	काष्ठा sk_buff *skb;
	u32 len = roundup(माप(काष्ठा cpl_बंद_con_req), 16);

	skb = alloc_skb(len, GFP_ATOMIC);
	अगर (!skb)
		वापस;

	cxgb_mk_बंद_con_req(skb, len, csk->tid, csk->txq_idx,
			      शून्य, शून्य);

	cxgbit_skcb_flags(skb) |= SKCBF_TX_FLAG_COMPL;
	__skb_queue_tail(&csk->txq, skb);
	cxgbit_push_tx_frames(csk);
पूर्ण

अटल व्योम cxgbit_arp_failure_discard(व्योम *handle, काष्ठा sk_buff *skb)
अणु
	काष्ठा cxgbit_sock *csk = handle;

	pr_debug("%s cxgbit_device %p\n", __func__, handle);
	kमुक्त_skb(skb);
	cxgbit_put_csk(csk);
पूर्ण

अटल व्योम cxgbit_पात_arp_failure(व्योम *handle, काष्ठा sk_buff *skb)
अणु
	काष्ठा cxgbit_device *cdev = handle;
	काष्ठा cpl_पात_req *req = cplhdr(skb);

	pr_debug("%s cdev %p\n", __func__, cdev);
	req->cmd = CPL_ABORT_NO_RST;
	cxgbit_ofld_send(cdev, skb);
पूर्ण

अटल पूर्णांक cxgbit_send_पात_req(काष्ठा cxgbit_sock *csk)
अणु
	काष्ठा sk_buff *skb;
	u32 len = roundup(माप(काष्ठा cpl_पात_req), 16);

	pr_debug("%s: csk %p tid %u; state %d\n",
		 __func__, csk, csk->tid, csk->com.state);

	__skb_queue_purge(&csk->txq);

	अगर (!test_and_set_bit(CSK_TX_DATA_SENT, &csk->com.flags))
		cxgbit_send_tx_flowc_wr(csk);

	skb = __skb_dequeue(&csk->skbq);
	cxgb_mk_पात_req(skb, len, csk->tid, csk->txq_idx,
			  csk->com.cdev, cxgbit_पात_arp_failure);

	वापस cxgbit_l2t_send(csk->com.cdev, skb, csk->l2t);
पूर्ण

अटल व्योम
__cxgbit_पात_conn(काष्ठा cxgbit_sock *csk, काष्ठा sk_buff *skb)
अणु
	__kमुक्त_skb(skb);

	अगर (csk->com.state != CSK_STATE_ESTABLISHED)
		जाओ no_पात;

	set_bit(CSK_ABORT_RPL_WAIT, &csk->com.flags);
	csk->com.state = CSK_STATE_ABORTING;

	cxgbit_send_पात_req(csk);

	वापस;

no_पात:
	cxgbit_wake_up(&csk->com.wr_रुको, __func__, CPL_ERR_NONE);
	cxgbit_put_csk(csk);
पूर्ण

व्योम cxgbit_पात_conn(काष्ठा cxgbit_sock *csk)
अणु
	काष्ठा sk_buff *skb = alloc_skb(0, GFP_KERNEL | __GFP_NOFAIL);

	cxgbit_get_csk(csk);
	cxgbit_init_wr_रुको(&csk->com.wr_रुको);

	spin_lock_bh(&csk->lock);
	अगर (csk->lock_owner) अणु
		cxgbit_skcb_rx_backlog_fn(skb) = __cxgbit_पात_conn;
		__skb_queue_tail(&csk->backlogq, skb);
	पूर्ण अन्यथा अणु
		__cxgbit_पात_conn(csk, skb);
	पूर्ण
	spin_unlock_bh(&csk->lock);

	cxgbit_रुको_क्रम_reply(csk->com.cdev, &csk->com.wr_रुको,
			      csk->tid, 600, __func__);
पूर्ण

अटल व्योम __cxgbit_मुक्त_conn(काष्ठा cxgbit_sock *csk)
अणु
	काष्ठा iscsi_conn *conn = csk->conn;
	bool release = false;

	pr_debug("%s: state %d\n",
		 __func__, csk->com.state);

	spin_lock_bh(&csk->lock);
	चयन (csk->com.state) अणु
	हाल CSK_STATE_ESTABLISHED:
		अगर (conn && (conn->conn_state == TARG_CONN_STATE_IN_LOGOUT)) अणु
			csk->com.state = CSK_STATE_CLOSING;
			cxgbit_send_halख_बंद(csk);
		पूर्ण अन्यथा अणु
			csk->com.state = CSK_STATE_ABORTING;
			cxgbit_send_पात_req(csk);
		पूर्ण
		अवरोध;
	हाल CSK_STATE_CLOSING:
		csk->com.state = CSK_STATE_MORIBUND;
		cxgbit_send_halख_बंद(csk);
		अवरोध;
	हाल CSK_STATE_DEAD:
		release = true;
		अवरोध;
	शेष:
		pr_err("%s: csk %p; state %d\n",
		       __func__, csk, csk->com.state);
	पूर्ण
	spin_unlock_bh(&csk->lock);

	अगर (release)
		cxgbit_put_csk(csk);
पूर्ण

व्योम cxgbit_मुक्त_conn(काष्ठा iscsi_conn *conn)
अणु
	__cxgbit_मुक्त_conn(conn->context);
पूर्ण

अटल व्योम cxgbit_set_emss(काष्ठा cxgbit_sock *csk, u16 opt)
अणु
	csk->emss = csk->com.cdev->lldi.mtus[TCPOPT_MSS_G(opt)] -
			((csk->com.remote_addr.ss_family == AF_INET) ?
			माप(काष्ठा iphdr) : माप(काष्ठा ipv6hdr)) -
			माप(काष्ठा tcphdr);
	csk->mss = csk->emss;
	अगर (TCPOPT_TSTAMP_G(opt))
		csk->emss -= round_up(TCPOLEN_TIMESTAMP, 4);
	अगर (csk->emss < 128)
		csk->emss = 128;
	अगर (csk->emss & 7)
		pr_info("Warning: misaligned mtu idx %u mss %u emss=%u\n",
			TCPOPT_MSS_G(opt), csk->mss, csk->emss);
	pr_debug("%s mss_idx %u mss %u emss=%u\n", __func__, TCPOPT_MSS_G(opt),
		 csk->mss, csk->emss);
पूर्ण

अटल व्योम cxgbit_मुक्त_skb(काष्ठा cxgbit_sock *csk)
अणु
	काष्ठा sk_buff *skb;

	__skb_queue_purge(&csk->txq);
	__skb_queue_purge(&csk->rxq);
	__skb_queue_purge(&csk->backlogq);
	__skb_queue_purge(&csk->ppodq);
	__skb_queue_purge(&csk->skbq);

	जबतक ((skb = cxgbit_sock_dequeue_wr(csk)))
		kमुक्त_skb(skb);

	__kमुक्त_skb(csk->lro_hskb);
पूर्ण

व्योम _cxgbit_मुक्त_csk(काष्ठा kref *kref)
अणु
	काष्ठा cxgbit_sock *csk;
	काष्ठा cxgbit_device *cdev;

	csk = container_of(kref, काष्ठा cxgbit_sock, kref);

	pr_debug("%s csk %p state %d\n", __func__, csk, csk->com.state);

	अगर (csk->com.local_addr.ss_family == AF_INET6) अणु
		काष्ठा sockaddr_in6 *sin6 = (काष्ठा sockaddr_in6 *)
					     &csk->com.local_addr;
		cxgb4_clip_release(csk->com.cdev->lldi.ports[0],
				   (स्थिर u32 *)
				   &sin6->sin6_addr.s6_addr, 1);
	पूर्ण

	cxgb4_हटाओ_tid(csk->com.cdev->lldi.tids, 0, csk->tid,
			 csk->com.local_addr.ss_family);
	dst_release(csk->dst);
	cxgb4_l2t_release(csk->l2t);

	cdev = csk->com.cdev;
	spin_lock_bh(&cdev->cskq.lock);
	list_del(&csk->list);
	spin_unlock_bh(&cdev->cskq.lock);

	cxgbit_मुक्त_skb(csk);
	cxgbit_put_cnp(csk->cnp);
	cxgbit_put_cdev(cdev);

	kमुक्त(csk);
पूर्ण

अटल व्योम cxgbit_set_tcp_winकरोw(काष्ठा cxgbit_sock *csk, काष्ठा port_info *pi)
अणु
	अचिन्हित पूर्णांक linkspeed;
	u8 scale;

	linkspeed = pi->link_cfg.speed;
	scale = linkspeed / SPEED_10000;

#घोषणा CXGBIT_10G_RCV_WIN (256 * 1024)
	csk->rcv_win = CXGBIT_10G_RCV_WIN;
	अगर (scale)
		csk->rcv_win *= scale;

#घोषणा CXGBIT_10G_SND_WIN (256 * 1024)
	csk->snd_win = CXGBIT_10G_SND_WIN;
	अगर (scale)
		csk->snd_win *= scale;

	pr_debug("%s snd_win %d rcv_win %d\n",
		 __func__, csk->snd_win, csk->rcv_win);
पूर्ण

#अगर_घोषित CONFIG_CHELSIO_T4_DCB
अटल u8 cxgbit_get_iscsi_dcb_state(काष्ठा net_device *ndev)
अणु
	वापस ndev->dcbnl_ops->माला_लोtate(ndev);
पूर्ण

अटल पूर्णांक cxgbit_select_priority(पूर्णांक pri_mask)
अणु
	अगर (!pri_mask)
		वापस 0;

	वापस (ffs(pri_mask) - 1);
पूर्ण

अटल u8 cxgbit_get_iscsi_dcb_priority(काष्ठा net_device *ndev, u16 local_port)
अणु
	पूर्णांक ret;
	u8 caps;

	काष्ठा dcb_app iscsi_dcb_app = अणु
		.protocol = local_port
	पूर्ण;

	ret = (पूर्णांक)ndev->dcbnl_ops->अ_लोap(ndev, DCB_CAP_ATTR_DCBX, &caps);

	अगर (ret)
		वापस 0;

	अगर (caps & DCB_CAP_DCBX_VER_IEEE) अणु
		iscsi_dcb_app.selector = IEEE_8021QAZ_APP_SEL_STREAM;
		ret = dcb_ieee_getapp_mask(ndev, &iscsi_dcb_app);
		अगर (!ret) अणु
			iscsi_dcb_app.selector = IEEE_8021QAZ_APP_SEL_ANY;
			ret = dcb_ieee_getapp_mask(ndev, &iscsi_dcb_app);
		पूर्ण
	पूर्ण अन्यथा अगर (caps & DCB_CAP_DCBX_VER_CEE) अणु
		iscsi_dcb_app.selector = DCB_APP_IDTYPE_PORTNUM;

		ret = dcb_getapp(ndev, &iscsi_dcb_app);
	पूर्ण

	pr_info("iSCSI priority is set to %u\n", cxgbit_select_priority(ret));

	वापस cxgbit_select_priority(ret);
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक
cxgbit_offload_init(काष्ठा cxgbit_sock *csk, पूर्णांक iptype, __u8 *peer_ip,
		    u16 local_port, काष्ठा dst_entry *dst,
		    काष्ठा cxgbit_device *cdev)
अणु
	काष्ठा neighbour *n;
	पूर्णांक ret, step;
	काष्ठा net_device *ndev;
	u16 rxq_idx, port_id;
#अगर_घोषित CONFIG_CHELSIO_T4_DCB
	u8 priority = 0;
#पूर्ण_अगर

	n = dst_neigh_lookup(dst, peer_ip);
	अगर (!n)
		वापस -ENODEV;

	rcu_पढ़ो_lock();
	अगर (!(n->nud_state & NUD_VALID))
		neigh_event_send(n, शून्य);

	ret = -ENOMEM;
	अगर (n->dev->flags & IFF_LOOPBACK) अणु
		अगर (iptype == 4)
			ndev = cxgbit_ipv4_netdev(*(__be32 *)peer_ip);
		अन्यथा अगर (IS_ENABLED(CONFIG_IPV6))
			ndev = cxgbit_ipv6_netdev((काष्ठा in6_addr *)peer_ip);
		अन्यथा
			ndev = शून्य;

		अगर (!ndev) अणु
			ret = -ENODEV;
			जाओ out;
		पूर्ण

		csk->l2t = cxgb4_l2t_get(cdev->lldi.l2t,
					 n, ndev, 0);
		अगर (!csk->l2t)
			जाओ out;
		csk->mtu = ndev->mtu;
		csk->tx_chan = cxgb4_port_chan(ndev);
		csk->smac_idx =
			       ((काष्ठा port_info *)netdev_priv(ndev))->smt_idx;
		step = cdev->lldi.ntxq /
			cdev->lldi.nchan;
		csk->txq_idx = cxgb4_port_idx(ndev) * step;
		step = cdev->lldi.nrxq /
			cdev->lldi.nchan;
		csk->ctrlq_idx = cxgb4_port_idx(ndev);
		csk->rss_qid = cdev->lldi.rxq_ids[
				cxgb4_port_idx(ndev) * step];
		csk->port_id = cxgb4_port_idx(ndev);
		cxgbit_set_tcp_winकरोw(csk,
				      (काष्ठा port_info *)netdev_priv(ndev));
	पूर्ण अन्यथा अणु
		ndev = cxgbit_get_real_dev(n->dev);
		अगर (!ndev) अणु
			ret = -ENODEV;
			जाओ out;
		पूर्ण

#अगर_घोषित CONFIG_CHELSIO_T4_DCB
		अगर (cxgbit_get_iscsi_dcb_state(ndev))
			priority = cxgbit_get_iscsi_dcb_priority(ndev,
								 local_port);

		csk->dcb_priority = priority;

		csk->l2t = cxgb4_l2t_get(cdev->lldi.l2t, n, ndev, priority);
#अन्यथा
		csk->l2t = cxgb4_l2t_get(cdev->lldi.l2t, n, ndev, 0);
#पूर्ण_अगर
		अगर (!csk->l2t)
			जाओ out;
		port_id = cxgb4_port_idx(ndev);
		csk->mtu = dst_mtu(dst);
		csk->tx_chan = cxgb4_port_chan(ndev);
		csk->smac_idx =
			       ((काष्ठा port_info *)netdev_priv(ndev))->smt_idx;
		step = cdev->lldi.ntxq /
			cdev->lldi.nports;
		csk->txq_idx = (port_id * step) +
				(cdev->selectq[port_id][0]++ % step);
		csk->ctrlq_idx = cxgb4_port_idx(ndev);
		step = cdev->lldi.nrxq /
			cdev->lldi.nports;
		rxq_idx = (port_id * step) +
				(cdev->selectq[port_id][1]++ % step);
		csk->rss_qid = cdev->lldi.rxq_ids[rxq_idx];
		csk->port_id = port_id;
		cxgbit_set_tcp_winकरोw(csk,
				      (काष्ठा port_info *)netdev_priv(ndev));
	पूर्ण
	ret = 0;
out:
	rcu_पढ़ो_unlock();
	neigh_release(n);
	वापस ret;
पूर्ण

पूर्णांक cxgbit_ofld_send(काष्ठा cxgbit_device *cdev, काष्ठा sk_buff *skb)
अणु
	पूर्णांक ret = 0;

	अगर (!test_bit(CDEV_STATE_UP, &cdev->flags)) अणु
		kमुक्त_skb(skb);
		pr_err("%s - device not up - dropping\n", __func__);
		वापस -EIO;
	पूर्ण

	ret = cxgb4_ofld_send(cdev->lldi.ports[0], skb);
	अगर (ret < 0)
		kमुक्त_skb(skb);
	वापस ret < 0 ? ret : 0;
पूर्ण

अटल व्योम cxgbit_release_tid(काष्ठा cxgbit_device *cdev, u32 tid)
अणु
	u32 len = roundup(माप(काष्ठा cpl_tid_release), 16);
	काष्ठा sk_buff *skb;

	skb = alloc_skb(len, GFP_ATOMIC);
	अगर (!skb)
		वापस;

	cxgb_mk_tid_release(skb, len, tid, 0);
	cxgbit_ofld_send(cdev, skb);
पूर्ण

पूर्णांक
cxgbit_l2t_send(काष्ठा cxgbit_device *cdev, काष्ठा sk_buff *skb,
		काष्ठा l2t_entry *l2e)
अणु
	पूर्णांक ret = 0;

	अगर (!test_bit(CDEV_STATE_UP, &cdev->flags)) अणु
		kमुक्त_skb(skb);
		pr_err("%s - device not up - dropping\n", __func__);
		वापस -EIO;
	पूर्ण

	ret = cxgb4_l2t_send(cdev->lldi.ports[0], skb, l2e);
	अगर (ret < 0)
		kमुक्त_skb(skb);
	वापस ret < 0 ? ret : 0;
पूर्ण

अटल व्योम cxgbit_send_rx_credits(काष्ठा cxgbit_sock *csk, काष्ठा sk_buff *skb)
अणु
	अगर (csk->com.state != CSK_STATE_ESTABLISHED) अणु
		__kमुक्त_skb(skb);
		वापस;
	पूर्ण

	cxgbit_ofld_send(csk->com.cdev, skb);
पूर्ण

/*
 * CPL connection rx data ack: host ->
 * Send RX credits through an RX_DATA_ACK CPL message.
 * Returns the number of credits sent.
 */
पूर्णांक cxgbit_rx_data_ack(काष्ठा cxgbit_sock *csk)
अणु
	काष्ठा sk_buff *skb;
	u32 len = roundup(माप(काष्ठा cpl_rx_data_ack), 16);
	u32 credit_dack;

	skb = alloc_skb(len, GFP_KERNEL);
	अगर (!skb)
		वापस -1;

	credit_dack = RX_DACK_CHANGE_F | RX_DACK_MODE_V(1) |
		      RX_CREDITS_V(csk->rx_credits);

	cxgb_mk_rx_data_ack(skb, len, csk->tid, csk->ctrlq_idx,
			    credit_dack);

	csk->rx_credits = 0;

	spin_lock_bh(&csk->lock);
	अगर (csk->lock_owner) अणु
		cxgbit_skcb_rx_backlog_fn(skb) = cxgbit_send_rx_credits;
		__skb_queue_tail(&csk->backlogq, skb);
		spin_unlock_bh(&csk->lock);
		वापस 0;
	पूर्ण

	cxgbit_send_rx_credits(csk, skb);
	spin_unlock_bh(&csk->lock);

	वापस 0;
पूर्ण

#घोषणा FLOWC_WR_NPARAMS_MIN    9
#घोषणा FLOWC_WR_NPARAMS_MAX	11
अटल पूर्णांक cxgbit_alloc_csk_skb(काष्ठा cxgbit_sock *csk)
अणु
	काष्ठा sk_buff *skb;
	u32 len, flowclen;
	u8 i;

	flowclen = दुरत्व(काष्ठा fw_flowc_wr,
			    mnemval[FLOWC_WR_NPARAMS_MAX]);

	len = max_t(u32, माप(काष्ठा cpl_पात_req),
		    माप(काष्ठा cpl_पात_rpl));

	len = max(len, flowclen);
	len = roundup(len, 16);

	क्रम (i = 0; i < 3; i++) अणु
		skb = alloc_skb(len, GFP_ATOMIC);
		अगर (!skb)
			जाओ out;
		__skb_queue_tail(&csk->skbq, skb);
	पूर्ण

	skb = alloc_skb(LRO_SKB_MIN_HEADROOM, GFP_ATOMIC);
	अगर (!skb)
		जाओ out;

	स_रखो(skb->data, 0, LRO_SKB_MIN_HEADROOM);
	csk->lro_hskb = skb;

	वापस 0;
out:
	__skb_queue_purge(&csk->skbq);
	वापस -ENOMEM;
पूर्ण

अटल व्योम
cxgbit_pass_accept_rpl(काष्ठा cxgbit_sock *csk, काष्ठा cpl_pass_accept_req *req)
अणु
	काष्ठा sk_buff *skb;
	स्थिर काष्ठा tcphdr *tcph;
	काष्ठा cpl_t5_pass_accept_rpl *rpl5;
	काष्ठा cxgb4_lld_info *lldi = &csk->com.cdev->lldi;
	अचिन्हित पूर्णांक len = roundup(माप(*rpl5), 16);
	अचिन्हित पूर्णांक mtu_idx;
	u64 opt0;
	u32 opt2, hlen;
	u32 wscale;
	u32 win;

	pr_debug("%s csk %p tid %u\n", __func__, csk, csk->tid);

	skb = alloc_skb(len, GFP_ATOMIC);
	अगर (!skb) अणु
		cxgbit_put_csk(csk);
		वापस;
	पूर्ण

	rpl5 = __skb_put_zero(skb, len);

	INIT_TP_WR(rpl5, csk->tid);
	OPCODE_TID(rpl5) = cpu_to_be32(MK_OPCODE_TID(CPL_PASS_ACCEPT_RPL,
						     csk->tid));
	cxgb_best_mtu(csk->com.cdev->lldi.mtus, csk->mtu, &mtu_idx,
		      req->tcpopt.tstamp,
		      (csk->com.remote_addr.ss_family == AF_INET) ? 0 : 1);
	wscale = cxgb_compute_wscale(csk->rcv_win);
	/*
	 * Specअगरy the largest winकरोw that will fit in opt0. The
	 * reमुख्यder will be specअगरied in the rx_data_ack.
	 */
	win = csk->rcv_win >> 10;
	अगर (win > RCV_बफ_मान_M)
		win = RCV_बफ_मान_M;
	opt0 =  TCAM_BYPASS_F |
		WND_SCALE_V(wscale) |
		MSS_IDX_V(mtu_idx) |
		L2T_IDX_V(csk->l2t->idx) |
		TX_CHAN_V(csk->tx_chan) |
		SMAC_SEL_V(csk->smac_idx) |
		DSCP_V(csk->tos >> 2) |
		ULP_MODE_V(ULP_MODE_ISCSI) |
		RCV_बफ_मान_V(win);

	opt2 = RX_CHANNEL_V(0) |
		RSS_QUEUE_VALID_F | RSS_QUEUE_V(csk->rss_qid);

	अगर (!is_t5(lldi->adapter_type))
		opt2 |= RX_FC_DISABLE_F;

	अगर (req->tcpopt.tstamp)
		opt2 |= TSTAMPS_EN_F;
	अगर (req->tcpopt.sack)
		opt2 |= SACK_EN_F;
	अगर (wscale)
		opt2 |= WND_SCALE_EN_F;

	hlen = ntohl(req->hdr_len);

	अगर (is_t5(lldi->adapter_type))
		tcph = (काष्ठा tcphdr *)((u8 *)(req + 1) +
		       ETH_HDR_LEN_G(hlen) + IP_HDR_LEN_G(hlen));
	अन्यथा
		tcph = (काष्ठा tcphdr *)((u8 *)(req + 1) +
		       T6_ETH_HDR_LEN_G(hlen) + T6_IP_HDR_LEN_G(hlen));

	अगर (tcph->ece && tcph->cwr)
		opt2 |= CCTRL_ECN_V(1);

	opt2 |= RX_COALESCE_V(3);
	opt2 |= CONG_CNTRL_V(CONG_ALG_NEWRENO);

	opt2 |= T5_ISS_F;
	rpl5->iss = cpu_to_be32((pअक्रमom_u32() & ~7UL) - 1);

	opt2 |= T5_OPT_2_VALID_F;

	rpl5->opt0 = cpu_to_be64(opt0);
	rpl5->opt2 = cpu_to_be32(opt2);
	set_wr_txq(skb, CPL_PRIORITY_SETUP, csk->ctrlq_idx);
	t4_set_arp_err_handler(skb, csk, cxgbit_arp_failure_discard);
	cxgbit_l2t_send(csk->com.cdev, skb, csk->l2t);
पूर्ण

अटल व्योम
cxgbit_pass_accept_req(काष्ठा cxgbit_device *cdev, काष्ठा sk_buff *skb)
अणु
	काष्ठा cxgbit_sock *csk = शून्य;
	काष्ठा cxgbit_np *cnp;
	काष्ठा cpl_pass_accept_req *req = cplhdr(skb);
	अचिन्हित पूर्णांक stid = PASS_OPEN_TID_G(ntohl(req->tos_stid));
	काष्ठा tid_info *t = cdev->lldi.tids;
	अचिन्हित पूर्णांक tid = GET_TID(req);
	u16 peer_mss = ntohs(req->tcpopt.mss);
	अचिन्हित लघु hdrs;

	काष्ठा dst_entry *dst;
	__u8 local_ip[16], peer_ip[16];
	__be16 local_port, peer_port;
	पूर्णांक ret;
	पूर्णांक iptype;

	pr_debug("%s: cdev = %p; stid = %u; tid = %u\n",
		 __func__, cdev, stid, tid);

	cnp = lookup_stid(t, stid);
	अगर (!cnp) अणु
		pr_err("%s connect request on invalid stid %d\n",
		       __func__, stid);
		जाओ rel_skb;
	पूर्ण

	अगर (cnp->com.state != CSK_STATE_LISTEN) अणु
		pr_err("%s - listening parent not in CSK_STATE_LISTEN\n",
		       __func__);
		जाओ reject;
	पूर्ण

	csk = lookup_tid(t, tid);
	अगर (csk) अणु
		pr_err("%s csk not null tid %u\n",
		       __func__, tid);
		जाओ rel_skb;
	पूर्ण

	cxgb_get_4tuple(req, cdev->lldi.adapter_type, &iptype, local_ip,
			peer_ip, &local_port, &peer_port);

	/* Find output route */
	अगर (iptype == 4)  अणु
		pr_debug("%s parent sock %p tid %u laddr %pI4 raddr %pI4 "
			 "lport %d rport %d peer_mss %d\n"
			 , __func__, cnp, tid,
			 local_ip, peer_ip, ntohs(local_port),
			 ntohs(peer_port), peer_mss);
		dst = cxgb_find_route(&cdev->lldi, cxgbit_get_real_dev,
				      *(__be32 *)local_ip,
				      *(__be32 *)peer_ip,
				      local_port, peer_port,
				      PASS_OPEN_TOS_G(ntohl(req->tos_stid)));
	पूर्ण अन्यथा अणु
		pr_debug("%s parent sock %p tid %u laddr %pI6 raddr %pI6 "
			 "lport %d rport %d peer_mss %d\n"
			 , __func__, cnp, tid,
			 local_ip, peer_ip, ntohs(local_port),
			 ntohs(peer_port), peer_mss);
		dst = cxgb_find_route6(&cdev->lldi, cxgbit_get_real_dev,
				       local_ip, peer_ip,
				       local_port, peer_port,
				       PASS_OPEN_TOS_G(ntohl(req->tos_stid)),
				       ((काष्ठा sockaddr_in6 *)
					&cnp->com.local_addr)->sin6_scope_id);
	पूर्ण
	अगर (!dst) अणु
		pr_err("%s - failed to find dst entry!\n",
		       __func__);
		जाओ reject;
	पूर्ण

	csk = kzalloc(माप(*csk), GFP_ATOMIC);
	अगर (!csk) अणु
		dst_release(dst);
		जाओ rel_skb;
	पूर्ण

	ret = cxgbit_offload_init(csk, iptype, peer_ip, ntohs(local_port),
				  dst, cdev);
	अगर (ret) अणु
		pr_err("%s - failed to allocate l2t entry!\n",
		       __func__);
		dst_release(dst);
		kमुक्त(csk);
		जाओ reject;
	पूर्ण

	kref_init(&csk->kref);
	init_completion(&csk->com.wr_रुको.completion);

	INIT_LIST_HEAD(&csk->accept_node);

	hdrs = (iptype == 4 ? माप(काष्ठा iphdr) : माप(काष्ठा ipv6hdr)) +
		माप(काष्ठा tcphdr) +	(req->tcpopt.tstamp ? 12 : 0);
	अगर (peer_mss && csk->mtu > (peer_mss + hdrs))
		csk->mtu = peer_mss + hdrs;

	csk->com.state = CSK_STATE_CONNECTING;
	csk->com.cdev = cdev;
	csk->cnp = cnp;
	csk->tos = PASS_OPEN_TOS_G(ntohl(req->tos_stid));
	csk->dst = dst;
	csk->tid = tid;
	csk->wr_cred = cdev->lldi.wr_cred -
			DIV_ROUND_UP(माप(काष्ठा cpl_पात_req), 16);
	csk->wr_max_cred = csk->wr_cred;
	csk->wr_una_cred = 0;

	अगर (iptype == 4) अणु
		काष्ठा sockaddr_in *sin = (काष्ठा sockaddr_in *)
					  &csk->com.local_addr;
		sin->sin_family = AF_INET;
		sin->sin_port = local_port;
		sin->sin_addr.s_addr = *(__be32 *)local_ip;

		sin = (काष्ठा sockaddr_in *)&csk->com.remote_addr;
		sin->sin_family = AF_INET;
		sin->sin_port = peer_port;
		sin->sin_addr.s_addr = *(__be32 *)peer_ip;
	पूर्ण अन्यथा अणु
		काष्ठा sockaddr_in6 *sin6 = (काष्ठा sockaddr_in6 *)
					    &csk->com.local_addr;

		sin6->sin6_family = PF_INET6;
		sin6->sin6_port = local_port;
		स_नकल(sin6->sin6_addr.s6_addr, local_ip, 16);
		cxgb4_clip_get(cdev->lldi.ports[0],
			       (स्थिर u32 *)&sin6->sin6_addr.s6_addr,
			       1);

		sin6 = (काष्ठा sockaddr_in6 *)&csk->com.remote_addr;
		sin6->sin6_family = PF_INET6;
		sin6->sin6_port = peer_port;
		स_नकल(sin6->sin6_addr.s6_addr, peer_ip, 16);
	पूर्ण

	skb_queue_head_init(&csk->rxq);
	skb_queue_head_init(&csk->txq);
	skb_queue_head_init(&csk->ppodq);
	skb_queue_head_init(&csk->backlogq);
	skb_queue_head_init(&csk->skbq);
	cxgbit_sock_reset_wr_list(csk);
	spin_lock_init(&csk->lock);
	init_रुकोqueue_head(&csk->रुकोq);
	csk->lock_owner = false;

	अगर (cxgbit_alloc_csk_skb(csk)) अणु
		dst_release(dst);
		kमुक्त(csk);
		जाओ rel_skb;
	पूर्ण

	cxgbit_get_cnp(cnp);
	cxgbit_get_cdev(cdev);

	spin_lock(&cdev->cskq.lock);
	list_add_tail(&csk->list, &cdev->cskq.list);
	spin_unlock(&cdev->cskq.lock);
	cxgb4_insert_tid(t, csk, tid, csk->com.local_addr.ss_family);
	cxgbit_pass_accept_rpl(csk, req);
	जाओ rel_skb;

reject:
	cxgbit_release_tid(cdev, tid);
rel_skb:
	__kमुक्त_skb(skb);
पूर्ण

अटल u32
cxgbit_tx_flowc_wr_credits(काष्ठा cxgbit_sock *csk, u32 *nparamsp,
			   u32 *flowclenp)
अणु
	u32 nparams, flowclen16, flowclen;

	nparams = FLOWC_WR_NPARAMS_MIN;

	अगर (csk->snd_wscale)
		nparams++;

#अगर_घोषित CONFIG_CHELSIO_T4_DCB
	nparams++;
#पूर्ण_अगर
	flowclen = दुरत्व(काष्ठा fw_flowc_wr, mnemval[nparams]);
	flowclen16 = DIV_ROUND_UP(flowclen, 16);
	flowclen = flowclen16 * 16;
	/*
	 * Return the number of 16-byte credits used by the flowc request.
	 * Pass back the nparams and actual flowc length अगर requested.
	 */
	अगर (nparamsp)
		*nparamsp = nparams;
	अगर (flowclenp)
		*flowclenp = flowclen;
	वापस flowclen16;
पूर्ण

u32 cxgbit_send_tx_flowc_wr(काष्ठा cxgbit_sock *csk)
अणु
	काष्ठा cxgbit_device *cdev = csk->com.cdev;
	काष्ठा fw_flowc_wr *flowc;
	u32 nparams, flowclen16, flowclen;
	काष्ठा sk_buff *skb;
	u8 index;

#अगर_घोषित CONFIG_CHELSIO_T4_DCB
	u16 vlan = ((काष्ठा l2t_entry *)csk->l2t)->vlan;
#पूर्ण_अगर

	flowclen16 = cxgbit_tx_flowc_wr_credits(csk, &nparams, &flowclen);

	skb = __skb_dequeue(&csk->skbq);
	flowc = __skb_put_zero(skb, flowclen);

	flowc->op_to_nparams = cpu_to_be32(FW_WR_OP_V(FW_FLOWC_WR) |
					   FW_FLOWC_WR_NPARAMS_V(nparams));
	flowc->flowid_len16 = cpu_to_be32(FW_WR_LEN16_V(flowclen16) |
					  FW_WR_FLOWID_V(csk->tid));
	flowc->mnemval[0].mnemonic = FW_FLOWC_MNEM_PFNVFN;
	flowc->mnemval[0].val = cpu_to_be32(FW_PFVF_CMD_PFN_V
					    (csk->com.cdev->lldi.pf));
	flowc->mnemval[1].mnemonic = FW_FLOWC_MNEM_CH;
	flowc->mnemval[1].val = cpu_to_be32(csk->tx_chan);
	flowc->mnemval[2].mnemonic = FW_FLOWC_MNEM_PORT;
	flowc->mnemval[2].val = cpu_to_be32(csk->tx_chan);
	flowc->mnemval[3].mnemonic = FW_FLOWC_MNEM_IQID;
	flowc->mnemval[3].val = cpu_to_be32(csk->rss_qid);
	flowc->mnemval[4].mnemonic = FW_FLOWC_MNEM_SNDNXT;
	flowc->mnemval[4].val = cpu_to_be32(csk->snd_nxt);
	flowc->mnemval[5].mnemonic = FW_FLOWC_MNEM_RCVNXT;
	flowc->mnemval[5].val = cpu_to_be32(csk->rcv_nxt);
	flowc->mnemval[6].mnemonic = FW_FLOWC_MNEM_SNDBUF;
	flowc->mnemval[6].val = cpu_to_be32(csk->snd_win);
	flowc->mnemval[7].mnemonic = FW_FLOWC_MNEM_MSS;
	flowc->mnemval[7].val = cpu_to_be32(csk->emss);

	flowc->mnemval[8].mnemonic = FW_FLOWC_MNEM_TXDATAPLEN_MAX;
	अगर (test_bit(CDEV_ISO_ENABLE, &cdev->flags))
		flowc->mnemval[8].val = cpu_to_be32(CXGBIT_MAX_ISO_PAYLOAD);
	अन्यथा
		flowc->mnemval[8].val = cpu_to_be32(16384);

	index = 9;

	अगर (csk->snd_wscale) अणु
		flowc->mnemval[index].mnemonic = FW_FLOWC_MNEM_RCV_SCALE;
		flowc->mnemval[index].val = cpu_to_be32(csk->snd_wscale);
		index++;
	पूर्ण

#अगर_घोषित CONFIG_CHELSIO_T4_DCB
	flowc->mnemval[index].mnemonic = FW_FLOWC_MNEM_DCBPRIO;
	अगर (vlan == VLAN_NONE) अणु
		pr_warn("csk %u without VLAN Tag on DCB Link\n", csk->tid);
		flowc->mnemval[index].val = cpu_to_be32(0);
	पूर्ण अन्यथा
		flowc->mnemval[index].val = cpu_to_be32(
				(vlan & VLAN_PRIO_MASK) >> VLAN_PRIO_SHIFT);
#पूर्ण_अगर

	pr_debug("%s: csk %p; tx_chan = %u; rss_qid = %u; snd_seq = %u;"
		 " rcv_seq = %u; snd_win = %u; emss = %u\n",
		 __func__, csk, csk->tx_chan, csk->rss_qid, csk->snd_nxt,
		 csk->rcv_nxt, csk->snd_win, csk->emss);
	set_wr_txq(skb, CPL_PRIORITY_DATA, csk->txq_idx);
	cxgbit_ofld_send(csk->com.cdev, skb);
	वापस flowclen16;
पूर्ण

अटल पूर्णांक
cxgbit_send_tcb_skb(काष्ठा cxgbit_sock *csk, काष्ठा sk_buff *skb)
अणु
	spin_lock_bh(&csk->lock);
	अगर (unlikely(csk->com.state != CSK_STATE_ESTABLISHED)) अणु
		spin_unlock_bh(&csk->lock);
		pr_err("%s: csk 0x%p, tid %u, state %u\n",
		       __func__, csk, csk->tid, csk->com.state);
		__kमुक्त_skb(skb);
		वापस -1;
	पूर्ण

	cxgbit_get_csk(csk);
	cxgbit_init_wr_रुको(&csk->com.wr_रुको);
	cxgbit_ofld_send(csk->com.cdev, skb);
	spin_unlock_bh(&csk->lock);

	वापस 0;
पूर्ण

पूर्णांक cxgbit_setup_conn_digest(काष्ठा cxgbit_sock *csk)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा cpl_set_tcb_field *req;
	u8 hcrc = csk->submode & CXGBIT_SUBMODE_HCRC;
	u8 dcrc = csk->submode & CXGBIT_SUBMODE_DCRC;
	अचिन्हित पूर्णांक len = roundup(माप(*req), 16);
	पूर्णांक ret;

	skb = alloc_skb(len, GFP_KERNEL);
	अगर (!skb)
		वापस -ENOMEM;

	/*  set up ulp submode */
	req = __skb_put_zero(skb, len);

	INIT_TP_WR(req, csk->tid);
	OPCODE_TID(req) = htonl(MK_OPCODE_TID(CPL_SET_TCB_FIELD, csk->tid));
	req->reply_ctrl = htons(NO_REPLY_V(0) | QUEUENO_V(csk->rss_qid));
	req->word_cookie = htons(0);
	req->mask = cpu_to_be64(0x3 << 4);
	req->val = cpu_to_be64(((hcrc ? ULP_CRC_HEADER : 0) |
				(dcrc ? ULP_CRC_DATA : 0)) << 4);
	set_wr_txq(skb, CPL_PRIORITY_CONTROL, csk->ctrlq_idx);

	अगर (cxgbit_send_tcb_skb(csk, skb))
		वापस -1;

	ret = cxgbit_रुको_क्रम_reply(csk->com.cdev,
				    &csk->com.wr_रुको,
				    csk->tid, 5, __func__);
	अगर (ret)
		वापस -1;

	वापस 0;
पूर्ण

पूर्णांक cxgbit_setup_conn_pgidx(काष्ठा cxgbit_sock *csk, u32 pg_idx)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा cpl_set_tcb_field *req;
	अचिन्हित पूर्णांक len = roundup(माप(*req), 16);
	पूर्णांक ret;

	skb = alloc_skb(len, GFP_KERNEL);
	अगर (!skb)
		वापस -ENOMEM;

	req = __skb_put_zero(skb, len);

	INIT_TP_WR(req, csk->tid);
	OPCODE_TID(req) = htonl(MK_OPCODE_TID(CPL_SET_TCB_FIELD, csk->tid));
	req->reply_ctrl = htons(NO_REPLY_V(0) | QUEUENO_V(csk->rss_qid));
	req->word_cookie = htons(0);
	req->mask = cpu_to_be64(0x3 << 8);
	req->val = cpu_to_be64(pg_idx << 8);
	set_wr_txq(skb, CPL_PRIORITY_CONTROL, csk->ctrlq_idx);

	अगर (cxgbit_send_tcb_skb(csk, skb))
		वापस -1;

	ret = cxgbit_रुको_क्रम_reply(csk->com.cdev,
				    &csk->com.wr_रुको,
				    csk->tid, 5, __func__);
	अगर (ret)
		वापस -1;

	वापस 0;
पूर्ण

अटल व्योम
cxgbit_pass_खोलो_rpl(काष्ठा cxgbit_device *cdev, काष्ठा sk_buff *skb)
अणु
	काष्ठा cpl_pass_खोलो_rpl *rpl = cplhdr(skb);
	काष्ठा tid_info *t = cdev->lldi.tids;
	अचिन्हित पूर्णांक stid = GET_TID(rpl);
	काष्ठा cxgbit_np *cnp = lookup_stid(t, stid);

	pr_debug("%s: cnp = %p; stid = %u; status = %d\n",
		 __func__, cnp, stid, rpl->status);

	अगर (!cnp) अणु
		pr_info("%s stid %d lookup failure\n", __func__, stid);
		जाओ rel_skb;
	पूर्ण

	cxgbit_wake_up(&cnp->com.wr_रुको, __func__, rpl->status);
	cxgbit_put_cnp(cnp);
rel_skb:
	__kमुक्त_skb(skb);
पूर्ण

अटल व्योम
cxgbit_बंद_listsrv_rpl(काष्ठा cxgbit_device *cdev, काष्ठा sk_buff *skb)
अणु
	काष्ठा cpl_बंद_listsvr_rpl *rpl = cplhdr(skb);
	काष्ठा tid_info *t = cdev->lldi.tids;
	अचिन्हित पूर्णांक stid = GET_TID(rpl);
	काष्ठा cxgbit_np *cnp = lookup_stid(t, stid);

	pr_debug("%s: cnp = %p; stid = %u; status = %d\n",
		 __func__, cnp, stid, rpl->status);

	अगर (!cnp) अणु
		pr_info("%s stid %d lookup failure\n", __func__, stid);
		जाओ rel_skb;
	पूर्ण

	cxgbit_wake_up(&cnp->com.wr_रुको, __func__, rpl->status);
	cxgbit_put_cnp(cnp);
rel_skb:
	__kमुक्त_skb(skb);
पूर्ण

अटल व्योम
cxgbit_pass_establish(काष्ठा cxgbit_device *cdev, काष्ठा sk_buff *skb)
अणु
	काष्ठा cpl_pass_establish *req = cplhdr(skb);
	काष्ठा tid_info *t = cdev->lldi.tids;
	अचिन्हित पूर्णांक tid = GET_TID(req);
	काष्ठा cxgbit_sock *csk;
	काष्ठा cxgbit_np *cnp;
	u16 tcp_opt = be16_to_cpu(req->tcp_opt);
	u32 snd_isn = be32_to_cpu(req->snd_isn);
	u32 rcv_isn = be32_to_cpu(req->rcv_isn);

	csk = lookup_tid(t, tid);
	अगर (unlikely(!csk)) अणु
		pr_err("can't find connection for tid %u.\n", tid);
		जाओ rel_skb;
	पूर्ण
	cnp = csk->cnp;

	pr_debug("%s: csk %p; tid %u; cnp %p\n",
		 __func__, csk, tid, cnp);

	csk->ग_लिखो_seq = snd_isn;
	csk->snd_una = snd_isn;
	csk->snd_nxt = snd_isn;

	csk->rcv_nxt = rcv_isn;

	अगर (csk->rcv_win > (RCV_बफ_मान_M << 10))
		csk->rx_credits = (csk->rcv_win - (RCV_बफ_मान_M << 10));

	csk->snd_wscale = TCPOPT_SND_WSCALE_G(tcp_opt);
	cxgbit_set_emss(csk, tcp_opt);
	dst_confirm(csk->dst);
	csk->com.state = CSK_STATE_ESTABLISHED;
	spin_lock_bh(&cnp->np_accept_lock);
	list_add_tail(&csk->accept_node, &cnp->np_accept_list);
	spin_unlock_bh(&cnp->np_accept_lock);
	complete(&cnp->accept_comp);
rel_skb:
	__kमुक्त_skb(skb);
पूर्ण

अटल व्योम cxgbit_queue_rx_skb(काष्ठा cxgbit_sock *csk, काष्ठा sk_buff *skb)
अणु
	cxgbit_skcb_flags(skb) = 0;
	spin_lock_bh(&csk->rxq.lock);
	__skb_queue_tail(&csk->rxq, skb);
	spin_unlock_bh(&csk->rxq.lock);
	wake_up(&csk->रुकोq);
पूर्ण

अटल व्योम cxgbit_peer_बंद(काष्ठा cxgbit_sock *csk, काष्ठा sk_buff *skb)
अणु
	pr_debug("%s: csk %p; tid %u; state %d\n",
		 __func__, csk, csk->tid, csk->com.state);

	चयन (csk->com.state) अणु
	हाल CSK_STATE_ESTABLISHED:
		csk->com.state = CSK_STATE_CLOSING;
		cxgbit_queue_rx_skb(csk, skb);
		वापस;
	हाल CSK_STATE_CLOSING:
		/* simultaneous बंद */
		csk->com.state = CSK_STATE_MORIBUND;
		अवरोध;
	हाल CSK_STATE_MORIBUND:
		csk->com.state = CSK_STATE_DEAD;
		cxgbit_put_csk(csk);
		अवरोध;
	हाल CSK_STATE_ABORTING:
		अवरोध;
	शेष:
		pr_info("%s: cpl_peer_close in bad state %d\n",
			__func__, csk->com.state);
	पूर्ण

	__kमुक्त_skb(skb);
पूर्ण

अटल व्योम cxgbit_बंद_con_rpl(काष्ठा cxgbit_sock *csk, काष्ठा sk_buff *skb)
अणु
	pr_debug("%s: csk %p; tid %u; state %d\n",
		 __func__, csk, csk->tid, csk->com.state);

	चयन (csk->com.state) अणु
	हाल CSK_STATE_CLOSING:
		csk->com.state = CSK_STATE_MORIBUND;
		अवरोध;
	हाल CSK_STATE_MORIBUND:
		csk->com.state = CSK_STATE_DEAD;
		cxgbit_put_csk(csk);
		अवरोध;
	हाल CSK_STATE_ABORTING:
	हाल CSK_STATE_DEAD:
		अवरोध;
	शेष:
		pr_info("%s: cpl_close_con_rpl in bad state %d\n",
			__func__, csk->com.state);
	पूर्ण

	__kमुक्त_skb(skb);
पूर्ण

अटल व्योम cxgbit_पात_req_rss(काष्ठा cxgbit_sock *csk, काष्ठा sk_buff *skb)
अणु
	काष्ठा cpl_पात_req_rss *hdr = cplhdr(skb);
	अचिन्हित पूर्णांक tid = GET_TID(hdr);
	काष्ठा sk_buff *rpl_skb;
	bool release = false;
	bool wakeup_thपढ़ो = false;
	u32 len = roundup(माप(काष्ठा cpl_पात_rpl), 16);

	pr_debug("%s: csk %p; tid %u; state %d\n",
		 __func__, csk, tid, csk->com.state);

	अगर (cxgb_is_neg_adv(hdr->status)) अणु
		pr_err("%s: got neg advise %d on tid %u\n",
		       __func__, hdr->status, tid);
		जाओ rel_skb;
	पूर्ण

	चयन (csk->com.state) अणु
	हाल CSK_STATE_CONNECTING:
	हाल CSK_STATE_MORIBUND:
		csk->com.state = CSK_STATE_DEAD;
		release = true;
		अवरोध;
	हाल CSK_STATE_ESTABLISHED:
		csk->com.state = CSK_STATE_DEAD;
		wakeup_thपढ़ो = true;
		अवरोध;
	हाल CSK_STATE_CLOSING:
		csk->com.state = CSK_STATE_DEAD;
		अगर (!csk->conn)
			release = true;
		अवरोध;
	हाल CSK_STATE_ABORTING:
		अवरोध;
	शेष:
		pr_info("%s: cpl_abort_req_rss in bad state %d\n",
			__func__, csk->com.state);
		csk->com.state = CSK_STATE_DEAD;
	पूर्ण

	__skb_queue_purge(&csk->txq);

	अगर (!test_and_set_bit(CSK_TX_DATA_SENT, &csk->com.flags))
		cxgbit_send_tx_flowc_wr(csk);

	rpl_skb = __skb_dequeue(&csk->skbq);

	cxgb_mk_पात_rpl(rpl_skb, len, csk->tid, csk->txq_idx);
	cxgbit_ofld_send(csk->com.cdev, rpl_skb);

	अगर (wakeup_thपढ़ो) अणु
		cxgbit_queue_rx_skb(csk, skb);
		वापस;
	पूर्ण

	अगर (release)
		cxgbit_put_csk(csk);
rel_skb:
	__kमुक्त_skb(skb);
पूर्ण

अटल व्योम cxgbit_पात_rpl_rss(काष्ठा cxgbit_sock *csk, काष्ठा sk_buff *skb)
अणु
	काष्ठा cpl_पात_rpl_rss *rpl = cplhdr(skb);

	pr_debug("%s: csk %p; tid %u; state %d\n",
		 __func__, csk, csk->tid, csk->com.state);

	चयन (csk->com.state) अणु
	हाल CSK_STATE_ABORTING:
		csk->com.state = CSK_STATE_DEAD;
		अगर (test_bit(CSK_ABORT_RPL_WAIT, &csk->com.flags))
			cxgbit_wake_up(&csk->com.wr_रुको, __func__,
				       rpl->status);
		cxgbit_put_csk(csk);
		अवरोध;
	शेष:
		pr_info("%s: cpl_abort_rpl_rss in state %d\n",
			__func__, csk->com.state);
	पूर्ण

	__kमुक्त_skb(skb);
पूर्ण

अटल bool cxgbit_credit_err(स्थिर काष्ठा cxgbit_sock *csk)
अणु
	स्थिर काष्ठा sk_buff *skb = csk->wr_pending_head;
	u32 credit = 0;

	अगर (unlikely(csk->wr_cred > csk->wr_max_cred)) अणु
		pr_err("csk 0x%p, tid %u, credit %u > %u\n",
		       csk, csk->tid, csk->wr_cred, csk->wr_max_cred);
		वापस true;
	पूर्ण

	जबतक (skb) अणु
		credit += (__क्रमce u32)skb->csum;
		skb = cxgbit_skcb_tx_wr_next(skb);
	पूर्ण

	अगर (unlikely((csk->wr_cred + credit) != csk->wr_max_cred)) अणु
		pr_err("csk 0x%p, tid %u, credit %u + %u != %u.\n",
		       csk, csk->tid, csk->wr_cred,
		       credit, csk->wr_max_cred);

		वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल व्योम cxgbit_fw4_ack(काष्ठा cxgbit_sock *csk, काष्ठा sk_buff *skb)
अणु
	काष्ठा cpl_fw4_ack *rpl = (काष्ठा cpl_fw4_ack *)cplhdr(skb);
	u32 credits = rpl->credits;
	u32 snd_una = ntohl(rpl->snd_una);

	csk->wr_cred += credits;
	अगर (csk->wr_una_cred > (csk->wr_max_cred - csk->wr_cred))
		csk->wr_una_cred = csk->wr_max_cred - csk->wr_cred;

	जबतक (credits) अणु
		काष्ठा sk_buff *p = cxgbit_sock_peek_wr(csk);
		u32 csum;

		अगर (unlikely(!p)) अणु
			pr_err("csk 0x%p,%u, cr %u,%u+%u, empty.\n",
			       csk, csk->tid, credits,
			       csk->wr_cred, csk->wr_una_cred);
			अवरोध;
		पूर्ण

		csum = (__क्रमce u32)p->csum;
		अगर (unlikely(credits < csum)) अणु
			pr_warn("csk 0x%p,%u, cr %u,%u+%u, < %u.\n",
				csk,  csk->tid,
				credits, csk->wr_cred, csk->wr_una_cred,
				csum);
			p->csum = (__क्रमce __wsum)(csum - credits);
			अवरोध;
		पूर्ण

		cxgbit_sock_dequeue_wr(csk);
		credits -= csum;
		kमुक्त_skb(p);
	पूर्ण

	अगर (unlikely(cxgbit_credit_err(csk))) अणु
		cxgbit_queue_rx_skb(csk, skb);
		वापस;
	पूर्ण

	अगर (rpl->seq_vld & CPL_FW4_ACK_FLAGS_SEQVAL) अणु
		अगर (unlikely(beक्रमe(snd_una, csk->snd_una))) अणु
			pr_warn("csk 0x%p,%u, snd_una %u/%u.",
				csk, csk->tid, snd_una,
				csk->snd_una);
			जाओ rel_skb;
		पूर्ण

		अगर (csk->snd_una != snd_una) अणु
			csk->snd_una = snd_una;
			dst_confirm(csk->dst);
		पूर्ण
	पूर्ण

	अगर (skb_queue_len(&csk->txq))
		cxgbit_push_tx_frames(csk);

rel_skb:
	__kमुक्त_skb(skb);
पूर्ण

अटल व्योम cxgbit_set_tcb_rpl(काष्ठा cxgbit_device *cdev, काष्ठा sk_buff *skb)
अणु
	काष्ठा cxgbit_sock *csk;
	काष्ठा cpl_set_tcb_rpl *rpl = (काष्ठा cpl_set_tcb_rpl *)skb->data;
	अचिन्हित पूर्णांक tid = GET_TID(rpl);
	काष्ठा cxgb4_lld_info *lldi = &cdev->lldi;
	काष्ठा tid_info *t = lldi->tids;

	csk = lookup_tid(t, tid);
	अगर (unlikely(!csk)) अणु
		pr_err("can't find connection for tid %u.\n", tid);
		जाओ rel_skb;
	पूर्ण अन्यथा अणु
		cxgbit_wake_up(&csk->com.wr_रुको, __func__, rpl->status);
	पूर्ण

	cxgbit_put_csk(csk);
rel_skb:
	__kमुक्त_skb(skb);
पूर्ण

अटल व्योम cxgbit_rx_data(काष्ठा cxgbit_device *cdev, काष्ठा sk_buff *skb)
अणु
	काष्ठा cxgbit_sock *csk;
	काष्ठा cpl_rx_data *cpl = cplhdr(skb);
	अचिन्हित पूर्णांक tid = GET_TID(cpl);
	काष्ठा cxgb4_lld_info *lldi = &cdev->lldi;
	काष्ठा tid_info *t = lldi->tids;

	csk = lookup_tid(t, tid);
	अगर (unlikely(!csk)) अणु
		pr_err("can't find conn. for tid %u.\n", tid);
		जाओ rel_skb;
	पूर्ण

	cxgbit_queue_rx_skb(csk, skb);
	वापस;
rel_skb:
	__kमुक्त_skb(skb);
पूर्ण

अटल व्योम
__cxgbit_process_rx_cpl(काष्ठा cxgbit_sock *csk, काष्ठा sk_buff *skb)
अणु
	spin_lock(&csk->lock);
	अगर (csk->lock_owner) अणु
		__skb_queue_tail(&csk->backlogq, skb);
		spin_unlock(&csk->lock);
		वापस;
	पूर्ण

	cxgbit_skcb_rx_backlog_fn(skb)(csk, skb);
	spin_unlock(&csk->lock);
पूर्ण

अटल व्योम cxgbit_process_rx_cpl(काष्ठा cxgbit_sock *csk, काष्ठा sk_buff *skb)
अणु
	cxgbit_get_csk(csk);
	__cxgbit_process_rx_cpl(csk, skb);
	cxgbit_put_csk(csk);
पूर्ण

अटल व्योम cxgbit_rx_cpl(काष्ठा cxgbit_device *cdev, काष्ठा sk_buff *skb)
अणु
	काष्ठा cxgbit_sock *csk;
	काष्ठा cpl_tx_data *cpl = cplhdr(skb);
	काष्ठा cxgb4_lld_info *lldi = &cdev->lldi;
	काष्ठा tid_info *t = lldi->tids;
	अचिन्हित पूर्णांक tid = GET_TID(cpl);
	u8 opcode = cxgbit_skcb_rx_opcode(skb);
	bool ref = true;

	चयन (opcode) अणु
	हाल CPL_FW4_ACK:
			cxgbit_skcb_rx_backlog_fn(skb) = cxgbit_fw4_ack;
			ref = false;
			अवरोध;
	हाल CPL_PEER_CLOSE:
			cxgbit_skcb_rx_backlog_fn(skb) = cxgbit_peer_बंद;
			अवरोध;
	हाल CPL_CLOSE_CON_RPL:
			cxgbit_skcb_rx_backlog_fn(skb) = cxgbit_बंद_con_rpl;
			अवरोध;
	हाल CPL_ABORT_REQ_RSS:
			cxgbit_skcb_rx_backlog_fn(skb) = cxgbit_पात_req_rss;
			अवरोध;
	हाल CPL_ABORT_RPL_RSS:
			cxgbit_skcb_rx_backlog_fn(skb) = cxgbit_पात_rpl_rss;
			अवरोध;
	शेष:
		जाओ rel_skb;
	पूर्ण

	csk = lookup_tid(t, tid);
	अगर (unlikely(!csk)) अणु
		pr_err("can't find conn. for tid %u.\n", tid);
		जाओ rel_skb;
	पूर्ण

	अगर (ref)
		cxgbit_process_rx_cpl(csk, skb);
	अन्यथा
		__cxgbit_process_rx_cpl(csk, skb);

	वापस;
rel_skb:
	__kमुक्त_skb(skb);
पूर्ण

cxgbit_cplhandler_func cxgbit_cplhandlers[NUM_CPL_CMDS] = अणु
	[CPL_PASS_OPEN_RPL]	= cxgbit_pass_खोलो_rpl,
	[CPL_CLOSE_LISTSRV_RPL] = cxgbit_बंद_listsrv_rpl,
	[CPL_PASS_ACCEPT_REQ]	= cxgbit_pass_accept_req,
	[CPL_PASS_ESTABLISH]	= cxgbit_pass_establish,
	[CPL_SET_TCB_RPL]	= cxgbit_set_tcb_rpl,
	[CPL_RX_DATA]		= cxgbit_rx_data,
	[CPL_FW4_ACK]		= cxgbit_rx_cpl,
	[CPL_PEER_CLOSE]	= cxgbit_rx_cpl,
	[CPL_CLOSE_CON_RPL]	= cxgbit_rx_cpl,
	[CPL_ABORT_REQ_RSS]	= cxgbit_rx_cpl,
	[CPL_ABORT_RPL_RSS]	= cxgbit_rx_cpl,
पूर्ण;
