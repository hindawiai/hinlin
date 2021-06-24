<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * This file is part of the Emulex Linux Device Driver क्रम Enterprise iSCSI
 * Host Bus Adapters. Refer to the README file included with this package
 * क्रम driver version and adapter compatibility.
 *
 * Copyright (c) 2018 Broadcom. All Rights Reserved.
 * The term "Broadcom" refers to Broadcom Inc. and/or its subsidiaries.
 *
 * Contact Inक्रमmation:
 * linux-drivers@broadcom.com
 */

#समावेश <scsi/libiscsi.h>
#समावेश <scsi/scsi_transport_iscsi.h>
#समावेश <scsi/scsi_transport.h>
#समावेश <scsi/scsi_cmnd.h>
#समावेश <scsi/scsi_device.h>
#समावेश <scsi/scsi_host.h>
#समावेश <scsi/scsi_netlink.h>
#समावेश <net/netlink.h>
#समावेश <scsi/scsi.h>

#समावेश "be_iscsi.h"

बाह्य काष्ठा iscsi_transport beiscsi_iscsi_transport;

/**
 * beiscsi_session_create - creates a new iscsi session
 * @ep: poपूर्णांकer to iscsi ep
 * @cmds_max: max commands supported
 * @qdepth: max queue depth supported
 * @initial_cmdsn: initial iscsi CMDSN
 */
काष्ठा iscsi_cls_session *beiscsi_session_create(काष्ठा iscsi_endpoपूर्णांक *ep,
						 u16 cmds_max,
						 u16 qdepth,
						 u32 initial_cmdsn)
अणु
	काष्ठा Scsi_Host *shost;
	काष्ठा beiscsi_endpoपूर्णांक *beiscsi_ep;
	काष्ठा iscsi_cls_session *cls_session;
	काष्ठा beiscsi_hba *phba;
	काष्ठा iscsi_session *sess;
	काष्ठा beiscsi_session *beiscsi_sess;
	काष्ठा beiscsi_io_task *io_task;


	अगर (!ep) अणु
		pr_err("beiscsi_session_create: invalid ep\n");
		वापस शून्य;
	पूर्ण
	beiscsi_ep = ep->dd_data;
	phba = beiscsi_ep->phba;

	अगर (!beiscsi_hba_is_online(phba)) अणु
		beiscsi_log(phba, KERN_INFO, BEISCSI_LOG_CONFIG,
			    "BS_%d : HBA in error 0x%lx\n", phba->state);
		वापस शून्य;
	पूर्ण

	beiscsi_log(phba, KERN_INFO, BEISCSI_LOG_CONFIG,
		    "BS_%d : In beiscsi_session_create\n");
	अगर (cmds_max > beiscsi_ep->phba->params.wrbs_per_cxn) अणु
		beiscsi_log(phba, KERN_ERR, BEISCSI_LOG_CONFIG,
			    "BS_%d : Cannot handle %d cmds."
			    "Max cmds per session supported is %d. Using %d."
			    "\n", cmds_max,
			    beiscsi_ep->phba->params.wrbs_per_cxn,
			    beiscsi_ep->phba->params.wrbs_per_cxn);

		cmds_max = beiscsi_ep->phba->params.wrbs_per_cxn;
	पूर्ण

	shost = phba->shost;
	cls_session = iscsi_session_setup(&beiscsi_iscsi_transport,
					  shost, cmds_max,
					  माप(*beiscsi_sess),
					  माप(*io_task),
					  initial_cmdsn, ISCSI_MAX_TARGET);
	अगर (!cls_session)
		वापस शून्य;
	sess = cls_session->dd_data;
	beiscsi_sess = sess->dd_data;
	beiscsi_sess->bhs_pool =  dma_pool_create("beiscsi_bhs_pool",
						   &phba->pcidev->dev,
						   माप(काष्ठा be_cmd_bhs),
						   64, 0);
	अगर (!beiscsi_sess->bhs_pool)
		जाओ destroy_sess;

	वापस cls_session;
destroy_sess:
	iscsi_session_tearकरोwn(cls_session);
	वापस शून्य;
पूर्ण

/**
 * beiscsi_session_destroy - destroys iscsi session
 * @cls_session:	poपूर्णांकer to iscsi cls session
 *
 * Destroys iSCSI session instance and releases
 * resources allocated क्रम it.
 */
व्योम beiscsi_session_destroy(काष्ठा iscsi_cls_session *cls_session)
अणु
	काष्ठा iscsi_session *sess = cls_session->dd_data;
	काष्ठा beiscsi_session *beiscsi_sess = sess->dd_data;

	prपूर्णांकk(KERN_INFO "In beiscsi_session_destroy\n");
	dma_pool_destroy(beiscsi_sess->bhs_pool);
	iscsi_session_tearकरोwn(cls_session);
पूर्ण

/**
 * beiscsi_session_fail(): Closing session with appropriate error
 * @cls_session: ptr to session
 **/
व्योम beiscsi_session_fail(काष्ठा iscsi_cls_session *cls_session)
अणु
	iscsi_session_failure(cls_session->dd_data, ISCSI_ERR_CONN_FAILED);
पूर्ण


/**
 * beiscsi_conn_create - create an instance of iscsi connection
 * @cls_session: ptr to iscsi_cls_session
 * @cid: iscsi cid
 */
काष्ठा iscsi_cls_conn *
beiscsi_conn_create(काष्ठा iscsi_cls_session *cls_session, u32 cid)
अणु
	काष्ठा beiscsi_hba *phba;
	काष्ठा Scsi_Host *shost;
	काष्ठा iscsi_cls_conn *cls_conn;
	काष्ठा beiscsi_conn *beiscsi_conn;
	काष्ठा iscsi_conn *conn;
	काष्ठा iscsi_session *sess;
	काष्ठा beiscsi_session *beiscsi_sess;

	shost = iscsi_session_to_shost(cls_session);
	phba = iscsi_host_priv(shost);

	beiscsi_log(phba, KERN_INFO, BEISCSI_LOG_CONFIG,
		    "BS_%d : In beiscsi_conn_create ,cid"
		    "from iscsi layer=%d\n", cid);

	cls_conn = iscsi_conn_setup(cls_session, माप(*beiscsi_conn), cid);
	अगर (!cls_conn)
		वापस शून्य;

	conn = cls_conn->dd_data;
	beiscsi_conn = conn->dd_data;
	beiscsi_conn->ep = शून्य;
	beiscsi_conn->phba = phba;
	beiscsi_conn->conn = conn;
	sess = cls_session->dd_data;
	beiscsi_sess = sess->dd_data;
	beiscsi_conn->beiscsi_sess = beiscsi_sess;
	वापस cls_conn;
पूर्ण

/**
 * beiscsi_conn_bind - Binds iscsi session/connection with TCP connection
 * @cls_session: poपूर्णांकer to iscsi cls session
 * @cls_conn: poपूर्णांकer to iscsi cls conn
 * @transport_fd: EP handle(64 bit)
 * @is_leading: indicate अगर this is the session leading connection (MCS)
 *
 * This function binds the TCP Conn with iSCSI Connection and Session.
 */
पूर्णांक beiscsi_conn_bind(काष्ठा iscsi_cls_session *cls_session,
		      काष्ठा iscsi_cls_conn *cls_conn,
		      u64 transport_fd, पूर्णांक is_leading)
अणु
	काष्ठा iscsi_conn *conn = cls_conn->dd_data;
	काष्ठा beiscsi_conn *beiscsi_conn = conn->dd_data;
	काष्ठा Scsi_Host *shost = iscsi_session_to_shost(cls_session);
	काष्ठा beiscsi_hba *phba = iscsi_host_priv(shost);
	काष्ठा hwi_controller *phwi_ctrlr = phba->phwi_ctrlr;
	काष्ठा hwi_wrb_context *pwrb_context;
	काष्ठा beiscsi_endpoपूर्णांक *beiscsi_ep;
	काष्ठा iscsi_endpoपूर्णांक *ep;
	uपूर्णांक16_t cri_index;

	ep = iscsi_lookup_endpoपूर्णांक(transport_fd);
	अगर (!ep)
		वापस -EINVAL;

	beiscsi_ep = ep->dd_data;

	अगर (iscsi_conn_bind(cls_session, cls_conn, is_leading))
		वापस -EINVAL;

	अगर (beiscsi_ep->phba != phba) अणु
		beiscsi_log(phba, KERN_ERR, BEISCSI_LOG_CONFIG,
			    "BS_%d : beiscsi_ep->hba=%p not equal to phba=%p\n",
			    beiscsi_ep->phba, phba);

		वापस -EEXIST;
	पूर्ण
	cri_index = BE_GET_CRI_FROM_CID(beiscsi_ep->ep_cid);
	अगर (phba->conn_table[cri_index]) अणु
		अगर (beiscsi_conn != phba->conn_table[cri_index] ||
		    beiscsi_ep != phba->conn_table[cri_index]->ep) अणु
			__beiscsi_log(phba, KERN_ERR,
				      "BS_%d : conn_table not empty at %u: cid %u conn %p:%p\n",
				      cri_index,
				      beiscsi_ep->ep_cid,
				      beiscsi_conn,
				      phba->conn_table[cri_index]);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	beiscsi_conn->beiscsi_conn_cid = beiscsi_ep->ep_cid;
	beiscsi_conn->ep = beiscsi_ep;
	beiscsi_ep->conn = beiscsi_conn;
	/**
	 * Each connection is associated with a WRBQ kept in wrb_context.
	 * Store करोorbell offset क्रम transmit path.
	 */
	pwrb_context = &phwi_ctrlr->wrb_context[cri_index];
	beiscsi_conn->करोorbell_offset = pwrb_context->करोorbell_offset;
	beiscsi_log(phba, KERN_INFO, BEISCSI_LOG_CONFIG,
		    "BS_%d : cid %d phba->conn_table[%u]=%p\n",
		    beiscsi_ep->ep_cid, cri_index, beiscsi_conn);
	phba->conn_table[cri_index] = beiscsi_conn;
	वापस 0;
पूर्ण

अटल पूर्णांक beiscsi_अगरace_create_ipv4(काष्ठा beiscsi_hba *phba)
अणु
	अगर (phba->ipv4_अगरace)
		वापस 0;

	phba->ipv4_अगरace = iscsi_create_अगरace(phba->shost,
					      &beiscsi_iscsi_transport,
					      ISCSI_IFACE_TYPE_IPV4,
					      0, 0);
	अगर (!phba->ipv4_अगरace) अणु
		beiscsi_log(phba, KERN_ERR, BEISCSI_LOG_CONFIG,
			    "BS_%d : Could not "
			    "create default IPv4 address.\n");
		वापस -ENODEV;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक beiscsi_अगरace_create_ipv6(काष्ठा beiscsi_hba *phba)
अणु
	अगर (phba->ipv6_अगरace)
		वापस 0;

	phba->ipv6_अगरace = iscsi_create_अगरace(phba->shost,
					      &beiscsi_iscsi_transport,
					      ISCSI_IFACE_TYPE_IPV6,
					      0, 0);
	अगर (!phba->ipv6_अगरace) अणु
		beiscsi_log(phba, KERN_ERR, BEISCSI_LOG_CONFIG,
			    "BS_%d : Could not "
			    "create default IPv6 address.\n");
		वापस -ENODEV;
	पूर्ण

	वापस 0;
पूर्ण

व्योम beiscsi_अगरace_create_शेष(काष्ठा beiscsi_hba *phba)
अणु
	काष्ठा be_cmd_get_अगर_info_resp *अगर_info;

	अगर (!beiscsi_अगर_get_info(phba, BEISCSI_IP_TYPE_V4, &अगर_info)) अणु
		beiscsi_अगरace_create_ipv4(phba);
		kमुक्त(अगर_info);
	पूर्ण

	अगर (!beiscsi_अगर_get_info(phba, BEISCSI_IP_TYPE_V6, &अगर_info)) अणु
		beiscsi_अगरace_create_ipv6(phba);
		kमुक्त(अगर_info);
	पूर्ण
पूर्ण

व्योम beiscsi_अगरace_destroy_शेष(काष्ठा beiscsi_hba *phba)
अणु
	अगर (phba->ipv6_अगरace) अणु
		iscsi_destroy_अगरace(phba->ipv6_अगरace);
		phba->ipv6_अगरace = शून्य;
	पूर्ण
	अगर (phba->ipv4_अगरace) अणु
		iscsi_destroy_अगरace(phba->ipv4_अगरace);
		phba->ipv4_अगरace = शून्य;
	पूर्ण
पूर्ण

/**
 * beiscsi_अगरace_config_vlan()- Set the VLAN TAG
 * @shost: Scsi Host क्रम the driver instance
 * @अगरace_param: Interface paramters
 *
 * Set the VLAN TAG क्रम the adapter or disable
 * the VLAN config
 *
 * वापसs
 *	Success: 0
 *	Failure: Non-Zero Value
 **/
अटल पूर्णांक
beiscsi_अगरace_config_vlan(काष्ठा Scsi_Host *shost,
			  काष्ठा iscsi_अगरace_param_info *अगरace_param)
अणु
	काष्ठा beiscsi_hba *phba = iscsi_host_priv(shost);
	पूर्णांक ret = -EPERM;

	चयन (अगरace_param->param) अणु
	हाल ISCSI_NET_PARAM_VLAN_ENABLED:
		ret = 0;
		अगर (अगरace_param->value[0] != ISCSI_VLAN_ENABLE)
			ret = beiscsi_अगर_set_vlan(phba, BEISCSI_VLAN_DISABLE);
		अवरोध;
	हाल ISCSI_NET_PARAM_VLAN_TAG:
		ret = beiscsi_अगर_set_vlan(phba,
					  *((uपूर्णांक16_t *)अगरace_param->value));
		अवरोध;
	पूर्ण
	वापस ret;
पूर्ण


अटल पूर्णांक
beiscsi_अगरace_config_ipv4(काष्ठा Scsi_Host *shost,
			  काष्ठा iscsi_अगरace_param_info *info,
			  व्योम *data, uपूर्णांक32_t dt_len)
अणु
	काष्ठा beiscsi_hba *phba = iscsi_host_priv(shost);
	u8 *ip = शून्य, *subnet = शून्य, *gw;
	काष्ठा nlattr *nla;
	पूर्णांक ret = -EPERM;

	/* Check the param */
	चयन (info->param) अणु
	हाल ISCSI_NET_PARAM_IFACE_ENABLE:
		अगर (info->value[0] == ISCSI_IFACE_ENABLE)
			ret = beiscsi_अगरace_create_ipv4(phba);
		अन्यथा अणु
			iscsi_destroy_अगरace(phba->ipv4_अगरace);
			phba->ipv4_अगरace = शून्य;
		पूर्ण
		अवरोध;
	हाल ISCSI_NET_PARAM_IPV4_GW:
		gw = info->value;
		ret = beiscsi_अगर_set_gw(phba, BEISCSI_IP_TYPE_V4, gw);
		अवरोध;
	हाल ISCSI_NET_PARAM_IPV4_BOOTPROTO:
		अगर (info->value[0] == ISCSI_BOOTPROTO_DHCP)
			ret = beiscsi_अगर_en_dhcp(phba, BEISCSI_IP_TYPE_V4);
		अन्यथा अगर (info->value[0] == ISCSI_BOOTPROTO_STATIC)
			/* release DHCP IP address */
			ret = beiscsi_अगर_en_अटल(phba, BEISCSI_IP_TYPE_V4,
						   शून्य, शून्य);
		अन्यथा
			beiscsi_log(phba, KERN_ERR, BEISCSI_LOG_CONFIG,
				    "BS_%d : Invalid BOOTPROTO: %d\n",
				    info->value[0]);
		अवरोध;
	हाल ISCSI_NET_PARAM_IPV4_ADDR:
		ip = info->value;
		nla = nla_find(data, dt_len, ISCSI_NET_PARAM_IPV4_SUBNET);
		अगर (nla) अणु
			info = nla_data(nla);
			subnet = info->value;
		पूर्ण
		ret = beiscsi_अगर_en_अटल(phba, BEISCSI_IP_TYPE_V4,
					   ip, subnet);
		अवरोध;
	हाल ISCSI_NET_PARAM_IPV4_SUBNET:
		/*
		 * OPCODE_COMMON_ISCSI_NTWK_MODIFY_IP_ADDR ioctl needs IP
		 * and subnet both. Find IP to be applied क्रम this subnet.
		 */
		subnet = info->value;
		nla = nla_find(data, dt_len, ISCSI_NET_PARAM_IPV4_ADDR);
		अगर (nla) अणु
			info = nla_data(nla);
			ip = info->value;
		पूर्ण
		ret = beiscsi_अगर_en_अटल(phba, BEISCSI_IP_TYPE_V4,
					   ip, subnet);
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक
beiscsi_अगरace_config_ipv6(काष्ठा Scsi_Host *shost,
			  काष्ठा iscsi_अगरace_param_info *अगरace_param,
			  व्योम *data, uपूर्णांक32_t dt_len)
अणु
	काष्ठा beiscsi_hba *phba = iscsi_host_priv(shost);
	पूर्णांक ret = -EPERM;

	चयन (अगरace_param->param) अणु
	हाल ISCSI_NET_PARAM_IFACE_ENABLE:
		अगर (अगरace_param->value[0] == ISCSI_IFACE_ENABLE)
			ret = beiscsi_अगरace_create_ipv6(phba);
		अन्यथा अणु
			iscsi_destroy_अगरace(phba->ipv6_अगरace);
			phba->ipv6_अगरace = शून्य;
		पूर्ण
		अवरोध;
	हाल ISCSI_NET_PARAM_IPV6_ADDR:
		ret = beiscsi_अगर_en_अटल(phba, BEISCSI_IP_TYPE_V6,
					   अगरace_param->value, शून्य);
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

पूर्णांक beiscsi_अगरace_set_param(काष्ठा Scsi_Host *shost,
			    व्योम *data, uपूर्णांक32_t dt_len)
अणु
	काष्ठा iscsi_अगरace_param_info *अगरace_param = शून्य;
	काष्ठा beiscsi_hba *phba = iscsi_host_priv(shost);
	काष्ठा nlattr *attrib;
	uपूर्णांक32_t rm_len = dt_len;
	पूर्णांक ret;

	अगर (!beiscsi_hba_is_online(phba)) अणु
		beiscsi_log(phba, KERN_INFO, BEISCSI_LOG_CONFIG,
			    "BS_%d : HBA in error 0x%lx\n", phba->state);
		वापस -EBUSY;
	पूर्ण

	/* update पूर्णांकerface_handle */
	ret = beiscsi_अगर_get_handle(phba);
	अगर (ret) अणु
		beiscsi_log(phba, KERN_ERR, BEISCSI_LOG_CONFIG,
			    "BS_%d : Getting Interface Handle Failed\n");
		वापस ret;
	पूर्ण

	nla_क्रम_each_attr(attrib, data, dt_len, rm_len) अणु
		अगरace_param = nla_data(attrib);

		अगर (अगरace_param->param_type != ISCSI_NET_PARAM)
			जारी;

		/*
		 * BE2ISCSI only supports 1 पूर्णांकerface
		 */
		अगर (अगरace_param->अगरace_num) अणु
			beiscsi_log(phba, KERN_ERR, BEISCSI_LOG_CONFIG,
				    "BS_%d : Invalid iface_num %d."
				    "Only iface_num 0 is supported.\n",
				    अगरace_param->अगरace_num);

			वापस -EINVAL;
		पूर्ण

		beiscsi_log(phba, KERN_INFO, BEISCSI_LOG_CONFIG,
			    "BS_%d : %s.0 set param %d",
			    (अगरace_param->अगरace_type == ISCSI_IFACE_TYPE_IPV4) ?
			    "ipv4" : "ipv6", अगरace_param->param);

		ret = -EPERM;
		चयन (अगरace_param->param) अणु
		हाल ISCSI_NET_PARAM_VLAN_ENABLED:
		हाल ISCSI_NET_PARAM_VLAN_TAG:
			ret = beiscsi_अगरace_config_vlan(shost, अगरace_param);
			अवरोध;
		शेष:
			चयन (अगरace_param->अगरace_type) अणु
			हाल ISCSI_IFACE_TYPE_IPV4:
				ret = beiscsi_अगरace_config_ipv4(shost,
								अगरace_param,
								data, dt_len);
				अवरोध;
			हाल ISCSI_IFACE_TYPE_IPV6:
				ret = beiscsi_अगरace_config_ipv6(shost,
								अगरace_param,
								data, dt_len);
				अवरोध;
			पूर्ण
		पूर्ण

		अगर (ret == -EPERM) अणु
			__beiscsi_log(phba, KERN_ERR,
				      "BS_%d : %s.0 set param %d not permitted",
				      (अगरace_param->अगरace_type ==
				       ISCSI_IFACE_TYPE_IPV4) ? "ipv4" : "ipv6",
				      अगरace_param->param);
			ret = 0;
		पूर्ण
		अगर (ret)
			अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक __beiscsi_अगरace_get_param(काष्ठा beiscsi_hba *phba,
				     काष्ठा iscsi_अगरace *अगरace,
				     पूर्णांक param, अक्षर *buf)
अणु
	काष्ठा be_cmd_get_अगर_info_resp *अगर_info;
	पूर्णांक len, ip_type = BEISCSI_IP_TYPE_V4;

	अगर (अगरace->अगरace_type == ISCSI_IFACE_TYPE_IPV6)
		ip_type = BEISCSI_IP_TYPE_V6;

	len = beiscsi_अगर_get_info(phba, ip_type, &अगर_info);
	अगर (len)
		वापस len;

	चयन (param) अणु
	हाल ISCSI_NET_PARAM_IPV4_ADDR:
		len = प्र_लिखो(buf, "%pI4\n", अगर_info->ip_addr.addr);
		अवरोध;
	हाल ISCSI_NET_PARAM_IPV6_ADDR:
		len = प्र_लिखो(buf, "%pI6\n", अगर_info->ip_addr.addr);
		अवरोध;
	हाल ISCSI_NET_PARAM_IPV4_BOOTPROTO:
		अगर (!अगर_info->dhcp_state)
			len = प्र_लिखो(buf, "static\n");
		अन्यथा
			len = प्र_लिखो(buf, "dhcp\n");
		अवरोध;
	हाल ISCSI_NET_PARAM_IPV4_SUBNET:
		len = प्र_लिखो(buf, "%pI4\n", अगर_info->ip_addr.subnet_mask);
		अवरोध;
	हाल ISCSI_NET_PARAM_VLAN_ENABLED:
		len = प्र_लिखो(buf, "%s\n",
			      (अगर_info->vlan_priority == BEISCSI_VLAN_DISABLE) ?
			      "disable" : "enable");
		अवरोध;
	हाल ISCSI_NET_PARAM_VLAN_ID:
		अगर (अगर_info->vlan_priority == BEISCSI_VLAN_DISABLE)
			len = -EINVAL;
		अन्यथा
			len = प्र_लिखो(buf, "%d\n",
				      (अगर_info->vlan_priority &
				       ISCSI_MAX_VLAN_ID));
		अवरोध;
	हाल ISCSI_NET_PARAM_VLAN_PRIORITY:
		अगर (अगर_info->vlan_priority == BEISCSI_VLAN_DISABLE)
			len = -EINVAL;
		अन्यथा
			len = प्र_लिखो(buf, "%d\n",
				      ((अगर_info->vlan_priority >> 13) &
				       ISCSI_MAX_VLAN_PRIORITY));
		अवरोध;
	शेष:
		WARN_ON(1);
	पूर्ण

	kमुक्त(अगर_info);
	वापस len;
पूर्ण

पूर्णांक beiscsi_अगरace_get_param(काष्ठा iscsi_अगरace *अगरace,
			    क्रमागत iscsi_param_type param_type,
			    पूर्णांक param, अक्षर *buf)
अणु
	काष्ठा Scsi_Host *shost = iscsi_अगरace_to_shost(अगरace);
	काष्ठा beiscsi_hba *phba = iscsi_host_priv(shost);
	काष्ठा be_cmd_get_def_gateway_resp gateway;
	पूर्णांक len = -EPERM;

	अगर (param_type != ISCSI_NET_PARAM)
		वापस 0;
	अगर (!beiscsi_hba_is_online(phba)) अणु
		beiscsi_log(phba, KERN_INFO, BEISCSI_LOG_CONFIG,
			    "BS_%d : HBA in error 0x%lx\n", phba->state);
		वापस -EBUSY;
	पूर्ण

	चयन (param) अणु
	हाल ISCSI_NET_PARAM_IPV4_ADDR:
	हाल ISCSI_NET_PARAM_IPV4_SUBNET:
	हाल ISCSI_NET_PARAM_IPV4_BOOTPROTO:
	हाल ISCSI_NET_PARAM_IPV6_ADDR:
	हाल ISCSI_NET_PARAM_VLAN_ENABLED:
	हाल ISCSI_NET_PARAM_VLAN_ID:
	हाल ISCSI_NET_PARAM_VLAN_PRIORITY:
		len = __beiscsi_अगरace_get_param(phba, अगरace, param, buf);
		अवरोध;
	हाल ISCSI_NET_PARAM_IFACE_ENABLE:
		अगर (अगरace->अगरace_type == ISCSI_IFACE_TYPE_IPV4)
			len = प्र_लिखो(buf, "%s\n",
				      phba->ipv4_अगरace ? "enable" : "disable");
		अन्यथा अगर (अगरace->अगरace_type == ISCSI_IFACE_TYPE_IPV6)
			len = प्र_लिखो(buf, "%s\n",
				      phba->ipv6_अगरace ? "enable" : "disable");
		अवरोध;
	हाल ISCSI_NET_PARAM_IPV4_GW:
		स_रखो(&gateway, 0, माप(gateway));
		len = beiscsi_अगर_get_gw(phba, BEISCSI_IP_TYPE_V4, &gateway);
		अगर (!len)
			len = प्र_लिखो(buf, "%pI4\n", &gateway.ip_addr.addr);
		अवरोध;
	पूर्ण

	वापस len;
पूर्ण

/**
 * beiscsi_ep_get_param - get the iscsi parameter
 * @ep: poपूर्णांकer to iscsi ep
 * @param: parameter type identअगरier
 * @buf: buffer poपूर्णांकer
 *
 * वापसs iscsi parameter
 */
पूर्णांक beiscsi_ep_get_param(काष्ठा iscsi_endpoपूर्णांक *ep,
			   क्रमागत iscsi_param param, अक्षर *buf)
अणु
	काष्ठा beiscsi_endpoपूर्णांक *beiscsi_ep = ep->dd_data;
	पूर्णांक len;

	beiscsi_log(beiscsi_ep->phba, KERN_INFO,
		    BEISCSI_LOG_CONFIG,
		    "BS_%d : In beiscsi_ep_get_param,"
		    " param= %d\n", param);

	चयन (param) अणु
	हाल ISCSI_PARAM_CONN_PORT:
		len = प्र_लिखो(buf, "%hu\n", beiscsi_ep->dst_tcpport);
		अवरोध;
	हाल ISCSI_PARAM_CONN_ADDRESS:
		अगर (beiscsi_ep->ip_type == BEISCSI_IP_TYPE_V4)
			len = प्र_लिखो(buf, "%pI4\n", &beiscsi_ep->dst_addr);
		अन्यथा
			len = प्र_लिखो(buf, "%pI6\n", &beiscsi_ep->dst6_addr);
		अवरोध;
	शेष:
		len = -EPERM;
	पूर्ण
	वापस len;
पूर्ण

पूर्णांक beiscsi_set_param(काष्ठा iscsi_cls_conn *cls_conn,
		      क्रमागत iscsi_param param, अक्षर *buf, पूर्णांक buflen)
अणु
	काष्ठा iscsi_conn *conn = cls_conn->dd_data;
	काष्ठा iscsi_session *session = conn->session;
	काष्ठा beiscsi_hba *phba = शून्य;
	पूर्णांक ret;

	phba = ((काष्ठा beiscsi_conn *)conn->dd_data)->phba;
	beiscsi_log(phba, KERN_INFO, BEISCSI_LOG_CONFIG,
		    "BS_%d : In beiscsi_conn_set_param,"
		    " param= %d\n", param);

	ret = iscsi_set_param(cls_conn, param, buf, buflen);
	अगर (ret)
		वापस ret;
	/*
	 * If userspace tried to set the value to higher than we can
	 * support override here.
	 */
	चयन (param) अणु
	हाल ISCSI_PARAM_FIRST_BURST:
		अगर (session->first_burst > 8192)
			session->first_burst = 8192;
		अवरोध;
	हाल ISCSI_PARAM_MAX_RECV_DLENGTH:
		अगर (conn->max_recv_dlength > 65536)
			conn->max_recv_dlength = 65536;
		अवरोध;
	हाल ISCSI_PARAM_MAX_BURST:
		अगर (session->max_burst > 262144)
			session->max_burst = 262144;
		अवरोध;
	हाल ISCSI_PARAM_MAX_XMIT_DLENGTH:
		अगर (conn->max_xmit_dlength > 65536)
			conn->max_xmit_dlength = 65536;
		fallthrough;
	शेष:
		वापस 0;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * beiscsi_get_port_state - Get the Port State
 * @shost : poपूर्णांकer to scsi_host काष्ठाure
 *
 */
अटल व्योम beiscsi_get_port_state(काष्ठा Scsi_Host *shost)
अणु
	काष्ठा beiscsi_hba *phba = iscsi_host_priv(shost);
	काष्ठा iscsi_cls_host *ihost = shost->shost_data;

	ihost->port_state = test_bit(BEISCSI_HBA_LINK_UP, &phba->state) ?
		ISCSI_PORT_STATE_UP : ISCSI_PORT_STATE_DOWN;
पूर्ण

/**
 * beiscsi_get_port_speed  - Get the Port Speed from Adapter
 * @shost : poपूर्णांकer to scsi_host काष्ठाure
 *
 */
अटल व्योम beiscsi_get_port_speed(काष्ठा Scsi_Host *shost)
अणु
	काष्ठा beiscsi_hba *phba = iscsi_host_priv(shost);
	काष्ठा iscsi_cls_host *ihost = shost->shost_data;

	चयन (phba->port_speed) अणु
	हाल BE2ISCSI_LINK_SPEED_10MBPS:
		ihost->port_speed = ISCSI_PORT_SPEED_10MBPS;
		अवरोध;
	हाल BE2ISCSI_LINK_SPEED_100MBPS:
		ihost->port_speed = ISCSI_PORT_SPEED_100MBPS;
		अवरोध;
	हाल BE2ISCSI_LINK_SPEED_1GBPS:
		ihost->port_speed = ISCSI_PORT_SPEED_1GBPS;
		अवरोध;
	हाल BE2ISCSI_LINK_SPEED_10GBPS:
		ihost->port_speed = ISCSI_PORT_SPEED_10GBPS;
		अवरोध;
	हाल BE2ISCSI_LINK_SPEED_25GBPS:
		ihost->port_speed = ISCSI_PORT_SPEED_25GBPS;
		अवरोध;
	हाल BE2ISCSI_LINK_SPEED_40GBPS:
		ihost->port_speed = ISCSI_PORT_SPEED_40GBPS;
		अवरोध;
	शेष:
		ihost->port_speed = ISCSI_PORT_SPEED_UNKNOWN;
	पूर्ण
पूर्ण

/**
 * beiscsi_get_host_param - get the iscsi parameter
 * @shost: poपूर्णांकer to scsi_host काष्ठाure
 * @param: parameter type identअगरier
 * @buf: buffer poपूर्णांकer
 *
 */
पूर्णांक beiscsi_get_host_param(काष्ठा Scsi_Host *shost,
			   क्रमागत iscsi_host_param param, अक्षर *buf)
अणु
	काष्ठा beiscsi_hba *phba = iscsi_host_priv(shost);
	पूर्णांक status = 0;

	अगर (!beiscsi_hba_is_online(phba)) अणु
		beiscsi_log(phba, KERN_INFO, BEISCSI_LOG_CONFIG,
			    "BS_%d : HBA in error 0x%lx\n", phba->state);
		वापस 0;
	पूर्ण
	beiscsi_log(phba, KERN_INFO, BEISCSI_LOG_CONFIG,
		    "BS_%d : In beiscsi_get_host_param, param = %d\n", param);

	चयन (param) अणु
	हाल ISCSI_HOST_PARAM_HWADDRESS:
		status = beiscsi_get_macaddr(buf, phba);
		अगर (status < 0) अणु
			beiscsi_log(phba, KERN_ERR, BEISCSI_LOG_CONFIG,
				    "BS_%d : beiscsi_get_macaddr Failed\n");
			वापस 0;
		पूर्ण
		अवरोध;
	हाल ISCSI_HOST_PARAM_INITIATOR_NAME:
		/* try fetching user configured name first */
		status = beiscsi_get_initiator_name(phba, buf, true);
		अगर (status < 0) अणु
			status = beiscsi_get_initiator_name(phba, buf, false);
			अगर (status < 0) अणु
				beiscsi_log(phba, KERN_ERR, BEISCSI_LOG_CONFIG,
					    "BS_%d : Retrieving Initiator Name Failed\n");
				status = 0;
			पूर्ण
		पूर्ण
		अवरोध;
	हाल ISCSI_HOST_PARAM_PORT_STATE:
		beiscsi_get_port_state(shost);
		status = प्र_लिखो(buf, "%s\n", iscsi_get_port_state_name(shost));
		अवरोध;
	हाल ISCSI_HOST_PARAM_PORT_SPEED:
		beiscsi_get_port_speed(shost);
		status = प्र_लिखो(buf, "%s\n", iscsi_get_port_speed_name(shost));
		अवरोध;
	शेष:
		वापस iscsi_host_get_param(shost, param, buf);
	पूर्ण
	वापस status;
पूर्ण

पूर्णांक beiscsi_get_macaddr(अक्षर *buf, काष्ठा beiscsi_hba *phba)
अणु
	काष्ठा be_cmd_get_nic_conf_resp resp;
	पूर्णांक rc;

	अगर (phba->mac_addr_set)
		वापस sysfs_क्रमmat_mac(buf, phba->mac_address, ETH_ALEN);

	स_रखो(&resp, 0, माप(resp));
	rc = mgmt_get_nic_conf(phba, &resp);
	अगर (rc)
		वापस rc;

	phba->mac_addr_set = true;
	स_नकल(phba->mac_address, resp.mac_address, ETH_ALEN);
	वापस sysfs_क्रमmat_mac(buf, phba->mac_address, ETH_ALEN);
पूर्ण

/**
 * beiscsi_conn_get_stats - get the iscsi stats
 * @cls_conn: poपूर्णांकer to iscsi cls conn
 * @stats: poपूर्णांकer to iscsi_stats काष्ठाure
 *
 * वापसs iscsi stats
 */
व्योम beiscsi_conn_get_stats(काष्ठा iscsi_cls_conn *cls_conn,
			    काष्ठा iscsi_stats *stats)
अणु
	काष्ठा iscsi_conn *conn = cls_conn->dd_data;
	काष्ठा beiscsi_hba *phba = शून्य;

	phba = ((काष्ठा beiscsi_conn *)conn->dd_data)->phba;
	beiscsi_log(phba, KERN_INFO, BEISCSI_LOG_CONFIG,
		    "BS_%d : In beiscsi_conn_get_stats\n");

	stats->txdata_octets = conn->txdata_octets;
	stats->rxdata_octets = conn->rxdata_octets;
	stats->dataout_pdus = conn->dataout_pdus_cnt;
	stats->scsirsp_pdus = conn->scsirsp_pdus_cnt;
	stats->scsicmd_pdus = conn->scsicmd_pdus_cnt;
	stats->datain_pdus = conn->datain_pdus_cnt;
	stats->पंचांगfrsp_pdus = conn->पंचांगfrsp_pdus_cnt;
	stats->पंचांगfcmd_pdus = conn->पंचांगfcmd_pdus_cnt;
	stats->r2t_pdus = conn->r2t_pdus_cnt;
	stats->digest_err = 0;
	stats->समयout_err = 0;
	stats->custom_length = 1;
	म_नकल(stats->custom[0].desc, "eh_abort_cnt");
	stats->custom[0].value = conn->eh_पात_cnt;
पूर्ण

/**
 * beiscsi_set_params_क्रम_offld - get the parameters क्रम offload
 * @beiscsi_conn: poपूर्णांकer to beiscsi_conn
 * @params: poपूर्णांकer to offload_params काष्ठाure
 */
अटल व्योम  beiscsi_set_params_क्रम_offld(काष्ठा beiscsi_conn *beiscsi_conn,
					  काष्ठा beiscsi_offload_params *params)
अणु
	काष्ठा iscsi_conn *conn = beiscsi_conn->conn;
	काष्ठा iscsi_session *session = conn->session;

	AMAP_SET_BITS(काष्ठा amap_beiscsi_offload_params, max_burst_length,
		      params, session->max_burst);
	AMAP_SET_BITS(काष्ठा amap_beiscsi_offload_params,
		      max_send_data_segment_length, params,
		      conn->max_xmit_dlength);
	AMAP_SET_BITS(काष्ठा amap_beiscsi_offload_params, first_burst_length,
		      params, session->first_burst);
	AMAP_SET_BITS(काष्ठा amap_beiscsi_offload_params, erl, params,
		      session->erl);
	AMAP_SET_BITS(काष्ठा amap_beiscsi_offload_params, dde, params,
		      conn->datadgst_en);
	AMAP_SET_BITS(काष्ठा amap_beiscsi_offload_params, hde, params,
		      conn->hdrdgst_en);
	AMAP_SET_BITS(काष्ठा amap_beiscsi_offload_params, ir2t, params,
		      session->initial_r2t_en);
	AMAP_SET_BITS(काष्ठा amap_beiscsi_offload_params, imd, params,
		      session->imm_data_en);
	AMAP_SET_BITS(काष्ठा amap_beiscsi_offload_params,
		      data_seq_inorder, params,
		      session->dataseq_inorder_en);
	AMAP_SET_BITS(काष्ठा amap_beiscsi_offload_params,
		      pdu_seq_inorder, params,
		      session->pdu_inorder_en);
	AMAP_SET_BITS(काष्ठा amap_beiscsi_offload_params, max_r2t, params,
		      session->max_r2t);
	AMAP_SET_BITS(काष्ठा amap_beiscsi_offload_params, exp_statsn, params,
		      (conn->exp_statsn - 1));
	AMAP_SET_BITS(काष्ठा amap_beiscsi_offload_params,
		      max_recv_data_segment_length, params,
		      conn->max_recv_dlength);

पूर्ण

/**
 * beiscsi_conn_start - offload of session to chip
 * @cls_conn: poपूर्णांकer to beiscsi_conn
 */
पूर्णांक beiscsi_conn_start(काष्ठा iscsi_cls_conn *cls_conn)
अणु
	काष्ठा iscsi_conn *conn = cls_conn->dd_data;
	काष्ठा beiscsi_conn *beiscsi_conn = conn->dd_data;
	काष्ठा beiscsi_endpoपूर्णांक *beiscsi_ep;
	काष्ठा beiscsi_offload_params params;
	काष्ठा beiscsi_hba *phba;

	phba = ((काष्ठा beiscsi_conn *)conn->dd_data)->phba;

	अगर (!beiscsi_hba_is_online(phba)) अणु
		beiscsi_log(phba, KERN_INFO, BEISCSI_LOG_CONFIG,
			    "BS_%d : HBA in error 0x%lx\n", phba->state);
		वापस -EBUSY;
	पूर्ण
	beiscsi_log(beiscsi_conn->phba, KERN_INFO, BEISCSI_LOG_CONFIG,
		    "BS_%d : In beiscsi_conn_start\n");

	स_रखो(&params, 0, माप(काष्ठा beiscsi_offload_params));
	beiscsi_ep = beiscsi_conn->ep;
	अगर (!beiscsi_ep)
		beiscsi_log(beiscsi_conn->phba, KERN_ERR,
			    BEISCSI_LOG_CONFIG,
			    "BS_%d : In beiscsi_conn_start , no beiscsi_ep\n");

	beiscsi_conn->login_in_progress = 0;
	beiscsi_set_params_क्रम_offld(beiscsi_conn, &params);
	beiscsi_offload_connection(beiscsi_conn, &params);
	iscsi_conn_start(cls_conn);
	वापस 0;
पूर्ण

/**
 * beiscsi_get_cid - Allocate a cid
 * @phba: The phba instance
 */
अटल पूर्णांक beiscsi_get_cid(काष्ठा beiscsi_hba *phba)
अणु
	uपूर्णांक16_t cid_avlbl_ulp0, cid_avlbl_ulp1;
	अचिन्हित लघु cid, cid_from_ulp;
	काष्ठा ulp_cid_info *cid_info;

	/* Find the ULP which has more CID available */
	cid_avlbl_ulp0 = (phba->cid_array_info[BEISCSI_ULP0]) ?
			  BEISCSI_ULP0_AVLBL_CID(phba) : 0;
	cid_avlbl_ulp1 = (phba->cid_array_info[BEISCSI_ULP1]) ?
			  BEISCSI_ULP1_AVLBL_CID(phba) : 0;
	cid_from_ulp = (cid_avlbl_ulp0 > cid_avlbl_ulp1) ?
			BEISCSI_ULP0 : BEISCSI_ULP1;
	/**
	 * If iSCSI protocol is loaded only on ULP 0, and when cid_avlbl_ulp
	 * is ZERO क्रम both, ULP 1 is वापसed.
	 * Check अगर ULP is loaded beक्रमe getting new CID.
	 */
	अगर (!test_bit(cid_from_ulp, (व्योम *)&phba->fw_config.ulp_supported))
		वापस BE_INVALID_CID;

	cid_info = phba->cid_array_info[cid_from_ulp];
	cid = cid_info->cid_array[cid_info->cid_alloc];
	अगर (!cid_info->avlbl_cids || cid == BE_INVALID_CID) अणु
		__beiscsi_log(phba, KERN_ERR,
				"BS_%d : failed to get cid: available %u:%u\n",
				cid_info->avlbl_cids, cid_info->cid_मुक्त);
		वापस BE_INVALID_CID;
	पूर्ण
	/* empty the slot */
	cid_info->cid_array[cid_info->cid_alloc++] = BE_INVALID_CID;
	अगर (cid_info->cid_alloc == BEISCSI_GET_CID_COUNT(phba, cid_from_ulp))
		cid_info->cid_alloc = 0;
	cid_info->avlbl_cids--;
	वापस cid;
पूर्ण

/**
 * beiscsi_put_cid - Free the cid
 * @phba: The phba क्रम which the cid is being मुक्तd
 * @cid: The cid to मुक्त
 */
अटल व्योम beiscsi_put_cid(काष्ठा beiscsi_hba *phba, अचिन्हित लघु cid)
अणु
	uपूर्णांक16_t cri_index = BE_GET_CRI_FROM_CID(cid);
	काष्ठा hwi_wrb_context *pwrb_context;
	काष्ठा hwi_controller *phwi_ctrlr;
	काष्ठा ulp_cid_info *cid_info;
	uपूर्णांक16_t cid_post_ulp;

	phwi_ctrlr = phba->phwi_ctrlr;
	pwrb_context = &phwi_ctrlr->wrb_context[cri_index];
	cid_post_ulp = pwrb_context->ulp_num;

	cid_info = phba->cid_array_info[cid_post_ulp];
	/* fill only in empty slot */
	अगर (cid_info->cid_array[cid_info->cid_मुक्त] != BE_INVALID_CID) अणु
		__beiscsi_log(phba, KERN_ERR,
			      "BS_%d : failed to put cid %u: available %u:%u\n",
			      cid, cid_info->avlbl_cids, cid_info->cid_मुक्त);
		वापस;
	पूर्ण
	cid_info->cid_array[cid_info->cid_मुक्त++] = cid;
	अगर (cid_info->cid_मुक्त == BEISCSI_GET_CID_COUNT(phba, cid_post_ulp))
		cid_info->cid_मुक्त = 0;
	cid_info->avlbl_cids++;
पूर्ण

/**
 * beiscsi_मुक्त_ep - मुक्त endpoपूर्णांक
 * @beiscsi_ep: poपूर्णांकer to device endpoपूर्णांक काष्ठा
 */
अटल व्योम beiscsi_मुक्त_ep(काष्ठा beiscsi_endpoपूर्णांक *beiscsi_ep)
अणु
	काष्ठा beiscsi_hba *phba = beiscsi_ep->phba;
	काष्ठा beiscsi_conn *beiscsi_conn;

	beiscsi_put_cid(phba, beiscsi_ep->ep_cid);
	beiscsi_ep->phba = शून्य;
	/* clear this to track मुक्तing in beiscsi_ep_disconnect */
	phba->ep_array[BE_GET_CRI_FROM_CID(beiscsi_ep->ep_cid)] = शून्य;

	/**
	 * Check अगर any connection resource allocated by driver
	 * is to be मुक्तd.This हाल occurs when target redirection
	 * or connection retry is करोne.
	 **/
	अगर (!beiscsi_ep->conn)
		वापस;

	beiscsi_conn = beiscsi_ep->conn;
	/**
	 * Break ep->conn link here so that completions after
	 * this are ignored.
	 */
	beiscsi_ep->conn = शून्य;
	अगर (beiscsi_conn->login_in_progress) अणु
		beiscsi_मुक्त_mgmt_task_handles(beiscsi_conn,
					       beiscsi_conn->task);
		beiscsi_conn->login_in_progress = 0;
	पूर्ण
पूर्ण

/**
 * beiscsi_खोलो_conn - Ask FW to खोलो a TCP connection
 * @ep: poपूर्णांकer to device endpoपूर्णांक काष्ठा
 * @src_addr: The source IP address
 * @dst_addr: The Destination  IP address
 * @non_blocking: blocking or non-blocking call
 *
 * Asks the FW to खोलो a TCP connection
 */
अटल पूर्णांक beiscsi_खोलो_conn(काष्ठा iscsi_endpoपूर्णांक *ep,
			     काष्ठा sockaddr *src_addr,
			     काष्ठा sockaddr *dst_addr, पूर्णांक non_blocking)
अणु
	काष्ठा beiscsi_endpoपूर्णांक *beiscsi_ep = ep->dd_data;
	काष्ठा beiscsi_hba *phba = beiscsi_ep->phba;
	काष्ठा tcp_connect_and_offload_out *ptcpcnct_out;
	काष्ठा be_dma_mem nonemb_cmd;
	अचिन्हित पूर्णांक tag, req_memsize;
	पूर्णांक ret = -ENOMEM;

	beiscsi_log(phba, KERN_INFO, BEISCSI_LOG_CONFIG,
		    "BS_%d : In beiscsi_open_conn\n");

	beiscsi_ep->ep_cid = beiscsi_get_cid(phba);
	अगर (beiscsi_ep->ep_cid == BE_INVALID_CID) अणु
		beiscsi_log(phba, KERN_ERR, BEISCSI_LOG_CONFIG,
			    "BS_%d : No free cid available\n");
		वापस ret;
	पूर्ण

	beiscsi_log(phba, KERN_INFO, BEISCSI_LOG_CONFIG,
		    "BS_%d : In beiscsi_open_conn, ep_cid=%d\n",
		    beiscsi_ep->ep_cid);

	phba->ep_array[BE_GET_CRI_FROM_CID
		       (beiscsi_ep->ep_cid)] = ep;

	beiscsi_ep->cid_vld = 0;

	अगर (is_chip_be2_be3r(phba))
		req_memsize = माप(काष्ठा tcp_connect_and_offload_in);
	अन्यथा
		req_memsize = माप(काष्ठा tcp_connect_and_offload_in_v1);

	nonemb_cmd.va = dma_alloc_coherent(&phba->ctrl.pdev->dev,
				req_memsize,
				&nonemb_cmd.dma, GFP_KERNEL);
	अगर (nonemb_cmd.va == शून्य) अणु

		beiscsi_log(phba, KERN_ERR, BEISCSI_LOG_CONFIG,
			    "BS_%d : Failed to allocate memory for"
			    " mgmt_open_connection\n");

		beiscsi_मुक्त_ep(beiscsi_ep);
		वापस -ENOMEM;
	पूर्ण
	nonemb_cmd.size = req_memsize;
	स_रखो(nonemb_cmd.va, 0, nonemb_cmd.size);
	tag = mgmt_खोलो_connection(phba, dst_addr, beiscsi_ep, &nonemb_cmd);
	अगर (!tag) अणु
		beiscsi_log(phba, KERN_ERR, BEISCSI_LOG_CONFIG,
			    "BS_%d : mgmt_open_connection Failed for cid=%d\n",
			    beiscsi_ep->ep_cid);

		dma_मुक्त_coherent(&phba->ctrl.pdev->dev, nonemb_cmd.size,
				    nonemb_cmd.va, nonemb_cmd.dma);
		beiscsi_मुक्त_ep(beiscsi_ep);
		वापस -EAGAIN;
	पूर्ण

	ret = beiscsi_mccq_compl_रुको(phba, tag, शून्य, &nonemb_cmd);
	अगर (ret) अणु
		beiscsi_log(phba, KERN_ERR,
			    BEISCSI_LOG_CONFIG | BEISCSI_LOG_MBOX,
			    "BS_%d : mgmt_open_connection Failed");

		अगर (ret != -EBUSY)
			dma_मुक्त_coherent(&phba->ctrl.pdev->dev,
					nonemb_cmd.size, nonemb_cmd.va,
					nonemb_cmd.dma);

		beiscsi_मुक्त_ep(beiscsi_ep);
		वापस ret;
	पूर्ण

	ptcpcnct_out = (काष्ठा tcp_connect_and_offload_out *)nonemb_cmd.va;
	beiscsi_ep = ep->dd_data;
	beiscsi_ep->fw_handle = ptcpcnct_out->connection_handle;
	beiscsi_ep->cid_vld = 1;
	beiscsi_log(phba, KERN_INFO, BEISCSI_LOG_CONFIG,
		    "BS_%d : mgmt_open_connection Success\n");

	dma_मुक्त_coherent(&phba->ctrl.pdev->dev, nonemb_cmd.size,
			    nonemb_cmd.va, nonemb_cmd.dma);
	वापस 0;
पूर्ण

/**
 * beiscsi_ep_connect - Ask chip to create TCP Conn
 * @shost: Poपूर्णांकer to scsi_host काष्ठाure
 * @dst_addr: The IP address of Target
 * @non_blocking: blocking or non-blocking call
 *
 * This routines first asks chip to create a connection and then allocates an EP
 */
काष्ठा iscsi_endpoपूर्णांक *
beiscsi_ep_connect(काष्ठा Scsi_Host *shost, काष्ठा sockaddr *dst_addr,
		   पूर्णांक non_blocking)
अणु
	काष्ठा beiscsi_hba *phba;
	काष्ठा beiscsi_endpoपूर्णांक *beiscsi_ep;
	काष्ठा iscsi_endpoपूर्णांक *ep;
	पूर्णांक ret;

	अगर (!shost) अणु
		ret = -ENXIO;
		pr_err("beiscsi_ep_connect shost is NULL\n");
		वापस ERR_PTR(ret);
	पूर्ण

	phba = iscsi_host_priv(shost);
	अगर (!beiscsi_hba_is_online(phba)) अणु
		ret = -EIO;
		beiscsi_log(phba, KERN_INFO, BEISCSI_LOG_CONFIG,
			    "BS_%d : HBA in error 0x%lx\n", phba->state);
		वापस ERR_PTR(ret);
	पूर्ण
	अगर (!test_bit(BEISCSI_HBA_LINK_UP, &phba->state)) अणु
		ret = -EBUSY;
		beiscsi_log(phba, KERN_WARNING, BEISCSI_LOG_CONFIG,
			    "BS_%d : The Adapter Port state is Down!!!\n");
		वापस ERR_PTR(ret);
	पूर्ण

	ep = iscsi_create_endpoपूर्णांक(माप(काष्ठा beiscsi_endpoपूर्णांक));
	अगर (!ep) अणु
		ret = -ENOMEM;
		वापस ERR_PTR(ret);
	पूर्ण

	beiscsi_ep = ep->dd_data;
	beiscsi_ep->phba = phba;
	beiscsi_ep->खोलोiscsi_ep = ep;
	ret = beiscsi_खोलो_conn(ep, शून्य, dst_addr, non_blocking);
	अगर (ret) अणु
		beiscsi_log(phba, KERN_ERR, BEISCSI_LOG_CONFIG,
			    "BS_%d : Failed in beiscsi_open_conn\n");
		जाओ मुक्त_ep;
	पूर्ण

	वापस ep;

मुक्त_ep:
	iscsi_destroy_endpoपूर्णांक(ep);
	वापस ERR_PTR(ret);
पूर्ण

/**
 * beiscsi_ep_poll - Poll to see अगर connection is established
 * @ep:	endpoपूर्णांक to be used
 * @समयout_ms: समयout specअगरied in millisecs
 *
 * Poll to see अगर TCP connection established
 */
पूर्णांक beiscsi_ep_poll(काष्ठा iscsi_endpoपूर्णांक *ep, पूर्णांक समयout_ms)
अणु
	काष्ठा beiscsi_endpoपूर्णांक *beiscsi_ep = ep->dd_data;

	beiscsi_log(beiscsi_ep->phba, KERN_INFO, BEISCSI_LOG_CONFIG,
		    "BS_%d : In  beiscsi_ep_poll\n");

	अगर (beiscsi_ep->cid_vld == 1)
		वापस 1;
	अन्यथा
		वापस 0;
पूर्ण

/**
 * beiscsi_flush_cq()- Flush the CQ created.
 * @phba: ptr device priv काष्ठाure.
 *
 * Beक्रमe the connection resource are मुक्तd flush
 * all the CQ enteries
 **/
अटल व्योम beiscsi_flush_cq(काष्ठा beiscsi_hba *phba)
अणु
	uपूर्णांक16_t i;
	काष्ठा be_eq_obj *pbe_eq;
	काष्ठा hwi_controller *phwi_ctrlr;
	काष्ठा hwi_context_memory *phwi_context;

	phwi_ctrlr = phba->phwi_ctrlr;
	phwi_context = phwi_ctrlr->phwi_ctxt;

	क्रम (i = 0; i < phba->num_cpus; i++) अणु
		pbe_eq = &phwi_context->be_eq[i];
		irq_poll_disable(&pbe_eq->iopoll);
		beiscsi_process_cq(pbe_eq, BE2_MAX_NUM_CQ_PROC);
		irq_poll_enable(&pbe_eq->iopoll);
	पूर्ण
पूर्ण

/**
 * beiscsi_conn_बंद - Invalidate and upload connection
 * @beiscsi_ep: poपूर्णांकer to device endpoपूर्णांक काष्ठा
 *
 * Returns 0 on success,  -1 on failure.
 */
अटल पूर्णांक beiscsi_conn_बंद(काष्ठा beiscsi_endpoपूर्णांक *beiscsi_ep)
अणु
	काष्ठा beiscsi_hba *phba = beiscsi_ep->phba;
	अचिन्हित पूर्णांक tag, attempts;
	पूर्णांक ret;

	/**
	 * Without successfully invalidating and uploading connection
	 * driver can't reuse the CID so attempt more than once.
	 */
	attempts = 0;
	जबतक (attempts++ < 3) अणु
		tag = beiscsi_invalidate_cxn(phba, beiscsi_ep);
		अगर (tag) अणु
			ret = beiscsi_mccq_compl_रुको(phba, tag, शून्य, शून्य);
			अगर (!ret)
				अवरोध;
			beiscsi_log(phba, KERN_INFO, BEISCSI_LOG_CONFIG,
				    "BS_%d : invalidate conn failed cid %d\n",
				    beiscsi_ep->ep_cid);
		पूर्ण
	पूर्ण

	/* रुको क्रम all completions to arrive, then process them */
	msleep(250);
	/* flush CQ entries */
	beiscsi_flush_cq(phba);

	अगर (attempts > 3)
		वापस -1;

	attempts = 0;
	जबतक (attempts++ < 3) अणु
		tag = beiscsi_upload_cxn(phba, beiscsi_ep);
		अगर (tag) अणु
			ret = beiscsi_mccq_compl_रुको(phba, tag, शून्य, शून्य);
			अगर (!ret)
				अवरोध;
			beiscsi_log(phba, KERN_INFO, BEISCSI_LOG_CONFIG,
				    "BS_%d : upload conn failed cid %d\n",
				    beiscsi_ep->ep_cid);
		पूर्ण
	पूर्ण
	अगर (attempts > 3)
		वापस -1;

	वापस 0;
पूर्ण

/**
 * beiscsi_ep_disconnect - Tears करोwn the TCP connection
 * @ep:	endpoपूर्णांक to be used
 *
 * Tears करोwn the TCP connection
 */
व्योम beiscsi_ep_disconnect(काष्ठा iscsi_endpoपूर्णांक *ep)
अणु
	काष्ठा beiscsi_endpoपूर्णांक *beiscsi_ep;
	काष्ठा beiscsi_conn *beiscsi_conn;
	काष्ठा beiscsi_hba *phba;
	uपूर्णांक16_t cri_index;

	beiscsi_ep = ep->dd_data;
	phba = beiscsi_ep->phba;
	beiscsi_log(phba, KERN_INFO, BEISCSI_LOG_CONFIG,
		    "BS_%d : In beiscsi_ep_disconnect for ep_cid = %u\n",
		    beiscsi_ep->ep_cid);

	cri_index = BE_GET_CRI_FROM_CID(beiscsi_ep->ep_cid);
	अगर (!phba->ep_array[cri_index]) अणु
		__beiscsi_log(phba, KERN_ERR,
			      "BS_%d : ep_array at %u cid %u empty\n",
			      cri_index,
			      beiscsi_ep->ep_cid);
		वापस;
	पूर्ण

	अगर (beiscsi_ep->conn) अणु
		beiscsi_conn = beiscsi_ep->conn;
		iscsi_suspend_queue(beiscsi_conn->conn);
	पूर्ण

	अगर (!beiscsi_hba_is_online(phba)) अणु
		beiscsi_log(phba, KERN_INFO, BEISCSI_LOG_CONFIG,
			    "BS_%d : HBA in error 0x%lx\n", phba->state);
	पूर्ण अन्यथा अणु
		/**
		 * Make CID available even अगर बंद fails.
		 * If not मुक्तd, FW might fail खोलो using the CID.
		 */
		अगर (beiscsi_conn_बंद(beiscsi_ep) < 0)
			__beiscsi_log(phba, KERN_ERR,
				      "BS_%d : close conn failed cid %d\n",
				      beiscsi_ep->ep_cid);
	पूर्ण

	beiscsi_मुक्त_ep(beiscsi_ep);
	अगर (!phba->conn_table[cri_index])
		__beiscsi_log(phba, KERN_ERR,
			      "BS_%d : conn_table empty at %u: cid %u\n",
			      cri_index, beiscsi_ep->ep_cid);
	phba->conn_table[cri_index] = शून्य;
	iscsi_destroy_endpoपूर्णांक(beiscsi_ep->खोलोiscsi_ep);
पूर्ण

umode_t beiscsi_attr_is_visible(पूर्णांक param_type, पूर्णांक param)
अणु
	चयन (param_type) अणु
	हाल ISCSI_NET_PARAM:
		चयन (param) अणु
		हाल ISCSI_NET_PARAM_IFACE_ENABLE:
		हाल ISCSI_NET_PARAM_IPV4_ADDR:
		हाल ISCSI_NET_PARAM_IPV4_SUBNET:
		हाल ISCSI_NET_PARAM_IPV4_BOOTPROTO:
		हाल ISCSI_NET_PARAM_IPV4_GW:
		हाल ISCSI_NET_PARAM_IPV6_ADDR:
		हाल ISCSI_NET_PARAM_VLAN_ID:
		हाल ISCSI_NET_PARAM_VLAN_PRIORITY:
		हाल ISCSI_NET_PARAM_VLAN_ENABLED:
			वापस S_IRUGO;
		शेष:
			वापस 0;
		पूर्ण
	हाल ISCSI_HOST_PARAM:
		चयन (param) अणु
		हाल ISCSI_HOST_PARAM_HWADDRESS:
		हाल ISCSI_HOST_PARAM_INITIATOR_NAME:
		हाल ISCSI_HOST_PARAM_PORT_STATE:
		हाल ISCSI_HOST_PARAM_PORT_SPEED:
			वापस S_IRUGO;
		शेष:
			वापस 0;
		पूर्ण
	हाल ISCSI_PARAM:
		चयन (param) अणु
		हाल ISCSI_PARAM_MAX_RECV_DLENGTH:
		हाल ISCSI_PARAM_MAX_XMIT_DLENGTH:
		हाल ISCSI_PARAM_HDRDGST_EN:
		हाल ISCSI_PARAM_DATADGST_EN:
		हाल ISCSI_PARAM_CONN_ADDRESS:
		हाल ISCSI_PARAM_CONN_PORT:
		हाल ISCSI_PARAM_EXP_STATSN:
		हाल ISCSI_PARAM_PERSISTENT_ADDRESS:
		हाल ISCSI_PARAM_PERSISTENT_PORT:
		हाल ISCSI_PARAM_PING_TMO:
		हाल ISCSI_PARAM_RECV_TMO:
		हाल ISCSI_PARAM_INITIAL_R2T_EN:
		हाल ISCSI_PARAM_MAX_R2T:
		हाल ISCSI_PARAM_IMM_DATA_EN:
		हाल ISCSI_PARAM_FIRST_BURST:
		हाल ISCSI_PARAM_MAX_BURST:
		हाल ISCSI_PARAM_PDU_INORDER_EN:
		हाल ISCSI_PARAM_DATASEQ_INORDER_EN:
		हाल ISCSI_PARAM_ERL:
		हाल ISCSI_PARAM_TARGET_NAME:
		हाल ISCSI_PARAM_TPGT:
		हाल ISCSI_PARAM_USERNAME:
		हाल ISCSI_PARAM_PASSWORD:
		हाल ISCSI_PARAM_USERNAME_IN:
		हाल ISCSI_PARAM_PASSWORD_IN:
		हाल ISCSI_PARAM_FAST_ABORT:
		हाल ISCSI_PARAM_ABORT_TMO:
		हाल ISCSI_PARAM_LU_RESET_TMO:
		हाल ISCSI_PARAM_IFACE_NAME:
		हाल ISCSI_PARAM_INITIATOR_NAME:
			वापस S_IRUGO;
		शेष:
			वापस 0;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण
