<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _SCSI_SAS_INTERNAL_H
#घोषणा _SCSI_SAS_INTERNAL_H

#घोषणा SAS_HOST_ATTRS		0
#घोषणा SAS_PHY_ATTRS		17
#घोषणा SAS_PORT_ATTRS		1
#घोषणा SAS_RPORT_ATTRS		8
#घोषणा SAS_END_DEV_ATTRS	5
#घोषणा SAS_EXPANDER_ATTRS	7

काष्ठा sas_पूर्णांकernal अणु
	काष्ठा scsi_transport_ढाँचा t;
	काष्ठा sas_function_ढाँचा *f;
	काष्ठा sas_करोमुख्य_function_ढाँचा *dft;

	काष्ठा device_attribute निजी_host_attrs[SAS_HOST_ATTRS];
	काष्ठा device_attribute निजी_phy_attrs[SAS_PHY_ATTRS];
	काष्ठा device_attribute निजी_port_attrs[SAS_PORT_ATTRS];
	काष्ठा device_attribute निजी_rphy_attrs[SAS_RPORT_ATTRS];
	काष्ठा device_attribute निजी_end_dev_attrs[SAS_END_DEV_ATTRS];
	काष्ठा device_attribute निजी_expander_attrs[SAS_EXPANDER_ATTRS];

	काष्ठा transport_container phy_attr_cont;
	काष्ठा transport_container port_attr_cont;
	काष्ठा transport_container rphy_attr_cont;
	काष्ठा transport_container end_dev_attr_cont;
	काष्ठा transport_container expander_attr_cont;

	/*
	 * The array of null terminated poपूर्णांकers to attributes
	 * needed by scsi_sysfs.c
	 */
	काष्ठा device_attribute *host_attrs[SAS_HOST_ATTRS + 1];
	काष्ठा device_attribute *phy_attrs[SAS_PHY_ATTRS + 1];
	काष्ठा device_attribute *port_attrs[SAS_PORT_ATTRS + 1];
	काष्ठा device_attribute *rphy_attrs[SAS_RPORT_ATTRS + 1];
	काष्ठा device_attribute *end_dev_attrs[SAS_END_DEV_ATTRS + 1];
	काष्ठा device_attribute *expander_attrs[SAS_EXPANDER_ATTRS + 1];
पूर्ण;
#घोषणा to_sas_पूर्णांकernal(पंचांगpl)	container_of(पंचांगpl, काष्ठा sas_पूर्णांकernal, t)

#पूर्ण_अगर
