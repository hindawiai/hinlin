<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright(c) 2013-2015 Intel Corporation. All rights reserved.
 */
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/module.h>
#समावेश <linux/device.h>
#समावेश <linux/sizes.h>
#समावेश <linux/ndctl.h>
#समावेश <linux/slab.h>
#समावेश <linux/mm.h>
#समावेश <linux/nd.h>
#समावेश "label.h"
#समावेश "nd.h"

अटल पूर्णांक nvdimm_probe(काष्ठा device *dev)
अणु
	काष्ठा nvdimm_drvdata *ndd;
	पूर्णांक rc;

	rc = nvdimm_security_setup_events(dev);
	अगर (rc < 0) अणु
		dev_err(dev, "security event setup failed: %d\n", rc);
		वापस rc;
	पूर्ण

	rc = nvdimm_check_config_data(dev);
	अगर (rc) अणु
		/* not required क्रम non-aliased nvdimm, ex. NVDIMM-N */
		अगर (rc == -ENOTTY)
			rc = 0;
		वापस rc;
	पूर्ण

	/*
	 * The locked status bit reflects explicit status codes from the
	 * label पढ़ोing commands, revalidate it each समय the driver is
	 * activated and re-पढ़ोs the label area.
	 */
	nvdimm_clear_locked(dev);

	ndd = kzalloc(माप(*ndd), GFP_KERNEL);
	अगर (!ndd)
		वापस -ENOMEM;

	dev_set_drvdata(dev, ndd);
	ndd->dpa.name = dev_name(dev);
	ndd->ns_current = -1;
	ndd->ns_next = -1;
	ndd->dpa.start = 0;
	ndd->dpa.end = -1;
	ndd->dev = dev;
	get_device(dev);
	kref_init(&ndd->kref);

	/*
	 * Attempt to unlock, अगर the DIMM supports security commands,
	 * otherwise the locked indication is determined by explicit
	 * status codes from the label पढ़ोing commands.
	 */
	rc = nvdimm_security_unlock(dev);
	अगर (rc < 0)
		dev_dbg(dev, "failed to unlock dimm: %d\n", rc);


	/*
	 * EACCES failures पढ़ोing the namespace label-area-properties
	 * are पूर्णांकerpreted as the DIMM capacity being locked but the
	 * namespace labels themselves being accessible.
	 */
	rc = nvdimm_init_nsarea(ndd);
	अगर (rc == -EACCES) अणु
		/*
		 * See nvdimm_namespace_common_probe() where we fail to
		 * allow namespaces to probe जबतक the DIMM is locked,
		 * but we करो allow क्रम namespace क्रमागतeration.
		 */
		nvdimm_set_locked(dev);
		rc = 0;
	पूर्ण
	अगर (rc)
		जाओ err;

	/*
	 * EACCES failures पढ़ोing the namespace label-data are
	 * पूर्णांकerpreted as the label area being locked in addition to the
	 * DIMM capacity. We fail the dimm probe to prevent regions from
	 * attempting to parse the label area.
	 */
	rc = nd_label_data_init(ndd);
	अगर (rc == -EACCES)
		nvdimm_set_locked(dev);
	अगर (rc)
		जाओ err;

	dev_dbg(dev, "config data size: %d\n", ndd->nsarea.config_size);

	nvdimm_bus_lock(dev);
	अगर (ndd->ns_current >= 0) अणु
		rc = nd_label_reserve_dpa(ndd);
		अगर (rc == 0)
			nvdimm_set_labeling(dev);
	पूर्ण
	nvdimm_bus_unlock(dev);

	अगर (rc)
		जाओ err;

	वापस 0;

 err:
	put_ndd(ndd);
	वापस rc;
पूर्ण

अटल व्योम nvdimm_हटाओ(काष्ठा device *dev)
अणु
	काष्ठा nvdimm_drvdata *ndd = dev_get_drvdata(dev);

	nvdimm_bus_lock(dev);
	dev_set_drvdata(dev, शून्य);
	nvdimm_bus_unlock(dev);
	put_ndd(ndd);
पूर्ण

अटल काष्ठा nd_device_driver nvdimm_driver = अणु
	.probe = nvdimm_probe,
	.हटाओ = nvdimm_हटाओ,
	.drv = अणु
		.name = "nvdimm",
	पूर्ण,
	.type = ND_DRIVER_DIMM,
पूर्ण;

पूर्णांक __init nvdimm_init(व्योम)
अणु
	वापस nd_driver_रेजिस्टर(&nvdimm_driver);
पूर्ण

व्योम nvdimm_निकास(व्योम)
अणु
	driver_unरेजिस्टर(&nvdimm_driver.drv);
पूर्ण

MODULE_ALIAS_ND_DEVICE(ND_DEVICE_DIMM);
