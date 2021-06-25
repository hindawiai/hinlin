<शैली गुरु>
/*
 * This file is provided under a dual BSD/GPLv2 license.  When using or
 *   redistributing this file, you may करो so under either license.
 *
 *   GPL LICENSE SUMMARY
 *
 *   Copyright (C) 2016 Advanced Micro Devices, Inc. All Rights Reserved.
 *   Copyright (C) 2016 T-Platक्रमms. All Rights Reserved.
 *
 *   This program is मुक्त software; you can redistribute it and/or modअगरy
 *   it under the terms of version 2 of the GNU General Public License as
 *   published by the Free Software Foundation.
 *
 *   BSD LICENSE
 *
 *   Copyright (C) 2016 Advanced Micro Devices, Inc. All Rights Reserved.
 *   Copyright (C) 2016 T-Platक्रमms. All Rights Reserved.
 *
 *   Redistribution and use in source and binary क्रमms, with or without
 *   modअगरication, are permitted provided that the following conditions
 *   are met:
 *
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary क्रमm must reproduce the above copy
 *       notice, this list of conditions and the following disclaimer in
 *       the करोcumentation and/or other materials provided with the
 *       distribution.
 *     * Neither the name of AMD Corporation nor the names of its
 *       contributors may be used to enकरोrse or promote products derived
 *       from this software without specअगरic prior written permission.
 *
 *   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *   "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *   LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *   A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 *   OWNER OR CONTRIBUTORS BE LIABLE FOR ANY सूचीECT, INसूचीECT, INCIDENTAL,
 *   SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *   LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *   DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *   THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *   (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *   OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * AMD PCIe NTB Linux driver
 *
 * Contact Inक्रमmation:
 * Xiangliang Yu <Xiangliang.Yu@amd.com>
 */

#समावेश <linux/debugfs.h>
#समावेश <linux/delay.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/module.h>
#समावेश <linux/acpi.h>
#समावेश <linux/pci.h>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/slab.h>
#समावेश <linux/ntb.h>

#समावेश "ntb_hw_amd.h"

#घोषणा NTB_NAME	"ntb_hw_amd"
#घोषणा NTB_DESC	"AMD(R) PCI-E Non-Transparent Bridge Driver"
#घोषणा NTB_VER		"1.0"

MODULE_DESCRIPTION(NTB_DESC);
MODULE_VERSION(NTB_VER);
MODULE_LICENSE("Dual BSD/GPL");
MODULE_AUTHOR("AMD Inc.");

अटल स्थिर काष्ठा file_operations amd_ntb_debugfs_info;
अटल काष्ठा dentry *debugfs_dir;

अटल पूर्णांक ndev_mw_to_bar(काष्ठा amd_ntb_dev *ndev, पूर्णांक idx)
अणु
	अगर (idx < 0 || idx > ndev->mw_count)
		वापस -EINVAL;

	वापस ndev->dev_data->mw_idx << idx;
पूर्ण

अटल पूर्णांक amd_ntb_mw_count(काष्ठा ntb_dev *ntb, पूर्णांक pidx)
अणु
	अगर (pidx != NTB_DEF_PEER_IDX)
		वापस -EINVAL;

	वापस ntb_ndev(ntb)->mw_count;
पूर्ण

अटल पूर्णांक amd_ntb_mw_get_align(काष्ठा ntb_dev *ntb, पूर्णांक pidx, पूर्णांक idx,
				resource_माप_प्रकार *addr_align,
				resource_माप_प्रकार *size_align,
				resource_माप_प्रकार *size_max)
अणु
	काष्ठा amd_ntb_dev *ndev = ntb_ndev(ntb);
	पूर्णांक bar;

	अगर (pidx != NTB_DEF_PEER_IDX)
		वापस -EINVAL;

	bar = ndev_mw_to_bar(ndev, idx);
	अगर (bar < 0)
		वापस bar;

	अगर (addr_align)
		*addr_align = SZ_4K;

	अगर (size_align)
		*size_align = 1;

	अगर (size_max)
		*size_max = pci_resource_len(ndev->ntb.pdev, bar);

	वापस 0;
पूर्ण

अटल पूर्णांक amd_ntb_mw_set_trans(काष्ठा ntb_dev *ntb, पूर्णांक pidx, पूर्णांक idx,
				dma_addr_t addr, resource_माप_प्रकार size)
अणु
	काष्ठा amd_ntb_dev *ndev = ntb_ndev(ntb);
	अचिन्हित दीर्घ xlat_reg, limit_reg = 0;
	resource_माप_प्रकार mw_size;
	व्योम __iomem *mmio, *peer_mmio;
	u64 base_addr, limit, reg_val;
	पूर्णांक bar;

	अगर (pidx != NTB_DEF_PEER_IDX)
		वापस -EINVAL;

	bar = ndev_mw_to_bar(ndev, idx);
	अगर (bar < 0)
		वापस bar;

	mw_size = pci_resource_len(ntb->pdev, bar);

	/* make sure the range fits in the usable mw size */
	अगर (size > mw_size)
		वापस -EINVAL;

	mmio = ndev->self_mmio;
	peer_mmio = ndev->peer_mmio;

	base_addr = pci_resource_start(ntb->pdev, bar);

	अगर (bar != 1) अणु
		xlat_reg = AMD_BAR23XLAT_OFFSET + ((bar - 2) << 2);
		limit_reg = AMD_BAR23LMT_OFFSET + ((bar - 2) << 2);

		/* Set the limit अगर supported */
		limit = size;

		/* set and verअगरy setting the translation address */
		ग_लिखो64(addr, peer_mmio + xlat_reg);
		reg_val = पढ़ो64(peer_mmio + xlat_reg);
		अगर (reg_val != addr) अणु
			ग_लिखो64(0, peer_mmio + xlat_reg);
			वापस -EIO;
		पूर्ण

		/* set and verअगरy setting the limit */
		ग_लिखो64(limit, peer_mmio + limit_reg);
		reg_val = पढ़ो64(peer_mmio + limit_reg);
		अगर (reg_val != limit) अणु
			ग_लिखो64(base_addr, mmio + limit_reg);
			ग_लिखो64(0, peer_mmio + xlat_reg);
			वापस -EIO;
		पूर्ण
	पूर्ण अन्यथा अणु
		xlat_reg = AMD_BAR1XLAT_OFFSET;
		limit_reg = AMD_BAR1LMT_OFFSET;

		/* Set the limit अगर supported */
		limit = size;

		/* set and verअगरy setting the translation address */
		ग_लिखो64(addr, peer_mmio + xlat_reg);
		reg_val = पढ़ो64(peer_mmio + xlat_reg);
		अगर (reg_val != addr) अणु
			ग_लिखो64(0, peer_mmio + xlat_reg);
			वापस -EIO;
		पूर्ण

		/* set and verअगरy setting the limit */
		ग_लिखोl(limit, peer_mmio + limit_reg);
		reg_val = पढ़ोl(peer_mmio + limit_reg);
		अगर (reg_val != limit) अणु
			ग_लिखोl(base_addr, mmio + limit_reg);
			ग_लिखोl(0, peer_mmio + xlat_reg);
			वापस -EIO;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक amd_ntb_get_link_status(काष्ठा amd_ntb_dev *ndev)
अणु
	काष्ठा pci_dev *pdev = शून्य;
	काष्ठा pci_dev *pci_swds = शून्य;
	काष्ठा pci_dev *pci_swus = शून्य;
	u32 stat;
	पूर्णांक rc;

	अगर (ndev->ntb.topo == NTB_TOPO_SEC) अणु
		/* Locate the poपूर्णांकer to Downstream Switch क्रम this device */
		pci_swds = pci_upstream_bridge(ndev->ntb.pdev);
		अगर (pci_swds) अणु
			/*
			 * Locate the poपूर्णांकer to Upstream Switch क्रम
			 * the Downstream Switch.
			 */
			pci_swus = pci_upstream_bridge(pci_swds);
			अगर (pci_swus) अणु
				rc = pcie_capability_पढ़ो_dword(pci_swus,
								PCI_EXP_LNKCTL,
								&stat);
				अगर (rc)
					वापस 0;
			पूर्ण अन्यथा अणु
				वापस 0;
			पूर्ण
		पूर्ण अन्यथा अणु
			वापस 0;
		पूर्ण
	पूर्ण अन्यथा अगर (ndev->ntb.topo == NTB_TOPO_PRI) अणु
		/*
		 * For NTB primary, we simply पढ़ो the Link Status and control
		 * रेजिस्टर of the NTB device itself.
		 */
		pdev = ndev->ntb.pdev;
		rc = pcie_capability_पढ़ो_dword(pdev, PCI_EXP_LNKCTL, &stat);
		अगर (rc)
			वापस 0;
	पूर्ण अन्यथा अणु
		/* Catch all क्रम everything अन्यथा */
		वापस 0;
	पूर्ण

	ndev->lnk_sta = stat;

	वापस 1;
पूर्ण

अटल पूर्णांक amd_link_is_up(काष्ठा amd_ntb_dev *ndev)
अणु
	पूर्णांक ret;

	/*
	 * We consider the link to be up under two conditions:
	 *
	 *   - When a link-up event is received. This is indicated by
	 *     AMD_LINK_UP_EVENT set in peer_sta.
	 *   - When driver on both sides of the link have been loaded.
	 *     This is indicated by bit 1 being set in the peer
	 *     SIDEINFO रेजिस्टर.
	 *
	 * This function should वापस 1 when the latter of the above
	 * two conditions is true.
	 *
	 * Now consider the sequence of events - Link-Up event occurs,
	 * then the peer side driver loads. In this हाल, we would have
	 * received LINK_UP event and bit 1 of peer SIDEINFO is also
	 * set. What happens now अगर the link goes करोwn? Bit 1 of
	 * peer SIDEINFO reमुख्यs set, but LINK_DOWN bit is set in
	 * peer_sta. So we should वापस 0 from this function. Not only
	 * that, we clear bit 1 of peer SIDEINFO to 0, since the peer
	 * side driver did not even get a chance to clear it beक्रमe
	 * the link went करोwn. This can be the हाल of surprise link
	 * removal.
	 *
	 * LINK_UP event will always occur beक्रमe the peer side driver
	 * माला_लो loaded the very first समय. So there can be a हाल when
	 * the LINK_UP event has occurred, but the peer side driver hasn't
	 * yet loaded. We वापस 0 in that हाल.
	 *
	 * There is also a special हाल when the primary side driver is
	 * unloaded and then loaded again. Since there is no change in
	 * the status of NTB secondary in this हाल, there is no Link-Up
	 * or Link-Down notअगरication received. We recognize this condition
	 * with peer_sta being set to 0.
	 *
	 * If bit 1 of peer SIDEINFO रेजिस्टर is not set, then we
	 * simply वापस 0 irrespective of the link up or करोwn status
	 * set in peer_sta.
	 */
	ret = amd_poll_link(ndev);
	अगर (ret) अणु
		/*
		 * We need to check the below only क्रम NTB primary. For NTB
		 * secondary, simply checking the result of PSIDE_INFO
		 * रेजिस्टर will suffice.
		 */
		अगर (ndev->ntb.topo == NTB_TOPO_PRI) अणु
			अगर ((ndev->peer_sta & AMD_LINK_UP_EVENT) ||
			    (ndev->peer_sta == 0))
				वापस ret;
			अन्यथा अगर (ndev->peer_sta & AMD_LINK_DOWN_EVENT) अणु
				/* Clear peer sideinfo रेजिस्टर */
				amd_clear_side_info_reg(ndev, true);

				वापस 0;
			पूर्ण
		पूर्ण अन्यथा अणु /* NTB_TOPO_SEC */
			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल u64 amd_ntb_link_is_up(काष्ठा ntb_dev *ntb,
			      क्रमागत ntb_speed *speed,
			      क्रमागत ntb_width *width)
अणु
	काष्ठा amd_ntb_dev *ndev = ntb_ndev(ntb);
	पूर्णांक ret = 0;

	अगर (amd_link_is_up(ndev)) अणु
		अगर (speed)
			*speed = NTB_LNK_STA_SPEED(ndev->lnk_sta);
		अगर (width)
			*width = NTB_LNK_STA_WIDTH(ndev->lnk_sta);

		dev_dbg(&ntb->pdev->dev, "link is up.\n");

		ret = 1;
	पूर्ण अन्यथा अणु
		अगर (speed)
			*speed = NTB_SPEED_NONE;
		अगर (width)
			*width = NTB_WIDTH_NONE;

		dev_dbg(&ntb->pdev->dev, "link is down.\n");
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक amd_ntb_link_enable(काष्ठा ntb_dev *ntb,
			       क्रमागत ntb_speed max_speed,
			       क्रमागत ntb_width max_width)
अणु
	काष्ठा amd_ntb_dev *ndev = ntb_ndev(ntb);
	व्योम __iomem *mmio = ndev->self_mmio;

	/* Enable event पूर्णांकerrupt */
	ndev->पूर्णांक_mask &= ~AMD_EVENT_INTMASK;
	ग_लिखोl(ndev->पूर्णांक_mask, mmio + AMD_INTMASK_OFFSET);

	अगर (ndev->ntb.topo == NTB_TOPO_SEC)
		वापस -EINVAL;
	dev_dbg(&ntb->pdev->dev, "Enabling Link.\n");

	वापस 0;
पूर्ण

अटल पूर्णांक amd_ntb_link_disable(काष्ठा ntb_dev *ntb)
अणु
	काष्ठा amd_ntb_dev *ndev = ntb_ndev(ntb);
	व्योम __iomem *mmio = ndev->self_mmio;

	/* Disable event पूर्णांकerrupt */
	ndev->पूर्णांक_mask |= AMD_EVENT_INTMASK;
	ग_लिखोl(ndev->पूर्णांक_mask, mmio + AMD_INTMASK_OFFSET);

	अगर (ndev->ntb.topo == NTB_TOPO_SEC)
		वापस -EINVAL;
	dev_dbg(&ntb->pdev->dev, "Enabling Link.\n");

	वापस 0;
पूर्ण

अटल पूर्णांक amd_ntb_peer_mw_count(काष्ठा ntb_dev *ntb)
अणु
	/* The same as क्रम inbound MWs */
	वापस ntb_ndev(ntb)->mw_count;
पूर्ण

अटल पूर्णांक amd_ntb_peer_mw_get_addr(काष्ठा ntb_dev *ntb, पूर्णांक idx,
				    phys_addr_t *base, resource_माप_प्रकार *size)
अणु
	काष्ठा amd_ntb_dev *ndev = ntb_ndev(ntb);
	पूर्णांक bar;

	bar = ndev_mw_to_bar(ndev, idx);
	अगर (bar < 0)
		वापस bar;

	अगर (base)
		*base = pci_resource_start(ndev->ntb.pdev, bar);

	अगर (size)
		*size = pci_resource_len(ndev->ntb.pdev, bar);

	वापस 0;
पूर्ण

अटल u64 amd_ntb_db_valid_mask(काष्ठा ntb_dev *ntb)
अणु
	वापस ntb_ndev(ntb)->db_valid_mask;
पूर्ण

अटल पूर्णांक amd_ntb_db_vector_count(काष्ठा ntb_dev *ntb)
अणु
	वापस ntb_ndev(ntb)->db_count;
पूर्ण

अटल u64 amd_ntb_db_vector_mask(काष्ठा ntb_dev *ntb, पूर्णांक db_vector)
अणु
	काष्ठा amd_ntb_dev *ndev = ntb_ndev(ntb);

	अगर (db_vector < 0 || db_vector > ndev->db_count)
		वापस 0;

	वापस ntb_ndev(ntb)->db_valid_mask & (1ULL << db_vector);
पूर्ण

अटल u64 amd_ntb_db_पढ़ो(काष्ठा ntb_dev *ntb)
अणु
	काष्ठा amd_ntb_dev *ndev = ntb_ndev(ntb);
	व्योम __iomem *mmio = ndev->self_mmio;

	वापस (u64)पढ़ोw(mmio + AMD_DBSTAT_OFFSET);
पूर्ण

अटल पूर्णांक amd_ntb_db_clear(काष्ठा ntb_dev *ntb, u64 db_bits)
अणु
	काष्ठा amd_ntb_dev *ndev = ntb_ndev(ntb);
	व्योम __iomem *mmio = ndev->self_mmio;

	ग_लिखोw((u16)db_bits, mmio + AMD_DBSTAT_OFFSET);

	वापस 0;
पूर्ण

अटल पूर्णांक amd_ntb_db_set_mask(काष्ठा ntb_dev *ntb, u64 db_bits)
अणु
	काष्ठा amd_ntb_dev *ndev = ntb_ndev(ntb);
	व्योम __iomem *mmio = ndev->self_mmio;
	अचिन्हित दीर्घ flags;

	अगर (db_bits & ~ndev->db_valid_mask)
		वापस -EINVAL;

	spin_lock_irqsave(&ndev->db_mask_lock, flags);
	ndev->db_mask |= db_bits;
	ग_लिखोw((u16)ndev->db_mask, mmio + AMD_DBMASK_OFFSET);
	spin_unlock_irqrestore(&ndev->db_mask_lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक amd_ntb_db_clear_mask(काष्ठा ntb_dev *ntb, u64 db_bits)
अणु
	काष्ठा amd_ntb_dev *ndev = ntb_ndev(ntb);
	व्योम __iomem *mmio = ndev->self_mmio;
	अचिन्हित दीर्घ flags;

	अगर (db_bits & ~ndev->db_valid_mask)
		वापस -EINVAL;

	spin_lock_irqsave(&ndev->db_mask_lock, flags);
	ndev->db_mask &= ~db_bits;
	ग_लिखोw((u16)ndev->db_mask, mmio + AMD_DBMASK_OFFSET);
	spin_unlock_irqrestore(&ndev->db_mask_lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक amd_ntb_peer_db_set(काष्ठा ntb_dev *ntb, u64 db_bits)
अणु
	काष्ठा amd_ntb_dev *ndev = ntb_ndev(ntb);
	व्योम __iomem *mmio = ndev->self_mmio;

	ग_लिखोw((u16)db_bits, mmio + AMD_DBREQ_OFFSET);

	वापस 0;
पूर्ण

अटल पूर्णांक amd_ntb_spad_count(काष्ठा ntb_dev *ntb)
अणु
	वापस ntb_ndev(ntb)->spad_count;
पूर्ण

अटल u32 amd_ntb_spad_पढ़ो(काष्ठा ntb_dev *ntb, पूर्णांक idx)
अणु
	काष्ठा amd_ntb_dev *ndev = ntb_ndev(ntb);
	व्योम __iomem *mmio = ndev->self_mmio;
	u32 offset;

	अगर (idx < 0 || idx >= ndev->spad_count)
		वापस 0;

	offset = ndev->self_spad + (idx << 2);
	वापस पढ़ोl(mmio + AMD_SPAD_OFFSET + offset);
पूर्ण

अटल पूर्णांक amd_ntb_spad_ग_लिखो(काष्ठा ntb_dev *ntb,
			      पूर्णांक idx, u32 val)
अणु
	काष्ठा amd_ntb_dev *ndev = ntb_ndev(ntb);
	व्योम __iomem *mmio = ndev->self_mmio;
	u32 offset;

	अगर (idx < 0 || idx >= ndev->spad_count)
		वापस -EINVAL;

	offset = ndev->self_spad + (idx << 2);
	ग_लिखोl(val, mmio + AMD_SPAD_OFFSET + offset);

	वापस 0;
पूर्ण

अटल u32 amd_ntb_peer_spad_पढ़ो(काष्ठा ntb_dev *ntb, पूर्णांक pidx, पूर्णांक sidx)
अणु
	काष्ठा amd_ntb_dev *ndev = ntb_ndev(ntb);
	व्योम __iomem *mmio = ndev->self_mmio;
	u32 offset;

	अगर (sidx < 0 || sidx >= ndev->spad_count)
		वापस -EINVAL;

	offset = ndev->peer_spad + (sidx << 2);
	वापस पढ़ोl(mmio + AMD_SPAD_OFFSET + offset);
पूर्ण

अटल पूर्णांक amd_ntb_peer_spad_ग_लिखो(काष्ठा ntb_dev *ntb, पूर्णांक pidx,
				   पूर्णांक sidx, u32 val)
अणु
	काष्ठा amd_ntb_dev *ndev = ntb_ndev(ntb);
	व्योम __iomem *mmio = ndev->self_mmio;
	u32 offset;

	अगर (sidx < 0 || sidx >= ndev->spad_count)
		वापस -EINVAL;

	offset = ndev->peer_spad + (sidx << 2);
	ग_लिखोl(val, mmio + AMD_SPAD_OFFSET + offset);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा ntb_dev_ops amd_ntb_ops = अणु
	.mw_count		= amd_ntb_mw_count,
	.mw_get_align		= amd_ntb_mw_get_align,
	.mw_set_trans		= amd_ntb_mw_set_trans,
	.peer_mw_count		= amd_ntb_peer_mw_count,
	.peer_mw_get_addr	= amd_ntb_peer_mw_get_addr,
	.link_is_up		= amd_ntb_link_is_up,
	.link_enable		= amd_ntb_link_enable,
	.link_disable		= amd_ntb_link_disable,
	.db_valid_mask		= amd_ntb_db_valid_mask,
	.db_vector_count	= amd_ntb_db_vector_count,
	.db_vector_mask		= amd_ntb_db_vector_mask,
	.db_पढ़ो		= amd_ntb_db_पढ़ो,
	.db_clear		= amd_ntb_db_clear,
	.db_set_mask		= amd_ntb_db_set_mask,
	.db_clear_mask		= amd_ntb_db_clear_mask,
	.peer_db_set		= amd_ntb_peer_db_set,
	.spad_count		= amd_ntb_spad_count,
	.spad_पढ़ो		= amd_ntb_spad_पढ़ो,
	.spad_ग_लिखो		= amd_ntb_spad_ग_लिखो,
	.peer_spad_पढ़ो		= amd_ntb_peer_spad_पढ़ो,
	.peer_spad_ग_लिखो	= amd_ntb_peer_spad_ग_लिखो,
पूर्ण;

अटल व्योम amd_ack_smu(काष्ठा amd_ntb_dev *ndev, u32 bit)
अणु
	व्योम __iomem *mmio = ndev->self_mmio;
	पूर्णांक reg;

	reg = पढ़ोl(mmio + AMD_SMUACK_OFFSET);
	reg |= bit;
	ग_लिखोl(reg, mmio + AMD_SMUACK_OFFSET);
पूर्ण

अटल व्योम amd_handle_event(काष्ठा amd_ntb_dev *ndev, पूर्णांक vec)
अणु
	व्योम __iomem *mmio = ndev->self_mmio;
	काष्ठा device *dev = &ndev->ntb.pdev->dev;
	u32 status;

	status = पढ़ोl(mmio + AMD_INTSTAT_OFFSET);
	अगर (!(status & AMD_EVENT_INTMASK))
		वापस;

	dev_dbg(dev, "status = 0x%x and vec = %d\n", status, vec);

	status &= AMD_EVENT_INTMASK;
	चयन (status) अणु
	हाल AMD_PEER_FLUSH_EVENT:
		ndev->peer_sta |= AMD_PEER_FLUSH_EVENT;
		dev_info(dev, "Flush is done.\n");
		अवरोध;
	हाल AMD_PEER_RESET_EVENT:
	हाल AMD_LINK_DOWN_EVENT:
		ndev->peer_sta |= status;
		अगर (status == AMD_LINK_DOWN_EVENT)
			ndev->peer_sta &= ~AMD_LINK_UP_EVENT;

		amd_ack_smu(ndev, status);

		/* link करोwn first */
		ntb_link_event(&ndev->ntb);
		/* polling peer status */
		schedule_delayed_work(&ndev->hb_समयr, AMD_LINK_HB_TIMEOUT);

		अवरोध;
	हाल AMD_PEER_D3_EVENT:
	हाल AMD_PEER_PMETO_EVENT:
	हाल AMD_LINK_UP_EVENT:
		ndev->peer_sta |= status;
		अगर (status == AMD_LINK_UP_EVENT)
			ndev->peer_sta &= ~AMD_LINK_DOWN_EVENT;
		अन्यथा अगर (status == AMD_PEER_D3_EVENT)
			ndev->peer_sta &= ~AMD_PEER_D0_EVENT;

		amd_ack_smu(ndev, status);

		/* link करोwn */
		ntb_link_event(&ndev->ntb);

		अवरोध;
	हाल AMD_PEER_D0_EVENT:
		mmio = ndev->peer_mmio;
		status = पढ़ोl(mmio + AMD_PMESTAT_OFFSET);
		/* check अगर this is WAKEUP event */
		अगर (status & 0x1)
			dev_info(dev, "Wakeup is done.\n");

		ndev->peer_sta |= AMD_PEER_D0_EVENT;
		ndev->peer_sta &= ~AMD_PEER_D3_EVENT;
		amd_ack_smu(ndev, AMD_PEER_D0_EVENT);

		/* start a समयr to poll link status */
		schedule_delayed_work(&ndev->hb_समयr,
				      AMD_LINK_HB_TIMEOUT);
		अवरोध;
	शेष:
		dev_info(dev, "event status = 0x%x.\n", status);
		अवरोध;
	पूर्ण

	/* Clear the पूर्णांकerrupt status */
	ग_लिखोl(status, mmio + AMD_INTSTAT_OFFSET);
पूर्ण

अटल व्योम amd_handle_db_event(काष्ठा amd_ntb_dev *ndev, पूर्णांक vec)
अणु
	काष्ठा device *dev = &ndev->ntb.pdev->dev;
	u64 status;

	status = amd_ntb_db_पढ़ो(&ndev->ntb);

	dev_dbg(dev, "status = 0x%llx and vec = %d\n", status, vec);

	/*
	 * Since we had reserved highest order bit of DB क्रम संकेतing peer of
	 * a special event, this is the only status bit we should be concerned
	 * here now.
	 */
	अगर (status & BIT(ndev->db_last_bit)) अणु
		ntb_db_clear(&ndev->ntb, BIT(ndev->db_last_bit));
		/* send link करोwn event notअगरication */
		ntb_link_event(&ndev->ntb);

		/*
		 * If we are here, that means the peer has संकेतled a special
		 * event which notअगरies that the peer driver has been
		 * un-loaded क्रम some reason. Since there is a chance that the
		 * peer will load its driver again someसमय, we schedule link
		 * polling routine.
		 */
		schedule_delayed_work(&ndev->hb_समयr, AMD_LINK_HB_TIMEOUT);
	पूर्ण
पूर्ण

अटल irqवापस_t ndev_पूर्णांकerrupt(काष्ठा amd_ntb_dev *ndev, पूर्णांक vec)
अणु
	dev_dbg(&ndev->ntb.pdev->dev, "vec %d\n", vec);

	अगर (vec > (AMD_DB_CNT - 1) || (ndev->msix_vec_count == 1))
		amd_handle_event(ndev, vec);

	अगर (vec < AMD_DB_CNT) अणु
		amd_handle_db_event(ndev, vec);
		ntb_db_event(&ndev->ntb, vec);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t ndev_vec_isr(पूर्णांक irq, व्योम *dev)
अणु
	काष्ठा amd_ntb_vec *nvec = dev;

	वापस ndev_पूर्णांकerrupt(nvec->ndev, nvec->num);
पूर्ण

अटल irqवापस_t ndev_irq_isr(पूर्णांक irq, व्योम *dev)
अणु
	काष्ठा amd_ntb_dev *ndev = dev;

	वापस ndev_पूर्णांकerrupt(ndev, irq - ndev->ntb.pdev->irq);
पूर्ण

अटल पूर्णांक ndev_init_isr(काष्ठा amd_ntb_dev *ndev,
			 पूर्णांक msix_min, पूर्णांक msix_max)
अणु
	काष्ठा pci_dev *pdev;
	पूर्णांक rc, i, msix_count, node;

	pdev = ndev->ntb.pdev;

	node = dev_to_node(&pdev->dev);

	ndev->db_mask = ndev->db_valid_mask;

	/* Try to set up msix irq */
	ndev->vec = kसुस्मृति_node(msix_max, माप(*ndev->vec),
				 GFP_KERNEL, node);
	अगर (!ndev->vec)
		जाओ err_msix_vec_alloc;

	ndev->msix = kसुस्मृति_node(msix_max, माप(*ndev->msix),
				  GFP_KERNEL, node);
	अगर (!ndev->msix)
		जाओ err_msix_alloc;

	क्रम (i = 0; i < msix_max; ++i)
		ndev->msix[i].entry = i;

	msix_count = pci_enable_msix_range(pdev, ndev->msix,
					   msix_min, msix_max);
	अगर (msix_count < 0)
		जाओ err_msix_enable;

	/* NOTE: Disable MSIX अगर msix count is less than 16 because of
	 * hardware limitation.
	 */
	अगर (msix_count < msix_min) अणु
		pci_disable_msix(pdev);
		जाओ err_msix_enable;
	पूर्ण

	क्रम (i = 0; i < msix_count; ++i) अणु
		ndev->vec[i].ndev = ndev;
		ndev->vec[i].num = i;
		rc = request_irq(ndev->msix[i].vector, ndev_vec_isr, 0,
				 "ndev_vec_isr", &ndev->vec[i]);
		अगर (rc)
			जाओ err_msix_request;
	पूर्ण

	dev_dbg(&pdev->dev, "Using msix interrupts\n");
	ndev->db_count = msix_min;
	ndev->msix_vec_count = msix_max;
	वापस 0;

err_msix_request:
	जबतक (i-- > 0)
		मुक्त_irq(ndev->msix[i].vector, &ndev->vec[i]);
	pci_disable_msix(pdev);
err_msix_enable:
	kमुक्त(ndev->msix);
err_msix_alloc:
	kमुक्त(ndev->vec);
err_msix_vec_alloc:
	ndev->msix = शून्य;
	ndev->vec = शून्य;

	/* Try to set up msi irq */
	rc = pci_enable_msi(pdev);
	अगर (rc)
		जाओ err_msi_enable;

	rc = request_irq(pdev->irq, ndev_irq_isr, 0,
			 "ndev_irq_isr", ndev);
	अगर (rc)
		जाओ err_msi_request;

	dev_dbg(&pdev->dev, "Using msi interrupts\n");
	ndev->db_count = 1;
	ndev->msix_vec_count = 1;
	वापस 0;

err_msi_request:
	pci_disable_msi(pdev);
err_msi_enable:

	/* Try to set up पूर्णांकx irq */
	pci_पूर्णांकx(pdev, 1);

	rc = request_irq(pdev->irq, ndev_irq_isr, IRQF_SHARED,
			 "ndev_irq_isr", ndev);
	अगर (rc)
		जाओ err_पूर्णांकx_request;

	dev_dbg(&pdev->dev, "Using intx interrupts\n");
	ndev->db_count = 1;
	ndev->msix_vec_count = 1;
	वापस 0;

err_पूर्णांकx_request:
	वापस rc;
पूर्ण

अटल व्योम ndev_deinit_isr(काष्ठा amd_ntb_dev *ndev)
अणु
	काष्ठा pci_dev *pdev;
	व्योम __iomem *mmio = ndev->self_mmio;
	पूर्णांक i;

	pdev = ndev->ntb.pdev;

	/* Mask all करोorbell पूर्णांकerrupts */
	ndev->db_mask = ndev->db_valid_mask;
	ग_लिखोl(ndev->db_mask, mmio + AMD_DBMASK_OFFSET);

	अगर (ndev->msix) अणु
		i = ndev->msix_vec_count;
		जबतक (i--)
			मुक्त_irq(ndev->msix[i].vector, &ndev->vec[i]);
		pci_disable_msix(pdev);
		kमुक्त(ndev->msix);
		kमुक्त(ndev->vec);
	पूर्ण अन्यथा अणु
		मुक्त_irq(pdev->irq, ndev);
		अगर (pci_dev_msi_enabled(pdev))
			pci_disable_msi(pdev);
		अन्यथा
			pci_पूर्णांकx(pdev, 0);
	पूर्ण
पूर्ण

अटल sमाप_प्रकार ndev_debugfs_पढ़ो(काष्ठा file *filp, अक्षर __user *ubuf,
				 माप_प्रकार count, loff_t *offp)
अणु
	काष्ठा amd_ntb_dev *ndev;
	व्योम __iomem *mmio;
	अक्षर *buf;
	माप_प्रकार buf_size;
	sमाप_प्रकार ret, off;
	जोड़ अणु u64 v64; u32 v32; u16 v16; पूर्ण u;

	ndev = filp->निजी_data;
	mmio = ndev->self_mmio;

	buf_size = min(count, 0x800ul);

	buf = kदो_स्मृति(buf_size, GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;

	off = 0;

	off += scnम_लिखो(buf + off, buf_size - off,
			 "NTB Device Information:\n");

	off += scnम_लिखो(buf + off, buf_size - off,
			 "Connection Topology -\t%s\n",
			 ntb_topo_string(ndev->ntb.topo));

	off += scnम_लिखो(buf + off, buf_size - off,
			 "LNK STA -\t\t%#06x\n", ndev->lnk_sta);

	अगर (!amd_link_is_up(ndev)) अणु
		off += scnम_लिखो(buf + off, buf_size - off,
				 "Link Status -\t\tDown\n");
	पूर्ण अन्यथा अणु
		off += scnम_लिखो(buf + off, buf_size - off,
				 "Link Status -\t\tUp\n");
		off += scnम_लिखो(buf + off, buf_size - off,
				 "Link Speed -\t\tPCI-E Gen %u\n",
				 NTB_LNK_STA_SPEED(ndev->lnk_sta));
		off += scnम_लिखो(buf + off, buf_size - off,
				 "Link Width -\t\tx%u\n",
				 NTB_LNK_STA_WIDTH(ndev->lnk_sta));
	पूर्ण

	off += scnम_लिखो(buf + off, buf_size - off,
			 "Memory Window Count -\t%u\n", ndev->mw_count);
	off += scnम_लिखो(buf + off, buf_size - off,
			 "Scratchpad Count -\t%u\n", ndev->spad_count);
	off += scnम_लिखो(buf + off, buf_size - off,
			 "Doorbell Count -\t%u\n", ndev->db_count);
	off += scnम_लिखो(buf + off, buf_size - off,
			 "MSIX Vector Count -\t%u\n", ndev->msix_vec_count);

	off += scnम_लिखो(buf + off, buf_size - off,
			 "Doorbell Valid Mask -\t%#llx\n", ndev->db_valid_mask);

	u.v32 = पढ़ोl(ndev->self_mmio + AMD_DBMASK_OFFSET);
	off += scnम_लिखो(buf + off, buf_size - off,
			 "Doorbell Mask -\t\t\t%#06x\n", u.v32);

	u.v32 = पढ़ोl(mmio + AMD_DBSTAT_OFFSET);
	off += scnम_लिखो(buf + off, buf_size - off,
			 "Doorbell Bell -\t\t\t%#06x\n", u.v32);

	off += scnम_लिखो(buf + off, buf_size - off,
			 "\nNTB Incoming XLAT:\n");

	u.v64 = पढ़ो64(mmio + AMD_BAR1XLAT_OFFSET);
	off += scnम_लिखो(buf + off, buf_size - off,
			 "XLAT1 -\t\t%#018llx\n", u.v64);

	u.v64 = पढ़ो64(ndev->self_mmio + AMD_BAR23XLAT_OFFSET);
	off += scnम_लिखो(buf + off, buf_size - off,
			 "XLAT23 -\t\t%#018llx\n", u.v64);

	u.v64 = पढ़ो64(ndev->self_mmio + AMD_BAR45XLAT_OFFSET);
	off += scnम_लिखो(buf + off, buf_size - off,
			 "XLAT45 -\t\t%#018llx\n", u.v64);

	u.v32 = पढ़ोl(mmio + AMD_BAR1LMT_OFFSET);
	off += scnम_लिखो(buf + off, buf_size - off,
			 "LMT1 -\t\t\t%#06x\n", u.v32);

	u.v64 = पढ़ो64(ndev->self_mmio + AMD_BAR23LMT_OFFSET);
	off += scnम_लिखो(buf + off, buf_size - off,
			 "LMT23 -\t\t\t%#018llx\n", u.v64);

	u.v64 = पढ़ो64(ndev->self_mmio + AMD_BAR45LMT_OFFSET);
	off += scnम_लिखो(buf + off, buf_size - off,
			 "LMT45 -\t\t\t%#018llx\n", u.v64);

	ret = simple_पढ़ो_from_buffer(ubuf, count, offp, buf, off);
	kमुक्त(buf);
	वापस ret;
पूर्ण

अटल व्योम ndev_init_debugfs(काष्ठा amd_ntb_dev *ndev)
अणु
	अगर (!debugfs_dir) अणु
		ndev->debugfs_dir = शून्य;
		ndev->debugfs_info = शून्य;
	पूर्ण अन्यथा अणु
		ndev->debugfs_dir =
			debugfs_create_dir(pci_name(ndev->ntb.pdev),
					   debugfs_dir);
		अगर (!ndev->debugfs_dir)
			ndev->debugfs_info = शून्य;
		अन्यथा
			ndev->debugfs_info =
				debugfs_create_file("info", S_IRUSR,
						    ndev->debugfs_dir, ndev,
						    &amd_ntb_debugfs_info);
	पूर्ण
पूर्ण

अटल व्योम ndev_deinit_debugfs(काष्ठा amd_ntb_dev *ndev)
अणु
	debugfs_हटाओ_recursive(ndev->debugfs_dir);
पूर्ण

अटल अंतरभूत व्योम ndev_init_काष्ठा(काष्ठा amd_ntb_dev *ndev,
				    काष्ठा pci_dev *pdev)
अणु
	ndev->ntb.pdev = pdev;
	ndev->ntb.topo = NTB_TOPO_NONE;
	ndev->ntb.ops = &amd_ntb_ops;
	ndev->पूर्णांक_mask = AMD_EVENT_INTMASK;
	spin_lock_init(&ndev->db_mask_lock);
पूर्ण

अटल पूर्णांक amd_poll_link(काष्ठा amd_ntb_dev *ndev)
अणु
	व्योम __iomem *mmio = ndev->peer_mmio;
	u32 reg;

	reg = पढ़ोl(mmio + AMD_SIDEINFO_OFFSET);
	reg &= AMD_SIDE_READY;

	dev_dbg(&ndev->ntb.pdev->dev, "%s: reg_val = 0x%x.\n", __func__, reg);

	ndev->cntl_sta = reg;

	amd_ntb_get_link_status(ndev);

	वापस ndev->cntl_sta;
पूर्ण

अटल व्योम amd_link_hb(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा amd_ntb_dev *ndev = hb_ndev(work);

	अगर (amd_poll_link(ndev))
		ntb_link_event(&ndev->ntb);

	अगर (!amd_link_is_up(ndev))
		schedule_delayed_work(&ndev->hb_समयr, AMD_LINK_HB_TIMEOUT);
पूर्ण

अटल पूर्णांक amd_init_isr(काष्ठा amd_ntb_dev *ndev)
अणु
	वापस ndev_init_isr(ndev, AMD_DB_CNT, AMD_MSIX_VECTOR_CNT);
पूर्ण

अटल व्योम amd_set_side_info_reg(काष्ठा amd_ntb_dev *ndev, bool peer)
अणु
	व्योम __iomem *mmio = शून्य;
	अचिन्हित पूर्णांक reg;

	अगर (peer)
		mmio = ndev->peer_mmio;
	अन्यथा
		mmio = ndev->self_mmio;

	reg = पढ़ोl(mmio + AMD_SIDEINFO_OFFSET);
	अगर (!(reg & AMD_SIDE_READY)) अणु
		reg |= AMD_SIDE_READY;
		ग_लिखोl(reg, mmio + AMD_SIDEINFO_OFFSET);
	पूर्ण
पूर्ण

अटल व्योम amd_clear_side_info_reg(काष्ठा amd_ntb_dev *ndev, bool peer)
अणु
	व्योम __iomem *mmio = शून्य;
	अचिन्हित पूर्णांक reg;

	अगर (peer)
		mmio = ndev->peer_mmio;
	अन्यथा
		mmio = ndev->self_mmio;

	reg = पढ़ोl(mmio + AMD_SIDEINFO_OFFSET);
	अगर (reg & AMD_SIDE_READY) अणु
		reg &= ~AMD_SIDE_READY;
		ग_लिखोl(reg, mmio + AMD_SIDEINFO_OFFSET);
		पढ़ोl(mmio + AMD_SIDEINFO_OFFSET);
	पूर्ण
पूर्ण

अटल व्योम amd_init_side_info(काष्ठा amd_ntb_dev *ndev)
अणु
	व्योम __iomem *mmio = ndev->self_mmio;
	u32 ntb_ctl;

	amd_set_side_info_reg(ndev, false);

	ntb_ctl = पढ़ोl(mmio + AMD_CNTL_OFFSET);
	ntb_ctl |= (PMM_REG_CTL | SMM_REG_CTL);
	ग_लिखोl(ntb_ctl, mmio + AMD_CNTL_OFFSET);
पूर्ण

अटल व्योम amd_deinit_side_info(काष्ठा amd_ntb_dev *ndev)
अणु
	व्योम __iomem *mmio = ndev->self_mmio;
	u32 ntb_ctl;

	amd_clear_side_info_reg(ndev, false);

	ntb_ctl = पढ़ोl(mmio + AMD_CNTL_OFFSET);
	ntb_ctl &= ~(PMM_REG_CTL | SMM_REG_CTL);
	ग_लिखोl(ntb_ctl, mmio + AMD_CNTL_OFFSET);
पूर्ण

अटल पूर्णांक amd_init_ntb(काष्ठा amd_ntb_dev *ndev)
अणु
	व्योम __iomem *mmio = ndev->self_mmio;

	ndev->mw_count = ndev->dev_data->mw_count;
	ndev->spad_count = AMD_SPADS_CNT;
	ndev->db_count = AMD_DB_CNT;

	चयन (ndev->ntb.topo) अणु
	हाल NTB_TOPO_PRI:
	हाल NTB_TOPO_SEC:
		ndev->spad_count >>= 1;
		अगर (ndev->ntb.topo == NTB_TOPO_PRI) अणु
			ndev->self_spad = 0;
			ndev->peer_spad = 0x20;
		पूर्ण अन्यथा अणु
			ndev->self_spad = 0x20;
			ndev->peer_spad = 0;
		पूर्ण

		INIT_DELAYED_WORK(&ndev->hb_समयr, amd_link_hb);
		schedule_delayed_work(&ndev->hb_समयr, AMD_LINK_HB_TIMEOUT);

		अवरोध;
	शेष:
		dev_err(&ndev->ntb.pdev->dev,
			"AMD NTB does not support B2B mode.\n");
		वापस -EINVAL;
	पूर्ण

	/* Mask event पूर्णांकerrupts */
	ग_लिखोl(ndev->पूर्णांक_mask, mmio + AMD_INTMASK_OFFSET);

	वापस 0;
पूर्ण

अटल क्रमागत ntb_topo amd_get_topo(काष्ठा amd_ntb_dev *ndev)
अणु
	व्योम __iomem *mmio = ndev->self_mmio;
	u32 info;

	info = पढ़ोl(mmio + AMD_SIDEINFO_OFFSET);
	अगर (info & AMD_SIDE_MASK)
		वापस NTB_TOPO_SEC;
	अन्यथा
		वापस NTB_TOPO_PRI;
पूर्ण

अटल पूर्णांक amd_init_dev(काष्ठा amd_ntb_dev *ndev)
अणु
	व्योम __iomem *mmio = ndev->self_mmio;
	काष्ठा pci_dev *pdev;
	पूर्णांक rc = 0;

	pdev = ndev->ntb.pdev;

	ndev->ntb.topo = amd_get_topo(ndev);
	dev_dbg(&pdev->dev, "AMD NTB topo is %s\n",
		ntb_topo_string(ndev->ntb.topo));

	rc = amd_init_ntb(ndev);
	अगर (rc)
		वापस rc;

	rc = amd_init_isr(ndev);
	अगर (rc) अणु
		dev_err(&pdev->dev, "fail to init isr.\n");
		वापस rc;
	पूर्ण

	ndev->db_valid_mask = BIT_ULL(ndev->db_count) - 1;
	/*
	 * We reserve the highest order bit of the DB रेजिस्टर which will
	 * be used to notअगरy peer when the driver on this side is being
	 * un-loaded.
	 */
	ndev->db_last_bit =
			find_last_bit((अचिन्हित दीर्घ *)&ndev->db_valid_mask,
				      hweight64(ndev->db_valid_mask));
	ग_लिखोw((u16)~BIT(ndev->db_last_bit), mmio + AMD_DBMASK_OFFSET);
	/*
	 * Since now there is one less bit to account क्रम, the DB count
	 * and DB mask should be adjusted accordingly.
	 */
	ndev->db_count -= 1;
	ndev->db_valid_mask = BIT_ULL(ndev->db_count) - 1;

	/* Enable Link-Up and Link-Down event पूर्णांकerrupts */
	ndev->पूर्णांक_mask &= ~(AMD_LINK_UP_EVENT | AMD_LINK_DOWN_EVENT);
	ग_लिखोl(ndev->पूर्णांक_mask, mmio + AMD_INTMASK_OFFSET);

	वापस 0;
पूर्ण

अटल व्योम amd_deinit_dev(काष्ठा amd_ntb_dev *ndev)
अणु
	cancel_delayed_work_sync(&ndev->hb_समयr);

	ndev_deinit_isr(ndev);
पूर्ण

अटल पूर्णांक amd_ntb_init_pci(काष्ठा amd_ntb_dev *ndev,
			    काष्ठा pci_dev *pdev)
अणु
	पूर्णांक rc;

	pci_set_drvdata(pdev, ndev);

	rc = pci_enable_device(pdev);
	अगर (rc)
		जाओ err_pci_enable;

	rc = pci_request_regions(pdev, NTB_NAME);
	अगर (rc)
		जाओ err_pci_regions;

	pci_set_master(pdev);

	rc = pci_set_dma_mask(pdev, DMA_BIT_MASK(64));
	अगर (rc) अणु
		rc = pci_set_dma_mask(pdev, DMA_BIT_MASK(32));
		अगर (rc)
			जाओ err_dma_mask;
		dev_warn(&pdev->dev, "Cannot DMA highmem\n");
	पूर्ण

	rc = pci_set_consistent_dma_mask(pdev, DMA_BIT_MASK(64));
	अगर (rc) अणु
		rc = pci_set_consistent_dma_mask(pdev, DMA_BIT_MASK(32));
		अगर (rc)
			जाओ err_dma_mask;
		dev_warn(&pdev->dev, "Cannot DMA consistent highmem\n");
	पूर्ण

	ndev->self_mmio = pci_iomap(pdev, 0, 0);
	अगर (!ndev->self_mmio) अणु
		rc = -EIO;
		जाओ err_dma_mask;
	पूर्ण
	ndev->peer_mmio = ndev->self_mmio + AMD_PEER_OFFSET;

	वापस 0;

err_dma_mask:
	pci_clear_master(pdev);
	pci_release_regions(pdev);
err_pci_regions:
	pci_disable_device(pdev);
err_pci_enable:
	pci_set_drvdata(pdev, शून्य);
	वापस rc;
पूर्ण

अटल व्योम amd_ntb_deinit_pci(काष्ठा amd_ntb_dev *ndev)
अणु
	काष्ठा pci_dev *pdev = ndev->ntb.pdev;

	pci_iounmap(pdev, ndev->self_mmio);

	pci_clear_master(pdev);
	pci_release_regions(pdev);
	pci_disable_device(pdev);
	pci_set_drvdata(pdev, शून्य);
पूर्ण

अटल पूर्णांक amd_ntb_pci_probe(काष्ठा pci_dev *pdev,
			     स्थिर काष्ठा pci_device_id *id)
अणु
	काष्ठा amd_ntb_dev *ndev;
	पूर्णांक rc, node;

	node = dev_to_node(&pdev->dev);

	ndev = kzalloc_node(माप(*ndev), GFP_KERNEL, node);
	अगर (!ndev) अणु
		rc = -ENOMEM;
		जाओ err_ndev;
	पूर्ण

	ndev->dev_data = (काष्ठा ntb_dev_data *)id->driver_data;

	ndev_init_काष्ठा(ndev, pdev);

	rc = amd_ntb_init_pci(ndev, pdev);
	अगर (rc)
		जाओ err_init_pci;

	rc = amd_init_dev(ndev);
	अगर (rc)
		जाओ err_init_dev;

	/* ग_लिखो side info */
	amd_init_side_info(ndev);

	amd_poll_link(ndev);

	ndev_init_debugfs(ndev);

	rc = ntb_रेजिस्टर_device(&ndev->ntb);
	अगर (rc)
		जाओ err_रेजिस्टर;

	dev_info(&pdev->dev, "NTB device registered.\n");

	वापस 0;

err_रेजिस्टर:
	ndev_deinit_debugfs(ndev);
	amd_deinit_dev(ndev);
err_init_dev:
	amd_ntb_deinit_pci(ndev);
err_init_pci:
	kमुक्त(ndev);
err_ndev:
	वापस rc;
पूर्ण

अटल व्योम amd_ntb_pci_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा amd_ntb_dev *ndev = pci_get_drvdata(pdev);

	/*
	 * Clear the READY bit in SIDEINFO रेजिस्टर beक्रमe sending DB event
	 * to the peer. This will make sure that when the peer handles the
	 * DB event, it correctly पढ़ोs this bit as being 0.
	 */
	amd_deinit_side_info(ndev);
	ntb_peer_db_set(&ndev->ntb, BIT_ULL(ndev->db_last_bit));
	ntb_unरेजिस्टर_device(&ndev->ntb);
	ndev_deinit_debugfs(ndev);
	amd_deinit_dev(ndev);
	amd_ntb_deinit_pci(ndev);
	kमुक्त(ndev);
पूर्ण

अटल व्योम amd_ntb_pci_shutकरोwn(काष्ठा pci_dev *pdev)
अणु
	काष्ठा amd_ntb_dev *ndev = pci_get_drvdata(pdev);

	/* Send link करोwn notअगरication */
	ntb_link_event(&ndev->ntb);

	amd_deinit_side_info(ndev);
	ntb_peer_db_set(&ndev->ntb, BIT_ULL(ndev->db_last_bit));
	ntb_unरेजिस्टर_device(&ndev->ntb);
	ndev_deinit_debugfs(ndev);
	amd_deinit_dev(ndev);
	amd_ntb_deinit_pci(ndev);
	kमुक्त(ndev);
पूर्ण

अटल स्थिर काष्ठा file_operations amd_ntb_debugfs_info = अणु
	.owner = THIS_MODULE,
	.खोलो = simple_खोलो,
	.पढ़ो = ndev_debugfs_पढ़ो,
पूर्ण;

अटल स्थिर काष्ठा ntb_dev_data dev_data[] = अणु
	अणु /* क्रम device 145b */
		.mw_count = 3,
		.mw_idx = 1,
	पूर्ण,
	अणु /* क्रम device 148b */
		.mw_count = 2,
		.mw_idx = 2,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा pci_device_id amd_ntb_pci_tbl[] = अणु
	अणु PCI_VDEVICE(AMD, 0x145b), (kernel_uदीर्घ_t)&dev_data[0] पूर्ण,
	अणु PCI_VDEVICE(AMD, 0x148b), (kernel_uदीर्घ_t)&dev_data[1] पूर्ण,
	अणु PCI_VDEVICE(HYGON, 0x145b), (kernel_uदीर्घ_t)&dev_data[0] पूर्ण,
	अणु 0, पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(pci, amd_ntb_pci_tbl);

अटल काष्ठा pci_driver amd_ntb_pci_driver = अणु
	.name		= KBUILD_MODNAME,
	.id_table	= amd_ntb_pci_tbl,
	.probe		= amd_ntb_pci_probe,
	.हटाओ		= amd_ntb_pci_हटाओ,
	.shutकरोwn	= amd_ntb_pci_shutकरोwn,
पूर्ण;

अटल पूर्णांक __init amd_ntb_pci_driver_init(व्योम)
अणु
	pr_info("%s %s\n", NTB_DESC, NTB_VER);

	अगर (debugfs_initialized())
		debugfs_dir = debugfs_create_dir(KBUILD_MODNAME, शून्य);

	वापस pci_रेजिस्टर_driver(&amd_ntb_pci_driver);
पूर्ण
module_init(amd_ntb_pci_driver_init);

अटल व्योम __निकास amd_ntb_pci_driver_निकास(व्योम)
अणु
	pci_unरेजिस्टर_driver(&amd_ntb_pci_driver);
	debugfs_हटाओ_recursive(debugfs_dir);
पूर्ण
module_निकास(amd_ntb_pci_driver_निकास);
