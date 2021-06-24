<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only

#समावेश <linux/ceph/ceph_debug.h>

#समावेश <linux/backing-dev.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/fs.h>
#समावेश <linux/inet.h>
#समावेश <linux/in6.h>
#समावेश <linux/module.h>
#समावेश <linux/mount.h>
#समावेश <linux/fs_context.h>
#समावेश <linux/fs_parser.h>
#समावेश <linux/sched.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/slab.h>
#समावेश <linux/statfs.h>
#समावेश <linux/माला.स>

#समावेश "super.h"
#समावेश "mds_client.h"
#समावेश "cache.h"

#समावेश <linux/ceph/ceph_features.h>
#समावेश <linux/ceph/decode.h>
#समावेश <linux/ceph/mon_client.h>
#समावेश <linux/ceph/auth.h>
#समावेश <linux/ceph/debugfs.h>

अटल DEFINE_SPINLOCK(ceph_fsc_lock);
अटल LIST_HEAD(ceph_fsc_list);

/*
 * Ceph superblock operations
 *
 * Handle the basics of mounting, unmounting.
 */

/*
 * super ops
 */
अटल व्योम ceph_put_super(काष्ठा super_block *s)
अणु
	काष्ठा ceph_fs_client *fsc = ceph_sb_to_client(s);

	करोut("put_super\n");
	ceph_mdsc_बंद_sessions(fsc->mdsc);
पूर्ण

अटल पूर्णांक ceph_statfs(काष्ठा dentry *dentry, काष्ठा kstatfs *buf)
अणु
	काष्ठा ceph_fs_client *fsc = ceph_inode_to_client(d_inode(dentry));
	काष्ठा ceph_mon_client *monc = &fsc->client->monc;
	काष्ठा ceph_statfs st;
	u64 fsid;
	पूर्णांक err;
	u64 data_pool;

	अगर (fsc->mdsc->mdsmap->m_num_data_pg_pools == 1) अणु
		data_pool = fsc->mdsc->mdsmap->m_data_pg_pools[0];
	पूर्ण अन्यथा अणु
		data_pool = CEPH_NOPOOL;
	पूर्ण

	करोut("statfs\n");
	err = ceph_monc_करो_statfs(monc, data_pool, &st);
	अगर (err < 0)
		वापस err;

	/* fill in kstatfs */
	buf->f_type = CEPH_SUPER_MAGIC;  /* ?? */

	/*
	 * express utilization in terms of large blocks to aव्योम
	 * overflow on 32-bit machines.
	 *
	 * NOTE: क्रम the समय being, we make bsize == frsize to humor
	 * not-yet-ancient versions of glibc that are broken.
	 * Someday, we will probably want to report a real block
	 * size...  whatever that may mean क्रम a network file प्रणाली!
	 */
	buf->f_bsize = 1 << CEPH_BLOCK_SHIFT;
	buf->f_frsize = 1 << CEPH_BLOCK_SHIFT;

	/*
	 * By शेष use root quota क्रम stats; fallback to overall fileप्रणाली
	 * usage अगर using 'noquotadf' mount option or if the root dir doesn't
	 * have max_bytes quota set.
	 */
	अगर (ceph_test_mount_opt(fsc, NOQUOTADF) ||
	    !ceph_quota_update_statfs(fsc, buf)) अणु
		buf->f_blocks = le64_to_cpu(st.kb) >> (CEPH_BLOCK_SHIFT-10);
		buf->f_bमुक्त = le64_to_cpu(st.kb_avail) >> (CEPH_BLOCK_SHIFT-10);
		buf->f_bavail = le64_to_cpu(st.kb_avail) >> (CEPH_BLOCK_SHIFT-10);
	पूर्ण

	buf->f_files = le64_to_cpu(st.num_objects);
	buf->f_fमुक्त = -1;
	buf->f_namelen = NAME_MAX;

	/* Must convert the fsid, क्रम consistent values across arches */
	mutex_lock(&monc->mutex);
	fsid = le64_to_cpu(*(__le64 *)(&monc->monmap->fsid)) ^
	       le64_to_cpu(*((__le64 *)&monc->monmap->fsid + 1));
	mutex_unlock(&monc->mutex);

	buf->f_fsid = u64_to_fsid(fsid);

	वापस 0;
पूर्ण

अटल पूर्णांक ceph_sync_fs(काष्ठा super_block *sb, पूर्णांक रुको)
अणु
	काष्ठा ceph_fs_client *fsc = ceph_sb_to_client(sb);

	अगर (!रुको) अणु
		करोut("sync_fs (non-blocking)\n");
		ceph_flush_dirty_caps(fsc->mdsc);
		करोut("sync_fs (non-blocking) done\n");
		वापस 0;
	पूर्ण

	करोut("sync_fs (blocking)\n");
	ceph_osdc_sync(&fsc->client->osdc);
	ceph_mdsc_sync(fsc->mdsc);
	करोut("sync_fs (blocking) done\n");
	वापस 0;
पूर्ण

/*
 * mount options
 */
क्रमागत अणु
	Opt_wsize,
	Opt_rsize,
	Opt_rasize,
	Opt_caps_wanted_delay_min,
	Opt_caps_wanted_delay_max,
	Opt_caps_max,
	Opt_सूची_पढ़ो_max_entries,
	Opt_सूची_पढ़ो_max_bytes,
	Opt_congestion_kb,
	/* पूर्णांक args above */
	Opt_snapस_नाम,
	Opt_mds_namespace,
	Opt_recover_session,
	Opt_source,
	/* string args above */
	Opt_dirstat,
	Opt_rbytes,
	Opt_asyncसूची_पढ़ो,
	Opt_dcache,
	Opt_ino32,
	Opt_fscache,
	Opt_poolperm,
	Opt_require_active_mds,
	Opt_acl,
	Opt_quotadf,
	Opt_copyfrom,
	Opt_wsync,
पूर्ण;

क्रमागत ceph_recover_session_mode अणु
	ceph_recover_session_no,
	ceph_recover_session_clean
पूर्ण;

अटल स्थिर काष्ठा स्थिरant_table ceph_param_recover[] = अणु
	अणु "no",		ceph_recover_session_no पूर्ण,
	अणु "clean",	ceph_recover_session_clean पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा fs_parameter_spec ceph_mount_parameters[] = अणु
	fsparam_flag_no ("acl",				Opt_acl),
	fsparam_flag_no ("asyncreaddir",		Opt_asyncसूची_पढ़ो),
	fsparam_s32	("caps_max",			Opt_caps_max),
	fsparam_u32	("caps_wanted_delay_max",	Opt_caps_wanted_delay_max),
	fsparam_u32	("caps_wanted_delay_min",	Opt_caps_wanted_delay_min),
	fsparam_u32	("write_congestion_kb",		Opt_congestion_kb),
	fsparam_flag_no ("copyfrom",			Opt_copyfrom),
	fsparam_flag_no ("dcache",			Opt_dcache),
	fsparam_flag_no ("dirstat",			Opt_dirstat),
	fsparam_flag_no	("fsc",				Opt_fscache), // fsc|nofsc
	fsparam_string	("fsc",				Opt_fscache), // fsc=...
	fsparam_flag_no ("ino32",			Opt_ino32),
	fsparam_string	("mds_namespace",		Opt_mds_namespace),
	fsparam_flag_no ("poolperm",			Opt_poolperm),
	fsparam_flag_no ("quotadf",			Opt_quotadf),
	fsparam_u32	("rasize",			Opt_rasize),
	fsparam_flag_no ("rbytes",			Opt_rbytes),
	fsparam_u32	("readdir_max_bytes",		Opt_सूची_पढ़ो_max_bytes),
	fsparam_u32	("readdir_max_entries",		Opt_सूची_पढ़ो_max_entries),
	fsparam_क्रमागत	("recover_session",		Opt_recover_session, ceph_param_recover),
	fsparam_flag_no ("require_active_mds",		Opt_require_active_mds),
	fsparam_u32	("rsize",			Opt_rsize),
	fsparam_string	("snapdirname",			Opt_snapस_नाम),
	fsparam_string	("source",			Opt_source),
	fsparam_u32	("wsize",			Opt_wsize),
	fsparam_flag_no	("wsync",			Opt_wsync),
	अणुपूर्ण
पूर्ण;

काष्ठा ceph_parse_opts_ctx अणु
	काष्ठा ceph_options		*copts;
	काष्ठा ceph_mount_options	*opts;
पूर्ण;

/*
 * Remove adjacent slashes and then the trailing slash, unless it is
 * the only reमुख्यing अक्षरacter.
 *
 * E.g. "//dir1////dir2///" --> "/dir1/dir2", "///" --> "/".
 */
अटल व्योम canonicalize_path(अक्षर *path)
अणु
	पूर्णांक i, j = 0;

	क्रम (i = 0; path[i] != '\0'; i++) अणु
		अगर (path[i] != '/' || j < 1 || path[j - 1] != '/')
			path[j++] = path[i];
	पूर्ण

	अगर (j > 1 && path[j - 1] == '/')
		j--;
	path[j] = '\0';
पूर्ण

/*
 * Parse the source parameter.  Distinguish the server list from the path.
 *
 * The source will look like:
 *     <server_spec>[,<server_spec>...]:[<path>]
 * where
 *     <server_spec> is <ip>[:<port>]
 *     <path> is optional, but अगर present must begin with '/'
 */
अटल पूर्णांक ceph_parse_source(काष्ठा fs_parameter *param, काष्ठा fs_context *fc)
अणु
	काष्ठा ceph_parse_opts_ctx *pctx = fc->fs_निजी;
	काष्ठा ceph_mount_options *fsopt = pctx->opts;
	अक्षर *dev_name = param->string, *dev_name_end;
	पूर्णांक ret;

	करोut("%s '%s'\n", __func__, dev_name);
	अगर (!dev_name || !*dev_name)
		वापस invalfc(fc, "Empty source");

	dev_name_end = म_अक्षर(dev_name, '/');
	अगर (dev_name_end) अणु
		/*
		 * The server_path will include the whole अक्षरs from userland
		 * including the leading '/'.
		 */
		kमुक्त(fsopt->server_path);
		fsopt->server_path = kstrdup(dev_name_end, GFP_KERNEL);
		अगर (!fsopt->server_path)
			वापस -ENOMEM;

		canonicalize_path(fsopt->server_path);
	पूर्ण अन्यथा अणु
		dev_name_end = dev_name + म_माप(dev_name);
	पूर्ण

	dev_name_end--;		/* back up to ':' separator */
	अगर (dev_name_end < dev_name || *dev_name_end != ':')
		वापस invalfc(fc, "No path or : separator in source");

	करोut("device name '%.*s'\n", (पूर्णांक)(dev_name_end - dev_name), dev_name);
	अगर (fsopt->server_path)
		करोut("server path '%s'\n", fsopt->server_path);

	ret = ceph_parse_mon_ips(param->string, dev_name_end - dev_name,
				 pctx->copts, fc->log.log);
	अगर (ret)
		वापस ret;

	fc->source = param->string;
	param->string = शून्य;
	वापस 0;
पूर्ण

अटल पूर्णांक ceph_parse_mount_param(काष्ठा fs_context *fc,
				  काष्ठा fs_parameter *param)
अणु
	काष्ठा ceph_parse_opts_ctx *pctx = fc->fs_निजी;
	काष्ठा ceph_mount_options *fsopt = pctx->opts;
	काष्ठा fs_parse_result result;
	अचिन्हित पूर्णांक mode;
	पूर्णांक token, ret;

	ret = ceph_parse_param(param, pctx->copts, fc->log.log);
	अगर (ret != -ENOPARAM)
		वापस ret;

	token = fs_parse(fc, ceph_mount_parameters, param, &result);
	करोut("%s fs_parse '%s' token %d\n", __func__, param->key, token);
	अगर (token < 0)
		वापस token;

	चयन (token) अणु
	हाल Opt_snapस_नाम:
		kमुक्त(fsopt->snapdir_name);
		fsopt->snapdir_name = param->string;
		param->string = शून्य;
		अवरोध;
	हाल Opt_mds_namespace:
		kमुक्त(fsopt->mds_namespace);
		fsopt->mds_namespace = param->string;
		param->string = शून्य;
		अवरोध;
	हाल Opt_recover_session:
		mode = result.uपूर्णांक_32;
		अगर (mode == ceph_recover_session_no)
			fsopt->flags &= ~CEPH_MOUNT_OPT_CLEANRECOVER;
		अन्यथा अगर (mode == ceph_recover_session_clean)
			fsopt->flags |= CEPH_MOUNT_OPT_CLEANRECOVER;
		अन्यथा
			BUG();
		अवरोध;
	हाल Opt_source:
		अगर (fc->source)
			वापस invalfc(fc, "Multiple sources specified");
		वापस ceph_parse_source(param, fc);
	हाल Opt_wsize:
		अगर (result.uपूर्णांक_32 < PAGE_SIZE ||
		    result.uपूर्णांक_32 > CEPH_MAX_WRITE_SIZE)
			जाओ out_of_range;
		fsopt->wsize = ALIGN(result.uपूर्णांक_32, PAGE_SIZE);
		अवरोध;
	हाल Opt_rsize:
		अगर (result.uपूर्णांक_32 < PAGE_SIZE ||
		    result.uपूर्णांक_32 > CEPH_MAX_READ_SIZE)
			जाओ out_of_range;
		fsopt->rsize = ALIGN(result.uपूर्णांक_32, PAGE_SIZE);
		अवरोध;
	हाल Opt_rasize:
		fsopt->rasize = ALIGN(result.uपूर्णांक_32, PAGE_SIZE);
		अवरोध;
	हाल Opt_caps_wanted_delay_min:
		अगर (result.uपूर्णांक_32 < 1)
			जाओ out_of_range;
		fsopt->caps_wanted_delay_min = result.uपूर्णांक_32;
		अवरोध;
	हाल Opt_caps_wanted_delay_max:
		अगर (result.uपूर्णांक_32 < 1)
			जाओ out_of_range;
		fsopt->caps_wanted_delay_max = result.uपूर्णांक_32;
		अवरोध;
	हाल Opt_caps_max:
		अगर (result.पूर्णांक_32 < 0)
			जाओ out_of_range;
		fsopt->caps_max = result.पूर्णांक_32;
		अवरोध;
	हाल Opt_सूची_पढ़ो_max_entries:
		अगर (result.uपूर्णांक_32 < 1)
			जाओ out_of_range;
		fsopt->max_सूची_पढ़ो = result.uपूर्णांक_32;
		अवरोध;
	हाल Opt_सूची_पढ़ो_max_bytes:
		अगर (result.uपूर्णांक_32 < PAGE_SIZE && result.uपूर्णांक_32 != 0)
			जाओ out_of_range;
		fsopt->max_सूची_पढ़ो_bytes = result.uपूर्णांक_32;
		अवरोध;
	हाल Opt_congestion_kb:
		अगर (result.uपूर्णांक_32 < 1024) /* at least 1M */
			जाओ out_of_range;
		fsopt->congestion_kb = result.uपूर्णांक_32;
		अवरोध;
	हाल Opt_dirstat:
		अगर (!result.negated)
			fsopt->flags |= CEPH_MOUNT_OPT_सूचीSTAT;
		अन्यथा
			fsopt->flags &= ~CEPH_MOUNT_OPT_सूचीSTAT;
		अवरोध;
	हाल Opt_rbytes:
		अगर (!result.negated)
			fsopt->flags |= CEPH_MOUNT_OPT_RBYTES;
		अन्यथा
			fsopt->flags &= ~CEPH_MOUNT_OPT_RBYTES;
		अवरोध;
	हाल Opt_asyncसूची_पढ़ो:
		अगर (!result.negated)
			fsopt->flags &= ~CEPH_MOUNT_OPT_NOASYNCREADसूची;
		अन्यथा
			fsopt->flags |= CEPH_MOUNT_OPT_NOASYNCREADसूची;
		अवरोध;
	हाल Opt_dcache:
		अगर (!result.negated)
			fsopt->flags |= CEPH_MOUNT_OPT_DCACHE;
		अन्यथा
			fsopt->flags &= ~CEPH_MOUNT_OPT_DCACHE;
		अवरोध;
	हाल Opt_ino32:
		अगर (!result.negated)
			fsopt->flags |= CEPH_MOUNT_OPT_INO32;
		अन्यथा
			fsopt->flags &= ~CEPH_MOUNT_OPT_INO32;
		अवरोध;

	हाल Opt_fscache:
#अगर_घोषित CONFIG_CEPH_FSCACHE
		kमुक्त(fsopt->fscache_uniq);
		fsopt->fscache_uniq = शून्य;
		अगर (result.negated) अणु
			fsopt->flags &= ~CEPH_MOUNT_OPT_FSCACHE;
		पूर्ण अन्यथा अणु
			fsopt->flags |= CEPH_MOUNT_OPT_FSCACHE;
			fsopt->fscache_uniq = param->string;
			param->string = शून्य;
		पूर्ण
		अवरोध;
#अन्यथा
		वापस invalfc(fc, "fscache support is disabled");
#पूर्ण_अगर
	हाल Opt_poolperm:
		अगर (!result.negated)
			fsopt->flags &= ~CEPH_MOUNT_OPT_NOPOOLPERM;
		अन्यथा
			fsopt->flags |= CEPH_MOUNT_OPT_NOPOOLPERM;
		अवरोध;
	हाल Opt_require_active_mds:
		अगर (!result.negated)
			fsopt->flags &= ~CEPH_MOUNT_OPT_MOUNTWAIT;
		अन्यथा
			fsopt->flags |= CEPH_MOUNT_OPT_MOUNTWAIT;
		अवरोध;
	हाल Opt_quotadf:
		अगर (!result.negated)
			fsopt->flags &= ~CEPH_MOUNT_OPT_NOQUOTADF;
		अन्यथा
			fsopt->flags |= CEPH_MOUNT_OPT_NOQUOTADF;
		अवरोध;
	हाल Opt_copyfrom:
		अगर (!result.negated)
			fsopt->flags &= ~CEPH_MOUNT_OPT_NOCOPYFROM;
		अन्यथा
			fsopt->flags |= CEPH_MOUNT_OPT_NOCOPYFROM;
		अवरोध;
	हाल Opt_acl:
		अगर (!result.negated) अणु
#अगर_घोषित CONFIG_CEPH_FS_POSIX_ACL
			fc->sb_flags |= SB_POSIXACL;
#अन्यथा
			वापस invalfc(fc, "POSIX ACL support is disabled");
#पूर्ण_अगर
		पूर्ण अन्यथा अणु
			fc->sb_flags &= ~SB_POSIXACL;
		पूर्ण
		अवरोध;
	हाल Opt_wsync:
		अगर (!result.negated)
			fsopt->flags &= ~CEPH_MOUNT_OPT_ASYNC_सूचीOPS;
		अन्यथा
			fsopt->flags |= CEPH_MOUNT_OPT_ASYNC_सूचीOPS;
		अवरोध;
	शेष:
		BUG();
	पूर्ण
	वापस 0;

out_of_range:
	वापस invalfc(fc, "%s out of range", param->key);
पूर्ण

अटल व्योम destroy_mount_options(काष्ठा ceph_mount_options *args)
अणु
	करोut("destroy_mount_options %p\n", args);
	अगर (!args)
		वापस;

	kमुक्त(args->snapdir_name);
	kमुक्त(args->mds_namespace);
	kमुक्त(args->server_path);
	kमुक्त(args->fscache_uniq);
	kमुक्त(args);
पूर्ण

अटल पूर्णांक म_भेद_null(स्थिर अक्षर *s1, स्थिर अक्षर *s2)
अणु
	अगर (!s1 && !s2)
		वापस 0;
	अगर (s1 && !s2)
		वापस -1;
	अगर (!s1 && s2)
		वापस 1;
	वापस म_भेद(s1, s2);
पूर्ण

अटल पूर्णांक compare_mount_options(काष्ठा ceph_mount_options *new_fsopt,
				 काष्ठा ceph_options *new_opt,
				 काष्ठा ceph_fs_client *fsc)
अणु
	काष्ठा ceph_mount_options *fsopt1 = new_fsopt;
	काष्ठा ceph_mount_options *fsopt2 = fsc->mount_options;
	पूर्णांक ofs = दुरत्व(काष्ठा ceph_mount_options, snapdir_name);
	पूर्णांक ret;

	ret = स_भेद(fsopt1, fsopt2, ofs);
	अगर (ret)
		वापस ret;

	ret = म_भेद_null(fsopt1->snapdir_name, fsopt2->snapdir_name);
	अगर (ret)
		वापस ret;

	ret = म_भेद_null(fsopt1->mds_namespace, fsopt2->mds_namespace);
	अगर (ret)
		वापस ret;

	ret = म_भेद_null(fsopt1->server_path, fsopt2->server_path);
	अगर (ret)
		वापस ret;

	ret = म_भेद_null(fsopt1->fscache_uniq, fsopt2->fscache_uniq);
	अगर (ret)
		वापस ret;

	वापस ceph_compare_options(new_opt, fsc->client);
पूर्ण

/**
 * ceph_show_options - Show mount options in /proc/mounts
 * @m: seq_file to ग_लिखो to
 * @root: root of that (sub)tree
 */
अटल पूर्णांक ceph_show_options(काष्ठा seq_file *m, काष्ठा dentry *root)
अणु
	काष्ठा ceph_fs_client *fsc = ceph_sb_to_client(root->d_sb);
	काष्ठा ceph_mount_options *fsopt = fsc->mount_options;
	माप_प्रकार pos;
	पूर्णांक ret;

	/* a comma between MNT/MS and client options */
	seq_अ_दो(m, ',');
	pos = m->count;

	ret = ceph_prपूर्णांक_client_options(m, fsc->client, false);
	अगर (ret)
		वापस ret;

	/* retract our comma अगर no client options */
	अगर (m->count == pos)
		m->count--;

	अगर (fsopt->flags & CEPH_MOUNT_OPT_सूचीSTAT)
		seq_माला_दो(m, ",dirstat");
	अगर ((fsopt->flags & CEPH_MOUNT_OPT_RBYTES))
		seq_माला_दो(m, ",rbytes");
	अगर (fsopt->flags & CEPH_MOUNT_OPT_NOASYNCREADसूची)
		seq_माला_दो(m, ",noasyncreaddir");
	अगर ((fsopt->flags & CEPH_MOUNT_OPT_DCACHE) == 0)
		seq_माला_दो(m, ",nodcache");
	अगर (fsopt->flags & CEPH_MOUNT_OPT_INO32)
		seq_माला_दो(m, ",ino32");
	अगर (fsopt->flags & CEPH_MOUNT_OPT_FSCACHE) अणु
		seq_show_option(m, "fsc", fsopt->fscache_uniq);
	पूर्ण
	अगर (fsopt->flags & CEPH_MOUNT_OPT_NOPOOLPERM)
		seq_माला_दो(m, ",nopoolperm");
	अगर (fsopt->flags & CEPH_MOUNT_OPT_NOQUOTADF)
		seq_माला_दो(m, ",noquotadf");

#अगर_घोषित CONFIG_CEPH_FS_POSIX_ACL
	अगर (root->d_sb->s_flags & SB_POSIXACL)
		seq_माला_दो(m, ",acl");
	अन्यथा
		seq_माला_दो(m, ",noacl");
#पूर्ण_अगर

	अगर ((fsopt->flags & CEPH_MOUNT_OPT_NOCOPYFROM) == 0)
		seq_माला_दो(m, ",copyfrom");

	अगर (fsopt->mds_namespace)
		seq_show_option(m, "mds_namespace", fsopt->mds_namespace);

	अगर (fsopt->flags & CEPH_MOUNT_OPT_CLEANRECOVER)
		seq_show_option(m, "recover_session", "clean");

	अगर (fsopt->flags & CEPH_MOUNT_OPT_ASYNC_सूचीOPS)
		seq_माला_दो(m, ",nowsync");

	अगर (fsopt->wsize != CEPH_MAX_WRITE_SIZE)
		seq_म_लिखो(m, ",wsize=%u", fsopt->wsize);
	अगर (fsopt->rsize != CEPH_MAX_READ_SIZE)
		seq_म_लिखो(m, ",rsize=%u", fsopt->rsize);
	अगर (fsopt->rasize != CEPH_RASIZE_DEFAULT)
		seq_म_लिखो(m, ",rasize=%u", fsopt->rasize);
	अगर (fsopt->congestion_kb != शेष_congestion_kb())
		seq_म_लिखो(m, ",write_congestion_kb=%u", fsopt->congestion_kb);
	अगर (fsopt->caps_max)
		seq_म_लिखो(m, ",caps_max=%d", fsopt->caps_max);
	अगर (fsopt->caps_wanted_delay_min != CEPH_CAPS_WANTED_DELAY_MIN_DEFAULT)
		seq_म_लिखो(m, ",caps_wanted_delay_min=%u",
			 fsopt->caps_wanted_delay_min);
	अगर (fsopt->caps_wanted_delay_max != CEPH_CAPS_WANTED_DELAY_MAX_DEFAULT)
		seq_म_लिखो(m, ",caps_wanted_delay_max=%u",
			   fsopt->caps_wanted_delay_max);
	अगर (fsopt->max_सूची_पढ़ो != CEPH_MAX_READसूची_DEFAULT)
		seq_म_लिखो(m, ",readdir_max_entries=%u", fsopt->max_सूची_पढ़ो);
	अगर (fsopt->max_सूची_पढ़ो_bytes != CEPH_MAX_READसूची_BYTES_DEFAULT)
		seq_म_लिखो(m, ",readdir_max_bytes=%u", fsopt->max_सूची_पढ़ो_bytes);
	अगर (म_भेद(fsopt->snapdir_name, CEPH_SNAPसूचीNAME_DEFAULT))
		seq_show_option(m, "snapdirname", fsopt->snapdir_name);

	वापस 0;
पूर्ण

/*
 * handle any mon messages the standard library करोesn't understand.
 * वापस error अगर we करोn't either.
 */
अटल पूर्णांक extra_mon_dispatch(काष्ठा ceph_client *client, काष्ठा ceph_msg *msg)
अणु
	काष्ठा ceph_fs_client *fsc = client->निजी;
	पूर्णांक type = le16_to_cpu(msg->hdr.type);

	चयन (type) अणु
	हाल CEPH_MSG_MDS_MAP:
		ceph_mdsc_handle_mdsmap(fsc->mdsc, msg);
		वापस 0;
	हाल CEPH_MSG_FS_MAP_USER:
		ceph_mdsc_handle_fsmap(fsc->mdsc, msg);
		वापस 0;
	शेष:
		वापस -1;
	पूर्ण
पूर्ण

/*
 * create a new fs client
 *
 * Success or not, this function consumes @fsopt and @opt.
 */
अटल काष्ठा ceph_fs_client *create_fs_client(काष्ठा ceph_mount_options *fsopt,
					काष्ठा ceph_options *opt)
अणु
	काष्ठा ceph_fs_client *fsc;
	पूर्णांक err;

	fsc = kzalloc(माप(*fsc), GFP_KERNEL);
	अगर (!fsc) अणु
		err = -ENOMEM;
		जाओ fail;
	पूर्ण

	fsc->client = ceph_create_client(opt, fsc);
	अगर (IS_ERR(fsc->client)) अणु
		err = PTR_ERR(fsc->client);
		जाओ fail;
	पूर्ण
	opt = शून्य; /* fsc->client now owns this */

	fsc->client->extra_mon_dispatch = extra_mon_dispatch;
	ceph_set_opt(fsc->client, ABORT_ON_FULL);

	अगर (!fsopt->mds_namespace) अणु
		ceph_monc_want_map(&fsc->client->monc, CEPH_SUB_MDSMAP,
				   0, true);
	पूर्ण अन्यथा अणु
		ceph_monc_want_map(&fsc->client->monc, CEPH_SUB_FSMAP,
				   0, false);
	पूर्ण

	fsc->mount_options = fsopt;

	fsc->sb = शून्य;
	fsc->mount_state = CEPH_MOUNT_MOUNTING;
	fsc->filp_gen = 1;
	fsc->have_copy_from2 = true;

	atomic_दीर्घ_set(&fsc->ग_लिखोback_count, 0);

	err = -ENOMEM;
	/*
	 * The number of concurrent works can be high but they करोn't need
	 * to be processed in parallel, limit concurrency.
	 */
	fsc->inode_wq = alloc_workqueue("ceph-inode", WQ_UNBOUND, 0);
	अगर (!fsc->inode_wq)
		जाओ fail_client;
	fsc->cap_wq = alloc_workqueue("ceph-cap", 0, 1);
	अगर (!fsc->cap_wq)
		जाओ fail_inode_wq;

	spin_lock(&ceph_fsc_lock);
	list_add_tail(&fsc->metric_wakeup, &ceph_fsc_list);
	spin_unlock(&ceph_fsc_lock);

	वापस fsc;

fail_inode_wq:
	destroy_workqueue(fsc->inode_wq);
fail_client:
	ceph_destroy_client(fsc->client);
fail:
	kमुक्त(fsc);
	अगर (opt)
		ceph_destroy_options(opt);
	destroy_mount_options(fsopt);
	वापस ERR_PTR(err);
पूर्ण

अटल व्योम flush_fs_workqueues(काष्ठा ceph_fs_client *fsc)
अणु
	flush_workqueue(fsc->inode_wq);
	flush_workqueue(fsc->cap_wq);
पूर्ण

अटल व्योम destroy_fs_client(काष्ठा ceph_fs_client *fsc)
अणु
	करोut("destroy_fs_client %p\n", fsc);

	spin_lock(&ceph_fsc_lock);
	list_del(&fsc->metric_wakeup);
	spin_unlock(&ceph_fsc_lock);

	ceph_mdsc_destroy(fsc);
	destroy_workqueue(fsc->inode_wq);
	destroy_workqueue(fsc->cap_wq);

	destroy_mount_options(fsc->mount_options);

	ceph_destroy_client(fsc->client);

	kमुक्त(fsc);
	करोut("destroy_fs_client %p done\n", fsc);
पूर्ण

/*
 * caches
 */
काष्ठा kmem_cache *ceph_inode_cachep;
काष्ठा kmem_cache *ceph_cap_cachep;
काष्ठा kmem_cache *ceph_cap_flush_cachep;
काष्ठा kmem_cache *ceph_dentry_cachep;
काष्ठा kmem_cache *ceph_file_cachep;
काष्ठा kmem_cache *ceph_dir_file_cachep;
काष्ठा kmem_cache *ceph_mds_request_cachep;
mempool_t *ceph_wb_pagevec_pool;

अटल व्योम ceph_inode_init_once(व्योम *foo)
अणु
	काष्ठा ceph_inode_info *ci = foo;
	inode_init_once(&ci->vfs_inode);
पूर्ण

अटल पूर्णांक __init init_caches(व्योम)
अणु
	पूर्णांक error = -ENOMEM;

	ceph_inode_cachep = kmem_cache_create("ceph_inode_info",
				      माप(काष्ठा ceph_inode_info),
				      __alignof__(काष्ठा ceph_inode_info),
				      SLAB_RECLAIM_ACCOUNT|SLAB_MEM_SPREAD|
				      SLAB_ACCOUNT, ceph_inode_init_once);
	अगर (!ceph_inode_cachep)
		वापस -ENOMEM;

	ceph_cap_cachep = KMEM_CACHE(ceph_cap, SLAB_MEM_SPREAD);
	अगर (!ceph_cap_cachep)
		जाओ bad_cap;
	ceph_cap_flush_cachep = KMEM_CACHE(ceph_cap_flush,
					   SLAB_RECLAIM_ACCOUNT|SLAB_MEM_SPREAD);
	अगर (!ceph_cap_flush_cachep)
		जाओ bad_cap_flush;

	ceph_dentry_cachep = KMEM_CACHE(ceph_dentry_info,
					SLAB_RECLAIM_ACCOUNT|SLAB_MEM_SPREAD);
	अगर (!ceph_dentry_cachep)
		जाओ bad_dentry;

	ceph_file_cachep = KMEM_CACHE(ceph_file_info, SLAB_MEM_SPREAD);
	अगर (!ceph_file_cachep)
		जाओ bad_file;

	ceph_dir_file_cachep = KMEM_CACHE(ceph_dir_file_info, SLAB_MEM_SPREAD);
	अगर (!ceph_dir_file_cachep)
		जाओ bad_dir_file;

	ceph_mds_request_cachep = KMEM_CACHE(ceph_mds_request, SLAB_MEM_SPREAD);
	अगर (!ceph_mds_request_cachep)
		जाओ bad_mds_req;

	ceph_wb_pagevec_pool = mempool_create_kदो_स्मृति_pool(10, CEPH_MAX_WRITE_SIZE >> PAGE_SHIFT);
	अगर (!ceph_wb_pagevec_pool)
		जाओ bad_pagevec_pool;

	error = ceph_fscache_रेजिस्टर();
	अगर (error)
		जाओ bad_fscache;

	वापस 0;

bad_fscache:
	kmem_cache_destroy(ceph_mds_request_cachep);
bad_pagevec_pool:
	mempool_destroy(ceph_wb_pagevec_pool);
bad_mds_req:
	kmem_cache_destroy(ceph_dir_file_cachep);
bad_dir_file:
	kmem_cache_destroy(ceph_file_cachep);
bad_file:
	kmem_cache_destroy(ceph_dentry_cachep);
bad_dentry:
	kmem_cache_destroy(ceph_cap_flush_cachep);
bad_cap_flush:
	kmem_cache_destroy(ceph_cap_cachep);
bad_cap:
	kmem_cache_destroy(ceph_inode_cachep);
	वापस error;
पूर्ण

अटल व्योम destroy_caches(व्योम)
अणु
	/*
	 * Make sure all delayed rcu मुक्त inodes are flushed beक्रमe we
	 * destroy cache.
	 */
	rcu_barrier();

	kmem_cache_destroy(ceph_inode_cachep);
	kmem_cache_destroy(ceph_cap_cachep);
	kmem_cache_destroy(ceph_cap_flush_cachep);
	kmem_cache_destroy(ceph_dentry_cachep);
	kmem_cache_destroy(ceph_file_cachep);
	kmem_cache_destroy(ceph_dir_file_cachep);
	kmem_cache_destroy(ceph_mds_request_cachep);
	mempool_destroy(ceph_wb_pagevec_pool);

	ceph_fscache_unरेजिस्टर();
पूर्ण

अटल व्योम __ceph_umount_begin(काष्ठा ceph_fs_client *fsc)
अणु
	ceph_osdc_पात_requests(&fsc->client->osdc, -EIO);
	ceph_mdsc_क्रमce_umount(fsc->mdsc);
	fsc->filp_gen++; // invalidate खोलो files
पूर्ण

/*
 * ceph_umount_begin - initiate क्रमced umount.  Tear करोwn the
 * mount, skipping steps that may hang जबतक रुकोing क्रम server(s).
 */
अटल व्योम ceph_umount_begin(काष्ठा super_block *sb)
अणु
	काष्ठा ceph_fs_client *fsc = ceph_sb_to_client(sb);

	करोut("ceph_umount_begin - starting forced umount\n");
	अगर (!fsc)
		वापस;
	fsc->mount_state = CEPH_MOUNT_SHUTDOWN;
	__ceph_umount_begin(fsc);
पूर्ण

अटल स्थिर काष्ठा super_operations ceph_super_ops = अणु
	.alloc_inode	= ceph_alloc_inode,
	.मुक्त_inode	= ceph_मुक्त_inode,
	.ग_लिखो_inode    = ceph_ग_लिखो_inode,
	.drop_inode	= generic_delete_inode,
	.evict_inode	= ceph_evict_inode,
	.sync_fs        = ceph_sync_fs,
	.put_super	= ceph_put_super,
	.show_options   = ceph_show_options,
	.statfs		= ceph_statfs,
	.umount_begin   = ceph_umount_begin,
पूर्ण;

/*
 * Bootstrap mount by खोलोing the root directory.  Note the mount
 * @started समय from caller, and समय out अगर this takes too दीर्घ.
 */
अटल काष्ठा dentry *खोलो_root_dentry(काष्ठा ceph_fs_client *fsc,
				       स्थिर अक्षर *path,
				       अचिन्हित दीर्घ started)
अणु
	काष्ठा ceph_mds_client *mdsc = fsc->mdsc;
	काष्ठा ceph_mds_request *req = शून्य;
	पूर्णांक err;
	काष्ठा dentry *root;

	/* खोलो dir */
	करोut("open_root_inode opening '%s'\n", path);
	req = ceph_mdsc_create_request(mdsc, CEPH_MDS_OP_GETATTR, USE_ANY_MDS);
	अगर (IS_ERR(req))
		वापस ERR_CAST(req);
	req->r_path1 = kstrdup(path, GFP_NOFS);
	अगर (!req->r_path1) अणु
		root = ERR_PTR(-ENOMEM);
		जाओ out;
	पूर्ण

	req->r_ino1.ino = CEPH_INO_ROOT;
	req->r_ino1.snap = CEPH_NOSNAP;
	req->r_started = started;
	req->r_समयout = fsc->client->options->mount_समयout;
	req->r_args.getattr.mask = cpu_to_le32(CEPH_STAT_CAP_INODE);
	req->r_num_caps = 2;
	err = ceph_mdsc_करो_request(mdsc, शून्य, req);
	अगर (err == 0) अणु
		काष्ठा inode *inode = req->r_target_inode;
		req->r_target_inode = शून्य;
		करोut("open_root_inode success\n");
		root = d_make_root(inode);
		अगर (!root) अणु
			root = ERR_PTR(-ENOMEM);
			जाओ out;
		पूर्ण
		करोut("open_root_inode success, root dentry is %p\n", root);
	पूर्ण अन्यथा अणु
		root = ERR_PTR(err);
	पूर्ण
out:
	ceph_mdsc_put_request(req);
	वापस root;
पूर्ण

/*
 * mount: join the ceph cluster, and खोलो root directory.
 */
अटल काष्ठा dentry *ceph_real_mount(काष्ठा ceph_fs_client *fsc,
				      काष्ठा fs_context *fc)
अणु
	पूर्णांक err;
	अचिन्हित दीर्घ started = jअगरfies;  /* note the start समय */
	काष्ठा dentry *root;

	करोut("mount start %p\n", fsc);
	mutex_lock(&fsc->client->mount_mutex);

	अगर (!fsc->sb->s_root) अणु
		स्थिर अक्षर *path = fsc->mount_options->server_path ?
				     fsc->mount_options->server_path + 1 : "";

		err = __ceph_खोलो_session(fsc->client, started);
		अगर (err < 0)
			जाओ out;

		/* setup fscache */
		अगर (fsc->mount_options->flags & CEPH_MOUNT_OPT_FSCACHE) अणु
			err = ceph_fscache_रेजिस्टर_fs(fsc, fc);
			अगर (err < 0)
				जाओ out;
		पूर्ण

		करोut("mount opening path '%s'\n", path);

		ceph_fs_debugfs_init(fsc);

		root = खोलो_root_dentry(fsc, path, started);
		अगर (IS_ERR(root)) अणु
			err = PTR_ERR(root);
			जाओ out;
		पूर्ण
		fsc->sb->s_root = dget(root);
	पूर्ण अन्यथा अणु
		root = dget(fsc->sb->s_root);
	पूर्ण

	fsc->mount_state = CEPH_MOUNT_MOUNTED;
	करोut("mount success\n");
	mutex_unlock(&fsc->client->mount_mutex);
	वापस root;

out:
	mutex_unlock(&fsc->client->mount_mutex);
	वापस ERR_PTR(err);
पूर्ण

अटल पूर्णांक ceph_set_super(काष्ठा super_block *s, काष्ठा fs_context *fc)
अणु
	काष्ठा ceph_fs_client *fsc = s->s_fs_info;
	पूर्णांक ret;

	करोut("set_super %p\n", s);

	s->s_maxbytes = MAX_LFS_खाताSIZE;

	s->s_xattr = ceph_xattr_handlers;
	fsc->sb = s;
	fsc->max_file_size = 1ULL << 40; /* temp value until we get mdsmap */

	s->s_op = &ceph_super_ops;
	s->s_d_op = &ceph_dentry_ops;
	s->s_export_op = &ceph_export_ops;

	s->s_समय_gran = 1;
	s->s_समय_min = 0;
	s->s_समय_max = U32_MAX;

	ret = set_anon_super_fc(s, fc);
	अगर (ret != 0)
		fsc->sb = शून्य;
	वापस ret;
पूर्ण

/*
 * share superblock अगर same fs AND options
 */
अटल पूर्णांक ceph_compare_super(काष्ठा super_block *sb, काष्ठा fs_context *fc)
अणु
	काष्ठा ceph_fs_client *new = fc->s_fs_info;
	काष्ठा ceph_mount_options *fsopt = new->mount_options;
	काष्ठा ceph_options *opt = new->client->options;
	काष्ठा ceph_fs_client *other = ceph_sb_to_client(sb);

	करोut("ceph_compare_super %p\n", sb);

	अगर (compare_mount_options(fsopt, opt, other)) अणु
		करोut("monitor(s)/mount options don't match\n");
		वापस 0;
	पूर्ण
	अगर ((opt->flags & CEPH_OPT_FSID) &&
	    ceph_fsid_compare(&opt->fsid, &other->client->fsid)) अणु
		करोut("fsid doesn't match\n");
		वापस 0;
	पूर्ण
	अगर (fc->sb_flags != (sb->s_flags & ~SB_BORN)) अणु
		करोut("flags differ\n");
		वापस 0;
	पूर्ण
	वापस 1;
पूर्ण

/*
 * स्थिरruct our own bdi so we can control पढ़ोahead, etc.
 */
अटल atomic_दीर्घ_t bdi_seq = ATOMIC_LONG_INIT(0);

अटल पूर्णांक ceph_setup_bdi(काष्ठा super_block *sb, काष्ठा ceph_fs_client *fsc)
अणु
	पूर्णांक err;

	err = super_setup_bdi_name(sb, "ceph-%ld",
				   atomic_दीर्घ_inc_वापस(&bdi_seq));
	अगर (err)
		वापस err;

	/* set ra_pages based on rasize mount option? */
	sb->s_bdi->ra_pages = fsc->mount_options->rasize >> PAGE_SHIFT;

	/* set io_pages based on max osd पढ़ो size */
	sb->s_bdi->io_pages = fsc->mount_options->rsize >> PAGE_SHIFT;

	वापस 0;
पूर्ण

अटल पूर्णांक ceph_get_tree(काष्ठा fs_context *fc)
अणु
	काष्ठा ceph_parse_opts_ctx *pctx = fc->fs_निजी;
	काष्ठा super_block *sb;
	काष्ठा ceph_fs_client *fsc;
	काष्ठा dentry *res;
	पूर्णांक (*compare_super)(काष्ठा super_block *, काष्ठा fs_context *) =
		ceph_compare_super;
	पूर्णांक err;

	करोut("ceph_get_tree\n");

	अगर (!fc->source)
		वापस invalfc(fc, "No source");

	/* create client (which we may/may not use) */
	fsc = create_fs_client(pctx->opts, pctx->copts);
	pctx->opts = शून्य;
	pctx->copts = शून्य;
	अगर (IS_ERR(fsc)) अणु
		err = PTR_ERR(fsc);
		जाओ out_final;
	पूर्ण

	err = ceph_mdsc_init(fsc);
	अगर (err < 0)
		जाओ out;

	अगर (ceph_test_opt(fsc->client, NOSHARE))
		compare_super = शून्य;

	fc->s_fs_info = fsc;
	sb = sget_fc(fc, compare_super, ceph_set_super);
	fc->s_fs_info = शून्य;
	अगर (IS_ERR(sb)) अणु
		err = PTR_ERR(sb);
		जाओ out;
	पूर्ण

	अगर (ceph_sb_to_client(sb) != fsc) अणु
		destroy_fs_client(fsc);
		fsc = ceph_sb_to_client(sb);
		करोut("get_sb got existing client %p\n", fsc);
	पूर्ण अन्यथा अणु
		करोut("get_sb using new client %p\n", fsc);
		err = ceph_setup_bdi(sb, fsc);
		अगर (err < 0)
			जाओ out_splat;
	पूर्ण

	res = ceph_real_mount(fsc, fc);
	अगर (IS_ERR(res)) अणु
		err = PTR_ERR(res);
		जाओ out_splat;
	पूर्ण
	करोut("root %p inode %p ino %llx.%llx\n", res,
	     d_inode(res), ceph_vinop(d_inode(res)));
	fc->root = fsc->sb->s_root;
	वापस 0;

out_splat:
	अगर (!ceph_mdsmap_is_cluster_available(fsc->mdsc->mdsmap)) अणु
		pr_info("No mds server is up or the cluster is laggy\n");
		err = -EHOSTUNREACH;
	पूर्ण

	ceph_mdsc_बंद_sessions(fsc->mdsc);
	deactivate_locked_super(sb);
	जाओ out_final;

out:
	destroy_fs_client(fsc);
out_final:
	करोut("ceph_get_tree fail %d\n", err);
	वापस err;
पूर्ण

अटल व्योम ceph_मुक्त_fc(काष्ठा fs_context *fc)
अणु
	काष्ठा ceph_parse_opts_ctx *pctx = fc->fs_निजी;

	अगर (pctx) अणु
		destroy_mount_options(pctx->opts);
		ceph_destroy_options(pctx->copts);
		kमुक्त(pctx);
	पूर्ण
पूर्ण

अटल पूर्णांक ceph_reconfigure_fc(काष्ठा fs_context *fc)
अणु
	काष्ठा ceph_parse_opts_ctx *pctx = fc->fs_निजी;
	काष्ठा ceph_mount_options *fsopt = pctx->opts;
	काष्ठा ceph_fs_client *fsc = ceph_sb_to_client(fc->root->d_sb);

	अगर (fsopt->flags & CEPH_MOUNT_OPT_ASYNC_सूचीOPS)
		ceph_set_mount_opt(fsc, ASYNC_सूचीOPS);
	अन्यथा
		ceph_clear_mount_opt(fsc, ASYNC_सूचीOPS);

	sync_fileप्रणाली(fc->root->d_sb);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा fs_context_operations ceph_context_ops = अणु
	.मुक्त		= ceph_मुक्त_fc,
	.parse_param	= ceph_parse_mount_param,
	.get_tree	= ceph_get_tree,
	.reconfigure	= ceph_reconfigure_fc,
पूर्ण;

/*
 * Set up the fileप्रणाली mount context.
 */
अटल पूर्णांक ceph_init_fs_context(काष्ठा fs_context *fc)
अणु
	काष्ठा ceph_parse_opts_ctx *pctx;
	काष्ठा ceph_mount_options *fsopt;

	pctx = kzalloc(माप(*pctx), GFP_KERNEL);
	अगर (!pctx)
		वापस -ENOMEM;

	pctx->copts = ceph_alloc_options();
	अगर (!pctx->copts)
		जाओ nomem;

	pctx->opts = kzalloc(माप(*pctx->opts), GFP_KERNEL);
	अगर (!pctx->opts)
		जाओ nomem;

	fsopt = pctx->opts;
	fsopt->flags = CEPH_MOUNT_OPT_DEFAULT;

	fsopt->wsize = CEPH_MAX_WRITE_SIZE;
	fsopt->rsize = CEPH_MAX_READ_SIZE;
	fsopt->rasize = CEPH_RASIZE_DEFAULT;
	fsopt->snapdir_name = kstrdup(CEPH_SNAPसूचीNAME_DEFAULT, GFP_KERNEL);
	अगर (!fsopt->snapdir_name)
		जाओ nomem;

	fsopt->caps_wanted_delay_min = CEPH_CAPS_WANTED_DELAY_MIN_DEFAULT;
	fsopt->caps_wanted_delay_max = CEPH_CAPS_WANTED_DELAY_MAX_DEFAULT;
	fsopt->max_सूची_पढ़ो = CEPH_MAX_READसूची_DEFAULT;
	fsopt->max_सूची_पढ़ो_bytes = CEPH_MAX_READसूची_BYTES_DEFAULT;
	fsopt->congestion_kb = शेष_congestion_kb();

#अगर_घोषित CONFIG_CEPH_FS_POSIX_ACL
	fc->sb_flags |= SB_POSIXACL;
#पूर्ण_अगर

	fc->fs_निजी = pctx;
	fc->ops = &ceph_context_ops;
	वापस 0;

nomem:
	destroy_mount_options(pctx->opts);
	ceph_destroy_options(pctx->copts);
	kमुक्त(pctx);
	वापस -ENOMEM;
पूर्ण

अटल व्योम ceph_समाप्त_sb(काष्ठा super_block *s)
अणु
	काष्ठा ceph_fs_client *fsc = ceph_sb_to_client(s);

	करोut("kill_sb %p\n", s);

	ceph_mdsc_pre_umount(fsc->mdsc);
	flush_fs_workqueues(fsc);

	समाप्त_anon_super(s);

	fsc->client->extra_mon_dispatch = शून्य;
	ceph_fs_debugfs_cleanup(fsc);

	ceph_fscache_unरेजिस्टर_fs(fsc);

	destroy_fs_client(fsc);
पूर्ण

अटल काष्ठा file_प्रणाली_type ceph_fs_type = अणु
	.owner		= THIS_MODULE,
	.name		= "ceph",
	.init_fs_context = ceph_init_fs_context,
	.समाप्त_sb	= ceph_समाप्त_sb,
	.fs_flags	= FS_RENAME_DOES_D_MOVE,
पूर्ण;
MODULE_ALIAS_FS("ceph");

पूर्णांक ceph_क्रमce_reconnect(काष्ठा super_block *sb)
अणु
	काष्ठा ceph_fs_client *fsc = ceph_sb_to_client(sb);
	पूर्णांक err = 0;

	fsc->mount_state = CEPH_MOUNT_RECOVER;
	__ceph_umount_begin(fsc);

	/* Make sure all page caches get invalidated.
	 * see हटाओ_session_caps_cb() */
	flush_workqueue(fsc->inode_wq);

	/* In हाल that we were blocklisted. This also reset
	 * all mon/osd connections */
	ceph_reset_client_addr(fsc->client);

	ceph_osdc_clear_पात_err(&fsc->client->osdc);

	fsc->blocklisted = false;
	fsc->mount_state = CEPH_MOUNT_MOUNTED;

	अगर (sb->s_root) अणु
		err = __ceph_करो_getattr(d_inode(sb->s_root), शून्य,
					CEPH_STAT_CAP_INODE, true);
	पूर्ण
	वापस err;
पूर्ण

अटल पूर्णांक __init init_ceph(व्योम)
अणु
	पूर्णांक ret = init_caches();
	अगर (ret)
		जाओ out;

	ceph_flock_init();
	ret = रेजिस्टर_fileप्रणाली(&ceph_fs_type);
	अगर (ret)
		जाओ out_caches;

	pr_info("loaded (mds proto %d)\n", CEPH_MDSC_PROTOCOL);

	वापस 0;

out_caches:
	destroy_caches();
out:
	वापस ret;
पूर्ण

अटल व्योम __निकास निकास_ceph(व्योम)
अणु
	करोut("exit_ceph\n");
	unरेजिस्टर_fileप्रणाली(&ceph_fs_type);
	destroy_caches();
पूर्ण

अटल पूर्णांक param_set_metrics(स्थिर अक्षर *val, स्थिर काष्ठा kernel_param *kp)
अणु
	काष्ठा ceph_fs_client *fsc;
	पूर्णांक ret;

	ret = param_set_bool(val, kp);
	अगर (ret) अणु
		pr_err("Failed to parse sending metrics switch value '%s'\n",
		       val);
		वापस ret;
	पूर्ण अन्यथा अगर (!disable_send_metrics) अणु
		// wake up all the mds clients
		spin_lock(&ceph_fsc_lock);
		list_क्रम_each_entry(fsc, &ceph_fsc_list, metric_wakeup) अणु
			metric_schedule_delayed(&fsc->mdsc->metric);
		पूर्ण
		spin_unlock(&ceph_fsc_lock);
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा kernel_param_ops param_ops_metrics = अणु
	.set = param_set_metrics,
	.get = param_get_bool,
पूर्ण;

bool disable_send_metrics = false;
module_param_cb(disable_send_metrics, &param_ops_metrics, &disable_send_metrics, 0644);
MODULE_PARM_DESC(disable_send_metrics, "Enable sending perf metrics to ceph cluster (default: on)");

module_init(init_ceph);
module_निकास(निकास_ceph);

MODULE_AUTHOR("Sage Weil <sage@newdream.net>");
MODULE_AUTHOR("Yehuda Sadeh <yehuda@hq.newdream.net>");
MODULE_AUTHOR("Patience Warnick <patience@newdream.net>");
MODULE_DESCRIPTION("Ceph filesystem for Linux");
MODULE_LICENSE("GPL");
