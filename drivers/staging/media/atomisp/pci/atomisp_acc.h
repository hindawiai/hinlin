<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Support क्रम Clovertrail PNW Camera Imaging ISP subप्रणाली.
 *
 * Copyright (c) 2012 Intel Corporation. All Rights Reserved.
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU General Public License version
 * 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License क्रम more details.
 *
 *
 */

#अगर_अघोषित __ATOMISP_ACC_H__
#घोषणा __ATOMISP_ACC_H__

#समावेश "../../include/linux/atomisp.h"
#समावेश "atomisp_internal.h"

#समावेश "ia_css_types.h"

/*
 * Interface functions क्रम AtomISP driver acceleration API implementation.
 */

काष्ठा atomisp_sub_device;

व्योम atomisp_acc_cleanup(काष्ठा atomisp_device *isp);

/*
 * Free up any allocated resources.
 * Must be called each समय when the device is बंदd.
 * Note that there isn't corresponding खोलो() call;
 * this function may be called sequentially multiple बार.
 * Must be called to मुक्त up resources beक्रमe driver is unloaded.
 */
व्योम atomisp_acc_release(काष्ठा atomisp_sub_device *asd);

/* Load acceleration binary. DEPRECATED. */
पूर्णांक atomisp_acc_load(काष्ठा atomisp_sub_device *asd,
		     काष्ठा atomisp_acc_fw_load *fw);

/* Load acceleration binary with specअगरied properties */
पूर्णांक atomisp_acc_load_to_pipe(काष्ठा atomisp_sub_device *asd,
			     काष्ठा atomisp_acc_fw_load_to_pipe *fw);

/* Unload specअगरied acceleration binary */
पूर्णांक atomisp_acc_unload(काष्ठा atomisp_sub_device *asd,
		       अचिन्हित पूर्णांक *handle);

/*
 * Map a memory region पूर्णांकo ISP memory space.
 */
पूर्णांक atomisp_acc_map(काष्ठा atomisp_sub_device *asd,
		    काष्ठा atomisp_acc_map *map);

/*
 * Unmap a mapped memory region.
 */
पूर्णांक atomisp_acc_unmap(काष्ठा atomisp_sub_device *asd,
		      काष्ठा atomisp_acc_map *map);

/*
 * Set acceleration binary argument to a previously mapped memory region.
 */
पूर्णांक atomisp_acc_s_mapped_arg(काष्ठा atomisp_sub_device *asd,
			     काष्ठा atomisp_acc_s_mapped_arg *arg);

/*
 * Start acceleration.
 * Return immediately, acceleration is left running in background.
 * Specअगरy either acceleration binary or pipeline which to start.
 */
पूर्णांक atomisp_acc_start(काष्ठा atomisp_sub_device *asd,
		      अचिन्हित पूर्णांक *handle);

/*
 * Wait until acceleration finishes.
 * This MUST be called after each acceleration has been started.
 * Specअगरy either acceleration binary or pipeline handle.
 */
पूर्णांक atomisp_acc_रुको(काष्ठा atomisp_sub_device *asd,
		     अचिन्हित पूर्णांक *handle);

/*
 * Used by ISR to notअगरy ACC stage finished.
 * This is पूर्णांकernally used and करोes not export as IOCTL.
 */
व्योम atomisp_acc_करोne(काष्ठा atomisp_sub_device *asd, अचिन्हित पूर्णांक handle);

/*
 * Appends the loaded acceleration binary extensions to the
 * current ISP mode. Must be called just beक्रमe atomisp_css_start().
 */
पूर्णांक atomisp_acc_load_extensions(काष्ठा atomisp_sub_device *asd);

/*
 * Must be called after streaming is stopped:
 * unloads any loaded acceleration extensions.
 */
व्योम atomisp_acc_unload_extensions(काष्ठा atomisp_sub_device *asd);

/*
 * Set acceleration firmware flags.
 */
पूर्णांक atomisp_acc_set_state(काष्ठा atomisp_sub_device *asd,
			  काष्ठा atomisp_acc_state *arg);

/*
 * Get acceleration firmware flags.
 */
पूर्णांक atomisp_acc_get_state(काष्ठा atomisp_sub_device *asd,
			  काष्ठा atomisp_acc_state *arg);

#पूर्ण_अगर /* __ATOMISP_ACC_H__ */
