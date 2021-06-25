<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* Applied Micro X-Gene SoC Ethernet Classअगरier काष्ठाures
 *
 * Copyright (c) 2016, Applied Micro Circuits Corporation
 * Authors: Khuong Dinh <kdinh@apm.com>
 *          Tanmay Inamdar <tinamdar@apm.com>
 *          Iyappan Subramanian <isubramanian@apm.com>
 */

#समावेश "xgene_enet_main.h"

/* पूर्णांकerfaces to convert काष्ठाures to HW recognized bit क्रमmats */
अटल व्योम xgene_cle_sband_to_hw(u8 frag, क्रमागत xgene_cle_prot_version ver,
				  क्रमागत xgene_cle_prot_type type, u32 len,
				  u32 *reg)
अणु
	*reg =  SET_VAL(SB_IPFRAG, frag) |
		SET_VAL(SB_IPPROT, type) |
		SET_VAL(SB_IPVER, ver) |
		SET_VAL(SB_HDRLEN, len);
पूर्ण

अटल व्योम xgene_cle_idt_to_hw(काष्ठा xgene_enet_pdata *pdata,
				u32 dstqid, u32 fpsel,
				u32 nfpsel, u32 *idt_reg)
अणु
	अगर (pdata->enet_id == XGENE_ENET1) अणु
		*idt_reg = SET_VAL(IDT_DSTQID, dstqid) |
			   SET_VAL(IDT_FPSEL1, fpsel)  |
			   SET_VAL(IDT_NFPSEL1, nfpsel);
	पूर्ण अन्यथा अणु
		*idt_reg = SET_VAL(IDT_DSTQID, dstqid) |
			   SET_VAL(IDT_FPSEL, fpsel)   |
			   SET_VAL(IDT_NFPSEL, nfpsel);
	पूर्ण
पूर्ण

अटल व्योम xgene_cle_dbptr_to_hw(काष्ठा xgene_enet_pdata *pdata,
				  काष्ठा xgene_cle_dbptr *dbptr, u32 *buf)
अणु
	buf[0] = SET_VAL(CLE_DROP, dbptr->drop);
	buf[4] = SET_VAL(CLE_FPSEL, dbptr->fpsel) |
		 SET_VAL(CLE_NFPSEL, dbptr->nxtfpsel) |
		 SET_VAL(CLE_DSTQIDL, dbptr->dstqid);

	buf[5] = SET_VAL(CLE_DSTQIDH, (u32)dbptr->dstqid >> CLE_DSTQIDL_LEN) |
		 SET_VAL(CLE_PRIORITY, dbptr->cle_priority);
पूर्ण

अटल व्योम xgene_cle_kn_to_hw(काष्ठा xgene_cle_ptree_kn *kn, u32 *buf)
अणु
	u32 i, j = 0;
	u32 data;

	buf[j++] = SET_VAL(CLE_TYPE, kn->node_type);
	क्रम (i = 0; i < kn->num_keys; i++) अणु
		काष्ठा xgene_cle_ptree_key *key = &kn->key[i];

		अगर (!(i % 2)) अणु
			buf[j] = SET_VAL(CLE_KN_PRIO, key->priority) |
				 SET_VAL(CLE_KN_RPTR, key->result_poपूर्णांकer);
		पूर्ण अन्यथा अणु
			data = SET_VAL(CLE_KN_PRIO, key->priority) |
			       SET_VAL(CLE_KN_RPTR, key->result_poपूर्णांकer);
			buf[j++] |= (data << 16);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम xgene_cle_dn_to_hw(स्थिर काष्ठा xgene_cle_ptree_ewdn *dn,
			       u32 *buf, u32 jb)
अणु
	स्थिर काष्ठा xgene_cle_ptree_branch *br;
	u32 i, j = 0;
	u32 npp;

	buf[j++] = SET_VAL(CLE_DN_TYPE, dn->node_type) |
		   SET_VAL(CLE_DN_LASTN, dn->last_node) |
		   SET_VAL(CLE_DN_HLS, dn->hdr_len_store) |
		   SET_VAL(CLE_DN_EXT, dn->hdr_extn) |
		   SET_VAL(CLE_DN_BSTOR, dn->byte_store) |
		   SET_VAL(CLE_DN_SBSTOR, dn->search_byte_store) |
		   SET_VAL(CLE_DN_RPTR, dn->result_poपूर्णांकer);

	क्रम (i = 0; i < dn->num_branches; i++) अणु
		br = &dn->branch[i];
		npp = br->next_packet_poपूर्णांकer;

		अगर ((br->jump_rel == JMP_ABS) && (npp < CLE_PKTRAM_SIZE))
			npp += jb;

		buf[j++] = SET_VAL(CLE_BR_VALID, br->valid) |
			   SET_VAL(CLE_BR_NPPTR, npp) |
			   SET_VAL(CLE_BR_JB, br->jump_bw) |
			   SET_VAL(CLE_BR_JR, br->jump_rel) |
			   SET_VAL(CLE_BR_OP, br->operation) |
			   SET_VAL(CLE_BR_NNODE, br->next_node) |
			   SET_VAL(CLE_BR_NBR, br->next_branch);

		buf[j++] = SET_VAL(CLE_BR_DATA, br->data) |
			   SET_VAL(CLE_BR_MASK, br->mask);
	पूर्ण
पूर्ण

अटल पूर्णांक xgene_cle_poll_cmd_करोne(व्योम __iomem *base,
				   क्रमागत xgene_cle_cmd_type cmd)
अणु
	u32 status, loop = 10;
	पूर्णांक ret = -EBUSY;

	जबतक (loop--) अणु
		status = ioपढ़ो32(base + INDCMD_STATUS);
		अगर (status & cmd) अणु
			ret = 0;
			अवरोध;
		पूर्ण
		usleep_range(1000, 2000);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक xgene_cle_dram_wr(काष्ठा xgene_enet_cle *cle, u32 *data, u8 nregs,
			     u32 index, क्रमागत xgene_cle_dram_type type,
			     क्रमागत xgene_cle_cmd_type cmd)
अणु
	क्रमागत xgene_cle_parser parser = cle->active_parser;
	व्योम __iomem *base = cle->base;
	u32 i, j, ind_addr;
	u8 port, nparsers;
	पूर्णांक ret = 0;

	/* PTREE_RAM onwards, DRAM regions are common क्रम all parsers */
	nparsers = (type >= PTREE_RAM) ? 1 : cle->parsers;

	क्रम (i = 0; i < nparsers; i++) अणु
		port = i;
		अगर ((type < PTREE_RAM) && (parser != PARSER_ALL))
			port = parser;

		ind_addr = XGENE_CLE_DRAM(type + (port * 4)) | index;
		ioग_लिखो32(ind_addr, base + INDADDR);
		क्रम (j = 0; j < nregs; j++)
			ioग_लिखो32(data[j], base + DATA_RAM0 + (j * 4));
		ioग_लिखो32(cmd, base + INDCMD);

		ret = xgene_cle_poll_cmd_करोne(base, cmd);
		अगर (ret)
			अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम xgene_cle_enable_ptree(काष्ठा xgene_enet_pdata *pdata,
				   काष्ठा xgene_enet_cle *cle)
अणु
	काष्ठा xgene_cle_ptree *ptree = &cle->ptree;
	व्योम __iomem *addr, *base = cle->base;
	u32 offset = CLE_PORT_OFFSET;
	u32 i;

	/* 1G port has to advance 4 bytes and 10G has to advance 8 bytes */
	ptree->start_pkt += cle->jump_bytes;
	क्रम (i = 0; i < cle->parsers; i++) अणु
		अगर (cle->active_parser != PARSER_ALL)
			addr = base + cle->active_parser * offset;
		अन्यथा
			addr = base + (i * offset);

		ioग_लिखो32(ptree->start_node & 0x3fff, addr + SNPTR0);
		ioग_लिखो32(ptree->start_pkt & 0x1ff, addr + SPPTR0);
	पूर्ण
पूर्ण

अटल पूर्णांक xgene_cle_setup_dbptr(काष्ठा xgene_enet_pdata *pdata,
				 काष्ठा xgene_enet_cle *cle)
अणु
	काष्ठा xgene_cle_ptree *ptree = &cle->ptree;
	u32 buf[CLE_DRAM_REGS];
	u32 i;
	पूर्णांक ret;

	स_रखो(buf, 0, माप(buf));
	क्रम (i = 0; i < ptree->num_dbptr; i++) अणु
		xgene_cle_dbptr_to_hw(pdata, &ptree->dbptr[i], buf);
		ret = xgene_cle_dram_wr(cle, buf, 6, i + ptree->start_dbptr,
					DB_RAM,	CLE_CMD_WR);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा xgene_cle_ptree_ewdn xgene_init_ptree_dn[] = अणु
	अणु
		/* PKT_TYPE_NODE */
		.node_type = EWDN,
		.last_node = 0,
		.hdr_len_store = 1,
		.hdr_extn = NO_BYTE,
		.byte_store = NO_BYTE,
		.search_byte_store = NO_BYTE,
		.result_poपूर्णांकer = DB_RES_DROP,
		.num_branches = 2,
		.branch = अणु
			अणु
				/* IPV4 */
				.valid = 1,
				.next_packet_poपूर्णांकer = 22,
				.jump_bw = JMP_FW,
				.jump_rel = JMP_ABS,
				.operation = EQT,
				.next_node = PKT_PROT_NODE,
				.next_branch = 0,
				.data = 0x8,
				.mask = 0x0
			पूर्ण,
			अणु
				.valid = 0,
				.next_packet_poपूर्णांकer = 262,
				.jump_bw = JMP_FW,
				.jump_rel = JMP_ABS,
				.operation = EQT,
				.next_node = LAST_NODE,
				.next_branch = 0,
				.data = 0x0,
				.mask = 0xffff
			पूर्ण
		पूर्ण,
	पूर्ण,
	अणु
		/* PKT_PROT_NODE */
		.node_type = EWDN,
		.last_node = 0,
		.hdr_len_store = 1,
		.hdr_extn = NO_BYTE,
		.byte_store = NO_BYTE,
		.search_byte_store = NO_BYTE,
		.result_poपूर्णांकer = DB_RES_DROP,
		.num_branches = 3,
		.branch = अणु
			अणु
				/* TCP */
				.valid = 1,
				.next_packet_poपूर्णांकer = 26,
				.jump_bw = JMP_FW,
				.jump_rel = JMP_ABS,
				.operation = EQT,
				.next_node = RSS_IPV4_TCP_NODE,
				.next_branch = 0,
				.data = 0x0600,
				.mask = 0x00ff
			पूर्ण,
			अणु
				/* UDP */
				.valid = 1,
				.next_packet_poपूर्णांकer = 26,
				.jump_bw = JMP_FW,
				.jump_rel = JMP_ABS,
				.operation = EQT,
				.next_node = RSS_IPV4_UDP_NODE,
				.next_branch = 0,
				.data = 0x1100,
				.mask = 0x00ff
			पूर्ण,
			अणु
				.valid = 0,
				.next_packet_poपूर्णांकer = 26,
				.jump_bw = JMP_FW,
				.jump_rel = JMP_ABS,
				.operation = EQT,
				.next_node = RSS_IPV4_OTHERS_NODE,
				.next_branch = 0,
				.data = 0x0,
				.mask = 0xffff
			पूर्ण
		पूर्ण
	पूर्ण,
	अणु
		/* RSS_IPV4_TCP_NODE */
		.node_type = EWDN,
		.last_node = 0,
		.hdr_len_store = 1,
		.hdr_extn = NO_BYTE,
		.byte_store = NO_BYTE,
		.search_byte_store = BOTH_BYTES,
		.result_poपूर्णांकer = DB_RES_DROP,
		.num_branches = 6,
		.branch = अणु
			अणु
				/* SRC IPV4 B01 */
				.valid = 0,
				.next_packet_poपूर्णांकer = 28,
				.jump_bw = JMP_FW,
				.jump_rel = JMP_ABS,
				.operation = EQT,
				.next_node = RSS_IPV4_TCP_NODE,
				.next_branch = 1,
				.data = 0x0,
				.mask = 0xffff
			पूर्ण,
			अणु
				/* SRC IPV4 B23 */
				.valid = 0,
				.next_packet_poपूर्णांकer = 30,
				.jump_bw = JMP_FW,
				.jump_rel = JMP_ABS,
				.operation = EQT,
				.next_node = RSS_IPV4_TCP_NODE,
				.next_branch = 2,
				.data = 0x0,
				.mask = 0xffff
			पूर्ण,
			अणु
				/* DST IPV4 B01 */
				.valid = 0,
				.next_packet_poपूर्णांकer = 32,
				.jump_bw = JMP_FW,
				.jump_rel = JMP_ABS,
				.operation = EQT,
				.next_node = RSS_IPV4_TCP_NODE,
				.next_branch = 3,
				.data = 0x0,
				.mask = 0xffff
			पूर्ण,
			अणु
				/* DST IPV4 B23 */
				.valid = 0,
				.next_packet_poपूर्णांकer = 34,
				.jump_bw = JMP_FW,
				.jump_rel = JMP_ABS,
				.operation = EQT,
				.next_node = RSS_IPV4_TCP_NODE,
				.next_branch = 4,
				.data = 0x0,
				.mask = 0xffff
			पूर्ण,
			अणु
				/* TCP SRC Port */
				.valid = 0,
				.next_packet_poपूर्णांकer = 36,
				.jump_bw = JMP_FW,
				.jump_rel = JMP_ABS,
				.operation = EQT,
				.next_node = RSS_IPV4_TCP_NODE,
				.next_branch = 5,
				.data = 0x0,
				.mask = 0xffff
			पूर्ण,
			अणु
				/* TCP DST Port */
				.valid = 0,
				.next_packet_poपूर्णांकer = 256,
				.jump_bw = JMP_FW,
				.jump_rel = JMP_ABS,
				.operation = EQT,
				.next_node = LAST_NODE,
				.next_branch = 0,
				.data = 0x0,
				.mask = 0xffff
			पूर्ण
		पूर्ण
	पूर्ण,
	अणु
		/* RSS_IPV4_UDP_NODE */
		.node_type = EWDN,
		.last_node = 0,
		.hdr_len_store = 1,
		.hdr_extn = NO_BYTE,
		.byte_store = NO_BYTE,
		.search_byte_store = BOTH_BYTES,
		.result_poपूर्णांकer = DB_RES_DROP,
		.num_branches = 6,
		.branch = अणु
			अणु
				/* SRC IPV4 B01 */
				.valid = 0,
				.next_packet_poपूर्णांकer = 28,
				.jump_bw = JMP_FW,
				.jump_rel = JMP_ABS,
				.operation = EQT,
				.next_node = RSS_IPV4_UDP_NODE,
				.next_branch = 1,
				.data = 0x0,
				.mask = 0xffff
			पूर्ण,
			अणु
				/* SRC IPV4 B23 */
				.valid = 0,
				.next_packet_poपूर्णांकer = 30,
				.jump_bw = JMP_FW,
				.jump_rel = JMP_ABS,
				.operation = EQT,
				.next_node = RSS_IPV4_UDP_NODE,
				.next_branch = 2,
				.data = 0x0,
				.mask = 0xffff
			पूर्ण,
			अणु
				/* DST IPV4 B01 */
				.valid = 0,
				.next_packet_poपूर्णांकer = 32,
				.jump_bw = JMP_FW,
				.jump_rel = JMP_ABS,
				.operation = EQT,
				.next_node = RSS_IPV4_UDP_NODE,
				.next_branch = 3,
				.data = 0x0,
				.mask = 0xffff
			पूर्ण,
			अणु
				/* DST IPV4 B23 */
				.valid = 0,
				.next_packet_poपूर्णांकer = 34,
				.jump_bw = JMP_FW,
				.jump_rel = JMP_ABS,
				.operation = EQT,
				.next_node = RSS_IPV4_UDP_NODE,
				.next_branch = 4,
				.data = 0x0,
				.mask = 0xffff
			पूर्ण,
			अणु
				/* TCP SRC Port */
				.valid = 0,
				.next_packet_poपूर्णांकer = 36,
				.jump_bw = JMP_FW,
				.jump_rel = JMP_ABS,
				.operation = EQT,
				.next_node = RSS_IPV4_UDP_NODE,
				.next_branch = 5,
				.data = 0x0,
				.mask = 0xffff
			पूर्ण,
			अणु
				/* TCP DST Port */
				.valid = 0,
				.next_packet_poपूर्णांकer = 258,
				.jump_bw = JMP_FW,
				.jump_rel = JMP_ABS,
				.operation = EQT,
				.next_node = LAST_NODE,
				.next_branch = 0,
				.data = 0x0,
				.mask = 0xffff
			पूर्ण
		पूर्ण
	पूर्ण,
	अणु
		/* RSS_IPV4_OTHERS_NODE */
		.node_type = EWDN,
		.last_node = 0,
		.hdr_len_store = 1,
		.hdr_extn = NO_BYTE,
		.byte_store = NO_BYTE,
		.search_byte_store = BOTH_BYTES,
		.result_poपूर्णांकer = DB_RES_DROP,
		.num_branches = 6,
		.branch = अणु
			अणु
				/* SRC IPV4 B01 */
				.valid = 0,
				.next_packet_poपूर्णांकer = 28,
				.jump_bw = JMP_FW,
				.jump_rel = JMP_ABS,
				.operation = EQT,
				.next_node = RSS_IPV4_OTHERS_NODE,
				.next_branch = 1,
				.data = 0x0,
				.mask = 0xffff
			पूर्ण,
			अणु
				/* SRC IPV4 B23 */
				.valid = 0,
				.next_packet_poपूर्णांकer = 30,
				.jump_bw = JMP_FW,
				.jump_rel = JMP_ABS,
				.operation = EQT,
				.next_node = RSS_IPV4_OTHERS_NODE,
				.next_branch = 2,
				.data = 0x0,
				.mask = 0xffff
			पूर्ण,
			अणु
				/* DST IPV4 B01 */
				.valid = 0,
				.next_packet_poपूर्णांकer = 32,
				.jump_bw = JMP_FW,
				.jump_rel = JMP_ABS,
				.operation = EQT,
				.next_node = RSS_IPV4_OTHERS_NODE,
				.next_branch = 3,
				.data = 0x0,
				.mask = 0xffff
			पूर्ण,
			अणु
				/* DST IPV4 B23 */
				.valid = 0,
				.next_packet_poपूर्णांकer = 34,
				.jump_bw = JMP_FW,
				.jump_rel = JMP_ABS,
				.operation = EQT,
				.next_node = RSS_IPV4_OTHERS_NODE,
				.next_branch = 4,
				.data = 0x0,
				.mask = 0xffff
			पूर्ण,
			अणु
				/* TCP SRC Port */
				.valid = 0,
				.next_packet_poपूर्णांकer = 36,
				.jump_bw = JMP_FW,
				.jump_rel = JMP_ABS,
				.operation = EQT,
				.next_node = RSS_IPV4_OTHERS_NODE,
				.next_branch = 5,
				.data = 0x0,
				.mask = 0xffff
			पूर्ण,
			अणु
				/* TCP DST Port */
				.valid = 0,
				.next_packet_poपूर्णांकer = 260,
				.jump_bw = JMP_FW,
				.jump_rel = JMP_ABS,
				.operation = EQT,
				.next_node = LAST_NODE,
				.next_branch = 0,
				.data = 0x0,
				.mask = 0xffff
			पूर्ण
		पूर्ण
	पूर्ण,

	अणु
		/* LAST NODE */
		.node_type = EWDN,
		.last_node = 1,
		.hdr_len_store = 1,
		.hdr_extn = NO_BYTE,
		.byte_store = NO_BYTE,
		.search_byte_store = NO_BYTE,
		.result_poपूर्णांकer = DB_RES_DROP,
		.num_branches = 1,
		.branch = अणु
			अणु
				.valid = 0,
				.next_packet_poपूर्णांकer = 0,
				.jump_bw = JMP_FW,
				.jump_rel = JMP_ABS,
				.operation = EQT,
				.next_node = MAX_NODES,
				.next_branch = 0,
				.data = 0,
				.mask = 0xffff
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण;

अटल पूर्णांक xgene_cle_setup_node(काष्ठा xgene_enet_pdata *pdata,
				काष्ठा xgene_enet_cle *cle)
अणु
	काष्ठा xgene_cle_ptree *ptree = &cle->ptree;
	स्थिर काष्ठा xgene_cle_ptree_ewdn *dn = xgene_init_ptree_dn;
	पूर्णांक num_dn = ARRAY_SIZE(xgene_init_ptree_dn);
	काष्ठा xgene_cle_ptree_kn *kn = ptree->kn;
	u32 buf[CLE_DRAM_REGS];
	पूर्णांक i, j, ret;

	स_रखो(buf, 0, माप(buf));
	क्रम (i = 0; i < num_dn; i++) अणु
		xgene_cle_dn_to_hw(&dn[i], buf, cle->jump_bytes);
		ret = xgene_cle_dram_wr(cle, buf, 17, i + ptree->start_node,
					PTREE_RAM, CLE_CMD_WR);
		अगर (ret)
			वापस ret;
	पूर्ण

	/* जारी node index क्रम key node */
	स_रखो(buf, 0, माप(buf));
	क्रम (j = i; j < (ptree->num_kn + num_dn); j++) अणु
		xgene_cle_kn_to_hw(&kn[j - num_dn], buf);
		ret = xgene_cle_dram_wr(cle, buf, 17, j + ptree->start_node,
					PTREE_RAM, CLE_CMD_WR);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक xgene_cle_setup_ptree(काष्ठा xgene_enet_pdata *pdata,
				 काष्ठा xgene_enet_cle *cle)
अणु
	पूर्णांक ret;

	ret = xgene_cle_setup_node(pdata, cle);
	अगर (ret)
		वापस ret;

	ret = xgene_cle_setup_dbptr(pdata, cle);
	अगर (ret)
		वापस ret;

	xgene_cle_enable_ptree(pdata, cle);

	वापस 0;
पूर्ण

अटल व्योम xgene_cle_setup_def_dbptr(काष्ठा xgene_enet_pdata *pdata,
				      काष्ठा xgene_enet_cle *enet_cle,
				      काष्ठा xgene_cle_dbptr *dbptr,
				      u32 index, u8 priority)
अणु
	व्योम __iomem *base = enet_cle->base;
	व्योम __iomem *base_addr;
	u32 buf[CLE_DRAM_REGS];
	u32 def_cls, offset;
	u32 i, j;

	स_रखो(buf, 0, माप(buf));
	xgene_cle_dbptr_to_hw(pdata, dbptr, buf);

	क्रम (i = 0; i < enet_cle->parsers; i++) अणु
		अगर (enet_cle->active_parser != PARSER_ALL) अणु
			offset = enet_cle->active_parser *
				CLE_PORT_OFFSET;
		पूर्ण अन्यथा अणु
			offset = i * CLE_PORT_OFFSET;
		पूर्ण

		base_addr = base + DFCLSRESDB00 + offset;
		क्रम (j = 0; j < 6; j++)
			ioग_लिखो32(buf[j], base_addr + (j * 4));

		def_cls = ((priority & 0x7) << 10) | (index & 0x3ff);
		ioग_लिखो32(def_cls, base + DFCLSRESDBPTR0 + offset);
	पूर्ण
पूर्ण

अटल पूर्णांक xgene_cle_set_rss_sband(काष्ठा xgene_enet_cle *cle)
अणु
	u32 idx = CLE_PKTRAM_SIZE / माप(u32);
	u32 mac_hdr_len = ETH_HLEN;
	u32 sband, reg = 0;
	u32 ipv4_ihl = 5;
	u32 hdr_len;
	पूर्णांक ret;

	/* Sideband: IPV4/TCP packets */
	hdr_len = (mac_hdr_len << 5) | ipv4_ihl;
	xgene_cle_sband_to_hw(0, XGENE_CLE_IPV4, XGENE_CLE_TCP, hdr_len, &reg);
	sband = reg;

	/* Sideband: IPv4/UDP packets */
	hdr_len = (mac_hdr_len << 5) | ipv4_ihl;
	xgene_cle_sband_to_hw(1, XGENE_CLE_IPV4, XGENE_CLE_UDP, hdr_len, &reg);
	sband |= (reg << 16);

	ret = xgene_cle_dram_wr(cle, &sband, 1, idx, PKT_RAM, CLE_CMD_WR);
	अगर (ret)
		वापस ret;

	/* Sideband: IPv4/RAW packets */
	hdr_len = (mac_hdr_len << 5) | ipv4_ihl;
	xgene_cle_sband_to_hw(0, XGENE_CLE_IPV4, XGENE_CLE_OTHER,
			      hdr_len, &reg);
	sband = reg;

	/* Sideband: Ethernet II/RAW packets */
	hdr_len = (mac_hdr_len << 5);
	xgene_cle_sband_to_hw(0, XGENE_CLE_IPV4, XGENE_CLE_OTHER,
			      hdr_len, &reg);
	sband |= (reg << 16);

	ret = xgene_cle_dram_wr(cle, &sband, 1, idx + 1, PKT_RAM, CLE_CMD_WR);
	अगर (ret)
		वापस ret;

	वापस 0;
पूर्ण

अटल पूर्णांक xgene_cle_set_rss_skeys(काष्ठा xgene_enet_cle *cle)
अणु
	u32 secret_key_ipv4[4];  /* 16 Bytes*/
	पूर्णांक ret = 0;

	get_अक्रमom_bytes(secret_key_ipv4, 16);
	ret = xgene_cle_dram_wr(cle, secret_key_ipv4, 4, 0,
				RSS_IPV4_HASH_SKEY, CLE_CMD_WR);
	वापस ret;
पूर्ण

अटल पूर्णांक xgene_cle_set_rss_idt(काष्ठा xgene_enet_pdata *pdata)
अणु
	u32 fpsel, dstqid, nfpsel, idt_reg, idx;
	पूर्णांक i, ret = 0;
	u16 pool_id;

	क्रम (i = 0; i < XGENE_CLE_IDT_ENTRIES; i++) अणु
		idx = i % pdata->rxq_cnt;
		pool_id = pdata->rx_ring[idx]->buf_pool->id;
		fpsel = xgene_enet_get_fpsel(pool_id);
		dstqid = xgene_enet_dst_ring_num(pdata->rx_ring[idx]);
		nfpsel = 0;
		अगर (pdata->rx_ring[idx]->page_pool) अणु
			pool_id = pdata->rx_ring[idx]->page_pool->id;
			nfpsel = xgene_enet_get_fpsel(pool_id);
		पूर्ण

		idt_reg = 0;
		xgene_cle_idt_to_hw(pdata, dstqid, fpsel, nfpsel, &idt_reg);
		ret = xgene_cle_dram_wr(&pdata->cle, &idt_reg, 1, i,
					RSS_IDT, CLE_CMD_WR);
		अगर (ret)
			वापस ret;
	पूर्ण

	ret = xgene_cle_set_rss_skeys(&pdata->cle);
	अगर (ret)
		वापस ret;

	वापस 0;
पूर्ण

अटल पूर्णांक xgene_cle_setup_rss(काष्ठा xgene_enet_pdata *pdata)
अणु
	काष्ठा xgene_enet_cle *cle = &pdata->cle;
	व्योम __iomem *base = cle->base;
	u32 offset, val = 0;
	पूर्णांक i, ret = 0;

	offset = CLE_PORT_OFFSET;
	क्रम (i = 0; i < cle->parsers; i++) अणु
		अगर (cle->active_parser != PARSER_ALL)
			offset = cle->active_parser * CLE_PORT_OFFSET;
		अन्यथा
			offset = i * CLE_PORT_OFFSET;

		/* enable RSS */
		val = (RSS_IPV4_12B << 1) | 0x1;
		ग_लिखोl(val, base + RSS_CTRL0 + offset);
	पूर्ण

	/* setup sideband data */
	ret = xgene_cle_set_rss_sband(cle);
	अगर (ret)
		वापस ret;

	/* setup indirection table */
	ret = xgene_cle_set_rss_idt(pdata);
	अगर (ret)
		वापस ret;

	वापस 0;
पूर्ण

अटल पूर्णांक xgene_enet_cle_init(काष्ठा xgene_enet_pdata *pdata)
अणु
	काष्ठा xgene_enet_cle *enet_cle = &pdata->cle;
	u32 def_qid, def_fpsel, def_nxtfpsel, pool_id;
	काष्ठा xgene_cle_dbptr dbptr[DB_MAX_PTRS];
	काष्ठा xgene_cle_ptree *ptree;
	काष्ठा xgene_cle_ptree_kn kn;
	पूर्णांक ret;

	अगर (pdata->phy_mode != PHY_INTERFACE_MODE_XGMII)
		वापस -EINVAL;

	ptree = &enet_cle->ptree;
	ptree->start_pkt = 12; /* Ethertype */

	ret = xgene_cle_setup_rss(pdata);
	अगर (ret) अणु
		netdev_err(pdata->ndev, "RSS initialization failed\n");
		वापस ret;
	पूर्ण

	def_qid = xgene_enet_dst_ring_num(pdata->rx_ring[0]);
	pool_id = pdata->rx_ring[0]->buf_pool->id;
	def_fpsel = xgene_enet_get_fpsel(pool_id);
	def_nxtfpsel = 0;
	अगर (pdata->rx_ring[0]->page_pool) अणु
		pool_id = pdata->rx_ring[0]->page_pool->id;
		def_nxtfpsel = xgene_enet_get_fpsel(pool_id);
	पूर्ण

	स_रखो(dbptr, 0, माप(काष्ठा xgene_cle_dbptr) * DB_MAX_PTRS);
	dbptr[DB_RES_ACCEPT].fpsel =  def_fpsel;
	dbptr[DB_RES_ACCEPT].nxtfpsel = def_nxtfpsel;
	dbptr[DB_RES_ACCEPT].dstqid = def_qid;
	dbptr[DB_RES_ACCEPT].cle_priority = 1;

	dbptr[DB_RES_DEF].fpsel = def_fpsel;
	dbptr[DB_RES_DEF].nxtfpsel = def_nxtfpsel;
	dbptr[DB_RES_DEF].dstqid = def_qid;
	dbptr[DB_RES_DEF].cle_priority = 7;
	xgene_cle_setup_def_dbptr(pdata, enet_cle, &dbptr[DB_RES_DEF],
				  DB_RES_ACCEPT, 7);

	dbptr[DB_RES_DROP].drop = 1;

	स_रखो(&kn, 0, माप(kn));
	kn.node_type = KN;
	kn.num_keys = 1;
	kn.key[0].priority = 0;
	kn.key[0].result_poपूर्णांकer = DB_RES_ACCEPT;

	ptree->kn = &kn;
	ptree->dbptr = dbptr;
	ptree->num_kn = 1;
	ptree->num_dbptr = DB_MAX_PTRS;

	वापस xgene_cle_setup_ptree(pdata, enet_cle);
पूर्ण

स्थिर काष्ठा xgene_cle_ops xgene_cle3in_ops = अणु
	.cle_init = xgene_enet_cle_init,
पूर्ण;
