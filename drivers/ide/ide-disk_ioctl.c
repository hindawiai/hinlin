<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/kernel.h>
#समावेश <linux/ide.h>
#समावेश <linux/hdreg.h>
#समावेश <linux/mutex.h>

#समावेश "ide-disk.h"

अटल DEFINE_MUTEX(ide_disk_ioctl_mutex);
अटल स्थिर काष्ठा ide_ioctl_devset ide_disk_ioctl_settings[] = अणु
अणु HDIO_GET_ADDRESS,	HDIO_SET_ADDRESS,   &ide_devset_address   पूर्ण,
अणु HDIO_GET_MULTCOUNT,	HDIO_SET_MULTCOUNT, &ide_devset_multcount पूर्ण,
अणु HDIO_GET_NOWERR,	HDIO_SET_NOWERR,    &ide_devset_nowerr	  पूर्ण,
अणु HDIO_GET_WCACHE,	HDIO_SET_WCACHE,    &ide_devset_wcache	  पूर्ण,
अणु HDIO_GET_ACOUSTIC,	HDIO_SET_ACOUSTIC,  &ide_devset_acoustic  पूर्ण,
अणु 0 पूर्ण
पूर्ण;

पूर्णांक ide_disk_ioctl(ide_drive_t *drive, काष्ठा block_device *bdev, भ_शेषe_t mode,
		   अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	पूर्णांक err;

	mutex_lock(&ide_disk_ioctl_mutex);
	err = ide_setting_ioctl(drive, bdev, cmd, arg, ide_disk_ioctl_settings);
	अगर (err != -EOPNOTSUPP)
		जाओ out;

	err = generic_ide_ioctl(drive, bdev, cmd, arg);
out:
	mutex_unlock(&ide_disk_ioctl_mutex);
	वापस err;
पूर्ण
