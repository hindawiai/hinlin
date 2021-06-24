<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  Copyright 2007-2010 Red Hat, Inc.
 *  by Peter Jones <pjones@redhat.com>
 *  Copyright 2008 IBM, Inc.
 *  by Konrad Rzeszutek <konradr@linux.vnet.ibm.com>
 *  Copyright 2008
 *  by Konrad Rzeszutek <ketuzsezr@darnok.org>
 *
 * This code exposes the iSCSI Boot Format Table to userland via sysfs.
 *
 * Changelog:
 *
 *  06 Jan 2010 - Peter Jones <pjones@redhat.com>
 *    New changelog entries are in the git log from now on.  Not here.
 *
 *  14 Mar 2008 - Konrad Rzeszutek <ketuzsezr@darnok.org>
 *    Updated comments and copyrights. (v0.4.9)
 *
 *  11 Feb 2008 - Konrad Rzeszutek <konradr@linux.vnet.ibm.com>
 *    Converted to using ibft_addr. (v0.4.8)
 *
 *   8 Feb 2008 - Konrad Rzeszutek <konradr@linux.vnet.ibm.com>
 *    Combined two functions in one: reserve_ibft_region. (v0.4.7)
 *
 *  30 Jan 2008 - Konrad Rzeszutek <konradr@linux.vnet.ibm.com>
 *   Added logic to handle IPv6 addresses. (v0.4.6)
 *
 *  25 Jan 2008 - Konrad Rzeszutek <konradr@linux.vnet.ibm.com>
 *   Added logic to handle badly not-to-spec iBFT. (v0.4.5)
 *
 *   4 Jan 2008 - Konrad Rzeszutek <konradr@linux.vnet.ibm.com>
 *   Added __init to function declarations. (v0.4.4)
 *
 *  21 Dec 2007 - Konrad Rzeszutek <konradr@linux.vnet.ibm.com>
 *   Updated kobject registration, combined unरेजिस्टर functions in one
 *   and code and style cleanup. (v0.4.3)
 *
 *   5 Dec 2007 - Konrad Rzeszutek <konradr@linux.vnet.ibm.com>
 *   Added end-markers to क्रमागतs and re-organized kobject registration. (v0.4.2)
 *
 *   4 Dec 2007 - Konrad Rzeszutek <konradr@linux.vnet.ibm.com>
 *   Created 'device' sysfs link to the NIC and style cleanup. (v0.4.1)
 *
 *  28 Nov 2007 - Konrad Rzeszutek <konradr@linux.vnet.ibm.com>
 *   Added sysfs-ibft करोcumentation, moved 'find_ibft' function to
 *   in its own file and added text attributes क्रम every काष्ठा field.  (v0.4)
 *
 *  21 Nov 2007 - Konrad Rzeszutek <konradr@linux.vnet.ibm.com>
 *   Added text attributes emulating OpenFirmware /proc/device-tree naming.
 *   Removed binary /sysfs पूर्णांकerface (v0.3)
 *
 *  29 Aug 2007 - Konrad Rzeszutek <konradr@linux.vnet.ibm.com>
 *   Added functionality in setup.c to reserve iBFT region. (v0.2)
 *
 *  27 Aug 2007 - Konrad Rzeszutek <konradr@linux.vnet.ibm.com>
 *   First version exposing iBFT data via a binary /sysfs. (v0.1)
 */


#समावेश <linux/blkdev.h>
#समावेश <linux/capability.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/device.h>
#समावेश <linux/err.h>
#समावेश <linux/init.h>
#समावेश <linux/iscsi_ibft.h>
#समावेश <linux/सीमा.स>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/slab.h>
#समावेश <linux/स्थिति.स>
#समावेश <linux/माला.स>
#समावेश <linux/types.h>
#समावेश <linux/acpi.h>
#समावेश <linux/iscsi_boot_sysfs.h>

#घोषणा IBFT_ISCSI_VERSION "0.5.0"
#घोषणा IBFT_ISCSI_DATE "2010-Feb-25"

MODULE_AUTHOR("Peter Jones <pjones@redhat.com> and "
	      "Konrad Rzeszutek <ketuzsezr@darnok.org>");
MODULE_DESCRIPTION("sysfs interface to BIOS iBFT information");
MODULE_LICENSE("GPL");
MODULE_VERSION(IBFT_ISCSI_VERSION);

#अगर_अघोषित CONFIG_ISCSI_IBFT_FIND
काष्ठा acpi_table_ibft *ibft_addr;
#पूर्ण_अगर

काष्ठा ibft_hdr अणु
	u8 id;
	u8 version;
	u16 length;
	u8 index;
	u8 flags;
पूर्ण __attribute__((__packed__));

काष्ठा ibft_control अणु
	काष्ठा ibft_hdr hdr;
	u16 extensions;
	u16 initiator_off;
	u16 nic0_off;
	u16 tgt0_off;
	u16 nic1_off;
	u16 tgt1_off;
	u16 expansion[];
पूर्ण __attribute__((__packed__));

काष्ठा ibft_initiator अणु
	काष्ठा ibft_hdr hdr;
	अक्षर isns_server[16];
	अक्षर slp_server[16];
	अक्षर pri_radius_server[16];
	अक्षर sec_radius_server[16];
	u16 initiator_name_len;
	u16 initiator_name_off;
पूर्ण __attribute__((__packed__));

काष्ठा ibft_nic अणु
	काष्ठा ibft_hdr hdr;
	अक्षर ip_addr[16];
	u8 subnet_mask_prefix;
	u8 origin;
	अक्षर gateway[16];
	अक्षर primary_dns[16];
	अक्षर secondary_dns[16];
	अक्षर dhcp[16];
	u16 vlan;
	अक्षर mac[6];
	u16 pci_bdf;
	u16 hostname_len;
	u16 hostname_off;
पूर्ण __attribute__((__packed__));

काष्ठा ibft_tgt अणु
	काष्ठा ibft_hdr hdr;
	अक्षर ip_addr[16];
	u16 port;
	अक्षर lun[8];
	u8 chap_type;
	u8 nic_assoc;
	u16 tgt_name_len;
	u16 tgt_name_off;
	u16 chap_name_len;
	u16 chap_name_off;
	u16 chap_secret_len;
	u16 chap_secret_off;
	u16 rev_chap_name_len;
	u16 rev_chap_name_off;
	u16 rev_chap_secret_len;
	u16 rev_chap_secret_off;
पूर्ण __attribute__((__packed__));

/*
 * The kobject dअगरferent types and its names.
 *
*/
क्रमागत ibft_id अणु
	id_reserved = 0, /* We करोn't support. */
	id_control = 1, /* Should show up only once and is not exported. */
	id_initiator = 2,
	id_nic = 3,
	id_target = 4,
	id_extensions = 5, /* We करोn't support. */
	id_end_marker,
पूर्ण;

/*
 * The kobject and attribute काष्ठाures.
 */

काष्ठा ibft_kobject अणु
	काष्ठा acpi_table_ibft *header;
	जोड़ अणु
		काष्ठा ibft_initiator *initiator;
		काष्ठा ibft_nic *nic;
		काष्ठा ibft_tgt *tgt;
		काष्ठा ibft_hdr *hdr;
	पूर्ण;
पूर्ण;

अटल काष्ठा iscsi_boot_kset *boot_kset;

/* fully null address */
अटल स्थिर अक्षर nulls[16];

/* IPv4-mapped IPv6 ::ffff:0.0.0.0 */
अटल स्थिर अक्षर mapped_nulls[16] = अणु 0x00, 0x00, 0x00, 0x00,
                                       0x00, 0x00, 0x00, 0x00,
                                       0x00, 0x00, 0xff, 0xff,
                                       0x00, 0x00, 0x00, 0x00 पूर्ण;

अटल पूर्णांक address_not_null(u8 *ip)
अणु
	वापस (स_भेद(ip, nulls, 16) && स_भेद(ip, mapped_nulls, 16));
पूर्ण

/*
 * Helper functions to parse data properly.
 */
अटल sमाप_प्रकार प्र_लिखो_ipaddr(अक्षर *buf, u8 *ip)
अणु
	अक्षर *str = buf;

	अगर (ip[0] == 0 && ip[1] == 0 && ip[2] == 0 && ip[3] == 0 &&
	    ip[4] == 0 && ip[5] == 0 && ip[6] == 0 && ip[7] == 0 &&
	    ip[8] == 0 && ip[9] == 0 && ip[10] == 0xff && ip[11] == 0xff) अणु
		/*
		 * IPV4
		 */
		str += प्र_लिखो(buf, "%pI4", ip + 12);
	पूर्ण अन्यथा अणु
		/*
		 * IPv6
		 */
		str += प्र_लिखो(str, "%pI6", ip);
	पूर्ण
	str += प्र_लिखो(str, "\n");
	वापस str - buf;
पूर्ण

अटल sमाप_प्रकार प्र_लिखो_string(अक्षर *str, पूर्णांक len, अक्षर *buf)
अणु
	वापस प्र_लिखो(str, "%.*s\n", len, buf);
पूर्ण

/*
 * Helper function to verअगरy the IBFT header.
 */
अटल पूर्णांक ibft_verअगरy_hdr(अक्षर *t, काष्ठा ibft_hdr *hdr, पूर्णांक id, पूर्णांक length)
अणु
	अगर (hdr->id != id) अणु
		prपूर्णांकk(KERN_ERR "iBFT error: We expected the %s " \
				"field header.id to have %d but " \
				"found %d instead!\n", t, id, hdr->id);
		वापस -ENODEV;
	पूर्ण
	अगर (length && hdr->length != length) अणु
		prपूर्णांकk(KERN_ERR "iBFT error: We expected the %s " \
				"field header.length to have %d but " \
				"found %d instead!\n", t, length, hdr->length);
		वापस -ENODEV;
	पूर्ण

	वापस 0;
पूर्ण

/*
 *  Routines क्रम parsing the iBFT data to be human पढ़ोable.
 */
अटल sमाप_प्रकार ibft_attr_show_initiator(व्योम *data, पूर्णांक type, अक्षर *buf)
अणु
	काष्ठा ibft_kobject *entry = data;
	काष्ठा ibft_initiator *initiator = entry->initiator;
	व्योम *ibft_loc = entry->header;
	अक्षर *str = buf;

	अगर (!initiator)
		वापस 0;

	चयन (type) अणु
	हाल ISCSI_BOOT_INI_INDEX:
		str += प्र_लिखो(str, "%d\n", initiator->hdr.index);
		अवरोध;
	हाल ISCSI_BOOT_INI_FLAGS:
		str += प्र_लिखो(str, "%d\n", initiator->hdr.flags);
		अवरोध;
	हाल ISCSI_BOOT_INI_ISNS_SERVER:
		str += प्र_लिखो_ipaddr(str, initiator->isns_server);
		अवरोध;
	हाल ISCSI_BOOT_INI_SLP_SERVER:
		str += प्र_लिखो_ipaddr(str, initiator->slp_server);
		अवरोध;
	हाल ISCSI_BOOT_INI_PRI_RADIUS_SERVER:
		str += प्र_लिखो_ipaddr(str, initiator->pri_radius_server);
		अवरोध;
	हाल ISCSI_BOOT_INI_SEC_RADIUS_SERVER:
		str += प्र_लिखो_ipaddr(str, initiator->sec_radius_server);
		अवरोध;
	हाल ISCSI_BOOT_INI_INITIATOR_NAME:
		str += प्र_लिखो_string(str, initiator->initiator_name_len,
				      (अक्षर *)ibft_loc +
				      initiator->initiator_name_off);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस str - buf;
पूर्ण

अटल sमाप_प्रकार ibft_attr_show_nic(व्योम *data, पूर्णांक type, अक्षर *buf)
अणु
	काष्ठा ibft_kobject *entry = data;
	काष्ठा ibft_nic *nic = entry->nic;
	व्योम *ibft_loc = entry->header;
	अक्षर *str = buf;
	__be32 val;

	अगर (!nic)
		वापस 0;

	चयन (type) अणु
	हाल ISCSI_BOOT_ETH_INDEX:
		str += प्र_लिखो(str, "%d\n", nic->hdr.index);
		अवरोध;
	हाल ISCSI_BOOT_ETH_FLAGS:
		str += प्र_लिखो(str, "%d\n", nic->hdr.flags);
		अवरोध;
	हाल ISCSI_BOOT_ETH_IP_ADDR:
		str += प्र_लिखो_ipaddr(str, nic->ip_addr);
		अवरोध;
	हाल ISCSI_BOOT_ETH_SUBNET_MASK:
		val = cpu_to_be32(~((1 << (32-nic->subnet_mask_prefix))-1));
		str += प्र_लिखो(str, "%pI4", &val);
		अवरोध;
	हाल ISCSI_BOOT_ETH_PREFIX_LEN:
		str += प्र_लिखो(str, "%d\n", nic->subnet_mask_prefix);
		अवरोध;
	हाल ISCSI_BOOT_ETH_ORIGIN:
		str += प्र_लिखो(str, "%d\n", nic->origin);
		अवरोध;
	हाल ISCSI_BOOT_ETH_GATEWAY:
		str += प्र_लिखो_ipaddr(str, nic->gateway);
		अवरोध;
	हाल ISCSI_BOOT_ETH_PRIMARY_DNS:
		str += प्र_लिखो_ipaddr(str, nic->primary_dns);
		अवरोध;
	हाल ISCSI_BOOT_ETH_SECONDARY_DNS:
		str += प्र_लिखो_ipaddr(str, nic->secondary_dns);
		अवरोध;
	हाल ISCSI_BOOT_ETH_DHCP:
		str += प्र_लिखो_ipaddr(str, nic->dhcp);
		अवरोध;
	हाल ISCSI_BOOT_ETH_VLAN:
		str += प्र_लिखो(str, "%d\n", nic->vlan);
		अवरोध;
	हाल ISCSI_BOOT_ETH_MAC:
		str += प्र_लिखो(str, "%pM\n", nic->mac);
		अवरोध;
	हाल ISCSI_BOOT_ETH_HOSTNAME:
		str += प्र_लिखो_string(str, nic->hostname_len,
				      (अक्षर *)ibft_loc + nic->hostname_off);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस str - buf;
पूर्ण;

अटल sमाप_प्रकार ibft_attr_show_target(व्योम *data, पूर्णांक type, अक्षर *buf)
अणु
	काष्ठा ibft_kobject *entry = data;
	काष्ठा ibft_tgt *tgt = entry->tgt;
	व्योम *ibft_loc = entry->header;
	अक्षर *str = buf;
	पूर्णांक i;

	अगर (!tgt)
		वापस 0;

	चयन (type) अणु
	हाल ISCSI_BOOT_TGT_INDEX:
		str += प्र_लिखो(str, "%d\n", tgt->hdr.index);
		अवरोध;
	हाल ISCSI_BOOT_TGT_FLAGS:
		str += प्र_लिखो(str, "%d\n", tgt->hdr.flags);
		अवरोध;
	हाल ISCSI_BOOT_TGT_IP_ADDR:
		str += प्र_लिखो_ipaddr(str, tgt->ip_addr);
		अवरोध;
	हाल ISCSI_BOOT_TGT_PORT:
		str += प्र_लिखो(str, "%d\n", tgt->port);
		अवरोध;
	हाल ISCSI_BOOT_TGT_LUN:
		क्रम (i = 0; i < 8; i++)
			str += प्र_लिखो(str, "%x", (u8)tgt->lun[i]);
		str += प्र_लिखो(str, "\n");
		अवरोध;
	हाल ISCSI_BOOT_TGT_NIC_ASSOC:
		str += प्र_लिखो(str, "%d\n", tgt->nic_assoc);
		अवरोध;
	हाल ISCSI_BOOT_TGT_CHAP_TYPE:
		str += प्र_लिखो(str, "%d\n", tgt->chap_type);
		अवरोध;
	हाल ISCSI_BOOT_TGT_NAME:
		str += प्र_लिखो_string(str, tgt->tgt_name_len,
				      (अक्षर *)ibft_loc + tgt->tgt_name_off);
		अवरोध;
	हाल ISCSI_BOOT_TGT_CHAP_NAME:
		str += प्र_लिखो_string(str, tgt->chap_name_len,
				      (अक्षर *)ibft_loc + tgt->chap_name_off);
		अवरोध;
	हाल ISCSI_BOOT_TGT_CHAP_SECRET:
		str += प्र_लिखो_string(str, tgt->chap_secret_len,
				      (अक्षर *)ibft_loc + tgt->chap_secret_off);
		अवरोध;
	हाल ISCSI_BOOT_TGT_REV_CHAP_NAME:
		str += प्र_लिखो_string(str, tgt->rev_chap_name_len,
				      (अक्षर *)ibft_loc +
				      tgt->rev_chap_name_off);
		अवरोध;
	हाल ISCSI_BOOT_TGT_REV_CHAP_SECRET:
		str += प्र_लिखो_string(str, tgt->rev_chap_secret_len,
				      (अक्षर *)ibft_loc +
				      tgt->rev_chap_secret_off);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस str - buf;
पूर्ण

अटल sमाप_प्रकार ibft_attr_show_acpitbl(व्योम *data, पूर्णांक type, अक्षर *buf)
अणु
	काष्ठा ibft_kobject *entry = data;
	अक्षर *str = buf;

	चयन (type) अणु
	हाल ISCSI_BOOT_ACPITBL_SIGNATURE:
		str += प्र_लिखो_string(str, ACPI_NAMESEG_SIZE,
				      entry->header->header.signature);
		अवरोध;
	हाल ISCSI_BOOT_ACPITBL_OEM_ID:
		str += प्र_लिखो_string(str, ACPI_OEM_ID_SIZE,
				      entry->header->header.oem_id);
		अवरोध;
	हाल ISCSI_BOOT_ACPITBL_OEM_TABLE_ID:
		str += प्र_लिखो_string(str, ACPI_OEM_TABLE_ID_SIZE,
				      entry->header->header.oem_table_id);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस str - buf;
पूर्ण

अटल पूर्णांक __init ibft_check_device(व्योम)
अणु
	पूर्णांक len;
	u8 *pos;
	u8 csum = 0;

	len = ibft_addr->header.length;

	/* Sanity checking of iBFT. */
	अगर (ibft_addr->header.revision != 1) अणु
		prपूर्णांकk(KERN_ERR "iBFT module supports only revision 1, " \
				"while this is %d.\n",
				ibft_addr->header.revision);
		वापस -ENOENT;
	पूर्ण
	क्रम (pos = (u8 *)ibft_addr; pos < (u8 *)ibft_addr + len; pos++)
		csum += *pos;

	अगर (csum) अणु
		prपूर्णांकk(KERN_ERR "iBFT has incorrect checksum (0x%x)!\n", csum);
		वापस -ENOENT;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Helper routiners to check to determine अगर the entry is valid
 * in the proper iBFT काष्ठाure.
 */
अटल umode_t ibft_check_nic_क्रम(व्योम *data, पूर्णांक type)
अणु
	काष्ठा ibft_kobject *entry = data;
	काष्ठा ibft_nic *nic = entry->nic;
	umode_t rc = 0;

	चयन (type) अणु
	हाल ISCSI_BOOT_ETH_INDEX:
	हाल ISCSI_BOOT_ETH_FLAGS:
		rc = S_IRUGO;
		अवरोध;
	हाल ISCSI_BOOT_ETH_IP_ADDR:
		अगर (address_not_null(nic->ip_addr))
			rc = S_IRUGO;
		अवरोध;
	हाल ISCSI_BOOT_ETH_PREFIX_LEN:
	हाल ISCSI_BOOT_ETH_SUBNET_MASK:
		अगर (nic->subnet_mask_prefix)
			rc = S_IRUGO;
		अवरोध;
	हाल ISCSI_BOOT_ETH_ORIGIN:
		rc = S_IRUGO;
		अवरोध;
	हाल ISCSI_BOOT_ETH_GATEWAY:
		अगर (address_not_null(nic->gateway))
			rc = S_IRUGO;
		अवरोध;
	हाल ISCSI_BOOT_ETH_PRIMARY_DNS:
		अगर (address_not_null(nic->primary_dns))
			rc = S_IRUGO;
		अवरोध;
	हाल ISCSI_BOOT_ETH_SECONDARY_DNS:
		अगर (address_not_null(nic->secondary_dns))
			rc = S_IRUGO;
		अवरोध;
	हाल ISCSI_BOOT_ETH_DHCP:
		अगर (address_not_null(nic->dhcp))
			rc = S_IRUGO;
		अवरोध;
	हाल ISCSI_BOOT_ETH_VLAN:
	हाल ISCSI_BOOT_ETH_MAC:
		rc = S_IRUGO;
		अवरोध;
	हाल ISCSI_BOOT_ETH_HOSTNAME:
		अगर (nic->hostname_off)
			rc = S_IRUGO;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस rc;
पूर्ण

अटल umode_t __init ibft_check_tgt_क्रम(व्योम *data, पूर्णांक type)
अणु
	काष्ठा ibft_kobject *entry = data;
	काष्ठा ibft_tgt *tgt = entry->tgt;
	umode_t rc = 0;

	चयन (type) अणु
	हाल ISCSI_BOOT_TGT_INDEX:
	हाल ISCSI_BOOT_TGT_FLAGS:
	हाल ISCSI_BOOT_TGT_IP_ADDR:
	हाल ISCSI_BOOT_TGT_PORT:
	हाल ISCSI_BOOT_TGT_LUN:
	हाल ISCSI_BOOT_TGT_NIC_ASSOC:
	हाल ISCSI_BOOT_TGT_CHAP_TYPE:
		rc = S_IRUGO;
		अवरोध;
	हाल ISCSI_BOOT_TGT_NAME:
		अगर (tgt->tgt_name_len)
			rc = S_IRUGO;
		अवरोध;
	हाल ISCSI_BOOT_TGT_CHAP_NAME:
	हाल ISCSI_BOOT_TGT_CHAP_SECRET:
		अगर (tgt->chap_name_len)
			rc = S_IRUGO;
		अवरोध;
	हाल ISCSI_BOOT_TGT_REV_CHAP_NAME:
	हाल ISCSI_BOOT_TGT_REV_CHAP_SECRET:
		अगर (tgt->rev_chap_name_len)
			rc = S_IRUGO;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस rc;
पूर्ण

अटल umode_t __init ibft_check_initiator_क्रम(व्योम *data, पूर्णांक type)
अणु
	काष्ठा ibft_kobject *entry = data;
	काष्ठा ibft_initiator *init = entry->initiator;
	umode_t rc = 0;

	चयन (type) अणु
	हाल ISCSI_BOOT_INI_INDEX:
	हाल ISCSI_BOOT_INI_FLAGS:
		rc = S_IRUGO;
		अवरोध;
	हाल ISCSI_BOOT_INI_ISNS_SERVER:
		अगर (address_not_null(init->isns_server))
			rc = S_IRUGO;
		अवरोध;
	हाल ISCSI_BOOT_INI_SLP_SERVER:
		अगर (address_not_null(init->slp_server))
			rc = S_IRUGO;
		अवरोध;
	हाल ISCSI_BOOT_INI_PRI_RADIUS_SERVER:
		अगर (address_not_null(init->pri_radius_server))
			rc = S_IRUGO;
		अवरोध;
	हाल ISCSI_BOOT_INI_SEC_RADIUS_SERVER:
		अगर (address_not_null(init->sec_radius_server))
			rc = S_IRUGO;
		अवरोध;
	हाल ISCSI_BOOT_INI_INITIATOR_NAME:
		अगर (init->initiator_name_len)
			rc = S_IRUGO;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस rc;
पूर्ण

अटल umode_t __init ibft_check_acpitbl_क्रम(व्योम *data, पूर्णांक type)
अणु

	umode_t rc = 0;

	चयन (type) अणु
	हाल ISCSI_BOOT_ACPITBL_SIGNATURE:
	हाल ISCSI_BOOT_ACPITBL_OEM_ID:
	हाल ISCSI_BOOT_ACPITBL_OEM_TABLE_ID:
		rc = S_IRUGO;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस rc;
पूर्ण

अटल व्योम ibft_kobj_release(व्योम *data)
अणु
	kमुक्त(data);
पूर्ण

/*
 * Helper function क्रम ibft_रेजिस्टर_kobjects.
 */
अटल पूर्णांक __init ibft_create_kobject(काष्ठा acpi_table_ibft *header,
				      काष्ठा ibft_hdr *hdr)
अणु
	काष्ठा iscsi_boot_kobj *boot_kobj = शून्य;
	काष्ठा ibft_kobject *ibft_kobj = शून्य;
	काष्ठा ibft_nic *nic = (काष्ठा ibft_nic *)hdr;
	काष्ठा pci_dev *pci_dev;
	पूर्णांक rc = 0;

	ibft_kobj = kzalloc(माप(*ibft_kobj), GFP_KERNEL);
	अगर (!ibft_kobj)
		वापस -ENOMEM;

	ibft_kobj->header = header;
	ibft_kobj->hdr = hdr;

	चयन (hdr->id) अणु
	हाल id_initiator:
		rc = ibft_verअगरy_hdr("initiator", hdr, id_initiator,
				     माप(*ibft_kobj->initiator));
		अगर (rc)
			अवरोध;

		boot_kobj = iscsi_boot_create_initiator(boot_kset, hdr->index,
						ibft_kobj,
						ibft_attr_show_initiator,
						ibft_check_initiator_क्रम,
						ibft_kobj_release);
		अगर (!boot_kobj) अणु
			rc = -ENOMEM;
			जाओ मुक्त_ibft_obj;
		पूर्ण
		अवरोध;
	हाल id_nic:
		rc = ibft_verअगरy_hdr("ethernet", hdr, id_nic,
				     माप(*ibft_kobj->nic));
		अगर (rc)
			अवरोध;

		boot_kobj = iscsi_boot_create_ethernet(boot_kset, hdr->index,
						       ibft_kobj,
						       ibft_attr_show_nic,
						       ibft_check_nic_क्रम,
						       ibft_kobj_release);
		अगर (!boot_kobj) अणु
			rc = -ENOMEM;
			जाओ मुक्त_ibft_obj;
		पूर्ण
		अवरोध;
	हाल id_target:
		rc = ibft_verअगरy_hdr("target", hdr, id_target,
				     माप(*ibft_kobj->tgt));
		अगर (rc)
			अवरोध;

		boot_kobj = iscsi_boot_create_target(boot_kset, hdr->index,
						     ibft_kobj,
						     ibft_attr_show_target,
						     ibft_check_tgt_क्रम,
						     ibft_kobj_release);
		अगर (!boot_kobj) अणु
			rc = -ENOMEM;
			जाओ मुक्त_ibft_obj;
		पूर्ण
		अवरोध;
	हाल id_reserved:
	हाल id_control:
	हाल id_extensions:
		/* Fields which we करोn't support. Ignore them */
		rc = 1;
		अवरोध;
	शेष:
		prपूर्णांकk(KERN_ERR "iBFT has unknown structure type (%d). " \
				"Report this bug to %.6s!\n", hdr->id,
				header->header.oem_id);
		rc = 1;
		अवरोध;
	पूर्ण

	अगर (rc) अणु
		/* Skip adding this kobject, but निकास with non-fatal error. */
		rc = 0;
		जाओ मुक्त_ibft_obj;
	पूर्ण

	अगर (hdr->id == id_nic) अणु
		/*
		* We करोn't search क्रम the device in other करोमुख्यs than
		* zero. This is because on x86 platक्रमms the BIOS
		* executes only devices which are in करोमुख्य 0. Furthermore, the
		* iBFT spec करोesn't have a करोमुख्य id field :-(
		*/
		pci_dev = pci_get_करोमुख्य_bus_and_slot(0,
						(nic->pci_bdf & 0xff00) >> 8,
						(nic->pci_bdf & 0xff));
		अगर (pci_dev) अणु
			rc = sysfs_create_link(&boot_kobj->kobj,
					       &pci_dev->dev.kobj, "device");
			pci_dev_put(pci_dev);
		पूर्ण
	पूर्ण
	वापस 0;

मुक्त_ibft_obj:
	kमुक्त(ibft_kobj);
	वापस rc;
पूर्ण

/*
 * Scan the IBFT table काष्ठाure क्रम the NIC and Target fields. When
 * found add them on the passed-in list. We करो not support the other
 * fields at this poपूर्णांक, so they are skipped.
 */
अटल पूर्णांक __init ibft_रेजिस्टर_kobjects(काष्ठा acpi_table_ibft *header)
अणु
	काष्ठा ibft_control *control = शून्य;
	काष्ठा iscsi_boot_kobj *boot_kobj;
	काष्ठा ibft_kobject *ibft_kobj;
	व्योम *ptr, *end;
	पूर्णांक rc = 0;
	u16 offset;
	u16 eot_offset;

	control = (व्योम *)header + माप(*header);
	end = (व्योम *)control + control->hdr.length;
	eot_offset = (व्योम *)header + header->header.length - (व्योम *)control;
	rc = ibft_verअगरy_hdr("control", (काष्ठा ibft_hdr *)control, id_control, 0);

	/* iBFT table safety checking */
	rc |= ((control->hdr.index) ? -ENODEV : 0);
	rc |= ((control->hdr.length < माप(*control)) ? -ENODEV : 0);
	अगर (rc) अणु
		prपूर्णांकk(KERN_ERR "iBFT error: Control header is invalid!\n");
		वापस rc;
	पूर्ण
	क्रम (ptr = &control->initiator_off; ptr + माप(u16) <= end; ptr += माप(u16)) अणु
		offset = *(u16 *)ptr;
		अगर (offset && offset < header->header.length &&
						offset < eot_offset) अणु
			rc = ibft_create_kobject(header,
						 (व्योम *)header + offset);
			अगर (rc)
				अवरोध;
		पूर्ण
	पूर्ण
	अगर (rc)
		वापस rc;

	ibft_kobj = kzalloc(माप(*ibft_kobj), GFP_KERNEL);
	अगर (!ibft_kobj)
		वापस -ENOMEM;

	ibft_kobj->header = header;
	ibft_kobj->hdr = शून्य; /*क्रम ibft_unरेजिस्टर*/

	boot_kobj = iscsi_boot_create_acpitbl(boot_kset, 0,
					ibft_kobj,
					ibft_attr_show_acpitbl,
					ibft_check_acpitbl_क्रम,
					ibft_kobj_release);
	अगर (!boot_kobj)  अणु
		kमुक्त(ibft_kobj);
		rc = -ENOMEM;
	पूर्ण

	वापस rc;
पूर्ण

अटल व्योम ibft_unरेजिस्टर(व्योम)
अणु
	काष्ठा iscsi_boot_kobj *boot_kobj, *पंचांगp_kobj;
	काष्ठा ibft_kobject *ibft_kobj;

	list_क्रम_each_entry_safe(boot_kobj, पंचांगp_kobj,
				 &boot_kset->kobj_list, list) अणु
		ibft_kobj = boot_kobj->data;
		अगर (ibft_kobj->hdr && ibft_kobj->hdr->id == id_nic)
			sysfs_हटाओ_link(&boot_kobj->kobj, "device");
	पूर्ण;
पूर्ण

अटल व्योम ibft_cleanup(व्योम)
अणु
	अगर (boot_kset) अणु
		ibft_unरेजिस्टर();
		iscsi_boot_destroy_kset(boot_kset);
	पूर्ण
पूर्ण

अटल व्योम __निकास ibft_निकास(व्योम)
अणु
	ibft_cleanup();
पूर्ण

#अगर_घोषित CONFIG_ACPI
अटल स्थिर काष्ठा अणु
	अक्षर *sign;
पूर्ण ibft_signs[] = अणु
	/*
	 * One spec says "IBFT", the other says "iBFT". We have to check
	 * क्रम both.
	 */
	अणु ACPI_SIG_IBFT पूर्ण,
	अणु "iBFT" पूर्ण,
	अणु "BIFT" पूर्ण,	/* Broadcom iSCSI Offload */
पूर्ण;

अटल व्योम __init acpi_find_ibft_region(व्योम)
अणु
	पूर्णांक i;
	काष्ठा acpi_table_header *table = शून्य;

	अगर (acpi_disabled)
		वापस;

	क्रम (i = 0; i < ARRAY_SIZE(ibft_signs) && !ibft_addr; i++) अणु
		acpi_get_table(ibft_signs[i].sign, 0, &table);
		ibft_addr = (काष्ठा acpi_table_ibft *)table;
	पूर्ण
पूर्ण
#अन्यथा
अटल व्योम __init acpi_find_ibft_region(व्योम)
अणु
पूर्ण
#पूर्ण_अगर

/*
 * ibft_init() - creates sysfs tree entries क्रम the iBFT data.
 */
अटल पूर्णांक __init ibft_init(व्योम)
अणु
	पूर्णांक rc = 0;

	/*
	   As on UEFI प्रणालीs the setup_arch()/find_ibft_region()
	   is called beक्रमe ACPI tables are parsed and it only करोes
	   legacy finding.
	*/
	अगर (!ibft_addr)
		acpi_find_ibft_region();

	अगर (ibft_addr) अणु
		pr_info("iBFT detected.\n");

		rc = ibft_check_device();
		अगर (rc)
			वापस rc;

		boot_kset = iscsi_boot_create_kset("ibft");
		अगर (!boot_kset)
			वापस -ENOMEM;

		/* Scan the IBFT क्रम data and रेजिस्टर the kobjects. */
		rc = ibft_रेजिस्टर_kobjects(ibft_addr);
		अगर (rc)
			जाओ out_मुक्त;
	पूर्ण अन्यथा
		prपूर्णांकk(KERN_INFO "No iBFT detected.\n");

	वापस 0;

out_मुक्त:
	ibft_cleanup();
	वापस rc;
पूर्ण

module_init(ibft_init);
module_निकास(ibft_निकास);
