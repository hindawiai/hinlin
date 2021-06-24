<शैली गुरु>
/* SPDX-License-Identअगरier: BSD-3-Clause */
/* Copyright (c) 2016-2018, NXP Semiconductors
 * Copyright (c) 2018-2019, Vladimir Oltean <olteanv@gmail.com>
 */
#अगर_अघोषित _SJA1105_STATIC_CONFIG_H
#घोषणा _SJA1105_STATIC_CONFIG_H

#समावेश <linux/packing.h>
#समावेश <linux/types.h>
#समावेश <यंत्र/types.h>

#घोषणा SJA1105_SIZE_DEVICE_ID				4
#घोषणा SJA1105_SIZE_TABLE_HEADER			12
#घोषणा SJA1105_SIZE_SCHEDULE_ENTRY			8
#घोषणा SJA1105_SIZE_SCHEDULE_ENTRY_POINTS_ENTRY	4
#घोषणा SJA1105_SIZE_VL_LOOKUP_ENTRY			12
#घोषणा SJA1105_SIZE_VL_POLICING_ENTRY			8
#घोषणा SJA1105_SIZE_VL_FORWARDING_ENTRY		4
#घोषणा SJA1105_SIZE_L2_POLICING_ENTRY			8
#घोषणा SJA1105_SIZE_VLAN_LOOKUP_ENTRY			8
#घोषणा SJA1105_SIZE_L2_FORWARDING_ENTRY		8
#घोषणा SJA1105_SIZE_L2_FORWARDING_PARAMS_ENTRY		12
#घोषणा SJA1105_SIZE_RETAGGING_ENTRY			8
#घोषणा SJA1105_SIZE_XMII_PARAMS_ENTRY			4
#घोषणा SJA1105_SIZE_SCHEDULE_PARAMS_ENTRY		12
#घोषणा SJA1105_SIZE_SCHEDULE_ENTRY_POINTS_PARAMS_ENTRY	4
#घोषणा SJA1105_SIZE_VL_FORWARDING_PARAMS_ENTRY         12
#घोषणा SJA1105ET_SIZE_L2_LOOKUP_ENTRY			12
#घोषणा SJA1105ET_SIZE_MAC_CONFIG_ENTRY			28
#घोषणा SJA1105ET_SIZE_L2_LOOKUP_PARAMS_ENTRY		4
#घोषणा SJA1105ET_SIZE_GENERAL_PARAMS_ENTRY		40
#घोषणा SJA1105ET_SIZE_AVB_PARAMS_ENTRY			12
#घोषणा SJA1105ET_SIZE_CBS_ENTRY			16
#घोषणा SJA1105PQRS_SIZE_L2_LOOKUP_ENTRY		20
#घोषणा SJA1105PQRS_SIZE_MAC_CONFIG_ENTRY		32
#घोषणा SJA1105PQRS_SIZE_L2_LOOKUP_PARAMS_ENTRY		16
#घोषणा SJA1105PQRS_SIZE_GENERAL_PARAMS_ENTRY		44
#घोषणा SJA1105PQRS_SIZE_AVB_PARAMS_ENTRY		16
#घोषणा SJA1105PQRS_SIZE_CBS_ENTRY			20

/* UM10944.pdf Page 11, Table 2. Configuration Blocks */
क्रमागत अणु
	BLKID_SCHEDULE					= 0x00,
	BLKID_SCHEDULE_ENTRY_POINTS			= 0x01,
	BLKID_VL_LOOKUP					= 0x02,
	BLKID_VL_POLICING				= 0x03,
	BLKID_VL_FORWARDING				= 0x04,
	BLKID_L2_LOOKUP					= 0x05,
	BLKID_L2_POLICING				= 0x06,
	BLKID_VLAN_LOOKUP				= 0x07,
	BLKID_L2_FORWARDING				= 0x08,
	BLKID_MAC_CONFIG				= 0x09,
	BLKID_SCHEDULE_PARAMS				= 0x0A,
	BLKID_SCHEDULE_ENTRY_POINTS_PARAMS		= 0x0B,
	BLKID_VL_FORWARDING_PARAMS			= 0x0C,
	BLKID_L2_LOOKUP_PARAMS				= 0x0D,
	BLKID_L2_FORWARDING_PARAMS			= 0x0E,
	BLKID_AVB_PARAMS				= 0x10,
	BLKID_GENERAL_PARAMS				= 0x11,
	BLKID_RETAGGING					= 0x12,
	BLKID_CBS					= 0x13,
	BLKID_XMII_PARAMS				= 0x4E,
पूर्ण;

क्रमागत sja1105_blk_idx अणु
	BLK_IDX_SCHEDULE = 0,
	BLK_IDX_SCHEDULE_ENTRY_POINTS,
	BLK_IDX_VL_LOOKUP,
	BLK_IDX_VL_POLICING,
	BLK_IDX_VL_FORWARDING,
	BLK_IDX_L2_LOOKUP,
	BLK_IDX_L2_POLICING,
	BLK_IDX_VLAN_LOOKUP,
	BLK_IDX_L2_FORWARDING,
	BLK_IDX_MAC_CONFIG,
	BLK_IDX_SCHEDULE_PARAMS,
	BLK_IDX_SCHEDULE_ENTRY_POINTS_PARAMS,
	BLK_IDX_VL_FORWARDING_PARAMS,
	BLK_IDX_L2_LOOKUP_PARAMS,
	BLK_IDX_L2_FORWARDING_PARAMS,
	BLK_IDX_AVB_PARAMS,
	BLK_IDX_GENERAL_PARAMS,
	BLK_IDX_RETAGGING,
	BLK_IDX_CBS,
	BLK_IDX_XMII_PARAMS,
	BLK_IDX_MAX,
	/* Fake block indices that are only valid क्रम dynamic access */
	BLK_IDX_MGMT_ROUTE,
	BLK_IDX_MAX_DYN,
	BLK_IDX_INVAL = -1,
पूर्ण;

#घोषणा SJA1105_MAX_SCHEDULE_COUNT			1024
#घोषणा SJA1105_MAX_SCHEDULE_ENTRY_POINTS_COUNT		2048
#घोषणा SJA1105_MAX_VL_LOOKUP_COUNT			1024
#घोषणा SJA1105_MAX_VL_POLICING_COUNT			1024
#घोषणा SJA1105_MAX_VL_FORWARDING_COUNT			1024
#घोषणा SJA1105_MAX_L2_LOOKUP_COUNT			1024
#घोषणा SJA1105_MAX_L2_POLICING_COUNT			45
#घोषणा SJA1105_MAX_VLAN_LOOKUP_COUNT			4096
#घोषणा SJA1105_MAX_L2_FORWARDING_COUNT			13
#घोषणा SJA1105_MAX_MAC_CONFIG_COUNT			5
#घोषणा SJA1105_MAX_SCHEDULE_PARAMS_COUNT		1
#घोषणा SJA1105_MAX_SCHEDULE_ENTRY_POINTS_PARAMS_COUNT	1
#घोषणा SJA1105_MAX_VL_FORWARDING_PARAMS_COUNT		1
#घोषणा SJA1105_MAX_L2_LOOKUP_PARAMS_COUNT		1
#घोषणा SJA1105_MAX_L2_FORWARDING_PARAMS_COUNT		1
#घोषणा SJA1105_MAX_GENERAL_PARAMS_COUNT		1
#घोषणा SJA1105_MAX_RETAGGING_COUNT			32
#घोषणा SJA1105_MAX_XMII_PARAMS_COUNT			1
#घोषणा SJA1105_MAX_AVB_PARAMS_COUNT			1
#घोषणा SJA1105ET_MAX_CBS_COUNT				10
#घोषणा SJA1105PQRS_MAX_CBS_COUNT			16

#घोषणा SJA1105_MAX_FRAME_MEMORY			929
#घोषणा SJA1105_MAX_FRAME_MEMORY_RETAGGING		910
#घोषणा SJA1105_VL_FRAME_MEMORY				100

#घोषणा SJA1105E_DEVICE_ID				0x9C00000Cull
#घोषणा SJA1105T_DEVICE_ID				0x9E00030Eull
#घोषणा SJA1105PR_DEVICE_ID				0xAF00030Eull
#घोषणा SJA1105QS_DEVICE_ID				0xAE00030Eull

#घोषणा SJA1105ET_PART_NO				0x9A83
#घोषणा SJA1105P_PART_NO				0x9A84
#घोषणा SJA1105Q_PART_NO				0x9A85
#घोषणा SJA1105R_PART_NO				0x9A86
#घोषणा SJA1105S_PART_NO				0x9A87

काष्ठा sja1105_schedule_entry अणु
	u64 winstindex;
	u64 winend;
	u64 winst;
	u64 destports;
	u64 setvalid;
	u64 txen;
	u64 resmedia_en;
	u64 resmedia;
	u64 vlindex;
	u64 delta;
पूर्ण;

काष्ठा sja1105_schedule_params_entry अणु
	u64 subscheind[8];
पूर्ण;

काष्ठा sja1105_general_params_entry अणु
	u64 vllupक्रमmat;
	u64 mirr_ptacu;
	u64 चयनid;
	u64 hostprio;
	u64 mac_fltres1;
	u64 mac_fltres0;
	u64 mac_flt1;
	u64 mac_flt0;
	u64 incl_srcpt1;
	u64 incl_srcpt0;
	u64 send_meta1;
	u64 send_meta0;
	u64 casc_port;
	u64 host_port;
	u64 mirr_port;
	u64 vlmarker;
	u64 vlmask;
	u64 tpid;
	u64 ignore2stf;
	u64 tpid2;
	/* P/Q/R/S only */
	u64 queue_ts;
	u64 egrmirrvid;
	u64 egrmirrpcp;
	u64 egrmirrdei;
	u64 replay_port;
पूर्ण;

काष्ठा sja1105_schedule_entry_poपूर्णांकs_entry अणु
	u64 subschindx;
	u64 delta;
	u64 address;
पूर्ण;

काष्ठा sja1105_schedule_entry_poपूर्णांकs_params_entry अणु
	u64 clksrc;
	u64 actsubsch;
पूर्ण;

काष्ठा sja1105_vlan_lookup_entry अणु
	u64 ving_mirr;
	u64 vegr_mirr;
	u64 vmemb_port;
	u64 vlan_bc;
	u64 tag_port;
	u64 vlanid;
पूर्ण;

काष्ठा sja1105_l2_lookup_entry अणु
	u64 vlanid;
	u64 macaddr;
	u64 destports;
	u64 enfport;
	u64 index;
	/* P/Q/R/S only */
	u64 mask_iotag;
	u64 mask_vlanid;
	u64 mask_macaddr;
	u64 iotag;
	u64 lockeds;
	जोड़ अणु
		/* LOCKEDS=1: Static FDB entries */
		काष्ठा अणु
			u64 tsreg;
			u64 mirrvlan;
			u64 takets;
			u64 mirr;
			u64 retag;
		पूर्ण;
		/* LOCKEDS=0: Dynamically learned FDB entries */
		काष्ठा अणु
			u64 touched;
			u64 age;
		पूर्ण;
	पूर्ण;
पूर्ण;

काष्ठा sja1105_l2_lookup_params_entry अणु
	u64 maxaddrp[5];     /* P/Q/R/S only */
	u64 start_dynspc;    /* P/Q/R/S only */
	u64 drpnolearn;      /* P/Q/R/S only */
	u64 use_अटल;      /* P/Q/R/S only */
	u64 owr_dyn;         /* P/Q/R/S only */
	u64 learn_once;      /* P/Q/R/S only */
	u64 maxage;          /* Shared */
	u64 dyn_tbsz;        /* E/T only */
	u64 poly;            /* E/T only */
	u64 shared_learn;    /* Shared */
	u64 no_enf_hostprt;  /* Shared */
	u64 no_mgmt_learn;   /* Shared */
पूर्ण;

काष्ठा sja1105_l2_क्रमwarding_entry अणु
	u64 bc_करोमुख्य;
	u64 reach_port;
	u64 fl_करोमुख्य;
	u64 vlan_pmap[8];
पूर्ण;

काष्ठा sja1105_l2_क्रमwarding_params_entry अणु
	u64 max_dynp;
	u64 part_spc[8];
पूर्ण;

काष्ठा sja1105_l2_policing_entry अणु
	u64 sharindx;
	u64 smax;
	u64 rate;
	u64 maxlen;
	u64 partition;
पूर्ण;

काष्ठा sja1105_avb_params_entry अणु
	u64 cas_master;
	u64 desपंचांगeta;
	u64 srcmeta;
पूर्ण;

काष्ठा sja1105_mac_config_entry अणु
	u64 top[8];
	u64 base[8];
	u64 enabled[8];
	u64 अगरg;
	u64 speed;
	u64 tp_delin;
	u64 tp_delout;
	u64 maxage;
	u64 vlanprio;
	u64 vlanid;
	u64 ing_mirr;
	u64 egr_mirr;
	u64 drpnona664;
	u64 drpdtag;
	u64 drpuntag;
	u64 retag;
	u64 dyn_learn;
	u64 egress;
	u64 ingress;
पूर्ण;

काष्ठा sja1105_retagging_entry अणु
	u64 egr_port;
	u64 ing_port;
	u64 vlan_ing;
	u64 vlan_egr;
	u64 करो_not_learn;
	u64 use_dest_ports;
	u64 destports;
पूर्ण;

काष्ठा sja1105_cbs_entry अणु
	u64 port;
	u64 prio;
	u64 credit_hi;
	u64 credit_lo;
	u64 send_slope;
	u64 idle_slope;
पूर्ण;

काष्ठा sja1105_xmii_params_entry अणु
	u64 phy_mac[5];
	u64 xmii_mode[5];
पूर्ण;

क्रमागत अणु
	SJA1105_VL_FORMAT_PSFP		= 0,
	SJA1105_VL_FORMAT_ARINC664	= 1,
पूर्ण;

काष्ठा sja1105_vl_lookup_entry अणु
	u64 क्रमmat;
	u64 port;
	जोड़ अणु
		/* SJA1105_VL_FORMAT_PSFP */
		काष्ठा अणु
			u64 destports;
			u64 iscritical;
			u64 macaddr;
			u64 vlanid;
			u64 vlanprior;
		पूर्ण;
		/* SJA1105_VL_FORMAT_ARINC664 */
		काष्ठा अणु
			u64 egrmirr;
			u64 ingrmirr;
			u64 vlid;
		पूर्ण;
	पूर्ण;
	/* Not part of hardware काष्ठाure */
	अचिन्हित दीर्घ flow_cookie;
पूर्ण;

काष्ठा sja1105_vl_policing_entry अणु
	u64 type;
	u64 maxlen;
	u64 sharindx;
	u64 bag;
	u64 jitter;
पूर्ण;

काष्ठा sja1105_vl_क्रमwarding_entry अणु
	u64 type;
	u64 priority;
	u64 partition;
	u64 destports;
पूर्ण;

काष्ठा sja1105_vl_क्रमwarding_params_entry अणु
	u64 partspc[8];
	u64 debugen;
पूर्ण;

काष्ठा sja1105_table_header अणु
	u64 block_id;
	u64 len;
	u64 crc;
पूर्ण;

काष्ठा sja1105_table_ops अणु
	माप_प्रकार (*packing)(व्योम *buf, व्योम *entry_ptr, क्रमागत packing_op op);
	माप_प्रकार unpacked_entry_size;
	माप_प्रकार packed_entry_size;
	माप_प्रकार max_entry_count;
पूर्ण;

काष्ठा sja1105_table अणु
	स्थिर काष्ठा sja1105_table_ops *ops;
	माप_प्रकार entry_count;
	व्योम *entries;
पूर्ण;

काष्ठा sja1105_अटल_config अणु
	u64 device_id;
	काष्ठा sja1105_table tables[BLK_IDX_MAX];
पूर्ण;

बाह्य स्थिर काष्ठा sja1105_table_ops sja1105e_table_ops[BLK_IDX_MAX];
बाह्य स्थिर काष्ठा sja1105_table_ops sja1105t_table_ops[BLK_IDX_MAX];
बाह्य स्थिर काष्ठा sja1105_table_ops sja1105p_table_ops[BLK_IDX_MAX];
बाह्य स्थिर काष्ठा sja1105_table_ops sja1105q_table_ops[BLK_IDX_MAX];
बाह्य स्थिर काष्ठा sja1105_table_ops sja1105r_table_ops[BLK_IDX_MAX];
बाह्य स्थिर काष्ठा sja1105_table_ops sja1105s_table_ops[BLK_IDX_MAX];

माप_प्रकार sja1105_table_header_packing(व्योम *buf, व्योम *hdr, क्रमागत packing_op op);
व्योम
sja1105_table_header_pack_with_crc(व्योम *buf, काष्ठा sja1105_table_header *hdr);
माप_प्रकार
sja1105_अटल_config_get_length(स्थिर काष्ठा sja1105_अटल_config *config);

प्रकार क्रमागत अणु
	SJA1105_CONFIG_OK = 0,
	SJA1105_TTETHERNET_NOT_SUPPORTED,
	SJA1105_INCORRECT_TTETHERNET_CONFIGURATION,
	SJA1105_INCORRECT_VIRTUAL_LINK_CONFIGURATION,
	SJA1105_MISSING_L2_POLICING_TABLE,
	SJA1105_MISSING_L2_FORWARDING_TABLE,
	SJA1105_MISSING_L2_FORWARDING_PARAMS_TABLE,
	SJA1105_MISSING_GENERAL_PARAMS_TABLE,
	SJA1105_MISSING_VLAN_TABLE,
	SJA1105_MISSING_XMII_TABLE,
	SJA1105_MISSING_MAC_TABLE,
	SJA1105_OVERCOMMITTED_FRAME_MEMORY,
पूर्ण sja1105_config_valid_t;

बाह्य स्थिर अक्षर *sja1105_अटल_config_error_msg[];

sja1105_config_valid_t
sja1105_अटल_config_check_valid(स्थिर काष्ठा sja1105_अटल_config *config);
व्योम
sja1105_अटल_config_pack(व्योम *buf, काष्ठा sja1105_अटल_config *config);
पूर्णांक sja1105_अटल_config_init(काष्ठा sja1105_अटल_config *config,
			       स्थिर काष्ठा sja1105_table_ops *अटल_ops,
			       u64 device_id);
व्योम sja1105_अटल_config_मुक्त(काष्ठा sja1105_अटल_config *config);

पूर्णांक sja1105_table_delete_entry(काष्ठा sja1105_table *table, पूर्णांक i);
पूर्णांक sja1105_table_resize(काष्ठा sja1105_table *table, माप_प्रकार new_count);

u32 sja1105_crc32(स्थिर व्योम *buf, माप_प्रकार len);

व्योम sja1105_pack(व्योम *buf, स्थिर u64 *val, पूर्णांक start, पूर्णांक end, माप_प्रकार len);
व्योम sja1105_unpack(स्थिर व्योम *buf, u64 *val, पूर्णांक start, पूर्णांक end, माप_प्रकार len);
व्योम sja1105_packing(व्योम *buf, u64 *val, पूर्णांक start, पूर्णांक end,
		     माप_प्रकार len, क्रमागत packing_op op);

/* Common implementations क्रम the अटल and dynamic configs */
माप_प्रकार sja1105pqrs_general_params_entry_packing(व्योम *buf, व्योम *entry_ptr,
						क्रमागत packing_op op);
माप_प्रकार sja1105pqrs_l2_lookup_params_entry_packing(व्योम *buf, व्योम *entry_ptr,
						  क्रमागत packing_op op);
माप_प्रकार sja1105_l2_क्रमwarding_entry_packing(व्योम *buf, व्योम *entry_ptr,
					   क्रमागत packing_op op);
माप_प्रकार sja1105pqrs_l2_lookup_entry_packing(व्योम *buf, व्योम *entry_ptr,
					   क्रमागत packing_op op);
माप_प्रकार sja1105et_l2_lookup_entry_packing(व्योम *buf, व्योम *entry_ptr,
					 क्रमागत packing_op op);
माप_प्रकार sja1105_vlan_lookup_entry_packing(व्योम *buf, व्योम *entry_ptr,
					 क्रमागत packing_op op);
माप_प्रकार sja1105_retagging_entry_packing(व्योम *buf, व्योम *entry_ptr,
				       क्रमागत packing_op op);
माप_प्रकार sja1105pqrs_mac_config_entry_packing(व्योम *buf, व्योम *entry_ptr,
					    क्रमागत packing_op op);
माप_प्रकार sja1105pqrs_avb_params_entry_packing(व्योम *buf, व्योम *entry_ptr,
					    क्रमागत packing_op op);
माप_प्रकार sja1105_vl_lookup_entry_packing(व्योम *buf, व्योम *entry_ptr,
				       क्रमागत packing_op op);

#पूर्ण_अगर
