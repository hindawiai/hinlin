<शैली गुरु>
#अगर_अघोषित _DRM_AUTH_H_
#घोषणा _DRM_AUTH_H_

/*
 * Internal Header क्रम the Direct Rendering Manager
 *
 * Copyright 2016 Intel Corporation
 *
 * Author: Daniel Vetter <daniel.vetter@ffwll.ch>
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the next
 * paragraph) shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * VA LINUX SYSTEMS AND/OR ITS SUPPLIERS BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

#समावेश <linux/idr.h>
#समावेश <linux/kref.h>
#समावेश <linux/रुको.h>

काष्ठा drm_file;
काष्ठा drm_hw_lock;

/*
 * Legacy DRI1 locking data काष्ठाure. Only here instead of in drm_legacy.h क्रम
 * include ordering reasons.
 *
 * DO NOT USE.
 */
काष्ठा drm_lock_data अणु
	काष्ठा drm_hw_lock *hw_lock;
	काष्ठा drm_file *file_priv;
	रुको_queue_head_t lock_queue;
	अचिन्हित दीर्घ lock_समय;
	spinlock_t spinlock;
	uपूर्णांक32_t kernel_रुकोers;
	uपूर्णांक32_t user_रुकोers;
	पूर्णांक idle_has_lock;
पूर्ण;

/**
 * काष्ठा drm_master - drm master काष्ठाure
 *
 * @refcount: Refcount क्रम this master object.
 * @dev: Link back to the DRM device
 * @driver_priv: Poपूर्णांकer to driver-निजी inक्रमmation.
 * @lessor: Lease holder
 * @lessee_id: id क्रम lessees. Owners always have id 0
 * @lessee_list: other lessees of the same master
 * @lessees: drm_masters leasing from this one
 * @leases: Objects leased to this drm_master.
 * @lessee_idr: All lessees under this owner (only used where lessor == शून्य)
 *
 * Note that master काष्ठाures are only relevant क्रम the legacy/primary device
 * nodes, hence there can only be one per device, not one per drm_minor.
 */
काष्ठा drm_master अणु
	काष्ठा kref refcount;
	काष्ठा drm_device *dev;
	/**
	 * @unique: Unique identअगरier: e.g. busid. Protected by
	 * &drm_device.master_mutex.
	 */
	अक्षर *unique;
	/**
	 * @unique_len: Length of unique field. Protected by
	 * &drm_device.master_mutex.
	 */
	पूर्णांक unique_len;
	/**
	 * @magic_map: Map of used authentication tokens. Protected by
	 * &drm_device.master_mutex.
	 */
	काष्ठा idr magic_map;
	व्योम *driver_priv;

	/* Tree of display resource leases, each of which is a drm_master काष्ठा
	 * All of these get activated simultaneously, so drm_device master poपूर्णांकs
	 * at the top of the tree (क्रम which lessor is शून्य). Protected by
	 * &drm_device.mode_config.idr_mutex.
	 */

	काष्ठा drm_master *lessor;
	पूर्णांक	lessee_id;
	काष्ठा list_head lessee_list;
	काष्ठा list_head lessees;
	काष्ठा idr leases;
	काष्ठा idr lessee_idr;
	/* निजी: */
#अगर IS_ENABLED(CONFIG_DRM_LEGACY)
	काष्ठा drm_lock_data lock;
#पूर्ण_अगर
पूर्ण;

काष्ठा drm_master *drm_master_get(काष्ठा drm_master *master);
व्योम drm_master_put(काष्ठा drm_master **master);
bool drm_is_current_master(काष्ठा drm_file *fpriv);

काष्ठा drm_master *drm_master_create(काष्ठा drm_device *dev);

#पूर्ण_अगर
