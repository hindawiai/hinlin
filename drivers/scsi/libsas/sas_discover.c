<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Serial Attached SCSI (SAS) Discover process
 *
 * Copyright (C) 2005 Adaptec, Inc.  All rights reserved.
 * Copyright (C) 2005 Luben Tuikov <luben_tuikov@adaptec.com>
 */

#समावेश <linux/scatterlist.h>
#समावेश <linux/slab.h>
#समावेश <linux/async.h>
#समावेश <scsi/scsi_host.h>
#समावेश <scsi/scsi_eh.h>
#समावेश "sas_internal.h"

#समावेश <scsi/scsi_transport.h>
#समावेश <scsi/scsi_transport_sas.h>
#समावेश <scsi/sas_ata.h>
#समावेश "../scsi_sas_internal.h"

/* ---------- Basic task processing क्रम discovery purposes ---------- */

व्योम sas_init_dev(काष्ठा करोमुख्य_device *dev)
अणु
	चयन (dev->dev_type) अणु
	हाल SAS_END_DEVICE:
		INIT_LIST_HEAD(&dev->ssp_dev.eh_list_node);
		अवरोध;
	हाल SAS_EDGE_EXPANDER_DEVICE:
	हाल SAS_FANOUT_EXPANDER_DEVICE:
		INIT_LIST_HEAD(&dev->ex_dev.children);
		mutex_init(&dev->ex_dev.cmd_mutex);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

/* ---------- Doमुख्य device discovery ---------- */

/**
 * sas_get_port_device - Discover devices which caused port creation
 * @port: poपूर्णांकer to काष्ठा sas_port of पूर्णांकerest
 *
 * Devices directly attached to a HA port, have no parent.  This is
 * how we know they are (करोमुख्य) "root" devices.  All other devices
 * करो, and should have their "parent" poपूर्णांकer set appropriately as
 * soon as a child device is discovered.
 */
अटल पूर्णांक sas_get_port_device(काष्ठा asd_sas_port *port)
अणु
	काष्ठा asd_sas_phy *phy;
	काष्ठा sas_rphy *rphy;
	काष्ठा करोमुख्य_device *dev;
	पूर्णांक rc = -ENODEV;

	dev = sas_alloc_device();
	अगर (!dev)
		वापस -ENOMEM;

	spin_lock_irq(&port->phy_list_lock);
	अगर (list_empty(&port->phy_list)) अणु
		spin_unlock_irq(&port->phy_list_lock);
		sas_put_device(dev);
		वापस -ENODEV;
	पूर्ण
	phy = container_of(port->phy_list.next, काष्ठा asd_sas_phy, port_phy_el);
	spin_lock(&phy->frame_rcvd_lock);
	स_नकल(dev->frame_rcvd, phy->frame_rcvd, min(माप(dev->frame_rcvd),
					     (माप_प्रकार)phy->frame_rcvd_size));
	spin_unlock(&phy->frame_rcvd_lock);
	spin_unlock_irq(&port->phy_list_lock);

	अगर (dev->frame_rcvd[0] == 0x34 && port->oob_mode == SATA_OOB_MODE) अणु
		काष्ठा dev_to_host_fis *fis =
			(काष्ठा dev_to_host_fis *) dev->frame_rcvd;
		अगर (fis->पूर्णांकerrupt_reason == 1 && fis->lbal == 1 &&
		    fis->byte_count_low == 0x69 && fis->byte_count_high == 0x96
		    && (fis->device & ~0x10) == 0)
			dev->dev_type = SAS_SATA_PM;
		अन्यथा
			dev->dev_type = SAS_SATA_DEV;
		dev->tproto = SAS_PROTOCOL_SATA;
	पूर्ण अन्यथा अगर (port->oob_mode == SAS_OOB_MODE) अणु
		काष्ठा sas_identअगरy_frame *id =
			(काष्ठा sas_identअगरy_frame *) dev->frame_rcvd;
		dev->dev_type = id->dev_type;
		dev->iproto = id->initiator_bits;
		dev->tproto = id->target_bits;
	पूर्ण अन्यथा अणु
		/* If the oob mode is OOB_NOT_CONNECTED, the port is
		 * disconnected due to race with PHY करोwn. We cannot
		 * जारी to discover this port
		 */
		sas_put_device(dev);
		pr_warn("Port %016llx is disconnected when discovering\n",
			SAS_ADDR(port->attached_sas_addr));
		वापस -ENODEV;
	पूर्ण

	sas_init_dev(dev);

	dev->port = port;
	चयन (dev->dev_type) अणु
	हाल SAS_SATA_DEV:
		rc = sas_ata_init(dev);
		अगर (rc) अणु
			rphy = शून्य;
			अवरोध;
		पूर्ण
		fallthrough;
	हाल SAS_END_DEVICE:
		rphy = sas_end_device_alloc(port->port);
		अवरोध;
	हाल SAS_EDGE_EXPANDER_DEVICE:
		rphy = sas_expander_alloc(port->port,
					  SAS_EDGE_EXPANDER_DEVICE);
		अवरोध;
	हाल SAS_FANOUT_EXPANDER_DEVICE:
		rphy = sas_expander_alloc(port->port,
					  SAS_FANOUT_EXPANDER_DEVICE);
		अवरोध;
	शेष:
		pr_warn("ERROR: Unidentified device type %d\n", dev->dev_type);
		rphy = शून्य;
		अवरोध;
	पूर्ण

	अगर (!rphy) अणु
		sas_put_device(dev);
		वापस rc;
	पूर्ण

	rphy->identअगरy.phy_identअगरier = phy->phy->identअगरy.phy_identअगरier;
	स_नकल(dev->sas_addr, port->attached_sas_addr, SAS_ADDR_SIZE);
	sas_fill_in_rphy(dev, rphy);
	sas_hash_addr(dev->hashed_sas_addr, dev->sas_addr);
	port->port_dev = dev;
	dev->linkrate = port->linkrate;
	dev->min_linkrate = port->linkrate;
	dev->max_linkrate = port->linkrate;
	dev->pathways = port->num_phys;
	स_रखो(port->disc.fanout_sas_addr, 0, SAS_ADDR_SIZE);
	स_रखो(port->disc.eeds_a, 0, SAS_ADDR_SIZE);
	स_रखो(port->disc.eeds_b, 0, SAS_ADDR_SIZE);
	port->disc.max_level = 0;
	sas_device_set_phy(dev, port->port);

	dev->rphy = rphy;
	get_device(&dev->rphy->dev);

	अगर (dev_is_sata(dev) || dev->dev_type == SAS_END_DEVICE)
		list_add_tail(&dev->disco_list_node, &port->disco_list);
	अन्यथा अणु
		spin_lock_irq(&port->dev_list_lock);
		list_add_tail(&dev->dev_list_node, &port->dev_list);
		spin_unlock_irq(&port->dev_list_lock);
	पूर्ण

	spin_lock_irq(&port->phy_list_lock);
	list_क्रम_each_entry(phy, &port->phy_list, port_phy_el)
		sas_phy_set_target(phy, dev);
	spin_unlock_irq(&port->phy_list_lock);

	वापस 0;
पूर्ण

/* ---------- Discover and Revalidate ---------- */

पूर्णांक sas_notअगरy_lldd_dev_found(काष्ठा करोमुख्य_device *dev)
अणु
	पूर्णांक res = 0;
	काष्ठा sas_ha_काष्ठा *sas_ha = dev->port->ha;
	काष्ठा Scsi_Host *shost = sas_ha->core.shost;
	काष्ठा sas_पूर्णांकernal *i = to_sas_पूर्णांकernal(shost->transportt);

	अगर (!i->dft->lldd_dev_found)
		वापस 0;

	res = i->dft->lldd_dev_found(dev);
	अगर (res) अणु
		pr_warn("driver on host %s cannot handle device %016llx, error:%d\n",
			dev_name(sas_ha->dev),
			SAS_ADDR(dev->sas_addr), res);
		वापस res;
	पूर्ण
	set_bit(SAS_DEV_FOUND, &dev->state);
	kref_get(&dev->kref);
	वापस 0;
पूर्ण


व्योम sas_notअगरy_lldd_dev_gone(काष्ठा करोमुख्य_device *dev)
अणु
	काष्ठा sas_ha_काष्ठा *sas_ha = dev->port->ha;
	काष्ठा Scsi_Host *shost = sas_ha->core.shost;
	काष्ठा sas_पूर्णांकernal *i = to_sas_पूर्णांकernal(shost->transportt);

	अगर (!i->dft->lldd_dev_gone)
		वापस;

	अगर (test_and_clear_bit(SAS_DEV_FOUND, &dev->state)) अणु
		i->dft->lldd_dev_gone(dev);
		sas_put_device(dev);
	पूर्ण
पूर्ण

अटल व्योम sas_probe_devices(काष्ठा asd_sas_port *port)
अणु
	काष्ठा करोमुख्य_device *dev, *n;

	/* devices must be करोमुख्य members beक्रमe link recovery and probe */
	list_क्रम_each_entry(dev, &port->disco_list, disco_list_node) अणु
		spin_lock_irq(&port->dev_list_lock);
		list_add_tail(&dev->dev_list_node, &port->dev_list);
		spin_unlock_irq(&port->dev_list_lock);
	पूर्ण

	sas_probe_sata(port);

	list_क्रम_each_entry_safe(dev, n, &port->disco_list, disco_list_node) अणु
		पूर्णांक err;

		err = sas_rphy_add(dev->rphy);
		अगर (err)
			sas_fail_probe(dev, __func__, err);
		अन्यथा
			list_del_init(&dev->disco_list_node);
	पूर्ण
पूर्ण

अटल व्योम sas_suspend_devices(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा asd_sas_phy *phy;
	काष्ठा करोमुख्य_device *dev;
	काष्ठा sas_discovery_event *ev = to_sas_discovery_event(work);
	काष्ठा asd_sas_port *port = ev->port;
	काष्ठा Scsi_Host *shost = port->ha->core.shost;
	काष्ठा sas_पूर्णांकernal *si = to_sas_पूर्णांकernal(shost->transportt);

	clear_bit(DISCE_SUSPEND, &port->disc.pending);

	sas_suspend_sata(port);

	/* lldd is मुक्त to क्रमget the करोमुख्य_device across the
	 * suspension, we क्रमce the issue here to keep the reference
	 * counts aligned
	 */
	list_क्रम_each_entry(dev, &port->dev_list, dev_list_node)
		sas_notअगरy_lldd_dev_gone(dev);

	/* we are suspending, so we know events are disabled and
	 * phy_list is not being mutated
	 */
	list_क्रम_each_entry(phy, &port->phy_list, port_phy_el) अणु
		अगर (si->dft->lldd_port_deक्रमmed)
			si->dft->lldd_port_deक्रमmed(phy);
		phy->suspended = 1;
		port->suspended = 1;
	पूर्ण
पूर्ण

अटल व्योम sas_resume_devices(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा sas_discovery_event *ev = to_sas_discovery_event(work);
	काष्ठा asd_sas_port *port = ev->port;

	clear_bit(DISCE_RESUME, &port->disc.pending);

	sas_resume_sata(port);
पूर्ण

/**
 * sas_discover_end_dev - discover an end device (SSP, etc)
 * @dev: poपूर्णांकer to करोमुख्य device of पूर्णांकerest
 *
 * See comment in sas_discover_sata().
 */
पूर्णांक sas_discover_end_dev(काष्ठा करोमुख्य_device *dev)
अणु
	वापस sas_notअगरy_lldd_dev_found(dev);
पूर्ण

/* ---------- Device registration and unregistration ---------- */

व्योम sas_मुक्त_device(काष्ठा kref *kref)
अणु
	काष्ठा करोमुख्य_device *dev = container_of(kref, typeof(*dev), kref);

	put_device(&dev->rphy->dev);
	dev->rphy = शून्य;

	अगर (dev->parent)
		sas_put_device(dev->parent);

	sas_port_put_phy(dev->phy);
	dev->phy = शून्य;

	/* हटाओ the phys and ports, everything अन्यथा should be gone */
	अगर (dev_is_expander(dev->dev_type))
		kमुक्त(dev->ex_dev.ex_phy);

	अगर (dev_is_sata(dev) && dev->sata_dev.ap) अणु
		ata_sas_tport_delete(dev->sata_dev.ap);
		ata_sas_port_destroy(dev->sata_dev.ap);
		ata_host_put(dev->sata_dev.ata_host);
		dev->sata_dev.ata_host = शून्य;
		dev->sata_dev.ap = शून्य;
	पूर्ण

	kमुक्त(dev);
पूर्ण

अटल व्योम sas_unरेजिस्टर_common_dev(काष्ठा asd_sas_port *port, काष्ठा करोमुख्य_device *dev)
अणु
	काष्ठा sas_ha_काष्ठा *ha = port->ha;

	sas_notअगरy_lldd_dev_gone(dev);
	अगर (!dev->parent)
		dev->port->port_dev = शून्य;
	अन्यथा
		list_del_init(&dev->siblings);

	spin_lock_irq(&port->dev_list_lock);
	list_del_init(&dev->dev_list_node);
	अगर (dev_is_sata(dev))
		sas_ata_end_eh(dev->sata_dev.ap);
	spin_unlock_irq(&port->dev_list_lock);

	spin_lock_irq(&ha->lock);
	अगर (dev->dev_type == SAS_END_DEVICE &&
	    !list_empty(&dev->ssp_dev.eh_list_node)) अणु
		list_del_init(&dev->ssp_dev.eh_list_node);
		ha->eh_active--;
	पूर्ण
	spin_unlock_irq(&ha->lock);

	sas_put_device(dev);
पूर्ण

व्योम sas_deकाष्ठा_devices(काष्ठा asd_sas_port *port)
अणु
	काष्ठा करोमुख्य_device *dev, *n;

	list_क्रम_each_entry_safe(dev, n, &port->destroy_list, disco_list_node) अणु
		list_del_init(&dev->disco_list_node);

		sas_हटाओ_children(&dev->rphy->dev);
		sas_rphy_delete(dev->rphy);
		sas_unरेजिस्टर_common_dev(port, dev);
	पूर्ण
पूर्ण

अटल व्योम sas_deकाष्ठा_ports(काष्ठा asd_sas_port *port)
अणु
	काष्ठा sas_port *sas_port, *p;

	list_क्रम_each_entry_safe(sas_port, p, &port->sas_port_del_list, del_list) अणु
		list_del_init(&sas_port->del_list);
		sas_port_delete(sas_port);
	पूर्ण
पूर्ण

व्योम sas_unरेजिस्टर_dev(काष्ठा asd_sas_port *port, काष्ठा करोमुख्य_device *dev)
अणु
	अगर (!test_bit(SAS_DEV_DESTROY, &dev->state) &&
	    !list_empty(&dev->disco_list_node)) अणु
		/* this rphy never saw sas_rphy_add */
		list_del_init(&dev->disco_list_node);
		sas_rphy_मुक्त(dev->rphy);
		sas_unरेजिस्टर_common_dev(port, dev);
		वापस;
	पूर्ण

	अगर (!test_and_set_bit(SAS_DEV_DESTROY, &dev->state)) अणु
		sas_rphy_unlink(dev->rphy);
		list_move_tail(&dev->disco_list_node, &port->destroy_list);
	पूर्ण
पूर्ण

व्योम sas_unरेजिस्टर_करोमुख्य_devices(काष्ठा asd_sas_port *port, पूर्णांक gone)
अणु
	काष्ठा करोमुख्य_device *dev, *n;

	list_क्रम_each_entry_safe_reverse(dev, n, &port->dev_list, dev_list_node) अणु
		अगर (gone)
			set_bit(SAS_DEV_GONE, &dev->state);
		sas_unरेजिस्टर_dev(port, dev);
	पूर्ण

	list_क्रम_each_entry_safe(dev, n, &port->disco_list, disco_list_node)
		sas_unरेजिस्टर_dev(port, dev);

	port->port->rphy = शून्य;

पूर्ण

व्योम sas_device_set_phy(काष्ठा करोमुख्य_device *dev, काष्ठा sas_port *port)
अणु
	काष्ठा sas_ha_काष्ठा *ha;
	काष्ठा sas_phy *new_phy;

	अगर (!dev)
		वापस;

	ha = dev->port->ha;
	new_phy = sas_port_get_phy(port);

	/* pin and record last seen phy */
	spin_lock_irq(&ha->phy_port_lock);
	अगर (new_phy) अणु
		sas_port_put_phy(dev->phy);
		dev->phy = new_phy;
	पूर्ण
	spin_unlock_irq(&ha->phy_port_lock);
पूर्ण

/* ---------- Discovery and Revalidation ---------- */

/**
 * sas_discover_करोमुख्य - discover the करोमुख्य
 * @work: work काष्ठाure embedded in port करोमुख्य device.
 *
 * NOTE: this process _must_ quit (वापस) as soon as any connection
 * errors are encountered.  Connection recovery is करोne अन्यथाwhere.
 * Discover process only पूर्णांकerrogates devices in order to discover the
 * करोमुख्य.
 */
अटल व्योम sas_discover_करोमुख्य(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा करोमुख्य_device *dev;
	पूर्णांक error = 0;
	काष्ठा sas_discovery_event *ev = to_sas_discovery_event(work);
	काष्ठा asd_sas_port *port = ev->port;

	clear_bit(DISCE_DISCOVER_DOMAIN, &port->disc.pending);

	अगर (port->port_dev)
		वापस;

	error = sas_get_port_device(port);
	अगर (error)
		वापस;
	dev = port->port_dev;

	pr_debug("DOING DISCOVERY on port %d, pid:%d\n", port->id,
		 task_pid_nr(current));

	चयन (dev->dev_type) अणु
	हाल SAS_END_DEVICE:
		error = sas_discover_end_dev(dev);
		अवरोध;
	हाल SAS_EDGE_EXPANDER_DEVICE:
	हाल SAS_FANOUT_EXPANDER_DEVICE:
		error = sas_discover_root_expander(dev);
		अवरोध;
	हाल SAS_SATA_DEV:
	हाल SAS_SATA_PM:
#अगर_घोषित CONFIG_SCSI_SAS_ATA
		error = sas_discover_sata(dev);
		अवरोध;
#अन्यथा
		pr_notice("ATA device seen but CONFIG_SCSI_SAS_ATA=N so cannot attach\n");
		/* Fall through */
#पूर्ण_अगर
		/* Fall through - only क्रम the #अन्यथा condition above. */
	शेष:
		error = -ENXIO;
		pr_err("unhandled device %d\n", dev->dev_type);
		अवरोध;
	पूर्ण

	अगर (error) अणु
		sas_rphy_मुक्त(dev->rphy);
		list_del_init(&dev->disco_list_node);
		spin_lock_irq(&port->dev_list_lock);
		list_del_init(&dev->dev_list_node);
		spin_unlock_irq(&port->dev_list_lock);

		sas_put_device(dev);
		port->port_dev = शून्य;
	पूर्ण

	sas_probe_devices(port);

	pr_debug("DONE DISCOVERY on port %d, pid:%d, result:%d\n", port->id,
		 task_pid_nr(current), error);
पूर्ण

अटल व्योम sas_revalidate_करोमुख्य(काष्ठा work_काष्ठा *work)
अणु
	पूर्णांक res = 0;
	काष्ठा sas_discovery_event *ev = to_sas_discovery_event(work);
	काष्ठा asd_sas_port *port = ev->port;
	काष्ठा sas_ha_काष्ठा *ha = port->ha;
	काष्ठा करोमुख्य_device *ddev = port->port_dev;

	/* prevent revalidation from finding sata links in recovery */
	mutex_lock(&ha->disco_mutex);
	अगर (test_bit(SAS_HA_ATA_EH_ACTIVE, &ha->state)) अणु
		pr_debug("REVALIDATION DEFERRED on port %d, pid:%d\n",
			 port->id, task_pid_nr(current));
		जाओ out;
	पूर्ण

	clear_bit(DISCE_REVALIDATE_DOMAIN, &port->disc.pending);

	pr_debug("REVALIDATING DOMAIN on port %d, pid:%d\n", port->id,
		 task_pid_nr(current));

	अगर (ddev && dev_is_expander(ddev->dev_type))
		res = sas_ex_revalidate_करोमुख्य(ddev);

	pr_debug("done REVALIDATING DOMAIN on port %d, pid:%d, res 0x%x\n",
		 port->id, task_pid_nr(current), res);
 out:
	mutex_unlock(&ha->disco_mutex);

	sas_deकाष्ठा_devices(port);
	sas_deकाष्ठा_ports(port);
	sas_probe_devices(port);
पूर्ण

/* ---------- Events ---------- */

अटल व्योम sas_chain_work(काष्ठा sas_ha_काष्ठा *ha, काष्ठा sas_work *sw)
अणु
	/* chained work is not subject to SA_HA_DRAINING or
	 * SAS_HA_REGISTERED, because it is either submitted in the
	 * workqueue, or known to be submitted from a context that is
	 * not racing against draining
	 */
	queue_work(ha->disco_q, &sw->work);
पूर्ण

अटल व्योम sas_chain_event(पूर्णांक event, अचिन्हित दीर्घ *pending,
			    काष्ठा sas_work *sw,
			    काष्ठा sas_ha_काष्ठा *ha)
अणु
	अगर (!test_and_set_bit(event, pending)) अणु
		अचिन्हित दीर्घ flags;

		spin_lock_irqsave(&ha->lock, flags);
		sas_chain_work(ha, sw);
		spin_unlock_irqrestore(&ha->lock, flags);
	पूर्ण
पूर्ण

पूर्णांक sas_discover_event(काष्ठा asd_sas_port *port, क्रमागत discover_event ev)
अणु
	काष्ठा sas_discovery *disc;

	अगर (!port)
		वापस 0;
	disc = &port->disc;

	BUG_ON(ev >= DISC_NUM_EVENTS);

	sas_chain_event(ev, &disc->pending, &disc->disc_work[ev].work, port->ha);

	वापस 0;
पूर्ण

/**
 * sas_init_disc - initialize the discovery काष्ठा in the port
 * @disc: port discovery काष्ठाure
 * @port: poपूर्णांकer to काष्ठा port
 *
 * Called when the ports are being initialized.
 */
व्योम sas_init_disc(काष्ठा sas_discovery *disc, काष्ठा asd_sas_port *port)
अणु
	पूर्णांक i;

	अटल स्थिर work_func_t sas_event_fns[DISC_NUM_EVENTS] = अणु
		[DISCE_DISCOVER_DOMAIN] = sas_discover_करोमुख्य,
		[DISCE_REVALIDATE_DOMAIN] = sas_revalidate_करोमुख्य,
		[DISCE_SUSPEND] = sas_suspend_devices,
		[DISCE_RESUME] = sas_resume_devices,
	पूर्ण;

	disc->pending = 0;
	क्रम (i = 0; i < DISC_NUM_EVENTS; i++) अणु
		INIT_SAS_WORK(&disc->disc_work[i].work, sas_event_fns[i]);
		disc->disc_work[i].port = port;
	पूर्ण
पूर्ण
