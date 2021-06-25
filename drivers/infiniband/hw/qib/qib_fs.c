<शैली गुरु>
/*
 * Copyright (c) 2012 Intel Corporation. All rights reserved.
 * Copyright (c) 2006 - 2012 QLogic Corporation. All rights reserved.
 * Copyright (c) 2006 PathScale, Inc. All rights reserved.
 *
 * This software is available to you under a choice of one of two
 * licenses.  You may choose to be licensed under the terms of the GNU
 * General Public License (GPL) Version 2, available from the file
 * COPYING in the मुख्य directory of this source tree, or the
 * OpenIB.org BSD license below:
 *
 *     Redistribution and use in source and binary क्रमms, with or
 *     without modअगरication, are permitted provided that the following
 *     conditions are met:
 *
 *      - Redistributions of source code must retain the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer.
 *
 *      - Redistributions in binary क्रमm must reproduce the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer in the करोcumentation and/or other materials
 *        provided with the distribution.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#समावेश <linux/module.h>
#समावेश <linux/fs.h>
#समावेश <linux/fs_context.h>
#समावेश <linux/mount.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/init.h>
#समावेश <linux/namei.h>

#समावेश "qib.h"

#घोषणा QIBFS_MAGIC 0x726a77

अटल काष्ठा super_block *qib_super;

#घोषणा निजी2dd(file) (file_inode(file)->i_निजी)

अटल पूर्णांक qibfs_mknod(काष्ठा inode *dir, काष्ठा dentry *dentry,
		       umode_t mode, स्थिर काष्ठा file_operations *fops,
		       व्योम *data)
अणु
	पूर्णांक error;
	काष्ठा inode *inode = new_inode(dir->i_sb);

	अगर (!inode) अणु
		error = -EPERM;
		जाओ bail;
	पूर्ण

	inode->i_ino = get_next_ino();
	inode->i_mode = mode;
	inode->i_uid = GLOBAL_ROOT_UID;
	inode->i_gid = GLOBAL_ROOT_GID;
	inode->i_blocks = 0;
	inode->i_aसमय = current_समय(inode);
	inode->i_mसमय = inode->i_aसमय;
	inode->i_स_समय = inode->i_aसमय;
	inode->i_निजी = data;
	अगर (S_ISसूची(mode)) अणु
		inode->i_op = &simple_dir_inode_operations;
		inc_nlink(inode);
		inc_nlink(dir);
	पूर्ण

	inode->i_fop = fops;

	d_instantiate(dentry, inode);
	error = 0;

bail:
	वापस error;
पूर्ण

अटल पूर्णांक create_file(स्थिर अक्षर *name, umode_t mode,
		       काष्ठा dentry *parent, काष्ठा dentry **dentry,
		       स्थिर काष्ठा file_operations *fops, व्योम *data)
अणु
	पूर्णांक error;

	inode_lock(d_inode(parent));
	*dentry = lookup_one_len(name, parent, म_माप(name));
	अगर (!IS_ERR(*dentry))
		error = qibfs_mknod(d_inode(parent), *dentry,
				    mode, fops, data);
	अन्यथा
		error = PTR_ERR(*dentry);
	inode_unlock(d_inode(parent));

	वापस error;
पूर्ण

अटल sमाप_प्रकार driver_stats_पढ़ो(काष्ठा file *file, अक्षर __user *buf,
				 माप_प्रकार count, loff_t *ppos)
अणु
	qib_stats.sps_पूर्णांकs = qib_sps_पूर्णांकs();
	वापस simple_पढ़ो_from_buffer(buf, count, ppos, &qib_stats,
				       माप(qib_stats));
पूर्ण

/*
 * driver stats field names, one line per stat, single string.  Used by
 * programs like ipathstats to prपूर्णांक the stats in a way which works क्रम
 * dअगरferent versions of drivers, without changing program source.
 * अगर qlogic_ib_stats changes, this needs to change.  Names need to be
 * 12 अक्षरs or less (w/o newline), क्रम proper display by ipathstats utility.
 */
अटल स्थिर अक्षर qib_statnames[] =
	"KernIntr\n"
	"ErrorIntr\n"
	"Tx_Errs\n"
	"Rcv_Errs\n"
	"H/W_Errs\n"
	"NoPIOBufs\n"
	"CtxtsOpen\n"
	"RcvLen_Errs\n"
	"EgrBufFull\n"
	"EgrHdrFull\n"
	;

अटल sमाप_प्रकार driver_names_पढ़ो(काष्ठा file *file, अक्षर __user *buf,
				 माप_प्रकार count, loff_t *ppos)
अणु
	वापस simple_पढ़ो_from_buffer(buf, count, ppos, qib_statnames,
		माप(qib_statnames) - 1); /* no null */
पूर्ण

अटल स्थिर काष्ठा file_operations driver_ops[] = अणु
	अणु .पढ़ो = driver_stats_पढ़ो, .llseek = generic_file_llseek, पूर्ण,
	अणु .पढ़ो = driver_names_पढ़ो, .llseek = generic_file_llseek, पूर्ण,
पूर्ण;

/* पढ़ो the per-device counters */
अटल sमाप_प्रकार dev_counters_पढ़ो(काष्ठा file *file, अक्षर __user *buf,
				 माप_प्रकार count, loff_t *ppos)
अणु
	u64 *counters;
	माप_प्रकार avail;
	काष्ठा qib_devdata *dd = निजी2dd(file);

	avail = dd->f_पढ़ो_cntrs(dd, *ppos, शून्य, &counters);
	वापस simple_पढ़ो_from_buffer(buf, count, ppos, counters, avail);
पूर्ण

/* पढ़ो the per-device counters */
अटल sमाप_प्रकार dev_names_पढ़ो(काष्ठा file *file, अक्षर __user *buf,
			      माप_प्रकार count, loff_t *ppos)
अणु
	अक्षर *names;
	माप_प्रकार avail;
	काष्ठा qib_devdata *dd = निजी2dd(file);

	avail = dd->f_पढ़ो_cntrs(dd, *ppos, &names, शून्य);
	वापस simple_पढ़ो_from_buffer(buf, count, ppos, names, avail);
पूर्ण

अटल स्थिर काष्ठा file_operations cntr_ops[] = अणु
	अणु .पढ़ो = dev_counters_पढ़ो, .llseek = generic_file_llseek, पूर्ण,
	अणु .पढ़ो = dev_names_पढ़ो, .llseek = generic_file_llseek, पूर्ण,
पूर्ण;

/*
 * Could use file_inode(file)->i_ino to figure out which file,
 * instead of separate routine क्रम each, but क्रम now, this works...
 */

/* पढ़ो the per-port names (same क्रम each port) */
अटल sमाप_प्रकार portnames_पढ़ो(काष्ठा file *file, अक्षर __user *buf,
			      माप_प्रकार count, loff_t *ppos)
अणु
	अक्षर *names;
	माप_प्रकार avail;
	काष्ठा qib_devdata *dd = निजी2dd(file);

	avail = dd->f_पढ़ो_portcntrs(dd, *ppos, 0, &names, शून्य);
	वापस simple_पढ़ो_from_buffer(buf, count, ppos, names, avail);
पूर्ण

/* पढ़ो the per-port counters क्रम port 1 (pidx 0) */
अटल sमाप_प्रकार portcntrs_1_पढ़ो(काष्ठा file *file, अक्षर __user *buf,
				माप_प्रकार count, loff_t *ppos)
अणु
	u64 *counters;
	माप_प्रकार avail;
	काष्ठा qib_devdata *dd = निजी2dd(file);

	avail = dd->f_पढ़ो_portcntrs(dd, *ppos, 0, शून्य, &counters);
	वापस simple_पढ़ो_from_buffer(buf, count, ppos, counters, avail);
पूर्ण

/* पढ़ो the per-port counters क्रम port 2 (pidx 1) */
अटल sमाप_प्रकार portcntrs_2_पढ़ो(काष्ठा file *file, अक्षर __user *buf,
				माप_प्रकार count, loff_t *ppos)
अणु
	u64 *counters;
	माप_प्रकार avail;
	काष्ठा qib_devdata *dd = निजी2dd(file);

	avail = dd->f_पढ़ो_portcntrs(dd, *ppos, 1, शून्य, &counters);
	वापस simple_पढ़ो_from_buffer(buf, count, ppos, counters, avail);
पूर्ण

अटल स्थिर काष्ठा file_operations portcntr_ops[] = अणु
	अणु .पढ़ो = portnames_पढ़ो, .llseek = generic_file_llseek, पूर्ण,
	अणु .पढ़ो = portcntrs_1_पढ़ो, .llseek = generic_file_llseek, पूर्ण,
	अणु .पढ़ो = portcntrs_2_पढ़ो, .llseek = generic_file_llseek, पूर्ण,
पूर्ण;

/*
 * पढ़ो the per-port QSFP data क्रम port 1 (pidx 0)
 */
अटल sमाप_प्रकार qsfp_1_पढ़ो(काष्ठा file *file, अक्षर __user *buf,
			   माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा qib_devdata *dd = निजी2dd(file);
	अक्षर *पंचांगp;
	पूर्णांक ret;

	पंचांगp = kदो_स्मृति(PAGE_SIZE, GFP_KERNEL);
	अगर (!पंचांगp)
		वापस -ENOMEM;

	ret = qib_qsfp_dump(dd->pport, पंचांगp, PAGE_SIZE);
	अगर (ret > 0)
		ret = simple_पढ़ो_from_buffer(buf, count, ppos, पंचांगp, ret);
	kमुक्त(पंचांगp);
	वापस ret;
पूर्ण

/*
 * पढ़ो the per-port QSFP data क्रम port 2 (pidx 1)
 */
अटल sमाप_प्रकार qsfp_2_पढ़ो(काष्ठा file *file, अक्षर __user *buf,
			   माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा qib_devdata *dd = निजी2dd(file);
	अक्षर *पंचांगp;
	पूर्णांक ret;

	अगर (dd->num_pports < 2)
		वापस -ENODEV;

	पंचांगp = kदो_स्मृति(PAGE_SIZE, GFP_KERNEL);
	अगर (!पंचांगp)
		वापस -ENOMEM;

	ret = qib_qsfp_dump(dd->pport + 1, पंचांगp, PAGE_SIZE);
	अगर (ret > 0)
		ret = simple_पढ़ो_from_buffer(buf, count, ppos, पंचांगp, ret);
	kमुक्त(पंचांगp);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा file_operations qsfp_ops[] = अणु
	अणु .पढ़ो = qsfp_1_पढ़ो, .llseek = generic_file_llseek, पूर्ण,
	अणु .पढ़ो = qsfp_2_पढ़ो, .llseek = generic_file_llseek, पूर्ण,
पूर्ण;

अटल sमाप_प्रकार flash_पढ़ो(काष्ठा file *file, अक्षर __user *buf,
			  माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा qib_devdata *dd;
	sमाप_प्रकार ret;
	loff_t pos;
	अक्षर *पंचांगp;

	pos = *ppos;

	अगर (pos < 0) अणु
		ret = -EINVAL;
		जाओ bail;
	पूर्ण

	अगर (pos >= माप(काष्ठा qib_flash)) अणु
		ret = 0;
		जाओ bail;
	पूर्ण

	अगर (count > माप(काष्ठा qib_flash) - pos)
		count = माप(काष्ठा qib_flash) - pos;

	पंचांगp = kदो_स्मृति(count, GFP_KERNEL);
	अगर (!पंचांगp) अणु
		ret = -ENOMEM;
		जाओ bail;
	पूर्ण

	dd = निजी2dd(file);
	अगर (qib_eeprom_पढ़ो(dd, pos, पंचांगp, count)) अणु
		qib_dev_err(dd, "failed to read from flash\n");
		ret = -ENXIO;
		जाओ bail_पंचांगp;
	पूर्ण

	अगर (copy_to_user(buf, पंचांगp, count)) अणु
		ret = -EFAULT;
		जाओ bail_पंचांगp;
	पूर्ण

	*ppos = pos + count;
	ret = count;

bail_पंचांगp:
	kमुक्त(पंचांगp);

bail:
	वापस ret;
पूर्ण

अटल sमाप_प्रकार flash_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *buf,
			   माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा qib_devdata *dd;
	sमाप_प्रकार ret;
	loff_t pos;
	अक्षर *पंचांगp;

	pos = *ppos;

	अगर (pos != 0 || count != माप(काष्ठा qib_flash))
		वापस -EINVAL;

	पंचांगp = memdup_user(buf, count);
	अगर (IS_ERR(पंचांगp))
		वापस PTR_ERR(पंचांगp);

	dd = निजी2dd(file);
	अगर (qib_eeprom_ग_लिखो(dd, pos, पंचांगp, count)) अणु
		ret = -ENXIO;
		qib_dev_err(dd, "failed to write to flash\n");
		जाओ bail_पंचांगp;
	पूर्ण

	*ppos = pos + count;
	ret = count;

bail_पंचांगp:
	kमुक्त(पंचांगp);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा file_operations flash_ops = अणु
	.पढ़ो = flash_पढ़ो,
	.ग_लिखो = flash_ग_लिखो,
	.llseek = शेष_llseek,
पूर्ण;

अटल पूर्णांक add_cntr_files(काष्ठा super_block *sb, काष्ठा qib_devdata *dd)
अणु
	काष्ठा dentry *dir, *पंचांगp;
	अक्षर unit[10];
	पूर्णांक ret, i;

	/* create the per-unit directory */
	snम_लिखो(unit, माप(unit), "%u", dd->unit);
	ret = create_file(unit, S_IFसूची|S_IRUGO|S_IXUGO, sb->s_root, &dir,
			  &simple_dir_operations, dd);
	अगर (ret) अणु
		pr_err("create_file(%s) failed: %d\n", unit, ret);
		जाओ bail;
	पूर्ण

	/* create the files in the new directory */
	ret = create_file("counters", S_IFREG|S_IRUGO, dir, &पंचांगp,
			  &cntr_ops[0], dd);
	अगर (ret) अणु
		pr_err("create_file(%s/counters) failed: %d\n",
		       unit, ret);
		जाओ bail;
	पूर्ण
	ret = create_file("counter_names", S_IFREG|S_IRUGO, dir, &पंचांगp,
			  &cntr_ops[1], dd);
	अगर (ret) अणु
		pr_err("create_file(%s/counter_names) failed: %d\n",
		       unit, ret);
		जाओ bail;
	पूर्ण
	ret = create_file("portcounter_names", S_IFREG|S_IRUGO, dir, &पंचांगp,
			  &portcntr_ops[0], dd);
	अगर (ret) अणु
		pr_err("create_file(%s/%s) failed: %d\n",
		       unit, "portcounter_names", ret);
		जाओ bail;
	पूर्ण
	क्रम (i = 1; i <= dd->num_pports; i++) अणु
		अक्षर fname[24];

		प्र_लिखो(fname, "port%dcounters", i);
		/* create the files in the new directory */
		ret = create_file(fname, S_IFREG|S_IRUGO, dir, &पंचांगp,
				  &portcntr_ops[i], dd);
		अगर (ret) अणु
			pr_err("create_file(%s/%s) failed: %d\n",
				unit, fname, ret);
			जाओ bail;
		पूर्ण
		अगर (!(dd->flags & QIB_HAS_QSFP))
			जारी;
		प्र_लिखो(fname, "qsfp%d", i);
		ret = create_file(fname, S_IFREG|S_IRUGO, dir, &पंचांगp,
				  &qsfp_ops[i - 1], dd);
		अगर (ret) अणु
			pr_err("create_file(%s/%s) failed: %d\n",
				unit, fname, ret);
			जाओ bail;
		पूर्ण
	पूर्ण

	ret = create_file("flash", S_IFREG|S_IWUSR|S_IRUGO, dir, &पंचांगp,
			  &flash_ops, dd);
	अगर (ret)
		pr_err("create_file(%s/flash) failed: %d\n",
			unit, ret);
bail:
	वापस ret;
पूर्ण

अटल पूर्णांक हटाओ_device_files(काष्ठा super_block *sb,
			       काष्ठा qib_devdata *dd)
अणु
	काष्ठा dentry *dir;
	अक्षर unit[10];

	snम_लिखो(unit, माप(unit), "%u", dd->unit);
	dir = lookup_one_len_unlocked(unit, sb->s_root, म_माप(unit));

	अगर (IS_ERR(dir)) अणु
		pr_err("Lookup of %s failed\n", unit);
		वापस PTR_ERR(dir);
	पूर्ण
	simple_recursive_removal(dir, शून्य);
	वापस 0;
पूर्ण

/*
 * This fills everything in when the fs is mounted, to handle umount/mount
 * after device init.  The direct add_cntr_files() call handles adding
 * them from the init code, when the fs is alपढ़ोy mounted.
 */
अटल पूर्णांक qibfs_fill_super(काष्ठा super_block *sb, काष्ठा fs_context *fc)
अणु
	काष्ठा qib_devdata *dd;
	अचिन्हित दीर्घ index;
	पूर्णांक ret;

	अटल स्थिर काष्ठा tree_descr files[] = अणु
		[2] = अणु"driver_stats", &driver_ops[0], S_IRUGOपूर्ण,
		[3] = अणु"driver_stats_names", &driver_ops[1], S_IRUGOपूर्ण,
		अणु""पूर्ण,
	पूर्ण;

	ret = simple_fill_super(sb, QIBFS_MAGIC, files);
	अगर (ret) अणु
		pr_err("simple_fill_super failed: %d\n", ret);
		जाओ bail;
	पूर्ण

	xa_क्रम_each(&qib_dev_table, index, dd) अणु
		ret = add_cntr_files(sb, dd);
		अगर (ret)
			जाओ bail;
	पूर्ण

bail:
	वापस ret;
पूर्ण

अटल पूर्णांक qibfs_get_tree(काष्ठा fs_context *fc)
अणु
	पूर्णांक ret = get_tree_single(fc, qibfs_fill_super);
	अगर (ret == 0)
		qib_super = fc->root->d_sb;
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा fs_context_operations qibfs_context_ops = अणु
	.get_tree	= qibfs_get_tree,
पूर्ण;

अटल पूर्णांक qibfs_init_fs_context(काष्ठा fs_context *fc)
अणु
	fc->ops = &qibfs_context_ops;
	वापस 0;
पूर्ण

अटल व्योम qibfs_समाप्त_super(काष्ठा super_block *s)
अणु
	समाप्त_litter_super(s);
	qib_super = शून्य;
पूर्ण

पूर्णांक qibfs_add(काष्ठा qib_devdata *dd)
अणु
	पूर्णांक ret;

	/*
	 * On first unit initialized, qib_super will not yet exist
	 * because nobody has yet tried to mount the fileप्रणाली, so
	 * we can't consider that to be an error; अगर an error occurs
	 * during the mount, that will get a complaपूर्णांक, so this is OK.
	 * add_cntr_files() क्रम all units is करोne at mount from
	 * qibfs_fill_super(), so one way or another, everything works.
	 */
	अगर (qib_super == शून्य)
		ret = 0;
	अन्यथा
		ret = add_cntr_files(qib_super, dd);
	वापस ret;
पूर्ण

पूर्णांक qibfs_हटाओ(काष्ठा qib_devdata *dd)
अणु
	पूर्णांक ret = 0;

	अगर (qib_super)
		ret = हटाओ_device_files(qib_super, dd);

	वापस ret;
पूर्ण

अटल काष्ठा file_प्रणाली_type qibfs_fs_type = अणु
	.owner =        THIS_MODULE,
	.name =         "ipathfs",
	.init_fs_context = qibfs_init_fs_context,
	.समाप्त_sb =      qibfs_समाप्त_super,
पूर्ण;
MODULE_ALIAS_FS("ipathfs");

पूर्णांक __init qib_init_qibfs(व्योम)
अणु
	वापस रेजिस्टर_fileप्रणाली(&qibfs_fs_type);
पूर्ण

पूर्णांक __निकास qib_निकास_qibfs(व्योम)
अणु
	वापस unरेजिस्टर_fileप्रणाली(&qibfs_fs_type);
पूर्ण
