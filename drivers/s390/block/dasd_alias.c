<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * PAV alias management क्रम the DASD ECKD discipline
 *
 * Copyright IBM Corp. 2007
 * Author(s): Stefan Weinhuber <wein@de.ibm.com>
 */

#घोषणा KMSG_COMPONENT "dasd-eckd"

#समावेश <linux/list.h>
#समावेश <linux/slab.h>
#समावेश <यंत्र/ebcdic.h>
#समावेश "dasd_int.h"
#समावेश "dasd_eckd.h"

#अगर_घोषित PRINTK_HEADER
#अघोषित PRINTK_HEADER
#पूर्ण_अगर				/* PRINTK_HEADER */
#घोषणा PRINTK_HEADER "dasd(eckd):"


/*
 * General concept of alias management:
 * - PAV and DASD alias management is specअगरic to the eckd discipline.
 * - A device is connected to an lcu as दीर्घ as the device exists.
 *   dasd_alias_make_device_known_to_lcu will be called wenn the
 *   device is checked by the eckd discipline and
 *   dasd_alias_disconnect_device_from_lcu will be called
 *   beक्रमe the device is deleted.
 * - The dasd_alias_add_device / dasd_alias_हटाओ_device
 *   functions mark the poपूर्णांक when a device is 'ready for service'.
 * - A summary unit check is a rare occasion, but it is mandatory to
 *   support it. It requires some complex recovery actions beक्रमe the
 *   devices can be used again (see dasd_alias_handle_summary_unit_check).
 * - dasd_alias_get_start_dev will find an alias device that can be used
 *   instead of the base device and करोes some (very simple) load balancing.
 *   This is the function that माला_लो called क्रम each I/O, so when improving
 *   something, this function should get faster or better, the rest has just
 *   to be correct.
 */


अटल व्योम summary_unit_check_handling_work(काष्ठा work_काष्ठा *);
अटल व्योम lcu_update_work(काष्ठा work_काष्ठा *);
अटल पूर्णांक _schedule_lcu_update(काष्ठा alias_lcu *, काष्ठा dasd_device *);

अटल काष्ठा alias_root aliastree = अणु
	.serverlist = LIST_HEAD_INIT(aliastree.serverlist),
	.lock = __SPIN_LOCK_UNLOCKED(aliastree.lock),
पूर्ण;

अटल काष्ठा alias_server *_find_server(काष्ठा dasd_uid *uid)
अणु
	काष्ठा alias_server *pos;
	list_क्रम_each_entry(pos, &aliastree.serverlist, server) अणु
		अगर (!म_भेदन(pos->uid.venकरोr, uid->venकरोr,
			     माप(uid->venकरोr))
		    && !म_भेदन(pos->uid.serial, uid->serial,
				माप(uid->serial)))
			वापस pos;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल काष्ठा alias_lcu *_find_lcu(काष्ठा alias_server *server,
				   काष्ठा dasd_uid *uid)
अणु
	काष्ठा alias_lcu *pos;
	list_क्रम_each_entry(pos, &server->lculist, lcu) अणु
		अगर (pos->uid.ssid == uid->ssid)
			वापस pos;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल काष्ठा alias_pav_group *_find_group(काष्ठा alias_lcu *lcu,
					   काष्ठा dasd_uid *uid)
अणु
	काष्ठा alias_pav_group *pos;
	__u8 search_unit_addr;

	/* क्रम hyper pav there is only one group */
	अगर (lcu->pav == HYPER_PAV) अणु
		अगर (list_empty(&lcu->grouplist))
			वापस शून्य;
		अन्यथा
			वापस list_first_entry(&lcu->grouplist,
						काष्ठा alias_pav_group, group);
	पूर्ण

	/* क्रम base pav we have to find the group that matches the base */
	अगर (uid->type == UA_BASE_DEVICE)
		search_unit_addr = uid->real_unit_addr;
	अन्यथा
		search_unit_addr = uid->base_unit_addr;
	list_क्रम_each_entry(pos, &lcu->grouplist, group) अणु
		अगर (pos->uid.base_unit_addr == search_unit_addr &&
		    !म_भेदन(pos->uid.vduit, uid->vduit, माप(uid->vduit)))
			वापस pos;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल काष्ठा alias_server *_allocate_server(काष्ठा dasd_uid *uid)
अणु
	काष्ठा alias_server *server;

	server = kzalloc(माप(*server), GFP_KERNEL);
	अगर (!server)
		वापस ERR_PTR(-ENOMEM);
	स_नकल(server->uid.venकरोr, uid->venकरोr, माप(uid->venकरोr));
	स_नकल(server->uid.serial, uid->serial, माप(uid->serial));
	INIT_LIST_HEAD(&server->server);
	INIT_LIST_HEAD(&server->lculist);
	वापस server;
पूर्ण

अटल व्योम _मुक्त_server(काष्ठा alias_server *server)
अणु
	kमुक्त(server);
पूर्ण

अटल काष्ठा alias_lcu *_allocate_lcu(काष्ठा dasd_uid *uid)
अणु
	काष्ठा alias_lcu *lcu;

	lcu = kzalloc(माप(*lcu), GFP_KERNEL);
	अगर (!lcu)
		वापस ERR_PTR(-ENOMEM);
	lcu->uac = kzalloc(माप(*(lcu->uac)), GFP_KERNEL | GFP_DMA);
	अगर (!lcu->uac)
		जाओ out_err1;
	lcu->rsu_cqr = kzalloc(माप(*lcu->rsu_cqr), GFP_KERNEL | GFP_DMA);
	अगर (!lcu->rsu_cqr)
		जाओ out_err2;
	lcu->rsu_cqr->cpaddr = kzalloc(माप(काष्ठा ccw1),
				       GFP_KERNEL | GFP_DMA);
	अगर (!lcu->rsu_cqr->cpaddr)
		जाओ out_err3;
	lcu->rsu_cqr->data = kzalloc(16, GFP_KERNEL | GFP_DMA);
	अगर (!lcu->rsu_cqr->data)
		जाओ out_err4;

	स_नकल(lcu->uid.venकरोr, uid->venकरोr, माप(uid->venकरोr));
	स_नकल(lcu->uid.serial, uid->serial, माप(uid->serial));
	lcu->uid.ssid = uid->ssid;
	lcu->pav = NO_PAV;
	lcu->flags = NEED_UAC_UPDATE | UPDATE_PENDING;
	INIT_LIST_HEAD(&lcu->lcu);
	INIT_LIST_HEAD(&lcu->inactive_devices);
	INIT_LIST_HEAD(&lcu->active_devices);
	INIT_LIST_HEAD(&lcu->grouplist);
	INIT_WORK(&lcu->suc_data.worker, summary_unit_check_handling_work);
	INIT_DELAYED_WORK(&lcu->ruac_data.dwork, lcu_update_work);
	spin_lock_init(&lcu->lock);
	init_completion(&lcu->lcu_setup);
	वापस lcu;

out_err4:
	kमुक्त(lcu->rsu_cqr->cpaddr);
out_err3:
	kमुक्त(lcu->rsu_cqr);
out_err2:
	kमुक्त(lcu->uac);
out_err1:
	kमुक्त(lcu);
	वापस ERR_PTR(-ENOMEM);
पूर्ण

अटल व्योम _मुक्त_lcu(काष्ठा alias_lcu *lcu)
अणु
	kमुक्त(lcu->rsu_cqr->data);
	kमुक्त(lcu->rsu_cqr->cpaddr);
	kमुक्त(lcu->rsu_cqr);
	kमुक्त(lcu->uac);
	kमुक्त(lcu);
पूर्ण

/*
 * This is the function that will allocate all the server and lcu data,
 * so this function must be called first क्रम a new device.
 * If the वापस value is 1, the lcu was alपढ़ोy known beक्रमe, अगर it
 * is 0, this is a new lcu.
 * Negative वापस code indicates that something went wrong (e.g. -ENOMEM)
 */
पूर्णांक dasd_alias_make_device_known_to_lcu(काष्ठा dasd_device *device)
अणु
	काष्ठा dasd_eckd_निजी *निजी = device->निजी;
	अचिन्हित दीर्घ flags;
	काष्ठा alias_server *server, *newserver;
	काष्ठा alias_lcu *lcu, *newlcu;
	काष्ठा dasd_uid uid;

	device->discipline->get_uid(device, &uid);
	spin_lock_irqsave(&aliastree.lock, flags);
	server = _find_server(&uid);
	अगर (!server) अणु
		spin_unlock_irqrestore(&aliastree.lock, flags);
		newserver = _allocate_server(&uid);
		अगर (IS_ERR(newserver))
			वापस PTR_ERR(newserver);
		spin_lock_irqsave(&aliastree.lock, flags);
		server = _find_server(&uid);
		अगर (!server) अणु
			list_add(&newserver->server, &aliastree.serverlist);
			server = newserver;
		पूर्ण अन्यथा अणु
			/* someone was faster */
			_मुक्त_server(newserver);
		पूर्ण
	पूर्ण

	lcu = _find_lcu(server, &uid);
	अगर (!lcu) अणु
		spin_unlock_irqrestore(&aliastree.lock, flags);
		newlcu = _allocate_lcu(&uid);
		अगर (IS_ERR(newlcu))
			वापस PTR_ERR(newlcu);
		spin_lock_irqsave(&aliastree.lock, flags);
		lcu = _find_lcu(server, &uid);
		अगर (!lcu) अणु
			list_add(&newlcu->lcu, &server->lculist);
			lcu = newlcu;
		पूर्ण अन्यथा अणु
			/* someone was faster */
			_मुक्त_lcu(newlcu);
		पूर्ण
	पूर्ण
	spin_lock(&lcu->lock);
	list_add(&device->alias_list, &lcu->inactive_devices);
	निजी->lcu = lcu;
	spin_unlock(&lcu->lock);
	spin_unlock_irqrestore(&aliastree.lock, flags);

	वापस 0;
पूर्ण

/*
 * This function हटाओs a device from the scope of alias management.
 * The complicated part is to make sure that it is not in use by
 * any of the workers. If necessary cancel the work.
 */
व्योम dasd_alias_disconnect_device_from_lcu(काष्ठा dasd_device *device)
अणु
	काष्ठा dasd_eckd_निजी *निजी = device->निजी;
	अचिन्हित दीर्घ flags;
	काष्ठा alias_lcu *lcu;
	काष्ठा alias_server *server;
	पूर्णांक was_pending;
	काष्ठा dasd_uid uid;

	lcu = निजी->lcu;
	/* nothing to करो अगर alपढ़ोy disconnected */
	अगर (!lcu)
		वापस;
	device->discipline->get_uid(device, &uid);
	spin_lock_irqsave(&lcu->lock, flags);
	/* make sure that the workers करोn't use this device */
	अगर (device == lcu->suc_data.device) अणु
		spin_unlock_irqrestore(&lcu->lock, flags);
		cancel_work_sync(&lcu->suc_data.worker);
		spin_lock_irqsave(&lcu->lock, flags);
		अगर (device == lcu->suc_data.device) अणु
			dasd_put_device(device);
			lcu->suc_data.device = शून्य;
		पूर्ण
	पूर्ण
	was_pending = 0;
	अगर (device == lcu->ruac_data.device) अणु
		spin_unlock_irqrestore(&lcu->lock, flags);
		was_pending = 1;
		cancel_delayed_work_sync(&lcu->ruac_data.dwork);
		spin_lock_irqsave(&lcu->lock, flags);
		अगर (device == lcu->ruac_data.device) अणु
			dasd_put_device(device);
			lcu->ruac_data.device = शून्य;
		पूर्ण
	पूर्ण
	निजी->lcu = शून्य;
	spin_unlock_irqrestore(&lcu->lock, flags);

	spin_lock_irqsave(&aliastree.lock, flags);
	spin_lock(&lcu->lock);
	list_del_init(&device->alias_list);
	अगर (list_empty(&lcu->grouplist) &&
	    list_empty(&lcu->active_devices) &&
	    list_empty(&lcu->inactive_devices)) अणु
		list_del(&lcu->lcu);
		spin_unlock(&lcu->lock);
		_मुक्त_lcu(lcu);
		lcu = शून्य;
	पूर्ण अन्यथा अणु
		अगर (was_pending)
			_schedule_lcu_update(lcu, शून्य);
		spin_unlock(&lcu->lock);
	पूर्ण
	server = _find_server(&uid);
	अगर (server && list_empty(&server->lculist)) अणु
		list_del(&server->server);
		_मुक्त_server(server);
	पूर्ण
	spin_unlock_irqrestore(&aliastree.lock, flags);
पूर्ण

/*
 * This function assumes that the unit address configuration stored
 * in the lcu is up to date and will update the device uid beक्रमe
 * adding it to a pav group.
 */

अटल पूर्णांक _add_device_to_lcu(काष्ठा alias_lcu *lcu,
			      काष्ठा dasd_device *device,
			      काष्ठा dasd_device *pos)
अणु

	काष्ठा dasd_eckd_निजी *निजी = device->निजी;
	काष्ठा alias_pav_group *group;
	काष्ठा dasd_uid uid;

	spin_lock(get_ccwdev_lock(device->cdev));
	निजी->uid.type = lcu->uac->unit[निजी->uid.real_unit_addr].ua_type;
	निजी->uid.base_unit_addr =
		lcu->uac->unit[निजी->uid.real_unit_addr].base_ua;
	uid = निजी->uid;
	spin_unlock(get_ccwdev_lock(device->cdev));
	/* अगर we have no PAV anyway, we करोn't need to bother with PAV groups */
	अगर (lcu->pav == NO_PAV) अणु
		list_move(&device->alias_list, &lcu->active_devices);
		वापस 0;
	पूर्ण
	group = _find_group(lcu, &uid);
	अगर (!group) अणु
		group = kzalloc(माप(*group), GFP_ATOMIC);
		अगर (!group)
			वापस -ENOMEM;
		स_नकल(group->uid.venकरोr, uid.venकरोr, माप(uid.venकरोr));
		स_नकल(group->uid.serial, uid.serial, माप(uid.serial));
		group->uid.ssid = uid.ssid;
		अगर (uid.type == UA_BASE_DEVICE)
			group->uid.base_unit_addr = uid.real_unit_addr;
		अन्यथा
			group->uid.base_unit_addr = uid.base_unit_addr;
		स_नकल(group->uid.vduit, uid.vduit, माप(uid.vduit));
		INIT_LIST_HEAD(&group->group);
		INIT_LIST_HEAD(&group->baselist);
		INIT_LIST_HEAD(&group->aliaslist);
		list_add(&group->group, &lcu->grouplist);
	पूर्ण
	अगर (uid.type == UA_BASE_DEVICE)
		list_move(&device->alias_list, &group->baselist);
	अन्यथा
		list_move(&device->alias_list, &group->aliaslist);
	निजी->pavgroup = group;
	वापस 0;
पूर्ण;

अटल व्योम _हटाओ_device_from_lcu(काष्ठा alias_lcu *lcu,
				    काष्ठा dasd_device *device)
अणु
	काष्ठा dasd_eckd_निजी *निजी = device->निजी;
	काष्ठा alias_pav_group *group;

	list_move(&device->alias_list, &lcu->inactive_devices);
	group = निजी->pavgroup;
	अगर (!group)
		वापस;
	निजी->pavgroup = शून्य;
	अगर (list_empty(&group->baselist) && list_empty(&group->aliaslist)) अणु
		list_del(&group->group);
		kमुक्त(group);
		वापस;
	पूर्ण
	अगर (group->next == device)
		group->next = शून्य;
पूर्ण;

अटल पूर्णांक
suborder_not_supported(काष्ठा dasd_ccw_req *cqr)
अणु
	अक्षर *sense;
	अक्षर reason;
	अक्षर msg_क्रमmat;
	अक्षर msg_no;

	/*
	 * पूर्णांकrc values ENODEV, ENOLINK and EPERM
	 * will be optained from sleep_on to indicate that no
	 * IO operation can be started
	 */
	अगर (cqr->पूर्णांकrc == -ENODEV)
		वापस 1;

	अगर (cqr->पूर्णांकrc == -ENOLINK)
		वापस 1;

	अगर (cqr->पूर्णांकrc == -EPERM)
		वापस 1;

	sense = dasd_get_sense(&cqr->irb);
	अगर (!sense)
		वापस 0;

	reason = sense[0];
	msg_क्रमmat = (sense[7] & 0xF0);
	msg_no = (sense[7] & 0x0F);

	/* command reject, Format 0 MSG 4 - invalid parameter */
	अगर ((reason == 0x80) && (msg_क्रमmat == 0x00) && (msg_no == 0x04))
		वापस 1;

	वापस 0;
पूर्ण

अटल पूर्णांक पढ़ो_unit_address_configuration(काष्ठा dasd_device *device,
					   काष्ठा alias_lcu *lcu)
अणु
	काष्ठा dasd_psf_prssd_data *prssdp;
	काष्ठा dasd_ccw_req *cqr;
	काष्ठा ccw1 *ccw;
	पूर्णांक rc;
	अचिन्हित दीर्घ flags;

	cqr = dasd_sदो_स्मृति_request(DASD_ECKD_MAGIC, 1 /* PSF */	+ 1 /* RSSD */,
				   (माप(काष्ठा dasd_psf_prssd_data)),
				   device, शून्य);
	अगर (IS_ERR(cqr))
		वापस PTR_ERR(cqr);
	cqr->startdev = device;
	cqr->memdev = device;
	clear_bit(DASD_CQR_FLAGS_USE_ERP, &cqr->flags);
	cqr->retries = 10;
	cqr->expires = 20 * HZ;

	/* Prepare क्रम Read Subप्रणाली Data */
	prssdp = (काष्ठा dasd_psf_prssd_data *) cqr->data;
	स_रखो(prssdp, 0, माप(काष्ठा dasd_psf_prssd_data));
	prssdp->order = PSF_ORDER_PRSSD;
	prssdp->suborder = 0x0e;	/* Read unit address configuration */
	/* all other bytes of prssdp must be zero */

	ccw = cqr->cpaddr;
	ccw->cmd_code = DASD_ECKD_CCW_PSF;
	ccw->count = माप(काष्ठा dasd_psf_prssd_data);
	ccw->flags |= CCW_FLAG_CC;
	ccw->cda = (__u32)(addr_t) prssdp;

	/* Read Subप्रणाली Data - feature codes */
	स_रखो(lcu->uac, 0, माप(*(lcu->uac)));

	ccw++;
	ccw->cmd_code = DASD_ECKD_CCW_RSSD;
	ccw->count = माप(*(lcu->uac));
	ccw->cda = (__u32)(addr_t) lcu->uac;

	cqr->buildclk = get_tod_घड़ी();
	cqr->status = DASD_CQR_FILLED;

	/* need to unset flag here to detect race with summary unit check */
	spin_lock_irqsave(&lcu->lock, flags);
	lcu->flags &= ~NEED_UAC_UPDATE;
	spin_unlock_irqrestore(&lcu->lock, flags);

	rc = dasd_sleep_on(cqr);
	अगर (!rc)
		जाओ out;

	अगर (suborder_not_supported(cqr)) अणु
		/* suborder not supported or device unusable क्रम IO */
		rc = -EOPNOTSUPP;
	पूर्ण अन्यथा अणु
		/* IO failed but should be retried */
		spin_lock_irqsave(&lcu->lock, flags);
		lcu->flags |= NEED_UAC_UPDATE;
		spin_unlock_irqrestore(&lcu->lock, flags);
	पूर्ण
out:
	dasd_sमुक्त_request(cqr, cqr->memdev);
	वापस rc;
पूर्ण

अटल पूर्णांक _lcu_update(काष्ठा dasd_device *refdev, काष्ठा alias_lcu *lcu)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा alias_pav_group *pavgroup, *tempgroup;
	काष्ठा dasd_device *device, *tempdev;
	पूर्णांक i, rc;
	काष्ठा dasd_eckd_निजी *निजी;

	spin_lock_irqsave(&lcu->lock, flags);
	list_क्रम_each_entry_safe(pavgroup, tempgroup, &lcu->grouplist, group) अणु
		list_क्रम_each_entry_safe(device, tempdev, &pavgroup->baselist,
					 alias_list) अणु
			list_move(&device->alias_list, &lcu->active_devices);
			निजी = device->निजी;
			निजी->pavgroup = शून्य;
		पूर्ण
		list_क्रम_each_entry_safe(device, tempdev, &pavgroup->aliaslist,
					 alias_list) अणु
			list_move(&device->alias_list, &lcu->active_devices);
			निजी = device->निजी;
			निजी->pavgroup = शून्य;
		पूर्ण
		list_del(&pavgroup->group);
		kमुक्त(pavgroup);
	पूर्ण
	spin_unlock_irqrestore(&lcu->lock, flags);

	rc = पढ़ो_unit_address_configuration(refdev, lcu);
	अगर (rc)
		वापस rc;

	spin_lock_irqsave(&lcu->lock, flags);
	/*
	 * there is another update needed skip the reमुख्यing handling
	 * the data might alपढ़ोy be outdated
	 * but especially करो not add the device to an LCU with pending
	 * update
	 */
	अगर (lcu->flags & NEED_UAC_UPDATE)
		जाओ out;
	lcu->pav = NO_PAV;
	क्रम (i = 0; i < MAX_DEVICES_PER_LCU; ++i) अणु
		चयन (lcu->uac->unit[i].ua_type) अणु
		हाल UA_BASE_PAV_ALIAS:
			lcu->pav = BASE_PAV;
			अवरोध;
		हाल UA_HYPER_PAV_ALIAS:
			lcu->pav = HYPER_PAV;
			अवरोध;
		पूर्ण
		अगर (lcu->pav != NO_PAV)
			अवरोध;
	पूर्ण

	list_क्रम_each_entry_safe(device, tempdev, &lcu->active_devices,
				 alias_list) अणु
		_add_device_to_lcu(lcu, device, refdev);
	पूर्ण
out:
	spin_unlock_irqrestore(&lcu->lock, flags);
	वापस 0;
पूर्ण

अटल व्योम lcu_update_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा alias_lcu *lcu;
	काष्ठा पढ़ो_uac_work_data *ruac_data;
	काष्ठा dasd_device *device;
	अचिन्हित दीर्घ flags;
	पूर्णांक rc;

	ruac_data = container_of(work, काष्ठा पढ़ो_uac_work_data, dwork.work);
	lcu = container_of(ruac_data, काष्ठा alias_lcu, ruac_data);
	device = ruac_data->device;
	rc = _lcu_update(device, lcu);
	/*
	 * Need to check flags again, as there could have been another
	 * prepare_update or a new device a new device जबतक we were still
	 * processing the data
	 */
	spin_lock_irqsave(&lcu->lock, flags);
	अगर ((rc && (rc != -EOPNOTSUPP)) || (lcu->flags & NEED_UAC_UPDATE)) अणु
		DBF_DEV_EVENT(DBF_WARNING, device, "could not update"
			    " alias data in lcu (rc = %d), retry later", rc);
		अगर (!schedule_delayed_work(&lcu->ruac_data.dwork, 30*HZ))
			dasd_put_device(device);
	पूर्ण अन्यथा अणु
		dasd_put_device(device);
		lcu->ruac_data.device = शून्य;
		lcu->flags &= ~UPDATE_PENDING;
	पूर्ण
	spin_unlock_irqrestore(&lcu->lock, flags);
पूर्ण

अटल पूर्णांक _schedule_lcu_update(काष्ठा alias_lcu *lcu,
				काष्ठा dasd_device *device)
अणु
	काष्ठा dasd_device *usedev = शून्य;
	काष्ठा alias_pav_group *group;

	lcu->flags |= NEED_UAC_UPDATE;
	अगर (lcu->ruac_data.device) अणु
		/* alपढ़ोy scheduled or running */
		वापस 0;
	पूर्ण
	अगर (device && !list_empty(&device->alias_list))
		usedev = device;

	अगर (!usedev && !list_empty(&lcu->grouplist)) अणु
		group = list_first_entry(&lcu->grouplist,
					 काष्ठा alias_pav_group, group);
		अगर (!list_empty(&group->baselist))
			usedev = list_first_entry(&group->baselist,
						  काष्ठा dasd_device,
						  alias_list);
		अन्यथा अगर (!list_empty(&group->aliaslist))
			usedev = list_first_entry(&group->aliaslist,
						  काष्ठा dasd_device,
						  alias_list);
	पूर्ण
	अगर (!usedev && !list_empty(&lcu->active_devices)) अणु
		usedev = list_first_entry(&lcu->active_devices,
					  काष्ठा dasd_device, alias_list);
	पूर्ण
	/*
	 * अगर we haven't found a proper device yet, give up क्रम now, the next
	 * device that will be set active will trigger an lcu update
	 */
	अगर (!usedev)
		वापस -EINVAL;
	dasd_get_device(usedev);
	lcu->ruac_data.device = usedev;
	अगर (!schedule_delayed_work(&lcu->ruac_data.dwork, 0))
		dasd_put_device(usedev);
	वापस 0;
पूर्ण

पूर्णांक dasd_alias_add_device(काष्ठा dasd_device *device)
अणु
	काष्ठा dasd_eckd_निजी *निजी = device->निजी;
	__u8 uaddr = निजी->uid.real_unit_addr;
	काष्ठा alias_lcu *lcu = निजी->lcu;
	अचिन्हित दीर्घ flags;
	पूर्णांक rc;

	rc = 0;
	spin_lock_irqsave(&lcu->lock, flags);
	/*
	 * Check अगर device and lcu type dअगरfer. If so, the uac data may be
	 * outdated and needs to be updated.
	 */
	अगर (निजी->uid.type !=  lcu->uac->unit[uaddr].ua_type) अणु
		lcu->flags |= UPDATE_PENDING;
		DBF_DEV_EVENT(DBF_WARNING, device, "%s",
			      "uid type mismatch - trigger rescan");
	पूर्ण
	अगर (!(lcu->flags & UPDATE_PENDING)) अणु
		rc = _add_device_to_lcu(lcu, device, device);
		अगर (rc)
			lcu->flags |= UPDATE_PENDING;
	पूर्ण
	अगर (lcu->flags & UPDATE_PENDING) अणु
		list_move(&device->alias_list, &lcu->active_devices);
		निजी->pavgroup = शून्य;
		_schedule_lcu_update(lcu, device);
	पूर्ण
	spin_unlock_irqrestore(&lcu->lock, flags);
	वापस rc;
पूर्ण

पूर्णांक dasd_alias_update_add_device(काष्ठा dasd_device *device)
अणु
	काष्ठा dasd_eckd_निजी *निजी = device->निजी;

	निजी->lcu->flags |= UPDATE_PENDING;
	वापस dasd_alias_add_device(device);
पूर्ण

पूर्णांक dasd_alias_हटाओ_device(काष्ठा dasd_device *device)
अणु
	काष्ठा dasd_eckd_निजी *निजी = device->निजी;
	काष्ठा alias_lcu *lcu = निजी->lcu;
	अचिन्हित दीर्घ flags;

	/* nothing to करो अगर alपढ़ोy हटाओd */
	अगर (!lcu)
		वापस 0;
	spin_lock_irqsave(&lcu->lock, flags);
	_हटाओ_device_from_lcu(lcu, device);
	spin_unlock_irqrestore(&lcu->lock, flags);
	वापस 0;
पूर्ण

काष्ठा dasd_device *dasd_alias_get_start_dev(काष्ठा dasd_device *base_device)
अणु
	काष्ठा dasd_eckd_निजी *alias_priv, *निजी = base_device->निजी;
	काष्ठा alias_pav_group *group = निजी->pavgroup;
	काष्ठा alias_lcu *lcu = निजी->lcu;
	काष्ठा dasd_device *alias_device;
	अचिन्हित दीर्घ flags;

	अगर (!group || !lcu)
		वापस शून्य;
	अगर (lcu->pav == NO_PAV ||
	    lcu->flags & (NEED_UAC_UPDATE | UPDATE_PENDING))
		वापस शून्य;
	अगर (unlikely(!(निजी->features.feature[8] & 0x01))) अणु
		/*
		 * PAV enabled but prefix not, very unlikely
		 * seems to be a lost pathgroup
		 * use base device to करो IO
		 */
		DBF_DEV_EVENT(DBF_ERR, base_device, "%s",
			      "Prefix not enabled with PAV enabled\n");
		वापस शून्य;
	पूर्ण

	spin_lock_irqsave(&lcu->lock, flags);
	alias_device = group->next;
	अगर (!alias_device) अणु
		अगर (list_empty(&group->aliaslist)) अणु
			spin_unlock_irqrestore(&lcu->lock, flags);
			वापस शून्य;
		पूर्ण अन्यथा अणु
			alias_device = list_first_entry(&group->aliaslist,
							काष्ठा dasd_device,
							alias_list);
		पूर्ण
	पूर्ण
	अगर (list_is_last(&alias_device->alias_list, &group->aliaslist))
		group->next = list_first_entry(&group->aliaslist,
					       काष्ठा dasd_device, alias_list);
	अन्यथा
		group->next = list_first_entry(&alias_device->alias_list,
					       काष्ठा dasd_device, alias_list);
	spin_unlock_irqrestore(&lcu->lock, flags);
	alias_priv = alias_device->निजी;
	अगर ((alias_priv->count < निजी->count) && !alias_device->stopped &&
	    !test_bit(DASD_FLAG_OFFLINE, &alias_device->flags))
		वापस alias_device;
	अन्यथा
		वापस शून्य;
पूर्ण

/*
 * Summary unit check handling depends on the way alias devices
 * are handled so it is करोne here rather then in dasd_eckd.c
 */
अटल पूर्णांक reset_summary_unit_check(काष्ठा alias_lcu *lcu,
				    काष्ठा dasd_device *device,
				    अक्षर reason)
अणु
	काष्ठा dasd_ccw_req *cqr;
	पूर्णांक rc = 0;
	काष्ठा ccw1 *ccw;

	cqr = lcu->rsu_cqr;
	स_नकल((अक्षर *) &cqr->magic, "ECKD", 4);
	ASCEBC((अक्षर *) &cqr->magic, 4);
	ccw = cqr->cpaddr;
	ccw->cmd_code = DASD_ECKD_CCW_RSCK;
	ccw->flags = CCW_FLAG_SLI;
	ccw->count = 16;
	ccw->cda = (__u32)(addr_t) cqr->data;
	((अक्षर *)cqr->data)[0] = reason;

	clear_bit(DASD_CQR_FLAGS_USE_ERP, &cqr->flags);
	cqr->retries = 255;	/* set retry counter to enable basic ERP */
	cqr->startdev = device;
	cqr->memdev = device;
	cqr->block = शून्य;
	cqr->expires = 5 * HZ;
	cqr->buildclk = get_tod_घड़ी();
	cqr->status = DASD_CQR_FILLED;

	rc = dasd_sleep_on_immediatly(cqr);
	वापस rc;
पूर्ण

अटल व्योम _restart_all_base_devices_on_lcu(काष्ठा alias_lcu *lcu)
अणु
	काष्ठा alias_pav_group *pavgroup;
	काष्ठा dasd_device *device;
	काष्ठा dasd_eckd_निजी *निजी;

	/* active and inactive list can contain alias as well as base devices */
	list_क्रम_each_entry(device, &lcu->active_devices, alias_list) अणु
		निजी = device->निजी;
		अगर (निजी->uid.type != UA_BASE_DEVICE)
			जारी;
		dasd_schedule_block_bh(device->block);
		dasd_schedule_device_bh(device);
	पूर्ण
	list_क्रम_each_entry(device, &lcu->inactive_devices, alias_list) अणु
		निजी = device->निजी;
		अगर (निजी->uid.type != UA_BASE_DEVICE)
			जारी;
		dasd_schedule_block_bh(device->block);
		dasd_schedule_device_bh(device);
	पूर्ण
	list_क्रम_each_entry(pavgroup, &lcu->grouplist, group) अणु
		list_क्रम_each_entry(device, &pavgroup->baselist, alias_list) अणु
			dasd_schedule_block_bh(device->block);
			dasd_schedule_device_bh(device);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम flush_all_alias_devices_on_lcu(काष्ठा alias_lcu *lcu)
अणु
	काष्ठा alias_pav_group *pavgroup;
	काष्ठा dasd_device *device, *temp;
	काष्ठा dasd_eckd_निजी *निजी;
	अचिन्हित दीर्घ flags;
	LIST_HEAD(active);

	/*
	 * Problem here ist that dasd_flush_device_queue may रुको
	 * क्रम termination of a request to complete. We can't keep
	 * the lcu lock during that समय, so we must assume that
	 * the lists may have changed.
	 * Idea: first gather all active alias devices in a separate list,
	 * then flush the first element of this list unlocked, and afterwards
	 * check अगर it is still on the list beक्रमe moving it to the
	 * active_devices list.
	 */

	spin_lock_irqsave(&lcu->lock, flags);
	list_क्रम_each_entry_safe(device, temp, &lcu->active_devices,
				 alias_list) अणु
		निजी = device->निजी;
		अगर (निजी->uid.type == UA_BASE_DEVICE)
			जारी;
		list_move(&device->alias_list, &active);
	पूर्ण

	list_क्रम_each_entry(pavgroup, &lcu->grouplist, group) अणु
		list_splice_init(&pavgroup->aliaslist, &active);
	पूर्ण
	जबतक (!list_empty(&active)) अणु
		device = list_first_entry(&active, काष्ठा dasd_device,
					  alias_list);
		spin_unlock_irqrestore(&lcu->lock, flags);
		dasd_flush_device_queue(device);
		spin_lock_irqsave(&lcu->lock, flags);
		/*
		 * only move device around अगर it wasn't moved away जबतक we
		 * were रुकोing क्रम the flush
		 */
		अगर (device == list_first_entry(&active,
					       काष्ठा dasd_device, alias_list)) अणु
			list_move(&device->alias_list, &lcu->active_devices);
			निजी = device->निजी;
			निजी->pavgroup = शून्य;
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&lcu->lock, flags);
पूर्ण

अटल व्योम _stop_all_devices_on_lcu(काष्ठा alias_lcu *lcu)
अणु
	काष्ठा alias_pav_group *pavgroup;
	काष्ठा dasd_device *device;

	list_क्रम_each_entry(device, &lcu->active_devices, alias_list) अणु
		spin_lock(get_ccwdev_lock(device->cdev));
		dasd_device_set_stop_bits(device, DASD_STOPPED_SU);
		spin_unlock(get_ccwdev_lock(device->cdev));
	पूर्ण
	list_क्रम_each_entry(device, &lcu->inactive_devices, alias_list) अणु
		spin_lock(get_ccwdev_lock(device->cdev));
		dasd_device_set_stop_bits(device, DASD_STOPPED_SU);
		spin_unlock(get_ccwdev_lock(device->cdev));
	पूर्ण
	list_क्रम_each_entry(pavgroup, &lcu->grouplist, group) अणु
		list_क्रम_each_entry(device, &pavgroup->baselist, alias_list) अणु
			spin_lock(get_ccwdev_lock(device->cdev));
			dasd_device_set_stop_bits(device, DASD_STOPPED_SU);
			spin_unlock(get_ccwdev_lock(device->cdev));
		पूर्ण
		list_क्रम_each_entry(device, &pavgroup->aliaslist, alias_list) अणु
			spin_lock(get_ccwdev_lock(device->cdev));
			dasd_device_set_stop_bits(device, DASD_STOPPED_SU);
			spin_unlock(get_ccwdev_lock(device->cdev));
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम _unstop_all_devices_on_lcu(काष्ठा alias_lcu *lcu)
अणु
	काष्ठा alias_pav_group *pavgroup;
	काष्ठा dasd_device *device;

	list_क्रम_each_entry(device, &lcu->active_devices, alias_list) अणु
		spin_lock(get_ccwdev_lock(device->cdev));
		dasd_device_हटाओ_stop_bits(device, DASD_STOPPED_SU);
		spin_unlock(get_ccwdev_lock(device->cdev));
	पूर्ण
	list_क्रम_each_entry(device, &lcu->inactive_devices, alias_list) अणु
		spin_lock(get_ccwdev_lock(device->cdev));
		dasd_device_हटाओ_stop_bits(device, DASD_STOPPED_SU);
		spin_unlock(get_ccwdev_lock(device->cdev));
	पूर्ण
	list_क्रम_each_entry(pavgroup, &lcu->grouplist, group) अणु
		list_क्रम_each_entry(device, &pavgroup->baselist, alias_list) अणु
			spin_lock(get_ccwdev_lock(device->cdev));
			dasd_device_हटाओ_stop_bits(device, DASD_STOPPED_SU);
			spin_unlock(get_ccwdev_lock(device->cdev));
		पूर्ण
		list_क्रम_each_entry(device, &pavgroup->aliaslist, alias_list) अणु
			spin_lock(get_ccwdev_lock(device->cdev));
			dasd_device_हटाओ_stop_bits(device, DASD_STOPPED_SU);
			spin_unlock(get_ccwdev_lock(device->cdev));
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम summary_unit_check_handling_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा alias_lcu *lcu;
	काष्ठा summary_unit_check_work_data *suc_data;
	अचिन्हित दीर्घ flags;
	काष्ठा dasd_device *device;

	suc_data = container_of(work, काष्ठा summary_unit_check_work_data,
				worker);
	lcu = container_of(suc_data, काष्ठा alias_lcu, suc_data);
	device = suc_data->device;

	/* 1. flush alias devices */
	flush_all_alias_devices_on_lcu(lcu);

	/* 2. reset summary unit check */
	spin_lock_irqsave(get_ccwdev_lock(device->cdev), flags);
	dasd_device_हटाओ_stop_bits(device,
				     (DASD_STOPPED_SU | DASD_STOPPED_PENDING));
	spin_unlock_irqrestore(get_ccwdev_lock(device->cdev), flags);
	reset_summary_unit_check(lcu, device, suc_data->reason);

	spin_lock_irqsave(&lcu->lock, flags);
	_unstop_all_devices_on_lcu(lcu);
	_restart_all_base_devices_on_lcu(lcu);
	/* 3. पढ़ो new alias configuration */
	_schedule_lcu_update(lcu, device);
	lcu->suc_data.device = शून्य;
	dasd_put_device(device);
	spin_unlock_irqrestore(&lcu->lock, flags);
पूर्ण

व्योम dasd_alias_handle_summary_unit_check(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा dasd_device *device = container_of(work, काष्ठा dasd_device,
						  suc_work);
	काष्ठा dasd_eckd_निजी *निजी = device->निजी;
	काष्ठा alias_lcu *lcu;
	अचिन्हित दीर्घ flags;

	lcu = निजी->lcu;
	अगर (!lcu) अणु
		DBF_DEV_EVENT(DBF_WARNING, device, "%s",
			    "device not ready to handle summary"
			    " unit check (no lcu structure)");
		जाओ out;
	पूर्ण
	spin_lock_irqsave(&lcu->lock, flags);
	/* If this device is about to be हटाओd just वापस and रुको क्रम
	 * the next पूर्णांकerrupt on a dअगरferent device
	 */
	अगर (list_empty(&device->alias_list)) अणु
		DBF_DEV_EVENT(DBF_WARNING, device, "%s",
			    "device is in offline processing,"
			    " don't do summary unit check handling");
		जाओ out_unlock;
	पूर्ण
	अगर (lcu->suc_data.device) अणु
		/* alपढ़ोy scheduled or running */
		DBF_DEV_EVENT(DBF_WARNING, device, "%s",
			    "previous instance of summary unit check worker"
			    " still pending");
		जाओ out_unlock;
	पूर्ण
	_stop_all_devices_on_lcu(lcu);
	/* prepare क्रम lcu_update */
	lcu->flags |= NEED_UAC_UPDATE | UPDATE_PENDING;
	lcu->suc_data.reason = निजी->suc_reason;
	lcu->suc_data.device = device;
	dasd_get_device(device);
	अगर (!schedule_work(&lcu->suc_data.worker))
		dasd_put_device(device);
out_unlock:
	spin_unlock_irqrestore(&lcu->lock, flags);
out:
	clear_bit(DASD_FLAG_SUC, &device->flags);
	dasd_put_device(device);
पूर्ण;
