<शैली गुरु>
/* SPDX-License-Identअगरier: (GPL-2.0-only OR BSD-2-Clause) */
/* Copyright (C) 2015-2018 Netronome Systems, Inc. */

/*
 * nfp_मुख्य.h
 * Author: Jason McMullan <jason.mcmullan@netronome.com>
 */

#अगर_अघोषित NFP_MAIN_H
#घोषणा NFP_MAIN_H

#समावेश <linux/ethtool.h>
#समावेश <linux/list.h>
#समावेश <linux/types.h>
#समावेश <linux/msi.h>
#समावेश <linux/mutex.h>
#समावेश <linux/pci.h>
#समावेश <linux/workqueue.h>
#समावेश <net/devlink.h>

काष्ठा dentry;
काष्ठा device;
काष्ठा pci_dev;

काष्ठा nfp_cpp;
काष्ठा nfp_cpp_area;
काष्ठा nfp_eth_table;
काष्ठा nfp_hwinfo;
काष्ठा nfp_mip;
काष्ठा nfp_net;
काष्ठा nfp_nsp_identअगरy;
काष्ठा nfp_port;
काष्ठा nfp_rtsym;
काष्ठा nfp_rtsym_table;
काष्ठा nfp_shared_buf;

/**
 * काष्ठा nfp_dumpspec - NFP FW dump specअगरication काष्ठाure
 * @size:	Size of the data
 * @data:	Sequence of TLVs, each being an inकाष्ठाion to dump some data
 *		from FW
 */
काष्ठा nfp_dumpspec अणु
	u32 size;
	u8 data[];
पूर्ण;

/**
 * काष्ठा nfp_pf - NFP PF-specअगरic device काष्ठाure
 * @pdev:		Backpoपूर्णांकer to PCI device
 * @cpp:		Poपूर्णांकer to the CPP handle
 * @app:		Poपूर्णांकer to the APP handle
 * @data_vnic_bar:	Poपूर्णांकer to the CPP area क्रम the data vNICs' BARs
 * @ctrl_vnic_bar:	Poपूर्णांकer to the CPP area क्रम the ctrl vNIC's BAR
 * @qc_area:		Poपूर्णांकer to the CPP area क्रम the queues
 * @mac_stats_bar:	Poपूर्णांकer to the CPP area क्रम the MAC stats
 * @mac_stats_mem:	Poपूर्णांकer to mapped MAC stats area
 * @vf_cfg_bar:		Poपूर्णांकer to the CPP area क्रम the VF configuration BAR
 * @vf_cfg_mem:		Poपूर्णांकer to mapped VF configuration area
 * @vfcfg_tbl2_area:	Poपूर्णांकer to the CPP area क्रम the VF config table
 * @vfcfg_tbl2:		Poपूर्णांकer to mapped VF config table
 * @mbox:		RTSym of per-PCI PF mailbox (under devlink lock)
 * @irq_entries:	Array of MSI-X entries क्रम all vNICs
 * @limit_vfs:		Number of VFs supported by firmware (~0 क्रम PCI limit)
 * @num_vfs:		Number of SR-IOV VFs enabled
 * @fw_loaded:		Is the firmware loaded?
 * @unload_fw_on_हटाओ:Do we need to unload firmware on driver removal?
 * @ctrl_vnic:		Poपूर्णांकer to the control vNIC अगर available
 * @mip:		MIP handle
 * @rtbl:		RTsym table
 * @hwinfo:		HWInfo table
 * @dumpspec:		Debug dump specअगरication
 * @dump_flag:		Store dump flag between set_dump and get_dump_flag
 * @dump_len:		Store dump length between set_dump and get_dump_flag
 * @eth_tbl:		NSP ETH table
 * @nspi:		NSP identअगरication info
 * @hwmon_dev:		poपूर्णांकer to hwmon device
 * @ddir:		Per-device debugfs directory
 * @max_data_vnics:	Number of data vNICs app firmware supports
 * @num_vnics:		Number of vNICs spawned
 * @vnics:		Linked list of vNIC काष्ठाures (काष्ठा nfp_net)
 * @ports:		Linked list of port काष्ठाures (काष्ठा nfp_port)
 * @wq:			Workqueue क्रम running works which need to grab @lock
 * @port_refresh_work:	Work entry क्रम taking netdevs out
 * @shared_bufs:	Array of shared buffer काष्ठाures अगर FW has any SBs
 * @num_shared_bufs:	Number of elements in @shared_bufs
 * @lock:		Protects all fields which may change after probe
 */
काष्ठा nfp_pf अणु
	काष्ठा pci_dev *pdev;

	काष्ठा nfp_cpp *cpp;

	काष्ठा nfp_app *app;

	काष्ठा nfp_cpp_area *data_vnic_bar;
	काष्ठा nfp_cpp_area *ctrl_vnic_bar;
	काष्ठा nfp_cpp_area *qc_area;
	काष्ठा nfp_cpp_area *mac_stats_bar;
	u8 __iomem *mac_stats_mem;
	काष्ठा nfp_cpp_area *vf_cfg_bar;
	u8 __iomem *vf_cfg_mem;
	काष्ठा nfp_cpp_area *vfcfg_tbl2_area;
	u8 __iomem *vfcfg_tbl2;

	स्थिर काष्ठा nfp_rtsym *mbox;

	काष्ठा msix_entry *irq_entries;

	अचिन्हित पूर्णांक limit_vfs;
	अचिन्हित पूर्णांक num_vfs;

	bool fw_loaded;
	bool unload_fw_on_हटाओ;

	काष्ठा nfp_net *ctrl_vnic;

	स्थिर काष्ठा nfp_mip *mip;
	काष्ठा nfp_rtsym_table *rtbl;
	काष्ठा nfp_hwinfo *hwinfo;
	काष्ठा nfp_dumpspec *dumpspec;
	u32 dump_flag;
	u32 dump_len;
	काष्ठा nfp_eth_table *eth_tbl;
	काष्ठा nfp_nsp_identअगरy *nspi;

	काष्ठा device *hwmon_dev;

	काष्ठा dentry *ddir;

	अचिन्हित पूर्णांक max_data_vnics;
	अचिन्हित पूर्णांक num_vnics;

	काष्ठा list_head vnics;
	काष्ठा list_head ports;

	काष्ठा workqueue_काष्ठा *wq;
	काष्ठा work_काष्ठा port_refresh_work;

	काष्ठा nfp_shared_buf *shared_bufs;
	अचिन्हित पूर्णांक num_shared_bufs;

	काष्ठा mutex lock;
पूर्ण;

बाह्य काष्ठा pci_driver nfp_netvf_pci_driver;

बाह्य स्थिर काष्ठा devlink_ops nfp_devlink_ops;

पूर्णांक nfp_net_pci_probe(काष्ठा nfp_pf *pf);
व्योम nfp_net_pci_हटाओ(काष्ठा nfp_pf *pf);

पूर्णांक nfp_hwmon_रेजिस्टर(काष्ठा nfp_pf *pf);
व्योम nfp_hwmon_unरेजिस्टर(काष्ठा nfp_pf *pf);

व्योम
nfp_net_get_mac_addr(काष्ठा nfp_pf *pf, काष्ठा net_device *netdev,
		     काष्ठा nfp_port *port);

bool nfp_ctrl_tx(काष्ठा nfp_net *nn, काष्ठा sk_buff *skb);

पूर्णांक nfp_pf_rtsym_पढ़ो_optional(काष्ठा nfp_pf *pf, स्थिर अक्षर *क्रमmat,
			       अचिन्हित पूर्णांक शेष_val);
u8 __iomem *
nfp_pf_map_rtsym(काष्ठा nfp_pf *pf, स्थिर अक्षर *name, स्थिर अक्षर *sym_fmt,
		 अचिन्हित पूर्णांक min_size, काष्ठा nfp_cpp_area **area);
पूर्णांक nfp_mbox_cmd(काष्ठा nfp_pf *pf, u32 cmd, व्योम *in_data, u64 in_length,
		 व्योम *out_data, u64 out_length);
पूर्णांक nfp_flash_update_common(काष्ठा nfp_pf *pf, स्थिर काष्ठा firmware *fw,
			    काष्ठा netlink_ext_ack *extack);

क्रमागत nfp_dump_diag अणु
	NFP_DUMP_NSP_DIAG = 0,
पूर्ण;

काष्ठा nfp_dumpspec *
nfp_net_dump_load_dumpspec(काष्ठा nfp_cpp *cpp, काष्ठा nfp_rtsym_table *rtbl);
s64 nfp_net_dump_calculate_size(काष्ठा nfp_pf *pf, काष्ठा nfp_dumpspec *spec,
				u32 flag);
पूर्णांक nfp_net_dump_populate_buffer(काष्ठा nfp_pf *pf, काष्ठा nfp_dumpspec *spec,
				 काष्ठा ethtool_dump *dump_param, व्योम *dest);

पूर्णांक nfp_shared_buf_रेजिस्टर(काष्ठा nfp_pf *pf);
व्योम nfp_shared_buf_unरेजिस्टर(काष्ठा nfp_pf *pf);
पूर्णांक nfp_shared_buf_pool_get(काष्ठा nfp_pf *pf, अचिन्हित पूर्णांक sb, u16 pool_index,
			    काष्ठा devlink_sb_pool_info *pool_info);
पूर्णांक nfp_shared_buf_pool_set(काष्ठा nfp_pf *pf, अचिन्हित पूर्णांक sb,
			    u16 pool_index, u32 size,
			    क्रमागत devlink_sb_threshold_type threshold_type);

पूर्णांक nfp_devlink_params_रेजिस्टर(काष्ठा nfp_pf *pf);
व्योम nfp_devlink_params_unरेजिस्टर(काष्ठा nfp_pf *pf);
#पूर्ण_अगर /* NFP_MAIN_H */
