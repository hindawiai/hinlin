<शैली गुरु>
/*
 * Created: Tue Feb  2 08:37:54 1999 by faith@valinux.com
 *
 * Copyright 1999 Precision Insight, Inc., Cedar Park, Texas.
 * Copyright 2000 VA Linux Systems, Inc., Sunnyvale, Calअगरornia.
 * All Rights Reserved.
 *
 * Author Rickard E. (Rik) Faith <faith@valinux.com>
 * Author Gareth Hughes <gareth@valinux.com>
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

#समावेश <linux/slab.h>

#समावेश <drm/drm_auth.h>
#समावेश <drm/drm_drv.h>
#समावेश <drm/drm_file.h>
#समावेश <drm/drm_lease.h>
#समावेश <drm/drm_prपूर्णांक.h>

#समावेश "drm_internal.h"
#समावेश "drm_legacy.h"

/**
 * DOC: master and authentication
 *
 * &काष्ठा drm_master is used to track groups of clients with खोलो
 * primary/legacy device nodes. For every &काष्ठा drm_file which has had at
 * least once successfully became the device master (either through the
 * SET_MASTER IOCTL, or implicitly through खोलोing the primary device node when
 * no one अन्यथा is the current master that समय) there exists one &drm_master.
 * This is noted in &drm_file.is_master. All other clients have just a poपूर्णांकer
 * to the &drm_master they are associated with.
 *
 * In addition only one &drm_master can be the current master क्रम a &drm_device.
 * It can be चयनed through the DROP_MASTER and SET_MASTER IOCTL, or
 * implicitly through closing/खोलोeing the primary device node. See also
 * drm_is_current_master().
 *
 * Clients can authenticate against the current master (अगर it matches their own)
 * using the GETMAGIC and AUTHMAGIC IOCTLs. Together with exchanging masters,
 * this allows controlled access to the device क्रम an entire group of mutually
 * trusted clients.
 */

पूर्णांक drm_geपंचांगagic(काष्ठा drm_device *dev, व्योम *data, काष्ठा drm_file *file_priv)
अणु
	काष्ठा drm_auth *auth = data;
	पूर्णांक ret = 0;

	mutex_lock(&dev->master_mutex);
	अगर (!file_priv->magic) अणु
		ret = idr_alloc(&file_priv->master->magic_map, file_priv,
				1, 0, GFP_KERNEL);
		अगर (ret >= 0)
			file_priv->magic = ret;
	पूर्ण
	auth->magic = file_priv->magic;
	mutex_unlock(&dev->master_mutex);

	DRM_DEBUG("%u\n", auth->magic);

	वापस ret < 0 ? ret : 0;
पूर्ण

पूर्णांक drm_authmagic(काष्ठा drm_device *dev, व्योम *data,
		  काष्ठा drm_file *file_priv)
अणु
	काष्ठा drm_auth *auth = data;
	काष्ठा drm_file *file;

	DRM_DEBUG("%u\n", auth->magic);

	mutex_lock(&dev->master_mutex);
	file = idr_find(&file_priv->master->magic_map, auth->magic);
	अगर (file) अणु
		file->authenticated = 1;
		idr_replace(&file_priv->master->magic_map, शून्य, auth->magic);
	पूर्ण
	mutex_unlock(&dev->master_mutex);

	वापस file ? 0 : -EINVAL;
पूर्ण

काष्ठा drm_master *drm_master_create(काष्ठा drm_device *dev)
अणु
	काष्ठा drm_master *master;

	master = kzalloc(माप(*master), GFP_KERNEL);
	अगर (!master)
		वापस शून्य;

	kref_init(&master->refcount);
	drm_master_legacy_init(master);
	idr_init(&master->magic_map);
	master->dev = dev;

	/* initialize the tree of output resource lessees */
	INIT_LIST_HEAD(&master->lessees);
	INIT_LIST_HEAD(&master->lessee_list);
	idr_init(&master->leases);
	idr_init(&master->lessee_idr);

	वापस master;
पूर्ण

अटल व्योम drm_set_master(काष्ठा drm_device *dev, काष्ठा drm_file *fpriv,
			   bool new_master)
अणु
	dev->master = drm_master_get(fpriv->master);
	अगर (dev->driver->master_set)
		dev->driver->master_set(dev, fpriv, new_master);

	fpriv->was_master = true;
पूर्ण

अटल पूर्णांक drm_new_set_master(काष्ठा drm_device *dev, काष्ठा drm_file *fpriv)
अणु
	काष्ठा drm_master *old_master;

	lockdep_निश्चित_held_once(&dev->master_mutex);

	WARN_ON(fpriv->is_master);
	old_master = fpriv->master;
	fpriv->master = drm_master_create(dev);
	अगर (!fpriv->master) अणु
		fpriv->master = old_master;
		वापस -ENOMEM;
	पूर्ण

	fpriv->is_master = 1;
	fpriv->authenticated = 1;

	drm_set_master(dev, fpriv, true);

	अगर (old_master)
		drm_master_put(&old_master);

	वापस 0;
पूर्ण

/*
 * In the olden days the SET/DROP_MASTER ioctls used to वापस EACCES when
 * CAP_SYS_ADMIN was not set. This was used to prevent rogue applications
 * from becoming master and/or failing to release it.
 *
 * At the same समय, the first client (क्रम a given VT) is _always_ master.
 * Thus in order क्रम the ioctls to succeed, one had to _explicitly_ run the
 * application as root or flip the setuid bit.
 *
 * If the CAP_SYS_ADMIN was missing, no other client could become master...
 * EVER :-( Leading to a) the graphics session dying badly or b) a completely
 * locked session.
 *
 *
 * As some poपूर्णांक प्रणालीd-logind was पूर्णांकroduced to orchestrate and delegate
 * master as applicable. It करोes so by खोलोing the fd and passing it to users
 * जबतक in itself logind a) करोes the set/drop master per users' request and
 * b)  * implicitly drops master on VT चयन.
 *
 * Even though logind looks like the future, there are a few issues:
 *  - some platक्रमms करोn't have equivalent (Android, CrOS, some BSDs) so
 * root is required _solely_ क्रम SET/DROP MASTER.
 *  - applications may not be updated to use it,
 *  - any client which fails to drop master* can DoS the application using
 * logind, to a varying degree.
 *
 * * Either due missing CAP_SYS_ADMIN or simply not calling DROP_MASTER.
 *
 *
 * Here we implement the next best thing:
 *  - ensure the logind style of fd passing works unchanged, and
 *  - allow a client to drop/set master, अगरf it is/was master at a given poपूर्णांक
 * in समय.
 *
 * Note: DROP_MASTER cannot be मुक्त क्रम all, as an arbitrator user could:
 *  - DoS/crash the arbitrator - details would be implementation specअगरic
 *  - खोलो the node, become master implicitly and cause issues
 *
 * As a result this fixes the following when using root-less build w/o logind
 * - startx
 * - weston
 * - various compositors based on wlroots
 */
अटल पूर्णांक
drm_master_check_perm(काष्ठा drm_device *dev, काष्ठा drm_file *file_priv)
अणु
	अगर (file_priv->pid == task_pid(current) && file_priv->was_master)
		वापस 0;

	अगर (!capable(CAP_SYS_ADMIN))
		वापस -EACCES;

	वापस 0;
पूर्ण

पूर्णांक drm_seपंचांगaster_ioctl(काष्ठा drm_device *dev, व्योम *data,
			काष्ठा drm_file *file_priv)
अणु
	पूर्णांक ret;

	mutex_lock(&dev->master_mutex);

	ret = drm_master_check_perm(dev, file_priv);
	अगर (ret)
		जाओ out_unlock;

	अगर (drm_is_current_master(file_priv))
		जाओ out_unlock;

	अगर (dev->master) अणु
		ret = -EBUSY;
		जाओ out_unlock;
	पूर्ण

	अगर (!file_priv->master) अणु
		ret = -EINVAL;
		जाओ out_unlock;
	पूर्ण

	अगर (!file_priv->is_master) अणु
		ret = drm_new_set_master(dev, file_priv);
		जाओ out_unlock;
	पूर्ण

	अगर (file_priv->master->lessor != शून्य) अणु
		DRM_DEBUG_LEASE("Attempt to set lessee %d as master\n", file_priv->master->lessee_id);
		ret = -EINVAL;
		जाओ out_unlock;
	पूर्ण

	drm_set_master(dev, file_priv, false);
out_unlock:
	mutex_unlock(&dev->master_mutex);
	वापस ret;
पूर्ण

अटल व्योम drm_drop_master(काष्ठा drm_device *dev,
			    काष्ठा drm_file *fpriv)
अणु
	अगर (dev->driver->master_drop)
		dev->driver->master_drop(dev, fpriv);
	drm_master_put(&dev->master);
पूर्ण

पूर्णांक drm_dropmaster_ioctl(काष्ठा drm_device *dev, व्योम *data,
			 काष्ठा drm_file *file_priv)
अणु
	पूर्णांक ret;

	mutex_lock(&dev->master_mutex);

	ret = drm_master_check_perm(dev, file_priv);
	अगर (ret)
		जाओ out_unlock;

	अगर (!drm_is_current_master(file_priv)) अणु
		ret = -EINVAL;
		जाओ out_unlock;
	पूर्ण

	अगर (!dev->master) अणु
		ret = -EINVAL;
		जाओ out_unlock;
	पूर्ण

	अगर (file_priv->master->lessor != शून्य) अणु
		DRM_DEBUG_LEASE("Attempt to drop lessee %d as master\n", file_priv->master->lessee_id);
		ret = -EINVAL;
		जाओ out_unlock;
	पूर्ण

	drm_drop_master(dev, file_priv);
out_unlock:
	mutex_unlock(&dev->master_mutex);
	वापस ret;
पूर्ण

पूर्णांक drm_master_खोलो(काष्ठा drm_file *file_priv)
अणु
	काष्ठा drm_device *dev = file_priv->minor->dev;
	पूर्णांक ret = 0;

	/* अगर there is no current master make this fd it, but करो not create
	 * any master object क्रम render clients */
	mutex_lock(&dev->master_mutex);
	अगर (!dev->master)
		ret = drm_new_set_master(dev, file_priv);
	अन्यथा
		file_priv->master = drm_master_get(dev->master);
	mutex_unlock(&dev->master_mutex);

	वापस ret;
पूर्ण

व्योम drm_master_release(काष्ठा drm_file *file_priv)
अणु
	काष्ठा drm_device *dev = file_priv->minor->dev;
	काष्ठा drm_master *master;

	mutex_lock(&dev->master_mutex);
	master = file_priv->master;
	अगर (file_priv->magic)
		idr_हटाओ(&file_priv->master->magic_map, file_priv->magic);

	अगर (!drm_is_current_master(file_priv))
		जाओ out;

	drm_legacy_lock_master_cleanup(dev, master);

	अगर (dev->master == file_priv->master)
		drm_drop_master(dev, file_priv);
out:
	अगर (drm_core_check_feature(dev, DRIVER_MODESET) && file_priv->is_master) अणु
		/* Revoke any leases held by this or lessees, but only अगर
		 * this is the "real" master
		 */
		drm_lease_revoke(master);
	पूर्ण

	/* drop the master reference held by the file priv */
	अगर (file_priv->master)
		drm_master_put(&file_priv->master);
	mutex_unlock(&dev->master_mutex);
पूर्ण

/**
 * drm_is_current_master - checks whether @priv is the current master
 * @fpriv: DRM file निजी
 *
 * Checks whether @fpriv is current master on its device. This decides whether a
 * client is allowed to run DRM_MASTER IOCTLs.
 *
 * Most of the modern IOCTL which require DRM_MASTER are क्रम kernel modesetting
 * - the current master is assumed to own the non-shareable display hardware.
 */
bool drm_is_current_master(काष्ठा drm_file *fpriv)
अणु
	वापस fpriv->is_master && drm_lease_owner(fpriv->master) == fpriv->minor->dev->master;
पूर्ण
EXPORT_SYMBOL(drm_is_current_master);

/**
 * drm_master_get - reference a master poपूर्णांकer
 * @master: &काष्ठा drm_master
 *
 * Increments the reference count of @master and वापसs a poपूर्णांकer to @master.
 */
काष्ठा drm_master *drm_master_get(काष्ठा drm_master *master)
अणु
	kref_get(&master->refcount);
	वापस master;
पूर्ण
EXPORT_SYMBOL(drm_master_get);

अटल व्योम drm_master_destroy(काष्ठा kref *kref)
अणु
	काष्ठा drm_master *master = container_of(kref, काष्ठा drm_master, refcount);
	काष्ठा drm_device *dev = master->dev;

	अगर (drm_core_check_feature(dev, DRIVER_MODESET))
		drm_lease_destroy(master);

	drm_legacy_master_rmmaps(dev, master);

	idr_destroy(&master->magic_map);
	idr_destroy(&master->leases);
	idr_destroy(&master->lessee_idr);

	kमुक्त(master->unique);
	kमुक्त(master);
पूर्ण

/**
 * drm_master_put - unreference and clear a master poपूर्णांकer
 * @master: poपूर्णांकer to a poपूर्णांकer of &काष्ठा drm_master
 *
 * This decrements the &drm_master behind @master and sets it to शून्य.
 */
व्योम drm_master_put(काष्ठा drm_master **master)
अणु
	kref_put(&(*master)->refcount, drm_master_destroy);
	*master = शून्य;
पूर्ण
EXPORT_SYMBOL(drm_master_put);

/* Used by drm_client and drm_fb_helper */
bool drm_master_पूर्णांकernal_acquire(काष्ठा drm_device *dev)
अणु
	mutex_lock(&dev->master_mutex);
	अगर (dev->master) अणु
		mutex_unlock(&dev->master_mutex);
		वापस false;
	पूर्ण

	वापस true;
पूर्ण
EXPORT_SYMBOL(drm_master_पूर्णांकernal_acquire);

/* Used by drm_client and drm_fb_helper */
व्योम drm_master_पूर्णांकernal_release(काष्ठा drm_device *dev)
अणु
	mutex_unlock(&dev->master_mutex);
पूर्ण
EXPORT_SYMBOL(drm_master_पूर्णांकernal_release);
