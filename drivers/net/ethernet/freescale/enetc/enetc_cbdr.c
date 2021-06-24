<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0+ OR BSD-3-Clause)
/* Copyright 2017-2019 NXP */

#समावेश "enetc.h"

पूर्णांक enetc_setup_cbdr(काष्ठा device *dev, काष्ठा enetc_hw *hw, पूर्णांक bd_count,
		     काष्ठा enetc_cbdr *cbdr)
अणु
	पूर्णांक size = bd_count * माप(काष्ठा enetc_cbd);

	cbdr->bd_base = dma_alloc_coherent(dev, size, &cbdr->bd_dma_base,
					   GFP_KERNEL);
	अगर (!cbdr->bd_base)
		वापस -ENOMEM;

	/* h/w requires 128B alignment */
	अगर (!IS_ALIGNED(cbdr->bd_dma_base, 128)) अणु
		dma_मुक्त_coherent(dev, size, cbdr->bd_base,
				  cbdr->bd_dma_base);
		वापस -EINVAL;
	पूर्ण

	cbdr->next_to_clean = 0;
	cbdr->next_to_use = 0;
	cbdr->dma_dev = dev;
	cbdr->bd_count = bd_count;

	cbdr->pir = hw->reg + ENETC_SICBDRPIR;
	cbdr->cir = hw->reg + ENETC_SICBDRCIR;
	cbdr->mr = hw->reg + ENETC_SICBDRMR;

	/* set CBDR cache attributes */
	enetc_wr(hw, ENETC_SICAR2,
		 ENETC_SICAR_RD_COHERENT | ENETC_SICAR_WR_COHERENT);

	enetc_wr(hw, ENETC_SICBDRBAR0, lower_32_bits(cbdr->bd_dma_base));
	enetc_wr(hw, ENETC_SICBDRBAR1, upper_32_bits(cbdr->bd_dma_base));
	enetc_wr(hw, ENETC_SICBDRLENR, ENETC_RTBLENR_LEN(cbdr->bd_count));

	enetc_wr_reg(cbdr->pir, cbdr->next_to_clean);
	enetc_wr_reg(cbdr->cir, cbdr->next_to_use);
	/* enable ring */
	enetc_wr_reg(cbdr->mr, BIT(31));

	वापस 0;
पूर्ण

व्योम enetc_tearकरोwn_cbdr(काष्ठा enetc_cbdr *cbdr)
अणु
	पूर्णांक size = cbdr->bd_count * माप(काष्ठा enetc_cbd);

	/* disable ring */
	enetc_wr_reg(cbdr->mr, 0);

	dma_मुक्त_coherent(cbdr->dma_dev, size, cbdr->bd_base,
			  cbdr->bd_dma_base);
	cbdr->bd_base = शून्य;
	cbdr->dma_dev = शून्य;
पूर्ण

अटल व्योम enetc_clean_cbdr(काष्ठा enetc_cbdr *ring)
अणु
	काष्ठा enetc_cbd *dest_cbd;
	पूर्णांक i, status;

	i = ring->next_to_clean;

	जबतक (enetc_rd_reg(ring->cir) != i) अणु
		dest_cbd = ENETC_CBD(*ring, i);
		status = dest_cbd->status_flags & ENETC_CBD_STATUS_MASK;
		अगर (status)
			dev_warn(ring->dma_dev, "CMD err %04x for cmd %04x\n",
				 status, dest_cbd->cmd);

		स_रखो(dest_cbd, 0, माप(*dest_cbd));

		i = (i + 1) % ring->bd_count;
	पूर्ण

	ring->next_to_clean = i;
पूर्ण

अटल पूर्णांक enetc_cbd_unused(काष्ठा enetc_cbdr *r)
अणु
	वापस (r->next_to_clean - r->next_to_use - 1 + r->bd_count) %
		r->bd_count;
पूर्ण

पूर्णांक enetc_send_cmd(काष्ठा enetc_si *si, काष्ठा enetc_cbd *cbd)
अणु
	काष्ठा enetc_cbdr *ring = &si->cbd_ring;
	पूर्णांक समयout = ENETC_CBDR_TIMEOUT;
	काष्ठा enetc_cbd *dest_cbd;
	पूर्णांक i;

	अगर (unlikely(!ring->bd_base))
		वापस -EIO;

	अगर (unlikely(!enetc_cbd_unused(ring)))
		enetc_clean_cbdr(ring);

	i = ring->next_to_use;
	dest_cbd = ENETC_CBD(*ring, i);

	/* copy command to the ring */
	*dest_cbd = *cbd;
	i = (i + 1) % ring->bd_count;

	ring->next_to_use = i;
	/* let H/W know BD ring has been updated */
	enetc_wr_reg(ring->pir, i);

	करो अणु
		अगर (enetc_rd_reg(ring->cir) == i)
			अवरोध;
		udelay(10); /* cannot sleep, rtnl_lock() */
		समयout -= 10;
	पूर्ण जबतक (समयout);

	अगर (!समयout)
		वापस -EBUSY;

	/* CBD may ग_लिखोback data, feedback up level */
	*cbd = *dest_cbd;

	enetc_clean_cbdr(ring);

	वापस 0;
पूर्ण

पूर्णांक enetc_clear_mac_flt_entry(काष्ठा enetc_si *si, पूर्णांक index)
अणु
	काष्ठा enetc_cbd cbd;

	स_रखो(&cbd, 0, माप(cbd));

	cbd.cls = 1;
	cbd.status_flags = ENETC_CBD_FLAGS_SF;
	cbd.index = cpu_to_le16(index);

	वापस enetc_send_cmd(si, &cbd);
पूर्ण

पूर्णांक enetc_set_mac_flt_entry(काष्ठा enetc_si *si, पूर्णांक index,
			    अक्षर *mac_addr, पूर्णांक si_map)
अणु
	काष्ठा enetc_cbd cbd;
	u32 upper;
	u16 lower;

	स_रखो(&cbd, 0, माप(cbd));

	/* fill up the "set" descriptor */
	cbd.cls = 1;
	cbd.status_flags = ENETC_CBD_FLAGS_SF;
	cbd.index = cpu_to_le16(index);
	cbd.opt[3] = cpu_to_le32(si_map);
	/* enable entry */
	cbd.opt[0] = cpu_to_le32(BIT(31));

	upper = *(स्थिर u32 *)mac_addr;
	lower = *(स्थिर u16 *)(mac_addr + 4);
	cbd.addr[0] = cpu_to_le32(upper);
	cbd.addr[1] = cpu_to_le32(lower);

	वापस enetc_send_cmd(si, &cbd);
पूर्ण

#घोषणा RFSE_ALIGN	64
/* Set entry in RFS table */
पूर्णांक enetc_set_fs_entry(काष्ठा enetc_si *si, काष्ठा enetc_cmd_rfse *rfse,
		       पूर्णांक index)
अणु
	काष्ठा enetc_cbdr *ring = &si->cbd_ring;
	काष्ठा enetc_cbd cbd = अणु.cmd = 0पूर्ण;
	dma_addr_t dma, dma_align;
	व्योम *पंचांगp, *पंचांगp_align;
	पूर्णांक err;

	/* fill up the "set" descriptor */
	cbd.cmd = 0;
	cbd.cls = 4;
	cbd.index = cpu_to_le16(index);
	cbd.length = cpu_to_le16(माप(*rfse));
	cbd.opt[3] = cpu_to_le32(0); /* SI */

	पंचांगp = dma_alloc_coherent(ring->dma_dev, माप(*rfse) + RFSE_ALIGN,
				 &dma, GFP_KERNEL);
	अगर (!पंचांगp) अणु
		dev_err(ring->dma_dev, "DMA mapping of RFS entry failed!\n");
		वापस -ENOMEM;
	पूर्ण

	dma_align = ALIGN(dma, RFSE_ALIGN);
	पंचांगp_align = PTR_ALIGN(पंचांगp, RFSE_ALIGN);
	स_नकल(पंचांगp_align, rfse, माप(*rfse));

	cbd.addr[0] = cpu_to_le32(lower_32_bits(dma_align));
	cbd.addr[1] = cpu_to_le32(upper_32_bits(dma_align));

	err = enetc_send_cmd(si, &cbd);
	अगर (err)
		dev_err(ring->dma_dev, "FS entry add failed (%d)!", err);

	dma_मुक्त_coherent(ring->dma_dev, माप(*rfse) + RFSE_ALIGN,
			  पंचांगp, dma);

	वापस err;
पूर्ण

#घोषणा RSSE_ALIGN	64
अटल पूर्णांक enetc_cmd_rss_table(काष्ठा enetc_si *si, u32 *table, पूर्णांक count,
			       bool पढ़ो)
अणु
	काष्ठा enetc_cbdr *ring = &si->cbd_ring;
	काष्ठा enetc_cbd cbd = अणु.cmd = 0पूर्ण;
	dma_addr_t dma, dma_align;
	u8 *पंचांगp, *पंचांगp_align;
	पूर्णांक err, i;

	अगर (count < RSSE_ALIGN)
		/* HW only takes in a full 64 entry table */
		वापस -EINVAL;

	पंचांगp = dma_alloc_coherent(ring->dma_dev, count + RSSE_ALIGN,
				 &dma, GFP_KERNEL);
	अगर (!पंचांगp) अणु
		dev_err(ring->dma_dev, "DMA mapping of RSS table failed!\n");
		वापस -ENOMEM;
	पूर्ण
	dma_align = ALIGN(dma, RSSE_ALIGN);
	पंचांगp_align = PTR_ALIGN(पंचांगp, RSSE_ALIGN);

	अगर (!पढ़ो)
		क्रम (i = 0; i < count; i++)
			पंचांगp_align[i] = (u8)(table[i]);

	/* fill up the descriptor */
	cbd.cmd = पढ़ो ? 2 : 1;
	cbd.cls = 3;
	cbd.length = cpu_to_le16(count);

	cbd.addr[0] = cpu_to_le32(lower_32_bits(dma_align));
	cbd.addr[1] = cpu_to_le32(upper_32_bits(dma_align));

	err = enetc_send_cmd(si, &cbd);
	अगर (err)
		dev_err(ring->dma_dev, "RSS cmd failed (%d)!", err);

	अगर (पढ़ो)
		क्रम (i = 0; i < count; i++)
			table[i] = पंचांगp_align[i];

	dma_मुक्त_coherent(ring->dma_dev, count + RSSE_ALIGN, पंचांगp, dma);

	वापस err;
पूर्ण

/* Get RSS table */
पूर्णांक enetc_get_rss_table(काष्ठा enetc_si *si, u32 *table, पूर्णांक count)
अणु
	वापस enetc_cmd_rss_table(si, table, count, true);
पूर्ण

/* Set RSS table */
पूर्णांक enetc_set_rss_table(काष्ठा enetc_si *si, स्थिर u32 *table, पूर्णांक count)
अणु
	वापस enetc_cmd_rss_table(si, (u32 *)table, count, false);
पूर्ण
