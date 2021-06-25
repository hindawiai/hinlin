<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
  * Copyright (C) 2010 Brian King IBM Corporation
  */

#समावेश <linux/cpu.h>
#समावेश <linux/delay.h>
#समावेश <linux/suspend.h>
#समावेश <linux/स्थिति.स>
#समावेश <यंत्र/firmware.h>
#समावेश <यंत्र/hvcall.h>
#समावेश <यंत्र/machdep.h>
#समावेश <यंत्र/mmu.h>
#समावेश <यंत्र/rtas.h>
#समावेश <यंत्र/topology.h>

अटल काष्ठा device suspend_dev;

/**
 * pseries_suspend_begin - First phase of hibernation
 *
 * Check to ensure we are in a valid state to hibernate
 *
 * Return value:
 * 	0 on success / other on failure
 **/
अटल पूर्णांक pseries_suspend_begin(u64 stream_id)
अणु
	दीर्घ vasi_state, rc;
	अचिन्हित दीर्घ retbuf[PLPAR_HCALL_बफ_मानE];

	/* Make sure the state is valid */
	rc = plpar_hcall(H_VASI_STATE, retbuf, stream_id);

	vasi_state = retbuf[0];

	अगर (rc) अणु
		pr_err("pseries_suspend_begin: vasi_state returned %ld\n",rc);
		वापस rc;
	पूर्ण अन्यथा अगर (vasi_state == H_VASI_ENABLED) अणु
		वापस -EAGAIN;
	पूर्ण अन्यथा अगर (vasi_state != H_VASI_SUSPENDING) अणु
		pr_err("pseries_suspend_begin: vasi_state returned state %ld\n",
		       vasi_state);
		वापस -EIO;
	पूर्ण
	वापस 0;
पूर्ण

/**
 * pseries_suspend_enter - Final phase of hibernation
 *
 * Return value:
 * 	0 on success / other on failure
 **/
अटल पूर्णांक pseries_suspend_enter(suspend_state_t state)
अणु
	वापस rtas_ibm_suspend_me(शून्य);
पूर्ण

/**
 * store_hibernate - Initiate partition hibernation
 * @dev:		subsys root device
 * @attr:		device attribute काष्ठा
 * @buf:		buffer
 * @count:		buffer size
 *
 * Write the stream ID received from the HMC to this file
 * to trigger hibernating the partition
 *
 * Return value:
 * 	number of bytes prपूर्णांकed to buffer / other on failure
 **/
अटल sमाप_प्रकार store_hibernate(काष्ठा device *dev,
			       काष्ठा device_attribute *attr,
			       स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	u64 stream_id;
	पूर्णांक rc;

	अगर (!capable(CAP_SYS_ADMIN))
		वापस -EPERM;

	stream_id = simple_म_से_अदीर्घ(buf, शून्य, 16);

	करो अणु
		rc = pseries_suspend_begin(stream_id);
		अगर (rc == -EAGAIN)
			ssleep(1);
	पूर्ण जबतक (rc == -EAGAIN);

	अगर (!rc)
		rc = pm_suspend(PM_SUSPEND_MEM);

	अगर (!rc) अणु
		rc = count;
		post_mobility_fixup();
	पूर्ण


	वापस rc;
पूर्ण

#घोषणा USER_DT_UPDATE	0
#घोषणा KERN_DT_UPDATE	1

/**
 * show_hibernate - Report device tree update responsibilty
 * @dev:		subsys root device
 * @attr:		device attribute काष्ठा
 * @buf:		buffer
 *
 * Report whether a device tree update is perक्रमmed by the kernel after a
 * resume, or अगर drmgr must coordinate the update from user space.
 *
 * Return value:
 *	0 अगर drmgr is to initiate update, and 1 otherwise
 **/
अटल sमाप_प्रकार show_hibernate(काष्ठा device *dev,
			      काष्ठा device_attribute *attr,
			      अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "%d\n", KERN_DT_UPDATE);
पूर्ण

अटल DEVICE_ATTR(hibernate, 0644, show_hibernate, store_hibernate);

अटल काष्ठा bus_type suspend_subsys = अणु
	.name = "power",
	.dev_name = "power",
पूर्ण;

अटल स्थिर काष्ठा platक्रमm_suspend_ops pseries_suspend_ops = अणु
	.valid		= suspend_valid_only_mem,
	.enter		= pseries_suspend_enter,
पूर्ण;

/**
 * pseries_suspend_sysfs_रेजिस्टर - Register with sysfs
 *
 * Return value:
 * 	0 on success / other on failure
 **/
अटल पूर्णांक pseries_suspend_sysfs_रेजिस्टर(काष्ठा device *dev)
अणु
	पूर्णांक rc;

	अगर ((rc = subsys_प्रणाली_रेजिस्टर(&suspend_subsys, शून्य)))
		वापस rc;

	dev->id = 0;
	dev->bus = &suspend_subsys;

	अगर ((rc = device_create_file(suspend_subsys.dev_root, &dev_attr_hibernate)))
		जाओ subsys_unरेजिस्टर;

	वापस 0;

subsys_unरेजिस्टर:
	bus_unरेजिस्टर(&suspend_subsys);
	वापस rc;
पूर्ण

/**
 * pseries_suspend_init - initcall क्रम pSeries suspend
 *
 * Return value:
 * 	0 on success / other on failure
 **/
अटल पूर्णांक __init pseries_suspend_init(व्योम)
अणु
	पूर्णांक rc;

	अगर (!firmware_has_feature(FW_FEATURE_LPAR))
		वापस 0;

	अगर ((rc = pseries_suspend_sysfs_रेजिस्टर(&suspend_dev)))
		वापस rc;

	suspend_set_ops(&pseries_suspend_ops);
	वापस 0;
पूर्ण
machine_device_initcall(pseries, pseries_suspend_init);
