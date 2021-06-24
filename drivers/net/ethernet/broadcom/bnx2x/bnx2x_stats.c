<शैली गुरु>
/* bnx2x_stats.c: QLogic Everest network driver.
 *
 * Copyright (c) 2007-2013 Broadcom Corporation
 * Copyright (c) 2014 QLogic Corporation
 * All rights reserved
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation.
 *
 * Maपूर्णांकained by: Ariel Elior <ariel.elior@qlogic.com>
 * Written by: Eliezer Tamir
 * Based on code from Michael Chan's bnx2 driver
 * UDP CSUM errata workaround by Arik Gendelman
 * Slowpath and fastpath rework by Vladislav Zolotarov
 * Statistics and Link management by Yitchak Gertner
 *
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश "bnx2x_stats.h"
#समावेश "bnx2x_cmn.h"
#समावेश "bnx2x_sriov.h"

बाह्य स्थिर u32 dmae_reg_go_c[];

/* Statistics */

/*
 * General service functions
 */

अटल अंतरभूत दीर्घ bnx2x_hilo(u32 *hiref)
अणु
	u32 lo = *(hiref + 1);
#अगर (BITS_PER_LONG == 64)
	u32 hi = *hiref;

	वापस HILO_U64(hi, lo);
#अन्यथा
	वापस lo;
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत u16 bnx2x_get_port_stats_dma_len(काष्ठा bnx2x *bp)
अणु
	u16 res = 0;

	/* 'newest' convention - shmem2 cotains the size of the port stats */
	अगर (SHMEM2_HAS(bp, माप_port_stats)) अणु
		u32 size = SHMEM2_RD(bp, माप_port_stats);
		अगर (size)
			res = size;

		/* prevent newer BC from causing buffer overflow */
		अगर (res > माप(काष्ठा host_port_stats))
			res = माप(काष्ठा host_port_stats);
	पूर्ण

	/* Older convention - all BCs support the port stats' fields up until
	 * the 'not_used' field
	 */
	अगर (!res) अणु
		res = दुरत्व(काष्ठा host_port_stats, not_used) + 4;

		/* अगर PFC stats are supported by the MFW, DMA them as well */
		अगर (bp->flags & BC_SUPPORTS_PFC_STATS) अणु
			res += दुरत्व(काष्ठा host_port_stats,
					pfc_frames_rx_lo) -
			       दुरत्व(काष्ठा host_port_stats,
					pfc_frames_tx_hi) + 4 ;
		पूर्ण
	पूर्ण

	res >>= 2;

	WARN_ON(res > 2 * DMAE_LEN32_RD_MAX);
	वापस res;
पूर्ण

/*
 * Init service functions
 */

अटल व्योम bnx2x_dp_stats(काष्ठा bnx2x *bp)
अणु
	पूर्णांक i;

	DP(BNX2X_MSG_STATS, "dumping stats:\n"
	   "fw_stats_req\n"
	   "    hdr\n"
	   "        cmd_num %d\n"
	   "        reserved0 %d\n"
	   "        drv_stats_counter %d\n"
	   "        reserved1 %d\n"
	   "        stats_counters_addrs %x %x\n",
	   bp->fw_stats_req->hdr.cmd_num,
	   bp->fw_stats_req->hdr.reserved0,
	   bp->fw_stats_req->hdr.drv_stats_counter,
	   bp->fw_stats_req->hdr.reserved1,
	   bp->fw_stats_req->hdr.stats_counters_addrs.hi,
	   bp->fw_stats_req->hdr.stats_counters_addrs.lo);

	क्रम (i = 0; i < bp->fw_stats_req->hdr.cmd_num; i++) अणु
		DP(BNX2X_MSG_STATS,
		   "query[%d]\n"
		   "              kind %d\n"
		   "              index %d\n"
		   "              funcID %d\n"
		   "              reserved %d\n"
		   "              address %x %x\n",
		   i, bp->fw_stats_req->query[i].kind,
		   bp->fw_stats_req->query[i].index,
		   bp->fw_stats_req->query[i].funcID,
		   bp->fw_stats_req->query[i].reserved,
		   bp->fw_stats_req->query[i].address.hi,
		   bp->fw_stats_req->query[i].address.lo);
	पूर्ण
पूर्ण

/* Post the next statistics ramrod. Protect it with the spin in
 * order to ensure the strict order between statistics ramrods
 * (each ramrod has a sequence number passed in a
 * bp->fw_stats_req->hdr.drv_stats_counter and ramrods must be
 * sent in order).
 */
अटल व्योम bnx2x_storm_stats_post(काष्ठा bnx2x *bp)
अणु
	पूर्णांक rc;

	अगर (bp->stats_pending)
		वापस;

	bp->fw_stats_req->hdr.drv_stats_counter =
		cpu_to_le16(bp->stats_counter++);

	DP(BNX2X_MSG_STATS, "Sending statistics ramrod %d\n",
	   le16_to_cpu(bp->fw_stats_req->hdr.drv_stats_counter));

	/* adjust the ramrod to include VF queues statistics */
	bnx2x_iov_adjust_stats_req(bp);
	bnx2x_dp_stats(bp);

	/* send FW stats ramrod */
	rc = bnx2x_sp_post(bp, RAMROD_CMD_ID_COMMON_STAT_QUERY, 0,
			   U64_HI(bp->fw_stats_req_mapping),
			   U64_LO(bp->fw_stats_req_mapping),
			   NONE_CONNECTION_TYPE);
	अगर (rc == 0)
		bp->stats_pending = 1;
पूर्ण

अटल व्योम bnx2x_hw_stats_post(काष्ठा bnx2x *bp)
अणु
	काष्ठा dmae_command *dmae = &bp->stats_dmae;
	u32 *stats_comp = bnx2x_sp(bp, stats_comp);

	*stats_comp = DMAE_COMP_VAL;
	अगर (CHIP_REV_IS_SLOW(bp))
		वापस;

	/* Update MCP's statistics अगर possible */
	अगर (bp->func_stx)
		स_नकल(bnx2x_sp(bp, func_stats), &bp->func_stats,
		       माप(bp->func_stats));

	/* loader */
	अगर (bp->executer_idx) अणु
		पूर्णांक loader_idx = PMF_DMAE_C(bp);
		u32 opcode =  bnx2x_dmae_opcode(bp, DMAE_SRC_PCI, DMAE_DST_GRC,
						 true, DMAE_COMP_GRC);
		opcode = bnx2x_dmae_opcode_clr_src_reset(opcode);

		स_रखो(dmae, 0, माप(काष्ठा dmae_command));
		dmae->opcode = opcode;
		dmae->src_addr_lo = U64_LO(bnx2x_sp_mapping(bp, dmae[0]));
		dmae->src_addr_hi = U64_HI(bnx2x_sp_mapping(bp, dmae[0]));
		dmae->dst_addr_lo = (DMAE_REG_CMD_MEM +
				     माप(काष्ठा dmae_command) *
				     (loader_idx + 1)) >> 2;
		dmae->dst_addr_hi = 0;
		dmae->len = माप(काष्ठा dmae_command) >> 2;
		अगर (CHIP_IS_E1(bp))
			dmae->len--;
		dmae->comp_addr_lo = dmae_reg_go_c[loader_idx + 1] >> 2;
		dmae->comp_addr_hi = 0;
		dmae->comp_val = 1;

		*stats_comp = 0;
		bnx2x_post_dmae(bp, dmae, loader_idx);

	पूर्ण अन्यथा अगर (bp->func_stx) अणु
		*stats_comp = 0;
		bnx2x_issue_dmae_with_comp(bp, dmae, stats_comp);
	पूर्ण
पूर्ण

अटल व्योम bnx2x_stats_comp(काष्ठा bnx2x *bp)
अणु
	u32 *stats_comp = bnx2x_sp(bp, stats_comp);
	पूर्णांक cnt = 10;

	might_sleep();
	जबतक (*stats_comp != DMAE_COMP_VAL) अणु
		अगर (!cnt) अणु
			BNX2X_ERR("timeout waiting for stats finished\n");
			अवरोध;
		पूर्ण
		cnt--;
		usleep_range(1000, 2000);
	पूर्ण
पूर्ण

/*
 * Statistics service functions
 */

/* should be called under stats_sema */
अटल व्योम bnx2x_stats_pmf_update(काष्ठा bnx2x *bp)
अणु
	काष्ठा dmae_command *dmae;
	u32 opcode;
	पूर्णांक loader_idx = PMF_DMAE_C(bp);
	u32 *stats_comp = bnx2x_sp(bp, stats_comp);

	/* sanity */
	अगर (!bp->port.pmf || !bp->port.port_stx) अणु
		BNX2X_ERR("BUG!\n");
		वापस;
	पूर्ण

	bp->executer_idx = 0;

	opcode = bnx2x_dmae_opcode(bp, DMAE_SRC_GRC, DMAE_DST_PCI, false, 0);

	dmae = bnx2x_sp(bp, dmae[bp->executer_idx++]);
	dmae->opcode = bnx2x_dmae_opcode_add_comp(opcode, DMAE_COMP_GRC);
	dmae->src_addr_lo = bp->port.port_stx >> 2;
	dmae->src_addr_hi = 0;
	dmae->dst_addr_lo = U64_LO(bnx2x_sp_mapping(bp, port_stats));
	dmae->dst_addr_hi = U64_HI(bnx2x_sp_mapping(bp, port_stats));
	dmae->len = DMAE_LEN32_RD_MAX;
	dmae->comp_addr_lo = dmae_reg_go_c[loader_idx] >> 2;
	dmae->comp_addr_hi = 0;
	dmae->comp_val = 1;

	dmae = bnx2x_sp(bp, dmae[bp->executer_idx++]);
	dmae->opcode = bnx2x_dmae_opcode_add_comp(opcode, DMAE_COMP_PCI);
	dmae->src_addr_lo = (bp->port.port_stx >> 2) + DMAE_LEN32_RD_MAX;
	dmae->src_addr_hi = 0;
	dmae->dst_addr_lo = U64_LO(bnx2x_sp_mapping(bp, port_stats) +
				   DMAE_LEN32_RD_MAX * 4);
	dmae->dst_addr_hi = U64_HI(bnx2x_sp_mapping(bp, port_stats) +
				   DMAE_LEN32_RD_MAX * 4);
	dmae->len = bnx2x_get_port_stats_dma_len(bp) - DMAE_LEN32_RD_MAX;

	dmae->comp_addr_lo = U64_LO(bnx2x_sp_mapping(bp, stats_comp));
	dmae->comp_addr_hi = U64_HI(bnx2x_sp_mapping(bp, stats_comp));
	dmae->comp_val = DMAE_COMP_VAL;

	*stats_comp = 0;
	bnx2x_hw_stats_post(bp);
	bnx2x_stats_comp(bp);
पूर्ण

अटल व्योम bnx2x_port_stats_init(काष्ठा bnx2x *bp)
अणु
	काष्ठा dmae_command *dmae;
	पूर्णांक port = BP_PORT(bp);
	u32 opcode;
	पूर्णांक loader_idx = PMF_DMAE_C(bp);
	u32 mac_addr;
	u32 *stats_comp = bnx2x_sp(bp, stats_comp);

	/* sanity */
	अगर (!bp->link_vars.link_up || !bp->port.pmf) अणु
		BNX2X_ERR("BUG!\n");
		वापस;
	पूर्ण

	bp->executer_idx = 0;

	/* MCP */
	opcode = bnx2x_dmae_opcode(bp, DMAE_SRC_PCI, DMAE_DST_GRC,
				    true, DMAE_COMP_GRC);

	अगर (bp->port.port_stx) अणु

		dmae = bnx2x_sp(bp, dmae[bp->executer_idx++]);
		dmae->opcode = opcode;
		dmae->src_addr_lo = U64_LO(bnx2x_sp_mapping(bp, port_stats));
		dmae->src_addr_hi = U64_HI(bnx2x_sp_mapping(bp, port_stats));
		dmae->dst_addr_lo = bp->port.port_stx >> 2;
		dmae->dst_addr_hi = 0;
		dmae->len = bnx2x_get_port_stats_dma_len(bp);
		dmae->comp_addr_lo = dmae_reg_go_c[loader_idx] >> 2;
		dmae->comp_addr_hi = 0;
		dmae->comp_val = 1;
	पूर्ण

	अगर (bp->func_stx) अणु

		dmae = bnx2x_sp(bp, dmae[bp->executer_idx++]);
		dmae->opcode = opcode;
		dmae->src_addr_lo = U64_LO(bnx2x_sp_mapping(bp, func_stats));
		dmae->src_addr_hi = U64_HI(bnx2x_sp_mapping(bp, func_stats));
		dmae->dst_addr_lo = bp->func_stx >> 2;
		dmae->dst_addr_hi = 0;
		dmae->len = माप(काष्ठा host_func_stats) >> 2;
		dmae->comp_addr_lo = dmae_reg_go_c[loader_idx] >> 2;
		dmae->comp_addr_hi = 0;
		dmae->comp_val = 1;
	पूर्ण

	/* MAC */
	opcode = bnx2x_dmae_opcode(bp, DMAE_SRC_GRC, DMAE_DST_PCI,
				   true, DMAE_COMP_GRC);

	/* EMAC is special */
	अगर (bp->link_vars.mac_type == MAC_TYPE_EMAC) अणु
		mac_addr = (port ? GRCBASE_EMAC1 : GRCBASE_EMAC0);

		/* EMAC_REG_EMAC_RX_STAT_AC (EMAC_REG_EMAC_RX_STAT_AC_COUNT)*/
		dmae = bnx2x_sp(bp, dmae[bp->executer_idx++]);
		dmae->opcode = opcode;
		dmae->src_addr_lo = (mac_addr +
				     EMAC_REG_EMAC_RX_STAT_AC) >> 2;
		dmae->src_addr_hi = 0;
		dmae->dst_addr_lo = U64_LO(bnx2x_sp_mapping(bp, mac_stats));
		dmae->dst_addr_hi = U64_HI(bnx2x_sp_mapping(bp, mac_stats));
		dmae->len = EMAC_REG_EMAC_RX_STAT_AC_COUNT;
		dmae->comp_addr_lo = dmae_reg_go_c[loader_idx] >> 2;
		dmae->comp_addr_hi = 0;
		dmae->comp_val = 1;

		/* EMAC_REG_EMAC_RX_STAT_AC_28 */
		dmae = bnx2x_sp(bp, dmae[bp->executer_idx++]);
		dmae->opcode = opcode;
		dmae->src_addr_lo = (mac_addr +
				     EMAC_REG_EMAC_RX_STAT_AC_28) >> 2;
		dmae->src_addr_hi = 0;
		dmae->dst_addr_lo = U64_LO(bnx2x_sp_mapping(bp, mac_stats) +
		     दुरत्व(काष्ठा emac_stats, rx_stat_falsecarriererrors));
		dmae->dst_addr_hi = U64_HI(bnx2x_sp_mapping(bp, mac_stats) +
		     दुरत्व(काष्ठा emac_stats, rx_stat_falsecarriererrors));
		dmae->len = 1;
		dmae->comp_addr_lo = dmae_reg_go_c[loader_idx] >> 2;
		dmae->comp_addr_hi = 0;
		dmae->comp_val = 1;

		/* EMAC_REG_EMAC_TX_STAT_AC (EMAC_REG_EMAC_TX_STAT_AC_COUNT)*/
		dmae = bnx2x_sp(bp, dmae[bp->executer_idx++]);
		dmae->opcode = opcode;
		dmae->src_addr_lo = (mac_addr +
				     EMAC_REG_EMAC_TX_STAT_AC) >> 2;
		dmae->src_addr_hi = 0;
		dmae->dst_addr_lo = U64_LO(bnx2x_sp_mapping(bp, mac_stats) +
			दुरत्व(काष्ठा emac_stats, tx_stat_अगरhcoutoctets));
		dmae->dst_addr_hi = U64_HI(bnx2x_sp_mapping(bp, mac_stats) +
			दुरत्व(काष्ठा emac_stats, tx_stat_अगरhcoutoctets));
		dmae->len = EMAC_REG_EMAC_TX_STAT_AC_COUNT;
		dmae->comp_addr_lo = dmae_reg_go_c[loader_idx] >> 2;
		dmae->comp_addr_hi = 0;
		dmae->comp_val = 1;
	पूर्ण अन्यथा अणु
		u32 tx_src_addr_lo, rx_src_addr_lo;
		u16 rx_len, tx_len;

		/* configure the params according to MAC type */
		चयन (bp->link_vars.mac_type) अणु
		हाल MAC_TYPE_BMAC:
			mac_addr = (port ? NIG_REG_INGRESS_BMAC1_MEM :
					   NIG_REG_INGRESS_BMAC0_MEM);

			/* BIGMAC_REGISTER_TX_STAT_GTPKT ..
			   BIGMAC_REGISTER_TX_STAT_GTBYT */
			अगर (CHIP_IS_E1x(bp)) अणु
				tx_src_addr_lo = (mac_addr +
					BIGMAC_REGISTER_TX_STAT_GTPKT) >> 2;
				tx_len = (8 + BIGMAC_REGISTER_TX_STAT_GTBYT -
					  BIGMAC_REGISTER_TX_STAT_GTPKT) >> 2;
				rx_src_addr_lo = (mac_addr +
					BIGMAC_REGISTER_RX_STAT_GR64) >> 2;
				rx_len = (8 + BIGMAC_REGISTER_RX_STAT_GRIPJ -
					  BIGMAC_REGISTER_RX_STAT_GR64) >> 2;
			पूर्ण अन्यथा अणु
				tx_src_addr_lo = (mac_addr +
					BIGMAC2_REGISTER_TX_STAT_GTPOK) >> 2;
				tx_len = (8 + BIGMAC2_REGISTER_TX_STAT_GTBYT -
					  BIGMAC2_REGISTER_TX_STAT_GTPOK) >> 2;
				rx_src_addr_lo = (mac_addr +
					BIGMAC2_REGISTER_RX_STAT_GR64) >> 2;
				rx_len = (8 + BIGMAC2_REGISTER_RX_STAT_GRIPJ -
					  BIGMAC2_REGISTER_RX_STAT_GR64) >> 2;
			पूर्ण
			अवरोध;

		हाल MAC_TYPE_UMAC: /* handled by MSTAT */
		हाल MAC_TYPE_XMAC: /* handled by MSTAT */
		शेष:
			mac_addr = port ? GRCBASE_MSTAT1 : GRCBASE_MSTAT0;
			tx_src_addr_lo = (mac_addr +
					  MSTAT_REG_TX_STAT_GTXPOK_LO) >> 2;
			rx_src_addr_lo = (mac_addr +
					  MSTAT_REG_RX_STAT_GR64_LO) >> 2;
			tx_len = माप(bp->slowpath->
					mac_stats.mstat_stats.stats_tx) >> 2;
			rx_len = माप(bp->slowpath->
					mac_stats.mstat_stats.stats_rx) >> 2;
			अवरोध;
		पूर्ण

		/* TX stats */
		dmae = bnx2x_sp(bp, dmae[bp->executer_idx++]);
		dmae->opcode = opcode;
		dmae->src_addr_lo = tx_src_addr_lo;
		dmae->src_addr_hi = 0;
		dmae->len = tx_len;
		dmae->dst_addr_lo = U64_LO(bnx2x_sp_mapping(bp, mac_stats));
		dmae->dst_addr_hi = U64_HI(bnx2x_sp_mapping(bp, mac_stats));
		dmae->comp_addr_lo = dmae_reg_go_c[loader_idx] >> 2;
		dmae->comp_addr_hi = 0;
		dmae->comp_val = 1;

		/* RX stats */
		dmae = bnx2x_sp(bp, dmae[bp->executer_idx++]);
		dmae->opcode = opcode;
		dmae->src_addr_hi = 0;
		dmae->src_addr_lo = rx_src_addr_lo;
		dmae->dst_addr_lo =
			U64_LO(bnx2x_sp_mapping(bp, mac_stats) + (tx_len << 2));
		dmae->dst_addr_hi =
			U64_HI(bnx2x_sp_mapping(bp, mac_stats) + (tx_len << 2));
		dmae->len = rx_len;
		dmae->comp_addr_lo = dmae_reg_go_c[loader_idx] >> 2;
		dmae->comp_addr_hi = 0;
		dmae->comp_val = 1;
	पूर्ण

	/* NIG */
	अगर (!CHIP_IS_E3(bp)) अणु
		dmae = bnx2x_sp(bp, dmae[bp->executer_idx++]);
		dmae->opcode = opcode;
		dmae->src_addr_lo = (port ? NIG_REG_STAT1_EGRESS_MAC_PKT0 :
					    NIG_REG_STAT0_EGRESS_MAC_PKT0) >> 2;
		dmae->src_addr_hi = 0;
		dmae->dst_addr_lo = U64_LO(bnx2x_sp_mapping(bp, nig_stats) +
				दुरत्व(काष्ठा nig_stats, egress_mac_pkt0_lo));
		dmae->dst_addr_hi = U64_HI(bnx2x_sp_mapping(bp, nig_stats) +
				दुरत्व(काष्ठा nig_stats, egress_mac_pkt0_lo));
		dmae->len = (2*माप(u32)) >> 2;
		dmae->comp_addr_lo = dmae_reg_go_c[loader_idx] >> 2;
		dmae->comp_addr_hi = 0;
		dmae->comp_val = 1;

		dmae = bnx2x_sp(bp, dmae[bp->executer_idx++]);
		dmae->opcode = opcode;
		dmae->src_addr_lo = (port ? NIG_REG_STAT1_EGRESS_MAC_PKT1 :
					    NIG_REG_STAT0_EGRESS_MAC_PKT1) >> 2;
		dmae->src_addr_hi = 0;
		dmae->dst_addr_lo = U64_LO(bnx2x_sp_mapping(bp, nig_stats) +
				दुरत्व(काष्ठा nig_stats, egress_mac_pkt1_lo));
		dmae->dst_addr_hi = U64_HI(bnx2x_sp_mapping(bp, nig_stats) +
				दुरत्व(काष्ठा nig_stats, egress_mac_pkt1_lo));
		dmae->len = (2*माप(u32)) >> 2;
		dmae->comp_addr_lo = dmae_reg_go_c[loader_idx] >> 2;
		dmae->comp_addr_hi = 0;
		dmae->comp_val = 1;
	पूर्ण

	dmae = bnx2x_sp(bp, dmae[bp->executer_idx++]);
	dmae->opcode = bnx2x_dmae_opcode(bp, DMAE_SRC_GRC, DMAE_DST_PCI,
						 true, DMAE_COMP_PCI);
	dmae->src_addr_lo = (port ? NIG_REG_STAT1_BRB_DISCARD :
				    NIG_REG_STAT0_BRB_DISCARD) >> 2;
	dmae->src_addr_hi = 0;
	dmae->dst_addr_lo = U64_LO(bnx2x_sp_mapping(bp, nig_stats));
	dmae->dst_addr_hi = U64_HI(bnx2x_sp_mapping(bp, nig_stats));
	dmae->len = (माप(काष्ठा nig_stats) - 4*माप(u32)) >> 2;

	dmae->comp_addr_lo = U64_LO(bnx2x_sp_mapping(bp, stats_comp));
	dmae->comp_addr_hi = U64_HI(bnx2x_sp_mapping(bp, stats_comp));
	dmae->comp_val = DMAE_COMP_VAL;

	*stats_comp = 0;
पूर्ण

अटल व्योम bnx2x_func_stats_init(काष्ठा bnx2x *bp)
अणु
	काष्ठा dmae_command *dmae = &bp->stats_dmae;
	u32 *stats_comp = bnx2x_sp(bp, stats_comp);

	/* sanity */
	अगर (!bp->func_stx) अणु
		BNX2X_ERR("BUG!\n");
		वापस;
	पूर्ण

	bp->executer_idx = 0;
	स_रखो(dmae, 0, माप(काष्ठा dmae_command));

	dmae->opcode = bnx2x_dmae_opcode(bp, DMAE_SRC_PCI, DMAE_DST_GRC,
					 true, DMAE_COMP_PCI);
	dmae->src_addr_lo = U64_LO(bnx2x_sp_mapping(bp, func_stats));
	dmae->src_addr_hi = U64_HI(bnx2x_sp_mapping(bp, func_stats));
	dmae->dst_addr_lo = bp->func_stx >> 2;
	dmae->dst_addr_hi = 0;
	dmae->len = माप(काष्ठा host_func_stats) >> 2;
	dmae->comp_addr_lo = U64_LO(bnx2x_sp_mapping(bp, stats_comp));
	dmae->comp_addr_hi = U64_HI(bnx2x_sp_mapping(bp, stats_comp));
	dmae->comp_val = DMAE_COMP_VAL;

	*stats_comp = 0;
पूर्ण

/* should be called under stats_sema */
अटल व्योम bnx2x_stats_start(काष्ठा bnx2x *bp)
अणु
	अगर (IS_PF(bp)) अणु
		अगर (bp->port.pmf)
			bnx2x_port_stats_init(bp);

		अन्यथा अगर (bp->func_stx)
			bnx2x_func_stats_init(bp);

		bnx2x_hw_stats_post(bp);
		bnx2x_storm_stats_post(bp);
	पूर्ण
पूर्ण

अटल व्योम bnx2x_stats_pmf_start(काष्ठा bnx2x *bp)
अणु
	bnx2x_stats_comp(bp);
	bnx2x_stats_pmf_update(bp);
	bnx2x_stats_start(bp);
पूर्ण

अटल व्योम bnx2x_stats_restart(काष्ठा bnx2x *bp)
अणु
	/* vfs travel through here as part of the statistics FSM, but no action
	 * is required
	 */
	अगर (IS_VF(bp))
		वापस;

	bnx2x_stats_comp(bp);
	bnx2x_stats_start(bp);
पूर्ण

अटल व्योम bnx2x_bmac_stats_update(काष्ठा bnx2x *bp)
अणु
	काष्ठा host_port_stats *pstats = bnx2x_sp(bp, port_stats);
	काष्ठा bnx2x_eth_stats *estats = &bp->eth_stats;
	काष्ठा अणु
		u32 lo;
		u32 hi;
	पूर्ण dअगरf;

	अगर (CHIP_IS_E1x(bp)) अणु
		काष्ठा bmac1_stats *new = bnx2x_sp(bp, mac_stats.bmac1_stats);

		/* the macros below will use "bmac1_stats" type */
		UPDATE_STAT64(rx_stat_grerb, rx_stat_अगरhcinbaकरोctets);
		UPDATE_STAT64(rx_stat_grfcs, rx_stat_करोt3statsfcserrors);
		UPDATE_STAT64(rx_stat_grund, rx_stat_etherstatsundersizepkts);
		UPDATE_STAT64(rx_stat_grovr, rx_stat_करोt3statsframestooदीर्घ);
		UPDATE_STAT64(rx_stat_grfrg, rx_stat_etherstatsfragments);
		UPDATE_STAT64(rx_stat_grjbr, rx_stat_etherstatsjabbers);
		UPDATE_STAT64(rx_stat_grxcf, rx_stat_maccontrolframesreceived);
		UPDATE_STAT64(rx_stat_grxpf, rx_stat_xofख_स्थितिeentered);
		UPDATE_STAT64(rx_stat_grxpf, rx_stat_mac_xpf);

		UPDATE_STAT64(tx_stat_gtxpf, tx_stat_outxoffsent);
		UPDATE_STAT64(tx_stat_gtxpf, tx_stat_flowcontrolकरोne);
		UPDATE_STAT64(tx_stat_gt64, tx_stat_etherstatspkts64octets);
		UPDATE_STAT64(tx_stat_gt127,
				tx_stat_etherstatspkts65octetsto127octets);
		UPDATE_STAT64(tx_stat_gt255,
				tx_stat_etherstatspkts128octetsto255octets);
		UPDATE_STAT64(tx_stat_gt511,
				tx_stat_etherstatspkts256octetsto511octets);
		UPDATE_STAT64(tx_stat_gt1023,
				tx_stat_etherstatspkts512octetsto1023octets);
		UPDATE_STAT64(tx_stat_gt1518,
				tx_stat_etherstatspkts1024octetsto1522octets);
		UPDATE_STAT64(tx_stat_gt2047, tx_stat_mac_2047);
		UPDATE_STAT64(tx_stat_gt4095, tx_stat_mac_4095);
		UPDATE_STAT64(tx_stat_gt9216, tx_stat_mac_9216);
		UPDATE_STAT64(tx_stat_gt16383, tx_stat_mac_16383);
		UPDATE_STAT64(tx_stat_gterr,
				tx_stat_करोt3statsपूर्णांकernalmactransmiterrors);
		UPDATE_STAT64(tx_stat_gtufl, tx_stat_mac_ufl);

	पूर्ण अन्यथा अणु
		काष्ठा bmac2_stats *new = bnx2x_sp(bp, mac_stats.bmac2_stats);

		/* the macros below will use "bmac2_stats" type */
		UPDATE_STAT64(rx_stat_grerb, rx_stat_अगरhcinbaकरोctets);
		UPDATE_STAT64(rx_stat_grfcs, rx_stat_करोt3statsfcserrors);
		UPDATE_STAT64(rx_stat_grund, rx_stat_etherstatsundersizepkts);
		UPDATE_STAT64(rx_stat_grovr, rx_stat_करोt3statsframestooदीर्घ);
		UPDATE_STAT64(rx_stat_grfrg, rx_stat_etherstatsfragments);
		UPDATE_STAT64(rx_stat_grjbr, rx_stat_etherstatsjabbers);
		UPDATE_STAT64(rx_stat_grxcf, rx_stat_maccontrolframesreceived);
		UPDATE_STAT64(rx_stat_grxpf, rx_stat_xofख_स्थितिeentered);
		UPDATE_STAT64(rx_stat_grxpf, rx_stat_mac_xpf);
		UPDATE_STAT64(tx_stat_gtxpf, tx_stat_outxoffsent);
		UPDATE_STAT64(tx_stat_gtxpf, tx_stat_flowcontrolकरोne);
		UPDATE_STAT64(tx_stat_gt64, tx_stat_etherstatspkts64octets);
		UPDATE_STAT64(tx_stat_gt127,
				tx_stat_etherstatspkts65octetsto127octets);
		UPDATE_STAT64(tx_stat_gt255,
				tx_stat_etherstatspkts128octetsto255octets);
		UPDATE_STAT64(tx_stat_gt511,
				tx_stat_etherstatspkts256octetsto511octets);
		UPDATE_STAT64(tx_stat_gt1023,
				tx_stat_etherstatspkts512octetsto1023octets);
		UPDATE_STAT64(tx_stat_gt1518,
				tx_stat_etherstatspkts1024octetsto1522octets);
		UPDATE_STAT64(tx_stat_gt2047, tx_stat_mac_2047);
		UPDATE_STAT64(tx_stat_gt4095, tx_stat_mac_4095);
		UPDATE_STAT64(tx_stat_gt9216, tx_stat_mac_9216);
		UPDATE_STAT64(tx_stat_gt16383, tx_stat_mac_16383);
		UPDATE_STAT64(tx_stat_gterr,
				tx_stat_करोt3statsपूर्णांकernalmactransmiterrors);
		UPDATE_STAT64(tx_stat_gtufl, tx_stat_mac_ufl);

		/* collect PFC stats */
		pstats->pfc_frames_tx_hi = new->tx_stat_gtpp_hi;
		pstats->pfc_frames_tx_lo = new->tx_stat_gtpp_lo;

		pstats->pfc_frames_rx_hi = new->rx_stat_grpp_hi;
		pstats->pfc_frames_rx_lo = new->rx_stat_grpp_lo;
	पूर्ण

	estats->छोड़ो_frames_received_hi =
				pstats->mac_stx[1].rx_stat_mac_xpf_hi;
	estats->छोड़ो_frames_received_lo =
				pstats->mac_stx[1].rx_stat_mac_xpf_lo;

	estats->छोड़ो_frames_sent_hi =
				pstats->mac_stx[1].tx_stat_outxoffsent_hi;
	estats->छोड़ो_frames_sent_lo =
				pstats->mac_stx[1].tx_stat_outxoffsent_lo;

	estats->pfc_frames_received_hi =
				pstats->pfc_frames_rx_hi;
	estats->pfc_frames_received_lo =
				pstats->pfc_frames_rx_lo;
	estats->pfc_frames_sent_hi =
				pstats->pfc_frames_tx_hi;
	estats->pfc_frames_sent_lo =
				pstats->pfc_frames_tx_lo;
पूर्ण

अटल व्योम bnx2x_mstat_stats_update(काष्ठा bnx2x *bp)
अणु
	काष्ठा host_port_stats *pstats = bnx2x_sp(bp, port_stats);
	काष्ठा bnx2x_eth_stats *estats = &bp->eth_stats;

	काष्ठा mstat_stats *new = bnx2x_sp(bp, mac_stats.mstat_stats);

	ADD_STAT64(stats_rx.rx_grerb, rx_stat_अगरhcinbaकरोctets);
	ADD_STAT64(stats_rx.rx_grfcs, rx_stat_करोt3statsfcserrors);
	ADD_STAT64(stats_rx.rx_grund, rx_stat_etherstatsundersizepkts);
	ADD_STAT64(stats_rx.rx_grovr, rx_stat_करोt3statsframestooदीर्घ);
	ADD_STAT64(stats_rx.rx_grfrg, rx_stat_etherstatsfragments);
	ADD_STAT64(stats_rx.rx_grxcf, rx_stat_maccontrolframesreceived);
	ADD_STAT64(stats_rx.rx_grxpf, rx_stat_xofख_स्थितिeentered);
	ADD_STAT64(stats_rx.rx_grxpf, rx_stat_mac_xpf);
	ADD_STAT64(stats_tx.tx_gtxpf, tx_stat_outxoffsent);
	ADD_STAT64(stats_tx.tx_gtxpf, tx_stat_flowcontrolकरोne);

	/* collect pfc stats */
	ADD_64(pstats->pfc_frames_tx_hi, new->stats_tx.tx_gtxpp_hi,
		pstats->pfc_frames_tx_lo, new->stats_tx.tx_gtxpp_lo);
	ADD_64(pstats->pfc_frames_rx_hi, new->stats_rx.rx_grxpp_hi,
		pstats->pfc_frames_rx_lo, new->stats_rx.rx_grxpp_lo);

	ADD_STAT64(stats_tx.tx_gt64, tx_stat_etherstatspkts64octets);
	ADD_STAT64(stats_tx.tx_gt127,
			tx_stat_etherstatspkts65octetsto127octets);
	ADD_STAT64(stats_tx.tx_gt255,
			tx_stat_etherstatspkts128octetsto255octets);
	ADD_STAT64(stats_tx.tx_gt511,
			tx_stat_etherstatspkts256octetsto511octets);
	ADD_STAT64(stats_tx.tx_gt1023,
			tx_stat_etherstatspkts512octetsto1023octets);
	ADD_STAT64(stats_tx.tx_gt1518,
			tx_stat_etherstatspkts1024octetsto1522octets);
	ADD_STAT64(stats_tx.tx_gt2047, tx_stat_mac_2047);

	ADD_STAT64(stats_tx.tx_gt4095, tx_stat_mac_4095);
	ADD_STAT64(stats_tx.tx_gt9216, tx_stat_mac_9216);
	ADD_STAT64(stats_tx.tx_gt16383, tx_stat_mac_16383);

	ADD_STAT64(stats_tx.tx_gterr,
			tx_stat_करोt3statsपूर्णांकernalmactransmiterrors);
	ADD_STAT64(stats_tx.tx_gtufl, tx_stat_mac_ufl);

	estats->etherstatspkts1024octetsto1522octets_hi =
	    pstats->mac_stx[1].tx_stat_etherstatspkts1024octetsto1522octets_hi;
	estats->etherstatspkts1024octetsto1522octets_lo =
	    pstats->mac_stx[1].tx_stat_etherstatspkts1024octetsto1522octets_lo;

	estats->etherstatspktsover1522octets_hi =
	    pstats->mac_stx[1].tx_stat_mac_2047_hi;
	estats->etherstatspktsover1522octets_lo =
	    pstats->mac_stx[1].tx_stat_mac_2047_lo;

	ADD_64(estats->etherstatspktsover1522octets_hi,
	       pstats->mac_stx[1].tx_stat_mac_4095_hi,
	       estats->etherstatspktsover1522octets_lo,
	       pstats->mac_stx[1].tx_stat_mac_4095_lo);

	ADD_64(estats->etherstatspktsover1522octets_hi,
	       pstats->mac_stx[1].tx_stat_mac_9216_hi,
	       estats->etherstatspktsover1522octets_lo,
	       pstats->mac_stx[1].tx_stat_mac_9216_lo);

	ADD_64(estats->etherstatspktsover1522octets_hi,
	       pstats->mac_stx[1].tx_stat_mac_16383_hi,
	       estats->etherstatspktsover1522octets_lo,
	       pstats->mac_stx[1].tx_stat_mac_16383_lo);

	estats->छोड़ो_frames_received_hi =
				pstats->mac_stx[1].rx_stat_mac_xpf_hi;
	estats->छोड़ो_frames_received_lo =
				pstats->mac_stx[1].rx_stat_mac_xpf_lo;

	estats->छोड़ो_frames_sent_hi =
				pstats->mac_stx[1].tx_stat_outxoffsent_hi;
	estats->छोड़ो_frames_sent_lo =
				pstats->mac_stx[1].tx_stat_outxoffsent_lo;

	estats->pfc_frames_received_hi =
				pstats->pfc_frames_rx_hi;
	estats->pfc_frames_received_lo =
				pstats->pfc_frames_rx_lo;
	estats->pfc_frames_sent_hi =
				pstats->pfc_frames_tx_hi;
	estats->pfc_frames_sent_lo =
				pstats->pfc_frames_tx_lo;
पूर्ण

अटल व्योम bnx2x_emac_stats_update(काष्ठा bnx2x *bp)
अणु
	काष्ठा emac_stats *new = bnx2x_sp(bp, mac_stats.emac_stats);
	काष्ठा host_port_stats *pstats = bnx2x_sp(bp, port_stats);
	काष्ठा bnx2x_eth_stats *estats = &bp->eth_stats;

	UPDATE_EXTEND_STAT(rx_stat_अगरhcinbaकरोctets);
	UPDATE_EXTEND_STAT(tx_stat_अगरhcoutbaकरोctets);
	UPDATE_EXTEND_STAT(rx_stat_करोt3statsfcserrors);
	UPDATE_EXTEND_STAT(rx_stat_करोt3statsalignmenterrors);
	UPDATE_EXTEND_STAT(rx_stat_करोt3statscarriersenseerrors);
	UPDATE_EXTEND_STAT(rx_stat_falsecarriererrors);
	UPDATE_EXTEND_STAT(rx_stat_etherstatsundersizepkts);
	UPDATE_EXTEND_STAT(rx_stat_करोt3statsframestooदीर्घ);
	UPDATE_EXTEND_STAT(rx_stat_etherstatsfragments);
	UPDATE_EXTEND_STAT(rx_stat_etherstatsjabbers);
	UPDATE_EXTEND_STAT(rx_stat_maccontrolframesreceived);
	UPDATE_EXTEND_STAT(rx_stat_xofख_स्थितिeentered);
	UPDATE_EXTEND_STAT(rx_stat_xonछोड़ोframesreceived);
	UPDATE_EXTEND_STAT(rx_stat_xoffछोड़ोframesreceived);
	UPDATE_EXTEND_STAT(tx_stat_outxonsent);
	UPDATE_EXTEND_STAT(tx_stat_outxoffsent);
	UPDATE_EXTEND_STAT(tx_stat_flowcontrolकरोne);
	UPDATE_EXTEND_STAT(tx_stat_etherstatscollisions);
	UPDATE_EXTEND_STAT(tx_stat_करोt3statssinglecollisionframes);
	UPDATE_EXTEND_STAT(tx_stat_करोt3statsmultiplecollisionframes);
	UPDATE_EXTEND_STAT(tx_stat_करोt3statsdeferredtransmissions);
	UPDATE_EXTEND_STAT(tx_stat_करोt3statsexcessivecollisions);
	UPDATE_EXTEND_STAT(tx_stat_करोt3statslatecollisions);
	UPDATE_EXTEND_STAT(tx_stat_etherstatspkts64octets);
	UPDATE_EXTEND_STAT(tx_stat_etherstatspkts65octetsto127octets);
	UPDATE_EXTEND_STAT(tx_stat_etherstatspkts128octetsto255octets);
	UPDATE_EXTEND_STAT(tx_stat_etherstatspkts256octetsto511octets);
	UPDATE_EXTEND_STAT(tx_stat_etherstatspkts512octetsto1023octets);
	UPDATE_EXTEND_STAT(tx_stat_etherstatspkts1024octetsto1522octets);
	UPDATE_EXTEND_STAT(tx_stat_etherstatspktsover1522octets);
	UPDATE_EXTEND_STAT(tx_stat_करोt3statsपूर्णांकernalmactransmiterrors);

	estats->छोड़ो_frames_received_hi =
			pstats->mac_stx[1].rx_stat_xonछोड़ोframesreceived_hi;
	estats->छोड़ो_frames_received_lo =
			pstats->mac_stx[1].rx_stat_xonछोड़ोframesreceived_lo;
	ADD_64(estats->छोड़ो_frames_received_hi,
	       pstats->mac_stx[1].rx_stat_xoffछोड़ोframesreceived_hi,
	       estats->छोड़ो_frames_received_lo,
	       pstats->mac_stx[1].rx_stat_xoffछोड़ोframesreceived_lo);

	estats->छोड़ो_frames_sent_hi =
			pstats->mac_stx[1].tx_stat_outxonsent_hi;
	estats->छोड़ो_frames_sent_lo =
			pstats->mac_stx[1].tx_stat_outxonsent_lo;
	ADD_64(estats->छोड़ो_frames_sent_hi,
	       pstats->mac_stx[1].tx_stat_outxoffsent_hi,
	       estats->छोड़ो_frames_sent_lo,
	       pstats->mac_stx[1].tx_stat_outxoffsent_lo);
पूर्ण

अटल पूर्णांक bnx2x_hw_stats_update(काष्ठा bnx2x *bp)
अणु
	काष्ठा nig_stats *new = bnx2x_sp(bp, nig_stats);
	काष्ठा nig_stats *old = &(bp->port.old_nig_stats);
	काष्ठा host_port_stats *pstats = bnx2x_sp(bp, port_stats);
	काष्ठा bnx2x_eth_stats *estats = &bp->eth_stats;
	काष्ठा अणु
		u32 lo;
		u32 hi;
	पूर्ण dअगरf;

	चयन (bp->link_vars.mac_type) अणु
	हाल MAC_TYPE_BMAC:
		bnx2x_bmac_stats_update(bp);
		अवरोध;

	हाल MAC_TYPE_EMAC:
		bnx2x_emac_stats_update(bp);
		अवरोध;

	हाल MAC_TYPE_UMAC:
	हाल MAC_TYPE_XMAC:
		bnx2x_mstat_stats_update(bp);
		अवरोध;

	हाल MAC_TYPE_NONE: /* unreached */
		DP(BNX2X_MSG_STATS,
		   "stats updated by DMAE but no MAC active\n");
		वापस -1;

	शेष: /* unreached */
		BNX2X_ERR("Unknown MAC type\n");
	पूर्ण

	ADD_EXTEND_64(pstats->brb_drop_hi, pstats->brb_drop_lo,
		      new->brb_discard - old->brb_discard);
	ADD_EXTEND_64(estats->brb_truncate_hi, estats->brb_truncate_lo,
		      new->brb_truncate - old->brb_truncate);

	अगर (!CHIP_IS_E3(bp)) अणु
		UPDATE_STAT64_NIG(egress_mac_pkt0,
					etherstatspkts1024octetsto1522octets);
		UPDATE_STAT64_NIG(egress_mac_pkt1,
					etherstatspktsover1522octets);
	पूर्ण

	स_नकल(old, new, माप(काष्ठा nig_stats));

	स_नकल(&(estats->rx_stat_अगरhcinbaकरोctets_hi), &(pstats->mac_stx[1]),
	       माप(काष्ठा mac_stx));
	estats->brb_drop_hi = pstats->brb_drop_hi;
	estats->brb_drop_lo = pstats->brb_drop_lo;

	pstats->host_port_stats_counter++;

	अगर (CHIP_IS_E3(bp)) अणु
		u32 lpi_reg = BP_PORT(bp) ? MISC_REG_CPMU_LP_SM_ENT_CNT_P1
					  : MISC_REG_CPMU_LP_SM_ENT_CNT_P0;
		estats->eee_tx_lpi += REG_RD(bp, lpi_reg);
	पूर्ण

	अगर (!BP_NOMCP(bp)) अणु
		u32 nig_समयr_max =
			SHMEM_RD(bp, port_mb[BP_PORT(bp)].stat_nig_समयr);
		अगर (nig_समयr_max != estats->nig_समयr_max) अणु
			estats->nig_समयr_max = nig_समयr_max;
			BNX2X_ERR("NIG timer max (%u)\n",
				  estats->nig_समयr_max);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक bnx2x_storm_stats_validate_counters(काष्ठा bnx2x *bp)
अणु
	काष्ठा stats_counter *counters = &bp->fw_stats_data->storm_counters;
	u16 cur_stats_counter;
	/* Make sure we use the value of the counter
	 * used क्रम sending the last stats ramrod.
	 */
	cur_stats_counter = bp->stats_counter - 1;

	/* are storm stats valid? */
	अगर (le16_to_cpu(counters->xstats_counter) != cur_stats_counter) अणु
		DP(BNX2X_MSG_STATS,
		   "stats not updated by xstorm  xstorm counter (0x%x) != stats_counter (0x%x)\n",
		   le16_to_cpu(counters->xstats_counter), bp->stats_counter);
		वापस -EAGAIN;
	पूर्ण

	अगर (le16_to_cpu(counters->ustats_counter) != cur_stats_counter) अणु
		DP(BNX2X_MSG_STATS,
		   "stats not updated by ustorm  ustorm counter (0x%x) != stats_counter (0x%x)\n",
		   le16_to_cpu(counters->ustats_counter), bp->stats_counter);
		वापस -EAGAIN;
	पूर्ण

	अगर (le16_to_cpu(counters->cstats_counter) != cur_stats_counter) अणु
		DP(BNX2X_MSG_STATS,
		   "stats not updated by cstorm  cstorm counter (0x%x) != stats_counter (0x%x)\n",
		   le16_to_cpu(counters->cstats_counter), bp->stats_counter);
		वापस -EAGAIN;
	पूर्ण

	अगर (le16_to_cpu(counters->tstats_counter) != cur_stats_counter) अणु
		DP(BNX2X_MSG_STATS,
		   "stats not updated by tstorm  tstorm counter (0x%x) != stats_counter (0x%x)\n",
		   le16_to_cpu(counters->tstats_counter), bp->stats_counter);
		वापस -EAGAIN;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक bnx2x_storm_stats_update(काष्ठा bnx2x *bp)
अणु
	काष्ठा tstorm_per_port_stats *tport =
				&bp->fw_stats_data->port.tstorm_port_statistics;
	काष्ठा tstorm_per_pf_stats *tfunc =
				&bp->fw_stats_data->pf.tstorm_pf_statistics;
	काष्ठा host_func_stats *ख_स्थितिs = &bp->func_stats;
	काष्ठा bnx2x_eth_stats *estats = &bp->eth_stats;
	काष्ठा bnx2x_eth_stats_old *estats_old = &bp->eth_stats_old;
	पूर्णांक i;

	/* vfs stat counter is managed by pf */
	अगर (IS_PF(bp) && bnx2x_storm_stats_validate_counters(bp))
		वापस -EAGAIN;

	estats->error_bytes_received_hi = 0;
	estats->error_bytes_received_lo = 0;

	क्रम_each_eth_queue(bp, i) अणु
		काष्ठा bnx2x_fastpath *fp = &bp->fp[i];
		काष्ठा tstorm_per_queue_stats *tclient =
			&bp->fw_stats_data->queue_stats[i].
			tstorm_queue_statistics;
		काष्ठा tstorm_per_queue_stats *old_tclient =
			&bnx2x_fp_stats(bp, fp)->old_tclient;
		काष्ठा ustorm_per_queue_stats *uclient =
			&bp->fw_stats_data->queue_stats[i].
			ustorm_queue_statistics;
		काष्ठा ustorm_per_queue_stats *old_uclient =
			&bnx2x_fp_stats(bp, fp)->old_uclient;
		काष्ठा xstorm_per_queue_stats *xclient =
			&bp->fw_stats_data->queue_stats[i].
			xstorm_queue_statistics;
		काष्ठा xstorm_per_queue_stats *old_xclient =
			&bnx2x_fp_stats(bp, fp)->old_xclient;
		काष्ठा bnx2x_eth_q_stats *qstats =
			&bnx2x_fp_stats(bp, fp)->eth_q_stats;
		काष्ठा bnx2x_eth_q_stats_old *qstats_old =
			&bnx2x_fp_stats(bp, fp)->eth_q_stats_old;

		u32 dअगरf;

		DP(BNX2X_MSG_STATS, "queue[%d]: ucast_sent 0x%x, bcast_sent 0x%x mcast_sent 0x%x\n",
		   i, xclient->ucast_pkts_sent,
		   xclient->bcast_pkts_sent, xclient->mcast_pkts_sent);

		DP(BNX2X_MSG_STATS, "---------------\n");

		UPDATE_QSTAT(tclient->rcv_bcast_bytes,
			     total_broadcast_bytes_received);
		UPDATE_QSTAT(tclient->rcv_mcast_bytes,
			     total_multicast_bytes_received);
		UPDATE_QSTAT(tclient->rcv_ucast_bytes,
			     total_unicast_bytes_received);

		/*
		 * sum to total_bytes_received all
		 * unicast/multicast/broadcast
		 */
		qstats->total_bytes_received_hi =
			qstats->total_broadcast_bytes_received_hi;
		qstats->total_bytes_received_lo =
			qstats->total_broadcast_bytes_received_lo;

		ADD_64(qstats->total_bytes_received_hi,
		       qstats->total_multicast_bytes_received_hi,
		       qstats->total_bytes_received_lo,
		       qstats->total_multicast_bytes_received_lo);

		ADD_64(qstats->total_bytes_received_hi,
		       qstats->total_unicast_bytes_received_hi,
		       qstats->total_bytes_received_lo,
		       qstats->total_unicast_bytes_received_lo);

		qstats->valid_bytes_received_hi =
					qstats->total_bytes_received_hi;
		qstats->valid_bytes_received_lo =
					qstats->total_bytes_received_lo;

		UPDATE_EXTEND_TSTAT(rcv_ucast_pkts,
					total_unicast_packets_received);
		UPDATE_EXTEND_TSTAT(rcv_mcast_pkts,
					total_multicast_packets_received);
		UPDATE_EXTEND_TSTAT(rcv_bcast_pkts,
					total_broadcast_packets_received);
		UPDATE_EXTEND_E_TSTAT(pkts_too_big_discard,
				      etherstatsoverrsizepkts, 32);
		UPDATE_EXTEND_E_TSTAT(no_buff_discard, no_buff_discard, 16);

		SUB_EXTEND_USTAT(ucast_no_buff_pkts,
					total_unicast_packets_received);
		SUB_EXTEND_USTAT(mcast_no_buff_pkts,
					total_multicast_packets_received);
		SUB_EXTEND_USTAT(bcast_no_buff_pkts,
					total_broadcast_packets_received);
		UPDATE_EXTEND_E_USTAT(ucast_no_buff_pkts, no_buff_discard);
		UPDATE_EXTEND_E_USTAT(mcast_no_buff_pkts, no_buff_discard);
		UPDATE_EXTEND_E_USTAT(bcast_no_buff_pkts, no_buff_discard);

		UPDATE_QSTAT(xclient->bcast_bytes_sent,
			     total_broadcast_bytes_transmitted);
		UPDATE_QSTAT(xclient->mcast_bytes_sent,
			     total_multicast_bytes_transmitted);
		UPDATE_QSTAT(xclient->ucast_bytes_sent,
			     total_unicast_bytes_transmitted);

		/*
		 * sum to total_bytes_transmitted all
		 * unicast/multicast/broadcast
		 */
		qstats->total_bytes_transmitted_hi =
				qstats->total_unicast_bytes_transmitted_hi;
		qstats->total_bytes_transmitted_lo =
				qstats->total_unicast_bytes_transmitted_lo;

		ADD_64(qstats->total_bytes_transmitted_hi,
		       qstats->total_broadcast_bytes_transmitted_hi,
		       qstats->total_bytes_transmitted_lo,
		       qstats->total_broadcast_bytes_transmitted_lo);

		ADD_64(qstats->total_bytes_transmitted_hi,
		       qstats->total_multicast_bytes_transmitted_hi,
		       qstats->total_bytes_transmitted_lo,
		       qstats->total_multicast_bytes_transmitted_lo);

		UPDATE_EXTEND_XSTAT(ucast_pkts_sent,
					total_unicast_packets_transmitted);
		UPDATE_EXTEND_XSTAT(mcast_pkts_sent,
					total_multicast_packets_transmitted);
		UPDATE_EXTEND_XSTAT(bcast_pkts_sent,
					total_broadcast_packets_transmitted);

		UPDATE_EXTEND_TSTAT(checksum_discard,
				    total_packets_received_checksum_discarded);
		UPDATE_EXTEND_TSTAT(ttl0_discard,
				    total_packets_received_ttl0_discarded);

		UPDATE_EXTEND_XSTAT(error_drop_pkts,
				    total_transmitted_dropped_packets_error);

		/* TPA aggregations completed */
		UPDATE_EXTEND_E_USTAT(coalesced_events, total_tpa_aggregations);
		/* Number of network frames aggregated by TPA */
		UPDATE_EXTEND_E_USTAT(coalesced_pkts,
				      total_tpa_aggregated_frames);
		/* Total number of bytes in completed TPA aggregations */
		UPDATE_QSTAT(uclient->coalesced_bytes, total_tpa_bytes);

		UPDATE_ESTAT_QSTAT_64(total_tpa_bytes);

		UPDATE_FSTAT_QSTAT(total_bytes_received);
		UPDATE_FSTAT_QSTAT(total_bytes_transmitted);
		UPDATE_FSTAT_QSTAT(total_unicast_packets_received);
		UPDATE_FSTAT_QSTAT(total_multicast_packets_received);
		UPDATE_FSTAT_QSTAT(total_broadcast_packets_received);
		UPDATE_FSTAT_QSTAT(total_unicast_packets_transmitted);
		UPDATE_FSTAT_QSTAT(total_multicast_packets_transmitted);
		UPDATE_FSTAT_QSTAT(total_broadcast_packets_transmitted);
		UPDATE_FSTAT_QSTAT(valid_bytes_received);
	पूर्ण

	ADD_64(estats->total_bytes_received_hi,
	       estats->rx_stat_अगरhcinbaकरोctets_hi,
	       estats->total_bytes_received_lo,
	       estats->rx_stat_अगरhcinbaकरोctets_lo);

	ADD_64_LE(estats->total_bytes_received_hi,
		  tfunc->rcv_error_bytes.hi,
		  estats->total_bytes_received_lo,
		  tfunc->rcv_error_bytes.lo);

	ADD_64_LE(estats->error_bytes_received_hi,
		  tfunc->rcv_error_bytes.hi,
		  estats->error_bytes_received_lo,
		  tfunc->rcv_error_bytes.lo);

	UPDATE_ESTAT(etherstatsoverrsizepkts, rx_stat_करोt3statsframestooदीर्घ);

	ADD_64(estats->error_bytes_received_hi,
	       estats->rx_stat_अगरhcinbaकरोctets_hi,
	       estats->error_bytes_received_lo,
	       estats->rx_stat_अगरhcinbaकरोctets_lo);

	अगर (bp->port.pmf) अणु
		काष्ठा bnx2x_fw_port_stats_old *fwstats = &bp->fw_stats_old;
		UPDATE_FW_STAT(mac_filter_discard);
		UPDATE_FW_STAT(mf_tag_discard);
		UPDATE_FW_STAT(brb_truncate_discard);
		UPDATE_FW_STAT(mac_discard);
	पूर्ण

	ख_स्थितिs->host_func_stats_start = ++ख_स्थितिs->host_func_stats_end;

	bp->stats_pending = 0;

	वापस 0;
पूर्ण

अटल व्योम bnx2x_net_stats_update(काष्ठा bnx2x *bp)
अणु
	काष्ठा bnx2x_eth_stats *estats = &bp->eth_stats;
	काष्ठा net_device_stats *nstats = &bp->dev->stats;
	अचिन्हित दीर्घ पंचांगp;
	पूर्णांक i;

	nstats->rx_packets =
		bnx2x_hilo(&estats->total_unicast_packets_received_hi) +
		bnx2x_hilo(&estats->total_multicast_packets_received_hi) +
		bnx2x_hilo(&estats->total_broadcast_packets_received_hi);

	nstats->tx_packets =
		bnx2x_hilo(&estats->total_unicast_packets_transmitted_hi) +
		bnx2x_hilo(&estats->total_multicast_packets_transmitted_hi) +
		bnx2x_hilo(&estats->total_broadcast_packets_transmitted_hi);

	nstats->rx_bytes = bnx2x_hilo(&estats->total_bytes_received_hi);

	nstats->tx_bytes = bnx2x_hilo(&estats->total_bytes_transmitted_hi);

	पंचांगp = estats->mac_discard;
	क्रम_each_rx_queue(bp, i) अणु
		काष्ठा tstorm_per_queue_stats *old_tclient =
			&bp->fp_stats[i].old_tclient;
		पंचांगp += le32_to_cpu(old_tclient->checksum_discard);
	पूर्ण
	nstats->rx_dropped = पंचांगp + bp->net_stats_old.rx_dropped;

	nstats->tx_dropped = 0;

	nstats->multicast =
		bnx2x_hilo(&estats->total_multicast_packets_received_hi);

	nstats->collisions =
		bnx2x_hilo(&estats->tx_stat_etherstatscollisions_hi);

	nstats->rx_length_errors =
		bnx2x_hilo(&estats->rx_stat_etherstatsundersizepkts_hi) +
		bnx2x_hilo(&estats->etherstatsoverrsizepkts_hi);
	nstats->rx_over_errors = bnx2x_hilo(&estats->brb_drop_hi) +
				 bnx2x_hilo(&estats->brb_truncate_hi);
	nstats->rx_crc_errors =
		bnx2x_hilo(&estats->rx_stat_करोt3statsfcserrors_hi);
	nstats->rx_frame_errors =
		bnx2x_hilo(&estats->rx_stat_करोt3statsalignmenterrors_hi);
	nstats->rx_fअगरo_errors = bnx2x_hilo(&estats->no_buff_discard_hi);
	nstats->rx_missed_errors = 0;

	nstats->rx_errors = nstats->rx_length_errors +
			    nstats->rx_over_errors +
			    nstats->rx_crc_errors +
			    nstats->rx_frame_errors +
			    nstats->rx_fअगरo_errors +
			    nstats->rx_missed_errors;

	nstats->tx_पातed_errors =
		bnx2x_hilo(&estats->tx_stat_करोt3statslatecollisions_hi) +
		bnx2x_hilo(&estats->tx_stat_करोt3statsexcessivecollisions_hi);
	nstats->tx_carrier_errors =
		bnx2x_hilo(&estats->rx_stat_करोt3statscarriersenseerrors_hi);
	nstats->tx_fअगरo_errors = 0;
	nstats->tx_heartbeat_errors = 0;
	nstats->tx_winकरोw_errors = 0;

	nstats->tx_errors = nstats->tx_पातed_errors +
			    nstats->tx_carrier_errors +
	    bnx2x_hilo(&estats->tx_stat_करोt3statsपूर्णांकernalmactransmiterrors_hi);
पूर्ण

अटल व्योम bnx2x_drv_stats_update(काष्ठा bnx2x *bp)
अणु
	काष्ठा bnx2x_eth_stats *estats = &bp->eth_stats;
	पूर्णांक i;

	क्रम_each_queue(bp, i) अणु
		काष्ठा bnx2x_eth_q_stats *qstats = &bp->fp_stats[i].eth_q_stats;
		काष्ठा bnx2x_eth_q_stats_old *qstats_old =
			&bp->fp_stats[i].eth_q_stats_old;

		UPDATE_ESTAT_QSTAT(driver_xoff);
		UPDATE_ESTAT_QSTAT(rx_err_discard_pkt);
		UPDATE_ESTAT_QSTAT(rx_skb_alloc_failed);
		UPDATE_ESTAT_QSTAT(hw_csum_err);
		UPDATE_ESTAT_QSTAT(driver_filtered_tx_pkt);
	पूर्ण
पूर्ण

अटल bool bnx2x_edebug_stats_stopped(काष्ठा bnx2x *bp)
अणु
	u32 val;

	अगर (SHMEM2_HAS(bp, edebug_driver_अगर[1])) अणु
		val = SHMEM2_RD(bp, edebug_driver_अगर[1]);

		अगर (val == EDEBUG_DRIVER_IF_OP_CODE_DISABLE_STAT)
			वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल व्योम bnx2x_stats_update(काष्ठा bnx2x *bp)
अणु
	u32 *stats_comp = bnx2x_sp(bp, stats_comp);

	अगर (bnx2x_edebug_stats_stopped(bp))
		वापस;

	अगर (IS_PF(bp)) अणु
		अगर (*stats_comp != DMAE_COMP_VAL)
			वापस;

		अगर (bp->port.pmf)
			bnx2x_hw_stats_update(bp);

		अगर (bnx2x_storm_stats_update(bp)) अणु
			अगर (bp->stats_pending++ == 3) अणु
				BNX2X_ERR("storm stats were not updated for 3 times\n");
				bnx2x_panic();
			पूर्ण
			वापस;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* vf करोesn't collect HW statistics, and doesn't get completions
		 * perक्रमm only update
		 */
		bnx2x_storm_stats_update(bp);
	पूर्ण

	bnx2x_net_stats_update(bp);
	bnx2x_drv_stats_update(bp);

	/* vf is करोne */
	अगर (IS_VF(bp))
		वापस;

	अगर (netअगर_msg_समयr(bp)) अणु
		काष्ठा bnx2x_eth_stats *estats = &bp->eth_stats;

		netdev_dbg(bp->dev, "brb drops %u  brb truncate %u\n",
		       estats->brb_drop_lo, estats->brb_truncate_lo);
	पूर्ण

	bnx2x_hw_stats_post(bp);
	bnx2x_storm_stats_post(bp);
पूर्ण

अटल व्योम bnx2x_port_stats_stop(काष्ठा bnx2x *bp)
अणु
	काष्ठा dmae_command *dmae;
	u32 opcode;
	पूर्णांक loader_idx = PMF_DMAE_C(bp);
	u32 *stats_comp = bnx2x_sp(bp, stats_comp);

	bp->executer_idx = 0;

	opcode = bnx2x_dmae_opcode(bp, DMAE_SRC_PCI, DMAE_DST_GRC, false, 0);

	अगर (bp->port.port_stx) अणु

		dmae = bnx2x_sp(bp, dmae[bp->executer_idx++]);
		अगर (bp->func_stx)
			dmae->opcode = bnx2x_dmae_opcode_add_comp(
						opcode, DMAE_COMP_GRC);
		अन्यथा
			dmae->opcode = bnx2x_dmae_opcode_add_comp(
						opcode, DMAE_COMP_PCI);

		dmae->src_addr_lo = U64_LO(bnx2x_sp_mapping(bp, port_stats));
		dmae->src_addr_hi = U64_HI(bnx2x_sp_mapping(bp, port_stats));
		dmae->dst_addr_lo = bp->port.port_stx >> 2;
		dmae->dst_addr_hi = 0;
		dmae->len = bnx2x_get_port_stats_dma_len(bp);
		अगर (bp->func_stx) अणु
			dmae->comp_addr_lo = dmae_reg_go_c[loader_idx] >> 2;
			dmae->comp_addr_hi = 0;
			dmae->comp_val = 1;
		पूर्ण अन्यथा अणु
			dmae->comp_addr_lo =
				U64_LO(bnx2x_sp_mapping(bp, stats_comp));
			dmae->comp_addr_hi =
				U64_HI(bnx2x_sp_mapping(bp, stats_comp));
			dmae->comp_val = DMAE_COMP_VAL;

			*stats_comp = 0;
		पूर्ण
	पूर्ण

	अगर (bp->func_stx) अणु

		dmae = bnx2x_sp(bp, dmae[bp->executer_idx++]);
		dmae->opcode =
			bnx2x_dmae_opcode_add_comp(opcode, DMAE_COMP_PCI);
		dmae->src_addr_lo = U64_LO(bnx2x_sp_mapping(bp, func_stats));
		dmae->src_addr_hi = U64_HI(bnx2x_sp_mapping(bp, func_stats));
		dmae->dst_addr_lo = bp->func_stx >> 2;
		dmae->dst_addr_hi = 0;
		dmae->len = माप(काष्ठा host_func_stats) >> 2;
		dmae->comp_addr_lo = U64_LO(bnx2x_sp_mapping(bp, stats_comp));
		dmae->comp_addr_hi = U64_HI(bnx2x_sp_mapping(bp, stats_comp));
		dmae->comp_val = DMAE_COMP_VAL;

		*stats_comp = 0;
	पूर्ण
पूर्ण

अटल व्योम bnx2x_stats_stop(काष्ठा bnx2x *bp)
अणु
	bool update = false;

	bnx2x_stats_comp(bp);

	अगर (bp->port.pmf)
		update = (bnx2x_hw_stats_update(bp) == 0);

	update |= (bnx2x_storm_stats_update(bp) == 0);

	अगर (update) अणु
		bnx2x_net_stats_update(bp);

		अगर (bp->port.pmf)
			bnx2x_port_stats_stop(bp);

		bnx2x_hw_stats_post(bp);
		bnx2x_stats_comp(bp);
	पूर्ण
पूर्ण

अटल व्योम bnx2x_stats_करो_nothing(काष्ठा bnx2x *bp)
अणु
पूर्ण

अटल स्थिर काष्ठा अणु
	व्योम (*action)(काष्ठा bnx2x *bp);
	क्रमागत bnx2x_stats_state next_state;
पूर्ण bnx2x_stats_sपंचांग[STATS_STATE_MAX][STATS_EVENT_MAX] = अणु
/* state	event	*/
अणु
/* DISABLED	PMF	*/ अणुbnx2x_stats_pmf_update, STATS_STATE_DISABLEDपूर्ण,
/*		LINK_UP	*/ अणुbnx2x_stats_start,      STATS_STATE_ENABLEDपूर्ण,
/*		UPDATE	*/ अणुbnx2x_stats_करो_nothing, STATS_STATE_DISABLEDपूर्ण,
/*		STOP	*/ अणुbnx2x_stats_करो_nothing, STATS_STATE_DISABLEDपूर्ण
पूर्ण,
अणु
/* ENABLED	PMF	*/ अणुbnx2x_stats_pmf_start,  STATS_STATE_ENABLEDपूर्ण,
/*		LINK_UP	*/ अणुbnx2x_stats_restart,    STATS_STATE_ENABLEDपूर्ण,
/*		UPDATE	*/ अणुbnx2x_stats_update,     STATS_STATE_ENABLEDपूर्ण,
/*		STOP	*/ अणुbnx2x_stats_stop,       STATS_STATE_DISABLEDपूर्ण
पूर्ण
पूर्ण;

व्योम bnx2x_stats_handle(काष्ठा bnx2x *bp, क्रमागत bnx2x_stats_event event)
अणु
	क्रमागत bnx2x_stats_state state = bp->stats_state;

	अगर (unlikely(bp->panic))
		वापस;

	/* Statistics update run from समयr context, and we करोn't want to stop
	 * that context in हाल someone is in the middle of a transition.
	 * For other events, रुको a bit until lock is taken.
	 */
	अगर (करोwn_trylock(&bp->stats_lock)) अणु
		अगर (event == STATS_EVENT_UPDATE)
			वापस;

		DP(BNX2X_MSG_STATS,
		   "Unlikely stats' lock contention [event %d]\n", event);
		अगर (unlikely(करोwn_समयout(&bp->stats_lock, HZ / 10))) अणु
			BNX2X_ERR("Failed to take stats lock [event %d]\n",
				  event);
			वापस;
		पूर्ण
	पूर्ण

	bnx2x_stats_sपंचांग[state][event].action(bp);
	bp->stats_state = bnx2x_stats_sपंचांग[state][event].next_state;

	up(&bp->stats_lock);

	अगर ((event != STATS_EVENT_UPDATE) || netअगर_msg_समयr(bp))
		DP(BNX2X_MSG_STATS, "state %d -> event %d -> state %d\n",
		   state, event, bp->stats_state);
पूर्ण

अटल व्योम bnx2x_port_stats_base_init(काष्ठा bnx2x *bp)
अणु
	काष्ठा dmae_command *dmae;
	u32 *stats_comp = bnx2x_sp(bp, stats_comp);

	/* sanity */
	अगर (!bp->port.pmf || !bp->port.port_stx) अणु
		BNX2X_ERR("BUG!\n");
		वापस;
	पूर्ण

	bp->executer_idx = 0;

	dmae = bnx2x_sp(bp, dmae[bp->executer_idx++]);
	dmae->opcode = bnx2x_dmae_opcode(bp, DMAE_SRC_PCI, DMAE_DST_GRC,
					 true, DMAE_COMP_PCI);
	dmae->src_addr_lo = U64_LO(bnx2x_sp_mapping(bp, port_stats));
	dmae->src_addr_hi = U64_HI(bnx2x_sp_mapping(bp, port_stats));
	dmae->dst_addr_lo = bp->port.port_stx >> 2;
	dmae->dst_addr_hi = 0;
	dmae->len = bnx2x_get_port_stats_dma_len(bp);
	dmae->comp_addr_lo = U64_LO(bnx2x_sp_mapping(bp, stats_comp));
	dmae->comp_addr_hi = U64_HI(bnx2x_sp_mapping(bp, stats_comp));
	dmae->comp_val = DMAE_COMP_VAL;

	*stats_comp = 0;
	bnx2x_hw_stats_post(bp);
	bnx2x_stats_comp(bp);
पूर्ण

/* This function will prepare the statistics ramrod data the way
 * we will only have to increment the statistics counter and
 * send the ramrod each समय we have to.
 */
अटल व्योम bnx2x_prep_fw_stats_req(काष्ठा bnx2x *bp)
अणु
	पूर्णांक i;
	पूर्णांक first_queue_query_index;
	काष्ठा stats_query_header *stats_hdr = &bp->fw_stats_req->hdr;

	dma_addr_t cur_data_offset;
	काष्ठा stats_query_entry *cur_query_entry;

	stats_hdr->cmd_num = bp->fw_stats_num;
	stats_hdr->drv_stats_counter = 0;

	/* storm_counters काष्ठा contains the counters of completed
	 * statistics requests per storm which are incremented by FW
	 * each समय it completes hadning a statistics ramrod. We will
	 * check these counters in the समयr handler and discard a
	 * (statistics) ramrod completion.
	 */
	cur_data_offset = bp->fw_stats_data_mapping +
		दुरत्व(काष्ठा bnx2x_fw_stats_data, storm_counters);

	stats_hdr->stats_counters_addrs.hi =
		cpu_to_le32(U64_HI(cur_data_offset));
	stats_hdr->stats_counters_addrs.lo =
		cpu_to_le32(U64_LO(cur_data_offset));

	/* prepare to the first stats ramrod (will be completed with
	 * the counters equal to zero) - init counters to somethig dअगरferent.
	 */
	स_रखो(&bp->fw_stats_data->storm_counters, 0xff,
	       माप(काष्ठा stats_counter));

	/**** Port FW statistics data ****/
	cur_data_offset = bp->fw_stats_data_mapping +
		दुरत्व(काष्ठा bnx2x_fw_stats_data, port);

	cur_query_entry = &bp->fw_stats_req->query[BNX2X_PORT_QUERY_IDX];

	cur_query_entry->kind = STATS_TYPE_PORT;
	/* For port query index is a DONT CARE */
	cur_query_entry->index = BP_PORT(bp);
	/* For port query funcID is a DONT CARE */
	cur_query_entry->funcID = cpu_to_le16(BP_FUNC(bp));
	cur_query_entry->address.hi = cpu_to_le32(U64_HI(cur_data_offset));
	cur_query_entry->address.lo = cpu_to_le32(U64_LO(cur_data_offset));

	/**** PF FW statistics data ****/
	cur_data_offset = bp->fw_stats_data_mapping +
		दुरत्व(काष्ठा bnx2x_fw_stats_data, pf);

	cur_query_entry = &bp->fw_stats_req->query[BNX2X_PF_QUERY_IDX];

	cur_query_entry->kind = STATS_TYPE_PF;
	/* For PF query index is a DONT CARE */
	cur_query_entry->index = BP_PORT(bp);
	cur_query_entry->funcID = cpu_to_le16(BP_FUNC(bp));
	cur_query_entry->address.hi = cpu_to_le32(U64_HI(cur_data_offset));
	cur_query_entry->address.lo = cpu_to_le32(U64_LO(cur_data_offset));

	/**** FCoE FW statistics data ****/
	अगर (!NO_FCOE(bp)) अणु
		cur_data_offset = bp->fw_stats_data_mapping +
			दुरत्व(काष्ठा bnx2x_fw_stats_data, fcoe);

		cur_query_entry =
			&bp->fw_stats_req->query[BNX2X_FCOE_QUERY_IDX];

		cur_query_entry->kind = STATS_TYPE_FCOE;
		/* For FCoE query index is a DONT CARE */
		cur_query_entry->index = BP_PORT(bp);
		cur_query_entry->funcID = cpu_to_le16(BP_FUNC(bp));
		cur_query_entry->address.hi =
			cpu_to_le32(U64_HI(cur_data_offset));
		cur_query_entry->address.lo =
			cpu_to_le32(U64_LO(cur_data_offset));
	पूर्ण

	/**** Clients' queries ****/
	cur_data_offset = bp->fw_stats_data_mapping +
		दुरत्व(काष्ठा bnx2x_fw_stats_data, queue_stats);

	/* first queue query index depends whether FCoE offloaded request will
	 * be included in the ramrod
	 */
	अगर (!NO_FCOE(bp))
		first_queue_query_index = BNX2X_FIRST_QUEUE_QUERY_IDX;
	अन्यथा
		first_queue_query_index = BNX2X_FIRST_QUEUE_QUERY_IDX - 1;

	क्रम_each_eth_queue(bp, i) अणु
		cur_query_entry =
			&bp->fw_stats_req->
					query[first_queue_query_index + i];

		cur_query_entry->kind = STATS_TYPE_QUEUE;
		cur_query_entry->index = bnx2x_stats_id(&bp->fp[i]);
		cur_query_entry->funcID = cpu_to_le16(BP_FUNC(bp));
		cur_query_entry->address.hi =
			cpu_to_le32(U64_HI(cur_data_offset));
		cur_query_entry->address.lo =
			cpu_to_le32(U64_LO(cur_data_offset));

		cur_data_offset += माप(काष्ठा per_queue_stats);
	पूर्ण

	/* add FCoE queue query अगर needed */
	अगर (!NO_FCOE(bp)) अणु
		cur_query_entry =
			&bp->fw_stats_req->
					query[first_queue_query_index + i];

		cur_query_entry->kind = STATS_TYPE_QUEUE;
		cur_query_entry->index = bnx2x_stats_id(&bp->fp[FCOE_IDX(bp)]);
		cur_query_entry->funcID = cpu_to_le16(BP_FUNC(bp));
		cur_query_entry->address.hi =
			cpu_to_le32(U64_HI(cur_data_offset));
		cur_query_entry->address.lo =
			cpu_to_le32(U64_LO(cur_data_offset));
	पूर्ण
पूर्ण

व्योम bnx2x_स_रखो_stats(काष्ठा bnx2x *bp)
अणु
	पूर्णांक i;

	/* function stats */
	क्रम_each_queue(bp, i) अणु
		काष्ठा bnx2x_fp_stats *fp_stats = &bp->fp_stats[i];

		स_रखो(&fp_stats->old_tclient, 0,
		       माप(fp_stats->old_tclient));
		स_रखो(&fp_stats->old_uclient, 0,
		       माप(fp_stats->old_uclient));
		स_रखो(&fp_stats->old_xclient, 0,
		       माप(fp_stats->old_xclient));
		अगर (bp->stats_init) अणु
			स_रखो(&fp_stats->eth_q_stats, 0,
			       माप(fp_stats->eth_q_stats));
			स_रखो(&fp_stats->eth_q_stats_old, 0,
			       माप(fp_stats->eth_q_stats_old));
		पूर्ण
	पूर्ण

	स_रखो(&bp->dev->stats, 0, माप(bp->dev->stats));

	अगर (bp->stats_init) अणु
		स_रखो(&bp->net_stats_old, 0, माप(bp->net_stats_old));
		स_रखो(&bp->fw_stats_old, 0, माप(bp->fw_stats_old));
		स_रखो(&bp->eth_stats_old, 0, माप(bp->eth_stats_old));
		स_रखो(&bp->eth_stats, 0, माप(bp->eth_stats));
		स_रखो(&bp->func_stats, 0, माप(bp->func_stats));
	पूर्ण

	bp->stats_state = STATS_STATE_DISABLED;

	अगर (bp->port.pmf && bp->port.port_stx)
		bnx2x_port_stats_base_init(bp);

	/* mark the end of statistics initialization */
	bp->stats_init = false;
पूर्ण

व्योम bnx2x_stats_init(काष्ठा bnx2x *bp)
अणु
	पूर्णांक /*असल*/port = BP_PORT(bp);
	पूर्णांक mb_idx = BP_FW_MB_IDX(bp);

	अगर (IS_VF(bp)) अणु
		bnx2x_स_रखो_stats(bp);
		वापस;
	पूर्ण

	bp->stats_pending = 0;
	bp->executer_idx = 0;
	bp->stats_counter = 0;

	/* port and func stats क्रम management */
	अगर (!BP_NOMCP(bp)) अणु
		bp->port.port_stx = SHMEM_RD(bp, port_mb[port].port_stx);
		bp->func_stx = SHMEM_RD(bp, func_mb[mb_idx].fw_mb_param);

	पूर्ण अन्यथा अणु
		bp->port.port_stx = 0;
		bp->func_stx = 0;
	पूर्ण
	DP(BNX2X_MSG_STATS, "port_stx 0x%x  func_stx 0x%x\n",
	   bp->port.port_stx, bp->func_stx);

	/* pmf should retrieve port statistics from SP on a non-init*/
	अगर (!bp->stats_init && bp->port.pmf && bp->port.port_stx)
		bnx2x_stats_handle(bp, STATS_EVENT_PMF);

	port = BP_PORT(bp);
	/* port stats */
	स_रखो(&(bp->port.old_nig_stats), 0, माप(काष्ठा nig_stats));
	bp->port.old_nig_stats.brb_discard =
			REG_RD(bp, NIG_REG_STAT0_BRB_DISCARD + port*0x38);
	bp->port.old_nig_stats.brb_truncate =
			REG_RD(bp, NIG_REG_STAT0_BRB_TRUNCATE + port*0x38);
	अगर (!CHIP_IS_E3(bp)) अणु
		REG_RD_DMAE(bp, NIG_REG_STAT0_EGRESS_MAC_PKT0 + port*0x50,
			    &(bp->port.old_nig_stats.egress_mac_pkt0_lo), 2);
		REG_RD_DMAE(bp, NIG_REG_STAT0_EGRESS_MAC_PKT1 + port*0x50,
			    &(bp->port.old_nig_stats.egress_mac_pkt1_lo), 2);
	पूर्ण

	/* Prepare statistics ramrod data */
	bnx2x_prep_fw_stats_req(bp);

	/* Clean SP from previous statistics */
	अगर (bp->stats_init) अणु
		अगर (bp->func_stx) अणु
			स_रखो(bnx2x_sp(bp, func_stats), 0,
			       माप(काष्ठा host_func_stats));
			bnx2x_func_stats_init(bp);
			bnx2x_hw_stats_post(bp);
			bnx2x_stats_comp(bp);
		पूर्ण
	पूर्ण

	bnx2x_स_रखो_stats(bp);
पूर्ण

व्योम bnx2x_save_statistics(काष्ठा bnx2x *bp)
अणु
	पूर्णांक i;
	काष्ठा net_device_stats *nstats = &bp->dev->stats;

	/* save queue statistics */
	क्रम_each_eth_queue(bp, i) अणु
		काष्ठा bnx2x_fastpath *fp = &bp->fp[i];
		काष्ठा bnx2x_eth_q_stats *qstats =
			&bnx2x_fp_stats(bp, fp)->eth_q_stats;
		काष्ठा bnx2x_eth_q_stats_old *qstats_old =
			&bnx2x_fp_stats(bp, fp)->eth_q_stats_old;

		UPDATE_QSTAT_OLD(total_unicast_bytes_received_hi);
		UPDATE_QSTAT_OLD(total_unicast_bytes_received_lo);
		UPDATE_QSTAT_OLD(total_broadcast_bytes_received_hi);
		UPDATE_QSTAT_OLD(total_broadcast_bytes_received_lo);
		UPDATE_QSTAT_OLD(total_multicast_bytes_received_hi);
		UPDATE_QSTAT_OLD(total_multicast_bytes_received_lo);
		UPDATE_QSTAT_OLD(total_unicast_bytes_transmitted_hi);
		UPDATE_QSTAT_OLD(total_unicast_bytes_transmitted_lo);
		UPDATE_QSTAT_OLD(total_broadcast_bytes_transmitted_hi);
		UPDATE_QSTAT_OLD(total_broadcast_bytes_transmitted_lo);
		UPDATE_QSTAT_OLD(total_multicast_bytes_transmitted_hi);
		UPDATE_QSTAT_OLD(total_multicast_bytes_transmitted_lo);
		UPDATE_QSTAT_OLD(total_tpa_bytes_hi);
		UPDATE_QSTAT_OLD(total_tpa_bytes_lo);
	पूर्ण

	/* save net_device_stats statistics */
	bp->net_stats_old.rx_dropped = nstats->rx_dropped;

	/* store port firmware statistics */
	अगर (bp->port.pmf && IS_MF(bp)) अणु
		काष्ठा bnx2x_eth_stats *estats = &bp->eth_stats;
		काष्ठा bnx2x_fw_port_stats_old *fwstats = &bp->fw_stats_old;
		UPDATE_FW_STAT_OLD(mac_filter_discard);
		UPDATE_FW_STAT_OLD(mf_tag_discard);
		UPDATE_FW_STAT_OLD(brb_truncate_discard);
		UPDATE_FW_STAT_OLD(mac_discard);
	पूर्ण
पूर्ण

व्योम bnx2x_afex_collect_stats(काष्ठा bnx2x *bp, व्योम *व्योम_afex_stats,
			      u32 stats_type)
अणु
	पूर्णांक i;
	काष्ठा afex_stats *afex_stats = (काष्ठा afex_stats *)व्योम_afex_stats;
	काष्ठा bnx2x_eth_stats *estats = &bp->eth_stats;
	काष्ठा per_queue_stats *fcoe_q_stats =
		&bp->fw_stats_data->queue_stats[FCOE_IDX(bp)];

	काष्ठा tstorm_per_queue_stats *fcoe_q_tstorm_stats =
		&fcoe_q_stats->tstorm_queue_statistics;

	काष्ठा ustorm_per_queue_stats *fcoe_q_ustorm_stats =
		&fcoe_q_stats->ustorm_queue_statistics;

	काष्ठा xstorm_per_queue_stats *fcoe_q_xstorm_stats =
		&fcoe_q_stats->xstorm_queue_statistics;

	काष्ठा fcoe_statistics_params *fw_fcoe_stat =
		&bp->fw_stats_data->fcoe;

	स_रखो(afex_stats, 0, माप(काष्ठा afex_stats));

	क्रम_each_eth_queue(bp, i) अणु
		काष्ठा bnx2x_eth_q_stats *qstats = &bp->fp_stats[i].eth_q_stats;

		ADD_64(afex_stats->rx_unicast_bytes_hi,
		       qstats->total_unicast_bytes_received_hi,
		       afex_stats->rx_unicast_bytes_lo,
		       qstats->total_unicast_bytes_received_lo);

		ADD_64(afex_stats->rx_broadcast_bytes_hi,
		       qstats->total_broadcast_bytes_received_hi,
		       afex_stats->rx_broadcast_bytes_lo,
		       qstats->total_broadcast_bytes_received_lo);

		ADD_64(afex_stats->rx_multicast_bytes_hi,
		       qstats->total_multicast_bytes_received_hi,
		       afex_stats->rx_multicast_bytes_lo,
		       qstats->total_multicast_bytes_received_lo);

		ADD_64(afex_stats->rx_unicast_frames_hi,
		       qstats->total_unicast_packets_received_hi,
		       afex_stats->rx_unicast_frames_lo,
		       qstats->total_unicast_packets_received_lo);

		ADD_64(afex_stats->rx_broadcast_frames_hi,
		       qstats->total_broadcast_packets_received_hi,
		       afex_stats->rx_broadcast_frames_lo,
		       qstats->total_broadcast_packets_received_lo);

		ADD_64(afex_stats->rx_multicast_frames_hi,
		       qstats->total_multicast_packets_received_hi,
		       afex_stats->rx_multicast_frames_lo,
		       qstats->total_multicast_packets_received_lo);

		/* sum to rx_frames_discarded all discraded
		 * packets due to size, ttl0 and checksum
		 */
		ADD_64(afex_stats->rx_frames_discarded_hi,
		       qstats->total_packets_received_checksum_discarded_hi,
		       afex_stats->rx_frames_discarded_lo,
		       qstats->total_packets_received_checksum_discarded_lo);

		ADD_64(afex_stats->rx_frames_discarded_hi,
		       qstats->total_packets_received_ttl0_discarded_hi,
		       afex_stats->rx_frames_discarded_lo,
		       qstats->total_packets_received_ttl0_discarded_lo);

		ADD_64(afex_stats->rx_frames_discarded_hi,
		       qstats->etherstatsoverrsizepkts_hi,
		       afex_stats->rx_frames_discarded_lo,
		       qstats->etherstatsoverrsizepkts_lo);

		ADD_64(afex_stats->rx_frames_dropped_hi,
		       qstats->no_buff_discard_hi,
		       afex_stats->rx_frames_dropped_lo,
		       qstats->no_buff_discard_lo);

		ADD_64(afex_stats->tx_unicast_bytes_hi,
		       qstats->total_unicast_bytes_transmitted_hi,
		       afex_stats->tx_unicast_bytes_lo,
		       qstats->total_unicast_bytes_transmitted_lo);

		ADD_64(afex_stats->tx_broadcast_bytes_hi,
		       qstats->total_broadcast_bytes_transmitted_hi,
		       afex_stats->tx_broadcast_bytes_lo,
		       qstats->total_broadcast_bytes_transmitted_lo);

		ADD_64(afex_stats->tx_multicast_bytes_hi,
		       qstats->total_multicast_bytes_transmitted_hi,
		       afex_stats->tx_multicast_bytes_lo,
		       qstats->total_multicast_bytes_transmitted_lo);

		ADD_64(afex_stats->tx_unicast_frames_hi,
		       qstats->total_unicast_packets_transmitted_hi,
		       afex_stats->tx_unicast_frames_lo,
		       qstats->total_unicast_packets_transmitted_lo);

		ADD_64(afex_stats->tx_broadcast_frames_hi,
		       qstats->total_broadcast_packets_transmitted_hi,
		       afex_stats->tx_broadcast_frames_lo,
		       qstats->total_broadcast_packets_transmitted_lo);

		ADD_64(afex_stats->tx_multicast_frames_hi,
		       qstats->total_multicast_packets_transmitted_hi,
		       afex_stats->tx_multicast_frames_lo,
		       qstats->total_multicast_packets_transmitted_lo);

		ADD_64(afex_stats->tx_frames_dropped_hi,
		       qstats->total_transmitted_dropped_packets_error_hi,
		       afex_stats->tx_frames_dropped_lo,
		       qstats->total_transmitted_dropped_packets_error_lo);
	पूर्ण

	/* now add FCoE statistics which are collected separately
	 * (both offloaded and non offloaded)
	 */
	अगर (!NO_FCOE(bp)) अणु
		ADD_64_LE(afex_stats->rx_unicast_bytes_hi,
			  LE32_0,
			  afex_stats->rx_unicast_bytes_lo,
			  fw_fcoe_stat->rx_stat0.fcoe_rx_byte_cnt);

		ADD_64_LE(afex_stats->rx_unicast_bytes_hi,
			  fcoe_q_tstorm_stats->rcv_ucast_bytes.hi,
			  afex_stats->rx_unicast_bytes_lo,
			  fcoe_q_tstorm_stats->rcv_ucast_bytes.lo);

		ADD_64_LE(afex_stats->rx_broadcast_bytes_hi,
			  fcoe_q_tstorm_stats->rcv_bcast_bytes.hi,
			  afex_stats->rx_broadcast_bytes_lo,
			  fcoe_q_tstorm_stats->rcv_bcast_bytes.lo);

		ADD_64_LE(afex_stats->rx_multicast_bytes_hi,
			  fcoe_q_tstorm_stats->rcv_mcast_bytes.hi,
			  afex_stats->rx_multicast_bytes_lo,
			  fcoe_q_tstorm_stats->rcv_mcast_bytes.lo);

		ADD_64_LE(afex_stats->rx_unicast_frames_hi,
			  LE32_0,
			  afex_stats->rx_unicast_frames_lo,
			  fw_fcoe_stat->rx_stat0.fcoe_rx_pkt_cnt);

		ADD_64_LE(afex_stats->rx_unicast_frames_hi,
			  LE32_0,
			  afex_stats->rx_unicast_frames_lo,
			  fcoe_q_tstorm_stats->rcv_ucast_pkts);

		ADD_64_LE(afex_stats->rx_broadcast_frames_hi,
			  LE32_0,
			  afex_stats->rx_broadcast_frames_lo,
			  fcoe_q_tstorm_stats->rcv_bcast_pkts);

		ADD_64_LE(afex_stats->rx_multicast_frames_hi,
			  LE32_0,
			  afex_stats->rx_multicast_frames_lo,
			  fcoe_q_tstorm_stats->rcv_ucast_pkts);

		ADD_64_LE(afex_stats->rx_frames_discarded_hi,
			  LE32_0,
			  afex_stats->rx_frames_discarded_lo,
			  fcoe_q_tstorm_stats->checksum_discard);

		ADD_64_LE(afex_stats->rx_frames_discarded_hi,
			  LE32_0,
			  afex_stats->rx_frames_discarded_lo,
			  fcoe_q_tstorm_stats->pkts_too_big_discard);

		ADD_64_LE(afex_stats->rx_frames_discarded_hi,
			  LE32_0,
			  afex_stats->rx_frames_discarded_lo,
			  fcoe_q_tstorm_stats->ttl0_discard);

		ADD_64_LE16(afex_stats->rx_frames_dropped_hi,
			    LE16_0,
			    afex_stats->rx_frames_dropped_lo,
			    fcoe_q_tstorm_stats->no_buff_discard);

		ADD_64_LE(afex_stats->rx_frames_dropped_hi,
			  LE32_0,
			  afex_stats->rx_frames_dropped_lo,
			  fcoe_q_ustorm_stats->ucast_no_buff_pkts);

		ADD_64_LE(afex_stats->rx_frames_dropped_hi,
			  LE32_0,
			  afex_stats->rx_frames_dropped_lo,
			  fcoe_q_ustorm_stats->mcast_no_buff_pkts);

		ADD_64_LE(afex_stats->rx_frames_dropped_hi,
			  LE32_0,
			  afex_stats->rx_frames_dropped_lo,
			  fcoe_q_ustorm_stats->bcast_no_buff_pkts);

		ADD_64_LE(afex_stats->rx_frames_dropped_hi,
			  LE32_0,
			  afex_stats->rx_frames_dropped_lo,
			  fw_fcoe_stat->rx_stat1.fcoe_rx_drop_pkt_cnt);

		ADD_64_LE(afex_stats->rx_frames_dropped_hi,
			  LE32_0,
			  afex_stats->rx_frames_dropped_lo,
			  fw_fcoe_stat->rx_stat2.fcoe_rx_drop_pkt_cnt);

		ADD_64_LE(afex_stats->tx_unicast_bytes_hi,
			  LE32_0,
			  afex_stats->tx_unicast_bytes_lo,
			  fw_fcoe_stat->tx_stat.fcoe_tx_byte_cnt);

		ADD_64_LE(afex_stats->tx_unicast_bytes_hi,
			  fcoe_q_xstorm_stats->ucast_bytes_sent.hi,
			  afex_stats->tx_unicast_bytes_lo,
			  fcoe_q_xstorm_stats->ucast_bytes_sent.lo);

		ADD_64_LE(afex_stats->tx_broadcast_bytes_hi,
			  fcoe_q_xstorm_stats->bcast_bytes_sent.hi,
			  afex_stats->tx_broadcast_bytes_lo,
			  fcoe_q_xstorm_stats->bcast_bytes_sent.lo);

		ADD_64_LE(afex_stats->tx_multicast_bytes_hi,
			  fcoe_q_xstorm_stats->mcast_bytes_sent.hi,
			  afex_stats->tx_multicast_bytes_lo,
			  fcoe_q_xstorm_stats->mcast_bytes_sent.lo);

		ADD_64_LE(afex_stats->tx_unicast_frames_hi,
			  LE32_0,
			  afex_stats->tx_unicast_frames_lo,
			  fw_fcoe_stat->tx_stat.fcoe_tx_pkt_cnt);

		ADD_64_LE(afex_stats->tx_unicast_frames_hi,
			  LE32_0,
			  afex_stats->tx_unicast_frames_lo,
			  fcoe_q_xstorm_stats->ucast_pkts_sent);

		ADD_64_LE(afex_stats->tx_broadcast_frames_hi,
			  LE32_0,
			  afex_stats->tx_broadcast_frames_lo,
			  fcoe_q_xstorm_stats->bcast_pkts_sent);

		ADD_64_LE(afex_stats->tx_multicast_frames_hi,
			  LE32_0,
			  afex_stats->tx_multicast_frames_lo,
			  fcoe_q_xstorm_stats->mcast_pkts_sent);

		ADD_64_LE(afex_stats->tx_frames_dropped_hi,
			  LE32_0,
			  afex_stats->tx_frames_dropped_lo,
			  fcoe_q_xstorm_stats->error_drop_pkts);
	पूर्ण

	/* अगर port stats are requested, add them to the PMF
	 * stats, as anyway they will be accumulated by the
	 * MCP beक्रमe sent to the चयन
	 */
	अगर ((bp->port.pmf) && (stats_type == VICSTATST_UIF_INDEX)) अणु
		ADD_64(afex_stats->rx_frames_dropped_hi,
		       0,
		       afex_stats->rx_frames_dropped_lo,
		       estats->mac_filter_discard);
		ADD_64(afex_stats->rx_frames_dropped_hi,
		       0,
		       afex_stats->rx_frames_dropped_lo,
		       estats->brb_truncate_discard);
		ADD_64(afex_stats->rx_frames_discarded_hi,
		       0,
		       afex_stats->rx_frames_discarded_lo,
		       estats->mac_discard);
	पूर्ण
पूर्ण

पूर्णांक bnx2x_stats_safe_exec(काष्ठा bnx2x *bp,
			  व्योम (func_to_exec)(व्योम *cookie),
			  व्योम *cookie)
अणु
	पूर्णांक cnt = 10, rc = 0;

	/* Wait क्रम statistics to end [जबतक blocking further requests],
	 * then run supplied function 'safely'.
	 */
	rc = करोwn_समयout(&bp->stats_lock, HZ / 10);
	अगर (unlikely(rc)) अणु
		BNX2X_ERR("Failed to take statistics lock for safe execution\n");
		जाओ out_no_lock;
	पूर्ण

	bnx2x_stats_comp(bp);
	जबतक (bp->stats_pending && cnt--)
		अगर (bnx2x_storm_stats_update(bp))
			usleep_range(1000, 2000);
	अगर (bp->stats_pending) अणु
		BNX2X_ERR("Failed to wait for stats pending to clear [possibly FW is stuck]\n");
		rc = -EBUSY;
		जाओ out;
	पूर्ण

	func_to_exec(cookie);

out:
	/* No need to restart statistics - अगर they're enabled, the समयr
	 * will restart the statistics.
	 */
	up(&bp->stats_lock);
out_no_lock:
	वापस rc;
पूर्ण
