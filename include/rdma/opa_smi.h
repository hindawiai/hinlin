<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR Linux-OpenIB */
/*
 * Copyright (c) 2014 Intel Corporation.  All rights reserved.
 */

#अगर_अघोषित OPA_SMI_H
#घोषणा OPA_SMI_H

#समावेश <rdma/ib_mad.h>
#समावेश <rdma/ib_smi.h>

#घोषणा OPA_SMP_LID_DATA_SIZE			2016
#घोषणा OPA_SMP_DR_DATA_SIZE			1872
#घोषणा OPA_SMP_MAX_PATH_HOPS			64

#घोषणा OPA_MAX_VLS				32
#घोषणा OPA_MAX_SLS				32
#घोषणा OPA_MAX_SCS				32

#घोषणा OPA_LID_PERMISSIVE			cpu_to_be32(0xFFFFFFFF)

काष्ठा opa_smp अणु
	u8	base_version;
	u8	mgmt_class;
	u8	class_version;
	u8	method;
	__be16	status;
	u8	hop_ptr;
	u8	hop_cnt;
	__be64	tid;
	__be16	attr_id;
	__be16	resv;
	__be32	attr_mod;
	__be64	mkey;
	जोड़ अणु
		काष्ठा अणु
			uपूर्णांक8_t data[OPA_SMP_LID_DATA_SIZE];
		पूर्ण lid;
		काष्ठा अणु
			__be32	dr_slid;
			__be32	dr_dlid;
			u8	initial_path[OPA_SMP_MAX_PATH_HOPS];
			u8	वापस_path[OPA_SMP_MAX_PATH_HOPS];
			u8	reserved[8];
			u8	data[OPA_SMP_DR_DATA_SIZE];
		पूर्ण dr;
	पूर्ण route;
पूर्ण __packed;


/* Subnet management attributes */
/* ... */
#घोषणा OPA_ATTRIB_ID_NODE_DESCRIPTION		cpu_to_be16(0x0010)
#घोषणा OPA_ATTRIB_ID_NODE_INFO			cpu_to_be16(0x0011)
#घोषणा OPA_ATTRIB_ID_PORT_INFO			cpu_to_be16(0x0015)
#घोषणा OPA_ATTRIB_ID_PARTITION_TABLE		cpu_to_be16(0x0016)
#घोषणा OPA_ATTRIB_ID_SL_TO_SC_MAP		cpu_to_be16(0x0017)
#घोषणा OPA_ATTRIB_ID_VL_ARBITRATION		cpu_to_be16(0x0018)
#घोषणा OPA_ATTRIB_ID_SM_INFO			cpu_to_be16(0x0020)
#घोषणा OPA_ATTRIB_ID_CABLE_INFO		cpu_to_be16(0x0032)
#घोषणा OPA_ATTRIB_ID_AGGREGATE			cpu_to_be16(0x0080)
#घोषणा OPA_ATTRIB_ID_SC_TO_SL_MAP		cpu_to_be16(0x0082)
#घोषणा OPA_ATTRIB_ID_SC_TO_VLR_MAP		cpu_to_be16(0x0083)
#घोषणा OPA_ATTRIB_ID_SC_TO_VLT_MAP		cpu_to_be16(0x0084)
#घोषणा OPA_ATTRIB_ID_SC_TO_VLNT_MAP		cpu_to_be16(0x0085)
/* ... */
#घोषणा OPA_ATTRIB_ID_PORT_STATE_INFO		cpu_to_be16(0x0087)
/* ... */
#घोषणा OPA_ATTRIB_ID_BUFFER_CONTROL_TABLE	cpu_to_be16(0x008A)
/* ... */

काष्ठा opa_node_description अणु
	u8 data[64];
पूर्ण __packed;

काष्ठा opa_node_info अणु
	u8      base_version;
	u8      class_version;
	u8      node_type;
	u8      num_ports;
	__be32  reserved;
	__be64  प्रणाली_image_guid;
	__be64  node_guid;
	__be64  port_guid;
	__be16  partition_cap;
	__be16  device_id;
	__be32  revision;
	u8      local_port_num;
	u8      venकरोr_id[3];   /* network byte order */
पूर्ण __packed;

#घोषणा OPA_PARTITION_TABLE_BLK_SIZE 32

अटल अंतरभूत u8
opa_get_smp_direction(काष्ठा opa_smp *smp)
अणु
	वापस ib_get_smp_direction((काष्ठा ib_smp *)smp);
पूर्ण

अटल अंतरभूत u8 *opa_get_smp_data(काष्ठा opa_smp *smp)
अणु
	अगर (smp->mgmt_class == IB_MGMT_CLASS_SUBN_सूचीECTED_ROUTE)
		वापस smp->route.dr.data;

	वापस smp->route.lid.data;
पूर्ण

अटल अंतरभूत माप_प्रकार opa_get_smp_data_size(काष्ठा opa_smp *smp)
अणु
	अगर (smp->mgmt_class == IB_MGMT_CLASS_SUBN_सूचीECTED_ROUTE)
		वापस माप(smp->route.dr.data);

	वापस माप(smp->route.lid.data);
पूर्ण

अटल अंतरभूत माप_प्रकार opa_get_smp_header_size(काष्ठा opa_smp *smp)
अणु
	अगर (smp->mgmt_class == IB_MGMT_CLASS_SUBN_सूचीECTED_ROUTE)
		वापस माप(*smp) - माप(smp->route.dr.data);

	वापस माप(*smp) - माप(smp->route.lid.data);
पूर्ण

#पूर्ण_अगर /* OPA_SMI_H */
