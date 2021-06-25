<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Serial Attached SCSI (SAS) Port class
 *
 * Copyright (C) 2005 Adaptec, Inc.  All rights reserved.
 * Copyright (C) 2005 Luben Tuikov <luben_tuikov@adaptec.com>
 */

#समावेश "sas_internal.h"

#समावेश <scsi/scsi_transport.h>
#समावेश <scsi/scsi_transport_sas.h>
#समावेश "../scsi_sas_internal.h"

अटल bool phy_is_wideport_member(काष्ठा asd_sas_port *port, काष्ठा asd_sas_phy *phy)
अणु
	काष्ठा sas_ha_काष्ठा *sas_ha = phy->ha;

	अगर (स_भेद(port->attached_sas_addr, phy->attached_sas_addr,
		   SAS_ADDR_SIZE) != 0 || (sas_ha->strict_wide_ports &&
	     स_भेद(port->sas_addr, phy->sas_addr, SAS_ADDR_SIZE) != 0))
		वापस false;
	वापस true;
पूर्ण

अटल व्योम sas_resume_port(काष्ठा asd_sas_phy *phy)
अणु
	काष्ठा करोमुख्य_device *dev, *n;
	काष्ठा asd_sas_port *port = phy->port;
	काष्ठा sas_ha_काष्ठा *sas_ha = phy->ha;
	काष्ठा sas_पूर्णांकernal *si = to_sas_पूर्णांकernal(sas_ha->core.shost->transportt);

	अगर (si->dft->lldd_port_क्रमmed)
		si->dft->lldd_port_क्रमmed(phy);

	अगर (port->suspended)
		port->suspended = 0;
	अन्यथा अणु
		/* we only need to handle "link returned" actions once */
		वापस;
	पूर्ण

	/* अगर the port came back:
	 * 1/ presume every device came back
	 * 2/ क्रमce the next revalidation to check all expander phys
	 */
	list_क्रम_each_entry_safe(dev, n, &port->dev_list, dev_list_node) अणु
		पूर्णांक i, rc;

		rc = sas_notअगरy_lldd_dev_found(dev);
		अगर (rc) अणु
			sas_unरेजिस्टर_dev(port, dev);
			sas_deकाष्ठा_devices(port);
			जारी;
		पूर्ण

		अगर (dev_is_expander(dev->dev_type)) अणु
			dev->ex_dev.ex_change_count = -1;
			क्रम (i = 0; i < dev->ex_dev.num_phys; i++) अणु
				काष्ठा ex_phy *phy = &dev->ex_dev.ex_phy[i];

				phy->phy_change_count = -1;
			पूर्ण
		पूर्ण
	पूर्ण

	sas_discover_event(port, DISCE_RESUME);
पूर्ण

/**
 * sas_क्रमm_port - add this phy to a port
 * @phy: the phy of पूर्णांकerest
 *
 * This function adds this phy to an existing port, thus creating a wide
 * port, or it creates a port and adds the phy to the port.
 */
अटल व्योम sas_क्रमm_port(काष्ठा asd_sas_phy *phy)
अणु
	पूर्णांक i;
	काष्ठा sas_ha_काष्ठा *sas_ha = phy->ha;
	काष्ठा asd_sas_port *port = phy->port;
	काष्ठा करोमुख्य_device *port_dev;
	काष्ठा sas_पूर्णांकernal *si =
		to_sas_पूर्णांकernal(sas_ha->core.shost->transportt);
	अचिन्हित दीर्घ flags;

	अगर (port) अणु
		अगर (!phy_is_wideport_member(port, phy))
			sas_deक्रमm_port(phy, 0);
		अन्यथा अगर (phy->suspended) अणु
			phy->suspended = 0;
			sas_resume_port(phy);

			/* phy came back, try to cancel the समयout */
			wake_up(&sas_ha->eh_रुको_q);
			वापस;
		पूर्ण अन्यथा अणु
			pr_info("%s: phy%d belongs to port%d already(%d)!\n",
				__func__, phy->id, phy->port->id,
				phy->port->num_phys);
			वापस;
		पूर्ण
	पूर्ण

	/* see अगर the phy should be part of a wide port */
	spin_lock_irqsave(&sas_ha->phy_port_lock, flags);
	क्रम (i = 0; i < sas_ha->num_phys; i++) अणु
		port = sas_ha->sas_port[i];
		spin_lock(&port->phy_list_lock);
		अगर (*(u64 *) port->sas_addr &&
		    phy_is_wideport_member(port, phy) && port->num_phys > 0) अणु
			/* wide port */
			pr_debug("phy%d matched wide port%d\n", phy->id,
				 port->id);
			अवरोध;
		पूर्ण
		spin_unlock(&port->phy_list_lock);
	पूर्ण
	/* The phy करोes not match any existing port, create a new one */
	अगर (i == sas_ha->num_phys) अणु
		क्रम (i = 0; i < sas_ha->num_phys; i++) अणु
			port = sas_ha->sas_port[i];
			spin_lock(&port->phy_list_lock);
			अगर (*(u64 *)port->sas_addr == 0
				&& port->num_phys == 0) अणु
				स_नकल(port->sas_addr, phy->sas_addr,
					SAS_ADDR_SIZE);
				अवरोध;
			पूर्ण
			spin_unlock(&port->phy_list_lock);
		पूर्ण
	पूर्ण

	अगर (i >= sas_ha->num_phys) अणु
		pr_err("%s: couldn't find a free port, bug?\n", __func__);
		spin_unlock_irqrestore(&sas_ha->phy_port_lock, flags);
		वापस;
	पूर्ण

	/* add the phy to the port */
	port_dev = port->port_dev;
	list_add_tail(&phy->port_phy_el, &port->phy_list);
	sas_phy_set_target(phy, port_dev);
	phy->port = port;
	port->num_phys++;
	port->phy_mask |= (1U << phy->id);

	अगर (*(u64 *)port->attached_sas_addr == 0) अणु
		port->class = phy->class;
		स_नकल(port->attached_sas_addr, phy->attached_sas_addr,
		       SAS_ADDR_SIZE);
		port->iproto = phy->iproto;
		port->tproto = phy->tproto;
		port->oob_mode = phy->oob_mode;
		port->linkrate = phy->linkrate;
	पूर्ण अन्यथा
		port->linkrate = max(port->linkrate, phy->linkrate);
	spin_unlock(&port->phy_list_lock);
	spin_unlock_irqrestore(&sas_ha->phy_port_lock, flags);

	अगर (!port->port) अणु
		port->port = sas_port_alloc(phy->phy->dev.parent, port->id);
		BUG_ON(!port->port);
		sas_port_add(port->port);
	पूर्ण
	sas_port_add_phy(port->port, phy->phy);

	pr_debug("%s added to %s, phy_mask:0x%x (%016llx)\n",
		 dev_name(&phy->phy->dev), dev_name(&port->port->dev),
		 port->phy_mask,
		 SAS_ADDR(port->attached_sas_addr));

	अगर (port_dev)
		port_dev->pathways = port->num_phys;

	/* Tell the LLDD about this port क्रमmation. */
	अगर (si->dft->lldd_port_क्रमmed)
		si->dft->lldd_port_क्रमmed(phy);

	sas_discover_event(phy->port, DISCE_DISCOVER_DOMAIN);
	/* Only insert a revalidate event after initial discovery */
	अगर (port_dev && dev_is_expander(port_dev->dev_type)) अणु
		काष्ठा expander_device *ex_dev = &port_dev->ex_dev;

		ex_dev->ex_change_count = -1;
		sas_discover_event(port, DISCE_REVALIDATE_DOMAIN);
	पूर्ण
	flush_workqueue(sas_ha->disco_q);
पूर्ण

/**
 * sas_deक्रमm_port - हटाओ this phy from the port it beदीर्घs to
 * @phy: the phy of पूर्णांकerest
 * @gone: whether or not the PHY is gone
 *
 * This is called when the physical link to the other phy has been
 * lost (on this phy), in Event thपढ़ो context. We cannot delay here.
 */
व्योम sas_deक्रमm_port(काष्ठा asd_sas_phy *phy, पूर्णांक gone)
अणु
	काष्ठा sas_ha_काष्ठा *sas_ha = phy->ha;
	काष्ठा asd_sas_port *port = phy->port;
	काष्ठा sas_पूर्णांकernal *si =
		to_sas_पूर्णांकernal(sas_ha->core.shost->transportt);
	काष्ठा करोमुख्य_device *dev;
	अचिन्हित दीर्घ flags;

	अगर (!port)
		वापस;		  /* करोne by a phy event */

	dev = port->port_dev;
	अगर (dev)
		dev->pathways--;

	अगर (port->num_phys == 1) अणु
		sas_unरेजिस्टर_करोमुख्य_devices(port, gone);
		sas_deकाष्ठा_devices(port);
		sas_port_delete(port->port);
		port->port = शून्य;
	पूर्ण अन्यथा अणु
		sas_port_delete_phy(port->port, phy->phy);
		sas_device_set_phy(dev, port->port);
	पूर्ण

	अगर (si->dft->lldd_port_deक्रमmed)
		si->dft->lldd_port_deक्रमmed(phy);

	spin_lock_irqsave(&sas_ha->phy_port_lock, flags);
	spin_lock(&port->phy_list_lock);

	list_del_init(&phy->port_phy_el);
	sas_phy_set_target(phy, शून्य);
	phy->port = शून्य;
	port->num_phys--;
	port->phy_mask &= ~(1U << phy->id);

	अगर (port->num_phys == 0) अणु
		INIT_LIST_HEAD(&port->phy_list);
		स_रखो(port->sas_addr, 0, SAS_ADDR_SIZE);
		स_रखो(port->attached_sas_addr, 0, SAS_ADDR_SIZE);
		port->class = 0;
		port->iproto = 0;
		port->tproto = 0;
		port->oob_mode = 0;
		port->phy_mask = 0;
	पूर्ण
	spin_unlock(&port->phy_list_lock);
	spin_unlock_irqrestore(&sas_ha->phy_port_lock, flags);

	/* Only insert revalidate event अगर the port still has members */
	अगर (port->port && dev && dev_is_expander(dev->dev_type)) अणु
		काष्ठा expander_device *ex_dev = &dev->ex_dev;

		ex_dev->ex_change_count = -1;
		sas_discover_event(port, DISCE_REVALIDATE_DOMAIN);
	पूर्ण
	flush_workqueue(sas_ha->disco_q);

	वापस;
पूर्ण

/* ---------- SAS port events ---------- */

व्योम sas_porte_bytes_dmaed(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा asd_sas_event *ev = to_asd_sas_event(work);
	काष्ठा asd_sas_phy *phy = ev->phy;

	sas_क्रमm_port(phy);
पूर्ण

व्योम sas_porte_broadcast_rcvd(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा asd_sas_event *ev = to_asd_sas_event(work);
	काष्ठा asd_sas_phy *phy = ev->phy;
	अचिन्हित दीर्घ flags;
	u32 prim;

	spin_lock_irqsave(&phy->sas_prim_lock, flags);
	prim = phy->sas_prim;
	spin_unlock_irqrestore(&phy->sas_prim_lock, flags);

	pr_debug("broadcast received: %d\n", prim);
	sas_discover_event(phy->port, DISCE_REVALIDATE_DOMAIN);

	अगर (phy->port)
		flush_workqueue(phy->port->ha->disco_q);
पूर्ण

व्योम sas_porte_link_reset_err(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा asd_sas_event *ev = to_asd_sas_event(work);
	काष्ठा asd_sas_phy *phy = ev->phy;

	sas_deक्रमm_port(phy, 1);
पूर्ण

व्योम sas_porte_समयr_event(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा asd_sas_event *ev = to_asd_sas_event(work);
	काष्ठा asd_sas_phy *phy = ev->phy;

	sas_deक्रमm_port(phy, 1);
पूर्ण

व्योम sas_porte_hard_reset(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा asd_sas_event *ev = to_asd_sas_event(work);
	काष्ठा asd_sas_phy *phy = ev->phy;

	sas_deक्रमm_port(phy, 1);
पूर्ण

/* ---------- SAS port registration ---------- */

अटल व्योम sas_init_port(काष्ठा asd_sas_port *port,
			  काष्ठा sas_ha_काष्ठा *sas_ha, पूर्णांक i)
अणु
	स_रखो(port, 0, माप(*port));
	port->id = i;
	INIT_LIST_HEAD(&port->dev_list);
	INIT_LIST_HEAD(&port->disco_list);
	INIT_LIST_HEAD(&port->destroy_list);
	INIT_LIST_HEAD(&port->sas_port_del_list);
	spin_lock_init(&port->phy_list_lock);
	INIT_LIST_HEAD(&port->phy_list);
	port->ha = sas_ha;

	spin_lock_init(&port->dev_list_lock);
पूर्ण

पूर्णांक sas_रेजिस्टर_ports(काष्ठा sas_ha_काष्ठा *sas_ha)
अणु
	पूर्णांक i;

	/* initialize the ports and discovery */
	क्रम (i = 0; i < sas_ha->num_phys; i++) अणु
		काष्ठा asd_sas_port *port = sas_ha->sas_port[i];

		sas_init_port(port, sas_ha, i);
		sas_init_disc(&port->disc, port);
	पूर्ण
	वापस 0;
पूर्ण

व्योम sas_unरेजिस्टर_ports(काष्ठा sas_ha_काष्ठा *sas_ha)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < sas_ha->num_phys; i++)
		अगर (sas_ha->sas_phy[i]->port)
			sas_deक्रमm_port(sas_ha->sas_phy[i], 0);

पूर्ण

स्थिर work_func_t sas_port_event_fns[PORT_NUM_EVENTS] = अणु
	[PORTE_BYTES_DMAED] = sas_porte_bytes_dmaed,
	[PORTE_BROADCAST_RCVD] = sas_porte_broadcast_rcvd,
	[PORTE_LINK_RESET_ERR] = sas_porte_link_reset_err,
	[PORTE_TIMER_EVENT] = sas_porte_समयr_event,
	[PORTE_HARD_RESET] = sas_porte_hard_reset,
पूर्ण;
