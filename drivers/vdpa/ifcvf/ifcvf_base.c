<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Intel IFC VF NIC driver क्रम virtio dataplane offloading
 *
 * Copyright (C) 2020 Intel Corporation.
 *
 * Author: Zhu Lingshan <lingshan.zhu@पूर्णांकel.com>
 *
 */

#समावेश "ifcvf_base.h"

अटल अंतरभूत u8 अगरc_ioपढ़ो8(u8 __iomem *addr)
अणु
	वापस ioपढ़ो8(addr);
पूर्ण
अटल अंतरभूत u16 अगरc_ioपढ़ो16 (__le16 __iomem *addr)
अणु
	वापस ioपढ़ो16(addr);
पूर्ण

अटल अंतरभूत u32 अगरc_ioपढ़ो32(__le32 __iomem *addr)
अणु
	वापस ioपढ़ो32(addr);
पूर्ण

अटल अंतरभूत व्योम अगरc_ioग_लिखो8(u8 value, u8 __iomem *addr)
अणु
	ioग_लिखो8(value, addr);
पूर्ण

अटल अंतरभूत व्योम अगरc_ioग_लिखो16(u16 value, __le16 __iomem *addr)
अणु
	ioग_लिखो16(value, addr);
पूर्ण

अटल अंतरभूत व्योम अगरc_ioग_लिखो32(u32 value, __le32 __iomem *addr)
अणु
	ioग_लिखो32(value, addr);
पूर्ण

अटल व्योम अगरc_ioग_लिखो64_twopart(u64 val,
				  __le32 __iomem *lo, __le32 __iomem *hi)
अणु
	अगरc_ioग_लिखो32((u32)val, lo);
	अगरc_ioग_लिखो32(val >> 32, hi);
पूर्ण

काष्ठा अगरcvf_adapter *vf_to_adapter(काष्ठा अगरcvf_hw *hw)
अणु
	वापस container_of(hw, काष्ठा अगरcvf_adapter, vf);
पूर्ण

अटल व्योम __iomem *get_cap_addr(काष्ठा अगरcvf_hw *hw,
				  काष्ठा virtio_pci_cap *cap)
अणु
	काष्ठा अगरcvf_adapter *अगरcvf;
	काष्ठा pci_dev *pdev;
	u32 length, offset;
	u8 bar;

	length = le32_to_cpu(cap->length);
	offset = le32_to_cpu(cap->offset);
	bar = cap->bar;

	अगरcvf= vf_to_adapter(hw);
	pdev = अगरcvf->pdev;

	अगर (bar >= IFCVF_PCI_MAX_RESOURCE) अणु
		IFCVF_DBG(pdev,
			  "Invalid bar number %u to get capabilities\n", bar);
		वापस शून्य;
	पूर्ण

	अगर (offset + length > pci_resource_len(pdev, bar)) अणु
		IFCVF_DBG(pdev,
			  "offset(%u) + len(%u) overflows bar%u's capability\n",
			  offset, length, bar);
		वापस शून्य;
	पूर्ण

	वापस hw->base[bar] + offset;
पूर्ण

अटल पूर्णांक अगरcvf_पढ़ो_config_range(काष्ठा pci_dev *dev,
				   uपूर्णांक32_t *val, पूर्णांक size, पूर्णांक where)
अणु
	पूर्णांक ret, i;

	क्रम (i = 0; i < size; i += 4) अणु
		ret = pci_पढ़ो_config_dword(dev, where + i, val + i / 4);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक अगरcvf_init_hw(काष्ठा अगरcvf_hw *hw, काष्ठा pci_dev *pdev)
अणु
	काष्ठा virtio_pci_cap cap;
	u16 notअगरy_off;
	पूर्णांक ret;
	u8 pos;
	u32 i;

	ret = pci_पढ़ो_config_byte(pdev, PCI_CAPABILITY_LIST, &pos);
	अगर (ret < 0) अणु
		IFCVF_ERR(pdev, "Failed to read PCI capability list\n");
		वापस -EIO;
	पूर्ण

	जबतक (pos) अणु
		ret = अगरcvf_पढ़ो_config_range(pdev, (u32 *)&cap,
					      माप(cap), pos);
		अगर (ret < 0) अणु
			IFCVF_ERR(pdev,
				  "Failed to get PCI capability at %x\n", pos);
			अवरोध;
		पूर्ण

		अगर (cap.cap_vndr != PCI_CAP_ID_VNDR)
			जाओ next;

		चयन (cap.cfg_type) अणु
		हाल VIRTIO_PCI_CAP_COMMON_CFG:
			hw->common_cfg = get_cap_addr(hw, &cap);
			IFCVF_DBG(pdev, "hw->common_cfg = %p\n",
				  hw->common_cfg);
			अवरोध;
		हाल VIRTIO_PCI_CAP_NOTIFY_CFG:
			pci_पढ़ो_config_dword(pdev, pos + माप(cap),
					      &hw->notअगरy_off_multiplier);
			hw->notअगरy_bar = cap.bar;
			hw->notअगरy_base = get_cap_addr(hw, &cap);
			IFCVF_DBG(pdev, "hw->notify_base = %p\n",
				  hw->notअगरy_base);
			अवरोध;
		हाल VIRTIO_PCI_CAP_ISR_CFG:
			hw->isr = get_cap_addr(hw, &cap);
			IFCVF_DBG(pdev, "hw->isr = %p\n", hw->isr);
			अवरोध;
		हाल VIRTIO_PCI_CAP_DEVICE_CFG:
			hw->net_cfg = get_cap_addr(hw, &cap);
			IFCVF_DBG(pdev, "hw->net_cfg = %p\n", hw->net_cfg);
			अवरोध;
		पूर्ण

next:
		pos = cap.cap_next;
	पूर्ण

	अगर (hw->common_cfg == शून्य || hw->notअगरy_base == शून्य ||
	    hw->isr == शून्य || hw->net_cfg == शून्य) अणु
		IFCVF_ERR(pdev, "Incomplete PCI capabilities\n");
		वापस -EIO;
	पूर्ण

	क्रम (i = 0; i < IFCVF_MAX_QUEUE_PAIRS * 2; i++) अणु
		अगरc_ioग_लिखो16(i, &hw->common_cfg->queue_select);
		notअगरy_off = अगरc_ioपढ़ो16(&hw->common_cfg->queue_notअगरy_off);
		hw->vring[i].notअगरy_addr = hw->notअगरy_base +
			notअगरy_off * hw->notअगरy_off_multiplier;
	पूर्ण

	hw->lm_cfg = hw->base[IFCVF_LM_BAR];

	IFCVF_DBG(pdev,
		  "PCI capability mapping: common cfg: %p, notify base: %p\n, isr cfg: %p, device cfg: %p, multiplier: %u\n",
		  hw->common_cfg, hw->notअगरy_base, hw->isr,
		  hw->net_cfg, hw->notअगरy_off_multiplier);

	वापस 0;
पूर्ण

u8 अगरcvf_get_status(काष्ठा अगरcvf_hw *hw)
अणु
	वापस अगरc_ioपढ़ो8(&hw->common_cfg->device_status);
पूर्ण

व्योम अगरcvf_set_status(काष्ठा अगरcvf_hw *hw, u8 status)
अणु
	अगरc_ioग_लिखो8(status, &hw->common_cfg->device_status);
पूर्ण

व्योम अगरcvf_reset(काष्ठा अगरcvf_hw *hw)
अणु
	hw->config_cb.callback = शून्य;
	hw->config_cb.निजी = शून्य;

	अगरcvf_set_status(hw, 0);
	/* flush set_status, make sure VF is stopped, reset */
	अगरcvf_get_status(hw);
पूर्ण

अटल व्योम अगरcvf_add_status(काष्ठा अगरcvf_hw *hw, u8 status)
अणु
	अगर (status != 0)
		status |= अगरcvf_get_status(hw);

	अगरcvf_set_status(hw, status);
	अगरcvf_get_status(hw);
पूर्ण

u64 अगरcvf_get_hw_features(काष्ठा अगरcvf_hw *hw)
अणु
	काष्ठा virtio_pci_common_cfg __iomem *cfg = hw->common_cfg;
	u32 features_lo, features_hi;
	u64 features;

	अगरc_ioग_लिखो32(0, &cfg->device_feature_select);
	features_lo = अगरc_ioपढ़ो32(&cfg->device_feature);

	अगरc_ioग_लिखो32(1, &cfg->device_feature_select);
	features_hi = अगरc_ioपढ़ो32(&cfg->device_feature);

	features = ((u64)features_hi << 32) | features_lo;

	वापस features;
पूर्ण

u64 अगरcvf_get_features(काष्ठा अगरcvf_hw *hw)
अणु
	वापस hw->hw_features;
पूर्ण

पूर्णांक अगरcvf_verअगरy_min_features(काष्ठा अगरcvf_hw *hw, u64 features)
अणु
	काष्ठा अगरcvf_adapter *अगरcvf = vf_to_adapter(hw);

	अगर (!(features & BIT_ULL(VIRTIO_F_ACCESS_PLATFORM)) && features) अणु
		IFCVF_ERR(अगरcvf->pdev, "VIRTIO_F_ACCESS_PLATFORM is not negotiated\n");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

व्योम अगरcvf_पढ़ो_net_config(काष्ठा अगरcvf_hw *hw, u64 offset,
			   व्योम *dst, पूर्णांक length)
अणु
	u8 old_gen, new_gen, *p;
	पूर्णांक i;

	WARN_ON(offset + length > माप(काष्ठा virtio_net_config));
	करो अणु
		old_gen = अगरc_ioपढ़ो8(&hw->common_cfg->config_generation);
		p = dst;
		क्रम (i = 0; i < length; i++)
			*p++ = अगरc_ioपढ़ो8(hw->net_cfg + offset + i);

		new_gen = अगरc_ioपढ़ो8(&hw->common_cfg->config_generation);
	पूर्ण जबतक (old_gen != new_gen);
पूर्ण

व्योम अगरcvf_ग_लिखो_net_config(काष्ठा अगरcvf_hw *hw, u64 offset,
			    स्थिर व्योम *src, पूर्णांक length)
अणु
	स्थिर u8 *p;
	पूर्णांक i;

	p = src;
	WARN_ON(offset + length > माप(काष्ठा virtio_net_config));
	क्रम (i = 0; i < length; i++)
		अगरc_ioग_लिखो8(*p++, hw->net_cfg + offset + i);
पूर्ण

अटल व्योम अगरcvf_set_features(काष्ठा अगरcvf_hw *hw, u64 features)
अणु
	काष्ठा virtio_pci_common_cfg __iomem *cfg = hw->common_cfg;

	अगरc_ioग_लिखो32(0, &cfg->guest_feature_select);
	अगरc_ioग_लिखो32((u32)features, &cfg->guest_feature);

	अगरc_ioग_लिखो32(1, &cfg->guest_feature_select);
	अगरc_ioग_लिखो32(features >> 32, &cfg->guest_feature);
पूर्ण

अटल पूर्णांक अगरcvf_config_features(काष्ठा अगरcvf_hw *hw)
अणु
	काष्ठा अगरcvf_adapter *अगरcvf;

	अगरcvf = vf_to_adapter(hw);
	अगरcvf_set_features(hw, hw->req_features);
	अगरcvf_add_status(hw, VIRTIO_CONFIG_S_FEATURES_OK);

	अगर (!(अगरcvf_get_status(hw) & VIRTIO_CONFIG_S_FEATURES_OK)) अणु
		IFCVF_ERR(अगरcvf->pdev, "Failed to set FEATURES_OK status\n");
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

u16 अगरcvf_get_vq_state(काष्ठा अगरcvf_hw *hw, u16 qid)
अणु
	काष्ठा अगरcvf_lm_cfg __iomem *अगरcvf_lm;
	व्योम __iomem *avail_idx_addr;
	u16 last_avail_idx;
	u32 q_pair_id;

	अगरcvf_lm = (काष्ठा अगरcvf_lm_cfg __iomem *)hw->lm_cfg;
	q_pair_id = qid / (IFCVF_MAX_QUEUE_PAIRS * 2);
	avail_idx_addr = &अगरcvf_lm->vring_lm_cfg[q_pair_id].idx_addr[qid % 2];
	last_avail_idx = अगरc_ioपढ़ो16(avail_idx_addr);

	वापस last_avail_idx;
पूर्ण

पूर्णांक अगरcvf_set_vq_state(काष्ठा अगरcvf_hw *hw, u16 qid, u16 num)
अणु
	काष्ठा अगरcvf_lm_cfg __iomem *अगरcvf_lm;
	व्योम __iomem *avail_idx_addr;
	u32 q_pair_id;

	अगरcvf_lm = (काष्ठा अगरcvf_lm_cfg __iomem *)hw->lm_cfg;
	q_pair_id = qid / (IFCVF_MAX_QUEUE_PAIRS * 2);
	avail_idx_addr = &अगरcvf_lm->vring_lm_cfg[q_pair_id].idx_addr[qid % 2];
	hw->vring[qid].last_avail_idx = num;
	अगरc_ioग_लिखो16(num, avail_idx_addr);

	वापस 0;
पूर्ण

अटल पूर्णांक अगरcvf_hw_enable(काष्ठा अगरcvf_hw *hw)
अणु
	काष्ठा virtio_pci_common_cfg __iomem *cfg;
	काष्ठा अगरcvf_adapter *अगरcvf;
	u32 i;

	अगरcvf = vf_to_adapter(hw);
	cfg = hw->common_cfg;
	अगरc_ioग_लिखो16(IFCVF_MSI_CONFIG_OFF, &cfg->msix_config);

	अगर (अगरc_ioपढ़ो16(&cfg->msix_config) == VIRTIO_MSI_NO_VECTOR) अणु
		IFCVF_ERR(अगरcvf->pdev, "No msix vector for device config\n");
		वापस -EINVAL;
	पूर्ण

	क्रम (i = 0; i < hw->nr_vring; i++) अणु
		अगर (!hw->vring[i].पढ़ोy)
			अवरोध;

		अगरc_ioग_लिखो16(i, &cfg->queue_select);
		अगरc_ioग_लिखो64_twopart(hw->vring[i].desc, &cfg->queue_desc_lo,
				     &cfg->queue_desc_hi);
		अगरc_ioग_लिखो64_twopart(hw->vring[i].avail, &cfg->queue_avail_lo,
				      &cfg->queue_avail_hi);
		अगरc_ioग_लिखो64_twopart(hw->vring[i].used, &cfg->queue_used_lo,
				     &cfg->queue_used_hi);
		अगरc_ioग_लिखो16(hw->vring[i].size, &cfg->queue_size);
		अगरc_ioग_लिखो16(i + IFCVF_MSI_QUEUE_OFF, &cfg->queue_msix_vector);

		अगर (अगरc_ioपढ़ो16(&cfg->queue_msix_vector) ==
		    VIRTIO_MSI_NO_VECTOR) अणु
			IFCVF_ERR(अगरcvf->pdev,
				  "No msix vector for queue %u\n", i);
			वापस -EINVAL;
		पूर्ण

		अगरcvf_set_vq_state(hw, i, hw->vring[i].last_avail_idx);
		अगरc_ioग_लिखो16(1, &cfg->queue_enable);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम अगरcvf_hw_disable(काष्ठा अगरcvf_hw *hw)
अणु
	काष्ठा virtio_pci_common_cfg __iomem *cfg;
	u32 i;

	cfg = hw->common_cfg;
	अगरc_ioग_लिखो16(VIRTIO_MSI_NO_VECTOR, &cfg->msix_config);

	क्रम (i = 0; i < hw->nr_vring; i++) अणु
		अगरc_ioग_लिखो16(i, &cfg->queue_select);
		अगरc_ioग_लिखो16(VIRTIO_MSI_NO_VECTOR, &cfg->queue_msix_vector);
	पूर्ण

	अगरc_ioपढ़ो16(&cfg->queue_msix_vector);
पूर्ण

पूर्णांक अगरcvf_start_hw(काष्ठा अगरcvf_hw *hw)
अणु
	अगरcvf_reset(hw);
	अगरcvf_add_status(hw, VIRTIO_CONFIG_S_ACKNOWLEDGE);
	अगरcvf_add_status(hw, VIRTIO_CONFIG_S_DRIVER);

	अगर (अगरcvf_config_features(hw) < 0)
		वापस -EINVAL;

	अगर (अगरcvf_hw_enable(hw) < 0)
		वापस -EINVAL;

	अगरcvf_add_status(hw, VIRTIO_CONFIG_S_DRIVER_OK);

	वापस 0;
पूर्ण

व्योम अगरcvf_stop_hw(काष्ठा अगरcvf_hw *hw)
अणु
	अगरcvf_hw_disable(hw);
	अगरcvf_reset(hw);
पूर्ण

व्योम अगरcvf_notअगरy_queue(काष्ठा अगरcvf_hw *hw, u16 qid)
अणु
	अगरc_ioग_लिखो16(qid, hw->vring[qid].notअगरy_addr);
पूर्ण
