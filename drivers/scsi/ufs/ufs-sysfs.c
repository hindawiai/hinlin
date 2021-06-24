<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (C) 2018 Western Digital Corporation

#समावेश <linux/err.h>
#समावेश <linux/माला.स>
#समावेश <linux/bitfield.h>
#समावेश <यंत्र/unaligned.h>

#समावेश "ufs.h"
#समावेश "ufs-sysfs.h"

अटल स्थिर अक्षर *ufshcd_uic_link_state_to_string(
			क्रमागत uic_link_state state)
अणु
	चयन (state) अणु
	हाल UIC_LINK_OFF_STATE:	वापस "OFF";
	हाल UIC_LINK_ACTIVE_STATE:	वापस "ACTIVE";
	हाल UIC_LINK_HIBERN8_STATE:	वापस "HIBERN8";
	हाल UIC_LINK_BROKEN_STATE:	वापस "BROKEN";
	शेष:			वापस "UNKNOWN";
	पूर्ण
पूर्ण

अटल स्थिर अक्षर *ufshcd_ufs_dev_pwr_mode_to_string(
			क्रमागत ufs_dev_pwr_mode state)
अणु
	चयन (state) अणु
	हाल UFS_ACTIVE_PWR_MODE:	वापस "ACTIVE";
	हाल UFS_SLEEP_PWR_MODE:	वापस "SLEEP";
	हाल UFS_POWERDOWN_PWR_MODE:	वापस "POWERDOWN";
	हाल UFS_DEEPSLEEP_PWR_MODE:	वापस "DEEPSLEEP";
	शेष:			वापस "UNKNOWN";
	पूर्ण
पूर्ण

अटल अंतरभूत sमाप_प्रकार ufs_sysfs_pm_lvl_store(काष्ठा device *dev,
					     काष्ठा device_attribute *attr,
					     स्थिर अक्षर *buf, माप_प्रकार count,
					     bool rpm)
अणु
	काष्ठा ufs_hba *hba = dev_get_drvdata(dev);
	काष्ठा ufs_dev_info *dev_info = &hba->dev_info;
	अचिन्हित दीर्घ flags, value;

	अगर (kम_से_अदीर्घ(buf, 0, &value))
		वापस -EINVAL;

	अगर (value >= UFS_PM_LVL_MAX)
		वापस -EINVAL;

	अगर (ufs_pm_lvl_states[value].dev_state == UFS_DEEPSLEEP_PWR_MODE &&
	    (!(hba->caps & UFSHCD_CAP_DEEPSLEEP) ||
	     !(dev_info->wspecversion >= 0x310)))
		वापस -EINVAL;

	spin_lock_irqsave(hba->host->host_lock, flags);
	अगर (rpm)
		hba->rpm_lvl = value;
	अन्यथा
		hba->spm_lvl = value;
	spin_unlock_irqrestore(hba->host->host_lock, flags);
	वापस count;
पूर्ण

अटल sमाप_प्रकार rpm_lvl_show(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा ufs_hba *hba = dev_get_drvdata(dev);

	वापस sysfs_emit(buf, "%d\n", hba->rpm_lvl);
पूर्ण

अटल sमाप_प्रकार rpm_lvl_store(काष्ठा device *dev,
		काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	वापस ufs_sysfs_pm_lvl_store(dev, attr, buf, count, true);
पूर्ण

अटल sमाप_प्रकार rpm_target_dev_state_show(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा ufs_hba *hba = dev_get_drvdata(dev);

	वापस sysfs_emit(buf, "%s\n", ufshcd_ufs_dev_pwr_mode_to_string(
			ufs_pm_lvl_states[hba->rpm_lvl].dev_state));
पूर्ण

अटल sमाप_प्रकार rpm_target_link_state_show(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा ufs_hba *hba = dev_get_drvdata(dev);

	वापस sysfs_emit(buf, "%s\n", ufshcd_uic_link_state_to_string(
			ufs_pm_lvl_states[hba->rpm_lvl].link_state));
पूर्ण

अटल sमाप_प्रकार spm_lvl_show(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा ufs_hba *hba = dev_get_drvdata(dev);

	वापस sysfs_emit(buf, "%d\n", hba->spm_lvl);
पूर्ण

अटल sमाप_प्रकार spm_lvl_store(काष्ठा device *dev,
		काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	वापस ufs_sysfs_pm_lvl_store(dev, attr, buf, count, false);
पूर्ण

अटल sमाप_प्रकार spm_target_dev_state_show(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा ufs_hba *hba = dev_get_drvdata(dev);

	वापस sysfs_emit(buf, "%s\n", ufshcd_ufs_dev_pwr_mode_to_string(
				ufs_pm_lvl_states[hba->spm_lvl].dev_state));
पूर्ण

अटल sमाप_प्रकार spm_target_link_state_show(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा ufs_hba *hba = dev_get_drvdata(dev);

	वापस sysfs_emit(buf, "%s\n", ufshcd_uic_link_state_to_string(
				ufs_pm_lvl_states[hba->spm_lvl].link_state));
पूर्ण

/* Convert Auto-Hibernate Idle Timer रेजिस्टर value to microseconds */
अटल पूर्णांक ufshcd_ahit_to_us(u32 ahit)
अणु
	पूर्णांक समयr = FIELD_GET(UFSHCI_AHIBERN8_TIMER_MASK, ahit);
	पूर्णांक scale = FIELD_GET(UFSHCI_AHIBERN8_SCALE_MASK, ahit);

	क्रम (; scale > 0; --scale)
		समयr *= UFSHCI_AHIBERN8_SCALE_FACTOR;

	वापस समयr;
पूर्ण

/* Convert microseconds to Auto-Hibernate Idle Timer रेजिस्टर value */
अटल u32 ufshcd_us_to_ahit(अचिन्हित पूर्णांक समयr)
अणु
	अचिन्हित पूर्णांक scale;

	क्रम (scale = 0; समयr > UFSHCI_AHIBERN8_TIMER_MASK; ++scale)
		समयr /= UFSHCI_AHIBERN8_SCALE_FACTOR;

	वापस FIELD_PREP(UFSHCI_AHIBERN8_TIMER_MASK, समयr) |
	       FIELD_PREP(UFSHCI_AHIBERN8_SCALE_MASK, scale);
पूर्ण

अटल sमाप_प्रकार स्वतः_hibern8_show(काष्ठा device *dev,
				 काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	u32 ahit;
	पूर्णांक ret;
	काष्ठा ufs_hba *hba = dev_get_drvdata(dev);

	अगर (!ufshcd_is_स्वतः_hibern8_supported(hba))
		वापस -EOPNOTSUPP;

	करोwn(&hba->host_sem);
	अगर (!ufshcd_is_user_access_allowed(hba)) अणु
		ret = -EBUSY;
		जाओ out;
	पूर्ण

	pm_runसमय_get_sync(hba->dev);
	ufshcd_hold(hba, false);
	ahit = ufshcd_पढ़ोl(hba, REG_AUTO_HIBERNATE_IDLE_TIMER);
	ufshcd_release(hba);
	pm_runसमय_put_sync(hba->dev);

	ret = sysfs_emit(buf, "%d\n", ufshcd_ahit_to_us(ahit));

out:
	up(&hba->host_sem);
	वापस ret;
पूर्ण

अटल sमाप_प्रकार स्वतः_hibern8_store(काष्ठा device *dev,
				  काष्ठा device_attribute *attr,
				  स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा ufs_hba *hba = dev_get_drvdata(dev);
	अचिन्हित पूर्णांक समयr;
	पूर्णांक ret = 0;

	अगर (!ufshcd_is_स्वतः_hibern8_supported(hba))
		वापस -EOPNOTSUPP;

	अगर (kstrtouपूर्णांक(buf, 0, &समयr))
		वापस -EINVAL;

	अगर (समयr > UFSHCI_AHIBERN8_MAX)
		वापस -EINVAL;

	करोwn(&hba->host_sem);
	अगर (!ufshcd_is_user_access_allowed(hba)) अणु
		ret = -EBUSY;
		जाओ out;
	पूर्ण

	ufshcd_स्वतः_hibern8_update(hba, ufshcd_us_to_ahit(समयr));

out:
	up(&hba->host_sem);
	वापस ret ? ret : count;
पूर्ण

अटल sमाप_प्रकार wb_on_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			  अक्षर *buf)
अणु
	काष्ठा ufs_hba *hba = dev_get_drvdata(dev);

	वापस sysfs_emit(buf, "%d\n", hba->dev_info.wb_enabled);
पूर्ण

अटल sमाप_प्रकार wb_on_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
			   स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा ufs_hba *hba = dev_get_drvdata(dev);
	अचिन्हित पूर्णांक wb_enable;
	sमाप_प्रकार res;

	अगर (!ufshcd_is_wb_allowed(hba) || ufshcd_is_clkscaling_supported(hba)) अणु
		/*
		 * If the platक्रमm supports UFSHCD_CAP_CLK_SCALING, turn WB
		 * on/off will be करोne जबतक घड़ी scaling up/करोwn.
		 */
		dev_warn(dev, "To control WB through wb_on is not allowed!\n");
		वापस -EOPNOTSUPP;
	पूर्ण

	अगर (kstrtouपूर्णांक(buf, 0, &wb_enable))
		वापस -EINVAL;

	अगर (wb_enable != 0 && wb_enable != 1)
		वापस -EINVAL;

	करोwn(&hba->host_sem);
	अगर (!ufshcd_is_user_access_allowed(hba)) अणु
		res = -EBUSY;
		जाओ out;
	पूर्ण

	pm_runसमय_get_sync(hba->dev);
	res = ufshcd_wb_toggle(hba, wb_enable);
	pm_runसमय_put_sync(hba->dev);
out:
	up(&hba->host_sem);
	वापस res < 0 ? res : count;
पूर्ण

अटल DEVICE_ATTR_RW(rpm_lvl);
अटल DEVICE_ATTR_RO(rpm_target_dev_state);
अटल DEVICE_ATTR_RO(rpm_target_link_state);
अटल DEVICE_ATTR_RW(spm_lvl);
अटल DEVICE_ATTR_RO(spm_target_dev_state);
अटल DEVICE_ATTR_RO(spm_target_link_state);
अटल DEVICE_ATTR_RW(स्वतः_hibern8);
अटल DEVICE_ATTR_RW(wb_on);

अटल काष्ठा attribute *ufs_sysfs_ufshcd_attrs[] = अणु
	&dev_attr_rpm_lvl.attr,
	&dev_attr_rpm_target_dev_state.attr,
	&dev_attr_rpm_target_link_state.attr,
	&dev_attr_spm_lvl.attr,
	&dev_attr_spm_target_dev_state.attr,
	&dev_attr_spm_target_link_state.attr,
	&dev_attr_स्वतः_hibern8.attr,
	&dev_attr_wb_on.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group ufs_sysfs_शेष_group = अणु
	.attrs = ufs_sysfs_ufshcd_attrs,
पूर्ण;

अटल sमाप_प्रकार ufs_sysfs_पढ़ो_desc_param(काष्ठा ufs_hba *hba,
				  क्रमागत desc_idn desc_id,
				  u8 desc_index,
				  u8 param_offset,
				  u8 *sysfs_buf,
				  u8 param_size)
अणु
	u8 desc_buf[8] = अणु0पूर्ण;
	पूर्णांक ret;

	अगर (param_size > 8)
		वापस -EINVAL;

	करोwn(&hba->host_sem);
	अगर (!ufshcd_is_user_access_allowed(hba)) अणु
		ret = -EBUSY;
		जाओ out;
	पूर्ण

	pm_runसमय_get_sync(hba->dev);
	ret = ufshcd_पढ़ो_desc_param(hba, desc_id, desc_index,
				param_offset, desc_buf, param_size);
	pm_runसमय_put_sync(hba->dev);
	अगर (ret) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	चयन (param_size) अणु
	हाल 1:
		ret = sysfs_emit(sysfs_buf, "0x%02X\n", *desc_buf);
		अवरोध;
	हाल 2:
		ret = sysfs_emit(sysfs_buf, "0x%04X\n",
			get_unaligned_be16(desc_buf));
		अवरोध;
	हाल 4:
		ret = sysfs_emit(sysfs_buf, "0x%08X\n",
			get_unaligned_be32(desc_buf));
		अवरोध;
	हाल 8:
		ret = sysfs_emit(sysfs_buf, "0x%016llX\n",
			get_unaligned_be64(desc_buf));
		अवरोध;
	पूर्ण

out:
	up(&hba->host_sem);
	वापस ret;
पूर्ण

#घोषणा UFS_DESC_PARAM(_name, _puname, _duname, _size)			\
अटल sमाप_प्रकार _name##_show(काष्ठा device *dev,				\
	काष्ठा device_attribute *attr, अक्षर *buf)			\
अणु									\
	काष्ठा ufs_hba *hba = dev_get_drvdata(dev);			\
	वापस ufs_sysfs_पढ़ो_desc_param(hba, QUERY_DESC_IDN_##_duname,	\
		0, _duname##_DESC_PARAM##_puname, buf, _size);		\
पूर्ण									\
अटल DEVICE_ATTR_RO(_name)

#घोषणा UFS_DEVICE_DESC_PARAM(_name, _uname, _size)			\
	UFS_DESC_PARAM(_name, _uname, DEVICE, _size)

UFS_DEVICE_DESC_PARAM(device_type, _DEVICE_TYPE, 1);
UFS_DEVICE_DESC_PARAM(device_class, _DEVICE_CLASS, 1);
UFS_DEVICE_DESC_PARAM(device_sub_class, _DEVICE_SUB_CLASS, 1);
UFS_DEVICE_DESC_PARAM(protocol, _PRTCL, 1);
UFS_DEVICE_DESC_PARAM(number_of_luns, _NUM_LU, 1);
UFS_DEVICE_DESC_PARAM(number_of_wluns, _NUM_WLU, 1);
UFS_DEVICE_DESC_PARAM(boot_enable, _BOOT_ENBL, 1);
UFS_DEVICE_DESC_PARAM(descriptor_access_enable, _DESC_ACCSS_ENBL, 1);
UFS_DEVICE_DESC_PARAM(initial_घातer_mode, _INIT_PWR_MODE, 1);
UFS_DEVICE_DESC_PARAM(high_priority_lun, _HIGH_PR_LUN, 1);
UFS_DEVICE_DESC_PARAM(secure_removal_type, _SEC_RMV_TYPE, 1);
UFS_DEVICE_DESC_PARAM(support_security_lun, _SEC_LU, 1);
UFS_DEVICE_DESC_PARAM(bkops_termination_latency, _BKOP_TERM_LT, 1);
UFS_DEVICE_DESC_PARAM(initial_active_icc_level, _ACTVE_ICC_LVL, 1);
UFS_DEVICE_DESC_PARAM(specअगरication_version, _SPEC_VER, 2);
UFS_DEVICE_DESC_PARAM(manufacturing_date, _MANF_DATE, 2);
UFS_DEVICE_DESC_PARAM(manufacturer_id, _MANF_ID, 2);
UFS_DEVICE_DESC_PARAM(rtt_capability, _RTT_CAP, 1);
UFS_DEVICE_DESC_PARAM(rtc_update, _FRQ_RTC, 2);
UFS_DEVICE_DESC_PARAM(ufs_features, _UFS_FEAT, 1);
UFS_DEVICE_DESC_PARAM(ffu_समयout, _FFU_TMT, 1);
UFS_DEVICE_DESC_PARAM(queue_depth, _Q_DPTH, 1);
UFS_DEVICE_DESC_PARAM(device_version, _DEV_VER, 2);
UFS_DEVICE_DESC_PARAM(number_of_secure_wpa, _NUM_SEC_WPA, 1);
UFS_DEVICE_DESC_PARAM(psa_max_data_size, _PSA_MAX_DATA, 4);
UFS_DEVICE_DESC_PARAM(psa_state_समयout, _PSA_TMT, 1);
UFS_DEVICE_DESC_PARAM(ext_feature_sup, _EXT_UFS_FEATURE_SUP, 4);
UFS_DEVICE_DESC_PARAM(wb_presv_us_en, _WB_PRESRV_USRSPC_EN, 1);
UFS_DEVICE_DESC_PARAM(wb_type, _WB_TYPE, 1);
UFS_DEVICE_DESC_PARAM(wb_shared_alloc_units, _WB_SHARED_ALLOC_UNITS, 4);

अटल काष्ठा attribute *ufs_sysfs_device_descriptor[] = अणु
	&dev_attr_device_type.attr,
	&dev_attr_device_class.attr,
	&dev_attr_device_sub_class.attr,
	&dev_attr_protocol.attr,
	&dev_attr_number_of_luns.attr,
	&dev_attr_number_of_wluns.attr,
	&dev_attr_boot_enable.attr,
	&dev_attr_descriptor_access_enable.attr,
	&dev_attr_initial_घातer_mode.attr,
	&dev_attr_high_priority_lun.attr,
	&dev_attr_secure_removal_type.attr,
	&dev_attr_support_security_lun.attr,
	&dev_attr_bkops_termination_latency.attr,
	&dev_attr_initial_active_icc_level.attr,
	&dev_attr_specअगरication_version.attr,
	&dev_attr_manufacturing_date.attr,
	&dev_attr_manufacturer_id.attr,
	&dev_attr_rtt_capability.attr,
	&dev_attr_rtc_update.attr,
	&dev_attr_ufs_features.attr,
	&dev_attr_ffu_समयout.attr,
	&dev_attr_queue_depth.attr,
	&dev_attr_device_version.attr,
	&dev_attr_number_of_secure_wpa.attr,
	&dev_attr_psa_max_data_size.attr,
	&dev_attr_psa_state_समयout.attr,
	&dev_attr_ext_feature_sup.attr,
	&dev_attr_wb_presv_us_en.attr,
	&dev_attr_wb_type.attr,
	&dev_attr_wb_shared_alloc_units.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group ufs_sysfs_device_descriptor_group = अणु
	.name = "device_descriptor",
	.attrs = ufs_sysfs_device_descriptor,
पूर्ण;

#घोषणा UFS_INTERCONNECT_DESC_PARAM(_name, _uname, _size)		\
	UFS_DESC_PARAM(_name, _uname, INTERCONNECT, _size)

UFS_INTERCONNECT_DESC_PARAM(unipro_version, _UNIPRO_VER, 2);
UFS_INTERCONNECT_DESC_PARAM(mphy_version, _MPHY_VER, 2);

अटल काष्ठा attribute *ufs_sysfs_पूर्णांकerconnect_descriptor[] = अणु
	&dev_attr_unipro_version.attr,
	&dev_attr_mphy_version.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group ufs_sysfs_पूर्णांकerconnect_descriptor_group = अणु
	.name = "interconnect_descriptor",
	.attrs = ufs_sysfs_पूर्णांकerconnect_descriptor,
पूर्ण;

#घोषणा UFS_GEOMETRY_DESC_PARAM(_name, _uname, _size)			\
	UFS_DESC_PARAM(_name, _uname, GEOMETRY, _size)

UFS_GEOMETRY_DESC_PARAM(raw_device_capacity, _DEV_CAP, 8);
UFS_GEOMETRY_DESC_PARAM(max_number_of_luns, _MAX_NUM_LUN, 1);
UFS_GEOMETRY_DESC_PARAM(segment_size, _SEG_SIZE, 4);
UFS_GEOMETRY_DESC_PARAM(allocation_unit_size, _ALLOC_UNIT_SIZE, 1);
UFS_GEOMETRY_DESC_PARAM(min_addressable_block_size, _MIN_BLK_SIZE, 1);
UFS_GEOMETRY_DESC_PARAM(optimal_पढ़ो_block_size, _OPT_RD_BLK_SIZE, 1);
UFS_GEOMETRY_DESC_PARAM(optimal_ग_लिखो_block_size, _OPT_WR_BLK_SIZE, 1);
UFS_GEOMETRY_DESC_PARAM(max_in_buffer_size, _MAX_IN_BUF_SIZE, 1);
UFS_GEOMETRY_DESC_PARAM(max_out_buffer_size, _MAX_OUT_BUF_SIZE, 1);
UFS_GEOMETRY_DESC_PARAM(rpmb_rw_size, _RPMB_RW_SIZE, 1);
UFS_GEOMETRY_DESC_PARAM(dyn_capacity_resource_policy, _DYN_CAP_RSRC_PLC, 1);
UFS_GEOMETRY_DESC_PARAM(data_ordering, _DATA_ORDER, 1);
UFS_GEOMETRY_DESC_PARAM(max_number_of_contexts, _MAX_NUM_CTX, 1);
UFS_GEOMETRY_DESC_PARAM(sys_data_tag_unit_size, _TAG_UNIT_SIZE, 1);
UFS_GEOMETRY_DESC_PARAM(sys_data_tag_resource_size, _TAG_RSRC_SIZE, 1);
UFS_GEOMETRY_DESC_PARAM(secure_removal_types, _SEC_RM_TYPES, 1);
UFS_GEOMETRY_DESC_PARAM(memory_types, _MEM_TYPES, 2);
UFS_GEOMETRY_DESC_PARAM(sys_code_memory_max_alloc_units,
	_SCM_MAX_NUM_UNITS, 4);
UFS_GEOMETRY_DESC_PARAM(sys_code_memory_capacity_adjusपंचांगent_factor,
	_SCM_CAP_ADJ_FCTR, 2);
UFS_GEOMETRY_DESC_PARAM(non_persist_memory_max_alloc_units,
	_NPM_MAX_NUM_UNITS, 4);
UFS_GEOMETRY_DESC_PARAM(non_persist_memory_capacity_adjusपंचांगent_factor,
	_NPM_CAP_ADJ_FCTR, 2);
UFS_GEOMETRY_DESC_PARAM(enh1_memory_max_alloc_units,
	_ENM1_MAX_NUM_UNITS, 4);
UFS_GEOMETRY_DESC_PARAM(enh1_memory_capacity_adjusपंचांगent_factor,
	_ENM1_CAP_ADJ_FCTR, 2);
UFS_GEOMETRY_DESC_PARAM(enh2_memory_max_alloc_units,
	_ENM2_MAX_NUM_UNITS, 4);
UFS_GEOMETRY_DESC_PARAM(enh2_memory_capacity_adjusपंचांगent_factor,
	_ENM2_CAP_ADJ_FCTR, 2);
UFS_GEOMETRY_DESC_PARAM(enh3_memory_max_alloc_units,
	_ENM3_MAX_NUM_UNITS, 4);
UFS_GEOMETRY_DESC_PARAM(enh3_memory_capacity_adjusपंचांगent_factor,
	_ENM3_CAP_ADJ_FCTR, 2);
UFS_GEOMETRY_DESC_PARAM(enh4_memory_max_alloc_units,
	_ENM4_MAX_NUM_UNITS, 4);
UFS_GEOMETRY_DESC_PARAM(enh4_memory_capacity_adjusपंचांगent_factor,
	_ENM4_CAP_ADJ_FCTR, 2);
UFS_GEOMETRY_DESC_PARAM(wb_max_alloc_units, _WB_MAX_ALLOC_UNITS, 4);
UFS_GEOMETRY_DESC_PARAM(wb_max_wb_luns, _WB_MAX_WB_LUNS, 1);
UFS_GEOMETRY_DESC_PARAM(wb_buff_cap_adj, _WB_BUFF_CAP_ADJ, 1);
UFS_GEOMETRY_DESC_PARAM(wb_sup_red_type, _WB_SUP_RED_TYPE, 1);
UFS_GEOMETRY_DESC_PARAM(wb_sup_wb_type, _WB_SUP_WB_TYPE, 1);


अटल काष्ठा attribute *ufs_sysfs_geometry_descriptor[] = अणु
	&dev_attr_raw_device_capacity.attr,
	&dev_attr_max_number_of_luns.attr,
	&dev_attr_segment_size.attr,
	&dev_attr_allocation_unit_size.attr,
	&dev_attr_min_addressable_block_size.attr,
	&dev_attr_optimal_पढ़ो_block_size.attr,
	&dev_attr_optimal_ग_लिखो_block_size.attr,
	&dev_attr_max_in_buffer_size.attr,
	&dev_attr_max_out_buffer_size.attr,
	&dev_attr_rpmb_rw_size.attr,
	&dev_attr_dyn_capacity_resource_policy.attr,
	&dev_attr_data_ordering.attr,
	&dev_attr_max_number_of_contexts.attr,
	&dev_attr_sys_data_tag_unit_size.attr,
	&dev_attr_sys_data_tag_resource_size.attr,
	&dev_attr_secure_removal_types.attr,
	&dev_attr_memory_types.attr,
	&dev_attr_sys_code_memory_max_alloc_units.attr,
	&dev_attr_sys_code_memory_capacity_adjusपंचांगent_factor.attr,
	&dev_attr_non_persist_memory_max_alloc_units.attr,
	&dev_attr_non_persist_memory_capacity_adjusपंचांगent_factor.attr,
	&dev_attr_enh1_memory_max_alloc_units.attr,
	&dev_attr_enh1_memory_capacity_adjusपंचांगent_factor.attr,
	&dev_attr_enh2_memory_max_alloc_units.attr,
	&dev_attr_enh2_memory_capacity_adjusपंचांगent_factor.attr,
	&dev_attr_enh3_memory_max_alloc_units.attr,
	&dev_attr_enh3_memory_capacity_adjusपंचांगent_factor.attr,
	&dev_attr_enh4_memory_max_alloc_units.attr,
	&dev_attr_enh4_memory_capacity_adjusपंचांगent_factor.attr,
	&dev_attr_wb_max_alloc_units.attr,
	&dev_attr_wb_max_wb_luns.attr,
	&dev_attr_wb_buff_cap_adj.attr,
	&dev_attr_wb_sup_red_type.attr,
	&dev_attr_wb_sup_wb_type.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group ufs_sysfs_geometry_descriptor_group = अणु
	.name = "geometry_descriptor",
	.attrs = ufs_sysfs_geometry_descriptor,
पूर्ण;

#घोषणा UFS_HEALTH_DESC_PARAM(_name, _uname, _size)			\
	UFS_DESC_PARAM(_name, _uname, HEALTH, _size)

UFS_HEALTH_DESC_PARAM(eol_info, _EOL_INFO, 1);
UFS_HEALTH_DESC_PARAM(lअगरe_समय_estimation_a, _LIFE_TIME_EST_A, 1);
UFS_HEALTH_DESC_PARAM(lअगरe_समय_estimation_b, _LIFE_TIME_EST_B, 1);

अटल काष्ठा attribute *ufs_sysfs_health_descriptor[] = अणु
	&dev_attr_eol_info.attr,
	&dev_attr_lअगरe_समय_estimation_a.attr,
	&dev_attr_lअगरe_समय_estimation_b.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group ufs_sysfs_health_descriptor_group = अणु
	.name = "health_descriptor",
	.attrs = ufs_sysfs_health_descriptor,
पूर्ण;

#घोषणा UFS_POWER_DESC_PARAM(_name, _uname, _index)			\
अटल sमाप_प्रकार _name##_index##_show(काष्ठा device *dev,			\
	काष्ठा device_attribute *attr, अक्षर *buf)			\
अणु									\
	काष्ठा ufs_hba *hba = dev_get_drvdata(dev);			\
	वापस ufs_sysfs_पढ़ो_desc_param(hba, QUERY_DESC_IDN_POWER, 0,	\
		PWR_DESC##_uname##_0 + _index * 2, buf, 2);		\
पूर्ण									\
अटल DEVICE_ATTR_RO(_name##_index)

UFS_POWER_DESC_PARAM(active_icc_levels_vcc, _ACTIVE_LVLS_VCC, 0);
UFS_POWER_DESC_PARAM(active_icc_levels_vcc, _ACTIVE_LVLS_VCC, 1);
UFS_POWER_DESC_PARAM(active_icc_levels_vcc, _ACTIVE_LVLS_VCC, 2);
UFS_POWER_DESC_PARAM(active_icc_levels_vcc, _ACTIVE_LVLS_VCC, 3);
UFS_POWER_DESC_PARAM(active_icc_levels_vcc, _ACTIVE_LVLS_VCC, 4);
UFS_POWER_DESC_PARAM(active_icc_levels_vcc, _ACTIVE_LVLS_VCC, 5);
UFS_POWER_DESC_PARAM(active_icc_levels_vcc, _ACTIVE_LVLS_VCC, 6);
UFS_POWER_DESC_PARAM(active_icc_levels_vcc, _ACTIVE_LVLS_VCC, 7);
UFS_POWER_DESC_PARAM(active_icc_levels_vcc, _ACTIVE_LVLS_VCC, 8);
UFS_POWER_DESC_PARAM(active_icc_levels_vcc, _ACTIVE_LVLS_VCC, 9);
UFS_POWER_DESC_PARAM(active_icc_levels_vcc, _ACTIVE_LVLS_VCC, 10);
UFS_POWER_DESC_PARAM(active_icc_levels_vcc, _ACTIVE_LVLS_VCC, 11);
UFS_POWER_DESC_PARAM(active_icc_levels_vcc, _ACTIVE_LVLS_VCC, 12);
UFS_POWER_DESC_PARAM(active_icc_levels_vcc, _ACTIVE_LVLS_VCC, 13);
UFS_POWER_DESC_PARAM(active_icc_levels_vcc, _ACTIVE_LVLS_VCC, 14);
UFS_POWER_DESC_PARAM(active_icc_levels_vcc, _ACTIVE_LVLS_VCC, 15);
UFS_POWER_DESC_PARAM(active_icc_levels_vccq, _ACTIVE_LVLS_VCCQ, 0);
UFS_POWER_DESC_PARAM(active_icc_levels_vccq, _ACTIVE_LVLS_VCCQ, 1);
UFS_POWER_DESC_PARAM(active_icc_levels_vccq, _ACTIVE_LVLS_VCCQ, 2);
UFS_POWER_DESC_PARAM(active_icc_levels_vccq, _ACTIVE_LVLS_VCCQ, 3);
UFS_POWER_DESC_PARAM(active_icc_levels_vccq, _ACTIVE_LVLS_VCCQ, 4);
UFS_POWER_DESC_PARAM(active_icc_levels_vccq, _ACTIVE_LVLS_VCCQ, 5);
UFS_POWER_DESC_PARAM(active_icc_levels_vccq, _ACTIVE_LVLS_VCCQ, 6);
UFS_POWER_DESC_PARAM(active_icc_levels_vccq, _ACTIVE_LVLS_VCCQ, 7);
UFS_POWER_DESC_PARAM(active_icc_levels_vccq, _ACTIVE_LVLS_VCCQ, 8);
UFS_POWER_DESC_PARAM(active_icc_levels_vccq, _ACTIVE_LVLS_VCCQ, 9);
UFS_POWER_DESC_PARAM(active_icc_levels_vccq, _ACTIVE_LVLS_VCCQ, 10);
UFS_POWER_DESC_PARAM(active_icc_levels_vccq, _ACTIVE_LVLS_VCCQ, 11);
UFS_POWER_DESC_PARAM(active_icc_levels_vccq, _ACTIVE_LVLS_VCCQ, 12);
UFS_POWER_DESC_PARAM(active_icc_levels_vccq, _ACTIVE_LVLS_VCCQ, 13);
UFS_POWER_DESC_PARAM(active_icc_levels_vccq, _ACTIVE_LVLS_VCCQ, 14);
UFS_POWER_DESC_PARAM(active_icc_levels_vccq, _ACTIVE_LVLS_VCCQ, 15);
UFS_POWER_DESC_PARAM(active_icc_levels_vccq2, _ACTIVE_LVLS_VCCQ2, 0);
UFS_POWER_DESC_PARAM(active_icc_levels_vccq2, _ACTIVE_LVLS_VCCQ2, 1);
UFS_POWER_DESC_PARAM(active_icc_levels_vccq2, _ACTIVE_LVLS_VCCQ2, 2);
UFS_POWER_DESC_PARAM(active_icc_levels_vccq2, _ACTIVE_LVLS_VCCQ2, 3);
UFS_POWER_DESC_PARAM(active_icc_levels_vccq2, _ACTIVE_LVLS_VCCQ2, 4);
UFS_POWER_DESC_PARAM(active_icc_levels_vccq2, _ACTIVE_LVLS_VCCQ2, 5);
UFS_POWER_DESC_PARAM(active_icc_levels_vccq2, _ACTIVE_LVLS_VCCQ2, 6);
UFS_POWER_DESC_PARAM(active_icc_levels_vccq2, _ACTIVE_LVLS_VCCQ2, 7);
UFS_POWER_DESC_PARAM(active_icc_levels_vccq2, _ACTIVE_LVLS_VCCQ2, 8);
UFS_POWER_DESC_PARAM(active_icc_levels_vccq2, _ACTIVE_LVLS_VCCQ2, 9);
UFS_POWER_DESC_PARAM(active_icc_levels_vccq2, _ACTIVE_LVLS_VCCQ2, 10);
UFS_POWER_DESC_PARAM(active_icc_levels_vccq2, _ACTIVE_LVLS_VCCQ2, 11);
UFS_POWER_DESC_PARAM(active_icc_levels_vccq2, _ACTIVE_LVLS_VCCQ2, 12);
UFS_POWER_DESC_PARAM(active_icc_levels_vccq2, _ACTIVE_LVLS_VCCQ2, 13);
UFS_POWER_DESC_PARAM(active_icc_levels_vccq2, _ACTIVE_LVLS_VCCQ2, 14);
UFS_POWER_DESC_PARAM(active_icc_levels_vccq2, _ACTIVE_LVLS_VCCQ2, 15);

अटल काष्ठा attribute *ufs_sysfs_घातer_descriptor[] = अणु
	&dev_attr_active_icc_levels_vcc0.attr,
	&dev_attr_active_icc_levels_vcc1.attr,
	&dev_attr_active_icc_levels_vcc2.attr,
	&dev_attr_active_icc_levels_vcc3.attr,
	&dev_attr_active_icc_levels_vcc4.attr,
	&dev_attr_active_icc_levels_vcc5.attr,
	&dev_attr_active_icc_levels_vcc6.attr,
	&dev_attr_active_icc_levels_vcc7.attr,
	&dev_attr_active_icc_levels_vcc8.attr,
	&dev_attr_active_icc_levels_vcc9.attr,
	&dev_attr_active_icc_levels_vcc10.attr,
	&dev_attr_active_icc_levels_vcc11.attr,
	&dev_attr_active_icc_levels_vcc12.attr,
	&dev_attr_active_icc_levels_vcc13.attr,
	&dev_attr_active_icc_levels_vcc14.attr,
	&dev_attr_active_icc_levels_vcc15.attr,
	&dev_attr_active_icc_levels_vccq0.attr,
	&dev_attr_active_icc_levels_vccq1.attr,
	&dev_attr_active_icc_levels_vccq2.attr,
	&dev_attr_active_icc_levels_vccq3.attr,
	&dev_attr_active_icc_levels_vccq4.attr,
	&dev_attr_active_icc_levels_vccq5.attr,
	&dev_attr_active_icc_levels_vccq6.attr,
	&dev_attr_active_icc_levels_vccq7.attr,
	&dev_attr_active_icc_levels_vccq8.attr,
	&dev_attr_active_icc_levels_vccq9.attr,
	&dev_attr_active_icc_levels_vccq10.attr,
	&dev_attr_active_icc_levels_vccq11.attr,
	&dev_attr_active_icc_levels_vccq12.attr,
	&dev_attr_active_icc_levels_vccq13.attr,
	&dev_attr_active_icc_levels_vccq14.attr,
	&dev_attr_active_icc_levels_vccq15.attr,
	&dev_attr_active_icc_levels_vccq20.attr,
	&dev_attr_active_icc_levels_vccq21.attr,
	&dev_attr_active_icc_levels_vccq22.attr,
	&dev_attr_active_icc_levels_vccq23.attr,
	&dev_attr_active_icc_levels_vccq24.attr,
	&dev_attr_active_icc_levels_vccq25.attr,
	&dev_attr_active_icc_levels_vccq26.attr,
	&dev_attr_active_icc_levels_vccq27.attr,
	&dev_attr_active_icc_levels_vccq28.attr,
	&dev_attr_active_icc_levels_vccq29.attr,
	&dev_attr_active_icc_levels_vccq210.attr,
	&dev_attr_active_icc_levels_vccq211.attr,
	&dev_attr_active_icc_levels_vccq212.attr,
	&dev_attr_active_icc_levels_vccq213.attr,
	&dev_attr_active_icc_levels_vccq214.attr,
	&dev_attr_active_icc_levels_vccq215.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group ufs_sysfs_घातer_descriptor_group = अणु
	.name = "power_descriptor",
	.attrs = ufs_sysfs_घातer_descriptor,
पूर्ण;

#घोषणा UFS_STRING_DESCRIPTOR(_name, _pname)				\
अटल sमाप_प्रकार _name##_show(काष्ठा device *dev,				\
	काष्ठा device_attribute *attr, अक्षर *buf)			\
अणु									\
	u8 index;							\
	काष्ठा ufs_hba *hba = dev_get_drvdata(dev);			\
	पूर्णांक ret;							\
	पूर्णांक desc_len = QUERY_DESC_MAX_SIZE;				\
	u8 *desc_buf;							\
									\
	करोwn(&hba->host_sem);						\
	अगर (!ufshcd_is_user_access_allowed(hba)) अणु			\
		up(&hba->host_sem);					\
		वापस -EBUSY;						\
	पूर्ण								\
	desc_buf = kzalloc(QUERY_DESC_MAX_SIZE, GFP_ATOMIC);		\
	अगर (!desc_buf) अणु						\
		up(&hba->host_sem);					\
		वापस -ENOMEM;						\
	पूर्ण								\
	pm_runसमय_get_sync(hba->dev);					\
	ret = ufshcd_query_descriptor_retry(hba,			\
		UPIU_QUERY_OPCODE_READ_DESC, QUERY_DESC_IDN_DEVICE,	\
		0, 0, desc_buf, &desc_len);				\
	अगर (ret) अणु							\
		ret = -EINVAL;						\
		जाओ out;						\
	पूर्ण								\
	index = desc_buf[DEVICE_DESC_PARAM##_pname];			\
	kमुक्त(desc_buf);						\
	desc_buf = शून्य;						\
	ret = ufshcd_पढ़ो_string_desc(hba, index, &desc_buf,		\
				      SD_ASCII_STD);			\
	अगर (ret < 0)							\
		जाओ out;						\
	ret = sysfs_emit(buf, "%s\n", desc_buf);			\
out:									\
	pm_runसमय_put_sync(hba->dev);					\
	kमुक्त(desc_buf);						\
	up(&hba->host_sem);						\
	वापस ret;							\
पूर्ण									\
अटल DEVICE_ATTR_RO(_name)

UFS_STRING_DESCRIPTOR(manufacturer_name, _MANF_NAME);
UFS_STRING_DESCRIPTOR(product_name, _PRDCT_NAME);
UFS_STRING_DESCRIPTOR(oem_id, _OEM_ID);
UFS_STRING_DESCRIPTOR(serial_number, _SN);
UFS_STRING_DESCRIPTOR(product_revision, _PRDCT_REV);

अटल काष्ठा attribute *ufs_sysfs_string_descriptors[] = अणु
	&dev_attr_manufacturer_name.attr,
	&dev_attr_product_name.attr,
	&dev_attr_oem_id.attr,
	&dev_attr_serial_number.attr,
	&dev_attr_product_revision.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group ufs_sysfs_string_descriptors_group = अणु
	.name = "string_descriptors",
	.attrs = ufs_sysfs_string_descriptors,
पूर्ण;

अटल अंतरभूत bool ufshcd_is_wb_flags(क्रमागत flag_idn idn)
अणु
	वापस ((idn >= QUERY_FLAG_IDN_WB_EN) &&
		(idn <= QUERY_FLAG_IDN_WB_BUFF_FLUSH_DURING_HIBERN8));
पूर्ण

#घोषणा UFS_FLAG(_name, _uname)						\
अटल sमाप_प्रकार _name##_show(काष्ठा device *dev,				\
	काष्ठा device_attribute *attr, अक्षर *buf)			\
अणु									\
	bool flag;							\
	u8 index = 0;							\
	पूर्णांक ret;							\
	काष्ठा ufs_hba *hba = dev_get_drvdata(dev);			\
									\
	करोwn(&hba->host_sem);						\
	अगर (!ufshcd_is_user_access_allowed(hba)) अणु			\
		up(&hba->host_sem);					\
		वापस -EBUSY;						\
	पूर्ण								\
	अगर (ufshcd_is_wb_flags(QUERY_FLAG_IDN##_uname))			\
		index = ufshcd_wb_get_query_index(hba);			\
	pm_runसमय_get_sync(hba->dev);					\
	ret = ufshcd_query_flag(hba, UPIU_QUERY_OPCODE_READ_FLAG,	\
		QUERY_FLAG_IDN##_uname, index, &flag);			\
	pm_runसमय_put_sync(hba->dev);					\
	अगर (ret) अणु							\
		ret = -EINVAL;						\
		जाओ out;						\
	पूर्ण								\
	ret = sysfs_emit(buf, "%s\n", flag ? "true" : "false");		\
out:									\
	up(&hba->host_sem);						\
	वापस ret;							\
पूर्ण									\
अटल DEVICE_ATTR_RO(_name)

UFS_FLAG(device_init, _FDEVICEINIT);
UFS_FLAG(permanent_wpe, _PERMANENT_WPE);
UFS_FLAG(घातer_on_wpe, _PWR_ON_WPE);
UFS_FLAG(bkops_enable, _BKOPS_EN);
UFS_FLAG(lअगरe_span_mode_enable, _LIFE_SPAN_MODE_ENABLE);
UFS_FLAG(phy_resource_removal, _FPHYRESOURCEREMOVAL);
UFS_FLAG(busy_rtc, _BUSY_RTC);
UFS_FLAG(disable_fw_update, _PERMANENTLY_DISABLE_FW_UPDATE);
UFS_FLAG(wb_enable, _WB_EN);
UFS_FLAG(wb_flush_en, _WB_BUFF_FLUSH_EN);
UFS_FLAG(wb_flush_during_h8, _WB_BUFF_FLUSH_DURING_HIBERN8);

अटल काष्ठा attribute *ufs_sysfs_device_flags[] = अणु
	&dev_attr_device_init.attr,
	&dev_attr_permanent_wpe.attr,
	&dev_attr_घातer_on_wpe.attr,
	&dev_attr_bkops_enable.attr,
	&dev_attr_lअगरe_span_mode_enable.attr,
	&dev_attr_phy_resource_removal.attr,
	&dev_attr_busy_rtc.attr,
	&dev_attr_disable_fw_update.attr,
	&dev_attr_wb_enable.attr,
	&dev_attr_wb_flush_en.attr,
	&dev_attr_wb_flush_during_h8.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group ufs_sysfs_flags_group = अणु
	.name = "flags",
	.attrs = ufs_sysfs_device_flags,
पूर्ण;

अटल अंतरभूत bool ufshcd_is_wb_attrs(क्रमागत attr_idn idn)
अणु
	वापस ((idn >= QUERY_ATTR_IDN_WB_FLUSH_STATUS) &&
		(idn <= QUERY_ATTR_IDN_CURR_WB_BUFF_SIZE));
पूर्ण

#घोषणा UFS_ATTRIBUTE(_name, _uname)					\
अटल sमाप_प्रकार _name##_show(काष्ठा device *dev,				\
	काष्ठा device_attribute *attr, अक्षर *buf)			\
अणु									\
	काष्ठा ufs_hba *hba = dev_get_drvdata(dev);			\
	u32 value;							\
	पूर्णांक ret;							\
	u8 index = 0;							\
									\
	करोwn(&hba->host_sem);						\
	अगर (!ufshcd_is_user_access_allowed(hba)) अणु			\
		up(&hba->host_sem);					\
		वापस -EBUSY;						\
	पूर्ण								\
	अगर (ufshcd_is_wb_attrs(QUERY_ATTR_IDN##_uname))			\
		index = ufshcd_wb_get_query_index(hba);			\
	pm_runसमय_get_sync(hba->dev);					\
	ret = ufshcd_query_attr(hba, UPIU_QUERY_OPCODE_READ_ATTR,	\
		QUERY_ATTR_IDN##_uname, index, 0, &value);		\
	pm_runसमय_put_sync(hba->dev);					\
	अगर (ret) अणु							\
		ret = -EINVAL;						\
		जाओ out;						\
	पूर्ण								\
	ret = sysfs_emit(buf, "0x%08X\n", value);			\
out:									\
	up(&hba->host_sem);						\
	वापस ret;							\
पूर्ण									\
अटल DEVICE_ATTR_RO(_name)

UFS_ATTRIBUTE(boot_lun_enabled, _BOOT_LU_EN);
UFS_ATTRIBUTE(current_घातer_mode, _POWER_MODE);
UFS_ATTRIBUTE(active_icc_level, _ACTIVE_ICC_LVL);
UFS_ATTRIBUTE(ooo_data_enabled, _OOO_DATA_EN);
UFS_ATTRIBUTE(bkops_status, _BKOPS_STATUS);
UFS_ATTRIBUTE(purge_status, _PURGE_STATUS);
UFS_ATTRIBUTE(max_data_in_size, _MAX_DATA_IN);
UFS_ATTRIBUTE(max_data_out_size, _MAX_DATA_OUT);
UFS_ATTRIBUTE(reference_घड़ी_frequency, _REF_CLK_FREQ);
UFS_ATTRIBUTE(configuration_descriptor_lock, _CONF_DESC_LOCK);
UFS_ATTRIBUTE(max_number_of_rtt, _MAX_NUM_OF_RTT);
UFS_ATTRIBUTE(exception_event_control, _EE_CONTROL);
UFS_ATTRIBUTE(exception_event_status, _EE_STATUS);
UFS_ATTRIBUTE(ffu_status, _FFU_STATUS);
UFS_ATTRIBUTE(psa_state, _PSA_STATE);
UFS_ATTRIBUTE(psa_data_size, _PSA_DATA_SIZE);
UFS_ATTRIBUTE(wb_flush_status, _WB_FLUSH_STATUS);
UFS_ATTRIBUTE(wb_avail_buf, _AVAIL_WB_BUFF_SIZE);
UFS_ATTRIBUTE(wb_lअगरe_समय_est, _WB_BUFF_LIFE_TIME_EST);
UFS_ATTRIBUTE(wb_cur_buf, _CURR_WB_BUFF_SIZE);


अटल काष्ठा attribute *ufs_sysfs_attributes[] = अणु
	&dev_attr_boot_lun_enabled.attr,
	&dev_attr_current_घातer_mode.attr,
	&dev_attr_active_icc_level.attr,
	&dev_attr_ooo_data_enabled.attr,
	&dev_attr_bkops_status.attr,
	&dev_attr_purge_status.attr,
	&dev_attr_max_data_in_size.attr,
	&dev_attr_max_data_out_size.attr,
	&dev_attr_reference_घड़ी_frequency.attr,
	&dev_attr_configuration_descriptor_lock.attr,
	&dev_attr_max_number_of_rtt.attr,
	&dev_attr_exception_event_control.attr,
	&dev_attr_exception_event_status.attr,
	&dev_attr_ffu_status.attr,
	&dev_attr_psa_state.attr,
	&dev_attr_psa_data_size.attr,
	&dev_attr_wb_flush_status.attr,
	&dev_attr_wb_avail_buf.attr,
	&dev_attr_wb_lअगरe_समय_est.attr,
	&dev_attr_wb_cur_buf.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group ufs_sysfs_attributes_group = अणु
	.name = "attributes",
	.attrs = ufs_sysfs_attributes,
पूर्ण;

अटल स्थिर काष्ठा attribute_group *ufs_sysfs_groups[] = अणु
	&ufs_sysfs_शेष_group,
	&ufs_sysfs_device_descriptor_group,
	&ufs_sysfs_पूर्णांकerconnect_descriptor_group,
	&ufs_sysfs_geometry_descriptor_group,
	&ufs_sysfs_health_descriptor_group,
	&ufs_sysfs_घातer_descriptor_group,
	&ufs_sysfs_string_descriptors_group,
	&ufs_sysfs_flags_group,
	&ufs_sysfs_attributes_group,
	शून्य,
पूर्ण;

#घोषणा UFS_LUN_DESC_PARAM(_pname, _puname, _duname, _size)		\
अटल sमाप_प्रकार _pname##_show(काष्ठा device *dev,			\
	काष्ठा device_attribute *attr, अक्षर *buf)			\
अणु									\
	काष्ठा scsi_device *sdev = to_scsi_device(dev);			\
	काष्ठा ufs_hba *hba = shost_priv(sdev->host);			\
	u8 lun = ufshcd_scsi_to_upiu_lun(sdev->lun);			\
	अगर (!ufs_is_valid_unit_desc_lun(&hba->dev_info, lun,		\
				_duname##_DESC_PARAM##_puname))		\
		वापस -EINVAL;						\
	वापस ufs_sysfs_पढ़ो_desc_param(hba, QUERY_DESC_IDN_##_duname,	\
		lun, _duname##_DESC_PARAM##_puname, buf, _size);	\
पूर्ण									\
अटल DEVICE_ATTR_RO(_pname)

#घोषणा UFS_UNIT_DESC_PARAM(_name, _uname, _size)			\
	UFS_LUN_DESC_PARAM(_name, _uname, UNIT, _size)

UFS_UNIT_DESC_PARAM(boot_lun_id, _BOOT_LUN_ID, 1);
UFS_UNIT_DESC_PARAM(lun_ग_लिखो_protect, _LU_WR_PROTECT, 1);
UFS_UNIT_DESC_PARAM(lun_queue_depth, _LU_Q_DEPTH, 1);
UFS_UNIT_DESC_PARAM(psa_sensitive, _PSA_SENSITIVE, 1);
UFS_UNIT_DESC_PARAM(lun_memory_type, _MEM_TYPE, 1);
UFS_UNIT_DESC_PARAM(data_reliability, _DATA_RELIABILITY, 1);
UFS_UNIT_DESC_PARAM(logical_block_size, _LOGICAL_BLK_SIZE, 1);
UFS_UNIT_DESC_PARAM(logical_block_count, _LOGICAL_BLK_COUNT, 8);
UFS_UNIT_DESC_PARAM(erase_block_size, _ERASE_BLK_SIZE, 4);
UFS_UNIT_DESC_PARAM(provisioning_type, _PROVISIONING_TYPE, 1);
UFS_UNIT_DESC_PARAM(physical_memory_resourse_count, _PHY_MEM_RSRC_CNT, 8);
UFS_UNIT_DESC_PARAM(context_capabilities, _CTX_CAPABILITIES, 2);
UFS_UNIT_DESC_PARAM(large_unit_granularity, _LARGE_UNIT_SIZE_M1, 1);
UFS_UNIT_DESC_PARAM(wb_buf_alloc_units, _WB_BUF_ALLOC_UNITS, 4);


अटल काष्ठा attribute *ufs_sysfs_unit_descriptor[] = अणु
	&dev_attr_boot_lun_id.attr,
	&dev_attr_lun_ग_लिखो_protect.attr,
	&dev_attr_lun_queue_depth.attr,
	&dev_attr_psa_sensitive.attr,
	&dev_attr_lun_memory_type.attr,
	&dev_attr_data_reliability.attr,
	&dev_attr_logical_block_size.attr,
	&dev_attr_logical_block_count.attr,
	&dev_attr_erase_block_size.attr,
	&dev_attr_provisioning_type.attr,
	&dev_attr_physical_memory_resourse_count.attr,
	&dev_attr_context_capabilities.attr,
	&dev_attr_large_unit_granularity.attr,
	&dev_attr_wb_buf_alloc_units.attr,
	शून्य,
पूर्ण;

स्थिर काष्ठा attribute_group ufs_sysfs_unit_descriptor_group = अणु
	.name = "unit_descriptor",
	.attrs = ufs_sysfs_unit_descriptor,
पूर्ण;

अटल sमाप_प्रकार dyn_cap_needed_attribute_show(काष्ठा device *dev,
	काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	u32 value;
	काष्ठा scsi_device *sdev = to_scsi_device(dev);
	काष्ठा ufs_hba *hba = shost_priv(sdev->host);
	u8 lun = ufshcd_scsi_to_upiu_lun(sdev->lun);
	पूर्णांक ret;

	करोwn(&hba->host_sem);
	अगर (!ufshcd_is_user_access_allowed(hba)) अणु
		ret = -EBUSY;
		जाओ out;
	पूर्ण

	pm_runसमय_get_sync(hba->dev);
	ret = ufshcd_query_attr(hba, UPIU_QUERY_OPCODE_READ_ATTR,
		QUERY_ATTR_IDN_DYN_CAP_NEEDED, lun, 0, &value);
	pm_runसमय_put_sync(hba->dev);
	अगर (ret) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	ret = sysfs_emit(buf, "0x%08X\n", value);

out:
	up(&hba->host_sem);
	वापस ret;
पूर्ण
अटल DEVICE_ATTR_RO(dyn_cap_needed_attribute);

अटल काष्ठा attribute *ufs_sysfs_lun_attributes[] = अणु
	&dev_attr_dyn_cap_needed_attribute.attr,
	शून्य,
पूर्ण;

स्थिर काष्ठा attribute_group ufs_sysfs_lun_attributes_group = अणु
	.attrs = ufs_sysfs_lun_attributes,
पूर्ण;

व्योम ufs_sysfs_add_nodes(काष्ठा device *dev)
अणु
	पूर्णांक ret;

	ret = sysfs_create_groups(&dev->kobj, ufs_sysfs_groups);
	अगर (ret)
		dev_err(dev,
			"%s: sysfs groups creation failed (err = %d)\n",
			__func__, ret);
पूर्ण

व्योम ufs_sysfs_हटाओ_nodes(काष्ठा device *dev)
अणु
	sysfs_हटाओ_groups(&dev->kobj, ufs_sysfs_groups);
पूर्ण
