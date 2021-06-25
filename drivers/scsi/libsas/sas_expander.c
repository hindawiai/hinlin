<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Serial Attached SCSI (SAS) Expander discovery and configuration
 *
 * Copyright (C) 2005 Adaptec, Inc.  All rights reserved.
 * Copyright (C) 2005 Luben Tuikov <luben_tuikov@adaptec.com>
 *
 * This file is licensed under GPLv2.
 */

#समावेश <linux/scatterlist.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/slab.h>
#समावेश <यंत्र/unaligned.h>

#समावेश "sas_internal.h"

#समावेश <scsi/sas_ata.h>
#समावेश <scsi/scsi_transport.h>
#समावेश <scsi/scsi_transport_sas.h>
#समावेश "../scsi_sas_internal.h"

अटल पूर्णांक sas_discover_expander(काष्ठा करोमुख्य_device *dev);
अटल पूर्णांक sas_configure_routing(काष्ठा करोमुख्य_device *dev, u8 *sas_addr);
अटल पूर्णांक sas_configure_phy(काष्ठा करोमुख्य_device *dev, पूर्णांक phy_id,
			     u8 *sas_addr, पूर्णांक include);
अटल पूर्णांक sas_disable_routing(काष्ठा करोमुख्य_device *dev,  u8 *sas_addr);

/* ---------- SMP task management ---------- */

अटल व्योम smp_task_समयकरोut(काष्ठा समयr_list *t)
अणु
	काष्ठा sas_task_slow *slow = from_समयr(slow, t, समयr);
	काष्ठा sas_task *task = slow->task;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&task->task_state_lock, flags);
	अगर (!(task->task_state_flags & SAS_TASK_STATE_DONE)) अणु
		task->task_state_flags |= SAS_TASK_STATE_ABORTED;
		complete(&task->slow_task->completion);
	पूर्ण
	spin_unlock_irqrestore(&task->task_state_lock, flags);
पूर्ण

अटल व्योम smp_task_करोne(काष्ठा sas_task *task)
अणु
	del_समयr(&task->slow_task->समयr);
	complete(&task->slow_task->completion);
पूर्ण

/* Give it some दीर्घ enough समयout. In seconds. */
#घोषणा SMP_TIMEOUT 10

अटल पूर्णांक smp_execute_task_sg(काष्ठा करोमुख्य_device *dev,
		काष्ठा scatterlist *req, काष्ठा scatterlist *resp)
अणु
	पूर्णांक res, retry;
	काष्ठा sas_task *task = शून्य;
	काष्ठा sas_पूर्णांकernal *i =
		to_sas_पूर्णांकernal(dev->port->ha->core.shost->transportt);

	mutex_lock(&dev->ex_dev.cmd_mutex);
	क्रम (retry = 0; retry < 3; retry++) अणु
		अगर (test_bit(SAS_DEV_GONE, &dev->state)) अणु
			res = -ECOMM;
			अवरोध;
		पूर्ण

		task = sas_alloc_slow_task(GFP_KERNEL);
		अगर (!task) अणु
			res = -ENOMEM;
			अवरोध;
		पूर्ण
		task->dev = dev;
		task->task_proto = dev->tproto;
		task->smp_task.smp_req = *req;
		task->smp_task.smp_resp = *resp;

		task->task_करोne = smp_task_करोne;

		task->slow_task->समयr.function = smp_task_समयकरोut;
		task->slow_task->समयr.expires = jअगरfies + SMP_TIMEOUT*HZ;
		add_समयr(&task->slow_task->समयr);

		res = i->dft->lldd_execute_task(task, GFP_KERNEL);

		अगर (res) अणु
			del_समयr(&task->slow_task->समयr);
			pr_notice("executing SMP task failed:%d\n", res);
			अवरोध;
		पूर्ण

		रुको_क्रम_completion(&task->slow_task->completion);
		res = -ECOMM;
		अगर ((task->task_state_flags & SAS_TASK_STATE_ABORTED)) अणु
			pr_notice("smp task timed out or aborted\n");
			i->dft->lldd_पात_task(task);
			अगर (!(task->task_state_flags & SAS_TASK_STATE_DONE)) अणु
				pr_notice("SMP task aborted and not done\n");
				अवरोध;
			पूर्ण
		पूर्ण
		अगर (task->task_status.resp == SAS_TASK_COMPLETE &&
		    task->task_status.stat == SAM_STAT_GOOD) अणु
			res = 0;
			अवरोध;
		पूर्ण
		अगर (task->task_status.resp == SAS_TASK_COMPLETE &&
		    task->task_status.stat == SAS_DATA_UNDERRUN) अणु
			/* no error, but वापस the number of bytes of
			 * underrun */
			res = task->task_status.residual;
			अवरोध;
		पूर्ण
		अगर (task->task_status.resp == SAS_TASK_COMPLETE &&
		    task->task_status.stat == SAS_DATA_OVERRUN) अणु
			res = -EMSGSIZE;
			अवरोध;
		पूर्ण
		अगर (task->task_status.resp == SAS_TASK_UNDELIVERED &&
		    task->task_status.stat == SAS_DEVICE_UNKNOWN)
			अवरोध;
		अन्यथा अणु
			pr_notice("%s: task to dev %016llx response: 0x%x status 0x%x\n",
				  __func__,
				  SAS_ADDR(dev->sas_addr),
				  task->task_status.resp,
				  task->task_status.stat);
			sas_मुक्त_task(task);
			task = शून्य;
		पूर्ण
	पूर्ण
	mutex_unlock(&dev->ex_dev.cmd_mutex);

	BUG_ON(retry == 3 && task != शून्य);
	sas_मुक्त_task(task);
	वापस res;
पूर्ण

अटल पूर्णांक smp_execute_task(काष्ठा करोमुख्य_device *dev, व्योम *req, पूर्णांक req_size,
			    व्योम *resp, पूर्णांक resp_size)
अणु
	काष्ठा scatterlist req_sg;
	काष्ठा scatterlist resp_sg;

	sg_init_one(&req_sg, req, req_size);
	sg_init_one(&resp_sg, resp, resp_size);
	वापस smp_execute_task_sg(dev, &req_sg, &resp_sg);
पूर्ण

/* ---------- Allocations ---------- */

अटल अंतरभूत व्योम *alloc_smp_req(पूर्णांक size)
अणु
	u8 *p = kzalloc(size, GFP_KERNEL);
	अगर (p)
		p[0] = SMP_REQUEST;
	वापस p;
पूर्ण

अटल अंतरभूत व्योम *alloc_smp_resp(पूर्णांक size)
अणु
	वापस kzalloc(size, GFP_KERNEL);
पूर्ण

अटल अक्षर sas_route_अक्षर(काष्ठा करोमुख्य_device *dev, काष्ठा ex_phy *phy)
अणु
	चयन (phy->routing_attr) अणु
	हाल TABLE_ROUTING:
		अगर (dev->ex_dev.t2t_supp)
			वापस 'U';
		अन्यथा
			वापस 'T';
	हाल सूचीECT_ROUTING:
		वापस 'D';
	हाल SUBTRACTIVE_ROUTING:
		वापस 'S';
	शेष:
		वापस '?';
	पूर्ण
पूर्ण

अटल क्रमागत sas_device_type to_dev_type(काष्ठा discover_resp *dr)
अणु
	/* This is detecting a failure to transmit initial dev to host
	 * FIS as described in section J.5 of sas-2 r16
	 */
	अगर (dr->attached_dev_type == SAS_PHY_UNUSED && dr->attached_sata_dev &&
	    dr->linkrate >= SAS_LINK_RATE_1_5_GBPS)
		वापस SAS_SATA_PENDING;
	अन्यथा
		वापस dr->attached_dev_type;
पूर्ण

अटल व्योम sas_set_ex_phy(काष्ठा करोमुख्य_device *dev, पूर्णांक phy_id, व्योम *rsp)
अणु
	क्रमागत sas_device_type dev_type;
	क्रमागत sas_linkrate linkrate;
	u8 sas_addr[SAS_ADDR_SIZE];
	काष्ठा smp_resp *resp = rsp;
	काष्ठा discover_resp *dr = &resp->disc;
	काष्ठा sas_ha_काष्ठा *ha = dev->port->ha;
	काष्ठा expander_device *ex = &dev->ex_dev;
	काष्ठा ex_phy *phy = &ex->ex_phy[phy_id];
	काष्ठा sas_rphy *rphy = dev->rphy;
	bool new_phy = !phy->phy;
	अक्षर *type;

	अगर (new_phy) अणु
		अगर (WARN_ON_ONCE(test_bit(SAS_HA_ATA_EH_ACTIVE, &ha->state)))
			वापस;
		phy->phy = sas_phy_alloc(&rphy->dev, phy_id);

		/* FIXME: error_handling */
		BUG_ON(!phy->phy);
	पूर्ण

	चयन (resp->result) अणु
	हाल SMP_RESP_PHY_VACANT:
		phy->phy_state = PHY_VACANT;
		अवरोध;
	शेष:
		phy->phy_state = PHY_NOT_PRESENT;
		अवरोध;
	हाल SMP_RESP_FUNC_ACC:
		phy->phy_state = PHY_EMPTY; /* करो not know yet */
		अवरोध;
	पूर्ण

	/* check अगर anything important changed to squelch debug */
	dev_type = phy->attached_dev_type;
	linkrate  = phy->linkrate;
	स_नकल(sas_addr, phy->attached_sas_addr, SAS_ADDR_SIZE);

	/* Handle vacant phy - rest of dr data is not valid so skip it */
	अगर (phy->phy_state == PHY_VACANT) अणु
		स_रखो(phy->attached_sas_addr, 0, SAS_ADDR_SIZE);
		phy->attached_dev_type = SAS_PHY_UNUSED;
		अगर (!test_bit(SAS_HA_ATA_EH_ACTIVE, &ha->state)) अणु
			phy->phy_id = phy_id;
			जाओ skip;
		पूर्ण अन्यथा
			जाओ out;
	पूर्ण

	phy->attached_dev_type = to_dev_type(dr);
	अगर (test_bit(SAS_HA_ATA_EH_ACTIVE, &ha->state))
		जाओ out;
	phy->phy_id = phy_id;
	phy->linkrate = dr->linkrate;
	phy->attached_sata_host = dr->attached_sata_host;
	phy->attached_sata_dev  = dr->attached_sata_dev;
	phy->attached_sata_ps   = dr->attached_sata_ps;
	phy->attached_iproto = dr->iproto << 1;
	phy->attached_tproto = dr->tproto << 1;
	/* help some expanders that fail to zero sas_address in the 'no
	 * device' हाल
	 */
	अगर (phy->attached_dev_type == SAS_PHY_UNUSED ||
	    phy->linkrate < SAS_LINK_RATE_1_5_GBPS)
		स_रखो(phy->attached_sas_addr, 0, SAS_ADDR_SIZE);
	अन्यथा
		स_नकल(phy->attached_sas_addr, dr->attached_sas_addr, SAS_ADDR_SIZE);
	phy->attached_phy_id = dr->attached_phy_id;
	phy->phy_change_count = dr->change_count;
	phy->routing_attr = dr->routing_attr;
	phy->भव = dr->भव;
	phy->last_da_index = -1;

	phy->phy->identअगरy.sas_address = SAS_ADDR(phy->attached_sas_addr);
	phy->phy->identअगरy.device_type = dr->attached_dev_type;
	phy->phy->identअगरy.initiator_port_protocols = phy->attached_iproto;
	phy->phy->identअगरy.target_port_protocols = phy->attached_tproto;
	अगर (!phy->attached_tproto && dr->attached_sata_dev)
		phy->phy->identअगरy.target_port_protocols = SAS_PROTOCOL_SATA;
	phy->phy->identअगरy.phy_identअगरier = phy_id;
	phy->phy->minimum_linkrate_hw = dr->hmin_linkrate;
	phy->phy->maximum_linkrate_hw = dr->hmax_linkrate;
	phy->phy->minimum_linkrate = dr->pmin_linkrate;
	phy->phy->maximum_linkrate = dr->pmax_linkrate;
	phy->phy->negotiated_linkrate = phy->linkrate;
	phy->phy->enabled = (phy->linkrate != SAS_PHY_DISABLED);

 skip:
	अगर (new_phy)
		अगर (sas_phy_add(phy->phy)) अणु
			sas_phy_मुक्त(phy->phy);
			वापस;
		पूर्ण

 out:
	चयन (phy->attached_dev_type) अणु
	हाल SAS_SATA_PENDING:
		type = "stp pending";
		अवरोध;
	हाल SAS_PHY_UNUSED:
		type = "no device";
		अवरोध;
	हाल SAS_END_DEVICE:
		अगर (phy->attached_iproto) अणु
			अगर (phy->attached_tproto)
				type = "host+target";
			अन्यथा
				type = "host";
		पूर्ण अन्यथा अणु
			अगर (dr->attached_sata_dev)
				type = "stp";
			अन्यथा
				type = "ssp";
		पूर्ण
		अवरोध;
	हाल SAS_EDGE_EXPANDER_DEVICE:
	हाल SAS_FANOUT_EXPANDER_DEVICE:
		type = "smp";
		अवरोध;
	शेष:
		type = "unknown";
	पूर्ण

	/* this routine is polled by libata error recovery so filter
	 * unimportant messages
	 */
	अगर (new_phy || phy->attached_dev_type != dev_type ||
	    phy->linkrate != linkrate ||
	    SAS_ADDR(phy->attached_sas_addr) != SAS_ADDR(sas_addr))
		/* pass */;
	अन्यथा
		वापस;

	/* अगर the attached device type changed and ata_eh is active,
	 * make sure we run revalidation when eh completes (see:
	 * sas_enable_revalidation)
	 */
	अगर (test_bit(SAS_HA_ATA_EH_ACTIVE, &ha->state))
		set_bit(DISCE_REVALIDATE_DOMAIN, &dev->port->disc.pending);

	pr_debug("%sex %016llx phy%02d:%c:%X attached: %016llx (%s)\n",
		 test_bit(SAS_HA_ATA_EH_ACTIVE, &ha->state) ? "ata: " : "",
		 SAS_ADDR(dev->sas_addr), phy->phy_id,
		 sas_route_अक्षर(dev, phy), phy->linkrate,
		 SAS_ADDR(phy->attached_sas_addr), type);
पूर्ण

/* check अगर we have an existing attached ata device on this expander phy */
काष्ठा करोमुख्य_device *sas_ex_to_ata(काष्ठा करोमुख्य_device *ex_dev, पूर्णांक phy_id)
अणु
	काष्ठा ex_phy *ex_phy = &ex_dev->ex_dev.ex_phy[phy_id];
	काष्ठा करोमुख्य_device *dev;
	काष्ठा sas_rphy *rphy;

	अगर (!ex_phy->port)
		वापस शून्य;

	rphy = ex_phy->port->rphy;
	अगर (!rphy)
		वापस शून्य;

	dev = sas_find_dev_by_rphy(rphy);

	अगर (dev && dev_is_sata(dev))
		वापस dev;

	वापस शून्य;
पूर्ण

#घोषणा DISCOVER_REQ_SIZE  16
#घोषणा DISCOVER_RESP_SIZE 56

अटल पूर्णांक sas_ex_phy_discover_helper(काष्ठा करोमुख्य_device *dev, u8 *disc_req,
				      u8 *disc_resp, पूर्णांक single)
अणु
	काष्ठा discover_resp *dr;
	पूर्णांक res;

	disc_req[9] = single;

	res = smp_execute_task(dev, disc_req, DISCOVER_REQ_SIZE,
			       disc_resp, DISCOVER_RESP_SIZE);
	अगर (res)
		वापस res;
	dr = &((काष्ठा smp_resp *)disc_resp)->disc;
	अगर (स_भेद(dev->sas_addr, dr->attached_sas_addr, SAS_ADDR_SIZE) == 0) अणु
		pr_notice("Found loopback topology, just ignore it!\n");
		वापस 0;
	पूर्ण
	sas_set_ex_phy(dev, single, disc_resp);
	वापस 0;
पूर्ण

पूर्णांक sas_ex_phy_discover(काष्ठा करोमुख्य_device *dev, पूर्णांक single)
अणु
	काष्ठा expander_device *ex = &dev->ex_dev;
	पूर्णांक  res = 0;
	u8   *disc_req;
	u8   *disc_resp;

	disc_req = alloc_smp_req(DISCOVER_REQ_SIZE);
	अगर (!disc_req)
		वापस -ENOMEM;

	disc_resp = alloc_smp_resp(DISCOVER_RESP_SIZE);
	अगर (!disc_resp) अणु
		kमुक्त(disc_req);
		वापस -ENOMEM;
	पूर्ण

	disc_req[1] = SMP_DISCOVER;

	अगर (0 <= single && single < ex->num_phys) अणु
		res = sas_ex_phy_discover_helper(dev, disc_req, disc_resp, single);
	पूर्ण अन्यथा अणु
		पूर्णांक i;

		क्रम (i = 0; i < ex->num_phys; i++) अणु
			res = sas_ex_phy_discover_helper(dev, disc_req,
							 disc_resp, i);
			अगर (res)
				जाओ out_err;
		पूर्ण
	पूर्ण
out_err:
	kमुक्त(disc_resp);
	kमुक्त(disc_req);
	वापस res;
पूर्ण

अटल पूर्णांक sas_expander_discover(काष्ठा करोमुख्य_device *dev)
अणु
	काष्ठा expander_device *ex = &dev->ex_dev;
	पूर्णांक res;

	ex->ex_phy = kसुस्मृति(ex->num_phys, माप(*ex->ex_phy), GFP_KERNEL);
	अगर (!ex->ex_phy)
		वापस -ENOMEM;

	res = sas_ex_phy_discover(dev, -1);
	अगर (res)
		जाओ out_err;

	वापस 0;
 out_err:
	kमुक्त(ex->ex_phy);
	ex->ex_phy = शून्य;
	वापस res;
पूर्ण

#घोषणा MAX_EXPANDER_PHYS 128

अटल व्योम ex_assign_report_general(काष्ठा करोमुख्य_device *dev,
					    काष्ठा smp_resp *resp)
अणु
	काष्ठा report_general_resp *rg = &resp->rg;

	dev->ex_dev.ex_change_count = be16_to_cpu(rg->change_count);
	dev->ex_dev.max_route_indexes = be16_to_cpu(rg->route_indexes);
	dev->ex_dev.num_phys = min(rg->num_phys, (u8)MAX_EXPANDER_PHYS);
	dev->ex_dev.t2t_supp = rg->t2t_supp;
	dev->ex_dev.conf_route_table = rg->conf_route_table;
	dev->ex_dev.configuring = rg->configuring;
	स_नकल(dev->ex_dev.enclosure_logical_id, rg->enclosure_logical_id, 8);
पूर्ण

#घोषणा RG_REQ_SIZE   8
#घोषणा RG_RESP_SIZE 32

अटल पूर्णांक sas_ex_general(काष्ठा करोमुख्य_device *dev)
अणु
	u8 *rg_req;
	काष्ठा smp_resp *rg_resp;
	पूर्णांक res;
	पूर्णांक i;

	rg_req = alloc_smp_req(RG_REQ_SIZE);
	अगर (!rg_req)
		वापस -ENOMEM;

	rg_resp = alloc_smp_resp(RG_RESP_SIZE);
	अगर (!rg_resp) अणु
		kमुक्त(rg_req);
		वापस -ENOMEM;
	पूर्ण

	rg_req[1] = SMP_REPORT_GENERAL;

	क्रम (i = 0; i < 5; i++) अणु
		res = smp_execute_task(dev, rg_req, RG_REQ_SIZE, rg_resp,
				       RG_RESP_SIZE);

		अगर (res) अणु
			pr_notice("RG to ex %016llx failed:0x%x\n",
				  SAS_ADDR(dev->sas_addr), res);
			जाओ out;
		पूर्ण अन्यथा अगर (rg_resp->result != SMP_RESP_FUNC_ACC) अणु
			pr_debug("RG:ex %016llx returned SMP result:0x%x\n",
				 SAS_ADDR(dev->sas_addr), rg_resp->result);
			res = rg_resp->result;
			जाओ out;
		पूर्ण

		ex_assign_report_general(dev, rg_resp);

		अगर (dev->ex_dev.configuring) अणु
			pr_debug("RG: ex %016llx self-configuring...\n",
				 SAS_ADDR(dev->sas_addr));
			schedule_समयout_पूर्णांकerruptible(5*HZ);
		पूर्ण अन्यथा
			अवरोध;
	पूर्ण
out:
	kमुक्त(rg_req);
	kमुक्त(rg_resp);
	वापस res;
पूर्ण

अटल व्योम ex_assign_manuf_info(काष्ठा करोमुख्य_device *dev, व्योम
					*_mi_resp)
अणु
	u8 *mi_resp = _mi_resp;
	काष्ठा sas_rphy *rphy = dev->rphy;
	काष्ठा sas_expander_device *edev = rphy_to_expander_device(rphy);

	स_नकल(edev->venकरोr_id, mi_resp + 12, SAS_EXPANDER_VENDOR_ID_LEN);
	स_नकल(edev->product_id, mi_resp + 20, SAS_EXPANDER_PRODUCT_ID_LEN);
	स_नकल(edev->product_rev, mi_resp + 36,
	       SAS_EXPANDER_PRODUCT_REV_LEN);

	अगर (mi_resp[8] & 1) अणु
		स_नकल(edev->component_venकरोr_id, mi_resp + 40,
		       SAS_EXPANDER_COMPONENT_VENDOR_ID_LEN);
		edev->component_id = mi_resp[48] << 8 | mi_resp[49];
		edev->component_revision_id = mi_resp[50];
	पूर्ण
पूर्ण

#घोषणा MI_REQ_SIZE   8
#घोषणा MI_RESP_SIZE 64

अटल पूर्णांक sas_ex_manuf_info(काष्ठा करोमुख्य_device *dev)
अणु
	u8 *mi_req;
	u8 *mi_resp;
	पूर्णांक res;

	mi_req = alloc_smp_req(MI_REQ_SIZE);
	अगर (!mi_req)
		वापस -ENOMEM;

	mi_resp = alloc_smp_resp(MI_RESP_SIZE);
	अगर (!mi_resp) अणु
		kमुक्त(mi_req);
		वापस -ENOMEM;
	पूर्ण

	mi_req[1] = SMP_REPORT_MANUF_INFO;

	res = smp_execute_task(dev, mi_req, MI_REQ_SIZE, mi_resp, MI_RESP_SIZE);
	अगर (res) अणु
		pr_notice("MI: ex %016llx failed:0x%x\n",
			  SAS_ADDR(dev->sas_addr), res);
		जाओ out;
	पूर्ण अन्यथा अगर (mi_resp[2] != SMP_RESP_FUNC_ACC) अणु
		pr_debug("MI ex %016llx returned SMP result:0x%x\n",
			 SAS_ADDR(dev->sas_addr), mi_resp[2]);
		जाओ out;
	पूर्ण

	ex_assign_manuf_info(dev, mi_resp);
out:
	kमुक्त(mi_req);
	kमुक्त(mi_resp);
	वापस res;
पूर्ण

#घोषणा PC_REQ_SIZE  44
#घोषणा PC_RESP_SIZE 8

पूर्णांक sas_smp_phy_control(काष्ठा करोमुख्य_device *dev, पूर्णांक phy_id,
			क्रमागत phy_func phy_func,
			काष्ठा sas_phy_linkrates *rates)
अणु
	u8 *pc_req;
	u8 *pc_resp;
	पूर्णांक res;

	pc_req = alloc_smp_req(PC_REQ_SIZE);
	अगर (!pc_req)
		वापस -ENOMEM;

	pc_resp = alloc_smp_resp(PC_RESP_SIZE);
	अगर (!pc_resp) अणु
		kमुक्त(pc_req);
		वापस -ENOMEM;
	पूर्ण

	pc_req[1] = SMP_PHY_CONTROL;
	pc_req[9] = phy_id;
	pc_req[10] = phy_func;
	अगर (rates) अणु
		pc_req[32] = rates->minimum_linkrate << 4;
		pc_req[33] = rates->maximum_linkrate << 4;
	पूर्ण

	res = smp_execute_task(dev, pc_req, PC_REQ_SIZE, pc_resp, PC_RESP_SIZE);
	अगर (res) अणु
		pr_err("ex %016llx phy%02d PHY control failed: %d\n",
		       SAS_ADDR(dev->sas_addr), phy_id, res);
	पूर्ण अन्यथा अगर (pc_resp[2] != SMP_RESP_FUNC_ACC) अणु
		pr_err("ex %016llx phy%02d PHY control failed: function result 0x%x\n",
		       SAS_ADDR(dev->sas_addr), phy_id, pc_resp[2]);
		res = pc_resp[2];
	पूर्ण
	kमुक्त(pc_resp);
	kमुक्त(pc_req);
	वापस res;
पूर्ण

अटल व्योम sas_ex_disable_phy(काष्ठा करोमुख्य_device *dev, पूर्णांक phy_id)
अणु
	काष्ठा expander_device *ex = &dev->ex_dev;
	काष्ठा ex_phy *phy = &ex->ex_phy[phy_id];

	sas_smp_phy_control(dev, phy_id, PHY_FUNC_DISABLE, शून्य);
	phy->linkrate = SAS_PHY_DISABLED;
पूर्ण

अटल व्योम sas_ex_disable_port(काष्ठा करोमुख्य_device *dev, u8 *sas_addr)
अणु
	काष्ठा expander_device *ex = &dev->ex_dev;
	पूर्णांक i;

	क्रम (i = 0; i < ex->num_phys; i++) अणु
		काष्ठा ex_phy *phy = &ex->ex_phy[i];

		अगर (phy->phy_state == PHY_VACANT ||
		    phy->phy_state == PHY_NOT_PRESENT)
			जारी;

		अगर (SAS_ADDR(phy->attached_sas_addr) == SAS_ADDR(sas_addr))
			sas_ex_disable_phy(dev, i);
	पूर्ण
पूर्ण

अटल पूर्णांक sas_dev_present_in_करोमुख्य(काष्ठा asd_sas_port *port,
					    u8 *sas_addr)
अणु
	काष्ठा करोमुख्य_device *dev;

	अगर (SAS_ADDR(port->sas_addr) == SAS_ADDR(sas_addr))
		वापस 1;
	list_क्रम_each_entry(dev, &port->dev_list, dev_list_node) अणु
		अगर (SAS_ADDR(dev->sas_addr) == SAS_ADDR(sas_addr))
			वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

#घोषणा RPEL_REQ_SIZE	16
#घोषणा RPEL_RESP_SIZE	32
पूर्णांक sas_smp_get_phy_events(काष्ठा sas_phy *phy)
अणु
	पूर्णांक res;
	u8 *req;
	u8 *resp;
	काष्ठा sas_rphy *rphy = dev_to_rphy(phy->dev.parent);
	काष्ठा करोमुख्य_device *dev = sas_find_dev_by_rphy(rphy);

	req = alloc_smp_req(RPEL_REQ_SIZE);
	अगर (!req)
		वापस -ENOMEM;

	resp = alloc_smp_resp(RPEL_RESP_SIZE);
	अगर (!resp) अणु
		kमुक्त(req);
		वापस -ENOMEM;
	पूर्ण

	req[1] = SMP_REPORT_PHY_ERR_LOG;
	req[9] = phy->number;

	res = smp_execute_task(dev, req, RPEL_REQ_SIZE,
			       resp, RPEL_RESP_SIZE);

	अगर (res)
		जाओ out;

	phy->invalid_dword_count = get_unaligned_be32(&resp[12]);
	phy->running_disparity_error_count = get_unaligned_be32(&resp[16]);
	phy->loss_of_dword_sync_count = get_unaligned_be32(&resp[20]);
	phy->phy_reset_problem_count = get_unaligned_be32(&resp[24]);

 out:
	kमुक्त(req);
	kमुक्त(resp);
	वापस res;

पूर्ण

#अगर_घोषित CONFIG_SCSI_SAS_ATA

#घोषणा RPS_REQ_SIZE  16
#घोषणा RPS_RESP_SIZE 60

पूर्णांक sas_get_report_phy_sata(काष्ठा करोमुख्य_device *dev, पूर्णांक phy_id,
			    काष्ठा smp_resp *rps_resp)
अणु
	पूर्णांक res;
	u8 *rps_req = alloc_smp_req(RPS_REQ_SIZE);
	u8 *resp = (u8 *)rps_resp;

	अगर (!rps_req)
		वापस -ENOMEM;

	rps_req[1] = SMP_REPORT_PHY_SATA;
	rps_req[9] = phy_id;

	res = smp_execute_task(dev, rps_req, RPS_REQ_SIZE,
			       rps_resp, RPS_RESP_SIZE);

	/* 0x34 is the FIS type क्रम the D2H fis.  There's a potential
	 * standards cockup here.  sas-2 explicitly specअगरies the FIS
	 * should be encoded so that FIS type is in resp[24].
	 * However, some expanders endian reverse this.  Unकरो the
	 * reversal here */
	अगर (!res && resp[27] == 0x34 && resp[24] != 0x34) अणु
		पूर्णांक i;

		क्रम (i = 0; i < 5; i++) अणु
			पूर्णांक j = 24 + (i*4);
			u8 a, b;
			a = resp[j + 0];
			b = resp[j + 1];
			resp[j + 0] = resp[j + 3];
			resp[j + 1] = resp[j + 2];
			resp[j + 2] = b;
			resp[j + 3] = a;
		पूर्ण
	पूर्ण

	kमुक्त(rps_req);
	वापस res;
पूर्ण
#पूर्ण_अगर

अटल व्योम sas_ex_get_linkrate(काष्ठा करोमुख्य_device *parent,
				       काष्ठा करोमुख्य_device *child,
				       काष्ठा ex_phy *parent_phy)
अणु
	काष्ठा expander_device *parent_ex = &parent->ex_dev;
	काष्ठा sas_port *port;
	पूर्णांक i;

	child->pathways = 0;

	port = parent_phy->port;

	क्रम (i = 0; i < parent_ex->num_phys; i++) अणु
		काष्ठा ex_phy *phy = &parent_ex->ex_phy[i];

		अगर (phy->phy_state == PHY_VACANT ||
		    phy->phy_state == PHY_NOT_PRESENT)
			जारी;

		अगर (SAS_ADDR(phy->attached_sas_addr) ==
		    SAS_ADDR(child->sas_addr)) अणु

			child->min_linkrate = min(parent->min_linkrate,
						  phy->linkrate);
			child->max_linkrate = max(parent->max_linkrate,
						  phy->linkrate);
			child->pathways++;
			sas_port_add_phy(port, phy->phy);
		पूर्ण
	पूर्ण
	child->linkrate = min(parent_phy->linkrate, child->max_linkrate);
	child->pathways = min(child->pathways, parent->pathways);
पूर्ण

अटल काष्ठा करोमुख्य_device *sas_ex_discover_end_dev(
	काष्ठा करोमुख्य_device *parent, पूर्णांक phy_id)
अणु
	काष्ठा expander_device *parent_ex = &parent->ex_dev;
	काष्ठा ex_phy *phy = &parent_ex->ex_phy[phy_id];
	काष्ठा करोमुख्य_device *child = शून्य;
	काष्ठा sas_rphy *rphy;
	पूर्णांक res;

	अगर (phy->attached_sata_host || phy->attached_sata_ps)
		वापस शून्य;

	child = sas_alloc_device();
	अगर (!child)
		वापस शून्य;

	kref_get(&parent->kref);
	child->parent = parent;
	child->port   = parent->port;
	child->iproto = phy->attached_iproto;
	स_नकल(child->sas_addr, phy->attached_sas_addr, SAS_ADDR_SIZE);
	sas_hash_addr(child->hashed_sas_addr, child->sas_addr);
	अगर (!phy->port) अणु
		phy->port = sas_port_alloc(&parent->rphy->dev, phy_id);
		अगर (unlikely(!phy->port))
			जाओ out_err;
		अगर (unlikely(sas_port_add(phy->port) != 0)) अणु
			sas_port_मुक्त(phy->port);
			जाओ out_err;
		पूर्ण
	पूर्ण
	sas_ex_get_linkrate(parent, child, phy);
	sas_device_set_phy(child, phy->port);

#अगर_घोषित CONFIG_SCSI_SAS_ATA
	अगर ((phy->attached_tproto & SAS_PROTOCOL_STP) || phy->attached_sata_dev) अणु
		अगर (child->linkrate > parent->min_linkrate) अणु
			काष्ठा sas_phy *cphy = child->phy;
			क्रमागत sas_linkrate min_prate = cphy->minimum_linkrate,
				parent_min_lrate = parent->min_linkrate,
				min_linkrate = (min_prate > parent_min_lrate) ?
					       parent_min_lrate : 0;
			काष्ठा sas_phy_linkrates rates = अणु
				.maximum_linkrate = parent->min_linkrate,
				.minimum_linkrate = min_linkrate,
			पूर्ण;
			पूर्णांक ret;

			pr_notice("ex %016llx phy%02d SATA device linkrate > min pathway connection rate, attempting to lower device linkrate\n",
				   SAS_ADDR(child->sas_addr), phy_id);
			ret = sas_smp_phy_control(parent, phy_id,
						  PHY_FUNC_LINK_RESET, &rates);
			अगर (ret) अणु
				pr_err("ex %016llx phy%02d SATA device could not set linkrate (%d)\n",
				       SAS_ADDR(child->sas_addr), phy_id, ret);
				जाओ out_मुक्त;
			पूर्ण
			pr_notice("ex %016llx phy%02d SATA device set linkrate successfully\n",
				  SAS_ADDR(child->sas_addr), phy_id);
			child->linkrate = child->min_linkrate;
		पूर्ण
		res = sas_get_ata_info(child, phy);
		अगर (res)
			जाओ out_मुक्त;

		sas_init_dev(child);
		res = sas_ata_init(child);
		अगर (res)
			जाओ out_मुक्त;
		rphy = sas_end_device_alloc(phy->port);
		अगर (!rphy)
			जाओ out_मुक्त;
		rphy->identअगरy.phy_identअगरier = phy_id;

		child->rphy = rphy;
		get_device(&rphy->dev);

		list_add_tail(&child->disco_list_node, &parent->port->disco_list);

		res = sas_discover_sata(child);
		अगर (res) अणु
			pr_notice("sas_discover_sata() for device %16llx at %016llx:%02d returned 0x%x\n",
				  SAS_ADDR(child->sas_addr),
				  SAS_ADDR(parent->sas_addr), phy_id, res);
			जाओ out_list_del;
		पूर्ण
	पूर्ण अन्यथा
#पूर्ण_अगर
	  अगर (phy->attached_tproto & SAS_PROTOCOL_SSP) अणु
		child->dev_type = SAS_END_DEVICE;
		rphy = sas_end_device_alloc(phy->port);
		/* FIXME: error handling */
		अगर (unlikely(!rphy))
			जाओ out_मुक्त;
		child->tproto = phy->attached_tproto;
		sas_init_dev(child);

		child->rphy = rphy;
		get_device(&rphy->dev);
		rphy->identअगरy.phy_identअगरier = phy_id;
		sas_fill_in_rphy(child, rphy);

		list_add_tail(&child->disco_list_node, &parent->port->disco_list);

		res = sas_discover_end_dev(child);
		अगर (res) अणु
			pr_notice("sas_discover_end_dev() for device %016llx at %016llx:%02d returned 0x%x\n",
				  SAS_ADDR(child->sas_addr),
				  SAS_ADDR(parent->sas_addr), phy_id, res);
			जाओ out_list_del;
		पूर्ण
	पूर्ण अन्यथा अणु
		pr_notice("target proto 0x%x at %016llx:0x%x not handled\n",
			  phy->attached_tproto, SAS_ADDR(parent->sas_addr),
			  phy_id);
		जाओ out_मुक्त;
	पूर्ण

	list_add_tail(&child->siblings, &parent_ex->children);
	वापस child;

 out_list_del:
	sas_rphy_मुक्त(child->rphy);
	list_del(&child->disco_list_node);
	spin_lock_irq(&parent->port->dev_list_lock);
	list_del(&child->dev_list_node);
	spin_unlock_irq(&parent->port->dev_list_lock);
 out_मुक्त:
	sas_port_delete(phy->port);
 out_err:
	phy->port = शून्य;
	sas_put_device(child);
	वापस शून्य;
पूर्ण

/* See अगर this phy is part of a wide port */
अटल bool sas_ex_join_wide_port(काष्ठा करोमुख्य_device *parent, पूर्णांक phy_id)
अणु
	काष्ठा ex_phy *phy = &parent->ex_dev.ex_phy[phy_id];
	पूर्णांक i;

	क्रम (i = 0; i < parent->ex_dev.num_phys; i++) अणु
		काष्ठा ex_phy *ephy = &parent->ex_dev.ex_phy[i];

		अगर (ephy == phy)
			जारी;

		अगर (!स_भेद(phy->attached_sas_addr, ephy->attached_sas_addr,
			    SAS_ADDR_SIZE) && ephy->port) अणु
			sas_port_add_phy(ephy->port, phy->phy);
			phy->port = ephy->port;
			phy->phy_state = PHY_DEVICE_DISCOVERED;
			वापस true;
		पूर्ण
	पूर्ण

	वापस false;
पूर्ण

अटल काष्ठा करोमुख्य_device *sas_ex_discover_expander(
	काष्ठा करोमुख्य_device *parent, पूर्णांक phy_id)
अणु
	काष्ठा sas_expander_device *parent_ex = rphy_to_expander_device(parent->rphy);
	काष्ठा ex_phy *phy = &parent->ex_dev.ex_phy[phy_id];
	काष्ठा करोमुख्य_device *child = शून्य;
	काष्ठा sas_rphy *rphy;
	काष्ठा sas_expander_device *edev;
	काष्ठा asd_sas_port *port;
	पूर्णांक res;

	अगर (phy->routing_attr == सूचीECT_ROUTING) अणु
		pr_warn("ex %016llx:%02d:D <--> ex %016llx:0x%x is not allowed\n",
			SAS_ADDR(parent->sas_addr), phy_id,
			SAS_ADDR(phy->attached_sas_addr),
			phy->attached_phy_id);
		वापस शून्य;
	पूर्ण
	child = sas_alloc_device();
	अगर (!child)
		वापस शून्य;

	phy->port = sas_port_alloc(&parent->rphy->dev, phy_id);
	/* FIXME: better error handling */
	BUG_ON(sas_port_add(phy->port) != 0);


	चयन (phy->attached_dev_type) अणु
	हाल SAS_EDGE_EXPANDER_DEVICE:
		rphy = sas_expander_alloc(phy->port,
					  SAS_EDGE_EXPANDER_DEVICE);
		अवरोध;
	हाल SAS_FANOUT_EXPANDER_DEVICE:
		rphy = sas_expander_alloc(phy->port,
					  SAS_FANOUT_EXPANDER_DEVICE);
		अवरोध;
	शेष:
		rphy = शून्य;	/* shut gcc up */
		BUG();
	पूर्ण
	port = parent->port;
	child->rphy = rphy;
	get_device(&rphy->dev);
	edev = rphy_to_expander_device(rphy);
	child->dev_type = phy->attached_dev_type;
	kref_get(&parent->kref);
	child->parent = parent;
	child->port = port;
	child->iproto = phy->attached_iproto;
	child->tproto = phy->attached_tproto;
	स_नकल(child->sas_addr, phy->attached_sas_addr, SAS_ADDR_SIZE);
	sas_hash_addr(child->hashed_sas_addr, child->sas_addr);
	sas_ex_get_linkrate(parent, child, phy);
	edev->level = parent_ex->level + 1;
	parent->port->disc.max_level = max(parent->port->disc.max_level,
					   edev->level);
	sas_init_dev(child);
	sas_fill_in_rphy(child, rphy);
	sas_rphy_add(rphy);

	spin_lock_irq(&parent->port->dev_list_lock);
	list_add_tail(&child->dev_list_node, &parent->port->dev_list);
	spin_unlock_irq(&parent->port->dev_list_lock);

	res = sas_discover_expander(child);
	अगर (res) अणु
		sas_rphy_delete(rphy);
		spin_lock_irq(&parent->port->dev_list_lock);
		list_del(&child->dev_list_node);
		spin_unlock_irq(&parent->port->dev_list_lock);
		sas_put_device(child);
		sas_port_delete(phy->port);
		phy->port = शून्य;
		वापस शून्य;
	पूर्ण
	list_add_tail(&child->siblings, &parent->ex_dev.children);
	वापस child;
पूर्ण

अटल पूर्णांक sas_ex_discover_dev(काष्ठा करोमुख्य_device *dev, पूर्णांक phy_id)
अणु
	काष्ठा expander_device *ex = &dev->ex_dev;
	काष्ठा ex_phy *ex_phy = &ex->ex_phy[phy_id];
	काष्ठा करोमुख्य_device *child = शून्य;
	पूर्णांक res = 0;

	/* Phy state */
	अगर (ex_phy->linkrate == SAS_SATA_SPINUP_HOLD) अणु
		अगर (!sas_smp_phy_control(dev, phy_id, PHY_FUNC_LINK_RESET, शून्य))
			res = sas_ex_phy_discover(dev, phy_id);
		अगर (res)
			वापस res;
	पूर्ण

	/* Parent and करोमुख्य coherency */
	अगर (!dev->parent && (SAS_ADDR(ex_phy->attached_sas_addr) ==
			     SAS_ADDR(dev->port->sas_addr))) अणु
		sas_add_parent_port(dev, phy_id);
		वापस 0;
	पूर्ण
	अगर (dev->parent && (SAS_ADDR(ex_phy->attached_sas_addr) ==
			    SAS_ADDR(dev->parent->sas_addr))) अणु
		sas_add_parent_port(dev, phy_id);
		अगर (ex_phy->routing_attr == TABLE_ROUTING)
			sas_configure_phy(dev, phy_id, dev->port->sas_addr, 1);
		वापस 0;
	पूर्ण

	अगर (sas_dev_present_in_करोमुख्य(dev->port, ex_phy->attached_sas_addr))
		sas_ex_disable_port(dev, ex_phy->attached_sas_addr);

	अगर (ex_phy->attached_dev_type == SAS_PHY_UNUSED) अणु
		अगर (ex_phy->routing_attr == सूचीECT_ROUTING) अणु
			स_रखो(ex_phy->attached_sas_addr, 0, SAS_ADDR_SIZE);
			sas_configure_routing(dev, ex_phy->attached_sas_addr);
		पूर्ण
		वापस 0;
	पूर्ण अन्यथा अगर (ex_phy->linkrate == SAS_LINK_RATE_UNKNOWN)
		वापस 0;

	अगर (ex_phy->attached_dev_type != SAS_END_DEVICE &&
	    ex_phy->attached_dev_type != SAS_FANOUT_EXPANDER_DEVICE &&
	    ex_phy->attached_dev_type != SAS_EDGE_EXPANDER_DEVICE &&
	    ex_phy->attached_dev_type != SAS_SATA_PENDING) अणु
		pr_warn("unknown device type(0x%x) attached to ex %016llx phy%02d\n",
			ex_phy->attached_dev_type,
			SAS_ADDR(dev->sas_addr),
			phy_id);
		वापस 0;
	पूर्ण

	res = sas_configure_routing(dev, ex_phy->attached_sas_addr);
	अगर (res) अणु
		pr_notice("configure routing for dev %016llx reported 0x%x. Forgotten\n",
			  SAS_ADDR(ex_phy->attached_sas_addr), res);
		sas_disable_routing(dev, ex_phy->attached_sas_addr);
		वापस res;
	पूर्ण

	अगर (sas_ex_join_wide_port(dev, phy_id)) अणु
		pr_debug("Attaching ex phy%02d to wide port %016llx\n",
			 phy_id, SAS_ADDR(ex_phy->attached_sas_addr));
		वापस res;
	पूर्ण

	चयन (ex_phy->attached_dev_type) अणु
	हाल SAS_END_DEVICE:
	हाल SAS_SATA_PENDING:
		child = sas_ex_discover_end_dev(dev, phy_id);
		अवरोध;
	हाल SAS_FANOUT_EXPANDER_DEVICE:
		अगर (SAS_ADDR(dev->port->disc.fanout_sas_addr)) अणु
			pr_debug("second fanout expander %016llx phy%02d attached to ex %016llx phy%02d\n",
				 SAS_ADDR(ex_phy->attached_sas_addr),
				 ex_phy->attached_phy_id,
				 SAS_ADDR(dev->sas_addr),
				 phy_id);
			sas_ex_disable_phy(dev, phy_id);
			वापस res;
		पूर्ण अन्यथा
			स_नकल(dev->port->disc.fanout_sas_addr,
			       ex_phy->attached_sas_addr, SAS_ADDR_SIZE);
		fallthrough;
	हाल SAS_EDGE_EXPANDER_DEVICE:
		child = sas_ex_discover_expander(dev, phy_id);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	अगर (!child)
		pr_notice("ex %016llx phy%02d failed to discover\n",
			  SAS_ADDR(dev->sas_addr), phy_id);
	वापस res;
पूर्ण

अटल पूर्णांक sas_find_sub_addr(काष्ठा करोमुख्य_device *dev, u8 *sub_addr)
अणु
	काष्ठा expander_device *ex = &dev->ex_dev;
	पूर्णांक i;

	क्रम (i = 0; i < ex->num_phys; i++) अणु
		काष्ठा ex_phy *phy = &ex->ex_phy[i];

		अगर (phy->phy_state == PHY_VACANT ||
		    phy->phy_state == PHY_NOT_PRESENT)
			जारी;

		अगर (dev_is_expander(phy->attached_dev_type) &&
		    phy->routing_attr == SUBTRACTIVE_ROUTING) अणु

			स_नकल(sub_addr, phy->attached_sas_addr, SAS_ADDR_SIZE);

			वापस 1;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक sas_check_level_subtractive_boundary(काष्ठा करोमुख्य_device *dev)
अणु
	काष्ठा expander_device *ex = &dev->ex_dev;
	काष्ठा करोमुख्य_device *child;
	u8 sub_addr[SAS_ADDR_SIZE] = अणु0, पूर्ण;

	list_क्रम_each_entry(child, &ex->children, siblings) अणु
		अगर (!dev_is_expander(child->dev_type))
			जारी;
		अगर (sub_addr[0] == 0) अणु
			sas_find_sub_addr(child, sub_addr);
			जारी;
		पूर्ण अन्यथा अणु
			u8 s2[SAS_ADDR_SIZE];

			अगर (sas_find_sub_addr(child, s2) &&
			    (SAS_ADDR(sub_addr) != SAS_ADDR(s2))) अणु

				pr_notice("ex %016llx->%016llx-?->%016llx diverges from subtractive boundary %016llx\n",
					  SAS_ADDR(dev->sas_addr),
					  SAS_ADDR(child->sas_addr),
					  SAS_ADDR(s2),
					  SAS_ADDR(sub_addr));

				sas_ex_disable_port(child, s2);
			पूर्ण
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण
/**
 * sas_ex_discover_devices - discover devices attached to this expander
 * @dev: poपूर्णांकer to the expander करोमुख्य device
 * @single: अगर you want to करो a single phy, अन्यथा set to -1;
 *
 * Configure this expander क्रम use with its devices and रेजिस्टर the
 * devices of this expander.
 */
अटल पूर्णांक sas_ex_discover_devices(काष्ठा करोमुख्य_device *dev, पूर्णांक single)
अणु
	काष्ठा expander_device *ex = &dev->ex_dev;
	पूर्णांक i = 0, end = ex->num_phys;
	पूर्णांक res = 0;

	अगर (0 <= single && single < end) अणु
		i = single;
		end = i+1;
	पूर्ण

	क्रम ( ; i < end; i++) अणु
		काष्ठा ex_phy *ex_phy = &ex->ex_phy[i];

		अगर (ex_phy->phy_state == PHY_VACANT ||
		    ex_phy->phy_state == PHY_NOT_PRESENT ||
		    ex_phy->phy_state == PHY_DEVICE_DISCOVERED)
			जारी;

		चयन (ex_phy->linkrate) अणु
		हाल SAS_PHY_DISABLED:
		हाल SAS_PHY_RESET_PROBLEM:
		हाल SAS_SATA_PORT_SELECTOR:
			जारी;
		शेष:
			res = sas_ex_discover_dev(dev, i);
			अगर (res)
				अवरोध;
			जारी;
		पूर्ण
	पूर्ण

	अगर (!res)
		sas_check_level_subtractive_boundary(dev);

	वापस res;
पूर्ण

अटल पूर्णांक sas_check_ex_subtractive_boundary(काष्ठा करोमुख्य_device *dev)
अणु
	काष्ठा expander_device *ex = &dev->ex_dev;
	पूर्णांक i;
	u8  *sub_sas_addr = शून्य;

	अगर (dev->dev_type != SAS_EDGE_EXPANDER_DEVICE)
		वापस 0;

	क्रम (i = 0; i < ex->num_phys; i++) अणु
		काष्ठा ex_phy *phy = &ex->ex_phy[i];

		अगर (phy->phy_state == PHY_VACANT ||
		    phy->phy_state == PHY_NOT_PRESENT)
			जारी;

		अगर (dev_is_expander(phy->attached_dev_type) &&
		    phy->routing_attr == SUBTRACTIVE_ROUTING) अणु

			अगर (!sub_sas_addr)
				sub_sas_addr = &phy->attached_sas_addr[0];
			अन्यथा अगर (SAS_ADDR(sub_sas_addr) !=
				 SAS_ADDR(phy->attached_sas_addr)) अणु

				pr_notice("ex %016llx phy%02d diverges(%016llx) on subtractive boundary(%016llx). Disabled\n",
					  SAS_ADDR(dev->sas_addr), i,
					  SAS_ADDR(phy->attached_sas_addr),
					  SAS_ADDR(sub_sas_addr));
				sas_ex_disable_phy(dev, i);
			पूर्ण
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम sas_prपूर्णांक_parent_topology_bug(काष्ठा करोमुख्य_device *child,
						 काष्ठा ex_phy *parent_phy,
						 काष्ठा ex_phy *child_phy)
अणु
	अटल स्थिर अक्षर *ex_type[] = अणु
		[SAS_EDGE_EXPANDER_DEVICE] = "edge",
		[SAS_FANOUT_EXPANDER_DEVICE] = "fanout",
	पूर्ण;
	काष्ठा करोमुख्य_device *parent = child->parent;

	pr_notice("%s ex %016llx phy%02d <--> %s ex %016llx phy%02d has %c:%c routing link!\n",
		  ex_type[parent->dev_type],
		  SAS_ADDR(parent->sas_addr),
		  parent_phy->phy_id,

		  ex_type[child->dev_type],
		  SAS_ADDR(child->sas_addr),
		  child_phy->phy_id,

		  sas_route_अक्षर(parent, parent_phy),
		  sas_route_अक्षर(child, child_phy));
पूर्ण

अटल पूर्णांक sas_check_eeds(काष्ठा करोमुख्य_device *child,
				 काष्ठा ex_phy *parent_phy,
				 काष्ठा ex_phy *child_phy)
अणु
	पूर्णांक res = 0;
	काष्ठा करोमुख्य_device *parent = child->parent;

	अगर (SAS_ADDR(parent->port->disc.fanout_sas_addr) != 0) अणु
		res = -ENODEV;
		pr_warn("edge ex %016llx phy S:%02d <--> edge ex %016llx phy S:%02d, while there is a fanout ex %016llx\n",
			SAS_ADDR(parent->sas_addr),
			parent_phy->phy_id,
			SAS_ADDR(child->sas_addr),
			child_phy->phy_id,
			SAS_ADDR(parent->port->disc.fanout_sas_addr));
	पूर्ण अन्यथा अगर (SAS_ADDR(parent->port->disc.eeds_a) == 0) अणु
		स_नकल(parent->port->disc.eeds_a, parent->sas_addr,
		       SAS_ADDR_SIZE);
		स_नकल(parent->port->disc.eeds_b, child->sas_addr,
		       SAS_ADDR_SIZE);
	पूर्ण अन्यथा अगर (((SAS_ADDR(parent->port->disc.eeds_a) ==
		    SAS_ADDR(parent->sas_addr)) ||
		   (SAS_ADDR(parent->port->disc.eeds_a) ==
		    SAS_ADDR(child->sas_addr)))
		   &&
		   ((SAS_ADDR(parent->port->disc.eeds_b) ==
		     SAS_ADDR(parent->sas_addr)) ||
		    (SAS_ADDR(parent->port->disc.eeds_b) ==
		     SAS_ADDR(child->sas_addr))))
		;
	अन्यथा अणु
		res = -ENODEV;
		pr_warn("edge ex %016llx phy%02d <--> edge ex %016llx phy%02d link forms a third EEDS!\n",
			SAS_ADDR(parent->sas_addr),
			parent_phy->phy_id,
			SAS_ADDR(child->sas_addr),
			child_phy->phy_id);
	पूर्ण

	वापस res;
पूर्ण

/* Here we spill over 80 columns.  It is पूर्णांकentional.
 */
अटल पूर्णांक sas_check_parent_topology(काष्ठा करोमुख्य_device *child)
अणु
	काष्ठा expander_device *child_ex = &child->ex_dev;
	काष्ठा expander_device *parent_ex;
	पूर्णांक i;
	पूर्णांक res = 0;

	अगर (!child->parent)
		वापस 0;

	अगर (!dev_is_expander(child->parent->dev_type))
		वापस 0;

	parent_ex = &child->parent->ex_dev;

	क्रम (i = 0; i < parent_ex->num_phys; i++) अणु
		काष्ठा ex_phy *parent_phy = &parent_ex->ex_phy[i];
		काष्ठा ex_phy *child_phy;

		अगर (parent_phy->phy_state == PHY_VACANT ||
		    parent_phy->phy_state == PHY_NOT_PRESENT)
			जारी;

		अगर (SAS_ADDR(parent_phy->attached_sas_addr) != SAS_ADDR(child->sas_addr))
			जारी;

		child_phy = &child_ex->ex_phy[parent_phy->attached_phy_id];

		चयन (child->parent->dev_type) अणु
		हाल SAS_EDGE_EXPANDER_DEVICE:
			अगर (child->dev_type == SAS_FANOUT_EXPANDER_DEVICE) अणु
				अगर (parent_phy->routing_attr != SUBTRACTIVE_ROUTING ||
				    child_phy->routing_attr != TABLE_ROUTING) अणु
					sas_prपूर्णांक_parent_topology_bug(child, parent_phy, child_phy);
					res = -ENODEV;
				पूर्ण
			पूर्ण अन्यथा अगर (parent_phy->routing_attr == SUBTRACTIVE_ROUTING) अणु
				अगर (child_phy->routing_attr == SUBTRACTIVE_ROUTING) अणु
					res = sas_check_eeds(child, parent_phy, child_phy);
				पूर्ण अन्यथा अगर (child_phy->routing_attr != TABLE_ROUTING) अणु
					sas_prपूर्णांक_parent_topology_bug(child, parent_phy, child_phy);
					res = -ENODEV;
				पूर्ण
			पूर्ण अन्यथा अगर (parent_phy->routing_attr == TABLE_ROUTING) अणु
				अगर (child_phy->routing_attr == SUBTRACTIVE_ROUTING ||
				    (child_phy->routing_attr == TABLE_ROUTING &&
				     child_ex->t2t_supp && parent_ex->t2t_supp)) अणु
					/* All good */;
				पूर्ण अन्यथा अणु
					sas_prपूर्णांक_parent_topology_bug(child, parent_phy, child_phy);
					res = -ENODEV;
				पूर्ण
			पूर्ण
			अवरोध;
		हाल SAS_FANOUT_EXPANDER_DEVICE:
			अगर (parent_phy->routing_attr != TABLE_ROUTING ||
			    child_phy->routing_attr != SUBTRACTIVE_ROUTING) अणु
				sas_prपूर्णांक_parent_topology_bug(child, parent_phy, child_phy);
				res = -ENODEV;
			पूर्ण
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण

	वापस res;
पूर्ण

#घोषणा RRI_REQ_SIZE  16
#घोषणा RRI_RESP_SIZE 44

अटल पूर्णांक sas_configure_present(काष्ठा करोमुख्य_device *dev, पूर्णांक phy_id,
				 u8 *sas_addr, पूर्णांक *index, पूर्णांक *present)
अणु
	पूर्णांक i, res = 0;
	काष्ठा expander_device *ex = &dev->ex_dev;
	काष्ठा ex_phy *phy = &ex->ex_phy[phy_id];
	u8 *rri_req;
	u8 *rri_resp;

	*present = 0;
	*index = 0;

	rri_req = alloc_smp_req(RRI_REQ_SIZE);
	अगर (!rri_req)
		वापस -ENOMEM;

	rri_resp = alloc_smp_resp(RRI_RESP_SIZE);
	अगर (!rri_resp) अणु
		kमुक्त(rri_req);
		वापस -ENOMEM;
	पूर्ण

	rri_req[1] = SMP_REPORT_ROUTE_INFO;
	rri_req[9] = phy_id;

	क्रम (i = 0; i < ex->max_route_indexes ; i++) अणु
		*(__be16 *)(rri_req+6) = cpu_to_be16(i);
		res = smp_execute_task(dev, rri_req, RRI_REQ_SIZE, rri_resp,
				       RRI_RESP_SIZE);
		अगर (res)
			जाओ out;
		res = rri_resp[2];
		अगर (res == SMP_RESP_NO_INDEX) अणु
			pr_warn("overflow of indexes: dev %016llx phy%02d index 0x%x\n",
				SAS_ADDR(dev->sas_addr), phy_id, i);
			जाओ out;
		पूर्ण अन्यथा अगर (res != SMP_RESP_FUNC_ACC) अणु
			pr_notice("%s: dev %016llx phy%02d index 0x%x result 0x%x\n",
				  __func__, SAS_ADDR(dev->sas_addr), phy_id,
				  i, res);
			जाओ out;
		पूर्ण
		अगर (SAS_ADDR(sas_addr) != 0) अणु
			अगर (SAS_ADDR(rri_resp+16) == SAS_ADDR(sas_addr)) अणु
				*index = i;
				अगर ((rri_resp[12] & 0x80) == 0x80)
					*present = 0;
				अन्यथा
					*present = 1;
				जाओ out;
			पूर्ण अन्यथा अगर (SAS_ADDR(rri_resp+16) == 0) अणु
				*index = i;
				*present = 0;
				जाओ out;
			पूर्ण
		पूर्ण अन्यथा अगर (SAS_ADDR(rri_resp+16) == 0 &&
			   phy->last_da_index < i) अणु
			phy->last_da_index = i;
			*index = i;
			*present = 0;
			जाओ out;
		पूर्ण
	पूर्ण
	res = -1;
out:
	kमुक्त(rri_req);
	kमुक्त(rri_resp);
	वापस res;
पूर्ण

#घोषणा CRI_REQ_SIZE  44
#घोषणा CRI_RESP_SIZE  8

अटल पूर्णांक sas_configure_set(काष्ठा करोमुख्य_device *dev, पूर्णांक phy_id,
			     u8 *sas_addr, पूर्णांक index, पूर्णांक include)
अणु
	पूर्णांक res;
	u8 *cri_req;
	u8 *cri_resp;

	cri_req = alloc_smp_req(CRI_REQ_SIZE);
	अगर (!cri_req)
		वापस -ENOMEM;

	cri_resp = alloc_smp_resp(CRI_RESP_SIZE);
	अगर (!cri_resp) अणु
		kमुक्त(cri_req);
		वापस -ENOMEM;
	पूर्ण

	cri_req[1] = SMP_CONF_ROUTE_INFO;
	*(__be16 *)(cri_req+6) = cpu_to_be16(index);
	cri_req[9] = phy_id;
	अगर (SAS_ADDR(sas_addr) == 0 || !include)
		cri_req[12] |= 0x80;
	स_नकल(cri_req+16, sas_addr, SAS_ADDR_SIZE);

	res = smp_execute_task(dev, cri_req, CRI_REQ_SIZE, cri_resp,
			       CRI_RESP_SIZE);
	अगर (res)
		जाओ out;
	res = cri_resp[2];
	अगर (res == SMP_RESP_NO_INDEX) अणु
		pr_warn("overflow of indexes: dev %016llx phy%02d index 0x%x\n",
			SAS_ADDR(dev->sas_addr), phy_id, index);
	पूर्ण
out:
	kमुक्त(cri_req);
	kमुक्त(cri_resp);
	वापस res;
पूर्ण

अटल पूर्णांक sas_configure_phy(काष्ठा करोमुख्य_device *dev, पूर्णांक phy_id,
				    u8 *sas_addr, पूर्णांक include)
अणु
	पूर्णांक index;
	पूर्णांक present;
	पूर्णांक res;

	res = sas_configure_present(dev, phy_id, sas_addr, &index, &present);
	अगर (res)
		वापस res;
	अगर (include ^ present)
		वापस sas_configure_set(dev, phy_id, sas_addr, index,
					 include);

	वापस res;
पूर्ण

/**
 * sas_configure_parent - configure routing table of parent
 * @parent: parent expander
 * @child: child expander
 * @sas_addr: SAS port identअगरier of device directly attached to child
 * @include: whether or not to include @child in the expander routing table
 */
अटल पूर्णांक sas_configure_parent(काष्ठा करोमुख्य_device *parent,
				काष्ठा करोमुख्य_device *child,
				u8 *sas_addr, पूर्णांक include)
अणु
	काष्ठा expander_device *ex_parent = &parent->ex_dev;
	पूर्णांक res = 0;
	पूर्णांक i;

	अगर (parent->parent) अणु
		res = sas_configure_parent(parent->parent, parent, sas_addr,
					   include);
		अगर (res)
			वापस res;
	पूर्ण

	अगर (ex_parent->conf_route_table == 0) अणु
		pr_debug("ex %016llx has self-configuring routing table\n",
			 SAS_ADDR(parent->sas_addr));
		वापस 0;
	पूर्ण

	क्रम (i = 0; i < ex_parent->num_phys; i++) अणु
		काष्ठा ex_phy *phy = &ex_parent->ex_phy[i];

		अगर ((phy->routing_attr == TABLE_ROUTING) &&
		    (SAS_ADDR(phy->attached_sas_addr) ==
		     SAS_ADDR(child->sas_addr))) अणु
			res = sas_configure_phy(parent, i, sas_addr, include);
			अगर (res)
				वापस res;
		पूर्ण
	पूर्ण

	वापस res;
पूर्ण

/**
 * sas_configure_routing - configure routing
 * @dev: expander device
 * @sas_addr: port identअगरier of device directly attached to the expander device
 */
अटल पूर्णांक sas_configure_routing(काष्ठा करोमुख्य_device *dev, u8 *sas_addr)
अणु
	अगर (dev->parent)
		वापस sas_configure_parent(dev->parent, dev, sas_addr, 1);
	वापस 0;
पूर्ण

अटल पूर्णांक sas_disable_routing(काष्ठा करोमुख्य_device *dev,  u8 *sas_addr)
अणु
	अगर (dev->parent)
		वापस sas_configure_parent(dev->parent, dev, sas_addr, 0);
	वापस 0;
पूर्ण

/**
 * sas_discover_expander - expander discovery
 * @dev: poपूर्णांकer to expander करोमुख्य device
 *
 * See comment in sas_discover_sata().
 */
अटल पूर्णांक sas_discover_expander(काष्ठा करोमुख्य_device *dev)
अणु
	पूर्णांक res;

	res = sas_notअगरy_lldd_dev_found(dev);
	अगर (res)
		वापस res;

	res = sas_ex_general(dev);
	अगर (res)
		जाओ out_err;
	res = sas_ex_manuf_info(dev);
	अगर (res)
		जाओ out_err;

	res = sas_expander_discover(dev);
	अगर (res) अणु
		pr_warn("expander %016llx discovery failed(0x%x)\n",
			SAS_ADDR(dev->sas_addr), res);
		जाओ out_err;
	पूर्ण

	sas_check_ex_subtractive_boundary(dev);
	res = sas_check_parent_topology(dev);
	अगर (res)
		जाओ out_err;
	वापस 0;
out_err:
	sas_notअगरy_lldd_dev_gone(dev);
	वापस res;
पूर्ण

अटल पूर्णांक sas_ex_level_discovery(काष्ठा asd_sas_port *port, स्थिर पूर्णांक level)
अणु
	पूर्णांक res = 0;
	काष्ठा करोमुख्य_device *dev;

	list_क्रम_each_entry(dev, &port->dev_list, dev_list_node) अणु
		अगर (dev_is_expander(dev->dev_type)) अणु
			काष्ठा sas_expander_device *ex =
				rphy_to_expander_device(dev->rphy);

			अगर (level == ex->level)
				res = sas_ex_discover_devices(dev, -1);
			अन्यथा अगर (level > 0)
				res = sas_ex_discover_devices(port->port_dev, -1);

		पूर्ण
	पूर्ण

	वापस res;
पूर्ण

अटल पूर्णांक sas_ex_bfs_disc(काष्ठा asd_sas_port *port)
अणु
	पूर्णांक res;
	पूर्णांक level;

	करो अणु
		level = port->disc.max_level;
		res = sas_ex_level_discovery(port, level);
		mb();
	पूर्ण जबतक (level < port->disc.max_level);

	वापस res;
पूर्ण

पूर्णांक sas_discover_root_expander(काष्ठा करोमुख्य_device *dev)
अणु
	पूर्णांक res;
	काष्ठा sas_expander_device *ex = rphy_to_expander_device(dev->rphy);

	res = sas_rphy_add(dev->rphy);
	अगर (res)
		जाओ out_err;

	ex->level = dev->port->disc.max_level; /* 0 */
	res = sas_discover_expander(dev);
	अगर (res)
		जाओ out_err2;

	sas_ex_bfs_disc(dev->port);

	वापस res;

out_err2:
	sas_rphy_हटाओ(dev->rphy);
out_err:
	वापस res;
पूर्ण

/* ---------- Doमुख्य revalidation ---------- */

अटल पूर्णांक sas_get_phy_discover(काष्ठा करोमुख्य_device *dev,
				पूर्णांक phy_id, काष्ठा smp_resp *disc_resp)
अणु
	पूर्णांक res;
	u8 *disc_req;

	disc_req = alloc_smp_req(DISCOVER_REQ_SIZE);
	अगर (!disc_req)
		वापस -ENOMEM;

	disc_req[1] = SMP_DISCOVER;
	disc_req[9] = phy_id;

	res = smp_execute_task(dev, disc_req, DISCOVER_REQ_SIZE,
			       disc_resp, DISCOVER_RESP_SIZE);
	अगर (res)
		जाओ out;
	अन्यथा अगर (disc_resp->result != SMP_RESP_FUNC_ACC) अणु
		res = disc_resp->result;
		जाओ out;
	पूर्ण
out:
	kमुक्त(disc_req);
	वापस res;
पूर्ण

अटल पूर्णांक sas_get_phy_change_count(काष्ठा करोमुख्य_device *dev,
				    पूर्णांक phy_id, पूर्णांक *pcc)
अणु
	पूर्णांक res;
	काष्ठा smp_resp *disc_resp;

	disc_resp = alloc_smp_resp(DISCOVER_RESP_SIZE);
	अगर (!disc_resp)
		वापस -ENOMEM;

	res = sas_get_phy_discover(dev, phy_id, disc_resp);
	अगर (!res)
		*pcc = disc_resp->disc.change_count;

	kमुक्त(disc_resp);
	वापस res;
पूर्ण

अटल पूर्णांक sas_get_phy_attached_dev(काष्ठा करोमुख्य_device *dev, पूर्णांक phy_id,
				    u8 *sas_addr, क्रमागत sas_device_type *type)
अणु
	पूर्णांक res;
	काष्ठा smp_resp *disc_resp;
	काष्ठा discover_resp *dr;

	disc_resp = alloc_smp_resp(DISCOVER_RESP_SIZE);
	अगर (!disc_resp)
		वापस -ENOMEM;
	dr = &disc_resp->disc;

	res = sas_get_phy_discover(dev, phy_id, disc_resp);
	अगर (res == 0) अणु
		स_नकल(sas_addr, disc_resp->disc.attached_sas_addr,
		       SAS_ADDR_SIZE);
		*type = to_dev_type(dr);
		अगर (*type == 0)
			स_रखो(sas_addr, 0, SAS_ADDR_SIZE);
	पूर्ण
	kमुक्त(disc_resp);
	वापस res;
पूर्ण

अटल पूर्णांक sas_find_bcast_phy(काष्ठा करोमुख्य_device *dev, पूर्णांक *phy_id,
			      पूर्णांक from_phy, bool update)
अणु
	काष्ठा expander_device *ex = &dev->ex_dev;
	पूर्णांक res = 0;
	पूर्णांक i;

	क्रम (i = from_phy; i < ex->num_phys; i++) अणु
		पूर्णांक phy_change_count = 0;

		res = sas_get_phy_change_count(dev, i, &phy_change_count);
		चयन (res) अणु
		हाल SMP_RESP_PHY_VACANT:
		हाल SMP_RESP_NO_PHY:
			जारी;
		हाल SMP_RESP_FUNC_ACC:
			अवरोध;
		शेष:
			वापस res;
		पूर्ण

		अगर (phy_change_count != ex->ex_phy[i].phy_change_count) अणु
			अगर (update)
				ex->ex_phy[i].phy_change_count =
					phy_change_count;
			*phy_id = i;
			वापस 0;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक sas_get_ex_change_count(काष्ठा करोमुख्य_device *dev, पूर्णांक *ecc)
अणु
	पूर्णांक res;
	u8  *rg_req;
	काष्ठा smp_resp  *rg_resp;

	rg_req = alloc_smp_req(RG_REQ_SIZE);
	अगर (!rg_req)
		वापस -ENOMEM;

	rg_resp = alloc_smp_resp(RG_RESP_SIZE);
	अगर (!rg_resp) अणु
		kमुक्त(rg_req);
		वापस -ENOMEM;
	पूर्ण

	rg_req[1] = SMP_REPORT_GENERAL;

	res = smp_execute_task(dev, rg_req, RG_REQ_SIZE, rg_resp,
			       RG_RESP_SIZE);
	अगर (res)
		जाओ out;
	अगर (rg_resp->result != SMP_RESP_FUNC_ACC) अणु
		res = rg_resp->result;
		जाओ out;
	पूर्ण

	*ecc = be16_to_cpu(rg_resp->rg.change_count);
out:
	kमुक्त(rg_resp);
	kमुक्त(rg_req);
	वापस res;
पूर्ण
/**
 * sas_find_bcast_dev -  find the device issue BROADCAST(CHANGE).
 * @dev:करोमुख्य device to be detect.
 * @src_dev: the device which originated BROADCAST(CHANGE).
 *
 * Add self-configuration expander support. Suppose two expander cascading,
 * when the first level expander is self-configuring, hotplug the disks in
 * second level expander, BROADCAST(CHANGE) will not only be originated
 * in the second level expander, but also be originated in the first level
 * expander (see SAS protocol SAS 2r-14, 7.11 क्रम detail), it is to say,
 * expander changed count in two level expanders will all increment at least
 * once, but the phy which chang count has changed is the source device which
 * we concerned.
 */

अटल पूर्णांक sas_find_bcast_dev(काष्ठा करोमुख्य_device *dev,
			      काष्ठा करोमुख्य_device **src_dev)
अणु
	काष्ठा expander_device *ex = &dev->ex_dev;
	पूर्णांक ex_change_count = -1;
	पूर्णांक phy_id = -1;
	पूर्णांक res;
	काष्ठा करोमुख्य_device *ch;

	res = sas_get_ex_change_count(dev, &ex_change_count);
	अगर (res)
		जाओ out;
	अगर (ex_change_count != -1 && ex_change_count != ex->ex_change_count) अणु
		/* Just detect अगर this expander phys phy change count changed,
		* in order to determine अगर this expander originate BROADCAST,
		* and करो not update phy change count field in our काष्ठाure.
		*/
		res = sas_find_bcast_phy(dev, &phy_id, 0, false);
		अगर (phy_id != -1) अणु
			*src_dev = dev;
			ex->ex_change_count = ex_change_count;
			pr_info("ex %016llx phy%02d change count has changed\n",
				SAS_ADDR(dev->sas_addr), phy_id);
			वापस res;
		पूर्ण अन्यथा
			pr_info("ex %016llx phys DID NOT change\n",
				SAS_ADDR(dev->sas_addr));
	पूर्ण
	list_क्रम_each_entry(ch, &ex->children, siblings) अणु
		अगर (dev_is_expander(ch->dev_type)) अणु
			res = sas_find_bcast_dev(ch, src_dev);
			अगर (*src_dev)
				वापस res;
		पूर्ण
	पूर्ण
out:
	वापस res;
पूर्ण

अटल व्योम sas_unरेजिस्टर_ex_tree(काष्ठा asd_sas_port *port, काष्ठा करोमुख्य_device *dev)
अणु
	काष्ठा expander_device *ex = &dev->ex_dev;
	काष्ठा करोमुख्य_device *child, *n;

	list_क्रम_each_entry_safe(child, n, &ex->children, siblings) अणु
		set_bit(SAS_DEV_GONE, &child->state);
		अगर (dev_is_expander(child->dev_type))
			sas_unरेजिस्टर_ex_tree(port, child);
		अन्यथा
			sas_unरेजिस्टर_dev(port, child);
	पूर्ण
	sas_unरेजिस्टर_dev(port, dev);
पूर्ण

अटल व्योम sas_unरेजिस्टर_devs_sas_addr(काष्ठा करोमुख्य_device *parent,
					 पूर्णांक phy_id, bool last)
अणु
	काष्ठा expander_device *ex_dev = &parent->ex_dev;
	काष्ठा ex_phy *phy = &ex_dev->ex_phy[phy_id];
	काष्ठा करोमुख्य_device *child, *n, *found = शून्य;
	अगर (last) अणु
		list_क्रम_each_entry_safe(child, n,
			&ex_dev->children, siblings) अणु
			अगर (SAS_ADDR(child->sas_addr) ==
			    SAS_ADDR(phy->attached_sas_addr)) अणु
				set_bit(SAS_DEV_GONE, &child->state);
				अगर (dev_is_expander(child->dev_type))
					sas_unरेजिस्टर_ex_tree(parent->port, child);
				अन्यथा
					sas_unरेजिस्टर_dev(parent->port, child);
				found = child;
				अवरोध;
			पूर्ण
		पूर्ण
		sas_disable_routing(parent, phy->attached_sas_addr);
	पूर्ण
	स_रखो(phy->attached_sas_addr, 0, SAS_ADDR_SIZE);
	अगर (phy->port) अणु
		sas_port_delete_phy(phy->port, phy->phy);
		sas_device_set_phy(found, phy->port);
		अगर (phy->port->num_phys == 0)
			list_add_tail(&phy->port->del_list,
				&parent->port->sas_port_del_list);
		phy->port = शून्य;
	पूर्ण
पूर्ण

अटल पूर्णांक sas_discover_bfs_by_root_level(काष्ठा करोमुख्य_device *root,
					  स्थिर पूर्णांक level)
अणु
	काष्ठा expander_device *ex_root = &root->ex_dev;
	काष्ठा करोमुख्य_device *child;
	पूर्णांक res = 0;

	list_क्रम_each_entry(child, &ex_root->children, siblings) अणु
		अगर (dev_is_expander(child->dev_type)) अणु
			काष्ठा sas_expander_device *ex =
				rphy_to_expander_device(child->rphy);

			अगर (level > ex->level)
				res = sas_discover_bfs_by_root_level(child,
								     level);
			अन्यथा अगर (level == ex->level)
				res = sas_ex_discover_devices(child, -1);
		पूर्ण
	पूर्ण
	वापस res;
पूर्ण

अटल पूर्णांक sas_discover_bfs_by_root(काष्ठा करोमुख्य_device *dev)
अणु
	पूर्णांक res;
	काष्ठा sas_expander_device *ex = rphy_to_expander_device(dev->rphy);
	पूर्णांक level = ex->level+1;

	res = sas_ex_discover_devices(dev, -1);
	अगर (res)
		जाओ out;
	करो अणु
		res = sas_discover_bfs_by_root_level(dev, level);
		mb();
		level += 1;
	पूर्ण जबतक (level <= dev->port->disc.max_level);
out:
	वापस res;
पूर्ण

अटल पूर्णांक sas_discover_new(काष्ठा करोमुख्य_device *dev, पूर्णांक phy_id)
अणु
	काष्ठा ex_phy *ex_phy = &dev->ex_dev.ex_phy[phy_id];
	काष्ठा करोमुख्य_device *child;
	पूर्णांक res;

	pr_debug("ex %016llx phy%02d new device attached\n",
		 SAS_ADDR(dev->sas_addr), phy_id);
	res = sas_ex_phy_discover(dev, phy_id);
	अगर (res)
		वापस res;

	अगर (sas_ex_join_wide_port(dev, phy_id))
		वापस 0;

	res = sas_ex_discover_devices(dev, phy_id);
	अगर (res)
		वापस res;
	list_क्रम_each_entry(child, &dev->ex_dev.children, siblings) अणु
		अगर (SAS_ADDR(child->sas_addr) ==
		    SAS_ADDR(ex_phy->attached_sas_addr)) अणु
			अगर (dev_is_expander(child->dev_type))
				res = sas_discover_bfs_by_root(child);
			अवरोध;
		पूर्ण
	पूर्ण
	वापस res;
पूर्ण

अटल bool dev_type_flutter(क्रमागत sas_device_type new, क्रमागत sas_device_type old)
अणु
	अगर (old == new)
		वापस true;

	/* treat device directed resets as flutter, अगर we went
	 * SAS_END_DEVICE to SAS_SATA_PENDING the link needs recovery
	 */
	अगर ((old == SAS_SATA_PENDING && new == SAS_END_DEVICE) ||
	    (old == SAS_END_DEVICE && new == SAS_SATA_PENDING))
		वापस true;

	वापस false;
पूर्ण

अटल पूर्णांक sas_rediscover_dev(काष्ठा करोमुख्य_device *dev, पूर्णांक phy_id,
			      bool last, पूर्णांक sibling)
अणु
	काष्ठा expander_device *ex = &dev->ex_dev;
	काष्ठा ex_phy *phy = &ex->ex_phy[phy_id];
	क्रमागत sas_device_type type = SAS_PHY_UNUSED;
	u8 sas_addr[SAS_ADDR_SIZE];
	अक्षर msg[80] = "";
	पूर्णांक res;

	अगर (!last)
		प्र_लिखो(msg, ", part of a wide port with phy%02d", sibling);

	pr_debug("ex %016llx rediscovering phy%02d%s\n",
		 SAS_ADDR(dev->sas_addr), phy_id, msg);

	स_रखो(sas_addr, 0, SAS_ADDR_SIZE);
	res = sas_get_phy_attached_dev(dev, phy_id, sas_addr, &type);
	चयन (res) अणु
	हाल SMP_RESP_NO_PHY:
		phy->phy_state = PHY_NOT_PRESENT;
		sas_unरेजिस्टर_devs_sas_addr(dev, phy_id, last);
		वापस res;
	हाल SMP_RESP_PHY_VACANT:
		phy->phy_state = PHY_VACANT;
		sas_unरेजिस्टर_devs_sas_addr(dev, phy_id, last);
		वापस res;
	हाल SMP_RESP_FUNC_ACC:
		अवरोध;
	हाल -ECOMM:
		अवरोध;
	शेष:
		वापस res;
	पूर्ण

	अगर ((SAS_ADDR(sas_addr) == 0) || (res == -ECOMM)) अणु
		phy->phy_state = PHY_EMPTY;
		sas_unरेजिस्टर_devs_sas_addr(dev, phy_id, last);
		/*
		 * Even though the PHY is empty, क्रम convenience we discover
		 * the PHY to update the PHY info, like negotiated linkrate.
		 */
		sas_ex_phy_discover(dev, phy_id);
		वापस res;
	पूर्ण अन्यथा अगर (SAS_ADDR(sas_addr) == SAS_ADDR(phy->attached_sas_addr) &&
		   dev_type_flutter(type, phy->attached_dev_type)) अणु
		काष्ठा करोमुख्य_device *ata_dev = sas_ex_to_ata(dev, phy_id);
		अक्षर *action = "";

		sas_ex_phy_discover(dev, phy_id);

		अगर (ata_dev && phy->attached_dev_type == SAS_SATA_PENDING)
			action = ", needs recovery";
		pr_debug("ex %016llx phy%02d broadcast flutter%s\n",
			 SAS_ADDR(dev->sas_addr), phy_id, action);
		वापस res;
	पूर्ण

	/* we always have to delete the old device when we went here */
	pr_info("ex %016llx phy%02d replace %016llx\n",
		SAS_ADDR(dev->sas_addr), phy_id,
		SAS_ADDR(phy->attached_sas_addr));
	sas_unरेजिस्टर_devs_sas_addr(dev, phy_id, last);

	वापस sas_discover_new(dev, phy_id);
पूर्ण

/**
 * sas_rediscover - revalidate the करोमुख्य.
 * @dev:करोमुख्य device to be detect.
 * @phy_id: the phy id will be detected.
 *
 * NOTE: this process _must_ quit (वापस) as soon as any connection
 * errors are encountered.  Connection recovery is करोne अन्यथाwhere.
 * Discover process only पूर्णांकerrogates devices in order to discover the
 * करोमुख्य.For plugging out, we un-रेजिस्टर the device only when it is
 * the last phy in the port, क्रम other phys in this port, we just delete it
 * from the port.For inserting, we करो discovery when it is the
 * first phy,क्रम other phys in this port, we add it to the port to
 * क्रमming the wide-port.
 */
अटल पूर्णांक sas_rediscover(काष्ठा करोमुख्य_device *dev, स्थिर पूर्णांक phy_id)
अणु
	काष्ठा expander_device *ex = &dev->ex_dev;
	काष्ठा ex_phy *changed_phy = &ex->ex_phy[phy_id];
	पूर्णांक res = 0;
	पूर्णांक i;
	bool last = true;	/* is this the last phy of the port */

	pr_debug("ex %016llx phy%02d originated BROADCAST(CHANGE)\n",
		 SAS_ADDR(dev->sas_addr), phy_id);

	अगर (SAS_ADDR(changed_phy->attached_sas_addr) != 0) अणु
		क्रम (i = 0; i < ex->num_phys; i++) अणु
			काष्ठा ex_phy *phy = &ex->ex_phy[i];

			अगर (i == phy_id)
				जारी;
			अगर (SAS_ADDR(phy->attached_sas_addr) ==
			    SAS_ADDR(changed_phy->attached_sas_addr)) अणु
				last = false;
				अवरोध;
			पूर्ण
		पूर्ण
		res = sas_rediscover_dev(dev, phy_id, last, i);
	पूर्ण अन्यथा
		res = sas_discover_new(dev, phy_id);
	वापस res;
पूर्ण

/**
 * sas_ex_revalidate_करोमुख्य - revalidate the करोमुख्य
 * @port_dev: port करोमुख्य device.
 *
 * NOTE: this process _must_ quit (वापस) as soon as any connection
 * errors are encountered.  Connection recovery is करोne अन्यथाwhere.
 * Discover process only पूर्णांकerrogates devices in order to discover the
 * करोमुख्य.
 */
पूर्णांक sas_ex_revalidate_करोमुख्य(काष्ठा करोमुख्य_device *port_dev)
अणु
	पूर्णांक res;
	काष्ठा करोमुख्य_device *dev = शून्य;

	res = sas_find_bcast_dev(port_dev, &dev);
	अगर (res == 0 && dev) अणु
		काष्ठा expander_device *ex = &dev->ex_dev;
		पूर्णांक i = 0, phy_id;

		करो अणु
			phy_id = -1;
			res = sas_find_bcast_phy(dev, &phy_id, i, true);
			अगर (phy_id == -1)
				अवरोध;
			res = sas_rediscover(dev, phy_id);
			i = phy_id + 1;
		पूर्ण जबतक (i < ex->num_phys);
	पूर्ण
	वापस res;
पूर्ण

व्योम sas_smp_handler(काष्ठा bsg_job *job, काष्ठा Scsi_Host *shost,
		काष्ठा sas_rphy *rphy)
अणु
	काष्ठा करोमुख्य_device *dev;
	अचिन्हित पूर्णांक rcvlen = 0;
	पूर्णांक ret = -EINVAL;

	/* no rphy means no smp target support (ie aic94xx host) */
	अगर (!rphy)
		वापस sas_smp_host_handler(job, shost);

	चयन (rphy->identअगरy.device_type) अणु
	हाल SAS_EDGE_EXPANDER_DEVICE:
	हाल SAS_FANOUT_EXPANDER_DEVICE:
		अवरोध;
	शेष:
		pr_err("%s: can we send a smp request to a device?\n",
		       __func__);
		जाओ out;
	पूर्ण

	dev = sas_find_dev_by_rphy(rphy);
	अगर (!dev) अणु
		pr_err("%s: fail to find a domain_device?\n", __func__);
		जाओ out;
	पूर्ण

	/* करो we need to support multiple segments? */
	अगर (job->request_payload.sg_cnt > 1 ||
	    job->reply_payload.sg_cnt > 1) अणु
		pr_info("%s: multiple segments req %u, rsp %u\n",
			__func__, job->request_payload.payload_len,
			job->reply_payload.payload_len);
		जाओ out;
	पूर्ण

	ret = smp_execute_task_sg(dev, job->request_payload.sg_list,
			job->reply_payload.sg_list);
	अगर (ret >= 0) अणु
		/* bsg_job_करोne() requires the length received  */
		rcvlen = job->reply_payload.payload_len - ret;
		ret = 0;
	पूर्ण

out:
	bsg_job_करोne(job, ret, rcvlen);
पूर्ण
