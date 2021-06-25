<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Serial Attached SCSI (SAS) class पूर्णांकernal header file
 *
 * Copyright (C) 2005 Adaptec, Inc.  All rights reserved.
 * Copyright (C) 2005 Luben Tuikov <luben_tuikov@adaptec.com>
 */

#अगर_अघोषित _SAS_INTERNAL_H_
#घोषणा _SAS_INTERNAL_H_

#समावेश <scsi/scsi.h>
#समावेश <scsi/scsi_host.h>
#समावेश <scsi/scsi_transport_sas.h>
#समावेश <scsi/libsas.h>
#समावेश <scsi/sas_ata.h>

#अगर_घोषित pr_fmt
#अघोषित pr_fmt
#पूर्ण_अगर

#घोषणा SAS_FMT "sas: "

#घोषणा pr_fmt(fmt) SAS_FMT fmt

#घोषणा TO_SAS_TASK(_scsi_cmd)  ((व्योम *)(_scsi_cmd)->host_scribble)
#घोषणा ASSIGN_SAS_TASK(_sc, _t) करो अणु (_sc)->host_scribble = (व्योम *) _t; पूर्ण जबतक (0)

काष्ठा sas_phy_data अणु
	/* let reset be perक्रमmed in sas_queue_work() context */
	काष्ठा sas_phy *phy;
	काष्ठा mutex event_lock;
	पूर्णांक hard_reset;
	पूर्णांक reset_result;
	काष्ठा sas_work reset_work;
	पूर्णांक enable;
	पूर्णांक enable_result;
	काष्ठा sas_work enable_work;
पूर्ण;

व्योम sas_scsi_recover_host(काष्ठा Scsi_Host *shost);

पूर्णांक sas_show_class(क्रमागत sas_class class, अक्षर *buf);
पूर्णांक sas_show_proto(क्रमागत sas_protocol proto, अक्षर *buf);
पूर्णांक sas_show_linkrate(क्रमागत sas_linkrate linkrate, अक्षर *buf);
पूर्णांक sas_show_oob_mode(क्रमागत sas_oob_mode oob_mode, अक्षर *buf);

पूर्णांक  sas_रेजिस्टर_phys(काष्ठा sas_ha_काष्ठा *sas_ha);
व्योम sas_unरेजिस्टर_phys(काष्ठा sas_ha_काष्ठा *sas_ha);

काष्ठा asd_sas_event *sas_alloc_event(काष्ठा asd_sas_phy *phy, gfp_t gfp_flags);
व्योम sas_मुक्त_event(काष्ठा asd_sas_event *event);

पूर्णांक  sas_रेजिस्टर_ports(काष्ठा sas_ha_काष्ठा *sas_ha);
व्योम sas_unरेजिस्टर_ports(काष्ठा sas_ha_काष्ठा *sas_ha);

व्योम sas_disable_revalidation(काष्ठा sas_ha_काष्ठा *ha);
व्योम sas_enable_revalidation(काष्ठा sas_ha_काष्ठा *ha);
व्योम __sas_drain_work(काष्ठा sas_ha_काष्ठा *ha);

व्योम sas_deक्रमm_port(काष्ठा asd_sas_phy *phy, पूर्णांक gone);

व्योम sas_porte_bytes_dmaed(काष्ठा work_काष्ठा *work);
व्योम sas_porte_broadcast_rcvd(काष्ठा work_काष्ठा *work);
व्योम sas_porte_link_reset_err(काष्ठा work_काष्ठा *work);
व्योम sas_porte_समयr_event(काष्ठा work_काष्ठा *work);
व्योम sas_porte_hard_reset(काष्ठा work_काष्ठा *work);
पूर्णांक sas_queue_work(काष्ठा sas_ha_काष्ठा *ha, काष्ठा sas_work *sw);

पूर्णांक sas_notअगरy_lldd_dev_found(काष्ठा करोमुख्य_device *);
व्योम sas_notअगरy_lldd_dev_gone(काष्ठा करोमुख्य_device *);

व्योम sas_smp_handler(काष्ठा bsg_job *job, काष्ठा Scsi_Host *shost,
		काष्ठा sas_rphy *rphy);
पूर्णांक sas_smp_phy_control(काष्ठा करोमुख्य_device *dev, पूर्णांक phy_id,
			क्रमागत phy_func phy_func, काष्ठा sas_phy_linkrates *);
पूर्णांक sas_smp_get_phy_events(काष्ठा sas_phy *phy);

पूर्णांक sas_notअगरy_phy_event(काष्ठा asd_sas_phy *phy, क्रमागत phy_event event,
			 gfp_t flags);
व्योम sas_device_set_phy(काष्ठा करोमुख्य_device *dev, काष्ठा sas_port *port);
काष्ठा करोमुख्य_device *sas_find_dev_by_rphy(काष्ठा sas_rphy *rphy);
काष्ठा करोमुख्य_device *sas_ex_to_ata(काष्ठा करोमुख्य_device *ex_dev, पूर्णांक phy_id);
पूर्णांक sas_ex_phy_discover(काष्ठा करोमुख्य_device *dev, पूर्णांक single);
पूर्णांक sas_get_report_phy_sata(काष्ठा करोमुख्य_device *dev, पूर्णांक phy_id,
			    काष्ठा smp_resp *rps_resp);
पूर्णांक sas_try_ata_reset(काष्ठा asd_sas_phy *phy);
व्योम sas_hae_reset(काष्ठा work_काष्ठा *work);

व्योम sas_मुक्त_device(काष्ठा kref *kref);
व्योम sas_deकाष्ठा_devices(काष्ठा asd_sas_port *port);

बाह्य स्थिर work_func_t sas_phy_event_fns[PHY_NUM_EVENTS];
बाह्य स्थिर work_func_t sas_port_event_fns[PORT_NUM_EVENTS];

#अगर_घोषित CONFIG_SCSI_SAS_HOST_SMP
बाह्य व्योम sas_smp_host_handler(काष्ठा bsg_job *job, काष्ठा Scsi_Host *shost);
#अन्यथा
अटल अंतरभूत व्योम sas_smp_host_handler(काष्ठा bsg_job *job,
		काष्ठा Scsi_Host *shost)
अणु
	shost_prपूर्णांकk(KERN_ERR, shost,
		"Cannot send SMP to a sas host (not enabled in CONFIG)\n");
	bsg_job_करोne(job, -EINVAL, 0);
पूर्ण
#पूर्ण_अगर

अटल अंतरभूत व्योम sas_fail_probe(काष्ठा करोमुख्य_device *dev, स्थिर अक्षर *func, पूर्णांक err)
अणु
	pr_warn("%s: for %s device %016llx returned %d\n",
		func, dev->parent ? "exp-attached" :
		"direct-attached",
		SAS_ADDR(dev->sas_addr), err);
	sas_unरेजिस्टर_dev(dev->port, dev);
पूर्ण

अटल अंतरभूत व्योम sas_fill_in_rphy(काष्ठा करोमुख्य_device *dev,
				    काष्ठा sas_rphy *rphy)
अणु
	rphy->identअगरy.sas_address = SAS_ADDR(dev->sas_addr);
	rphy->identअगरy.initiator_port_protocols = dev->iproto;
	rphy->identअगरy.target_port_protocols = dev->tproto;
	चयन (dev->dev_type) अणु
	हाल SAS_SATA_DEV:
		/* FIXME: need sata device type */
	हाल SAS_END_DEVICE:
	हाल SAS_SATA_PENDING:
		rphy->identअगरy.device_type = SAS_END_DEVICE;
		अवरोध;
	हाल SAS_EDGE_EXPANDER_DEVICE:
		rphy->identअगरy.device_type = SAS_EDGE_EXPANDER_DEVICE;
		अवरोध;
	हाल SAS_FANOUT_EXPANDER_DEVICE:
		rphy->identअगरy.device_type = SAS_FANOUT_EXPANDER_DEVICE;
		अवरोध;
	शेष:
		rphy->identअगरy.device_type = SAS_PHY_UNUSED;
		अवरोध;
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम sas_phy_set_target(काष्ठा asd_sas_phy *p, काष्ठा करोमुख्य_device *dev)
अणु
	काष्ठा sas_phy *phy = p->phy;

	अगर (dev) अणु
		अगर (dev_is_sata(dev))
			phy->identअगरy.device_type = SAS_END_DEVICE;
		अन्यथा
			phy->identअगरy.device_type = dev->dev_type;
		phy->identअगरy.target_port_protocols = dev->tproto;
	पूर्ण अन्यथा अणु
		phy->identअगरy.device_type = SAS_PHY_UNUSED;
		phy->identअगरy.target_port_protocols = 0;
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम sas_add_parent_port(काष्ठा करोमुख्य_device *dev, पूर्णांक phy_id)
अणु
	काष्ठा expander_device *ex = &dev->ex_dev;
	काष्ठा ex_phy *ex_phy = &ex->ex_phy[phy_id];

	अगर (!ex->parent_port) अणु
		ex->parent_port = sas_port_alloc(&dev->rphy->dev, phy_id);
		/* FIXME: error handling */
		BUG_ON(!ex->parent_port);
		BUG_ON(sas_port_add(ex->parent_port));
		sas_port_mark_backlink(ex->parent_port);
	पूर्ण
	sas_port_add_phy(ex->parent_port, ex_phy->phy);
पूर्ण

अटल अंतरभूत काष्ठा करोमुख्य_device *sas_alloc_device(व्योम)
अणु
	काष्ठा करोमुख्य_device *dev = kzalloc(माप(*dev), GFP_KERNEL);

	अगर (dev) अणु
		INIT_LIST_HEAD(&dev->siblings);
		INIT_LIST_HEAD(&dev->dev_list_node);
		INIT_LIST_HEAD(&dev->disco_list_node);
		kref_init(&dev->kref);
		spin_lock_init(&dev->करोne_lock);
	पूर्ण
	वापस dev;
पूर्ण

अटल अंतरभूत व्योम sas_put_device(काष्ठा करोमुख्य_device *dev)
अणु
	kref_put(&dev->kref, sas_मुक्त_device);
पूर्ण

#पूर्ण_अगर /* _SAS_INTERNAL_H_ */
