<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0 OR MIT)
// Copyright (c) 2017 Synopsys, Inc. and/or its affiliates.
// sपंचांगmac Support क्रम 5.xx Ethernet QoS cores

#समावेश <linux/bitops.h>
#समावेश <linux/iopoll.h>
#समावेश "common.h"
#समावेश "dwmac4.h"
#समावेश "dwmac5.h"
#समावेश "stmmac.h"
#समावेश "stmmac_ptp.h"

काष्ठा dwmac5_error_desc अणु
	bool valid;
	स्थिर अक्षर *desc;
	स्थिर अक्षर *detailed_desc;
पूर्ण;

#घोषणा STAT_OFF(field)		दुरत्व(काष्ठा sपंचांगmac_safety_stats, field)

अटल व्योम dwmac5_log_error(काष्ठा net_device *ndev, u32 value, bool corr,
		स्थिर अक्षर *module_name, स्थिर काष्ठा dwmac5_error_desc *desc,
		अचिन्हित दीर्घ field_offset, काष्ठा sपंचांगmac_safety_stats *stats)
अणु
	अचिन्हित दीर्घ loc, mask;
	u8 *bptr = (u8 *)stats;
	अचिन्हित दीर्घ *ptr;

	ptr = (अचिन्हित दीर्घ *)(bptr + field_offset);

	mask = value;
	क्रम_each_set_bit(loc, &mask, 32) अणु
		netdev_err(ndev, "Found %s error in %s: '%s: %s'\n", corr ?
				"correctable" : "uncorrectable", module_name,
				desc[loc].desc, desc[loc].detailed_desc);

		/* Update counters */
		ptr[loc]++;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा dwmac5_error_desc dwmac5_mac_errors[32]= अणु
	अणु true, "ATPES", "Application Transmit Interface Parity Check Error" पूर्ण,
	अणु true, "TPES", "TSO Data Path Parity Check Error" पूर्ण,
	अणु true, "RDPES", "Read Descriptor Parity Check Error" पूर्ण,
	अणु true, "MPES", "MTL Data Path Parity Check Error" पूर्ण,
	अणु true, "MTSPES", "MTL TX Status Data Path Parity Check Error" पूर्ण,
	अणु true, "ARPES", "Application Receive Interface Data Path Parity Check Error" पूर्ण,
	अणु true, "CWPES", "CSR Write Data Path Parity Check Error" पूर्ण,
	अणु true, "ASRPES", "AXI Slave Read Data Path Parity Check Error" पूर्ण,
	अणु true, "TTES", "TX FSM Timeout Error" पूर्ण,
	अणु true, "RTES", "RX FSM Timeout Error" पूर्ण,
	अणु true, "CTES", "CSR FSM Timeout Error" पूर्ण,
	अणु true, "ATES", "APP FSM Timeout Error" पूर्ण,
	अणु true, "PTES", "PTP FSM Timeout Error" पूर्ण,
	अणु true, "T125ES", "TX125 FSM Timeout Error" पूर्ण,
	अणु true, "R125ES", "RX125 FSM Timeout Error" पूर्ण,
	अणु true, "RVCTES", "REV MDC FSM Timeout Error" पूर्ण,
	अणु true, "MSTTES", "Master Read/Write Timeout Error" पूर्ण,
	अणु true, "SLVTES", "Slave Read/Write Timeout Error" पूर्ण,
	अणु true, "ATITES", "Application Timeout on ATI Interface Error" पूर्ण,
	अणु true, "ARITES", "Application Timeout on ARI Interface Error" पूर्ण,
	अणु false, "UNKNOWN", "Unknown Error" पूर्ण, /* 20 */
	अणु false, "UNKNOWN", "Unknown Error" पूर्ण, /* 21 */
	अणु false, "UNKNOWN", "Unknown Error" पूर्ण, /* 22 */
	अणु false, "UNKNOWN", "Unknown Error" पूर्ण, /* 23 */
	अणु true, "FSMPES", "FSM State Parity Error" पूर्ण,
	अणु false, "UNKNOWN", "Unknown Error" पूर्ण, /* 25 */
	अणु false, "UNKNOWN", "Unknown Error" पूर्ण, /* 26 */
	अणु false, "UNKNOWN", "Unknown Error" पूर्ण, /* 27 */
	अणु false, "UNKNOWN", "Unknown Error" पूर्ण, /* 28 */
	अणु false, "UNKNOWN", "Unknown Error" पूर्ण, /* 29 */
	अणु false, "UNKNOWN", "Unknown Error" पूर्ण, /* 30 */
	अणु false, "UNKNOWN", "Unknown Error" पूर्ण, /* 31 */
पूर्ण;

अटल व्योम dwmac5_handle_mac_err(काष्ठा net_device *ndev,
		व्योम __iomem *ioaddr, bool correctable,
		काष्ठा sपंचांगmac_safety_stats *stats)
अणु
	u32 value;

	value = पढ़ोl(ioaddr + MAC_DPP_FSM_INT_STATUS);
	ग_लिखोl(value, ioaddr + MAC_DPP_FSM_INT_STATUS);

	dwmac5_log_error(ndev, value, correctable, "MAC", dwmac5_mac_errors,
			STAT_OFF(mac_errors), stats);
पूर्ण

अटल स्थिर काष्ठा dwmac5_error_desc dwmac5_mtl_errors[32]= अणु
	अणु true, "TXCES", "MTL TX Memory Error" पूर्ण,
	अणु true, "TXAMS", "MTL TX Memory Address Mismatch Error" पूर्ण,
	अणु true, "TXUES", "MTL TX Memory Error" पूर्ण,
	अणु false, "UNKNOWN", "Unknown Error" पूर्ण, /* 3 */
	अणु true, "RXCES", "MTL RX Memory Error" पूर्ण,
	अणु true, "RXAMS", "MTL RX Memory Address Mismatch Error" पूर्ण,
	अणु true, "RXUES", "MTL RX Memory Error" पूर्ण,
	अणु false, "UNKNOWN", "Unknown Error" पूर्ण, /* 7 */
	अणु true, "ECES", "MTL EST Memory Error" पूर्ण,
	अणु true, "EAMS", "MTL EST Memory Address Mismatch Error" पूर्ण,
	अणु true, "EUES", "MTL EST Memory Error" पूर्ण,
	अणु false, "UNKNOWN", "Unknown Error" पूर्ण, /* 11 */
	अणु true, "RPCES", "MTL RX Parser Memory Error" पूर्ण,
	अणु true, "RPAMS", "MTL RX Parser Memory Address Mismatch Error" पूर्ण,
	अणु true, "RPUES", "MTL RX Parser Memory Error" पूर्ण,
	अणु false, "UNKNOWN", "Unknown Error" पूर्ण, /* 15 */
	अणु false, "UNKNOWN", "Unknown Error" पूर्ण, /* 16 */
	अणु false, "UNKNOWN", "Unknown Error" पूर्ण, /* 17 */
	अणु false, "UNKNOWN", "Unknown Error" पूर्ण, /* 18 */
	अणु false, "UNKNOWN", "Unknown Error" पूर्ण, /* 19 */
	अणु false, "UNKNOWN", "Unknown Error" पूर्ण, /* 20 */
	अणु false, "UNKNOWN", "Unknown Error" पूर्ण, /* 21 */
	अणु false, "UNKNOWN", "Unknown Error" पूर्ण, /* 22 */
	अणु false, "UNKNOWN", "Unknown Error" पूर्ण, /* 23 */
	अणु false, "UNKNOWN", "Unknown Error" पूर्ण, /* 24 */
	अणु false, "UNKNOWN", "Unknown Error" पूर्ण, /* 25 */
	अणु false, "UNKNOWN", "Unknown Error" पूर्ण, /* 26 */
	अणु false, "UNKNOWN", "Unknown Error" पूर्ण, /* 27 */
	अणु false, "UNKNOWN", "Unknown Error" पूर्ण, /* 28 */
	अणु false, "UNKNOWN", "Unknown Error" पूर्ण, /* 29 */
	अणु false, "UNKNOWN", "Unknown Error" पूर्ण, /* 30 */
	अणु false, "UNKNOWN", "Unknown Error" पूर्ण, /* 31 */
पूर्ण;

अटल व्योम dwmac5_handle_mtl_err(काष्ठा net_device *ndev,
		व्योम __iomem *ioaddr, bool correctable,
		काष्ठा sपंचांगmac_safety_stats *stats)
अणु
	u32 value;

	value = पढ़ोl(ioaddr + MTL_ECC_INT_STATUS);
	ग_लिखोl(value, ioaddr + MTL_ECC_INT_STATUS);

	dwmac5_log_error(ndev, value, correctable, "MTL", dwmac5_mtl_errors,
			STAT_OFF(mtl_errors), stats);
पूर्ण

अटल स्थिर काष्ठा dwmac5_error_desc dwmac5_dma_errors[32]= अणु
	अणु true, "TCES", "DMA TSO Memory Error" पूर्ण,
	अणु true, "TAMS", "DMA TSO Memory Address Mismatch Error" पूर्ण,
	अणु true, "TUES", "DMA TSO Memory Error" पूर्ण,
	अणु false, "UNKNOWN", "Unknown Error" पूर्ण, /* 3 */
	अणु false, "UNKNOWN", "Unknown Error" पूर्ण, /* 4 */
	अणु false, "UNKNOWN", "Unknown Error" पूर्ण, /* 5 */
	अणु false, "UNKNOWN", "Unknown Error" पूर्ण, /* 6 */
	अणु false, "UNKNOWN", "Unknown Error" पूर्ण, /* 7 */
	अणु false, "UNKNOWN", "Unknown Error" पूर्ण, /* 8 */
	अणु false, "UNKNOWN", "Unknown Error" पूर्ण, /* 9 */
	अणु false, "UNKNOWN", "Unknown Error" पूर्ण, /* 10 */
	अणु false, "UNKNOWN", "Unknown Error" पूर्ण, /* 11 */
	अणु false, "UNKNOWN", "Unknown Error" पूर्ण, /* 12 */
	अणु false, "UNKNOWN", "Unknown Error" पूर्ण, /* 13 */
	अणु false, "UNKNOWN", "Unknown Error" पूर्ण, /* 14 */
	अणु false, "UNKNOWN", "Unknown Error" पूर्ण, /* 15 */
	अणु false, "UNKNOWN", "Unknown Error" पूर्ण, /* 16 */
	अणु false, "UNKNOWN", "Unknown Error" पूर्ण, /* 17 */
	अणु false, "UNKNOWN", "Unknown Error" पूर्ण, /* 18 */
	अणु false, "UNKNOWN", "Unknown Error" पूर्ण, /* 19 */
	अणु false, "UNKNOWN", "Unknown Error" पूर्ण, /* 20 */
	अणु false, "UNKNOWN", "Unknown Error" पूर्ण, /* 21 */
	अणु false, "UNKNOWN", "Unknown Error" पूर्ण, /* 22 */
	अणु false, "UNKNOWN", "Unknown Error" पूर्ण, /* 23 */
	अणु false, "UNKNOWN", "Unknown Error" पूर्ण, /* 24 */
	अणु false, "UNKNOWN", "Unknown Error" पूर्ण, /* 25 */
	अणु false, "UNKNOWN", "Unknown Error" पूर्ण, /* 26 */
	अणु false, "UNKNOWN", "Unknown Error" पूर्ण, /* 27 */
	अणु false, "UNKNOWN", "Unknown Error" पूर्ण, /* 28 */
	अणु false, "UNKNOWN", "Unknown Error" पूर्ण, /* 29 */
	अणु false, "UNKNOWN", "Unknown Error" पूर्ण, /* 30 */
	अणु false, "UNKNOWN", "Unknown Error" पूर्ण, /* 31 */
पूर्ण;

अटल व्योम dwmac5_handle_dma_err(काष्ठा net_device *ndev,
		व्योम __iomem *ioaddr, bool correctable,
		काष्ठा sपंचांगmac_safety_stats *stats)
अणु
	u32 value;

	value = पढ़ोl(ioaddr + DMA_ECC_INT_STATUS);
	ग_लिखोl(value, ioaddr + DMA_ECC_INT_STATUS);

	dwmac5_log_error(ndev, value, correctable, "DMA", dwmac5_dma_errors,
			STAT_OFF(dma_errors), stats);
पूर्ण

पूर्णांक dwmac5_safety_feat_config(व्योम __iomem *ioaddr, अचिन्हित पूर्णांक asp)
अणु
	u32 value;

	अगर (!asp)
		वापस -EINVAL;

	/* 1. Enable Safety Features */
	value = पढ़ोl(ioaddr + MTL_ECC_CONTROL);
	value |= MEEAO; /* MTL ECC Error Addr Status Override */
	value |= TSOEE; /* TSO ECC */
	value |= MRXPEE; /* MTL RX Parser ECC */
	value |= MESTEE; /* MTL EST ECC */
	value |= MRXEE; /* MTL RX FIFO ECC */
	value |= MTXEE; /* MTL TX FIFO ECC */
	ग_लिखोl(value, ioaddr + MTL_ECC_CONTROL);

	/* 2. Enable MTL Safety Interrupts */
	value = पढ़ोl(ioaddr + MTL_ECC_INT_ENABLE);
	value |= RPCEIE; /* RX Parser Memory Correctable Error */
	value |= ECEIE; /* EST Memory Correctable Error */
	value |= RXCEIE; /* RX Memory Correctable Error */
	value |= TXCEIE; /* TX Memory Correctable Error */
	ग_लिखोl(value, ioaddr + MTL_ECC_INT_ENABLE);

	/* 3. Enable DMA Safety Interrupts */
	value = पढ़ोl(ioaddr + DMA_ECC_INT_ENABLE);
	value |= TCEIE; /* TSO Memory Correctable Error */
	ग_लिखोl(value, ioaddr + DMA_ECC_INT_ENABLE);

	/* Only ECC Protection क्रम External Memory feature is selected */
	अगर (asp <= 0x1)
		वापस 0;

	/* 5. Enable Parity and Timeout क्रम FSM */
	value = पढ़ोl(ioaddr + MAC_FSM_CONTROL);
	value |= PRTYEN; /* FSM Parity Feature */
	value |= TMOUTEN; /* FSM Timeout Feature */
	ग_लिखोl(value, ioaddr + MAC_FSM_CONTROL);

	/* 4. Enable Data Parity Protection */
	value = पढ़ोl(ioaddr + MTL_DPP_CONTROL);
	value |= EDPP;
	ग_लिखोl(value, ioaddr + MTL_DPP_CONTROL);

	/*
	 * All the Automotive Safety features are selected without the "Parity
	 * Port Enable क्रम बाह्यal पूर्णांकerface" feature.
	 */
	अगर (asp <= 0x2)
		वापस 0;

	value |= EPSI;
	ग_लिखोl(value, ioaddr + MTL_DPP_CONTROL);
	वापस 0;
पूर्ण

पूर्णांक dwmac5_safety_feat_irq_status(काष्ठा net_device *ndev,
		व्योम __iomem *ioaddr, अचिन्हित पूर्णांक asp,
		काष्ठा sपंचांगmac_safety_stats *stats)
अणु
	bool err, corr;
	u32 mtl, dma;
	पूर्णांक ret = 0;

	अगर (!asp)
		वापस -EINVAL;

	mtl = पढ़ोl(ioaddr + MTL_SAFETY_INT_STATUS);
	dma = पढ़ोl(ioaddr + DMA_SAFETY_INT_STATUS);

	err = (mtl & MCSIS) || (dma & MCSIS);
	corr = false;
	अगर (err) अणु
		dwmac5_handle_mac_err(ndev, ioaddr, corr, stats);
		ret |= !corr;
	पूर्ण

	err = (mtl & (MEUIS | MECIS)) || (dma & (MSUIS | MSCIS));
	corr = (mtl & MECIS) || (dma & MSCIS);
	अगर (err) अणु
		dwmac5_handle_mtl_err(ndev, ioaddr, corr, stats);
		ret |= !corr;
	पूर्ण

	err = dma & (DEUIS | DECIS);
	corr = dma & DECIS;
	अगर (err) अणु
		dwmac5_handle_dma_err(ndev, ioaddr, corr, stats);
		ret |= !corr;
	पूर्ण

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा dwmac5_error अणु
	स्थिर काष्ठा dwmac5_error_desc *desc;
पूर्ण dwmac5_all_errors[] = अणु
	अणु dwmac5_mac_errors पूर्ण,
	अणु dwmac5_mtl_errors पूर्ण,
	अणु dwmac5_dma_errors पूर्ण,
पूर्ण;

पूर्णांक dwmac5_safety_feat_dump(काष्ठा sपंचांगmac_safety_stats *stats,
			पूर्णांक index, अचिन्हित दीर्घ *count, स्थिर अक्षर **desc)
अणु
	पूर्णांक module = index / 32, offset = index % 32;
	अचिन्हित दीर्घ *ptr = (अचिन्हित दीर्घ *)stats;

	अगर (module >= ARRAY_SIZE(dwmac5_all_errors))
		वापस -EINVAL;
	अगर (!dwmac5_all_errors[module].desc[offset].valid)
		वापस -EINVAL;
	अगर (count)
		*count = *(ptr + index);
	अगर (desc)
		*desc = dwmac5_all_errors[module].desc[offset].desc;
	वापस 0;
पूर्ण

अटल पूर्णांक dwmac5_rxp_disable(व्योम __iomem *ioaddr)
अणु
	u32 val;

	val = पढ़ोl(ioaddr + MTL_OPERATION_MODE);
	val &= ~MTL_FRPE;
	ग_लिखोl(val, ioaddr + MTL_OPERATION_MODE);

	वापस पढ़ोl_poll_समयout(ioaddr + MTL_RXP_CONTROL_STATUS, val,
			val & RXPI, 1, 10000);
पूर्ण

अटल व्योम dwmac5_rxp_enable(व्योम __iomem *ioaddr)
अणु
	u32 val;

	val = पढ़ोl(ioaddr + MTL_OPERATION_MODE);
	val |= MTL_FRPE;
	ग_लिखोl(val, ioaddr + MTL_OPERATION_MODE);
पूर्ण

अटल पूर्णांक dwmac5_rxp_update_single_entry(व्योम __iomem *ioaddr,
					  काष्ठा sपंचांगmac_tc_entry *entry,
					  पूर्णांक pos)
अणु
	पूर्णांक ret, i;

	क्रम (i = 0; i < (माप(entry->val) / माप(u32)); i++) अणु
		पूर्णांक real_pos = pos * (माप(entry->val) / माप(u32)) + i;
		u32 val;

		/* Wait क्रम पढ़ोy */
		ret = पढ़ोl_poll_समयout(ioaddr + MTL_RXP_IACC_CTRL_STATUS,
				val, !(val & STARTBUSY), 1, 10000);
		अगर (ret)
			वापस ret;

		/* Write data */
		val = *((u32 *)&entry->val + i);
		ग_लिखोl(val, ioaddr + MTL_RXP_IACC_DATA);

		/* Write pos */
		val = real_pos & ADDR;
		ग_लिखोl(val, ioaddr + MTL_RXP_IACC_CTRL_STATUS);

		/* Write OP */
		val |= WRRDN;
		ग_लिखोl(val, ioaddr + MTL_RXP_IACC_CTRL_STATUS);

		/* Start Write */
		val |= STARTBUSY;
		ग_लिखोl(val, ioaddr + MTL_RXP_IACC_CTRL_STATUS);

		/* Wait क्रम करोne */
		ret = पढ़ोl_poll_समयout(ioaddr + MTL_RXP_IACC_CTRL_STATUS,
				val, !(val & STARTBUSY), 1, 10000);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा sपंचांगmac_tc_entry *
dwmac5_rxp_get_next_entry(काष्ठा sपंचांगmac_tc_entry *entries, अचिन्हित पूर्णांक count,
			  u32 curr_prio)
अणु
	काष्ठा sपंचांगmac_tc_entry *entry;
	u32 min_prio = ~0x0;
	पूर्णांक i, min_prio_idx;
	bool found = false;

	क्रम (i = count - 1; i >= 0; i--) अणु
		entry = &entries[i];

		/* Do not update unused entries */
		अगर (!entry->in_use)
			जारी;
		/* Do not update alपढ़ोy updated entries (i.e. fragments) */
		अगर (entry->in_hw)
			जारी;
		/* Let last entry be updated last */
		अगर (entry->is_last)
			जारी;
		/* Do not वापस fragments */
		अगर (entry->is_frag)
			जारी;
		/* Check अगर we alपढ़ोy checked this prio */
		अगर (entry->prio < curr_prio)
			जारी;
		/* Check अगर this is the minimum prio */
		अगर (entry->prio < min_prio) अणु
			min_prio = entry->prio;
			min_prio_idx = i;
			found = true;
		पूर्ण
	पूर्ण

	अगर (found)
		वापस &entries[min_prio_idx];
	वापस शून्य;
पूर्ण

पूर्णांक dwmac5_rxp_config(व्योम __iomem *ioaddr, काष्ठा sपंचांगmac_tc_entry *entries,
		      अचिन्हित पूर्णांक count)
अणु
	काष्ठा sपंचांगmac_tc_entry *entry, *frag;
	पूर्णांक i, ret, nve = 0;
	u32 curr_prio = 0;
	u32 old_val, val;

	/* Force disable RX */
	old_val = पढ़ोl(ioaddr + GMAC_CONFIG);
	val = old_val & ~GMAC_CONFIG_RE;
	ग_लिखोl(val, ioaddr + GMAC_CONFIG);

	/* Disable RX Parser */
	ret = dwmac5_rxp_disable(ioaddr);
	अगर (ret)
		जाओ re_enable;

	/* Set all entries as NOT in HW */
	क्रम (i = 0; i < count; i++) अणु
		entry = &entries[i];
		entry->in_hw = false;
	पूर्ण

	/* Update entries by reverse order */
	जबतक (1) अणु
		entry = dwmac5_rxp_get_next_entry(entries, count, curr_prio);
		अगर (!entry)
			अवरोध;

		curr_prio = entry->prio;
		frag = entry->frag_ptr;

		/* Set special fragment requirements */
		अगर (frag) अणु
			entry->val.af = 0;
			entry->val.rf = 0;
			entry->val.nc = 1;
			entry->val.ok_index = nve + 2;
		पूर्ण

		ret = dwmac5_rxp_update_single_entry(ioaddr, entry, nve);
		अगर (ret)
			जाओ re_enable;

		entry->table_pos = nve++;
		entry->in_hw = true;

		अगर (frag && !frag->in_hw) अणु
			ret = dwmac5_rxp_update_single_entry(ioaddr, frag, nve);
			अगर (ret)
				जाओ re_enable;
			frag->table_pos = nve++;
			frag->in_hw = true;
		पूर्ण
	पूर्ण

	अगर (!nve)
		जाओ re_enable;

	/* Update all pass entry */
	क्रम (i = 0; i < count; i++) अणु
		entry = &entries[i];
		अगर (!entry->is_last)
			जारी;

		ret = dwmac5_rxp_update_single_entry(ioaddr, entry, nve);
		अगर (ret)
			जाओ re_enable;

		entry->table_pos = nve++;
	पूर्ण

	/* Assume n. of parsable entries == n. of valid entries */
	val = (nve << 16) & NPE;
	val |= nve & NVE;
	ग_लिखोl(val, ioaddr + MTL_RXP_CONTROL_STATUS);

	/* Enable RX Parser */
	dwmac5_rxp_enable(ioaddr);

re_enable:
	/* Re-enable RX */
	ग_लिखोl(old_val, ioaddr + GMAC_CONFIG);
	वापस ret;
पूर्ण

पूर्णांक dwmac5_flex_pps_config(व्योम __iomem *ioaddr, पूर्णांक index,
			   काष्ठा sपंचांगmac_pps_cfg *cfg, bool enable,
			   u32 sub_second_inc, u32 sysसमय_flags)
अणु
	u32 tnsec = पढ़ोl(ioaddr + MAC_PPSx_TARGET_TIME_NSEC(index));
	u32 val = पढ़ोl(ioaddr + MAC_PPS_CONTROL);
	u64 period;

	अगर (!cfg->available)
		वापस -EINVAL;
	अगर (tnsec & TRGTBUSY0)
		वापस -EBUSY;
	अगर (!sub_second_inc || !sysसमय_flags)
		वापस -EINVAL;

	val &= ~PPSx_MASK(index);

	अगर (!enable) अणु
		val |= PPSCMDx(index, 0x5);
		val |= PPSEN0;
		ग_लिखोl(val, ioaddr + MAC_PPS_CONTROL);
		वापस 0;
	पूर्ण

	val |= PPSCMDx(index, 0x2);
	val |= TRGTMODSELx(index, 0x2);
	val |= PPSEN0;

	ग_लिखोl(cfg->start.tv_sec, ioaddr + MAC_PPSx_TARGET_TIME_SEC(index));

	अगर (!(sysसमय_flags & PTP_TCR_TSCTRLSSR))
		cfg->start.tv_nsec = (cfg->start.tv_nsec * 1000) / 465;
	ग_लिखोl(cfg->start.tv_nsec, ioaddr + MAC_PPSx_TARGET_TIME_NSEC(index));

	period = cfg->period.tv_sec * 1000000000;
	period += cfg->period.tv_nsec;

	करो_भाग(period, sub_second_inc);

	अगर (period <= 1)
		वापस -EINVAL;

	ग_लिखोl(period - 1, ioaddr + MAC_PPSx_INTERVAL(index));

	period >>= 1;
	अगर (period <= 1)
		वापस -EINVAL;

	ग_लिखोl(period - 1, ioaddr + MAC_PPSx_WIDTH(index));

	/* Finally, activate it */
	ग_लिखोl(val, ioaddr + MAC_PPS_CONTROL);
	वापस 0;
पूर्ण

अटल पूर्णांक dwmac5_est_ग_लिखो(व्योम __iomem *ioaddr, u32 reg, u32 val, bool gcl)
अणु
	u32 ctrl;

	ग_लिखोl(val, ioaddr + MTL_EST_GCL_DATA);

	ctrl = (reg << ADDR_SHIFT);
	ctrl |= gcl ? 0 : GCRR;

	ग_लिखोl(ctrl, ioaddr + MTL_EST_GCL_CONTROL);

	ctrl |= SRWO;
	ग_लिखोl(ctrl, ioaddr + MTL_EST_GCL_CONTROL);

	वापस पढ़ोl_poll_समयout(ioaddr + MTL_EST_GCL_CONTROL,
				  ctrl, !(ctrl & SRWO), 100, 5000);
पूर्ण

पूर्णांक dwmac5_est_configure(व्योम __iomem *ioaddr, काष्ठा sपंचांगmac_est *cfg,
			 अचिन्हित पूर्णांक ptp_rate)
अणु
	पूर्णांक i, ret = 0x0;
	u32 ctrl;

	ret |= dwmac5_est_ग_लिखो(ioaddr, BTR_LOW, cfg->btr[0], false);
	ret |= dwmac5_est_ग_लिखो(ioaddr, BTR_HIGH, cfg->btr[1], false);
	ret |= dwmac5_est_ग_लिखो(ioaddr, TER, cfg->ter, false);
	ret |= dwmac5_est_ग_लिखो(ioaddr, LLR, cfg->gcl_size, false);
	ret |= dwmac5_est_ग_लिखो(ioaddr, CTR_LOW, cfg->ctr[0], false);
	ret |= dwmac5_est_ग_लिखो(ioaddr, CTR_HIGH, cfg->ctr[1], false);
	अगर (ret)
		वापस ret;

	क्रम (i = 0; i < cfg->gcl_size; i++) अणु
		ret = dwmac5_est_ग_लिखो(ioaddr, i, cfg->gcl[i], true);
		अगर (ret)
			वापस ret;
	पूर्ण

	ctrl = पढ़ोl(ioaddr + MTL_EST_CONTROL);
	ctrl &= ~PTOV;
	ctrl |= ((1000000000 / ptp_rate) * 6) << PTOV_SHIFT;
	अगर (cfg->enable)
		ctrl |= EEST | SSWL;
	अन्यथा
		ctrl &= ~EEST;

	ग_लिखोl(ctrl, ioaddr + MTL_EST_CONTROL);

	/* Configure EST पूर्णांकerrupt */
	अगर (cfg->enable)
		ctrl = (IECGCE | IEHS | IEHF | IEBE | IECC);
	अन्यथा
		ctrl = 0;

	ग_लिखोl(ctrl, ioaddr + MTL_EST_INT_EN);

	वापस 0;
पूर्ण

व्योम dwmac5_est_irq_status(व्योम __iomem *ioaddr, काष्ठा net_device *dev,
			  काष्ठा sपंचांगmac_extra_stats *x, u32 txqcnt)
अणु
	u32 status, value, feqn, hbfq, hbfs, btrl;
	u32 txqcnt_mask = (1 << txqcnt) - 1;

	status = पढ़ोl(ioaddr + MTL_EST_STATUS);

	value = (CGCE | HLBS | HLBF | BTRE | SWLC);

	/* Return अगर there is no error */
	अगर (!(status & value))
		वापस;

	अगर (status & CGCE) अणु
		/* Clear Interrupt */
		ग_लिखोl(CGCE, ioaddr + MTL_EST_STATUS);

		x->mtl_est_cgce++;
	पूर्ण

	अगर (status & HLBS) अणु
		value = पढ़ोl(ioaddr + MTL_EST_SCH_ERR);
		value &= txqcnt_mask;

		x->mtl_est_hlbs++;

		/* Clear Interrupt */
		ग_लिखोl(value, ioaddr + MTL_EST_SCH_ERR);

		/* Collecting info to shows all the queues that has HLBS
		 * issue. The only way to clear this is to clear the
		 * statistic
		 */
		अगर (net_ratelimit())
			netdev_err(dev, "EST: HLB(sched) Queue 0x%x\n", value);
	पूर्ण

	अगर (status & HLBF) अणु
		value = पढ़ोl(ioaddr + MTL_EST_FRM_SZ_ERR);
		feqn = value & txqcnt_mask;

		value = पढ़ोl(ioaddr + MTL_EST_FRM_SZ_CAP);
		hbfq = (value & SZ_CAP_HBFQ_MASK(txqcnt)) >> SZ_CAP_HBFQ_SHIFT;
		hbfs = value & SZ_CAP_HBFS_MASK;

		x->mtl_est_hlbf++;

		/* Clear Interrupt */
		ग_लिखोl(feqn, ioaddr + MTL_EST_FRM_SZ_ERR);

		अगर (net_ratelimit())
			netdev_err(dev, "EST: HLB(size) Queue %u Size %u\n",
				   hbfq, hbfs);
	पूर्ण

	अगर (status & BTRE) अणु
		अगर ((status & BTRL) == BTRL_MAX)
			x->mtl_est_btrlm++;
		अन्यथा
			x->mtl_est_btre++;

		btrl = (status & BTRL) >> BTRL_SHIFT;

		अगर (net_ratelimit())
			netdev_info(dev, "EST: BTR Error Loop Count %u\n",
				    btrl);

		ग_लिखोl(BTRE, ioaddr + MTL_EST_STATUS);
	पूर्ण

	अगर (status & SWLC) अणु
		ग_लिखोl(SWLC, ioaddr + MTL_EST_STATUS);
		netdev_info(dev, "EST: SWOL has been switched\n");
	पूर्ण
पूर्ण

व्योम dwmac5_fpe_configure(व्योम __iomem *ioaddr, u32 num_txq, u32 num_rxq,
			  bool enable)
अणु
	u32 value;

	अगर (!enable) अणु
		value = पढ़ोl(ioaddr + MAC_FPE_CTRL_STS);

		value &= ~EFPE;

		ग_लिखोl(value, ioaddr + MAC_FPE_CTRL_STS);
		वापस;
	पूर्ण

	value = पढ़ोl(ioaddr + GMAC_RXQ_CTRL1);
	value &= ~GMAC_RXQCTRL_FPRQ;
	value |= (num_rxq - 1) << GMAC_RXQCTRL_FPRQ_SHIFT;
	ग_लिखोl(value, ioaddr + GMAC_RXQ_CTRL1);

	value = पढ़ोl(ioaddr + MAC_FPE_CTRL_STS);
	value |= EFPE;
	ग_लिखोl(value, ioaddr + MAC_FPE_CTRL_STS);
पूर्ण

पूर्णांक dwmac5_fpe_irq_status(व्योम __iomem *ioaddr, काष्ठा net_device *dev)
अणु
	u32 value;
	पूर्णांक status;

	status = FPE_EVENT_UNKNOWN;

	value = पढ़ोl(ioaddr + MAC_FPE_CTRL_STS);

	अगर (value & TRSP) अणु
		status |= FPE_EVENT_TRSP;
		netdev_info(dev, "FPE: Respond mPacket is transmitted\n");
	पूर्ण

	अगर (value & TVER) अणु
		status |= FPE_EVENT_TVER;
		netdev_info(dev, "FPE: Verify mPacket is transmitted\n");
	पूर्ण

	अगर (value & RRSP) अणु
		status |= FPE_EVENT_RRSP;
		netdev_info(dev, "FPE: Respond mPacket is received\n");
	पूर्ण

	अगर (value & RVER) अणु
		status |= FPE_EVENT_RVER;
		netdev_info(dev, "FPE: Verify mPacket is received\n");
	पूर्ण

	वापस status;
पूर्ण

व्योम dwmac5_fpe_send_mpacket(व्योम __iomem *ioaddr, क्रमागत sपंचांगmac_mpacket_type type)
अणु
	u32 value;

	value = पढ़ोl(ioaddr + MAC_FPE_CTRL_STS);

	अगर (type == MPACKET_VERIFY) अणु
		value &= ~SRSP;
		value |= SVER;
	पूर्ण अन्यथा अणु
		value &= ~SVER;
		value |= SRSP;
	पूर्ण

	ग_लिखोl(value, ioaddr + MAC_FPE_CTRL_STS);
पूर्ण
