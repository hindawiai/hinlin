<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * AC driver क्रम 7th-generation Microsoft Surface devices via Surface System
 * Aggregator Module (SSAM).
 *
 * Copyright (C) 2019-2021 Maximilian Luz <luzmaximilian@gmail.com>
 */

#समावेश <यंत्र/unaligned.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/घातer_supply.h>
#समावेश <linux/types.h>

#समावेश <linux/surface_aggregator/device.h>


/* -- SAM पूर्णांकerface. -------------------------------------------------------- */

क्रमागत sam_event_cid_bat अणु
	SAM_EVENT_CID_BAT_ADP   = 0x17,
पूर्ण;

क्रमागत sam_battery_sta अणु
	SAM_BATTERY_STA_OK      = 0x0f,
	SAM_BATTERY_STA_PRESENT	= 0x10,
पूर्ण;

/* Get battery status (_STA). */
SSAM_DEFINE_SYNC_REQUEST_CL_R(ssam_bat_get_sta, __le32, अणु
	.target_category = SSAM_SSH_TC_BAT,
	.command_id      = 0x01,
पूर्ण);

/* Get platक्रमm घातer source क्रम battery (_PSR / DPTF PSRC). */
SSAM_DEFINE_SYNC_REQUEST_CL_R(ssam_bat_get_psrc, __le32, अणु
	.target_category = SSAM_SSH_TC_BAT,
	.command_id      = 0x0d,
पूर्ण);


/* -- Device काष्ठाures. ---------------------------------------------------- */

काष्ठा spwr_psy_properties अणु
	स्थिर अक्षर *name;
	काष्ठा ssam_event_registry registry;
पूर्ण;

काष्ठा spwr_ac_device अणु
	काष्ठा ssam_device *sdev;

	अक्षर name[32];
	काष्ठा घातer_supply *psy;
	काष्ठा घातer_supply_desc psy_desc;

	काष्ठा ssam_event_notअगरier notअगर;

	काष्ठा mutex lock;  /* Guards access to state below. */

	__le32 state;
पूर्ण;


/* -- State management. ----------------------------------------------------- */

अटल पूर्णांक spwr_ac_update_unlocked(काष्ठा spwr_ac_device *ac)
अणु
	u32 old = ac->state;
	पूर्णांक status;

	lockdep_निश्चित_held(&ac->lock);

	status = ssam_retry(ssam_bat_get_psrc, ac->sdev, &ac->state);
	अगर (status < 0)
		वापस status;

	वापस old != ac->state;
पूर्ण

अटल पूर्णांक spwr_ac_update(काष्ठा spwr_ac_device *ac)
अणु
	पूर्णांक status;

	mutex_lock(&ac->lock);
	status = spwr_ac_update_unlocked(ac);
	mutex_unlock(&ac->lock);

	वापस status;
पूर्ण

अटल पूर्णांक spwr_ac_recheck(काष्ठा spwr_ac_device *ac)
अणु
	पूर्णांक status;

	status = spwr_ac_update(ac);
	अगर (status > 0)
		घातer_supply_changed(ac->psy);

	वापस status >= 0 ? 0 : status;
पूर्ण

अटल u32 spwr_notअगरy_ac(काष्ठा ssam_event_notअगरier *nf, स्थिर काष्ठा ssam_event *event)
अणु
	काष्ठा spwr_ac_device *ac;
	पूर्णांक status;

	ac = container_of(nf, काष्ठा spwr_ac_device, notअगर);

	dev_dbg(&ac->sdev->dev, "power event (cid = %#04x, iid = %#04x, tid = %#04x)\n",
		event->command_id, event->instance_id, event->target_id);

	/*
	 * Allow events of all tarमाला_लो/instances here. Global adapter status
	 * seems to be handled via target=1 and instance=1, but events are
	 * reported on all tarमाला_लो/instances in use.
	 *
	 * While it should be enough to just listen on 1/1, listen everywhere to
	 * make sure we करोn't miss anything.
	 */

	चयन (event->command_id) अणु
	हाल SAM_EVENT_CID_BAT_ADP:
		status = spwr_ac_recheck(ac);
		वापस ssam_notअगरier_from_त्रुटि_सं(status) | SSAM_NOTIF_HANDLED;

	शेष:
		वापस 0;
	पूर्ण
पूर्ण


/* -- Properties. ----------------------------------------------------------- */

अटल स्थिर क्रमागत घातer_supply_property spwr_ac_props[] = अणु
	POWER_SUPPLY_PROP_ONLINE,
पूर्ण;

अटल पूर्णांक spwr_ac_get_property(काष्ठा घातer_supply *psy, क्रमागत घातer_supply_property psp,
				जोड़ घातer_supply_propval *val)
अणु
	काष्ठा spwr_ac_device *ac = घातer_supply_get_drvdata(psy);
	पूर्णांक status;

	mutex_lock(&ac->lock);

	status = spwr_ac_update_unlocked(ac);
	अगर (status)
		जाओ out;

	चयन (psp) अणु
	हाल POWER_SUPPLY_PROP_ONLINE:
		val->पूर्णांकval = !!le32_to_cpu(ac->state);
		अवरोध;

	शेष:
		status = -EINVAL;
		जाओ out;
	पूर्ण

out:
	mutex_unlock(&ac->lock);
	वापस status;
पूर्ण


/* -- Device setup. --------------------------------------------------------- */

अटल अक्षर *battery_supplied_to[] = अणु
	"BAT1",
	"BAT2",
पूर्ण;

अटल व्योम spwr_ac_init(काष्ठा spwr_ac_device *ac, काष्ठा ssam_device *sdev,
			 काष्ठा ssam_event_registry registry, स्थिर अक्षर *name)
अणु
	mutex_init(&ac->lock);
	म_नकलन(ac->name, name, ARRAY_SIZE(ac->name) - 1);

	ac->sdev = sdev;

	ac->notअगर.base.priority = 1;
	ac->notअगर.base.fn = spwr_notअगरy_ac;
	ac->notअगर.event.reg = registry;
	ac->notअगर.event.id.target_category = sdev->uid.category;
	ac->notअगर.event.id.instance = 0;
	ac->notअगर.event.mask = SSAM_EVENT_MASK_NONE;
	ac->notअगर.event.flags = SSAM_EVENT_SEQUENCED;

	ac->psy_desc.name = ac->name;
	ac->psy_desc.type = POWER_SUPPLY_TYPE_MAINS;
	ac->psy_desc.properties = spwr_ac_props;
	ac->psy_desc.num_properties = ARRAY_SIZE(spwr_ac_props);
	ac->psy_desc.get_property = spwr_ac_get_property;
पूर्ण

अटल पूर्णांक spwr_ac_रेजिस्टर(काष्ठा spwr_ac_device *ac)
अणु
	काष्ठा घातer_supply_config psy_cfg = अणुपूर्ण;
	__le32 sta;
	पूर्णांक status;

	/* Make sure the device is there and functioning properly. */
	status = ssam_retry(ssam_bat_get_sta, ac->sdev, &sta);
	अगर (status)
		वापस status;

	अगर ((le32_to_cpu(sta) & SAM_BATTERY_STA_OK) != SAM_BATTERY_STA_OK)
		वापस -ENODEV;

	psy_cfg.drv_data = ac;
	psy_cfg.supplied_to = battery_supplied_to;
	psy_cfg.num_supplicants = ARRAY_SIZE(battery_supplied_to);

	ac->psy = devm_घातer_supply_रेजिस्टर(&ac->sdev->dev, &ac->psy_desc, &psy_cfg);
	अगर (IS_ERR(ac->psy))
		वापस PTR_ERR(ac->psy);

	वापस ssam_notअगरier_रेजिस्टर(ac->sdev->ctrl, &ac->notअगर);
पूर्ण


/* -- Driver setup. --------------------------------------------------------- */

अटल पूर्णांक __maybe_unused surface_ac_resume(काष्ठा device *dev)
अणु
	वापस spwr_ac_recheck(dev_get_drvdata(dev));
पूर्ण
अटल SIMPLE_DEV_PM_OPS(surface_ac_pm_ops, शून्य, surface_ac_resume);

अटल पूर्णांक surface_ac_probe(काष्ठा ssam_device *sdev)
अणु
	स्थिर काष्ठा spwr_psy_properties *p;
	काष्ठा spwr_ac_device *ac;

	p = ssam_device_get_match_data(sdev);
	अगर (!p)
		वापस -ENODEV;

	ac = devm_kzalloc(&sdev->dev, माप(*ac), GFP_KERNEL);
	अगर (!ac)
		वापस -ENOMEM;

	spwr_ac_init(ac, sdev, p->registry, p->name);
	ssam_device_set_drvdata(sdev, ac);

	वापस spwr_ac_रेजिस्टर(ac);
पूर्ण

अटल व्योम surface_ac_हटाओ(काष्ठा ssam_device *sdev)
अणु
	काष्ठा spwr_ac_device *ac = ssam_device_get_drvdata(sdev);

	ssam_notअगरier_unरेजिस्टर(sdev->ctrl, &ac->notअगर);
पूर्ण

अटल स्थिर काष्ठा spwr_psy_properties spwr_psy_props_adp1 = अणु
	.name = "ADP1",
	.registry = SSAM_EVENT_REGISTRY_SAM,
पूर्ण;

अटल स्थिर काष्ठा ssam_device_id surface_ac_match[] = अणु
	अणु SSAM_SDEV(BAT, 0x01, 0x01, 0x01), (अचिन्हित दीर्घ)&spwr_psy_props_adp1 पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(ssam, surface_ac_match);

अटल काष्ठा ssam_device_driver surface_ac_driver = अणु
	.probe = surface_ac_probe,
	.हटाओ = surface_ac_हटाओ,
	.match_table = surface_ac_match,
	.driver = अणु
		.name = "surface_ac",
		.pm = &surface_ac_pm_ops,
		.probe_type = PROBE_PREFER_ASYNCHRONOUS,
	पूर्ण,
पूर्ण;
module_ssam_device_driver(surface_ac_driver);

MODULE_AUTHOR("Maximilian Luz <luzmaximilian@gmail.com>");
MODULE_DESCRIPTION("AC driver for Surface System Aggregator Module");
MODULE_LICENSE("GPL");
