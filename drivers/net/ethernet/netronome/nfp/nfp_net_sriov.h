<शैली गुरु>
/* SPDX-License-Identअगरier: (GPL-2.0-only OR BSD-2-Clause) */
/* Copyright (C) 2017-2019 Netronome Systems, Inc. */

#अगर_अघोषित _NFP_NET_SRIOV_H_
#घोषणा _NFP_NET_SRIOV_H_

/**
 * SRIOV VF configuration.
 * The configuration memory begins with a mailbox region क्रम communication with
 * the firmware followed by inभागidual VF entries.
 */
#घोषणा NFP_NET_VF_CFG_SZ		16
#घोषणा NFP_NET_VF_CFG_MB_SZ		16

/* VF config mailbox */
#घोषणा NFP_NET_VF_CFG_MB				0x0
#घोषणा NFP_NET_VF_CFG_MB_CAP				0x0
#घोषणा   NFP_NET_VF_CFG_MB_CAP_MAC			  (0x1 << 0)
#घोषणा   NFP_NET_VF_CFG_MB_CAP_VLAN			  (0x1 << 1)
#घोषणा   NFP_NET_VF_CFG_MB_CAP_SPOOF			  (0x1 << 2)
#घोषणा   NFP_NET_VF_CFG_MB_CAP_LINK_STATE		  (0x1 << 3)
#घोषणा   NFP_NET_VF_CFG_MB_CAP_TRUST			  (0x1 << 4)
#घोषणा NFP_NET_VF_CFG_MB_RET				0x2
#घोषणा NFP_NET_VF_CFG_MB_UPD				0x4
#घोषणा   NFP_NET_VF_CFG_MB_UPD_MAC			  (0x1 << 0)
#घोषणा   NFP_NET_VF_CFG_MB_UPD_VLAN			  (0x1 << 1)
#घोषणा   NFP_NET_VF_CFG_MB_UPD_SPOOF			  (0x1 << 2)
#घोषणा   NFP_NET_VF_CFG_MB_UPD_LINK_STATE		  (0x1 << 3)
#घोषणा   NFP_NET_VF_CFG_MB_UPD_TRUST			  (0x1 << 4)
#घोषणा NFP_NET_VF_CFG_MB_VF_NUM			0x7

/* VF config entry
 * MAC_LO is set that the MAC address can be पढ़ो in a single 6 byte पढ़ो
 * by the NFP
 */
#घोषणा NFP_NET_VF_CFG_MAC				0x0
#घोषणा   NFP_NET_VF_CFG_MAC_HI				  0x0
#घोषणा   NFP_NET_VF_CFG_MAC_LO				  0x6
#घोषणा NFP_NET_VF_CFG_CTRL				0x4
#घोषणा   NFP_NET_VF_CFG_CTRL_TRUST			  0x8
#घोषणा   NFP_NET_VF_CFG_CTRL_SPOOF			  0x4
#घोषणा   NFP_NET_VF_CFG_CTRL_LINK_STATE		  0x3
#घोषणा     NFP_NET_VF_CFG_LS_MODE_AUTO			    0
#घोषणा     NFP_NET_VF_CFG_LS_MODE_ENABLE		    1
#घोषणा     NFP_NET_VF_CFG_LS_MODE_DISABLE		    2
#घोषणा NFP_NET_VF_CFG_VLAN				0x8
#घोषणा   NFP_NET_VF_CFG_VLAN_QOS			  0xe000
#घोषणा   NFP_NET_VF_CFG_VLAN_VID			  0x0fff

पूर्णांक nfp_app_set_vf_mac(काष्ठा net_device *netdev, पूर्णांक vf, u8 *mac);
पूर्णांक nfp_app_set_vf_vlan(काष्ठा net_device *netdev, पूर्णांक vf, u16 vlan, u8 qos,
			__be16 vlan_proto);
पूर्णांक nfp_app_set_vf_spoofchk(काष्ठा net_device *netdev, पूर्णांक vf, bool setting);
पूर्णांक nfp_app_set_vf_trust(काष्ठा net_device *netdev, पूर्णांक vf, bool setting);
पूर्णांक nfp_app_set_vf_link_state(काष्ठा net_device *netdev, पूर्णांक vf,
			      पूर्णांक link_state);
पूर्णांक nfp_app_get_vf_config(काष्ठा net_device *netdev, पूर्णांक vf,
			  काष्ठा अगरla_vf_info *ivi);

#पूर्ण_अगर /* _NFP_NET_SRIOV_H_ */
