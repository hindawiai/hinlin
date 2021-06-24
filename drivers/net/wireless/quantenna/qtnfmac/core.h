<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/* Copyright (c) 2015-2016 Quantenna Communications. All rights reserved. */

#अगर_अघोषित _QTN_FMAC_CORE_H_
#घोषणा _QTN_FMAC_CORE_H_

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/sched.h>
#समावेश <linux/semaphore.h>
#समावेश <linux/ip.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/अगर_arp.h>
#समावेश <linux/etherdevice.h>
#समावेश <net/sock.h>
#समावेश <net/lib80211.h>
#समावेश <net/cfg80211.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/firmware.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/workqueue.h>
#समावेश <linux/slab.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश "qlink.h"
#समावेश "trans.h"
#समावेश "qlink_util.h"

#अघोषित pr_fmt
#घोषणा pr_fmt(fmt)	KBUILD_MODNAME ": %s: " fmt, __func__

#घोषणा QTNF_MAX_VSIE_LEN		255
#घोषणा QTNF_MAX_INTF			8
#घोषणा QTNF_MAX_EVENT_QUEUE_LEN	255
#घोषणा QTNF_SCAN_TIMEOUT_SEC		15

#घोषणा QTNF_DEF_BSS_PRIORITY		0
#घोषणा QTNF_DEF_WDOG_TIMEOUT		5
#घोषणा QTNF_TX_TIMEOUT_TRSHLD		100

बाह्य स्थिर काष्ठा net_device_ops qtnf_netdev_ops;

काष्ठा qtnf_bus;
काष्ठा qtnf_vअगर;

काष्ठा qtnf_sta_node अणु
	काष्ठा list_head list;
	u8 mac_addr[ETH_ALEN];
पूर्ण;

काष्ठा qtnf_sta_list अणु
	काष्ठा list_head head;
	atomic_t size;
पूर्ण;

काष्ठा qtnf_vअगर अणु
	काष्ठा wireless_dev wdev;
	u8 bssid[ETH_ALEN];
	u8 mac_addr[ETH_ALEN];
	u8 vअगरid;
	u8 bss_priority;
	u8 bss_status;
	u16 mgmt_frames_biपंचांगask;
	काष्ठा net_device *netdev;
	काष्ठा qtnf_wmac *mac;

	काष्ठा work_काष्ठा reset_work;
	काष्ठा work_काष्ठा high_pri_tx_work;
	काष्ठा sk_buff_head high_pri_tx_queue;
	काष्ठा qtnf_sta_list sta_list;
	अचिन्हित दीर्घ cons_tx_समयout_cnt;
	पूर्णांक generation;
पूर्ण;

काष्ठा qtnf_mac_info अणु
	u8 bands_cap;
	u8 num_tx_chain;
	u8 num_rx_chain;
	u16 max_ap_assoc_sta;
	u32 frag_thr;
	u32 rts_thr;
	u8 lretry_limit;
	u8 sretry_limit;
	u8 coverage_class;
	u8 radar_detect_widths;
	u8 max_scan_ssids;
	u16 max_acl_mac_addrs;
	काष्ठा ieee80211_ht_cap ht_cap_mod_mask;
	काष्ठा ieee80211_vht_cap vht_cap_mod_mask;
	काष्ठा ieee80211_अगरace_combination *अगर_comb;
	माप_प्रकार n_अगर_comb;
	u8 *extended_capabilities;
	u8 *extended_capabilities_mask;
	u8 extended_capabilities_len;
	काष्ठा wiphy_wowlan_support *wowlan;
पूर्ण;

काष्ठा qtnf_wmac अणु
	u8 macid;
	u8 wiphy_रेजिस्टरed;
	u8 macaddr[ETH_ALEN];
	काष्ठा qtnf_bus *bus;
	काष्ठा qtnf_mac_info macinfo;
	काष्ठा qtnf_vअगर अगरlist[QTNF_MAX_INTF];
	काष्ठा cfg80211_scan_request *scan_req;
	काष्ठा mutex mac_lock;	/* lock during wmac speicअगरic ops */
	काष्ठा delayed_work scan_समयout;
	काष्ठा ieee80211_regकरोमुख्य *rd;
	काष्ठा platक्रमm_device *pdev;
पूर्ण;

काष्ठा qtnf_hw_info अणु
	u32 ql_proto_ver;
	u8 num_mac;
	u8 mac_biपंचांगap;
	u32 fw_ver;
	u8 total_tx_chain;
	u8 total_rx_chain;
	अक्षर fw_version[ETHTOOL_FWVERS_LEN];
	u32 hw_version;
	u8 hw_capab[QLINK_HW_CAPAB_NUM / BITS_PER_BYTE + 1];
पूर्ण;

काष्ठा qtnf_vअगर *qtnf_mac_get_मुक्त_vअगर(काष्ठा qtnf_wmac *mac);
काष्ठा qtnf_vअगर *qtnf_mac_get_base_vअगर(काष्ठा qtnf_wmac *mac);
व्योम qtnf_mac_अगरace_comb_मुक्त(काष्ठा qtnf_wmac *mac);
व्योम qtnf_mac_ext_caps_मुक्त(काष्ठा qtnf_wmac *mac);
bool qtnf_slave_radar_get(व्योम);
bool qtnf_dfs_offload_get(व्योम);
काष्ठा wiphy *qtnf_wiphy_allocate(काष्ठा qtnf_bus *bus,
				  काष्ठा platक्रमm_device *pdev);
पूर्णांक qtnf_core_net_attach(काष्ठा qtnf_wmac *mac, काष्ठा qtnf_vअगर *priv,
			 स्थिर अक्षर *name, अचिन्हित अक्षर name_assign_type);
व्योम qtnf_मुख्य_work_queue(काष्ठा work_काष्ठा *work);
पूर्णांक qtnf_cmd_send_update_phy_params(काष्ठा qtnf_wmac *mac, u32 changed);

काष्ठा qtnf_wmac *qtnf_core_get_mac(स्थिर काष्ठा qtnf_bus *bus, u8 macid);
काष्ठा net_device *qtnf_classअगरy_skb(काष्ठा qtnf_bus *bus, काष्ठा sk_buff *skb);
व्योम qtnf_wake_all_queues(काष्ठा net_device *ndev);

व्योम qtnf_भव_पूर्णांकf_cleanup(काष्ठा net_device *ndev);

व्योम qtnf_netdev_upकरोwn(काष्ठा net_device *ndev, bool up);
व्योम qtnf_scan_करोne(काष्ठा qtnf_wmac *mac, bool पातed);
काष्ठा dentry *qtnf_get_debugfs_dir(व्योम);
bool qtnf_netdev_is_qtn(स्थिर काष्ठा net_device *ndev);

अटल अंतरभूत काष्ठा qtnf_vअगर *qtnf_netdev_get_priv(काष्ठा net_device *dev)
अणु
	वापस *((व्योम **)netdev_priv(dev));
पूर्ण

अटल अंतरभूत bool qtnf_hwcap_is_set(स्थिर काष्ठा qtnf_hw_info *info,
				     अचिन्हित पूर्णांक bit)
अणु
	वापस qtnf_utils_is_bit_set(info->hw_capab, bit,
				     माप(info->hw_capab));
पूर्ण

#पूर्ण_अगर /* _QTN_FMAC_CORE_H_ */
