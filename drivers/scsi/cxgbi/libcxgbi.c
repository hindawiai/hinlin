<शैली गुरु>
/*
 * libcxgbi.c: Chelsio common library क्रम T3/T4 iSCSI driver.
 *
 * Copyright (c) 2010-2015 Chelsio Communications, Inc.
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation.
 *
 * Written by: Karen Xie (kxie@chelsio.com)
 * Written by: Rakesh Ranjan (rranjan@chelsio.com)
 */

#घोषणा pr_fmt(fmt)	KBUILD_MODNAME ":%s: " fmt, __func__

#समावेश <linux/skbuff.h>
#समावेश <linux/crypto.h>
#समावेश <linux/scatterlist.h>
#समावेश <linux/pci.h>
#समावेश <scsi/scsi.h>
#समावेश <scsi/scsi_cmnd.h>
#समावेश <scsi/scsi_host.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <linux/inet.h>
#समावेश <net/dst.h>
#समावेश <net/route.h>
#समावेश <net/ipv6.h>
#समावेश <net/ip6_route.h>
#समावेश <net/addrconf.h>

#समावेश <linux/inetdevice.h>	/* ip_dev_find */
#समावेश <linux/module.h>
#समावेश <net/tcp.h>

अटल अचिन्हित पूर्णांक dbg_level;

#समावेश "libcxgbi.h"

#घोषणा DRV_MODULE_NAME		"libcxgbi"
#घोषणा DRV_MODULE_DESC		"Chelsio iSCSI driver library"
#घोषणा DRV_MODULE_VERSION	"0.9.1-ko"
#घोषणा DRV_MODULE_RELDATE	"Apr. 2015"

अटल अक्षर version[] =
	DRV_MODULE_DESC " " DRV_MODULE_NAME
	" v" DRV_MODULE_VERSION " (" DRV_MODULE_RELDATE ")\n";

MODULE_AUTHOR("Chelsio Communications, Inc.");
MODULE_DESCRIPTION(DRV_MODULE_DESC);
MODULE_VERSION(DRV_MODULE_VERSION);
MODULE_LICENSE("GPL");

module_param(dbg_level, uपूर्णांक, 0644);
MODULE_PARM_DESC(dbg_level, "libiscsi debug level (default=0)");


/*
 * cxgbi device management
 * मुख्यtains a list of the cxgbi devices
 */
अटल LIST_HEAD(cdev_list);
अटल DEFINE_MUTEX(cdev_mutex);

अटल LIST_HEAD(cdev_rcu_list);
अटल DEFINE_SPINLOCK(cdev_rcu_lock);

अटल अंतरभूत व्योम cxgbi_decode_sw_tag(u32 sw_tag, पूर्णांक *idx, पूर्णांक *age)
अणु
	अगर (age)
		*age = sw_tag & 0x7FFF;
	अगर (idx)
		*idx = (sw_tag >> 16) & 0x7FFF;
पूर्ण

पूर्णांक cxgbi_device_porपंचांगap_create(काष्ठा cxgbi_device *cdev, अचिन्हित पूर्णांक base,
				अचिन्हित पूर्णांक max_conn)
अणु
	काष्ठा cxgbi_ports_map *pmap = &cdev->pmap;

	pmap->port_csk = kvzalloc(array_size(max_conn,
					     माप(काष्ठा cxgbi_sock *)),
				  GFP_KERNEL | __GFP_NOWARN);
	अगर (!pmap->port_csk) अणु
		pr_warn("cdev 0x%p, portmap OOM %u.\n", cdev, max_conn);
		वापस -ENOMEM;
	पूर्ण

	pmap->max_connect = max_conn;
	pmap->sport_base = base;
	spin_lock_init(&pmap->lock);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(cxgbi_device_porपंचांगap_create);

व्योम cxgbi_device_porपंचांगap_cleanup(काष्ठा cxgbi_device *cdev)
अणु
	काष्ठा cxgbi_ports_map *pmap = &cdev->pmap;
	काष्ठा cxgbi_sock *csk;
	पूर्णांक i;

	क्रम (i = 0; i < pmap->max_connect; i++) अणु
		अगर (pmap->port_csk[i]) अणु
			csk = pmap->port_csk[i];
			pmap->port_csk[i] = शून्य;
			log_debug(1 << CXGBI_DBG_SOCK,
				"csk 0x%p, cdev 0x%p, offload down.\n",
				csk, cdev);
			spin_lock_bh(&csk->lock);
			cxgbi_sock_set_flag(csk, CTPF_OFFLOAD_DOWN);
			cxgbi_sock_बंदd(csk);
			spin_unlock_bh(&csk->lock);
			cxgbi_sock_put(csk);
		पूर्ण
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(cxgbi_device_porपंचांगap_cleanup);

अटल अंतरभूत व्योम cxgbi_device_destroy(काष्ठा cxgbi_device *cdev)
अणु
	log_debug(1 << CXGBI_DBG_DEV,
		"cdev 0x%p, p# %u.\n", cdev, cdev->nports);
	cxgbi_hbas_हटाओ(cdev);
	cxgbi_device_porपंचांगap_cleanup(cdev);
	अगर (cdev->cdev2ppm)
		cxgbi_ppm_release(cdev->cdev2ppm(cdev));
	अगर (cdev->pmap.max_connect)
		kvमुक्त(cdev->pmap.port_csk);
	kमुक्त(cdev);
पूर्ण

काष्ठा cxgbi_device *cxgbi_device_रेजिस्टर(अचिन्हित पूर्णांक extra,
					   अचिन्हित पूर्णांक nports)
अणु
	काष्ठा cxgbi_device *cdev;

	cdev = kzalloc(माप(*cdev) + extra + nports *
			(माप(काष्ठा cxgbi_hba *) +
			 माप(काष्ठा net_device *)),
			GFP_KERNEL);
	अगर (!cdev) अणु
		pr_warn("nport %d, OOM.\n", nports);
		वापस शून्य;
	पूर्ण
	cdev->ports = (काष्ठा net_device **)(cdev + 1);
	cdev->hbas = (काष्ठा cxgbi_hba **)(((अक्षर*)cdev->ports) + nports *
						माप(काष्ठा net_device *));
	अगर (extra)
		cdev->dd_data = ((अक्षर *)cdev->hbas) +
				nports * माप(काष्ठा cxgbi_hba *);
	spin_lock_init(&cdev->pmap.lock);

	mutex_lock(&cdev_mutex);
	list_add_tail(&cdev->list_head, &cdev_list);
	mutex_unlock(&cdev_mutex);

	spin_lock(&cdev_rcu_lock);
	list_add_tail_rcu(&cdev->rcu_node, &cdev_rcu_list);
	spin_unlock(&cdev_rcu_lock);

	log_debug(1 << CXGBI_DBG_DEV,
		"cdev 0x%p, p# %u.\n", cdev, nports);
	वापस cdev;
पूर्ण
EXPORT_SYMBOL_GPL(cxgbi_device_रेजिस्टर);

व्योम cxgbi_device_unरेजिस्टर(काष्ठा cxgbi_device *cdev)
अणु
	log_debug(1 << CXGBI_DBG_DEV,
		"cdev 0x%p, p# %u,%s.\n",
		cdev, cdev->nports, cdev->nports ? cdev->ports[0]->name : "");

	mutex_lock(&cdev_mutex);
	list_del(&cdev->list_head);
	mutex_unlock(&cdev_mutex);

	spin_lock(&cdev_rcu_lock);
	list_del_rcu(&cdev->rcu_node);
	spin_unlock(&cdev_rcu_lock);
	synchronize_rcu();

	cxgbi_device_destroy(cdev);
पूर्ण
EXPORT_SYMBOL_GPL(cxgbi_device_unरेजिस्टर);

व्योम cxgbi_device_unरेजिस्टर_all(अचिन्हित पूर्णांक flag)
अणु
	काष्ठा cxgbi_device *cdev, *पंचांगp;

	mutex_lock(&cdev_mutex);
	list_क्रम_each_entry_safe(cdev, पंचांगp, &cdev_list, list_head) अणु
		अगर ((cdev->flags & flag) == flag) अणु
			mutex_unlock(&cdev_mutex);
			cxgbi_device_unरेजिस्टर(cdev);
			mutex_lock(&cdev_mutex);
		पूर्ण
	पूर्ण
	mutex_unlock(&cdev_mutex);
पूर्ण
EXPORT_SYMBOL_GPL(cxgbi_device_unरेजिस्टर_all);

काष्ठा cxgbi_device *cxgbi_device_find_by_lldev(व्योम *lldev)
अणु
	काष्ठा cxgbi_device *cdev, *पंचांगp;

	mutex_lock(&cdev_mutex);
	list_क्रम_each_entry_safe(cdev, पंचांगp, &cdev_list, list_head) अणु
		अगर (cdev->lldev == lldev) अणु
			mutex_unlock(&cdev_mutex);
			वापस cdev;
		पूर्ण
	पूर्ण
	mutex_unlock(&cdev_mutex);

	log_debug(1 << CXGBI_DBG_DEV,
		"lldev 0x%p, NO match found.\n", lldev);
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(cxgbi_device_find_by_lldev);

काष्ठा cxgbi_device *cxgbi_device_find_by_netdev(काष्ठा net_device *ndev,
						 पूर्णांक *port)
अणु
	काष्ठा net_device *vdev = शून्य;
	काष्ठा cxgbi_device *cdev, *पंचांगp;
	पूर्णांक i;

	अगर (is_vlan_dev(ndev)) अणु
		vdev = ndev;
		ndev = vlan_dev_real_dev(ndev);
		log_debug(1 << CXGBI_DBG_DEV,
			"vlan dev %s -> %s.\n", vdev->name, ndev->name);
	पूर्ण

	mutex_lock(&cdev_mutex);
	list_क्रम_each_entry_safe(cdev, पंचांगp, &cdev_list, list_head) अणु
		क्रम (i = 0; i < cdev->nports; i++) अणु
			अगर (ndev == cdev->ports[i]) अणु
				cdev->hbas[i]->vdev = vdev;
				mutex_unlock(&cdev_mutex);
				अगर (port)
					*port = i;
				वापस cdev;
			पूर्ण
		पूर्ण
	पूर्ण
	mutex_unlock(&cdev_mutex);
	log_debug(1 << CXGBI_DBG_DEV,
		"ndev 0x%p, %s, NO match found.\n", ndev, ndev->name);
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(cxgbi_device_find_by_netdev);

काष्ठा cxgbi_device *cxgbi_device_find_by_netdev_rcu(काष्ठा net_device *ndev,
						     पूर्णांक *port)
अणु
	काष्ठा net_device *vdev = शून्य;
	काष्ठा cxgbi_device *cdev;
	पूर्णांक i;

	अगर (is_vlan_dev(ndev)) अणु
		vdev = ndev;
		ndev = vlan_dev_real_dev(ndev);
		pr_info("vlan dev %s -> %s.\n", vdev->name, ndev->name);
	पूर्ण

	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(cdev, &cdev_rcu_list, rcu_node) अणु
		क्रम (i = 0; i < cdev->nports; i++) अणु
			अगर (ndev == cdev->ports[i]) अणु
				cdev->hbas[i]->vdev = vdev;
				rcu_पढ़ो_unlock();
				अगर (port)
					*port = i;
				वापस cdev;
			पूर्ण
		पूर्ण
	पूर्ण
	rcu_पढ़ो_unlock();

	log_debug(1 << CXGBI_DBG_DEV,
		  "ndev 0x%p, %s, NO match found.\n", ndev, ndev->name);
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(cxgbi_device_find_by_netdev_rcu);

अटल काष्ठा cxgbi_device *cxgbi_device_find_by_mac(काष्ठा net_device *ndev,
						     पूर्णांक *port)
अणु
	काष्ठा net_device *vdev = शून्य;
	काष्ठा cxgbi_device *cdev, *पंचांगp;
	पूर्णांक i;

	अगर (is_vlan_dev(ndev)) अणु
		vdev = ndev;
		ndev = vlan_dev_real_dev(ndev);
		pr_info("vlan dev %s -> %s.\n", vdev->name, ndev->name);
	पूर्ण

	mutex_lock(&cdev_mutex);
	list_क्रम_each_entry_safe(cdev, पंचांगp, &cdev_list, list_head) अणु
		क्रम (i = 0; i < cdev->nports; i++) अणु
			अगर (!स_भेद(ndev->dev_addr, cdev->ports[i]->dev_addr,
				    MAX_ADDR_LEN)) अणु
				cdev->hbas[i]->vdev = vdev;
				mutex_unlock(&cdev_mutex);
				अगर (port)
					*port = i;
				वापस cdev;
			पूर्ण
		पूर्ण
	पूर्ण
	mutex_unlock(&cdev_mutex);
	log_debug(1 << CXGBI_DBG_DEV,
		  "ndev 0x%p, %s, NO match mac found.\n",
		  ndev, ndev->name);
	वापस शून्य;
पूर्ण

व्योम cxgbi_hbas_हटाओ(काष्ठा cxgbi_device *cdev)
अणु
	पूर्णांक i;
	काष्ठा cxgbi_hba *chba;

	log_debug(1 << CXGBI_DBG_DEV,
		"cdev 0x%p, p#%u.\n", cdev, cdev->nports);

	क्रम (i = 0; i < cdev->nports; i++) अणु
		chba = cdev->hbas[i];
		अगर (chba) अणु
			cdev->hbas[i] = शून्य;
			iscsi_host_हटाओ(chba->shost);
			pci_dev_put(cdev->pdev);
			iscsi_host_मुक्त(chba->shost);
		पूर्ण
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(cxgbi_hbas_हटाओ);

पूर्णांक cxgbi_hbas_add(काष्ठा cxgbi_device *cdev, u64 max_lun,
		अचिन्हित पूर्णांक max_id, काष्ठा scsi_host_ढाँचा *sht,
		काष्ठा scsi_transport_ढाँचा *stt)
अणु
	काष्ठा cxgbi_hba *chba;
	काष्ठा Scsi_Host *shost;
	पूर्णांक i, err;

	log_debug(1 << CXGBI_DBG_DEV, "cdev 0x%p, p#%u.\n", cdev, cdev->nports);

	क्रम (i = 0; i < cdev->nports; i++) अणु
		shost = iscsi_host_alloc(sht, माप(*chba), 1);
		अगर (!shost) अणु
			pr_info("0x%p, p%d, %s, host alloc failed.\n",
				cdev, i, cdev->ports[i]->name);
			err = -ENOMEM;
			जाओ err_out;
		पूर्ण

		shost->transportt = stt;
		shost->max_lun = max_lun;
		shost->max_id = max_id;
		shost->max_channel = 0;
		shost->max_cmd_len = SCSI_MAX_VARLEN_CDB_SIZE;

		chba = iscsi_host_priv(shost);
		chba->cdev = cdev;
		chba->ndev = cdev->ports[i];
		chba->shost = shost;

		shost->can_queue = sht->can_queue - ISCSI_MGMT_CMDS_MAX;

		log_debug(1 << CXGBI_DBG_DEV,
			"cdev 0x%p, p#%d %s: chba 0x%p.\n",
			cdev, i, cdev->ports[i]->name, chba);

		pci_dev_get(cdev->pdev);
		err = iscsi_host_add(shost, &cdev->pdev->dev);
		अगर (err) अणु
			pr_info("cdev 0x%p, p#%d %s, host add failed.\n",
				cdev, i, cdev->ports[i]->name);
			pci_dev_put(cdev->pdev);
			scsi_host_put(shost);
			जाओ  err_out;
		पूर्ण

		cdev->hbas[i] = chba;
	पूर्ण

	वापस 0;

err_out:
	cxgbi_hbas_हटाओ(cdev);
	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(cxgbi_hbas_add);

/*
 * iSCSI offload
 *
 * - source port management
 *   To find a मुक्त source port in the port allocation map we use a very simple
 *   rotor scheme to look क्रम the next मुक्त port.
 *
 *   If a source port has been specअगरied make sure that it करोesn't collide with
 *   our normal source port allocation map.  If it's outside the range of our
 *   allocation/deallocation scheme just let them use it.
 *
 *   If the source port is outside our allocation range, the caller is
 *   responsible क्रम keeping track of their port usage.
 */

अटल काष्ठा cxgbi_sock *find_sock_on_port(काष्ठा cxgbi_device *cdev,
					    अचिन्हित अक्षर port_id)
अणु
	काष्ठा cxgbi_ports_map *pmap = &cdev->pmap;
	अचिन्हित पूर्णांक i;
	अचिन्हित पूर्णांक used;

	अगर (!pmap->max_connect || !pmap->used)
		वापस शून्य;

	spin_lock_bh(&pmap->lock);
	used = pmap->used;
	क्रम (i = 0; used && i < pmap->max_connect; i++) अणु
		काष्ठा cxgbi_sock *csk = pmap->port_csk[i];

		अगर (csk) अणु
			अगर (csk->port_id == port_id) अणु
				spin_unlock_bh(&pmap->lock);
				वापस csk;
			पूर्ण
			used--;
		पूर्ण
	पूर्ण
	spin_unlock_bh(&pmap->lock);

	वापस शून्य;
पूर्ण

अटल पूर्णांक sock_get_port(काष्ठा cxgbi_sock *csk)
अणु
	काष्ठा cxgbi_device *cdev = csk->cdev;
	काष्ठा cxgbi_ports_map *pmap = &cdev->pmap;
	अचिन्हित पूर्णांक start;
	पूर्णांक idx;
	__be16 *port;

	अगर (!pmap->max_connect) अणु
		pr_err("cdev 0x%p, p#%u %s, NO port map.\n",
			   cdev, csk->port_id, cdev->ports[csk->port_id]->name);
		वापस -EADDRNOTAVAIL;
	पूर्ण

	अगर (csk->csk_family == AF_INET)
		port = &csk->saddr.sin_port;
	अन्यथा /* ipv6 */
		port = &csk->saddr6.sin6_port;

	अगर (*port) अणु
		pr_err("source port NON-ZERO %u.\n",
			ntohs(*port));
		वापस -EADDRINUSE;
	पूर्ण

	spin_lock_bh(&pmap->lock);
	अगर (pmap->used >= pmap->max_connect) अणु
		spin_unlock_bh(&pmap->lock);
		pr_info("cdev 0x%p, p#%u %s, ALL ports used.\n",
			cdev, csk->port_id, cdev->ports[csk->port_id]->name);
		वापस -EADDRNOTAVAIL;
	पूर्ण

	start = idx = pmap->next;
	करो अणु
		अगर (++idx >= pmap->max_connect)
			idx = 0;
		अगर (!pmap->port_csk[idx]) अणु
			pmap->used++;
			*port = htons(pmap->sport_base + idx);
			pmap->next = idx;
			pmap->port_csk[idx] = csk;
			spin_unlock_bh(&pmap->lock);
			cxgbi_sock_get(csk);
			log_debug(1 << CXGBI_DBG_SOCK,
				"cdev 0x%p, p#%u %s, p %u, %u.\n",
				cdev, csk->port_id,
				cdev->ports[csk->port_id]->name,
				pmap->sport_base + idx, pmap->next);
			वापस 0;
		पूर्ण
	पूर्ण जबतक (idx != start);
	spin_unlock_bh(&pmap->lock);

	/* should not happen */
	pr_warn("cdev 0x%p, p#%u %s, next %u?\n",
		cdev, csk->port_id, cdev->ports[csk->port_id]->name,
		pmap->next);
	वापस -EADDRNOTAVAIL;
पूर्ण

अटल व्योम sock_put_port(काष्ठा cxgbi_sock *csk)
अणु
	काष्ठा cxgbi_device *cdev = csk->cdev;
	काष्ठा cxgbi_ports_map *pmap = &cdev->pmap;
	__be16 *port;

	अगर (csk->csk_family == AF_INET)
		port = &csk->saddr.sin_port;
	अन्यथा /* ipv6 */
		port = &csk->saddr6.sin6_port;

	अगर (*port) अणु
		पूर्णांक idx = ntohs(*port) - pmap->sport_base;

		*port = 0;
		अगर (idx < 0 || idx >= pmap->max_connect) अणु
			pr_err("cdev 0x%p, p#%u %s, port %u OOR.\n",
				cdev, csk->port_id,
				cdev->ports[csk->port_id]->name,
				ntohs(*port));
			वापस;
		पूर्ण

		spin_lock_bh(&pmap->lock);
		pmap->port_csk[idx] = शून्य;
		pmap->used--;
		spin_unlock_bh(&pmap->lock);

		log_debug(1 << CXGBI_DBG_SOCK,
			"cdev 0x%p, p#%u %s, release %u.\n",
			cdev, csk->port_id, cdev->ports[csk->port_id]->name,
			pmap->sport_base + idx);

		cxgbi_sock_put(csk);
	पूर्ण
पूर्ण

/*
 * iscsi tcp connection
 */
व्योम cxgbi_sock_मुक्त_cpl_skbs(काष्ठा cxgbi_sock *csk)
अणु
	अगर (csk->cpl_बंद) अणु
		kमुक्त_skb(csk->cpl_बंद);
		csk->cpl_बंद = शून्य;
	पूर्ण
	अगर (csk->cpl_पात_req) अणु
		kमुक्त_skb(csk->cpl_पात_req);
		csk->cpl_पात_req = शून्य;
	पूर्ण
	अगर (csk->cpl_पात_rpl) अणु
		kमुक्त_skb(csk->cpl_पात_rpl);
		csk->cpl_पात_rpl = शून्य;
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(cxgbi_sock_मुक्त_cpl_skbs);

अटल काष्ठा cxgbi_sock *cxgbi_sock_create(काष्ठा cxgbi_device *cdev)
अणु
	काष्ठा cxgbi_sock *csk = kzalloc(माप(*csk), GFP_NOIO);

	अगर (!csk) अणु
		pr_info("alloc csk %zu failed.\n", माप(*csk));
		वापस शून्य;
	पूर्ण

	अगर (cdev->csk_alloc_cpls(csk) < 0) अणु
		pr_info("csk 0x%p, alloc cpls failed.\n", csk);
		kमुक्त(csk);
		वापस शून्य;
	पूर्ण

	spin_lock_init(&csk->lock);
	kref_init(&csk->refcnt);
	skb_queue_head_init(&csk->receive_queue);
	skb_queue_head_init(&csk->ग_लिखो_queue);
	समयr_setup(&csk->retry_समयr, शून्य, 0);
	init_completion(&csk->cmpl);
	rwlock_init(&csk->callback_lock);
	csk->cdev = cdev;
	csk->flags = 0;
	cxgbi_sock_set_state(csk, CTP_CLOSED);

	log_debug(1 << CXGBI_DBG_SOCK, "cdev 0x%p, new csk 0x%p.\n", cdev, csk);

	वापस csk;
पूर्ण

अटल काष्ठा rtable *find_route_ipv4(काष्ठा flowi4 *fl4,
				      __be32 saddr, __be32 daddr,
				      __be16 sport, __be16 dport, u8 tos,
				      पूर्णांक अगरindex)
अणु
	काष्ठा rtable *rt;

	rt = ip_route_output_ports(&init_net, fl4, शून्य, daddr, saddr,
				   dport, sport, IPPROTO_TCP, tos, अगरindex);
	अगर (IS_ERR(rt))
		वापस शून्य;

	वापस rt;
पूर्ण

अटल काष्ठा cxgbi_sock *
cxgbi_check_route(काष्ठा sockaddr *dst_addr, पूर्णांक अगरindex)
अणु
	काष्ठा sockaddr_in *daddr = (काष्ठा sockaddr_in *)dst_addr;
	काष्ठा dst_entry *dst;
	काष्ठा net_device *ndev;
	काष्ठा cxgbi_device *cdev;
	काष्ठा rtable *rt = शून्य;
	काष्ठा neighbour *n;
	काष्ठा flowi4 fl4;
	काष्ठा cxgbi_sock *csk = शून्य;
	अचिन्हित पूर्णांक mtu = 0;
	पूर्णांक port = 0xFFFF;
	पूर्णांक err = 0;

	rt = find_route_ipv4(&fl4, 0, daddr->sin_addr.s_addr, 0,
			     daddr->sin_port, 0, अगरindex);
	अगर (!rt) अणु
		pr_info("no route to ipv4 0x%x, port %u.\n",
			be32_to_cpu(daddr->sin_addr.s_addr),
			be16_to_cpu(daddr->sin_port));
		err = -ENETUNREACH;
		जाओ err_out;
	पूर्ण
	dst = &rt->dst;
	n = dst_neigh_lookup(dst, &daddr->sin_addr.s_addr);
	अगर (!n) अणु
		err = -ENODEV;
		जाओ rel_rt;
	पूर्ण
	ndev = n->dev;

	अगर (rt->rt_flags & (RTCF_MULTICAST | RTCF_BROADCAST)) अणु
		pr_info("multi-cast route %pI4, port %u, dev %s.\n",
			&daddr->sin_addr.s_addr, ntohs(daddr->sin_port),
			ndev->name);
		err = -ENETUNREACH;
		जाओ rel_neigh;
	पूर्ण

	अगर (ndev->flags & IFF_LOOPBACK) अणु
		ndev = ip_dev_find(&init_net, daddr->sin_addr.s_addr);
		अगर (!ndev) अणु
			err = -ENETUNREACH;
			जाओ rel_neigh;
		पूर्ण
		mtu = ndev->mtu;
		pr_info("rt dev %s, loopback -> %s, mtu %u.\n",
			n->dev->name, ndev->name, mtu);
	पूर्ण

	अगर (!(ndev->flags & IFF_UP) || !netअगर_carrier_ok(ndev)) अणु
		pr_info("%s interface not up.\n", ndev->name);
		err = -ENETDOWN;
		जाओ rel_neigh;
	पूर्ण

	cdev = cxgbi_device_find_by_netdev(ndev, &port);
	अगर (!cdev)
		cdev = cxgbi_device_find_by_mac(ndev, &port);
	अगर (!cdev) अणु
		pr_info("dst %pI4, %s, NOT cxgbi device.\n",
			&daddr->sin_addr.s_addr, ndev->name);
		err = -ENETUNREACH;
		जाओ rel_neigh;
	पूर्ण
	log_debug(1 << CXGBI_DBG_SOCK,
		"route to %pI4 :%u, ndev p#%d,%s, cdev 0x%p.\n",
		&daddr->sin_addr.s_addr, ntohs(daddr->sin_port),
			   port, ndev->name, cdev);

	csk = cxgbi_sock_create(cdev);
	अगर (!csk) अणु
		err = -ENOMEM;
		जाओ rel_neigh;
	पूर्ण
	csk->cdev = cdev;
	csk->port_id = port;
	csk->mtu = mtu;
	csk->dst = dst;

	csk->csk_family = AF_INET;
	csk->daddr.sin_addr.s_addr = daddr->sin_addr.s_addr;
	csk->daddr.sin_port = daddr->sin_port;
	csk->daddr.sin_family = daddr->sin_family;
	csk->saddr.sin_family = daddr->sin_family;
	csk->saddr.sin_addr.s_addr = fl4.saddr;
	neigh_release(n);

	वापस csk;

rel_neigh:
	neigh_release(n);

rel_rt:
	ip_rt_put(rt);
err_out:
	वापस ERR_PTR(err);
पूर्ण

#अगर IS_ENABLED(CONFIG_IPV6)
अटल काष्ठा rt6_info *find_route_ipv6(स्थिर काष्ठा in6_addr *saddr,
					स्थिर काष्ठा in6_addr *daddr,
					पूर्णांक अगरindex)
अणु
	काष्ठा flowi6 fl;

	स_रखो(&fl, 0, माप(fl));
	fl.flowi6_oअगर = अगरindex;
	अगर (saddr)
		स_नकल(&fl.saddr, saddr, माप(काष्ठा in6_addr));
	अगर (daddr)
		स_नकल(&fl.daddr, daddr, माप(काष्ठा in6_addr));
	वापस (काष्ठा rt6_info *)ip6_route_output(&init_net, शून्य, &fl);
पूर्ण

अटल काष्ठा cxgbi_sock *
cxgbi_check_route6(काष्ठा sockaddr *dst_addr, पूर्णांक अगरindex)
अणु
	काष्ठा sockaddr_in6 *daddr6 = (काष्ठा sockaddr_in6 *)dst_addr;
	काष्ठा dst_entry *dst;
	काष्ठा net_device *ndev;
	काष्ठा cxgbi_device *cdev;
	काष्ठा rt6_info *rt = शून्य;
	काष्ठा neighbour *n;
	काष्ठा in6_addr pref_saddr;
	काष्ठा cxgbi_sock *csk = शून्य;
	अचिन्हित पूर्णांक mtu = 0;
	पूर्णांक port = 0xFFFF;
	पूर्णांक err = 0;

	rt = find_route_ipv6(शून्य, &daddr6->sin6_addr, अगरindex);

	अगर (!rt) अणु
		pr_info("no route to ipv6 %pI6 port %u\n",
			daddr6->sin6_addr.s6_addr,
			be16_to_cpu(daddr6->sin6_port));
		err = -ENETUNREACH;
		जाओ err_out;
	पूर्ण

	dst = &rt->dst;

	n = dst_neigh_lookup(dst, &daddr6->sin6_addr);

	अगर (!n) अणु
		pr_info("%pI6, port %u, dst no neighbour.\n",
			daddr6->sin6_addr.s6_addr,
			be16_to_cpu(daddr6->sin6_port));
		err = -ENETUNREACH;
		जाओ rel_rt;
	पूर्ण
	ndev = n->dev;

	अगर (!(ndev->flags & IFF_UP) || !netअगर_carrier_ok(ndev)) अणु
		pr_info("%s interface not up.\n", ndev->name);
		err = -ENETDOWN;
		जाओ rel_rt;
	पूर्ण

	अगर (ipv6_addr_is_multicast(&daddr6->sin6_addr)) अणु
		pr_info("multi-cast route %pI6 port %u, dev %s.\n",
			daddr6->sin6_addr.s6_addr,
			ntohs(daddr6->sin6_port), ndev->name);
		err = -ENETUNREACH;
		जाओ rel_rt;
	पूर्ण

	cdev = cxgbi_device_find_by_netdev(ndev, &port);
	अगर (!cdev)
		cdev = cxgbi_device_find_by_mac(ndev, &port);
	अगर (!cdev) अणु
		pr_info("dst %pI6 %s, NOT cxgbi device.\n",
			daddr6->sin6_addr.s6_addr, ndev->name);
		err = -ENETUNREACH;
		जाओ rel_rt;
	पूर्ण
	log_debug(1 << CXGBI_DBG_SOCK,
		  "route to %pI6 :%u, ndev p#%d,%s, cdev 0x%p.\n",
		  daddr6->sin6_addr.s6_addr, ntohs(daddr6->sin6_port), port,
		  ndev->name, cdev);

	csk = cxgbi_sock_create(cdev);
	अगर (!csk) अणु
		err = -ENOMEM;
		जाओ rel_rt;
	पूर्ण
	csk->cdev = cdev;
	csk->port_id = port;
	csk->mtu = mtu;
	csk->dst = dst;

	rt6_get_prefsrc(rt, &pref_saddr);
	अगर (ipv6_addr_any(&pref_saddr)) अणु
		काष्ठा inet6_dev *idev = ip6_dst_idev((काष्ठा dst_entry *)rt);

		err = ipv6_dev_get_saddr(&init_net, idev ? idev->dev : शून्य,
					 &daddr6->sin6_addr, 0, &pref_saddr);
		अगर (err) अणु
			pr_info("failed to get source address to reach %pI6\n",
				&daddr6->sin6_addr);
			जाओ rel_rt;
		पूर्ण
	पूर्ण

	csk->csk_family = AF_INET6;
	csk->daddr6.sin6_addr = daddr6->sin6_addr;
	csk->daddr6.sin6_port = daddr6->sin6_port;
	csk->daddr6.sin6_family = daddr6->sin6_family;
	csk->saddr6.sin6_family = daddr6->sin6_family;
	csk->saddr6.sin6_addr = pref_saddr;

	neigh_release(n);
	वापस csk;

rel_rt:
	अगर (n)
		neigh_release(n);

	ip6_rt_put(rt);
	अगर (csk)
		cxgbi_sock_बंदd(csk);
err_out:
	वापस ERR_PTR(err);
पूर्ण
#पूर्ण_अगर /* IS_ENABLED(CONFIG_IPV6) */

व्योम cxgbi_sock_established(काष्ठा cxgbi_sock *csk, अचिन्हित पूर्णांक snd_isn,
			अचिन्हित पूर्णांक opt)
अणु
	csk->ग_लिखो_seq = csk->snd_nxt = csk->snd_una = snd_isn;
	dst_confirm(csk->dst);
	smp_mb();
	cxgbi_sock_set_state(csk, CTP_ESTABLISHED);
पूर्ण
EXPORT_SYMBOL_GPL(cxgbi_sock_established);

अटल व्योम cxgbi_inक्रमm_iscsi_conn_closing(काष्ठा cxgbi_sock *csk)
अणु
	log_debug(1 << CXGBI_DBG_SOCK,
		"csk 0x%p, state %u, flags 0x%lx, conn 0x%p.\n",
		csk, csk->state, csk->flags, csk->user_data);

	अगर (csk->state != CTP_ESTABLISHED) अणु
		पढ़ो_lock_bh(&csk->callback_lock);
		अगर (csk->user_data)
			iscsi_conn_failure(csk->user_data,
					ISCSI_ERR_TCP_CONN_CLOSE);
		पढ़ो_unlock_bh(&csk->callback_lock);
	पूर्ण
पूर्ण

व्योम cxgbi_sock_बंदd(काष्ठा cxgbi_sock *csk)
अणु
	log_debug(1 << CXGBI_DBG_SOCK, "csk 0x%p,%u,0x%lx,%u.\n",
		csk, (csk)->state, (csk)->flags, (csk)->tid);
	cxgbi_sock_set_flag(csk, CTPF_ACTIVE_CLOSE_NEEDED);
	अगर (csk->state == CTP_ACTIVE_OPEN || csk->state == CTP_CLOSED)
		वापस;
	अगर (csk->saddr.sin_port)
		sock_put_port(csk);
	अगर (csk->dst)
		dst_release(csk->dst);
	csk->cdev->csk_release_offload_resources(csk);
	cxgbi_sock_set_state(csk, CTP_CLOSED);
	cxgbi_inक्रमm_iscsi_conn_closing(csk);
	cxgbi_sock_put(csk);
पूर्ण
EXPORT_SYMBOL_GPL(cxgbi_sock_बंदd);

अटल व्योम need_active_बंद(काष्ठा cxgbi_sock *csk)
अणु
	पूर्णांक data_lost;
	पूर्णांक बंद_req = 0;

	log_debug(1 << CXGBI_DBG_SOCK, "csk 0x%p,%u,0x%lx,%u.\n",
		csk, (csk)->state, (csk)->flags, (csk)->tid);
	spin_lock_bh(&csk->lock);
	अगर (csk->dst)
		dst_confirm(csk->dst);
	data_lost = skb_queue_len(&csk->receive_queue);
	__skb_queue_purge(&csk->receive_queue);

	अगर (csk->state == CTP_ACTIVE_OPEN)
		cxgbi_sock_set_flag(csk, CTPF_ACTIVE_CLOSE_NEEDED);
	अन्यथा अगर (csk->state == CTP_ESTABLISHED) अणु
		बंद_req = 1;
		cxgbi_sock_set_state(csk, CTP_ACTIVE_CLOSE);
	पूर्ण अन्यथा अगर (csk->state == CTP_PASSIVE_CLOSE) अणु
		बंद_req = 1;
		cxgbi_sock_set_state(csk, CTP_CLOSE_WAIT_2);
	पूर्ण

	अगर (बंद_req) अणु
		अगर (!cxgbi_sock_flag(csk, CTPF_LOGOUT_RSP_RCVD) ||
		    data_lost)
			csk->cdev->csk_send_पात_req(csk);
		अन्यथा
			csk->cdev->csk_send_बंद_req(csk);
	पूर्ण

	spin_unlock_bh(&csk->lock);
पूर्ण

व्योम cxgbi_sock_fail_act_खोलो(काष्ठा cxgbi_sock *csk, पूर्णांक त्रुटि_सं)
अणु
	pr_info("csk 0x%p,%u,%lx, %pI4:%u-%pI4:%u, err %d.\n",
			csk, csk->state, csk->flags,
			&csk->saddr.sin_addr.s_addr, csk->saddr.sin_port,
			&csk->daddr.sin_addr.s_addr, csk->daddr.sin_port,
			त्रुटि_सं);

	cxgbi_sock_set_state(csk, CTP_CONNECTING);
	csk->err = त्रुटि_सं;
	cxgbi_sock_बंदd(csk);
पूर्ण
EXPORT_SYMBOL_GPL(cxgbi_sock_fail_act_खोलो);

व्योम cxgbi_sock_act_खोलो_req_arp_failure(व्योम *handle, काष्ठा sk_buff *skb)
अणु
	काष्ठा cxgbi_sock *csk = (काष्ठा cxgbi_sock *)skb->sk;
	काष्ठा module *owner = csk->cdev->owner;

	log_debug(1 << CXGBI_DBG_SOCK, "csk 0x%p,%u,0x%lx,%u.\n",
		csk, (csk)->state, (csk)->flags, (csk)->tid);
	cxgbi_sock_get(csk);
	spin_lock_bh(&csk->lock);
	अगर (csk->state == CTP_ACTIVE_OPEN)
		cxgbi_sock_fail_act_खोलो(csk, -EHOSTUNREACH);
	spin_unlock_bh(&csk->lock);
	cxgbi_sock_put(csk);
	__kमुक्त_skb(skb);

	module_put(owner);
पूर्ण
EXPORT_SYMBOL_GPL(cxgbi_sock_act_खोलो_req_arp_failure);

व्योम cxgbi_sock_rcv_पात_rpl(काष्ठा cxgbi_sock *csk)
अणु
	cxgbi_sock_get(csk);
	spin_lock_bh(&csk->lock);

	cxgbi_sock_set_flag(csk, CTPF_ABORT_RPL_RCVD);
	अगर (cxgbi_sock_flag(csk, CTPF_ABORT_RPL_PENDING)) अणु
		cxgbi_sock_clear_flag(csk, CTPF_ABORT_RPL_PENDING);
		अगर (cxgbi_sock_flag(csk, CTPF_ABORT_REQ_RCVD))
			pr_err("csk 0x%p,%u,0x%lx,%u,ABT_RPL_RSS.\n",
			       csk, csk->state, csk->flags, csk->tid);
		cxgbi_sock_बंदd(csk);
	पूर्ण

	spin_unlock_bh(&csk->lock);
	cxgbi_sock_put(csk);
पूर्ण
EXPORT_SYMBOL_GPL(cxgbi_sock_rcv_पात_rpl);

व्योम cxgbi_sock_rcv_peer_बंद(काष्ठा cxgbi_sock *csk)
अणु
	log_debug(1 << CXGBI_DBG_SOCK, "csk 0x%p,%u,0x%lx,%u.\n",
		csk, (csk)->state, (csk)->flags, (csk)->tid);
	cxgbi_sock_get(csk);
	spin_lock_bh(&csk->lock);

	अगर (cxgbi_sock_flag(csk, CTPF_ABORT_RPL_PENDING))
		जाओ करोne;

	चयन (csk->state) अणु
	हाल CTP_ESTABLISHED:
		cxgbi_sock_set_state(csk, CTP_PASSIVE_CLOSE);
		अवरोध;
	हाल CTP_ACTIVE_CLOSE:
		cxgbi_sock_set_state(csk, CTP_CLOSE_WAIT_2);
		अवरोध;
	हाल CTP_CLOSE_WAIT_1:
		cxgbi_sock_बंदd(csk);
		अवरोध;
	हाल CTP_ABORTING:
		अवरोध;
	शेष:
		pr_err("csk 0x%p,%u,0x%lx,%u, bad state.\n",
			csk, csk->state, csk->flags, csk->tid);
	पूर्ण
	cxgbi_inक्रमm_iscsi_conn_closing(csk);
करोne:
	spin_unlock_bh(&csk->lock);
	cxgbi_sock_put(csk);
पूर्ण
EXPORT_SYMBOL_GPL(cxgbi_sock_rcv_peer_बंद);

व्योम cxgbi_sock_rcv_बंद_conn_rpl(काष्ठा cxgbi_sock *csk, u32 snd_nxt)
अणु
	log_debug(1 << CXGBI_DBG_SOCK, "csk 0x%p,%u,0x%lx,%u.\n",
		csk, (csk)->state, (csk)->flags, (csk)->tid);
	cxgbi_sock_get(csk);
	spin_lock_bh(&csk->lock);

	csk->snd_una = snd_nxt - 1;
	अगर (cxgbi_sock_flag(csk, CTPF_ABORT_RPL_PENDING))
		जाओ करोne;

	चयन (csk->state) अणु
	हाल CTP_ACTIVE_CLOSE:
		cxgbi_sock_set_state(csk, CTP_CLOSE_WAIT_1);
		अवरोध;
	हाल CTP_CLOSE_WAIT_1:
	हाल CTP_CLOSE_WAIT_2:
		cxgbi_sock_बंदd(csk);
		अवरोध;
	हाल CTP_ABORTING:
		अवरोध;
	शेष:
		pr_err("csk 0x%p,%u,0x%lx,%u, bad state.\n",
			csk, csk->state, csk->flags, csk->tid);
	पूर्ण
करोne:
	spin_unlock_bh(&csk->lock);
	cxgbi_sock_put(csk);
पूर्ण
EXPORT_SYMBOL_GPL(cxgbi_sock_rcv_बंद_conn_rpl);

व्योम cxgbi_sock_rcv_wr_ack(काष्ठा cxgbi_sock *csk, अचिन्हित पूर्णांक credits,
			   अचिन्हित पूर्णांक snd_una, पूर्णांक seq_chk)
अणु
	log_debug(1 << CXGBI_DBG_TOE | 1 << CXGBI_DBG_SOCK,
			"csk 0x%p,%u,0x%lx,%u, cr %u,%u+%u, snd_una %u,%d.\n",
			csk, csk->state, csk->flags, csk->tid, credits,
			csk->wr_cred, csk->wr_una_cred, snd_una, seq_chk);

	spin_lock_bh(&csk->lock);

	csk->wr_cred += credits;
	अगर (csk->wr_una_cred > csk->wr_max_cred - csk->wr_cred)
		csk->wr_una_cred = csk->wr_max_cred - csk->wr_cred;

	जबतक (credits) अणु
		काष्ठा sk_buff *p = cxgbi_sock_peek_wr(csk);

		अगर (unlikely(!p)) अणु
			pr_err("csk 0x%p,%u,0x%lx,%u, cr %u,%u+%u, empty.\n",
				csk, csk->state, csk->flags, csk->tid, credits,
				csk->wr_cred, csk->wr_una_cred);
			अवरोध;
		पूर्ण

		अगर (unlikely(credits < p->csum)) अणु
			pr_warn("csk 0x%p,%u,0x%lx,%u, cr %u,%u+%u, < %u.\n",
				csk, csk->state, csk->flags, csk->tid,
				credits, csk->wr_cred, csk->wr_una_cred,
				p->csum);
			p->csum -= credits;
			अवरोध;
		पूर्ण अन्यथा अणु
			cxgbi_sock_dequeue_wr(csk);
			credits -= p->csum;
			kमुक्त_skb(p);
		पूर्ण
	पूर्ण

	cxgbi_sock_check_wr_invariants(csk);

	अगर (seq_chk) अणु
		अगर (unlikely(beक्रमe(snd_una, csk->snd_una))) अणु
			pr_warn("csk 0x%p,%u,0x%lx,%u, snd_una %u/%u.",
				csk, csk->state, csk->flags, csk->tid, snd_una,
				csk->snd_una);
			जाओ करोne;
		पूर्ण

		अगर (csk->snd_una != snd_una) अणु
			csk->snd_una = snd_una;
			dst_confirm(csk->dst);
		पूर्ण
	पूर्ण

	अगर (skb_queue_len(&csk->ग_लिखो_queue)) अणु
		अगर (csk->cdev->csk_push_tx_frames(csk, 0))
			cxgbi_conn_tx_खोलो(csk);
	पूर्ण अन्यथा
		cxgbi_conn_tx_खोलो(csk);
करोne:
	spin_unlock_bh(&csk->lock);
पूर्ण
EXPORT_SYMBOL_GPL(cxgbi_sock_rcv_wr_ack);

अटल अचिन्हित पूर्णांक cxgbi_sock_find_best_mtu(काष्ठा cxgbi_sock *csk,
					     अचिन्हित लघु mtu)
अणु
	पूर्णांक i = 0;

	जबतक (i < csk->cdev->nmtus - 1 && csk->cdev->mtus[i + 1] <= mtu)
		++i;

	वापस i;
पूर्ण

अचिन्हित पूर्णांक cxgbi_sock_select_mss(काष्ठा cxgbi_sock *csk, अचिन्हित पूर्णांक pmtu)
अणु
	अचिन्हित पूर्णांक idx;
	काष्ठा dst_entry *dst = csk->dst;

	csk->advmss = dst_metric_advmss(dst);

	अगर (csk->advmss > pmtu - 40)
		csk->advmss = pmtu - 40;
	अगर (csk->advmss < csk->cdev->mtus[0] - 40)
		csk->advmss = csk->cdev->mtus[0] - 40;
	idx = cxgbi_sock_find_best_mtu(csk, csk->advmss + 40);

	वापस idx;
पूर्ण
EXPORT_SYMBOL_GPL(cxgbi_sock_select_mss);

व्योम cxgbi_sock_skb_entail(काष्ठा cxgbi_sock *csk, काष्ठा sk_buff *skb)
अणु
	cxgbi_skcb_tcp_seq(skb) = csk->ग_लिखो_seq;
	__skb_queue_tail(&csk->ग_लिखो_queue, skb);
पूर्ण
EXPORT_SYMBOL_GPL(cxgbi_sock_skb_entail);

व्योम cxgbi_sock_purge_wr_queue(काष्ठा cxgbi_sock *csk)
अणु
	काष्ठा sk_buff *skb;

	जबतक ((skb = cxgbi_sock_dequeue_wr(csk)) != शून्य)
		kमुक्त_skb(skb);
पूर्ण
EXPORT_SYMBOL_GPL(cxgbi_sock_purge_wr_queue);

व्योम cxgbi_sock_check_wr_invariants(स्थिर काष्ठा cxgbi_sock *csk)
अणु
	पूर्णांक pending = cxgbi_sock_count_pending_wrs(csk);

	अगर (unlikely(csk->wr_cred + pending != csk->wr_max_cred))
		pr_err("csk 0x%p, tid %u, credit %u + %u != %u.\n",
			csk, csk->tid, csk->wr_cred, pending, csk->wr_max_cred);
पूर्ण
EXPORT_SYMBOL_GPL(cxgbi_sock_check_wr_invariants);

अटल अंतरभूत व्योम
scmd_get_params(काष्ठा scsi_cmnd *sc, काष्ठा scatterlist **sgl,
		अचिन्हित पूर्णांक *sgcnt, अचिन्हित पूर्णांक *dlen,
		अचिन्हित पूर्णांक prot)
अणु
	काष्ठा scsi_data_buffer *sdb = prot ? scsi_prot(sc) : &sc->sdb;

	*sgl = sdb->table.sgl;
	*sgcnt = sdb->table.nents;
	*dlen = sdb->length;
	/* Caution: क्रम protection sdb, sdb->length is invalid */
पूर्ण

व्योम cxgbi_ddp_set_one_ppod(काष्ठा cxgbi_pagepod *ppod,
			    काष्ठा cxgbi_task_tag_info *ttinfo,
			    काष्ठा scatterlist **sg_pp, अचिन्हित पूर्णांक *sg_off)
अणु
	काष्ठा scatterlist *sg = sg_pp ? *sg_pp : शून्य;
	अचिन्हित पूर्णांक offset = sg_off ? *sg_off : 0;
	dma_addr_t addr = 0UL;
	अचिन्हित पूर्णांक len = 0;
	पूर्णांक i;

	स_नकल(ppod, &ttinfo->hdr, माप(काष्ठा cxgbi_pagepod_hdr));

	अगर (sg) अणु
		addr = sg_dma_address(sg);
		len = sg_dma_len(sg);
	पूर्ण

	क्रम (i = 0; i < PPOD_PAGES_MAX; i++) अणु
		अगर (sg) अणु
			ppod->addr[i] = cpu_to_be64(addr + offset);
			offset += PAGE_SIZE;
			अगर (offset == (len + sg->offset)) अणु
				offset = 0;
				sg = sg_next(sg);
				अगर (sg) अणु
					addr = sg_dma_address(sg);
					len = sg_dma_len(sg);
				पूर्ण
			पूर्ण
		पूर्ण अन्यथा अणु
			ppod->addr[i] = 0ULL;
		पूर्ण
	पूर्ण

	/*
	 * the fअगरth address needs to be repeated in the next ppod, so करो
	 * not move sg
	 */
	अगर (sg_pp) अणु
		*sg_pp = sg;
		*sg_off = offset;
	पूर्ण

	अगर (offset == len) अणु
		offset = 0;
		sg = sg_next(sg);
		अगर (sg) अणु
			addr = sg_dma_address(sg);
			len = sg_dma_len(sg);
		पूर्ण
	पूर्ण
	ppod->addr[i] = sg ? cpu_to_be64(addr + offset) : 0ULL;
पूर्ण
EXPORT_SYMBOL_GPL(cxgbi_ddp_set_one_ppod);

/*
 * APIs पूर्णांकeracting with खोलो-iscsi libraries
 */

पूर्णांक cxgbi_ddp_ppm_setup(व्योम **ppm_pp, काष्ठा cxgbi_device *cdev,
			काष्ठा cxgbi_tag_क्रमmat *tक्रमmat,
			अचिन्हित पूर्णांक iscsi_size, अचिन्हित पूर्णांक llimit,
			अचिन्हित पूर्णांक start, अचिन्हित पूर्णांक rsvd_factor,
			अचिन्हित पूर्णांक edram_start, अचिन्हित पूर्णांक edram_size)
अणु
	पूर्णांक err = cxgbi_ppm_init(ppm_pp, cdev->ports[0], cdev->pdev,
				cdev->lldev, tक्रमmat, iscsi_size, llimit, start,
				rsvd_factor, edram_start, edram_size);

	अगर (err >= 0) अणु
		काष्ठा cxgbi_ppm *ppm = (काष्ठा cxgbi_ppm *)(*ppm_pp);

		अगर (ppm->ppmax < 1024 ||
		    ppm->tक्रमmat.pgsz_idx_dflt >= DDP_PGIDX_MAX)
			cdev->flags |= CXGBI_FLAG_DDP_OFF;
		err = 0;
	पूर्ण अन्यथा अणु
		cdev->flags |= CXGBI_FLAG_DDP_OFF;
	पूर्ण

	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(cxgbi_ddp_ppm_setup);

अटल पूर्णांक cxgbi_ddp_sgl_check(काष्ठा scatterlist *sgl, पूर्णांक nents)
अणु
	पूर्णांक i;
	पूर्णांक last_sgidx = nents - 1;
	काष्ठा scatterlist *sg = sgl;

	क्रम (i = 0; i < nents; i++, sg = sg_next(sg)) अणु
		अचिन्हित पूर्णांक len = sg->length + sg->offset;

		अगर ((sg->offset & 0x3) || (i && sg->offset) ||
		    ((i != last_sgidx) && len != PAGE_SIZE)) अणु
			log_debug(1 << CXGBI_DBG_DDP,
				  "sg %u/%u, %u,%u, not aligned.\n",
				  i, nents, sg->offset, sg->length);
			जाओ err_out;
		पूर्ण
	पूर्ण
	वापस 0;
err_out:
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक cxgbi_ddp_reserve(काष्ठा cxgbi_conn *cconn,
			     काष्ठा cxgbi_task_data *tdata, u32 sw_tag,
			     अचिन्हित पूर्णांक xferlen)
अणु
	काष्ठा cxgbi_sock *csk = cconn->cep->csk;
	काष्ठा cxgbi_device *cdev = csk->cdev;
	काष्ठा cxgbi_ppm *ppm = cdev->cdev2ppm(cdev);
	काष्ठा cxgbi_task_tag_info *ttinfo = &tdata->ttinfo;
	काष्ठा scatterlist *sgl = ttinfo->sgl;
	अचिन्हित पूर्णांक sgcnt = ttinfo->nents;
	अचिन्हित पूर्णांक sg_offset = sgl->offset;
	पूर्णांक err;

	अगर (cdev->flags & CXGBI_FLAG_DDP_OFF) अणु
		log_debug(1 << CXGBI_DBG_DDP,
			  "cdev 0x%p DDP off.\n", cdev);
		वापस -EINVAL;
	पूर्ण

	अगर (!ppm || xferlen < DDP_THRESHOLD || !sgcnt ||
	    ppm->tक्रमmat.pgsz_idx_dflt >= DDP_PGIDX_MAX) अणु
		log_debug(1 << CXGBI_DBG_DDP,
			  "ppm 0x%p, pgidx %u, xfer %u, sgcnt %u, NO ddp.\n",
			  ppm, ppm ? ppm->tक्रमmat.pgsz_idx_dflt : DDP_PGIDX_MAX,
			  xferlen, ttinfo->nents);
		वापस -EINVAL;
	पूर्ण

	/* make sure the buffer is suitable क्रम ddp */
	अगर (cxgbi_ddp_sgl_check(sgl, sgcnt) < 0)
		वापस -EINVAL;

	ttinfo->nr_pages = (xferlen + sgl->offset + (1 << PAGE_SHIFT) - 1) >>
			    PAGE_SHIFT;

	/*
	 * the ddp tag will be used क्रम the itt in the outgoing pdu,
	 * the itt genrated by libiscsi is saved in the ppm and can be
	 * retrieved via the ddp tag
	 */
	err = cxgbi_ppm_ppods_reserve(ppm, ttinfo->nr_pages, 0, &ttinfo->idx,
				      &ttinfo->tag, (अचिन्हित दीर्घ)sw_tag);
	अगर (err < 0) अणु
		cconn->ddp_full++;
		वापस err;
	पूर्ण
	ttinfo->npods = err;

	 /* setup dma from scsi command sgl */
	sgl->offset = 0;
	err = dma_map_sg(&ppm->pdev->dev, sgl, sgcnt, DMA_FROM_DEVICE);
	sgl->offset = sg_offset;
	अगर (err == 0) अणु
		pr_info("%s: 0x%x, xfer %u, sgl %u dma mapping err.\n",
			__func__, sw_tag, xferlen, sgcnt);
		जाओ rel_ppods;
	पूर्ण
	अगर (err != ttinfo->nr_pages) अणु
		log_debug(1 << CXGBI_DBG_DDP,
			  "%s: sw tag 0x%x, xfer %u, sgl %u, dma count %d.\n",
			  __func__, sw_tag, xferlen, sgcnt, err);
	पूर्ण

	ttinfo->flags |= CXGBI_PPOD_INFO_FLAG_MAPPED;
	ttinfo->cid = csk->port_id;

	cxgbi_ppm_make_ppod_hdr(ppm, ttinfo->tag, csk->tid, sgl->offset,
				xferlen, &ttinfo->hdr);

	अगर (cdev->flags & CXGBI_FLAG_USE_PPOD_OFLDQ) अणु
		/* ग_लिखो ppod from xmit_pdu (of iscsi_scsi_command pdu) */
		ttinfo->flags |= CXGBI_PPOD_INFO_FLAG_VALID;
	पूर्ण अन्यथा अणु
		/* ग_लिखो ppod from control queue now */
		err = cdev->csk_ddp_set_map(ppm, csk, ttinfo);
		अगर (err < 0)
			जाओ rel_ppods;
	पूर्ण

	वापस 0;

rel_ppods:
	cxgbi_ppm_ppod_release(ppm, ttinfo->idx);

	अगर (ttinfo->flags & CXGBI_PPOD_INFO_FLAG_MAPPED) अणु
		ttinfo->flags &= ~CXGBI_PPOD_INFO_FLAG_MAPPED;
		dma_unmap_sg(&ppm->pdev->dev, sgl, sgcnt, DMA_FROM_DEVICE);
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल व्योम task_release_itt(काष्ठा iscsi_task *task, itt_t hdr_itt)
अणु
	काष्ठा scsi_cmnd *sc = task->sc;
	काष्ठा iscsi_tcp_conn *tcp_conn = task->conn->dd_data;
	काष्ठा cxgbi_conn *cconn = tcp_conn->dd_data;
	काष्ठा cxgbi_device *cdev = cconn->chba->cdev;
	काष्ठा cxgbi_ppm *ppm = cdev->cdev2ppm(cdev);
	u32 tag = ntohl((__क्रमce u32)hdr_itt);

	log_debug(1 << CXGBI_DBG_DDP,
		  "cdev 0x%p, task 0x%p, release tag 0x%x.\n",
		  cdev, task, tag);
	अगर (sc && sc->sc_data_direction == DMA_FROM_DEVICE &&
	    cxgbi_ppm_is_ddp_tag(ppm, tag)) अणु
		काष्ठा cxgbi_task_data *tdata = iscsi_task_cxgbi_data(task);
		काष्ठा cxgbi_task_tag_info *ttinfo = &tdata->ttinfo;

		अगर (!(cdev->flags & CXGBI_FLAG_USE_PPOD_OFLDQ))
			cdev->csk_ddp_clear_map(cdev, ppm, ttinfo);
		cxgbi_ppm_ppod_release(ppm, ttinfo->idx);
		dma_unmap_sg(&ppm->pdev->dev, ttinfo->sgl, ttinfo->nents,
			     DMA_FROM_DEVICE);
	पूर्ण
पूर्ण

अटल अंतरभूत u32 cxgbi_build_sw_tag(u32 idx, u32 age)
अणु
	/* assume idx and age both are < 0x7FFF (32767) */
	वापस (idx << 16) | age;
पूर्ण

अटल पूर्णांक task_reserve_itt(काष्ठा iscsi_task *task, itt_t *hdr_itt)
अणु
	काष्ठा scsi_cmnd *sc = task->sc;
	काष्ठा iscsi_conn *conn = task->conn;
	काष्ठा iscsi_session *sess = conn->session;
	काष्ठा iscsi_tcp_conn *tcp_conn = conn->dd_data;
	काष्ठा cxgbi_conn *cconn = tcp_conn->dd_data;
	काष्ठा cxgbi_device *cdev = cconn->chba->cdev;
	काष्ठा cxgbi_ppm *ppm = cdev->cdev2ppm(cdev);
	u32 sw_tag = cxgbi_build_sw_tag(task->itt, sess->age);
	u32 tag = 0;
	पूर्णांक err = -EINVAL;

	अगर (sc && sc->sc_data_direction == DMA_FROM_DEVICE) अणु
		काष्ठा cxgbi_task_data *tdata = iscsi_task_cxgbi_data(task);
		काष्ठा cxgbi_task_tag_info *ttinfo = &tdata->ttinfo;

		scmd_get_params(sc, &ttinfo->sgl, &ttinfo->nents,
				&tdata->dlen, 0);
		err = cxgbi_ddp_reserve(cconn, tdata, sw_tag, tdata->dlen);
		अगर (!err)
			tag = ttinfo->tag;
		अन्यथा
			 log_debug(1 << CXGBI_DBG_DDP,
				   "csk 0x%p, R task 0x%p, %u,%u, no ddp.\n",
				   cconn->cep->csk, task, tdata->dlen,
				   ttinfo->nents);
	पूर्ण

	अगर (err < 0) अणु
		err = cxgbi_ppm_make_non_ddp_tag(ppm, sw_tag, &tag);
		अगर (err < 0)
			वापस err;
	पूर्ण
	/*  the itt need to sent in big-endian order */
	*hdr_itt = (__क्रमce itt_t)htonl(tag);

	log_debug(1 << CXGBI_DBG_DDP,
		  "cdev 0x%p, task 0x%p, 0x%x(0x%x,0x%x)->0x%x/0x%x.\n",
		  cdev, task, sw_tag, task->itt, sess->age, tag, *hdr_itt);
	वापस 0;
पूर्ण

व्योम cxgbi_parse_pdu_itt(काष्ठा iscsi_conn *conn, itt_t itt, पूर्णांक *idx, पूर्णांक *age)
अणु
	काष्ठा iscsi_tcp_conn *tcp_conn = conn->dd_data;
	काष्ठा cxgbi_conn *cconn = tcp_conn->dd_data;
	काष्ठा cxgbi_device *cdev = cconn->chba->cdev;
	काष्ठा cxgbi_ppm *ppm = cdev->cdev2ppm(cdev);
	u32 tag = ntohl((__क्रमce u32)itt);
	u32 sw_bits;

	अगर (ppm) अणु
		अगर (cxgbi_ppm_is_ddp_tag(ppm, tag))
			sw_bits = cxgbi_ppm_get_tag_caller_data(ppm, tag);
		अन्यथा
			sw_bits = cxgbi_ppm_decode_non_ddp_tag(ppm, tag);
	पूर्ण अन्यथा अणु
		sw_bits = tag;
	पूर्ण

	cxgbi_decode_sw_tag(sw_bits, idx, age);
	log_debug(1 << CXGBI_DBG_DDP,
		  "cdev 0x%p, tag 0x%x/0x%x, -> 0x%x(0x%x,0x%x).\n",
		  cdev, tag, itt, sw_bits, idx ? *idx : 0xFFFFF,
		  age ? *age : 0xFF);
पूर्ण
EXPORT_SYMBOL_GPL(cxgbi_parse_pdu_itt);

व्योम cxgbi_conn_tx_खोलो(काष्ठा cxgbi_sock *csk)
अणु
	काष्ठा iscsi_conn *conn = csk->user_data;

	अगर (conn) अणु
		log_debug(1 << CXGBI_DBG_SOCK,
			"csk 0x%p, cid %d.\n", csk, conn->id);
		iscsi_conn_queue_work(conn);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(cxgbi_conn_tx_खोलो);

/*
 * pdu receive, पूर्णांकeract with libiscsi_tcp
 */
अटल अंतरभूत पूर्णांक पढ़ो_pdu_skb(काष्ठा iscsi_conn *conn,
			       काष्ठा sk_buff *skb,
			       अचिन्हित पूर्णांक offset,
			       पूर्णांक offloaded)
अणु
	पूर्णांक status = 0;
	पूर्णांक bytes_पढ़ो;

	bytes_पढ़ो = iscsi_tcp_recv_skb(conn, skb, offset, offloaded, &status);
	चयन (status) अणु
	हाल ISCSI_TCP_CONN_ERR:
		pr_info("skb 0x%p, off %u, %d, TCP_ERR.\n",
			  skb, offset, offloaded);
		वापस -EIO;
	हाल ISCSI_TCP_SUSPENDED:
		log_debug(1 << CXGBI_DBG_PDU_RX,
			"skb 0x%p, off %u, %d, TCP_SUSPEND, rc %d.\n",
			skb, offset, offloaded, bytes_पढ़ो);
		/* no transfer - just have caller flush queue */
		वापस bytes_पढ़ो;
	हाल ISCSI_TCP_SKB_DONE:
		pr_info("skb 0x%p, off %u, %d, TCP_SKB_DONE.\n",
			skb, offset, offloaded);
		/*
		 * pdus should always fit in the skb and we should get
		 * segment करोne notअगरcation.
		 */
		iscsi_conn_prपूर्णांकk(KERN_ERR, conn, "Invalid pdu or skb.");
		वापस -EFAULT;
	हाल ISCSI_TCP_SEGMENT_DONE:
		log_debug(1 << CXGBI_DBG_PDU_RX,
			"skb 0x%p, off %u, %d, TCP_SEG_DONE, rc %d.\n",
			skb, offset, offloaded, bytes_पढ़ो);
		वापस bytes_पढ़ो;
	शेष:
		pr_info("skb 0x%p, off %u, %d, invalid status %d.\n",
			skb, offset, offloaded, status);
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक
skb_पढ़ो_pdu_bhs(काष्ठा cxgbi_sock *csk, काष्ठा iscsi_conn *conn,
		 काष्ठा sk_buff *skb)
अणु
	काष्ठा iscsi_tcp_conn *tcp_conn = conn->dd_data;
	पूर्णांक err;

	log_debug(1 << CXGBI_DBG_PDU_RX,
		"conn 0x%p, skb 0x%p, len %u, flag 0x%lx.\n",
		conn, skb, skb->len, cxgbi_skcb_flags(skb));

	अगर (!iscsi_tcp_recv_segment_is_hdr(tcp_conn)) अणु
		pr_info("conn 0x%p, skb 0x%p, not hdr.\n", conn, skb);
		iscsi_conn_failure(conn, ISCSI_ERR_PROTO);
		वापस -EIO;
	पूर्ण

	अगर (conn->hdrdgst_en &&
	    cxgbi_skcb_test_flag(skb, SKCBF_RX_HCRC_ERR)) अणु
		pr_info("conn 0x%p, skb 0x%p, hcrc.\n", conn, skb);
		iscsi_conn_failure(conn, ISCSI_ERR_HDR_DGST);
		वापस -EIO;
	पूर्ण

	अगर (cxgbi_skcb_test_flag(skb, SKCBF_RX_ISCSI_COMPL) &&
	    cxgbi_skcb_test_flag(skb, SKCBF_RX_DATA_DDPD)) अणु
		/* If completion flag is set and data is directly
		 * placed in to the host memory then update
		 * task->exp_datasn to the datasn in completion
		 * iSCSI hdr as T6 adapter generates completion only
		 * क्रम the last pdu of a sequence.
		 */
		itt_t itt = ((काष्ठा iscsi_data *)skb->data)->itt;
		काष्ठा iscsi_task *task = iscsi_itt_to_ctask(conn, itt);
		u32 data_sn = be32_to_cpu(((काष्ठा iscsi_data *)
							skb->data)->datasn);
		अगर (task && task->sc) अणु
			काष्ठा iscsi_tcp_task *tcp_task = task->dd_data;

			tcp_task->exp_datasn = data_sn;
		पूर्ण
	पूर्ण

	err = पढ़ो_pdu_skb(conn, skb, 0, 0);
	अगर (likely(err >= 0)) अणु
		काष्ठा iscsi_hdr *hdr = (काष्ठा iscsi_hdr *)skb->data;
		u8 opcode = hdr->opcode & ISCSI_OPCODE_MASK;

		अगर (unlikely(opcode == ISCSI_OP_LOGOUT_RSP))
			cxgbi_sock_set_flag(csk, CTPF_LOGOUT_RSP_RCVD);
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक skb_पढ़ो_pdu_data(काष्ठा iscsi_conn *conn, काष्ठा sk_buff *lskb,
			     काष्ठा sk_buff *skb, अचिन्हित पूर्णांक offset)
अणु
	काष्ठा iscsi_tcp_conn *tcp_conn = conn->dd_data;
	bool offloaded = 0;
	पूर्णांक opcode = tcp_conn->in.hdr->opcode & ISCSI_OPCODE_MASK;

	log_debug(1 << CXGBI_DBG_PDU_RX,
		"conn 0x%p, skb 0x%p, len %u, flag 0x%lx.\n",
		conn, skb, skb->len, cxgbi_skcb_flags(skb));

	अगर (conn->datadgst_en &&
	    cxgbi_skcb_test_flag(lskb, SKCBF_RX_DCRC_ERR)) अणु
		pr_info("conn 0x%p, skb 0x%p, dcrc 0x%lx.\n",
			conn, lskb, cxgbi_skcb_flags(lskb));
		iscsi_conn_failure(conn, ISCSI_ERR_DATA_DGST);
		वापस -EIO;
	पूर्ण

	अगर (iscsi_tcp_recv_segment_is_hdr(tcp_conn))
		वापस 0;

	/* coalesced, add header digest length */
	अगर (lskb == skb && conn->hdrdgst_en)
		offset += ISCSI_DIGEST_SIZE;

	अगर (cxgbi_skcb_test_flag(lskb, SKCBF_RX_DATA_DDPD))
		offloaded = 1;

	अगर (opcode == ISCSI_OP_SCSI_DATA_IN)
		log_debug(1 << CXGBI_DBG_PDU_RX,
			"skb 0x%p, op 0x%x, itt 0x%x, %u %s ddp'ed.\n",
			skb, opcode, ntohl(tcp_conn->in.hdr->itt),
			tcp_conn->in.datalen, offloaded ? "is" : "not");

	वापस पढ़ो_pdu_skb(conn, skb, offset, offloaded);
पूर्ण

अटल व्योम csk_वापस_rx_credits(काष्ठा cxgbi_sock *csk, पूर्णांक copied)
अणु
	काष्ठा cxgbi_device *cdev = csk->cdev;
	पूर्णांक must_send;
	u32 credits;

	log_debug(1 << CXGBI_DBG_PDU_RX,
		"csk 0x%p,%u,0x%lx,%u, seq %u, wup %u, thre %u, %u.\n",
		csk, csk->state, csk->flags, csk->tid, csk->copied_seq,
		csk->rcv_wup, cdev->rx_credit_thres,
		csk->rcv_win);

	अगर (!cdev->rx_credit_thres)
		वापस;

	अगर (csk->state != CTP_ESTABLISHED)
		वापस;

	credits = csk->copied_seq - csk->rcv_wup;
	अगर (unlikely(!credits))
		वापस;
	must_send = credits + 16384 >= csk->rcv_win;
	अगर (must_send || credits >= cdev->rx_credit_thres)
		csk->rcv_wup += cdev->csk_send_rx_credits(csk, credits);
पूर्ण

व्योम cxgbi_conn_pdu_पढ़ोy(काष्ठा cxgbi_sock *csk)
अणु
	काष्ठा cxgbi_device *cdev = csk->cdev;
	काष्ठा iscsi_conn *conn = csk->user_data;
	काष्ठा sk_buff *skb;
	अचिन्हित पूर्णांक पढ़ो = 0;
	पूर्णांक err = 0;

	log_debug(1 << CXGBI_DBG_PDU_RX,
		"csk 0x%p, conn 0x%p.\n", csk, conn);

	अगर (unlikely(!conn || conn->suspend_rx)) अणु
		log_debug(1 << CXGBI_DBG_PDU_RX,
			"csk 0x%p, conn 0x%p, id %d, suspend_rx %lu!\n",
			csk, conn, conn ? conn->id : 0xFF,
			conn ? conn->suspend_rx : 0xFF);
		वापस;
	पूर्ण

	जबतक (!err) अणु
		skb = skb_peek(&csk->receive_queue);
		अगर (!skb ||
		    !(cxgbi_skcb_test_flag(skb, SKCBF_RX_STATUS))) अणु
			अगर (skb)
				log_debug(1 << CXGBI_DBG_PDU_RX,
					"skb 0x%p, NOT ready 0x%lx.\n",
					skb, cxgbi_skcb_flags(skb));
			अवरोध;
		पूर्ण
		__skb_unlink(skb, &csk->receive_queue);

		पढ़ो += cxgbi_skcb_rx_pdulen(skb);
		log_debug(1 << CXGBI_DBG_PDU_RX,
			"csk 0x%p, skb 0x%p,%u,f 0x%lx, pdu len %u.\n",
			csk, skb, skb->len, cxgbi_skcb_flags(skb),
			cxgbi_skcb_rx_pdulen(skb));

		अगर (cxgbi_skcb_test_flag(skb, SKCBF_RX_COALESCED)) अणु
			err = skb_पढ़ो_pdu_bhs(csk, conn, skb);
			अगर (err < 0) अणु
				pr_err("coalesced bhs, csk 0x%p, skb 0x%p,%u, "
					"f 0x%lx, plen %u.\n",
					csk, skb, skb->len,
					cxgbi_skcb_flags(skb),
					cxgbi_skcb_rx_pdulen(skb));
				जाओ skb_करोne;
			पूर्ण
			err = skb_पढ़ो_pdu_data(conn, skb, skb,
						err + cdev->skb_rx_extra);
			अगर (err < 0)
				pr_err("coalesced data, csk 0x%p, skb 0x%p,%u, "
					"f 0x%lx, plen %u.\n",
					csk, skb, skb->len,
					cxgbi_skcb_flags(skb),
					cxgbi_skcb_rx_pdulen(skb));
		पूर्ण अन्यथा अणु
			err = skb_पढ़ो_pdu_bhs(csk, conn, skb);
			अगर (err < 0) अणु
				pr_err("bhs, csk 0x%p, skb 0x%p,%u, "
					"f 0x%lx, plen %u.\n",
					csk, skb, skb->len,
					cxgbi_skcb_flags(skb),
					cxgbi_skcb_rx_pdulen(skb));
				जाओ skb_करोne;
			पूर्ण

			अगर (cxgbi_skcb_test_flag(skb, SKCBF_RX_DATA)) अणु
				काष्ठा sk_buff *dskb;

				dskb = skb_peek(&csk->receive_queue);
				अगर (!dskb) अणु
					pr_err("csk 0x%p, skb 0x%p,%u, f 0x%lx,"
						" plen %u, NO data.\n",
						csk, skb, skb->len,
						cxgbi_skcb_flags(skb),
						cxgbi_skcb_rx_pdulen(skb));
					err = -EIO;
					जाओ skb_करोne;
				पूर्ण
				__skb_unlink(dskb, &csk->receive_queue);

				err = skb_पढ़ो_pdu_data(conn, skb, dskb, 0);
				अगर (err < 0)
					pr_err("data, csk 0x%p, skb 0x%p,%u, "
						"f 0x%lx, plen %u, dskb 0x%p,"
						"%u.\n",
						csk, skb, skb->len,
						cxgbi_skcb_flags(skb),
						cxgbi_skcb_rx_pdulen(skb),
						dskb, dskb->len);
				__kमुक्त_skb(dskb);
			पूर्ण अन्यथा
				err = skb_पढ़ो_pdu_data(conn, skb, skb, 0);
		पूर्ण
skb_करोne:
		__kमुक्त_skb(skb);

		अगर (err < 0)
			अवरोध;
	पूर्ण

	log_debug(1 << CXGBI_DBG_PDU_RX, "csk 0x%p, read %u.\n", csk, पढ़ो);
	अगर (पढ़ो) अणु
		csk->copied_seq += पढ़ो;
		csk_वापस_rx_credits(csk, पढ़ो);
		conn->rxdata_octets += पढ़ो;
	पूर्ण

	अगर (err < 0) अणु
		pr_info("csk 0x%p, 0x%p, rx failed %d, read %u.\n",
			csk, conn, err, पढ़ो);
		iscsi_conn_failure(conn, ISCSI_ERR_CONN_FAILED);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(cxgbi_conn_pdu_पढ़ोy);

अटल पूर्णांक sgl_seek_offset(काष्ठा scatterlist *sgl, अचिन्हित पूर्णांक sgcnt,
				अचिन्हित पूर्णांक offset, अचिन्हित पूर्णांक *off,
				काष्ठा scatterlist **sgp)
अणु
	पूर्णांक i;
	काष्ठा scatterlist *sg;

	क्रम_each_sg(sgl, sg, sgcnt, i) अणु
		अगर (offset < sg->length) अणु
			*off = offset;
			*sgp = sg;
			वापस 0;
		पूर्ण
		offset -= sg->length;
	पूर्ण
	वापस -EFAULT;
पूर्ण

अटल पूर्णांक
sgl_पढ़ो_to_frags(काष्ठा scatterlist *sg, अचिन्हित पूर्णांक sgoffset,
		  अचिन्हित पूर्णांक dlen, काष्ठा page_frag *frags,
		  पूर्णांक frag_max, u32 *dlimit)
अणु
	अचिन्हित पूर्णांक datalen = dlen;
	अचिन्हित पूर्णांक sglen = sg->length - sgoffset;
	काष्ठा page *page = sg_page(sg);
	पूर्णांक i;

	i = 0;
	करो अणु
		अचिन्हित पूर्णांक copy;

		अगर (!sglen) अणु
			sg = sg_next(sg);
			अगर (!sg) अणु
				pr_warn("sg %d NULL, len %u/%u.\n",
					i, datalen, dlen);
				वापस -EINVAL;
			पूर्ण
			sgoffset = 0;
			sglen = sg->length;
			page = sg_page(sg);

		पूर्ण
		copy = min(datalen, sglen);
		अगर (i && page == frags[i - 1].page &&
		    sgoffset + sg->offset ==
			frags[i - 1].offset + frags[i - 1].size) अणु
			frags[i - 1].size += copy;
		पूर्ण अन्यथा अणु
			अगर (i >= frag_max) अणु
				pr_warn("too many pages %u, dlen %u.\n",
					frag_max, dlen);
				*dlimit = dlen - datalen;
				वापस -EINVAL;
			पूर्ण

			frags[i].page = page;
			frags[i].offset = sg->offset + sgoffset;
			frags[i].size = copy;
			i++;
		पूर्ण
		datalen -= copy;
		sgoffset += copy;
		sglen -= copy;
	पूर्ण जबतक (datalen);

	वापस i;
पूर्ण

अटल व्योम cxgbi_task_data_sgl_check(काष्ठा iscsi_task *task)
अणु
	काष्ठा scsi_cmnd *sc = task->sc;
	काष्ठा cxgbi_task_data *tdata = iscsi_task_cxgbi_data(task);
	काष्ठा scatterlist *sg, *sgl = शून्य;
	u32 sgcnt = 0;
	पूर्णांक i;

	tdata->flags = CXGBI_TASK_SGL_CHECKED;
	अगर (!sc)
		वापस;

	scmd_get_params(sc, &sgl, &sgcnt, &tdata->dlen, 0);
	अगर (!sgl || !sgcnt) अणु
		tdata->flags |= CXGBI_TASK_SGL_COPY;
		वापस;
	पूर्ण

	क्रम_each_sg(sgl, sg, sgcnt, i) अणु
		अगर (page_count(sg_page(sg)) < 1) अणु
			tdata->flags |= CXGBI_TASK_SGL_COPY;
			वापस;
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक
cxgbi_task_data_sgl_पढ़ो(काष्ठा iscsi_task *task, u32 offset, u32 count,
			 u32 *dlimit)
अणु
	काष्ठा scsi_cmnd *sc = task->sc;
	काष्ठा cxgbi_task_data *tdata = iscsi_task_cxgbi_data(task);
	काष्ठा scatterlist *sgl = शून्य;
	काष्ठा scatterlist *sg;
	u32 dlen = 0;
	u32 sgcnt;
	पूर्णांक err;

	अगर (!sc)
		वापस 0;

	scmd_get_params(sc, &sgl, &sgcnt, &dlen, 0);
	अगर (!sgl || !sgcnt)
		वापस 0;

	err = sgl_seek_offset(sgl, sgcnt, offset, &tdata->sgoffset, &sg);
	अगर (err < 0) अणु
		pr_warn("tpdu max, sgl %u, bad offset %u/%u.\n",
			sgcnt, offset, tdata->dlen);
		वापस err;
	पूर्ण
	err = sgl_पढ़ो_to_frags(sg, tdata->sgoffset, count,
				tdata->frags, MAX_SKB_FRAGS, dlimit);
	अगर (err < 0) अणु
		log_debug(1 << CXGBI_DBG_ISCSI,
			  "sgl max limit, sgl %u, offset %u, %u/%u, dlimit %u.\n",
			  sgcnt, offset, count, tdata->dlen, *dlimit);
		वापस err;
	पूर्ण
	tdata->offset = offset;
	tdata->count = count;
	tdata->nr_frags = err;
	tdata->total_count = count;
	tdata->total_offset = offset;

	log_debug(1 << CXGBI_DBG_ISCSI | 1 << CXGBI_DBG_PDU_TX,
		  "%s: offset %u, count %u,\n"
		  "err %u, total_count %u, total_offset %u\n",
		  __func__, offset, count, err,  tdata->total_count, tdata->total_offset);

	वापस 0;
पूर्ण

पूर्णांक cxgbi_conn_alloc_pdu(काष्ठा iscsi_task *task, u8 op)
अणु
	काष्ठा iscsi_conn *conn = task->conn;
	काष्ठा iscsi_session *session = task->conn->session;
	काष्ठा iscsi_tcp_conn *tcp_conn = conn->dd_data;
	काष्ठा cxgbi_conn *cconn = tcp_conn->dd_data;
	काष्ठा cxgbi_device *cdev = cconn->chba->cdev;
	काष्ठा cxgbi_sock *csk = cconn->cep ? cconn->cep->csk : शून्य;
	काष्ठा iscsi_tcp_task *tcp_task = task->dd_data;
	काष्ठा cxgbi_task_data *tdata = iscsi_task_cxgbi_data(task);
	काष्ठा scsi_cmnd *sc = task->sc;
	u32 headroom = SKB_TX_ISCSI_PDU_HEADER_MAX;
	u32 max_txdata_len = conn->max_xmit_dlength;
	u32 iso_tx_rsvd = 0, local_iso_info = 0;
	u32 last_tdata_offset, last_tdata_count;
	पूर्णांक err = 0;

	अगर (!tcp_task) अणु
		pr_err("task 0x%p, tcp_task 0x%p, tdata 0x%p.\n",
		       task, tcp_task, tdata);
		वापस -ENOMEM;
	पूर्ण
	अगर (!csk) अणु
		pr_err("task 0x%p, csk gone.\n", task);
		वापस -EPIPE;
	पूर्ण

	op &= ISCSI_OPCODE_MASK;

	tcp_task->dd_data = tdata;
	task->hdr = शून्य;

	last_tdata_count = tdata->count;
	last_tdata_offset = tdata->offset;

	अगर ((op == ISCSI_OP_SCSI_DATA_OUT) ||
	    ((op == ISCSI_OP_SCSI_CMD) &&
	     (sc->sc_data_direction == DMA_TO_DEVICE))) अणु
		u32 reमुख्यing_data_tosend, dlimit = 0;
		u32 max_pdu_size, max_num_pdu, num_pdu;
		u32 count;

		/* Preserve conn->max_xmit_dlength because it can get updated to
		 * ISO data size.
		 */
		अगर (task->state == ISCSI_TASK_PENDING)
			tdata->max_xmit_dlength = conn->max_xmit_dlength;

		अगर (!tdata->offset)
			cxgbi_task_data_sgl_check(task);

		reमुख्यing_data_tosend =
			tdata->dlen - tdata->offset - tdata->count;

recalculate_sgl:
		max_txdata_len = tdata->max_xmit_dlength;
		log_debug(1 << CXGBI_DBG_ISCSI | 1 << CXGBI_DBG_PDU_TX,
			  "tdata->dlen %u, remaining to send %u "
			  "conn->max_xmit_dlength %u, "
			  "tdata->max_xmit_dlength %u\n",
			  tdata->dlen, reमुख्यing_data_tosend,
			  conn->max_xmit_dlength, tdata->max_xmit_dlength);

		अगर (cdev->skb_iso_txhdr && !csk->disable_iso &&
		    (reमुख्यing_data_tosend > tdata->max_xmit_dlength) &&
		    !(reमुख्यing_data_tosend % 4)) अणु
			u32 max_iso_data;

			अगर ((op == ISCSI_OP_SCSI_CMD) &&
			    session->initial_r2t_en)
				जाओ no_iso;

			max_pdu_size = tdata->max_xmit_dlength +
				       ISCSI_PDU_NONPAYLOAD_LEN;
			max_iso_data = roundकरोwn(CXGBI_MAX_ISO_DATA_IN_SKB,
						 csk->advmss);
			max_num_pdu = max_iso_data / max_pdu_size;

			num_pdu = (reमुख्यing_data_tosend +
				   tdata->max_xmit_dlength - 1) /
				  tdata->max_xmit_dlength;

			अगर (num_pdu > max_num_pdu)
				num_pdu = max_num_pdu;

			conn->max_xmit_dlength = tdata->max_xmit_dlength * num_pdu;
			max_txdata_len = conn->max_xmit_dlength;
			iso_tx_rsvd = cdev->skb_iso_txhdr;
			local_iso_info = माप(काष्ठा cxgbi_iso_info);

			log_debug(1 << CXGBI_DBG_ISCSI | 1 << CXGBI_DBG_PDU_TX,
				  "max_pdu_size %u, max_num_pdu %u, "
				  "max_txdata %u, num_pdu %u\n",
				  max_pdu_size, max_num_pdu,
				  max_txdata_len, num_pdu);
		पूर्ण
no_iso:
		count  = min_t(u32, max_txdata_len, reमुख्यing_data_tosend);
		err = cxgbi_task_data_sgl_पढ़ो(task,
					       tdata->offset + tdata->count,
					       count, &dlimit);
		अगर (unlikely(err < 0)) अणु
			log_debug(1 << CXGBI_DBG_ISCSI,
				  "task 0x%p, tcp_task 0x%p, tdata 0x%p, "
				  "sgl err %d, count %u, dlimit %u\n",
				  task, tcp_task, tdata, err, count, dlimit);
			अगर (dlimit) अणु
				reमुख्यing_data_tosend =
					roundकरोwn(dlimit,
						  tdata->max_xmit_dlength);
				अगर (!reमुख्यing_data_tosend)
					reमुख्यing_data_tosend = dlimit;

				dlimit = 0;

				conn->max_xmit_dlength = reमुख्यing_data_tosend;
				जाओ recalculate_sgl;
			पूर्ण

			pr_err("task 0x%p, tcp_task 0x%p, tdata 0x%p, "
				"sgl err %d\n",
				task, tcp_task, tdata, err);
			जाओ ret_err;
		पूर्ण

		अगर ((tdata->flags & CXGBI_TASK_SGL_COPY) ||
		    (tdata->nr_frags > MAX_SKB_FRAGS))
			headroom += conn->max_xmit_dlength;
	पूर्ण

	tdata->skb = alloc_skb(local_iso_info + cdev->skb_tx_rsvd +
			       iso_tx_rsvd + headroom, GFP_ATOMIC);
	अगर (!tdata->skb) अणु
		tdata->count = last_tdata_count;
		tdata->offset = last_tdata_offset;
		err = -ENOMEM;
		जाओ ret_err;
	पूर्ण

	skb_reserve(tdata->skb, local_iso_info + cdev->skb_tx_rsvd +
		    iso_tx_rsvd);

	अगर (task->sc) अणु
		task->hdr = (काष्ठा iscsi_hdr *)tdata->skb->data;
	पूर्ण अन्यथा अणु
		task->hdr = kzalloc(SKB_TX_ISCSI_PDU_HEADER_MAX, GFP_ATOMIC);
		अगर (!task->hdr) अणु
			__kमुक्त_skb(tdata->skb);
			tdata->skb = शून्य;
			वापस -ENOMEM;
		पूर्ण
	पूर्ण

	task->hdr_max = SKB_TX_ISCSI_PDU_HEADER_MAX;

	अगर (iso_tx_rsvd)
		cxgbi_skcb_set_flag(tdata->skb, SKCBF_TX_ISO);

	/* data_out uses scsi_cmd's itt */
	अगर (op != ISCSI_OP_SCSI_DATA_OUT)
		task_reserve_itt(task, &task->hdr->itt);

	log_debug(1 << CXGBI_DBG_ISCSI | 1 << CXGBI_DBG_PDU_TX,
		  "task 0x%p, op 0x%x, skb 0x%p,%u+%u/%u, itt 0x%x.\n",
		  task, op, tdata->skb, cdev->skb_tx_rsvd, headroom,
		  conn->max_xmit_dlength, be32_to_cpu(task->hdr->itt));

	वापस 0;

ret_err:
	conn->max_xmit_dlength = tdata->max_xmit_dlength;
	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(cxgbi_conn_alloc_pdu);

अटल पूर्णांक
cxgbi_prep_iso_info(काष्ठा iscsi_task *task, काष्ठा sk_buff *skb,
		    u32 count)
अणु
	काष्ठा cxgbi_iso_info *iso_info = (काष्ठा cxgbi_iso_info *)skb->head;
	काष्ठा iscsi_r2t_info *r2t;
	काष्ठा cxgbi_task_data *tdata = iscsi_task_cxgbi_data(task);
	काष्ठा iscsi_conn *conn = task->conn;
	काष्ठा iscsi_session *session = conn->session;
	काष्ठा iscsi_tcp_task *tcp_task = task->dd_data;
	u32 burst_size = 0, r2t_dlength = 0, dlength;
	u32 max_pdu_len = tdata->max_xmit_dlength;
	u32 segment_offset = 0;
	u32 num_pdu;

	अगर (unlikely(!cxgbi_skcb_test_flag(skb, SKCBF_TX_ISO)))
		वापस 0;

	स_रखो(iso_info, 0, माप(काष्ठा cxgbi_iso_info));

	अगर (task->hdr->opcode == ISCSI_OP_SCSI_CMD && session->imm_data_en) अणु
		iso_info->flags |= CXGBI_ISO_INFO_IMM_ENABLE;
		burst_size = count;
	पूर्ण

	dlength = ntoh24(task->hdr->dlength);
	dlength = min(dlength, max_pdu_len);
	hton24(task->hdr->dlength, dlength);

	num_pdu = (count + max_pdu_len - 1) / max_pdu_len;

	अगर (iscsi_task_has_unsol_data(task))
		r2t = &task->unsol_r2t;
	अन्यथा
		r2t = tcp_task->r2t;

	अगर (r2t) अणु
		log_debug(1 << CXGBI_DBG_ISCSI | 1 << CXGBI_DBG_PDU_TX,
			  "count %u, tdata->count %u, num_pdu %u,"
			  "task->hdr_len %u, r2t->data_length %u, r2t->sent %u\n",
			  count, tdata->count, num_pdu, task->hdr_len,
			  r2t->data_length, r2t->sent);

		r2t_dlength = r2t->data_length - r2t->sent;
		segment_offset = r2t->sent;
		r2t->datasn += num_pdu - 1;
	पूर्ण

	अगर (!r2t || !r2t->sent)
		iso_info->flags |= CXGBI_ISO_INFO_FSLICE;

	अगर (task->hdr->flags & ISCSI_FLAG_CMD_FINAL)
		iso_info->flags |= CXGBI_ISO_INFO_LSLICE;

	task->hdr->flags &= ~ISCSI_FLAG_CMD_FINAL;

	iso_info->op = task->hdr->opcode;
	iso_info->ahs = task->hdr->hlength;
	iso_info->num_pdu = num_pdu;
	iso_info->mpdu = max_pdu_len;
	iso_info->burst_size = (burst_size + r2t_dlength) >> 2;
	iso_info->len = count + task->hdr_len;
	iso_info->segment_offset = segment_offset;

	cxgbi_skcb_tx_iscsi_hdrlen(skb) = task->hdr_len;
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम tx_skb_seपंचांगode(काष्ठा sk_buff *skb, पूर्णांक hcrc, पूर्णांक dcrc)
अणु
	अगर (hcrc || dcrc) अणु
		u8 submode = 0;

		अगर (hcrc)
			submode |= 1;
		अगर (dcrc)
			submode |= 2;
		cxgbi_skcb_tx_ulp_mode(skb) = (ULP2_MODE_ISCSI << 4) | submode;
	पूर्ण अन्यथा
		cxgbi_skcb_tx_ulp_mode(skb) = 0;
पूर्ण

अटल काष्ठा page *rsvd_page;

पूर्णांक cxgbi_conn_init_pdu(काष्ठा iscsi_task *task, अचिन्हित पूर्णांक offset,
			      अचिन्हित पूर्णांक count)
अणु
	काष्ठा iscsi_conn *conn = task->conn;
	काष्ठा iscsi_tcp_task *tcp_task = task->dd_data;
	काष्ठा cxgbi_task_data *tdata = iscsi_task_cxgbi_data(task);
	काष्ठा sk_buff *skb;
	काष्ठा scsi_cmnd *sc = task->sc;
	u32 expected_count, expected_offset;
	u32 datalen = count, dlimit = 0;
	u32 i, padlen = iscsi_padding(count);
	काष्ठा page *pg;
	पूर्णांक err;

	अगर (!tcp_task || (tcp_task->dd_data != tdata)) अणु
		pr_err("task 0x%p,0x%p, tcp_task 0x%p, tdata 0x%p/0x%p.\n",
		       task, task->sc, tcp_task,
		       tcp_task ? tcp_task->dd_data : शून्य, tdata);
		वापस -EINVAL;
	पूर्ण
	skb = tdata->skb;

	log_debug(1 << CXGBI_DBG_ISCSI | 1 << CXGBI_DBG_PDU_TX,
		  "task 0x%p,0x%p, skb 0x%p, 0x%x,0x%x,0x%x, %u+%u.\n",
		  task, task->sc, skb, (*skb->data) & ISCSI_OPCODE_MASK,
		  be32_to_cpu(task->cmdsn), be32_to_cpu(task->hdr->itt), offset, count);

	skb_put(skb, task->hdr_len);
	tx_skb_seपंचांगode(skb, conn->hdrdgst_en, datalen ? conn->datadgst_en : 0);
	अगर (!count) अणु
		tdata->count = count;
		tdata->offset = offset;
		tdata->nr_frags = 0;
		tdata->total_offset = 0;
		tdata->total_count = 0;
		अगर (tdata->max_xmit_dlength)
			conn->max_xmit_dlength = tdata->max_xmit_dlength;
		cxgbi_skcb_clear_flag(skb, SKCBF_TX_ISO);
		वापस 0;
	पूर्ण

	log_debug(1 << CXGBI_DBG_ISCSI | 1 << CXGBI_DBG_PDU_TX,
		  "data->total_count %u, tdata->total_offset %u\n",
		  tdata->total_count, tdata->total_offset);

	expected_count = tdata->total_count;
	expected_offset = tdata->total_offset;

	अगर ((count != expected_count) ||
	    (offset != expected_offset)) अणु
		err = cxgbi_task_data_sgl_पढ़ो(task, offset, count, &dlimit);
		अगर (err < 0) अणु
			pr_err("task 0x%p,0x%p, tcp_task 0x%p, tdata 0x%p/0x%p "
			       "dlimit %u, sgl err %d.\n", task, task->sc,
			       tcp_task, tcp_task ? tcp_task->dd_data : शून्य,
			       tdata, dlimit, err);
			वापस err;
		पूर्ण
	पूर्ण

	/* Restore original value of conn->max_xmit_dlength because
	 * it can get updated to ISO data size.
	 */
	conn->max_xmit_dlength = tdata->max_xmit_dlength;

	अगर (sc) अणु
		काष्ठा page_frag *frag = tdata->frags;

		अगर ((tdata->flags & CXGBI_TASK_SGL_COPY) ||
		    (tdata->nr_frags > MAX_SKB_FRAGS) ||
		    (padlen && (tdata->nr_frags ==
					MAX_SKB_FRAGS))) अणु
			अक्षर *dst = skb->data + task->hdr_len;

			/* data fits in the skb's headroom */
			क्रम (i = 0; i < tdata->nr_frags; i++, frag++) अणु
				अक्षर *src = kmap_atomic(frag->page);

				स_नकल(dst, src + frag->offset, frag->size);
				dst += frag->size;
				kunmap_atomic(src);
			पूर्ण

			अगर (padlen) अणु
				स_रखो(dst, 0, padlen);
				padlen = 0;
			पूर्ण
			skb_put(skb, count + padlen);
		पूर्ण अन्यथा अणु
			क्रम (i = 0; i < tdata->nr_frags; i++, frag++) अणु
				get_page(frag->page);
				skb_fill_page_desc(skb, i, frag->page,
						   frag->offset, frag->size);
			पूर्ण

			skb->len += count;
			skb->data_len += count;
			skb->truesize += count;
		पूर्ण
	पूर्ण अन्यथा अणु
		pg = virt_to_head_page(task->data);
		get_page(pg);
		skb_fill_page_desc(skb, 0, pg,
				   task->data - (अक्षर *)page_address(pg),
				   count);
		skb->len += count;
		skb->data_len += count;
		skb->truesize += count;
	पूर्ण

	अगर (padlen) अणु
		get_page(rsvd_page);
		skb_fill_page_desc(skb, skb_shinfo(skb)->nr_frags,
				   rsvd_page, 0, padlen);

		skb->data_len += padlen;
		skb->truesize += padlen;
		skb->len += padlen;
	पूर्ण

	अगर (likely(count > tdata->max_xmit_dlength))
		cxgbi_prep_iso_info(task, skb, count);
	अन्यथा
		cxgbi_skcb_clear_flag(skb, SKCBF_TX_ISO);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(cxgbi_conn_init_pdu);

अटल पूर्णांक cxgbi_sock_tx_queue_up(काष्ठा cxgbi_sock *csk, काष्ठा sk_buff *skb)
अणु
	काष्ठा cxgbi_device *cdev = csk->cdev;
	काष्ठा cxgbi_iso_info *iso_cpl;
	u32 frags = skb_shinfo(skb)->nr_frags;
	u32 extra_len, num_pdu, hdr_len;
	u32 iso_tx_rsvd = 0;

	अगर (csk->state != CTP_ESTABLISHED) अणु
		log_debug(1 << CXGBI_DBG_PDU_TX,
			  "csk 0x%p,%u,0x%lx,%u, EAGAIN.\n",
			  csk, csk->state, csk->flags, csk->tid);
		वापस -EPIPE;
	पूर्ण

	अगर (csk->err) अणु
		log_debug(1 << CXGBI_DBG_PDU_TX,
			  "csk 0x%p,%u,0x%lx,%u, EPIPE %d.\n",
			  csk, csk->state, csk->flags, csk->tid, csk->err);
		वापस -EPIPE;
	पूर्ण

	अगर ((cdev->flags & CXGBI_FLAG_DEV_T3) &&
	    beक्रमe((csk->snd_win + csk->snd_una), csk->ग_लिखो_seq)) अणु
		log_debug(1 << CXGBI_DBG_PDU_TX,
			  "csk 0x%p,%u,0x%lx,%u, FULL %u-%u >= %u.\n",
			  csk, csk->state, csk->flags, csk->tid, csk->ग_लिखो_seq,
			  csk->snd_una, csk->snd_win);
		वापस -ENOBUFS;
	पूर्ण

	अगर (cxgbi_skcb_test_flag(skb, SKCBF_TX_ISO))
		iso_tx_rsvd = cdev->skb_iso_txhdr;

	अगर (unlikely(skb_headroom(skb) < (cdev->skb_tx_rsvd + iso_tx_rsvd))) अणु
		pr_err("csk 0x%p, skb head %u < %u.\n",
		       csk, skb_headroom(skb), cdev->skb_tx_rsvd);
		वापस -EINVAL;
	पूर्ण

	अगर (skb->len != skb->data_len)
		frags++;

	अगर (frags >= SKB_WR_LIST_SIZE) अणु
		pr_err("csk 0x%p, frags %u, %u,%u >%lu.\n",
		       csk, skb_shinfo(skb)->nr_frags, skb->len,
		       skb->data_len, SKB_WR_LIST_SIZE);
		वापस -EINVAL;
	पूर्ण

	cxgbi_skcb_set_flag(skb, SKCBF_TX_NEED_HDR);
	skb_reset_transport_header(skb);
	cxgbi_sock_skb_entail(csk, skb);

	extra_len = cxgbi_ulp_extra_len(cxgbi_skcb_tx_ulp_mode(skb));

	अगर (likely(cxgbi_skcb_test_flag(skb, SKCBF_TX_ISO))) अणु
		iso_cpl = (काष्ठा cxgbi_iso_info *)skb->head;
		num_pdu = iso_cpl->num_pdu;
		hdr_len = cxgbi_skcb_tx_iscsi_hdrlen(skb);
		extra_len = (cxgbi_ulp_extra_len(cxgbi_skcb_tx_ulp_mode(skb)) *
			     num_pdu) +	(hdr_len * (num_pdu - 1));
	पूर्ण

	csk->ग_लिखो_seq += (skb->len + extra_len);

	वापस 0;
पूर्ण

अटल पूर्णांक cxgbi_sock_send_skb(काष्ठा cxgbi_sock *csk, काष्ठा sk_buff *skb)
अणु
	काष्ठा cxgbi_device *cdev = csk->cdev;
	पूर्णांक len = skb->len;
	पूर्णांक err;

	spin_lock_bh(&csk->lock);
	err = cxgbi_sock_tx_queue_up(csk, skb);
	अगर (err < 0) अणु
		spin_unlock_bh(&csk->lock);
		वापस err;
	पूर्ण

	अगर (likely(skb_queue_len(&csk->ग_लिखो_queue)))
		cdev->csk_push_tx_frames(csk, 0);
	spin_unlock_bh(&csk->lock);
	वापस len;
पूर्ण

पूर्णांक cxgbi_conn_xmit_pdu(काष्ठा iscsi_task *task)
अणु
	काष्ठा iscsi_tcp_conn *tcp_conn = task->conn->dd_data;
	काष्ठा cxgbi_conn *cconn = tcp_conn->dd_data;
	काष्ठा iscsi_tcp_task *tcp_task = task->dd_data;
	काष्ठा cxgbi_task_data *tdata = iscsi_task_cxgbi_data(task);
	काष्ठा cxgbi_task_tag_info *ttinfo = &tdata->ttinfo;
	काष्ठा sk_buff *skb;
	काष्ठा cxgbi_sock *csk = शून्य;
	u32 pdulen = 0;
	u32 datalen;
	पूर्णांक err;

	अगर (!tcp_task || (tcp_task->dd_data != tdata)) अणु
		pr_err("task 0x%p,0x%p, tcp_task 0x%p, tdata 0x%p/0x%p.\n",
		       task, task->sc, tcp_task,
		       tcp_task ? tcp_task->dd_data : शून्य, tdata);
		वापस -EINVAL;
	पूर्ण

	skb = tdata->skb;
	अगर (!skb) अणु
		log_debug(1 << CXGBI_DBG_ISCSI | 1 << CXGBI_DBG_PDU_TX,
			  "task 0x%p, skb NULL.\n", task);
		वापस 0;
	पूर्ण

	अगर (cconn && cconn->cep)
		csk = cconn->cep->csk;

	अगर (!csk) अणु
		log_debug(1 << CXGBI_DBG_ISCSI | 1 << CXGBI_DBG_PDU_TX,
			  "task 0x%p, csk gone.\n", task);
		वापस -EPIPE;
	पूर्ण

	tdata->skb = शून्य;
	datalen = skb->data_len;

	/* ग_लिखो ppod first अगर using ofldq to ग_लिखो ppod */
	अगर (ttinfo->flags & CXGBI_PPOD_INFO_FLAG_VALID) अणु
		काष्ठा cxgbi_ppm *ppm = csk->cdev->cdev2ppm(csk->cdev);

		ttinfo->flags &= ~CXGBI_PPOD_INFO_FLAG_VALID;
		अगर (csk->cdev->csk_ddp_set_map(ppm, csk, ttinfo) < 0)
			pr_err("task 0x%p, ppod writing using ofldq failed.\n",
			       task);
			/* जारी. Let fl get the data */
	पूर्ण

	अगर (!task->sc)
		स_नकल(skb->data, task->hdr, SKB_TX_ISCSI_PDU_HEADER_MAX);

	err = cxgbi_sock_send_skb(csk, skb);
	अगर (err > 0) अणु
		pdulen += err;

		log_debug(1 << CXGBI_DBG_PDU_TX, "task 0x%p,0x%p, rv %d.\n",
			  task, task->sc, err);

		अगर (task->conn->hdrdgst_en)
			pdulen += ISCSI_DIGEST_SIZE;

		अगर (datalen && task->conn->datadgst_en)
			pdulen += ISCSI_DIGEST_SIZE;

		task->conn->txdata_octets += pdulen;

		अगर (unlikely(cxgbi_is_iso_config(csk) && cxgbi_is_iso_disabled(csk))) अणु
			अगर (समय_after(jअगरfies, csk->prev_iso_ts + HZ)) अणु
				csk->disable_iso = false;
				csk->prev_iso_ts = 0;
				log_debug(1 << CXGBI_DBG_PDU_TX,
					  "enable iso: csk 0x%p\n", csk);
			पूर्ण
		पूर्ण

		वापस 0;
	पूर्ण

	अगर (err == -EAGAIN || err == -ENOBUFS) अणु
		log_debug(1 << CXGBI_DBG_PDU_TX,
			  "task 0x%p, skb 0x%p, len %u/%u, %d EAGAIN.\n",
			  task, skb, skb->len, skb->data_len, err);
		/* reset skb to send when we are called again */
		tdata->skb = skb;

		अगर (cxgbi_is_iso_config(csk) && !cxgbi_is_iso_disabled(csk) &&
		    (csk->no_tx_credits++ >= 2)) अणु
			csk->disable_iso = true;
			csk->prev_iso_ts = jअगरfies;
			log_debug(1 << CXGBI_DBG_PDU_TX,
				  "disable iso:csk 0x%p, ts:%lu\n",
				  csk, csk->prev_iso_ts);
		पूर्ण

		वापस err;
	पूर्ण

	log_debug(1 << CXGBI_DBG_ISCSI | 1 << CXGBI_DBG_PDU_TX,
		  "itt 0x%x, skb 0x%p, len %u/%u, xmit err %d.\n",
		  task->itt, skb, skb->len, skb->data_len, err);
	__kमुक्त_skb(skb);
	iscsi_conn_prपूर्णांकk(KERN_ERR, task->conn, "xmit err %d.\n", err);
	iscsi_conn_failure(task->conn, ISCSI_ERR_XMIT_FAILED);
	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(cxgbi_conn_xmit_pdu);

व्योम cxgbi_cleanup_task(काष्ठा iscsi_task *task)
अणु
	काष्ठा iscsi_tcp_task *tcp_task = task->dd_data;
	काष्ठा cxgbi_task_data *tdata = iscsi_task_cxgbi_data(task);

	अगर (!tcp_task || (tcp_task->dd_data != tdata)) अणु
		pr_info("task 0x%p,0x%p, tcp_task 0x%p, tdata 0x%p/0x%p.\n",
			task, task->sc, tcp_task,
			tcp_task ? tcp_task->dd_data : शून्य, tdata);
		वापस;
	पूर्ण

	log_debug(1 << CXGBI_DBG_ISCSI,
		"task 0x%p, skb 0x%p, itt 0x%x.\n",
		task, tdata->skb, task->hdr_itt);

	tcp_task->dd_data = शून्य;

	अगर (!task->sc)
		kमुक्त(task->hdr);
	task->hdr = शून्य;

	/*  never reached the xmit task callout */
	अगर (tdata->skb) अणु
		__kमुक्त_skb(tdata->skb);
		tdata->skb = शून्य;
	पूर्ण

	task_release_itt(task, task->hdr_itt);
	स_रखो(tdata, 0, माप(*tdata));

	iscsi_tcp_cleanup_task(task);
पूर्ण
EXPORT_SYMBOL_GPL(cxgbi_cleanup_task);

व्योम cxgbi_get_conn_stats(काष्ठा iscsi_cls_conn *cls_conn,
				काष्ठा iscsi_stats *stats)
अणु
	काष्ठा iscsi_conn *conn = cls_conn->dd_data;

	stats->txdata_octets = conn->txdata_octets;
	stats->rxdata_octets = conn->rxdata_octets;
	stats->scsicmd_pdus = conn->scsicmd_pdus_cnt;
	stats->dataout_pdus = conn->dataout_pdus_cnt;
	stats->scsirsp_pdus = conn->scsirsp_pdus_cnt;
	stats->datain_pdus = conn->datain_pdus_cnt;
	stats->r2t_pdus = conn->r2t_pdus_cnt;
	stats->पंचांगfcmd_pdus = conn->पंचांगfcmd_pdus_cnt;
	stats->पंचांगfrsp_pdus = conn->पंचांगfrsp_pdus_cnt;
	stats->digest_err = 0;
	stats->समयout_err = 0;
	stats->custom_length = 1;
	म_नकल(stats->custom[0].desc, "eh_abort_cnt");
	stats->custom[0].value = conn->eh_पात_cnt;
पूर्ण
EXPORT_SYMBOL_GPL(cxgbi_get_conn_stats);

अटल पूर्णांक cxgbi_conn_max_xmit_dlength(काष्ठा iscsi_conn *conn)
अणु
	काष्ठा iscsi_tcp_conn *tcp_conn = conn->dd_data;
	काष्ठा cxgbi_conn *cconn = tcp_conn->dd_data;
	काष्ठा cxgbi_device *cdev = cconn->chba->cdev;
	अचिन्हित पूर्णांक headroom = SKB_MAX_HEAD(cdev->skb_tx_rsvd);
	अचिन्हित पूर्णांक max_def = 512 * MAX_SKB_FRAGS;
	अचिन्हित पूर्णांक max = max(max_def, headroom);

	max = min(cconn->chba->cdev->tx_max_size, max);
	अगर (conn->max_xmit_dlength)
		conn->max_xmit_dlength = min(conn->max_xmit_dlength, max);
	अन्यथा
		conn->max_xmit_dlength = max;
	cxgbi_align_pdu_size(conn->max_xmit_dlength);

	वापस 0;
पूर्ण

अटल पूर्णांक cxgbi_conn_max_recv_dlength(काष्ठा iscsi_conn *conn)
अणु
	काष्ठा iscsi_tcp_conn *tcp_conn = conn->dd_data;
	काष्ठा cxgbi_conn *cconn = tcp_conn->dd_data;
	अचिन्हित पूर्णांक max = cconn->chba->cdev->rx_max_size;

	cxgbi_align_pdu_size(max);

	अगर (conn->max_recv_dlength) अणु
		अगर (conn->max_recv_dlength > max) अणु
			pr_err("MaxRecvDataSegmentLength %u > %u.\n",
				conn->max_recv_dlength, max);
			वापस -EINVAL;
		पूर्ण
		conn->max_recv_dlength = min(conn->max_recv_dlength, max);
		cxgbi_align_pdu_size(conn->max_recv_dlength);
	पूर्ण अन्यथा
		conn->max_recv_dlength = max;

	वापस 0;
पूर्ण

पूर्णांक cxgbi_set_conn_param(काष्ठा iscsi_cls_conn *cls_conn,
			क्रमागत iscsi_param param, अक्षर *buf, पूर्णांक buflen)
अणु
	काष्ठा iscsi_conn *conn = cls_conn->dd_data;
	काष्ठा iscsi_tcp_conn *tcp_conn = conn->dd_data;
	काष्ठा cxgbi_conn *cconn = tcp_conn->dd_data;
	काष्ठा cxgbi_sock *csk = cconn->cep->csk;
	पूर्णांक err;

	log_debug(1 << CXGBI_DBG_ISCSI,
		"cls_conn 0x%p, param %d, buf(%d) %s.\n",
		cls_conn, param, buflen, buf);

	चयन (param) अणु
	हाल ISCSI_PARAM_HDRDGST_EN:
		err = iscsi_set_param(cls_conn, param, buf, buflen);
		अगर (!err && conn->hdrdgst_en)
			err = csk->cdev->csk_ddp_setup_digest(csk, csk->tid,
							conn->hdrdgst_en,
							conn->datadgst_en);
		अवरोध;
	हाल ISCSI_PARAM_DATADGST_EN:
		err = iscsi_set_param(cls_conn, param, buf, buflen);
		अगर (!err && conn->datadgst_en)
			err = csk->cdev->csk_ddp_setup_digest(csk, csk->tid,
							conn->hdrdgst_en,
							conn->datadgst_en);
		अवरोध;
	हाल ISCSI_PARAM_MAX_R2T:
		वापस iscsi_tcp_set_max_r2t(conn, buf);
	हाल ISCSI_PARAM_MAX_RECV_DLENGTH:
		err = iscsi_set_param(cls_conn, param, buf, buflen);
		अगर (!err)
			err = cxgbi_conn_max_recv_dlength(conn);
		अवरोध;
	हाल ISCSI_PARAM_MAX_XMIT_DLENGTH:
		err = iscsi_set_param(cls_conn, param, buf, buflen);
		अगर (!err)
			err = cxgbi_conn_max_xmit_dlength(conn);
		अवरोध;
	शेष:
		वापस iscsi_set_param(cls_conn, param, buf, buflen);
	पूर्ण
	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(cxgbi_set_conn_param);

पूर्णांक cxgbi_get_ep_param(काष्ठा iscsi_endpoपूर्णांक *ep, क्रमागत iscsi_param param,
		       अक्षर *buf)
अणु
	काष्ठा cxgbi_endpoपूर्णांक *cep = ep->dd_data;
	काष्ठा cxgbi_sock *csk;

	log_debug(1 << CXGBI_DBG_ISCSI,
		"cls_conn 0x%p, param %d.\n", ep, param);

	चयन (param) अणु
	हाल ISCSI_PARAM_CONN_PORT:
	हाल ISCSI_PARAM_CONN_ADDRESS:
		अगर (!cep)
			वापस -ENOTCONN;

		csk = cep->csk;
		अगर (!csk)
			वापस -ENOTCONN;

		वापस iscsi_conn_get_addr_param((काष्ठा sockaddr_storage *)
						 &csk->daddr, param, buf);
	शेष:
		अवरोध;
	पूर्ण
	वापस -ENOSYS;
पूर्ण
EXPORT_SYMBOL_GPL(cxgbi_get_ep_param);

काष्ठा iscsi_cls_conn *
cxgbi_create_conn(काष्ठा iscsi_cls_session *cls_session, u32 cid)
अणु
	काष्ठा iscsi_cls_conn *cls_conn;
	काष्ठा iscsi_conn *conn;
	काष्ठा iscsi_tcp_conn *tcp_conn;
	काष्ठा cxgbi_conn *cconn;

	cls_conn = iscsi_tcp_conn_setup(cls_session, माप(*cconn), cid);
	अगर (!cls_conn)
		वापस शून्य;

	conn = cls_conn->dd_data;
	tcp_conn = conn->dd_data;
	cconn = tcp_conn->dd_data;
	cconn->iconn = conn;

	log_debug(1 << CXGBI_DBG_ISCSI,
		"cid %u(0x%x), cls 0x%p,0x%p, conn 0x%p,0x%p,0x%p.\n",
		cid, cid, cls_session, cls_conn, conn, tcp_conn, cconn);

	वापस cls_conn;
पूर्ण
EXPORT_SYMBOL_GPL(cxgbi_create_conn);

पूर्णांक cxgbi_bind_conn(काष्ठा iscsi_cls_session *cls_session,
				काष्ठा iscsi_cls_conn *cls_conn,
				u64 transport_eph, पूर्णांक is_leading)
अणु
	काष्ठा iscsi_conn *conn = cls_conn->dd_data;
	काष्ठा iscsi_tcp_conn *tcp_conn = conn->dd_data;
	काष्ठा cxgbi_conn *cconn = tcp_conn->dd_data;
	काष्ठा cxgbi_ppm *ppm;
	काष्ठा iscsi_endpoपूर्णांक *ep;
	काष्ठा cxgbi_endpoपूर्णांक *cep;
	काष्ठा cxgbi_sock *csk;
	पूर्णांक err;

	ep = iscsi_lookup_endpoपूर्णांक(transport_eph);
	अगर (!ep)
		वापस -EINVAL;

	/*  setup ddp pagesize */
	cep = ep->dd_data;
	csk = cep->csk;

	ppm = csk->cdev->cdev2ppm(csk->cdev);
	err = csk->cdev->csk_ddp_setup_pgidx(csk, csk->tid,
					     ppm->tक्रमmat.pgsz_idx_dflt);
	अगर (err < 0)
		वापस err;

	err = iscsi_conn_bind(cls_session, cls_conn, is_leading);
	अगर (err)
		वापस -EINVAL;

	/*  calculate the tag idx bits needed क्रम this conn based on cmds_max */
	cconn->task_idx_bits = (__ilog2_u32(conn->session->cmds_max - 1)) + 1;

	ग_लिखो_lock_bh(&csk->callback_lock);
	csk->user_data = conn;
	cconn->chba = cep->chba;
	cconn->cep = cep;
	cep->cconn = cconn;
	ग_लिखो_unlock_bh(&csk->callback_lock);

	cxgbi_conn_max_xmit_dlength(conn);
	cxgbi_conn_max_recv_dlength(conn);

	log_debug(1 << CXGBI_DBG_ISCSI,
		"cls 0x%p,0x%p, ep 0x%p, cconn 0x%p, csk 0x%p.\n",
		cls_session, cls_conn, ep, cconn, csk);
	/*  init recv engine */
	iscsi_tcp_hdr_recv_prep(tcp_conn);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(cxgbi_bind_conn);

काष्ठा iscsi_cls_session *cxgbi_create_session(काष्ठा iscsi_endpoपूर्णांक *ep,
						u16 cmds_max, u16 qdepth,
						u32 initial_cmdsn)
अणु
	काष्ठा cxgbi_endpoपूर्णांक *cep;
	काष्ठा cxgbi_hba *chba;
	काष्ठा Scsi_Host *shost;
	काष्ठा iscsi_cls_session *cls_session;
	काष्ठा iscsi_session *session;

	अगर (!ep) अणु
		pr_err("missing endpoint.\n");
		वापस शून्य;
	पूर्ण

	cep = ep->dd_data;
	chba = cep->chba;
	shost = chba->shost;

	BUG_ON(chba != iscsi_host_priv(shost));

	cls_session = iscsi_session_setup(chba->cdev->itp, shost,
					cmds_max, 0,
					माप(काष्ठा iscsi_tcp_task) +
					माप(काष्ठा cxgbi_task_data),
					initial_cmdsn, ISCSI_MAX_TARGET);
	अगर (!cls_session)
		वापस शून्य;

	session = cls_session->dd_data;
	अगर (iscsi_tcp_r2tpool_alloc(session))
		जाओ हटाओ_session;

	log_debug(1 << CXGBI_DBG_ISCSI,
		"ep 0x%p, cls sess 0x%p.\n", ep, cls_session);
	वापस cls_session;

हटाओ_session:
	iscsi_session_tearकरोwn(cls_session);
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(cxgbi_create_session);

व्योम cxgbi_destroy_session(काष्ठा iscsi_cls_session *cls_session)
अणु
	log_debug(1 << CXGBI_DBG_ISCSI,
		"cls sess 0x%p.\n", cls_session);

	iscsi_tcp_r2tpool_मुक्त(cls_session->dd_data);
	iscsi_session_tearकरोwn(cls_session);
पूर्ण
EXPORT_SYMBOL_GPL(cxgbi_destroy_session);

पूर्णांक cxgbi_set_host_param(काष्ठा Scsi_Host *shost, क्रमागत iscsi_host_param param,
			अक्षर *buf, पूर्णांक buflen)
अणु
	काष्ठा cxgbi_hba *chba = iscsi_host_priv(shost);

	अगर (!chba->ndev) अणु
		shost_prपूर्णांकk(KERN_ERR, shost, "Could not get host param. "
				"netdev for host not set.\n");
		वापस -ENODEV;
	पूर्ण

	log_debug(1 << CXGBI_DBG_ISCSI,
		"shost 0x%p, hba 0x%p,%s, param %d, buf(%d) %s.\n",
		shost, chba, chba->ndev->name, param, buflen, buf);

	चयन (param) अणु
	हाल ISCSI_HOST_PARAM_IPADDRESS:
	अणु
		__be32 addr = in_aton(buf);
		log_debug(1 << CXGBI_DBG_ISCSI,
			"hba %s, req. ipv4 %pI4.\n", chba->ndev->name, &addr);
		cxgbi_set_iscsi_ipv4(chba, addr);
		वापस 0;
	पूर्ण
	हाल ISCSI_HOST_PARAM_HWADDRESS:
	हाल ISCSI_HOST_PARAM_NETDEV_NAME:
		वापस 0;
	शेष:
		वापस iscsi_host_set_param(shost, param, buf, buflen);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(cxgbi_set_host_param);

पूर्णांक cxgbi_get_host_param(काष्ठा Scsi_Host *shost, क्रमागत iscsi_host_param param,
			अक्षर *buf)
अणु
	काष्ठा cxgbi_hba *chba = iscsi_host_priv(shost);
	पूर्णांक len = 0;

	अगर (!chba->ndev) अणु
		shost_prपूर्णांकk(KERN_ERR, shost, "Could not get host param. "
				"netdev for host not set.\n");
		वापस -ENODEV;
	पूर्ण

	log_debug(1 << CXGBI_DBG_ISCSI,
		"shost 0x%p, hba 0x%p,%s, param %d.\n",
		shost, chba, chba->ndev->name, param);

	चयन (param) अणु
	हाल ISCSI_HOST_PARAM_HWADDRESS:
		len = sysfs_क्रमmat_mac(buf, chba->ndev->dev_addr, 6);
		अवरोध;
	हाल ISCSI_HOST_PARAM_NETDEV_NAME:
		len = प्र_लिखो(buf, "%s\n", chba->ndev->name);
		अवरोध;
	हाल ISCSI_HOST_PARAM_IPADDRESS:
	अणु
		काष्ठा cxgbi_sock *csk = find_sock_on_port(chba->cdev,
							   chba->port_id);
		अगर (csk) अणु
			len = प्र_लिखो(buf, "%pIS",
				      (काष्ठा sockaddr *)&csk->saddr);
		पूर्ण
		log_debug(1 << CXGBI_DBG_ISCSI,
			  "hba %s, addr %s.\n", chba->ndev->name, buf);
		अवरोध;
	पूर्ण
	शेष:
		वापस iscsi_host_get_param(shost, param, buf);
	पूर्ण

	वापस len;
पूर्ण
EXPORT_SYMBOL_GPL(cxgbi_get_host_param);

काष्ठा iscsi_endpoपूर्णांक *cxgbi_ep_connect(काष्ठा Scsi_Host *shost,
					काष्ठा sockaddr *dst_addr,
					पूर्णांक non_blocking)
अणु
	काष्ठा iscsi_endpoपूर्णांक *ep;
	काष्ठा cxgbi_endpoपूर्णांक *cep;
	काष्ठा cxgbi_hba *hba = शून्य;
	काष्ठा cxgbi_sock *csk;
	पूर्णांक अगरindex = 0;
	पूर्णांक err = -EINVAL;

	log_debug(1 << CXGBI_DBG_ISCSI | 1 << CXGBI_DBG_SOCK,
		"shost 0x%p, non_blocking %d, dst_addr 0x%p.\n",
		shost, non_blocking, dst_addr);

	अगर (shost) अणु
		hba = iscsi_host_priv(shost);
		अगर (!hba) अणु
			pr_info("shost 0x%p, priv NULL.\n", shost);
			जाओ err_out;
		पूर्ण
	पूर्ण

check_route:
	अगर (dst_addr->sa_family == AF_INET) अणु
		csk = cxgbi_check_route(dst_addr, अगरindex);
#अगर IS_ENABLED(CONFIG_IPV6)
	पूर्ण अन्यथा अगर (dst_addr->sa_family == AF_INET6) अणु
		csk = cxgbi_check_route6(dst_addr, अगरindex);
#पूर्ण_अगर
	पूर्ण अन्यथा अणु
		pr_info("address family 0x%x NOT supported.\n",
			dst_addr->sa_family);
		err = -EAFNOSUPPORT;
		वापस (काष्ठा iscsi_endpoपूर्णांक *)ERR_PTR(err);
	पूर्ण

	अगर (IS_ERR(csk))
		वापस (काष्ठा iscsi_endpoपूर्णांक *)csk;
	cxgbi_sock_get(csk);

	अगर (!hba)
		hba = csk->cdev->hbas[csk->port_id];
	अन्यथा अगर (hba != csk->cdev->hbas[csk->port_id]) अणु
		अगर (अगरindex != hba->ndev->अगरindex) अणु
			cxgbi_sock_put(csk);
			cxgbi_sock_बंदd(csk);
			अगरindex = hba->ndev->अगरindex;
			जाओ check_route;
		पूर्ण

		pr_info("Could not connect through requested host %u"
			"hba 0x%p != 0x%p (%u).\n",
			shost->host_no, hba,
			csk->cdev->hbas[csk->port_id], csk->port_id);
		err = -ENOSPC;
		जाओ release_conn;
	पूर्ण

	err = sock_get_port(csk);
	अगर (err)
		जाओ release_conn;

	cxgbi_sock_set_state(csk, CTP_CONNECTING);
	err = csk->cdev->csk_init_act_खोलो(csk);
	अगर (err)
		जाओ release_conn;

	अगर (cxgbi_sock_is_closing(csk)) अणु
		err = -ENOSPC;
		pr_info("csk 0x%p is closing.\n", csk);
		जाओ release_conn;
	पूर्ण

	ep = iscsi_create_endpoपूर्णांक(माप(*cep));
	अगर (!ep) अणु
		err = -ENOMEM;
		pr_info("iscsi alloc ep, OOM.\n");
		जाओ release_conn;
	पूर्ण

	cep = ep->dd_data;
	cep->csk = csk;
	cep->chba = hba;

	log_debug(1 << CXGBI_DBG_ISCSI | 1 << CXGBI_DBG_SOCK,
		"ep 0x%p, cep 0x%p, csk 0x%p, hba 0x%p,%s.\n",
		ep, cep, csk, hba, hba->ndev->name);
	वापस ep;

release_conn:
	cxgbi_sock_put(csk);
	cxgbi_sock_बंदd(csk);
err_out:
	वापस ERR_PTR(err);
पूर्ण
EXPORT_SYMBOL_GPL(cxgbi_ep_connect);

पूर्णांक cxgbi_ep_poll(काष्ठा iscsi_endpoपूर्णांक *ep, पूर्णांक समयout_ms)
अणु
	काष्ठा cxgbi_endpoपूर्णांक *cep = ep->dd_data;
	काष्ठा cxgbi_sock *csk = cep->csk;

	अगर (!cxgbi_sock_is_established(csk))
		वापस 0;
	वापस 1;
पूर्ण
EXPORT_SYMBOL_GPL(cxgbi_ep_poll);

व्योम cxgbi_ep_disconnect(काष्ठा iscsi_endpoपूर्णांक *ep)
अणु
	काष्ठा cxgbi_endpoपूर्णांक *cep = ep->dd_data;
	काष्ठा cxgbi_conn *cconn = cep->cconn;
	काष्ठा cxgbi_sock *csk = cep->csk;

	log_debug(1 << CXGBI_DBG_ISCSI | 1 << CXGBI_DBG_SOCK,
		"ep 0x%p, cep 0x%p, cconn 0x%p, csk 0x%p,%u,0x%lx.\n",
		ep, cep, cconn, csk, csk->state, csk->flags);

	अगर (cconn && cconn->iconn) अणु
		iscsi_suspend_tx(cconn->iconn);
		ग_लिखो_lock_bh(&csk->callback_lock);
		cep->csk->user_data = शून्य;
		cconn->cep = शून्य;
		ग_लिखो_unlock_bh(&csk->callback_lock);
	पूर्ण
	iscsi_destroy_endpoपूर्णांक(ep);

	अगर (likely(csk->state >= CTP_ESTABLISHED))
		need_active_बंद(csk);
	अन्यथा
		cxgbi_sock_बंदd(csk);

	cxgbi_sock_put(csk);
पूर्ण
EXPORT_SYMBOL_GPL(cxgbi_ep_disconnect);

पूर्णांक cxgbi_iscsi_init(काष्ठा iscsi_transport *itp,
			काष्ठा scsi_transport_ढाँचा **stt)
अणु
	*stt = iscsi_रेजिस्टर_transport(itp);
	अगर (*stt == शून्य) अणु
		pr_err("unable to register %s transport 0x%p.\n",
			itp->name, itp);
		वापस -ENODEV;
	पूर्ण
	log_debug(1 << CXGBI_DBG_ISCSI,
		"%s, registered iscsi transport 0x%p.\n",
		itp->name, stt);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(cxgbi_iscsi_init);

व्योम cxgbi_iscsi_cleanup(काष्ठा iscsi_transport *itp,
			काष्ठा scsi_transport_ढाँचा **stt)
अणु
	अगर (*stt) अणु
		log_debug(1 << CXGBI_DBG_ISCSI,
			"de-register transport 0x%p, %s, stt 0x%p.\n",
			itp, itp->name, *stt);
		*stt = शून्य;
		iscsi_unरेजिस्टर_transport(itp);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(cxgbi_iscsi_cleanup);

umode_t cxgbi_attr_is_visible(पूर्णांक param_type, पूर्णांक param)
अणु
	चयन (param_type) अणु
	हाल ISCSI_HOST_PARAM:
		चयन (param) अणु
		हाल ISCSI_HOST_PARAM_NETDEV_NAME:
		हाल ISCSI_HOST_PARAM_HWADDRESS:
		हाल ISCSI_HOST_PARAM_IPADDRESS:
		हाल ISCSI_HOST_PARAM_INITIATOR_NAME:
			वापस S_IRUGO;
		शेष:
			वापस 0;
		पूर्ण
	हाल ISCSI_PARAM:
		चयन (param) अणु
		हाल ISCSI_PARAM_MAX_RECV_DLENGTH:
		हाल ISCSI_PARAM_MAX_XMIT_DLENGTH:
		हाल ISCSI_PARAM_HDRDGST_EN:
		हाल ISCSI_PARAM_DATADGST_EN:
		हाल ISCSI_PARAM_CONN_ADDRESS:
		हाल ISCSI_PARAM_CONN_PORT:
		हाल ISCSI_PARAM_EXP_STATSN:
		हाल ISCSI_PARAM_PERSISTENT_ADDRESS:
		हाल ISCSI_PARAM_PERSISTENT_PORT:
		हाल ISCSI_PARAM_PING_TMO:
		हाल ISCSI_PARAM_RECV_TMO:
		हाल ISCSI_PARAM_INITIAL_R2T_EN:
		हाल ISCSI_PARAM_MAX_R2T:
		हाल ISCSI_PARAM_IMM_DATA_EN:
		हाल ISCSI_PARAM_FIRST_BURST:
		हाल ISCSI_PARAM_MAX_BURST:
		हाल ISCSI_PARAM_PDU_INORDER_EN:
		हाल ISCSI_PARAM_DATASEQ_INORDER_EN:
		हाल ISCSI_PARAM_ERL:
		हाल ISCSI_PARAM_TARGET_NAME:
		हाल ISCSI_PARAM_TPGT:
		हाल ISCSI_PARAM_USERNAME:
		हाल ISCSI_PARAM_PASSWORD:
		हाल ISCSI_PARAM_USERNAME_IN:
		हाल ISCSI_PARAM_PASSWORD_IN:
		हाल ISCSI_PARAM_FAST_ABORT:
		हाल ISCSI_PARAM_ABORT_TMO:
		हाल ISCSI_PARAM_LU_RESET_TMO:
		हाल ISCSI_PARAM_TGT_RESET_TMO:
		हाल ISCSI_PARAM_IFACE_NAME:
		हाल ISCSI_PARAM_INITIATOR_NAME:
			वापस S_IRUGO;
		शेष:
			वापस 0;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(cxgbi_attr_is_visible);

अटल पूर्णांक __init libcxgbi_init_module(व्योम)
अणु
	pr_info("%s", version);

	BUILD_BUG_ON(माप_field(काष्ठा sk_buff, cb) <
		     माप(काष्ठा cxgbi_skb_cb));
	rsvd_page = alloc_page(GFP_KERNEL | __GFP_ZERO);
	अगर (!rsvd_page)
		वापस -ENOMEM;

	वापस 0;
पूर्ण

अटल व्योम __निकास libcxgbi_निकास_module(व्योम)
अणु
	cxgbi_device_unरेजिस्टर_all(0xFF);
	put_page(rsvd_page);
	वापस;
पूर्ण

module_init(libcxgbi_init_module);
module_निकास(libcxgbi_निकास_module);
