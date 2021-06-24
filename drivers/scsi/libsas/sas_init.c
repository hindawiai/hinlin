<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Serial Attached SCSI (SAS) Transport Layer initialization
 *
 * Copyright (C) 2005 Adaptec, Inc.  All rights reserved.
 * Copyright (C) 2005 Luben Tuikov <luben_tuikov@adaptec.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/init.h>
#समावेश <linux/device.h>
#समावेश <linux/spinlock.h>
#समावेश <scsi/sas_ata.h>
#समावेश <scsi/scsi_host.h>
#समावेश <scsi/scsi_device.h>
#समावेश <scsi/scsi_transport.h>
#समावेश <scsi/scsi_transport_sas.h>

#समावेश "sas_internal.h"

#समावेश "../scsi_sas_internal.h"

अटल काष्ठा kmem_cache *sas_task_cache;
अटल काष्ठा kmem_cache *sas_event_cache;

काष्ठा sas_task *sas_alloc_task(gfp_t flags)
अणु
	काष्ठा sas_task *task = kmem_cache_zalloc(sas_task_cache, flags);

	अगर (task) अणु
		spin_lock_init(&task->task_state_lock);
		task->task_state_flags = SAS_TASK_STATE_PENDING;
	पूर्ण

	वापस task;
पूर्ण
EXPORT_SYMBOL_GPL(sas_alloc_task);

काष्ठा sas_task *sas_alloc_slow_task(gfp_t flags)
अणु
	काष्ठा sas_task *task = sas_alloc_task(flags);
	काष्ठा sas_task_slow *slow = kदो_स्मृति(माप(*slow), flags);

	अगर (!task || !slow) अणु
		अगर (task)
			kmem_cache_मुक्त(sas_task_cache, task);
		kमुक्त(slow);
		वापस शून्य;
	पूर्ण

	task->slow_task = slow;
	slow->task = task;
	समयr_setup(&slow->समयr, शून्य, 0);
	init_completion(&slow->completion);

	वापस task;
पूर्ण
EXPORT_SYMBOL_GPL(sas_alloc_slow_task);

व्योम sas_मुक्त_task(काष्ठा sas_task *task)
अणु
	अगर (task) अणु
		kमुक्त(task->slow_task);
		kmem_cache_मुक्त(sas_task_cache, task);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(sas_मुक्त_task);

/*------------ SAS addr hash -----------*/
व्योम sas_hash_addr(u8 *hashed, स्थिर u8 *sas_addr)
अणु
	स्थिर u32 poly = 0x00DB2777;
	u32 r = 0;
	पूर्णांक i;

	क्रम (i = 0; i < SAS_ADDR_SIZE; i++) अणु
		पूर्णांक b;

		क्रम (b = (SAS_ADDR_SIZE - 1); b >= 0; b--) अणु
			r <<= 1;
			अगर ((1 << b) & sas_addr[i]) अणु
				अगर (!(r & 0x01000000))
					r ^= poly;
			पूर्ण अन्यथा अगर (r & 0x01000000) अणु
				r ^= poly;
			पूर्ण
		पूर्ण
	पूर्ण

	hashed[0] = (r >> 16) & 0xFF;
	hashed[1] = (r >> 8) & 0xFF;
	hashed[2] = r & 0xFF;
पूर्ण

पूर्णांक sas_रेजिस्टर_ha(काष्ठा sas_ha_काष्ठा *sas_ha)
अणु
	अक्षर name[64];
	पूर्णांक error = 0;

	mutex_init(&sas_ha->disco_mutex);
	spin_lock_init(&sas_ha->phy_port_lock);
	sas_hash_addr(sas_ha->hashed_sas_addr, sas_ha->sas_addr);

	set_bit(SAS_HA_REGISTERED, &sas_ha->state);
	spin_lock_init(&sas_ha->lock);
	mutex_init(&sas_ha->drain_mutex);
	init_रुकोqueue_head(&sas_ha->eh_रुको_q);
	INIT_LIST_HEAD(&sas_ha->defer_q);
	INIT_LIST_HEAD(&sas_ha->eh_dev_q);

	sas_ha->event_thres = SAS_PHY_SHUTDOWN_THRES;

	error = sas_रेजिस्टर_phys(sas_ha);
	अगर (error) अणु
		pr_notice("couldn't register sas phys:%d\n", error);
		वापस error;
	पूर्ण

	error = sas_रेजिस्टर_ports(sas_ha);
	अगर (error) अणु
		pr_notice("couldn't register sas ports:%d\n", error);
		जाओ Unकरो_phys;
	पूर्ण

	error = -ENOMEM;
	snम_लिखो(name, माप(name), "%s_event_q", dev_name(sas_ha->dev));
	sas_ha->event_q = create_singlethपढ़ो_workqueue(name);
	अगर (!sas_ha->event_q)
		जाओ Unकरो_ports;

	snम_लिखो(name, माप(name), "%s_disco_q", dev_name(sas_ha->dev));
	sas_ha->disco_q = create_singlethपढ़ो_workqueue(name);
	अगर (!sas_ha->disco_q)
		जाओ Unकरो_event_q;

	INIT_LIST_HEAD(&sas_ha->eh_करोne_q);
	INIT_LIST_HEAD(&sas_ha->eh_ata_q);

	वापस 0;

Unकरो_event_q:
	destroy_workqueue(sas_ha->event_q);
Unकरो_ports:
	sas_unरेजिस्टर_ports(sas_ha);
Unकरो_phys:

	वापस error;
पूर्ण

अटल व्योम sas_disable_events(काष्ठा sas_ha_काष्ठा *sas_ha)
अणु
	/* Set the state to unरेजिस्टरed to aव्योम further unchained
	 * events to be queued, and flush any in-progress drainers
	 */
	mutex_lock(&sas_ha->drain_mutex);
	spin_lock_irq(&sas_ha->lock);
	clear_bit(SAS_HA_REGISTERED, &sas_ha->state);
	spin_unlock_irq(&sas_ha->lock);
	__sas_drain_work(sas_ha);
	mutex_unlock(&sas_ha->drain_mutex);
पूर्ण

पूर्णांक sas_unरेजिस्टर_ha(काष्ठा sas_ha_काष्ठा *sas_ha)
अणु
	sas_disable_events(sas_ha);
	sas_unरेजिस्टर_ports(sas_ha);

	/* flush unregistration work */
	mutex_lock(&sas_ha->drain_mutex);
	__sas_drain_work(sas_ha);
	mutex_unlock(&sas_ha->drain_mutex);

	destroy_workqueue(sas_ha->disco_q);
	destroy_workqueue(sas_ha->event_q);

	वापस 0;
पूर्ण

अटल पूर्णांक sas_get_linkerrors(काष्ठा sas_phy *phy)
अणु
	अगर (scsi_is_sas_phy_local(phy)) अणु
		काष्ठा Scsi_Host *shost = dev_to_shost(phy->dev.parent);
		काष्ठा sas_ha_काष्ठा *sas_ha = SHOST_TO_SAS_HA(shost);
		काष्ठा asd_sas_phy *asd_phy = sas_ha->sas_phy[phy->number];
		काष्ठा sas_पूर्णांकernal *i =
			to_sas_पूर्णांकernal(sas_ha->core.shost->transportt);

		वापस i->dft->lldd_control_phy(asd_phy, PHY_FUNC_GET_EVENTS, शून्य);
	पूर्ण

	वापस sas_smp_get_phy_events(phy);
पूर्ण

पूर्णांक sas_try_ata_reset(काष्ठा asd_sas_phy *asd_phy)
अणु
	काष्ठा करोमुख्य_device *dev = शून्य;

	/* try to route user requested link resets through libata */
	अगर (asd_phy->port)
		dev = asd_phy->port->port_dev;

	/* validate that dev has been probed */
	अगर (dev)
		dev = sas_find_dev_by_rphy(dev->rphy);

	अगर (dev && dev_is_sata(dev)) अणु
		sas_ata_schedule_reset(dev);
		sas_ata_रुको_eh(dev);
		वापस 0;
	पूर्ण

	वापस -ENODEV;
पूर्ण

/*
 * transport_sas_phy_reset - reset a phy and permit libata to manage the link
 *
 * phy reset request via sysfs in host workqueue context so we know we
 * can block on eh and safely traverse the करोमुख्य_device topology
 */
अटल पूर्णांक transport_sas_phy_reset(काष्ठा sas_phy *phy, पूर्णांक hard_reset)
अणु
	क्रमागत phy_func reset_type;

	अगर (hard_reset)
		reset_type = PHY_FUNC_HARD_RESET;
	अन्यथा
		reset_type = PHY_FUNC_LINK_RESET;

	अगर (scsi_is_sas_phy_local(phy)) अणु
		काष्ठा Scsi_Host *shost = dev_to_shost(phy->dev.parent);
		काष्ठा sas_ha_काष्ठा *sas_ha = SHOST_TO_SAS_HA(shost);
		काष्ठा asd_sas_phy *asd_phy = sas_ha->sas_phy[phy->number];
		काष्ठा sas_पूर्णांकernal *i =
			to_sas_पूर्णांकernal(sas_ha->core.shost->transportt);

		अगर (!hard_reset && sas_try_ata_reset(asd_phy) == 0)
			वापस 0;
		वापस i->dft->lldd_control_phy(asd_phy, reset_type, शून्य);
	पूर्ण अन्यथा अणु
		काष्ठा sas_rphy *rphy = dev_to_rphy(phy->dev.parent);
		काष्ठा करोमुख्य_device *ddev = sas_find_dev_by_rphy(rphy);
		काष्ठा करोमुख्य_device *ata_dev = sas_ex_to_ata(ddev, phy->number);

		अगर (ata_dev && !hard_reset) अणु
			sas_ata_schedule_reset(ata_dev);
			sas_ata_रुको_eh(ata_dev);
			वापस 0;
		पूर्ण अन्यथा
			वापस sas_smp_phy_control(ddev, phy->number, reset_type, शून्य);
	पूर्ण
पूर्ण

अटल पूर्णांक sas_phy_enable(काष्ठा sas_phy *phy, पूर्णांक enable)
अणु
	पूर्णांक ret;
	क्रमागत phy_func cmd;

	अगर (enable)
		cmd = PHY_FUNC_LINK_RESET;
	अन्यथा
		cmd = PHY_FUNC_DISABLE;

	अगर (scsi_is_sas_phy_local(phy)) अणु
		काष्ठा Scsi_Host *shost = dev_to_shost(phy->dev.parent);
		काष्ठा sas_ha_काष्ठा *sas_ha = SHOST_TO_SAS_HA(shost);
		काष्ठा asd_sas_phy *asd_phy = sas_ha->sas_phy[phy->number];
		काष्ठा sas_पूर्णांकernal *i =
			to_sas_पूर्णांकernal(sas_ha->core.shost->transportt);

		अगर (enable)
			ret = transport_sas_phy_reset(phy, 0);
		अन्यथा
			ret = i->dft->lldd_control_phy(asd_phy, cmd, शून्य);
	पूर्ण अन्यथा अणु
		काष्ठा sas_rphy *rphy = dev_to_rphy(phy->dev.parent);
		काष्ठा करोमुख्य_device *ddev = sas_find_dev_by_rphy(rphy);

		अगर (enable)
			ret = transport_sas_phy_reset(phy, 0);
		अन्यथा
			ret = sas_smp_phy_control(ddev, phy->number, cmd, शून्य);
	पूर्ण
	वापस ret;
पूर्ण

पूर्णांक sas_phy_reset(काष्ठा sas_phy *phy, पूर्णांक hard_reset)
अणु
	पूर्णांक ret;
	क्रमागत phy_func reset_type;

	अगर (!phy->enabled)
		वापस -ENODEV;

	अगर (hard_reset)
		reset_type = PHY_FUNC_HARD_RESET;
	अन्यथा
		reset_type = PHY_FUNC_LINK_RESET;

	अगर (scsi_is_sas_phy_local(phy)) अणु
		काष्ठा Scsi_Host *shost = dev_to_shost(phy->dev.parent);
		काष्ठा sas_ha_काष्ठा *sas_ha = SHOST_TO_SAS_HA(shost);
		काष्ठा asd_sas_phy *asd_phy = sas_ha->sas_phy[phy->number];
		काष्ठा sas_पूर्णांकernal *i =
			to_sas_पूर्णांकernal(sas_ha->core.shost->transportt);

		ret = i->dft->lldd_control_phy(asd_phy, reset_type, शून्य);
	पूर्ण अन्यथा अणु
		काष्ठा sas_rphy *rphy = dev_to_rphy(phy->dev.parent);
		काष्ठा करोमुख्य_device *ddev = sas_find_dev_by_rphy(rphy);
		ret = sas_smp_phy_control(ddev, phy->number, reset_type, शून्य);
	पूर्ण
	वापस ret;
पूर्ण

पूर्णांक sas_set_phy_speed(काष्ठा sas_phy *phy,
		      काष्ठा sas_phy_linkrates *rates)
अणु
	पूर्णांक ret;

	अगर ((rates->minimum_linkrate &&
	     rates->minimum_linkrate > phy->maximum_linkrate) ||
	    (rates->maximum_linkrate &&
	     rates->maximum_linkrate < phy->minimum_linkrate))
		वापस -EINVAL;

	अगर (rates->minimum_linkrate &&
	    rates->minimum_linkrate < phy->minimum_linkrate_hw)
		rates->minimum_linkrate = phy->minimum_linkrate_hw;

	अगर (rates->maximum_linkrate &&
	    rates->maximum_linkrate > phy->maximum_linkrate_hw)
		rates->maximum_linkrate = phy->maximum_linkrate_hw;

	अगर (scsi_is_sas_phy_local(phy)) अणु
		काष्ठा Scsi_Host *shost = dev_to_shost(phy->dev.parent);
		काष्ठा sas_ha_काष्ठा *sas_ha = SHOST_TO_SAS_HA(shost);
		काष्ठा asd_sas_phy *asd_phy = sas_ha->sas_phy[phy->number];
		काष्ठा sas_पूर्णांकernal *i =
			to_sas_पूर्णांकernal(sas_ha->core.shost->transportt);

		ret = i->dft->lldd_control_phy(asd_phy, PHY_FUNC_SET_LINK_RATE,
					       rates);
	पूर्ण अन्यथा अणु
		काष्ठा sas_rphy *rphy = dev_to_rphy(phy->dev.parent);
		काष्ठा करोमुख्य_device *ddev = sas_find_dev_by_rphy(rphy);
		ret = sas_smp_phy_control(ddev, phy->number,
					  PHY_FUNC_LINK_RESET, rates);

	पूर्ण

	वापस ret;
पूर्ण

व्योम sas_prep_resume_ha(काष्ठा sas_ha_काष्ठा *ha)
अणु
	पूर्णांक i;

	set_bit(SAS_HA_REGISTERED, &ha->state);

	/* clear out any stale link events/data from the suspension path */
	क्रम (i = 0; i < ha->num_phys; i++) अणु
		काष्ठा asd_sas_phy *phy = ha->sas_phy[i];

		स_रखो(phy->attached_sas_addr, 0, SAS_ADDR_SIZE);
		phy->frame_rcvd_size = 0;
	पूर्ण
पूर्ण
EXPORT_SYMBOL(sas_prep_resume_ha);

अटल पूर्णांक phys_suspended(काष्ठा sas_ha_काष्ठा *ha)
अणु
	पूर्णांक i, rc = 0;

	क्रम (i = 0; i < ha->num_phys; i++) अणु
		काष्ठा asd_sas_phy *phy = ha->sas_phy[i];

		अगर (phy->suspended)
			rc++;
	पूर्ण

	वापस rc;
पूर्ण

व्योम sas_resume_ha(काष्ठा sas_ha_काष्ठा *ha)
अणु
	स्थिर अचिन्हित दीर्घ पंचांगo = msecs_to_jअगरfies(25000);
	पूर्णांक i;

	/* deक्रमm ports on phys that did not resume
	 * at this poपूर्णांक we may be racing the phy coming back (as posted
	 * by the lldd).  So we post the event and once we are in the
	 * libsas context check that the phy reमुख्यs suspended beक्रमe
	 * tearing it करोwn.
	 */
	i = phys_suspended(ha);
	अगर (i)
		dev_info(ha->dev, "waiting up to 25 seconds for %d phy%s to resume\n",
			 i, i > 1 ? "s" : "");
	रुको_event_समयout(ha->eh_रुको_q, phys_suspended(ha) == 0, पंचांगo);
	क्रम (i = 0; i < ha->num_phys; i++) अणु
		काष्ठा asd_sas_phy *phy = ha->sas_phy[i];

		अगर (phy->suspended) अणु
			dev_warn(&phy->phy->dev, "resume timeout\n");
			sas_notअगरy_phy_event(phy, PHYE_RESUME_TIMEOUT,
					     GFP_KERNEL);
		पूर्ण
	पूर्ण

	/* all phys are back up or समयd out, turn on i/o so we can
	 * flush out disks that did not वापस
	 */
	scsi_unblock_requests(ha->core.shost);
	sas_drain_work(ha);
पूर्ण
EXPORT_SYMBOL(sas_resume_ha);

व्योम sas_suspend_ha(काष्ठा sas_ha_काष्ठा *ha)
अणु
	पूर्णांक i;

	sas_disable_events(ha);
	scsi_block_requests(ha->core.shost);
	क्रम (i = 0; i < ha->num_phys; i++) अणु
		काष्ठा asd_sas_port *port = ha->sas_port[i];

		sas_discover_event(port, DISCE_SUSPEND);
	पूर्ण

	/* flush suspend events जबतक unरेजिस्टरed */
	mutex_lock(&ha->drain_mutex);
	__sas_drain_work(ha);
	mutex_unlock(&ha->drain_mutex);
पूर्ण
EXPORT_SYMBOL(sas_suspend_ha);

अटल व्योम sas_phy_release(काष्ठा sas_phy *phy)
अणु
	kमुक्त(phy->hostdata);
	phy->hostdata = शून्य;
पूर्ण

अटल व्योम phy_reset_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा sas_phy_data *d = container_of(work, typeof(*d), reset_work.work);

	d->reset_result = transport_sas_phy_reset(d->phy, d->hard_reset);
पूर्ण

अटल व्योम phy_enable_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा sas_phy_data *d = container_of(work, typeof(*d), enable_work.work);

	d->enable_result = sas_phy_enable(d->phy, d->enable);
पूर्ण

अटल पूर्णांक sas_phy_setup(काष्ठा sas_phy *phy)
अणु
	काष्ठा sas_phy_data *d = kzalloc(माप(*d), GFP_KERNEL);

	अगर (!d)
		वापस -ENOMEM;

	mutex_init(&d->event_lock);
	INIT_SAS_WORK(&d->reset_work, phy_reset_work);
	INIT_SAS_WORK(&d->enable_work, phy_enable_work);
	d->phy = phy;
	phy->hostdata = d;

	वापस 0;
पूर्ण

अटल पूर्णांक queue_phy_reset(काष्ठा sas_phy *phy, पूर्णांक hard_reset)
अणु
	काष्ठा Scsi_Host *shost = dev_to_shost(phy->dev.parent);
	काष्ठा sas_ha_काष्ठा *ha = SHOST_TO_SAS_HA(shost);
	काष्ठा sas_phy_data *d = phy->hostdata;
	पूर्णांक rc;

	अगर (!d)
		वापस -ENOMEM;

	/* libsas workqueue coordinates ata-eh reset with discovery */
	mutex_lock(&d->event_lock);
	d->reset_result = 0;
	d->hard_reset = hard_reset;

	spin_lock_irq(&ha->lock);
	sas_queue_work(ha, &d->reset_work);
	spin_unlock_irq(&ha->lock);

	rc = sas_drain_work(ha);
	अगर (rc == 0)
		rc = d->reset_result;
	mutex_unlock(&d->event_lock);

	वापस rc;
पूर्ण

अटल पूर्णांक queue_phy_enable(काष्ठा sas_phy *phy, पूर्णांक enable)
अणु
	काष्ठा Scsi_Host *shost = dev_to_shost(phy->dev.parent);
	काष्ठा sas_ha_काष्ठा *ha = SHOST_TO_SAS_HA(shost);
	काष्ठा sas_phy_data *d = phy->hostdata;
	पूर्णांक rc;

	अगर (!d)
		वापस -ENOMEM;

	/* libsas workqueue coordinates ata-eh reset with discovery */
	mutex_lock(&d->event_lock);
	d->enable_result = 0;
	d->enable = enable;

	spin_lock_irq(&ha->lock);
	sas_queue_work(ha, &d->enable_work);
	spin_unlock_irq(&ha->lock);

	rc = sas_drain_work(ha);
	अगर (rc == 0)
		rc = d->enable_result;
	mutex_unlock(&d->event_lock);

	वापस rc;
पूर्ण

अटल काष्ठा sas_function_ढाँचा sft = अणु
	.phy_enable = queue_phy_enable,
	.phy_reset = queue_phy_reset,
	.phy_setup = sas_phy_setup,
	.phy_release = sas_phy_release,
	.set_phy_speed = sas_set_phy_speed,
	.get_linkerrors = sas_get_linkerrors,
	.smp_handler = sas_smp_handler,
पूर्ण;

अटल अंतरभूत sमाप_प्रकार phy_event_threshold_show(काष्ठा device *dev,
			काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा Scsi_Host *shost = class_to_shost(dev);
	काष्ठा sas_ha_काष्ठा *sha = SHOST_TO_SAS_HA(shost);

	वापस scnम_लिखो(buf, PAGE_SIZE, "%u\n", sha->event_thres);
पूर्ण

अटल अंतरभूत sमाप_प्रकार phy_event_threshold_store(काष्ठा device *dev,
			काष्ठा device_attribute *attr,
			स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा Scsi_Host *shost = class_to_shost(dev);
	काष्ठा sas_ha_काष्ठा *sha = SHOST_TO_SAS_HA(shost);

	sha->event_thres = simple_म_से_दीर्घ(buf, शून्य, 10);

	/* threshold cannot be set too small */
	अगर (sha->event_thres < 32)
		sha->event_thres = 32;

	वापस count;
पूर्ण

DEVICE_ATTR(phy_event_threshold,
	S_IRUGO|S_IWUSR,
	phy_event_threshold_show,
	phy_event_threshold_store);
EXPORT_SYMBOL_GPL(dev_attr_phy_event_threshold);

काष्ठा scsi_transport_ढाँचा *
sas_करोमुख्य_attach_transport(काष्ठा sas_करोमुख्य_function_ढाँचा *dft)
अणु
	काष्ठा scsi_transport_ढाँचा *stt = sas_attach_transport(&sft);
	काष्ठा sas_पूर्णांकernal *i;

	अगर (!stt)
		वापस stt;

	i = to_sas_पूर्णांकernal(stt);
	i->dft = dft;
	stt->create_work_queue = 1;
	stt->eh_strategy_handler = sas_scsi_recover_host;

	वापस stt;
पूर्ण
EXPORT_SYMBOL_GPL(sas_करोमुख्य_attach_transport);

काष्ठा asd_sas_event *sas_alloc_event(काष्ठा asd_sas_phy *phy,
				      gfp_t gfp_flags)
अणु
	काष्ठा asd_sas_event *event;
	काष्ठा sas_ha_काष्ठा *sas_ha = phy->ha;
	काष्ठा sas_पूर्णांकernal *i =
		to_sas_पूर्णांकernal(sas_ha->core.shost->transportt);

	event = kmem_cache_zalloc(sas_event_cache, gfp_flags);
	अगर (!event)
		वापस शून्य;

	atomic_inc(&phy->event_nr);

	अगर (atomic_पढ़ो(&phy->event_nr) > phy->ha->event_thres) अणु
		अगर (i->dft->lldd_control_phy) अणु
			अगर (cmpxchg(&phy->in_shutकरोwn, 0, 1) == 0) अणु
				pr_notice("The phy%d bursting events, shut it down.\n",
					  phy->id);
				sas_notअगरy_phy_event(phy, PHYE_SHUTDOWN,
						     gfp_flags);
			पूर्ण
		पूर्ण अन्यथा अणु
			/* Do not support PHY control, stop allocating events */
			WARN_ONCE(1, "PHY control not supported.\n");
			kmem_cache_मुक्त(sas_event_cache, event);
			atomic_dec(&phy->event_nr);
			event = शून्य;
		पूर्ण
	पूर्ण

	वापस event;
पूर्ण

व्योम sas_मुक्त_event(काष्ठा asd_sas_event *event)
अणु
	काष्ठा asd_sas_phy *phy = event->phy;

	kmem_cache_मुक्त(sas_event_cache, event);
	atomic_dec(&phy->event_nr);
पूर्ण

/* ---------- SAS Class रेजिस्टर/unरेजिस्टर ---------- */

अटल पूर्णांक __init sas_class_init(व्योम)
अणु
	sas_task_cache = KMEM_CACHE(sas_task, SLAB_HWCACHE_ALIGN);
	अगर (!sas_task_cache)
		जाओ out;

	sas_event_cache = KMEM_CACHE(asd_sas_event, SLAB_HWCACHE_ALIGN);
	अगर (!sas_event_cache)
		जाओ मुक्त_task_kmem;

	वापस 0;
मुक्त_task_kmem:
	kmem_cache_destroy(sas_task_cache);
out:
	वापस -ENOMEM;
पूर्ण

अटल व्योम __निकास sas_class_निकास(व्योम)
अणु
	kmem_cache_destroy(sas_task_cache);
	kmem_cache_destroy(sas_event_cache);
पूर्ण

MODULE_AUTHOR("Luben Tuikov <luben_tuikov@adaptec.com>");
MODULE_DESCRIPTION("SAS Transport Layer");
MODULE_LICENSE("GPL v2");

module_init(sas_class_init);
module_निकास(sas_class_निकास);

EXPORT_SYMBOL_GPL(sas_रेजिस्टर_ha);
EXPORT_SYMBOL_GPL(sas_unरेजिस्टर_ha);
