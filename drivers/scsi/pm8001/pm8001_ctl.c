<शैली गुरु>
/*
 * PMC-Sierra 8001/8081/8088/8089 SAS/SATA based host adapters driver
 *
 * Copyright (c) 2008-2009 USI Co., Ltd.
 * All rights reserved.
 *
 * Redistribution and use in source and binary क्रमms, with or without
 * modअगरication, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions, and the following disclaimer,
 *    without modअगरication.
 * 2. Redistributions in binary क्रमm must reproduce at minimum a disclaimer
 *    substantially similar to the "NO WARRANTY" disclaimer below
 *    ("Disclaimer") and any redistribution must be conditioned upon
 *    including a substantially similar Disclaimer requirement क्रम further
 *    binary redistribution.
 * 3. Neither the names of the above-listed copyright holders nor the names
 *    of any contributors may be used to enकरोrse or promote products derived
 *    from this software without specअगरic prior written permission.
 *
 * Alternatively, this software may be distributed under the terms of the
 * GNU General Public License ("GPL") version 2 as published by the Free
 * Software Foundation.
 *
 * NO WARRANTY
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * HOLDERS OR CONTRIBUTORS BE LIABLE FOR SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
 * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGES.
 *
 */
#समावेश <linux/firmware.h>
#समावेश <linux/slab.h>
#समावेश "pm8001_sas.h"
#समावेश "pm8001_ctl.h"
#समावेश "pm8001_chips.h"

/* scsi host attributes */

/**
 * pm8001_ctl_mpi_पूर्णांकerface_rev_show - MPI पूर्णांकerface revision number
 * @cdev: poपूर्णांकer to embedded class device
 * @attr: device attribute (unused)
 * @buf: the buffer वापसed
 *
 * A sysfs 'read-only' shost attribute.
 */
अटल sमाप_प्रकार pm8001_ctl_mpi_पूर्णांकerface_rev_show(काष्ठा device *cdev,
	काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा Scsi_Host *shost = class_to_shost(cdev);
	काष्ठा sas_ha_काष्ठा *sha = SHOST_TO_SAS_HA(shost);
	काष्ठा pm8001_hba_info *pm8001_ha = sha->lldd_ha;

	अगर (pm8001_ha->chip_id == chip_8001) अणु
		वापस snम_लिखो(buf, PAGE_SIZE, "%d\n",
			pm8001_ha->मुख्य_cfg_tbl.pm8001_tbl.पूर्णांकerface_rev);
	पूर्ण अन्यथा अणु
		वापस snम_लिखो(buf, PAGE_SIZE, "%d\n",
			pm8001_ha->मुख्य_cfg_tbl.pm80xx_tbl.पूर्णांकerface_rev);
	पूर्ण
पूर्ण
अटल
DEVICE_ATTR(पूर्णांकerface_rev, S_IRUGO, pm8001_ctl_mpi_पूर्णांकerface_rev_show, शून्य);

/**
 * controller_fatal_error_show - check controller is under fatal err
 * @cdev: poपूर्णांकer to embedded class device
 * @attr: device attribute (unused)
 * @buf: the buffer वापसed
 *
 * A sysfs 'read only' shost attribute.
 */
अटल sमाप_प्रकार controller_fatal_error_show(काष्ठा device *cdev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा Scsi_Host *shost = class_to_shost(cdev);
	काष्ठा sas_ha_काष्ठा *sha = SHOST_TO_SAS_HA(shost);
	काष्ठा pm8001_hba_info *pm8001_ha = sha->lldd_ha;

	वापस snम_लिखो(buf, PAGE_SIZE, "%d\n",
			pm8001_ha->controller_fatal_error);
पूर्ण
अटल DEVICE_ATTR_RO(controller_fatal_error);

/**
 * pm8001_ctl_fw_version_show - firmware version
 * @cdev: poपूर्णांकer to embedded class device
 * @attr: device attribute (unused)
 * @buf: the buffer वापसed
 *
 * A sysfs 'read-only' shost attribute.
 */
अटल sमाप_प्रकार pm8001_ctl_fw_version_show(काष्ठा device *cdev,
	काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा Scsi_Host *shost = class_to_shost(cdev);
	काष्ठा sas_ha_काष्ठा *sha = SHOST_TO_SAS_HA(shost);
	काष्ठा pm8001_hba_info *pm8001_ha = sha->lldd_ha;

	अगर (pm8001_ha->chip_id == chip_8001) अणु
		वापस snम_लिखो(buf, PAGE_SIZE, "%02x.%02x.%02x.%02x\n",
		(u8)(pm8001_ha->मुख्य_cfg_tbl.pm8001_tbl.firmware_rev >> 24),
		(u8)(pm8001_ha->मुख्य_cfg_tbl.pm8001_tbl.firmware_rev >> 16),
		(u8)(pm8001_ha->मुख्य_cfg_tbl.pm8001_tbl.firmware_rev >> 8),
		(u8)(pm8001_ha->मुख्य_cfg_tbl.pm8001_tbl.firmware_rev));
	पूर्ण अन्यथा अणु
		वापस snम_लिखो(buf, PAGE_SIZE, "%02x.%02x.%02x.%02x\n",
		(u8)(pm8001_ha->मुख्य_cfg_tbl.pm80xx_tbl.firmware_rev >> 24),
		(u8)(pm8001_ha->मुख्य_cfg_tbl.pm80xx_tbl.firmware_rev >> 16),
		(u8)(pm8001_ha->मुख्य_cfg_tbl.pm80xx_tbl.firmware_rev >> 8),
		(u8)(pm8001_ha->मुख्य_cfg_tbl.pm80xx_tbl.firmware_rev));
	पूर्ण
पूर्ण
अटल DEVICE_ATTR(fw_version, S_IRUGO, pm8001_ctl_fw_version_show, शून्य);

/**
 * pm8001_ctl_ila_version_show - ila version
 * @cdev: poपूर्णांकer to embedded class device
 * @attr: device attribute (unused)
 * @buf: the buffer वापसed
 *
 * A sysfs 'read-only' shost attribute.
 */
अटल sमाप_प्रकार pm8001_ctl_ila_version_show(काष्ठा device *cdev,
	काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा Scsi_Host *shost = class_to_shost(cdev);
	काष्ठा sas_ha_काष्ठा *sha = SHOST_TO_SAS_HA(shost);
	काष्ठा pm8001_hba_info *pm8001_ha = sha->lldd_ha;

	अगर (pm8001_ha->chip_id != chip_8001) अणु
		वापस snम_लिखो(buf, PAGE_SIZE, "%02x.%02x.%02x.%02x\n",
		(u8)(pm8001_ha->मुख्य_cfg_tbl.pm80xx_tbl.ila_version >> 24),
		(u8)(pm8001_ha->मुख्य_cfg_tbl.pm80xx_tbl.ila_version >> 16),
		(u8)(pm8001_ha->मुख्य_cfg_tbl.pm80xx_tbl.ila_version >> 8),
		(u8)(pm8001_ha->मुख्य_cfg_tbl.pm80xx_tbl.ila_version));
	पूर्ण
	वापस 0;
पूर्ण
अटल DEVICE_ATTR(ila_version, 0444, pm8001_ctl_ila_version_show, शून्य);

/**
 * pm8001_ctl_inactive_fw_version_show - Inacative firmware version number
 * @cdev: poपूर्णांकer to embedded class device
 * @attr: device attribute (unused)
 * @buf: the buffer वापसed
 *
 * A sysfs 'read-only' shost attribute.
 */
अटल sमाप_प्रकार pm8001_ctl_inactive_fw_version_show(काष्ठा device *cdev,
	काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा Scsi_Host *shost = class_to_shost(cdev);
	काष्ठा sas_ha_काष्ठा *sha = SHOST_TO_SAS_HA(shost);
	काष्ठा pm8001_hba_info *pm8001_ha = sha->lldd_ha;

	अगर (pm8001_ha->chip_id != chip_8001) अणु
		वापस snम_लिखो(buf, PAGE_SIZE, "%02x.%02x.%02x.%02x\n",
		(u8)(pm8001_ha->मुख्य_cfg_tbl.pm80xx_tbl.inc_fw_version >> 24),
		(u8)(pm8001_ha->मुख्य_cfg_tbl.pm80xx_tbl.inc_fw_version >> 16),
		(u8)(pm8001_ha->मुख्य_cfg_tbl.pm80xx_tbl.inc_fw_version >> 8),
		(u8)(pm8001_ha->मुख्य_cfg_tbl.pm80xx_tbl.inc_fw_version));
	पूर्ण
	वापस 0;
पूर्ण
अटल
DEVICE_ATTR(inc_fw_ver, 0444, pm8001_ctl_inactive_fw_version_show, शून्य);

/**
 * pm8001_ctl_max_out_io_show - max outstanding io supported
 * @cdev: poपूर्णांकer to embedded class device
 * @attr: device attribute (unused)
 * @buf: the buffer वापसed
 *
 * A sysfs 'read-only' shost attribute.
 */
अटल sमाप_प्रकार pm8001_ctl_max_out_io_show(काष्ठा device *cdev,
	काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा Scsi_Host *shost = class_to_shost(cdev);
	काष्ठा sas_ha_काष्ठा *sha = SHOST_TO_SAS_HA(shost);
	काष्ठा pm8001_hba_info *pm8001_ha = sha->lldd_ha;

	अगर (pm8001_ha->chip_id == chip_8001) अणु
		वापस snम_लिखो(buf, PAGE_SIZE, "%d\n",
			pm8001_ha->मुख्य_cfg_tbl.pm8001_tbl.max_out_io);
	पूर्ण अन्यथा अणु
		वापस snम_लिखो(buf, PAGE_SIZE, "%d\n",
			pm8001_ha->मुख्य_cfg_tbl.pm80xx_tbl.max_out_io);
	पूर्ण
पूर्ण
अटल DEVICE_ATTR(max_out_io, S_IRUGO, pm8001_ctl_max_out_io_show, शून्य);
/**
 * pm8001_ctl_max_devices_show - max devices support
 * @cdev: poपूर्णांकer to embedded class device
 * @attr: device attribute (unused)
 * @buf: the buffer वापसed
 *
 * A sysfs 'read-only' shost attribute.
 */
अटल sमाप_प्रकार pm8001_ctl_max_devices_show(काष्ठा device *cdev,
	काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा Scsi_Host *shost = class_to_shost(cdev);
	काष्ठा sas_ha_काष्ठा *sha = SHOST_TO_SAS_HA(shost);
	काष्ठा pm8001_hba_info *pm8001_ha = sha->lldd_ha;

	अगर (pm8001_ha->chip_id == chip_8001) अणु
		वापस snम_लिखो(buf, PAGE_SIZE, "%04d\n",
			(u16)(pm8001_ha->मुख्य_cfg_tbl.pm8001_tbl.max_sgl >> 16)
			);
	पूर्ण अन्यथा अणु
		वापस snम_लिखो(buf, PAGE_SIZE, "%04d\n",
			(u16)(pm8001_ha->मुख्य_cfg_tbl.pm80xx_tbl.max_sgl >> 16)
			);
	पूर्ण
पूर्ण
अटल DEVICE_ATTR(max_devices, S_IRUGO, pm8001_ctl_max_devices_show, शून्य);
/**
 * pm8001_ctl_max_sg_list_show - max sg list supported अगरf not 0.0 क्रम no
 * hardware limitation
 * @cdev: poपूर्णांकer to embedded class device
 * @attr: device attribute (unused)
 * @buf: the buffer वापसed
 *
 * A sysfs 'read-only' shost attribute.
 */
अटल sमाप_प्रकार pm8001_ctl_max_sg_list_show(काष्ठा device *cdev,
	काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा Scsi_Host *shost = class_to_shost(cdev);
	काष्ठा sas_ha_काष्ठा *sha = SHOST_TO_SAS_HA(shost);
	काष्ठा pm8001_hba_info *pm8001_ha = sha->lldd_ha;

	अगर (pm8001_ha->chip_id == chip_8001) अणु
		वापस snम_लिखो(buf, PAGE_SIZE, "%04d\n",
			pm8001_ha->मुख्य_cfg_tbl.pm8001_tbl.max_sgl & 0x0000FFFF
			);
	पूर्ण अन्यथा अणु
		वापस snम_लिखो(buf, PAGE_SIZE, "%04d\n",
			pm8001_ha->मुख्य_cfg_tbl.pm80xx_tbl.max_sgl & 0x0000FFFF
			);
	पूर्ण
पूर्ण
अटल DEVICE_ATTR(max_sg_list, S_IRUGO, pm8001_ctl_max_sg_list_show, शून्य);

#घोषणा SAS_1_0 0x1
#घोषणा SAS_1_1 0x2
#घोषणा SAS_2_0 0x4

अटल sमाप_प्रकार
show_sas_spec_support_status(अचिन्हित पूर्णांक mode, अक्षर *buf)
अणु
	sमाप_प्रकार len = 0;

	अगर (mode & SAS_1_1)
		len = प्र_लिखो(buf, "%s", "SAS1.1");
	अगर (mode & SAS_2_0)
		len += प्र_लिखो(buf + len, "%s%s", len ? ", " : "", "SAS2.0");
	len += प्र_लिखो(buf + len, "\n");

	वापस len;
पूर्ण

/**
 * pm8001_ctl_sas_spec_support_show - sas spec supported
 * @cdev: poपूर्णांकer to embedded class device
 * @attr: device attribute (unused)
 * @buf: the buffer वापसed
 *
 * A sysfs 'read-only' shost attribute.
 */
अटल sमाप_प्रकार pm8001_ctl_sas_spec_support_show(काष्ठा device *cdev,
	काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	अचिन्हित पूर्णांक mode;
	काष्ठा Scsi_Host *shost = class_to_shost(cdev);
	काष्ठा sas_ha_काष्ठा *sha = SHOST_TO_SAS_HA(shost);
	काष्ठा pm8001_hba_info *pm8001_ha = sha->lldd_ha;
	/* fe000000 means supports SAS2.1 */
	अगर (pm8001_ha->chip_id == chip_8001)
		mode = (pm8001_ha->मुख्य_cfg_tbl.pm8001_tbl.ctrl_cap_flag &
							0xfe000000)>>25;
	अन्यथा
		/* fe000000 means supports SAS2.1 */
		mode = (pm8001_ha->मुख्य_cfg_tbl.pm80xx_tbl.ctrl_cap_flag &
							0xfe000000)>>25;
	वापस show_sas_spec_support_status(mode, buf);
पूर्ण
अटल DEVICE_ATTR(sas_spec_support, S_IRUGO,
		   pm8001_ctl_sas_spec_support_show, शून्य);

/**
 * pm8001_ctl_host_sas_address_show - sas address
 * @cdev: poपूर्णांकer to embedded class device
 * @attr: device attribute (unused)
 * @buf: the buffer वापसed
 *
 * This is the controller sas address
 *
 * A sysfs 'read-only' shost attribute.
 */
अटल sमाप_प्रकार pm8001_ctl_host_sas_address_show(काष्ठा device *cdev,
	काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा Scsi_Host *shost = class_to_shost(cdev);
	काष्ठा sas_ha_काष्ठा *sha = SHOST_TO_SAS_HA(shost);
	काष्ठा pm8001_hba_info *pm8001_ha = sha->lldd_ha;
	वापस snम_लिखो(buf, PAGE_SIZE, "0x%016llx\n",
			be64_to_cpu(*(__be64 *)pm8001_ha->sas_addr));
पूर्ण
अटल DEVICE_ATTR(host_sas_address, S_IRUGO,
		   pm8001_ctl_host_sas_address_show, शून्य);

/**
 * pm8001_ctl_logging_level_show - logging level
 * @cdev: poपूर्णांकer to embedded class device
 * @attr: device attribute (unused)
 * @buf: the buffer वापसed
 *
 * A sysfs 'read/write' shost attribute.
 */
अटल sमाप_प्रकार pm8001_ctl_logging_level_show(काष्ठा device *cdev,
	काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा Scsi_Host *shost = class_to_shost(cdev);
	काष्ठा sas_ha_काष्ठा *sha = SHOST_TO_SAS_HA(shost);
	काष्ठा pm8001_hba_info *pm8001_ha = sha->lldd_ha;

	वापस snम_लिखो(buf, PAGE_SIZE, "%08xh\n", pm8001_ha->logging_level);
पूर्ण

अटल sमाप_प्रकार pm8001_ctl_logging_level_store(काष्ठा device *cdev,
	काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा Scsi_Host *shost = class_to_shost(cdev);
	काष्ठा sas_ha_काष्ठा *sha = SHOST_TO_SAS_HA(shost);
	काष्ठा pm8001_hba_info *pm8001_ha = sha->lldd_ha;
	पूर्णांक val = 0;

	अगर (माला_पूछो(buf, "%x", &val) != 1)
		वापस -EINVAL;

	pm8001_ha->logging_level = val;
	वापस म_माप(buf);
पूर्ण

अटल DEVICE_ATTR(logging_level, S_IRUGO | S_IWUSR,
	pm8001_ctl_logging_level_show, pm8001_ctl_logging_level_store);
/**
 * pm8001_ctl_aap_log_show - aap1 event log
 * @cdev: poपूर्णांकer to embedded class device
 * @attr: device attribute (unused)
 * @buf: the buffer वापसed
 *
 * A sysfs 'read-only' shost attribute.
 */
अटल sमाप_प्रकार pm8001_ctl_aap_log_show(काष्ठा device *cdev,
	काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा Scsi_Host *shost = class_to_shost(cdev);
	काष्ठा sas_ha_काष्ठा *sha = SHOST_TO_SAS_HA(shost);
	काष्ठा pm8001_hba_info *pm8001_ha = sha->lldd_ha;
	u8 *ptr = (u8 *)pm8001_ha->memoryMap.region[AAP1].virt_ptr;
	पूर्णांक i;

	अक्षर *str = buf;
	पूर्णांक max = 2;
	क्रम (i = 0; i < max; i++) अणु
		str += प्र_लिखो(str, "0x%08x 0x%08x 0x%08x 0x%08x 0x%08x 0x%08x"
			       "0x%08x 0x%08x\n",
			       pm8001_ctl_aap1_memmap(ptr, i, 0),
			       pm8001_ctl_aap1_memmap(ptr, i, 4),
			       pm8001_ctl_aap1_memmap(ptr, i, 8),
			       pm8001_ctl_aap1_memmap(ptr, i, 12),
			       pm8001_ctl_aap1_memmap(ptr, i, 16),
			       pm8001_ctl_aap1_memmap(ptr, i, 20),
			       pm8001_ctl_aap1_memmap(ptr, i, 24),
			       pm8001_ctl_aap1_memmap(ptr, i, 28));
	पूर्ण

	वापस str - buf;
पूर्ण
अटल DEVICE_ATTR(aap_log, S_IRUGO, pm8001_ctl_aap_log_show, शून्य);
/**
 * pm8001_ctl_ib_queue_log_show - Out bound Queue log
 * @cdev:poपूर्णांकer to embedded class device
 * @attr: device attribute (unused)
 * @buf: the buffer वापसed
 * A sysfs 'read-only' shost attribute.
 */
अटल sमाप_प्रकार pm8001_ctl_ib_queue_log_show(काष्ठा device *cdev,
	काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा Scsi_Host *shost = class_to_shost(cdev);
	काष्ठा sas_ha_काष्ठा *sha = SHOST_TO_SAS_HA(shost);
	काष्ठा pm8001_hba_info *pm8001_ha = sha->lldd_ha;
	पूर्णांक offset;
	अक्षर *str = buf;
	पूर्णांक start = 0;
	u32 ib_offset = pm8001_ha->ib_offset;
#घोषणा IB_MEMMAP(c)	\
		(*(u32 *)((u8 *)pm8001_ha->	\
		memoryMap.region[ib_offset].virt_ptr +	\
		pm8001_ha->evtlog_ib_offset + (c)))

	क्रम (offset = 0; offset < IB_OB_READ_TIMES; offset++) अणु
		str += प्र_लिखो(str, "0x%08x\n", IB_MEMMAP(start));
		start = start + 4;
	पूर्ण
	pm8001_ha->evtlog_ib_offset += SYSFS_OFFSET;
	अगर (((pm8001_ha->evtlog_ib_offset) % (PM80XX_IB_OB_QUEUE_SIZE)) == 0)
		pm8001_ha->evtlog_ib_offset = 0;

	वापस str - buf;
पूर्ण

अटल DEVICE_ATTR(ib_log, S_IRUGO, pm8001_ctl_ib_queue_log_show, शून्य);
/**
 * pm8001_ctl_ob_queue_log_show - Out bound Queue log
 * @cdev:poपूर्णांकer to embedded class device
 * @attr: device attribute (unused)
 * @buf: the buffer वापसed
 * A sysfs 'read-only' shost attribute.
 */

अटल sमाप_प्रकार pm8001_ctl_ob_queue_log_show(काष्ठा device *cdev,
	काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा Scsi_Host *shost = class_to_shost(cdev);
	काष्ठा sas_ha_काष्ठा *sha = SHOST_TO_SAS_HA(shost);
	काष्ठा pm8001_hba_info *pm8001_ha = sha->lldd_ha;
	पूर्णांक offset;
	अक्षर *str = buf;
	पूर्णांक start = 0;
	u32 ob_offset = pm8001_ha->ob_offset;
#घोषणा OB_MEMMAP(c)	\
		(*(u32 *)((u8 *)pm8001_ha->	\
		memoryMap.region[ob_offset].virt_ptr +	\
		pm8001_ha->evtlog_ob_offset + (c)))

	क्रम (offset = 0; offset < IB_OB_READ_TIMES; offset++) अणु
		str += प्र_लिखो(str, "0x%08x\n", OB_MEMMAP(start));
		start = start + 4;
	पूर्ण
	pm8001_ha->evtlog_ob_offset += SYSFS_OFFSET;
	अगर (((pm8001_ha->evtlog_ob_offset) % (PM80XX_IB_OB_QUEUE_SIZE)) == 0)
		pm8001_ha->evtlog_ob_offset = 0;

	वापस str - buf;
पूर्ण
अटल DEVICE_ATTR(ob_log, S_IRUGO, pm8001_ctl_ob_queue_log_show, शून्य);
/**
 * pm8001_ctl_bios_version_show - Bios version Display
 * @cdev:poपूर्णांकer to embedded class device
 * @attr: device attribute (unused)
 * @buf:the buffer वापसed
 * A sysfs 'read-only' shost attribute.
 */
अटल sमाप_प्रकार pm8001_ctl_bios_version_show(काष्ठा device *cdev,
	काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा Scsi_Host *shost = class_to_shost(cdev);
	काष्ठा sas_ha_काष्ठा *sha = SHOST_TO_SAS_HA(shost);
	काष्ठा pm8001_hba_info *pm8001_ha = sha->lldd_ha;
	अक्षर *str = buf;
	पूर्णांक bios_index;
	DECLARE_COMPLETION_ONSTACK(completion);
	काष्ठा pm8001_ioctl_payload payload;

	pm8001_ha->nvmd_completion = &completion;
	payload.minor_function = 7;
	payload.offset = 0;
	payload.rd_length = 4096;
	payload.func_specअगरic = kzalloc(4096, GFP_KERNEL);
	अगर (!payload.func_specअगरic)
		वापस -ENOMEM;
	अगर (PM8001_CHIP_DISP->get_nvmd_req(pm8001_ha, &payload)) अणु
		kमुक्त(payload.func_specअगरic);
		वापस -ENOMEM;
	पूर्ण
	रुको_क्रम_completion(&completion);
	क्रम (bios_index = BIOSOFFSET; bios_index < BIOS_OFFSET_LIMIT;
		bios_index++)
		str += प्र_लिखो(str, "%c",
			*(payload.func_specअगरic+bios_index));
	kमुक्त(payload.func_specअगरic);
	वापस str - buf;
पूर्ण
अटल DEVICE_ATTR(bios_version, S_IRUGO, pm8001_ctl_bios_version_show, शून्य);
/**
 * event_log_size_show - event log size
 * @cdev: poपूर्णांकer to embedded class device
 * @attr: device attribute (unused)
 * @buf: the buffer वापसed
 *
 * A sysfs पढ़ो  shost attribute.
 */
अटल sमाप_प्रकार event_log_size_show(काष्ठा device *cdev,
	काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा Scsi_Host *shost = class_to_shost(cdev);
	काष्ठा sas_ha_काष्ठा *sha = SHOST_TO_SAS_HA(shost);
	काष्ठा pm8001_hba_info *pm8001_ha = sha->lldd_ha;

	वापस snम_लिखो(buf, PAGE_SIZE, "%d\n",
		pm8001_ha->मुख्य_cfg_tbl.pm80xx_tbl.event_log_size);
पूर्ण
अटल DEVICE_ATTR_RO(event_log_size);
/**
 * pm8001_ctl_iop_log_show - IOP event log
 * @cdev: poपूर्णांकer to embedded class device
 * @attr: device attribute (unused)
 * @buf: the buffer वापसed
 *
 * A sysfs 'read-only' shost attribute.
 */
अटल sमाप_प्रकार pm8001_ctl_iop_log_show(काष्ठा device *cdev,
	काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा Scsi_Host *shost = class_to_shost(cdev);
	काष्ठा sas_ha_काष्ठा *sha = SHOST_TO_SAS_HA(shost);
	काष्ठा pm8001_hba_info *pm8001_ha = sha->lldd_ha;
	अक्षर *str = buf;
	u32 पढ़ो_size =
		pm8001_ha->मुख्य_cfg_tbl.pm80xx_tbl.event_log_size / 1024;
	अटल u32 start, end, count;
	u32 max_पढ़ो_बार = 32;
	u32 max_count = (पढ़ो_size * 1024) / (max_पढ़ो_बार * 4);
	u32 *temp = (u32 *)pm8001_ha->memoryMap.region[IOP].virt_ptr;

	अगर ((count % max_count) == 0) अणु
		start = 0;
		end = max_पढ़ो_बार;
		count = 0;
	पूर्ण अन्यथा अणु
		start = end;
		end = end + max_पढ़ो_बार;
	पूर्ण

	क्रम (; start < end; start++)
		str += प्र_लिखो(str, "%08x ", *(temp+start));
	count++;
	वापस str - buf;
पूर्ण
अटल DEVICE_ATTR(iop_log, S_IRUGO, pm8001_ctl_iop_log_show, शून्य);

/**
 ** pm8001_ctl_fatal_log_show - fatal error logging
 ** @cdev:poपूर्णांकer to embedded class device
 ** @attr: device attribute
 ** @buf: the buffer वापसed
 **
 ** A sysfs 'read-only' shost attribute.
 **/

अटल sमाप_प्रकार pm8001_ctl_fatal_log_show(काष्ठा device *cdev,
	काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	sमाप_प्रकार count;

	count = pm80xx_get_fatal_dump(cdev, attr, buf);
	वापस count;
पूर्ण

अटल DEVICE_ATTR(fatal_log, S_IRUGO, pm8001_ctl_fatal_log_show, शून्य);

/**
 ** non_fatal_log_show - non fatal error logging
 ** @cdev:poपूर्णांकer to embedded class device
 ** @attr: device attribute
 ** @buf: the buffer वापसed
 **
 ** A sysfs 'read-only' shost attribute.
 **/
अटल sमाप_प्रकार non_fatal_log_show(काष्ठा device *cdev,
	काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	u32 count;

	count = pm80xx_get_non_fatal_dump(cdev, attr, buf);
	वापस count;
पूर्ण
अटल DEVICE_ATTR_RO(non_fatal_log);

अटल sमाप_प्रकार non_fatal_count_show(काष्ठा device *cdev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा Scsi_Host *shost = class_to_shost(cdev);
	काष्ठा sas_ha_काष्ठा *sha = SHOST_TO_SAS_HA(shost);
	काष्ठा pm8001_hba_info *pm8001_ha = sha->lldd_ha;

	वापस snम_लिखो(buf, PAGE_SIZE, "%08x",
			pm8001_ha->non_fatal_count);
पूर्ण

अटल sमाप_प्रकार non_fatal_count_store(काष्ठा device *cdev,
		काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा Scsi_Host *shost = class_to_shost(cdev);
	काष्ठा sas_ha_काष्ठा *sha = SHOST_TO_SAS_HA(shost);
	काष्ठा pm8001_hba_info *pm8001_ha = sha->lldd_ha;
	पूर्णांक val = 0;

	अगर (kstrtoपूर्णांक(buf, 16, &val) != 0)
		वापस -EINVAL;

	pm8001_ha->non_fatal_count = val;
	वापस म_माप(buf);
पूर्ण
अटल DEVICE_ATTR_RW(non_fatal_count);

/**
 ** pm8001_ctl_gsm_log_show - gsm dump collection
 ** @cdev:poपूर्णांकer to embedded class device
 ** @attr: device attribute (unused)
 ** @buf: the buffer वापसed
 ** A sysfs 'read-only' shost attribute.
 **/
अटल sमाप_प्रकार pm8001_ctl_gsm_log_show(काष्ठा device *cdev,
	काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	sमाप_प्रकार count;

	count = pm8001_get_gsm_dump(cdev, SYSFS_OFFSET, buf);
	वापस count;
पूर्ण

अटल DEVICE_ATTR(gsm_log, S_IRUGO, pm8001_ctl_gsm_log_show, शून्य);

#घोषणा FLASH_CMD_NONE      0x00
#घोषणा FLASH_CMD_UPDATE    0x01
#घोषणा FLASH_CMD_SET_NVMD    0x02

काष्ठा flash_command अणु
     u8      command[8];
     पूर्णांक     code;
पूर्ण;

अटल स्थिर काष्ठा flash_command flash_command_table[] = अणु
     अणु"set_nvmd",    FLASH_CMD_SET_NVMDपूर्ण,
     अणु"update",      FLASH_CMD_UPDATEपूर्ण,
     अणु"",            FLASH_CMD_NONEपूर्ण /* Last entry should be शून्य. */
पूर्ण;

काष्ठा error_fw अणु
     अक्षर    *reason;
     पूर्णांक     err_code;
पूर्ण;

अटल स्थिर काष्ठा error_fw flash_error_table[] = अणु
     अणु"Failed to open fw image file",	FAIL_OPEN_BIOS_खातापूर्ण,
     अणु"image header mismatch",		FLASH_UPDATE_HDR_ERRपूर्ण,
     अणु"image offset mismatch",		FLASH_UPDATE_OFFSET_ERRपूर्ण,
     अणु"image CRC Error",		FLASH_UPDATE_CRC_ERRपूर्ण,
     अणु"image length Error.",		FLASH_UPDATE_LENGTH_ERRपूर्ण,
     अणु"Failed to program flash chip",	FLASH_UPDATE_HW_ERRपूर्ण,
     अणु"Flash chip not supported.",	FLASH_UPDATE_DNLD_NOT_SUPPORTEDपूर्ण,
     अणु"Flash update disabled.",		FLASH_UPDATE_DISABLEDपूर्ण,
     अणु"Flash in progress",		FLASH_IN_PROGRESSपूर्ण,
     अणु"Image file size Error",		FAIL_खाता_SIZEपूर्ण,
     अणु"Input parameter error",		FAIL_PARAMETERSपूर्ण,
     अणु"Out of memory",			FAIL_OUT_MEMORYपूर्ण,
     अणु"OK", 0पूर्ण	/* Last entry err_code = 0. */
पूर्ण;

अटल पूर्णांक pm8001_set_nvmd(काष्ठा pm8001_hba_info *pm8001_ha)
अणु
	काष्ठा pm8001_ioctl_payload	*payload;
	DECLARE_COMPLETION_ONSTACK(completion);
	u8		*ioctlbuffer;
	u32		ret;
	u32		length = 1024 * 5 + माप(*payload) - 1;

	अगर (pm8001_ha->fw_image->size > 4096) अणु
		pm8001_ha->fw_status = FAIL_खाता_SIZE;
		वापस -EFAULT;
	पूर्ण

	ioctlbuffer = kzalloc(length, GFP_KERNEL);
	अगर (!ioctlbuffer) अणु
		pm8001_ha->fw_status = FAIL_OUT_MEMORY;
		वापस -ENOMEM;
	पूर्ण
	payload = (काष्ठा pm8001_ioctl_payload *)ioctlbuffer;
	स_नकल((u8 *)&payload->func_specअगरic, (u8 *)pm8001_ha->fw_image->data,
				pm8001_ha->fw_image->size);
	payload->wr_length = pm8001_ha->fw_image->size;
	payload->id = 0;
	payload->minor_function = 0x1;
	pm8001_ha->nvmd_completion = &completion;
	ret = PM8001_CHIP_DISP->set_nvmd_req(pm8001_ha, payload);
	अगर (ret) अणु
		pm8001_ha->fw_status = FAIL_OUT_MEMORY;
		जाओ out;
	पूर्ण
	रुको_क्रम_completion(&completion);
out:
	kमुक्त(ioctlbuffer);
	वापस ret;
पूर्ण

अटल पूर्णांक pm8001_update_flash(काष्ठा pm8001_hba_info *pm8001_ha)
अणु
	काष्ठा pm8001_ioctl_payload	*payload;
	DECLARE_COMPLETION_ONSTACK(completion);
	u8		*ioctlbuffer;
	काष्ठा fw_control_info	*fwControl;
	u32		partitionSize, partitionSizeTmp;
	u32		loopNumber, loopcount;
	काष्ठा pm8001_fw_image_header *image_hdr;
	u32		sizeRead = 0;
	u32		ret = 0;
	u32		length = 1024 * 16 + माप(*payload) - 1;

	अगर (pm8001_ha->fw_image->size < 28) अणु
		pm8001_ha->fw_status = FAIL_खाता_SIZE;
		वापस -EFAULT;
	पूर्ण
	ioctlbuffer = kzalloc(length, GFP_KERNEL);
	अगर (!ioctlbuffer) अणु
		pm8001_ha->fw_status = FAIL_OUT_MEMORY;
		वापस -ENOMEM;
	पूर्ण
	image_hdr = (काष्ठा pm8001_fw_image_header *)pm8001_ha->fw_image->data;
	जबतक (sizeRead < pm8001_ha->fw_image->size) अणु
		partitionSizeTmp =
			*(u32 *)((u8 *)&image_hdr->image_length + sizeRead);
		partitionSize = be32_to_cpu(partitionSizeTmp);
		loopcount = DIV_ROUND_UP(partitionSize + HEADER_LEN,
					IOCTL_BUF_SIZE);
		क्रम (loopNumber = 0; loopNumber < loopcount; loopNumber++) अणु
			payload = (काष्ठा pm8001_ioctl_payload *)ioctlbuffer;
			payload->wr_length = 1024*16;
			payload->id = 0;
			fwControl =
			      (काष्ठा fw_control_info *)&payload->func_specअगरic;
			fwControl->len = IOCTL_BUF_SIZE;   /* IN */
			fwControl->size = partitionSize + HEADER_LEN;/* IN */
			fwControl->retcode = 0;/* OUT */
			fwControl->offset = loopNumber * IOCTL_BUF_SIZE;/*OUT */

		/* क्रम the last chunk of data in हाल file size is not even with
		4k, load only the rest*/
		अगर (((loopcount-loopNumber) == 1) &&
			((partitionSize + HEADER_LEN) % IOCTL_BUF_SIZE)) अणु
			fwControl->len =
				(partitionSize + HEADER_LEN) % IOCTL_BUF_SIZE;
			स_नकल((u8 *)fwControl->buffer,
				(u8 *)pm8001_ha->fw_image->data + sizeRead,
				(partitionSize + HEADER_LEN) % IOCTL_BUF_SIZE);
			sizeRead +=
				(partitionSize + HEADER_LEN) % IOCTL_BUF_SIZE;
		पूर्ण अन्यथा अणु
			स_नकल((u8 *)fwControl->buffer,
				(u8 *)pm8001_ha->fw_image->data + sizeRead,
				IOCTL_BUF_SIZE);
			sizeRead += IOCTL_BUF_SIZE;
		पूर्ण

		pm8001_ha->nvmd_completion = &completion;
		ret = PM8001_CHIP_DISP->fw_flash_update_req(pm8001_ha, payload);
		अगर (ret) अणु
			pm8001_ha->fw_status = FAIL_OUT_MEMORY;
			जाओ out;
		पूर्ण
		रुको_क्रम_completion(&completion);
		अगर (fwControl->retcode > FLASH_UPDATE_IN_PROGRESS) अणु
			pm8001_ha->fw_status = fwControl->retcode;
			ret = -EFAULT;
			जाओ out;
		पूर्ण
		पूर्ण
	पूर्ण
out:
	kमुक्त(ioctlbuffer);
	वापस ret;
पूर्ण
अटल sमाप_प्रकार pm8001_store_update_fw(काष्ठा device *cdev,
				      काष्ठा device_attribute *attr,
				      स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा Scsi_Host *shost = class_to_shost(cdev);
	काष्ठा sas_ha_काष्ठा *sha = SHOST_TO_SAS_HA(shost);
	काष्ठा pm8001_hba_info *pm8001_ha = sha->lldd_ha;
	अक्षर *cmd_ptr, *filename_ptr;
	पूर्णांक res, i;
	पूर्णांक flash_command = FLASH_CMD_NONE;
	पूर्णांक ret;

	अगर (!capable(CAP_SYS_ADMIN))
		वापस -EACCES;

	/* this test protects us from running two flash processes at once,
	 * so we should start with this test */
	अगर (pm8001_ha->fw_status == FLASH_IN_PROGRESS)
		वापस -EINPROGRESS;
	pm8001_ha->fw_status = FLASH_IN_PROGRESS;

	cmd_ptr = kसुस्मृति(count, 2, GFP_KERNEL);
	अगर (!cmd_ptr) अणु
		pm8001_ha->fw_status = FAIL_OUT_MEMORY;
		वापस -ENOMEM;
	पूर्ण

	filename_ptr = cmd_ptr + count;
	res = माला_पूछो(buf, "%s %s", cmd_ptr, filename_ptr);
	अगर (res != 2) अणु
		pm8001_ha->fw_status = FAIL_PARAMETERS;
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	क्रम (i = 0; flash_command_table[i].code != FLASH_CMD_NONE; i++) अणु
		अगर (!स_भेद(flash_command_table[i].command,
				 cmd_ptr, म_माप(cmd_ptr))) अणु
			flash_command = flash_command_table[i].code;
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (flash_command == FLASH_CMD_NONE) अणु
		pm8001_ha->fw_status = FAIL_PARAMETERS;
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	ret = request_firmware(&pm8001_ha->fw_image,
			       filename_ptr,
			       pm8001_ha->dev);

	अगर (ret) अणु
		pm8001_dbg(pm8001_ha, FAIL,
			   "Failed to load firmware image file %s, error %d\n",
			   filename_ptr, ret);
		pm8001_ha->fw_status = FAIL_OPEN_BIOS_खाता;
		जाओ out;
	पूर्ण

	अगर (FLASH_CMD_UPDATE == flash_command)
		ret = pm8001_update_flash(pm8001_ha);
	अन्यथा
		ret = pm8001_set_nvmd(pm8001_ha);

	release_firmware(pm8001_ha->fw_image);
out:
	kमुक्त(cmd_ptr);

	अगर (ret)
		वापस ret;

	pm8001_ha->fw_status = FLASH_OK;
	वापस count;
पूर्ण

अटल sमाप_प्रकार pm8001_show_update_fw(काष्ठा device *cdev,
				     काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	पूर्णांक i;
	काष्ठा Scsi_Host *shost = class_to_shost(cdev);
	काष्ठा sas_ha_काष्ठा *sha = SHOST_TO_SAS_HA(shost);
	काष्ठा pm8001_hba_info *pm8001_ha = sha->lldd_ha;

	क्रम (i = 0; flash_error_table[i].err_code != 0; i++) अणु
		अगर (flash_error_table[i].err_code == pm8001_ha->fw_status)
			अवरोध;
	पूर्ण
	अगर (pm8001_ha->fw_status != FLASH_IN_PROGRESS)
		pm8001_ha->fw_status = FLASH_OK;

	वापस snम_लिखो(buf, PAGE_SIZE, "status=%x %s\n",
			flash_error_table[i].err_code,
			flash_error_table[i].reason);
पूर्ण
अटल DEVICE_ATTR(update_fw, S_IRUGO|S_IWUSR|S_IWGRP,
	pm8001_show_update_fw, pm8001_store_update_fw);

/**
 * ctl_mpi_state_show - controller MPI state check
 * @cdev: poपूर्णांकer to embedded class device
 * @buf: the buffer वापसed
 *
 * A sysfs 'read-only' shost attribute.
 */

अटल स्थिर अक्षर *स्थिर mpiStateText[] = अणु
	"MPI is not initialized",
	"MPI is successfully initialized",
	"MPI termination is in progress",
	"MPI initialization failed with error in [31:16]"
पूर्ण;

अटल sमाप_प्रकार ctl_mpi_state_show(काष्ठा device *cdev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा Scsi_Host *shost = class_to_shost(cdev);
	काष्ठा sas_ha_काष्ठा *sha = SHOST_TO_SAS_HA(shost);
	काष्ठा pm8001_hba_info *pm8001_ha = sha->lldd_ha;
	अचिन्हित पूर्णांक mpidw0;

	mpidw0 = pm8001_mr32(pm8001_ha->general_stat_tbl_addr, 0);
	वापस sysfs_emit(buf, "%s\n", mpiStateText[mpidw0 & 0x0003]);
पूर्ण
अटल DEVICE_ATTR_RO(ctl_mpi_state);

/**
 * ctl_hmi_error_show - controller MPI initialization fails
 * @cdev: poपूर्णांकer to embedded class device
 * @buf: the buffer वापसed
 *
 * A sysfs 'read-only' shost attribute.
 */

अटल sमाप_प्रकार ctl_hmi_error_show(काष्ठा device *cdev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा Scsi_Host *shost = class_to_shost(cdev);
	काष्ठा sas_ha_काष्ठा *sha = SHOST_TO_SAS_HA(shost);
	काष्ठा pm8001_hba_info *pm8001_ha = sha->lldd_ha;
	अचिन्हित पूर्णांक mpidw0;

	mpidw0 = pm8001_mr32(pm8001_ha->general_stat_tbl_addr, 0);
	वापस sysfs_emit(buf, "0x%08x\n", (mpidw0 >> 16));
पूर्ण
अटल DEVICE_ATTR_RO(ctl_hmi_error);

/**
 * ctl_raae_count_show - controller raae count check
 * @cdev: poपूर्णांकer to embedded class device
 * @buf: the buffer वापसed
 *
 * A sysfs 'read-only' shost attribute.
 */

अटल sमाप_प्रकार ctl_raae_count_show(काष्ठा device *cdev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा Scsi_Host *shost = class_to_shost(cdev);
	काष्ठा sas_ha_काष्ठा *sha = SHOST_TO_SAS_HA(shost);
	काष्ठा pm8001_hba_info *pm8001_ha = sha->lldd_ha;
	अचिन्हित पूर्णांक raaecnt;

	raaecnt = pm8001_mr32(pm8001_ha->general_stat_tbl_addr, 12);
	वापस sysfs_emit(buf, "0x%08x\n", raaecnt);
पूर्ण
अटल DEVICE_ATTR_RO(ctl_raae_count);

/**
 * ctl_iop0_count_show - controller iop0 count check
 * @cdev: poपूर्णांकer to embedded class device
 * @buf: the buffer वापसed
 *
 * A sysfs 'read-only' shost attribute.
 */

अटल sमाप_प्रकार ctl_iop0_count_show(काष्ठा device *cdev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा Scsi_Host *shost = class_to_shost(cdev);
	काष्ठा sas_ha_काष्ठा *sha = SHOST_TO_SAS_HA(shost);
	काष्ठा pm8001_hba_info *pm8001_ha = sha->lldd_ha;
	अचिन्हित पूर्णांक iop0cnt;

	iop0cnt = pm8001_mr32(pm8001_ha->general_stat_tbl_addr, 16);
	वापस sysfs_emit(buf, "0x%08x\n", iop0cnt);
पूर्ण
अटल DEVICE_ATTR_RO(ctl_iop0_count);

/**
 * ctl_iop1_count_show - controller iop1 count check
 * @cdev: poपूर्णांकer to embedded class device
 * @buf: the buffer वापसed
 *
 * A sysfs 'read-only' shost attribute.
 */

अटल sमाप_प्रकार ctl_iop1_count_show(काष्ठा device *cdev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा Scsi_Host *shost = class_to_shost(cdev);
	काष्ठा sas_ha_काष्ठा *sha = SHOST_TO_SAS_HA(shost);
	काष्ठा pm8001_hba_info *pm8001_ha = sha->lldd_ha;
	अचिन्हित पूर्णांक iop1cnt;

	iop1cnt = pm8001_mr32(pm8001_ha->general_stat_tbl_addr, 20);
	वापस sysfs_emit(buf, "0x%08x\n", iop1cnt);

पूर्ण
अटल DEVICE_ATTR_RO(ctl_iop1_count);

काष्ठा device_attribute *pm8001_host_attrs[] = अणु
	&dev_attr_पूर्णांकerface_rev,
	&dev_attr_controller_fatal_error,
	&dev_attr_fw_version,
	&dev_attr_update_fw,
	&dev_attr_aap_log,
	&dev_attr_iop_log,
	&dev_attr_fatal_log,
	&dev_attr_non_fatal_log,
	&dev_attr_non_fatal_count,
	&dev_attr_gsm_log,
	&dev_attr_max_out_io,
	&dev_attr_max_devices,
	&dev_attr_max_sg_list,
	&dev_attr_sas_spec_support,
	&dev_attr_logging_level,
	&dev_attr_event_log_size,
	&dev_attr_host_sas_address,
	&dev_attr_bios_version,
	&dev_attr_ib_log,
	&dev_attr_ob_log,
	&dev_attr_ila_version,
	&dev_attr_inc_fw_ver,
	&dev_attr_ctl_mpi_state,
	&dev_attr_ctl_hmi_error,
	&dev_attr_ctl_raae_count,
	&dev_attr_ctl_iop0_count,
	&dev_attr_ctl_iop1_count,
	शून्य,
पूर्ण;

