<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Export the iSCSI boot info to userland via sysfs.
 *
 * Copyright (C) 2010 Red Hat, Inc.  All rights reserved.
 * Copyright (C) 2010 Mike Christie
 */

#समावेश <linux/module.h>
#समावेश <linux/माला.स>
#समावेश <linux/slab.h>
#समावेश <linux/sysfs.h>
#समावेश <linux/capability.h>
#समावेश <linux/iscsi_boot_sysfs.h>


MODULE_AUTHOR("Mike Christie <michaelc@cs.wisc.edu>");
MODULE_DESCRIPTION("sysfs interface and helpers to export iSCSI boot information");
MODULE_LICENSE("GPL");
/*
 * The kobject and attribute काष्ठाures.
 */
काष्ठा iscsi_boot_attr अणु
	काष्ठा attribute attr;
	पूर्णांक type;
	sमाप_प्रकार (*show) (व्योम *data, पूर्णांक type, अक्षर *buf);
पूर्ण;

/*
 * The routine called क्रम all sysfs attributes.
 */
अटल sमाप_प्रकार iscsi_boot_show_attribute(काष्ठा kobject *kobj,
					 काष्ठा attribute *attr, अक्षर *buf)
अणु
	काष्ठा iscsi_boot_kobj *boot_kobj =
			container_of(kobj, काष्ठा iscsi_boot_kobj, kobj);
	काष्ठा iscsi_boot_attr *boot_attr =
			container_of(attr, काष्ठा iscsi_boot_attr, attr);
	sमाप_प्रकार ret = -EIO;
	अक्षर *str = buf;

	अगर (!capable(CAP_SYS_ADMIN))
		वापस -EACCES;

	अगर (boot_kobj->show)
		ret = boot_kobj->show(boot_kobj->data, boot_attr->type, str);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा sysfs_ops iscsi_boot_attr_ops = अणु
	.show = iscsi_boot_show_attribute,
पूर्ण;

अटल व्योम iscsi_boot_kobj_release(काष्ठा kobject *kobj)
अणु
	काष्ठा iscsi_boot_kobj *boot_kobj =
			container_of(kobj, काष्ठा iscsi_boot_kobj, kobj);

	अगर (boot_kobj->release)
		boot_kobj->release(boot_kobj->data);
	kमुक्त(boot_kobj);
पूर्ण

अटल काष्ठा kobj_type iscsi_boot_ktype = अणु
	.release = iscsi_boot_kobj_release,
	.sysfs_ops = &iscsi_boot_attr_ops,
पूर्ण;

#घोषणा iscsi_boot_rd_attr(fnname, sysfs_name, attr_type)		\
अटल काष्ठा iscsi_boot_attr iscsi_boot_attr_##fnname = अणु	\
	.attr	= अणु .name = __stringअगरy(sysfs_name), .mode = 0444 पूर्ण,	\
	.type	= attr_type,						\
पूर्ण

/* Target attrs */
iscsi_boot_rd_attr(tgt_index, index, ISCSI_BOOT_TGT_INDEX);
iscsi_boot_rd_attr(tgt_flags, flags, ISCSI_BOOT_TGT_FLAGS);
iscsi_boot_rd_attr(tgt_ip, ip-addr, ISCSI_BOOT_TGT_IP_ADDR);
iscsi_boot_rd_attr(tgt_port, port, ISCSI_BOOT_TGT_PORT);
iscsi_boot_rd_attr(tgt_lun, lun, ISCSI_BOOT_TGT_LUN);
iscsi_boot_rd_attr(tgt_chap, chap-type, ISCSI_BOOT_TGT_CHAP_TYPE);
iscsi_boot_rd_attr(tgt_nic, nic-assoc, ISCSI_BOOT_TGT_NIC_ASSOC);
iscsi_boot_rd_attr(tgt_name, target-name, ISCSI_BOOT_TGT_NAME);
iscsi_boot_rd_attr(tgt_chap_name, chap-name, ISCSI_BOOT_TGT_CHAP_NAME);
iscsi_boot_rd_attr(tgt_chap_secret, chap-secret, ISCSI_BOOT_TGT_CHAP_SECRET);
iscsi_boot_rd_attr(tgt_chap_rev_name, rev-chap-name,
		   ISCSI_BOOT_TGT_REV_CHAP_NAME);
iscsi_boot_rd_attr(tgt_chap_rev_secret, rev-chap-name-secret,
		   ISCSI_BOOT_TGT_REV_CHAP_SECRET);

अटल काष्ठा attribute *target_attrs[] = अणु
	&iscsi_boot_attr_tgt_index.attr,
	&iscsi_boot_attr_tgt_flags.attr,
	&iscsi_boot_attr_tgt_ip.attr,
	&iscsi_boot_attr_tgt_port.attr,
	&iscsi_boot_attr_tgt_lun.attr,
	&iscsi_boot_attr_tgt_chap.attr,
	&iscsi_boot_attr_tgt_nic.attr,
	&iscsi_boot_attr_tgt_name.attr,
	&iscsi_boot_attr_tgt_chap_name.attr,
	&iscsi_boot_attr_tgt_chap_secret.attr,
	&iscsi_boot_attr_tgt_chap_rev_name.attr,
	&iscsi_boot_attr_tgt_chap_rev_secret.attr,
	शून्य
पूर्ण;

अटल umode_t iscsi_boot_tgt_attr_is_visible(काष्ठा kobject *kobj,
					     काष्ठा attribute *attr, पूर्णांक i)
अणु
	काष्ठा iscsi_boot_kobj *boot_kobj =
			container_of(kobj, काष्ठा iscsi_boot_kobj, kobj);

	अगर (attr ==  &iscsi_boot_attr_tgt_index.attr)
		वापस boot_kobj->is_visible(boot_kobj->data,
					     ISCSI_BOOT_TGT_INDEX);
	अन्यथा अगर (attr == &iscsi_boot_attr_tgt_flags.attr)
		वापस boot_kobj->is_visible(boot_kobj->data,
					     ISCSI_BOOT_TGT_FLAGS);
	अन्यथा अगर (attr == &iscsi_boot_attr_tgt_ip.attr)
		वापस boot_kobj->is_visible(boot_kobj->data,
					      ISCSI_BOOT_TGT_IP_ADDR);
	अन्यथा अगर (attr == &iscsi_boot_attr_tgt_port.attr)
		वापस boot_kobj->is_visible(boot_kobj->data,
					      ISCSI_BOOT_TGT_PORT);
	अन्यथा अगर (attr == &iscsi_boot_attr_tgt_lun.attr)
		वापस boot_kobj->is_visible(boot_kobj->data,
					      ISCSI_BOOT_TGT_LUN);
	अन्यथा अगर (attr == &iscsi_boot_attr_tgt_chap.attr)
		वापस boot_kobj->is_visible(boot_kobj->data,
					     ISCSI_BOOT_TGT_CHAP_TYPE);
	अन्यथा अगर (attr == &iscsi_boot_attr_tgt_nic.attr)
		वापस boot_kobj->is_visible(boot_kobj->data,
					     ISCSI_BOOT_TGT_NIC_ASSOC);
	अन्यथा अगर (attr == &iscsi_boot_attr_tgt_name.attr)
		वापस boot_kobj->is_visible(boot_kobj->data,
					     ISCSI_BOOT_TGT_NAME);
	अन्यथा अगर (attr == &iscsi_boot_attr_tgt_chap_name.attr)
		वापस boot_kobj->is_visible(boot_kobj->data,
					     ISCSI_BOOT_TGT_CHAP_NAME);
	अन्यथा अगर (attr == &iscsi_boot_attr_tgt_chap_secret.attr)
		वापस boot_kobj->is_visible(boot_kobj->data,
					     ISCSI_BOOT_TGT_CHAP_SECRET);
	अन्यथा अगर (attr == &iscsi_boot_attr_tgt_chap_rev_name.attr)
		वापस boot_kobj->is_visible(boot_kobj->data,
					     ISCSI_BOOT_TGT_REV_CHAP_NAME);
	अन्यथा अगर (attr == &iscsi_boot_attr_tgt_chap_rev_secret.attr)
		वापस boot_kobj->is_visible(boot_kobj->data,
					     ISCSI_BOOT_TGT_REV_CHAP_SECRET);
	वापस 0;
पूर्ण

अटल काष्ठा attribute_group iscsi_boot_target_attr_group = अणु
	.attrs = target_attrs,
	.is_visible = iscsi_boot_tgt_attr_is_visible,
पूर्ण;

/* Ethernet attrs */
iscsi_boot_rd_attr(eth_index, index, ISCSI_BOOT_ETH_INDEX);
iscsi_boot_rd_attr(eth_flags, flags, ISCSI_BOOT_ETH_FLAGS);
iscsi_boot_rd_attr(eth_ip, ip-addr, ISCSI_BOOT_ETH_IP_ADDR);
iscsi_boot_rd_attr(eth_prefix, prefix-len, ISCSI_BOOT_ETH_PREFIX_LEN);
iscsi_boot_rd_attr(eth_subnet, subnet-mask, ISCSI_BOOT_ETH_SUBNET_MASK);
iscsi_boot_rd_attr(eth_origin, origin, ISCSI_BOOT_ETH_ORIGIN);
iscsi_boot_rd_attr(eth_gateway, gateway, ISCSI_BOOT_ETH_GATEWAY);
iscsi_boot_rd_attr(eth_primary_dns, primary-dns, ISCSI_BOOT_ETH_PRIMARY_DNS);
iscsi_boot_rd_attr(eth_secondary_dns, secondary-dns,
		   ISCSI_BOOT_ETH_SECONDARY_DNS);
iscsi_boot_rd_attr(eth_dhcp, dhcp, ISCSI_BOOT_ETH_DHCP);
iscsi_boot_rd_attr(eth_vlan, vlan, ISCSI_BOOT_ETH_VLAN);
iscsi_boot_rd_attr(eth_mac, mac, ISCSI_BOOT_ETH_MAC);
iscsi_boot_rd_attr(eth_hostname, hostname, ISCSI_BOOT_ETH_HOSTNAME);

अटल काष्ठा attribute *ethernet_attrs[] = अणु
	&iscsi_boot_attr_eth_index.attr,
	&iscsi_boot_attr_eth_flags.attr,
	&iscsi_boot_attr_eth_ip.attr,
	&iscsi_boot_attr_eth_prefix.attr,
	&iscsi_boot_attr_eth_subnet.attr,
	&iscsi_boot_attr_eth_origin.attr,
	&iscsi_boot_attr_eth_gateway.attr,
	&iscsi_boot_attr_eth_primary_dns.attr,
	&iscsi_boot_attr_eth_secondary_dns.attr,
	&iscsi_boot_attr_eth_dhcp.attr,
	&iscsi_boot_attr_eth_vlan.attr,
	&iscsi_boot_attr_eth_mac.attr,
	&iscsi_boot_attr_eth_hostname.attr,
	शून्य
पूर्ण;

अटल umode_t iscsi_boot_eth_attr_is_visible(काष्ठा kobject *kobj,
					     काष्ठा attribute *attr, पूर्णांक i)
अणु
	काष्ठा iscsi_boot_kobj *boot_kobj =
			container_of(kobj, काष्ठा iscsi_boot_kobj, kobj);

	अगर (attr ==  &iscsi_boot_attr_eth_index.attr)
		वापस boot_kobj->is_visible(boot_kobj->data,
					     ISCSI_BOOT_ETH_INDEX);
	अन्यथा अगर (attr ==  &iscsi_boot_attr_eth_flags.attr)
		वापस boot_kobj->is_visible(boot_kobj->data,
					     ISCSI_BOOT_ETH_FLAGS);
	अन्यथा अगर (attr ==  &iscsi_boot_attr_eth_ip.attr)
		वापस boot_kobj->is_visible(boot_kobj->data,
					     ISCSI_BOOT_ETH_IP_ADDR);
	अन्यथा अगर (attr ==  &iscsi_boot_attr_eth_prefix.attr)
		वापस boot_kobj->is_visible(boot_kobj->data,
					     ISCSI_BOOT_ETH_PREFIX_LEN);
	अन्यथा अगर (attr ==  &iscsi_boot_attr_eth_subnet.attr)
		वापस boot_kobj->is_visible(boot_kobj->data,
					     ISCSI_BOOT_ETH_SUBNET_MASK);
	अन्यथा अगर (attr ==  &iscsi_boot_attr_eth_origin.attr)
		वापस boot_kobj->is_visible(boot_kobj->data,
					     ISCSI_BOOT_ETH_ORIGIN);
	अन्यथा अगर (attr ==  &iscsi_boot_attr_eth_gateway.attr)
		वापस boot_kobj->is_visible(boot_kobj->data,
					     ISCSI_BOOT_ETH_GATEWAY);
	अन्यथा अगर (attr ==  &iscsi_boot_attr_eth_primary_dns.attr)
		वापस boot_kobj->is_visible(boot_kobj->data,
					     ISCSI_BOOT_ETH_PRIMARY_DNS);
	अन्यथा अगर (attr ==  &iscsi_boot_attr_eth_secondary_dns.attr)
		वापस boot_kobj->is_visible(boot_kobj->data,
					     ISCSI_BOOT_ETH_SECONDARY_DNS);
	अन्यथा अगर (attr ==  &iscsi_boot_attr_eth_dhcp.attr)
		वापस boot_kobj->is_visible(boot_kobj->data,
					     ISCSI_BOOT_ETH_DHCP);
	अन्यथा अगर (attr ==  &iscsi_boot_attr_eth_vlan.attr)
		वापस boot_kobj->is_visible(boot_kobj->data,
					     ISCSI_BOOT_ETH_VLAN);
	अन्यथा अगर (attr ==  &iscsi_boot_attr_eth_mac.attr)
		वापस boot_kobj->is_visible(boot_kobj->data,
					     ISCSI_BOOT_ETH_MAC);
	अन्यथा अगर (attr ==  &iscsi_boot_attr_eth_hostname.attr)
		वापस boot_kobj->is_visible(boot_kobj->data,
					     ISCSI_BOOT_ETH_HOSTNAME);
	वापस 0;
पूर्ण

अटल काष्ठा attribute_group iscsi_boot_ethernet_attr_group = अणु
	.attrs = ethernet_attrs,
	.is_visible = iscsi_boot_eth_attr_is_visible,
पूर्ण;

/* Initiator attrs */
iscsi_boot_rd_attr(ini_index, index, ISCSI_BOOT_INI_INDEX);
iscsi_boot_rd_attr(ini_flags, flags, ISCSI_BOOT_INI_FLAGS);
iscsi_boot_rd_attr(ini_isns, isns-server, ISCSI_BOOT_INI_ISNS_SERVER);
iscsi_boot_rd_attr(ini_slp, slp-server, ISCSI_BOOT_INI_SLP_SERVER);
iscsi_boot_rd_attr(ini_primary_radius, pri-radius-server,
		   ISCSI_BOOT_INI_PRI_RADIUS_SERVER);
iscsi_boot_rd_attr(ini_secondary_radius, sec-radius-server,
		   ISCSI_BOOT_INI_SEC_RADIUS_SERVER);
iscsi_boot_rd_attr(ini_name, initiator-name, ISCSI_BOOT_INI_INITIATOR_NAME);

अटल काष्ठा attribute *initiator_attrs[] = अणु
	&iscsi_boot_attr_ini_index.attr,
	&iscsi_boot_attr_ini_flags.attr,
	&iscsi_boot_attr_ini_isns.attr,
	&iscsi_boot_attr_ini_slp.attr,
	&iscsi_boot_attr_ini_primary_radius.attr,
	&iscsi_boot_attr_ini_secondary_radius.attr,
	&iscsi_boot_attr_ini_name.attr,
	शून्य
पूर्ण;

अटल umode_t iscsi_boot_ini_attr_is_visible(काष्ठा kobject *kobj,
					     काष्ठा attribute *attr, पूर्णांक i)
अणु
	काष्ठा iscsi_boot_kobj *boot_kobj =
			container_of(kobj, काष्ठा iscsi_boot_kobj, kobj);

	अगर (attr ==  &iscsi_boot_attr_ini_index.attr)
		वापस boot_kobj->is_visible(boot_kobj->data,
					     ISCSI_BOOT_INI_INDEX);
	अगर (attr ==  &iscsi_boot_attr_ini_flags.attr)
		वापस boot_kobj->is_visible(boot_kobj->data,
					     ISCSI_BOOT_INI_FLAGS);
	अगर (attr ==  &iscsi_boot_attr_ini_isns.attr)
		वापस boot_kobj->is_visible(boot_kobj->data,
					     ISCSI_BOOT_INI_ISNS_SERVER);
	अगर (attr ==  &iscsi_boot_attr_ini_slp.attr)
		वापस boot_kobj->is_visible(boot_kobj->data,
					     ISCSI_BOOT_INI_SLP_SERVER);
	अगर (attr ==  &iscsi_boot_attr_ini_primary_radius.attr)
		वापस boot_kobj->is_visible(boot_kobj->data,
					     ISCSI_BOOT_INI_PRI_RADIUS_SERVER);
	अगर (attr ==  &iscsi_boot_attr_ini_secondary_radius.attr)
		वापस boot_kobj->is_visible(boot_kobj->data,
					     ISCSI_BOOT_INI_SEC_RADIUS_SERVER);
	अगर (attr ==  &iscsi_boot_attr_ini_name.attr)
		वापस boot_kobj->is_visible(boot_kobj->data,
					     ISCSI_BOOT_INI_INITIATOR_NAME);

	वापस 0;
पूर्ण

अटल काष्ठा attribute_group iscsi_boot_initiator_attr_group = अणु
	.attrs = initiator_attrs,
	.is_visible = iscsi_boot_ini_attr_is_visible,
पूर्ण;

/* iBFT ACPI Table attributes */
iscsi_boot_rd_attr(acpitbl_signature, signature, ISCSI_BOOT_ACPITBL_SIGNATURE);
iscsi_boot_rd_attr(acpitbl_oem_id, oem_id, ISCSI_BOOT_ACPITBL_OEM_ID);
iscsi_boot_rd_attr(acpitbl_oem_table_id, oem_table_id,
		   ISCSI_BOOT_ACPITBL_OEM_TABLE_ID);

अटल काष्ठा attribute *acpitbl_attrs[] = अणु
	&iscsi_boot_attr_acpitbl_signature.attr,
	&iscsi_boot_attr_acpitbl_oem_id.attr,
	&iscsi_boot_attr_acpitbl_oem_table_id.attr,
	शून्य
पूर्ण;

अटल umode_t iscsi_boot_acpitbl_attr_is_visible(काष्ठा kobject *kobj,
					     काष्ठा attribute *attr, पूर्णांक i)
अणु
	काष्ठा iscsi_boot_kobj *boot_kobj =
			container_of(kobj, काष्ठा iscsi_boot_kobj, kobj);

	अगर (attr ==  &iscsi_boot_attr_acpitbl_signature.attr)
		वापस boot_kobj->is_visible(boot_kobj->data,
					     ISCSI_BOOT_ACPITBL_SIGNATURE);
	अगर (attr ==  &iscsi_boot_attr_acpitbl_oem_id.attr)
		वापस boot_kobj->is_visible(boot_kobj->data,
					     ISCSI_BOOT_ACPITBL_OEM_ID);
	अगर (attr ==  &iscsi_boot_attr_acpitbl_oem_table_id.attr)
		वापस boot_kobj->is_visible(boot_kobj->data,
					     ISCSI_BOOT_ACPITBL_OEM_TABLE_ID);
	वापस 0;
पूर्ण

अटल काष्ठा attribute_group iscsi_boot_acpitbl_attr_group = अणु
	.attrs = acpitbl_attrs,
	.is_visible = iscsi_boot_acpitbl_attr_is_visible,
पूर्ण;

अटल काष्ठा iscsi_boot_kobj *
iscsi_boot_create_kobj(काष्ठा iscsi_boot_kset *boot_kset,
		       काष्ठा attribute_group *attr_group,
		       स्थिर अक्षर *name, पूर्णांक index, व्योम *data,
		       sमाप_प्रकार (*show) (व्योम *data, पूर्णांक type, अक्षर *buf),
		       umode_t (*is_visible) (व्योम *data, पूर्णांक type),
		       व्योम (*release) (व्योम *data))
अणु
	काष्ठा iscsi_boot_kobj *boot_kobj;

	boot_kobj = kzalloc(माप(*boot_kobj), GFP_KERNEL);
	अगर (!boot_kobj)
		वापस शून्य;
	INIT_LIST_HEAD(&boot_kobj->list);

	boot_kobj->kobj.kset = boot_kset->kset;
	अगर (kobject_init_and_add(&boot_kobj->kobj, &iscsi_boot_ktype,
				 शून्य, name, index)) अणु
		kobject_put(&boot_kobj->kobj);
		वापस शून्य;
	पूर्ण
	boot_kobj->data = data;
	boot_kobj->show = show;
	boot_kobj->is_visible = is_visible;
	boot_kobj->release = release;

	अगर (sysfs_create_group(&boot_kobj->kobj, attr_group)) अणु
		/*
		 * We करो not want to मुक्त this because the caller
		 * will assume that since the creation call failed
		 * the boot kobj was not setup and the normal release
		 * path is not being run.
		 */
		boot_kobj->release = शून्य;
		kobject_put(&boot_kobj->kobj);
		वापस शून्य;
	पूर्ण
	boot_kobj->attr_group = attr_group;

	kobject_uevent(&boot_kobj->kobj, KOBJ_ADD);
	/* Nothing broke so lets add it to the list. */
	list_add_tail(&boot_kobj->list, &boot_kset->kobj_list);
	वापस boot_kobj;
पूर्ण

अटल व्योम iscsi_boot_हटाओ_kobj(काष्ठा iscsi_boot_kobj *boot_kobj)
अणु
	list_del(&boot_kobj->list);
	sysfs_हटाओ_group(&boot_kobj->kobj, boot_kobj->attr_group);
	kobject_put(&boot_kobj->kobj);
पूर्ण

/**
 * iscsi_boot_create_target() - create boot target sysfs dir
 * @boot_kset: boot kset
 * @index: the target id
 * @data: driver specअगरic data क्रम target
 * @show: attr show function
 * @is_visible: attr visibility function
 * @release: release function
 *
 * Note: The boot sysfs lib will मुक्त the data passed in क्रम the caller
 * when all refs to the target kobject have been released.
 */
काष्ठा iscsi_boot_kobj *
iscsi_boot_create_target(काष्ठा iscsi_boot_kset *boot_kset, पूर्णांक index,
			 व्योम *data,
			 sमाप_प्रकार (*show) (व्योम *data, पूर्णांक type, अक्षर *buf),
			 umode_t (*is_visible) (व्योम *data, पूर्णांक type),
			 व्योम (*release) (व्योम *data))
अणु
	वापस iscsi_boot_create_kobj(boot_kset, &iscsi_boot_target_attr_group,
				      "target%d", index, data, show, is_visible,
				      release);
पूर्ण
EXPORT_SYMBOL_GPL(iscsi_boot_create_target);

/**
 * iscsi_boot_create_initiator() - create boot initiator sysfs dir
 * @boot_kset: boot kset
 * @index: the initiator id
 * @data: driver specअगरic data
 * @show: attr show function
 * @is_visible: attr visibility function
 * @release: release function
 *
 * Note: The boot sysfs lib will मुक्त the data passed in क्रम the caller
 * when all refs to the initiator kobject have been released.
 */
काष्ठा iscsi_boot_kobj *
iscsi_boot_create_initiator(काष्ठा iscsi_boot_kset *boot_kset, पूर्णांक index,
			    व्योम *data,
			    sमाप_प्रकार (*show) (व्योम *data, पूर्णांक type, अक्षर *buf),
			    umode_t (*is_visible) (व्योम *data, पूर्णांक type),
			    व्योम (*release) (व्योम *data))
अणु
	वापस iscsi_boot_create_kobj(boot_kset,
				      &iscsi_boot_initiator_attr_group,
				      "initiator", index, data, show,
				      is_visible, release);
पूर्ण
EXPORT_SYMBOL_GPL(iscsi_boot_create_initiator);

/**
 * iscsi_boot_create_ethernet() - create boot ethernet sysfs dir
 * @boot_kset: boot kset
 * @index: the ethernet device id
 * @data: driver specअगरic data
 * @show: attr show function
 * @is_visible: attr visibility function
 * @release: release function
 *
 * Note: The boot sysfs lib will मुक्त the data passed in क्रम the caller
 * when all refs to the ethernet kobject have been released.
 */
काष्ठा iscsi_boot_kobj *
iscsi_boot_create_ethernet(काष्ठा iscsi_boot_kset *boot_kset, पूर्णांक index,
			   व्योम *data,
			   sमाप_प्रकार (*show) (व्योम *data, पूर्णांक type, अक्षर *buf),
			   umode_t (*is_visible) (व्योम *data, पूर्णांक type),
			   व्योम (*release) (व्योम *data))
अणु
	वापस iscsi_boot_create_kobj(boot_kset,
				      &iscsi_boot_ethernet_attr_group,
				      "ethernet%d", index, data, show,
				      is_visible, release);
पूर्ण
EXPORT_SYMBOL_GPL(iscsi_boot_create_ethernet);

/**
 * iscsi_boot_create_acpitbl() - create boot acpi table sysfs dir
 * @boot_kset: boot kset
 * @index: not used
 * @data: driver specअगरic data
 * @show: attr show function
 * @is_visible: attr visibility function
 * @release: release function
 *
 * Note: The boot sysfs lib will मुक्त the data passed in क्रम the caller
 * when all refs to the acpitbl kobject have been released.
 */
काष्ठा iscsi_boot_kobj *
iscsi_boot_create_acpitbl(काष्ठा iscsi_boot_kset *boot_kset, पूर्णांक index,
			   व्योम *data,
			   sमाप_प्रकार (*show)(व्योम *data, पूर्णांक type, अक्षर *buf),
			   umode_t (*is_visible)(व्योम *data, पूर्णांक type),
			   व्योम (*release)(व्योम *data))
अणु
	वापस iscsi_boot_create_kobj(boot_kset,
				      &iscsi_boot_acpitbl_attr_group,
				      "acpi_header", index, data, show,
				      is_visible, release);
पूर्ण
EXPORT_SYMBOL_GPL(iscsi_boot_create_acpitbl);

/**
 * iscsi_boot_create_kset() - creates root sysfs tree
 * @set_name: name of root dir
 */
काष्ठा iscsi_boot_kset *iscsi_boot_create_kset(स्थिर अक्षर *set_name)
अणु
	काष्ठा iscsi_boot_kset *boot_kset;

	boot_kset = kzalloc(माप(*boot_kset), GFP_KERNEL);
	अगर (!boot_kset)
		वापस शून्य;

	boot_kset->kset = kset_create_and_add(set_name, शून्य, firmware_kobj);
	अगर (!boot_kset->kset) अणु
		kमुक्त(boot_kset);
		वापस शून्य;
	पूर्ण

	INIT_LIST_HEAD(&boot_kset->kobj_list);
	वापस boot_kset;
पूर्ण
EXPORT_SYMBOL_GPL(iscsi_boot_create_kset);

/**
 * iscsi_boot_create_host_kset() - creates root sysfs tree क्रम a scsi host
 * @hostno: host number of scsi host
 */
काष्ठा iscsi_boot_kset *iscsi_boot_create_host_kset(अचिन्हित पूर्णांक hostno)
अणु
	काष्ठा iscsi_boot_kset *boot_kset;
	अक्षर *set_name;

	set_name = kaप्र_लिखो(GFP_KERNEL, "iscsi_boot%u", hostno);
	अगर (!set_name)
		वापस शून्य;

	boot_kset = iscsi_boot_create_kset(set_name);
	kमुक्त(set_name);
	वापस boot_kset;
पूर्ण
EXPORT_SYMBOL_GPL(iscsi_boot_create_host_kset);

/**
 * iscsi_boot_destroy_kset() - destroy kset and kobjects under it
 * @boot_kset: boot kset
 *
 * This will हटाओ the kset and kobjects and attrs under it.
 */
व्योम iscsi_boot_destroy_kset(काष्ठा iscsi_boot_kset *boot_kset)
अणु
	काष्ठा iscsi_boot_kobj *boot_kobj, *पंचांगp_kobj;

	अगर (!boot_kset)
		वापस;

	list_क्रम_each_entry_safe(boot_kobj, पंचांगp_kobj,
				 &boot_kset->kobj_list, list)
		iscsi_boot_हटाओ_kobj(boot_kobj);

	kset_unरेजिस्टर(boot_kset->kset);
	kमुक्त(boot_kset);
पूर्ण
EXPORT_SYMBOL_GPL(iscsi_boot_destroy_kset);
