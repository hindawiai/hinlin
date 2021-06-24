<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Export Runसमय Configuration Interface Table Version 2 (RCI2)
 * to sysfs
 *
 * Copyright (C) 2019 Dell Inc
 * by Narendra K <Narendra.K@dell.com>
 *
 * System firmware advertises the address of the RCI2 Table via
 * an EFI Configuration Table entry. This code retrieves the RCI2
 * table from the address and exports it to sysfs as a binary
 * attribute 'rci2' under /sys/firmware/efi/tables directory.
 */

#समावेश <linux/kobject.h>
#समावेश <linux/device.h>
#समावेश <linux/sysfs.h>
#समावेश <linux/efi.h>
#समावेश <linux/types.h>
#समावेश <linux/पन.स>

#घोषणा RCI_SIGNATURE	"_RC_"

काष्ठा rci2_table_global_hdr अणु
	u16 type;
	u16 resvd0;
	u16 hdr_len;
	u8 rci2_sig[4];
	u16 resvd1;
	u32 resvd2;
	u32 resvd3;
	u8 major_rev;
	u8 minor_rev;
	u16 num_of_काष्ठाs;
	u32 rci2_len;
	u16 rci2_chksum;
पूर्ण __packed;

अटल u8 *rci2_base;
अटल u32 rci2_table_len;
अचिन्हित दीर्घ rci2_table_phys __ro_after_init = EFI_INVALID_TABLE_ADDR;

अटल sमाप_प्रकार raw_table_पढ़ो(काष्ठा file *file, काष्ठा kobject *kobj,
			      काष्ठा bin_attribute *attr, अक्षर *buf,
			      loff_t pos, माप_प्रकार count)
अणु
	स_नकल(buf, attr->निजी + pos, count);
	वापस count;
पूर्ण

अटल BIN_ATTR(rci2, S_IRUSR, raw_table_पढ़ो, शून्य, 0);

अटल u16 checksum(व्योम)
अणु
	u8 len_is_odd = rci2_table_len % 2;
	u32 chksum_len = rci2_table_len;
	u16 *base = (u16 *)rci2_base;
	u8 buf[2] = अणु0पूर्ण;
	u32 offset = 0;
	u16 chksum = 0;

	अगर (len_is_odd)
		chksum_len -= 1;

	जबतक (offset < chksum_len) अणु
		chksum += *base;
		offset += 2;
		base++;
	पूर्ण

	अगर (len_is_odd) अणु
		buf[0] = *(u8 *)base;
		chksum += *(u16 *)(buf);
	पूर्ण

	वापस chksum;
पूर्ण

अटल पूर्णांक __init efi_rci2_sysfs_init(व्योम)
अणु
	काष्ठा kobject *tables_kobj;
	पूर्णांक ret = -ENOMEM;

	अगर (rci2_table_phys == EFI_INVALID_TABLE_ADDR)
		वापस 0;

	rci2_base = memremap(rci2_table_phys,
			     माप(काष्ठा rci2_table_global_hdr),
			     MEMREMAP_WB);
	अगर (!rci2_base) अणु
		pr_debug("RCI2 table init failed - could not map RCI2 table\n");
		जाओ err;
	पूर्ण

	अगर (म_भेदन(rci2_base +
		    दुरत्व(काष्ठा rci2_table_global_hdr, rci2_sig),
		    RCI_SIGNATURE, 4)) अणु
		pr_debug("RCI2 table init failed - incorrect signature\n");
		ret = -ENODEV;
		जाओ err_unmap;
	पूर्ण

	rci2_table_len = *(u32 *)(rci2_base +
				  दुरत्व(काष्ठा rci2_table_global_hdr,
				  rci2_len));

	memunmap(rci2_base);

	अगर (!rci2_table_len) अणु
		pr_debug("RCI2 table init failed - incorrect table length\n");
		जाओ err;
	पूर्ण

	rci2_base = memremap(rci2_table_phys, rci2_table_len, MEMREMAP_WB);
	अगर (!rci2_base) अणु
		pr_debug("RCI2 table - could not map RCI2 table\n");
		जाओ err;
	पूर्ण

	अगर (checksum() != 0) अणु
		pr_debug("RCI2 table - incorrect checksum\n");
		ret = -ENODEV;
		जाओ err_unmap;
	पूर्ण

	tables_kobj = kobject_create_and_add("tables", efi_kobj);
	अगर (!tables_kobj) अणु
		pr_debug("RCI2 table - tables_kobj creation failed\n");
		जाओ err_unmap;
	पूर्ण

	bin_attr_rci2.size = rci2_table_len;
	bin_attr_rci2.निजी = rci2_base;
	ret = sysfs_create_bin_file(tables_kobj, &bin_attr_rci2);
	अगर (ret != 0) अणु
		pr_debug("RCI2 table - rci2 sysfs bin file creation failed\n");
		kobject_del(tables_kobj);
		kobject_put(tables_kobj);
		जाओ err_unmap;
	पूर्ण

	वापस 0;

 err_unmap:
	memunmap(rci2_base);
 err:
	pr_debug("RCI2 table - sysfs initialization failed\n");
	वापस ret;
पूर्ण
late_initcall(efi_rci2_sysfs_init);
