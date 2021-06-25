<शैली गुरु>
/*
 * Copyright(c) 2017 Intel Corporation.
 *
 * This file is provided under a dual BSD/GPLv2 license.  When using or
 * redistributing this file, you may करो so under either license.
 *
 * GPL LICENSE SUMMARY
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of version 2 of the GNU General Public License as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License क्रम more details.
 *
 * BSD LICENSE
 *
 * Redistribution and use in source and binary क्रमms, with or without
 * modअगरication, are permitted provided that the following conditions
 * are met:
 *
 *  - Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *  - Redistributions in binary क्रमm must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the करोcumentation and/or other materials provided with the
 *    distribution.
 *  - Neither the name of Intel Corporation nor the names of its
 *    contributors may be used to enकरोrse or promote products derived
 *    from this software without specअगरic prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY सूचीECT, INसूचीECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

/*
 * This file contains OPA Virtual Network Interface Controller (VNIC)
 * Ethernet Management Agent (EMA) driver
 */

#समावेश <linux/module.h>
#समावेश <linux/xarray.h>
#समावेश <rdma/ib_addr.h>
#समावेश <rdma/ib_verbs.h>
#समावेश <rdma/opa_smi.h>
#समावेश <rdma/opa_port_info.h>

#समावेश "opa_vnic_internal.h"

अक्षर opa_vnic_driver_name[] = "opa_vnic";

/*
 * The trap service level is kept in bits 3 to 7 in the trap_sl_rsvd
 * field in the class port info MAD.
 */
#घोषणा GET_TRAP_SL_FROM_CLASS_PORT_INFO(x)  (((x) >> 3) & 0x1f)

/* Cap trap bursts to a reasonable limit good क्रम normal हालs */
#घोषणा OPA_VNIC_TRAP_BURST_LIMIT 4

/*
 * VNIC trap limit समयout.
 * Inverse of cap2_mask response समय out (1.0737 secs) = 0.9
 * secs approx IB spec 13.4.6.2.1 PortInfoSubnetTimeout and
 * 13.4.9 Traps.
 */
#घोषणा OPA_VNIC_TRAP_TIMEOUT  ((4096 * (1UL << 18)) / 1000)

#घोषणा OPA_VNIC_UNSUP_ATTR  \
		cpu_to_be16(IB_MGMT_MAD_STATUS_UNSUPPORTED_METHOD_ATTRIB)

#घोषणा OPA_VNIC_INVAL_ATTR  \
		cpu_to_be16(IB_MGMT_MAD_STATUS_INVALID_ATTRIB_VALUE)

#घोषणा OPA_VNIC_CLASS_CAP_TRAP   0x1

/* Maximum number of VNIC ports supported */
#घोषणा OPA_VNIC_MAX_NUM_VPORT    255

/**
 * काष्ठा opa_vnic_vema_port -- VNIC VEMA port details
 * @cport: poपूर्णांकer to port
 * @mad_agent: poपूर्णांकer to mad agent क्रम port
 * @class_port_info: Class port info inक्रमmation.
 * @tid: Transaction id
 * @port_num: OPA port number
 * @vports: vnic ports
 * @event_handler: ib event handler
 * @lock: adapter पूर्णांकerface lock
 */
काष्ठा opa_vnic_vema_port अणु
	काष्ठा opa_vnic_ctrl_port      *cport;
	काष्ठा ib_mad_agent            *mad_agent;
	काष्ठा opa_class_port_info      class_port_info;
	u64                             tid;
	u8                              port_num;
	काष्ठा xarray                   vports;
	काष्ठा ib_event_handler         event_handler;

	/* Lock to query/update network adapter */
	काष्ठा mutex                    lock;
पूर्ण;

अटल पूर्णांक opa_vnic_vema_add_one(काष्ठा ib_device *device);
अटल व्योम opa_vnic_vema_rem_one(काष्ठा ib_device *device,
				  व्योम *client_data);

अटल काष्ठा ib_client opa_vnic_client = अणु
	.name   = opa_vnic_driver_name,
	.add    = opa_vnic_vema_add_one,
	.हटाओ = opa_vnic_vema_rem_one,
पूर्ण;

/**
 * vema_get_vport_num -- Get the vnic from the mad
 * @recvd_mad:  Received mad
 *
 * Return: वापसs value of the vnic port number
 */
अटल अंतरभूत u8 vema_get_vport_num(काष्ठा opa_vnic_vema_mad *recvd_mad)
अणु
	वापस be32_to_cpu(recvd_mad->mad_hdr.attr_mod) & 0xff;
पूर्ण

/**
 * vema_get_vport_adapter -- Get vnic port adapter from recvd mad
 * @recvd_mad: received mad
 * @port: ptr to port काष्ठा on which MAD was recvd
 *
 * Return: vnic adapter
 */
अटल अंतरभूत काष्ठा opa_vnic_adapter *
vema_get_vport_adapter(काष्ठा opa_vnic_vema_mad *recvd_mad,
		       काष्ठा opa_vnic_vema_port *port)
अणु
	u8 vport_num = vema_get_vport_num(recvd_mad);

	वापस xa_load(&port->vports, vport_num);
पूर्ण

/**
 * vema_mac_tbl_req_ok -- Check अगर mac request has correct values
 * @mac_tbl: mac table
 *
 * This function checks क्रम the validity of the offset and number of
 * entries required.
 *
 * Return: true अगर offset and num_entries are valid
 */
अटल अंतरभूत bool vema_mac_tbl_req_ok(काष्ठा opa_veswport_mactable *mac_tbl)
अणु
	u16 offset, num_entries;
	u16 req_entries = ((OPA_VNIC_EMA_DATA - माप(*mac_tbl)) /
			   माप(mac_tbl->tbl_entries[0]));

	offset = be16_to_cpu(mac_tbl->offset);
	num_entries = be16_to_cpu(mac_tbl->num_entries);

	वापस ((num_entries <= req_entries) &&
		(offset + num_entries <= OPA_VNIC_MAC_TBL_MAX_ENTRIES));
पूर्ण

/*
 * Return the घातer on शेष values in the port info काष्ठाure
 * in big endian क्रमmat as required by MAD.
 */
अटल अंतरभूत व्योम vema_get_pod_values(काष्ठा opa_veswport_info *port_info)
अणु
	स_रखो(port_info, 0, माप(*port_info));
	port_info->vport.max_mac_tbl_ent =
		cpu_to_be16(OPA_VNIC_MAC_TBL_MAX_ENTRIES);
	port_info->vport.max_smac_ent =
		cpu_to_be16(OPA_VNIC_MAX_SMAC_LIMIT);
	port_info->vport.oper_state = OPA_VNIC_STATE_DROP_ALL;
	port_info->vport.config_state = OPA_VNIC_STATE_DROP_ALL;
	port_info->vesw.eth_mtu = cpu_to_be16(ETH_DATA_LEN);
पूर्ण

/**
 * vema_add_vport -- Add a new vnic port
 * @port: ptr to opa_vnic_vema_port काष्ठा
 * @vport_num: vnic port number (to be added)
 *
 * Return a poपूर्णांकer to the vnic adapter काष्ठाure
 */
अटल काष्ठा opa_vnic_adapter *vema_add_vport(काष्ठा opa_vnic_vema_port *port,
					       u8 vport_num)
अणु
	काष्ठा opa_vnic_ctrl_port *cport = port->cport;
	काष्ठा opa_vnic_adapter *adapter;

	adapter = opa_vnic_add_netdev(cport->ibdev, port->port_num, vport_num);
	अगर (!IS_ERR(adapter)) अणु
		पूर्णांक rc;

		adapter->cport = cport;
		rc = xa_insert(&port->vports, vport_num, adapter, GFP_KERNEL);
		अगर (rc < 0) अणु
			opa_vnic_rem_netdev(adapter);
			adapter = ERR_PTR(rc);
		पूर्ण
	पूर्ण

	वापस adapter;
पूर्ण

/**
 * vema_get_class_port_info -- Get class info क्रम port
 * @port:  Port on whic MAD was received
 * @recvd_mad: poपूर्णांकer to the received mad
 * @rsp_mad:   poपूर्णांकer to respose mad
 *
 * This function copies the latest class port info value set क्रम the
 * port and stores it क्रम generating traps
 */
अटल व्योम vema_get_class_port_info(काष्ठा opa_vnic_vema_port *port,
				     काष्ठा opa_vnic_vema_mad *recvd_mad,
				     काष्ठा opa_vnic_vema_mad *rsp_mad)
अणु
	काष्ठा opa_class_port_info *port_info;

	port_info = (काष्ठा opa_class_port_info *)rsp_mad->data;
	स_नकल(port_info, &port->class_port_info, माप(*port_info));
	port_info->base_version = OPA_MGMT_BASE_VERSION;
	port_info->class_version = OPA_EMA_CLASS_VERSION;

	/*
	 * Set capability mask bit indicating agent generates traps,
	 * and set the maximum number of VNIC ports supported.
	 */
	port_info->cap_mask = cpu_to_be16((OPA_VNIC_CLASS_CAP_TRAP |
					   (OPA_VNIC_MAX_NUM_VPORT << 8)));

	/*
	 * Since a get routine is always sent by the EM first we
	 * set the expected response समय to
	 * 4.096 usec * 2^18 == 1.0737 sec here.
	 */
	port_info->cap_mask2_resp_समय = cpu_to_be32(18);
पूर्ण

/**
 * vema_set_class_port_info -- Get class info क्रम port
 * @port:  Port on whic MAD was received
 * @recvd_mad: poपूर्णांकer to the received mad
 * @rsp_mad:   poपूर्णांकer to respose mad
 *
 * This function updates the port class info क्रम the specअगरic vnic
 * and sets up the response mad data
 */
अटल व्योम vema_set_class_port_info(काष्ठा opa_vnic_vema_port *port,
				     काष्ठा opa_vnic_vema_mad *recvd_mad,
				     काष्ठा opa_vnic_vema_mad *rsp_mad)
अणु
	स_नकल(&port->class_port_info, recvd_mad->data,
	       माप(port->class_port_info));

	vema_get_class_port_info(port, recvd_mad, rsp_mad);
पूर्ण

/**
 * vema_get_veswport_info -- Get veswport info
 * @port:      source port on which MAD was received
 * @recvd_mad: poपूर्णांकer to the received mad
 * @rsp_mad:   poपूर्णांकer to respose mad
 */
अटल व्योम vema_get_veswport_info(काष्ठा opa_vnic_vema_port *port,
				   काष्ठा opa_vnic_vema_mad *recvd_mad,
				   काष्ठा opa_vnic_vema_mad *rsp_mad)
अणु
	काष्ठा opa_veswport_info *port_info =
				  (काष्ठा opa_veswport_info *)rsp_mad->data;
	काष्ठा opa_vnic_adapter *adapter;

	adapter = vema_get_vport_adapter(recvd_mad, port);
	अगर (adapter) अणु
		स_रखो(port_info, 0, माप(*port_info));
		opa_vnic_get_vesw_info(adapter, &port_info->vesw);
		opa_vnic_get_per_veswport_info(adapter,
					       &port_info->vport);
	पूर्ण अन्यथा अणु
		vema_get_pod_values(port_info);
	पूर्ण
पूर्ण

/**
 * vema_set_veswport_info -- Set veswport info
 * @port:      source port on which MAD was received
 * @recvd_mad: poपूर्णांकer to the received mad
 * @rsp_mad:   poपूर्णांकer to respose mad
 *
 * This function माला_लो the port class inक्रम क्रम vnic
 */
अटल व्योम vema_set_veswport_info(काष्ठा opa_vnic_vema_port *port,
				   काष्ठा opa_vnic_vema_mad *recvd_mad,
				   काष्ठा opa_vnic_vema_mad *rsp_mad)
अणु
	काष्ठा opa_vnic_ctrl_port *cport = port->cport;
	काष्ठा opa_veswport_info *port_info;
	काष्ठा opa_vnic_adapter *adapter;
	u8 vport_num;

	vport_num = vema_get_vport_num(recvd_mad);

	adapter = vema_get_vport_adapter(recvd_mad, port);
	अगर (!adapter) अणु
		adapter = vema_add_vport(port, vport_num);
		अगर (IS_ERR(adapter)) अणु
			c_err("failed to add vport %d: %ld\n",
			      vport_num, PTR_ERR(adapter));
			जाओ err_निकास;
		पूर्ण
	पूर्ण

	port_info = (काष्ठा opa_veswport_info *)recvd_mad->data;
	opa_vnic_set_vesw_info(adapter, &port_info->vesw);
	opa_vnic_set_per_veswport_info(adapter, &port_info->vport);

	/* Process the new config settings */
	opa_vnic_process_vema_config(adapter);

	vema_get_veswport_info(port, recvd_mad, rsp_mad);
	वापस;

err_निकास:
	rsp_mad->mad_hdr.status = OPA_VNIC_INVAL_ATTR;
पूर्ण

/**
 * vema_get_mac_entries -- Get MAC entries in VNIC MAC table
 * @port:      source port on which MAD was received
 * @recvd_mad: poपूर्णांकer to the received mad
 * @rsp_mad:   poपूर्णांकer to respose mad
 *
 * This function माला_लो the MAC entries that are programmed पूर्णांकo
 * the VNIC MAC क्रमwarding table. It checks क्रम the validity of
 * the index पूर्णांकo the MAC table and the number of entries that
 * are to be retrieved.
 */
अटल व्योम vema_get_mac_entries(काष्ठा opa_vnic_vema_port *port,
				 काष्ठा opa_vnic_vema_mad *recvd_mad,
				 काष्ठा opa_vnic_vema_mad *rsp_mad)
अणु
	काष्ठा opa_veswport_mactable *mac_tbl_in, *mac_tbl_out;
	काष्ठा opa_vnic_adapter *adapter;

	adapter = vema_get_vport_adapter(recvd_mad, port);
	अगर (!adapter) अणु
		rsp_mad->mad_hdr.status = OPA_VNIC_INVAL_ATTR;
		वापस;
	पूर्ण

	mac_tbl_in = (काष्ठा opa_veswport_mactable *)recvd_mad->data;
	mac_tbl_out = (काष्ठा opa_veswport_mactable *)rsp_mad->data;

	अगर (vema_mac_tbl_req_ok(mac_tbl_in)) अणु
		mac_tbl_out->offset = mac_tbl_in->offset;
		mac_tbl_out->num_entries = mac_tbl_in->num_entries;
		opa_vnic_query_mac_tbl(adapter, mac_tbl_out);
	पूर्ण अन्यथा अणु
		rsp_mad->mad_hdr.status = OPA_VNIC_INVAL_ATTR;
	पूर्ण
पूर्ण

/**
 * vema_set_mac_entries -- Set MAC entries in VNIC MAC table
 * @port:      source port on which MAD was received
 * @recvd_mad: poपूर्णांकer to the received mad
 * @rsp_mad:   poपूर्णांकer to respose mad
 *
 * This function sets the MAC entries in the VNIC क्रमwarding table
 * It checks क्रम the validity of the index and the number of क्रमwarding
 * table entries to be programmed.
 */
अटल व्योम vema_set_mac_entries(काष्ठा opa_vnic_vema_port *port,
				 काष्ठा opa_vnic_vema_mad *recvd_mad,
				 काष्ठा opa_vnic_vema_mad *rsp_mad)
अणु
	काष्ठा opa_veswport_mactable *mac_tbl;
	काष्ठा opa_vnic_adapter *adapter;

	adapter = vema_get_vport_adapter(recvd_mad, port);
	अगर (!adapter) अणु
		rsp_mad->mad_hdr.status = OPA_VNIC_INVAL_ATTR;
		वापस;
	पूर्ण

	mac_tbl = (काष्ठा opa_veswport_mactable *)recvd_mad->data;
	अगर (vema_mac_tbl_req_ok(mac_tbl)) अणु
		अगर (opa_vnic_update_mac_tbl(adapter, mac_tbl))
			rsp_mad->mad_hdr.status = OPA_VNIC_UNSUP_ATTR;
	पूर्ण अन्यथा अणु
		rsp_mad->mad_hdr.status = OPA_VNIC_UNSUP_ATTR;
	पूर्ण
	vema_get_mac_entries(port, recvd_mad, rsp_mad);
पूर्ण

/**
 * vema_set_delete_vesw -- Reset VESW info to POD values
 * @port:      source port on which MAD was received
 * @recvd_mad: poपूर्णांकer to the received mad
 * @rsp_mad:   poपूर्णांकer to respose mad
 *
 * This function clears all the fields of veswport info क्रम the requested vesw
 * and sets them back to the घातer-on शेष values. It करोes not delete the
 * vesw.
 */
अटल व्योम vema_set_delete_vesw(काष्ठा opa_vnic_vema_port *port,
				 काष्ठा opa_vnic_vema_mad *recvd_mad,
				 काष्ठा opa_vnic_vema_mad *rsp_mad)
अणु
	काष्ठा opa_veswport_info *port_info =
				  (काष्ठा opa_veswport_info *)rsp_mad->data;
	काष्ठा opa_vnic_adapter *adapter;

	adapter = vema_get_vport_adapter(recvd_mad, port);
	अगर (!adapter) अणु
		rsp_mad->mad_hdr.status = OPA_VNIC_INVAL_ATTR;
		वापस;
	पूर्ण

	vema_get_pod_values(port_info);
	opa_vnic_set_vesw_info(adapter, &port_info->vesw);
	opa_vnic_set_per_veswport_info(adapter, &port_info->vport);

	/* Process the new config settings */
	opa_vnic_process_vema_config(adapter);

	opa_vnic_release_mac_tbl(adapter);

	vema_get_veswport_info(port, recvd_mad, rsp_mad);
पूर्ण

/**
 * vema_get_mac_list -- Get the unicast/multicast macs.
 * @port:      source port on which MAD was received
 * @recvd_mad: Received mad contains fields to set vnic parameters
 * @rsp_mad:   Response mad to be built
 * @attr_id:   Attribute ID indicating multicast or unicast mac list
 */
अटल व्योम vema_get_mac_list(काष्ठा opa_vnic_vema_port *port,
			      काष्ठा opa_vnic_vema_mad *recvd_mad,
			      काष्ठा opa_vnic_vema_mad *rsp_mad,
			      u16 attr_id)
अणु
	काष्ठा opa_veswport_अगरace_macs *macs_in, *macs_out;
	पूर्णांक max_entries = (OPA_VNIC_EMA_DATA - माप(*macs_out)) / ETH_ALEN;
	काष्ठा opa_vnic_adapter *adapter;

	adapter = vema_get_vport_adapter(recvd_mad, port);
	अगर (!adapter) अणु
		rsp_mad->mad_hdr.status = OPA_VNIC_INVAL_ATTR;
		वापस;
	पूर्ण

	macs_in = (काष्ठा opa_veswport_अगरace_macs *)recvd_mad->data;
	macs_out = (काष्ठा opa_veswport_अगरace_macs *)rsp_mad->data;

	macs_out->start_idx = macs_in->start_idx;
	अगर (macs_in->num_macs_in_msg)
		macs_out->num_macs_in_msg = macs_in->num_macs_in_msg;
	अन्यथा
		macs_out->num_macs_in_msg = cpu_to_be16(max_entries);

	अगर (attr_id == OPA_EM_ATTR_IFACE_MCAST_MACS)
		opa_vnic_query_mcast_macs(adapter, macs_out);
	अन्यथा
		opa_vnic_query_ucast_macs(adapter, macs_out);
पूर्ण

/**
 * vema_get_summary_counters -- Gets summary counters.
 * @port:      source port on which MAD was received
 * @recvd_mad: Received mad contains fields to set vnic parameters
 * @rsp_mad:   Response mad to be built
 */
अटल व्योम vema_get_summary_counters(काष्ठा opa_vnic_vema_port *port,
				      काष्ठा opa_vnic_vema_mad *recvd_mad,
				      काष्ठा opa_vnic_vema_mad *rsp_mad)
अणु
	काष्ठा opa_veswport_summary_counters *cntrs;
	काष्ठा opa_vnic_adapter *adapter;

	adapter = vema_get_vport_adapter(recvd_mad, port);
	अगर (adapter) अणु
		cntrs = (काष्ठा opa_veswport_summary_counters *)rsp_mad->data;
		opa_vnic_get_summary_counters(adapter, cntrs);
	पूर्ण अन्यथा अणु
		rsp_mad->mad_hdr.status = OPA_VNIC_INVAL_ATTR;
	पूर्ण
पूर्ण

/**
 * vema_get_error_counters -- Gets summary counters.
 * @port:      source port on which MAD was received
 * @recvd_mad: Received mad contains fields to set vnic parameters
 * @rsp_mad:   Response mad to be built
 */
अटल व्योम vema_get_error_counters(काष्ठा opa_vnic_vema_port *port,
				    काष्ठा opa_vnic_vema_mad *recvd_mad,
				    काष्ठा opa_vnic_vema_mad *rsp_mad)
अणु
	काष्ठा opa_veswport_error_counters *cntrs;
	काष्ठा opa_vnic_adapter *adapter;

	adapter = vema_get_vport_adapter(recvd_mad, port);
	अगर (adapter) अणु
		cntrs = (काष्ठा opa_veswport_error_counters *)rsp_mad->data;
		opa_vnic_get_error_counters(adapter, cntrs);
	पूर्ण अन्यथा अणु
		rsp_mad->mad_hdr.status = OPA_VNIC_INVAL_ATTR;
	पूर्ण
पूर्ण

/**
 * vema_get -- Process received get MAD
 * @port:      source port on which MAD was received
 * @recvd_mad: Received mad
 * @rsp_mad:   Response mad to be built
 */
अटल व्योम vema_get(काष्ठा opa_vnic_vema_port *port,
		     काष्ठा opa_vnic_vema_mad *recvd_mad,
		     काष्ठा opa_vnic_vema_mad *rsp_mad)
अणु
	u16 attr_id = be16_to_cpu(recvd_mad->mad_hdr.attr_id);

	चयन (attr_id) अणु
	हाल OPA_EM_ATTR_CLASS_PORT_INFO:
		vema_get_class_port_info(port, recvd_mad, rsp_mad);
		अवरोध;
	हाल OPA_EM_ATTR_VESWPORT_INFO:
		vema_get_veswport_info(port, recvd_mad, rsp_mad);
		अवरोध;
	हाल OPA_EM_ATTR_VESWPORT_MAC_ENTRIES:
		vema_get_mac_entries(port, recvd_mad, rsp_mad);
		अवरोध;
	हाल OPA_EM_ATTR_IFACE_UCAST_MACS:
	हाल OPA_EM_ATTR_IFACE_MCAST_MACS:
		vema_get_mac_list(port, recvd_mad, rsp_mad, attr_id);
		अवरोध;
	हाल OPA_EM_ATTR_VESWPORT_SUMMARY_COUNTERS:
		vema_get_summary_counters(port, recvd_mad, rsp_mad);
		अवरोध;
	हाल OPA_EM_ATTR_VESWPORT_ERROR_COUNTERS:
		vema_get_error_counters(port, recvd_mad, rsp_mad);
		अवरोध;
	शेष:
		rsp_mad->mad_hdr.status = OPA_VNIC_UNSUP_ATTR;
		अवरोध;
	पूर्ण
पूर्ण

/**
 * vema_set -- Process received set MAD
 * @port:      source port on which MAD was received
 * @recvd_mad: Received mad contains fields to set vnic parameters
 * @rsp_mad:   Response mad to be built
 */
अटल व्योम vema_set(काष्ठा opa_vnic_vema_port *port,
		     काष्ठा opa_vnic_vema_mad *recvd_mad,
		     काष्ठा opa_vnic_vema_mad *rsp_mad)
अणु
	u16 attr_id = be16_to_cpu(recvd_mad->mad_hdr.attr_id);

	चयन (attr_id) अणु
	हाल OPA_EM_ATTR_CLASS_PORT_INFO:
		vema_set_class_port_info(port, recvd_mad, rsp_mad);
		अवरोध;
	हाल OPA_EM_ATTR_VESWPORT_INFO:
		vema_set_veswport_info(port, recvd_mad, rsp_mad);
		अवरोध;
	हाल OPA_EM_ATTR_VESWPORT_MAC_ENTRIES:
		vema_set_mac_entries(port, recvd_mad, rsp_mad);
		अवरोध;
	हाल OPA_EM_ATTR_DELETE_VESW:
		vema_set_delete_vesw(port, recvd_mad, rsp_mad);
		अवरोध;
	शेष:
		rsp_mad->mad_hdr.status = OPA_VNIC_UNSUP_ATTR;
		अवरोध;
	पूर्ण
पूर्ण

/**
 * vema_send -- Send handler क्रम VEMA MAD agent
 * @mad_agent: poपूर्णांकer to the mad agent
 * @mad_wc:    poपूर्णांकer to mad send work completion inक्रमmation
 *
 * Free all the data काष्ठाures associated with the sent MAD
 */
अटल व्योम vema_send(काष्ठा ib_mad_agent *mad_agent,
		      काष्ठा ib_mad_send_wc *mad_wc)
अणु
	rdma_destroy_ah(mad_wc->send_buf->ah, RDMA_DESTROY_AH_SLEEPABLE);
	ib_मुक्त_send_mad(mad_wc->send_buf);
पूर्ण

/**
 * vema_recv -- Recv handler क्रम VEMA MAD agent
 * @mad_agent: poपूर्णांकer to the mad agent
 * @send_buf: Send buffer अगर found, अन्यथा शून्य
 * @mad_wc:    poपूर्णांकer to mad send work completion inक्रमmation
 *
 * Handle only set and get methods and respond to other methods
 * as unsupported. Allocate response buffer and address handle
 * क्रम the response MAD.
 */
अटल व्योम vema_recv(काष्ठा ib_mad_agent *mad_agent,
		      काष्ठा ib_mad_send_buf *send_buf,
		      काष्ठा ib_mad_recv_wc *mad_wc)
अणु
	काष्ठा opa_vnic_vema_port *port;
	काष्ठा ib_ah              *ah;
	काष्ठा ib_mad_send_buf    *rsp;
	काष्ठा opa_vnic_vema_mad  *vema_mad;

	अगर (!mad_wc || !mad_wc->recv_buf.mad)
		वापस;

	port = mad_agent->context;
	ah = ib_create_ah_from_wc(mad_agent->qp->pd, mad_wc->wc,
				  mad_wc->recv_buf.grh, mad_agent->port_num);
	अगर (IS_ERR(ah))
		जाओ मुक्त_recv_mad;

	rsp = ib_create_send_mad(mad_agent, mad_wc->wc->src_qp,
				 mad_wc->wc->pkey_index, 0,
				 IB_MGMT_VENDOR_HDR, OPA_VNIC_EMA_DATA,
				 GFP_KERNEL, OPA_MGMT_BASE_VERSION);
	अगर (IS_ERR(rsp))
		जाओ err_rsp;

	rsp->ah = ah;
	vema_mad = rsp->mad;
	स_नकल(vema_mad, mad_wc->recv_buf.mad, IB_MGMT_VENDOR_HDR);
	vema_mad->mad_hdr.method = IB_MGMT_METHOD_GET_RESP;
	vema_mad->mad_hdr.status = 0;

	/* Lock ensures network adapter is not हटाओd */
	mutex_lock(&port->lock);

	चयन (mad_wc->recv_buf.mad->mad_hdr.method) अणु
	हाल IB_MGMT_METHOD_GET:
		vema_get(port, (काष्ठा opa_vnic_vema_mad *)mad_wc->recv_buf.mad,
			 vema_mad);
		अवरोध;
	हाल IB_MGMT_METHOD_SET:
		vema_set(port, (काष्ठा opa_vnic_vema_mad *)mad_wc->recv_buf.mad,
			 vema_mad);
		अवरोध;
	शेष:
		vema_mad->mad_hdr.status = OPA_VNIC_UNSUP_ATTR;
		अवरोध;
	पूर्ण
	mutex_unlock(&port->lock);

	अगर (!ib_post_send_mad(rsp, शून्य)) अणु
		/*
		 * with post send successful ah and send mad
		 * will be destroyed in send handler
		 */
		जाओ मुक्त_recv_mad;
	पूर्ण

	ib_मुक्त_send_mad(rsp);

err_rsp:
	rdma_destroy_ah(ah, RDMA_DESTROY_AH_SLEEPABLE);
मुक्त_recv_mad:
	ib_मुक्त_recv_mad(mad_wc);
पूर्ण

/**
 * vema_get_port -- Gets the opa_vnic_vema_port
 * @cport: poपूर्णांकer to control dev
 * @port_num: Port number
 *
 * This function loops through the ports and वापसs
 * the opa_vnic_vema port काष्ठाure that is associated
 * with the OPA port number
 *
 * Return: ptr to requested opa_vnic_vema_port strucure
 *         अगर success, शून्य अगर not
 */
अटल काष्ठा opa_vnic_vema_port *
vema_get_port(काष्ठा opa_vnic_ctrl_port *cport, u8 port_num)
अणु
	काष्ठा opa_vnic_vema_port *port = (व्योम *)cport + माप(*cport);

	अगर (port_num > cport->num_ports)
		वापस शून्य;

	वापस port + (port_num - 1);
पूर्ण

/**
 * opa_vnic_vema_send_trap -- This function sends a trap to the EM
 * @adapter: poपूर्णांकer to vnic adapter
 * @data: poपूर्णांकer to trap data filled by calling function
 * @lid:  issuers lid (encap_slid from vesw_port_info)
 *
 * This function is called from the VNIC driver to send a trap अगर there
 * is somethng the EM should be notअगरied about. These events currently
 * are
 * 1) UNICAST INTERFACE MACADDRESS changes
 * 2) MULTICAST INTERFACE MACADDRESS changes
 * 3) ETHERNET LINK STATUS changes
 * While allocating the send mad the remote site qpn used is 1
 * as this is the well known QP.
 *
 */
व्योम opa_vnic_vema_send_trap(काष्ठा opa_vnic_adapter *adapter,
			     काष्ठा __opa_veswport_trap *data, u32 lid)
अणु
	काष्ठा opa_vnic_ctrl_port *cport = adapter->cport;
	काष्ठा ib_mad_send_buf *send_buf;
	काष्ठा opa_vnic_vema_port *port;
	काष्ठा ib_device *ibp;
	काष्ठा opa_vnic_vema_mad_trap *trap_mad;
	काष्ठा opa_class_port_info *class;
	काष्ठा rdma_ah_attr ah_attr;
	काष्ठा ib_ah *ah;
	काष्ठा opa_veswport_trap *trap;
	u32 trap_lid;
	u16 pkey_idx;

	अगर (!cport)
		जाओ err_निकास;
	ibp = cport->ibdev;
	port = vema_get_port(cport, data->opaportnum);
	अगर (!port || !port->mad_agent)
		जाओ err_निकास;

	अगर (समय_beक्रमe(jअगरfies, adapter->trap_समयout)) अणु
		अगर (adapter->trap_count == OPA_VNIC_TRAP_BURST_LIMIT) अणु
			v_warn("Trap rate exceeded\n");
			जाओ err_निकास;
		पूर्ण अन्यथा अणु
			adapter->trap_count++;
		पूर्ण
	पूर्ण अन्यथा अणु
		adapter->trap_count = 0;
	पूर्ण

	class = &port->class_port_info;
	/* Set up address handle */
	स_रखो(&ah_attr, 0, माप(ah_attr));
	ah_attr.type = rdma_ah_find_type(ibp, port->port_num);
	rdma_ah_set_sl(&ah_attr,
		       GET_TRAP_SL_FROM_CLASS_PORT_INFO(class->trap_sl_rsvd));
	rdma_ah_set_port_num(&ah_attr, port->port_num);
	trap_lid = be32_to_cpu(class->trap_lid);
	/*
	 * check क्रम trap lid validity, must not be zero
	 * The trap sink could change after we fashion the MAD but since traps
	 * are not guaranteed we won't use a lock as anyway the change will take
	 * place even with locking.
	 */
	अगर (!trap_lid) अणु
		c_err("%s: Invalid dlid\n", __func__);
		जाओ err_निकास;
	पूर्ण

	rdma_ah_set_dlid(&ah_attr, trap_lid);
	ah = rdma_create_ah(port->mad_agent->qp->pd, &ah_attr, 0);
	अगर (IS_ERR(ah)) अणु
		c_err("%s:Couldn't create new AH = %p\n", __func__, ah);
		c_err("%s:dlid = %d, sl = %d, port = %d\n", __func__,
		      rdma_ah_get_dlid(&ah_attr), rdma_ah_get_sl(&ah_attr),
		      rdma_ah_get_port_num(&ah_attr));
		जाओ err_निकास;
	पूर्ण

	अगर (ib_find_pkey(ibp, data->opaportnum, IB_DEFAULT_PKEY_FULL,
			 &pkey_idx) < 0) अणु
		c_err("%s:full key not found, defaulting to partial\n",
		      __func__);
		अगर (ib_find_pkey(ibp, data->opaportnum, IB_DEFAULT_PKEY_PARTIAL,
				 &pkey_idx) < 0)
			pkey_idx = 1;
	पूर्ण

	send_buf = ib_create_send_mad(port->mad_agent, 1, pkey_idx, 0,
				      IB_MGMT_VENDOR_HDR, IB_MGMT_MAD_DATA,
				      GFP_ATOMIC, OPA_MGMT_BASE_VERSION);
	अगर (IS_ERR(send_buf)) अणु
		c_err("%s:Couldn't allocate send buf\n", __func__);
		जाओ err_sndbuf;
	पूर्ण

	send_buf->ah = ah;

	/* Set up common MAD hdr */
	trap_mad = send_buf->mad;
	trap_mad->mad_hdr.base_version = OPA_MGMT_BASE_VERSION;
	trap_mad->mad_hdr.mgmt_class = OPA_MGMT_CLASS_INTEL_EMA;
	trap_mad->mad_hdr.class_version = OPA_EMA_CLASS_VERSION;
	trap_mad->mad_hdr.method = IB_MGMT_METHOD_TRAP;
	port->tid++;
	trap_mad->mad_hdr.tid = cpu_to_be64(port->tid);
	trap_mad->mad_hdr.attr_id = IB_SMP_ATTR_NOTICE;

	/* Set up venकरोr OUI */
	trap_mad->oui[0] = INTEL_OUI_1;
	trap_mad->oui[1] = INTEL_OUI_2;
	trap_mad->oui[2] = INTEL_OUI_3;

	/* Setup notice attribute portion */
	trap_mad->notice.gen_type = OPA_INTEL_EMA_NOTICE_TYPE_INFO << 1;
	trap_mad->notice.oui_1 = INTEL_OUI_1;
	trap_mad->notice.oui_2 = INTEL_OUI_2;
	trap_mad->notice.oui_3 = INTEL_OUI_3;
	trap_mad->notice.issuer_lid = cpu_to_be32(lid);

	/* copy the actual trap data */
	trap = (काष्ठा opa_veswport_trap *)trap_mad->notice.raw_data;
	trap->fabric_id = cpu_to_be16(data->fabric_id);
	trap->veswid = cpu_to_be16(data->veswid);
	trap->veswportnum = cpu_to_be32(data->veswportnum);
	trap->opaportnum = cpu_to_be16(data->opaportnum);
	trap->veswportindex = data->veswportindex;
	trap->opcode = data->opcode;

	/* If successful send set up rate limit समयout अन्यथा bail */
	अगर (ib_post_send_mad(send_buf, शून्य)) अणु
		ib_मुक्त_send_mad(send_buf);
	पूर्ण अन्यथा अणु
		अगर (adapter->trap_count)
			वापस;
		adapter->trap_समयout = jअगरfies +
					usecs_to_jअगरfies(OPA_VNIC_TRAP_TIMEOUT);
		वापस;
	पूर्ण

err_sndbuf:
	rdma_destroy_ah(ah, 0);
err_निकास:
	v_err("Aborting trap\n");
पूर्ण

अटल व्योम opa_vnic_event(काष्ठा ib_event_handler *handler,
			   काष्ठा ib_event *record)
अणु
	काष्ठा opa_vnic_vema_port *port =
		container_of(handler, काष्ठा opa_vnic_vema_port, event_handler);
	काष्ठा opa_vnic_ctrl_port *cport = port->cport;
	काष्ठा opa_vnic_adapter *adapter;
	अचिन्हित दीर्घ index;

	अगर (record->element.port_num != port->port_num)
		वापस;

	c_dbg("OPA_VNIC received event %d on device %s port %d\n",
	      record->event, dev_name(&record->device->dev),
	      record->element.port_num);

	अगर (record->event != IB_EVENT_PORT_ERR &&
	    record->event != IB_EVENT_PORT_ACTIVE)
		वापस;

	xa_क्रम_each(&port->vports, index, adapter) अणु
		अगर (record->event == IB_EVENT_PORT_ACTIVE)
			netअगर_carrier_on(adapter->netdev);
		अन्यथा
			netअगर_carrier_off(adapter->netdev);
	पूर्ण
पूर्ण

/**
 * vema_unरेजिस्टर -- Unरेजिस्टरs agent
 * @cport: poपूर्णांकer to control port
 *
 * This deletes the registration by VEMA क्रम MADs
 */
अटल व्योम vema_unरेजिस्टर(काष्ठा opa_vnic_ctrl_port *cport)
अणु
	काष्ठा opa_vnic_adapter *adapter;
	अचिन्हित दीर्घ index;
	पूर्णांक i;

	क्रम (i = 1; i <= cport->num_ports; i++) अणु
		काष्ठा opa_vnic_vema_port *port = vema_get_port(cport, i);

		अगर (!port->mad_agent)
			जारी;

		/* Lock ensures no MAD is being processed */
		mutex_lock(&port->lock);
		xa_क्रम_each(&port->vports, index, adapter)
			opa_vnic_rem_netdev(adapter);
		mutex_unlock(&port->lock);

		ib_unरेजिस्टर_mad_agent(port->mad_agent);
		port->mad_agent = शून्य;
		mutex_destroy(&port->lock);
		xa_destroy(&port->vports);
		ib_unरेजिस्टर_event_handler(&port->event_handler);
	पूर्ण
पूर्ण

/**
 * vema_रेजिस्टर -- Registers agent
 * @cport: poपूर्णांकer to control port
 *
 * This function रेजिस्टरs the handlers क्रम the VEMA MADs
 *
 * Return: वापसs 0 on success. non zero otherwise
 */
अटल पूर्णांक vema_रेजिस्टर(काष्ठा opa_vnic_ctrl_port *cport)
अणु
	काष्ठा ib_mad_reg_req reg_req = अणु
		.mgmt_class = OPA_MGMT_CLASS_INTEL_EMA,
		.mgmt_class_version = OPA_MGMT_BASE_VERSION,
		.oui = अणु INTEL_OUI_1, INTEL_OUI_2, INTEL_OUI_3 पूर्ण
	पूर्ण;
	पूर्णांक i;

	set_bit(IB_MGMT_METHOD_GET, reg_req.method_mask);
	set_bit(IB_MGMT_METHOD_SET, reg_req.method_mask);

	/* रेजिस्टर ib event handler and mad agent क्रम each port on dev */
	क्रम (i = 1; i <= cport->num_ports; i++) अणु
		काष्ठा opa_vnic_vema_port *port = vema_get_port(cport, i);
		पूर्णांक ret;

		port->cport = cport;
		port->port_num = i;

		INIT_IB_EVENT_HANDLER(&port->event_handler,
				      cport->ibdev, opa_vnic_event);
		ib_रेजिस्टर_event_handler(&port->event_handler);

		xa_init(&port->vports);
		mutex_init(&port->lock);
		port->mad_agent = ib_रेजिस्टर_mad_agent(cport->ibdev, i,
							IB_QPT_GSI, &reg_req,
							IB_MGMT_RMPP_VERSION,
							vema_send, vema_recv,
							port, 0);
		अगर (IS_ERR(port->mad_agent)) अणु
			ret = PTR_ERR(port->mad_agent);
			port->mad_agent = शून्य;
			mutex_destroy(&port->lock);
			vema_unरेजिस्टर(cport);
			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/**
 * opa_vnic_ctrl_config_dev -- This function sends a trap to the EM
 * by way of ib_modअगरy_port to indicate support क्रम ethernet on the
 * fabric.
 * @cport: poपूर्णांकer to control port
 * @en: enable or disable ethernet on fabric support
 */
अटल व्योम opa_vnic_ctrl_config_dev(काष्ठा opa_vnic_ctrl_port *cport, bool en)
अणु
	काष्ठा ib_port_modअगरy pm = अणु 0 पूर्ण;
	पूर्णांक i;

	अगर (en)
		pm.set_port_cap_mask = OPA_CAP_MASK3_IsEthOnFabricSupported;
	अन्यथा
		pm.clr_port_cap_mask = OPA_CAP_MASK3_IsEthOnFabricSupported;

	क्रम (i = 1; i <= cport->num_ports; i++)
		ib_modअगरy_port(cport->ibdev, i, IB_PORT_OPA_MASK_CHG, &pm);
पूर्ण

/**
 * opa_vnic_vema_add_one -- Handle new ib device
 * @device: ib device poपूर्णांकer
 *
 * Allocate the vnic control port and initialize it.
 */
अटल पूर्णांक opa_vnic_vema_add_one(काष्ठा ib_device *device)
अणु
	काष्ठा opa_vnic_ctrl_port *cport;
	पूर्णांक rc, size = माप(*cport);

	अगर (!rdma_cap_opa_vnic(device))
		वापस -EOPNOTSUPP;

	size += device->phys_port_cnt * माप(काष्ठा opa_vnic_vema_port);
	cport = kzalloc(size, GFP_KERNEL);
	अगर (!cport)
		वापस -ENOMEM;

	cport->num_ports = device->phys_port_cnt;
	cport->ibdev = device;

	/* Initialize opa vnic management agent (vema) */
	rc = vema_रेजिस्टर(cport);
	अगर (!rc)
		c_info("VNIC client initialized\n");

	ib_set_client_data(device, &opa_vnic_client, cport);
	opa_vnic_ctrl_config_dev(cport, true);
	वापस 0;
पूर्ण

/**
 * opa_vnic_vema_rem_one -- Handle ib device removal
 * @device: ib device poपूर्णांकer
 * @client_data: ib client data
 *
 * Uninitialize and मुक्त the vnic control port.
 */
अटल व्योम opa_vnic_vema_rem_one(काष्ठा ib_device *device,
				  व्योम *client_data)
अणु
	काष्ठा opa_vnic_ctrl_port *cport = client_data;

	c_info("removing VNIC client\n");
	opa_vnic_ctrl_config_dev(cport, false);
	vema_unरेजिस्टर(cport);
	kमुक्त(cport);
पूर्ण

अटल पूर्णांक __init opa_vnic_init(व्योम)
अणु
	पूर्णांक rc;

	rc = ib_रेजिस्टर_client(&opa_vnic_client);
	अगर (rc)
		pr_err("VNIC driver register failed %d\n", rc);

	वापस rc;
पूर्ण
module_init(opa_vnic_init);

अटल व्योम opa_vnic_deinit(व्योम)
अणु
	ib_unरेजिस्टर_client(&opa_vnic_client);
पूर्ण
module_निकास(opa_vnic_deinit);

MODULE_LICENSE("Dual BSD/GPL");
MODULE_AUTHOR("Intel Corporation");
MODULE_DESCRIPTION("Intel OPA Virtual Network driver");
