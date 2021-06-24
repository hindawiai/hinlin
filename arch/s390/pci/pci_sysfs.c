<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright IBM Corp. 2012
 *
 * Author(s):
 *   Jan Glauber <jang@linux.vnet.ibm.com>
 */

#घोषणा KMSG_COMPONENT "zpci"
#घोषणा pr_fmt(fmt) KMSG_COMPONENT ": " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/स्थिति.स>
#समावेश <linux/pci.h>

#समावेश "../../../drivers/pci/pci.h"

#समावेश <यंत्र/sclp.h>

#घोषणा zpci_attr(name, fmt, member)					\
अटल sमाप_प्रकार name##_show(काष्ठा device *dev,				\
			   काष्ठा device_attribute *attr, अक्षर *buf)	\
अणु									\
	काष्ठा zpci_dev *zdev = to_zpci(to_pci_dev(dev));		\
									\
	वापस प्र_लिखो(buf, fmt, zdev->member);				\
पूर्ण									\
अटल DEVICE_ATTR_RO(name)

zpci_attr(function_id, "0x%08x\n", fid);
zpci_attr(function_handle, "0x%08x\n", fh);
zpci_attr(pchid, "0x%04x\n", pchid);
zpci_attr(pfgid, "0x%02x\n", pfgid);
zpci_attr(vfn, "0x%04x\n", vfn);
zpci_attr(pft, "0x%02x\n", pft);
zpci_attr(port, "%d\n", port);
zpci_attr(uid, "0x%x\n", uid);
zpci_attr(segment0, "0x%02x\n", pfip[0]);
zpci_attr(segment1, "0x%02x\n", pfip[1]);
zpci_attr(segment2, "0x%02x\n", pfip[2]);
zpci_attr(segment3, "0x%02x\n", pfip[3]);

अटल sमाप_प्रकार mio_enabled_show(काष्ठा device *dev,
				काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा zpci_dev *zdev = to_zpci(to_pci_dev(dev));

	वापस प्र_लिखो(buf, zpci_use_mio(zdev) ? "1\n" : "0\n");
पूर्ण
अटल DEVICE_ATTR_RO(mio_enabled);

अटल sमाप_प्रकार recover_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
			     स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा kernfs_node *kn;
	काष्ठा pci_dev *pdev = to_pci_dev(dev);
	काष्ठा zpci_dev *zdev = to_zpci(pdev);
	पूर्णांक ret = 0;

	/* Can't use device_हटाओ_self() here as that would lead us to lock
	 * the pci_rescan_हटाओ_lock जबतक holding the device' kernfs lock.
	 * This would create a possible deadlock with disable_slot() which is
	 * not directly रक्षित by the device' kernfs lock but takes it
	 * during the device removal which happens under
	 * pci_rescan_हटाओ_lock.
	 *
	 * This is analogous to sdev_store_delete() in
	 * drivers/scsi/scsi_sysfs.c
	 */
	kn = sysfs_अवरोध_active_protection(&dev->kobj, &attr->attr);
	WARN_ON_ONCE(!kn);
	/* device_हटाओ_file() serializes concurrent calls ignoring all but
	 * the first
	 */
	device_हटाओ_file(dev, attr);

	/* A concurrent call to recover_store() may slip between
	 * sysfs_अवरोध_active_protection() and the sysfs file removal.
	 * Once it unblocks from pci_lock_rescan_हटाओ() the original pdev
	 * will alपढ़ोy be हटाओd.
	 */
	pci_lock_rescan_हटाओ();
	अगर (pci_dev_is_added(pdev)) अणु
		pci_stop_and_हटाओ_bus_device(pdev);
		ret = zpci_disable_device(zdev);
		अगर (ret)
			जाओ out;

		ret = zpci_enable_device(zdev);
		अगर (ret)
			जाओ out;
		pci_rescan_bus(zdev->zbus->bus);
	पूर्ण
out:
	pci_unlock_rescan_हटाओ();
	अगर (kn)
		sysfs_unअवरोध_active_protection(kn);
	वापस ret ? ret : count;
पूर्ण
अटल DEVICE_ATTR_WO(recover);

अटल sमाप_प्रकार util_string_पढ़ो(काष्ठा file *filp, काष्ठा kobject *kobj,
				काष्ठा bin_attribute *attr, अक्षर *buf,
				loff_t off, माप_प्रकार count)
अणु
	काष्ठा device *dev = kobj_to_dev(kobj);
	काष्ठा pci_dev *pdev = to_pci_dev(dev);
	काष्ठा zpci_dev *zdev = to_zpci(pdev);

	वापस memory_पढ़ो_from_buffer(buf, count, &off, zdev->util_str,
				       माप(zdev->util_str));
पूर्ण
अटल BIN_ATTR_RO(util_string, CLP_UTIL_STR_LEN);

अटल sमाप_प्रकार report_error_ग_लिखो(काष्ठा file *filp, काष्ठा kobject *kobj,
				  काष्ठा bin_attribute *attr, अक्षर *buf,
				  loff_t off, माप_प्रकार count)
अणु
	काष्ठा zpci_report_error_header *report = (व्योम *) buf;
	काष्ठा device *dev = kobj_to_dev(kobj);
	काष्ठा pci_dev *pdev = to_pci_dev(dev);
	काष्ठा zpci_dev *zdev = to_zpci(pdev);
	पूर्णांक ret;

	अगर (off || (count < माप(*report)))
		वापस -EINVAL;

	ret = sclp_pci_report(report, zdev->fh, zdev->fid);

	वापस ret ? ret : count;
पूर्ण
अटल BIN_ATTR(report_error, S_IWUSR, शून्य, report_error_ग_लिखो, PAGE_SIZE);

अटल sमाप_प्रकार uid_is_unique_show(काष्ठा device *dev,
				  काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	वापस sysfs_emit(buf, "%d\n", zpci_unique_uid ? 1 : 0);
पूर्ण
अटल DEVICE_ATTR_RO(uid_is_unique);

#अगर_अघोषित CONFIG_DMI
/* analogous to smbios index */
अटल sमाप_प्रकार index_show(काष्ठा device *dev,
			  काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा zpci_dev *zdev = to_zpci(to_pci_dev(dev));
	u32 index = ~0;

	अगर (zpci_unique_uid)
		index = zdev->uid;

	वापस sysfs_emit(buf, "%u\n", index);
पूर्ण
अटल DEVICE_ATTR_RO(index);

अटल umode_t zpci_index_is_visible(काष्ठा kobject *kobj,
				     काष्ठा attribute *attr, पूर्णांक n)
अणु
	वापस zpci_unique_uid ? attr->mode : 0;
पूर्ण

अटल काष्ठा attribute *zpci_ident_attrs[] = अणु
	&dev_attr_index.attr,
	शून्य,
पूर्ण;

अटल काष्ठा attribute_group zpci_ident_attr_group = अणु
	.attrs = zpci_ident_attrs,
	.is_visible = zpci_index_is_visible,
पूर्ण;
#पूर्ण_अगर

अटल काष्ठा bin_attribute *zpci_bin_attrs[] = अणु
	&bin_attr_util_string,
	&bin_attr_report_error,
	शून्य,
पूर्ण;

अटल काष्ठा attribute *zpci_dev_attrs[] = अणु
	&dev_attr_function_id.attr,
	&dev_attr_function_handle.attr,
	&dev_attr_pchid.attr,
	&dev_attr_pfgid.attr,
	&dev_attr_pft.attr,
	&dev_attr_port.attr,
	&dev_attr_vfn.attr,
	&dev_attr_uid.attr,
	&dev_attr_recover.attr,
	&dev_attr_mio_enabled.attr,
	&dev_attr_uid_is_unique.attr,
	शून्य,
पूर्ण;

अटल काष्ठा attribute_group zpci_attr_group = अणु
	.attrs = zpci_dev_attrs,
	.bin_attrs = zpci_bin_attrs,
पूर्ण;

अटल काष्ठा attribute *pfip_attrs[] = अणु
	&dev_attr_segment0.attr,
	&dev_attr_segment1.attr,
	&dev_attr_segment2.attr,
	&dev_attr_segment3.attr,
	शून्य,
पूर्ण;
अटल काष्ठा attribute_group pfip_attr_group = अणु
	.name = "pfip",
	.attrs = pfip_attrs,
पूर्ण;

स्थिर काष्ठा attribute_group *zpci_attr_groups[] = अणु
	&zpci_attr_group,
	&pfip_attr_group,
#अगर_अघोषित CONFIG_DMI
	&zpci_ident_attr_group,
#पूर्ण_अगर
	शून्य,
पूर्ण;
