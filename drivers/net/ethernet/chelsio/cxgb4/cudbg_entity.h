<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *  Copyright (C) 2017 Chelsio Communications.  All rights reserved.
 */

#अगर_अघोषित __CUDBG_ENTITY_H__
#घोषणा __CUDBG_ENTITY_H__

#घोषणा EDC0_FLAG 0
#घोषणा EDC1_FLAG 1
#घोषणा MC_FLAG 2
#घोषणा MC0_FLAG 3
#घोषणा MC1_FLAG 4
#घोषणा HMA_FLAG 5

#घोषणा CUDBG_ENTITY_SIGNATURE 0xCCEDB001

काष्ठा cudbg_mbox_log अणु
	काष्ठा mbox_cmd entry;
	u32 hi[MBOX_LEN / 8];
	u32 lo[MBOX_LEN / 8];
पूर्ण;

काष्ठा cudbg_cim_qcfg अणु
	u8 chip;
	u16 base[CIM_NUM_IBQ + CIM_NUM_OBQ_T5];
	u16 size[CIM_NUM_IBQ + CIM_NUM_OBQ_T5];
	u16 thres[CIM_NUM_IBQ];
	u32 obq_wr[2 * CIM_NUM_OBQ_T5];
	u32 stat[4 * (CIM_NUM_IBQ + CIM_NUM_OBQ_T5)];
पूर्ण;

काष्ठा cudbg_rss_vf_conf अणु
	u32 rss_vf_vfl;
	u32 rss_vf_vfh;
पूर्ण;

काष्ठा cudbg_pm_stats अणु
	u32 tx_cnt[T6_PM_NSTATS];
	u32 rx_cnt[T6_PM_NSTATS];
	u64 tx_cyc[T6_PM_NSTATS];
	u64 rx_cyc[T6_PM_NSTATS];
पूर्ण;

काष्ठा cudbg_hw_sched अणु
	u32 kbps[NTX_SCHED];
	u32 ipg[NTX_SCHED];
	u32 pace_tab[NTX_SCHED];
	u32 mode;
	u32 map;
पूर्ण;

#घोषणा SGE_QBASE_DATA_REG_NUM 4

काष्ठा sge_qbase_reg_field अणु
	u32 reg_addr;
	u32 reg_data[SGE_QBASE_DATA_REG_NUM];
	/* Max supported PFs */
	u32 pf_data_value[PCIE_FW_MASTER_M + 1][SGE_QBASE_DATA_REG_NUM];
	/* Max supported VFs */
	u32 vf_data_value[T6_VF_M + 1][SGE_QBASE_DATA_REG_NUM];
	u32 vfcount; /* Actual number of max vfs in current configuration */
पूर्ण;

काष्ठा ireg_field अणु
	u32 ireg_addr;
	u32 ireg_data;
	u32 ireg_local_offset;
	u32 ireg_offset_range;
पूर्ण;

काष्ठा ireg_buf अणु
	काष्ठा ireg_field tp_pio;
	u32 outbuf[32];
पूर्ण;

काष्ठा cudbg_ulprx_la अणु
	u32 data[ULPRX_LA_SIZE * 8];
	u32 size;
पूर्ण;

काष्ठा cudbg_tp_la अणु
	u32 size;
	u32 mode;
	u8 data[];
पूर्ण;

अटल स्थिर अक्षर * स्थिर cudbg_region[] = अणु
	"DBQ contexts:", "IMSG contexts:", "FLM cache:", "TCBs:",
	"Pstructs:", "Timers:", "Rx FL:", "Tx FL:", "Pstruct FL:",
	"Tx payload:", "Rx payload:", "LE hash:", "iSCSI region:",
	"TDDP region:", "TPT region:", "STAG region:", "RQ region:",
	"RQUDP region:", "PBL region:", "TXPBL region:",
	"DBVFIFO region:", "ULPRX state:", "ULPTX state:",
	"On-chip queues:"
पूर्ण;

/* Memory region info relative to current memory (i.e. wrt 0). */
काष्ठा cudbg_region_info अणु
	bool exist; /* Does region exists in current memory? */
	u32 start;  /* Start wrt 0 */
	u32 end;    /* End wrt 0 */
पूर्ण;

काष्ठा cudbg_mem_desc अणु
	u32 base;
	u32 limit;
	u32 idx;
पूर्ण;

#घोषणा CUDBG_MEMINFO_REV 1

काष्ठा cudbg_meminfo अणु
	काष्ठा cudbg_mem_desc avail[4];
	काष्ठा cudbg_mem_desc mem[ARRAY_SIZE(cudbg_region) + 3];
	u32 avail_c;
	u32 mem_c;
	u32 up_ram_lo;
	u32 up_ram_hi;
	u32 up_exपंचांगem2_lo;
	u32 up_exपंचांगem2_hi;
	u32 rx_pages_data[3];
	u32 tx_pages_data[4];
	u32 p_काष्ठाs;
	u32 reserved[12];
	u32 port_used[4];
	u32 port_alloc[4];
	u32 loopback_used[NCHAN];
	u32 loopback_alloc[NCHAN];
	u32 p_काष्ठाs_मुक्त_cnt;
	u32 मुक्त_rx_cnt;
	u32 मुक्त_tx_cnt;
पूर्ण;

काष्ठा cudbg_cim_pअगर_la अणु
	पूर्णांक size;
	u8 data[];
पूर्ण;

काष्ठा cudbg_clk_info अणु
	u64 retransmit_min;
	u64 retransmit_max;
	u64 persist_समयr_min;
	u64 persist_समयr_max;
	u64 keepalive_idle_समयr;
	u64 keepalive_पूर्णांकerval;
	u64 initial_srtt;
	u64 finरुको2_समयr;
	u32 dack_समयr;
	u32 res;
	u32 cclk_ps;
	u32 tre;
	u32 dack_re;
पूर्ण;

काष्ठा cudbg_tid_info_region अणु
	u32 ntids;
	u32 nstids;
	u32 stid_base;
	u32 hash_base;

	u32 natids;
	u32 nftids;
	u32 ftid_base;
	u32 aftid_base;
	u32 aftid_end;

	u32 sftid_base;
	u32 nsftids;

	u32 uotid_base;
	u32 nuotids;

	u32 sb;
	u32 flags;
	u32 le_db_conf;
	u32 ip_users;
	u32 ipv6_users;

	u32 hpftid_base;
	u32 nhpftids;
पूर्ण;

#घोषणा CUDBG_TID_INFO_REV 1

काष्ठा cudbg_tid_info_region_rev1 अणु
	काष्ठा cudbg_ver_hdr ver_hdr;
	काष्ठा cudbg_tid_info_region tid;
	u32 tid_start;
	u32 reserved[16];
पूर्ण;

#घोषणा CUDBG_LOWMEM_MAX_CTXT_QIDS 256
#घोषणा CUDBG_MAX_FL_QIDS 1024

काष्ठा cudbg_ch_cntxt अणु
	u32 cntxt_type;
	u32 cntxt_id;
	u32 data[SGE_CTXT_SIZE / 4];
पूर्ण;

#घोषणा CUDBG_MAX_RPLC_SIZE 128

काष्ठा cudbg_mps_tcam अणु
	u64 mask;
	u32 rplc[8];
	u32 idx;
	u32 cls_lo;
	u32 cls_hi;
	u32 rplc_size;
	u32 vniy;
	u32 vnix;
	u32 dip_hit;
	u32 vlan_vld;
	u32 repli;
	u16 ivlan;
	u8 addr[ETH_ALEN];
	u8 lookup_type;
	u8 port_num;
	u8 reserved[2];
पूर्ण;

#घोषणा CUDBG_VPD_VER_ADDR 0x18c7
#घोषणा CUDBG_VPD_VER_LEN 2

काष्ठा cudbg_vpd_data अणु
	u8 sn[SERNUM_LEN + 1];
	u8 bn[PN_LEN + 1];
	u8 na[MACADDR_LEN + 1];
	u8 mn[ID_LEN + 1];
	u16 fw_major;
	u16 fw_minor;
	u16 fw_micro;
	u16 fw_build;
	u32 scfg_vers;
	u32 vpd_vers;
पूर्ण;

#घोषणा CUDBG_MAX_TCAM_TID 0x800
#घोषणा CUDBG_T6_CLIP 1536
#घोषणा CUDBG_MAX_TID_COMP_EN 6144
#घोषणा CUDBG_MAX_TID_COMP_DIS 3072

क्रमागत cudbg_le_entry_types अणु
	LE_ET_UNKNOWN = 0,
	LE_ET_TCAM_CON = 1,
	LE_ET_TCAM_SERVER = 2,
	LE_ET_TCAM_FILTER = 3,
	LE_ET_TCAM_CLIP = 4,
	LE_ET_TCAM_ROUTING = 5,
	LE_ET_HASH_CON = 6,
	LE_ET_INVALID_TID = 8,
पूर्ण;

काष्ठा cudbg_tcam अणु
	u32 filter_start;
	u32 server_start;
	u32 clip_start;
	u32 routing_start;
	u32 tid_hash_base;
	u32 max_tid;
पूर्ण;

काष्ठा cudbg_tid_data अणु
	u32 tid;
	u32 dbig_cmd;
	u32 dbig_conf;
	u32 dbig_rsp_stat;
	u32 data[NUM_LE_DB_DBGI_RSP_DATA_INSTANCES];
पूर्ण;

#घोषणा CUDBG_NUM_ULPTX 11
#घोषणा CUDBG_NUM_ULPTX_READ 512
#घोषणा CUDBG_NUM_ULPTX_ASIC 6
#घोषणा CUDBG_NUM_ULPTX_ASIC_READ 128

#घोषणा CUDBG_ULPTX_LA_REV 1

काष्ठा cudbg_ulptx_la अणु
	u32 rdptr[CUDBG_NUM_ULPTX];
	u32 wrptr[CUDBG_NUM_ULPTX];
	u32 rddata[CUDBG_NUM_ULPTX];
	u32 rd_data[CUDBG_NUM_ULPTX][CUDBG_NUM_ULPTX_READ];
	u32 rdptr_asic[CUDBG_NUM_ULPTX_ASIC_READ];
	u32 rddata_asic[CUDBG_NUM_ULPTX_ASIC_READ][CUDBG_NUM_ULPTX_ASIC];
पूर्ण;

#घोषणा CUDBG_CHAC_PBT_ADDR 0x2800
#घोषणा CUDBG_CHAC_PBT_LRF  0x3000
#घोषणा CUDBG_CHAC_PBT_DATA 0x3800
#घोषणा CUDBG_PBT_DYNAMIC_ENTRIES 8
#घोषणा CUDBG_PBT_STATIC_ENTRIES 16
#घोषणा CUDBG_LRF_ENTRIES 8
#घोषणा CUDBG_PBT_DATA_ENTRIES 512

काष्ठा cudbg_pbt_tables अणु
	u32 pbt_dynamic[CUDBG_PBT_DYNAMIC_ENTRIES];
	u32 pbt_अटल[CUDBG_PBT_STATIC_ENTRIES];
	u32 lrf_table[CUDBG_LRF_ENTRIES];
	u32 pbt_data[CUDBG_PBT_DATA_ENTRIES];
पूर्ण;

क्रमागत cudbg_qdesc_qtype अणु
	CUDBG_QTYPE_UNKNOWN = 0,
	CUDBG_QTYPE_NIC_TXQ,
	CUDBG_QTYPE_NIC_RXQ,
	CUDBG_QTYPE_NIC_FLQ,
	CUDBG_QTYPE_CTRLQ,
	CUDBG_QTYPE_FWEVTQ,
	CUDBG_QTYPE_INTRQ,
	CUDBG_QTYPE_PTP_TXQ,
	CUDBG_QTYPE_OFLD_TXQ,
	CUDBG_QTYPE_RDMA_RXQ,
	CUDBG_QTYPE_RDMA_FLQ,
	CUDBG_QTYPE_RDMA_CIQ,
	CUDBG_QTYPE_ISCSI_RXQ,
	CUDBG_QTYPE_ISCSI_FLQ,
	CUDBG_QTYPE_ISCSIT_RXQ,
	CUDBG_QTYPE_ISCSIT_FLQ,
	CUDBG_QTYPE_CRYPTO_TXQ,
	CUDBG_QTYPE_CRYPTO_RXQ,
	CUDBG_QTYPE_CRYPTO_FLQ,
	CUDBG_QTYPE_TLS_RXQ,
	CUDBG_QTYPE_TLS_FLQ,
	CUDBG_QTYPE_ETHOFLD_TXQ,
	CUDBG_QTYPE_ETHOFLD_RXQ,
	CUDBG_QTYPE_ETHOFLD_FLQ,
	CUDBG_QTYPE_MAX,
पूर्ण;

#घोषणा CUDBG_QDESC_REV 1

काष्ठा cudbg_qdesc_entry अणु
	u32 data_size;
	u32 qtype;
	u32 qid;
	u32 desc_size;
	u32 num_desc;
	u8 data[]; /* Must be last */
पूर्ण;

काष्ठा cudbg_qdesc_info अणु
	u32 qdesc_entry_size;
	u32 num_queues;
	u8 data[]; /* Must be last */
पूर्ण;

#घोषणा IREG_NUM_ELEM 4

#घोषणा CUDBG_NUM_PCIE_CONFIG_REGS 0x61

#पूर्ण_अगर /* __CUDBG_ENTITY_H__ */
