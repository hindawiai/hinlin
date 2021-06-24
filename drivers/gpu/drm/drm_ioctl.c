<शैली गुरु>
/*
 * Created: Fri Jan  8 09:01:26 1999 by faith@valinux.com
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

#समावेश <linux/export.h>
#समावेश <linux/nospec.h>
#समावेश <linux/pci.h>
#समावेश <linux/uaccess.h>

#समावेश <drm/drm_agpsupport.h>
#समावेश <drm/drm_auth.h>
#समावेश <drm/drm_crtc.h>
#समावेश <drm/drm_drv.h>
#समावेश <drm/drm_file.h>
#समावेश <drm/drm_ioctl.h>
#समावेश <drm/drm_prपूर्णांक.h>

#समावेश "drm_crtc_internal.h"
#समावेश "drm_internal.h"
#समावेश "drm_legacy.h"

/**
 * DOC: getunique and setversion story
 *
 * BEWARE THE DRAGONS! MIND THE TRAPDOORS!
 *
 * In an attempt to warn anyone अन्यथा who's trying to figure out what's going
 * on here, I'll try to summarize the story. First things first, let's clear up
 * the names, because the kernel पूर्णांकernals, libdrm and the ioctls are all named
 * dअगरferently:
 *
 *  - GET_UNIQUE ioctl, implemented by drm_getunique is wrapped up in libdrm
 *    through the drmGetBusid function.
 *  - The libdrm drmSetBusid function is backed by the SET_UNIQUE ioctl. All
 *    that code is nerved in the kernel with drm_invalid_op().
 *  - The पूर्णांकernal set_busid kernel functions and driver callbacks are
 *    exclusively use by the SET_VERSION ioctl, because only drm 1.0 (which is
 *    nerved) allowed userspace to set the busid through the above ioctl.
 *  - Other ioctls and functions involved are named consistently.
 *
 * For anyone wondering what's the dअगरference between drm 1.1 and 1.4: Correctly
 * handling pci करोमुख्यs in the busid on ppc. Doing this correctly was only
 * implemented in libdrm in 2010, hence can't be nerved yet. No one knows what's
 * special with drm 1.2 and 1.3.
 *
 * Now the actual horror story of how device lookup in drm works. At large,
 * there's 2 dअगरferent ways, either by busid, or by device driver name.
 *
 * Opening by busid is fairly simple:
 *
 * 1. First call SET_VERSION to make sure pci करोमुख्यs are handled properly. As a
 *    side-effect this fills out the unique name in the master काष्ठाure.
 * 2. Call GET_UNIQUE to पढ़ो out the unique name from the master काष्ठाure,
 *    which matches the busid thanks to step 1. If it करोesn't, proceed to try
 *    the next device node.
 *
 * Opening by name is slightly dअगरferent:
 *
 * 1. Directly call VERSION to get the version and to match against the driver
 *    name वापसed by that ioctl. Note that SET_VERSION is not called, which
 *    means the the unique name क्रम the master node just खोलोing is _not_ filled
 *    out. This despite that with current drm device nodes are always bound to
 *    one device, and can't be runसमय asचिन्हित like with drm 1.0.
 * 2. Match driver name. If it mismatches, proceed to the next device node.
 * 3. Call GET_UNIQUE, and check whether the unique name has length zero (by
 *    checking that the first byte in the string is 0). If that's not the हाल
 *    libdrm skips and proceeds to the next device node. Probably this is just
 *    copypasta from drm 1.0 बार where a set unique name meant that the driver
 *    was in use alपढ़ोy, but that's just conjecture.
 *
 * Long story लघु: To keep the खोलो by name logic working, GET_UNIQUE must
 * _not_ वापस a unique string when SET_VERSION hasn't been called yet,
 * otherwise libdrm अवरोधs. Even when that unique string can't ever change, and
 * is totally irrelevant क्रम actually खोलोing the device because runसमय
 * assignable device instances were only support in drm 1.0, which is दीर्घ dead.
 * But the libdrm code in drmOpenByName somehow survived, hence this can't be
 * broken.
 */

/*
 * Get the bus id.
 *
 * \param inode device inode.
 * \param file_priv DRM file निजी.
 * \param cmd command.
 * \param arg user argument, poपूर्णांकing to a drm_unique काष्ठाure.
 * \लeturn zero on success or a negative number on failure.
 *
 * Copies the bus id from drm_device::unique पूर्णांकo user space.
 */
पूर्णांक drm_getunique(काष्ठा drm_device *dev, व्योम *data,
		  काष्ठा drm_file *file_priv)
अणु
	काष्ठा drm_unique *u = data;
	काष्ठा drm_master *master;

	mutex_lock(&dev->master_mutex);
	master = file_priv->master;
	अगर (u->unique_len >= master->unique_len) अणु
		अगर (copy_to_user(u->unique, master->unique, master->unique_len)) अणु
			mutex_unlock(&dev->master_mutex);
			वापस -EFAULT;
		पूर्ण
	पूर्ण
	u->unique_len = master->unique_len;
	mutex_unlock(&dev->master_mutex);

	वापस 0;
पूर्ण

अटल व्योम
drm_unset_busid(काष्ठा drm_device *dev,
		काष्ठा drm_master *master)
अणु
	kमुक्त(master->unique);
	master->unique = शून्य;
	master->unique_len = 0;
पूर्ण

अटल पूर्णांक drm_set_busid(काष्ठा drm_device *dev, काष्ठा drm_file *file_priv)
अणु
	काष्ठा drm_master *master = file_priv->master;
	पूर्णांक ret;

	अगर (master->unique != शून्य)
		drm_unset_busid(dev, master);

	अगर (dev->dev && dev_is_pci(dev->dev)) अणु
		ret = drm_pci_set_busid(dev, master);
		अगर (ret) अणु
			drm_unset_busid(dev, master);
			वापस ret;
		पूर्ण
	पूर्ण अन्यथा अणु
		WARN_ON(!dev->unique);
		master->unique = kstrdup(dev->unique, GFP_KERNEL);
		अगर (master->unique)
			master->unique_len = म_माप(dev->unique);
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Get client inक्रमmation.
 *
 * \param inode device inode.
 * \param file_priv DRM file निजी.
 * \param cmd command.
 * \param arg user argument, poपूर्णांकing to a drm_client काष्ठाure.
 *
 * \लeturn zero on success or a negative number on failure.
 *
 * Searches क्रम the client with the specअगरied index and copies its inक्रमmation
 * पूर्णांकo userspace
 */
पूर्णांक drm_अ_लोlient(काष्ठा drm_device *dev, व्योम *data,
		  काष्ठा drm_file *file_priv)
अणु
	काष्ठा drm_client *client = data;

	/*
	 * Hollowed-out अ_लोlient ioctl to keep some dead old drm tests/tools
	 * not अवरोधing completely. Userspace tools stop क्रमागतerating one they
	 * get -EINVAL, hence this is the वापस value we need to hand back क्रम
	 * no clients tracked.
	 *
	 * Unक्रमtunately some clients (*cough* libva *cough*) use this in a fun
	 * attempt to figure out whether they're authenticated or not. Since
	 * that's the only thing they care about, give it to the directly
	 * instead of walking one giant list.
	 */
	अगर (client->idx == 0) अणु
		client->auth = file_priv->authenticated;
		client->pid = task_pid_vnr(current);
		client->uid = overflowuid;
		client->magic = 0;
		client->iocs = 0;

		वापस 0;
	पूर्ण अन्यथा अणु
		वापस -EINVAL;
	पूर्ण
पूर्ण

/*
 * Get statistics inक्रमmation.
 *
 * \param inode device inode.
 * \param file_priv DRM file निजी.
 * \param cmd command.
 * \param arg user argument, poपूर्णांकing to a drm_stats काष्ठाure.
 *
 * \लeturn zero on success or a negative number on failure.
 */
अटल पूर्णांक drm_माला_लोtats(काष्ठा drm_device *dev, व्योम *data,
		 काष्ठा drm_file *file_priv)
अणु
	काष्ठा drm_stats *stats = data;

	/* Clear stats to prevent userspace from eating its stack garbage. */
	स_रखो(stats, 0, माप(*stats));

	वापस 0;
पूर्ण

/*
 * Get device/driver capabilities
 */
अटल पूर्णांक drm_अ_लोap(काष्ठा drm_device *dev, व्योम *data, काष्ठा drm_file *file_priv)
अणु
	काष्ठा drm_get_cap *req = data;
	काष्ठा drm_crtc *crtc;

	req->value = 0;

	/* Only some caps make sense with UMS/render-only drivers. */
	चयन (req->capability) अणु
	हाल DRM_CAP_TIMESTAMP_MONOTONIC:
		req->value = 1;
		वापस 0;
	हाल DRM_CAP_PRIME:
		req->value |= dev->driver->prime_fd_to_handle ? DRM_PRIME_CAP_IMPORT : 0;
		req->value |= dev->driver->prime_handle_to_fd ? DRM_PRIME_CAP_EXPORT : 0;
		वापस 0;
	हाल DRM_CAP_SYNCOBJ:
		req->value = drm_core_check_feature(dev, DRIVER_SYNCOBJ);
		वापस 0;
	हाल DRM_CAP_SYNCOBJ_TIMELINE:
		req->value = drm_core_check_feature(dev, DRIVER_SYNCOBJ_TIMELINE);
		वापस 0;
	पूर्ण

	/* Other caps only work with KMS drivers */
	अगर (!drm_core_check_feature(dev, DRIVER_MODESET))
		वापस -EOPNOTSUPP;

	चयन (req->capability) अणु
	हाल DRM_CAP_DUMB_BUFFER:
		अगर (dev->driver->dumb_create)
			req->value = 1;
		अवरोध;
	हाल DRM_CAP_VBLANK_HIGH_CRTC:
		req->value = 1;
		अवरोध;
	हाल DRM_CAP_DUMB_PREFERRED_DEPTH:
		req->value = dev->mode_config.preferred_depth;
		अवरोध;
	हाल DRM_CAP_DUMB_PREFER_SHADOW:
		req->value = dev->mode_config.prefer_shaकरोw;
		अवरोध;
	हाल DRM_CAP_ASYNC_PAGE_FLIP:
		req->value = dev->mode_config.async_page_flip;
		अवरोध;
	हाल DRM_CAP_PAGE_FLIP_TARGET:
		req->value = 1;
		drm_क्रम_each_crtc(crtc, dev) अणु
			अगर (!crtc->funcs->page_flip_target)
				req->value = 0;
		पूर्ण
		अवरोध;
	हाल DRM_CAP_CURSOR_WIDTH:
		अगर (dev->mode_config.cursor_width)
			req->value = dev->mode_config.cursor_width;
		अन्यथा
			req->value = 64;
		अवरोध;
	हाल DRM_CAP_CURSOR_HEIGHT:
		अगर (dev->mode_config.cursor_height)
			req->value = dev->mode_config.cursor_height;
		अन्यथा
			req->value = 64;
		अवरोध;
	हाल DRM_CAP_ADDFB2_MODIFIERS:
		req->value = dev->mode_config.allow_fb_modअगरiers;
		अवरोध;
	हाल DRM_CAP_CRTC_IN_VBLANK_EVENT:
		req->value = 1;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

/*
 * Set device/driver capabilities
 */
अटल पूर्णांक
drm_setclientcap(काष्ठा drm_device *dev, व्योम *data, काष्ठा drm_file *file_priv)
अणु
	काष्ठा drm_set_client_cap *req = data;

	/* No render-only settable capabilities क्रम now */

	/* Below caps that only works with KMS drivers */
	अगर (!drm_core_check_feature(dev, DRIVER_MODESET))
		वापस -EOPNOTSUPP;

	चयन (req->capability) अणु
	हाल DRM_CLIENT_CAP_STEREO_3D:
		अगर (req->value > 1)
			वापस -EINVAL;
		file_priv->stereo_allowed = req->value;
		अवरोध;
	हाल DRM_CLIENT_CAP_UNIVERSAL_PLANES:
		अगर (req->value > 1)
			वापस -EINVAL;
		file_priv->universal_planes = req->value;
		अवरोध;
	हाल DRM_CLIENT_CAP_ATOMIC:
		अगर (!drm_core_check_feature(dev, DRIVER_ATOMIC))
			वापस -EOPNOTSUPP;
		/* The modesetting DDX has a totally broken idea of atomic. */
		अगर (current->comm[0] == 'X' && req->value == 1) अणु
			pr_info("broken atomic modeset userspace detected, disabling atomic\n");
			वापस -EOPNOTSUPP;
		पूर्ण
		अगर (req->value > 2)
			वापस -EINVAL;
		file_priv->atomic = req->value;
		file_priv->universal_planes = req->value;
		/*
		 * No atomic user-space blows up on aspect ratio mode bits.
		 */
		file_priv->aspect_ratio_allowed = req->value;
		अवरोध;
	हाल DRM_CLIENT_CAP_ASPECT_RATIO:
		अगर (req->value > 1)
			वापस -EINVAL;
		file_priv->aspect_ratio_allowed = req->value;
		अवरोध;
	हाल DRM_CLIENT_CAP_WRITEBACK_CONNECTORS:
		अगर (!file_priv->atomic)
			वापस -EINVAL;
		अगर (req->value > 1)
			वापस -EINVAL;
		file_priv->ग_लिखोback_connectors = req->value;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Setversion ioctl.
 *
 * \param inode device inode.
 * \param file_priv DRM file निजी.
 * \param cmd command.
 * \param arg user argument, poपूर्णांकing to a drm_lock काष्ठाure.
 * \लeturn zero on success or negative number on failure.
 *
 * Sets the requested पूर्णांकerface version
 */
अटल पूर्णांक drm_setversion(काष्ठा drm_device *dev, व्योम *data, काष्ठा drm_file *file_priv)
अणु
	काष्ठा drm_set_version *sv = data;
	पूर्णांक अगर_version, retcode = 0;

	mutex_lock(&dev->master_mutex);
	अगर (sv->drm_di_major != -1) अणु
		अगर (sv->drm_di_major != DRM_IF_MAJOR ||
		    sv->drm_di_minor < 0 || sv->drm_di_minor > DRM_IF_MINOR) अणु
			retcode = -EINVAL;
			जाओ करोne;
		पूर्ण
		अगर_version = DRM_IF_VERSION(sv->drm_di_major,
					    sv->drm_di_minor);
		dev->अगर_version = max(अगर_version, dev->अगर_version);
		अगर (sv->drm_di_minor >= 1) अणु
			/*
			 * Version 1.1 includes tying of DRM to specअगरic device
			 * Version 1.4 has proper PCI करोमुख्य support
			 */
			retcode = drm_set_busid(dev, file_priv);
			अगर (retcode)
				जाओ करोne;
		पूर्ण
	पूर्ण

	अगर (sv->drm_dd_major != -1) अणु
		अगर (sv->drm_dd_major != dev->driver->major ||
		    sv->drm_dd_minor < 0 || sv->drm_dd_minor >
		    dev->driver->minor) अणु
			retcode = -EINVAL;
			जाओ करोne;
		पूर्ण
	पूर्ण

करोne:
	sv->drm_di_major = DRM_IF_MAJOR;
	sv->drm_di_minor = DRM_IF_MINOR;
	sv->drm_dd_major = dev->driver->major;
	sv->drm_dd_minor = dev->driver->minor;
	mutex_unlock(&dev->master_mutex);

	वापस retcode;
पूर्ण

/**
 * drm_noop - DRM no-op ioctl implemntation
 * @dev: DRM device क्रम the ioctl
 * @data: data poपूर्णांकer क्रम the ioctl
 * @file_priv: DRM file क्रम the ioctl call
 *
 * This no-op implementation क्रम drm ioctls is useful क्रम deprecated
 * functionality where we can't वापस a failure code because existing userspace
 * checks the result of the ioctl, but करोesn't care about the action.
 *
 * Always वापसs successfully with 0.
 */
पूर्णांक drm_noop(काष्ठा drm_device *dev, व्योम *data,
	     काष्ठा drm_file *file_priv)
अणु
	DRM_DEBUG("\n");
	वापस 0;
पूर्ण
EXPORT_SYMBOL(drm_noop);

/**
 * drm_invalid_op - DRM invalid ioctl implemntation
 * @dev: DRM device क्रम the ioctl
 * @data: data poपूर्णांकer क्रम the ioctl
 * @file_priv: DRM file क्रम the ioctl call
 *
 * This no-op implementation क्रम drm ioctls is useful क्रम deprecated
 * functionality where we really करोn't want to allow userspace to call the ioctl
 * any more. This is the हाल क्रम old ums पूर्णांकerfaces क्रम drivers that
 * transitioned to kms gradually and so kept the old legacy tables around. This
 * only applies to radeon and i915 kms drivers, other drivers shouldn't need to
 * use this function.
 *
 * Always fails with a वापस value of -EINVAL.
 */
पूर्णांक drm_invalid_op(काष्ठा drm_device *dev, व्योम *data,
		   काष्ठा drm_file *file_priv)
अणु
	वापस -EINVAL;
पूर्ण
EXPORT_SYMBOL(drm_invalid_op);

/*
 * Copy and IOCTL वापस string to user space
 */
अटल पूर्णांक drm_copy_field(अक्षर __user *buf, माप_प्रकार *buf_len, स्थिर अक्षर *value)
अणु
	पूर्णांक len;

	/* करोn't overflow userbuf */
	len = म_माप(value);
	अगर (len > *buf_len)
		len = *buf_len;

	/* let userspace know exact length of driver value (which could be
	 * larger than the userspace-supplied buffer) */
	*buf_len = म_माप(value);

	/* finally, try filling in the userbuf */
	अगर (len && buf)
		अगर (copy_to_user(buf, value, len))
			वापस -EFAULT;
	वापस 0;
पूर्ण

/*
 * Get version inक्रमmation
 *
 * \param inode device inode.
 * \param filp file poपूर्णांकer.
 * \param cmd command.
 * \param arg user argument, poपूर्णांकing to a drm_version काष्ठाure.
 * \लeturn zero on success or negative number on failure.
 *
 * Fills in the version inक्रमmation in \p arg.
 */
पूर्णांक drm_version(काष्ठा drm_device *dev, व्योम *data,
		       काष्ठा drm_file *file_priv)
अणु
	काष्ठा drm_version *version = data;
	पूर्णांक err;

	version->version_major = dev->driver->major;
	version->version_minor = dev->driver->minor;
	version->version_patchlevel = dev->driver->patchlevel;
	err = drm_copy_field(version->name, &version->name_len,
			dev->driver->name);
	अगर (!err)
		err = drm_copy_field(version->date, &version->date_len,
				dev->driver->date);
	अगर (!err)
		err = drm_copy_field(version->desc, &version->desc_len,
				dev->driver->desc);

	वापस err;
पूर्ण

/**
 * drm_ioctl_permit - Check ioctl permissions against caller
 *
 * @flags: ioctl permission flags.
 * @file_priv: Poपूर्णांकer to काष्ठा drm_file identअगरying the caller.
 *
 * Checks whether the caller is allowed to run an ioctl with the
 * indicated permissions.
 *
 * Returns:
 * Zero अगर allowed, -EACCES otherwise.
 */
पूर्णांक drm_ioctl_permit(u32 flags, काष्ठा drm_file *file_priv)
अणु
	/* ROOT_ONLY is only क्रम CAP_SYS_ADMIN */
	अगर (unlikely((flags & DRM_ROOT_ONLY) && !capable(CAP_SYS_ADMIN)))
		वापस -EACCES;

	/* AUTH is only क्रम authenticated or render client */
	अगर (unlikely((flags & DRM_AUTH) && !drm_is_render_client(file_priv) &&
		     !file_priv->authenticated))
		वापस -EACCES;

	/* MASTER is only क्रम master or control clients */
	अगर (unlikely((flags & DRM_MASTER) &&
		     !drm_is_current_master(file_priv)))
		वापस -EACCES;

	/* Render clients must be explicitly allowed */
	अगर (unlikely(!(flags & DRM_RENDER_ALLOW) &&
		     drm_is_render_client(file_priv)))
		वापस -EACCES;

	वापस 0;
पूर्ण
EXPORT_SYMBOL(drm_ioctl_permit);

#घोषणा DRM_IOCTL_DEF(ioctl, _func, _flags)	\
	[DRM_IOCTL_NR(ioctl)] = अणु		\
		.cmd = ioctl,			\
		.func = _func,			\
		.flags = _flags,		\
		.name = #ioctl			\
	पूर्ण

#अगर IS_ENABLED(CONFIG_DRM_LEGACY)
#घोषणा DRM_LEGACY_IOCTL_DEF(ioctl, _func, _flags)  DRM_IOCTL_DEF(ioctl, _func, _flags)
#अन्यथा
#घोषणा DRM_LEGACY_IOCTL_DEF(ioctl, _func, _flags) DRM_IOCTL_DEF(ioctl, drm_invalid_op, _flags)
#पूर्ण_अगर

/* Ioctl table */
अटल स्थिर काष्ठा drm_ioctl_desc drm_ioctls[] = अणु
	DRM_IOCTL_DEF(DRM_IOCTL_VERSION, drm_version, DRM_RENDER_ALLOW),
	DRM_IOCTL_DEF(DRM_IOCTL_GET_UNIQUE, drm_getunique, 0),
	DRM_IOCTL_DEF(DRM_IOCTL_GET_MAGIC, drm_geपंचांगagic, 0),
	DRM_IOCTL_DEF(DRM_IOCTL_IRQ_BUSID, drm_legacy_irq_by_busid, DRM_MASTER|DRM_ROOT_ONLY),

	DRM_LEGACY_IOCTL_DEF(DRM_IOCTL_GET_MAP, drm_legacy_geपंचांगap_ioctl, 0),

	DRM_IOCTL_DEF(DRM_IOCTL_GET_CLIENT, drm_अ_लोlient, 0),
	DRM_IOCTL_DEF(DRM_IOCTL_GET_STATS, drm_माला_लोtats, 0),
	DRM_IOCTL_DEF(DRM_IOCTL_GET_CAP, drm_अ_लोap, DRM_RENDER_ALLOW),
	DRM_IOCTL_DEF(DRM_IOCTL_SET_CLIENT_CAP, drm_setclientcap, 0),
	DRM_IOCTL_DEF(DRM_IOCTL_SET_VERSION, drm_setversion, DRM_MASTER),

	DRM_IOCTL_DEF(DRM_IOCTL_SET_UNIQUE, drm_invalid_op, DRM_AUTH|DRM_MASTER|DRM_ROOT_ONLY),
	DRM_IOCTL_DEF(DRM_IOCTL_BLOCK, drm_noop, DRM_AUTH|DRM_MASTER|DRM_ROOT_ONLY),
	DRM_IOCTL_DEF(DRM_IOCTL_UNBLOCK, drm_noop, DRM_AUTH|DRM_MASTER|DRM_ROOT_ONLY),
	DRM_IOCTL_DEF(DRM_IOCTL_AUTH_MAGIC, drm_authmagic, DRM_MASTER),

	DRM_LEGACY_IOCTL_DEF(DRM_IOCTL_ADD_MAP, drm_legacy_addmap_ioctl, DRM_AUTH|DRM_MASTER|DRM_ROOT_ONLY),
	DRM_LEGACY_IOCTL_DEF(DRM_IOCTL_RM_MAP, drm_legacy_rmmap_ioctl, DRM_AUTH),

	DRM_LEGACY_IOCTL_DEF(DRM_IOCTL_SET_SAREA_CTX, drm_legacy_setsareactx, DRM_AUTH|DRM_MASTER|DRM_ROOT_ONLY),
	DRM_LEGACY_IOCTL_DEF(DRM_IOCTL_GET_SAREA_CTX, drm_legacy_माला_लोareactx, DRM_AUTH),

	DRM_IOCTL_DEF(DRM_IOCTL_SET_MASTER, drm_seपंचांगaster_ioctl, 0),
	DRM_IOCTL_DEF(DRM_IOCTL_DROP_MASTER, drm_dropmaster_ioctl, 0),

	DRM_LEGACY_IOCTL_DEF(DRM_IOCTL_ADD_CTX, drm_legacy_addctx, DRM_AUTH|DRM_ROOT_ONLY),
	DRM_LEGACY_IOCTL_DEF(DRM_IOCTL_RM_CTX, drm_legacy_rmctx, DRM_AUTH|DRM_MASTER|DRM_ROOT_ONLY),
	DRM_LEGACY_IOCTL_DEF(DRM_IOCTL_MOD_CTX, drm_noop, DRM_AUTH|DRM_MASTER|DRM_ROOT_ONLY),
	DRM_LEGACY_IOCTL_DEF(DRM_IOCTL_GET_CTX, drm_legacy_अ_लोtx, DRM_AUTH),
	DRM_LEGACY_IOCTL_DEF(DRM_IOCTL_SWITCH_CTX, drm_legacy_चयनctx, DRM_AUTH|DRM_MASTER|DRM_ROOT_ONLY),
	DRM_LEGACY_IOCTL_DEF(DRM_IOCTL_NEW_CTX, drm_legacy_newctx, DRM_AUTH|DRM_MASTER|DRM_ROOT_ONLY),
	DRM_LEGACY_IOCTL_DEF(DRM_IOCTL_RES_CTX, drm_legacy_resctx, DRM_AUTH),

	DRM_IOCTL_DEF(DRM_IOCTL_ADD_DRAW, drm_noop, DRM_AUTH|DRM_MASTER|DRM_ROOT_ONLY),
	DRM_IOCTL_DEF(DRM_IOCTL_RM_DRAW, drm_noop, DRM_AUTH|DRM_MASTER|DRM_ROOT_ONLY),

	DRM_LEGACY_IOCTL_DEF(DRM_IOCTL_LOCK, drm_legacy_lock, DRM_AUTH),
	DRM_LEGACY_IOCTL_DEF(DRM_IOCTL_UNLOCK, drm_legacy_unlock, DRM_AUTH),

	DRM_IOCTL_DEF(DRM_IOCTL_FINISH, drm_noop, DRM_AUTH),

	DRM_LEGACY_IOCTL_DEF(DRM_IOCTL_ADD_BUFS, drm_legacy_addbufs, DRM_AUTH|DRM_MASTER|DRM_ROOT_ONLY),
	DRM_LEGACY_IOCTL_DEF(DRM_IOCTL_MARK_BUFS, drm_legacy_markbufs, DRM_AUTH|DRM_MASTER|DRM_ROOT_ONLY),
	DRM_LEGACY_IOCTL_DEF(DRM_IOCTL_INFO_BUFS, drm_legacy_infobufs, DRM_AUTH),
	DRM_LEGACY_IOCTL_DEF(DRM_IOCTL_MAP_BUFS, drm_legacy_mapbufs, DRM_AUTH),
	DRM_LEGACY_IOCTL_DEF(DRM_IOCTL_FREE_BUFS, drm_legacy_मुक्तbufs, DRM_AUTH),
	DRM_LEGACY_IOCTL_DEF(DRM_IOCTL_DMA, drm_legacy_dma_ioctl, DRM_AUTH),
	DRM_LEGACY_IOCTL_DEF(DRM_IOCTL_CONTROL, drm_legacy_irq_control, DRM_AUTH|DRM_MASTER|DRM_ROOT_ONLY),

#अगर IS_ENABLED(CONFIG_AGP)
	DRM_IOCTL_DEF(DRM_IOCTL_AGP_ACQUIRE, drm_agp_acquire_ioctl, DRM_AUTH|DRM_MASTER|DRM_ROOT_ONLY),
	DRM_IOCTL_DEF(DRM_IOCTL_AGP_RELEASE, drm_agp_release_ioctl, DRM_AUTH|DRM_MASTER|DRM_ROOT_ONLY),
	DRM_IOCTL_DEF(DRM_IOCTL_AGP_ENABLE, drm_agp_enable_ioctl, DRM_AUTH|DRM_MASTER|DRM_ROOT_ONLY),
	DRM_IOCTL_DEF(DRM_IOCTL_AGP_INFO, drm_agp_info_ioctl, DRM_AUTH),
	DRM_IOCTL_DEF(DRM_IOCTL_AGP_ALLOC, drm_agp_alloc_ioctl, DRM_AUTH|DRM_MASTER|DRM_ROOT_ONLY),
	DRM_IOCTL_DEF(DRM_IOCTL_AGP_FREE, drm_agp_मुक्त_ioctl, DRM_AUTH|DRM_MASTER|DRM_ROOT_ONLY),
	DRM_IOCTL_DEF(DRM_IOCTL_AGP_BIND, drm_agp_bind_ioctl, DRM_AUTH|DRM_MASTER|DRM_ROOT_ONLY),
	DRM_IOCTL_DEF(DRM_IOCTL_AGP_UNBIND, drm_agp_unbind_ioctl, DRM_AUTH|DRM_MASTER|DRM_ROOT_ONLY),
#पूर्ण_अगर

	DRM_LEGACY_IOCTL_DEF(DRM_IOCTL_SG_ALLOC, drm_legacy_sg_alloc, DRM_AUTH|DRM_MASTER|DRM_ROOT_ONLY),
	DRM_LEGACY_IOCTL_DEF(DRM_IOCTL_SG_FREE, drm_legacy_sg_मुक्त, DRM_AUTH|DRM_MASTER|DRM_ROOT_ONLY),

	DRM_IOCTL_DEF(DRM_IOCTL_WAIT_VBLANK, drm_रुको_vblank_ioctl, DRM_UNLOCKED),

	DRM_IOCTL_DEF(DRM_IOCTL_MODESET_CTL, drm_legacy_modeset_ctl_ioctl, 0),

	DRM_IOCTL_DEF(DRM_IOCTL_UPDATE_DRAW, drm_noop, DRM_AUTH|DRM_MASTER|DRM_ROOT_ONLY),

	DRM_IOCTL_DEF(DRM_IOCTL_GEM_CLOSE, drm_gem_बंद_ioctl, DRM_RENDER_ALLOW),
	DRM_IOCTL_DEF(DRM_IOCTL_GEM_FLINK, drm_gem_flink_ioctl, DRM_AUTH),
	DRM_IOCTL_DEF(DRM_IOCTL_GEM_OPEN, drm_gem_खोलो_ioctl, DRM_AUTH),

	DRM_IOCTL_DEF(DRM_IOCTL_MODE_GETRESOURCES, drm_mode_getresources, 0),

	DRM_IOCTL_DEF(DRM_IOCTL_PRIME_HANDLE_TO_FD, drm_prime_handle_to_fd_ioctl, DRM_RENDER_ALLOW),
	DRM_IOCTL_DEF(DRM_IOCTL_PRIME_FD_TO_HANDLE, drm_prime_fd_to_handle_ioctl, DRM_RENDER_ALLOW),

	DRM_IOCTL_DEF(DRM_IOCTL_MODE_GETPLANERESOURCES, drm_mode_getplane_res, 0),
	DRM_IOCTL_DEF(DRM_IOCTL_MODE_GETCRTC, drm_mode_अ_लोrtc, 0),
	DRM_IOCTL_DEF(DRM_IOCTL_MODE_SETCRTC, drm_mode_setcrtc, DRM_MASTER),
	DRM_IOCTL_DEF(DRM_IOCTL_MODE_GETPLANE, drm_mode_getplane, 0),
	DRM_IOCTL_DEF(DRM_IOCTL_MODE_SETPLANE, drm_mode_setplane, DRM_MASTER),
	DRM_IOCTL_DEF(DRM_IOCTL_MODE_CURSOR, drm_mode_cursor_ioctl, DRM_MASTER),
	DRM_IOCTL_DEF(DRM_IOCTL_MODE_GETGAMMA, drm_mode_gamma_get_ioctl, 0),
	DRM_IOCTL_DEF(DRM_IOCTL_MODE_SETGAMMA, drm_mode_gamma_set_ioctl, DRM_MASTER),
	DRM_IOCTL_DEF(DRM_IOCTL_MODE_GETENCODER, drm_mode_getencoder, 0),
	DRM_IOCTL_DEF(DRM_IOCTL_MODE_GETCONNECTOR, drm_mode_अ_लोonnector, 0),
	DRM_IOCTL_DEF(DRM_IOCTL_MODE_ATTACHMODE, drm_noop, DRM_MASTER),
	DRM_IOCTL_DEF(DRM_IOCTL_MODE_DETACHMODE, drm_noop, DRM_MASTER),
	DRM_IOCTL_DEF(DRM_IOCTL_MODE_GETPROPERTY, drm_mode_getproperty_ioctl, 0),
	DRM_IOCTL_DEF(DRM_IOCTL_MODE_SETPROPERTY, drm_connector_property_set_ioctl, DRM_MASTER),
	DRM_IOCTL_DEF(DRM_IOCTL_MODE_GETPROPBLOB, drm_mode_getblob_ioctl, 0),
	DRM_IOCTL_DEF(DRM_IOCTL_MODE_GETFB, drm_mode_getfb, 0),
	DRM_IOCTL_DEF(DRM_IOCTL_MODE_GETFB2, drm_mode_getfb2_ioctl, 0),
	DRM_IOCTL_DEF(DRM_IOCTL_MODE_ADDFB, drm_mode_addfb_ioctl, 0),
	DRM_IOCTL_DEF(DRM_IOCTL_MODE_ADDFB2, drm_mode_addfb2_ioctl, 0),
	DRM_IOCTL_DEF(DRM_IOCTL_MODE_RMFB, drm_mode_rmfb_ioctl, 0),
	DRM_IOCTL_DEF(DRM_IOCTL_MODE_PAGE_FLIP, drm_mode_page_flip_ioctl, DRM_MASTER),
	DRM_IOCTL_DEF(DRM_IOCTL_MODE_सूचीTYFB, drm_mode_dirtyfb_ioctl, DRM_MASTER),
	DRM_IOCTL_DEF(DRM_IOCTL_MODE_CREATE_DUMB, drm_mode_create_dumb_ioctl, 0),
	DRM_IOCTL_DEF(DRM_IOCTL_MODE_MAP_DUMB, drm_mode_mmap_dumb_ioctl, 0),
	DRM_IOCTL_DEF(DRM_IOCTL_MODE_DESTROY_DUMB, drm_mode_destroy_dumb_ioctl, 0),
	DRM_IOCTL_DEF(DRM_IOCTL_MODE_OBJ_GETPROPERTIES, drm_mode_obj_get_properties_ioctl, 0),
	DRM_IOCTL_DEF(DRM_IOCTL_MODE_OBJ_SETPROPERTY, drm_mode_obj_set_property_ioctl, DRM_MASTER),
	DRM_IOCTL_DEF(DRM_IOCTL_MODE_CURSOR2, drm_mode_cursor2_ioctl, DRM_MASTER),
	DRM_IOCTL_DEF(DRM_IOCTL_MODE_ATOMIC, drm_mode_atomic_ioctl, DRM_MASTER),
	DRM_IOCTL_DEF(DRM_IOCTL_MODE_CREATEPROPBLOB, drm_mode_createblob_ioctl, 0),
	DRM_IOCTL_DEF(DRM_IOCTL_MODE_DESTROYPROPBLOB, drm_mode_destroyblob_ioctl, 0),

	DRM_IOCTL_DEF(DRM_IOCTL_SYNCOBJ_CREATE, drm_syncobj_create_ioctl,
		      DRM_RENDER_ALLOW),
	DRM_IOCTL_DEF(DRM_IOCTL_SYNCOBJ_DESTROY, drm_syncobj_destroy_ioctl,
		      DRM_RENDER_ALLOW),
	DRM_IOCTL_DEF(DRM_IOCTL_SYNCOBJ_HANDLE_TO_FD, drm_syncobj_handle_to_fd_ioctl,
		      DRM_RENDER_ALLOW),
	DRM_IOCTL_DEF(DRM_IOCTL_SYNCOBJ_FD_TO_HANDLE, drm_syncobj_fd_to_handle_ioctl,
		      DRM_RENDER_ALLOW),
	DRM_IOCTL_DEF(DRM_IOCTL_SYNCOBJ_TRANSFER, drm_syncobj_transfer_ioctl,
		      DRM_RENDER_ALLOW),
	DRM_IOCTL_DEF(DRM_IOCTL_SYNCOBJ_WAIT, drm_syncobj_रुको_ioctl,
		      DRM_RENDER_ALLOW),
	DRM_IOCTL_DEF(DRM_IOCTL_SYNCOBJ_TIMELINE_WAIT, drm_syncobj_समयline_रुको_ioctl,
		      DRM_RENDER_ALLOW),
	DRM_IOCTL_DEF(DRM_IOCTL_SYNCOBJ_RESET, drm_syncobj_reset_ioctl,
		      DRM_RENDER_ALLOW),
	DRM_IOCTL_DEF(DRM_IOCTL_SYNCOBJ_SIGNAL, drm_syncobj_संकेत_ioctl,
		      DRM_RENDER_ALLOW),
	DRM_IOCTL_DEF(DRM_IOCTL_SYNCOBJ_TIMELINE_SIGNAL, drm_syncobj_समयline_संकेत_ioctl,
		      DRM_RENDER_ALLOW),
	DRM_IOCTL_DEF(DRM_IOCTL_SYNCOBJ_QUERY, drm_syncobj_query_ioctl,
		      DRM_RENDER_ALLOW),
	DRM_IOCTL_DEF(DRM_IOCTL_CRTC_GET_SEQUENCE, drm_crtc_get_sequence_ioctl, 0),
	DRM_IOCTL_DEF(DRM_IOCTL_CRTC_QUEUE_SEQUENCE, drm_crtc_queue_sequence_ioctl, 0),
	DRM_IOCTL_DEF(DRM_IOCTL_MODE_CREATE_LEASE, drm_mode_create_lease_ioctl, DRM_MASTER),
	DRM_IOCTL_DEF(DRM_IOCTL_MODE_LIST_LESSEES, drm_mode_list_lessees_ioctl, DRM_MASTER),
	DRM_IOCTL_DEF(DRM_IOCTL_MODE_GET_LEASE, drm_mode_get_lease_ioctl, DRM_MASTER),
	DRM_IOCTL_DEF(DRM_IOCTL_MODE_REVOKE_LEASE, drm_mode_revoke_lease_ioctl, DRM_MASTER),
पूर्ण;

#घोषणा DRM_CORE_IOCTL_COUNT	ARRAY_SIZE( drm_ioctls )

/**
 * DOC: driver specअगरic ioctls
 *
 * First things first, driver निजी IOCTLs should only be needed क्रम drivers
 * supporting rendering. Kernel modesetting is all standardized, and extended
 * through properties. There are a few exceptions in some existing drivers,
 * which define IOCTL क्रम use by the display DRM master, but they all predate
 * properties.
 *
 * Now अगर you करो have a render driver you always have to support it through
 * driver निजी properties. There's a few steps needed to wire all the things
 * up.
 *
 * First you need to define the काष्ठाure क्रम your IOCTL in your driver निजी
 * UAPI header in ``include/uapi/drm/my_driver_drm.h``::
 *
 *     काष्ठा my_driver_operation अणु
 *             u32 some_thing;
 *             u32 another_thing;
 *     पूर्ण;
 *
 * Please make sure that you follow all the best practices from
 * ``Documentation/process/botching-up-ioctls.rst``. Note that drm_ioctl()
 * स्वतःmatically zero-extends काष्ठाures, hence make sure you can add more stuff
 * at the end, i.e. करोn't put a variable sized array there.
 *
 * Then you need to define your IOCTL number, using one of DRM_IO(), DRM_IOR(),
 * DRM_IOW() or DRM_IOWR(). It must start with the DRM_IOCTL\_ prefix::
 *
 *     ##घोषणा DRM_IOCTL_MY_DRIVER_OPERATION \
 *         DRM_IOW(DRM_COMMAND_BASE, काष्ठा my_driver_operation)
 *
 * DRM driver निजी IOCTL must be in the range from DRM_COMMAND_BASE to
 * DRM_COMMAND_END. Finally you need an array of &काष्ठा drm_ioctl_desc to wire
 * up the handlers and set the access rights::
 *
 *     अटल स्थिर काष्ठा drm_ioctl_desc my_driver_ioctls[] = अणु
 *         DRM_IOCTL_DEF_DRV(MY_DRIVER_OPERATION, my_driver_operation,
 *                 DRM_AUTH|DRM_RENDER_ALLOW),
 *     पूर्ण;
 *
 * And then assign this to the &drm_driver.ioctls field in your driver
 * काष्ठाure.
 *
 * See the separate chapter on :ref:`file operations<drm_driver_fops>` क्रम how
 * the driver-specअगरic IOCTLs are wired up.
 */

दीर्घ drm_ioctl_kernel(काष्ठा file *file, drm_ioctl_t *func, व्योम *kdata,
		      u32 flags)
अणु
	काष्ठा drm_file *file_priv = file->निजी_data;
	काष्ठा drm_device *dev = file_priv->minor->dev;
	पूर्णांक retcode;

	अगर (drm_dev_is_unplugged(dev))
		वापस -ENODEV;

	retcode = drm_ioctl_permit(flags, file_priv);
	अगर (unlikely(retcode))
		वापस retcode;

	/* Enक्रमce sane locking क्रम modern driver ioctls. */
	अगर (likely(!drm_core_check_feature(dev, DRIVER_LEGACY)) ||
	    (flags & DRM_UNLOCKED))
		retcode = func(dev, kdata, file_priv);
	अन्यथा अणु
		mutex_lock(&drm_global_mutex);
		retcode = func(dev, kdata, file_priv);
		mutex_unlock(&drm_global_mutex);
	पूर्ण
	वापस retcode;
पूर्ण
EXPORT_SYMBOL(drm_ioctl_kernel);

/**
 * drm_ioctl - ioctl callback implementation क्रम DRM drivers
 * @filp: file this ioctl is called on
 * @cmd: ioctl cmd number
 * @arg: user argument
 *
 * Looks up the ioctl function in the DRM core and the driver dispatch table,
 * stored in &drm_driver.ioctls. It checks क्रम necessary permission by calling
 * drm_ioctl_permit(), and dispatches to the respective function.
 *
 * Returns:
 * Zero on success, negative error code on failure.
 */
दीर्घ drm_ioctl(काष्ठा file *filp,
	      अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	काष्ठा drm_file *file_priv = filp->निजी_data;
	काष्ठा drm_device *dev;
	स्थिर काष्ठा drm_ioctl_desc *ioctl = शून्य;
	drm_ioctl_t *func;
	अचिन्हित पूर्णांक nr = DRM_IOCTL_NR(cmd);
	पूर्णांक retcode = -EINVAL;
	अक्षर stack_kdata[128];
	अक्षर *kdata = शून्य;
	अचिन्हित पूर्णांक in_size, out_size, drv_size, ksize;
	bool is_driver_ioctl;

	dev = file_priv->minor->dev;

	अगर (drm_dev_is_unplugged(dev))
		वापस -ENODEV;

	is_driver_ioctl = nr >= DRM_COMMAND_BASE && nr < DRM_COMMAND_END;

	अगर (is_driver_ioctl) अणु
		/* driver ioctl */
		अचिन्हित पूर्णांक index = nr - DRM_COMMAND_BASE;

		अगर (index >= dev->driver->num_ioctls)
			जाओ err_i1;
		index = array_index_nospec(index, dev->driver->num_ioctls);
		ioctl = &dev->driver->ioctls[index];
	पूर्ण अन्यथा अणु
		/* core ioctl */
		अगर (nr >= DRM_CORE_IOCTL_COUNT)
			जाओ err_i1;
		nr = array_index_nospec(nr, DRM_CORE_IOCTL_COUNT);
		ioctl = &drm_ioctls[nr];
	पूर्ण

	drv_size = _IOC_SIZE(ioctl->cmd);
	out_size = in_size = _IOC_SIZE(cmd);
	अगर ((cmd & ioctl->cmd & IOC_IN) == 0)
		in_size = 0;
	अगर ((cmd & ioctl->cmd & IOC_OUT) == 0)
		out_size = 0;
	ksize = max(max(in_size, out_size), drv_size);

	DRM_DEBUG("comm=\"%s\" pid=%d, dev=0x%lx, auth=%d, %s\n",
		  current->comm, task_pid_nr(current),
		  (दीर्घ)old_encode_dev(file_priv->minor->kdev->devt),
		  file_priv->authenticated, ioctl->name);

	/* Do not trust userspace, use our own definition */
	func = ioctl->func;

	अगर (unlikely(!func)) अणु
		DRM_DEBUG("no function\n");
		retcode = -EINVAL;
		जाओ err_i1;
	पूर्ण

	अगर (ksize <= माप(stack_kdata)) अणु
		kdata = stack_kdata;
	पूर्ण अन्यथा अणु
		kdata = kदो_स्मृति(ksize, GFP_KERNEL);
		अगर (!kdata) अणु
			retcode = -ENOMEM;
			जाओ err_i1;
		पूर्ण
	पूर्ण

	अगर (copy_from_user(kdata, (व्योम __user *)arg, in_size) != 0) अणु
		retcode = -EFAULT;
		जाओ err_i1;
	पूर्ण

	अगर (ksize > in_size)
		स_रखो(kdata + in_size, 0, ksize - in_size);

	retcode = drm_ioctl_kernel(filp, func, kdata, ioctl->flags);
	अगर (copy_to_user((व्योम __user *)arg, kdata, out_size) != 0)
		retcode = -EFAULT;

      err_i1:
	अगर (!ioctl)
		DRM_DEBUG("invalid ioctl: comm=\"%s\", pid=%d, dev=0x%lx, auth=%d, cmd=0x%02x, nr=0x%02x\n",
			  current->comm, task_pid_nr(current),
			  (दीर्घ)old_encode_dev(file_priv->minor->kdev->devt),
			  file_priv->authenticated, cmd, nr);

	अगर (kdata != stack_kdata)
		kमुक्त(kdata);
	अगर (retcode)
		DRM_DEBUG("comm=\"%s\", pid=%d, ret=%d\n", current->comm,
			  task_pid_nr(current), retcode);
	वापस retcode;
पूर्ण
EXPORT_SYMBOL(drm_ioctl);

/**
 * drm_ioctl_flags - Check क्रम core ioctl and वापस ioctl permission flags
 * @nr: ioctl number
 * @flags: where to वापस the ioctl permission flags
 *
 * This ioctl is only used by the vmwgfx driver to augment the access checks
 * करोne by the drm core and insofar a pretty decent layering violation. This
 * shouldn't be used by any drivers.
 *
 * Returns:
 * True अगर the @nr corresponds to a DRM core ioctl number, false otherwise.
 */
bool drm_ioctl_flags(अचिन्हित पूर्णांक nr, अचिन्हित पूर्णांक *flags)
अणु
	अगर (nr >= DRM_COMMAND_BASE && nr < DRM_COMMAND_END)
		वापस false;

	अगर (nr >= DRM_CORE_IOCTL_COUNT)
		वापस false;
	nr = array_index_nospec(nr, DRM_CORE_IOCTL_COUNT);

	*flags = drm_ioctls[nr].flags;
	वापस true;
पूर्ण
EXPORT_SYMBOL(drm_ioctl_flags);
