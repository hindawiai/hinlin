<शैली गुरु>
/*
 * Broadcom NetXtreme-E RoCE driver.
 *
 * Copyright (c) 2016 - 2017, Broadcom. All rights reserved.  The term
 * Broadcom refers to Broadcom Limited and/or its subsidiaries.
 *
 * This software is available to you under a choice of one of two
 * licenses.  You may choose to be licensed under the terms of the GNU
 * General Public License (GPL) Version 2, available from the file
 * COPYING in the मुख्य directory of this source tree, or the
 * BSD license below:
 *
 * Redistribution and use in source and binary क्रमms, with or without
 * modअगरication, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary क्रमm must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the करोcumentation and/or other materials provided with the
 *    distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS''
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS
 * BE LIABLE FOR ANY सूचीECT, INसूचीECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
 * BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 * OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN
 * IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * Description: Slow Path Operators
 */

#घोषणा dev_fmt(fmt) "QPLIB: " fmt

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/sched.h>
#समावेश <linux/pci.h>

#समावेश "roce_hsi.h"

#समावेश "qplib_res.h"
#समावेश "qplib_rcfw.h"
#समावेश "qplib_sp.h"

स्थिर काष्ठा bnxt_qplib_gid bnxt_qplib_gid_zero = अणुअणु 0, 0, 0, 0, 0, 0, 0, 0,
						     0, 0, 0, 0, 0, 0, 0, 0 पूर्ण पूर्ण;

/* Device */

अटल व्योम bnxt_qplib_query_version(काष्ठा bnxt_qplib_rcfw *rcfw,
				     अक्षर *fw_ver)
अणु
	काष्ठा cmdq_query_version req;
	काष्ठा creq_query_version_resp resp;
	u16 cmd_flags = 0;
	पूर्णांक rc = 0;

	RCFW_CMD_PREP(req, QUERY_VERSION, cmd_flags);

	rc = bnxt_qplib_rcfw_send_message(rcfw, (व्योम *)&req,
					  (व्योम *)&resp, शून्य, 0);
	अगर (rc)
		वापस;
	fw_ver[0] = resp.fw_maj;
	fw_ver[1] = resp.fw_minor;
	fw_ver[2] = resp.fw_bld;
	fw_ver[3] = resp.fw_rsvd;
पूर्ण

पूर्णांक bnxt_qplib_get_dev_attr(काष्ठा bnxt_qplib_rcfw *rcfw,
			    काष्ठा bnxt_qplib_dev_attr *attr, bool vf)
अणु
	काष्ठा cmdq_query_func req;
	काष्ठा creq_query_func_resp resp;
	काष्ठा bnxt_qplib_rcfw_sbuf *sbuf;
	काष्ठा creq_query_func_resp_sb *sb;
	u16 cmd_flags = 0;
	u32 temp;
	u8 *tqm_alloc;
	पूर्णांक i, rc = 0;

	RCFW_CMD_PREP(req, QUERY_FUNC, cmd_flags);

	sbuf = bnxt_qplib_rcfw_alloc_sbuf(rcfw, माप(*sb));
	अगर (!sbuf) अणु
		dev_err(&rcfw->pdev->dev,
			"SP: QUERY_FUNC alloc side buffer failed\n");
		वापस -ENOMEM;
	पूर्ण

	sb = sbuf->sb;
	req.resp_size = माप(*sb) / BNXT_QPLIB_CMDQE_UNITS;
	rc = bnxt_qplib_rcfw_send_message(rcfw, (व्योम *)&req, (व्योम *)&resp,
					  (व्योम *)sbuf, 0);
	अगर (rc)
		जाओ bail;

	/* Extract the context from the side buffer */
	attr->max_qp = le32_to_cpu(sb->max_qp);
	/* max_qp value reported by FW क्रम PF करोesn't include the QP1 क्रम PF */
	अगर (!vf)
		attr->max_qp += 1;
	attr->max_qp_rd_atom =
		sb->max_qp_rd_atom > BNXT_QPLIB_MAX_OUT_RD_ATOM ?
		BNXT_QPLIB_MAX_OUT_RD_ATOM : sb->max_qp_rd_atom;
	attr->max_qp_init_rd_atom =
		sb->max_qp_init_rd_atom > BNXT_QPLIB_MAX_OUT_RD_ATOM ?
		BNXT_QPLIB_MAX_OUT_RD_ATOM : sb->max_qp_init_rd_atom;
	attr->max_qp_wqes = le16_to_cpu(sb->max_qp_wr);
	/*
	 * 128 WQEs needs to be reserved क्रम the HW (8916). Prevent
	 * reporting the max number
	 */
	attr->max_qp_wqes -= BNXT_QPLIB_RESERVED_QP_WRS + 1;
	attr->max_qp_sges = bnxt_qplib_is_chip_gen_p5(rcfw->res->cctx) ?
			    6 : sb->max_sge;
	attr->max_cq = le32_to_cpu(sb->max_cq);
	attr->max_cq_wqes = le32_to_cpu(sb->max_cqe);
	attr->max_cq_sges = attr->max_qp_sges;
	attr->max_mr = le32_to_cpu(sb->max_mr);
	attr->max_mw = le32_to_cpu(sb->max_mw);

	attr->max_mr_size = le64_to_cpu(sb->max_mr_size);
	attr->max_pd = 64 * 1024;
	attr->max_raw_ethy_qp = le32_to_cpu(sb->max_raw_eth_qp);
	attr->max_ah = le32_to_cpu(sb->max_ah);

	attr->max_srq = le16_to_cpu(sb->max_srq);
	attr->max_srq_wqes = le32_to_cpu(sb->max_srq_wr) - 1;
	attr->max_srq_sges = sb->max_srq_sge;
	attr->max_pkey = le32_to_cpu(sb->max_pkeys);
	/*
	 * Some versions of FW reports more than 0xFFFF.
	 * Restrict it क्रम now to 0xFFFF to aव्योम
	 * reporting trucated value
	 */
	अगर (attr->max_pkey > 0xFFFF) अणु
		/* ib_port_attr::pkey_tbl_len is u16 */
		attr->max_pkey = 0xFFFF;
	पूर्ण

	attr->max_अंतरभूत_data = le32_to_cpu(sb->max_अंतरभूत_data);
	attr->l2_db_size = (sb->l2_db_space_size + 1) *
			    (0x01 << RCFW_DBR_BASE_PAGE_SHIFT);
	attr->max_sgid = BNXT_QPLIB_NUM_GIDS_SUPPORTED;

	bnxt_qplib_query_version(rcfw, attr->fw_ver);

	क्रम (i = 0; i < MAX_TQM_ALLOC_REQ / 4; i++) अणु
		temp = le32_to_cpu(sb->tqm_alloc_reqs[i]);
		tqm_alloc = (u8 *)&temp;
		attr->tqm_alloc_reqs[i * 4] = *tqm_alloc;
		attr->tqm_alloc_reqs[i * 4 + 1] = *(++tqm_alloc);
		attr->tqm_alloc_reqs[i * 4 + 2] = *(++tqm_alloc);
		attr->tqm_alloc_reqs[i * 4 + 3] = *(++tqm_alloc);
	पूर्ण

	attr->is_atomic = false;
bail:
	bnxt_qplib_rcfw_मुक्त_sbuf(rcfw, sbuf);
	वापस rc;
पूर्ण

पूर्णांक bnxt_qplib_set_func_resources(काष्ठा bnxt_qplib_res *res,
				  काष्ठा bnxt_qplib_rcfw *rcfw,
				  काष्ठा bnxt_qplib_ctx *ctx)
अणु
	काष्ठा cmdq_set_func_resources req;
	काष्ठा creq_set_func_resources_resp resp;
	u16 cmd_flags = 0;
	पूर्णांक rc = 0;

	RCFW_CMD_PREP(req, SET_FUNC_RESOURCES, cmd_flags);

	req.number_of_qp = cpu_to_le32(ctx->qpc_count);
	req.number_of_mrw = cpu_to_le32(ctx->mrw_count);
	req.number_of_srq =  cpu_to_le32(ctx->srqc_count);
	req.number_of_cq = cpu_to_le32(ctx->cq_count);

	req.max_qp_per_vf = cpu_to_le32(ctx->vf_res.max_qp_per_vf);
	req.max_mrw_per_vf = cpu_to_le32(ctx->vf_res.max_mrw_per_vf);
	req.max_srq_per_vf = cpu_to_le32(ctx->vf_res.max_srq_per_vf);
	req.max_cq_per_vf = cpu_to_le32(ctx->vf_res.max_cq_per_vf);
	req.max_gid_per_vf = cpu_to_le32(ctx->vf_res.max_gid_per_vf);

	rc = bnxt_qplib_rcfw_send_message(rcfw, (व्योम *)&req,
					  (व्योम *)&resp,
					  शून्य, 0);
	अगर (rc) अणु
		dev_err(&res->pdev->dev, "Failed to set function resources\n");
	पूर्ण
	वापस rc;
पूर्ण

/* SGID */
पूर्णांक bnxt_qplib_get_sgid(काष्ठा bnxt_qplib_res *res,
			काष्ठा bnxt_qplib_sgid_tbl *sgid_tbl, पूर्णांक index,
			काष्ठा bnxt_qplib_gid *gid)
अणु
	अगर (index >= sgid_tbl->max) अणु
		dev_err(&res->pdev->dev,
			"Index %d exceeded SGID table max (%d)\n",
			index, sgid_tbl->max);
		वापस -EINVAL;
	पूर्ण
	स_नकल(gid, &sgid_tbl->tbl[index].gid, माप(*gid));
	वापस 0;
पूर्ण

पूर्णांक bnxt_qplib_del_sgid(काष्ठा bnxt_qplib_sgid_tbl *sgid_tbl,
			काष्ठा bnxt_qplib_gid *gid, u16 vlan_id, bool update)
अणु
	काष्ठा bnxt_qplib_res *res = to_bnxt_qplib(sgid_tbl,
						   काष्ठा bnxt_qplib_res,
						   sgid_tbl);
	काष्ठा bnxt_qplib_rcfw *rcfw = res->rcfw;
	पूर्णांक index;

	अगर (!sgid_tbl) अणु
		dev_err(&res->pdev->dev, "SGID table not allocated\n");
		वापस -EINVAL;
	पूर्ण
	/* Do we need a sgid_lock here? */
	अगर (!sgid_tbl->active) अणु
		dev_err(&res->pdev->dev, "SGID table has no active entries\n");
		वापस -ENOMEM;
	पूर्ण
	क्रम (index = 0; index < sgid_tbl->max; index++) अणु
		अगर (!स_भेद(&sgid_tbl->tbl[index].gid, gid, माप(*gid)) &&
		    vlan_id == sgid_tbl->tbl[index].vlan_id)
			अवरोध;
	पूर्ण
	अगर (index == sgid_tbl->max) अणु
		dev_warn(&res->pdev->dev, "GID not found in the SGID table\n");
		वापस 0;
	पूर्ण
	/* Remove GID from the SGID table */
	अगर (update) अणु
		काष्ठा cmdq_delete_gid req;
		काष्ठा creq_delete_gid_resp resp;
		u16 cmd_flags = 0;
		पूर्णांक rc;

		RCFW_CMD_PREP(req, DELETE_GID, cmd_flags);
		अगर (sgid_tbl->hw_id[index] == 0xFFFF) अणु
			dev_err(&res->pdev->dev,
				"GID entry contains an invalid HW id\n");
			वापस -EINVAL;
		पूर्ण
		req.gid_index = cpu_to_le16(sgid_tbl->hw_id[index]);
		rc = bnxt_qplib_rcfw_send_message(rcfw, (व्योम *)&req,
						  (व्योम *)&resp, शून्य, 0);
		अगर (rc)
			वापस rc;
	पूर्ण
	स_नकल(&sgid_tbl->tbl[index].gid, &bnxt_qplib_gid_zero,
	       माप(bnxt_qplib_gid_zero));
	sgid_tbl->tbl[index].vlan_id = 0xFFFF;
	sgid_tbl->vlan[index] = 0;
	sgid_tbl->active--;
	dev_dbg(&res->pdev->dev,
		"SGID deleted hw_id[0x%x] = 0x%x active = 0x%x\n",
		 index, sgid_tbl->hw_id[index], sgid_tbl->active);
	sgid_tbl->hw_id[index] = (u16)-1;

	/* unlock */
	वापस 0;
पूर्ण

पूर्णांक bnxt_qplib_add_sgid(काष्ठा bnxt_qplib_sgid_tbl *sgid_tbl,
			काष्ठा bnxt_qplib_gid *gid, u8 *smac, u16 vlan_id,
			bool update, u32 *index)
अणु
	काष्ठा bnxt_qplib_res *res = to_bnxt_qplib(sgid_tbl,
						   काष्ठा bnxt_qplib_res,
						   sgid_tbl);
	काष्ठा bnxt_qplib_rcfw *rcfw = res->rcfw;
	पूर्णांक i, मुक्त_idx;

	अगर (!sgid_tbl) अणु
		dev_err(&res->pdev->dev, "SGID table not allocated\n");
		वापस -EINVAL;
	पूर्ण
	/* Do we need a sgid_lock here? */
	अगर (sgid_tbl->active == sgid_tbl->max) अणु
		dev_err(&res->pdev->dev, "SGID table is full\n");
		वापस -ENOMEM;
	पूर्ण
	मुक्त_idx = sgid_tbl->max;
	क्रम (i = 0; i < sgid_tbl->max; i++) अणु
		अगर (!स_भेद(&sgid_tbl->tbl[i], gid, माप(*gid)) &&
		    sgid_tbl->tbl[i].vlan_id == vlan_id) अणु
			dev_dbg(&res->pdev->dev,
				"SGID entry already exist in entry %d!\n", i);
			*index = i;
			वापस -EALREADY;
		पूर्ण अन्यथा अगर (!स_भेद(&sgid_tbl->tbl[i], &bnxt_qplib_gid_zero,
				   माप(bnxt_qplib_gid_zero)) &&
			   मुक्त_idx == sgid_tbl->max) अणु
			मुक्त_idx = i;
		पूर्ण
	पूर्ण
	अगर (मुक्त_idx == sgid_tbl->max) अणु
		dev_err(&res->pdev->dev,
			"SGID table is FULL but count is not MAX??\n");
		वापस -ENOMEM;
	पूर्ण
	अगर (update) अणु
		काष्ठा cmdq_add_gid req;
		काष्ठा creq_add_gid_resp resp;
		u16 cmd_flags = 0;
		पूर्णांक rc;

		RCFW_CMD_PREP(req, ADD_GID, cmd_flags);

		req.gid[0] = cpu_to_be32(((u32 *)gid->data)[3]);
		req.gid[1] = cpu_to_be32(((u32 *)gid->data)[2]);
		req.gid[2] = cpu_to_be32(((u32 *)gid->data)[1]);
		req.gid[3] = cpu_to_be32(((u32 *)gid->data)[0]);
		/*
		 * driver should ensure that all RoCE traffic is always VLAN
		 * tagged अगर RoCE traffic is running on non-zero VLAN ID or
		 * RoCE traffic is running on non-zero Priority.
		 */
		अगर ((vlan_id != 0xFFFF) || res->prio) अणु
			अगर (vlan_id != 0xFFFF)
				req.vlan = cpu_to_le16
				(vlan_id & CMDQ_ADD_GID_VLAN_VLAN_ID_MASK);
			req.vlan |= cpu_to_le16
					(CMDQ_ADD_GID_VLAN_TPID_TPID_8100 |
					 CMDQ_ADD_GID_VLAN_VLAN_EN);
		पूर्ण

		/* MAC in network क्रमmat */
		req.src_mac[0] = cpu_to_be16(((u16 *)smac)[0]);
		req.src_mac[1] = cpu_to_be16(((u16 *)smac)[1]);
		req.src_mac[2] = cpu_to_be16(((u16 *)smac)[2]);

		rc = bnxt_qplib_rcfw_send_message(rcfw, (व्योम *)&req,
						  (व्योम *)&resp, शून्य, 0);
		अगर (rc)
			वापस rc;
		sgid_tbl->hw_id[मुक्त_idx] = le32_to_cpu(resp.xid);
	पूर्ण
	/* Add GID to the sgid_tbl */
	स_नकल(&sgid_tbl->tbl[मुक्त_idx], gid, माप(*gid));
	sgid_tbl->tbl[मुक्त_idx].vlan_id = vlan_id;
	sgid_tbl->active++;
	अगर (vlan_id != 0xFFFF)
		sgid_tbl->vlan[मुक्त_idx] = 1;

	dev_dbg(&res->pdev->dev,
		"SGID added hw_id[0x%x] = 0x%x active = 0x%x\n",
		 मुक्त_idx, sgid_tbl->hw_id[मुक्त_idx], sgid_tbl->active);

	*index = मुक्त_idx;
	/* unlock */
	वापस 0;
पूर्ण

पूर्णांक bnxt_qplib_update_sgid(काष्ठा bnxt_qplib_sgid_tbl *sgid_tbl,
			   काष्ठा bnxt_qplib_gid *gid, u16 gid_idx,
			   u8 *smac)
अणु
	काष्ठा bnxt_qplib_res *res = to_bnxt_qplib(sgid_tbl,
						   काष्ठा bnxt_qplib_res,
						   sgid_tbl);
	काष्ठा bnxt_qplib_rcfw *rcfw = res->rcfw;
	काष्ठा creq_modअगरy_gid_resp resp;
	काष्ठा cmdq_modअगरy_gid req;
	पूर्णांक rc;
	u16 cmd_flags = 0;

	RCFW_CMD_PREP(req, MODIFY_GID, cmd_flags);

	req.gid[0] = cpu_to_be32(((u32 *)gid->data)[3]);
	req.gid[1] = cpu_to_be32(((u32 *)gid->data)[2]);
	req.gid[2] = cpu_to_be32(((u32 *)gid->data)[1]);
	req.gid[3] = cpu_to_be32(((u32 *)gid->data)[0]);
	अगर (res->prio) अणु
		req.vlan |= cpu_to_le16
			(CMDQ_ADD_GID_VLAN_TPID_TPID_8100 |
			 CMDQ_ADD_GID_VLAN_VLAN_EN);
	पूर्ण

	/* MAC in network क्रमmat */
	req.src_mac[0] = cpu_to_be16(((u16 *)smac)[0]);
	req.src_mac[1] = cpu_to_be16(((u16 *)smac)[1]);
	req.src_mac[2] = cpu_to_be16(((u16 *)smac)[2]);

	req.gid_index = cpu_to_le16(gid_idx);

	rc = bnxt_qplib_rcfw_send_message(rcfw, (व्योम *)&req,
					  (व्योम *)&resp, शून्य, 0);
	वापस rc;
पूर्ण

/* pkeys */
पूर्णांक bnxt_qplib_get_pkey(काष्ठा bnxt_qplib_res *res,
			काष्ठा bnxt_qplib_pkey_tbl *pkey_tbl, u16 index,
			u16 *pkey)
अणु
	अगर (index == 0xFFFF) अणु
		*pkey = 0xFFFF;
		वापस 0;
	पूर्ण
	अगर (index >= pkey_tbl->max) अणु
		dev_err(&res->pdev->dev,
			"Index %d exceeded PKEY table max (%d)\n",
			index, pkey_tbl->max);
		वापस -EINVAL;
	पूर्ण
	स_नकल(pkey, &pkey_tbl->tbl[index], माप(*pkey));
	वापस 0;
पूर्ण

पूर्णांक bnxt_qplib_del_pkey(काष्ठा bnxt_qplib_res *res,
			काष्ठा bnxt_qplib_pkey_tbl *pkey_tbl, u16 *pkey,
			bool update)
अणु
	पूर्णांक i, rc = 0;

	अगर (!pkey_tbl) अणु
		dev_err(&res->pdev->dev, "PKEY table not allocated\n");
		वापस -EINVAL;
	पूर्ण

	/* Do we need a pkey_lock here? */
	अगर (!pkey_tbl->active) अणु
		dev_err(&res->pdev->dev, "PKEY table has no active entries\n");
		वापस -ENOMEM;
	पूर्ण
	क्रम (i = 0; i < pkey_tbl->max; i++) अणु
		अगर (!स_भेद(&pkey_tbl->tbl[i], pkey, माप(*pkey)))
			अवरोध;
	पूर्ण
	अगर (i == pkey_tbl->max) अणु
		dev_err(&res->pdev->dev,
			"PKEY 0x%04x not found in the pkey table\n", *pkey);
		वापस -ENOMEM;
	पूर्ण
	स_रखो(&pkey_tbl->tbl[i], 0, माप(*pkey));
	pkey_tbl->active--;

	/* unlock */
	वापस rc;
पूर्ण

पूर्णांक bnxt_qplib_add_pkey(काष्ठा bnxt_qplib_res *res,
			काष्ठा bnxt_qplib_pkey_tbl *pkey_tbl, u16 *pkey,
			bool update)
अणु
	पूर्णांक i, मुक्त_idx, rc = 0;

	अगर (!pkey_tbl) अणु
		dev_err(&res->pdev->dev, "PKEY table not allocated\n");
		वापस -EINVAL;
	पूर्ण

	/* Do we need a pkey_lock here? */
	अगर (pkey_tbl->active == pkey_tbl->max) अणु
		dev_err(&res->pdev->dev, "PKEY table is full\n");
		वापस -ENOMEM;
	पूर्ण
	मुक्त_idx = pkey_tbl->max;
	क्रम (i = 0; i < pkey_tbl->max; i++) अणु
		अगर (!स_भेद(&pkey_tbl->tbl[i], pkey, माप(*pkey)))
			वापस -EALREADY;
		अन्यथा अगर (!pkey_tbl->tbl[i] && मुक्त_idx == pkey_tbl->max)
			मुक्त_idx = i;
	पूर्ण
	अगर (मुक्त_idx == pkey_tbl->max) अणु
		dev_err(&res->pdev->dev,
			"PKEY table is FULL but count is not MAX??\n");
		वापस -ENOMEM;
	पूर्ण
	/* Add PKEY to the pkey_tbl */
	स_नकल(&pkey_tbl->tbl[मुक्त_idx], pkey, माप(*pkey));
	pkey_tbl->active++;

	/* unlock */
	वापस rc;
पूर्ण

/* AH */
पूर्णांक bnxt_qplib_create_ah(काष्ठा bnxt_qplib_res *res, काष्ठा bnxt_qplib_ah *ah,
			 bool block)
अणु
	काष्ठा bnxt_qplib_rcfw *rcfw = res->rcfw;
	काष्ठा cmdq_create_ah req;
	काष्ठा creq_create_ah_resp resp;
	u16 cmd_flags = 0;
	u32 temp32[4];
	u16 temp16[3];
	पूर्णांक rc;

	RCFW_CMD_PREP(req, CREATE_AH, cmd_flags);

	स_नकल(temp32, ah->dgid.data, माप(काष्ठा bnxt_qplib_gid));
	req.dgid[0] = cpu_to_le32(temp32[0]);
	req.dgid[1] = cpu_to_le32(temp32[1]);
	req.dgid[2] = cpu_to_le32(temp32[2]);
	req.dgid[3] = cpu_to_le32(temp32[3]);

	req.type = ah->nw_type;
	req.hop_limit = ah->hop_limit;
	req.sgid_index = cpu_to_le16(res->sgid_tbl.hw_id[ah->sgid_index]);
	req.dest_vlan_id_flow_label = cpu_to_le32((ah->flow_label &
					CMDQ_CREATE_AH_FLOW_LABEL_MASK) |
					CMDQ_CREATE_AH_DEST_VLAN_ID_MASK);
	req.pd_id = cpu_to_le32(ah->pd->id);
	req.traffic_class = ah->traffic_class;

	/* MAC in network क्रमmat */
	स_नकल(temp16, ah->dmac, 6);
	req.dest_mac[0] = cpu_to_le16(temp16[0]);
	req.dest_mac[1] = cpu_to_le16(temp16[1]);
	req.dest_mac[2] = cpu_to_le16(temp16[2]);

	rc = bnxt_qplib_rcfw_send_message(rcfw, (व्योम *)&req, (व्योम *)&resp,
					  शून्य, block);
	अगर (rc)
		वापस rc;

	ah->id = le32_to_cpu(resp.xid);
	वापस 0;
पूर्ण

व्योम bnxt_qplib_destroy_ah(काष्ठा bnxt_qplib_res *res, काष्ठा bnxt_qplib_ah *ah,
			   bool block)
अणु
	काष्ठा bnxt_qplib_rcfw *rcfw = res->rcfw;
	काष्ठा cmdq_destroy_ah req;
	काष्ठा creq_destroy_ah_resp resp;
	u16 cmd_flags = 0;

	/* Clean up the AH table in the device */
	RCFW_CMD_PREP(req, DESTROY_AH, cmd_flags);

	req.ah_cid = cpu_to_le32(ah->id);

	bnxt_qplib_rcfw_send_message(rcfw, (व्योम *)&req, (व्योम *)&resp, शून्य,
				     block);
पूर्ण

/* MRW */
पूर्णांक bnxt_qplib_मुक्त_mrw(काष्ठा bnxt_qplib_res *res, काष्ठा bnxt_qplib_mrw *mrw)
अणु
	काष्ठा bnxt_qplib_rcfw *rcfw = res->rcfw;
	काष्ठा cmdq_deallocate_key req;
	काष्ठा creq_deallocate_key_resp resp;
	u16 cmd_flags = 0;
	पूर्णांक rc;

	अगर (mrw->lkey == 0xFFFFFFFF) अणु
		dev_info(&res->pdev->dev, "SP: Free a reserved lkey MRW\n");
		वापस 0;
	पूर्ण

	RCFW_CMD_PREP(req, DEALLOCATE_KEY, cmd_flags);

	req.mrw_flags = mrw->type;

	अगर ((mrw->type == CMDQ_ALLOCATE_MRW_MRW_FLAGS_MW_TYPE1)  ||
	    (mrw->type == CMDQ_ALLOCATE_MRW_MRW_FLAGS_MW_TYPE2A) ||
	    (mrw->type == CMDQ_ALLOCATE_MRW_MRW_FLAGS_MW_TYPE2B))
		req.key = cpu_to_le32(mrw->rkey);
	अन्यथा
		req.key = cpu_to_le32(mrw->lkey);

	rc = bnxt_qplib_rcfw_send_message(rcfw, (व्योम *)&req, (व्योम *)&resp,
					  शून्य, 0);
	अगर (rc)
		वापस rc;

	/* Free the qplib's MRW memory */
	अगर (mrw->hwq.max_elements)
		bnxt_qplib_मुक्त_hwq(res, &mrw->hwq);

	वापस 0;
पूर्ण

पूर्णांक bnxt_qplib_alloc_mrw(काष्ठा bnxt_qplib_res *res, काष्ठा bnxt_qplib_mrw *mrw)
अणु
	काष्ठा bnxt_qplib_rcfw *rcfw = res->rcfw;
	काष्ठा cmdq_allocate_mrw req;
	काष्ठा creq_allocate_mrw_resp resp;
	u16 cmd_flags = 0;
	अचिन्हित दीर्घ पंचांगp;
	पूर्णांक rc;

	RCFW_CMD_PREP(req, ALLOCATE_MRW, cmd_flags);

	req.pd_id = cpu_to_le32(mrw->pd->id);
	req.mrw_flags = mrw->type;
	अगर ((mrw->type == CMDQ_ALLOCATE_MRW_MRW_FLAGS_PMR &&
	     mrw->flags & BNXT_QPLIB_FR_PMR) ||
	    mrw->type == CMDQ_ALLOCATE_MRW_MRW_FLAGS_MW_TYPE2A ||
	    mrw->type == CMDQ_ALLOCATE_MRW_MRW_FLAGS_MW_TYPE2B)
		req.access = CMDQ_ALLOCATE_MRW_ACCESS_CONSUMER_OWNED_KEY;
	पंचांगp = (अचिन्हित दीर्घ)mrw;
	req.mrw_handle = cpu_to_le64(पंचांगp);

	rc = bnxt_qplib_rcfw_send_message(rcfw, (व्योम *)&req,
					  (व्योम *)&resp, शून्य, 0);
	अगर (rc)
		वापस rc;

	अगर ((mrw->type == CMDQ_ALLOCATE_MRW_MRW_FLAGS_MW_TYPE1)  ||
	    (mrw->type == CMDQ_ALLOCATE_MRW_MRW_FLAGS_MW_TYPE2A) ||
	    (mrw->type == CMDQ_ALLOCATE_MRW_MRW_FLAGS_MW_TYPE2B))
		mrw->rkey = le32_to_cpu(resp.xid);
	अन्यथा
		mrw->lkey = le32_to_cpu(resp.xid);
	वापस 0;
पूर्ण

पूर्णांक bnxt_qplib_dereg_mrw(काष्ठा bnxt_qplib_res *res, काष्ठा bnxt_qplib_mrw *mrw,
			 bool block)
अणु
	काष्ठा bnxt_qplib_rcfw *rcfw = res->rcfw;
	काष्ठा cmdq_deरेजिस्टर_mr req;
	काष्ठा creq_deरेजिस्टर_mr_resp resp;
	u16 cmd_flags = 0;
	पूर्णांक rc;

	RCFW_CMD_PREP(req, DEREGISTER_MR, cmd_flags);

	req.lkey = cpu_to_le32(mrw->lkey);
	rc = bnxt_qplib_rcfw_send_message(rcfw, (व्योम *)&req,
					  (व्योम *)&resp, शून्य, block);
	अगर (rc)
		वापस rc;

	/* Free the qplib's MR memory */
	अगर (mrw->hwq.max_elements) अणु
		mrw->va = 0;
		mrw->total_size = 0;
		bnxt_qplib_मुक्त_hwq(res, &mrw->hwq);
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक bnxt_qplib_reg_mr(काष्ठा bnxt_qplib_res *res, काष्ठा bnxt_qplib_mrw *mr,
		      काष्ठा ib_umem *umem, पूर्णांक num_pbls, u32 buf_pg_size)
अणु
	काष्ठा bnxt_qplib_rcfw *rcfw = res->rcfw;
	काष्ठा bnxt_qplib_hwq_attr hwq_attr = अणुपूर्ण;
	काष्ठा bnxt_qplib_sg_info sginfo = अणुपूर्ण;
	काष्ठा creq_रेजिस्टर_mr_resp resp;
	काष्ठा cmdq_रेजिस्टर_mr req;
	u16 cmd_flags = 0, level;
	पूर्णांक pages, rc;
	u32 pg_size;

	अगर (num_pbls) अणु
		pages = roundup_घात_of_two(num_pbls);
		/* Allocate memory क्रम the non-leaf pages to store buf ptrs.
		 * Non-leaf pages always uses प्रणाली PAGE_SIZE
		 */
		/* Free the hwq अगर it alपढ़ोy exist, must be a rereg */
		अगर (mr->hwq.max_elements)
			bnxt_qplib_मुक्त_hwq(res, &mr->hwq);
		/* Use प्रणाली PAGE_SIZE */
		hwq_attr.res = res;
		hwq_attr.depth = pages;
		hwq_attr.stride = buf_pg_size;
		hwq_attr.type = HWQ_TYPE_MR;
		hwq_attr.sginfo = &sginfo;
		hwq_attr.sginfo->umem = umem;
		hwq_attr.sginfo->npages = pages;
		hwq_attr.sginfo->pgsize = PAGE_SIZE;
		hwq_attr.sginfo->pgshft = PAGE_SHIFT;
		rc = bnxt_qplib_alloc_init_hwq(&mr->hwq, &hwq_attr);
		अगर (rc) अणु
			dev_err(&res->pdev->dev,
				"SP: Reg MR memory allocation failed\n");
			वापस -ENOMEM;
		पूर्ण
	पूर्ण

	RCFW_CMD_PREP(req, REGISTER_MR, cmd_flags);

	/* Configure the request */
	अगर (mr->hwq.level == PBL_LVL_MAX) अणु
		/* No PBL provided, just use प्रणाली PAGE_SIZE */
		level = 0;
		req.pbl = 0;
		pg_size = PAGE_SIZE;
	पूर्ण अन्यथा अणु
		level = mr->hwq.level;
		req.pbl = cpu_to_le64(mr->hwq.pbl[PBL_LVL_0].pg_map_arr[0]);
	पूर्ण
	pg_size = buf_pg_size ? buf_pg_size : PAGE_SIZE;
	req.log2_pg_size_lvl = (level << CMDQ_REGISTER_MR_LVL_SFT) |
			       ((ilog2(pg_size) <<
				 CMDQ_REGISTER_MR_LOG2_PG_SIZE_SFT) &
				CMDQ_REGISTER_MR_LOG2_PG_SIZE_MASK);
	req.log2_pbl_pg_size = cpu_to_le16(((ilog2(PAGE_SIZE) <<
				 CMDQ_REGISTER_MR_LOG2_PBL_PG_SIZE_SFT) &
				CMDQ_REGISTER_MR_LOG2_PBL_PG_SIZE_MASK));
	req.access = (mr->flags & 0xFFFF);
	req.va = cpu_to_le64(mr->va);
	req.key = cpu_to_le32(mr->lkey);
	req.mr_size = cpu_to_le64(mr->total_size);

	rc = bnxt_qplib_rcfw_send_message(rcfw, (व्योम *)&req,
					  (व्योम *)&resp, शून्य, false);
	अगर (rc)
		जाओ fail;

	वापस 0;

fail:
	अगर (mr->hwq.max_elements)
		bnxt_qplib_मुक्त_hwq(res, &mr->hwq);
	वापस rc;
पूर्ण

पूर्णांक bnxt_qplib_alloc_fast_reg_page_list(काष्ठा bnxt_qplib_res *res,
					काष्ठा bnxt_qplib_frpl *frpl,
					पूर्णांक max_pg_ptrs)
अणु
	काष्ठा bnxt_qplib_hwq_attr hwq_attr = अणुपूर्ण;
	काष्ठा bnxt_qplib_sg_info sginfo = अणुपूर्ण;
	पूर्णांक pg_ptrs, pages, rc;

	/* Re-calculate the max to fit the HWQ allocation model */
	pg_ptrs = roundup_घात_of_two(max_pg_ptrs);
	pages = pg_ptrs >> MAX_PBL_LVL_1_PGS_SHIFT;
	अगर (!pages)
		pages++;

	अगर (pages > MAX_PBL_LVL_1_PGS)
		वापस -ENOMEM;

	sginfo.pgsize = PAGE_SIZE;
	sginfo.nopte = true;

	hwq_attr.res = res;
	hwq_attr.depth = pg_ptrs;
	hwq_attr.stride = PAGE_SIZE;
	hwq_attr.sginfo = &sginfo;
	hwq_attr.type = HWQ_TYPE_CTX;
	rc = bnxt_qplib_alloc_init_hwq(&frpl->hwq, &hwq_attr);
	अगर (!rc)
		frpl->max_pg_ptrs = pg_ptrs;

	वापस rc;
पूर्ण

पूर्णांक bnxt_qplib_मुक्त_fast_reg_page_list(काष्ठा bnxt_qplib_res *res,
				       काष्ठा bnxt_qplib_frpl *frpl)
अणु
	bnxt_qplib_मुक्त_hwq(res, &frpl->hwq);
	वापस 0;
पूर्ण

पूर्णांक bnxt_qplib_map_tc2cos(काष्ठा bnxt_qplib_res *res, u16 *cids)
अणु
	काष्ठा bnxt_qplib_rcfw *rcfw = res->rcfw;
	काष्ठा cmdq_map_tc_to_cos req;
	काष्ठा creq_map_tc_to_cos_resp resp;
	u16 cmd_flags = 0;

	RCFW_CMD_PREP(req, MAP_TC_TO_COS, cmd_flags);
	req.cos0 = cpu_to_le16(cids[0]);
	req.cos1 = cpu_to_le16(cids[1]);

	वापस bnxt_qplib_rcfw_send_message(rcfw, (व्योम *)&req, (व्योम *)&resp,
						शून्य, 0);
पूर्ण

पूर्णांक bnxt_qplib_get_roce_stats(काष्ठा bnxt_qplib_rcfw *rcfw,
			      काष्ठा bnxt_qplib_roce_stats *stats)
अणु
	काष्ठा cmdq_query_roce_stats req;
	काष्ठा creq_query_roce_stats_resp resp;
	काष्ठा bnxt_qplib_rcfw_sbuf *sbuf;
	काष्ठा creq_query_roce_stats_resp_sb *sb;
	u16 cmd_flags = 0;
	पूर्णांक rc = 0;

	RCFW_CMD_PREP(req, QUERY_ROCE_STATS, cmd_flags);

	sbuf = bnxt_qplib_rcfw_alloc_sbuf(rcfw, माप(*sb));
	अगर (!sbuf) अणु
		dev_err(&rcfw->pdev->dev,
			"SP: QUERY_ROCE_STATS alloc side buffer failed\n");
		वापस -ENOMEM;
	पूर्ण

	sb = sbuf->sb;
	req.resp_size = माप(*sb) / BNXT_QPLIB_CMDQE_UNITS;
	rc = bnxt_qplib_rcfw_send_message(rcfw, (व्योम *)&req, (व्योम *)&resp,
					  (व्योम *)sbuf, 0);
	अगर (rc)
		जाओ bail;
	/* Extract the context from the side buffer */
	stats->to_retransmits = le64_to_cpu(sb->to_retransmits);
	stats->seq_err_naks_rcvd = le64_to_cpu(sb->seq_err_naks_rcvd);
	stats->max_retry_exceeded = le64_to_cpu(sb->max_retry_exceeded);
	stats->rnr_naks_rcvd = le64_to_cpu(sb->rnr_naks_rcvd);
	stats->missing_resp = le64_to_cpu(sb->missing_resp);
	stats->unrecoverable_err = le64_to_cpu(sb->unrecoverable_err);
	stats->bad_resp_err = le64_to_cpu(sb->bad_resp_err);
	stats->local_qp_op_err = le64_to_cpu(sb->local_qp_op_err);
	stats->local_protection_err = le64_to_cpu(sb->local_protection_err);
	stats->mem_mgmt_op_err = le64_to_cpu(sb->mem_mgmt_op_err);
	stats->remote_invalid_req_err = le64_to_cpu(sb->remote_invalid_req_err);
	stats->remote_access_err = le64_to_cpu(sb->remote_access_err);
	stats->remote_op_err = le64_to_cpu(sb->remote_op_err);
	stats->dup_req = le64_to_cpu(sb->dup_req);
	stats->res_exceed_max = le64_to_cpu(sb->res_exceed_max);
	stats->res_length_mismatch = le64_to_cpu(sb->res_length_mismatch);
	stats->res_exceeds_wqe = le64_to_cpu(sb->res_exceeds_wqe);
	stats->res_opcode_err = le64_to_cpu(sb->res_opcode_err);
	stats->res_rx_invalid_rkey = le64_to_cpu(sb->res_rx_invalid_rkey);
	stats->res_rx_करोमुख्य_err = le64_to_cpu(sb->res_rx_करोमुख्य_err);
	stats->res_rx_no_perm = le64_to_cpu(sb->res_rx_no_perm);
	stats->res_rx_range_err = le64_to_cpu(sb->res_rx_range_err);
	stats->res_tx_invalid_rkey = le64_to_cpu(sb->res_tx_invalid_rkey);
	stats->res_tx_करोमुख्य_err = le64_to_cpu(sb->res_tx_करोमुख्य_err);
	stats->res_tx_no_perm = le64_to_cpu(sb->res_tx_no_perm);
	stats->res_tx_range_err = le64_to_cpu(sb->res_tx_range_err);
	stats->res_irrq_oflow = le64_to_cpu(sb->res_irrq_oflow);
	stats->res_unsup_opcode = le64_to_cpu(sb->res_unsup_opcode);
	stats->res_unaligned_atomic = le64_to_cpu(sb->res_unaligned_atomic);
	stats->res_rem_inv_err = le64_to_cpu(sb->res_rem_inv_err);
	stats->res_mem_error = le64_to_cpu(sb->res_mem_error);
	stats->res_srq_err = le64_to_cpu(sb->res_srq_err);
	stats->res_cmp_err = le64_to_cpu(sb->res_cmp_err);
	stats->res_invalid_dup_rkey = le64_to_cpu(sb->res_invalid_dup_rkey);
	stats->res_wqe_क्रमmat_err = le64_to_cpu(sb->res_wqe_क्रमmat_err);
	stats->res_cq_load_err = le64_to_cpu(sb->res_cq_load_err);
	stats->res_srq_load_err = le64_to_cpu(sb->res_srq_load_err);
	stats->res_tx_pci_err = le64_to_cpu(sb->res_tx_pci_err);
	stats->res_rx_pci_err = le64_to_cpu(sb->res_rx_pci_err);
	अगर (!rcfw->init_oos_stats) अणु
		rcfw->oos_prev = le64_to_cpu(sb->res_oos_drop_count);
		rcfw->init_oos_stats = 1;
	पूर्ण अन्यथा अणु
		stats->res_oos_drop_count +=
				(le64_to_cpu(sb->res_oos_drop_count) -
				 rcfw->oos_prev) & BNXT_QPLIB_OOS_COUNT_MASK;
		rcfw->oos_prev = le64_to_cpu(sb->res_oos_drop_count);
	पूर्ण

bail:
	bnxt_qplib_rcfw_मुक्त_sbuf(rcfw, sbuf);
	वापस rc;
पूर्ण
