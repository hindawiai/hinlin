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
#समावेश <linux/माला.स>
#समावेश <linux/delay.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/pci.h>
#समावेश <linux/mm.h>
#समावेश <linux/jअगरfies.h>
#समावेश <scsi/fc/fc_fs.h>

#समावेश "csio_init.h"

अटल व्योम
csio_vport_set_state(काष्ठा csio_lnode *ln);

/*
 * csio_reg_rnode - Register a remote port with FC transport.
 * @rn: Rnode representing remote port.
 *
 * Call fc_remote_port_add() to रेजिस्टर this remote port with FC transport.
 * If remote port is Initiator OR Target OR both, change the role appropriately.
 *
 */
व्योम
csio_reg_rnode(काष्ठा csio_rnode *rn)
अणु
	काष्ठा csio_lnode *ln		= csio_rnode_to_lnode(rn);
	काष्ठा Scsi_Host *shost		= csio_ln_to_shost(ln);
	काष्ठा fc_rport_identअगरiers ids;
	काष्ठा fc_rport  *rport;
	काष्ठा csio_service_parms *sp;

	ids.node_name	= wwn_to_u64(csio_rn_wwnn(rn));
	ids.port_name	= wwn_to_u64(csio_rn_wwpn(rn));
	ids.port_id	= rn->nport_id;
	ids.roles	= FC_RPORT_ROLE_UNKNOWN;

	अगर (rn->role & CSIO_RNFR_INITIATOR || rn->role & CSIO_RNFR_TARGET) अणु
		rport = rn->rport;
		CSIO_ASSERT(rport != शून्य);
		जाओ update_role;
	पूर्ण

	rn->rport = fc_remote_port_add(shost, 0, &ids);
	अगर (!rn->rport) अणु
		csio_ln_err(ln, "Failed to register rport = 0x%x.\n",
					rn->nport_id);
		वापस;
	पूर्ण

	ln->num_reg_rnodes++;
	rport = rn->rport;
	spin_lock_irq(shost->host_lock);
	*((काष्ठा csio_rnode **)rport->dd_data) = rn;
	spin_unlock_irq(shost->host_lock);

	sp = &rn->rn_sparm;
	rport->maxframe_size = ntohs(sp->csp.sp_bb_data);
	अगर (ntohs(sp->clsp[2].cp_class) & FC_CPC_VALID)
		rport->supported_classes = FC_COS_CLASS3;
	अन्यथा
		rport->supported_classes = FC_COS_UNSPECIFIED;
update_role:
	अगर (rn->role & CSIO_RNFR_INITIATOR)
		ids.roles |= FC_RPORT_ROLE_FCP_INITIATOR;
	अगर (rn->role & CSIO_RNFR_TARGET)
		ids.roles |= FC_RPORT_ROLE_FCP_TARGET;

	अगर (ids.roles != FC_RPORT_ROLE_UNKNOWN)
		fc_remote_port_rolechg(rport, ids.roles);

	rn->scsi_id = rport->scsi_target_id;

	csio_ln_dbg(ln, "Remote port x%x role 0x%x registered\n",
		rn->nport_id, ids.roles);
पूर्ण

/*
 * csio_unreg_rnode - Unरेजिस्टर a remote port with FC transport.
 * @rn: Rnode representing remote port.
 *
 * Call fc_remote_port_delete() to unरेजिस्टर this remote port with FC
 * transport.
 *
 */
व्योम
csio_unreg_rnode(काष्ठा csio_rnode *rn)
अणु
	काष्ठा csio_lnode *ln = csio_rnode_to_lnode(rn);
	काष्ठा fc_rport *rport = rn->rport;

	rn->role &= ~(CSIO_RNFR_INITIATOR | CSIO_RNFR_TARGET);
	fc_remote_port_delete(rport);
	ln->num_reg_rnodes--;

	csio_ln_dbg(ln, "Remote port x%x un-registered\n", rn->nport_id);
पूर्ण

/*
 * csio_lnode_async_event - Async events from local port.
 * @ln: lnode representing local port.
 *
 * Async events from local node that FC transport/SCSI ML
 * should be made aware of (Eg: RSCN).
 */
व्योम
csio_lnode_async_event(काष्ठा csio_lnode *ln, क्रमागत csio_ln_fc_evt fc_evt)
अणु
	चयन (fc_evt) अणु
	हाल CSIO_LN_FC_RSCN:
		/* Get payload of rscn from ln */
		/* For each RSCN entry */
			/*
			 * fc_host_post_event(shost,
			 *		      fc_get_event_number(),
			 *		      FCH_EVT_RSCN,
			 *		      rscn_entry);
			 */
		अवरोध;
	हाल CSIO_LN_FC_LINKUP:
		/* send fc_host_post_event */
		/* set vport state */
		अगर (csio_is_npiv_ln(ln))
			csio_vport_set_state(ln);

		अवरोध;
	हाल CSIO_LN_FC_LINKDOWN:
		/* send fc_host_post_event */
		/* set vport state */
		अगर (csio_is_npiv_ln(ln))
			csio_vport_set_state(ln);

		अवरोध;
	हाल CSIO_LN_FC_ATTRIB_UPDATE:
		csio_fchost_attr_init(ln);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

/*
 * csio_fchost_attr_init - Initialize FC transport attributes
 * @ln: Lnode.
 *
 */
व्योम
csio_fchost_attr_init(काष्ठा csio_lnode *ln)
अणु
	काष्ठा Scsi_Host  *shost = csio_ln_to_shost(ln);

	fc_host_node_name(shost) = wwn_to_u64(csio_ln_wwnn(ln));
	fc_host_port_name(shost) = wwn_to_u64(csio_ln_wwpn(ln));

	fc_host_supported_classes(shost) = FC_COS_CLASS3;
	fc_host_max_npiv_vports(shost) =
			(csio_lnode_to_hw(ln))->fres_info.max_vnps;
	fc_host_supported_speeds(shost) = FC_PORTSPEED_10GBIT |
		FC_PORTSPEED_1GBIT;

	fc_host_maxframe_size(shost) = ntohs(ln->ln_sparm.csp.sp_bb_data);
	स_रखो(fc_host_supported_fc4s(shost), 0,
		माप(fc_host_supported_fc4s(shost)));
	fc_host_supported_fc4s(shost)[7] = 1;

	स_रखो(fc_host_active_fc4s(shost), 0,
		माप(fc_host_active_fc4s(shost)));
	fc_host_active_fc4s(shost)[7] = 1;
पूर्ण

/*
 * csio_get_host_port_id - sysfs entries क्रम nport_id is
 * populated/cached from this function
 */
अटल व्योम
csio_get_host_port_id(काष्ठा Scsi_Host *shost)
अणु
	काष्ठा csio_lnode *ln	= shost_priv(shost);
	काष्ठा csio_hw *hw = csio_lnode_to_hw(ln);

	spin_lock_irq(&hw->lock);
	fc_host_port_id(shost) = ln->nport_id;
	spin_unlock_irq(&hw->lock);
पूर्ण

/*
 * csio_get_port_type - Return FC local port type.
 * @shost: scsi host.
 *
 */
अटल व्योम
csio_get_host_port_type(काष्ठा Scsi_Host *shost)
अणु
	काष्ठा csio_lnode *ln = shost_priv(shost);
	काष्ठा csio_hw *hw = csio_lnode_to_hw(ln);

	spin_lock_irq(&hw->lock);
	अगर (csio_is_npiv_ln(ln))
		fc_host_port_type(shost) = FC_PORTTYPE_NPIV;
	अन्यथा
		fc_host_port_type(shost) = FC_PORTTYPE_NPORT;
	spin_unlock_irq(&hw->lock);
पूर्ण

/*
 * csio_get_port_state - Return FC local port state.
 * @shost: scsi host.
 *
 */
अटल व्योम
csio_get_host_port_state(काष्ठा Scsi_Host *shost)
अणु
	काष्ठा csio_lnode *ln = shost_priv(shost);
	काष्ठा csio_hw *hw = csio_lnode_to_hw(ln);
	अक्षर state[16];

	spin_lock_irq(&hw->lock);

	csio_lnode_state_to_str(ln, state);
	अगर (!म_भेद(state, "READY"))
		fc_host_port_state(shost) = FC_PORTSTATE_ONLINE;
	अन्यथा अगर (!म_भेद(state, "OFFLINE"))
		fc_host_port_state(shost) = FC_PORTSTATE_LINKDOWN;
	अन्यथा
		fc_host_port_state(shost) = FC_PORTSTATE_UNKNOWN;

	spin_unlock_irq(&hw->lock);
पूर्ण

/*
 * csio_get_host_speed - Return link speed to FC transport.
 * @shost: scsi host.
 *
 */
अटल व्योम
csio_get_host_speed(काष्ठा Scsi_Host *shost)
अणु
	काष्ठा csio_lnode *ln = shost_priv(shost);
	काष्ठा csio_hw *hw = csio_lnode_to_hw(ln);

	spin_lock_irq(&hw->lock);
	चयन (hw->pport[ln->portid].link_speed) अणु
	हाल FW_PORT_CAP32_SPEED_1G:
		fc_host_speed(shost) = FC_PORTSPEED_1GBIT;
		अवरोध;
	हाल FW_PORT_CAP32_SPEED_10G:
		fc_host_speed(shost) = FC_PORTSPEED_10GBIT;
		अवरोध;
	हाल FW_PORT_CAP32_SPEED_25G:
		fc_host_speed(shost) = FC_PORTSPEED_25GBIT;
		अवरोध;
	हाल FW_PORT_CAP32_SPEED_40G:
		fc_host_speed(shost) = FC_PORTSPEED_40GBIT;
		अवरोध;
	हाल FW_PORT_CAP32_SPEED_50G:
		fc_host_speed(shost) = FC_PORTSPEED_50GBIT;
		अवरोध;
	हाल FW_PORT_CAP32_SPEED_100G:
		fc_host_speed(shost) = FC_PORTSPEED_100GBIT;
		अवरोध;
	शेष:
		fc_host_speed(shost) = FC_PORTSPEED_UNKNOWN;
		अवरोध;
	पूर्ण
	spin_unlock_irq(&hw->lock);
पूर्ण

/*
 * csio_get_host_fabric_name - Return fabric name
 * @shost: scsi host.
 *
 */
अटल व्योम
csio_get_host_fabric_name(काष्ठा Scsi_Host *shost)
अणु
	काष्ठा csio_lnode *ln = shost_priv(shost);
	काष्ठा csio_rnode *rn = शून्य;
	काष्ठा csio_hw *hw = csio_lnode_to_hw(ln);

	spin_lock_irq(&hw->lock);
	rn = csio_rnode_lookup_portid(ln, FC_FID_FLOGI);
	अगर (rn)
		fc_host_fabric_name(shost) = wwn_to_u64(csio_rn_wwnn(rn));
	अन्यथा
		fc_host_fabric_name(shost) = 0;
	spin_unlock_irq(&hw->lock);
पूर्ण

/*
 * csio_get_host_speed - Return FC transport statistics.
 * @ln: Lnode.
 *
 */
अटल काष्ठा fc_host_statistics *
csio_get_stats(काष्ठा Scsi_Host *shost)
अणु
	काष्ठा csio_lnode *ln = shost_priv(shost);
	काष्ठा csio_hw *hw = csio_lnode_to_hw(ln);
	काष्ठा fc_host_statistics *fhs = &ln->fch_stats;
	काष्ठा fw_fcoe_port_stats fcoe_port_stats;
	uपूर्णांक64_t seconds;

	स_रखो(&fcoe_port_stats, 0, माप(काष्ठा fw_fcoe_port_stats));
	csio_get_phy_port_stats(hw, ln->portid, &fcoe_port_stats);

	fhs->tx_frames  += (be64_to_cpu(fcoe_port_stats.tx_bcast_frames) +
			    be64_to_cpu(fcoe_port_stats.tx_mcast_frames) +
			    be64_to_cpu(fcoe_port_stats.tx_ucast_frames) +
			    be64_to_cpu(fcoe_port_stats.tx_offload_frames));
	fhs->tx_words  += (be64_to_cpu(fcoe_port_stats.tx_bcast_bytes) +
			   be64_to_cpu(fcoe_port_stats.tx_mcast_bytes) +
			   be64_to_cpu(fcoe_port_stats.tx_ucast_bytes) +
			   be64_to_cpu(fcoe_port_stats.tx_offload_bytes)) /
							CSIO_WORD_TO_BYTE;
	fhs->rx_frames += (be64_to_cpu(fcoe_port_stats.rx_bcast_frames) +
			   be64_to_cpu(fcoe_port_stats.rx_mcast_frames) +
			   be64_to_cpu(fcoe_port_stats.rx_ucast_frames));
	fhs->rx_words += (be64_to_cpu(fcoe_port_stats.rx_bcast_bytes) +
			  be64_to_cpu(fcoe_port_stats.rx_mcast_bytes) +
			  be64_to_cpu(fcoe_port_stats.rx_ucast_bytes)) /
							CSIO_WORD_TO_BYTE;
	fhs->error_frames += be64_to_cpu(fcoe_port_stats.rx_err_frames);
	fhs->fcp_input_requests +=  ln->stats.n_input_requests;
	fhs->fcp_output_requests +=  ln->stats.n_output_requests;
	fhs->fcp_control_requests +=  ln->stats.n_control_requests;
	fhs->fcp_input_megabytes +=  ln->stats.n_input_bytes >> 20;
	fhs->fcp_output_megabytes +=  ln->stats.n_output_bytes >> 20;
	fhs->link_failure_count = ln->stats.n_link_करोwn;
	/* Reset stats क्रम the device */
	seconds = jअगरfies_to_msecs(jअगरfies) - hw->stats.n_reset_start;
	करो_भाग(seconds, 1000);
	fhs->seconds_since_last_reset = seconds;

	वापस fhs;
पूर्ण

/*
 * csio_set_rport_loss_पंचांगo - Set the rport dev loss समयout
 * @rport: fc rport.
 * @समयout: new value क्रम dev loss पंचांगo.
 *
 * If समयout is non zero set the dev_loss_पंचांगo to समयout, अन्यथा set
 * dev_loss_पंचांगo to one.
 */
अटल व्योम
csio_set_rport_loss_पंचांगo(काष्ठा fc_rport *rport, uपूर्णांक32_t समयout)
अणु
	अगर (समयout)
		rport->dev_loss_पंचांगo = समयout;
	अन्यथा
		rport->dev_loss_पंचांगo = 1;
पूर्ण

अटल व्योम
csio_vport_set_state(काष्ठा csio_lnode *ln)
अणु
	काष्ठा fc_vport *fc_vport = ln->fc_vport;
	काष्ठा csio_lnode  *pln = ln->pln;
	अक्षर state[16];

	/* Set fc vport state based on phyiscal lnode */
	csio_lnode_state_to_str(pln, state);
	अगर (म_भेद(state, "READY")) अणु
		fc_vport_set_state(fc_vport, FC_VPORT_LINKDOWN);
		वापस;
	पूर्ण

	अगर (!(pln->flags & CSIO_LNF_NPIVSUPP)) अणु
		fc_vport_set_state(fc_vport, FC_VPORT_NO_FABRIC_SUPP);
		वापस;
	पूर्ण

	/* Set fc vport state based on भव lnode */
	csio_lnode_state_to_str(ln, state);
	अगर (म_भेद(state, "READY")) अणु
		fc_vport_set_state(fc_vport, FC_VPORT_LINKDOWN);
		वापस;
	पूर्ण
	fc_vport_set_state(fc_vport, FC_VPORT_ACTIVE);
पूर्ण

अटल पूर्णांक
csio_fcoe_alloc_vnp(काष्ठा csio_hw *hw, काष्ठा csio_lnode *ln)
अणु
	काष्ठा csio_lnode *pln;
	काष्ठा csio_mb  *mbp;
	काष्ठा fw_fcoe_vnp_cmd *rsp;
	पूर्णांक ret = 0;
	पूर्णांक retry = 0;

	/* Issue VNP cmd to alloc vport */
	/* Allocate Mbox request */
	spin_lock_irq(&hw->lock);
	mbp = mempool_alloc(hw->mb_mempool, GFP_ATOMIC);
	अगर (!mbp) अणु
		CSIO_INC_STATS(hw, n_err_nomem);
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	pln = ln->pln;
	ln->fcf_flowid = pln->fcf_flowid;
	ln->portid = pln->portid;

	csio_fcoe_vnp_alloc_init_mb(ln, mbp, CSIO_MB_DEFAULT_TMO,
				    pln->fcf_flowid, pln->vnp_flowid, 0,
				    csio_ln_wwnn(ln), csio_ln_wwpn(ln), शून्य);

	क्रम (retry = 0; retry < 3; retry++) अणु
		/* FW is expected to complete vnp cmd in immediate mode
		 * without much delay.
		 * Otherwise, there will be increase in IO latency since HW
		 * lock is held till completion of vnp mbox cmd.
		 */
		ret = csio_mb_issue(hw, mbp);
		अगर (ret != -EBUSY)
			अवरोध;

		/* Retry अगर mbox वापसs busy */
		spin_unlock_irq(&hw->lock);
		msleep(2000);
		spin_lock_irq(&hw->lock);
	पूर्ण

	अगर (ret) अणु
		csio_ln_err(ln, "Failed to issue mbox FCoE VNP command\n");
		जाओ out_मुक्त;
	पूर्ण

	/* Process Mbox response of VNP command */
	rsp = (काष्ठा fw_fcoe_vnp_cmd *)(mbp->mb);
	अगर (FW_CMD_RETVAL_G(ntohl(rsp->alloc_to_len16)) != FW_SUCCESS) अणु
		csio_ln_err(ln, "FCOE VNP ALLOC cmd returned 0x%x!\n",
			    FW_CMD_RETVAL_G(ntohl(rsp->alloc_to_len16)));
		ret = -EINVAL;
		जाओ out_मुक्त;
	पूर्ण

	ln->vnp_flowid = FW_FCOE_VNP_CMD_VNPI_GET(
				ntohl(rsp->gen_wwn_to_vnpi));
	स_नकल(csio_ln_wwnn(ln), rsp->vnport_wwnn, 8);
	स_नकल(csio_ln_wwpn(ln), rsp->vnport_wwpn, 8);

	csio_ln_dbg(ln, "FCOE VNPI: 0x%x\n", ln->vnp_flowid);
	csio_ln_dbg(ln, "\tWWNN: %x%x%x%x%x%x%x%x\n",
		    ln->ln_sparm.wwnn[0], ln->ln_sparm.wwnn[1],
		    ln->ln_sparm.wwnn[2], ln->ln_sparm.wwnn[3],
		    ln->ln_sparm.wwnn[4], ln->ln_sparm.wwnn[5],
		    ln->ln_sparm.wwnn[6], ln->ln_sparm.wwnn[7]);
	csio_ln_dbg(ln, "\tWWPN: %x%x%x%x%x%x%x%x\n",
		    ln->ln_sparm.wwpn[0], ln->ln_sparm.wwpn[1],
		    ln->ln_sparm.wwpn[2], ln->ln_sparm.wwpn[3],
		    ln->ln_sparm.wwpn[4], ln->ln_sparm.wwpn[5],
		    ln->ln_sparm.wwpn[6], ln->ln_sparm.wwpn[7]);

out_मुक्त:
	mempool_मुक्त(mbp, hw->mb_mempool);
out:
	spin_unlock_irq(&hw->lock);
	वापस ret;
पूर्ण

अटल पूर्णांक
csio_fcoe_मुक्त_vnp(काष्ठा csio_hw *hw, काष्ठा csio_lnode *ln)
अणु
	काष्ठा csio_mb  *mbp;
	काष्ठा fw_fcoe_vnp_cmd *rsp;
	पूर्णांक ret = 0;
	पूर्णांक retry = 0;

	/* Issue VNP cmd to मुक्त vport */
	/* Allocate Mbox request */

	spin_lock_irq(&hw->lock);
	mbp = mempool_alloc(hw->mb_mempool, GFP_ATOMIC);
	अगर (!mbp) अणु
		CSIO_INC_STATS(hw, n_err_nomem);
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	csio_fcoe_vnp_मुक्त_init_mb(ln, mbp, CSIO_MB_DEFAULT_TMO,
				   ln->fcf_flowid, ln->vnp_flowid,
				   शून्य);

	क्रम (retry = 0; retry < 3; retry++) अणु
		ret = csio_mb_issue(hw, mbp);
		अगर (ret != -EBUSY)
			अवरोध;

		/* Retry अगर mbox वापसs busy */
		spin_unlock_irq(&hw->lock);
		msleep(2000);
		spin_lock_irq(&hw->lock);
	पूर्ण

	अगर (ret) अणु
		csio_ln_err(ln, "Failed to issue mbox FCoE VNP command\n");
		जाओ out_मुक्त;
	पूर्ण

	/* Process Mbox response of VNP command */
	rsp = (काष्ठा fw_fcoe_vnp_cmd *)(mbp->mb);
	अगर (FW_CMD_RETVAL_G(ntohl(rsp->alloc_to_len16)) != FW_SUCCESS) अणु
		csio_ln_err(ln, "FCOE VNP FREE cmd returned 0x%x!\n",
			    FW_CMD_RETVAL_G(ntohl(rsp->alloc_to_len16)));
		ret = -EINVAL;
	पूर्ण

out_मुक्त:
	mempool_मुक्त(mbp, hw->mb_mempool);
out:
	spin_unlock_irq(&hw->lock);
	वापस ret;
पूर्ण

अटल पूर्णांक
csio_vport_create(काष्ठा fc_vport *fc_vport, bool disable)
अणु
	काष्ठा Scsi_Host *shost = fc_vport->shost;
	काष्ठा csio_lnode *pln = shost_priv(shost);
	काष्ठा csio_lnode *ln = शून्य;
	काष्ठा csio_hw *hw = csio_lnode_to_hw(pln);
	uपूर्णांक8_t wwn[8];
	पूर्णांक ret = -1;

	ln = csio_shost_init(hw, &fc_vport->dev, false, pln);
	अगर (!ln)
		जाओ error;

	अगर (fc_vport->node_name != 0) अणु
		u64_to_wwn(fc_vport->node_name, wwn);

		अगर (!CSIO_VALID_WWN(wwn)) अणु
			csio_ln_err(ln,
				    "vport create failed. Invalid wwnn\n");
			जाओ error;
		पूर्ण
		स_नकल(csio_ln_wwnn(ln), wwn, 8);
	पूर्ण

	अगर (fc_vport->port_name != 0) अणु
		u64_to_wwn(fc_vport->port_name, wwn);

		अगर (!CSIO_VALID_WWN(wwn)) अणु
			csio_ln_err(ln,
				    "vport create failed. Invalid wwpn\n");
			जाओ error;
		पूर्ण

		अगर (csio_lnode_lookup_by_wwpn(hw, wwn)) अणु
			csio_ln_err(ln,
			    "vport create failed. wwpn already exists\n");
			जाओ error;
		पूर्ण
		स_नकल(csio_ln_wwpn(ln), wwn, 8);
	पूर्ण

	fc_vport_set_state(fc_vport, FC_VPORT_INITIALIZING);
	ln->fc_vport = fc_vport;

	अगर (csio_fcoe_alloc_vnp(hw, ln))
		जाओ error;

	*(काष्ठा csio_lnode **)fc_vport->dd_data = ln;
	अगर (!fc_vport->node_name)
		fc_vport->node_name = wwn_to_u64(csio_ln_wwnn(ln));
	अगर (!fc_vport->port_name)
		fc_vport->port_name = wwn_to_u64(csio_ln_wwpn(ln));
	csio_fchost_attr_init(ln);
	वापस 0;
error:
	अगर (ln)
		csio_shost_निकास(ln);

	वापस ret;
पूर्ण

अटल पूर्णांक
csio_vport_delete(काष्ठा fc_vport *fc_vport)
अणु
	काष्ठा csio_lnode *ln = *(काष्ठा csio_lnode **)fc_vport->dd_data;
	काष्ठा Scsi_Host *shost = csio_ln_to_shost(ln);
	काष्ठा csio_hw *hw = csio_lnode_to_hw(ln);
	पूर्णांक rmv;

	spin_lock_irq(&hw->lock);
	rmv = csio_is_hw_removing(hw);
	spin_unlock_irq(&hw->lock);

	अगर (rmv) अणु
		csio_shost_निकास(ln);
		वापस 0;
	पूर्ण

	/* Quiesce ios and send हटाओ event to lnode */
	scsi_block_requests(shost);
	spin_lock_irq(&hw->lock);
	csio_scsim_cleanup_io_lnode(csio_hw_to_scsim(hw), ln);
	csio_lnode_बंद(ln);
	spin_unlock_irq(&hw->lock);
	scsi_unblock_requests(shost);

	/* Free vnp */
	अगर (fc_vport->vport_state !=  FC_VPORT_DISABLED)
		csio_fcoe_मुक्त_vnp(hw, ln);

	csio_shost_निकास(ln);
	वापस 0;
पूर्ण

अटल पूर्णांक
csio_vport_disable(काष्ठा fc_vport *fc_vport, bool disable)
अणु
	काष्ठा csio_lnode *ln = *(काष्ठा csio_lnode **)fc_vport->dd_data;
	काष्ठा Scsi_Host *shost = csio_ln_to_shost(ln);
	काष्ठा csio_hw *hw = csio_lnode_to_hw(ln);

	/* disable vport */
	अगर (disable) अणु
		/* Quiesce ios and send stop event to lnode */
		scsi_block_requests(shost);
		spin_lock_irq(&hw->lock);
		csio_scsim_cleanup_io_lnode(csio_hw_to_scsim(hw), ln);
		csio_lnode_stop(ln);
		spin_unlock_irq(&hw->lock);
		scsi_unblock_requests(shost);

		/* Free vnp */
		csio_fcoe_मुक्त_vnp(hw, ln);
		fc_vport_set_state(fc_vport, FC_VPORT_DISABLED);
		csio_ln_err(ln, "vport disabled\n");
		वापस 0;
	पूर्ण अन्यथा अणु
		/* enable vport */
		fc_vport_set_state(fc_vport, FC_VPORT_INITIALIZING);
		अगर (csio_fcoe_alloc_vnp(hw, ln)) अणु
			csio_ln_err(ln, "vport enabled failed.\n");
			वापस -1;
		पूर्ण
		csio_ln_err(ln, "vport enabled\n");
		वापस 0;
	पूर्ण
पूर्ण

अटल व्योम
csio_dev_loss_पंचांगo_callbk(काष्ठा fc_rport *rport)
अणु
	काष्ठा csio_rnode *rn;
	काष्ठा csio_hw *hw;
	काष्ठा csio_lnode *ln;

	rn = *((काष्ठा csio_rnode **)rport->dd_data);
	ln = csio_rnode_to_lnode(rn);
	hw = csio_lnode_to_hw(ln);

	spin_lock_irq(&hw->lock);

	/* वापस अगर driver is being हटाओd or same rnode comes back online */
	अगर (csio_is_hw_removing(hw) || csio_is_rnode_पढ़ोy(rn))
		जाओ out;

	csio_ln_dbg(ln, "devloss timeout on rnode:%p portid:x%x flowid:x%x\n",
		    rn, rn->nport_id, csio_rn_flowid(rn));

	CSIO_INC_STATS(ln, n_dev_loss_पंचांगo);

	/*
	 * enqueue devloss event to event worker thपढ़ो to serialize all
	 * rnode events.
	 */
	अगर (csio_enqueue_evt(hw, CSIO_EVT_DEV_LOSS, &rn, माप(rn))) अणु
		CSIO_INC_STATS(hw, n_evt_drop);
		जाओ out;
	पूर्ण

	अगर (!(hw->flags & CSIO_HWF_FWEVT_PENDING)) अणु
		hw->flags |= CSIO_HWF_FWEVT_PENDING;
		spin_unlock_irq(&hw->lock);
		schedule_work(&hw->evtq_work);
		वापस;
	पूर्ण

out:
	spin_unlock_irq(&hw->lock);
पूर्ण

/* FC transport functions ढाँचा - Physical port */
काष्ठा fc_function_ढाँचा csio_fc_transport_funcs = अणु
	.show_host_node_name = 1,
	.show_host_port_name = 1,
	.show_host_supported_classes = 1,
	.show_host_supported_fc4s = 1,
	.show_host_maxframe_size = 1,

	.get_host_port_id = csio_get_host_port_id,
	.show_host_port_id = 1,

	.get_host_port_type = csio_get_host_port_type,
	.show_host_port_type = 1,

	.get_host_port_state = csio_get_host_port_state,
	.show_host_port_state = 1,

	.show_host_active_fc4s = 1,
	.get_host_speed = csio_get_host_speed,
	.show_host_speed = 1,
	.get_host_fabric_name = csio_get_host_fabric_name,
	.show_host_fabric_name = 1,

	.get_fc_host_stats = csio_get_stats,

	.dd_fcrport_size = माप(काष्ठा csio_rnode *),
	.show_rport_maxframe_size = 1,
	.show_rport_supported_classes = 1,

	.set_rport_dev_loss_पंचांगo = csio_set_rport_loss_पंचांगo,
	.show_rport_dev_loss_पंचांगo = 1,

	.show_starget_port_id = 1,
	.show_starget_node_name = 1,
	.show_starget_port_name = 1,

	.dev_loss_पंचांगo_callbk = csio_dev_loss_पंचांगo_callbk,
	.dd_fcvport_size = माप(काष्ठा csio_lnode *),

	.vport_create = csio_vport_create,
	.vport_disable = csio_vport_disable,
	.vport_delete = csio_vport_delete,
पूर्ण;

/* FC transport functions ढाँचा - Virtual  port */
काष्ठा fc_function_ढाँचा csio_fc_transport_vport_funcs = अणु
	.show_host_node_name = 1,
	.show_host_port_name = 1,
	.show_host_supported_classes = 1,
	.show_host_supported_fc4s = 1,
	.show_host_maxframe_size = 1,

	.get_host_port_id = csio_get_host_port_id,
	.show_host_port_id = 1,

	.get_host_port_type = csio_get_host_port_type,
	.show_host_port_type = 1,

	.get_host_port_state = csio_get_host_port_state,
	.show_host_port_state = 1,
	.show_host_active_fc4s = 1,

	.get_host_speed = csio_get_host_speed,
	.show_host_speed = 1,

	.get_host_fabric_name = csio_get_host_fabric_name,
	.show_host_fabric_name = 1,

	.get_fc_host_stats = csio_get_stats,

	.dd_fcrport_size = माप(काष्ठा csio_rnode *),
	.show_rport_maxframe_size = 1,
	.show_rport_supported_classes = 1,

	.set_rport_dev_loss_पंचांगo = csio_set_rport_loss_पंचांगo,
	.show_rport_dev_loss_पंचांगo = 1,

	.show_starget_port_id = 1,
	.show_starget_node_name = 1,
	.show_starget_port_name = 1,

	.dev_loss_पंचांगo_callbk = csio_dev_loss_पंचांगo_callbk,

पूर्ण;
