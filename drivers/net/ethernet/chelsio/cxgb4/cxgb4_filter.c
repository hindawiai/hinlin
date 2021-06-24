<शैली गुरु>
/*
 * This file is part of the Chelsio T4 Ethernet driver क्रम Linux.
 *
 * Copyright (c) 2003-2016 Chelsio Communications, Inc. All rights reserved.
 *
 * This software is available to you under a choice of one of two
 * licenses.  You may choose to be licensed under the terms of the GNU
 * General Public License (GPL) Version 2, available from the file
 * COPYING in the मुख्य directory of this source tree, or the
 * OpenIB.org BSD license below:
 *
 *     Redistribution and use in source and binary क्रमms, with or
 *     without modअगरication, are permitted provided that the following
 *     conditions are met:
 *
 *      - Redistributions of source code must retain the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer.
 *
 *      - Redistributions in binary क्रमm must reproduce the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer in the करोcumentation and/or other materials
 *        provided with the distribution.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
#समावेश <net/ipv6.h>

#समावेश "cxgb4.h"
#समावेश "t4_regs.h"
#समावेश "t4_tcb.h"
#समावेश "t4_values.h"
#समावेश "clip_tbl.h"
#समावेश "l2t.h"
#समावेश "smt.h"
#समावेश "t4fw_api.h"
#समावेश "cxgb4_filter.h"

अटल अंतरभूत bool is_field_set(u32 val, u32 mask)
अणु
	वापस val || mask;
पूर्ण

अटल अंतरभूत bool unsupported(u32 conf, u32 conf_mask, u32 val, u32 mask)
अणु
	वापस !(conf & conf_mask) && is_field_set(val, mask);
पूर्ण

अटल पूर्णांक set_tcb_field(काष्ठा adapter *adap, काष्ठा filter_entry *f,
			 अचिन्हित पूर्णांक ftid,  u16 word, u64 mask, u64 val,
			 पूर्णांक no_reply)
अणु
	काष्ठा cpl_set_tcb_field *req;
	काष्ठा sk_buff *skb;

	skb = alloc_skb(माप(काष्ठा cpl_set_tcb_field), GFP_ATOMIC);
	अगर (!skb)
		वापस -ENOMEM;

	req = (काष्ठा cpl_set_tcb_field *)__skb_put_zero(skb, माप(*req));
	INIT_TP_WR_CPL(req, CPL_SET_TCB_FIELD, ftid);
	req->reply_ctrl = htons(REPLY_CHAN_V(0) |
				QUEUENO_V(adap->sge.fw_evtq.असल_id) |
				NO_REPLY_V(no_reply));
	req->word_cookie = htons(TCB_WORD_V(word) | TCB_COOKIE_V(ftid));
	req->mask = cpu_to_be64(mask);
	req->val = cpu_to_be64(val);
	set_wr_txq(skb, CPL_PRIORITY_CONTROL, f->fs.val.iport & 0x3);
	t4_ofld_send(adap, skb);
	वापस 0;
पूर्ण

/* Set one of the t_flags bits in the TCB.
 */
अटल पूर्णांक set_tcb_tflag(काष्ठा adapter *adap, काष्ठा filter_entry *f,
			 अचिन्हित पूर्णांक ftid, अचिन्हित पूर्णांक bit_pos,
			 अचिन्हित पूर्णांक val, पूर्णांक no_reply)
अणु
	वापस set_tcb_field(adap, f, ftid,  TCB_T_FLAGS_W, 1ULL << bit_pos,
			     (अचिन्हित दीर्घ दीर्घ)val << bit_pos, no_reply);
पूर्ण

अटल व्योम mk_पात_req_ulp(काष्ठा cpl_पात_req *पात_req, अचिन्हित पूर्णांक tid)
अणु
	काष्ठा ulp_txpkt *txpkt = (काष्ठा ulp_txpkt *)पात_req;
	काष्ठा ulptx_idata *sc = (काष्ठा ulptx_idata *)(txpkt + 1);

	txpkt->cmd_dest = htonl(ULPTX_CMD_V(ULP_TX_PKT) | ULP_TXPKT_DEST_V(0));
	txpkt->len = htonl(DIV_ROUND_UP(माप(*पात_req), 16));
	sc->cmd_more = htonl(ULPTX_CMD_V(ULP_TX_SC_IMM));
	sc->len = htonl(माप(*पात_req) - माप(काष्ठा work_request_hdr));
	OPCODE_TID(पात_req) = htonl(MK_OPCODE_TID(CPL_ABORT_REQ, tid));
	पात_req->rsvd0 = htonl(0);
	पात_req->rsvd1 = 0;
	पात_req->cmd = CPL_ABORT_NO_RST;
पूर्ण

अटल व्योम mk_पात_rpl_ulp(काष्ठा cpl_पात_rpl *पात_rpl, अचिन्हित पूर्णांक tid)
अणु
	काष्ठा ulp_txpkt *txpkt = (काष्ठा ulp_txpkt *)पात_rpl;
	काष्ठा ulptx_idata *sc = (काष्ठा ulptx_idata *)(txpkt + 1);

	txpkt->cmd_dest = htonl(ULPTX_CMD_V(ULP_TX_PKT) | ULP_TXPKT_DEST_V(0));
	txpkt->len = htonl(DIV_ROUND_UP(माप(*पात_rpl), 16));
	sc->cmd_more = htonl(ULPTX_CMD_V(ULP_TX_SC_IMM));
	sc->len = htonl(माप(*पात_rpl) - माप(काष्ठा work_request_hdr));
	OPCODE_TID(पात_rpl) = htonl(MK_OPCODE_TID(CPL_ABORT_RPL, tid));
	पात_rpl->rsvd0 = htonl(0);
	पात_rpl->rsvd1 = 0;
	पात_rpl->cmd = CPL_ABORT_NO_RST;
पूर्ण

अटल व्योम mk_set_tcb_ulp(काष्ठा filter_entry *f,
			   काष्ठा cpl_set_tcb_field *req,
			   अचिन्हित पूर्णांक word, u64 mask, u64 val,
			   u8 cookie, पूर्णांक no_reply)
अणु
	काष्ठा ulp_txpkt *txpkt = (काष्ठा ulp_txpkt *)req;
	काष्ठा ulptx_idata *sc = (काष्ठा ulptx_idata *)(txpkt + 1);

	txpkt->cmd_dest = htonl(ULPTX_CMD_V(ULP_TX_PKT) | ULP_TXPKT_DEST_V(0));
	txpkt->len = htonl(DIV_ROUND_UP(माप(*req), 16));
	sc->cmd_more = htonl(ULPTX_CMD_V(ULP_TX_SC_IMM));
	sc->len = htonl(माप(*req) - माप(काष्ठा work_request_hdr));
	OPCODE_TID(req) = htonl(MK_OPCODE_TID(CPL_SET_TCB_FIELD, f->tid));
	req->reply_ctrl = htons(NO_REPLY_V(no_reply) | REPLY_CHAN_V(0) |
				QUEUENO_V(0));
	req->word_cookie = htons(TCB_WORD_V(word) | TCB_COOKIE_V(cookie));
	req->mask = cpu_to_be64(mask);
	req->val = cpu_to_be64(val);
	sc = (काष्ठा ulptx_idata *)(req + 1);
	sc->cmd_more = htonl(ULPTX_CMD_V(ULP_TX_SC_NOOP));
	sc->len = htonl(0);
पूर्ण

अटल पूर्णांक configure_filter_smac(काष्ठा adapter *adap, काष्ठा filter_entry *f)
अणु
	पूर्णांक err;

	/* करो a set-tcb क्रम smac-sel and CWR bit.. */
	err = set_tcb_field(adap, f, f->tid, TCB_SMAC_SEL_W,
			    TCB_SMAC_SEL_V(TCB_SMAC_SEL_M),
			    TCB_SMAC_SEL_V(f->smt->idx), 1);
	अगर (err)
		जाओ smac_err;

	err = set_tcb_tflag(adap, f, f->tid, TF_CCTRL_CWR_S, 1, 1);
	अगर (!err)
		वापस 0;

smac_err:
	dev_err(adap->pdev_dev, "filter %u smac config failed with error %u\n",
		f->tid, err);
	वापस err;
पूर्ण

अटल व्योम set_nat_params(काष्ठा adapter *adap, काष्ठा filter_entry *f,
			   अचिन्हित पूर्णांक tid, bool dip, bool sip, bool dp,
			   bool sp)
अणु
	u8 *nat_lp = (u8 *)&f->fs.nat_lport;
	u8 *nat_fp = (u8 *)&f->fs.nat_fport;

	अगर (dip) अणु
		अगर (f->fs.type) अणु
			set_tcb_field(adap, f, tid, TCB_SND_UNA_RAW_W,
				      WORD_MASK, f->fs.nat_lip[15] |
				      f->fs.nat_lip[14] << 8 |
				      f->fs.nat_lip[13] << 16 |
				      (u64)f->fs.nat_lip[12] << 24, 1);

			set_tcb_field(adap, f, tid, TCB_SND_UNA_RAW_W + 1,
				      WORD_MASK, f->fs.nat_lip[11] |
				      f->fs.nat_lip[10] << 8 |
				      f->fs.nat_lip[9] << 16 |
				      (u64)f->fs.nat_lip[8] << 24, 1);

			set_tcb_field(adap, f, tid, TCB_SND_UNA_RAW_W + 2,
				      WORD_MASK, f->fs.nat_lip[7] |
				      f->fs.nat_lip[6] << 8 |
				      f->fs.nat_lip[5] << 16 |
				      (u64)f->fs.nat_lip[4] << 24, 1);

			set_tcb_field(adap, f, tid, TCB_SND_UNA_RAW_W + 3,
				      WORD_MASK, f->fs.nat_lip[3] |
				      f->fs.nat_lip[2] << 8 |
				      f->fs.nat_lip[1] << 16 |
				      (u64)f->fs.nat_lip[0] << 24, 1);
		पूर्ण अन्यथा अणु
			set_tcb_field(adap, f, tid, TCB_RX_FRAG3_LEN_RAW_W,
				      WORD_MASK, f->fs.nat_lip[3] |
				      f->fs.nat_lip[2] << 8 |
				      f->fs.nat_lip[1] << 16 |
				      (u64)f->fs.nat_lip[0] << 24, 1);
		पूर्ण
	पूर्ण

	अगर (sip) अणु
		अगर (f->fs.type) अणु
			set_tcb_field(adap, f, tid, TCB_RX_FRAG2_PTR_RAW_W,
				      WORD_MASK, f->fs.nat_fip[15] |
				      f->fs.nat_fip[14] << 8 |
				      f->fs.nat_fip[13] << 16 |
				      (u64)f->fs.nat_fip[12] << 24, 1);

			set_tcb_field(adap, f, tid, TCB_RX_FRAG2_PTR_RAW_W + 1,
				      WORD_MASK, f->fs.nat_fip[11] |
				      f->fs.nat_fip[10] << 8 |
				      f->fs.nat_fip[9] << 16 |
				      (u64)f->fs.nat_fip[8] << 24, 1);

			set_tcb_field(adap, f, tid, TCB_RX_FRAG2_PTR_RAW_W + 2,
				      WORD_MASK, f->fs.nat_fip[7] |
				      f->fs.nat_fip[6] << 8 |
				      f->fs.nat_fip[5] << 16 |
				      (u64)f->fs.nat_fip[4] << 24, 1);

			set_tcb_field(adap, f, tid, TCB_RX_FRAG2_PTR_RAW_W + 3,
				      WORD_MASK, f->fs.nat_fip[3] |
				      f->fs.nat_fip[2] << 8 |
				      f->fs.nat_fip[1] << 16 |
				      (u64)f->fs.nat_fip[0] << 24, 1);

		पूर्ण अन्यथा अणु
			set_tcb_field(adap, f, tid,
				      TCB_RX_FRAG3_START_IDX_OFFSET_RAW_W,
				      WORD_MASK, f->fs.nat_fip[3] |
				      f->fs.nat_fip[2] << 8 |
				      f->fs.nat_fip[1] << 16 |
				      (u64)f->fs.nat_fip[0] << 24, 1);
		पूर्ण
	पूर्ण

	set_tcb_field(adap, f, tid, TCB_PDU_HDR_LEN_W, WORD_MASK,
		      (dp ? (nat_lp[1] | nat_lp[0] << 8) : 0) |
		      (sp ? (nat_fp[1] << 16 | (u64)nat_fp[0] << 24) : 0),
		      1);
पूर्ण

/* Validate filter spec against configuration करोne on the card. */
अटल पूर्णांक validate_filter(काष्ठा net_device *dev,
			   काष्ठा ch_filter_specअगरication *fs)
अणु
	काष्ठा adapter *adapter = netdev2adap(dev);
	u32 fconf, iconf;

	/* Check क्रम unconfigured fields being used. */
	iconf = adapter->params.tp.ingress_config;
	fconf = fs->hash ? adapter->params.tp.filter_mask :
			   adapter->params.tp.vlan_pri_map;

	अगर (unsupported(fconf, FCOE_F, fs->val.fcoe, fs->mask.fcoe) ||
	    unsupported(fconf, PORT_F, fs->val.iport, fs->mask.iport) ||
	    unsupported(fconf, TOS_F, fs->val.tos, fs->mask.tos) ||
	    unsupported(fconf, ETHERTYPE_F, fs->val.ethtype,
			fs->mask.ethtype) ||
	    unsupported(fconf, MACMATCH_F, fs->val.macidx, fs->mask.macidx) ||
	    unsupported(fconf, MPSHITTYPE_F, fs->val.matchtype,
			fs->mask.matchtype) ||
	    unsupported(fconf, FRAGMENTATION_F, fs->val.frag, fs->mask.frag) ||
	    unsupported(fconf, PROTOCOL_F, fs->val.proto, fs->mask.proto) ||
	    unsupported(fconf, VNIC_ID_F, fs->val.pfvf_vld,
			fs->mask.pfvf_vld) ||
	    unsupported(fconf, VNIC_ID_F, fs->val.ovlan_vld,
			fs->mask.ovlan_vld) ||
	    unsupported(fconf, VNIC_ID_F, fs->val.encap_vld,
			fs->mask.encap_vld) ||
	    unsupported(fconf, VLAN_F, fs->val.ivlan_vld, fs->mask.ivlan_vld))
		वापस -EOPNOTSUPP;

	/* T4 inconveniently uses the same FT_VNIC_ID_W bits क्रम both the Outer
	 * VLAN Tag and PF/VF/VFvld fields based on VNIC_F being set
	 * in TP_INGRESS_CONFIG.  Hense the somewhat crazy checks
	 * below.  Additionally, since the T4 firmware पूर्णांकerface also
	 * carries that overlap, we need to translate any PF/VF
	 * specअगरication पूर्णांकo that पूर्णांकernal क्रमmat below.
	 */
	अगर ((is_field_set(fs->val.pfvf_vld, fs->mask.pfvf_vld) &&
	     is_field_set(fs->val.ovlan_vld, fs->mask.ovlan_vld)) ||
	    (is_field_set(fs->val.pfvf_vld, fs->mask.pfvf_vld) &&
	     is_field_set(fs->val.encap_vld, fs->mask.encap_vld)) ||
	    (is_field_set(fs->val.ovlan_vld, fs->mask.ovlan_vld) &&
	     is_field_set(fs->val.encap_vld, fs->mask.encap_vld)))
		वापस -EOPNOTSUPP;
	अगर (unsupported(iconf, VNIC_F, fs->val.pfvf_vld, fs->mask.pfvf_vld) ||
	    (is_field_set(fs->val.ovlan_vld, fs->mask.ovlan_vld) &&
	     (iconf & VNIC_F)))
		वापस -EOPNOTSUPP;
	अगर (fs->val.pf > 0x7 || fs->val.vf > 0x7f)
		वापस -दुस्फल;
	fs->mask.pf &= 0x7;
	fs->mask.vf &= 0x7f;

	/* If the user is requesting that the filter action loop
	 * matching packets back out one of our ports, make sure that
	 * the egress port is in range.
	 */
	अगर (fs->action == FILTER_SWITCH &&
	    fs->eport >= adapter->params.nports)
		वापस -दुस्फल;

	/* Don't allow various trivially obvious bogus out-of-range values... */
	अगर (fs->val.iport >= adapter->params.nports)
		वापस -दुस्फल;

	/* T4 करोesn't support removing VLAN Tags क्रम loop back filters. */
	अगर (is_t4(adapter->params.chip) &&
	    fs->action == FILTER_SWITCH &&
	    (fs->newvlan == VLAN_REMOVE ||
	     fs->newvlan == VLAN_REWRITE))
		वापस -EOPNOTSUPP;

	अगर (fs->val.encap_vld &&
	    CHELSIO_CHIP_VERSION(adapter->params.chip) < CHELSIO_T6)
		वापस -EOPNOTSUPP;
	वापस 0;
पूर्ण

अटल पूर्णांक get_filter_steerq(काष्ठा net_device *dev,
			     काष्ठा ch_filter_specअगरication *fs)
अणु
	काष्ठा adapter *adapter = netdev2adap(dev);
	पूर्णांक iq;

	/* If the user has requested steering matching Ingress Packets
	 * to a specअगरic Queue Set, we need to make sure it's in range
	 * क्रम the port and map that पूर्णांकo the Absolute Queue ID of the
	 * Queue Set's Response Queue.
	 */
	अगर (!fs->dirsteer) अणु
		अगर (fs->iq)
			वापस -EINVAL;
		iq = 0;
	पूर्ण अन्यथा अणु
		काष्ठा port_info *pi = netdev_priv(dev);

		/* If the iq id is greater than the number of qsets,
		 * then assume it is an असलolute qid.
		 */
		अगर (fs->iq < pi->nqsets)
			iq = adapter->sge.ethrxq[pi->first_qset +
						 fs->iq].rspq.असल_id;
		अन्यथा
			iq = fs->iq;
	पूर्ण

	वापस iq;
पूर्ण

अटल पूर्णांक get_filter_count(काष्ठा adapter *adapter, अचिन्हित पूर्णांक fidx,
			    u64 *pkts, u64 *bytes, bool hash)
अणु
	अचिन्हित पूर्णांक tcb_base, tcbaddr;
	अचिन्हित पूर्णांक word_offset;
	काष्ठा filter_entry *f;
	__be64 be64_byte_count;
	पूर्णांक ret;

	tcb_base = t4_पढ़ो_reg(adapter, TP_CMM_TCB_BASE_A);
	अगर (is_hashfilter(adapter) && hash) अणु
		अगर (tid_out_of_range(&adapter->tids, fidx))
			वापस -E2BIG;
		f = adapter->tids.tid_tab[fidx - adapter->tids.tid_base];
		अगर (!f)
			वापस -EINVAL;
	पूर्ण अन्यथा अणु
		अगर ((fidx != (adapter->tids.nftids + adapter->tids.nsftids +
			      adapter->tids.nhpftids - 1)) &&
		    fidx >= (adapter->tids.nftids + adapter->tids.nhpftids))
			वापस -E2BIG;

		अगर (fidx < adapter->tids.nhpftids)
			f = &adapter->tids.hpftid_tab[fidx];
		अन्यथा
			f = &adapter->tids.ftid_tab[fidx -
						    adapter->tids.nhpftids];
		अगर (!f->valid)
			वापस -EINVAL;
	पूर्ण
	tcbaddr = tcb_base + f->tid * TCB_SIZE;

	spin_lock(&adapter->win0_lock);
	अगर (is_t4(adapter->params.chip)) अणु
		__be64 be64_count;

		/* T4 करोesn't मुख्यtain byte counts in hw */
		*bytes = 0;

		/* Get pkts */
		word_offset = 4;
		ret = t4_memory_rw(adapter, MEMWIN_NIC, MEM_EDC0,
				   tcbaddr + (word_offset * माप(__be32)),
				   माप(be64_count),
				   (__be32 *)&be64_count,
				   T4_MEMORY_READ);
		अगर (ret < 0)
			जाओ out;
		*pkts = be64_to_cpu(be64_count);
	पूर्ण अन्यथा अणु
		__be32 be32_count;

		/* Get bytes */
		word_offset = 4;
		ret = t4_memory_rw(adapter, MEMWIN_NIC, MEM_EDC0,
				   tcbaddr + (word_offset * माप(__be32)),
				   माप(be64_byte_count),
				   &be64_byte_count,
				   T4_MEMORY_READ);
		अगर (ret < 0)
			जाओ out;
		*bytes = be64_to_cpu(be64_byte_count);

		/* Get pkts */
		word_offset = 6;
		ret = t4_memory_rw(adapter, MEMWIN_NIC, MEM_EDC0,
				   tcbaddr + (word_offset * माप(__be32)),
				   माप(be32_count),
				   &be32_count,
				   T4_MEMORY_READ);
		अगर (ret < 0)
			जाओ out;
		*pkts = (u64)be32_to_cpu(be32_count);
	पूर्ण

out:
	spin_unlock(&adapter->win0_lock);
	वापस ret;
पूर्ण

पूर्णांक cxgb4_get_filter_counters(काष्ठा net_device *dev, अचिन्हित पूर्णांक fidx,
			      u64 *hitcnt, u64 *bytecnt, bool hash)
अणु
	काष्ठा adapter *adapter = netdev2adap(dev);

	वापस get_filter_count(adapter, fidx, hitcnt, bytecnt, hash);
पूर्ण

अटल bool cxgb4_filter_prio_in_range(काष्ठा tid_info *t, u32 idx, u8 nslots,
				       u32 prio)
अणु
	काष्ठा filter_entry *prev_tab, *next_tab, *prev_fe, *next_fe;
	u32 prev_ftid, next_ftid;

	/* Only insert the rule अगर both of the following conditions
	 * are met:
	 * 1. The immediate previous rule has priority <= @prio.
	 * 2. The immediate next rule has priority >= @prio.
	 */

	/* High Priority (HPFILTER) region always has higher priority
	 * than normal FILTER region. So, all rules in HPFILTER region
	 * must have prio value <= rules in normal FILTER region.
	 */
	अगर (idx < t->nhpftids) अणु
		/* Don't insert if there's a rule alपढ़ोy present at @idx
		 * in HPFILTER region.
		 */
		अगर (test_bit(idx, t->hpftid_bmap))
			वापस false;

		next_tab = t->hpftid_tab;
		next_ftid = find_next_bit(t->hpftid_bmap, t->nhpftids, idx);
		अगर (next_ftid >= t->nhpftids) अणु
			/* No next entry found in HPFILTER region.
			 * See अगर there's any next entry in normal
			 * FILTER region.
			 */
			next_ftid = find_first_bit(t->ftid_bmap, t->nftids);
			अगर (next_ftid >= t->nftids)
				next_ftid = idx;
			अन्यथा
				next_tab = t->ftid_tab;
		पूर्ण

		/* Search क्रम the बंदst previous filter entry in HPFILTER
		 * region. No need to search in normal FILTER region because
		 * there can never be any entry in normal FILTER region whose
		 * prio value is < last entry in HPFILTER region.
		 */
		prev_ftid = find_last_bit(t->hpftid_bmap, idx);
		अगर (prev_ftid >= idx)
			prev_ftid = idx;

		prev_tab = t->hpftid_tab;
	पूर्ण अन्यथा अणु
		idx -= t->nhpftids;

		/* Don't insert if there's a rule alपढ़ोy present at @idx
		 * in normal FILTER region.
		 */
		अगर (test_bit(idx, t->ftid_bmap))
			वापस false;

		prev_tab = t->ftid_tab;
		prev_ftid = find_last_bit(t->ftid_bmap, idx);
		अगर (prev_ftid >= idx) अणु
			/* No previous entry found in normal FILTER
			 * region. See अगर there's any previous entry
			 * in HPFILTER region.
			 */
			prev_ftid = find_last_bit(t->hpftid_bmap, t->nhpftids);
			अगर (prev_ftid >= t->nhpftids)
				prev_ftid = idx;
			अन्यथा
				prev_tab = t->hpftid_tab;
		पूर्ण

		/* Search क्रम the बंदst next filter entry in normal
		 * FILTER region. No need to search in HPFILTER region
		 * because there can never be any entry in HPFILTER
		 * region whose prio value is > first entry in normal
		 * FILTER region.
		 */
		next_ftid = find_next_bit(t->ftid_bmap, t->nftids, idx);
		अगर (next_ftid >= t->nftids)
			next_ftid = idx;

		next_tab = t->ftid_tab;
	पूर्ण

	next_fe = &next_tab[next_ftid];

	/* See अगर the filter entry beदीर्घs to an IPv6 rule, which
	 * occupy 4 slots on T5 and 2 slots on T6. Adjust the
	 * reference to the previously inserted filter entry
	 * accordingly.
	 */
	prev_fe = &prev_tab[prev_ftid & ~(nslots - 1)];
	अगर (!prev_fe->fs.type)
		prev_fe = &prev_tab[prev_ftid];

	अगर ((prev_fe->valid && prev_fe->fs.tc_prio > prio) ||
	    (next_fe->valid && next_fe->fs.tc_prio < prio))
		वापस false;

	वापस true;
पूर्ण

पूर्णांक cxgb4_get_मुक्त_ftid(काष्ठा net_device *dev, u8 family, bool hash_en,
			u32 tc_prio)
अणु
	काष्ठा adapter *adap = netdev2adap(dev);
	काष्ठा tid_info *t = &adap->tids;
	u32 bmap_ftid, max_ftid;
	काष्ठा filter_entry *f;
	अचिन्हित दीर्घ *bmap;
	bool found = false;
	u8 i, cnt, n;
	पूर्णांक ftid = 0;

	/* IPv4 occupy 1 slot. IPv6 occupy 2 slots on T6 and 4 slots
	 * on T5.
	 */
	n = 1;
	अगर (family == PF_INET6) अणु
		n++;
		अगर (CHELSIO_CHIP_VERSION(adap->params.chip) < CHELSIO_T6)
			n += 2;
	पूर्ण

	/* There are 3 filter regions available in hardware in
	 * following order of priority:
	 *
	 * 1. High Priority (HPFILTER) region (Highest Priority).
	 * 2. HASH region.
	 * 3. Normal FILTER region (Lowest Priority).
	 *
	 * Entries in HPFILTER and normal FILTER region have index
	 * 0 as the highest priority and the rules will be scanned
	 * in ascending order until either a rule hits or end of
	 * the region is reached.
	 *
	 * All HASH region entries have same priority. The set of
	 * fields to match in headers are pre-determined. The same
	 * set of header match fields must be compulsorily specअगरied
	 * in all the rules wanting to get inserted in HASH region.
	 * Hence, HASH region is an exact-match region. A HASH is
	 * generated क्रम a rule based on the values in the
	 * pre-determined set of header match fields. The generated
	 * HASH serves as an index पूर्णांकo the HASH region. There can
	 * never be 2 rules having the same HASH. Hardware will
	 * compute a HASH क्रम every incoming packet based on the
	 * values in the pre-determined set of header match fields
	 * and uses it as an index to check अगर there's a rule
	 * inserted in the HASH region at the specअगरied index. If
	 * there's a rule inserted, then it's considered as a filter
	 * hit. Otherwise, it's a filter miss and normal FILTER region
	 * is scanned afterwards.
	 */

	spin_lock_bh(&t->ftid_lock);

	ftid = (tc_prio <= t->nhpftids) ? 0 : t->nhpftids;
	max_ftid = t->nftids + t->nhpftids;
	जबतक (ftid < max_ftid) अणु
		अगर (ftid < t->nhpftids) अणु
			/* If the new rule wants to get inserted पूर्णांकo
			 * HPFILTER region, but its prio is greater
			 * than the rule with the highest prio in HASH
			 * region, or अगर there's not enough slots
			 * available in HPFILTER region, then skip
			 * trying to insert this rule पूर्णांकo HPFILTER
			 * region and directly go to the next region.
			 */
			अगर ((t->tc_hash_tids_max_prio &&
			     tc_prio > t->tc_hash_tids_max_prio) ||
			     (ftid + n) > t->nhpftids) अणु
				ftid = t->nhpftids;
				जारी;
			पूर्ण

			bmap = t->hpftid_bmap;
			bmap_ftid = ftid;
		पूर्ण अन्यथा अगर (hash_en) अणु
			/* Ensure priority is >= last rule in HPFILTER
			 * region.
			 */
			ftid = find_last_bit(t->hpftid_bmap, t->nhpftids);
			अगर (ftid < t->nhpftids) अणु
				f = &t->hpftid_tab[ftid];
				अगर (f->valid && tc_prio < f->fs.tc_prio)
					अवरोध;
			पूर्ण

			/* Ensure priority is <= first rule in normal
			 * FILTER region.
			 */
			ftid = find_first_bit(t->ftid_bmap, t->nftids);
			अगर (ftid < t->nftids) अणु
				f = &t->ftid_tab[ftid];
				अगर (f->valid && tc_prio > f->fs.tc_prio)
					अवरोध;
			पूर्ण

			found = true;
			ftid = t->nhpftids;
			जाओ out_unlock;
		पूर्ण अन्यथा अणु
			/* If the new rule wants to get inserted पूर्णांकo
			 * normal FILTER region, but its prio is less
			 * than the rule with the highest prio in HASH
			 * region, then reject the rule.
			 */
			अगर (t->tc_hash_tids_max_prio &&
			    tc_prio < t->tc_hash_tids_max_prio)
				अवरोध;

			अगर (ftid + n > max_ftid)
				अवरोध;

			bmap = t->ftid_bmap;
			bmap_ftid = ftid - t->nhpftids;
		पूर्ण

		cnt = 0;
		क्रम (i = 0; i < n; i++) अणु
			अगर (test_bit(bmap_ftid + i, bmap))
				अवरोध;
			cnt++;
		पूर्ण

		अगर (cnt == n) अणु
			/* Ensure the new rule's prio doesn't conflict
			 * with existing rules.
			 */
			अगर (cxgb4_filter_prio_in_range(t, ftid, n,
						       tc_prio)) अणु
				ftid &= ~(n - 1);
				found = true;
				अवरोध;
			पूर्ण
		पूर्ण

		ftid += n;
	पूर्ण

out_unlock:
	spin_unlock_bh(&t->ftid_lock);
	वापस found ? ftid : -ENOMEM;
पूर्ण

अटल पूर्णांक cxgb4_set_ftid(काष्ठा tid_info *t, पूर्णांक fidx, पूर्णांक family,
			  अचिन्हित पूर्णांक chip_ver)
अणु
	spin_lock_bh(&t->ftid_lock);

	अगर (test_bit(fidx, t->ftid_bmap)) अणु
		spin_unlock_bh(&t->ftid_lock);
		वापस -EBUSY;
	पूर्ण

	अगर (family == PF_INET) अणु
		__set_bit(fidx, t->ftid_bmap);
	पूर्ण अन्यथा अणु
		अगर (chip_ver < CHELSIO_T6)
			biपंचांगap_allocate_region(t->ftid_bmap, fidx, 2);
		अन्यथा
			biपंचांगap_allocate_region(t->ftid_bmap, fidx, 1);
	पूर्ण

	spin_unlock_bh(&t->ftid_lock);
	वापस 0;
पूर्ण

अटल पूर्णांक cxgb4_set_hpftid(काष्ठा tid_info *t, पूर्णांक fidx, पूर्णांक family)
अणु
	spin_lock_bh(&t->ftid_lock);

	अगर (test_bit(fidx, t->hpftid_bmap)) अणु
		spin_unlock_bh(&t->ftid_lock);
		वापस -EBUSY;
	पूर्ण

	अगर (family == PF_INET)
		__set_bit(fidx, t->hpftid_bmap);
	अन्यथा
		biपंचांगap_allocate_region(t->hpftid_bmap, fidx, 1);

	spin_unlock_bh(&t->ftid_lock);
	वापस 0;
पूर्ण

अटल व्योम cxgb4_clear_ftid(काष्ठा tid_info *t, पूर्णांक fidx, पूर्णांक family,
			     अचिन्हित पूर्णांक chip_ver)
अणु
	spin_lock_bh(&t->ftid_lock);
	अगर (family == PF_INET) अणु
		__clear_bit(fidx, t->ftid_bmap);
	पूर्ण अन्यथा अणु
		अगर (chip_ver < CHELSIO_T6)
			biपंचांगap_release_region(t->ftid_bmap, fidx, 2);
		अन्यथा
			biपंचांगap_release_region(t->ftid_bmap, fidx, 1);
	पूर्ण
	spin_unlock_bh(&t->ftid_lock);
पूर्ण

अटल व्योम cxgb4_clear_hpftid(काष्ठा tid_info *t, पूर्णांक fidx, पूर्णांक family)
अणु
	spin_lock_bh(&t->ftid_lock);

	अगर (family == PF_INET)
		__clear_bit(fidx, t->hpftid_bmap);
	अन्यथा
		biपंचांगap_release_region(t->hpftid_bmap, fidx, 1);

	spin_unlock_bh(&t->ftid_lock);
पूर्ण

/* Delete the filter at a specअगरied index. */
अटल पूर्णांक del_filter_wr(काष्ठा adapter *adapter, पूर्णांक fidx)
अणु
	काष्ठा fw_filter_wr *fwr;
	काष्ठा filter_entry *f;
	काष्ठा sk_buff *skb;
	अचिन्हित पूर्णांक len;

	अगर (fidx < adapter->tids.nhpftids)
		f = &adapter->tids.hpftid_tab[fidx];
	अन्यथा
		f = &adapter->tids.ftid_tab[fidx - adapter->tids.nhpftids];

	len = माप(*fwr);

	skb = alloc_skb(len, GFP_KERNEL);
	अगर (!skb)
		वापस -ENOMEM;

	fwr = __skb_put(skb, len);
	t4_mk_filtdelwr(f->tid, fwr, adapter->sge.fw_evtq.असल_id);

	/* Mark the filter as "pending" and ship off the Filter Work Request.
	 * When we get the Work Request Reply we'll clear the pending status.
	 */
	f->pending = 1;
	t4_mgmt_tx(adapter, skb);
	वापस 0;
पूर्ण

/* Send a Work Request to ग_लिखो the filter at a specअगरied index.  We स्थिरruct
 * a Firmware Filter Work Request to have the work करोne and put the indicated
 * filter पूर्णांकo "pending" mode which will prevent any further actions against
 * it till we get a reply from the firmware on the completion status of the
 * request.
 */
पूर्णांक set_filter_wr(काष्ठा adapter *adapter, पूर्णांक fidx)
अणु
	काष्ठा fw_filter2_wr *fwr;
	काष्ठा filter_entry *f;
	काष्ठा sk_buff *skb;

	अगर (fidx < adapter->tids.nhpftids)
		f = &adapter->tids.hpftid_tab[fidx];
	अन्यथा
		f = &adapter->tids.ftid_tab[fidx - adapter->tids.nhpftids];

	skb = alloc_skb(माप(*fwr), GFP_KERNEL);
	अगर (!skb)
		वापस -ENOMEM;

	/* If the new filter requires loopback Destination MAC and/or VLAN
	 * rewriting then we need to allocate a Layer 2 Table (L2T) entry क्रम
	 * the filter.
	 */
	अगर (f->fs.newdmac || f->fs.newvlan) अणु
		/* allocate L2T entry क्रम new filter */
		f->l2t = t4_l2t_alloc_चयनing(adapter, f->fs.vlan,
						f->fs.eport, f->fs.dmac);
		अगर (!f->l2t) अणु
			kमुक्त_skb(skb);
			वापस -ENOMEM;
		पूर्ण
	पूर्ण

	/* If the new filter requires loopback Source MAC rewriting then
	 * we need to allocate a SMT entry क्रम the filter.
	 */
	अगर (f->fs.newsmac) अणु
		f->smt = cxgb4_smt_alloc_चयनing(f->dev, f->fs.smac);
		अगर (!f->smt) अणु
			अगर (f->l2t) अणु
				cxgb4_l2t_release(f->l2t);
				f->l2t = शून्य;
			पूर्ण
			kमुक्त_skb(skb);
			वापस -ENOMEM;
		पूर्ण
	पूर्ण

	fwr = __skb_put_zero(skb, माप(*fwr));

	/* It would be nice to put most of the following in t4_hw.c but most
	 * of the work is translating the cxgbtool ch_filter_specअगरication
	 * पूर्णांकo the Work Request and the definition of that काष्ठाure is
	 * currently in cxgbtool.h which isn't appropriate to pull पूर्णांकo the
	 * common code.  We may eventually try to come up with a more neutral
	 * filter specअगरication काष्ठाure but क्रम now it's easiest to simply
	 * put this fairly direct code in line ...
	 */
	अगर (adapter->params.filter2_wr_support)
		fwr->op_pkd = htonl(FW_WR_OP_V(FW_FILTER2_WR));
	अन्यथा
		fwr->op_pkd = htonl(FW_WR_OP_V(FW_FILTER_WR));
	fwr->len16_pkd = htonl(FW_WR_LEN16_V(माप(*fwr) / 16));
	fwr->tid_to_iq =
		htonl(FW_FILTER_WR_TID_V(f->tid) |
		      FW_FILTER_WR_RQTYPE_V(f->fs.type) |
		      FW_FILTER_WR_NOREPLY_V(0) |
		      FW_FILTER_WR_IQ_V(f->fs.iq));
	fwr->del_filter_to_l2tix =
		htonl(FW_FILTER_WR_RPTTID_V(f->fs.rpttid) |
		      FW_FILTER_WR_DROP_V(f->fs.action == FILTER_DROP) |
		      FW_FILTER_WR_सूचीSTEER_V(f->fs.dirsteer) |
		      FW_FILTER_WR_MASKHASH_V(f->fs.maskhash) |
		      FW_FILTER_WR_सूचीSTEERHASH_V(f->fs.dirsteerhash) |
		      FW_FILTER_WR_LPBK_V(f->fs.action == FILTER_SWITCH) |
		      FW_FILTER_WR_DMAC_V(f->fs.newdmac) |
		      FW_FILTER_WR_SMAC_V(f->fs.newsmac) |
		      FW_FILTER_WR_INSVLAN_V(f->fs.newvlan == VLAN_INSERT ||
					     f->fs.newvlan == VLAN_REWRITE) |
		      FW_FILTER_WR_RMVLAN_V(f->fs.newvlan == VLAN_REMOVE ||
					    f->fs.newvlan == VLAN_REWRITE) |
		      FW_FILTER_WR_HITCNTS_V(f->fs.hitcnts) |
		      FW_FILTER_WR_TXCHAN_V(f->fs.eport) |
		      FW_FILTER_WR_PRIO_V(f->fs.prio) |
		      FW_FILTER_WR_L2TIX_V(f->l2t ? f->l2t->idx : 0));
	fwr->ethtype = htons(f->fs.val.ethtype);
	fwr->ethtypem = htons(f->fs.mask.ethtype);
	fwr->frag_to_ovlan_vldm =
		(FW_FILTER_WR_FRAG_V(f->fs.val.frag) |
		 FW_FILTER_WR_FRAGM_V(f->fs.mask.frag) |
		 FW_FILTER_WR_IVLAN_VLD_V(f->fs.val.ivlan_vld) |
		 FW_FILTER_WR_OVLAN_VLD_V(f->fs.val.ovlan_vld) |
		 FW_FILTER_WR_IVLAN_VLDM_V(f->fs.mask.ivlan_vld) |
		 FW_FILTER_WR_OVLAN_VLDM_V(f->fs.mask.ovlan_vld));
	अगर (f->fs.newsmac)
		fwr->smac_sel = f->smt->idx;
	fwr->rx_chan_rx_rpl_iq =
		htons(FW_FILTER_WR_RX_CHAN_V(0) |
		      FW_FILTER_WR_RX_RPL_IQ_V(adapter->sge.fw_evtq.असल_id));
	fwr->maci_to_matchtypem =
		htonl(FW_FILTER_WR_MACI_V(f->fs.val.macidx) |
		      FW_FILTER_WR_MACIM_V(f->fs.mask.macidx) |
		      FW_FILTER_WR_FCOE_V(f->fs.val.fcoe) |
		      FW_FILTER_WR_FCOEM_V(f->fs.mask.fcoe) |
		      FW_FILTER_WR_PORT_V(f->fs.val.iport) |
		      FW_FILTER_WR_PORTM_V(f->fs.mask.iport) |
		      FW_FILTER_WR_MATCHTYPE_V(f->fs.val.matchtype) |
		      FW_FILTER_WR_MATCHTYPEM_V(f->fs.mask.matchtype));
	fwr->ptcl = f->fs.val.proto;
	fwr->ptclm = f->fs.mask.proto;
	fwr->ttyp = f->fs.val.tos;
	fwr->ttypm = f->fs.mask.tos;
	fwr->ivlan = htons(f->fs.val.ivlan);
	fwr->ivlanm = htons(f->fs.mask.ivlan);
	fwr->ovlan = htons(f->fs.val.ovlan);
	fwr->ovlanm = htons(f->fs.mask.ovlan);
	स_नकल(fwr->lip, f->fs.val.lip, माप(fwr->lip));
	स_नकल(fwr->lipm, f->fs.mask.lip, माप(fwr->lipm));
	स_नकल(fwr->fip, f->fs.val.fip, माप(fwr->fip));
	स_नकल(fwr->fipm, f->fs.mask.fip, माप(fwr->fipm));
	fwr->lp = htons(f->fs.val.lport);
	fwr->lpm = htons(f->fs.mask.lport);
	fwr->fp = htons(f->fs.val.fport);
	fwr->fpm = htons(f->fs.mask.fport);

	अगर (adapter->params.filter2_wr_support) अणु
		u8 *nat_lp = (u8 *)&f->fs.nat_lport;
		u8 *nat_fp = (u8 *)&f->fs.nat_fport;

		fwr->naपंचांगode_to_ulp_type =
			FW_FILTER2_WR_ULP_TYPE_V(f->fs.nat_mode ?
						 ULP_MODE_TCPDDP :
						 ULP_MODE_NONE) |
			FW_FILTER2_WR_NATMODE_V(f->fs.nat_mode);
		स_नकल(fwr->newlip, f->fs.nat_lip, माप(fwr->newlip));
		स_नकल(fwr->newfip, f->fs.nat_fip, माप(fwr->newfip));
		fwr->newlport = htons(nat_lp[1] | nat_lp[0] << 8);
		fwr->newfport = htons(nat_fp[1] | nat_fp[0] << 8);
	पूर्ण

	/* Mark the filter as "pending" and ship off the Filter Work Request.
	 * When we get the Work Request Reply we'll clear the pending status.
	 */
	f->pending = 1;
	set_wr_txq(skb, CPL_PRIORITY_CONTROL, f->fs.val.iport & 0x3);
	t4_ofld_send(adapter, skb);
	वापस 0;
पूर्ण

/* Return an error number अगर the indicated filter isn't writable ... */
पूर्णांक writable_filter(काष्ठा filter_entry *f)
अणु
	अगर (f->locked)
		वापस -EPERM;
	अगर (f->pending)
		वापस -EBUSY;

	वापस 0;
पूर्ण

/* Delete the filter at the specअगरied index (अगर valid).  The checks क्रम all
 * the common problems with करोing this like the filter being locked, currently
 * pending in another operation, etc.
 */
पूर्णांक delete_filter(काष्ठा adapter *adapter, अचिन्हित पूर्णांक fidx)
अणु
	काष्ठा filter_entry *f;
	पूर्णांक ret;

	अगर (fidx >= adapter->tids.nftids + adapter->tids.nsftids +
		    adapter->tids.nhpftids)
		वापस -EINVAL;

	अगर (fidx < adapter->tids.nhpftids)
		f = &adapter->tids.hpftid_tab[fidx];
	अन्यथा
		f = &adapter->tids.ftid_tab[fidx - adapter->tids.nhpftids];
	ret = writable_filter(f);
	अगर (ret)
		वापस ret;
	अगर (f->valid)
		वापस del_filter_wr(adapter, fidx);

	वापस 0;
पूर्ण

/* Clear a filter and release any of its resources that we own.  This also
 * clears the filter's "pending" status.
 */
व्योम clear_filter(काष्ठा adapter *adap, काष्ठा filter_entry *f)
अणु
	काष्ठा port_info *pi = netdev_priv(f->dev);

	/* If the new or old filter have loopback rewriting rules then we'll
	 * need to मुक्त any existing L2T, SMT, CLIP entries of filter
	 * rule.
	 */
	अगर (f->l2t)
		cxgb4_l2t_release(f->l2t);

	अगर (f->smt)
		cxgb4_smt_release(f->smt);

	अगर (f->fs.val.encap_vld && f->fs.val.ovlan_vld)
		t4_मुक्त_encap_mac_filt(adap, pi->viid,
				       f->fs.val.ovlan & 0x1ff, 0);

	अगर ((f->fs.hash || is_t6(adap->params.chip)) && f->fs.type)
		cxgb4_clip_release(f->dev, (स्थिर u32 *)&f->fs.val.lip, 1);

	/* The zeroing of the filter rule below clears the filter valid,
	 * pending, locked flags, l2t poपूर्णांकer, etc. so it's all we need क्रम
	 * this operation.
	 */
	स_रखो(f, 0, माप(*f));
पूर्ण

व्योम clear_all_filters(काष्ठा adapter *adapter)
अणु
	काष्ठा net_device *dev = adapter->port[0];
	अचिन्हित पूर्णांक i;

	अगर (adapter->tids.hpftid_tab) अणु
		काष्ठा filter_entry *f = &adapter->tids.hpftid_tab[0];

		क्रम (i = 0; i < adapter->tids.nhpftids; i++, f++)
			अगर (f->valid || f->pending)
				cxgb4_del_filter(dev, i, &f->fs);
	पूर्ण

	अगर (adapter->tids.ftid_tab) अणु
		काष्ठा filter_entry *f = &adapter->tids.ftid_tab[0];
		अचिन्हित पूर्णांक max_ftid = adapter->tids.nftids +
					adapter->tids.nsftids +
					adapter->tids.nhpftids;

		/* Clear all TCAM filters */
		क्रम (i = adapter->tids.nhpftids; i < max_ftid; i++, f++)
			अगर (f->valid || f->pending)
				cxgb4_del_filter(dev, i, &f->fs);
	पूर्ण

	/* Clear all hash filters */
	अगर (is_hashfilter(adapter) && adapter->tids.tid_tab) अणु
		काष्ठा filter_entry *f;
		अचिन्हित पूर्णांक sb;

		क्रम (i = adapter->tids.hash_base;
		     i <= adapter->tids.ntids; i++) अणु
			f = (काष्ठा filter_entry *)
				adapter->tids.tid_tab[i];

			अगर (f && (f->valid || f->pending))
				cxgb4_del_filter(dev, f->tid, &f->fs);
		पूर्ण

		sb = adapter->tids.stid_base;
		क्रम (i = 0; i < sb; i++) अणु
			f = (काष्ठा filter_entry *)adapter->tids.tid_tab[i];

			अगर (f && (f->valid || f->pending))
				cxgb4_del_filter(dev, f->tid, &f->fs);
		पूर्ण
	पूर्ण
पूर्ण

/* Fill up शेष masks क्रम set match fields. */
अटल व्योम fill_शेष_mask(काष्ठा ch_filter_specअगरication *fs)
अणु
	अचिन्हित पूर्णांक lip = 0, lip_mask = 0;
	अचिन्हित पूर्णांक fip = 0, fip_mask = 0;
	अचिन्हित पूर्णांक i;

	अगर (fs->val.iport && !fs->mask.iport)
		fs->mask.iport |= ~0;
	अगर (fs->val.fcoe && !fs->mask.fcoe)
		fs->mask.fcoe |= ~0;
	अगर (fs->val.matchtype && !fs->mask.matchtype)
		fs->mask.matchtype |= ~0;
	अगर (fs->val.macidx && !fs->mask.macidx)
		fs->mask.macidx |= ~0;
	अगर (fs->val.ethtype && !fs->mask.ethtype)
		fs->mask.ethtype |= ~0;
	अगर (fs->val.ivlan && !fs->mask.ivlan)
		fs->mask.ivlan |= ~0;
	अगर (fs->val.ovlan && !fs->mask.ovlan)
		fs->mask.ovlan |= ~0;
	अगर (fs->val.frag && !fs->mask.frag)
		fs->mask.frag |= ~0;
	अगर (fs->val.tos && !fs->mask.tos)
		fs->mask.tos |= ~0;
	अगर (fs->val.proto && !fs->mask.proto)
		fs->mask.proto |= ~0;
	अगर (fs->val.pfvf_vld && !fs->mask.pfvf_vld)
		fs->mask.pfvf_vld |= ~0;
	अगर (fs->val.pf && !fs->mask.pf)
		fs->mask.pf |= ~0;
	अगर (fs->val.vf && !fs->mask.vf)
		fs->mask.vf |= ~0;

	क्रम (i = 0; i < ARRAY_SIZE(fs->val.lip); i++) अणु
		lip |= fs->val.lip[i];
		lip_mask |= fs->mask.lip[i];
		fip |= fs->val.fip[i];
		fip_mask |= fs->mask.fip[i];
	पूर्ण

	अगर (lip && !lip_mask)
		स_रखो(fs->mask.lip, ~0, माप(fs->mask.lip));

	अगर (fip && !fip_mask)
		स_रखो(fs->mask.fip, ~0, माप(fs->mask.lip));

	अगर (fs->val.lport && !fs->mask.lport)
		fs->mask.lport = ~0;
	अगर (fs->val.fport && !fs->mask.fport)
		fs->mask.fport = ~0;
पूर्ण

अटल bool is_addr_all_mask(u8 *ipmask, पूर्णांक family)
अणु
	अगर (family == AF_INET) अणु
		काष्ठा in_addr *addr;

		addr = (काष्ठा in_addr *)ipmask;
		अगर (addr->s_addr == htonl(0xffffffff))
			वापस true;
	पूर्ण अन्यथा अगर (family == AF_INET6) अणु
		काष्ठा in6_addr *addr6;

		addr6 = (काष्ठा in6_addr *)ipmask;
		अगर (addr6->s6_addr32[0] == htonl(0xffffffff) &&
		    addr6->s6_addr32[1] == htonl(0xffffffff) &&
		    addr6->s6_addr32[2] == htonl(0xffffffff) &&
		    addr6->s6_addr32[3] == htonl(0xffffffff))
			वापस true;
	पूर्ण
	वापस false;
पूर्ण

अटल bool is_inaddr_any(u8 *ip, पूर्णांक family)
अणु
	पूर्णांक addr_type;

	अगर (family == AF_INET) अणु
		काष्ठा in_addr *addr;

		addr = (काष्ठा in_addr *)ip;
		अगर (addr->s_addr == htonl(INADDR_ANY))
			वापस true;
	पूर्ण अन्यथा अगर (family == AF_INET6) अणु
		काष्ठा in6_addr *addr6;

		addr6 = (काष्ठा in6_addr *)ip;
		addr_type = ipv6_addr_type((स्थिर काष्ठा in6_addr *)
					   &addr6);
		अगर (addr_type == IPV6_ADDR_ANY)
			वापस true;
	पूर्ण
	वापस false;
पूर्ण

bool is_filter_exact_match(काष्ठा adapter *adap,
			   काष्ठा ch_filter_specअगरication *fs)
अणु
	काष्ठा tp_params *tp = &adap->params.tp;
	u64 hash_filter_mask = tp->hash_filter_mask;
	u64 ntuple_mask = 0;

	अगर (!is_hashfilter(adap))
		वापस false;

	अगर ((atomic_पढ़ो(&adap->tids.hash_tids_in_use) +
	     atomic_पढ़ो(&adap->tids.tids_in_use)) >=
	    (adap->tids.nhash + (adap->tids.stid_base - adap->tids.tid_base)))
		वापस false;

	 /* Keep tunnel VNI match disabled क्रम hash-filters क्रम now */
	अगर (fs->mask.encap_vld)
		वापस false;

	अगर (fs->type) अणु
		अगर (is_inaddr_any(fs->val.fip, AF_INET6) ||
		    !is_addr_all_mask(fs->mask.fip, AF_INET6))
			वापस false;

		अगर (is_inaddr_any(fs->val.lip, AF_INET6) ||
		    !is_addr_all_mask(fs->mask.lip, AF_INET6))
			वापस false;
	पूर्ण अन्यथा अणु
		अगर (is_inaddr_any(fs->val.fip, AF_INET) ||
		    !is_addr_all_mask(fs->mask.fip, AF_INET))
			वापस false;

		अगर (is_inaddr_any(fs->val.lip, AF_INET) ||
		    !is_addr_all_mask(fs->mask.lip, AF_INET))
			वापस false;
	पूर्ण

	अगर (!fs->val.lport || fs->mask.lport != 0xffff)
		वापस false;

	अगर (!fs->val.fport || fs->mask.fport != 0xffff)
		वापस false;

	/* calculate tuple mask and compare with mask configured in hw */
	अगर (tp->fcoe_shअगरt >= 0)
		ntuple_mask |= (u64)fs->mask.fcoe << tp->fcoe_shअगरt;

	अगर (tp->port_shअगरt >= 0)
		ntuple_mask |= (u64)fs->mask.iport << tp->port_shअगरt;

	अगर (tp->vnic_shअगरt >= 0) अणु
		अगर ((adap->params.tp.ingress_config & VNIC_F))
			ntuple_mask |= (u64)fs->mask.pfvf_vld << tp->vnic_shअगरt;
		अन्यथा
			ntuple_mask |= (u64)fs->mask.ovlan_vld <<
				tp->vnic_shअगरt;
	पूर्ण

	अगर (tp->vlan_shअगरt >= 0)
		ntuple_mask |= (u64)fs->mask.ivlan << tp->vlan_shअगरt;

	अगर (tp->tos_shअगरt >= 0)
		ntuple_mask |= (u64)fs->mask.tos << tp->tos_shअगरt;

	अगर (tp->protocol_shअगरt >= 0)
		ntuple_mask |= (u64)fs->mask.proto << tp->protocol_shअगरt;

	अगर (tp->ethertype_shअगरt >= 0)
		ntuple_mask |= (u64)fs->mask.ethtype << tp->ethertype_shअगरt;

	अगर (tp->macmatch_shअगरt >= 0)
		ntuple_mask |= (u64)fs->mask.macidx << tp->macmatch_shअगरt;

	अगर (tp->matchtype_shअगरt >= 0)
		ntuple_mask |= (u64)fs->mask.matchtype << tp->matchtype_shअगरt;

	अगर (tp->frag_shअगरt >= 0)
		ntuple_mask |= (u64)fs->mask.frag << tp->frag_shअगरt;

	अगर (ntuple_mask != hash_filter_mask)
		वापस false;

	वापस true;
पूर्ण

अटल u64 hash_filter_ntuple(काष्ठा ch_filter_specअगरication *fs,
			      काष्ठा net_device *dev)
अणु
	काष्ठा adapter *adap = netdev2adap(dev);
	काष्ठा tp_params *tp = &adap->params.tp;
	u64 ntuple = 0;

	/* Initialize each of the fields which we care about which are present
	 * in the Compressed Filter Tuple.
	 */
	अगर (tp->vlan_shअगरt >= 0 && fs->mask.ivlan)
		ntuple |= (FT_VLAN_VLD_F | fs->val.ivlan) << tp->vlan_shअगरt;

	अगर (tp->port_shअगरt >= 0 && fs->mask.iport)
		ntuple |= (u64)fs->val.iport << tp->port_shअगरt;

	अगर (tp->protocol_shअगरt >= 0) अणु
		अगर (!fs->val.proto)
			ntuple |= (u64)IPPROTO_TCP << tp->protocol_shअगरt;
		अन्यथा
			ntuple |= (u64)fs->val.proto << tp->protocol_shअगरt;
	पूर्ण

	अगर (tp->tos_shअगरt >= 0 && fs->mask.tos)
		ntuple |= (u64)(fs->val.tos) << tp->tos_shअगरt;

	अगर (tp->vnic_shअगरt >= 0) अणु
		अगर ((adap->params.tp.ingress_config & USE_ENC_IDX_F) &&
		    fs->mask.encap_vld)
			ntuple |= (u64)((fs->val.encap_vld << 16) |
					(fs->val.ovlan)) << tp->vnic_shअगरt;
		अन्यथा अगर ((adap->params.tp.ingress_config & VNIC_F) &&
			 fs->mask.pfvf_vld)
			ntuple |= (u64)((fs->val.pfvf_vld << 16) |
					(fs->val.pf << 13) |
					(fs->val.vf)) << tp->vnic_shअगरt;
		अन्यथा
			ntuple |= (u64)((fs->val.ovlan_vld << 16) |
					(fs->val.ovlan)) << tp->vnic_shअगरt;
	पूर्ण

	अगर (tp->macmatch_shअगरt >= 0 && fs->mask.macidx)
		ntuple |= (u64)(fs->val.macidx) << tp->macmatch_shअगरt;

	अगर (tp->ethertype_shअगरt >= 0 && fs->mask.ethtype)
		ntuple |= (u64)(fs->val.ethtype) << tp->ethertype_shअगरt;

	अगर (tp->matchtype_shअगरt >= 0 && fs->mask.matchtype)
		ntuple |= (u64)(fs->val.matchtype) << tp->matchtype_shअगरt;

	अगर (tp->frag_shअगरt >= 0 && fs->mask.frag)
		ntuple |= (u64)(fs->val.frag) << tp->frag_shअगरt;

	अगर (tp->fcoe_shअगरt >= 0 && fs->mask.fcoe)
		ntuple |= (u64)(fs->val.fcoe) << tp->fcoe_shअगरt;
	वापस ntuple;
पूर्ण

अटल व्योम mk_act_खोलो_req6(काष्ठा filter_entry *f, काष्ठा sk_buff *skb,
			     अचिन्हित पूर्णांक qid_filterid, काष्ठा adapter *adap)
अणु
	काष्ठा cpl_t6_act_खोलो_req6 *t6req = शून्य;
	काष्ठा cpl_act_खोलो_req6 *req = शून्य;

	t6req = (काष्ठा cpl_t6_act_खोलो_req6 *)__skb_put(skb, माप(*t6req));
	INIT_TP_WR(t6req, 0);
	req = (काष्ठा cpl_act_खोलो_req6 *)t6req;
	OPCODE_TID(req) = htonl(MK_OPCODE_TID(CPL_ACT_OPEN_REQ6, qid_filterid));
	req->local_port = cpu_to_be16(f->fs.val.lport);
	req->peer_port = cpu_to_be16(f->fs.val.fport);
	req->local_ip_hi = *(__be64 *)(&f->fs.val.lip);
	req->local_ip_lo = *(((__be64 *)&f->fs.val.lip) + 1);
	req->peer_ip_hi = *(__be64 *)(&f->fs.val.fip);
	req->peer_ip_lo = *(((__be64 *)&f->fs.val.fip) + 1);
	req->opt0 = cpu_to_be64(NAGLE_V(f->fs.newvlan == VLAN_REMOVE ||
					f->fs.newvlan == VLAN_REWRITE) |
				DELACK_V(f->fs.hitcnts) |
				L2T_IDX_V(f->l2t ? f->l2t->idx : 0) |
				SMAC_SEL_V((cxgb4_port_viid(f->dev) &
					    0x7F) << 1) |
				TX_CHAN_V(f->fs.eport) |
				NO_CONG_V(f->fs.rpttid) |
				ULP_MODE_V(f->fs.nat_mode ?
					   ULP_MODE_TCPDDP : ULP_MODE_NONE) |
				TCAM_BYPASS_F | NON_OFFLOAD_F);
	t6req->params = cpu_to_be64(FILTER_TUPLE_V(hash_filter_ntuple(&f->fs,
								      f->dev)));
	t6req->opt2 = htonl(RSS_QUEUE_VALID_F |
			    RSS_QUEUE_V(f->fs.iq) |
			    TX_QUEUE_V(f->fs.nat_mode) |
			    T5_OPT_2_VALID_F |
			    RX_CHANNEL_V(cxgb4_port_e2cchan(f->dev)) |
			    PACE_V((f->fs.maskhash) |
				   ((f->fs.dirsteerhash) << 1)));
पूर्ण

अटल व्योम mk_act_खोलो_req(काष्ठा filter_entry *f, काष्ठा sk_buff *skb,
			    अचिन्हित पूर्णांक qid_filterid, काष्ठा adapter *adap)
अणु
	काष्ठा cpl_t6_act_खोलो_req *t6req = शून्य;
	काष्ठा cpl_act_खोलो_req *req = शून्य;

	t6req = (काष्ठा cpl_t6_act_खोलो_req *)__skb_put(skb, माप(*t6req));
	INIT_TP_WR(t6req, 0);
	req = (काष्ठा cpl_act_खोलो_req *)t6req;
	OPCODE_TID(req) = htonl(MK_OPCODE_TID(CPL_ACT_OPEN_REQ, qid_filterid));
	req->local_port = cpu_to_be16(f->fs.val.lport);
	req->peer_port = cpu_to_be16(f->fs.val.fport);
	स_नकल(&req->local_ip, f->fs.val.lip, 4);
	स_नकल(&req->peer_ip, f->fs.val.fip, 4);
	req->opt0 = cpu_to_be64(NAGLE_V(f->fs.newvlan == VLAN_REMOVE ||
					f->fs.newvlan == VLAN_REWRITE) |
				DELACK_V(f->fs.hitcnts) |
				L2T_IDX_V(f->l2t ? f->l2t->idx : 0) |
				SMAC_SEL_V((cxgb4_port_viid(f->dev) &
					    0x7F) << 1) |
				TX_CHAN_V(f->fs.eport) |
				NO_CONG_V(f->fs.rpttid) |
				ULP_MODE_V(f->fs.nat_mode ?
					   ULP_MODE_TCPDDP : ULP_MODE_NONE) |
				TCAM_BYPASS_F | NON_OFFLOAD_F);

	t6req->params = cpu_to_be64(FILTER_TUPLE_V(hash_filter_ntuple(&f->fs,
								      f->dev)));
	t6req->opt2 = htonl(RSS_QUEUE_VALID_F |
			    RSS_QUEUE_V(f->fs.iq) |
			    TX_QUEUE_V(f->fs.nat_mode) |
			    T5_OPT_2_VALID_F |
			    RX_CHANNEL_V(cxgb4_port_e2cchan(f->dev)) |
			    PACE_V((f->fs.maskhash) |
				   ((f->fs.dirsteerhash) << 1)));
पूर्ण

अटल पूर्णांक cxgb4_set_hash_filter(काष्ठा net_device *dev,
				 काष्ठा ch_filter_specअगरication *fs,
				 काष्ठा filter_ctx *ctx)
अणु
	काष्ठा adapter *adapter = netdev2adap(dev);
	काष्ठा port_info *pi = netdev_priv(dev);
	काष्ठा tid_info *t = &adapter->tids;
	काष्ठा filter_entry *f;
	काष्ठा sk_buff *skb;
	पूर्णांक iq, atid, size;
	पूर्णांक ret = 0;
	u32 iconf;

	fill_शेष_mask(fs);
	ret = validate_filter(dev, fs);
	अगर (ret)
		वापस ret;

	iq = get_filter_steerq(dev, fs);
	अगर (iq < 0)
		वापस iq;

	f = kzalloc(माप(*f), GFP_KERNEL);
	अगर (!f)
		वापस -ENOMEM;

	f->fs = *fs;
	f->ctx = ctx;
	f->dev = dev;
	f->fs.iq = iq;

	/* If the new filter requires loopback Destination MAC and/or VLAN
	 * rewriting then we need to allocate a Layer 2 Table (L2T) entry क्रम
	 * the filter.
	 */
	अगर (f->fs.newdmac || f->fs.newvlan) अणु
		/* allocate L2T entry क्रम new filter */
		f->l2t = t4_l2t_alloc_चयनing(adapter, f->fs.vlan,
						f->fs.eport, f->fs.dmac);
		अगर (!f->l2t) अणु
			ret = -ENOMEM;
			जाओ out_err;
		पूर्ण
	पूर्ण

	/* If the new filter requires loopback Source MAC rewriting then
	 * we need to allocate a SMT entry क्रम the filter.
	 */
	अगर (f->fs.newsmac) अणु
		f->smt = cxgb4_smt_alloc_चयनing(f->dev, f->fs.smac);
		अगर (!f->smt) अणु
			अगर (f->l2t) अणु
				cxgb4_l2t_release(f->l2t);
				f->l2t = शून्य;
			पूर्ण
			ret = -ENOMEM;
			जाओ मुक्त_l2t;
		पूर्ण
	पूर्ण

	atid = cxgb4_alloc_atid(t, f);
	अगर (atid < 0) अणु
		ret = atid;
		जाओ मुक्त_smt;
	पूर्ण

	iconf = adapter->params.tp.ingress_config;
	अगर (iconf & VNIC_F) अणु
		f->fs.val.ovlan = (fs->val.pf << 13) | fs->val.vf;
		f->fs.mask.ovlan = (fs->mask.pf << 13) | fs->mask.vf;
		f->fs.val.ovlan_vld = fs->val.pfvf_vld;
		f->fs.mask.ovlan_vld = fs->mask.pfvf_vld;
	पूर्ण अन्यथा अगर (iconf & USE_ENC_IDX_F) अणु
		अगर (f->fs.val.encap_vld) अणु
			काष्ठा port_info *pi = netdev_priv(f->dev);
			u8 match_all_mac[] = अणु 0, 0, 0, 0, 0, 0 पूर्ण;

			/* allocate MPS TCAM entry */
			ret = t4_alloc_encap_mac_filt(adapter, pi->viid,
						      match_all_mac,
						      match_all_mac,
						      f->fs.val.vni,
						      f->fs.mask.vni,
						      0, 1, 1);
			अगर (ret < 0)
				जाओ मुक्त_atid;

			f->fs.val.ovlan = ret;
			f->fs.mask.ovlan = 0xffff;
			f->fs.val.ovlan_vld = 1;
			f->fs.mask.ovlan_vld = 1;
		पूर्ण
	पूर्ण

	size = माप(काष्ठा cpl_t6_act_खोलो_req);
	अगर (f->fs.type) अणु
		ret = cxgb4_clip_get(f->dev, (स्थिर u32 *)&f->fs.val.lip, 1);
		अगर (ret)
			जाओ मुक्त_mps;

		skb = alloc_skb(size, GFP_KERNEL);
		अगर (!skb) अणु
			ret = -ENOMEM;
			जाओ मुक्त_clip;
		पूर्ण

		mk_act_खोलो_req6(f, skb,
				 ((adapter->sge.fw_evtq.असल_id << 14) | atid),
				 adapter);
	पूर्ण अन्यथा अणु
		skb = alloc_skb(size, GFP_KERNEL);
		अगर (!skb) अणु
			ret = -ENOMEM;
			जाओ मुक्त_mps;
		पूर्ण

		mk_act_खोलो_req(f, skb,
				((adapter->sge.fw_evtq.असल_id << 14) | atid),
				adapter);
	पूर्ण

	f->pending = 1;
	set_wr_txq(skb, CPL_PRIORITY_SETUP, f->fs.val.iport & 0x3);
	t4_ofld_send(adapter, skb);
	वापस 0;

मुक्त_clip:
	cxgb4_clip_release(f->dev, (स्थिर u32 *)&f->fs.val.lip, 1);

मुक्त_mps:
	अगर (f->fs.val.encap_vld && f->fs.val.ovlan_vld)
		t4_मुक्त_encap_mac_filt(adapter, pi->viid, f->fs.val.ovlan, 1);

मुक्त_atid:
	cxgb4_मुक्त_atid(t, atid);

मुक्त_smt:
	अगर (f->smt) अणु
		cxgb4_smt_release(f->smt);
		f->smt = शून्य;
	पूर्ण

मुक्त_l2t:
	अगर (f->l2t) अणु
		cxgb4_l2t_release(f->l2t);
		f->l2t = शून्य;
	पूर्ण

out_err:
	kमुक्त(f);
	वापस ret;
पूर्ण

/* Check a Chelsio Filter Request क्रम validity, convert it पूर्णांकo our पूर्णांकernal
 * क्रमmat and send it to the hardware.  Return 0 on success, an error number
 * otherwise.  We attach any provided filter operation context to the पूर्णांकernal
 * filter specअगरication in order to facilitate संकेतing completion of the
 * operation.
 */
पूर्णांक __cxgb4_set_filter(काष्ठा net_device *dev, पूर्णांक ftid,
		       काष्ठा ch_filter_specअगरication *fs,
		       काष्ठा filter_ctx *ctx)
अणु
	काष्ठा adapter *adapter = netdev2adap(dev);
	अचिन्हित पूर्णांक max_fidx, fidx, chip_ver;
	पूर्णांक iq, ret, filter_id = ftid;
	काष्ठा filter_entry *f, *tab;
	u32 iconf;

	chip_ver = CHELSIO_CHIP_VERSION(adapter->params.chip);
	अगर (fs->hash) अणु
		अगर (is_hashfilter(adapter))
			वापस cxgb4_set_hash_filter(dev, fs, ctx);
		netdev_err(dev, "%s: Exact-match filters only supported with Hash Filter configuration\n",
			   __func__);
		वापस -EINVAL;
	पूर्ण

	max_fidx = adapter->tids.nftids + adapter->tids.nhpftids;
	अगर (filter_id != (max_fidx + adapter->tids.nsftids - 1) &&
	    filter_id >= max_fidx)
		वापस -E2BIG;

	fill_शेष_mask(fs);

	ret = validate_filter(dev, fs);
	अगर (ret)
		वापस ret;

	iq = get_filter_steerq(dev, fs);
	अगर (iq < 0)
		वापस iq;

	अगर (fs->prio) अणु
		tab = &adapter->tids.hpftid_tab[0];
	पूर्ण अन्यथा अणु
		tab = &adapter->tids.ftid_tab[0];
		filter_id = ftid - adapter->tids.nhpftids;
	पूर्ण

	/* IPv6 filters occupy four slots and must be aligned on
	 * four-slot boundaries.  IPv4 filters only occupy a single
	 * slot and have no alignment requirements but writing a new
	 * IPv4 filter पूर्णांकo the middle of an existing IPv6 filter
	 * requires clearing the old IPv6 filter and hence we prevent
	 * insertion.
	 */
	अगर (fs->type == 0) अणु /* IPv4 */
		/* For T6, If our IPv4 filter isn't being written to a
		 * multiple of two filter index and there's an IPv6
		 * filter at the multiple of 2 base slot, then we need
		 * to delete that IPv6 filter ...
		 * For adapters below T6, IPv6 filter occupies 4 entries.
		 * Hence we need to delete the filter in multiple of 4 slot.
		 */
		अगर (chip_ver < CHELSIO_T6)
			fidx = filter_id & ~0x3;
		अन्यथा
			fidx = filter_id & ~0x1;

		अगर (fidx != filter_id && tab[fidx].fs.type) अणु
			f = &tab[fidx];
			अगर (f->valid) अणु
				dev_err(adapter->pdev_dev,
					"Invalid location. IPv6 requires 4 slots and is occupying slots %u to %u\n",
					fidx, fidx + 3);
				वापस -EINVAL;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु /* IPv6 */
		अगर (chip_ver < CHELSIO_T6) अणु
			/* Ensure that the IPv6 filter is aligned on a
			 * multiple of 4 boundary.
			 */
			अगर (filter_id & 0x3) अणु
				dev_err(adapter->pdev_dev,
					"Invalid location. IPv6 must be aligned on a 4-slot boundary\n");
				वापस -EINVAL;
			पूर्ण

			/* Check all except the base overlapping IPv4 filter
			 * slots.
			 */
			क्रम (fidx = filter_id + 1; fidx < filter_id + 4;
			     fidx++) अणु
				f = &tab[fidx];
				अगर (f->valid) अणु
					dev_err(adapter->pdev_dev,
						"Invalid location.  IPv6 requires 4 slots and an IPv4 filter exists at %u\n",
						fidx);
					वापस -EBUSY;
				पूर्ण
			पूर्ण
		पूर्ण अन्यथा अणु
			/* For T6, CLIP being enabled, IPv6 filter would occupy
			 * 2 entries.
			 */
			अगर (filter_id & 0x1)
				वापस -EINVAL;
			/* Check overlapping IPv4 filter slot */
			fidx = filter_id + 1;
			f = &tab[fidx];
			अगर (f->valid) अणु
				pr_err("%s: IPv6 filter requires 2 indices. IPv4 filter already present at %d. Please remove IPv4 filter first.\n",
				       __func__, fidx);
				वापस -EBUSY;
			पूर्ण
		पूर्ण
	पूर्ण

	/* Check to make sure that provided filter index is not
	 * alपढ़ोy in use by someone अन्यथा
	 */
	f = &tab[filter_id];
	अगर (f->valid)
		वापस -EBUSY;

	अगर (fs->prio) अणु
		fidx = filter_id + adapter->tids.hpftid_base;
		ret = cxgb4_set_hpftid(&adapter->tids, filter_id,
				       fs->type ? PF_INET6 : PF_INET);
	पूर्ण अन्यथा अणु
		fidx = filter_id + adapter->tids.ftid_base;
		ret = cxgb4_set_ftid(&adapter->tids, filter_id,
				     fs->type ? PF_INET6 : PF_INET,
				     chip_ver);
	पूर्ण

	अगर (ret)
		वापस ret;

	/* Check t  make sure the filter requested is writable ... */
	ret = writable_filter(f);
	अगर (ret)
		जाओ मुक्त_tid;

	अगर (is_t6(adapter->params.chip) && fs->type &&
	    ipv6_addr_type((स्थिर काष्ठा in6_addr *)fs->val.lip) !=
	    IPV6_ADDR_ANY) अणु
		ret = cxgb4_clip_get(dev, (स्थिर u32 *)&fs->val.lip, 1);
		अगर (ret)
			जाओ मुक्त_tid;
	पूर्ण

	/* Convert the filter specअगरication पूर्णांकo our पूर्णांकernal क्रमmat.
	 * We copy the PF/VF specअगरication पूर्णांकo the Outer VLAN field
	 * here so the rest of the code -- including the पूर्णांकerface to
	 * the firmware -- करोesn't have to स्थिरantly करो these checks.
	 */
	f->fs = *fs;
	f->fs.iq = iq;
	f->dev = dev;

	iconf = adapter->params.tp.ingress_config;
	अगर (iconf & VNIC_F) अणु
		f->fs.val.ovlan = (fs->val.pf << 13) | fs->val.vf;
		f->fs.mask.ovlan = (fs->mask.pf << 13) | fs->mask.vf;
		f->fs.val.ovlan_vld = fs->val.pfvf_vld;
		f->fs.mask.ovlan_vld = fs->mask.pfvf_vld;
	पूर्ण अन्यथा अगर (iconf & USE_ENC_IDX_F) अणु
		अगर (f->fs.val.encap_vld) अणु
			काष्ठा port_info *pi = netdev_priv(f->dev);
			u8 match_all_mac[] = अणु 0, 0, 0, 0, 0, 0 पूर्ण;

			/* allocate MPS TCAM entry */
			ret = t4_alloc_encap_mac_filt(adapter, pi->viid,
						      match_all_mac,
						      match_all_mac,
						      f->fs.val.vni,
						      f->fs.mask.vni,
						      0, 1, 1);
			अगर (ret < 0)
				जाओ मुक्त_tid;

			f->fs.val.ovlan = ret;
			f->fs.mask.ovlan = 0x1ff;
			f->fs.val.ovlan_vld = 1;
			f->fs.mask.ovlan_vld = 1;
		पूर्ण
	पूर्ण

	/* Attempt to set the filter.  If we करोn't succeed, we clear
	 * it and वापस the failure.
	 */
	f->ctx = ctx;
	f->tid = fidx; /* Save the actual tid */
	ret = set_filter_wr(adapter, ftid);
	अगर (ret)
		जाओ मुक्त_tid;

	वापस ret;

मुक्त_tid:
	अगर (f->fs.prio)
		cxgb4_clear_hpftid(&adapter->tids, filter_id,
				   fs->type ? PF_INET6 : PF_INET);
	अन्यथा
		cxgb4_clear_ftid(&adapter->tids, filter_id,
				 fs->type ? PF_INET6 : PF_INET,
				 chip_ver);

	clear_filter(adapter, f);
	वापस ret;
पूर्ण

अटल पूर्णांक cxgb4_del_hash_filter(काष्ठा net_device *dev, पूर्णांक filter_id,
				 काष्ठा filter_ctx *ctx)
अणु
	काष्ठा adapter *adapter = netdev2adap(dev);
	काष्ठा tid_info *t = &adapter->tids;
	काष्ठा cpl_पात_req *पात_req;
	काष्ठा cpl_पात_rpl *पात_rpl;
	काष्ठा cpl_set_tcb_field *req;
	काष्ठा ulptx_idata *aligner;
	काष्ठा work_request_hdr *wr;
	काष्ठा filter_entry *f;
	काष्ठा sk_buff *skb;
	अचिन्हित पूर्णांक wrlen;
	पूर्णांक ret;

	netdev_dbg(dev, "%s: filter_id = %d ; nftids = %d\n",
		   __func__, filter_id, adapter->tids.nftids);

	अगर (tid_out_of_range(t, filter_id))
		वापस -E2BIG;

	f = lookup_tid(t, filter_id);
	अगर (!f) अणु
		netdev_err(dev, "%s: no filter entry for filter_id = %d",
			   __func__, filter_id);
		वापस -EINVAL;
	पूर्ण

	ret = writable_filter(f);
	अगर (ret)
		वापस ret;

	अगर (!f->valid)
		वापस -EINVAL;

	f->ctx = ctx;
	f->pending = 1;
	wrlen = roundup(माप(*wr) + (माप(*req) + माप(*aligner))
			+ माप(*पात_req) + माप(*पात_rpl), 16);
	skb = alloc_skb(wrlen, GFP_KERNEL);
	अगर (!skb) अणु
		netdev_err(dev, "%s: could not allocate skb ..\n", __func__);
		वापस -ENOMEM;
	पूर्ण
	set_wr_txq(skb, CPL_PRIORITY_CONTROL, f->fs.val.iport & 0x3);
	req = (काष्ठा cpl_set_tcb_field *)__skb_put(skb, wrlen);
	INIT_ULPTX_WR(req, wrlen, 0, 0);
	wr = (काष्ठा work_request_hdr *)req;
	wr++;
	req = (काष्ठा cpl_set_tcb_field *)wr;
	mk_set_tcb_ulp(f, req, TCB_RSS_INFO_W, TCB_RSS_INFO_V(TCB_RSS_INFO_M),
		       TCB_RSS_INFO_V(adapter->sge.fw_evtq.असल_id), 0, 1);
	aligner = (काष्ठा ulptx_idata *)(req + 1);
	पात_req = (काष्ठा cpl_पात_req *)(aligner + 1);
	mk_पात_req_ulp(पात_req, f->tid);
	पात_rpl = (काष्ठा cpl_पात_rpl *)(पात_req + 1);
	mk_पात_rpl_ulp(पात_rpl, f->tid);
	t4_ofld_send(adapter, skb);
	वापस 0;
पूर्ण

/* Check a delete filter request क्रम validity and send it to the hardware.
 * Return 0 on success, an error number otherwise.  We attach any provided
 * filter operation context to the पूर्णांकernal filter specअगरication in order to
 * facilitate संकेतing completion of the operation.
 */
पूर्णांक __cxgb4_del_filter(काष्ठा net_device *dev, पूर्णांक filter_id,
		       काष्ठा ch_filter_specअगरication *fs,
		       काष्ठा filter_ctx *ctx)
अणु
	काष्ठा adapter *adapter = netdev2adap(dev);
	अचिन्हित पूर्णांक max_fidx, chip_ver;
	काष्ठा filter_entry *f;
	पूर्णांक ret;

	chip_ver = CHELSIO_CHIP_VERSION(adapter->params.chip);
	अगर (fs && fs->hash) अणु
		अगर (is_hashfilter(adapter))
			वापस cxgb4_del_hash_filter(dev, filter_id, ctx);
		netdev_err(dev, "%s: Exact-match filters only supported with Hash Filter configuration\n",
			   __func__);
		वापस -EINVAL;
	पूर्ण

	max_fidx = adapter->tids.nftids + adapter->tids.nhpftids;
	अगर (filter_id != (max_fidx + adapter->tids.nsftids - 1) &&
	    filter_id >= max_fidx)
		वापस -E2BIG;

	अगर (filter_id < adapter->tids.nhpftids)
		f = &adapter->tids.hpftid_tab[filter_id];
	अन्यथा
		f = &adapter->tids.ftid_tab[filter_id - adapter->tids.nhpftids];

	ret = writable_filter(f);
	अगर (ret)
		वापस ret;

	अगर (f->valid) अणु
		f->ctx = ctx;
		अगर (f->fs.prio)
			cxgb4_clear_hpftid(&adapter->tids,
					   f->tid - adapter->tids.hpftid_base,
					   f->fs.type ? PF_INET6 : PF_INET);
		अन्यथा
			cxgb4_clear_ftid(&adapter->tids,
					 f->tid - adapter->tids.ftid_base,
					 f->fs.type ? PF_INET6 : PF_INET,
					 chip_ver);
		वापस del_filter_wr(adapter, filter_id);
	पूर्ण

	/* If the caller has passed in a Completion Context then we need to
	 * mark it as a successful completion so they करोn't stall रुकोing
	 * क्रम it.
	 */
	अगर (ctx) अणु
		ctx->result = 0;
		complete(&ctx->completion);
	पूर्ण
	वापस ret;
पूर्ण

पूर्णांक cxgb4_set_filter(काष्ठा net_device *dev, पूर्णांक filter_id,
		     काष्ठा ch_filter_specअगरication *fs)
अणु
	काष्ठा filter_ctx ctx;
	पूर्णांक ret;

	init_completion(&ctx.completion);

	ret = __cxgb4_set_filter(dev, filter_id, fs, &ctx);
	अगर (ret)
		जाओ out;

	/* Wait क्रम reply */
	ret = रुको_क्रम_completion_समयout(&ctx.completion, 10 * HZ);
	अगर (!ret)
		वापस -ETIMEDOUT;

	ret = ctx.result;
out:
	वापस ret;
पूर्ण

पूर्णांक cxgb4_del_filter(काष्ठा net_device *dev, पूर्णांक filter_id,
		     काष्ठा ch_filter_specअगरication *fs)
अणु
	काष्ठा filter_ctx ctx;
	पूर्णांक ret;

	अगर (netdev2adap(dev)->flags & CXGB4_SHUTTING_DOWN)
		वापस 0;

	init_completion(&ctx.completion);

	ret = __cxgb4_del_filter(dev, filter_id, fs, &ctx);
	अगर (ret)
		जाओ out;

	/* Wait क्रम reply */
	ret = रुको_क्रम_completion_समयout(&ctx.completion, 10 * HZ);
	अगर (!ret)
		वापस -ETIMEDOUT;

	ret = ctx.result;
out:
	वापस ret;
पूर्ण

अटल पूर्णांक configure_filter_tcb(काष्ठा adapter *adap, अचिन्हित पूर्णांक tid,
				काष्ठा filter_entry *f)
अणु
	अगर (f->fs.hitcnts) अणु
		set_tcb_field(adap, f, tid, TCB_TIMESTAMP_W,
			      TCB_TIMESTAMP_V(TCB_TIMESTAMP_M),
			      TCB_TIMESTAMP_V(0ULL),
			      1);
		set_tcb_field(adap, f, tid, TCB_RTT_TS_RECENT_AGE_W,
			      TCB_RTT_TS_RECENT_AGE_V(TCB_RTT_TS_RECENT_AGE_M),
			      TCB_RTT_TS_RECENT_AGE_V(0ULL),
			      1);
	पूर्ण

	अगर (f->fs.newdmac)
		set_tcb_tflag(adap, f, tid, TF_CCTRL_ECE_S, 1,
			      1);

	अगर (f->fs.newvlan == VLAN_INSERT ||
	    f->fs.newvlan == VLAN_REWRITE)
		set_tcb_tflag(adap, f, tid, TF_CCTRL_RFR_S, 1,
			      1);
	अगर (f->fs.newsmac)
		configure_filter_smac(adap, f);

	अगर (f->fs.nat_mode) अणु
		चयन (f->fs.nat_mode) अणु
		हाल NAT_MODE_DIP:
			set_nat_params(adap, f, tid, true, false, false, false);
			अवरोध;

		हाल NAT_MODE_DIP_DP:
			set_nat_params(adap, f, tid, true, false, true, false);
			अवरोध;

		हाल NAT_MODE_DIP_DP_SIP:
			set_nat_params(adap, f, tid, true, true, true, false);
			अवरोध;
		हाल NAT_MODE_DIP_DP_SP:
			set_nat_params(adap, f, tid, true, false, true, true);
			अवरोध;

		हाल NAT_MODE_SIP_SP:
			set_nat_params(adap, f, tid, false, true, false, true);
			अवरोध;

		हाल NAT_MODE_DIP_SIP_SP:
			set_nat_params(adap, f, tid, true, true, false, true);
			अवरोध;

		हाल NAT_MODE_ALL:
			set_nat_params(adap, f, tid, true, true, true, true);
			अवरोध;

		शेष:
			pr_err("%s: Invalid NAT mode: %d\n",
			       __func__, f->fs.nat_mode);
			वापस -EINVAL;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

व्योम hash_del_filter_rpl(काष्ठा adapter *adap,
			 स्थिर काष्ठा cpl_पात_rpl_rss *rpl)
अणु
	अचिन्हित पूर्णांक status = rpl->status;
	काष्ठा tid_info *t = &adap->tids;
	अचिन्हित पूर्णांक tid = GET_TID(rpl);
	काष्ठा filter_ctx *ctx = शून्य;
	काष्ठा filter_entry *f;

	dev_dbg(adap->pdev_dev, "%s: status = %u; tid = %u\n",
		__func__, status, tid);

	f = lookup_tid(t, tid);
	अगर (!f) अणु
		dev_err(adap->pdev_dev, "%s:could not find filter entry",
			__func__);
		वापस;
	पूर्ण
	ctx = f->ctx;
	f->ctx = शून्य;
	clear_filter(adap, f);
	cxgb4_हटाओ_tid(t, 0, tid, 0);
	kमुक्त(f);
	अगर (ctx) अणु
		ctx->result = 0;
		complete(&ctx->completion);
	पूर्ण
पूर्ण

व्योम hash_filter_rpl(काष्ठा adapter *adap, स्थिर काष्ठा cpl_act_खोलो_rpl *rpl)
अणु
	अचिन्हित पूर्णांक ftid = TID_TID_G(AOPEN_ATID_G(ntohl(rpl->atid_status)));
	अचिन्हित पूर्णांक status  = AOPEN_STATUS_G(ntohl(rpl->atid_status));
	काष्ठा tid_info *t = &adap->tids;
	अचिन्हित पूर्णांक tid = GET_TID(rpl);
	काष्ठा filter_ctx *ctx = शून्य;
	काष्ठा filter_entry *f;

	dev_dbg(adap->pdev_dev, "%s: tid = %u; atid = %u; status = %u\n",
		__func__, tid, ftid, status);

	f = lookup_atid(t, ftid);
	अगर (!f) अणु
		dev_err(adap->pdev_dev, "%s:could not find filter entry",
			__func__);
		वापस;
	पूर्ण
	ctx = f->ctx;
	f->ctx = शून्य;

	चयन (status) अणु
	हाल CPL_ERR_NONE:
		f->tid = tid;
		f->pending = 0;
		f->valid = 1;
		cxgb4_insert_tid(t, f, f->tid, 0);
		cxgb4_मुक्त_atid(t, ftid);
		अगर (ctx) अणु
			ctx->tid = f->tid;
			ctx->result = 0;
		पूर्ण
		अगर (configure_filter_tcb(adap, tid, f)) अणु
			clear_filter(adap, f);
			cxgb4_हटाओ_tid(t, 0, tid, 0);
			kमुक्त(f);
			अगर (ctx) अणु
				ctx->result = -EINVAL;
				complete(&ctx->completion);
			पूर्ण
			वापस;
		पूर्ण
		चयन (f->fs.action) अणु
		हाल FILTER_PASS:
			अगर (f->fs.dirsteer)
				set_tcb_tflag(adap, f, tid,
					      TF_सूचीECT_STEER_S, 1, 1);
			अवरोध;
		हाल FILTER_DROP:
			set_tcb_tflag(adap, f, tid, TF_DROP_S, 1, 1);
			अवरोध;
		हाल FILTER_SWITCH:
			set_tcb_tflag(adap, f, tid, TF_LPBK_S, 1, 1);
			अवरोध;
		पूर्ण

		अवरोध;

	शेष:
		अगर (status != CPL_ERR_TCAM_FULL)
			dev_err(adap->pdev_dev, "%s: filter creation PROBLEM; status = %u\n",
				__func__, status);

		अगर (ctx) अणु
			अगर (status == CPL_ERR_TCAM_FULL)
				ctx->result = -ENOSPC;
			अन्यथा
				ctx->result = -EINVAL;
		पूर्ण
		clear_filter(adap, f);
		cxgb4_मुक्त_atid(t, ftid);
		kमुक्त(f);
	पूर्ण
	अगर (ctx)
		complete(&ctx->completion);
पूर्ण

/* Handle a filter ग_लिखो/deletion reply. */
व्योम filter_rpl(काष्ठा adapter *adap, स्थिर काष्ठा cpl_set_tcb_rpl *rpl)
अणु
	अचिन्हित पूर्णांक tid = GET_TID(rpl);
	काष्ठा filter_entry *f = शून्य;
	अचिन्हित पूर्णांक max_fidx;
	पूर्णांक idx;

	max_fidx = adap->tids.nftids + adap->tids.nsftids;
	/* Get the corresponding filter entry क्रम this tid */
	अगर (adap->tids.ftid_tab) अणु
		idx = tid - adap->tids.hpftid_base;
		अगर (idx < adap->tids.nhpftids) अणु
			f = &adap->tids.hpftid_tab[idx];
		पूर्ण अन्यथा अणु
			/* Check this in normal filter region */
			idx = tid - adap->tids.ftid_base;
			अगर (idx >= max_fidx)
				वापस;
			f = &adap->tids.ftid_tab[idx];
			idx += adap->tids.nhpftids;
		पूर्ण

		अगर (f->tid != tid)
			वापस;
	पूर्ण

	/* We found the filter entry क्रम this tid */
	अगर (f) अणु
		अचिन्हित पूर्णांक ret = TCB_COOKIE_G(rpl->cookie);
		काष्ठा filter_ctx *ctx;

		/* Pull off any filter operation context attached to the
		 * filter.
		 */
		ctx = f->ctx;
		f->ctx = शून्य;

		अगर (ret == FW_FILTER_WR_FLT_DELETED) अणु
			/* Clear the filter when we get confirmation from the
			 * hardware that the filter has been deleted.
			 */
			clear_filter(adap, f);
			अगर (ctx)
				ctx->result = 0;
		पूर्ण अन्यथा अगर (ret == FW_FILTER_WR_FLT_ADDED) अणु
			f->pending = 0;  /* async setup completed */
			f->valid = 1;
			अगर (ctx) अणु
				ctx->result = 0;
				ctx->tid = idx;
			पूर्ण
		पूर्ण अन्यथा अणु
			/* Something went wrong.  Issue a warning about the
			 * problem and clear everything out.
			 */
			dev_err(adap->pdev_dev, "filter %u setup failed with error %u\n",
				idx, ret);
			clear_filter(adap, f);
			अगर (ctx)
				ctx->result = -EINVAL;
		पूर्ण
		अगर (ctx)
			complete(&ctx->completion);
	पूर्ण
पूर्ण

व्योम init_hash_filter(काष्ठा adapter *adap)
अणु
	u32 reg;

	/* On T6, verअगरy the necessary रेजिस्टर configs and warn the user in
	 * हाल of improper config
	 */
	अगर (is_t6(adap->params.chip)) अणु
		अगर (is_offload(adap)) अणु
			अगर (!(t4_पढ़ो_reg(adap, TP_GLOBAL_CONFIG_A)
			   & ACTIVEFILTERCOUNTS_F)) अणु
				dev_err(adap->pdev_dev, "Invalid hash filter + ofld config\n");
				वापस;
			पूर्ण
		पूर्ण अन्यथा अणु
			reg = t4_पढ़ो_reg(adap, LE_DB_RSP_CODE_0_A);
			अगर (TCAM_ACTV_HIT_G(reg) != 4) अणु
				dev_err(adap->pdev_dev, "Invalid hash filter config\n");
				वापस;
			पूर्ण

			reg = t4_पढ़ो_reg(adap, LE_DB_RSP_CODE_1_A);
			अगर (HASH_ACTV_HIT_G(reg) != 4) अणु
				dev_err(adap->pdev_dev, "Invalid hash filter config\n");
				वापस;
			पूर्ण
		पूर्ण

	पूर्ण अन्यथा अणु
		dev_err(adap->pdev_dev, "Hash filter supported only on T6\n");
		वापस;
	पूर्ण

	adap->params.hash_filter = 1;
पूर्ण
