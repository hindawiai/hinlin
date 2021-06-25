<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Greybus पूर्णांकerface code
 *
 * Copyright 2014 Google Inc.
 * Copyright 2014 Linaro Ltd.
 */

#समावेश <linux/delay.h>
#समावेश <linux/greybus.h>

#समावेश "greybus_trace.h"

#घोषणा GB_INTERFACE_MODE_SWITCH_TIMEOUT	2000

#घोषणा GB_INTERFACE_DEVICE_ID_BAD	0xff

#घोषणा GB_INTERFACE_AUTOSUSPEND_MS			3000

/* Time required क्रम पूर्णांकerface to enter standby beक्रमe disabling REFCLK */
#घोषणा GB_INTERFACE_SUSPEND_HIBERNATE_DELAY_MS			20

/* Don't-care selector index */
#घोषणा DME_SELECTOR_INDEX_शून्य		0

/* DME attributes */
/* FIXME: हटाओ ES2 support and DME_T_TST_SRC_INCREMENT */
#घोषणा DME_T_TST_SRC_INCREMENT		0x4083

#घोषणा DME_DDBL1_MANUFACTURERID	0x5003
#घोषणा DME_DDBL1_PRODUCTID		0x5004

#घोषणा DME_TOSHIBA_GMP_VID		0x6000
#घोषणा DME_TOSHIBA_GMP_PID		0x6001
#घोषणा DME_TOSHIBA_GMP_SN0		0x6002
#घोषणा DME_TOSHIBA_GMP_SN1		0x6003
#घोषणा DME_TOSHIBA_GMP_INIT_STATUS	0x6101

/* DDBL1 Manufacturer and Product ids */
#घोषणा TOSHIBA_DMID			0x0126
#घोषणा TOSHIBA_ES2_BRIDGE_DPID		0x1000
#घोषणा TOSHIBA_ES3_APBRIDGE_DPID	0x1001
#घोषणा TOSHIBA_ES3_GBPHY_DPID	0x1002

अटल पूर्णांक gb_पूर्णांकerface_hibernate_link(काष्ठा gb_पूर्णांकerface *पूर्णांकf);
अटल पूर्णांक gb_पूर्णांकerface_refclk_set(काष्ठा gb_पूर्णांकerface *पूर्णांकf, bool enable);

अटल पूर्णांक gb_पूर्णांकerface_dme_attr_get(काष्ठा gb_पूर्णांकerface *पूर्णांकf,
				     u16 attr, u32 *val)
अणु
	वापस gb_svc_dme_peer_get(पूर्णांकf->hd->svc, पूर्णांकf->पूर्णांकerface_id,
					attr, DME_SELECTOR_INDEX_शून्य, val);
पूर्ण

अटल पूर्णांक gb_पूर्णांकerface_पढ़ो_ara_dme(काष्ठा gb_पूर्णांकerface *पूर्णांकf)
अणु
	u32 sn0, sn1;
	पूर्णांक ret;

	/*
	 * Unless this is a Toshiba bridge, bail out until we have defined
	 * standard GMP attributes.
	 */
	अगर (पूर्णांकf->ddbl1_manufacturer_id != TOSHIBA_DMID) अणु
		dev_err(&पूर्णांकf->dev, "unknown manufacturer %08x\n",
			पूर्णांकf->ddbl1_manufacturer_id);
		वापस -ENODEV;
	पूर्ण

	ret = gb_पूर्णांकerface_dme_attr_get(पूर्णांकf, DME_TOSHIBA_GMP_VID,
					&पूर्णांकf->venकरोr_id);
	अगर (ret)
		वापस ret;

	ret = gb_पूर्णांकerface_dme_attr_get(पूर्णांकf, DME_TOSHIBA_GMP_PID,
					&पूर्णांकf->product_id);
	अगर (ret)
		वापस ret;

	ret = gb_पूर्णांकerface_dme_attr_get(पूर्णांकf, DME_TOSHIBA_GMP_SN0, &sn0);
	अगर (ret)
		वापस ret;

	ret = gb_पूर्णांकerface_dme_attr_get(पूर्णांकf, DME_TOSHIBA_GMP_SN1, &sn1);
	अगर (ret)
		वापस ret;

	पूर्णांकf->serial_number = (u64)sn1 << 32 | sn0;

	वापस 0;
पूर्ण

अटल पूर्णांक gb_पूर्णांकerface_पढ़ो_dme(काष्ठा gb_पूर्णांकerface *पूर्णांकf)
अणु
	पूर्णांक ret;

	/* DME attributes have alपढ़ोy been पढ़ो */
	अगर (पूर्णांकf->dme_पढ़ो)
		वापस 0;

	ret = gb_पूर्णांकerface_dme_attr_get(पूर्णांकf, DME_DDBL1_MANUFACTURERID,
					&पूर्णांकf->ddbl1_manufacturer_id);
	अगर (ret)
		वापस ret;

	ret = gb_पूर्णांकerface_dme_attr_get(पूर्णांकf, DME_DDBL1_PRODUCTID,
					&पूर्णांकf->ddbl1_product_id);
	अगर (ret)
		वापस ret;

	अगर (पूर्णांकf->ddbl1_manufacturer_id == TOSHIBA_DMID &&
	    पूर्णांकf->ddbl1_product_id == TOSHIBA_ES2_BRIDGE_DPID) अणु
		पूर्णांकf->quirks |= GB_INTERFACE_QUIRK_NO_GMP_IDS;
		पूर्णांकf->quirks |= GB_INTERFACE_QUIRK_NO_INIT_STATUS;
	पूर्ण

	ret = gb_पूर्णांकerface_पढ़ो_ara_dme(पूर्णांकf);
	अगर (ret)
		वापस ret;

	पूर्णांकf->dme_पढ़ो = true;

	वापस 0;
पूर्ण

अटल पूर्णांक gb_पूर्णांकerface_route_create(काष्ठा gb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा gb_svc *svc = पूर्णांकf->hd->svc;
	u8 पूर्णांकf_id = पूर्णांकf->पूर्णांकerface_id;
	u8 device_id;
	पूर्णांक ret;

	/* Allocate an पूर्णांकerface device id. */
	ret = ida_simple_get(&svc->device_id_map,
			     GB_SVC_DEVICE_ID_MIN, GB_SVC_DEVICE_ID_MAX + 1,
			     GFP_KERNEL);
	अगर (ret < 0) अणु
		dev_err(&पूर्णांकf->dev, "failed to allocate device id: %d\n", ret);
		वापस ret;
	पूर्ण
	device_id = ret;

	ret = gb_svc_पूर्णांकf_device_id(svc, पूर्णांकf_id, device_id);
	अगर (ret) अणु
		dev_err(&पूर्णांकf->dev, "failed to set device id %u: %d\n",
			device_id, ret);
		जाओ err_ida_हटाओ;
	पूर्ण

	/* FIXME: Hard-coded AP device id. */
	ret = gb_svc_route_create(svc, svc->ap_पूर्णांकf_id, GB_SVC_DEVICE_ID_AP,
				  पूर्णांकf_id, device_id);
	अगर (ret) अणु
		dev_err(&पूर्णांकf->dev, "failed to create route: %d\n", ret);
		जाओ err_svc_id_मुक्त;
	पूर्ण

	पूर्णांकf->device_id = device_id;

	वापस 0;

err_svc_id_मुक्त:
	/*
	 * XXX Should we tell SVC that this id करोesn't beदीर्घ to पूर्णांकerface
	 * XXX anymore.
	 */
err_ida_हटाओ:
	ida_simple_हटाओ(&svc->device_id_map, device_id);

	वापस ret;
पूर्ण

अटल व्योम gb_पूर्णांकerface_route_destroy(काष्ठा gb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा gb_svc *svc = पूर्णांकf->hd->svc;

	अगर (पूर्णांकf->device_id == GB_INTERFACE_DEVICE_ID_BAD)
		वापस;

	gb_svc_route_destroy(svc, svc->ap_पूर्णांकf_id, पूर्णांकf->पूर्णांकerface_id);
	ida_simple_हटाओ(&svc->device_id_map, पूर्णांकf->device_id);
	पूर्णांकf->device_id = GB_INTERFACE_DEVICE_ID_BAD;
पूर्ण

/* Locking: Caller holds the पूर्णांकerface mutex. */
अटल पूर्णांक gb_पूर्णांकerface_legacy_mode_चयन(काष्ठा gb_पूर्णांकerface *पूर्णांकf)
अणु
	पूर्णांक ret;

	dev_info(&पूर्णांकf->dev, "legacy mode switch detected\n");

	/* Mark as disconnected to prevent I/O during disable. */
	पूर्णांकf->disconnected = true;
	gb_पूर्णांकerface_disable(पूर्णांकf);
	पूर्णांकf->disconnected = false;

	ret = gb_पूर्णांकerface_enable(पूर्णांकf);
	अगर (ret) अणु
		dev_err(&पूर्णांकf->dev, "failed to re-enable interface: %d\n", ret);
		gb_पूर्णांकerface_deactivate(पूर्णांकf);
	पूर्ण

	वापस ret;
पूर्ण

व्योम gb_पूर्णांकerface_mailbox_event(काष्ठा gb_पूर्णांकerface *पूर्णांकf, u16 result,
				u32 mailbox)
अणु
	mutex_lock(&पूर्णांकf->mutex);

	अगर (result) अणु
		dev_warn(&पूर्णांकf->dev,
			 "mailbox event with UniPro error: 0x%04x\n",
			 result);
		जाओ err_disable;
	पूर्ण

	अगर (mailbox != GB_SVC_INTF_MAILBOX_GREYBUS) अणु
		dev_warn(&पूर्णांकf->dev,
			 "mailbox event with unexpected value: 0x%08x\n",
			 mailbox);
		जाओ err_disable;
	पूर्ण

	अगर (पूर्णांकf->quirks & GB_INTERFACE_QUIRK_LEGACY_MODE_SWITCH) अणु
		gb_पूर्णांकerface_legacy_mode_चयन(पूर्णांकf);
		जाओ out_unlock;
	पूर्ण

	अगर (!पूर्णांकf->mode_चयन) अणु
		dev_warn(&पूर्णांकf->dev, "unexpected mailbox event: 0x%08x\n",
			 mailbox);
		जाओ err_disable;
	पूर्ण

	dev_info(&पूर्णांकf->dev, "mode switch detected\n");

	complete(&पूर्णांकf->mode_चयन_completion);

out_unlock:
	mutex_unlock(&पूर्णांकf->mutex);

	वापस;

err_disable:
	gb_पूर्णांकerface_disable(पूर्णांकf);
	gb_पूर्णांकerface_deactivate(पूर्णांकf);
	mutex_unlock(&पूर्णांकf->mutex);
पूर्ण

अटल व्योम gb_पूर्णांकerface_mode_चयन_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा gb_पूर्णांकerface *पूर्णांकf;
	काष्ठा gb_control *control;
	अचिन्हित दीर्घ समयout;
	पूर्णांक ret;

	पूर्णांकf = container_of(work, काष्ठा gb_पूर्णांकerface, mode_चयन_work);

	mutex_lock(&पूर्णांकf->mutex);
	/* Make sure पूर्णांकerface is still enabled. */
	अगर (!पूर्णांकf->enabled) अणु
		dev_dbg(&पूर्णांकf->dev, "mode switch aborted\n");
		पूर्णांकf->mode_चयन = false;
		mutex_unlock(&पूर्णांकf->mutex);
		जाओ out_पूर्णांकerface_put;
	पूर्ण

	/*
	 * Prepare the control device क्रम mode चयन and make sure to get an
	 * extra reference beक्रमe it goes away during पूर्णांकerface disable.
	 */
	control = gb_control_get(पूर्णांकf->control);
	gb_control_mode_चयन_prepare(control);
	gb_पूर्णांकerface_disable(पूर्णांकf);
	mutex_unlock(&पूर्णांकf->mutex);

	समयout = msecs_to_jअगरfies(GB_INTERFACE_MODE_SWITCH_TIMEOUT);
	ret = रुको_क्रम_completion_पूर्णांकerruptible_समयout(
			&पूर्णांकf->mode_चयन_completion, समयout);

	/* Finalise control-connection mode चयन. */
	gb_control_mode_चयन_complete(control);
	gb_control_put(control);

	अगर (ret < 0) अणु
		dev_err(&पूर्णांकf->dev, "mode switch interrupted\n");
		जाओ err_deactivate;
	पूर्ण अन्यथा अगर (ret == 0) अणु
		dev_err(&पूर्णांकf->dev, "mode switch timed out\n");
		जाओ err_deactivate;
	पूर्ण

	/* Re-enable (re-क्रमागतerate) पूर्णांकerface अगर still active. */
	mutex_lock(&पूर्णांकf->mutex);
	पूर्णांकf->mode_चयन = false;
	अगर (पूर्णांकf->active) अणु
		ret = gb_पूर्णांकerface_enable(पूर्णांकf);
		अगर (ret) अणु
			dev_err(&पूर्णांकf->dev, "failed to re-enable interface: %d\n",
				ret);
			gb_पूर्णांकerface_deactivate(पूर्णांकf);
		पूर्ण
	पूर्ण
	mutex_unlock(&पूर्णांकf->mutex);

out_पूर्णांकerface_put:
	gb_पूर्णांकerface_put(पूर्णांकf);

	वापस;

err_deactivate:
	mutex_lock(&पूर्णांकf->mutex);
	पूर्णांकf->mode_चयन = false;
	gb_पूर्णांकerface_deactivate(पूर्णांकf);
	mutex_unlock(&पूर्णांकf->mutex);

	gb_पूर्णांकerface_put(पूर्णांकf);
पूर्ण

पूर्णांक gb_पूर्णांकerface_request_mode_चयन(काष्ठा gb_पूर्णांकerface *पूर्णांकf)
अणु
	पूर्णांक ret = 0;

	mutex_lock(&पूर्णांकf->mutex);
	अगर (पूर्णांकf->mode_चयन) अणु
		ret = -EBUSY;
		जाओ out_unlock;
	पूर्ण

	पूर्णांकf->mode_चयन = true;
	reinit_completion(&पूर्णांकf->mode_चयन_completion);

	/*
	 * Get a reference to the पूर्णांकerface device, which will be put once the
	 * mode चयन is complete.
	 */
	get_device(&पूर्णांकf->dev);

	अगर (!queue_work(प्रणाली_दीर्घ_wq, &पूर्णांकf->mode_चयन_work)) अणु
		put_device(&पूर्णांकf->dev);
		ret = -EBUSY;
		जाओ out_unlock;
	पूर्ण

out_unlock:
	mutex_unlock(&पूर्णांकf->mutex);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(gb_पूर्णांकerface_request_mode_चयन);

/*
 * T_TstSrcIncrement is written by the module on ES2 as a stand-in क्रम the
 * init-status attribute DME_TOSHIBA_INIT_STATUS. The AP needs to पढ़ो and
 * clear it after पढ़ोing a non-zero value from it.
 *
 * FIXME: This is module-hardware dependent and needs to be extended क्रम every
 * type of module we want to support.
 */
अटल पूर्णांक gb_पूर्णांकerface_पढ़ो_and_clear_init_status(काष्ठा gb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा gb_host_device *hd = पूर्णांकf->hd;
	अचिन्हित दीर्घ bootrom_quirks;
	अचिन्हित दीर्घ s2l_quirks;
	पूर्णांक ret;
	u32 value;
	u16 attr;
	u8 init_status;

	/*
	 * ES2 bridges use T_TstSrcIncrement क्रम the init status.
	 *
	 * FIXME: Remove ES2 support
	 */
	अगर (पूर्णांकf->quirks & GB_INTERFACE_QUIRK_NO_INIT_STATUS)
		attr = DME_T_TST_SRC_INCREMENT;
	अन्यथा
		attr = DME_TOSHIBA_GMP_INIT_STATUS;

	ret = gb_svc_dme_peer_get(hd->svc, पूर्णांकf->पूर्णांकerface_id, attr,
				  DME_SELECTOR_INDEX_शून्य, &value);
	अगर (ret)
		वापस ret;

	/*
	 * A nonzero init status indicates the module has finished
	 * initializing.
	 */
	अगर (!value) अणु
		dev_err(&पूर्णांकf->dev, "invalid init status\n");
		वापस -ENODEV;
	पूर्ण

	/*
	 * Extract the init status.
	 *
	 * For ES2: We need to check lowest 8 bits of 'value'.
	 * For ES3: We need to check highest 8 bits out of 32 of 'value'.
	 *
	 * FIXME: Remove ES2 support
	 */
	अगर (पूर्णांकf->quirks & GB_INTERFACE_QUIRK_NO_INIT_STATUS)
		init_status = value & 0xff;
	अन्यथा
		init_status = value >> 24;

	/*
	 * Check अगर the पूर्णांकerface is executing the quirky ES3 bootrom that,
	 * क्रम example, requires E2EFC, CSD and CSV to be disabled.
	 */
	bootrom_quirks = GB_INTERFACE_QUIRK_NO_CPORT_FEATURES |
				GB_INTERFACE_QUIRK_FORCED_DISABLE |
				GB_INTERFACE_QUIRK_LEGACY_MODE_SWITCH |
				GB_INTERFACE_QUIRK_NO_BUNDLE_ACTIVATE;

	s2l_quirks = GB_INTERFACE_QUIRK_NO_PM;

	चयन (init_status) अणु
	हाल GB_INIT_BOOTROM_UNIPRO_BOOT_STARTED:
	हाल GB_INIT_BOOTROM_FALLBACK_UNIPRO_BOOT_STARTED:
		पूर्णांकf->quirks |= bootrom_quirks;
		अवरोध;
	हाल GB_INIT_S2_LOADER_BOOT_STARTED:
		/* S2 Loader करोesn't support runसमय PM */
		पूर्णांकf->quirks &= ~bootrom_quirks;
		पूर्णांकf->quirks |= s2l_quirks;
		अवरोध;
	शेष:
		पूर्णांकf->quirks &= ~bootrom_quirks;
		पूर्णांकf->quirks &= ~s2l_quirks;
	पूर्ण

	/* Clear the init status. */
	वापस gb_svc_dme_peer_set(hd->svc, पूर्णांकf->पूर्णांकerface_id, attr,
				   DME_SELECTOR_INDEX_शून्य, 0);
पूर्ण

/* पूर्णांकerface sysfs attributes */
#घोषणा gb_पूर्णांकerface_attr(field, type)					\
अटल sमाप_प्रकार field##_show(काष्ठा device *dev,				\
			    काष्ठा device_attribute *attr,		\
			    अक्षर *buf)					\
अणु									\
	काष्ठा gb_पूर्णांकerface *पूर्णांकf = to_gb_पूर्णांकerface(dev);		\
	वापस scnम_लिखो(buf, PAGE_SIZE, type"\n", पूर्णांकf->field);	\
पूर्ण									\
अटल DEVICE_ATTR_RO(field)

gb_पूर्णांकerface_attr(ddbl1_manufacturer_id, "0x%08x");
gb_पूर्णांकerface_attr(ddbl1_product_id, "0x%08x");
gb_पूर्णांकerface_attr(पूर्णांकerface_id, "%u");
gb_पूर्णांकerface_attr(venकरोr_id, "0x%08x");
gb_पूर्णांकerface_attr(product_id, "0x%08x");
gb_पूर्णांकerface_attr(serial_number, "0x%016llx");

अटल sमाप_प्रकार voltage_now_show(काष्ठा device *dev,
				काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा gb_पूर्णांकerface *पूर्णांकf = to_gb_पूर्णांकerface(dev);
	पूर्णांक ret;
	u32 measurement;

	ret = gb_svc_pwrmon_पूर्णांकf_sample_get(पूर्णांकf->hd->svc, पूर्णांकf->पूर्णांकerface_id,
					    GB_SVC_PWRMON_TYPE_VOL,
					    &measurement);
	अगर (ret) अणु
		dev_err(&पूर्णांकf->dev, "failed to get voltage sample (%d)\n", ret);
		वापस ret;
	पूर्ण

	वापस प्र_लिखो(buf, "%u\n", measurement);
पूर्ण
अटल DEVICE_ATTR_RO(voltage_now);

अटल sमाप_प्रकार current_now_show(काष्ठा device *dev,
				काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा gb_पूर्णांकerface *पूर्णांकf = to_gb_पूर्णांकerface(dev);
	पूर्णांक ret;
	u32 measurement;

	ret = gb_svc_pwrmon_पूर्णांकf_sample_get(पूर्णांकf->hd->svc, पूर्णांकf->पूर्णांकerface_id,
					    GB_SVC_PWRMON_TYPE_CURR,
					    &measurement);
	अगर (ret) अणु
		dev_err(&पूर्णांकf->dev, "failed to get current sample (%d)\n", ret);
		वापस ret;
	पूर्ण

	वापस प्र_लिखो(buf, "%u\n", measurement);
पूर्ण
अटल DEVICE_ATTR_RO(current_now);

अटल sमाप_प्रकार घातer_now_show(काष्ठा device *dev,
			      काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा gb_पूर्णांकerface *पूर्णांकf = to_gb_पूर्णांकerface(dev);
	पूर्णांक ret;
	u32 measurement;

	ret = gb_svc_pwrmon_पूर्णांकf_sample_get(पूर्णांकf->hd->svc, पूर्णांकf->पूर्णांकerface_id,
					    GB_SVC_PWRMON_TYPE_PWR,
					    &measurement);
	अगर (ret) अणु
		dev_err(&पूर्णांकf->dev, "failed to get power sample (%d)\n", ret);
		वापस ret;
	पूर्ण

	वापस प्र_लिखो(buf, "%u\n", measurement);
पूर्ण
अटल DEVICE_ATTR_RO(घातer_now);

अटल sमाप_प्रकार घातer_state_show(काष्ठा device *dev,
				काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा gb_पूर्णांकerface *पूर्णांकf = to_gb_पूर्णांकerface(dev);

	अगर (पूर्णांकf->active)
		वापस scnम_लिखो(buf, PAGE_SIZE, "on\n");
	अन्यथा
		वापस scnम_लिखो(buf, PAGE_SIZE, "off\n");
पूर्ण

अटल sमाप_प्रकार घातer_state_store(काष्ठा device *dev,
				 काष्ठा device_attribute *attr, स्थिर अक्षर *buf,
				 माप_प्रकार len)
अणु
	काष्ठा gb_पूर्णांकerface *पूर्णांकf = to_gb_पूर्णांकerface(dev);
	bool activate;
	पूर्णांक ret = 0;

	अगर (kstrtobool(buf, &activate))
		वापस -EINVAL;

	mutex_lock(&पूर्णांकf->mutex);

	अगर (activate == पूर्णांकf->active)
		जाओ unlock;

	अगर (activate) अणु
		ret = gb_पूर्णांकerface_activate(पूर्णांकf);
		अगर (ret) अणु
			dev_err(&पूर्णांकf->dev,
				"failed to activate interface: %d\n", ret);
			जाओ unlock;
		पूर्ण

		ret = gb_पूर्णांकerface_enable(पूर्णांकf);
		अगर (ret) अणु
			dev_err(&पूर्णांकf->dev,
				"failed to enable interface: %d\n", ret);
			gb_पूर्णांकerface_deactivate(पूर्णांकf);
			जाओ unlock;
		पूर्ण
	पूर्ण अन्यथा अणु
		gb_पूर्णांकerface_disable(पूर्णांकf);
		gb_पूर्णांकerface_deactivate(पूर्णांकf);
	पूर्ण

unlock:
	mutex_unlock(&पूर्णांकf->mutex);

	अगर (ret)
		वापस ret;

	वापस len;
पूर्ण
अटल DEVICE_ATTR_RW(घातer_state);

अटल स्थिर अक्षर *gb_पूर्णांकerface_type_string(काष्ठा gb_पूर्णांकerface *पूर्णांकf)
अणु
	अटल स्थिर अक्षर * स्थिर types[] = अणु
		[GB_INTERFACE_TYPE_INVALID] = "invalid",
		[GB_INTERFACE_TYPE_UNKNOWN] = "unknown",
		[GB_INTERFACE_TYPE_DUMMY] = "dummy",
		[GB_INTERFACE_TYPE_UNIPRO] = "unipro",
		[GB_INTERFACE_TYPE_GREYBUS] = "greybus",
	पूर्ण;

	वापस types[पूर्णांकf->type];
पूर्ण

अटल sमाप_प्रकार पूर्णांकerface_type_show(काष्ठा device *dev,
				   काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा gb_पूर्णांकerface *पूर्णांकf = to_gb_पूर्णांकerface(dev);

	वापस प्र_लिखो(buf, "%s\n", gb_पूर्णांकerface_type_string(पूर्णांकf));
पूर्ण
अटल DEVICE_ATTR_RO(पूर्णांकerface_type);

अटल काष्ठा attribute *पूर्णांकerface_unipro_attrs[] = अणु
	&dev_attr_ddbl1_manufacturer_id.attr,
	&dev_attr_ddbl1_product_id.attr,
	शून्य
पूर्ण;

अटल काष्ठा attribute *पूर्णांकerface_greybus_attrs[] = अणु
	&dev_attr_venकरोr_id.attr,
	&dev_attr_product_id.attr,
	&dev_attr_serial_number.attr,
	शून्य
पूर्ण;

अटल काष्ठा attribute *पूर्णांकerface_घातer_attrs[] = अणु
	&dev_attr_voltage_now.attr,
	&dev_attr_current_now.attr,
	&dev_attr_घातer_now.attr,
	&dev_attr_घातer_state.attr,
	शून्य
पूर्ण;

अटल काष्ठा attribute *पूर्णांकerface_common_attrs[] = अणु
	&dev_attr_पूर्णांकerface_id.attr,
	&dev_attr_पूर्णांकerface_type.attr,
	शून्य
पूर्ण;

अटल umode_t पूर्णांकerface_unipro_is_visible(काष्ठा kobject *kobj,
					   काष्ठा attribute *attr, पूर्णांक n)
अणु
	काष्ठा device *dev = kobj_to_dev(kobj);
	काष्ठा gb_पूर्णांकerface *पूर्णांकf = to_gb_पूर्णांकerface(dev);

	चयन (पूर्णांकf->type) अणु
	हाल GB_INTERFACE_TYPE_UNIPRO:
	हाल GB_INTERFACE_TYPE_GREYBUS:
		वापस attr->mode;
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

अटल umode_t पूर्णांकerface_greybus_is_visible(काष्ठा kobject *kobj,
					    काष्ठा attribute *attr, पूर्णांक n)
अणु
	काष्ठा device *dev = kobj_to_dev(kobj);
	काष्ठा gb_पूर्णांकerface *पूर्णांकf = to_gb_पूर्णांकerface(dev);

	चयन (पूर्णांकf->type) अणु
	हाल GB_INTERFACE_TYPE_GREYBUS:
		वापस attr->mode;
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

अटल umode_t पूर्णांकerface_घातer_is_visible(काष्ठा kobject *kobj,
					  काष्ठा attribute *attr, पूर्णांक n)
अणु
	काष्ठा device *dev = kobj_to_dev(kobj);
	काष्ठा gb_पूर्णांकerface *पूर्णांकf = to_gb_पूर्णांकerface(dev);

	चयन (पूर्णांकf->type) अणु
	हाल GB_INTERFACE_TYPE_UNIPRO:
	हाल GB_INTERFACE_TYPE_GREYBUS:
		वापस attr->mode;
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा attribute_group पूर्णांकerface_unipro_group = अणु
	.is_visible	= पूर्णांकerface_unipro_is_visible,
	.attrs		= पूर्णांकerface_unipro_attrs,
पूर्ण;

अटल स्थिर काष्ठा attribute_group पूर्णांकerface_greybus_group = अणु
	.is_visible	= पूर्णांकerface_greybus_is_visible,
	.attrs		= पूर्णांकerface_greybus_attrs,
पूर्ण;

अटल स्थिर काष्ठा attribute_group पूर्णांकerface_घातer_group = अणु
	.is_visible	= पूर्णांकerface_घातer_is_visible,
	.attrs		= पूर्णांकerface_घातer_attrs,
पूर्ण;

अटल स्थिर काष्ठा attribute_group पूर्णांकerface_common_group = अणु
	.attrs		= पूर्णांकerface_common_attrs,
पूर्ण;

अटल स्थिर काष्ठा attribute_group *पूर्णांकerface_groups[] = अणु
	&पूर्णांकerface_unipro_group,
	&पूर्णांकerface_greybus_group,
	&पूर्णांकerface_घातer_group,
	&पूर्णांकerface_common_group,
	शून्य
पूर्ण;

अटल व्योम gb_पूर्णांकerface_release(काष्ठा device *dev)
अणु
	काष्ठा gb_पूर्णांकerface *पूर्णांकf = to_gb_पूर्णांकerface(dev);

	trace_gb_पूर्णांकerface_release(पूर्णांकf);

	kमुक्त(पूर्णांकf);
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक gb_पूर्णांकerface_suspend(काष्ठा device *dev)
अणु
	काष्ठा gb_पूर्णांकerface *पूर्णांकf = to_gb_पूर्णांकerface(dev);
	पूर्णांक ret;

	ret = gb_control_पूर्णांकerface_suspend_prepare(पूर्णांकf->control);
	अगर (ret)
		वापस ret;

	ret = gb_control_suspend(पूर्णांकf->control);
	अगर (ret)
		जाओ err_hibernate_पात;

	ret = gb_पूर्णांकerface_hibernate_link(पूर्णांकf);
	अगर (ret)
		वापस ret;

	/* Delay to allow पूर्णांकerface to enter standby beक्रमe disabling refclk */
	msleep(GB_INTERFACE_SUSPEND_HIBERNATE_DELAY_MS);

	ret = gb_पूर्णांकerface_refclk_set(पूर्णांकf, false);
	अगर (ret)
		वापस ret;

	वापस 0;

err_hibernate_पात:
	gb_control_पूर्णांकerface_hibernate_पात(पूर्णांकf->control);

	वापस ret;
पूर्ण

अटल पूर्णांक gb_पूर्णांकerface_resume(काष्ठा device *dev)
अणु
	काष्ठा gb_पूर्णांकerface *पूर्णांकf = to_gb_पूर्णांकerface(dev);
	काष्ठा gb_svc *svc = पूर्णांकf->hd->svc;
	पूर्णांक ret;

	ret = gb_पूर्णांकerface_refclk_set(पूर्णांकf, true);
	अगर (ret)
		वापस ret;

	ret = gb_svc_पूर्णांकf_resume(svc, पूर्णांकf->पूर्णांकerface_id);
	अगर (ret)
		वापस ret;

	ret = gb_control_resume(पूर्णांकf->control);
	अगर (ret)
		वापस ret;

	वापस 0;
पूर्ण

अटल पूर्णांक gb_पूर्णांकerface_runसमय_idle(काष्ठा device *dev)
अणु
	pm_runसमय_mark_last_busy(dev);
	pm_request_स्वतःsuspend(dev);

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा dev_pm_ops gb_पूर्णांकerface_pm_ops = अणु
	SET_RUNTIME_PM_OPS(gb_पूर्णांकerface_suspend, gb_पूर्णांकerface_resume,
			   gb_पूर्णांकerface_runसमय_idle)
पूर्ण;

काष्ठा device_type greybus_पूर्णांकerface_type = अणु
	.name =		"greybus_interface",
	.release =	gb_पूर्णांकerface_release,
	.pm =		&gb_पूर्णांकerface_pm_ops,
पूर्ण;

/*
 * A Greybus module represents a user-replaceable component on a GMP
 * phone.  An पूर्णांकerface is the physical connection on that module.  A
 * module may have more than one पूर्णांकerface.
 *
 * Create a gb_पूर्णांकerface काष्ठाure to represent a discovered पूर्णांकerface.
 * The position of पूर्णांकerface within the Enकरो is encoded in "interface_id"
 * argument.
 *
 * Returns a poपूर्णांकer to the new पूर्णांकerfce or a null poपूर्णांकer अगर a
 * failure occurs due to memory exhaustion.
 */
काष्ठा gb_पूर्णांकerface *gb_पूर्णांकerface_create(काष्ठा gb_module *module,
					 u8 पूर्णांकerface_id)
अणु
	काष्ठा gb_host_device *hd = module->hd;
	काष्ठा gb_पूर्णांकerface *पूर्णांकf;

	पूर्णांकf = kzalloc(माप(*पूर्णांकf), GFP_KERNEL);
	अगर (!पूर्णांकf)
		वापस शून्य;

	पूर्णांकf->hd = hd;		/* XXX refcount? */
	पूर्णांकf->module = module;
	पूर्णांकf->पूर्णांकerface_id = पूर्णांकerface_id;
	INIT_LIST_HEAD(&पूर्णांकf->bundles);
	INIT_LIST_HEAD(&पूर्णांकf->manअगरest_descs);
	mutex_init(&पूर्णांकf->mutex);
	INIT_WORK(&पूर्णांकf->mode_चयन_work, gb_पूर्णांकerface_mode_चयन_work);
	init_completion(&पूर्णांकf->mode_चयन_completion);

	/* Invalid device id to start with */
	पूर्णांकf->device_id = GB_INTERFACE_DEVICE_ID_BAD;

	पूर्णांकf->dev.parent = &module->dev;
	पूर्णांकf->dev.bus = &greybus_bus_type;
	पूर्णांकf->dev.type = &greybus_पूर्णांकerface_type;
	पूर्णांकf->dev.groups = पूर्णांकerface_groups;
	पूर्णांकf->dev.dma_mask = module->dev.dma_mask;
	device_initialize(&पूर्णांकf->dev);
	dev_set_name(&पूर्णांकf->dev, "%s.%u", dev_name(&module->dev),
		     पूर्णांकerface_id);

	pm_runसमय_set_स्वतःsuspend_delay(&पूर्णांकf->dev,
					 GB_INTERFACE_AUTOSUSPEND_MS);

	trace_gb_पूर्णांकerface_create(पूर्णांकf);

	वापस पूर्णांकf;
पूर्ण

अटल पूर्णांक gb_पूर्णांकerface_vsys_set(काष्ठा gb_पूर्णांकerface *पूर्णांकf, bool enable)
अणु
	काष्ठा gb_svc *svc = पूर्णांकf->hd->svc;
	पूर्णांक ret;

	dev_dbg(&पूर्णांकf->dev, "%s - %d\n", __func__, enable);

	ret = gb_svc_पूर्णांकf_vsys_set(svc, पूर्णांकf->पूर्णांकerface_id, enable);
	अगर (ret) अणु
		dev_err(&पूर्णांकf->dev, "failed to set v_sys: %d\n", ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक gb_पूर्णांकerface_refclk_set(काष्ठा gb_पूर्णांकerface *पूर्णांकf, bool enable)
अणु
	काष्ठा gb_svc *svc = पूर्णांकf->hd->svc;
	पूर्णांक ret;

	dev_dbg(&पूर्णांकf->dev, "%s - %d\n", __func__, enable);

	ret = gb_svc_पूर्णांकf_refclk_set(svc, पूर्णांकf->पूर्णांकerface_id, enable);
	अगर (ret) अणु
		dev_err(&पूर्णांकf->dev, "failed to set refclk: %d\n", ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक gb_पूर्णांकerface_unipro_set(काष्ठा gb_पूर्णांकerface *पूर्णांकf, bool enable)
अणु
	काष्ठा gb_svc *svc = पूर्णांकf->hd->svc;
	पूर्णांक ret;

	dev_dbg(&पूर्णांकf->dev, "%s - %d\n", __func__, enable);

	ret = gb_svc_पूर्णांकf_unipro_set(svc, पूर्णांकf->पूर्णांकerface_id, enable);
	अगर (ret) अणु
		dev_err(&पूर्णांकf->dev, "failed to set UniPro: %d\n", ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक gb_पूर्णांकerface_activate_operation(काष्ठा gb_पूर्णांकerface *पूर्णांकf,
					   क्रमागत gb_पूर्णांकerface_type *पूर्णांकf_type)
अणु
	काष्ठा gb_svc *svc = पूर्णांकf->hd->svc;
	u8 type;
	पूर्णांक ret;

	dev_dbg(&पूर्णांकf->dev, "%s\n", __func__);

	ret = gb_svc_पूर्णांकf_activate(svc, पूर्णांकf->पूर्णांकerface_id, &type);
	अगर (ret) अणु
		dev_err(&पूर्णांकf->dev, "failed to activate: %d\n", ret);
		वापस ret;
	पूर्ण

	चयन (type) अणु
	हाल GB_SVC_INTF_TYPE_DUMMY:
		*पूर्णांकf_type = GB_INTERFACE_TYPE_DUMMY;
		/* FIXME: handle as an error क्रम now */
		वापस -ENODEV;
	हाल GB_SVC_INTF_TYPE_UNIPRO:
		*पूर्णांकf_type = GB_INTERFACE_TYPE_UNIPRO;
		dev_err(&पूर्णांकf->dev, "interface type UniPro not supported\n");
		/* FIXME: handle as an error क्रम now */
		वापस -ENODEV;
	हाल GB_SVC_INTF_TYPE_GREYBUS:
		*पूर्णांकf_type = GB_INTERFACE_TYPE_GREYBUS;
		अवरोध;
	शेष:
		dev_err(&पूर्णांकf->dev, "unknown interface type: %u\n", type);
		*पूर्णांकf_type = GB_INTERFACE_TYPE_UNKNOWN;
		वापस -ENODEV;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक gb_पूर्णांकerface_hibernate_link(काष्ठा gb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा gb_svc *svc = पूर्णांकf->hd->svc;

	वापस gb_svc_पूर्णांकf_set_घातer_mode_hibernate(svc, पूर्णांकf->पूर्णांकerface_id);
पूर्ण

अटल पूर्णांक _gb_पूर्णांकerface_activate(काष्ठा gb_पूर्णांकerface *पूर्णांकf,
				  क्रमागत gb_पूर्णांकerface_type *type)
अणु
	पूर्णांक ret;

	*type = GB_INTERFACE_TYPE_UNKNOWN;

	अगर (पूर्णांकf->ejected || पूर्णांकf->हटाओd)
		वापस -ENODEV;

	ret = gb_पूर्णांकerface_vsys_set(पूर्णांकf, true);
	अगर (ret)
		वापस ret;

	ret = gb_पूर्णांकerface_refclk_set(पूर्णांकf, true);
	अगर (ret)
		जाओ err_vsys_disable;

	ret = gb_पूर्णांकerface_unipro_set(पूर्णांकf, true);
	अगर (ret)
		जाओ err_refclk_disable;

	ret = gb_पूर्णांकerface_activate_operation(पूर्णांकf, type);
	अगर (ret) अणु
		चयन (*type) अणु
		हाल GB_INTERFACE_TYPE_UNIPRO:
		हाल GB_INTERFACE_TYPE_GREYBUS:
			जाओ err_hibernate_link;
		शेष:
			जाओ err_unipro_disable;
		पूर्ण
	पूर्ण

	ret = gb_पूर्णांकerface_पढ़ो_dme(पूर्णांकf);
	अगर (ret)
		जाओ err_hibernate_link;

	ret = gb_पूर्णांकerface_route_create(पूर्णांकf);
	अगर (ret)
		जाओ err_hibernate_link;

	पूर्णांकf->active = true;

	trace_gb_पूर्णांकerface_activate(पूर्णांकf);

	वापस 0;

err_hibernate_link:
	gb_पूर्णांकerface_hibernate_link(पूर्णांकf);
err_unipro_disable:
	gb_पूर्णांकerface_unipro_set(पूर्णांकf, false);
err_refclk_disable:
	gb_पूर्णांकerface_refclk_set(पूर्णांकf, false);
err_vsys_disable:
	gb_पूर्णांकerface_vsys_set(पूर्णांकf, false);

	वापस ret;
पूर्ण

/*
 * At present, we assume a UniPro-only module to be a Greybus module that
 * failed to send its mailbox poke. There is some reason to believe that this
 * is because of a bug in the ES3 bootrom.
 *
 * FIXME: Check अगर this is a Toshiba bridge beक्रमe retrying?
 */
अटल पूर्णांक _gb_पूर्णांकerface_activate_es3_hack(काष्ठा gb_पूर्णांकerface *पूर्णांकf,
					   क्रमागत gb_पूर्णांकerface_type *type)
अणु
	पूर्णांक retries = 3;
	पूर्णांक ret;

	जबतक (retries--) अणु
		ret = _gb_पूर्णांकerface_activate(पूर्णांकf, type);
		अगर (ret == -ENODEV && *type == GB_INTERFACE_TYPE_UNIPRO)
			जारी;

		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

/*
 * Activate an पूर्णांकerface.
 *
 * Locking: Caller holds the पूर्णांकerface mutex.
 */
पूर्णांक gb_पूर्णांकerface_activate(काष्ठा gb_पूर्णांकerface *पूर्णांकf)
अणु
	क्रमागत gb_पूर्णांकerface_type type;
	पूर्णांक ret;

	चयन (पूर्णांकf->type) अणु
	हाल GB_INTERFACE_TYPE_INVALID:
	हाल GB_INTERFACE_TYPE_GREYBUS:
		ret = _gb_पूर्णांकerface_activate_es3_hack(पूर्णांकf, &type);
		अवरोध;
	शेष:
		ret = _gb_पूर्णांकerface_activate(पूर्णांकf, &type);
	पूर्ण

	/* Make sure type is detected correctly during reactivation. */
	अगर (पूर्णांकf->type != GB_INTERFACE_TYPE_INVALID) अणु
		अगर (type != पूर्णांकf->type) अणु
			dev_err(&पूर्णांकf->dev, "failed to detect interface type\n");

			अगर (!ret)
				gb_पूर्णांकerface_deactivate(पूर्णांकf);

			वापस -EIO;
		पूर्ण
	पूर्ण अन्यथा अणु
		पूर्णांकf->type = type;
	पूर्ण

	वापस ret;
पूर्ण

/*
 * Deactivate an पूर्णांकerface.
 *
 * Locking: Caller holds the पूर्णांकerface mutex.
 */
व्योम gb_पूर्णांकerface_deactivate(काष्ठा gb_पूर्णांकerface *पूर्णांकf)
अणु
	अगर (!पूर्णांकf->active)
		वापस;

	trace_gb_पूर्णांकerface_deactivate(पूर्णांकf);

	/* Abort any ongoing mode चयन. */
	अगर (पूर्णांकf->mode_चयन)
		complete(&पूर्णांकf->mode_चयन_completion);

	gb_पूर्णांकerface_route_destroy(पूर्णांकf);
	gb_पूर्णांकerface_hibernate_link(पूर्णांकf);
	gb_पूर्णांकerface_unipro_set(पूर्णांकf, false);
	gb_पूर्णांकerface_refclk_set(पूर्णांकf, false);
	gb_पूर्णांकerface_vsys_set(पूर्णांकf, false);

	पूर्णांकf->active = false;
पूर्ण

/*
 * Enable an पूर्णांकerface by enabling its control connection, fetching the
 * manअगरest and other inक्रमmation over it, and finally रेजिस्टरing its child
 * devices.
 *
 * Locking: Caller holds the पूर्णांकerface mutex.
 */
पूर्णांक gb_पूर्णांकerface_enable(काष्ठा gb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा gb_control *control;
	काष्ठा gb_bundle *bundle, *पंचांगp;
	पूर्णांक ret, size;
	व्योम *manअगरest;

	ret = gb_पूर्णांकerface_पढ़ो_and_clear_init_status(पूर्णांकf);
	अगर (ret) अणु
		dev_err(&पूर्णांकf->dev, "failed to clear init status: %d\n", ret);
		वापस ret;
	पूर्ण

	/* Establish control connection */
	control = gb_control_create(पूर्णांकf);
	अगर (IS_ERR(control)) अणु
		dev_err(&पूर्णांकf->dev, "failed to create control device: %ld\n",
			PTR_ERR(control));
		वापस PTR_ERR(control);
	पूर्ण
	पूर्णांकf->control = control;

	ret = gb_control_enable(पूर्णांकf->control);
	अगर (ret)
		जाओ err_put_control;

	/* Get manअगरest size using control protocol on CPort */
	size = gb_control_get_manअगरest_size_operation(पूर्णांकf);
	अगर (size <= 0) अणु
		dev_err(&पूर्णांकf->dev, "failed to get manifest size: %d\n", size);

		अगर (size)
			ret = size;
		अन्यथा
			ret =  -EINVAL;

		जाओ err_disable_control;
	पूर्ण

	manअगरest = kदो_स्मृति(size, GFP_KERNEL);
	अगर (!manअगरest) अणु
		ret = -ENOMEM;
		जाओ err_disable_control;
	पूर्ण

	/* Get manअगरest using control protocol on CPort */
	ret = gb_control_get_manअगरest_operation(पूर्णांकf, manअगरest, size);
	अगर (ret) अणु
		dev_err(&पूर्णांकf->dev, "failed to get manifest: %d\n", ret);
		जाओ err_मुक्त_manअगरest;
	पूर्ण

	/*
	 * Parse the manअगरest and build up our data काष्ठाures representing
	 * what's in it.
	 */
	अगर (!gb_manअगरest_parse(पूर्णांकf, manअगरest, size)) अणु
		dev_err(&पूर्णांकf->dev, "failed to parse manifest\n");
		ret = -EINVAL;
		जाओ err_destroy_bundles;
	पूर्ण

	ret = gb_control_get_bundle_versions(पूर्णांकf->control);
	अगर (ret)
		जाओ err_destroy_bundles;

	/* Register the control device and any bundles */
	ret = gb_control_add(पूर्णांकf->control);
	अगर (ret)
		जाओ err_destroy_bundles;

	pm_runसमय_use_स्वतःsuspend(&पूर्णांकf->dev);
	pm_runसमय_get_noresume(&पूर्णांकf->dev);
	pm_runसमय_set_active(&पूर्णांकf->dev);
	pm_runसमय_enable(&पूर्णांकf->dev);

	list_क्रम_each_entry_safe_reverse(bundle, पंचांगp, &पूर्णांकf->bundles, links) अणु
		ret = gb_bundle_add(bundle);
		अगर (ret) अणु
			gb_bundle_destroy(bundle);
			जारी;
		पूर्ण
	पूर्ण

	kमुक्त(manअगरest);

	पूर्णांकf->enabled = true;

	pm_runसमय_put(&पूर्णांकf->dev);

	trace_gb_पूर्णांकerface_enable(पूर्णांकf);

	वापस 0;

err_destroy_bundles:
	list_क्रम_each_entry_safe(bundle, पंचांगp, &पूर्णांकf->bundles, links)
		gb_bundle_destroy(bundle);
err_मुक्त_manअगरest:
	kमुक्त(manअगरest);
err_disable_control:
	gb_control_disable(पूर्णांकf->control);
err_put_control:
	gb_control_put(पूर्णांकf->control);
	पूर्णांकf->control = शून्य;

	वापस ret;
पूर्ण

/*
 * Disable an पूर्णांकerface and destroy its bundles.
 *
 * Locking: Caller holds the पूर्णांकerface mutex.
 */
व्योम gb_पूर्णांकerface_disable(काष्ठा gb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा gb_bundle *bundle;
	काष्ठा gb_bundle *next;

	अगर (!पूर्णांकf->enabled)
		वापस;

	trace_gb_पूर्णांकerface_disable(पूर्णांकf);

	pm_runसमय_get_sync(&पूर्णांकf->dev);

	/* Set disconnected flag to aव्योम I/O during connection tear करोwn. */
	अगर (पूर्णांकf->quirks & GB_INTERFACE_QUIRK_FORCED_DISABLE)
		पूर्णांकf->disconnected = true;

	list_क्रम_each_entry_safe(bundle, next, &पूर्णांकf->bundles, links)
		gb_bundle_destroy(bundle);

	अगर (!पूर्णांकf->mode_चयन && !पूर्णांकf->disconnected)
		gb_control_पूर्णांकerface_deactivate_prepare(पूर्णांकf->control);

	gb_control_del(पूर्णांकf->control);
	gb_control_disable(पूर्णांकf->control);
	gb_control_put(पूर्णांकf->control);
	पूर्णांकf->control = शून्य;

	पूर्णांकf->enabled = false;

	pm_runसमय_disable(&पूर्णांकf->dev);
	pm_runसमय_set_suspended(&पूर्णांकf->dev);
	pm_runसमय_करोnt_use_स्वतःsuspend(&पूर्णांकf->dev);
	pm_runसमय_put_noidle(&पूर्णांकf->dev);
पूर्ण

/* Register an पूर्णांकerface. */
पूर्णांक gb_पूर्णांकerface_add(काष्ठा gb_पूर्णांकerface *पूर्णांकf)
अणु
	पूर्णांक ret;

	ret = device_add(&पूर्णांकf->dev);
	अगर (ret) अणु
		dev_err(&पूर्णांकf->dev, "failed to register interface: %d\n", ret);
		वापस ret;
	पूर्ण

	trace_gb_पूर्णांकerface_add(पूर्णांकf);

	dev_info(&पूर्णांकf->dev, "Interface added (%s)\n",
		 gb_पूर्णांकerface_type_string(पूर्णांकf));

	चयन (पूर्णांकf->type) अणु
	हाल GB_INTERFACE_TYPE_GREYBUS:
		dev_info(&पूर्णांकf->dev, "GMP VID=0x%08x, PID=0x%08x\n",
			 पूर्णांकf->venकरोr_id, पूर्णांकf->product_id);
		fallthrough;
	हाल GB_INTERFACE_TYPE_UNIPRO:
		dev_info(&पूर्णांकf->dev, "DDBL1 Manufacturer=0x%08x, Product=0x%08x\n",
			 पूर्णांकf->ddbl1_manufacturer_id,
			 पूर्णांकf->ddbl1_product_id);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

/* Deरेजिस्टर an पूर्णांकerface. */
व्योम gb_पूर्णांकerface_del(काष्ठा gb_पूर्णांकerface *पूर्णांकf)
अणु
	अगर (device_is_रेजिस्टरed(&पूर्णांकf->dev)) अणु
		trace_gb_पूर्णांकerface_del(पूर्णांकf);

		device_del(&पूर्णांकf->dev);
		dev_info(&पूर्णांकf->dev, "Interface removed\n");
	पूर्ण
पूर्ण

व्योम gb_पूर्णांकerface_put(काष्ठा gb_पूर्णांकerface *पूर्णांकf)
अणु
	put_device(&पूर्णांकf->dev);
पूर्ण
