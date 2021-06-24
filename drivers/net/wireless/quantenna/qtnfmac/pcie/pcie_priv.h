<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/* Copyright (c) 2018 Quantenna Communications, Inc. All rights reserved. */

#अगर_अघोषित _QTN_FMAC_PCIE_H_
#घोषणा _QTN_FMAC_PCIE_H_

#समावेश <linux/pci.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/पन.स>
#समावेश <linux/skbuff.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/पूर्णांकerrupt.h>

#समावेश "shm_ipc.h"
#समावेश "bus.h"

#घोषणा SKB_BUF_SIZE		2048

#घोषणा QTN_FW_DL_TIMEOUT_MS	3000
#घोषणा QTN_FW_QLINK_TIMEOUT_MS	30000
#घोषणा QTN_EP_RESET_WAIT_MS	1000

काष्ठा qtnf_pcie_bus_priv अणु
	काष्ठा pci_dev *pdev;

	पूर्णांक (*probe_cb)(काष्ठा qtnf_bus *bus, अचिन्हित पूर्णांक tx_bd_size,
			अचिन्हित पूर्णांक rx_bd_size);
	व्योम (*हटाओ_cb)(काष्ठा qtnf_bus *bus);
	पूर्णांक (*suspend_cb)(काष्ठा qtnf_bus *bus);
	पूर्णांक (*resume_cb)(काष्ठा qtnf_bus *bus);
	u64 (*dma_mask_get_cb)(व्योम);

	spinlock_t tx_reclaim_lock;
	spinlock_t tx_lock;

	काष्ठा workqueue_काष्ठा *workqueue;
	काष्ठा tasklet_काष्ठा reclaim_tq;

	व्योम __iomem *sysctl_bar;
	व्योम __iomem *epmem_bar;
	व्योम __iomem *dmareg_bar;

	काष्ठा qtnf_shm_ipc shm_ipc_ep_in;
	काष्ठा qtnf_shm_ipc shm_ipc_ep_out;

	u16 tx_bd_num;
	u16 rx_bd_num;

	काष्ठा sk_buff **tx_skb;
	काष्ठा sk_buff **rx_skb;

	अचिन्हित पूर्णांक fw_blksize;

	u32 rx_bd_w_index;
	u32 rx_bd_r_index;

	u32 tx_bd_w_index;
	u32 tx_bd_r_index;

	/* diagnostics stats */
	u32 pcie_irq_count;
	u32 tx_full_count;
	u32 tx_करोne_count;
	u32 tx_reclaim_करोne;
	u32 tx_reclaim_req;

	u8 msi_enabled;
	u8 tx_stopped;
	bool flashboot;
पूर्ण;

पूर्णांक qtnf_pcie_control_tx(काष्ठा qtnf_bus *bus, काष्ठा sk_buff *skb);
पूर्णांक qtnf_pcie_alloc_skb_array(काष्ठा qtnf_pcie_bus_priv *priv);
पूर्णांक qtnf_pcie_fw_boot_करोne(काष्ठा qtnf_bus *bus);
व्योम qtnf_pcie_init_shm_ipc(काष्ठा qtnf_pcie_bus_priv *priv,
			    काष्ठा qtnf_shm_ipc_region __iomem *ipc_tx_reg,
			    काष्ठा qtnf_shm_ipc_region __iomem *ipc_rx_reg,
			    स्थिर काष्ठा qtnf_shm_ipc_पूर्णांक *ipc_पूर्णांक);
काष्ठा qtnf_bus *qtnf_pcie_pearl_alloc(काष्ठा pci_dev *pdev);
काष्ठा qtnf_bus *qtnf_pcie_topaz_alloc(काष्ठा pci_dev *pdev);

अटल अंतरभूत व्योम qtnf_non_posted_ग_लिखो(u32 val, व्योम __iomem *basereg)
अणु
	ग_लिखोl(val, basereg);

	/* flush posted ग_लिखो */
	पढ़ोl(basereg);
पूर्ण

#पूर्ण_अगर /* _QTN_FMAC_PCIE_H_ */
