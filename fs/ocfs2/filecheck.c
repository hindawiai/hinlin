<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * filecheck.c
 *
 * Code which implements online file check.
 *
 * Copyright (C) 2016 SuSE.  All rights reserved.
 */

#समावेश <linux/list.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/kmod.h>
#समावेश <linux/fs.h>
#समावेश <linux/kobject.h>
#समावेश <linux/sysfs.h>
#समावेश <linux/sysctl.h>
#समावेश <cluster/masklog.h>

#समावेश "ocfs2.h"
#समावेश "ocfs2_fs.h"
#समावेश "stackglue.h"
#समावेश "inode.h"

#समावेश "filecheck.h"


/* File check error strings,
 * must correspond with error number in header file.
 */
अटल स्थिर अक्षर * स्थिर ocfs2_filecheck_errs[] = अणु
	"SUCCESS",
	"FAILED",
	"INPROGRESS",
	"READONLY",
	"INJBD",
	"INVALIDINO",
	"BLOCKECC",
	"BLOCKNO",
	"VALIDFLAG",
	"GENERATION",
	"UNSUPPORTED"
पूर्ण;

काष्ठा ocfs2_filecheck_entry अणु
	काष्ठा list_head fe_list;
	अचिन्हित दीर्घ fe_ino;
	अचिन्हित पूर्णांक fe_type;
	अचिन्हित पूर्णांक fe_करोne:1;
	अचिन्हित पूर्णांक fe_status:31;
पूर्ण;

काष्ठा ocfs2_filecheck_args अणु
	अचिन्हित पूर्णांक fa_type;
	जोड़ अणु
		अचिन्हित दीर्घ fa_ino;
		अचिन्हित पूर्णांक fa_len;
	पूर्ण;
पूर्ण;

अटल स्थिर अक्षर *
ocfs2_filecheck_error(पूर्णांक त्रुटि_सं)
अणु
	अगर (!त्रुटि_सं)
		वापस ocfs2_filecheck_errs[त्रुटि_सं];

	BUG_ON(त्रुटि_सं < OCFS2_खाताCHECK_ERR_START ||
	       त्रुटि_सं > OCFS2_खाताCHECK_ERR_END);
	वापस ocfs2_filecheck_errs[त्रुटि_सं - OCFS2_खाताCHECK_ERR_START + 1];
पूर्ण

अटल sमाप_प्रकार ocfs2_filecheck_attr_show(काष्ठा kobject *kobj,
					काष्ठा kobj_attribute *attr,
					अक्षर *buf);
अटल sमाप_प्रकार ocfs2_filecheck_attr_store(काष्ठा kobject *kobj,
					काष्ठा kobj_attribute *attr,
					स्थिर अक्षर *buf, माप_प्रकार count);
अटल काष्ठा kobj_attribute ocfs2_filecheck_attr_chk =
					__ATTR(check, S_IRUSR | S_IWUSR,
					ocfs2_filecheck_attr_show,
					ocfs2_filecheck_attr_store);
अटल काष्ठा kobj_attribute ocfs2_filecheck_attr_fix =
					__ATTR(fix, S_IRUSR | S_IWUSR,
					ocfs2_filecheck_attr_show,
					ocfs2_filecheck_attr_store);
अटल काष्ठा kobj_attribute ocfs2_filecheck_attr_set =
					__ATTR(set, S_IRUSR | S_IWUSR,
					ocfs2_filecheck_attr_show,
					ocfs2_filecheck_attr_store);
अटल काष्ठा attribute *ocfs2_filecheck_attrs[] = अणु
	&ocfs2_filecheck_attr_chk.attr,
	&ocfs2_filecheck_attr_fix.attr,
	&ocfs2_filecheck_attr_set.attr,
	शून्य
पूर्ण;

अटल व्योम ocfs2_filecheck_release(काष्ठा kobject *kobj)
अणु
	काष्ठा ocfs2_filecheck_sysfs_entry *entry = container_of(kobj,
				काष्ठा ocfs2_filecheck_sysfs_entry, fs_kobj);

	complete(&entry->fs_kobj_unरेजिस्टर);
पूर्ण

अटल sमाप_प्रकार
ocfs2_filecheck_show(काष्ठा kobject *kobj, काष्ठा attribute *attr, अक्षर *buf)
अणु
	sमाप_प्रकार ret = -EIO;
	काष्ठा kobj_attribute *kattr = container_of(attr,
					काष्ठा kobj_attribute, attr);

	kobject_get(kobj);
	अगर (kattr->show)
		ret = kattr->show(kobj, kattr, buf);
	kobject_put(kobj);
	वापस ret;
पूर्ण

अटल sमाप_प्रकार
ocfs2_filecheck_store(काष्ठा kobject *kobj, काष्ठा attribute *attr,
			स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	sमाप_प्रकार ret = -EIO;
	काष्ठा kobj_attribute *kattr = container_of(attr,
					काष्ठा kobj_attribute, attr);

	kobject_get(kobj);
	अगर (kattr->store)
		ret = kattr->store(kobj, kattr, buf, count);
	kobject_put(kobj);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा sysfs_ops ocfs2_filecheck_ops = अणु
	.show = ocfs2_filecheck_show,
	.store = ocfs2_filecheck_store,
पूर्ण;

अटल काष्ठा kobj_type ocfs2_ktype_filecheck = अणु
	.शेष_attrs = ocfs2_filecheck_attrs,
	.sysfs_ops = &ocfs2_filecheck_ops,
	.release = ocfs2_filecheck_release,
पूर्ण;

अटल व्योम
ocfs2_filecheck_sysfs_मुक्त(काष्ठा ocfs2_filecheck_sysfs_entry *entry)
अणु
	काष्ठा ocfs2_filecheck_entry *p;

	spin_lock(&entry->fs_fcheck->fc_lock);
	जबतक (!list_empty(&entry->fs_fcheck->fc_head)) अणु
		p = list_first_entry(&entry->fs_fcheck->fc_head,
				     काष्ठा ocfs2_filecheck_entry, fe_list);
		list_del(&p->fe_list);
		BUG_ON(!p->fe_करोne); /* To मुक्त a unकरोne file check entry */
		kमुक्त(p);
	पूर्ण
	spin_unlock(&entry->fs_fcheck->fc_lock);

	kमुक्त(entry->fs_fcheck);
	entry->fs_fcheck = शून्य;
पूर्ण

पूर्णांक ocfs2_filecheck_create_sysfs(काष्ठा ocfs2_super *osb)
अणु
	पूर्णांक ret;
	काष्ठा ocfs2_filecheck *fcheck;
	काष्ठा ocfs2_filecheck_sysfs_entry *entry = &osb->osb_fc_ent;

	fcheck = kदो_स्मृति(माप(काष्ठा ocfs2_filecheck), GFP_NOFS);
	अगर (!fcheck)
		वापस -ENOMEM;

	INIT_LIST_HEAD(&fcheck->fc_head);
	spin_lock_init(&fcheck->fc_lock);
	fcheck->fc_max = OCFS2_खाताCHECK_MINSIZE;
	fcheck->fc_size = 0;
	fcheck->fc_करोne = 0;

	entry->fs_kobj.kset = osb->osb_dev_kset;
	init_completion(&entry->fs_kobj_unरेजिस्टर);
	ret = kobject_init_and_add(&entry->fs_kobj, &ocfs2_ktype_filecheck,
					शून्य, "filecheck");
	अगर (ret) अणु
		kobject_put(&entry->fs_kobj);
		kमुक्त(fcheck);
		वापस ret;
	पूर्ण

	entry->fs_fcheck = fcheck;
	वापस 0;
पूर्ण

व्योम ocfs2_filecheck_हटाओ_sysfs(काष्ठा ocfs2_super *osb)
अणु
	अगर (!osb->osb_fc_ent.fs_fcheck)
		वापस;

	kobject_del(&osb->osb_fc_ent.fs_kobj);
	kobject_put(&osb->osb_fc_ent.fs_kobj);
	रुको_क्रम_completion(&osb->osb_fc_ent.fs_kobj_unरेजिस्टर);
	ocfs2_filecheck_sysfs_मुक्त(&osb->osb_fc_ent);
पूर्ण

अटल पूर्णांक
ocfs2_filecheck_erase_entries(काष्ठा ocfs2_filecheck_sysfs_entry *ent,
			      अचिन्हित पूर्णांक count);
अटल पूर्णांक
ocfs2_filecheck_adjust_max(काष्ठा ocfs2_filecheck_sysfs_entry *ent,
			   अचिन्हित पूर्णांक len)
अणु
	पूर्णांक ret;

	अगर ((len < OCFS2_खाताCHECK_MINSIZE) || (len > OCFS2_खाताCHECK_MAXSIZE))
		वापस -EINVAL;

	spin_lock(&ent->fs_fcheck->fc_lock);
	अगर (len < (ent->fs_fcheck->fc_size - ent->fs_fcheck->fc_करोne)) अणु
		mlog(ML_NOTICE,
		"Cannot set online file check maximum entry number "
		"to %u due to too many pending entries(%u)\n",
		len, ent->fs_fcheck->fc_size - ent->fs_fcheck->fc_करोne);
		ret = -EBUSY;
	पूर्ण अन्यथा अणु
		अगर (len < ent->fs_fcheck->fc_size)
			BUG_ON(!ocfs2_filecheck_erase_entries(ent,
				ent->fs_fcheck->fc_size - len));

		ent->fs_fcheck->fc_max = len;
		ret = 0;
	पूर्ण
	spin_unlock(&ent->fs_fcheck->fc_lock);

	वापस ret;
पूर्ण

#घोषणा OCFS2_खाताCHECK_ARGS_LEN	24
अटल पूर्णांक
ocfs2_filecheck_args_get_दीर्घ(स्थिर अक्षर *buf, माप_प्रकार count,
			      अचिन्हित दीर्घ *val)
अणु
	अक्षर buffer[OCFS2_खाताCHECK_ARGS_LEN];

	स_नकल(buffer, buf, count);
	buffer[count] = '\0';

	अगर (kम_से_अदीर्घ(buffer, 0, val))
		वापस 1;

	वापस 0;
पूर्ण

अटल पूर्णांक
ocfs2_filecheck_type_parse(स्थिर अक्षर *name, अचिन्हित पूर्णांक *type)
अणु
	अगर (!म_भेदन(name, "fix", 4))
		*type = OCFS2_खाताCHECK_TYPE_FIX;
	अन्यथा अगर (!म_भेदन(name, "check", 6))
		*type = OCFS2_खाताCHECK_TYPE_CHK;
	अन्यथा अगर (!म_भेदन(name, "set", 4))
		*type = OCFS2_खाताCHECK_TYPE_SET;
	अन्यथा
		वापस 1;

	वापस 0;
पूर्ण

अटल पूर्णांक
ocfs2_filecheck_args_parse(स्थिर अक्षर *name, स्थिर अक्षर *buf, माप_प्रकार count,
			   काष्ठा ocfs2_filecheck_args *args)
अणु
	अचिन्हित दीर्घ val = 0;
	अचिन्हित पूर्णांक type;

	/* too लघु/दीर्घ args length */
	अगर ((count < 1) || (count >= OCFS2_खाताCHECK_ARGS_LEN))
		वापस 1;

	अगर (ocfs2_filecheck_type_parse(name, &type))
		वापस 1;
	अगर (ocfs2_filecheck_args_get_दीर्घ(buf, count, &val))
		वापस 1;

	अगर (val <= 0)
		वापस 1;

	args->fa_type = type;
	अगर (type == OCFS2_खाताCHECK_TYPE_SET)
		args->fa_len = (अचिन्हित पूर्णांक)val;
	अन्यथा
		args->fa_ino = val;

	वापस 0;
पूर्ण

अटल sमाप_प्रकार ocfs2_filecheck_attr_show(काष्ठा kobject *kobj,
				    काष्ठा kobj_attribute *attr,
				    अक्षर *buf)
अणु

	sमाप_प्रकार ret = 0, total = 0, reमुख्य = PAGE_SIZE;
	अचिन्हित पूर्णांक type;
	काष्ठा ocfs2_filecheck_entry *p;
	काष्ठा ocfs2_filecheck_sysfs_entry *ent = container_of(kobj,
				काष्ठा ocfs2_filecheck_sysfs_entry, fs_kobj);

	अगर (ocfs2_filecheck_type_parse(attr->attr.name, &type))
		वापस -EINVAL;

	अगर (type == OCFS2_खाताCHECK_TYPE_SET) अणु
		spin_lock(&ent->fs_fcheck->fc_lock);
		total = snम_लिखो(buf, reमुख्य, "%u\n", ent->fs_fcheck->fc_max);
		spin_unlock(&ent->fs_fcheck->fc_lock);
		जाओ निकास;
	पूर्ण

	ret = snम_लिखो(buf, reमुख्य, "INO\t\tDONE\tERROR\n");
	total += ret;
	reमुख्य -= ret;
	spin_lock(&ent->fs_fcheck->fc_lock);
	list_क्रम_each_entry(p, &ent->fs_fcheck->fc_head, fe_list) अणु
		अगर (p->fe_type != type)
			जारी;

		ret = snम_लिखो(buf + total, reमुख्य, "%lu\t\t%u\t%s\n",
			       p->fe_ino, p->fe_करोne,
			       ocfs2_filecheck_error(p->fe_status));
		अगर (ret < 0) अणु
			total = ret;
			अवरोध;
		पूर्ण
		अगर (ret == reमुख्य) अणु
			/* snम_लिखो() didn't fit */
			total = -E2BIG;
			अवरोध;
		पूर्ण
		total += ret;
		reमुख्य -= ret;
	पूर्ण
	spin_unlock(&ent->fs_fcheck->fc_lock);

निकास:
	वापस total;
पूर्ण

अटल अंतरभूत पूर्णांक
ocfs2_filecheck_is_dup_entry(काष्ठा ocfs2_filecheck_sysfs_entry *ent,
				अचिन्हित दीर्घ ino)
अणु
	काष्ठा ocfs2_filecheck_entry *p;

	list_क्रम_each_entry(p, &ent->fs_fcheck->fc_head, fe_list) अणु
		अगर (!p->fe_करोne) अणु
			अगर (p->fe_ino == ino)
				वापस 1;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक
ocfs2_filecheck_erase_entry(काष्ठा ocfs2_filecheck_sysfs_entry *ent)
अणु
	काष्ठा ocfs2_filecheck_entry *p;

	list_क्रम_each_entry(p, &ent->fs_fcheck->fc_head, fe_list) अणु
		अगर (p->fe_करोne) अणु
			list_del(&p->fe_list);
			kमुक्त(p);
			ent->fs_fcheck->fc_size--;
			ent->fs_fcheck->fc_करोne--;
			वापस 1;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
ocfs2_filecheck_erase_entries(काष्ठा ocfs2_filecheck_sysfs_entry *ent,
			      अचिन्हित पूर्णांक count)
अणु
	अचिन्हित पूर्णांक i = 0;
	अचिन्हित पूर्णांक ret = 0;

	जबतक (i++ < count) अणु
		अगर (ocfs2_filecheck_erase_entry(ent))
			ret++;
		अन्यथा
			अवरोध;
	पूर्ण

	वापस (ret == count ? 1 : 0);
पूर्ण

अटल व्योम
ocfs2_filecheck_करोne_entry(काष्ठा ocfs2_filecheck_sysfs_entry *ent,
			   काष्ठा ocfs2_filecheck_entry *entry)
अणु
	spin_lock(&ent->fs_fcheck->fc_lock);
	entry->fe_करोne = 1;
	ent->fs_fcheck->fc_करोne++;
	spin_unlock(&ent->fs_fcheck->fc_lock);
पूर्ण

अटल अचिन्हित पूर्णांक
ocfs2_filecheck_handle(काष्ठा ocfs2_super *osb,
		       अचिन्हित दीर्घ ino, अचिन्हित पूर्णांक flags)
अणु
	अचिन्हित पूर्णांक ret = OCFS2_खाताCHECK_ERR_SUCCESS;
	काष्ठा inode *inode = शून्य;
	पूर्णांक rc;

	inode = ocfs2_iget(osb, ino, flags, 0);
	अगर (IS_ERR(inode)) अणु
		rc = (पूर्णांक)(-(दीर्घ)inode);
		अगर (rc >= OCFS2_खाताCHECK_ERR_START &&
		    rc < OCFS2_खाताCHECK_ERR_END)
			ret = rc;
		अन्यथा
			ret = OCFS2_खाताCHECK_ERR_FAILED;
	पूर्ण अन्यथा
		iput(inode);

	वापस ret;
पूर्ण

अटल व्योम
ocfs2_filecheck_handle_entry(काष्ठा ocfs2_filecheck_sysfs_entry *ent,
			     काष्ठा ocfs2_filecheck_entry *entry)
अणु
	काष्ठा ocfs2_super *osb = container_of(ent, काष्ठा ocfs2_super,
						osb_fc_ent);

	अगर (entry->fe_type == OCFS2_खाताCHECK_TYPE_CHK)
		entry->fe_status = ocfs2_filecheck_handle(osb,
				entry->fe_ino, OCFS2_FI_FLAG_खाताCHECK_CHK);
	अन्यथा अगर (entry->fe_type == OCFS2_खाताCHECK_TYPE_FIX)
		entry->fe_status = ocfs2_filecheck_handle(osb,
				entry->fe_ino, OCFS2_FI_FLAG_खाताCHECK_FIX);
	अन्यथा
		entry->fe_status = OCFS2_खाताCHECK_ERR_UNSUPPORTED;

	ocfs2_filecheck_करोne_entry(ent, entry);
पूर्ण

अटल sमाप_प्रकार ocfs2_filecheck_attr_store(काष्ठा kobject *kobj,
				     काष्ठा kobj_attribute *attr,
				     स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	sमाप_प्रकार ret = 0;
	काष्ठा ocfs2_filecheck_args args;
	काष्ठा ocfs2_filecheck_entry *entry;
	काष्ठा ocfs2_filecheck_sysfs_entry *ent = container_of(kobj,
				काष्ठा ocfs2_filecheck_sysfs_entry, fs_kobj);

	अगर (count == 0)
		वापस count;

	अगर (ocfs2_filecheck_args_parse(attr->attr.name, buf, count, &args))
		वापस -EINVAL;

	अगर (args.fa_type == OCFS2_खाताCHECK_TYPE_SET) अणु
		ret = ocfs2_filecheck_adjust_max(ent, args.fa_len);
		जाओ निकास;
	पूर्ण

	entry = kदो_स्मृति(माप(काष्ठा ocfs2_filecheck_entry), GFP_NOFS);
	अगर (!entry) अणु
		ret = -ENOMEM;
		जाओ निकास;
	पूर्ण

	spin_lock(&ent->fs_fcheck->fc_lock);
	अगर (ocfs2_filecheck_is_dup_entry(ent, args.fa_ino)) अणु
		ret = -EEXIST;
		kमुक्त(entry);
	पूर्ण अन्यथा अगर ((ent->fs_fcheck->fc_size >= ent->fs_fcheck->fc_max) &&
		(ent->fs_fcheck->fc_करोne == 0)) अणु
		mlog(ML_NOTICE,
		"Cannot do more file check "
		"since file check queue(%u) is full now\n",
		ent->fs_fcheck->fc_max);
		ret = -EAGAIN;
		kमुक्त(entry);
	पूर्ण अन्यथा अणु
		अगर ((ent->fs_fcheck->fc_size >= ent->fs_fcheck->fc_max) &&
		    (ent->fs_fcheck->fc_करोne > 0)) अणु
			/* Delete the oldest entry which was करोne,
			 * make sure the entry size in list करोes
			 * not exceed maximum value
			 */
			BUG_ON(!ocfs2_filecheck_erase_entry(ent));
		पूर्ण

		entry->fe_ino = args.fa_ino;
		entry->fe_type = args.fa_type;
		entry->fe_करोne = 0;
		entry->fe_status = OCFS2_खाताCHECK_ERR_INPROGRESS;
		list_add_tail(&entry->fe_list, &ent->fs_fcheck->fc_head);
		ent->fs_fcheck->fc_size++;
	पूर्ण
	spin_unlock(&ent->fs_fcheck->fc_lock);

	अगर (!ret)
		ocfs2_filecheck_handle_entry(ent, entry);

निकास:
	वापस (!ret ? count : ret);
पूर्ण
