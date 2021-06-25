<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0-only OR BSD-2-Clause)
/* Copyright (C) 2015-2018 Netronome Systems, Inc. */

/*
 * nfp_net_मुख्य.c
 * Netronome network device driver: Main entry poपूर्णांक
 * Authors: Jakub Kicinski <jakub.kicinski@netronome.com>
 *          Alejandro Lucero <alejandro.lucero@netronome.com>
 *          Jason McMullan <jason.mcmullan@netronome.com>
 *          Rolf Neugebauer <rolf.neugebauer@netronome.com>
 */

#समावेश <linux/etherdevice.h>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/lockdep.h>
#समावेश <linux/pci.h>
#समावेश <linux/pci_regs.h>
#समावेश <linux/msi.h>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/rtnetlink.h>

#समावेश "nfpcore/nfp.h"
#समावेश "nfpcore/nfp_cpp.h"
#समावेश "nfpcore/nfp_nffw.h"
#समावेश "nfpcore/nfp_nsp.h"
#समावेश "nfpcore/nfp6000_pcie.h"
#समावेश "nfp_app.h"
#समावेश "nfp_net_ctrl.h"
#समावेश "nfp_net_sriov.h"
#समावेश "nfp_net.h"
#समावेश "nfp_main.h"
#समावेश "nfp_port.h"

#घोषणा NFP_PF_CSR_SLICE_SIZE	(32 * 1024)

/**
 * nfp_net_get_mac_addr() - Get the MAC address.
 * @pf:       NFP PF handle
 * @netdev:   net_device to set MAC address on
 * @port:     NFP port काष्ठाure
 *
 * First try to get the MAC address from NSP ETH table. If that
 * fails generate a अक्रमom address.
 */
व्योम
nfp_net_get_mac_addr(काष्ठा nfp_pf *pf, काष्ठा net_device *netdev,
		     काष्ठा nfp_port *port)
अणु
	काष्ठा nfp_eth_table_port *eth_port;

	eth_port = __nfp_port_get_eth_port(port);
	अगर (!eth_port) अणु
		eth_hw_addr_अक्रमom(netdev);
		वापस;
	पूर्ण

	ether_addr_copy(netdev->dev_addr, eth_port->mac_addr);
	ether_addr_copy(netdev->perm_addr, eth_port->mac_addr);
पूर्ण

अटल काष्ठा nfp_eth_table_port *
nfp_net_find_port(काष्ठा nfp_eth_table *eth_tbl, अचिन्हित पूर्णांक index)
अणु
	पूर्णांक i;

	क्रम (i = 0; eth_tbl && i < eth_tbl->count; i++)
		अगर (eth_tbl->ports[i].index == index)
			वापस &eth_tbl->ports[i];

	वापस शून्य;
पूर्ण

अटल पूर्णांक nfp_net_pf_get_num_ports(काष्ठा nfp_pf *pf)
अणु
	वापस nfp_pf_rtsym_पढ़ो_optional(pf, "nfd_cfg_pf%u_num_ports", 1);
पूर्ण

अटल पूर्णांक nfp_net_pf_get_app_id(काष्ठा nfp_pf *pf)
अणु
	वापस nfp_pf_rtsym_पढ़ो_optional(pf, "_pf%u_net_app_id",
					  NFP_APP_CORE_NIC);
पूर्ण

अटल व्योम nfp_net_pf_मुक्त_vnic(काष्ठा nfp_pf *pf, काष्ठा nfp_net *nn)
अणु
	अगर (nfp_net_is_data_vnic(nn))
		nfp_app_vnic_मुक्त(pf->app, nn);
	nfp_port_मुक्त(nn->port);
	list_del(&nn->vnic_list);
	pf->num_vnics--;
	nfp_net_मुक्त(nn);
पूर्ण

अटल व्योम nfp_net_pf_मुक्त_vnics(काष्ठा nfp_pf *pf)
अणु
	काष्ठा nfp_net *nn, *next;

	list_क्रम_each_entry_safe(nn, next, &pf->vnics, vnic_list)
		अगर (nfp_net_is_data_vnic(nn))
			nfp_net_pf_मुक्त_vnic(pf, nn);
पूर्ण

अटल काष्ठा nfp_net *
nfp_net_pf_alloc_vnic(काष्ठा nfp_pf *pf, bool needs_netdev,
		      व्योम __iomem *ctrl_bar, व्योम __iomem *qc_bar,
		      पूर्णांक stride, अचिन्हित पूर्णांक id)
अणु
	u32 tx_base, rx_base, n_tx_rings, n_rx_rings;
	काष्ठा nfp_net *nn;
	पूर्णांक err;

	tx_base = पढ़ोl(ctrl_bar + NFP_NET_CFG_START_TXQ);
	rx_base = पढ़ोl(ctrl_bar + NFP_NET_CFG_START_RXQ);
	n_tx_rings = पढ़ोl(ctrl_bar + NFP_NET_CFG_MAX_TXRINGS);
	n_rx_rings = पढ़ोl(ctrl_bar + NFP_NET_CFG_MAX_RXRINGS);

	/* Allocate and initialise the vNIC */
	nn = nfp_net_alloc(pf->pdev, ctrl_bar, needs_netdev,
			   n_tx_rings, n_rx_rings);
	अगर (IS_ERR(nn))
		वापस nn;

	nn->app = pf->app;
	nfp_net_get_fw_version(&nn->fw_ver, ctrl_bar);
	nn->tx_bar = qc_bar + tx_base * NFP_QCP_QUEUE_ADDR_SZ;
	nn->rx_bar = qc_bar + rx_base * NFP_QCP_QUEUE_ADDR_SZ;
	nn->dp.is_vf = 0;
	nn->stride_rx = stride;
	nn->stride_tx = stride;

	अगर (needs_netdev) अणु
		err = nfp_app_vnic_alloc(pf->app, nn, id);
		अगर (err) अणु
			nfp_net_मुक्त(nn);
			वापस ERR_PTR(err);
		पूर्ण
	पूर्ण

	pf->num_vnics++;
	list_add_tail(&nn->vnic_list, &pf->vnics);

	वापस nn;
पूर्ण

अटल पूर्णांक
nfp_net_pf_init_vnic(काष्ठा nfp_pf *pf, काष्ठा nfp_net *nn, अचिन्हित पूर्णांक id)
अणु
	पूर्णांक err;

	nn->id = id;

	अगर (nn->port) अणु
		err = nfp_devlink_port_रेजिस्टर(pf->app, nn->port);
		अगर (err)
			वापस err;
	पूर्ण

	err = nfp_net_init(nn);
	अगर (err)
		जाओ err_devlink_port_clean;

	nfp_net_debugfs_vnic_add(nn, pf->ddir);

	अगर (nn->port)
		nfp_devlink_port_type_eth_set(nn->port);

	nfp_net_info(nn);

	अगर (nfp_net_is_data_vnic(nn)) अणु
		err = nfp_app_vnic_init(pf->app, nn);
		अगर (err)
			जाओ err_devlink_port_type_clean;
	पूर्ण

	वापस 0;

err_devlink_port_type_clean:
	अगर (nn->port)
		nfp_devlink_port_type_clear(nn->port);
	nfp_net_debugfs_dir_clean(&nn->debugfs_dir);
	nfp_net_clean(nn);
err_devlink_port_clean:
	अगर (nn->port)
		nfp_devlink_port_unरेजिस्टर(nn->port);
	वापस err;
पूर्ण

अटल पूर्णांक
nfp_net_pf_alloc_vnics(काष्ठा nfp_pf *pf, व्योम __iomem *ctrl_bar,
		       व्योम __iomem *qc_bar, पूर्णांक stride)
अणु
	काष्ठा nfp_net *nn;
	अचिन्हित पूर्णांक i;
	पूर्णांक err;

	क्रम (i = 0; i < pf->max_data_vnics; i++) अणु
		nn = nfp_net_pf_alloc_vnic(pf, true, ctrl_bar, qc_bar,
					   stride, i);
		अगर (IS_ERR(nn)) अणु
			err = PTR_ERR(nn);
			जाओ err_मुक्त_prev;
		पूर्ण

		ctrl_bar += NFP_PF_CSR_SLICE_SIZE;

		/* Kill the vNIC अगर app init marked it as invalid */
		अगर (nn->port && nn->port->type == NFP_PORT_INVALID)
			nfp_net_pf_मुक्त_vnic(pf, nn);
	पूर्ण

	अगर (list_empty(&pf->vnics))
		वापस -ENODEV;

	वापस 0;

err_मुक्त_prev:
	nfp_net_pf_मुक्त_vnics(pf);
	वापस err;
पूर्ण

अटल व्योम nfp_net_pf_clean_vnic(काष्ठा nfp_pf *pf, काष्ठा nfp_net *nn)
अणु
	अगर (nfp_net_is_data_vnic(nn))
		nfp_app_vnic_clean(pf->app, nn);
	अगर (nn->port)
		nfp_devlink_port_type_clear(nn->port);
	nfp_net_debugfs_dir_clean(&nn->debugfs_dir);
	nfp_net_clean(nn);
	अगर (nn->port)
		nfp_devlink_port_unरेजिस्टर(nn->port);
पूर्ण

अटल पूर्णांक nfp_net_pf_alloc_irqs(काष्ठा nfp_pf *pf)
अणु
	अचिन्हित पूर्णांक wanted_irqs, num_irqs, vnics_left, irqs_left;
	काष्ठा nfp_net *nn;

	/* Get MSI-X vectors */
	wanted_irqs = 0;
	list_क्रम_each_entry(nn, &pf->vnics, vnic_list)
		wanted_irqs += NFP_NET_NON_Q_VECTORS + nn->dp.num_r_vecs;
	pf->irq_entries = kसुस्मृति(wanted_irqs, माप(*pf->irq_entries),
				  GFP_KERNEL);
	अगर (!pf->irq_entries)
		वापस -ENOMEM;

	num_irqs = nfp_net_irqs_alloc(pf->pdev, pf->irq_entries,
				      NFP_NET_MIN_VNIC_IRQS * pf->num_vnics,
				      wanted_irqs);
	अगर (!num_irqs) अणु
		nfp_warn(pf->cpp, "Unable to allocate MSI-X vectors\n");
		kमुक्त(pf->irq_entries);
		वापस -ENOMEM;
	पूर्ण

	/* Distribute IRQs to vNICs */
	irqs_left = num_irqs;
	vnics_left = pf->num_vnics;
	list_क्रम_each_entry(nn, &pf->vnics, vnic_list) अणु
		अचिन्हित पूर्णांक n;

		n = min(NFP_NET_NON_Q_VECTORS + nn->dp.num_r_vecs,
			DIV_ROUND_UP(irqs_left, vnics_left));
		nfp_net_irqs_assign(nn, &pf->irq_entries[num_irqs - irqs_left],
				    n);
		irqs_left -= n;
		vnics_left--;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम nfp_net_pf_मुक्त_irqs(काष्ठा nfp_pf *pf)
अणु
	nfp_net_irqs_disable(pf->pdev);
	kमुक्त(pf->irq_entries);
पूर्ण

अटल पूर्णांक nfp_net_pf_init_vnics(काष्ठा nfp_pf *pf)
अणु
	काष्ठा nfp_net *nn;
	अचिन्हित पूर्णांक id;
	पूर्णांक err;

	/* Finish vNIC init and रेजिस्टर */
	id = 0;
	list_क्रम_each_entry(nn, &pf->vnics, vnic_list) अणु
		अगर (!nfp_net_is_data_vnic(nn))
			जारी;
		err = nfp_net_pf_init_vnic(pf, nn, id);
		अगर (err)
			जाओ err_prev_deinit;

		id++;
	पूर्ण

	वापस 0;

err_prev_deinit:
	list_क्रम_each_entry_जारी_reverse(nn, &pf->vnics, vnic_list)
		अगर (nfp_net_is_data_vnic(nn))
			nfp_net_pf_clean_vnic(pf, nn);
	वापस err;
पूर्ण

अटल पूर्णांक
nfp_net_pf_app_init(काष्ठा nfp_pf *pf, u8 __iomem *qc_bar, अचिन्हित पूर्णांक stride)
अणु
	u8 __iomem *ctrl_bar;
	पूर्णांक err;

	pf->app = nfp_app_alloc(pf, nfp_net_pf_get_app_id(pf));
	अगर (IS_ERR(pf->app))
		वापस PTR_ERR(pf->app);

	mutex_lock(&pf->lock);
	err = nfp_app_init(pf->app);
	mutex_unlock(&pf->lock);
	अगर (err)
		जाओ err_मुक्त;

	अगर (!nfp_app_needs_ctrl_vnic(pf->app))
		वापस 0;

	ctrl_bar = nfp_pf_map_rtsym(pf, "net.ctrl", "_pf%u_net_ctrl_bar",
				    NFP_PF_CSR_SLICE_SIZE, &pf->ctrl_vnic_bar);
	अगर (IS_ERR(ctrl_bar)) अणु
		nfp_err(pf->cpp, "Failed to find ctrl vNIC memory symbol\n");
		err = PTR_ERR(ctrl_bar);
		जाओ err_app_clean;
	पूर्ण

	pf->ctrl_vnic =	nfp_net_pf_alloc_vnic(pf, false, ctrl_bar, qc_bar,
					      stride, 0);
	अगर (IS_ERR(pf->ctrl_vnic)) अणु
		err = PTR_ERR(pf->ctrl_vnic);
		जाओ err_unmap;
	पूर्ण

	वापस 0;

err_unmap:
	nfp_cpp_area_release_मुक्त(pf->ctrl_vnic_bar);
err_app_clean:
	mutex_lock(&pf->lock);
	nfp_app_clean(pf->app);
	mutex_unlock(&pf->lock);
err_मुक्त:
	nfp_app_मुक्त(pf->app);
	pf->app = शून्य;
	वापस err;
पूर्ण

अटल व्योम nfp_net_pf_app_clean(काष्ठा nfp_pf *pf)
अणु
	अगर (pf->ctrl_vnic) अणु
		nfp_net_pf_मुक्त_vnic(pf, pf->ctrl_vnic);
		nfp_cpp_area_release_मुक्त(pf->ctrl_vnic_bar);
	पूर्ण

	mutex_lock(&pf->lock);
	nfp_app_clean(pf->app);
	mutex_unlock(&pf->lock);

	nfp_app_मुक्त(pf->app);
	pf->app = शून्य;
पूर्ण

अटल पूर्णांक nfp_net_pf_app_start_ctrl(काष्ठा nfp_pf *pf)
अणु
	पूर्णांक err;

	अगर (!pf->ctrl_vnic)
		वापस 0;
	err = nfp_net_pf_init_vnic(pf, pf->ctrl_vnic, 0);
	अगर (err)
		वापस err;

	err = nfp_ctrl_खोलो(pf->ctrl_vnic);
	अगर (err)
		जाओ err_clean_ctrl;

	वापस 0;

err_clean_ctrl:
	nfp_net_pf_clean_vnic(pf, pf->ctrl_vnic);
	वापस err;
पूर्ण

अटल व्योम nfp_net_pf_app_stop_ctrl(काष्ठा nfp_pf *pf)
अणु
	अगर (!pf->ctrl_vnic)
		वापस;
	nfp_ctrl_बंद(pf->ctrl_vnic);
	nfp_net_pf_clean_vnic(pf, pf->ctrl_vnic);
पूर्ण

अटल पूर्णांक nfp_net_pf_app_start(काष्ठा nfp_pf *pf)
अणु
	पूर्णांक err;

	err = nfp_net_pf_app_start_ctrl(pf);
	अगर (err)
		वापस err;

	err = nfp_app_start(pf->app, pf->ctrl_vnic);
	अगर (err)
		जाओ err_ctrl_stop;

	अगर (pf->num_vfs) अणु
		err = nfp_app_sriov_enable(pf->app, pf->num_vfs);
		अगर (err)
			जाओ err_app_stop;
	पूर्ण

	वापस 0;

err_app_stop:
	nfp_app_stop(pf->app);
err_ctrl_stop:
	nfp_net_pf_app_stop_ctrl(pf);
	वापस err;
पूर्ण

अटल व्योम nfp_net_pf_app_stop(काष्ठा nfp_pf *pf)
अणु
	अगर (pf->num_vfs)
		nfp_app_sriov_disable(pf->app);
	nfp_app_stop(pf->app);
	nfp_net_pf_app_stop_ctrl(pf);
पूर्ण

अटल व्योम nfp_net_pci_unmap_mem(काष्ठा nfp_pf *pf)
अणु
	अगर (pf->vfcfg_tbl2_area)
		nfp_cpp_area_release_मुक्त(pf->vfcfg_tbl2_area);
	अगर (pf->vf_cfg_bar)
		nfp_cpp_area_release_मुक्त(pf->vf_cfg_bar);
	अगर (pf->mac_stats_bar)
		nfp_cpp_area_release_मुक्त(pf->mac_stats_bar);
	nfp_cpp_area_release_मुक्त(pf->qc_area);
	nfp_cpp_area_release_मुक्त(pf->data_vnic_bar);
पूर्ण

अटल पूर्णांक nfp_net_pci_map_mem(काष्ठा nfp_pf *pf)
अणु
	u32 min_size, cpp_id;
	u8 __iomem *mem;
	पूर्णांक err;

	min_size = pf->max_data_vnics * NFP_PF_CSR_SLICE_SIZE;
	mem = nfp_pf_map_rtsym(pf, "net.bar0", "_pf%d_net_bar0",
			       min_size, &pf->data_vnic_bar);
	अगर (IS_ERR(mem)) अणु
		nfp_err(pf->cpp, "Failed to find data vNIC memory symbol\n");
		वापस PTR_ERR(mem);
	पूर्ण

	अगर (pf->eth_tbl) अणु
		min_size =  NFP_MAC_STATS_SIZE * (pf->eth_tbl->max_index + 1);
		pf->mac_stats_mem = nfp_rtsym_map(pf->rtbl, "_mac_stats",
						  "net.macstats", min_size,
						  &pf->mac_stats_bar);
		अगर (IS_ERR(pf->mac_stats_mem)) अणु
			अगर (PTR_ERR(pf->mac_stats_mem) != -ENOENT) अणु
				err = PTR_ERR(pf->mac_stats_mem);
				जाओ err_unmap_ctrl;
			पूर्ण
			pf->mac_stats_mem = शून्य;
		पूर्ण
	पूर्ण

	pf->vf_cfg_mem = nfp_pf_map_rtsym(pf, "net.vfcfg", "_pf%d_net_vf_bar",
					  NFP_NET_CFG_BAR_SZ * pf->limit_vfs,
					  &pf->vf_cfg_bar);
	अगर (IS_ERR(pf->vf_cfg_mem)) अणु
		अगर (PTR_ERR(pf->vf_cfg_mem) != -ENOENT) अणु
			err = PTR_ERR(pf->vf_cfg_mem);
			जाओ err_unmap_mac_stats;
		पूर्ण
		pf->vf_cfg_mem = शून्य;
	पूर्ण

	min_size = NFP_NET_VF_CFG_SZ * pf->limit_vfs + NFP_NET_VF_CFG_MB_SZ;
	pf->vfcfg_tbl2 = nfp_pf_map_rtsym(pf, "net.vfcfg_tbl2",
					  "_pf%d_net_vf_cfg2",
					  min_size, &pf->vfcfg_tbl2_area);
	अगर (IS_ERR(pf->vfcfg_tbl2)) अणु
		अगर (PTR_ERR(pf->vfcfg_tbl2) != -ENOENT) अणु
			err = PTR_ERR(pf->vfcfg_tbl2);
			जाओ err_unmap_vf_cfg;
		पूर्ण
		pf->vfcfg_tbl2 = शून्य;
	पूर्ण

	cpp_id = NFP_CPP_ISLAND_ID(0, NFP_CPP_ACTION_RW, 0, 0);
	mem = nfp_cpp_map_area(pf->cpp, "net.qc", cpp_id, NFP_PCIE_QUEUE(0),
			       NFP_QCP_QUEUE_AREA_SZ, &pf->qc_area);
	अगर (IS_ERR(mem)) अणु
		nfp_err(pf->cpp, "Failed to map Queue Controller area.\n");
		err = PTR_ERR(mem);
		जाओ err_unmap_vfcfg_tbl2;
	पूर्ण

	वापस 0;

err_unmap_vfcfg_tbl2:
	अगर (pf->vfcfg_tbl2_area)
		nfp_cpp_area_release_मुक्त(pf->vfcfg_tbl2_area);
err_unmap_vf_cfg:
	अगर (pf->vf_cfg_bar)
		nfp_cpp_area_release_मुक्त(pf->vf_cfg_bar);
err_unmap_mac_stats:
	अगर (pf->mac_stats_bar)
		nfp_cpp_area_release_मुक्त(pf->mac_stats_bar);
err_unmap_ctrl:
	nfp_cpp_area_release_मुक्त(pf->data_vnic_bar);
	वापस err;
पूर्ण

अटल पूर्णांक
nfp_net_eth_port_update(काष्ठा nfp_cpp *cpp, काष्ठा nfp_port *port,
			काष्ठा nfp_eth_table *eth_table)
अणु
	काष्ठा nfp_eth_table_port *eth_port;

	ASSERT_RTNL();

	eth_port = nfp_net_find_port(eth_table, port->eth_id);
	अगर (!eth_port) अणु
		set_bit(NFP_PORT_CHANGED, &port->flags);
		nfp_warn(cpp, "Warning: port #%d not present after reconfig\n",
			 port->eth_id);
		वापस -EIO;
	पूर्ण
	अगर (eth_port->override_changed) अणु
		nfp_warn(cpp, "Port #%d config changed, unregistering. Driver reload required before port will be operational again.\n", port->eth_id);
		port->type = NFP_PORT_INVALID;
	पूर्ण

	स_नकल(port->eth_port, eth_port, माप(*eth_port));

	वापस 0;
पूर्ण

पूर्णांक nfp_net_refresh_port_table_sync(काष्ठा nfp_pf *pf)
अणु
	काष्ठा nfp_eth_table *eth_table;
	काष्ठा nfp_net *nn, *next;
	काष्ठा nfp_port *port;
	पूर्णांक err;

	lockdep_निश्चित_held(&pf->lock);

	/* Check क्रम nfp_net_pci_हटाओ() racing against us */
	अगर (list_empty(&pf->vnics))
		वापस 0;

	/* Update state of all ports */
	rtnl_lock();
	list_क्रम_each_entry(port, &pf->ports, port_list)
		clear_bit(NFP_PORT_CHANGED, &port->flags);

	eth_table = nfp_eth_पढ़ो_ports(pf->cpp);
	अगर (!eth_table) अणु
		list_क्रम_each_entry(port, &pf->ports, port_list)
			अगर (__nfp_port_get_eth_port(port))
				set_bit(NFP_PORT_CHANGED, &port->flags);
		rtnl_unlock();
		nfp_err(pf->cpp, "Error refreshing port config!\n");
		वापस -EIO;
	पूर्ण

	list_क्रम_each_entry(port, &pf->ports, port_list)
		अगर (__nfp_port_get_eth_port(port))
			nfp_net_eth_port_update(pf->cpp, port, eth_table);
	rtnl_unlock();

	kमुक्त(eth_table);

	/* Resync repr state. This may cause reprs to be हटाओd. */
	err = nfp_reprs_resync_phys_ports(pf->app);
	अगर (err)
		वापस err;

	/* Shoot off the ports which became invalid */
	list_क्रम_each_entry_safe(nn, next, &pf->vnics, vnic_list) अणु
		अगर (!nn->port || nn->port->type != NFP_PORT_INVALID)
			जारी;

		nfp_net_pf_clean_vnic(pf, nn);
		nfp_net_pf_मुक्त_vnic(pf, nn);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम nfp_net_refresh_vnics(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा nfp_pf *pf = container_of(work, काष्ठा nfp_pf,
					 port_refresh_work);

	mutex_lock(&pf->lock);
	nfp_net_refresh_port_table_sync(pf);
	mutex_unlock(&pf->lock);
पूर्ण

व्योम nfp_net_refresh_port_table(काष्ठा nfp_port *port)
अणु
	काष्ठा nfp_pf *pf = port->app->pf;

	set_bit(NFP_PORT_CHANGED, &port->flags);

	queue_work(pf->wq, &pf->port_refresh_work);
पूर्ण

पूर्णांक nfp_net_refresh_eth_port(काष्ठा nfp_port *port)
अणु
	काष्ठा nfp_cpp *cpp = port->app->cpp;
	काष्ठा nfp_eth_table *eth_table;
	पूर्णांक ret;

	clear_bit(NFP_PORT_CHANGED, &port->flags);

	eth_table = nfp_eth_पढ़ो_ports(cpp);
	अगर (!eth_table) अणु
		set_bit(NFP_PORT_CHANGED, &port->flags);
		nfp_err(cpp, "Error refreshing port state table!\n");
		वापस -EIO;
	पूर्ण

	ret = nfp_net_eth_port_update(cpp, port, eth_table);

	kमुक्त(eth_table);

	वापस ret;
पूर्ण

/*
 * PCI device functions
 */
पूर्णांक nfp_net_pci_probe(काष्ठा nfp_pf *pf)
अणु
	काष्ठा devlink *devlink = priv_to_devlink(pf);
	काष्ठा nfp_net_fw_version fw_ver;
	u8 __iomem *ctrl_bar, *qc_bar;
	पूर्णांक stride;
	पूर्णांक err;

	INIT_WORK(&pf->port_refresh_work, nfp_net_refresh_vnics);

	अगर (!pf->rtbl) अणु
		nfp_err(pf->cpp, "No %s, giving up.\n",
			pf->fw_loaded ? "symbol table" : "firmware found");
		वापस -EINVAL;
	पूर्ण

	pf->max_data_vnics = nfp_net_pf_get_num_ports(pf);
	अगर ((पूर्णांक)pf->max_data_vnics < 0)
		वापस pf->max_data_vnics;

	err = nfp_net_pci_map_mem(pf);
	अगर (err)
		वापस err;

	ctrl_bar = nfp_cpp_area_iomem(pf->data_vnic_bar);
	qc_bar = nfp_cpp_area_iomem(pf->qc_area);
	अगर (!ctrl_bar || !qc_bar) अणु
		err = -EIO;
		जाओ err_unmap;
	पूर्ण

	nfp_net_get_fw_version(&fw_ver, ctrl_bar);
	अगर (fw_ver.resv || fw_ver.class != NFP_NET_CFG_VERSION_CLASS_GENERIC) अणु
		nfp_err(pf->cpp, "Unknown Firmware ABI %d.%d.%d.%d\n",
			fw_ver.resv, fw_ver.class, fw_ver.major, fw_ver.minor);
		err = -EINVAL;
		जाओ err_unmap;
	पूर्ण

	/* Determine stride */
	अगर (nfp_net_fw_ver_eq(&fw_ver, 0, 0, 0, 1)) अणु
		stride = 2;
		nfp_warn(pf->cpp, "OBSOLETE Firmware detected - VF isolation not available\n");
	पूर्ण अन्यथा अणु
		चयन (fw_ver.major) अणु
		हाल 1 ... 5:
			stride = 4;
			अवरोध;
		शेष:
			nfp_err(pf->cpp, "Unsupported Firmware ABI %d.%d.%d.%d\n",
				fw_ver.resv, fw_ver.class,
				fw_ver.major, fw_ver.minor);
			err = -EINVAL;
			जाओ err_unmap;
		पूर्ण
	पूर्ण

	err = nfp_net_pf_app_init(pf, qc_bar, stride);
	अगर (err)
		जाओ err_unmap;

	err = devlink_रेजिस्टर(devlink, &pf->pdev->dev);
	अगर (err)
		जाओ err_app_clean;

	err = nfp_shared_buf_रेजिस्टर(pf);
	अगर (err)
		जाओ err_devlink_unreg;

	err = nfp_devlink_params_रेजिस्टर(pf);
	अगर (err)
		जाओ err_shared_buf_unreg;

	mutex_lock(&pf->lock);
	pf->ddir = nfp_net_debugfs_device_add(pf->pdev);

	/* Allocate the vnics and करो basic init */
	err = nfp_net_pf_alloc_vnics(pf, ctrl_bar, qc_bar, stride);
	अगर (err)
		जाओ err_clean_ddir;

	err = nfp_net_pf_alloc_irqs(pf);
	अगर (err)
		जाओ err_मुक्त_vnics;

	err = nfp_net_pf_app_start(pf);
	अगर (err)
		जाओ err_मुक्त_irqs;

	err = nfp_net_pf_init_vnics(pf);
	अगर (err)
		जाओ err_stop_app;

	mutex_unlock(&pf->lock);

	वापस 0;

err_stop_app:
	nfp_net_pf_app_stop(pf);
err_मुक्त_irqs:
	nfp_net_pf_मुक्त_irqs(pf);
err_मुक्त_vnics:
	nfp_net_pf_मुक्त_vnics(pf);
err_clean_ddir:
	nfp_net_debugfs_dir_clean(&pf->ddir);
	mutex_unlock(&pf->lock);
	nfp_devlink_params_unरेजिस्टर(pf);
err_shared_buf_unreg:
	nfp_shared_buf_unरेजिस्टर(pf);
err_devlink_unreg:
	cancel_work_sync(&pf->port_refresh_work);
	devlink_unरेजिस्टर(devlink);
err_app_clean:
	nfp_net_pf_app_clean(pf);
err_unmap:
	nfp_net_pci_unmap_mem(pf);
	वापस err;
पूर्ण

व्योम nfp_net_pci_हटाओ(काष्ठा nfp_pf *pf)
अणु
	काष्ठा nfp_net *nn, *next;

	mutex_lock(&pf->lock);
	list_क्रम_each_entry_safe(nn, next, &pf->vnics, vnic_list) अणु
		अगर (!nfp_net_is_data_vnic(nn))
			जारी;
		nfp_net_pf_clean_vnic(pf, nn);
		nfp_net_pf_मुक्त_vnic(pf, nn);
	पूर्ण

	nfp_net_pf_app_stop(pf);
	/* stop app first, to aव्योम द्विगुन मुक्त of ctrl vNIC's ddir */
	nfp_net_debugfs_dir_clean(&pf->ddir);

	mutex_unlock(&pf->lock);

	nfp_devlink_params_unरेजिस्टर(pf);
	nfp_shared_buf_unरेजिस्टर(pf);
	devlink_unरेजिस्टर(priv_to_devlink(pf));

	nfp_net_pf_मुक्त_irqs(pf);
	nfp_net_pf_app_clean(pf);
	nfp_net_pci_unmap_mem(pf);

	cancel_work_sync(&pf->port_refresh_work);
पूर्ण
