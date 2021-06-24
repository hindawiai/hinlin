<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/* Applied Micro X-Gene SoC Ethernet Classअगरier काष्ठाures
 *
 * Copyright (c) 2016, Applied Micro Circuits Corporation
 * Authors: Khuong Dinh <kdinh@apm.com>
 *          Tanmay Inamdar <tinamdar@apm.com>
 *          Iyappan Subramanian <isubramanian@apm.com>
 */

#अगर_अघोषित __XGENE_ENET_CLE_H__
#घोषणा __XGENE_ENET_CLE_H__

#समावेश <linux/पन.स>
#समावेश <linux/अक्रमom.h>

/* Register offsets */
#घोषणा INDADDR			0x04
#घोषणा INDCMD			0x08
#घोषणा INDCMD_STATUS		0x0c
#घोषणा DATA_RAM0		0x10
#घोषणा SNPTR0			0x0100
#घोषणा SPPTR0			0x0104
#घोषणा DFCLSRESDBPTR0		0x0108
#घोषणा DFCLSRESDB00		0x010c
#घोषणा RSS_CTRL0		0x0000013c

#घोषणा CLE_CMD_TO		10	/* ms */
#घोषणा CLE_PKTRAM_SIZE		256	/* bytes */
#घोषणा CLE_PORT_OFFSET		0x200
#घोषणा CLE_DRAM_REGS		17

#घोषणा CLE_DN_TYPE_LEN		2
#घोषणा CLE_DN_TYPE_POS		0
#घोषणा CLE_DN_LASTN_LEN	1
#घोषणा CLE_DN_LASTN_POS	2
#घोषणा CLE_DN_HLS_LEN		1
#घोषणा CLE_DN_HLS_POS		3
#घोषणा CLE_DN_EXT_LEN		2
#घोषणा	CLE_DN_EXT_POS		4
#घोषणा CLE_DN_BSTOR_LEN	2
#घोषणा CLE_DN_BSTOR_POS	6
#घोषणा CLE_DN_SBSTOR_LEN	2
#घोषणा CLE_DN_SBSTOR_POS	8
#घोषणा CLE_DN_RPTR_LEN		12
#घोषणा CLE_DN_RPTR_POS		12

#घोषणा CLE_BR_VALID_LEN	1
#घोषणा CLE_BR_VALID_POS	0
#घोषणा CLE_BR_NPPTR_LEN	9
#घोषणा CLE_BR_NPPTR_POS	1
#घोषणा CLE_BR_JB_LEN		1
#घोषणा CLE_BR_JB_POS		10
#घोषणा CLE_BR_JR_LEN		1
#घोषणा CLE_BR_JR_POS		11
#घोषणा CLE_BR_OP_LEN		3
#घोषणा CLE_BR_OP_POS		12
#घोषणा CLE_BR_NNODE_LEN	9
#घोषणा CLE_BR_NNODE_POS	15
#घोषणा CLE_BR_NBR_LEN		5
#घोषणा CLE_BR_NBR_POS		24

#घोषणा CLE_BR_DATA_LEN		16
#घोषणा CLE_BR_DATA_POS		0
#घोषणा CLE_BR_MASK_LEN		16
#घोषणा CLE_BR_MASK_POS		16

#घोषणा CLE_KN_PRIO_POS		0
#घोषणा CLE_KN_PRIO_LEN		3
#घोषणा CLE_KN_RPTR_POS		3
#घोषणा CLE_KN_RPTR_LEN		10
#घोषणा CLE_TYPE_POS		0
#घोषणा CLE_TYPE_LEN		2

#घोषणा CLE_DROP_POS		28
#घोषणा CLE_DROP_LEN		1
#घोषणा CLE_DSTQIDL_POS		25
#घोषणा CLE_DSTQIDL_LEN		7
#घोषणा CLE_DSTQIDH_POS		0
#घोषणा CLE_DSTQIDH_LEN		5
#घोषणा CLE_FPSEL_POS		21
#घोषणा CLE_FPSEL_LEN		4
#घोषणा CLE_NFPSEL_POS		17
#घोषणा CLE_NFPSEL_LEN		4
#घोषणा CLE_PRIORITY_POS	5
#घोषणा CLE_PRIORITY_LEN	3

#घोषणा JMP_ABS			0
#घोषणा JMP_REL			1
#घोषणा JMP_FW			0
#घोषणा JMP_BW			1

क्रमागत xgene_cle_ptree_nodes अणु
	PKT_TYPE_NODE,
	PKT_PROT_NODE,
	RSS_IPV4_TCP_NODE,
	RSS_IPV4_UDP_NODE,
	RSS_IPV4_OTHERS_NODE,
	LAST_NODE,
	MAX_NODES
पूर्ण;

क्रमागत xgene_cle_byte_store अणु
	NO_BYTE,
	FIRST_BYTE,
	SECOND_BYTE,
	BOTH_BYTES
पूर्ण;

/* Preclassअगरication operation types */
क्रमागत xgene_cle_node_type अणु
	INV,
	KN,
	EWDN,
	RES_NODE
पूर्ण;

/* Preclassअगरication operation types */
क्रमागत xgene_cle_op_type अणु
	EQT,
	NEQT,
	LTEQT,
	GTEQT,
	AND,
	न_अंकD
पूर्ण;

क्रमागत xgene_cle_parser अणु
	PARSER0,
	PARSER1,
	PARSER2,
	PARSER_ALL
पूर्ण;

#घोषणा XGENE_CLE_DRAM(type)	(((type) & 0xf) << 28)
क्रमागत xgene_cle_dram_type अणु
	PKT_RAM,
	RSS_IDT,
	RSS_IPV4_HASH_SKEY,
	PTREE_RAM = 0xc,
	AVL_RAM,
	DB_RAM
पूर्ण;

क्रमागत xgene_cle_cmd_type अणु
	CLE_CMD_WR = 1,
	CLE_CMD_RD = 2,
	CLE_CMD_AVL_ADD = 8,
	CLE_CMD_AVL_DEL = 16,
	CLE_CMD_AVL_SRCH = 32
पूर्ण;

क्रमागत xgene_cle_ipv4_rss_hashtype अणु
	RSS_IPV4_8B,
	RSS_IPV4_12B,
पूर्ण;

क्रमागत xgene_cle_prot_type अणु
	XGENE_CLE_TCP,
	XGENE_CLE_UDP,
	XGENE_CLE_ESP,
	XGENE_CLE_OTHER
पूर्ण;

क्रमागत xgene_cle_prot_version अणु
	XGENE_CLE_IPV4,
पूर्ण;

क्रमागत xgene_cle_ptree_dbptrs अणु
	DB_RES_DROP,
	DB_RES_DEF,
	DB_RES_ACCEPT,
	DB_MAX_PTRS
पूर्ण;

/* RSS sideband संकेत info */
#घोषणा SB_IPFRAG_POS	0
#घोषणा SB_IPFRAG_LEN	1
#घोषणा SB_IPPROT_POS	1
#घोषणा SB_IPPROT_LEN	2
#घोषणा SB_IPVER_POS	3
#घोषणा SB_IPVER_LEN	1
#घोषणा SB_HDRLEN_POS	4
#घोषणा SB_HDRLEN_LEN	12

/* RSS indirection table */
#घोषणा XGENE_CLE_IDT_ENTRIES	128
#घोषणा IDT_DSTQID_POS		0
#घोषणा IDT_DSTQID_LEN		12
#घोषणा IDT_FPSEL_POS		12
#घोषणा IDT_FPSEL_LEN		5
#घोषणा IDT_NFPSEL_POS		17
#घोषणा IDT_NFPSEL_LEN		5
#घोषणा IDT_FPSEL1_POS		12
#घोषणा IDT_FPSEL1_LEN		4
#घोषणा IDT_NFPSEL1_POS		16
#घोषणा IDT_NFPSEL1_LEN		4

काष्ठा xgene_cle_ptree_branch अणु
	bool valid;
	u16 next_packet_poपूर्णांकer;
	bool jump_bw;
	bool jump_rel;
	u8 operation;
	u16 next_node;
	u8 next_branch;
	u16 data;
	u16 mask;
पूर्ण;

काष्ठा xgene_cle_ptree_ewdn अणु
	u8 node_type;
	bool last_node;
	bool hdr_len_store;
	u8 hdr_extn;
	u8 byte_store;
	u8 search_byte_store;
	u16 result_poपूर्णांकer;
	u8 num_branches;
	काष्ठा xgene_cle_ptree_branch branch[6];
पूर्ण;

काष्ठा xgene_cle_ptree_key अणु
	u8 priority;
	u16 result_poपूर्णांकer;
पूर्ण;

काष्ठा xgene_cle_ptree_kn अणु
	u8 node_type;
	u8 num_keys;
	काष्ठा xgene_cle_ptree_key key[32];
पूर्ण;

काष्ठा xgene_cle_dbptr अणु
	u8 split_boundary;
	u8 mirror_nxtfpsel;
	u8 mirror_fpsel;
	u16 mirror_dstqid;
	u8 drop;
	u8 mirror;
	u8 hdr_data_split;
	u64 hopinfomsbs;
	u8 DR;
	u8 HR;
	u64 hopinfomlsbs;
	u16 h0enq_num;
	u8 h0fpsel;
	u8 nxtfpsel;
	u8 fpsel;
	u16 dstqid;
	u8 cle_priority;
	u8 cle_flowgroup;
	u8 cle_perflow;
	u8 cle_insert_बारtamp;
	u8 stash;
	u8 in;
	u8 perprioen;
	u8 perflowgroupen;
	u8 perflowen;
	u8 selhash;
	u8 selhdrext;
	u8 mirror_nxtfpsel_msb;
	u8 mirror_fpsel_msb;
	u8 hfpsel_msb;
	u8 nxtfpsel_msb;
	u8 fpsel_msb;
पूर्ण;

काष्ठा xgene_cle_ptree अणु
	काष्ठा xgene_cle_ptree_kn *kn;
	काष्ठा xgene_cle_dbptr *dbptr;
	u32 num_kn;
	u32 num_dbptr;
	u32 start_node;
	u32 start_pkt;
	u32 start_dbptr;
पूर्ण;

काष्ठा xgene_enet_cle अणु
	व्योम __iomem *base;
	काष्ठा xgene_cle_ptree ptree;
	क्रमागत xgene_cle_parser active_parser;
	u32 parsers;
	u32 max_nodes;
	u32 max_dbptrs;
	u32 jump_bytes;
पूर्ण;

बाह्य स्थिर काष्ठा xgene_cle_ops xgene_cle3in_ops;

#पूर्ण_अगर /* __XGENE_ENET_CLE_H__ */
