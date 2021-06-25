<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *
 *  Copyright (C) 2005 Mike Isely <isely@pobox.com>
 *  Copyright (C) 2004 Aurelien Alleaume <slts@मुक्त.fr>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/module.h>
#समावेश <linux/usb.h>
#समावेश <linux/videodev2.h>

#समावेश "pvrusb2-hdw.h"
#समावेश "pvrusb2-devattr.h"
#समावेश "pvrusb2-context.h"
#समावेश "pvrusb2-debug.h"
#समावेश "pvrusb2-v4l2.h"
#अगर_घोषित CONFIG_VIDEO_PVRUSB2_SYSFS
#समावेश "pvrusb2-sysfs.h"
#पूर्ण_अगर /* CONFIG_VIDEO_PVRUSB2_SYSFS */

#घोषणा DRIVER_AUTHOR "Mike Isely <isely@pobox.com>"
#घोषणा DRIVER_DESC "Hauppauge WinTV-PVR-USB2 MPEG2 Encoder/Tuner"
#घोषणा DRIVER_VERSION "V4L in-tree version"

#घोषणा DEFAULT_DEBUG_MASK (PVR2_TRACE_ERROR_LEGS| \
			    PVR2_TRACE_INFO| \
			    PVR2_TRACE_STD| \
			    PVR2_TRACE_TOLERANCE| \
			    PVR2_TRACE_TRAP| \
			    0)

पूर्णांक pvrusb2_debug = DEFAULT_DEBUG_MASK;

module_param_named(debug,pvrusb2_debug,पूर्णांक,S_IRUGO|S_IWUSR);
MODULE_PARM_DESC(debug, "Debug trace mask");

#अगर_घोषित CONFIG_VIDEO_PVRUSB2_SYSFS
अटल काष्ठा pvr2_sysfs_class *class_ptr = शून्य;
#पूर्ण_अगर /* CONFIG_VIDEO_PVRUSB2_SYSFS */

अटल व्योम pvr_setup_attach(काष्ठा pvr2_context *pvr)
अणु
	/* Create association with v4l layer */
	pvr2_v4l2_create(pvr);
#अगर_घोषित CONFIG_VIDEO_PVRUSB2_DVB
	/* Create association with dvb layer */
	pvr2_dvb_create(pvr);
#पूर्ण_अगर
#अगर_घोषित CONFIG_VIDEO_PVRUSB2_SYSFS
	pvr2_sysfs_create(pvr,class_ptr);
#पूर्ण_अगर /* CONFIG_VIDEO_PVRUSB2_SYSFS */
पूर्ण

अटल पूर्णांक pvr_probe(काष्ठा usb_पूर्णांकerface *पूर्णांकf,
		     स्थिर काष्ठा usb_device_id *devid)
अणु
	काष्ठा pvr2_context *pvr;

	/* Create underlying hardware पूर्णांकerface */
	pvr = pvr2_context_create(पूर्णांकf,devid,pvr_setup_attach);
	अगर (!pvr) अणु
		pvr2_trace(PVR2_TRACE_ERROR_LEGS,
			   "Failed to create hdw handler");
		वापस -ENOMEM;
	पूर्ण

	pvr2_trace(PVR2_TRACE_INIT,"pvr_probe(pvr=%p)",pvr);

	usb_set_पूर्णांकfdata(पूर्णांकf, pvr);

	वापस 0;
पूर्ण

/*
 * pvr_disconnect()
 *
 */
अटल व्योम pvr_disconnect(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा pvr2_context *pvr = usb_get_पूर्णांकfdata(पूर्णांकf);

	pvr2_trace(PVR2_TRACE_INIT,"pvr_disconnect(pvr=%p) BEGIN",pvr);

	usb_set_पूर्णांकfdata (पूर्णांकf, शून्य);
	pvr2_context_disconnect(pvr);

	pvr2_trace(PVR2_TRACE_INIT,"pvr_disconnect(pvr=%p) DONE",pvr);

पूर्ण

अटल काष्ठा usb_driver pvr_driver = अणु
	.name =         "pvrusb2",
	.id_table =     pvr2_device_table,
	.probe =        pvr_probe,
	.disconnect =   pvr_disconnect
पूर्ण;

/*
 * pvr_init() / pvr_निकास()
 *
 * This code is run to initialize/निकास the driver.
 *
 */
अटल पूर्णांक __init pvr_init(व्योम)
अणु
	पूर्णांक ret;

	pvr2_trace(PVR2_TRACE_INIT,"pvr_init");

	ret = pvr2_context_global_init();
	अगर (ret != 0) अणु
		pvr2_trace(PVR2_TRACE_INIT,"pvr_init failure code=%d",ret);
		वापस ret;
	पूर्ण

#अगर_घोषित CONFIG_VIDEO_PVRUSB2_SYSFS
	class_ptr = pvr2_sysfs_class_create();
#पूर्ण_अगर /* CONFIG_VIDEO_PVRUSB2_SYSFS */

	ret = usb_रेजिस्टर(&pvr_driver);

	अगर (ret == 0)
		pr_info("pvrusb2: " DRIVER_VERSION ":"
		       DRIVER_DESC "\n");
	अगर (pvrusb2_debug)
		pr_info("pvrusb2: Debug mask is %d (0x%x)\n",
		       pvrusb2_debug,pvrusb2_debug);

	pvr2_trace(PVR2_TRACE_INIT,"pvr_init complete");

	वापस ret;
पूर्ण

अटल व्योम __निकास pvr_निकास(व्योम)
अणु
	pvr2_trace(PVR2_TRACE_INIT,"pvr_exit");

	usb_deरेजिस्टर(&pvr_driver);

	pvr2_context_global_करोne();

#अगर_घोषित CONFIG_VIDEO_PVRUSB2_SYSFS
	pvr2_sysfs_class_destroy(class_ptr);
#पूर्ण_अगर /* CONFIG_VIDEO_PVRUSB2_SYSFS */

	pvr2_trace(PVR2_TRACE_INIT,"pvr_exit complete");
पूर्ण

module_init(pvr_init);
module_निकास(pvr_निकास);

MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_LICENSE("GPL");
MODULE_VERSION("0.9.1");
