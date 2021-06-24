<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Persistent Storage - ramfs parts.
 *
 * Copyright (C) 2010 Intel Corporation <tony.luck@पूर्णांकel.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/fs.h>
#समावेश <linux/fsnotअगरy.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/समय.स>
#समावेश <linux/init.h>
#समावेश <linux/list.h>
#समावेश <linux/माला.स>
#समावेश <linux/mount.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/ramfs.h>
#समावेश <linux/parser.h>
#समावेश <linux/sched.h>
#समावेश <linux/magic.h>
#समावेश <linux/pstore.h>
#समावेश <linux/slab.h>
#समावेश <linux/uaccess.h>

#समावेश "internal.h"

#घोषणा	PSTORE_NAMELEN	64

अटल DEFINE_MUTEX(records_list_lock);
अटल LIST_HEAD(records_list);

अटल DEFINE_MUTEX(pstore_sb_lock);
अटल काष्ठा super_block *pstore_sb;

काष्ठा pstore_निजी अणु
	काष्ठा list_head list;
	काष्ठा dentry *dentry;
	काष्ठा pstore_record *record;
	माप_प्रकार total_size;
पूर्ण;

काष्ठा pstore_ftrace_seq_data अणु
	स्थिर व्योम *ptr;
	माप_प्रकार off;
	माप_प्रकार size;
पूर्ण;

#घोषणा REC_SIZE माप(काष्ठा pstore_ftrace_record)

अटल व्योम मुक्त_pstore_निजी(काष्ठा pstore_निजी *निजी)
अणु
	अगर (!निजी)
		वापस;
	अगर (निजी->record) अणु
		kमुक्त(निजी->record->buf);
		kमुक्त(निजी->record);
	पूर्ण
	kमुक्त(निजी);
पूर्ण

अटल व्योम *pstore_ftrace_seq_start(काष्ठा seq_file *s, loff_t *pos)
अणु
	काष्ठा pstore_निजी *ps = s->निजी;
	काष्ठा pstore_ftrace_seq_data *data;

	data = kzalloc(माप(*data), GFP_KERNEL);
	अगर (!data)
		वापस शून्य;

	data->off = ps->total_size % REC_SIZE;
	data->off += *pos * REC_SIZE;
	अगर (data->off + REC_SIZE > ps->total_size) अणु
		kमुक्त(data);
		वापस शून्य;
	पूर्ण

	वापस data;

पूर्ण

अटल व्योम pstore_ftrace_seq_stop(काष्ठा seq_file *s, व्योम *v)
अणु
	kमुक्त(v);
पूर्ण

अटल व्योम *pstore_ftrace_seq_next(काष्ठा seq_file *s, व्योम *v, loff_t *pos)
अणु
	काष्ठा pstore_निजी *ps = s->निजी;
	काष्ठा pstore_ftrace_seq_data *data = v;

	(*pos)++;
	data->off += REC_SIZE;
	अगर (data->off + REC_SIZE > ps->total_size)
		वापस शून्य;

	वापस data;
पूर्ण

अटल पूर्णांक pstore_ftrace_seq_show(काष्ठा seq_file *s, व्योम *v)
अणु
	काष्ठा pstore_निजी *ps = s->निजी;
	काष्ठा pstore_ftrace_seq_data *data = v;
	काष्ठा pstore_ftrace_record *rec;

	अगर (!data)
		वापस 0;

	rec = (काष्ठा pstore_ftrace_record *)(ps->record->buf + data->off);

	seq_म_लिखो(s, "CPU:%d ts:%llu %08lx  %08lx  %ps <- %pS\n",
		   pstore_ftrace_decode_cpu(rec),
		   pstore_ftrace_पढ़ो_बारtamp(rec),
		   rec->ip, rec->parent_ip, (व्योम *)rec->ip,
		   (व्योम *)rec->parent_ip);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा seq_operations pstore_ftrace_seq_ops = अणु
	.start	= pstore_ftrace_seq_start,
	.next	= pstore_ftrace_seq_next,
	.stop	= pstore_ftrace_seq_stop,
	.show	= pstore_ftrace_seq_show,
पूर्ण;

अटल sमाप_प्रकार pstore_file_पढ़ो(काष्ठा file *file, अक्षर __user *userbuf,
						माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा seq_file *sf = file->निजी_data;
	काष्ठा pstore_निजी *ps = sf->निजी;

	अगर (ps->record->type == PSTORE_TYPE_FTRACE)
		वापस seq_पढ़ो(file, userbuf, count, ppos);
	वापस simple_पढ़ो_from_buffer(userbuf, count, ppos,
				       ps->record->buf, ps->total_size);
पूर्ण

अटल पूर्णांक pstore_file_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा pstore_निजी *ps = inode->i_निजी;
	काष्ठा seq_file *sf;
	पूर्णांक err;
	स्थिर काष्ठा seq_operations *sops = शून्य;

	अगर (ps->record->type == PSTORE_TYPE_FTRACE)
		sops = &pstore_ftrace_seq_ops;

	err = seq_खोलो(file, sops);
	अगर (err < 0)
		वापस err;

	sf = file->निजी_data;
	sf->निजी = ps;

	वापस 0;
पूर्ण

अटल loff_t pstore_file_llseek(काष्ठा file *file, loff_t off, पूर्णांक whence)
अणु
	काष्ठा seq_file *sf = file->निजी_data;

	अगर (sf->op)
		वापस seq_lseek(file, off, whence);
	वापस शेष_llseek(file, off, whence);
पूर्ण

अटल स्थिर काष्ठा file_operations pstore_file_operations = अणु
	.खोलो		= pstore_file_खोलो,
	.पढ़ो		= pstore_file_पढ़ो,
	.llseek		= pstore_file_llseek,
	.release	= seq_release,
पूर्ण;

/*
 * When a file is unlinked from our file प्रणाली we call the
 * platक्रमm driver to erase the record from persistent store.
 */
अटल पूर्णांक pstore_unlink(काष्ठा inode *dir, काष्ठा dentry *dentry)
अणु
	काष्ठा pstore_निजी *p = d_inode(dentry)->i_निजी;
	काष्ठा pstore_record *record = p->record;
	पूर्णांक rc = 0;

	अगर (!record->psi->erase)
		वापस -EPERM;

	/* Make sure we can't race जबतक removing this file. */
	mutex_lock(&records_list_lock);
	अगर (!list_empty(&p->list))
		list_del_init(&p->list);
	अन्यथा
		rc = -ENOENT;
	p->dentry = शून्य;
	mutex_unlock(&records_list_lock);
	अगर (rc)
		वापस rc;

	mutex_lock(&record->psi->पढ़ो_mutex);
	record->psi->erase(record);
	mutex_unlock(&record->psi->पढ़ो_mutex);

	वापस simple_unlink(dir, dentry);
पूर्ण

अटल व्योम pstore_evict_inode(काष्ठा inode *inode)
अणु
	काष्ठा pstore_निजी	*p = inode->i_निजी;

	clear_inode(inode);
	मुक्त_pstore_निजी(p);
पूर्ण

अटल स्थिर काष्ठा inode_operations pstore_dir_inode_operations = अणु
	.lookup		= simple_lookup,
	.unlink		= pstore_unlink,
पूर्ण;

अटल काष्ठा inode *pstore_get_inode(काष्ठा super_block *sb)
अणु
	काष्ठा inode *inode = new_inode(sb);
	अगर (inode) अणु
		inode->i_ino = get_next_ino();
		inode->i_aसमय = inode->i_mसमय = inode->i_स_समय = current_समय(inode);
	पूर्ण
	वापस inode;
पूर्ण

क्रमागत अणु
	Opt_kmsg_bytes, Opt_err
पूर्ण;

अटल स्थिर match_table_t tokens = अणु
	अणुOpt_kmsg_bytes, "kmsg_bytes=%u"पूर्ण,
	अणुOpt_err, शून्यपूर्ण
पूर्ण;

अटल व्योम parse_options(अक्षर *options)
अणु
	अक्षर		*p;
	substring_t	args[MAX_OPT_ARGS];
	पूर्णांक		option;

	अगर (!options)
		वापस;

	जबतक ((p = strsep(&options, ",")) != शून्य) अणु
		पूर्णांक token;

		अगर (!*p)
			जारी;

		token = match_token(p, tokens, args);
		चयन (token) अणु
		हाल Opt_kmsg_bytes:
			अगर (!match_पूर्णांक(&args[0], &option))
				pstore_set_kmsg_bytes(option);
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

/*
 * Display the mount options in /proc/mounts.
 */
अटल पूर्णांक pstore_show_options(काष्ठा seq_file *m, काष्ठा dentry *root)
अणु
	अगर (kmsg_bytes != CONFIG_PSTORE_DEFAULT_KMSG_BYTES)
		seq_म_लिखो(m, ",kmsg_bytes=%lu", kmsg_bytes);
	वापस 0;
पूर्ण

अटल पूर्णांक pstore_remount(काष्ठा super_block *sb, पूर्णांक *flags, अक्षर *data)
अणु
	sync_fileप्रणाली(sb);
	parse_options(data);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा super_operations pstore_ops = अणु
	.statfs		= simple_statfs,
	.drop_inode	= generic_delete_inode,
	.evict_inode	= pstore_evict_inode,
	.remount_fs	= pstore_remount,
	.show_options	= pstore_show_options,
पूर्ण;

अटल काष्ठा dentry *psinfo_lock_root(व्योम)
अणु
	काष्ठा dentry *root;

	mutex_lock(&pstore_sb_lock);
	/*
	 * Having no backend is fine -- no records appear.
	 * Not being mounted is fine -- nothing to करो.
	 */
	अगर (!psinfo || !pstore_sb) अणु
		mutex_unlock(&pstore_sb_lock);
		वापस शून्य;
	पूर्ण

	root = pstore_sb->s_root;
	inode_lock(d_inode(root));
	mutex_unlock(&pstore_sb_lock);

	वापस root;
पूर्ण

पूर्णांक pstore_put_backend_records(काष्ठा pstore_info *psi)
अणु
	काष्ठा pstore_निजी *pos, *पंचांगp;
	काष्ठा dentry *root;
	पूर्णांक rc = 0;

	root = psinfo_lock_root();
	अगर (!root)
		वापस 0;

	mutex_lock(&records_list_lock);
	list_क्रम_each_entry_safe(pos, पंचांगp, &records_list, list) अणु
		अगर (pos->record->psi == psi) अणु
			list_del_init(&pos->list);
			rc = simple_unlink(d_inode(root), pos->dentry);
			अगर (WARN_ON(rc))
				अवरोध;
			d_drop(pos->dentry);
			dput(pos->dentry);
			pos->dentry = शून्य;
		पूर्ण
	पूर्ण
	mutex_unlock(&records_list_lock);

	inode_unlock(d_inode(root));

	वापस rc;
पूर्ण

/*
 * Make a regular file in the root directory of our file प्रणाली.
 * Load it up with "size" bytes of data from "buf".
 * Set the mसमय & स_समय to the date that this record was originally stored.
 */
पूर्णांक pstore_mkfile(काष्ठा dentry *root, काष्ठा pstore_record *record)
अणु
	काष्ठा dentry		*dentry;
	काष्ठा inode		*inode;
	पूर्णांक			rc = 0;
	अक्षर			name[PSTORE_NAMELEN];
	काष्ठा pstore_निजी	*निजी, *pos;
	माप_प्रकार			size = record->size + record->ecc_notice_size;

	अगर (WARN_ON(!inode_is_locked(d_inode(root))))
		वापस -EINVAL;

	rc = -EEXIST;
	/* Skip records that are alपढ़ोy present in the fileप्रणाली. */
	mutex_lock(&records_list_lock);
	list_क्रम_each_entry(pos, &records_list, list) अणु
		अगर (pos->record->type == record->type &&
		    pos->record->id == record->id &&
		    pos->record->psi == record->psi)
			जाओ fail;
	पूर्ण

	rc = -ENOMEM;
	inode = pstore_get_inode(root->d_sb);
	अगर (!inode)
		जाओ fail;
	inode->i_mode = S_IFREG | 0444;
	inode->i_fop = &pstore_file_operations;
	scnम_लिखो(name, माप(name), "%s-%s-%llu%s",
			pstore_type_to_name(record->type),
			record->psi->name, record->id,
			record->compressed ? ".enc.z" : "");

	निजी = kzalloc(माप(*निजी), GFP_KERNEL);
	अगर (!निजी)
		जाओ fail_inode;

	dentry = d_alloc_name(root, name);
	अगर (!dentry)
		जाओ fail_निजी;

	निजी->dentry = dentry;
	निजी->record = record;
	inode->i_size = निजी->total_size = size;
	inode->i_निजी = निजी;

	अगर (record->समय.tv_sec)
		inode->i_mसमय = inode->i_स_समय = record->समय;

	d_add(dentry, inode);

	list_add(&निजी->list, &records_list);
	mutex_unlock(&records_list_lock);

	वापस 0;

fail_निजी:
	मुक्त_pstore_निजी(निजी);
fail_inode:
	iput(inode);
fail:
	mutex_unlock(&records_list_lock);
	वापस rc;
पूर्ण

/*
 * Read all the records from the persistent store. Create
 * files in our fileप्रणाली.  Don't warn about -EEXIST errors
 * when we are re-scanning the backing store looking to add new
 * error records.
 */
व्योम pstore_get_records(पूर्णांक quiet)
अणु
	काष्ठा dentry *root;

	root = psinfo_lock_root();
	अगर (!root)
		वापस;

	pstore_get_backend_records(psinfo, root, quiet);
	inode_unlock(d_inode(root));
पूर्ण

अटल पूर्णांक pstore_fill_super(काष्ठा super_block *sb, व्योम *data, पूर्णांक silent)
अणु
	काष्ठा inode *inode;

	sb->s_maxbytes		= MAX_LFS_खाताSIZE;
	sb->s_blocksize		= PAGE_SIZE;
	sb->s_blocksize_bits	= PAGE_SHIFT;
	sb->s_magic		= PSTOREFS_MAGIC;
	sb->s_op		= &pstore_ops;
	sb->s_समय_gran		= 1;

	parse_options(data);

	inode = pstore_get_inode(sb);
	अगर (inode) अणु
		inode->i_mode = S_IFसूची | 0750;
		inode->i_op = &pstore_dir_inode_operations;
		inode->i_fop = &simple_dir_operations;
		inc_nlink(inode);
	पूर्ण
	sb->s_root = d_make_root(inode);
	अगर (!sb->s_root)
		वापस -ENOMEM;

	mutex_lock(&pstore_sb_lock);
	pstore_sb = sb;
	mutex_unlock(&pstore_sb_lock);

	pstore_get_records(0);

	वापस 0;
पूर्ण

अटल काष्ठा dentry *pstore_mount(काष्ठा file_प्रणाली_type *fs_type,
	पूर्णांक flags, स्थिर अक्षर *dev_name, व्योम *data)
अणु
	वापस mount_single(fs_type, flags, data, pstore_fill_super);
पूर्ण

अटल व्योम pstore_समाप्त_sb(काष्ठा super_block *sb)
अणु
	mutex_lock(&pstore_sb_lock);
	WARN_ON(pstore_sb && pstore_sb != sb);

	समाप्त_litter_super(sb);
	pstore_sb = शून्य;

	mutex_lock(&records_list_lock);
	INIT_LIST_HEAD(&records_list);
	mutex_unlock(&records_list_lock);

	mutex_unlock(&pstore_sb_lock);
पूर्ण

अटल काष्ठा file_प्रणाली_type pstore_fs_type = अणु
	.owner          = THIS_MODULE,
	.name		= "pstore",
	.mount		= pstore_mount,
	.समाप्त_sb	= pstore_समाप्त_sb,
पूर्ण;

पूर्णांक __init pstore_init_fs(व्योम)
अणु
	पूर्णांक err;

	/* Create a convenient mount poपूर्णांक क्रम people to access pstore */
	err = sysfs_create_mount_poपूर्णांक(fs_kobj, "pstore");
	अगर (err)
		जाओ out;

	err = रेजिस्टर_fileप्रणाली(&pstore_fs_type);
	अगर (err < 0)
		sysfs_हटाओ_mount_poपूर्णांक(fs_kobj, "pstore");

out:
	वापस err;
पूर्ण

व्योम __निकास pstore_निकास_fs(व्योम)
अणु
	unरेजिस्टर_fileप्रणाली(&pstore_fs_type);
	sysfs_हटाओ_mount_poपूर्णांक(fs_kobj, "pstore");
पूर्ण
