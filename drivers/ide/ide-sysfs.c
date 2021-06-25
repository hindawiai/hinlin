<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/kernel.h>
#समावेश <linux/ide.h>

अक्षर *ide_media_string(ide_drive_t *drive)
अणु
	चयन (drive->media) अणु
	हाल ide_disk:
		वापस "disk";
	हाल ide_cdrom:
		वापस "cdrom";
	हाल ide_tape:
		वापस "tape";
	हाल ide_floppy:
		वापस "floppy";
	हाल ide_optical:
		वापस "optical";
	शेष:
		वापस "UNKNOWN";
	पूर्ण
पूर्ण

अटल sमाप_प्रकार media_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			  अक्षर *buf)
अणु
	ide_drive_t *drive = to_ide_device(dev);
	वापस प्र_लिखो(buf, "%s\n", ide_media_string(drive));
पूर्ण
अटल DEVICE_ATTR_RO(media);

अटल sमाप_प्रकार drivename_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			      अक्षर *buf)
अणु
	ide_drive_t *drive = to_ide_device(dev);
	वापस प्र_लिखो(buf, "%s\n", drive->name);
पूर्ण
अटल DEVICE_ATTR_RO(drivename);

अटल sमाप_प्रकार modalias_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			     अक्षर *buf)
अणु
	ide_drive_t *drive = to_ide_device(dev);
	वापस प्र_लिखो(buf, "ide:m-%s\n", ide_media_string(drive));
पूर्ण
अटल DEVICE_ATTR_RO(modalias);

अटल sमाप_प्रकार model_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			  अक्षर *buf)
अणु
	ide_drive_t *drive = to_ide_device(dev);
	वापस प्र_लिखो(buf, "%s\n", (अक्षर *)&drive->id[ATA_ID_PROD]);
पूर्ण
अटल DEVICE_ATTR_RO(model);

अटल sमाप_प्रकार firmware_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			     अक्षर *buf)
अणु
	ide_drive_t *drive = to_ide_device(dev);
	वापस प्र_लिखो(buf, "%s\n", (अक्षर *)&drive->id[ATA_ID_FW_REV]);
पूर्ण
अटल DEVICE_ATTR_RO(firmware);

अटल sमाप_प्रकार serial_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			   अक्षर *buf)
अणु
	ide_drive_t *drive = to_ide_device(dev);
	वापस प्र_लिखो(buf, "%s\n", (अक्षर *)&drive->id[ATA_ID_SERNO]);
पूर्ण
अटल DEVICE_ATTR(serial, 0400, serial_show, शून्य);

अटल DEVICE_ATTR(unload_heads, 0644, ide_park_show, ide_park_store);

अटल काष्ठा attribute *ide_attrs[] = अणु
	&dev_attr_media.attr,
	&dev_attr_drivename.attr,
	&dev_attr_modalias.attr,
	&dev_attr_model.attr,
	&dev_attr_firmware.attr,
	&dev_attr_serial.attr,
	&dev_attr_unload_heads.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group ide_attr_group = अणु
	.attrs = ide_attrs,
पूर्ण;

स्थिर काष्ठा attribute_group *ide_dev_groups[] = अणु
	&ide_attr_group,
	शून्य,
पूर्ण;

अटल sमाप_प्रकार store_delete_devices(काष्ठा device *portdev,
				    काष्ठा device_attribute *attr,
				    स्थिर अक्षर *buf, माप_प्रकार n)
अणु
	ide_hwअगर_t *hwअगर = dev_get_drvdata(portdev);

	अगर (म_भेदन(buf, "1", n))
		वापस -EINVAL;

	ide_port_unरेजिस्टर_devices(hwअगर);

	वापस n;
पूर्ण;

अटल DEVICE_ATTR(delete_devices, S_IWUSR, शून्य, store_delete_devices);

अटल sमाप_प्रकार store_scan(काष्ठा device *portdev,
			  काष्ठा device_attribute *attr,
			  स्थिर अक्षर *buf, माप_प्रकार n)
अणु
	ide_hwअगर_t *hwअगर = dev_get_drvdata(portdev);

	अगर (म_भेदन(buf, "1", n))
		वापस -EINVAL;

	ide_port_unरेजिस्टर_devices(hwअगर);
	ide_port_scan(hwअगर);

	वापस n;
पूर्ण;

अटल DEVICE_ATTR(scan, S_IWUSR, शून्य, store_scan);

अटल काष्ठा device_attribute *ide_port_attrs[] = अणु
	&dev_attr_delete_devices,
	&dev_attr_scan,
	शून्य
पूर्ण;

पूर्णांक ide_sysfs_रेजिस्टर_port(ide_hwअगर_t *hwअगर)
अणु
	पूर्णांक i, rc;

	क्रम (i = 0; ide_port_attrs[i]; i++) अणु
		rc = device_create_file(hwअगर->portdev, ide_port_attrs[i]);
		अगर (rc)
			अवरोध;
	पूर्ण

	वापस rc;
पूर्ण
