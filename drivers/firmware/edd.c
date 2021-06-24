<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * linux/drivers/firmware/edd.c
 *  Copyright (C) 2002, 2003, 2004 Dell Inc.
 *  by Matt Domsch <Matt_Domsch@dell.com>
 *  disk signature by Matt Domsch, Andrew Wilks, and Sandeep K. Shandilya
 *  legacy CHS by Patrick J. LoPresti <patl@users.sourceक्रमge.net>
 *
 * BIOS Enhanced Disk Drive Services (EDD)
 * conक्रमmant to T13 Committee www.t13.org
 *   projects 1572D, 1484D, 1386D, 1226DT
 *
 * This code takes inक्रमmation provided by BIOS EDD calls
 * fn41 - Check Extensions Present and
 * fn48 - Get Device Parameters with EDD extensions
 * made in setup.S, copied to safe काष्ठाures in setup.c,
 * and presents it in sysfs.
 *
 * Please see http://linux.dell.com/edd/results.hपंचांगl क्रम
 * the list of BIOSs which have been reported to implement EDD.
 */

#समावेश <linux/module.h>
#समावेश <linux/माला.स>
#समावेश <linux/types.h>
#समावेश <linux/init.h>
#समावेश <linux/स्थिति.स>
#समावेश <linux/err.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/slab.h>
#समावेश <linux/सीमा.स>
#समावेश <linux/device.h>
#समावेश <linux/pci.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/edd.h>

#घोषणा EDD_VERSION "0.16"
#घोषणा EDD_DATE    "2004-Jun-25"

MODULE_AUTHOR("Matt Domsch <Matt_Domsch@Dell.com>");
MODULE_DESCRIPTION("sysfs interface to BIOS EDD information");
MODULE_LICENSE("GPL");
MODULE_VERSION(EDD_VERSION);

#घोषणा left (PAGE_SIZE - (p - buf) - 1)

काष्ठा edd_device अणु
	अचिन्हित पूर्णांक index;
	अचिन्हित पूर्णांक mbr_signature;
	काष्ठा edd_info *info;
	काष्ठा kobject kobj;
पूर्ण;

काष्ठा edd_attribute अणु
	काष्ठा attribute attr;
	sमाप_प्रकार(*show) (काष्ठा edd_device * edev, अक्षर *buf);
	पूर्णांक (*test) (काष्ठा edd_device * edev);
पूर्ण;

/* क्रमward declarations */
अटल पूर्णांक edd_dev_is_type(काष्ठा edd_device *edev, स्थिर अक्षर *type);
अटल काष्ठा pci_dev *edd_get_pci_dev(काष्ठा edd_device *edev);

अटल काष्ठा edd_device *edd_devices[EDD_MBR_SIG_MAX];

#घोषणा EDD_DEVICE_ATTR(_name,_mode,_show,_test) \
काष्ठा edd_attribute edd_attr_##_name = अणु 	\
	.attr = अणु.name = __stringअगरy(_name), .mode = _mode पूर्ण,	\
	.show	= _show,				\
	.test	= _test,				\
पूर्ण;

अटल पूर्णांक
edd_has_mbr_signature(काष्ठा edd_device *edev)
अणु
	वापस edev->index < min_t(अचिन्हित अक्षर, edd.mbr_signature_nr, EDD_MBR_SIG_MAX);
पूर्ण

अटल पूर्णांक
edd_has_edd_info(काष्ठा edd_device *edev)
अणु
	वापस edev->index < min_t(अचिन्हित अक्षर, edd.edd_info_nr, EDDMAXNR);
पूर्ण

अटल अंतरभूत काष्ठा edd_info *
edd_dev_get_info(काष्ठा edd_device *edev)
अणु
	वापस edev->info;
पूर्ण

अटल अंतरभूत व्योम
edd_dev_set_info(काष्ठा edd_device *edev, पूर्णांक i)
अणु
	edev->index = i;
	अगर (edd_has_mbr_signature(edev))
		edev->mbr_signature = edd.mbr_signature[i];
	अगर (edd_has_edd_info(edev))
		edev->info = &edd.edd_info[i];
पूर्ण

#घोषणा to_edd_attr(_attr) container_of(_attr,काष्ठा edd_attribute,attr)
#घोषणा to_edd_device(obj) container_of(obj,काष्ठा edd_device,kobj)

अटल sमाप_प्रकार
edd_attr_show(काष्ठा kobject * kobj, काष्ठा attribute *attr, अक्षर *buf)
अणु
	काष्ठा edd_device *dev = to_edd_device(kobj);
	काष्ठा edd_attribute *edd_attr = to_edd_attr(attr);
	sमाप_प्रकार ret = -EIO;

	अगर (edd_attr->show)
		ret = edd_attr->show(dev, buf);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा sysfs_ops edd_attr_ops = अणु
	.show = edd_attr_show,
पूर्ण;

अटल sमाप_प्रकार
edd_show_host_bus(काष्ठा edd_device *edev, अक्षर *buf)
अणु
	काष्ठा edd_info *info;
	अक्षर *p = buf;
	पूर्णांक i;

	अगर (!edev)
		वापस -EINVAL;
	info = edd_dev_get_info(edev);
	अगर (!info || !buf)
		वापस -EINVAL;

	क्रम (i = 0; i < 4; i++) अणु
		अगर (है_छाप(info->params.host_bus_type[i])) अणु
			p += scnम_लिखो(p, left, "%c", info->params.host_bus_type[i]);
		पूर्ण अन्यथा अणु
			p += scnम_लिखो(p, left, " ");
		पूर्ण
	पूर्ण

	अगर (!म_भेदन(info->params.host_bus_type, "ISA", 3)) अणु
		p += scnम_लिखो(p, left, "\tbase_address: %x\n",
			     info->params.पूर्णांकerface_path.isa.base_address);
	पूर्ण अन्यथा अगर (!म_भेदन(info->params.host_bus_type, "PCIX", 4) ||
		   !म_भेदन(info->params.host_bus_type, "PCI", 3) ||
		   !म_भेदन(info->params.host_bus_type, "XPRS", 4)) अणु
		p += scnम_लिखो(p, left,
			     "\t%02x:%02x.%d  channel: %u\n",
			     info->params.पूर्णांकerface_path.pci.bus,
			     info->params.पूर्णांकerface_path.pci.slot,
			     info->params.पूर्णांकerface_path.pci.function,
			     info->params.पूर्णांकerface_path.pci.channel);
	पूर्ण अन्यथा अगर (!म_भेदन(info->params.host_bus_type, "IBND", 4) ||
		   !म_भेदन(info->params.host_bus_type, "HTPT", 4)) अणु
		p += scnम_लिखो(p, left,
			     "\tTBD: %llx\n",
			     info->params.पूर्णांकerface_path.ibnd.reserved);

	पूर्ण अन्यथा अणु
		p += scnम_लिखो(p, left, "\tunknown: %llx\n",
			     info->params.पूर्णांकerface_path.unknown.reserved);
	पूर्ण
	वापस (p - buf);
पूर्ण

अटल sमाप_प्रकार
edd_show_पूर्णांकerface(काष्ठा edd_device *edev, अक्षर *buf)
अणु
	काष्ठा edd_info *info;
	अक्षर *p = buf;
	पूर्णांक i;

	अगर (!edev)
		वापस -EINVAL;
	info = edd_dev_get_info(edev);
	अगर (!info || !buf)
		वापस -EINVAL;

	क्रम (i = 0; i < 8; i++) अणु
		अगर (है_छाप(info->params.पूर्णांकerface_type[i])) अणु
			p += scnम_लिखो(p, left, "%c", info->params.पूर्णांकerface_type[i]);
		पूर्ण अन्यथा अणु
			p += scnम_लिखो(p, left, " ");
		पूर्ण
	पूर्ण
	अगर (!म_भेदन(info->params.पूर्णांकerface_type, "ATAPI", 5)) अणु
		p += scnम_लिखो(p, left, "\tdevice: %u  lun: %u\n",
			     info->params.device_path.atapi.device,
			     info->params.device_path.atapi.lun);
	पूर्ण अन्यथा अगर (!म_भेदन(info->params.पूर्णांकerface_type, "ATA", 3)) अणु
		p += scnम_लिखो(p, left, "\tdevice: %u\n",
			     info->params.device_path.ata.device);
	पूर्ण अन्यथा अगर (!म_भेदन(info->params.पूर्णांकerface_type, "SCSI", 4)) अणु
		p += scnम_लिखो(p, left, "\tid: %u  lun: %llu\n",
			     info->params.device_path.scsi.id,
			     info->params.device_path.scsi.lun);
	पूर्ण अन्यथा अगर (!म_भेदन(info->params.पूर्णांकerface_type, "USB", 3)) अणु
		p += scnम_लिखो(p, left, "\tserial_number: %llx\n",
			     info->params.device_path.usb.serial_number);
	पूर्ण अन्यथा अगर (!म_भेदन(info->params.पूर्णांकerface_type, "1394", 4)) अणु
		p += scnम_लिखो(p, left, "\teui: %llx\n",
			     info->params.device_path.i1394.eui);
	पूर्ण अन्यथा अगर (!म_भेदन(info->params.पूर्णांकerface_type, "FIBRE", 5)) अणु
		p += scnम_लिखो(p, left, "\twwid: %llx lun: %llx\n",
			     info->params.device_path.fibre.wwid,
			     info->params.device_path.fibre.lun);
	पूर्ण अन्यथा अगर (!म_भेदन(info->params.पूर्णांकerface_type, "I2O", 3)) अणु
		p += scnम_लिखो(p, left, "\tidentity_tag: %llx\n",
			     info->params.device_path.i2o.identity_tag);
	पूर्ण अन्यथा अगर (!म_भेदन(info->params.पूर्णांकerface_type, "RAID", 4)) अणु
		p += scnम_लिखो(p, left, "\tidentity_tag: %x\n",
			     info->params.device_path.raid.array_number);
	पूर्ण अन्यथा अगर (!म_भेदन(info->params.पूर्णांकerface_type, "SATA", 4)) अणु
		p += scnम_लिखो(p, left, "\tdevice: %u\n",
			     info->params.device_path.sata.device);
	पूर्ण अन्यथा अणु
		p += scnम_लिखो(p, left, "\tunknown: %llx %llx\n",
			     info->params.device_path.unknown.reserved1,
			     info->params.device_path.unknown.reserved2);
	पूर्ण

	वापस (p - buf);
पूर्ण

/**
 * edd_show_raw_data() - copies raw data to buffer क्रम userspace to parse
 * @edev: target edd_device
 * @buf: output buffer
 *
 * Returns: number of bytes written, or -EINVAL on failure
 */
अटल sमाप_प्रकार
edd_show_raw_data(काष्ठा edd_device *edev, अक्षर *buf)
अणु
	काष्ठा edd_info *info;
	sमाप_प्रकार len = माप (info->params);
	अगर (!edev)
		वापस -EINVAL;
	info = edd_dev_get_info(edev);
	अगर (!info || !buf)
		वापस -EINVAL;

	अगर (!(info->params.key == 0xBEDD || info->params.key == 0xDDBE))
		len = info->params.length;

	/* In हाल of buggy BIOSs */
	अगर (len > (माप(info->params)))
		len = माप(info->params);

	स_नकल(buf, &info->params, len);
	वापस len;
पूर्ण

अटल sमाप_प्रकार
edd_show_version(काष्ठा edd_device *edev, अक्षर *buf)
अणु
	काष्ठा edd_info *info;
	अक्षर *p = buf;
	अगर (!edev)
		वापस -EINVAL;
	info = edd_dev_get_info(edev);
	अगर (!info || !buf)
		वापस -EINVAL;

	p += scnम_लिखो(p, left, "0x%02x\n", info->version);
	वापस (p - buf);
पूर्ण

अटल sमाप_प्रकार
edd_show_mbr_signature(काष्ठा edd_device *edev, अक्षर *buf)
अणु
	अक्षर *p = buf;
	p += scnम_लिखो(p, left, "0x%08x\n", edev->mbr_signature);
	वापस (p - buf);
पूर्ण

अटल sमाप_प्रकार
edd_show_extensions(काष्ठा edd_device *edev, अक्षर *buf)
अणु
	काष्ठा edd_info *info;
	अक्षर *p = buf;
	अगर (!edev)
		वापस -EINVAL;
	info = edd_dev_get_info(edev);
	अगर (!info || !buf)
		वापस -EINVAL;

	अगर (info->पूर्णांकerface_support & EDD_EXT_FIXED_DISK_ACCESS) अणु
		p += scnम_लिखो(p, left, "Fixed disk access\n");
	पूर्ण
	अगर (info->पूर्णांकerface_support & EDD_EXT_DEVICE_LOCKING_AND_EJECTING) अणु
		p += scnम_लिखो(p, left, "Device locking and ejecting\n");
	पूर्ण
	अगर (info->पूर्णांकerface_support & EDD_EXT_ENHANCED_DISK_DRIVE_SUPPORT) अणु
		p += scnम_लिखो(p, left, "Enhanced Disk Drive support\n");
	पूर्ण
	अगर (info->पूर्णांकerface_support & EDD_EXT_64BIT_EXTENSIONS) अणु
		p += scnम_लिखो(p, left, "64-bit extensions\n");
	पूर्ण
	वापस (p - buf);
पूर्ण

अटल sमाप_प्रकार
edd_show_info_flags(काष्ठा edd_device *edev, अक्षर *buf)
अणु
	काष्ठा edd_info *info;
	अक्षर *p = buf;
	अगर (!edev)
		वापस -EINVAL;
	info = edd_dev_get_info(edev);
	अगर (!info || !buf)
		वापस -EINVAL;

	अगर (info->params.info_flags & EDD_INFO_DMA_BOUNDARY_ERROR_TRANSPARENT)
		p += scnम_लिखो(p, left, "DMA boundary error transparent\n");
	अगर (info->params.info_flags & EDD_INFO_GEOMETRY_VALID)
		p += scnम_लिखो(p, left, "geometry valid\n");
	अगर (info->params.info_flags & EDD_INFO_REMOVABLE)
		p += scnम_लिखो(p, left, "removable\n");
	अगर (info->params.info_flags & EDD_INFO_WRITE_VERIFY)
		p += scnम_लिखो(p, left, "write verify\n");
	अगर (info->params.info_flags & EDD_INFO_MEDIA_CHANGE_NOTIFICATION)
		p += scnम_लिखो(p, left, "media change notification\n");
	अगर (info->params.info_flags & EDD_INFO_LOCKABLE)
		p += scnम_लिखो(p, left, "lockable\n");
	अगर (info->params.info_flags & EDD_INFO_NO_MEDIA_PRESENT)
		p += scnम_लिखो(p, left, "no media present\n");
	अगर (info->params.info_flags & EDD_INFO_USE_INT13_FN50)
		p += scnम_लिखो(p, left, "use int13 fn50\n");
	वापस (p - buf);
पूर्ण

अटल sमाप_प्रकार
edd_show_legacy_max_cylinder(काष्ठा edd_device *edev, अक्षर *buf)
अणु
	काष्ठा edd_info *info;
	अक्षर *p = buf;
	अगर (!edev)
		वापस -EINVAL;
	info = edd_dev_get_info(edev);
	अगर (!info || !buf)
		वापस -EINVAL;

	p += scnम_लिखो(p, left, "%u\n", info->legacy_max_cylinder);
	वापस (p - buf);
पूर्ण

अटल sमाप_प्रकार
edd_show_legacy_max_head(काष्ठा edd_device *edev, अक्षर *buf)
अणु
	काष्ठा edd_info *info;
	अक्षर *p = buf;
	अगर (!edev)
		वापस -EINVAL;
	info = edd_dev_get_info(edev);
	अगर (!info || !buf)
		वापस -EINVAL;

	p += scnम_लिखो(p, left, "%u\n", info->legacy_max_head);
	वापस (p - buf);
पूर्ण

अटल sमाप_प्रकार
edd_show_legacy_sectors_per_track(काष्ठा edd_device *edev, अक्षर *buf)
अणु
	काष्ठा edd_info *info;
	अक्षर *p = buf;
	अगर (!edev)
		वापस -EINVAL;
	info = edd_dev_get_info(edev);
	अगर (!info || !buf)
		वापस -EINVAL;

	p += scnम_लिखो(p, left, "%u\n", info->legacy_sectors_per_track);
	वापस (p - buf);
पूर्ण

अटल sमाप_प्रकार
edd_show_शेष_cylinders(काष्ठा edd_device *edev, अक्षर *buf)
अणु
	काष्ठा edd_info *info;
	अक्षर *p = buf;
	अगर (!edev)
		वापस -EINVAL;
	info = edd_dev_get_info(edev);
	अगर (!info || !buf)
		वापस -EINVAL;

	p += scnम_लिखो(p, left, "%u\n", info->params.num_शेष_cylinders);
	वापस (p - buf);
पूर्ण

अटल sमाप_प्रकार
edd_show_शेष_heads(काष्ठा edd_device *edev, अक्षर *buf)
अणु
	काष्ठा edd_info *info;
	अक्षर *p = buf;
	अगर (!edev)
		वापस -EINVAL;
	info = edd_dev_get_info(edev);
	अगर (!info || !buf)
		वापस -EINVAL;

	p += scnम_लिखो(p, left, "%u\n", info->params.num_शेष_heads);
	वापस (p - buf);
पूर्ण

अटल sमाप_प्रकार
edd_show_शेष_sectors_per_track(काष्ठा edd_device *edev, अक्षर *buf)
अणु
	काष्ठा edd_info *info;
	अक्षर *p = buf;
	अगर (!edev)
		वापस -EINVAL;
	info = edd_dev_get_info(edev);
	अगर (!info || !buf)
		वापस -EINVAL;

	p += scnम_लिखो(p, left, "%u\n", info->params.sectors_per_track);
	वापस (p - buf);
पूर्ण

अटल sमाप_प्रकार
edd_show_sectors(काष्ठा edd_device *edev, अक्षर *buf)
अणु
	काष्ठा edd_info *info;
	अक्षर *p = buf;
	अगर (!edev)
		वापस -EINVAL;
	info = edd_dev_get_info(edev);
	अगर (!info || !buf)
		वापस -EINVAL;

	p += scnम_लिखो(p, left, "%llu\n", info->params.number_of_sectors);
	वापस (p - buf);
पूर्ण


/*
 * Some device instances may not have all the above attributes,
 * or the attribute values may be meaningless (i.e. अगर
 * the device is < EDD 3.0, it won't have host_bus and पूर्णांकerface
 * inक्रमmation), so करोn't bother making files क्रम them.  Likewise
 * अगर the शेष_अणुcylinders,heads,sectors_per_trackपूर्ण values
 * are zero, the BIOS करोesn't provide sane values, don't bother
 * creating files क्रम them either.
 */

अटल पूर्णांक
edd_has_legacy_max_cylinder(काष्ठा edd_device *edev)
अणु
	काष्ठा edd_info *info;
	अगर (!edev)
		वापस 0;
	info = edd_dev_get_info(edev);
	अगर (!info)
		वापस 0;
	वापस info->legacy_max_cylinder > 0;
पूर्ण

अटल पूर्णांक
edd_has_legacy_max_head(काष्ठा edd_device *edev)
अणु
	काष्ठा edd_info *info;
	अगर (!edev)
		वापस 0;
	info = edd_dev_get_info(edev);
	अगर (!info)
		वापस 0;
	वापस info->legacy_max_head > 0;
पूर्ण

अटल पूर्णांक
edd_has_legacy_sectors_per_track(काष्ठा edd_device *edev)
अणु
	काष्ठा edd_info *info;
	अगर (!edev)
		वापस 0;
	info = edd_dev_get_info(edev);
	अगर (!info)
		वापस 0;
	वापस info->legacy_sectors_per_track > 0;
पूर्ण

अटल पूर्णांक
edd_has_शेष_cylinders(काष्ठा edd_device *edev)
अणु
	काष्ठा edd_info *info;
	अगर (!edev)
		वापस 0;
	info = edd_dev_get_info(edev);
	अगर (!info)
		वापस 0;
	वापस info->params.num_शेष_cylinders > 0;
पूर्ण

अटल पूर्णांक
edd_has_शेष_heads(काष्ठा edd_device *edev)
अणु
	काष्ठा edd_info *info;
	अगर (!edev)
		वापस 0;
	info = edd_dev_get_info(edev);
	अगर (!info)
		वापस 0;
	वापस info->params.num_शेष_heads > 0;
पूर्ण

अटल पूर्णांक
edd_has_शेष_sectors_per_track(काष्ठा edd_device *edev)
अणु
	काष्ठा edd_info *info;
	अगर (!edev)
		वापस 0;
	info = edd_dev_get_info(edev);
	अगर (!info)
		वापस 0;
	वापस info->params.sectors_per_track > 0;
पूर्ण

अटल पूर्णांक
edd_has_edd30(काष्ठा edd_device *edev)
अणु
	काष्ठा edd_info *info;
	पूर्णांक i;
	u8 csum = 0;

	अगर (!edev)
		वापस 0;
	info = edd_dev_get_info(edev);
	अगर (!info)
		वापस 0;

	अगर (!(info->params.key == 0xBEDD || info->params.key == 0xDDBE)) अणु
		वापस 0;
	पूर्ण


	/* We support only T13 spec */
	अगर (info->params.device_path_info_length != 44)
		वापस 0;

	क्रम (i = 30; i < info->params.device_path_info_length + 30; i++)
		csum += *(((u8 *)&info->params) + i);

	अगर (csum)
		वापस 0;

	वापस 1;
पूर्ण


अटल EDD_DEVICE_ATTR(raw_data, 0444, edd_show_raw_data, edd_has_edd_info);
अटल EDD_DEVICE_ATTR(version, 0444, edd_show_version, edd_has_edd_info);
अटल EDD_DEVICE_ATTR(extensions, 0444, edd_show_extensions, edd_has_edd_info);
अटल EDD_DEVICE_ATTR(info_flags, 0444, edd_show_info_flags, edd_has_edd_info);
अटल EDD_DEVICE_ATTR(sectors, 0444, edd_show_sectors, edd_has_edd_info);
अटल EDD_DEVICE_ATTR(legacy_max_cylinder, 0444,
                       edd_show_legacy_max_cylinder,
		       edd_has_legacy_max_cylinder);
अटल EDD_DEVICE_ATTR(legacy_max_head, 0444, edd_show_legacy_max_head,
		       edd_has_legacy_max_head);
अटल EDD_DEVICE_ATTR(legacy_sectors_per_track, 0444,
                       edd_show_legacy_sectors_per_track,
		       edd_has_legacy_sectors_per_track);
अटल EDD_DEVICE_ATTR(शेष_cylinders, 0444, edd_show_शेष_cylinders,
		       edd_has_शेष_cylinders);
अटल EDD_DEVICE_ATTR(शेष_heads, 0444, edd_show_शेष_heads,
		       edd_has_शेष_heads);
अटल EDD_DEVICE_ATTR(शेष_sectors_per_track, 0444,
		       edd_show_शेष_sectors_per_track,
		       edd_has_शेष_sectors_per_track);
अटल EDD_DEVICE_ATTR(पूर्णांकerface, 0444, edd_show_पूर्णांकerface, edd_has_edd30);
अटल EDD_DEVICE_ATTR(host_bus, 0444, edd_show_host_bus, edd_has_edd30);
अटल EDD_DEVICE_ATTR(mbr_signature, 0444, edd_show_mbr_signature, edd_has_mbr_signature);


/* These are शेष attributes that are added क्रम every edd
 * device discovered.  There are none.
 */
अटल काष्ठा attribute * def_attrs[] = अणु
	शून्य,
पूर्ण;

/* These attributes are conditional and only added क्रम some devices. */
अटल काष्ठा edd_attribute * edd_attrs[] = अणु
	&edd_attr_raw_data,
	&edd_attr_version,
	&edd_attr_extensions,
	&edd_attr_info_flags,
	&edd_attr_sectors,
	&edd_attr_legacy_max_cylinder,
	&edd_attr_legacy_max_head,
	&edd_attr_legacy_sectors_per_track,
	&edd_attr_शेष_cylinders,
	&edd_attr_शेष_heads,
	&edd_attr_शेष_sectors_per_track,
	&edd_attr_पूर्णांकerface,
	&edd_attr_host_bus,
	&edd_attr_mbr_signature,
	शून्य,
पूर्ण;

/**
 *	edd_release - मुक्त edd काष्ठाure
 *	@kobj:	kobject of edd काष्ठाure
 *
 *	This is called when the refcount of the edd काष्ठाure
 *	reaches 0. This should happen right after we unरेजिस्टर,
 *	but just in हाल, we use the release callback anyway.
 */

अटल व्योम edd_release(काष्ठा kobject * kobj)
अणु
	काष्ठा edd_device * dev = to_edd_device(kobj);
	kमुक्त(dev);
पूर्ण

अटल काष्ठा kobj_type edd_ktype = अणु
	.release	= edd_release,
	.sysfs_ops	= &edd_attr_ops,
	.शेष_attrs	= def_attrs,
पूर्ण;

अटल काष्ठा kset *edd_kset;


/**
 * edd_dev_is_type() - is this EDD device a 'type' device?
 * @edev: target edd_device
 * @type: a host bus or पूर्णांकerface identअगरier string per the EDD spec
 *
 * Returns 1 (TRUE) अगर it is a 'type' device, 0 otherwise.
 */
अटल पूर्णांक
edd_dev_is_type(काष्ठा edd_device *edev, स्थिर अक्षर *type)
अणु
	काष्ठा edd_info *info;
	अगर (!edev)
		वापस 0;
	info = edd_dev_get_info(edev);

	अगर (type && info) अणु
		अगर (!म_भेदन(info->params.host_bus_type, type, म_माप(type)) ||
		    !म_भेदन(info->params.पूर्णांकerface_type, type, म_माप(type)))
			वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

/**
 * edd_get_pci_dev() - finds pci_dev that matches edev
 * @edev: edd_device
 *
 * Returns pci_dev अगर found, or शून्य
 */
अटल काष्ठा pci_dev *
edd_get_pci_dev(काष्ठा edd_device *edev)
अणु
	काष्ठा edd_info *info = edd_dev_get_info(edev);

	अगर (edd_dev_is_type(edev, "PCI") || edd_dev_is_type(edev, "XPRS")) अणु
		वापस pci_get_करोमुख्य_bus_and_slot(0,
				info->params.पूर्णांकerface_path.pci.bus,
				PCI_DEVFN(info->params.पूर्णांकerface_path.pci.slot,
				info->params.पूर्णांकerface_path.pci.function));
	पूर्ण
	वापस शून्य;
पूर्ण

अटल पूर्णांक
edd_create_symlink_to_pcidev(काष्ठा edd_device *edev)
अणु

	काष्ठा pci_dev *pci_dev = edd_get_pci_dev(edev);
	पूर्णांक ret;
	अगर (!pci_dev)
		वापस 1;
	ret = sysfs_create_link(&edev->kobj,&pci_dev->dev.kobj,"pci_dev");
	pci_dev_put(pci_dev);
	वापस ret;
पूर्ण

अटल अंतरभूत व्योम
edd_device_unरेजिस्टर(काष्ठा edd_device *edev)
अणु
	kobject_put(&edev->kobj);
पूर्ण

अटल व्योम edd_populate_dir(काष्ठा edd_device * edev)
अणु
	काष्ठा edd_attribute * attr;
	पूर्णांक error = 0;
	पूर्णांक i;

	क्रम (i = 0; (attr = edd_attrs[i]) && !error; i++) अणु
		अगर (!attr->test ||
		    (attr->test && attr->test(edev)))
			error = sysfs_create_file(&edev->kobj,&attr->attr);
	पूर्ण

	अगर (!error) अणु
		edd_create_symlink_to_pcidev(edev);
	पूर्ण
पूर्ण

अटल पूर्णांक
edd_device_रेजिस्टर(काष्ठा edd_device *edev, पूर्णांक i)
अणु
	पूर्णांक error;

	अगर (!edev)
		वापस 1;
	edd_dev_set_info(edev, i);
	edev->kobj.kset = edd_kset;
	error = kobject_init_and_add(&edev->kobj, &edd_ktype, शून्य,
				     "int13_dev%02x", 0x80 + i);
	अगर (!error) अणु
		edd_populate_dir(edev);
		kobject_uevent(&edev->kobj, KOBJ_ADD);
	पूर्ण
	वापस error;
पूर्ण

अटल अंतरभूत पूर्णांक edd_num_devices(व्योम)
अणु
	वापस max_t(अचिन्हित अक्षर,
		     min_t(अचिन्हित अक्षर, EDD_MBR_SIG_MAX, edd.mbr_signature_nr),
		     min_t(अचिन्हित अक्षर, EDDMAXNR, edd.edd_info_nr));
पूर्ण

/**
 * edd_init() - creates sysfs tree of EDD data
 */
अटल पूर्णांक __init
edd_init(व्योम)
अणु
	पूर्णांक i;
	पूर्णांक rc=0;
	काष्ठा edd_device *edev;

	अगर (!edd_num_devices())
		वापस -ENODEV;

	prपूर्णांकk(KERN_INFO "BIOS EDD facility v%s %s, %d devices found\n",
	       EDD_VERSION, EDD_DATE, edd_num_devices());

	edd_kset = kset_create_and_add("edd", शून्य, firmware_kobj);
	अगर (!edd_kset)
		वापस -ENOMEM;

	क्रम (i = 0; i < edd_num_devices(); i++) अणु
		edev = kzalloc(माप (*edev), GFP_KERNEL);
		अगर (!edev) अणु
			rc = -ENOMEM;
			जाओ out;
		पूर्ण

		rc = edd_device_रेजिस्टर(edev, i);
		अगर (rc) अणु
			kमुक्त(edev);
			जाओ out;
		पूर्ण
		edd_devices[i] = edev;
	पूर्ण

	वापस 0;

out:
	जबतक (--i >= 0)
		edd_device_unरेजिस्टर(edd_devices[i]);
	kset_unरेजिस्टर(edd_kset);
	वापस rc;
पूर्ण

अटल व्योम __निकास
edd_निकास(व्योम)
अणु
	पूर्णांक i;
	काष्ठा edd_device *edev;

	क्रम (i = 0; i < edd_num_devices(); i++) अणु
		अगर ((edev = edd_devices[i]))
			edd_device_unरेजिस्टर(edev);
	पूर्ण
	kset_unरेजिस्टर(edd_kset);
पूर्ण

late_initcall(edd_init);
module_निकास(edd_निकास);
