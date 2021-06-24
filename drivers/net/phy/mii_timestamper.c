<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// Support क्रम generic समय stamping devices on MII buses.
// Copyright (C) 2018 Riअक्षरd Cochran <riअक्षरdcochran@gmail.com>
//

#समावेश <linux/mii_बारtamper.h>

अटल LIST_HEAD(mii_बारtamping_devices);
अटल DEFINE_MUTEX(tstamping_devices_lock);

काष्ठा mii_बारtamping_desc अणु
	काष्ठा list_head list;
	काष्ठा mii_बारtamping_ctrl *ctrl;
	काष्ठा device *device;
पूर्ण;

/**
 * रेजिस्टर_mii_tstamp_controller() - रेजिस्टरs an MII समय stamping device.
 *
 * @device:	The device to be रेजिस्टरed.
 * @ctrl:	Poपूर्णांकer to device's control पूर्णांकerface.
 *
 * Returns zero on success or non-zero on failure.
 */
पूर्णांक रेजिस्टर_mii_tstamp_controller(काष्ठा device *device,
				   काष्ठा mii_बारtamping_ctrl *ctrl)
अणु
	काष्ठा mii_बारtamping_desc *desc;

	desc = kzalloc(माप(*desc), GFP_KERNEL);
	अगर (!desc)
		वापस -ENOMEM;

	INIT_LIST_HEAD(&desc->list);
	desc->ctrl = ctrl;
	desc->device = device;

	mutex_lock(&tstamping_devices_lock);
	list_add_tail(&mii_बारtamping_devices, &desc->list);
	mutex_unlock(&tstamping_devices_lock);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(रेजिस्टर_mii_tstamp_controller);

/**
 * unरेजिस्टर_mii_tstamp_controller() - unरेजिस्टरs an MII समय stamping device.
 *
 * @device:	A device previously passed to रेजिस्टर_mii_tstamp_controller().
 */
व्योम unरेजिस्टर_mii_tstamp_controller(काष्ठा device *device)
अणु
	काष्ठा mii_बारtamping_desc *desc;
	काष्ठा list_head *this, *next;

	mutex_lock(&tstamping_devices_lock);
	list_क्रम_each_safe(this, next, &mii_बारtamping_devices) अणु
		desc = list_entry(this, काष्ठा mii_बारtamping_desc, list);
		अगर (desc->device == device) अणु
			list_del_init(&desc->list);
			kमुक्त(desc);
			अवरोध;
		पूर्ण
	पूर्ण
	mutex_unlock(&tstamping_devices_lock);
पूर्ण
EXPORT_SYMBOL(unरेजिस्टर_mii_tstamp_controller);

/**
 * रेजिस्टर_mii_बारtamper - Enables a given port of an MII समय stamper.
 *
 * @node:	The device tree node of the MII समय stamp controller.
 * @port:	The index of the port to be enabled.
 *
 * Returns a valid पूर्णांकerface on success or ERR_PTR otherwise.
 */
काष्ठा mii_बारtamper *रेजिस्टर_mii_बारtamper(काष्ठा device_node *node,
						 अचिन्हित पूर्णांक port)
अणु
	काष्ठा mii_बारtamper *mii_ts = शून्य;
	काष्ठा mii_बारtamping_desc *desc;
	काष्ठा list_head *this;

	mutex_lock(&tstamping_devices_lock);
	list_क्रम_each(this, &mii_बारtamping_devices) अणु
		desc = list_entry(this, काष्ठा mii_बारtamping_desc, list);
		अगर (desc->device->of_node == node) अणु
			mii_ts = desc->ctrl->probe_channel(desc->device, port);
			अगर (!IS_ERR(mii_ts)) अणु
				mii_ts->device = desc->device;
				get_device(desc->device);
			पूर्ण
			अवरोध;
		पूर्ण
	पूर्ण
	mutex_unlock(&tstamping_devices_lock);

	वापस mii_ts ? mii_ts : ERR_PTR(-EPROBE_DEFER);
पूर्ण
EXPORT_SYMBOL(रेजिस्टर_mii_बारtamper);

/**
 * unरेजिस्टर_mii_बारtamper - Disables a given MII समय stamper.
 *
 * @mii_ts:	An पूर्णांकerface obtained via रेजिस्टर_mii_बारtamper().
 *
 */
व्योम unरेजिस्टर_mii_बारtamper(काष्ठा mii_बारtamper *mii_ts)
अणु
	काष्ठा mii_बारtamping_desc *desc;
	काष्ठा list_head *this;

	/* mii_बारtamper अटलally रेजिस्टरed by the PHY driver won't use the
	 * रेजिस्टर_mii_बारtamper() and thus करोn't have ->device set. Don't
	 * try to unरेजिस्टर these.
	 */
	अगर (!mii_ts->device)
		वापस;

	mutex_lock(&tstamping_devices_lock);
	list_क्रम_each(this, &mii_बारtamping_devices) अणु
		desc = list_entry(this, काष्ठा mii_बारtamping_desc, list);
		अगर (desc->device == mii_ts->device) अणु
			desc->ctrl->release_channel(desc->device, mii_ts);
			put_device(desc->device);
			अवरोध;
		पूर्ण
	पूर्ण
	mutex_unlock(&tstamping_devices_lock);
पूर्ण
EXPORT_SYMBOL(unरेजिस्टर_mii_बारtamper);
