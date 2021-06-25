<शैली गुरु>
/*
 * This file is provided under a dual BSD/GPLv2 license.  When using or
 *   redistributing this file, you may करो so under either license.
 *
 *   GPL LICENSE SUMMARY
 *
 *   Copyright(c) 2012 Intel Corporation. All rights reserved.
 *   Copyright (C) 2015 EMC Corporation. All Rights Reserved.
 *   Copyright (C) 2016 T-Platक्रमms. All Rights Reserved.
 *
 *   This program is मुक्त software; you can redistribute it and/or modअगरy
 *   it under the terms of version 2 of the GNU General Public License as
 *   published by the Free Software Foundation.
 *
 *   BSD LICENSE
 *
 *   Copyright(c) 2012 Intel Corporation. All rights reserved.
 *   Copyright (C) 2015 EMC Corporation. All Rights Reserved.
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
 *     * Neither the name of Intel Corporation nor the names of its
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
 * Intel PCIe NTB Linux driver
 */

#समावेश <linux/debugfs.h>
#समावेश <linux/delay.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/slab.h>
#समावेश <linux/ntb.h>

#समावेश "ntb_hw_intel.h"
#समावेश "ntb_hw_gen1.h"
#समावेश "ntb_hw_gen3.h"
#समावेश "ntb_hw_gen4.h"

#घोषणा NTB_NAME	"ntb_hw_intel"
#घोषणा NTB_DESC	"Intel(R) PCI-E Non-Transparent Bridge Driver"
#घोषणा NTB_VER		"2.0"

MODULE_DESCRIPTION(NTB_DESC);
MODULE_VERSION(NTB_VER);
MODULE_LICENSE("Dual BSD/GPL");
MODULE_AUTHOR("Intel Corporation");

#घोषणा bar0_off(base, bar) ((base) + ((bar) << 2))
#घोषणा bar2_off(base, bar) bar0_off(base, (bar) - 2)

अटल स्थिर काष्ठा पूर्णांकel_ntb_reg xeon_reg;
अटल स्थिर काष्ठा पूर्णांकel_ntb_alt_reg xeon_pri_reg;
अटल स्थिर काष्ठा पूर्णांकel_ntb_alt_reg xeon_sec_reg;
अटल स्थिर काष्ठा पूर्णांकel_ntb_alt_reg xeon_b2b_reg;
अटल स्थिर काष्ठा पूर्णांकel_ntb_xlat_reg xeon_pri_xlat;
अटल स्थिर काष्ठा पूर्णांकel_ntb_xlat_reg xeon_sec_xlat;
अटल स्थिर काष्ठा ntb_dev_ops पूर्णांकel_ntb_ops;

अटल स्थिर काष्ठा file_operations पूर्णांकel_ntb_debugfs_info;
अटल काष्ठा dentry *debugfs_dir;

अटल पूर्णांक b2b_mw_idx = -1;
module_param(b2b_mw_idx, पूर्णांक, 0644);
MODULE_PARM_DESC(b2b_mw_idx, "Use this mw idx to access the peer ntb.  A "
		 "value of zero or positive starts from first mw idx, and a "
		 "negative value starts from last mw idx.  Both sides MUST "
		 "set the same value here!");

अटल अचिन्हित पूर्णांक b2b_mw_share;
module_param(b2b_mw_share, uपूर्णांक, 0644);
MODULE_PARM_DESC(b2b_mw_share, "If the b2b mw is large enough, configure the "
		 "ntb so that the peer ntb only occupies the first half of "
		 "the mw, so the second half can still be used as a mw.  Both "
		 "sides MUST set the same value here!");

module_param_named(xeon_b2b_usd_bar2_addr64,
		   xeon_b2b_usd_addr.bar2_addr64, ulदीर्घ, 0644);
MODULE_PARM_DESC(xeon_b2b_usd_bar2_addr64,
		 "XEON B2B USD BAR 2 64-bit address");

module_param_named(xeon_b2b_usd_bar4_addr64,
		   xeon_b2b_usd_addr.bar4_addr64, ulदीर्घ, 0644);
MODULE_PARM_DESC(xeon_b2b_usd_bar4_addr64,
		 "XEON B2B USD BAR 4 64-bit address");

module_param_named(xeon_b2b_usd_bar4_addr32,
		   xeon_b2b_usd_addr.bar4_addr32, ulदीर्घ, 0644);
MODULE_PARM_DESC(xeon_b2b_usd_bar4_addr32,
		 "XEON B2B USD split-BAR 4 32-bit address");

module_param_named(xeon_b2b_usd_bar5_addr32,
		   xeon_b2b_usd_addr.bar5_addr32, ulदीर्घ, 0644);
MODULE_PARM_DESC(xeon_b2b_usd_bar5_addr32,
		 "XEON B2B USD split-BAR 5 32-bit address");

module_param_named(xeon_b2b_dsd_bar2_addr64,
		   xeon_b2b_dsd_addr.bar2_addr64, ulदीर्घ, 0644);
MODULE_PARM_DESC(xeon_b2b_dsd_bar2_addr64,
		 "XEON B2B DSD BAR 2 64-bit address");

module_param_named(xeon_b2b_dsd_bar4_addr64,
		   xeon_b2b_dsd_addr.bar4_addr64, ulदीर्घ, 0644);
MODULE_PARM_DESC(xeon_b2b_dsd_bar4_addr64,
		 "XEON B2B DSD BAR 4 64-bit address");

module_param_named(xeon_b2b_dsd_bar4_addr32,
		   xeon_b2b_dsd_addr.bar4_addr32, ulदीर्घ, 0644);
MODULE_PARM_DESC(xeon_b2b_dsd_bar4_addr32,
		 "XEON B2B DSD split-BAR 4 32-bit address");

module_param_named(xeon_b2b_dsd_bar5_addr32,
		   xeon_b2b_dsd_addr.bar5_addr32, ulदीर्घ, 0644);
MODULE_PARM_DESC(xeon_b2b_dsd_bar5_addr32,
		 "XEON B2B DSD split-BAR 5 32-bit address");


अटल पूर्णांक xeon_init_isr(काष्ठा पूर्णांकel_ntb_dev *ndev);

अटल अंतरभूत व्योम ndev_reset_unsafe_flags(काष्ठा पूर्णांकel_ntb_dev *ndev)
अणु
	ndev->unsafe_flags = 0;
	ndev->unsafe_flags_ignore = 0;

	/* Only B2B has a workaround to aव्योम SDOORBELL */
	अगर (ndev->hwerr_flags & NTB_HWERR_SDOORBELL_LOCKUP)
		अगर (!ntb_topo_is_b2b(ndev->ntb.topo))
			ndev->unsafe_flags |= NTB_UNSAFE_DB;

	/* No low level workaround to aव्योम SB01BASE */
	अगर (ndev->hwerr_flags & NTB_HWERR_SB01BASE_LOCKUP) अणु
		ndev->unsafe_flags |= NTB_UNSAFE_DB;
		ndev->unsafe_flags |= NTB_UNSAFE_SPAD;
	पूर्ण
पूर्ण

अटल अंतरभूत पूर्णांक ndev_is_unsafe(काष्ठा पूर्णांकel_ntb_dev *ndev,
				 अचिन्हित दीर्घ flag)
अणु
	वापस !!(flag & ndev->unsafe_flags & ~ndev->unsafe_flags_ignore);
पूर्ण

अटल अंतरभूत पूर्णांक ndev_ignore_unsafe(काष्ठा पूर्णांकel_ntb_dev *ndev,
				     अचिन्हित दीर्घ flag)
अणु
	flag &= ndev->unsafe_flags;
	ndev->unsafe_flags_ignore |= flag;

	वापस !!flag;
पूर्ण

पूर्णांक ndev_mw_to_bar(काष्ठा पूर्णांकel_ntb_dev *ndev, पूर्णांक idx)
अणु
	अगर (idx < 0 || idx >= ndev->mw_count)
		वापस -EINVAL;
	वापस ndev->reg->mw_bar[idx];
पूर्ण

व्योम ndev_db_addr(काष्ठा पूर्णांकel_ntb_dev *ndev,
			       phys_addr_t *db_addr, resource_माप_प्रकार *db_size,
			       phys_addr_t reg_addr, अचिन्हित दीर्घ reg)
अणु
	अगर (ndev_is_unsafe(ndev, NTB_UNSAFE_DB))
		pr_warn_once("%s: NTB unsafe doorbell access", __func__);

	अगर (db_addr) अणु
		*db_addr = reg_addr + reg;
		dev_dbg(&ndev->ntb.pdev->dev, "Peer db addr %llx\n", *db_addr);
	पूर्ण

	अगर (db_size) अणु
		*db_size = ndev->reg->db_size;
		dev_dbg(&ndev->ntb.pdev->dev, "Peer db size %llx\n", *db_size);
	पूर्ण
पूर्ण

u64 ndev_db_पढ़ो(काष्ठा पूर्णांकel_ntb_dev *ndev,
			       व्योम __iomem *mmio)
अणु
	अगर (ndev_is_unsafe(ndev, NTB_UNSAFE_DB))
		pr_warn_once("%s: NTB unsafe doorbell access", __func__);

	वापस ndev->reg->db_ioपढ़ो(mmio);
पूर्ण

पूर्णांक ndev_db_ग_लिखो(काष्ठा पूर्णांकel_ntb_dev *ndev, u64 db_bits,
				व्योम __iomem *mmio)
अणु
	अगर (ndev_is_unsafe(ndev, NTB_UNSAFE_DB))
		pr_warn_once("%s: NTB unsafe doorbell access", __func__);

	अगर (db_bits & ~ndev->db_valid_mask)
		वापस -EINVAL;

	ndev->reg->db_ioग_लिखो(db_bits, mmio);

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक ndev_db_set_mask(काष्ठा पूर्णांकel_ntb_dev *ndev, u64 db_bits,
				   व्योम __iomem *mmio)
अणु
	अचिन्हित दीर्घ irqflags;

	अगर (ndev_is_unsafe(ndev, NTB_UNSAFE_DB))
		pr_warn_once("%s: NTB unsafe doorbell access", __func__);

	अगर (db_bits & ~ndev->db_valid_mask)
		वापस -EINVAL;

	spin_lock_irqsave(&ndev->db_mask_lock, irqflags);
	अणु
		ndev->db_mask |= db_bits;
		ndev->reg->db_ioग_लिखो(ndev->db_mask, mmio);
	पूर्ण
	spin_unlock_irqrestore(&ndev->db_mask_lock, irqflags);

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक ndev_db_clear_mask(काष्ठा पूर्णांकel_ntb_dev *ndev, u64 db_bits,
				     व्योम __iomem *mmio)
अणु
	अचिन्हित दीर्घ irqflags;

	अगर (ndev_is_unsafe(ndev, NTB_UNSAFE_DB))
		pr_warn_once("%s: NTB unsafe doorbell access", __func__);

	अगर (db_bits & ~ndev->db_valid_mask)
		वापस -EINVAL;

	spin_lock_irqsave(&ndev->db_mask_lock, irqflags);
	अणु
		ndev->db_mask &= ~db_bits;
		ndev->reg->db_ioग_लिखो(ndev->db_mask, mmio);
	पूर्ण
	spin_unlock_irqrestore(&ndev->db_mask_lock, irqflags);

	वापस 0;
पूर्ण

अटल अंतरभूत u64 ndev_vec_mask(काष्ठा पूर्णांकel_ntb_dev *ndev, पूर्णांक db_vector)
अणु
	u64 shअगरt, mask;

	shअगरt = ndev->db_vec_shअगरt;
	mask = BIT_ULL(shअगरt) - 1;

	वापस mask << (shअगरt * db_vector);
पूर्ण

अटल अंतरभूत पूर्णांक ndev_spad_addr(काष्ठा पूर्णांकel_ntb_dev *ndev, पूर्णांक idx,
				 phys_addr_t *spad_addr, phys_addr_t reg_addr,
				 अचिन्हित दीर्घ reg)
अणु
	अगर (ndev_is_unsafe(ndev, NTB_UNSAFE_SPAD))
		pr_warn_once("%s: NTB unsafe scratchpad access", __func__);

	अगर (idx < 0 || idx >= ndev->spad_count)
		वापस -EINVAL;

	अगर (spad_addr) अणु
		*spad_addr = reg_addr + reg + (idx << 2);
		dev_dbg(&ndev->ntb.pdev->dev, "Peer spad addr %llx\n",
			*spad_addr);
	पूर्ण

	वापस 0;
पूर्ण

अटल अंतरभूत u32 ndev_spad_पढ़ो(काष्ठा पूर्णांकel_ntb_dev *ndev, पूर्णांक idx,
				 व्योम __iomem *mmio)
अणु
	अगर (ndev_is_unsafe(ndev, NTB_UNSAFE_SPAD))
		pr_warn_once("%s: NTB unsafe scratchpad access", __func__);

	अगर (idx < 0 || idx >= ndev->spad_count)
		वापस 0;

	वापस ioपढ़ो32(mmio + (idx << 2));
पूर्ण

अटल अंतरभूत पूर्णांक ndev_spad_ग_लिखो(काष्ठा पूर्णांकel_ntb_dev *ndev, पूर्णांक idx, u32 val,
				  व्योम __iomem *mmio)
अणु
	अगर (ndev_is_unsafe(ndev, NTB_UNSAFE_SPAD))
		pr_warn_once("%s: NTB unsafe scratchpad access", __func__);

	अगर (idx < 0 || idx >= ndev->spad_count)
		वापस -EINVAL;

	ioग_लिखो32(val, mmio + (idx << 2));

	वापस 0;
पूर्ण

अटल irqवापस_t ndev_पूर्णांकerrupt(काष्ठा पूर्णांकel_ntb_dev *ndev, पूर्णांक vec)
अणु
	u64 vec_mask;

	vec_mask = ndev_vec_mask(ndev, vec);

	अगर ((ndev->hwerr_flags & NTB_HWERR_MSIX_VECTOR32_BAD) && (vec == 31))
		vec_mask |= ndev->db_link_mask;

	dev_dbg(&ndev->ntb.pdev->dev, "vec %d vec_mask %llx\n", vec, vec_mask);

	ndev->last_ts = jअगरfies;

	अगर (vec_mask & ndev->db_link_mask) अणु
		अगर (ndev->reg->poll_link(ndev))
			ntb_link_event(&ndev->ntb);
	पूर्ण

	अगर (vec_mask & ndev->db_valid_mask)
		ntb_db_event(&ndev->ntb, vec);

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t ndev_vec_isr(पूर्णांक irq, व्योम *dev)
अणु
	काष्ठा पूर्णांकel_ntb_vec *nvec = dev;

	dev_dbg(&nvec->ndev->ntb.pdev->dev, "irq: %d  nvec->num: %d\n",
		irq, nvec->num);

	वापस ndev_पूर्णांकerrupt(nvec->ndev, nvec->num);
पूर्ण

अटल irqवापस_t ndev_irq_isr(पूर्णांक irq, व्योम *dev)
अणु
	काष्ठा पूर्णांकel_ntb_dev *ndev = dev;

	वापस ndev_पूर्णांकerrupt(ndev, irq - ndev->ntb.pdev->irq);
पूर्ण

पूर्णांक ndev_init_isr(काष्ठा पूर्णांकel_ntb_dev *ndev,
			 पूर्णांक msix_min, पूर्णांक msix_max,
			 पूर्णांक msix_shअगरt, पूर्णांक total_shअगरt)
अणु
	काष्ठा pci_dev *pdev;
	पूर्णांक rc, i, msix_count, node;

	pdev = ndev->ntb.pdev;

	node = dev_to_node(&pdev->dev);

	/* Mask all करोorbell पूर्णांकerrupts */
	ndev->db_mask = ndev->db_valid_mask;
	ndev->reg->db_ioग_लिखो(ndev->db_mask,
			      ndev->self_mmio +
			      ndev->self_reg->db_mask);

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

	क्रम (i = 0; i < msix_count; ++i) अणु
		ndev->vec[i].ndev = ndev;
		ndev->vec[i].num = i;
		rc = request_irq(ndev->msix[i].vector, ndev_vec_isr, 0,
				 "ndev_vec_isr", &ndev->vec[i]);
		अगर (rc)
			जाओ err_msix_request;
	पूर्ण

	dev_dbg(&pdev->dev, "Using %d msix interrupts\n", msix_count);
	ndev->db_vec_count = msix_count;
	ndev->db_vec_shअगरt = msix_shअगरt;
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
	ndev->db_vec_count = 1;
	ndev->db_vec_shअगरt = total_shअगरt;
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
	ndev->db_vec_count = 1;
	ndev->db_vec_shअगरt = total_shअगरt;
	वापस 0;

err_पूर्णांकx_request:
	वापस rc;
पूर्ण

अटल व्योम ndev_deinit_isr(काष्ठा पूर्णांकel_ntb_dev *ndev)
अणु
	काष्ठा pci_dev *pdev;
	पूर्णांक i;

	pdev = ndev->ntb.pdev;

	/* Mask all करोorbell पूर्णांकerrupts */
	ndev->db_mask = ndev->db_valid_mask;
	ndev->reg->db_ioग_लिखो(ndev->db_mask,
			      ndev->self_mmio +
			      ndev->self_reg->db_mask);

	अगर (ndev->msix) अणु
		i = ndev->db_vec_count;
		जबतक (i--)
			मुक्त_irq(ndev->msix[i].vector, &ndev->vec[i]);
		pci_disable_msix(pdev);
		kमुक्त(ndev->msix);
		kमुक्त(ndev->vec);
	पूर्ण अन्यथा अणु
		मुक्त_irq(pdev->irq, ndev);
		अगर (pci_dev_msi_enabled(pdev))
			pci_disable_msi(pdev);
	पूर्ण
पूर्ण

अटल sमाप_प्रकार ndev_ntb_debugfs_पढ़ो(काष्ठा file *filp, अक्षर __user *ubuf,
				     माप_प्रकार count, loff_t *offp)
अणु
	काष्ठा पूर्णांकel_ntb_dev *ndev;
	काष्ठा pci_dev *pdev;
	व्योम __iomem *mmio;
	अक्षर *buf;
	माप_प्रकार buf_size;
	sमाप_प्रकार ret, off;
	जोड़ अणु u64 v64; u32 v32; u16 v16; u8 v8; पूर्ण u;

	ndev = filp->निजी_data;
	pdev = ndev->ntb.pdev;
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

	अगर (ndev->b2b_idx != अच_पूर्णांक_उच्च) अणु
		off += scnम_लिखो(buf + off, buf_size - off,
				 "B2B MW Idx -\t\t%u\n", ndev->b2b_idx);
		off += scnम_लिखो(buf + off, buf_size - off,
				 "B2B Offset -\t\t%#lx\n", ndev->b2b_off);
	पूर्ण

	off += scnम_लिखो(buf + off, buf_size - off,
			 "BAR4 Split -\t\t%s\n",
			 ndev->bar4_split ? "yes" : "no");

	off += scnम_लिखो(buf + off, buf_size - off,
			 "NTB CTL -\t\t%#06x\n", ndev->ntb_ctl);
	off += scnम_लिखो(buf + off, buf_size - off,
			 "LNK STA -\t\t%#06x\n", ndev->lnk_sta);

	अगर (!ndev->reg->link_is_up(ndev)) अणु
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
			 "Doorbell Vector Count -\t%u\n", ndev->db_vec_count);
	off += scnम_लिखो(buf + off, buf_size - off,
			 "Doorbell Vector Shift -\t%u\n", ndev->db_vec_shअगरt);

	off += scnम_लिखो(buf + off, buf_size - off,
			 "Doorbell Valid Mask -\t%#llx\n", ndev->db_valid_mask);
	off += scnम_लिखो(buf + off, buf_size - off,
			 "Doorbell Link Mask -\t%#llx\n", ndev->db_link_mask);
	off += scnम_लिखो(buf + off, buf_size - off,
			 "Doorbell Mask Cached -\t%#llx\n", ndev->db_mask);

	u.v64 = ndev_db_पढ़ो(ndev, mmio + ndev->self_reg->db_mask);
	off += scnम_लिखो(buf + off, buf_size - off,
			 "Doorbell Mask -\t\t%#llx\n", u.v64);

	u.v64 = ndev_db_पढ़ो(ndev, mmio + ndev->self_reg->db_bell);
	off += scnम_लिखो(buf + off, buf_size - off,
			 "Doorbell Bell -\t\t%#llx\n", u.v64);

	off += scnम_लिखो(buf + off, buf_size - off,
			 "\nNTB Window Size:\n");

	pci_पढ़ो_config_byte(pdev, XEON_PBAR23SZ_OFFSET, &u.v8);
	off += scnम_लिखो(buf + off, buf_size - off,
			 "PBAR23SZ %hhu\n", u.v8);
	अगर (!ndev->bar4_split) अणु
		pci_पढ़ो_config_byte(pdev, XEON_PBAR45SZ_OFFSET, &u.v8);
		off += scnम_लिखो(buf + off, buf_size - off,
				 "PBAR45SZ %hhu\n", u.v8);
	पूर्ण अन्यथा अणु
		pci_पढ़ो_config_byte(pdev, XEON_PBAR4SZ_OFFSET, &u.v8);
		off += scnम_लिखो(buf + off, buf_size - off,
				 "PBAR4SZ %hhu\n", u.v8);
		pci_पढ़ो_config_byte(pdev, XEON_PBAR5SZ_OFFSET, &u.v8);
		off += scnम_लिखो(buf + off, buf_size - off,
				 "PBAR5SZ %hhu\n", u.v8);
	पूर्ण

	pci_पढ़ो_config_byte(pdev, XEON_SBAR23SZ_OFFSET, &u.v8);
	off += scnम_लिखो(buf + off, buf_size - off,
			 "SBAR23SZ %hhu\n", u.v8);
	अगर (!ndev->bar4_split) अणु
		pci_पढ़ो_config_byte(pdev, XEON_SBAR45SZ_OFFSET, &u.v8);
		off += scnम_लिखो(buf + off, buf_size - off,
				 "SBAR45SZ %hhu\n", u.v8);
	पूर्ण अन्यथा अणु
		pci_पढ़ो_config_byte(pdev, XEON_SBAR4SZ_OFFSET, &u.v8);
		off += scnम_लिखो(buf + off, buf_size - off,
				 "SBAR4SZ %hhu\n", u.v8);
		pci_पढ़ो_config_byte(pdev, XEON_SBAR5SZ_OFFSET, &u.v8);
		off += scnम_लिखो(buf + off, buf_size - off,
				 "SBAR5SZ %hhu\n", u.v8);
	पूर्ण

	off += scnम_लिखो(buf + off, buf_size - off,
			 "\nNTB Incoming XLAT:\n");

	u.v64 = ioपढ़ो64(mmio + bar2_off(ndev->xlat_reg->bar2_xlat, 2));
	off += scnम_लिखो(buf + off, buf_size - off,
			 "XLAT23 -\t\t%#018llx\n", u.v64);

	अगर (ndev->bar4_split) अणु
		u.v32 = ioपढ़ो32(mmio + bar2_off(ndev->xlat_reg->bar2_xlat, 4));
		off += scnम_लिखो(buf + off, buf_size - off,
				 "XLAT4 -\t\t\t%#06x\n", u.v32);

		u.v32 = ioपढ़ो32(mmio + bar2_off(ndev->xlat_reg->bar2_xlat, 5));
		off += scnम_लिखो(buf + off, buf_size - off,
				 "XLAT5 -\t\t\t%#06x\n", u.v32);
	पूर्ण अन्यथा अणु
		u.v64 = ioपढ़ो64(mmio + bar2_off(ndev->xlat_reg->bar2_xlat, 4));
		off += scnम_लिखो(buf + off, buf_size - off,
				 "XLAT45 -\t\t%#018llx\n", u.v64);
	पूर्ण

	u.v64 = ioपढ़ो64(mmio + bar2_off(ndev->xlat_reg->bar2_limit, 2));
	off += scnम_लिखो(buf + off, buf_size - off,
			 "LMT23 -\t\t\t%#018llx\n", u.v64);

	अगर (ndev->bar4_split) अणु
		u.v32 = ioपढ़ो32(mmio + bar2_off(ndev->xlat_reg->bar2_limit, 4));
		off += scnम_लिखो(buf + off, buf_size - off,
				 "LMT4 -\t\t\t%#06x\n", u.v32);
		u.v32 = ioपढ़ो32(mmio + bar2_off(ndev->xlat_reg->bar2_limit, 5));
		off += scnम_लिखो(buf + off, buf_size - off,
				 "LMT5 -\t\t\t%#06x\n", u.v32);
	पूर्ण अन्यथा अणु
		u.v64 = ioपढ़ो64(mmio + bar2_off(ndev->xlat_reg->bar2_limit, 4));
		off += scnम_लिखो(buf + off, buf_size - off,
				 "LMT45 -\t\t\t%#018llx\n", u.v64);
	पूर्ण

	अगर (pdev_is_gen1(pdev)) अणु
		अगर (ntb_topo_is_b2b(ndev->ntb.topo)) अणु
			off += scnम_लिखो(buf + off, buf_size - off,
					 "\nNTB Outgoing B2B XLAT:\n");

			u.v64 = ioपढ़ो64(mmio + XEON_PBAR23XLAT_OFFSET);
			off += scnम_लिखो(buf + off, buf_size - off,
					 "B2B XLAT23 -\t\t%#018llx\n", u.v64);

			अगर (ndev->bar4_split) अणु
				u.v32 = ioपढ़ो32(mmio + XEON_PBAR4XLAT_OFFSET);
				off += scnम_लिखो(buf + off, buf_size - off,
						 "B2B XLAT4 -\t\t%#06x\n",
						 u.v32);
				u.v32 = ioपढ़ो32(mmio + XEON_PBAR5XLAT_OFFSET);
				off += scnम_लिखो(buf + off, buf_size - off,
						 "B2B XLAT5 -\t\t%#06x\n",
						 u.v32);
			पूर्ण अन्यथा अणु
				u.v64 = ioपढ़ो64(mmio + XEON_PBAR45XLAT_OFFSET);
				off += scnम_लिखो(buf + off, buf_size - off,
						 "B2B XLAT45 -\t\t%#018llx\n",
						 u.v64);
			पूर्ण

			u.v64 = ioपढ़ो64(mmio + XEON_PBAR23LMT_OFFSET);
			off += scnम_लिखो(buf + off, buf_size - off,
					 "B2B LMT23 -\t\t%#018llx\n", u.v64);

			अगर (ndev->bar4_split) अणु
				u.v32 = ioपढ़ो32(mmio + XEON_PBAR4LMT_OFFSET);
				off += scnम_लिखो(buf + off, buf_size - off,
						 "B2B LMT4 -\t\t%#06x\n",
						 u.v32);
				u.v32 = ioपढ़ो32(mmio + XEON_PBAR5LMT_OFFSET);
				off += scnम_लिखो(buf + off, buf_size - off,
						 "B2B LMT5 -\t\t%#06x\n",
						 u.v32);
			पूर्ण अन्यथा अणु
				u.v64 = ioपढ़ो64(mmio + XEON_PBAR45LMT_OFFSET);
				off += scnम_लिखो(buf + off, buf_size - off,
						 "B2B LMT45 -\t\t%#018llx\n",
						 u.v64);
			पूर्ण

			off += scnम_लिखो(buf + off, buf_size - off,
					 "\nNTB Secondary BAR:\n");

			u.v64 = ioपढ़ो64(mmio + XEON_SBAR0BASE_OFFSET);
			off += scnम_लिखो(buf + off, buf_size - off,
					 "SBAR01 -\t\t%#018llx\n", u.v64);

			u.v64 = ioपढ़ो64(mmio + XEON_SBAR23BASE_OFFSET);
			off += scnम_लिखो(buf + off, buf_size - off,
					 "SBAR23 -\t\t%#018llx\n", u.v64);

			अगर (ndev->bar4_split) अणु
				u.v32 = ioपढ़ो32(mmio + XEON_SBAR4BASE_OFFSET);
				off += scnम_लिखो(buf + off, buf_size - off,
						 "SBAR4 -\t\t\t%#06x\n", u.v32);
				u.v32 = ioपढ़ो32(mmio + XEON_SBAR5BASE_OFFSET);
				off += scnम_लिखो(buf + off, buf_size - off,
						 "SBAR5 -\t\t\t%#06x\n", u.v32);
			पूर्ण अन्यथा अणु
				u.v64 = ioपढ़ो64(mmio + XEON_SBAR45BASE_OFFSET);
				off += scnम_लिखो(buf + off, buf_size - off,
						 "SBAR45 -\t\t%#018llx\n",
						 u.v64);
			पूर्ण
		पूर्ण

		off += scnम_लिखो(buf + off, buf_size - off,
				 "\nXEON NTB Statistics:\n");

		u.v16 = ioपढ़ो16(mmio + XEON_USMEMMISS_OFFSET);
		off += scnम_लिखो(buf + off, buf_size - off,
				 "Upstream Memory Miss -\t%u\n", u.v16);

		off += scnम_लिखो(buf + off, buf_size - off,
				 "\nXEON NTB Hardware Errors:\n");

		अगर (!pci_पढ़ो_config_word(pdev,
					  XEON_DEVSTS_OFFSET, &u.v16))
			off += scnम_लिखो(buf + off, buf_size - off,
					 "DEVSTS -\t\t%#06x\n", u.v16);

		अगर (!pci_पढ़ो_config_word(pdev,
					  XEON_LINK_STATUS_OFFSET, &u.v16))
			off += scnम_लिखो(buf + off, buf_size - off,
					 "LNKSTS -\t\t%#06x\n", u.v16);

		अगर (!pci_पढ़ो_config_dword(pdev,
					   XEON_UNCERRSTS_OFFSET, &u.v32))
			off += scnम_लिखो(buf + off, buf_size - off,
					 "UNCERRSTS -\t\t%#06x\n", u.v32);

		अगर (!pci_पढ़ो_config_dword(pdev,
					   XEON_CORERRSTS_OFFSET, &u.v32))
			off += scnम_लिखो(buf + off, buf_size - off,
					 "CORERRSTS -\t\t%#06x\n", u.v32);
	पूर्ण

	ret = simple_पढ़ो_from_buffer(ubuf, count, offp, buf, off);
	kमुक्त(buf);
	वापस ret;
पूर्ण

अटल sमाप_प्रकार ndev_debugfs_पढ़ो(काष्ठा file *filp, अक्षर __user *ubuf,
				 माप_प्रकार count, loff_t *offp)
अणु
	काष्ठा पूर्णांकel_ntb_dev *ndev = filp->निजी_data;

	अगर (pdev_is_gen1(ndev->ntb.pdev))
		वापस ndev_ntb_debugfs_पढ़ो(filp, ubuf, count, offp);
	अन्यथा अगर (pdev_is_gen3(ndev->ntb.pdev))
		वापस ndev_ntb3_debugfs_पढ़ो(filp, ubuf, count, offp);
	अन्यथा अगर (pdev_is_gen4(ndev->ntb.pdev))
		वापस ndev_ntb4_debugfs_पढ़ो(filp, ubuf, count, offp);

	वापस -ENXIO;
पूर्ण

अटल व्योम ndev_init_debugfs(काष्ठा पूर्णांकel_ntb_dev *ndev)
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
						    &पूर्णांकel_ntb_debugfs_info);
	पूर्ण
पूर्ण

अटल व्योम ndev_deinit_debugfs(काष्ठा पूर्णांकel_ntb_dev *ndev)
अणु
	debugfs_हटाओ_recursive(ndev->debugfs_dir);
पूर्ण

पूर्णांक पूर्णांकel_ntb_mw_count(काष्ठा ntb_dev *ntb, पूर्णांक pidx)
अणु
	अगर (pidx != NTB_DEF_PEER_IDX)
		वापस -EINVAL;

	वापस ntb_ndev(ntb)->mw_count;
पूर्ण

पूर्णांक पूर्णांकel_ntb_mw_get_align(काष्ठा ntb_dev *ntb, पूर्णांक pidx, पूर्णांक idx,
			   resource_माप_प्रकार *addr_align,
			   resource_माप_प्रकार *size_align,
			   resource_माप_प्रकार *size_max)
अणु
	काष्ठा पूर्णांकel_ntb_dev *ndev = ntb_ndev(ntb);
	resource_माप_प्रकार bar_size, mw_size;
	पूर्णांक bar;

	अगर (pidx != NTB_DEF_PEER_IDX)
		वापस -EINVAL;

	अगर (idx >= ndev->b2b_idx && !ndev->b2b_off)
		idx += 1;

	bar = ndev_mw_to_bar(ndev, idx);
	अगर (bar < 0)
		वापस bar;

	bar_size = pci_resource_len(ndev->ntb.pdev, bar);

	अगर (idx == ndev->b2b_idx)
		mw_size = bar_size - ndev->b2b_off;
	अन्यथा
		mw_size = bar_size;

	अगर (addr_align)
		*addr_align = pci_resource_len(ndev->ntb.pdev, bar);

	अगर (size_align)
		*size_align = 1;

	अगर (size_max)
		*size_max = mw_size;

	वापस 0;
पूर्ण

अटल पूर्णांक पूर्णांकel_ntb_mw_set_trans(काष्ठा ntb_dev *ntb, पूर्णांक pidx, पूर्णांक idx,
				  dma_addr_t addr, resource_माप_प्रकार size)
अणु
	काष्ठा पूर्णांकel_ntb_dev *ndev = ntb_ndev(ntb);
	अचिन्हित दीर्घ base_reg, xlat_reg, limit_reg;
	resource_माप_प्रकार bar_size, mw_size;
	व्योम __iomem *mmio;
	u64 base, limit, reg_val;
	पूर्णांक bar;

	अगर (pidx != NTB_DEF_PEER_IDX)
		वापस -EINVAL;

	अगर (idx >= ndev->b2b_idx && !ndev->b2b_off)
		idx += 1;

	bar = ndev_mw_to_bar(ndev, idx);
	अगर (bar < 0)
		वापस bar;

	bar_size = pci_resource_len(ndev->ntb.pdev, bar);

	अगर (idx == ndev->b2b_idx)
		mw_size = bar_size - ndev->b2b_off;
	अन्यथा
		mw_size = bar_size;

	/* hardware requires that addr is aligned to bar size */
	अगर (addr & (bar_size - 1))
		वापस -EINVAL;

	/* make sure the range fits in the usable mw size */
	अगर (size > mw_size)
		वापस -EINVAL;

	mmio = ndev->self_mmio;
	base_reg = bar0_off(ndev->xlat_reg->bar0_base, bar);
	xlat_reg = bar2_off(ndev->xlat_reg->bar2_xlat, bar);
	limit_reg = bar2_off(ndev->xlat_reg->bar2_limit, bar);

	अगर (bar < 4 || !ndev->bar4_split) अणु
		base = ioपढ़ो64(mmio + base_reg) & NTB_BAR_MASK_64;

		/* Set the limit अगर supported, अगर size is not mw_size */
		अगर (limit_reg && size != mw_size)
			limit = base + size;
		अन्यथा
			limit = 0;

		/* set and verअगरy setting the translation address */
		ioग_लिखो64(addr, mmio + xlat_reg);
		reg_val = ioपढ़ो64(mmio + xlat_reg);
		अगर (reg_val != addr) अणु
			ioग_लिखो64(0, mmio + xlat_reg);
			वापस -EIO;
		पूर्ण

		/* set and verअगरy setting the limit */
		ioग_लिखो64(limit, mmio + limit_reg);
		reg_val = ioपढ़ो64(mmio + limit_reg);
		अगर (reg_val != limit) अणु
			ioग_लिखो64(base, mmio + limit_reg);
			ioग_लिखो64(0, mmio + xlat_reg);
			वापस -EIO;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* split bar addr range must all be 32 bit */
		अगर (addr & (~0ull << 32))
			वापस -EINVAL;
		अगर ((addr + size) & (~0ull << 32))
			वापस -EINVAL;

		base = ioपढ़ो32(mmio + base_reg) & NTB_BAR_MASK_32;

		/* Set the limit अगर supported, अगर size is not mw_size */
		अगर (limit_reg && size != mw_size)
			limit = base + size;
		अन्यथा
			limit = 0;

		/* set and verअगरy setting the translation address */
		ioग_लिखो32(addr, mmio + xlat_reg);
		reg_val = ioपढ़ो32(mmio + xlat_reg);
		अगर (reg_val != addr) अणु
			ioग_लिखो32(0, mmio + xlat_reg);
			वापस -EIO;
		पूर्ण

		/* set and verअगरy setting the limit */
		ioग_लिखो32(limit, mmio + limit_reg);
		reg_val = ioपढ़ो32(mmio + limit_reg);
		अगर (reg_val != limit) अणु
			ioग_लिखो32(base, mmio + limit_reg);
			ioग_लिखो32(0, mmio + xlat_reg);
			वापस -EIO;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

u64 पूर्णांकel_ntb_link_is_up(काष्ठा ntb_dev *ntb, क्रमागत ntb_speed *speed,
			 क्रमागत ntb_width *width)
अणु
	काष्ठा पूर्णांकel_ntb_dev *ndev = ntb_ndev(ntb);

	अगर (ndev->reg->link_is_up(ndev)) अणु
		अगर (speed)
			*speed = NTB_LNK_STA_SPEED(ndev->lnk_sta);
		अगर (width)
			*width = NTB_LNK_STA_WIDTH(ndev->lnk_sta);
		वापस 1;
	पूर्ण अन्यथा अणु
		/* TODO MAYBE: is it possible to observe the link speed and
		 * width जबतक link is training? */
		अगर (speed)
			*speed = NTB_SPEED_NONE;
		अगर (width)
			*width = NTB_WIDTH_NONE;
		वापस 0;
	पूर्ण
पूर्ण

अटल पूर्णांक पूर्णांकel_ntb_link_enable(काष्ठा ntb_dev *ntb,
				 क्रमागत ntb_speed max_speed,
				 क्रमागत ntb_width max_width)
अणु
	काष्ठा पूर्णांकel_ntb_dev *ndev;
	u32 ntb_ctl;

	ndev = container_of(ntb, काष्ठा पूर्णांकel_ntb_dev, ntb);

	अगर (ndev->ntb.topo == NTB_TOPO_SEC)
		वापस -EINVAL;

	dev_dbg(&ntb->pdev->dev,
		"Enabling link with max_speed %d max_width %d\n",
		max_speed, max_width);
	अगर (max_speed != NTB_SPEED_AUTO)
		dev_dbg(&ntb->pdev->dev, "ignoring max_speed %d\n", max_speed);
	अगर (max_width != NTB_WIDTH_AUTO)
		dev_dbg(&ntb->pdev->dev, "ignoring max_width %d\n", max_width);

	ntb_ctl = ioपढ़ो32(ndev->self_mmio + ndev->reg->ntb_ctl);
	ntb_ctl &= ~(NTB_CTL_DISABLE | NTB_CTL_CFG_LOCK);
	ntb_ctl |= NTB_CTL_P2S_BAR2_SNOOP | NTB_CTL_S2P_BAR2_SNOOP;
	ntb_ctl |= NTB_CTL_P2S_BAR4_SNOOP | NTB_CTL_S2P_BAR4_SNOOP;
	अगर (ndev->bar4_split)
		ntb_ctl |= NTB_CTL_P2S_BAR5_SNOOP | NTB_CTL_S2P_BAR5_SNOOP;
	ioग_लिखो32(ntb_ctl, ndev->self_mmio + ndev->reg->ntb_ctl);

	वापस 0;
पूर्ण

पूर्णांक पूर्णांकel_ntb_link_disable(काष्ठा ntb_dev *ntb)
अणु
	काष्ठा पूर्णांकel_ntb_dev *ndev;
	u32 ntb_cntl;

	ndev = container_of(ntb, काष्ठा पूर्णांकel_ntb_dev, ntb);

	अगर (ndev->ntb.topo == NTB_TOPO_SEC)
		वापस -EINVAL;

	dev_dbg(&ntb->pdev->dev, "Disabling link\n");

	/* Bring NTB link करोwn */
	ntb_cntl = ioपढ़ो32(ndev->self_mmio + ndev->reg->ntb_ctl);
	ntb_cntl &= ~(NTB_CTL_P2S_BAR2_SNOOP | NTB_CTL_S2P_BAR2_SNOOP);
	ntb_cntl &= ~(NTB_CTL_P2S_BAR4_SNOOP | NTB_CTL_S2P_BAR4_SNOOP);
	अगर (ndev->bar4_split)
		ntb_cntl &= ~(NTB_CTL_P2S_BAR5_SNOOP | NTB_CTL_S2P_BAR5_SNOOP);
	ntb_cntl |= NTB_CTL_DISABLE | NTB_CTL_CFG_LOCK;
	ioग_लिखो32(ntb_cntl, ndev->self_mmio + ndev->reg->ntb_ctl);

	वापस 0;
पूर्ण

पूर्णांक पूर्णांकel_ntb_peer_mw_count(काष्ठा ntb_dev *ntb)
अणु
	/* Numbers of inbound and outbound memory winकरोws match */
	वापस ntb_ndev(ntb)->mw_count;
पूर्ण

पूर्णांक पूर्णांकel_ntb_peer_mw_get_addr(काष्ठा ntb_dev *ntb, पूर्णांक idx,
			       phys_addr_t *base, resource_माप_प्रकार *size)
अणु
	काष्ठा पूर्णांकel_ntb_dev *ndev = ntb_ndev(ntb);
	पूर्णांक bar;

	अगर (idx >= ndev->b2b_idx && !ndev->b2b_off)
		idx += 1;

	bar = ndev_mw_to_bar(ndev, idx);
	अगर (bar < 0)
		वापस bar;

	अगर (base)
		*base = pci_resource_start(ndev->ntb.pdev, bar) +
			(idx == ndev->b2b_idx ? ndev->b2b_off : 0);

	अगर (size)
		*size = pci_resource_len(ndev->ntb.pdev, bar) -
			(idx == ndev->b2b_idx ? ndev->b2b_off : 0);

	वापस 0;
पूर्ण

अटल पूर्णांक पूर्णांकel_ntb_db_is_unsafe(काष्ठा ntb_dev *ntb)
अणु
	वापस ndev_ignore_unsafe(ntb_ndev(ntb), NTB_UNSAFE_DB);
पूर्ण

u64 पूर्णांकel_ntb_db_valid_mask(काष्ठा ntb_dev *ntb)
अणु
	वापस ntb_ndev(ntb)->db_valid_mask;
पूर्ण

पूर्णांक पूर्णांकel_ntb_db_vector_count(काष्ठा ntb_dev *ntb)
अणु
	काष्ठा पूर्णांकel_ntb_dev *ndev;

	ndev = container_of(ntb, काष्ठा पूर्णांकel_ntb_dev, ntb);

	वापस ndev->db_vec_count;
पूर्ण

u64 पूर्णांकel_ntb_db_vector_mask(काष्ठा ntb_dev *ntb, पूर्णांक db_vector)
अणु
	काष्ठा पूर्णांकel_ntb_dev *ndev = ntb_ndev(ntb);

	अगर (db_vector < 0 || db_vector > ndev->db_vec_count)
		वापस 0;

	वापस ndev->db_valid_mask & ndev_vec_mask(ndev, db_vector);
पूर्ण

अटल u64 पूर्णांकel_ntb_db_पढ़ो(काष्ठा ntb_dev *ntb)
अणु
	काष्ठा पूर्णांकel_ntb_dev *ndev = ntb_ndev(ntb);

	वापस ndev_db_पढ़ो(ndev,
			    ndev->self_mmio +
			    ndev->self_reg->db_bell);
पूर्ण

अटल पूर्णांक पूर्णांकel_ntb_db_clear(काष्ठा ntb_dev *ntb, u64 db_bits)
अणु
	काष्ठा पूर्णांकel_ntb_dev *ndev = ntb_ndev(ntb);

	वापस ndev_db_ग_लिखो(ndev, db_bits,
			     ndev->self_mmio +
			     ndev->self_reg->db_bell);
पूर्ण

पूर्णांक पूर्णांकel_ntb_db_set_mask(काष्ठा ntb_dev *ntb, u64 db_bits)
अणु
	काष्ठा पूर्णांकel_ntb_dev *ndev = ntb_ndev(ntb);

	वापस ndev_db_set_mask(ndev, db_bits,
				ndev->self_mmio +
				ndev->self_reg->db_mask);
पूर्ण

पूर्णांक पूर्णांकel_ntb_db_clear_mask(काष्ठा ntb_dev *ntb, u64 db_bits)
अणु
	काष्ठा पूर्णांकel_ntb_dev *ndev = ntb_ndev(ntb);

	वापस ndev_db_clear_mask(ndev, db_bits,
				  ndev->self_mmio +
				  ndev->self_reg->db_mask);
पूर्ण

अटल पूर्णांक पूर्णांकel_ntb_peer_db_addr(काष्ठा ntb_dev *ntb, phys_addr_t *db_addr,
			   resource_माप_प्रकार *db_size, u64 *db_data, पूर्णांक db_bit)
अणु
	u64 db_bits;
	काष्ठा पूर्णांकel_ntb_dev *ndev = ntb_ndev(ntb);

	अगर (unlikely(db_bit >= BITS_PER_LONG_LONG))
		वापस -EINVAL;

	db_bits = BIT_ULL(db_bit);

	अगर (unlikely(db_bits & ~ntb_ndev(ntb)->db_valid_mask))
		वापस -EINVAL;

	ndev_db_addr(ndev, db_addr, db_size, ndev->peer_addr,
			    ndev->peer_reg->db_bell);

	अगर (db_data)
		*db_data = db_bits;


	वापस 0;
पूर्ण

अटल पूर्णांक पूर्णांकel_ntb_peer_db_set(काष्ठा ntb_dev *ntb, u64 db_bits)
अणु
	काष्ठा पूर्णांकel_ntb_dev *ndev = ntb_ndev(ntb);

	वापस ndev_db_ग_लिखो(ndev, db_bits,
			     ndev->peer_mmio +
			     ndev->peer_reg->db_bell);
पूर्ण

पूर्णांक पूर्णांकel_ntb_spad_is_unsafe(काष्ठा ntb_dev *ntb)
अणु
	वापस ndev_ignore_unsafe(ntb_ndev(ntb), NTB_UNSAFE_SPAD);
पूर्ण

पूर्णांक पूर्णांकel_ntb_spad_count(काष्ठा ntb_dev *ntb)
अणु
	काष्ठा पूर्णांकel_ntb_dev *ndev;

	ndev = container_of(ntb, काष्ठा पूर्णांकel_ntb_dev, ntb);

	वापस ndev->spad_count;
पूर्ण

u32 पूर्णांकel_ntb_spad_पढ़ो(काष्ठा ntb_dev *ntb, पूर्णांक idx)
अणु
	काष्ठा पूर्णांकel_ntb_dev *ndev = ntb_ndev(ntb);

	वापस ndev_spad_पढ़ो(ndev, idx,
			      ndev->self_mmio +
			      ndev->self_reg->spad);
पूर्ण

पूर्णांक पूर्णांकel_ntb_spad_ग_लिखो(काष्ठा ntb_dev *ntb, पूर्णांक idx, u32 val)
अणु
	काष्ठा पूर्णांकel_ntb_dev *ndev = ntb_ndev(ntb);

	वापस ndev_spad_ग_लिखो(ndev, idx, val,
			       ndev->self_mmio +
			       ndev->self_reg->spad);
पूर्ण

पूर्णांक पूर्णांकel_ntb_peer_spad_addr(काष्ठा ntb_dev *ntb, पूर्णांक pidx, पूर्णांक sidx,
			     phys_addr_t *spad_addr)
अणु
	काष्ठा पूर्णांकel_ntb_dev *ndev = ntb_ndev(ntb);

	वापस ndev_spad_addr(ndev, sidx, spad_addr, ndev->peer_addr,
			      ndev->peer_reg->spad);
पूर्ण

u32 पूर्णांकel_ntb_peer_spad_पढ़ो(काष्ठा ntb_dev *ntb, पूर्णांक pidx, पूर्णांक sidx)
अणु
	काष्ठा पूर्णांकel_ntb_dev *ndev = ntb_ndev(ntb);

	वापस ndev_spad_पढ़ो(ndev, sidx,
			      ndev->peer_mmio +
			      ndev->peer_reg->spad);
पूर्ण

पूर्णांक पूर्णांकel_ntb_peer_spad_ग_लिखो(काष्ठा ntb_dev *ntb, पूर्णांक pidx, पूर्णांक sidx,
			      u32 val)
अणु
	काष्ठा पूर्णांकel_ntb_dev *ndev = ntb_ndev(ntb);

	वापस ndev_spad_ग_लिखो(ndev, sidx, val,
			       ndev->peer_mmio +
			       ndev->peer_reg->spad);
पूर्ण

अटल u64 xeon_db_ioपढ़ो(स्थिर व्योम __iomem *mmio)
अणु
	वापस (u64)ioपढ़ो16(mmio);
पूर्ण

अटल व्योम xeon_db_ioग_लिखो(u64 bits, व्योम __iomem *mmio)
अणु
	ioग_लिखो16((u16)bits, mmio);
पूर्ण

अटल पूर्णांक xeon_poll_link(काष्ठा पूर्णांकel_ntb_dev *ndev)
अणु
	u16 reg_val;
	पूर्णांक rc;

	ndev->reg->db_ioग_लिखो(ndev->db_link_mask,
			      ndev->self_mmio +
			      ndev->self_reg->db_bell);

	rc = pci_पढ़ो_config_word(ndev->ntb.pdev,
				  XEON_LINK_STATUS_OFFSET, &reg_val);
	अगर (rc)
		वापस 0;

	अगर (reg_val == ndev->lnk_sta)
		वापस 0;

	ndev->lnk_sta = reg_val;

	वापस 1;
पूर्ण

पूर्णांक xeon_link_is_up(काष्ठा पूर्णांकel_ntb_dev *ndev)
अणु
	अगर (ndev->ntb.topo == NTB_TOPO_SEC)
		वापस 1;

	वापस NTB_LNK_STA_ACTIVE(ndev->lnk_sta);
पूर्ण

क्रमागत ntb_topo xeon_ppd_topo(काष्ठा पूर्णांकel_ntb_dev *ndev, u8 ppd)
अणु
	चयन (ppd & XEON_PPD_TOPO_MASK) अणु
	हाल XEON_PPD_TOPO_B2B_USD:
		वापस NTB_TOPO_B2B_USD;

	हाल XEON_PPD_TOPO_B2B_DSD:
		वापस NTB_TOPO_B2B_DSD;

	हाल XEON_PPD_TOPO_PRI_USD:
	हाल XEON_PPD_TOPO_PRI_DSD: /* accept bogus PRI_DSD */
		वापस NTB_TOPO_PRI;

	हाल XEON_PPD_TOPO_SEC_USD:
	हाल XEON_PPD_TOPO_SEC_DSD: /* accept bogus SEC_DSD */
		वापस NTB_TOPO_SEC;
	पूर्ण

	वापस NTB_TOPO_NONE;
पूर्ण

अटल अंतरभूत पूर्णांक xeon_ppd_bar4_split(काष्ठा पूर्णांकel_ntb_dev *ndev, u8 ppd)
अणु
	अगर (ppd & XEON_PPD_SPLIT_BAR_MASK) अणु
		dev_dbg(&ndev->ntb.pdev->dev, "PPD %d split bar\n", ppd);
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक xeon_init_isr(काष्ठा पूर्णांकel_ntb_dev *ndev)
अणु
	वापस ndev_init_isr(ndev, XEON_DB_MSIX_VECTOR_COUNT,
			     XEON_DB_MSIX_VECTOR_COUNT,
			     XEON_DB_MSIX_VECTOR_SHIFT,
			     XEON_DB_TOTAL_SHIFT);
पूर्ण

अटल व्योम xeon_deinit_isr(काष्ठा पूर्णांकel_ntb_dev *ndev)
अणु
	ndev_deinit_isr(ndev);
पूर्ण

अटल पूर्णांक xeon_setup_b2b_mw(काष्ठा पूर्णांकel_ntb_dev *ndev,
			     स्थिर काष्ठा पूर्णांकel_b2b_addr *addr,
			     स्थिर काष्ठा पूर्णांकel_b2b_addr *peer_addr)
अणु
	काष्ठा pci_dev *pdev;
	व्योम __iomem *mmio;
	resource_माप_प्रकार bar_size;
	phys_addr_t bar_addr;
	पूर्णांक b2b_bar;
	u8 bar_sz;

	pdev = ndev->ntb.pdev;
	mmio = ndev->self_mmio;

	अगर (ndev->b2b_idx == अच_पूर्णांक_उच्च) अणु
		dev_dbg(&pdev->dev, "not using b2b mw\n");
		b2b_bar = 0;
		ndev->b2b_off = 0;
	पूर्ण अन्यथा अणु
		b2b_bar = ndev_mw_to_bar(ndev, ndev->b2b_idx);
		अगर (b2b_bar < 0)
			वापस -EIO;

		dev_dbg(&pdev->dev, "using b2b mw bar %d\n", b2b_bar);

		bar_size = pci_resource_len(ndev->ntb.pdev, b2b_bar);

		dev_dbg(&pdev->dev, "b2b bar size %#llx\n", bar_size);

		अगर (b2b_mw_share && XEON_B2B_MIN_SIZE <= bar_size >> 1) अणु
			dev_dbg(&pdev->dev, "b2b using first half of bar\n");
			ndev->b2b_off = bar_size >> 1;
		पूर्ण अन्यथा अगर (XEON_B2B_MIN_SIZE <= bar_size) अणु
			dev_dbg(&pdev->dev, "b2b using whole bar\n");
			ndev->b2b_off = 0;
			--ndev->mw_count;
		पूर्ण अन्यथा अणु
			dev_dbg(&pdev->dev, "b2b bar size is too small\n");
			वापस -EIO;
		पूर्ण
	पूर्ण

	/* Reset the secondary bar sizes to match the primary bar sizes,
	 * except disable or halve the size of the b2b secondary bar.
	 *
	 * Note: code क्रम each specअगरic bar size रेजिस्टर, because the रेजिस्टर
	 * offsets are not in a consistent order (bar5sz comes after ppd, odd).
	 */
	pci_पढ़ो_config_byte(pdev, XEON_PBAR23SZ_OFFSET, &bar_sz);
	dev_dbg(&pdev->dev, "PBAR23SZ %#x\n", bar_sz);
	अगर (b2b_bar == 2) अणु
		अगर (ndev->b2b_off)
			bar_sz -= 1;
		अन्यथा
			bar_sz = 0;
	पूर्ण
	pci_ग_लिखो_config_byte(pdev, XEON_SBAR23SZ_OFFSET, bar_sz);
	pci_पढ़ो_config_byte(pdev, XEON_SBAR23SZ_OFFSET, &bar_sz);
	dev_dbg(&pdev->dev, "SBAR23SZ %#x\n", bar_sz);

	अगर (!ndev->bar4_split) अणु
		pci_पढ़ो_config_byte(pdev, XEON_PBAR45SZ_OFFSET, &bar_sz);
		dev_dbg(&pdev->dev, "PBAR45SZ %#x\n", bar_sz);
		अगर (b2b_bar == 4) अणु
			अगर (ndev->b2b_off)
				bar_sz -= 1;
			अन्यथा
				bar_sz = 0;
		पूर्ण
		pci_ग_लिखो_config_byte(pdev, XEON_SBAR45SZ_OFFSET, bar_sz);
		pci_पढ़ो_config_byte(pdev, XEON_SBAR45SZ_OFFSET, &bar_sz);
		dev_dbg(&pdev->dev, "SBAR45SZ %#x\n", bar_sz);
	पूर्ण अन्यथा अणु
		pci_पढ़ो_config_byte(pdev, XEON_PBAR4SZ_OFFSET, &bar_sz);
		dev_dbg(&pdev->dev, "PBAR4SZ %#x\n", bar_sz);
		अगर (b2b_bar == 4) अणु
			अगर (ndev->b2b_off)
				bar_sz -= 1;
			अन्यथा
				bar_sz = 0;
		पूर्ण
		pci_ग_लिखो_config_byte(pdev, XEON_SBAR4SZ_OFFSET, bar_sz);
		pci_पढ़ो_config_byte(pdev, XEON_SBAR4SZ_OFFSET, &bar_sz);
		dev_dbg(&pdev->dev, "SBAR4SZ %#x\n", bar_sz);

		pci_पढ़ो_config_byte(pdev, XEON_PBAR5SZ_OFFSET, &bar_sz);
		dev_dbg(&pdev->dev, "PBAR5SZ %#x\n", bar_sz);
		अगर (b2b_bar == 5) अणु
			अगर (ndev->b2b_off)
				bar_sz -= 1;
			अन्यथा
				bar_sz = 0;
		पूर्ण
		pci_ग_लिखो_config_byte(pdev, XEON_SBAR5SZ_OFFSET, bar_sz);
		pci_पढ़ो_config_byte(pdev, XEON_SBAR5SZ_OFFSET, &bar_sz);
		dev_dbg(&pdev->dev, "SBAR5SZ %#x\n", bar_sz);
	पूर्ण

	/* SBAR01 hit by first part of the b2b bar */
	अगर (b2b_bar == 0)
		bar_addr = addr->bar0_addr;
	अन्यथा अगर (b2b_bar == 2)
		bar_addr = addr->bar2_addr64;
	अन्यथा अगर (b2b_bar == 4 && !ndev->bar4_split)
		bar_addr = addr->bar4_addr64;
	अन्यथा अगर (b2b_bar == 4)
		bar_addr = addr->bar4_addr32;
	अन्यथा अगर (b2b_bar == 5)
		bar_addr = addr->bar5_addr32;
	अन्यथा
		वापस -EIO;

	dev_dbg(&pdev->dev, "SBAR01 %#018llx\n", bar_addr);
	ioग_लिखो64(bar_addr, mmio + XEON_SBAR0BASE_OFFSET);

	/* Other SBAR are normally hit by the PBAR xlat, except क्रम b2b bar.
	 * The b2b bar is either disabled above, or configured half-size, and
	 * it starts at the PBAR xlat + offset.
	 */

	bar_addr = addr->bar2_addr64 + (b2b_bar == 2 ? ndev->b2b_off : 0);
	ioग_लिखो64(bar_addr, mmio + XEON_SBAR23BASE_OFFSET);
	bar_addr = ioपढ़ो64(mmio + XEON_SBAR23BASE_OFFSET);
	dev_dbg(&pdev->dev, "SBAR23 %#018llx\n", bar_addr);

	अगर (!ndev->bar4_split) अणु
		bar_addr = addr->bar4_addr64 +
			(b2b_bar == 4 ? ndev->b2b_off : 0);
		ioग_लिखो64(bar_addr, mmio + XEON_SBAR45BASE_OFFSET);
		bar_addr = ioपढ़ो64(mmio + XEON_SBAR45BASE_OFFSET);
		dev_dbg(&pdev->dev, "SBAR45 %#018llx\n", bar_addr);
	पूर्ण अन्यथा अणु
		bar_addr = addr->bar4_addr32 +
			(b2b_bar == 4 ? ndev->b2b_off : 0);
		ioग_लिखो32(bar_addr, mmio + XEON_SBAR4BASE_OFFSET);
		bar_addr = ioपढ़ो32(mmio + XEON_SBAR4BASE_OFFSET);
		dev_dbg(&pdev->dev, "SBAR4 %#010llx\n", bar_addr);

		bar_addr = addr->bar5_addr32 +
			(b2b_bar == 5 ? ndev->b2b_off : 0);
		ioग_लिखो32(bar_addr, mmio + XEON_SBAR5BASE_OFFSET);
		bar_addr = ioपढ़ो32(mmio + XEON_SBAR5BASE_OFFSET);
		dev_dbg(&pdev->dev, "SBAR5 %#010llx\n", bar_addr);
	पूर्ण

	/* setup incoming bar limits == base addrs (zero length winकरोws) */

	bar_addr = addr->bar2_addr64 + (b2b_bar == 2 ? ndev->b2b_off : 0);
	ioग_लिखो64(bar_addr, mmio + XEON_SBAR23LMT_OFFSET);
	bar_addr = ioपढ़ो64(mmio + XEON_SBAR23LMT_OFFSET);
	dev_dbg(&pdev->dev, "SBAR23LMT %#018llx\n", bar_addr);

	अगर (!ndev->bar4_split) अणु
		bar_addr = addr->bar4_addr64 +
			(b2b_bar == 4 ? ndev->b2b_off : 0);
		ioग_लिखो64(bar_addr, mmio + XEON_SBAR45LMT_OFFSET);
		bar_addr = ioपढ़ो64(mmio + XEON_SBAR45LMT_OFFSET);
		dev_dbg(&pdev->dev, "SBAR45LMT %#018llx\n", bar_addr);
	पूर्ण अन्यथा अणु
		bar_addr = addr->bar4_addr32 +
			(b2b_bar == 4 ? ndev->b2b_off : 0);
		ioग_लिखो32(bar_addr, mmio + XEON_SBAR4LMT_OFFSET);
		bar_addr = ioपढ़ो32(mmio + XEON_SBAR4LMT_OFFSET);
		dev_dbg(&pdev->dev, "SBAR4LMT %#010llx\n", bar_addr);

		bar_addr = addr->bar5_addr32 +
			(b2b_bar == 5 ? ndev->b2b_off : 0);
		ioग_लिखो32(bar_addr, mmio + XEON_SBAR5LMT_OFFSET);
		bar_addr = ioपढ़ो32(mmio + XEON_SBAR5LMT_OFFSET);
		dev_dbg(&pdev->dev, "SBAR5LMT %#05llx\n", bar_addr);
	पूर्ण

	/* zero incoming translation addrs */
	ioग_लिखो64(0, mmio + XEON_SBAR23XLAT_OFFSET);

	अगर (!ndev->bar4_split) अणु
		ioग_लिखो64(0, mmio + XEON_SBAR45XLAT_OFFSET);
	पूर्ण अन्यथा अणु
		ioग_लिखो32(0, mmio + XEON_SBAR4XLAT_OFFSET);
		ioग_लिखो32(0, mmio + XEON_SBAR5XLAT_OFFSET);
	पूर्ण

	/* zero outgoing translation limits (whole bar size winकरोws) */
	ioग_लिखो64(0, mmio + XEON_PBAR23LMT_OFFSET);
	अगर (!ndev->bar4_split) अणु
		ioग_लिखो64(0, mmio + XEON_PBAR45LMT_OFFSET);
	पूर्ण अन्यथा अणु
		ioग_लिखो32(0, mmio + XEON_PBAR4LMT_OFFSET);
		ioग_लिखो32(0, mmio + XEON_PBAR5LMT_OFFSET);
	पूर्ण

	/* set outgoing translation offsets */
	bar_addr = peer_addr->bar2_addr64;
	ioग_लिखो64(bar_addr, mmio + XEON_PBAR23XLAT_OFFSET);
	bar_addr = ioपढ़ो64(mmio + XEON_PBAR23XLAT_OFFSET);
	dev_dbg(&pdev->dev, "PBAR23XLAT %#018llx\n", bar_addr);

	अगर (!ndev->bar4_split) अणु
		bar_addr = peer_addr->bar4_addr64;
		ioग_लिखो64(bar_addr, mmio + XEON_PBAR45XLAT_OFFSET);
		bar_addr = ioपढ़ो64(mmio + XEON_PBAR45XLAT_OFFSET);
		dev_dbg(&pdev->dev, "PBAR45XLAT %#018llx\n", bar_addr);
	पूर्ण अन्यथा अणु
		bar_addr = peer_addr->bar4_addr32;
		ioग_लिखो32(bar_addr, mmio + XEON_PBAR4XLAT_OFFSET);
		bar_addr = ioपढ़ो32(mmio + XEON_PBAR4XLAT_OFFSET);
		dev_dbg(&pdev->dev, "PBAR4XLAT %#010llx\n", bar_addr);

		bar_addr = peer_addr->bar5_addr32;
		ioग_लिखो32(bar_addr, mmio + XEON_PBAR5XLAT_OFFSET);
		bar_addr = ioपढ़ो32(mmio + XEON_PBAR5XLAT_OFFSET);
		dev_dbg(&pdev->dev, "PBAR5XLAT %#010llx\n", bar_addr);
	पूर्ण

	/* set the translation offset क्रम b2b रेजिस्टरs */
	अगर (b2b_bar == 0)
		bar_addr = peer_addr->bar0_addr;
	अन्यथा अगर (b2b_bar == 2)
		bar_addr = peer_addr->bar2_addr64;
	अन्यथा अगर (b2b_bar == 4 && !ndev->bar4_split)
		bar_addr = peer_addr->bar4_addr64;
	अन्यथा अगर (b2b_bar == 4)
		bar_addr = peer_addr->bar4_addr32;
	अन्यथा अगर (b2b_bar == 5)
		bar_addr = peer_addr->bar5_addr32;
	अन्यथा
		वापस -EIO;

	/* B2B_XLAT_OFFSET is 64bit, but can only take 32bit ग_लिखोs */
	dev_dbg(&pdev->dev, "B2BXLAT %#018llx\n", bar_addr);
	ioग_लिखो32(bar_addr, mmio + XEON_B2B_XLAT_OFFSETL);
	ioग_लिखो32(bar_addr >> 32, mmio + XEON_B2B_XLAT_OFFSETU);

	अगर (b2b_bar) अणु
		/* map peer ntb mmio config space रेजिस्टरs */
		ndev->peer_mmio = pci_iomap(pdev, b2b_bar,
					    XEON_B2B_MIN_SIZE);
		अगर (!ndev->peer_mmio)
			वापस -EIO;

		ndev->peer_addr = pci_resource_start(pdev, b2b_bar);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक xeon_init_ntb(काष्ठा पूर्णांकel_ntb_dev *ndev)
अणु
	काष्ठा device *dev = &ndev->ntb.pdev->dev;
	पूर्णांक rc;
	u32 ntb_ctl;

	अगर (ndev->bar4_split)
		ndev->mw_count = HSX_SPLIT_BAR_MW_COUNT;
	अन्यथा
		ndev->mw_count = XEON_MW_COUNT;

	ndev->spad_count = XEON_SPAD_COUNT;
	ndev->db_count = XEON_DB_COUNT;
	ndev->db_link_mask = XEON_DB_LINK_BIT;

	चयन (ndev->ntb.topo) अणु
	हाल NTB_TOPO_PRI:
		अगर (ndev->hwerr_flags & NTB_HWERR_SDOORBELL_LOCKUP) अणु
			dev_err(dev, "NTB Primary config disabled\n");
			वापस -EINVAL;
		पूर्ण

		/* enable link to allow secondary side device to appear */
		ntb_ctl = ioपढ़ो32(ndev->self_mmio + ndev->reg->ntb_ctl);
		ntb_ctl &= ~NTB_CTL_DISABLE;
		ioग_लिखो32(ntb_ctl, ndev->self_mmio + ndev->reg->ntb_ctl);

		/* use half the spads क्रम the peer */
		ndev->spad_count >>= 1;
		ndev->self_reg = &xeon_pri_reg;
		ndev->peer_reg = &xeon_sec_reg;
		ndev->xlat_reg = &xeon_sec_xlat;
		अवरोध;

	हाल NTB_TOPO_SEC:
		अगर (ndev->hwerr_flags & NTB_HWERR_SDOORBELL_LOCKUP) अणु
			dev_err(dev, "NTB Secondary config disabled\n");
			वापस -EINVAL;
		पूर्ण
		/* use half the spads क्रम the peer */
		ndev->spad_count >>= 1;
		ndev->self_reg = &xeon_sec_reg;
		ndev->peer_reg = &xeon_pri_reg;
		ndev->xlat_reg = &xeon_pri_xlat;
		अवरोध;

	हाल NTB_TOPO_B2B_USD:
	हाल NTB_TOPO_B2B_DSD:
		ndev->self_reg = &xeon_pri_reg;
		ndev->peer_reg = &xeon_b2b_reg;
		ndev->xlat_reg = &xeon_sec_xlat;

		अगर (ndev->hwerr_flags & NTB_HWERR_SDOORBELL_LOCKUP) अणु
			ndev->peer_reg = &xeon_pri_reg;

			अगर (b2b_mw_idx < 0)
				ndev->b2b_idx = b2b_mw_idx + ndev->mw_count;
			अन्यथा
				ndev->b2b_idx = b2b_mw_idx;

			अगर (ndev->b2b_idx >= ndev->mw_count) अणु
				dev_dbg(dev,
					"b2b_mw_idx %d invalid for mw_count %u\n",
					b2b_mw_idx, ndev->mw_count);
				वापस -EINVAL;
			पूर्ण

			dev_dbg(dev, "setting up b2b mw idx %d means %d\n",
				b2b_mw_idx, ndev->b2b_idx);

		पूर्ण अन्यथा अगर (ndev->hwerr_flags & NTB_HWERR_B2BDOORBELL_BIT14) अणु
			dev_warn(dev, "Reduce doorbell count by 1\n");
			ndev->db_count -= 1;
		पूर्ण

		अगर (ndev->ntb.topo == NTB_TOPO_B2B_USD) अणु
			rc = xeon_setup_b2b_mw(ndev,
					       &xeon_b2b_dsd_addr,
					       &xeon_b2b_usd_addr);
		पूर्ण अन्यथा अणु
			rc = xeon_setup_b2b_mw(ndev,
					       &xeon_b2b_usd_addr,
					       &xeon_b2b_dsd_addr);
		पूर्ण
		अगर (rc)
			वापस rc;

		/* Enable Bus Master and Memory Space on the secondary side */
		ioग_लिखो16(PCI_COMMAND_MEMORY | PCI_COMMAND_MASTER,
			  ndev->self_mmio + XEON_SPCICMD_OFFSET);

		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	ndev->db_valid_mask = BIT_ULL(ndev->db_count) - 1;

	ndev->reg->db_ioग_लिखो(ndev->db_valid_mask,
			      ndev->self_mmio +
			      ndev->self_reg->db_mask);

	वापस 0;
पूर्ण

अटल पूर्णांक xeon_init_dev(काष्ठा पूर्णांकel_ntb_dev *ndev)
अणु
	काष्ठा pci_dev *pdev;
	u8 ppd;
	पूर्णांक rc, mem;

	pdev = ndev->ntb.pdev;

	चयन (pdev->device) अणु
	/* There is a Xeon hardware errata related to ग_लिखोs to SDOORBELL or
	 * B2BDOORBELL in conjunction with inbound access to NTB MMIO Space,
	 * which may hang the प्रणाली.  To workaround this use the second memory
	 * winकरोw to access the पूर्णांकerrupt and scratch pad रेजिस्टरs on the
	 * remote प्रणाली.
	 */
	हाल PCI_DEVICE_ID_INTEL_NTB_SS_JSF:
	हाल PCI_DEVICE_ID_INTEL_NTB_PS_JSF:
	हाल PCI_DEVICE_ID_INTEL_NTB_B2B_JSF:
	हाल PCI_DEVICE_ID_INTEL_NTB_SS_SNB:
	हाल PCI_DEVICE_ID_INTEL_NTB_PS_SNB:
	हाल PCI_DEVICE_ID_INTEL_NTB_B2B_SNB:
	हाल PCI_DEVICE_ID_INTEL_NTB_SS_IVT:
	हाल PCI_DEVICE_ID_INTEL_NTB_PS_IVT:
	हाल PCI_DEVICE_ID_INTEL_NTB_B2B_IVT:
	हाल PCI_DEVICE_ID_INTEL_NTB_SS_HSX:
	हाल PCI_DEVICE_ID_INTEL_NTB_PS_HSX:
	हाल PCI_DEVICE_ID_INTEL_NTB_B2B_HSX:
	हाल PCI_DEVICE_ID_INTEL_NTB_SS_BDX:
	हाल PCI_DEVICE_ID_INTEL_NTB_PS_BDX:
	हाल PCI_DEVICE_ID_INTEL_NTB_B2B_BDX:
		ndev->hwerr_flags |= NTB_HWERR_SDOORBELL_LOCKUP;
		अवरोध;
	पूर्ण

	चयन (pdev->device) अणु
	/* There is a hardware errata related to accessing any रेजिस्टर in
	 * SB01BASE in the presence of bidirectional traffic crossing the NTB.
	 */
	हाल PCI_DEVICE_ID_INTEL_NTB_SS_IVT:
	हाल PCI_DEVICE_ID_INTEL_NTB_PS_IVT:
	हाल PCI_DEVICE_ID_INTEL_NTB_B2B_IVT:
	हाल PCI_DEVICE_ID_INTEL_NTB_SS_HSX:
	हाल PCI_DEVICE_ID_INTEL_NTB_PS_HSX:
	हाल PCI_DEVICE_ID_INTEL_NTB_B2B_HSX:
	हाल PCI_DEVICE_ID_INTEL_NTB_SS_BDX:
	हाल PCI_DEVICE_ID_INTEL_NTB_PS_BDX:
	हाल PCI_DEVICE_ID_INTEL_NTB_B2B_BDX:
		ndev->hwerr_flags |= NTB_HWERR_SB01BASE_LOCKUP;
		अवरोध;
	पूर्ण

	चयन (pdev->device) अणु
	/* HW Errata on bit 14 of b2bकरोorbell रेजिस्टर.  Writes will not be
	 * mirrored to the remote प्रणाली.  Shrink the number of bits by one,
	 * since bit 14 is the last bit.
	 */
	हाल PCI_DEVICE_ID_INTEL_NTB_SS_JSF:
	हाल PCI_DEVICE_ID_INTEL_NTB_PS_JSF:
	हाल PCI_DEVICE_ID_INTEL_NTB_B2B_JSF:
	हाल PCI_DEVICE_ID_INTEL_NTB_SS_SNB:
	हाल PCI_DEVICE_ID_INTEL_NTB_PS_SNB:
	हाल PCI_DEVICE_ID_INTEL_NTB_B2B_SNB:
	हाल PCI_DEVICE_ID_INTEL_NTB_SS_IVT:
	हाल PCI_DEVICE_ID_INTEL_NTB_PS_IVT:
	हाल PCI_DEVICE_ID_INTEL_NTB_B2B_IVT:
	हाल PCI_DEVICE_ID_INTEL_NTB_SS_HSX:
	हाल PCI_DEVICE_ID_INTEL_NTB_PS_HSX:
	हाल PCI_DEVICE_ID_INTEL_NTB_B2B_HSX:
	हाल PCI_DEVICE_ID_INTEL_NTB_SS_BDX:
	हाल PCI_DEVICE_ID_INTEL_NTB_PS_BDX:
	हाल PCI_DEVICE_ID_INTEL_NTB_B2B_BDX:
		ndev->hwerr_flags |= NTB_HWERR_B2BDOORBELL_BIT14;
		अवरोध;
	पूर्ण

	ndev->reg = &xeon_reg;

	rc = pci_पढ़ो_config_byte(pdev, XEON_PPD_OFFSET, &ppd);
	अगर (rc)
		वापस -EIO;

	ndev->ntb.topo = xeon_ppd_topo(ndev, ppd);
	dev_dbg(&pdev->dev, "ppd %#x topo %s\n", ppd,
		ntb_topo_string(ndev->ntb.topo));
	अगर (ndev->ntb.topo == NTB_TOPO_NONE)
		वापस -EINVAL;

	अगर (ndev->ntb.topo != NTB_TOPO_SEC) अणु
		ndev->bar4_split = xeon_ppd_bar4_split(ndev, ppd);
		dev_dbg(&pdev->dev, "ppd %#x bar4_split %d\n",
			ppd, ndev->bar4_split);
	पूर्ण अन्यथा अणु
		/* This is a way क्रम transparent BAR to figure out अगर we are
		 * करोing split BAR or not. There is no way क्रम the hw on the
		 * transparent side to know and set the PPD.
		 */
		mem = pci_select_bars(pdev, IORESOURCE_MEM);
		ndev->bar4_split = hweight32(mem) ==
			HSX_SPLIT_BAR_MW_COUNT + 1;
		dev_dbg(&pdev->dev, "mem %#x bar4_split %d\n",
			mem, ndev->bar4_split);
	पूर्ण

	rc = xeon_init_ntb(ndev);
	अगर (rc)
		वापस rc;

	वापस xeon_init_isr(ndev);
पूर्ण

अटल व्योम xeon_deinit_dev(काष्ठा पूर्णांकel_ntb_dev *ndev)
अणु
	xeon_deinit_isr(ndev);
पूर्ण

अटल पूर्णांक पूर्णांकel_ntb_init_pci(काष्ठा पूर्णांकel_ntb_dev *ndev, काष्ठा pci_dev *pdev)
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
		जाओ err_mmio;
	पूर्ण
	ndev->peer_mmio = ndev->self_mmio;
	ndev->peer_addr = pci_resource_start(pdev, 0);

	वापस 0;

err_mmio:
err_dma_mask:
	pci_clear_master(pdev);
	pci_release_regions(pdev);
err_pci_regions:
	pci_disable_device(pdev);
err_pci_enable:
	pci_set_drvdata(pdev, शून्य);
	वापस rc;
पूर्ण

अटल व्योम पूर्णांकel_ntb_deinit_pci(काष्ठा पूर्णांकel_ntb_dev *ndev)
अणु
	काष्ठा pci_dev *pdev = ndev->ntb.pdev;

	अगर (ndev->peer_mmio && ndev->peer_mmio != ndev->self_mmio)
		pci_iounmap(pdev, ndev->peer_mmio);
	pci_iounmap(pdev, ndev->self_mmio);

	pci_clear_master(pdev);
	pci_release_regions(pdev);
	pci_disable_device(pdev);
	pci_set_drvdata(pdev, शून्य);
पूर्ण

अटल अंतरभूत व्योम ndev_init_काष्ठा(काष्ठा पूर्णांकel_ntb_dev *ndev,
				    काष्ठा pci_dev *pdev)
अणु
	ndev->ntb.pdev = pdev;
	ndev->ntb.topo = NTB_TOPO_NONE;
	ndev->ntb.ops = &पूर्णांकel_ntb_ops;

	ndev->b2b_off = 0;
	ndev->b2b_idx = अच_पूर्णांक_उच्च;

	ndev->bar4_split = 0;

	ndev->mw_count = 0;
	ndev->spad_count = 0;
	ndev->db_count = 0;
	ndev->db_vec_count = 0;
	ndev->db_vec_shअगरt = 0;

	ndev->ntb_ctl = 0;
	ndev->lnk_sta = 0;

	ndev->db_valid_mask = 0;
	ndev->db_link_mask = 0;
	ndev->db_mask = 0;

	spin_lock_init(&ndev->db_mask_lock);
पूर्ण

अटल पूर्णांक पूर्णांकel_ntb_pci_probe(काष्ठा pci_dev *pdev,
			       स्थिर काष्ठा pci_device_id *id)
अणु
	काष्ठा पूर्णांकel_ntb_dev *ndev;
	पूर्णांक rc, node;

	node = dev_to_node(&pdev->dev);
	ndev = kzalloc_node(माप(*ndev), GFP_KERNEL, node);
	अगर (!ndev) अणु
		rc = -ENOMEM;
		जाओ err_ndev;
	पूर्ण

	ndev_init_काष्ठा(ndev, pdev);

	अगर (pdev_is_gen1(pdev)) अणु
		rc = पूर्णांकel_ntb_init_pci(ndev, pdev);
		अगर (rc)
			जाओ err_init_pci;

		rc = xeon_init_dev(ndev);
		अगर (rc)
			जाओ err_init_dev;
	पूर्ण अन्यथा अगर (pdev_is_gen3(pdev)) अणु
		ndev->ntb.ops = &पूर्णांकel_ntb3_ops;
		rc = पूर्णांकel_ntb_init_pci(ndev, pdev);
		अगर (rc)
			जाओ err_init_pci;

		rc = gen3_init_dev(ndev);
		अगर (rc)
			जाओ err_init_dev;
	पूर्ण अन्यथा अगर (pdev_is_gen4(pdev)) अणु
		ndev->ntb.ops = &पूर्णांकel_ntb4_ops;
		rc = पूर्णांकel_ntb_init_pci(ndev, pdev);
		अगर (rc)
			जाओ err_init_pci;

		rc = gen4_init_dev(ndev);
		अगर (rc)
			जाओ err_init_dev;
	पूर्ण अन्यथा अणु
		rc = -EINVAL;
		जाओ err_init_pci;
	पूर्ण

	ndev_reset_unsafe_flags(ndev);

	ndev->reg->poll_link(ndev);

	ndev_init_debugfs(ndev);

	rc = ntb_रेजिस्टर_device(&ndev->ntb);
	अगर (rc)
		जाओ err_रेजिस्टर;

	dev_info(&pdev->dev, "NTB device registered.\n");

	वापस 0;

err_रेजिस्टर:
	ndev_deinit_debugfs(ndev);
	अगर (pdev_is_gen1(pdev) || pdev_is_gen3(pdev) || pdev_is_gen4(pdev))
		xeon_deinit_dev(ndev);
err_init_dev:
	पूर्णांकel_ntb_deinit_pci(ndev);
err_init_pci:
	kमुक्त(ndev);
err_ndev:
	वापस rc;
पूर्ण

अटल व्योम पूर्णांकel_ntb_pci_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा पूर्णांकel_ntb_dev *ndev = pci_get_drvdata(pdev);

	ntb_unरेजिस्टर_device(&ndev->ntb);
	ndev_deinit_debugfs(ndev);
	अगर (pdev_is_gen1(pdev) || pdev_is_gen3(pdev) || pdev_is_gen4(pdev))
		xeon_deinit_dev(ndev);
	पूर्णांकel_ntb_deinit_pci(ndev);
	kमुक्त(ndev);
पूर्ण

अटल स्थिर काष्ठा पूर्णांकel_ntb_reg xeon_reg = अणु
	.poll_link		= xeon_poll_link,
	.link_is_up		= xeon_link_is_up,
	.db_ioपढ़ो		= xeon_db_ioपढ़ो,
	.db_ioग_लिखो		= xeon_db_ioग_लिखो,
	.db_size		= माप(u32),
	.ntb_ctl		= XEON_NTBCNTL_OFFSET,
	.mw_bar			= अणु2, 4, 5पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा पूर्णांकel_ntb_alt_reg xeon_pri_reg = अणु
	.db_bell		= XEON_PDOORBELL_OFFSET,
	.db_mask		= XEON_PDBMSK_OFFSET,
	.spad			= XEON_SPAD_OFFSET,
पूर्ण;

अटल स्थिर काष्ठा पूर्णांकel_ntb_alt_reg xeon_sec_reg = अणु
	.db_bell		= XEON_SDOORBELL_OFFSET,
	.db_mask		= XEON_SDBMSK_OFFSET,
	/* second half of the scratchpads */
	.spad			= XEON_SPAD_OFFSET + (XEON_SPAD_COUNT << 1),
पूर्ण;

अटल स्थिर काष्ठा पूर्णांकel_ntb_alt_reg xeon_b2b_reg = अणु
	.db_bell		= XEON_B2B_DOORBELL_OFFSET,
	.spad			= XEON_B2B_SPAD_OFFSET,
पूर्ण;

अटल स्थिर काष्ठा पूर्णांकel_ntb_xlat_reg xeon_pri_xlat = अणु
	/* Note: no primary .bar0_base visible to the secondary side.
	 *
	 * The secondary side cannot get the base address stored in primary
	 * bars.  The base address is necessary to set the limit रेजिस्टर to
	 * any value other than zero, or unlimited.
	 *
	 * WITHOUT THE BASE ADDRESS, THE SECONDARY SIDE CANNOT DISABLE the
	 * winकरोw by setting the limit equal to base, nor can it limit the size
	 * of the memory winकरोw by setting the limit to base + size.
	 */
	.bar2_limit		= XEON_PBAR23LMT_OFFSET,
	.bar2_xlat		= XEON_PBAR23XLAT_OFFSET,
पूर्ण;

अटल स्थिर काष्ठा पूर्णांकel_ntb_xlat_reg xeon_sec_xlat = अणु
	.bar0_base		= XEON_SBAR0BASE_OFFSET,
	.bar2_limit		= XEON_SBAR23LMT_OFFSET,
	.bar2_xlat		= XEON_SBAR23XLAT_OFFSET,
पूर्ण;

काष्ठा पूर्णांकel_b2b_addr xeon_b2b_usd_addr = अणु
	.bar2_addr64		= XEON_B2B_BAR2_ADDR64,
	.bar4_addr64		= XEON_B2B_BAR4_ADDR64,
	.bar4_addr32		= XEON_B2B_BAR4_ADDR32,
	.bar5_addr32		= XEON_B2B_BAR5_ADDR32,
पूर्ण;

काष्ठा पूर्णांकel_b2b_addr xeon_b2b_dsd_addr = अणु
	.bar2_addr64		= XEON_B2B_BAR2_ADDR64,
	.bar4_addr64		= XEON_B2B_BAR4_ADDR64,
	.bar4_addr32		= XEON_B2B_BAR4_ADDR32,
	.bar5_addr32		= XEON_B2B_BAR5_ADDR32,
पूर्ण;

/* operations क्रम primary side of local ntb */
अटल स्थिर काष्ठा ntb_dev_ops पूर्णांकel_ntb_ops = अणु
	.mw_count		= पूर्णांकel_ntb_mw_count,
	.mw_get_align		= पूर्णांकel_ntb_mw_get_align,
	.mw_set_trans		= पूर्णांकel_ntb_mw_set_trans,
	.peer_mw_count		= पूर्णांकel_ntb_peer_mw_count,
	.peer_mw_get_addr	= पूर्णांकel_ntb_peer_mw_get_addr,
	.link_is_up		= पूर्णांकel_ntb_link_is_up,
	.link_enable		= पूर्णांकel_ntb_link_enable,
	.link_disable		= पूर्णांकel_ntb_link_disable,
	.db_is_unsafe		= पूर्णांकel_ntb_db_is_unsafe,
	.db_valid_mask		= पूर्णांकel_ntb_db_valid_mask,
	.db_vector_count	= पूर्णांकel_ntb_db_vector_count,
	.db_vector_mask		= पूर्णांकel_ntb_db_vector_mask,
	.db_पढ़ो		= पूर्णांकel_ntb_db_पढ़ो,
	.db_clear		= पूर्णांकel_ntb_db_clear,
	.db_set_mask		= पूर्णांकel_ntb_db_set_mask,
	.db_clear_mask		= पूर्णांकel_ntb_db_clear_mask,
	.peer_db_addr		= पूर्णांकel_ntb_peer_db_addr,
	.peer_db_set		= पूर्णांकel_ntb_peer_db_set,
	.spad_is_unsafe		= पूर्णांकel_ntb_spad_is_unsafe,
	.spad_count		= पूर्णांकel_ntb_spad_count,
	.spad_पढ़ो		= पूर्णांकel_ntb_spad_पढ़ो,
	.spad_ग_लिखो		= पूर्णांकel_ntb_spad_ग_लिखो,
	.peer_spad_addr		= पूर्णांकel_ntb_peer_spad_addr,
	.peer_spad_पढ़ो		= पूर्णांकel_ntb_peer_spad_पढ़ो,
	.peer_spad_ग_लिखो	= पूर्णांकel_ntb_peer_spad_ग_लिखो,
पूर्ण;

अटल स्थिर काष्ठा file_operations पूर्णांकel_ntb_debugfs_info = अणु
	.owner = THIS_MODULE,
	.खोलो = simple_खोलो,
	.पढ़ो = ndev_debugfs_पढ़ो,
पूर्ण;

अटल स्थिर काष्ठा pci_device_id पूर्णांकel_ntb_pci_tbl[] = अणु
	/* GEN1 */
	अणुPCI_VDEVICE(INTEL, PCI_DEVICE_ID_INTEL_NTB_B2B_JSF)पूर्ण,
	अणुPCI_VDEVICE(INTEL, PCI_DEVICE_ID_INTEL_NTB_B2B_SNB)पूर्ण,
	अणुPCI_VDEVICE(INTEL, PCI_DEVICE_ID_INTEL_NTB_B2B_IVT)पूर्ण,
	अणुPCI_VDEVICE(INTEL, PCI_DEVICE_ID_INTEL_NTB_B2B_HSX)पूर्ण,
	अणुPCI_VDEVICE(INTEL, PCI_DEVICE_ID_INTEL_NTB_B2B_BDX)पूर्ण,
	अणुPCI_VDEVICE(INTEL, PCI_DEVICE_ID_INTEL_NTB_PS_JSF)पूर्ण,
	अणुPCI_VDEVICE(INTEL, PCI_DEVICE_ID_INTEL_NTB_PS_SNB)पूर्ण,
	अणुPCI_VDEVICE(INTEL, PCI_DEVICE_ID_INTEL_NTB_PS_IVT)पूर्ण,
	अणुPCI_VDEVICE(INTEL, PCI_DEVICE_ID_INTEL_NTB_PS_HSX)पूर्ण,
	अणुPCI_VDEVICE(INTEL, PCI_DEVICE_ID_INTEL_NTB_PS_BDX)पूर्ण,
	अणुPCI_VDEVICE(INTEL, PCI_DEVICE_ID_INTEL_NTB_SS_JSF)पूर्ण,
	अणुPCI_VDEVICE(INTEL, PCI_DEVICE_ID_INTEL_NTB_SS_SNB)पूर्ण,
	अणुPCI_VDEVICE(INTEL, PCI_DEVICE_ID_INTEL_NTB_SS_IVT)पूर्ण,
	अणुPCI_VDEVICE(INTEL, PCI_DEVICE_ID_INTEL_NTB_SS_HSX)पूर्ण,
	अणुPCI_VDEVICE(INTEL, PCI_DEVICE_ID_INTEL_NTB_SS_BDX)पूर्ण,

	/* GEN3 */
	अणुPCI_VDEVICE(INTEL, PCI_DEVICE_ID_INTEL_NTB_B2B_SKX)पूर्ण,

	/* GEN4 */
	अणुPCI_VDEVICE(INTEL, PCI_DEVICE_ID_INTEL_NTB_B2B_ICX)पूर्ण,
	अणु0पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(pci, पूर्णांकel_ntb_pci_tbl);

अटल काष्ठा pci_driver पूर्णांकel_ntb_pci_driver = अणु
	.name = KBUILD_MODNAME,
	.id_table = पूर्णांकel_ntb_pci_tbl,
	.probe = पूर्णांकel_ntb_pci_probe,
	.हटाओ = पूर्णांकel_ntb_pci_हटाओ,
पूर्ण;

अटल पूर्णांक __init पूर्णांकel_ntb_pci_driver_init(व्योम)
अणु
	pr_info("%s %s\n", NTB_DESC, NTB_VER);

	अगर (debugfs_initialized())
		debugfs_dir = debugfs_create_dir(KBUILD_MODNAME, शून्य);

	वापस pci_रेजिस्टर_driver(&पूर्णांकel_ntb_pci_driver);
पूर्ण
module_init(पूर्णांकel_ntb_pci_driver_init);

अटल व्योम __निकास पूर्णांकel_ntb_pci_driver_निकास(व्योम)
अणु
	pci_unरेजिस्टर_driver(&पूर्णांकel_ntb_pci_driver);

	debugfs_हटाओ_recursive(debugfs_dir);
पूर्ण
module_निकास(पूर्णांकel_ntb_pci_driver_निकास);
