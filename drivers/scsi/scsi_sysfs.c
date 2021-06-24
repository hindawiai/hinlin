<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * scsi_sysfs.c
 *
 * SCSI sysfs पूर्णांकerface routines.
 *
 * Created to pull SCSI mid layer sysfs routines पूर्णांकo one file.
 */

#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/init.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/device.h>
#समावेश <linux/pm_runसमय.स>

#समावेश <scsi/scsi.h>
#समावेश <scsi/scsi_device.h>
#समावेश <scsi/scsi_host.h>
#समावेश <scsi/scsi_tcq.h>
#समावेश <scsi/scsi_dh.h>
#समावेश <scsi/scsi_transport.h>
#समावेश <scsi/scsi_driver.h>
#समावेश <scsi/scsi_devinfo.h>

#समावेश "scsi_priv.h"
#समावेश "scsi_logging.h"

अटल काष्ठा device_type scsi_dev_type;

अटल स्थिर काष्ठा अणु
	क्रमागत scsi_device_state	value;
	अक्षर			*name;
पूर्ण sdev_states[] = अणु
	अणु SDEV_CREATED, "created" पूर्ण,
	अणु SDEV_RUNNING, "running" पूर्ण,
	अणु SDEV_CANCEL, "cancel" पूर्ण,
	अणु SDEV_DEL, "deleted" पूर्ण,
	अणु SDEV_QUIESCE, "quiesce" पूर्ण,
	अणु SDEV_OFFLINE,	"offline" पूर्ण,
	अणु SDEV_TRANSPORT_OFFLINE, "transport-offline" पूर्ण,
	अणु SDEV_BLOCK,	"blocked" पूर्ण,
	अणु SDEV_CREATED_BLOCK, "created-blocked" पूर्ण,
पूर्ण;

स्थिर अक्षर *scsi_device_state_name(क्रमागत scsi_device_state state)
अणु
	पूर्णांक i;
	अक्षर *name = शून्य;

	क्रम (i = 0; i < ARRAY_SIZE(sdev_states); i++) अणु
		अगर (sdev_states[i].value == state) अणु
			name = sdev_states[i].name;
			अवरोध;
		पूर्ण
	पूर्ण
	वापस name;
पूर्ण

अटल स्थिर काष्ठा अणु
	क्रमागत scsi_host_state	value;
	अक्षर			*name;
पूर्ण shost_states[] = अणु
	अणु SHOST_CREATED, "created" पूर्ण,
	अणु SHOST_RUNNING, "running" पूर्ण,
	अणु SHOST_CANCEL, "cancel" पूर्ण,
	अणु SHOST_DEL, "deleted" पूर्ण,
	अणु SHOST_RECOVERY, "recovery" पूर्ण,
	अणु SHOST_CANCEL_RECOVERY, "cancel/recovery" पूर्ण,
	अणु SHOST_DEL_RECOVERY, "deleted/recovery", पूर्ण,
पूर्ण;
स्थिर अक्षर *scsi_host_state_name(क्रमागत scsi_host_state state)
अणु
	पूर्णांक i;
	अक्षर *name = शून्य;

	क्रम (i = 0; i < ARRAY_SIZE(shost_states); i++) अणु
		अगर (shost_states[i].value == state) अणु
			name = shost_states[i].name;
			अवरोध;
		पूर्ण
	पूर्ण
	वापस name;
पूर्ण

#अगर_घोषित CONFIG_SCSI_DH
अटल स्थिर काष्ठा अणु
	अचिन्हित अक्षर	value;
	अक्षर		*name;
पूर्ण sdev_access_states[] = अणु
	अणु SCSI_ACCESS_STATE_OPTIMAL, "active/optimized" पूर्ण,
	अणु SCSI_ACCESS_STATE_ACTIVE, "active/non-optimized" पूर्ण,
	अणु SCSI_ACCESS_STATE_STANDBY, "standby" पूर्ण,
	अणु SCSI_ACCESS_STATE_UNAVAILABLE, "unavailable" पूर्ण,
	अणु SCSI_ACCESS_STATE_LBA, "lba-dependent" पूर्ण,
	अणु SCSI_ACCESS_STATE_OFFLINE, "offline" पूर्ण,
	अणु SCSI_ACCESS_STATE_TRANSITIONING, "transitioning" पूर्ण,
पूर्ण;

अटल स्थिर अक्षर *scsi_access_state_name(अचिन्हित अक्षर state)
अणु
	पूर्णांक i;
	अक्षर *name = शून्य;

	क्रम (i = 0; i < ARRAY_SIZE(sdev_access_states); i++) अणु
		अगर (sdev_access_states[i].value == state) अणु
			name = sdev_access_states[i].name;
			अवरोध;
		पूर्ण
	पूर्ण
	वापस name;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक check_set(अचिन्हित दीर्घ दीर्घ *val, अक्षर *src)
अणु
	अक्षर *last;

	अगर (म_भेद(src, "-") == 0) अणु
		*val = SCAN_WILD_CARD;
	पूर्ण अन्यथा अणु
		/*
		 * Doesn't check क्रम पूर्णांक overflow
		 */
		*val = simple_म_से_अदीर्घl(src, &last, 0);
		अगर (*last != '\0')
			वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक scsi_scan(काष्ठा Scsi_Host *shost, स्थिर अक्षर *str)
अणु
	अक्षर s1[15], s2[15], s3[17], junk;
	अचिन्हित दीर्घ दीर्घ channel, id, lun;
	पूर्णांक res;

	res = माला_पूछो(str, "%10s %10s %16s %c", s1, s2, s3, &junk);
	अगर (res != 3)
		वापस -EINVAL;
	अगर (check_set(&channel, s1))
		वापस -EINVAL;
	अगर (check_set(&id, s2))
		वापस -EINVAL;
	अगर (check_set(&lun, s3))
		वापस -EINVAL;
	अगर (shost->transportt->user_scan)
		res = shost->transportt->user_scan(shost, channel, id, lun);
	अन्यथा
		res = scsi_scan_host_selected(shost, channel, id, lun,
					      SCSI_SCAN_MANUAL);
	वापस res;
पूर्ण

/*
 * shost_show_function: macro to create an attr function that can be used to
 * show a non-bit field.
 */
#घोषणा shost_show_function(name, field, क्रमmat_string)			\
अटल sमाप_प्रकार								\
show_##name (काष्ठा device *dev, काष्ठा device_attribute *attr, 	\
	     अक्षर *buf)							\
अणु									\
	काष्ठा Scsi_Host *shost = class_to_shost(dev);			\
	वापस snम_लिखो (buf, 20, क्रमmat_string, shost->field);		\
पूर्ण

/*
 * shost_rd_attr: macro to create a function and attribute variable क्रम a
 * पढ़ो only field.
 */
#घोषणा shost_rd_attr2(name, field, क्रमmat_string)			\
	shost_show_function(name, field, क्रमmat_string)			\
अटल DEVICE_ATTR(name, S_IRUGO, show_##name, शून्य);

#घोषणा shost_rd_attr(field, क्रमmat_string) \
shost_rd_attr2(field, field, क्रमmat_string)

/*
 * Create the actual show/store functions and data काष्ठाures.
 */

अटल sमाप_प्रकार
store_scan(काष्ठा device *dev, काष्ठा device_attribute *attr,
	   स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा Scsi_Host *shost = class_to_shost(dev);
	पूर्णांक res;

	res = scsi_scan(shost, buf);
	अगर (res == 0)
		res = count;
	वापस res;
पूर्ण;
अटल DEVICE_ATTR(scan, S_IWUSR, शून्य, store_scan);

अटल sमाप_प्रकार
store_shost_state(काष्ठा device *dev, काष्ठा device_attribute *attr,
		  स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	पूर्णांक i;
	काष्ठा Scsi_Host *shost = class_to_shost(dev);
	क्रमागत scsi_host_state state = 0;

	क्रम (i = 0; i < ARRAY_SIZE(shost_states); i++) अणु
		स्थिर पूर्णांक len = म_माप(shost_states[i].name);
		अगर (म_भेदन(shost_states[i].name, buf, len) == 0 &&
		   buf[len] == '\n') अणु
			state = shost_states[i].value;
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (!state)
		वापस -EINVAL;

	अगर (scsi_host_set_state(shost, state))
		वापस -EINVAL;
	वापस count;
पूर्ण

अटल sमाप_प्रकार
show_shost_state(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा Scsi_Host *shost = class_to_shost(dev);
	स्थिर अक्षर *name = scsi_host_state_name(shost->shost_state);

	अगर (!name)
		वापस -EINVAL;

	वापस snम_लिखो(buf, 20, "%s\n", name);
पूर्ण

/* DEVICE_ATTR(state) clashes with dev_attr_state क्रम sdev */
अटल काष्ठा device_attribute dev_attr_hstate =
	__ATTR(state, S_IRUGO | S_IWUSR, show_shost_state, store_shost_state);

अटल sमाप_प्रकार
show_shost_mode(अचिन्हित पूर्णांक mode, अक्षर *buf)
अणु
	sमाप_प्रकार len = 0;

	अगर (mode & MODE_INITIATOR)
		len = प्र_लिखो(buf, "%s", "Initiator");

	अगर (mode & MODE_TARGET)
		len += प्र_लिखो(buf + len, "%s%s", len ? ", " : "", "Target");

	len += प्र_लिखो(buf + len, "\n");

	वापस len;
पूर्ण

अटल sमाप_प्रकार
show_shost_supported_mode(काष्ठा device *dev, काष्ठा device_attribute *attr,
			  अक्षर *buf)
अणु
	काष्ठा Scsi_Host *shost = class_to_shost(dev);
	अचिन्हित पूर्णांक supported_mode = shost->hostt->supported_mode;

	अगर (supported_mode == MODE_UNKNOWN)
		/* by शेष this should be initiator */
		supported_mode = MODE_INITIATOR;

	वापस show_shost_mode(supported_mode, buf);
पूर्ण

अटल DEVICE_ATTR(supported_mode, S_IRUGO | S_IWUSR, show_shost_supported_mode, शून्य);

अटल sमाप_प्रकार
show_shost_active_mode(काष्ठा device *dev,
		       काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा Scsi_Host *shost = class_to_shost(dev);

	अगर (shost->active_mode == MODE_UNKNOWN)
		वापस snम_लिखो(buf, 20, "unknown\n");
	अन्यथा
		वापस show_shost_mode(shost->active_mode, buf);
पूर्ण

अटल DEVICE_ATTR(active_mode, S_IRUGO | S_IWUSR, show_shost_active_mode, शून्य);

अटल पूर्णांक check_reset_type(स्थिर अक्षर *str)
अणु
	अगर (sysfs_streq(str, "adapter"))
		वापस SCSI_ADAPTER_RESET;
	अन्यथा अगर (sysfs_streq(str, "firmware"))
		वापस SCSI_FIRMWARE_RESET;
	अन्यथा
		वापस 0;
पूर्ण

अटल sमाप_प्रकार
store_host_reset(काष्ठा device *dev, काष्ठा device_attribute *attr,
		स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा Scsi_Host *shost = class_to_shost(dev);
	काष्ठा scsi_host_ढाँचा *sht = shost->hostt;
	पूर्णांक ret = -EINVAL;
	पूर्णांक type;

	type = check_reset_type(buf);
	अगर (!type)
		जाओ निकास_store_host_reset;

	अगर (sht->host_reset)
		ret = sht->host_reset(shost, type);
	अन्यथा
		ret = -EOPNOTSUPP;

निकास_store_host_reset:
	अगर (ret == 0)
		ret = count;
	वापस ret;
पूर्ण

अटल DEVICE_ATTR(host_reset, S_IWUSR, शून्य, store_host_reset);

अटल sमाप_प्रकार
show_shost_eh_deadline(काष्ठा device *dev,
		      काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा Scsi_Host *shost = class_to_shost(dev);

	अगर (shost->eh_deadline == -1)
		वापस snम_लिखो(buf, म_माप("off") + 2, "off\n");
	वापस प्र_लिखो(buf, "%u\n", shost->eh_deadline / HZ);
पूर्ण

अटल sमाप_प्रकार
store_shost_eh_deadline(काष्ठा device *dev, काष्ठा device_attribute *attr,
		स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा Scsi_Host *shost = class_to_shost(dev);
	पूर्णांक ret = -EINVAL;
	अचिन्हित दीर्घ deadline, flags;

	अगर (shost->transportt &&
	    (shost->transportt->eh_strategy_handler ||
	     !shost->hostt->eh_host_reset_handler))
		वापस ret;

	अगर (!म_भेदन(buf, "off", म_माप("off")))
		deadline = -1;
	अन्यथा अणु
		ret = kम_से_अदीर्घ(buf, 10, &deadline);
		अगर (ret)
			वापस ret;
		अगर (deadline * HZ > अच_पूर्णांक_उच्च)
			वापस -EINVAL;
	पूर्ण

	spin_lock_irqsave(shost->host_lock, flags);
	अगर (scsi_host_in_recovery(shost))
		ret = -EBUSY;
	अन्यथा अणु
		अगर (deadline == -1)
			shost->eh_deadline = -1;
		अन्यथा
			shost->eh_deadline = deadline * HZ;

		ret = count;
	पूर्ण
	spin_unlock_irqrestore(shost->host_lock, flags);

	वापस ret;
पूर्ण

अटल DEVICE_ATTR(eh_deadline, S_IRUGO | S_IWUSR, show_shost_eh_deadline, store_shost_eh_deadline);

shost_rd_attr(unique_id, "%u\n");
shost_rd_attr(cmd_per_lun, "%hd\n");
shost_rd_attr(can_queue, "%d\n");
shost_rd_attr(sg_tablesize, "%hu\n");
shost_rd_attr(sg_prot_tablesize, "%hu\n");
shost_rd_attr(prot_capabilities, "%u\n");
shost_rd_attr(prot_guard_type, "%hd\n");
shost_rd_attr2(proc_name, hostt->proc_name, "%s\n");

अटल sमाप_प्रकार
show_host_busy(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा Scsi_Host *shost = class_to_shost(dev);
	वापस snम_लिखो(buf, 20, "%d\n", scsi_host_busy(shost));
पूर्ण
अटल DEVICE_ATTR(host_busy, S_IRUGO, show_host_busy, शून्य);

अटल sमाप_प्रकार
show_use_blk_mq(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "1\n");
पूर्ण
अटल DEVICE_ATTR(use_blk_mq, S_IRUGO, show_use_blk_mq, शून्य);

अटल sमाप_प्रकार
show_nr_hw_queues(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा Scsi_Host *shost = class_to_shost(dev);
	काष्ठा blk_mq_tag_set *tag_set = &shost->tag_set;

	वापस snम_लिखो(buf, 20, "%d\n", tag_set->nr_hw_queues);
पूर्ण
अटल DEVICE_ATTR(nr_hw_queues, S_IRUGO, show_nr_hw_queues, शून्य);

अटल काष्ठा attribute *scsi_sysfs_shost_attrs[] = अणु
	&dev_attr_use_blk_mq.attr,
	&dev_attr_unique_id.attr,
	&dev_attr_host_busy.attr,
	&dev_attr_cmd_per_lun.attr,
	&dev_attr_can_queue.attr,
	&dev_attr_sg_tablesize.attr,
	&dev_attr_sg_prot_tablesize.attr,
	&dev_attr_proc_name.attr,
	&dev_attr_scan.attr,
	&dev_attr_hstate.attr,
	&dev_attr_supported_mode.attr,
	&dev_attr_active_mode.attr,
	&dev_attr_prot_capabilities.attr,
	&dev_attr_prot_guard_type.attr,
	&dev_attr_host_reset.attr,
	&dev_attr_eh_deadline.attr,
	&dev_attr_nr_hw_queues.attr,
	शून्य
पूर्ण;

अटल काष्ठा attribute_group scsi_shost_attr_group = अणु
	.attrs =	scsi_sysfs_shost_attrs,
पूर्ण;

स्थिर काष्ठा attribute_group *scsi_sysfs_shost_attr_groups[] = अणु
	&scsi_shost_attr_group,
	शून्य
पूर्ण;

अटल व्योम scsi_device_cls_release(काष्ठा device *class_dev)
अणु
	काष्ठा scsi_device *sdev;

	sdev = class_to_sdev(class_dev);
	put_device(&sdev->sdev_gendev);
पूर्ण

अटल व्योम scsi_device_dev_release_usercontext(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा scsi_device *sdev;
	काष्ठा device *parent;
	काष्ठा list_head *this, *पंचांगp;
	काष्ठा scsi_vpd *vpd_pg80 = शून्य, *vpd_pg83 = शून्य;
	काष्ठा scsi_vpd *vpd_pg0 = शून्य, *vpd_pg89 = शून्य;
	अचिन्हित दीर्घ flags;

	sdev = container_of(work, काष्ठा scsi_device, ew.work);

	scsi_dh_release_device(sdev);

	parent = sdev->sdev_gendev.parent;

	spin_lock_irqsave(sdev->host->host_lock, flags);
	list_del(&sdev->siblings);
	list_del(&sdev->same_target_siblings);
	list_del(&sdev->starved_entry);
	spin_unlock_irqrestore(sdev->host->host_lock, flags);

	cancel_work_sync(&sdev->event_work);

	list_क्रम_each_safe(this, पंचांगp, &sdev->event_list) अणु
		काष्ठा scsi_event *evt;

		evt = list_entry(this, काष्ठा scsi_event, node);
		list_del(&evt->node);
		kमुक्त(evt);
	पूर्ण

	blk_put_queue(sdev->request_queue);
	/* शून्य queue means the device can't be used */
	sdev->request_queue = शून्य;

	sbiपंचांगap_मुक्त(&sdev->budget_map);

	mutex_lock(&sdev->inquiry_mutex);
	vpd_pg0 = rcu_replace_poपूर्णांकer(sdev->vpd_pg0, vpd_pg0,
				       lockdep_is_held(&sdev->inquiry_mutex));
	vpd_pg80 = rcu_replace_poपूर्णांकer(sdev->vpd_pg80, vpd_pg80,
				       lockdep_is_held(&sdev->inquiry_mutex));
	vpd_pg83 = rcu_replace_poपूर्णांकer(sdev->vpd_pg83, vpd_pg83,
				       lockdep_is_held(&sdev->inquiry_mutex));
	vpd_pg89 = rcu_replace_poपूर्णांकer(sdev->vpd_pg89, vpd_pg89,
				       lockdep_is_held(&sdev->inquiry_mutex));
	mutex_unlock(&sdev->inquiry_mutex);

	अगर (vpd_pg0)
		kमुक्त_rcu(vpd_pg0, rcu);
	अगर (vpd_pg83)
		kमुक्त_rcu(vpd_pg83, rcu);
	अगर (vpd_pg80)
		kमुक्त_rcu(vpd_pg80, rcu);
	अगर (vpd_pg89)
		kमुक्त_rcu(vpd_pg89, rcu);
	kमुक्त(sdev->inquiry);
	kमुक्त(sdev);

	अगर (parent)
		put_device(parent);
पूर्ण

अटल व्योम scsi_device_dev_release(काष्ठा device *dev)
अणु
	काष्ठा scsi_device *sdp = to_scsi_device(dev);
	execute_in_process_context(scsi_device_dev_release_usercontext,
				   &sdp->ew);
पूर्ण

अटल काष्ठा class sdev_class = अणु
	.name		= "scsi_device",
	.dev_release	= scsi_device_cls_release,
पूर्ण;

/* all probing is करोne in the inभागidual ->probe routines */
अटल पूर्णांक scsi_bus_match(काष्ठा device *dev, काष्ठा device_driver *gendrv)
अणु
	काष्ठा scsi_device *sdp;

	अगर (dev->type != &scsi_dev_type)
		वापस 0;

	sdp = to_scsi_device(dev);
	अगर (sdp->no_uld_attach)
		वापस 0;
	वापस (sdp->inq_periph_qual == SCSI_INQ_PQ_CON)? 1: 0;
पूर्ण

अटल पूर्णांक scsi_bus_uevent(काष्ठा device *dev, काष्ठा kobj_uevent_env *env)
अणु
	काष्ठा scsi_device *sdev;

	अगर (dev->type != &scsi_dev_type)
		वापस 0;

	sdev = to_scsi_device(dev);

	add_uevent_var(env, "MODALIAS=" SCSI_DEVICE_MODALIAS_FMT, sdev->type);
	वापस 0;
पूर्ण

काष्ठा bus_type scsi_bus_type = अणु
        .name		= "scsi",
        .match		= scsi_bus_match,
	.uevent		= scsi_bus_uevent,
#अगर_घोषित CONFIG_PM
	.pm		= &scsi_bus_pm_ops,
#पूर्ण_अगर
पूर्ण;
EXPORT_SYMBOL_GPL(scsi_bus_type);

पूर्णांक scsi_sysfs_रेजिस्टर(व्योम)
अणु
	पूर्णांक error;

	error = bus_रेजिस्टर(&scsi_bus_type);
	अगर (!error) अणु
		error = class_रेजिस्टर(&sdev_class);
		अगर (error)
			bus_unरेजिस्टर(&scsi_bus_type);
	पूर्ण

	वापस error;
पूर्ण

व्योम scsi_sysfs_unरेजिस्टर(व्योम)
अणु
	class_unरेजिस्टर(&sdev_class);
	bus_unरेजिस्टर(&scsi_bus_type);
पूर्ण

/*
 * sdev_show_function: macro to create an attr function that can be used to
 * show a non-bit field.
 */
#घोषणा sdev_show_function(field, क्रमmat_string)				\
अटल sमाप_प्रकार								\
sdev_show_##field (काष्ठा device *dev, काष्ठा device_attribute *attr,	\
		   अक्षर *buf)						\
अणु									\
	काष्ठा scsi_device *sdev;					\
	sdev = to_scsi_device(dev);					\
	वापस snम_लिखो (buf, 20, क्रमmat_string, sdev->field);		\
पूर्ण									\

/*
 * sdev_rd_attr: macro to create a function and attribute variable क्रम a
 * पढ़ो only field.
 */
#घोषणा sdev_rd_attr(field, क्रमmat_string)				\
	sdev_show_function(field, क्रमmat_string)			\
अटल DEVICE_ATTR(field, S_IRUGO, sdev_show_##field, शून्य);


/*
 * sdev_rw_attr: create a function and attribute variable क्रम a
 * पढ़ो/ग_लिखो field.
 */
#घोषणा sdev_rw_attr(field, क्रमmat_string)				\
	sdev_show_function(field, क्रमmat_string)				\
									\
अटल sमाप_प्रकार								\
sdev_store_##field (काष्ठा device *dev, काष्ठा device_attribute *attr,	\
		    स्थिर अक्षर *buf, माप_प्रकार count)			\
अणु									\
	काष्ठा scsi_device *sdev;					\
	sdev = to_scsi_device(dev);					\
	माला_पूछो (buf, क्रमmat_string, &sdev->field);			\
	वापस count;							\
पूर्ण									\
अटल DEVICE_ATTR(field, S_IRUGO | S_IWUSR, sdev_show_##field, sdev_store_##field);

/* Currently we करोn't export bit fields, but we might in future,
 * so leave this code in */
#अगर 0
/*
 * sdev_rd_attr: create a function and attribute variable क्रम a
 * पढ़ो/ग_लिखो bit field.
 */
#घोषणा sdev_rw_attr_bit(field)						\
	sdev_show_function(field, "%d\n")					\
									\
अटल sमाप_प्रकार								\
sdev_store_##field (काष्ठा device *dev, काष्ठा device_attribute *attr,	\
		    स्थिर अक्षर *buf, माप_प्रकार count)			\
अणु									\
	पूर्णांक ret;							\
	काष्ठा scsi_device *sdev;					\
	ret = scsi_sdev_check_buf_bit(buf);				\
	अगर (ret >= 0)	अणु						\
		sdev = to_scsi_device(dev);				\
		sdev->field = ret;					\
		ret = count;						\
	पूर्ण								\
	वापस ret;							\
पूर्ण									\
अटल DEVICE_ATTR(field, S_IRUGO | S_IWUSR, sdev_show_##field, sdev_store_##field);

/*
 * scsi_sdev_check_buf_bit: वापस 0 अगर buf is "0", वापस 1 अगर buf is "1",
 * अन्यथा वापस -EINVAL.
 */
अटल पूर्णांक scsi_sdev_check_buf_bit(स्थिर अक्षर *buf)
अणु
	अगर ((buf[1] == '\0') || ((buf[1] == '\n') && (buf[2] == '\0'))) अणु
		अगर (buf[0] == '1')
			वापस 1;
		अन्यथा अगर (buf[0] == '0')
			वापस 0;
		अन्यथा 
			वापस -EINVAL;
	पूर्ण अन्यथा
		वापस -EINVAL;
पूर्ण
#पूर्ण_अगर
/*
 * Create the actual show/store functions and data काष्ठाures.
 */
sdev_rd_attr (type, "%d\n");
sdev_rd_attr (scsi_level, "%d\n");
sdev_rd_attr (venकरोr, "%.8s\n");
sdev_rd_attr (model, "%.16s\n");
sdev_rd_attr (rev, "%.4s\n");

अटल sमाप_प्रकार
sdev_show_device_busy(काष्ठा device *dev, काष्ठा device_attribute *attr,
		अक्षर *buf)
अणु
	काष्ठा scsi_device *sdev = to_scsi_device(dev);
	वापस snम_लिखो(buf, 20, "%d\n", scsi_device_busy(sdev));
पूर्ण
अटल DEVICE_ATTR(device_busy, S_IRUGO, sdev_show_device_busy, शून्य);

अटल sमाप_प्रकार
sdev_show_device_blocked(काष्ठा device *dev, काष्ठा device_attribute *attr,
		अक्षर *buf)
अणु
	काष्ठा scsi_device *sdev = to_scsi_device(dev);
	वापस snम_लिखो(buf, 20, "%d\n", atomic_पढ़ो(&sdev->device_blocked));
पूर्ण
अटल DEVICE_ATTR(device_blocked, S_IRUGO, sdev_show_device_blocked, शून्य);

/*
 * TODO: can we make these symlinks to the block layer ones?
 */
अटल sमाप_प्रकार
sdev_show_समयout (काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा scsi_device *sdev;
	sdev = to_scsi_device(dev);
	वापस snम_लिखो(buf, 20, "%d\n", sdev->request_queue->rq_समयout / HZ);
पूर्ण

अटल sमाप_प्रकार
sdev_store_समयout (काष्ठा device *dev, काष्ठा device_attribute *attr,
		    स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा scsi_device *sdev;
	पूर्णांक समयout;
	sdev = to_scsi_device(dev);
	माला_पूछो (buf, "%d\n", &समयout);
	blk_queue_rq_समयout(sdev->request_queue, समयout * HZ);
	वापस count;
पूर्ण
अटल DEVICE_ATTR(समयout, S_IRUGO | S_IWUSR, sdev_show_समयout, sdev_store_समयout);

अटल sमाप_प्रकार
sdev_show_eh_समयout(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा scsi_device *sdev;
	sdev = to_scsi_device(dev);
	वापस snम_लिखो(buf, 20, "%u\n", sdev->eh_समयout / HZ);
पूर्ण

अटल sमाप_प्रकार
sdev_store_eh_समयout(काष्ठा device *dev, काष्ठा device_attribute *attr,
		    स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा scsi_device *sdev;
	अचिन्हित पूर्णांक eh_समयout;
	पूर्णांक err;

	अगर (!capable(CAP_SYS_ADMIN))
		वापस -EACCES;

	sdev = to_scsi_device(dev);
	err = kstrtouपूर्णांक(buf, 10, &eh_समयout);
	अगर (err)
		वापस err;
	sdev->eh_समयout = eh_समयout * HZ;

	वापस count;
पूर्ण
अटल DEVICE_ATTR(eh_समयout, S_IRUGO | S_IWUSR, sdev_show_eh_समयout, sdev_store_eh_समयout);

अटल sमाप_प्रकार
store_rescan_field (काष्ठा device *dev, काष्ठा device_attribute *attr,
		    स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	scsi_rescan_device(dev);
	वापस count;
पूर्ण
अटल DEVICE_ATTR(rescan, S_IWUSR, शून्य, store_rescan_field);

अटल sमाप_प्रकार
sdev_store_delete(काष्ठा device *dev, काष्ठा device_attribute *attr,
		  स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा kernfs_node *kn;
	काष्ठा scsi_device *sdev = to_scsi_device(dev);

	/*
	 * We need to try to get module, aव्योमing the module been हटाओd
	 * during delete.
	 */
	अगर (scsi_device_get(sdev))
		वापस -ENODEV;

	kn = sysfs_अवरोध_active_protection(&dev->kobj, &attr->attr);
	WARN_ON_ONCE(!kn);
	/*
	 * Concurrent ग_लिखोs पूर्णांकo the "delete" sysfs attribute may trigger
	 * concurrent calls to device_हटाओ_file() and scsi_हटाओ_device().
	 * device_हटाओ_file() handles concurrent removal calls by
	 * serializing these and by ignoring the second and later removal
	 * attempts.  Concurrent calls of scsi_हटाओ_device() are
	 * serialized. The second and later calls of scsi_हटाओ_device() are
	 * ignored because the first call of that function changes the device
	 * state पूर्णांकo SDEV_DEL.
	 */
	device_हटाओ_file(dev, attr);
	scsi_हटाओ_device(sdev);
	अगर (kn)
		sysfs_unअवरोध_active_protection(kn);
	scsi_device_put(sdev);
	वापस count;
पूर्ण;
अटल DEVICE_ATTR(delete, S_IWUSR, शून्य, sdev_store_delete);

अटल sमाप_प्रकार
store_state_field(काष्ठा device *dev, काष्ठा device_attribute *attr,
		  स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	पूर्णांक i, ret;
	काष्ठा scsi_device *sdev = to_scsi_device(dev);
	क्रमागत scsi_device_state state = 0;

	क्रम (i = 0; i < ARRAY_SIZE(sdev_states); i++) अणु
		स्थिर पूर्णांक len = म_माप(sdev_states[i].name);
		अगर (म_भेदन(sdev_states[i].name, buf, len) == 0 &&
		   buf[len] == '\n') अणु
			state = sdev_states[i].value;
			अवरोध;
		पूर्ण
	पूर्ण
	चयन (state) अणु
	हाल SDEV_RUNNING:
	हाल SDEV_OFFLINE:
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	mutex_lock(&sdev->state_mutex);
	ret = scsi_device_set_state(sdev, state);
	/*
	 * If the device state changes to SDEV_RUNNING, we need to run
	 * the queue to aव्योम I/O hang.
	 */
	अगर (ret == 0 && state == SDEV_RUNNING)
		blk_mq_run_hw_queues(sdev->request_queue, true);
	mutex_unlock(&sdev->state_mutex);

	वापस ret == 0 ? count : -EINVAL;
पूर्ण

अटल sमाप_प्रकार
show_state_field(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा scsi_device *sdev = to_scsi_device(dev);
	स्थिर अक्षर *name = scsi_device_state_name(sdev->sdev_state);

	अगर (!name)
		वापस -EINVAL;

	वापस snम_लिखो(buf, 20, "%s\n", name);
पूर्ण

अटल DEVICE_ATTR(state, S_IRUGO | S_IWUSR, show_state_field, store_state_field);

अटल sमाप_प्रकार
show_queue_type_field(काष्ठा device *dev, काष्ठा device_attribute *attr,
		      अक्षर *buf)
अणु
	काष्ठा scsi_device *sdev = to_scsi_device(dev);
	स्थिर अक्षर *name = "none";

	अगर (sdev->simple_tags)
		name = "simple";

	वापस snम_लिखो(buf, 20, "%s\n", name);
पूर्ण

अटल sमाप_प्रकार
store_queue_type_field(काष्ठा device *dev, काष्ठा device_attribute *attr,
		       स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा scsi_device *sdev = to_scsi_device(dev);

	अगर (!sdev->tagged_supported)
		वापस -EINVAL;
		
	sdev_prपूर्णांकk(KERN_INFO, sdev,
		    "ignoring write to deprecated queue_type attribute");
	वापस count;
पूर्ण

अटल DEVICE_ATTR(queue_type, S_IRUGO | S_IWUSR, show_queue_type_field,
		   store_queue_type_field);

#घोषणा sdev_vpd_pg_attr(_page)						\
अटल sमाप_प्रकार							\
show_vpd_##_page(काष्ठा file *filp, काष्ठा kobject *kobj,	\
		 काष्ठा bin_attribute *bin_attr,			\
		 अक्षर *buf, loff_t off, माप_प्रकार count)			\
अणु									\
	काष्ठा device *dev = kobj_to_dev(kobj);				\
	काष्ठा scsi_device *sdev = to_scsi_device(dev);			\
	काष्ठा scsi_vpd *vpd_page;					\
	पूर्णांक ret = -EINVAL;						\
									\
	rcu_पढ़ो_lock();						\
	vpd_page = rcu_dereference(sdev->vpd_##_page);			\
	अगर (vpd_page)							\
		ret = memory_पढ़ो_from_buffer(buf, count, &off,		\
				vpd_page->data, vpd_page->len);		\
	rcu_पढ़ो_unlock();						\
	वापस ret;							\
पूर्ण									\
अटल काष्ठा bin_attribute dev_attr_vpd_##_page = अणु		\
	.attr =	अणु.name = __stringअगरy(vpd_##_page), .mode = S_IRUGO पूर्ण,	\
	.size = 0,							\
	.पढ़ो = show_vpd_##_page,					\
पूर्ण;

sdev_vpd_pg_attr(pg83);
sdev_vpd_pg_attr(pg80);
sdev_vpd_pg_attr(pg89);
sdev_vpd_pg_attr(pg0);

अटल sमाप_प्रकार show_inquiry(काष्ठा file *filep, काष्ठा kobject *kobj,
			    काष्ठा bin_attribute *bin_attr,
			    अक्षर *buf, loff_t off, माप_प्रकार count)
अणु
	काष्ठा device *dev = kobj_to_dev(kobj);
	काष्ठा scsi_device *sdev = to_scsi_device(dev);

	अगर (!sdev->inquiry)
		वापस -EINVAL;

	वापस memory_पढ़ो_from_buffer(buf, count, &off, sdev->inquiry,
				       sdev->inquiry_len);
पूर्ण

अटल काष्ठा bin_attribute dev_attr_inquiry = अणु
	.attr = अणु
		.name = "inquiry",
		.mode = S_IRUGO,
	पूर्ण,
	.size = 0,
	.पढ़ो = show_inquiry,
पूर्ण;

अटल sमाप_प्रकार
show_iostat_counterbits(काष्ठा device *dev, काष्ठा device_attribute *attr,
			अक्षर *buf)
अणु
	वापस snम_लिखो(buf, 20, "%d\n", (पूर्णांक)माप(atomic_t) * 8);
पूर्ण

अटल DEVICE_ATTR(iocounterbits, S_IRUGO, show_iostat_counterbits, शून्य);

#घोषणा show_sdev_iostat(field)						\
अटल sमाप_प्रकार								\
show_iostat_##field(काष्ठा device *dev, काष्ठा device_attribute *attr,	\
		    अक्षर *buf)						\
अणु									\
	काष्ठा scsi_device *sdev = to_scsi_device(dev);			\
	अचिन्हित दीर्घ दीर्घ count = atomic_पढ़ो(&sdev->field);		\
	वापस snम_लिखो(buf, 20, "0x%llx\n", count);			\
पूर्ण									\
अटल DEVICE_ATTR(field, S_IRUGO, show_iostat_##field, शून्य)

show_sdev_iostat(iorequest_cnt);
show_sdev_iostat(ioकरोne_cnt);
show_sdev_iostat(ioerr_cnt);

अटल sमाप_प्रकार
sdev_show_modalias(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा scsi_device *sdev;
	sdev = to_scsi_device(dev);
	वापस snम_लिखो (buf, 20, SCSI_DEVICE_MODALIAS_FMT "\n", sdev->type);
पूर्ण
अटल DEVICE_ATTR(modalias, S_IRUGO, sdev_show_modalias, शून्य);

#घोषणा DECLARE_EVT_SHOW(name, Cap_name)				\
अटल sमाप_प्रकार								\
sdev_show_evt_##name(काष्ठा device *dev, काष्ठा device_attribute *attr,	\
		     अक्षर *buf)						\
अणु									\
	काष्ठा scsi_device *sdev = to_scsi_device(dev);			\
	पूर्णांक val = test_bit(SDEV_EVT_##Cap_name, sdev->supported_events);\
	वापस snम_लिखो(buf, 20, "%d\n", val);				\
पूर्ण

#घोषणा DECLARE_EVT_STORE(name, Cap_name)				\
अटल sमाप_प्रकार								\
sdev_store_evt_##name(काष्ठा device *dev, काष्ठा device_attribute *attr,\
		      स्थिर अक्षर *buf, माप_प्रकार count)			\
अणु									\
	काष्ठा scsi_device *sdev = to_scsi_device(dev);			\
	पूर्णांक val = simple_म_से_अदीर्घ(buf, शून्य, 0);				\
	अगर (val == 0)							\
		clear_bit(SDEV_EVT_##Cap_name, sdev->supported_events);	\
	अन्यथा अगर (val == 1)						\
		set_bit(SDEV_EVT_##Cap_name, sdev->supported_events);	\
	अन्यथा								\
		वापस -EINVAL;						\
	वापस count;							\
पूर्ण

#घोषणा DECLARE_EVT(name, Cap_name)					\
	DECLARE_EVT_SHOW(name, Cap_name)				\
	DECLARE_EVT_STORE(name, Cap_name)				\
	अटल DEVICE_ATTR(evt_##name, S_IRUGO, sdev_show_evt_##name,	\
			   sdev_store_evt_##name);
#घोषणा REF_EVT(name) &dev_attr_evt_##name.attr

DECLARE_EVT(media_change, MEDIA_CHANGE)
DECLARE_EVT(inquiry_change_reported, INQUIRY_CHANGE_REPORTED)
DECLARE_EVT(capacity_change_reported, CAPACITY_CHANGE_REPORTED)
DECLARE_EVT(soft_threshold_reached, SOFT_THRESHOLD_REACHED_REPORTED)
DECLARE_EVT(mode_parameter_change_reported, MODE_PARAMETER_CHANGE_REPORTED)
DECLARE_EVT(lun_change_reported, LUN_CHANGE_REPORTED)

अटल sमाप_प्रकार
sdev_store_queue_depth(काष्ठा device *dev, काष्ठा device_attribute *attr,
		       स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	पूर्णांक depth, retval;
	काष्ठा scsi_device *sdev = to_scsi_device(dev);
	काष्ठा scsi_host_ढाँचा *sht = sdev->host->hostt;

	अगर (!sht->change_queue_depth)
		वापस -EINVAL;

	depth = simple_म_से_अदीर्घ(buf, शून्य, 0);

	अगर (depth < 1 || depth > sdev->host->can_queue)
		वापस -EINVAL;

	retval = sht->change_queue_depth(sdev, depth);
	अगर (retval < 0)
		वापस retval;

	sdev->max_queue_depth = sdev->queue_depth;

	वापस count;
पूर्ण
sdev_show_function(queue_depth, "%d\n");

अटल DEVICE_ATTR(queue_depth, S_IRUGO | S_IWUSR, sdev_show_queue_depth,
		   sdev_store_queue_depth);

अटल sमाप_प्रकार
sdev_show_wwid(काष्ठा device *dev, काष्ठा device_attribute *attr,
		    अक्षर *buf)
अणु
	काष्ठा scsi_device *sdev = to_scsi_device(dev);
	sमाप_प्रकार count;

	count = scsi_vpd_lun_id(sdev, buf, PAGE_SIZE);
	अगर (count > 0) अणु
		buf[count] = '\n';
		count++;
	पूर्ण
	वापस count;
पूर्ण
अटल DEVICE_ATTR(wwid, S_IRUGO, sdev_show_wwid, शून्य);

#घोषणा BLIST_FLAG_NAME(name)					\
	[स्थिर_ilog2((__क्रमce __u64)BLIST_##name)] = #name
अटल स्थिर अक्षर *स्थिर sdev_bflags_name[] = अणु
#समावेश "scsi_devinfo_tbl.c"
पूर्ण;
#अघोषित BLIST_FLAG_NAME

अटल sमाप_प्रकार
sdev_show_blacklist(काष्ठा device *dev, काष्ठा device_attribute *attr,
		    अक्षर *buf)
अणु
	काष्ठा scsi_device *sdev = to_scsi_device(dev);
	पूर्णांक i;
	sमाप_प्रकार len = 0;

	क्रम (i = 0; i < माप(sdev->sdev_bflags) * BITS_PER_BYTE; i++) अणु
		स्थिर अक्षर *name = शून्य;

		अगर (!(sdev->sdev_bflags & (__क्रमce blist_flags_t)BIT(i)))
			जारी;
		अगर (i < ARRAY_SIZE(sdev_bflags_name) && sdev_bflags_name[i])
			name = sdev_bflags_name[i];

		अगर (name)
			len += scnम_लिखो(buf + len, PAGE_SIZE - len,
					 "%s%s", len ? " " : "", name);
		अन्यथा
			len += scnम_लिखो(buf + len, PAGE_SIZE - len,
					 "%sINVALID_BIT(%d)", len ? " " : "", i);
	पूर्ण
	अगर (len)
		len += scnम_लिखो(buf + len, PAGE_SIZE - len, "\n");
	वापस len;
पूर्ण
अटल DEVICE_ATTR(blacklist, S_IRUGO, sdev_show_blacklist, शून्य);

#अगर_घोषित CONFIG_SCSI_DH
अटल sमाप_प्रकार
sdev_show_dh_state(काष्ठा device *dev, काष्ठा device_attribute *attr,
		   अक्षर *buf)
अणु
	काष्ठा scsi_device *sdev = to_scsi_device(dev);

	अगर (!sdev->handler)
		वापस snम_लिखो(buf, 20, "detached\n");

	वापस snम_लिखो(buf, 20, "%s\n", sdev->handler->name);
पूर्ण

अटल sमाप_प्रकार
sdev_store_dh_state(काष्ठा device *dev, काष्ठा device_attribute *attr,
		    स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा scsi_device *sdev = to_scsi_device(dev);
	पूर्णांक err = -EINVAL;

	अगर (sdev->sdev_state == SDEV_CANCEL ||
	    sdev->sdev_state == SDEV_DEL)
		वापस -ENODEV;

	अगर (!sdev->handler) अणु
		/*
		 * Attach to a device handler
		 */
		err = scsi_dh_attach(sdev->request_queue, buf);
	पूर्ण अन्यथा अगर (!म_भेदन(buf, "activate", 8)) अणु
		/*
		 * Activate a device handler
		 */
		अगर (sdev->handler->activate)
			err = sdev->handler->activate(sdev, शून्य, शून्य);
		अन्यथा
			err = 0;
	पूर्ण अन्यथा अगर (!म_भेदन(buf, "detach", 6)) अणु
		/*
		 * Detach from a device handler
		 */
		sdev_prपूर्णांकk(KERN_WARNING, sdev,
			    "can't detach handler %s.\n",
			    sdev->handler->name);
		err = -EINVAL;
	पूर्ण

	वापस err < 0 ? err : count;
पूर्ण

अटल DEVICE_ATTR(dh_state, S_IRUGO | S_IWUSR, sdev_show_dh_state,
		   sdev_store_dh_state);

अटल sमाप_प्रकार
sdev_show_access_state(काष्ठा device *dev,
		       काष्ठा device_attribute *attr,
		       अक्षर *buf)
अणु
	काष्ठा scsi_device *sdev = to_scsi_device(dev);
	अचिन्हित अक्षर access_state;
	स्थिर अक्षर *access_state_name;

	अगर (!sdev->handler)
		वापस -EINVAL;

	access_state = (sdev->access_state & SCSI_ACCESS_STATE_MASK);
	access_state_name = scsi_access_state_name(access_state);

	वापस प्र_लिखो(buf, "%s\n",
		       access_state_name ? access_state_name : "unknown");
पूर्ण
अटल DEVICE_ATTR(access_state, S_IRUGO, sdev_show_access_state, शून्य);

अटल sमाप_प्रकार
sdev_show_preferred_path(काष्ठा device *dev,
			 काष्ठा device_attribute *attr,
			 अक्षर *buf)
अणु
	काष्ठा scsi_device *sdev = to_scsi_device(dev);

	अगर (!sdev->handler)
		वापस -EINVAL;

	अगर (sdev->access_state & SCSI_ACCESS_STATE_PREFERRED)
		वापस प्र_लिखो(buf, "1\n");
	अन्यथा
		वापस प्र_लिखो(buf, "0\n");
पूर्ण
अटल DEVICE_ATTR(preferred_path, S_IRUGO, sdev_show_preferred_path, शून्य);
#पूर्ण_अगर

अटल sमाप_प्रकार
sdev_show_queue_ramp_up_period(काष्ठा device *dev,
			       काष्ठा device_attribute *attr,
			       अक्षर *buf)
अणु
	काष्ठा scsi_device *sdev;
	sdev = to_scsi_device(dev);
	वापस snम_लिखो(buf, 20, "%u\n",
			jअगरfies_to_msecs(sdev->queue_ramp_up_period));
पूर्ण

अटल sमाप_प्रकार
sdev_store_queue_ramp_up_period(काष्ठा device *dev,
				काष्ठा device_attribute *attr,
				स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा scsi_device *sdev = to_scsi_device(dev);
	अचिन्हित पूर्णांक period;

	अगर (kstrtouपूर्णांक(buf, 10, &period))
		वापस -EINVAL;

	sdev->queue_ramp_up_period = msecs_to_jअगरfies(period);
	वापस count;
पूर्ण

अटल DEVICE_ATTR(queue_ramp_up_period, S_IRUGO | S_IWUSR,
		   sdev_show_queue_ramp_up_period,
		   sdev_store_queue_ramp_up_period);

अटल umode_t scsi_sdev_attr_is_visible(काष्ठा kobject *kobj,
					 काष्ठा attribute *attr, पूर्णांक i)
अणु
	काष्ठा device *dev = kobj_to_dev(kobj);
	काष्ठा scsi_device *sdev = to_scsi_device(dev);


	अगर (attr == &dev_attr_queue_depth.attr &&
	    !sdev->host->hostt->change_queue_depth)
		वापस S_IRUGO;

	अगर (attr == &dev_attr_queue_ramp_up_period.attr &&
	    !sdev->host->hostt->change_queue_depth)
		वापस 0;

#अगर_घोषित CONFIG_SCSI_DH
	अगर (attr == &dev_attr_access_state.attr &&
	    !sdev->handler)
		वापस 0;
	अगर (attr == &dev_attr_preferred_path.attr &&
	    !sdev->handler)
		वापस 0;
#पूर्ण_अगर
	वापस attr->mode;
पूर्ण

अटल umode_t scsi_sdev_bin_attr_is_visible(काष्ठा kobject *kobj,
					     काष्ठा bin_attribute *attr, पूर्णांक i)
अणु
	काष्ठा device *dev = kobj_to_dev(kobj);
	काष्ठा scsi_device *sdev = to_scsi_device(dev);


	अगर (attr == &dev_attr_vpd_pg0 && !sdev->vpd_pg0)
		वापस 0;

	अगर (attr == &dev_attr_vpd_pg80 && !sdev->vpd_pg80)
		वापस 0;

	अगर (attr == &dev_attr_vpd_pg83 && !sdev->vpd_pg83)
		वापस 0;

	अगर (attr == &dev_attr_vpd_pg89 && !sdev->vpd_pg89)
		वापस 0;

	वापस S_IRUGO;
पूर्ण

/* Default ढाँचा क्रम device attributes.  May NOT be modअगरied */
अटल काष्ठा attribute *scsi_sdev_attrs[] = अणु
	&dev_attr_device_blocked.attr,
	&dev_attr_type.attr,
	&dev_attr_scsi_level.attr,
	&dev_attr_device_busy.attr,
	&dev_attr_venकरोr.attr,
	&dev_attr_model.attr,
	&dev_attr_rev.attr,
	&dev_attr_rescan.attr,
	&dev_attr_delete.attr,
	&dev_attr_state.attr,
	&dev_attr_समयout.attr,
	&dev_attr_eh_समयout.attr,
	&dev_attr_iocounterbits.attr,
	&dev_attr_iorequest_cnt.attr,
	&dev_attr_ioकरोne_cnt.attr,
	&dev_attr_ioerr_cnt.attr,
	&dev_attr_modalias.attr,
	&dev_attr_queue_depth.attr,
	&dev_attr_queue_type.attr,
	&dev_attr_wwid.attr,
	&dev_attr_blacklist.attr,
#अगर_घोषित CONFIG_SCSI_DH
	&dev_attr_dh_state.attr,
	&dev_attr_access_state.attr,
	&dev_attr_preferred_path.attr,
#पूर्ण_अगर
	&dev_attr_queue_ramp_up_period.attr,
	REF_EVT(media_change),
	REF_EVT(inquiry_change_reported),
	REF_EVT(capacity_change_reported),
	REF_EVT(soft_threshold_reached),
	REF_EVT(mode_parameter_change_reported),
	REF_EVT(lun_change_reported),
	शून्य
पूर्ण;

अटल काष्ठा bin_attribute *scsi_sdev_bin_attrs[] = अणु
	&dev_attr_vpd_pg0,
	&dev_attr_vpd_pg83,
	&dev_attr_vpd_pg80,
	&dev_attr_vpd_pg89,
	&dev_attr_inquiry,
	शून्य
पूर्ण;
अटल काष्ठा attribute_group scsi_sdev_attr_group = अणु
	.attrs =	scsi_sdev_attrs,
	.bin_attrs =	scsi_sdev_bin_attrs,
	.is_visible =	scsi_sdev_attr_is_visible,
	.is_bin_visible = scsi_sdev_bin_attr_is_visible,
पूर्ण;

अटल स्थिर काष्ठा attribute_group *scsi_sdev_attr_groups[] = अणु
	&scsi_sdev_attr_group,
	शून्य
पूर्ण;

अटल पूर्णांक scsi_target_add(काष्ठा scsi_target *starget)
अणु
	पूर्णांक error;

	अगर (starget->state != STARGET_CREATED)
		वापस 0;

	error = device_add(&starget->dev);
	अगर (error) अणु
		dev_err(&starget->dev, "target device_add failed, error %d\n", error);
		वापस error;
	पूर्ण
	transport_add_device(&starget->dev);
	starget->state = STARGET_RUNNING;

	pm_runसमय_set_active(&starget->dev);
	pm_runसमय_enable(&starget->dev);
	device_enable_async_suspend(&starget->dev);

	वापस 0;
पूर्ण

/**
 * scsi_sysfs_add_sdev - add scsi device to sysfs
 * @sdev:	scsi_device to add
 *
 * Return value:
 * 	0 on Success / non-zero on Failure
 **/
पूर्णांक scsi_sysfs_add_sdev(काष्ठा scsi_device *sdev)
अणु
	पूर्णांक error, i;
	काष्ठा request_queue *rq = sdev->request_queue;
	काष्ठा scsi_target *starget = sdev->sdev_target;

	error = scsi_target_add(starget);
	अगर (error)
		वापस error;

	transport_configure_device(&starget->dev);

	device_enable_async_suspend(&sdev->sdev_gendev);
	scsi_स्वतःpm_get_target(starget);
	pm_runसमय_set_active(&sdev->sdev_gendev);
	अगर (!sdev->rpm_स्वतःsuspend)
		pm_runसमय_क्रमbid(&sdev->sdev_gendev);
	pm_runसमय_enable(&sdev->sdev_gendev);
	scsi_स्वतःpm_put_target(starget);

	scsi_स्वतःpm_get_device(sdev);

	scsi_dh_add_device(sdev);

	error = device_add(&sdev->sdev_gendev);
	अगर (error) अणु
		sdev_prपूर्णांकk(KERN_INFO, sdev,
				"failed to add device: %d\n", error);
		वापस error;
	पूर्ण

	device_enable_async_suspend(&sdev->sdev_dev);
	error = device_add(&sdev->sdev_dev);
	अगर (error) अणु
		sdev_prपूर्णांकk(KERN_INFO, sdev,
				"failed to add class device: %d\n", error);
		device_del(&sdev->sdev_gendev);
		वापस error;
	पूर्ण
	transport_add_device(&sdev->sdev_gendev);
	sdev->is_visible = 1;

	error = bsg_scsi_रेजिस्टर_queue(rq, &sdev->sdev_gendev);
	अगर (error)
		/* we're treating error on bsg रेजिस्टर as non-fatal,
		 * so pretend nothing went wrong */
		sdev_prपूर्णांकk(KERN_INFO, sdev,
			    "Failed to register bsg queue, errno=%d\n", error);

	/* add additional host specअगरic attributes */
	अगर (sdev->host->hostt->sdev_attrs) अणु
		क्रम (i = 0; sdev->host->hostt->sdev_attrs[i]; i++) अणु
			error = device_create_file(&sdev->sdev_gendev,
					sdev->host->hostt->sdev_attrs[i]);
			अगर (error)
				वापस error;
		पूर्ण
	पूर्ण

	अगर (sdev->host->hostt->sdev_groups) अणु
		error = sysfs_create_groups(&sdev->sdev_gendev.kobj,
				sdev->host->hostt->sdev_groups);
		अगर (error)
			वापस error;
	पूर्ण

	scsi_स्वतःpm_put_device(sdev);
	वापस error;
पूर्ण

व्योम __scsi_हटाओ_device(काष्ठा scsi_device *sdev)
अणु
	काष्ठा device *dev = &sdev->sdev_gendev;
	पूर्णांक res;

	/*
	 * This cleanup path is not reentrant and जबतक it is impossible
	 * to get a new reference with scsi_device_get() someone can still
	 * hold a previously acquired one.
	 */
	अगर (sdev->sdev_state == SDEV_DEL)
		वापस;

	अगर (sdev->is_visible) अणु
		/*
		 * If scsi_पूर्णांकernal_target_block() is running concurrently,
		 * रुको until it has finished beक्रमe changing the device state.
		 */
		mutex_lock(&sdev->state_mutex);
		/*
		 * If blocked, we go straight to DEL and restart the queue so
		 * any commands issued during driver shutकरोwn (like sync
		 * cache) are errored immediately.
		 */
		res = scsi_device_set_state(sdev, SDEV_CANCEL);
		अगर (res != 0) अणु
			res = scsi_device_set_state(sdev, SDEV_DEL);
			अगर (res == 0)
				scsi_start_queue(sdev);
		पूर्ण
		mutex_unlock(&sdev->state_mutex);

		अगर (res != 0)
			वापस;

		अगर (sdev->host->hostt->sdev_groups)
			sysfs_हटाओ_groups(&sdev->sdev_gendev.kobj,
					sdev->host->hostt->sdev_groups);

		bsg_unरेजिस्टर_queue(sdev->request_queue);
		device_unरेजिस्टर(&sdev->sdev_dev);
		transport_हटाओ_device(dev);
		device_del(dev);
	पूर्ण अन्यथा
		put_device(&sdev->sdev_dev);

	/*
	 * Stop accepting new requests and रुको until all queuecommand() and
	 * scsi_run_queue() invocations have finished beक्रमe tearing करोwn the
	 * device.
	 */
	mutex_lock(&sdev->state_mutex);
	scsi_device_set_state(sdev, SDEV_DEL);
	mutex_unlock(&sdev->state_mutex);

	blk_cleanup_queue(sdev->request_queue);
	cancel_work_sync(&sdev->requeue_work);

	अगर (sdev->host->hostt->slave_destroy)
		sdev->host->hostt->slave_destroy(sdev);
	transport_destroy_device(dev);

	/*
	 * Paired with the kref_get() in scsi_sysfs_initialize().  We have
	 * हटाओd sysfs visibility from the device, so make the target
	 * invisible अगर this was the last device underneath it.
	 */
	scsi_target_reap(scsi_target(sdev));

	put_device(dev);
पूर्ण

/**
 * scsi_हटाओ_device - unरेजिस्टर a device from the scsi bus
 * @sdev:	scsi_device to unरेजिस्टर
 **/
व्योम scsi_हटाओ_device(काष्ठा scsi_device *sdev)
अणु
	काष्ठा Scsi_Host *shost = sdev->host;

	mutex_lock(&shost->scan_mutex);
	__scsi_हटाओ_device(sdev);
	mutex_unlock(&shost->scan_mutex);
पूर्ण
EXPORT_SYMBOL(scsi_हटाओ_device);

अटल व्योम __scsi_हटाओ_target(काष्ठा scsi_target *starget)
अणु
	काष्ठा Scsi_Host *shost = dev_to_shost(starget->dev.parent);
	अचिन्हित दीर्घ flags;
	काष्ठा scsi_device *sdev;

	spin_lock_irqsave(shost->host_lock, flags);
 restart:
	list_क्रम_each_entry(sdev, &shost->__devices, siblings) अणु
		/*
		 * We cannot call scsi_device_get() here, as
		 * we might've been called from rmmod() causing
		 * scsi_device_get() to fail the module_is_live()
		 * check.
		 */
		अगर (sdev->channel != starget->channel ||
		    sdev->id != starget->id)
			जारी;
		अगर (sdev->sdev_state == SDEV_DEL ||
		    sdev->sdev_state == SDEV_CANCEL ||
		    !get_device(&sdev->sdev_gendev))
			जारी;
		spin_unlock_irqrestore(shost->host_lock, flags);
		scsi_हटाओ_device(sdev);
		put_device(&sdev->sdev_gendev);
		spin_lock_irqsave(shost->host_lock, flags);
		जाओ restart;
	पूर्ण
	spin_unlock_irqrestore(shost->host_lock, flags);
पूर्ण

/**
 * scsi_हटाओ_target - try to हटाओ a target and all its devices
 * @dev: generic starget or parent of generic starमाला_लो to be हटाओd
 *
 * Note: This is slightly racy.  It is possible that अगर the user
 * requests the addition of another device then the target won't be
 * हटाओd.
 */
व्योम scsi_हटाओ_target(काष्ठा device *dev)
अणु
	काष्ठा Scsi_Host *shost = dev_to_shost(dev->parent);
	काष्ठा scsi_target *starget;
	अचिन्हित दीर्घ flags;

restart:
	spin_lock_irqsave(shost->host_lock, flags);
	list_क्रम_each_entry(starget, &shost->__tarमाला_लो, siblings) अणु
		अगर (starget->state == STARGET_DEL ||
		    starget->state == STARGET_REMOVE ||
		    starget->state == STARGET_CREATED_REMOVE)
			जारी;
		अगर (starget->dev.parent == dev || &starget->dev == dev) अणु
			kref_get(&starget->reap_ref);
			अगर (starget->state == STARGET_CREATED)
				starget->state = STARGET_CREATED_REMOVE;
			अन्यथा
				starget->state = STARGET_REMOVE;
			spin_unlock_irqrestore(shost->host_lock, flags);
			__scsi_हटाओ_target(starget);
			scsi_target_reap(starget);
			जाओ restart;
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(shost->host_lock, flags);
पूर्ण
EXPORT_SYMBOL(scsi_हटाओ_target);

पूर्णांक scsi_रेजिस्टर_driver(काष्ठा device_driver *drv)
अणु
	drv->bus = &scsi_bus_type;

	वापस driver_रेजिस्टर(drv);
पूर्ण
EXPORT_SYMBOL(scsi_रेजिस्टर_driver);

पूर्णांक scsi_रेजिस्टर_पूर्णांकerface(काष्ठा class_पूर्णांकerface *पूर्णांकf)
अणु
	पूर्णांकf->class = &sdev_class;

	वापस class_पूर्णांकerface_रेजिस्टर(पूर्णांकf);
पूर्ण
EXPORT_SYMBOL(scsi_रेजिस्टर_पूर्णांकerface);

/**
 * scsi_sysfs_add_host - add scsi host to subप्रणाली
 * @shost:     scsi host काष्ठा to add to subप्रणाली
 **/
पूर्णांक scsi_sysfs_add_host(काष्ठा Scsi_Host *shost)
अणु
	पूर्णांक error, i;

	/* add host specअगरic attributes */
	अगर (shost->hostt->shost_attrs) अणु
		क्रम (i = 0; shost->hostt->shost_attrs[i]; i++) अणु
			error = device_create_file(&shost->shost_dev,
					shost->hostt->shost_attrs[i]);
			अगर (error)
				वापस error;
		पूर्ण
	पूर्ण

	transport_रेजिस्टर_device(&shost->shost_gendev);
	transport_configure_device(&shost->shost_gendev);
	वापस 0;
पूर्ण

अटल काष्ठा device_type scsi_dev_type = अणु
	.name =		"scsi_device",
	.release =	scsi_device_dev_release,
	.groups =	scsi_sdev_attr_groups,
पूर्ण;

व्योम scsi_sysfs_device_initialize(काष्ठा scsi_device *sdev)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा Scsi_Host *shost = sdev->host;
	काष्ठा scsi_target  *starget = sdev->sdev_target;

	device_initialize(&sdev->sdev_gendev);
	sdev->sdev_gendev.bus = &scsi_bus_type;
	sdev->sdev_gendev.type = &scsi_dev_type;
	dev_set_name(&sdev->sdev_gendev, "%d:%d:%d:%llu",
		     sdev->host->host_no, sdev->channel, sdev->id, sdev->lun);

	device_initialize(&sdev->sdev_dev);
	sdev->sdev_dev.parent = get_device(&sdev->sdev_gendev);
	sdev->sdev_dev.class = &sdev_class;
	dev_set_name(&sdev->sdev_dev, "%d:%d:%d:%llu",
		     sdev->host->host_no, sdev->channel, sdev->id, sdev->lun);
	/*
	 * Get a शेष scsi_level from the target (derived from sibling
	 * devices).  This is the best we can करो क्रम guessing how to set
	 * sdev->lun_in_cdb क्रम the initial INQUIRY command.  For LUN 0 the
	 * setting करोesn't matter, because all the bits are zero anyway.
	 * But it करोes matter क्रम higher LUNs.
	 */
	sdev->scsi_level = starget->scsi_level;
	अगर (sdev->scsi_level <= SCSI_2 &&
			sdev->scsi_level != SCSI_UNKNOWN &&
			!shost->no_scsi2_lun_in_cdb)
		sdev->lun_in_cdb = 1;

	transport_setup_device(&sdev->sdev_gendev);
	spin_lock_irqsave(shost->host_lock, flags);
	list_add_tail(&sdev->same_target_siblings, &starget->devices);
	list_add_tail(&sdev->siblings, &shost->__devices);
	spin_unlock_irqrestore(shost->host_lock, flags);
	/*
	 * device can now only be हटाओd via __scsi_हटाओ_device() so hold
	 * the target.  Target will be held in CREATED state until something
	 * beneath it becomes visible (in which हाल it moves to RUNNING)
	 */
	kref_get(&starget->reap_ref);
पूर्ण

पूर्णांक scsi_is_sdev_device(स्थिर काष्ठा device *dev)
अणु
	वापस dev->type == &scsi_dev_type;
पूर्ण
EXPORT_SYMBOL(scsi_is_sdev_device);

/* A blank transport ढाँचा that is used in drivers that करोn't
 * yet implement Transport Attributes */
काष्ठा scsi_transport_ढाँचा blank_transport_ढाँचा = अणु अणु अणु अणुशून्य, पूर्ण, पूर्ण, पूर्ण, पूर्ण;
