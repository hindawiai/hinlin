<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* CacheFiles path walking and related routines
 *
 * Copyright (C) 2007 Red Hat, Inc. All Rights Reserved.
 * Written by David Howells (dhowells@redhat.com)
 */

#समावेश <linux/module.h>
#समावेश <linux/sched.h>
#समावेश <linux/file.h>
#समावेश <linux/fs.h>
#समावेश <linux/fsnotअगरy.h>
#समावेश <linux/quotaops.h>
#समावेश <linux/xattr.h>
#समावेश <linux/mount.h>
#समावेश <linux/namei.h>
#समावेश <linux/security.h>
#समावेश <linux/slab.h>
#समावेश "internal.h"

#घोषणा CACHEखाताS_KEYBUF_SIZE 512

/*
 * dump debugging info about an object
 */
अटल noअंतरभूत
व्योम __cachefiles_prपूर्णांकk_object(काष्ठा cachefiles_object *object,
				स्थिर अक्षर *prefix)
अणु
	काष्ठा fscache_cookie *cookie;
	स्थिर u8 *k;
	अचिन्हित loop;

	pr_err("%sobject: OBJ%x\n", prefix, object->fscache.debug_id);
	pr_err("%sobjstate=%s fl=%lx wbusy=%x ev=%lx[%lx]\n",
	       prefix, object->fscache.state->name,
	       object->fscache.flags, work_busy(&object->fscache.work),
	       object->fscache.events, object->fscache.event_mask);
	pr_err("%sops=%u inp=%u exc=%u\n",
	       prefix, object->fscache.n_ops, object->fscache.n_in_progress,
	       object->fscache.n_exclusive);
	pr_err("%sparent=%p\n",
	       prefix, object->fscache.parent);

	spin_lock(&object->fscache.lock);
	cookie = object->fscache.cookie;
	अगर (cookie) अणु
		pr_err("%scookie=%p [pr=%p nd=%p fl=%lx]\n",
		       prefix,
		       object->fscache.cookie,
		       object->fscache.cookie->parent,
		       object->fscache.cookie->netfs_data,
		       object->fscache.cookie->flags);
		pr_err("%skey=[%u] '", prefix, cookie->key_len);
		k = (cookie->key_len <= माप(cookie->अंतरभूत_key)) ?
			cookie->अंतरभूत_key : cookie->key;
		क्रम (loop = 0; loop < cookie->key_len; loop++)
			pr_cont("%02x", k[loop]);
		pr_cont("'\n");
	पूर्ण अन्यथा अणु
		pr_err("%scookie=NULL\n", prefix);
	पूर्ण
	spin_unlock(&object->fscache.lock);
पूर्ण

/*
 * dump debugging info about a pair of objects
 */
अटल noअंतरभूत व्योम cachefiles_prपूर्णांकk_object(काष्ठा cachefiles_object *object,
					      काष्ठा cachefiles_object *xobject)
अणु
	अगर (object)
		__cachefiles_prपूर्णांकk_object(object, "");
	अगर (xobject)
		__cachefiles_prपूर्णांकk_object(xobject, "x");
पूर्ण

/*
 * mark the owner of a dentry, अगर there is one, to indicate that that dentry
 * has been preemptively deleted
 * - the caller must hold the i_mutex on the dentry's parent as required to
 *   call vfs_unlink(), vfs_सूची_हटाओ() or vfs_नाम()
 */
अटल व्योम cachefiles_mark_object_buried(काष्ठा cachefiles_cache *cache,
					  काष्ठा dentry *dentry,
					  क्रमागत fscache_why_object_समाप्तed why)
अणु
	काष्ठा cachefiles_object *object;
	काष्ठा rb_node *p;

	_enter(",'%pd'", dentry);

	ग_लिखो_lock(&cache->active_lock);

	p = cache->active_nodes.rb_node;
	जबतक (p) अणु
		object = rb_entry(p, काष्ठा cachefiles_object, active_node);
		अगर (object->dentry > dentry)
			p = p->rb_left;
		अन्यथा अगर (object->dentry < dentry)
			p = p->rb_right;
		अन्यथा
			जाओ found_dentry;
	पूर्ण

	ग_लिखो_unlock(&cache->active_lock);
	trace_cachefiles_mark_buried(शून्य, dentry, why);
	_leave(" [no owner]");
	वापस;

	/* found the dentry क्रम  */
found_dentry:
	kdebug("preemptive burial: OBJ%x [%s] %p",
	       object->fscache.debug_id,
	       object->fscache.state->name,
	       dentry);

	trace_cachefiles_mark_buried(object, dentry, why);

	अगर (fscache_object_is_live(&object->fscache)) अणु
		pr_err("\n");
		pr_err("Error: Can't preemptively bury live object\n");
		cachefiles_prपूर्णांकk_object(object, शून्य);
	पूर्ण अन्यथा अणु
		अगर (why != FSCACHE_OBJECT_IS_STALE)
			fscache_object_mark_समाप्तed(&object->fscache, why);
	पूर्ण

	ग_लिखो_unlock(&cache->active_lock);
	_leave(" [owner marked]");
पूर्ण

/*
 * record the fact that an object is now active
 */
अटल पूर्णांक cachefiles_mark_object_active(काष्ठा cachefiles_cache *cache,
					 काष्ठा cachefiles_object *object)
अणु
	काष्ठा cachefiles_object *xobject;
	काष्ठा rb_node **_p, *_parent = शून्य;
	काष्ठा dentry *dentry;

	_enter(",%p", object);

try_again:
	ग_लिखो_lock(&cache->active_lock);

	dentry = object->dentry;
	trace_cachefiles_mark_active(object, dentry);

	अगर (test_and_set_bit(CACHEखाताS_OBJECT_ACTIVE, &object->flags)) अणु
		pr_err("Error: Object already active\n");
		cachefiles_prपूर्णांकk_object(object, शून्य);
		BUG();
	पूर्ण

	_p = &cache->active_nodes.rb_node;
	जबतक (*_p) अणु
		_parent = *_p;
		xobject = rb_entry(_parent,
				   काष्ठा cachefiles_object, active_node);

		ASSERT(xobject != object);

		अगर (xobject->dentry > dentry)
			_p = &(*_p)->rb_left;
		अन्यथा अगर (xobject->dentry < dentry)
			_p = &(*_p)->rb_right;
		अन्यथा
			जाओ रुको_क्रम_old_object;
	पूर्ण

	rb_link_node(&object->active_node, _parent, _p);
	rb_insert_color(&object->active_node, &cache->active_nodes);

	ग_लिखो_unlock(&cache->active_lock);
	_leave(" = 0");
	वापस 0;

	/* an old object from a previous incarnation is hogging the slot - we
	 * need to रुको क्रम it to be destroyed */
रुको_क्रम_old_object:
	trace_cachefiles_रुको_active(object, dentry, xobject);
	clear_bit(CACHEखाताS_OBJECT_ACTIVE, &object->flags);

	अगर (fscache_object_is_live(&xobject->fscache)) अणु
		pr_err("\n");
		pr_err("Error: Unexpected object collision\n");
		cachefiles_prपूर्णांकk_object(object, xobject);
	पूर्ण
	atomic_inc(&xobject->usage);
	ग_लिखो_unlock(&cache->active_lock);

	अगर (test_bit(CACHEखाताS_OBJECT_ACTIVE, &xobject->flags)) अणु
		रुको_queue_head_t *wq;

		चिन्हित दीर्घ समयout = 60 * HZ;
		रुको_queue_entry_t रुको;
		bool requeue;

		/* अगर the object we're रुकोing क्रम is queued क्रम processing,
		 * then just put ourselves on the queue behind it */
		अगर (work_pending(&xobject->fscache.work)) अणु
			_debug("queue OBJ%x behind OBJ%x immediately",
			       object->fscache.debug_id,
			       xobject->fscache.debug_id);
			जाओ requeue;
		पूर्ण

		/* otherwise we sleep until either the object we're रुकोing क्रम
		 * is करोne, or the fscache_object is congested */
		wq = bit_रुकोqueue(&xobject->flags, CACHEखाताS_OBJECT_ACTIVE);
		init_रुको(&रुको);
		requeue = false;
		करो अणु
			prepare_to_रुको(wq, &रुको, TASK_UNINTERRUPTIBLE);
			अगर (!test_bit(CACHEखाताS_OBJECT_ACTIVE, &xobject->flags))
				अवरोध;

			requeue = fscache_object_sleep_till_congested(&समयout);
		पूर्ण जबतक (समयout > 0 && !requeue);
		finish_रुको(wq, &रुको);

		अगर (requeue &&
		    test_bit(CACHEखाताS_OBJECT_ACTIVE, &xobject->flags)) अणु
			_debug("queue OBJ%x behind OBJ%x after wait",
			       object->fscache.debug_id,
			       xobject->fscache.debug_id);
			जाओ requeue;
		पूर्ण

		अगर (समयout <= 0) अणु
			pr_err("\n");
			pr_err("Error: Overlong wait for old active object to go away\n");
			cachefiles_prपूर्णांकk_object(object, xobject);
			जाओ requeue;
		पूर्ण
	पूर्ण

	ASSERT(!test_bit(CACHEखाताS_OBJECT_ACTIVE, &xobject->flags));

	cache->cache.ops->put_object(&xobject->fscache,
		(क्रमागत fscache_obj_ref_trace)cachefiles_obj_put_रुको_retry);
	जाओ try_again;

requeue:
	cache->cache.ops->put_object(&xobject->fscache,
		(क्रमागत fscache_obj_ref_trace)cachefiles_obj_put_रुको_समयo);
	_leave(" = -ETIMEDOUT");
	वापस -ETIMEDOUT;
पूर्ण

/*
 * Mark an object as being inactive.
 */
व्योम cachefiles_mark_object_inactive(काष्ठा cachefiles_cache *cache,
				     काष्ठा cachefiles_object *object,
				     blkcnt_t i_blocks)
अणु
	काष्ठा dentry *dentry = object->dentry;
	काष्ठा inode *inode = d_backing_inode(dentry);

	trace_cachefiles_mark_inactive(object, dentry, inode);

	ग_लिखो_lock(&cache->active_lock);
	rb_erase(&object->active_node, &cache->active_nodes);
	clear_bit(CACHEखाताS_OBJECT_ACTIVE, &object->flags);
	ग_लिखो_unlock(&cache->active_lock);

	wake_up_bit(&object->flags, CACHEखाताS_OBJECT_ACTIVE);

	/* This object can now be culled, so we need to let the daemon know
	 * that there is something it can हटाओ अगर it needs to.
	 */
	atomic_दीर्घ_add(i_blocks, &cache->b_released);
	अगर (atomic_inc_वापस(&cache->f_released))
		cachefiles_state_changed(cache);
पूर्ण

/*
 * delete an object representation from the cache
 * - file backed objects are unlinked
 * - directory backed objects are stuffed पूर्णांकo the graveyard क्रम userspace to
 *   delete
 * - unlocks the directory mutex
 */
अटल पूर्णांक cachefiles_bury_object(काष्ठा cachefiles_cache *cache,
				  काष्ठा cachefiles_object *object,
				  काष्ठा dentry *dir,
				  काष्ठा dentry *rep,
				  bool preemptive,
				  क्रमागत fscache_why_object_समाप्तed why)
अणु
	काष्ठा dentry *grave, *trap;
	काष्ठा path path, path_to_graveyard;
	अक्षर nbuffer[8 + 8 + 1];
	पूर्णांक ret;

	_enter(",'%pd','%pd'", dir, rep);

	_debug("remove %p from %p", rep, dir);

	/* non-directories can just be unlinked */
	अगर (!d_is_dir(rep)) अणु
		_debug("unlink stale object");

		path.mnt = cache->mnt;
		path.dentry = dir;
		ret = security_path_unlink(&path, rep);
		अगर (ret < 0) अणु
			cachefiles_io_error(cache, "Unlink security error");
		पूर्ण अन्यथा अणु
			trace_cachefiles_unlink(object, rep, why);
			ret = vfs_unlink(&init_user_ns, d_inode(dir), rep,
					 शून्य);

			अगर (preemptive)
				cachefiles_mark_object_buried(cache, rep, why);
		पूर्ण

		inode_unlock(d_inode(dir));

		अगर (ret == -EIO)
			cachefiles_io_error(cache, "Unlink failed");

		_leave(" = %d", ret);
		वापस ret;
	पूर्ण

	/* directories have to be moved to the graveyard */
	_debug("move stale object to graveyard");
	inode_unlock(d_inode(dir));

try_again:
	/* first step is to make up a grave dentry in the graveyard */
	प्र_लिखो(nbuffer, "%08x%08x",
		(uपूर्णांक32_t) kसमय_get_real_seconds(),
		(uपूर्णांक32_t) atomic_inc_वापस(&cache->gravecounter));

	/* करो the multiway lock magic */
	trap = lock_नाम(cache->graveyard, dir);

	/* करो some checks beक्रमe getting the grave dentry */
	अगर (rep->d_parent != dir || IS_DEADसूची(d_inode(rep))) अणु
		/* the entry was probably culled when we dropped the parent dir
		 * lock */
		unlock_नाम(cache->graveyard, dir);
		_leave(" = 0 [culled?]");
		वापस 0;
	पूर्ण

	अगर (!d_can_lookup(cache->graveyard)) अणु
		unlock_नाम(cache->graveyard, dir);
		cachefiles_io_error(cache, "Graveyard no longer a directory");
		वापस -EIO;
	पूर्ण

	अगर (trap == rep) अणु
		unlock_नाम(cache->graveyard, dir);
		cachefiles_io_error(cache, "May not make directory loop");
		वापस -EIO;
	पूर्ण

	अगर (d_mountpoपूर्णांक(rep)) अणु
		unlock_नाम(cache->graveyard, dir);
		cachefiles_io_error(cache, "Mountpoint in cache");
		वापस -EIO;
	पूर्ण

	grave = lookup_one_len(nbuffer, cache->graveyard, म_माप(nbuffer));
	अगर (IS_ERR(grave)) अणु
		unlock_नाम(cache->graveyard, dir);

		अगर (PTR_ERR(grave) == -ENOMEM) अणु
			_leave(" = -ENOMEM");
			वापस -ENOMEM;
		पूर्ण

		cachefiles_io_error(cache, "Lookup error %ld",
				    PTR_ERR(grave));
		वापस -EIO;
	पूर्ण

	अगर (d_is_positive(grave)) अणु
		unlock_नाम(cache->graveyard, dir);
		dput(grave);
		grave = शून्य;
		cond_resched();
		जाओ try_again;
	पूर्ण

	अगर (d_mountpoपूर्णांक(grave)) अणु
		unlock_नाम(cache->graveyard, dir);
		dput(grave);
		cachefiles_io_error(cache, "Mountpoint in graveyard");
		वापस -EIO;
	पूर्ण

	/* target should not be an ancestor of source */
	अगर (trap == grave) अणु
		unlock_नाम(cache->graveyard, dir);
		dput(grave);
		cachefiles_io_error(cache, "May not make directory loop");
		वापस -EIO;
	पूर्ण

	/* attempt the नाम */
	path.mnt = cache->mnt;
	path.dentry = dir;
	path_to_graveyard.mnt = cache->mnt;
	path_to_graveyard.dentry = cache->graveyard;
	ret = security_path_नाम(&path, rep, &path_to_graveyard, grave, 0);
	अगर (ret < 0) अणु
		cachefiles_io_error(cache, "Rename security error %d", ret);
	पूर्ण अन्यथा अणु
		काष्ठा नामdata rd = अणु
			.old_mnt_userns	= &init_user_ns,
			.old_dir	= d_inode(dir),
			.old_dentry	= rep,
			.new_mnt_userns	= &init_user_ns,
			.new_dir	= d_inode(cache->graveyard),
			.new_dentry	= grave,
		पूर्ण;
		trace_cachefiles_नाम(object, rep, grave, why);
		ret = vfs_नाम(&rd);
		अगर (ret != 0 && ret != -ENOMEM)
			cachefiles_io_error(cache,
					    "Rename failed with error %d", ret);

		अगर (preemptive)
			cachefiles_mark_object_buried(cache, rep, why);
	पूर्ण

	unlock_नाम(cache->graveyard, dir);
	dput(grave);
	_leave(" = 0");
	वापस 0;
पूर्ण

/*
 * delete an object representation from the cache
 */
पूर्णांक cachefiles_delete_object(काष्ठा cachefiles_cache *cache,
			     काष्ठा cachefiles_object *object)
अणु
	काष्ठा dentry *dir;
	पूर्णांक ret;

	_enter(",OBJ%x{%p}", object->fscache.debug_id, object->dentry);

	ASSERT(object->dentry);
	ASSERT(d_backing_inode(object->dentry));
	ASSERT(object->dentry->d_parent);

	dir = dget_parent(object->dentry);

	inode_lock_nested(d_inode(dir), I_MUTEX_PARENT);

	अगर (test_bit(FSCACHE_OBJECT_KILLED_BY_CACHE, &object->fscache.flags)) अणु
		/* object allocation क्रम the same key preemptively deleted this
		 * object's file so that it could create its own file */
		_debug("object preemptively buried");
		inode_unlock(d_inode(dir));
		ret = 0;
	पूर्ण अन्यथा अणु
		/* we need to check that our parent is _still_ our parent - it
		 * may have been नामd */
		अगर (dir == object->dentry->d_parent) अणु
			ret = cachefiles_bury_object(cache, object, dir,
						     object->dentry, false,
						     FSCACHE_OBJECT_WAS_RETIRED);
		पूर्ण अन्यथा अणु
			/* it got moved, presumably by cachefilesd culling it,
			 * so it's no दीर्घer in the key path and we can ignore
			 * it */
			inode_unlock(d_inode(dir));
			ret = 0;
		पूर्ण
	पूर्ण

	dput(dir);
	_leave(" = %d", ret);
	वापस ret;
पूर्ण

/*
 * walk from the parent object to the child object through the backing
 * fileप्रणाली, creating directories as we go
 */
पूर्णांक cachefiles_walk_to_object(काष्ठा cachefiles_object *parent,
			      काष्ठा cachefiles_object *object,
			      स्थिर अक्षर *key,
			      काष्ठा cachefiles_xattr *auxdata)
अणु
	काष्ठा cachefiles_cache *cache;
	काष्ठा dentry *dir, *next = शून्य;
	काष्ठा inode *inode;
	काष्ठा path path;
	अचिन्हित दीर्घ start;
	स्थिर अक्षर *name;
	पूर्णांक ret, nlen;

	_enter("OBJ%x{%p},OBJ%x,%s,",
	       parent->fscache.debug_id, parent->dentry,
	       object->fscache.debug_id, key);

	cache = container_of(parent->fscache.cache,
			     काष्ठा cachefiles_cache, cache);
	path.mnt = cache->mnt;

	ASSERT(parent->dentry);
	ASSERT(d_backing_inode(parent->dentry));

	अगर (!(d_is_dir(parent->dentry))) अणु
		// TODO: convert file to dir
		_leave("looking up in none directory");
		वापस -ENOBUFS;
	पूर्ण

	dir = dget(parent->dentry);

advance:
	/* attempt to transit the first directory component */
	name = key;
	nlen = म_माप(key);

	/* key ends in a द्विगुन NUL */
	key = key + nlen + 1;
	अगर (!*key)
		key = शून्य;

lookup_again:
	/* search the current directory क्रम the element name */
	_debug("lookup '%s'", name);

	inode_lock_nested(d_inode(dir), I_MUTEX_PARENT);

	start = jअगरfies;
	next = lookup_one_len(name, dir, nlen);
	cachefiles_hist(cachefiles_lookup_histogram, start);
	अगर (IS_ERR(next)) अणु
		trace_cachefiles_lookup(object, next, शून्य);
		जाओ lookup_error;
	पूर्ण

	inode = d_backing_inode(next);
	trace_cachefiles_lookup(object, next, inode);
	_debug("next -> %p %s", next, inode ? "positive" : "negative");

	अगर (!key)
		object->new = !inode;

	/* अगर this element of the path करोesn't exist, then the lookup phase
	 * failed, and we can release any पढ़ोers in the certain knowledge that
	 * there's nothing क्रम them to actually पढ़ो */
	अगर (d_is_negative(next))
		fscache_object_lookup_negative(&object->fscache);

	/* we need to create the object अगर it's negative */
	अगर (key || object->type == FSCACHE_COOKIE_TYPE_INDEX) अणु
		/* index objects and पूर्णांकervening tree levels must be subdirs */
		अगर (d_is_negative(next)) अणु
			ret = cachefiles_has_space(cache, 1, 0);
			अगर (ret < 0)
				जाओ no_space_error;

			path.dentry = dir;
			ret = security_path_सूची_गढ़ो(&path, next, 0);
			अगर (ret < 0)
				जाओ create_error;
			start = jअगरfies;
			ret = vfs_सूची_गढ़ो(&init_user_ns, d_inode(dir), next, 0);
			cachefiles_hist(cachefiles_सूची_गढ़ो_histogram, start);
			अगर (!key)
				trace_cachefiles_सूची_गढ़ो(object, next, ret);
			अगर (ret < 0)
				जाओ create_error;

			अगर (unlikely(d_unhashed(next))) अणु
				dput(next);
				inode_unlock(d_inode(dir));
				जाओ lookup_again;
			पूर्ण
			ASSERT(d_backing_inode(next));

			_debug("mkdir -> %p{%p{ino=%lu}}",
			       next, d_backing_inode(next), d_backing_inode(next)->i_ino);

		पूर्ण अन्यथा अगर (!d_can_lookup(next)) अणु
			pr_err("inode %lu is not a directory\n",
			       d_backing_inode(next)->i_ino);
			ret = -ENOBUFS;
			जाओ error;
		पूर्ण

	पूर्ण अन्यथा अणु
		/* non-index objects start out lअगरe as files */
		अगर (d_is_negative(next)) अणु
			ret = cachefiles_has_space(cache, 1, 0);
			अगर (ret < 0)
				जाओ no_space_error;

			path.dentry = dir;
			ret = security_path_mknod(&path, next, S_IFREG, 0);
			अगर (ret < 0)
				जाओ create_error;
			start = jअगरfies;
			ret = vfs_create(&init_user_ns, d_inode(dir), next,
					 S_IFREG, true);
			cachefiles_hist(cachefiles_create_histogram, start);
			trace_cachefiles_create(object, next, ret);
			अगर (ret < 0)
				जाओ create_error;

			ASSERT(d_backing_inode(next));

			_debug("create -> %p{%p{ino=%lu}}",
			       next, d_backing_inode(next), d_backing_inode(next)->i_ino);

		पूर्ण अन्यथा अगर (!d_can_lookup(next) &&
			   !d_is_reg(next)
			   ) अणु
			pr_err("inode %lu is not a file or directory\n",
			       d_backing_inode(next)->i_ino);
			ret = -ENOBUFS;
			जाओ error;
		पूर्ण
	पूर्ण

	/* process the next component */
	अगर (key) अणु
		_debug("advance");
		inode_unlock(d_inode(dir));
		dput(dir);
		dir = next;
		next = शून्य;
		जाओ advance;
	पूर्ण

	/* we've found the object we were looking क्रम */
	object->dentry = next;

	/* अगर we've found that the terminal object exists, then we need to
	 * check its attributes and delete it अगर it's out of date */
	अगर (!object->new) अणु
		_debug("validate '%pd'", next);

		ret = cachefiles_check_object_xattr(object, auxdata);
		अगर (ret == -ESTALE) अणु
			/* delete the object (the deleter drops the directory
			 * mutex) */
			object->dentry = शून्य;

			ret = cachefiles_bury_object(cache, object, dir, next,
						     true,
						     FSCACHE_OBJECT_IS_STALE);
			dput(next);
			next = शून्य;

			अगर (ret < 0)
				जाओ delete_error;

			_debug("redo lookup");
			fscache_object_retrying_stale(&object->fscache);
			जाओ lookup_again;
		पूर्ण
	पूर्ण

	/* note that we're now using this object */
	ret = cachefiles_mark_object_active(cache, object);

	inode_unlock(d_inode(dir));
	dput(dir);
	dir = शून्य;

	अगर (ret == -ETIMEDOUT)
		जाओ mark_active_समयd_out;

	_debug("=== OBTAINED_OBJECT ===");

	अगर (object->new) अणु
		/* attach data to a newly स्थिरructed terminal object */
		ret = cachefiles_set_object_xattr(object, auxdata);
		अगर (ret < 0)
			जाओ check_error;
	पूर्ण अन्यथा अणु
		/* always update the aसमय on an object we've just looked up
		 * (this is used to keep track of culling, and aबार are only
		 * updated by पढ़ो, ग_लिखो and सूची_पढ़ो but not lookup or
		 * खोलो) */
		path.dentry = next;
		touch_aसमय(&path);
	पूर्ण

	/* खोलो a file पूर्णांकerface onto a data file */
	अगर (object->type != FSCACHE_COOKIE_TYPE_INDEX) अणु
		अगर (d_is_reg(object->dentry)) अणु
			स्थिर काष्ठा address_space_operations *aops;

			ret = -EPERM;
			aops = d_backing_inode(object->dentry)->i_mapping->a_ops;
			अगर (!aops->bmap)
				जाओ check_error;
			अगर (object->dentry->d_sb->s_blocksize > PAGE_SIZE)
				जाओ check_error;

			object->backer = object->dentry;
		पूर्ण अन्यथा अणु
			BUG(); // TODO: खोलो file in data-class subdir
		पूर्ण
	पूर्ण

	object->new = 0;
	fscache_obtained_object(&object->fscache);

	_leave(" = 0 [%lu]", d_backing_inode(object->dentry)->i_ino);
	वापस 0;

no_space_error:
	fscache_object_mark_समाप्तed(&object->fscache, FSCACHE_OBJECT_NO_SPACE);
create_error:
	_debug("create error %d", ret);
	अगर (ret == -EIO)
		cachefiles_io_error(cache, "Create/mkdir failed");
	जाओ error;

mark_active_समयd_out:
	_debug("mark active timed out");
	जाओ release_dentry;

check_error:
	_debug("check error %d", ret);
	cachefiles_mark_object_inactive(
		cache, object, d_backing_inode(object->dentry)->i_blocks);
release_dentry:
	dput(object->dentry);
	object->dentry = शून्य;
	जाओ error_out;

delete_error:
	_debug("delete error %d", ret);
	जाओ error_out2;

lookup_error:
	_debug("lookup error %ld", PTR_ERR(next));
	ret = PTR_ERR(next);
	अगर (ret == -EIO)
		cachefiles_io_error(cache, "Lookup failed");
	next = शून्य;
error:
	inode_unlock(d_inode(dir));
	dput(next);
error_out2:
	dput(dir);
error_out:
	_leave(" = error %d", -ret);
	वापस ret;
पूर्ण

/*
 * get a subdirectory
 */
काष्ठा dentry *cachefiles_get_directory(काष्ठा cachefiles_cache *cache,
					काष्ठा dentry *dir,
					स्थिर अक्षर *स_नाम)
अणु
	काष्ठा dentry *subdir;
	अचिन्हित दीर्घ start;
	काष्ठा path path;
	पूर्णांक ret;

	_enter(",,%s", स_नाम);

	/* search the current directory क्रम the element name */
	inode_lock(d_inode(dir));

retry:
	start = jअगरfies;
	subdir = lookup_one_len(स_नाम, dir, म_माप(स_नाम));
	cachefiles_hist(cachefiles_lookup_histogram, start);
	अगर (IS_ERR(subdir)) अणु
		अगर (PTR_ERR(subdir) == -ENOMEM)
			जाओ nomem_d_alloc;
		जाओ lookup_error;
	पूर्ण

	_debug("subdir -> %p %s",
	       subdir, d_backing_inode(subdir) ? "positive" : "negative");

	/* we need to create the subdir अगर it करोesn't exist yet */
	अगर (d_is_negative(subdir)) अणु
		ret = cachefiles_has_space(cache, 1, 0);
		अगर (ret < 0)
			जाओ सूची_गढ़ो_error;

		_debug("attempt mkdir");

		path.mnt = cache->mnt;
		path.dentry = dir;
		ret = security_path_सूची_गढ़ो(&path, subdir, 0700);
		अगर (ret < 0)
			जाओ सूची_गढ़ो_error;
		ret = vfs_सूची_गढ़ो(&init_user_ns, d_inode(dir), subdir, 0700);
		अगर (ret < 0)
			जाओ सूची_गढ़ो_error;

		अगर (unlikely(d_unhashed(subdir))) अणु
			dput(subdir);
			जाओ retry;
		पूर्ण
		ASSERT(d_backing_inode(subdir));

		_debug("mkdir -> %p{%p{ino=%lu}}",
		       subdir,
		       d_backing_inode(subdir),
		       d_backing_inode(subdir)->i_ino);
	पूर्ण

	inode_unlock(d_inode(dir));

	/* we need to make sure the subdir is a directory */
	ASSERT(d_backing_inode(subdir));

	अगर (!d_can_lookup(subdir)) अणु
		pr_err("%s is not a directory\n", स_नाम);
		ret = -EIO;
		जाओ check_error;
	पूर्ण

	ret = -EPERM;
	अगर (!(d_backing_inode(subdir)->i_opflags & IOP_XATTR) ||
	    !d_backing_inode(subdir)->i_op->lookup ||
	    !d_backing_inode(subdir)->i_op->सूची_गढ़ो ||
	    !d_backing_inode(subdir)->i_op->create ||
	    !d_backing_inode(subdir)->i_op->नाम ||
	    !d_backing_inode(subdir)->i_op->सूची_हटाओ ||
	    !d_backing_inode(subdir)->i_op->unlink)
		जाओ check_error;

	_leave(" = [%lu]", d_backing_inode(subdir)->i_ino);
	वापस subdir;

check_error:
	dput(subdir);
	_leave(" = %d [check]", ret);
	वापस ERR_PTR(ret);

सूची_गढ़ो_error:
	inode_unlock(d_inode(dir));
	dput(subdir);
	pr_err("mkdir %s failed with error %d\n", स_नाम, ret);
	वापस ERR_PTR(ret);

lookup_error:
	inode_unlock(d_inode(dir));
	ret = PTR_ERR(subdir);
	pr_err("Lookup %s failed with error %d\n", स_नाम, ret);
	वापस ERR_PTR(ret);

nomem_d_alloc:
	inode_unlock(d_inode(dir));
	_leave(" = -ENOMEM");
	वापस ERR_PTR(-ENOMEM);
पूर्ण

/*
 * find out अगर an object is in use or not
 * - अगर finds object and it's not in use:
 *   - वापसs a poपूर्णांकer to the object and a reference on it
 *   - वापसs with the directory locked
 */
अटल काष्ठा dentry *cachefiles_check_active(काष्ठा cachefiles_cache *cache,
					      काष्ठा dentry *dir,
					      अक्षर *filename)
अणु
	काष्ठा cachefiles_object *object;
	काष्ठा rb_node *_n;
	काष्ठा dentry *victim;
	अचिन्हित दीर्घ start;
	पूर्णांक ret;

	//_enter(",%pd/,%s",
	//       dir, filename);

	/* look up the victim */
	inode_lock_nested(d_inode(dir), I_MUTEX_PARENT);

	start = jअगरfies;
	victim = lookup_one_len(filename, dir, म_माप(filename));
	cachefiles_hist(cachefiles_lookup_histogram, start);
	अगर (IS_ERR(victim))
		जाओ lookup_error;

	//_debug("victim -> %p %s",
	//       victim, d_backing_inode(victim) ? "positive" : "negative");

	/* अगर the object is no दीर्घer there then we probably retired the object
	 * at the netfs's request whilst the cull was in progress
	 */
	अगर (d_is_negative(victim)) अणु
		inode_unlock(d_inode(dir));
		dput(victim);
		_leave(" = -ENOENT [absent]");
		वापस ERR_PTR(-ENOENT);
	पूर्ण

	/* check to see अगर we're using this object */
	पढ़ो_lock(&cache->active_lock);

	_n = cache->active_nodes.rb_node;

	जबतक (_n) अणु
		object = rb_entry(_n, काष्ठा cachefiles_object, active_node);

		अगर (object->dentry > victim)
			_n = _n->rb_left;
		अन्यथा अगर (object->dentry < victim)
			_n = _n->rb_right;
		अन्यथा
			जाओ object_in_use;
	पूर्ण

	पढ़ो_unlock(&cache->active_lock);

	//_leave(" = %p", victim);
	वापस victim;

object_in_use:
	पढ़ो_unlock(&cache->active_lock);
	inode_unlock(d_inode(dir));
	dput(victim);
	//_leave(" = -EBUSY [in use]");
	वापस ERR_PTR(-EBUSY);

lookup_error:
	inode_unlock(d_inode(dir));
	ret = PTR_ERR(victim);
	अगर (ret == -ENOENT) अणु
		/* file or dir now असलent - probably retired by netfs */
		_leave(" = -ESTALE [absent]");
		वापस ERR_PTR(-ESTALE);
	पूर्ण

	अगर (ret == -EIO) अणु
		cachefiles_io_error(cache, "Lookup failed");
	पूर्ण अन्यथा अगर (ret != -ENOMEM) अणु
		pr_err("Internal error: %d\n", ret);
		ret = -EIO;
	पूर्ण

	_leave(" = %d", ret);
	वापस ERR_PTR(ret);
पूर्ण

/*
 * cull an object अगर it's not in use
 * - called only by cache manager daemon
 */
पूर्णांक cachefiles_cull(काष्ठा cachefiles_cache *cache, काष्ठा dentry *dir,
		    अक्षर *filename)
अणु
	काष्ठा dentry *victim;
	पूर्णांक ret;

	_enter(",%pd/,%s", dir, filename);

	victim = cachefiles_check_active(cache, dir, filename);
	अगर (IS_ERR(victim))
		वापस PTR_ERR(victim);

	_debug("victim -> %p %s",
	       victim, d_backing_inode(victim) ? "positive" : "negative");

	/* okay... the victim is not being used so we can cull it
	 * - start by marking it as stale
	 */
	_debug("victim is cullable");

	ret = cachefiles_हटाओ_object_xattr(cache, victim);
	अगर (ret < 0)
		जाओ error_unlock;

	/*  actually हटाओ the victim (drops the dir mutex) */
	_debug("bury");

	ret = cachefiles_bury_object(cache, शून्य, dir, victim, false,
				     FSCACHE_OBJECT_WAS_CULLED);
	अगर (ret < 0)
		जाओ error;

	dput(victim);
	_leave(" = 0");
	वापस 0;

error_unlock:
	inode_unlock(d_inode(dir));
error:
	dput(victim);
	अगर (ret == -ENOENT) अणु
		/* file or dir now असलent - probably retired by netfs */
		_leave(" = -ESTALE [absent]");
		वापस -ESTALE;
	पूर्ण

	अगर (ret != -ENOMEM) अणु
		pr_err("Internal error: %d\n", ret);
		ret = -EIO;
	पूर्ण

	_leave(" = %d", ret);
	वापस ret;
पूर्ण

/*
 * find out अगर an object is in use or not
 * - called only by cache manager daemon
 * - वापसs -EBUSY or 0 to indicate whether an object is in use or not
 */
पूर्णांक cachefiles_check_in_use(काष्ठा cachefiles_cache *cache, काष्ठा dentry *dir,
			    अक्षर *filename)
अणु
	काष्ठा dentry *victim;

	//_enter(",%pd/,%s",
	//       dir, filename);

	victim = cachefiles_check_active(cache, dir, filename);
	अगर (IS_ERR(victim))
		वापस PTR_ERR(victim);

	inode_unlock(d_inode(dir));
	dput(victim);
	//_leave(" = 0");
	वापस 0;
पूर्ण
