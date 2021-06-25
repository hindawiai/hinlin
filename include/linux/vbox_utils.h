<शैली गुरु>
/* SPDX-License-Identअगरier: (GPL-2.0 OR CDDL-1.0) */
/* Copyright (C) 2006-2016 Oracle Corporation */

#अगर_अघोषित __VBOX_UTILS_H__
#घोषणा __VBOX_UTILS_H__

#समावेश <linux/prपूर्णांकk.h>
#समावेश <linux/vbox_vmmdev_types.h>

काष्ठा vbg_dev;

/**
 * vboxguest logging functions, these log both to the backकरोor and call
 * the equivalent kernel pr_foo function.
 */
__म_लिखो(1, 2) व्योम vbg_info(स्थिर अक्षर *fmt, ...);
__म_लिखो(1, 2) व्योम vbg_warn(स्थिर अक्षर *fmt, ...);
__म_लिखो(1, 2) व्योम vbg_err(स्थिर अक्षर *fmt, ...);
__म_लिखो(1, 2) व्योम vbg_err_ratelimited(स्थिर अक्षर *fmt, ...);

/* Only use backकरोor logging क्रम non-dynamic debug builds */
#अगर defined(DEBUG) && !defined(CONFIG_DYNAMIC_DEBUG)
__म_लिखो(1, 2) व्योम vbg_debug(स्थिर अक्षर *fmt, ...);
#अन्यथा
#घोषणा vbg_debug pr_debug
#पूर्ण_अगर

पूर्णांक vbg_hgcm_connect(काष्ठा vbg_dev *gdev, u32 requestor,
		     काष्ठा vmmdev_hgcm_service_location *loc,
		     u32 *client_id, पूर्णांक *vbox_status);

पूर्णांक vbg_hgcm_disconnect(काष्ठा vbg_dev *gdev, u32 requestor,
			u32 client_id, पूर्णांक *vbox_status);

पूर्णांक vbg_hgcm_call(काष्ठा vbg_dev *gdev, u32 requestor, u32 client_id,
		  u32 function, u32 समयout_ms,
		  काष्ठा vmmdev_hgcm_function_parameter *parms, u32 parm_count,
		  पूर्णांक *vbox_status);

/**
 * Convert a VirtualBox status code to a standard Linux kernel वापस value.
 * Return: 0 or negative त्रुटि_सं value.
 * @rc:			VirtualBox status code to convert.
 */
पूर्णांक vbg_status_code_to_त्रुटि_सं(पूर्णांक rc);

/**
 * Helper क्रम the vboxsf driver to get a reference to the guest device.
 * Return: a poपूर्णांकer to the gdev; or a ERR_PTR value on error.
 */
काष्ठा vbg_dev *vbg_get_gdev(व्योम);

/**
 * Helper क्रम the vboxsf driver to put a guest device reference.
 * @gdev:		Reference वापसed by vbg_get_gdev to put.
 */
व्योम vbg_put_gdev(काष्ठा vbg_dev *gdev);

#पूर्ण_अगर
