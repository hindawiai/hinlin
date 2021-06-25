<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0 OR BSD-3-Clause)
/* Copyright(c) 2020 Intel Corporation. All rights reserved. */
#समावेश <linux/debugfs.h>
#समावेश <linux/delay.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/slab.h>
#समावेश <linux/ntb.h>
#समावेश <linux/log2.h>

#समावेश "ntb_hw_intel.h"
#समावेश "ntb_hw_gen1.h"
#समावेश "ntb_hw_gen3.h"
#समावेश "ntb_hw_gen4.h"

अटल पूर्णांक gen4_poll_link(काष्ठा पूर्णांकel_ntb_dev *ndev);
अटल पूर्णांक gen4_link_is_up(काष्ठा पूर्णांकel_ntb_dev *ndev);

अटल स्थिर काष्ठा पूर्णांकel_ntb_reg gen4_reg = अणु
	.poll_link		= gen4_poll_link,
	.link_is_up		= gen4_link_is_up,
	.db_ioपढ़ो		= gen3_db_ioपढ़ो,
	.db_ioग_लिखो		= gen3_db_ioग_लिखो,
	.db_size		= माप(u32),
	.ntb_ctl		= GEN4_NTBCNTL_OFFSET,
	.mw_bar			= अणु2, 4पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा पूर्णांकel_ntb_alt_reg gen4_pri_reg = अणु
	.db_clear		= GEN4_IM_INT_STATUS_OFFSET,
	.db_mask		= GEN4_IM_INT_DISABLE_OFFSET,
	.spad			= GEN4_IM_SPAD_OFFSET,
पूर्ण;

अटल स्थिर काष्ठा पूर्णांकel_ntb_xlat_reg gen4_sec_xlat = अणु
	.bar2_limit		= GEN4_IM23XLMT_OFFSET,
	.bar2_xlat		= GEN4_IM23XBASE_OFFSET,
	.bar2_idx		= GEN4_IM23XBASEIDX_OFFSET,
पूर्ण;

अटल स्थिर काष्ठा पूर्णांकel_ntb_alt_reg gen4_b2b_reg = अणु
	.db_bell		= GEN4_IM_DOORBELL_OFFSET,
	.spad			= GEN4_EM_SPAD_OFFSET,
पूर्ण;

अटल पूर्णांक gen4_poll_link(काष्ठा पूर्णांकel_ntb_dev *ndev)
अणु
	u16 reg_val;

	/*
	 * We need to ग_लिखो to DLLSCS bit in the SLOTSTS beक्रमe we
	 * can clear the hardware link पूर्णांकerrupt on ICX NTB.
	 */
	ioग_लिखो16(GEN4_SLOTSTS_DLLSCS, ndev->self_mmio + GEN4_SLOTSTS);
	ndev->reg->db_ioग_लिखो(ndev->db_link_mask,
			      ndev->self_mmio +
			      ndev->self_reg->db_clear);

	reg_val = ioपढ़ो16(ndev->self_mmio + GEN4_LINK_STATUS_OFFSET);
	अगर (reg_val == ndev->lnk_sta)
		वापस 0;

	ndev->lnk_sta = reg_val;

	वापस 1;
पूर्ण

अटल पूर्णांक gen4_link_is_up(काष्ठा पूर्णांकel_ntb_dev *ndev)
अणु
	वापस NTB_LNK_STA_ACTIVE(ndev->lnk_sta);
पूर्ण

अटल पूर्णांक gen4_init_isr(काष्ठा पूर्णांकel_ntb_dev *ndev)
अणु
	पूर्णांक i;

	/*
	 * The MSIX vectors and the पूर्णांकerrupt status bits are not lined up
	 * on Gen3 (Skylake) and Gen4. By शेष the link status bit is bit
	 * 32, however it is by शेष MSIX vector0. We need to fixup to
	 * line them up. The vectors at reset is 1-32,0. We need to reprogram
	 * to 0-32.
	 */
	क्रम (i = 0; i < GEN4_DB_MSIX_VECTOR_COUNT; i++)
		ioग_लिखो8(i, ndev->self_mmio + GEN4_INTVEC_OFFSET + i);

	वापस ndev_init_isr(ndev, GEN4_DB_MSIX_VECTOR_COUNT,
			     GEN4_DB_MSIX_VECTOR_COUNT,
			     GEN4_DB_MSIX_VECTOR_SHIFT,
			     GEN4_DB_TOTAL_SHIFT);
पूर्ण

अटल पूर्णांक gen4_setup_b2b_mw(काष्ठा पूर्णांकel_ntb_dev *ndev,
			    स्थिर काष्ठा पूर्णांकel_b2b_addr *addr,
			    स्थिर काष्ठा पूर्णांकel_b2b_addr *peer_addr)
अणु
	काष्ठा pci_dev *pdev;
	व्योम __iomem *mmio;
	phys_addr_t bar_addr;

	pdev = ndev->ntb.pdev;
	mmio = ndev->self_mmio;

	/* setup incoming bar limits == base addrs (zero length winकरोws) */
	bar_addr = addr->bar2_addr64;
	ioग_लिखो64(bar_addr, mmio + GEN4_IM23XLMT_OFFSET);
	bar_addr = ioपढ़ो64(mmio + GEN4_IM23XLMT_OFFSET);
	dev_dbg(&pdev->dev, "IM23XLMT %#018llx\n", bar_addr);

	bar_addr = addr->bar4_addr64;
	ioग_लिखो64(bar_addr, mmio + GEN4_IM45XLMT_OFFSET);
	bar_addr = ioपढ़ो64(mmio + GEN4_IM45XLMT_OFFSET);
	dev_dbg(&pdev->dev, "IM45XLMT %#018llx\n", bar_addr);

	/* zero incoming translation addrs */
	ioग_लिखो64(0, mmio + GEN4_IM23XBASE_OFFSET);
	ioग_लिखो64(0, mmio + GEN4_IM45XBASE_OFFSET);

	ndev->peer_mmio = ndev->self_mmio;

	वापस 0;
पूर्ण

अटल पूर्णांक gen4_init_ntb(काष्ठा पूर्णांकel_ntb_dev *ndev)
अणु
	पूर्णांक rc;


	ndev->mw_count = XEON_MW_COUNT;
	ndev->spad_count = GEN4_SPAD_COUNT;
	ndev->db_count = GEN4_DB_COUNT;
	ndev->db_link_mask = GEN4_DB_LINK_BIT;

	ndev->self_reg = &gen4_pri_reg;
	ndev->xlat_reg = &gen4_sec_xlat;
	ndev->peer_reg = &gen4_b2b_reg;

	अगर (ndev->ntb.topo == NTB_TOPO_B2B_USD)
		rc = gen4_setup_b2b_mw(ndev, &xeon_b2b_dsd_addr,
				&xeon_b2b_usd_addr);
	अन्यथा
		rc = gen4_setup_b2b_mw(ndev, &xeon_b2b_usd_addr,
				&xeon_b2b_dsd_addr);
	अगर (rc)
		वापस rc;

	ndev->db_valid_mask = BIT_ULL(ndev->db_count) - 1;

	ndev->reg->db_ioग_लिखो(ndev->db_valid_mask,
			      ndev->self_mmio +
			      ndev->self_reg->db_mask);

	वापस 0;
पूर्ण

अटल क्रमागत ntb_topo gen4_ppd_topo(काष्ठा पूर्णांकel_ntb_dev *ndev, u32 ppd)
अणु
	चयन (ppd & GEN4_PPD_TOPO_MASK) अणु
	हाल GEN4_PPD_TOPO_B2B_USD:
		वापस NTB_TOPO_B2B_USD;
	हाल GEN4_PPD_TOPO_B2B_DSD:
		वापस NTB_TOPO_B2B_DSD;
	पूर्ण

	वापस NTB_TOPO_NONE;
पूर्ण

पूर्णांक gen4_init_dev(काष्ठा पूर्णांकel_ntb_dev *ndev)
अणु
	काष्ठा pci_dev *pdev = ndev->ntb.pdev;
	u32 ppd1/*, ppd0*/;
	u16 lnkctl;
	पूर्णांक rc;

	ndev->reg = &gen4_reg;

	अगर (pdev_is_ICX(pdev)) अणु
		ndev->hwerr_flags |= NTB_HWERR_BAR_ALIGN;
		ndev->hwerr_flags |= NTB_HWERR_LTR_BAD;
	पूर्ण

	ppd1 = ioपढ़ो32(ndev->self_mmio + GEN4_PPD1_OFFSET);
	ndev->ntb.topo = gen4_ppd_topo(ndev, ppd1);
	dev_dbg(&pdev->dev, "ppd %#x topo %s\n", ppd1,
		ntb_topo_string(ndev->ntb.topo));
	अगर (ndev->ntb.topo == NTB_TOPO_NONE)
		वापस -EINVAL;

	rc = gen4_init_ntb(ndev);
	अगर (rc)
		वापस rc;

	/* init link setup */
	lnkctl = ioपढ़ो16(ndev->self_mmio + GEN4_LINK_CTRL_OFFSET);
	lnkctl |= GEN4_LINK_CTRL_LINK_DISABLE;
	ioग_लिखो16(lnkctl, ndev->self_mmio + GEN4_LINK_CTRL_OFFSET);

	वापस gen4_init_isr(ndev);
पूर्ण

sमाप_प्रकार ndev_ntb4_debugfs_पढ़ो(काष्ठा file *filp, अक्षर __user *ubuf,
				      माप_प्रकार count, loff_t *offp)
अणु
	काष्ठा पूर्णांकel_ntb_dev *ndev;
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
			 "NTB CTL -\t\t%#06x\n", ndev->ntb_ctl);
	off += scnम_लिखो(buf + off, buf_size - off,
			 "LNK STA (cached) -\t\t%#06x\n", ndev->lnk_sta);

	अगर (!ndev->reg->link_is_up(ndev))
		off += scnम_लिखो(buf + off, buf_size - off,
				 "Link Status -\t\tDown\n");
	अन्यथा अणु
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

	off += scnम_लिखो(buf + off, buf_size - off,
			 "\nNTB Incoming XLAT:\n");

	u.v64 = ioपढ़ो64(mmio + GEN4_IM23XBASE_OFFSET);
	off += scnम_लिखो(buf + off, buf_size - off,
			 "IM23XBASE -\t\t%#018llx\n", u.v64);

	u.v64 = ioपढ़ो64(mmio + GEN4_IM45XBASE_OFFSET);
	off += scnम_लिखो(buf + off, buf_size - off,
			 "IM45XBASE -\t\t%#018llx\n", u.v64);

	u.v64 = ioपढ़ो64(mmio + GEN4_IM23XLMT_OFFSET);
	off += scnम_लिखो(buf + off, buf_size - off,
			 "IM23XLMT -\t\t\t%#018llx\n", u.v64);

	u.v64 = ioपढ़ो64(mmio + GEN4_IM45XLMT_OFFSET);
	off += scnम_लिखो(buf + off, buf_size - off,
			 "IM45XLMT -\t\t\t%#018llx\n", u.v64);

	off += scnम_लिखो(buf + off, buf_size - off,
			 "\nNTB Statistics:\n");

	off += scnम_लिखो(buf + off, buf_size - off,
			 "\nNTB Hardware Errors:\n");

	अगर (!pci_पढ़ो_config_word(ndev->ntb.pdev,
				  GEN4_DEVSTS_OFFSET, &u.v16))
		off += scnम_लिखो(buf + off, buf_size - off,
				"DEVSTS -\t\t%#06x\n", u.v16);

	u.v16 = ioपढ़ो16(mmio + GEN4_LINK_STATUS_OFFSET);
	off += scnम_लिखो(buf + off, buf_size - off,
			"LNKSTS -\t\t%#06x\n", u.v16);

	अगर (!pci_पढ़ो_config_dword(ndev->ntb.pdev,
				   GEN4_UNCERRSTS_OFFSET, &u.v32))
		off += scnम_लिखो(buf + off, buf_size - off,
				 "UNCERRSTS -\t\t%#06x\n", u.v32);

	अगर (!pci_पढ़ो_config_dword(ndev->ntb.pdev,
				   GEN4_CORERRSTS_OFFSET, &u.v32))
		off += scnम_लिखो(buf + off, buf_size - off,
				 "CORERRSTS -\t\t%#06x\n", u.v32);

	ret = simple_पढ़ो_from_buffer(ubuf, count, offp, buf, off);
	kमुक्त(buf);
	वापस ret;
पूर्ण

अटल पूर्णांक पूर्णांकel_ntb4_mw_set_trans(काष्ठा ntb_dev *ntb, पूर्णांक pidx, पूर्णांक idx,
				   dma_addr_t addr, resource_माप_प्रकार size)
अणु
	काष्ठा पूर्णांकel_ntb_dev *ndev = ntb_ndev(ntb);
	अचिन्हित दीर्घ xlat_reg, limit_reg, idx_reg;
	अचिन्हित लघु base_idx, reg_val16;
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

	अगर (ndev->hwerr_flags & NTB_HWERR_BAR_ALIGN) अणु
		/* hardware requires that addr is aligned to bar size */
		अगर (addr & (bar_size - 1))
			वापस -EINVAL;
	पूर्ण अन्यथा अणु
		अगर (addr & (PAGE_SIZE - 1))
			वापस -EINVAL;
	पूर्ण

	/* make sure the range fits in the usable mw size */
	अगर (size > mw_size)
		वापस -EINVAL;

	mmio = ndev->self_mmio;
	xlat_reg = ndev->xlat_reg->bar2_xlat + (idx * 0x10);
	limit_reg = ndev->xlat_reg->bar2_limit + (idx * 0x10);
	base = pci_resource_start(ndev->ntb.pdev, bar);

	/* Set the limit अगर supported, अगर size is not mw_size */
	अगर (limit_reg && size != mw_size) अणु
		limit = base + size;
		base_idx = __ilog2_u64(size);
	पूर्ण अन्यथा अणु
		limit = base + mw_size;
		base_idx = __ilog2_u64(mw_size);
	पूर्ण


	/* set and verअगरy setting the translation address */
	ioग_लिखो64(addr, mmio + xlat_reg);
	reg_val = ioपढ़ो64(mmio + xlat_reg);
	अगर (reg_val != addr) अणु
		ioग_लिखो64(0, mmio + xlat_reg);
		वापस -EIO;
	पूर्ण

	dev_dbg(&ntb->pdev->dev, "BAR %d IMXBASE: %#Lx\n", bar, reg_val);

	/* set and verअगरy setting the limit */
	ioग_लिखो64(limit, mmio + limit_reg);
	reg_val = ioपढ़ो64(mmio + limit_reg);
	अगर (reg_val != limit) अणु
		ioग_लिखो64(base, mmio + limit_reg);
		ioग_लिखो64(0, mmio + xlat_reg);
		वापस -EIO;
	पूर्ण

	dev_dbg(&ntb->pdev->dev, "BAR %d IMXLMT: %#Lx\n", bar, reg_val);

	अगर (ndev->hwerr_flags & NTB_HWERR_BAR_ALIGN) अणु
		idx_reg = ndev->xlat_reg->bar2_idx + (idx * 0x2);
		ioग_लिखो16(base_idx, mmio + idx_reg);
		reg_val16 = ioपढ़ो16(mmio + idx_reg);
		अगर (reg_val16 != base_idx) अणु
			ioग_लिखो64(base, mmio + limit_reg);
			ioग_लिखो64(0, mmio + xlat_reg);
			ioग_लिखो16(0, mmio + idx_reg);
			वापस -EIO;
		पूर्ण
		dev_dbg(&ntb->pdev->dev, "BAR %d IMBASEIDX: %#x\n", bar, reg_val16);
	पूर्ण


	वापस 0;
पूर्ण

अटल पूर्णांक पूर्णांकel_ntb4_link_enable(काष्ठा ntb_dev *ntb,
		क्रमागत ntb_speed max_speed, क्रमागत ntb_width max_width)
अणु
	काष्ठा पूर्णांकel_ntb_dev *ndev;
	u32 ntb_ctl, ppd0;
	u16 lnkctl;

	ndev = container_of(ntb, काष्ठा पूर्णांकel_ntb_dev, ntb);

	dev_dbg(&ntb->pdev->dev,
			"Enabling link with max_speed %d max_width %d\n",
			max_speed, max_width);

	अगर (max_speed != NTB_SPEED_AUTO)
		dev_dbg(&ntb->pdev->dev,
				"ignoring max_speed %d\n", max_speed);
	अगर (max_width != NTB_WIDTH_AUTO)
		dev_dbg(&ntb->pdev->dev,
				"ignoring max_width %d\n", max_width);

	अगर (!(ndev->hwerr_flags & NTB_HWERR_LTR_BAD)) अणु
		u32 ltr;

		/* Setup active snoop LTR values */
		ltr = NTB_LTR_ACTIVE_REQMNT | NTB_LTR_ACTIVE_VAL | NTB_LTR_ACTIVE_LATSCALE;
		/* Setup active non-snoop values */
		ltr = (ltr << NTB_LTR_NS_SHIFT) | ltr;
		ioग_लिखो32(ltr, ndev->self_mmio + GEN4_LTR_ACTIVE_OFFSET);

		/* Setup idle snoop LTR values */
		ltr = NTB_LTR_IDLE_VAL | NTB_LTR_IDLE_LATSCALE | NTB_LTR_IDLE_REQMNT;
		/* Setup idle non-snoop values */
		ltr = (ltr << NTB_LTR_NS_SHIFT) | ltr;
		ioग_लिखो32(ltr, ndev->self_mmio + GEN4_LTR_IDLE_OFFSET);

		/* setup PCIe LTR to active */
		ioग_लिखो8(NTB_LTR_SWSEL_ACTIVE, ndev->self_mmio + GEN4_LTR_SWSEL_OFFSET);
	पूर्ण

	ntb_ctl = NTB_CTL_E2I_BAR23_SNOOP | NTB_CTL_I2E_BAR23_SNOOP;
	ntb_ctl |= NTB_CTL_E2I_BAR45_SNOOP | NTB_CTL_I2E_BAR45_SNOOP;
	ioग_लिखो32(ntb_ctl, ndev->self_mmio + ndev->reg->ntb_ctl);

	lnkctl = ioपढ़ो16(ndev->self_mmio + GEN4_LINK_CTRL_OFFSET);
	lnkctl &= ~GEN4_LINK_CTRL_LINK_DISABLE;
	ioग_लिखो16(lnkctl, ndev->self_mmio + GEN4_LINK_CTRL_OFFSET);

	/* start link training in PPD0 */
	ppd0 = ioपढ़ो32(ndev->self_mmio + GEN4_PPD0_OFFSET);
	ppd0 |= GEN4_PPD_LINKTRN;
	ioग_लिखो32(ppd0, ndev->self_mmio + GEN4_PPD0_OFFSET);

	/* make sure link training has started */
	ppd0 = ioपढ़ो32(ndev->self_mmio + GEN4_PPD0_OFFSET);
	अगर (!(ppd0 & GEN4_PPD_LINKTRN)) अणु
		dev_warn(&ntb->pdev->dev, "Link is not training\n");
		वापस -ENXIO;
	पूर्ण

	ndev->dev_up = 1;

	वापस 0;
पूर्ण

अटल पूर्णांक पूर्णांकel_ntb4_link_disable(काष्ठा ntb_dev *ntb)
अणु
	काष्ठा पूर्णांकel_ntb_dev *ndev;
	u32 ntb_cntl;
	u16 lnkctl;

	ndev = container_of(ntb, काष्ठा पूर्णांकel_ntb_dev, ntb);

	dev_dbg(&ntb->pdev->dev, "Disabling link\n");

	/* clear the snoop bits */
	ntb_cntl = ioपढ़ो32(ndev->self_mmio + ndev->reg->ntb_ctl);
	ntb_cntl &= ~(NTB_CTL_E2I_BAR23_SNOOP | NTB_CTL_I2E_BAR23_SNOOP);
	ntb_cntl &= ~(NTB_CTL_E2I_BAR45_SNOOP | NTB_CTL_I2E_BAR45_SNOOP);
	ioग_लिखो32(ntb_cntl, ndev->self_mmio + ndev->reg->ntb_ctl);

	lnkctl = ioपढ़ो16(ndev->self_mmio + GEN4_LINK_CTRL_OFFSET);
	lnkctl |= GEN4_LINK_CTRL_LINK_DISABLE;
	ioग_लिखो16(lnkctl, ndev->self_mmio + GEN4_LINK_CTRL_OFFSET);

	/* set LTR to idle */
	अगर (!(ndev->hwerr_flags & NTB_HWERR_LTR_BAD))
		ioग_लिखो8(NTB_LTR_SWSEL_IDLE, ndev->self_mmio + GEN4_LTR_SWSEL_OFFSET);

	ndev->dev_up = 0;

	वापस 0;
पूर्ण

अटल पूर्णांक पूर्णांकel_ntb4_mw_get_align(काष्ठा ntb_dev *ntb, पूर्णांक pidx, पूर्णांक idx,
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

	अगर (addr_align) अणु
		अगर (ndev->hwerr_flags & NTB_HWERR_BAR_ALIGN)
			*addr_align = pci_resource_len(ndev->ntb.pdev, bar);
		अन्यथा
			*addr_align = PAGE_SIZE;
	पूर्ण

	अगर (size_align)
		*size_align = 1;

	अगर (size_max)
		*size_max = mw_size;

	वापस 0;
पूर्ण

स्थिर काष्ठा ntb_dev_ops पूर्णांकel_ntb4_ops = अणु
	.mw_count		= पूर्णांकel_ntb_mw_count,
	.mw_get_align		= पूर्णांकel_ntb4_mw_get_align,
	.mw_set_trans		= पूर्णांकel_ntb4_mw_set_trans,
	.peer_mw_count		= पूर्णांकel_ntb_peer_mw_count,
	.peer_mw_get_addr	= पूर्णांकel_ntb_peer_mw_get_addr,
	.link_is_up		= पूर्णांकel_ntb_link_is_up,
	.link_enable		= पूर्णांकel_ntb4_link_enable,
	.link_disable		= पूर्णांकel_ntb4_link_disable,
	.db_valid_mask		= पूर्णांकel_ntb_db_valid_mask,
	.db_vector_count	= पूर्णांकel_ntb_db_vector_count,
	.db_vector_mask		= पूर्णांकel_ntb_db_vector_mask,
	.db_पढ़ो		= पूर्णांकel_ntb3_db_पढ़ो,
	.db_clear		= पूर्णांकel_ntb3_db_clear,
	.db_set_mask		= पूर्णांकel_ntb_db_set_mask,
	.db_clear_mask		= पूर्णांकel_ntb_db_clear_mask,
	.peer_db_addr		= पूर्णांकel_ntb3_peer_db_addr,
	.peer_db_set		= पूर्णांकel_ntb3_peer_db_set,
	.spad_is_unsafe		= पूर्णांकel_ntb_spad_is_unsafe,
	.spad_count		= पूर्णांकel_ntb_spad_count,
	.spad_पढ़ो		= पूर्णांकel_ntb_spad_पढ़ो,
	.spad_ग_लिखो		= पूर्णांकel_ntb_spad_ग_लिखो,
	.peer_spad_addr		= पूर्णांकel_ntb_peer_spad_addr,
	.peer_spad_पढ़ो		= पूर्णांकel_ntb_peer_spad_पढ़ो,
	.peer_spad_ग_लिखो	= पूर्णांकel_ntb_peer_spad_ग_लिखो,
पूर्ण;

