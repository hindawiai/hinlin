<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright(c) 2011 Intel Corporation. All rights reserved.
 *
 * Maपूर्णांकained at www.Open-FCoE.org
 */

#अगर_अघोषित _FC_MS_H_
#घोषणा	_FC_MS_H_

#समावेश <linux/types.h>

/*
 * Fibre Channel Services - Management Service (MS)
 * From T11.org FC-GS-4 Rev 7.91 February 4, 2004
 */

/*
 * Fabric Device Management Interface
 */

/*
 * Common-transport sub-type क्रम FDMI
 */
#घोषणा	FC_FDMI_SUBTYPE	    0x10 /* fs_ct_hdr.ct_fs_subtype */

/*
 * Management server FDMI Requests.
 */
क्रमागत fc_fdmi_req अणु
	FC_FDMI_GRHL = 0x0100,	/* Get Registered HBA List */
	FC_FDMI_GHAT = 0x0101,	/* Get HBA Attributes */
	FC_FDMI_GRPL = 0x0102,	/* Get Registered Port List */
	FC_FDMI_GPAT = 0x0110,	/* Get Port Attributes */
	FC_FDMI_RHBA = 0x0200,	/* Register HBA */
	FC_FDMI_RHAT = 0x0201,	/* Register HBA Attributes */
	FC_FDMI_RPRT = 0x0210,	/* Register Port */
	FC_FDMI_RPA = 0x0211,	/* Register Port Attributes */
	FC_FDMI_DHBA = 0x0300,	/* Deरेजिस्टर HBA */
	FC_FDMI_DHAT = 0x0301,	/* Deरेजिस्टर HBA Attributes */
	FC_FDMI_DPRT = 0x0310,	/* Deरेजिस्टर Port */
	FC_FDMI_DPA = 0x0311,	/* Deरेजिस्टर Port Attributes */
पूर्ण;

/*
 * HBA Attribute Entry Type
 */
क्रमागत fc_fdmi_hba_attr_type अणु
	FC_FDMI_HBA_ATTR_NODENAME = 0x0001,
	FC_FDMI_HBA_ATTR_MANUFACTURER = 0x0002,
	FC_FDMI_HBA_ATTR_SERIALNUMBER = 0x0003,
	FC_FDMI_HBA_ATTR_MODEL = 0x0004,
	FC_FDMI_HBA_ATTR_MODELDESCRIPTION = 0x0005,
	FC_FDMI_HBA_ATTR_HARDWAREVERSION = 0x0006,
	FC_FDMI_HBA_ATTR_DRIVERVERSION = 0x0007,
	FC_FDMI_HBA_ATTR_OPTIONROMVERSION = 0x0008,
	FC_FDMI_HBA_ATTR_FIRMWAREVERSION = 0x0009,
	FC_FDMI_HBA_ATTR_OSNAMEVERSION = 0x000A,
	FC_FDMI_HBA_ATTR_MAXCTPAYLOAD = 0x000B,
पूर्ण;

/*
 * HBA Attribute Length
 */
#घोषणा FC_FDMI_HBA_ATTR_NODENAME_LEN		8
#घोषणा FC_FDMI_HBA_ATTR_MANUFACTURER_LEN	80
#घोषणा FC_FDMI_HBA_ATTR_SERIALNUMBER_LEN	80
#घोषणा FC_FDMI_HBA_ATTR_MODEL_LEN		256
#घोषणा FC_FDMI_HBA_ATTR_MODELDESCR_LEN		256
#घोषणा FC_FDMI_HBA_ATTR_HARDWAREVERSION_LEN	256
#घोषणा FC_FDMI_HBA_ATTR_DRIVERVERSION_LEN	256
#घोषणा FC_FDMI_HBA_ATTR_OPTIONROMVERSION_LEN	256
#घोषणा FC_FDMI_HBA_ATTR_FIRMWAREVERSION_LEN	256
#घोषणा FC_FDMI_HBA_ATTR_OSNAMEVERSION_LEN	256
#घोषणा FC_FDMI_HBA_ATTR_MAXCTPAYLOAD_LEN	4

/*
 * Port Attribute Type
 */
क्रमागत fc_fdmi_port_attr_type अणु
	FC_FDMI_PORT_ATTR_FC4TYPES = 0x0001,
	FC_FDMI_PORT_ATTR_SUPPORTEDSPEED = 0x0002,
	FC_FDMI_PORT_ATTR_CURRENTPORTSPEED = 0x0003,
	FC_FDMI_PORT_ATTR_MAXFRAMESIZE = 0x0004,
	FC_FDMI_PORT_ATTR_OSDEVICENAME = 0x0005,
	FC_FDMI_PORT_ATTR_HOSTNAME = 0x0006,
पूर्ण;

/*
 * Port Attribute Length
 */
#घोषणा FC_FDMI_PORT_ATTR_FC4TYPES_LEN		32
#घोषणा FC_FDMI_PORT_ATTR_SUPPORTEDSPEED_LEN	4
#घोषणा FC_FDMI_PORT_ATTR_CURRENTPORTSPEED_LEN	4
#घोषणा FC_FDMI_PORT_ATTR_MAXFRAMESIZE_LEN	4
#घोषणा FC_FDMI_PORT_ATTR_OSDEVICENAME_LEN	256
#घोषणा FC_FDMI_PORT_ATTR_HOSTNAME_LEN		256

/*
 * HBA Attribute ID
 */
काष्ठा fc_fdmi_hba_identअगरier अणु
	__be64		id;
पूर्ण;

/*
 * Port Name
 */
काष्ठा fc_fdmi_port_name अणु
	__be64		portname;
पूर्ण;

/*
 * Attribute Entry Block क्रम HBA/Port Attributes
 */
#घोषणा FC_FDMI_ATTR_ENTRY_HEADER_LEN	4
काष्ठा fc_fdmi_attr_entry अणु
	__be16		type;
	__be16		len;
	__u8		value[1];
पूर्ण __attribute__((__packed__));

/*
 * Common क्रम HBA/Port Attributes
 */
काष्ठा fs_fdmi_attrs अणु
	__be32				numattrs;
	काष्ठा fc_fdmi_attr_entry	attr[1];
पूर्ण __attribute__((__packed__));

/*
 * Registered Port List
 */
काष्ठा fc_fdmi_rpl अणु
	__be32				numport;
	काष्ठा fc_fdmi_port_name	port[1];
पूर्ण __attribute__((__packed__));

/*
 * Register HBA (RHBA)
 */
काष्ठा fc_fdmi_rhba अणु
	काष्ठा fc_fdmi_hba_identअगरier hbaid;
	काष्ठा fc_fdmi_rpl		 port;
	काष्ठा fs_fdmi_attrs		 hba_attrs;
पूर्ण __attribute__((__packed__));

/*
 * Register HBA Attributes (RHAT)
 */
काष्ठा fc_fdmi_rhat अणु
	काष्ठा fc_fdmi_hba_identअगरier hbaid;
	काष्ठा fs_fdmi_attrs		 hba_attrs;
पूर्ण __attribute__((__packed__));

/*
 * Register Port (RPRT)
 */
काष्ठा fc_fdmi_rprt अणु
	काष्ठा fc_fdmi_hba_identअगरier hbaid;
	काष्ठा fc_fdmi_port_name	 port;
	काष्ठा fs_fdmi_attrs		 hba_attrs;
पूर्ण __attribute__((__packed__));

/*
 * Register Port Attributes (RPA)
 */
काष्ठा fc_fdmi_rpa अणु
	काष्ठा fc_fdmi_port_name	 port;
	काष्ठा fs_fdmi_attrs		 hba_attrs;
पूर्ण __attribute__((__packed__));

/*
 * Deरेजिस्टर Port (DPRT)
 */
काष्ठा fc_fdmi_dprt अणु
	काष्ठा fc_fdmi_port_name	 port;
पूर्ण __attribute__((__packed__));

/*
 * Deरेजिस्टर Port Attributes (DPA)
 */
काष्ठा fc_fdmi_dpa अणु
	काष्ठा fc_fdmi_port_name	 port;
	काष्ठा fs_fdmi_attrs		 hba_attrs;
पूर्ण __attribute__((__packed__));

/*
 * Deरेजिस्टर HBA Attributes (DHAT)
 */
काष्ठा fc_fdmi_dhat अणु
	काष्ठा fc_fdmi_hba_identअगरier hbaid;
पूर्ण __attribute__((__packed__));

/*
 * Deरेजिस्टर HBA (DHBA)
 */
काष्ठा fc_fdmi_dhba अणु
	काष्ठा fc_fdmi_hba_identअगरier hbaid;
पूर्ण __attribute__((__packed__));

#पूर्ण_अगर /* _FC_MS_H_ */
