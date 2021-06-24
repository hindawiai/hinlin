<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Export the iSCSI boot info to userland via sysfs.
 *
 * Copyright (C) 2010 Red Hat, Inc.  All rights reserved.
 * Copyright (C) 2010 Mike Christie
 */
#अगर_अघोषित _ISCSI_BOOT_SYSFS_
#घोषणा _ISCSI_BOOT_SYSFS_

/*
 * The text attributes names क्रम each of the kobjects.
*/
क्रमागत iscsi_boot_eth_properties_क्रमागत अणु
	ISCSI_BOOT_ETH_INDEX,
	ISCSI_BOOT_ETH_FLAGS,
	ISCSI_BOOT_ETH_IP_ADDR,
	ISCSI_BOOT_ETH_PREFIX_LEN,
	ISCSI_BOOT_ETH_SUBNET_MASK,
	ISCSI_BOOT_ETH_ORIGIN,
	ISCSI_BOOT_ETH_GATEWAY,
	ISCSI_BOOT_ETH_PRIMARY_DNS,
	ISCSI_BOOT_ETH_SECONDARY_DNS,
	ISCSI_BOOT_ETH_DHCP,
	ISCSI_BOOT_ETH_VLAN,
	ISCSI_BOOT_ETH_MAC,
	/* eth_pci_bdf - this is replaced by link to the device itself. */
	ISCSI_BOOT_ETH_HOSTNAME,
	ISCSI_BOOT_ETH_END_MARKER,
पूर्ण;

क्रमागत iscsi_boot_tgt_properties_क्रमागत अणु
	ISCSI_BOOT_TGT_INDEX,
	ISCSI_BOOT_TGT_FLAGS,
	ISCSI_BOOT_TGT_IP_ADDR,
	ISCSI_BOOT_TGT_PORT,
	ISCSI_BOOT_TGT_LUN,
	ISCSI_BOOT_TGT_CHAP_TYPE,
	ISCSI_BOOT_TGT_NIC_ASSOC,
	ISCSI_BOOT_TGT_NAME,
	ISCSI_BOOT_TGT_CHAP_NAME,
	ISCSI_BOOT_TGT_CHAP_SECRET,
	ISCSI_BOOT_TGT_REV_CHAP_NAME,
	ISCSI_BOOT_TGT_REV_CHAP_SECRET,
	ISCSI_BOOT_TGT_END_MARKER,
पूर्ण;

क्रमागत iscsi_boot_initiator_properties_क्रमागत अणु
	ISCSI_BOOT_INI_INDEX,
	ISCSI_BOOT_INI_FLAGS,
	ISCSI_BOOT_INI_ISNS_SERVER,
	ISCSI_BOOT_INI_SLP_SERVER,
	ISCSI_BOOT_INI_PRI_RADIUS_SERVER,
	ISCSI_BOOT_INI_SEC_RADIUS_SERVER,
	ISCSI_BOOT_INI_INITIATOR_NAME,
	ISCSI_BOOT_INI_END_MARKER,
पूर्ण;

क्रमागत iscsi_boot_acpitbl_properties_क्रमागत अणु
	ISCSI_BOOT_ACPITBL_SIGNATURE,
	ISCSI_BOOT_ACPITBL_OEM_ID,
	ISCSI_BOOT_ACPITBL_OEM_TABLE_ID,
पूर्ण;

काष्ठा attribute_group;

काष्ठा iscsi_boot_kobj अणु
	काष्ठा kobject kobj;
	काष्ठा attribute_group *attr_group;
	काष्ठा list_head list;

	/*
	 * Poपूर्णांकer to store driver specअगरic info. If set this will
	 * be मुक्तd क्रम the LLD when the kobj release function is called.
	 */
	व्योम *data;
	/*
	 * Driver specअगरic show function.
	 *
	 * The क्रमागत of the type. This can be any value of the above
	 * properties.
	 */
	sमाप_प्रकार (*show) (व्योम *data, पूर्णांक type, अक्षर *buf);

	/*
	 * Drivers specअगरic visibility function.
	 * The function should वापस अगर they the attr should be पढ़ोable
	 * writable or should not be shown.
	 *
	 * The क्रमागत of the type. This can be any value of the above
	 * properties.
	 */
	umode_t (*is_visible) (व्योम *data, पूर्णांक type);

	/*
	 * Driver specअगरic release function.
	 *
	 * The function should मुक्त the data passed in.
	 */
	व्योम (*release) (व्योम *data);
पूर्ण;

काष्ठा iscsi_boot_kset अणु
	काष्ठा list_head kobj_list;
	काष्ठा kset *kset;
पूर्ण;

काष्ठा iscsi_boot_kobj *
iscsi_boot_create_initiator(काष्ठा iscsi_boot_kset *boot_kset, पूर्णांक index,
			    व्योम *data,
			    sमाप_प्रकार (*show) (व्योम *data, पूर्णांक type, अक्षर *buf),
			    umode_t (*is_visible) (व्योम *data, पूर्णांक type),
			    व्योम (*release) (व्योम *data));

काष्ठा iscsi_boot_kobj *
iscsi_boot_create_ethernet(काष्ठा iscsi_boot_kset *boot_kset, पूर्णांक index,
			   व्योम *data,
			   sमाप_प्रकार (*show) (व्योम *data, पूर्णांक type, अक्षर *buf),
			   umode_t (*is_visible) (व्योम *data, पूर्णांक type),
			   व्योम (*release) (व्योम *data));
काष्ठा iscsi_boot_kobj *
iscsi_boot_create_target(काष्ठा iscsi_boot_kset *boot_kset, पूर्णांक index,
			 व्योम *data,
			 sमाप_प्रकार (*show) (व्योम *data, पूर्णांक type, अक्षर *buf),
			 umode_t (*is_visible) (व्योम *data, पूर्णांक type),
			 व्योम (*release) (व्योम *data));

काष्ठा iscsi_boot_kobj *
iscsi_boot_create_acpitbl(काष्ठा iscsi_boot_kset *boot_kset, पूर्णांक index,
			  व्योम *data,
			  sमाप_प्रकार (*show)(व्योम *data, पूर्णांक type, अक्षर *buf),
			  umode_t (*is_visible)(व्योम *data, पूर्णांक type),
			  व्योम (*release)(व्योम *data));

काष्ठा iscsi_boot_kset *iscsi_boot_create_kset(स्थिर अक्षर *set_name);
काष्ठा iscsi_boot_kset *iscsi_boot_create_host_kset(अचिन्हित पूर्णांक hostno);
व्योम iscsi_boot_destroy_kset(काष्ठा iscsi_boot_kset *boot_kset);

#पूर्ण_अगर
