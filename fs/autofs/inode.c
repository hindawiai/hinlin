<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright 1997-1998 Transmeta Corporation -- All Rights Reserved
 * Copyright 2005-2006 Ian Kent <raven@themaw.net>
 */

#समावेश <linux/seq_file.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/parser.h>

#समावेश "autofs_i.h"

काष्ठा स्वतःfs_info *स्वतःfs_new_ino(काष्ठा स्वतःfs_sb_info *sbi)
अणु
	काष्ठा स्वतःfs_info *ino;

	ino = kzalloc(माप(*ino), GFP_KERNEL);
	अगर (ino) अणु
		INIT_LIST_HEAD(&ino->active);
		INIT_LIST_HEAD(&ino->expiring);
		ino->last_used = jअगरfies;
		ino->sbi = sbi;
	पूर्ण
	वापस ino;
पूर्ण

व्योम स्वतःfs_clean_ino(काष्ठा स्वतःfs_info *ino)
अणु
	ino->uid = GLOBAL_ROOT_UID;
	ino->gid = GLOBAL_ROOT_GID;
	ino->last_used = jअगरfies;
पूर्ण

व्योम स्वतःfs_मुक्त_ino(काष्ठा स्वतःfs_info *ino)
अणु
	kमुक्त_rcu(ino, rcu);
पूर्ण

व्योम स्वतःfs_समाप्त_sb(काष्ठा super_block *sb)
अणु
	काष्ठा स्वतःfs_sb_info *sbi = स्वतःfs_sbi(sb);

	/*
	 * In the event of a failure in get_sb_nodev the superblock
	 * info is not present so nothing अन्यथा has been setup, so
	 * just call समाप्त_anon_super when we are called from
	 * deactivate_super.
	 */
	अगर (sbi) अणु
		/* Free रुको queues, बंद pipe */
		स्वतःfs_catatonic_mode(sbi);
		put_pid(sbi->oz_pgrp);
	पूर्ण

	pr_debug("shutting down\n");
	समाप्त_litter_super(sb);
	अगर (sbi)
		kमुक्त_rcu(sbi, rcu);
पूर्ण

अटल पूर्णांक स्वतःfs_show_options(काष्ठा seq_file *m, काष्ठा dentry *root)
अणु
	काष्ठा स्वतःfs_sb_info *sbi = स्वतःfs_sbi(root->d_sb);
	काष्ठा inode *root_inode = d_inode(root->d_sb->s_root);

	अगर (!sbi)
		वापस 0;

	seq_म_लिखो(m, ",fd=%d", sbi->pipefd);
	अगर (!uid_eq(root_inode->i_uid, GLOBAL_ROOT_UID))
		seq_म_लिखो(m, ",uid=%u",
			from_kuid_munged(&init_user_ns, root_inode->i_uid));
	अगर (!gid_eq(root_inode->i_gid, GLOBAL_ROOT_GID))
		seq_म_लिखो(m, ",gid=%u",
			from_kgid_munged(&init_user_ns, root_inode->i_gid));
	seq_म_लिखो(m, ",pgrp=%d", pid_vnr(sbi->oz_pgrp));
	seq_म_लिखो(m, ",timeout=%lu", sbi->exp_समयout/HZ);
	seq_म_लिखो(m, ",minproto=%d", sbi->min_proto);
	seq_म_लिखो(m, ",maxproto=%d", sbi->max_proto);

	अगर (स्वतःfs_type_offset(sbi->type))
		seq_माला_दो(m, ",offset");
	अन्यथा अगर (स्वतःfs_type_direct(sbi->type))
		seq_माला_दो(m, ",direct");
	अन्यथा
		seq_माला_दो(m, ",indirect");
	अगर (sbi->flags & AUTOFS_SBI_STRICTEXPIRE)
		seq_माला_दो(m, ",strictexpire");
	अगर (sbi->flags & AUTOFS_SBI_IGNORE)
		seq_माला_दो(m, ",ignore");
#अगर_घोषित CONFIG_CHECKPOINT_RESTORE
	अगर (sbi->pipe)
		seq_म_लिखो(m, ",pipe_ino=%ld", file_inode(sbi->pipe)->i_ino);
	अन्यथा
		seq_माला_दो(m, ",pipe_ino=-1");
#पूर्ण_अगर
	वापस 0;
पूर्ण

अटल व्योम स्वतःfs_evict_inode(काष्ठा inode *inode)
अणु
	clear_inode(inode);
	kमुक्त(inode->i_निजी);
पूर्ण

अटल स्थिर काष्ठा super_operations स्वतःfs_sops = अणु
	.statfs		= simple_statfs,
	.show_options	= स्वतःfs_show_options,
	.evict_inode	= स्वतःfs_evict_inode,
पूर्ण;

क्रमागत अणुOpt_err, Opt_fd, Opt_uid, Opt_gid, Opt_pgrp, Opt_minproto, Opt_maxproto,
	Opt_indirect, Opt_direct, Opt_offset, Opt_strictexpire,
	Opt_ignoreपूर्ण;

अटल स्थिर match_table_t tokens = अणु
	अणुOpt_fd, "fd=%u"पूर्ण,
	अणुOpt_uid, "uid=%u"पूर्ण,
	अणुOpt_gid, "gid=%u"पूर्ण,
	अणुOpt_pgrp, "pgrp=%u"पूर्ण,
	अणुOpt_minproto, "minproto=%u"पूर्ण,
	अणुOpt_maxproto, "maxproto=%u"पूर्ण,
	अणुOpt_indirect, "indirect"पूर्ण,
	अणुOpt_direct, "direct"पूर्ण,
	अणुOpt_offset, "offset"पूर्ण,
	अणुOpt_strictexpire, "strictexpire"पूर्ण,
	अणुOpt_ignore, "ignore"पूर्ण,
	अणुOpt_err, शून्यपूर्ण
पूर्ण;

अटल पूर्णांक parse_options(अक्षर *options,
			 काष्ठा inode *root, पूर्णांक *pgrp, bool *pgrp_set,
			 काष्ठा स्वतःfs_sb_info *sbi)
अणु
	अक्षर *p;
	substring_t args[MAX_OPT_ARGS];
	पूर्णांक option;
	पूर्णांक pipefd = -1;
	kuid_t uid;
	kgid_t gid;

	root->i_uid = current_uid();
	root->i_gid = current_gid();

	sbi->min_proto = AUTOFS_MIN_PROTO_VERSION;
	sbi->max_proto = AUTOFS_MAX_PROTO_VERSION;

	sbi->pipefd = -1;

	अगर (!options)
		वापस 1;

	जबतक ((p = strsep(&options, ",")) != शून्य) अणु
		पूर्णांक token;

		अगर (!*p)
			जारी;

		token = match_token(p, tokens, args);
		चयन (token) अणु
		हाल Opt_fd:
			अगर (match_पूर्णांक(args, &pipefd))
				वापस 1;
			sbi->pipefd = pipefd;
			अवरोध;
		हाल Opt_uid:
			अगर (match_पूर्णांक(args, &option))
				वापस 1;
			uid = make_kuid(current_user_ns(), option);
			अगर (!uid_valid(uid))
				वापस 1;
			root->i_uid = uid;
			अवरोध;
		हाल Opt_gid:
			अगर (match_पूर्णांक(args, &option))
				वापस 1;
			gid = make_kgid(current_user_ns(), option);
			अगर (!gid_valid(gid))
				वापस 1;
			root->i_gid = gid;
			अवरोध;
		हाल Opt_pgrp:
			अगर (match_पूर्णांक(args, &option))
				वापस 1;
			*pgrp = option;
			*pgrp_set = true;
			अवरोध;
		हाल Opt_minproto:
			अगर (match_पूर्णांक(args, &option))
				वापस 1;
			sbi->min_proto = option;
			अवरोध;
		हाल Opt_maxproto:
			अगर (match_पूर्णांक(args, &option))
				वापस 1;
			sbi->max_proto = option;
			अवरोध;
		हाल Opt_indirect:
			set_स्वतःfs_type_indirect(&sbi->type);
			अवरोध;
		हाल Opt_direct:
			set_स्वतःfs_type_direct(&sbi->type);
			अवरोध;
		हाल Opt_offset:
			set_स्वतःfs_type_offset(&sbi->type);
			अवरोध;
		हाल Opt_strictexpire:
			sbi->flags |= AUTOFS_SBI_STRICTEXPIRE;
			अवरोध;
		हाल Opt_ignore:
			sbi->flags |= AUTOFS_SBI_IGNORE;
			अवरोध;
		शेष:
			वापस 1;
		पूर्ण
	पूर्ण
	वापस (sbi->pipefd < 0);
पूर्ण

पूर्णांक स्वतःfs_fill_super(काष्ठा super_block *s, व्योम *data, पूर्णांक silent)
अणु
	काष्ठा inode *root_inode;
	काष्ठा dentry *root;
	काष्ठा file *pipe;
	काष्ठा स्वतःfs_sb_info *sbi;
	काष्ठा स्वतःfs_info *ino;
	पूर्णांक pgrp = 0;
	bool pgrp_set = false;
	पूर्णांक ret = -EINVAL;

	sbi = kzalloc(माप(*sbi), GFP_KERNEL);
	अगर (!sbi)
		वापस -ENOMEM;
	pr_debug("starting up, sbi = %p\n", sbi);

	s->s_fs_info = sbi;
	sbi->magic = AUTOFS_SBI_MAGIC;
	sbi->pipefd = -1;
	sbi->pipe = शून्य;
	sbi->exp_समयout = 0;
	sbi->oz_pgrp = शून्य;
	sbi->sb = s;
	sbi->version = 0;
	sbi->sub_version = 0;
	sbi->flags = AUTOFS_SBI_CATATONIC;
	set_स्वतःfs_type_indirect(&sbi->type);
	sbi->min_proto = 0;
	sbi->max_proto = 0;
	mutex_init(&sbi->wq_mutex);
	mutex_init(&sbi->pipe_mutex);
	spin_lock_init(&sbi->fs_lock);
	sbi->queues = शून्य;
	spin_lock_init(&sbi->lookup_lock);
	INIT_LIST_HEAD(&sbi->active_list);
	INIT_LIST_HEAD(&sbi->expiring_list);
	s->s_blocksize = 1024;
	s->s_blocksize_bits = 10;
	s->s_magic = AUTOFS_SUPER_MAGIC;
	s->s_op = &स्वतःfs_sops;
	s->s_d_op = &स्वतःfs_dentry_operations;
	s->s_समय_gran = 1;

	/*
	 * Get the root inode and dentry, but defer checking क्रम errors.
	 */
	ino = स्वतःfs_new_ino(sbi);
	अगर (!ino) अणु
		ret = -ENOMEM;
		जाओ fail_मुक्त;
	पूर्ण
	root_inode = स्वतःfs_get_inode(s, S_IFसूची | 0755);
	root = d_make_root(root_inode);
	अगर (!root) अणु
		ret = -ENOMEM;
		जाओ fail_ino;
	पूर्ण
	pipe = शून्य;

	root->d_fsdata = ino;

	/* Can this call block? */
	अगर (parse_options(data, root_inode, &pgrp, &pgrp_set, sbi)) अणु
		pr_err("called with bogus options\n");
		जाओ fail_dput;
	पूर्ण

	/* Test versions first */
	अगर (sbi->max_proto < AUTOFS_MIN_PROTO_VERSION ||
	    sbi->min_proto > AUTOFS_MAX_PROTO_VERSION) अणु
		pr_err("kernel does not match daemon version "
		       "daemon (%d, %d) kernel (%d, %d)\n",
		       sbi->min_proto, sbi->max_proto,
		       AUTOFS_MIN_PROTO_VERSION, AUTOFS_MAX_PROTO_VERSION);
		जाओ fail_dput;
	पूर्ण

	/* Establish highest kernel protocol version */
	अगर (sbi->max_proto > AUTOFS_MAX_PROTO_VERSION)
		sbi->version = AUTOFS_MAX_PROTO_VERSION;
	अन्यथा
		sbi->version = sbi->max_proto;
	sbi->sub_version = AUTOFS_PROTO_SUBVERSION;

	अगर (pgrp_set) अणु
		sbi->oz_pgrp = find_get_pid(pgrp);
		अगर (!sbi->oz_pgrp) अणु
			pr_err("could not find process group %d\n",
				pgrp);
			जाओ fail_dput;
		पूर्ण
	पूर्ण अन्यथा अणु
		sbi->oz_pgrp = get_task_pid(current, PIDTYPE_PGID);
	पूर्ण

	अगर (स्वतःfs_type_trigger(sbi->type))
		__managed_dentry_set_managed(root);

	root_inode->i_fop = &स्वतःfs_root_operations;
	root_inode->i_op = &स्वतःfs_dir_inode_operations;

	pr_debug("pipe fd = %d, pgrp = %u\n",
		 sbi->pipefd, pid_nr(sbi->oz_pgrp));
	pipe = fget(sbi->pipefd);

	अगर (!pipe) अणु
		pr_err("could not open pipe file descriptor\n");
		जाओ fail_put_pid;
	पूर्ण
	ret = स्वतःfs_prepare_pipe(pipe);
	अगर (ret < 0)
		जाओ fail_fput;
	sbi->pipe = pipe;
	sbi->flags &= ~AUTOFS_SBI_CATATONIC;

	/*
	 * Success! Install the root dentry now to indicate completion.
	 */
	s->s_root = root;
	वापस 0;

	/*
	 * Failure ... clean up.
	 */
fail_fput:
	pr_err("pipe file descriptor does not contain proper ops\n");
	fput(pipe);
fail_put_pid:
	put_pid(sbi->oz_pgrp);
fail_dput:
	dput(root);
	जाओ fail_मुक्त;
fail_ino:
	स्वतःfs_मुक्त_ino(ino);
fail_मुक्त:
	kमुक्त(sbi);
	s->s_fs_info = शून्य;
	वापस ret;
पूर्ण

काष्ठा inode *स्वतःfs_get_inode(काष्ठा super_block *sb, umode_t mode)
अणु
	काष्ठा inode *inode = new_inode(sb);

	अगर (inode == शून्य)
		वापस शून्य;

	inode->i_mode = mode;
	अगर (sb->s_root) अणु
		inode->i_uid = d_inode(sb->s_root)->i_uid;
		inode->i_gid = d_inode(sb->s_root)->i_gid;
	पूर्ण
	inode->i_aसमय = inode->i_mसमय = inode->i_स_समय = current_समय(inode);
	inode->i_ino = get_next_ino();

	अगर (S_ISसूची(mode)) अणु
		set_nlink(inode, 2);
		inode->i_op = &स्वतःfs_dir_inode_operations;
		inode->i_fop = &स्वतःfs_dir_operations;
	पूर्ण अन्यथा अगर (S_ISLNK(mode)) अणु
		inode->i_op = &स्वतःfs_symlink_inode_operations;
	पूर्ण अन्यथा
		WARN_ON(1);

	वापस inode;
पूर्ण
