<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * SCSI device handler infraकाष्ठाure.
 *
 * Copyright IBM Corporation, 2007
 *      Authors:
 *               Chandra Seetharaman <sekharan@us.ibm.com>
 *               Mike Anderson <andmike@linux.vnet.ibm.com>
 */

#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <scsi/scsi_dh.h>
#समावेश "scsi_priv.h"

अटल DEFINE_SPINLOCK(list_lock);
अटल LIST_HEAD(scsi_dh_list);

काष्ठा scsi_dh_blist अणु
	स्थिर अक्षर *venकरोr;
	स्थिर अक्षर *model;
	स्थिर अक्षर *driver;
पूर्ण;

अटल स्थिर काष्ठा scsi_dh_blist scsi_dh_blist[] = अणु
	अणु"DGC", "RAID",			"emc" पूर्ण,
	अणु"DGC", "DISK",			"emc" पूर्ण,
	अणु"DGC", "VRAID",		"emc" पूर्ण,

	अणु"COMPAQ", "MSA1000 VOLUME",	"hp_sw" पूर्ण,
	अणु"COMPAQ", "HSV110",		"hp_sw" पूर्ण,
	अणु"HP", "HSV100",		"hp_sw"पूर्ण,
	अणु"DEC", "HSG80",		"hp_sw"पूर्ण,

	अणु"IBM", "1722",			"rdac", पूर्ण,
	अणु"IBM", "1724",			"rdac", पूर्ण,
	अणु"IBM", "1726",			"rdac", पूर्ण,
	अणु"IBM", "1742",			"rdac", पूर्ण,
	अणु"IBM", "1745",			"rdac", पूर्ण,
	अणु"IBM", "1746",			"rdac", पूर्ण,
	अणु"IBM", "1813",			"rdac", पूर्ण,
	अणु"IBM", "1814",			"rdac", पूर्ण,
	अणु"IBM", "1815",			"rdac", पूर्ण,
	अणु"IBM", "1818",			"rdac", पूर्ण,
	अणु"IBM", "3526",			"rdac", पूर्ण,
	अणु"IBM", "3542",			"rdac", पूर्ण,
	अणु"IBM", "3552",			"rdac", पूर्ण,
	अणु"SGI", "TP9300",		"rdac", पूर्ण,
	अणु"SGI", "TP9400",		"rdac", पूर्ण,
	अणु"SGI", "TP9500",		"rdac", पूर्ण,
	अणु"SGI", "TP9700",		"rdac", पूर्ण,
	अणु"SGI", "IS",			"rdac", पूर्ण,
	अणु"STK", "OPENstorage",		"rdac", पूर्ण,
	अणु"STK", "FLEXLINE 380",		"rdac", पूर्ण,
	अणु"STK", "BladeCtlr",		"rdac", पूर्ण,
	अणु"SUN", "CSM",			"rdac", पूर्ण,
	अणु"SUN", "LCSM100",		"rdac", पूर्ण,
	अणु"SUN", "STK6580_6780",		"rdac", पूर्ण,
	अणु"SUN", "SUN_6180",		"rdac", पूर्ण,
	अणु"SUN", "ArrayStorage",		"rdac", पूर्ण,
	अणु"DELL", "MD3",			"rdac", पूर्ण,
	अणु"NETAPP", "INF-01-00",		"rdac", पूर्ण,
	अणु"LSI", "INF-01-00",		"rdac", पूर्ण,
	अणु"ENGENIO", "INF-01-00",	"rdac", पूर्ण,
	अणु"LENOVO", "DE_Series",		"rdac", पूर्ण,
	अणु"FUJITSU", "ETERNUS_AHB",	"rdac", पूर्ण,
	अणुशून्य, शून्य,			शून्य पूर्ण,
पूर्ण;

अटल स्थिर अक्षर *
scsi_dh_find_driver(काष्ठा scsi_device *sdev)
अणु
	स्थिर काष्ठा scsi_dh_blist *b;

	अगर (scsi_device_tpgs(sdev))
		वापस "alua";

	क्रम (b = scsi_dh_blist; b->venकरोr; b++) अणु
		अगर (!म_भेदन(sdev->venकरोr, b->venकरोr, म_माप(b->venकरोr)) &&
		    !म_भेदन(sdev->model, b->model, म_माप(b->model))) अणु
			वापस b->driver;
		पूर्ण
	पूर्ण
	वापस शून्य;
पूर्ण


अटल काष्ठा scsi_device_handler *__scsi_dh_lookup(स्थिर अक्षर *name)
अणु
	काष्ठा scsi_device_handler *पंचांगp, *found = शून्य;

	spin_lock(&list_lock);
	list_क्रम_each_entry(पंचांगp, &scsi_dh_list, list) अणु
		अगर (!म_भेदन(पंचांगp->name, name, म_माप(पंचांगp->name))) अणु
			found = पंचांगp;
			अवरोध;
		पूर्ण
	पूर्ण
	spin_unlock(&list_lock);
	वापस found;
पूर्ण

अटल काष्ठा scsi_device_handler *scsi_dh_lookup(स्थिर अक्षर *name)
अणु
	काष्ठा scsi_device_handler *dh;

	अगर (!name || म_माप(name) == 0)
		वापस शून्य;

	dh = __scsi_dh_lookup(name);
	अगर (!dh) अणु
		request_module("scsi_dh_%s", name);
		dh = __scsi_dh_lookup(name);
	पूर्ण

	वापस dh;
पूर्ण

/*
 * scsi_dh_handler_attach - Attach a device handler to a device
 * @sdev - SCSI device the device handler should attach to
 * @scsi_dh - The device handler to attach
 */
अटल पूर्णांक scsi_dh_handler_attach(काष्ठा scsi_device *sdev,
				  काष्ठा scsi_device_handler *scsi_dh)
अणु
	पूर्णांक error, ret = 0;

	अगर (!try_module_get(scsi_dh->module))
		वापस -EINVAL;

	error = scsi_dh->attach(sdev);
	अगर (error != SCSI_DH_OK) अणु
		चयन (error) अणु
		हाल SCSI_DH_NOMEM:
			ret = -ENOMEM;
			अवरोध;
		हाल SCSI_DH_RES_TEMP_UNAVAIL:
			ret = -EAGAIN;
			अवरोध;
		हाल SCSI_DH_DEV_UNSUPP:
		हाल SCSI_DH_NOSYS:
			ret = -ENODEV;
			अवरोध;
		शेष:
			ret = -EINVAL;
			अवरोध;
		पूर्ण
		अगर (ret != -ENODEV)
			sdev_prपूर्णांकk(KERN_ERR, sdev, "%s: Attach failed (%d)\n",
				    scsi_dh->name, error);
		module_put(scsi_dh->module);
	पूर्ण अन्यथा
		sdev->handler = scsi_dh;

	वापस ret;
पूर्ण

/*
 * scsi_dh_handler_detach - Detach a device handler from a device
 * @sdev - SCSI device the device handler should be detached from
 */
अटल व्योम scsi_dh_handler_detach(काष्ठा scsi_device *sdev)
अणु
	sdev->handler->detach(sdev);
	sdev_prपूर्णांकk(KERN_NOTICE, sdev, "%s: Detached\n", sdev->handler->name);
	module_put(sdev->handler->module);
पूर्ण

व्योम scsi_dh_add_device(काष्ठा scsi_device *sdev)
अणु
	काष्ठा scsi_device_handler *devinfo = शून्य;
	स्थिर अक्षर *drv;

	drv = scsi_dh_find_driver(sdev);
	अगर (drv)
		devinfo = __scsi_dh_lookup(drv);
	/*
	 * device_handler is optional, so ignore errors
	 * from scsi_dh_handler_attach()
	 */
	अगर (devinfo)
		(व्योम)scsi_dh_handler_attach(sdev, devinfo);
पूर्ण

व्योम scsi_dh_release_device(काष्ठा scsi_device *sdev)
अणु
	अगर (sdev->handler)
		scsi_dh_handler_detach(sdev);
पूर्ण

/*
 * scsi_रेजिस्टर_device_handler - रेजिस्टर a device handler personality
 *      module.
 * @scsi_dh - device handler to be रेजिस्टरed.
 *
 * Returns 0 on success, -EBUSY अगर handler alपढ़ोy रेजिस्टरed.
 */
पूर्णांक scsi_रेजिस्टर_device_handler(काष्ठा scsi_device_handler *scsi_dh)
अणु
	अगर (__scsi_dh_lookup(scsi_dh->name))
		वापस -EBUSY;

	अगर (!scsi_dh->attach || !scsi_dh->detach)
		वापस -EINVAL;

	spin_lock(&list_lock);
	list_add(&scsi_dh->list, &scsi_dh_list);
	spin_unlock(&list_lock);

	prपूर्णांकk(KERN_INFO "%s: device handler registered\n", scsi_dh->name);

	वापस SCSI_DH_OK;
पूर्ण
EXPORT_SYMBOL_GPL(scsi_रेजिस्टर_device_handler);

/*
 * scsi_unरेजिस्टर_device_handler - रेजिस्टर a device handler personality
 *      module.
 * @scsi_dh - device handler to be unरेजिस्टरed.
 *
 * Returns 0 on success, -ENODEV अगर handler not रेजिस्टरed.
 */
पूर्णांक scsi_unरेजिस्टर_device_handler(काष्ठा scsi_device_handler *scsi_dh)
अणु
	अगर (!__scsi_dh_lookup(scsi_dh->name))
		वापस -ENODEV;

	spin_lock(&list_lock);
	list_del(&scsi_dh->list);
	spin_unlock(&list_lock);
	prपूर्णांकk(KERN_INFO "%s: device handler unregistered\n", scsi_dh->name);

	वापस SCSI_DH_OK;
पूर्ण
EXPORT_SYMBOL_GPL(scsi_unरेजिस्टर_device_handler);

/*
 * scsi_dh_activate - activate the path associated with the scsi_device
 *      corresponding to the given request queue.
 *     Returns immediately without रुकोing क्रम activation to be completed.
 * @q    - Request queue that is associated with the scsi_device to be
 *         activated.
 * @fn   - Function to be called upon completion of the activation.
 *         Function fn is called with data (below) and the error code.
 *         Function fn may be called from the same calling context. So,
 *         करो not hold the lock in the caller which may be needed in fn.
 * @data - data passed to the function fn upon completion.
 *
 */
पूर्णांक scsi_dh_activate(काष्ठा request_queue *q, activate_complete fn, व्योम *data)
अणु
	काष्ठा scsi_device *sdev;
	पूर्णांक err = SCSI_DH_NOSYS;

	sdev = scsi_device_from_queue(q);
	अगर (!sdev) अणु
		अगर (fn)
			fn(data, err);
		वापस err;
	पूर्ण

	अगर (!sdev->handler)
		जाओ out_fn;
	err = SCSI_DH_NOTCONN;
	अगर (sdev->sdev_state == SDEV_CANCEL ||
	    sdev->sdev_state == SDEV_DEL)
		जाओ out_fn;

	err = SCSI_DH_DEV_OFFLINED;
	अगर (sdev->sdev_state == SDEV_OFFLINE)
		जाओ out_fn;

	अगर (sdev->handler->activate)
		err = sdev->handler->activate(sdev, fn, data);

out_put_device:
	put_device(&sdev->sdev_gendev);
	वापस err;

out_fn:
	अगर (fn)
		fn(data, err);
	जाओ out_put_device;
पूर्ण
EXPORT_SYMBOL_GPL(scsi_dh_activate);

/*
 * scsi_dh_set_params - set the parameters क्रम the device as per the
 *      string specअगरied in params.
 * @q - Request queue that is associated with the scsi_device क्रम
 *      which the parameters to be set.
 * @params - parameters in the following क्रमmat
 *      "no_of_params\0param1\0param2\0param3\0...\0"
 *      क्रम example, string क्रम 2 parameters with value 10 and 21
 *      is specअगरied as "2\010\021\0".
 */
पूर्णांक scsi_dh_set_params(काष्ठा request_queue *q, स्थिर अक्षर *params)
अणु
	काष्ठा scsi_device *sdev;
	पूर्णांक err = -SCSI_DH_NOSYS;

	sdev = scsi_device_from_queue(q);
	अगर (!sdev)
		वापस err;

	अगर (sdev->handler && sdev->handler->set_params)
		err = sdev->handler->set_params(sdev, params);
	put_device(&sdev->sdev_gendev);
	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(scsi_dh_set_params);

/*
 * scsi_dh_attach - Attach device handler
 * @q - Request queue that is associated with the scsi_device
 *      the handler should be attached to
 * @name - name of the handler to attach
 */
पूर्णांक scsi_dh_attach(काष्ठा request_queue *q, स्थिर अक्षर *name)
अणु
	काष्ठा scsi_device *sdev;
	काष्ठा scsi_device_handler *scsi_dh;
	पूर्णांक err = 0;

	sdev = scsi_device_from_queue(q);
	अगर (!sdev)
		वापस -ENODEV;

	scsi_dh = scsi_dh_lookup(name);
	अगर (!scsi_dh) अणु
		err = -EINVAL;
		जाओ out_put_device;
	पूर्ण

	अगर (sdev->handler) अणु
		अगर (sdev->handler != scsi_dh)
			err = -EBUSY;
		जाओ out_put_device;
	पूर्ण

	err = scsi_dh_handler_attach(sdev, scsi_dh);

out_put_device:
	put_device(&sdev->sdev_gendev);
	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(scsi_dh_attach);

/*
 * scsi_dh_attached_handler_name - Get attached device handler's name
 * @q - Request queue that is associated with the scsi_device
 *      that may have a device handler attached
 * @gfp - the GFP mask used in the kदो_स्मृति() call when allocating memory
 *
 * Returns name of attached handler, शून्य अगर no handler is attached.
 * Caller must take care to मुक्त the वापसed string.
 */
स्थिर अक्षर *scsi_dh_attached_handler_name(काष्ठा request_queue *q, gfp_t gfp)
अणु
	काष्ठा scsi_device *sdev;
	स्थिर अक्षर *handler_name = शून्य;

	sdev = scsi_device_from_queue(q);
	अगर (!sdev)
		वापस शून्य;

	अगर (sdev->handler)
		handler_name = kstrdup(sdev->handler->name, gfp);
	put_device(&sdev->sdev_gendev);
	वापस handler_name;
पूर्ण
EXPORT_SYMBOL_GPL(scsi_dh_attached_handler_name);
