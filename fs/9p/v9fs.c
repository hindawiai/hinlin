<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  linux/fs/9p/v9fs.c
 *
 *  This file contains functions assisting in mapping VFS to 9P2000
 *
 *  Copyright (C) 2004-2008 by Eric Van Hensbergen <ericvh@gmail.com>
 *  Copyright (C) 2002 by Ron Minnich <rminnich@lanl.gov>
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/fs.h>
#समावेश <linux/sched.h>
#समावेश <linux/cred.h>
#समावेश <linux/parser.h>
#समावेश <linux/idr.h>
#समावेश <linux/slab.h>
#समावेश <linux/seq_file.h>
#समावेश <net/9p/9p.h>
#समावेश <net/9p/client.h>
#समावेश <net/9p/transport.h>
#समावेश "v9fs.h"
#समावेश "v9fs_vfs.h"
#समावेश "cache.h"

अटल DEFINE_SPINLOCK(v9fs_sessionlist_lock);
अटल LIST_HEAD(v9fs_sessionlist);
काष्ठा kmem_cache *v9fs_inode_cache;

/*
 * Option Parsing (code inspired by NFS code)
 *  NOTE: each transport will parse its own options
 */

क्रमागत अणु
	/* Options that take पूर्णांकeger arguments */
	Opt_debug, Opt_dfltuid, Opt_dfltgid, Opt_afid,
	/* String options */
	Opt_uname, Opt_remotename, Opt_cache, Opt_cachetag,
	/* Options that take no arguments */
	Opt_nodevmap,
	/* Cache options */
	Opt_cache_loose, Opt_fscache, Opt_mmap,
	/* Access options */
	Opt_access, Opt_posixacl,
	/* Lock समयout option */
	Opt_lockसमयout,
	/* Error token */
	Opt_err
पूर्ण;

अटल स्थिर match_table_t tokens = अणु
	अणुOpt_debug, "debug=%x"पूर्ण,
	अणुOpt_dfltuid, "dfltuid=%u"पूर्ण,
	अणुOpt_dfltgid, "dfltgid=%u"पूर्ण,
	अणुOpt_afid, "afid=%u"पूर्ण,
	अणुOpt_uname, "uname=%s"पूर्ण,
	अणुOpt_remotename, "aname=%s"पूर्ण,
	अणुOpt_nodevmap, "nodevmap"पूर्ण,
	अणुOpt_cache, "cache=%s"पूर्ण,
	अणुOpt_cache_loose, "loose"पूर्ण,
	अणुOpt_fscache, "fscache"पूर्ण,
	अणुOpt_mmap, "mmap"पूर्ण,
	अणुOpt_cachetag, "cachetag=%s"पूर्ण,
	अणुOpt_access, "access=%s"पूर्ण,
	अणुOpt_posixacl, "posixacl"पूर्ण,
	अणुOpt_lockसमयout, "locktimeout=%u"पूर्ण,
	अणुOpt_err, शून्यपूर्ण
पूर्ण;

अटल स्थिर अक्षर *स्थिर v9fs_cache_modes[nr__p9_cache_modes] = अणु
	[CACHE_NONE]	= "none",
	[CACHE_MMAP]	= "mmap",
	[CACHE_LOOSE]	= "loose",
	[CACHE_FSCACHE]	= "fscache",
पूर्ण;

/* Interpret mount options क्रम cache mode */
अटल पूर्णांक get_cache_mode(अक्षर *s)
अणु
	पूर्णांक version = -EINVAL;

	अगर (!म_भेद(s, "loose")) अणु
		version = CACHE_LOOSE;
		p9_debug(P9_DEBUG_9P, "Cache mode: loose\n");
	पूर्ण अन्यथा अगर (!म_भेद(s, "fscache")) अणु
		version = CACHE_FSCACHE;
		p9_debug(P9_DEBUG_9P, "Cache mode: fscache\n");
	पूर्ण अन्यथा अगर (!म_भेद(s, "mmap")) अणु
		version = CACHE_MMAP;
		p9_debug(P9_DEBUG_9P, "Cache mode: mmap\n");
	पूर्ण अन्यथा अगर (!म_भेद(s, "none")) अणु
		version = CACHE_NONE;
		p9_debug(P9_DEBUG_9P, "Cache mode: none\n");
	पूर्ण अन्यथा
		pr_info("Unknown Cache mode %s\n", s);
	वापस version;
पूर्ण

/*
 * Display the mount options in /proc/mounts.
 */
पूर्णांक v9fs_show_options(काष्ठा seq_file *m, काष्ठा dentry *root)
अणु
	काष्ठा v9fs_session_info *v9ses = root->d_sb->s_fs_info;

	अगर (v9ses->debug)
		seq_म_लिखो(m, ",debug=%x", v9ses->debug);
	अगर (!uid_eq(v9ses->dfltuid, V9FS_DEFUID))
		seq_म_लिखो(m, ",dfltuid=%u",
			   from_kuid_munged(&init_user_ns, v9ses->dfltuid));
	अगर (!gid_eq(v9ses->dfltgid, V9FS_DEFGID))
		seq_म_लिखो(m, ",dfltgid=%u",
			   from_kgid_munged(&init_user_ns, v9ses->dfltgid));
	अगर (v9ses->afid != ~0)
		seq_म_लिखो(m, ",afid=%u", v9ses->afid);
	अगर (म_भेद(v9ses->uname, V9FS_DEFUSER) != 0)
		seq_म_लिखो(m, ",uname=%s", v9ses->uname);
	अगर (म_भेद(v9ses->aname, V9FS_DEFANAME) != 0)
		seq_म_लिखो(m, ",aname=%s", v9ses->aname);
	अगर (v9ses->nodev)
		seq_माला_दो(m, ",nodevmap");
	अगर (v9ses->cache)
		seq_म_लिखो(m, ",%s", v9fs_cache_modes[v9ses->cache]);
#अगर_घोषित CONFIG_9P_FSCACHE
	अगर (v9ses->cachetag && v9ses->cache == CACHE_FSCACHE)
		seq_म_लिखो(m, ",cachetag=%s", v9ses->cachetag);
#पूर्ण_अगर

	चयन (v9ses->flags & V9FS_ACCESS_MASK) अणु
	हाल V9FS_ACCESS_USER:
		seq_माला_दो(m, ",access=user");
		अवरोध;
	हाल V9FS_ACCESS_ANY:
		seq_माला_दो(m, ",access=any");
		अवरोध;
	हाल V9FS_ACCESS_CLIENT:
		seq_माला_दो(m, ",access=client");
		अवरोध;
	हाल V9FS_ACCESS_SINGLE:
		seq_म_लिखो(m, ",access=%u",
			   from_kuid_munged(&init_user_ns, v9ses->uid));
		अवरोध;
	पूर्ण

	अगर (v9ses->flags & V9FS_POSIX_ACL)
		seq_माला_दो(m, ",posixacl");

	वापस p9_show_client_options(m, v9ses->clnt);
पूर्ण

/**
 * v9fs_parse_options - parse mount options पूर्णांकo session काष्ठाure
 * @v9ses: existing v9fs session inक्रमmation
 *
 * Return 0 upon success, -ERRNO upon failure.
 */

अटल पूर्णांक v9fs_parse_options(काष्ठा v9fs_session_info *v9ses, अक्षर *opts)
अणु
	अक्षर *options, *पंचांगp_options;
	substring_t args[MAX_OPT_ARGS];
	अक्षर *p;
	पूर्णांक option = 0;
	अक्षर *s, *e;
	पूर्णांक ret = 0;

	/* setup शेषs */
	v9ses->afid = ~0;
	v9ses->debug = 0;
	v9ses->cache = CACHE_NONE;
#अगर_घोषित CONFIG_9P_FSCACHE
	v9ses->cachetag = शून्य;
#पूर्ण_अगर
	v9ses->session_lock_समयout = P9_LOCK_TIMEOUT;

	अगर (!opts)
		वापस 0;

	पंचांगp_options = kstrdup(opts, GFP_KERNEL);
	अगर (!पंचांगp_options) अणु
		ret = -ENOMEM;
		जाओ fail_option_alloc;
	पूर्ण
	options = पंचांगp_options;

	जबतक ((p = strsep(&options, ",")) != शून्य) अणु
		पूर्णांक token, r;
		अगर (!*p)
			जारी;
		token = match_token(p, tokens, args);
		चयन (token) अणु
		हाल Opt_debug:
			r = match_पूर्णांक(&args[0], &option);
			अगर (r < 0) अणु
				p9_debug(P9_DEBUG_ERROR,
					 "integer field, but no integer?\n");
				ret = r;
			पूर्ण अन्यथा अणु
				v9ses->debug = option;
#अगर_घोषित CONFIG_NET_9P_DEBUG
				p9_debug_level = option;
#पूर्ण_अगर
			पूर्ण
			अवरोध;

		हाल Opt_dfltuid:
			r = match_पूर्णांक(&args[0], &option);
			अगर (r < 0) अणु
				p9_debug(P9_DEBUG_ERROR,
					 "integer field, but no integer?\n");
				ret = r;
				जारी;
			पूर्ण
			v9ses->dfltuid = make_kuid(current_user_ns(), option);
			अगर (!uid_valid(v9ses->dfltuid)) अणु
				p9_debug(P9_DEBUG_ERROR,
					 "uid field, but not a uid?\n");
				ret = -EINVAL;
			पूर्ण
			अवरोध;
		हाल Opt_dfltgid:
			r = match_पूर्णांक(&args[0], &option);
			अगर (r < 0) अणु
				p9_debug(P9_DEBUG_ERROR,
					 "integer field, but no integer?\n");
				ret = r;
				जारी;
			पूर्ण
			v9ses->dfltgid = make_kgid(current_user_ns(), option);
			अगर (!gid_valid(v9ses->dfltgid)) अणु
				p9_debug(P9_DEBUG_ERROR,
					 "gid field, but not a gid?\n");
				ret = -EINVAL;
			पूर्ण
			अवरोध;
		हाल Opt_afid:
			r = match_पूर्णांक(&args[0], &option);
			अगर (r < 0) अणु
				p9_debug(P9_DEBUG_ERROR,
					 "integer field, but no integer?\n");
				ret = r;
			पूर्ण अन्यथा अणु
				v9ses->afid = option;
			पूर्ण
			अवरोध;
		हाल Opt_uname:
			kमुक्त(v9ses->uname);
			v9ses->uname = match_strdup(&args[0]);
			अगर (!v9ses->uname) अणु
				ret = -ENOMEM;
				जाओ मुक्त_and_वापस;
			पूर्ण
			अवरोध;
		हाल Opt_remotename:
			kमुक्त(v9ses->aname);
			v9ses->aname = match_strdup(&args[0]);
			अगर (!v9ses->aname) अणु
				ret = -ENOMEM;
				जाओ मुक्त_and_वापस;
			पूर्ण
			अवरोध;
		हाल Opt_nodevmap:
			v9ses->nodev = 1;
			अवरोध;
		हाल Opt_cache_loose:
			v9ses->cache = CACHE_LOOSE;
			अवरोध;
		हाल Opt_fscache:
			v9ses->cache = CACHE_FSCACHE;
			अवरोध;
		हाल Opt_mmap:
			v9ses->cache = CACHE_MMAP;
			अवरोध;
		हाल Opt_cachetag:
#अगर_घोषित CONFIG_9P_FSCACHE
			kमुक्त(v9ses->cachetag);
			v9ses->cachetag = match_strdup(&args[0]);
			अगर (!v9ses->cachetag) अणु
				ret = -ENOMEM;
				जाओ मुक्त_and_वापस;
			पूर्ण
#पूर्ण_अगर
			अवरोध;
		हाल Opt_cache:
			s = match_strdup(&args[0]);
			अगर (!s) अणु
				ret = -ENOMEM;
				p9_debug(P9_DEBUG_ERROR,
					 "problem allocating copy of cache arg\n");
				जाओ मुक्त_and_वापस;
			पूर्ण
			r = get_cache_mode(s);
			अगर (r < 0)
				ret = r;
			अन्यथा
				v9ses->cache = r;

			kमुक्त(s);
			अवरोध;

		हाल Opt_access:
			s = match_strdup(&args[0]);
			अगर (!s) अणु
				ret = -ENOMEM;
				p9_debug(P9_DEBUG_ERROR,
					 "problem allocating copy of access arg\n");
				जाओ मुक्त_and_वापस;
			पूर्ण

			v9ses->flags &= ~V9FS_ACCESS_MASK;
			अगर (म_भेद(s, "user") == 0)
				v9ses->flags |= V9FS_ACCESS_USER;
			अन्यथा अगर (म_भेद(s, "any") == 0)
				v9ses->flags |= V9FS_ACCESS_ANY;
			अन्यथा अगर (म_भेद(s, "client") == 0) अणु
				v9ses->flags |= V9FS_ACCESS_CLIENT;
			पूर्ण अन्यथा अणु
				uid_t uid;
				v9ses->flags |= V9FS_ACCESS_SINGLE;
				uid = simple_म_से_अदीर्घ(s, &e, 10);
				अगर (*e != '\0') अणु
					ret = -EINVAL;
					pr_info("Unknown access argument %s\n",
						s);
					kमुक्त(s);
					जारी;
				पूर्ण
				v9ses->uid = make_kuid(current_user_ns(), uid);
				अगर (!uid_valid(v9ses->uid)) अणु
					ret = -EINVAL;
					pr_info("Unknown uid %s\n", s);
				पूर्ण
			पूर्ण

			kमुक्त(s);
			अवरोध;

		हाल Opt_posixacl:
#अगर_घोषित CONFIG_9P_FS_POSIX_ACL
			v9ses->flags |= V9FS_POSIX_ACL;
#अन्यथा
			p9_debug(P9_DEBUG_ERROR,
				 "Not defined CONFIG_9P_FS_POSIX_ACL. Ignoring posixacl option\n");
#पूर्ण_अगर
			अवरोध;

		हाल Opt_lockसमयout:
			r = match_पूर्णांक(&args[0], &option);
			अगर (r < 0) अणु
				p9_debug(P9_DEBUG_ERROR,
					 "integer field, but no integer?\n");
				ret = r;
				जारी;
			पूर्ण
			अगर (option < 1) अणु
				p9_debug(P9_DEBUG_ERROR,
					 "locktimeout must be a greater than zero integer.\n");
				ret = -EINVAL;
				जारी;
			पूर्ण
			v9ses->session_lock_समयout = (दीर्घ)option * HZ;
			अवरोध;

		शेष:
			जारी;
		पूर्ण
	पूर्ण

मुक्त_and_वापस:
	kमुक्त(पंचांगp_options);
fail_option_alloc:
	वापस ret;
पूर्ण

/**
 * v9fs_session_init - initialize session
 * @v9ses: session inक्रमmation काष्ठाure
 * @dev_name: device being mounted
 * @data: options
 *
 */

काष्ठा p9_fid *v9fs_session_init(काष्ठा v9fs_session_info *v9ses,
		  स्थिर अक्षर *dev_name, अक्षर *data)
अणु
	काष्ठा p9_fid *fid;
	पूर्णांक rc = -ENOMEM;

	v9ses->uname = kstrdup(V9FS_DEFUSER, GFP_KERNEL);
	अगर (!v9ses->uname)
		जाओ err_names;

	v9ses->aname = kstrdup(V9FS_DEFANAME, GFP_KERNEL);
	अगर (!v9ses->aname)
		जाओ err_names;
	init_rwsem(&v9ses->नाम_sem);

	v9ses->uid = INVALID_UID;
	v9ses->dfltuid = V9FS_DEFUID;
	v9ses->dfltgid = V9FS_DEFGID;

	v9ses->clnt = p9_client_create(dev_name, data);
	अगर (IS_ERR(v9ses->clnt)) अणु
		rc = PTR_ERR(v9ses->clnt);
		p9_debug(P9_DEBUG_ERROR, "problem initializing 9p client\n");
		जाओ err_names;
	पूर्ण

	v9ses->flags = V9FS_ACCESS_USER;

	अगर (p9_is_proto_करोtl(v9ses->clnt)) अणु
		v9ses->flags = V9FS_ACCESS_CLIENT;
		v9ses->flags |= V9FS_PROTO_2000L;
	पूर्ण अन्यथा अगर (p9_is_proto_करोtu(v9ses->clnt)) अणु
		v9ses->flags |= V9FS_PROTO_2000U;
	पूर्ण

	rc = v9fs_parse_options(v9ses, data);
	अगर (rc < 0)
		जाओ err_clnt;

	v9ses->maxdata = v9ses->clnt->msize - P9_IOHDRSZ;

	अगर (!v9fs_proto_करोtl(v9ses) &&
	    ((v9ses->flags & V9FS_ACCESS_MASK) == V9FS_ACCESS_CLIENT)) अणु
		/*
		 * We support ACCESS_CLIENT only क्रम करोtl.
		 * Fall back to ACCESS_USER
		 */
		v9ses->flags &= ~V9FS_ACCESS_MASK;
		v9ses->flags |= V9FS_ACCESS_USER;
	पूर्ण
	/*FIXME !! */
	/* क्रम legacy mode, fall back to V9FS_ACCESS_ANY */
	अगर (!(v9fs_proto_करोtu(v9ses) || v9fs_proto_करोtl(v9ses)) &&
		((v9ses->flags&V9FS_ACCESS_MASK) == V9FS_ACCESS_USER)) अणु

		v9ses->flags &= ~V9FS_ACCESS_MASK;
		v9ses->flags |= V9FS_ACCESS_ANY;
		v9ses->uid = INVALID_UID;
	पूर्ण
	अगर (!v9fs_proto_करोtl(v9ses) ||
		!((v9ses->flags & V9FS_ACCESS_MASK) == V9FS_ACCESS_CLIENT)) अणु
		/*
		 * We support ACL checks on clinet only अगर the protocol is
		 * 9P2000.L and access is V9FS_ACCESS_CLIENT.
		 */
		v9ses->flags &= ~V9FS_ACL_MASK;
	पूर्ण

	fid = p9_client_attach(v9ses->clnt, शून्य, v9ses->uname, INVALID_UID,
							v9ses->aname);
	अगर (IS_ERR(fid)) अणु
		rc = PTR_ERR(fid);
		p9_debug(P9_DEBUG_ERROR, "cannot attach\n");
		जाओ err_clnt;
	पूर्ण

	अगर ((v9ses->flags & V9FS_ACCESS_MASK) == V9FS_ACCESS_SINGLE)
		fid->uid = v9ses->uid;
	अन्यथा
		fid->uid = INVALID_UID;

#अगर_घोषित CONFIG_9P_FSCACHE
	/* रेजिस्टर the session क्रम caching */
	v9fs_cache_session_get_cookie(v9ses);
#पूर्ण_अगर
	spin_lock(&v9fs_sessionlist_lock);
	list_add(&v9ses->slist, &v9fs_sessionlist);
	spin_unlock(&v9fs_sessionlist_lock);

	वापस fid;

err_clnt:
#अगर_घोषित CONFIG_9P_FSCACHE
	kमुक्त(v9ses->cachetag);
#पूर्ण_अगर
	p9_client_destroy(v9ses->clnt);
err_names:
	kमुक्त(v9ses->uname);
	kमुक्त(v9ses->aname);
	वापस ERR_PTR(rc);
पूर्ण

/**
 * v9fs_session_बंद - shutकरोwn a session
 * @v9ses: session inक्रमmation काष्ठाure
 *
 */

व्योम v9fs_session_बंद(काष्ठा v9fs_session_info *v9ses)
अणु
	अगर (v9ses->clnt) अणु
		p9_client_destroy(v9ses->clnt);
		v9ses->clnt = शून्य;
	पूर्ण

#अगर_घोषित CONFIG_9P_FSCACHE
	अगर (v9ses->fscache)
		v9fs_cache_session_put_cookie(v9ses);
	kमुक्त(v9ses->cachetag);
#पूर्ण_अगर
	kमुक्त(v9ses->uname);
	kमुक्त(v9ses->aname);

	spin_lock(&v9fs_sessionlist_lock);
	list_del(&v9ses->slist);
	spin_unlock(&v9fs_sessionlist_lock);
पूर्ण

/**
 * v9fs_session_cancel - terminate a session
 * @v9ses: session to terminate
 *
 * mark transport as disconnected and cancel all pending requests.
 */

व्योम v9fs_session_cancel(काष्ठा v9fs_session_info *v9ses) अणु
	p9_debug(P9_DEBUG_ERROR, "cancel session %p\n", v9ses);
	p9_client_disconnect(v9ses->clnt);
पूर्ण

/**
 * v9fs_session_begin_cancel - Begin terminate of a session
 * @v9ses: session to terminate
 *
 * After this call we करोn't allow any request other than clunk.
 */

व्योम v9fs_session_begin_cancel(काष्ठा v9fs_session_info *v9ses)
अणु
	p9_debug(P9_DEBUG_ERROR, "begin cancel session %p\n", v9ses);
	p9_client_begin_disconnect(v9ses->clnt);
पूर्ण

बाह्य पूर्णांक v9fs_error_init(व्योम);

अटल काष्ठा kobject *v9fs_kobj;

#अगर_घोषित CONFIG_9P_FSCACHE
/**
 * caches_show - list caches associated with a session
 *
 * Returns the size of buffer written.
 */

अटल sमाप_प्रकार caches_show(काष्ठा kobject *kobj,
			   काष्ठा kobj_attribute *attr,
			   अक्षर *buf)
अणु
	sमाप_प्रकार n = 0, count = 0, limit = PAGE_SIZE;
	काष्ठा v9fs_session_info *v9ses;

	spin_lock(&v9fs_sessionlist_lock);
	list_क्रम_each_entry(v9ses, &v9fs_sessionlist, slist) अणु
		अगर (v9ses->cachetag) अणु
			n = snम_लिखो(buf, limit, "%s\n", v9ses->cachetag);
			अगर (n < 0) अणु
				count = n;
				अवरोध;
			पूर्ण

			count += n;
			limit -= n;
		पूर्ण
	पूर्ण

	spin_unlock(&v9fs_sessionlist_lock);
	वापस count;
पूर्ण

अटल काष्ठा kobj_attribute v9fs_attr_cache = __ATTR_RO(caches);
#पूर्ण_अगर /* CONFIG_9P_FSCACHE */

अटल काष्ठा attribute *v9fs_attrs[] = अणु
#अगर_घोषित CONFIG_9P_FSCACHE
	&v9fs_attr_cache.attr,
#पूर्ण_अगर
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group v9fs_attr_group = अणु
	.attrs = v9fs_attrs,
पूर्ण;

/**
 * v9fs_sysfs_init - Initialize the v9fs sysfs पूर्णांकerface
 *
 */

अटल पूर्णांक __init v9fs_sysfs_init(व्योम)
अणु
	v9fs_kobj = kobject_create_and_add("9p", fs_kobj);
	अगर (!v9fs_kobj)
		वापस -ENOMEM;

	अगर (sysfs_create_group(v9fs_kobj, &v9fs_attr_group)) अणु
		kobject_put(v9fs_kobj);
		वापस -ENOMEM;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * v9fs_sysfs_cleanup - Unरेजिस्टर the v9fs sysfs पूर्णांकerface
 *
 */

अटल व्योम v9fs_sysfs_cleanup(व्योम)
अणु
	sysfs_हटाओ_group(v9fs_kobj, &v9fs_attr_group);
	kobject_put(v9fs_kobj);
पूर्ण

अटल व्योम v9fs_inode_init_once(व्योम *foo)
अणु
	काष्ठा v9fs_inode *v9inode = (काष्ठा v9fs_inode *)foo;
#अगर_घोषित CONFIG_9P_FSCACHE
	v9inode->fscache = शून्य;
#पूर्ण_अगर
	स_रखो(&v9inode->qid, 0, माप(v9inode->qid));
	inode_init_once(&v9inode->vfs_inode);
पूर्ण

/**
 * v9fs_init_inode_cache - initialize a cache क्रम 9P
 * Returns 0 on success.
 */
अटल पूर्णांक v9fs_init_inode_cache(व्योम)
अणु
	v9fs_inode_cache = kmem_cache_create("v9fs_inode_cache",
					  माप(काष्ठा v9fs_inode),
					  0, (SLAB_RECLAIM_ACCOUNT|
					      SLAB_MEM_SPREAD|SLAB_ACCOUNT),
					  v9fs_inode_init_once);
	अगर (!v9fs_inode_cache)
		वापस -ENOMEM;

	वापस 0;
पूर्ण

/**
 * v9fs_destroy_inode_cache - destroy the cache of 9P inode
 *
 */
अटल व्योम v9fs_destroy_inode_cache(व्योम)
अणु
	/*
	 * Make sure all delayed rcu मुक्त inodes are flushed beक्रमe we
	 * destroy cache.
	 */
	rcu_barrier();
	kmem_cache_destroy(v9fs_inode_cache);
पूर्ण

अटल पूर्णांक v9fs_cache_रेजिस्टर(व्योम)
अणु
	पूर्णांक ret;
	ret = v9fs_init_inode_cache();
	अगर (ret < 0)
		वापस ret;
#अगर_घोषित CONFIG_9P_FSCACHE
	ret = fscache_रेजिस्टर_netfs(&v9fs_cache_netfs);
	अगर (ret < 0)
		v9fs_destroy_inode_cache();
#पूर्ण_अगर
	वापस ret;
पूर्ण

अटल व्योम v9fs_cache_unरेजिस्टर(व्योम)
अणु
	v9fs_destroy_inode_cache();
#अगर_घोषित CONFIG_9P_FSCACHE
	fscache_unरेजिस्टर_netfs(&v9fs_cache_netfs);
#पूर्ण_अगर
पूर्ण

/**
 * init_v9fs - Initialize module
 *
 */

अटल पूर्णांक __init init_v9fs(व्योम)
अणु
	पूर्णांक err;
	pr_info("Installing v9fs 9p2000 file system support\n");
	/* TODO: Setup list of रेजिस्टरed trasnport modules */

	err = v9fs_cache_रेजिस्टर();
	अगर (err < 0) अणु
		pr_err("Failed to register v9fs for caching\n");
		वापस err;
	पूर्ण

	err = v9fs_sysfs_init();
	अगर (err < 0) अणु
		pr_err("Failed to register with sysfs\n");
		जाओ out_cache;
	पूर्ण
	err = रेजिस्टर_fileप्रणाली(&v9fs_fs_type);
	अगर (err < 0) अणु
		pr_err("Failed to register filesystem\n");
		जाओ out_sysfs_cleanup;
	पूर्ण

	वापस 0;

out_sysfs_cleanup:
	v9fs_sysfs_cleanup();

out_cache:
	v9fs_cache_unरेजिस्टर();

	वापस err;
पूर्ण

/**
 * निकास_v9fs - shutकरोwn module
 *
 */

अटल व्योम __निकास निकास_v9fs(व्योम)
अणु
	v9fs_sysfs_cleanup();
	v9fs_cache_unरेजिस्टर();
	unरेजिस्टर_fileप्रणाली(&v9fs_fs_type);
पूर्ण

module_init(init_v9fs)
module_निकास(निकास_v9fs)

MODULE_AUTHOR("Latchesar Ionkov <lucho@ionkov.net>");
MODULE_AUTHOR("Eric Van Hensbergen <ericvh@gmail.com>");
MODULE_AUTHOR("Ron Minnich <rminnich@lanl.gov>");
MODULE_LICENSE("GPL");
