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

#समावेश <linux/kernel.h>
#समावेश <linux/delay.h>
#समावेश <linux/slab.h>
#समावेश <linux/utsname.h>
#समावेश <scsi/scsi_device.h>
#समावेश <scsi/scsi_transport_fc.h>
#समावेश <यंत्र/unaligned.h>
#समावेश <scsi/fc/fc_els.h>
#समावेश <scsi/fc/fc_fs.h>
#समावेश <scsi/fc/fc_gs.h>
#समावेश <scsi/fc/fc_ms.h>

#समावेश "csio_hw.h"
#समावेश "csio_mb.h"
#समावेश "csio_lnode.h"
#समावेश "csio_rnode.h"

पूर्णांक csio_fcoe_rnodes = 1024;
पूर्णांक csio_fdmi_enable = 1;

#घोषणा PORT_ID_PTR(_x)         ((uपूर्णांक8_t *)(&_x) + 1)

/* Lnode SM declarations */
अटल व्योम csio_lns_uninit(काष्ठा csio_lnode *, क्रमागत csio_ln_ev);
अटल व्योम csio_lns_online(काष्ठा csio_lnode *, क्रमागत csio_ln_ev);
अटल व्योम csio_lns_पढ़ोy(काष्ठा csio_lnode *, क्रमागत csio_ln_ev);
अटल व्योम csio_lns_offline(काष्ठा csio_lnode *, क्रमागत csio_ln_ev);

अटल पूर्णांक csio_ln_mgmt_submit_req(काष्ठा csio_ioreq *,
		व्योम (*io_cbfn) (काष्ठा csio_hw *, काष्ठा csio_ioreq *),
		क्रमागत fcoe_cmn_type, काष्ठा csio_dma_buf *, uपूर्णांक32_t);

/* LN event mapping */
अटल क्रमागत csio_ln_ev fwevt_to_lnevt[] = अणु
	CSIO_LNE_NONE,		/* None */
	CSIO_LNE_NONE,		/* PLOGI_ACC_RCVD  */
	CSIO_LNE_NONE,		/* PLOGI_RJT_RCVD  */
	CSIO_LNE_NONE,		/* PLOGI_RCVD	   */
	CSIO_LNE_NONE,		/* PLOGO_RCVD	   */
	CSIO_LNE_NONE,		/* PRLI_ACC_RCVD   */
	CSIO_LNE_NONE,		/* PRLI_RJT_RCVD   */
	CSIO_LNE_NONE,		/* PRLI_RCVD	   */
	CSIO_LNE_NONE,		/* PRLO_RCVD	   */
	CSIO_LNE_NONE,		/* NPORT_ID_CHGD   */
	CSIO_LNE_LOGO,		/* FLOGO_RCVD	   */
	CSIO_LNE_LOGO,		/* CLR_VIRT_LNK_RCVD */
	CSIO_LNE_FAB_INIT_DONE,/* FLOGI_ACC_RCVD   */
	CSIO_LNE_NONE,		/* FLOGI_RJT_RCVD   */
	CSIO_LNE_FAB_INIT_DONE,/* FDISC_ACC_RCVD   */
	CSIO_LNE_NONE,		/* FDISC_RJT_RCVD   */
	CSIO_LNE_NONE,		/* FLOGI_TMO_MAX_RETRY */
	CSIO_LNE_NONE,		/* IMPL_LOGO_ADISC_ACC */
	CSIO_LNE_NONE,		/* IMPL_LOGO_ADISC_RJT */
	CSIO_LNE_NONE,		/* IMPL_LOGO_ADISC_CNFLT */
	CSIO_LNE_NONE,		/* PRLI_TMO		*/
	CSIO_LNE_NONE,		/* ADISC_TMO		*/
	CSIO_LNE_NONE,		/* RSCN_DEV_LOST */
	CSIO_LNE_NONE,		/* SCR_ACC_RCVD */
	CSIO_LNE_NONE,		/* ADISC_RJT_RCVD */
	CSIO_LNE_NONE,		/* LOGO_SNT */
	CSIO_LNE_NONE,		/* PROTO_ERR_IMPL_LOGO */
पूर्ण;

#घोषणा CSIO_FWE_TO_LNE(_evt)	((_evt > PROTO_ERR_IMPL_LOGO) ?		\
						CSIO_LNE_NONE :	\
						fwevt_to_lnevt[_evt])

#घोषणा csio_ct_rsp(cp)		(((काष्ठा fc_ct_hdr *)cp)->ct_cmd)
#घोषणा csio_ct_reason(cp)	(((काष्ठा fc_ct_hdr *)cp)->ct_reason)
#घोषणा csio_ct_expl(cp)	(((काष्ठा fc_ct_hdr *)cp)->ct_explan)
#घोषणा csio_ct_get_pld(cp)	((व्योम *)(((uपूर्णांक8_t *)cp) + FC_CT_HDR_LEN))

/*
 * csio_ln_match_by_portid - lookup lnode using given portid.
 * @hw: HW module
 * @portid: port-id.
 *
 * If found, वापसs lnode matching given portid otherwise वापसs शून्य.
 */
अटल काष्ठा csio_lnode *
csio_ln_lookup_by_portid(काष्ठा csio_hw *hw, uपूर्णांक8_t portid)
अणु
	काष्ठा csio_lnode *ln;
	काष्ठा list_head *पंचांगp;

	/* Match siblings lnode with portid */
	list_क्रम_each(पंचांगp, &hw->sln_head) अणु
		ln = (काष्ठा csio_lnode *) पंचांगp;
		अगर (ln->portid == portid)
			वापस ln;
	पूर्ण

	वापस शून्य;
पूर्ण

/*
 * csio_ln_lookup_by_vnpi - Lookup lnode using given vnp id.
 * @hw - HW module
 * @vnpi - vnp index.
 * Returns - If found, वापसs lnode matching given vnp id
 * otherwise वापसs शून्य.
 */
अटल काष्ठा csio_lnode *
csio_ln_lookup_by_vnpi(काष्ठा csio_hw *hw, uपूर्णांक32_t vnp_id)
अणु
	काष्ठा list_head *पंचांगp1, *पंचांगp2;
	काष्ठा csio_lnode *sln = शून्य, *cln = शून्य;

	अगर (list_empty(&hw->sln_head)) अणु
		CSIO_INC_STATS(hw, n_lnlkup_miss);
		वापस शून्य;
	पूर्ण
	/* Traverse sibling lnodes */
	list_क्रम_each(पंचांगp1, &hw->sln_head) अणु
		sln = (काष्ठा csio_lnode *) पंचांगp1;

		/* Match sibling lnode */
		अगर (sln->vnp_flowid == vnp_id)
			वापस sln;

		अगर (list_empty(&sln->cln_head))
			जारी;

		/* Traverse children lnodes */
		list_क्रम_each(पंचांगp2, &sln->cln_head) अणु
			cln = (काष्ठा csio_lnode *) पंचांगp2;

			अगर (cln->vnp_flowid == vnp_id)
				वापस cln;
		पूर्ण
	पूर्ण
	CSIO_INC_STATS(hw, n_lnlkup_miss);
	वापस शून्य;
पूर्ण

/**
 * csio_lnode_lookup_by_wwpn - Lookup lnode using given wwpn.
 * @hw:		HW module.
 * @wwpn:	WWPN.
 *
 * If found, वापसs lnode matching given wwpn, वापसs शून्य otherwise.
 */
काष्ठा csio_lnode *
csio_lnode_lookup_by_wwpn(काष्ठा csio_hw *hw, uपूर्णांक8_t *wwpn)
अणु
	काष्ठा list_head *पंचांगp1, *पंचांगp2;
	काष्ठा csio_lnode *sln = शून्य, *cln = शून्य;

	अगर (list_empty(&hw->sln_head)) अणु
		CSIO_INC_STATS(hw, n_lnlkup_miss);
		वापस शून्य;
	पूर्ण
	/* Traverse sibling lnodes */
	list_क्रम_each(पंचांगp1, &hw->sln_head) अणु
		sln = (काष्ठा csio_lnode *) पंचांगp1;

		/* Match sibling lnode */
		अगर (!स_भेद(csio_ln_wwpn(sln), wwpn, 8))
			वापस sln;

		अगर (list_empty(&sln->cln_head))
			जारी;

		/* Traverse children lnodes */
		list_क्रम_each(पंचांगp2, &sln->cln_head) अणु
			cln = (काष्ठा csio_lnode *) पंचांगp2;

			अगर (!स_भेद(csio_ln_wwpn(cln), wwpn, 8))
				वापस cln;
		पूर्ण
	पूर्ण
	वापस शून्य;
पूर्ण

/* FDMI */
अटल व्योम
csio_fill_ct_iu(व्योम *buf, uपूर्णांक8_t type, uपूर्णांक8_t sub_type, uपूर्णांक16_t op)
अणु
	काष्ठा fc_ct_hdr *cmd = (काष्ठा fc_ct_hdr *)buf;
	cmd->ct_rev = FC_CT_REV;
	cmd->ct_fs_type = type;
	cmd->ct_fs_subtype = sub_type;
	cmd->ct_cmd = htons(op);
पूर्ण

अटल पूर्णांक
csio_hostname(uपूर्णांक8_t *buf, माप_प्रकार buf_len)
अणु
	अगर (snम_लिखो(buf, buf_len, "%s", init_utsname()->nodename) > 0)
		वापस 0;
	वापस -1;
पूर्ण

अटल पूर्णांक
csio_osname(uपूर्णांक8_t *buf, माप_प्रकार buf_len)
अणु
	अगर (snम_लिखो(buf, buf_len, "%s %s %s",
		     init_utsname()->sysname,
		     init_utsname()->release,
		     init_utsname()->version) > 0)
		वापस 0;

	वापस -1;
पूर्ण

अटल अंतरभूत व्योम
csio_append_attrib(uपूर्णांक8_t **ptr, uपूर्णांक16_t type, व्योम *val, माप_प्रकार val_len)
अणु
	uपूर्णांक16_t len;
	काष्ठा fc_fdmi_attr_entry *ae = (काष्ठा fc_fdmi_attr_entry *)*ptr;

	अगर (WARN_ON(val_len > U16_MAX))
		वापस;

	len = val_len;

	ae->type = htons(type);
	len += 4;		/* includes attribute type and length */
	len = (len + 3) & ~3;	/* should be multiple of 4 bytes */
	ae->len = htons(len);
	स_नकल(ae->value, val, val_len);
	अगर (len > val_len)
		स_रखो(ae->value + val_len, 0, len - val_len);
	*ptr += len;
पूर्ण

/*
 * csio_ln_fdmi_करोne - FDMI रेजिस्टरation completion
 * @hw: HW context
 * @fdmi_req: fdmi request
 */
अटल व्योम
csio_ln_fdmi_करोne(काष्ठा csio_hw *hw, काष्ठा csio_ioreq *fdmi_req)
अणु
	व्योम *cmd;
	काष्ठा csio_lnode *ln = fdmi_req->lnode;

	अगर (fdmi_req->wr_status != FW_SUCCESS) अणु
		csio_ln_dbg(ln, "WR error:%x in processing fdmi rpa cmd\n",
			    fdmi_req->wr_status);
		CSIO_INC_STATS(ln, n_fdmi_err);
	पूर्ण

	cmd = fdmi_req->dma_buf.vaddr;
	अगर (ntohs(csio_ct_rsp(cmd)) != FC_FS_ACC) अणु
		csio_ln_dbg(ln, "fdmi rpa cmd rejected reason %x expl %x\n",
			    csio_ct_reason(cmd), csio_ct_expl(cmd));
	पूर्ण
पूर्ण

/*
 * csio_ln_fdmi_rhba_cbfn - RHBA completion
 * @hw: HW context
 * @fdmi_req: fdmi request
 */
अटल व्योम
csio_ln_fdmi_rhba_cbfn(काष्ठा csio_hw *hw, काष्ठा csio_ioreq *fdmi_req)
अणु
	व्योम *cmd;
	uपूर्णांक8_t *pld;
	uपूर्णांक32_t len = 0;
	__be32 val;
	__be16 mfs;
	uपूर्णांक32_t numattrs = 0;
	काष्ठा csio_lnode *ln = fdmi_req->lnode;
	काष्ठा fs_fdmi_attrs *attrib_blk;
	काष्ठा fc_fdmi_port_name *port_name;
	uपूर्णांक8_t buf[64];
	uपूर्णांक8_t *fc4_type;
	अचिन्हित दीर्घ flags;

	अगर (fdmi_req->wr_status != FW_SUCCESS) अणु
		csio_ln_dbg(ln, "WR error:%x in processing fdmi rhba cmd\n",
			    fdmi_req->wr_status);
		CSIO_INC_STATS(ln, n_fdmi_err);
	पूर्ण

	cmd = fdmi_req->dma_buf.vaddr;
	अगर (ntohs(csio_ct_rsp(cmd)) != FC_FS_ACC) अणु
		csio_ln_dbg(ln, "fdmi rhba cmd rejected reason %x expl %x\n",
			    csio_ct_reason(cmd), csio_ct_expl(cmd));
	पूर्ण

	अगर (!csio_is_rnode_पढ़ोy(fdmi_req->rnode)) अणु
		CSIO_INC_STATS(ln, n_fdmi_err);
		वापस;
	पूर्ण

	/* Prepare CT hdr क्रम RPA cmd */
	स_रखो(cmd, 0, FC_CT_HDR_LEN);
	csio_fill_ct_iu(cmd, FC_FST_MGMT, FC_FDMI_SUBTYPE, FC_FDMI_RPA);

	/* Prepare RPA payload */
	pld = (uपूर्णांक8_t *)csio_ct_get_pld(cmd);
	port_name = (काष्ठा fc_fdmi_port_name *)pld;
	स_नकल(&port_name->portname, csio_ln_wwpn(ln), 8);
	pld += माप(*port_name);

	/* Start appending Port attributes */
	attrib_blk = (काष्ठा fs_fdmi_attrs *)pld;
	attrib_blk->numattrs = 0;
	len += माप(attrib_blk->numattrs);
	pld += माप(attrib_blk->numattrs);

	fc4_type = &buf[0];
	स_रखो(fc4_type, 0, FC_FDMI_PORT_ATTR_FC4TYPES_LEN);
	fc4_type[2] = 1;
	fc4_type[7] = 1;
	csio_append_attrib(&pld, FC_FDMI_PORT_ATTR_FC4TYPES,
			   fc4_type, FC_FDMI_PORT_ATTR_FC4TYPES_LEN);
	numattrs++;
	val = htonl(FC_PORTSPEED_1GBIT | FC_PORTSPEED_10GBIT);
	csio_append_attrib(&pld, FC_FDMI_PORT_ATTR_SUPPORTEDSPEED,
			   &val,
			   FC_FDMI_PORT_ATTR_SUPPORTEDSPEED_LEN);
	numattrs++;

	अगर (hw->pport[ln->portid].link_speed == FW_PORT_CAP_SPEED_1G)
		val = htonl(FC_PORTSPEED_1GBIT);
	अन्यथा अगर (hw->pport[ln->portid].link_speed == FW_PORT_CAP_SPEED_10G)
		val = htonl(FC_PORTSPEED_10GBIT);
	अन्यथा अगर (hw->pport[ln->portid].link_speed == FW_PORT_CAP32_SPEED_25G)
		val = htonl(FC_PORTSPEED_25GBIT);
	अन्यथा अगर (hw->pport[ln->portid].link_speed == FW_PORT_CAP32_SPEED_40G)
		val = htonl(FC_PORTSPEED_40GBIT);
	अन्यथा अगर (hw->pport[ln->portid].link_speed == FW_PORT_CAP32_SPEED_50G)
		val = htonl(FC_PORTSPEED_50GBIT);
	अन्यथा अगर (hw->pport[ln->portid].link_speed == FW_PORT_CAP32_SPEED_100G)
		val = htonl(FC_PORTSPEED_100GBIT);
	अन्यथा
		val = htonl(CSIO_HBA_PORTSPEED_UNKNOWN);
	csio_append_attrib(&pld, FC_FDMI_PORT_ATTR_CURRENTPORTSPEED,
			   &val, FC_FDMI_PORT_ATTR_CURRENTPORTSPEED_LEN);
	numattrs++;

	mfs = ln->ln_sparm.csp.sp_bb_data;
	csio_append_attrib(&pld, FC_FDMI_PORT_ATTR_MAXFRAMESIZE,
			   &mfs, माप(mfs));
	numattrs++;

	म_नकल(buf, "csiostor");
	csio_append_attrib(&pld, FC_FDMI_PORT_ATTR_OSDEVICENAME, buf,
			   म_माप(buf));
	numattrs++;

	अगर (!csio_hostname(buf, माप(buf))) अणु
		csio_append_attrib(&pld, FC_FDMI_PORT_ATTR_HOSTNAME,
				   buf, म_माप(buf));
		numattrs++;
	पूर्ण
	attrib_blk->numattrs = htonl(numattrs);
	len = (uपूर्णांक32_t)(pld - (uपूर्णांक8_t *)cmd);

	/* Submit FDMI RPA request */
	spin_lock_irqsave(&hw->lock, flags);
	अगर (csio_ln_mgmt_submit_req(fdmi_req, csio_ln_fdmi_करोne,
				FCOE_CT, &fdmi_req->dma_buf, len)) अणु
		CSIO_INC_STATS(ln, n_fdmi_err);
		csio_ln_dbg(ln, "Failed to issue fdmi rpa req\n");
	पूर्ण
	spin_unlock_irqrestore(&hw->lock, flags);
पूर्ण

/*
 * csio_ln_fdmi_dprt_cbfn - DPRT completion
 * @hw: HW context
 * @fdmi_req: fdmi request
 */
अटल व्योम
csio_ln_fdmi_dprt_cbfn(काष्ठा csio_hw *hw, काष्ठा csio_ioreq *fdmi_req)
अणु
	व्योम *cmd;
	uपूर्णांक8_t *pld;
	uपूर्णांक32_t len = 0;
	uपूर्णांक32_t numattrs = 0;
	__be32  maxpayload = htonl(65536);
	काष्ठा fc_fdmi_hba_identअगरier *hbaid;
	काष्ठा csio_lnode *ln = fdmi_req->lnode;
	काष्ठा fc_fdmi_rpl *reg_pl;
	काष्ठा fs_fdmi_attrs *attrib_blk;
	uपूर्णांक8_t buf[64];
	अचिन्हित दीर्घ flags;

	अगर (fdmi_req->wr_status != FW_SUCCESS) अणु
		csio_ln_dbg(ln, "WR error:%x in processing fdmi dprt cmd\n",
			    fdmi_req->wr_status);
		CSIO_INC_STATS(ln, n_fdmi_err);
	पूर्ण

	अगर (!csio_is_rnode_पढ़ोy(fdmi_req->rnode)) अणु
		CSIO_INC_STATS(ln, n_fdmi_err);
		वापस;
	पूर्ण
	cmd = fdmi_req->dma_buf.vaddr;
	अगर (ntohs(csio_ct_rsp(cmd)) != FC_FS_ACC) अणु
		csio_ln_dbg(ln, "fdmi dprt cmd rejected reason %x expl %x\n",
			    csio_ct_reason(cmd), csio_ct_expl(cmd));
	पूर्ण

	/* Prepare CT hdr क्रम RHBA cmd */
	स_रखो(cmd, 0, FC_CT_HDR_LEN);
	csio_fill_ct_iu(cmd, FC_FST_MGMT, FC_FDMI_SUBTYPE, FC_FDMI_RHBA);
	len = FC_CT_HDR_LEN;

	/* Prepare RHBA payload */
	pld = (uपूर्णांक8_t *)csio_ct_get_pld(cmd);
	hbaid = (काष्ठा fc_fdmi_hba_identअगरier *)pld;
	स_नकल(&hbaid->id, csio_ln_wwpn(ln), 8); /* HBA identअगरer */
	pld += माप(*hbaid);

	/* Register one port per hba */
	reg_pl = (काष्ठा fc_fdmi_rpl *)pld;
	reg_pl->numport = htonl(1);
	स_नकल(&reg_pl->port[0].portname, csio_ln_wwpn(ln), 8);
	pld += माप(*reg_pl);

	/* Start appending HBA attributes hba */
	attrib_blk = (काष्ठा fs_fdmi_attrs *)pld;
	attrib_blk->numattrs = 0;
	len += माप(attrib_blk->numattrs);
	pld += माप(attrib_blk->numattrs);

	csio_append_attrib(&pld, FC_FDMI_HBA_ATTR_NODENAME, csio_ln_wwnn(ln),
			   FC_FDMI_HBA_ATTR_NODENAME_LEN);
	numattrs++;

	स_रखो(buf, 0, माप(buf));

	म_नकल(buf, "Chelsio Communications");
	csio_append_attrib(&pld, FC_FDMI_HBA_ATTR_MANUFACTURER, buf,
			   म_माप(buf));
	numattrs++;
	csio_append_attrib(&pld, FC_FDMI_HBA_ATTR_SERIALNUMBER,
			   hw->vpd.sn, माप(hw->vpd.sn));
	numattrs++;
	csio_append_attrib(&pld, FC_FDMI_HBA_ATTR_MODEL, hw->vpd.id,
			   माप(hw->vpd.id));
	numattrs++;
	csio_append_attrib(&pld, FC_FDMI_HBA_ATTR_MODELDESCRIPTION,
			   hw->model_desc, म_माप(hw->model_desc));
	numattrs++;
	csio_append_attrib(&pld, FC_FDMI_HBA_ATTR_HARDWAREVERSION,
			   hw->hw_ver, माप(hw->hw_ver));
	numattrs++;
	csio_append_attrib(&pld, FC_FDMI_HBA_ATTR_FIRMWAREVERSION,
			   hw->fwrev_str, म_माप(hw->fwrev_str));
	numattrs++;

	अगर (!csio_osname(buf, माप(buf))) अणु
		csio_append_attrib(&pld, FC_FDMI_HBA_ATTR_OSNAMEVERSION,
				   buf, म_माप(buf));
		numattrs++;
	पूर्ण

	csio_append_attrib(&pld, FC_FDMI_HBA_ATTR_MAXCTPAYLOAD,
			   &maxpayload, FC_FDMI_HBA_ATTR_MAXCTPAYLOAD_LEN);
	len = (uपूर्णांक32_t)(pld - (uपूर्णांक8_t *)cmd);
	numattrs++;
	attrib_blk->numattrs = htonl(numattrs);

	/* Submit FDMI RHBA request */
	spin_lock_irqsave(&hw->lock, flags);
	अगर (csio_ln_mgmt_submit_req(fdmi_req, csio_ln_fdmi_rhba_cbfn,
				FCOE_CT, &fdmi_req->dma_buf, len)) अणु
		CSIO_INC_STATS(ln, n_fdmi_err);
		csio_ln_dbg(ln, "Failed to issue fdmi rhba req\n");
	पूर्ण
	spin_unlock_irqrestore(&hw->lock, flags);
पूर्ण

/*
 * csio_ln_fdmi_dhba_cbfn - DHBA completion
 * @hw: HW context
 * @fdmi_req: fdmi request
 */
अटल व्योम
csio_ln_fdmi_dhba_cbfn(काष्ठा csio_hw *hw, काष्ठा csio_ioreq *fdmi_req)
अणु
	काष्ठा csio_lnode *ln = fdmi_req->lnode;
	व्योम *cmd;
	काष्ठा fc_fdmi_port_name *port_name;
	uपूर्णांक32_t len;
	अचिन्हित दीर्घ flags;

	अगर (fdmi_req->wr_status != FW_SUCCESS) अणु
		csio_ln_dbg(ln, "WR error:%x in processing fdmi dhba cmd\n",
			    fdmi_req->wr_status);
		CSIO_INC_STATS(ln, n_fdmi_err);
	पूर्ण

	अगर (!csio_is_rnode_पढ़ोy(fdmi_req->rnode)) अणु
		CSIO_INC_STATS(ln, n_fdmi_err);
		वापस;
	पूर्ण
	cmd = fdmi_req->dma_buf.vaddr;
	अगर (ntohs(csio_ct_rsp(cmd)) != FC_FS_ACC) अणु
		csio_ln_dbg(ln, "fdmi dhba cmd rejected reason %x expl %x\n",
			    csio_ct_reason(cmd), csio_ct_expl(cmd));
	पूर्ण

	/* Send FDMI cmd to de-रेजिस्टर any Port attributes अगर रेजिस्टरed
	 * beक्रमe
	 */

	/* Prepare FDMI DPRT cmd */
	स_रखो(cmd, 0, FC_CT_HDR_LEN);
	csio_fill_ct_iu(cmd, FC_FST_MGMT, FC_FDMI_SUBTYPE, FC_FDMI_DPRT);
	len = FC_CT_HDR_LEN;
	port_name = (काष्ठा fc_fdmi_port_name *)csio_ct_get_pld(cmd);
	स_नकल(&port_name->portname, csio_ln_wwpn(ln), 8);
	len += माप(*port_name);

	/* Submit FDMI request */
	spin_lock_irqsave(&hw->lock, flags);
	अगर (csio_ln_mgmt_submit_req(fdmi_req, csio_ln_fdmi_dprt_cbfn,
				FCOE_CT, &fdmi_req->dma_buf, len)) अणु
		CSIO_INC_STATS(ln, n_fdmi_err);
		csio_ln_dbg(ln, "Failed to issue fdmi dprt req\n");
	पूर्ण
	spin_unlock_irqrestore(&hw->lock, flags);
पूर्ण

/**
 * csio_ln_fdmi_start - Start an FDMI request.
 * @ln:		lnode
 * @context:	session context
 *
 * Issued with lock held.
 */
पूर्णांक
csio_ln_fdmi_start(काष्ठा csio_lnode *ln, व्योम *context)
अणु
	काष्ठा csio_ioreq *fdmi_req;
	काष्ठा csio_rnode *fdmi_rn = (काष्ठा csio_rnode *)context;
	व्योम *cmd;
	काष्ठा fc_fdmi_hba_identअगरier *hbaid;
	uपूर्णांक32_t len;

	अगर (!(ln->flags & CSIO_LNF_FDMI_ENABLE))
		वापस -EPROTONOSUPPORT;

	अगर (!csio_is_rnode_पढ़ोy(fdmi_rn))
		CSIO_INC_STATS(ln, n_fdmi_err);

	/* Send FDMI cmd to de-रेजिस्टर any HBA attributes अगर रेजिस्टरed
	 * beक्रमe
	 */

	fdmi_req = ln->mgmt_req;
	fdmi_req->lnode = ln;
	fdmi_req->rnode = fdmi_rn;

	/* Prepare FDMI DHBA cmd */
	cmd = fdmi_req->dma_buf.vaddr;
	स_रखो(cmd, 0, FC_CT_HDR_LEN);
	csio_fill_ct_iu(cmd, FC_FST_MGMT, FC_FDMI_SUBTYPE, FC_FDMI_DHBA);
	len = FC_CT_HDR_LEN;

	hbaid = (काष्ठा fc_fdmi_hba_identअगरier *)csio_ct_get_pld(cmd);
	स_नकल(&hbaid->id, csio_ln_wwpn(ln), 8);
	len += माप(*hbaid);

	/* Submit FDMI request */
	अगर (csio_ln_mgmt_submit_req(fdmi_req, csio_ln_fdmi_dhba_cbfn,
					FCOE_CT, &fdmi_req->dma_buf, len)) अणु
		CSIO_INC_STATS(ln, n_fdmi_err);
		csio_ln_dbg(ln, "Failed to issue fdmi dhba req\n");
	पूर्ण

	वापस 0;
पूर्ण

/*
 * csio_ln_vnp_पढ़ो_cbfn - vnp पढ़ो completion handler.
 * @hw: HW lnode
 * @cbfn: Completion handler.
 *
 * Reads vnp response and updates ln parameters.
 */
अटल व्योम
csio_ln_vnp_पढ़ो_cbfn(काष्ठा csio_hw *hw, काष्ठा csio_mb *mbp)
अणु
	काष्ठा csio_lnode *ln = ((काष्ठा csio_lnode *)mbp->priv);
	काष्ठा fw_fcoe_vnp_cmd *rsp = (काष्ठा fw_fcoe_vnp_cmd *)(mbp->mb);
	काष्ठा fc_els_csp *csp;
	काष्ठा fc_els_cssp *clsp;
	क्रमागत fw_retval retval;
	__be32 nport_id;

	retval = FW_CMD_RETVAL_G(ntohl(rsp->alloc_to_len16));
	अगर (retval != FW_SUCCESS) अणु
		csio_err(hw, "FCOE VNP read cmd returned error:0x%x\n", retval);
		mempool_मुक्त(mbp, hw->mb_mempool);
		वापस;
	पूर्ण

	spin_lock_irq(&hw->lock);

	स_नकल(ln->mac, rsp->vnport_mac, माप(ln->mac));
	स_नकल(&nport_id, &rsp->vnport_mac[3], माप(uपूर्णांक8_t)*3);
	ln->nport_id = ntohl(nport_id);
	ln->nport_id = ln->nport_id >> 8;

	/* Update WWNs */
	/*
	 * This may look like a duplication of what csio_fcoe_enable_link()
	 * करोes, but is असलolutely necessary अगर the vnpi changes between
	 * a FCOE LINK UP and FCOE LINK DOWN.
	 */
	स_नकल(csio_ln_wwnn(ln), rsp->vnport_wwnn, 8);
	स_नकल(csio_ln_wwpn(ln), rsp->vnport_wwpn, 8);

	/* Copy common sparam */
	csp = (काष्ठा fc_els_csp *)rsp->cmn_srv_parms;
	ln->ln_sparm.csp.sp_hi_ver = csp->sp_hi_ver;
	ln->ln_sparm.csp.sp_lo_ver = csp->sp_lo_ver;
	ln->ln_sparm.csp.sp_bb_cred = csp->sp_bb_cred;
	ln->ln_sparm.csp.sp_features = csp->sp_features;
	ln->ln_sparm.csp.sp_bb_data = csp->sp_bb_data;
	ln->ln_sparm.csp.sp_r_a_tov = csp->sp_r_a_tov;
	ln->ln_sparm.csp.sp_e_d_tov = csp->sp_e_d_tov;

	/* Copy word 0 & word 1 of class sparam */
	clsp = (काष्ठा fc_els_cssp *)rsp->clsp_word_0_1;
	ln->ln_sparm.clsp[2].cp_class = clsp->cp_class;
	ln->ln_sparm.clsp[2].cp_init = clsp->cp_init;
	ln->ln_sparm.clsp[2].cp_recip = clsp->cp_recip;
	ln->ln_sparm.clsp[2].cp_rdfs = clsp->cp_rdfs;

	spin_unlock_irq(&hw->lock);

	mempool_मुक्त(mbp, hw->mb_mempool);

	/* Send an event to update local attribs */
	csio_lnode_async_event(ln, CSIO_LN_FC_ATTRIB_UPDATE);
पूर्ण

/*
 * csio_ln_vnp_पढ़ो - Read vnp params.
 * @ln: lnode
 * @cbfn: Completion handler.
 *
 * Issued with lock held.
 */
अटल पूर्णांक
csio_ln_vnp_पढ़ो(काष्ठा csio_lnode *ln,
		व्योम (*cbfn) (काष्ठा csio_hw *, काष्ठा csio_mb *))
अणु
	काष्ठा csio_hw *hw = ln->hwp;
	काष्ठा csio_mb  *mbp;

	/* Allocate Mbox request */
	mbp = mempool_alloc(hw->mb_mempool, GFP_ATOMIC);
	अगर (!mbp) अणु
		CSIO_INC_STATS(hw, n_err_nomem);
		वापस -ENOMEM;
	पूर्ण

	/* Prepare VNP Command */
	csio_fcoe_vnp_पढ़ो_init_mb(ln, mbp,
				    CSIO_MB_DEFAULT_TMO,
				    ln->fcf_flowid,
				    ln->vnp_flowid,
				    cbfn);

	/* Issue MBOX cmd */
	अगर (csio_mb_issue(hw, mbp)) अणु
		csio_err(hw, "Failed to issue mbox FCoE VNP command\n");
		mempool_मुक्त(mbp, hw->mb_mempool);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * csio_fcoe_enable_link - Enable fcoe link.
 * @ln: lnode
 * @enable: enable/disable
 * Issued with lock held.
 * Issues mbox cmd to bring up FCOE link on port associated with given ln.
 */
अटल पूर्णांक
csio_fcoe_enable_link(काष्ठा csio_lnode *ln, bool enable)
अणु
	काष्ठा csio_hw *hw = ln->hwp;
	काष्ठा csio_mb  *mbp;
	क्रमागत fw_retval retval;
	uपूर्णांक8_t portid;
	uपूर्णांक8_t sub_op;
	काष्ठा fw_fcoe_link_cmd *lcmd;
	पूर्णांक i;

	mbp = mempool_alloc(hw->mb_mempool, GFP_ATOMIC);
	अगर (!mbp) अणु
		CSIO_INC_STATS(hw, n_err_nomem);
		वापस -ENOMEM;
	पूर्ण

	portid = ln->portid;
	sub_op = enable ? FCOE_LINK_UP : FCOE_LINK_DOWN;

	csio_dbg(hw, "bringing FCOE LINK %s on Port:%d\n",
		 sub_op ? "UP" : "DOWN", portid);

	csio_ग_लिखो_fcoe_link_cond_init_mb(ln, mbp, CSIO_MB_DEFAULT_TMO,
					  portid, sub_op, 0, 0, 0, शून्य);

	अगर (csio_mb_issue(hw, mbp)) अणु
		csio_err(hw, "failed to issue FCOE LINK cmd on port[%d]\n",
			portid);
		mempool_मुक्त(mbp, hw->mb_mempool);
		वापस -EINVAL;
	पूर्ण

	retval = csio_mb_fw_retval(mbp);
	अगर (retval != FW_SUCCESS) अणु
		csio_err(hw,
			 "FCOE LINK %s cmd on port[%d] failed with "
			 "ret:x%x\n", sub_op ? "UP" : "DOWN", portid, retval);
		mempool_मुक्त(mbp, hw->mb_mempool);
		वापस -EINVAL;
	पूर्ण

	अगर (!enable)
		जाओ out;

	lcmd = (काष्ठा fw_fcoe_link_cmd *)mbp->mb;

	स_नकल(csio_ln_wwnn(ln), lcmd->vnport_wwnn, 8);
	स_नकल(csio_ln_wwpn(ln), lcmd->vnport_wwpn, 8);

	क्रम (i = 0; i < CSIO_MAX_PPORTS; i++)
		अगर (hw->pport[i].portid == portid)
			स_नकल(hw->pport[i].mac, lcmd->phy_mac, 6);

out:
	mempool_मुक्त(mbp, hw->mb_mempool);
	वापस 0;
पूर्ण

/*
 * csio_ln_पढ़ो_fcf_cbfn - Read fcf parameters
 * @ln: lnode
 *
 * पढ़ो fcf response and Update ln fcf inक्रमmation.
 */
अटल व्योम
csio_ln_पढ़ो_fcf_cbfn(काष्ठा csio_hw *hw, काष्ठा csio_mb *mbp)
अणु
	काष्ठा csio_lnode *ln = (काष्ठा csio_lnode *)mbp->priv;
	काष्ठा csio_fcf_info	*fcf_info;
	काष्ठा fw_fcoe_fcf_cmd *rsp =
				(काष्ठा fw_fcoe_fcf_cmd *)(mbp->mb);
	क्रमागत fw_retval retval;

	retval = FW_CMD_RETVAL_G(ntohl(rsp->retval_len16));
	अगर (retval != FW_SUCCESS) अणु
		csio_ln_err(ln, "FCOE FCF cmd failed with ret x%x\n",
				retval);
		mempool_मुक्त(mbp, hw->mb_mempool);
		वापस;
	पूर्ण

	spin_lock_irq(&hw->lock);
	fcf_info = ln->fcfinfo;
	fcf_info->priority = FW_FCOE_FCF_CMD_PRIORITY_GET(
					ntohs(rsp->priority_pkd));
	fcf_info->vf_id = ntohs(rsp->vf_id);
	fcf_info->vlan_id = rsp->vlan_id;
	fcf_info->max_fcoe_size = ntohs(rsp->max_fcoe_size);
	fcf_info->fka_adv = be32_to_cpu(rsp->fka_adv);
	fcf_info->fcfi = FW_FCOE_FCF_CMD_FCFI_GET(ntohl(rsp->op_to_fcfi));
	fcf_info->fpma = FW_FCOE_FCF_CMD_FPMA_GET(rsp->fpma_to_portid);
	fcf_info->spma = FW_FCOE_FCF_CMD_SPMA_GET(rsp->fpma_to_portid);
	fcf_info->login = FW_FCOE_FCF_CMD_LOGIN_GET(rsp->fpma_to_portid);
	fcf_info->portid = FW_FCOE_FCF_CMD_PORTID_GET(rsp->fpma_to_portid);
	स_नकल(fcf_info->fc_map, rsp->fc_map, माप(fcf_info->fc_map));
	स_नकल(fcf_info->mac, rsp->mac, माप(fcf_info->mac));
	स_नकल(fcf_info->name_id, rsp->name_id, माप(fcf_info->name_id));
	स_नकल(fcf_info->fabric, rsp->fabric, माप(fcf_info->fabric));
	स_नकल(fcf_info->spma_mac, rsp->spma_mac, माप(fcf_info->spma_mac));

	spin_unlock_irq(&hw->lock);

	mempool_मुक्त(mbp, hw->mb_mempool);
पूर्ण

/*
 * csio_ln_पढ़ो_fcf_entry - Read fcf entry.
 * @ln: lnode
 * @cbfn: Completion handler.
 *
 * Issued with lock held.
 */
अटल पूर्णांक
csio_ln_पढ़ो_fcf_entry(काष्ठा csio_lnode *ln,
			व्योम (*cbfn) (काष्ठा csio_hw *, काष्ठा csio_mb *))
अणु
	काष्ठा csio_hw *hw = ln->hwp;
	काष्ठा csio_mb  *mbp;

	mbp = mempool_alloc(hw->mb_mempool, GFP_ATOMIC);
	अगर (!mbp) अणु
		CSIO_INC_STATS(hw, n_err_nomem);
		वापस -ENOMEM;
	पूर्ण

	/* Get FCoE FCF inक्रमmation */
	csio_fcoe_पढ़ो_fcf_init_mb(ln, mbp, CSIO_MB_DEFAULT_TMO,
				      ln->portid, ln->fcf_flowid, cbfn);

	अगर (csio_mb_issue(hw, mbp)) अणु
		csio_err(hw, "failed to issue FCOE FCF cmd\n");
		mempool_मुक्त(mbp, hw->mb_mempool);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * csio_handle_link_up - Logical Linkup event.
 * @hw - HW module.
 * @portid - Physical port number
 * @fcfi - FCF index.
 * @vnpi - VNP index.
 * Returns - none.
 *
 * This event is received from FW, when भव link is established between
 * Physical port[ENode] and FCF. If its new vnpi, then local node object is
 * created on this FCF and set to [ONLINE] state.
 * Lnode रुकोs क्रम FW_RDEV_CMD event to be received indicating that
 * Fabric login is completed and lnode moves to [READY] state.
 *
 * This called with hw lock held
 */
अटल व्योम
csio_handle_link_up(काष्ठा csio_hw *hw, uपूर्णांक8_t portid, uपूर्णांक32_t fcfi,
		    uपूर्णांक32_t vnpi)
अणु
	काष्ठा csio_lnode *ln = शून्य;

	/* Lookup lnode based on vnpi */
	ln = csio_ln_lookup_by_vnpi(hw, vnpi);
	अगर (!ln) अणु
		/* Pick lnode based on portid */
		ln = csio_ln_lookup_by_portid(hw, portid);
		अगर (!ln) अणु
			csio_err(hw, "failed to lookup fcoe lnode on port:%d\n",
				portid);
			CSIO_DB_ASSERT(0);
			वापस;
		पूर्ण

		/* Check अगर lnode has valid vnp flowid */
		अगर (ln->vnp_flowid != CSIO_INVALID_IDX) अणु
			/* New VN-Port */
			spin_unlock_irq(&hw->lock);
			csio_lnode_alloc(hw);
			spin_lock_irq(&hw->lock);
			अगर (!ln) अणु
				csio_err(hw,
					 "failed to allocate fcoe lnode"
					 "for port:%d vnpi:x%x\n",
					 portid, vnpi);
				CSIO_DB_ASSERT(0);
				वापस;
			पूर्ण
			ln->portid = portid;
		पूर्ण
		ln->vnp_flowid = vnpi;
		ln->dev_num &= ~0xFFFF;
		ln->dev_num |= vnpi;
	पूर्ण

	/*Initialize fcfi */
	ln->fcf_flowid = fcfi;

	csio_info(hw, "Port:%d - FCOE LINK UP\n", portid);

	CSIO_INC_STATS(ln, n_link_up);

	/* Send LINKUP event to SM */
	csio_post_event(&ln->sm, CSIO_LNE_LINKUP);
पूर्ण

/*
 * csio_post_event_rns
 * @ln - FCOE lnode
 * @evt - Given rnode event
 * Returns - none
 *
 * Posts given rnode event to all FCOE rnodes connected with given Lnode.
 * This routine is invoked when lnode receives LINK_DOWN/DOWN_LINK/CLOSE
 * event.
 *
 * This called with hw lock held
 */
अटल व्योम
csio_post_event_rns(काष्ठा csio_lnode *ln, क्रमागत csio_rn_ev evt)
अणु
	काष्ठा csio_rnode *rnhead = (काष्ठा csio_rnode *) &ln->rnhead;
	काष्ठा list_head *पंचांगp, *next;
	काष्ठा csio_rnode *rn;

	list_क्रम_each_safe(पंचांगp, next, &rnhead->sm.sm_list) अणु
		rn = (काष्ठा csio_rnode *) पंचांगp;
		csio_post_event(&rn->sm, evt);
	पूर्ण
पूर्ण

/*
 * csio_cleanup_rns
 * @ln - FCOE lnode
 * Returns - none
 *
 * Frees all FCOE rnodes connected with given Lnode.
 *
 * This called with hw lock held
 */
अटल व्योम
csio_cleanup_rns(काष्ठा csio_lnode *ln)
अणु
	काष्ठा csio_rnode *rnhead = (काष्ठा csio_rnode *) &ln->rnhead;
	काष्ठा list_head *पंचांगp, *next_rn;
	काष्ठा csio_rnode *rn;

	list_क्रम_each_safe(पंचांगp, next_rn, &rnhead->sm.sm_list) अणु
		rn = (काष्ठा csio_rnode *) पंचांगp;
		csio_put_rnode(ln, rn);
	पूर्ण

पूर्ण

/*
 * csio_post_event_lns
 * @ln - FCOE lnode
 * @evt - Given lnode event
 * Returns - none
 *
 * Posts given lnode event to all FCOE lnodes connected with given Lnode.
 * This routine is invoked when lnode receives LINK_DOWN/DOWN_LINK/CLOSE
 * event.
 *
 * This called with hw lock held
 */
अटल व्योम
csio_post_event_lns(काष्ठा csio_lnode *ln, क्रमागत csio_ln_ev evt)
अणु
	काष्ठा list_head *पंचांगp;
	काष्ठा csio_lnode *cln, *sln;

	/* If NPIV lnode, send evt only to that and वापस */
	अगर (csio_is_npiv_ln(ln)) अणु
		csio_post_event(&ln->sm, evt);
		वापस;
	पूर्ण

	sln = ln;
	/* Traverse children lnodes list and send evt */
	list_क्रम_each(पंचांगp, &sln->cln_head) अणु
		cln = (काष्ठा csio_lnode *) पंचांगp;
		csio_post_event(&cln->sm, evt);
	पूर्ण

	/* Send evt to parent lnode */
	csio_post_event(&ln->sm, evt);
पूर्ण

/*
 * csio_ln_करोwn - Lcoal nport is करोwn
 * @ln - FCOE Lnode
 * Returns - none
 *
 * Sends LINK_DOWN events to Lnode and its associated NPIVs lnodes.
 *
 * This called with hw lock held
 */
अटल व्योम
csio_ln_करोwn(काष्ठा csio_lnode *ln)
अणु
	csio_post_event_lns(ln, CSIO_LNE_LINK_DOWN);
पूर्ण

/*
 * csio_handle_link_करोwn - Logical Linkकरोwn event.
 * @hw - HW module.
 * @portid - Physical port number
 * @fcfi - FCF index.
 * @vnpi - VNP index.
 * Returns - none
 *
 * This event is received from FW, when भव link goes करोwn between
 * Physical port[ENode] and FCF. Lnode and its associated NPIVs lnode hosted on
 * this vnpi[VN-Port] will be de-instantiated.
 *
 * This called with hw lock held
 */
अटल व्योम
csio_handle_link_करोwn(काष्ठा csio_hw *hw, uपूर्णांक8_t portid, uपूर्णांक32_t fcfi,
		      uपूर्णांक32_t vnpi)
अणु
	काष्ठा csio_fcf_info *fp;
	काष्ठा csio_lnode *ln;

	/* Lookup lnode based on vnpi */
	ln = csio_ln_lookup_by_vnpi(hw, vnpi);
	अगर (ln) अणु
		fp = ln->fcfinfo;
		CSIO_INC_STATS(ln, n_link_करोwn);

		/*Warn अगर linkकरोwn received अगर lnode is not in पढ़ोy state */
		अगर (!csio_is_lnode_पढ़ोy(ln)) अणु
			csio_ln_warn(ln,
				"warn: FCOE link is already in offline "
				"Ignoring Fcoe linkdown event on portid %d\n",
				 portid);
			CSIO_INC_STATS(ln, n_evt_drop);
			वापस;
		पूर्ण

		/* Verअगरy portid */
		अगर (fp->portid != portid) अणु
			csio_ln_warn(ln,
				"warn: FCOE linkdown recv with "
				"invalid port %d\n", portid);
			CSIO_INC_STATS(ln, n_evt_drop);
			वापस;
		पूर्ण

		/* verअगरy fcfi */
		अगर (ln->fcf_flowid != fcfi) अणु
			csio_ln_warn(ln,
				"warn: FCOE linkdown recv with "
				"invalid fcfi x%x\n", fcfi);
			CSIO_INC_STATS(ln, n_evt_drop);
			वापस;
		पूर्ण

		csio_info(hw, "Port:%d - FCOE LINK DOWN\n", portid);

		/* Send LINK_DOWN event to lnode s/m */
		csio_ln_करोwn(ln);

		वापस;
	पूर्ण अन्यथा अणु
		csio_warn(hw,
			  "warn: FCOE linkdown recv with invalid vnpi x%x\n",
			  vnpi);
		CSIO_INC_STATS(hw, n_evt_drop);
	पूर्ण
पूर्ण

/*
 * csio_is_lnode_पढ़ोy - Checks FCOE lnode is in पढ़ोy state.
 * @ln: Lnode module
 *
 * Returns True अगर FCOE lnode is in पढ़ोy state.
 */
पूर्णांक
csio_is_lnode_पढ़ोy(काष्ठा csio_lnode *ln)
अणु
	वापस (csio_get_state(ln) == ((csio_sm_state_t)csio_lns_पढ़ोy));
पूर्ण

/*****************************************************************************/
/* START: Lnode SM                                                           */
/*****************************************************************************/
/*
 * csio_lns_uninit - The request in uninit state.
 * @ln - FCOE lnode.
 * @evt - Event to be processed.
 *
 * Process the given lnode event which is currently in "uninit" state.
 * Invoked with HW lock held.
 * Return - none.
 */
अटल व्योम
csio_lns_uninit(काष्ठा csio_lnode *ln, क्रमागत csio_ln_ev evt)
अणु
	काष्ठा csio_hw *hw = csio_lnode_to_hw(ln);
	काष्ठा csio_lnode *rln = hw->rln;
	पूर्णांक rv;

	CSIO_INC_STATS(ln, n_evt_sm[evt]);
	चयन (evt) अणु
	हाल CSIO_LNE_LINKUP:
		csio_set_state(&ln->sm, csio_lns_online);
		/* Read FCF only क्रम physical lnode */
		अगर (csio_is_phys_ln(ln)) अणु
			rv = csio_ln_पढ़ो_fcf_entry(ln,
					csio_ln_पढ़ो_fcf_cbfn);
			अगर (rv != 0) अणु
				/* TODO: Send HW RESET event */
				CSIO_INC_STATS(ln, n_err);
				अवरोध;
			पूर्ण

			/* Add FCF record */
			list_add_tail(&ln->fcfinfo->list, &rln->fcf_lsthead);
		पूर्ण

		rv = csio_ln_vnp_पढ़ो(ln, csio_ln_vnp_पढ़ो_cbfn);
		अगर (rv != 0) अणु
			/* TODO: Send HW RESET event */
			CSIO_INC_STATS(ln, n_err);
		पूर्ण
		अवरोध;

	हाल CSIO_LNE_DOWN_LINK:
		अवरोध;

	शेष:
		csio_ln_dbg(ln,
			    "unexp ln event %d recv from did:x%x in "
			    "ln state[uninit].\n", evt, ln->nport_id);
		CSIO_INC_STATS(ln, n_evt_unexp);
		अवरोध;
	पूर्ण /* चयन event */
पूर्ण

/*
 * csio_lns_online - The request in online state.
 * @ln - FCOE lnode.
 * @evt - Event to be processed.
 *
 * Process the given lnode event which is currently in "online" state.
 * Invoked with HW lock held.
 * Return - none.
 */
अटल व्योम
csio_lns_online(काष्ठा csio_lnode *ln, क्रमागत csio_ln_ev evt)
अणु
	काष्ठा csio_hw *hw = csio_lnode_to_hw(ln);

	CSIO_INC_STATS(ln, n_evt_sm[evt]);
	चयन (evt) अणु
	हाल CSIO_LNE_LINKUP:
		csio_ln_warn(ln,
			     "warn: FCOE link is up already "
			     "Ignoring linkup on port:%d\n", ln->portid);
		CSIO_INC_STATS(ln, n_evt_drop);
		अवरोध;

	हाल CSIO_LNE_FAB_INIT_DONE:
		csio_set_state(&ln->sm, csio_lns_पढ़ोy);

		spin_unlock_irq(&hw->lock);
		csio_lnode_async_event(ln, CSIO_LN_FC_LINKUP);
		spin_lock_irq(&hw->lock);

		अवरोध;

	हाल CSIO_LNE_LINK_DOWN:
	हाल CSIO_LNE_DOWN_LINK:
		csio_set_state(&ln->sm, csio_lns_uninit);
		अगर (csio_is_phys_ln(ln)) अणु
			/* Remove FCF entry */
			list_del_init(&ln->fcfinfo->list);
		पूर्ण
		अवरोध;

	शेष:
		csio_ln_dbg(ln,
			    "unexp ln event %d recv from did:x%x in "
			    "ln state[uninit].\n", evt, ln->nport_id);
		CSIO_INC_STATS(ln, n_evt_unexp);

		अवरोध;
	पूर्ण /* चयन event */
पूर्ण

/*
 * csio_lns_पढ़ोy - The request in पढ़ोy state.
 * @ln - FCOE lnode.
 * @evt - Event to be processed.
 *
 * Process the given lnode event which is currently in "ready" state.
 * Invoked with HW lock held.
 * Return - none.
 */
अटल व्योम
csio_lns_पढ़ोy(काष्ठा csio_lnode *ln, क्रमागत csio_ln_ev evt)
अणु
	काष्ठा csio_hw *hw = csio_lnode_to_hw(ln);

	CSIO_INC_STATS(ln, n_evt_sm[evt]);
	चयन (evt) अणु
	हाल CSIO_LNE_FAB_INIT_DONE:
		csio_ln_dbg(ln,
			    "ignoring event %d recv from did x%x"
			    "in ln state[ready].\n", evt, ln->nport_id);
		CSIO_INC_STATS(ln, n_evt_drop);
		अवरोध;

	हाल CSIO_LNE_LINK_DOWN:
		csio_set_state(&ln->sm, csio_lns_offline);
		csio_post_event_rns(ln, CSIO_RNFE_DOWN);

		spin_unlock_irq(&hw->lock);
		csio_lnode_async_event(ln, CSIO_LN_FC_LINKDOWN);
		spin_lock_irq(&hw->lock);

		अगर (csio_is_phys_ln(ln)) अणु
			/* Remove FCF entry */
			list_del_init(&ln->fcfinfo->list);
		पूर्ण
		अवरोध;

	हाल CSIO_LNE_DOWN_LINK:
		csio_set_state(&ln->sm, csio_lns_offline);
		csio_post_event_rns(ln, CSIO_RNFE_DOWN);

		/* Host need to issue पातs in हाल अगर FW has not वापसed
		 * WRs with status "ABORTED"
		 */
		spin_unlock_irq(&hw->lock);
		csio_lnode_async_event(ln, CSIO_LN_FC_LINKDOWN);
		spin_lock_irq(&hw->lock);

		अगर (csio_is_phys_ln(ln)) अणु
			/* Remove FCF entry */
			list_del_init(&ln->fcfinfo->list);
		पूर्ण
		अवरोध;

	हाल CSIO_LNE_CLOSE:
		csio_set_state(&ln->sm, csio_lns_uninit);
		csio_post_event_rns(ln, CSIO_RNFE_CLOSE);
		अवरोध;

	हाल CSIO_LNE_LOGO:
		csio_set_state(&ln->sm, csio_lns_offline);
		csio_post_event_rns(ln, CSIO_RNFE_DOWN);
		अवरोध;

	शेष:
		csio_ln_dbg(ln,
			    "unexp ln event %d recv from did:x%x in "
			    "ln state[uninit].\n", evt, ln->nport_id);
		CSIO_INC_STATS(ln, n_evt_unexp);
		CSIO_DB_ASSERT(0);
		अवरोध;
	पूर्ण /* चयन event */
पूर्ण

/*
 * csio_lns_offline - The request in offline state.
 * @ln - FCOE lnode.
 * @evt - Event to be processed.
 *
 * Process the given lnode event which is currently in "offline" state.
 * Invoked with HW lock held.
 * Return - none.
 */
अटल व्योम
csio_lns_offline(काष्ठा csio_lnode *ln, क्रमागत csio_ln_ev evt)
अणु
	काष्ठा csio_hw *hw = csio_lnode_to_hw(ln);
	काष्ठा csio_lnode *rln = hw->rln;
	पूर्णांक rv;

	CSIO_INC_STATS(ln, n_evt_sm[evt]);
	चयन (evt) अणु
	हाल CSIO_LNE_LINKUP:
		csio_set_state(&ln->sm, csio_lns_online);
		/* Read FCF only क्रम physical lnode */
		अगर (csio_is_phys_ln(ln)) अणु
			rv = csio_ln_पढ़ो_fcf_entry(ln,
					csio_ln_पढ़ो_fcf_cbfn);
			अगर (rv != 0) अणु
				/* TODO: Send HW RESET event */
				CSIO_INC_STATS(ln, n_err);
				अवरोध;
			पूर्ण

			/* Add FCF record */
			list_add_tail(&ln->fcfinfo->list, &rln->fcf_lsthead);
		पूर्ण

		rv = csio_ln_vnp_पढ़ो(ln, csio_ln_vnp_पढ़ो_cbfn);
		अगर (rv != 0) अणु
			/* TODO: Send HW RESET event */
			CSIO_INC_STATS(ln, n_err);
		पूर्ण
		अवरोध;

	हाल CSIO_LNE_LINK_DOWN:
	हाल CSIO_LNE_DOWN_LINK:
	हाल CSIO_LNE_LOGO:
		csio_ln_dbg(ln,
			    "ignoring event %d recv from did x%x"
			    "in ln state[offline].\n", evt, ln->nport_id);
		CSIO_INC_STATS(ln, n_evt_drop);
		अवरोध;

	हाल CSIO_LNE_CLOSE:
		csio_set_state(&ln->sm, csio_lns_uninit);
		csio_post_event_rns(ln, CSIO_RNFE_CLOSE);
		अवरोध;

	शेष:
		csio_ln_dbg(ln,
			    "unexp ln event %d recv from did:x%x in "
			    "ln state[offline]\n", evt, ln->nport_id);
		CSIO_INC_STATS(ln, n_evt_unexp);
		CSIO_DB_ASSERT(0);
		अवरोध;
	पूर्ण /* चयन event */
पूर्ण

/*****************************************************************************/
/* END: Lnode SM                                                             */
/*****************************************************************************/

अटल व्योम
csio_मुक्त_fcfinfo(काष्ठा kref *kref)
अणु
	काष्ठा csio_fcf_info *fcfinfo = container_of(kref,
						काष्ठा csio_fcf_info, kref);
	kमुक्त(fcfinfo);
पूर्ण

/* Helper routines क्रम attributes  */
/*
 * csio_lnode_state_to_str - Get current state of FCOE lnode.
 * @ln - lnode
 * @str - state of lnode.
 *
 */
व्योम
csio_lnode_state_to_str(काष्ठा csio_lnode *ln, पूर्णांक8_t *str)
अणु
	अगर (csio_get_state(ln) == ((csio_sm_state_t)csio_lns_uninit)) अणु
		म_नकल(str, "UNINIT");
		वापस;
	पूर्ण
	अगर (csio_get_state(ln) == ((csio_sm_state_t)csio_lns_पढ़ोy)) अणु
		म_नकल(str, "READY");
		वापस;
	पूर्ण
	अगर (csio_get_state(ln) == ((csio_sm_state_t)csio_lns_offline)) अणु
		म_नकल(str, "OFFLINE");
		वापस;
	पूर्ण
	म_नकल(str, "UNKNOWN");
पूर्ण /* csio_lnode_state_to_str */


पूर्णांक
csio_get_phy_port_stats(काष्ठा csio_hw *hw, uपूर्णांक8_t portid,
			काष्ठा fw_fcoe_port_stats *port_stats)
अणु
	काष्ठा csio_mb  *mbp;
	काष्ठा fw_fcoe_port_cmd_params portparams;
	क्रमागत fw_retval retval;
	पूर्णांक idx;

	mbp = mempool_alloc(hw->mb_mempool, GFP_ATOMIC);
	अगर (!mbp) अणु
		csio_err(hw, "FCoE FCF PARAMS command out of memory!\n");
		वापस -EINVAL;
	पूर्ण
	portparams.portid = portid;

	क्रम (idx = 1; idx <= 3; idx++) अणु
		portparams.idx = (idx-1)*6 + 1;
		portparams.nstats = 6;
		अगर (idx == 3)
			portparams.nstats = 4;
		csio_fcoe_पढ़ो_portparams_init_mb(hw, mbp, CSIO_MB_DEFAULT_TMO,
							&portparams, शून्य);
		अगर (csio_mb_issue(hw, mbp)) अणु
			csio_err(hw, "Issue of FCoE port params failed!\n");
			mempool_मुक्त(mbp, hw->mb_mempool);
			वापस -EINVAL;
		पूर्ण
		csio_mb_process_portparams_rsp(hw, mbp, &retval,
						&portparams, port_stats);
	पूर्ण

	mempool_मुक्त(mbp, hw->mb_mempool);
	वापस 0;
पूर्ण

/*
 * csio_ln_mgmt_wr_handler -Mgmt Work Request handler.
 * @wr - WR.
 * @len - WR len.
 * This handler is invoked when an outstanding mgmt WR is completed.
 * Its invoked in the context of FW event worker thपढ़ो क्रम every
 * mgmt event received.
 * Return - none.
 */

अटल व्योम
csio_ln_mgmt_wr_handler(काष्ठा csio_hw *hw, व्योम *wr, uपूर्णांक32_t len)
अणु
	काष्ठा csio_mgmपंचांग *mgmपंचांग = csio_hw_to_mgmपंचांग(hw);
	काष्ठा csio_ioreq *io_req = शून्य;
	काष्ठा fw_fcoe_els_ct_wr *wr_cmd;


	wr_cmd = (काष्ठा fw_fcoe_els_ct_wr *) wr;

	अगर (len < माप(काष्ठा fw_fcoe_els_ct_wr)) अणु
		csio_err(mgmपंचांग->hw,
			 "Invalid ELS CT WR length recvd, len:%x\n", len);
		mgmपंचांग->stats.n_err++;
		वापस;
	पूर्ण

	io_req = (काष्ठा csio_ioreq *) ((uपूर्णांकptr_t) wr_cmd->cookie);
	io_req->wr_status = csio_wr_status(wr_cmd);

	/* lookup ioreq exists in our active Q */
	spin_lock_irq(&hw->lock);
	अगर (csio_mgmt_req_lookup(mgmपंचांग, io_req) != 0) अणु
		csio_err(mgmपंचांग->hw,
			"Error- Invalid IO handle recv in WR. handle: %p\n",
			io_req);
		mgmपंचांग->stats.n_err++;
		spin_unlock_irq(&hw->lock);
		वापस;
	पूर्ण

	mgmपंचांग = csio_hw_to_mgmपंचांग(hw);

	/* Dequeue from active queue */
	list_del_init(&io_req->sm.sm_list);
	mgmपंचांग->stats.n_active--;
	spin_unlock_irq(&hw->lock);

	/* io_req will be मुक्तd by completion handler */
	अगर (io_req->io_cbfn)
		io_req->io_cbfn(hw, io_req);
पूर्ण

/**
 * csio_fcoe_fwevt_handler - Event handler क्रम Firmware FCoE events.
 * @hw:		HW module
 * @cpl_op:	CPL opcode
 * @cmd:	FW cmd/WR.
 *
 * Process received FCoE cmd/WR event from FW.
 */
व्योम
csio_fcoe_fwevt_handler(काष्ठा csio_hw *hw, __u8 cpl_op, __be64 *cmd)
अणु
	काष्ठा csio_lnode *ln;
	काष्ठा csio_rnode *rn;
	uपूर्णांक8_t portid, opcode = *(uपूर्णांक8_t *)cmd;
	काष्ठा fw_fcoe_link_cmd *lcmd;
	काष्ठा fw_wr_hdr *wr;
	काष्ठा fw_rdev_wr *rdev_wr;
	क्रमागत fw_fcoe_link_status lstatus;
	uपूर्णांक32_t fcfi, rdev_flowid, vnpi;
	क्रमागत csio_ln_ev evt;

	अगर (cpl_op == CPL_FW6_MSG && opcode == FW_FCOE_LINK_CMD) अणु

		lcmd = (काष्ठा fw_fcoe_link_cmd *)cmd;
		lstatus = lcmd->lstatus;
		portid = FW_FCOE_LINK_CMD_PORTID_GET(
					ntohl(lcmd->op_to_portid));
		fcfi = FW_FCOE_LINK_CMD_FCFI_GET(ntohl(lcmd->sub_opcode_fcfi));
		vnpi = FW_FCOE_LINK_CMD_VNPI_GET(ntohl(lcmd->vnpi_pkd));

		अगर (lstatus == FCOE_LINKUP) अणु

			/* HW lock here */
			spin_lock_irq(&hw->lock);
			csio_handle_link_up(hw, portid, fcfi, vnpi);
			spin_unlock_irq(&hw->lock);
			/* HW un lock here */

		पूर्ण अन्यथा अगर (lstatus == FCOE_LINKDOWN) अणु

			/* HW lock here */
			spin_lock_irq(&hw->lock);
			csio_handle_link_करोwn(hw, portid, fcfi, vnpi);
			spin_unlock_irq(&hw->lock);
			/* HW un lock here */
		पूर्ण अन्यथा अणु
			csio_warn(hw, "Unexpected FCOE LINK status:0x%x\n",
				  lcmd->lstatus);
			CSIO_INC_STATS(hw, n_cpl_unexp);
		पूर्ण
	पूर्ण अन्यथा अगर (cpl_op == CPL_FW6_PLD) अणु
		wr = (काष्ठा fw_wr_hdr *) (cmd + 4);
		अगर (FW_WR_OP_G(be32_to_cpu(wr->hi))
			== FW_RDEV_WR) अणु

			rdev_wr = (काष्ठा fw_rdev_wr *) (cmd + 4);

			rdev_flowid = FW_RDEV_WR_FLOWID_GET(
					ntohl(rdev_wr->alloc_to_len16));
			vnpi = FW_RDEV_WR_ASSOC_FLOWID_GET(
				    ntohl(rdev_wr->flags_to_assoc_flowid));

			csio_dbg(hw,
				"FW_RDEV_WR: flowid:x%x ev_cause:x%x "
				"vnpi:0x%x\n", rdev_flowid,
				rdev_wr->event_cause, vnpi);

			अगर (rdev_wr->protocol != PROT_FCOE) अणु
				csio_err(hw,
					"FW_RDEV_WR: invalid proto:x%x "
					"received with flowid:x%x\n",
					rdev_wr->protocol,
					rdev_flowid);
				CSIO_INC_STATS(hw, n_evt_drop);
				वापस;
			पूर्ण

			/* HW lock here */
			spin_lock_irq(&hw->lock);
			ln = csio_ln_lookup_by_vnpi(hw, vnpi);
			अगर (!ln) अणु
				csio_err(hw,
					"FW_DEV_WR: invalid vnpi:x%x received "
					"with flowid:x%x\n", vnpi, rdev_flowid);
				CSIO_INC_STATS(hw, n_evt_drop);
				जाओ out_pld;
			पूर्ण

			rn = csio_confirm_rnode(ln, rdev_flowid,
					&rdev_wr->u.fcoe_rdev);
			अगर (!rn) अणु
				csio_ln_dbg(ln,
					"Failed to confirm rnode "
					"for flowid:x%x\n", rdev_flowid);
				CSIO_INC_STATS(hw, n_evt_drop);
				जाओ out_pld;
			पूर्ण

			/* save previous event क्रम debugging */
			ln->prev_evt = ln->cur_evt;
			ln->cur_evt = rdev_wr->event_cause;
			CSIO_INC_STATS(ln, n_evt_fw[rdev_wr->event_cause]);

			/* Translate all the fabric events to lnode SM events */
			evt = CSIO_FWE_TO_LNE(rdev_wr->event_cause);
			अगर (evt) अणु
				csio_ln_dbg(ln,
					"Posting event to lnode event:%d "
					"cause:%d flowid:x%x\n", evt,
					rdev_wr->event_cause, rdev_flowid);
				csio_post_event(&ln->sm, evt);
			पूर्ण

			/* Hanकरोver event to rn SM here. */
			csio_rnode_fwevt_handler(rn, rdev_wr->event_cause);
out_pld:
			spin_unlock_irq(&hw->lock);
			वापस;
		पूर्ण अन्यथा अणु
			csio_warn(hw, "unexpected WR op(0x%x) recv\n",
				  FW_WR_OP_G(be32_to_cpu((wr->hi))));
			CSIO_INC_STATS(hw, n_cpl_unexp);
		पूर्ण
	पूर्ण अन्यथा अगर (cpl_op == CPL_FW6_MSG) अणु
		wr = (काष्ठा fw_wr_hdr *) (cmd);
		अगर (FW_WR_OP_G(be32_to_cpu(wr->hi)) == FW_FCOE_ELS_CT_WR) अणु
			csio_ln_mgmt_wr_handler(hw, wr,
					माप(काष्ठा fw_fcoe_els_ct_wr));
		पूर्ण अन्यथा अणु
			csio_warn(hw, "unexpected WR op(0x%x) recv\n",
				  FW_WR_OP_G(be32_to_cpu((wr->hi))));
			CSIO_INC_STATS(hw, n_cpl_unexp);
		पूर्ण
	पूर्ण अन्यथा अणु
		csio_warn(hw, "unexpected CPL op(0x%x) recv\n", opcode);
		CSIO_INC_STATS(hw, n_cpl_unexp);
	पूर्ण
पूर्ण

/**
 * csio_lnode_start - Kickstart lnode discovery.
 * @ln:		lnode
 *
 * This routine kickstarts the discovery by issuing an FCOE_LINK (up) command.
 */
पूर्णांक
csio_lnode_start(काष्ठा csio_lnode *ln)
अणु
	पूर्णांक rv = 0;
	अगर (csio_is_phys_ln(ln) && !(ln->flags & CSIO_LNF_LINK_ENABLE)) अणु
		rv = csio_fcoe_enable_link(ln, 1);
		ln->flags |= CSIO_LNF_LINK_ENABLE;
	पूर्ण

	वापस rv;
पूर्ण

/**
 * csio_lnode_stop - Stop the lnode.
 * @ln:		lnode
 *
 * This routine is invoked by HW module to stop lnode and its associated NPIV
 * lnodes.
 */
व्योम
csio_lnode_stop(काष्ठा csio_lnode *ln)
अणु
	csio_post_event_lns(ln, CSIO_LNE_DOWN_LINK);
	अगर (csio_is_phys_ln(ln) && (ln->flags & CSIO_LNF_LINK_ENABLE)) अणु
		csio_fcoe_enable_link(ln, 0);
		ln->flags &= ~CSIO_LNF_LINK_ENABLE;
	पूर्ण
	csio_ln_dbg(ln, "stopping ln :%p\n", ln);
पूर्ण

/**
 * csio_lnode_बंद - Close an lnode.
 * @ln:		lnode
 *
 * This routine is invoked by HW module to बंद an lnode and its
 * associated NPIV lnodes. Lnode and its associated NPIV lnodes are
 * set to uninitialized state.
 */
व्योम
csio_lnode_बंद(काष्ठा csio_lnode *ln)
अणु
	csio_post_event_lns(ln, CSIO_LNE_CLOSE);
	अगर (csio_is_phys_ln(ln))
		ln->vnp_flowid = CSIO_INVALID_IDX;

	csio_ln_dbg(ln, "closed ln :%p\n", ln);
पूर्ण

/*
 * csio_ln_prep_ecwr - Prepare ELS/CT WR.
 * @io_req - IO request.
 * @wr_len - WR len
 * @immd_len - WR immediate data
 * @sub_op - Sub opcode
 * @sid - source portid.
 * @did - destination portid
 * @flow_id - flowid
 * @fw_wr - ELS/CT WR to be prepared.
 * Returns: 0 - on success
 */
अटल पूर्णांक
csio_ln_prep_ecwr(काष्ठा csio_ioreq *io_req, uपूर्णांक32_t wr_len,
		      uपूर्णांक32_t immd_len, uपूर्णांक8_t sub_op, uपूर्णांक32_t sid,
		      uपूर्णांक32_t did, uपूर्णांक32_t flow_id, uपूर्णांक8_t *fw_wr)
अणु
	काष्ठा fw_fcoe_els_ct_wr *wr;
	__be32 port_id;

	wr  = (काष्ठा fw_fcoe_els_ct_wr *)fw_wr;
	wr->op_immdlen = cpu_to_be32(FW_WR_OP_V(FW_FCOE_ELS_CT_WR) |
				     FW_FCOE_ELS_CT_WR_IMMDLEN(immd_len));

	wr_len =  DIV_ROUND_UP(wr_len, 16);
	wr->flowid_len16 = cpu_to_be32(FW_WR_FLOWID_V(flow_id) |
				       FW_WR_LEN16_V(wr_len));
	wr->els_ct_type = sub_op;
	wr->ctl_pri = 0;
	wr->cp_en_class = 0;
	wr->cookie = io_req->fw_handle;
	wr->iqid = cpu_to_be16(csio_q_physiqid(
					io_req->lnode->hwp, io_req->iq_idx));
	wr->fl_to_sp =  FW_FCOE_ELS_CT_WR_SP(1);
	wr->पंचांगo_val = (uपूर्णांक8_t) io_req->पंचांगo;
	port_id = htonl(sid);
	स_नकल(wr->l_id, PORT_ID_PTR(port_id), 3);
	port_id = htonl(did);
	स_नकल(wr->r_id, PORT_ID_PTR(port_id), 3);

	/* Prepare RSP SGL */
	wr->rsp_dmalen = cpu_to_be32(io_req->dma_buf.len);
	wr->rsp_dmaaddr = cpu_to_be64(io_req->dma_buf.paddr);
	वापस 0;
पूर्ण

/*
 * csio_ln_mgmt_submit_wr - Post elsct work request.
 * @mgmपंचांग - mgmपंचांग
 * @io_req - io request.
 * @sub_op - ELS or CT request type
 * @pld - Dma Payload buffer
 * @pld_len - Payload len
 * Prepares ELSCT Work request and sents it to FW.
 * Returns: 0 - on success
 */
अटल पूर्णांक
csio_ln_mgmt_submit_wr(काष्ठा csio_mgmपंचांग *mgmपंचांग, काष्ठा csio_ioreq *io_req,
		uपूर्णांक8_t sub_op, काष्ठा csio_dma_buf *pld,
		uपूर्णांक32_t pld_len)
अणु
	काष्ठा csio_wr_pair wrp;
	काष्ठा csio_lnode *ln = io_req->lnode;
	काष्ठा csio_rnode *rn = io_req->rnode;
	काष्ठा	csio_hw	*hw = mgmपंचांग->hw;
	uपूर्णांक8_t fw_wr[64];
	काष्ठा ulptx_sgl dsgl;
	uपूर्णांक32_t wr_size = 0;
	uपूर्णांक8_t im_len = 0;
	uपूर्णांक32_t wr_off = 0;

	पूर्णांक ret = 0;

	/* Calculate WR Size क्रम this ELS REQ */
	wr_size = माप(काष्ठा fw_fcoe_els_ct_wr);

	/* Send as immediate data अगर pld < 256 */
	अगर (pld_len < 256) अणु
		wr_size += ALIGN(pld_len, 8);
		im_len = (uपूर्णांक8_t)pld_len;
	पूर्ण अन्यथा
		wr_size += माप(काष्ठा ulptx_sgl);

	/* Roundup WR size in units of 16 bytes */
	wr_size = ALIGN(wr_size, 16);

	/* Get WR to send ELS REQ */
	ret = csio_wr_get(hw, mgmपंचांग->eq_idx, wr_size, &wrp);
	अगर (ret != 0) अणु
		csio_err(hw, "Failed to get WR for ec_req %p ret:%d\n",
			io_req, ret);
		वापस ret;
	पूर्ण

	/* Prepare Generic WR used by all ELS/CT cmd */
	csio_ln_prep_ecwr(io_req, wr_size, im_len, sub_op,
				ln->nport_id, rn->nport_id,
				csio_rn_flowid(rn),
				&fw_wr[0]);

	/* Copy ELS/CT WR CMD */
	csio_wr_copy_to_wrp(&fw_wr[0], &wrp, wr_off,
			माप(काष्ठा fw_fcoe_els_ct_wr));
	wr_off += माप(काष्ठा fw_fcoe_els_ct_wr);

	/* Copy payload to Immediate section of WR */
	अगर (im_len)
		csio_wr_copy_to_wrp(pld->vaddr, &wrp, wr_off, im_len);
	अन्यथा अणु
		/* Program DSGL to dma payload */
		dsgl.cmd_nsge = htonl(ULPTX_CMD_V(ULP_TX_SC_DSGL) |
					ULPTX_MORE_F | ULPTX_NSGE_V(1));
		dsgl.len0 = cpu_to_be32(pld_len);
		dsgl.addr0 = cpu_to_be64(pld->paddr);
		csio_wr_copy_to_wrp(&dsgl, &wrp, ALIGN(wr_off, 8),
				   माप(काष्ठा ulptx_sgl));
	पूर्ण

	/* Issue work request to xmit ELS/CT req to FW */
	csio_wr_issue(mgmपंचांग->hw, mgmपंचांग->eq_idx, false);
	वापस ret;
पूर्ण

/*
 * csio_ln_mgmt_submit_req - Submit FCOE Mgmt request.
 * @io_req - IO Request
 * @io_cbfn - Completion handler.
 * @req_type - ELS or CT request type
 * @pld - Dma Payload buffer
 * @pld_len - Payload len
 *
 *
 * This API used submit managment ELS/CT request.
 * This called with hw lock held
 * Returns: 0 - on success
 *	    -ENOMEM	- on error.
 */
अटल पूर्णांक
csio_ln_mgmt_submit_req(काष्ठा csio_ioreq *io_req,
		व्योम (*io_cbfn) (काष्ठा csio_hw *, काष्ठा csio_ioreq *),
		क्रमागत fcoe_cmn_type req_type, काष्ठा csio_dma_buf *pld,
		uपूर्णांक32_t pld_len)
अणु
	काष्ठा csio_hw *hw = csio_lnode_to_hw(io_req->lnode);
	काष्ठा csio_mgmपंचांग *mgmपंचांग = csio_hw_to_mgmपंचांग(hw);
	पूर्णांक rv;

	BUG_ON(pld_len > pld->len);

	io_req->io_cbfn = io_cbfn;	/* Upper layer callback handler */
	io_req->fw_handle = (uपूर्णांकptr_t) (io_req);
	io_req->eq_idx = mgmपंचांग->eq_idx;
	io_req->iq_idx = mgmपंचांग->iq_idx;

	rv = csio_ln_mgmt_submit_wr(mgmपंचांग, io_req, req_type, pld, pld_len);
	अगर (rv == 0) अणु
		list_add_tail(&io_req->sm.sm_list, &mgmपंचांग->active_q);
		mgmपंचांग->stats.n_active++;
	पूर्ण
	वापस rv;
पूर्ण

/*
 * csio_ln_fdmi_init - FDMI Init entry poपूर्णांक.
 * @ln: lnode
 */
अटल पूर्णांक
csio_ln_fdmi_init(काष्ठा csio_lnode *ln)
अणु
	काष्ठा csio_hw *hw = csio_lnode_to_hw(ln);
	काष्ठा csio_dma_buf	*dma_buf;

	/* Allocate MGMT request required क्रम FDMI */
	ln->mgmt_req = kzalloc(माप(काष्ठा csio_ioreq), GFP_KERNEL);
	अगर (!ln->mgmt_req) अणु
		csio_ln_err(ln, "Failed to alloc ioreq for FDMI\n");
		CSIO_INC_STATS(hw, n_err_nomem);
		वापस -ENOMEM;
	पूर्ण

	/* Allocate Dma buffers क्रम FDMI response Payload */
	dma_buf = &ln->mgmt_req->dma_buf;
	dma_buf->len = 2048;
	dma_buf->vaddr = dma_alloc_coherent(&hw->pdev->dev, dma_buf->len,
						&dma_buf->paddr, GFP_KERNEL);
	अगर (!dma_buf->vaddr) अणु
		csio_err(hw, "Failed to alloc DMA buffer for FDMI!\n");
		kमुक्त(ln->mgmt_req);
		ln->mgmt_req = शून्य;
		वापस -ENOMEM;
	पूर्ण

	ln->flags |= CSIO_LNF_FDMI_ENABLE;
	वापस 0;
पूर्ण

/*
 * csio_ln_fdmi_निकास - FDMI निकास entry poपूर्णांक.
 * @ln: lnode
 */
अटल पूर्णांक
csio_ln_fdmi_निकास(काष्ठा csio_lnode *ln)
अणु
	काष्ठा csio_dma_buf *dma_buf;
	काष्ठा csio_hw *hw = csio_lnode_to_hw(ln);

	अगर (!ln->mgmt_req)
		वापस 0;

	dma_buf = &ln->mgmt_req->dma_buf;
	अगर (dma_buf->vaddr)
		dma_मुक्त_coherent(&hw->pdev->dev, dma_buf->len, dma_buf->vaddr,
				    dma_buf->paddr);

	kमुक्त(ln->mgmt_req);
	वापस 0;
पूर्ण

पूर्णांक
csio_scan_करोne(काष्ठा csio_lnode *ln, अचिन्हित दीर्घ ticks,
		अचिन्हित दीर्घ समय, अचिन्हित दीर्घ max_scan_ticks,
		अचिन्हित दीर्घ delta_scan_ticks)
अणु
	पूर्णांक rv = 0;

	अगर (समय >= max_scan_ticks)
		वापस 1;

	अगर (!ln->tgt_scan_tick)
		ln->tgt_scan_tick = ticks;

	अगर (((ticks - ln->tgt_scan_tick) >= delta_scan_ticks)) अणु
		अगर (!ln->last_scan_ntgts)
			ln->last_scan_ntgts = ln->n_scsi_tgts;
		अन्यथा अणु
			अगर (ln->last_scan_ntgts == ln->n_scsi_tgts)
				वापस 1;

			ln->last_scan_ntgts = ln->n_scsi_tgts;
		पूर्ण
		ln->tgt_scan_tick = ticks;
	पूर्ण
	वापस rv;
पूर्ण

/*
 * csio_notअगरy_lnodes:
 * @hw: HW module
 * @note: Notअगरication
 *
 * Called from the HW SM to fan out notअगरications to the
 * Lnode SM. Since the HW SM is entered with lock held,
 * there is no need to hold locks here.
 *
 */
व्योम
csio_notअगरy_lnodes(काष्ठा csio_hw *hw, क्रमागत csio_ln_notअगरy note)
अणु
	काष्ठा list_head *पंचांगp;
	काष्ठा csio_lnode *ln;

	csio_dbg(hw, "Notifying all nodes of event %d\n", note);

	/* Traverse children lnodes list and send evt */
	list_क्रम_each(पंचांगp, &hw->sln_head) अणु
		ln = (काष्ठा csio_lnode *) पंचांगp;

		चयन (note) अणु
		हाल CSIO_LN_NOTIFY_HWREADY:
			csio_lnode_start(ln);
			अवरोध;

		हाल CSIO_LN_NOTIFY_HWRESET:
		हाल CSIO_LN_NOTIFY_HWREMOVE:
			csio_lnode_बंद(ln);
			अवरोध;

		हाल CSIO_LN_NOTIFY_HWSTOP:
			csio_lnode_stop(ln);
			अवरोध;

		शेष:
			अवरोध;

		पूर्ण
	पूर्ण
पूर्ण

/*
 * csio_disable_lnodes:
 * @hw: HW module
 * @portid:port id
 * @disable: disable/enable flag.
 * If disable=1, disables all lnode hosted on given physical port.
 * otherwise enables all the lnodes on given phsysical port.
 * This routine need to called with hw lock held.
 */
व्योम
csio_disable_lnodes(काष्ठा csio_hw *hw, uपूर्णांक8_t portid, bool disable)
अणु
	काष्ठा list_head *पंचांगp;
	काष्ठा csio_lnode *ln;

	csio_dbg(hw, "Notifying event to all nodes of port:%d\n", portid);

	/* Traverse sibling lnodes list and send evt */
	list_क्रम_each(पंचांगp, &hw->sln_head) अणु
		ln = (काष्ठा csio_lnode *) पंचांगp;
		अगर (ln->portid != portid)
			जारी;

		अगर (disable)
			csio_lnode_stop(ln);
		अन्यथा
			csio_lnode_start(ln);
	पूर्ण
पूर्ण

/*
 * csio_ln_init - Initialize an lnode.
 * @ln:		lnode
 *
 */
अटल पूर्णांक
csio_ln_init(काष्ठा csio_lnode *ln)
अणु
	पूर्णांक rv = -EINVAL;
	काष्ठा csio_lnode *pln;
	काष्ठा csio_hw *hw = csio_lnode_to_hw(ln);

	csio_init_state(&ln->sm, csio_lns_uninit);
	ln->vnp_flowid = CSIO_INVALID_IDX;
	ln->fcf_flowid = CSIO_INVALID_IDX;

	अगर (csio_is_root_ln(ln)) अणु

		/* This is the lnode used during initialization */

		ln->fcfinfo = kzalloc(माप(काष्ठा csio_fcf_info), GFP_KERNEL);
		अगर (!ln->fcfinfo) अणु
			csio_ln_err(ln, "Failed to alloc FCF record\n");
			CSIO_INC_STATS(hw, n_err_nomem);
			जाओ err;
		पूर्ण

		INIT_LIST_HEAD(&ln->fcf_lsthead);
		kref_init(&ln->fcfinfo->kref);

		अगर (csio_fdmi_enable && csio_ln_fdmi_init(ln))
			जाओ err;

	पूर्ण अन्यथा अणु /* Either a non-root physical or a भव lnode */

		/*
		 * THe rest is common क्रम non-root physical and NPIV lnodes.
		 * Just get references to all other modules
		 */

		अगर (csio_is_npiv_ln(ln)) अणु
			/* NPIV */
			pln = csio_parent_lnode(ln);
			kref_get(&pln->fcfinfo->kref);
			ln->fcfinfo = pln->fcfinfo;
		पूर्ण अन्यथा अणु
			/* Another non-root physical lnode (FCF) */
			ln->fcfinfo = kzalloc(माप(काष्ठा csio_fcf_info),
								GFP_KERNEL);
			अगर (!ln->fcfinfo) अणु
				csio_ln_err(ln, "Failed to alloc FCF info\n");
				CSIO_INC_STATS(hw, n_err_nomem);
				जाओ err;
			पूर्ण

			kref_init(&ln->fcfinfo->kref);

			अगर (csio_fdmi_enable && csio_ln_fdmi_init(ln))
				जाओ err;
		पूर्ण

	पूर्ण /* अगर (!csio_is_root_ln(ln)) */

	वापस 0;
err:
	वापस rv;
पूर्ण

अटल व्योम
csio_ln_निकास(काष्ठा csio_lnode *ln)
अणु
	काष्ठा csio_lnode *pln;

	csio_cleanup_rns(ln);
	अगर (csio_is_npiv_ln(ln)) अणु
		pln = csio_parent_lnode(ln);
		kref_put(&pln->fcfinfo->kref, csio_मुक्त_fcfinfo);
	पूर्ण अन्यथा अणु
		kref_put(&ln->fcfinfo->kref, csio_मुक्त_fcfinfo);
		अगर (csio_fdmi_enable)
			csio_ln_fdmi_निकास(ln);
	पूर्ण
	ln->fcfinfo = शून्य;
पूर्ण

/*
 * csio_lnode_init - Initialize the members of an lnode.
 * @ln:		lnode
 */
पूर्णांक
csio_lnode_init(काष्ठा csio_lnode *ln, काष्ठा csio_hw *hw,
		काष्ठा csio_lnode *pln)
अणु
	पूर्णांक rv = -EINVAL;

	/* Link this lnode to hw */
	csio_lnode_to_hw(ln)	= hw;

	/* Link child to parent अगर child lnode */
	अगर (pln)
		ln->pln = pln;
	अन्यथा
		ln->pln = शून्य;

	/* Initialize scsi_tgt and समयrs to zero */
	ln->n_scsi_tgts = 0;
	ln->last_scan_ntgts = 0;
	ln->tgt_scan_tick = 0;

	/* Initialize rnode list */
	INIT_LIST_HEAD(&ln->rnhead);
	INIT_LIST_HEAD(&ln->cln_head);

	/* Initialize log level क्रम debug */
	ln->params.log_level	= hw->params.log_level;

	अगर (csio_ln_init(ln))
		जाओ err;

	/* Add lnode to list of sibling or children lnodes */
	spin_lock_irq(&hw->lock);
	list_add_tail(&ln->sm.sm_list, pln ? &pln->cln_head : &hw->sln_head);
	अगर (pln)
		pln->num_vports++;
	spin_unlock_irq(&hw->lock);

	hw->num_lns++;

	वापस 0;
err:
	csio_lnode_to_hw(ln) = शून्य;
	वापस rv;
पूर्ण

/**
 * csio_lnode_निकास - De-instantiate an lnode.
 * @ln:		lnode
 *
 */
व्योम
csio_lnode_निकास(काष्ठा csio_lnode *ln)
अणु
	काष्ठा csio_hw *hw = csio_lnode_to_hw(ln);

	csio_ln_निकास(ln);

	/* Remove this lnode from hw->sln_head */
	spin_lock_irq(&hw->lock);

	list_del_init(&ln->sm.sm_list);

	/* If it is children lnode, decrement the
	 * counter in its parent lnode
	 */
	अगर (ln->pln)
		ln->pln->num_vports--;

	/* Update root lnode poपूर्णांकer */
	अगर (list_empty(&hw->sln_head))
		hw->rln = शून्य;
	अन्यथा
		hw->rln = (काष्ठा csio_lnode *)csio_list_next(&hw->sln_head);

	spin_unlock_irq(&hw->lock);

	csio_lnode_to_hw(ln)	= शून्य;
	hw->num_lns--;
पूर्ण
