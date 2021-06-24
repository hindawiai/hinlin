<शैली गुरु>
/*
 * This file is part of the Chelsio FCoE driver क्रम Linux.
 *
 * Copyright (c) 2008-2012 Chelsio Communications, Inc. All rights reserved.
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

#समावेश <linux/माला.स>
#समावेश <scsi/scsi_device.h>
#समावेश <scsi/scsi_transport_fc.h>
#समावेश <scsi/fc/fc_els.h>
#समावेश <scsi/fc/fc_fs.h>

#समावेश "csio_hw.h"
#समावेश "csio_lnode.h"
#समावेश "csio_rnode.h"

अटल पूर्णांक csio_rnode_init(काष्ठा csio_rnode *, काष्ठा csio_lnode *);
अटल व्योम csio_rnode_निकास(काष्ठा csio_rnode *);

/* Static machine क्रमward declarations */
अटल व्योम csio_rns_uninit(काष्ठा csio_rnode *, क्रमागत csio_rn_ev);
अटल व्योम csio_rns_पढ़ोy(काष्ठा csio_rnode *, क्रमागत csio_rn_ev);
अटल व्योम csio_rns_offline(काष्ठा csio_rnode *, क्रमागत csio_rn_ev);
अटल व्योम csio_rns_disappeared(काष्ठा csio_rnode *, क्रमागत csio_rn_ev);

/* RNF event mapping */
अटल क्रमागत csio_rn_ev fwevt_to_rnevt[] = अणु
	CSIO_RNFE_NONE,		/* None */
	CSIO_RNFE_LOGGED_IN,	/* PLOGI_ACC_RCVD  */
	CSIO_RNFE_NONE,		/* PLOGI_RJT_RCVD  */
	CSIO_RNFE_PLOGI_RECV,	/* PLOGI_RCVD	   */
	CSIO_RNFE_LOGO_RECV,	/* PLOGO_RCVD	   */
	CSIO_RNFE_PRLI_DONE,	/* PRLI_ACC_RCVD   */
	CSIO_RNFE_NONE,		/* PRLI_RJT_RCVD   */
	CSIO_RNFE_PRLI_RECV,	/* PRLI_RCVD	   */
	CSIO_RNFE_PRLO_RECV,	/* PRLO_RCVD	   */
	CSIO_RNFE_NONE,		/* NPORT_ID_CHGD   */
	CSIO_RNFE_LOGO_RECV,	/* FLOGO_RCVD	   */
	CSIO_RNFE_NONE,		/* CLR_VIRT_LNK_RCVD */
	CSIO_RNFE_LOGGED_IN,	/* FLOGI_ACC_RCVD   */
	CSIO_RNFE_NONE,		/* FLOGI_RJT_RCVD   */
	CSIO_RNFE_LOGGED_IN,	/* FDISC_ACC_RCVD   */
	CSIO_RNFE_NONE,		/* FDISC_RJT_RCVD   */
	CSIO_RNFE_NONE,		/* FLOGI_TMO_MAX_RETRY */
	CSIO_RNFE_NONE,		/* IMPL_LOGO_ADISC_ACC */
	CSIO_RNFE_NONE,		/* IMPL_LOGO_ADISC_RJT */
	CSIO_RNFE_NONE,		/* IMPL_LOGO_ADISC_CNFLT */
	CSIO_RNFE_NONE,		/* PRLI_TMO		*/
	CSIO_RNFE_NONE,		/* ADISC_TMO		*/
	CSIO_RNFE_NAME_MISSING,	/* RSCN_DEV_LOST  */
	CSIO_RNFE_NONE,		/* SCR_ACC_RCVD	*/
	CSIO_RNFE_NONE,		/* ADISC_RJT_RCVD */
	CSIO_RNFE_NONE,		/* LOGO_SNT */
	CSIO_RNFE_LOGO_RECV,	/* PROTO_ERR_IMPL_LOGO */
पूर्ण;

#घोषणा CSIO_FWE_TO_RNFE(_evt)	((_evt > PROTO_ERR_IMPL_LOGO) ?		\
						CSIO_RNFE_NONE :	\
						fwevt_to_rnevt[_evt])
पूर्णांक
csio_is_rnode_पढ़ोy(काष्ठा csio_rnode *rn)
अणु
	वापस csio_match_state(rn, csio_rns_पढ़ोy);
पूर्ण

अटल पूर्णांक
csio_is_rnode_uninit(काष्ठा csio_rnode *rn)
अणु
	वापस csio_match_state(rn, csio_rns_uninit);
पूर्ण

अटल पूर्णांक
csio_is_rnode_wka(uपूर्णांक8_t rport_type)
अणु
	अगर ((rport_type == FLOGI_VFPORT) ||
	    (rport_type == FDISC_VFPORT) ||
	    (rport_type == NS_VNPORT) ||
	    (rport_type == FDMI_VNPORT))
		वापस 1;

	वापस 0;
पूर्ण

/*
 * csio_rn_lookup - Finds the rnode with the given flowid
 * @ln - lnode
 * @flowid - flowid.
 *
 * Does the rnode lookup on the given lnode and flowid.If no matching entry
 * found, शून्य is वापसed.
 */
अटल काष्ठा csio_rnode *
csio_rn_lookup(काष्ठा csio_lnode *ln, uपूर्णांक32_t flowid)
अणु
	काष्ठा csio_rnode *rnhead = (काष्ठा csio_rnode *) &ln->rnhead;
	काष्ठा list_head *पंचांगp;
	काष्ठा csio_rnode *rn;

	list_क्रम_each(पंचांगp, &rnhead->sm.sm_list) अणु
		rn = (काष्ठा csio_rnode *) पंचांगp;
		अगर (rn->flowid == flowid)
			वापस rn;
	पूर्ण

	वापस शून्य;
पूर्ण

/*
 * csio_rn_lookup_wwpn - Finds the rnode with the given wwpn
 * @ln: lnode
 * @wwpn: wwpn
 *
 * Does the rnode lookup on the given lnode and wwpn. If no matching entry
 * found, शून्य is वापसed.
 */
अटल काष्ठा csio_rnode *
csio_rn_lookup_wwpn(काष्ठा csio_lnode *ln, uपूर्णांक8_t *wwpn)
अणु
	काष्ठा csio_rnode *rnhead = (काष्ठा csio_rnode *) &ln->rnhead;
	काष्ठा list_head *पंचांगp;
	काष्ठा csio_rnode *rn;

	list_क्रम_each(पंचांगp, &rnhead->sm.sm_list) अणु
		rn = (काष्ठा csio_rnode *) पंचांगp;
		अगर (!स_भेद(csio_rn_wwpn(rn), wwpn, 8))
			वापस rn;
	पूर्ण

	वापस शून्य;
पूर्ण

/**
 * csio_rnode_lookup_portid - Finds the rnode with the given portid
 * @ln:		lnode
 * @portid:	port id
 *
 * Lookup the rnode list क्रम a given portid. If no matching entry
 * found, शून्य is वापसed.
 */
काष्ठा csio_rnode *
csio_rnode_lookup_portid(काष्ठा csio_lnode *ln, uपूर्णांक32_t portid)
अणु
	काष्ठा csio_rnode *rnhead = (काष्ठा csio_rnode *) &ln->rnhead;
	काष्ठा list_head *पंचांगp;
	काष्ठा csio_rnode *rn;

	list_क्रम_each(पंचांगp, &rnhead->sm.sm_list) अणु
		rn = (काष्ठा csio_rnode *) पंचांगp;
		अगर (rn->nport_id == portid)
			वापस rn;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल पूर्णांक
csio_rn_dup_flowid(काष्ठा csio_lnode *ln, uपूर्णांक32_t rdev_flowid,
		    uपूर्णांक32_t *vnp_flowid)
अणु
	काष्ठा csio_rnode *rnhead;
	काष्ठा list_head *पंचांगp, *पंचांगp1;
	काष्ठा csio_rnode *rn;
	काष्ठा csio_lnode *ln_पंचांगp;
	काष्ठा csio_hw *hw = csio_lnode_to_hw(ln);

	list_क्रम_each(पंचांगp1, &hw->sln_head) अणु
		ln_पंचांगp = (काष्ठा csio_lnode *) पंचांगp1;
		अगर (ln_पंचांगp == ln)
			जारी;

		rnhead = (काष्ठा csio_rnode *)&ln_पंचांगp->rnhead;
		list_क्रम_each(पंचांगp, &rnhead->sm.sm_list) अणु

			rn = (काष्ठा csio_rnode *) पंचांगp;
			अगर (csio_is_rnode_पढ़ोy(rn)) अणु
				अगर (rn->flowid == rdev_flowid) अणु
					*vnp_flowid = csio_ln_flowid(ln_पंचांगp);
					वापस 1;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा csio_rnode *
csio_alloc_rnode(काष्ठा csio_lnode *ln)
अणु
	काष्ठा csio_hw *hw = csio_lnode_to_hw(ln);

	काष्ठा csio_rnode *rn = mempool_alloc(hw->rnode_mempool, GFP_ATOMIC);
	अगर (!rn)
		जाओ err;

	स_रखो(rn, 0, माप(काष्ठा csio_rnode));
	अगर (csio_rnode_init(rn, ln))
		जाओ err_मुक्त;

	CSIO_INC_STATS(ln, n_rnode_alloc);

	वापस rn;

err_मुक्त:
	mempool_मुक्त(rn, hw->rnode_mempool);
err:
	CSIO_INC_STATS(ln, n_rnode_nomem);
	वापस शून्य;
पूर्ण

अटल व्योम
csio_मुक्त_rnode(काष्ठा csio_rnode *rn)
अणु
	काष्ठा csio_hw *hw = csio_lnode_to_hw(csio_rnode_to_lnode(rn));

	csio_rnode_निकास(rn);
	CSIO_INC_STATS(rn->lnp, n_rnode_मुक्त);
	mempool_मुक्त(rn, hw->rnode_mempool);
पूर्ण

/*
 * csio_get_rnode - Gets rnode with the given flowid
 * @ln - lnode
 * @flowid - flow id.
 *
 * Does the rnode lookup on the given lnode and flowid. If no matching
 * rnode found, then new rnode with given npid is allocated and वापसed.
 */
अटल काष्ठा csio_rnode *
csio_get_rnode(काष्ठा csio_lnode *ln, uपूर्णांक32_t flowid)
अणु
	काष्ठा csio_rnode *rn;

	rn = csio_rn_lookup(ln, flowid);
	अगर (!rn) अणु
		rn = csio_alloc_rnode(ln);
		अगर (!rn)
			वापस शून्य;

		rn->flowid = flowid;
	पूर्ण

	वापस rn;
पूर्ण

/*
 * csio_put_rnode - Frees the given rnode
 * @ln - lnode
 * @flowid - flow id.
 *
 * Does the rnode lookup on the given lnode and flowid. If no matching
 * rnode found, then new rnode with given npid is allocated and वापसed.
 */
व्योम
csio_put_rnode(काष्ठा csio_lnode *ln, काष्ठा csio_rnode *rn)
अणु
	CSIO_DB_ASSERT(csio_is_rnode_uninit(rn) != 0);
	csio_मुक्त_rnode(rn);
पूर्ण

/*
 * csio_confirm_rnode - confirms rnode based on wwpn.
 * @ln: lnode
 * @rdev_flowid: remote device flowid
 * @rdevp: remote device params
 * This routines searches other rnode in list having same wwpn of new rnode.
 * If there is a match, then matched rnode is वापसed and otherwise new rnode
 * is वापसed.
 * वापसs rnode.
 */
काष्ठा csio_rnode *
csio_confirm_rnode(काष्ठा csio_lnode *ln, uपूर्णांक32_t rdev_flowid,
		   काष्ठा fcoe_rdev_entry *rdevp)
अणु
	uपूर्णांक8_t rport_type;
	काष्ठा csio_rnode *rn, *match_rn;
	uपूर्णांक32_t vnp_flowid = 0;
	__be32 *port_id;

	port_id = (__be32 *)&rdevp->r_id[0];
	rport_type =
		FW_RDEV_WR_RPORT_TYPE_GET(rdevp->rd_xfer_rdy_to_rport_type);

	/* Drop rdev event क्रम cntrl port */
	अगर (rport_type == FAB_CTLR_VNPORT) अणु
		csio_ln_dbg(ln,
			    "Unhandled rport_type:%d recv in rdev evt "
			    "ssni:x%x\n", rport_type, rdev_flowid);
		वापस शून्य;
	पूर्ण

	/* Lookup on flowid */
	rn = csio_rn_lookup(ln, rdev_flowid);
	अगर (!rn) अणु

		/* Drop events with duplicate flowid */
		अगर (csio_rn_dup_flowid(ln, rdev_flowid, &vnp_flowid)) अणु
			csio_ln_warn(ln,
				     "ssni:%x already active on vnpi:%x",
				     rdev_flowid, vnp_flowid);
			वापस शून्य;
		पूर्ण

		/* Lookup on wwpn क्रम NPORTs */
		rn = csio_rn_lookup_wwpn(ln, rdevp->wwpn);
		अगर (!rn)
			जाओ alloc_rnode;

	पूर्ण अन्यथा अणु
		/* Lookup well-known ports with nport id */
		अगर (csio_is_rnode_wka(rport_type)) अणु
			match_rn = csio_rnode_lookup_portid(ln,
				      ((ntohl(*port_id) >> 8) & CSIO_DID_MASK));
			अगर (match_rn == शून्य) अणु
				csio_rn_flowid(rn) = CSIO_INVALID_IDX;
				जाओ alloc_rnode;
			पूर्ण

			/*
			 * Now compare the wwpn to confirm that
			 * same port relogged in. If so update the matched rn.
			 * Else, go ahead and alloc a new rnode.
			 */
			अगर (!स_भेद(csio_rn_wwpn(match_rn), rdevp->wwpn, 8)) अणु
				अगर (rn == match_rn)
					जाओ found_rnode;
				csio_ln_dbg(ln,
					    "nport_id:x%x and wwpn:%llx"
					    " match for ssni:x%x\n",
					    rn->nport_id,
					    wwn_to_u64(rdevp->wwpn),
					    rdev_flowid);
				अगर (csio_is_rnode_पढ़ोy(rn)) अणु
					csio_ln_warn(ln,
						     "rnode is already"
						     "active ssni:x%x\n",
						     rdev_flowid);
					CSIO_ASSERT(0);
				पूर्ण
				csio_rn_flowid(rn) = CSIO_INVALID_IDX;
				rn = match_rn;

				/* Update rn */
				जाओ found_rnode;
			पूर्ण
			csio_rn_flowid(rn) = CSIO_INVALID_IDX;
			जाओ alloc_rnode;
		पूर्ण

		/* wwpn match */
		अगर (!स_भेद(csio_rn_wwpn(rn), rdevp->wwpn, 8))
			जाओ found_rnode;

		/* Search क्रम rnode that have same wwpn */
		match_rn = csio_rn_lookup_wwpn(ln, rdevp->wwpn);
		अगर (match_rn != शून्य) अणु
			csio_ln_dbg(ln,
				"ssni:x%x changed for rport name(wwpn):%llx "
				"did:x%x\n", rdev_flowid,
				wwn_to_u64(rdevp->wwpn),
				match_rn->nport_id);
			csio_rn_flowid(rn) = CSIO_INVALID_IDX;
			rn = match_rn;
		पूर्ण अन्यथा अणु
			csio_ln_dbg(ln,
				"rnode wwpn mismatch found ssni:x%x "
				"name(wwpn):%llx\n",
				rdev_flowid,
				wwn_to_u64(csio_rn_wwpn(rn)));
			अगर (csio_is_rnode_पढ़ोy(rn)) अणु
				csio_ln_warn(ln,
					     "rnode is already active "
					     "wwpn:%llx ssni:x%x\n",
					     wwn_to_u64(csio_rn_wwpn(rn)),
					     rdev_flowid);
				CSIO_ASSERT(0);
			पूर्ण
			csio_rn_flowid(rn) = CSIO_INVALID_IDX;
			जाओ alloc_rnode;
		पूर्ण
	पूर्ण

found_rnode:
	csio_ln_dbg(ln, "found rnode:%p ssni:x%x name(wwpn):%llx\n",
		rn, rdev_flowid, wwn_to_u64(rdevp->wwpn));

	/* Update flowid */
	csio_rn_flowid(rn) = rdev_flowid;

	/* update rdev entry */
	rn->rdev_entry = rdevp;
	CSIO_INC_STATS(ln, n_rnode_match);
	वापस rn;

alloc_rnode:
	rn = csio_get_rnode(ln, rdev_flowid);
	अगर (!rn)
		वापस शून्य;

	csio_ln_dbg(ln, "alloc rnode:%p ssni:x%x name(wwpn):%llx\n",
		rn, rdev_flowid, wwn_to_u64(rdevp->wwpn));

	/* update rdev entry */
	rn->rdev_entry = rdevp;
	वापस rn;
पूर्ण

/*
 * csio_rn_verअगरy_rparams - verअगरy rparams.
 * @ln: lnode
 * @rn: rnode
 * @rdevp: remote device params
 * वापसs success अगर rparams are verअगरied.
 */
अटल पूर्णांक
csio_rn_verअगरy_rparams(काष्ठा csio_lnode *ln, काष्ठा csio_rnode *rn,
			काष्ठा fcoe_rdev_entry *rdevp)
अणु
	uपूर्णांक8_t null[8];
	uपूर्णांक8_t rport_type;
	uपूर्णांक8_t fc_class;
	__be32 *did;

	did = (__be32 *) &rdevp->r_id[0];
	rport_type =
		FW_RDEV_WR_RPORT_TYPE_GET(rdevp->rd_xfer_rdy_to_rport_type);
	चयन (rport_type) अणु
	हाल FLOGI_VFPORT:
		rn->role = CSIO_RNFR_FABRIC;
		अगर (((ntohl(*did) >> 8) & CSIO_DID_MASK) != FC_FID_FLOGI) अणु
			csio_ln_err(ln, "ssni:x%x invalid fabric portid\n",
				csio_rn_flowid(rn));
			वापस -EINVAL;
		पूर्ण
		/* NPIV support */
		अगर (FW_RDEV_WR_NPIV_GET(rdevp->vft_to_qos))
			ln->flags |= CSIO_LNF_NPIVSUPP;

		अवरोध;

	हाल NS_VNPORT:
		rn->role = CSIO_RNFR_NS;
		अगर (((ntohl(*did) >> 8) & CSIO_DID_MASK) != FC_FID_सूची_SERV) अणु
			csio_ln_err(ln, "ssni:x%x invalid fabric portid\n",
				csio_rn_flowid(rn));
			वापस -EINVAL;
		पूर्ण
		अवरोध;

	हाल REG_FC4_VNPORT:
	हाल REG_VNPORT:
		rn->role = CSIO_RNFR_NPORT;
		अगर (rdevp->event_cause == PRLI_ACC_RCVD ||
			rdevp->event_cause == PRLI_RCVD) अणु
			अगर (FW_RDEV_WR_TASK_RETRY_ID_GET(
							rdevp->enh_disc_to_tgt))
				rn->fcp_flags |= FCP_SPPF_OVLY_ALLOW;

			अगर (FW_RDEV_WR_RETRY_GET(rdevp->enh_disc_to_tgt))
				rn->fcp_flags |= FCP_SPPF_RETRY;

			अगर (FW_RDEV_WR_CONF_CMPL_GET(rdevp->enh_disc_to_tgt))
				rn->fcp_flags |= FCP_SPPF_CONF_COMPL;

			अगर (FW_RDEV_WR_TGT_GET(rdevp->enh_disc_to_tgt))
				rn->role |= CSIO_RNFR_TARGET;

			अगर (FW_RDEV_WR_INI_GET(rdevp->enh_disc_to_tgt))
				rn->role |= CSIO_RNFR_INITIATOR;
		पूर्ण

		अवरोध;

	हाल FDMI_VNPORT:
	हाल FAB_CTLR_VNPORT:
		rn->role = 0;
		अवरोध;

	शेष:
		csio_ln_err(ln, "ssni:x%x invalid rport type recv x%x\n",
			csio_rn_flowid(rn), rport_type);
		वापस -EINVAL;
	पूर्ण

	/* validate wwpn/wwnn क्रम Name server/remote port */
	अगर (rport_type == REG_VNPORT || rport_type == NS_VNPORT) अणु
		स_रखो(null, 0, 8);
		अगर (!स_भेद(rdevp->wwnn, null, 8)) अणु
			csio_ln_err(ln,
				    "ssni:x%x invalid wwnn received from"
				    " rport did:x%x\n",
				    csio_rn_flowid(rn),
				    (ntohl(*did) & CSIO_DID_MASK));
			वापस -EINVAL;
		पूर्ण

		अगर (!स_भेद(rdevp->wwpn, null, 8)) अणु
			csio_ln_err(ln,
				    "ssni:x%x invalid wwpn received from"
				    " rport did:x%x\n",
				    csio_rn_flowid(rn),
				    (ntohl(*did) & CSIO_DID_MASK));
			वापस -EINVAL;
		पूर्ण

	पूर्ण

	/* Copy wwnn, wwpn and nport id */
	rn->nport_id = (ntohl(*did) >> 8) & CSIO_DID_MASK;
	स_नकल(csio_rn_wwnn(rn), rdevp->wwnn, 8);
	स_नकल(csio_rn_wwpn(rn), rdevp->wwpn, 8);
	rn->rn_sparm.csp.sp_bb_data = rdevp->rcv_fr_sz;
	fc_class = FW_RDEV_WR_CLASS_GET(rdevp->vft_to_qos);
	rn->rn_sparm.clsp[fc_class - 1].cp_class = htons(FC_CPC_VALID);

	वापस 0;
पूर्ण

अटल व्योम
__csio_reg_rnode(काष्ठा csio_rnode *rn)
अणु
	काष्ठा csio_lnode *ln = csio_rnode_to_lnode(rn);
	काष्ठा csio_hw *hw = csio_lnode_to_hw(ln);

	spin_unlock_irq(&hw->lock);
	csio_reg_rnode(rn);
	spin_lock_irq(&hw->lock);

	अगर (rn->role & CSIO_RNFR_TARGET)
		ln->n_scsi_tgts++;

	अगर (rn->nport_id == FC_FID_MGMT_SERV)
		csio_ln_fdmi_start(ln, (व्योम *) rn);
पूर्ण

अटल व्योम
__csio_unreg_rnode(काष्ठा csio_rnode *rn)
अणु
	काष्ठा csio_lnode *ln = csio_rnode_to_lnode(rn);
	काष्ठा csio_hw *hw = csio_lnode_to_hw(ln);
	LIST_HEAD(पंचांगp_q);
	पूर्णांक cmpl = 0;

	अगर (!list_empty(&rn->host_cmpl_q)) अणु
		csio_dbg(hw, "Returning completion queue I/Os\n");
		list_splice_tail_init(&rn->host_cmpl_q, &पंचांगp_q);
		cmpl = 1;
	पूर्ण

	अगर (rn->role & CSIO_RNFR_TARGET) अणु
		ln->n_scsi_tgts--;
		ln->last_scan_ntgts--;
	पूर्ण

	spin_unlock_irq(&hw->lock);
	csio_unreg_rnode(rn);
	spin_lock_irq(&hw->lock);

	/* Cleanup I/Os that were रुकोing क्रम rnode to unरेजिस्टर */
	अगर (cmpl)
		csio_scsi_cleanup_io_q(csio_hw_to_scsim(hw), &पंचांगp_q);

पूर्ण

/*****************************************************************************/
/* START: Rnode SM                                                           */
/*****************************************************************************/

/*
 * csio_rns_uninit -
 * @rn - rnode
 * @evt - SM event.
 *
 */
अटल व्योम
csio_rns_uninit(काष्ठा csio_rnode *rn, क्रमागत csio_rn_ev evt)
अणु
	काष्ठा csio_lnode *ln = csio_rnode_to_lnode(rn);
	पूर्णांक ret = 0;

	CSIO_INC_STATS(rn, n_evt_sm[evt]);

	चयन (evt) अणु
	हाल CSIO_RNFE_LOGGED_IN:
	हाल CSIO_RNFE_PLOGI_RECV:
		ret = csio_rn_verअगरy_rparams(ln, rn, rn->rdev_entry);
		अगर (!ret) अणु
			csio_set_state(&rn->sm, csio_rns_पढ़ोy);
			__csio_reg_rnode(rn);
		पूर्ण अन्यथा अणु
			CSIO_INC_STATS(rn, n_err_inval);
		पूर्ण
		अवरोध;
	हाल CSIO_RNFE_LOGO_RECV:
		csio_ln_dbg(ln,
			    "ssni:x%x Ignoring event %d recv "
			    "in rn state[uninit]\n", csio_rn_flowid(rn), evt);
		CSIO_INC_STATS(rn, n_evt_drop);
		अवरोध;
	शेष:
		csio_ln_dbg(ln,
			    "ssni:x%x unexp event %d recv "
			    "in rn state[uninit]\n", csio_rn_flowid(rn), evt);
		CSIO_INC_STATS(rn, n_evt_unexp);
		अवरोध;
	पूर्ण
पूर्ण

/*
 * csio_rns_पढ़ोy -
 * @rn - rnode
 * @evt - SM event.
 *
 */
अटल व्योम
csio_rns_पढ़ोy(काष्ठा csio_rnode *rn, क्रमागत csio_rn_ev evt)
अणु
	काष्ठा csio_lnode *ln = csio_rnode_to_lnode(rn);
	पूर्णांक ret = 0;

	CSIO_INC_STATS(rn, n_evt_sm[evt]);

	चयन (evt) अणु
	हाल CSIO_RNFE_LOGGED_IN:
	हाल CSIO_RNFE_PLOGI_RECV:
		csio_ln_dbg(ln,
			"ssni:x%x Ignoring event %d recv from did:x%x "
			"in rn state[ready]\n", csio_rn_flowid(rn), evt,
			rn->nport_id);
		CSIO_INC_STATS(rn, n_evt_drop);
		अवरोध;

	हाल CSIO_RNFE_PRLI_DONE:
	हाल CSIO_RNFE_PRLI_RECV:
		ret = csio_rn_verअगरy_rparams(ln, rn, rn->rdev_entry);
		अगर (!ret)
			__csio_reg_rnode(rn);
		अन्यथा
			CSIO_INC_STATS(rn, n_err_inval);

		अवरोध;
	हाल CSIO_RNFE_DOWN:
		csio_set_state(&rn->sm, csio_rns_offline);
		__csio_unreg_rnode(rn);

		/* FW expected to पूर्णांकernally पातed outstanding SCSI WRs
		 * and वापस all SCSI WRs to host with status "ABORTED".
		 */
		अवरोध;

	हाल CSIO_RNFE_LOGO_RECV:
		csio_set_state(&rn->sm, csio_rns_offline);

		__csio_unreg_rnode(rn);

		/* FW expected to पूर्णांकernally पातed outstanding SCSI WRs
		 * and वापस all SCSI WRs to host with status "ABORTED".
		 */
		अवरोध;

	हाल CSIO_RNFE_CLOSE:
		/*
		 * Each rnode receives CLOSE event when driver is हटाओd or
		 * device is reset
		 * Note: All outstanding IOs on remote port need to वापसed
		 * to uppper layer with appropriate error beक्रमe sending
		 * CLOSE event
		 */
		csio_set_state(&rn->sm, csio_rns_uninit);
		__csio_unreg_rnode(rn);
		अवरोध;

	हाल CSIO_RNFE_NAME_MISSING:
		csio_set_state(&rn->sm, csio_rns_disappeared);
		__csio_unreg_rnode(rn);

		/*
		 * FW expected to पूर्णांकernally पातed outstanding SCSI WRs
		 * and वापस all SCSI WRs to host with status "ABORTED".
		 */

		अवरोध;

	शेष:
		csio_ln_dbg(ln,
			"ssni:x%x unexp event %d recv from did:x%x "
			"in rn state[uninit]\n", csio_rn_flowid(rn), evt,
			rn->nport_id);
		CSIO_INC_STATS(rn, n_evt_unexp);
		अवरोध;
	पूर्ण
पूर्ण

/*
 * csio_rns_offline -
 * @rn - rnode
 * @evt - SM event.
 *
 */
अटल व्योम
csio_rns_offline(काष्ठा csio_rnode *rn, क्रमागत csio_rn_ev evt)
अणु
	काष्ठा csio_lnode *ln = csio_rnode_to_lnode(rn);
	पूर्णांक ret = 0;

	CSIO_INC_STATS(rn, n_evt_sm[evt]);

	चयन (evt) अणु
	हाल CSIO_RNFE_LOGGED_IN:
	हाल CSIO_RNFE_PLOGI_RECV:
		ret = csio_rn_verअगरy_rparams(ln, rn, rn->rdev_entry);
		अगर (!ret) अणु
			csio_set_state(&rn->sm, csio_rns_पढ़ोy);
			__csio_reg_rnode(rn);
		पूर्ण अन्यथा अणु
			CSIO_INC_STATS(rn, n_err_inval);
			csio_post_event(&rn->sm, CSIO_RNFE_CLOSE);
		पूर्ण
		अवरोध;

	हाल CSIO_RNFE_DOWN:
		csio_ln_dbg(ln,
			"ssni:x%x Ignoring event %d recv from did:x%x "
			"in rn state[offline]\n", csio_rn_flowid(rn), evt,
			rn->nport_id);
		CSIO_INC_STATS(rn, n_evt_drop);
		अवरोध;

	हाल CSIO_RNFE_CLOSE:
		/* Each rnode receives CLOSE event when driver is हटाओd or
		 * device is reset
		 * Note: All outstanding IOs on remote port need to वापसed
		 * to uppper layer with appropriate error beक्रमe sending
		 * CLOSE event
		 */
		csio_set_state(&rn->sm, csio_rns_uninit);
		अवरोध;

	हाल CSIO_RNFE_NAME_MISSING:
		csio_set_state(&rn->sm, csio_rns_disappeared);
		अवरोध;

	शेष:
		csio_ln_dbg(ln,
			"ssni:x%x unexp event %d recv from did:x%x "
			"in rn state[offline]\n", csio_rn_flowid(rn), evt,
			rn->nport_id);
		CSIO_INC_STATS(rn, n_evt_unexp);
		अवरोध;
	पूर्ण
पूर्ण

/*
 * csio_rns_disappeared -
 * @rn - rnode
 * @evt - SM event.
 *
 */
अटल व्योम
csio_rns_disappeared(काष्ठा csio_rnode *rn, क्रमागत csio_rn_ev evt)
अणु
	काष्ठा csio_lnode *ln = csio_rnode_to_lnode(rn);
	पूर्णांक ret = 0;

	CSIO_INC_STATS(rn, n_evt_sm[evt]);

	चयन (evt) अणु
	हाल CSIO_RNFE_LOGGED_IN:
	हाल CSIO_RNFE_PLOGI_RECV:
		ret = csio_rn_verअगरy_rparams(ln, rn, rn->rdev_entry);
		अगर (!ret) अणु
			csio_set_state(&rn->sm, csio_rns_पढ़ोy);
			__csio_reg_rnode(rn);
		पूर्ण अन्यथा अणु
			CSIO_INC_STATS(rn, n_err_inval);
			csio_post_event(&rn->sm, CSIO_RNFE_CLOSE);
		पूर्ण
		अवरोध;

	हाल CSIO_RNFE_CLOSE:
		/* Each rnode receives CLOSE event when driver is हटाओd or
		 * device is reset.
		 * Note: All outstanding IOs on remote port need to वापसed
		 * to uppper layer with appropriate error beक्रमe sending
		 * CLOSE event
		 */
		csio_set_state(&rn->sm, csio_rns_uninit);
		अवरोध;

	हाल CSIO_RNFE_DOWN:
	हाल CSIO_RNFE_NAME_MISSING:
		csio_ln_dbg(ln,
			"ssni:x%x Ignoring event %d recv from did x%x"
			"in rn state[disappeared]\n", csio_rn_flowid(rn),
			evt, rn->nport_id);
		अवरोध;

	शेष:
		csio_ln_dbg(ln,
			"ssni:x%x unexp event %d recv from did x%x"
			"in rn state[disappeared]\n", csio_rn_flowid(rn),
			evt, rn->nport_id);
		CSIO_INC_STATS(rn, n_evt_unexp);
		अवरोध;
	पूर्ण
पूर्ण

/*****************************************************************************/
/* END: Rnode SM                                                             */
/*****************************************************************************/

/*
 * csio_rnode_devloss_handler - Device loss event handler
 * @rn: rnode
 *
 * Post event to बंद rnode SM and मुक्त rnode.
 */
व्योम
csio_rnode_devloss_handler(काष्ठा csio_rnode *rn)
अणु
	काष्ठा csio_lnode *ln = csio_rnode_to_lnode(rn);

	/* ignore अगर same rnode came back as online */
	अगर (csio_is_rnode_पढ़ोy(rn))
		वापस;

	csio_post_event(&rn->sm, CSIO_RNFE_CLOSE);

	/* Free rn अगर in uninit state */
	अगर (csio_is_rnode_uninit(rn))
		csio_put_rnode(ln, rn);
पूर्ण

/**
 * csio_rnode_fwevt_handler - Event handler क्रम firmware rnode events.
 * @rn:		rnode
 * @fwevt:	firmware event to handle
 */
व्योम
csio_rnode_fwevt_handler(काष्ठा csio_rnode *rn, uपूर्णांक8_t fwevt)
अणु
	काष्ठा csio_lnode *ln = csio_rnode_to_lnode(rn);
	क्रमागत csio_rn_ev evt;

	evt = CSIO_FWE_TO_RNFE(fwevt);
	अगर (!evt) अणु
		csio_ln_err(ln, "ssni:x%x Unhandled FW Rdev event: %d\n",
			    csio_rn_flowid(rn), fwevt);
		CSIO_INC_STATS(rn, n_evt_unexp);
		वापस;
	पूर्ण
	CSIO_INC_STATS(rn, n_evt_fw[fwevt]);

	/* Track previous & current events क्रम debugging */
	rn->prev_evt = rn->cur_evt;
	rn->cur_evt = fwevt;

	/* Post event to rnode SM */
	csio_post_event(&rn->sm, evt);

	/* Free rn अगर in uninit state */
	अगर (csio_is_rnode_uninit(rn))
		csio_put_rnode(ln, rn);
पूर्ण

/*
 * csio_rnode_init - Initialize rnode.
 * @rn: RNode
 * @ln: Associated lnode
 *
 * Caller is responsible क्रम holding the lock. The lock is required
 * to be held क्रम inserting the rnode in ln->rnhead list.
 */
अटल पूर्णांक
csio_rnode_init(काष्ठा csio_rnode *rn, काष्ठा csio_lnode *ln)
अणु
	csio_rnode_to_lnode(rn) = ln;
	csio_init_state(&rn->sm, csio_rns_uninit);
	INIT_LIST_HEAD(&rn->host_cmpl_q);
	csio_rn_flowid(rn) = CSIO_INVALID_IDX;

	/* Add rnode to list of lnodes->rnhead */
	list_add_tail(&rn->sm.sm_list, &ln->rnhead);

	वापस 0;
पूर्ण

अटल व्योम
csio_rnode_निकास(काष्ठा csio_rnode *rn)
अणु
	list_del_init(&rn->sm.sm_list);
	CSIO_DB_ASSERT(list_empty(&rn->host_cmpl_q));
पूर्ण
