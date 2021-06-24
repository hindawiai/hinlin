<शैली गुरु>
/* SPDX-License-Identअगरier: (GPL-2.0+ OR BSD-3-Clause) */
/* Copyright 2017-2019 NXP */

#समावेश "enetc.h"
#समावेश <linux/pcs-lynx.h>

#घोषणा ENETC_PF_NUM_RINGS	8

क्रमागत enetc_mac_addr_type अणुUC, MC, MADDR_TYPEपूर्ण;
#घोषणा ENETC_MAX_NUM_MAC_FLT	((ENETC_MAX_NUM_VFS + 1) * MADDR_TYPE)

#घोषणा ENETC_MADDR_HASH_TBL_SZ	64
काष्ठा enetc_mac_filter अणु
	जोड़ अणु
		अक्षर mac_addr[ETH_ALEN];
		DECLARE_BITMAP(mac_hash_table, ENETC_MADDR_HASH_TBL_SZ);
	पूर्ण;
	पूर्णांक mac_addr_cnt;
पूर्ण;

#घोषणा ENETC_VLAN_HT_SIZE	64

क्रमागत enetc_vf_flags अणु
	ENETC_VF_FLAG_PF_SET_MAC	= BIT(0),
पूर्ण;

काष्ठा enetc_vf_state अणु
	क्रमागत enetc_vf_flags flags;
पूर्ण;

काष्ठा enetc_pf अणु
	काष्ठा enetc_si *si;
	पूर्णांक num_vfs; /* number of active VFs, after sriov_init */
	पूर्णांक total_vfs; /* max number of VFs, set क्रम PF at probe */
	काष्ठा enetc_vf_state *vf_state;

	काष्ठा enetc_mac_filter mac_filter[ENETC_MAX_NUM_MAC_FLT];

	काष्ठा enetc_msg_swbd rxmsg[ENETC_MAX_NUM_VFS];
	काष्ठा work_काष्ठा msg_task;
	अक्षर msg_पूर्णांक_name[ENETC_INT_NAME_MAX];

	अक्षर vlan_promisc_simap; /* biपंचांगap of SIs in VLAN promisc mode */
	DECLARE_BITMAP(vlan_ht_filter, ENETC_VLAN_HT_SIZE);
	DECLARE_BITMAP(active_vlans, VLAN_N_VID);

	काष्ठा mii_bus *mdio; /* saved क्रम cleanup */
	काष्ठा mii_bus *imdio;
	काष्ठा lynx_pcs *pcs;

	phy_पूर्णांकerface_t अगर_mode;
	काष्ठा phylink_config phylink_config;
पूर्ण;

#घोषणा phylink_to_enetc_pf(config) \
	container_of((config), काष्ठा enetc_pf, phylink_config)

पूर्णांक enetc_msg_psi_init(काष्ठा enetc_pf *pf);
व्योम enetc_msg_psi_मुक्त(काष्ठा enetc_pf *pf);
व्योम enetc_msg_handle_rxmsg(काष्ठा enetc_pf *pf, पूर्णांक mbox_id, u16 *status);
