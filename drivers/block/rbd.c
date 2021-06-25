<शैली गुरु>

/*
   rbd.c -- Export ceph raकरोs objects as a Linux block device


   based on drivers/block/osdblk.c:

   Copyright 2009 Red Hat, Inc.

   This program is मुक्त software; you can redistribute it and/or modअगरy
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License क्रम more details.

   You should have received a copy of the GNU General Public License
   aदीर्घ with this program; see the file COPYING.  If not, ग_लिखो to
   the Free Software Foundation, 675 Mass Ave, Cambridge, MA 02139, USA.



   For usage inकाष्ठाions, please refer to:

                 Documentation/ABI/testing/sysfs-bus-rbd

 */

#समावेश <linux/ceph/libceph.h>
#समावेश <linux/ceph/osd_client.h>
#समावेश <linux/ceph/mon_client.h>
#समावेश <linux/ceph/cls_lock_client.h>
#समावेश <linux/ceph/striper.h>
#समावेश <linux/ceph/decode.h>
#समावेश <linux/fs_parser.h>
#समावेश <linux/द्वा_खोज.h>

#समावेश <linux/kernel.h>
#समावेश <linux/device.h>
#समावेश <linux/module.h>
#समावेश <linux/blk-mq.h>
#समावेश <linux/fs.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/slab.h>
#समावेश <linux/idr.h>
#समावेश <linux/workqueue.h>

#समावेश "rbd_types.h"

#घोषणा RBD_DEBUG	/* Activate rbd_निश्चित() calls */

/*
 * Increment the given counter and वापस its updated value.
 * If the counter is alपढ़ोy 0 it will not be incremented.
 * If the counter is alपढ़ोy at its maximum value वापसs
 * -EINVAL without updating it.
 */
अटल पूर्णांक atomic_inc_वापस_safe(atomic_t *v)
अणु
	अचिन्हित पूर्णांक counter;

	counter = (अचिन्हित पूर्णांक)atomic_fetch_add_unless(v, 1, 0);
	अगर (counter <= (अचिन्हित पूर्णांक)पूर्णांक_उच्च)
		वापस (पूर्णांक)counter;

	atomic_dec(v);

	वापस -EINVAL;
पूर्ण

/* Decrement the counter.  Return the resulting value, or -EINVAL */
अटल पूर्णांक atomic_dec_वापस_safe(atomic_t *v)
अणु
	पूर्णांक counter;

	counter = atomic_dec_वापस(v);
	अगर (counter >= 0)
		वापस counter;

	atomic_inc(v);

	वापस -EINVAL;
पूर्ण

#घोषणा RBD_DRV_NAME "rbd"

#घोषणा RBD_MINORS_PER_MAJOR		256
#घोषणा RBD_SINGLE_MAJOR_PART_SHIFT	4

#घोषणा RBD_MAX_PARENT_CHAIN_LEN	16

#घोषणा RBD_SNAP_DEV_NAME_PREFIX	"snap_"
#घोषणा RBD_MAX_SNAP_NAME_LEN	\
			(NAME_MAX - (माप (RBD_SNAP_DEV_NAME_PREFIX) - 1))

#घोषणा RBD_MAX_SNAP_COUNT	510	/* allows max snapc to fit in 4KB */

#घोषणा RBD_SNAP_HEAD_NAME	"-"

#घोषणा	BAD_SNAP_INDEX	U32_MAX		/* invalid index पूर्णांकo snap array */

/* This allows a single page to hold an image name sent by OSD */
#घोषणा RBD_IMAGE_NAME_LEN_MAX	(PAGE_SIZE - माप (__le32) - 1)
#घोषणा RBD_IMAGE_ID_LEN_MAX	64

#घोषणा RBD_OBJ_PREFIX_LEN_MAX	64

#घोषणा RBD_NOTIFY_TIMEOUT	5	/* seconds */
#घोषणा RBD_RETRY_DELAY		msecs_to_jअगरfies(1000)

/* Feature bits */

#घोषणा RBD_FEATURE_LAYERING		(1ULL<<0)
#घोषणा RBD_FEATURE_STRIPINGV2		(1ULL<<1)
#घोषणा RBD_FEATURE_EXCLUSIVE_LOCK	(1ULL<<2)
#घोषणा RBD_FEATURE_OBJECT_MAP		(1ULL<<3)
#घोषणा RBD_FEATURE_FAST_DIFF		(1ULL<<4)
#घोषणा RBD_FEATURE_DEEP_FLATTEN	(1ULL<<5)
#घोषणा RBD_FEATURE_DATA_POOL		(1ULL<<7)
#घोषणा RBD_FEATURE_OPERATIONS		(1ULL<<8)

#घोषणा RBD_FEATURES_ALL	(RBD_FEATURE_LAYERING |		\
				 RBD_FEATURE_STRIPINGV2 |	\
				 RBD_FEATURE_EXCLUSIVE_LOCK |	\
				 RBD_FEATURE_OBJECT_MAP |	\
				 RBD_FEATURE_FAST_DIFF |	\
				 RBD_FEATURE_DEEP_FLATTEN |	\
				 RBD_FEATURE_DATA_POOL |	\
				 RBD_FEATURE_OPERATIONS)

/* Features supported by this (client software) implementation. */

#घोषणा RBD_FEATURES_SUPPORTED	(RBD_FEATURES_ALL)

/*
 * An RBD device name will be "rbd#", where the "rbd" comes from
 * RBD_DRV_NAME above, and # is a unique पूर्णांकeger identअगरier.
 */
#घोषणा DEV_NAME_LEN		32

/*
 * block device image metadata (in-memory version)
 */
काष्ठा rbd_image_header अणु
	/* These six fields never change क्रम a given rbd image */
	अक्षर *object_prefix;
	__u8 obj_order;
	u64 stripe_unit;
	u64 stripe_count;
	s64 data_pool_id;
	u64 features;		/* Might be changeable someday? */

	/* The reमुख्यing fields need to be updated occasionally */
	u64 image_size;
	काष्ठा ceph_snap_context *snapc;
	अक्षर *snap_names;	/* क्रमmat 1 only */
	u64 *snap_sizes;	/* क्रमmat 1 only */
पूर्ण;

/*
 * An rbd image specअगरication.
 *
 * The tuple (pool_id, image_id, snap_id) is sufficient to uniquely
 * identअगरy an image.  Each rbd_dev काष्ठाure includes a poपूर्णांकer to
 * an rbd_spec काष्ठाure that encapsulates this identity.
 *
 * Each of the id's in an rbd_spec has an associated name.  For a
 * user-mapped image, the names are supplied and the id's associated
 * with them are looked up.  For a layered image, a parent image is
 * defined by the tuple, and the names are looked up.
 *
 * An rbd_dev काष्ठाure contains a parent_spec poपूर्णांकer which is
 * non-null अगर the image it represents is a child in a layered
 * image.  This poपूर्णांकer will refer to the rbd_spec काष्ठाure used
 * by the parent rbd_dev क्रम its own identity (i.e., the काष्ठाure
 * is shared between the parent and child).
 *
 * Since these काष्ठाures are populated once, during the discovery
 * phase of image स्थिरruction, they are effectively immutable so
 * we make no efक्रमt to synchronize access to them.
 *
 * Note that code herein करोes not assume the image name is known (it
 * could be a null poपूर्णांकer).
 */
काष्ठा rbd_spec अणु
	u64		pool_id;
	स्थिर अक्षर	*pool_name;
	स्थिर अक्षर	*pool_ns;	/* शून्य अगर शेष, never "" */

	स्थिर अक्षर	*image_id;
	स्थिर अक्षर	*image_name;

	u64		snap_id;
	स्थिर अक्षर	*snap_name;

	काष्ठा kref	kref;
पूर्ण;

/*
 * an instance of the client.  multiple devices may share an rbd client.
 */
काष्ठा rbd_client अणु
	काष्ठा ceph_client	*client;
	काष्ठा kref		kref;
	काष्ठा list_head	node;
पूर्ण;

काष्ठा pending_result अणु
	पूर्णांक			result;		/* first nonzero result */
	पूर्णांक			num_pending;
पूर्ण;

काष्ठा rbd_img_request;

क्रमागत obj_request_type अणु
	OBJ_REQUEST_NODATA = 1,
	OBJ_REQUEST_BIO,	/* poपूर्णांकer पूर्णांकo provided bio (list) */
	OBJ_REQUEST_BVECS,	/* poपूर्णांकer पूर्णांकo provided bio_vec array */
	OBJ_REQUEST_OWN_BVECS,	/* निजी bio_vec array, करोesn't own pages */
पूर्ण;

क्रमागत obj_operation_type अणु
	OBJ_OP_READ = 1,
	OBJ_OP_WRITE,
	OBJ_OP_DISCARD,
	OBJ_OP_ZEROOUT,
पूर्ण;

#घोषणा RBD_OBJ_FLAG_DELETION			(1U << 0)
#घोषणा RBD_OBJ_FLAG_COPYUP_ENABLED		(1U << 1)
#घोषणा RBD_OBJ_FLAG_COPYUP_ZEROS		(1U << 2)
#घोषणा RBD_OBJ_FLAG_MAY_EXIST			(1U << 3)
#घोषणा RBD_OBJ_FLAG_NOOP_FOR_NONEXISTENT	(1U << 4)

क्रमागत rbd_obj_पढ़ो_state अणु
	RBD_OBJ_READ_START = 1,
	RBD_OBJ_READ_OBJECT,
	RBD_OBJ_READ_PARENT,
पूर्ण;

/*
 * Writes go through the following state machine to deal with
 * layering:
 *
 *            . . . . . RBD_OBJ_WRITE_GUARD. . . . . . . . . . . . . .
 *            .                 |                                    .
 *            .                 v                                    .
 *            .    RBD_OBJ_WRITE_READ_FROM_PARENT. . .               .
 *            .                 |                    .               .
 *            .                 v                    v (deep-copyup  .
 *    (image  .   RBD_OBJ_WRITE_COPYUP_EMPTY_SNAPC   .  not needed)  .
 * flattened) v                 |                    .               .
 *            .                 v                    .               .
 *            . . . .RBD_OBJ_WRITE_COPYUP_OPS. . . . .      (copyup  .
 *                              |                        not needed) v
 *                              v                                    .
 *                            करोne . . . . . . . . . . . . . . . . . .
 *                              ^
 *                              |
 *                     RBD_OBJ_WRITE_FLAT
 *
 * Writes start in RBD_OBJ_WRITE_GUARD or _FLAT, depending on whether
 * निश्चित_exists guard is needed or not (in some हालs it's not needed
 * even अगर there is a parent).
 */
क्रमागत rbd_obj_ग_लिखो_state अणु
	RBD_OBJ_WRITE_START = 1,
	RBD_OBJ_WRITE_PRE_OBJECT_MAP,
	RBD_OBJ_WRITE_OBJECT,
	__RBD_OBJ_WRITE_COPYUP,
	RBD_OBJ_WRITE_COPYUP,
	RBD_OBJ_WRITE_POST_OBJECT_MAP,
पूर्ण;

क्रमागत rbd_obj_copyup_state अणु
	RBD_OBJ_COPYUP_START = 1,
	RBD_OBJ_COPYUP_READ_PARENT,
	__RBD_OBJ_COPYUP_OBJECT_MAPS,
	RBD_OBJ_COPYUP_OBJECT_MAPS,
	__RBD_OBJ_COPYUP_WRITE_OBJECT,
	RBD_OBJ_COPYUP_WRITE_OBJECT,
पूर्ण;

काष्ठा rbd_obj_request अणु
	काष्ठा ceph_object_extent ex;
	अचिन्हित पूर्णांक		flags;	/* RBD_OBJ_FLAG_* */
	जोड़ अणु
		क्रमागत rbd_obj_पढ़ो_state	 पढ़ो_state;	/* क्रम पढ़ोs */
		क्रमागत rbd_obj_ग_लिखो_state ग_लिखो_state;	/* क्रम ग_लिखोs */
	पूर्ण;

	काष्ठा rbd_img_request	*img_request;
	काष्ठा ceph_file_extent	*img_extents;
	u32			num_img_extents;

	जोड़ अणु
		काष्ठा ceph_bio_iter	bio_pos;
		काष्ठा अणु
			काष्ठा ceph_bvec_iter	bvec_pos;
			u32			bvec_count;
			u32			bvec_idx;
		पूर्ण;
	पूर्ण;

	क्रमागत rbd_obj_copyup_state copyup_state;
	काष्ठा bio_vec		*copyup_bvecs;
	u32			copyup_bvec_count;

	काष्ठा list_head	osd_reqs;	/* w/ r_निजी_item */

	काष्ठा mutex		state_mutex;
	काष्ठा pending_result	pending;
	काष्ठा kref		kref;
पूर्ण;

क्रमागत img_req_flags अणु
	IMG_REQ_CHILD,		/* initiator: block = 0, child image = 1 */
	IMG_REQ_LAYERED,	/* ENOENT handling: normal = 0, layered = 1 */
पूर्ण;

क्रमागत rbd_img_state अणु
	RBD_IMG_START = 1,
	RBD_IMG_EXCLUSIVE_LOCK,
	__RBD_IMG_OBJECT_REQUESTS,
	RBD_IMG_OBJECT_REQUESTS,
पूर्ण;

काष्ठा rbd_img_request अणु
	काष्ठा rbd_device	*rbd_dev;
	क्रमागत obj_operation_type	op_type;
	क्रमागत obj_request_type	data_type;
	अचिन्हित दीर्घ		flags;
	क्रमागत rbd_img_state	state;
	जोड़ अणु
		u64			snap_id;	/* क्रम पढ़ोs */
		काष्ठा ceph_snap_context *snapc;	/* क्रम ग_लिखोs */
	पूर्ण;
	काष्ठा rbd_obj_request	*obj_request;	/* obj req initiator */

	काष्ठा list_head	lock_item;
	काष्ठा list_head	object_extents;	/* obj_req.ex काष्ठाs */

	काष्ठा mutex		state_mutex;
	काष्ठा pending_result	pending;
	काष्ठा work_काष्ठा	work;
	पूर्णांक			work_result;
पूर्ण;

#घोषणा क्रम_each_obj_request(ireq, oreq) \
	list_क्रम_each_entry(oreq, &(ireq)->object_extents, ex.oe_item)
#घोषणा क्रम_each_obj_request_safe(ireq, oreq, n) \
	list_क्रम_each_entry_safe(oreq, n, &(ireq)->object_extents, ex.oe_item)

क्रमागत rbd_watch_state अणु
	RBD_WATCH_STATE_UNREGISTERED,
	RBD_WATCH_STATE_REGISTERED,
	RBD_WATCH_STATE_ERROR,
पूर्ण;

क्रमागत rbd_lock_state अणु
	RBD_LOCK_STATE_UNLOCKED,
	RBD_LOCK_STATE_LOCKED,
	RBD_LOCK_STATE_RELEASING,
पूर्ण;

/* WatchNotअगरy::ClientId */
काष्ठा rbd_client_id अणु
	u64 gid;
	u64 handle;
पूर्ण;

काष्ठा rbd_mapping अणु
	u64                     size;
पूर्ण;

/*
 * a single device
 */
काष्ठा rbd_device अणु
	पूर्णांक			dev_id;		/* blkdev unique id */

	पूर्णांक			major;		/* blkdev asचिन्हित major */
	पूर्णांक			minor;
	काष्ठा gendisk		*disk;		/* blkdev's gendisk and rq */

	u32			image_क्रमmat;	/* Either 1 or 2 */
	काष्ठा rbd_client	*rbd_client;

	अक्षर			name[DEV_NAME_LEN]; /* blkdev name, e.g. rbd3 */

	spinlock_t		lock;		/* queue, flags, खोलो_count */

	काष्ठा rbd_image_header	header;
	अचिन्हित दीर्घ		flags;		/* possibly lock रक्षित */
	काष्ठा rbd_spec		*spec;
	काष्ठा rbd_options	*opts;
	अक्षर			*config_info;	/* addअणु,_single_majorपूर्ण string */

	काष्ठा ceph_object_id	header_oid;
	काष्ठा ceph_object_locator header_oloc;

	काष्ठा ceph_file_layout	layout;		/* used क्रम all rbd requests */

	काष्ठा mutex		watch_mutex;
	क्रमागत rbd_watch_state	watch_state;
	काष्ठा ceph_osd_linger_request *watch_handle;
	u64			watch_cookie;
	काष्ठा delayed_work	watch_dwork;

	काष्ठा rw_semaphore	lock_rwsem;
	क्रमागत rbd_lock_state	lock_state;
	अक्षर			lock_cookie[32];
	काष्ठा rbd_client_id	owner_cid;
	काष्ठा work_काष्ठा	acquired_lock_work;
	काष्ठा work_काष्ठा	released_lock_work;
	काष्ठा delayed_work	lock_dwork;
	काष्ठा work_काष्ठा	unlock_work;
	spinlock_t		lock_lists_lock;
	काष्ठा list_head	acquiring_list;
	काष्ठा list_head	running_list;
	काष्ठा completion	acquire_रुको;
	पूर्णांक			acquire_err;
	काष्ठा completion	releasing_रुको;

	spinlock_t		object_map_lock;
	u8			*object_map;
	u64			object_map_size;	/* in objects */
	u64			object_map_flags;

	काष्ठा workqueue_काष्ठा	*task_wq;

	काष्ठा rbd_spec		*parent_spec;
	u64			parent_overlap;
	atomic_t		parent_ref;
	काष्ठा rbd_device	*parent;

	/* Block layer tags. */
	काष्ठा blk_mq_tag_set	tag_set;

	/* protects updating the header */
	काष्ठा rw_semaphore     header_rwsem;

	काष्ठा rbd_mapping	mapping;

	काष्ठा list_head	node;

	/* sysfs related */
	काष्ठा device		dev;
	अचिन्हित दीर्घ		खोलो_count;	/* रक्षित by lock */
पूर्ण;

/*
 * Flag bits क्रम rbd_dev->flags:
 * - REMOVING (which is coupled with rbd_dev->खोलो_count) is रक्षित
 *   by rbd_dev->lock
 */
क्रमागत rbd_dev_flags अणु
	RBD_DEV_FLAG_EXISTS,	/* rbd_dev_device_setup() ran */
	RBD_DEV_FLAG_REMOVING,	/* this mapping is being हटाओd */
	RBD_DEV_FLAG_READONLY,  /* -o ro or snapshot */
पूर्ण;

अटल DEFINE_MUTEX(client_mutex);	/* Serialize client creation */

अटल LIST_HEAD(rbd_dev_list);    /* devices */
अटल DEFINE_SPINLOCK(rbd_dev_list_lock);

अटल LIST_HEAD(rbd_client_list);		/* clients */
अटल DEFINE_SPINLOCK(rbd_client_list_lock);

/* Slab caches क्रम frequently-allocated काष्ठाures */

अटल काष्ठा kmem_cache	*rbd_img_request_cache;
अटल काष्ठा kmem_cache	*rbd_obj_request_cache;

अटल पूर्णांक rbd_major;
अटल DEFINE_IDA(rbd_dev_id_ida);

अटल काष्ठा workqueue_काष्ठा *rbd_wq;

अटल काष्ठा ceph_snap_context rbd_empty_snapc = अणु
	.nref = REFCOUNT_INIT(1),
पूर्ण;

/*
 * single-major requires >= 0.75 version of userspace rbd utility.
 */
अटल bool single_major = true;
module_param(single_major, bool, 0444);
MODULE_PARM_DESC(single_major, "Use a single major number for all rbd devices (default: true)");

अटल sमाप_प्रकार add_store(काष्ठा bus_type *bus, स्थिर अक्षर *buf, माप_प्रकार count);
अटल sमाप_प्रकार हटाओ_store(काष्ठा bus_type *bus, स्थिर अक्षर *buf,
			    माप_प्रकार count);
अटल sमाप_प्रकार add_single_major_store(काष्ठा bus_type *bus, स्थिर अक्षर *buf,
				      माप_प्रकार count);
अटल sमाप_प्रकार हटाओ_single_major_store(काष्ठा bus_type *bus, स्थिर अक्षर *buf,
					 माप_प्रकार count);
अटल पूर्णांक rbd_dev_image_probe(काष्ठा rbd_device *rbd_dev, पूर्णांक depth);

अटल पूर्णांक rbd_dev_id_to_minor(पूर्णांक dev_id)
अणु
	वापस dev_id << RBD_SINGLE_MAJOR_PART_SHIFT;
पूर्ण

अटल पूर्णांक minor_to_rbd_dev_id(पूर्णांक minor)
अणु
	वापस minor >> RBD_SINGLE_MAJOR_PART_SHIFT;
पूर्ण

अटल bool rbd_is_ro(काष्ठा rbd_device *rbd_dev)
अणु
	वापस test_bit(RBD_DEV_FLAG_READONLY, &rbd_dev->flags);
पूर्ण

अटल bool rbd_is_snap(काष्ठा rbd_device *rbd_dev)
अणु
	वापस rbd_dev->spec->snap_id != CEPH_NOSNAP;
पूर्ण

अटल bool __rbd_is_lock_owner(काष्ठा rbd_device *rbd_dev)
अणु
	lockdep_निश्चित_held(&rbd_dev->lock_rwsem);

	वापस rbd_dev->lock_state == RBD_LOCK_STATE_LOCKED ||
	       rbd_dev->lock_state == RBD_LOCK_STATE_RELEASING;
पूर्ण

अटल bool rbd_is_lock_owner(काष्ठा rbd_device *rbd_dev)
अणु
	bool is_lock_owner;

	करोwn_पढ़ो(&rbd_dev->lock_rwsem);
	is_lock_owner = __rbd_is_lock_owner(rbd_dev);
	up_पढ़ो(&rbd_dev->lock_rwsem);
	वापस is_lock_owner;
पूर्ण

अटल sमाप_प्रकार supported_features_show(काष्ठा bus_type *bus, अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "0x%llx\n", RBD_FEATURES_SUPPORTED);
पूर्ण

अटल BUS_ATTR_WO(add);
अटल BUS_ATTR_WO(हटाओ);
अटल BUS_ATTR_WO(add_single_major);
अटल BUS_ATTR_WO(हटाओ_single_major);
अटल BUS_ATTR_RO(supported_features);

अटल काष्ठा attribute *rbd_bus_attrs[] = अणु
	&bus_attr_add.attr,
	&bus_attr_हटाओ.attr,
	&bus_attr_add_single_major.attr,
	&bus_attr_हटाओ_single_major.attr,
	&bus_attr_supported_features.attr,
	शून्य,
पूर्ण;

अटल umode_t rbd_bus_is_visible(काष्ठा kobject *kobj,
				  काष्ठा attribute *attr, पूर्णांक index)
अणु
	अगर (!single_major &&
	    (attr == &bus_attr_add_single_major.attr ||
	     attr == &bus_attr_हटाओ_single_major.attr))
		वापस 0;

	वापस attr->mode;
पूर्ण

अटल स्थिर काष्ठा attribute_group rbd_bus_group = अणु
	.attrs = rbd_bus_attrs,
	.is_visible = rbd_bus_is_visible,
पूर्ण;
__ATTRIBUTE_GROUPS(rbd_bus);

अटल काष्ठा bus_type rbd_bus_type = अणु
	.name		= "rbd",
	.bus_groups	= rbd_bus_groups,
पूर्ण;

अटल व्योम rbd_root_dev_release(काष्ठा device *dev)
अणु
पूर्ण

अटल काष्ठा device rbd_root_dev = अणु
	.init_name =    "rbd",
	.release =      rbd_root_dev_release,
पूर्ण;

अटल __म_लिखो(2, 3)
व्योम rbd_warn(काष्ठा rbd_device *rbd_dev, स्थिर अक्षर *fmt, ...)
अणु
	काष्ठा va_क्रमmat vaf;
	बहु_सूची args;

	बहु_शुरू(args, fmt);
	vaf.fmt = fmt;
	vaf.va = &args;

	अगर (!rbd_dev)
		prपूर्णांकk(KERN_WARNING "%s: %pV\n", RBD_DRV_NAME, &vaf);
	अन्यथा अगर (rbd_dev->disk)
		prपूर्णांकk(KERN_WARNING "%s: %s: %pV\n",
			RBD_DRV_NAME, rbd_dev->disk->disk_name, &vaf);
	अन्यथा अगर (rbd_dev->spec && rbd_dev->spec->image_name)
		prपूर्णांकk(KERN_WARNING "%s: image %s: %pV\n",
			RBD_DRV_NAME, rbd_dev->spec->image_name, &vaf);
	अन्यथा अगर (rbd_dev->spec && rbd_dev->spec->image_id)
		prपूर्णांकk(KERN_WARNING "%s: id %s: %pV\n",
			RBD_DRV_NAME, rbd_dev->spec->image_id, &vaf);
	अन्यथा	/* punt */
		prपूर्णांकk(KERN_WARNING "%s: rbd_dev %p: %pV\n",
			RBD_DRV_NAME, rbd_dev, &vaf);
	बहु_पूर्ण(args);
पूर्ण

#अगर_घोषित RBD_DEBUG
#घोषणा rbd_निश्चित(expr)						\
		अगर (unlikely(!(expr))) अणु				\
			prपूर्णांकk(KERN_ERR "\nAssertion failure in %s() "	\
						"at line %d:\n\n"	\
					"\trbd_assert(%s);\n\n",	\
					__func__, __LINE__, #expr);	\
			BUG();						\
		पूर्ण
#अन्यथा /* !RBD_DEBUG */
#  define rbd_निश्चित(expr)	((व्योम) 0)
#पूर्ण_अगर /* !RBD_DEBUG */

अटल व्योम rbd_dev_हटाओ_parent(काष्ठा rbd_device *rbd_dev);

अटल पूर्णांक rbd_dev_refresh(काष्ठा rbd_device *rbd_dev);
अटल पूर्णांक rbd_dev_v2_header_oneसमय(काष्ठा rbd_device *rbd_dev);
अटल पूर्णांक rbd_dev_header_info(काष्ठा rbd_device *rbd_dev);
अटल पूर्णांक rbd_dev_v2_parent_info(काष्ठा rbd_device *rbd_dev);
अटल स्थिर अक्षर *rbd_dev_v2_snap_name(काष्ठा rbd_device *rbd_dev,
					u64 snap_id);
अटल पूर्णांक _rbd_dev_v2_snap_size(काष्ठा rbd_device *rbd_dev, u64 snap_id,
				u8 *order, u64 *snap_size);
अटल पूर्णांक rbd_dev_v2_get_flags(काष्ठा rbd_device *rbd_dev);

अटल व्योम rbd_obj_handle_request(काष्ठा rbd_obj_request *obj_req, पूर्णांक result);
अटल व्योम rbd_img_handle_request(काष्ठा rbd_img_request *img_req, पूर्णांक result);

/*
 * Return true अगर nothing अन्यथा is pending.
 */
अटल bool pending_result_dec(काष्ठा pending_result *pending, पूर्णांक *result)
अणु
	rbd_निश्चित(pending->num_pending > 0);

	अगर (*result && !pending->result)
		pending->result = *result;
	अगर (--pending->num_pending)
		वापस false;

	*result = pending->result;
	वापस true;
पूर्ण

अटल पूर्णांक rbd_खोलो(काष्ठा block_device *bdev, भ_शेषe_t mode)
अणु
	काष्ठा rbd_device *rbd_dev = bdev->bd_disk->निजी_data;
	bool removing = false;

	spin_lock_irq(&rbd_dev->lock);
	अगर (test_bit(RBD_DEV_FLAG_REMOVING, &rbd_dev->flags))
		removing = true;
	अन्यथा
		rbd_dev->खोलो_count++;
	spin_unlock_irq(&rbd_dev->lock);
	अगर (removing)
		वापस -ENOENT;

	(व्योम) get_device(&rbd_dev->dev);

	वापस 0;
पूर्ण

अटल व्योम rbd_release(काष्ठा gendisk *disk, भ_शेषe_t mode)
अणु
	काष्ठा rbd_device *rbd_dev = disk->निजी_data;
	अचिन्हित दीर्घ खोलो_count_beक्रमe;

	spin_lock_irq(&rbd_dev->lock);
	खोलो_count_beक्रमe = rbd_dev->खोलो_count--;
	spin_unlock_irq(&rbd_dev->lock);
	rbd_निश्चित(खोलो_count_beक्रमe > 0);

	put_device(&rbd_dev->dev);
पूर्ण

अटल स्थिर काष्ठा block_device_operations rbd_bd_ops = अणु
	.owner			= THIS_MODULE,
	.खोलो			= rbd_खोलो,
	.release		= rbd_release,
पूर्ण;

/*
 * Initialize an rbd client instance.  Success or not, this function
 * consumes ceph_opts.  Caller holds client_mutex.
 */
अटल काष्ठा rbd_client *rbd_client_create(काष्ठा ceph_options *ceph_opts)
अणु
	काष्ठा rbd_client *rbdc;
	पूर्णांक ret = -ENOMEM;

	करोut("%s:\n", __func__);
	rbdc = kदो_स्मृति(माप(काष्ठा rbd_client), GFP_KERNEL);
	अगर (!rbdc)
		जाओ out_opt;

	kref_init(&rbdc->kref);
	INIT_LIST_HEAD(&rbdc->node);

	rbdc->client = ceph_create_client(ceph_opts, rbdc);
	अगर (IS_ERR(rbdc->client))
		जाओ out_rbdc;
	ceph_opts = शून्य; /* Now rbdc->client is responsible क्रम ceph_opts */

	ret = ceph_खोलो_session(rbdc->client);
	अगर (ret < 0)
		जाओ out_client;

	spin_lock(&rbd_client_list_lock);
	list_add_tail(&rbdc->node, &rbd_client_list);
	spin_unlock(&rbd_client_list_lock);

	करोut("%s: rbdc %p\n", __func__, rbdc);

	वापस rbdc;
out_client:
	ceph_destroy_client(rbdc->client);
out_rbdc:
	kमुक्त(rbdc);
out_opt:
	अगर (ceph_opts)
		ceph_destroy_options(ceph_opts);
	करोut("%s: error %d\n", __func__, ret);

	वापस ERR_PTR(ret);
पूर्ण

अटल काष्ठा rbd_client *__rbd_get_client(काष्ठा rbd_client *rbdc)
अणु
	kref_get(&rbdc->kref);

	वापस rbdc;
पूर्ण

/*
 * Find a ceph client with specअगरic addr and configuration.  If
 * found, bump its reference count.
 */
अटल काष्ठा rbd_client *rbd_client_find(काष्ठा ceph_options *ceph_opts)
अणु
	काष्ठा rbd_client *client_node;
	bool found = false;

	अगर (ceph_opts->flags & CEPH_OPT_NOSHARE)
		वापस शून्य;

	spin_lock(&rbd_client_list_lock);
	list_क्रम_each_entry(client_node, &rbd_client_list, node) अणु
		अगर (!ceph_compare_options(ceph_opts, client_node->client)) अणु
			__rbd_get_client(client_node);

			found = true;
			अवरोध;
		पूर्ण
	पूर्ण
	spin_unlock(&rbd_client_list_lock);

	वापस found ? client_node : शून्य;
पूर्ण

/*
 * (Per device) rbd map options
 */
क्रमागत अणु
	Opt_queue_depth,
	Opt_alloc_size,
	Opt_lock_समयout,
	/* पूर्णांक args above */
	Opt_pool_ns,
	Opt_compression_hपूर्णांक,
	/* string args above */
	Opt_पढ़ो_only,
	Opt_पढ़ो_ग_लिखो,
	Opt_lock_on_पढ़ो,
	Opt_exclusive,
	Opt_notrim,
पूर्ण;

क्रमागत अणु
	Opt_compression_hपूर्णांक_none,
	Opt_compression_hपूर्णांक_compressible,
	Opt_compression_hपूर्णांक_incompressible,
पूर्ण;

अटल स्थिर काष्ठा स्थिरant_table rbd_param_compression_hपूर्णांक[] = अणु
	अणु"none",		Opt_compression_hपूर्णांक_noneपूर्ण,
	अणु"compressible",	Opt_compression_hपूर्णांक_compressibleपूर्ण,
	अणु"incompressible",	Opt_compression_hपूर्णांक_incompressibleपूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा fs_parameter_spec rbd_parameters[] = अणु
	fsparam_u32	("alloc_size",			Opt_alloc_size),
	fsparam_क्रमागत	("compression_hint",		Opt_compression_hपूर्णांक,
			 rbd_param_compression_hपूर्णांक),
	fsparam_flag	("exclusive",			Opt_exclusive),
	fsparam_flag	("lock_on_read",		Opt_lock_on_पढ़ो),
	fsparam_u32	("lock_timeout",		Opt_lock_समयout),
	fsparam_flag	("notrim",			Opt_notrim),
	fsparam_string	("_pool_ns",			Opt_pool_ns),
	fsparam_u32	("queue_depth",			Opt_queue_depth),
	fsparam_flag	("read_only",			Opt_पढ़ो_only),
	fsparam_flag	("read_write",			Opt_पढ़ो_ग_लिखो),
	fsparam_flag	("ro",				Opt_पढ़ो_only),
	fsparam_flag	("rw",				Opt_पढ़ो_ग_लिखो),
	अणुपूर्ण
पूर्ण;

काष्ठा rbd_options अणु
	पूर्णांक	queue_depth;
	पूर्णांक	alloc_size;
	अचिन्हित दीर्घ	lock_समयout;
	bool	पढ़ो_only;
	bool	lock_on_पढ़ो;
	bool	exclusive;
	bool	trim;

	u32 alloc_hपूर्णांक_flags;  /* CEPH_OSD_OP_ALLOC_HINT_FLAG_* */
पूर्ण;

#घोषणा RBD_QUEUE_DEPTH_DEFAULT	BLKDEV_MAX_RQ
#घोषणा RBD_ALLOC_SIZE_DEFAULT	(64 * 1024)
#घोषणा RBD_LOCK_TIMEOUT_DEFAULT 0  /* no समयout */
#घोषणा RBD_READ_ONLY_DEFAULT	false
#घोषणा RBD_LOCK_ON_READ_DEFAULT false
#घोषणा RBD_EXCLUSIVE_DEFAULT	false
#घोषणा RBD_TRIM_DEFAULT	true

काष्ठा rbd_parse_opts_ctx अणु
	काष्ठा rbd_spec		*spec;
	काष्ठा ceph_options	*copts;
	काष्ठा rbd_options	*opts;
पूर्ण;

अटल अक्षर* obj_op_name(क्रमागत obj_operation_type op_type)
अणु
	चयन (op_type) अणु
	हाल OBJ_OP_READ:
		वापस "read";
	हाल OBJ_OP_WRITE:
		वापस "write";
	हाल OBJ_OP_DISCARD:
		वापस "discard";
	हाल OBJ_OP_ZEROOUT:
		वापस "zeroout";
	शेष:
		वापस "???";
	पूर्ण
पूर्ण

/*
 * Destroy ceph client
 *
 * Caller must hold rbd_client_list_lock.
 */
अटल व्योम rbd_client_release(काष्ठा kref *kref)
अणु
	काष्ठा rbd_client *rbdc = container_of(kref, काष्ठा rbd_client, kref);

	करोut("%s: rbdc %p\n", __func__, rbdc);
	spin_lock(&rbd_client_list_lock);
	list_del(&rbdc->node);
	spin_unlock(&rbd_client_list_lock);

	ceph_destroy_client(rbdc->client);
	kमुक्त(rbdc);
पूर्ण

/*
 * Drop reference to ceph client node. If it's not referenced anymore, release
 * it.
 */
अटल व्योम rbd_put_client(काष्ठा rbd_client *rbdc)
अणु
	अगर (rbdc)
		kref_put(&rbdc->kref, rbd_client_release);
पूर्ण

/*
 * Get a ceph client with specअगरic addr and configuration, अगर one करोes
 * not exist create it.  Either way, ceph_opts is consumed by this
 * function.
 */
अटल काष्ठा rbd_client *rbd_get_client(काष्ठा ceph_options *ceph_opts)
अणु
	काष्ठा rbd_client *rbdc;
	पूर्णांक ret;

	mutex_lock(&client_mutex);
	rbdc = rbd_client_find(ceph_opts);
	अगर (rbdc) अणु
		ceph_destroy_options(ceph_opts);

		/*
		 * Using an existing client.  Make sure ->pg_pools is up to
		 * date beक्रमe we look up the pool id in करो_rbd_add().
		 */
		ret = ceph_रुको_क्रम_latest_osdmap(rbdc->client,
					rbdc->client->options->mount_समयout);
		अगर (ret) अणु
			rbd_warn(शून्य, "failed to get latest osdmap: %d", ret);
			rbd_put_client(rbdc);
			rbdc = ERR_PTR(ret);
		पूर्ण
	पूर्ण अन्यथा अणु
		rbdc = rbd_client_create(ceph_opts);
	पूर्ण
	mutex_unlock(&client_mutex);

	वापस rbdc;
पूर्ण

अटल bool rbd_image_क्रमmat_valid(u32 image_क्रमmat)
अणु
	वापस image_क्रमmat == 1 || image_क्रमmat == 2;
पूर्ण

अटल bool rbd_dev_ondisk_valid(काष्ठा rbd_image_header_ondisk *ondisk)
अणु
	माप_प्रकार size;
	u32 snap_count;

	/* The header has to start with the magic rbd header text */
	अगर (स_भेद(&ondisk->text, RBD_HEADER_TEXT, माप (RBD_HEADER_TEXT)))
		वापस false;

	/* The bio layer requires at least sector-sized I/O */

	अगर (ondisk->options.order < SECTOR_SHIFT)
		वापस false;

	/* If we use u64 in a few spots we may be able to loosen this */

	अगर (ondisk->options.order > 8 * माप (पूर्णांक) - 1)
		वापस false;

	/*
	 * The size of a snapshot header has to fit in a माप_प्रकार, and
	 * that limits the number of snapshots.
	 */
	snap_count = le32_to_cpu(ondisk->snap_count);
	size = SIZE_MAX - माप (काष्ठा ceph_snap_context);
	अगर (snap_count > size / माप (__le64))
		वापस false;

	/*
	 * Not only that, but the size of the entire the snapshot
	 * header must also be representable in a माप_प्रकार.
	 */
	size -= snap_count * माप (__le64);
	अगर ((u64) size < le64_to_cpu(ondisk->snap_names_len))
		वापस false;

	वापस true;
पूर्ण

/*
 * वापसs the size of an object in the image
 */
अटल u32 rbd_obj_bytes(काष्ठा rbd_image_header *header)
अणु
	वापस 1U << header->obj_order;
पूर्ण

अटल व्योम rbd_init_layout(काष्ठा rbd_device *rbd_dev)
अणु
	अगर (rbd_dev->header.stripe_unit == 0 ||
	    rbd_dev->header.stripe_count == 0) अणु
		rbd_dev->header.stripe_unit = rbd_obj_bytes(&rbd_dev->header);
		rbd_dev->header.stripe_count = 1;
	पूर्ण

	rbd_dev->layout.stripe_unit = rbd_dev->header.stripe_unit;
	rbd_dev->layout.stripe_count = rbd_dev->header.stripe_count;
	rbd_dev->layout.object_size = rbd_obj_bytes(&rbd_dev->header);
	rbd_dev->layout.pool_id = rbd_dev->header.data_pool_id == CEPH_NOPOOL ?
			  rbd_dev->spec->pool_id : rbd_dev->header.data_pool_id;
	RCU_INIT_POINTER(rbd_dev->layout.pool_ns, शून्य);
पूर्ण

/*
 * Fill an rbd image header with inक्रमmation from the given क्रमmat 1
 * on-disk header.
 */
अटल पूर्णांक rbd_header_from_disk(काष्ठा rbd_device *rbd_dev,
				 काष्ठा rbd_image_header_ondisk *ondisk)
अणु
	काष्ठा rbd_image_header *header = &rbd_dev->header;
	bool first_समय = header->object_prefix == शून्य;
	काष्ठा ceph_snap_context *snapc;
	अक्षर *object_prefix = शून्य;
	अक्षर *snap_names = शून्य;
	u64 *snap_sizes = शून्य;
	u32 snap_count;
	पूर्णांक ret = -ENOMEM;
	u32 i;

	/* Allocate this now to aव्योम having to handle failure below */

	अगर (first_समय) अणु
		object_prefix = kstrndup(ondisk->object_prefix,
					 माप(ondisk->object_prefix),
					 GFP_KERNEL);
		अगर (!object_prefix)
			वापस -ENOMEM;
	पूर्ण

	/* Allocate the snapshot context and fill it in */

	snap_count = le32_to_cpu(ondisk->snap_count);
	snapc = ceph_create_snap_context(snap_count, GFP_KERNEL);
	अगर (!snapc)
		जाओ out_err;
	snapc->seq = le64_to_cpu(ondisk->snap_seq);
	अगर (snap_count) अणु
		काष्ठा rbd_image_snap_ondisk *snaps;
		u64 snap_names_len = le64_to_cpu(ondisk->snap_names_len);

		/* We'll keep a copy of the snapshot names... */

		अगर (snap_names_len > (u64)SIZE_MAX)
			जाओ out_2big;
		snap_names = kदो_स्मृति(snap_names_len, GFP_KERNEL);
		अगर (!snap_names)
			जाओ out_err;

		/* ...as well as the array of their sizes. */
		snap_sizes = kदो_स्मृति_array(snap_count,
					   माप(*header->snap_sizes),
					   GFP_KERNEL);
		अगर (!snap_sizes)
			जाओ out_err;

		/*
		 * Copy the names, and fill in each snapshot's id
		 * and size.
		 *
		 * Note that rbd_dev_v1_header_info() guarantees the
		 * ondisk buffer we're working with has
		 * snap_names_len bytes beyond the end of the
		 * snapshot id array, this स_नकल() is safe.
		 */
		स_नकल(snap_names, &ondisk->snaps[snap_count], snap_names_len);
		snaps = ondisk->snaps;
		क्रम (i = 0; i < snap_count; i++) अणु
			snapc->snaps[i] = le64_to_cpu(snaps[i].id);
			snap_sizes[i] = le64_to_cpu(snaps[i].image_size);
		पूर्ण
	पूर्ण

	/* We won't fail any more, fill in the header */

	अगर (first_समय) अणु
		header->object_prefix = object_prefix;
		header->obj_order = ondisk->options.order;
		rbd_init_layout(rbd_dev);
	पूर्ण अन्यथा अणु
		ceph_put_snap_context(header->snapc);
		kमुक्त(header->snap_names);
		kमुक्त(header->snap_sizes);
	पूर्ण

	/* The reमुख्यing fields always get updated (when we refresh) */

	header->image_size = le64_to_cpu(ondisk->image_size);
	header->snapc = snapc;
	header->snap_names = snap_names;
	header->snap_sizes = snap_sizes;

	वापस 0;
out_2big:
	ret = -EIO;
out_err:
	kमुक्त(snap_sizes);
	kमुक्त(snap_names);
	ceph_put_snap_context(snapc);
	kमुक्त(object_prefix);

	वापस ret;
पूर्ण

अटल स्थिर अक्षर *_rbd_dev_v1_snap_name(काष्ठा rbd_device *rbd_dev, u32 which)
अणु
	स्थिर अक्षर *snap_name;

	rbd_निश्चित(which < rbd_dev->header.snapc->num_snaps);

	/* Skip over names until we find the one we are looking क्रम */

	snap_name = rbd_dev->header.snap_names;
	जबतक (which--)
		snap_name += म_माप(snap_name) + 1;

	वापस kstrdup(snap_name, GFP_KERNEL);
पूर्ण

/*
 * Snapshot id comparison function क्रम use with क्विक()/द्वा_खोज().
 * Note that result is क्रम snapshots in *descending* order.
 */
अटल पूर्णांक snapid_compare_reverse(स्थिर व्योम *s1, स्थिर व्योम *s2)
अणु
	u64 snap_id1 = *(u64 *)s1;
	u64 snap_id2 = *(u64 *)s2;

	अगर (snap_id1 < snap_id2)
		वापस 1;
	वापस snap_id1 == snap_id2 ? 0 : -1;
पूर्ण

/*
 * Search a snapshot context to see अगर the given snapshot id is
 * present.
 *
 * Returns the position of the snapshot id in the array अगर it's found,
 * or BAD_SNAP_INDEX otherwise.
 *
 * Note: The snapshot array is in kept sorted (by the osd) in
 * reverse order, highest snapshot id first.
 */
अटल u32 rbd_dev_snap_index(काष्ठा rbd_device *rbd_dev, u64 snap_id)
अणु
	काष्ठा ceph_snap_context *snapc = rbd_dev->header.snapc;
	u64 *found;

	found = द्वा_खोज(&snap_id, &snapc->snaps, snapc->num_snaps,
				माप (snap_id), snapid_compare_reverse);

	वापस found ? (u32)(found - &snapc->snaps[0]) : BAD_SNAP_INDEX;
पूर्ण

अटल स्थिर अक्षर *rbd_dev_v1_snap_name(काष्ठा rbd_device *rbd_dev,
					u64 snap_id)
अणु
	u32 which;
	स्थिर अक्षर *snap_name;

	which = rbd_dev_snap_index(rbd_dev, snap_id);
	अगर (which == BAD_SNAP_INDEX)
		वापस ERR_PTR(-ENOENT);

	snap_name = _rbd_dev_v1_snap_name(rbd_dev, which);
	वापस snap_name ? snap_name : ERR_PTR(-ENOMEM);
पूर्ण

अटल स्थिर अक्षर *rbd_snap_name(काष्ठा rbd_device *rbd_dev, u64 snap_id)
अणु
	अगर (snap_id == CEPH_NOSNAP)
		वापस RBD_SNAP_HEAD_NAME;

	rbd_निश्चित(rbd_image_क्रमmat_valid(rbd_dev->image_क्रमmat));
	अगर (rbd_dev->image_क्रमmat == 1)
		वापस rbd_dev_v1_snap_name(rbd_dev, snap_id);

	वापस rbd_dev_v2_snap_name(rbd_dev, snap_id);
पूर्ण

अटल पूर्णांक rbd_snap_size(काष्ठा rbd_device *rbd_dev, u64 snap_id,
				u64 *snap_size)
अणु
	rbd_निश्चित(rbd_image_क्रमmat_valid(rbd_dev->image_क्रमmat));
	अगर (snap_id == CEPH_NOSNAP) अणु
		*snap_size = rbd_dev->header.image_size;
	पूर्ण अन्यथा अगर (rbd_dev->image_क्रमmat == 1) अणु
		u32 which;

		which = rbd_dev_snap_index(rbd_dev, snap_id);
		अगर (which == BAD_SNAP_INDEX)
			वापस -ENOENT;

		*snap_size = rbd_dev->header.snap_sizes[which];
	पूर्ण अन्यथा अणु
		u64 size = 0;
		पूर्णांक ret;

		ret = _rbd_dev_v2_snap_size(rbd_dev, snap_id, शून्य, &size);
		अगर (ret)
			वापस ret;

		*snap_size = size;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक rbd_dev_mapping_set(काष्ठा rbd_device *rbd_dev)
अणु
	u64 snap_id = rbd_dev->spec->snap_id;
	u64 size = 0;
	पूर्णांक ret;

	ret = rbd_snap_size(rbd_dev, snap_id, &size);
	अगर (ret)
		वापस ret;

	rbd_dev->mapping.size = size;
	वापस 0;
पूर्ण

अटल व्योम rbd_dev_mapping_clear(काष्ठा rbd_device *rbd_dev)
अणु
	rbd_dev->mapping.size = 0;
पूर्ण

अटल व्योम zero_bvec(काष्ठा bio_vec *bv)
अणु
	व्योम *buf;
	अचिन्हित दीर्घ flags;

	buf = bvec_kmap_irq(bv, &flags);
	स_रखो(buf, 0, bv->bv_len);
	flush_dcache_page(bv->bv_page);
	bvec_kunmap_irq(buf, &flags);
पूर्ण

अटल व्योम zero_bios(काष्ठा ceph_bio_iter *bio_pos, u32 off, u32 bytes)
अणु
	काष्ठा ceph_bio_iter it = *bio_pos;

	ceph_bio_iter_advance(&it, off);
	ceph_bio_iter_advance_step(&it, bytes, (अणु
		zero_bvec(&bv);
	पूर्ण));
पूर्ण

अटल व्योम zero_bvecs(काष्ठा ceph_bvec_iter *bvec_pos, u32 off, u32 bytes)
अणु
	काष्ठा ceph_bvec_iter it = *bvec_pos;

	ceph_bvec_iter_advance(&it, off);
	ceph_bvec_iter_advance_step(&it, bytes, (अणु
		zero_bvec(&bv);
	पूर्ण));
पूर्ण

/*
 * Zero a range in @obj_req data buffer defined by a bio (list) or
 * (निजी) bio_vec array.
 *
 * @off is relative to the start of the data buffer.
 */
अटल व्योम rbd_obj_zero_range(काष्ठा rbd_obj_request *obj_req, u32 off,
			       u32 bytes)
अणु
	करोut("%s %p data buf %u~%u\n", __func__, obj_req, off, bytes);

	चयन (obj_req->img_request->data_type) अणु
	हाल OBJ_REQUEST_BIO:
		zero_bios(&obj_req->bio_pos, off, bytes);
		अवरोध;
	हाल OBJ_REQUEST_BVECS:
	हाल OBJ_REQUEST_OWN_BVECS:
		zero_bvecs(&obj_req->bvec_pos, off, bytes);
		अवरोध;
	शेष:
		BUG();
	पूर्ण
पूर्ण

अटल व्योम rbd_obj_request_destroy(काष्ठा kref *kref);
अटल व्योम rbd_obj_request_put(काष्ठा rbd_obj_request *obj_request)
अणु
	rbd_निश्चित(obj_request != शून्य);
	करोut("%s: obj %p (was %d)\n", __func__, obj_request,
		kref_पढ़ो(&obj_request->kref));
	kref_put(&obj_request->kref, rbd_obj_request_destroy);
पूर्ण

अटल अंतरभूत व्योम rbd_img_obj_request_add(काष्ठा rbd_img_request *img_request,
					काष्ठा rbd_obj_request *obj_request)
अणु
	rbd_निश्चित(obj_request->img_request == शून्य);

	/* Image request now owns object's original reference */
	obj_request->img_request = img_request;
	करोut("%s: img %p obj %p\n", __func__, img_request, obj_request);
पूर्ण

अटल अंतरभूत व्योम rbd_img_obj_request_del(काष्ठा rbd_img_request *img_request,
					काष्ठा rbd_obj_request *obj_request)
अणु
	करोut("%s: img %p obj %p\n", __func__, img_request, obj_request);
	list_del(&obj_request->ex.oe_item);
	rbd_निश्चित(obj_request->img_request == img_request);
	rbd_obj_request_put(obj_request);
पूर्ण

अटल व्योम rbd_osd_submit(काष्ठा ceph_osd_request *osd_req)
अणु
	काष्ठा rbd_obj_request *obj_req = osd_req->r_priv;

	करोut("%s osd_req %p for obj_req %p objno %llu %llu~%llu\n",
	     __func__, osd_req, obj_req, obj_req->ex.oe_objno,
	     obj_req->ex.oe_off, obj_req->ex.oe_len);
	ceph_osdc_start_request(osd_req->r_osdc, osd_req, false);
पूर्ण

/*
 * The शेष/initial value क्रम all image request flags is 0.  Each
 * is conditionally set to 1 at image request initialization समय
 * and currently never change thereafter.
 */
अटल व्योम img_request_layered_set(काष्ठा rbd_img_request *img_request)
अणु
	set_bit(IMG_REQ_LAYERED, &img_request->flags);
पूर्ण

अटल bool img_request_layered_test(काष्ठा rbd_img_request *img_request)
अणु
	वापस test_bit(IMG_REQ_LAYERED, &img_request->flags) != 0;
पूर्ण

अटल bool rbd_obj_is_entire(काष्ठा rbd_obj_request *obj_req)
अणु
	काष्ठा rbd_device *rbd_dev = obj_req->img_request->rbd_dev;

	वापस !obj_req->ex.oe_off &&
	       obj_req->ex.oe_len == rbd_dev->layout.object_size;
पूर्ण

अटल bool rbd_obj_is_tail(काष्ठा rbd_obj_request *obj_req)
अणु
	काष्ठा rbd_device *rbd_dev = obj_req->img_request->rbd_dev;

	वापस obj_req->ex.oe_off + obj_req->ex.oe_len ==
					rbd_dev->layout.object_size;
पूर्ण

/*
 * Must be called after rbd_obj_calc_img_extents().
 */
अटल bool rbd_obj_copyup_enabled(काष्ठा rbd_obj_request *obj_req)
अणु
	अगर (!obj_req->num_img_extents ||
	    (rbd_obj_is_entire(obj_req) &&
	     !obj_req->img_request->snapc->num_snaps))
		वापस false;

	वापस true;
पूर्ण

अटल u64 rbd_obj_img_extents_bytes(काष्ठा rbd_obj_request *obj_req)
अणु
	वापस ceph_file_extents_bytes(obj_req->img_extents,
				       obj_req->num_img_extents);
पूर्ण

अटल bool rbd_img_is_ग_लिखो(काष्ठा rbd_img_request *img_req)
अणु
	चयन (img_req->op_type) अणु
	हाल OBJ_OP_READ:
		वापस false;
	हाल OBJ_OP_WRITE:
	हाल OBJ_OP_DISCARD:
	हाल OBJ_OP_ZEROOUT:
		वापस true;
	शेष:
		BUG();
	पूर्ण
पूर्ण

अटल व्योम rbd_osd_req_callback(काष्ठा ceph_osd_request *osd_req)
अणु
	काष्ठा rbd_obj_request *obj_req = osd_req->r_priv;
	पूर्णांक result;

	करोut("%s osd_req %p result %d for obj_req %p\n", __func__, osd_req,
	     osd_req->r_result, obj_req);

	/*
	 * Writes aren't allowed to वापस a data payload.  In some
	 * guarded ग_लिखो हालs (e.g. stat + zero on an empty object)
	 * a stat response makes it through, but we करोn't care.
	 */
	अगर (osd_req->r_result > 0 && rbd_img_is_ग_लिखो(obj_req->img_request))
		result = 0;
	अन्यथा
		result = osd_req->r_result;

	rbd_obj_handle_request(obj_req, result);
पूर्ण

अटल व्योम rbd_osd_क्रमmat_पढ़ो(काष्ठा ceph_osd_request *osd_req)
अणु
	काष्ठा rbd_obj_request *obj_request = osd_req->r_priv;
	काष्ठा rbd_device *rbd_dev = obj_request->img_request->rbd_dev;
	काष्ठा ceph_options *opt = rbd_dev->rbd_client->client->options;

	osd_req->r_flags = CEPH_OSD_FLAG_READ | opt->पढ़ो_from_replica;
	osd_req->r_snapid = obj_request->img_request->snap_id;
पूर्ण

अटल व्योम rbd_osd_क्रमmat_ग_लिखो(काष्ठा ceph_osd_request *osd_req)
अणु
	काष्ठा rbd_obj_request *obj_request = osd_req->r_priv;

	osd_req->r_flags = CEPH_OSD_FLAG_WRITE;
	kसमय_get_real_ts64(&osd_req->r_mसमय);
	osd_req->r_data_offset = obj_request->ex.oe_off;
पूर्ण

अटल काष्ठा ceph_osd_request *
__rbd_obj_add_osd_request(काष्ठा rbd_obj_request *obj_req,
			  काष्ठा ceph_snap_context *snapc, पूर्णांक num_ops)
अणु
	काष्ठा rbd_device *rbd_dev = obj_req->img_request->rbd_dev;
	काष्ठा ceph_osd_client *osdc = &rbd_dev->rbd_client->client->osdc;
	काष्ठा ceph_osd_request *req;
	स्थिर अक्षर *name_क्रमmat = rbd_dev->image_क्रमmat == 1 ?
				      RBD_V1_DATA_FORMAT : RBD_V2_DATA_FORMAT;
	पूर्णांक ret;

	req = ceph_osdc_alloc_request(osdc, snapc, num_ops, false, GFP_NOIO);
	अगर (!req)
		वापस ERR_PTR(-ENOMEM);

	list_add_tail(&req->r_निजी_item, &obj_req->osd_reqs);
	req->r_callback = rbd_osd_req_callback;
	req->r_priv = obj_req;

	/*
	 * Data objects may be stored in a separate pool, but always in
	 * the same namespace in that pool as the header in its pool.
	 */
	ceph_oloc_copy(&req->r_base_oloc, &rbd_dev->header_oloc);
	req->r_base_oloc.pool = rbd_dev->layout.pool_id;

	ret = ceph_oid_aम_लिखो(&req->r_base_oid, GFP_NOIO, name_क्रमmat,
			       rbd_dev->header.object_prefix,
			       obj_req->ex.oe_objno);
	अगर (ret)
		वापस ERR_PTR(ret);

	वापस req;
पूर्ण

अटल काष्ठा ceph_osd_request *
rbd_obj_add_osd_request(काष्ठा rbd_obj_request *obj_req, पूर्णांक num_ops)
अणु
	वापस __rbd_obj_add_osd_request(obj_req, obj_req->img_request->snapc,
					 num_ops);
पूर्ण

अटल काष्ठा rbd_obj_request *rbd_obj_request_create(व्योम)
अणु
	काष्ठा rbd_obj_request *obj_request;

	obj_request = kmem_cache_zalloc(rbd_obj_request_cache, GFP_NOIO);
	अगर (!obj_request)
		वापस शून्य;

	ceph_object_extent_init(&obj_request->ex);
	INIT_LIST_HEAD(&obj_request->osd_reqs);
	mutex_init(&obj_request->state_mutex);
	kref_init(&obj_request->kref);

	करोut("%s %p\n", __func__, obj_request);
	वापस obj_request;
पूर्ण

अटल व्योम rbd_obj_request_destroy(काष्ठा kref *kref)
अणु
	काष्ठा rbd_obj_request *obj_request;
	काष्ठा ceph_osd_request *osd_req;
	u32 i;

	obj_request = container_of(kref, काष्ठा rbd_obj_request, kref);

	करोut("%s: obj %p\n", __func__, obj_request);

	जबतक (!list_empty(&obj_request->osd_reqs)) अणु
		osd_req = list_first_entry(&obj_request->osd_reqs,
				    काष्ठा ceph_osd_request, r_निजी_item);
		list_del_init(&osd_req->r_निजी_item);
		ceph_osdc_put_request(osd_req);
	पूर्ण

	चयन (obj_request->img_request->data_type) अणु
	हाल OBJ_REQUEST_NODATA:
	हाल OBJ_REQUEST_BIO:
	हाल OBJ_REQUEST_BVECS:
		अवरोध;		/* Nothing to करो */
	हाल OBJ_REQUEST_OWN_BVECS:
		kमुक्त(obj_request->bvec_pos.bvecs);
		अवरोध;
	शेष:
		BUG();
	पूर्ण

	kमुक्त(obj_request->img_extents);
	अगर (obj_request->copyup_bvecs) अणु
		क्रम (i = 0; i < obj_request->copyup_bvec_count; i++) अणु
			अगर (obj_request->copyup_bvecs[i].bv_page)
				__मुक्त_page(obj_request->copyup_bvecs[i].bv_page);
		पूर्ण
		kमुक्त(obj_request->copyup_bvecs);
	पूर्ण

	kmem_cache_मुक्त(rbd_obj_request_cache, obj_request);
पूर्ण

/* It's OK to call this क्रम a device with no parent */

अटल व्योम rbd_spec_put(काष्ठा rbd_spec *spec);
अटल व्योम rbd_dev_unparent(काष्ठा rbd_device *rbd_dev)
अणु
	rbd_dev_हटाओ_parent(rbd_dev);
	rbd_spec_put(rbd_dev->parent_spec);
	rbd_dev->parent_spec = शून्य;
	rbd_dev->parent_overlap = 0;
पूर्ण

/*
 * Parent image reference counting is used to determine when an
 * image's parent fields can be safely torn करोwn--after there are no
 * more in-flight requests to the parent image.  When the last
 * reference is dropped, cleaning them up is safe.
 */
अटल व्योम rbd_dev_parent_put(काष्ठा rbd_device *rbd_dev)
अणु
	पूर्णांक counter;

	अगर (!rbd_dev->parent_spec)
		वापस;

	counter = atomic_dec_वापस_safe(&rbd_dev->parent_ref);
	अगर (counter > 0)
		वापस;

	/* Last reference; clean up parent data काष्ठाures */

	अगर (!counter)
		rbd_dev_unparent(rbd_dev);
	अन्यथा
		rbd_warn(rbd_dev, "parent reference underflow");
पूर्ण

/*
 * If an image has a non-zero parent overlap, get a reference to its
 * parent.
 *
 * Returns true अगर the rbd device has a parent with a non-zero
 * overlap and a reference क्रम it was successfully taken, or
 * false otherwise.
 */
अटल bool rbd_dev_parent_get(काष्ठा rbd_device *rbd_dev)
अणु
	पूर्णांक counter = 0;

	अगर (!rbd_dev->parent_spec)
		वापस false;

	अगर (rbd_dev->parent_overlap)
		counter = atomic_inc_वापस_safe(&rbd_dev->parent_ref);

	अगर (counter < 0)
		rbd_warn(rbd_dev, "parent reference overflow");

	वापस counter > 0;
पूर्ण

अटल व्योम rbd_img_request_init(काष्ठा rbd_img_request *img_request,
				 काष्ठा rbd_device *rbd_dev,
				 क्रमागत obj_operation_type op_type)
अणु
	स_रखो(img_request, 0, माप(*img_request));

	img_request->rbd_dev = rbd_dev;
	img_request->op_type = op_type;

	INIT_LIST_HEAD(&img_request->lock_item);
	INIT_LIST_HEAD(&img_request->object_extents);
	mutex_init(&img_request->state_mutex);
पूर्ण

अटल व्योम rbd_img_capture_header(काष्ठा rbd_img_request *img_req)
अणु
	काष्ठा rbd_device *rbd_dev = img_req->rbd_dev;

	lockdep_निश्चित_held(&rbd_dev->header_rwsem);

	अगर (rbd_img_is_ग_लिखो(img_req))
		img_req->snapc = ceph_get_snap_context(rbd_dev->header.snapc);
	अन्यथा
		img_req->snap_id = rbd_dev->spec->snap_id;

	अगर (rbd_dev_parent_get(rbd_dev))
		img_request_layered_set(img_req);
पूर्ण

अटल व्योम rbd_img_request_destroy(काष्ठा rbd_img_request *img_request)
अणु
	काष्ठा rbd_obj_request *obj_request;
	काष्ठा rbd_obj_request *next_obj_request;

	करोut("%s: img %p\n", __func__, img_request);

	WARN_ON(!list_empty(&img_request->lock_item));
	क्रम_each_obj_request_safe(img_request, obj_request, next_obj_request)
		rbd_img_obj_request_del(img_request, obj_request);

	अगर (img_request_layered_test(img_request))
		rbd_dev_parent_put(img_request->rbd_dev);

	अगर (rbd_img_is_ग_लिखो(img_request))
		ceph_put_snap_context(img_request->snapc);

	अगर (test_bit(IMG_REQ_CHILD, &img_request->flags))
		kmem_cache_मुक्त(rbd_img_request_cache, img_request);
पूर्ण

#घोषणा BITS_PER_OBJ	2
#घोषणा OBJS_PER_BYTE	(BITS_PER_BYTE / BITS_PER_OBJ)
#घोषणा OBJ_MASK	((1 << BITS_PER_OBJ) - 1)

अटल व्योम __rbd_object_map_index(काष्ठा rbd_device *rbd_dev, u64 objno,
				   u64 *index, u8 *shअगरt)
अणु
	u32 off;

	rbd_निश्चित(objno < rbd_dev->object_map_size);
	*index = भाग_u64_rem(objno, OBJS_PER_BYTE, &off);
	*shअगरt = (OBJS_PER_BYTE - off - 1) * BITS_PER_OBJ;
पूर्ण

अटल u8 __rbd_object_map_get(काष्ठा rbd_device *rbd_dev, u64 objno)
अणु
	u64 index;
	u8 shअगरt;

	lockdep_निश्चित_held(&rbd_dev->object_map_lock);
	__rbd_object_map_index(rbd_dev, objno, &index, &shअगरt);
	वापस (rbd_dev->object_map[index] >> shअगरt) & OBJ_MASK;
पूर्ण

अटल व्योम __rbd_object_map_set(काष्ठा rbd_device *rbd_dev, u64 objno, u8 val)
अणु
	u64 index;
	u8 shअगरt;
	u8 *p;

	lockdep_निश्चित_held(&rbd_dev->object_map_lock);
	rbd_निश्चित(!(val & ~OBJ_MASK));

	__rbd_object_map_index(rbd_dev, objno, &index, &shअगरt);
	p = &rbd_dev->object_map[index];
	*p = (*p & ~(OBJ_MASK << shअगरt)) | (val << shअगरt);
पूर्ण

अटल u8 rbd_object_map_get(काष्ठा rbd_device *rbd_dev, u64 objno)
अणु
	u8 state;

	spin_lock(&rbd_dev->object_map_lock);
	state = __rbd_object_map_get(rbd_dev, objno);
	spin_unlock(&rbd_dev->object_map_lock);
	वापस state;
पूर्ण

अटल bool use_object_map(काष्ठा rbd_device *rbd_dev)
अणु
	/*
	 * An image mapped पढ़ो-only can't use the object map -- it isn't
	 * loaded because the header lock isn't acquired.  Someone अन्यथा can
	 * ग_लिखो to the image and update the object map behind our back.
	 *
	 * A snapshot can't be written to, so using the object map is always
	 * safe.
	 */
	अगर (!rbd_is_snap(rbd_dev) && rbd_is_ro(rbd_dev))
		वापस false;

	वापस ((rbd_dev->header.features & RBD_FEATURE_OBJECT_MAP) &&
		!(rbd_dev->object_map_flags & RBD_FLAG_OBJECT_MAP_INVALID));
पूर्ण

अटल bool rbd_object_map_may_exist(काष्ठा rbd_device *rbd_dev, u64 objno)
अणु
	u8 state;

	/* fall back to शेष logic अगर object map is disabled or invalid */
	अगर (!use_object_map(rbd_dev))
		वापस true;

	state = rbd_object_map_get(rbd_dev, objno);
	वापस state != OBJECT_NONEXISTENT;
पूर्ण

अटल व्योम rbd_object_map_name(काष्ठा rbd_device *rbd_dev, u64 snap_id,
				काष्ठा ceph_object_id *oid)
अणु
	अगर (snap_id == CEPH_NOSNAP)
		ceph_oid_म_लिखो(oid, "%s%s", RBD_OBJECT_MAP_PREFIX,
				rbd_dev->spec->image_id);
	अन्यथा
		ceph_oid_म_लिखो(oid, "%s%s.%016llx", RBD_OBJECT_MAP_PREFIX,
				rbd_dev->spec->image_id, snap_id);
पूर्ण

अटल पूर्णांक rbd_object_map_lock(काष्ठा rbd_device *rbd_dev)
अणु
	काष्ठा ceph_osd_client *osdc = &rbd_dev->rbd_client->client->osdc;
	CEPH_DEFINE_OID_ONSTACK(oid);
	u8 lock_type;
	अक्षर *lock_tag;
	काष्ठा ceph_locker *lockers;
	u32 num_lockers;
	bool broke_lock = false;
	पूर्णांक ret;

	rbd_object_map_name(rbd_dev, CEPH_NOSNAP, &oid);

again:
	ret = ceph_cls_lock(osdc, &oid, &rbd_dev->header_oloc, RBD_LOCK_NAME,
			    CEPH_CLS_LOCK_EXCLUSIVE, "", "", "", 0);
	अगर (ret != -EBUSY || broke_lock) अणु
		अगर (ret == -EEXIST)
			ret = 0; /* alपढ़ोy locked by myself */
		अगर (ret)
			rbd_warn(rbd_dev, "failed to lock object map: %d", ret);
		वापस ret;
	पूर्ण

	ret = ceph_cls_lock_info(osdc, &oid, &rbd_dev->header_oloc,
				 RBD_LOCK_NAME, &lock_type, &lock_tag,
				 &lockers, &num_lockers);
	अगर (ret) अणु
		अगर (ret == -ENOENT)
			जाओ again;

		rbd_warn(rbd_dev, "failed to get object map lockers: %d", ret);
		वापस ret;
	पूर्ण

	kमुक्त(lock_tag);
	अगर (num_lockers == 0)
		जाओ again;

	rbd_warn(rbd_dev, "breaking object map lock owned by %s%llu",
		 ENTITY_NAME(lockers[0].id.name));

	ret = ceph_cls_अवरोध_lock(osdc, &oid, &rbd_dev->header_oloc,
				  RBD_LOCK_NAME, lockers[0].id.cookie,
				  &lockers[0].id.name);
	ceph_मुक्त_lockers(lockers, num_lockers);
	अगर (ret) अणु
		अगर (ret == -ENOENT)
			जाओ again;

		rbd_warn(rbd_dev, "failed to break object map lock: %d", ret);
		वापस ret;
	पूर्ण

	broke_lock = true;
	जाओ again;
पूर्ण

अटल व्योम rbd_object_map_unlock(काष्ठा rbd_device *rbd_dev)
अणु
	काष्ठा ceph_osd_client *osdc = &rbd_dev->rbd_client->client->osdc;
	CEPH_DEFINE_OID_ONSTACK(oid);
	पूर्णांक ret;

	rbd_object_map_name(rbd_dev, CEPH_NOSNAP, &oid);

	ret = ceph_cls_unlock(osdc, &oid, &rbd_dev->header_oloc, RBD_LOCK_NAME,
			      "");
	अगर (ret && ret != -ENOENT)
		rbd_warn(rbd_dev, "failed to unlock object map: %d", ret);
पूर्ण

अटल पूर्णांक decode_object_map_header(व्योम **p, व्योम *end, u64 *object_map_size)
अणु
	u8 काष्ठा_v;
	u32 काष्ठा_len;
	u32 header_len;
	व्योम *header_end;
	पूर्णांक ret;

	ceph_decode_32_safe(p, end, header_len, e_inval);
	header_end = *p + header_len;

	ret = ceph_start_decoding(p, end, 1, "BitVector header", &काष्ठा_v,
				  &काष्ठा_len);
	अगर (ret)
		वापस ret;

	ceph_decode_64_safe(p, end, *object_map_size, e_inval);

	*p = header_end;
	वापस 0;

e_inval:
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक __rbd_object_map_load(काष्ठा rbd_device *rbd_dev)
अणु
	काष्ठा ceph_osd_client *osdc = &rbd_dev->rbd_client->client->osdc;
	CEPH_DEFINE_OID_ONSTACK(oid);
	काष्ठा page **pages;
	व्योम *p, *end;
	माप_प्रकार reply_len;
	u64 num_objects;
	u64 object_map_bytes;
	u64 object_map_size;
	पूर्णांक num_pages;
	पूर्णांक ret;

	rbd_निश्चित(!rbd_dev->object_map && !rbd_dev->object_map_size);

	num_objects = ceph_get_num_objects(&rbd_dev->layout,
					   rbd_dev->mapping.size);
	object_map_bytes = DIV_ROUND_UP_ULL(num_objects * BITS_PER_OBJ,
					    BITS_PER_BYTE);
	num_pages = calc_pages_क्रम(0, object_map_bytes) + 1;
	pages = ceph_alloc_page_vector(num_pages, GFP_KERNEL);
	अगर (IS_ERR(pages))
		वापस PTR_ERR(pages);

	reply_len = num_pages * PAGE_SIZE;
	rbd_object_map_name(rbd_dev, rbd_dev->spec->snap_id, &oid);
	ret = ceph_osdc_call(osdc, &oid, &rbd_dev->header_oloc,
			     "rbd", "object_map_load", CEPH_OSD_FLAG_READ,
			     शून्य, 0, pages, &reply_len);
	अगर (ret)
		जाओ out;

	p = page_address(pages[0]);
	end = p + min(reply_len, (माप_प्रकार)PAGE_SIZE);
	ret = decode_object_map_header(&p, end, &object_map_size);
	अगर (ret)
		जाओ out;

	अगर (object_map_size != num_objects) अणु
		rbd_warn(rbd_dev, "object map size mismatch: %llu vs %llu",
			 object_map_size, num_objects);
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	अगर (offset_in_page(p) + object_map_bytes > reply_len) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	rbd_dev->object_map = kvदो_स्मृति(object_map_bytes, GFP_KERNEL);
	अगर (!rbd_dev->object_map) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	rbd_dev->object_map_size = object_map_size;
	ceph_copy_from_page_vector(pages, rbd_dev->object_map,
				   offset_in_page(p), object_map_bytes);

out:
	ceph_release_page_vector(pages, num_pages);
	वापस ret;
पूर्ण

अटल व्योम rbd_object_map_मुक्त(काष्ठा rbd_device *rbd_dev)
अणु
	kvमुक्त(rbd_dev->object_map);
	rbd_dev->object_map = शून्य;
	rbd_dev->object_map_size = 0;
पूर्ण

अटल पूर्णांक rbd_object_map_load(काष्ठा rbd_device *rbd_dev)
अणु
	पूर्णांक ret;

	ret = __rbd_object_map_load(rbd_dev);
	अगर (ret)
		वापस ret;

	ret = rbd_dev_v2_get_flags(rbd_dev);
	अगर (ret) अणु
		rbd_object_map_मुक्त(rbd_dev);
		वापस ret;
	पूर्ण

	अगर (rbd_dev->object_map_flags & RBD_FLAG_OBJECT_MAP_INVALID)
		rbd_warn(rbd_dev, "object map is invalid");

	वापस 0;
पूर्ण

अटल पूर्णांक rbd_object_map_खोलो(काष्ठा rbd_device *rbd_dev)
अणु
	पूर्णांक ret;

	ret = rbd_object_map_lock(rbd_dev);
	अगर (ret)
		वापस ret;

	ret = rbd_object_map_load(rbd_dev);
	अगर (ret) अणु
		rbd_object_map_unlock(rbd_dev);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम rbd_object_map_बंद(काष्ठा rbd_device *rbd_dev)
अणु
	rbd_object_map_मुक्त(rbd_dev);
	rbd_object_map_unlock(rbd_dev);
पूर्ण

/*
 * This function needs snap_id (or more precisely just something to
 * distinguish between HEAD and snapshot object maps), new_state and
 * current_state that were passed to rbd_object_map_update().
 *
 * To aव्योम allocating and stashing a context we piggyback on the OSD
 * request.  A HEAD update has two ops (निश्चित_locked).  For new_state
 * and current_state we decode our own object_map_update op, encoded in
 * rbd_cls_object_map_update().
 */
अटल पूर्णांक rbd_object_map_update_finish(काष्ठा rbd_obj_request *obj_req,
					काष्ठा ceph_osd_request *osd_req)
अणु
	काष्ठा rbd_device *rbd_dev = obj_req->img_request->rbd_dev;
	काष्ठा ceph_osd_data *osd_data;
	u64 objno;
	u8 state, new_state, current_state;
	bool has_current_state;
	व्योम *p;

	अगर (osd_req->r_result)
		वापस osd_req->r_result;

	/*
	 * Nothing to करो क्रम a snapshot object map.
	 */
	अगर (osd_req->r_num_ops == 1)
		वापस 0;

	/*
	 * Update in-memory HEAD object map.
	 */
	rbd_निश्चित(osd_req->r_num_ops == 2);
	osd_data = osd_req_op_data(osd_req, 1, cls, request_data);
	rbd_निश्चित(osd_data->type == CEPH_OSD_DATA_TYPE_PAGES);

	p = page_address(osd_data->pages[0]);
	objno = ceph_decode_64(&p);
	rbd_निश्चित(objno == obj_req->ex.oe_objno);
	rbd_निश्चित(ceph_decode_64(&p) == objno + 1);
	new_state = ceph_decode_8(&p);
	has_current_state = ceph_decode_8(&p);
	अगर (has_current_state)
		current_state = ceph_decode_8(&p);

	spin_lock(&rbd_dev->object_map_lock);
	state = __rbd_object_map_get(rbd_dev, objno);
	अगर (!has_current_state || current_state == state ||
	    (current_state == OBJECT_EXISTS && state == OBJECT_EXISTS_CLEAN))
		__rbd_object_map_set(rbd_dev, objno, new_state);
	spin_unlock(&rbd_dev->object_map_lock);

	वापस 0;
पूर्ण

अटल व्योम rbd_object_map_callback(काष्ठा ceph_osd_request *osd_req)
अणु
	काष्ठा rbd_obj_request *obj_req = osd_req->r_priv;
	पूर्णांक result;

	करोut("%s osd_req %p result %d for obj_req %p\n", __func__, osd_req,
	     osd_req->r_result, obj_req);

	result = rbd_object_map_update_finish(obj_req, osd_req);
	rbd_obj_handle_request(obj_req, result);
पूर्ण

अटल bool update_needed(काष्ठा rbd_device *rbd_dev, u64 objno, u8 new_state)
अणु
	u8 state = rbd_object_map_get(rbd_dev, objno);

	अगर (state == new_state ||
	    (new_state == OBJECT_PENDING && state == OBJECT_NONEXISTENT) ||
	    (new_state == OBJECT_NONEXISTENT && state != OBJECT_PENDING))
		वापस false;

	वापस true;
पूर्ण

अटल पूर्णांक rbd_cls_object_map_update(काष्ठा ceph_osd_request *req,
				     पूर्णांक which, u64 objno, u8 new_state,
				     स्थिर u8 *current_state)
अणु
	काष्ठा page **pages;
	व्योम *p, *start;
	पूर्णांक ret;

	ret = osd_req_op_cls_init(req, which, "rbd", "object_map_update");
	अगर (ret)
		वापस ret;

	pages = ceph_alloc_page_vector(1, GFP_NOIO);
	अगर (IS_ERR(pages))
		वापस PTR_ERR(pages);

	p = start = page_address(pages[0]);
	ceph_encode_64(&p, objno);
	ceph_encode_64(&p, objno + 1);
	ceph_encode_8(&p, new_state);
	अगर (current_state) अणु
		ceph_encode_8(&p, 1);
		ceph_encode_8(&p, *current_state);
	पूर्ण अन्यथा अणु
		ceph_encode_8(&p, 0);
	पूर्ण

	osd_req_op_cls_request_data_pages(req, which, pages, p - start, 0,
					  false, true);
	वापस 0;
पूर्ण

/*
 * Return:
 *   0 - object map update sent
 *   1 - object map update isn't needed
 *  <0 - error
 */
अटल पूर्णांक rbd_object_map_update(काष्ठा rbd_obj_request *obj_req, u64 snap_id,
				 u8 new_state, स्थिर u8 *current_state)
अणु
	काष्ठा rbd_device *rbd_dev = obj_req->img_request->rbd_dev;
	काष्ठा ceph_osd_client *osdc = &rbd_dev->rbd_client->client->osdc;
	काष्ठा ceph_osd_request *req;
	पूर्णांक num_ops = 1;
	पूर्णांक which = 0;
	पूर्णांक ret;

	अगर (snap_id == CEPH_NOSNAP) अणु
		अगर (!update_needed(rbd_dev, obj_req->ex.oe_objno, new_state))
			वापस 1;

		num_ops++; /* निश्चित_locked */
	पूर्ण

	req = ceph_osdc_alloc_request(osdc, शून्य, num_ops, false, GFP_NOIO);
	अगर (!req)
		वापस -ENOMEM;

	list_add_tail(&req->r_निजी_item, &obj_req->osd_reqs);
	req->r_callback = rbd_object_map_callback;
	req->r_priv = obj_req;

	rbd_object_map_name(rbd_dev, snap_id, &req->r_base_oid);
	ceph_oloc_copy(&req->r_base_oloc, &rbd_dev->header_oloc);
	req->r_flags = CEPH_OSD_FLAG_WRITE;
	kसमय_get_real_ts64(&req->r_mसमय);

	अगर (snap_id == CEPH_NOSNAP) अणु
		/*
		 * Protect against possible race conditions during lock
		 * ownership transitions.
		 */
		ret = ceph_cls_निश्चित_locked(req, which++, RBD_LOCK_NAME,
					     CEPH_CLS_LOCK_EXCLUSIVE, "", "");
		अगर (ret)
			वापस ret;
	पूर्ण

	ret = rbd_cls_object_map_update(req, which, obj_req->ex.oe_objno,
					new_state, current_state);
	अगर (ret)
		वापस ret;

	ret = ceph_osdc_alloc_messages(req, GFP_NOIO);
	अगर (ret)
		वापस ret;

	ceph_osdc_start_request(osdc, req, false);
	वापस 0;
पूर्ण

अटल व्योम prune_extents(काष्ठा ceph_file_extent *img_extents,
			  u32 *num_img_extents, u64 overlap)
अणु
	u32 cnt = *num_img_extents;

	/* drop extents completely beyond the overlap */
	जबतक (cnt && img_extents[cnt - 1].fe_off >= overlap)
		cnt--;

	अगर (cnt) अणु
		काष्ठा ceph_file_extent *ex = &img_extents[cnt - 1];

		/* trim final overlapping extent */
		अगर (ex->fe_off + ex->fe_len > overlap)
			ex->fe_len = overlap - ex->fe_off;
	पूर्ण

	*num_img_extents = cnt;
पूर्ण

/*
 * Determine the byte range(s) covered by either just the object extent
 * or the entire object in the parent image.
 */
अटल पूर्णांक rbd_obj_calc_img_extents(काष्ठा rbd_obj_request *obj_req,
				    bool entire)
अणु
	काष्ठा rbd_device *rbd_dev = obj_req->img_request->rbd_dev;
	पूर्णांक ret;

	अगर (!rbd_dev->parent_overlap)
		वापस 0;

	ret = ceph_extent_to_file(&rbd_dev->layout, obj_req->ex.oe_objno,
				  entire ? 0 : obj_req->ex.oe_off,
				  entire ? rbd_dev->layout.object_size :
							obj_req->ex.oe_len,
				  &obj_req->img_extents,
				  &obj_req->num_img_extents);
	अगर (ret)
		वापस ret;

	prune_extents(obj_req->img_extents, &obj_req->num_img_extents,
		      rbd_dev->parent_overlap);
	वापस 0;
पूर्ण

अटल व्योम rbd_osd_setup_data(काष्ठा ceph_osd_request *osd_req, पूर्णांक which)
अणु
	काष्ठा rbd_obj_request *obj_req = osd_req->r_priv;

	चयन (obj_req->img_request->data_type) अणु
	हाल OBJ_REQUEST_BIO:
		osd_req_op_extent_osd_data_bio(osd_req, which,
					       &obj_req->bio_pos,
					       obj_req->ex.oe_len);
		अवरोध;
	हाल OBJ_REQUEST_BVECS:
	हाल OBJ_REQUEST_OWN_BVECS:
		rbd_निश्चित(obj_req->bvec_pos.iter.bi_size ==
							obj_req->ex.oe_len);
		rbd_निश्चित(obj_req->bvec_idx == obj_req->bvec_count);
		osd_req_op_extent_osd_data_bvec_pos(osd_req, which,
						    &obj_req->bvec_pos);
		अवरोध;
	शेष:
		BUG();
	पूर्ण
पूर्ण

अटल पूर्णांक rbd_osd_setup_stat(काष्ठा ceph_osd_request *osd_req, पूर्णांक which)
अणु
	काष्ठा page **pages;

	/*
	 * The response data क्रम a STAT call consists of:
	 *     le64 length;
	 *     काष्ठा अणु
	 *         le32 tv_sec;
	 *         le32 tv_nsec;
	 *     पूर्ण mसमय;
	 */
	pages = ceph_alloc_page_vector(1, GFP_NOIO);
	अगर (IS_ERR(pages))
		वापस PTR_ERR(pages);

	osd_req_op_init(osd_req, which, CEPH_OSD_OP_STAT, 0);
	osd_req_op_raw_data_in_pages(osd_req, which, pages,
				     8 + माप(काष्ठा ceph_बारpec),
				     0, false, true);
	वापस 0;
पूर्ण

अटल पूर्णांक rbd_osd_setup_copyup(काष्ठा ceph_osd_request *osd_req, पूर्णांक which,
				u32 bytes)
अणु
	काष्ठा rbd_obj_request *obj_req = osd_req->r_priv;
	पूर्णांक ret;

	ret = osd_req_op_cls_init(osd_req, which, "rbd", "copyup");
	अगर (ret)
		वापस ret;

	osd_req_op_cls_request_data_bvecs(osd_req, which, obj_req->copyup_bvecs,
					  obj_req->copyup_bvec_count, bytes);
	वापस 0;
पूर्ण

अटल पूर्णांक rbd_obj_init_पढ़ो(काष्ठा rbd_obj_request *obj_req)
अणु
	obj_req->पढ़ो_state = RBD_OBJ_READ_START;
	वापस 0;
पूर्ण

अटल व्योम __rbd_osd_setup_ग_लिखो_ops(काष्ठा ceph_osd_request *osd_req,
				      पूर्णांक which)
अणु
	काष्ठा rbd_obj_request *obj_req = osd_req->r_priv;
	काष्ठा rbd_device *rbd_dev = obj_req->img_request->rbd_dev;
	u16 opcode;

	अगर (!use_object_map(rbd_dev) ||
	    !(obj_req->flags & RBD_OBJ_FLAG_MAY_EXIST)) अणु
		osd_req_op_alloc_hपूर्णांक_init(osd_req, which++,
					   rbd_dev->layout.object_size,
					   rbd_dev->layout.object_size,
					   rbd_dev->opts->alloc_hपूर्णांक_flags);
	पूर्ण

	अगर (rbd_obj_is_entire(obj_req))
		opcode = CEPH_OSD_OP_WRITEFULL;
	अन्यथा
		opcode = CEPH_OSD_OP_WRITE;

	osd_req_op_extent_init(osd_req, which, opcode,
			       obj_req->ex.oe_off, obj_req->ex.oe_len, 0, 0);
	rbd_osd_setup_data(osd_req, which);
पूर्ण

अटल पूर्णांक rbd_obj_init_ग_लिखो(काष्ठा rbd_obj_request *obj_req)
अणु
	पूर्णांक ret;

	/* reverse map the entire object onto the parent */
	ret = rbd_obj_calc_img_extents(obj_req, true);
	अगर (ret)
		वापस ret;

	अगर (rbd_obj_copyup_enabled(obj_req))
		obj_req->flags |= RBD_OBJ_FLAG_COPYUP_ENABLED;

	obj_req->ग_लिखो_state = RBD_OBJ_WRITE_START;
	वापस 0;
पूर्ण

अटल u16 truncate_or_zero_opcode(काष्ठा rbd_obj_request *obj_req)
अणु
	वापस rbd_obj_is_tail(obj_req) ? CEPH_OSD_OP_TRUNCATE :
					  CEPH_OSD_OP_ZERO;
पूर्ण

अटल व्योम __rbd_osd_setup_discard_ops(काष्ठा ceph_osd_request *osd_req,
					पूर्णांक which)
अणु
	काष्ठा rbd_obj_request *obj_req = osd_req->r_priv;

	अगर (rbd_obj_is_entire(obj_req) && !obj_req->num_img_extents) अणु
		rbd_निश्चित(obj_req->flags & RBD_OBJ_FLAG_DELETION);
		osd_req_op_init(osd_req, which, CEPH_OSD_OP_DELETE, 0);
	पूर्ण अन्यथा अणु
		osd_req_op_extent_init(osd_req, which,
				       truncate_or_zero_opcode(obj_req),
				       obj_req->ex.oe_off, obj_req->ex.oe_len,
				       0, 0);
	पूर्ण
पूर्ण

अटल पूर्णांक rbd_obj_init_discard(काष्ठा rbd_obj_request *obj_req)
अणु
	काष्ठा rbd_device *rbd_dev = obj_req->img_request->rbd_dev;
	u64 off, next_off;
	पूर्णांक ret;

	/*
	 * Align the range to alloc_size boundary and punt on discards
	 * that are too small to मुक्त up any space.
	 *
	 * alloc_size == object_size && is_tail() is a special हाल क्रम
	 * filestore with filestore_punch_hole = false, needed to allow
	 * truncate (in addition to delete).
	 */
	अगर (rbd_dev->opts->alloc_size != rbd_dev->layout.object_size ||
	    !rbd_obj_is_tail(obj_req)) अणु
		off = round_up(obj_req->ex.oe_off, rbd_dev->opts->alloc_size);
		next_off = round_करोwn(obj_req->ex.oe_off + obj_req->ex.oe_len,
				      rbd_dev->opts->alloc_size);
		अगर (off >= next_off)
			वापस 1;

		करोut("%s %p %llu~%llu -> %llu~%llu\n", __func__,
		     obj_req, obj_req->ex.oe_off, obj_req->ex.oe_len,
		     off, next_off - off);
		obj_req->ex.oe_off = off;
		obj_req->ex.oe_len = next_off - off;
	पूर्ण

	/* reverse map the entire object onto the parent */
	ret = rbd_obj_calc_img_extents(obj_req, true);
	अगर (ret)
		वापस ret;

	obj_req->flags |= RBD_OBJ_FLAG_NOOP_FOR_NONEXISTENT;
	अगर (rbd_obj_is_entire(obj_req) && !obj_req->num_img_extents)
		obj_req->flags |= RBD_OBJ_FLAG_DELETION;

	obj_req->ग_लिखो_state = RBD_OBJ_WRITE_START;
	वापस 0;
पूर्ण

अटल व्योम __rbd_osd_setup_zeroout_ops(काष्ठा ceph_osd_request *osd_req,
					पूर्णांक which)
अणु
	काष्ठा rbd_obj_request *obj_req = osd_req->r_priv;
	u16 opcode;

	अगर (rbd_obj_is_entire(obj_req)) अणु
		अगर (obj_req->num_img_extents) अणु
			अगर (!(obj_req->flags & RBD_OBJ_FLAG_COPYUP_ENABLED))
				osd_req_op_init(osd_req, which++,
						CEPH_OSD_OP_CREATE, 0);
			opcode = CEPH_OSD_OP_TRUNCATE;
		पूर्ण अन्यथा अणु
			rbd_निश्चित(obj_req->flags & RBD_OBJ_FLAG_DELETION);
			osd_req_op_init(osd_req, which++,
					CEPH_OSD_OP_DELETE, 0);
			opcode = 0;
		पूर्ण
	पूर्ण अन्यथा अणु
		opcode = truncate_or_zero_opcode(obj_req);
	पूर्ण

	अगर (opcode)
		osd_req_op_extent_init(osd_req, which, opcode,
				       obj_req->ex.oe_off, obj_req->ex.oe_len,
				       0, 0);
पूर्ण

अटल पूर्णांक rbd_obj_init_zeroout(काष्ठा rbd_obj_request *obj_req)
अणु
	पूर्णांक ret;

	/* reverse map the entire object onto the parent */
	ret = rbd_obj_calc_img_extents(obj_req, true);
	अगर (ret)
		वापस ret;

	अगर (rbd_obj_copyup_enabled(obj_req))
		obj_req->flags |= RBD_OBJ_FLAG_COPYUP_ENABLED;
	अगर (!obj_req->num_img_extents) अणु
		obj_req->flags |= RBD_OBJ_FLAG_NOOP_FOR_NONEXISTENT;
		अगर (rbd_obj_is_entire(obj_req))
			obj_req->flags |= RBD_OBJ_FLAG_DELETION;
	पूर्ण

	obj_req->ग_लिखो_state = RBD_OBJ_WRITE_START;
	वापस 0;
पूर्ण

अटल पूर्णांक count_ग_लिखो_ops(काष्ठा rbd_obj_request *obj_req)
अणु
	काष्ठा rbd_img_request *img_req = obj_req->img_request;

	चयन (img_req->op_type) अणु
	हाल OBJ_OP_WRITE:
		अगर (!use_object_map(img_req->rbd_dev) ||
		    !(obj_req->flags & RBD_OBJ_FLAG_MAY_EXIST))
			वापस 2; /* setallochपूर्णांक + ग_लिखो/ग_लिखोfull */

		वापस 1; /* ग_लिखो/ग_लिखोfull */
	हाल OBJ_OP_DISCARD:
		वापस 1; /* delete/truncate/zero */
	हाल OBJ_OP_ZEROOUT:
		अगर (rbd_obj_is_entire(obj_req) && obj_req->num_img_extents &&
		    !(obj_req->flags & RBD_OBJ_FLAG_COPYUP_ENABLED))
			वापस 2; /* create + truncate */

		वापस 1; /* delete/truncate/zero */
	शेष:
		BUG();
	पूर्ण
पूर्ण

अटल व्योम rbd_osd_setup_ग_लिखो_ops(काष्ठा ceph_osd_request *osd_req,
				    पूर्णांक which)
अणु
	काष्ठा rbd_obj_request *obj_req = osd_req->r_priv;

	चयन (obj_req->img_request->op_type) अणु
	हाल OBJ_OP_WRITE:
		__rbd_osd_setup_ग_लिखो_ops(osd_req, which);
		अवरोध;
	हाल OBJ_OP_DISCARD:
		__rbd_osd_setup_discard_ops(osd_req, which);
		अवरोध;
	हाल OBJ_OP_ZEROOUT:
		__rbd_osd_setup_zeroout_ops(osd_req, which);
		अवरोध;
	शेष:
		BUG();
	पूर्ण
पूर्ण

/*
 * Prune the list of object requests (adjust offset and/or length, drop
 * redundant requests).  Prepare object request state machines and image
 * request state machine क्रम execution.
 */
अटल पूर्णांक __rbd_img_fill_request(काष्ठा rbd_img_request *img_req)
अणु
	काष्ठा rbd_obj_request *obj_req, *next_obj_req;
	पूर्णांक ret;

	क्रम_each_obj_request_safe(img_req, obj_req, next_obj_req) अणु
		चयन (img_req->op_type) अणु
		हाल OBJ_OP_READ:
			ret = rbd_obj_init_पढ़ो(obj_req);
			अवरोध;
		हाल OBJ_OP_WRITE:
			ret = rbd_obj_init_ग_लिखो(obj_req);
			अवरोध;
		हाल OBJ_OP_DISCARD:
			ret = rbd_obj_init_discard(obj_req);
			अवरोध;
		हाल OBJ_OP_ZEROOUT:
			ret = rbd_obj_init_zeroout(obj_req);
			अवरोध;
		शेष:
			BUG();
		पूर्ण
		अगर (ret < 0)
			वापस ret;
		अगर (ret > 0) अणु
			rbd_img_obj_request_del(img_req, obj_req);
			जारी;
		पूर्ण
	पूर्ण

	img_req->state = RBD_IMG_START;
	वापस 0;
पूर्ण

जोड़ rbd_img_fill_iter अणु
	काष्ठा ceph_bio_iter	bio_iter;
	काष्ठा ceph_bvec_iter	bvec_iter;
पूर्ण;

काष्ठा rbd_img_fill_ctx अणु
	क्रमागत obj_request_type	pos_type;
	जोड़ rbd_img_fill_iter	*pos;
	जोड़ rbd_img_fill_iter	iter;
	ceph_object_extent_fn_t	set_pos_fn;
	ceph_object_extent_fn_t	count_fn;
	ceph_object_extent_fn_t	copy_fn;
पूर्ण;

अटल काष्ठा ceph_object_extent *alloc_object_extent(व्योम *arg)
अणु
	काष्ठा rbd_img_request *img_req = arg;
	काष्ठा rbd_obj_request *obj_req;

	obj_req = rbd_obj_request_create();
	अगर (!obj_req)
		वापस शून्य;

	rbd_img_obj_request_add(img_req, obj_req);
	वापस &obj_req->ex;
पूर्ण

/*
 * While su != os && sc == 1 is technically not fancy (it's the same
 * layout as su == os && sc == 1), we can't use the nocopy path क्रम it
 * because ->set_pos_fn() should be called only once per object.
 * ceph_file_to_extents() invokes action_fn once per stripe unit, so
 * treat su != os && sc == 1 as fancy.
 */
अटल bool rbd_layout_is_fancy(काष्ठा ceph_file_layout *l)
अणु
	वापस l->stripe_unit != l->object_size;
पूर्ण

अटल पूर्णांक rbd_img_fill_request_nocopy(काष्ठा rbd_img_request *img_req,
				       काष्ठा ceph_file_extent *img_extents,
				       u32 num_img_extents,
				       काष्ठा rbd_img_fill_ctx *fctx)
अणु
	u32 i;
	पूर्णांक ret;

	img_req->data_type = fctx->pos_type;

	/*
	 * Create object requests and set each object request's starting
	 * position in the provided bio (list) or bio_vec array.
	 */
	fctx->iter = *fctx->pos;
	क्रम (i = 0; i < num_img_extents; i++) अणु
		ret = ceph_file_to_extents(&img_req->rbd_dev->layout,
					   img_extents[i].fe_off,
					   img_extents[i].fe_len,
					   &img_req->object_extents,
					   alloc_object_extent, img_req,
					   fctx->set_pos_fn, &fctx->iter);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस __rbd_img_fill_request(img_req);
पूर्ण

/*
 * Map a list of image extents to a list of object extents, create the
 * corresponding object requests (normally each to a dअगरferent object,
 * but not always) and add them to @img_req.  For each object request,
 * set up its data descriptor to poपूर्णांक to the corresponding chunk(s) of
 * @fctx->pos data buffer.
 *
 * Because ceph_file_to_extents() will merge adjacent object extents
 * together, each object request's data descriptor may poपूर्णांक to multiple
 * dअगरferent chunks of @fctx->pos data buffer.
 *
 * @fctx->pos data buffer is assumed to be large enough.
 */
अटल पूर्णांक rbd_img_fill_request(काष्ठा rbd_img_request *img_req,
				काष्ठा ceph_file_extent *img_extents,
				u32 num_img_extents,
				काष्ठा rbd_img_fill_ctx *fctx)
अणु
	काष्ठा rbd_device *rbd_dev = img_req->rbd_dev;
	काष्ठा rbd_obj_request *obj_req;
	u32 i;
	पूर्णांक ret;

	अगर (fctx->pos_type == OBJ_REQUEST_NODATA ||
	    !rbd_layout_is_fancy(&rbd_dev->layout))
		वापस rbd_img_fill_request_nocopy(img_req, img_extents,
						   num_img_extents, fctx);

	img_req->data_type = OBJ_REQUEST_OWN_BVECS;

	/*
	 * Create object requests and determine ->bvec_count क्रम each object
	 * request.  Note that ->bvec_count sum over all object requests may
	 * be greater than the number of bio_vecs in the provided bio (list)
	 * or bio_vec array because when mapped, those bio_vecs can straddle
	 * stripe unit boundaries.
	 */
	fctx->iter = *fctx->pos;
	क्रम (i = 0; i < num_img_extents; i++) अणु
		ret = ceph_file_to_extents(&rbd_dev->layout,
					   img_extents[i].fe_off,
					   img_extents[i].fe_len,
					   &img_req->object_extents,
					   alloc_object_extent, img_req,
					   fctx->count_fn, &fctx->iter);
		अगर (ret)
			वापस ret;
	पूर्ण

	क्रम_each_obj_request(img_req, obj_req) अणु
		obj_req->bvec_pos.bvecs = kदो_स्मृति_array(obj_req->bvec_count,
					      माप(*obj_req->bvec_pos.bvecs),
					      GFP_NOIO);
		अगर (!obj_req->bvec_pos.bvecs)
			वापस -ENOMEM;
	पूर्ण

	/*
	 * Fill in each object request's निजी bio_vec array, splitting and
	 * rearranging the provided bio_vecs in stripe unit chunks as needed.
	 */
	fctx->iter = *fctx->pos;
	क्रम (i = 0; i < num_img_extents; i++) अणु
		ret = ceph_iterate_extents(&rbd_dev->layout,
					   img_extents[i].fe_off,
					   img_extents[i].fe_len,
					   &img_req->object_extents,
					   fctx->copy_fn, &fctx->iter);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस __rbd_img_fill_request(img_req);
पूर्ण

अटल पूर्णांक rbd_img_fill_nodata(काष्ठा rbd_img_request *img_req,
			       u64 off, u64 len)
अणु
	काष्ठा ceph_file_extent ex = अणु off, len पूर्ण;
	जोड़ rbd_img_fill_iter dummy = अणुपूर्ण;
	काष्ठा rbd_img_fill_ctx fctx = अणु
		.pos_type = OBJ_REQUEST_NODATA,
		.pos = &dummy,
	पूर्ण;

	वापस rbd_img_fill_request(img_req, &ex, 1, &fctx);
पूर्ण

अटल व्योम set_bio_pos(काष्ठा ceph_object_extent *ex, u32 bytes, व्योम *arg)
अणु
	काष्ठा rbd_obj_request *obj_req =
	    container_of(ex, काष्ठा rbd_obj_request, ex);
	काष्ठा ceph_bio_iter *it = arg;

	करोut("%s objno %llu bytes %u\n", __func__, ex->oe_objno, bytes);
	obj_req->bio_pos = *it;
	ceph_bio_iter_advance(it, bytes);
पूर्ण

अटल व्योम count_bio_bvecs(काष्ठा ceph_object_extent *ex, u32 bytes, व्योम *arg)
अणु
	काष्ठा rbd_obj_request *obj_req =
	    container_of(ex, काष्ठा rbd_obj_request, ex);
	काष्ठा ceph_bio_iter *it = arg;

	करोut("%s objno %llu bytes %u\n", __func__, ex->oe_objno, bytes);
	ceph_bio_iter_advance_step(it, bytes, (अणु
		obj_req->bvec_count++;
	पूर्ण));

पूर्ण

अटल व्योम copy_bio_bvecs(काष्ठा ceph_object_extent *ex, u32 bytes, व्योम *arg)
अणु
	काष्ठा rbd_obj_request *obj_req =
	    container_of(ex, काष्ठा rbd_obj_request, ex);
	काष्ठा ceph_bio_iter *it = arg;

	करोut("%s objno %llu bytes %u\n", __func__, ex->oe_objno, bytes);
	ceph_bio_iter_advance_step(it, bytes, (अणु
		obj_req->bvec_pos.bvecs[obj_req->bvec_idx++] = bv;
		obj_req->bvec_pos.iter.bi_size += bv.bv_len;
	पूर्ण));
पूर्ण

अटल पूर्णांक __rbd_img_fill_from_bio(काष्ठा rbd_img_request *img_req,
				   काष्ठा ceph_file_extent *img_extents,
				   u32 num_img_extents,
				   काष्ठा ceph_bio_iter *bio_pos)
अणु
	काष्ठा rbd_img_fill_ctx fctx = अणु
		.pos_type = OBJ_REQUEST_BIO,
		.pos = (जोड़ rbd_img_fill_iter *)bio_pos,
		.set_pos_fn = set_bio_pos,
		.count_fn = count_bio_bvecs,
		.copy_fn = copy_bio_bvecs,
	पूर्ण;

	वापस rbd_img_fill_request(img_req, img_extents, num_img_extents,
				    &fctx);
पूर्ण

अटल पूर्णांक rbd_img_fill_from_bio(काष्ठा rbd_img_request *img_req,
				 u64 off, u64 len, काष्ठा bio *bio)
अणु
	काष्ठा ceph_file_extent ex = अणु off, len पूर्ण;
	काष्ठा ceph_bio_iter it = अणु .bio = bio, .iter = bio->bi_iter पूर्ण;

	वापस __rbd_img_fill_from_bio(img_req, &ex, 1, &it);
पूर्ण

अटल व्योम set_bvec_pos(काष्ठा ceph_object_extent *ex, u32 bytes, व्योम *arg)
अणु
	काष्ठा rbd_obj_request *obj_req =
	    container_of(ex, काष्ठा rbd_obj_request, ex);
	काष्ठा ceph_bvec_iter *it = arg;

	obj_req->bvec_pos = *it;
	ceph_bvec_iter_लघुen(&obj_req->bvec_pos, bytes);
	ceph_bvec_iter_advance(it, bytes);
पूर्ण

अटल व्योम count_bvecs(काष्ठा ceph_object_extent *ex, u32 bytes, व्योम *arg)
अणु
	काष्ठा rbd_obj_request *obj_req =
	    container_of(ex, काष्ठा rbd_obj_request, ex);
	काष्ठा ceph_bvec_iter *it = arg;

	ceph_bvec_iter_advance_step(it, bytes, (अणु
		obj_req->bvec_count++;
	पूर्ण));
पूर्ण

अटल व्योम copy_bvecs(काष्ठा ceph_object_extent *ex, u32 bytes, व्योम *arg)
अणु
	काष्ठा rbd_obj_request *obj_req =
	    container_of(ex, काष्ठा rbd_obj_request, ex);
	काष्ठा ceph_bvec_iter *it = arg;

	ceph_bvec_iter_advance_step(it, bytes, (अणु
		obj_req->bvec_pos.bvecs[obj_req->bvec_idx++] = bv;
		obj_req->bvec_pos.iter.bi_size += bv.bv_len;
	पूर्ण));
पूर्ण

अटल पूर्णांक __rbd_img_fill_from_bvecs(काष्ठा rbd_img_request *img_req,
				     काष्ठा ceph_file_extent *img_extents,
				     u32 num_img_extents,
				     काष्ठा ceph_bvec_iter *bvec_pos)
अणु
	काष्ठा rbd_img_fill_ctx fctx = अणु
		.pos_type = OBJ_REQUEST_BVECS,
		.pos = (जोड़ rbd_img_fill_iter *)bvec_pos,
		.set_pos_fn = set_bvec_pos,
		.count_fn = count_bvecs,
		.copy_fn = copy_bvecs,
	पूर्ण;

	वापस rbd_img_fill_request(img_req, img_extents, num_img_extents,
				    &fctx);
पूर्ण

अटल पूर्णांक rbd_img_fill_from_bvecs(काष्ठा rbd_img_request *img_req,
				   काष्ठा ceph_file_extent *img_extents,
				   u32 num_img_extents,
				   काष्ठा bio_vec *bvecs)
अणु
	काष्ठा ceph_bvec_iter it = अणु
		.bvecs = bvecs,
		.iter = अणु .bi_size = ceph_file_extents_bytes(img_extents,
							     num_img_extents) पूर्ण,
	पूर्ण;

	वापस __rbd_img_fill_from_bvecs(img_req, img_extents, num_img_extents,
					 &it);
पूर्ण

अटल व्योम rbd_img_handle_request_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा rbd_img_request *img_req =
	    container_of(work, काष्ठा rbd_img_request, work);

	rbd_img_handle_request(img_req, img_req->work_result);
पूर्ण

अटल व्योम rbd_img_schedule(काष्ठा rbd_img_request *img_req, पूर्णांक result)
अणु
	INIT_WORK(&img_req->work, rbd_img_handle_request_work);
	img_req->work_result = result;
	queue_work(rbd_wq, &img_req->work);
पूर्ण

अटल bool rbd_obj_may_exist(काष्ठा rbd_obj_request *obj_req)
अणु
	काष्ठा rbd_device *rbd_dev = obj_req->img_request->rbd_dev;

	अगर (rbd_object_map_may_exist(rbd_dev, obj_req->ex.oe_objno)) अणु
		obj_req->flags |= RBD_OBJ_FLAG_MAY_EXIST;
		वापस true;
	पूर्ण

	करोut("%s %p objno %llu assuming dne\n", __func__, obj_req,
	     obj_req->ex.oe_objno);
	वापस false;
पूर्ण

अटल पूर्णांक rbd_obj_पढ़ो_object(काष्ठा rbd_obj_request *obj_req)
अणु
	काष्ठा ceph_osd_request *osd_req;
	पूर्णांक ret;

	osd_req = __rbd_obj_add_osd_request(obj_req, शून्य, 1);
	अगर (IS_ERR(osd_req))
		वापस PTR_ERR(osd_req);

	osd_req_op_extent_init(osd_req, 0, CEPH_OSD_OP_READ,
			       obj_req->ex.oe_off, obj_req->ex.oe_len, 0, 0);
	rbd_osd_setup_data(osd_req, 0);
	rbd_osd_क्रमmat_पढ़ो(osd_req);

	ret = ceph_osdc_alloc_messages(osd_req, GFP_NOIO);
	अगर (ret)
		वापस ret;

	rbd_osd_submit(osd_req);
	वापस 0;
पूर्ण

अटल पूर्णांक rbd_obj_पढ़ो_from_parent(काष्ठा rbd_obj_request *obj_req)
अणु
	काष्ठा rbd_img_request *img_req = obj_req->img_request;
	काष्ठा rbd_device *parent = img_req->rbd_dev->parent;
	काष्ठा rbd_img_request *child_img_req;
	पूर्णांक ret;

	child_img_req = kmem_cache_alloc(rbd_img_request_cache, GFP_NOIO);
	अगर (!child_img_req)
		वापस -ENOMEM;

	rbd_img_request_init(child_img_req, parent, OBJ_OP_READ);
	__set_bit(IMG_REQ_CHILD, &child_img_req->flags);
	child_img_req->obj_request = obj_req;

	करोwn_पढ़ो(&parent->header_rwsem);
	rbd_img_capture_header(child_img_req);
	up_पढ़ो(&parent->header_rwsem);

	करोut("%s child_img_req %p for obj_req %p\n", __func__, child_img_req,
	     obj_req);

	अगर (!rbd_img_is_ग_लिखो(img_req)) अणु
		चयन (img_req->data_type) अणु
		हाल OBJ_REQUEST_BIO:
			ret = __rbd_img_fill_from_bio(child_img_req,
						      obj_req->img_extents,
						      obj_req->num_img_extents,
						      &obj_req->bio_pos);
			अवरोध;
		हाल OBJ_REQUEST_BVECS:
		हाल OBJ_REQUEST_OWN_BVECS:
			ret = __rbd_img_fill_from_bvecs(child_img_req,
						      obj_req->img_extents,
						      obj_req->num_img_extents,
						      &obj_req->bvec_pos);
			अवरोध;
		शेष:
			BUG();
		पूर्ण
	पूर्ण अन्यथा अणु
		ret = rbd_img_fill_from_bvecs(child_img_req,
					      obj_req->img_extents,
					      obj_req->num_img_extents,
					      obj_req->copyup_bvecs);
	पूर्ण
	अगर (ret) अणु
		rbd_img_request_destroy(child_img_req);
		वापस ret;
	पूर्ण

	/* aव्योम parent chain recursion */
	rbd_img_schedule(child_img_req, 0);
	वापस 0;
पूर्ण

अटल bool rbd_obj_advance_पढ़ो(काष्ठा rbd_obj_request *obj_req, पूर्णांक *result)
अणु
	काष्ठा rbd_device *rbd_dev = obj_req->img_request->rbd_dev;
	पूर्णांक ret;

again:
	चयन (obj_req->पढ़ो_state) अणु
	हाल RBD_OBJ_READ_START:
		rbd_निश्चित(!*result);

		अगर (!rbd_obj_may_exist(obj_req)) अणु
			*result = -ENOENT;
			obj_req->पढ़ो_state = RBD_OBJ_READ_OBJECT;
			जाओ again;
		पूर्ण

		ret = rbd_obj_पढ़ो_object(obj_req);
		अगर (ret) अणु
			*result = ret;
			वापस true;
		पूर्ण
		obj_req->पढ़ो_state = RBD_OBJ_READ_OBJECT;
		वापस false;
	हाल RBD_OBJ_READ_OBJECT:
		अगर (*result == -ENOENT && rbd_dev->parent_overlap) अणु
			/* reverse map this object extent onto the parent */
			ret = rbd_obj_calc_img_extents(obj_req, false);
			अगर (ret) अणु
				*result = ret;
				वापस true;
			पूर्ण
			अगर (obj_req->num_img_extents) अणु
				ret = rbd_obj_पढ़ो_from_parent(obj_req);
				अगर (ret) अणु
					*result = ret;
					वापस true;
				पूर्ण
				obj_req->पढ़ो_state = RBD_OBJ_READ_PARENT;
				वापस false;
			पूर्ण
		पूर्ण

		/*
		 * -ENOENT means a hole in the image -- zero-fill the entire
		 * length of the request.  A लघु पढ़ो also implies zero-fill
		 * to the end of the request.
		 */
		अगर (*result == -ENOENT) अणु
			rbd_obj_zero_range(obj_req, 0, obj_req->ex.oe_len);
			*result = 0;
		पूर्ण अन्यथा अगर (*result >= 0) अणु
			अगर (*result < obj_req->ex.oe_len)
				rbd_obj_zero_range(obj_req, *result,
						obj_req->ex.oe_len - *result);
			अन्यथा
				rbd_निश्चित(*result == obj_req->ex.oe_len);
			*result = 0;
		पूर्ण
		वापस true;
	हाल RBD_OBJ_READ_PARENT:
		/*
		 * The parent image is पढ़ो only up to the overlap -- zero-fill
		 * from the overlap to the end of the request.
		 */
		अगर (!*result) अणु
			u32 obj_overlap = rbd_obj_img_extents_bytes(obj_req);

			अगर (obj_overlap < obj_req->ex.oe_len)
				rbd_obj_zero_range(obj_req, obj_overlap,
					    obj_req->ex.oe_len - obj_overlap);
		पूर्ण
		वापस true;
	शेष:
		BUG();
	पूर्ण
पूर्ण

अटल bool rbd_obj_ग_लिखो_is_noop(काष्ठा rbd_obj_request *obj_req)
अणु
	काष्ठा rbd_device *rbd_dev = obj_req->img_request->rbd_dev;

	अगर (rbd_object_map_may_exist(rbd_dev, obj_req->ex.oe_objno))
		obj_req->flags |= RBD_OBJ_FLAG_MAY_EXIST;

	अगर (!(obj_req->flags & RBD_OBJ_FLAG_MAY_EXIST) &&
	    (obj_req->flags & RBD_OBJ_FLAG_NOOP_FOR_NONEXISTENT)) अणु
		करोut("%s %p noop for nonexistent\n", __func__, obj_req);
		वापस true;
	पूर्ण

	वापस false;
पूर्ण

/*
 * Return:
 *   0 - object map update sent
 *   1 - object map update isn't needed
 *  <0 - error
 */
अटल पूर्णांक rbd_obj_ग_लिखो_pre_object_map(काष्ठा rbd_obj_request *obj_req)
अणु
	काष्ठा rbd_device *rbd_dev = obj_req->img_request->rbd_dev;
	u8 new_state;

	अगर (!(rbd_dev->header.features & RBD_FEATURE_OBJECT_MAP))
		वापस 1;

	अगर (obj_req->flags & RBD_OBJ_FLAG_DELETION)
		new_state = OBJECT_PENDING;
	अन्यथा
		new_state = OBJECT_EXISTS;

	वापस rbd_object_map_update(obj_req, CEPH_NOSNAP, new_state, शून्य);
पूर्ण

अटल पूर्णांक rbd_obj_ग_लिखो_object(काष्ठा rbd_obj_request *obj_req)
अणु
	काष्ठा ceph_osd_request *osd_req;
	पूर्णांक num_ops = count_ग_लिखो_ops(obj_req);
	पूर्णांक which = 0;
	पूर्णांक ret;

	अगर (obj_req->flags & RBD_OBJ_FLAG_COPYUP_ENABLED)
		num_ops++; /* stat */

	osd_req = rbd_obj_add_osd_request(obj_req, num_ops);
	अगर (IS_ERR(osd_req))
		वापस PTR_ERR(osd_req);

	अगर (obj_req->flags & RBD_OBJ_FLAG_COPYUP_ENABLED) अणु
		ret = rbd_osd_setup_stat(osd_req, which++);
		अगर (ret)
			वापस ret;
	पूर्ण

	rbd_osd_setup_ग_लिखो_ops(osd_req, which);
	rbd_osd_क्रमmat_ग_लिखो(osd_req);

	ret = ceph_osdc_alloc_messages(osd_req, GFP_NOIO);
	अगर (ret)
		वापस ret;

	rbd_osd_submit(osd_req);
	वापस 0;
पूर्ण

/*
 * copyup_bvecs pages are never highmem pages
 */
अटल bool is_zero_bvecs(काष्ठा bio_vec *bvecs, u32 bytes)
अणु
	काष्ठा ceph_bvec_iter it = अणु
		.bvecs = bvecs,
		.iter = अणु .bi_size = bytes पूर्ण,
	पूर्ण;

	ceph_bvec_iter_advance_step(&it, bytes, (अणु
		अगर (स_प्रथम_inv(page_address(bv.bv_page) + bv.bv_offset, 0,
			       bv.bv_len))
			वापस false;
	पूर्ण));
	वापस true;
पूर्ण

#घोषणा MODS_ONLY	U32_MAX

अटल पूर्णांक rbd_obj_copyup_empty_snapc(काष्ठा rbd_obj_request *obj_req,
				      u32 bytes)
अणु
	काष्ठा ceph_osd_request *osd_req;
	पूर्णांक ret;

	करोut("%s obj_req %p bytes %u\n", __func__, obj_req, bytes);
	rbd_निश्चित(bytes > 0 && bytes != MODS_ONLY);

	osd_req = __rbd_obj_add_osd_request(obj_req, &rbd_empty_snapc, 1);
	अगर (IS_ERR(osd_req))
		वापस PTR_ERR(osd_req);

	ret = rbd_osd_setup_copyup(osd_req, 0, bytes);
	अगर (ret)
		वापस ret;

	rbd_osd_क्रमmat_ग_लिखो(osd_req);

	ret = ceph_osdc_alloc_messages(osd_req, GFP_NOIO);
	अगर (ret)
		वापस ret;

	rbd_osd_submit(osd_req);
	वापस 0;
पूर्ण

अटल पूर्णांक rbd_obj_copyup_current_snapc(काष्ठा rbd_obj_request *obj_req,
					u32 bytes)
अणु
	काष्ठा ceph_osd_request *osd_req;
	पूर्णांक num_ops = count_ग_लिखो_ops(obj_req);
	पूर्णांक which = 0;
	पूर्णांक ret;

	करोut("%s obj_req %p bytes %u\n", __func__, obj_req, bytes);

	अगर (bytes != MODS_ONLY)
		num_ops++; /* copyup */

	osd_req = rbd_obj_add_osd_request(obj_req, num_ops);
	अगर (IS_ERR(osd_req))
		वापस PTR_ERR(osd_req);

	अगर (bytes != MODS_ONLY) अणु
		ret = rbd_osd_setup_copyup(osd_req, which++, bytes);
		अगर (ret)
			वापस ret;
	पूर्ण

	rbd_osd_setup_ग_लिखो_ops(osd_req, which);
	rbd_osd_क्रमmat_ग_लिखो(osd_req);

	ret = ceph_osdc_alloc_messages(osd_req, GFP_NOIO);
	अगर (ret)
		वापस ret;

	rbd_osd_submit(osd_req);
	वापस 0;
पूर्ण

अटल पूर्णांक setup_copyup_bvecs(काष्ठा rbd_obj_request *obj_req, u64 obj_overlap)
अणु
	u32 i;

	rbd_निश्चित(!obj_req->copyup_bvecs);
	obj_req->copyup_bvec_count = calc_pages_क्रम(0, obj_overlap);
	obj_req->copyup_bvecs = kसुस्मृति(obj_req->copyup_bvec_count,
					माप(*obj_req->copyup_bvecs),
					GFP_NOIO);
	अगर (!obj_req->copyup_bvecs)
		वापस -ENOMEM;

	क्रम (i = 0; i < obj_req->copyup_bvec_count; i++) अणु
		अचिन्हित पूर्णांक len = min(obj_overlap, (u64)PAGE_SIZE);

		obj_req->copyup_bvecs[i].bv_page = alloc_page(GFP_NOIO);
		अगर (!obj_req->copyup_bvecs[i].bv_page)
			वापस -ENOMEM;

		obj_req->copyup_bvecs[i].bv_offset = 0;
		obj_req->copyup_bvecs[i].bv_len = len;
		obj_overlap -= len;
	पूर्ण

	rbd_निश्चित(!obj_overlap);
	वापस 0;
पूर्ण

/*
 * The target object करोesn't exist.  Read the data क्रम the entire
 * target object up to the overlap poपूर्णांक (अगर any) from the parent,
 * so we can use it क्रम a copyup.
 */
अटल पूर्णांक rbd_obj_copyup_पढ़ो_parent(काष्ठा rbd_obj_request *obj_req)
अणु
	काष्ठा rbd_device *rbd_dev = obj_req->img_request->rbd_dev;
	पूर्णांक ret;

	rbd_निश्चित(obj_req->num_img_extents);
	prune_extents(obj_req->img_extents, &obj_req->num_img_extents,
		      rbd_dev->parent_overlap);
	अगर (!obj_req->num_img_extents) अणु
		/*
		 * The overlap has become 0 (most likely because the
		 * image has been flattened).  Re-submit the original ग_लिखो
		 * request -- pass MODS_ONLY since the copyup isn't needed
		 * anymore.
		 */
		वापस rbd_obj_copyup_current_snapc(obj_req, MODS_ONLY);
	पूर्ण

	ret = setup_copyup_bvecs(obj_req, rbd_obj_img_extents_bytes(obj_req));
	अगर (ret)
		वापस ret;

	वापस rbd_obj_पढ़ो_from_parent(obj_req);
पूर्ण

अटल व्योम rbd_obj_copyup_object_maps(काष्ठा rbd_obj_request *obj_req)
अणु
	काष्ठा rbd_device *rbd_dev = obj_req->img_request->rbd_dev;
	काष्ठा ceph_snap_context *snapc = obj_req->img_request->snapc;
	u8 new_state;
	u32 i;
	पूर्णांक ret;

	rbd_निश्चित(!obj_req->pending.result && !obj_req->pending.num_pending);

	अगर (!(rbd_dev->header.features & RBD_FEATURE_OBJECT_MAP))
		वापस;

	अगर (obj_req->flags & RBD_OBJ_FLAG_COPYUP_ZEROS)
		वापस;

	क्रम (i = 0; i < snapc->num_snaps; i++) अणु
		अगर ((rbd_dev->header.features & RBD_FEATURE_FAST_DIFF) &&
		    i + 1 < snapc->num_snaps)
			new_state = OBJECT_EXISTS_CLEAN;
		अन्यथा
			new_state = OBJECT_EXISTS;

		ret = rbd_object_map_update(obj_req, snapc->snaps[i],
					    new_state, शून्य);
		अगर (ret < 0) अणु
			obj_req->pending.result = ret;
			वापस;
		पूर्ण

		rbd_निश्चित(!ret);
		obj_req->pending.num_pending++;
	पूर्ण
पूर्ण

अटल व्योम rbd_obj_copyup_ग_लिखो_object(काष्ठा rbd_obj_request *obj_req)
अणु
	u32 bytes = rbd_obj_img_extents_bytes(obj_req);
	पूर्णांक ret;

	rbd_निश्चित(!obj_req->pending.result && !obj_req->pending.num_pending);

	/*
	 * Only send non-zero copyup data to save some I/O and network
	 * bandwidth -- zero copyup data is equivalent to the object not
	 * existing.
	 */
	अगर (obj_req->flags & RBD_OBJ_FLAG_COPYUP_ZEROS)
		bytes = 0;

	अगर (obj_req->img_request->snapc->num_snaps && bytes > 0) अणु
		/*
		 * Send a copyup request with an empty snapshot context to
		 * deep-copyup the object through all existing snapshots.
		 * A second request with the current snapshot context will be
		 * sent क्रम the actual modअगरication.
		 */
		ret = rbd_obj_copyup_empty_snapc(obj_req, bytes);
		अगर (ret) अणु
			obj_req->pending.result = ret;
			वापस;
		पूर्ण

		obj_req->pending.num_pending++;
		bytes = MODS_ONLY;
	पूर्ण

	ret = rbd_obj_copyup_current_snapc(obj_req, bytes);
	अगर (ret) अणु
		obj_req->pending.result = ret;
		वापस;
	पूर्ण

	obj_req->pending.num_pending++;
पूर्ण

अटल bool rbd_obj_advance_copyup(काष्ठा rbd_obj_request *obj_req, पूर्णांक *result)
अणु
	काष्ठा rbd_device *rbd_dev = obj_req->img_request->rbd_dev;
	पूर्णांक ret;

again:
	चयन (obj_req->copyup_state) अणु
	हाल RBD_OBJ_COPYUP_START:
		rbd_निश्चित(!*result);

		ret = rbd_obj_copyup_पढ़ो_parent(obj_req);
		अगर (ret) अणु
			*result = ret;
			वापस true;
		पूर्ण
		अगर (obj_req->num_img_extents)
			obj_req->copyup_state = RBD_OBJ_COPYUP_READ_PARENT;
		अन्यथा
			obj_req->copyup_state = RBD_OBJ_COPYUP_WRITE_OBJECT;
		वापस false;
	हाल RBD_OBJ_COPYUP_READ_PARENT:
		अगर (*result)
			वापस true;

		अगर (is_zero_bvecs(obj_req->copyup_bvecs,
				  rbd_obj_img_extents_bytes(obj_req))) अणु
			करोut("%s %p detected zeros\n", __func__, obj_req);
			obj_req->flags |= RBD_OBJ_FLAG_COPYUP_ZEROS;
		पूर्ण

		rbd_obj_copyup_object_maps(obj_req);
		अगर (!obj_req->pending.num_pending) अणु
			*result = obj_req->pending.result;
			obj_req->copyup_state = RBD_OBJ_COPYUP_OBJECT_MAPS;
			जाओ again;
		पूर्ण
		obj_req->copyup_state = __RBD_OBJ_COPYUP_OBJECT_MAPS;
		वापस false;
	हाल __RBD_OBJ_COPYUP_OBJECT_MAPS:
		अगर (!pending_result_dec(&obj_req->pending, result))
			वापस false;
		fallthrough;
	हाल RBD_OBJ_COPYUP_OBJECT_MAPS:
		अगर (*result) अणु
			rbd_warn(rbd_dev, "snap object map update failed: %d",
				 *result);
			वापस true;
		पूर्ण

		rbd_obj_copyup_ग_लिखो_object(obj_req);
		अगर (!obj_req->pending.num_pending) अणु
			*result = obj_req->pending.result;
			obj_req->copyup_state = RBD_OBJ_COPYUP_WRITE_OBJECT;
			जाओ again;
		पूर्ण
		obj_req->copyup_state = __RBD_OBJ_COPYUP_WRITE_OBJECT;
		वापस false;
	हाल __RBD_OBJ_COPYUP_WRITE_OBJECT:
		अगर (!pending_result_dec(&obj_req->pending, result))
			वापस false;
		fallthrough;
	हाल RBD_OBJ_COPYUP_WRITE_OBJECT:
		वापस true;
	शेष:
		BUG();
	पूर्ण
पूर्ण

/*
 * Return:
 *   0 - object map update sent
 *   1 - object map update isn't needed
 *  <0 - error
 */
अटल पूर्णांक rbd_obj_ग_लिखो_post_object_map(काष्ठा rbd_obj_request *obj_req)
अणु
	काष्ठा rbd_device *rbd_dev = obj_req->img_request->rbd_dev;
	u8 current_state = OBJECT_PENDING;

	अगर (!(rbd_dev->header.features & RBD_FEATURE_OBJECT_MAP))
		वापस 1;

	अगर (!(obj_req->flags & RBD_OBJ_FLAG_DELETION))
		वापस 1;

	वापस rbd_object_map_update(obj_req, CEPH_NOSNAP, OBJECT_NONEXISTENT,
				     &current_state);
पूर्ण

अटल bool rbd_obj_advance_ग_लिखो(काष्ठा rbd_obj_request *obj_req, पूर्णांक *result)
अणु
	काष्ठा rbd_device *rbd_dev = obj_req->img_request->rbd_dev;
	पूर्णांक ret;

again:
	चयन (obj_req->ग_लिखो_state) अणु
	हाल RBD_OBJ_WRITE_START:
		rbd_निश्चित(!*result);

		अगर (rbd_obj_ग_लिखो_is_noop(obj_req))
			वापस true;

		ret = rbd_obj_ग_लिखो_pre_object_map(obj_req);
		अगर (ret < 0) अणु
			*result = ret;
			वापस true;
		पूर्ण
		obj_req->ग_लिखो_state = RBD_OBJ_WRITE_PRE_OBJECT_MAP;
		अगर (ret > 0)
			जाओ again;
		वापस false;
	हाल RBD_OBJ_WRITE_PRE_OBJECT_MAP:
		अगर (*result) अणु
			rbd_warn(rbd_dev, "pre object map update failed: %d",
				 *result);
			वापस true;
		पूर्ण
		ret = rbd_obj_ग_लिखो_object(obj_req);
		अगर (ret) अणु
			*result = ret;
			वापस true;
		पूर्ण
		obj_req->ग_लिखो_state = RBD_OBJ_WRITE_OBJECT;
		वापस false;
	हाल RBD_OBJ_WRITE_OBJECT:
		अगर (*result == -ENOENT) अणु
			अगर (obj_req->flags & RBD_OBJ_FLAG_COPYUP_ENABLED) अणु
				*result = 0;
				obj_req->copyup_state = RBD_OBJ_COPYUP_START;
				obj_req->ग_लिखो_state = __RBD_OBJ_WRITE_COPYUP;
				जाओ again;
			पूर्ण
			/*
			 * On a non-existent object:
			 *   delete - -ENOENT, truncate/zero - 0
			 */
			अगर (obj_req->flags & RBD_OBJ_FLAG_DELETION)
				*result = 0;
		पूर्ण
		अगर (*result)
			वापस true;

		obj_req->ग_लिखो_state = RBD_OBJ_WRITE_COPYUP;
		जाओ again;
	हाल __RBD_OBJ_WRITE_COPYUP:
		अगर (!rbd_obj_advance_copyup(obj_req, result))
			वापस false;
		fallthrough;
	हाल RBD_OBJ_WRITE_COPYUP:
		अगर (*result) अणु
			rbd_warn(rbd_dev, "copyup failed: %d", *result);
			वापस true;
		पूर्ण
		ret = rbd_obj_ग_लिखो_post_object_map(obj_req);
		अगर (ret < 0) अणु
			*result = ret;
			वापस true;
		पूर्ण
		obj_req->ग_लिखो_state = RBD_OBJ_WRITE_POST_OBJECT_MAP;
		अगर (ret > 0)
			जाओ again;
		वापस false;
	हाल RBD_OBJ_WRITE_POST_OBJECT_MAP:
		अगर (*result)
			rbd_warn(rbd_dev, "post object map update failed: %d",
				 *result);
		वापस true;
	शेष:
		BUG();
	पूर्ण
पूर्ण

/*
 * Return true अगर @obj_req is completed.
 */
अटल bool __rbd_obj_handle_request(काष्ठा rbd_obj_request *obj_req,
				     पूर्णांक *result)
अणु
	काष्ठा rbd_img_request *img_req = obj_req->img_request;
	काष्ठा rbd_device *rbd_dev = img_req->rbd_dev;
	bool करोne;

	mutex_lock(&obj_req->state_mutex);
	अगर (!rbd_img_is_ग_लिखो(img_req))
		करोne = rbd_obj_advance_पढ़ो(obj_req, result);
	अन्यथा
		करोne = rbd_obj_advance_ग_लिखो(obj_req, result);
	mutex_unlock(&obj_req->state_mutex);

	अगर (करोne && *result) अणु
		rbd_निश्चित(*result < 0);
		rbd_warn(rbd_dev, "%s at objno %llu %llu~%llu result %d",
			 obj_op_name(img_req->op_type), obj_req->ex.oe_objno,
			 obj_req->ex.oe_off, obj_req->ex.oe_len, *result);
	पूर्ण
	वापस करोne;
पूर्ण

/*
 * This is खोलो-coded in rbd_img_handle_request() to aव्योम parent chain
 * recursion.
 */
अटल व्योम rbd_obj_handle_request(काष्ठा rbd_obj_request *obj_req, पूर्णांक result)
अणु
	अगर (__rbd_obj_handle_request(obj_req, &result))
		rbd_img_handle_request(obj_req->img_request, result);
पूर्ण

अटल bool need_exclusive_lock(काष्ठा rbd_img_request *img_req)
अणु
	काष्ठा rbd_device *rbd_dev = img_req->rbd_dev;

	अगर (!(rbd_dev->header.features & RBD_FEATURE_EXCLUSIVE_LOCK))
		वापस false;

	अगर (rbd_is_ro(rbd_dev))
		वापस false;

	rbd_निश्चित(!test_bit(IMG_REQ_CHILD, &img_req->flags));
	अगर (rbd_dev->opts->lock_on_पढ़ो ||
	    (rbd_dev->header.features & RBD_FEATURE_OBJECT_MAP))
		वापस true;

	वापस rbd_img_is_ग_लिखो(img_req);
पूर्ण

अटल bool rbd_lock_add_request(काष्ठा rbd_img_request *img_req)
अणु
	काष्ठा rbd_device *rbd_dev = img_req->rbd_dev;
	bool locked;

	lockdep_निश्चित_held(&rbd_dev->lock_rwsem);
	locked = rbd_dev->lock_state == RBD_LOCK_STATE_LOCKED;
	spin_lock(&rbd_dev->lock_lists_lock);
	rbd_निश्चित(list_empty(&img_req->lock_item));
	अगर (!locked)
		list_add_tail(&img_req->lock_item, &rbd_dev->acquiring_list);
	अन्यथा
		list_add_tail(&img_req->lock_item, &rbd_dev->running_list);
	spin_unlock(&rbd_dev->lock_lists_lock);
	वापस locked;
पूर्ण

अटल व्योम rbd_lock_del_request(काष्ठा rbd_img_request *img_req)
अणु
	काष्ठा rbd_device *rbd_dev = img_req->rbd_dev;
	bool need_wakeup;

	lockdep_निश्चित_held(&rbd_dev->lock_rwsem);
	spin_lock(&rbd_dev->lock_lists_lock);
	rbd_निश्चित(!list_empty(&img_req->lock_item));
	list_del_init(&img_req->lock_item);
	need_wakeup = (rbd_dev->lock_state == RBD_LOCK_STATE_RELEASING &&
		       list_empty(&rbd_dev->running_list));
	spin_unlock(&rbd_dev->lock_lists_lock);
	अगर (need_wakeup)
		complete(&rbd_dev->releasing_रुको);
पूर्ण

अटल पूर्णांक rbd_img_exclusive_lock(काष्ठा rbd_img_request *img_req)
अणु
	काष्ठा rbd_device *rbd_dev = img_req->rbd_dev;

	अगर (!need_exclusive_lock(img_req))
		वापस 1;

	अगर (rbd_lock_add_request(img_req))
		वापस 1;

	अगर (rbd_dev->opts->exclusive) अणु
		WARN_ON(1); /* lock got released? */
		वापस -EROFS;
	पूर्ण

	/*
	 * Note the use of mod_delayed_work() in rbd_acquire_lock()
	 * and cancel_delayed_work() in wake_lock_रुकोers().
	 */
	करोut("%s rbd_dev %p queueing lock_dwork\n", __func__, rbd_dev);
	queue_delayed_work(rbd_dev->task_wq, &rbd_dev->lock_dwork, 0);
	वापस 0;
पूर्ण

अटल व्योम rbd_img_object_requests(काष्ठा rbd_img_request *img_req)
अणु
	काष्ठा rbd_obj_request *obj_req;

	rbd_निश्चित(!img_req->pending.result && !img_req->pending.num_pending);

	क्रम_each_obj_request(img_req, obj_req) अणु
		पूर्णांक result = 0;

		अगर (__rbd_obj_handle_request(obj_req, &result)) अणु
			अगर (result) अणु
				img_req->pending.result = result;
				वापस;
			पूर्ण
		पूर्ण अन्यथा अणु
			img_req->pending.num_pending++;
		पूर्ण
	पूर्ण
पूर्ण

अटल bool rbd_img_advance(काष्ठा rbd_img_request *img_req, पूर्णांक *result)
अणु
	काष्ठा rbd_device *rbd_dev = img_req->rbd_dev;
	पूर्णांक ret;

again:
	चयन (img_req->state) अणु
	हाल RBD_IMG_START:
		rbd_निश्चित(!*result);

		ret = rbd_img_exclusive_lock(img_req);
		अगर (ret < 0) अणु
			*result = ret;
			वापस true;
		पूर्ण
		img_req->state = RBD_IMG_EXCLUSIVE_LOCK;
		अगर (ret > 0)
			जाओ again;
		वापस false;
	हाल RBD_IMG_EXCLUSIVE_LOCK:
		अगर (*result)
			वापस true;

		rbd_निश्चित(!need_exclusive_lock(img_req) ||
			   __rbd_is_lock_owner(rbd_dev));

		rbd_img_object_requests(img_req);
		अगर (!img_req->pending.num_pending) अणु
			*result = img_req->pending.result;
			img_req->state = RBD_IMG_OBJECT_REQUESTS;
			जाओ again;
		पूर्ण
		img_req->state = __RBD_IMG_OBJECT_REQUESTS;
		वापस false;
	हाल __RBD_IMG_OBJECT_REQUESTS:
		अगर (!pending_result_dec(&img_req->pending, result))
			वापस false;
		fallthrough;
	हाल RBD_IMG_OBJECT_REQUESTS:
		वापस true;
	शेष:
		BUG();
	पूर्ण
पूर्ण

/*
 * Return true अगर @img_req is completed.
 */
अटल bool __rbd_img_handle_request(काष्ठा rbd_img_request *img_req,
				     पूर्णांक *result)
अणु
	काष्ठा rbd_device *rbd_dev = img_req->rbd_dev;
	bool करोne;

	अगर (need_exclusive_lock(img_req)) अणु
		करोwn_पढ़ो(&rbd_dev->lock_rwsem);
		mutex_lock(&img_req->state_mutex);
		करोne = rbd_img_advance(img_req, result);
		अगर (करोne)
			rbd_lock_del_request(img_req);
		mutex_unlock(&img_req->state_mutex);
		up_पढ़ो(&rbd_dev->lock_rwsem);
	पूर्ण अन्यथा अणु
		mutex_lock(&img_req->state_mutex);
		करोne = rbd_img_advance(img_req, result);
		mutex_unlock(&img_req->state_mutex);
	पूर्ण

	अगर (करोne && *result) अणु
		rbd_निश्चित(*result < 0);
		rbd_warn(rbd_dev, "%s%s result %d",
		      test_bit(IMG_REQ_CHILD, &img_req->flags) ? "child " : "",
		      obj_op_name(img_req->op_type), *result);
	पूर्ण
	वापस करोne;
पूर्ण

अटल व्योम rbd_img_handle_request(काष्ठा rbd_img_request *img_req, पूर्णांक result)
अणु
again:
	अगर (!__rbd_img_handle_request(img_req, &result))
		वापस;

	अगर (test_bit(IMG_REQ_CHILD, &img_req->flags)) अणु
		काष्ठा rbd_obj_request *obj_req = img_req->obj_request;

		rbd_img_request_destroy(img_req);
		अगर (__rbd_obj_handle_request(obj_req, &result)) अणु
			img_req = obj_req->img_request;
			जाओ again;
		पूर्ण
	पूर्ण अन्यथा अणु
		काष्ठा request *rq = blk_mq_rq_from_pdu(img_req);

		rbd_img_request_destroy(img_req);
		blk_mq_end_request(rq, त्रुटि_सं_to_blk_status(result));
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा rbd_client_id rbd_empty_cid;

अटल bool rbd_cid_equal(स्थिर काष्ठा rbd_client_id *lhs,
			  स्थिर काष्ठा rbd_client_id *rhs)
अणु
	वापस lhs->gid == rhs->gid && lhs->handle == rhs->handle;
पूर्ण

अटल काष्ठा rbd_client_id rbd_get_cid(काष्ठा rbd_device *rbd_dev)
अणु
	काष्ठा rbd_client_id cid;

	mutex_lock(&rbd_dev->watch_mutex);
	cid.gid = ceph_client_gid(rbd_dev->rbd_client->client);
	cid.handle = rbd_dev->watch_cookie;
	mutex_unlock(&rbd_dev->watch_mutex);
	वापस cid;
पूर्ण

/*
 * lock_rwsem must be held क्रम ग_लिखो
 */
अटल व्योम rbd_set_owner_cid(काष्ठा rbd_device *rbd_dev,
			      स्थिर काष्ठा rbd_client_id *cid)
अणु
	करोut("%s rbd_dev %p %llu-%llu -> %llu-%llu\n", __func__, rbd_dev,
	     rbd_dev->owner_cid.gid, rbd_dev->owner_cid.handle,
	     cid->gid, cid->handle);
	rbd_dev->owner_cid = *cid; /* काष्ठा */
पूर्ण

अटल व्योम क्रमmat_lock_cookie(काष्ठा rbd_device *rbd_dev, अक्षर *buf)
अणु
	mutex_lock(&rbd_dev->watch_mutex);
	प्र_लिखो(buf, "%s %llu", RBD_LOCK_COOKIE_PREFIX, rbd_dev->watch_cookie);
	mutex_unlock(&rbd_dev->watch_mutex);
पूर्ण

अटल व्योम __rbd_lock(काष्ठा rbd_device *rbd_dev, स्थिर अक्षर *cookie)
अणु
	काष्ठा rbd_client_id cid = rbd_get_cid(rbd_dev);

	rbd_dev->lock_state = RBD_LOCK_STATE_LOCKED;
	म_नकल(rbd_dev->lock_cookie, cookie);
	rbd_set_owner_cid(rbd_dev, &cid);
	queue_work(rbd_dev->task_wq, &rbd_dev->acquired_lock_work);
पूर्ण

/*
 * lock_rwsem must be held क्रम ग_लिखो
 */
अटल पूर्णांक rbd_lock(काष्ठा rbd_device *rbd_dev)
अणु
	काष्ठा ceph_osd_client *osdc = &rbd_dev->rbd_client->client->osdc;
	अक्षर cookie[32];
	पूर्णांक ret;

	WARN_ON(__rbd_is_lock_owner(rbd_dev) ||
		rbd_dev->lock_cookie[0] != '\0');

	क्रमmat_lock_cookie(rbd_dev, cookie);
	ret = ceph_cls_lock(osdc, &rbd_dev->header_oid, &rbd_dev->header_oloc,
			    RBD_LOCK_NAME, CEPH_CLS_LOCK_EXCLUSIVE, cookie,
			    RBD_LOCK_TAG, "", 0);
	अगर (ret)
		वापस ret;

	__rbd_lock(rbd_dev, cookie);
	वापस 0;
पूर्ण

/*
 * lock_rwsem must be held क्रम ग_लिखो
 */
अटल व्योम rbd_unlock(काष्ठा rbd_device *rbd_dev)
अणु
	काष्ठा ceph_osd_client *osdc = &rbd_dev->rbd_client->client->osdc;
	पूर्णांक ret;

	WARN_ON(!__rbd_is_lock_owner(rbd_dev) ||
		rbd_dev->lock_cookie[0] == '\0');

	ret = ceph_cls_unlock(osdc, &rbd_dev->header_oid, &rbd_dev->header_oloc,
			      RBD_LOCK_NAME, rbd_dev->lock_cookie);
	अगर (ret && ret != -ENOENT)
		rbd_warn(rbd_dev, "failed to unlock header: %d", ret);

	/* treat errors as the image is unlocked */
	rbd_dev->lock_state = RBD_LOCK_STATE_UNLOCKED;
	rbd_dev->lock_cookie[0] = '\0';
	rbd_set_owner_cid(rbd_dev, &rbd_empty_cid);
	queue_work(rbd_dev->task_wq, &rbd_dev->released_lock_work);
पूर्ण

अटल पूर्णांक __rbd_notअगरy_op_lock(काष्ठा rbd_device *rbd_dev,
				क्रमागत rbd_notअगरy_op notअगरy_op,
				काष्ठा page ***preply_pages,
				माप_प्रकार *preply_len)
अणु
	काष्ठा ceph_osd_client *osdc = &rbd_dev->rbd_client->client->osdc;
	काष्ठा rbd_client_id cid = rbd_get_cid(rbd_dev);
	अक्षर buf[4 + 8 + 8 + CEPH_ENCODING_START_BLK_LEN];
	पूर्णांक buf_size = माप(buf);
	व्योम *p = buf;

	करोut("%s rbd_dev %p notify_op %d\n", __func__, rbd_dev, notअगरy_op);

	/* encode *LockPayload NotअगरyMessage (op + ClientId) */
	ceph_start_encoding(&p, 2, 1, buf_size - CEPH_ENCODING_START_BLK_LEN);
	ceph_encode_32(&p, notअगरy_op);
	ceph_encode_64(&p, cid.gid);
	ceph_encode_64(&p, cid.handle);

	वापस ceph_osdc_notअगरy(osdc, &rbd_dev->header_oid,
				&rbd_dev->header_oloc, buf, buf_size,
				RBD_NOTIFY_TIMEOUT, preply_pages, preply_len);
पूर्ण

अटल व्योम rbd_notअगरy_op_lock(काष्ठा rbd_device *rbd_dev,
			       क्रमागत rbd_notअगरy_op notअगरy_op)
अणु
	__rbd_notअगरy_op_lock(rbd_dev, notअगरy_op, शून्य, शून्य);
पूर्ण

अटल व्योम rbd_notअगरy_acquired_lock(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा rbd_device *rbd_dev = container_of(work, काष्ठा rbd_device,
						  acquired_lock_work);

	rbd_notअगरy_op_lock(rbd_dev, RBD_NOTIFY_OP_ACQUIRED_LOCK);
पूर्ण

अटल व्योम rbd_notअगरy_released_lock(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा rbd_device *rbd_dev = container_of(work, काष्ठा rbd_device,
						  released_lock_work);

	rbd_notअगरy_op_lock(rbd_dev, RBD_NOTIFY_OP_RELEASED_LOCK);
पूर्ण

अटल पूर्णांक rbd_request_lock(काष्ठा rbd_device *rbd_dev)
अणु
	काष्ठा page **reply_pages;
	माप_प्रकार reply_len;
	bool lock_owner_responded = false;
	पूर्णांक ret;

	करोut("%s rbd_dev %p\n", __func__, rbd_dev);

	ret = __rbd_notअगरy_op_lock(rbd_dev, RBD_NOTIFY_OP_REQUEST_LOCK,
				   &reply_pages, &reply_len);
	अगर (ret && ret != -ETIMEDOUT) अणु
		rbd_warn(rbd_dev, "failed to request lock: %d", ret);
		जाओ out;
	पूर्ण

	अगर (reply_len > 0 && reply_len <= PAGE_SIZE) अणु
		व्योम *p = page_address(reply_pages[0]);
		व्योम *स्थिर end = p + reply_len;
		u32 n;

		ceph_decode_32_safe(&p, end, n, e_inval); /* num_acks */
		जबतक (n--) अणु
			u8 काष्ठा_v;
			u32 len;

			ceph_decode_need(&p, end, 8 + 8, e_inval);
			p += 8 + 8; /* skip gid and cookie */

			ceph_decode_32_safe(&p, end, len, e_inval);
			अगर (!len)
				जारी;

			अगर (lock_owner_responded) अणु
				rbd_warn(rbd_dev,
					 "duplicate lock owners detected");
				ret = -EIO;
				जाओ out;
			पूर्ण

			lock_owner_responded = true;
			ret = ceph_start_decoding(&p, end, 1, "ResponseMessage",
						  &काष्ठा_v, &len);
			अगर (ret) अणु
				rbd_warn(rbd_dev,
					 "failed to decode ResponseMessage: %d",
					 ret);
				जाओ e_inval;
			पूर्ण

			ret = ceph_decode_32(&p);
		पूर्ण
	पूर्ण

	अगर (!lock_owner_responded) अणु
		rbd_warn(rbd_dev, "no lock owners detected");
		ret = -ETIMEDOUT;
	पूर्ण

out:
	ceph_release_page_vector(reply_pages, calc_pages_क्रम(0, reply_len));
	वापस ret;

e_inval:
	ret = -EINVAL;
	जाओ out;
पूर्ण

/*
 * Either image request state machine(s) or rbd_add_acquire_lock()
 * (i.e. "rbd map").
 */
अटल व्योम wake_lock_रुकोers(काष्ठा rbd_device *rbd_dev, पूर्णांक result)
अणु
	काष्ठा rbd_img_request *img_req;

	करोut("%s rbd_dev %p result %d\n", __func__, rbd_dev, result);
	lockdep_निश्चित_held_ग_लिखो(&rbd_dev->lock_rwsem);

	cancel_delayed_work(&rbd_dev->lock_dwork);
	अगर (!completion_करोne(&rbd_dev->acquire_रुको)) अणु
		rbd_निश्चित(list_empty(&rbd_dev->acquiring_list) &&
			   list_empty(&rbd_dev->running_list));
		rbd_dev->acquire_err = result;
		complete_all(&rbd_dev->acquire_रुको);
		वापस;
	पूर्ण

	list_क्रम_each_entry(img_req, &rbd_dev->acquiring_list, lock_item) अणु
		mutex_lock(&img_req->state_mutex);
		rbd_निश्चित(img_req->state == RBD_IMG_EXCLUSIVE_LOCK);
		rbd_img_schedule(img_req, result);
		mutex_unlock(&img_req->state_mutex);
	पूर्ण

	list_splice_tail_init(&rbd_dev->acquiring_list, &rbd_dev->running_list);
पूर्ण

अटल पूर्णांक get_lock_owner_info(काष्ठा rbd_device *rbd_dev,
			       काष्ठा ceph_locker **lockers, u32 *num_lockers)
अणु
	काष्ठा ceph_osd_client *osdc = &rbd_dev->rbd_client->client->osdc;
	u8 lock_type;
	अक्षर *lock_tag;
	पूर्णांक ret;

	करोut("%s rbd_dev %p\n", __func__, rbd_dev);

	ret = ceph_cls_lock_info(osdc, &rbd_dev->header_oid,
				 &rbd_dev->header_oloc, RBD_LOCK_NAME,
				 &lock_type, &lock_tag, lockers, num_lockers);
	अगर (ret)
		वापस ret;

	अगर (*num_lockers == 0) अणु
		करोut("%s rbd_dev %p no lockers detected\n", __func__, rbd_dev);
		जाओ out;
	पूर्ण

	अगर (म_भेद(lock_tag, RBD_LOCK_TAG)) अणु
		rbd_warn(rbd_dev, "locked by external mechanism, tag %s",
			 lock_tag);
		ret = -EBUSY;
		जाओ out;
	पूर्ण

	अगर (lock_type == CEPH_CLS_LOCK_SHARED) अणु
		rbd_warn(rbd_dev, "shared lock type detected");
		ret = -EBUSY;
		जाओ out;
	पूर्ण

	अगर (म_भेदन((*lockers)[0].id.cookie, RBD_LOCK_COOKIE_PREFIX,
		    म_माप(RBD_LOCK_COOKIE_PREFIX))) अणु
		rbd_warn(rbd_dev, "locked by external mechanism, cookie %s",
			 (*lockers)[0].id.cookie);
		ret = -EBUSY;
		जाओ out;
	पूर्ण

out:
	kमुक्त(lock_tag);
	वापस ret;
पूर्ण

अटल पूर्णांक find_watcher(काष्ठा rbd_device *rbd_dev,
			स्थिर काष्ठा ceph_locker *locker)
अणु
	काष्ठा ceph_osd_client *osdc = &rbd_dev->rbd_client->client->osdc;
	काष्ठा ceph_watch_item *watchers;
	u32 num_watchers;
	u64 cookie;
	पूर्णांक i;
	पूर्णांक ret;

	ret = ceph_osdc_list_watchers(osdc, &rbd_dev->header_oid,
				      &rbd_dev->header_oloc, &watchers,
				      &num_watchers);
	अगर (ret)
		वापस ret;

	माला_पूछो(locker->id.cookie, RBD_LOCK_COOKIE_PREFIX " %llu", &cookie);
	क्रम (i = 0; i < num_watchers; i++) अणु
		/*
		 * Ignore addr->type जबतक comparing.  This mimics
		 * entity_addr_t::get_legacy_str() + म_भेद().
		 */
		अगर (ceph_addr_equal_no_type(&watchers[i].addr,
					    &locker->info.addr) &&
		    watchers[i].cookie == cookie) अणु
			काष्ठा rbd_client_id cid = अणु
				.gid = le64_to_cpu(watchers[i].name.num),
				.handle = cookie,
			पूर्ण;

			करोut("%s rbd_dev %p found cid %llu-%llu\n", __func__,
			     rbd_dev, cid.gid, cid.handle);
			rbd_set_owner_cid(rbd_dev, &cid);
			ret = 1;
			जाओ out;
		पूर्ण
	पूर्ण

	करोut("%s rbd_dev %p no watchers\n", __func__, rbd_dev);
	ret = 0;
out:
	kमुक्त(watchers);
	वापस ret;
पूर्ण

/*
 * lock_rwsem must be held क्रम ग_लिखो
 */
अटल पूर्णांक rbd_try_lock(काष्ठा rbd_device *rbd_dev)
अणु
	काष्ठा ceph_client *client = rbd_dev->rbd_client->client;
	काष्ठा ceph_locker *lockers;
	u32 num_lockers;
	पूर्णांक ret;

	क्रम (;;) अणु
		ret = rbd_lock(rbd_dev);
		अगर (ret != -EBUSY)
			वापस ret;

		/* determine अगर the current lock holder is still alive */
		ret = get_lock_owner_info(rbd_dev, &lockers, &num_lockers);
		अगर (ret)
			वापस ret;

		अगर (num_lockers == 0)
			जाओ again;

		ret = find_watcher(rbd_dev, lockers);
		अगर (ret)
			जाओ out; /* request lock or error */

		rbd_warn(rbd_dev, "breaking header lock owned by %s%llu",
			 ENTITY_NAME(lockers[0].id.name));

		ret = ceph_monc_blocklist_add(&client->monc,
					      &lockers[0].info.addr);
		अगर (ret) अणु
			rbd_warn(rbd_dev, "blocklist of %s%llu failed: %d",
				 ENTITY_NAME(lockers[0].id.name), ret);
			जाओ out;
		पूर्ण

		ret = ceph_cls_अवरोध_lock(&client->osdc, &rbd_dev->header_oid,
					  &rbd_dev->header_oloc, RBD_LOCK_NAME,
					  lockers[0].id.cookie,
					  &lockers[0].id.name);
		अगर (ret && ret != -ENOENT)
			जाओ out;

again:
		ceph_मुक्त_lockers(lockers, num_lockers);
	पूर्ण

out:
	ceph_मुक्त_lockers(lockers, num_lockers);
	वापस ret;
पूर्ण

अटल पूर्णांक rbd_post_acquire_action(काष्ठा rbd_device *rbd_dev)
अणु
	पूर्णांक ret;

	अगर (rbd_dev->header.features & RBD_FEATURE_OBJECT_MAP) अणु
		ret = rbd_object_map_खोलो(rbd_dev);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Return:
 *   0 - lock acquired
 *   1 - caller should call rbd_request_lock()
 *  <0 - error
 */
अटल पूर्णांक rbd_try_acquire_lock(काष्ठा rbd_device *rbd_dev)
अणु
	पूर्णांक ret;

	करोwn_पढ़ो(&rbd_dev->lock_rwsem);
	करोut("%s rbd_dev %p read lock_state %d\n", __func__, rbd_dev,
	     rbd_dev->lock_state);
	अगर (__rbd_is_lock_owner(rbd_dev)) अणु
		up_पढ़ो(&rbd_dev->lock_rwsem);
		वापस 0;
	पूर्ण

	up_पढ़ो(&rbd_dev->lock_rwsem);
	करोwn_ग_लिखो(&rbd_dev->lock_rwsem);
	करोut("%s rbd_dev %p write lock_state %d\n", __func__, rbd_dev,
	     rbd_dev->lock_state);
	अगर (__rbd_is_lock_owner(rbd_dev)) अणु
		up_ग_लिखो(&rbd_dev->lock_rwsem);
		वापस 0;
	पूर्ण

	ret = rbd_try_lock(rbd_dev);
	अगर (ret < 0) अणु
		rbd_warn(rbd_dev, "failed to lock header: %d", ret);
		अगर (ret == -EBLOCKLISTED)
			जाओ out;

		ret = 1; /* request lock anyway */
	पूर्ण
	अगर (ret > 0) अणु
		up_ग_लिखो(&rbd_dev->lock_rwsem);
		वापस ret;
	पूर्ण

	rbd_निश्चित(rbd_dev->lock_state == RBD_LOCK_STATE_LOCKED);
	rbd_निश्चित(list_empty(&rbd_dev->running_list));

	ret = rbd_post_acquire_action(rbd_dev);
	अगर (ret) अणु
		rbd_warn(rbd_dev, "post-acquire action failed: %d", ret);
		/*
		 * Can't stay in RBD_LOCK_STATE_LOCKED because
		 * rbd_lock_add_request() would let the request through,
		 * assuming that e.g. object map is locked and loaded.
		 */
		rbd_unlock(rbd_dev);
	पूर्ण

out:
	wake_lock_रुकोers(rbd_dev, ret);
	up_ग_लिखो(&rbd_dev->lock_rwsem);
	वापस ret;
पूर्ण

अटल व्योम rbd_acquire_lock(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा rbd_device *rbd_dev = container_of(to_delayed_work(work),
					    काष्ठा rbd_device, lock_dwork);
	पूर्णांक ret;

	करोut("%s rbd_dev %p\n", __func__, rbd_dev);
again:
	ret = rbd_try_acquire_lock(rbd_dev);
	अगर (ret <= 0) अणु
		करोut("%s rbd_dev %p ret %d - done\n", __func__, rbd_dev, ret);
		वापस;
	पूर्ण

	ret = rbd_request_lock(rbd_dev);
	अगर (ret == -ETIMEDOUT) अणु
		जाओ again; /* treat this as a dead client */
	पूर्ण अन्यथा अगर (ret == -EROFS) अणु
		rbd_warn(rbd_dev, "peer will not release lock");
		करोwn_ग_लिखो(&rbd_dev->lock_rwsem);
		wake_lock_रुकोers(rbd_dev, ret);
		up_ग_लिखो(&rbd_dev->lock_rwsem);
	पूर्ण अन्यथा अगर (ret < 0) अणु
		rbd_warn(rbd_dev, "error requesting lock: %d", ret);
		mod_delayed_work(rbd_dev->task_wq, &rbd_dev->lock_dwork,
				 RBD_RETRY_DELAY);
	पूर्ण अन्यथा अणु
		/*
		 * lock owner acked, but resend अगर we करोn't see them
		 * release the lock
		 */
		करोut("%s rbd_dev %p requeuing lock_dwork\n", __func__,
		     rbd_dev);
		mod_delayed_work(rbd_dev->task_wq, &rbd_dev->lock_dwork,
		    msecs_to_jअगरfies(2 * RBD_NOTIFY_TIMEOUT * MSEC_PER_SEC));
	पूर्ण
पूर्ण

अटल bool rbd_quiesce_lock(काष्ठा rbd_device *rbd_dev)
अणु
	bool need_रुको;

	करोut("%s rbd_dev %p\n", __func__, rbd_dev);
	lockdep_निश्चित_held_ग_लिखो(&rbd_dev->lock_rwsem);

	अगर (rbd_dev->lock_state != RBD_LOCK_STATE_LOCKED)
		वापस false;

	/*
	 * Ensure that all in-flight IO is flushed.
	 */
	rbd_dev->lock_state = RBD_LOCK_STATE_RELEASING;
	rbd_निश्चित(!completion_करोne(&rbd_dev->releasing_रुको));
	need_रुको = !list_empty(&rbd_dev->running_list);
	करोwngrade_ग_लिखो(&rbd_dev->lock_rwsem);
	अगर (need_रुको)
		रुको_क्रम_completion(&rbd_dev->releasing_रुको);
	up_पढ़ो(&rbd_dev->lock_rwsem);

	करोwn_ग_लिखो(&rbd_dev->lock_rwsem);
	अगर (rbd_dev->lock_state != RBD_LOCK_STATE_RELEASING)
		वापस false;

	rbd_निश्चित(list_empty(&rbd_dev->running_list));
	वापस true;
पूर्ण

अटल व्योम rbd_pre_release_action(काष्ठा rbd_device *rbd_dev)
अणु
	अगर (rbd_dev->header.features & RBD_FEATURE_OBJECT_MAP)
		rbd_object_map_बंद(rbd_dev);
पूर्ण

अटल व्योम __rbd_release_lock(काष्ठा rbd_device *rbd_dev)
अणु
	rbd_निश्चित(list_empty(&rbd_dev->running_list));

	rbd_pre_release_action(rbd_dev);
	rbd_unlock(rbd_dev);
पूर्ण

/*
 * lock_rwsem must be held क्रम ग_लिखो
 */
अटल व्योम rbd_release_lock(काष्ठा rbd_device *rbd_dev)
अणु
	अगर (!rbd_quiesce_lock(rbd_dev))
		वापस;

	__rbd_release_lock(rbd_dev);

	/*
	 * Give others a chance to grab the lock - we would re-acquire
	 * almost immediately अगर we got new IO जबतक draining the running
	 * list otherwise.  We need to ack our own notअगरications, so this
	 * lock_dwork will be requeued from rbd_handle_released_lock() by
	 * way of maybe_kick_acquire().
	 */
	cancel_delayed_work(&rbd_dev->lock_dwork);
पूर्ण

अटल व्योम rbd_release_lock_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा rbd_device *rbd_dev = container_of(work, काष्ठा rbd_device,
						  unlock_work);

	करोwn_ग_लिखो(&rbd_dev->lock_rwsem);
	rbd_release_lock(rbd_dev);
	up_ग_लिखो(&rbd_dev->lock_rwsem);
पूर्ण

अटल व्योम maybe_kick_acquire(काष्ठा rbd_device *rbd_dev)
अणु
	bool have_requests;

	करोut("%s rbd_dev %p\n", __func__, rbd_dev);
	अगर (__rbd_is_lock_owner(rbd_dev))
		वापस;

	spin_lock(&rbd_dev->lock_lists_lock);
	have_requests = !list_empty(&rbd_dev->acquiring_list);
	spin_unlock(&rbd_dev->lock_lists_lock);
	अगर (have_requests || delayed_work_pending(&rbd_dev->lock_dwork)) अणु
		करोut("%s rbd_dev %p kicking lock_dwork\n", __func__, rbd_dev);
		mod_delayed_work(rbd_dev->task_wq, &rbd_dev->lock_dwork, 0);
	पूर्ण
पूर्ण

अटल व्योम rbd_handle_acquired_lock(काष्ठा rbd_device *rbd_dev, u8 काष्ठा_v,
				     व्योम **p)
अणु
	काष्ठा rbd_client_id cid = अणु 0 पूर्ण;

	अगर (काष्ठा_v >= 2) अणु
		cid.gid = ceph_decode_64(p);
		cid.handle = ceph_decode_64(p);
	पूर्ण

	करोut("%s rbd_dev %p cid %llu-%llu\n", __func__, rbd_dev, cid.gid,
	     cid.handle);
	अगर (!rbd_cid_equal(&cid, &rbd_empty_cid)) अणु
		करोwn_ग_लिखो(&rbd_dev->lock_rwsem);
		अगर (rbd_cid_equal(&cid, &rbd_dev->owner_cid)) अणु
			/*
			 * we alपढ़ोy know that the remote client is
			 * the owner
			 */
			up_ग_लिखो(&rbd_dev->lock_rwsem);
			वापस;
		पूर्ण

		rbd_set_owner_cid(rbd_dev, &cid);
		करोwngrade_ग_लिखो(&rbd_dev->lock_rwsem);
	पूर्ण अन्यथा अणु
		करोwn_पढ़ो(&rbd_dev->lock_rwsem);
	पूर्ण

	maybe_kick_acquire(rbd_dev);
	up_पढ़ो(&rbd_dev->lock_rwsem);
पूर्ण

अटल व्योम rbd_handle_released_lock(काष्ठा rbd_device *rbd_dev, u8 काष्ठा_v,
				     व्योम **p)
अणु
	काष्ठा rbd_client_id cid = अणु 0 पूर्ण;

	अगर (काष्ठा_v >= 2) अणु
		cid.gid = ceph_decode_64(p);
		cid.handle = ceph_decode_64(p);
	पूर्ण

	करोut("%s rbd_dev %p cid %llu-%llu\n", __func__, rbd_dev, cid.gid,
	     cid.handle);
	अगर (!rbd_cid_equal(&cid, &rbd_empty_cid)) अणु
		करोwn_ग_लिखो(&rbd_dev->lock_rwsem);
		अगर (!rbd_cid_equal(&cid, &rbd_dev->owner_cid)) अणु
			करोut("%s rbd_dev %p unexpected owner, cid %llu-%llu != owner_cid %llu-%llu\n",
			     __func__, rbd_dev, cid.gid, cid.handle,
			     rbd_dev->owner_cid.gid, rbd_dev->owner_cid.handle);
			up_ग_लिखो(&rbd_dev->lock_rwsem);
			वापस;
		पूर्ण

		rbd_set_owner_cid(rbd_dev, &rbd_empty_cid);
		करोwngrade_ग_लिखो(&rbd_dev->lock_rwsem);
	पूर्ण अन्यथा अणु
		करोwn_पढ़ो(&rbd_dev->lock_rwsem);
	पूर्ण

	maybe_kick_acquire(rbd_dev);
	up_पढ़ो(&rbd_dev->lock_rwsem);
पूर्ण

/*
 * Returns result क्रम ResponseMessage to be encoded (<= 0), or 1 अगर no
 * ResponseMessage is needed.
 */
अटल पूर्णांक rbd_handle_request_lock(काष्ठा rbd_device *rbd_dev, u8 काष्ठा_v,
				   व्योम **p)
अणु
	काष्ठा rbd_client_id my_cid = rbd_get_cid(rbd_dev);
	काष्ठा rbd_client_id cid = अणु 0 पूर्ण;
	पूर्णांक result = 1;

	अगर (काष्ठा_v >= 2) अणु
		cid.gid = ceph_decode_64(p);
		cid.handle = ceph_decode_64(p);
	पूर्ण

	करोut("%s rbd_dev %p cid %llu-%llu\n", __func__, rbd_dev, cid.gid,
	     cid.handle);
	अगर (rbd_cid_equal(&cid, &my_cid))
		वापस result;

	करोwn_पढ़ो(&rbd_dev->lock_rwsem);
	अगर (__rbd_is_lock_owner(rbd_dev)) अणु
		अगर (rbd_dev->lock_state == RBD_LOCK_STATE_LOCKED &&
		    rbd_cid_equal(&rbd_dev->owner_cid, &rbd_empty_cid))
			जाओ out_unlock;

		/*
		 * encode ResponseMessage(0) so the peer can detect
		 * a missing owner
		 */
		result = 0;

		अगर (rbd_dev->lock_state == RBD_LOCK_STATE_LOCKED) अणु
			अगर (!rbd_dev->opts->exclusive) अणु
				करोut("%s rbd_dev %p queueing unlock_work\n",
				     __func__, rbd_dev);
				queue_work(rbd_dev->task_wq,
					   &rbd_dev->unlock_work);
			पूर्ण अन्यथा अणु
				/* refuse to release the lock */
				result = -EROFS;
			पूर्ण
		पूर्ण
	पूर्ण

out_unlock:
	up_पढ़ो(&rbd_dev->lock_rwsem);
	वापस result;
पूर्ण

अटल व्योम __rbd_acknowledge_notअगरy(काष्ठा rbd_device *rbd_dev,
				     u64 notअगरy_id, u64 cookie, s32 *result)
अणु
	काष्ठा ceph_osd_client *osdc = &rbd_dev->rbd_client->client->osdc;
	अक्षर buf[4 + CEPH_ENCODING_START_BLK_LEN];
	पूर्णांक buf_size = माप(buf);
	पूर्णांक ret;

	अगर (result) अणु
		व्योम *p = buf;

		/* encode ResponseMessage */
		ceph_start_encoding(&p, 1, 1,
				    buf_size - CEPH_ENCODING_START_BLK_LEN);
		ceph_encode_32(&p, *result);
	पूर्ण अन्यथा अणु
		buf_size = 0;
	पूर्ण

	ret = ceph_osdc_notअगरy_ack(osdc, &rbd_dev->header_oid,
				   &rbd_dev->header_oloc, notअगरy_id, cookie,
				   buf, buf_size);
	अगर (ret)
		rbd_warn(rbd_dev, "acknowledge_notify failed: %d", ret);
पूर्ण

अटल व्योम rbd_acknowledge_notअगरy(काष्ठा rbd_device *rbd_dev, u64 notअगरy_id,
				   u64 cookie)
अणु
	करोut("%s rbd_dev %p\n", __func__, rbd_dev);
	__rbd_acknowledge_notअगरy(rbd_dev, notअगरy_id, cookie, शून्य);
पूर्ण

अटल व्योम rbd_acknowledge_notअगरy_result(काष्ठा rbd_device *rbd_dev,
					  u64 notअगरy_id, u64 cookie, s32 result)
अणु
	करोut("%s rbd_dev %p result %d\n", __func__, rbd_dev, result);
	__rbd_acknowledge_notअगरy(rbd_dev, notअगरy_id, cookie, &result);
पूर्ण

अटल व्योम rbd_watch_cb(व्योम *arg, u64 notअगरy_id, u64 cookie,
			 u64 notअगरier_id, व्योम *data, माप_प्रकार data_len)
अणु
	काष्ठा rbd_device *rbd_dev = arg;
	व्योम *p = data;
	व्योम *स्थिर end = p + data_len;
	u8 काष्ठा_v = 0;
	u32 len;
	u32 notअगरy_op;
	पूर्णांक ret;

	करोut("%s rbd_dev %p cookie %llu notify_id %llu data_len %zu\n",
	     __func__, rbd_dev, cookie, notअगरy_id, data_len);
	अगर (data_len) अणु
		ret = ceph_start_decoding(&p, end, 1, "NotifyMessage",
					  &काष्ठा_v, &len);
		अगर (ret) अणु
			rbd_warn(rbd_dev, "failed to decode NotifyMessage: %d",
				 ret);
			वापस;
		पूर्ण

		notअगरy_op = ceph_decode_32(&p);
	पूर्ण अन्यथा अणु
		/* legacy notअगरication क्रम header updates */
		notअगरy_op = RBD_NOTIFY_OP_HEADER_UPDATE;
		len = 0;
	पूर्ण

	करोut("%s rbd_dev %p notify_op %u\n", __func__, rbd_dev, notअगरy_op);
	चयन (notअगरy_op) अणु
	हाल RBD_NOTIFY_OP_ACQUIRED_LOCK:
		rbd_handle_acquired_lock(rbd_dev, काष्ठा_v, &p);
		rbd_acknowledge_notअगरy(rbd_dev, notअगरy_id, cookie);
		अवरोध;
	हाल RBD_NOTIFY_OP_RELEASED_LOCK:
		rbd_handle_released_lock(rbd_dev, काष्ठा_v, &p);
		rbd_acknowledge_notअगरy(rbd_dev, notअगरy_id, cookie);
		अवरोध;
	हाल RBD_NOTIFY_OP_REQUEST_LOCK:
		ret = rbd_handle_request_lock(rbd_dev, काष्ठा_v, &p);
		अगर (ret <= 0)
			rbd_acknowledge_notअगरy_result(rbd_dev, notअगरy_id,
						      cookie, ret);
		अन्यथा
			rbd_acknowledge_notअगरy(rbd_dev, notअगरy_id, cookie);
		अवरोध;
	हाल RBD_NOTIFY_OP_HEADER_UPDATE:
		ret = rbd_dev_refresh(rbd_dev);
		अगर (ret)
			rbd_warn(rbd_dev, "refresh failed: %d", ret);

		rbd_acknowledge_notअगरy(rbd_dev, notअगरy_id, cookie);
		अवरोध;
	शेष:
		अगर (rbd_is_lock_owner(rbd_dev))
			rbd_acknowledge_notअगरy_result(rbd_dev, notअगरy_id,
						      cookie, -EOPNOTSUPP);
		अन्यथा
			rbd_acknowledge_notअगरy(rbd_dev, notअगरy_id, cookie);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम __rbd_unरेजिस्टर_watch(काष्ठा rbd_device *rbd_dev);

अटल व्योम rbd_watch_errcb(व्योम *arg, u64 cookie, पूर्णांक err)
अणु
	काष्ठा rbd_device *rbd_dev = arg;

	rbd_warn(rbd_dev, "encountered watch error: %d", err);

	करोwn_ग_लिखो(&rbd_dev->lock_rwsem);
	rbd_set_owner_cid(rbd_dev, &rbd_empty_cid);
	up_ग_लिखो(&rbd_dev->lock_rwsem);

	mutex_lock(&rbd_dev->watch_mutex);
	अगर (rbd_dev->watch_state == RBD_WATCH_STATE_REGISTERED) अणु
		__rbd_unरेजिस्टर_watch(rbd_dev);
		rbd_dev->watch_state = RBD_WATCH_STATE_ERROR;

		queue_delayed_work(rbd_dev->task_wq, &rbd_dev->watch_dwork, 0);
	पूर्ण
	mutex_unlock(&rbd_dev->watch_mutex);
पूर्ण

/*
 * watch_mutex must be locked
 */
अटल पूर्णांक __rbd_रेजिस्टर_watch(काष्ठा rbd_device *rbd_dev)
अणु
	काष्ठा ceph_osd_client *osdc = &rbd_dev->rbd_client->client->osdc;
	काष्ठा ceph_osd_linger_request *handle;

	rbd_निश्चित(!rbd_dev->watch_handle);
	करोut("%s rbd_dev %p\n", __func__, rbd_dev);

	handle = ceph_osdc_watch(osdc, &rbd_dev->header_oid,
				 &rbd_dev->header_oloc, rbd_watch_cb,
				 rbd_watch_errcb, rbd_dev);
	अगर (IS_ERR(handle))
		वापस PTR_ERR(handle);

	rbd_dev->watch_handle = handle;
	वापस 0;
पूर्ण

/*
 * watch_mutex must be locked
 */
अटल व्योम __rbd_unरेजिस्टर_watch(काष्ठा rbd_device *rbd_dev)
अणु
	काष्ठा ceph_osd_client *osdc = &rbd_dev->rbd_client->client->osdc;
	पूर्णांक ret;

	rbd_निश्चित(rbd_dev->watch_handle);
	करोut("%s rbd_dev %p\n", __func__, rbd_dev);

	ret = ceph_osdc_unwatch(osdc, rbd_dev->watch_handle);
	अगर (ret)
		rbd_warn(rbd_dev, "failed to unwatch: %d", ret);

	rbd_dev->watch_handle = शून्य;
पूर्ण

अटल पूर्णांक rbd_रेजिस्टर_watch(काष्ठा rbd_device *rbd_dev)
अणु
	पूर्णांक ret;

	mutex_lock(&rbd_dev->watch_mutex);
	rbd_निश्चित(rbd_dev->watch_state == RBD_WATCH_STATE_UNREGISTERED);
	ret = __rbd_रेजिस्टर_watch(rbd_dev);
	अगर (ret)
		जाओ out;

	rbd_dev->watch_state = RBD_WATCH_STATE_REGISTERED;
	rbd_dev->watch_cookie = rbd_dev->watch_handle->linger_id;

out:
	mutex_unlock(&rbd_dev->watch_mutex);
	वापस ret;
पूर्ण

अटल व्योम cancel_tasks_sync(काष्ठा rbd_device *rbd_dev)
अणु
	करोut("%s rbd_dev %p\n", __func__, rbd_dev);

	cancel_work_sync(&rbd_dev->acquired_lock_work);
	cancel_work_sync(&rbd_dev->released_lock_work);
	cancel_delayed_work_sync(&rbd_dev->lock_dwork);
	cancel_work_sync(&rbd_dev->unlock_work);
पूर्ण

/*
 * header_rwsem must not be held to aव्योम a deadlock with
 * rbd_dev_refresh() when flushing notअगरies.
 */
अटल व्योम rbd_unरेजिस्टर_watch(काष्ठा rbd_device *rbd_dev)
अणु
	cancel_tasks_sync(rbd_dev);

	mutex_lock(&rbd_dev->watch_mutex);
	अगर (rbd_dev->watch_state == RBD_WATCH_STATE_REGISTERED)
		__rbd_unरेजिस्टर_watch(rbd_dev);
	rbd_dev->watch_state = RBD_WATCH_STATE_UNREGISTERED;
	mutex_unlock(&rbd_dev->watch_mutex);

	cancel_delayed_work_sync(&rbd_dev->watch_dwork);
	ceph_osdc_flush_notअगरies(&rbd_dev->rbd_client->client->osdc);
पूर्ण

/*
 * lock_rwsem must be held क्रम ग_लिखो
 */
अटल व्योम rbd_reacquire_lock(काष्ठा rbd_device *rbd_dev)
अणु
	काष्ठा ceph_osd_client *osdc = &rbd_dev->rbd_client->client->osdc;
	अक्षर cookie[32];
	पूर्णांक ret;

	अगर (!rbd_quiesce_lock(rbd_dev))
		वापस;

	क्रमmat_lock_cookie(rbd_dev, cookie);
	ret = ceph_cls_set_cookie(osdc, &rbd_dev->header_oid,
				  &rbd_dev->header_oloc, RBD_LOCK_NAME,
				  CEPH_CLS_LOCK_EXCLUSIVE, rbd_dev->lock_cookie,
				  RBD_LOCK_TAG, cookie);
	अगर (ret) अणु
		अगर (ret != -EOPNOTSUPP)
			rbd_warn(rbd_dev, "failed to update lock cookie: %d",
				 ret);

		/*
		 * Lock cookie cannot be updated on older OSDs, so करो
		 * a manual release and queue an acquire.
		 */
		__rbd_release_lock(rbd_dev);
		queue_delayed_work(rbd_dev->task_wq, &rbd_dev->lock_dwork, 0);
	पूर्ण अन्यथा अणु
		__rbd_lock(rbd_dev, cookie);
		wake_lock_रुकोers(rbd_dev, 0);
	पूर्ण
पूर्ण

अटल व्योम rbd_reरेजिस्टर_watch(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा rbd_device *rbd_dev = container_of(to_delayed_work(work),
					    काष्ठा rbd_device, watch_dwork);
	पूर्णांक ret;

	करोut("%s rbd_dev %p\n", __func__, rbd_dev);

	mutex_lock(&rbd_dev->watch_mutex);
	अगर (rbd_dev->watch_state != RBD_WATCH_STATE_ERROR) अणु
		mutex_unlock(&rbd_dev->watch_mutex);
		वापस;
	पूर्ण

	ret = __rbd_रेजिस्टर_watch(rbd_dev);
	अगर (ret) अणु
		rbd_warn(rbd_dev, "failed to reregister watch: %d", ret);
		अगर (ret != -EBLOCKLISTED && ret != -ENOENT) अणु
			queue_delayed_work(rbd_dev->task_wq,
					   &rbd_dev->watch_dwork,
					   RBD_RETRY_DELAY);
			mutex_unlock(&rbd_dev->watch_mutex);
			वापस;
		पूर्ण

		mutex_unlock(&rbd_dev->watch_mutex);
		करोwn_ग_लिखो(&rbd_dev->lock_rwsem);
		wake_lock_रुकोers(rbd_dev, ret);
		up_ग_लिखो(&rbd_dev->lock_rwsem);
		वापस;
	पूर्ण

	rbd_dev->watch_state = RBD_WATCH_STATE_REGISTERED;
	rbd_dev->watch_cookie = rbd_dev->watch_handle->linger_id;
	mutex_unlock(&rbd_dev->watch_mutex);

	करोwn_ग_लिखो(&rbd_dev->lock_rwsem);
	अगर (rbd_dev->lock_state == RBD_LOCK_STATE_LOCKED)
		rbd_reacquire_lock(rbd_dev);
	up_ग_लिखो(&rbd_dev->lock_rwsem);

	ret = rbd_dev_refresh(rbd_dev);
	अगर (ret)
		rbd_warn(rbd_dev, "reregistration refresh failed: %d", ret);
पूर्ण

/*
 * Synchronous osd object method call.  Returns the number of bytes
 * वापसed in the outbound buffer, or a negative error code.
 */
अटल पूर्णांक rbd_obj_method_sync(काष्ठा rbd_device *rbd_dev,
			     काष्ठा ceph_object_id *oid,
			     काष्ठा ceph_object_locator *oloc,
			     स्थिर अक्षर *method_name,
			     स्थिर व्योम *outbound,
			     माप_प्रकार outbound_size,
			     व्योम *inbound,
			     माप_प्रकार inbound_size)
अणु
	काष्ठा ceph_osd_client *osdc = &rbd_dev->rbd_client->client->osdc;
	काष्ठा page *req_page = शून्य;
	काष्ठा page *reply_page;
	पूर्णांक ret;

	/*
	 * Method calls are ultimately पढ़ो operations.  The result
	 * should placed पूर्णांकo the inbound buffer provided.  They
	 * also supply outbound data--parameters क्रम the object
	 * method.  Currently अगर this is present it will be a
	 * snapshot id.
	 */
	अगर (outbound) अणु
		अगर (outbound_size > PAGE_SIZE)
			वापस -E2BIG;

		req_page = alloc_page(GFP_KERNEL);
		अगर (!req_page)
			वापस -ENOMEM;

		स_नकल(page_address(req_page), outbound, outbound_size);
	पूर्ण

	reply_page = alloc_page(GFP_KERNEL);
	अगर (!reply_page) अणु
		अगर (req_page)
			__मुक्त_page(req_page);
		वापस -ENOMEM;
	पूर्ण

	ret = ceph_osdc_call(osdc, oid, oloc, RBD_DRV_NAME, method_name,
			     CEPH_OSD_FLAG_READ, req_page, outbound_size,
			     &reply_page, &inbound_size);
	अगर (!ret) अणु
		स_नकल(inbound, page_address(reply_page), inbound_size);
		ret = inbound_size;
	पूर्ण

	अगर (req_page)
		__मुक्त_page(req_page);
	__मुक्त_page(reply_page);
	वापस ret;
पूर्ण

अटल व्योम rbd_queue_workfn(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा rbd_img_request *img_request =
	    container_of(work, काष्ठा rbd_img_request, work);
	काष्ठा rbd_device *rbd_dev = img_request->rbd_dev;
	क्रमागत obj_operation_type op_type = img_request->op_type;
	काष्ठा request *rq = blk_mq_rq_from_pdu(img_request);
	u64 offset = (u64)blk_rq_pos(rq) << SECTOR_SHIFT;
	u64 length = blk_rq_bytes(rq);
	u64 mapping_size;
	पूर्णांक result;

	/* Ignore/skip any zero-length requests */
	अगर (!length) अणु
		करोut("%s: zero-length request\n", __func__);
		result = 0;
		जाओ err_img_request;
	पूर्ण

	blk_mq_start_request(rq);

	करोwn_पढ़ो(&rbd_dev->header_rwsem);
	mapping_size = rbd_dev->mapping.size;
	rbd_img_capture_header(img_request);
	up_पढ़ो(&rbd_dev->header_rwsem);

	अगर (offset + length > mapping_size) अणु
		rbd_warn(rbd_dev, "beyond EOD (%llu~%llu > %llu)", offset,
			 length, mapping_size);
		result = -EIO;
		जाओ err_img_request;
	पूर्ण

	करोut("%s rbd_dev %p img_req %p %s %llu~%llu\n", __func__, rbd_dev,
	     img_request, obj_op_name(op_type), offset, length);

	अगर (op_type == OBJ_OP_DISCARD || op_type == OBJ_OP_ZEROOUT)
		result = rbd_img_fill_nodata(img_request, offset, length);
	अन्यथा
		result = rbd_img_fill_from_bio(img_request, offset, length,
					       rq->bio);
	अगर (result)
		जाओ err_img_request;

	rbd_img_handle_request(img_request, 0);
	वापस;

err_img_request:
	rbd_img_request_destroy(img_request);
	अगर (result)
		rbd_warn(rbd_dev, "%s %llx at %llx result %d",
			 obj_op_name(op_type), length, offset, result);
	blk_mq_end_request(rq, त्रुटि_सं_to_blk_status(result));
पूर्ण

अटल blk_status_t rbd_queue_rq(काष्ठा blk_mq_hw_ctx *hctx,
		स्थिर काष्ठा blk_mq_queue_data *bd)
अणु
	काष्ठा rbd_device *rbd_dev = hctx->queue->queuedata;
	काष्ठा rbd_img_request *img_req = blk_mq_rq_to_pdu(bd->rq);
	क्रमागत obj_operation_type op_type;

	चयन (req_op(bd->rq)) अणु
	हाल REQ_OP_DISCARD:
		op_type = OBJ_OP_DISCARD;
		अवरोध;
	हाल REQ_OP_WRITE_ZEROES:
		op_type = OBJ_OP_ZEROOUT;
		अवरोध;
	हाल REQ_OP_WRITE:
		op_type = OBJ_OP_WRITE;
		अवरोध;
	हाल REQ_OP_READ:
		op_type = OBJ_OP_READ;
		अवरोध;
	शेष:
		rbd_warn(rbd_dev, "unknown req_op %d", req_op(bd->rq));
		वापस BLK_STS_IOERR;
	पूर्ण

	rbd_img_request_init(img_req, rbd_dev, op_type);

	अगर (rbd_img_is_ग_लिखो(img_req)) अणु
		अगर (rbd_is_ro(rbd_dev)) अणु
			rbd_warn(rbd_dev, "%s on read-only mapping",
				 obj_op_name(img_req->op_type));
			वापस BLK_STS_IOERR;
		पूर्ण
		rbd_निश्चित(!rbd_is_snap(rbd_dev));
	पूर्ण

	INIT_WORK(&img_req->work, rbd_queue_workfn);
	queue_work(rbd_wq, &img_req->work);
	वापस BLK_STS_OK;
पूर्ण

अटल व्योम rbd_मुक्त_disk(काष्ठा rbd_device *rbd_dev)
अणु
	blk_cleanup_queue(rbd_dev->disk->queue);
	blk_mq_मुक्त_tag_set(&rbd_dev->tag_set);
	put_disk(rbd_dev->disk);
	rbd_dev->disk = शून्य;
पूर्ण

अटल पूर्णांक rbd_obj_पढ़ो_sync(काष्ठा rbd_device *rbd_dev,
			     काष्ठा ceph_object_id *oid,
			     काष्ठा ceph_object_locator *oloc,
			     व्योम *buf, पूर्णांक buf_len)

अणु
	काष्ठा ceph_osd_client *osdc = &rbd_dev->rbd_client->client->osdc;
	काष्ठा ceph_osd_request *req;
	काष्ठा page **pages;
	पूर्णांक num_pages = calc_pages_क्रम(0, buf_len);
	पूर्णांक ret;

	req = ceph_osdc_alloc_request(osdc, शून्य, 1, false, GFP_KERNEL);
	अगर (!req)
		वापस -ENOMEM;

	ceph_oid_copy(&req->r_base_oid, oid);
	ceph_oloc_copy(&req->r_base_oloc, oloc);
	req->r_flags = CEPH_OSD_FLAG_READ;

	pages = ceph_alloc_page_vector(num_pages, GFP_KERNEL);
	अगर (IS_ERR(pages)) अणु
		ret = PTR_ERR(pages);
		जाओ out_req;
	पूर्ण

	osd_req_op_extent_init(req, 0, CEPH_OSD_OP_READ, 0, buf_len, 0, 0);
	osd_req_op_extent_osd_data_pages(req, 0, pages, buf_len, 0, false,
					 true);

	ret = ceph_osdc_alloc_messages(req, GFP_KERNEL);
	अगर (ret)
		जाओ out_req;

	ceph_osdc_start_request(osdc, req, false);
	ret = ceph_osdc_रुको_request(osdc, req);
	अगर (ret >= 0)
		ceph_copy_from_page_vector(pages, buf, 0, ret);

out_req:
	ceph_osdc_put_request(req);
	वापस ret;
पूर्ण

/*
 * Read the complete header क्रम the given rbd device.  On successful
 * वापस, the rbd_dev->header field will contain up-to-date
 * inक्रमmation about the image.
 */
अटल पूर्णांक rbd_dev_v1_header_info(काष्ठा rbd_device *rbd_dev)
अणु
	काष्ठा rbd_image_header_ondisk *ondisk = शून्य;
	u32 snap_count = 0;
	u64 names_size = 0;
	u32 want_count;
	पूर्णांक ret;

	/*
	 * The complete header will include an array of its 64-bit
	 * snapshot ids, followed by the names of those snapshots as
	 * a contiguous block of NUL-terminated strings.  Note that
	 * the number of snapshots could change by the समय we पढ़ो
	 * it in, in which हाल we re-पढ़ो it.
	 */
	करो अणु
		माप_प्रकार size;

		kमुक्त(ondisk);

		size = माप (*ondisk);
		size += snap_count * माप (काष्ठा rbd_image_snap_ondisk);
		size += names_size;
		ondisk = kदो_स्मृति(size, GFP_KERNEL);
		अगर (!ondisk)
			वापस -ENOMEM;

		ret = rbd_obj_पढ़ो_sync(rbd_dev, &rbd_dev->header_oid,
					&rbd_dev->header_oloc, ondisk, size);
		अगर (ret < 0)
			जाओ out;
		अगर ((माप_प्रकार)ret < size) अणु
			ret = -ENXIO;
			rbd_warn(rbd_dev, "short header read (want %zd got %d)",
				size, ret);
			जाओ out;
		पूर्ण
		अगर (!rbd_dev_ondisk_valid(ondisk)) अणु
			ret = -ENXIO;
			rbd_warn(rbd_dev, "invalid header");
			जाओ out;
		पूर्ण

		names_size = le64_to_cpu(ondisk->snap_names_len);
		want_count = snap_count;
		snap_count = le32_to_cpu(ondisk->snap_count);
	पूर्ण जबतक (snap_count != want_count);

	ret = rbd_header_from_disk(rbd_dev, ondisk);
out:
	kमुक्त(ondisk);

	वापस ret;
पूर्ण

अटल व्योम rbd_dev_update_size(काष्ठा rbd_device *rbd_dev)
अणु
	sector_t size;

	/*
	 * If EXISTS is not set, rbd_dev->disk may be शून्य, so करोn't
	 * try to update its size.  If REMOVING is set, updating size
	 * is just useless work since the device can't be खोलोed.
	 */
	अगर (test_bit(RBD_DEV_FLAG_EXISTS, &rbd_dev->flags) &&
	    !test_bit(RBD_DEV_FLAG_REMOVING, &rbd_dev->flags)) अणु
		size = (sector_t)rbd_dev->mapping.size / SECTOR_SIZE;
		करोut("setting size to %llu sectors", (अचिन्हित दीर्घ दीर्घ)size);
		set_capacity_and_notअगरy(rbd_dev->disk, size);
	पूर्ण
पूर्ण

अटल पूर्णांक rbd_dev_refresh(काष्ठा rbd_device *rbd_dev)
अणु
	u64 mapping_size;
	पूर्णांक ret;

	करोwn_ग_लिखो(&rbd_dev->header_rwsem);
	mapping_size = rbd_dev->mapping.size;

	ret = rbd_dev_header_info(rbd_dev);
	अगर (ret)
		जाओ out;

	/*
	 * If there is a parent, see अगर it has disappeared due to the
	 * mapped image getting flattened.
	 */
	अगर (rbd_dev->parent) अणु
		ret = rbd_dev_v2_parent_info(rbd_dev);
		अगर (ret)
			जाओ out;
	पूर्ण

	rbd_निश्चित(!rbd_is_snap(rbd_dev));
	rbd_dev->mapping.size = rbd_dev->header.image_size;

out:
	up_ग_लिखो(&rbd_dev->header_rwsem);
	अगर (!ret && mapping_size != rbd_dev->mapping.size)
		rbd_dev_update_size(rbd_dev);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा blk_mq_ops rbd_mq_ops = अणु
	.queue_rq	= rbd_queue_rq,
पूर्ण;

अटल पूर्णांक rbd_init_disk(काष्ठा rbd_device *rbd_dev)
अणु
	काष्ठा gendisk *disk;
	काष्ठा request_queue *q;
	अचिन्हित पूर्णांक objset_bytes =
	    rbd_dev->layout.object_size * rbd_dev->layout.stripe_count;
	पूर्णांक err;

	/* create gendisk info */
	disk = alloc_disk(single_major ?
			  (1 << RBD_SINGLE_MAJOR_PART_SHIFT) :
			  RBD_MINORS_PER_MAJOR);
	अगर (!disk)
		वापस -ENOMEM;

	snम_लिखो(disk->disk_name, माप(disk->disk_name), RBD_DRV_NAME "%d",
		 rbd_dev->dev_id);
	disk->major = rbd_dev->major;
	disk->first_minor = rbd_dev->minor;
	अगर (single_major)
		disk->flags |= GENHD_FL_EXT_DEVT;
	disk->fops = &rbd_bd_ops;
	disk->निजी_data = rbd_dev;

	स_रखो(&rbd_dev->tag_set, 0, माप(rbd_dev->tag_set));
	rbd_dev->tag_set.ops = &rbd_mq_ops;
	rbd_dev->tag_set.queue_depth = rbd_dev->opts->queue_depth;
	rbd_dev->tag_set.numa_node = NUMA_NO_NODE;
	rbd_dev->tag_set.flags = BLK_MQ_F_SHOULD_MERGE;
	rbd_dev->tag_set.nr_hw_queues = num_present_cpus();
	rbd_dev->tag_set.cmd_size = माप(काष्ठा rbd_img_request);

	err = blk_mq_alloc_tag_set(&rbd_dev->tag_set);
	अगर (err)
		जाओ out_disk;

	q = blk_mq_init_queue(&rbd_dev->tag_set);
	अगर (IS_ERR(q)) अणु
		err = PTR_ERR(q);
		जाओ out_tag_set;
	पूर्ण

	blk_queue_flag_set(QUEUE_FLAG_NONROT, q);
	/* QUEUE_FLAG_ADD_RANDOM is off by शेष क्रम blk-mq */

	blk_queue_max_hw_sectors(q, objset_bytes >> SECTOR_SHIFT);
	q->limits.max_sectors = queue_max_hw_sectors(q);
	blk_queue_max_segments(q, अच_लघु_उच्च);
	blk_queue_max_segment_size(q, अच_पूर्णांक_उच्च);
	blk_queue_io_min(q, rbd_dev->opts->alloc_size);
	blk_queue_io_opt(q, rbd_dev->opts->alloc_size);

	अगर (rbd_dev->opts->trim) अणु
		blk_queue_flag_set(QUEUE_FLAG_DISCARD, q);
		q->limits.discard_granularity = rbd_dev->opts->alloc_size;
		blk_queue_max_discard_sectors(q, objset_bytes >> SECTOR_SHIFT);
		blk_queue_max_ग_लिखो_zeroes_sectors(q, objset_bytes >> SECTOR_SHIFT);
	पूर्ण

	अगर (!ceph_test_opt(rbd_dev->rbd_client->client, NOCRC))
		blk_queue_flag_set(QUEUE_FLAG_STABLE_WRITES, q);

	/*
	 * disk_release() expects a queue ref from add_disk() and will
	 * put it.  Hold an extra ref until add_disk() is called.
	 */
	WARN_ON(!blk_get_queue(q));
	disk->queue = q;
	q->queuedata = rbd_dev;

	rbd_dev->disk = disk;

	वापस 0;
out_tag_set:
	blk_mq_मुक्त_tag_set(&rbd_dev->tag_set);
out_disk:
	put_disk(disk);
	वापस err;
पूर्ण

/*
  sysfs
*/

अटल काष्ठा rbd_device *dev_to_rbd_dev(काष्ठा device *dev)
अणु
	वापस container_of(dev, काष्ठा rbd_device, dev);
पूर्ण

अटल sमाप_प्रकार rbd_size_show(काष्ठा device *dev,
			     काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा rbd_device *rbd_dev = dev_to_rbd_dev(dev);

	वापस प्र_लिखो(buf, "%llu\n",
		(अचिन्हित दीर्घ दीर्घ)rbd_dev->mapping.size);
पूर्ण

अटल sमाप_प्रकार rbd_features_show(काष्ठा device *dev,
			     काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा rbd_device *rbd_dev = dev_to_rbd_dev(dev);

	वापस प्र_लिखो(buf, "0x%016llx\n", rbd_dev->header.features);
पूर्ण

अटल sमाप_प्रकार rbd_major_show(काष्ठा device *dev,
			      काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा rbd_device *rbd_dev = dev_to_rbd_dev(dev);

	अगर (rbd_dev->major)
		वापस प्र_लिखो(buf, "%d\n", rbd_dev->major);

	वापस प्र_लिखो(buf, "(none)\n");
पूर्ण

अटल sमाप_प्रकार rbd_minor_show(काष्ठा device *dev,
			      काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा rbd_device *rbd_dev = dev_to_rbd_dev(dev);

	वापस प्र_लिखो(buf, "%d\n", rbd_dev->minor);
पूर्ण

अटल sमाप_प्रकार rbd_client_addr_show(काष्ठा device *dev,
				    काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा rbd_device *rbd_dev = dev_to_rbd_dev(dev);
	काष्ठा ceph_entity_addr *client_addr =
	    ceph_client_addr(rbd_dev->rbd_client->client);

	वापस प्र_लिखो(buf, "%pISpc/%u\n", &client_addr->in_addr,
		       le32_to_cpu(client_addr->nonce));
पूर्ण

अटल sमाप_प्रकार rbd_client_id_show(काष्ठा device *dev,
				  काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा rbd_device *rbd_dev = dev_to_rbd_dev(dev);

	वापस प्र_लिखो(buf, "client%lld\n",
		       ceph_client_gid(rbd_dev->rbd_client->client));
पूर्ण

अटल sमाप_प्रकार rbd_cluster_fsid_show(काष्ठा device *dev,
				     काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा rbd_device *rbd_dev = dev_to_rbd_dev(dev);

	वापस प्र_लिखो(buf, "%pU\n", &rbd_dev->rbd_client->client->fsid);
पूर्ण

अटल sमाप_प्रकार rbd_config_info_show(काष्ठा device *dev,
				    काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा rbd_device *rbd_dev = dev_to_rbd_dev(dev);

	अगर (!capable(CAP_SYS_ADMIN))
		वापस -EPERM;

	वापस प्र_लिखो(buf, "%s\n", rbd_dev->config_info);
पूर्ण

अटल sमाप_प्रकार rbd_pool_show(काष्ठा device *dev,
			     काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा rbd_device *rbd_dev = dev_to_rbd_dev(dev);

	वापस प्र_लिखो(buf, "%s\n", rbd_dev->spec->pool_name);
पूर्ण

अटल sमाप_प्रकार rbd_pool_id_show(काष्ठा device *dev,
			     काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा rbd_device *rbd_dev = dev_to_rbd_dev(dev);

	वापस प्र_लिखो(buf, "%llu\n",
			(अचिन्हित दीर्घ दीर्घ) rbd_dev->spec->pool_id);
पूर्ण

अटल sमाप_प्रकार rbd_pool_ns_show(काष्ठा device *dev,
				काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा rbd_device *rbd_dev = dev_to_rbd_dev(dev);

	वापस प्र_लिखो(buf, "%s\n", rbd_dev->spec->pool_ns ?: "");
पूर्ण

अटल sमाप_प्रकार rbd_name_show(काष्ठा device *dev,
			     काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा rbd_device *rbd_dev = dev_to_rbd_dev(dev);

	अगर (rbd_dev->spec->image_name)
		वापस प्र_लिखो(buf, "%s\n", rbd_dev->spec->image_name);

	वापस प्र_लिखो(buf, "(unknown)\n");
पूर्ण

अटल sमाप_प्रकार rbd_image_id_show(काष्ठा device *dev,
			     काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा rbd_device *rbd_dev = dev_to_rbd_dev(dev);

	वापस प्र_लिखो(buf, "%s\n", rbd_dev->spec->image_id);
पूर्ण

/*
 * Shows the name of the currently-mapped snapshot (or
 * RBD_SNAP_HEAD_NAME क्रम the base image).
 */
अटल sमाप_प्रकार rbd_snap_show(काष्ठा device *dev,
			     काष्ठा device_attribute *attr,
			     अक्षर *buf)
अणु
	काष्ठा rbd_device *rbd_dev = dev_to_rbd_dev(dev);

	वापस प्र_लिखो(buf, "%s\n", rbd_dev->spec->snap_name);
पूर्ण

अटल sमाप_प्रकार rbd_snap_id_show(काष्ठा device *dev,
				काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा rbd_device *rbd_dev = dev_to_rbd_dev(dev);

	वापस प्र_लिखो(buf, "%llu\n", rbd_dev->spec->snap_id);
पूर्ण

/*
 * For a v2 image, shows the chain of parent images, separated by empty
 * lines.  For v1 images or अगर there is no parent, shows "(no parent
 * image)".
 */
अटल sमाप_प्रकार rbd_parent_show(काष्ठा device *dev,
			       काष्ठा device_attribute *attr,
			       अक्षर *buf)
अणु
	काष्ठा rbd_device *rbd_dev = dev_to_rbd_dev(dev);
	sमाप_प्रकार count = 0;

	अगर (!rbd_dev->parent)
		वापस प्र_लिखो(buf, "(no parent image)\n");

	क्रम ( ; rbd_dev->parent; rbd_dev = rbd_dev->parent) अणु
		काष्ठा rbd_spec *spec = rbd_dev->parent_spec;

		count += प्र_लिखो(&buf[count], "%s"
			    "pool_id %llu\npool_name %s\n"
			    "pool_ns %s\n"
			    "image_id %s\nimage_name %s\n"
			    "snap_id %llu\nsnap_name %s\n"
			    "overlap %llu\n",
			    !count ? "" : "\n", /* first? */
			    spec->pool_id, spec->pool_name,
			    spec->pool_ns ?: "",
			    spec->image_id, spec->image_name ?: "(unknown)",
			    spec->snap_id, spec->snap_name,
			    rbd_dev->parent_overlap);
	पूर्ण

	वापस count;
पूर्ण

अटल sमाप_प्रकार rbd_image_refresh(काष्ठा device *dev,
				 काष्ठा device_attribute *attr,
				 स्थिर अक्षर *buf,
				 माप_प्रकार size)
अणु
	काष्ठा rbd_device *rbd_dev = dev_to_rbd_dev(dev);
	पूर्णांक ret;

	अगर (!capable(CAP_SYS_ADMIN))
		वापस -EPERM;

	ret = rbd_dev_refresh(rbd_dev);
	अगर (ret)
		वापस ret;

	वापस size;
पूर्ण

अटल DEVICE_ATTR(size, 0444, rbd_size_show, शून्य);
अटल DEVICE_ATTR(features, 0444, rbd_features_show, शून्य);
अटल DEVICE_ATTR(major, 0444, rbd_major_show, शून्य);
अटल DEVICE_ATTR(minor, 0444, rbd_minor_show, शून्य);
अटल DEVICE_ATTR(client_addr, 0444, rbd_client_addr_show, शून्य);
अटल DEVICE_ATTR(client_id, 0444, rbd_client_id_show, शून्य);
अटल DEVICE_ATTR(cluster_fsid, 0444, rbd_cluster_fsid_show, शून्य);
अटल DEVICE_ATTR(config_info, 0400, rbd_config_info_show, शून्य);
अटल DEVICE_ATTR(pool, 0444, rbd_pool_show, शून्य);
अटल DEVICE_ATTR(pool_id, 0444, rbd_pool_id_show, शून्य);
अटल DEVICE_ATTR(pool_ns, 0444, rbd_pool_ns_show, शून्य);
अटल DEVICE_ATTR(name, 0444, rbd_name_show, शून्य);
अटल DEVICE_ATTR(image_id, 0444, rbd_image_id_show, शून्य);
अटल DEVICE_ATTR(refresh, 0200, शून्य, rbd_image_refresh);
अटल DEVICE_ATTR(current_snap, 0444, rbd_snap_show, शून्य);
अटल DEVICE_ATTR(snap_id, 0444, rbd_snap_id_show, शून्य);
अटल DEVICE_ATTR(parent, 0444, rbd_parent_show, शून्य);

अटल काष्ठा attribute *rbd_attrs[] = अणु
	&dev_attr_size.attr,
	&dev_attr_features.attr,
	&dev_attr_major.attr,
	&dev_attr_minor.attr,
	&dev_attr_client_addr.attr,
	&dev_attr_client_id.attr,
	&dev_attr_cluster_fsid.attr,
	&dev_attr_config_info.attr,
	&dev_attr_pool.attr,
	&dev_attr_pool_id.attr,
	&dev_attr_pool_ns.attr,
	&dev_attr_name.attr,
	&dev_attr_image_id.attr,
	&dev_attr_current_snap.attr,
	&dev_attr_snap_id.attr,
	&dev_attr_parent.attr,
	&dev_attr_refresh.attr,
	शून्य
पूर्ण;

अटल काष्ठा attribute_group rbd_attr_group = अणु
	.attrs = rbd_attrs,
पूर्ण;

अटल स्थिर काष्ठा attribute_group *rbd_attr_groups[] = अणु
	&rbd_attr_group,
	शून्य
पूर्ण;

अटल व्योम rbd_dev_release(काष्ठा device *dev);

अटल स्थिर काष्ठा device_type rbd_device_type = अणु
	.name		= "rbd",
	.groups		= rbd_attr_groups,
	.release	= rbd_dev_release,
पूर्ण;

अटल काष्ठा rbd_spec *rbd_spec_get(काष्ठा rbd_spec *spec)
अणु
	kref_get(&spec->kref);

	वापस spec;
पूर्ण

अटल व्योम rbd_spec_मुक्त(काष्ठा kref *kref);
अटल व्योम rbd_spec_put(काष्ठा rbd_spec *spec)
अणु
	अगर (spec)
		kref_put(&spec->kref, rbd_spec_मुक्त);
पूर्ण

अटल काष्ठा rbd_spec *rbd_spec_alloc(व्योम)
अणु
	काष्ठा rbd_spec *spec;

	spec = kzalloc(माप (*spec), GFP_KERNEL);
	अगर (!spec)
		वापस शून्य;

	spec->pool_id = CEPH_NOPOOL;
	spec->snap_id = CEPH_NOSNAP;
	kref_init(&spec->kref);

	वापस spec;
पूर्ण

अटल व्योम rbd_spec_मुक्त(काष्ठा kref *kref)
अणु
	काष्ठा rbd_spec *spec = container_of(kref, काष्ठा rbd_spec, kref);

	kमुक्त(spec->pool_name);
	kमुक्त(spec->pool_ns);
	kमुक्त(spec->image_id);
	kमुक्त(spec->image_name);
	kमुक्त(spec->snap_name);
	kमुक्त(spec);
पूर्ण

अटल व्योम rbd_dev_मुक्त(काष्ठा rbd_device *rbd_dev)
अणु
	WARN_ON(rbd_dev->watch_state != RBD_WATCH_STATE_UNREGISTERED);
	WARN_ON(rbd_dev->lock_state != RBD_LOCK_STATE_UNLOCKED);

	ceph_oid_destroy(&rbd_dev->header_oid);
	ceph_oloc_destroy(&rbd_dev->header_oloc);
	kमुक्त(rbd_dev->config_info);

	rbd_put_client(rbd_dev->rbd_client);
	rbd_spec_put(rbd_dev->spec);
	kमुक्त(rbd_dev->opts);
	kमुक्त(rbd_dev);
पूर्ण

अटल व्योम rbd_dev_release(काष्ठा device *dev)
अणु
	काष्ठा rbd_device *rbd_dev = dev_to_rbd_dev(dev);
	bool need_put = !!rbd_dev->opts;

	अगर (need_put) अणु
		destroy_workqueue(rbd_dev->task_wq);
		ida_simple_हटाओ(&rbd_dev_id_ida, rbd_dev->dev_id);
	पूर्ण

	rbd_dev_मुक्त(rbd_dev);

	/*
	 * This is racy, but way better than putting module outside of
	 * the release callback.  The race winकरोw is pretty small, so
	 * करोing something similar to dm (dm-builtin.c) is overसमाप्त.
	 */
	अगर (need_put)
		module_put(THIS_MODULE);
पूर्ण

अटल काष्ठा rbd_device *__rbd_dev_create(काष्ठा rbd_client *rbdc,
					   काष्ठा rbd_spec *spec)
अणु
	काष्ठा rbd_device *rbd_dev;

	rbd_dev = kzalloc(माप(*rbd_dev), GFP_KERNEL);
	अगर (!rbd_dev)
		वापस शून्य;

	spin_lock_init(&rbd_dev->lock);
	INIT_LIST_HEAD(&rbd_dev->node);
	init_rwsem(&rbd_dev->header_rwsem);

	rbd_dev->header.data_pool_id = CEPH_NOPOOL;
	ceph_oid_init(&rbd_dev->header_oid);
	rbd_dev->header_oloc.pool = spec->pool_id;
	अगर (spec->pool_ns) अणु
		WARN_ON(!*spec->pool_ns);
		rbd_dev->header_oloc.pool_ns =
		    ceph_find_or_create_string(spec->pool_ns,
					       म_माप(spec->pool_ns));
	पूर्ण

	mutex_init(&rbd_dev->watch_mutex);
	rbd_dev->watch_state = RBD_WATCH_STATE_UNREGISTERED;
	INIT_DELAYED_WORK(&rbd_dev->watch_dwork, rbd_reरेजिस्टर_watch);

	init_rwsem(&rbd_dev->lock_rwsem);
	rbd_dev->lock_state = RBD_LOCK_STATE_UNLOCKED;
	INIT_WORK(&rbd_dev->acquired_lock_work, rbd_notअगरy_acquired_lock);
	INIT_WORK(&rbd_dev->released_lock_work, rbd_notअगरy_released_lock);
	INIT_DELAYED_WORK(&rbd_dev->lock_dwork, rbd_acquire_lock);
	INIT_WORK(&rbd_dev->unlock_work, rbd_release_lock_work);
	spin_lock_init(&rbd_dev->lock_lists_lock);
	INIT_LIST_HEAD(&rbd_dev->acquiring_list);
	INIT_LIST_HEAD(&rbd_dev->running_list);
	init_completion(&rbd_dev->acquire_रुको);
	init_completion(&rbd_dev->releasing_रुको);

	spin_lock_init(&rbd_dev->object_map_lock);

	rbd_dev->dev.bus = &rbd_bus_type;
	rbd_dev->dev.type = &rbd_device_type;
	rbd_dev->dev.parent = &rbd_root_dev;
	device_initialize(&rbd_dev->dev);

	rbd_dev->rbd_client = rbdc;
	rbd_dev->spec = spec;

	वापस rbd_dev;
पूर्ण

/*
 * Create a mapping rbd_dev.
 */
अटल काष्ठा rbd_device *rbd_dev_create(काष्ठा rbd_client *rbdc,
					 काष्ठा rbd_spec *spec,
					 काष्ठा rbd_options *opts)
अणु
	काष्ठा rbd_device *rbd_dev;

	rbd_dev = __rbd_dev_create(rbdc, spec);
	अगर (!rbd_dev)
		वापस शून्य;

	rbd_dev->opts = opts;

	/* get an id and fill in device name */
	rbd_dev->dev_id = ida_simple_get(&rbd_dev_id_ida, 0,
					 minor_to_rbd_dev_id(1 << MINORBITS),
					 GFP_KERNEL);
	अगर (rbd_dev->dev_id < 0)
		जाओ fail_rbd_dev;

	प्र_लिखो(rbd_dev->name, RBD_DRV_NAME "%d", rbd_dev->dev_id);
	rbd_dev->task_wq = alloc_ordered_workqueue("%s-tasks", WQ_MEM_RECLAIM,
						   rbd_dev->name);
	अगर (!rbd_dev->task_wq)
		जाओ fail_dev_id;

	/* we have a ref from करो_rbd_add() */
	__module_get(THIS_MODULE);

	करोut("%s rbd_dev %p dev_id %d\n", __func__, rbd_dev, rbd_dev->dev_id);
	वापस rbd_dev;

fail_dev_id:
	ida_simple_हटाओ(&rbd_dev_id_ida, rbd_dev->dev_id);
fail_rbd_dev:
	rbd_dev_मुक्त(rbd_dev);
	वापस शून्य;
पूर्ण

अटल व्योम rbd_dev_destroy(काष्ठा rbd_device *rbd_dev)
अणु
	अगर (rbd_dev)
		put_device(&rbd_dev->dev);
पूर्ण

/*
 * Get the size and object order क्रम an image snapshot, or अगर
 * snap_id is CEPH_NOSNAP, माला_लो this inक्रमmation क्रम the base
 * image.
 */
अटल पूर्णांक _rbd_dev_v2_snap_size(काष्ठा rbd_device *rbd_dev, u64 snap_id,
				u8 *order, u64 *snap_size)
अणु
	__le64 snapid = cpu_to_le64(snap_id);
	पूर्णांक ret;
	काष्ठा अणु
		u8 order;
		__le64 size;
	पूर्ण __attribute__ ((packed)) size_buf = अणु 0 पूर्ण;

	ret = rbd_obj_method_sync(rbd_dev, &rbd_dev->header_oid,
				  &rbd_dev->header_oloc, "get_size",
				  &snapid, माप(snapid),
				  &size_buf, माप(size_buf));
	करोut("%s: rbd_obj_method_sync returned %d\n", __func__, ret);
	अगर (ret < 0)
		वापस ret;
	अगर (ret < माप (size_buf))
		वापस -दुस्फल;

	अगर (order) अणु
		*order = size_buf.order;
		करोut("  order %u", (अचिन्हित पूर्णांक)*order);
	पूर्ण
	*snap_size = le64_to_cpu(size_buf.size);

	करोut("  snap_id 0x%016llx snap_size = %llu\n",
		(अचिन्हित दीर्घ दीर्घ)snap_id,
		(अचिन्हित दीर्घ दीर्घ)*snap_size);

	वापस 0;
पूर्ण

अटल पूर्णांक rbd_dev_v2_image_size(काष्ठा rbd_device *rbd_dev)
अणु
	वापस _rbd_dev_v2_snap_size(rbd_dev, CEPH_NOSNAP,
					&rbd_dev->header.obj_order,
					&rbd_dev->header.image_size);
पूर्ण

अटल पूर्णांक rbd_dev_v2_object_prefix(काष्ठा rbd_device *rbd_dev)
अणु
	माप_प्रकार size;
	व्योम *reply_buf;
	पूर्णांक ret;
	व्योम *p;

	/* Response will be an encoded string, which includes a length */
	size = माप(__le32) + RBD_OBJ_PREFIX_LEN_MAX;
	reply_buf = kzalloc(size, GFP_KERNEL);
	अगर (!reply_buf)
		वापस -ENOMEM;

	ret = rbd_obj_method_sync(rbd_dev, &rbd_dev->header_oid,
				  &rbd_dev->header_oloc, "get_object_prefix",
				  शून्य, 0, reply_buf, size);
	करोut("%s: rbd_obj_method_sync returned %d\n", __func__, ret);
	अगर (ret < 0)
		जाओ out;

	p = reply_buf;
	rbd_dev->header.object_prefix = ceph_extract_encoded_string(&p,
						p + ret, शून्य, GFP_NOIO);
	ret = 0;

	अगर (IS_ERR(rbd_dev->header.object_prefix)) अणु
		ret = PTR_ERR(rbd_dev->header.object_prefix);
		rbd_dev->header.object_prefix = शून्य;
	पूर्ण अन्यथा अणु
		करोut("  object_prefix = %s\n", rbd_dev->header.object_prefix);
	पूर्ण
out:
	kमुक्त(reply_buf);

	वापस ret;
पूर्ण

अटल पूर्णांक _rbd_dev_v2_snap_features(काष्ठा rbd_device *rbd_dev, u64 snap_id,
				     bool पढ़ो_only, u64 *snap_features)
अणु
	काष्ठा अणु
		__le64 snap_id;
		u8 पढ़ो_only;
	पूर्ण features_in;
	काष्ठा अणु
		__le64 features;
		__le64 incompat;
	पूर्ण __attribute__ ((packed)) features_buf = अणु 0 पूर्ण;
	u64 unsup;
	पूर्णांक ret;

	features_in.snap_id = cpu_to_le64(snap_id);
	features_in.पढ़ो_only = पढ़ो_only;

	ret = rbd_obj_method_sync(rbd_dev, &rbd_dev->header_oid,
				  &rbd_dev->header_oloc, "get_features",
				  &features_in, माप(features_in),
				  &features_buf, माप(features_buf));
	करोut("%s: rbd_obj_method_sync returned %d\n", __func__, ret);
	अगर (ret < 0)
		वापस ret;
	अगर (ret < माप (features_buf))
		वापस -दुस्फल;

	unsup = le64_to_cpu(features_buf.incompat) & ~RBD_FEATURES_SUPPORTED;
	अगर (unsup) अणु
		rbd_warn(rbd_dev, "image uses unsupported features: 0x%llx",
			 unsup);
		वापस -ENXIO;
	पूर्ण

	*snap_features = le64_to_cpu(features_buf.features);

	करोut("  snap_id 0x%016llx features = 0x%016llx incompat = 0x%016llx\n",
		(अचिन्हित दीर्घ दीर्घ)snap_id,
		(अचिन्हित दीर्घ दीर्घ)*snap_features,
		(अचिन्हित दीर्घ दीर्घ)le64_to_cpu(features_buf.incompat));

	वापस 0;
पूर्ण

अटल पूर्णांक rbd_dev_v2_features(काष्ठा rbd_device *rbd_dev)
अणु
	वापस _rbd_dev_v2_snap_features(rbd_dev, CEPH_NOSNAP,
					 rbd_is_ro(rbd_dev),
					 &rbd_dev->header.features);
पूर्ण

/*
 * These are generic image flags, but since they are used only क्रम
 * object map, store them in rbd_dev->object_map_flags.
 *
 * For the same reason, this function is called only on object map
 * (re)load and not on header refresh.
 */
अटल पूर्णांक rbd_dev_v2_get_flags(काष्ठा rbd_device *rbd_dev)
अणु
	__le64 snapid = cpu_to_le64(rbd_dev->spec->snap_id);
	__le64 flags;
	पूर्णांक ret;

	ret = rbd_obj_method_sync(rbd_dev, &rbd_dev->header_oid,
				  &rbd_dev->header_oloc, "get_flags",
				  &snapid, माप(snapid),
				  &flags, माप(flags));
	अगर (ret < 0)
		वापस ret;
	अगर (ret < माप(flags))
		वापस -EBADMSG;

	rbd_dev->object_map_flags = le64_to_cpu(flags);
	वापस 0;
पूर्ण

काष्ठा parent_image_info अणु
	u64		pool_id;
	स्थिर अक्षर	*pool_ns;
	स्थिर अक्षर	*image_id;
	u64		snap_id;

	bool		has_overlap;
	u64		overlap;
पूर्ण;

/*
 * The caller is responsible क्रम @pii.
 */
अटल पूर्णांक decode_parent_image_spec(व्योम **p, व्योम *end,
				    काष्ठा parent_image_info *pii)
अणु
	u8 काष्ठा_v;
	u32 काष्ठा_len;
	पूर्णांक ret;

	ret = ceph_start_decoding(p, end, 1, "ParentImageSpec",
				  &काष्ठा_v, &काष्ठा_len);
	अगर (ret)
		वापस ret;

	ceph_decode_64_safe(p, end, pii->pool_id, e_inval);
	pii->pool_ns = ceph_extract_encoded_string(p, end, शून्य, GFP_KERNEL);
	अगर (IS_ERR(pii->pool_ns)) अणु
		ret = PTR_ERR(pii->pool_ns);
		pii->pool_ns = शून्य;
		वापस ret;
	पूर्ण
	pii->image_id = ceph_extract_encoded_string(p, end, शून्य, GFP_KERNEL);
	अगर (IS_ERR(pii->image_id)) अणु
		ret = PTR_ERR(pii->image_id);
		pii->image_id = शून्य;
		वापस ret;
	पूर्ण
	ceph_decode_64_safe(p, end, pii->snap_id, e_inval);
	वापस 0;

e_inval:
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक __get_parent_info(काष्ठा rbd_device *rbd_dev,
			     काष्ठा page *req_page,
			     काष्ठा page *reply_page,
			     काष्ठा parent_image_info *pii)
अणु
	काष्ठा ceph_osd_client *osdc = &rbd_dev->rbd_client->client->osdc;
	माप_प्रकार reply_len = PAGE_SIZE;
	व्योम *p, *end;
	पूर्णांक ret;

	ret = ceph_osdc_call(osdc, &rbd_dev->header_oid, &rbd_dev->header_oloc,
			     "rbd", "parent_get", CEPH_OSD_FLAG_READ,
			     req_page, माप(u64), &reply_page, &reply_len);
	अगर (ret)
		वापस ret == -EOPNOTSUPP ? 1 : ret;

	p = page_address(reply_page);
	end = p + reply_len;
	ret = decode_parent_image_spec(&p, end, pii);
	अगर (ret)
		वापस ret;

	ret = ceph_osdc_call(osdc, &rbd_dev->header_oid, &rbd_dev->header_oloc,
			     "rbd", "parent_overlap_get", CEPH_OSD_FLAG_READ,
			     req_page, माप(u64), &reply_page, &reply_len);
	अगर (ret)
		वापस ret;

	p = page_address(reply_page);
	end = p + reply_len;
	ceph_decode_8_safe(&p, end, pii->has_overlap, e_inval);
	अगर (pii->has_overlap)
		ceph_decode_64_safe(&p, end, pii->overlap, e_inval);

	वापस 0;

e_inval:
	वापस -EINVAL;
पूर्ण

/*
 * The caller is responsible क्रम @pii.
 */
अटल पूर्णांक __get_parent_info_legacy(काष्ठा rbd_device *rbd_dev,
				    काष्ठा page *req_page,
				    काष्ठा page *reply_page,
				    काष्ठा parent_image_info *pii)
अणु
	काष्ठा ceph_osd_client *osdc = &rbd_dev->rbd_client->client->osdc;
	माप_प्रकार reply_len = PAGE_SIZE;
	व्योम *p, *end;
	पूर्णांक ret;

	ret = ceph_osdc_call(osdc, &rbd_dev->header_oid, &rbd_dev->header_oloc,
			     "rbd", "get_parent", CEPH_OSD_FLAG_READ,
			     req_page, माप(u64), &reply_page, &reply_len);
	अगर (ret)
		वापस ret;

	p = page_address(reply_page);
	end = p + reply_len;
	ceph_decode_64_safe(&p, end, pii->pool_id, e_inval);
	pii->image_id = ceph_extract_encoded_string(&p, end, शून्य, GFP_KERNEL);
	अगर (IS_ERR(pii->image_id)) अणु
		ret = PTR_ERR(pii->image_id);
		pii->image_id = शून्य;
		वापस ret;
	पूर्ण
	ceph_decode_64_safe(&p, end, pii->snap_id, e_inval);
	pii->has_overlap = true;
	ceph_decode_64_safe(&p, end, pii->overlap, e_inval);

	वापस 0;

e_inval:
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक get_parent_info(काष्ठा rbd_device *rbd_dev,
			   काष्ठा parent_image_info *pii)
अणु
	काष्ठा page *req_page, *reply_page;
	व्योम *p;
	पूर्णांक ret;

	req_page = alloc_page(GFP_KERNEL);
	अगर (!req_page)
		वापस -ENOMEM;

	reply_page = alloc_page(GFP_KERNEL);
	अगर (!reply_page) अणु
		__मुक्त_page(req_page);
		वापस -ENOMEM;
	पूर्ण

	p = page_address(req_page);
	ceph_encode_64(&p, rbd_dev->spec->snap_id);
	ret = __get_parent_info(rbd_dev, req_page, reply_page, pii);
	अगर (ret > 0)
		ret = __get_parent_info_legacy(rbd_dev, req_page, reply_page,
					       pii);

	__मुक्त_page(req_page);
	__मुक्त_page(reply_page);
	वापस ret;
पूर्ण

अटल पूर्णांक rbd_dev_v2_parent_info(काष्ठा rbd_device *rbd_dev)
अणु
	काष्ठा rbd_spec *parent_spec;
	काष्ठा parent_image_info pii = अणु 0 पूर्ण;
	पूर्णांक ret;

	parent_spec = rbd_spec_alloc();
	अगर (!parent_spec)
		वापस -ENOMEM;

	ret = get_parent_info(rbd_dev, &pii);
	अगर (ret)
		जाओ out_err;

	करोut("%s pool_id %llu pool_ns %s image_id %s snap_id %llu has_overlap %d overlap %llu\n",
	     __func__, pii.pool_id, pii.pool_ns, pii.image_id, pii.snap_id,
	     pii.has_overlap, pii.overlap);

	अगर (pii.pool_id == CEPH_NOPOOL || !pii.has_overlap) अणु
		/*
		 * Either the parent never existed, or we have
		 * record of it but the image got flattened so it no
		 * दीर्घer has a parent.  When the parent of a
		 * layered image disappears we immediately set the
		 * overlap to 0.  The effect of this is that all new
		 * requests will be treated as अगर the image had no
		 * parent.
		 *
		 * If !pii.has_overlap, the parent image spec is not
		 * applicable.  It's there to aव्योम duplication in each
		 * snapshot record.
		 */
		अगर (rbd_dev->parent_overlap) अणु
			rbd_dev->parent_overlap = 0;
			rbd_dev_parent_put(rbd_dev);
			pr_info("%s: clone image has been flattened\n",
				rbd_dev->disk->disk_name);
		पूर्ण

		जाओ out;	/* No parent?  No problem. */
	पूर्ण

	/* The ceph file layout needs to fit pool id in 32 bits */

	ret = -EIO;
	अगर (pii.pool_id > (u64)U32_MAX) अणु
		rbd_warn(शून्य, "parent pool id too large (%llu > %u)",
			(अचिन्हित दीर्घ दीर्घ)pii.pool_id, U32_MAX);
		जाओ out_err;
	पूर्ण

	/*
	 * The parent won't change (except when the clone is
	 * flattened, alपढ़ोy handled that).  So we only need to
	 * record the parent spec we have not alपढ़ोy करोne so.
	 */
	अगर (!rbd_dev->parent_spec) अणु
		parent_spec->pool_id = pii.pool_id;
		अगर (pii.pool_ns && *pii.pool_ns) अणु
			parent_spec->pool_ns = pii.pool_ns;
			pii.pool_ns = शून्य;
		पूर्ण
		parent_spec->image_id = pii.image_id;
		pii.image_id = शून्य;
		parent_spec->snap_id = pii.snap_id;

		rbd_dev->parent_spec = parent_spec;
		parent_spec = शून्य;	/* rbd_dev now owns this */
	पूर्ण

	/*
	 * We always update the parent overlap.  If it's zero we issue
	 * a warning, as we will proceed as अगर there was no parent.
	 */
	अगर (!pii.overlap) अणु
		अगर (parent_spec) अणु
			/* refresh, careful to warn just once */
			अगर (rbd_dev->parent_overlap)
				rbd_warn(rbd_dev,
				    "clone now standalone (overlap became 0)");
		पूर्ण अन्यथा अणु
			/* initial probe */
			rbd_warn(rbd_dev, "clone is standalone (overlap 0)");
		पूर्ण
	पूर्ण
	rbd_dev->parent_overlap = pii.overlap;

out:
	ret = 0;
out_err:
	kमुक्त(pii.pool_ns);
	kमुक्त(pii.image_id);
	rbd_spec_put(parent_spec);
	वापस ret;
पूर्ण

अटल पूर्णांक rbd_dev_v2_striping_info(काष्ठा rbd_device *rbd_dev)
अणु
	काष्ठा अणु
		__le64 stripe_unit;
		__le64 stripe_count;
	पूर्ण __attribute__ ((packed)) striping_info_buf = अणु 0 पूर्ण;
	माप_प्रकार size = माप (striping_info_buf);
	व्योम *p;
	पूर्णांक ret;

	ret = rbd_obj_method_sync(rbd_dev, &rbd_dev->header_oid,
				&rbd_dev->header_oloc, "get_stripe_unit_count",
				शून्य, 0, &striping_info_buf, size);
	करोut("%s: rbd_obj_method_sync returned %d\n", __func__, ret);
	अगर (ret < 0)
		वापस ret;
	अगर (ret < size)
		वापस -दुस्फल;

	p = &striping_info_buf;
	rbd_dev->header.stripe_unit = ceph_decode_64(&p);
	rbd_dev->header.stripe_count = ceph_decode_64(&p);
	वापस 0;
पूर्ण

अटल पूर्णांक rbd_dev_v2_data_pool(काष्ठा rbd_device *rbd_dev)
अणु
	__le64 data_pool_id;
	पूर्णांक ret;

	ret = rbd_obj_method_sync(rbd_dev, &rbd_dev->header_oid,
				  &rbd_dev->header_oloc, "get_data_pool",
				  शून्य, 0, &data_pool_id, माप(data_pool_id));
	अगर (ret < 0)
		वापस ret;
	अगर (ret < माप(data_pool_id))
		वापस -EBADMSG;

	rbd_dev->header.data_pool_id = le64_to_cpu(data_pool_id);
	WARN_ON(rbd_dev->header.data_pool_id == CEPH_NOPOOL);
	वापस 0;
पूर्ण

अटल अक्षर *rbd_dev_image_name(काष्ठा rbd_device *rbd_dev)
अणु
	CEPH_DEFINE_OID_ONSTACK(oid);
	माप_प्रकार image_id_size;
	अक्षर *image_id;
	व्योम *p;
	व्योम *end;
	माप_प्रकार size;
	व्योम *reply_buf = शून्य;
	माप_प्रकार len = 0;
	अक्षर *image_name = शून्य;
	पूर्णांक ret;

	rbd_निश्चित(!rbd_dev->spec->image_name);

	len = म_माप(rbd_dev->spec->image_id);
	image_id_size = माप (__le32) + len;
	image_id = kदो_स्मृति(image_id_size, GFP_KERNEL);
	अगर (!image_id)
		वापस शून्य;

	p = image_id;
	end = image_id + image_id_size;
	ceph_encode_string(&p, end, rbd_dev->spec->image_id, (u32)len);

	size = माप (__le32) + RBD_IMAGE_NAME_LEN_MAX;
	reply_buf = kदो_स्मृति(size, GFP_KERNEL);
	अगर (!reply_buf)
		जाओ out;

	ceph_oid_म_लिखो(&oid, "%s", RBD_सूचीECTORY);
	ret = rbd_obj_method_sync(rbd_dev, &oid, &rbd_dev->header_oloc,
				  "dir_get_name", image_id, image_id_size,
				  reply_buf, size);
	अगर (ret < 0)
		जाओ out;
	p = reply_buf;
	end = reply_buf + ret;

	image_name = ceph_extract_encoded_string(&p, end, &len, GFP_KERNEL);
	अगर (IS_ERR(image_name))
		image_name = शून्य;
	अन्यथा
		करोut("%s: name is %s len is %zd\n", __func__, image_name, len);
out:
	kमुक्त(reply_buf);
	kमुक्त(image_id);

	वापस image_name;
पूर्ण

अटल u64 rbd_v1_snap_id_by_name(काष्ठा rbd_device *rbd_dev, स्थिर अक्षर *name)
अणु
	काष्ठा ceph_snap_context *snapc = rbd_dev->header.snapc;
	स्थिर अक्षर *snap_name;
	u32 which = 0;

	/* Skip over names until we find the one we are looking क्रम */

	snap_name = rbd_dev->header.snap_names;
	जबतक (which < snapc->num_snaps) अणु
		अगर (!म_भेद(name, snap_name))
			वापस snapc->snaps[which];
		snap_name += म_माप(snap_name) + 1;
		which++;
	पूर्ण
	वापस CEPH_NOSNAP;
पूर्ण

अटल u64 rbd_v2_snap_id_by_name(काष्ठा rbd_device *rbd_dev, स्थिर अक्षर *name)
अणु
	काष्ठा ceph_snap_context *snapc = rbd_dev->header.snapc;
	u32 which;
	bool found = false;
	u64 snap_id;

	क्रम (which = 0; !found && which < snapc->num_snaps; which++) अणु
		स्थिर अक्षर *snap_name;

		snap_id = snapc->snaps[which];
		snap_name = rbd_dev_v2_snap_name(rbd_dev, snap_id);
		अगर (IS_ERR(snap_name)) अणु
			/* ignore no-दीर्घer existing snapshots */
			अगर (PTR_ERR(snap_name) == -ENOENT)
				जारी;
			अन्यथा
				अवरोध;
		पूर्ण
		found = !म_भेद(name, snap_name);
		kमुक्त(snap_name);
	पूर्ण
	वापस found ? snap_id : CEPH_NOSNAP;
पूर्ण

/*
 * Assumes name is never RBD_SNAP_HEAD_NAME; वापसs CEPH_NOSNAP अगर
 * no snapshot by that name is found, or अगर an error occurs.
 */
अटल u64 rbd_snap_id_by_name(काष्ठा rbd_device *rbd_dev, स्थिर अक्षर *name)
अणु
	अगर (rbd_dev->image_क्रमmat == 1)
		वापस rbd_v1_snap_id_by_name(rbd_dev, name);

	वापस rbd_v2_snap_id_by_name(rbd_dev, name);
पूर्ण

/*
 * An image being mapped will have everything but the snap id.
 */
अटल पूर्णांक rbd_spec_fill_snap_id(काष्ठा rbd_device *rbd_dev)
अणु
	काष्ठा rbd_spec *spec = rbd_dev->spec;

	rbd_निश्चित(spec->pool_id != CEPH_NOPOOL && spec->pool_name);
	rbd_निश्चित(spec->image_id && spec->image_name);
	rbd_निश्चित(spec->snap_name);

	अगर (म_भेद(spec->snap_name, RBD_SNAP_HEAD_NAME)) अणु
		u64 snap_id;

		snap_id = rbd_snap_id_by_name(rbd_dev, spec->snap_name);
		अगर (snap_id == CEPH_NOSNAP)
			वापस -ENOENT;

		spec->snap_id = snap_id;
	पूर्ण अन्यथा अणु
		spec->snap_id = CEPH_NOSNAP;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * A parent image will have all ids but none of the names.
 *
 * All names in an rbd spec are dynamically allocated.  It's OK अगर we
 * can't figure out the name क्रम an image id.
 */
अटल पूर्णांक rbd_spec_fill_names(काष्ठा rbd_device *rbd_dev)
अणु
	काष्ठा ceph_osd_client *osdc = &rbd_dev->rbd_client->client->osdc;
	काष्ठा rbd_spec *spec = rbd_dev->spec;
	स्थिर अक्षर *pool_name;
	स्थिर अक्षर *image_name;
	स्थिर अक्षर *snap_name;
	पूर्णांक ret;

	rbd_निश्चित(spec->pool_id != CEPH_NOPOOL);
	rbd_निश्चित(spec->image_id);
	rbd_निश्चित(spec->snap_id != CEPH_NOSNAP);

	/* Get the pool name; we have to make our own copy of this */

	pool_name = ceph_pg_pool_name_by_id(osdc->osdmap, spec->pool_id);
	अगर (!pool_name) अणु
		rbd_warn(rbd_dev, "no pool with id %llu", spec->pool_id);
		वापस -EIO;
	पूर्ण
	pool_name = kstrdup(pool_name, GFP_KERNEL);
	अगर (!pool_name)
		वापस -ENOMEM;

	/* Fetch the image name; tolerate failure here */

	image_name = rbd_dev_image_name(rbd_dev);
	अगर (!image_name)
		rbd_warn(rbd_dev, "unable to get image name");

	/* Fetch the snapshot name */

	snap_name = rbd_snap_name(rbd_dev, spec->snap_id);
	अगर (IS_ERR(snap_name)) अणु
		ret = PTR_ERR(snap_name);
		जाओ out_err;
	पूर्ण

	spec->pool_name = pool_name;
	spec->image_name = image_name;
	spec->snap_name = snap_name;

	वापस 0;

out_err:
	kमुक्त(image_name);
	kमुक्त(pool_name);
	वापस ret;
पूर्ण

अटल पूर्णांक rbd_dev_v2_snap_context(काष्ठा rbd_device *rbd_dev)
अणु
	माप_प्रकार size;
	पूर्णांक ret;
	व्योम *reply_buf;
	व्योम *p;
	व्योम *end;
	u64 seq;
	u32 snap_count;
	काष्ठा ceph_snap_context *snapc;
	u32 i;

	/*
	 * We'll need room क्रम the seq value (maximum snapshot id),
	 * snapshot count, and array of that many snapshot ids.
	 * For now we have a fixed upper limit on the number we're
	 * prepared to receive.
	 */
	size = माप (__le64) + माप (__le32) +
			RBD_MAX_SNAP_COUNT * माप (__le64);
	reply_buf = kzalloc(size, GFP_KERNEL);
	अगर (!reply_buf)
		वापस -ENOMEM;

	ret = rbd_obj_method_sync(rbd_dev, &rbd_dev->header_oid,
				  &rbd_dev->header_oloc, "get_snapcontext",
				  शून्य, 0, reply_buf, size);
	करोut("%s: rbd_obj_method_sync returned %d\n", __func__, ret);
	अगर (ret < 0)
		जाओ out;

	p = reply_buf;
	end = reply_buf + ret;
	ret = -दुस्फल;
	ceph_decode_64_safe(&p, end, seq, out);
	ceph_decode_32_safe(&p, end, snap_count, out);

	/*
	 * Make sure the reported number of snapshot ids wouldn't go
	 * beyond the end of our buffer.  But beक्रमe checking that,
	 * make sure the computed size of the snapshot context we
	 * allocate is representable in a माप_प्रकार.
	 */
	अगर (snap_count > (SIZE_MAX - माप (काष्ठा ceph_snap_context))
				 / माप (u64)) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण
	अगर (!ceph_has_room(&p, end, snap_count * माप (__le64)))
		जाओ out;
	ret = 0;

	snapc = ceph_create_snap_context(snap_count, GFP_KERNEL);
	अगर (!snapc) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण
	snapc->seq = seq;
	क्रम (i = 0; i < snap_count; i++)
		snapc->snaps[i] = ceph_decode_64(&p);

	ceph_put_snap_context(rbd_dev->header.snapc);
	rbd_dev->header.snapc = snapc;

	करोut("  snap context seq = %llu, snap_count = %u\n",
		(अचिन्हित दीर्घ दीर्घ)seq, (अचिन्हित पूर्णांक)snap_count);
out:
	kमुक्त(reply_buf);

	वापस ret;
पूर्ण

अटल स्थिर अक्षर *rbd_dev_v2_snap_name(काष्ठा rbd_device *rbd_dev,
					u64 snap_id)
अणु
	माप_प्रकार size;
	व्योम *reply_buf;
	__le64 snapid;
	पूर्णांक ret;
	व्योम *p;
	व्योम *end;
	अक्षर *snap_name;

	size = माप (__le32) + RBD_MAX_SNAP_NAME_LEN;
	reply_buf = kदो_स्मृति(size, GFP_KERNEL);
	अगर (!reply_buf)
		वापस ERR_PTR(-ENOMEM);

	snapid = cpu_to_le64(snap_id);
	ret = rbd_obj_method_sync(rbd_dev, &rbd_dev->header_oid,
				  &rbd_dev->header_oloc, "get_snapshot_name",
				  &snapid, माप(snapid), reply_buf, size);
	करोut("%s: rbd_obj_method_sync returned %d\n", __func__, ret);
	अगर (ret < 0) अणु
		snap_name = ERR_PTR(ret);
		जाओ out;
	पूर्ण

	p = reply_buf;
	end = reply_buf + ret;
	snap_name = ceph_extract_encoded_string(&p, end, शून्य, GFP_KERNEL);
	अगर (IS_ERR(snap_name))
		जाओ out;

	करोut("  snap_id 0x%016llx snap_name = %s\n",
		(अचिन्हित दीर्घ दीर्घ)snap_id, snap_name);
out:
	kमुक्त(reply_buf);

	वापस snap_name;
पूर्ण

अटल पूर्णांक rbd_dev_v2_header_info(काष्ठा rbd_device *rbd_dev)
अणु
	bool first_समय = rbd_dev->header.object_prefix == शून्य;
	पूर्णांक ret;

	ret = rbd_dev_v2_image_size(rbd_dev);
	अगर (ret)
		वापस ret;

	अगर (first_समय) अणु
		ret = rbd_dev_v2_header_oneसमय(rbd_dev);
		अगर (ret)
			वापस ret;
	पूर्ण

	ret = rbd_dev_v2_snap_context(rbd_dev);
	अगर (ret && first_समय) अणु
		kमुक्त(rbd_dev->header.object_prefix);
		rbd_dev->header.object_prefix = शून्य;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक rbd_dev_header_info(काष्ठा rbd_device *rbd_dev)
अणु
	rbd_निश्चित(rbd_image_क्रमmat_valid(rbd_dev->image_क्रमmat));

	अगर (rbd_dev->image_क्रमmat == 1)
		वापस rbd_dev_v1_header_info(rbd_dev);

	वापस rbd_dev_v2_header_info(rbd_dev);
पूर्ण

/*
 * Skips over white space at *buf, and updates *buf to poपूर्णांक to the
 * first found non-space अक्षरacter (अगर any). Returns the length of
 * the token (string of non-white space अक्षरacters) found.  Note
 * that *buf must be terminated with '\0'.
 */
अटल अंतरभूत माप_प्रकार next_token(स्थिर अक्षर **buf)
अणु
        /*
        * These are the अक्षरacters that produce nonzero क्रम
        * है_खाली() in the "C" and "POSIX" locales.
        */
        स्थिर अक्षर *spaces = " \f\n\r\t\v";

        *buf += म_अखोज(*buf, spaces);	/* Find start of token */

	वापस म_खोज(*buf, spaces);   /* Return token length */
पूर्ण

/*
 * Finds the next token in *buf, dynamically allocates a buffer big
 * enough to hold a copy of it, and copies the token पूर्णांकo the new
 * buffer.  The copy is guaranteed to be terminated with '\0'.  Note
 * that a duplicate buffer is created even क्रम a zero-length token.
 *
 * Returns a poपूर्णांकer to the newly-allocated duplicate, or a null
 * poपूर्णांकer अगर memory क्रम the duplicate was not available.  If
 * the lenp argument is a non-null poपूर्णांकer, the length of the token
 * (not including the '\0') is वापसed in *lenp.
 *
 * If successful, the *buf poपूर्णांकer will be updated to poपूर्णांक beyond
 * the end of the found token.
 *
 * Note: uses GFP_KERNEL क्रम allocation.
 */
अटल अंतरभूत अक्षर *dup_token(स्थिर अक्षर **buf, माप_प्रकार *lenp)
अणु
	अक्षर *dup;
	माप_प्रकार len;

	len = next_token(buf);
	dup = kmemdup(*buf, len + 1, GFP_KERNEL);
	अगर (!dup)
		वापस शून्य;
	*(dup + len) = '\0';
	*buf += len;

	अगर (lenp)
		*lenp = len;

	वापस dup;
पूर्ण

अटल पूर्णांक rbd_parse_param(काष्ठा fs_parameter *param,
			    काष्ठा rbd_parse_opts_ctx *pctx)
अणु
	काष्ठा rbd_options *opt = pctx->opts;
	काष्ठा fs_parse_result result;
	काष्ठा p_log log = अणु.prefix = "rbd"पूर्ण;
	पूर्णांक token, ret;

	ret = ceph_parse_param(param, pctx->copts, शून्य);
	अगर (ret != -ENOPARAM)
		वापस ret;

	token = __fs_parse(&log, rbd_parameters, param, &result);
	करोut("%s fs_parse '%s' token %d\n", __func__, param->key, token);
	अगर (token < 0) अणु
		अगर (token == -ENOPARAM)
			वापस inval_plog(&log, "Unknown parameter '%s'",
					  param->key);
		वापस token;
	पूर्ण

	चयन (token) अणु
	हाल Opt_queue_depth:
		अगर (result.uपूर्णांक_32 < 1)
			जाओ out_of_range;
		opt->queue_depth = result.uपूर्णांक_32;
		अवरोध;
	हाल Opt_alloc_size:
		अगर (result.uपूर्णांक_32 < SECTOR_SIZE)
			जाओ out_of_range;
		अगर (!is_घातer_of_2(result.uपूर्णांक_32))
			वापस inval_plog(&log, "alloc_size must be a power of 2");
		opt->alloc_size = result.uपूर्णांक_32;
		अवरोध;
	हाल Opt_lock_समयout:
		/* 0 is "wait forever" (i.e. infinite समयout) */
		अगर (result.uपूर्णांक_32 > पूर्णांक_उच्च / 1000)
			जाओ out_of_range;
		opt->lock_समयout = msecs_to_jअगरfies(result.uपूर्णांक_32 * 1000);
		अवरोध;
	हाल Opt_pool_ns:
		kमुक्त(pctx->spec->pool_ns);
		pctx->spec->pool_ns = param->string;
		param->string = शून्य;
		अवरोध;
	हाल Opt_compression_hपूर्णांक:
		चयन (result.uपूर्णांक_32) अणु
		हाल Opt_compression_hपूर्णांक_none:
			opt->alloc_hपूर्णांक_flags &=
			    ~(CEPH_OSD_ALLOC_HINT_FLAG_COMPRESSIBLE |
			      CEPH_OSD_ALLOC_HINT_FLAG_INCOMPRESSIBLE);
			अवरोध;
		हाल Opt_compression_hपूर्णांक_compressible:
			opt->alloc_hपूर्णांक_flags |=
			    CEPH_OSD_ALLOC_HINT_FLAG_COMPRESSIBLE;
			opt->alloc_hपूर्णांक_flags &=
			    ~CEPH_OSD_ALLOC_HINT_FLAG_INCOMPRESSIBLE;
			अवरोध;
		हाल Opt_compression_hपूर्णांक_incompressible:
			opt->alloc_hपूर्णांक_flags |=
			    CEPH_OSD_ALLOC_HINT_FLAG_INCOMPRESSIBLE;
			opt->alloc_hपूर्णांक_flags &=
			    ~CEPH_OSD_ALLOC_HINT_FLAG_COMPRESSIBLE;
			अवरोध;
		शेष:
			BUG();
		पूर्ण
		अवरोध;
	हाल Opt_पढ़ो_only:
		opt->पढ़ो_only = true;
		अवरोध;
	हाल Opt_पढ़ो_ग_लिखो:
		opt->पढ़ो_only = false;
		अवरोध;
	हाल Opt_lock_on_पढ़ो:
		opt->lock_on_पढ़ो = true;
		अवरोध;
	हाल Opt_exclusive:
		opt->exclusive = true;
		अवरोध;
	हाल Opt_notrim:
		opt->trim = false;
		अवरोध;
	शेष:
		BUG();
	पूर्ण

	वापस 0;

out_of_range:
	वापस inval_plog(&log, "%s out of range", param->key);
पूर्ण

/*
 * This duplicates most of generic_parse_monolithic(), untying it from
 * fs_context and skipping standard superblock and security options.
 */
अटल पूर्णांक rbd_parse_options(अक्षर *options, काष्ठा rbd_parse_opts_ctx *pctx)
अणु
	अक्षर *key;
	पूर्णांक ret = 0;

	करोut("%s '%s'\n", __func__, options);
	जबतक ((key = strsep(&options, ",")) != शून्य) अणु
		अगर (*key) अणु
			काष्ठा fs_parameter param = अणु
				.key	= key,
				.type	= fs_value_is_flag,
			पूर्ण;
			अक्षर *value = म_अक्षर(key, '=');
			माप_प्रकार v_len = 0;

			अगर (value) अणु
				अगर (value == key)
					जारी;
				*value++ = 0;
				v_len = म_माप(value);
				param.string = kmemdup_nul(value, v_len,
							   GFP_KERNEL);
				अगर (!param.string)
					वापस -ENOMEM;
				param.type = fs_value_is_string;
			पूर्ण
			param.size = v_len;

			ret = rbd_parse_param(&param, pctx);
			kमुक्त(param.string);
			अगर (ret)
				अवरोध;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

/*
 * Parse the options provided क्रम an "rbd add" (i.e., rbd image
 * mapping) request.  These arrive via a ग_लिखो to /sys/bus/rbd/add,
 * and the data written is passed here via a NUL-terminated buffer.
 * Returns 0 अगर successful or an error code otherwise.
 *
 * The inक्रमmation extracted from these options is recorded in
 * the other parameters which वापस dynamically-allocated
 * काष्ठाures:
 *  ceph_opts
 *      The address of a poपूर्णांकer that will refer to a ceph options
 *      काष्ठाure.  Caller must release the वापसed poपूर्णांकer using
 *      ceph_destroy_options() when it is no दीर्घer needed.
 *  rbd_opts
 *	Address of an rbd options poपूर्णांकer.  Fully initialized by
 *	this function; caller must release with kमुक्त().
 *  spec
 *	Address of an rbd image specअगरication poपूर्णांकer.  Fully
 *	initialized by this function based on parsed options.
 *	Caller must release with rbd_spec_put().
 *
 * The options passed take this क्रमm:
 *  <mon_addrs> <options> <pool_name> <image_name> [<snap_id>]
 * where:
 *  <mon_addrs>
 *      A comma-separated list of one or more monitor addresses.
 *      A monitor address is an ip address, optionally followed
 *      by a port number (separated by a colon).
 *        I.e.:  ip1[:port1][,ip2[:port2]...]
 *  <options>
 *      A comma-separated list of ceph and/or rbd options.
 *  <pool_name>
 *      The name of the raकरोs pool containing the rbd image.
 *  <image_name>
 *      The name of the image in that pool to map.
 *  <snap_id>
 *      An optional snapshot id.  If provided, the mapping will
 *      present data from the image at the समय that snapshot was
 *      created.  The image head is used अगर no snapshot id is
 *      provided.  Snapshot mappings are always पढ़ो-only.
 */
अटल पूर्णांक rbd_add_parse_args(स्थिर अक्षर *buf,
				काष्ठा ceph_options **ceph_opts,
				काष्ठा rbd_options **opts,
				काष्ठा rbd_spec **rbd_spec)
अणु
	माप_प्रकार len;
	अक्षर *options;
	स्थिर अक्षर *mon_addrs;
	अक्षर *snap_name;
	माप_प्रकार mon_addrs_size;
	काष्ठा rbd_parse_opts_ctx pctx = अणु 0 पूर्ण;
	पूर्णांक ret;

	/* The first four tokens are required */

	len = next_token(&buf);
	अगर (!len) अणु
		rbd_warn(शून्य, "no monitor address(es) provided");
		वापस -EINVAL;
	पूर्ण
	mon_addrs = buf;
	mon_addrs_size = len;
	buf += len;

	ret = -EINVAL;
	options = dup_token(&buf, शून्य);
	अगर (!options)
		वापस -ENOMEM;
	अगर (!*options) अणु
		rbd_warn(शून्य, "no options provided");
		जाओ out_err;
	पूर्ण

	pctx.spec = rbd_spec_alloc();
	अगर (!pctx.spec)
		जाओ out_mem;

	pctx.spec->pool_name = dup_token(&buf, शून्य);
	अगर (!pctx.spec->pool_name)
		जाओ out_mem;
	अगर (!*pctx.spec->pool_name) अणु
		rbd_warn(शून्य, "no pool name provided");
		जाओ out_err;
	पूर्ण

	pctx.spec->image_name = dup_token(&buf, शून्य);
	अगर (!pctx.spec->image_name)
		जाओ out_mem;
	अगर (!*pctx.spec->image_name) अणु
		rbd_warn(शून्य, "no image name provided");
		जाओ out_err;
	पूर्ण

	/*
	 * Snapshot name is optional; शेष is to use "-"
	 * (indicating the head/no snapshot).
	 */
	len = next_token(&buf);
	अगर (!len) अणु
		buf = RBD_SNAP_HEAD_NAME; /* No snapshot supplied */
		len = माप (RBD_SNAP_HEAD_NAME) - 1;
	पूर्ण अन्यथा अगर (len > RBD_MAX_SNAP_NAME_LEN) अणु
		ret = -ENAMETOOLONG;
		जाओ out_err;
	पूर्ण
	snap_name = kmemdup(buf, len + 1, GFP_KERNEL);
	अगर (!snap_name)
		जाओ out_mem;
	*(snap_name + len) = '\0';
	pctx.spec->snap_name = snap_name;

	pctx.copts = ceph_alloc_options();
	अगर (!pctx.copts)
		जाओ out_mem;

	/* Initialize all rbd options to the शेषs */

	pctx.opts = kzalloc(माप(*pctx.opts), GFP_KERNEL);
	अगर (!pctx.opts)
		जाओ out_mem;

	pctx.opts->पढ़ो_only = RBD_READ_ONLY_DEFAULT;
	pctx.opts->queue_depth = RBD_QUEUE_DEPTH_DEFAULT;
	pctx.opts->alloc_size = RBD_ALLOC_SIZE_DEFAULT;
	pctx.opts->lock_समयout = RBD_LOCK_TIMEOUT_DEFAULT;
	pctx.opts->lock_on_पढ़ो = RBD_LOCK_ON_READ_DEFAULT;
	pctx.opts->exclusive = RBD_EXCLUSIVE_DEFAULT;
	pctx.opts->trim = RBD_TRIM_DEFAULT;

	ret = ceph_parse_mon_ips(mon_addrs, mon_addrs_size, pctx.copts, शून्य);
	अगर (ret)
		जाओ out_err;

	ret = rbd_parse_options(options, &pctx);
	अगर (ret)
		जाओ out_err;

	*ceph_opts = pctx.copts;
	*opts = pctx.opts;
	*rbd_spec = pctx.spec;
	kमुक्त(options);
	वापस 0;

out_mem:
	ret = -ENOMEM;
out_err:
	kमुक्त(pctx.opts);
	ceph_destroy_options(pctx.copts);
	rbd_spec_put(pctx.spec);
	kमुक्त(options);
	वापस ret;
पूर्ण

अटल व्योम rbd_dev_image_unlock(काष्ठा rbd_device *rbd_dev)
अणु
	करोwn_ग_लिखो(&rbd_dev->lock_rwsem);
	अगर (__rbd_is_lock_owner(rbd_dev))
		__rbd_release_lock(rbd_dev);
	up_ग_लिखो(&rbd_dev->lock_rwsem);
पूर्ण

/*
 * If the रुको is पूर्णांकerrupted, an error is वापसed even अगर the lock
 * was successfully acquired.  rbd_dev_image_unlock() will release it
 * अगर needed.
 */
अटल पूर्णांक rbd_add_acquire_lock(काष्ठा rbd_device *rbd_dev)
अणु
	दीर्घ ret;

	अगर (!(rbd_dev->header.features & RBD_FEATURE_EXCLUSIVE_LOCK)) अणु
		अगर (!rbd_dev->opts->exclusive && !rbd_dev->opts->lock_on_पढ़ो)
			वापस 0;

		rbd_warn(rbd_dev, "exclusive-lock feature is not enabled");
		वापस -EINVAL;
	पूर्ण

	अगर (rbd_is_ro(rbd_dev))
		वापस 0;

	rbd_निश्चित(!rbd_is_lock_owner(rbd_dev));
	queue_delayed_work(rbd_dev->task_wq, &rbd_dev->lock_dwork, 0);
	ret = रुको_क्रम_completion_समाप्तable_समयout(&rbd_dev->acquire_रुको,
			    ceph_समयout_jअगरfies(rbd_dev->opts->lock_समयout));
	अगर (ret > 0) अणु
		ret = rbd_dev->acquire_err;
	पूर्ण अन्यथा अणु
		cancel_delayed_work_sync(&rbd_dev->lock_dwork);
		अगर (!ret)
			ret = -ETIMEDOUT;
	पूर्ण

	अगर (ret) अणु
		rbd_warn(rbd_dev, "failed to acquire exclusive lock: %ld", ret);
		वापस ret;
	पूर्ण

	/*
	 * The lock may have been released by now, unless स्वतःmatic lock
	 * transitions are disabled.
	 */
	rbd_निश्चित(!rbd_dev->opts->exclusive || rbd_is_lock_owner(rbd_dev));
	वापस 0;
पूर्ण

/*
 * An rbd क्रमmat 2 image has a unique identअगरier, distinct from the
 * name given to it by the user.  Internally, that identअगरier is
 * what's used to specअगरy the names of objects related to the image.
 *
 * A special "rbd id" object is used to map an rbd image name to its
 * id.  If that object करोesn't exist, then there is no v2 rbd image
 * with the supplied name.
 *
 * This function will record the given rbd_dev's image_id field अगर
 * it can be determined, and in that हाल will वापस 0.  If any
 * errors occur a negative त्रुटि_सं will be वापसed and the rbd_dev's
 * image_id field will be unchanged (and should be शून्य).
 */
अटल पूर्णांक rbd_dev_image_id(काष्ठा rbd_device *rbd_dev)
अणु
	पूर्णांक ret;
	माप_प्रकार size;
	CEPH_DEFINE_OID_ONSTACK(oid);
	व्योम *response;
	अक्षर *image_id;

	/*
	 * When probing a parent image, the image id is alपढ़ोy
	 * known (and the image name likely is not).  There's no
	 * need to fetch the image id again in this हाल.  We
	 * करो still need to set the image क्रमmat though.
	 */
	अगर (rbd_dev->spec->image_id) अणु
		rbd_dev->image_क्रमmat = *rbd_dev->spec->image_id ? 2 : 1;

		वापस 0;
	पूर्ण

	/*
	 * First, see अगर the क्रमmat 2 image id file exists, and अगर
	 * so, get the image's persistent id from it.
	 */
	ret = ceph_oid_aम_लिखो(&oid, GFP_KERNEL, "%s%s", RBD_ID_PREFIX,
			       rbd_dev->spec->image_name);
	अगर (ret)
		वापस ret;

	करोut("rbd id object name is %s\n", oid.name);

	/* Response will be an encoded string, which includes a length */
	size = माप (__le32) + RBD_IMAGE_ID_LEN_MAX;
	response = kzalloc(size, GFP_NOIO);
	अगर (!response) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	/* If it करोesn't exist we'll assume it's a क्रमmat 1 image */

	ret = rbd_obj_method_sync(rbd_dev, &oid, &rbd_dev->header_oloc,
				  "get_id", शून्य, 0,
				  response, size);
	करोut("%s: rbd_obj_method_sync returned %d\n", __func__, ret);
	अगर (ret == -ENOENT) अणु
		image_id = kstrdup("", GFP_KERNEL);
		ret = image_id ? 0 : -ENOMEM;
		अगर (!ret)
			rbd_dev->image_क्रमmat = 1;
	पूर्ण अन्यथा अगर (ret >= 0) अणु
		व्योम *p = response;

		image_id = ceph_extract_encoded_string(&p, p + ret,
						शून्य, GFP_NOIO);
		ret = PTR_ERR_OR_ZERO(image_id);
		अगर (!ret)
			rbd_dev->image_क्रमmat = 2;
	पूर्ण

	अगर (!ret) अणु
		rbd_dev->spec->image_id = image_id;
		करोut("image_id is %s\n", image_id);
	पूर्ण
out:
	kमुक्त(response);
	ceph_oid_destroy(&oid);
	वापस ret;
पूर्ण

/*
 * Unकरो whatever state changes are made by v1 or v2 header info
 * call.
 */
अटल व्योम rbd_dev_unprobe(काष्ठा rbd_device *rbd_dev)
अणु
	काष्ठा rbd_image_header	*header;

	rbd_dev_parent_put(rbd_dev);
	rbd_object_map_मुक्त(rbd_dev);
	rbd_dev_mapping_clear(rbd_dev);

	/* Free dynamic fields from the header, then zero it out */

	header = &rbd_dev->header;
	ceph_put_snap_context(header->snapc);
	kमुक्त(header->snap_sizes);
	kमुक्त(header->snap_names);
	kमुक्त(header->object_prefix);
	स_रखो(header, 0, माप (*header));
पूर्ण

अटल पूर्णांक rbd_dev_v2_header_oneसमय(काष्ठा rbd_device *rbd_dev)
अणु
	पूर्णांक ret;

	ret = rbd_dev_v2_object_prefix(rbd_dev);
	अगर (ret)
		जाओ out_err;

	/*
	 * Get the and check features क्रम the image.  Currently the
	 * features are assumed to never change.
	 */
	ret = rbd_dev_v2_features(rbd_dev);
	अगर (ret)
		जाओ out_err;

	/* If the image supports fancy striping, get its parameters */

	अगर (rbd_dev->header.features & RBD_FEATURE_STRIPINGV2) अणु
		ret = rbd_dev_v2_striping_info(rbd_dev);
		अगर (ret < 0)
			जाओ out_err;
	पूर्ण

	अगर (rbd_dev->header.features & RBD_FEATURE_DATA_POOL) अणु
		ret = rbd_dev_v2_data_pool(rbd_dev);
		अगर (ret)
			जाओ out_err;
	पूर्ण

	rbd_init_layout(rbd_dev);
	वापस 0;

out_err:
	rbd_dev->header.features = 0;
	kमुक्त(rbd_dev->header.object_prefix);
	rbd_dev->header.object_prefix = शून्य;
	वापस ret;
पूर्ण

/*
 * @depth is rbd_dev_image_probe() -> rbd_dev_probe_parent() ->
 * rbd_dev_image_probe() recursion depth, which means it's also the
 * length of the alपढ़ोy discovered part of the parent chain.
 */
अटल पूर्णांक rbd_dev_probe_parent(काष्ठा rbd_device *rbd_dev, पूर्णांक depth)
अणु
	काष्ठा rbd_device *parent = शून्य;
	पूर्णांक ret;

	अगर (!rbd_dev->parent_spec)
		वापस 0;

	अगर (++depth > RBD_MAX_PARENT_CHAIN_LEN) अणु
		pr_info("parent chain is too long (%d)\n", depth);
		ret = -EINVAL;
		जाओ out_err;
	पूर्ण

	parent = __rbd_dev_create(rbd_dev->rbd_client, rbd_dev->parent_spec);
	अगर (!parent) अणु
		ret = -ENOMEM;
		जाओ out_err;
	पूर्ण

	/*
	 * Images related by parent/child relationships always share
	 * rbd_client and spec/parent_spec, so bump their refcounts.
	 */
	__rbd_get_client(rbd_dev->rbd_client);
	rbd_spec_get(rbd_dev->parent_spec);

	__set_bit(RBD_DEV_FLAG_READONLY, &parent->flags);

	ret = rbd_dev_image_probe(parent, depth);
	अगर (ret < 0)
		जाओ out_err;

	rbd_dev->parent = parent;
	atomic_set(&rbd_dev->parent_ref, 1);
	वापस 0;

out_err:
	rbd_dev_unparent(rbd_dev);
	rbd_dev_destroy(parent);
	वापस ret;
पूर्ण

अटल व्योम rbd_dev_device_release(काष्ठा rbd_device *rbd_dev)
अणु
	clear_bit(RBD_DEV_FLAG_EXISTS, &rbd_dev->flags);
	rbd_मुक्त_disk(rbd_dev);
	अगर (!single_major)
		unरेजिस्टर_blkdev(rbd_dev->major, rbd_dev->name);
पूर्ण

/*
 * rbd_dev->header_rwsem must be locked क्रम ग_लिखो and will be unlocked
 * upon वापस.
 */
अटल पूर्णांक rbd_dev_device_setup(काष्ठा rbd_device *rbd_dev)
अणु
	पूर्णांक ret;

	/* Record our major and minor device numbers. */

	अगर (!single_major) अणु
		ret = रेजिस्टर_blkdev(0, rbd_dev->name);
		अगर (ret < 0)
			जाओ err_out_unlock;

		rbd_dev->major = ret;
		rbd_dev->minor = 0;
	पूर्ण अन्यथा अणु
		rbd_dev->major = rbd_major;
		rbd_dev->minor = rbd_dev_id_to_minor(rbd_dev->dev_id);
	पूर्ण

	/* Set up the blkdev mapping. */

	ret = rbd_init_disk(rbd_dev);
	अगर (ret)
		जाओ err_out_blkdev;

	set_capacity(rbd_dev->disk, rbd_dev->mapping.size / SECTOR_SIZE);
	set_disk_ro(rbd_dev->disk, rbd_is_ro(rbd_dev));

	ret = dev_set_name(&rbd_dev->dev, "%d", rbd_dev->dev_id);
	अगर (ret)
		जाओ err_out_disk;

	set_bit(RBD_DEV_FLAG_EXISTS, &rbd_dev->flags);
	up_ग_लिखो(&rbd_dev->header_rwsem);
	वापस 0;

err_out_disk:
	rbd_मुक्त_disk(rbd_dev);
err_out_blkdev:
	अगर (!single_major)
		unरेजिस्टर_blkdev(rbd_dev->major, rbd_dev->name);
err_out_unlock:
	up_ग_लिखो(&rbd_dev->header_rwsem);
	वापस ret;
पूर्ण

अटल पूर्णांक rbd_dev_header_name(काष्ठा rbd_device *rbd_dev)
अणु
	काष्ठा rbd_spec *spec = rbd_dev->spec;
	पूर्णांक ret;

	/* Record the header object name क्रम this rbd image. */

	rbd_निश्चित(rbd_image_क्रमmat_valid(rbd_dev->image_क्रमmat));
	अगर (rbd_dev->image_क्रमmat == 1)
		ret = ceph_oid_aम_लिखो(&rbd_dev->header_oid, GFP_KERNEL, "%s%s",
				       spec->image_name, RBD_SUFFIX);
	अन्यथा
		ret = ceph_oid_aम_लिखो(&rbd_dev->header_oid, GFP_KERNEL, "%s%s",
				       RBD_HEADER_PREFIX, spec->image_id);

	वापस ret;
पूर्ण

अटल व्योम rbd_prपूर्णांक_dne(काष्ठा rbd_device *rbd_dev, bool is_snap)
अणु
	अगर (!is_snap) अणु
		pr_info("image %s/%s%s%s does not exist\n",
			rbd_dev->spec->pool_name,
			rbd_dev->spec->pool_ns ?: "",
			rbd_dev->spec->pool_ns ? "/" : "",
			rbd_dev->spec->image_name);
	पूर्ण अन्यथा अणु
		pr_info("snap %s/%s%s%s@%s does not exist\n",
			rbd_dev->spec->pool_name,
			rbd_dev->spec->pool_ns ?: "",
			rbd_dev->spec->pool_ns ? "/" : "",
			rbd_dev->spec->image_name,
			rbd_dev->spec->snap_name);
	पूर्ण
पूर्ण

अटल व्योम rbd_dev_image_release(काष्ठा rbd_device *rbd_dev)
अणु
	अगर (!rbd_is_ro(rbd_dev))
		rbd_unरेजिस्टर_watch(rbd_dev);

	rbd_dev_unprobe(rbd_dev);
	rbd_dev->image_क्रमmat = 0;
	kमुक्त(rbd_dev->spec->image_id);
	rbd_dev->spec->image_id = शून्य;
पूर्ण

/*
 * Probe क्रम the existence of the header object क्रम the given rbd
 * device.  If this image is the one being mapped (i.e., not a
 * parent), initiate a watch on its header object beक्रमe using that
 * object to get detailed inक्रमmation about the rbd image.
 *
 * On success, वापसs with header_rwsem held क्रम ग_लिखो अगर called
 * with @depth == 0.
 */
अटल पूर्णांक rbd_dev_image_probe(काष्ठा rbd_device *rbd_dev, पूर्णांक depth)
अणु
	bool need_watch = !rbd_is_ro(rbd_dev);
	पूर्णांक ret;

	/*
	 * Get the id from the image id object.  Unless there's an
	 * error, rbd_dev->spec->image_id will be filled in with
	 * a dynamically-allocated string, and rbd_dev->image_क्रमmat
	 * will be set to either 1 or 2.
	 */
	ret = rbd_dev_image_id(rbd_dev);
	अगर (ret)
		वापस ret;

	ret = rbd_dev_header_name(rbd_dev);
	अगर (ret)
		जाओ err_out_क्रमmat;

	अगर (need_watch) अणु
		ret = rbd_रेजिस्टर_watch(rbd_dev);
		अगर (ret) अणु
			अगर (ret == -ENOENT)
				rbd_prपूर्णांक_dne(rbd_dev, false);
			जाओ err_out_क्रमmat;
		पूर्ण
	पूर्ण

	अगर (!depth)
		करोwn_ग_लिखो(&rbd_dev->header_rwsem);

	ret = rbd_dev_header_info(rbd_dev);
	अगर (ret) अणु
		अगर (ret == -ENOENT && !need_watch)
			rbd_prपूर्णांक_dne(rbd_dev, false);
		जाओ err_out_probe;
	पूर्ण

	/*
	 * If this image is the one being mapped, we have pool name and
	 * id, image name and id, and snap name - need to fill snap id.
	 * Otherwise this is a parent image, identअगरied by pool, image
	 * and snap ids - need to fill in names क्रम those ids.
	 */
	अगर (!depth)
		ret = rbd_spec_fill_snap_id(rbd_dev);
	अन्यथा
		ret = rbd_spec_fill_names(rbd_dev);
	अगर (ret) अणु
		अगर (ret == -ENOENT)
			rbd_prपूर्णांक_dne(rbd_dev, true);
		जाओ err_out_probe;
	पूर्ण

	ret = rbd_dev_mapping_set(rbd_dev);
	अगर (ret)
		जाओ err_out_probe;

	अगर (rbd_is_snap(rbd_dev) &&
	    (rbd_dev->header.features & RBD_FEATURE_OBJECT_MAP)) अणु
		ret = rbd_object_map_load(rbd_dev);
		अगर (ret)
			जाओ err_out_probe;
	पूर्ण

	अगर (rbd_dev->header.features & RBD_FEATURE_LAYERING) अणु
		ret = rbd_dev_v2_parent_info(rbd_dev);
		अगर (ret)
			जाओ err_out_probe;
	पूर्ण

	ret = rbd_dev_probe_parent(rbd_dev, depth);
	अगर (ret)
		जाओ err_out_probe;

	करोut("discovered format %u image, header name is %s\n",
		rbd_dev->image_क्रमmat, rbd_dev->header_oid.name);
	वापस 0;

err_out_probe:
	अगर (!depth)
		up_ग_लिखो(&rbd_dev->header_rwsem);
	अगर (need_watch)
		rbd_unरेजिस्टर_watch(rbd_dev);
	rbd_dev_unprobe(rbd_dev);
err_out_क्रमmat:
	rbd_dev->image_क्रमmat = 0;
	kमुक्त(rbd_dev->spec->image_id);
	rbd_dev->spec->image_id = शून्य;
	वापस ret;
पूर्ण

अटल sमाप_प्रकार करो_rbd_add(काष्ठा bus_type *bus,
			  स्थिर अक्षर *buf,
			  माप_प्रकार count)
अणु
	काष्ठा rbd_device *rbd_dev = शून्य;
	काष्ठा ceph_options *ceph_opts = शून्य;
	काष्ठा rbd_options *rbd_opts = शून्य;
	काष्ठा rbd_spec *spec = शून्य;
	काष्ठा rbd_client *rbdc;
	पूर्णांक rc;

	अगर (!capable(CAP_SYS_ADMIN))
		वापस -EPERM;

	अगर (!try_module_get(THIS_MODULE))
		वापस -ENODEV;

	/* parse add command */
	rc = rbd_add_parse_args(buf, &ceph_opts, &rbd_opts, &spec);
	अगर (rc < 0)
		जाओ out;

	rbdc = rbd_get_client(ceph_opts);
	अगर (IS_ERR(rbdc)) अणु
		rc = PTR_ERR(rbdc);
		जाओ err_out_args;
	पूर्ण

	/* pick the pool */
	rc = ceph_pg_poolid_by_name(rbdc->client->osdc.osdmap, spec->pool_name);
	अगर (rc < 0) अणु
		अगर (rc == -ENOENT)
			pr_info("pool %s does not exist\n", spec->pool_name);
		जाओ err_out_client;
	पूर्ण
	spec->pool_id = (u64)rc;

	rbd_dev = rbd_dev_create(rbdc, spec, rbd_opts);
	अगर (!rbd_dev) अणु
		rc = -ENOMEM;
		जाओ err_out_client;
	पूर्ण
	rbdc = शून्य;		/* rbd_dev now owns this */
	spec = शून्य;		/* rbd_dev now owns this */
	rbd_opts = शून्य;	/* rbd_dev now owns this */

	/* अगर we are mapping a snapshot it will be a पढ़ो-only mapping */
	अगर (rbd_dev->opts->पढ़ो_only ||
	    म_भेद(rbd_dev->spec->snap_name, RBD_SNAP_HEAD_NAME))
		__set_bit(RBD_DEV_FLAG_READONLY, &rbd_dev->flags);

	rbd_dev->config_info = kstrdup(buf, GFP_KERNEL);
	अगर (!rbd_dev->config_info) अणु
		rc = -ENOMEM;
		जाओ err_out_rbd_dev;
	पूर्ण

	rc = rbd_dev_image_probe(rbd_dev, 0);
	अगर (rc < 0)
		जाओ err_out_rbd_dev;

	अगर (rbd_dev->opts->alloc_size > rbd_dev->layout.object_size) अणु
		rbd_warn(rbd_dev, "alloc_size adjusted to %u",
			 rbd_dev->layout.object_size);
		rbd_dev->opts->alloc_size = rbd_dev->layout.object_size;
	पूर्ण

	rc = rbd_dev_device_setup(rbd_dev);
	अगर (rc)
		जाओ err_out_image_probe;

	rc = rbd_add_acquire_lock(rbd_dev);
	अगर (rc)
		जाओ err_out_image_lock;

	/* Everything's पढ़ोy.  Announce the disk to the world. */

	rc = device_add(&rbd_dev->dev);
	अगर (rc)
		जाओ err_out_image_lock;

	device_add_disk(&rbd_dev->dev, rbd_dev->disk, शून्य);
	/* see rbd_init_disk() */
	blk_put_queue(rbd_dev->disk->queue);

	spin_lock(&rbd_dev_list_lock);
	list_add_tail(&rbd_dev->node, &rbd_dev_list);
	spin_unlock(&rbd_dev_list_lock);

	pr_info("%s: capacity %llu features 0x%llx\n", rbd_dev->disk->disk_name,
		(अचिन्हित दीर्घ दीर्घ)get_capacity(rbd_dev->disk) << SECTOR_SHIFT,
		rbd_dev->header.features);
	rc = count;
out:
	module_put(THIS_MODULE);
	वापस rc;

err_out_image_lock:
	rbd_dev_image_unlock(rbd_dev);
	rbd_dev_device_release(rbd_dev);
err_out_image_probe:
	rbd_dev_image_release(rbd_dev);
err_out_rbd_dev:
	rbd_dev_destroy(rbd_dev);
err_out_client:
	rbd_put_client(rbdc);
err_out_args:
	rbd_spec_put(spec);
	kमुक्त(rbd_opts);
	जाओ out;
पूर्ण

अटल sमाप_प्रकार add_store(काष्ठा bus_type *bus, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	अगर (single_major)
		वापस -EINVAL;

	वापस करो_rbd_add(bus, buf, count);
पूर्ण

अटल sमाप_प्रकार add_single_major_store(काष्ठा bus_type *bus, स्थिर अक्षर *buf,
				      माप_प्रकार count)
अणु
	वापस करो_rbd_add(bus, buf, count);
पूर्ण

अटल व्योम rbd_dev_हटाओ_parent(काष्ठा rbd_device *rbd_dev)
अणु
	जबतक (rbd_dev->parent) अणु
		काष्ठा rbd_device *first = rbd_dev;
		काष्ठा rbd_device *second = first->parent;
		काष्ठा rbd_device *third;

		/*
		 * Follow to the parent with no gअक्रमparent and
		 * हटाओ it.
		 */
		जबतक (second && (third = second->parent)) अणु
			first = second;
			second = third;
		पूर्ण
		rbd_निश्चित(second);
		rbd_dev_image_release(second);
		rbd_dev_destroy(second);
		first->parent = शून्य;
		first->parent_overlap = 0;

		rbd_निश्चित(first->parent_spec);
		rbd_spec_put(first->parent_spec);
		first->parent_spec = शून्य;
	पूर्ण
पूर्ण

अटल sमाप_प्रकार करो_rbd_हटाओ(काष्ठा bus_type *bus,
			     स्थिर अक्षर *buf,
			     माप_प्रकार count)
अणु
	काष्ठा rbd_device *rbd_dev = शून्य;
	काष्ठा list_head *पंचांगp;
	पूर्णांक dev_id;
	अक्षर opt_buf[6];
	bool क्रमce = false;
	पूर्णांक ret;

	अगर (!capable(CAP_SYS_ADMIN))
		वापस -EPERM;

	dev_id = -1;
	opt_buf[0] = '\0';
	माला_पूछो(buf, "%d %5s", &dev_id, opt_buf);
	अगर (dev_id < 0) अणु
		pr_err("dev_id out of range\n");
		वापस -EINVAL;
	पूर्ण
	अगर (opt_buf[0] != '\0') अणु
		अगर (!म_भेद(opt_buf, "force")) अणु
			क्रमce = true;
		पूर्ण अन्यथा अणु
			pr_err("bad remove option at '%s'\n", opt_buf);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	ret = -ENOENT;
	spin_lock(&rbd_dev_list_lock);
	list_क्रम_each(पंचांगp, &rbd_dev_list) अणु
		rbd_dev = list_entry(पंचांगp, काष्ठा rbd_device, node);
		अगर (rbd_dev->dev_id == dev_id) अणु
			ret = 0;
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (!ret) अणु
		spin_lock_irq(&rbd_dev->lock);
		अगर (rbd_dev->खोलो_count && !क्रमce)
			ret = -EBUSY;
		अन्यथा अगर (test_and_set_bit(RBD_DEV_FLAG_REMOVING,
					  &rbd_dev->flags))
			ret = -EINPROGRESS;
		spin_unlock_irq(&rbd_dev->lock);
	पूर्ण
	spin_unlock(&rbd_dev_list_lock);
	अगर (ret)
		वापस ret;

	अगर (क्रमce) अणु
		/*
		 * Prevent new IO from being queued and रुको क्रम existing
		 * IO to complete/fail.
		 */
		blk_mq_मुक्तze_queue(rbd_dev->disk->queue);
		blk_set_queue_dying(rbd_dev->disk->queue);
	पूर्ण

	del_gendisk(rbd_dev->disk);
	spin_lock(&rbd_dev_list_lock);
	list_del_init(&rbd_dev->node);
	spin_unlock(&rbd_dev_list_lock);
	device_del(&rbd_dev->dev);

	rbd_dev_image_unlock(rbd_dev);
	rbd_dev_device_release(rbd_dev);
	rbd_dev_image_release(rbd_dev);
	rbd_dev_destroy(rbd_dev);
	वापस count;
पूर्ण

अटल sमाप_प्रकार हटाओ_store(काष्ठा bus_type *bus, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	अगर (single_major)
		वापस -EINVAL;

	वापस करो_rbd_हटाओ(bus, buf, count);
पूर्ण

अटल sमाप_प्रकार हटाओ_single_major_store(काष्ठा bus_type *bus, स्थिर अक्षर *buf,
					 माप_प्रकार count)
अणु
	वापस करो_rbd_हटाओ(bus, buf, count);
पूर्ण

/*
 * create control files in sysfs
 * /sys/bus/rbd/...
 */
अटल पूर्णांक __init rbd_sysfs_init(व्योम)
अणु
	पूर्णांक ret;

	ret = device_रेजिस्टर(&rbd_root_dev);
	अगर (ret < 0)
		वापस ret;

	ret = bus_रेजिस्टर(&rbd_bus_type);
	अगर (ret < 0)
		device_unरेजिस्टर(&rbd_root_dev);

	वापस ret;
पूर्ण

अटल व्योम __निकास rbd_sysfs_cleanup(व्योम)
अणु
	bus_unरेजिस्टर(&rbd_bus_type);
	device_unरेजिस्टर(&rbd_root_dev);
पूर्ण

अटल पूर्णांक __init rbd_slab_init(व्योम)
अणु
	rbd_निश्चित(!rbd_img_request_cache);
	rbd_img_request_cache = KMEM_CACHE(rbd_img_request, 0);
	अगर (!rbd_img_request_cache)
		वापस -ENOMEM;

	rbd_निश्चित(!rbd_obj_request_cache);
	rbd_obj_request_cache = KMEM_CACHE(rbd_obj_request, 0);
	अगर (!rbd_obj_request_cache)
		जाओ out_err;

	वापस 0;

out_err:
	kmem_cache_destroy(rbd_img_request_cache);
	rbd_img_request_cache = शून्य;
	वापस -ENOMEM;
पूर्ण

अटल व्योम rbd_slab_निकास(व्योम)
अणु
	rbd_निश्चित(rbd_obj_request_cache);
	kmem_cache_destroy(rbd_obj_request_cache);
	rbd_obj_request_cache = शून्य;

	rbd_निश्चित(rbd_img_request_cache);
	kmem_cache_destroy(rbd_img_request_cache);
	rbd_img_request_cache = शून्य;
पूर्ण

अटल पूर्णांक __init rbd_init(व्योम)
अणु
	पूर्णांक rc;

	अगर (!libceph_compatible(शून्य)) अणु
		rbd_warn(शून्य, "libceph incompatibility (quitting)");
		वापस -EINVAL;
	पूर्ण

	rc = rbd_slab_init();
	अगर (rc)
		वापस rc;

	/*
	 * The number of active work items is limited by the number of
	 * rbd devices * queue depth, so leave @max_active at शेष.
	 */
	rbd_wq = alloc_workqueue(RBD_DRV_NAME, WQ_MEM_RECLAIM, 0);
	अगर (!rbd_wq) अणु
		rc = -ENOMEM;
		जाओ err_out_slab;
	पूर्ण

	अगर (single_major) अणु
		rbd_major = रेजिस्टर_blkdev(0, RBD_DRV_NAME);
		अगर (rbd_major < 0) अणु
			rc = rbd_major;
			जाओ err_out_wq;
		पूर्ण
	पूर्ण

	rc = rbd_sysfs_init();
	अगर (rc)
		जाओ err_out_blkdev;

	अगर (single_major)
		pr_info("loaded (major %d)\n", rbd_major);
	अन्यथा
		pr_info("loaded\n");

	वापस 0;

err_out_blkdev:
	अगर (single_major)
		unरेजिस्टर_blkdev(rbd_major, RBD_DRV_NAME);
err_out_wq:
	destroy_workqueue(rbd_wq);
err_out_slab:
	rbd_slab_निकास();
	वापस rc;
पूर्ण

अटल व्योम __निकास rbd_निकास(व्योम)
अणु
	ida_destroy(&rbd_dev_id_ida);
	rbd_sysfs_cleanup();
	अगर (single_major)
		unरेजिस्टर_blkdev(rbd_major, RBD_DRV_NAME);
	destroy_workqueue(rbd_wq);
	rbd_slab_निकास();
पूर्ण

module_init(rbd_init);
module_निकास(rbd_निकास);

MODULE_AUTHOR("Alex Elder <elder@inktank.com>");
MODULE_AUTHOR("Sage Weil <sage@newdream.net>");
MODULE_AUTHOR("Yehuda Sadeh <yehuda@hq.newdream.net>");
/* following authorship retained from original osdblk.c */
MODULE_AUTHOR("Jeff Garzik <jeff@garzik.org>");

MODULE_DESCRIPTION("RADOS Block Device (RBD) driver");
MODULE_LICENSE("GPL");
