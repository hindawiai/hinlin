<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only

#समावेश <linux/export.h>
#समावेश <linux/nsproxy.h>
#समावेश <linux/slab.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/user_namespace.h>
#समावेश <linux/proc_ns.h>
#समावेश <linux/highuid.h>
#समावेश <linux/cred.h>
#समावेश <linux/securebits.h>
#समावेश <linux/keyctl.h>
#समावेश <linux/key-type.h>
#समावेश <keys/user-type.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/fs.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/projid.h>
#समावेश <linux/fs_काष्ठा.h>
#समावेश <linux/द्वा_खोज.h>
#समावेश <linux/sort.h>

अटल काष्ठा kmem_cache *user_ns_cachep __पढ़ो_mostly;
अटल DEFINE_MUTEX(userns_state_mutex);

अटल bool new_idmap_permitted(स्थिर काष्ठा file *file,
				काष्ठा user_namespace *ns, पूर्णांक cap_setid,
				काष्ठा uid_gid_map *map);
अटल व्योम मुक्त_user_ns(काष्ठा work_काष्ठा *work);

अटल काष्ठा ucounts *inc_user_namespaces(काष्ठा user_namespace *ns, kuid_t uid)
अणु
	वापस inc_ucount(ns, uid, UCOUNT_USER_NAMESPACES);
पूर्ण

अटल व्योम dec_user_namespaces(काष्ठा ucounts *ucounts)
अणु
	वापस dec_ucount(ucounts, UCOUNT_USER_NAMESPACES);
पूर्ण

अटल व्योम set_cred_user_ns(काष्ठा cred *cred, काष्ठा user_namespace *user_ns)
अणु
	/* Start with the same capabilities as init but useless क्रम करोing
	 * anything as the capabilities are bound to the new user namespace.
	 */
	cred->securebits = SECUREBITS_DEFAULT;
	cred->cap_inheritable = CAP_EMPTY_SET;
	cred->cap_permitted = CAP_FULL_SET;
	cred->cap_effective = CAP_FULL_SET;
	cred->cap_ambient = CAP_EMPTY_SET;
	cred->cap_bset = CAP_FULL_SET;
#अगर_घोषित CONFIG_KEYS
	key_put(cred->request_key_auth);
	cred->request_key_auth = शून्य;
#पूर्ण_अगर
	/* tgcred will be cleared in our caller bc CLONE_THREAD won't be set */
	cred->user_ns = user_ns;
पूर्ण

/*
 * Create a new user namespace, deriving the creator from the user in the
 * passed credentials, and replacing that user with the new root user क्रम the
 * new namespace.
 *
 * This is called by copy_creds(), which will finish setting the target task's
 * credentials.
 */
पूर्णांक create_user_ns(काष्ठा cred *new)
अणु
	काष्ठा user_namespace *ns, *parent_ns = new->user_ns;
	kuid_t owner = new->euid;
	kgid_t group = new->egid;
	काष्ठा ucounts *ucounts;
	पूर्णांक ret, i;

	ret = -ENOSPC;
	अगर (parent_ns->level > 32)
		जाओ fail;

	ucounts = inc_user_namespaces(parent_ns, owner);
	अगर (!ucounts)
		जाओ fail;

	/*
	 * Verअगरy that we can not violate the policy of which files
	 * may be accessed that is specअगरied by the root directory,
	 * by verअगरying that the root directory is at the root of the
	 * mount namespace which allows all files to be accessed.
	 */
	ret = -EPERM;
	अगर (current_chrooted())
		जाओ fail_dec;

	/* The creator needs a mapping in the parent user namespace
	 * or अन्यथा we won't be able to reasonably tell userspace who
	 * created a user_namespace.
	 */
	ret = -EPERM;
	अगर (!kuid_has_mapping(parent_ns, owner) ||
	    !kgid_has_mapping(parent_ns, group))
		जाओ fail_dec;

	ret = -ENOMEM;
	ns = kmem_cache_zalloc(user_ns_cachep, GFP_KERNEL);
	अगर (!ns)
		जाओ fail_dec;

	ns->parent_could_setfcap = cap_उठाओd(new->cap_effective, CAP_SETFCAP);
	ret = ns_alloc_inum(&ns->ns);
	अगर (ret)
		जाओ fail_मुक्त;
	ns->ns.ops = &userns_operations;

	refcount_set(&ns->ns.count, 1);
	/* Leave the new->user_ns reference with the new user namespace. */
	ns->parent = parent_ns;
	ns->level = parent_ns->level + 1;
	ns->owner = owner;
	ns->group = group;
	INIT_WORK(&ns->work, मुक्त_user_ns);
	क्रम (i = 0; i < UCOUNT_COUNTS; i++) अणु
		ns->ucount_max[i] = पूर्णांक_उच्च;
	पूर्ण
	ns->ucounts = ucounts;

	/* Inherit USERNS_SETGROUPS_ALLOWED from our parent */
	mutex_lock(&userns_state_mutex);
	ns->flags = parent_ns->flags;
	mutex_unlock(&userns_state_mutex);

#अगर_घोषित CONFIG_KEYS
	INIT_LIST_HEAD(&ns->keyring_name_list);
	init_rwsem(&ns->keyring_sem);
#पूर्ण_अगर
	ret = -ENOMEM;
	अगर (!setup_userns_sysctls(ns))
		जाओ fail_keyring;

	set_cred_user_ns(new, ns);
	वापस 0;
fail_keyring:
#अगर_घोषित CONFIG_PERSISTENT_KEYRINGS
	key_put(ns->persistent_keyring_रेजिस्टर);
#पूर्ण_अगर
	ns_मुक्त_inum(&ns->ns);
fail_मुक्त:
	kmem_cache_मुक्त(user_ns_cachep, ns);
fail_dec:
	dec_user_namespaces(ucounts);
fail:
	वापस ret;
पूर्ण

पूर्णांक unshare_userns(अचिन्हित दीर्घ unshare_flags, काष्ठा cred **new_cred)
अणु
	काष्ठा cred *cred;
	पूर्णांक err = -ENOMEM;

	अगर (!(unshare_flags & CLONE_NEWUSER))
		वापस 0;

	cred = prepare_creds();
	अगर (cred) अणु
		err = create_user_ns(cred);
		अगर (err)
			put_cred(cred);
		अन्यथा
			*new_cred = cred;
	पूर्ण

	वापस err;
पूर्ण

अटल व्योम मुक्त_user_ns(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा user_namespace *parent, *ns =
		container_of(work, काष्ठा user_namespace, work);

	करो अणु
		काष्ठा ucounts *ucounts = ns->ucounts;
		parent = ns->parent;
		अगर (ns->gid_map.nr_extents > UID_GID_MAP_MAX_BASE_EXTENTS) अणु
			kमुक्त(ns->gid_map.क्रमward);
			kमुक्त(ns->gid_map.reverse);
		पूर्ण
		अगर (ns->uid_map.nr_extents > UID_GID_MAP_MAX_BASE_EXTENTS) अणु
			kमुक्त(ns->uid_map.क्रमward);
			kमुक्त(ns->uid_map.reverse);
		पूर्ण
		अगर (ns->projid_map.nr_extents > UID_GID_MAP_MAX_BASE_EXTENTS) अणु
			kमुक्त(ns->projid_map.क्रमward);
			kमुक्त(ns->projid_map.reverse);
		पूर्ण
		retire_userns_sysctls(ns);
		key_मुक्त_user_ns(ns);
		ns_मुक्त_inum(&ns->ns);
		kmem_cache_मुक्त(user_ns_cachep, ns);
		dec_user_namespaces(ucounts);
		ns = parent;
	पूर्ण जबतक (refcount_dec_and_test(&parent->ns.count));
पूर्ण

व्योम __put_user_ns(काष्ठा user_namespace *ns)
अणु
	schedule_work(&ns->work);
पूर्ण
EXPORT_SYMBOL(__put_user_ns);

/**
 * idmap_key काष्ठा holds the inक्रमmation necessary to find an idmapping in a
 * sorted idmap array. It is passed to cmp_map_id() as first argument.
 */
काष्ठा idmap_key अणु
	bool map_up; /* true  -> id from kid; false -> kid from id */
	u32 id; /* id to find */
	u32 count; /* == 0 unless used with map_id_range_करोwn() */
पूर्ण;

/**
 * cmp_map_id - Function to be passed to द्वा_खोज() to find the requested
 * idmapping. Expects काष्ठा idmap_key to be passed via @k.
 */
अटल पूर्णांक cmp_map_id(स्थिर व्योम *k, स्थिर व्योम *e)
अणु
	u32 first, last, id2;
	स्थिर काष्ठा idmap_key *key = k;
	स्थिर काष्ठा uid_gid_extent *el = e;

	id2 = key->id + key->count - 1;

	/* handle map_id_अणुकरोwn,upपूर्ण() */
	अगर (key->map_up)
		first = el->lower_first;
	अन्यथा
		first = el->first;

	last = first + el->count - 1;

	अगर (key->id >= first && key->id <= last &&
	    (id2 >= first && id2 <= last))
		वापस 0;

	अगर (key->id < first || id2 < first)
		वापस -1;

	वापस 1;
पूर्ण

/**
 * map_id_range_करोwn_max - Find idmap via binary search in ordered idmap array.
 * Can only be called अगर number of mappings exceeds UID_GID_MAP_MAX_BASE_EXTENTS.
 */
अटल काष्ठा uid_gid_extent *
map_id_range_करोwn_max(अचिन्हित extents, काष्ठा uid_gid_map *map, u32 id, u32 count)
अणु
	काष्ठा idmap_key key;

	key.map_up = false;
	key.count = count;
	key.id = id;

	वापस द्वा_खोज(&key, map->क्रमward, extents,
		       माप(काष्ठा uid_gid_extent), cmp_map_id);
पूर्ण

/**
 * map_id_range_करोwn_base - Find idmap via binary search in अटल extent array.
 * Can only be called अगर number of mappings is equal or less than
 * UID_GID_MAP_MAX_BASE_EXTENTS.
 */
अटल काष्ठा uid_gid_extent *
map_id_range_करोwn_base(अचिन्हित extents, काष्ठा uid_gid_map *map, u32 id, u32 count)
अणु
	अचिन्हित idx;
	u32 first, last, id2;

	id2 = id + count - 1;

	/* Find the matching extent */
	क्रम (idx = 0; idx < extents; idx++) अणु
		first = map->extent[idx].first;
		last = first + map->extent[idx].count - 1;
		अगर (id >= first && id <= last &&
		    (id2 >= first && id2 <= last))
			वापस &map->extent[idx];
	पूर्ण
	वापस शून्य;
पूर्ण

अटल u32 map_id_range_करोwn(काष्ठा uid_gid_map *map, u32 id, u32 count)
अणु
	काष्ठा uid_gid_extent *extent;
	अचिन्हित extents = map->nr_extents;
	smp_rmb();

	अगर (extents <= UID_GID_MAP_MAX_BASE_EXTENTS)
		extent = map_id_range_करोwn_base(extents, map, id, count);
	अन्यथा
		extent = map_id_range_करोwn_max(extents, map, id, count);

	/* Map the id or note failure */
	अगर (extent)
		id = (id - extent->first) + extent->lower_first;
	अन्यथा
		id = (u32) -1;

	वापस id;
पूर्ण

अटल u32 map_id_करोwn(काष्ठा uid_gid_map *map, u32 id)
अणु
	वापस map_id_range_करोwn(map, id, 1);
पूर्ण

/**
 * map_id_up_base - Find idmap via binary search in अटल extent array.
 * Can only be called अगर number of mappings is equal or less than
 * UID_GID_MAP_MAX_BASE_EXTENTS.
 */
अटल काष्ठा uid_gid_extent *
map_id_up_base(अचिन्हित extents, काष्ठा uid_gid_map *map, u32 id)
अणु
	अचिन्हित idx;
	u32 first, last;

	/* Find the matching extent */
	क्रम (idx = 0; idx < extents; idx++) अणु
		first = map->extent[idx].lower_first;
		last = first + map->extent[idx].count - 1;
		अगर (id >= first && id <= last)
			वापस &map->extent[idx];
	पूर्ण
	वापस शून्य;
पूर्ण

/**
 * map_id_up_max - Find idmap via binary search in ordered idmap array.
 * Can only be called अगर number of mappings exceeds UID_GID_MAP_MAX_BASE_EXTENTS.
 */
अटल काष्ठा uid_gid_extent *
map_id_up_max(अचिन्हित extents, काष्ठा uid_gid_map *map, u32 id)
अणु
	काष्ठा idmap_key key;

	key.map_up = true;
	key.count = 1;
	key.id = id;

	वापस द्वा_खोज(&key, map->reverse, extents,
		       माप(काष्ठा uid_gid_extent), cmp_map_id);
पूर्ण

अटल u32 map_id_up(काष्ठा uid_gid_map *map, u32 id)
अणु
	काष्ठा uid_gid_extent *extent;
	अचिन्हित extents = map->nr_extents;
	smp_rmb();

	अगर (extents <= UID_GID_MAP_MAX_BASE_EXTENTS)
		extent = map_id_up_base(extents, map, id);
	अन्यथा
		extent = map_id_up_max(extents, map, id);

	/* Map the id or note failure */
	अगर (extent)
		id = (id - extent->lower_first) + extent->first;
	अन्यथा
		id = (u32) -1;

	वापस id;
पूर्ण

/**
 *	make_kuid - Map a user-namespace uid pair पूर्णांकo a kuid.
 *	@ns:  User namespace that the uid is in
 *	@uid: User identअगरier
 *
 *	Maps a user-namespace uid pair पूर्णांकo a kernel पूर्णांकernal kuid,
 *	and वापसs that kuid.
 *
 *	When there is no mapping defined क्रम the user-namespace uid
 *	pair INVALID_UID is वापसed.  Callers are expected to test
 *	क्रम and handle INVALID_UID being वापसed.  INVALID_UID
 *	may be tested क्रम using uid_valid().
 */
kuid_t make_kuid(काष्ठा user_namespace *ns, uid_t uid)
अणु
	/* Map the uid to a global kernel uid */
	वापस KUIDT_INIT(map_id_करोwn(&ns->uid_map, uid));
पूर्ण
EXPORT_SYMBOL(make_kuid);

/**
 *	from_kuid - Create a uid from a kuid user-namespace pair.
 *	@targ: The user namespace we want a uid in.
 *	@kuid: The kernel पूर्णांकernal uid to start with.
 *
 *	Map @kuid पूर्णांकo the user-namespace specअगरied by @targ and
 *	वापस the resulting uid.
 *
 *	There is always a mapping पूर्णांकo the initial user_namespace.
 *
 *	If @kuid has no mapping in @targ (uid_t)-1 is वापसed.
 */
uid_t from_kuid(काष्ठा user_namespace *targ, kuid_t kuid)
अणु
	/* Map the uid from a global kernel uid */
	वापस map_id_up(&targ->uid_map, __kuid_val(kuid));
पूर्ण
EXPORT_SYMBOL(from_kuid);

/**
 *	from_kuid_munged - Create a uid from a kuid user-namespace pair.
 *	@targ: The user namespace we want a uid in.
 *	@kuid: The kernel पूर्णांकernal uid to start with.
 *
 *	Map @kuid पूर्णांकo the user-namespace specअगरied by @targ and
 *	वापस the resulting uid.
 *
 *	There is always a mapping पूर्णांकo the initial user_namespace.
 *
 *	Unlike from_kuid from_kuid_munged never fails and always
 *	वापसs a valid uid.  This makes from_kuid_munged appropriate
 *	क्रम use in syscalls like stat and getuid where failing the
 *	प्रणाली call and failing to provide a valid uid are not an
 *	options.
 *
 *	If @kuid has no mapping in @targ overflowuid is वापसed.
 */
uid_t from_kuid_munged(काष्ठा user_namespace *targ, kuid_t kuid)
अणु
	uid_t uid;
	uid = from_kuid(targ, kuid);

	अगर (uid == (uid_t) -1)
		uid = overflowuid;
	वापस uid;
पूर्ण
EXPORT_SYMBOL(from_kuid_munged);

/**
 *	make_kgid - Map a user-namespace gid pair पूर्णांकo a kgid.
 *	@ns:  User namespace that the gid is in
 *	@gid: group identअगरier
 *
 *	Maps a user-namespace gid pair पूर्णांकo a kernel पूर्णांकernal kgid,
 *	and वापसs that kgid.
 *
 *	When there is no mapping defined क्रम the user-namespace gid
 *	pair INVALID_GID is वापसed.  Callers are expected to test
 *	क्रम and handle INVALID_GID being वापसed.  INVALID_GID may be
 *	tested क्रम using gid_valid().
 */
kgid_t make_kgid(काष्ठा user_namespace *ns, gid_t gid)
अणु
	/* Map the gid to a global kernel gid */
	वापस KGIDT_INIT(map_id_करोwn(&ns->gid_map, gid));
पूर्ण
EXPORT_SYMBOL(make_kgid);

/**
 *	from_kgid - Create a gid from a kgid user-namespace pair.
 *	@targ: The user namespace we want a gid in.
 *	@kgid: The kernel पूर्णांकernal gid to start with.
 *
 *	Map @kgid पूर्णांकo the user-namespace specअगरied by @targ and
 *	वापस the resulting gid.
 *
 *	There is always a mapping पूर्णांकo the initial user_namespace.
 *
 *	If @kgid has no mapping in @targ (gid_t)-1 is वापसed.
 */
gid_t from_kgid(काष्ठा user_namespace *targ, kgid_t kgid)
अणु
	/* Map the gid from a global kernel gid */
	वापस map_id_up(&targ->gid_map, __kgid_val(kgid));
पूर्ण
EXPORT_SYMBOL(from_kgid);

/**
 *	from_kgid_munged - Create a gid from a kgid user-namespace pair.
 *	@targ: The user namespace we want a gid in.
 *	@kgid: The kernel पूर्णांकernal gid to start with.
 *
 *	Map @kgid पूर्णांकo the user-namespace specअगरied by @targ and
 *	वापस the resulting gid.
 *
 *	There is always a mapping पूर्णांकo the initial user_namespace.
 *
 *	Unlike from_kgid from_kgid_munged never fails and always
 *	वापसs a valid gid.  This makes from_kgid_munged appropriate
 *	क्रम use in syscalls like stat and getgid where failing the
 *	प्रणाली call and failing to provide a valid gid are not options.
 *
 *	If @kgid has no mapping in @targ overflowgid is वापसed.
 */
gid_t from_kgid_munged(काष्ठा user_namespace *targ, kgid_t kgid)
अणु
	gid_t gid;
	gid = from_kgid(targ, kgid);

	अगर (gid == (gid_t) -1)
		gid = overflowgid;
	वापस gid;
पूर्ण
EXPORT_SYMBOL(from_kgid_munged);

/**
 *	make_kprojid - Map a user-namespace projid pair पूर्णांकo a kprojid.
 *	@ns:  User namespace that the projid is in
 *	@projid: Project identअगरier
 *
 *	Maps a user-namespace uid pair पूर्णांकo a kernel पूर्णांकernal kuid,
 *	and वापसs that kuid.
 *
 *	When there is no mapping defined क्रम the user-namespace projid
 *	pair INVALID_PROJID is वापसed.  Callers are expected to test
 *	क्रम and handle INVALID_PROJID being वापसed.  INVALID_PROJID
 *	may be tested क्रम using projid_valid().
 */
kprojid_t make_kprojid(काष्ठा user_namespace *ns, projid_t projid)
अणु
	/* Map the uid to a global kernel uid */
	वापस KPROJIDT_INIT(map_id_करोwn(&ns->projid_map, projid));
पूर्ण
EXPORT_SYMBOL(make_kprojid);

/**
 *	from_kprojid - Create a projid from a kprojid user-namespace pair.
 *	@targ: The user namespace we want a projid in.
 *	@kprojid: The kernel पूर्णांकernal project identअगरier to start with.
 *
 *	Map @kprojid पूर्णांकo the user-namespace specअगरied by @targ and
 *	वापस the resulting projid.
 *
 *	There is always a mapping पूर्णांकo the initial user_namespace.
 *
 *	If @kprojid has no mapping in @targ (projid_t)-1 is वापसed.
 */
projid_t from_kprojid(काष्ठा user_namespace *targ, kprojid_t kprojid)
अणु
	/* Map the uid from a global kernel uid */
	वापस map_id_up(&targ->projid_map, __kprojid_val(kprojid));
पूर्ण
EXPORT_SYMBOL(from_kprojid);

/**
 *	from_kprojid_munged - Create a projiid from a kprojid user-namespace pair.
 *	@targ: The user namespace we want a projid in.
 *	@kprojid: The kernel पूर्णांकernal projid to start with.
 *
 *	Map @kprojid पूर्णांकo the user-namespace specअगरied by @targ and
 *	वापस the resulting projid.
 *
 *	There is always a mapping पूर्णांकo the initial user_namespace.
 *
 *	Unlike from_kprojid from_kprojid_munged never fails and always
 *	वापसs a valid projid.  This makes from_kprojid_munged
 *	appropriate क्रम use in syscalls like stat and where
 *	failing the प्रणाली call and failing to provide a valid projid are
 *	not an options.
 *
 *	If @kprojid has no mapping in @targ OVERFLOW_PROJID is वापसed.
 */
projid_t from_kprojid_munged(काष्ठा user_namespace *targ, kprojid_t kprojid)
अणु
	projid_t projid;
	projid = from_kprojid(targ, kprojid);

	अगर (projid == (projid_t) -1)
		projid = OVERFLOW_PROJID;
	वापस projid;
पूर्ण
EXPORT_SYMBOL(from_kprojid_munged);


अटल पूर्णांक uid_m_show(काष्ठा seq_file *seq, व्योम *v)
अणु
	काष्ठा user_namespace *ns = seq->निजी;
	काष्ठा uid_gid_extent *extent = v;
	काष्ठा user_namespace *lower_ns;
	uid_t lower;

	lower_ns = seq_user_ns(seq);
	अगर ((lower_ns == ns) && lower_ns->parent)
		lower_ns = lower_ns->parent;

	lower = from_kuid(lower_ns, KUIDT_INIT(extent->lower_first));

	seq_म_लिखो(seq, "%10u %10u %10u\n",
		extent->first,
		lower,
		extent->count);

	वापस 0;
पूर्ण

अटल पूर्णांक gid_m_show(काष्ठा seq_file *seq, व्योम *v)
अणु
	काष्ठा user_namespace *ns = seq->निजी;
	काष्ठा uid_gid_extent *extent = v;
	काष्ठा user_namespace *lower_ns;
	gid_t lower;

	lower_ns = seq_user_ns(seq);
	अगर ((lower_ns == ns) && lower_ns->parent)
		lower_ns = lower_ns->parent;

	lower = from_kgid(lower_ns, KGIDT_INIT(extent->lower_first));

	seq_म_लिखो(seq, "%10u %10u %10u\n",
		extent->first,
		lower,
		extent->count);

	वापस 0;
पूर्ण

अटल पूर्णांक projid_m_show(काष्ठा seq_file *seq, व्योम *v)
अणु
	काष्ठा user_namespace *ns = seq->निजी;
	काष्ठा uid_gid_extent *extent = v;
	काष्ठा user_namespace *lower_ns;
	projid_t lower;

	lower_ns = seq_user_ns(seq);
	अगर ((lower_ns == ns) && lower_ns->parent)
		lower_ns = lower_ns->parent;

	lower = from_kprojid(lower_ns, KPROJIDT_INIT(extent->lower_first));

	seq_म_लिखो(seq, "%10u %10u %10u\n",
		extent->first,
		lower,
		extent->count);

	वापस 0;
पूर्ण

अटल व्योम *m_start(काष्ठा seq_file *seq, loff_t *ppos,
		     काष्ठा uid_gid_map *map)
अणु
	loff_t pos = *ppos;
	अचिन्हित extents = map->nr_extents;
	smp_rmb();

	अगर (pos >= extents)
		वापस शून्य;

	अगर (extents <= UID_GID_MAP_MAX_BASE_EXTENTS)
		वापस &map->extent[pos];

	वापस &map->क्रमward[pos];
पूर्ण

अटल व्योम *uid_m_start(काष्ठा seq_file *seq, loff_t *ppos)
अणु
	काष्ठा user_namespace *ns = seq->निजी;

	वापस m_start(seq, ppos, &ns->uid_map);
पूर्ण

अटल व्योम *gid_m_start(काष्ठा seq_file *seq, loff_t *ppos)
अणु
	काष्ठा user_namespace *ns = seq->निजी;

	वापस m_start(seq, ppos, &ns->gid_map);
पूर्ण

अटल व्योम *projid_m_start(काष्ठा seq_file *seq, loff_t *ppos)
अणु
	काष्ठा user_namespace *ns = seq->निजी;

	वापस m_start(seq, ppos, &ns->projid_map);
पूर्ण

अटल व्योम *m_next(काष्ठा seq_file *seq, व्योम *v, loff_t *pos)
अणु
	(*pos)++;
	वापस seq->op->start(seq, pos);
पूर्ण

अटल व्योम m_stop(काष्ठा seq_file *seq, व्योम *v)
अणु
	वापस;
पूर्ण

स्थिर काष्ठा seq_operations proc_uid_seq_operations = अणु
	.start = uid_m_start,
	.stop = m_stop,
	.next = m_next,
	.show = uid_m_show,
पूर्ण;

स्थिर काष्ठा seq_operations proc_gid_seq_operations = अणु
	.start = gid_m_start,
	.stop = m_stop,
	.next = m_next,
	.show = gid_m_show,
पूर्ण;

स्थिर काष्ठा seq_operations proc_projid_seq_operations = अणु
	.start = projid_m_start,
	.stop = m_stop,
	.next = m_next,
	.show = projid_m_show,
पूर्ण;

अटल bool mappings_overlap(काष्ठा uid_gid_map *new_map,
			     काष्ठा uid_gid_extent *extent)
अणु
	u32 upper_first, lower_first, upper_last, lower_last;
	अचिन्हित idx;

	upper_first = extent->first;
	lower_first = extent->lower_first;
	upper_last = upper_first + extent->count - 1;
	lower_last = lower_first + extent->count - 1;

	क्रम (idx = 0; idx < new_map->nr_extents; idx++) अणु
		u32 prev_upper_first, prev_lower_first;
		u32 prev_upper_last, prev_lower_last;
		काष्ठा uid_gid_extent *prev;

		अगर (new_map->nr_extents <= UID_GID_MAP_MAX_BASE_EXTENTS)
			prev = &new_map->extent[idx];
		अन्यथा
			prev = &new_map->क्रमward[idx];

		prev_upper_first = prev->first;
		prev_lower_first = prev->lower_first;
		prev_upper_last = prev_upper_first + prev->count - 1;
		prev_lower_last = prev_lower_first + prev->count - 1;

		/* Does the upper range पूर्णांकersect a previous extent? */
		अगर ((prev_upper_first <= upper_last) &&
		    (prev_upper_last >= upper_first))
			वापस true;

		/* Does the lower range पूर्णांकersect a previous extent? */
		अगर ((prev_lower_first <= lower_last) &&
		    (prev_lower_last >= lower_first))
			वापस true;
	पूर्ण
	वापस false;
पूर्ण

/**
 * insert_extent - Safely insert a new idmap extent पूर्णांकo काष्ठा uid_gid_map.
 * Takes care to allocate a 4K block of memory अगर the number of mappings exceeds
 * UID_GID_MAP_MAX_BASE_EXTENTS.
 */
अटल पूर्णांक insert_extent(काष्ठा uid_gid_map *map, काष्ठा uid_gid_extent *extent)
अणु
	काष्ठा uid_gid_extent *dest;

	अगर (map->nr_extents == UID_GID_MAP_MAX_BASE_EXTENTS) अणु
		काष्ठा uid_gid_extent *क्रमward;

		/* Allocate memory क्रम 340 mappings. */
		क्रमward = kदो_स्मृति_array(UID_GID_MAP_MAX_EXTENTS,
					माप(काष्ठा uid_gid_extent),
					GFP_KERNEL);
		अगर (!क्रमward)
			वापस -ENOMEM;

		/* Copy over memory. Only set up memory क्रम the क्रमward poपूर्णांकer.
		 * Defer the memory setup क्रम the reverse poपूर्णांकer.
		 */
		स_नकल(क्रमward, map->extent,
		       map->nr_extents * माप(map->extent[0]));

		map->क्रमward = क्रमward;
		map->reverse = शून्य;
	पूर्ण

	अगर (map->nr_extents < UID_GID_MAP_MAX_BASE_EXTENTS)
		dest = &map->extent[map->nr_extents];
	अन्यथा
		dest = &map->क्रमward[map->nr_extents];

	*dest = *extent;
	map->nr_extents++;
	वापस 0;
पूर्ण

/* cmp function to sort() क्रमward mappings */
अटल पूर्णांक cmp_extents_क्रमward(स्थिर व्योम *a, स्थिर व्योम *b)
अणु
	स्थिर काष्ठा uid_gid_extent *e1 = a;
	स्थिर काष्ठा uid_gid_extent *e2 = b;

	अगर (e1->first < e2->first)
		वापस -1;

	अगर (e1->first > e2->first)
		वापस 1;

	वापस 0;
पूर्ण

/* cmp function to sort() reverse mappings */
अटल पूर्णांक cmp_extents_reverse(स्थिर व्योम *a, स्थिर व्योम *b)
अणु
	स्थिर काष्ठा uid_gid_extent *e1 = a;
	स्थिर काष्ठा uid_gid_extent *e2 = b;

	अगर (e1->lower_first < e2->lower_first)
		वापस -1;

	अगर (e1->lower_first > e2->lower_first)
		वापस 1;

	वापस 0;
पूर्ण

/**
 * sort_idmaps - Sorts an array of idmap entries.
 * Can only be called अगर number of mappings exceeds UID_GID_MAP_MAX_BASE_EXTENTS.
 */
अटल पूर्णांक sort_idmaps(काष्ठा uid_gid_map *map)
अणु
	अगर (map->nr_extents <= UID_GID_MAP_MAX_BASE_EXTENTS)
		वापस 0;

	/* Sort क्रमward array. */
	sort(map->क्रमward, map->nr_extents, माप(काष्ठा uid_gid_extent),
	     cmp_extents_क्रमward, शून्य);

	/* Only copy the memory from क्रमward we actually need. */
	map->reverse = kmemdup(map->क्रमward,
			       map->nr_extents * माप(काष्ठा uid_gid_extent),
			       GFP_KERNEL);
	अगर (!map->reverse)
		वापस -ENOMEM;

	/* Sort reverse array. */
	sort(map->reverse, map->nr_extents, माप(काष्ठा uid_gid_extent),
	     cmp_extents_reverse, शून्य);

	वापस 0;
पूर्ण

/**
 * verअगरy_root_map() - check the uid 0 mapping
 * @file: idmapping file
 * @map_ns: user namespace of the target process
 * @new_map: requested idmap
 *
 * If a process requests mapping parent uid 0 पूर्णांकo the new ns, verअगरy that the
 * process writing the map had the CAP_SETFCAP capability as the target process
 * will be able to ग_लिखो fscaps that are valid in ancestor user namespaces.
 *
 * Return: true अगर the mapping is allowed, false अगर not.
 */
अटल bool verअगरy_root_map(स्थिर काष्ठा file *file,
			    काष्ठा user_namespace *map_ns,
			    काष्ठा uid_gid_map *new_map)
अणु
	पूर्णांक idx;
	स्थिर काष्ठा user_namespace *file_ns = file->f_cred->user_ns;
	काष्ठा uid_gid_extent *extent0 = शून्य;

	क्रम (idx = 0; idx < new_map->nr_extents; idx++) अणु
		अगर (new_map->nr_extents <= UID_GID_MAP_MAX_BASE_EXTENTS)
			extent0 = &new_map->extent[idx];
		अन्यथा
			extent0 = &new_map->क्रमward[idx];
		अगर (extent0->lower_first == 0)
			अवरोध;

		extent0 = शून्य;
	पूर्ण

	अगर (!extent0)
		वापस true;

	अगर (map_ns == file_ns) अणु
		/* The process unshared its ns and is writing to its own
		 * /proc/self/uid_map.  User alपढ़ोy has full capabilites in
		 * the new namespace.  Verअगरy that the parent had CAP_SETFCAP
		 * when it unshared.
		 * */
		अगर (!file_ns->parent_could_setfcap)
			वापस false;
	पूर्ण अन्यथा अणु
		/* Process p1 is writing to uid_map of p2, who is in a child
		 * user namespace to p1's.  Verअगरy that the खोलोer of the map
		 * file has CAP_SETFCAP against the parent of the new map
		 * namespace */
		अगर (!file_ns_capable(file, map_ns->parent, CAP_SETFCAP))
			वापस false;
	पूर्ण

	वापस true;
पूर्ण

अटल sमाप_प्रकार map_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *buf,
			 माप_प्रकार count, loff_t *ppos,
			 पूर्णांक cap_setid,
			 काष्ठा uid_gid_map *map,
			 काष्ठा uid_gid_map *parent_map)
अणु
	काष्ठा seq_file *seq = file->निजी_data;
	काष्ठा user_namespace *map_ns = seq->निजी;
	काष्ठा uid_gid_map new_map;
	अचिन्हित idx;
	काष्ठा uid_gid_extent extent;
	अक्षर *kbuf = शून्य, *pos, *next_line;
	sमाप_प्रकार ret;

	/* Only allow < page size ग_लिखोs at the beginning of the file */
	अगर ((*ppos != 0) || (count >= PAGE_SIZE))
		वापस -EINVAL;

	/* Slurp in the user data */
	kbuf = memdup_user_nul(buf, count);
	अगर (IS_ERR(kbuf))
		वापस PTR_ERR(kbuf);

	/*
	 * The userns_state_mutex serializes all ग_लिखोs to any given map.
	 *
	 * Any map is only ever written once.
	 *
	 * An id map fits within 1 cache line on most architectures.
	 *
	 * On पढ़ो nothing needs to be करोne unless you are on an
	 * architecture with a crazy cache coherency model like alpha.
	 *
	 * There is a one समय data dependency between पढ़ोing the
	 * count of the extents and the values of the extents.  The
	 * desired behavior is to see the values of the extents that
	 * were written beक्रमe the count of the extents.
	 *
	 * To achieve this smp_wmb() is used on guarantee the ग_लिखो
	 * order and smp_rmb() is guaranteed that we करोn't have crazy
	 * architectures वापसing stale data.
	 */
	mutex_lock(&userns_state_mutex);

	स_रखो(&new_map, 0, माप(काष्ठा uid_gid_map));

	ret = -EPERM;
	/* Only allow one successful ग_लिखो to the map */
	अगर (map->nr_extents != 0)
		जाओ out;

	/*
	 * Adjusting namespace settings requires capabilities on the target.
	 */
	अगर (cap_valid(cap_setid) && !file_ns_capable(file, map_ns, CAP_SYS_ADMIN))
		जाओ out;

	/* Parse the user data */
	ret = -EINVAL;
	pos = kbuf;
	क्रम (; pos; pos = next_line) अणु

		/* Find the end of line and ensure I करोn't look past it */
		next_line = म_अक्षर(pos, '\n');
		अगर (next_line) अणु
			*next_line = '\0';
			next_line++;
			अगर (*next_line == '\0')
				next_line = शून्य;
		पूर्ण

		pos = skip_spaces(pos);
		extent.first = simple_म_से_अदीर्घ(pos, &pos, 10);
		अगर (!है_खाली(*pos))
			जाओ out;

		pos = skip_spaces(pos);
		extent.lower_first = simple_म_से_अदीर्घ(pos, &pos, 10);
		अगर (!है_खाली(*pos))
			जाओ out;

		pos = skip_spaces(pos);
		extent.count = simple_म_से_अदीर्घ(pos, &pos, 10);
		अगर (*pos && !है_खाली(*pos))
			जाओ out;

		/* Verअगरy there is not trailing junk on the line */
		pos = skip_spaces(pos);
		अगर (*pos != '\0')
			जाओ out;

		/* Verअगरy we have been given valid starting values */
		अगर ((extent.first == (u32) -1) ||
		    (extent.lower_first == (u32) -1))
			जाओ out;

		/* Verअगरy count is not zero and करोes not cause the
		 * extent to wrap
		 */
		अगर ((extent.first + extent.count) <= extent.first)
			जाओ out;
		अगर ((extent.lower_first + extent.count) <=
		     extent.lower_first)
			जाओ out;

		/* Do the ranges in extent overlap any previous extents? */
		अगर (mappings_overlap(&new_map, &extent))
			जाओ out;

		अगर ((new_map.nr_extents + 1) == UID_GID_MAP_MAX_EXTENTS &&
		    (next_line != शून्य))
			जाओ out;

		ret = insert_extent(&new_map, &extent);
		अगर (ret < 0)
			जाओ out;
		ret = -EINVAL;
	पूर्ण
	/* Be very certain the new map actually exists */
	अगर (new_map.nr_extents == 0)
		जाओ out;

	ret = -EPERM;
	/* Validate the user is allowed to use user id's mapped to. */
	अगर (!new_idmap_permitted(file, map_ns, cap_setid, &new_map))
		जाओ out;

	ret = -EPERM;
	/* Map the lower ids from the parent user namespace to the
	 * kernel global id space.
	 */
	क्रम (idx = 0; idx < new_map.nr_extents; idx++) अणु
		काष्ठा uid_gid_extent *e;
		u32 lower_first;

		अगर (new_map.nr_extents <= UID_GID_MAP_MAX_BASE_EXTENTS)
			e = &new_map.extent[idx];
		अन्यथा
			e = &new_map.क्रमward[idx];

		lower_first = map_id_range_करोwn(parent_map,
						e->lower_first,
						e->count);

		/* Fail अगर we can not map the specअगरied extent to
		 * the kernel global id space.
		 */
		अगर (lower_first == (u32) -1)
			जाओ out;

		e->lower_first = lower_first;
	पूर्ण

	/*
	 * If we want to use binary search क्रम lookup, this clones the extent
	 * array and sorts both copies.
	 */
	ret = sort_idmaps(&new_map);
	अगर (ret < 0)
		जाओ out;

	/* Install the map */
	अगर (new_map.nr_extents <= UID_GID_MAP_MAX_BASE_EXTENTS) अणु
		स_नकल(map->extent, new_map.extent,
		       new_map.nr_extents * माप(new_map.extent[0]));
	पूर्ण अन्यथा अणु
		map->क्रमward = new_map.क्रमward;
		map->reverse = new_map.reverse;
	पूर्ण
	smp_wmb();
	map->nr_extents = new_map.nr_extents;

	*ppos = count;
	ret = count;
out:
	अगर (ret < 0 && new_map.nr_extents > UID_GID_MAP_MAX_BASE_EXTENTS) अणु
		kमुक्त(new_map.क्रमward);
		kमुक्त(new_map.reverse);
		map->क्रमward = शून्य;
		map->reverse = शून्य;
		map->nr_extents = 0;
	पूर्ण

	mutex_unlock(&userns_state_mutex);
	kमुक्त(kbuf);
	वापस ret;
पूर्ण

sमाप_प्रकार proc_uid_map_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *buf,
			   माप_प्रकार size, loff_t *ppos)
अणु
	काष्ठा seq_file *seq = file->निजी_data;
	काष्ठा user_namespace *ns = seq->निजी;
	काष्ठा user_namespace *seq_ns = seq_user_ns(seq);

	अगर (!ns->parent)
		वापस -EPERM;

	अगर ((seq_ns != ns) && (seq_ns != ns->parent))
		वापस -EPERM;

	वापस map_ग_लिखो(file, buf, size, ppos, CAP_SETUID,
			 &ns->uid_map, &ns->parent->uid_map);
पूर्ण

sमाप_प्रकार proc_gid_map_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *buf,
			   माप_प्रकार size, loff_t *ppos)
अणु
	काष्ठा seq_file *seq = file->निजी_data;
	काष्ठा user_namespace *ns = seq->निजी;
	काष्ठा user_namespace *seq_ns = seq_user_ns(seq);

	अगर (!ns->parent)
		वापस -EPERM;

	अगर ((seq_ns != ns) && (seq_ns != ns->parent))
		वापस -EPERM;

	वापस map_ग_लिखो(file, buf, size, ppos, CAP_SETGID,
			 &ns->gid_map, &ns->parent->gid_map);
पूर्ण

sमाप_प्रकार proc_projid_map_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *buf,
			      माप_प्रकार size, loff_t *ppos)
अणु
	काष्ठा seq_file *seq = file->निजी_data;
	काष्ठा user_namespace *ns = seq->निजी;
	काष्ठा user_namespace *seq_ns = seq_user_ns(seq);

	अगर (!ns->parent)
		वापस -EPERM;

	अगर ((seq_ns != ns) && (seq_ns != ns->parent))
		वापस -EPERM;

	/* Anyone can set any valid project id no capability needed */
	वापस map_ग_लिखो(file, buf, size, ppos, -1,
			 &ns->projid_map, &ns->parent->projid_map);
पूर्ण

अटल bool new_idmap_permitted(स्थिर काष्ठा file *file,
				काष्ठा user_namespace *ns, पूर्णांक cap_setid,
				काष्ठा uid_gid_map *new_map)
अणु
	स्थिर काष्ठा cred *cred = file->f_cred;

	अगर (cap_setid == CAP_SETUID && !verअगरy_root_map(file, ns, new_map))
		वापस false;

	/* Don't allow mappings that would allow anything that wouldn't
	 * be allowed without the establishment of unprivileged mappings.
	 */
	अगर ((new_map->nr_extents == 1) && (new_map->extent[0].count == 1) &&
	    uid_eq(ns->owner, cred->euid)) अणु
		u32 id = new_map->extent[0].lower_first;
		अगर (cap_setid == CAP_SETUID) अणु
			kuid_t uid = make_kuid(ns->parent, id);
			अगर (uid_eq(uid, cred->euid))
				वापस true;
		पूर्ण अन्यथा अगर (cap_setid == CAP_SETGID) अणु
			kgid_t gid = make_kgid(ns->parent, id);
			अगर (!(ns->flags & USERNS_SETGROUPS_ALLOWED) &&
			    gid_eq(gid, cred->egid))
				वापस true;
		पूर्ण
	पूर्ण

	/* Allow anyone to set a mapping that करोesn't require privilege */
	अगर (!cap_valid(cap_setid))
		वापस true;

	/* Allow the specअगरied ids अगर we have the appropriate capability
	 * (CAP_SETUID or CAP_SETGID) over the parent user namespace.
	 * And the खोलोer of the id file also has the appropriate capability.
	 */
	अगर (ns_capable(ns->parent, cap_setid) &&
	    file_ns_capable(file, ns->parent, cap_setid))
		वापस true;

	वापस false;
पूर्ण

पूर्णांक proc_setgroups_show(काष्ठा seq_file *seq, व्योम *v)
अणु
	काष्ठा user_namespace *ns = seq->निजी;
	अचिन्हित दीर्घ userns_flags = READ_ONCE(ns->flags);

	seq_म_लिखो(seq, "%s\n",
		   (userns_flags & USERNS_SETGROUPS_ALLOWED) ?
		   "allow" : "deny");
	वापस 0;
पूर्ण

sमाप_प्रकार proc_setgroups_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *buf,
			     माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा seq_file *seq = file->निजी_data;
	काष्ठा user_namespace *ns = seq->निजी;
	अक्षर kbuf[8], *pos;
	bool setgroups_allowed;
	sमाप_प्रकार ret;

	/* Only allow a very narrow range of strings to be written */
	ret = -EINVAL;
	अगर ((*ppos != 0) || (count >= माप(kbuf)))
		जाओ out;

	/* What was written? */
	ret = -EFAULT;
	अगर (copy_from_user(kbuf, buf, count))
		जाओ out;
	kbuf[count] = '\0';
	pos = kbuf;

	/* What is being requested? */
	ret = -EINVAL;
	अगर (म_भेदन(pos, "allow", 5) == 0) अणु
		pos += 5;
		setgroups_allowed = true;
	पूर्ण
	अन्यथा अगर (म_भेदन(pos, "deny", 4) == 0) अणु
		pos += 4;
		setgroups_allowed = false;
	पूर्ण
	अन्यथा
		जाओ out;

	/* Verअगरy there is not trailing junk on the line */
	pos = skip_spaces(pos);
	अगर (*pos != '\0')
		जाओ out;

	ret = -EPERM;
	mutex_lock(&userns_state_mutex);
	अगर (setgroups_allowed) अणु
		/* Enabling setgroups after setgroups has been disabled
		 * is not allowed.
		 */
		अगर (!(ns->flags & USERNS_SETGROUPS_ALLOWED))
			जाओ out_unlock;
	पूर्ण अन्यथा अणु
		/* Permanently disabling setgroups after setgroups has
		 * been enabled by writing the gid_map is not allowed.
		 */
		अगर (ns->gid_map.nr_extents != 0)
			जाओ out_unlock;
		ns->flags &= ~USERNS_SETGROUPS_ALLOWED;
	पूर्ण
	mutex_unlock(&userns_state_mutex);

	/* Report a successful ग_लिखो */
	*ppos = count;
	ret = count;
out:
	वापस ret;
out_unlock:
	mutex_unlock(&userns_state_mutex);
	जाओ out;
पूर्ण

bool userns_may_setgroups(स्थिर काष्ठा user_namespace *ns)
अणु
	bool allowed;

	mutex_lock(&userns_state_mutex);
	/* It is not safe to use setgroups until a gid mapping in
	 * the user namespace has been established.
	 */
	allowed = ns->gid_map.nr_extents != 0;
	/* Is setgroups allowed? */
	allowed = allowed && (ns->flags & USERNS_SETGROUPS_ALLOWED);
	mutex_unlock(&userns_state_mutex);

	वापस allowed;
पूर्ण

/*
 * Returns true अगर @child is the same namespace or a descendant of
 * @ancestor.
 */
bool in_userns(स्थिर काष्ठा user_namespace *ancestor,
	       स्थिर काष्ठा user_namespace *child)
अणु
	स्थिर काष्ठा user_namespace *ns;
	क्रम (ns = child; ns->level > ancestor->level; ns = ns->parent)
		;
	वापस (ns == ancestor);
पूर्ण

bool current_in_userns(स्थिर काष्ठा user_namespace *target_ns)
अणु
	वापस in_userns(target_ns, current_user_ns());
पूर्ण
EXPORT_SYMBOL(current_in_userns);

अटल अंतरभूत काष्ठा user_namespace *to_user_ns(काष्ठा ns_common *ns)
अणु
	वापस container_of(ns, काष्ठा user_namespace, ns);
पूर्ण

अटल काष्ठा ns_common *userns_get(काष्ठा task_काष्ठा *task)
अणु
	काष्ठा user_namespace *user_ns;

	rcu_पढ़ो_lock();
	user_ns = get_user_ns(__task_cred(task)->user_ns);
	rcu_पढ़ो_unlock();

	वापस user_ns ? &user_ns->ns : शून्य;
पूर्ण

अटल व्योम userns_put(काष्ठा ns_common *ns)
अणु
	put_user_ns(to_user_ns(ns));
पूर्ण

अटल पूर्णांक userns_install(काष्ठा nsset *nsset, काष्ठा ns_common *ns)
अणु
	काष्ठा user_namespace *user_ns = to_user_ns(ns);
	काष्ठा cred *cred;

	/* Don't allow gaining capabilities by reentering
	 * the same user namespace.
	 */
	अगर (user_ns == current_user_ns())
		वापस -EINVAL;

	/* Tasks that share a thपढ़ो group must share a user namespace */
	अगर (!thपढ़ो_group_empty(current))
		वापस -EINVAL;

	अगर (current->fs->users != 1)
		वापस -EINVAL;

	अगर (!ns_capable(user_ns, CAP_SYS_ADMIN))
		वापस -EPERM;

	cred = nsset_cred(nsset);
	अगर (!cred)
		वापस -EINVAL;

	put_user_ns(cred->user_ns);
	set_cred_user_ns(cred, get_user_ns(user_ns));

	वापस 0;
पूर्ण

काष्ठा ns_common *ns_get_owner(काष्ठा ns_common *ns)
अणु
	काष्ठा user_namespace *my_user_ns = current_user_ns();
	काष्ठा user_namespace *owner, *p;

	/* See अगर the owner is in the current user namespace */
	owner = p = ns->ops->owner(ns);
	क्रम (;;) अणु
		अगर (!p)
			वापस ERR_PTR(-EPERM);
		अगर (p == my_user_ns)
			अवरोध;
		p = p->parent;
	पूर्ण

	वापस &get_user_ns(owner)->ns;
पूर्ण

अटल काष्ठा user_namespace *userns_owner(काष्ठा ns_common *ns)
अणु
	वापस to_user_ns(ns)->parent;
पूर्ण

स्थिर काष्ठा proc_ns_operations userns_operations = अणु
	.name		= "user",
	.type		= CLONE_NEWUSER,
	.get		= userns_get,
	.put		= userns_put,
	.install	= userns_install,
	.owner		= userns_owner,
	.get_parent	= ns_get_owner,
पूर्ण;

अटल __init पूर्णांक user_namespaces_init(व्योम)
अणु
	user_ns_cachep = KMEM_CACHE(user_namespace, SLAB_PANIC);
	वापस 0;
पूर्ण
subsys_initcall(user_namespaces_init);
