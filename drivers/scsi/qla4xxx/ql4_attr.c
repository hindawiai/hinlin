<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * QLogic iSCSI HBA Driver
 * Copyright (c)  2003-2013 QLogic Corporation
 */

#समावेश "ql4_def.h"
#समावेश "ql4_glbl.h"
#समावेश "ql4_dbg.h"

अटल sमाप_प्रकार
qla4_8xxx_sysfs_पढ़ो_fw_dump(काष्ठा file *filep, काष्ठा kobject *kobj,
			     काष्ठा bin_attribute *ba, अक्षर *buf, loff_t off,
			     माप_प्रकार count)
अणु
	काष्ठा scsi_qla_host *ha = to_qla_host(dev_to_shost(container_of(kobj,
					       काष्ठा device, kobj)));

	अगर (is_qla40XX(ha))
		वापस -EINVAL;

	अगर (!test_bit(AF_82XX_DUMP_READING, &ha->flags))
		वापस 0;

	वापस memory_पढ़ो_from_buffer(buf, count, &off, ha->fw_dump,
				       ha->fw_dump_size);
पूर्ण

अटल sमाप_प्रकार
qla4_8xxx_sysfs_ग_लिखो_fw_dump(काष्ठा file *filep, काष्ठा kobject *kobj,
			      काष्ठा bin_attribute *ba, अक्षर *buf, loff_t off,
			      माप_प्रकार count)
अणु
	काष्ठा scsi_qla_host *ha = to_qla_host(dev_to_shost(container_of(kobj,
					       काष्ठा device, kobj)));
	uपूर्णांक32_t dev_state;
	दीर्घ पढ़ोing;
	पूर्णांक ret = 0;

	अगर (is_qla40XX(ha))
		वापस -EINVAL;

	अगर (off != 0)
		वापस ret;

	buf[1] = 0;
	ret = kम_से_दीर्घ(buf, 10, &पढ़ोing);
	अगर (ret) अणु
		ql4_prपूर्णांकk(KERN_ERR, ha, "%s: Invalid input. Return err %d\n",
			   __func__, ret);
		वापस ret;
	पूर्ण

	चयन (पढ़ोing) अणु
	हाल 0:
		/* clear dump collection flags */
		अगर (test_and_clear_bit(AF_82XX_DUMP_READING, &ha->flags)) अणु
			clear_bit(AF_82XX_FW_DUMPED, &ha->flags);
			/* Reload minidump ढाँचा */
			qla4xxx_alloc_fw_dump(ha);
			DEBUG2(ql4_prपूर्णांकk(KERN_INFO, ha,
					  "Firmware template reloaded\n"));
		पूर्ण
		अवरोध;
	हाल 1:
		/* Set flag to पढ़ो dump */
		अगर (test_bit(AF_82XX_FW_DUMPED, &ha->flags) &&
		    !test_bit(AF_82XX_DUMP_READING, &ha->flags)) अणु
			set_bit(AF_82XX_DUMP_READING, &ha->flags);
			DEBUG2(ql4_prपूर्णांकk(KERN_INFO, ha,
					  "Raw firmware dump ready for read on (%ld).\n",
					  ha->host_no));
		पूर्ण
		अवरोध;
	हाल 2:
		/* Reset HBA and collect FW dump */
		ha->isp_ops->idc_lock(ha);
		dev_state = qla4_8xxx_rd_direct(ha, QLA8XXX_CRB_DEV_STATE);
		अगर (dev_state == QLA8XXX_DEV_READY) अणु
			ql4_prपूर्णांकk(KERN_INFO, ha, "%s: Setting Need reset\n",
				   __func__);
			qla4_8xxx_wr_direct(ha, QLA8XXX_CRB_DEV_STATE,
					    QLA8XXX_DEV_NEED_RESET);
			अगर (is_qla8022(ha) ||
			    ((is_qla8032(ha) || is_qla8042(ha)) &&
			     qla4_83xx_can_perक्रमm_reset(ha))) अणु
				set_bit(AF_8XXX_RST_OWNER, &ha->flags);
				set_bit(AF_FW_RECOVERY, &ha->flags);
				ql4_prपूर्णांकk(KERN_INFO, ha, "%s: Reset owner is 0x%x\n",
					   __func__, ha->func_num);
			पूर्ण
		पूर्ण अन्यथा
			ql4_prपूर्णांकk(KERN_INFO, ha,
				   "%s: Reset not performed as device state is 0x%x\n",
				   __func__, dev_state);

		ha->isp_ops->idc_unlock(ha);
		अवरोध;
	शेष:
		/* करो nothing */
		अवरोध;
	पूर्ण

	वापस count;
पूर्ण

अटल काष्ठा bin_attribute sysfs_fw_dump_attr = अणु
	.attr = अणु
		.name = "fw_dump",
		.mode = S_IRUSR | S_IWUSR,
	पूर्ण,
	.size = 0,
	.पढ़ो = qla4_8xxx_sysfs_पढ़ो_fw_dump,
	.ग_लिखो = qla4_8xxx_sysfs_ग_लिखो_fw_dump,
पूर्ण;

अटल काष्ठा sysfs_entry अणु
	अक्षर *name;
	काष्ठा bin_attribute *attr;
पूर्ण bin_file_entries[] = अणु
	अणु "fw_dump", &sysfs_fw_dump_attr पूर्ण,
	अणु शून्य पूर्ण,
पूर्ण;

व्योम qla4_8xxx_alloc_sysfs_attr(काष्ठा scsi_qla_host *ha)
अणु
	काष्ठा Scsi_Host *host = ha->host;
	काष्ठा sysfs_entry *iter;
	पूर्णांक ret;

	क्रम (iter = bin_file_entries; iter->name; iter++) अणु
		ret = sysfs_create_bin_file(&host->shost_gendev.kobj,
					    iter->attr);
		अगर (ret)
			ql4_prपूर्णांकk(KERN_ERR, ha,
				   "Unable to create sysfs %s binary attribute (%d).\n",
				   iter->name, ret);
	पूर्ण
पूर्ण

व्योम qla4_8xxx_मुक्त_sysfs_attr(काष्ठा scsi_qla_host *ha)
अणु
	काष्ठा Scsi_Host *host = ha->host;
	काष्ठा sysfs_entry *iter;

	क्रम (iter = bin_file_entries; iter->name; iter++)
		sysfs_हटाओ_bin_file(&host->shost_gendev.kobj,
				      iter->attr);
पूर्ण

/* Scsi_Host attributes. */
अटल sमाप_प्रकार
qla4xxx_fw_version_show(काष्ठा device *dev,
			काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा scsi_qla_host *ha = to_qla_host(class_to_shost(dev));

	अगर (is_qla80XX(ha))
		वापस snम_लिखो(buf, PAGE_SIZE, "%d.%02d.%02d (%x)\n",
				ha->fw_info.fw_major, ha->fw_info.fw_minor,
				ha->fw_info.fw_patch, ha->fw_info.fw_build);
	अन्यथा
		वापस snम_लिखो(buf, PAGE_SIZE, "%d.%02d.%02d.%02d\n",
				ha->fw_info.fw_major, ha->fw_info.fw_minor,
				ha->fw_info.fw_patch, ha->fw_info.fw_build);
पूर्ण

अटल sमाप_प्रकार
qla4xxx_serial_num_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			अक्षर *buf)
अणु
	काष्ठा scsi_qla_host *ha = to_qla_host(class_to_shost(dev));
	वापस snम_लिखो(buf, PAGE_SIZE, "%s\n", ha->serial_number);
पूर्ण

अटल sमाप_प्रकार
qla4xxx_iscsi_version_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			   अक्षर *buf)
अणु
	काष्ठा scsi_qla_host *ha = to_qla_host(class_to_shost(dev));
	वापस snम_लिखो(buf, PAGE_SIZE, "%d.%02d\n", ha->fw_info.iscsi_major,
			ha->fw_info.iscsi_minor);
पूर्ण

अटल sमाप_प्रकार
qla4xxx_optrom_version_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			    अक्षर *buf)
अणु
	काष्ठा scsi_qla_host *ha = to_qla_host(class_to_shost(dev));
	वापस snम_लिखो(buf, PAGE_SIZE, "%d.%02d.%02d.%02d\n",
			ha->fw_info.bootload_major, ha->fw_info.bootload_minor,
			ha->fw_info.bootload_patch, ha->fw_info.bootload_build);
पूर्ण

अटल sमाप_प्रकार
qla4xxx_board_id_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
		      अक्षर *buf)
अणु
	काष्ठा scsi_qla_host *ha = to_qla_host(class_to_shost(dev));
	वापस snम_लिखो(buf, PAGE_SIZE, "0x%08X\n", ha->board_id);
पूर्ण

अटल sमाप_प्रकार
qla4xxx_fw_state_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
		      अक्षर *buf)
अणु
	काष्ठा scsi_qla_host *ha = to_qla_host(class_to_shost(dev));

	qla4xxx_get_firmware_state(ha);
	वापस snम_लिखो(buf, PAGE_SIZE, "0x%08X%8X\n", ha->firmware_state,
			ha->addl_fw_state);
पूर्ण

अटल sमाप_प्रकार
qla4xxx_phy_port_cnt_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
		      अक्षर *buf)
अणु
	काष्ठा scsi_qla_host *ha = to_qla_host(class_to_shost(dev));

	अगर (is_qla40XX(ha))
		वापस -ENOSYS;

	वापस snम_लिखो(buf, PAGE_SIZE, "0x%04X\n", ha->phy_port_cnt);
पूर्ण

अटल sमाप_प्रकार
qla4xxx_phy_port_num_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
		      अक्षर *buf)
अणु
	काष्ठा scsi_qla_host *ha = to_qla_host(class_to_shost(dev));

	अगर (is_qla40XX(ha))
		वापस -ENOSYS;

	वापस snम_लिखो(buf, PAGE_SIZE, "0x%04X\n", ha->phy_port_num);
पूर्ण

अटल sमाप_प्रकार
qla4xxx_iscsi_func_cnt_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
		      अक्षर *buf)
अणु
	काष्ठा scsi_qla_host *ha = to_qla_host(class_to_shost(dev));

	अगर (is_qla40XX(ha))
		वापस -ENOSYS;

	वापस snम_लिखो(buf, PAGE_SIZE, "0x%04X\n", ha->iscsi_pci_func_cnt);
पूर्ण

अटल sमाप_प्रकार
qla4xxx_hba_model_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
		       अक्षर *buf)
अणु
	काष्ठा scsi_qla_host *ha = to_qla_host(class_to_shost(dev));

	वापस snम_लिखो(buf, PAGE_SIZE, "%s\n", ha->model_name);
पूर्ण

अटल sमाप_प्रकार
qla4xxx_fw_बारtamp_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			  अक्षर *buf)
अणु
	काष्ठा scsi_qla_host *ha = to_qla_host(class_to_shost(dev));
	वापस snम_लिखो(buf, PAGE_SIZE, "%s %s\n", ha->fw_info.fw_build_date,
			ha->fw_info.fw_build_समय);
पूर्ण

अटल sमाप_प्रकार
qla4xxx_fw_build_user_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			   अक्षर *buf)
अणु
	काष्ठा scsi_qla_host *ha = to_qla_host(class_to_shost(dev));
	वापस snम_लिखो(buf, PAGE_SIZE, "%s\n", ha->fw_info.fw_build_user);
पूर्ण

अटल sमाप_प्रकार
qla4xxx_fw_ext_बारtamp_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			      अक्षर *buf)
अणु
	काष्ठा scsi_qla_host *ha = to_qla_host(class_to_shost(dev));
	वापस snम_लिखो(buf, PAGE_SIZE, "%s\n", ha->fw_info.extended_बारtamp);
पूर्ण

अटल sमाप_प्रकार
qla4xxx_fw_load_src_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			 अक्षर *buf)
अणु
	काष्ठा scsi_qla_host *ha = to_qla_host(class_to_shost(dev));
	अक्षर *load_src = शून्य;

	चयन (ha->fw_info.fw_load_source) अणु
	हाल 1:
		load_src = "Flash Primary";
		अवरोध;
	हाल 2:
		load_src = "Flash Secondary";
		अवरोध;
	हाल 3:
		load_src = "Host Download";
		अवरोध;
	पूर्ण

	वापस snम_लिखो(buf, PAGE_SIZE, "%s\n", load_src);
पूर्ण

अटल sमाप_प्रकार
qla4xxx_fw_upसमय_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
		       अक्षर *buf)
अणु
	काष्ठा scsi_qla_host *ha = to_qla_host(class_to_shost(dev));
	qla4xxx_about_firmware(ha);
	वापस snम_लिखो(buf, PAGE_SIZE, "%u.%u secs\n", ha->fw_upसमय_secs,
			ha->fw_upसमय_msecs);
पूर्ण

अटल DEVICE_ATTR(fw_version, S_IRUGO, qla4xxx_fw_version_show, शून्य);
अटल DEVICE_ATTR(serial_num, S_IRUGO, qla4xxx_serial_num_show, शून्य);
अटल DEVICE_ATTR(iscsi_version, S_IRUGO, qla4xxx_iscsi_version_show, शून्य);
अटल DEVICE_ATTR(optrom_version, S_IRUGO, qla4xxx_optrom_version_show, शून्य);
अटल DEVICE_ATTR(board_id, S_IRUGO, qla4xxx_board_id_show, शून्य);
अटल DEVICE_ATTR(fw_state, S_IRUGO, qla4xxx_fw_state_show, शून्य);
अटल DEVICE_ATTR(phy_port_cnt, S_IRUGO, qla4xxx_phy_port_cnt_show, शून्य);
अटल DEVICE_ATTR(phy_port_num, S_IRUGO, qla4xxx_phy_port_num_show, शून्य);
अटल DEVICE_ATTR(iscsi_func_cnt, S_IRUGO, qla4xxx_iscsi_func_cnt_show, शून्य);
अटल DEVICE_ATTR(hba_model, S_IRUGO, qla4xxx_hba_model_show, शून्य);
अटल DEVICE_ATTR(fw_बारtamp, S_IRUGO, qla4xxx_fw_बारtamp_show, शून्य);
अटल DEVICE_ATTR(fw_build_user, S_IRUGO, qla4xxx_fw_build_user_show, शून्य);
अटल DEVICE_ATTR(fw_ext_बारtamp, S_IRUGO, qla4xxx_fw_ext_बारtamp_show,
		   शून्य);
अटल DEVICE_ATTR(fw_load_src, S_IRUGO, qla4xxx_fw_load_src_show, शून्य);
अटल DEVICE_ATTR(fw_upसमय, S_IRUGO, qla4xxx_fw_upसमय_show, शून्य);

काष्ठा device_attribute *qla4xxx_host_attrs[] = अणु
	&dev_attr_fw_version,
	&dev_attr_serial_num,
	&dev_attr_iscsi_version,
	&dev_attr_optrom_version,
	&dev_attr_board_id,
	&dev_attr_fw_state,
	&dev_attr_phy_port_cnt,
	&dev_attr_phy_port_num,
	&dev_attr_iscsi_func_cnt,
	&dev_attr_hba_model,
	&dev_attr_fw_बारtamp,
	&dev_attr_fw_build_user,
	&dev_attr_fw_ext_बारtamp,
	&dev_attr_fw_load_src,
	&dev_attr_fw_upसमय,
	शून्य,
पूर्ण;
