<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* Updated: Karl MacMillan <kmacmillan@tresys.com>
 *
 *	Added conditional policy language extensions
 *
 *  Updated: Hewlett-Packard <paul@paul-moore.com>
 *
 *	Added support क्रम the policy capability biपंचांगap
 *
 * Copyright (C) 2007 Hewlett-Packard Development Company, L.P.
 * Copyright (C) 2003 - 2004 Tresys Technology, LLC
 * Copyright (C) 2004 Red Hat, Inc., James Morris <jmorris@redhat.com>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/slab.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/fs.h>
#समावेश <linux/fs_context.h>
#समावेश <linux/mount.h>
#समावेश <linux/mutex.h>
#समावेश <linux/namei.h>
#समावेश <linux/init.h>
#समावेश <linux/माला.स>
#समावेश <linux/security.h>
#समावेश <linux/major.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/percpu.h>
#समावेश <linux/audit.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/kobject.h>
#समावेश <linux/प्रकार.स>

/* selinuxfs pseuकरो fileप्रणाली क्रम exporting the security policy API.
   Based on the proc code and the fs/nfsd/nfsctl.c code. */

#समावेश "flask.h"
#समावेश "avc.h"
#समावेश "avc_ss.h"
#समावेश "security.h"
#समावेश "objsec.h"
#समावेश "conditional.h"
#समावेश "ima.h"

क्रमागत sel_inos अणु
	SEL_ROOT_INO = 2,
	SEL_LOAD,	/* load policy */
	SEL_ENFORCE,	/* get or set enक्रमcing status */
	SEL_CONTEXT,	/* validate context */
	SEL_ACCESS,	/* compute access decision */
	SEL_CREATE,	/* compute create labeling decision */
	SEL_RELABEL,	/* compute relabeling decision */
	SEL_USER,	/* compute reachable user contexts */
	SEL_POLICYVERS,	/* वापस policy version क्रम this kernel */
	SEL_COMMIT_BOOLS, /* commit new boolean values */
	SEL_MLS,	/* वापस अगर MLS policy is enabled */
	SEL_DISABLE,	/* disable SELinux until next reboot */
	SEL_MEMBER,	/* compute polyinstantiation membership decision */
	SEL_CHECKREQPROT, /* check requested protection, not kernel-applied one */
	SEL_COMPAT_NET,	/* whether to use old compat network packet controls */
	SEL_REJECT_UNKNOWN, /* export unknown reject handling to userspace */
	SEL_DENY_UNKNOWN, /* export unknown deny handling to userspace */
	SEL_STATUS,	/* export current status using mmap() */
	SEL_POLICY,	/* allow userspace to पढ़ो the in kernel policy */
	SEL_VALIDATE_TRANS, /* compute validatetrans decision */
	SEL_INO_NEXT,	/* The next inode number to use */
पूर्ण;

काष्ठा selinux_fs_info अणु
	काष्ठा dentry *bool_dir;
	अचिन्हित पूर्णांक bool_num;
	अक्षर **bool_pending_names;
	अचिन्हित पूर्णांक *bool_pending_values;
	काष्ठा dentry *class_dir;
	अचिन्हित दीर्घ last_class_ino;
	bool policy_खोलोed;
	काष्ठा dentry *policycap_dir;
	अचिन्हित दीर्घ last_ino;
	काष्ठा selinux_state *state;
	काष्ठा super_block *sb;
पूर्ण;

अटल पूर्णांक selinux_fs_info_create(काष्ठा super_block *sb)
अणु
	काष्ठा selinux_fs_info *fsi;

	fsi = kzalloc(माप(*fsi), GFP_KERNEL);
	अगर (!fsi)
		वापस -ENOMEM;

	fsi->last_ino = SEL_INO_NEXT - 1;
	fsi->state = &selinux_state;
	fsi->sb = sb;
	sb->s_fs_info = fsi;
	वापस 0;
पूर्ण

अटल व्योम selinux_fs_info_मुक्त(काष्ठा super_block *sb)
अणु
	काष्ठा selinux_fs_info *fsi = sb->s_fs_info;
	पूर्णांक i;

	अगर (fsi) अणु
		क्रम (i = 0; i < fsi->bool_num; i++)
			kमुक्त(fsi->bool_pending_names[i]);
		kमुक्त(fsi->bool_pending_names);
		kमुक्त(fsi->bool_pending_values);
	पूर्ण
	kमुक्त(sb->s_fs_info);
	sb->s_fs_info = शून्य;
पूर्ण

#घोषणा SEL_INITCON_INO_OFFSET		0x01000000
#घोषणा SEL_BOOL_INO_OFFSET		0x02000000
#घोषणा SEL_CLASS_INO_OFFSET		0x04000000
#घोषणा SEL_POLICYCAP_INO_OFFSET	0x08000000
#घोषणा SEL_INO_MASK			0x00ffffff

#घोषणा BOOL_सूची_NAME "booleans"
#घोषणा CLASS_सूची_NAME "class"
#घोषणा POLICYCAP_सूची_NAME "policy_capabilities"

#घोषणा TMPBUFLEN	12
अटल sमाप_प्रकार sel_पढ़ो_enक्रमce(काष्ठा file *filp, अक्षर __user *buf,
				माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा selinux_fs_info *fsi = file_inode(filp)->i_sb->s_fs_info;
	अक्षर पंचांगpbuf[TMPBUFLEN];
	sमाप_प्रकार length;

	length = scnम_लिखो(पंचांगpbuf, TMPBUFLEN, "%d",
			   enक्रमcing_enabled(fsi->state));
	वापस simple_पढ़ो_from_buffer(buf, count, ppos, पंचांगpbuf, length);
पूर्ण

#अगर_घोषित CONFIG_SECURITY_SELINUX_DEVELOP
अटल sमाप_प्रकार sel_ग_लिखो_enक्रमce(काष्ठा file *file, स्थिर अक्षर __user *buf,
				 माप_प्रकार count, loff_t *ppos)

अणु
	काष्ठा selinux_fs_info *fsi = file_inode(file)->i_sb->s_fs_info;
	काष्ठा selinux_state *state = fsi->state;
	अक्षर *page = शून्य;
	sमाप_प्रकार length;
	पूर्णांक old_value, new_value;

	अगर (count >= PAGE_SIZE)
		वापस -ENOMEM;

	/* No partial ग_लिखोs. */
	अगर (*ppos != 0)
		वापस -EINVAL;

	page = memdup_user_nul(buf, count);
	अगर (IS_ERR(page))
		वापस PTR_ERR(page);

	length = -EINVAL;
	अगर (माला_पूछो(page, "%d", &new_value) != 1)
		जाओ out;

	new_value = !!new_value;

	old_value = enक्रमcing_enabled(state);
	अगर (new_value != old_value) अणु
		length = avc_has_perm(&selinux_state,
				      current_sid(), SECINITSID_SECURITY,
				      SECCLASS_SECURITY, SECURITY__SETENFORCE,
				      शून्य);
		अगर (length)
			जाओ out;
		audit_log(audit_context(), GFP_KERNEL, AUDIT_MAC_STATUS,
			"enforcing=%d old_enforcing=%d auid=%u ses=%u"
			" enabled=1 old-enabled=1 lsm=selinux res=1",
			new_value, old_value,
			from_kuid(&init_user_ns, audit_get_loginuid(current)),
			audit_get_sessionid(current));
		enक्रमcing_set(state, new_value);
		अगर (new_value)
			avc_ss_reset(state->avc, 0);
		selnl_notअगरy_setenक्रमce(new_value);
		selinux_status_update_setenक्रमce(state, new_value);
		अगर (!new_value)
			call_blocking_lsm_notअगरier(LSM_POLICY_CHANGE, शून्य);

		selinux_ima_measure_state(state);
	पूर्ण
	length = count;
out:
	kमुक्त(page);
	वापस length;
पूर्ण
#अन्यथा
#घोषणा sel_ग_लिखो_enक्रमce शून्य
#पूर्ण_अगर

अटल स्थिर काष्ठा file_operations sel_enक्रमce_ops = अणु
	.पढ़ो		= sel_पढ़ो_enक्रमce,
	.ग_लिखो		= sel_ग_लिखो_enक्रमce,
	.llseek		= generic_file_llseek,
पूर्ण;

अटल sमाप_प्रकार sel_पढ़ो_handle_unknown(काष्ठा file *filp, अक्षर __user *buf,
					माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा selinux_fs_info *fsi = file_inode(filp)->i_sb->s_fs_info;
	काष्ठा selinux_state *state = fsi->state;
	अक्षर पंचांगpbuf[TMPBUFLEN];
	sमाप_प्रकार length;
	ino_t ino = file_inode(filp)->i_ino;
	पूर्णांक handle_unknown = (ino == SEL_REJECT_UNKNOWN) ?
		security_get_reject_unknown(state) :
		!security_get_allow_unknown(state);

	length = scnम_लिखो(पंचांगpbuf, TMPBUFLEN, "%d", handle_unknown);
	वापस simple_पढ़ो_from_buffer(buf, count, ppos, पंचांगpbuf, length);
पूर्ण

अटल स्थिर काष्ठा file_operations sel_handle_unknown_ops = अणु
	.पढ़ो		= sel_पढ़ो_handle_unknown,
	.llseek		= generic_file_llseek,
पूर्ण;

अटल पूर्णांक sel_खोलो_handle_status(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	काष्ठा selinux_fs_info *fsi = file_inode(filp)->i_sb->s_fs_info;
	काष्ठा page    *status = selinux_kernel_status_page(fsi->state);

	अगर (!status)
		वापस -ENOMEM;

	filp->निजी_data = status;

	वापस 0;
पूर्ण

अटल sमाप_प्रकार sel_पढ़ो_handle_status(काष्ठा file *filp, अक्षर __user *buf,
				      माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा page    *status = filp->निजी_data;

	BUG_ON(!status);

	वापस simple_पढ़ो_from_buffer(buf, count, ppos,
				       page_address(status),
				       माप(काष्ठा selinux_kernel_status));
पूर्ण

अटल पूर्णांक sel_mmap_handle_status(काष्ठा file *filp,
				  काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा page    *status = filp->निजी_data;
	अचिन्हित दीर्घ	size = vma->vm_end - vma->vm_start;

	BUG_ON(!status);

	/* only allows one page from the head */
	अगर (vma->vm_pgoff > 0 || size != PAGE_SIZE)
		वापस -EIO;
	/* disallow writable mapping */
	अगर (vma->vm_flags & VM_WRITE)
		वापस -EPERM;
	/* disallow mprotect() turns it पूर्णांकo writable */
	vma->vm_flags &= ~VM_MAYWRITE;

	वापस remap_pfn_range(vma, vma->vm_start,
			       page_to_pfn(status),
			       size, vma->vm_page_prot);
पूर्ण

अटल स्थिर काष्ठा file_operations sel_handle_status_ops = अणु
	.खोलो		= sel_खोलो_handle_status,
	.पढ़ो		= sel_पढ़ो_handle_status,
	.mmap		= sel_mmap_handle_status,
	.llseek		= generic_file_llseek,
पूर्ण;

#अगर_घोषित CONFIG_SECURITY_SELINUX_DISABLE
अटल sमाप_प्रकार sel_ग_लिखो_disable(काष्ठा file *file, स्थिर अक्षर __user *buf,
				 माप_प्रकार count, loff_t *ppos)

अणु
	काष्ठा selinux_fs_info *fsi = file_inode(file)->i_sb->s_fs_info;
	अक्षर *page;
	sमाप_प्रकार length;
	पूर्णांक new_value;
	पूर्णांक enक्रमcing;

	/* NOTE: we are now officially considering runसमय disable as
	 *       deprecated, and using it will become increasingly painful
	 *       (e.g. sleeping/blocking) as we progress through future
	 *       kernel releases until eventually it is हटाओd
	 */
	pr_err("SELinux:  Runtime disable is deprecated, use selinux=0 on the kernel cmdline.\n");

	अगर (count >= PAGE_SIZE)
		वापस -ENOMEM;

	/* No partial ग_लिखोs. */
	अगर (*ppos != 0)
		वापस -EINVAL;

	page = memdup_user_nul(buf, count);
	अगर (IS_ERR(page))
		वापस PTR_ERR(page);

	length = -EINVAL;
	अगर (माला_पूछो(page, "%d", &new_value) != 1)
		जाओ out;

	अगर (new_value) अणु
		enक्रमcing = enक्रमcing_enabled(fsi->state);
		length = selinux_disable(fsi->state);
		अगर (length)
			जाओ out;
		audit_log(audit_context(), GFP_KERNEL, AUDIT_MAC_STATUS,
			"enforcing=%d old_enforcing=%d auid=%u ses=%u"
			" enabled=0 old-enabled=1 lsm=selinux res=1",
			enक्रमcing, enक्रमcing,
			from_kuid(&init_user_ns, audit_get_loginuid(current)),
			audit_get_sessionid(current));
	पूर्ण

	length = count;
out:
	kमुक्त(page);
	वापस length;
पूर्ण
#अन्यथा
#घोषणा sel_ग_लिखो_disable शून्य
#पूर्ण_अगर

अटल स्थिर काष्ठा file_operations sel_disable_ops = अणु
	.ग_लिखो		= sel_ग_लिखो_disable,
	.llseek		= generic_file_llseek,
पूर्ण;

अटल sमाप_प्रकार sel_पढ़ो_policyvers(काष्ठा file *filp, अक्षर __user *buf,
				   माप_प्रकार count, loff_t *ppos)
अणु
	अक्षर पंचांगpbuf[TMPBUFLEN];
	sमाप_प्रकार length;

	length = scnम_लिखो(पंचांगpbuf, TMPBUFLEN, "%u", POLICYDB_VERSION_MAX);
	वापस simple_पढ़ो_from_buffer(buf, count, ppos, पंचांगpbuf, length);
पूर्ण

अटल स्थिर काष्ठा file_operations sel_policyvers_ops = अणु
	.पढ़ो		= sel_पढ़ो_policyvers,
	.llseek		= generic_file_llseek,
पूर्ण;

/* declaration क्रम sel_ग_लिखो_load */
अटल पूर्णांक sel_make_bools(काष्ठा selinux_policy *newpolicy, काष्ठा dentry *bool_dir,
			  अचिन्हित पूर्णांक *bool_num, अक्षर ***bool_pending_names,
			  अचिन्हित पूर्णांक **bool_pending_values);
अटल पूर्णांक sel_make_classes(काष्ठा selinux_policy *newpolicy,
			    काष्ठा dentry *class_dir,
			    अचिन्हित दीर्घ *last_class_ino);

/* declaration क्रम sel_make_class_dirs */
अटल काष्ठा dentry *sel_make_dir(काष्ठा dentry *dir, स्थिर अक्षर *name,
			अचिन्हित दीर्घ *ino);

/* declaration क्रम sel_make_policy_nodes */
अटल काष्ठा dentry *sel_make_disconnected_dir(काष्ठा super_block *sb,
						अचिन्हित दीर्घ *ino);

/* declaration क्रम sel_make_policy_nodes */
अटल व्योम sel_हटाओ_entries(काष्ठा dentry *de);

अटल sमाप_प्रकार sel_पढ़ो_mls(काष्ठा file *filp, अक्षर __user *buf,
				माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा selinux_fs_info *fsi = file_inode(filp)->i_sb->s_fs_info;
	अक्षर पंचांगpbuf[TMPBUFLEN];
	sमाप_प्रकार length;

	length = scnम_लिखो(पंचांगpbuf, TMPBUFLEN, "%d",
			   security_mls_enabled(fsi->state));
	वापस simple_पढ़ो_from_buffer(buf, count, ppos, पंचांगpbuf, length);
पूर्ण

अटल स्थिर काष्ठा file_operations sel_mls_ops = अणु
	.पढ़ो		= sel_पढ़ो_mls,
	.llseek		= generic_file_llseek,
पूर्ण;

काष्ठा policy_load_memory अणु
	माप_प्रकार len;
	व्योम *data;
पूर्ण;

अटल पूर्णांक sel_खोलो_policy(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	काष्ठा selinux_fs_info *fsi = inode->i_sb->s_fs_info;
	काष्ठा selinux_state *state = fsi->state;
	काष्ठा policy_load_memory *plm = शून्य;
	पूर्णांक rc;

	BUG_ON(filp->निजी_data);

	mutex_lock(&fsi->state->policy_mutex);

	rc = avc_has_perm(&selinux_state,
			  current_sid(), SECINITSID_SECURITY,
			  SECCLASS_SECURITY, SECURITY__READ_POLICY, शून्य);
	अगर (rc)
		जाओ err;

	rc = -EBUSY;
	अगर (fsi->policy_खोलोed)
		जाओ err;

	rc = -ENOMEM;
	plm = kzalloc(माप(*plm), GFP_KERNEL);
	अगर (!plm)
		जाओ err;

	rc = security_पढ़ो_policy(state, &plm->data, &plm->len);
	अगर (rc)
		जाओ err;

	अगर ((माप_प्रकार)i_size_पढ़ो(inode) != plm->len) अणु
		inode_lock(inode);
		i_size_ग_लिखो(inode, plm->len);
		inode_unlock(inode);
	पूर्ण

	fsi->policy_खोलोed = 1;

	filp->निजी_data = plm;

	mutex_unlock(&fsi->state->policy_mutex);

	वापस 0;
err:
	mutex_unlock(&fsi->state->policy_mutex);

	अगर (plm)
		vमुक्त(plm->data);
	kमुक्त(plm);
	वापस rc;
पूर्ण

अटल पूर्णांक sel_release_policy(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	काष्ठा selinux_fs_info *fsi = inode->i_sb->s_fs_info;
	काष्ठा policy_load_memory *plm = filp->निजी_data;

	BUG_ON(!plm);

	fsi->policy_खोलोed = 0;

	vमुक्त(plm->data);
	kमुक्त(plm);

	वापस 0;
पूर्ण

अटल sमाप_प्रकार sel_पढ़ो_policy(काष्ठा file *filp, अक्षर __user *buf,
			       माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा policy_load_memory *plm = filp->निजी_data;
	पूर्णांक ret;

	ret = avc_has_perm(&selinux_state,
			   current_sid(), SECINITSID_SECURITY,
			  SECCLASS_SECURITY, SECURITY__READ_POLICY, शून्य);
	अगर (ret)
		वापस ret;

	वापस simple_पढ़ो_from_buffer(buf, count, ppos, plm->data, plm->len);
पूर्ण

अटल vm_fault_t sel_mmap_policy_fault(काष्ठा vm_fault *vmf)
अणु
	काष्ठा policy_load_memory *plm = vmf->vma->vm_file->निजी_data;
	अचिन्हित दीर्घ offset;
	काष्ठा page *page;

	अगर (vmf->flags & (FAULT_FLAG_MKWRITE | FAULT_FLAG_WRITE))
		वापस VM_FAULT_SIGBUS;

	offset = vmf->pgoff << PAGE_SHIFT;
	अगर (offset >= roundup(plm->len, PAGE_SIZE))
		वापस VM_FAULT_SIGBUS;

	page = vदो_स्मृति_to_page(plm->data + offset);
	get_page(page);

	vmf->page = page;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा vm_operations_काष्ठा sel_mmap_policy_ops = अणु
	.fault = sel_mmap_policy_fault,
	.page_mkग_लिखो = sel_mmap_policy_fault,
पूर्ण;

अटल पूर्णांक sel_mmap_policy(काष्ठा file *filp, काष्ठा vm_area_काष्ठा *vma)
अणु
	अगर (vma->vm_flags & VM_SHARED) अणु
		/* करो not allow mprotect to make mapping writable */
		vma->vm_flags &= ~VM_MAYWRITE;

		अगर (vma->vm_flags & VM_WRITE)
			वापस -EACCES;
	पूर्ण

	vma->vm_flags |= VM_DONTEXPAND | VM_DONTDUMP;
	vma->vm_ops = &sel_mmap_policy_ops;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा file_operations sel_policy_ops = अणु
	.खोलो		= sel_खोलो_policy,
	.पढ़ो		= sel_पढ़ो_policy,
	.mmap		= sel_mmap_policy,
	.release	= sel_release_policy,
	.llseek		= generic_file_llseek,
पूर्ण;

अटल व्योम sel_हटाओ_old_bool_data(अचिन्हित पूर्णांक bool_num, अक्षर **bool_names,
				अचिन्हित पूर्णांक *bool_values)
अणु
	u32 i;

	/* bool_dir cleanup */
	क्रम (i = 0; i < bool_num; i++)
		kमुक्त(bool_names[i]);
	kमुक्त(bool_names);
	kमुक्त(bool_values);
पूर्ण

अटल पूर्णांक sel_make_policy_nodes(काष्ठा selinux_fs_info *fsi,
				काष्ठा selinux_policy *newpolicy)
अणु
	पूर्णांक ret = 0;
	काष्ठा dentry *पंचांगp_parent, *पंचांगp_bool_dir, *पंचांगp_class_dir, *old_dentry;
	अचिन्हित पूर्णांक पंचांगp_bool_num, old_bool_num;
	अक्षर **पंचांगp_bool_names, **old_bool_names;
	अचिन्हित पूर्णांक *पंचांगp_bool_values, *old_bool_values;
	अचिन्हित दीर्घ पंचांगp_ino = fsi->last_ino; /* Don't increment last_ino in this function */

	पंचांगp_parent = sel_make_disconnected_dir(fsi->sb, &पंचांगp_ino);
	अगर (IS_ERR(पंचांगp_parent))
		वापस PTR_ERR(पंचांगp_parent);

	पंचांगp_ino = fsi->bool_dir->d_inode->i_ino - 1; /* sel_make_dir will increment and set */
	पंचांगp_bool_dir = sel_make_dir(पंचांगp_parent, BOOL_सूची_NAME, &पंचांगp_ino);
	अगर (IS_ERR(पंचांगp_bool_dir)) अणु
		ret = PTR_ERR(पंचांगp_bool_dir);
		जाओ out;
	पूर्ण

	पंचांगp_ino = fsi->class_dir->d_inode->i_ino - 1; /* sel_make_dir will increment and set */
	पंचांगp_class_dir = sel_make_dir(पंचांगp_parent, CLASS_सूची_NAME, &पंचांगp_ino);
	अगर (IS_ERR(पंचांगp_class_dir)) अणु
		ret = PTR_ERR(पंचांगp_class_dir);
		जाओ out;
	पूर्ण

	ret = sel_make_bools(newpolicy, पंचांगp_bool_dir, &पंचांगp_bool_num,
			     &पंचांगp_bool_names, &पंचांगp_bool_values);
	अगर (ret)
		जाओ out;

	ret = sel_make_classes(newpolicy, पंचांगp_class_dir,
			       &fsi->last_class_ino);
	अगर (ret)
		जाओ out;

	/* booleans */
	old_dentry = fsi->bool_dir;
	lock_नाम(पंचांगp_bool_dir, old_dentry);
	d_exchange(पंचांगp_bool_dir, fsi->bool_dir);

	old_bool_num = fsi->bool_num;
	old_bool_names = fsi->bool_pending_names;
	old_bool_values = fsi->bool_pending_values;

	fsi->bool_num = पंचांगp_bool_num;
	fsi->bool_pending_names = पंचांगp_bool_names;
	fsi->bool_pending_values = पंचांगp_bool_values;

	sel_हटाओ_old_bool_data(old_bool_num, old_bool_names, old_bool_values);

	fsi->bool_dir = पंचांगp_bool_dir;
	unlock_नाम(पंचांगp_bool_dir, old_dentry);

	/* classes */
	old_dentry = fsi->class_dir;
	lock_नाम(पंचांगp_class_dir, old_dentry);
	d_exchange(पंचांगp_class_dir, fsi->class_dir);
	fsi->class_dir = पंचांगp_class_dir;
	unlock_नाम(पंचांगp_class_dir, old_dentry);

out:
	/* Since the other temporary dirs are children of पंचांगp_parent
	 * this will handle all the cleanup in the हाल of a failure beक्रमe
	 * the swapover
	 */
	sel_हटाओ_entries(पंचांगp_parent);
	dput(पंचांगp_parent); /* d_genocide() only handles the children */

	वापस ret;
पूर्ण

अटल sमाप_प्रकार sel_ग_लिखो_load(काष्ठा file *file, स्थिर अक्षर __user *buf,
			      माप_प्रकार count, loff_t *ppos)

अणु
	काष्ठा selinux_fs_info *fsi = file_inode(file)->i_sb->s_fs_info;
	काष्ठा selinux_load_state load_state;
	sमाप_प्रकार length;
	व्योम *data = शून्य;

	mutex_lock(&fsi->state->policy_mutex);

	length = avc_has_perm(&selinux_state,
			      current_sid(), SECINITSID_SECURITY,
			      SECCLASS_SECURITY, SECURITY__LOAD_POLICY, शून्य);
	अगर (length)
		जाओ out;

	/* No partial ग_लिखोs. */
	length = -EINVAL;
	अगर (*ppos != 0)
		जाओ out;

	length = -ENOMEM;
	data = vदो_स्मृति(count);
	अगर (!data)
		जाओ out;

	length = -EFAULT;
	अगर (copy_from_user(data, buf, count) != 0)
		जाओ out;

	length = security_load_policy(fsi->state, data, count, &load_state);
	अगर (length) अणु
		pr_warn_ratelimited("SELinux: failed to load policy\n");
		जाओ out;
	पूर्ण

	length = sel_make_policy_nodes(fsi, load_state.policy);
	अगर (length) अणु
		pr_warn_ratelimited("SELinux: failed to initialize selinuxfs\n");
		selinux_policy_cancel(fsi->state, &load_state);
		जाओ out;
	पूर्ण

	selinux_policy_commit(fsi->state, &load_state);

	length = count;

	audit_log(audit_context(), GFP_KERNEL, AUDIT_MAC_POLICY_LOAD,
		"auid=%u ses=%u lsm=selinux res=1",
		from_kuid(&init_user_ns, audit_get_loginuid(current)),
		audit_get_sessionid(current));
out:
	mutex_unlock(&fsi->state->policy_mutex);
	vमुक्त(data);
	वापस length;
पूर्ण

अटल स्थिर काष्ठा file_operations sel_load_ops = अणु
	.ग_लिखो		= sel_ग_लिखो_load,
	.llseek		= generic_file_llseek,
पूर्ण;

अटल sमाप_प्रकार sel_ग_लिखो_context(काष्ठा file *file, अक्षर *buf, माप_प्रकार size)
अणु
	काष्ठा selinux_fs_info *fsi = file_inode(file)->i_sb->s_fs_info;
	काष्ठा selinux_state *state = fsi->state;
	अक्षर *canon = शून्य;
	u32 sid, len;
	sमाप_प्रकार length;

	length = avc_has_perm(&selinux_state,
			      current_sid(), SECINITSID_SECURITY,
			      SECCLASS_SECURITY, SECURITY__CHECK_CONTEXT, शून्य);
	अगर (length)
		जाओ out;

	length = security_context_to_sid(state, buf, size, &sid, GFP_KERNEL);
	अगर (length)
		जाओ out;

	length = security_sid_to_context(state, sid, &canon, &len);
	अगर (length)
		जाओ out;

	length = -दुस्फल;
	अगर (len > SIMPLE_TRANSACTION_LIMIT) अणु
		pr_err("SELinux: %s:  context size (%u) exceeds "
			"payload max\n", __func__, len);
		जाओ out;
	पूर्ण

	स_नकल(buf, canon, len);
	length = len;
out:
	kमुक्त(canon);
	वापस length;
पूर्ण

अटल sमाप_प्रकार sel_पढ़ो_checkreqprot(काष्ठा file *filp, अक्षर __user *buf,
				     माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा selinux_fs_info *fsi = file_inode(filp)->i_sb->s_fs_info;
	अक्षर पंचांगpbuf[TMPBUFLEN];
	sमाप_प्रकार length;

	length = scnम_लिखो(पंचांगpbuf, TMPBUFLEN, "%u",
			   checkreqprot_get(fsi->state));
	वापस simple_पढ़ो_from_buffer(buf, count, ppos, पंचांगpbuf, length);
पूर्ण

अटल sमाप_प्रकार sel_ग_लिखो_checkreqprot(काष्ठा file *file, स्थिर अक्षर __user *buf,
				      माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा selinux_fs_info *fsi = file_inode(file)->i_sb->s_fs_info;
	अक्षर *page;
	sमाप_प्रकार length;
	अचिन्हित पूर्णांक new_value;

	length = avc_has_perm(&selinux_state,
			      current_sid(), SECINITSID_SECURITY,
			      SECCLASS_SECURITY, SECURITY__SETCHECKREQPROT,
			      शून्य);
	अगर (length)
		वापस length;

	अगर (count >= PAGE_SIZE)
		वापस -ENOMEM;

	/* No partial ग_लिखोs. */
	अगर (*ppos != 0)
		वापस -EINVAL;

	page = memdup_user_nul(buf, count);
	अगर (IS_ERR(page))
		वापस PTR_ERR(page);

	length = -EINVAL;
	अगर (माला_पूछो(page, "%u", &new_value) != 1)
		जाओ out;

	अगर (new_value) अणु
		अक्षर comm[माप(current->comm)];

		स_नकल(comm, current->comm, माप(comm));
		pr_warn_once("SELinux: %s (%d) set checkreqprot to 1. This is deprecated and will be rejected in a future kernel release.\n",
			     comm, current->pid);
	पूर्ण

	checkreqprot_set(fsi->state, (new_value ? 1 : 0));
	length = count;

	selinux_ima_measure_state(fsi->state);

out:
	kमुक्त(page);
	वापस length;
पूर्ण
अटल स्थिर काष्ठा file_operations sel_checkreqprot_ops = अणु
	.पढ़ो		= sel_पढ़ो_checkreqprot,
	.ग_लिखो		= sel_ग_लिखो_checkreqprot,
	.llseek		= generic_file_llseek,
पूर्ण;

अटल sमाप_प्रकार sel_ग_लिखो_validatetrans(काष्ठा file *file,
					स्थिर अक्षर __user *buf,
					माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा selinux_fs_info *fsi = file_inode(file)->i_sb->s_fs_info;
	काष्ठा selinux_state *state = fsi->state;
	अक्षर *oldcon = शून्य, *newcon = शून्य, *taskcon = शून्य;
	अक्षर *req = शून्य;
	u32 osid, nsid, tsid;
	u16 tclass;
	पूर्णांक rc;

	rc = avc_has_perm(&selinux_state,
			  current_sid(), SECINITSID_SECURITY,
			  SECCLASS_SECURITY, SECURITY__VALIDATE_TRANS, शून्य);
	अगर (rc)
		जाओ out;

	rc = -ENOMEM;
	अगर (count >= PAGE_SIZE)
		जाओ out;

	/* No partial ग_लिखोs. */
	rc = -EINVAL;
	अगर (*ppos != 0)
		जाओ out;

	req = memdup_user_nul(buf, count);
	अगर (IS_ERR(req)) अणु
		rc = PTR_ERR(req);
		req = शून्य;
		जाओ out;
	पूर्ण

	rc = -ENOMEM;
	oldcon = kzalloc(count + 1, GFP_KERNEL);
	अगर (!oldcon)
		जाओ out;

	newcon = kzalloc(count + 1, GFP_KERNEL);
	अगर (!newcon)
		जाओ out;

	taskcon = kzalloc(count + 1, GFP_KERNEL);
	अगर (!taskcon)
		जाओ out;

	rc = -EINVAL;
	अगर (माला_पूछो(req, "%s %s %hu %s", oldcon, newcon, &tclass, taskcon) != 4)
		जाओ out;

	rc = security_context_str_to_sid(state, oldcon, &osid, GFP_KERNEL);
	अगर (rc)
		जाओ out;

	rc = security_context_str_to_sid(state, newcon, &nsid, GFP_KERNEL);
	अगर (rc)
		जाओ out;

	rc = security_context_str_to_sid(state, taskcon, &tsid, GFP_KERNEL);
	अगर (rc)
		जाओ out;

	rc = security_validate_transition_user(state, osid, nsid, tsid, tclass);
	अगर (!rc)
		rc = count;
out:
	kमुक्त(req);
	kमुक्त(oldcon);
	kमुक्त(newcon);
	kमुक्त(taskcon);
	वापस rc;
पूर्ण

अटल स्थिर काष्ठा file_operations sel_transition_ops = अणु
	.ग_लिखो		= sel_ग_लिखो_validatetrans,
	.llseek		= generic_file_llseek,
पूर्ण;

/*
 * Reमुख्यing nodes use transaction based IO methods like nfsd/nfsctl.c
 */
अटल sमाप_प्रकार sel_ग_लिखो_access(काष्ठा file *file, अक्षर *buf, माप_प्रकार size);
अटल sमाप_प्रकार sel_ग_लिखो_create(काष्ठा file *file, अक्षर *buf, माप_प्रकार size);
अटल sमाप_प्रकार sel_ग_लिखो_relabel(काष्ठा file *file, अक्षर *buf, माप_प्रकार size);
अटल sमाप_प्रकार sel_ग_लिखो_user(काष्ठा file *file, अक्षर *buf, माप_प्रकार size);
अटल sमाप_प्रकार sel_ग_लिखो_member(काष्ठा file *file, अक्षर *buf, माप_प्रकार size);

अटल sमाप_प्रकार (*स्थिर ग_लिखो_op[])(काष्ठा file *, अक्षर *, माप_प्रकार) = अणु
	[SEL_ACCESS] = sel_ग_लिखो_access,
	[SEL_CREATE] = sel_ग_लिखो_create,
	[SEL_RELABEL] = sel_ग_लिखो_relabel,
	[SEL_USER] = sel_ग_लिखो_user,
	[SEL_MEMBER] = sel_ग_लिखो_member,
	[SEL_CONTEXT] = sel_ग_लिखो_context,
पूर्ण;

अटल sमाप_प्रकार selinux_transaction_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *buf, माप_प्रकार size, loff_t *pos)
अणु
	ino_t ino = file_inode(file)->i_ino;
	अक्षर *data;
	sमाप_प्रकार rv;

	अगर (ino >= ARRAY_SIZE(ग_लिखो_op) || !ग_लिखो_op[ino])
		वापस -EINVAL;

	data = simple_transaction_get(file, buf, size);
	अगर (IS_ERR(data))
		वापस PTR_ERR(data);

	rv = ग_लिखो_op[ino](file, data, size);
	अगर (rv > 0) अणु
		simple_transaction_set(file, rv);
		rv = size;
	पूर्ण
	वापस rv;
पूर्ण

अटल स्थिर काष्ठा file_operations transaction_ops = अणु
	.ग_लिखो		= selinux_transaction_ग_लिखो,
	.पढ़ो		= simple_transaction_पढ़ो,
	.release	= simple_transaction_release,
	.llseek		= generic_file_llseek,
पूर्ण;

/*
 * payload - ग_लिखो methods
 * If the method has a response, the response should be put in buf,
 * and the length वापसed.  Otherwise वापस 0 or and -error.
 */

अटल sमाप_प्रकार sel_ग_लिखो_access(काष्ठा file *file, अक्षर *buf, माप_प्रकार size)
अणु
	काष्ठा selinux_fs_info *fsi = file_inode(file)->i_sb->s_fs_info;
	काष्ठा selinux_state *state = fsi->state;
	अक्षर *scon = शून्य, *tcon = शून्य;
	u32 ssid, tsid;
	u16 tclass;
	काष्ठा av_decision avd;
	sमाप_प्रकार length;

	length = avc_has_perm(&selinux_state,
			      current_sid(), SECINITSID_SECURITY,
			      SECCLASS_SECURITY, SECURITY__COMPUTE_AV, शून्य);
	अगर (length)
		जाओ out;

	length = -ENOMEM;
	scon = kzalloc(size + 1, GFP_KERNEL);
	अगर (!scon)
		जाओ out;

	length = -ENOMEM;
	tcon = kzalloc(size + 1, GFP_KERNEL);
	अगर (!tcon)
		जाओ out;

	length = -EINVAL;
	अगर (माला_पूछो(buf, "%s %s %hu", scon, tcon, &tclass) != 3)
		जाओ out;

	length = security_context_str_to_sid(state, scon, &ssid, GFP_KERNEL);
	अगर (length)
		जाओ out;

	length = security_context_str_to_sid(state, tcon, &tsid, GFP_KERNEL);
	अगर (length)
		जाओ out;

	security_compute_av_user(state, ssid, tsid, tclass, &avd);

	length = scnम_लिखो(buf, SIMPLE_TRANSACTION_LIMIT,
			  "%x %x %x %x %u %x",
			  avd.allowed, 0xffffffff,
			  avd.auditallow, avd.auditdeny,
			  avd.seqno, avd.flags);
out:
	kमुक्त(tcon);
	kमुक्त(scon);
	वापस length;
पूर्ण

अटल sमाप_प्रकार sel_ग_लिखो_create(काष्ठा file *file, अक्षर *buf, माप_प्रकार size)
अणु
	काष्ठा selinux_fs_info *fsi = file_inode(file)->i_sb->s_fs_info;
	काष्ठा selinux_state *state = fsi->state;
	अक्षर *scon = शून्य, *tcon = शून्य;
	अक्षर *namebuf = शून्य, *objname = शून्य;
	u32 ssid, tsid, newsid;
	u16 tclass;
	sमाप_प्रकार length;
	अक्षर *newcon = शून्य;
	u32 len;
	पूर्णांक nargs;

	length = avc_has_perm(&selinux_state,
			      current_sid(), SECINITSID_SECURITY,
			      SECCLASS_SECURITY, SECURITY__COMPUTE_CREATE,
			      शून्य);
	अगर (length)
		जाओ out;

	length = -ENOMEM;
	scon = kzalloc(size + 1, GFP_KERNEL);
	अगर (!scon)
		जाओ out;

	length = -ENOMEM;
	tcon = kzalloc(size + 1, GFP_KERNEL);
	अगर (!tcon)
		जाओ out;

	length = -ENOMEM;
	namebuf = kzalloc(size + 1, GFP_KERNEL);
	अगर (!namebuf)
		जाओ out;

	length = -EINVAL;
	nargs = माला_पूछो(buf, "%s %s %hu %s", scon, tcon, &tclass, namebuf);
	अगर (nargs < 3 || nargs > 4)
		जाओ out;
	अगर (nargs == 4) अणु
		/*
		 * If and when the name of new object to be queried contains
		 * either whitespace or multibyte अक्षरacters, they shall be
		 * encoded based on the percentage-encoding rule.
		 * If not encoded, the माला_पूछो logic picks up only left-half
		 * of the supplied name; splitted by a whitespace unexpectedly.
		 */
		अक्षर   *r, *w;
		पूर्णांक     c1, c2;

		r = w = namebuf;
		करो अणु
			c1 = *r++;
			अगर (c1 == '+')
				c1 = ' ';
			अन्यथा अगर (c1 == '%') अणु
				c1 = hex_to_bin(*r++);
				अगर (c1 < 0)
					जाओ out;
				c2 = hex_to_bin(*r++);
				अगर (c2 < 0)
					जाओ out;
				c1 = (c1 << 4) | c2;
			पूर्ण
			*w++ = c1;
		पूर्ण जबतक (c1 != '\0');

		objname = namebuf;
	पूर्ण

	length = security_context_str_to_sid(state, scon, &ssid, GFP_KERNEL);
	अगर (length)
		जाओ out;

	length = security_context_str_to_sid(state, tcon, &tsid, GFP_KERNEL);
	अगर (length)
		जाओ out;

	length = security_transition_sid_user(state, ssid, tsid, tclass,
					      objname, &newsid);
	अगर (length)
		जाओ out;

	length = security_sid_to_context(state, newsid, &newcon, &len);
	अगर (length)
		जाओ out;

	length = -दुस्फल;
	अगर (len > SIMPLE_TRANSACTION_LIMIT) अणु
		pr_err("SELinux: %s:  context size (%u) exceeds "
			"payload max\n", __func__, len);
		जाओ out;
	पूर्ण

	स_नकल(buf, newcon, len);
	length = len;
out:
	kमुक्त(newcon);
	kमुक्त(namebuf);
	kमुक्त(tcon);
	kमुक्त(scon);
	वापस length;
पूर्ण

अटल sमाप_प्रकार sel_ग_लिखो_relabel(काष्ठा file *file, अक्षर *buf, माप_प्रकार size)
अणु
	काष्ठा selinux_fs_info *fsi = file_inode(file)->i_sb->s_fs_info;
	काष्ठा selinux_state *state = fsi->state;
	अक्षर *scon = शून्य, *tcon = शून्य;
	u32 ssid, tsid, newsid;
	u16 tclass;
	sमाप_प्रकार length;
	अक्षर *newcon = शून्य;
	u32 len;

	length = avc_has_perm(&selinux_state,
			      current_sid(), SECINITSID_SECURITY,
			      SECCLASS_SECURITY, SECURITY__COMPUTE_RELABEL,
			      शून्य);
	अगर (length)
		जाओ out;

	length = -ENOMEM;
	scon = kzalloc(size + 1, GFP_KERNEL);
	अगर (!scon)
		जाओ out;

	length = -ENOMEM;
	tcon = kzalloc(size + 1, GFP_KERNEL);
	अगर (!tcon)
		जाओ out;

	length = -EINVAL;
	अगर (माला_पूछो(buf, "%s %s %hu", scon, tcon, &tclass) != 3)
		जाओ out;

	length = security_context_str_to_sid(state, scon, &ssid, GFP_KERNEL);
	अगर (length)
		जाओ out;

	length = security_context_str_to_sid(state, tcon, &tsid, GFP_KERNEL);
	अगर (length)
		जाओ out;

	length = security_change_sid(state, ssid, tsid, tclass, &newsid);
	अगर (length)
		जाओ out;

	length = security_sid_to_context(state, newsid, &newcon, &len);
	अगर (length)
		जाओ out;

	length = -दुस्फल;
	अगर (len > SIMPLE_TRANSACTION_LIMIT)
		जाओ out;

	स_नकल(buf, newcon, len);
	length = len;
out:
	kमुक्त(newcon);
	kमुक्त(tcon);
	kमुक्त(scon);
	वापस length;
पूर्ण

अटल sमाप_प्रकार sel_ग_लिखो_user(काष्ठा file *file, अक्षर *buf, माप_प्रकार size)
अणु
	काष्ठा selinux_fs_info *fsi = file_inode(file)->i_sb->s_fs_info;
	काष्ठा selinux_state *state = fsi->state;
	अक्षर *con = शून्य, *user = शून्य, *ptr;
	u32 sid, *sids = शून्य;
	sमाप_प्रकार length;
	अक्षर *newcon;
	पूर्णांक i, rc;
	u32 len, nsids;

	length = avc_has_perm(&selinux_state,
			      current_sid(), SECINITSID_SECURITY,
			      SECCLASS_SECURITY, SECURITY__COMPUTE_USER,
			      शून्य);
	अगर (length)
		जाओ out;

	length = -ENOMEM;
	con = kzalloc(size + 1, GFP_KERNEL);
	अगर (!con)
		जाओ out;

	length = -ENOMEM;
	user = kzalloc(size + 1, GFP_KERNEL);
	अगर (!user)
		जाओ out;

	length = -EINVAL;
	अगर (माला_पूछो(buf, "%s %s", con, user) != 2)
		जाओ out;

	length = security_context_str_to_sid(state, con, &sid, GFP_KERNEL);
	अगर (length)
		जाओ out;

	length = security_get_user_sids(state, sid, user, &sids, &nsids);
	अगर (length)
		जाओ out;

	length = प्र_लिखो(buf, "%u", nsids) + 1;
	ptr = buf + length;
	क्रम (i = 0; i < nsids; i++) अणु
		rc = security_sid_to_context(state, sids[i], &newcon, &len);
		अगर (rc) अणु
			length = rc;
			जाओ out;
		पूर्ण
		अगर ((length + len) >= SIMPLE_TRANSACTION_LIMIT) अणु
			kमुक्त(newcon);
			length = -दुस्फल;
			जाओ out;
		पूर्ण
		स_नकल(ptr, newcon, len);
		kमुक्त(newcon);
		ptr += len;
		length += len;
	पूर्ण
out:
	kमुक्त(sids);
	kमुक्त(user);
	kमुक्त(con);
	वापस length;
पूर्ण

अटल sमाप_प्रकार sel_ग_लिखो_member(काष्ठा file *file, अक्षर *buf, माप_प्रकार size)
अणु
	काष्ठा selinux_fs_info *fsi = file_inode(file)->i_sb->s_fs_info;
	काष्ठा selinux_state *state = fsi->state;
	अक्षर *scon = शून्य, *tcon = शून्य;
	u32 ssid, tsid, newsid;
	u16 tclass;
	sमाप_प्रकार length;
	अक्षर *newcon = शून्य;
	u32 len;

	length = avc_has_perm(&selinux_state,
			      current_sid(), SECINITSID_SECURITY,
			      SECCLASS_SECURITY, SECURITY__COMPUTE_MEMBER,
			      शून्य);
	अगर (length)
		जाओ out;

	length = -ENOMEM;
	scon = kzalloc(size + 1, GFP_KERNEL);
	अगर (!scon)
		जाओ out;

	length = -ENOMEM;
	tcon = kzalloc(size + 1, GFP_KERNEL);
	अगर (!tcon)
		जाओ out;

	length = -EINVAL;
	अगर (माला_पूछो(buf, "%s %s %hu", scon, tcon, &tclass) != 3)
		जाओ out;

	length = security_context_str_to_sid(state, scon, &ssid, GFP_KERNEL);
	अगर (length)
		जाओ out;

	length = security_context_str_to_sid(state, tcon, &tsid, GFP_KERNEL);
	अगर (length)
		जाओ out;

	length = security_member_sid(state, ssid, tsid, tclass, &newsid);
	अगर (length)
		जाओ out;

	length = security_sid_to_context(state, newsid, &newcon, &len);
	अगर (length)
		जाओ out;

	length = -दुस्फल;
	अगर (len > SIMPLE_TRANSACTION_LIMIT) अणु
		pr_err("SELinux: %s:  context size (%u) exceeds "
			"payload max\n", __func__, len);
		जाओ out;
	पूर्ण

	स_नकल(buf, newcon, len);
	length = len;
out:
	kमुक्त(newcon);
	kमुक्त(tcon);
	kमुक्त(scon);
	वापस length;
पूर्ण

अटल काष्ठा inode *sel_make_inode(काष्ठा super_block *sb, पूर्णांक mode)
अणु
	काष्ठा inode *ret = new_inode(sb);

	अगर (ret) अणु
		ret->i_mode = mode;
		ret->i_aसमय = ret->i_mसमय = ret->i_स_समय = current_समय(ret);
	पूर्ण
	वापस ret;
पूर्ण

अटल sमाप_प्रकार sel_पढ़ो_bool(काष्ठा file *filep, अक्षर __user *buf,
			     माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा selinux_fs_info *fsi = file_inode(filep)->i_sb->s_fs_info;
	अक्षर *page = शून्य;
	sमाप_प्रकार length;
	sमाप_प्रकार ret;
	पूर्णांक cur_enक्रमcing;
	अचिन्हित index = file_inode(filep)->i_ino & SEL_INO_MASK;
	स्थिर अक्षर *name = filep->f_path.dentry->d_name.name;

	mutex_lock(&fsi->state->policy_mutex);

	ret = -EINVAL;
	अगर (index >= fsi->bool_num || म_भेद(name,
					     fsi->bool_pending_names[index]))
		जाओ out_unlock;

	ret = -ENOMEM;
	page = (अक्षर *)get_zeroed_page(GFP_KERNEL);
	अगर (!page)
		जाओ out_unlock;

	cur_enक्रमcing = security_get_bool_value(fsi->state, index);
	अगर (cur_enक्रमcing < 0) अणु
		ret = cur_enक्रमcing;
		जाओ out_unlock;
	पूर्ण
	length = scnम_लिखो(page, PAGE_SIZE, "%d %d", cur_enक्रमcing,
			  fsi->bool_pending_values[index]);
	mutex_unlock(&fsi->state->policy_mutex);
	ret = simple_पढ़ो_from_buffer(buf, count, ppos, page, length);
out_मुक्त:
	मुक्त_page((अचिन्हित दीर्घ)page);
	वापस ret;

out_unlock:
	mutex_unlock(&fsi->state->policy_mutex);
	जाओ out_मुक्त;
पूर्ण

अटल sमाप_प्रकार sel_ग_लिखो_bool(काष्ठा file *filep, स्थिर अक्षर __user *buf,
			      माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा selinux_fs_info *fsi = file_inode(filep)->i_sb->s_fs_info;
	अक्षर *page = शून्य;
	sमाप_प्रकार length;
	पूर्णांक new_value;
	अचिन्हित index = file_inode(filep)->i_ino & SEL_INO_MASK;
	स्थिर अक्षर *name = filep->f_path.dentry->d_name.name;

	अगर (count >= PAGE_SIZE)
		वापस -ENOMEM;

	/* No partial ग_लिखोs. */
	अगर (*ppos != 0)
		वापस -EINVAL;

	page = memdup_user_nul(buf, count);
	अगर (IS_ERR(page))
		वापस PTR_ERR(page);

	mutex_lock(&fsi->state->policy_mutex);

	length = avc_has_perm(&selinux_state,
			      current_sid(), SECINITSID_SECURITY,
			      SECCLASS_SECURITY, SECURITY__SETBOOL,
			      शून्य);
	अगर (length)
		जाओ out;

	length = -EINVAL;
	अगर (index >= fsi->bool_num || म_भेद(name,
					     fsi->bool_pending_names[index]))
		जाओ out;

	length = -EINVAL;
	अगर (माला_पूछो(page, "%d", &new_value) != 1)
		जाओ out;

	अगर (new_value)
		new_value = 1;

	fsi->bool_pending_values[index] = new_value;
	length = count;

out:
	mutex_unlock(&fsi->state->policy_mutex);
	kमुक्त(page);
	वापस length;
पूर्ण

अटल स्थिर काष्ठा file_operations sel_bool_ops = अणु
	.पढ़ो		= sel_पढ़ो_bool,
	.ग_लिखो		= sel_ग_लिखो_bool,
	.llseek		= generic_file_llseek,
पूर्ण;

अटल sमाप_प्रकार sel_commit_bools_ग_लिखो(काष्ठा file *filep,
				      स्थिर अक्षर __user *buf,
				      माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा selinux_fs_info *fsi = file_inode(filep)->i_sb->s_fs_info;
	अक्षर *page = शून्य;
	sमाप_प्रकार length;
	पूर्णांक new_value;

	अगर (count >= PAGE_SIZE)
		वापस -ENOMEM;

	/* No partial ग_लिखोs. */
	अगर (*ppos != 0)
		वापस -EINVAL;

	page = memdup_user_nul(buf, count);
	अगर (IS_ERR(page))
		वापस PTR_ERR(page);

	mutex_lock(&fsi->state->policy_mutex);

	length = avc_has_perm(&selinux_state,
			      current_sid(), SECINITSID_SECURITY,
			      SECCLASS_SECURITY, SECURITY__SETBOOL,
			      शून्य);
	अगर (length)
		जाओ out;

	length = -EINVAL;
	अगर (माला_पूछो(page, "%d", &new_value) != 1)
		जाओ out;

	length = 0;
	अगर (new_value && fsi->bool_pending_values)
		length = security_set_bools(fsi->state, fsi->bool_num,
					    fsi->bool_pending_values);

	अगर (!length)
		length = count;

out:
	mutex_unlock(&fsi->state->policy_mutex);
	kमुक्त(page);
	वापस length;
पूर्ण

अटल स्थिर काष्ठा file_operations sel_commit_bools_ops = अणु
	.ग_लिखो		= sel_commit_bools_ग_लिखो,
	.llseek		= generic_file_llseek,
पूर्ण;

अटल व्योम sel_हटाओ_entries(काष्ठा dentry *de)
अणु
	d_genocide(de);
	shrink_dcache_parent(de);
पूर्ण

अटल पूर्णांक sel_make_bools(काष्ठा selinux_policy *newpolicy, काष्ठा dentry *bool_dir,
			  अचिन्हित पूर्णांक *bool_num, अक्षर ***bool_pending_names,
			  अचिन्हित पूर्णांक **bool_pending_values)
अणु
	पूर्णांक ret;
	sमाप_प्रकार len;
	काष्ठा dentry *dentry = शून्य;
	काष्ठा inode *inode = शून्य;
	काष्ठा inode_security_काष्ठा *isec;
	अक्षर **names = शून्य, *page;
	u32 i, num;
	पूर्णांक *values = शून्य;
	u32 sid;

	ret = -ENOMEM;
	page = (अक्षर *)get_zeroed_page(GFP_KERNEL);
	अगर (!page)
		जाओ out;

	ret = security_get_bools(newpolicy, &num, &names, &values);
	अगर (ret)
		जाओ out;

	क्रम (i = 0; i < num; i++) अणु
		ret = -ENOMEM;
		dentry = d_alloc_name(bool_dir, names[i]);
		अगर (!dentry)
			जाओ out;

		ret = -ENOMEM;
		inode = sel_make_inode(bool_dir->d_sb, S_IFREG | S_IRUGO | S_IWUSR);
		अगर (!inode) अणु
			dput(dentry);
			जाओ out;
		पूर्ण

		ret = -ENAMETOOLONG;
		len = snम_लिखो(page, PAGE_SIZE, "/%s/%s", BOOL_सूची_NAME, names[i]);
		अगर (len >= PAGE_SIZE) अणु
			dput(dentry);
			iput(inode);
			जाओ out;
		पूर्ण

		isec = selinux_inode(inode);
		ret = selinux_policy_genfs_sid(newpolicy, "selinuxfs", page,
					 SECCLASS_खाता, &sid);
		अगर (ret) अणु
			pr_warn_ratelimited("SELinux: no sid found, defaulting to security isid for %s\n",
					   page);
			sid = SECINITSID_SECURITY;
		पूर्ण

		isec->sid = sid;
		isec->initialized = LABEL_INITIALIZED;
		inode->i_fop = &sel_bool_ops;
		inode->i_ino = i|SEL_BOOL_INO_OFFSET;
		d_add(dentry, inode);
	पूर्ण
	*bool_num = num;
	*bool_pending_names = names;
	*bool_pending_values = values;

	मुक्त_page((अचिन्हित दीर्घ)page);
	वापस 0;
out:
	मुक्त_page((अचिन्हित दीर्घ)page);

	अगर (names) अणु
		क्रम (i = 0; i < num; i++)
			kमुक्त(names[i]);
		kमुक्त(names);
	पूर्ण
	kमुक्त(values);
	sel_हटाओ_entries(bool_dir);

	वापस ret;
पूर्ण

अटल sमाप_प्रकार sel_पढ़ो_avc_cache_threshold(काष्ठा file *filp, अक्षर __user *buf,
					    माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा selinux_fs_info *fsi = file_inode(filp)->i_sb->s_fs_info;
	काष्ठा selinux_state *state = fsi->state;
	अक्षर पंचांगpbuf[TMPBUFLEN];
	sमाप_प्रकार length;

	length = scnम_लिखो(पंचांगpbuf, TMPBUFLEN, "%u",
			   avc_get_cache_threshold(state->avc));
	वापस simple_पढ़ो_from_buffer(buf, count, ppos, पंचांगpbuf, length);
पूर्ण

अटल sमाप_प्रकार sel_ग_लिखो_avc_cache_threshold(काष्ठा file *file,
					     स्थिर अक्षर __user *buf,
					     माप_प्रकार count, loff_t *ppos)

अणु
	काष्ठा selinux_fs_info *fsi = file_inode(file)->i_sb->s_fs_info;
	काष्ठा selinux_state *state = fsi->state;
	अक्षर *page;
	sमाप_प्रकार ret;
	अचिन्हित पूर्णांक new_value;

	ret = avc_has_perm(&selinux_state,
			   current_sid(), SECINITSID_SECURITY,
			   SECCLASS_SECURITY, SECURITY__SETSECPARAM,
			   शून्य);
	अगर (ret)
		वापस ret;

	अगर (count >= PAGE_SIZE)
		वापस -ENOMEM;

	/* No partial ग_लिखोs. */
	अगर (*ppos != 0)
		वापस -EINVAL;

	page = memdup_user_nul(buf, count);
	अगर (IS_ERR(page))
		वापस PTR_ERR(page);

	ret = -EINVAL;
	अगर (माला_पूछो(page, "%u", &new_value) != 1)
		जाओ out;

	avc_set_cache_threshold(state->avc, new_value);

	ret = count;
out:
	kमुक्त(page);
	वापस ret;
पूर्ण

अटल sमाप_प्रकार sel_पढ़ो_avc_hash_stats(काष्ठा file *filp, अक्षर __user *buf,
				       माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा selinux_fs_info *fsi = file_inode(filp)->i_sb->s_fs_info;
	काष्ठा selinux_state *state = fsi->state;
	अक्षर *page;
	sमाप_प्रकार length;

	page = (अक्षर *)__get_मुक्त_page(GFP_KERNEL);
	अगर (!page)
		वापस -ENOMEM;

	length = avc_get_hash_stats(state->avc, page);
	अगर (length >= 0)
		length = simple_पढ़ो_from_buffer(buf, count, ppos, page, length);
	मुक्त_page((अचिन्हित दीर्घ)page);

	वापस length;
पूर्ण

अटल sमाप_प्रकार sel_पढ़ो_sidtab_hash_stats(काष्ठा file *filp, अक्षर __user *buf,
					माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा selinux_fs_info *fsi = file_inode(filp)->i_sb->s_fs_info;
	काष्ठा selinux_state *state = fsi->state;
	अक्षर *page;
	sमाप_प्रकार length;

	page = (अक्षर *)__get_मुक्त_page(GFP_KERNEL);
	अगर (!page)
		वापस -ENOMEM;

	length = security_sidtab_hash_stats(state, page);
	अगर (length >= 0)
		length = simple_पढ़ो_from_buffer(buf, count, ppos, page,
						length);
	मुक्त_page((अचिन्हित दीर्घ)page);

	वापस length;
पूर्ण

अटल स्थिर काष्ठा file_operations sel_sidtab_hash_stats_ops = अणु
	.पढ़ो		= sel_पढ़ो_sidtab_hash_stats,
	.llseek		= generic_file_llseek,
पूर्ण;

अटल स्थिर काष्ठा file_operations sel_avc_cache_threshold_ops = अणु
	.पढ़ो		= sel_पढ़ो_avc_cache_threshold,
	.ग_लिखो		= sel_ग_लिखो_avc_cache_threshold,
	.llseek		= generic_file_llseek,
पूर्ण;

अटल स्थिर काष्ठा file_operations sel_avc_hash_stats_ops = अणु
	.पढ़ो		= sel_पढ़ो_avc_hash_stats,
	.llseek		= generic_file_llseek,
पूर्ण;

#अगर_घोषित CONFIG_SECURITY_SELINUX_AVC_STATS
अटल काष्ठा avc_cache_stats *sel_avc_get_stat_idx(loff_t *idx)
अणु
	पूर्णांक cpu;

	क्रम (cpu = *idx; cpu < nr_cpu_ids; ++cpu) अणु
		अगर (!cpu_possible(cpu))
			जारी;
		*idx = cpu + 1;
		वापस &per_cpu(avc_cache_stats, cpu);
	पूर्ण
	(*idx)++;
	वापस शून्य;
पूर्ण

अटल व्योम *sel_avc_stats_seq_start(काष्ठा seq_file *seq, loff_t *pos)
अणु
	loff_t n = *pos - 1;

	अगर (*pos == 0)
		वापस SEQ_START_TOKEN;

	वापस sel_avc_get_stat_idx(&n);
पूर्ण

अटल व्योम *sel_avc_stats_seq_next(काष्ठा seq_file *seq, व्योम *v, loff_t *pos)
अणु
	वापस sel_avc_get_stat_idx(pos);
पूर्ण

अटल पूर्णांक sel_avc_stats_seq_show(काष्ठा seq_file *seq, व्योम *v)
अणु
	काष्ठा avc_cache_stats *st = v;

	अगर (v == SEQ_START_TOKEN) अणु
		seq_माला_दो(seq,
			 "lookups hits misses allocations reclaims frees\n");
	पूर्ण अन्यथा अणु
		अचिन्हित पूर्णांक lookups = st->lookups;
		अचिन्हित पूर्णांक misses = st->misses;
		अचिन्हित पूर्णांक hits = lookups - misses;
		seq_म_लिखो(seq, "%u %u %u %u %u %u\n", lookups,
			   hits, misses, st->allocations,
			   st->reclaims, st->मुक्तs);
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम sel_avc_stats_seq_stop(काष्ठा seq_file *seq, व्योम *v)
अणु पूर्ण

अटल स्थिर काष्ठा seq_operations sel_avc_cache_stats_seq_ops = अणु
	.start		= sel_avc_stats_seq_start,
	.next		= sel_avc_stats_seq_next,
	.show		= sel_avc_stats_seq_show,
	.stop		= sel_avc_stats_seq_stop,
पूर्ण;

अटल पूर्णांक sel_खोलो_avc_cache_stats(काष्ठा inode *inode, काष्ठा file *file)
अणु
	वापस seq_खोलो(file, &sel_avc_cache_stats_seq_ops);
पूर्ण

अटल स्थिर काष्ठा file_operations sel_avc_cache_stats_ops = अणु
	.खोलो		= sel_खोलो_avc_cache_stats,
	.पढ़ो		= seq_पढ़ो,
	.llseek		= seq_lseek,
	.release	= seq_release,
पूर्ण;
#पूर्ण_अगर

अटल पूर्णांक sel_make_avc_files(काष्ठा dentry *dir)
अणु
	काष्ठा super_block *sb = dir->d_sb;
	काष्ठा selinux_fs_info *fsi = sb->s_fs_info;
	पूर्णांक i;
	अटल स्थिर काष्ठा tree_descr files[] = अणु
		अणु "cache_threshold",
		  &sel_avc_cache_threshold_ops, S_IRUGO|S_IWUSR पूर्ण,
		अणु "hash_stats", &sel_avc_hash_stats_ops, S_IRUGO पूर्ण,
#अगर_घोषित CONFIG_SECURITY_SELINUX_AVC_STATS
		अणु "cache_stats", &sel_avc_cache_stats_ops, S_IRUGO पूर्ण,
#पूर्ण_अगर
	पूर्ण;

	क्रम (i = 0; i < ARRAY_SIZE(files); i++) अणु
		काष्ठा inode *inode;
		काष्ठा dentry *dentry;

		dentry = d_alloc_name(dir, files[i].name);
		अगर (!dentry)
			वापस -ENOMEM;

		inode = sel_make_inode(dir->d_sb, S_IFREG|files[i].mode);
		अगर (!inode) अणु
			dput(dentry);
			वापस -ENOMEM;
		पूर्ण

		inode->i_fop = files[i].ops;
		inode->i_ino = ++fsi->last_ino;
		d_add(dentry, inode);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक sel_make_ss_files(काष्ठा dentry *dir)
अणु
	काष्ठा super_block *sb = dir->d_sb;
	काष्ठा selinux_fs_info *fsi = sb->s_fs_info;
	पूर्णांक i;
	अटल काष्ठा tree_descr files[] = अणु
		अणु "sidtab_hash_stats", &sel_sidtab_hash_stats_ops, S_IRUGO पूर्ण,
	पूर्ण;

	क्रम (i = 0; i < ARRAY_SIZE(files); i++) अणु
		काष्ठा inode *inode;
		काष्ठा dentry *dentry;

		dentry = d_alloc_name(dir, files[i].name);
		अगर (!dentry)
			वापस -ENOMEM;

		inode = sel_make_inode(dir->d_sb, S_IFREG|files[i].mode);
		अगर (!inode) अणु
			dput(dentry);
			वापस -ENOMEM;
		पूर्ण

		inode->i_fop = files[i].ops;
		inode->i_ino = ++fsi->last_ino;
		d_add(dentry, inode);
	पूर्ण

	वापस 0;
पूर्ण

अटल sमाप_प्रकार sel_पढ़ो_initcon(काष्ठा file *file, अक्षर __user *buf,
				माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा selinux_fs_info *fsi = file_inode(file)->i_sb->s_fs_info;
	अक्षर *con;
	u32 sid, len;
	sमाप_प्रकार ret;

	sid = file_inode(file)->i_ino&SEL_INO_MASK;
	ret = security_sid_to_context(fsi->state, sid, &con, &len);
	अगर (ret)
		वापस ret;

	ret = simple_पढ़ो_from_buffer(buf, count, ppos, con, len);
	kमुक्त(con);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा file_operations sel_initcon_ops = अणु
	.पढ़ो		= sel_पढ़ो_initcon,
	.llseek		= generic_file_llseek,
पूर्ण;

अटल पूर्णांक sel_make_initcon_files(काष्ठा dentry *dir)
अणु
	पूर्णांक i;

	क्रम (i = 1; i <= SECINITSID_NUM; i++) अणु
		काष्ठा inode *inode;
		काष्ठा dentry *dentry;
		स्थिर अक्षर *s = security_get_initial_sid_context(i);

		अगर (!s)
			जारी;
		dentry = d_alloc_name(dir, s);
		अगर (!dentry)
			वापस -ENOMEM;

		inode = sel_make_inode(dir->d_sb, S_IFREG|S_IRUGO);
		अगर (!inode) अणु
			dput(dentry);
			वापस -ENOMEM;
		पूर्ण

		inode->i_fop = &sel_initcon_ops;
		inode->i_ino = i|SEL_INITCON_INO_OFFSET;
		d_add(dentry, inode);
	पूर्ण

	वापस 0;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ sel_class_to_ino(u16 class)
अणु
	वापस (class * (SEL_VEC_MAX + 1)) | SEL_CLASS_INO_OFFSET;
पूर्ण

अटल अंतरभूत u16 sel_ino_to_class(अचिन्हित दीर्घ ino)
अणु
	वापस (ino & SEL_INO_MASK) / (SEL_VEC_MAX + 1);
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ sel_perm_to_ino(u16 class, u32 perm)
अणु
	वापस (class * (SEL_VEC_MAX + 1) + perm) | SEL_CLASS_INO_OFFSET;
पूर्ण

अटल अंतरभूत u32 sel_ino_to_perm(अचिन्हित दीर्घ ino)
अणु
	वापस (ino & SEL_INO_MASK) % (SEL_VEC_MAX + 1);
पूर्ण

अटल sमाप_प्रकार sel_पढ़ो_class(काष्ठा file *file, अक्षर __user *buf,
				माप_प्रकार count, loff_t *ppos)
अणु
	अचिन्हित दीर्घ ino = file_inode(file)->i_ino;
	अक्षर res[TMPBUFLEN];
	sमाप_प्रकार len = scnम_लिखो(res, माप(res), "%d", sel_ino_to_class(ino));
	वापस simple_पढ़ो_from_buffer(buf, count, ppos, res, len);
पूर्ण

अटल स्थिर काष्ठा file_operations sel_class_ops = अणु
	.पढ़ो		= sel_पढ़ो_class,
	.llseek		= generic_file_llseek,
पूर्ण;

अटल sमाप_प्रकार sel_पढ़ो_perm(काष्ठा file *file, अक्षर __user *buf,
				माप_प्रकार count, loff_t *ppos)
अणु
	अचिन्हित दीर्घ ino = file_inode(file)->i_ino;
	अक्षर res[TMPBUFLEN];
	sमाप_प्रकार len = scnम_लिखो(res, माप(res), "%d", sel_ino_to_perm(ino));
	वापस simple_पढ़ो_from_buffer(buf, count, ppos, res, len);
पूर्ण

अटल स्थिर काष्ठा file_operations sel_perm_ops = अणु
	.पढ़ो		= sel_पढ़ो_perm,
	.llseek		= generic_file_llseek,
पूर्ण;

अटल sमाप_प्रकार sel_पढ़ो_policycap(काष्ठा file *file, अक्षर __user *buf,
				  माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा selinux_fs_info *fsi = file_inode(file)->i_sb->s_fs_info;
	पूर्णांक value;
	अक्षर पंचांगpbuf[TMPBUFLEN];
	sमाप_प्रकार length;
	अचिन्हित दीर्घ i_ino = file_inode(file)->i_ino;

	value = security_policycap_supported(fsi->state, i_ino & SEL_INO_MASK);
	length = scnम_लिखो(पंचांगpbuf, TMPBUFLEN, "%d", value);

	वापस simple_पढ़ो_from_buffer(buf, count, ppos, पंचांगpbuf, length);
पूर्ण

अटल स्थिर काष्ठा file_operations sel_policycap_ops = अणु
	.पढ़ो		= sel_पढ़ो_policycap,
	.llseek		= generic_file_llseek,
पूर्ण;

अटल पूर्णांक sel_make_perm_files(काष्ठा selinux_policy *newpolicy,
			अक्षर *objclass, पूर्णांक classvalue,
			काष्ठा dentry *dir)
अणु
	पूर्णांक i, rc, nperms;
	अक्षर **perms;

	rc = security_get_permissions(newpolicy, objclass, &perms, &nperms);
	अगर (rc)
		वापस rc;

	क्रम (i = 0; i < nperms; i++) अणु
		काष्ठा inode *inode;
		काष्ठा dentry *dentry;

		rc = -ENOMEM;
		dentry = d_alloc_name(dir, perms[i]);
		अगर (!dentry)
			जाओ out;

		rc = -ENOMEM;
		inode = sel_make_inode(dir->d_sb, S_IFREG|S_IRUGO);
		अगर (!inode) अणु
			dput(dentry);
			जाओ out;
		पूर्ण

		inode->i_fop = &sel_perm_ops;
		/* i+1 since perm values are 1-indexed */
		inode->i_ino = sel_perm_to_ino(classvalue, i + 1);
		d_add(dentry, inode);
	पूर्ण
	rc = 0;
out:
	क्रम (i = 0; i < nperms; i++)
		kमुक्त(perms[i]);
	kमुक्त(perms);
	वापस rc;
पूर्ण

अटल पूर्णांक sel_make_class_dir_entries(काष्ठा selinux_policy *newpolicy,
				अक्षर *classname, पूर्णांक index,
				काष्ठा dentry *dir)
अणु
	काष्ठा super_block *sb = dir->d_sb;
	काष्ठा selinux_fs_info *fsi = sb->s_fs_info;
	काष्ठा dentry *dentry = शून्य;
	काष्ठा inode *inode = शून्य;
	पूर्णांक rc;

	dentry = d_alloc_name(dir, "index");
	अगर (!dentry)
		वापस -ENOMEM;

	inode = sel_make_inode(dir->d_sb, S_IFREG|S_IRUGO);
	अगर (!inode) अणु
		dput(dentry);
		वापस -ENOMEM;
	पूर्ण

	inode->i_fop = &sel_class_ops;
	inode->i_ino = sel_class_to_ino(index);
	d_add(dentry, inode);

	dentry = sel_make_dir(dir, "perms", &fsi->last_class_ino);
	अगर (IS_ERR(dentry))
		वापस PTR_ERR(dentry);

	rc = sel_make_perm_files(newpolicy, classname, index, dentry);

	वापस rc;
पूर्ण

अटल पूर्णांक sel_make_classes(काष्ठा selinux_policy *newpolicy,
			    काष्ठा dentry *class_dir,
			    अचिन्हित दीर्घ *last_class_ino)
अणु

	पूर्णांक rc, nclasses, i;
	अक्षर **classes;

	rc = security_get_classes(newpolicy, &classes, &nclasses);
	अगर (rc)
		वापस rc;

	/* +2 since classes are 1-indexed */
	*last_class_ino = sel_class_to_ino(nclasses + 2);

	क्रम (i = 0; i < nclasses; i++) अणु
		काष्ठा dentry *class_name_dir;

		class_name_dir = sel_make_dir(class_dir, classes[i],
					      last_class_ino);
		अगर (IS_ERR(class_name_dir)) अणु
			rc = PTR_ERR(class_name_dir);
			जाओ out;
		पूर्ण

		/* i+1 since class values are 1-indexed */
		rc = sel_make_class_dir_entries(newpolicy, classes[i], i + 1,
				class_name_dir);
		अगर (rc)
			जाओ out;
	पूर्ण
	rc = 0;
out:
	क्रम (i = 0; i < nclasses; i++)
		kमुक्त(classes[i]);
	kमुक्त(classes);
	वापस rc;
पूर्ण

अटल पूर्णांक sel_make_policycap(काष्ठा selinux_fs_info *fsi)
अणु
	अचिन्हित पूर्णांक iter;
	काष्ठा dentry *dentry = शून्य;
	काष्ठा inode *inode = शून्य;

	क्रम (iter = 0; iter <= POLICYDB_CAPABILITY_MAX; iter++) अणु
		अगर (iter < ARRAY_SIZE(selinux_policycap_names))
			dentry = d_alloc_name(fsi->policycap_dir,
					      selinux_policycap_names[iter]);
		अन्यथा
			dentry = d_alloc_name(fsi->policycap_dir, "unknown");

		अगर (dentry == शून्य)
			वापस -ENOMEM;

		inode = sel_make_inode(fsi->sb, S_IFREG | 0444);
		अगर (inode == शून्य) अणु
			dput(dentry);
			वापस -ENOMEM;
		पूर्ण

		inode->i_fop = &sel_policycap_ops;
		inode->i_ino = iter | SEL_POLICYCAP_INO_OFFSET;
		d_add(dentry, inode);
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा dentry *sel_make_dir(काष्ठा dentry *dir, स्थिर अक्षर *name,
			अचिन्हित दीर्घ *ino)
अणु
	काष्ठा dentry *dentry = d_alloc_name(dir, name);
	काष्ठा inode *inode;

	अगर (!dentry)
		वापस ERR_PTR(-ENOMEM);

	inode = sel_make_inode(dir->d_sb, S_IFसूची | S_IRUGO | S_IXUGO);
	अगर (!inode) अणु
		dput(dentry);
		वापस ERR_PTR(-ENOMEM);
	पूर्ण

	inode->i_op = &simple_dir_inode_operations;
	inode->i_fop = &simple_dir_operations;
	inode->i_ino = ++(*ino);
	/* directory inodes start off with i_nlink == 2 (क्रम "." entry) */
	inc_nlink(inode);
	d_add(dentry, inode);
	/* bump link count on parent directory, too */
	inc_nlink(d_inode(dir));

	वापस dentry;
पूर्ण

अटल काष्ठा dentry *sel_make_disconnected_dir(काष्ठा super_block *sb,
						अचिन्हित दीर्घ *ino)
अणु
	काष्ठा inode *inode = sel_make_inode(sb, S_IFसूची | S_IRUGO | S_IXUGO);

	अगर (!inode)
		वापस ERR_PTR(-ENOMEM);

	inode->i_op = &simple_dir_inode_operations;
	inode->i_fop = &simple_dir_operations;
	inode->i_ino = ++(*ino);
	/* directory inodes start off with i_nlink == 2 (क्रम "." entry) */
	inc_nlink(inode);
	वापस d_obtain_alias(inode);
पूर्ण

#घोषणा शून्य_खाता_NAME "null"

अटल पूर्णांक sel_fill_super(काष्ठा super_block *sb, काष्ठा fs_context *fc)
अणु
	काष्ठा selinux_fs_info *fsi;
	पूर्णांक ret;
	काष्ठा dentry *dentry;
	काष्ठा inode *inode;
	काष्ठा inode_security_काष्ठा *isec;

	अटल स्थिर काष्ठा tree_descr selinux_files[] = अणु
		[SEL_LOAD] = अणु"load", &sel_load_ops, S_IRUSR|S_IWUSRपूर्ण,
		[SEL_ENFORCE] = अणु"enforce", &sel_enक्रमce_ops, S_IRUGO|S_IWUSRपूर्ण,
		[SEL_CONTEXT] = अणु"context", &transaction_ops, S_IRUGO|S_IWUGOपूर्ण,
		[SEL_ACCESS] = अणु"access", &transaction_ops, S_IRUGO|S_IWUGOपूर्ण,
		[SEL_CREATE] = अणु"create", &transaction_ops, S_IRUGO|S_IWUGOपूर्ण,
		[SEL_RELABEL] = अणु"relabel", &transaction_ops, S_IRUGO|S_IWUGOपूर्ण,
		[SEL_USER] = अणु"user", &transaction_ops, S_IRUGO|S_IWUGOपूर्ण,
		[SEL_POLICYVERS] = अणु"policyvers", &sel_policyvers_ops, S_IRUGOपूर्ण,
		[SEL_COMMIT_BOOLS] = अणु"commit_pending_bools", &sel_commit_bools_ops, S_IWUSRपूर्ण,
		[SEL_MLS] = अणु"mls", &sel_mls_ops, S_IRUGOपूर्ण,
		[SEL_DISABLE] = अणु"disable", &sel_disable_ops, S_IWUSRपूर्ण,
		[SEL_MEMBER] = अणु"member", &transaction_ops, S_IRUGO|S_IWUGOपूर्ण,
		[SEL_CHECKREQPROT] = अणु"checkreqprot", &sel_checkreqprot_ops, S_IRUGO|S_IWUSRपूर्ण,
		[SEL_REJECT_UNKNOWN] = अणु"reject_unknown", &sel_handle_unknown_ops, S_IRUGOपूर्ण,
		[SEL_DENY_UNKNOWN] = अणु"deny_unknown", &sel_handle_unknown_ops, S_IRUGOपूर्ण,
		[SEL_STATUS] = अणु"status", &sel_handle_status_ops, S_IRUGOपूर्ण,
		[SEL_POLICY] = अणु"policy", &sel_policy_ops, S_IRUGOपूर्ण,
		[SEL_VALIDATE_TRANS] = अणु"validatetrans", &sel_transition_ops,
					S_IWUGOपूर्ण,
		/* last one */ अणु""पूर्ण
	पूर्ण;

	ret = selinux_fs_info_create(sb);
	अगर (ret)
		जाओ err;

	ret = simple_fill_super(sb, SELINUX_MAGIC, selinux_files);
	अगर (ret)
		जाओ err;

	fsi = sb->s_fs_info;
	fsi->bool_dir = sel_make_dir(sb->s_root, BOOL_सूची_NAME, &fsi->last_ino);
	अगर (IS_ERR(fsi->bool_dir)) अणु
		ret = PTR_ERR(fsi->bool_dir);
		fsi->bool_dir = शून्य;
		जाओ err;
	पूर्ण

	ret = -ENOMEM;
	dentry = d_alloc_name(sb->s_root, शून्य_खाता_NAME);
	अगर (!dentry)
		जाओ err;

	ret = -ENOMEM;
	inode = sel_make_inode(sb, S_IFCHR | S_IRUGO | S_IWUGO);
	अगर (!inode) अणु
		dput(dentry);
		जाओ err;
	पूर्ण

	inode->i_ino = ++fsi->last_ino;
	isec = selinux_inode(inode);
	isec->sid = SECINITSID_DEVशून्य;
	isec->sclass = SECCLASS_CHR_खाता;
	isec->initialized = LABEL_INITIALIZED;

	init_special_inode(inode, S_IFCHR | S_IRUGO | S_IWUGO, MKDEV(MEM_MAJOR, 3));
	d_add(dentry, inode);

	dentry = sel_make_dir(sb->s_root, "avc", &fsi->last_ino);
	अगर (IS_ERR(dentry)) अणु
		ret = PTR_ERR(dentry);
		जाओ err;
	पूर्ण

	ret = sel_make_avc_files(dentry);

	dentry = sel_make_dir(sb->s_root, "ss", &fsi->last_ino);
	अगर (IS_ERR(dentry)) अणु
		ret = PTR_ERR(dentry);
		जाओ err;
	पूर्ण

	ret = sel_make_ss_files(dentry);
	अगर (ret)
		जाओ err;

	dentry = sel_make_dir(sb->s_root, "initial_contexts", &fsi->last_ino);
	अगर (IS_ERR(dentry)) अणु
		ret = PTR_ERR(dentry);
		जाओ err;
	पूर्ण

	ret = sel_make_initcon_files(dentry);
	अगर (ret)
		जाओ err;

	fsi->class_dir = sel_make_dir(sb->s_root, CLASS_सूची_NAME, &fsi->last_ino);
	अगर (IS_ERR(fsi->class_dir)) अणु
		ret = PTR_ERR(fsi->class_dir);
		fsi->class_dir = शून्य;
		जाओ err;
	पूर्ण

	fsi->policycap_dir = sel_make_dir(sb->s_root, POLICYCAP_सूची_NAME,
					  &fsi->last_ino);
	अगर (IS_ERR(fsi->policycap_dir)) अणु
		ret = PTR_ERR(fsi->policycap_dir);
		fsi->policycap_dir = शून्य;
		जाओ err;
	पूर्ण

	ret = sel_make_policycap(fsi);
	अगर (ret) अणु
		pr_err("SELinux: failed to load policy capabilities\n");
		जाओ err;
	पूर्ण

	वापस 0;
err:
	pr_err("SELinux: %s:  failed while creating inodes\n",
		__func__);

	selinux_fs_info_मुक्त(sb);

	वापस ret;
पूर्ण

अटल पूर्णांक sel_get_tree(काष्ठा fs_context *fc)
अणु
	वापस get_tree_single(fc, sel_fill_super);
पूर्ण

अटल स्थिर काष्ठा fs_context_operations sel_context_ops = अणु
	.get_tree	= sel_get_tree,
पूर्ण;

अटल पूर्णांक sel_init_fs_context(काष्ठा fs_context *fc)
अणु
	fc->ops = &sel_context_ops;
	वापस 0;
पूर्ण

अटल व्योम sel_समाप्त_sb(काष्ठा super_block *sb)
अणु
	selinux_fs_info_मुक्त(sb);
	समाप्त_litter_super(sb);
पूर्ण

अटल काष्ठा file_प्रणाली_type sel_fs_type = अणु
	.name		= "selinuxfs",
	.init_fs_context = sel_init_fs_context,
	.समाप्त_sb	= sel_समाप्त_sb,
पूर्ण;

अटल काष्ठा vfsmount *selinuxfs_mount __ro_after_init;
काष्ठा path selinux_null __ro_after_init;

अटल पूर्णांक __init init_sel_fs(व्योम)
अणु
	काष्ठा qstr null_name = QSTR_INIT(शून्य_खाता_NAME,
					  माप(शून्य_खाता_NAME)-1);
	पूर्णांक err;

	अगर (!selinux_enabled_boot)
		वापस 0;

	err = sysfs_create_mount_poपूर्णांक(fs_kobj, "selinux");
	अगर (err)
		वापस err;

	err = रेजिस्टर_fileप्रणाली(&sel_fs_type);
	अगर (err) अणु
		sysfs_हटाओ_mount_poपूर्णांक(fs_kobj, "selinux");
		वापस err;
	पूर्ण

	selinux_null.mnt = selinuxfs_mount = kern_mount(&sel_fs_type);
	अगर (IS_ERR(selinuxfs_mount)) अणु
		pr_err("selinuxfs:  could not mount!\n");
		err = PTR_ERR(selinuxfs_mount);
		selinuxfs_mount = शून्य;
	पूर्ण
	selinux_null.dentry = d_hash_and_lookup(selinux_null.mnt->mnt_root,
						&null_name);
	अगर (IS_ERR(selinux_null.dentry)) अणु
		pr_err("selinuxfs:  could not lookup null!\n");
		err = PTR_ERR(selinux_null.dentry);
		selinux_null.dentry = शून्य;
	पूर्ण

	वापस err;
पूर्ण

__initcall(init_sel_fs);

#अगर_घोषित CONFIG_SECURITY_SELINUX_DISABLE
व्योम निकास_sel_fs(व्योम)
अणु
	sysfs_हटाओ_mount_poपूर्णांक(fs_kobj, "selinux");
	dput(selinux_null.dentry);
	kern_unmount(selinuxfs_mount);
	unरेजिस्टर_fileप्रणाली(&sel_fs_type);
पूर्ण
#पूर्ण_अगर
