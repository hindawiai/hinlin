<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*******************************************************************************
 * Filename:  target_core_stat.c
 *
 * Modern ConfigFS group context specअगरic statistics based on original
 * target_core_mib.c code
 *
 * (c) Copyright 2006-2013 Datera, Inc.
 *
 * Nicholas A. Bellinger <nab@linux-iscsi.org>
 *
 ******************************************************************************/

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/delay.h>
#समावेश <linux/समयr.h>
#समावेश <linux/माला.स>
#समावेश <linux/utsname.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/configfs.h>

#समावेश <target/target_core_base.h>
#समावेश <target/target_core_backend.h>
#समावेश <target/target_core_fabric.h>

#समावेश "target_core_internal.h"

#अगर_अघोषित INITIAL_JIFFIES
#घोषणा INITIAL_JIFFIES ((अचिन्हित दीर्घ)(अचिन्हित पूर्णांक) (-300*HZ))
#पूर्ण_अगर

#घोषणा SCSI_LU_INDEX			1
#घोषणा LU_COUNT			1

/*
 * SCSI Device Table
 */

अटल काष्ठा se_device *to_stat_dev(काष्ठा config_item *item)
अणु
	काष्ठा se_dev_stat_grps *sgrps = container_of(to_config_group(item),
			काष्ठा se_dev_stat_grps, scsi_dev_group);
	वापस container_of(sgrps, काष्ठा se_device, dev_stat_grps);
पूर्ण

अटल sमाप_प्रकार target_stat_inst_show(काष्ठा config_item *item, अक्षर *page)
अणु
	काष्ठा se_hba *hba = to_stat_dev(item)->se_hba;

	वापस snम_लिखो(page, PAGE_SIZE, "%u\n", hba->hba_index);
पूर्ण

अटल sमाप_प्रकार target_stat_indx_show(काष्ठा config_item *item, अक्षर *page)
अणु
	वापस snम_लिखो(page, PAGE_SIZE, "%u\n", to_stat_dev(item)->dev_index);
पूर्ण

अटल sमाप_प्रकार target_stat_role_show(काष्ठा config_item *item, अक्षर *page)
अणु
	वापस snम_लिखो(page, PAGE_SIZE, "Target\n");
पूर्ण

अटल sमाप_प्रकार target_stat_ports_show(काष्ठा config_item *item, अक्षर *page)
अणु
	वापस snम_लिखो(page, PAGE_SIZE, "%u\n", to_stat_dev(item)->export_count);
पूर्ण

CONFIGFS_ATTR_RO(target_stat_, inst);
CONFIGFS_ATTR_RO(target_stat_, indx);
CONFIGFS_ATTR_RO(target_stat_, role);
CONFIGFS_ATTR_RO(target_stat_, ports);

अटल काष्ठा configfs_attribute *target_stat_scsi_dev_attrs[] = अणु
	&target_stat_attr_inst,
	&target_stat_attr_indx,
	&target_stat_attr_role,
	&target_stat_attr_ports,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा config_item_type target_stat_scsi_dev_cit = अणु
	.ct_attrs		= target_stat_scsi_dev_attrs,
	.ct_owner		= THIS_MODULE,
पूर्ण;

/*
 * SCSI Target Device Table
 */
अटल काष्ठा se_device *to_stat_tgt_dev(काष्ठा config_item *item)
अणु
	काष्ठा se_dev_stat_grps *sgrps = container_of(to_config_group(item),
			काष्ठा se_dev_stat_grps, scsi_tgt_dev_group);
	वापस container_of(sgrps, काष्ठा se_device, dev_stat_grps);
पूर्ण

अटल sमाप_प्रकार target_stat_tgt_inst_show(काष्ठा config_item *item, अक्षर *page)
अणु
	काष्ठा se_hba *hba = to_stat_tgt_dev(item)->se_hba;

	वापस snम_लिखो(page, PAGE_SIZE, "%u\n", hba->hba_index);
पूर्ण

अटल sमाप_प्रकार target_stat_tgt_indx_show(काष्ठा config_item *item, अक्षर *page)
अणु
	वापस snम_लिखो(page, PAGE_SIZE, "%u\n", to_stat_tgt_dev(item)->dev_index);
पूर्ण

अटल sमाप_प्रकार target_stat_tgt_num_lus_show(काष्ठा config_item *item,
		अक्षर *page)
अणु
	वापस snम_लिखो(page, PAGE_SIZE, "%u\n", LU_COUNT);
पूर्ण

अटल sमाप_प्रकार target_stat_tgt_status_show(काष्ठा config_item *item,
		अक्षर *page)
अणु
	अगर (to_stat_tgt_dev(item)->export_count)
		वापस snम_लिखो(page, PAGE_SIZE, "activated");
	अन्यथा
		वापस snम_लिखो(page, PAGE_SIZE, "deactivated");
पूर्ण

अटल sमाप_प्रकार target_stat_tgt_non_access_lus_show(काष्ठा config_item *item,
		अक्षर *page)
अणु
	पूर्णांक non_accessible_lus;

	अगर (to_stat_tgt_dev(item)->export_count)
		non_accessible_lus = 0;
	अन्यथा
		non_accessible_lus = 1;

	वापस snम_लिखो(page, PAGE_SIZE, "%u\n", non_accessible_lus);
पूर्ण

अटल sमाप_प्रकार target_stat_tgt_resets_show(काष्ठा config_item *item,
		अक्षर *page)
अणु
	वापस snम_लिखो(page, PAGE_SIZE, "%lu\n",
			atomic_दीर्घ_पढ़ो(&to_stat_tgt_dev(item)->num_resets));
पूर्ण

अटल sमाप_प्रकार target_stat_tgt_पातs_complete_show(काष्ठा config_item *item,
		अक्षर *page)
अणु
	वापस snम_लिखो(page, PAGE_SIZE, "%lu\n",
			atomic_दीर्घ_पढ़ो(&to_stat_tgt_dev(item)->पातs_complete));
पूर्ण

अटल sमाप_प्रकार target_stat_tgt_पातs_no_task_show(काष्ठा config_item *item,
		अक्षर *page)
अणु
	वापस snम_लिखो(page, PAGE_SIZE, "%lu\n",
			atomic_दीर्घ_पढ़ो(&to_stat_tgt_dev(item)->पातs_no_task));
पूर्ण

CONFIGFS_ATTR_RO(target_stat_tgt_, inst);
CONFIGFS_ATTR_RO(target_stat_tgt_, indx);
CONFIGFS_ATTR_RO(target_stat_tgt_, num_lus);
CONFIGFS_ATTR_RO(target_stat_tgt_, status);
CONFIGFS_ATTR_RO(target_stat_tgt_, non_access_lus);
CONFIGFS_ATTR_RO(target_stat_tgt_, resets);
CONFIGFS_ATTR_RO(target_stat_tgt_, पातs_complete);
CONFIGFS_ATTR_RO(target_stat_tgt_, पातs_no_task);

अटल काष्ठा configfs_attribute *target_stat_scsi_tgt_dev_attrs[] = अणु
	&target_stat_tgt_attr_inst,
	&target_stat_tgt_attr_indx,
	&target_stat_tgt_attr_num_lus,
	&target_stat_tgt_attr_status,
	&target_stat_tgt_attr_non_access_lus,
	&target_stat_tgt_attr_resets,
	&target_stat_tgt_attr_पातs_complete,
	&target_stat_tgt_attr_पातs_no_task,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा config_item_type target_stat_scsi_tgt_dev_cit = अणु
	.ct_attrs		= target_stat_scsi_tgt_dev_attrs,
	.ct_owner		= THIS_MODULE,
पूर्ण;

/*
 * SCSI Logical Unit Table
 */

अटल काष्ठा se_device *to_stat_lu_dev(काष्ठा config_item *item)
अणु
	काष्ठा se_dev_stat_grps *sgrps = container_of(to_config_group(item),
			काष्ठा se_dev_stat_grps, scsi_lu_group);
	वापस container_of(sgrps, काष्ठा se_device, dev_stat_grps);
पूर्ण

अटल sमाप_प्रकार target_stat_lu_inst_show(काष्ठा config_item *item, अक्षर *page)
अणु
	काष्ठा se_hba *hba = to_stat_lu_dev(item)->se_hba;

	वापस snम_लिखो(page, PAGE_SIZE, "%u\n", hba->hba_index);
पूर्ण

अटल sमाप_प्रकार target_stat_lu_dev_show(काष्ठा config_item *item, अक्षर *page)
अणु
	वापस snम_लिखो(page, PAGE_SIZE, "%u\n",
			to_stat_lu_dev(item)->dev_index);
पूर्ण

अटल sमाप_प्रकार target_stat_lu_indx_show(काष्ठा config_item *item, अक्षर *page)
अणु
	वापस snम_लिखो(page, PAGE_SIZE, "%u\n", SCSI_LU_INDEX);
पूर्ण

अटल sमाप_प्रकार target_stat_lu_lun_show(काष्ठा config_item *item, अक्षर *page)
अणु
	/* FIXME: scsiLuDefaultLun */
	वापस snम_लिखो(page, PAGE_SIZE, "%llu\n", (अचिन्हित दीर्घ दीर्घ)0);
पूर्ण

अटल sमाप_प्रकार target_stat_lu_lu_name_show(काष्ठा config_item *item, अक्षर *page)
अणु
	काष्ठा se_device *dev = to_stat_lu_dev(item);

	/* scsiLuWwnName */
	वापस snम_लिखो(page, PAGE_SIZE, "%s\n",
			(म_माप(dev->t10_wwn.unit_serial)) ?
			dev->t10_wwn.unit_serial : "None");
पूर्ण

अटल sमाप_प्रकार target_stat_lu_vend_show(काष्ठा config_item *item, अक्षर *page)
अणु
	काष्ठा se_device *dev = to_stat_lu_dev(item);

	वापस snम_लिखो(page, PAGE_SIZE, "%-" __stringअगरy(INQUIRY_VENDOR_LEN)
			"s\n", dev->t10_wwn.venकरोr);
पूर्ण

अटल sमाप_प्रकार target_stat_lu_prod_show(काष्ठा config_item *item, अक्षर *page)
अणु
	काष्ठा se_device *dev = to_stat_lu_dev(item);

	वापस snम_लिखो(page, PAGE_SIZE, "%-" __stringअगरy(INQUIRY_MODEL_LEN)
			"s\n", dev->t10_wwn.model);
पूर्ण

अटल sमाप_प्रकार target_stat_lu_rev_show(काष्ठा config_item *item, अक्षर *page)
अणु
	काष्ठा se_device *dev = to_stat_lu_dev(item);

	वापस snम_लिखो(page, PAGE_SIZE, "%-" __stringअगरy(INQUIRY_REVISION_LEN)
			"s\n", dev->t10_wwn.revision);
पूर्ण

अटल sमाप_प्रकार target_stat_lu_dev_type_show(काष्ठा config_item *item, अक्षर *page)
अणु
	काष्ठा se_device *dev = to_stat_lu_dev(item);

	/* scsiLuPeripheralType */
	वापस snम_लिखो(page, PAGE_SIZE, "%u\n",
			dev->transport->get_device_type(dev));
पूर्ण

अटल sमाप_प्रकार target_stat_lu_status_show(काष्ठा config_item *item, अक्षर *page)
अणु
	काष्ठा se_device *dev = to_stat_lu_dev(item);

	/* scsiLuStatus */
	वापस snम_लिखो(page, PAGE_SIZE, "%s\n",
		(dev->export_count) ? "available" : "notavailable");
पूर्ण

अटल sमाप_प्रकार target_stat_lu_state_bit_show(काष्ठा config_item *item,
		अक्षर *page)
अणु
	/* scsiLuState */
	वापस snम_लिखो(page, PAGE_SIZE, "exposed\n");
पूर्ण

अटल sमाप_प्रकार target_stat_lu_num_cmds_show(काष्ठा config_item *item,
		अक्षर *page)
अणु
	काष्ठा se_device *dev = to_stat_lu_dev(item);

	/* scsiLuNumCommands */
	वापस snम_लिखो(page, PAGE_SIZE, "%lu\n",
			atomic_दीर्घ_पढ़ो(&dev->num_cmds));
पूर्ण

अटल sमाप_प्रकार target_stat_lu_पढ़ो_mbytes_show(काष्ठा config_item *item,
		अक्षर *page)
अणु
	काष्ठा se_device *dev = to_stat_lu_dev(item);

	/* scsiLuReadMegaBytes */
	वापस snम_लिखो(page, PAGE_SIZE, "%lu\n",
			atomic_दीर्घ_पढ़ो(&dev->पढ़ो_bytes) >> 20);
पूर्ण

अटल sमाप_प्रकार target_stat_lu_ग_लिखो_mbytes_show(काष्ठा config_item *item,
		अक्षर *page)
अणु
	काष्ठा se_device *dev = to_stat_lu_dev(item);

	/* scsiLuWrittenMegaBytes */
	वापस snम_लिखो(page, PAGE_SIZE, "%lu\n",
			atomic_दीर्घ_पढ़ो(&dev->ग_लिखो_bytes) >> 20);
पूर्ण

अटल sमाप_प्रकार target_stat_lu_resets_show(काष्ठा config_item *item, अक्षर *page)
अणु
	काष्ठा se_device *dev = to_stat_lu_dev(item);

	/* scsiLuInResets */
	वापस snम_लिखो(page, PAGE_SIZE, "%lu\n",
		atomic_दीर्घ_पढ़ो(&dev->num_resets));
पूर्ण

अटल sमाप_प्रकार target_stat_lu_full_stat_show(काष्ठा config_item *item,
		अक्षर *page)
अणु
	/* FIXME: scsiLuOutTaskSetFullStatus */
	वापस snम_लिखो(page, PAGE_SIZE, "%u\n", 0);
पूर्ण

अटल sमाप_प्रकार target_stat_lu_hs_num_cmds_show(काष्ठा config_item *item,
		अक्षर *page)
अणु
	/* FIXME: scsiLuHSInCommands */
	वापस snम_लिखो(page, PAGE_SIZE, "%u\n", 0);
पूर्ण

अटल sमाप_प्रकार target_stat_lu_creation_समय_show(काष्ठा config_item *item,
		अक्षर *page)
अणु
	काष्ठा se_device *dev = to_stat_lu_dev(item);

	/* scsiLuCreationTime */
	वापस snम_लिखो(page, PAGE_SIZE, "%u\n", (u32)(((u32)dev->creation_समय -
				INITIAL_JIFFIES) * 100 / HZ));
पूर्ण

CONFIGFS_ATTR_RO(target_stat_lu_, inst);
CONFIGFS_ATTR_RO(target_stat_lu_, dev);
CONFIGFS_ATTR_RO(target_stat_lu_, indx);
CONFIGFS_ATTR_RO(target_stat_lu_, lun);
CONFIGFS_ATTR_RO(target_stat_lu_, lu_name);
CONFIGFS_ATTR_RO(target_stat_lu_, vend);
CONFIGFS_ATTR_RO(target_stat_lu_, prod);
CONFIGFS_ATTR_RO(target_stat_lu_, rev);
CONFIGFS_ATTR_RO(target_stat_lu_, dev_type);
CONFIGFS_ATTR_RO(target_stat_lu_, status);
CONFIGFS_ATTR_RO(target_stat_lu_, state_bit);
CONFIGFS_ATTR_RO(target_stat_lu_, num_cmds);
CONFIGFS_ATTR_RO(target_stat_lu_, पढ़ो_mbytes);
CONFIGFS_ATTR_RO(target_stat_lu_, ग_लिखो_mbytes);
CONFIGFS_ATTR_RO(target_stat_lu_, resets);
CONFIGFS_ATTR_RO(target_stat_lu_, full_stat);
CONFIGFS_ATTR_RO(target_stat_lu_, hs_num_cmds);
CONFIGFS_ATTR_RO(target_stat_lu_, creation_समय);

अटल काष्ठा configfs_attribute *target_stat_scsi_lu_attrs[] = अणु
	&target_stat_lu_attr_inst,
	&target_stat_lu_attr_dev,
	&target_stat_lu_attr_indx,
	&target_stat_lu_attr_lun,
	&target_stat_lu_attr_lu_name,
	&target_stat_lu_attr_vend,
	&target_stat_lu_attr_prod,
	&target_stat_lu_attr_rev,
	&target_stat_lu_attr_dev_type,
	&target_stat_lu_attr_status,
	&target_stat_lu_attr_state_bit,
	&target_stat_lu_attr_num_cmds,
	&target_stat_lu_attr_पढ़ो_mbytes,
	&target_stat_lu_attr_ग_लिखो_mbytes,
	&target_stat_lu_attr_resets,
	&target_stat_lu_attr_full_stat,
	&target_stat_lu_attr_hs_num_cmds,
	&target_stat_lu_attr_creation_समय,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा config_item_type target_stat_scsi_lu_cit = अणु
	.ct_attrs		= target_stat_scsi_lu_attrs,
	.ct_owner		= THIS_MODULE,
पूर्ण;

/*
 * Called from target_core_configfs.c:target_core_make_subdev() to setup
 * the target statistics groups + configfs CITs located in target_core_stat.c
 */
व्योम target_stat_setup_dev_शेष_groups(काष्ठा se_device *dev)
अणु
	config_group_init_type_name(&dev->dev_stat_grps.scsi_dev_group,
			"scsi_dev", &target_stat_scsi_dev_cit);
	configfs_add_शेष_group(&dev->dev_stat_grps.scsi_dev_group,
			&dev->dev_stat_grps.stat_group);

	config_group_init_type_name(&dev->dev_stat_grps.scsi_tgt_dev_group,
			"scsi_tgt_dev", &target_stat_scsi_tgt_dev_cit);
	configfs_add_शेष_group(&dev->dev_stat_grps.scsi_tgt_dev_group,
			&dev->dev_stat_grps.stat_group);

	config_group_init_type_name(&dev->dev_stat_grps.scsi_lu_group,
			"scsi_lu", &target_stat_scsi_lu_cit);
	configfs_add_शेष_group(&dev->dev_stat_grps.scsi_lu_group,
			&dev->dev_stat_grps.stat_group);
पूर्ण

/*
 * SCSI Port Table
 */

अटल काष्ठा se_lun *to_stat_port(काष्ठा config_item *item)
अणु
	काष्ठा se_port_stat_grps *pgrps = container_of(to_config_group(item),
			काष्ठा se_port_stat_grps, scsi_port_group);
	वापस container_of(pgrps, काष्ठा se_lun, port_stat_grps);
पूर्ण

अटल sमाप_प्रकार target_stat_port_inst_show(काष्ठा config_item *item, अक्षर *page)
अणु
	काष्ठा se_lun *lun = to_stat_port(item);
	काष्ठा se_device *dev;
	sमाप_प्रकार ret = -ENODEV;

	rcu_पढ़ो_lock();
	dev = rcu_dereference(lun->lun_se_dev);
	अगर (dev)
		ret = snम_लिखो(page, PAGE_SIZE, "%u\n", dev->hba_index);
	rcu_पढ़ो_unlock();
	वापस ret;
पूर्ण

अटल sमाप_प्रकार target_stat_port_dev_show(काष्ठा config_item *item, अक्षर *page)
अणु
	काष्ठा se_lun *lun = to_stat_port(item);
	काष्ठा se_device *dev;
	sमाप_प्रकार ret = -ENODEV;

	rcu_पढ़ो_lock();
	dev = rcu_dereference(lun->lun_se_dev);
	अगर (dev)
		ret = snम_लिखो(page, PAGE_SIZE, "%u\n", dev->dev_index);
	rcu_पढ़ो_unlock();
	वापस ret;
पूर्ण

अटल sमाप_प्रकार target_stat_port_indx_show(काष्ठा config_item *item, अक्षर *page)
अणु
	काष्ठा se_lun *lun = to_stat_port(item);
	काष्ठा se_device *dev;
	sमाप_प्रकार ret = -ENODEV;

	rcu_पढ़ो_lock();
	dev = rcu_dereference(lun->lun_se_dev);
	अगर (dev)
		ret = snम_लिखो(page, PAGE_SIZE, "%u\n", lun->lun_rtpi);
	rcu_पढ़ो_unlock();
	वापस ret;
पूर्ण

अटल sमाप_प्रकार target_stat_port_role_show(काष्ठा config_item *item, अक्षर *page)
अणु
	काष्ठा se_lun *lun = to_stat_port(item);
	काष्ठा se_device *dev;
	sमाप_प्रकार ret = -ENODEV;

	rcu_पढ़ो_lock();
	dev = rcu_dereference(lun->lun_se_dev);
	अगर (dev)
		ret = snम_लिखो(page, PAGE_SIZE, "%s%u\n", "Device", dev->dev_index);
	rcu_पढ़ो_unlock();
	वापस ret;
पूर्ण

अटल sमाप_प्रकार target_stat_port_busy_count_show(काष्ठा config_item *item,
		अक्षर *page)
अणु
	काष्ठा se_lun *lun = to_stat_port(item);
	काष्ठा se_device *dev;
	sमाप_प्रकार ret = -ENODEV;

	rcu_पढ़ो_lock();
	dev = rcu_dereference(lun->lun_se_dev);
	अगर (dev) अणु
		/* FIXME: scsiPortBusyStatuses  */
		ret = snम_लिखो(page, PAGE_SIZE, "%u\n", 0);
	पूर्ण
	rcu_पढ़ो_unlock();
	वापस ret;
पूर्ण

CONFIGFS_ATTR_RO(target_stat_port_, inst);
CONFIGFS_ATTR_RO(target_stat_port_, dev);
CONFIGFS_ATTR_RO(target_stat_port_, indx);
CONFIGFS_ATTR_RO(target_stat_port_, role);
CONFIGFS_ATTR_RO(target_stat_port_, busy_count);

अटल काष्ठा configfs_attribute *target_stat_scsi_port_attrs[] = अणु
	&target_stat_port_attr_inst,
	&target_stat_port_attr_dev,
	&target_stat_port_attr_indx,
	&target_stat_port_attr_role,
	&target_stat_port_attr_busy_count,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा config_item_type target_stat_scsi_port_cit = अणु
	.ct_attrs		= target_stat_scsi_port_attrs,
	.ct_owner		= THIS_MODULE,
पूर्ण;

/*
 * SCSI Target Port Table
 */
अटल काष्ठा se_lun *to_stat_tgt_port(काष्ठा config_item *item)
अणु
	काष्ठा se_port_stat_grps *pgrps = container_of(to_config_group(item),
			काष्ठा se_port_stat_grps, scsi_tgt_port_group);
	वापस container_of(pgrps, काष्ठा se_lun, port_stat_grps);
पूर्ण

अटल sमाप_प्रकार target_stat_tgt_port_inst_show(काष्ठा config_item *item,
		अक्षर *page)
अणु
	काष्ठा se_lun *lun = to_stat_tgt_port(item);
	काष्ठा se_device *dev;
	sमाप_प्रकार ret = -ENODEV;

	rcu_पढ़ो_lock();
	dev = rcu_dereference(lun->lun_se_dev);
	अगर (dev)
		ret = snम_लिखो(page, PAGE_SIZE, "%u\n", dev->hba_index);
	rcu_पढ़ो_unlock();
	वापस ret;
पूर्ण

अटल sमाप_प्रकार target_stat_tgt_port_dev_show(काष्ठा config_item *item,
		अक्षर *page)
अणु
	काष्ठा se_lun *lun = to_stat_tgt_port(item);
	काष्ठा se_device *dev;
	sमाप_प्रकार ret = -ENODEV;

	rcu_पढ़ो_lock();
	dev = rcu_dereference(lun->lun_se_dev);
	अगर (dev)
		ret = snम_लिखो(page, PAGE_SIZE, "%u\n", dev->dev_index);
	rcu_पढ़ो_unlock();
	वापस ret;
पूर्ण

अटल sमाप_प्रकार target_stat_tgt_port_indx_show(काष्ठा config_item *item,
		अक्षर *page)
अणु
	काष्ठा se_lun *lun = to_stat_tgt_port(item);
	काष्ठा se_device *dev;
	sमाप_प्रकार ret = -ENODEV;

	rcu_पढ़ो_lock();
	dev = rcu_dereference(lun->lun_se_dev);
	अगर (dev)
		ret = snम_लिखो(page, PAGE_SIZE, "%u\n", lun->lun_rtpi);
	rcu_पढ़ो_unlock();
	वापस ret;
पूर्ण

अटल sमाप_प्रकार target_stat_tgt_port_name_show(काष्ठा config_item *item,
		अक्षर *page)
अणु
	काष्ठा se_lun *lun = to_stat_tgt_port(item);
	काष्ठा se_portal_group *tpg = lun->lun_tpg;
	काष्ठा se_device *dev;
	sमाप_प्रकार ret = -ENODEV;

	rcu_पढ़ो_lock();
	dev = rcu_dereference(lun->lun_se_dev);
	अगर (dev)
		ret = snम_लिखो(page, PAGE_SIZE, "%sPort#%u\n",
			tpg->se_tpg_tfo->fabric_name,
			lun->lun_rtpi);
	rcu_पढ़ो_unlock();
	वापस ret;
पूर्ण

अटल sमाप_प्रकार target_stat_tgt_port_port_index_show(काष्ठा config_item *item,
		अक्षर *page)
अणु
	काष्ठा se_lun *lun = to_stat_tgt_port(item);
	काष्ठा se_portal_group *tpg = lun->lun_tpg;
	काष्ठा se_device *dev;
	sमाप_प्रकार ret = -ENODEV;

	rcu_पढ़ो_lock();
	dev = rcu_dereference(lun->lun_se_dev);
	अगर (dev)
		ret = snम_लिखो(page, PAGE_SIZE, "%s%s%d\n",
			tpg->se_tpg_tfo->tpg_get_wwn(tpg), "+t+",
			tpg->se_tpg_tfo->tpg_get_tag(tpg));
	rcu_पढ़ो_unlock();
	वापस ret;
पूर्ण

अटल sमाप_प्रकार target_stat_tgt_port_in_cmds_show(काष्ठा config_item *item,
		अक्षर *page)
अणु
	काष्ठा se_lun *lun = to_stat_tgt_port(item);
	काष्ठा se_device *dev;
	sमाप_प्रकार ret = -ENODEV;

	rcu_पढ़ो_lock();
	dev = rcu_dereference(lun->lun_se_dev);
	अगर (dev)
		ret = snम_लिखो(page, PAGE_SIZE, "%lu\n",
			       atomic_दीर्घ_पढ़ो(&lun->lun_stats.cmd_pdus));
	rcu_पढ़ो_unlock();
	वापस ret;
पूर्ण

अटल sमाप_प्रकार target_stat_tgt_port_ग_लिखो_mbytes_show(काष्ठा config_item *item,
		अक्षर *page)
अणु
	काष्ठा se_lun *lun = to_stat_tgt_port(item);
	काष्ठा se_device *dev;
	sमाप_प्रकार ret = -ENODEV;

	rcu_पढ़ो_lock();
	dev = rcu_dereference(lun->lun_se_dev);
	अगर (dev)
		ret = snम_लिखो(page, PAGE_SIZE, "%u\n",
			(u32)(atomic_दीर्घ_पढ़ो(&lun->lun_stats.rx_data_octets) >> 20));
	rcu_पढ़ो_unlock();
	वापस ret;
पूर्ण

अटल sमाप_प्रकार target_stat_tgt_port_पढ़ो_mbytes_show(काष्ठा config_item *item,
		अक्षर *page)
अणु
	काष्ठा se_lun *lun = to_stat_tgt_port(item);
	काष्ठा se_device *dev;
	sमाप_प्रकार ret = -ENODEV;

	rcu_पढ़ो_lock();
	dev = rcu_dereference(lun->lun_se_dev);
	अगर (dev)
		ret = snम_लिखो(page, PAGE_SIZE, "%u\n",
				(u32)(atomic_दीर्घ_पढ़ो(&lun->lun_stats.tx_data_octets) >> 20));
	rcu_पढ़ो_unlock();
	वापस ret;
पूर्ण

अटल sमाप_प्रकार target_stat_tgt_port_hs_in_cmds_show(काष्ठा config_item *item,
		अक्षर *page)
अणु
	काष्ठा se_lun *lun = to_stat_tgt_port(item);
	काष्ठा se_device *dev;
	sमाप_प्रकार ret = -ENODEV;

	rcu_पढ़ो_lock();
	dev = rcu_dereference(lun->lun_se_dev);
	अगर (dev) अणु
		/* FIXME: scsiTgtPortHsInCommands */
		ret = snम_लिखो(page, PAGE_SIZE, "%u\n", 0);
	पूर्ण
	rcu_पढ़ो_unlock();
	वापस ret;
पूर्ण

CONFIGFS_ATTR_RO(target_stat_tgt_port_, inst);
CONFIGFS_ATTR_RO(target_stat_tgt_port_, dev);
CONFIGFS_ATTR_RO(target_stat_tgt_port_, indx);
CONFIGFS_ATTR_RO(target_stat_tgt_port_, name);
CONFIGFS_ATTR_RO(target_stat_tgt_port_, port_index);
CONFIGFS_ATTR_RO(target_stat_tgt_port_, in_cmds);
CONFIGFS_ATTR_RO(target_stat_tgt_port_, ग_लिखो_mbytes);
CONFIGFS_ATTR_RO(target_stat_tgt_port_, पढ़ो_mbytes);
CONFIGFS_ATTR_RO(target_stat_tgt_port_, hs_in_cmds);

अटल काष्ठा configfs_attribute *target_stat_scsi_tgt_port_attrs[] = अणु
	&target_stat_tgt_port_attr_inst,
	&target_stat_tgt_port_attr_dev,
	&target_stat_tgt_port_attr_indx,
	&target_stat_tgt_port_attr_name,
	&target_stat_tgt_port_attr_port_index,
	&target_stat_tgt_port_attr_in_cmds,
	&target_stat_tgt_port_attr_ग_लिखो_mbytes,
	&target_stat_tgt_port_attr_पढ़ो_mbytes,
	&target_stat_tgt_port_attr_hs_in_cmds,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा config_item_type target_stat_scsi_tgt_port_cit = अणु
	.ct_attrs		= target_stat_scsi_tgt_port_attrs,
	.ct_owner		= THIS_MODULE,
पूर्ण;

/*
 * SCSI Transport Table
 */
अटल काष्ठा se_lun *to_transport_stat(काष्ठा config_item *item)
अणु
	काष्ठा se_port_stat_grps *pgrps = container_of(to_config_group(item),
			काष्ठा se_port_stat_grps, scsi_transport_group);
	वापस container_of(pgrps, काष्ठा se_lun, port_stat_grps);
पूर्ण

अटल sमाप_प्रकार target_stat_transport_inst_show(काष्ठा config_item *item,
		अक्षर *page)
अणु
	काष्ठा se_lun *lun = to_transport_stat(item);
	काष्ठा se_device *dev;
	sमाप_प्रकार ret = -ENODEV;

	rcu_पढ़ो_lock();
	dev = rcu_dereference(lun->lun_se_dev);
	अगर (dev)
		ret = snम_लिखो(page, PAGE_SIZE, "%u\n", dev->hba_index);
	rcu_पढ़ो_unlock();
	वापस ret;
पूर्ण

अटल sमाप_प्रकार target_stat_transport_device_show(काष्ठा config_item *item,
		अक्षर *page)
अणु
	काष्ठा se_lun *lun = to_transport_stat(item);
	काष्ठा se_device *dev;
	काष्ठा se_portal_group *tpg = lun->lun_tpg;
	sमाप_प्रकार ret = -ENODEV;

	rcu_पढ़ो_lock();
	dev = rcu_dereference(lun->lun_se_dev);
	अगर (dev) अणु
		/* scsiTransportType */
		ret = snम_लिखो(page, PAGE_SIZE, "scsiTransport%s\n",
			       tpg->se_tpg_tfo->fabric_name);
	पूर्ण
	rcu_पढ़ो_unlock();
	वापस ret;
पूर्ण

अटल sमाप_प्रकार target_stat_transport_indx_show(काष्ठा config_item *item,
		अक्षर *page)
अणु
	काष्ठा se_lun *lun = to_transport_stat(item);
	काष्ठा se_device *dev;
	काष्ठा se_portal_group *tpg = lun->lun_tpg;
	sमाप_प्रकार ret = -ENODEV;

	rcu_पढ़ो_lock();
	dev = rcu_dereference(lun->lun_se_dev);
	अगर (dev)
		ret = snम_लिखो(page, PAGE_SIZE, "%u\n",
			       tpg->se_tpg_tfo->tpg_get_inst_index(tpg));
	rcu_पढ़ो_unlock();
	वापस ret;
पूर्ण

अटल sमाप_प्रकार target_stat_transport_dev_name_show(काष्ठा config_item *item,
		अक्षर *page)
अणु
	काष्ठा se_lun *lun = to_transport_stat(item);
	काष्ठा se_device *dev;
	काष्ठा se_portal_group *tpg = lun->lun_tpg;
	काष्ठा t10_wwn *wwn;
	sमाप_प्रकार ret = -ENODEV;

	rcu_पढ़ो_lock();
	dev = rcu_dereference(lun->lun_se_dev);
	अगर (dev) अणु
		wwn = &dev->t10_wwn;
		/* scsiTransportDevName */
		ret = snम_लिखो(page, PAGE_SIZE, "%s+%s\n",
				tpg->se_tpg_tfo->tpg_get_wwn(tpg),
				(म_माप(wwn->unit_serial)) ? wwn->unit_serial :
				wwn->venकरोr);
	पूर्ण
	rcu_पढ़ो_unlock();
	वापस ret;
पूर्ण

अटल sमाप_प्रकार target_stat_transport_proto_id_show(काष्ठा config_item *item,
		अक्षर *page)
अणु
	काष्ठा se_lun *lun = to_transport_stat(item);
	काष्ठा se_device *dev;
	काष्ठा se_portal_group *tpg = lun->lun_tpg;
	sमाप_प्रकार ret = -ENODEV;

	rcu_पढ़ो_lock();
	dev = rcu_dereference(lun->lun_se_dev);
	अगर (dev)
		ret = snम_लिखो(page, PAGE_SIZE, "%u\n", tpg->proto_id);
	rcu_पढ़ो_unlock();
	वापस ret;
पूर्ण

CONFIGFS_ATTR_RO(target_stat_transport_, inst);
CONFIGFS_ATTR_RO(target_stat_transport_, device);
CONFIGFS_ATTR_RO(target_stat_transport_, indx);
CONFIGFS_ATTR_RO(target_stat_transport_, dev_name);
CONFIGFS_ATTR_RO(target_stat_transport_, proto_id);

अटल काष्ठा configfs_attribute *target_stat_scsi_transport_attrs[] = अणु
	&target_stat_transport_attr_inst,
	&target_stat_transport_attr_device,
	&target_stat_transport_attr_indx,
	&target_stat_transport_attr_dev_name,
	&target_stat_transport_attr_proto_id,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा config_item_type target_stat_scsi_transport_cit = अणु
	.ct_attrs		= target_stat_scsi_transport_attrs,
	.ct_owner		= THIS_MODULE,
पूर्ण;

/*
 * Called from target_core_fabric_configfs.c:target_fabric_make_lun() to setup
 * the target port statistics groups + configfs CITs located in target_core_stat.c
 */
व्योम target_stat_setup_port_शेष_groups(काष्ठा se_lun *lun)
अणु
	config_group_init_type_name(&lun->port_stat_grps.scsi_port_group,
			"scsi_port", &target_stat_scsi_port_cit);
	configfs_add_शेष_group(&lun->port_stat_grps.scsi_port_group,
			&lun->port_stat_grps.stat_group);

	config_group_init_type_name(&lun->port_stat_grps.scsi_tgt_port_group,
			"scsi_tgt_port", &target_stat_scsi_tgt_port_cit);
	configfs_add_शेष_group(&lun->port_stat_grps.scsi_tgt_port_group,
			&lun->port_stat_grps.stat_group);

	config_group_init_type_name(&lun->port_stat_grps.scsi_transport_group,
			"scsi_transport", &target_stat_scsi_transport_cit);
	configfs_add_शेष_group(&lun->port_stat_grps.scsi_transport_group,
			&lun->port_stat_grps.stat_group);
पूर्ण

/*
 * SCSI Authorized Initiator Table
 */

अटल काष्ठा se_lun_acl *auth_to_lacl(काष्ठा config_item *item)
अणु
	काष्ठा se_ml_stat_grps *lgrps = container_of(to_config_group(item),
			काष्ठा se_ml_stat_grps, scsi_auth_पूर्णांकr_group);
	वापस container_of(lgrps, काष्ठा se_lun_acl, ml_stat_grps);
पूर्ण

अटल sमाप_प्रकार target_stat_auth_inst_show(काष्ठा config_item *item,
		अक्षर *page)
अणु
	काष्ठा se_lun_acl *lacl = auth_to_lacl(item);
	काष्ठा se_node_acl *nacl = lacl->se_lun_nacl;
	काष्ठा se_dev_entry *deve;
	काष्ठा se_portal_group *tpg;
	sमाप_प्रकार ret;

	rcu_पढ़ो_lock();
	deve = target_nacl_find_deve(nacl, lacl->mapped_lun);
	अगर (!deve) अणु
		rcu_पढ़ो_unlock();
		वापस -ENODEV;
	पूर्ण
	tpg = nacl->se_tpg;
	/* scsiInstIndex */
	ret = snम_लिखो(page, PAGE_SIZE, "%u\n",
			tpg->se_tpg_tfo->tpg_get_inst_index(tpg));
	rcu_पढ़ो_unlock();
	वापस ret;
पूर्ण

अटल sमाप_प्रकार target_stat_auth_dev_show(काष्ठा config_item *item,
		अक्षर *page)
अणु
	काष्ठा se_lun_acl *lacl = auth_to_lacl(item);
	काष्ठा se_node_acl *nacl = lacl->se_lun_nacl;
	काष्ठा se_dev_entry *deve;
	काष्ठा se_lun *lun;
	sमाप_प्रकार ret;

	rcu_पढ़ो_lock();
	deve = target_nacl_find_deve(nacl, lacl->mapped_lun);
	अगर (!deve) अणु
		rcu_पढ़ो_unlock();
		वापस -ENODEV;
	पूर्ण
	lun = rcu_dereference(deve->se_lun);
	/* scsiDeviceIndex */
	ret = snम_लिखो(page, PAGE_SIZE, "%u\n", lun->lun_index);
	rcu_पढ़ो_unlock();
	वापस ret;
पूर्ण

अटल sमाप_प्रकार target_stat_auth_port_show(काष्ठा config_item *item,
		अक्षर *page)
अणु
	काष्ठा se_lun_acl *lacl = auth_to_lacl(item);
	काष्ठा se_node_acl *nacl = lacl->se_lun_nacl;
	काष्ठा se_dev_entry *deve;
	काष्ठा se_portal_group *tpg;
	sमाप_प्रकार ret;

	rcu_पढ़ो_lock();
	deve = target_nacl_find_deve(nacl, lacl->mapped_lun);
	अगर (!deve) अणु
		rcu_पढ़ो_unlock();
		वापस -ENODEV;
	पूर्ण
	tpg = nacl->se_tpg;
	/* scsiAuthIntrTgtPortIndex */
	ret = snम_लिखो(page, PAGE_SIZE, "%u\n", tpg->se_tpg_tfo->tpg_get_tag(tpg));
	rcu_पढ़ो_unlock();
	वापस ret;
पूर्ण

अटल sमाप_प्रकार target_stat_auth_indx_show(काष्ठा config_item *item,
		अक्षर *page)
अणु
	काष्ठा se_lun_acl *lacl = auth_to_lacl(item);
	काष्ठा se_node_acl *nacl = lacl->se_lun_nacl;
	काष्ठा se_dev_entry *deve;
	sमाप_प्रकार ret;

	rcu_पढ़ो_lock();
	deve = target_nacl_find_deve(nacl, lacl->mapped_lun);
	अगर (!deve) अणु
		rcu_पढ़ो_unlock();
		वापस -ENODEV;
	पूर्ण
	/* scsiAuthIntrIndex */
	ret = snम_लिखो(page, PAGE_SIZE, "%u\n", nacl->acl_index);
	rcu_पढ़ो_unlock();
	वापस ret;
पूर्ण

अटल sमाप_प्रकार target_stat_auth_dev_or_port_show(काष्ठा config_item *item,
		अक्षर *page)
अणु
	काष्ठा se_lun_acl *lacl = auth_to_lacl(item);
	काष्ठा se_node_acl *nacl = lacl->se_lun_nacl;
	काष्ठा se_dev_entry *deve;
	sमाप_प्रकार ret;

	rcu_पढ़ो_lock();
	deve = target_nacl_find_deve(nacl, lacl->mapped_lun);
	अगर (!deve) अणु
		rcu_पढ़ो_unlock();
		वापस -ENODEV;
	पूर्ण
	/* scsiAuthIntrDevOrPort */
	ret = snम_लिखो(page, PAGE_SIZE, "%u\n", 1);
	rcu_पढ़ो_unlock();
	वापस ret;
पूर्ण

अटल sमाप_प्रकार target_stat_auth_पूर्णांकr_name_show(काष्ठा config_item *item,
		अक्षर *page)
अणु
	काष्ठा se_lun_acl *lacl = auth_to_lacl(item);
	काष्ठा se_node_acl *nacl = lacl->se_lun_nacl;
	काष्ठा se_dev_entry *deve;
	sमाप_प्रकार ret;

	rcu_पढ़ो_lock();
	deve = target_nacl_find_deve(nacl, lacl->mapped_lun);
	अगर (!deve) अणु
		rcu_पढ़ो_unlock();
		वापस -ENODEV;
	पूर्ण
	/* scsiAuthIntrName */
	ret = snम_लिखो(page, PAGE_SIZE, "%s\n", nacl->initiatorname);
	rcu_पढ़ो_unlock();
	वापस ret;
पूर्ण

अटल sमाप_प्रकार target_stat_auth_map_indx_show(काष्ठा config_item *item,
		अक्षर *page)
अणु
	काष्ठा se_lun_acl *lacl = auth_to_lacl(item);
	काष्ठा se_node_acl *nacl = lacl->se_lun_nacl;
	काष्ठा se_dev_entry *deve;
	sमाप_प्रकार ret;

	rcu_पढ़ो_lock();
	deve = target_nacl_find_deve(nacl, lacl->mapped_lun);
	अगर (!deve) अणु
		rcu_पढ़ो_unlock();
		वापस -ENODEV;
	पूर्ण
	/* FIXME: scsiAuthIntrLunMapIndex */
	ret = snम_लिखो(page, PAGE_SIZE, "%u\n", 0);
	rcu_पढ़ो_unlock();
	वापस ret;
पूर्ण

अटल sमाप_प्रकार target_stat_auth_att_count_show(काष्ठा config_item *item,
		अक्षर *page)
अणु
	काष्ठा se_lun_acl *lacl = auth_to_lacl(item);
	काष्ठा se_node_acl *nacl = lacl->se_lun_nacl;
	काष्ठा se_dev_entry *deve;
	sमाप_प्रकार ret;

	rcu_पढ़ो_lock();
	deve = target_nacl_find_deve(nacl, lacl->mapped_lun);
	अगर (!deve) अणु
		rcu_पढ़ो_unlock();
		वापस -ENODEV;
	पूर्ण
	/* scsiAuthIntrAttachedTimes */
	ret = snम_लिखो(page, PAGE_SIZE, "%u\n", deve->attach_count);
	rcu_पढ़ो_unlock();
	वापस ret;
पूर्ण

अटल sमाप_प्रकार target_stat_auth_num_cmds_show(काष्ठा config_item *item,
		अक्षर *page)
अणु
	काष्ठा se_lun_acl *lacl = auth_to_lacl(item);
	काष्ठा se_node_acl *nacl = lacl->se_lun_nacl;
	काष्ठा se_dev_entry *deve;
	sमाप_प्रकार ret;

	rcu_पढ़ो_lock();
	deve = target_nacl_find_deve(nacl, lacl->mapped_lun);
	अगर (!deve) अणु
		rcu_पढ़ो_unlock();
		वापस -ENODEV;
	पूर्ण
	/* scsiAuthIntrOutCommands */
	ret = snम_लिखो(page, PAGE_SIZE, "%lu\n",
		       atomic_दीर्घ_पढ़ो(&deve->total_cmds));
	rcu_पढ़ो_unlock();
	वापस ret;
पूर्ण

अटल sमाप_प्रकार target_stat_auth_पढ़ो_mbytes_show(काष्ठा config_item *item,
		अक्षर *page)
अणु
	काष्ठा se_lun_acl *lacl = auth_to_lacl(item);
	काष्ठा se_node_acl *nacl = lacl->se_lun_nacl;
	काष्ठा se_dev_entry *deve;
	sमाप_प्रकार ret;

	rcu_पढ़ो_lock();
	deve = target_nacl_find_deve(nacl, lacl->mapped_lun);
	अगर (!deve) अणु
		rcu_पढ़ो_unlock();
		वापस -ENODEV;
	पूर्ण
	/* scsiAuthIntrReadMegaBytes */
	ret = snम_लिखो(page, PAGE_SIZE, "%u\n",
		      (u32)(atomic_दीर्घ_पढ़ो(&deve->पढ़ो_bytes) >> 20));
	rcu_पढ़ो_unlock();
	वापस ret;
पूर्ण

अटल sमाप_प्रकार target_stat_auth_ग_लिखो_mbytes_show(काष्ठा config_item *item,
		अक्षर *page)
अणु
	काष्ठा se_lun_acl *lacl = auth_to_lacl(item);
	काष्ठा se_node_acl *nacl = lacl->se_lun_nacl;
	काष्ठा se_dev_entry *deve;
	sमाप_प्रकार ret;

	rcu_पढ़ो_lock();
	deve = target_nacl_find_deve(nacl, lacl->mapped_lun);
	अगर (!deve) अणु
		rcu_पढ़ो_unlock();
		वापस -ENODEV;
	पूर्ण
	/* scsiAuthIntrWrittenMegaBytes */
	ret = snम_लिखो(page, PAGE_SIZE, "%u\n",
		      (u32)(atomic_दीर्घ_पढ़ो(&deve->ग_लिखो_bytes) >> 20));
	rcu_पढ़ो_unlock();
	वापस ret;
पूर्ण

अटल sमाप_प्रकार target_stat_auth_hs_num_cmds_show(काष्ठा config_item *item,
		अक्षर *page)
अणु
	काष्ठा se_lun_acl *lacl = auth_to_lacl(item);
	काष्ठा se_node_acl *nacl = lacl->se_lun_nacl;
	काष्ठा se_dev_entry *deve;
	sमाप_प्रकार ret;

	rcu_पढ़ो_lock();
	deve = target_nacl_find_deve(nacl, lacl->mapped_lun);
	अगर (!deve) अणु
		rcu_पढ़ो_unlock();
		वापस -ENODEV;
	पूर्ण
	/* FIXME: scsiAuthIntrHSOutCommands */
	ret = snम_लिखो(page, PAGE_SIZE, "%u\n", 0);
	rcu_पढ़ो_unlock();
	वापस ret;
पूर्ण

अटल sमाप_प्रकार target_stat_auth_creation_समय_show(काष्ठा config_item *item,
		अक्षर *page)
अणु
	काष्ठा se_lun_acl *lacl = auth_to_lacl(item);
	काष्ठा se_node_acl *nacl = lacl->se_lun_nacl;
	काष्ठा se_dev_entry *deve;
	sमाप_प्रकार ret;

	rcu_पढ़ो_lock();
	deve = target_nacl_find_deve(nacl, lacl->mapped_lun);
	अगर (!deve) अणु
		rcu_पढ़ो_unlock();
		वापस -ENODEV;
	पूर्ण
	/* scsiAuthIntrLastCreation */
	ret = snम_लिखो(page, PAGE_SIZE, "%u\n", (u32)(((u32)deve->creation_समय -
				INITIAL_JIFFIES) * 100 / HZ));
	rcu_पढ़ो_unlock();
	वापस ret;
पूर्ण

अटल sमाप_प्रकार target_stat_auth_row_status_show(काष्ठा config_item *item,
		अक्षर *page)
अणु
	काष्ठा se_lun_acl *lacl = auth_to_lacl(item);
	काष्ठा se_node_acl *nacl = lacl->se_lun_nacl;
	काष्ठा se_dev_entry *deve;
	sमाप_प्रकार ret;

	rcu_पढ़ो_lock();
	deve = target_nacl_find_deve(nacl, lacl->mapped_lun);
	अगर (!deve) अणु
		rcu_पढ़ो_unlock();
		वापस -ENODEV;
	पूर्ण
	/* FIXME: scsiAuthIntrRowStatus */
	ret = snम_लिखो(page, PAGE_SIZE, "Ready\n");
	rcu_पढ़ो_unlock();
	वापस ret;
पूर्ण

CONFIGFS_ATTR_RO(target_stat_auth_, inst);
CONFIGFS_ATTR_RO(target_stat_auth_, dev);
CONFIGFS_ATTR_RO(target_stat_auth_, port);
CONFIGFS_ATTR_RO(target_stat_auth_, indx);
CONFIGFS_ATTR_RO(target_stat_auth_, dev_or_port);
CONFIGFS_ATTR_RO(target_stat_auth_, पूर्णांकr_name);
CONFIGFS_ATTR_RO(target_stat_auth_, map_indx);
CONFIGFS_ATTR_RO(target_stat_auth_, att_count);
CONFIGFS_ATTR_RO(target_stat_auth_, num_cmds);
CONFIGFS_ATTR_RO(target_stat_auth_, पढ़ो_mbytes);
CONFIGFS_ATTR_RO(target_stat_auth_, ग_लिखो_mbytes);
CONFIGFS_ATTR_RO(target_stat_auth_, hs_num_cmds);
CONFIGFS_ATTR_RO(target_stat_auth_, creation_समय);
CONFIGFS_ATTR_RO(target_stat_auth_, row_status);

अटल काष्ठा configfs_attribute *target_stat_scsi_auth_पूर्णांकr_attrs[] = अणु
	&target_stat_auth_attr_inst,
	&target_stat_auth_attr_dev,
	&target_stat_auth_attr_port,
	&target_stat_auth_attr_indx,
	&target_stat_auth_attr_dev_or_port,
	&target_stat_auth_attr_पूर्णांकr_name,
	&target_stat_auth_attr_map_indx,
	&target_stat_auth_attr_att_count,
	&target_stat_auth_attr_num_cmds,
	&target_stat_auth_attr_पढ़ो_mbytes,
	&target_stat_auth_attr_ग_लिखो_mbytes,
	&target_stat_auth_attr_hs_num_cmds,
	&target_stat_auth_attr_creation_समय,
	&target_stat_auth_attr_row_status,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा config_item_type target_stat_scsi_auth_पूर्णांकr_cit = अणु
	.ct_attrs		= target_stat_scsi_auth_पूर्णांकr_attrs,
	.ct_owner		= THIS_MODULE,
पूर्ण;

/*
 * SCSI Attached Initiator Port Table
 */

अटल काष्ठा se_lun_acl *iport_to_lacl(काष्ठा config_item *item)
अणु
	काष्ठा se_ml_stat_grps *lgrps = container_of(to_config_group(item),
			काष्ठा se_ml_stat_grps, scsi_att_पूर्णांकr_port_group);
	वापस container_of(lgrps, काष्ठा se_lun_acl, ml_stat_grps);
पूर्ण

अटल sमाप_प्रकार target_stat_iport_inst_show(काष्ठा config_item *item,
		अक्षर *page)
अणु
	काष्ठा se_lun_acl *lacl = iport_to_lacl(item);
	काष्ठा se_node_acl *nacl = lacl->se_lun_nacl;
	काष्ठा se_dev_entry *deve;
	काष्ठा se_portal_group *tpg;
	sमाप_प्रकार ret;

	rcu_पढ़ो_lock();
	deve = target_nacl_find_deve(nacl, lacl->mapped_lun);
	अगर (!deve) अणु
		rcu_पढ़ो_unlock();
		वापस -ENODEV;
	पूर्ण
	tpg = nacl->se_tpg;
	/* scsiInstIndex */
	ret = snम_लिखो(page, PAGE_SIZE, "%u\n",
			tpg->se_tpg_tfo->tpg_get_inst_index(tpg));
	rcu_पढ़ो_unlock();
	वापस ret;
पूर्ण

अटल sमाप_प्रकार target_stat_iport_dev_show(काष्ठा config_item *item,
		अक्षर *page)
अणु
	काष्ठा se_lun_acl *lacl = iport_to_lacl(item);
	काष्ठा se_node_acl *nacl = lacl->se_lun_nacl;
	काष्ठा se_dev_entry *deve;
	काष्ठा se_lun *lun;
	sमाप_प्रकार ret;

	rcu_पढ़ो_lock();
	deve = target_nacl_find_deve(nacl, lacl->mapped_lun);
	अगर (!deve) अणु
		rcu_पढ़ो_unlock();
		वापस -ENODEV;
	पूर्ण
	lun = rcu_dereference(deve->se_lun);
	/* scsiDeviceIndex */
	ret = snम_लिखो(page, PAGE_SIZE, "%u\n", lun->lun_index);
	rcu_पढ़ो_unlock();
	वापस ret;
पूर्ण

अटल sमाप_प्रकार target_stat_iport_port_show(काष्ठा config_item *item,
		अक्षर *page)
अणु
	काष्ठा se_lun_acl *lacl = iport_to_lacl(item);
	काष्ठा se_node_acl *nacl = lacl->se_lun_nacl;
	काष्ठा se_dev_entry *deve;
	काष्ठा se_portal_group *tpg;
	sमाप_प्रकार ret;

	rcu_पढ़ो_lock();
	deve = target_nacl_find_deve(nacl, lacl->mapped_lun);
	अगर (!deve) अणु
		rcu_पढ़ो_unlock();
		वापस -ENODEV;
	पूर्ण
	tpg = nacl->se_tpg;
	/* scsiPortIndex */
	ret = snम_लिखो(page, PAGE_SIZE, "%u\n", tpg->se_tpg_tfo->tpg_get_tag(tpg));
	rcu_पढ़ो_unlock();
	वापस ret;
पूर्ण

अटल sमाप_प्रकार target_stat_iport_indx_show(काष्ठा config_item *item,
		अक्षर *page)
अणु
	काष्ठा se_lun_acl *lacl = iport_to_lacl(item);
	काष्ठा se_node_acl *nacl = lacl->se_lun_nacl;
	काष्ठा se_session *se_sess;
	काष्ठा se_portal_group *tpg;
	sमाप_प्रकार ret;

	spin_lock_irq(&nacl->nacl_sess_lock);
	se_sess = nacl->nacl_sess;
	अगर (!se_sess) अणु
		spin_unlock_irq(&nacl->nacl_sess_lock);
		वापस -ENODEV;
	पूर्ण

	tpg = nacl->se_tpg;
	/* scsiAttIntrPortIndex */
	ret = snम_लिखो(page, PAGE_SIZE, "%u\n",
			tpg->se_tpg_tfo->sess_get_index(se_sess));
	spin_unlock_irq(&nacl->nacl_sess_lock);
	वापस ret;
पूर्ण

अटल sमाप_प्रकार target_stat_iport_port_auth_indx_show(काष्ठा config_item *item,
		अक्षर *page)
अणु
	काष्ठा se_lun_acl *lacl = iport_to_lacl(item);
	काष्ठा se_node_acl *nacl = lacl->se_lun_nacl;
	काष्ठा se_dev_entry *deve;
	sमाप_प्रकार ret;

	rcu_पढ़ो_lock();
	deve = target_nacl_find_deve(nacl, lacl->mapped_lun);
	अगर (!deve) अणु
		rcu_पढ़ो_unlock();
		वापस -ENODEV;
	पूर्ण
	/* scsiAttIntrPortAuthIntrIdx */
	ret = snम_लिखो(page, PAGE_SIZE, "%u\n", nacl->acl_index);
	rcu_पढ़ो_unlock();
	वापस ret;
पूर्ण

अटल sमाप_प्रकार target_stat_iport_port_ident_show(काष्ठा config_item *item,
		अक्षर *page)
अणु
	काष्ठा se_lun_acl *lacl = iport_to_lacl(item);
	काष्ठा se_node_acl *nacl = lacl->se_lun_nacl;
	काष्ठा se_session *se_sess;
	काष्ठा se_portal_group *tpg;
	sमाप_प्रकार ret;
	अचिन्हित अक्षर buf[64];

	spin_lock_irq(&nacl->nacl_sess_lock);
	se_sess = nacl->nacl_sess;
	अगर (!se_sess) अणु
		spin_unlock_irq(&nacl->nacl_sess_lock);
		वापस -ENODEV;
	पूर्ण

	tpg = nacl->se_tpg;
	/* scsiAttIntrPortName+scsiAttIntrPortIdentअगरier */
	स_रखो(buf, 0, 64);
	अगर (tpg->se_tpg_tfo->sess_get_initiator_sid != शून्य)
		tpg->se_tpg_tfo->sess_get_initiator_sid(se_sess, buf, 64);

	ret = snम_लिखो(page, PAGE_SIZE, "%s+i+%s\n", nacl->initiatorname, buf);
	spin_unlock_irq(&nacl->nacl_sess_lock);
	वापस ret;
पूर्ण

CONFIGFS_ATTR_RO(target_stat_iport_, inst);
CONFIGFS_ATTR_RO(target_stat_iport_, dev);
CONFIGFS_ATTR_RO(target_stat_iport_, port);
CONFIGFS_ATTR_RO(target_stat_iport_, indx);
CONFIGFS_ATTR_RO(target_stat_iport_, port_auth_indx);
CONFIGFS_ATTR_RO(target_stat_iport_, port_ident);

अटल काष्ठा configfs_attribute *target_stat_scsi_ath_पूर्णांकr_port_attrs[] = अणु
	&target_stat_iport_attr_inst,
	&target_stat_iport_attr_dev,
	&target_stat_iport_attr_port,
	&target_stat_iport_attr_indx,
	&target_stat_iport_attr_port_auth_indx,
	&target_stat_iport_attr_port_ident,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा config_item_type target_stat_scsi_att_पूर्णांकr_port_cit = अणु
	.ct_attrs		= target_stat_scsi_ath_पूर्णांकr_port_attrs,
	.ct_owner		= THIS_MODULE,
पूर्ण;

/*
 * Called from target_core_fabric_configfs.c:target_fabric_make_mappedlun() to setup
 * the target MappedLUN statistics groups + configfs CITs located in target_core_stat.c
 */
व्योम target_stat_setup_mappedlun_शेष_groups(काष्ठा se_lun_acl *lacl)
अणु
	config_group_init_type_name(&lacl->ml_stat_grps.scsi_auth_पूर्णांकr_group,
			"scsi_auth_intr", &target_stat_scsi_auth_पूर्णांकr_cit);
	configfs_add_शेष_group(&lacl->ml_stat_grps.scsi_auth_पूर्णांकr_group,
			&lacl->ml_stat_grps.stat_group);

	config_group_init_type_name(&lacl->ml_stat_grps.scsi_att_पूर्णांकr_port_group,
			"scsi_att_intr_port", &target_stat_scsi_att_पूर्णांकr_port_cit);
	configfs_add_शेष_group(&lacl->ml_stat_grps.scsi_att_पूर्णांकr_port_group,
			&lacl->ml_stat_grps.stat_group);
पूर्ण
