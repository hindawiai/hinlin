<शैली गुरु>
/*
 * Copyright (c) 2012 Intel Corporation.  All rights reserved.
 * Copyright (c) 2006 - 2012 QLogic Corporation. All rights reserved.
 * Copyright (c) 2005, 2006 PathScale, Inc. All rights reserved.
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

#समावेश <rdma/ib_smi.h>

#समावेश "qib.h"
#समावेश "qib_mad.h"

अटल पूर्णांक reply(काष्ठा ib_smp *smp)
अणु
	/*
	 * The verbs framework will handle the directed/LID route
	 * packet changes.
	 */
	smp->method = IB_MGMT_METHOD_GET_RESP;
	अगर (smp->mgmt_class == IB_MGMT_CLASS_SUBN_सूचीECTED_ROUTE)
		smp->status |= IB_SMP_सूचीECTION;
	वापस IB_MAD_RESULT_SUCCESS | IB_MAD_RESULT_REPLY;
पूर्ण

अटल पूर्णांक reply_failure(काष्ठा ib_smp *smp)
अणु
	/*
	 * The verbs framework will handle the directed/LID route
	 * packet changes.
	 */
	smp->method = IB_MGMT_METHOD_GET_RESP;
	अगर (smp->mgmt_class == IB_MGMT_CLASS_SUBN_सूचीECTED_ROUTE)
		smp->status |= IB_SMP_सूचीECTION;
	वापस IB_MAD_RESULT_FAILURE | IB_MAD_RESULT_REPLY;
पूर्ण

अटल व्योम qib_send_trap(काष्ठा qib_ibport *ibp, व्योम *data, अचिन्हित len)
अणु
	काष्ठा ib_mad_send_buf *send_buf;
	काष्ठा ib_mad_agent *agent;
	काष्ठा ib_smp *smp;
	पूर्णांक ret;
	अचिन्हित दीर्घ flags;
	अचिन्हित दीर्घ समयout;

	agent = ibp->rvp.send_agent;
	अगर (!agent)
		वापस;

	/* o14-3.2.1 */
	अगर (!(ppd_from_ibp(ibp)->lflags & QIBL_LINKACTIVE))
		वापस;

	/* o14-2 */
	अगर (ibp->rvp.trap_समयout &&
	    समय_beक्रमe(jअगरfies, ibp->rvp.trap_समयout))
		वापस;

	send_buf = ib_create_send_mad(agent, 0, 0, 0, IB_MGMT_MAD_HDR,
				      IB_MGMT_MAD_DATA, GFP_ATOMIC,
				      IB_MGMT_BASE_VERSION);
	अगर (IS_ERR(send_buf))
		वापस;

	smp = send_buf->mad;
	smp->base_version = IB_MGMT_BASE_VERSION;
	smp->mgmt_class = IB_MGMT_CLASS_SUBN_LID_ROUTED;
	smp->class_version = 1;
	smp->method = IB_MGMT_METHOD_TRAP;
	ibp->rvp.tid++;
	smp->tid = cpu_to_be64(ibp->rvp.tid);
	smp->attr_id = IB_SMP_ATTR_NOTICE;
	/* o14-1: smp->mkey = 0; */
	स_नकल(smp->data, data, len);

	spin_lock_irqsave(&ibp->rvp.lock, flags);
	अगर (!ibp->rvp.sm_ah) अणु
		अगर (ibp->rvp.sm_lid != be16_to_cpu(IB_LID_PERMISSIVE)) अणु
			काष्ठा ib_ah *ah;

			ah = qib_create_qp0_ah(ibp, (u16)ibp->rvp.sm_lid);
			अगर (IS_ERR(ah))
				ret = PTR_ERR(ah);
			अन्यथा अणु
				send_buf->ah = ah;
				ibp->rvp.sm_ah = ibah_to_rvtah(ah);
				ret = 0;
			पूर्ण
		पूर्ण अन्यथा
			ret = -EINVAL;
	पूर्ण अन्यथा अणु
		send_buf->ah = &ibp->rvp.sm_ah->ibah;
		ret = 0;
	पूर्ण
	spin_unlock_irqrestore(&ibp->rvp.lock, flags);

	अगर (!ret)
		ret = ib_post_send_mad(send_buf, शून्य);
	अगर (!ret) अणु
		/* 4.096 usec. */
		समयout = (4096 * (1UL << ibp->rvp.subnet_समयout)) / 1000;
		ibp->rvp.trap_समयout = jअगरfies + usecs_to_jअगरfies(समयout);
	पूर्ण अन्यथा अणु
		ib_मुक्त_send_mad(send_buf);
		ibp->rvp.trap_समयout = 0;
	पूर्ण
पूर्ण

/*
 * Send a bad P_Key trap (ch. 14.3.8).
 */
व्योम qib_bad_pkey(काष्ठा qib_ibport *ibp, u32 key, u32 sl,
		  u32 qp1, u32 qp2, __be16 lid1, __be16 lid2)
अणु
	काष्ठा ib_mad_notice_attr data;

	ibp->rvp.n_pkt_drops++;
	ibp->rvp.pkey_violations++;

	/* Send violation trap */
	data.generic_type = IB_NOTICE_TYPE_SECURITY;
	data.prod_type_msb = 0;
	data.prod_type_lsb = IB_NOTICE_PROD_CA;
	data.trap_num = IB_NOTICE_TRAP_BAD_PKEY;
	data.issuer_lid = cpu_to_be16(ppd_from_ibp(ibp)->lid);
	data.toggle_count = 0;
	स_रखो(&data.details, 0, माप(data.details));
	data.details.ntc_257_258.lid1 = lid1;
	data.details.ntc_257_258.lid2 = lid2;
	data.details.ntc_257_258.key = cpu_to_be32(key);
	data.details.ntc_257_258.sl_qp1 = cpu_to_be32((sl << 28) | qp1);
	data.details.ntc_257_258.qp2 = cpu_to_be32(qp2);

	qib_send_trap(ibp, &data, माप(data));
पूर्ण

/*
 * Send a bad M_Key trap (ch. 14.3.9).
 */
अटल व्योम qib_bad_mkey(काष्ठा qib_ibport *ibp, काष्ठा ib_smp *smp)
अणु
	काष्ठा ib_mad_notice_attr data;

	/* Send violation trap */
	data.generic_type = IB_NOTICE_TYPE_SECURITY;
	data.prod_type_msb = 0;
	data.prod_type_lsb = IB_NOTICE_PROD_CA;
	data.trap_num = IB_NOTICE_TRAP_BAD_MKEY;
	data.issuer_lid = cpu_to_be16(ppd_from_ibp(ibp)->lid);
	data.toggle_count = 0;
	स_रखो(&data.details, 0, माप(data.details));
	data.details.ntc_256.lid = data.issuer_lid;
	data.details.ntc_256.method = smp->method;
	data.details.ntc_256.attr_id = smp->attr_id;
	data.details.ntc_256.attr_mod = smp->attr_mod;
	data.details.ntc_256.mkey = smp->mkey;
	अगर (smp->mgmt_class == IB_MGMT_CLASS_SUBN_सूचीECTED_ROUTE) अणु
		u8 hop_cnt;

		data.details.ntc_256.dr_slid = smp->dr_slid;
		data.details.ntc_256.dr_trunc_hop = IB_NOTICE_TRAP_DR_NOTICE;
		hop_cnt = smp->hop_cnt;
		अगर (hop_cnt > ARRAY_SIZE(data.details.ntc_256.dr_rtn_path)) अणु
			data.details.ntc_256.dr_trunc_hop |=
				IB_NOTICE_TRAP_DR_TRUNC;
			hop_cnt = ARRAY_SIZE(data.details.ntc_256.dr_rtn_path);
		पूर्ण
		data.details.ntc_256.dr_trunc_hop |= hop_cnt;
		स_नकल(data.details.ntc_256.dr_rtn_path, smp->वापस_path,
		       hop_cnt);
	पूर्ण

	qib_send_trap(ibp, &data, माप(data));
पूर्ण

/*
 * Send a Port Capability Mask Changed trap (ch. 14.3.11).
 */
व्योम qib_cap_mask_chg(काष्ठा rvt_dev_info *rdi, u32 port_num)
अणु
	काष्ठा qib_ibdev *ibdev = container_of(rdi, काष्ठा qib_ibdev, rdi);
	काष्ठा qib_devdata *dd = dd_from_dev(ibdev);
	काष्ठा qib_ibport *ibp = &dd->pport[port_num - 1].ibport_data;
	काष्ठा ib_mad_notice_attr data;

	data.generic_type = IB_NOTICE_TYPE_INFO;
	data.prod_type_msb = 0;
	data.prod_type_lsb = IB_NOTICE_PROD_CA;
	data.trap_num = IB_NOTICE_TRAP_CAP_MASK_CHG;
	data.issuer_lid = cpu_to_be16(ppd_from_ibp(ibp)->lid);
	data.toggle_count = 0;
	स_रखो(&data.details, 0, माप(data.details));
	data.details.ntc_144.lid = data.issuer_lid;
	data.details.ntc_144.new_cap_mask =
					cpu_to_be32(ibp->rvp.port_cap_flags);
	qib_send_trap(ibp, &data, माप(data));
पूर्ण

/*
 * Send a System Image GUID Changed trap (ch. 14.3.12).
 */
व्योम qib_sys_guid_chg(काष्ठा qib_ibport *ibp)
अणु
	काष्ठा ib_mad_notice_attr data;

	data.generic_type = IB_NOTICE_TYPE_INFO;
	data.prod_type_msb = 0;
	data.prod_type_lsb = IB_NOTICE_PROD_CA;
	data.trap_num = IB_NOTICE_TRAP_SYS_GUID_CHG;
	data.issuer_lid = cpu_to_be16(ppd_from_ibp(ibp)->lid);
	data.toggle_count = 0;
	स_रखो(&data.details, 0, माप(data.details));
	data.details.ntc_145.lid = data.issuer_lid;
	data.details.ntc_145.new_sys_guid = ib_qib_sys_image_guid;

	qib_send_trap(ibp, &data, माप(data));
पूर्ण

/*
 * Send a Node Description Changed trap (ch. 14.3.13).
 */
व्योम qib_node_desc_chg(काष्ठा qib_ibport *ibp)
अणु
	काष्ठा ib_mad_notice_attr data;

	data.generic_type = IB_NOTICE_TYPE_INFO;
	data.prod_type_msb = 0;
	data.prod_type_lsb = IB_NOTICE_PROD_CA;
	data.trap_num = IB_NOTICE_TRAP_CAP_MASK_CHG;
	data.issuer_lid = cpu_to_be16(ppd_from_ibp(ibp)->lid);
	data.toggle_count = 0;
	स_रखो(&data.details, 0, माप(data.details));
	data.details.ntc_144.lid = data.issuer_lid;
	data.details.ntc_144.local_changes = 1;
	data.details.ntc_144.change_flags = IB_NOTICE_TRAP_NODE_DESC_CHG;

	qib_send_trap(ibp, &data, माप(data));
पूर्ण

अटल पूर्णांक subn_get_nodedescription(काष्ठा ib_smp *smp,
				    काष्ठा ib_device *ibdev)
अणु
	अगर (smp->attr_mod)
		smp->status |= IB_SMP_INVALID_FIELD;

	स_नकल(smp->data, ibdev->node_desc, माप(smp->data));

	वापस reply(smp);
पूर्ण

अटल पूर्णांक subn_get_nodeinfo(काष्ठा ib_smp *smp, काष्ठा ib_device *ibdev,
			     u8 port)
अणु
	काष्ठा ib_node_info *nip = (काष्ठा ib_node_info *)&smp->data;
	काष्ठा qib_devdata *dd = dd_from_ibdev(ibdev);
	u32 majrev, minrev;
	अचिन्हित pidx = port - 1; /* IB number port from 1, hdw from 0 */

	/* GUID 0 is illegal */
	अगर (smp->attr_mod || pidx >= dd->num_pports ||
	    dd->pport[pidx].guid == 0)
		smp->status |= IB_SMP_INVALID_FIELD;
	अन्यथा
		nip->port_guid = dd->pport[pidx].guid;

	nip->base_version = 1;
	nip->class_version = 1;
	nip->node_type = 1;     /* channel adapter */
	nip->num_ports = ibdev->phys_port_cnt;
	/* This is alपढ़ोy in network order */
	nip->sys_guid = ib_qib_sys_image_guid;
	nip->node_guid = dd->pport->guid; /* Use first-port GUID as node */
	nip->partition_cap = cpu_to_be16(qib_get_npkeys(dd));
	nip->device_id = cpu_to_be16(dd->deviceid);
	majrev = dd->majrev;
	minrev = dd->minrev;
	nip->revision = cpu_to_be32((majrev << 16) | minrev);
	nip->local_port_num = port;
	nip->venकरोr_id[0] = QIB_SRC_OUI_1;
	nip->venकरोr_id[1] = QIB_SRC_OUI_2;
	nip->venकरोr_id[2] = QIB_SRC_OUI_3;

	वापस reply(smp);
पूर्ण

अटल पूर्णांक subn_get_guidinfo(काष्ठा ib_smp *smp, काष्ठा ib_device *ibdev,
			     u8 port)
अणु
	काष्ठा qib_devdata *dd = dd_from_ibdev(ibdev);
	u32 startgx = 8 * be32_to_cpu(smp->attr_mod);
	__be64 *p = (__be64 *) smp->data;
	अचिन्हित pidx = port - 1; /* IB number port from 1, hdw from 0 */

	/* 32 blocks of 8 64-bit GUIDs per block */

	स_रखो(smp->data, 0, माप(smp->data));

	अगर (startgx == 0 && pidx < dd->num_pports) अणु
		काष्ठा qib_pportdata *ppd = dd->pport + pidx;
		काष्ठा qib_ibport *ibp = &ppd->ibport_data;
		__be64 g = ppd->guid;
		अचिन्हित i;

		/* GUID 0 is illegal */
		अगर (g == 0)
			smp->status |= IB_SMP_INVALID_FIELD;
		अन्यथा अणु
			/* The first is a copy of the पढ़ो-only HW GUID. */
			p[0] = g;
			क्रम (i = 1; i < QIB_GUIDS_PER_PORT; i++)
				p[i] = ibp->guids[i - 1];
		पूर्ण
	पूर्ण अन्यथा
		smp->status |= IB_SMP_INVALID_FIELD;

	वापस reply(smp);
पूर्ण

अटल व्योम set_link_width_enabled(काष्ठा qib_pportdata *ppd, u32 w)
अणु
	(व्योम) ppd->dd->f_set_ib_cfg(ppd, QIB_IB_CFG_LWID_ENB, w);
पूर्ण

अटल व्योम set_link_speed_enabled(काष्ठा qib_pportdata *ppd, u32 s)
अणु
	(व्योम) ppd->dd->f_set_ib_cfg(ppd, QIB_IB_CFG_SPD_ENB, s);
पूर्ण

अटल पूर्णांक get_overrunthreshold(काष्ठा qib_pportdata *ppd)
अणु
	वापस ppd->dd->f_get_ib_cfg(ppd, QIB_IB_CFG_OVERRUN_THRESH);
पूर्ण

/**
 * set_overrunthreshold - set the overrun threshold
 * @ppd: the physical port data
 * @n: the new threshold
 *
 * Note that this will only take effect when the link state changes.
 */
अटल पूर्णांक set_overrunthreshold(काष्ठा qib_pportdata *ppd, अचिन्हित n)
अणु
	(व्योम) ppd->dd->f_set_ib_cfg(ppd, QIB_IB_CFG_OVERRUN_THRESH,
					 (u32)n);
	वापस 0;
पूर्ण

अटल पूर्णांक get_phyerrthreshold(काष्ठा qib_pportdata *ppd)
अणु
	वापस ppd->dd->f_get_ib_cfg(ppd, QIB_IB_CFG_PHYERR_THRESH);
पूर्ण

/**
 * set_phyerrthreshold - set the physical error threshold
 * @ppd: the physical port data
 * @n: the new threshold
 *
 * Note that this will only take effect when the link state changes.
 */
अटल पूर्णांक set_phyerrthreshold(काष्ठा qib_pportdata *ppd, अचिन्हित n)
अणु
	(व्योम) ppd->dd->f_set_ib_cfg(ppd, QIB_IB_CFG_PHYERR_THRESH,
					 (u32)n);
	वापस 0;
पूर्ण

/**
 * get_linkकरोwnशेषstate - get the शेष linkकरोwn state
 * @ppd: the physical port data
 *
 * Returns zero अगर the शेष is POLL, 1 अगर the शेष is SLEEP.
 */
अटल पूर्णांक get_linkकरोwnशेषstate(काष्ठा qib_pportdata *ppd)
अणु
	वापस ppd->dd->f_get_ib_cfg(ppd, QIB_IB_CFG_LINKDEFAULT) ==
		IB_LINKINITCMD_SLEEP;
पूर्ण

अटल पूर्णांक check_mkey(काष्ठा qib_ibport *ibp, काष्ठा ib_smp *smp, पूर्णांक mad_flags)
अणु
	पूर्णांक valid_mkey = 0;
	पूर्णांक ret = 0;

	/* Is the mkey in the process of expiring? */
	अगर (ibp->rvp.mkey_lease_समयout &&
	    समय_after_eq(jअगरfies, ibp->rvp.mkey_lease_समयout)) अणु
		/* Clear समयout and mkey protection field. */
		ibp->rvp.mkey_lease_समयout = 0;
		ibp->rvp.mkeyprot = 0;
	पूर्ण

	अगर ((mad_flags & IB_MAD_IGNORE_MKEY) ||  ibp->rvp.mkey == 0 ||
	    ibp->rvp.mkey == smp->mkey)
		valid_mkey = 1;

	/* Unset lease समयout on any valid Get/Set/TrapRepress */
	अगर (valid_mkey && ibp->rvp.mkey_lease_समयout &&
	    (smp->method == IB_MGMT_METHOD_GET ||
	     smp->method == IB_MGMT_METHOD_SET ||
	     smp->method == IB_MGMT_METHOD_TRAP_REPRESS))
		ibp->rvp.mkey_lease_समयout = 0;

	अगर (!valid_mkey) अणु
		चयन (smp->method) अणु
		हाल IB_MGMT_METHOD_GET:
			/* Bad mkey not a violation below level 2 */
			अगर (ibp->rvp.mkeyprot < 2)
				अवरोध;
			fallthrough;
		हाल IB_MGMT_METHOD_SET:
		हाल IB_MGMT_METHOD_TRAP_REPRESS:
			अगर (ibp->rvp.mkey_violations != 0xFFFF)
				++ibp->rvp.mkey_violations;
			अगर (!ibp->rvp.mkey_lease_समयout &&
			    ibp->rvp.mkey_lease_period)
				ibp->rvp.mkey_lease_समयout = jअगरfies +
					ibp->rvp.mkey_lease_period * HZ;
			/* Generate a trap notice. */
			qib_bad_mkey(ibp, smp);
			ret = 1;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक subn_get_portinfo(काष्ठा ib_smp *smp, काष्ठा ib_device *ibdev,
			     u8 port)
अणु
	काष्ठा qib_devdata *dd;
	काष्ठा qib_pportdata *ppd;
	काष्ठा qib_ibport *ibp;
	काष्ठा ib_port_info *pip = (काष्ठा ib_port_info *)smp->data;
	u8 mtu;
	पूर्णांक ret;
	u32 state;
	u32 port_num = be32_to_cpu(smp->attr_mod);

	अगर (port_num == 0)
		port_num = port;
	अन्यथा अणु
		अगर (port_num > ibdev->phys_port_cnt) अणु
			smp->status |= IB_SMP_INVALID_FIELD;
			ret = reply(smp);
			जाओ bail;
		पूर्ण
		अगर (port_num != port) अणु
			ibp = to_iport(ibdev, port_num);
			ret = check_mkey(ibp, smp, 0);
			अगर (ret) अणु
				ret = IB_MAD_RESULT_FAILURE;
				जाओ bail;
			पूर्ण
		पूर्ण
	पूर्ण

	dd = dd_from_ibdev(ibdev);
	/* IB numbers ports from 1, hdw from 0 */
	ppd = dd->pport + (port_num - 1);
	ibp = &ppd->ibport_data;

	/* Clear all fields.  Only set the non-zero fields. */
	स_रखो(smp->data, 0, माप(smp->data));

	/* Only वापस the mkey अगर the protection field allows it. */
	अगर (!(smp->method == IB_MGMT_METHOD_GET &&
	      ibp->rvp.mkey != smp->mkey &&
	      ibp->rvp.mkeyprot == 1))
		pip->mkey = ibp->rvp.mkey;
	pip->gid_prefix = ibp->rvp.gid_prefix;
	pip->lid = cpu_to_be16(ppd->lid);
	pip->sm_lid = cpu_to_be16((u16)ibp->rvp.sm_lid);
	pip->cap_mask = cpu_to_be32(ibp->rvp.port_cap_flags);
	/* pip->diag_code; */
	pip->mkey_lease_period = cpu_to_be16(ibp->rvp.mkey_lease_period);
	pip->local_port_num = port;
	pip->link_width_enabled = ppd->link_width_enabled;
	pip->link_width_supported = ppd->link_width_supported;
	pip->link_width_active = ppd->link_width_active;
	state = dd->f_iblink_state(ppd->lastibcstat);
	pip->linkspeed_portstate = ppd->link_speed_supported << 4 | state;

	pip->portphysstate_linkकरोwn =
		(dd->f_ibphys_portstate(ppd->lastibcstat) << 4) |
		(get_linkकरोwnशेषstate(ppd) ? 1 : 2);
	pip->mkeyprot_resv_lmc = (ibp->rvp.mkeyprot << 6) | ppd->lmc;
	pip->linkspeedactive_enabled = (ppd->link_speed_active << 4) |
		ppd->link_speed_enabled;
	चयन (ppd->ibmtu) अणु
	शेष: /* something is wrong; fall through */
	हाल 4096:
		mtu = IB_MTU_4096;
		अवरोध;
	हाल 2048:
		mtu = IB_MTU_2048;
		अवरोध;
	हाल 1024:
		mtu = IB_MTU_1024;
		अवरोध;
	हाल 512:
		mtu = IB_MTU_512;
		अवरोध;
	हाल 256:
		mtu = IB_MTU_256;
		अवरोध;
	पूर्ण
	pip->neighbormtu_mastersmsl = (mtu << 4) | ibp->rvp.sm_sl;
	pip->vlcap_inittype = ppd->vls_supported << 4;  /* InitType = 0 */
	pip->vl_high_limit = ibp->rvp.vl_high_limit;
	pip->vl_arb_high_cap =
		dd->f_get_ib_cfg(ppd, QIB_IB_CFG_VL_HIGH_CAP);
	pip->vl_arb_low_cap =
		dd->f_get_ib_cfg(ppd, QIB_IB_CFG_VL_LOW_CAP);
	/* InitTypeReply = 0 */
	pip->inittypereply_mtucap = qib_ibmtu ? qib_ibmtu : IB_MTU_4096;
	/* HCAs ignore VLStallCount and HOQLअगरe */
	/* pip->vlstallcnt_hoqlअगरe; */
	pip->operationalvl_pei_peo_fpi_fpo =
		dd->f_get_ib_cfg(ppd, QIB_IB_CFG_OP_VLS) << 4;
	pip->mkey_violations = cpu_to_be16(ibp->rvp.mkey_violations);
	/* P_KeyViolations are counted by hardware. */
	pip->pkey_violations = cpu_to_be16(ibp->rvp.pkey_violations);
	pip->qkey_violations = cpu_to_be16(ibp->rvp.qkey_violations);
	/* Only the hardware GUID is supported क्रम now */
	pip->guid_cap = QIB_GUIDS_PER_PORT;
	pip->clientrereg_resv_subnetto = ibp->rvp.subnet_समयout;
	/* 32.768 usec. response समय (guessing) */
	pip->resv_respसमयvalue = 3;
	pip->localphyerrors_overrunerrors =
		(get_phyerrthreshold(ppd) << 4) |
		get_overrunthreshold(ppd);
	/* pip->max_credit_hपूर्णांक; */
	अगर (ibp->rvp.port_cap_flags & IB_PORT_LINK_LATENCY_SUP) अणु
		u32 v;

		v = dd->f_get_ib_cfg(ppd, QIB_IB_CFG_LINKLATENCY);
		pip->link_roundtrip_latency[0] = v >> 16;
		pip->link_roundtrip_latency[1] = v >> 8;
		pip->link_roundtrip_latency[2] = v;
	पूर्ण

	ret = reply(smp);

bail:
	वापस ret;
पूर्ण

/**
 * get_pkeys - वापस the PKEY table
 * @dd: the qlogic_ib device
 * @port: the IB port number
 * @pkeys: the pkey table is placed here
 */
अटल पूर्णांक get_pkeys(काष्ठा qib_devdata *dd, u8 port, u16 *pkeys)
अणु
	काष्ठा qib_pportdata *ppd = dd->pport + port - 1;
	/*
	 * always a kernel context, no locking needed.
	 * If we get here with ppd setup, no need to check
	 * that pd is valid.
	 */
	काष्ठा qib_ctxtdata *rcd = dd->rcd[ppd->hw_pidx];

	स_नकल(pkeys, rcd->pkeys, माप(rcd->pkeys));

	वापस 0;
पूर्ण

अटल पूर्णांक subn_get_pkeytable(काष्ठा ib_smp *smp, काष्ठा ib_device *ibdev,
			      u8 port)
अणु
	u32 startpx = 32 * (be32_to_cpu(smp->attr_mod) & 0xffff);
	u16 *p = (u16 *) smp->data;
	__be16 *q = (__be16 *) smp->data;

	/* 64 blocks of 32 16-bit P_Key entries */

	स_रखो(smp->data, 0, माप(smp->data));
	अगर (startpx == 0) अणु
		काष्ठा qib_devdata *dd = dd_from_ibdev(ibdev);
		अचिन्हित i, n = qib_get_npkeys(dd);

		get_pkeys(dd, port, p);

		क्रम (i = 0; i < n; i++)
			q[i] = cpu_to_be16(p[i]);
	पूर्ण अन्यथा
		smp->status |= IB_SMP_INVALID_FIELD;

	वापस reply(smp);
पूर्ण

अटल पूर्णांक subn_set_guidinfo(काष्ठा ib_smp *smp, काष्ठा ib_device *ibdev,
			     u8 port)
अणु
	काष्ठा qib_devdata *dd = dd_from_ibdev(ibdev);
	u32 startgx = 8 * be32_to_cpu(smp->attr_mod);
	__be64 *p = (__be64 *) smp->data;
	अचिन्हित pidx = port - 1; /* IB number port from 1, hdw from 0 */

	/* 32 blocks of 8 64-bit GUIDs per block */

	अगर (startgx == 0 && pidx < dd->num_pports) अणु
		काष्ठा qib_pportdata *ppd = dd->pport + pidx;
		काष्ठा qib_ibport *ibp = &ppd->ibport_data;
		अचिन्हित i;

		/* The first entry is पढ़ो-only. */
		क्रम (i = 1; i < QIB_GUIDS_PER_PORT; i++)
			ibp->guids[i - 1] = p[i];
	पूर्ण अन्यथा
		smp->status |= IB_SMP_INVALID_FIELD;

	/* The only GUID we support is the first पढ़ो-only entry. */
	वापस subn_get_guidinfo(smp, ibdev, port);
पूर्ण

/**
 * subn_set_portinfo - set port inक्रमmation
 * @smp: the incoming SM packet
 * @ibdev: the infiniband device
 * @port: the port on the device
 *
 * Set Portinfo (see ch. 14.2.5.6).
 */
अटल पूर्णांक subn_set_portinfo(काष्ठा ib_smp *smp, काष्ठा ib_device *ibdev,
			     u8 port)
अणु
	काष्ठा ib_port_info *pip = (काष्ठा ib_port_info *)smp->data;
	काष्ठा ib_event event;
	काष्ठा qib_devdata *dd;
	काष्ठा qib_pportdata *ppd;
	काष्ठा qib_ibport *ibp;
	u8 clientrereg = (pip->clientrereg_resv_subnetto & 0x80);
	अचिन्हित दीर्घ flags;
	u16 lid, smlid;
	u8 lwe;
	u8 lse;
	u8 state;
	u8 vls;
	u8 msl;
	u16 lstate;
	पूर्णांक ret, ore, mtu;
	u32 port_num = be32_to_cpu(smp->attr_mod);

	अगर (port_num == 0)
		port_num = port;
	अन्यथा अणु
		अगर (port_num > ibdev->phys_port_cnt)
			जाओ err;
		/* Port attributes can only be set on the receiving port */
		अगर (port_num != port)
			जाओ get_only;
	पूर्ण

	dd = dd_from_ibdev(ibdev);
	/* IB numbers ports from 1, hdw from 0 */
	ppd = dd->pport + (port_num - 1);
	ibp = &ppd->ibport_data;
	event.device = ibdev;
	event.element.port_num = port;

	ibp->rvp.mkey = pip->mkey;
	ibp->rvp.gid_prefix = pip->gid_prefix;
	ibp->rvp.mkey_lease_period = be16_to_cpu(pip->mkey_lease_period);

	lid = be16_to_cpu(pip->lid);
	/* Must be a valid unicast LID address. */
	अगर (lid == 0 || lid >= be16_to_cpu(IB_MULTICAST_LID_BASE))
		smp->status |= IB_SMP_INVALID_FIELD;
	अन्यथा अगर (ppd->lid != lid || ppd->lmc != (pip->mkeyprot_resv_lmc & 7)) अणु
		अगर (ppd->lid != lid)
			qib_set_uevent_bits(ppd, _QIB_EVENT_LID_CHANGE_BIT);
		अगर (ppd->lmc != (pip->mkeyprot_resv_lmc & 7))
			qib_set_uevent_bits(ppd, _QIB_EVENT_LMC_CHANGE_BIT);
		qib_set_lid(ppd, lid, pip->mkeyprot_resv_lmc & 7);
		event.event = IB_EVENT_LID_CHANGE;
		ib_dispatch_event(&event);
	पूर्ण

	smlid = be16_to_cpu(pip->sm_lid);
	msl = pip->neighbormtu_mastersmsl & 0xF;
	/* Must be a valid unicast LID address. */
	अगर (smlid == 0 || smlid >= be16_to_cpu(IB_MULTICAST_LID_BASE))
		smp->status |= IB_SMP_INVALID_FIELD;
	अन्यथा अगर (smlid != ibp->rvp.sm_lid || msl != ibp->rvp.sm_sl) अणु
		spin_lock_irqsave(&ibp->rvp.lock, flags);
		अगर (ibp->rvp.sm_ah) अणु
			अगर (smlid != ibp->rvp.sm_lid)
				rdma_ah_set_dlid(&ibp->rvp.sm_ah->attr,
						 smlid);
			अगर (msl != ibp->rvp.sm_sl)
				rdma_ah_set_sl(&ibp->rvp.sm_ah->attr, msl);
		पूर्ण
		spin_unlock_irqrestore(&ibp->rvp.lock, flags);
		अगर (smlid != ibp->rvp.sm_lid)
			ibp->rvp.sm_lid = smlid;
		अगर (msl != ibp->rvp.sm_sl)
			ibp->rvp.sm_sl = msl;
		event.event = IB_EVENT_SM_CHANGE;
		ib_dispatch_event(&event);
	पूर्ण

	/* Allow 1x or 4x to be set (see 14.2.6.6). */
	lwe = pip->link_width_enabled;
	अगर (lwe) अणु
		अगर (lwe == 0xFF)
			set_link_width_enabled(ppd, ppd->link_width_supported);
		अन्यथा अगर (lwe >= 16 || (lwe & ~ppd->link_width_supported))
			smp->status |= IB_SMP_INVALID_FIELD;
		अन्यथा अगर (lwe != ppd->link_width_enabled)
			set_link_width_enabled(ppd, lwe);
	पूर्ण

	lse = pip->linkspeedactive_enabled & 0xF;
	अगर (lse) अणु
		/*
		 * The IB 1.2 spec. only allows link speed values
		 * 1, 3, 5, 7, 15.  1.2.1 extended to allow specअगरic
		 * speeds.
		 */
		अगर (lse == 15)
			set_link_speed_enabled(ppd,
					       ppd->link_speed_supported);
		अन्यथा अगर (lse >= 8 || (lse & ~ppd->link_speed_supported))
			smp->status |= IB_SMP_INVALID_FIELD;
		अन्यथा अगर (lse != ppd->link_speed_enabled)
			set_link_speed_enabled(ppd, lse);
	पूर्ण

	/* Set link करोwn शेष state. */
	चयन (pip->portphysstate_linkकरोwn & 0xF) अणु
	हाल 0: /* NOP */
		अवरोध;
	हाल 1: /* SLEEP */
		(व्योम) dd->f_set_ib_cfg(ppd, QIB_IB_CFG_LINKDEFAULT,
					IB_LINKINITCMD_SLEEP);
		अवरोध;
	हाल 2: /* POLL */
		(व्योम) dd->f_set_ib_cfg(ppd, QIB_IB_CFG_LINKDEFAULT,
					IB_LINKINITCMD_POLL);
		अवरोध;
	शेष:
		smp->status |= IB_SMP_INVALID_FIELD;
	पूर्ण

	ibp->rvp.mkeyprot = pip->mkeyprot_resv_lmc >> 6;
	ibp->rvp.vl_high_limit = pip->vl_high_limit;
	(व्योम) dd->f_set_ib_cfg(ppd, QIB_IB_CFG_VL_HIGH_LIMIT,
				    ibp->rvp.vl_high_limit);

	mtu = ib_mtu_क्रमागत_to_पूर्णांक((pip->neighbormtu_mastersmsl >> 4) & 0xF);
	अगर (mtu == -1)
		smp->status |= IB_SMP_INVALID_FIELD;
	अन्यथा
		qib_set_mtu(ppd, mtu);

	/* Set operational VLs */
	vls = (pip->operationalvl_pei_peo_fpi_fpo >> 4) & 0xF;
	अगर (vls) अणु
		अगर (vls > ppd->vls_supported)
			smp->status |= IB_SMP_INVALID_FIELD;
		अन्यथा
			(व्योम) dd->f_set_ib_cfg(ppd, QIB_IB_CFG_OP_VLS, vls);
	पूर्ण

	अगर (pip->mkey_violations == 0)
		ibp->rvp.mkey_violations = 0;

	अगर (pip->pkey_violations == 0)
		ibp->rvp.pkey_violations = 0;

	अगर (pip->qkey_violations == 0)
		ibp->rvp.qkey_violations = 0;

	ore = pip->localphyerrors_overrunerrors;
	अगर (set_phyerrthreshold(ppd, (ore >> 4) & 0xF))
		smp->status |= IB_SMP_INVALID_FIELD;

	अगर (set_overrunthreshold(ppd, (ore & 0xF)))
		smp->status |= IB_SMP_INVALID_FIELD;

	ibp->rvp.subnet_समयout = pip->clientrereg_resv_subnetto & 0x1F;

	/*
	 * Do the port state change now that the other link parameters
	 * have been set.
	 * Changing the port physical state only makes sense अगर the link
	 * is करोwn or is being set to करोwn.
	 */
	state = pip->linkspeed_portstate & 0xF;
	lstate = (pip->portphysstate_linkकरोwn >> 4) & 0xF;
	अगर (lstate && !(state == IB_PORT_DOWN || state == IB_PORT_NOP))
		smp->status |= IB_SMP_INVALID_FIELD;

	/*
	 * Only state changes of DOWN, ARM, and ACTIVE are valid
	 * and must be in the correct state to take effect (see 7.2.6).
	 */
	चयन (state) अणु
	हाल IB_PORT_NOP:
		अगर (lstate == 0)
			अवरोध;
		fallthrough;
	हाल IB_PORT_DOWN:
		अगर (lstate == 0)
			lstate = QIB_IB_LINKDOWN_ONLY;
		अन्यथा अगर (lstate == 1)
			lstate = QIB_IB_LINKDOWN_SLEEP;
		अन्यथा अगर (lstate == 2)
			lstate = QIB_IB_LINKDOWN;
		अन्यथा अगर (lstate == 3)
			lstate = QIB_IB_LINKDOWN_DISABLE;
		अन्यथा अणु
			smp->status |= IB_SMP_INVALID_FIELD;
			अवरोध;
		पूर्ण
		spin_lock_irqsave(&ppd->lflags_lock, flags);
		ppd->lflags &= ~QIBL_LINKV;
		spin_unlock_irqrestore(&ppd->lflags_lock, flags);
		qib_set_linkstate(ppd, lstate);
		/*
		 * Don't send a reply अगर the response would be sent
		 * through the disabled port.
		 */
		अगर (lstate == QIB_IB_LINKDOWN_DISABLE && smp->hop_cnt) अणु
			ret = IB_MAD_RESULT_SUCCESS | IB_MAD_RESULT_CONSUMED;
			जाओ करोne;
		पूर्ण
		qib_रुको_linkstate(ppd, QIBL_LINKV, 10);
		अवरोध;
	हाल IB_PORT_ARMED:
		qib_set_linkstate(ppd, QIB_IB_LINKARM);
		अवरोध;
	हाल IB_PORT_ACTIVE:
		qib_set_linkstate(ppd, QIB_IB_LINKACTIVE);
		अवरोध;
	शेष:
		smp->status |= IB_SMP_INVALID_FIELD;
	पूर्ण

	अगर (clientrereg) अणु
		event.event = IB_EVENT_CLIENT_REREGISTER;
		ib_dispatch_event(&event);
	पूर्ण

	/* restore re-reg bit per o14-12.2.1 */
	pip->clientrereg_resv_subnetto |= clientrereg;

	जाओ get_only;

err:
	smp->status |= IB_SMP_INVALID_FIELD;
get_only:
	ret = subn_get_portinfo(smp, ibdev, port);
करोne:
	वापस ret;
पूर्ण

/**
 * rm_pkey - decrecment the reference count क्रम the given PKEY
 * @ppd: the qlogic_ib device
 * @key: the PKEY index
 *
 * Return true अगर this was the last reference and the hardware table entry
 * needs to be changed.
 */
अटल पूर्णांक rm_pkey(काष्ठा qib_pportdata *ppd, u16 key)
अणु
	पूर्णांक i;
	पूर्णांक ret;

	क्रम (i = 0; i < ARRAY_SIZE(ppd->pkeys); i++) अणु
		अगर (ppd->pkeys[i] != key)
			जारी;
		अगर (atomic_dec_and_test(&ppd->pkeyrefs[i])) अणु
			ppd->pkeys[i] = 0;
			ret = 1;
			जाओ bail;
		पूर्ण
		अवरोध;
	पूर्ण

	ret = 0;

bail:
	वापस ret;
पूर्ण

/**
 * add_pkey - add the given PKEY to the hardware table
 * @ppd: the qlogic_ib device
 * @key: the PKEY
 *
 * Return an error code अगर unable to add the entry, zero अगर no change,
 * or 1 अगर the hardware PKEY रेजिस्टर needs to be updated.
 */
अटल पूर्णांक add_pkey(काष्ठा qib_pportdata *ppd, u16 key)
अणु
	पूर्णांक i;
	u16 lkey = key & 0x7FFF;
	पूर्णांक any = 0;
	पूर्णांक ret;

	अगर (lkey == 0x7FFF) अणु
		ret = 0;
		जाओ bail;
	पूर्ण

	/* Look क्रम an empty slot or a matching PKEY. */
	क्रम (i = 0; i < ARRAY_SIZE(ppd->pkeys); i++) अणु
		अगर (!ppd->pkeys[i]) अणु
			any++;
			जारी;
		पूर्ण
		/* If it matches exactly, try to increment the ref count */
		अगर (ppd->pkeys[i] == key) अणु
			अगर (atomic_inc_वापस(&ppd->pkeyrefs[i]) > 1) अणु
				ret = 0;
				जाओ bail;
			पूर्ण
			/* Lost the race. Look क्रम an empty slot below. */
			atomic_dec(&ppd->pkeyrefs[i]);
			any++;
		पूर्ण
		/*
		 * It makes no sense to have both the limited and unlimited
		 * PKEY set at the same समय since the unlimited one will
		 * disable the limited one.
		 */
		अगर ((ppd->pkeys[i] & 0x7FFF) == lkey) अणु
			ret = -EEXIST;
			जाओ bail;
		पूर्ण
	पूर्ण
	अगर (!any) अणु
		ret = -EBUSY;
		जाओ bail;
	पूर्ण
	क्रम (i = 0; i < ARRAY_SIZE(ppd->pkeys); i++) अणु
		अगर (!ppd->pkeys[i] &&
		    atomic_inc_वापस(&ppd->pkeyrefs[i]) == 1) अणु
			/* क्रम qibstats, etc. */
			ppd->pkeys[i] = key;
			ret = 1;
			जाओ bail;
		पूर्ण
	पूर्ण
	ret = -EBUSY;

bail:
	वापस ret;
पूर्ण

/**
 * set_pkeys - set the PKEY table क्रम ctxt 0
 * @dd: the qlogic_ib device
 * @port: the IB port number
 * @pkeys: the PKEY table
 */
अटल पूर्णांक set_pkeys(काष्ठा qib_devdata *dd, u8 port, u16 *pkeys)
अणु
	काष्ठा qib_pportdata *ppd;
	काष्ठा qib_ctxtdata *rcd;
	पूर्णांक i;
	पूर्णांक changed = 0;

	/*
	 * IB port one/two always maps to context zero/one,
	 * always a kernel context, no locking needed
	 * If we get here with ppd setup, no need to check
	 * that rcd is valid.
	 */
	ppd = dd->pport + (port - 1);
	rcd = dd->rcd[ppd->hw_pidx];

	क्रम (i = 0; i < ARRAY_SIZE(rcd->pkeys); i++) अणु
		u16 key = pkeys[i];
		u16 okey = rcd->pkeys[i];

		अगर (key == okey)
			जारी;
		/*
		 * The value of this PKEY table entry is changing.
		 * Remove the old entry in the hardware's array of PKEYs.
		 */
		अगर (okey & 0x7FFF)
			changed |= rm_pkey(ppd, okey);
		अगर (key & 0x7FFF) अणु
			पूर्णांक ret = add_pkey(ppd, key);

			अगर (ret < 0)
				key = 0;
			अन्यथा
				changed |= ret;
		पूर्ण
		rcd->pkeys[i] = key;
	पूर्ण
	अगर (changed) अणु
		काष्ठा ib_event event;

		(व्योम) dd->f_set_ib_cfg(ppd, QIB_IB_CFG_PKEYS, 0);

		event.event = IB_EVENT_PKEY_CHANGE;
		event.device = &dd->verbs_dev.rdi.ibdev;
		event.element.port_num = port;
		ib_dispatch_event(&event);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक subn_set_pkeytable(काष्ठा ib_smp *smp, काष्ठा ib_device *ibdev,
			      u8 port)
अणु
	u32 startpx = 32 * (be32_to_cpu(smp->attr_mod) & 0xffff);
	__be16 *p = (__be16 *) smp->data;
	u16 *q = (u16 *) smp->data;
	काष्ठा qib_devdata *dd = dd_from_ibdev(ibdev);
	अचिन्हित i, n = qib_get_npkeys(dd);

	क्रम (i = 0; i < n; i++)
		q[i] = be16_to_cpu(p[i]);

	अगर (startpx != 0 || set_pkeys(dd, port, q) != 0)
		smp->status |= IB_SMP_INVALID_FIELD;

	वापस subn_get_pkeytable(smp, ibdev, port);
पूर्ण

अटल पूर्णांक subn_get_sl_to_vl(काष्ठा ib_smp *smp, काष्ठा ib_device *ibdev,
			     u8 port)
अणु
	काष्ठा qib_ibport *ibp = to_iport(ibdev, port);
	u8 *p = (u8 *) smp->data;
	अचिन्हित i;

	स_रखो(smp->data, 0, माप(smp->data));

	अगर (!(ibp->rvp.port_cap_flags & IB_PORT_SL_MAP_SUP))
		smp->status |= IB_SMP_UNSUP_METHOD;
	अन्यथा
		क्रम (i = 0; i < ARRAY_SIZE(ibp->sl_to_vl); i += 2)
			*p++ = (ibp->sl_to_vl[i] << 4) | ibp->sl_to_vl[i + 1];

	वापस reply(smp);
पूर्ण

अटल पूर्णांक subn_set_sl_to_vl(काष्ठा ib_smp *smp, काष्ठा ib_device *ibdev,
			     u8 port)
अणु
	काष्ठा qib_ibport *ibp = to_iport(ibdev, port);
	u8 *p = (u8 *) smp->data;
	अचिन्हित i;

	अगर (!(ibp->rvp.port_cap_flags & IB_PORT_SL_MAP_SUP)) अणु
		smp->status |= IB_SMP_UNSUP_METHOD;
		वापस reply(smp);
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(ibp->sl_to_vl); i += 2, p++) अणु
		ibp->sl_to_vl[i] = *p >> 4;
		ibp->sl_to_vl[i + 1] = *p & 0xF;
	पूर्ण
	qib_set_uevent_bits(ppd_from_ibp(to_iport(ibdev, port)),
			    _QIB_EVENT_SL2VL_CHANGE_BIT);

	वापस subn_get_sl_to_vl(smp, ibdev, port);
पूर्ण

अटल पूर्णांक subn_get_vl_arb(काष्ठा ib_smp *smp, काष्ठा ib_device *ibdev,
			   u8 port)
अणु
	अचिन्हित which = be32_to_cpu(smp->attr_mod) >> 16;
	काष्ठा qib_pportdata *ppd = ppd_from_ibp(to_iport(ibdev, port));

	स_रखो(smp->data, 0, माप(smp->data));

	अगर (ppd->vls_supported == IB_VL_VL0)
		smp->status |= IB_SMP_UNSUP_METHOD;
	अन्यथा अगर (which == IB_VLARB_LOWPRI_0_31)
		(व्योम) ppd->dd->f_get_ib_table(ppd, QIB_IB_TBL_VL_LOW_ARB,
						   smp->data);
	अन्यथा अगर (which == IB_VLARB_HIGHPRI_0_31)
		(व्योम) ppd->dd->f_get_ib_table(ppd, QIB_IB_TBL_VL_HIGH_ARB,
						   smp->data);
	अन्यथा
		smp->status |= IB_SMP_INVALID_FIELD;

	वापस reply(smp);
पूर्ण

अटल पूर्णांक subn_set_vl_arb(काष्ठा ib_smp *smp, काष्ठा ib_device *ibdev,
			   u8 port)
अणु
	अचिन्हित which = be32_to_cpu(smp->attr_mod) >> 16;
	काष्ठा qib_pportdata *ppd = ppd_from_ibp(to_iport(ibdev, port));

	अगर (ppd->vls_supported == IB_VL_VL0)
		smp->status |= IB_SMP_UNSUP_METHOD;
	अन्यथा अगर (which == IB_VLARB_LOWPRI_0_31)
		(व्योम) ppd->dd->f_set_ib_table(ppd, QIB_IB_TBL_VL_LOW_ARB,
						   smp->data);
	अन्यथा अगर (which == IB_VLARB_HIGHPRI_0_31)
		(व्योम) ppd->dd->f_set_ib_table(ppd, QIB_IB_TBL_VL_HIGH_ARB,
						   smp->data);
	अन्यथा
		smp->status |= IB_SMP_INVALID_FIELD;

	वापस subn_get_vl_arb(smp, ibdev, port);
पूर्ण

अटल पूर्णांक subn_trap_repress(काष्ठा ib_smp *smp, काष्ठा ib_device *ibdev,
			     u8 port)
अणु
	/*
	 * For now, we only send the trap once so no need to process this.
	 * o13-6, o13-7,
	 * o14-3.a4 The SMA shall not send any message in response to a valid
	 * SubnTrapRepress() message.
	 */
	वापस IB_MAD_RESULT_SUCCESS | IB_MAD_RESULT_CONSUMED;
पूर्ण

अटल पूर्णांक pma_get_classportinfo(काष्ठा ib_pma_mad *pmp,
				 काष्ठा ib_device *ibdev)
अणु
	काष्ठा ib_class_port_info *p =
		(काष्ठा ib_class_port_info *)pmp->data;
	काष्ठा qib_devdata *dd = dd_from_ibdev(ibdev);

	स_रखो(pmp->data, 0, माप(pmp->data));

	अगर (pmp->mad_hdr.attr_mod != 0)
		pmp->mad_hdr.status |= IB_SMP_INVALID_FIELD;

	/* Note that AllPortSelect is not valid */
	p->base_version = 1;
	p->class_version = 1;
	p->capability_mask = IB_PMA_CLASS_CAP_EXT_WIDTH;
	/*
	 * Set the most signअगरicant bit of CM2 to indicate support क्रम
	 * congestion statistics
	 */
	ib_set_cpi_capmask2(p,
			    dd->psxmitरुको_supported <<
			    (31 - IB_CLASS_PORT_INFO_RESP_TIME_FIELD_SIZE));
	/*
	 * Expected response समय is 4.096 usec. * 2^18 == 1.073741824 sec.
	 */
	ib_set_cpi_resp_समय(p, 18);

	वापस reply((काष्ठा ib_smp *) pmp);
पूर्ण

अटल पूर्णांक pma_get_portsamplescontrol(काष्ठा ib_pma_mad *pmp,
				      काष्ठा ib_device *ibdev, u8 port)
अणु
	काष्ठा ib_pma_portsamplescontrol *p =
		(काष्ठा ib_pma_portsamplescontrol *)pmp->data;
	काष्ठा qib_ibdev *dev = to_idev(ibdev);
	काष्ठा qib_devdata *dd = dd_from_dev(dev);
	काष्ठा qib_ibport *ibp = to_iport(ibdev, port);
	काष्ठा qib_pportdata *ppd = ppd_from_ibp(ibp);
	अचिन्हित दीर्घ flags;
	u8 port_select = p->port_select;

	स_रखो(pmp->data, 0, माप(pmp->data));

	p->port_select = port_select;
	अगर (pmp->mad_hdr.attr_mod != 0 || port_select != port) अणु
		pmp->mad_hdr.status |= IB_SMP_INVALID_FIELD;
		जाओ bail;
	पूर्ण
	spin_lock_irqsave(&ibp->rvp.lock, flags);
	p->tick = dd->f_get_ib_cfg(ppd, QIB_IB_CFG_PMA_TICKS);
	p->sample_status = dd->f_portcntr(ppd, QIBPORTCNTR_PSSTAT);
	p->counter_width = 4;   /* 32 bit counters */
	p->counter_mask0_9 = COUNTER_MASK0_9;
	p->sample_start = cpu_to_be32(ibp->rvp.pma_sample_start);
	p->sample_पूर्णांकerval = cpu_to_be32(ibp->rvp.pma_sample_पूर्णांकerval);
	p->tag = cpu_to_be16(ibp->rvp.pma_tag);
	p->counter_select[0] = ibp->rvp.pma_counter_select[0];
	p->counter_select[1] = ibp->rvp.pma_counter_select[1];
	p->counter_select[2] = ibp->rvp.pma_counter_select[2];
	p->counter_select[3] = ibp->rvp.pma_counter_select[3];
	p->counter_select[4] = ibp->rvp.pma_counter_select[4];
	spin_unlock_irqrestore(&ibp->rvp.lock, flags);

bail:
	वापस reply((काष्ठा ib_smp *) pmp);
पूर्ण

अटल पूर्णांक pma_set_portsamplescontrol(काष्ठा ib_pma_mad *pmp,
				      काष्ठा ib_device *ibdev, u8 port)
अणु
	काष्ठा ib_pma_portsamplescontrol *p =
		(काष्ठा ib_pma_portsamplescontrol *)pmp->data;
	काष्ठा qib_ibdev *dev = to_idev(ibdev);
	काष्ठा qib_devdata *dd = dd_from_dev(dev);
	काष्ठा qib_ibport *ibp = to_iport(ibdev, port);
	काष्ठा qib_pportdata *ppd = ppd_from_ibp(ibp);
	अचिन्हित दीर्घ flags;
	u8 status, xmit_flags;
	पूर्णांक ret;

	अगर (pmp->mad_hdr.attr_mod != 0 || p->port_select != port) अणु
		pmp->mad_hdr.status |= IB_SMP_INVALID_FIELD;
		ret = reply((काष्ठा ib_smp *) pmp);
		जाओ bail;
	पूर्ण

	spin_lock_irqsave(&ibp->rvp.lock, flags);

	/* Port Sampling code owns the PS* HW counters */
	xmit_flags = ppd->cong_stats.flags;
	ppd->cong_stats.flags = IB_PMA_CONG_HW_CONTROL_SAMPLE;
	status = dd->f_portcntr(ppd, QIBPORTCNTR_PSSTAT);
	अगर (status == IB_PMA_SAMPLE_STATUS_DONE ||
	    (status == IB_PMA_SAMPLE_STATUS_RUNNING &&
	     xmit_flags == IB_PMA_CONG_HW_CONTROL_TIMER)) अणु
		ibp->rvp.pma_sample_start = be32_to_cpu(p->sample_start);
		ibp->rvp.pma_sample_पूर्णांकerval = be32_to_cpu(p->sample_पूर्णांकerval);
		ibp->rvp.pma_tag = be16_to_cpu(p->tag);
		ibp->rvp.pma_counter_select[0] = p->counter_select[0];
		ibp->rvp.pma_counter_select[1] = p->counter_select[1];
		ibp->rvp.pma_counter_select[2] = p->counter_select[2];
		ibp->rvp.pma_counter_select[3] = p->counter_select[3];
		ibp->rvp.pma_counter_select[4] = p->counter_select[4];
		dd->f_set_cntr_sample(ppd, ibp->rvp.pma_sample_पूर्णांकerval,
				      ibp->rvp.pma_sample_start);
	पूर्ण
	spin_unlock_irqrestore(&ibp->rvp.lock, flags);

	ret = pma_get_portsamplescontrol(pmp, ibdev, port);

bail:
	वापस ret;
पूर्ण

अटल u64 get_counter(काष्ठा qib_ibport *ibp, काष्ठा qib_pportdata *ppd,
		       __be16 sel)
अणु
	u64 ret;

	चयन (sel) अणु
	हाल IB_PMA_PORT_XMIT_DATA:
		ret = ppd->dd->f_portcntr(ppd, QIBPORTCNTR_PSXMITDATA);
		अवरोध;
	हाल IB_PMA_PORT_RCV_DATA:
		ret = ppd->dd->f_portcntr(ppd, QIBPORTCNTR_PSRCVDATA);
		अवरोध;
	हाल IB_PMA_PORT_XMIT_PKTS:
		ret = ppd->dd->f_portcntr(ppd, QIBPORTCNTR_PSXMITPKTS);
		अवरोध;
	हाल IB_PMA_PORT_RCV_PKTS:
		ret = ppd->dd->f_portcntr(ppd, QIBPORTCNTR_PSRCVPKTS);
		अवरोध;
	हाल IB_PMA_PORT_XMIT_WAIT:
		ret = ppd->dd->f_portcntr(ppd, QIBPORTCNTR_PSXMITWAIT);
		अवरोध;
	शेष:
		ret = 0;
	पूर्ण

	वापस ret;
पूर्ण

/* This function assumes that the xmit_रुको lock is alपढ़ोy held */
अटल u64 xmit_रुको_get_value_delta(काष्ठा qib_pportdata *ppd)
अणु
	u32 delta;

	delta = get_counter(&ppd->ibport_data, ppd,
			    IB_PMA_PORT_XMIT_WAIT);
	वापस ppd->cong_stats.counter + delta;
पूर्ण

अटल व्योम cache_hw_sample_counters(काष्ठा qib_pportdata *ppd)
अणु
	काष्ठा qib_ibport *ibp = &ppd->ibport_data;

	ppd->cong_stats.counter_cache.psxmitdata =
		get_counter(ibp, ppd, IB_PMA_PORT_XMIT_DATA);
	ppd->cong_stats.counter_cache.psrcvdata =
		get_counter(ibp, ppd, IB_PMA_PORT_RCV_DATA);
	ppd->cong_stats.counter_cache.psxmitpkts =
		get_counter(ibp, ppd, IB_PMA_PORT_XMIT_PKTS);
	ppd->cong_stats.counter_cache.psrcvpkts =
		get_counter(ibp, ppd, IB_PMA_PORT_RCV_PKTS);
	ppd->cong_stats.counter_cache.psxmitरुको =
		get_counter(ibp, ppd, IB_PMA_PORT_XMIT_WAIT);
पूर्ण

अटल u64 get_cache_hw_sample_counters(काष्ठा qib_pportdata *ppd,
					__be16 sel)
अणु
	u64 ret;

	चयन (sel) अणु
	हाल IB_PMA_PORT_XMIT_DATA:
		ret = ppd->cong_stats.counter_cache.psxmitdata;
		अवरोध;
	हाल IB_PMA_PORT_RCV_DATA:
		ret = ppd->cong_stats.counter_cache.psrcvdata;
		अवरोध;
	हाल IB_PMA_PORT_XMIT_PKTS:
		ret = ppd->cong_stats.counter_cache.psxmitpkts;
		अवरोध;
	हाल IB_PMA_PORT_RCV_PKTS:
		ret = ppd->cong_stats.counter_cache.psrcvpkts;
		अवरोध;
	हाल IB_PMA_PORT_XMIT_WAIT:
		ret = ppd->cong_stats.counter_cache.psxmitरुको;
		अवरोध;
	शेष:
		ret = 0;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक pma_get_portsamplesresult(काष्ठा ib_pma_mad *pmp,
				     काष्ठा ib_device *ibdev, u8 port)
अणु
	काष्ठा ib_pma_portsamplesresult *p =
		(काष्ठा ib_pma_portsamplesresult *)pmp->data;
	काष्ठा qib_ibdev *dev = to_idev(ibdev);
	काष्ठा qib_devdata *dd = dd_from_dev(dev);
	काष्ठा qib_ibport *ibp = to_iport(ibdev, port);
	काष्ठा qib_pportdata *ppd = ppd_from_ibp(ibp);
	अचिन्हित दीर्घ flags;
	u8 status;
	पूर्णांक i;

	स_रखो(pmp->data, 0, माप(pmp->data));
	spin_lock_irqsave(&ibp->rvp.lock, flags);
	p->tag = cpu_to_be16(ibp->rvp.pma_tag);
	अगर (ppd->cong_stats.flags == IB_PMA_CONG_HW_CONTROL_TIMER)
		p->sample_status = IB_PMA_SAMPLE_STATUS_DONE;
	अन्यथा अणु
		status = dd->f_portcntr(ppd, QIBPORTCNTR_PSSTAT);
		p->sample_status = cpu_to_be16(status);
		अगर (status == IB_PMA_SAMPLE_STATUS_DONE) अणु
			cache_hw_sample_counters(ppd);
			ppd->cong_stats.counter =
				xmit_रुको_get_value_delta(ppd);
			dd->f_set_cntr_sample(ppd,
					      QIB_CONG_TIMER_PSINTERVAL, 0);
			ppd->cong_stats.flags = IB_PMA_CONG_HW_CONTROL_TIMER;
		पूर्ण
	पूर्ण
	क्रम (i = 0; i < ARRAY_SIZE(ibp->rvp.pma_counter_select); i++)
		p->counter[i] = cpu_to_be32(
			get_cache_hw_sample_counters(
				ppd, ibp->rvp.pma_counter_select[i]));
	spin_unlock_irqrestore(&ibp->rvp.lock, flags);

	वापस reply((काष्ठा ib_smp *) pmp);
पूर्ण

अटल पूर्णांक pma_get_portsamplesresult_ext(काष्ठा ib_pma_mad *pmp,
					 काष्ठा ib_device *ibdev, u8 port)
अणु
	काष्ठा ib_pma_portsamplesresult_ext *p =
		(काष्ठा ib_pma_portsamplesresult_ext *)pmp->data;
	काष्ठा qib_ibdev *dev = to_idev(ibdev);
	काष्ठा qib_devdata *dd = dd_from_dev(dev);
	काष्ठा qib_ibport *ibp = to_iport(ibdev, port);
	काष्ठा qib_pportdata *ppd = ppd_from_ibp(ibp);
	अचिन्हित दीर्घ flags;
	u8 status;
	पूर्णांक i;

	/* Port Sampling code owns the PS* HW counters */
	स_रखो(pmp->data, 0, माप(pmp->data));
	spin_lock_irqsave(&ibp->rvp.lock, flags);
	p->tag = cpu_to_be16(ibp->rvp.pma_tag);
	अगर (ppd->cong_stats.flags == IB_PMA_CONG_HW_CONTROL_TIMER)
		p->sample_status = IB_PMA_SAMPLE_STATUS_DONE;
	अन्यथा अणु
		status = dd->f_portcntr(ppd, QIBPORTCNTR_PSSTAT);
		p->sample_status = cpu_to_be16(status);
		/* 64 bits */
		p->extended_width = cpu_to_be32(0x80000000);
		अगर (status == IB_PMA_SAMPLE_STATUS_DONE) अणु
			cache_hw_sample_counters(ppd);
			ppd->cong_stats.counter =
				xmit_रुको_get_value_delta(ppd);
			dd->f_set_cntr_sample(ppd,
					      QIB_CONG_TIMER_PSINTERVAL, 0);
			ppd->cong_stats.flags = IB_PMA_CONG_HW_CONTROL_TIMER;
		पूर्ण
	पूर्ण
	क्रम (i = 0; i < ARRAY_SIZE(ibp->rvp.pma_counter_select); i++)
		p->counter[i] = cpu_to_be64(
			get_cache_hw_sample_counters(
				ppd, ibp->rvp.pma_counter_select[i]));
	spin_unlock_irqrestore(&ibp->rvp.lock, flags);

	वापस reply((काष्ठा ib_smp *) pmp);
पूर्ण

अटल पूर्णांक pma_get_portcounters(काष्ठा ib_pma_mad *pmp,
				काष्ठा ib_device *ibdev, u8 port)
अणु
	काष्ठा ib_pma_portcounters *p = (काष्ठा ib_pma_portcounters *)
		pmp->data;
	काष्ठा qib_ibport *ibp = to_iport(ibdev, port);
	काष्ठा qib_pportdata *ppd = ppd_from_ibp(ibp);
	काष्ठा qib_verbs_counters cntrs;
	u8 port_select = p->port_select;

	qib_get_counters(ppd, &cntrs);

	/* Adjust counters क्रम any resets करोne. */
	cntrs.symbol_error_counter -= ibp->z_symbol_error_counter;
	cntrs.link_error_recovery_counter -=
		ibp->z_link_error_recovery_counter;
	cntrs.link_करोwned_counter -= ibp->z_link_करोwned_counter;
	cntrs.port_rcv_errors -= ibp->z_port_rcv_errors;
	cntrs.port_rcv_remphys_errors -= ibp->z_port_rcv_remphys_errors;
	cntrs.port_xmit_discards -= ibp->z_port_xmit_discards;
	cntrs.port_xmit_data -= ibp->z_port_xmit_data;
	cntrs.port_rcv_data -= ibp->z_port_rcv_data;
	cntrs.port_xmit_packets -= ibp->z_port_xmit_packets;
	cntrs.port_rcv_packets -= ibp->z_port_rcv_packets;
	cntrs.local_link_पूर्णांकegrity_errors -=
		ibp->z_local_link_पूर्णांकegrity_errors;
	cntrs.excessive_buffer_overrun_errors -=
		ibp->z_excessive_buffer_overrun_errors;
	cntrs.vl15_dropped -= ibp->z_vl15_dropped;
	cntrs.vl15_dropped += ibp->rvp.n_vl15_dropped;

	स_रखो(pmp->data, 0, माप(pmp->data));

	p->port_select = port_select;
	अगर (pmp->mad_hdr.attr_mod != 0 || port_select != port)
		pmp->mad_hdr.status |= IB_SMP_INVALID_FIELD;

	अगर (cntrs.symbol_error_counter > 0xFFFFUL)
		p->symbol_error_counter = cpu_to_be16(0xFFFF);
	अन्यथा
		p->symbol_error_counter =
			cpu_to_be16((u16)cntrs.symbol_error_counter);
	अगर (cntrs.link_error_recovery_counter > 0xFFUL)
		p->link_error_recovery_counter = 0xFF;
	अन्यथा
		p->link_error_recovery_counter =
			(u8)cntrs.link_error_recovery_counter;
	अगर (cntrs.link_करोwned_counter > 0xFFUL)
		p->link_करोwned_counter = 0xFF;
	अन्यथा
		p->link_करोwned_counter = (u8)cntrs.link_करोwned_counter;
	अगर (cntrs.port_rcv_errors > 0xFFFFUL)
		p->port_rcv_errors = cpu_to_be16(0xFFFF);
	अन्यथा
		p->port_rcv_errors =
			cpu_to_be16((u16) cntrs.port_rcv_errors);
	अगर (cntrs.port_rcv_remphys_errors > 0xFFFFUL)
		p->port_rcv_remphys_errors = cpu_to_be16(0xFFFF);
	अन्यथा
		p->port_rcv_remphys_errors =
			cpu_to_be16((u16)cntrs.port_rcv_remphys_errors);
	अगर (cntrs.port_xmit_discards > 0xFFFFUL)
		p->port_xmit_discards = cpu_to_be16(0xFFFF);
	अन्यथा
		p->port_xmit_discards =
			cpu_to_be16((u16)cntrs.port_xmit_discards);
	अगर (cntrs.local_link_पूर्णांकegrity_errors > 0xFUL)
		cntrs.local_link_पूर्णांकegrity_errors = 0xFUL;
	अगर (cntrs.excessive_buffer_overrun_errors > 0xFUL)
		cntrs.excessive_buffer_overrun_errors = 0xFUL;
	p->link_overrun_errors = (cntrs.local_link_पूर्णांकegrity_errors << 4) |
		cntrs.excessive_buffer_overrun_errors;
	अगर (cntrs.vl15_dropped > 0xFFFFUL)
		p->vl15_dropped = cpu_to_be16(0xFFFF);
	अन्यथा
		p->vl15_dropped = cpu_to_be16((u16)cntrs.vl15_dropped);
	अगर (cntrs.port_xmit_data > 0xFFFFFFFFUL)
		p->port_xmit_data = cpu_to_be32(0xFFFFFFFF);
	अन्यथा
		p->port_xmit_data = cpu_to_be32((u32)cntrs.port_xmit_data);
	अगर (cntrs.port_rcv_data > 0xFFFFFFFFUL)
		p->port_rcv_data = cpu_to_be32(0xFFFFFFFF);
	अन्यथा
		p->port_rcv_data = cpu_to_be32((u32)cntrs.port_rcv_data);
	अगर (cntrs.port_xmit_packets > 0xFFFFFFFFUL)
		p->port_xmit_packets = cpu_to_be32(0xFFFFFFFF);
	अन्यथा
		p->port_xmit_packets =
			cpu_to_be32((u32)cntrs.port_xmit_packets);
	अगर (cntrs.port_rcv_packets > 0xFFFFFFFFUL)
		p->port_rcv_packets = cpu_to_be32(0xFFFFFFFF);
	अन्यथा
		p->port_rcv_packets =
			cpu_to_be32((u32) cntrs.port_rcv_packets);

	वापस reply((काष्ठा ib_smp *) pmp);
पूर्ण

अटल पूर्णांक pma_get_portcounters_cong(काष्ठा ib_pma_mad *pmp,
				     काष्ठा ib_device *ibdev, u8 port)
अणु
	/* Congestion PMA packets start at offset 24 not 64 */
	काष्ठा ib_pma_portcounters_cong *p =
		(काष्ठा ib_pma_portcounters_cong *)pmp->reserved;
	काष्ठा qib_verbs_counters cntrs;
	काष्ठा qib_ibport *ibp = to_iport(ibdev, port);
	काष्ठा qib_pportdata *ppd = ppd_from_ibp(ibp);
	काष्ठा qib_devdata *dd = dd_from_ppd(ppd);
	u32 port_select = be32_to_cpu(pmp->mad_hdr.attr_mod) & 0xFF;
	u64 xmit_रुको_counter;
	अचिन्हित दीर्घ flags;

	/*
	 * This check is perक्रमmed only in the GET method because the
	 * SET method ends up calling this anyway.
	 */
	अगर (!dd->psxmitरुको_supported)
		pmp->mad_hdr.status |= IB_SMP_UNSUP_METH_ATTR;
	अगर (port_select != port)
		pmp->mad_hdr.status |= IB_SMP_INVALID_FIELD;

	qib_get_counters(ppd, &cntrs);
	spin_lock_irqsave(&ppd->ibport_data.rvp.lock, flags);
	xmit_रुको_counter = xmit_रुको_get_value_delta(ppd);
	spin_unlock_irqrestore(&ppd->ibport_data.rvp.lock, flags);

	/* Adjust counters क्रम any resets करोne. */
	cntrs.symbol_error_counter -= ibp->z_symbol_error_counter;
	cntrs.link_error_recovery_counter -=
		ibp->z_link_error_recovery_counter;
	cntrs.link_करोwned_counter -= ibp->z_link_करोwned_counter;
	cntrs.port_rcv_errors -= ibp->z_port_rcv_errors;
	cntrs.port_rcv_remphys_errors -=
		ibp->z_port_rcv_remphys_errors;
	cntrs.port_xmit_discards -= ibp->z_port_xmit_discards;
	cntrs.local_link_पूर्णांकegrity_errors -=
		ibp->z_local_link_पूर्णांकegrity_errors;
	cntrs.excessive_buffer_overrun_errors -=
		ibp->z_excessive_buffer_overrun_errors;
	cntrs.vl15_dropped -= ibp->z_vl15_dropped;
	cntrs.vl15_dropped += ibp->rvp.n_vl15_dropped;
	cntrs.port_xmit_data -= ibp->z_port_xmit_data;
	cntrs.port_rcv_data -= ibp->z_port_rcv_data;
	cntrs.port_xmit_packets -= ibp->z_port_xmit_packets;
	cntrs.port_rcv_packets -= ibp->z_port_rcv_packets;

	स_रखो(pmp->reserved, 0, माप(pmp->reserved));
	स_रखो(pmp->data, 0, माप(pmp->data));

	/*
	 * Set top 3 bits to indicate पूर्णांकerval in picoseconds in
	 * reमुख्यing bits.
	 */
	p->port_check_rate =
		cpu_to_be16((QIB_XMIT_RATE_PICO << 13) |
			    (dd->psxmitरुको_check_rate &
			     ~(QIB_XMIT_RATE_PICO << 13)));
	p->port_adr_events = cpu_to_be64(0);
	p->port_xmit_रुको = cpu_to_be64(xmit_रुको_counter);
	p->port_xmit_data = cpu_to_be64(cntrs.port_xmit_data);
	p->port_rcv_data = cpu_to_be64(cntrs.port_rcv_data);
	p->port_xmit_packets =
		cpu_to_be64(cntrs.port_xmit_packets);
	p->port_rcv_packets =
		cpu_to_be64(cntrs.port_rcv_packets);
	अगर (cntrs.symbol_error_counter > 0xFFFFUL)
		p->symbol_error_counter = cpu_to_be16(0xFFFF);
	अन्यथा
		p->symbol_error_counter =
			cpu_to_be16(
				(u16)cntrs.symbol_error_counter);
	अगर (cntrs.link_error_recovery_counter > 0xFFUL)
		p->link_error_recovery_counter = 0xFF;
	अन्यथा
		p->link_error_recovery_counter =
			(u8)cntrs.link_error_recovery_counter;
	अगर (cntrs.link_करोwned_counter > 0xFFUL)
		p->link_करोwned_counter = 0xFF;
	अन्यथा
		p->link_करोwned_counter =
			(u8)cntrs.link_करोwned_counter;
	अगर (cntrs.port_rcv_errors > 0xFFFFUL)
		p->port_rcv_errors = cpu_to_be16(0xFFFF);
	अन्यथा
		p->port_rcv_errors =
			cpu_to_be16((u16) cntrs.port_rcv_errors);
	अगर (cntrs.port_rcv_remphys_errors > 0xFFFFUL)
		p->port_rcv_remphys_errors = cpu_to_be16(0xFFFF);
	अन्यथा
		p->port_rcv_remphys_errors =
			cpu_to_be16(
				(u16)cntrs.port_rcv_remphys_errors);
	अगर (cntrs.port_xmit_discards > 0xFFFFUL)
		p->port_xmit_discards = cpu_to_be16(0xFFFF);
	अन्यथा
		p->port_xmit_discards =
			cpu_to_be16((u16)cntrs.port_xmit_discards);
	अगर (cntrs.local_link_पूर्णांकegrity_errors > 0xFUL)
		cntrs.local_link_पूर्णांकegrity_errors = 0xFUL;
	अगर (cntrs.excessive_buffer_overrun_errors > 0xFUL)
		cntrs.excessive_buffer_overrun_errors = 0xFUL;
	p->link_overrun_errors = (cntrs.local_link_पूर्णांकegrity_errors << 4) |
		cntrs.excessive_buffer_overrun_errors;
	अगर (cntrs.vl15_dropped > 0xFFFFUL)
		p->vl15_dropped = cpu_to_be16(0xFFFF);
	अन्यथा
		p->vl15_dropped = cpu_to_be16((u16)cntrs.vl15_dropped);

	वापस reply((काष्ठा ib_smp *)pmp);
पूर्ण

अटल व्योम qib_snapshot_pmacounters(
	काष्ठा qib_ibport *ibp,
	काष्ठा qib_pma_counters *pmacounters)
अणु
	काष्ठा qib_pma_counters *p;
	पूर्णांक cpu;

	स_रखो(pmacounters, 0, माप(*pmacounters));
	क्रम_each_possible_cpu(cpu) अणु
		p = per_cpu_ptr(ibp->pmastats, cpu);
		pmacounters->n_unicast_xmit += p->n_unicast_xmit;
		pmacounters->n_unicast_rcv += p->n_unicast_rcv;
		pmacounters->n_multicast_xmit += p->n_multicast_xmit;
		pmacounters->n_multicast_rcv += p->n_multicast_rcv;
	पूर्ण
पूर्ण

अटल पूर्णांक pma_get_portcounters_ext(काष्ठा ib_pma_mad *pmp,
				    काष्ठा ib_device *ibdev, u8 port)
अणु
	काष्ठा ib_pma_portcounters_ext *p =
		(काष्ठा ib_pma_portcounters_ext *)pmp->data;
	काष्ठा qib_ibport *ibp = to_iport(ibdev, port);
	काष्ठा qib_pportdata *ppd = ppd_from_ibp(ibp);
	u64 swords, rwords, spkts, rpkts, xरुको;
	काष्ठा qib_pma_counters pma;
	u8 port_select = p->port_select;

	स_रखो(pmp->data, 0, माप(pmp->data));

	p->port_select = port_select;
	अगर (pmp->mad_hdr.attr_mod != 0 || port_select != port) अणु
		pmp->mad_hdr.status |= IB_SMP_INVALID_FIELD;
		जाओ bail;
	पूर्ण

	qib_snapshot_counters(ppd, &swords, &rwords, &spkts, &rpkts, &xरुको);

	/* Adjust counters क्रम any resets करोne. */
	swords -= ibp->z_port_xmit_data;
	rwords -= ibp->z_port_rcv_data;
	spkts -= ibp->z_port_xmit_packets;
	rpkts -= ibp->z_port_rcv_packets;

	p->port_xmit_data = cpu_to_be64(swords);
	p->port_rcv_data = cpu_to_be64(rwords);
	p->port_xmit_packets = cpu_to_be64(spkts);
	p->port_rcv_packets = cpu_to_be64(rpkts);

	qib_snapshot_pmacounters(ibp, &pma);

	p->port_unicast_xmit_packets = cpu_to_be64(pma.n_unicast_xmit
		- ibp->z_unicast_xmit);
	p->port_unicast_rcv_packets = cpu_to_be64(pma.n_unicast_rcv
		- ibp->z_unicast_rcv);
	p->port_multicast_xmit_packets = cpu_to_be64(pma.n_multicast_xmit
		- ibp->z_multicast_xmit);
	p->port_multicast_rcv_packets = cpu_to_be64(pma.n_multicast_rcv
		- ibp->z_multicast_rcv);

bail:
	वापस reply((काष्ठा ib_smp *) pmp);
पूर्ण

अटल पूर्णांक pma_set_portcounters(काष्ठा ib_pma_mad *pmp,
				काष्ठा ib_device *ibdev, u8 port)
अणु
	काष्ठा ib_pma_portcounters *p = (काष्ठा ib_pma_portcounters *)
		pmp->data;
	काष्ठा qib_ibport *ibp = to_iport(ibdev, port);
	काष्ठा qib_pportdata *ppd = ppd_from_ibp(ibp);
	काष्ठा qib_verbs_counters cntrs;

	/*
	 * Since the HW करोesn't support clearing counters, we save the
	 * current count and subtract it from future responses.
	 */
	qib_get_counters(ppd, &cntrs);

	अगर (p->counter_select & IB_PMA_SEL_SYMBOL_ERROR)
		ibp->z_symbol_error_counter = cntrs.symbol_error_counter;

	अगर (p->counter_select & IB_PMA_SEL_LINK_ERROR_RECOVERY)
		ibp->z_link_error_recovery_counter =
			cntrs.link_error_recovery_counter;

	अगर (p->counter_select & IB_PMA_SEL_LINK_DOWNED)
		ibp->z_link_करोwned_counter = cntrs.link_करोwned_counter;

	अगर (p->counter_select & IB_PMA_SEL_PORT_RCV_ERRORS)
		ibp->z_port_rcv_errors = cntrs.port_rcv_errors;

	अगर (p->counter_select & IB_PMA_SEL_PORT_RCV_REMPHYS_ERRORS)
		ibp->z_port_rcv_remphys_errors =
			cntrs.port_rcv_remphys_errors;

	अगर (p->counter_select & IB_PMA_SEL_PORT_XMIT_DISCARDS)
		ibp->z_port_xmit_discards = cntrs.port_xmit_discards;

	अगर (p->counter_select & IB_PMA_SEL_LOCAL_LINK_INTEGRITY_ERRORS)
		ibp->z_local_link_पूर्णांकegrity_errors =
			cntrs.local_link_पूर्णांकegrity_errors;

	अगर (p->counter_select & IB_PMA_SEL_EXCESSIVE_BUFFER_OVERRUNS)
		ibp->z_excessive_buffer_overrun_errors =
			cntrs.excessive_buffer_overrun_errors;

	अगर (p->counter_select & IB_PMA_SEL_PORT_VL15_DROPPED) अणु
		ibp->rvp.n_vl15_dropped = 0;
		ibp->z_vl15_dropped = cntrs.vl15_dropped;
	पूर्ण

	अगर (p->counter_select & IB_PMA_SEL_PORT_XMIT_DATA)
		ibp->z_port_xmit_data = cntrs.port_xmit_data;

	अगर (p->counter_select & IB_PMA_SEL_PORT_RCV_DATA)
		ibp->z_port_rcv_data = cntrs.port_rcv_data;

	अगर (p->counter_select & IB_PMA_SEL_PORT_XMIT_PACKETS)
		ibp->z_port_xmit_packets = cntrs.port_xmit_packets;

	अगर (p->counter_select & IB_PMA_SEL_PORT_RCV_PACKETS)
		ibp->z_port_rcv_packets = cntrs.port_rcv_packets;

	वापस pma_get_portcounters(pmp, ibdev, port);
पूर्ण

अटल पूर्णांक pma_set_portcounters_cong(काष्ठा ib_pma_mad *pmp,
				     काष्ठा ib_device *ibdev, u8 port)
अणु
	काष्ठा qib_ibport *ibp = to_iport(ibdev, port);
	काष्ठा qib_pportdata *ppd = ppd_from_ibp(ibp);
	काष्ठा qib_devdata *dd = dd_from_ppd(ppd);
	काष्ठा qib_verbs_counters cntrs;
	u32 counter_select = (be32_to_cpu(pmp->mad_hdr.attr_mod) >> 24) & 0xFF;
	पूर्णांक ret = 0;
	अचिन्हित दीर्घ flags;

	qib_get_counters(ppd, &cntrs);
	/* Get counter values beक्रमe we save them */
	ret = pma_get_portcounters_cong(pmp, ibdev, port);

	अगर (counter_select & IB_PMA_SEL_CONG_XMIT) अणु
		spin_lock_irqsave(&ppd->ibport_data.rvp.lock, flags);
		ppd->cong_stats.counter = 0;
		dd->f_set_cntr_sample(ppd, QIB_CONG_TIMER_PSINTERVAL,
				      0x0);
		spin_unlock_irqrestore(&ppd->ibport_data.rvp.lock, flags);
	पूर्ण
	अगर (counter_select & IB_PMA_SEL_CONG_PORT_DATA) अणु
		ibp->z_port_xmit_data = cntrs.port_xmit_data;
		ibp->z_port_rcv_data = cntrs.port_rcv_data;
		ibp->z_port_xmit_packets = cntrs.port_xmit_packets;
		ibp->z_port_rcv_packets = cntrs.port_rcv_packets;
	पूर्ण
	अगर (counter_select & IB_PMA_SEL_CONG_ALL) अणु
		ibp->z_symbol_error_counter =
			cntrs.symbol_error_counter;
		ibp->z_link_error_recovery_counter =
			cntrs.link_error_recovery_counter;
		ibp->z_link_करोwned_counter =
			cntrs.link_करोwned_counter;
		ibp->z_port_rcv_errors = cntrs.port_rcv_errors;
		ibp->z_port_rcv_remphys_errors =
			cntrs.port_rcv_remphys_errors;
		ibp->z_port_xmit_discards =
			cntrs.port_xmit_discards;
		ibp->z_local_link_पूर्णांकegrity_errors =
			cntrs.local_link_पूर्णांकegrity_errors;
		ibp->z_excessive_buffer_overrun_errors =
			cntrs.excessive_buffer_overrun_errors;
		ibp->rvp.n_vl15_dropped = 0;
		ibp->z_vl15_dropped = cntrs.vl15_dropped;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक pma_set_portcounters_ext(काष्ठा ib_pma_mad *pmp,
				    काष्ठा ib_device *ibdev, u8 port)
अणु
	काष्ठा ib_pma_portcounters *p = (काष्ठा ib_pma_portcounters *)
		pmp->data;
	काष्ठा qib_ibport *ibp = to_iport(ibdev, port);
	काष्ठा qib_pportdata *ppd = ppd_from_ibp(ibp);
	u64 swords, rwords, spkts, rpkts, xरुको;
	काष्ठा qib_pma_counters pma;

	qib_snapshot_counters(ppd, &swords, &rwords, &spkts, &rpkts, &xरुको);

	अगर (p->counter_select & IB_PMA_SELX_PORT_XMIT_DATA)
		ibp->z_port_xmit_data = swords;

	अगर (p->counter_select & IB_PMA_SELX_PORT_RCV_DATA)
		ibp->z_port_rcv_data = rwords;

	अगर (p->counter_select & IB_PMA_SELX_PORT_XMIT_PACKETS)
		ibp->z_port_xmit_packets = spkts;

	अगर (p->counter_select & IB_PMA_SELX_PORT_RCV_PACKETS)
		ibp->z_port_rcv_packets = rpkts;

	qib_snapshot_pmacounters(ibp, &pma);

	अगर (p->counter_select & IB_PMA_SELX_PORT_UNI_XMIT_PACKETS)
		ibp->z_unicast_xmit = pma.n_unicast_xmit;

	अगर (p->counter_select & IB_PMA_SELX_PORT_UNI_RCV_PACKETS)
		ibp->z_unicast_rcv = pma.n_unicast_rcv;

	अगर (p->counter_select & IB_PMA_SELX_PORT_MULTI_XMIT_PACKETS)
		ibp->z_multicast_xmit = pma.n_multicast_xmit;

	अगर (p->counter_select & IB_PMA_SELX_PORT_MULTI_RCV_PACKETS)
		ibp->z_multicast_rcv = pma.n_multicast_rcv;

	वापस pma_get_portcounters_ext(pmp, ibdev, port);
पूर्ण

अटल पूर्णांक process_subn(काष्ठा ib_device *ibdev, पूर्णांक mad_flags,
			u8 port, स्थिर काष्ठा ib_mad *in_mad,
			काष्ठा ib_mad *out_mad)
अणु
	काष्ठा ib_smp *smp = (काष्ठा ib_smp *)out_mad;
	काष्ठा qib_ibport *ibp = to_iport(ibdev, port);
	काष्ठा qib_pportdata *ppd = ppd_from_ibp(ibp);
	पूर्णांक ret;

	*out_mad = *in_mad;
	अगर (smp->class_version != 1) अणु
		smp->status |= IB_SMP_UNSUP_VERSION;
		ret = reply(smp);
		जाओ bail;
	पूर्ण

	ret = check_mkey(ibp, smp, mad_flags);
	अगर (ret) अणु
		u32 port_num = be32_to_cpu(smp->attr_mod);

		/*
		 * If this is a get/set portinfo, we alपढ़ोy check the
		 * M_Key अगर the MAD is क्रम another port and the M_Key
		 * is OK on the receiving port. This check is needed
		 * to increment the error counters when the M_Key
		 * fails to match on *both* ports.
		 */
		अगर (in_mad->mad_hdr.attr_id == IB_SMP_ATTR_PORT_INFO &&
		    (smp->method == IB_MGMT_METHOD_GET ||
		     smp->method == IB_MGMT_METHOD_SET) &&
		    port_num && port_num <= ibdev->phys_port_cnt &&
		    port != port_num)
			(व्योम) check_mkey(to_iport(ibdev, port_num), smp, 0);
		ret = IB_MAD_RESULT_FAILURE;
		जाओ bail;
	पूर्ण

	चयन (smp->method) अणु
	हाल IB_MGMT_METHOD_GET:
		चयन (smp->attr_id) अणु
		हाल IB_SMP_ATTR_NODE_DESC:
			ret = subn_get_nodedescription(smp, ibdev);
			जाओ bail;
		हाल IB_SMP_ATTR_NODE_INFO:
			ret = subn_get_nodeinfo(smp, ibdev, port);
			जाओ bail;
		हाल IB_SMP_ATTR_GUID_INFO:
			ret = subn_get_guidinfo(smp, ibdev, port);
			जाओ bail;
		हाल IB_SMP_ATTR_PORT_INFO:
			ret = subn_get_portinfo(smp, ibdev, port);
			जाओ bail;
		हाल IB_SMP_ATTR_PKEY_TABLE:
			ret = subn_get_pkeytable(smp, ibdev, port);
			जाओ bail;
		हाल IB_SMP_ATTR_SL_TO_VL_TABLE:
			ret = subn_get_sl_to_vl(smp, ibdev, port);
			जाओ bail;
		हाल IB_SMP_ATTR_VL_ARB_TABLE:
			ret = subn_get_vl_arb(smp, ibdev, port);
			जाओ bail;
		हाल IB_SMP_ATTR_SM_INFO:
			अगर (ibp->rvp.port_cap_flags & IB_PORT_SM_DISABLED) अणु
				ret = IB_MAD_RESULT_SUCCESS |
					IB_MAD_RESULT_CONSUMED;
				जाओ bail;
			पूर्ण
			अगर (ibp->rvp.port_cap_flags & IB_PORT_SM) अणु
				ret = IB_MAD_RESULT_SUCCESS;
				जाओ bail;
			पूर्ण
			fallthrough;
		शेष:
			smp->status |= IB_SMP_UNSUP_METH_ATTR;
			ret = reply(smp);
			जाओ bail;
		पूर्ण

	हाल IB_MGMT_METHOD_SET:
		चयन (smp->attr_id) अणु
		हाल IB_SMP_ATTR_GUID_INFO:
			ret = subn_set_guidinfo(smp, ibdev, port);
			जाओ bail;
		हाल IB_SMP_ATTR_PORT_INFO:
			ret = subn_set_portinfo(smp, ibdev, port);
			जाओ bail;
		हाल IB_SMP_ATTR_PKEY_TABLE:
			ret = subn_set_pkeytable(smp, ibdev, port);
			जाओ bail;
		हाल IB_SMP_ATTR_SL_TO_VL_TABLE:
			ret = subn_set_sl_to_vl(smp, ibdev, port);
			जाओ bail;
		हाल IB_SMP_ATTR_VL_ARB_TABLE:
			ret = subn_set_vl_arb(smp, ibdev, port);
			जाओ bail;
		हाल IB_SMP_ATTR_SM_INFO:
			अगर (ibp->rvp.port_cap_flags & IB_PORT_SM_DISABLED) अणु
				ret = IB_MAD_RESULT_SUCCESS |
					IB_MAD_RESULT_CONSUMED;
				जाओ bail;
			पूर्ण
			अगर (ibp->rvp.port_cap_flags & IB_PORT_SM) अणु
				ret = IB_MAD_RESULT_SUCCESS;
				जाओ bail;
			पूर्ण
			fallthrough;
		शेष:
			smp->status |= IB_SMP_UNSUP_METH_ATTR;
			ret = reply(smp);
			जाओ bail;
		पूर्ण

	हाल IB_MGMT_METHOD_TRAP_REPRESS:
		अगर (smp->attr_id == IB_SMP_ATTR_NOTICE)
			ret = subn_trap_repress(smp, ibdev, port);
		अन्यथा अणु
			smp->status |= IB_SMP_UNSUP_METH_ATTR;
			ret = reply(smp);
		पूर्ण
		जाओ bail;

	हाल IB_MGMT_METHOD_TRAP:
	हाल IB_MGMT_METHOD_REPORT:
	हाल IB_MGMT_METHOD_REPORT_RESP:
	हाल IB_MGMT_METHOD_GET_RESP:
		/*
		 * The ib_mad module will call us to process responses
		 * beक्रमe checking क्रम other consumers.
		 * Just tell the caller to process it normally.
		 */
		ret = IB_MAD_RESULT_SUCCESS;
		जाओ bail;

	हाल IB_MGMT_METHOD_SEND:
		अगर (ib_get_smp_direction(smp) &&
		    smp->attr_id == QIB_VENDOR_IPG) अणु
			ppd->dd->f_set_ib_cfg(ppd, QIB_IB_CFG_PORT,
					      smp->data[0]);
			ret = IB_MAD_RESULT_SUCCESS | IB_MAD_RESULT_CONSUMED;
		पूर्ण अन्यथा
			ret = IB_MAD_RESULT_SUCCESS;
		जाओ bail;

	शेष:
		smp->status |= IB_SMP_UNSUP_METHOD;
		ret = reply(smp);
	पूर्ण

bail:
	वापस ret;
पूर्ण

अटल पूर्णांक process_perf(काष्ठा ib_device *ibdev, u8 port,
			स्थिर काष्ठा ib_mad *in_mad,
			काष्ठा ib_mad *out_mad)
अणु
	काष्ठा ib_pma_mad *pmp = (काष्ठा ib_pma_mad *)out_mad;
	पूर्णांक ret;

	*out_mad = *in_mad;
	अगर (pmp->mad_hdr.class_version != 1) अणु
		pmp->mad_hdr.status |= IB_SMP_UNSUP_VERSION;
		ret = reply((काष्ठा ib_smp *) pmp);
		जाओ bail;
	पूर्ण

	चयन (pmp->mad_hdr.method) अणु
	हाल IB_MGMT_METHOD_GET:
		चयन (pmp->mad_hdr.attr_id) अणु
		हाल IB_PMA_CLASS_PORT_INFO:
			ret = pma_get_classportinfo(pmp, ibdev);
			जाओ bail;
		हाल IB_PMA_PORT_SAMPLES_CONTROL:
			ret = pma_get_portsamplescontrol(pmp, ibdev, port);
			जाओ bail;
		हाल IB_PMA_PORT_SAMPLES_RESULT:
			ret = pma_get_portsamplesresult(pmp, ibdev, port);
			जाओ bail;
		हाल IB_PMA_PORT_SAMPLES_RESULT_EXT:
			ret = pma_get_portsamplesresult_ext(pmp, ibdev, port);
			जाओ bail;
		हाल IB_PMA_PORT_COUNTERS:
			ret = pma_get_portcounters(pmp, ibdev, port);
			जाओ bail;
		हाल IB_PMA_PORT_COUNTERS_EXT:
			ret = pma_get_portcounters_ext(pmp, ibdev, port);
			जाओ bail;
		हाल IB_PMA_PORT_COUNTERS_CONG:
			ret = pma_get_portcounters_cong(pmp, ibdev, port);
			जाओ bail;
		शेष:
			pmp->mad_hdr.status |= IB_SMP_UNSUP_METH_ATTR;
			ret = reply((काष्ठा ib_smp *) pmp);
			जाओ bail;
		पूर्ण

	हाल IB_MGMT_METHOD_SET:
		चयन (pmp->mad_hdr.attr_id) अणु
		हाल IB_PMA_PORT_SAMPLES_CONTROL:
			ret = pma_set_portsamplescontrol(pmp, ibdev, port);
			जाओ bail;
		हाल IB_PMA_PORT_COUNTERS:
			ret = pma_set_portcounters(pmp, ibdev, port);
			जाओ bail;
		हाल IB_PMA_PORT_COUNTERS_EXT:
			ret = pma_set_portcounters_ext(pmp, ibdev, port);
			जाओ bail;
		हाल IB_PMA_PORT_COUNTERS_CONG:
			ret = pma_set_portcounters_cong(pmp, ibdev, port);
			जाओ bail;
		शेष:
			pmp->mad_hdr.status |= IB_SMP_UNSUP_METH_ATTR;
			ret = reply((काष्ठा ib_smp *) pmp);
			जाओ bail;
		पूर्ण

	हाल IB_MGMT_METHOD_TRAP:
	हाल IB_MGMT_METHOD_GET_RESP:
		/*
		 * The ib_mad module will call us to process responses
		 * beक्रमe checking क्रम other consumers.
		 * Just tell the caller to process it normally.
		 */
		ret = IB_MAD_RESULT_SUCCESS;
		जाओ bail;

	शेष:
		pmp->mad_hdr.status |= IB_SMP_UNSUP_METHOD;
		ret = reply((काष्ठा ib_smp *) pmp);
	पूर्ण

bail:
	वापस ret;
पूर्ण

अटल पूर्णांक cc_get_classportinfo(काष्ठा ib_cc_mad *ccp,
				काष्ठा ib_device *ibdev)
अणु
	काष्ठा ib_cc_classportinfo_attr *p =
		(काष्ठा ib_cc_classportinfo_attr *)ccp->mgmt_data;

	p->base_version = 1;
	p->class_version = 1;
	p->cap_mask = 0;

	/*
	 * Expected response समय is 4.096 usec. * 2^18 == 1.073741824 sec.
	 */
	p->resp_समय_value = 18;

	वापस reply((काष्ठा ib_smp *) ccp);
पूर्ण

अटल पूर्णांक cc_get_congestion_info(काष्ठा ib_cc_mad *ccp,
				काष्ठा ib_device *ibdev, u8 port)
अणु
	काष्ठा ib_cc_info_attr *p =
		(काष्ठा ib_cc_info_attr *)ccp->mgmt_data;
	काष्ठा qib_ibport *ibp = to_iport(ibdev, port);
	काष्ठा qib_pportdata *ppd = ppd_from_ibp(ibp);

	p->congestion_info = 0;
	p->control_table_cap = ppd->cc_max_table_entries;

	वापस reply((काष्ठा ib_smp *) ccp);
पूर्ण

अटल पूर्णांक cc_get_congestion_setting(काष्ठा ib_cc_mad *ccp,
				काष्ठा ib_device *ibdev, u8 port)
अणु
	पूर्णांक i;
	काष्ठा ib_cc_congestion_setting_attr *p =
		(काष्ठा ib_cc_congestion_setting_attr *)ccp->mgmt_data;
	काष्ठा qib_ibport *ibp = to_iport(ibdev, port);
	काष्ठा qib_pportdata *ppd = ppd_from_ibp(ibp);
	काष्ठा ib_cc_congestion_entry_shaकरोw *entries;

	spin_lock(&ppd->cc_shaकरोw_lock);

	entries = ppd->congestion_entries_shaकरोw->entries;
	p->port_control = cpu_to_be16(
		ppd->congestion_entries_shaकरोw->port_control);
	p->control_map = cpu_to_be16(
		ppd->congestion_entries_shaकरोw->control_map);
	क्रम (i = 0; i < IB_CC_CCS_ENTRIES; i++) अणु
		p->entries[i].ccti_increase = entries[i].ccti_increase;
		p->entries[i].ccti_समयr = cpu_to_be16(entries[i].ccti_समयr);
		p->entries[i].trigger_threshold = entries[i].trigger_threshold;
		p->entries[i].ccti_min = entries[i].ccti_min;
	पूर्ण

	spin_unlock(&ppd->cc_shaकरोw_lock);

	वापस reply((काष्ठा ib_smp *) ccp);
पूर्ण

अटल पूर्णांक cc_get_congestion_control_table(काष्ठा ib_cc_mad *ccp,
				काष्ठा ib_device *ibdev, u8 port)
अणु
	काष्ठा ib_cc_table_attr *p =
		(काष्ठा ib_cc_table_attr *)ccp->mgmt_data;
	काष्ठा qib_ibport *ibp = to_iport(ibdev, port);
	काष्ठा qib_pportdata *ppd = ppd_from_ibp(ibp);
	u32 cct_block_index = be32_to_cpu(ccp->attr_mod);
	u32 max_cct_block;
	u32 cct_entry;
	काष्ठा ib_cc_table_entry_shaकरोw *entries;
	पूर्णांक i;

	/* Is the table index more than what is supported? */
	अगर (cct_block_index > IB_CC_TABLE_CAP_DEFAULT - 1)
		जाओ bail;

	spin_lock(&ppd->cc_shaकरोw_lock);

	max_cct_block =
		(ppd->ccti_entries_shaकरोw->ccti_last_entry + 1)/IB_CCT_ENTRIES;
	max_cct_block = max_cct_block ? max_cct_block - 1 : 0;

	अगर (cct_block_index > max_cct_block) अणु
		spin_unlock(&ppd->cc_shaकरोw_lock);
		जाओ bail;
	पूर्ण

	ccp->attr_mod = cpu_to_be32(cct_block_index);

	cct_entry = IB_CCT_ENTRIES * (cct_block_index + 1);

	cct_entry--;

	p->ccti_limit = cpu_to_be16(cct_entry);

	entries = &ppd->ccti_entries_shaकरोw->
			entries[IB_CCT_ENTRIES * cct_block_index];
	cct_entry %= IB_CCT_ENTRIES;

	क्रम (i = 0; i <= cct_entry; i++)
		p->ccti_entries[i].entry = cpu_to_be16(entries[i].entry);

	spin_unlock(&ppd->cc_shaकरोw_lock);

	वापस reply((काष्ठा ib_smp *) ccp);

bail:
	वापस reply_failure((काष्ठा ib_smp *) ccp);
पूर्ण

अटल पूर्णांक cc_set_congestion_setting(काष्ठा ib_cc_mad *ccp,
				काष्ठा ib_device *ibdev, u8 port)
अणु
	काष्ठा ib_cc_congestion_setting_attr *p =
		(काष्ठा ib_cc_congestion_setting_attr *)ccp->mgmt_data;
	काष्ठा qib_ibport *ibp = to_iport(ibdev, port);
	काष्ठा qib_pportdata *ppd = ppd_from_ibp(ibp);
	पूर्णांक i;

	ppd->cc_sl_control_map = be16_to_cpu(p->control_map);

	क्रम (i = 0; i < IB_CC_CCS_ENTRIES; i++) अणु
		ppd->congestion_entries[i].ccti_increase =
			p->entries[i].ccti_increase;

		ppd->congestion_entries[i].ccti_समयr =
			be16_to_cpu(p->entries[i].ccti_समयr);

		ppd->congestion_entries[i].trigger_threshold =
			p->entries[i].trigger_threshold;

		ppd->congestion_entries[i].ccti_min =
			p->entries[i].ccti_min;
	पूर्ण

	वापस reply((काष्ठा ib_smp *) ccp);
पूर्ण

अटल पूर्णांक cc_set_congestion_control_table(काष्ठा ib_cc_mad *ccp,
				काष्ठा ib_device *ibdev, u8 port)
अणु
	काष्ठा ib_cc_table_attr *p =
		(काष्ठा ib_cc_table_attr *)ccp->mgmt_data;
	काष्ठा qib_ibport *ibp = to_iport(ibdev, port);
	काष्ठा qib_pportdata *ppd = ppd_from_ibp(ibp);
	u32 cct_block_index = be32_to_cpu(ccp->attr_mod);
	u32 cct_entry;
	काष्ठा ib_cc_table_entry_shaकरोw *entries;
	पूर्णांक i;

	/* Is the table index more than what is supported? */
	अगर (cct_block_index > IB_CC_TABLE_CAP_DEFAULT - 1)
		जाओ bail;

	/* If this packet is the first in the sequence then
	 * zero the total table entry count.
	 */
	अगर (be16_to_cpu(p->ccti_limit) < IB_CCT_ENTRIES)
		ppd->total_cct_entry = 0;

	cct_entry = (be16_to_cpu(p->ccti_limit))%IB_CCT_ENTRIES;

	/* ccti_limit is 0 to 63 */
	ppd->total_cct_entry += (cct_entry + 1);

	अगर (ppd->total_cct_entry > ppd->cc_supported_table_entries)
		जाओ bail;

	ppd->ccti_limit = be16_to_cpu(p->ccti_limit);

	entries = ppd->ccti_entries + (IB_CCT_ENTRIES * cct_block_index);

	क्रम (i = 0; i <= cct_entry; i++)
		entries[i].entry = be16_to_cpu(p->ccti_entries[i].entry);

	spin_lock(&ppd->cc_shaकरोw_lock);

	ppd->ccti_entries_shaकरोw->ccti_last_entry = ppd->total_cct_entry - 1;
	स_नकल(ppd->ccti_entries_shaकरोw->entries, ppd->ccti_entries,
		(ppd->total_cct_entry * माप(काष्ठा ib_cc_table_entry)));

	ppd->congestion_entries_shaकरोw->port_control = IB_CC_CCS_PC_SL_BASED;
	ppd->congestion_entries_shaकरोw->control_map = ppd->cc_sl_control_map;
	स_नकल(ppd->congestion_entries_shaकरोw->entries, ppd->congestion_entries,
		IB_CC_CCS_ENTRIES * माप(काष्ठा ib_cc_congestion_entry));

	spin_unlock(&ppd->cc_shaकरोw_lock);

	वापस reply((काष्ठा ib_smp *) ccp);

bail:
	वापस reply_failure((काष्ठा ib_smp *) ccp);
पूर्ण

अटल पूर्णांक process_cc(काष्ठा ib_device *ibdev, पूर्णांक mad_flags,
			u8 port, स्थिर काष्ठा ib_mad *in_mad,
			काष्ठा ib_mad *out_mad)
अणु
	काष्ठा ib_cc_mad *ccp = (काष्ठा ib_cc_mad *)out_mad;
	*out_mad = *in_mad;

	अगर (ccp->class_version != 2) अणु
		ccp->status |= IB_SMP_UNSUP_VERSION;
		वापस reply((काष्ठा ib_smp *)ccp);
	पूर्ण

	चयन (ccp->method) अणु
	हाल IB_MGMT_METHOD_GET:
		चयन (ccp->attr_id) अणु
		हाल IB_CC_ATTR_CLASSPORTINFO:
			वापस cc_get_classportinfo(ccp, ibdev);
		हाल IB_CC_ATTR_CONGESTION_INFO:
			वापस cc_get_congestion_info(ccp, ibdev, port);
		हाल IB_CC_ATTR_CA_CONGESTION_SETTING:
			वापस cc_get_congestion_setting(ccp, ibdev, port);
		हाल IB_CC_ATTR_CONGESTION_CONTROL_TABLE:
			वापस cc_get_congestion_control_table(ccp, ibdev, port);
		शेष:
			ccp->status |= IB_SMP_UNSUP_METH_ATTR;
			वापस reply((काष्ठा ib_smp *) ccp);
		पूर्ण
	हाल IB_MGMT_METHOD_SET:
		चयन (ccp->attr_id) अणु
		हाल IB_CC_ATTR_CA_CONGESTION_SETTING:
			वापस cc_set_congestion_setting(ccp, ibdev, port);
		हाल IB_CC_ATTR_CONGESTION_CONTROL_TABLE:
			वापस cc_set_congestion_control_table(ccp, ibdev, port);
		शेष:
			ccp->status |= IB_SMP_UNSUP_METH_ATTR;
			वापस reply((काष्ठा ib_smp *) ccp);
		पूर्ण
	हाल IB_MGMT_METHOD_GET_RESP:
		/*
		 * The ib_mad module will call us to process responses
		 * beक्रमe checking क्रम other consumers.
		 * Just tell the caller to process it normally.
		 */
		वापस IB_MAD_RESULT_SUCCESS;
	पूर्ण

	/* method is unsupported */
	ccp->status |= IB_SMP_UNSUP_METHOD;
	वापस reply((काष्ठा ib_smp *) ccp);
पूर्ण

/**
 * qib_process_mad - process an incoming MAD packet
 * @ibdev: the infiniband device this packet came in on
 * @mad_flags: MAD flags
 * @port: the port number this packet came in on
 * @in_wc: the work completion entry क्रम this packet
 * @in_grh: the global route header क्रम this packet
 * @in: the incoming MAD
 * @out: any outgoing MAD reply
 * @out_mad_size: size of the outgoing MAD reply
 * @out_mad_pkey_index: unused
 *
 * Returns IB_MAD_RESULT_SUCCESS अगर this is a MAD that we are not
 * पूर्णांकerested in processing.
 *
 * Note that the verbs framework has alपढ़ोy करोne the MAD sanity checks,
 * and hop count/poपूर्णांकer updating क्रम IB_MGMT_CLASS_SUBN_सूचीECTED_ROUTE
 * MADs.
 *
 * This is called by the ib_mad module.
 */
पूर्णांक qib_process_mad(काष्ठा ib_device *ibdev, पूर्णांक mad_flags, u32 port,
		    स्थिर काष्ठा ib_wc *in_wc, स्थिर काष्ठा ib_grh *in_grh,
		    स्थिर काष्ठा ib_mad *in, काष्ठा ib_mad *out,
		    माप_प्रकार *out_mad_size, u16 *out_mad_pkey_index)
अणु
	पूर्णांक ret;
	काष्ठा qib_ibport *ibp = to_iport(ibdev, port);
	काष्ठा qib_pportdata *ppd = ppd_from_ibp(ibp);

	चयन (in->mad_hdr.mgmt_class) अणु
	हाल IB_MGMT_CLASS_SUBN_सूचीECTED_ROUTE:
	हाल IB_MGMT_CLASS_SUBN_LID_ROUTED:
		ret = process_subn(ibdev, mad_flags, port, in, out);
		जाओ bail;

	हाल IB_MGMT_CLASS_PERF_MGMT:
		ret = process_perf(ibdev, port, in, out);
		जाओ bail;

	हाल IB_MGMT_CLASS_CONG_MGMT:
		अगर (!ppd->congestion_entries_shaकरोw ||
			 !qib_cc_table_size) अणु
			ret = IB_MAD_RESULT_SUCCESS;
			जाओ bail;
		पूर्ण
		ret = process_cc(ibdev, mad_flags, port, in, out);
		जाओ bail;

	शेष:
		ret = IB_MAD_RESULT_SUCCESS;
	पूर्ण

bail:
	वापस ret;
पूर्ण

अटल व्योम xmit_रुको_समयr_func(काष्ठा समयr_list *t)
अणु
	काष्ठा qib_pportdata *ppd = from_समयr(ppd, t, cong_stats.समयr);
	काष्ठा qib_devdata *dd = dd_from_ppd(ppd);
	अचिन्हित दीर्घ flags;
	u8 status;

	spin_lock_irqsave(&ppd->ibport_data.rvp.lock, flags);
	अगर (ppd->cong_stats.flags == IB_PMA_CONG_HW_CONTROL_SAMPLE) अणु
		status = dd->f_portcntr(ppd, QIBPORTCNTR_PSSTAT);
		अगर (status == IB_PMA_SAMPLE_STATUS_DONE) अणु
			/* save counter cache */
			cache_hw_sample_counters(ppd);
			ppd->cong_stats.flags = IB_PMA_CONG_HW_CONTROL_TIMER;
		पूर्ण अन्यथा
			जाओ करोne;
	पूर्ण
	ppd->cong_stats.counter = xmit_रुको_get_value_delta(ppd);
	dd->f_set_cntr_sample(ppd, QIB_CONG_TIMER_PSINTERVAL, 0x0);
करोne:
	spin_unlock_irqrestore(&ppd->ibport_data.rvp.lock, flags);
	mod_समयr(&ppd->cong_stats.समयr, jअगरfies + HZ);
पूर्ण

व्योम qib_notअगरy_create_mad_agent(काष्ठा rvt_dev_info *rdi, पूर्णांक port_idx)
अणु
	काष्ठा qib_ibdev *ibdev = container_of(rdi, काष्ठा qib_ibdev, rdi);
	काष्ठा qib_devdata *dd = container_of(ibdev,
					      काष्ठा qib_devdata, verbs_dev);

	/* Initialize xmit_रुको काष्ठाure */
	dd->pport[port_idx].cong_stats.counter = 0;
	समयr_setup(&dd->pport[port_idx].cong_stats.समयr,
		    xmit_रुको_समयr_func, 0);
	dd->pport[port_idx].cong_stats.समयr.expires = 0;
	add_समयr(&dd->pport[port_idx].cong_stats.समयr);
पूर्ण

व्योम qib_notअगरy_मुक्त_mad_agent(काष्ठा rvt_dev_info *rdi, पूर्णांक port_idx)
अणु
	काष्ठा qib_ibdev *ibdev = container_of(rdi, काष्ठा qib_ibdev, rdi);
	काष्ठा qib_devdata *dd = container_of(ibdev,
					      काष्ठा qib_devdata, verbs_dev);

	अगर (dd->pport[port_idx].cong_stats.समयr.function)
		del_समयr_sync(&dd->pport[port_idx].cong_stats.समयr);

	अगर (dd->pport[port_idx].ibport_data.smi_ah)
		rdma_destroy_ah(&dd->pport[port_idx].ibport_data.smi_ah->ibah,
				RDMA_DESTROY_AH_SLEEPABLE);
पूर्ण
