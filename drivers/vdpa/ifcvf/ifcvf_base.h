<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Intel IFC VF NIC driver क्रम virtio dataplane offloading
 *
 * Copyright (C) 2020 Intel Corporation.
 *
 * Author: Zhu Lingshan <lingshan.zhu@पूर्णांकel.com>
 *
 */

#अगर_अघोषित _IFCVF_H_
#घोषणा _IFCVF_H_

#समावेश <linux/pci.h>
#समावेश <linux/pci_regs.h>
#समावेश <linux/vdpa.h>
#समावेश <uapi/linux/virtio_net.h>
#समावेश <uapi/linux/virtio_blk.h>
#समावेश <uapi/linux/virtio_config.h>
#समावेश <uapi/linux/virtio_pci.h>

#घोषणा N3000_VENDOR_ID		0x1AF4
#घोषणा N3000_DEVICE_ID		0x1041
#घोषणा N3000_SUBSYS_VENDOR_ID	0x8086
#घोषणा N3000_SUBSYS_DEVICE_ID	0x001A

#घोषणा C5000X_PL_VENDOR_ID		0x1AF4
#घोषणा C5000X_PL_DEVICE_ID		0x1000
#घोषणा C5000X_PL_SUBSYS_VENDOR_ID	0x8086
#घोषणा C5000X_PL_SUBSYS_DEVICE_ID	0x0001

#घोषणा C5000X_PL_BLK_VENDOR_ID		0x1AF4
#घोषणा C5000X_PL_BLK_DEVICE_ID		0x1001
#घोषणा C5000X_PL_BLK_SUBSYS_VENDOR_ID	0x8086
#घोषणा C5000X_PL_BLK_SUBSYS_DEVICE_ID	0x0002

#घोषणा IFCVF_NET_SUPPORTED_FEATURES \
		((1ULL << VIRTIO_NET_F_MAC)			| \
		 (1ULL << VIRTIO_F_ANY_LAYOUT)			| \
		 (1ULL << VIRTIO_F_VERSION_1)			| \
		 (1ULL << VIRTIO_NET_F_STATUS)			| \
		 (1ULL << VIRTIO_F_ORDER_PLATFORM)		| \
		 (1ULL << VIRTIO_F_ACCESS_PLATFORM)		| \
		 (1ULL << VIRTIO_NET_F_MRG_RXBUF))

/* Only one queue pair क्रम now. */
#घोषणा IFCVF_MAX_QUEUE_PAIRS	1

#घोषणा IFCVF_QUEUE_ALIGNMENT	PAGE_SIZE
#घोषणा IFCVF_QUEUE_MAX		32768
#घोषणा IFCVF_MSI_CONFIG_OFF	0
#घोषणा IFCVF_MSI_QUEUE_OFF	1
#घोषणा IFCVF_PCI_MAX_RESOURCE	6

#घोषणा IFCVF_LM_CFG_SIZE		0x40
#घोषणा IFCVF_LM_RING_STATE_OFFSET	0x20
#घोषणा IFCVF_LM_BAR			4

#घोषणा IFCVF_ERR(pdev, fmt, ...)	dev_err(&pdev->dev, fmt, ##__VA_ARGS__)
#घोषणा IFCVF_DBG(pdev, fmt, ...)	dev_dbg(&pdev->dev, fmt, ##__VA_ARGS__)
#घोषणा IFCVF_INFO(pdev, fmt, ...)	dev_info(&pdev->dev, fmt, ##__VA_ARGS__)

#घोषणा अगरcvf_निजी_to_vf(adapter) \
	(&((काष्ठा अगरcvf_adapter *)adapter)->vf)

#घोषणा IFCVF_MAX_INTR (IFCVF_MAX_QUEUE_PAIRS * 2 + 1)

काष्ठा vring_info अणु
	u64 desc;
	u64 avail;
	u64 used;
	u16 size;
	u16 last_avail_idx;
	bool पढ़ोy;
	व्योम __iomem *notअगरy_addr;
	u32 irq;
	काष्ठा vdpa_callback cb;
	अक्षर msix_name[256];
पूर्ण;

काष्ठा अगरcvf_hw अणु
	u8 __iomem *isr;
	/* Live migration */
	u8 __iomem *lm_cfg;
	u16 nr_vring;
	/* Notअगरication bar number */
	u8 notअगरy_bar;
	/* Notअगरicaiton bar address */
	व्योम __iomem *notअगरy_base;
	u32 notअगरy_off_multiplier;
	u64 req_features;
	u64 hw_features;
	u32 dev_type;
	काष्ठा virtio_pci_common_cfg __iomem *common_cfg;
	व्योम __iomem *net_cfg;
	काष्ठा vring_info vring[IFCVF_MAX_QUEUE_PAIRS * 2];
	व्योम __iomem * स्थिर *base;
	अक्षर config_msix_name[256];
	काष्ठा vdpa_callback config_cb;
	अचिन्हित पूर्णांक config_irq;
पूर्ण;

काष्ठा अगरcvf_adapter अणु
	काष्ठा vdpa_device vdpa;
	काष्ठा pci_dev *pdev;
	काष्ठा अगरcvf_hw vf;
पूर्ण;

काष्ठा अगरcvf_vring_lm_cfg अणु
	u32 idx_addr[2];
	u8 reserved[IFCVF_LM_CFG_SIZE - 8];
पूर्ण;

काष्ठा अगरcvf_lm_cfg अणु
	u8 reserved[IFCVF_LM_RING_STATE_OFFSET];
	काष्ठा अगरcvf_vring_lm_cfg vring_lm_cfg[IFCVF_MAX_QUEUE_PAIRS];
पूर्ण;

पूर्णांक अगरcvf_init_hw(काष्ठा अगरcvf_hw *hw, काष्ठा pci_dev *dev);
पूर्णांक अगरcvf_start_hw(काष्ठा अगरcvf_hw *hw);
व्योम अगरcvf_stop_hw(काष्ठा अगरcvf_hw *hw);
व्योम अगरcvf_notअगरy_queue(काष्ठा अगरcvf_hw *hw, u16 qid);
व्योम अगरcvf_पढ़ो_net_config(काष्ठा अगरcvf_hw *hw, u64 offset,
			   व्योम *dst, पूर्णांक length);
व्योम अगरcvf_ग_लिखो_net_config(काष्ठा अगरcvf_hw *hw, u64 offset,
			    स्थिर व्योम *src, पूर्णांक length);
u8 अगरcvf_get_status(काष्ठा अगरcvf_hw *hw);
व्योम अगरcvf_set_status(काष्ठा अगरcvf_hw *hw, u8 status);
व्योम io_ग_लिखो64_twopart(u64 val, u32 *lo, u32 *hi);
व्योम अगरcvf_reset(काष्ठा अगरcvf_hw *hw);
u64 अगरcvf_get_features(काष्ठा अगरcvf_hw *hw);
u64 अगरcvf_get_hw_features(काष्ठा अगरcvf_hw *hw);
पूर्णांक अगरcvf_verअगरy_min_features(काष्ठा अगरcvf_hw *hw, u64 features);
u16 अगरcvf_get_vq_state(काष्ठा अगरcvf_hw *hw, u16 qid);
पूर्णांक अगरcvf_set_vq_state(काष्ठा अगरcvf_hw *hw, u16 qid, u16 num);
काष्ठा अगरcvf_adapter *vf_to_adapter(काष्ठा अगरcvf_hw *hw);
पूर्णांक अगरcvf_probed_virtio_net(काष्ठा अगरcvf_hw *hw);
#पूर्ण_अगर /* _IFCVF_H_ */
