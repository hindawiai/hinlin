<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright तऊ 2017 Keith Packard <keithp@keithp.com>
 */
#समावेश <linux/file.h>
#समावेश <linux/uaccess.h>

#समावेश <drm/drm_auth.h>
#समावेश <drm/drm_crtc_helper.h>
#समावेश <drm/drm_drv.h>
#समावेश <drm/drm_file.h>
#समावेश <drm/drm_lease.h>
#समावेश <drm/drm_prपूर्णांक.h>

#समावेश "drm_crtc_internal.h"
#समावेश "drm_internal.h"
#समावेश "drm_legacy.h"

#घोषणा drm_क्रम_each_lessee(lessee, lessor) \
	list_क्रम_each_entry((lessee), &(lessor)->lessees, lessee_list)

अटल uपूर्णांक64_t drm_lease_idr_object;

/**
 * drm_lease_owner - वापस ancestor owner drm_master
 * @master: drm_master somewhere within tree of lessees and lessors
 *
 * RETURN:
 *
 * drm_master at the top of the tree (i.e, with lessor शून्य
 */
काष्ठा drm_master *drm_lease_owner(काष्ठा drm_master *master)
अणु
	जबतक (master->lessor != शून्य)
		master = master->lessor;
	वापस master;
पूर्ण

/**
 * _drm_find_lessee - find lessee by id (idr_mutex held)
 * @master: drm_master of lessor
 * @lessee_id: id
 *
 * RETURN:
 *
 * drm_master of the lessee अगर valid, शून्य otherwise
 */

अटल काष्ठा drm_master*
_drm_find_lessee(काष्ठा drm_master *master, पूर्णांक lessee_id)
अणु
	lockdep_निश्चित_held(&master->dev->mode_config.idr_mutex);
	वापस idr_find(&drm_lease_owner(master)->lessee_idr, lessee_id);
पूर्ण

/**
 * _drm_lease_held_master - check to see अगर an object is leased (or owned) by master (idr_mutex held)
 * @master: the master to check the lease status of
 * @id: the id to check
 *
 * Checks अगर the specअगरied master holds a lease on the object. Return
 * value:
 *
 *	true		'master' holds a lease on (or owns) the object
 *	false		'master' करोes not hold a lease.
 */
अटल पूर्णांक _drm_lease_held_master(काष्ठा drm_master *master, पूर्णांक id)
अणु
	lockdep_निश्चित_held(&master->dev->mode_config.idr_mutex);
	अगर (master->lessor)
		वापस idr_find(&master->leases, id) != शून्य;
	वापस true;
पूर्ण

/**
 * _drm_has_leased - check to see अगर an object has been leased (idr_mutex held)
 * @master: the master to check the lease status of
 * @id: the id to check
 *
 * Checks अगर any lessee of 'master' holds a lease on 'id'. Return
 * value:
 *
 *	true		Some lessee holds a lease on the object.
 *	false		No lessee has a lease on the object.
 */
अटल bool _drm_has_leased(काष्ठा drm_master *master, पूर्णांक id)
अणु
	काष्ठा drm_master *lessee;

	lockdep_निश्चित_held(&master->dev->mode_config.idr_mutex);
	drm_क्रम_each_lessee(lessee, master)
		अगर (_drm_lease_held_master(lessee, id))
			वापस true;
	वापस false;
पूर्ण

/**
 * _drm_lease_held - check drm_mode_object lease status (idr_mutex held)
 * @file_priv: the master drm_file
 * @id: the object id
 *
 * Checks अगर the specअगरied master holds a lease on the object. Return
 * value:
 *
 *	true		'master' holds a lease on (or owns) the object
 *	false		'master' करोes not hold a lease.
 */
bool _drm_lease_held(काष्ठा drm_file *file_priv, पूर्णांक id)
अणु
	अगर (!file_priv || !file_priv->master)
		वापस true;

	वापस _drm_lease_held_master(file_priv->master, id);
पूर्ण

/**
 * drm_lease_held - check drm_mode_object lease status (idr_mutex not held)
 * @file_priv: the master drm_file
 * @id: the object id
 *
 * Checks अगर the specअगरied master holds a lease on the object. Return
 * value:
 *
 *	true		'master' holds a lease on (or owns) the object
 *	false		'master' करोes not hold a lease.
 */
bool drm_lease_held(काष्ठा drm_file *file_priv, पूर्णांक id)
अणु
	काष्ठा drm_master *master;
	bool ret;

	अगर (!file_priv || !file_priv->master || !file_priv->master->lessor)
		वापस true;

	master = file_priv->master;
	mutex_lock(&master->dev->mode_config.idr_mutex);
	ret = _drm_lease_held_master(master, id);
	mutex_unlock(&master->dev->mode_config.idr_mutex);
	वापस ret;
पूर्ण

/**
 * drm_lease_filter_crtcs - restricted crtc set to leased values (idr_mutex not held)
 * @file_priv: requestor file
 * @crtcs_in: biपंचांगask of crtcs to check
 *
 * Reस्थिरructs a crtc mask based on the crtcs which are visible
 * through the specअगरied file.
 */
uपूर्णांक32_t drm_lease_filter_crtcs(काष्ठा drm_file *file_priv, uपूर्णांक32_t crtcs_in)
अणु
	काष्ठा drm_master *master;
	काष्ठा drm_device *dev;
	काष्ठा drm_crtc *crtc;
	पूर्णांक count_in, count_out;
	uपूर्णांक32_t crtcs_out = 0;

	अगर (!file_priv || !file_priv->master || !file_priv->master->lessor)
		वापस crtcs_in;

	master = file_priv->master;
	dev = master->dev;

	count_in = count_out = 0;
	mutex_lock(&master->dev->mode_config.idr_mutex);
	list_क्रम_each_entry(crtc, &dev->mode_config.crtc_list, head) अणु
		अगर (_drm_lease_held_master(master, crtc->base.id)) अणु
			uपूर्णांक32_t mask_in = 1ul << count_in;

			अगर ((crtcs_in & mask_in) != 0) अणु
				uपूर्णांक32_t mask_out = 1ul << count_out;

				crtcs_out |= mask_out;
			पूर्ण
			count_out++;
		पूर्ण
		count_in++;
	पूर्ण
	mutex_unlock(&master->dev->mode_config.idr_mutex);
	वापस crtcs_out;
पूर्ण

/*
 * drm_lease_create - create a new drm_master with leased objects (idr_mutex not held)
 * @lessor: lease holder (or owner) of objects
 * @leases: objects to lease to the new drm_master
 *
 * Uses drm_master_create to allocate a new drm_master, then checks to
 * make sure all of the desired objects can be leased, atomically
 * leasing them to the new drmmaster.
 *
 * 	ERR_PTR(-EACCES)	some other master holds the title to any object
 * 	ERR_PTR(-ENOENT)	some object is not a valid DRM object क्रम this device
 * 	ERR_PTR(-EBUSY)		some other lessee holds title to this object
 *	ERR_PTR(-EEXIST)	same object specअगरied more than once in the provided list
 *	ERR_PTR(-ENOMEM)	allocation failed
 */
अटल काष्ठा drm_master *drm_lease_create(काष्ठा drm_master *lessor, काष्ठा idr *leases)
अणु
	काष्ठा drm_device *dev = lessor->dev;
	पूर्णांक error;
	काष्ठा drm_master *lessee;
	पूर्णांक object;
	पूर्णांक id;
	व्योम *entry;

	DRM_DEBUG_LEASE("lessor %d\n", lessor->lessee_id);

	lessee = drm_master_create(lessor->dev);
	अगर (!lessee) अणु
		DRM_DEBUG_LEASE("drm_master_create failed\n");
		वापस ERR_PTR(-ENOMEM);
	पूर्ण

	mutex_lock(&dev->mode_config.idr_mutex);

	idr_क्रम_each_entry(leases, entry, object) अणु
		error = 0;
		अगर (!idr_find(&dev->mode_config.object_idr, object))
			error = -ENOENT;
		अन्यथा अगर (_drm_has_leased(lessor, object))
			error = -EBUSY;

		अगर (error != 0) अणु
			DRM_DEBUG_LEASE("object %d failed %d\n", object, error);
			जाओ out_lessee;
		पूर्ण
	पूर्ण

	/* Insert the new lessee पूर्णांकo the tree */
	id = idr_alloc(&(drm_lease_owner(lessor)->lessee_idr), lessee, 1, 0, GFP_KERNEL);
	अगर (id < 0) अणु
		error = id;
		जाओ out_lessee;
	पूर्ण

	lessee->lessee_id = id;
	lessee->lessor = drm_master_get(lessor);
	list_add_tail(&lessee->lessee_list, &lessor->lessees);

	/* Move the leases over */
	lessee->leases = *leases;
	DRM_DEBUG_LEASE("new lessee %d %p, lessor %d %p\n", lessee->lessee_id, lessee, lessor->lessee_id, lessor);

	mutex_unlock(&dev->mode_config.idr_mutex);
	वापस lessee;

out_lessee:
	mutex_unlock(&dev->mode_config.idr_mutex);

	drm_master_put(&lessee);

	वापस ERR_PTR(error);
पूर्ण

/**
 * drm_lease_destroy - a master is going away (idr_mutex not held)
 * @master: the drm_master being destroyed
 *
 * All lessees will have been destroyed as they
 * hold a reference on their lessor. Notअगरy any
 * lessor क्रम this master so that it can check
 * the list of lessees.
 */
व्योम drm_lease_destroy(काष्ठा drm_master *master)
अणु
	काष्ठा drm_device *dev = master->dev;

	mutex_lock(&dev->mode_config.idr_mutex);

	DRM_DEBUG_LEASE("drm_lease_destroy %d\n", master->lessee_id);

	/* This master is referenced by all lessees, hence it cannot be destroyed
	 * until all of them have been
	 */
	WARN_ON(!list_empty(&master->lessees));

	/* Remove this master from the lessee idr in the owner */
	अगर (master->lessee_id != 0) अणु
		DRM_DEBUG_LEASE("remove master %d from device list of lessees\n", master->lessee_id);
		idr_हटाओ(&(drm_lease_owner(master)->lessee_idr), master->lessee_id);
	पूर्ण

	/* Remove this master from any lessee list it may be on */
	list_del(&master->lessee_list);

	mutex_unlock(&dev->mode_config.idr_mutex);

	अगर (master->lessor) अणु
		/* Tell the master to check the lessee list */
		drm_sysfs_lease_event(dev);
		drm_master_put(&master->lessor);
	पूर्ण

	DRM_DEBUG_LEASE("drm_lease_destroy done %d\n", master->lessee_id);
पूर्ण

/**
 * _drm_lease_revoke - revoke access to all leased objects (idr_mutex held)
 * @top: the master losing its lease
 */
अटल व्योम _drm_lease_revoke(काष्ठा drm_master *top)
अणु
	पूर्णांक object;
	व्योम *entry;
	काष्ठा drm_master *master = top;

	lockdep_निश्चित_held(&top->dev->mode_config.idr_mutex);

	/*
	 * Walk the tree starting at 'top' emptying all leases. Because
	 * the tree is fully connected, we can करो this without recursing
	 */
	क्रम (;;) अणु
		DRM_DEBUG_LEASE("revoke leases for %p %d\n", master, master->lessee_id);

		/* Evacuate the lease */
		idr_क्रम_each_entry(&master->leases, entry, object)
			idr_हटाओ(&master->leases, object);

		/* Depth-first list walk */

		/* Down */
		अगर (!list_empty(&master->lessees)) अणु
			master = list_first_entry(&master->lessees, काष्ठा drm_master, lessee_list);
		पूर्ण अन्यथा अणु
			/* Up */
			जबतक (master != top && master == list_last_entry(&master->lessor->lessees, काष्ठा drm_master, lessee_list))
				master = master->lessor;

			अगर (master == top)
				अवरोध;

			/* Over */
			master = list_next_entry(master, lessee_list);
		पूर्ण
	पूर्ण
पूर्ण

/**
 * drm_lease_revoke - revoke access to all leased objects (idr_mutex not held)
 * @top: the master losing its lease
 */
व्योम drm_lease_revoke(काष्ठा drm_master *top)
अणु
	mutex_lock(&top->dev->mode_config.idr_mutex);
	_drm_lease_revoke(top);
	mutex_unlock(&top->dev->mode_config.idr_mutex);
पूर्ण

अटल पूर्णांक validate_lease(काष्ठा drm_device *dev,
			  पूर्णांक object_count,
			  काष्ठा drm_mode_object **objects,
			  bool universal_planes)
अणु
	पूर्णांक o;
	पूर्णांक has_crtc = -1;
	पूर्णांक has_connector = -1;
	पूर्णांक has_plane = -1;

	/* we want to confirm that there is at least one crtc, plane
	   connector object. */

	क्रम (o = 0; o < object_count; o++) अणु
		अगर (objects[o]->type == DRM_MODE_OBJECT_CRTC && has_crtc == -1) अणु
			has_crtc = o;
		पूर्ण
		अगर (objects[o]->type == DRM_MODE_OBJECT_CONNECTOR && has_connector == -1)
			has_connector = o;

		अगर (universal_planes) अणु
			अगर (objects[o]->type == DRM_MODE_OBJECT_PLANE && has_plane == -1)
				has_plane = o;
		पूर्ण
	पूर्ण
	अगर (has_crtc == -1 || has_connector == -1)
		वापस -EINVAL;
	अगर (universal_planes && has_plane == -1)
		वापस -EINVAL;
	वापस 0;
पूर्ण

अटल पूर्णांक fill_object_idr(काष्ठा drm_device *dev,
			   काष्ठा drm_file *lessor_priv,
			   काष्ठा idr *leases,
			   पूर्णांक object_count,
			   u32 *object_ids)
अणु
	काष्ठा drm_mode_object **objects;
	u32 o;
	पूर्णांक ret;
	bool universal_planes = READ_ONCE(lessor_priv->universal_planes);

	objects = kसुस्मृति(object_count, माप(काष्ठा drm_mode_object *),
			  GFP_KERNEL);
	अगर (!objects)
		वापस -ENOMEM;

	/* step one - get references to all the mode objects
	   and check क्रम validity. */
	क्रम (o = 0; o < object_count; o++) अणु
		objects[o] = drm_mode_object_find(dev, lessor_priv,
						  object_ids[o],
						  DRM_MODE_OBJECT_ANY);
		अगर (!objects[o]) अणु
			ret = -ENOENT;
			जाओ out_मुक्त_objects;
		पूर्ण

		अगर (!drm_mode_object_lease_required(objects[o]->type)) अणु
			DRM_DEBUG_KMS("invalid object for lease\n");
			ret = -EINVAL;
			जाओ out_मुक्त_objects;
		पूर्ण
	पूर्ण

	ret = validate_lease(dev, object_count, objects, universal_planes);
	अगर (ret) अणु
		DRM_DEBUG_LEASE("lease validation failed\n");
		जाओ out_मुक्त_objects;
	पूर्ण

	/* add their IDs to the lease request - taking पूर्णांकo account
	   universal planes */
	क्रम (o = 0; o < object_count; o++) अणु
		काष्ठा drm_mode_object *obj = objects[o];
		u32 object_id = objects[o]->id;

		DRM_DEBUG_LEASE("Adding object %d to lease\n", object_id);

		/*
		 * We're using an IDR to hold the set of leased
		 * objects, but we करोn't need to point at the object's
		 * data काष्ठाure from the lease as the मुख्य object_idr
		 * will be used to actually find that. Instead, all we
		 * really want is a 'leased/not-leased' result, क्रम
		 * which any non-शून्य poपूर्णांकer will work fine.
		 */
		ret = idr_alloc(leases, &drm_lease_idr_object , object_id, object_id + 1, GFP_KERNEL);
		अगर (ret < 0) अणु
			DRM_DEBUG_LEASE("Object %d cannot be inserted into leases (%d)\n",
					object_id, ret);
			जाओ out_मुक्त_objects;
		पूर्ण
		अगर (obj->type == DRM_MODE_OBJECT_CRTC && !universal_planes) अणु
			काष्ठा drm_crtc *crtc = obj_to_crtc(obj);

			ret = idr_alloc(leases, &drm_lease_idr_object, crtc->primary->base.id, crtc->primary->base.id + 1, GFP_KERNEL);
			अगर (ret < 0) अणु
				DRM_DEBUG_LEASE("Object primary plane %d cannot be inserted into leases (%d)\n",
						object_id, ret);
				जाओ out_मुक्त_objects;
			पूर्ण
			अगर (crtc->cursor) अणु
				ret = idr_alloc(leases, &drm_lease_idr_object, crtc->cursor->base.id, crtc->cursor->base.id + 1, GFP_KERNEL);
				अगर (ret < 0) अणु
					DRM_DEBUG_LEASE("Object cursor plane %d cannot be inserted into leases (%d)\n",
							object_id, ret);
					जाओ out_मुक्त_objects;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण

	ret = 0;
out_मुक्त_objects:
	क्रम (o = 0; o < object_count; o++) अणु
		अगर (objects[o])
			drm_mode_object_put(objects[o]);
	पूर्ण
	kमुक्त(objects);
	वापस ret;
पूर्ण

/**
 * drm_mode_create_lease_ioctl - create a new lease
 * @dev: the drm device
 * @data: poपूर्णांकer to काष्ठा drm_mode_create_lease
 * @lessor_priv: the file being manipulated
 *
 * The master associated with the specअगरied file will have a lease
 * created containing the objects specअगरied in the ioctl काष्ठाure.
 * A file descriptor will be allocated क्रम that and वापसed to the
 * application.
 */
पूर्णांक drm_mode_create_lease_ioctl(काष्ठा drm_device *dev,
				व्योम *data, काष्ठा drm_file *lessor_priv)
अणु
	काष्ठा drm_mode_create_lease *cl = data;
	माप_प्रकार object_count;
	पूर्णांक ret = 0;
	काष्ठा idr leases;
	काष्ठा drm_master *lessor = lessor_priv->master;
	काष्ठा drm_master *lessee = शून्य;
	काष्ठा file *lessee_file = शून्य;
	काष्ठा file *lessor_file = lessor_priv->filp;
	काष्ठा drm_file *lessee_priv;
	पूर्णांक fd = -1;
	uपूर्णांक32_t *object_ids;

	/* Can't lease without MODESET */
	अगर (!drm_core_check_feature(dev, DRIVER_MODESET))
		वापस -EOPNOTSUPP;

	/* Do not allow sub-leases */
	अगर (lessor->lessor) अणु
		DRM_DEBUG_LEASE("recursive leasing not allowed\n");
		वापस -EINVAL;
	पूर्ण

	/* need some objects */
	अगर (cl->object_count == 0) अणु
		DRM_DEBUG_LEASE("no objects in lease\n");
		वापस -EINVAL;
	पूर्ण

	अगर (cl->flags && (cl->flags & ~(O_CLOEXEC | O_NONBLOCK))) अणु
		DRM_DEBUG_LEASE("invalid flags\n");
		वापस -EINVAL;
	पूर्ण

	object_count = cl->object_count;

	object_ids = memdup_user(u64_to_user_ptr(cl->object_ids),
			array_size(object_count, माप(__u32)));
	अगर (IS_ERR(object_ids))
		वापस PTR_ERR(object_ids);

	idr_init(&leases);

	/* fill and validate the object idr */
	ret = fill_object_idr(dev, lessor_priv, &leases,
			      object_count, object_ids);
	kमुक्त(object_ids);
	अगर (ret) अणु
		DRM_DEBUG_LEASE("lease object lookup failed: %i\n", ret);
		idr_destroy(&leases);
		वापस ret;
	पूर्ण

	/* Allocate a file descriptor क्रम the lease */
	fd = get_unused_fd_flags(cl->flags & (O_CLOEXEC | O_NONBLOCK));
	अगर (fd < 0) अणु
		idr_destroy(&leases);
		वापस fd;
	पूर्ण

	DRM_DEBUG_LEASE("Creating lease\n");
	/* lessee will take the ownership of leases */
	lessee = drm_lease_create(lessor, &leases);

	अगर (IS_ERR(lessee)) अणु
		ret = PTR_ERR(lessee);
		idr_destroy(&leases);
		जाओ out_leases;
	पूर्ण

	/* Clone the lessor file to create a new file क्रम us */
	DRM_DEBUG_LEASE("Allocating lease file\n");
	lessee_file = file_clone_खोलो(lessor_file);
	अगर (IS_ERR(lessee_file)) अणु
		ret = PTR_ERR(lessee_file);
		जाओ out_lessee;
	पूर्ण

	lessee_priv = lessee_file->निजी_data;
	/* Change the file to a master one */
	drm_master_put(&lessee_priv->master);
	lessee_priv->master = lessee;
	lessee_priv->is_master = 1;
	lessee_priv->authenticated = 1;

	/* Pass fd back to userspace */
	DRM_DEBUG_LEASE("Returning fd %d id %d\n", fd, lessee->lessee_id);
	cl->fd = fd;
	cl->lessee_id = lessee->lessee_id;

	/* Hook up the fd */
	fd_install(fd, lessee_file);

	DRM_DEBUG_LEASE("drm_mode_create_lease_ioctl succeeded\n");
	वापस 0;

out_lessee:
	drm_master_put(&lessee);

out_leases:
	put_unused_fd(fd);

	DRM_DEBUG_LEASE("drm_mode_create_lease_ioctl failed: %d\n", ret);
	वापस ret;
पूर्ण

/**
 * drm_mode_list_lessees_ioctl - list lessee ids
 * @dev: the drm device
 * @data: poपूर्णांकer to काष्ठा drm_mode_list_lessees
 * @lessor_priv: the file being manipulated
 *
 * Starting from the master associated with the specअगरied file,
 * the master with the provided lessee_id is found, and then
 * an array of lessee ids associated with leases from that master
 * are वापसed.
 */

पूर्णांक drm_mode_list_lessees_ioctl(काष्ठा drm_device *dev,
			       व्योम *data, काष्ठा drm_file *lessor_priv)
अणु
	काष्ठा drm_mode_list_lessees *arg = data;
	__u32 __user *lessee_ids = (__u32 __user *) (uपूर्णांकptr_t) (arg->lessees_ptr);
	__u32 count_lessees = arg->count_lessees;
	काष्ठा drm_master *lessor = lessor_priv->master, *lessee;
	पूर्णांक count;
	पूर्णांक ret = 0;

	अगर (arg->pad)
		वापस -EINVAL;

	/* Can't lease without MODESET */
	अगर (!drm_core_check_feature(dev, DRIVER_MODESET))
		वापस -EOPNOTSUPP;

	DRM_DEBUG_LEASE("List lessees for %d\n", lessor->lessee_id);

	mutex_lock(&dev->mode_config.idr_mutex);

	count = 0;
	drm_क्रम_each_lessee(lessee, lessor) अणु
		/* Only list un-revoked leases */
		अगर (!idr_is_empty(&lessee->leases)) अणु
			अगर (count_lessees > count) अणु
				DRM_DEBUG_LEASE("Add lessee %d\n", lessee->lessee_id);
				ret = put_user(lessee->lessee_id, lessee_ids + count);
				अगर (ret)
					अवरोध;
			पूर्ण
			count++;
		पूर्ण
	पूर्ण

	DRM_DEBUG_LEASE("Lessor leases to %d\n", count);
	अगर (ret == 0)
		arg->count_lessees = count;

	mutex_unlock(&dev->mode_config.idr_mutex);

	वापस ret;
पूर्ण

/**
 * drm_mode_get_lease_ioctl - list leased objects
 * @dev: the drm device
 * @data: poपूर्णांकer to काष्ठा drm_mode_get_lease
 * @lessee_priv: the file being manipulated
 *
 * Return the list of leased objects क्रम the specअगरied lessee
 */

पूर्णांक drm_mode_get_lease_ioctl(काष्ठा drm_device *dev,
			     व्योम *data, काष्ठा drm_file *lessee_priv)
अणु
	काष्ठा drm_mode_get_lease *arg = data;
	__u32 __user *object_ids = (__u32 __user *) (uपूर्णांकptr_t) (arg->objects_ptr);
	__u32 count_objects = arg->count_objects;
	काष्ठा drm_master *lessee = lessee_priv->master;
	काष्ठा idr *object_idr;
	पूर्णांक count;
	व्योम *entry;
	पूर्णांक object;
	पूर्णांक ret = 0;

	अगर (arg->pad)
		वापस -EINVAL;

	/* Can't lease without MODESET */
	अगर (!drm_core_check_feature(dev, DRIVER_MODESET))
		वापस -EOPNOTSUPP;

	DRM_DEBUG_LEASE("get lease for %d\n", lessee->lessee_id);

	mutex_lock(&dev->mode_config.idr_mutex);

	अगर (lessee->lessor == शून्य)
		/* owner can use all objects */
		object_idr = &lessee->dev->mode_config.object_idr;
	अन्यथा
		/* lessee can only use allowed object */
		object_idr = &lessee->leases;

	count = 0;
	idr_क्रम_each_entry(object_idr, entry, object) अणु
		अगर (count_objects > count) अणु
			DRM_DEBUG_LEASE("adding object %d\n", object);
			ret = put_user(object, object_ids + count);
			अगर (ret)
				अवरोध;
		पूर्ण
		count++;
	पूर्ण

	DRM_DEBUG("lease holds %d objects\n", count);
	अगर (ret == 0)
		arg->count_objects = count;

	mutex_unlock(&dev->mode_config.idr_mutex);

	वापस ret;
पूर्ण

/**
 * drm_mode_revoke_lease_ioctl - revoke lease
 * @dev: the drm device
 * @data: poपूर्णांकer to काष्ठा drm_mode_revoke_lease
 * @lessor_priv: the file being manipulated
 *
 * This हटाओs all of the objects from the lease without
 * actually getting rid of the lease itself; that way all
 * references to it still work correctly
 */
पूर्णांक drm_mode_revoke_lease_ioctl(काष्ठा drm_device *dev,
				व्योम *data, काष्ठा drm_file *lessor_priv)
अणु
	काष्ठा drm_mode_revoke_lease *arg = data;
	काष्ठा drm_master *lessor = lessor_priv->master;
	काष्ठा drm_master *lessee;
	पूर्णांक ret = 0;

	DRM_DEBUG_LEASE("revoke lease for %d\n", arg->lessee_id);

	/* Can't lease without MODESET */
	अगर (!drm_core_check_feature(dev, DRIVER_MODESET))
		वापस -EOPNOTSUPP;

	mutex_lock(&dev->mode_config.idr_mutex);

	lessee = _drm_find_lessee(lessor, arg->lessee_id);

	/* No such lessee */
	अगर (!lessee) अणु
		ret = -ENOENT;
		जाओ fail;
	पूर्ण

	/* Lease is not held by lessor */
	अगर (lessee->lessor != lessor) अणु
		ret = -EACCES;
		जाओ fail;
	पूर्ण

	_drm_lease_revoke(lessee);

fail:
	mutex_unlock(&dev->mode_config.idr_mutex);

	वापस ret;
पूर्ण
