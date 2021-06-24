<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Serial Attached SCSI (SAS) Event processing
 *
 * Copyright (C) 2005 Adaptec, Inc.  All rights reserved.
 * Copyright (C) 2005 Luben Tuikov <luben_tuikov@adaptec.com>
 */

#समावेश <linux/export.h>
#समावेश <scsi/scsi_host.h>
#समावेश "sas_internal.h"

पूर्णांक sas_queue_work(काष्ठा sas_ha_काष्ठा *ha, काष्ठा sas_work *sw)
अणु
	/* it's added to the defer_q when draining so वापस succeed */
	पूर्णांक rc = 1;

	अगर (!test_bit(SAS_HA_REGISTERED, &ha->state))
		वापस 0;

	अगर (test_bit(SAS_HA_DRAINING, &ha->state)) अणु
		/* add it to the defer list, अगर not alपढ़ोy pending */
		अगर (list_empty(&sw->drain_node))
			list_add_tail(&sw->drain_node, &ha->defer_q);
	पूर्ण अन्यथा
		rc = queue_work(ha->event_q, &sw->work);

	वापस rc;
पूर्ण

अटल पूर्णांक sas_queue_event(पूर्णांक event, काष्ठा sas_work *work,
			    काष्ठा sas_ha_काष्ठा *ha)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक rc;

	spin_lock_irqsave(&ha->lock, flags);
	rc = sas_queue_work(ha, work);
	spin_unlock_irqrestore(&ha->lock, flags);

	वापस rc;
पूर्ण


व्योम __sas_drain_work(काष्ठा sas_ha_काष्ठा *ha)
अणु
	काष्ठा sas_work *sw, *_sw;
	पूर्णांक ret;

	set_bit(SAS_HA_DRAINING, &ha->state);
	/* flush submitters */
	spin_lock_irq(&ha->lock);
	spin_unlock_irq(&ha->lock);

	drain_workqueue(ha->event_q);
	drain_workqueue(ha->disco_q);

	spin_lock_irq(&ha->lock);
	clear_bit(SAS_HA_DRAINING, &ha->state);
	list_क्रम_each_entry_safe(sw, _sw, &ha->defer_q, drain_node) अणु
		list_del_init(&sw->drain_node);
		ret = sas_queue_work(ha, sw);
		अगर (ret != 1)
			sas_मुक्त_event(to_asd_sas_event(&sw->work));

	पूर्ण
	spin_unlock_irq(&ha->lock);
पूर्ण

पूर्णांक sas_drain_work(काष्ठा sas_ha_काष्ठा *ha)
अणु
	पूर्णांक err;

	err = mutex_lock_पूर्णांकerruptible(&ha->drain_mutex);
	अगर (err)
		वापस err;
	अगर (test_bit(SAS_HA_REGISTERED, &ha->state))
		__sas_drain_work(ha);
	mutex_unlock(&ha->drain_mutex);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(sas_drain_work);

व्योम sas_disable_revalidation(काष्ठा sas_ha_काष्ठा *ha)
अणु
	mutex_lock(&ha->disco_mutex);
	set_bit(SAS_HA_ATA_EH_ACTIVE, &ha->state);
	mutex_unlock(&ha->disco_mutex);
पूर्ण

व्योम sas_enable_revalidation(काष्ठा sas_ha_काष्ठा *ha)
अणु
	पूर्णांक i;

	mutex_lock(&ha->disco_mutex);
	clear_bit(SAS_HA_ATA_EH_ACTIVE, &ha->state);
	क्रम (i = 0; i < ha->num_phys; i++) अणु
		काष्ठा asd_sas_port *port = ha->sas_port[i];
		स्थिर पूर्णांक ev = DISCE_REVALIDATE_DOMAIN;
		काष्ठा sas_discovery *d = &port->disc;
		काष्ठा asd_sas_phy *sas_phy;

		अगर (!test_and_clear_bit(ev, &d->pending))
			जारी;

		अगर (list_empty(&port->phy_list))
			जारी;

		sas_phy = container_of(port->phy_list.next, काष्ठा asd_sas_phy,
				port_phy_el);
		sas_notअगरy_port_event(sas_phy,
				PORTE_BROADCAST_RCVD, GFP_KERNEL);
	पूर्ण
	mutex_unlock(&ha->disco_mutex);
पूर्ण


अटल व्योम sas_port_event_worker(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा asd_sas_event *ev = to_asd_sas_event(work);

	sas_port_event_fns[ev->event](work);
	sas_मुक्त_event(ev);
पूर्ण

अटल व्योम sas_phy_event_worker(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा asd_sas_event *ev = to_asd_sas_event(work);

	sas_phy_event_fns[ev->event](work);
	sas_मुक्त_event(ev);
पूर्ण

पूर्णांक sas_notअगरy_port_event(काष्ठा asd_sas_phy *phy, क्रमागत port_event event,
			  gfp_t gfp_flags)
अणु
	काष्ठा sas_ha_काष्ठा *ha = phy->ha;
	काष्ठा asd_sas_event *ev;
	पूर्णांक ret;

	BUG_ON(event >= PORT_NUM_EVENTS);

	ev = sas_alloc_event(phy, gfp_flags);
	अगर (!ev)
		वापस -ENOMEM;

	INIT_SAS_EVENT(ev, sas_port_event_worker, phy, event);

	ret = sas_queue_event(event, &ev->work, ha);
	अगर (ret != 1)
		sas_मुक्त_event(ev);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(sas_notअगरy_port_event);

पूर्णांक sas_notअगरy_phy_event(काष्ठा asd_sas_phy *phy, क्रमागत phy_event event,
			 gfp_t gfp_flags)
अणु
	काष्ठा sas_ha_काष्ठा *ha = phy->ha;
	काष्ठा asd_sas_event *ev;
	पूर्णांक ret;

	BUG_ON(event >= PHY_NUM_EVENTS);

	ev = sas_alloc_event(phy, gfp_flags);
	अगर (!ev)
		वापस -ENOMEM;

	INIT_SAS_EVENT(ev, sas_phy_event_worker, phy, event);

	ret = sas_queue_event(event, &ev->work, ha);
	अगर (ret != 1)
		sas_मुक्त_event(ev);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(sas_notअगरy_phy_event);
