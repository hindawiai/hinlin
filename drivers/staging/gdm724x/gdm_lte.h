<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright (c) 2012 GCT Semiconductor, Inc. All rights reserved. */

#अगर_अघोषित _GDM_LTE_H_
#घोषणा _GDM_LTE_H_

#समावेश <linux/netdevice.h>
#समावेश <linux/types.h>

#समावेश "gdm_endian.h"

#घोषणा MAX_NIC_TYPE		4
#घोषणा MAX_RX_SUBMIT_COUNT	3
#घोषणा DRIVER_VERSION		"3.7.17.0"

क्रमागत TX_ERROR_CODE अणु
	TX_NO_ERROR = 0,
	TX_NO_DEV,
	TX_NO_SPC,
	TX_NO_BUFFER,
पूर्ण;

क्रमागत CALLBACK_CONTEXT अणु
	KERNEL_THREAD = 0,
	USB_COMPLETE,
पूर्ण;

काष्ठा pdn_table अणु
	u8 activate;
	u32 dft_eps_id;
	u32 nic_type;
पूर्ण __packed;

काष्ठा nic;

काष्ठा phy_dev अणु
	व्योम	*priv_dev;
	काष्ठा net_device *dev[MAX_NIC_TYPE];
	पूर्णांक	(*send_hci_func)(व्योम *priv_dev, व्योम *data, पूर्णांक len,
				 व्योम (*cb)(व्योम *cb_data), व्योम *cb_data);
	पूर्णांक	(*send_sdu_func)(व्योम *priv_dev, व्योम *data, पूर्णांक len,
				 अचिन्हित पूर्णांक dft_eps_id, अचिन्हित पूर्णांक eps_id,
				 व्योम (*cb)(व्योम *cb_data), व्योम *cb_data,
				 पूर्णांक dev_idx, पूर्णांक nic_type);
	पूर्णांक	(*rcv_func)(व्योम *priv_dev,
			    पूर्णांक (*cb)(व्योम *cb_data, व्योम *data, पूर्णांक len,
				      पूर्णांक context),
			    व्योम *cb_data, पूर्णांक context);
	u8 (*get_endian)(व्योम *priv_dev);
पूर्ण;

काष्ठा nic अणु
	काष्ठा net_device *netdev;
	काष्ठा phy_dev *phy_dev;
	काष्ठा net_device_stats stats;
	काष्ठा pdn_table pdn_table;
	u8 dest_mac_addr[ETH_ALEN];
	u8 src_mac_addr[ETH_ALEN];
	u32 nic_id;
	u16 vlan_id;
पूर्ण;

पूर्णांक gdm_lte_event_init(व्योम);
व्योम gdm_lte_event_निकास(व्योम);

व्योम start_rx_proc(काष्ठा phy_dev *phy_dev);
पूर्णांक रेजिस्टर_lte_device(काष्ठा phy_dev *phy_dev, काष्ठा device *dev,
			u8 *mac_address);
व्योम unरेजिस्टर_lte_device(काष्ठा phy_dev *phy_dev);

#पूर्ण_अगर /* _GDM_LTE_H_ */
