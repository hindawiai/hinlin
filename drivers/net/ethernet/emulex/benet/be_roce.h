<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2005 - 2016 Broadcom
 * All rights reserved.
 *
 * Contact Inक्रमmation:
 * linux-drivers@emulex.com
 *
 * Emulex
 * 3333 Susan Street
 * Costa Mesa, CA 92626
 */

#अगर_अघोषित BE_ROCE_H
#घोषणा BE_ROCE_H

#समावेश <linux/pci.h>
#समावेश <linux/netdevice.h>

#घोषणा BE_ROCE_ABI_VERSION	1

काष्ठा ocrdma_dev;

क्रमागत be_पूर्णांकerrupt_mode अणु
	BE_INTERRUPT_MODE_MSIX	= 0,
	BE_INTERRUPT_MODE_INTX	= 1,
	BE_INTERRUPT_MODE_MSI	= 2,
पूर्ण;

#घोषणा MAX_MSIX_VECTORS		32
काष्ठा be_dev_info अणु
	u8 __iomem *db;
	u64 unmapped_db;
	u32 db_page_size;
	u32 db_total_size;
	u64 dpp_unmapped_addr;
	u32 dpp_unmapped_len;
	काष्ठा pci_dev *pdev;
	काष्ठा net_device *netdev;
	u8 mac_addr[ETH_ALEN];
	u32 dev_family;
	क्रमागत be_पूर्णांकerrupt_mode पूर्णांकr_mode;
	काष्ठा अणु
		पूर्णांक num_vectors;
		पूर्णांक start_vector;
		u32 vector_list[MAX_MSIX_VECTORS];
	पूर्ण msix;
पूर्ण;

/* ocrdma driver रेजिस्टर's the callback functions with nic driver. */
काष्ठा ocrdma_driver अणु
	अचिन्हित अक्षर name[32];
	u32 be_abi_version;
	काष्ठा ocrdma_dev *(*add) (काष्ठा be_dev_info *dev_info);
	व्योम (*हटाओ) (काष्ठा ocrdma_dev *);
	व्योम (*state_change_handler) (काष्ठा ocrdma_dev *, u32 new_state);
पूर्ण;

क्रमागत be_roce_event अणु
	BE_DEV_SHUTDOWN = 2
पूर्ण;

/* APIs क्रम RoCE driver to रेजिस्टर callback handlers,
 * which will be invoked when device is added, हटाओd, अगरup, अगरकरोwn
 */
पूर्णांक be_roce_रेजिस्टर_driver(काष्ठा ocrdma_driver *drv);
व्योम be_roce_unरेजिस्टर_driver(काष्ठा ocrdma_driver *drv);

/* API क्रम RoCE driver to issue mailbox commands */
पूर्णांक be_roce_mcc_cmd(व्योम *netdev_handle, व्योम *wrb_payload,
		    पूर्णांक wrb_payload_size, u16 *cmd_status, u16 *ext_status);

#पूर्ण_अगर /* BE_ROCE_H */
