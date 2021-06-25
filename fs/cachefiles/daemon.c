<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* Daemon पूर्णांकerface
 *
 * Copyright (C) 2007 Red Hat, Inc. All Rights Reserved.
 * Written by David Howells (dhowells@redhat.com)
 */

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/sched.h>
#समावेश <linux/completion.h>
#समावेश <linux/slab.h>
#समावेश <linux/fs.h>
#समावेश <linux/file.h>
#समावेश <linux/namei.h>
#समावेश <linux/poll.h>
#समावेश <linux/mount.h>
#समावेश <linux/statfs.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/माला.स>
#समावेश <linux/fs_काष्ठा.h>
#समावेश "internal.h"

अटल पूर्णांक cachefiles_daemon_खोलो(काष्ठा inode *, काष्ठा file *);
अटल पूर्णांक cachefiles_daemon_release(काष्ठा inode *, काष्ठा file *);
अटल sमाप_प्रकार cachefiles_daemon_पढ़ो(काष्ठा file *, अक्षर __user *, माप_प्रकार,
				      loff_t *);
अटल sमाप_प्रकार cachefiles_daemon_ग_लिखो(काष्ठा file *, स्थिर अक्षर __user *,
				       माप_प्रकार, loff_t *);
अटल __poll_t cachefiles_daemon_poll(काष्ठा file *,
					   काष्ठा poll_table_काष्ठा *);
अटल पूर्णांक cachefiles_daemon_frun(काष्ठा cachefiles_cache *, अक्षर *);
अटल पूर्णांक cachefiles_daemon_fcull(काष्ठा cachefiles_cache *, अक्षर *);
अटल पूर्णांक cachefiles_daemon_fstop(काष्ठा cachefiles_cache *, अक्षर *);
अटल पूर्णांक cachefiles_daemon_brun(काष्ठा cachefiles_cache *, अक्षर *);
अटल पूर्णांक cachefiles_daemon_bcull(काष्ठा cachefiles_cache *, अक्षर *);
अटल पूर्णांक cachefiles_daemon_bstop(काष्ठा cachefiles_cache *, अक्षर *);
अटल पूर्णांक cachefiles_daemon_cull(काष्ठा cachefiles_cache *, अक्षर *);
अटल पूर्णांक cachefiles_daemon_debug(काष्ठा cachefiles_cache *, अक्षर *);
अटल पूर्णांक cachefiles_daemon_dir(काष्ठा cachefiles_cache *, अक्षर *);
अटल पूर्णांक cachefiles_daemon_inuse(काष्ठा cachefiles_cache *, अक्षर *);
अटल पूर्णांक cachefiles_daemon_secctx(काष्ठा cachefiles_cache *, अक्षर *);
अटल पूर्णांक cachefiles_daemon_tag(काष्ठा cachefiles_cache *, अक्षर *);

अटल अचिन्हित दीर्घ cachefiles_खोलो;

स्थिर काष्ठा file_operations cachefiles_daemon_fops = अणु
	.owner		= THIS_MODULE,
	.खोलो		= cachefiles_daemon_खोलो,
	.release	= cachefiles_daemon_release,
	.पढ़ो		= cachefiles_daemon_पढ़ो,
	.ग_लिखो		= cachefiles_daemon_ग_लिखो,
	.poll		= cachefiles_daemon_poll,
	.llseek		= noop_llseek,
पूर्ण;

काष्ठा cachefiles_daemon_cmd अणु
	अक्षर name[8];
	पूर्णांक (*handler)(काष्ठा cachefiles_cache *cache, अक्षर *args);
पूर्ण;

अटल स्थिर काष्ठा cachefiles_daemon_cmd cachefiles_daemon_cmds[] = अणु
	अणु "bind",	cachefiles_daemon_bind		पूर्ण,
	अणु "brun",	cachefiles_daemon_brun		पूर्ण,
	अणु "bcull",	cachefiles_daemon_bcull		पूर्ण,
	अणु "bstop",	cachefiles_daemon_bstop		पूर्ण,
	अणु "cull",	cachefiles_daemon_cull		पूर्ण,
	अणु "debug",	cachefiles_daemon_debug		पूर्ण,
	अणु "dir",	cachefiles_daemon_dir		पूर्ण,
	अणु "frun",	cachefiles_daemon_frun		पूर्ण,
	अणु "fcull",	cachefiles_daemon_fcull		पूर्ण,
	अणु "fstop",	cachefiles_daemon_fstop		पूर्ण,
	अणु "inuse",	cachefiles_daemon_inuse		पूर्ण,
	अणु "secctx",	cachefiles_daemon_secctx	पूर्ण,
	अणु "tag",	cachefiles_daemon_tag		पूर्ण,
	अणु "",		शून्य				पूर्ण
पूर्ण;


/*
 * करो various checks
 */
अटल पूर्णांक cachefiles_daemon_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा cachefiles_cache *cache;

	_enter("");

	/* only the superuser may करो this */
	अगर (!capable(CAP_SYS_ADMIN))
		वापस -EPERM;

	/* the cachefiles device may only be खोलो once at a समय */
	अगर (xchg(&cachefiles_खोलो, 1) == 1)
		वापस -EBUSY;

	/* allocate a cache record */
	cache = kzalloc(माप(काष्ठा cachefiles_cache), GFP_KERNEL);
	अगर (!cache) अणु
		cachefiles_खोलो = 0;
		वापस -ENOMEM;
	पूर्ण

	mutex_init(&cache->daemon_mutex);
	cache->active_nodes = RB_ROOT;
	rwlock_init(&cache->active_lock);
	init_रुकोqueue_head(&cache->daemon_pollwq);

	/* set शेष caching limits
	 * - limit at 1% मुक्त space and/or मुक्त files
	 * - cull below 5% मुक्त space and/or मुक्त files
	 * - cease culling above 7% मुक्त space and/or मुक्त files
	 */
	cache->frun_percent = 7;
	cache->fcull_percent = 5;
	cache->fstop_percent = 1;
	cache->brun_percent = 7;
	cache->bcull_percent = 5;
	cache->bstop_percent = 1;

	file->निजी_data = cache;
	cache->cachefilesd = file;
	वापस 0;
पूर्ण

/*
 * release a cache
 */
अटल पूर्णांक cachefiles_daemon_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा cachefiles_cache *cache = file->निजी_data;

	_enter("");

	ASSERT(cache);

	set_bit(CACHEखाताS_DEAD, &cache->flags);

	cachefiles_daemon_unbind(cache);

	ASSERT(!cache->active_nodes.rb_node);

	/* clean up the control file पूर्णांकerface */
	cache->cachefilesd = शून्य;
	file->निजी_data = शून्य;
	cachefiles_खोलो = 0;

	kमुक्त(cache);

	_leave("");
	वापस 0;
पूर्ण

/*
 * पढ़ो the cache state
 */
अटल sमाप_प्रकार cachefiles_daemon_पढ़ो(काष्ठा file *file, अक्षर __user *_buffer,
				      माप_प्रकार buflen, loff_t *pos)
अणु
	काष्ठा cachefiles_cache *cache = file->निजी_data;
	अचिन्हित दीर्घ दीर्घ b_released;
	अचिन्हित f_released;
	अक्षर buffer[256];
	पूर्णांक n;

	//_enter(",,%zu,", buflen);

	अगर (!test_bit(CACHEखाताS_READY, &cache->flags))
		वापस 0;

	/* check how much space the cache has */
	cachefiles_has_space(cache, 0, 0);

	/* summarise */
	f_released = atomic_xchg(&cache->f_released, 0);
	b_released = atomic_दीर्घ_xchg(&cache->b_released, 0);
	clear_bit(CACHEखाताS_STATE_CHANGED, &cache->flags);

	n = snम_लिखो(buffer, माप(buffer),
		     "cull=%c"
		     " frun=%llx"
		     " fcull=%llx"
		     " fstop=%llx"
		     " brun=%llx"
		     " bcull=%llx"
		     " bstop=%llx"
		     " freleased=%x"
		     " breleased=%llx",
		     test_bit(CACHEखाताS_CULLING, &cache->flags) ? '1' : '0',
		     (अचिन्हित दीर्घ दीर्घ) cache->frun,
		     (अचिन्हित दीर्घ दीर्घ) cache->fcull,
		     (अचिन्हित दीर्घ दीर्घ) cache->fstop,
		     (अचिन्हित दीर्घ दीर्घ) cache->brun,
		     (अचिन्हित दीर्घ दीर्घ) cache->bcull,
		     (अचिन्हित दीर्घ दीर्घ) cache->bstop,
		     f_released,
		     b_released);

	अगर (n > buflen)
		वापस -EMSGSIZE;

	अगर (copy_to_user(_buffer, buffer, n) != 0)
		वापस -EFAULT;

	वापस n;
पूर्ण

/*
 * command the cache
 */
अटल sमाप_प्रकार cachefiles_daemon_ग_लिखो(काष्ठा file *file,
				       स्थिर अक्षर __user *_data,
				       माप_प्रकार datalen,
				       loff_t *pos)
अणु
	स्थिर काष्ठा cachefiles_daemon_cmd *cmd;
	काष्ठा cachefiles_cache *cache = file->निजी_data;
	sमाप_प्रकार ret;
	अक्षर *data, *args, *cp;

	//_enter(",,%zu,", datalen);

	ASSERT(cache);

	अगर (test_bit(CACHEखाताS_DEAD, &cache->flags))
		वापस -EIO;

	अगर (datalen < 0 || datalen > PAGE_SIZE - 1)
		वापस -EOPNOTSUPP;

	/* drag the command string पूर्णांकo the kernel so we can parse it */
	data = memdup_user_nul(_data, datalen);
	अगर (IS_ERR(data))
		वापस PTR_ERR(data);

	ret = -EINVAL;
	अगर (स_प्रथम(data, '\0', datalen))
		जाओ error;

	/* strip any newline */
	cp = स_प्रथम(data, '\n', datalen);
	अगर (cp) अणु
		अगर (cp == data)
			जाओ error;

		*cp = '\0';
	पूर्ण

	/* parse the command */
	ret = -EOPNOTSUPP;

	क्रम (args = data; *args; args++)
		अगर (है_खाली(*args))
			अवरोध;
	अगर (*args) अणु
		अगर (args == data)
			जाओ error;
		*args = '\0';
		args = skip_spaces(++args);
	पूर्ण

	/* run the appropriate command handler */
	क्रम (cmd = cachefiles_daemon_cmds; cmd->name[0]; cmd++)
		अगर (म_भेद(cmd->name, data) == 0)
			जाओ found_command;

error:
	kमुक्त(data);
	//_leave(" = %zd", ret);
	वापस ret;

found_command:
	mutex_lock(&cache->daemon_mutex);

	ret = -EIO;
	अगर (!test_bit(CACHEखाताS_DEAD, &cache->flags))
		ret = cmd->handler(cache, args);

	mutex_unlock(&cache->daemon_mutex);

	अगर (ret == 0)
		ret = datalen;
	जाओ error;
पूर्ण

/*
 * poll क्रम culling state
 * - use EPOLLOUT to indicate culling state
 */
अटल __poll_t cachefiles_daemon_poll(काष्ठा file *file,
					   काष्ठा poll_table_काष्ठा *poll)
अणु
	काष्ठा cachefiles_cache *cache = file->निजी_data;
	__poll_t mask;

	poll_रुको(file, &cache->daemon_pollwq, poll);
	mask = 0;

	अगर (test_bit(CACHEखाताS_STATE_CHANGED, &cache->flags))
		mask |= EPOLLIN;

	अगर (test_bit(CACHEखाताS_CULLING, &cache->flags))
		mask |= EPOLLOUT;

	वापस mask;
पूर्ण

/*
 * give a range error क्रम cache space स्थिरraपूर्णांकs
 * - can be tail-called
 */
अटल पूर्णांक cachefiles_daemon_range_error(काष्ठा cachefiles_cache *cache,
					 अक्षर *args)
अणु
	pr_err("Free space limits must be in range 0%%<=stop<cull<run<100%%\n");

	वापस -EINVAL;
पूर्ण

/*
 * set the percentage of files at which to stop culling
 * - command: "frun <N>%"
 */
अटल पूर्णांक cachefiles_daemon_frun(काष्ठा cachefiles_cache *cache, अक्षर *args)
अणु
	अचिन्हित दीर्घ frun;

	_enter(",%s", args);

	अगर (!*args)
		वापस -EINVAL;

	frun = simple_म_से_अदीर्घ(args, &args, 10);
	अगर (args[0] != '%' || args[1] != '\0')
		वापस -EINVAL;

	अगर (frun <= cache->fcull_percent || frun >= 100)
		वापस cachefiles_daemon_range_error(cache, args);

	cache->frun_percent = frun;
	वापस 0;
पूर्ण

/*
 * set the percentage of files at which to start culling
 * - command: "fcull <N>%"
 */
अटल पूर्णांक cachefiles_daemon_fcull(काष्ठा cachefiles_cache *cache, अक्षर *args)
अणु
	अचिन्हित दीर्घ fcull;

	_enter(",%s", args);

	अगर (!*args)
		वापस -EINVAL;

	fcull = simple_म_से_अदीर्घ(args, &args, 10);
	अगर (args[0] != '%' || args[1] != '\0')
		वापस -EINVAL;

	अगर (fcull <= cache->fstop_percent || fcull >= cache->frun_percent)
		वापस cachefiles_daemon_range_error(cache, args);

	cache->fcull_percent = fcull;
	वापस 0;
पूर्ण

/*
 * set the percentage of files at which to stop allocating
 * - command: "fstop <N>%"
 */
अटल पूर्णांक cachefiles_daemon_fstop(काष्ठा cachefiles_cache *cache, अक्षर *args)
अणु
	अचिन्हित दीर्घ fstop;

	_enter(",%s", args);

	अगर (!*args)
		वापस -EINVAL;

	fstop = simple_म_से_अदीर्घ(args, &args, 10);
	अगर (args[0] != '%' || args[1] != '\0')
		वापस -EINVAL;

	अगर (fstop < 0 || fstop >= cache->fcull_percent)
		वापस cachefiles_daemon_range_error(cache, args);

	cache->fstop_percent = fstop;
	वापस 0;
पूर्ण

/*
 * set the percentage of blocks at which to stop culling
 * - command: "brun <N>%"
 */
अटल पूर्णांक cachefiles_daemon_brun(काष्ठा cachefiles_cache *cache, अक्षर *args)
अणु
	अचिन्हित दीर्घ brun;

	_enter(",%s", args);

	अगर (!*args)
		वापस -EINVAL;

	brun = simple_म_से_अदीर्घ(args, &args, 10);
	अगर (args[0] != '%' || args[1] != '\0')
		वापस -EINVAL;

	अगर (brun <= cache->bcull_percent || brun >= 100)
		वापस cachefiles_daemon_range_error(cache, args);

	cache->brun_percent = brun;
	वापस 0;
पूर्ण

/*
 * set the percentage of blocks at which to start culling
 * - command: "bcull <N>%"
 */
अटल पूर्णांक cachefiles_daemon_bcull(काष्ठा cachefiles_cache *cache, अक्षर *args)
अणु
	अचिन्हित दीर्घ bcull;

	_enter(",%s", args);

	अगर (!*args)
		वापस -EINVAL;

	bcull = simple_म_से_अदीर्घ(args, &args, 10);
	अगर (args[0] != '%' || args[1] != '\0')
		वापस -EINVAL;

	अगर (bcull <= cache->bstop_percent || bcull >= cache->brun_percent)
		वापस cachefiles_daemon_range_error(cache, args);

	cache->bcull_percent = bcull;
	वापस 0;
पूर्ण

/*
 * set the percentage of blocks at which to stop allocating
 * - command: "bstop <N>%"
 */
अटल पूर्णांक cachefiles_daemon_bstop(काष्ठा cachefiles_cache *cache, अक्षर *args)
अणु
	अचिन्हित दीर्घ bstop;

	_enter(",%s", args);

	अगर (!*args)
		वापस -EINVAL;

	bstop = simple_म_से_अदीर्घ(args, &args, 10);
	अगर (args[0] != '%' || args[1] != '\0')
		वापस -EINVAL;

	अगर (bstop < 0 || bstop >= cache->bcull_percent)
		वापस cachefiles_daemon_range_error(cache, args);

	cache->bstop_percent = bstop;
	वापस 0;
पूर्ण

/*
 * set the cache directory
 * - command: "dir <name>"
 */
अटल पूर्णांक cachefiles_daemon_dir(काष्ठा cachefiles_cache *cache, अक्षर *args)
अणु
	अक्षर *dir;

	_enter(",%s", args);

	अगर (!*args) अणु
		pr_err("Empty directory specified\n");
		वापस -EINVAL;
	पूर्ण

	अगर (cache->rootस_नाम) अणु
		pr_err("Second cache directory specified\n");
		वापस -EEXIST;
	पूर्ण

	dir = kstrdup(args, GFP_KERNEL);
	अगर (!dir)
		वापस -ENOMEM;

	cache->rootस_नाम = dir;
	वापस 0;
पूर्ण

/*
 * set the cache security context
 * - command: "secctx <ctx>"
 */
अटल पूर्णांक cachefiles_daemon_secctx(काष्ठा cachefiles_cache *cache, अक्षर *args)
अणु
	अक्षर *secctx;

	_enter(",%s", args);

	अगर (!*args) अणु
		pr_err("Empty security context specified\n");
		वापस -EINVAL;
	पूर्ण

	अगर (cache->secctx) अणु
		pr_err("Second security context specified\n");
		वापस -EINVAL;
	पूर्ण

	secctx = kstrdup(args, GFP_KERNEL);
	अगर (!secctx)
		वापस -ENOMEM;

	cache->secctx = secctx;
	वापस 0;
पूर्ण

/*
 * set the cache tag
 * - command: "tag <name>"
 */
अटल पूर्णांक cachefiles_daemon_tag(काष्ठा cachefiles_cache *cache, अक्षर *args)
अणु
	अक्षर *tag;

	_enter(",%s", args);

	अगर (!*args) अणु
		pr_err("Empty tag specified\n");
		वापस -EINVAL;
	पूर्ण

	अगर (cache->tag)
		वापस -EEXIST;

	tag = kstrdup(args, GFP_KERNEL);
	अगर (!tag)
		वापस -ENOMEM;

	cache->tag = tag;
	वापस 0;
पूर्ण

/*
 * request a node in the cache be culled from the current working directory
 * - command: "cull <name>"
 */
अटल पूर्णांक cachefiles_daemon_cull(काष्ठा cachefiles_cache *cache, अक्षर *args)
अणु
	काष्ठा path path;
	स्थिर काष्ठा cred *saved_cred;
	पूर्णांक ret;

	_enter(",%s", args);

	अगर (म_अक्षर(args, '/'))
		जाओ inval;

	अगर (!test_bit(CACHEखाताS_READY, &cache->flags)) अणु
		pr_err("cull applied to unready cache\n");
		वापस -EIO;
	पूर्ण

	अगर (test_bit(CACHEखाताS_DEAD, &cache->flags)) अणु
		pr_err("cull applied to dead cache\n");
		वापस -EIO;
	पूर्ण

	/* extract the directory dentry from the cwd */
	get_fs_pwd(current->fs, &path);

	अगर (!d_can_lookup(path.dentry))
		जाओ notdir;

	cachefiles_begin_secure(cache, &saved_cred);
	ret = cachefiles_cull(cache, path.dentry, args);
	cachefiles_end_secure(cache, saved_cred);

	path_put(&path);
	_leave(" = %d", ret);
	वापस ret;

notdir:
	path_put(&path);
	pr_err("cull command requires dirfd to be a directory\n");
	वापस -ENOTसूची;

inval:
	pr_err("cull command requires dirfd and filename\n");
	वापस -EINVAL;
पूर्ण

/*
 * set debugging mode
 * - command: "debug <mask>"
 */
अटल पूर्णांक cachefiles_daemon_debug(काष्ठा cachefiles_cache *cache, अक्षर *args)
अणु
	अचिन्हित दीर्घ mask;

	_enter(",%s", args);

	mask = simple_म_से_अदीर्घ(args, &args, 0);
	अगर (args[0] != '\0')
		जाओ inval;

	cachefiles_debug = mask;
	_leave(" = 0");
	वापस 0;

inval:
	pr_err("debug command requires mask\n");
	वापस -EINVAL;
पूर्ण

/*
 * find out whether an object in the current working directory is in use or not
 * - command: "inuse <name>"
 */
अटल पूर्णांक cachefiles_daemon_inuse(काष्ठा cachefiles_cache *cache, अक्षर *args)
अणु
	काष्ठा path path;
	स्थिर काष्ठा cred *saved_cred;
	पूर्णांक ret;

	//_enter(",%s", args);

	अगर (म_अक्षर(args, '/'))
		जाओ inval;

	अगर (!test_bit(CACHEखाताS_READY, &cache->flags)) अणु
		pr_err("inuse applied to unready cache\n");
		वापस -EIO;
	पूर्ण

	अगर (test_bit(CACHEखाताS_DEAD, &cache->flags)) अणु
		pr_err("inuse applied to dead cache\n");
		वापस -EIO;
	पूर्ण

	/* extract the directory dentry from the cwd */
	get_fs_pwd(current->fs, &path);

	अगर (!d_can_lookup(path.dentry))
		जाओ notdir;

	cachefiles_begin_secure(cache, &saved_cred);
	ret = cachefiles_check_in_use(cache, path.dentry, args);
	cachefiles_end_secure(cache, saved_cred);

	path_put(&path);
	//_leave(" = %d", ret);
	वापस ret;

notdir:
	path_put(&path);
	pr_err("inuse command requires dirfd to be a directory\n");
	वापस -ENOTसूची;

inval:
	pr_err("inuse command requires dirfd and filename\n");
	वापस -EINVAL;
पूर्ण

/*
 * see अगर we have space क्रम a number of pages and/or a number of files in the
 * cache
 */
पूर्णांक cachefiles_has_space(काष्ठा cachefiles_cache *cache,
			 अचिन्हित fnr, अचिन्हित bnr)
अणु
	काष्ठा kstatfs stats;
	काष्ठा path path = अणु
		.mnt	= cache->mnt,
		.dentry	= cache->mnt->mnt_root,
	पूर्ण;
	पूर्णांक ret;

	//_enter("{%llu,%llu,%llu,%llu,%llu,%llu},%u,%u",
	//       (अचिन्हित दीर्घ दीर्घ) cache->frun,
	//       (अचिन्हित दीर्घ दीर्घ) cache->fcull,
	//       (अचिन्हित दीर्घ दीर्घ) cache->fstop,
	//       (अचिन्हित दीर्घ दीर्घ) cache->brun,
	//       (अचिन्हित दीर्घ दीर्घ) cache->bcull,
	//       (अचिन्हित दीर्घ दीर्घ) cache->bstop,
	//       fnr, bnr);

	/* find out how many pages of blockdev are available */
	स_रखो(&stats, 0, माप(stats));

	ret = vfs_statfs(&path, &stats);
	अगर (ret < 0) अणु
		अगर (ret == -EIO)
			cachefiles_io_error(cache, "statfs failed");
		_leave(" = %d", ret);
		वापस ret;
	पूर्ण

	stats.f_bavail >>= cache->bshअगरt;

	//_debug("avail %llu,%llu",
	//       (अचिन्हित दीर्घ दीर्घ) stats.f_fमुक्त,
	//       (अचिन्हित दीर्घ दीर्घ) stats.f_bavail);

	/* see अगर there is sufficient space */
	अगर (stats.f_fमुक्त > fnr)
		stats.f_fमुक्त -= fnr;
	अन्यथा
		stats.f_fमुक्त = 0;

	अगर (stats.f_bavail > bnr)
		stats.f_bavail -= bnr;
	अन्यथा
		stats.f_bavail = 0;

	ret = -ENOBUFS;
	अगर (stats.f_fमुक्त < cache->fstop ||
	    stats.f_bavail < cache->bstop)
		जाओ begin_cull;

	ret = 0;
	अगर (stats.f_fमुक्त < cache->fcull ||
	    stats.f_bavail < cache->bcull)
		जाओ begin_cull;

	अगर (test_bit(CACHEखाताS_CULLING, &cache->flags) &&
	    stats.f_fमुक्त >= cache->frun &&
	    stats.f_bavail >= cache->brun &&
	    test_and_clear_bit(CACHEखाताS_CULLING, &cache->flags)
	    ) अणु
		_debug("cease culling");
		cachefiles_state_changed(cache);
	पूर्ण

	//_leave(" = 0");
	वापस 0;

begin_cull:
	अगर (!test_and_set_bit(CACHEखाताS_CULLING, &cache->flags)) अणु
		_debug("### CULL CACHE ###");
		cachefiles_state_changed(cache);
	पूर्ण

	_leave(" = %d", ret);
	वापस ret;
पूर्ण
