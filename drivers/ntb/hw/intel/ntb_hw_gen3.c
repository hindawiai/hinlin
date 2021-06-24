<शैली गुरु>
/*
 * This file is provided under a dual BSD/GPLv2 license.  When using or
 *   redistributing this file, you may करो so under either license.
 *
 *   GPL LICENSE SUMMARY
 *
 *   Copyright(c) 2017 Intel Corporation. All rights reserved.
 *
 *   This program is मुक्त software; you can redistribute it and/or modअगरy
 *   it under the terms of version 2 of the GNU General Public License as
 *   published by the Free Software Foundation.
 *
 *   BSD LICENSE
 *
 *   Copyright(c) 2017 Intel Corporation. All rights reserved.
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
 * Intel PCIe GEN3 NTB Linux driver
 *
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

अटल पूर्णांक gen3_poll_link(काष्ठा पूर्णांकel_ntb_dev *ndev);

अटल स्थिर काष्ठा पूर्णांकel_ntb_reg gen3_reg = अणु
	.poll_link		= gen3_poll_link,
	.link_is_up		= xeon_link_is_up,
	.db_ioपढ़ो		= gen3_db_ioपढ़ो,
	.db_ioग_लिखो		= gen3_db_ioग_लिखो,
	.db_size		= माप(u32),
	.ntb_ctl		= GEN3_NTBCNTL_OFFSET,
	.mw_bar			= अणु2, 4पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा पूर्णांकel_ntb_alt_reg gen3_pri_reg = अणु
	.db_bell		= GEN3_EM_DOORBELL_OFFSET,
	.db_clear		= GEN3_IM_INT_STATUS_OFFSET,
	.db_mask		= GEN3_IM_INT_DISABLE_OFFSET,
	.spad			= GEN3_IM_SPAD_OFFSET,
पूर्ण;

अटल स्थिर काष्ठा पूर्णांकel_ntb_alt_reg gen3_b2b_reg = अणु
	.db_bell		= GEN3_IM_DOORBELL_OFFSET,
	.db_clear		= GEN3_EM_INT_STATUS_OFFSET,
	.db_mask		= GEN3_EM_INT_DISABLE_OFFSET,
	.spad			= GEN3_B2B_SPAD_OFFSET,
पूर्ण;

अटल स्थिर काष्ठा पूर्णांकel_ntb_xlat_reg gen3_sec_xlat = अणु
/*	.bar0_base		= GEN3_EMBAR0_OFFSET, */
	.bar2_limit		= GEN3_IMBAR1XLMT_OFFSET,
	.bar2_xlat		= GEN3_IMBAR1XBASE_OFFSET,
पूर्ण;

अटल पूर्णांक gen3_poll_link(काष्ठा पूर्णांकel_ntb_dev *ndev)
अणु
	u16 reg_val;
	पूर्णांक rc;

	ndev->reg->db_ioग_लिखो(ndev->db_link_mask,
			      ndev->self_mmio +
			      ndev->self_reg->db_clear);

	rc = pci_पढ़ो_config_word(ndev->ntb.pdev,
				  GEN3_LINK_STATUS_OFFSET, &reg_val);
	अगर (rc)
		वापस 0;

	अगर (reg_val == ndev->lnk_sta)
		वापस 0;

	ndev->lnk_sta = reg_val;

	वापस 1;
पूर्ण

अटल पूर्णांक gen3_init_isr(काष्ठा पूर्णांकel_ntb_dev *ndev)
अणु
	पूर्णांक i;

	/*
	 * The MSIX vectors and the पूर्णांकerrupt status bits are not lined up
	 * on Skylake. By शेष the link status bit is bit 32, however it
	 * is by शेष MSIX vector0. We need to fixup to line them up.
	 * The vectors at reset is 1-32,0. We need to reprogram to 0-32.
	 */

	क्रम (i = 0; i < GEN3_DB_MSIX_VECTOR_COUNT; i++)
		ioग_लिखो8(i, ndev->self_mmio + GEN3_INTVEC_OFFSET + i);

	/* move link status करोwn one as workaround */
	अगर (ndev->hwerr_flags & NTB_HWERR_MSIX_VECTOR32_BAD) अणु
		ioग_लिखो8(GEN3_DB_MSIX_VECTOR_COUNT - 2,
			 ndev->self_mmio + GEN3_INTVEC_OFFSET +
			 (GEN3_DB_MSIX_VECTOR_COUNT - 1));
	पूर्ण

	वापस ndev_init_isr(ndev, GEN3_DB_MSIX_VECTOR_COUNT,
			     GEN3_DB_MSIX_VECTOR_COUNT,
			     GEN3_DB_MSIX_VECTOR_SHIFT,
			     GEN3_DB_TOTAL_SHIFT);
पूर्ण

अटल पूर्णांक gen3_setup_b2b_mw(काष्ठा पूर्णांकel_ntb_dev *ndev,
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
	ioग_लिखो64(bar_addr, mmio + GEN3_IMBAR1XLMT_OFFSET);
	bar_addr = ioपढ़ो64(mmio + GEN3_IMBAR1XLMT_OFFSET);
	dev_dbg(&pdev->dev, "IMBAR1XLMT %#018llx\n", bar_addr);

	bar_addr = addr->bar4_addr64;
	ioग_लिखो64(bar_addr, mmio + GEN3_IMBAR2XLMT_OFFSET);
	bar_addr = ioपढ़ो64(mmio + GEN3_IMBAR2XLMT_OFFSET);
	dev_dbg(&pdev->dev, "IMBAR2XLMT %#018llx\n", bar_addr);

	/* zero incoming translation addrs */
	ioग_लिखो64(0, mmio + GEN3_IMBAR1XBASE_OFFSET);
	ioग_लिखो64(0, mmio + GEN3_IMBAR2XBASE_OFFSET);

	ndev->peer_mmio = ndev->self_mmio;

	वापस 0;
पूर्ण

अटल पूर्णांक gen3_init_ntb(काष्ठा पूर्णांकel_ntb_dev *ndev)
अणु
	पूर्णांक rc;


	ndev->mw_count = XEON_MW_COUNT;
	ndev->spad_count = GEN3_SPAD_COUNT;
	ndev->db_count = GEN3_DB_COUNT;
	ndev->db_link_mask = GEN3_DB_LINK_BIT;

	/* DB fixup क्रम using 31 right now */
	अगर (ndev->hwerr_flags & NTB_HWERR_MSIX_VECTOR32_BAD)
		ndev->db_link_mask |= BIT_ULL(31);

	चयन (ndev->ntb.topo) अणु
	हाल NTB_TOPO_B2B_USD:
	हाल NTB_TOPO_B2B_DSD:
		ndev->self_reg = &gen3_pri_reg;
		ndev->peer_reg = &gen3_b2b_reg;
		ndev->xlat_reg = &gen3_sec_xlat;

		अगर (ndev->ntb.topo == NTB_TOPO_B2B_USD) अणु
			rc = gen3_setup_b2b_mw(ndev,
					      &xeon_b2b_dsd_addr,
					      &xeon_b2b_usd_addr);
		पूर्ण अन्यथा अणु
			rc = gen3_setup_b2b_mw(ndev,
					      &xeon_b2b_usd_addr,
					      &xeon_b2b_dsd_addr);
		पूर्ण

		अगर (rc)
			वापस rc;

		/* Enable Bus Master and Memory Space on the secondary side */
		ioग_लिखो16(PCI_COMMAND_MEMORY | PCI_COMMAND_MASTER,
			  ndev->self_mmio + GEN3_SPCICMD_OFFSET);

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

पूर्णांक gen3_init_dev(काष्ठा पूर्णांकel_ntb_dev *ndev)
अणु
	काष्ठा pci_dev *pdev;
	u8 ppd;
	पूर्णांक rc;

	pdev = ndev->ntb.pdev;

	ndev->reg = &gen3_reg;

	rc = pci_पढ़ो_config_byte(pdev, XEON_PPD_OFFSET, &ppd);
	अगर (rc)
		वापस -EIO;

	ndev->ntb.topo = xeon_ppd_topo(ndev, ppd);
	dev_dbg(&pdev->dev, "ppd %#x topo %s\n", ppd,
		ntb_topo_string(ndev->ntb.topo));
	अगर (ndev->ntb.topo == NTB_TOPO_NONE)
		वापस -EINVAL;

	ndev->hwerr_flags |= NTB_HWERR_MSIX_VECTOR32_BAD;

	rc = gen3_init_ntb(ndev);
	अगर (rc)
		वापस rc;

	वापस gen3_init_isr(ndev);
पूर्ण

sमाप_प्रकार ndev_ntb3_debugfs_पढ़ो(काष्ठा file *filp, अक्षर __user *ubuf,
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
			 "LNK STA -\t\t%#06x\n", ndev->lnk_sta);

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

	u.v64 = ndev_db_पढ़ो(ndev, mmio + ndev->self_reg->db_bell);
	off += scnम_लिखो(buf + off, buf_size - off,
			 "Doorbell Bell -\t\t%#llx\n", u.v64);

	off += scnम_लिखो(buf + off, buf_size - off,
			 "\nNTB Incoming XLAT:\n");

	u.v64 = ioपढ़ो64(mmio + GEN3_IMBAR1XBASE_OFFSET);
	off += scnम_लिखो(buf + off, buf_size - off,
			 "IMBAR1XBASE -\t\t%#018llx\n", u.v64);

	u.v64 = ioपढ़ो64(mmio + GEN3_IMBAR2XBASE_OFFSET);
	off += scnम_लिखो(buf + off, buf_size - off,
			 "IMBAR2XBASE -\t\t%#018llx\n", u.v64);

	u.v64 = ioपढ़ो64(mmio + GEN3_IMBAR1XLMT_OFFSET);
	off += scnम_लिखो(buf + off, buf_size - off,
			 "IMBAR1XLMT -\t\t\t%#018llx\n", u.v64);

	u.v64 = ioपढ़ो64(mmio + GEN3_IMBAR2XLMT_OFFSET);
	off += scnम_लिखो(buf + off, buf_size - off,
			 "IMBAR2XLMT -\t\t\t%#018llx\n", u.v64);

	अगर (ntb_topo_is_b2b(ndev->ntb.topo)) अणु
		off += scnम_लिखो(buf + off, buf_size - off,
				 "\nNTB Outgoing B2B XLAT:\n");

		u.v64 = ioपढ़ो64(mmio + GEN3_EMBAR1XBASE_OFFSET);
		off += scnम_लिखो(buf + off, buf_size - off,
				 "EMBAR1XBASE -\t\t%#018llx\n", u.v64);

		u.v64 = ioपढ़ो64(mmio + GEN3_EMBAR2XBASE_OFFSET);
		off += scnम_लिखो(buf + off, buf_size - off,
				 "EMBAR2XBASE -\t\t%#018llx\n", u.v64);

		u.v64 = ioपढ़ो64(mmio + GEN3_EMBAR1XLMT_OFFSET);
		off += scnम_लिखो(buf + off, buf_size - off,
				 "EMBAR1XLMT -\t\t%#018llx\n", u.v64);

		u.v64 = ioपढ़ो64(mmio + GEN3_EMBAR2XLMT_OFFSET);
		off += scnम_लिखो(buf + off, buf_size - off,
				 "EMBAR2XLMT -\t\t%#018llx\n", u.v64);

		off += scnम_लिखो(buf + off, buf_size - off,
				 "\nNTB Secondary BAR:\n");

		u.v64 = ioपढ़ो64(mmio + GEN3_EMBAR0_OFFSET);
		off += scnम_लिखो(buf + off, buf_size - off,
				 "EMBAR0 -\t\t%#018llx\n", u.v64);

		u.v64 = ioपढ़ो64(mmio + GEN3_EMBAR1_OFFSET);
		off += scnम_लिखो(buf + off, buf_size - off,
				 "EMBAR1 -\t\t%#018llx\n", u.v64);

		u.v64 = ioपढ़ो64(mmio + GEN3_EMBAR2_OFFSET);
		off += scnम_लिखो(buf + off, buf_size - off,
				 "EMBAR2 -\t\t%#018llx\n", u.v64);
	पूर्ण

	off += scnम_लिखो(buf + off, buf_size - off,
			 "\nNTB Statistics:\n");

	u.v16 = ioपढ़ो16(mmio + GEN3_USMEMMISS_OFFSET);
	off += scnम_लिखो(buf + off, buf_size - off,
			 "Upstream Memory Miss -\t%u\n", u.v16);

	off += scnम_लिखो(buf + off, buf_size - off,
			 "\nNTB Hardware Errors:\n");

	अगर (!pci_पढ़ो_config_word(ndev->ntb.pdev,
				  GEN3_DEVSTS_OFFSET, &u.v16))
		off += scnम_लिखो(buf + off, buf_size - off,
				 "DEVSTS -\t\t%#06x\n", u.v16);

	अगर (!pci_पढ़ो_config_word(ndev->ntb.pdev,
				  GEN3_LINK_STATUS_OFFSET, &u.v16))
		off += scnम_लिखो(buf + off, buf_size - off,
				 "LNKSTS -\t\t%#06x\n", u.v16);

	अगर (!pci_पढ़ो_config_dword(ndev->ntb.pdev,
				   GEN3_UNCERRSTS_OFFSET, &u.v32))
		off += scnम_लिखो(buf + off, buf_size - off,
				 "UNCERRSTS -\t\t%#06x\n", u.v32);

	अगर (!pci_पढ़ो_config_dword(ndev->ntb.pdev,
				   GEN3_CORERRSTS_OFFSET, &u.v32))
		off += scnम_लिखो(buf + off, buf_size - off,
				 "CORERRSTS -\t\t%#06x\n", u.v32);

	ret = simple_पढ़ो_from_buffer(ubuf, count, offp, buf, off);
	kमुक्त(buf);
	वापस ret;
पूर्ण

पूर्णांक पूर्णांकel_ntb3_link_enable(काष्ठा ntb_dev *ntb, क्रमागत ntb_speed max_speed,
		क्रमागत ntb_width max_width)
अणु
	काष्ठा पूर्णांकel_ntb_dev *ndev;
	u32 ntb_ctl;

	ndev = container_of(ntb, काष्ठा पूर्णांकel_ntb_dev, ntb);

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
	ioग_लिखो32(ntb_ctl, ndev->self_mmio + ndev->reg->ntb_ctl);

	वापस 0;
पूर्ण
अटल पूर्णांक पूर्णांकel_ntb3_mw_set_trans(काष्ठा ntb_dev *ntb, पूर्णांक pidx, पूर्णांक idx,
				   dma_addr_t addr, resource_माप_प्रकार size)
अणु
	काष्ठा पूर्णांकel_ntb_dev *ndev = ntb_ndev(ntb);
	अचिन्हित दीर्घ xlat_reg, limit_reg;
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
	xlat_reg = ndev->xlat_reg->bar2_xlat + (idx * 0x10);
	limit_reg = ndev->xlat_reg->bar2_limit + (idx * 0x10);
	base = pci_resource_start(ndev->ntb.pdev, bar);

	/* Set the limit अगर supported, अगर size is not mw_size */
	अगर (limit_reg && size != mw_size)
		limit = base + size;
	अन्यथा
		limit = base + mw_size;

	/* set and verअगरy setting the translation address */
	ioग_लिखो64(addr, mmio + xlat_reg);
	reg_val = ioपढ़ो64(mmio + xlat_reg);
	अगर (reg_val != addr) अणु
		ioग_लिखो64(0, mmio + xlat_reg);
		वापस -EIO;
	पूर्ण

	dev_dbg(&ntb->pdev->dev, "BAR %d IMBARXBASE: %#Lx\n", bar, reg_val);

	/* set and verअगरy setting the limit */
	ioग_लिखो64(limit, mmio + limit_reg);
	reg_val = ioपढ़ो64(mmio + limit_reg);
	अगर (reg_val != limit) अणु
		ioग_लिखो64(base, mmio + limit_reg);
		ioग_लिखो64(0, mmio + xlat_reg);
		वापस -EIO;
	पूर्ण

	dev_dbg(&ntb->pdev->dev, "BAR %d IMBARXLMT: %#Lx\n", bar, reg_val);

	/* setup the EP */
	limit_reg = ndev->xlat_reg->bar2_limit + (idx * 0x10) + 0x4000;
	base = ioपढ़ो64(mmio + GEN3_EMBAR1_OFFSET + (8 * idx));
	base &= ~0xf;

	अगर (limit_reg && size != mw_size)
		limit = base + size;
	अन्यथा
		limit = base + mw_size;

	/* set and verअगरy setting the limit */
	ioग_लिखो64(limit, mmio + limit_reg);
	reg_val = ioपढ़ो64(mmio + limit_reg);
	अगर (reg_val != limit) अणु
		ioग_लिखो64(base, mmio + limit_reg);
		ioग_लिखो64(0, mmio + xlat_reg);
		वापस -EIO;
	पूर्ण

	dev_dbg(&ntb->pdev->dev, "BAR %d EMBARXLMT: %#Lx\n", bar, reg_val);

	वापस 0;
पूर्ण

पूर्णांक पूर्णांकel_ntb3_peer_db_addr(काष्ठा ntb_dev *ntb, phys_addr_t *db_addr,
				   resource_माप_प्रकार *db_size,
				   u64 *db_data, पूर्णांक db_bit)
अणु
	phys_addr_t db_addr_base;
	काष्ठा पूर्णांकel_ntb_dev *ndev = ntb_ndev(ntb);

	अगर (unlikely(db_bit >= BITS_PER_LONG_LONG))
		वापस -EINVAL;

	अगर (unlikely(BIT_ULL(db_bit) & ~ntb_ndev(ntb)->db_valid_mask))
		वापस -EINVAL;

	ndev_db_addr(ndev, &db_addr_base, db_size, ndev->peer_addr,
				ndev->peer_reg->db_bell);

	अगर (db_addr) अणु
		*db_addr = db_addr_base + (db_bit * 4);
		dev_dbg(&ndev->ntb.pdev->dev, "Peer db addr %llx db bit %d\n",
				*db_addr, db_bit);
	पूर्ण

	अगर (db_data) अणु
		*db_data = 1;
		dev_dbg(&ndev->ntb.pdev->dev, "Peer db data %llx db bit %d\n",
				*db_data, db_bit);
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक पूर्णांकel_ntb3_peer_db_set(काष्ठा ntb_dev *ntb, u64 db_bits)
अणु
	काष्ठा पूर्णांकel_ntb_dev *ndev = ntb_ndev(ntb);
	पूर्णांक bit;

	अगर (db_bits & ~ndev->db_valid_mask)
		वापस -EINVAL;

	जबतक (db_bits) अणु
		bit = __ffs(db_bits);
		ioग_लिखो32(1, ndev->peer_mmio +
				ndev->peer_reg->db_bell + (bit * 4));
		db_bits &= db_bits - 1;
	पूर्ण

	वापस 0;
पूर्ण

u64 पूर्णांकel_ntb3_db_पढ़ो(काष्ठा ntb_dev *ntb)
अणु
	काष्ठा पूर्णांकel_ntb_dev *ndev = ntb_ndev(ntb);

	वापस ndev_db_पढ़ो(ndev,
			    ndev->self_mmio +
			    ndev->self_reg->db_clear);
पूर्ण

पूर्णांक पूर्णांकel_ntb3_db_clear(काष्ठा ntb_dev *ntb, u64 db_bits)
अणु
	काष्ठा पूर्णांकel_ntb_dev *ndev = ntb_ndev(ntb);

	वापस ndev_db_ग_लिखो(ndev, db_bits,
			     ndev->self_mmio +
			     ndev->self_reg->db_clear);
पूर्ण

स्थिर काष्ठा ntb_dev_ops पूर्णांकel_ntb3_ops = अणु
	.mw_count		= पूर्णांकel_ntb_mw_count,
	.mw_get_align		= पूर्णांकel_ntb_mw_get_align,
	.mw_set_trans		= पूर्णांकel_ntb3_mw_set_trans,
	.peer_mw_count		= पूर्णांकel_ntb_peer_mw_count,
	.peer_mw_get_addr	= पूर्णांकel_ntb_peer_mw_get_addr,
	.link_is_up		= पूर्णांकel_ntb_link_is_up,
	.link_enable		= पूर्णांकel_ntb3_link_enable,
	.link_disable		= पूर्णांकel_ntb_link_disable,
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

