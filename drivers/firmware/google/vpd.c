<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * vpd.c
 *
 * Driver क्रम exporting VPD content to sysfs.
 *
 * Copyright 2017 Google Inc.
 */

#समावेश <linux/प्रकार.स>
#समावेश <linux/init.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/kobject.h>
#समावेश <linux/list.h>
#समावेश <linux/module.h>
#समावेश <linux/of_address.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>
#समावेश <linux/sysfs.h>

#समावेश "coreboot_table.h"
#समावेश "vpd_decode.h"

#घोषणा CB_TAG_VPD      0x2c
#घोषणा VPD_CBMEM_MAGIC 0x43524f53

अटल काष्ठा kobject *vpd_kobj;

काष्ठा vpd_cbmem अणु
	u32 magic;
	u32 version;
	u32 ro_size;
	u32 rw_size;
	u8  blob[];
पूर्ण;

काष्ठा vpd_section अणु
	bool enabled;
	स्थिर अक्षर *name;
	अक्षर *raw_name;                /* the string name_raw */
	काष्ठा kobject *kobj;          /* vpd/name directory */
	अक्षर *baseaddr;
	काष्ठा bin_attribute bin_attr; /* vpd/name_raw bin_attribute */
	काष्ठा list_head attribs;      /* key/value in vpd_attrib_info list */
पूर्ण;

काष्ठा vpd_attrib_info अणु
	अक्षर *key;
	स्थिर अक्षर *value;
	काष्ठा bin_attribute bin_attr;
	काष्ठा list_head list;
पूर्ण;

अटल काष्ठा vpd_section ro_vpd;
अटल काष्ठा vpd_section rw_vpd;

अटल sमाप_प्रकार vpd_attrib_पढ़ो(काष्ठा file *filp, काष्ठा kobject *kobp,
			       काष्ठा bin_attribute *bin_attr, अक्षर *buf,
			       loff_t pos, माप_प्रकार count)
अणु
	काष्ठा vpd_attrib_info *info = bin_attr->निजी;

	वापस memory_पढ़ो_from_buffer(buf, count, &pos, info->value,
				       info->bin_attr.size);
पूर्ण

/*
 * vpd_section_check_key_name()
 *
 * The VPD specअगरication supports only [a-zA-Z0-9_]+ अक्षरacters in key names but
 * old firmware versions may have entries like "S/N" which are problematic when
 * exporting them as sysfs attributes. These keys present in old firmwares are
 * ignored.
 *
 * Returns VPD_OK क्रम a valid key name, VPD_FAIL otherwise.
 *
 * @key: The key name to check
 * @key_len: key name length
 */
अटल पूर्णांक vpd_section_check_key_name(स्थिर u8 *key, s32 key_len)
अणु
	पूर्णांक c;

	जबतक (key_len-- > 0) अणु
		c = *key++;

		अगर (!है_अक्षर_अंक(c) && c != '_')
			वापस VPD_FAIL;
	पूर्ण

	वापस VPD_OK;
पूर्ण

अटल पूर्णांक vpd_section_attrib_add(स्थिर u8 *key, u32 key_len,
				  स्थिर u8 *value, u32 value_len,
				  व्योम *arg)
अणु
	पूर्णांक ret;
	काष्ठा vpd_section *sec = arg;
	काष्ठा vpd_attrib_info *info;

	/*
	 * Return VPD_OK immediately to decode next entry अगर the current key
	 * name contains invalid अक्षरacters.
	 */
	अगर (vpd_section_check_key_name(key, key_len) != VPD_OK)
		वापस VPD_OK;

	info = kzalloc(माप(*info), GFP_KERNEL);
	अगर (!info)
		वापस -ENOMEM;

	info->key = kstrndup(key, key_len, GFP_KERNEL);
	अगर (!info->key) अणु
		ret = -ENOMEM;
		जाओ मुक्त_info;
	पूर्ण

	sysfs_bin_attr_init(&info->bin_attr);
	info->bin_attr.attr.name = info->key;
	info->bin_attr.attr.mode = 0444;
	info->bin_attr.size = value_len;
	info->bin_attr.पढ़ो = vpd_attrib_पढ़ो;
	info->bin_attr.निजी = info;

	info->value = value;

	INIT_LIST_HEAD(&info->list);

	ret = sysfs_create_bin_file(sec->kobj, &info->bin_attr);
	अगर (ret)
		जाओ मुक्त_info_key;

	list_add_tail(&info->list, &sec->attribs);
	वापस 0;

मुक्त_info_key:
	kमुक्त(info->key);
मुक्त_info:
	kमुक्त(info);

	वापस ret;
पूर्ण

अटल व्योम vpd_section_attrib_destroy(काष्ठा vpd_section *sec)
अणु
	काष्ठा vpd_attrib_info *info;
	काष्ठा vpd_attrib_info *temp;

	list_क्रम_each_entry_safe(info, temp, &sec->attribs, list) अणु
		sysfs_हटाओ_bin_file(sec->kobj, &info->bin_attr);
		kमुक्त(info->key);
		kमुक्त(info);
	पूर्ण
पूर्ण

अटल sमाप_प्रकार vpd_section_पढ़ो(काष्ठा file *filp, काष्ठा kobject *kobp,
				काष्ठा bin_attribute *bin_attr, अक्षर *buf,
				loff_t pos, माप_प्रकार count)
अणु
	काष्ठा vpd_section *sec = bin_attr->निजी;

	वापस memory_पढ़ो_from_buffer(buf, count, &pos, sec->baseaddr,
				       sec->bin_attr.size);
पूर्ण

अटल पूर्णांक vpd_section_create_attribs(काष्ठा vpd_section *sec)
अणु
	s32 consumed;
	पूर्णांक ret;

	consumed = 0;
	करो अणु
		ret = vpd_decode_string(sec->bin_attr.size, sec->baseaddr,
					&consumed, vpd_section_attrib_add, sec);
	पूर्ण जबतक (ret == VPD_OK);

	वापस 0;
पूर्ण

अटल पूर्णांक vpd_section_init(स्थिर अक्षर *name, काष्ठा vpd_section *sec,
			    phys_addr_t physaddr, माप_प्रकार size)
अणु
	पूर्णांक err;

	sec->baseaddr = memremap(physaddr, size, MEMREMAP_WB);
	अगर (!sec->baseaddr)
		वापस -ENOMEM;

	sec->name = name;

	/* We want to export the raw partition with name $अणुnameपूर्ण_raw */
	sec->raw_name = kaप्र_लिखो(GFP_KERNEL, "%s_raw", name);
	अगर (!sec->raw_name) अणु
		err = -ENOMEM;
		जाओ err_memunmap;
	पूर्ण

	sysfs_bin_attr_init(&sec->bin_attr);
	sec->bin_attr.attr.name = sec->raw_name;
	sec->bin_attr.attr.mode = 0444;
	sec->bin_attr.size = size;
	sec->bin_attr.पढ़ो = vpd_section_पढ़ो;
	sec->bin_attr.निजी = sec;

	err = sysfs_create_bin_file(vpd_kobj, &sec->bin_attr);
	अगर (err)
		जाओ err_मुक्त_raw_name;

	sec->kobj = kobject_create_and_add(name, vpd_kobj);
	अगर (!sec->kobj) अणु
		err = -EINVAL;
		जाओ err_sysfs_हटाओ;
	पूर्ण

	INIT_LIST_HEAD(&sec->attribs);
	vpd_section_create_attribs(sec);

	sec->enabled = true;

	वापस 0;

err_sysfs_हटाओ:
	sysfs_हटाओ_bin_file(vpd_kobj, &sec->bin_attr);
err_मुक्त_raw_name:
	kमुक्त(sec->raw_name);
err_memunmap:
	memunmap(sec->baseaddr);
	वापस err;
पूर्ण

अटल पूर्णांक vpd_section_destroy(काष्ठा vpd_section *sec)
अणु
	अगर (sec->enabled) अणु
		vpd_section_attrib_destroy(sec);
		kobject_put(sec->kobj);
		sysfs_हटाओ_bin_file(vpd_kobj, &sec->bin_attr);
		kमुक्त(sec->raw_name);
		memunmap(sec->baseaddr);
		sec->enabled = false;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक vpd_sections_init(phys_addr_t physaddr)
अणु
	काष्ठा vpd_cbmem *temp;
	काष्ठा vpd_cbmem header;
	पूर्णांक ret = 0;

	temp = memremap(physaddr, माप(काष्ठा vpd_cbmem), MEMREMAP_WB);
	अगर (!temp)
		वापस -ENOMEM;

	स_नकल(&header, temp, माप(काष्ठा vpd_cbmem));
	memunmap(temp);

	अगर (header.magic != VPD_CBMEM_MAGIC)
		वापस -ENODEV;

	अगर (header.ro_size) अणु
		ret = vpd_section_init("ro", &ro_vpd,
				       physaddr + माप(काष्ठा vpd_cbmem),
				       header.ro_size);
		अगर (ret)
			वापस ret;
	पूर्ण

	अगर (header.rw_size) अणु
		ret = vpd_section_init("rw", &rw_vpd,
				       physaddr + माप(काष्ठा vpd_cbmem) +
				       header.ro_size, header.rw_size);
		अगर (ret) अणु
			vpd_section_destroy(&ro_vpd);
			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक vpd_probe(काष्ठा coreboot_device *dev)
अणु
	पूर्णांक ret;

	vpd_kobj = kobject_create_and_add("vpd", firmware_kobj);
	अगर (!vpd_kobj)
		वापस -ENOMEM;

	ret = vpd_sections_init(dev->cbmem_ref.cbmem_addr);
	अगर (ret) अणु
		kobject_put(vpd_kobj);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम vpd_हटाओ(काष्ठा coreboot_device *dev)
अणु
	vpd_section_destroy(&ro_vpd);
	vpd_section_destroy(&rw_vpd);

	kobject_put(vpd_kobj);
पूर्ण

अटल काष्ठा coreboot_driver vpd_driver = अणु
	.probe = vpd_probe,
	.हटाओ = vpd_हटाओ,
	.drv = अणु
		.name = "vpd",
	पूर्ण,
	.tag = CB_TAG_VPD,
पूर्ण;
module_coreboot_driver(vpd_driver);

MODULE_AUTHOR("Google, Inc.");
MODULE_LICENSE("GPL");
