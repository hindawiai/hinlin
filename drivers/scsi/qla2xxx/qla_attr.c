<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * QLogic Fibre Channel HBA Driver
 * Copyright (c)  2003-2014 QLogic Corporation
 */
#समावेश "qla_def.h"
#समावेश "qla_target.h"

#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/slab.h>
#समावेश <linux/delay.h>

अटल पूर्णांक qla24xx_vport_disable(काष्ठा fc_vport *, bool);

/* SYSFS attributes --------------------------------------------------------- */

अटल sमाप_प्रकार
qla2x00_sysfs_पढ़ो_fw_dump(काष्ठा file *filp, काष्ठा kobject *kobj,
			   काष्ठा bin_attribute *bin_attr,
			   अक्षर *buf, loff_t off, माप_प्रकार count)
अणु
	काष्ठा scsi_qla_host *vha = shost_priv(dev_to_shost(container_of(kobj,
	    काष्ठा device, kobj)));
	काष्ठा qla_hw_data *ha = vha->hw;
	पूर्णांक rval = 0;

	अगर (!(ha->fw_dump_पढ़ोing || ha->mctp_dump_पढ़ोing ||
	      ha->mpi_fw_dump_पढ़ोing))
		वापस 0;

	mutex_lock(&ha->optrom_mutex);
	अगर (IS_P3P_TYPE(ha)) अणु
		अगर (off < ha->md_ढाँचा_size) अणु
			rval = memory_पढ़ो_from_buffer(buf, count,
			    &off, ha->md_पंचांगplt_hdr, ha->md_ढाँचा_size);
		पूर्ण अन्यथा अणु
			off -= ha->md_ढाँचा_size;
			rval = memory_पढ़ो_from_buffer(buf, count,
			    &off, ha->md_dump, ha->md_dump_size);
		पूर्ण
	पूर्ण अन्यथा अगर (ha->mctp_dumped && ha->mctp_dump_पढ़ोing) अणु
		rval = memory_पढ़ो_from_buffer(buf, count, &off, ha->mctp_dump,
		    MCTP_DUMP_SIZE);
	पूर्ण अन्यथा अगर (ha->mpi_fw_dumped && ha->mpi_fw_dump_पढ़ोing) अणु
		rval = memory_पढ़ो_from_buffer(buf, count, &off,
					       ha->mpi_fw_dump,
					       ha->mpi_fw_dump_len);
	पूर्ण अन्यथा अगर (ha->fw_dump_पढ़ोing) अणु
		rval = memory_पढ़ो_from_buffer(buf, count, &off, ha->fw_dump,
					ha->fw_dump_len);
	पूर्ण अन्यथा अणु
		rval = 0;
	पूर्ण
	mutex_unlock(&ha->optrom_mutex);
	वापस rval;
पूर्ण

अटल sमाप_प्रकार
qla2x00_sysfs_ग_लिखो_fw_dump(काष्ठा file *filp, काष्ठा kobject *kobj,
			    काष्ठा bin_attribute *bin_attr,
			    अक्षर *buf, loff_t off, माप_प्रकार count)
अणु
	काष्ठा scsi_qla_host *vha = shost_priv(dev_to_shost(container_of(kobj,
	    काष्ठा device, kobj)));
	काष्ठा qla_hw_data *ha = vha->hw;
	पूर्णांक पढ़ोing;

	अगर (off != 0)
		वापस (0);

	पढ़ोing = simple_म_से_दीर्घ(buf, शून्य, 10);
	चयन (पढ़ोing) अणु
	हाल 0:
		अगर (!ha->fw_dump_पढ़ोing)
			अवरोध;

		ql_log(ql_log_info, vha, 0x705d,
		    "Firmware dump cleared on (%ld).\n", vha->host_no);

		अगर (IS_P3P_TYPE(ha)) अणु
			qla82xx_md_मुक्त(vha);
			qla82xx_md_prep(vha);
		पूर्ण
		ha->fw_dump_पढ़ोing = 0;
		ha->fw_dumped = false;
		अवरोध;
	हाल 1:
		अगर (ha->fw_dumped && !ha->fw_dump_पढ़ोing) अणु
			ha->fw_dump_पढ़ोing = 1;

			ql_log(ql_log_info, vha, 0x705e,
			    "Raw firmware dump ready for read on (%ld).\n",
			    vha->host_no);
		पूर्ण
		अवरोध;
	हाल 2:
		qla2x00_alloc_fw_dump(vha);
		अवरोध;
	हाल 3:
		अगर (IS_QLA82XX(ha)) अणु
			qla82xx_idc_lock(ha);
			qla82xx_set_reset_owner(vha);
			qla82xx_idc_unlock(ha);
		पूर्ण अन्यथा अगर (IS_QLA8044(ha)) अणु
			qla8044_idc_lock(ha);
			qla82xx_set_reset_owner(vha);
			qla8044_idc_unlock(ha);
		पूर्ण अन्यथा अणु
			qla2x00_प्रणाली_error(vha);
		पूर्ण
		अवरोध;
	हाल 4:
		अगर (IS_P3P_TYPE(ha)) अणु
			अगर (ha->md_पंचांगplt_hdr)
				ql_dbg(ql_dbg_user, vha, 0x705b,
				    "MiniDump supported with this firmware.\n");
			अन्यथा
				ql_dbg(ql_dbg_user, vha, 0x709d,
				    "MiniDump not supported with this firmware.\n");
		पूर्ण
		अवरोध;
	हाल 5:
		अगर (IS_P3P_TYPE(ha))
			set_bit(ISP_ABORT_NEEDED, &vha->dpc_flags);
		अवरोध;
	हाल 6:
		अगर (!ha->mctp_dump_पढ़ोing)
			अवरोध;
		ql_log(ql_log_info, vha, 0x70c1,
		    "MCTP dump cleared on (%ld).\n", vha->host_no);
		ha->mctp_dump_पढ़ोing = 0;
		ha->mctp_dumped = 0;
		अवरोध;
	हाल 7:
		अगर (ha->mctp_dumped && !ha->mctp_dump_पढ़ोing) अणु
			ha->mctp_dump_पढ़ोing = 1;
			ql_log(ql_log_info, vha, 0x70c2,
			    "Raw mctp dump ready for read on (%ld).\n",
			    vha->host_no);
		पूर्ण
		अवरोध;
	हाल 8:
		अगर (!ha->mpi_fw_dump_पढ़ोing)
			अवरोध;
		ql_log(ql_log_info, vha, 0x70e7,
		       "MPI firmware dump cleared on (%ld).\n", vha->host_no);
		ha->mpi_fw_dump_पढ़ोing = 0;
		ha->mpi_fw_dumped = 0;
		अवरोध;
	हाल 9:
		अगर (ha->mpi_fw_dumped && !ha->mpi_fw_dump_पढ़ोing) अणु
			ha->mpi_fw_dump_पढ़ोing = 1;
			ql_log(ql_log_info, vha, 0x70e8,
			       "Raw MPI firmware dump ready for read on (%ld).\n",
			       vha->host_no);
		पूर्ण
		अवरोध;
	हाल 10:
		अगर (IS_QLA27XX(ha) || IS_QLA28XX(ha)) अणु
			ql_log(ql_log_info, vha, 0x70e9,
			       "Issuing MPI firmware dump on host#%ld.\n",
			       vha->host_no);
			ha->isp_ops->mpi_fw_dump(vha, 0);
		पूर्ण
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
	.पढ़ो = qla2x00_sysfs_पढ़ो_fw_dump,
	.ग_लिखो = qla2x00_sysfs_ग_लिखो_fw_dump,
पूर्ण;

अटल sमाप_प्रकार
qla2x00_sysfs_पढ़ो_nvram(काष्ठा file *filp, काष्ठा kobject *kobj,
			 काष्ठा bin_attribute *bin_attr,
			 अक्षर *buf, loff_t off, माप_प्रकार count)
अणु
	काष्ठा scsi_qla_host *vha = shost_priv(dev_to_shost(container_of(kobj,
	    काष्ठा device, kobj)));
	काष्ठा qla_hw_data *ha = vha->hw;
	uपूर्णांक32_t faddr;
	काष्ठा active_regions active_regions = अणु पूर्ण;

	अगर (!capable(CAP_SYS_ADMIN))
		वापस 0;

	mutex_lock(&ha->optrom_mutex);
	अगर (qla2x00_chip_is_करोwn(vha)) अणु
		mutex_unlock(&ha->optrom_mutex);
		वापस -EAGAIN;
	पूर्ण

	अगर (!IS_NOCACHE_VPD_TYPE(ha)) अणु
		mutex_unlock(&ha->optrom_mutex);
		जाओ skip;
	पूर्ण

	faddr = ha->flt_region_nvram;
	अगर (IS_QLA28XX(ha)) अणु
		qla28xx_get_aux_images(vha, &active_regions);
		अगर (active_regions.aux.vpd_nvram == QLA27XX_SECONDARY_IMAGE)
			faddr = ha->flt_region_nvram_sec;
	पूर्ण
	ha->isp_ops->पढ़ो_optrom(vha, ha->nvram, faddr << 2, ha->nvram_size);

	mutex_unlock(&ha->optrom_mutex);

skip:
	वापस memory_पढ़ो_from_buffer(buf, count, &off, ha->nvram,
					ha->nvram_size);
पूर्ण

अटल sमाप_प्रकार
qla2x00_sysfs_ग_लिखो_nvram(काष्ठा file *filp, काष्ठा kobject *kobj,
			  काष्ठा bin_attribute *bin_attr,
			  अक्षर *buf, loff_t off, माप_प्रकार count)
अणु
	काष्ठा scsi_qla_host *vha = shost_priv(dev_to_shost(container_of(kobj,
	    काष्ठा device, kobj)));
	काष्ठा qla_hw_data *ha = vha->hw;
	uपूर्णांक16_t	cnt;

	अगर (!capable(CAP_SYS_ADMIN) || off != 0 || count != ha->nvram_size ||
	    !ha->isp_ops->ग_लिखो_nvram)
		वापस -EINVAL;

	/* Checksum NVRAM. */
	अगर (IS_FWI2_CAPABLE(ha)) अणु
		__le32 *iter = (__क्रमce __le32 *)buf;
		uपूर्णांक32_t chksum;

		chksum = 0;
		क्रम (cnt = 0; cnt < ((count >> 2) - 1); cnt++, iter++)
			chksum += le32_to_cpu(*iter);
		chksum = ~chksum + 1;
		*iter = cpu_to_le32(chksum);
	पूर्ण अन्यथा अणु
		uपूर्णांक8_t *iter;
		uपूर्णांक8_t chksum;

		iter = (uपूर्णांक8_t *)buf;
		chksum = 0;
		क्रम (cnt = 0; cnt < count - 1; cnt++)
			chksum += *iter++;
		chksum = ~chksum + 1;
		*iter = chksum;
	पूर्ण

	अगर (qla2x00_रुको_क्रम_hba_online(vha) != QLA_SUCCESS) अणु
		ql_log(ql_log_warn, vha, 0x705f,
		    "HBA not online, failing NVRAM update.\n");
		वापस -EAGAIN;
	पूर्ण

	mutex_lock(&ha->optrom_mutex);
	अगर (qla2x00_chip_is_करोwn(vha)) अणु
		mutex_unlock(&ha->optrom_mutex);
		वापस -EAGAIN;
	पूर्ण

	/* Write NVRAM. */
	ha->isp_ops->ग_लिखो_nvram(vha, buf, ha->nvram_base, count);
	ha->isp_ops->पढ़ो_nvram(vha, ha->nvram, ha->nvram_base,
	    count);
	mutex_unlock(&ha->optrom_mutex);

	ql_dbg(ql_dbg_user, vha, 0x7060,
	    "Setting ISP_ABORT_NEEDED\n");
	/* NVRAM settings take effect immediately. */
	set_bit(ISP_ABORT_NEEDED, &vha->dpc_flags);
	qla2xxx_wake_dpc(vha);
	qla2x00_रुको_क्रम_chip_reset(vha);

	वापस count;
पूर्ण

अटल काष्ठा bin_attribute sysfs_nvram_attr = अणु
	.attr = अणु
		.name = "nvram",
		.mode = S_IRUSR | S_IWUSR,
	पूर्ण,
	.size = 512,
	.पढ़ो = qla2x00_sysfs_पढ़ो_nvram,
	.ग_लिखो = qla2x00_sysfs_ग_लिखो_nvram,
पूर्ण;

अटल sमाप_प्रकार
qla2x00_sysfs_पढ़ो_optrom(काष्ठा file *filp, काष्ठा kobject *kobj,
			  काष्ठा bin_attribute *bin_attr,
			  अक्षर *buf, loff_t off, माप_प्रकार count)
अणु
	काष्ठा scsi_qla_host *vha = shost_priv(dev_to_shost(container_of(kobj,
	    काष्ठा device, kobj)));
	काष्ठा qla_hw_data *ha = vha->hw;
	sमाप_प्रकार rval = 0;

	mutex_lock(&ha->optrom_mutex);

	अगर (ha->optrom_state != QLA_SREADING)
		जाओ out;

	rval = memory_पढ़ो_from_buffer(buf, count, &off, ha->optrom_buffer,
	    ha->optrom_region_size);

out:
	mutex_unlock(&ha->optrom_mutex);

	वापस rval;
पूर्ण

अटल sमाप_प्रकार
qla2x00_sysfs_ग_लिखो_optrom(काष्ठा file *filp, काष्ठा kobject *kobj,
			   काष्ठा bin_attribute *bin_attr,
			   अक्षर *buf, loff_t off, माप_प्रकार count)
अणु
	काष्ठा scsi_qla_host *vha = shost_priv(dev_to_shost(container_of(kobj,
	    काष्ठा device, kobj)));
	काष्ठा qla_hw_data *ha = vha->hw;

	mutex_lock(&ha->optrom_mutex);

	अगर (ha->optrom_state != QLA_SWRITING) अणु
		mutex_unlock(&ha->optrom_mutex);
		वापस -EINVAL;
	पूर्ण
	अगर (off > ha->optrom_region_size) अणु
		mutex_unlock(&ha->optrom_mutex);
		वापस -दुस्फल;
	पूर्ण
	अगर (off + count > ha->optrom_region_size)
		count = ha->optrom_region_size - off;

	स_नकल(&ha->optrom_buffer[off], buf, count);
	mutex_unlock(&ha->optrom_mutex);

	वापस count;
पूर्ण

अटल काष्ठा bin_attribute sysfs_optrom_attr = अणु
	.attr = अणु
		.name = "optrom",
		.mode = S_IRUSR | S_IWUSR,
	पूर्ण,
	.size = 0,
	.पढ़ो = qla2x00_sysfs_पढ़ो_optrom,
	.ग_लिखो = qla2x00_sysfs_ग_लिखो_optrom,
पूर्ण;

अटल sमाप_प्रकार
qla2x00_sysfs_ग_लिखो_optrom_ctl(काष्ठा file *filp, काष्ठा kobject *kobj,
			       काष्ठा bin_attribute *bin_attr,
			       अक्षर *buf, loff_t off, माप_प्रकार count)
अणु
	काष्ठा scsi_qla_host *vha = shost_priv(dev_to_shost(container_of(kobj,
	    काष्ठा device, kobj)));
	काष्ठा qla_hw_data *ha = vha->hw;
	uपूर्णांक32_t start = 0;
	uपूर्णांक32_t size = ha->optrom_size;
	पूर्णांक val, valid;
	sमाप_प्रकार rval = count;

	अगर (off)
		वापस -EINVAL;

	अगर (unlikely(pci_channel_offline(ha->pdev)))
		वापस -EAGAIN;

	अगर (माला_पूछो(buf, "%d:%x:%x", &val, &start, &size) < 1)
		वापस -EINVAL;
	अगर (start > ha->optrom_size)
		वापस -EINVAL;
	अगर (size > ha->optrom_size - start)
		size = ha->optrom_size - start;

	mutex_lock(&ha->optrom_mutex);
	अगर (qla2x00_chip_is_करोwn(vha)) अणु
		mutex_unlock(&ha->optrom_mutex);
		वापस -EAGAIN;
	पूर्ण
	चयन (val) अणु
	हाल 0:
		अगर (ha->optrom_state != QLA_SREADING &&
		    ha->optrom_state != QLA_SWRITING) अणु
			rval =  -EINVAL;
			जाओ out;
		पूर्ण
		ha->optrom_state = QLA_SWAITING;

		ql_dbg(ql_dbg_user, vha, 0x7061,
		    "Freeing flash region allocation -- 0x%x bytes.\n",
		    ha->optrom_region_size);

		vमुक्त(ha->optrom_buffer);
		ha->optrom_buffer = शून्य;
		अवरोध;
	हाल 1:
		अगर (ha->optrom_state != QLA_SWAITING) अणु
			rval = -EINVAL;
			जाओ out;
		पूर्ण

		ha->optrom_region_start = start;
		ha->optrom_region_size = size;

		ha->optrom_state = QLA_SREADING;
		ha->optrom_buffer = vzalloc(ha->optrom_region_size);
		अगर (ha->optrom_buffer == शून्य) अणु
			ql_log(ql_log_warn, vha, 0x7062,
			    "Unable to allocate memory for optrom retrieval "
			    "(%x).\n", ha->optrom_region_size);

			ha->optrom_state = QLA_SWAITING;
			rval = -ENOMEM;
			जाओ out;
		पूर्ण

		अगर (qla2x00_रुको_क्रम_hba_online(vha) != QLA_SUCCESS) अणु
			ql_log(ql_log_warn, vha, 0x7063,
			    "HBA not online, failing NVRAM update.\n");
			rval = -EAGAIN;
			जाओ out;
		पूर्ण

		ql_dbg(ql_dbg_user, vha, 0x7064,
		    "Reading flash region -- 0x%x/0x%x.\n",
		    ha->optrom_region_start, ha->optrom_region_size);

		ha->isp_ops->पढ़ो_optrom(vha, ha->optrom_buffer,
		    ha->optrom_region_start, ha->optrom_region_size);
		अवरोध;
	हाल 2:
		अगर (ha->optrom_state != QLA_SWAITING) अणु
			rval = -EINVAL;
			जाओ out;
		पूर्ण

		/*
		 * We need to be more restrictive on which FLASH regions are
		 * allowed to be updated via user-space.  Regions accessible
		 * via this method include:
		 *
		 * ISP21xx/ISP22xx/ISP23xx type boards:
		 *
		 * 	0x000000 -> 0x020000 -- Boot code.
		 *
		 * ISP2322/ISP24xx type boards:
		 *
		 * 	0x000000 -> 0x07ffff -- Boot code.
		 * 	0x080000 -> 0x0fffff -- Firmware.
		 *
		 * ISP25xx type boards:
		 *
		 * 	0x000000 -> 0x07ffff -- Boot code.
		 * 	0x080000 -> 0x0fffff -- Firmware.
		 * 	0x120000 -> 0x12ffff -- VPD and HBA parameters.
		 *
		 * > ISP25xx type boards:
		 *
		 *      None -- should go through BSG.
		 */
		valid = 0;
		अगर (ha->optrom_size == OPTROM_SIZE_2300 && start == 0)
			valid = 1;
		अन्यथा अगर (IS_QLA24XX_TYPE(ha) || IS_QLA25XX(ha))
			valid = 1;
		अगर (!valid) अणु
			ql_log(ql_log_warn, vha, 0x7065,
			    "Invalid start region 0x%x/0x%x.\n", start, size);
			rval = -EINVAL;
			जाओ out;
		पूर्ण

		ha->optrom_region_start = start;
		ha->optrom_region_size = size;

		ha->optrom_state = QLA_SWRITING;
		ha->optrom_buffer = vzalloc(ha->optrom_region_size);
		अगर (ha->optrom_buffer == शून्य) अणु
			ql_log(ql_log_warn, vha, 0x7066,
			    "Unable to allocate memory for optrom update "
			    "(%x)\n", ha->optrom_region_size);

			ha->optrom_state = QLA_SWAITING;
			rval = -ENOMEM;
			जाओ out;
		पूर्ण

		ql_dbg(ql_dbg_user, vha, 0x7067,
		    "Staging flash region write -- 0x%x/0x%x.\n",
		    ha->optrom_region_start, ha->optrom_region_size);

		अवरोध;
	हाल 3:
		अगर (ha->optrom_state != QLA_SWRITING) अणु
			rval = -EINVAL;
			जाओ out;
		पूर्ण

		अगर (qla2x00_रुको_क्रम_hba_online(vha) != QLA_SUCCESS) अणु
			ql_log(ql_log_warn, vha, 0x7068,
			    "HBA not online, failing flash update.\n");
			rval = -EAGAIN;
			जाओ out;
		पूर्ण

		ql_dbg(ql_dbg_user, vha, 0x7069,
		    "Writing flash region -- 0x%x/0x%x.\n",
		    ha->optrom_region_start, ha->optrom_region_size);

		rval = ha->isp_ops->ग_लिखो_optrom(vha, ha->optrom_buffer,
		    ha->optrom_region_start, ha->optrom_region_size);
		अगर (rval)
			rval = -EIO;
		अवरोध;
	शेष:
		rval = -EINVAL;
	पूर्ण

out:
	mutex_unlock(&ha->optrom_mutex);
	वापस rval;
पूर्ण

अटल काष्ठा bin_attribute sysfs_optrom_ctl_attr = अणु
	.attr = अणु
		.name = "optrom_ctl",
		.mode = S_IWUSR,
	पूर्ण,
	.size = 0,
	.ग_लिखो = qla2x00_sysfs_ग_लिखो_optrom_ctl,
पूर्ण;

अटल sमाप_प्रकार
qla2x00_sysfs_पढ़ो_vpd(काष्ठा file *filp, काष्ठा kobject *kobj,
		       काष्ठा bin_attribute *bin_attr,
		       अक्षर *buf, loff_t off, माप_प्रकार count)
अणु
	काष्ठा scsi_qla_host *vha = shost_priv(dev_to_shost(container_of(kobj,
	    काष्ठा device, kobj)));
	काष्ठा qla_hw_data *ha = vha->hw;
	uपूर्णांक32_t faddr;
	काष्ठा active_regions active_regions = अणु पूर्ण;

	अगर (unlikely(pci_channel_offline(ha->pdev)))
		वापस -EAGAIN;

	अगर (!capable(CAP_SYS_ADMIN))
		वापस -EINVAL;

	अगर (IS_NOCACHE_VPD_TYPE(ha))
		जाओ skip;

	faddr = ha->flt_region_vpd << 2;

	अगर (IS_QLA28XX(ha)) अणु
		qla28xx_get_aux_images(vha, &active_regions);
		अगर (active_regions.aux.vpd_nvram == QLA27XX_SECONDARY_IMAGE)
			faddr = ha->flt_region_vpd_sec << 2;

		ql_dbg(ql_dbg_init, vha, 0x7070,
		    "Loading %s nvram image.\n",
		    active_regions.aux.vpd_nvram == QLA27XX_PRIMARY_IMAGE ?
		    "primary" : "secondary");
	पूर्ण

	mutex_lock(&ha->optrom_mutex);
	अगर (qla2x00_chip_is_करोwn(vha)) अणु
		mutex_unlock(&ha->optrom_mutex);
		वापस -EAGAIN;
	पूर्ण

	ha->isp_ops->पढ़ो_optrom(vha, ha->vpd, faddr, ha->vpd_size);
	mutex_unlock(&ha->optrom_mutex);

	ha->isp_ops->पढ़ो_optrom(vha, ha->vpd, faddr, ha->vpd_size);
skip:
	वापस memory_पढ़ो_from_buffer(buf, count, &off, ha->vpd, ha->vpd_size);
पूर्ण

अटल sमाप_प्रकार
qla2x00_sysfs_ग_लिखो_vpd(काष्ठा file *filp, काष्ठा kobject *kobj,
			काष्ठा bin_attribute *bin_attr,
			अक्षर *buf, loff_t off, माप_प्रकार count)
अणु
	काष्ठा scsi_qla_host *vha = shost_priv(dev_to_shost(container_of(kobj,
	    काष्ठा device, kobj)));
	काष्ठा qla_hw_data *ha = vha->hw;
	uपूर्णांक8_t *पंचांगp_data;

	अगर (unlikely(pci_channel_offline(ha->pdev)))
		वापस 0;

	अगर (qla2x00_chip_is_करोwn(vha))
		वापस 0;

	अगर (!capable(CAP_SYS_ADMIN) || off != 0 || count != ha->vpd_size ||
	    !ha->isp_ops->ग_लिखो_nvram)
		वापस 0;

	अगर (qla2x00_रुको_क्रम_hba_online(vha) != QLA_SUCCESS) अणु
		ql_log(ql_log_warn, vha, 0x706a,
		    "HBA not online, failing VPD update.\n");
		वापस -EAGAIN;
	पूर्ण

	mutex_lock(&ha->optrom_mutex);
	अगर (qla2x00_chip_is_करोwn(vha)) अणु
		mutex_unlock(&ha->optrom_mutex);
		वापस -EAGAIN;
	पूर्ण

	/* Write NVRAM. */
	ha->isp_ops->ग_लिखो_nvram(vha, buf, ha->vpd_base, count);
	ha->isp_ops->पढ़ो_nvram(vha, ha->vpd, ha->vpd_base, count);

	/* Update flash version inक्रमmation क्रम 4Gb & above. */
	अगर (!IS_FWI2_CAPABLE(ha)) अणु
		mutex_unlock(&ha->optrom_mutex);
		वापस -EINVAL;
	पूर्ण

	पंचांगp_data = vदो_स्मृति(256);
	अगर (!पंचांगp_data) अणु
		mutex_unlock(&ha->optrom_mutex);
		ql_log(ql_log_warn, vha, 0x706b,
		    "Unable to allocate memory for VPD information update.\n");
		वापस -ENOMEM;
	पूर्ण
	ha->isp_ops->get_flash_version(vha, पंचांगp_data);
	vमुक्त(पंचांगp_data);

	mutex_unlock(&ha->optrom_mutex);

	वापस count;
पूर्ण

अटल काष्ठा bin_attribute sysfs_vpd_attr = अणु
	.attr = अणु
		.name = "vpd",
		.mode = S_IRUSR | S_IWUSR,
	पूर्ण,
	.size = 0,
	.पढ़ो = qla2x00_sysfs_पढ़ो_vpd,
	.ग_लिखो = qla2x00_sysfs_ग_लिखो_vpd,
पूर्ण;

अटल sमाप_प्रकार
qla2x00_sysfs_पढ़ो_sfp(काष्ठा file *filp, काष्ठा kobject *kobj,
		       काष्ठा bin_attribute *bin_attr,
		       अक्षर *buf, loff_t off, माप_प्रकार count)
अणु
	काष्ठा scsi_qla_host *vha = shost_priv(dev_to_shost(container_of(kobj,
	    काष्ठा device, kobj)));
	पूर्णांक rval;

	अगर (!capable(CAP_SYS_ADMIN) || off != 0 || count < SFP_DEV_SIZE)
		वापस 0;

	mutex_lock(&vha->hw->optrom_mutex);
	अगर (qla2x00_chip_is_करोwn(vha)) अणु
		mutex_unlock(&vha->hw->optrom_mutex);
		वापस 0;
	पूर्ण

	rval = qla2x00_पढ़ो_sfp_dev(vha, buf, count);
	mutex_unlock(&vha->hw->optrom_mutex);

	अगर (rval)
		वापस -EIO;

	वापस count;
पूर्ण

अटल काष्ठा bin_attribute sysfs_sfp_attr = अणु
	.attr = अणु
		.name = "sfp",
		.mode = S_IRUSR | S_IWUSR,
	पूर्ण,
	.size = SFP_DEV_SIZE,
	.पढ़ो = qla2x00_sysfs_पढ़ो_sfp,
पूर्ण;

अटल sमाप_प्रकार
qla2x00_sysfs_ग_लिखो_reset(काष्ठा file *filp, काष्ठा kobject *kobj,
			काष्ठा bin_attribute *bin_attr,
			अक्षर *buf, loff_t off, माप_प्रकार count)
अणु
	काष्ठा scsi_qla_host *vha = shost_priv(dev_to_shost(container_of(kobj,
	    काष्ठा device, kobj)));
	काष्ठा qla_hw_data *ha = vha->hw;
	काष्ठा scsi_qla_host *base_vha = pci_get_drvdata(ha->pdev);
	पूर्णांक type;
	uपूर्णांक32_t idc_control;
	uपूर्णांक8_t *पंचांगp_data = शून्य;

	अगर (off != 0)
		वापस -EINVAL;

	type = simple_म_से_दीर्घ(buf, शून्य, 10);
	चयन (type) अणु
	हाल 0x2025c:
		ql_log(ql_log_info, vha, 0x706e,
		    "Issuing ISP reset.\n");

		अगर (vha->hw->flags.port_isolated) अणु
			ql_log(ql_log_info, vha, 0x706e,
			       "Port is isolated, returning.\n");
			वापस -EINVAL;
		पूर्ण

		scsi_block_requests(vha->host);
		अगर (IS_QLA82XX(ha)) अणु
			ha->flags.isp82xx_no_md_cap = 1;
			qla82xx_idc_lock(ha);
			qla82xx_set_reset_owner(vha);
			qla82xx_idc_unlock(ha);
		पूर्ण अन्यथा अगर (IS_QLA8044(ha)) अणु
			qla8044_idc_lock(ha);
			idc_control = qla8044_rd_reg(ha,
			    QLA8044_IDC_DRV_CTRL);
			qla8044_wr_reg(ha, QLA8044_IDC_DRV_CTRL,
			    (idc_control | GRACEFUL_RESET_BIT1));
			qla82xx_set_reset_owner(vha);
			qla8044_idc_unlock(ha);
		पूर्ण अन्यथा अणु
			set_bit(ISP_ABORT_NEEDED, &vha->dpc_flags);
			qla2xxx_wake_dpc(vha);
		पूर्ण
		qla2x00_रुको_क्रम_chip_reset(vha);
		scsi_unblock_requests(vha->host);
		अवरोध;
	हाल 0x2025d:
		अगर (!IS_QLA81XX(ha) && !IS_QLA83XX(ha) &&
		    !IS_QLA27XX(ha) && !IS_QLA28XX(ha))
			वापस -EPERM;

		ql_log(ql_log_info, vha, 0x706f,
		    "Issuing MPI reset.\n");

		अगर (IS_QLA83XX(ha) || IS_QLA27XX(ha) || IS_QLA28XX(ha)) अणु
			uपूर्णांक32_t idc_control;

			qla83xx_idc_lock(vha, 0);
			__qla83xx_get_idc_control(vha, &idc_control);
			idc_control |= QLA83XX_IDC_GRACEFUL_RESET;
			__qla83xx_set_idc_control(vha, idc_control);
			qla83xx_wr_reg(vha, QLA83XX_IDC_DEV_STATE,
			    QLA8XXX_DEV_NEED_RESET);
			qla83xx_idc_audit(vha, IDC_AUDIT_TIMESTAMP);
			qla83xx_idc_unlock(vha, 0);
			अवरोध;
		पूर्ण अन्यथा अणु
			/* Make sure FC side is not in reset */
			WARN_ON_ONCE(qla2x00_रुको_क्रम_hba_online(vha) !=
				     QLA_SUCCESS);

			/* Issue MPI reset */
			scsi_block_requests(vha->host);
			अगर (qla81xx_restart_mpi_firmware(vha) != QLA_SUCCESS)
				ql_log(ql_log_warn, vha, 0x7070,
				    "MPI reset failed.\n");
			scsi_unblock_requests(vha->host);
			अवरोध;
		पूर्ण
		अवरोध;
	हाल 0x2025e:
		अगर (!IS_P3P_TYPE(ha) || vha != base_vha) अणु
			ql_log(ql_log_info, vha, 0x7071,
			    "FCoE ctx reset not supported.\n");
			वापस -EPERM;
		पूर्ण

		ql_log(ql_log_info, vha, 0x7072,
		    "Issuing FCoE ctx reset.\n");
		set_bit(FCOE_CTX_RESET_NEEDED, &vha->dpc_flags);
		qla2xxx_wake_dpc(vha);
		qla2x00_रुको_क्रम_fcoe_ctx_reset(vha);
		अवरोध;
	हाल 0x2025f:
		अगर (!IS_QLA8031(ha))
			वापस -EPERM;
		ql_log(ql_log_info, vha, 0x70bc,
		    "Disabling Reset by IDC control\n");
		qla83xx_idc_lock(vha, 0);
		__qla83xx_get_idc_control(vha, &idc_control);
		idc_control |= QLA83XX_IDC_RESET_DISABLED;
		__qla83xx_set_idc_control(vha, idc_control);
		qla83xx_idc_unlock(vha, 0);
		अवरोध;
	हाल 0x20260:
		अगर (!IS_QLA8031(ha))
			वापस -EPERM;
		ql_log(ql_log_info, vha, 0x70bd,
		    "Enabling Reset by IDC control\n");
		qla83xx_idc_lock(vha, 0);
		__qla83xx_get_idc_control(vha, &idc_control);
		idc_control &= ~QLA83XX_IDC_RESET_DISABLED;
		__qla83xx_set_idc_control(vha, idc_control);
		qla83xx_idc_unlock(vha, 0);
		अवरोध;
	हाल 0x20261:
		ql_dbg(ql_dbg_user, vha, 0x70e0,
		    "Updating cache versions without reset ");

		पंचांगp_data = vदो_स्मृति(256);
		अगर (!पंचांगp_data) अणु
			ql_log(ql_log_warn, vha, 0x70e1,
			    "Unable to allocate memory for VPD information update.\n");
			वापस -ENOMEM;
		पूर्ण
		ha->isp_ops->get_flash_version(vha, पंचांगp_data);
		vमुक्त(पंचांगp_data);
		अवरोध;
	पूर्ण
	वापस count;
पूर्ण

अटल काष्ठा bin_attribute sysfs_reset_attr = अणु
	.attr = अणु
		.name = "reset",
		.mode = S_IWUSR,
	पूर्ण,
	.size = 0,
	.ग_लिखो = qla2x00_sysfs_ग_लिखो_reset,
पूर्ण;

अटल sमाप_प्रकार
qla2x00_issue_logo(काष्ठा file *filp, काष्ठा kobject *kobj,
			काष्ठा bin_attribute *bin_attr,
			अक्षर *buf, loff_t off, माप_प्रकार count)
अणु
	काष्ठा scsi_qla_host *vha = shost_priv(dev_to_shost(container_of(kobj,
	    काष्ठा device, kobj)));
	पूर्णांक type;
	port_id_t did;

	अगर (!capable(CAP_SYS_ADMIN))
		वापस 0;

	अगर (unlikely(pci_channel_offline(vha->hw->pdev)))
		वापस 0;

	अगर (qla2x00_chip_is_करोwn(vha))
		वापस 0;

	type = simple_म_से_दीर्घ(buf, शून्य, 10);

	did.b.करोमुख्य = (type & 0x00ff0000) >> 16;
	did.b.area = (type & 0x0000ff00) >> 8;
	did.b.al_pa = (type & 0x000000ff);

	ql_log(ql_log_info, vha, 0xd04d, "portid=%02x%02x%02x done\n",
	    did.b.करोमुख्य, did.b.area, did.b.al_pa);

	ql_log(ql_log_info, vha, 0x70e4, "%s: %d\n", __func__, type);

	qla24xx_els_dcmd_iocb(vha, ELS_DCMD_LOGO, did);
	वापस count;
पूर्ण

अटल काष्ठा bin_attribute sysfs_issue_logo_attr = अणु
	.attr = अणु
		.name = "issue_logo",
		.mode = S_IWUSR,
	पूर्ण,
	.size = 0,
	.ग_लिखो = qla2x00_issue_logo,
पूर्ण;

अटल sमाप_प्रकार
qla2x00_sysfs_पढ़ो_xgmac_stats(काष्ठा file *filp, काष्ठा kobject *kobj,
		       काष्ठा bin_attribute *bin_attr,
		       अक्षर *buf, loff_t off, माप_प्रकार count)
अणु
	काष्ठा scsi_qla_host *vha = shost_priv(dev_to_shost(container_of(kobj,
	    काष्ठा device, kobj)));
	काष्ठा qla_hw_data *ha = vha->hw;
	पूर्णांक rval;
	uपूर्णांक16_t actual_size;

	अगर (!capable(CAP_SYS_ADMIN) || off != 0 || count > XGMAC_DATA_SIZE)
		वापस 0;

	अगर (unlikely(pci_channel_offline(ha->pdev)))
		वापस 0;
	mutex_lock(&vha->hw->optrom_mutex);
	अगर (qla2x00_chip_is_करोwn(vha)) अणु
		mutex_unlock(&vha->hw->optrom_mutex);
		वापस 0;
	पूर्ण

	अगर (ha->xgmac_data)
		जाओ करो_पढ़ो;

	ha->xgmac_data = dma_alloc_coherent(&ha->pdev->dev, XGMAC_DATA_SIZE,
	    &ha->xgmac_data_dma, GFP_KERNEL);
	अगर (!ha->xgmac_data) अणु
		mutex_unlock(&vha->hw->optrom_mutex);
		ql_log(ql_log_warn, vha, 0x7076,
		    "Unable to allocate memory for XGMAC read-data.\n");
		वापस 0;
	पूर्ण

करो_पढ़ो:
	actual_size = 0;
	स_रखो(ha->xgmac_data, 0, XGMAC_DATA_SIZE);

	rval = qla2x00_get_xgmac_stats(vha, ha->xgmac_data_dma,
	    XGMAC_DATA_SIZE, &actual_size);

	mutex_unlock(&vha->hw->optrom_mutex);
	अगर (rval != QLA_SUCCESS) अणु
		ql_log(ql_log_warn, vha, 0x7077,
		    "Unable to read XGMAC data (%x).\n", rval);
		count = 0;
	पूर्ण

	count = actual_size > count ? count : actual_size;
	स_नकल(buf, ha->xgmac_data, count);

	वापस count;
पूर्ण

अटल काष्ठा bin_attribute sysfs_xgmac_stats_attr = अणु
	.attr = अणु
		.name = "xgmac_stats",
		.mode = S_IRUSR,
	पूर्ण,
	.size = 0,
	.पढ़ो = qla2x00_sysfs_पढ़ो_xgmac_stats,
पूर्ण;

अटल sमाप_प्रकार
qla2x00_sysfs_पढ़ो_dcbx_tlv(काष्ठा file *filp, काष्ठा kobject *kobj,
		       काष्ठा bin_attribute *bin_attr,
		       अक्षर *buf, loff_t off, माप_प्रकार count)
अणु
	काष्ठा scsi_qla_host *vha = shost_priv(dev_to_shost(container_of(kobj,
	    काष्ठा device, kobj)));
	काष्ठा qla_hw_data *ha = vha->hw;
	पूर्णांक rval;

	अगर (!capable(CAP_SYS_ADMIN) || off != 0 || count > DCBX_TLV_DATA_SIZE)
		वापस 0;

	अगर (ha->dcbx_tlv)
		जाओ करो_पढ़ो;
	mutex_lock(&vha->hw->optrom_mutex);
	अगर (qla2x00_chip_is_करोwn(vha)) अणु
		mutex_unlock(&vha->hw->optrom_mutex);
		वापस 0;
	पूर्ण

	ha->dcbx_tlv = dma_alloc_coherent(&ha->pdev->dev, DCBX_TLV_DATA_SIZE,
	    &ha->dcbx_tlv_dma, GFP_KERNEL);
	अगर (!ha->dcbx_tlv) अणु
		mutex_unlock(&vha->hw->optrom_mutex);
		ql_log(ql_log_warn, vha, 0x7078,
		    "Unable to allocate memory for DCBX TLV read-data.\n");
		वापस -ENOMEM;
	पूर्ण

करो_पढ़ो:
	स_रखो(ha->dcbx_tlv, 0, DCBX_TLV_DATA_SIZE);

	rval = qla2x00_get_dcbx_params(vha, ha->dcbx_tlv_dma,
	    DCBX_TLV_DATA_SIZE);

	mutex_unlock(&vha->hw->optrom_mutex);

	अगर (rval != QLA_SUCCESS) अणु
		ql_log(ql_log_warn, vha, 0x7079,
		    "Unable to read DCBX TLV (%x).\n", rval);
		वापस -EIO;
	पूर्ण

	स_नकल(buf, ha->dcbx_tlv, count);

	वापस count;
पूर्ण

अटल काष्ठा bin_attribute sysfs_dcbx_tlv_attr = अणु
	.attr = अणु
		.name = "dcbx_tlv",
		.mode = S_IRUSR,
	पूर्ण,
	.size = 0,
	.पढ़ो = qla2x00_sysfs_पढ़ो_dcbx_tlv,
पूर्ण;

अटल काष्ठा sysfs_entry अणु
	अक्षर *name;
	काष्ठा bin_attribute *attr;
	पूर्णांक type;
पूर्ण bin_file_entries[] = अणु
	अणु "fw_dump", &sysfs_fw_dump_attr, पूर्ण,
	अणु "nvram", &sysfs_nvram_attr, पूर्ण,
	अणु "optrom", &sysfs_optrom_attr, पूर्ण,
	अणु "optrom_ctl", &sysfs_optrom_ctl_attr, पूर्ण,
	अणु "vpd", &sysfs_vpd_attr, 1 पूर्ण,
	अणु "sfp", &sysfs_sfp_attr, 1 पूर्ण,
	अणु "reset", &sysfs_reset_attr, पूर्ण,
	अणु "issue_logo", &sysfs_issue_logo_attr, पूर्ण,
	अणु "xgmac_stats", &sysfs_xgmac_stats_attr, 3 पूर्ण,
	अणु "dcbx_tlv", &sysfs_dcbx_tlv_attr, 3 पूर्ण,
	अणु शून्य पूर्ण,
पूर्ण;

व्योम
qla2x00_alloc_sysfs_attr(scsi_qla_host_t *vha)
अणु
	काष्ठा Scsi_Host *host = vha->host;
	काष्ठा sysfs_entry *iter;
	पूर्णांक ret;

	क्रम (iter = bin_file_entries; iter->name; iter++) अणु
		अगर (iter->type && !IS_FWI2_CAPABLE(vha->hw))
			जारी;
		अगर (iter->type == 2 && !IS_QLA25XX(vha->hw))
			जारी;
		अगर (iter->type == 3 && !(IS_CNA_CAPABLE(vha->hw)))
			जारी;

		ret = sysfs_create_bin_file(&host->shost_gendev.kobj,
		    iter->attr);
		अगर (ret)
			ql_log(ql_log_warn, vha, 0x00f3,
			    "Unable to create sysfs %s binary attribute (%d).\n",
			    iter->name, ret);
		अन्यथा
			ql_dbg(ql_dbg_init, vha, 0x00f4,
			    "Successfully created sysfs %s binary attribute.\n",
			    iter->name);
	पूर्ण
पूर्ण

व्योम
qla2x00_मुक्त_sysfs_attr(scsi_qla_host_t *vha, bool stop_beacon)
अणु
	काष्ठा Scsi_Host *host = vha->host;
	काष्ठा sysfs_entry *iter;
	काष्ठा qla_hw_data *ha = vha->hw;

	क्रम (iter = bin_file_entries; iter->name; iter++) अणु
		अगर (iter->type && !IS_FWI2_CAPABLE(ha))
			जारी;
		अगर (iter->type == 2 && !IS_QLA25XX(ha))
			जारी;
		अगर (iter->type == 3 && !(IS_CNA_CAPABLE(ha)))
			जारी;
		अगर (iter->type == 0x27 &&
		    (!IS_QLA27XX(ha) || !IS_QLA28XX(ha)))
			जारी;

		sysfs_हटाओ_bin_file(&host->shost_gendev.kobj,
		    iter->attr);
	पूर्ण

	अगर (stop_beacon && ha->beacon_blink_led == 1)
		ha->isp_ops->beacon_off(vha);
पूर्ण

/* Scsi_Host attributes. */

अटल sमाप_प्रकार
qla2x00_driver_version_show(काष्ठा device *dev,
			  काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	वापस scnम_लिखो(buf, PAGE_SIZE, "%s\n", qla2x00_version_str);
पूर्ण

अटल sमाप_प्रकार
qla2x00_fw_version_show(काष्ठा device *dev,
			काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	scsi_qla_host_t *vha = shost_priv(class_to_shost(dev));
	काष्ठा qla_hw_data *ha = vha->hw;
	अक्षर fw_str[128];

	वापस scnम_लिखो(buf, PAGE_SIZE, "%s\n",
	    ha->isp_ops->fw_version_str(vha, fw_str, माप(fw_str)));
पूर्ण

अटल sमाप_प्रकार
qla2x00_serial_num_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			अक्षर *buf)
अणु
	scsi_qla_host_t *vha = shost_priv(class_to_shost(dev));
	काष्ठा qla_hw_data *ha = vha->hw;
	uपूर्णांक32_t sn;

	अगर (IS_QLAFX00(vha->hw)) अणु
		वापस scnम_लिखो(buf, PAGE_SIZE, "%s\n",
		    vha->hw->mr.serial_num);
	पूर्ण अन्यथा अगर (IS_FWI2_CAPABLE(ha)) अणु
		qla2xxx_get_vpd_field(vha, "SN", buf, PAGE_SIZE - 1);
		वापस म_माप(म_जोड़ो(buf, "\n"));
	पूर्ण

	sn = ((ha->serial0 & 0x1f) << 16) | (ha->serial2 << 8) | ha->serial1;
	वापस scnम_लिखो(buf, PAGE_SIZE, "%c%05d\n", 'A' + sn / 100000,
	    sn % 100000);
पूर्ण

अटल sमाप_प्रकार
qla2x00_isp_name_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
		      अक्षर *buf)
अणु
	scsi_qla_host_t *vha = shost_priv(class_to_shost(dev));

	वापस scnम_लिखो(buf, PAGE_SIZE, "ISP%04X\n", vha->hw->pdev->device);
पूर्ण

अटल sमाप_प्रकार
qla2x00_isp_id_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
		    अक्षर *buf)
अणु
	scsi_qla_host_t *vha = shost_priv(class_to_shost(dev));
	काष्ठा qla_hw_data *ha = vha->hw;

	अगर (IS_QLAFX00(vha->hw))
		वापस scnम_लिखो(buf, PAGE_SIZE, "%s\n",
		    vha->hw->mr.hw_version);

	वापस scnम_लिखो(buf, PAGE_SIZE, "%04x %04x %04x %04x\n",
	    ha->product_id[0], ha->product_id[1], ha->product_id[2],
	    ha->product_id[3]);
पूर्ण

अटल sमाप_प्रकार
qla2x00_model_name_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			अक्षर *buf)
अणु
	scsi_qla_host_t *vha = shost_priv(class_to_shost(dev));

	वापस scnम_लिखो(buf, PAGE_SIZE, "%s\n", vha->hw->model_number);
पूर्ण

अटल sमाप_प्रकार
qla2x00_model_desc_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			अक्षर *buf)
अणु
	scsi_qla_host_t *vha = shost_priv(class_to_shost(dev));

	वापस scnम_लिखो(buf, PAGE_SIZE, "%s\n", vha->hw->model_desc);
पूर्ण

अटल sमाप_प्रकार
qla2x00_pci_info_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
		      अक्षर *buf)
अणु
	scsi_qla_host_t *vha = shost_priv(class_to_shost(dev));
	अक्षर pci_info[30];

	वापस scnम_लिखो(buf, PAGE_SIZE, "%s\n",
			 vha->hw->isp_ops->pci_info_str(vha, pci_info,
							माप(pci_info)));
पूर्ण

अटल sमाप_प्रकार
qla2x00_link_state_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			अक्षर *buf)
अणु
	scsi_qla_host_t *vha = shost_priv(class_to_shost(dev));
	काष्ठा qla_hw_data *ha = vha->hw;
	पूर्णांक len = 0;

	अगर (atomic_पढ़ो(&vha->loop_state) == LOOP_DOWN ||
	    atomic_पढ़ो(&vha->loop_state) == LOOP_DEAD ||
	    vha->device_flags & DFLG_NO_CABLE)
		len = scnम_लिखो(buf, PAGE_SIZE, "Link Down\n");
	अन्यथा अगर (atomic_पढ़ो(&vha->loop_state) != LOOP_READY ||
	    qla2x00_chip_is_करोwn(vha))
		len = scnम_लिखो(buf, PAGE_SIZE, "Unknown Link State\n");
	अन्यथा अणु
		len = scnम_लिखो(buf, PAGE_SIZE, "Link Up - ");

		चयन (ha->current_topology) अणु
		हाल ISP_CFG_NL:
			len += scnम_लिखो(buf + len, PAGE_SIZE-len, "Loop\n");
			अवरोध;
		हाल ISP_CFG_FL:
			len += scnम_लिखो(buf + len, PAGE_SIZE-len, "FL_Port\n");
			अवरोध;
		हाल ISP_CFG_N:
			len += scnम_लिखो(buf + len, PAGE_SIZE-len,
			    "N_Port to N_Port\n");
			अवरोध;
		हाल ISP_CFG_F:
			len += scnम_लिखो(buf + len, PAGE_SIZE-len, "F_Port\n");
			अवरोध;
		शेष:
			len += scnम_लिखो(buf + len, PAGE_SIZE-len, "Loop\n");
			अवरोध;
		पूर्ण
	पूर्ण
	वापस len;
पूर्ण

अटल sमाप_प्रकार
qla2x00_zio_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
		 अक्षर *buf)
अणु
	scsi_qla_host_t *vha = shost_priv(class_to_shost(dev));
	पूर्णांक len = 0;

	चयन (vha->hw->zio_mode) अणु
	हाल QLA_ZIO_MODE_6:
		len += scnम_लिखो(buf + len, PAGE_SIZE-len, "Mode 6\n");
		अवरोध;
	हाल QLA_ZIO_DISABLED:
		len += scnम_लिखो(buf + len, PAGE_SIZE-len, "Disabled\n");
		अवरोध;
	पूर्ण
	वापस len;
पूर्ण

अटल sमाप_प्रकार
qla2x00_zio_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
		  स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	scsi_qla_host_t *vha = shost_priv(class_to_shost(dev));
	काष्ठा qla_hw_data *ha = vha->hw;
	पूर्णांक val = 0;
	uपूर्णांक16_t zio_mode;

	अगर (!IS_ZIO_SUPPORTED(ha))
		वापस -ENOTSUPP;

	अगर (माला_पूछो(buf, "%d", &val) != 1)
		वापस -EINVAL;

	अगर (val)
		zio_mode = QLA_ZIO_MODE_6;
	अन्यथा
		zio_mode = QLA_ZIO_DISABLED;

	/* Update per-hba values and queue a reset. */
	अगर (zio_mode != QLA_ZIO_DISABLED || ha->zio_mode != QLA_ZIO_DISABLED) अणु
		ha->zio_mode = zio_mode;
		set_bit(ISP_ABORT_NEEDED, &vha->dpc_flags);
	पूर्ण
	वापस म_माप(buf);
पूर्ण

अटल sमाप_प्रकार
qla2x00_zio_समयr_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
		       अक्षर *buf)
अणु
	scsi_qla_host_t *vha = shost_priv(class_to_shost(dev));

	वापस scnम_लिखो(buf, PAGE_SIZE, "%d us\n", vha->hw->zio_समयr * 100);
पूर्ण

अटल sमाप_प्रकार
qla2x00_zio_समयr_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
			स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	scsi_qla_host_t *vha = shost_priv(class_to_shost(dev));
	पूर्णांक val = 0;
	uपूर्णांक16_t zio_समयr;

	अगर (माला_पूछो(buf, "%d", &val) != 1)
		वापस -EINVAL;
	अगर (val > 25500 || val < 100)
		वापस -दुस्फल;

	zio_समयr = (uपूर्णांक16_t)(val / 100);
	vha->hw->zio_समयr = zio_समयr;

	वापस म_माप(buf);
पूर्ण

अटल sमाप_प्रकार
qla_zio_threshold_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
		       अक्षर *buf)
अणु
	scsi_qla_host_t *vha = shost_priv(class_to_shost(dev));

	वापस scnम_लिखो(buf, PAGE_SIZE, "%d exchanges\n",
	    vha->hw->last_zio_threshold);
पूर्ण

अटल sमाप_प्रकार
qla_zio_threshold_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
    स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	scsi_qla_host_t *vha = shost_priv(class_to_shost(dev));
	पूर्णांक val = 0;

	अगर (vha->hw->zio_mode != QLA_ZIO_MODE_6)
		वापस -EINVAL;
	अगर (माला_पूछो(buf, "%d", &val) != 1)
		वापस -EINVAL;
	अगर (val < 0 || val > 256)
		वापस -दुस्फल;

	atomic_set(&vha->hw->zio_threshold, val);
	वापस म_माप(buf);
पूर्ण

अटल sमाप_प्रकार
qla2x00_beacon_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
		    अक्षर *buf)
अणु
	scsi_qla_host_t *vha = shost_priv(class_to_shost(dev));
	पूर्णांक len = 0;

	अगर (vha->hw->beacon_blink_led)
		len += scnम_लिखो(buf + len, PAGE_SIZE-len, "Enabled\n");
	अन्यथा
		len += scnम_लिखो(buf + len, PAGE_SIZE-len, "Disabled\n");
	वापस len;
पूर्ण

अटल sमाप_प्रकार
qla2x00_beacon_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
		     स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	scsi_qla_host_t *vha = shost_priv(class_to_shost(dev));
	काष्ठा qla_hw_data *ha = vha->hw;
	पूर्णांक val = 0;
	पूर्णांक rval;

	अगर (IS_QLA2100(ha) || IS_QLA2200(ha))
		वापस -EPERM;

	अगर (माला_पूछो(buf, "%d", &val) != 1)
		वापस -EINVAL;

	mutex_lock(&vha->hw->optrom_mutex);
	अगर (qla2x00_chip_is_करोwn(vha)) अणु
		mutex_unlock(&vha->hw->optrom_mutex);
		ql_log(ql_log_warn, vha, 0x707a,
		    "Abort ISP active -- ignoring beacon request.\n");
		वापस -EBUSY;
	पूर्ण

	अगर (val)
		rval = ha->isp_ops->beacon_on(vha);
	अन्यथा
		rval = ha->isp_ops->beacon_off(vha);

	अगर (rval != QLA_SUCCESS)
		count = 0;

	mutex_unlock(&vha->hw->optrom_mutex);

	वापस count;
पूर्ण

अटल sमाप_प्रकार
qla2x00_beacon_config_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
	अक्षर *buf)
अणु
	scsi_qla_host_t *vha = shost_priv(class_to_shost(dev));
	काष्ठा qla_hw_data *ha = vha->hw;
	uपूर्णांक16_t led[3] = अणु 0 पूर्ण;

	अगर (!IS_QLA2031(ha) && !IS_QLA27XX(ha) && !IS_QLA28XX(ha))
		वापस -EPERM;

	अगर (ql26xx_led_config(vha, 0, led))
		वापस scnम_लिखो(buf, PAGE_SIZE, "\n");

	वापस scnम_लिखो(buf, PAGE_SIZE, "%#04hx %#04hx %#04hx\n",
	    led[0], led[1], led[2]);
पूर्ण

अटल sमाप_प्रकार
qla2x00_beacon_config_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
	स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	scsi_qla_host_t *vha = shost_priv(class_to_shost(dev));
	काष्ठा qla_hw_data *ha = vha->hw;
	uपूर्णांक16_t options = BIT_0;
	uपूर्णांक16_t led[3] = अणु 0 पूर्ण;
	uपूर्णांक16_t word[4];
	पूर्णांक n;

	अगर (!IS_QLA2031(ha) && !IS_QLA27XX(ha) && !IS_QLA28XX(ha))
		वापस -EPERM;

	n = माला_पूछो(buf, "%hx %hx %hx %hx", word+0, word+1, word+2, word+3);
	अगर (n == 4) अणु
		अगर (word[0] == 3) अणु
			options |= BIT_3|BIT_2|BIT_1;
			led[0] = word[1];
			led[1] = word[2];
			led[2] = word[3];
			जाओ ग_लिखो;
		पूर्ण
		वापस -EINVAL;
	पूर्ण

	अगर (n == 2) अणु
		/* check led index */
		अगर (word[0] == 0) अणु
			options |= BIT_2;
			led[0] = word[1];
			जाओ ग_लिखो;
		पूर्ण
		अगर (word[0] == 1) अणु
			options |= BIT_3;
			led[1] = word[1];
			जाओ ग_लिखो;
		पूर्ण
		अगर (word[0] == 2) अणु
			options |= BIT_1;
			led[2] = word[1];
			जाओ ग_लिखो;
		पूर्ण
		वापस -EINVAL;
	पूर्ण

	वापस -EINVAL;

ग_लिखो:
	अगर (ql26xx_led_config(vha, options, led))
		वापस -EFAULT;

	वापस count;
पूर्ण

अटल sमाप_प्रकार
qla2x00_optrom_bios_version_show(काष्ठा device *dev,
				 काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	scsi_qla_host_t *vha = shost_priv(class_to_shost(dev));
	काष्ठा qla_hw_data *ha = vha->hw;

	वापस scnम_लिखो(buf, PAGE_SIZE, "%d.%02d\n", ha->bios_revision[1],
	    ha->bios_revision[0]);
पूर्ण

अटल sमाप_प्रकार
qla2x00_optrom_efi_version_show(काष्ठा device *dev,
				काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	scsi_qla_host_t *vha = shost_priv(class_to_shost(dev));
	काष्ठा qla_hw_data *ha = vha->hw;

	वापस scnम_लिखो(buf, PAGE_SIZE, "%d.%02d\n", ha->efi_revision[1],
	    ha->efi_revision[0]);
पूर्ण

अटल sमाप_प्रकार
qla2x00_optrom_fcode_version_show(काष्ठा device *dev,
				  काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	scsi_qla_host_t *vha = shost_priv(class_to_shost(dev));
	काष्ठा qla_hw_data *ha = vha->hw;

	वापस scnम_लिखो(buf, PAGE_SIZE, "%d.%02d\n", ha->fcode_revision[1],
	    ha->fcode_revision[0]);
पूर्ण

अटल sमाप_प्रकार
qla2x00_optrom_fw_version_show(काष्ठा device *dev,
			       काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	scsi_qla_host_t *vha = shost_priv(class_to_shost(dev));
	काष्ठा qla_hw_data *ha = vha->hw;

	वापस scnम_लिखो(buf, PAGE_SIZE, "%d.%02d.%02d %d\n",
	    ha->fw_revision[0], ha->fw_revision[1], ha->fw_revision[2],
	    ha->fw_revision[3]);
पूर्ण

अटल sमाप_प्रकार
qla2x00_optrom_gold_fw_version_show(काष्ठा device *dev,
    काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	scsi_qla_host_t *vha = shost_priv(class_to_shost(dev));
	काष्ठा qla_hw_data *ha = vha->hw;

	अगर (!IS_QLA81XX(ha) && !IS_QLA83XX(ha) &&
	    !IS_QLA27XX(ha) && !IS_QLA28XX(ha))
		वापस scnम_लिखो(buf, PAGE_SIZE, "\n");

	वापस scnम_लिखो(buf, PAGE_SIZE, "%d.%02d.%02d (%d)\n",
	    ha->gold_fw_version[0], ha->gold_fw_version[1],
	    ha->gold_fw_version[2], ha->gold_fw_version[3]);
पूर्ण

अटल sमाप_प्रकार
qla2x00_total_isp_पातs_show(काष्ठा device *dev,
			      काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	scsi_qla_host_t *vha = shost_priv(class_to_shost(dev));

	वापस scnम_लिखो(buf, PAGE_SIZE, "%d\n",
	    vha->qla_stats.total_isp_पातs);
पूर्ण

अटल sमाप_प्रकार
qla24xx_84xx_fw_version_show(काष्ठा device *dev,
	काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	पूर्णांक rval = QLA_SUCCESS;
	uपूर्णांक16_t status[2] = अणु 0 पूर्ण;
	scsi_qla_host_t *vha = shost_priv(class_to_shost(dev));
	काष्ठा qla_hw_data *ha = vha->hw;

	अगर (!IS_QLA84XX(ha))
		वापस scnम_लिखो(buf, PAGE_SIZE, "\n");

	अगर (!ha->cs84xx->op_fw_version) अणु
		rval = qla84xx_verअगरy_chip(vha, status);

		अगर (!rval && !status[0])
			वापस scnम_लिखो(buf, PAGE_SIZE, "%u\n",
			    (uपूर्णांक32_t)ha->cs84xx->op_fw_version);
	पूर्ण

	वापस scnम_लिखो(buf, PAGE_SIZE, "\n");
पूर्ण

अटल sमाप_प्रकार
qla2x00_serdes_version_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
    अक्षर *buf)
अणु
	scsi_qla_host_t *vha = shost_priv(class_to_shost(dev));
	काष्ठा qla_hw_data *ha = vha->hw;

	अगर (!IS_QLA27XX(ha) && !IS_QLA28XX(ha))
		वापस scnम_लिखो(buf, PAGE_SIZE, "\n");

	वापस scnम_लिखो(buf, PAGE_SIZE, "%d.%02d.%02d\n",
	    ha->serdes_version[0], ha->serdes_version[1],
	    ha->serdes_version[2]);
पूर्ण

अटल sमाप_प्रकार
qla2x00_mpi_version_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
    अक्षर *buf)
अणु
	scsi_qla_host_t *vha = shost_priv(class_to_shost(dev));
	काष्ठा qla_hw_data *ha = vha->hw;

	अगर (!IS_QLA81XX(ha) && !IS_QLA8031(ha) && !IS_QLA8044(ha) &&
	    !IS_QLA27XX(ha) && !IS_QLA28XX(ha))
		वापस scnम_लिखो(buf, PAGE_SIZE, "\n");

	वापस scnम_लिखो(buf, PAGE_SIZE, "%d.%02d.%02d (%x)\n",
	    ha->mpi_version[0], ha->mpi_version[1], ha->mpi_version[2],
	    ha->mpi_capabilities);
पूर्ण

अटल sमाप_प्रकार
qla2x00_phy_version_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
    अक्षर *buf)
अणु
	scsi_qla_host_t *vha = shost_priv(class_to_shost(dev));
	काष्ठा qla_hw_data *ha = vha->hw;

	अगर (!IS_QLA81XX(ha) && !IS_QLA8031(ha))
		वापस scnम_लिखो(buf, PAGE_SIZE, "\n");

	वापस scnम_लिखो(buf, PAGE_SIZE, "%d.%02d.%02d\n",
	    ha->phy_version[0], ha->phy_version[1], ha->phy_version[2]);
पूर्ण

अटल sमाप_प्रकार
qla2x00_flash_block_size_show(काष्ठा device *dev,
			      काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	scsi_qla_host_t *vha = shost_priv(class_to_shost(dev));
	काष्ठा qla_hw_data *ha = vha->hw;

	वापस scnम_लिखो(buf, PAGE_SIZE, "0x%x\n", ha->fdt_block_size);
पूर्ण

अटल sमाप_प्रकार
qla2x00_vlan_id_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
    अक्षर *buf)
अणु
	scsi_qla_host_t *vha = shost_priv(class_to_shost(dev));

	अगर (!IS_CNA_CAPABLE(vha->hw))
		वापस scnम_लिखो(buf, PAGE_SIZE, "\n");

	वापस scnम_लिखो(buf, PAGE_SIZE, "%d\n", vha->fcoe_vlan_id);
पूर्ण

अटल sमाप_प्रकार
qla2x00_vn_port_mac_address_show(काष्ठा device *dev,
    काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	scsi_qla_host_t *vha = shost_priv(class_to_shost(dev));

	अगर (!IS_CNA_CAPABLE(vha->hw))
		वापस scnम_लिखो(buf, PAGE_SIZE, "\n");

	वापस scnम_लिखो(buf, PAGE_SIZE, "%pMR\n", vha->fcoe_vn_port_mac);
पूर्ण

अटल sमाप_प्रकार
qla2x00_fabric_param_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
    अक्षर *buf)
अणु
	scsi_qla_host_t *vha = shost_priv(class_to_shost(dev));

	वापस scnम_लिखो(buf, PAGE_SIZE, "%d\n", vha->hw->चयन_cap);
पूर्ण

अटल sमाप_प्रकार
qla2x00_thermal_temp_show(काष्ठा device *dev,
	काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	scsi_qla_host_t *vha = shost_priv(class_to_shost(dev));
	uपूर्णांक16_t temp = 0;
	पूर्णांक rc;

	mutex_lock(&vha->hw->optrom_mutex);
	अगर (qla2x00_chip_is_करोwn(vha)) अणु
		mutex_unlock(&vha->hw->optrom_mutex);
		ql_log(ql_log_warn, vha, 0x70dc, "ISP reset active.\n");
		जाओ करोne;
	पूर्ण

	अगर (vha->hw->flags.eeh_busy) अणु
		mutex_unlock(&vha->hw->optrom_mutex);
		ql_log(ql_log_warn, vha, 0x70dd, "PCI EEH busy.\n");
		जाओ करोne;
	पूर्ण

	rc = qla2x00_get_thermal_temp(vha, &temp);
	mutex_unlock(&vha->hw->optrom_mutex);
	अगर (rc == QLA_SUCCESS)
		वापस scnम_लिखो(buf, PAGE_SIZE, "%d\n", temp);

करोne:
	वापस scnम_लिखो(buf, PAGE_SIZE, "\n");
पूर्ण

अटल sमाप_प्रकार
qla2x00_fw_state_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
    अक्षर *buf)
अणु
	scsi_qla_host_t *vha = shost_priv(class_to_shost(dev));
	पूर्णांक rval = QLA_FUNCTION_FAILED;
	uपूर्णांक16_t state[6];
	uपूर्णांक32_t pstate;

	अगर (IS_QLAFX00(vha->hw)) अणु
		pstate = qlafx00_fw_state_show(dev, attr, buf);
		वापस scnम_लिखो(buf, PAGE_SIZE, "0x%x\n", pstate);
	पूर्ण

	mutex_lock(&vha->hw->optrom_mutex);
	अगर (qla2x00_chip_is_करोwn(vha)) अणु
		mutex_unlock(&vha->hw->optrom_mutex);
		ql_log(ql_log_warn, vha, 0x707c,
		    "ISP reset active.\n");
		जाओ out;
	पूर्ण अन्यथा अगर (vha->hw->flags.eeh_busy) अणु
		mutex_unlock(&vha->hw->optrom_mutex);
		जाओ out;
	पूर्ण

	rval = qla2x00_get_firmware_state(vha, state);
	mutex_unlock(&vha->hw->optrom_mutex);
out:
	अगर (rval != QLA_SUCCESS) अणु
		स_रखो(state, -1, माप(state));
		rval = qla2x00_get_firmware_state(vha, state);
	पूर्ण

	वापस scnम_लिखो(buf, PAGE_SIZE, "0x%x 0x%x 0x%x 0x%x 0x%x 0x%x\n",
	    state[0], state[1], state[2], state[3], state[4], state[5]);
पूर्ण

अटल sमाप_प्रकार
qla2x00_diag_requests_show(काष्ठा device *dev,
	काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	scsi_qla_host_t *vha = shost_priv(class_to_shost(dev));

	अगर (!IS_BIDI_CAPABLE(vha->hw))
		वापस scnम_लिखो(buf, PAGE_SIZE, "\n");

	वापस scnम_लिखो(buf, PAGE_SIZE, "%llu\n", vha->bidi_stats.io_count);
पूर्ण

अटल sमाप_प्रकार
qla2x00_diag_megabytes_show(काष्ठा device *dev,
	काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	scsi_qla_host_t *vha = shost_priv(class_to_shost(dev));

	अगर (!IS_BIDI_CAPABLE(vha->hw))
		वापस scnम_लिखो(buf, PAGE_SIZE, "\n");

	वापस scnम_लिखो(buf, PAGE_SIZE, "%llu\n",
	    vha->bidi_stats.transfer_bytes >> 20);
पूर्ण

अटल sमाप_प्रकार
qla2x00_fw_dump_size_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
	अक्षर *buf)
अणु
	scsi_qla_host_t *vha = shost_priv(class_to_shost(dev));
	काष्ठा qla_hw_data *ha = vha->hw;
	uपूर्णांक32_t size;

	अगर (!ha->fw_dumped)
		size = 0;
	अन्यथा अगर (IS_P3P_TYPE(ha))
		size = ha->md_ढाँचा_size + ha->md_dump_size;
	अन्यथा
		size = ha->fw_dump_len;

	वापस scnम_लिखो(buf, PAGE_SIZE, "%d\n", size);
पूर्ण

अटल sमाप_प्रकार
qla2x00_allow_cna_fw_dump_show(काष्ठा device *dev,
	काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	scsi_qla_host_t *vha = shost_priv(class_to_shost(dev));

	अगर (!IS_P3P_TYPE(vha->hw))
		वापस scnम_लिखो(buf, PAGE_SIZE, "\n");
	अन्यथा
		वापस scnम_लिखो(buf, PAGE_SIZE, "%s\n",
		    vha->hw->allow_cna_fw_dump ? "true" : "false");
पूर्ण

अटल sमाप_प्रकार
qla2x00_allow_cna_fw_dump_store(काष्ठा device *dev,
	काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	scsi_qla_host_t *vha = shost_priv(class_to_shost(dev));
	पूर्णांक val = 0;

	अगर (!IS_P3P_TYPE(vha->hw))
		वापस -EINVAL;

	अगर (माला_पूछो(buf, "%d", &val) != 1)
		वापस -EINVAL;

	vha->hw->allow_cna_fw_dump = val != 0;

	वापस म_माप(buf);
पूर्ण

अटल sमाप_प्रकार
qla2x00_pep_version_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
	अक्षर *buf)
अणु
	scsi_qla_host_t *vha = shost_priv(class_to_shost(dev));
	काष्ठा qla_hw_data *ha = vha->hw;

	अगर (!IS_QLA27XX(ha) && !IS_QLA28XX(ha))
		वापस scnम_लिखो(buf, PAGE_SIZE, "\n");

	वापस scnम_लिखो(buf, PAGE_SIZE, "%d.%02d.%02d\n",
	    ha->pep_version[0], ha->pep_version[1], ha->pep_version[2]);
पूर्ण

अटल sमाप_प्रकार
qla2x00_min_supported_speed_show(काष्ठा device *dev,
    काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	scsi_qla_host_t *vha = shost_priv(class_to_shost(dev));
	काष्ठा qla_hw_data *ha = vha->hw;

	अगर (!IS_QLA27XX(ha) && !IS_QLA28XX(ha))
		वापस scnम_लिखो(buf, PAGE_SIZE, "\n");

	वापस scnम_लिखो(buf, PAGE_SIZE, "%s\n",
	    ha->min_supported_speed == 6 ? "64Gps" :
	    ha->min_supported_speed == 5 ? "32Gps" :
	    ha->min_supported_speed == 4 ? "16Gps" :
	    ha->min_supported_speed == 3 ? "8Gps" :
	    ha->min_supported_speed == 2 ? "4Gps" :
	    ha->min_supported_speed != 0 ? "unknown" : "");
पूर्ण

अटल sमाप_प्रकार
qla2x00_max_supported_speed_show(काष्ठा device *dev,
    काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	scsi_qla_host_t *vha = shost_priv(class_to_shost(dev));
	काष्ठा qla_hw_data *ha = vha->hw;

	अगर (!IS_QLA27XX(ha) && !IS_QLA28XX(ha))
		वापस scnम_लिखो(buf, PAGE_SIZE, "\n");

	वापस scnम_लिखो(buf, PAGE_SIZE, "%s\n",
	    ha->max_supported_speed  == 2 ? "64Gps" :
	    ha->max_supported_speed  == 1 ? "32Gps" :
	    ha->max_supported_speed  == 0 ? "16Gps" : "unknown");
पूर्ण

अटल sमाप_प्रकार
qla2x00_port_speed_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
    स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा scsi_qla_host *vha = shost_priv(dev_to_shost(dev));
	uदीर्घ type, speed;
	पूर्णांक oldspeed, rval;
	पूर्णांक mode = QLA_SET_DATA_RATE_LR;
	काष्ठा qla_hw_data *ha = vha->hw;

	अगर (!IS_QLA27XX(ha) && !IS_QLA28XX(ha)) अणु
		ql_log(ql_log_warn, vha, 0x70d8,
		    "Speed setting not supported \n");
		वापस -EINVAL;
	पूर्ण

	rval = kम_से_दीर्घ(buf, 10, &type);
	अगर (rval)
		वापस rval;
	speed = type;
	अगर (type == 40 || type == 80 || type == 160 ||
	    type == 320) अणु
		ql_dbg(ql_dbg_user, vha, 0x70d9,
		    "Setting will be affected after a loss of sync\n");
		type = type/10;
		mode = QLA_SET_DATA_RATE_NOLR;
	पूर्ण

	oldspeed = ha->set_data_rate;

	चयन (type) अणु
	हाल 0:
		ha->set_data_rate = PORT_SPEED_AUTO;
		अवरोध;
	हाल 4:
		ha->set_data_rate = PORT_SPEED_4GB;
		अवरोध;
	हाल 8:
		ha->set_data_rate = PORT_SPEED_8GB;
		अवरोध;
	हाल 16:
		ha->set_data_rate = PORT_SPEED_16GB;
		अवरोध;
	हाल 32:
		ha->set_data_rate = PORT_SPEED_32GB;
		अवरोध;
	शेष:
		ql_log(ql_log_warn, vha, 0x1199,
		    "Unrecognized speed setting:%lx. Setting Autoneg\n",
		    speed);
		ha->set_data_rate = PORT_SPEED_AUTO;
	पूर्ण

	अगर (qla2x00_chip_is_करोwn(vha) || (oldspeed == ha->set_data_rate))
		वापस -EINVAL;

	ql_log(ql_log_info, vha, 0x70da,
	    "Setting speed to %lx Gbps \n", type);

	rval = qla2x00_set_data_rate(vha, mode);
	अगर (rval != QLA_SUCCESS)
		वापस -EIO;

	वापस म_माप(buf);
पूर्ण

अटल sमाप_प्रकार
qla2x00_port_speed_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
    अक्षर *buf)
अणु
	काष्ठा scsi_qla_host *vha = shost_priv(dev_to_shost(dev));
	काष्ठा qla_hw_data *ha = vha->hw;
	sमाप_प्रकार rval;
	अक्षर *spd[7] = अणु"0", "0", "0", "4", "8", "16", "32"पूर्ण;

	rval = qla2x00_get_data_rate(vha);
	अगर (rval != QLA_SUCCESS) अणु
		ql_log(ql_log_warn, vha, 0x70db,
		    "Unable to get port speed rval:%zd\n", rval);
		वापस -EINVAL;
	पूर्ण

	वापस scnम_लिखो(buf, PAGE_SIZE, "%s\n", spd[ha->link_data_rate]);
पूर्ण

/* ----- */

अटल sमाप_प्रकार
qlini_mode_show(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	scsi_qla_host_t *vha = shost_priv(class_to_shost(dev));
	पूर्णांक len = 0;

	len += scnम_लिखो(buf + len, PAGE_SIZE-len,
	    "Supported options: enabled | disabled | dual | exclusive\n");

	/* --- */
	len += scnम_लिखो(buf + len, PAGE_SIZE-len, "Current selection: ");

	चयन (vha->qlini_mode) अणु
	हाल QLA2XXX_INI_MODE_EXCLUSIVE:
		len += scnम_लिखो(buf + len, PAGE_SIZE-len,
		    QLA2XXX_INI_MODE_STR_EXCLUSIVE);
		अवरोध;
	हाल QLA2XXX_INI_MODE_DISABLED:
		len += scnम_लिखो(buf + len, PAGE_SIZE-len,
		    QLA2XXX_INI_MODE_STR_DISABLED);
		अवरोध;
	हाल QLA2XXX_INI_MODE_ENABLED:
		len += scnम_लिखो(buf + len, PAGE_SIZE-len,
		    QLA2XXX_INI_MODE_STR_ENABLED);
		अवरोध;
	हाल QLA2XXX_INI_MODE_DUAL:
		len += scnम_लिखो(buf + len, PAGE_SIZE-len,
		    QLA2XXX_INI_MODE_STR_DUAL);
		अवरोध;
	पूर्ण
	len += scnम_लिखो(buf + len, PAGE_SIZE-len, "\n");

	वापस len;
पूर्ण

अटल अक्षर *mode_to_str[] = अणु
	"exclusive",
	"disabled",
	"enabled",
	"dual",
पूर्ण;

#घोषणा NEED_EXCH_OFFLOAD(_exchg) ((_exchg) > FW_DEF_EXCHANGES_CNT)
अटल व्योम qla_set_ini_mode(scsi_qla_host_t *vha, पूर्णांक op)
अणु
	क्रमागत अणु
		NO_ACTION,
		MODE_CHANGE_ACCEPT,
		MODE_CHANGE_NO_ACTION,
		TARGET_STILL_ACTIVE,
	पूर्ण;
	पूर्णांक action = NO_ACTION;
	पूर्णांक set_mode = 0;
	u8  eo_toggle = 0;	/* exchange offload flipped */

	चयन (vha->qlini_mode) अणु
	हाल QLA2XXX_INI_MODE_DISABLED:
		चयन (op) अणु
		हाल QLA2XXX_INI_MODE_DISABLED:
			अगर (qla_tgt_mode_enabled(vha)) अणु
				अगर (NEED_EXCH_OFFLOAD(vha->u_ql2xexchoffld) !=
				    vha->hw->flags.exchoffld_enabled)
					eo_toggle = 1;
				अगर (((vha->ql2xexchoffld !=
				    vha->u_ql2xexchoffld) &&
				    NEED_EXCH_OFFLOAD(vha->u_ql2xexchoffld)) ||
				    eo_toggle) अणु
					/*
					 * The number of exchange to be offload
					 * was tweaked or offload option was
					 * flipped
					 */
					action = MODE_CHANGE_ACCEPT;
				पूर्ण अन्यथा अणु
					action = MODE_CHANGE_NO_ACTION;
				पूर्ण
			पूर्ण अन्यथा अणु
				action = MODE_CHANGE_NO_ACTION;
			पूर्ण
			अवरोध;
		हाल QLA2XXX_INI_MODE_EXCLUSIVE:
			अगर (qla_tgt_mode_enabled(vha)) अणु
				अगर (NEED_EXCH_OFFLOAD(vha->u_ql2xexchoffld) !=
				    vha->hw->flags.exchoffld_enabled)
					eo_toggle = 1;
				अगर (((vha->ql2xexchoffld !=
				    vha->u_ql2xexchoffld) &&
				    NEED_EXCH_OFFLOAD(vha->u_ql2xexchoffld)) ||
				    eo_toggle) अणु
					/*
					 * The number of exchange to be offload
					 * was tweaked or offload option was
					 * flipped
					 */
					action = MODE_CHANGE_ACCEPT;
				पूर्ण अन्यथा अणु
					action = MODE_CHANGE_NO_ACTION;
				पूर्ण
			पूर्ण अन्यथा अणु
				action = MODE_CHANGE_ACCEPT;
			पूर्ण
			अवरोध;
		हाल QLA2XXX_INI_MODE_DUAL:
			action = MODE_CHANGE_ACCEPT;
			/* active_mode is target only, reset it to dual */
			अगर (qla_tgt_mode_enabled(vha)) अणु
				set_mode = 1;
				action = MODE_CHANGE_ACCEPT;
			पूर्ण अन्यथा अणु
				action = MODE_CHANGE_NO_ACTION;
			पूर्ण
			अवरोध;

		हाल QLA2XXX_INI_MODE_ENABLED:
			अगर (qla_tgt_mode_enabled(vha))
				action = TARGET_STILL_ACTIVE;
			अन्यथा अणु
				action = MODE_CHANGE_ACCEPT;
				set_mode = 1;
			पूर्ण
			अवरोध;
		पूर्ण
		अवरोध;

	हाल QLA2XXX_INI_MODE_EXCLUSIVE:
		चयन (op) अणु
		हाल QLA2XXX_INI_MODE_EXCLUSIVE:
			अगर (qla_tgt_mode_enabled(vha)) अणु
				अगर (NEED_EXCH_OFFLOAD(vha->u_ql2xexchoffld) !=
				    vha->hw->flags.exchoffld_enabled)
					eo_toggle = 1;
				अगर (((vha->ql2xexchoffld !=
				    vha->u_ql2xexchoffld) &&
				    NEED_EXCH_OFFLOAD(vha->u_ql2xexchoffld)) ||
				    eo_toggle)
					/*
					 * The number of exchange to be offload
					 * was tweaked or offload option was
					 * flipped
					 */
					action = MODE_CHANGE_ACCEPT;
				अन्यथा
					action = NO_ACTION;
			पूर्ण अन्यथा
				action = NO_ACTION;

			अवरोध;

		हाल QLA2XXX_INI_MODE_DISABLED:
			अगर (qla_tgt_mode_enabled(vha)) अणु
				अगर (NEED_EXCH_OFFLOAD(vha->u_ql2xexchoffld) !=
				    vha->hw->flags.exchoffld_enabled)
					eo_toggle = 1;
				अगर (((vha->ql2xexchoffld !=
				      vha->u_ql2xexchoffld) &&
				    NEED_EXCH_OFFLOAD(vha->u_ql2xexchoffld)) ||
				    eo_toggle)
					action = MODE_CHANGE_ACCEPT;
				अन्यथा
					action = MODE_CHANGE_NO_ACTION;
			पूर्ण अन्यथा
				action = MODE_CHANGE_NO_ACTION;
			अवरोध;

		हाल QLA2XXX_INI_MODE_DUAL: /* exclusive -> dual */
			अगर (qla_tgt_mode_enabled(vha)) अणु
				action = MODE_CHANGE_ACCEPT;
				set_mode = 1;
			पूर्ण अन्यथा
				action = MODE_CHANGE_ACCEPT;
			अवरोध;

		हाल QLA2XXX_INI_MODE_ENABLED:
			अगर (qla_tgt_mode_enabled(vha))
				action = TARGET_STILL_ACTIVE;
			अन्यथा अणु
				अगर (vha->hw->flags.fw_started)
					action = MODE_CHANGE_NO_ACTION;
				अन्यथा
					action = MODE_CHANGE_ACCEPT;
			पूर्ण
			अवरोध;
		पूर्ण
		अवरोध;

	हाल QLA2XXX_INI_MODE_ENABLED:
		चयन (op) अणु
		हाल QLA2XXX_INI_MODE_ENABLED:
			अगर (NEED_EXCH_OFFLOAD(vha->u_ql2xiniexchg) !=
			    vha->hw->flags.exchoffld_enabled)
				eo_toggle = 1;
			अगर (((vha->ql2xiniexchg != vha->u_ql2xiniexchg) &&
				NEED_EXCH_OFFLOAD(vha->u_ql2xiniexchg)) ||
			    eo_toggle)
				action = MODE_CHANGE_ACCEPT;
			अन्यथा
				action = NO_ACTION;
			अवरोध;
		हाल QLA2XXX_INI_MODE_DUAL:
		हाल QLA2XXX_INI_MODE_DISABLED:
			action = MODE_CHANGE_ACCEPT;
			अवरोध;
		शेष:
			action = MODE_CHANGE_NO_ACTION;
			अवरोध;
		पूर्ण
		अवरोध;

	हाल QLA2XXX_INI_MODE_DUAL:
		चयन (op) अणु
		हाल QLA2XXX_INI_MODE_DUAL:
			अगर (qla_tgt_mode_enabled(vha) ||
			    qla_dual_mode_enabled(vha)) अणु
				अगर (NEED_EXCH_OFFLOAD(vha->u_ql2xexchoffld +
					vha->u_ql2xiniexchg) !=
				    vha->hw->flags.exchoffld_enabled)
					eo_toggle = 1;

				अगर ((((vha->ql2xexchoffld +
				       vha->ql2xiniexchg) !=
				    (vha->u_ql2xiniexchg +
				     vha->u_ql2xexchoffld)) &&
				    NEED_EXCH_OFFLOAD(vha->u_ql2xiniexchg +
					vha->u_ql2xexchoffld)) || eo_toggle)
					action = MODE_CHANGE_ACCEPT;
				अन्यथा
					action = NO_ACTION;
			पूर्ण अन्यथा अणु
				अगर (NEED_EXCH_OFFLOAD(vha->u_ql2xexchoffld +
					vha->u_ql2xiniexchg) !=
				    vha->hw->flags.exchoffld_enabled)
					eo_toggle = 1;

				अगर ((((vha->ql2xexchoffld + vha->ql2xiniexchg)
				    != (vha->u_ql2xiniexchg +
					vha->u_ql2xexchoffld)) &&
				    NEED_EXCH_OFFLOAD(vha->u_ql2xiniexchg +
					vha->u_ql2xexchoffld)) || eo_toggle)
					action = MODE_CHANGE_NO_ACTION;
				अन्यथा
					action = NO_ACTION;
			पूर्ण
			अवरोध;

		हाल QLA2XXX_INI_MODE_DISABLED:
			अगर (qla_tgt_mode_enabled(vha) ||
			    qla_dual_mode_enabled(vha)) अणु
				/* turning off initiator mode */
				set_mode = 1;
				action = MODE_CHANGE_ACCEPT;
			पूर्ण अन्यथा अणु
				action = MODE_CHANGE_NO_ACTION;
			पूर्ण
			अवरोध;

		हाल QLA2XXX_INI_MODE_EXCLUSIVE:
			अगर (qla_tgt_mode_enabled(vha) ||
			    qla_dual_mode_enabled(vha)) अणु
				set_mode = 1;
				action = MODE_CHANGE_ACCEPT;
			पूर्ण अन्यथा अणु
				action = MODE_CHANGE_ACCEPT;
			पूर्ण
			अवरोध;

		हाल QLA2XXX_INI_MODE_ENABLED:
			अगर (qla_tgt_mode_enabled(vha) ||
			    qla_dual_mode_enabled(vha)) अणु
				action = TARGET_STILL_ACTIVE;
			पूर्ण अन्यथा अणु
				action = MODE_CHANGE_ACCEPT;
			पूर्ण
		पूर्ण
		अवरोध;
	पूर्ण

	चयन (action) अणु
	हाल MODE_CHANGE_ACCEPT:
		ql_log(ql_log_warn, vha, 0xffff,
		    "Mode change accepted. From %s to %s, Tgt exchg %d|%d. ini exchg %d|%d\n",
		    mode_to_str[vha->qlini_mode], mode_to_str[op],
		    vha->ql2xexchoffld, vha->u_ql2xexchoffld,
		    vha->ql2xiniexchg, vha->u_ql2xiniexchg);

		vha->qlini_mode = op;
		vha->ql2xexchoffld = vha->u_ql2xexchoffld;
		vha->ql2xiniexchg = vha->u_ql2xiniexchg;
		अगर (set_mode)
			qlt_set_mode(vha);
		vha->flags.online = 1;
		set_bit(ISP_ABORT_NEEDED, &vha->dpc_flags);
		अवरोध;

	हाल MODE_CHANGE_NO_ACTION:
		ql_log(ql_log_warn, vha, 0xffff,
		    "Mode is set. No action taken. From %s to %s, Tgt exchg %d|%d. ini exchg %d|%d\n",
		    mode_to_str[vha->qlini_mode], mode_to_str[op],
		    vha->ql2xexchoffld, vha->u_ql2xexchoffld,
		    vha->ql2xiniexchg, vha->u_ql2xiniexchg);
		vha->qlini_mode = op;
		vha->ql2xexchoffld = vha->u_ql2xexchoffld;
		vha->ql2xiniexchg = vha->u_ql2xiniexchg;
		अवरोध;

	हाल TARGET_STILL_ACTIVE:
		ql_log(ql_log_warn, vha, 0xffff,
		    "Target Mode is active. Unable to change Mode.\n");
		अवरोध;

	हाल NO_ACTION:
	शेष:
		ql_log(ql_log_warn, vha, 0xffff,
		    "Mode unchange. No action taken. %d|%d pct %d|%d.\n",
		    vha->qlini_mode, op,
		    vha->ql2xexchoffld, vha->u_ql2xexchoffld);
		अवरोध;
	पूर्ण
पूर्ण

अटल sमाप_प्रकार
qlini_mode_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
    स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	scsi_qla_host_t *vha = shost_priv(class_to_shost(dev));
	पूर्णांक ini;

	अगर (!buf)
		वापस -EINVAL;

	अगर (strnहालcmp(QLA2XXX_INI_MODE_STR_EXCLUSIVE, buf,
		म_माप(QLA2XXX_INI_MODE_STR_EXCLUSIVE)) == 0)
		ini = QLA2XXX_INI_MODE_EXCLUSIVE;
	अन्यथा अगर (strnहालcmp(QLA2XXX_INI_MODE_STR_DISABLED, buf,
		म_माप(QLA2XXX_INI_MODE_STR_DISABLED)) == 0)
		ini = QLA2XXX_INI_MODE_DISABLED;
	अन्यथा अगर (strnहालcmp(QLA2XXX_INI_MODE_STR_ENABLED, buf,
		  म_माप(QLA2XXX_INI_MODE_STR_ENABLED)) == 0)
		ini = QLA2XXX_INI_MODE_ENABLED;
	अन्यथा अगर (strnहालcmp(QLA2XXX_INI_MODE_STR_DUAL, buf,
		म_माप(QLA2XXX_INI_MODE_STR_DUAL)) == 0)
		ini = QLA2XXX_INI_MODE_DUAL;
	अन्यथा
		वापस -EINVAL;

	qla_set_ini_mode(vha, ini);
	वापस म_माप(buf);
पूर्ण

अटल sमाप_प्रकार
ql2xexchoffld_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
    अक्षर *buf)
अणु
	scsi_qla_host_t *vha = shost_priv(class_to_shost(dev));
	पूर्णांक len = 0;

	len += scnम_लिखो(buf + len, PAGE_SIZE-len,
		"target exchange: new %d : current: %d\n\n",
		vha->u_ql2xexchoffld, vha->ql2xexchoffld);

	len += scnम_लिखो(buf + len, PAGE_SIZE-len,
	    "Please (re)set operating mode via \"/sys/class/scsi_host/host%ld/qlini_mode\" to load new setting.\n",
	    vha->host_no);

	वापस len;
पूर्ण

अटल sमाप_प्रकार
ql2xexchoffld_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
    स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	scsi_qla_host_t *vha = shost_priv(class_to_shost(dev));
	पूर्णांक val = 0;

	अगर (माला_पूछो(buf, "%d", &val) != 1)
		वापस -EINVAL;

	अगर (val > FW_MAX_EXCHANGES_CNT)
		val = FW_MAX_EXCHANGES_CNT;
	अन्यथा अगर (val < 0)
		val = 0;

	vha->u_ql2xexchoffld = val;
	वापस म_माप(buf);
पूर्ण

अटल sमाप_प्रकार
ql2xiniexchg_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
    अक्षर *buf)
अणु
	scsi_qla_host_t *vha = shost_priv(class_to_shost(dev));
	पूर्णांक len = 0;

	len += scnम_लिखो(buf + len, PAGE_SIZE-len,
		"target exchange: new %d : current: %d\n\n",
		vha->u_ql2xiniexchg, vha->ql2xiniexchg);

	len += scnम_लिखो(buf + len, PAGE_SIZE-len,
	    "Please (re)set operating mode via \"/sys/class/scsi_host/host%ld/qlini_mode\" to load new setting.\n",
	    vha->host_no);

	वापस len;
पूर्ण

अटल sमाप_प्रकार
ql2xiniexchg_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
    स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	scsi_qla_host_t *vha = shost_priv(class_to_shost(dev));
	पूर्णांक val = 0;

	अगर (माला_पूछो(buf, "%d", &val) != 1)
		वापस -EINVAL;

	अगर (val > FW_MAX_EXCHANGES_CNT)
		val = FW_MAX_EXCHANGES_CNT;
	अन्यथा अगर (val < 0)
		val = 0;

	vha->u_ql2xiniexchg = val;
	वापस म_माप(buf);
पूर्ण

अटल sमाप_प्रकार
qla2x00_dअगर_bundle_statistics_show(काष्ठा device *dev,
    काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	scsi_qla_host_t *vha = shost_priv(class_to_shost(dev));
	काष्ठा qla_hw_data *ha = vha->hw;

	वापस scnम_लिखो(buf, PAGE_SIZE,
	    "cross=%llu read=%llu write=%llu kalloc=%llu dma_alloc=%llu unusable=%u\n",
	    ha->dअगर_bundle_crossed_pages, ha->dअगर_bundle_पढ़ोs,
	    ha->dअगर_bundle_ग_लिखोs, ha->dअगर_bundle_kallocs,
	    ha->dअगर_bundle_dma_allocs, ha->pool.unusable.count);
पूर्ण

अटल sमाप_प्रकार
qla2x00_fw_attr_show(काष्ठा device *dev,
    काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	scsi_qla_host_t *vha = shost_priv(class_to_shost(dev));
	काष्ठा qla_hw_data *ha = vha->hw;

	अगर (!IS_QLA27XX(ha) && !IS_QLA28XX(ha))
		वापस scnम_लिखो(buf, PAGE_SIZE, "\n");

	वापस scnम_लिखो(buf, PAGE_SIZE, "%llx\n",
	    (uपूर्णांक64_t)ha->fw_attributes_ext[1] << 48 |
	    (uपूर्णांक64_t)ha->fw_attributes_ext[0] << 32 |
	    (uपूर्णांक64_t)ha->fw_attributes_h << 16 |
	    (uपूर्णांक64_t)ha->fw_attributes);
पूर्ण

अटल sमाप_प्रकार
qla2x00_port_no_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
    अक्षर *buf)
अणु
	scsi_qla_host_t *vha = shost_priv(class_to_shost(dev));

	वापस scnम_लिखो(buf, PAGE_SIZE, "%u\n", vha->hw->port_no);
पूर्ण

अटल sमाप_प्रकार
qla2x00_dport_diagnostics_show(काष्ठा device *dev,
	काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	scsi_qla_host_t *vha = shost_priv(class_to_shost(dev));

	अगर (!IS_QLA83XX(vha->hw) && !IS_QLA27XX(vha->hw) &&
	    !IS_QLA28XX(vha->hw))
		वापस scnम_लिखो(buf, PAGE_SIZE, "\n");

	अगर (!*vha->dport_data)
		वापस scnम_लिखो(buf, PAGE_SIZE, "\n");

	वापस scnम_लिखो(buf, PAGE_SIZE, "%04x %04x %04x %04x\n",
	    vha->dport_data[0], vha->dport_data[1],
	    vha->dport_data[2], vha->dport_data[3]);
पूर्ण
अटल DEVICE_ATTR(dport_diagnostics, 0444,
	   qla2x00_dport_diagnostics_show, शून्य);

अटल DEVICE_ATTR(driver_version, S_IRUGO, qla2x00_driver_version_show, शून्य);
अटल DEVICE_ATTR(fw_version, S_IRUGO, qla2x00_fw_version_show, शून्य);
अटल DEVICE_ATTR(serial_num, S_IRUGO, qla2x00_serial_num_show, शून्य);
अटल DEVICE_ATTR(isp_name, S_IRUGO, qla2x00_isp_name_show, शून्य);
अटल DEVICE_ATTR(isp_id, S_IRUGO, qla2x00_isp_id_show, शून्य);
अटल DEVICE_ATTR(model_name, S_IRUGO, qla2x00_model_name_show, शून्य);
अटल DEVICE_ATTR(model_desc, S_IRUGO, qla2x00_model_desc_show, शून्य);
अटल DEVICE_ATTR(pci_info, S_IRUGO, qla2x00_pci_info_show, शून्य);
अटल DEVICE_ATTR(link_state, S_IRUGO, qla2x00_link_state_show, शून्य);
अटल DEVICE_ATTR(zio, S_IRUGO | S_IWUSR, qla2x00_zio_show, qla2x00_zio_store);
अटल DEVICE_ATTR(zio_समयr, S_IRUGO | S_IWUSR, qla2x00_zio_समयr_show,
		   qla2x00_zio_समयr_store);
अटल DEVICE_ATTR(beacon, S_IRUGO | S_IWUSR, qla2x00_beacon_show,
		   qla2x00_beacon_store);
अटल DEVICE_ATTR(beacon_config, 0644, qla2x00_beacon_config_show,
		   qla2x00_beacon_config_store);
अटल DEVICE_ATTR(optrom_bios_version, S_IRUGO,
		   qla2x00_optrom_bios_version_show, शून्य);
अटल DEVICE_ATTR(optrom_efi_version, S_IRUGO,
		   qla2x00_optrom_efi_version_show, शून्य);
अटल DEVICE_ATTR(optrom_fcode_version, S_IRUGO,
		   qla2x00_optrom_fcode_version_show, शून्य);
अटल DEVICE_ATTR(optrom_fw_version, S_IRUGO, qla2x00_optrom_fw_version_show,
		   शून्य);
अटल DEVICE_ATTR(optrom_gold_fw_version, S_IRUGO,
    qla2x00_optrom_gold_fw_version_show, शून्य);
अटल DEVICE_ATTR(84xx_fw_version, S_IRUGO, qla24xx_84xx_fw_version_show,
		   शून्य);
अटल DEVICE_ATTR(total_isp_पातs, S_IRUGO, qla2x00_total_isp_पातs_show,
		   शून्य);
अटल DEVICE_ATTR(serdes_version, 0444, qla2x00_serdes_version_show, शून्य);
अटल DEVICE_ATTR(mpi_version, S_IRUGO, qla2x00_mpi_version_show, शून्य);
अटल DEVICE_ATTR(phy_version, S_IRUGO, qla2x00_phy_version_show, शून्य);
अटल DEVICE_ATTR(flash_block_size, S_IRUGO, qla2x00_flash_block_size_show,
		   शून्य);
अटल DEVICE_ATTR(vlan_id, S_IRUGO, qla2x00_vlan_id_show, शून्य);
अटल DEVICE_ATTR(vn_port_mac_address, S_IRUGO,
		   qla2x00_vn_port_mac_address_show, शून्य);
अटल DEVICE_ATTR(fabric_param, S_IRUGO, qla2x00_fabric_param_show, शून्य);
अटल DEVICE_ATTR(fw_state, S_IRUGO, qla2x00_fw_state_show, शून्य);
अटल DEVICE_ATTR(thermal_temp, S_IRUGO, qla2x00_thermal_temp_show, शून्य);
अटल DEVICE_ATTR(diag_requests, S_IRUGO, qla2x00_diag_requests_show, शून्य);
अटल DEVICE_ATTR(diag_megabytes, S_IRUGO, qla2x00_diag_megabytes_show, शून्य);
अटल DEVICE_ATTR(fw_dump_size, S_IRUGO, qla2x00_fw_dump_size_show, शून्य);
अटल DEVICE_ATTR(allow_cna_fw_dump, S_IRUGO | S_IWUSR,
		   qla2x00_allow_cna_fw_dump_show,
		   qla2x00_allow_cna_fw_dump_store);
अटल DEVICE_ATTR(pep_version, S_IRUGO, qla2x00_pep_version_show, शून्य);
अटल DEVICE_ATTR(min_supported_speed, 0444,
		   qla2x00_min_supported_speed_show, शून्य);
अटल DEVICE_ATTR(max_supported_speed, 0444,
		   qla2x00_max_supported_speed_show, शून्य);
अटल DEVICE_ATTR(zio_threshold, 0644,
    qla_zio_threshold_show,
    qla_zio_threshold_store);
अटल DEVICE_ATTR_RW(qlini_mode);
अटल DEVICE_ATTR_RW(ql2xexchoffld);
अटल DEVICE_ATTR_RW(ql2xiniexchg);
अटल DEVICE_ATTR(dअगर_bundle_statistics, 0444,
    qla2x00_dअगर_bundle_statistics_show, शून्य);
अटल DEVICE_ATTR(port_speed, 0644, qla2x00_port_speed_show,
    qla2x00_port_speed_store);
अटल DEVICE_ATTR(port_no, 0444, qla2x00_port_no_show, शून्य);
अटल DEVICE_ATTR(fw_attr, 0444, qla2x00_fw_attr_show, शून्य);


काष्ठा device_attribute *qla2x00_host_attrs[] = अणु
	&dev_attr_driver_version,
	&dev_attr_fw_version,
	&dev_attr_serial_num,
	&dev_attr_isp_name,
	&dev_attr_isp_id,
	&dev_attr_model_name,
	&dev_attr_model_desc,
	&dev_attr_pci_info,
	&dev_attr_link_state,
	&dev_attr_zio,
	&dev_attr_zio_समयr,
	&dev_attr_beacon,
	&dev_attr_beacon_config,
	&dev_attr_optrom_bios_version,
	&dev_attr_optrom_efi_version,
	&dev_attr_optrom_fcode_version,
	&dev_attr_optrom_fw_version,
	&dev_attr_84xx_fw_version,
	&dev_attr_total_isp_पातs,
	&dev_attr_serdes_version,
	&dev_attr_mpi_version,
	&dev_attr_phy_version,
	&dev_attr_flash_block_size,
	&dev_attr_vlan_id,
	&dev_attr_vn_port_mac_address,
	&dev_attr_fabric_param,
	&dev_attr_fw_state,
	&dev_attr_optrom_gold_fw_version,
	&dev_attr_thermal_temp,
	&dev_attr_diag_requests,
	&dev_attr_diag_megabytes,
	&dev_attr_fw_dump_size,
	&dev_attr_allow_cna_fw_dump,
	&dev_attr_pep_version,
	&dev_attr_min_supported_speed,
	&dev_attr_max_supported_speed,
	&dev_attr_zio_threshold,
	&dev_attr_dअगर_bundle_statistics,
	&dev_attr_port_speed,
	&dev_attr_port_no,
	&dev_attr_fw_attr,
	&dev_attr_dport_diagnostics,
	शून्य, /* reserve क्रम qlini_mode */
	शून्य, /* reserve क्रम ql2xiniexchg */
	शून्य, /* reserve क्रम ql2xexchoffld */
	शून्य,
पूर्ण;

व्योम qla_insert_tgt_attrs(व्योम)
अणु
	काष्ठा device_attribute **attr;

	/* advance to empty slot */
	क्रम (attr = &qla2x00_host_attrs[0]; *attr; ++attr)
		जारी;

	*attr = &dev_attr_qlini_mode;
	attr++;
	*attr = &dev_attr_ql2xiniexchg;
	attr++;
	*attr = &dev_attr_ql2xexchoffld;
पूर्ण

/* Host attributes. */

अटल व्योम
qla2x00_get_host_port_id(काष्ठा Scsi_Host *shost)
अणु
	scsi_qla_host_t *vha = shost_priv(shost);

	fc_host_port_id(shost) = vha->d_id.b.करोमुख्य << 16 |
	    vha->d_id.b.area << 8 | vha->d_id.b.al_pa;
पूर्ण

अटल व्योम
qla2x00_get_host_speed(काष्ठा Scsi_Host *shost)
अणु
	scsi_qla_host_t *vha = shost_priv(shost);
	u32 speed;

	अगर (IS_QLAFX00(vha->hw)) अणु
		qlafx00_get_host_speed(shost);
		वापस;
	पूर्ण

	चयन (vha->hw->link_data_rate) अणु
	हाल PORT_SPEED_1GB:
		speed = FC_PORTSPEED_1GBIT;
		अवरोध;
	हाल PORT_SPEED_2GB:
		speed = FC_PORTSPEED_2GBIT;
		अवरोध;
	हाल PORT_SPEED_4GB:
		speed = FC_PORTSPEED_4GBIT;
		अवरोध;
	हाल PORT_SPEED_8GB:
		speed = FC_PORTSPEED_8GBIT;
		अवरोध;
	हाल PORT_SPEED_10GB:
		speed = FC_PORTSPEED_10GBIT;
		अवरोध;
	हाल PORT_SPEED_16GB:
		speed = FC_PORTSPEED_16GBIT;
		अवरोध;
	हाल PORT_SPEED_32GB:
		speed = FC_PORTSPEED_32GBIT;
		अवरोध;
	हाल PORT_SPEED_64GB:
		speed = FC_PORTSPEED_64GBIT;
		अवरोध;
	शेष:
		speed = FC_PORTSPEED_UNKNOWN;
		अवरोध;
	पूर्ण

	fc_host_speed(shost) = speed;
पूर्ण

अटल व्योम
qla2x00_get_host_port_type(काष्ठा Scsi_Host *shost)
अणु
	scsi_qla_host_t *vha = shost_priv(shost);
	uपूर्णांक32_t port_type;

	अगर (vha->vp_idx) अणु
		fc_host_port_type(shost) = FC_PORTTYPE_NPIV;
		वापस;
	पूर्ण
	चयन (vha->hw->current_topology) अणु
	हाल ISP_CFG_NL:
		port_type = FC_PORTTYPE_LPORT;
		अवरोध;
	हाल ISP_CFG_FL:
		port_type = FC_PORTTYPE_NLPORT;
		अवरोध;
	हाल ISP_CFG_N:
		port_type = FC_PORTTYPE_PTP;
		अवरोध;
	हाल ISP_CFG_F:
		port_type = FC_PORTTYPE_NPORT;
		अवरोध;
	शेष:
		port_type = FC_PORTTYPE_UNKNOWN;
		अवरोध;
	पूर्ण

	fc_host_port_type(shost) = port_type;
पूर्ण

अटल व्योम
qla2x00_get_starget_node_name(काष्ठा scsi_target *starget)
अणु
	काष्ठा Scsi_Host *host = dev_to_shost(starget->dev.parent);
	scsi_qla_host_t *vha = shost_priv(host);
	fc_port_t *fcport;
	u64 node_name = 0;

	list_क्रम_each_entry(fcport, &vha->vp_fcports, list) अणु
		अगर (fcport->rport &&
		    starget->id == fcport->rport->scsi_target_id) अणु
			node_name = wwn_to_u64(fcport->node_name);
			अवरोध;
		पूर्ण
	पूर्ण

	fc_starget_node_name(starget) = node_name;
पूर्ण

अटल व्योम
qla2x00_get_starget_port_name(काष्ठा scsi_target *starget)
अणु
	काष्ठा Scsi_Host *host = dev_to_shost(starget->dev.parent);
	scsi_qla_host_t *vha = shost_priv(host);
	fc_port_t *fcport;
	u64 port_name = 0;

	list_क्रम_each_entry(fcport, &vha->vp_fcports, list) अणु
		अगर (fcport->rport &&
		    starget->id == fcport->rport->scsi_target_id) अणु
			port_name = wwn_to_u64(fcport->port_name);
			अवरोध;
		पूर्ण
	पूर्ण

	fc_starget_port_name(starget) = port_name;
पूर्ण

अटल व्योम
qla2x00_get_starget_port_id(काष्ठा scsi_target *starget)
अणु
	काष्ठा Scsi_Host *host = dev_to_shost(starget->dev.parent);
	scsi_qla_host_t *vha = shost_priv(host);
	fc_port_t *fcport;
	uपूर्णांक32_t port_id = ~0U;

	list_क्रम_each_entry(fcport, &vha->vp_fcports, list) अणु
		अगर (fcport->rport &&
		    starget->id == fcport->rport->scsi_target_id) अणु
			port_id = fcport->d_id.b.करोमुख्य << 16 |
			    fcport->d_id.b.area << 8 | fcport->d_id.b.al_pa;
			अवरोध;
		पूर्ण
	पूर्ण

	fc_starget_port_id(starget) = port_id;
पूर्ण

अटल अंतरभूत व्योम
qla2x00_set_rport_loss_पंचांगo(काष्ठा fc_rport *rport, uपूर्णांक32_t समयout)
अणु
	rport->dev_loss_पंचांगo = समयout ? समयout : 1;
पूर्ण

अटल व्योम
qla2x00_dev_loss_पंचांगo_callbk(काष्ठा fc_rport *rport)
अणु
	काष्ठा Scsi_Host *host = rport_to_shost(rport);
	fc_port_t *fcport = *(fc_port_t **)rport->dd_data;
	अचिन्हित दीर्घ flags;

	अगर (!fcport)
		वापस;

	/* Now that the rport has been deleted, set the fcport state to
	   FCS_DEVICE_DEAD */
	qla2x00_set_fcport_state(fcport, FCS_DEVICE_DEAD);

	/*
	 * Transport has effectively 'deleted' the rport, clear
	 * all local references.
	 */
	spin_lock_irqsave(host->host_lock, flags);
	fcport->rport = fcport->drport = शून्य;
	*((fc_port_t **)rport->dd_data) = शून्य;
	spin_unlock_irqrestore(host->host_lock, flags);

	अगर (test_bit(ABORT_ISP_ACTIVE, &fcport->vha->dpc_flags))
		वापस;

	अगर (unlikely(pci_channel_offline(fcport->vha->hw->pdev))) अणु
		qla2x00_पात_all_cmds(fcport->vha, DID_NO_CONNECT << 16);
		वापस;
	पूर्ण
पूर्ण

अटल व्योम
qla2x00_terminate_rport_io(काष्ठा fc_rport *rport)
अणु
	fc_port_t *fcport = *(fc_port_t **)rport->dd_data;

	अगर (!fcport)
		वापस;

	अगर (test_bit(UNLOADING, &fcport->vha->dpc_flags))
		वापस;

	अगर (test_bit(ABORT_ISP_ACTIVE, &fcport->vha->dpc_flags))
		वापस;

	अगर (unlikely(pci_channel_offline(fcport->vha->hw->pdev))) अणु
		qla2x00_पात_all_cmds(fcport->vha, DID_NO_CONNECT << 16);
		वापस;
	पूर्ण
	/*
	 * At this poपूर्णांक all fcport's software-states are cleared.  Perक्रमm any
	 * final cleanup of firmware resources (PCBs and XCBs).
	 */
	अगर (fcport->loop_id != FC_NO_LOOP_ID) अणु
		अगर (IS_FWI2_CAPABLE(fcport->vha->hw))
			fcport->vha->hw->isp_ops->fabric_logout(fcport->vha,
			    fcport->loop_id, fcport->d_id.b.करोमुख्य,
			    fcport->d_id.b.area, fcport->d_id.b.al_pa);
		अन्यथा
			qla2x00_port_logout(fcport->vha, fcport);
	पूर्ण
पूर्ण

अटल पूर्णांक
qla2x00_issue_lip(काष्ठा Scsi_Host *shost)
अणु
	scsi_qla_host_t *vha = shost_priv(shost);

	अगर (IS_QLAFX00(vha->hw))
		वापस 0;

	अगर (vha->hw->flags.port_isolated)
		वापस 0;

	qla2x00_loop_reset(vha);
	वापस 0;
पूर्ण

अटल काष्ठा fc_host_statistics *
qla2x00_get_fc_host_stats(काष्ठा Scsi_Host *shost)
अणु
	scsi_qla_host_t *vha = shost_priv(shost);
	काष्ठा qla_hw_data *ha = vha->hw;
	काष्ठा scsi_qla_host *base_vha = pci_get_drvdata(ha->pdev);
	पूर्णांक rval;
	काष्ठा link_statistics *stats;
	dma_addr_t stats_dma;
	काष्ठा fc_host_statistics *p = &vha->fc_host_stat;
	काष्ठा qla_qpair *qpair;
	पूर्णांक i;
	u64 ib = 0, ob = 0, ir = 0, or = 0;

	स_रखो(p, -1, माप(*p));

	अगर (IS_QLAFX00(vha->hw))
		जाओ करोne;

	अगर (test_bit(UNLOADING, &vha->dpc_flags))
		जाओ करोne;

	अगर (unlikely(pci_channel_offline(ha->pdev)))
		जाओ करोne;

	अगर (qla2x00_chip_is_करोwn(vha))
		जाओ करोne;

	stats = dma_alloc_coherent(&ha->pdev->dev, माप(*stats), &stats_dma,
				   GFP_KERNEL);
	अगर (!stats) अणु
		ql_log(ql_log_warn, vha, 0x707d,
		    "Failed to allocate memory for stats.\n");
		जाओ करोne;
	पूर्ण

	rval = QLA_FUNCTION_FAILED;
	अगर (IS_FWI2_CAPABLE(ha)) अणु
		rval = qla24xx_get_isp_stats(base_vha, stats, stats_dma, 0);
	पूर्ण अन्यथा अगर (atomic_पढ़ो(&base_vha->loop_state) == LOOP_READY &&
	    !ha->dpc_active) अणु
		/* Must be in a 'READY' state क्रम statistics retrieval. */
		rval = qla2x00_get_link_status(base_vha, base_vha->loop_id,
						stats, stats_dma);
	पूर्ण

	अगर (rval != QLA_SUCCESS)
		जाओ करोne_मुक्त;

	/* --- */
	क्रम (i = 0; i < vha->hw->max_qpairs; i++) अणु
		qpair = vha->hw->queue_pair_map[i];
		अगर (!qpair)
			जारी;
		ir += qpair->counters.input_requests;
		or += qpair->counters.output_requests;
		ib += qpair->counters.input_bytes;
		ob += qpair->counters.output_bytes;
	पूर्ण
	ir += ha->base_qpair->counters.input_requests;
	or += ha->base_qpair->counters.output_requests;
	ib += ha->base_qpair->counters.input_bytes;
	ob += ha->base_qpair->counters.output_bytes;

	ir += vha->qla_stats.input_requests;
	or += vha->qla_stats.output_requests;
	ib += vha->qla_stats.input_bytes;
	ob += vha->qla_stats.output_bytes;
	/* --- */

	p->link_failure_count = le32_to_cpu(stats->link_fail_cnt);
	p->loss_of_sync_count = le32_to_cpu(stats->loss_sync_cnt);
	p->loss_of_संकेत_count = le32_to_cpu(stats->loss_sig_cnt);
	p->prim_seq_protocol_err_count = le32_to_cpu(stats->prim_seq_err_cnt);
	p->invalid_tx_word_count = le32_to_cpu(stats->inval_xmit_word_cnt);
	p->invalid_crc_count = le32_to_cpu(stats->inval_crc_cnt);
	अगर (IS_FWI2_CAPABLE(ha)) अणु
		p->lip_count = le32_to_cpu(stats->lip_cnt);
		p->tx_frames = le32_to_cpu(stats->tx_frames);
		p->rx_frames = le32_to_cpu(stats->rx_frames);
		p->dumped_frames = le32_to_cpu(stats->discarded_frames);
		p->nos_count = le32_to_cpu(stats->nos_rcvd);
		p->error_frames =
		    le32_to_cpu(stats->dropped_frames) +
		    le32_to_cpu(stats->discarded_frames);
		अगर (IS_QLA83XX(ha) || IS_QLA27XX(ha) || IS_QLA28XX(ha)) अणु
			p->rx_words = le64_to_cpu(stats->fpm_recv_word_cnt);
			p->tx_words = le64_to_cpu(stats->fpm_xmit_word_cnt);
		पूर्ण अन्यथा अणु
			p->rx_words = ib >> 2;
			p->tx_words = ob >> 2;
		पूर्ण
	पूर्ण

	p->fcp_control_requests = vha->qla_stats.control_requests;
	p->fcp_input_requests = ir;
	p->fcp_output_requests = or;
	p->fcp_input_megabytes  = ib >> 20;
	p->fcp_output_megabytes = ob >> 20;
	p->seconds_since_last_reset =
	    get_jअगरfies_64() - vha->qla_stats.jअगरfies_at_last_reset;
	करो_भाग(p->seconds_since_last_reset, HZ);

करोne_मुक्त:
	dma_मुक्त_coherent(&ha->pdev->dev, माप(काष्ठा link_statistics),
	    stats, stats_dma);
करोne:
	वापस p;
पूर्ण

अटल व्योम
qla2x00_reset_host_stats(काष्ठा Scsi_Host *shost)
अणु
	scsi_qla_host_t *vha = shost_priv(shost);
	काष्ठा qla_hw_data *ha = vha->hw;
	काष्ठा scsi_qla_host *base_vha = pci_get_drvdata(ha->pdev);
	काष्ठा link_statistics *stats;
	dma_addr_t stats_dma;
	पूर्णांक i;
	काष्ठा qla_qpair *qpair;

	स_रखो(&vha->qla_stats, 0, माप(vha->qla_stats));
	स_रखो(&vha->fc_host_stat, 0, माप(vha->fc_host_stat));
	क्रम (i = 0; i < vha->hw->max_qpairs; i++) अणु
		qpair = vha->hw->queue_pair_map[i];
		अगर (!qpair)
			जारी;
		स_रखो(&qpair->counters, 0, माप(qpair->counters));
	पूर्ण
	स_रखो(&ha->base_qpair->counters, 0, माप(qpair->counters));

	vha->qla_stats.jअगरfies_at_last_reset = get_jअगरfies_64();

	अगर (IS_FWI2_CAPABLE(ha)) अणु
		पूर्णांक rval;

		stats = dma_alloc_coherent(&ha->pdev->dev,
		    माप(*stats), &stats_dma, GFP_KERNEL);
		अगर (!stats) अणु
			ql_log(ql_log_warn, vha, 0x70d7,
			    "Failed to allocate memory for stats.\n");
			वापस;
		पूर्ण

		/* reset firmware statistics */
		rval = qla24xx_get_isp_stats(base_vha, stats, stats_dma, BIT_0);
		अगर (rval != QLA_SUCCESS)
			ql_log(ql_log_warn, vha, 0x70de,
			       "Resetting ISP statistics failed: rval = %d\n",
			       rval);

		dma_मुक्त_coherent(&ha->pdev->dev, माप(*stats),
		    stats, stats_dma);
	पूर्ण
पूर्ण

अटल व्योम
qla2x00_get_host_symbolic_name(काष्ठा Scsi_Host *shost)
अणु
	scsi_qla_host_t *vha = shost_priv(shost);

	qla2x00_get_sym_node_name(vha, fc_host_symbolic_name(shost),
	    माप(fc_host_symbolic_name(shost)));
पूर्ण

अटल व्योम
qla2x00_set_host_प्रणाली_hostname(काष्ठा Scsi_Host *shost)
अणु
	scsi_qla_host_t *vha = shost_priv(shost);

	set_bit(REGISTER_FDMI_NEEDED, &vha->dpc_flags);
पूर्ण

अटल व्योम
qla2x00_get_host_fabric_name(काष्ठा Scsi_Host *shost)
अणु
	scsi_qla_host_t *vha = shost_priv(shost);
	अटल स्थिर uपूर्णांक8_t node_name[WWN_SIZE] = अणु
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF
	पूर्ण;
	u64 fabric_name = wwn_to_u64(node_name);

	अगर (vha->device_flags & SWITCH_FOUND)
		fabric_name = wwn_to_u64(vha->fabric_node_name);

	fc_host_fabric_name(shost) = fabric_name;
पूर्ण

अटल व्योम
qla2x00_get_host_port_state(काष्ठा Scsi_Host *shost)
अणु
	scsi_qla_host_t *vha = shost_priv(shost);
	काष्ठा scsi_qla_host *base_vha = pci_get_drvdata(vha->hw->pdev);

	अगर (!base_vha->flags.online) अणु
		fc_host_port_state(shost) = FC_PORTSTATE_OFFLINE;
		वापस;
	पूर्ण

	चयन (atomic_पढ़ो(&base_vha->loop_state)) अणु
	हाल LOOP_UPDATE:
		fc_host_port_state(shost) = FC_PORTSTATE_DIAGNOSTICS;
		अवरोध;
	हाल LOOP_DOWN:
		अगर (test_bit(LOOP_RESYNC_NEEDED, &base_vha->dpc_flags))
			fc_host_port_state(shost) = FC_PORTSTATE_DIAGNOSTICS;
		अन्यथा
			fc_host_port_state(shost) = FC_PORTSTATE_LINKDOWN;
		अवरोध;
	हाल LOOP_DEAD:
		fc_host_port_state(shost) = FC_PORTSTATE_LINKDOWN;
		अवरोध;
	हाल LOOP_READY:
		fc_host_port_state(shost) = FC_PORTSTATE_ONLINE;
		अवरोध;
	शेष:
		fc_host_port_state(shost) = FC_PORTSTATE_UNKNOWN;
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक
qla24xx_vport_create(काष्ठा fc_vport *fc_vport, bool disable)
अणु
	पूर्णांक	ret = 0;
	uपूर्णांक8_t	qos = 0;
	scsi_qla_host_t *base_vha = shost_priv(fc_vport->shost);
	scsi_qla_host_t *vha = शून्य;
	काष्ठा qla_hw_data *ha = base_vha->hw;
	पूर्णांक	cnt;
	काष्ठा req_que *req = ha->req_q_map[0];
	काष्ठा qla_qpair *qpair;

	ret = qla24xx_vport_create_req_sanity_check(fc_vport);
	अगर (ret) अणु
		ql_log(ql_log_warn, vha, 0x707e,
		    "Vport sanity check failed, status %x\n", ret);
		वापस (ret);
	पूर्ण

	vha = qla24xx_create_vhost(fc_vport);
	अगर (vha == शून्य) अणु
		ql_log(ql_log_warn, vha, 0x707f, "Vport create host failed.\n");
		वापस FC_VPORT_FAILED;
	पूर्ण
	अगर (disable) अणु
		atomic_set(&vha->vp_state, VP_OFFLINE);
		fc_vport_set_state(fc_vport, FC_VPORT_DISABLED);
	पूर्ण अन्यथा
		atomic_set(&vha->vp_state, VP_FAILED);

	/* पढ़ोy to create vport */
	ql_log(ql_log_info, vha, 0x7080,
	    "VP entry id %d assigned.\n", vha->vp_idx);

	/* initialized vport states */
	atomic_set(&vha->loop_state, LOOP_DOWN);
	vha->vp_err_state = VP_ERR_PORTDWN;
	vha->vp_prev_err_state = VP_ERR_UNKWN;
	/* Check अगर physical ha port is Up */
	अगर (atomic_पढ़ो(&base_vha->loop_state) == LOOP_DOWN ||
	    atomic_पढ़ो(&base_vha->loop_state) == LOOP_DEAD) अणु
		/* Don't retry or attempt login of this भव port */
		ql_dbg(ql_dbg_user, vha, 0x7081,
		    "Vport loop state is not UP.\n");
		atomic_set(&vha->loop_state, LOOP_DEAD);
		अगर (!disable)
			fc_vport_set_state(fc_vport, FC_VPORT_LINKDOWN);
	पूर्ण

	अगर (IS_T10_PI_CAPABLE(ha) && ql2xenabledअगर) अणु
		अगर (ha->fw_attributes & BIT_4) अणु
			पूर्णांक prot = 0, guard;

			vha->flags.dअगरdix_supported = 1;
			ql_dbg(ql_dbg_user, vha, 0x7082,
			    "Registered for DIF/DIX type 1 and 3 protection.\n");
			अगर (ql2xenabledअगर == 1)
				prot = SHOST_DIX_TYPE0_PROTECTION;
			scsi_host_set_prot(vha->host,
			    prot | SHOST_DIF_TYPE1_PROTECTION
			    | SHOST_DIF_TYPE2_PROTECTION
			    | SHOST_DIF_TYPE3_PROTECTION
			    | SHOST_DIX_TYPE1_PROTECTION
			    | SHOST_DIX_TYPE2_PROTECTION
			    | SHOST_DIX_TYPE3_PROTECTION);

			guard = SHOST_DIX_GUARD_CRC;

			अगर (IS_PI_IPGUARD_CAPABLE(ha) &&
			    (ql2xenabledअगर > 1 || IS_PI_DIFB_DIX0_CAPABLE(ha)))
				guard |= SHOST_DIX_GUARD_IP;

			scsi_host_set_guard(vha->host, guard);
		पूर्ण अन्यथा
			vha->flags.dअगरdix_supported = 0;
	पूर्ण

	अगर (scsi_add_host_with_dma(vha->host, &fc_vport->dev,
				   &ha->pdev->dev)) अणु
		ql_dbg(ql_dbg_user, vha, 0x7083,
		    "scsi_add_host failure for VP[%d].\n", vha->vp_idx);
		जाओ vport_create_failed_2;
	पूर्ण

	/* initialize attributes */
	fc_host_dev_loss_पंचांगo(vha->host) = ha->port_करोwn_retry_count;
	fc_host_node_name(vha->host) = wwn_to_u64(vha->node_name);
	fc_host_port_name(vha->host) = wwn_to_u64(vha->port_name);
	fc_host_supported_classes(vha->host) =
		fc_host_supported_classes(base_vha->host);
	fc_host_supported_speeds(vha->host) =
		fc_host_supported_speeds(base_vha->host);

	qlt_vport_create(vha, ha);
	qla24xx_vport_disable(fc_vport, disable);

	अगर (!ql2xmqsupport || !ha->npiv_info)
		जाओ vport_queue;

	/* Create a request queue in QoS mode क्रम the vport */
	क्रम (cnt = 0; cnt < ha->nvram_npiv_size; cnt++) अणु
		अगर (स_भेद(ha->npiv_info[cnt].port_name, vha->port_name, 8) == 0
			&& स_भेद(ha->npiv_info[cnt].node_name, vha->node_name,
					8) == 0) अणु
			qos = ha->npiv_info[cnt].q_qos;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (qos) अणु
		qpair = qla2xxx_create_qpair(vha, qos, vha->vp_idx, true);
		अगर (!qpair)
			ql_log(ql_log_warn, vha, 0x7084,
			    "Can't create qpair for VP[%d]\n",
			    vha->vp_idx);
		अन्यथा अणु
			ql_dbg(ql_dbg_multiq, vha, 0xc001,
			    "Queue pair: %d Qos: %d) created for VP[%d]\n",
			    qpair->id, qos, vha->vp_idx);
			ql_dbg(ql_dbg_user, vha, 0x7085,
			    "Queue Pair: %d Qos: %d) created for VP[%d]\n",
			    qpair->id, qos, vha->vp_idx);
			req = qpair->req;
			vha->qpair = qpair;
		पूर्ण
	पूर्ण

vport_queue:
	vha->req = req;
	वापस 0;

vport_create_failed_2:
	qla24xx_disable_vp(vha);
	qla24xx_deallocate_vp_id(vha);
	scsi_host_put(vha->host);
	वापस FC_VPORT_FAILED;
पूर्ण

अटल पूर्णांक
qla24xx_vport_delete(काष्ठा fc_vport *fc_vport)
अणु
	scsi_qla_host_t *vha = fc_vport->dd_data;
	काष्ठा qla_hw_data *ha = vha->hw;
	uपूर्णांक16_t id = vha->vp_idx;

	set_bit(VPORT_DELETE, &vha->dpc_flags);

	जबतक (test_bit(LOOP_RESYNC_ACTIVE, &vha->dpc_flags) ||
	    test_bit(FCPORT_UPDATE_NEEDED, &vha->dpc_flags))
		msleep(1000);


	qla24xx_disable_vp(vha);
	qla2x00_रुको_क्रम_sess_deletion(vha);

	qla_nvme_delete(vha);
	vha->flags.delete_progress = 1;

	qlt_हटाओ_target(ha, vha);

	fc_हटाओ_host(vha->host);

	scsi_हटाओ_host(vha->host);

	/* Allow समयr to run to drain queued items, when removing vp */
	qla24xx_deallocate_vp_id(vha);

	अगर (vha->समयr_active) अणु
		qla2x00_vp_stop_समयr(vha);
		ql_dbg(ql_dbg_user, vha, 0x7086,
		    "Timer for the VP[%d] has stopped\n", vha->vp_idx);
	पूर्ण

	qla2x00_मुक्त_fcports(vha);

	mutex_lock(&ha->vport_lock);
	ha->cur_vport_count--;
	clear_bit(vha->vp_idx, ha->vp_idx_map);
	mutex_unlock(&ha->vport_lock);

	dma_मुक्त_coherent(&ha->pdev->dev, vha->gnl.size, vha->gnl.l,
	    vha->gnl.ldma);

	vha->gnl.l = शून्य;

	vमुक्त(vha->scan.l);

	अगर (vha->qpair && vha->qpair->vp_idx == vha->vp_idx) अणु
		अगर (qla2xxx_delete_qpair(vha, vha->qpair) != QLA_SUCCESS)
			ql_log(ql_log_warn, vha, 0x7087,
			    "Queue Pair delete failed.\n");
	पूर्ण

	ql_log(ql_log_info, vha, 0x7088, "VP[%d] deleted.\n", id);
	scsi_host_put(vha->host);
	वापस 0;
पूर्ण

अटल पूर्णांक
qla24xx_vport_disable(काष्ठा fc_vport *fc_vport, bool disable)
अणु
	scsi_qla_host_t *vha = fc_vport->dd_data;

	अगर (disable)
		qla24xx_disable_vp(vha);
	अन्यथा
		qla24xx_enable_vp(vha);

	वापस 0;
पूर्ण

काष्ठा fc_function_ढाँचा qla2xxx_transport_functions = अणु

	.show_host_node_name = 1,
	.show_host_port_name = 1,
	.show_host_supported_classes = 1,
	.show_host_supported_speeds = 1,

	.get_host_port_id = qla2x00_get_host_port_id,
	.show_host_port_id = 1,
	.get_host_speed = qla2x00_get_host_speed,
	.show_host_speed = 1,
	.get_host_port_type = qla2x00_get_host_port_type,
	.show_host_port_type = 1,
	.get_host_symbolic_name = qla2x00_get_host_symbolic_name,
	.show_host_symbolic_name = 1,
	.set_host_प्रणाली_hostname = qla2x00_set_host_प्रणाली_hostname,
	.show_host_प्रणाली_hostname = 1,
	.get_host_fabric_name = qla2x00_get_host_fabric_name,
	.show_host_fabric_name = 1,
	.get_host_port_state = qla2x00_get_host_port_state,
	.show_host_port_state = 1,

	.dd_fcrport_size = माप(काष्ठा fc_port *),
	.show_rport_supported_classes = 1,

	.get_starget_node_name = qla2x00_get_starget_node_name,
	.show_starget_node_name = 1,
	.get_starget_port_name = qla2x00_get_starget_port_name,
	.show_starget_port_name = 1,
	.get_starget_port_id  = qla2x00_get_starget_port_id,
	.show_starget_port_id = 1,

	.set_rport_dev_loss_पंचांगo = qla2x00_set_rport_loss_पंचांगo,
	.show_rport_dev_loss_पंचांगo = 1,

	.issue_fc_host_lip = qla2x00_issue_lip,
	.dev_loss_पंचांगo_callbk = qla2x00_dev_loss_पंचांगo_callbk,
	.terminate_rport_io = qla2x00_terminate_rport_io,
	.get_fc_host_stats = qla2x00_get_fc_host_stats,
	.reset_fc_host_stats = qla2x00_reset_host_stats,

	.vport_create = qla24xx_vport_create,
	.vport_disable = qla24xx_vport_disable,
	.vport_delete = qla24xx_vport_delete,
	.bsg_request = qla24xx_bsg_request,
	.bsg_समयout = qla24xx_bsg_समयout,
पूर्ण;

काष्ठा fc_function_ढाँचा qla2xxx_transport_vport_functions = अणु

	.show_host_node_name = 1,
	.show_host_port_name = 1,
	.show_host_supported_classes = 1,

	.get_host_port_id = qla2x00_get_host_port_id,
	.show_host_port_id = 1,
	.get_host_speed = qla2x00_get_host_speed,
	.show_host_speed = 1,
	.get_host_port_type = qla2x00_get_host_port_type,
	.show_host_port_type = 1,
	.get_host_symbolic_name = qla2x00_get_host_symbolic_name,
	.show_host_symbolic_name = 1,
	.set_host_प्रणाली_hostname = qla2x00_set_host_प्रणाली_hostname,
	.show_host_प्रणाली_hostname = 1,
	.get_host_fabric_name = qla2x00_get_host_fabric_name,
	.show_host_fabric_name = 1,
	.get_host_port_state = qla2x00_get_host_port_state,
	.show_host_port_state = 1,

	.dd_fcrport_size = माप(काष्ठा fc_port *),
	.show_rport_supported_classes = 1,

	.get_starget_node_name = qla2x00_get_starget_node_name,
	.show_starget_node_name = 1,
	.get_starget_port_name = qla2x00_get_starget_port_name,
	.show_starget_port_name = 1,
	.get_starget_port_id  = qla2x00_get_starget_port_id,
	.show_starget_port_id = 1,

	.set_rport_dev_loss_पंचांगo = qla2x00_set_rport_loss_पंचांगo,
	.show_rport_dev_loss_पंचांगo = 1,

	.issue_fc_host_lip = qla2x00_issue_lip,
	.dev_loss_पंचांगo_callbk = qla2x00_dev_loss_पंचांगo_callbk,
	.terminate_rport_io = qla2x00_terminate_rport_io,
	.get_fc_host_stats = qla2x00_get_fc_host_stats,
	.reset_fc_host_stats = qla2x00_reset_host_stats,

	.bsg_request = qla24xx_bsg_request,
	.bsg_समयout = qla24xx_bsg_समयout,
पूर्ण;

व्योम
qla2x00_init_host_attr(scsi_qla_host_t *vha)
अणु
	काष्ठा qla_hw_data *ha = vha->hw;
	u32 speeds = FC_PORTSPEED_UNKNOWN;

	fc_host_dev_loss_पंचांगo(vha->host) = ha->port_करोwn_retry_count;
	fc_host_node_name(vha->host) = wwn_to_u64(vha->node_name);
	fc_host_port_name(vha->host) = wwn_to_u64(vha->port_name);
	fc_host_supported_classes(vha->host) = ha->base_qpair->enable_class_2 ?
			(FC_COS_CLASS2|FC_COS_CLASS3) : FC_COS_CLASS3;
	fc_host_max_npiv_vports(vha->host) = ha->max_npiv_vports;
	fc_host_npiv_vports_inuse(vha->host) = ha->cur_vport_count;

	speeds = qla25xx_fdmi_port_speed_capability(ha);

	fc_host_supported_speeds(vha->host) = speeds;
पूर्ण
