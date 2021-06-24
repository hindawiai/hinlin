<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  Simplअगरied MAC Kernel (smack) security module
 *
 *  This file contains the smack hook function implementations.
 *
 *  Authors:
 *	Casey Schaufler <हालy@schaufler-ca.com>
 *	Jarkko Sakkinen <jarkko.sakkinen@पूर्णांकel.com>
 *
 *  Copyright (C) 2007 Casey Schaufler <हालy@schaufler-ca.com>
 *  Copyright (C) 2009 Hewlett-Packard Development Company, L.P.
 *                Paul Moore <paul@paul-moore.com>
 *  Copyright (C) 2010 Nokia Corporation
 *  Copyright (C) 2011 Intel Corporation.
 */

#समावेश <linux/xattr.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/mount.h>
#समावेश <linux/स्थिति.स>
#समावेश <linux/kd.h>
#समावेश <यंत्र/ioctls.h>
#समावेश <linux/ip.h>
#समावेश <linux/tcp.h>
#समावेश <linux/udp.h>
#समावेश <linux/dccp.h>
#समावेश <linux/icmpv6.h>
#समावेश <linux/slab.h>
#समावेश <linux/mutex.h>
#समावेश <net/cipso_ipv4.h>
#समावेश <net/ip.h>
#समावेश <net/ipv6.h>
#समावेश <linux/audit.h>
#समावेश <linux/magic.h>
#समावेश <linux/dcache.h>
#समावेश <linux/personality.h>
#समावेश <linux/msg.h>
#समावेश <linux/shm.h>
#समावेश <linux/binfmts.h>
#समावेश <linux/parser.h>
#समावेश <linux/fs_context.h>
#समावेश <linux/fs_parser.h>
#समावेश <linux/watch_queue.h>
#समावेश "smack.h"

#घोषणा TRANS_TRUE	"TRUE"
#घोषणा TRANS_TRUE_SIZE	4

#घोषणा SMK_CONNECTING	0
#घोषणा SMK_RECEIVING	1
#घोषणा SMK_SENDING	2

अटल DEFINE_MUTEX(smack_ipv6_lock);
अटल LIST_HEAD(smk_ipv6_port_list);
काष्ठा kmem_cache *smack_rule_cache;
पूर्णांक smack_enabled;

#घोषणा A(s) अणु"smack"#s, माप("smack"#s) - 1, Opt_##sपूर्ण
अटल काष्ठा अणु
	स्थिर अक्षर *name;
	पूर्णांक len;
	पूर्णांक opt;
पूर्ण smk_mount_opts[] = अणु
	अणु"smackfsdef", माप("smackfsdef") - 1, Opt_fsशेषपूर्ण,
	A(fsशेष), A(fsन्यूनमान), A(fshat), A(fsroot), A(fstransmute)
पूर्ण;
#अघोषित A

अटल पूर्णांक match_opt_prefix(अक्षर *s, पूर्णांक l, अक्षर **arg)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(smk_mount_opts); i++) अणु
		माप_प्रकार len = smk_mount_opts[i].len;
		अगर (len > l || स_भेद(s, smk_mount_opts[i].name, len))
			जारी;
		अगर (len == l || s[len] != '=')
			जारी;
		*arg = s + len + 1;
		वापस smk_mount_opts[i].opt;
	पूर्ण
	वापस Opt_error;
पूर्ण

#अगर_घोषित CONFIG_SECURITY_SMACK_BRINGUP
अटल अक्षर *smk_bu_mess[] = अणु
	"Bringup Error",	/* Unused */
	"Bringup",		/* SMACK_BRINGUP_ALLOW */
	"Unconfined Subject",	/* SMACK_UNCONFINED_SUBJECT */
	"Unconfined Object",	/* SMACK_UNCONFINED_OBJECT */
पूर्ण;

अटल व्योम smk_bu_mode(पूर्णांक mode, अक्षर *s)
अणु
	पूर्णांक i = 0;

	अगर (mode & MAY_READ)
		s[i++] = 'r';
	अगर (mode & MAY_WRITE)
		s[i++] = 'w';
	अगर (mode & MAY_EXEC)
		s[i++] = 'x';
	अगर (mode & MAY_APPEND)
		s[i++] = 'a';
	अगर (mode & MAY_TRANSMUTE)
		s[i++] = 't';
	अगर (mode & MAY_LOCK)
		s[i++] = 'l';
	अगर (i == 0)
		s[i++] = '-';
	s[i] = '\0';
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_SECURITY_SMACK_BRINGUP
अटल पूर्णांक smk_bu_note(अक्षर *note, काष्ठा smack_known *sskp,
		       काष्ठा smack_known *oskp, पूर्णांक mode, पूर्णांक rc)
अणु
	अक्षर acc[SMK_NUM_ACCESS_TYPE + 1];

	अगर (rc <= 0)
		वापस rc;
	अगर (rc > SMACK_UNCONFINED_OBJECT)
		rc = 0;

	smk_bu_mode(mode, acc);
	pr_info("Smack %s: (%s %s %s) %s\n", smk_bu_mess[rc],
		sskp->smk_known, oskp->smk_known, acc, note);
	वापस 0;
पूर्ण
#अन्यथा
#घोषणा smk_bu_note(note, sskp, oskp, mode, RC) (RC)
#पूर्ण_अगर

#अगर_घोषित CONFIG_SECURITY_SMACK_BRINGUP
अटल पूर्णांक smk_bu_current(अक्षर *note, काष्ठा smack_known *oskp,
			  पूर्णांक mode, पूर्णांक rc)
अणु
	काष्ठा task_smack *tsp = smack_cred(current_cred());
	अक्षर acc[SMK_NUM_ACCESS_TYPE + 1];

	अगर (rc <= 0)
		वापस rc;
	अगर (rc > SMACK_UNCONFINED_OBJECT)
		rc = 0;

	smk_bu_mode(mode, acc);
	pr_info("Smack %s: (%s %s %s) %s %s\n", smk_bu_mess[rc],
		tsp->smk_task->smk_known, oskp->smk_known,
		acc, current->comm, note);
	वापस 0;
पूर्ण
#अन्यथा
#घोषणा smk_bu_current(note, oskp, mode, RC) (RC)
#पूर्ण_अगर

#अगर_घोषित CONFIG_SECURITY_SMACK_BRINGUP
अटल पूर्णांक smk_bu_task(काष्ठा task_काष्ठा *otp, पूर्णांक mode, पूर्णांक rc)
अणु
	काष्ठा task_smack *tsp = smack_cred(current_cred());
	काष्ठा smack_known *smk_task = smk_of_task_काष्ठा_obj(otp);
	अक्षर acc[SMK_NUM_ACCESS_TYPE + 1];

	अगर (rc <= 0)
		वापस rc;
	अगर (rc > SMACK_UNCONFINED_OBJECT)
		rc = 0;

	smk_bu_mode(mode, acc);
	pr_info("Smack %s: (%s %s %s) %s to %s\n", smk_bu_mess[rc],
		tsp->smk_task->smk_known, smk_task->smk_known, acc,
		current->comm, otp->comm);
	वापस 0;
पूर्ण
#अन्यथा
#घोषणा smk_bu_task(otp, mode, RC) (RC)
#पूर्ण_अगर

#अगर_घोषित CONFIG_SECURITY_SMACK_BRINGUP
अटल पूर्णांक smk_bu_inode(काष्ठा inode *inode, पूर्णांक mode, पूर्णांक rc)
अणु
	काष्ठा task_smack *tsp = smack_cred(current_cred());
	काष्ठा inode_smack *isp = smack_inode(inode);
	अक्षर acc[SMK_NUM_ACCESS_TYPE + 1];

	अगर (isp->smk_flags & SMK_INODE_IMPURE)
		pr_info("Smack Unconfined Corruption: inode=(%s %ld) %s\n",
			inode->i_sb->s_id, inode->i_ino, current->comm);

	अगर (rc <= 0)
		वापस rc;
	अगर (rc > SMACK_UNCONFINED_OBJECT)
		rc = 0;
	अगर (rc == SMACK_UNCONFINED_SUBJECT &&
	    (mode & (MAY_WRITE | MAY_APPEND)))
		isp->smk_flags |= SMK_INODE_IMPURE;

	smk_bu_mode(mode, acc);

	pr_info("Smack %s: (%s %s %s) inode=(%s %ld) %s\n", smk_bu_mess[rc],
		tsp->smk_task->smk_known, isp->smk_inode->smk_known, acc,
		inode->i_sb->s_id, inode->i_ino, current->comm);
	वापस 0;
पूर्ण
#अन्यथा
#घोषणा smk_bu_inode(inode, mode, RC) (RC)
#पूर्ण_अगर

#अगर_घोषित CONFIG_SECURITY_SMACK_BRINGUP
अटल पूर्णांक smk_bu_file(काष्ठा file *file, पूर्णांक mode, पूर्णांक rc)
अणु
	काष्ठा task_smack *tsp = smack_cred(current_cred());
	काष्ठा smack_known *sskp = tsp->smk_task;
	काष्ठा inode *inode = file_inode(file);
	काष्ठा inode_smack *isp = smack_inode(inode);
	अक्षर acc[SMK_NUM_ACCESS_TYPE + 1];

	अगर (isp->smk_flags & SMK_INODE_IMPURE)
		pr_info("Smack Unconfined Corruption: inode=(%s %ld) %s\n",
			inode->i_sb->s_id, inode->i_ino, current->comm);

	अगर (rc <= 0)
		वापस rc;
	अगर (rc > SMACK_UNCONFINED_OBJECT)
		rc = 0;

	smk_bu_mode(mode, acc);
	pr_info("Smack %s: (%s %s %s) file=(%s %ld %pD) %s\n", smk_bu_mess[rc],
		sskp->smk_known, smk_of_inode(inode)->smk_known, acc,
		inode->i_sb->s_id, inode->i_ino, file,
		current->comm);
	वापस 0;
पूर्ण
#अन्यथा
#घोषणा smk_bu_file(file, mode, RC) (RC)
#पूर्ण_अगर

#अगर_घोषित CONFIG_SECURITY_SMACK_BRINGUP
अटल पूर्णांक smk_bu_credfile(स्थिर काष्ठा cred *cred, काष्ठा file *file,
				पूर्णांक mode, पूर्णांक rc)
अणु
	काष्ठा task_smack *tsp = smack_cred(cred);
	काष्ठा smack_known *sskp = tsp->smk_task;
	काष्ठा inode *inode = file_inode(file);
	काष्ठा inode_smack *isp = smack_inode(inode);
	अक्षर acc[SMK_NUM_ACCESS_TYPE + 1];

	अगर (isp->smk_flags & SMK_INODE_IMPURE)
		pr_info("Smack Unconfined Corruption: inode=(%s %ld) %s\n",
			inode->i_sb->s_id, inode->i_ino, current->comm);

	अगर (rc <= 0)
		वापस rc;
	अगर (rc > SMACK_UNCONFINED_OBJECT)
		rc = 0;

	smk_bu_mode(mode, acc);
	pr_info("Smack %s: (%s %s %s) file=(%s %ld %pD) %s\n", smk_bu_mess[rc],
		sskp->smk_known, smk_of_inode(inode)->smk_known, acc,
		inode->i_sb->s_id, inode->i_ino, file,
		current->comm);
	वापस 0;
पूर्ण
#अन्यथा
#घोषणा smk_bu_credfile(cred, file, mode, RC) (RC)
#पूर्ण_अगर

/**
 * smk_fetch - Fetch the smack label from a file.
 * @name: type of the label (attribute)
 * @ip: a poपूर्णांकer to the inode
 * @dp: a poपूर्णांकer to the dentry
 *
 * Returns a poपूर्णांकer to the master list entry क्रम the Smack label,
 * शून्य अगर there was no label to fetch, or an error code.
 */
अटल काष्ठा smack_known *smk_fetch(स्थिर अक्षर *name, काष्ठा inode *ip,
					काष्ठा dentry *dp)
अणु
	पूर्णांक rc;
	अक्षर *buffer;
	काष्ठा smack_known *skp = शून्य;

	अगर (!(ip->i_opflags & IOP_XATTR))
		वापस ERR_PTR(-EOPNOTSUPP);

	buffer = kzalloc(SMK_LONGLABEL, GFP_NOFS);
	अगर (buffer == शून्य)
		वापस ERR_PTR(-ENOMEM);

	rc = __vfs_getxattr(dp, ip, name, buffer, SMK_LONGLABEL);
	अगर (rc < 0)
		skp = ERR_PTR(rc);
	अन्यथा अगर (rc == 0)
		skp = शून्य;
	अन्यथा
		skp = smk_import_entry(buffer, rc);

	kमुक्त(buffer);

	वापस skp;
पूर्ण

/**
 * init_inode_smack - initialize an inode security blob
 * @inode: inode to extract the info from
 * @skp: a poपूर्णांकer to the Smack label entry to use in the blob
 *
 */
अटल व्योम init_inode_smack(काष्ठा inode *inode, काष्ठा smack_known *skp)
अणु
	काष्ठा inode_smack *isp = smack_inode(inode);

	isp->smk_inode = skp;
	isp->smk_flags = 0;
पूर्ण

/**
 * init_task_smack - initialize a task security blob
 * @tsp: blob to initialize
 * @task: a poपूर्णांकer to the Smack label क्रम the running task
 * @विभाजनed: a poपूर्णांकer to the Smack label क्रम the विभाजनed task
 *
 */
अटल व्योम init_task_smack(काष्ठा task_smack *tsp, काष्ठा smack_known *task,
					काष्ठा smack_known *विभाजनed)
अणु
	tsp->smk_task = task;
	tsp->smk_विभाजनed = विभाजनed;
	INIT_LIST_HEAD(&tsp->smk_rules);
	INIT_LIST_HEAD(&tsp->smk_relabel);
	mutex_init(&tsp->smk_rules_lock);
पूर्ण

/**
 * smk_copy_rules - copy a rule set
 * @nhead: new rules header poपूर्णांकer
 * @ohead: old rules header poपूर्णांकer
 * @gfp: type of the memory क्रम the allocation
 *
 * Returns 0 on success, -ENOMEM on error
 */
अटल पूर्णांक smk_copy_rules(काष्ठा list_head *nhead, काष्ठा list_head *ohead,
				gfp_t gfp)
अणु
	काष्ठा smack_rule *nrp;
	काष्ठा smack_rule *orp;
	पूर्णांक rc = 0;

	list_क्रम_each_entry_rcu(orp, ohead, list) अणु
		nrp = kmem_cache_zalloc(smack_rule_cache, gfp);
		अगर (nrp == शून्य) अणु
			rc = -ENOMEM;
			अवरोध;
		पूर्ण
		*nrp = *orp;
		list_add_rcu(&nrp->list, nhead);
	पूर्ण
	वापस rc;
पूर्ण

/**
 * smk_copy_relabel - copy smk_relabel labels list
 * @nhead: new rules header poपूर्णांकer
 * @ohead: old rules header poपूर्णांकer
 * @gfp: type of the memory क्रम the allocation
 *
 * Returns 0 on success, -ENOMEM on error
 */
अटल पूर्णांक smk_copy_relabel(काष्ठा list_head *nhead, काष्ठा list_head *ohead,
				gfp_t gfp)
अणु
	काष्ठा smack_known_list_elem *nklep;
	काष्ठा smack_known_list_elem *oklep;

	list_क्रम_each_entry(oklep, ohead, list) अणु
		nklep = kzalloc(माप(काष्ठा smack_known_list_elem), gfp);
		अगर (nklep == शून्य) अणु
			smk_destroy_label_list(nhead);
			वापस -ENOMEM;
		पूर्ण
		nklep->smk_label = oklep->smk_label;
		list_add(&nklep->list, nhead);
	पूर्ण

	वापस 0;
पूर्ण

/**
 * smk_ptrace_mode - helper function क्रम converting PTRACE_MODE_* पूर्णांकo MAY_*
 * @mode - input mode in क्रमm of PTRACE_MODE_*
 *
 * Returns a converted MAY_* mode usable by smack rules
 */
अटल अंतरभूत अचिन्हित पूर्णांक smk_ptrace_mode(अचिन्हित पूर्णांक mode)
अणु
	अगर (mode & PTRACE_MODE_ATTACH)
		वापस MAY_READWRITE;
	अगर (mode & PTRACE_MODE_READ)
		वापस MAY_READ;

	वापस 0;
पूर्ण

/**
 * smk_ptrace_rule_check - helper क्रम ptrace access
 * @tracer: tracer process
 * @tracee_known: label entry of the process that's about to be traced
 * @mode: ptrace attachment mode (PTRACE_MODE_*)
 * @func: name of the function that called us, used क्रम audit
 *
 * Returns 0 on access granted, -error on error
 */
अटल पूर्णांक smk_ptrace_rule_check(काष्ठा task_काष्ठा *tracer,
				 काष्ठा smack_known *tracee_known,
				 अचिन्हित पूर्णांक mode, स्थिर अक्षर *func)
अणु
	पूर्णांक rc;
	काष्ठा smk_audit_info ad, *saip = शून्य;
	काष्ठा task_smack *tsp;
	काष्ठा smack_known *tracer_known;
	स्थिर काष्ठा cred *tracercred;

	अगर ((mode & PTRACE_MODE_NOAUDIT) == 0) अणु
		smk_ad_init(&ad, func, LSM_AUDIT_DATA_TASK);
		smk_ad_setfield_u_tsk(&ad, tracer);
		saip = &ad;
	पूर्ण

	rcu_पढ़ो_lock();
	tracercred = __task_cred(tracer);
	tsp = smack_cred(tracercred);
	tracer_known = smk_of_task(tsp);

	अगर ((mode & PTRACE_MODE_ATTACH) &&
	    (smack_ptrace_rule == SMACK_PTRACE_EXACT ||
	     smack_ptrace_rule == SMACK_PTRACE_DRACONIAN)) अणु
		अगर (tracer_known->smk_known == tracee_known->smk_known)
			rc = 0;
		अन्यथा अगर (smack_ptrace_rule == SMACK_PTRACE_DRACONIAN)
			rc = -EACCES;
		अन्यथा अगर (smack_privileged_cred(CAP_SYS_PTRACE, tracercred))
			rc = 0;
		अन्यथा
			rc = -EACCES;

		अगर (saip)
			smack_log(tracer_known->smk_known,
				  tracee_known->smk_known,
				  0, rc, saip);

		rcu_पढ़ो_unlock();
		वापस rc;
	पूर्ण

	/* In हाल of rule==SMACK_PTRACE_DEFAULT or mode==PTRACE_MODE_READ */
	rc = smk_tskacc(tsp, tracee_known, smk_ptrace_mode(mode), saip);

	rcu_पढ़ो_unlock();
	वापस rc;
पूर्ण

/*
 * LSM hooks.
 * We he, that is fun!
 */

/**
 * smack_ptrace_access_check - Smack approval on PTRACE_ATTACH
 * @ctp: child task poपूर्णांकer
 * @mode: ptrace attachment mode (PTRACE_MODE_*)
 *
 * Returns 0 अगर access is OK, an error code otherwise
 *
 * Do the capability checks.
 */
अटल पूर्णांक smack_ptrace_access_check(काष्ठा task_काष्ठा *ctp, अचिन्हित पूर्णांक mode)
अणु
	काष्ठा smack_known *skp;

	skp = smk_of_task_काष्ठा_obj(ctp);

	वापस smk_ptrace_rule_check(current, skp, mode, __func__);
पूर्ण

/**
 * smack_ptrace_traceme - Smack approval on PTRACE_TRACEME
 * @ptp: parent task poपूर्णांकer
 *
 * Returns 0 अगर access is OK, an error code otherwise
 *
 * Do the capability checks, and require PTRACE_MODE_ATTACH.
 */
अटल पूर्णांक smack_ptrace_traceme(काष्ठा task_काष्ठा *ptp)
अणु
	पूर्णांक rc;
	काष्ठा smack_known *skp;

	skp = smk_of_task(smack_cred(current_cred()));

	rc = smk_ptrace_rule_check(ptp, skp, PTRACE_MODE_ATTACH, __func__);
	वापस rc;
पूर्ण

/**
 * smack_syslog - Smack approval on syslog
 * @typefrom_file: unused
 *
 * Returns 0 on success, error code otherwise.
 */
अटल पूर्णांक smack_syslog(पूर्णांक typefrom_file)
अणु
	पूर्णांक rc = 0;
	काष्ठा smack_known *skp = smk_of_current();

	अगर (smack_privileged(CAP_MAC_OVERRIDE))
		वापस 0;

	अगर (smack_syslog_label != शून्य && smack_syslog_label != skp)
		rc = -EACCES;

	वापस rc;
पूर्ण

/*
 * Superblock Hooks.
 */

/**
 * smack_sb_alloc_security - allocate a superblock blob
 * @sb: the superblock getting the blob
 *
 * Returns 0 on success or -ENOMEM on error.
 */
अटल पूर्णांक smack_sb_alloc_security(काष्ठा super_block *sb)
अणु
	काष्ठा superblock_smack *sbsp = smack_superblock(sb);

	sbsp->smk_root = &smack_known_न्यूनमान;
	sbsp->smk_शेष = &smack_known_न्यूनमान;
	sbsp->smk_न्यूनमान = &smack_known_न्यूनमान;
	sbsp->smk_hat = &smack_known_hat;
	/*
	 * SMK_SB_INITIALIZED will be zero from kzalloc.
	 */

	वापस 0;
पूर्ण

काष्ठा smack_mnt_opts अणु
	स्थिर अक्षर *fsशेष, *fsन्यूनमान, *fshat, *fsroot, *fstransmute;
पूर्ण;

अटल व्योम smack_मुक्त_mnt_opts(व्योम *mnt_opts)
अणु
	काष्ठा smack_mnt_opts *opts = mnt_opts;
	kमुक्त(opts->fsशेष);
	kमुक्त(opts->fsन्यूनमान);
	kमुक्त(opts->fshat);
	kमुक्त(opts->fsroot);
	kमुक्त(opts->fstransmute);
	kमुक्त(opts);
पूर्ण

अटल पूर्णांक smack_add_opt(पूर्णांक token, स्थिर अक्षर *s, व्योम **mnt_opts)
अणु
	काष्ठा smack_mnt_opts *opts = *mnt_opts;

	अगर (!opts) अणु
		opts = kzalloc(माप(काष्ठा smack_mnt_opts), GFP_KERNEL);
		अगर (!opts)
			वापस -ENOMEM;
		*mnt_opts = opts;
	पूर्ण
	अगर (!s)
		वापस -ENOMEM;

	चयन (token) अणु
	हाल Opt_fsशेष:
		अगर (opts->fsशेष)
			जाओ out_opt_err;
		opts->fsशेष = s;
		अवरोध;
	हाल Opt_fsन्यूनमान:
		अगर (opts->fsन्यूनमान)
			जाओ out_opt_err;
		opts->fsन्यूनमान = s;
		अवरोध;
	हाल Opt_fshat:
		अगर (opts->fshat)
			जाओ out_opt_err;
		opts->fshat = s;
		अवरोध;
	हाल Opt_fsroot:
		अगर (opts->fsroot)
			जाओ out_opt_err;
		opts->fsroot = s;
		अवरोध;
	हाल Opt_fstransmute:
		अगर (opts->fstransmute)
			जाओ out_opt_err;
		opts->fstransmute = s;
		अवरोध;
	पूर्ण
	वापस 0;

out_opt_err:
	pr_warn("Smack: duplicate mount options\n");
	वापस -EINVAL;
पूर्ण

/**
 * smack_fs_context_dup - Duplicate the security data on fs_context duplication
 * @fc: The new fileप्रणाली context.
 * @src_fc: The source fileप्रणाली context being duplicated.
 *
 * Returns 0 on success or -ENOMEM on error.
 */
अटल पूर्णांक smack_fs_context_dup(काष्ठा fs_context *fc,
				काष्ठा fs_context *src_fc)
अणु
	काष्ठा smack_mnt_opts *dst, *src = src_fc->security;

	अगर (!src)
		वापस 0;

	fc->security = kzalloc(माप(काष्ठा smack_mnt_opts), GFP_KERNEL);
	अगर (!fc->security)
		वापस -ENOMEM;
	dst = fc->security;

	अगर (src->fsशेष) अणु
		dst->fsशेष = kstrdup(src->fsशेष, GFP_KERNEL);
		अगर (!dst->fsशेष)
			वापस -ENOMEM;
	पूर्ण
	अगर (src->fsन्यूनमान) अणु
		dst->fsन्यूनमान = kstrdup(src->fsन्यूनमान, GFP_KERNEL);
		अगर (!dst->fsन्यूनमान)
			वापस -ENOMEM;
	पूर्ण
	अगर (src->fshat) अणु
		dst->fshat = kstrdup(src->fshat, GFP_KERNEL);
		अगर (!dst->fshat)
			वापस -ENOMEM;
	पूर्ण
	अगर (src->fsroot) अणु
		dst->fsroot = kstrdup(src->fsroot, GFP_KERNEL);
		अगर (!dst->fsroot)
			वापस -ENOMEM;
	पूर्ण
	अगर (src->fstransmute) अणु
		dst->fstransmute = kstrdup(src->fstransmute, GFP_KERNEL);
		अगर (!dst->fstransmute)
			वापस -ENOMEM;
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा fs_parameter_spec smack_fs_parameters[] = अणु
	fsparam_string("smackfsdef",		Opt_fsशेष),
	fsparam_string("smackfsdefault",	Opt_fsशेष),
	fsparam_string("smackfsfloor",		Opt_fsन्यूनमान),
	fsparam_string("smackfshat",		Opt_fshat),
	fsparam_string("smackfsroot",		Opt_fsroot),
	fsparam_string("smackfstransmute",	Opt_fstransmute),
	अणुपूर्ण
पूर्ण;

/**
 * smack_fs_context_parse_param - Parse a single mount parameter
 * @fc: The new fileप्रणाली context being स्थिरructed.
 * @param: The parameter.
 *
 * Returns 0 on success, -ENOPARAM to pass the parameter on or anything अन्यथा on
 * error.
 */
अटल पूर्णांक smack_fs_context_parse_param(काष्ठा fs_context *fc,
					काष्ठा fs_parameter *param)
अणु
	काष्ठा fs_parse_result result;
	पूर्णांक opt, rc;

	opt = fs_parse(fc, smack_fs_parameters, param, &result);
	अगर (opt < 0)
		वापस opt;

	rc = smack_add_opt(opt, param->string, &fc->security);
	अगर (!rc)
		param->string = शून्य;
	वापस rc;
पूर्ण

अटल पूर्णांक smack_sb_eat_lsm_opts(अक्षर *options, व्योम **mnt_opts)
अणु
	अक्षर *from = options, *to = options;
	bool first = true;

	जबतक (1) अणु
		अक्षर *next = म_अक्षर(from, ',');
		पूर्णांक token, len, rc;
		अक्षर *arg = शून्य;

		अगर (next)
			len = next - from;
		अन्यथा
			len = म_माप(from);

		token = match_opt_prefix(from, len, &arg);
		अगर (token != Opt_error) अणु
			arg = kmemdup_nul(arg, from + len - arg, GFP_KERNEL);
			rc = smack_add_opt(token, arg, mnt_opts);
			अगर (unlikely(rc)) अणु
				kमुक्त(arg);
				अगर (*mnt_opts)
					smack_मुक्त_mnt_opts(*mnt_opts);
				*mnt_opts = शून्य;
				वापस rc;
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (!first) अणु	// copy with preceding comma
				from--;
				len++;
			पूर्ण
			अगर (to != from)
				स_हटाओ(to, from, len);
			to += len;
			first = false;
		पूर्ण
		अगर (!from[len])
			अवरोध;
		from += len + 1;
	पूर्ण
	*to = '\0';
	वापस 0;
पूर्ण

/**
 * smack_set_mnt_opts - set Smack specअगरic mount options
 * @sb: the file प्रणाली superblock
 * @mnt_opts: Smack mount options
 * @kern_flags: mount option from kernel space or user space
 * @set_kern_flags: where to store converted mount opts
 *
 * Returns 0 on success, an error code on failure
 *
 * Allow fileप्रणालीs with binary mount data to explicitly set Smack mount
 * labels.
 */
अटल पूर्णांक smack_set_mnt_opts(काष्ठा super_block *sb,
		व्योम *mnt_opts,
		अचिन्हित दीर्घ kern_flags,
		अचिन्हित दीर्घ *set_kern_flags)
अणु
	काष्ठा dentry *root = sb->s_root;
	काष्ठा inode *inode = d_backing_inode(root);
	काष्ठा superblock_smack *sp = smack_superblock(sb);
	काष्ठा inode_smack *isp;
	काष्ठा smack_known *skp;
	काष्ठा smack_mnt_opts *opts = mnt_opts;
	bool transmute = false;

	अगर (sp->smk_flags & SMK_SB_INITIALIZED)
		वापस 0;

	अगर (inode->i_security == शून्य) अणु
		पूर्णांक rc = lsm_inode_alloc(inode);

		अगर (rc)
			वापस rc;
	पूर्ण

	अगर (!smack_privileged(CAP_MAC_ADMIN)) अणु
		/*
		 * Unprivileged mounts करोn't get to specअगरy Smack values.
		 */
		अगर (opts)
			वापस -EPERM;
		/*
		 * Unprivileged mounts get root and शेष from the caller.
		 */
		skp = smk_of_current();
		sp->smk_root = skp;
		sp->smk_शेष = skp;
		/*
		 * For a handful of fs types with no user-controlled
		 * backing store it's okay to trust security labels
		 * in the fileप्रणाली. The rest are untrusted.
		 */
		अगर (sb->s_user_ns != &init_user_ns &&
		    sb->s_magic != SYSFS_MAGIC && sb->s_magic != TMPFS_MAGIC &&
		    sb->s_magic != RAMFS_MAGIC) अणु
			transmute = true;
			sp->smk_flags |= SMK_SB_UNTRUSTED;
		पूर्ण
	पूर्ण

	sp->smk_flags |= SMK_SB_INITIALIZED;

	अगर (opts) अणु
		अगर (opts->fsशेष) अणु
			skp = smk_import_entry(opts->fsशेष, 0);
			अगर (IS_ERR(skp))
				वापस PTR_ERR(skp);
			sp->smk_शेष = skp;
		पूर्ण
		अगर (opts->fsन्यूनमान) अणु
			skp = smk_import_entry(opts->fsन्यूनमान, 0);
			अगर (IS_ERR(skp))
				वापस PTR_ERR(skp);
			sp->smk_न्यूनमान = skp;
		पूर्ण
		अगर (opts->fshat) अणु
			skp = smk_import_entry(opts->fshat, 0);
			अगर (IS_ERR(skp))
				वापस PTR_ERR(skp);
			sp->smk_hat = skp;
		पूर्ण
		अगर (opts->fsroot) अणु
			skp = smk_import_entry(opts->fsroot, 0);
			अगर (IS_ERR(skp))
				वापस PTR_ERR(skp);
			sp->smk_root = skp;
		पूर्ण
		अगर (opts->fstransmute) अणु
			skp = smk_import_entry(opts->fstransmute, 0);
			अगर (IS_ERR(skp))
				वापस PTR_ERR(skp);
			sp->smk_root = skp;
			transmute = true;
		पूर्ण
	पूर्ण

	/*
	 * Initialize the root inode.
	 */
	init_inode_smack(inode, sp->smk_root);

	अगर (transmute) अणु
		isp = smack_inode(inode);
		isp->smk_flags |= SMK_INODE_TRANSMUTE;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * smack_sb_statfs - Smack check on statfs
 * @dentry: identअगरies the file प्रणाली in question
 *
 * Returns 0 अगर current can पढ़ो the न्यूनमान of the fileप्रणाली,
 * and error code otherwise
 */
अटल पूर्णांक smack_sb_statfs(काष्ठा dentry *dentry)
अणु
	काष्ठा superblock_smack *sbp = smack_superblock(dentry->d_sb);
	पूर्णांक rc;
	काष्ठा smk_audit_info ad;

	smk_ad_init(&ad, __func__, LSM_AUDIT_DATA_DENTRY);
	smk_ad_setfield_u_fs_path_dentry(&ad, dentry);

	rc = smk_curacc(sbp->smk_न्यूनमान, MAY_READ, &ad);
	rc = smk_bu_current("statfs", sbp->smk_न्यूनमान, MAY_READ, rc);
	वापस rc;
पूर्ण

/*
 * BPRM hooks
 */

/**
 * smack_bprm_creds_क्रम_exec - Update bprm->cred अगर needed क्रम exec
 * @bprm: the exec inक्रमmation
 *
 * Returns 0 अगर it माला_लो a blob, -EPERM अगर exec क्रमbidden and -ENOMEM otherwise
 */
अटल पूर्णांक smack_bprm_creds_क्रम_exec(काष्ठा linux_binprm *bprm)
अणु
	काष्ठा inode *inode = file_inode(bprm->file);
	काष्ठा task_smack *bsp = smack_cred(bprm->cred);
	काष्ठा inode_smack *isp;
	काष्ठा superblock_smack *sbsp;
	पूर्णांक rc;

	isp = smack_inode(inode);
	अगर (isp->smk_task == शून्य || isp->smk_task == bsp->smk_task)
		वापस 0;

	sbsp = smack_superblock(inode->i_sb);
	अगर ((sbsp->smk_flags & SMK_SB_UNTRUSTED) &&
	    isp->smk_task != sbsp->smk_root)
		वापस 0;

	अगर (bprm->unsafe & LSM_UNSAFE_PTRACE) अणु
		काष्ठा task_काष्ठा *tracer;
		rc = 0;

		rcu_पढ़ो_lock();
		tracer = ptrace_parent(current);
		अगर (likely(tracer != शून्य))
			rc = smk_ptrace_rule_check(tracer,
						   isp->smk_task,
						   PTRACE_MODE_ATTACH,
						   __func__);
		rcu_पढ़ो_unlock();

		अगर (rc != 0)
			वापस rc;
	पूर्ण
	अगर (bprm->unsafe & ~LSM_UNSAFE_PTRACE)
		वापस -EPERM;

	bsp->smk_task = isp->smk_task;
	bprm->per_clear |= PER_CLEAR_ON_SETID;

	/* Decide अगर this is a secure exec. */
	अगर (bsp->smk_task != bsp->smk_विभाजनed)
		bprm->secureexec = 1;

	वापस 0;
पूर्ण

/*
 * Inode hooks
 */

/**
 * smack_inode_alloc_security - allocate an inode blob
 * @inode: the inode in need of a blob
 *
 * Returns 0
 */
अटल पूर्णांक smack_inode_alloc_security(काष्ठा inode *inode)
अणु
	काष्ठा smack_known *skp = smk_of_current();

	init_inode_smack(inode, skp);
	वापस 0;
पूर्ण

/**
 * smack_inode_init_security - copy out the smack from an inode
 * @inode: the newly created inode
 * @dir: containing directory object
 * @qstr: unused
 * @name: where to put the attribute name
 * @value: where to put the attribute value
 * @len: where to put the length of the attribute
 *
 * Returns 0 अगर it all works out, -ENOMEM अगर there's no memory
 */
अटल पूर्णांक smack_inode_init_security(काष्ठा inode *inode, काष्ठा inode *dir,
				     स्थिर काष्ठा qstr *qstr, स्थिर अक्षर **name,
				     व्योम **value, माप_प्रकार *len)
अणु
	काष्ठा inode_smack *issp = smack_inode(inode);
	काष्ठा smack_known *skp = smk_of_current();
	काष्ठा smack_known *isp = smk_of_inode(inode);
	काष्ठा smack_known *dsp = smk_of_inode(dir);
	पूर्णांक may;

	अगर (name)
		*name = XATTR_SMACK_SUFFIX;

	अगर (value && len) अणु
		rcu_पढ़ो_lock();
		may = smk_access_entry(skp->smk_known, dsp->smk_known,
				       &skp->smk_rules);
		rcu_पढ़ो_unlock();

		/*
		 * If the access rule allows transmutation and
		 * the directory requests transmutation then
		 * by all means transmute.
		 * Mark the inode as changed.
		 */
		अगर (may > 0 && ((may & MAY_TRANSMUTE) != 0) &&
		    smk_inode_transmutable(dir)) अणु
			isp = dsp;
			issp->smk_flags |= SMK_INODE_CHANGED;
		पूर्ण

		*value = kstrdup(isp->smk_known, GFP_NOFS);
		अगर (*value == शून्य)
			वापस -ENOMEM;

		*len = म_माप(isp->smk_known);
	पूर्ण

	वापस 0;
पूर्ण

/**
 * smack_inode_link - Smack check on link
 * @old_dentry: the existing object
 * @dir: unused
 * @new_dentry: the new object
 *
 * Returns 0 अगर access is permitted, an error code otherwise
 */
अटल पूर्णांक smack_inode_link(काष्ठा dentry *old_dentry, काष्ठा inode *dir,
			    काष्ठा dentry *new_dentry)
अणु
	काष्ठा smack_known *isp;
	काष्ठा smk_audit_info ad;
	पूर्णांक rc;

	smk_ad_init(&ad, __func__, LSM_AUDIT_DATA_DENTRY);
	smk_ad_setfield_u_fs_path_dentry(&ad, old_dentry);

	isp = smk_of_inode(d_backing_inode(old_dentry));
	rc = smk_curacc(isp, MAY_WRITE, &ad);
	rc = smk_bu_inode(d_backing_inode(old_dentry), MAY_WRITE, rc);

	अगर (rc == 0 && d_is_positive(new_dentry)) अणु
		isp = smk_of_inode(d_backing_inode(new_dentry));
		smk_ad_setfield_u_fs_path_dentry(&ad, new_dentry);
		rc = smk_curacc(isp, MAY_WRITE, &ad);
		rc = smk_bu_inode(d_backing_inode(new_dentry), MAY_WRITE, rc);
	पूर्ण

	वापस rc;
पूर्ण

/**
 * smack_inode_unlink - Smack check on inode deletion
 * @dir: containing directory object
 * @dentry: file to unlink
 *
 * Returns 0 अगर current can ग_लिखो the containing directory
 * and the object, error code otherwise
 */
अटल पूर्णांक smack_inode_unlink(काष्ठा inode *dir, काष्ठा dentry *dentry)
अणु
	काष्ठा inode *ip = d_backing_inode(dentry);
	काष्ठा smk_audit_info ad;
	पूर्णांक rc;

	smk_ad_init(&ad, __func__, LSM_AUDIT_DATA_DENTRY);
	smk_ad_setfield_u_fs_path_dentry(&ad, dentry);

	/*
	 * You need ग_लिखो access to the thing you're unlinking
	 */
	rc = smk_curacc(smk_of_inode(ip), MAY_WRITE, &ad);
	rc = smk_bu_inode(ip, MAY_WRITE, rc);
	अगर (rc == 0) अणु
		/*
		 * You also need ग_लिखो access to the containing directory
		 */
		smk_ad_init(&ad, __func__, LSM_AUDIT_DATA_INODE);
		smk_ad_setfield_u_fs_inode(&ad, dir);
		rc = smk_curacc(smk_of_inode(dir), MAY_WRITE, &ad);
		rc = smk_bu_inode(dir, MAY_WRITE, rc);
	पूर्ण
	वापस rc;
पूर्ण

/**
 * smack_inode_सूची_हटाओ - Smack check on directory deletion
 * @dir: containing directory object
 * @dentry: directory to unlink
 *
 * Returns 0 अगर current can ग_लिखो the containing directory
 * and the directory, error code otherwise
 */
अटल पूर्णांक smack_inode_सूची_हटाओ(काष्ठा inode *dir, काष्ठा dentry *dentry)
अणु
	काष्ठा smk_audit_info ad;
	पूर्णांक rc;

	smk_ad_init(&ad, __func__, LSM_AUDIT_DATA_DENTRY);
	smk_ad_setfield_u_fs_path_dentry(&ad, dentry);

	/*
	 * You need ग_लिखो access to the thing you're removing
	 */
	rc = smk_curacc(smk_of_inode(d_backing_inode(dentry)), MAY_WRITE, &ad);
	rc = smk_bu_inode(d_backing_inode(dentry), MAY_WRITE, rc);
	अगर (rc == 0) अणु
		/*
		 * You also need ग_लिखो access to the containing directory
		 */
		smk_ad_init(&ad, __func__, LSM_AUDIT_DATA_INODE);
		smk_ad_setfield_u_fs_inode(&ad, dir);
		rc = smk_curacc(smk_of_inode(dir), MAY_WRITE, &ad);
		rc = smk_bu_inode(dir, MAY_WRITE, rc);
	पूर्ण

	वापस rc;
पूर्ण

/**
 * smack_inode_नाम - Smack check on नाम
 * @old_inode: unused
 * @old_dentry: the old object
 * @new_inode: unused
 * @new_dentry: the new object
 *
 * Read and ग_लिखो access is required on both the old and
 * new directories.
 *
 * Returns 0 अगर access is permitted, an error code otherwise
 */
अटल पूर्णांक smack_inode_नाम(काष्ठा inode *old_inode,
			      काष्ठा dentry *old_dentry,
			      काष्ठा inode *new_inode,
			      काष्ठा dentry *new_dentry)
अणु
	पूर्णांक rc;
	काष्ठा smack_known *isp;
	काष्ठा smk_audit_info ad;

	smk_ad_init(&ad, __func__, LSM_AUDIT_DATA_DENTRY);
	smk_ad_setfield_u_fs_path_dentry(&ad, old_dentry);

	isp = smk_of_inode(d_backing_inode(old_dentry));
	rc = smk_curacc(isp, MAY_READWRITE, &ad);
	rc = smk_bu_inode(d_backing_inode(old_dentry), MAY_READWRITE, rc);

	अगर (rc == 0 && d_is_positive(new_dentry)) अणु
		isp = smk_of_inode(d_backing_inode(new_dentry));
		smk_ad_setfield_u_fs_path_dentry(&ad, new_dentry);
		rc = smk_curacc(isp, MAY_READWRITE, &ad);
		rc = smk_bu_inode(d_backing_inode(new_dentry), MAY_READWRITE, rc);
	पूर्ण
	वापस rc;
पूर्ण

/**
 * smack_inode_permission - Smack version of permission()
 * @inode: the inode in question
 * @mask: the access requested
 *
 * This is the important Smack hook.
 *
 * Returns 0 अगर access is permitted, an error code otherwise
 */
अटल पूर्णांक smack_inode_permission(काष्ठा inode *inode, पूर्णांक mask)
अणु
	काष्ठा superblock_smack *sbsp = smack_superblock(inode->i_sb);
	काष्ठा smk_audit_info ad;
	पूर्णांक no_block = mask & MAY_NOT_BLOCK;
	पूर्णांक rc;

	mask &= (MAY_READ|MAY_WRITE|MAY_EXEC|MAY_APPEND);
	/*
	 * No permission to check. Existence test. Yup, it's there.
	 */
	अगर (mask == 0)
		वापस 0;

	अगर (sbsp->smk_flags & SMK_SB_UNTRUSTED) अणु
		अगर (smk_of_inode(inode) != sbsp->smk_root)
			वापस -EACCES;
	पूर्ण

	/* May be droppable after audit */
	अगर (no_block)
		वापस -ECHILD;
	smk_ad_init(&ad, __func__, LSM_AUDIT_DATA_INODE);
	smk_ad_setfield_u_fs_inode(&ad, inode);
	rc = smk_curacc(smk_of_inode(inode), mask, &ad);
	rc = smk_bu_inode(inode, mask, rc);
	वापस rc;
पूर्ण

/**
 * smack_inode_setattr - Smack check क्रम setting attributes
 * @dentry: the object
 * @iattr: क्रम the क्रमce flag
 *
 * Returns 0 अगर access is permitted, an error code otherwise
 */
अटल पूर्णांक smack_inode_setattr(काष्ठा dentry *dentry, काष्ठा iattr *iattr)
अणु
	काष्ठा smk_audit_info ad;
	पूर्णांक rc;

	/*
	 * Need to allow क्रम clearing the setuid bit.
	 */
	अगर (iattr->ia_valid & ATTR_FORCE)
		वापस 0;
	smk_ad_init(&ad, __func__, LSM_AUDIT_DATA_DENTRY);
	smk_ad_setfield_u_fs_path_dentry(&ad, dentry);

	rc = smk_curacc(smk_of_inode(d_backing_inode(dentry)), MAY_WRITE, &ad);
	rc = smk_bu_inode(d_backing_inode(dentry), MAY_WRITE, rc);
	वापस rc;
पूर्ण

/**
 * smack_inode_getattr - Smack check क्रम getting attributes
 * @path: path to extract the info from
 *
 * Returns 0 अगर access is permitted, an error code otherwise
 */
अटल पूर्णांक smack_inode_getattr(स्थिर काष्ठा path *path)
अणु
	काष्ठा smk_audit_info ad;
	काष्ठा inode *inode = d_backing_inode(path->dentry);
	पूर्णांक rc;

	smk_ad_init(&ad, __func__, LSM_AUDIT_DATA_PATH);
	smk_ad_setfield_u_fs_path(&ad, *path);
	rc = smk_curacc(smk_of_inode(inode), MAY_READ, &ad);
	rc = smk_bu_inode(inode, MAY_READ, rc);
	वापस rc;
पूर्ण

/**
 * smack_inode_setxattr - Smack check क्रम setting xattrs
 * @dentry: the object
 * @name: name of the attribute
 * @value: value of the attribute
 * @size: size of the value
 * @flags: unused
 *
 * This protects the Smack attribute explicitly.
 *
 * Returns 0 अगर access is permitted, an error code otherwise
 */
अटल पूर्णांक smack_inode_setxattr(काष्ठा user_namespace *mnt_userns,
				काष्ठा dentry *dentry, स्थिर अक्षर *name,
				स्थिर व्योम *value, माप_प्रकार size, पूर्णांक flags)
अणु
	काष्ठा smk_audit_info ad;
	काष्ठा smack_known *skp;
	पूर्णांक check_priv = 0;
	पूर्णांक check_import = 0;
	पूर्णांक check_star = 0;
	पूर्णांक rc = 0;

	/*
	 * Check label validity here so import won't fail in post_setxattr
	 */
	अगर (म_भेद(name, XATTR_NAME_SMACK) == 0 ||
	    म_भेद(name, XATTR_NAME_SMACKIPIN) == 0 ||
	    म_भेद(name, XATTR_NAME_SMACKIPOUT) == 0) अणु
		check_priv = 1;
		check_import = 1;
	पूर्ण अन्यथा अगर (म_भेद(name, XATTR_NAME_SMACKEXEC) == 0 ||
		   म_भेद(name, XATTR_NAME_SMACKMMAP) == 0) अणु
		check_priv = 1;
		check_import = 1;
		check_star = 1;
	पूर्ण अन्यथा अगर (म_भेद(name, XATTR_NAME_SMACKTRANSMUTE) == 0) अणु
		check_priv = 1;
		अगर (size != TRANS_TRUE_SIZE ||
		    म_भेदन(value, TRANS_TRUE, TRANS_TRUE_SIZE) != 0)
			rc = -EINVAL;
	पूर्ण अन्यथा
		rc = cap_inode_setxattr(dentry, name, value, size, flags);

	अगर (check_priv && !smack_privileged(CAP_MAC_ADMIN))
		rc = -EPERM;

	अगर (rc == 0 && check_import) अणु
		skp = size ? smk_import_entry(value, size) : शून्य;
		अगर (IS_ERR(skp))
			rc = PTR_ERR(skp);
		अन्यथा अगर (skp == शून्य || (check_star &&
		    (skp == &smack_known_star || skp == &smack_known_web)))
			rc = -EINVAL;
	पूर्ण

	smk_ad_init(&ad, __func__, LSM_AUDIT_DATA_DENTRY);
	smk_ad_setfield_u_fs_path_dentry(&ad, dentry);

	अगर (rc == 0) अणु
		rc = smk_curacc(smk_of_inode(d_backing_inode(dentry)), MAY_WRITE, &ad);
		rc = smk_bu_inode(d_backing_inode(dentry), MAY_WRITE, rc);
	पूर्ण

	वापस rc;
पूर्ण

/**
 * smack_inode_post_setxattr - Apply the Smack update approved above
 * @dentry: object
 * @name: attribute name
 * @value: attribute value
 * @size: attribute size
 * @flags: unused
 *
 * Set the poपूर्णांकer in the inode blob to the entry found
 * in the master label list.
 */
अटल व्योम smack_inode_post_setxattr(काष्ठा dentry *dentry, स्थिर अक्षर *name,
				      स्थिर व्योम *value, माप_प्रकार size, पूर्णांक flags)
अणु
	काष्ठा smack_known *skp;
	काष्ठा inode_smack *isp = smack_inode(d_backing_inode(dentry));

	अगर (म_भेद(name, XATTR_NAME_SMACKTRANSMUTE) == 0) अणु
		isp->smk_flags |= SMK_INODE_TRANSMUTE;
		वापस;
	पूर्ण

	अगर (म_भेद(name, XATTR_NAME_SMACK) == 0) अणु
		skp = smk_import_entry(value, size);
		अगर (!IS_ERR(skp))
			isp->smk_inode = skp;
	पूर्ण अन्यथा अगर (म_भेद(name, XATTR_NAME_SMACKEXEC) == 0) अणु
		skp = smk_import_entry(value, size);
		अगर (!IS_ERR(skp))
			isp->smk_task = skp;
	पूर्ण अन्यथा अगर (म_भेद(name, XATTR_NAME_SMACKMMAP) == 0) अणु
		skp = smk_import_entry(value, size);
		अगर (!IS_ERR(skp))
			isp->smk_mmap = skp;
	पूर्ण

	वापस;
पूर्ण

/**
 * smack_inode_getxattr - Smack check on getxattr
 * @dentry: the object
 * @name: unused
 *
 * Returns 0 अगर access is permitted, an error code otherwise
 */
अटल पूर्णांक smack_inode_getxattr(काष्ठा dentry *dentry, स्थिर अक्षर *name)
अणु
	काष्ठा smk_audit_info ad;
	पूर्णांक rc;

	smk_ad_init(&ad, __func__, LSM_AUDIT_DATA_DENTRY);
	smk_ad_setfield_u_fs_path_dentry(&ad, dentry);

	rc = smk_curacc(smk_of_inode(d_backing_inode(dentry)), MAY_READ, &ad);
	rc = smk_bu_inode(d_backing_inode(dentry), MAY_READ, rc);
	वापस rc;
पूर्ण

/**
 * smack_inode_हटाओxattr - Smack check on हटाओxattr
 * @dentry: the object
 * @name: name of the attribute
 *
 * Removing the Smack attribute requires CAP_MAC_ADMIN
 *
 * Returns 0 अगर access is permitted, an error code otherwise
 */
अटल पूर्णांक smack_inode_हटाओxattr(काष्ठा user_namespace *mnt_userns,
				   काष्ठा dentry *dentry, स्थिर अक्षर *name)
अणु
	काष्ठा inode_smack *isp;
	काष्ठा smk_audit_info ad;
	पूर्णांक rc = 0;

	अगर (म_भेद(name, XATTR_NAME_SMACK) == 0 ||
	    म_भेद(name, XATTR_NAME_SMACKIPIN) == 0 ||
	    म_भेद(name, XATTR_NAME_SMACKIPOUT) == 0 ||
	    म_भेद(name, XATTR_NAME_SMACKEXEC) == 0 ||
	    म_भेद(name, XATTR_NAME_SMACKTRANSMUTE) == 0 ||
	    म_भेद(name, XATTR_NAME_SMACKMMAP) == 0) अणु
		अगर (!smack_privileged(CAP_MAC_ADMIN))
			rc = -EPERM;
	पूर्ण अन्यथा
		rc = cap_inode_हटाओxattr(mnt_userns, dentry, name);

	अगर (rc != 0)
		वापस rc;

	smk_ad_init(&ad, __func__, LSM_AUDIT_DATA_DENTRY);
	smk_ad_setfield_u_fs_path_dentry(&ad, dentry);

	rc = smk_curacc(smk_of_inode(d_backing_inode(dentry)), MAY_WRITE, &ad);
	rc = smk_bu_inode(d_backing_inode(dentry), MAY_WRITE, rc);
	अगर (rc != 0)
		वापस rc;

	isp = smack_inode(d_backing_inode(dentry));
	/*
	 * Don't करो anything special क्रम these.
	 *	XATTR_NAME_SMACKIPIN
	 *	XATTR_NAME_SMACKIPOUT
	 */
	अगर (म_भेद(name, XATTR_NAME_SMACK) == 0) अणु
		काष्ठा super_block *sbp = dentry->d_sb;
		काष्ठा superblock_smack *sbsp = smack_superblock(sbp);

		isp->smk_inode = sbsp->smk_शेष;
	पूर्ण अन्यथा अगर (म_भेद(name, XATTR_NAME_SMACKEXEC) == 0)
		isp->smk_task = शून्य;
	अन्यथा अगर (म_भेद(name, XATTR_NAME_SMACKMMAP) == 0)
		isp->smk_mmap = शून्य;
	अन्यथा अगर (म_भेद(name, XATTR_NAME_SMACKTRANSMUTE) == 0)
		isp->smk_flags &= ~SMK_INODE_TRANSMUTE;

	वापस 0;
पूर्ण

/**
 * smack_inode_माला_लोecurity - get smack xattrs
 * @inode: the object
 * @name: attribute name
 * @buffer: where to put the result
 * @alloc: duplicate memory
 *
 * Returns the size of the attribute or an error code
 */
अटल पूर्णांक smack_inode_माला_लोecurity(काष्ठा user_namespace *mnt_userns,
				   काष्ठा inode *inode, स्थिर अक्षर *name,
				   व्योम **buffer, bool alloc)
अणु
	काष्ठा socket_smack *ssp;
	काष्ठा socket *sock;
	काष्ठा super_block *sbp;
	काष्ठा inode *ip = (काष्ठा inode *)inode;
	काष्ठा smack_known *isp;

	अगर (म_भेद(name, XATTR_SMACK_SUFFIX) == 0)
		isp = smk_of_inode(inode);
	अन्यथा अणु
		/*
		 * The rest of the Smack xattrs are only on sockets.
		 */
		sbp = ip->i_sb;
		अगर (sbp->s_magic != SOCKFS_MAGIC)
			वापस -EOPNOTSUPP;

		sock = SOCKET_I(ip);
		अगर (sock == शून्य || sock->sk == शून्य)
			वापस -EOPNOTSUPP;

		ssp = sock->sk->sk_security;

		अगर (म_भेद(name, XATTR_SMACK_IPIN) == 0)
			isp = ssp->smk_in;
		अन्यथा अगर (म_भेद(name, XATTR_SMACK_IPOUT) == 0)
			isp = ssp->smk_out;
		अन्यथा
			वापस -EOPNOTSUPP;
	पूर्ण

	अगर (alloc) अणु
		*buffer = kstrdup(isp->smk_known, GFP_KERNEL);
		अगर (*buffer == शून्य)
			वापस -ENOMEM;
	पूर्ण

	वापस म_माप(isp->smk_known);
पूर्ण


/**
 * smack_inode_listsecurity - list the Smack attributes
 * @inode: the object
 * @buffer: where they go
 * @buffer_size: size of buffer
 */
अटल पूर्णांक smack_inode_listsecurity(काष्ठा inode *inode, अक्षर *buffer,
				    माप_प्रकार buffer_size)
अणु
	पूर्णांक len = माप(XATTR_NAME_SMACK);

	अगर (buffer != शून्य && len <= buffer_size)
		स_नकल(buffer, XATTR_NAME_SMACK, len);

	वापस len;
पूर्ण

/**
 * smack_inode_माला_लोecid - Extract inode's security id
 * @inode: inode to extract the info from
 * @secid: where result will be saved
 */
अटल व्योम smack_inode_माला_लोecid(काष्ठा inode *inode, u32 *secid)
अणु
	काष्ठा smack_known *skp = smk_of_inode(inode);

	*secid = skp->smk_secid;
पूर्ण

/*
 * File Hooks
 */

/*
 * There is no smack_file_permission hook
 *
 * Should access checks be करोne on each पढ़ो or ग_लिखो?
 * UNICOS and SELinux say yes.
 * Trusted Solaris, Trusted Irix, and just about everyone अन्यथा says no.
 *
 * I'll say no क्रम now. Smack करोes not करो the frequent
 * label changing that SELinux करोes.
 */

/**
 * smack_file_alloc_security - assign a file security blob
 * @file: the object
 *
 * The security blob क्रम a file is a poपूर्णांकer to the master
 * label list, so no allocation is करोne.
 *
 * f_security is the owner security inक्रमmation. It
 * isn't used on file access checks, it's क्रम send_sigio.
 *
 * Returns 0
 */
अटल पूर्णांक smack_file_alloc_security(काष्ठा file *file)
अणु
	काष्ठा smack_known **blob = smack_file(file);

	*blob = smk_of_current();
	वापस 0;
पूर्ण

/**
 * smack_file_ioctl - Smack check on ioctls
 * @file: the object
 * @cmd: what to करो
 * @arg: unused
 *
 * Relies heavily on the correct use of the ioctl command conventions.
 *
 * Returns 0 अगर allowed, error code otherwise
 */
अटल पूर्णांक smack_file_ioctl(काष्ठा file *file, अचिन्हित पूर्णांक cmd,
			    अचिन्हित दीर्घ arg)
अणु
	पूर्णांक rc = 0;
	काष्ठा smk_audit_info ad;
	काष्ठा inode *inode = file_inode(file);

	अगर (unlikely(IS_PRIVATE(inode)))
		वापस 0;

	smk_ad_init(&ad, __func__, LSM_AUDIT_DATA_PATH);
	smk_ad_setfield_u_fs_path(&ad, file->f_path);

	अगर (_IOC_सूची(cmd) & _IOC_WRITE) अणु
		rc = smk_curacc(smk_of_inode(inode), MAY_WRITE, &ad);
		rc = smk_bu_file(file, MAY_WRITE, rc);
	पूर्ण

	अगर (rc == 0 && (_IOC_सूची(cmd) & _IOC_READ)) अणु
		rc = smk_curacc(smk_of_inode(inode), MAY_READ, &ad);
		rc = smk_bu_file(file, MAY_READ, rc);
	पूर्ण

	वापस rc;
पूर्ण

/**
 * smack_file_lock - Smack check on file locking
 * @file: the object
 * @cmd: unused
 *
 * Returns 0 अगर current has lock access, error code otherwise
 */
अटल पूर्णांक smack_file_lock(काष्ठा file *file, अचिन्हित पूर्णांक cmd)
अणु
	काष्ठा smk_audit_info ad;
	पूर्णांक rc;
	काष्ठा inode *inode = file_inode(file);

	अगर (unlikely(IS_PRIVATE(inode)))
		वापस 0;

	smk_ad_init(&ad, __func__, LSM_AUDIT_DATA_PATH);
	smk_ad_setfield_u_fs_path(&ad, file->f_path);
	rc = smk_curacc(smk_of_inode(inode), MAY_LOCK, &ad);
	rc = smk_bu_file(file, MAY_LOCK, rc);
	वापस rc;
पूर्ण

/**
 * smack_file_fcntl - Smack check on fcntl
 * @file: the object
 * @cmd: what action to check
 * @arg: unused
 *
 * Generally these operations are harmless.
 * File locking operations present an obvious mechanism
 * क्रम passing inक्रमmation, so they require ग_लिखो access.
 *
 * Returns 0 अगर current has access, error code otherwise
 */
अटल पूर्णांक smack_file_fcntl(काष्ठा file *file, अचिन्हित पूर्णांक cmd,
			    अचिन्हित दीर्घ arg)
अणु
	काष्ठा smk_audit_info ad;
	पूर्णांक rc = 0;
	काष्ठा inode *inode = file_inode(file);

	अगर (unlikely(IS_PRIVATE(inode)))
		वापस 0;

	चयन (cmd) अणु
	हाल F_GETLK:
		अवरोध;
	हाल F_SETLK:
	हाल F_SETLKW:
		smk_ad_init(&ad, __func__, LSM_AUDIT_DATA_PATH);
		smk_ad_setfield_u_fs_path(&ad, file->f_path);
		rc = smk_curacc(smk_of_inode(inode), MAY_LOCK, &ad);
		rc = smk_bu_file(file, MAY_LOCK, rc);
		अवरोध;
	हाल F_SETOWN:
	हाल F_SETSIG:
		smk_ad_init(&ad, __func__, LSM_AUDIT_DATA_PATH);
		smk_ad_setfield_u_fs_path(&ad, file->f_path);
		rc = smk_curacc(smk_of_inode(inode), MAY_WRITE, &ad);
		rc = smk_bu_file(file, MAY_WRITE, rc);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस rc;
पूर्ण

/**
 * smack_mmap_file :
 * Check permissions क्रम a mmap operation.  The @file may be शून्य, e.g.
 * अगर mapping anonymous memory.
 * @file contains the file काष्ठाure क्रम file to map (may be शून्य).
 * @reqprot contains the protection requested by the application.
 * @prot contains the protection that will be applied by the kernel.
 * @flags contains the operational flags.
 * Return 0 अगर permission is granted.
 */
अटल पूर्णांक smack_mmap_file(काष्ठा file *file,
			   अचिन्हित दीर्घ reqprot, अचिन्हित दीर्घ prot,
			   अचिन्हित दीर्घ flags)
अणु
	काष्ठा smack_known *skp;
	काष्ठा smack_known *mkp;
	काष्ठा smack_rule *srp;
	काष्ठा task_smack *tsp;
	काष्ठा smack_known *okp;
	काष्ठा inode_smack *isp;
	काष्ठा superblock_smack *sbsp;
	पूर्णांक may;
	पूर्णांक mmay;
	पूर्णांक पंचांगay;
	पूर्णांक rc;

	अगर (file == शून्य)
		वापस 0;

	अगर (unlikely(IS_PRIVATE(file_inode(file))))
		वापस 0;

	isp = smack_inode(file_inode(file));
	अगर (isp->smk_mmap == शून्य)
		वापस 0;
	sbsp = smack_superblock(file_inode(file)->i_sb);
	अगर (sbsp->smk_flags & SMK_SB_UNTRUSTED &&
	    isp->smk_mmap != sbsp->smk_root)
		वापस -EACCES;
	mkp = isp->smk_mmap;

	tsp = smack_cred(current_cred());
	skp = smk_of_current();
	rc = 0;

	rcu_पढ़ो_lock();
	/*
	 * For each Smack rule associated with the subject
	 * label verअगरy that the SMACK64MMAP also has access
	 * to that rule's object label.
	 */
	list_क्रम_each_entry_rcu(srp, &skp->smk_rules, list) अणु
		okp = srp->smk_object;
		/*
		 * Matching labels always allows access.
		 */
		अगर (mkp->smk_known == okp->smk_known)
			जारी;
		/*
		 * If there is a matching local rule take
		 * that पूर्णांकo account as well.
		 */
		may = smk_access_entry(srp->smk_subject->smk_known,
				       okp->smk_known,
				       &tsp->smk_rules);
		अगर (may == -ENOENT)
			may = srp->smk_access;
		अन्यथा
			may &= srp->smk_access;
		/*
		 * If may is zero the SMACK64MMAP subject can't
		 * possibly have less access.
		 */
		अगर (may == 0)
			जारी;

		/*
		 * Fetch the global list entry.
		 * If there isn't one a SMACK64MMAP subject
		 * can't have as much access as current.
		 */
		mmay = smk_access_entry(mkp->smk_known, okp->smk_known,
					&mkp->smk_rules);
		अगर (mmay == -ENOENT) अणु
			rc = -EACCES;
			अवरोध;
		पूर्ण
		/*
		 * If there is a local entry it modअगरies the
		 * potential access, too.
		 */
		पंचांगay = smk_access_entry(mkp->smk_known, okp->smk_known,
					&tsp->smk_rules);
		अगर (पंचांगay != -ENOENT)
			mmay &= पंचांगay;

		/*
		 * If there is any access available to current that is
		 * not available to a SMACK64MMAP subject
		 * deny access.
		 */
		अगर ((may | mmay) != mmay) अणु
			rc = -EACCES;
			अवरोध;
		पूर्ण
	पूर्ण

	rcu_पढ़ो_unlock();

	वापस rc;
पूर्ण

/**
 * smack_file_set_fowner - set the file security blob value
 * @file: object in question
 *
 */
अटल व्योम smack_file_set_fowner(काष्ठा file *file)
अणु
	काष्ठा smack_known **blob = smack_file(file);

	*blob = smk_of_current();
पूर्ण

/**
 * smack_file_send_sigiotask - Smack on sigio
 * @tsk: The target task
 * @fown: the object the संकेत come from
 * @signum: unused
 *
 * Allow a privileged task to get संकेतs even अगर it shouldn't
 *
 * Returns 0 अगर a subject with the object's smack could
 * ग_लिखो to the task, an error code otherwise.
 */
अटल पूर्णांक smack_file_send_sigiotask(काष्ठा task_काष्ठा *tsk,
				     काष्ठा fown_काष्ठा *fown, पूर्णांक signum)
अणु
	काष्ठा smack_known **blob;
	काष्ठा smack_known *skp;
	काष्ठा smack_known *tkp = smk_of_task(smack_cred(tsk->cred));
	स्थिर काष्ठा cred *tcred;
	काष्ठा file *file;
	पूर्णांक rc;
	काष्ठा smk_audit_info ad;

	/*
	 * काष्ठा fown_काष्ठा is never outside the context of a काष्ठा file
	 */
	file = container_of(fown, काष्ठा file, f_owner);

	/* we करोn't log here as rc can be overriden */
	blob = smack_file(file);
	skp = *blob;
	rc = smk_access(skp, tkp, MAY_DELIVER, शून्य);
	rc = smk_bu_note("sigiotask", skp, tkp, MAY_DELIVER, rc);

	rcu_पढ़ो_lock();
	tcred = __task_cred(tsk);
	अगर (rc != 0 && smack_privileged_cred(CAP_MAC_OVERRIDE, tcred))
		rc = 0;
	rcu_पढ़ो_unlock();

	smk_ad_init(&ad, __func__, LSM_AUDIT_DATA_TASK);
	smk_ad_setfield_u_tsk(&ad, tsk);
	smack_log(skp->smk_known, tkp->smk_known, MAY_DELIVER, rc, &ad);
	वापस rc;
पूर्ण

/**
 * smack_file_receive - Smack file receive check
 * @file: the object
 *
 * Returns 0 अगर current has access, error code otherwise
 */
अटल पूर्णांक smack_file_receive(काष्ठा file *file)
अणु
	पूर्णांक rc;
	पूर्णांक may = 0;
	काष्ठा smk_audit_info ad;
	काष्ठा inode *inode = file_inode(file);
	काष्ठा socket *sock;
	काष्ठा task_smack *tsp;
	काष्ठा socket_smack *ssp;

	अगर (unlikely(IS_PRIVATE(inode)))
		वापस 0;

	smk_ad_init(&ad, __func__, LSM_AUDIT_DATA_PATH);
	smk_ad_setfield_u_fs_path(&ad, file->f_path);

	अगर (inode->i_sb->s_magic == SOCKFS_MAGIC) अणु
		sock = SOCKET_I(inode);
		ssp = sock->sk->sk_security;
		tsp = smack_cred(current_cred());
		/*
		 * If the receiving process can't ग_लिखो to the
		 * passed socket or अगर the passed socket can't
		 * ग_लिखो to the receiving process करोn't accept
		 * the passed socket.
		 */
		rc = smk_access(tsp->smk_task, ssp->smk_out, MAY_WRITE, &ad);
		rc = smk_bu_file(file, may, rc);
		अगर (rc < 0)
			वापस rc;
		rc = smk_access(ssp->smk_in, tsp->smk_task, MAY_WRITE, &ad);
		rc = smk_bu_file(file, may, rc);
		वापस rc;
	पूर्ण
	/*
	 * This code relies on biपंचांगasks.
	 */
	अगर (file->f_mode & FMODE_READ)
		may = MAY_READ;
	अगर (file->f_mode & FMODE_WRITE)
		may |= MAY_WRITE;

	rc = smk_curacc(smk_of_inode(inode), may, &ad);
	rc = smk_bu_file(file, may, rc);
	वापस rc;
पूर्ण

/**
 * smack_file_खोलो - Smack dentry खोलो processing
 * @file: the object
 *
 * Set the security blob in the file काष्ठाure.
 * Allow the खोलो only अगर the task has पढ़ो access. There are
 * many पढ़ो operations (e.g. ख_स्थिति) that you can करो with an
 * fd even अगर you have the file खोलो ग_लिखो-only.
 *
 * Returns 0 अगर current has access, error code otherwise
 */
अटल पूर्णांक smack_file_खोलो(काष्ठा file *file)
अणु
	काष्ठा task_smack *tsp = smack_cred(file->f_cred);
	काष्ठा inode *inode = file_inode(file);
	काष्ठा smk_audit_info ad;
	पूर्णांक rc;

	smk_ad_init(&ad, __func__, LSM_AUDIT_DATA_PATH);
	smk_ad_setfield_u_fs_path(&ad, file->f_path);
	rc = smk_tskacc(tsp, smk_of_inode(inode), MAY_READ, &ad);
	rc = smk_bu_credfile(file->f_cred, file, MAY_READ, rc);

	वापस rc;
पूर्ण

/*
 * Task hooks
 */

/**
 * smack_cred_alloc_blank - "allocate" blank task-level security credentials
 * @cred: the new credentials
 * @gfp: the atomicity of any memory allocations
 *
 * Prepare a blank set of credentials क्रम modअगरication.  This must allocate all
 * the memory the LSM module might require such that cred_transfer() can
 * complete without error.
 */
अटल पूर्णांक smack_cred_alloc_blank(काष्ठा cred *cred, gfp_t gfp)
अणु
	init_task_smack(smack_cred(cred), शून्य, शून्य);
	वापस 0;
पूर्ण


/**
 * smack_cred_मुक्त - "free" task-level security credentials
 * @cred: the credentials in question
 *
 */
अटल व्योम smack_cred_मुक्त(काष्ठा cred *cred)
अणु
	काष्ठा task_smack *tsp = smack_cred(cred);
	काष्ठा smack_rule *rp;
	काष्ठा list_head *l;
	काष्ठा list_head *n;

	smk_destroy_label_list(&tsp->smk_relabel);

	list_क्रम_each_safe(l, n, &tsp->smk_rules) अणु
		rp = list_entry(l, काष्ठा smack_rule, list);
		list_del(&rp->list);
		kmem_cache_मुक्त(smack_rule_cache, rp);
	पूर्ण
पूर्ण

/**
 * smack_cred_prepare - prepare new set of credentials क्रम modअगरication
 * @new: the new credentials
 * @old: the original credentials
 * @gfp: the atomicity of any memory allocations
 *
 * Prepare a new set of credentials क्रम modअगरication.
 */
अटल पूर्णांक smack_cred_prepare(काष्ठा cred *new, स्थिर काष्ठा cred *old,
			      gfp_t gfp)
अणु
	काष्ठा task_smack *old_tsp = smack_cred(old);
	काष्ठा task_smack *new_tsp = smack_cred(new);
	पूर्णांक rc;

	init_task_smack(new_tsp, old_tsp->smk_task, old_tsp->smk_task);

	rc = smk_copy_rules(&new_tsp->smk_rules, &old_tsp->smk_rules, gfp);
	अगर (rc != 0)
		वापस rc;

	rc = smk_copy_relabel(&new_tsp->smk_relabel, &old_tsp->smk_relabel,
				gfp);
	वापस rc;
पूर्ण

/**
 * smack_cred_transfer - Transfer the old credentials to the new credentials
 * @new: the new credentials
 * @old: the original credentials
 *
 * Fill in a set of blank credentials from another set of credentials.
 */
अटल व्योम smack_cred_transfer(काष्ठा cred *new, स्थिर काष्ठा cred *old)
अणु
	काष्ठा task_smack *old_tsp = smack_cred(old);
	काष्ठा task_smack *new_tsp = smack_cred(new);

	new_tsp->smk_task = old_tsp->smk_task;
	new_tsp->smk_विभाजनed = old_tsp->smk_task;
	mutex_init(&new_tsp->smk_rules_lock);
	INIT_LIST_HEAD(&new_tsp->smk_rules);

	/* cbs copy rule list */
पूर्ण

/**
 * smack_cred_माला_लोecid - get the secid corresponding to a creds काष्ठाure
 * @cred: the object creds
 * @secid: where to put the result
 *
 * Sets the secid to contain a u32 version of the smack label.
 */
अटल व्योम smack_cred_माला_लोecid(स्थिर काष्ठा cred *cred, u32 *secid)
अणु
	काष्ठा smack_known *skp;

	rcu_पढ़ो_lock();
	skp = smk_of_task(smack_cred(cred));
	*secid = skp->smk_secid;
	rcu_पढ़ो_unlock();
पूर्ण

/**
 * smack_kernel_act_as - Set the subjective context in a set of credentials
 * @new: poपूर्णांकs to the set of credentials to be modअगरied.
 * @secid: specअगरies the security ID to be set
 *
 * Set the security data क्रम a kernel service.
 */
अटल पूर्णांक smack_kernel_act_as(काष्ठा cred *new, u32 secid)
अणु
	काष्ठा task_smack *new_tsp = smack_cred(new);

	new_tsp->smk_task = smack_from_secid(secid);
	वापस 0;
पूर्ण

/**
 * smack_kernel_create_files_as - Set the file creation label in a set of creds
 * @new: poपूर्णांकs to the set of credentials to be modअगरied
 * @inode: poपूर्णांकs to the inode to use as a reference
 *
 * Set the file creation context in a set of credentials to the same
 * as the objective context of the specअगरied inode
 */
अटल पूर्णांक smack_kernel_create_files_as(काष्ठा cred *new,
					काष्ठा inode *inode)
अणु
	काष्ठा inode_smack *isp = smack_inode(inode);
	काष्ठा task_smack *tsp = smack_cred(new);

	tsp->smk_विभाजनed = isp->smk_inode;
	tsp->smk_task = tsp->smk_विभाजनed;
	वापस 0;
पूर्ण

/**
 * smk_curacc_on_task - helper to log task related access
 * @p: the task object
 * @access: the access requested
 * @caller: name of the calling function क्रम audit
 *
 * Return 0 अगर access is permitted
 */
अटल पूर्णांक smk_curacc_on_task(काष्ठा task_काष्ठा *p, पूर्णांक access,
				स्थिर अक्षर *caller)
अणु
	काष्ठा smk_audit_info ad;
	काष्ठा smack_known *skp = smk_of_task_काष्ठा_subj(p);
	पूर्णांक rc;

	smk_ad_init(&ad, caller, LSM_AUDIT_DATA_TASK);
	smk_ad_setfield_u_tsk(&ad, p);
	rc = smk_curacc(skp, access, &ad);
	rc = smk_bu_task(p, access, rc);
	वापस rc;
पूर्ण

/**
 * smack_task_setpgid - Smack check on setting pgid
 * @p: the task object
 * @pgid: unused
 *
 * Return 0 अगर ग_लिखो access is permitted
 */
अटल पूर्णांक smack_task_setpgid(काष्ठा task_काष्ठा *p, pid_t pgid)
अणु
	वापस smk_curacc_on_task(p, MAY_WRITE, __func__);
पूर्ण

/**
 * smack_task_getpgid - Smack access check क्रम getpgid
 * @p: the object task
 *
 * Returns 0 अगर current can पढ़ो the object task, error code otherwise
 */
अटल पूर्णांक smack_task_getpgid(काष्ठा task_काष्ठा *p)
अणु
	वापस smk_curacc_on_task(p, MAY_READ, __func__);
पूर्ण

/**
 * smack_task_माला_लोid - Smack access check क्रम माला_लोid
 * @p: the object task
 *
 * Returns 0 अगर current can पढ़ो the object task, error code otherwise
 */
अटल पूर्णांक smack_task_माला_लोid(काष्ठा task_काष्ठा *p)
अणु
	वापस smk_curacc_on_task(p, MAY_READ, __func__);
पूर्ण

/**
 * smack_task_माला_लोecid_subj - get the subjective secid of the task
 * @p: the task
 * @secid: where to put the result
 *
 * Sets the secid to contain a u32 version of the task's subjective smack label.
 */
अटल व्योम smack_task_माला_लोecid_subj(काष्ठा task_काष्ठा *p, u32 *secid)
अणु
	काष्ठा smack_known *skp = smk_of_task_काष्ठा_subj(p);

	*secid = skp->smk_secid;
पूर्ण

/**
 * smack_task_माला_लोecid_obj - get the objective secid of the task
 * @p: the task
 * @secid: where to put the result
 *
 * Sets the secid to contain a u32 version of the task's objective smack label.
 */
अटल व्योम smack_task_माला_लोecid_obj(काष्ठा task_काष्ठा *p, u32 *secid)
अणु
	काष्ठा smack_known *skp = smk_of_task_काष्ठा_obj(p);

	*secid = skp->smk_secid;
पूर्ण

/**
 * smack_task_setnice - Smack check on setting nice
 * @p: the task object
 * @nice: unused
 *
 * Return 0 अगर ग_लिखो access is permitted
 */
अटल पूर्णांक smack_task_setnice(काष्ठा task_काष्ठा *p, पूर्णांक nice)
अणु
	वापस smk_curacc_on_task(p, MAY_WRITE, __func__);
पूर्ण

/**
 * smack_task_setioprio - Smack check on setting ioprio
 * @p: the task object
 * @ioprio: unused
 *
 * Return 0 अगर ग_लिखो access is permitted
 */
अटल पूर्णांक smack_task_setioprio(काष्ठा task_काष्ठा *p, पूर्णांक ioprio)
अणु
	वापस smk_curacc_on_task(p, MAY_WRITE, __func__);
पूर्ण

/**
 * smack_task_getioprio - Smack check on पढ़ोing ioprio
 * @p: the task object
 *
 * Return 0 अगर पढ़ो access is permitted
 */
अटल पूर्णांक smack_task_getioprio(काष्ठा task_काष्ठा *p)
अणु
	वापस smk_curacc_on_task(p, MAY_READ, __func__);
पूर्ण

/**
 * smack_task_setscheduler - Smack check on setting scheduler
 * @p: the task object
 *
 * Return 0 अगर पढ़ो access is permitted
 */
अटल पूर्णांक smack_task_setscheduler(काष्ठा task_काष्ठा *p)
अणु
	वापस smk_curacc_on_task(p, MAY_WRITE, __func__);
पूर्ण

/**
 * smack_task_माला_लोcheduler - Smack check on पढ़ोing scheduler
 * @p: the task object
 *
 * Return 0 अगर पढ़ो access is permitted
 */
अटल पूर्णांक smack_task_माला_लोcheduler(काष्ठा task_काष्ठा *p)
अणु
	वापस smk_curacc_on_task(p, MAY_READ, __func__);
पूर्ण

/**
 * smack_task_movememory - Smack check on moving memory
 * @p: the task object
 *
 * Return 0 अगर ग_लिखो access is permitted
 */
अटल पूर्णांक smack_task_movememory(काष्ठा task_काष्ठा *p)
अणु
	वापस smk_curacc_on_task(p, MAY_WRITE, __func__);
पूर्ण

/**
 * smack_task_समाप्त - Smack check on संकेत delivery
 * @p: the task object
 * @info: unused
 * @sig: unused
 * @cred: identअगरies the cred to use in lieu of current's
 *
 * Return 0 अगर ग_लिखो access is permitted
 *
 */
अटल पूर्णांक smack_task_समाप्त(काष्ठा task_काष्ठा *p, काष्ठा kernel_siginfo *info,
			   पूर्णांक sig, स्थिर काष्ठा cred *cred)
अणु
	काष्ठा smk_audit_info ad;
	काष्ठा smack_known *skp;
	काष्ठा smack_known *tkp = smk_of_task_काष्ठा_obj(p);
	पूर्णांक rc;

	अगर (!sig)
		वापस 0; /* null संकेत; existence test */

	smk_ad_init(&ad, __func__, LSM_AUDIT_DATA_TASK);
	smk_ad_setfield_u_tsk(&ad, p);
	/*
	 * Sending a संकेत requires that the sender
	 * can ग_लिखो the receiver.
	 */
	अगर (cred == शून्य) अणु
		rc = smk_curacc(tkp, MAY_DELIVER, &ad);
		rc = smk_bu_task(p, MAY_DELIVER, rc);
		वापस rc;
	पूर्ण
	/*
	 * If the cred isn't NULL we're dealing with some USB IO
	 * specअगरic behavior. This is not clean. For one thing
	 * we can't take privilege पूर्णांकo account.
	 */
	skp = smk_of_task(smack_cred(cred));
	rc = smk_access(skp, tkp, MAY_DELIVER, &ad);
	rc = smk_bu_note("USB signal", skp, tkp, MAY_DELIVER, rc);
	वापस rc;
पूर्ण

/**
 * smack_task_to_inode - copy task smack पूर्णांकo the inode blob
 * @p: task to copy from
 * @inode: inode to copy to
 *
 * Sets the smack poपूर्णांकer in the inode security blob
 */
अटल व्योम smack_task_to_inode(काष्ठा task_काष्ठा *p, काष्ठा inode *inode)
अणु
	काष्ठा inode_smack *isp = smack_inode(inode);
	काष्ठा smack_known *skp = smk_of_task_काष्ठा_obj(p);

	isp->smk_inode = skp;
	isp->smk_flags |= SMK_INODE_INSTANT;
पूर्ण

/*
 * Socket hooks.
 */

/**
 * smack_sk_alloc_security - Allocate a socket blob
 * @sk: the socket
 * @family: unused
 * @gfp_flags: memory allocation flags
 *
 * Assign Smack poपूर्णांकers to current
 *
 * Returns 0 on success, -ENOMEM is there's no memory
 */
अटल पूर्णांक smack_sk_alloc_security(काष्ठा sock *sk, पूर्णांक family, gfp_t gfp_flags)
अणु
	काष्ठा smack_known *skp = smk_of_current();
	काष्ठा socket_smack *ssp;

	ssp = kzalloc(माप(काष्ठा socket_smack), gfp_flags);
	अगर (ssp == शून्य)
		वापस -ENOMEM;

	/*
	 * Sockets created by kernel thपढ़ोs receive web label.
	 */
	अगर (unlikely(current->flags & PF_KTHREAD)) अणु
		ssp->smk_in = &smack_known_web;
		ssp->smk_out = &smack_known_web;
	पूर्ण अन्यथा अणु
		ssp->smk_in = skp;
		ssp->smk_out = skp;
	पूर्ण
	ssp->smk_packet = शून्य;

	sk->sk_security = ssp;

	वापस 0;
पूर्ण

/**
 * smack_sk_मुक्त_security - Free a socket blob
 * @sk: the socket
 *
 * Clears the blob poपूर्णांकer
 */
अटल व्योम smack_sk_मुक्त_security(काष्ठा sock *sk)
अणु
#अगर_घोषित SMACK_IPV6_PORT_LABELING
	काष्ठा smk_port_label *spp;

	अगर (sk->sk_family == PF_INET6) अणु
		rcu_पढ़ो_lock();
		list_क्रम_each_entry_rcu(spp, &smk_ipv6_port_list, list) अणु
			अगर (spp->smk_sock != sk)
				जारी;
			spp->smk_can_reuse = 1;
			अवरोध;
		पूर्ण
		rcu_पढ़ो_unlock();
	पूर्ण
#पूर्ण_अगर
	kमुक्त(sk->sk_security);
पूर्ण

/**
* smack_ipv4host_label - check host based restrictions
* @sip: the object end
*
* looks क्रम host based access restrictions
*
* This version will only be appropriate क्रम really small sets of single label
* hosts.  The caller is responsible क्रम ensuring that the RCU पढ़ो lock is
* taken beक्रमe calling this function.
*
* Returns the label of the far end or शून्य अगर it's not special.
*/
अटल काष्ठा smack_known *smack_ipv4host_label(काष्ठा sockaddr_in *sip)
अणु
	काष्ठा smk_net4addr *snp;
	काष्ठा in_addr *siap = &sip->sin_addr;

	अगर (siap->s_addr == 0)
		वापस शून्य;

	list_क्रम_each_entry_rcu(snp, &smk_net4addr_list, list)
		/*
		 * we अवरोध after finding the first match because
		 * the list is sorted from दीर्घest to लघुest mask
		 * so we have found the most specअगरic match
		 */
		अगर (snp->smk_host.s_addr ==
		    (siap->s_addr & snp->smk_mask.s_addr))
			वापस snp->smk_label;

	वापस शून्य;
पूर्ण

/*
 * smk_ipv6_localhost - Check क्रम local ipv6 host address
 * @sip: the address
 *
 * Returns boolean true अगर this is the localhost address
 */
अटल bool smk_ipv6_localhost(काष्ठा sockaddr_in6 *sip)
अणु
	__be16 *be16p = (__be16 *)&sip->sin6_addr;
	__be32 *be32p = (__be32 *)&sip->sin6_addr;

	अगर (be32p[0] == 0 && be32p[1] == 0 && be32p[2] == 0 && be16p[6] == 0 &&
	    ntohs(be16p[7]) == 1)
		वापस true;
	वापस false;
पूर्ण

/**
* smack_ipv6host_label - check host based restrictions
* @sip: the object end
*
* looks क्रम host based access restrictions
*
* This version will only be appropriate क्रम really small sets of single label
* hosts.  The caller is responsible क्रम ensuring that the RCU पढ़ो lock is
* taken beक्रमe calling this function.
*
* Returns the label of the far end or शून्य अगर it's not special.
*/
अटल काष्ठा smack_known *smack_ipv6host_label(काष्ठा sockaddr_in6 *sip)
अणु
	काष्ठा smk_net6addr *snp;
	काष्ठा in6_addr *sap = &sip->sin6_addr;
	पूर्णांक i;
	पूर्णांक found = 0;

	/*
	 * It's local. Don't look क्रम a host label.
	 */
	अगर (smk_ipv6_localhost(sip))
		वापस शून्य;

	list_क्रम_each_entry_rcu(snp, &smk_net6addr_list, list) अणु
		/*
		 * If the label is शून्य the entry has
		 * been renounced. Ignore it.
		 */
		अगर (snp->smk_label == शून्य)
			जारी;
		/*
		* we अवरोध after finding the first match because
		* the list is sorted from दीर्घest to लघुest mask
		* so we have found the most specअगरic match
		*/
		क्रम (found = 1, i = 0; i < 8; i++) अणु
			अगर ((sap->s6_addr16[i] & snp->smk_mask.s6_addr16[i]) !=
			    snp->smk_host.s6_addr16[i]) अणु
				found = 0;
				अवरोध;
			पूर्ण
		पूर्ण
		अगर (found)
			वापस snp->smk_label;
	पूर्ण

	वापस शून्य;
पूर्ण

/**
 * smack_netlbl_add - Set the secattr on a socket
 * @sk: the socket
 *
 * Attach the outbound smack value (smk_out) to the socket.
 *
 * Returns 0 on success or an error code
 */
अटल पूर्णांक smack_netlbl_add(काष्ठा sock *sk)
अणु
	काष्ठा socket_smack *ssp = sk->sk_security;
	काष्ठा smack_known *skp = ssp->smk_out;
	पूर्णांक rc;

	local_bh_disable();
	bh_lock_sock_nested(sk);

	rc = netlbl_sock_setattr(sk, sk->sk_family, &skp->smk_netlabel);
	चयन (rc) अणु
	हाल 0:
		ssp->smk_state = SMK_NETLBL_LABELED;
		अवरोध;
	हाल -EDESTADDRREQ:
		ssp->smk_state = SMK_NETLBL_REQSKB;
		rc = 0;
		अवरोध;
	पूर्ण

	bh_unlock_sock(sk);
	local_bh_enable();

	वापस rc;
पूर्ण

/**
 * smack_netlbl_delete - Remove the secattr from a socket
 * @sk: the socket
 *
 * Remove the outbound smack value from a socket
 */
अटल व्योम smack_netlbl_delete(काष्ठा sock *sk)
अणु
	काष्ठा socket_smack *ssp = sk->sk_security;

	/*
	 * Take the label off the socket अगर one is set.
	 */
	अगर (ssp->smk_state != SMK_NETLBL_LABELED)
		वापस;

	local_bh_disable();
	bh_lock_sock_nested(sk);
	netlbl_sock_delattr(sk);
	bh_unlock_sock(sk);
	local_bh_enable();
	ssp->smk_state = SMK_NETLBL_UNLABELED;
पूर्ण

/**
 * smk_ipv4_check - Perक्रमm IPv4 host access checks
 * @sk: the socket
 * @sap: the destination address
 *
 * Set the correct secattr क्रम the given socket based on the destination
 * address and perक्रमm any outbound access checks needed.
 *
 * Returns 0 on success or an error code.
 *
 */
अटल पूर्णांक smk_ipv4_check(काष्ठा sock *sk, काष्ठा sockaddr_in *sap)
अणु
	काष्ठा smack_known *skp;
	पूर्णांक rc = 0;
	काष्ठा smack_known *hkp;
	काष्ठा socket_smack *ssp = sk->sk_security;
	काष्ठा smk_audit_info ad;

	rcu_पढ़ो_lock();
	hkp = smack_ipv4host_label(sap);
	अगर (hkp != शून्य) अणु
#अगर_घोषित CONFIG_AUDIT
		काष्ठा lsm_network_audit net;

		smk_ad_init_net(&ad, __func__, LSM_AUDIT_DATA_NET, &net);
		ad.a.u.net->family = sap->sin_family;
		ad.a.u.net->dport = sap->sin_port;
		ad.a.u.net->v4info.daddr = sap->sin_addr.s_addr;
#पूर्ण_अगर
		skp = ssp->smk_out;
		rc = smk_access(skp, hkp, MAY_WRITE, &ad);
		rc = smk_bu_note("IPv4 host check", skp, hkp, MAY_WRITE, rc);
		/*
		 * Clear the socket netlabel अगर it's set.
		 */
		अगर (!rc)
			smack_netlbl_delete(sk);
	पूर्ण
	rcu_पढ़ो_unlock();

	वापस rc;
पूर्ण

/**
 * smk_ipv6_check - check Smack access
 * @subject: subject Smack label
 * @object: object Smack label
 * @address: address
 * @act: the action being taken
 *
 * Check an IPv6 access
 */
अटल पूर्णांक smk_ipv6_check(काष्ठा smack_known *subject,
				काष्ठा smack_known *object,
				काष्ठा sockaddr_in6 *address, पूर्णांक act)
अणु
#अगर_घोषित CONFIG_AUDIT
	काष्ठा lsm_network_audit net;
#पूर्ण_अगर
	काष्ठा smk_audit_info ad;
	पूर्णांक rc;

#अगर_घोषित CONFIG_AUDIT
	smk_ad_init_net(&ad, __func__, LSM_AUDIT_DATA_NET, &net);
	ad.a.u.net->family = PF_INET6;
	ad.a.u.net->dport = ntohs(address->sin6_port);
	अगर (act == SMK_RECEIVING)
		ad.a.u.net->v6info.saddr = address->sin6_addr;
	अन्यथा
		ad.a.u.net->v6info.daddr = address->sin6_addr;
#पूर्ण_अगर
	rc = smk_access(subject, object, MAY_WRITE, &ad);
	rc = smk_bu_note("IPv6 check", subject, object, MAY_WRITE, rc);
	वापस rc;
पूर्ण

#अगर_घोषित SMACK_IPV6_PORT_LABELING
/**
 * smk_ipv6_port_label - Smack port access table management
 * @sock: socket
 * @address: address
 *
 * Create or update the port list entry
 */
अटल व्योम smk_ipv6_port_label(काष्ठा socket *sock, काष्ठा sockaddr *address)
अणु
	काष्ठा sock *sk = sock->sk;
	काष्ठा sockaddr_in6 *addr6;
	काष्ठा socket_smack *ssp = sock->sk->sk_security;
	काष्ठा smk_port_label *spp;
	अचिन्हित लघु port = 0;

	अगर (address == शून्य) अणु
		/*
		 * This operation is changing the Smack inक्रमmation
		 * on the bound socket. Take the changes to the port
		 * as well.
		 */
		rcu_पढ़ो_lock();
		list_क्रम_each_entry_rcu(spp, &smk_ipv6_port_list, list) अणु
			अगर (sk != spp->smk_sock)
				जारी;
			spp->smk_in = ssp->smk_in;
			spp->smk_out = ssp->smk_out;
			rcu_पढ़ो_unlock();
			वापस;
		पूर्ण
		/*
		 * A शून्य address is only used क्रम updating existing
		 * bound entries. If there isn't one, it's OK.
		 */
		rcu_पढ़ो_unlock();
		वापस;
	पूर्ण

	addr6 = (काष्ठा sockaddr_in6 *)address;
	port = ntohs(addr6->sin6_port);
	/*
	 * This is a special हाल that is safely ignored.
	 */
	अगर (port == 0)
		वापस;

	/*
	 * Look क्रम an existing port list entry.
	 * This is an indication that a port is getting reused.
	 */
	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(spp, &smk_ipv6_port_list, list) अणु
		अगर (spp->smk_port != port || spp->smk_sock_type != sock->type)
			जारी;
		अगर (spp->smk_can_reuse != 1) अणु
			rcu_पढ़ो_unlock();
			वापस;
		पूर्ण
		spp->smk_port = port;
		spp->smk_sock = sk;
		spp->smk_in = ssp->smk_in;
		spp->smk_out = ssp->smk_out;
		spp->smk_can_reuse = 0;
		rcu_पढ़ो_unlock();
		वापस;
	पूर्ण
	rcu_पढ़ो_unlock();
	/*
	 * A new port entry is required.
	 */
	spp = kzalloc(माप(*spp), GFP_KERNEL);
	अगर (spp == शून्य)
		वापस;

	spp->smk_port = port;
	spp->smk_sock = sk;
	spp->smk_in = ssp->smk_in;
	spp->smk_out = ssp->smk_out;
	spp->smk_sock_type = sock->type;
	spp->smk_can_reuse = 0;

	mutex_lock(&smack_ipv6_lock);
	list_add_rcu(&spp->list, &smk_ipv6_port_list);
	mutex_unlock(&smack_ipv6_lock);
	वापस;
पूर्ण
#पूर्ण_अगर

/**
 * smk_ipv6_port_check - check Smack port access
 * @sk: socket
 * @address: address
 * @act: the action being taken
 *
 * Create or update the port list entry
 */
अटल पूर्णांक smk_ipv6_port_check(काष्ठा sock *sk, काष्ठा sockaddr_in6 *address,
				पूर्णांक act)
अणु
	काष्ठा smk_port_label *spp;
	काष्ठा socket_smack *ssp = sk->sk_security;
	काष्ठा smack_known *skp = शून्य;
	अचिन्हित लघु port;
	काष्ठा smack_known *object;

	अगर (act == SMK_RECEIVING) अणु
		skp = smack_ipv6host_label(address);
		object = ssp->smk_in;
	पूर्ण अन्यथा अणु
		skp = ssp->smk_out;
		object = smack_ipv6host_label(address);
	पूर्ण

	/*
	 * The other end is a single label host.
	 */
	अगर (skp != शून्य && object != शून्य)
		वापस smk_ipv6_check(skp, object, address, act);
	अगर (skp == शून्य)
		skp = smack_net_ambient;
	अगर (object == शून्य)
		object = smack_net_ambient;

	/*
	 * It's remote, so port lookup करोes no good.
	 */
	अगर (!smk_ipv6_localhost(address))
		वापस smk_ipv6_check(skp, object, address, act);

	/*
	 * It's local so the send check has to have passed.
	 */
	अगर (act == SMK_RECEIVING)
		वापस 0;

	port = ntohs(address->sin6_port);
	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(spp, &smk_ipv6_port_list, list) अणु
		अगर (spp->smk_port != port || spp->smk_sock_type != sk->sk_type)
			जारी;
		object = spp->smk_in;
		अगर (act == SMK_CONNECTING)
			ssp->smk_packet = spp->smk_out;
		अवरोध;
	पूर्ण
	rcu_पढ़ो_unlock();

	वापस smk_ipv6_check(skp, object, address, act);
पूर्ण

/**
 * smack_inode_setsecurity - set smack xattrs
 * @inode: the object
 * @name: attribute name
 * @value: attribute value
 * @size: size of the attribute
 * @flags: unused
 *
 * Sets the named attribute in the appropriate blob
 *
 * Returns 0 on success, or an error code
 */
अटल पूर्णांक smack_inode_setsecurity(काष्ठा inode *inode, स्थिर अक्षर *name,
				   स्थिर व्योम *value, माप_प्रकार size, पूर्णांक flags)
अणु
	काष्ठा smack_known *skp;
	काष्ठा inode_smack *nsp = smack_inode(inode);
	काष्ठा socket_smack *ssp;
	काष्ठा socket *sock;
	पूर्णांक rc = 0;

	अगर (value == शून्य || size > SMK_LONGLABEL || size == 0)
		वापस -EINVAL;

	skp = smk_import_entry(value, size);
	अगर (IS_ERR(skp))
		वापस PTR_ERR(skp);

	अगर (म_भेद(name, XATTR_SMACK_SUFFIX) == 0) अणु
		nsp->smk_inode = skp;
		nsp->smk_flags |= SMK_INODE_INSTANT;
		वापस 0;
	पूर्ण
	/*
	 * The rest of the Smack xattrs are only on sockets.
	 */
	अगर (inode->i_sb->s_magic != SOCKFS_MAGIC)
		वापस -EOPNOTSUPP;

	sock = SOCKET_I(inode);
	अगर (sock == शून्य || sock->sk == शून्य)
		वापस -EOPNOTSUPP;

	ssp = sock->sk->sk_security;

	अगर (म_भेद(name, XATTR_SMACK_IPIN) == 0)
		ssp->smk_in = skp;
	अन्यथा अगर (म_भेद(name, XATTR_SMACK_IPOUT) == 0) अणु
		ssp->smk_out = skp;
		अगर (sock->sk->sk_family == PF_INET) अणु
			rc = smack_netlbl_add(sock->sk);
			अगर (rc != 0)
				prपूर्णांकk(KERN_WARNING
					"Smack: \"%s\" netlbl error %d.\n",
					__func__, -rc);
		पूर्ण
	पूर्ण अन्यथा
		वापस -EOPNOTSUPP;

#अगर_घोषित SMACK_IPV6_PORT_LABELING
	अगर (sock->sk->sk_family == PF_INET6)
		smk_ipv6_port_label(sock, शून्य);
#पूर्ण_अगर

	वापस 0;
पूर्ण

/**
 * smack_socket_post_create - finish socket setup
 * @sock: the socket
 * @family: protocol family
 * @type: unused
 * @protocol: unused
 * @kern: unused
 *
 * Sets the netlabel inक्रमmation on the socket
 *
 * Returns 0 on success, and error code otherwise
 */
अटल पूर्णांक smack_socket_post_create(काष्ठा socket *sock, पूर्णांक family,
				    पूर्णांक type, पूर्णांक protocol, पूर्णांक kern)
अणु
	काष्ठा socket_smack *ssp;

	अगर (sock->sk == शून्य)
		वापस 0;

	/*
	 * Sockets created by kernel thपढ़ोs receive web label.
	 */
	अगर (unlikely(current->flags & PF_KTHREAD)) अणु
		ssp = sock->sk->sk_security;
		ssp->smk_in = &smack_known_web;
		ssp->smk_out = &smack_known_web;
	पूर्ण

	अगर (family != PF_INET)
		वापस 0;
	/*
	 * Set the outbound netlbl.
	 */
	वापस smack_netlbl_add(sock->sk);
पूर्ण

/**
 * smack_socket_socketpair - create socket pair
 * @socka: one socket
 * @sockb: another socket
 *
 * Cross reference the peer labels क्रम SO_PEERSEC
 *
 * Returns 0
 */
अटल पूर्णांक smack_socket_socketpair(काष्ठा socket *socka,
		                   काष्ठा socket *sockb)
अणु
	काष्ठा socket_smack *asp = socka->sk->sk_security;
	काष्ठा socket_smack *bsp = sockb->sk->sk_security;

	asp->smk_packet = bsp->smk_out;
	bsp->smk_packet = asp->smk_out;

	वापस 0;
पूर्ण

#अगर_घोषित SMACK_IPV6_PORT_LABELING
/**
 * smack_socket_bind - record port binding inक्रमmation.
 * @sock: the socket
 * @address: the port address
 * @addrlen: size of the address
 *
 * Records the label bound to a port.
 *
 * Returns 0 on success, and error code otherwise
 */
अटल पूर्णांक smack_socket_bind(काष्ठा socket *sock, काष्ठा sockaddr *address,
				पूर्णांक addrlen)
अणु
	अगर (sock->sk != शून्य && sock->sk->sk_family == PF_INET6) अणु
		अगर (addrlen < SIN6_LEN_RFC2133 ||
		    address->sa_family != AF_INET6)
			वापस -EINVAL;
		smk_ipv6_port_label(sock, address);
	पूर्ण
	वापस 0;
पूर्ण
#पूर्ण_अगर /* SMACK_IPV6_PORT_LABELING */

/**
 * smack_socket_connect - connect access check
 * @sock: the socket
 * @sap: the other end
 * @addrlen: size of sap
 *
 * Verअगरies that a connection may be possible
 *
 * Returns 0 on success, and error code otherwise
 */
अटल पूर्णांक smack_socket_connect(काष्ठा socket *sock, काष्ठा sockaddr *sap,
				पूर्णांक addrlen)
अणु
	पूर्णांक rc = 0;

	अगर (sock->sk == शून्य)
		वापस 0;
	अगर (sock->sk->sk_family != PF_INET &&
	    (!IS_ENABLED(CONFIG_IPV6) || sock->sk->sk_family != PF_INET6))
		वापस 0;
	अगर (addrlen < दुरत्वend(काष्ठा sockaddr, sa_family))
		वापस 0;
	अगर (IS_ENABLED(CONFIG_IPV6) && sap->sa_family == AF_INET6) अणु
		काष्ठा sockaddr_in6 *sip = (काष्ठा sockaddr_in6 *)sap;
		काष्ठा smack_known *rsp = शून्य;

		अगर (addrlen < SIN6_LEN_RFC2133)
			वापस 0;
		अगर (__is_defined(SMACK_IPV6_SECMARK_LABELING))
			rsp = smack_ipv6host_label(sip);
		अगर (rsp != शून्य) अणु
			काष्ठा socket_smack *ssp = sock->sk->sk_security;

			rc = smk_ipv6_check(ssp->smk_out, rsp, sip,
					    SMK_CONNECTING);
		पूर्ण
		अगर (__is_defined(SMACK_IPV6_PORT_LABELING))
			rc = smk_ipv6_port_check(sock->sk, sip, SMK_CONNECTING);

		वापस rc;
	पूर्ण
	अगर (sap->sa_family != AF_INET || addrlen < माप(काष्ठा sockaddr_in))
		वापस 0;
	rc = smk_ipv4_check(sock->sk, (काष्ठा sockaddr_in *)sap);
	वापस rc;
पूर्ण

/**
 * smack_flags_to_may - convert S_ to MAY_ values
 * @flags: the S_ value
 *
 * Returns the equivalent MAY_ value
 */
अटल पूर्णांक smack_flags_to_may(पूर्णांक flags)
अणु
	पूर्णांक may = 0;

	अगर (flags & S_IRUGO)
		may |= MAY_READ;
	अगर (flags & S_IWUGO)
		may |= MAY_WRITE;
	अगर (flags & S_IXUGO)
		may |= MAY_EXEC;

	वापस may;
पूर्ण

/**
 * smack_msg_msg_alloc_security - Set the security blob क्रम msg_msg
 * @msg: the object
 *
 * Returns 0
 */
अटल पूर्णांक smack_msg_msg_alloc_security(काष्ठा msg_msg *msg)
अणु
	काष्ठा smack_known **blob = smack_msg_msg(msg);

	*blob = smk_of_current();
	वापस 0;
पूर्ण

/**
 * smack_of_ipc - the smack poपूर्णांकer क्रम the ipc
 * @isp: the object
 *
 * Returns a poपूर्णांकer to the smack value
 */
अटल काष्ठा smack_known *smack_of_ipc(काष्ठा kern_ipc_perm *isp)
अणु
	काष्ठा smack_known **blob = smack_ipc(isp);

	वापस *blob;
पूर्ण

/**
 * smack_ipc_alloc_security - Set the security blob क्रम ipc
 * @isp: the object
 *
 * Returns 0
 */
अटल पूर्णांक smack_ipc_alloc_security(काष्ठा kern_ipc_perm *isp)
अणु
	काष्ठा smack_known **blob = smack_ipc(isp);

	*blob = smk_of_current();
	वापस 0;
पूर्ण

/**
 * smk_curacc_shm : check अगर current has access on shm
 * @isp : the object
 * @access : access requested
 *
 * Returns 0 अगर current has the requested access, error code otherwise
 */
अटल पूर्णांक smk_curacc_shm(काष्ठा kern_ipc_perm *isp, पूर्णांक access)
अणु
	काष्ठा smack_known *ssp = smack_of_ipc(isp);
	काष्ठा smk_audit_info ad;
	पूर्णांक rc;

#अगर_घोषित CONFIG_AUDIT
	smk_ad_init(&ad, __func__, LSM_AUDIT_DATA_IPC);
	ad.a.u.ipc_id = isp->id;
#पूर्ण_अगर
	rc = smk_curacc(ssp, access, &ad);
	rc = smk_bu_current("shm", ssp, access, rc);
	वापस rc;
पूर्ण

/**
 * smack_shm_associate - Smack access check क्रम shm
 * @isp: the object
 * @shmflg: access requested
 *
 * Returns 0 अगर current has the requested access, error code otherwise
 */
अटल पूर्णांक smack_shm_associate(काष्ठा kern_ipc_perm *isp, पूर्णांक shmflg)
अणु
	पूर्णांक may;

	may = smack_flags_to_may(shmflg);
	वापस smk_curacc_shm(isp, may);
पूर्ण

/**
 * smack_shm_shmctl - Smack access check क्रम shm
 * @isp: the object
 * @cmd: what it wants to करो
 *
 * Returns 0 अगर current has the requested access, error code otherwise
 */
अटल पूर्णांक smack_shm_shmctl(काष्ठा kern_ipc_perm *isp, पूर्णांक cmd)
अणु
	पूर्णांक may;

	चयन (cmd) अणु
	हाल IPC_STAT:
	हाल SHM_STAT:
	हाल SHM_STAT_ANY:
		may = MAY_READ;
		अवरोध;
	हाल IPC_SET:
	हाल SHM_LOCK:
	हाल SHM_UNLOCK:
	हाल IPC_RMID:
		may = MAY_READWRITE;
		अवरोध;
	हाल IPC_INFO:
	हाल SHM_INFO:
		/*
		 * System level inक्रमmation.
		 */
		वापस 0;
	शेष:
		वापस -EINVAL;
	पूर्ण
	वापस smk_curacc_shm(isp, may);
पूर्ण

/**
 * smack_shm_shmat - Smack access क्रम shmat
 * @isp: the object
 * @shmaddr: unused
 * @shmflg: access requested
 *
 * Returns 0 अगर current has the requested access, error code otherwise
 */
अटल पूर्णांक smack_shm_shmat(काष्ठा kern_ipc_perm *isp, अक्षर __user *shmaddr,
			   पूर्णांक shmflg)
अणु
	पूर्णांक may;

	may = smack_flags_to_may(shmflg);
	वापस smk_curacc_shm(isp, may);
पूर्ण

/**
 * smk_curacc_sem : check अगर current has access on sem
 * @isp : the object
 * @access : access requested
 *
 * Returns 0 अगर current has the requested access, error code otherwise
 */
अटल पूर्णांक smk_curacc_sem(काष्ठा kern_ipc_perm *isp, पूर्णांक access)
अणु
	काष्ठा smack_known *ssp = smack_of_ipc(isp);
	काष्ठा smk_audit_info ad;
	पूर्णांक rc;

#अगर_घोषित CONFIG_AUDIT
	smk_ad_init(&ad, __func__, LSM_AUDIT_DATA_IPC);
	ad.a.u.ipc_id = isp->id;
#पूर्ण_अगर
	rc = smk_curacc(ssp, access, &ad);
	rc = smk_bu_current("sem", ssp, access, rc);
	वापस rc;
पूर्ण

/**
 * smack_sem_associate - Smack access check क्रम sem
 * @isp: the object
 * @semflg: access requested
 *
 * Returns 0 अगर current has the requested access, error code otherwise
 */
अटल पूर्णांक smack_sem_associate(काष्ठा kern_ipc_perm *isp, पूर्णांक semflg)
अणु
	पूर्णांक may;

	may = smack_flags_to_may(semflg);
	वापस smk_curacc_sem(isp, may);
पूर्ण

/**
 * smack_sem_shmctl - Smack access check क्रम sem
 * @isp: the object
 * @cmd: what it wants to करो
 *
 * Returns 0 अगर current has the requested access, error code otherwise
 */
अटल पूर्णांक smack_sem_semctl(काष्ठा kern_ipc_perm *isp, पूर्णांक cmd)
अणु
	पूर्णांक may;

	चयन (cmd) अणु
	हाल GETPID:
	हाल GETNCNT:
	हाल GETZCNT:
	हाल GETVAL:
	हाल GETALL:
	हाल IPC_STAT:
	हाल SEM_STAT:
	हाल SEM_STAT_ANY:
		may = MAY_READ;
		अवरोध;
	हाल SETVAL:
	हाल SETALL:
	हाल IPC_RMID:
	हाल IPC_SET:
		may = MAY_READWRITE;
		अवरोध;
	हाल IPC_INFO:
	हाल SEM_INFO:
		/*
		 * System level inक्रमmation
		 */
		वापस 0;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस smk_curacc_sem(isp, may);
पूर्ण

/**
 * smack_sem_semop - Smack checks of semaphore operations
 * @isp: the object
 * @sops: unused
 * @nsops: unused
 * @alter: unused
 *
 * Treated as पढ़ो and ग_लिखो in all हालs.
 *
 * Returns 0 अगर access is allowed, error code otherwise
 */
अटल पूर्णांक smack_sem_semop(काष्ठा kern_ipc_perm *isp, काष्ठा sembuf *sops,
			   अचिन्हित nsops, पूर्णांक alter)
अणु
	वापस smk_curacc_sem(isp, MAY_READWRITE);
पूर्ण

/**
 * smk_curacc_msq : helper to check अगर current has access on msq
 * @isp : the msq
 * @access : access requested
 *
 * वापस 0 अगर current has access, error otherwise
 */
अटल पूर्णांक smk_curacc_msq(काष्ठा kern_ipc_perm *isp, पूर्णांक access)
अणु
	काष्ठा smack_known *msp = smack_of_ipc(isp);
	काष्ठा smk_audit_info ad;
	पूर्णांक rc;

#अगर_घोषित CONFIG_AUDIT
	smk_ad_init(&ad, __func__, LSM_AUDIT_DATA_IPC);
	ad.a.u.ipc_id = isp->id;
#पूर्ण_अगर
	rc = smk_curacc(msp, access, &ad);
	rc = smk_bu_current("msq", msp, access, rc);
	वापस rc;
पूर्ण

/**
 * smack_msg_queue_associate - Smack access check क्रम msg_queue
 * @isp: the object
 * @msqflg: access requested
 *
 * Returns 0 अगर current has the requested access, error code otherwise
 */
अटल पूर्णांक smack_msg_queue_associate(काष्ठा kern_ipc_perm *isp, पूर्णांक msqflg)
अणु
	पूर्णांक may;

	may = smack_flags_to_may(msqflg);
	वापस smk_curacc_msq(isp, may);
पूर्ण

/**
 * smack_msg_queue_msgctl - Smack access check क्रम msg_queue
 * @isp: the object
 * @cmd: what it wants to करो
 *
 * Returns 0 अगर current has the requested access, error code otherwise
 */
अटल पूर्णांक smack_msg_queue_msgctl(काष्ठा kern_ipc_perm *isp, पूर्णांक cmd)
अणु
	पूर्णांक may;

	चयन (cmd) अणु
	हाल IPC_STAT:
	हाल MSG_STAT:
	हाल MSG_STAT_ANY:
		may = MAY_READ;
		अवरोध;
	हाल IPC_SET:
	हाल IPC_RMID:
		may = MAY_READWRITE;
		अवरोध;
	हाल IPC_INFO:
	हाल MSG_INFO:
		/*
		 * System level inक्रमmation
		 */
		वापस 0;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस smk_curacc_msq(isp, may);
पूर्ण

/**
 * smack_msg_queue_msgsnd - Smack access check क्रम msg_queue
 * @isp: the object
 * @msg: unused
 * @msqflg: access requested
 *
 * Returns 0 अगर current has the requested access, error code otherwise
 */
अटल पूर्णांक smack_msg_queue_msgsnd(काष्ठा kern_ipc_perm *isp, काष्ठा msg_msg *msg,
				  पूर्णांक msqflg)
अणु
	पूर्णांक may;

	may = smack_flags_to_may(msqflg);
	वापस smk_curacc_msq(isp, may);
पूर्ण

/**
 * smack_msg_queue_msgsnd - Smack access check क्रम msg_queue
 * @isp: the object
 * @msg: unused
 * @target: unused
 * @type: unused
 * @mode: unused
 *
 * Returns 0 अगर current has पढ़ो and ग_लिखो access, error code otherwise
 */
अटल पूर्णांक smack_msg_queue_msgrcv(काष्ठा kern_ipc_perm *isp, काष्ठा msg_msg *msg,
			काष्ठा task_काष्ठा *target, दीर्घ type, पूर्णांक mode)
अणु
	वापस smk_curacc_msq(isp, MAY_READWRITE);
पूर्ण

/**
 * smack_ipc_permission - Smack access क्रम ipc_permission()
 * @ipp: the object permissions
 * @flag: access requested
 *
 * Returns 0 अगर current has पढ़ो and ग_लिखो access, error code otherwise
 */
अटल पूर्णांक smack_ipc_permission(काष्ठा kern_ipc_perm *ipp, लघु flag)
अणु
	काष्ठा smack_known **blob = smack_ipc(ipp);
	काष्ठा smack_known *iskp = *blob;
	पूर्णांक may = smack_flags_to_may(flag);
	काष्ठा smk_audit_info ad;
	पूर्णांक rc;

#अगर_घोषित CONFIG_AUDIT
	smk_ad_init(&ad, __func__, LSM_AUDIT_DATA_IPC);
	ad.a.u.ipc_id = ipp->id;
#पूर्ण_अगर
	rc = smk_curacc(iskp, may, &ad);
	rc = smk_bu_current("svipc", iskp, may, rc);
	वापस rc;
पूर्ण

/**
 * smack_ipc_माला_लोecid - Extract smack security id
 * @ipp: the object permissions
 * @secid: where result will be saved
 */
अटल व्योम smack_ipc_माला_लोecid(काष्ठा kern_ipc_perm *ipp, u32 *secid)
अणु
	काष्ठा smack_known **blob = smack_ipc(ipp);
	काष्ठा smack_known *iskp = *blob;

	*secid = iskp->smk_secid;
पूर्ण

/**
 * smack_d_instantiate - Make sure the blob is correct on an inode
 * @opt_dentry: dentry where inode will be attached
 * @inode: the object
 *
 * Set the inode's security blob if it hasn't been करोne alपढ़ोy.
 */
अटल व्योम smack_d_instantiate(काष्ठा dentry *opt_dentry, काष्ठा inode *inode)
अणु
	काष्ठा super_block *sbp;
	काष्ठा superblock_smack *sbsp;
	काष्ठा inode_smack *isp;
	काष्ठा smack_known *skp;
	काष्ठा smack_known *ckp = smk_of_current();
	काष्ठा smack_known *final;
	अक्षर trattr[TRANS_TRUE_SIZE];
	पूर्णांक transflag = 0;
	पूर्णांक rc;
	काष्ठा dentry *dp;

	अगर (inode == शून्य)
		वापस;

	isp = smack_inode(inode);

	/*
	 * If the inode is alपढ़ोy instantiated
	 * take the quick way out
	 */
	अगर (isp->smk_flags & SMK_INODE_INSTANT)
		वापस;

	sbp = inode->i_sb;
	sbsp = smack_superblock(sbp);
	/*
	 * We're going to use the superblock शेष label
	 * अगर there's no label on the file.
	 */
	final = sbsp->smk_शेष;

	/*
	 * If this is the root inode the superblock
	 * may be in the process of initialization.
	 * If that is the हाल use the root value out
	 * of the superblock.
	 */
	अगर (opt_dentry->d_parent == opt_dentry) अणु
		चयन (sbp->s_magic) अणु
		हाल CGROUP_SUPER_MAGIC:
		हाल CGROUP2_SUPER_MAGIC:
			/*
			 * The cgroup fileप्रणाली is never mounted,
			 * so there's no opportunity to set the mount
			 * options.
			 */
			sbsp->smk_root = &smack_known_star;
			sbsp->smk_शेष = &smack_known_star;
			isp->smk_inode = sbsp->smk_root;
			अवरोध;
		हाल TMPFS_MAGIC:
			/*
			 * What about shmem/पंचांगpfs anonymous files with dentry
			 * obtained from d_alloc_pseuकरो()?
			 */
			isp->smk_inode = smk_of_current();
			अवरोध;
		हाल PIPEFS_MAGIC:
			isp->smk_inode = smk_of_current();
			अवरोध;
		हाल SOCKFS_MAGIC:
			/*
			 * Socket access is controlled by the socket
			 * काष्ठाures associated with the task involved.
			 */
			isp->smk_inode = &smack_known_star;
			अवरोध;
		शेष:
			isp->smk_inode = sbsp->smk_root;
			अवरोध;
		पूर्ण
		isp->smk_flags |= SMK_INODE_INSTANT;
		वापस;
	पूर्ण

	/*
	 * This is pretty hackish.
	 * Casey says that we shouldn't have to करो
	 * file प्रणाली specअगरic code, but it करोes help
	 * with keeping it simple.
	 */
	चयन (sbp->s_magic) अणु
	हाल SMACK_MAGIC:
	हाल CGROUP_SUPER_MAGIC:
	हाल CGROUP2_SUPER_MAGIC:
		/*
		 * Casey says that it's a little embarrassing
		 * that the smack file प्रणाली करोesn't करो
		 * extended attributes.
		 *
		 * Cgroupfs is special
		 */
		final = &smack_known_star;
		अवरोध;
	हाल DEVPTS_SUPER_MAGIC:
		/*
		 * devpts seems content with the label of the task.
		 * Programs that change smack have to treat the
		 * pty with respect.
		 */
		final = ckp;
		अवरोध;
	हाल PROC_SUPER_MAGIC:
		/*
		 * Casey says procfs appears not to care.
		 * The superblock शेष suffices.
		 */
		अवरोध;
	हाल TMPFS_MAGIC:
		/*
		 * Device labels should come from the fileप्रणाली,
		 * but watch out, because they're volitile,
		 * getting recreated on every reboot.
		 */
		final = &smack_known_star;
		/*
		 * If a smack value has been set we want to use it,
		 * but since पंचांगpfs isn't giving us the opportunity
		 * to set mount options simulate setting the
		 * superblock शेष.
		 */
		fallthrough;
	शेष:
		/*
		 * This isn't an understood special हाल.
		 * Get the value from the xattr.
		 */

		/*
		 * UNIX करोमुख्य sockets use lower level socket data.
		 */
		अगर (S_ISSOCK(inode->i_mode)) अणु
			final = &smack_known_star;
			अवरोध;
		पूर्ण
		/*
		 * No xattr support means, alas, no SMACK label.
		 * Use the aक्रमeapplied शेष.
		 * It would be curious अगर the label of the task
		 * करोes not match that asचिन्हित.
		 */
		अगर (!(inode->i_opflags & IOP_XATTR))
		        अवरोध;
		/*
		 * Get the dentry क्रम xattr.
		 */
		dp = dget(opt_dentry);
		skp = smk_fetch(XATTR_NAME_SMACK, inode, dp);
		अगर (!IS_ERR_OR_शून्य(skp))
			final = skp;

		/*
		 * Transmuting directory
		 */
		अगर (S_ISसूची(inode->i_mode)) अणु
			/*
			 * If this is a new directory and the label was
			 * transmuted when the inode was initialized
			 * set the transmute attribute on the directory
			 * and mark the inode.
			 *
			 * If there is a transmute attribute on the
			 * directory mark the inode.
			 */
			अगर (isp->smk_flags & SMK_INODE_CHANGED) अणु
				isp->smk_flags &= ~SMK_INODE_CHANGED;
				rc = __vfs_setxattr(&init_user_ns, dp, inode,
					XATTR_NAME_SMACKTRANSMUTE,
					TRANS_TRUE, TRANS_TRUE_SIZE,
					0);
			पूर्ण अन्यथा अणु
				rc = __vfs_getxattr(dp, inode,
					XATTR_NAME_SMACKTRANSMUTE, trattr,
					TRANS_TRUE_SIZE);
				अगर (rc >= 0 && म_भेदन(trattr, TRANS_TRUE,
						       TRANS_TRUE_SIZE) != 0)
					rc = -EINVAL;
			पूर्ण
			अगर (rc >= 0)
				transflag = SMK_INODE_TRANSMUTE;
		पूर्ण
		/*
		 * Don't let the exec or mmap label be "*" or "@".
		 */
		skp = smk_fetch(XATTR_NAME_SMACKEXEC, inode, dp);
		अगर (IS_ERR(skp) || skp == &smack_known_star ||
		    skp == &smack_known_web)
			skp = शून्य;
		isp->smk_task = skp;

		skp = smk_fetch(XATTR_NAME_SMACKMMAP, inode, dp);
		अगर (IS_ERR(skp) || skp == &smack_known_star ||
		    skp == &smack_known_web)
			skp = शून्य;
		isp->smk_mmap = skp;

		dput(dp);
		अवरोध;
	पूर्ण

	अगर (final == शून्य)
		isp->smk_inode = ckp;
	अन्यथा
		isp->smk_inode = final;

	isp->smk_flags |= (SMK_INODE_INSTANT | transflag);

	वापस;
पूर्ण

/**
 * smack_getprocattr - Smack process attribute access
 * @p: the object task
 * @name: the name of the attribute in /proc/.../attr
 * @value: where to put the result
 *
 * Places a copy of the task Smack पूर्णांकo value
 *
 * Returns the length of the smack label or an error code
 */
अटल पूर्णांक smack_getprocattr(काष्ठा task_काष्ठा *p, अक्षर *name, अक्षर **value)
अणु
	काष्ठा smack_known *skp = smk_of_task_काष्ठा_subj(p);
	अक्षर *cp;
	पूर्णांक slen;

	अगर (म_भेद(name, "current") != 0)
		वापस -EINVAL;

	cp = kstrdup(skp->smk_known, GFP_KERNEL);
	अगर (cp == शून्य)
		वापस -ENOMEM;

	slen = म_माप(cp);
	*value = cp;
	वापस slen;
पूर्ण

/**
 * smack_setprocattr - Smack process attribute setting
 * @name: the name of the attribute in /proc/.../attr
 * @value: the value to set
 * @size: the size of the value
 *
 * Sets the Smack value of the task. Only setting self
 * is permitted and only with privilege
 *
 * Returns the length of the smack label or an error code
 */
अटल पूर्णांक smack_setprocattr(स्थिर अक्षर *name, व्योम *value, माप_प्रकार size)
अणु
	काष्ठा task_smack *tsp = smack_cred(current_cred());
	काष्ठा cred *new;
	काष्ठा smack_known *skp;
	काष्ठा smack_known_list_elem *sklep;
	पूर्णांक rc;

	अगर (!smack_privileged(CAP_MAC_ADMIN) && list_empty(&tsp->smk_relabel))
		वापस -EPERM;

	अगर (value == शून्य || size == 0 || size >= SMK_LONGLABEL)
		वापस -EINVAL;

	अगर (म_भेद(name, "current") != 0)
		वापस -EINVAL;

	skp = smk_import_entry(value, size);
	अगर (IS_ERR(skp))
		वापस PTR_ERR(skp);

	/*
	 * No process is ever allowed the web ("@") label
	 * and the star ("*") label.
	 */
	अगर (skp == &smack_known_web || skp == &smack_known_star)
		वापस -EINVAL;

	अगर (!smack_privileged(CAP_MAC_ADMIN)) अणु
		rc = -EPERM;
		list_क्रम_each_entry(sklep, &tsp->smk_relabel, list)
			अगर (sklep->smk_label == skp) अणु
				rc = 0;
				अवरोध;
			पूर्ण
		अगर (rc)
			वापस rc;
	पूर्ण

	new = prepare_creds();
	अगर (new == शून्य)
		वापस -ENOMEM;

	tsp = smack_cred(new);
	tsp->smk_task = skp;
	/*
	 * process can change its label only once
	 */
	smk_destroy_label_list(&tsp->smk_relabel);

	commit_creds(new);
	वापस size;
पूर्ण

/**
 * smack_unix_stream_connect - Smack access on UDS
 * @sock: one sock
 * @other: the other sock
 * @newsk: unused
 *
 * Return 0 अगर a subject with the smack of sock could access
 * an object with the smack of other, otherwise an error code
 */
अटल पूर्णांक smack_unix_stream_connect(काष्ठा sock *sock,
				     काष्ठा sock *other, काष्ठा sock *newsk)
अणु
	काष्ठा smack_known *skp;
	काष्ठा smack_known *okp;
	काष्ठा socket_smack *ssp = sock->sk_security;
	काष्ठा socket_smack *osp = other->sk_security;
	काष्ठा socket_smack *nsp = newsk->sk_security;
	काष्ठा smk_audit_info ad;
	पूर्णांक rc = 0;
#अगर_घोषित CONFIG_AUDIT
	काष्ठा lsm_network_audit net;
#पूर्ण_अगर

	अगर (!smack_privileged(CAP_MAC_OVERRIDE)) अणु
		skp = ssp->smk_out;
		okp = osp->smk_in;
#अगर_घोषित CONFIG_AUDIT
		smk_ad_init_net(&ad, __func__, LSM_AUDIT_DATA_NET, &net);
		smk_ad_setfield_u_net_sk(&ad, other);
#पूर्ण_अगर
		rc = smk_access(skp, okp, MAY_WRITE, &ad);
		rc = smk_bu_note("UDS connect", skp, okp, MAY_WRITE, rc);
		अगर (rc == 0) अणु
			okp = osp->smk_out;
			skp = ssp->smk_in;
			rc = smk_access(okp, skp, MAY_WRITE, &ad);
			rc = smk_bu_note("UDS connect", okp, skp,
						MAY_WRITE, rc);
		पूर्ण
	पूर्ण

	/*
	 * Cross reference the peer labels क्रम SO_PEERSEC.
	 */
	अगर (rc == 0) अणु
		nsp->smk_packet = ssp->smk_out;
		ssp->smk_packet = osp->smk_out;
	पूर्ण

	वापस rc;
पूर्ण

/**
 * smack_unix_may_send - Smack access on UDS
 * @sock: one socket
 * @other: the other socket
 *
 * Return 0 अगर a subject with the smack of sock could access
 * an object with the smack of other, otherwise an error code
 */
अटल पूर्णांक smack_unix_may_send(काष्ठा socket *sock, काष्ठा socket *other)
अणु
	काष्ठा socket_smack *ssp = sock->sk->sk_security;
	काष्ठा socket_smack *osp = other->sk->sk_security;
	काष्ठा smk_audit_info ad;
	पूर्णांक rc;

#अगर_घोषित CONFIG_AUDIT
	काष्ठा lsm_network_audit net;

	smk_ad_init_net(&ad, __func__, LSM_AUDIT_DATA_NET, &net);
	smk_ad_setfield_u_net_sk(&ad, other->sk);
#पूर्ण_अगर

	अगर (smack_privileged(CAP_MAC_OVERRIDE))
		वापस 0;

	rc = smk_access(ssp->smk_out, osp->smk_in, MAY_WRITE, &ad);
	rc = smk_bu_note("UDS send", ssp->smk_out, osp->smk_in, MAY_WRITE, rc);
	वापस rc;
पूर्ण

/**
 * smack_socket_sendmsg - Smack check based on destination host
 * @sock: the socket
 * @msg: the message
 * @size: the size of the message
 *
 * Return 0 अगर the current subject can ग_लिखो to the destination host.
 * For IPv4 this is only a question अगर the destination is a single label host.
 * For IPv6 this is a check against the label of the port.
 */
अटल पूर्णांक smack_socket_sendmsg(काष्ठा socket *sock, काष्ठा msghdr *msg,
				पूर्णांक size)
अणु
	काष्ठा sockaddr_in *sip = (काष्ठा sockaddr_in *) msg->msg_name;
#अगर IS_ENABLED(CONFIG_IPV6)
	काष्ठा sockaddr_in6 *sap = (काष्ठा sockaddr_in6 *) msg->msg_name;
#पूर्ण_अगर
#अगर_घोषित SMACK_IPV6_SECMARK_LABELING
	काष्ठा socket_smack *ssp = sock->sk->sk_security;
	काष्ठा smack_known *rsp;
#पूर्ण_अगर
	पूर्णांक rc = 0;

	/*
	 * Perfectly reasonable क्रम this to be शून्य
	 */
	अगर (sip == शून्य)
		वापस 0;

	चयन (sock->sk->sk_family) अणु
	हाल AF_INET:
		अगर (msg->msg_namelen < माप(काष्ठा sockaddr_in) ||
		    sip->sin_family != AF_INET)
			वापस -EINVAL;
		rc = smk_ipv4_check(sock->sk, sip);
		अवरोध;
#अगर IS_ENABLED(CONFIG_IPV6)
	हाल AF_INET6:
		अगर (msg->msg_namelen < SIN6_LEN_RFC2133 ||
		    sap->sin6_family != AF_INET6)
			वापस -EINVAL;
#अगर_घोषित SMACK_IPV6_SECMARK_LABELING
		rsp = smack_ipv6host_label(sap);
		अगर (rsp != शून्य)
			rc = smk_ipv6_check(ssp->smk_out, rsp, sap,
						SMK_CONNECTING);
#पूर्ण_अगर
#अगर_घोषित SMACK_IPV6_PORT_LABELING
		rc = smk_ipv6_port_check(sock->sk, sap, SMK_SENDING);
#पूर्ण_अगर
#पूर्ण_अगर /* IS_ENABLED(CONFIG_IPV6) */
		अवरोध;
	पूर्ण
	वापस rc;
पूर्ण

/**
 * smack_from_secattr - Convert a netlabel attr.mls.lvl/attr.mls.cat pair to smack
 * @sap: netlabel secattr
 * @ssp: socket security inक्रमmation
 *
 * Returns a poपूर्णांकer to a Smack label entry found on the label list.
 */
अटल काष्ठा smack_known *smack_from_secattr(काष्ठा netlbl_lsm_secattr *sap,
						काष्ठा socket_smack *ssp)
अणु
	काष्ठा smack_known *skp;
	पूर्णांक found = 0;
	पूर्णांक acat;
	पूर्णांक kcat;

	/*
	 * Netlabel found it in the cache.
	 */
	अगर ((sap->flags & NETLBL_SECATTR_CACHE) != 0)
		वापस (काष्ठा smack_known *)sap->cache->data;

	अगर ((sap->flags & NETLBL_SECATTR_SECID) != 0)
		/*
		 * Looks like a fallback, which gives us a secid.
		 */
		वापस smack_from_secid(sap->attr.secid);

	अगर ((sap->flags & NETLBL_SECATTR_MLS_LVL) != 0) अणु
		/*
		 * Looks like a CIPSO packet.
		 * If there are flags but no level netlabel isn't
		 * behaving the way we expect it to.
		 *
		 * Look it up in the label table
		 * Without guidance regarding the smack value
		 * क्रम the packet fall back on the network
		 * ambient value.
		 */
		rcu_पढ़ो_lock();
		list_क्रम_each_entry_rcu(skp, &smack_known_list, list) अणु
			अगर (sap->attr.mls.lvl != skp->smk_netlabel.attr.mls.lvl)
				जारी;
			/*
			 * Compare the catsets. Use the netlbl APIs.
			 */
			अगर ((sap->flags & NETLBL_SECATTR_MLS_CAT) == 0) अणु
				अगर ((skp->smk_netlabel.flags &
				     NETLBL_SECATTR_MLS_CAT) == 0)
					found = 1;
				अवरोध;
			पूर्ण
			क्रम (acat = -1, kcat = -1; acat == kcat; ) अणु
				acat = netlbl_caपंचांगap_walk(sap->attr.mls.cat,
							  acat + 1);
				kcat = netlbl_caपंचांगap_walk(
					skp->smk_netlabel.attr.mls.cat,
					kcat + 1);
				अगर (acat < 0 || kcat < 0)
					अवरोध;
			पूर्ण
			अगर (acat == kcat) अणु
				found = 1;
				अवरोध;
			पूर्ण
		पूर्ण
		rcu_पढ़ो_unlock();

		अगर (found)
			वापस skp;

		अगर (ssp != शून्य && ssp->smk_in == &smack_known_star)
			वापस &smack_known_web;
		वापस &smack_known_star;
	पूर्ण
	/*
	 * Without guidance regarding the smack value
	 * क्रम the packet fall back on the network
	 * ambient value.
	 */
	वापस smack_net_ambient;
पूर्ण

#अगर IS_ENABLED(CONFIG_IPV6)
अटल पूर्णांक smk_skb_to_addr_ipv6(काष्ठा sk_buff *skb, काष्ठा sockaddr_in6 *sip)
अणु
	u8 nexthdr;
	पूर्णांक offset;
	पूर्णांक proto = -EINVAL;
	काष्ठा ipv6hdr _ipv6h;
	काष्ठा ipv6hdr *ip6;
	__be16 frag_off;
	काष्ठा tcphdr _tcph, *th;
	काष्ठा udphdr _udph, *uh;
	काष्ठा dccp_hdr _dccph, *dh;

	sip->sin6_port = 0;

	offset = skb_network_offset(skb);
	ip6 = skb_header_poपूर्णांकer(skb, offset, माप(_ipv6h), &_ipv6h);
	अगर (ip6 == शून्य)
		वापस -EINVAL;
	sip->sin6_addr = ip6->saddr;

	nexthdr = ip6->nexthdr;
	offset += माप(_ipv6h);
	offset = ipv6_skip_exthdr(skb, offset, &nexthdr, &frag_off);
	अगर (offset < 0)
		वापस -EINVAL;

	proto = nexthdr;
	चयन (proto) अणु
	हाल IPPROTO_TCP:
		th = skb_header_poपूर्णांकer(skb, offset, माप(_tcph), &_tcph);
		अगर (th != शून्य)
			sip->sin6_port = th->source;
		अवरोध;
	हाल IPPROTO_UDP:
	हाल IPPROTO_UDPLITE:
		uh = skb_header_poपूर्णांकer(skb, offset, माप(_udph), &_udph);
		अगर (uh != शून्य)
			sip->sin6_port = uh->source;
		अवरोध;
	हाल IPPROTO_DCCP:
		dh = skb_header_poपूर्णांकer(skb, offset, माप(_dccph), &_dccph);
		अगर (dh != शून्य)
			sip->sin6_port = dh->dccph_sport;
		अवरोध;
	पूर्ण
	वापस proto;
पूर्ण
#पूर्ण_अगर /* CONFIG_IPV6 */

/**
 * smack_from_skb - Smack data from the secmark in an skb
 * @skb: packet
 *
 * Returns smack_known of the secmark or शून्य अगर that won't work.
 */
#अगर_घोषित CONFIG_NETWORK_SECMARK
अटल काष्ठा smack_known *smack_from_skb(काष्ठा sk_buff *skb)
अणु
	अगर (skb == शून्य || skb->secmark == 0)
		वापस शून्य;

	वापस smack_from_secid(skb->secmark);
पूर्ण
#अन्यथा
अटल अंतरभूत काष्ठा smack_known *smack_from_skb(काष्ठा sk_buff *skb)
अणु
	वापस शून्य;
पूर्ण
#पूर्ण_अगर

/**
 * smack_from_netlbl - Smack data from the IP options in an skb
 * @sk: socket data came in on
 * @family: address family
 * @skb: packet
 *
 * Find the Smack label in the IP options. If it hasn't been
 * added to the netlabel cache, add it here.
 *
 * Returns smack_known of the IP options or शून्य अगर that won't work.
 */
अटल काष्ठा smack_known *smack_from_netlbl(स्थिर काष्ठा sock *sk, u16 family,
					     काष्ठा sk_buff *skb)
अणु
	काष्ठा netlbl_lsm_secattr secattr;
	काष्ठा socket_smack *ssp = शून्य;
	काष्ठा smack_known *skp = शून्य;

	netlbl_secattr_init(&secattr);

	अगर (sk)
		ssp = sk->sk_security;

	अगर (netlbl_skbuff_getattr(skb, family, &secattr) == 0) अणु
		skp = smack_from_secattr(&secattr, ssp);
		अगर (secattr.flags & NETLBL_SECATTR_CACHEABLE)
			netlbl_cache_add(skb, family, &skp->smk_netlabel);
	पूर्ण

	netlbl_secattr_destroy(&secattr);

	वापस skp;
पूर्ण

/**
 * smack_socket_sock_rcv_skb - Smack packet delivery access check
 * @sk: socket
 * @skb: packet
 *
 * Returns 0 अगर the packet should be delivered, an error code otherwise
 */
अटल पूर्णांक smack_socket_sock_rcv_skb(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	काष्ठा socket_smack *ssp = sk->sk_security;
	काष्ठा smack_known *skp = शून्य;
	पूर्णांक rc = 0;
	काष्ठा smk_audit_info ad;
	u16 family = sk->sk_family;
#अगर_घोषित CONFIG_AUDIT
	काष्ठा lsm_network_audit net;
#पूर्ण_अगर
#अगर IS_ENABLED(CONFIG_IPV6)
	काष्ठा sockaddr_in6 sadd;
	पूर्णांक proto;

	अगर (family == PF_INET6 && skb->protocol == htons(ETH_P_IP))
		family = PF_INET;
#पूर्ण_अगर /* CONFIG_IPV6 */

	चयन (family) अणु
	हाल PF_INET:
		/*
		 * If there is a secmark use it rather than the CIPSO label.
		 * If there is no secmark fall back to CIPSO.
		 * The secmark is assumed to reflect policy better.
		 */
		skp = smack_from_skb(skb);
		अगर (skp == शून्य) अणु
			skp = smack_from_netlbl(sk, family, skb);
			अगर (skp == शून्य)
				skp = smack_net_ambient;
		पूर्ण

#अगर_घोषित CONFIG_AUDIT
		smk_ad_init_net(&ad, __func__, LSM_AUDIT_DATA_NET, &net);
		ad.a.u.net->family = family;
		ad.a.u.net->netअगर = skb->skb_iअगर;
		ipv4_skb_to_auditdata(skb, &ad.a, शून्य);
#पूर्ण_अगर
		/*
		 * Receiving a packet requires that the other end
		 * be able to ग_लिखो here. Read access is not required.
		 * This is the simplist possible security model
		 * क्रम networking.
		 */
		rc = smk_access(skp, ssp->smk_in, MAY_WRITE, &ad);
		rc = smk_bu_note("IPv4 delivery", skp, ssp->smk_in,
					MAY_WRITE, rc);
		अगर (rc != 0)
			netlbl_skbuff_err(skb, family, rc, 0);
		अवरोध;
#अगर IS_ENABLED(CONFIG_IPV6)
	हाल PF_INET6:
		proto = smk_skb_to_addr_ipv6(skb, &sadd);
		अगर (proto != IPPROTO_UDP && proto != IPPROTO_UDPLITE &&
		    proto != IPPROTO_TCP && proto != IPPROTO_DCCP)
			अवरोध;
#अगर_घोषित SMACK_IPV6_SECMARK_LABELING
		skp = smack_from_skb(skb);
		अगर (skp == शून्य) अणु
			अगर (smk_ipv6_localhost(&sadd))
				अवरोध;
			skp = smack_ipv6host_label(&sadd);
			अगर (skp == शून्य)
				skp = smack_net_ambient;
		पूर्ण
#अगर_घोषित CONFIG_AUDIT
		smk_ad_init_net(&ad, __func__, LSM_AUDIT_DATA_NET, &net);
		ad.a.u.net->family = family;
		ad.a.u.net->netअगर = skb->skb_iअगर;
		ipv6_skb_to_auditdata(skb, &ad.a, शून्य);
#पूर्ण_अगर /* CONFIG_AUDIT */
		rc = smk_access(skp, ssp->smk_in, MAY_WRITE, &ad);
		rc = smk_bu_note("IPv6 delivery", skp, ssp->smk_in,
					MAY_WRITE, rc);
#पूर्ण_अगर /* SMACK_IPV6_SECMARK_LABELING */
#अगर_घोषित SMACK_IPV6_PORT_LABELING
		rc = smk_ipv6_port_check(sk, &sadd, SMK_RECEIVING);
#पूर्ण_अगर /* SMACK_IPV6_PORT_LABELING */
		अगर (rc != 0)
			icmpv6_send(skb, ICMPV6_DEST_UNREACH,
					ICMPV6_ADM_PROHIBITED, 0);
		अवरोध;
#पूर्ण_अगर /* CONFIG_IPV6 */
	पूर्ण

	वापस rc;
पूर्ण

/**
 * smack_socket_getpeersec_stream - pull in packet label
 * @sock: the socket
 * @optval: user's destination
 * @optlen: size thereof
 * @len: max thereof
 *
 * वापसs zero on success, an error code otherwise
 */
अटल पूर्णांक smack_socket_getpeersec_stream(काष्ठा socket *sock,
					  अक्षर __user *optval,
					  पूर्णांक __user *optlen, अचिन्हित len)
अणु
	काष्ठा socket_smack *ssp;
	अक्षर *rcp = "";
	पूर्णांक slen = 1;
	पूर्णांक rc = 0;

	ssp = sock->sk->sk_security;
	अगर (ssp->smk_packet != शून्य) अणु
		rcp = ssp->smk_packet->smk_known;
		slen = म_माप(rcp) + 1;
	पूर्ण

	अगर (slen > len)
		rc = -दुस्फल;
	अन्यथा अगर (copy_to_user(optval, rcp, slen) != 0)
		rc = -EFAULT;

	अगर (put_user(slen, optlen) != 0)
		rc = -EFAULT;

	वापस rc;
पूर्ण


/**
 * smack_socket_getpeersec_dgram - pull in packet label
 * @sock: the peer socket
 * @skb: packet data
 * @secid: poपूर्णांकer to where to put the secid of the packet
 *
 * Sets the netlabel socket state on sk from parent
 */
अटल पूर्णांक smack_socket_getpeersec_dgram(काष्ठा socket *sock,
					 काष्ठा sk_buff *skb, u32 *secid)

अणु
	काष्ठा socket_smack *ssp = शून्य;
	काष्ठा smack_known *skp;
	काष्ठा sock *sk = शून्य;
	पूर्णांक family = PF_UNSPEC;
	u32 s = 0;	/* 0 is the invalid secid */

	अगर (skb != शून्य) अणु
		अगर (skb->protocol == htons(ETH_P_IP))
			family = PF_INET;
#अगर IS_ENABLED(CONFIG_IPV6)
		अन्यथा अगर (skb->protocol == htons(ETH_P_IPV6))
			family = PF_INET6;
#पूर्ण_अगर /* CONFIG_IPV6 */
	पूर्ण
	अगर (family == PF_UNSPEC && sock != शून्य)
		family = sock->sk->sk_family;

	चयन (family) अणु
	हाल PF_UNIX:
		ssp = sock->sk->sk_security;
		s = ssp->smk_out->smk_secid;
		अवरोध;
	हाल PF_INET:
		skp = smack_from_skb(skb);
		अगर (skp) अणु
			s = skp->smk_secid;
			अवरोध;
		पूर्ण
		/*
		 * Translate what netlabel gave us.
		 */
		अगर (sock != शून्य)
			sk = sock->sk;
		skp = smack_from_netlbl(sk, family, skb);
		अगर (skp != शून्य)
			s = skp->smk_secid;
		अवरोध;
	हाल PF_INET6:
#अगर_घोषित SMACK_IPV6_SECMARK_LABELING
		skp = smack_from_skb(skb);
		अगर (skp)
			s = skp->smk_secid;
#पूर्ण_अगर
		अवरोध;
	पूर्ण
	*secid = s;
	अगर (s == 0)
		वापस -EINVAL;
	वापस 0;
पूर्ण

/**
 * smack_sock_graft - Initialize a newly created socket with an existing sock
 * @sk: child sock
 * @parent: parent socket
 *
 * Set the smk_अणुin,outपूर्ण state of an existing sock based on the process that
 * is creating the new socket.
 */
अटल व्योम smack_sock_graft(काष्ठा sock *sk, काष्ठा socket *parent)
अणु
	काष्ठा socket_smack *ssp;
	काष्ठा smack_known *skp = smk_of_current();

	अगर (sk == शून्य ||
	    (sk->sk_family != PF_INET && sk->sk_family != PF_INET6))
		वापस;

	ssp = sk->sk_security;
	ssp->smk_in = skp;
	ssp->smk_out = skp;
	/* cssp->smk_packet is alपढ़ोy set in smack_inet_csk_clone() */
पूर्ण

/**
 * smack_inet_conn_request - Smack access check on connect
 * @sk: socket involved
 * @skb: packet
 * @req: unused
 *
 * Returns 0 अगर a task with the packet label could ग_लिखो to
 * the socket, otherwise an error code
 */
अटल पूर्णांक smack_inet_conn_request(स्थिर काष्ठा sock *sk, काष्ठा sk_buff *skb,
				   काष्ठा request_sock *req)
अणु
	u16 family = sk->sk_family;
	काष्ठा smack_known *skp;
	काष्ठा socket_smack *ssp = sk->sk_security;
	काष्ठा sockaddr_in addr;
	काष्ठा iphdr *hdr;
	काष्ठा smack_known *hskp;
	पूर्णांक rc;
	काष्ठा smk_audit_info ad;
#अगर_घोषित CONFIG_AUDIT
	काष्ठा lsm_network_audit net;
#पूर्ण_अगर

#अगर IS_ENABLED(CONFIG_IPV6)
	अगर (family == PF_INET6) अणु
		/*
		 * Handle mapped IPv4 packets arriving
		 * via IPv6 sockets. Don't set up netlabel
		 * processing on IPv6.
		 */
		अगर (skb->protocol == htons(ETH_P_IP))
			family = PF_INET;
		अन्यथा
			वापस 0;
	पूर्ण
#पूर्ण_अगर /* CONFIG_IPV6 */

	/*
	 * If there is a secmark use it rather than the CIPSO label.
	 * If there is no secmark fall back to CIPSO.
	 * The secmark is assumed to reflect policy better.
	 */
	skp = smack_from_skb(skb);
	अगर (skp == शून्य) अणु
		skp = smack_from_netlbl(sk, family, skb);
		अगर (skp == शून्य)
			skp = &smack_known_huh;
	पूर्ण

#अगर_घोषित CONFIG_AUDIT
	smk_ad_init_net(&ad, __func__, LSM_AUDIT_DATA_NET, &net);
	ad.a.u.net->family = family;
	ad.a.u.net->netअगर = skb->skb_iअगर;
	ipv4_skb_to_auditdata(skb, &ad.a, शून्य);
#पूर्ण_अगर
	/*
	 * Receiving a packet requires that the other end be able to ग_लिखो
	 * here. Read access is not required.
	 */
	rc = smk_access(skp, ssp->smk_in, MAY_WRITE, &ad);
	rc = smk_bu_note("IPv4 connect", skp, ssp->smk_in, MAY_WRITE, rc);
	अगर (rc != 0)
		वापस rc;

	/*
	 * Save the peer's label in the request_sock so we can later setup
	 * smk_packet in the child socket so that SO_PEERCRED can report it.
	 */
	req->peer_secid = skp->smk_secid;

	/*
	 * We need to decide अगर we want to label the incoming connection here
	 * अगर we करो we only need to label the request_sock and the stack will
	 * propagate the wire-label to the sock when it is created.
	 */
	hdr = ip_hdr(skb);
	addr.sin_addr.s_addr = hdr->saddr;
	rcu_पढ़ो_lock();
	hskp = smack_ipv4host_label(&addr);
	rcu_पढ़ो_unlock();

	अगर (hskp == शून्य)
		rc = netlbl_req_setattr(req, &skp->smk_netlabel);
	अन्यथा
		netlbl_req_delattr(req);

	वापस rc;
पूर्ण

/**
 * smack_inet_csk_clone - Copy the connection inक्रमmation to the new socket
 * @sk: the new socket
 * @req: the connection's request_sock
 *
 * Transfer the connection's peer label to the newly created socket.
 */
अटल व्योम smack_inet_csk_clone(काष्ठा sock *sk,
				 स्थिर काष्ठा request_sock *req)
अणु
	काष्ठा socket_smack *ssp = sk->sk_security;
	काष्ठा smack_known *skp;

	अगर (req->peer_secid != 0) अणु
		skp = smack_from_secid(req->peer_secid);
		ssp->smk_packet = skp;
	पूर्ण अन्यथा
		ssp->smk_packet = शून्य;
पूर्ण

/*
 * Key management security hooks
 *
 * Casey has not tested key support very heavily.
 * The permission check is most likely too restrictive.
 * If you care about keys please have a look.
 */
#अगर_घोषित CONFIG_KEYS

/**
 * smack_key_alloc - Set the key security blob
 * @key: object
 * @cred: the credentials to use
 * @flags: unused
 *
 * No allocation required
 *
 * Returns 0
 */
अटल पूर्णांक smack_key_alloc(काष्ठा key *key, स्थिर काष्ठा cred *cred,
			   अचिन्हित दीर्घ flags)
अणु
	काष्ठा smack_known *skp = smk_of_task(smack_cred(cred));

	key->security = skp;
	वापस 0;
पूर्ण

/**
 * smack_key_मुक्त - Clear the key security blob
 * @key: the object
 *
 * Clear the blob poपूर्णांकer
 */
अटल व्योम smack_key_मुक्त(काष्ठा key *key)
अणु
	key->security = शून्य;
पूर्ण

/**
 * smack_key_permission - Smack access on a key
 * @key_ref: माला_लो to the object
 * @cred: the credentials to use
 * @need_perm: requested key permission
 *
 * Return 0 अगर the task has पढ़ो and ग_लिखो to the object,
 * an error code otherwise
 */
अटल पूर्णांक smack_key_permission(key_ref_t key_ref,
				स्थिर काष्ठा cred *cred,
				क्रमागत key_need_perm need_perm)
अणु
	काष्ठा key *keyp;
	काष्ठा smk_audit_info ad;
	काष्ठा smack_known *tkp = smk_of_task(smack_cred(cred));
	पूर्णांक request = 0;
	पूर्णांक rc;

	/*
	 * Validate requested permissions
	 */
	चयन (need_perm) अणु
	हाल KEY_NEED_READ:
	हाल KEY_NEED_SEARCH:
	हाल KEY_NEED_VIEW:
		request |= MAY_READ;
		अवरोध;
	हाल KEY_NEED_WRITE:
	हाल KEY_NEED_LINK:
	हाल KEY_NEED_SETATTR:
		request |= MAY_WRITE;
		अवरोध;
	हाल KEY_NEED_UNSPECIFIED:
	हाल KEY_NEED_UNLINK:
	हाल KEY_SYSADMIN_OVERRIDE:
	हाल KEY_AUTHTOKEN_OVERRIDE:
	हाल KEY_DEFER_PERM_CHECK:
		वापस 0;
	शेष:
		वापस -EINVAL;
	पूर्ण

	keyp = key_ref_to_ptr(key_ref);
	अगर (keyp == शून्य)
		वापस -EINVAL;
	/*
	 * If the key hasn't been initialized give it access so that
	 * it may करो so.
	 */
	अगर (keyp->security == शून्य)
		वापस 0;
	/*
	 * This should not occur
	 */
	अगर (tkp == शून्य)
		वापस -EACCES;

	अगर (smack_privileged(CAP_MAC_OVERRIDE))
		वापस 0;

#अगर_घोषित CONFIG_AUDIT
	smk_ad_init(&ad, __func__, LSM_AUDIT_DATA_KEY);
	ad.a.u.key_काष्ठा.key = keyp->serial;
	ad.a.u.key_काष्ठा.key_desc = keyp->description;
#पूर्ण_अगर
	rc = smk_access(tkp, keyp->security, request, &ad);
	rc = smk_bu_note("key access", tkp, keyp->security, request, rc);
	वापस rc;
पूर्ण

/*
 * smack_key_माला_लोecurity - Smack label tagging the key
 * @key poपूर्णांकs to the key to be queried
 * @_buffer poपूर्णांकs to a poपूर्णांकer that should be set to poपूर्णांक to the
 * resulting string (अगर no label or an error occurs).
 * Return the length of the string (including terminating NUL) or -ve अगर
 * an error.
 * May also वापस 0 (and a शून्य buffer poपूर्णांकer) अगर there is no label.
 */
अटल पूर्णांक smack_key_माला_लोecurity(काष्ठा key *key, अक्षर **_buffer)
अणु
	काष्ठा smack_known *skp = key->security;
	माप_प्रकार length;
	अक्षर *copy;

	अगर (key->security == शून्य) अणु
		*_buffer = शून्य;
		वापस 0;
	पूर्ण

	copy = kstrdup(skp->smk_known, GFP_KERNEL);
	अगर (copy == शून्य)
		वापस -ENOMEM;
	length = म_माप(copy) + 1;

	*_buffer = copy;
	वापस length;
पूर्ण


#अगर_घोषित CONFIG_KEY_NOTIFICATIONS
/**
 * smack_watch_key - Smack access to watch a key क्रम notअगरications.
 * @key: The key to be watched
 *
 * Return 0 अगर the @watch->cred has permission to पढ़ो from the key object and
 * an error otherwise.
 */
अटल पूर्णांक smack_watch_key(काष्ठा key *key)
अणु
	काष्ठा smk_audit_info ad;
	काष्ठा smack_known *tkp = smk_of_current();
	पूर्णांक rc;

	अगर (key == शून्य)
		वापस -EINVAL;
	/*
	 * If the key hasn't been initialized give it access so that
	 * it may करो so.
	 */
	अगर (key->security == शून्य)
		वापस 0;
	/*
	 * This should not occur
	 */
	अगर (tkp == शून्य)
		वापस -EACCES;

	अगर (smack_privileged_cred(CAP_MAC_OVERRIDE, current_cred()))
		वापस 0;

#अगर_घोषित CONFIG_AUDIT
	smk_ad_init(&ad, __func__, LSM_AUDIT_DATA_KEY);
	ad.a.u.key_काष्ठा.key = key->serial;
	ad.a.u.key_काष्ठा.key_desc = key->description;
#पूर्ण_अगर
	rc = smk_access(tkp, key->security, MAY_READ, &ad);
	rc = smk_bu_note("key watch", tkp, key->security, MAY_READ, rc);
	वापस rc;
पूर्ण
#पूर्ण_अगर /* CONFIG_KEY_NOTIFICATIONS */
#पूर्ण_अगर /* CONFIG_KEYS */

#अगर_घोषित CONFIG_WATCH_QUEUE
/**
 * smack_post_notअगरication - Smack access to post a notअगरication to a queue
 * @w_cred: The credentials of the watcher.
 * @cred: The credentials of the event source (may be शून्य).
 * @n: The notअगरication message to be posted.
 */
अटल पूर्णांक smack_post_notअगरication(स्थिर काष्ठा cred *w_cred,
				   स्थिर काष्ठा cred *cred,
				   काष्ठा watch_notअगरication *n)
अणु
	काष्ठा smk_audit_info ad;
	काष्ठा smack_known *subj, *obj;
	पूर्णांक rc;

	/* Always let मुख्यtenance notअगरications through. */
	अगर (n->type == WATCH_TYPE_META)
		वापस 0;

	अगर (!cred)
		वापस 0;
	subj = smk_of_task(smack_cred(cred));
	obj = smk_of_task(smack_cred(w_cred));

	smk_ad_init(&ad, __func__, LSM_AUDIT_DATA_NOTIFICATION);
	rc = smk_access(subj, obj, MAY_WRITE, &ad);
	rc = smk_bu_note("notification", subj, obj, MAY_WRITE, rc);
	वापस rc;
पूर्ण
#पूर्ण_अगर /* CONFIG_WATCH_QUEUE */

/*
 * Smack Audit hooks
 *
 * Audit requires a unique representation of each Smack specअगरic
 * rule. This unique representation is used to distinguish the
 * object to be audited from reमुख्यing kernel objects and also
 * works as a glue between the audit hooks.
 *
 * Since repository entries are added but never deleted, we'll use
 * the smack_known label address related to the given audit rule as
 * the needed unique representation. This also better fits the smack
 * model where nearly everything is a label.
 */
#अगर_घोषित CONFIG_AUDIT

/**
 * smack_audit_rule_init - Initialize a smack audit rule
 * @field: audit rule fields given from user-space (audit.h)
 * @op: required testing चालक (=, !=, >, <, ...)
 * @rulestr: smack label to be audited
 * @vrule: poपूर्णांकer to save our own audit rule representation
 *
 * Prepare to audit हालs where (@field @op @rulestr) is true.
 * The label to be audited is created अगर necessay.
 */
अटल पूर्णांक smack_audit_rule_init(u32 field, u32 op, अक्षर *rulestr, व्योम **vrule)
अणु
	काष्ठा smack_known *skp;
	अक्षर **rule = (अक्षर **)vrule;
	*rule = शून्य;

	अगर (field != AUDIT_SUBJ_USER && field != AUDIT_OBJ_USER)
		वापस -EINVAL;

	अगर (op != Audit_equal && op != Audit_not_equal)
		वापस -EINVAL;

	skp = smk_import_entry(rulestr, 0);
	अगर (IS_ERR(skp))
		वापस PTR_ERR(skp);

	*rule = skp->smk_known;

	वापस 0;
पूर्ण

/**
 * smack_audit_rule_known - Distinguish Smack audit rules
 * @krule: rule of पूर्णांकerest, in Audit kernel representation क्रमmat
 *
 * This is used to filter Smack rules from reमुख्यing Audit ones.
 * If it's proved that this rule beदीर्घs to us, the
 * audit_rule_match hook will be called to करो the final judgement.
 */
अटल पूर्णांक smack_audit_rule_known(काष्ठा audit_krule *krule)
अणु
	काष्ठा audit_field *f;
	पूर्णांक i;

	क्रम (i = 0; i < krule->field_count; i++) अणु
		f = &krule->fields[i];

		अगर (f->type == AUDIT_SUBJ_USER || f->type == AUDIT_OBJ_USER)
			वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * smack_audit_rule_match - Audit given object ?
 * @secid: security id क्रम identअगरying the object to test
 * @field: audit rule flags given from user-space
 * @op: required testing चालक
 * @vrule: smack पूर्णांकernal rule presentation
 *
 * The core Audit hook. It's used to take the decision of
 * whether to audit or not to audit a given object.
 */
अटल पूर्णांक smack_audit_rule_match(u32 secid, u32 field, u32 op, व्योम *vrule)
अणु
	काष्ठा smack_known *skp;
	अक्षर *rule = vrule;

	अगर (unlikely(!rule)) अणु
		WARN_ONCE(1, "Smack: missing rule\n");
		वापस -ENOENT;
	पूर्ण

	अगर (field != AUDIT_SUBJ_USER && field != AUDIT_OBJ_USER)
		वापस 0;

	skp = smack_from_secid(secid);

	/*
	 * No need to करो string comparisons. If a match occurs,
	 * both poपूर्णांकers will poपूर्णांक to the same smack_known
	 * label.
	 */
	अगर (op == Audit_equal)
		वापस (rule == skp->smk_known);
	अगर (op == Audit_not_equal)
		वापस (rule != skp->smk_known);

	वापस 0;
पूर्ण

/*
 * There is no need क्रम a smack_audit_rule_मुक्त hook.
 * No memory was allocated.
 */

#पूर्ण_अगर /* CONFIG_AUDIT */

/**
 * smack_ismaclabel - check अगर xattr @name references a smack MAC label
 * @name: Full xattr name to check.
 */
अटल पूर्णांक smack_ismaclabel(स्थिर अक्षर *name)
अणु
	वापस (म_भेद(name, XATTR_SMACK_SUFFIX) == 0);
पूर्ण


/**
 * smack_secid_to_secctx - वापस the smack label क्रम a secid
 * @secid: incoming पूर्णांकeger
 * @secdata: destination
 * @seclen: how दीर्घ it is
 *
 * Exists क्रम networking code.
 */
अटल पूर्णांक smack_secid_to_secctx(u32 secid, अक्षर **secdata, u32 *seclen)
अणु
	काष्ठा smack_known *skp = smack_from_secid(secid);

	अगर (secdata)
		*secdata = skp->smk_known;
	*seclen = म_माप(skp->smk_known);
	वापस 0;
पूर्ण

/**
 * smack_secctx_to_secid - वापस the secid क्रम a smack label
 * @secdata: smack label
 * @seclen: how दीर्घ result is
 * @secid: outgoing पूर्णांकeger
 *
 * Exists क्रम audit and networking code.
 */
अटल पूर्णांक smack_secctx_to_secid(स्थिर अक्षर *secdata, u32 seclen, u32 *secid)
अणु
	काष्ठा smack_known *skp = smk_find_entry(secdata);

	अगर (skp)
		*secid = skp->smk_secid;
	अन्यथा
		*secid = 0;
	वापस 0;
पूर्ण

/*
 * There used to be a smack_release_secctx hook
 * that did nothing back when hooks were in a vector.
 * Now that there's a list such a hook adds cost.
 */

अटल पूर्णांक smack_inode_notअगरysecctx(काष्ठा inode *inode, व्योम *ctx, u32 ctxlen)
अणु
	वापस smack_inode_setsecurity(inode, XATTR_SMACK_SUFFIX, ctx,
				       ctxlen, 0);
पूर्ण

अटल पूर्णांक smack_inode_setsecctx(काष्ठा dentry *dentry, व्योम *ctx, u32 ctxlen)
अणु
	वापस __vfs_setxattr_noperm(&init_user_ns, dentry, XATTR_NAME_SMACK,
				     ctx, ctxlen, 0);
पूर्ण

अटल पूर्णांक smack_inode_माला_लोecctx(काष्ठा inode *inode, व्योम **ctx, u32 *ctxlen)
अणु
	काष्ठा smack_known *skp = smk_of_inode(inode);

	*ctx = skp->smk_known;
	*ctxlen = म_माप(skp->smk_known);
	वापस 0;
पूर्ण

अटल पूर्णांक smack_inode_copy_up(काष्ठा dentry *dentry, काष्ठा cred **new)
अणु

	काष्ठा task_smack *tsp;
	काष्ठा smack_known *skp;
	काष्ठा inode_smack *isp;
	काष्ठा cred *new_creds = *new;

	अगर (new_creds == शून्य) अणु
		new_creds = prepare_creds();
		अगर (new_creds == शून्य)
			वापस -ENOMEM;
	पूर्ण

	tsp = smack_cred(new_creds);

	/*
	 * Get label from overlay inode and set it in create_sid
	 */
	isp = smack_inode(d_inode(dentry->d_parent));
	skp = isp->smk_inode;
	tsp->smk_task = skp;
	*new = new_creds;
	वापस 0;
पूर्ण

अटल पूर्णांक smack_inode_copy_up_xattr(स्थिर अक्षर *name)
अणु
	/*
	 * Return 1 अगर this is the smack access Smack attribute.
	 */
	अगर (म_भेद(name, XATTR_NAME_SMACK) == 0)
		वापस 1;

	वापस -EOPNOTSUPP;
पूर्ण

अटल पूर्णांक smack_dentry_create_files_as(काष्ठा dentry *dentry, पूर्णांक mode,
					काष्ठा qstr *name,
					स्थिर काष्ठा cred *old,
					काष्ठा cred *new)
अणु
	काष्ठा task_smack *otsp = smack_cred(old);
	काष्ठा task_smack *ntsp = smack_cred(new);
	काष्ठा inode_smack *isp;
	पूर्णांक may;

	/*
	 * Use the process credential unless all of
	 * the transmuting criteria are met
	 */
	ntsp->smk_task = otsp->smk_task;

	/*
	 * the attribute of the containing directory
	 */
	isp = smack_inode(d_inode(dentry->d_parent));

	अगर (isp->smk_flags & SMK_INODE_TRANSMUTE) अणु
		rcu_पढ़ो_lock();
		may = smk_access_entry(otsp->smk_task->smk_known,
				       isp->smk_inode->smk_known,
				       &otsp->smk_task->smk_rules);
		rcu_पढ़ो_unlock();

		/*
		 * If the directory is transmuting and the rule
		 * providing access is transmuting use the containing
		 * directory label instead of the process label.
		 */
		अगर (may > 0 && (may & MAY_TRANSMUTE))
			ntsp->smk_task = isp->smk_inode;
	पूर्ण
	वापस 0;
पूर्ण

काष्ठा lsm_blob_sizes smack_blob_sizes __lsm_ro_after_init = अणु
	.lbs_cred = माप(काष्ठा task_smack),
	.lbs_file = माप(काष्ठा smack_known *),
	.lbs_inode = माप(काष्ठा inode_smack),
	.lbs_ipc = माप(काष्ठा smack_known *),
	.lbs_msg_msg = माप(काष्ठा smack_known *),
	.lbs_superblock = माप(काष्ठा superblock_smack),
पूर्ण;

अटल काष्ठा security_hook_list smack_hooks[] __lsm_ro_after_init = अणु
	LSM_HOOK_INIT(ptrace_access_check, smack_ptrace_access_check),
	LSM_HOOK_INIT(ptrace_traceme, smack_ptrace_traceme),
	LSM_HOOK_INIT(syslog, smack_syslog),

	LSM_HOOK_INIT(fs_context_dup, smack_fs_context_dup),
	LSM_HOOK_INIT(fs_context_parse_param, smack_fs_context_parse_param),

	LSM_HOOK_INIT(sb_alloc_security, smack_sb_alloc_security),
	LSM_HOOK_INIT(sb_मुक्त_mnt_opts, smack_मुक्त_mnt_opts),
	LSM_HOOK_INIT(sb_eat_lsm_opts, smack_sb_eat_lsm_opts),
	LSM_HOOK_INIT(sb_statfs, smack_sb_statfs),
	LSM_HOOK_INIT(sb_set_mnt_opts, smack_set_mnt_opts),

	LSM_HOOK_INIT(bprm_creds_क्रम_exec, smack_bprm_creds_क्रम_exec),

	LSM_HOOK_INIT(inode_alloc_security, smack_inode_alloc_security),
	LSM_HOOK_INIT(inode_init_security, smack_inode_init_security),
	LSM_HOOK_INIT(inode_link, smack_inode_link),
	LSM_HOOK_INIT(inode_unlink, smack_inode_unlink),
	LSM_HOOK_INIT(inode_सूची_हटाओ, smack_inode_सूची_हटाओ),
	LSM_HOOK_INIT(inode_नाम, smack_inode_नाम),
	LSM_HOOK_INIT(inode_permission, smack_inode_permission),
	LSM_HOOK_INIT(inode_setattr, smack_inode_setattr),
	LSM_HOOK_INIT(inode_getattr, smack_inode_getattr),
	LSM_HOOK_INIT(inode_setxattr, smack_inode_setxattr),
	LSM_HOOK_INIT(inode_post_setxattr, smack_inode_post_setxattr),
	LSM_HOOK_INIT(inode_getxattr, smack_inode_getxattr),
	LSM_HOOK_INIT(inode_हटाओxattr, smack_inode_हटाओxattr),
	LSM_HOOK_INIT(inode_माला_लोecurity, smack_inode_माला_लोecurity),
	LSM_HOOK_INIT(inode_setsecurity, smack_inode_setsecurity),
	LSM_HOOK_INIT(inode_listsecurity, smack_inode_listsecurity),
	LSM_HOOK_INIT(inode_माला_लोecid, smack_inode_माला_लोecid),

	LSM_HOOK_INIT(file_alloc_security, smack_file_alloc_security),
	LSM_HOOK_INIT(file_ioctl, smack_file_ioctl),
	LSM_HOOK_INIT(file_lock, smack_file_lock),
	LSM_HOOK_INIT(file_fcntl, smack_file_fcntl),
	LSM_HOOK_INIT(mmap_file, smack_mmap_file),
	LSM_HOOK_INIT(mmap_addr, cap_mmap_addr),
	LSM_HOOK_INIT(file_set_fowner, smack_file_set_fowner),
	LSM_HOOK_INIT(file_send_sigiotask, smack_file_send_sigiotask),
	LSM_HOOK_INIT(file_receive, smack_file_receive),

	LSM_HOOK_INIT(file_खोलो, smack_file_खोलो),

	LSM_HOOK_INIT(cred_alloc_blank, smack_cred_alloc_blank),
	LSM_HOOK_INIT(cred_मुक्त, smack_cred_मुक्त),
	LSM_HOOK_INIT(cred_prepare, smack_cred_prepare),
	LSM_HOOK_INIT(cred_transfer, smack_cred_transfer),
	LSM_HOOK_INIT(cred_माला_लोecid, smack_cred_माला_लोecid),
	LSM_HOOK_INIT(kernel_act_as, smack_kernel_act_as),
	LSM_HOOK_INIT(kernel_create_files_as, smack_kernel_create_files_as),
	LSM_HOOK_INIT(task_setpgid, smack_task_setpgid),
	LSM_HOOK_INIT(task_getpgid, smack_task_getpgid),
	LSM_HOOK_INIT(task_माला_लोid, smack_task_माला_लोid),
	LSM_HOOK_INIT(task_माला_लोecid_subj, smack_task_माला_लोecid_subj),
	LSM_HOOK_INIT(task_माला_लोecid_obj, smack_task_माला_लोecid_obj),
	LSM_HOOK_INIT(task_setnice, smack_task_setnice),
	LSM_HOOK_INIT(task_setioprio, smack_task_setioprio),
	LSM_HOOK_INIT(task_getioprio, smack_task_getioprio),
	LSM_HOOK_INIT(task_setscheduler, smack_task_setscheduler),
	LSM_HOOK_INIT(task_माला_लोcheduler, smack_task_माला_लोcheduler),
	LSM_HOOK_INIT(task_movememory, smack_task_movememory),
	LSM_HOOK_INIT(task_समाप्त, smack_task_समाप्त),
	LSM_HOOK_INIT(task_to_inode, smack_task_to_inode),

	LSM_HOOK_INIT(ipc_permission, smack_ipc_permission),
	LSM_HOOK_INIT(ipc_माला_लोecid, smack_ipc_माला_लोecid),

	LSM_HOOK_INIT(msg_msg_alloc_security, smack_msg_msg_alloc_security),

	LSM_HOOK_INIT(msg_queue_alloc_security, smack_ipc_alloc_security),
	LSM_HOOK_INIT(msg_queue_associate, smack_msg_queue_associate),
	LSM_HOOK_INIT(msg_queue_msgctl, smack_msg_queue_msgctl),
	LSM_HOOK_INIT(msg_queue_msgsnd, smack_msg_queue_msgsnd),
	LSM_HOOK_INIT(msg_queue_msgrcv, smack_msg_queue_msgrcv),

	LSM_HOOK_INIT(shm_alloc_security, smack_ipc_alloc_security),
	LSM_HOOK_INIT(shm_associate, smack_shm_associate),
	LSM_HOOK_INIT(shm_shmctl, smack_shm_shmctl),
	LSM_HOOK_INIT(shm_shmat, smack_shm_shmat),

	LSM_HOOK_INIT(sem_alloc_security, smack_ipc_alloc_security),
	LSM_HOOK_INIT(sem_associate, smack_sem_associate),
	LSM_HOOK_INIT(sem_semctl, smack_sem_semctl),
	LSM_HOOK_INIT(sem_semop, smack_sem_semop),

	LSM_HOOK_INIT(d_instantiate, smack_d_instantiate),

	LSM_HOOK_INIT(getprocattr, smack_getprocattr),
	LSM_HOOK_INIT(setprocattr, smack_setprocattr),

	LSM_HOOK_INIT(unix_stream_connect, smack_unix_stream_connect),
	LSM_HOOK_INIT(unix_may_send, smack_unix_may_send),

	LSM_HOOK_INIT(socket_post_create, smack_socket_post_create),
	LSM_HOOK_INIT(socket_socketpair, smack_socket_socketpair),
#अगर_घोषित SMACK_IPV6_PORT_LABELING
	LSM_HOOK_INIT(socket_bind, smack_socket_bind),
#पूर्ण_अगर
	LSM_HOOK_INIT(socket_connect, smack_socket_connect),
	LSM_HOOK_INIT(socket_sendmsg, smack_socket_sendmsg),
	LSM_HOOK_INIT(socket_sock_rcv_skb, smack_socket_sock_rcv_skb),
	LSM_HOOK_INIT(socket_getpeersec_stream, smack_socket_getpeersec_stream),
	LSM_HOOK_INIT(socket_getpeersec_dgram, smack_socket_getpeersec_dgram),
	LSM_HOOK_INIT(sk_alloc_security, smack_sk_alloc_security),
	LSM_HOOK_INIT(sk_मुक्त_security, smack_sk_मुक्त_security),
	LSM_HOOK_INIT(sock_graft, smack_sock_graft),
	LSM_HOOK_INIT(inet_conn_request, smack_inet_conn_request),
	LSM_HOOK_INIT(inet_csk_clone, smack_inet_csk_clone),

 /* key management security hooks */
#अगर_घोषित CONFIG_KEYS
	LSM_HOOK_INIT(key_alloc, smack_key_alloc),
	LSM_HOOK_INIT(key_मुक्त, smack_key_मुक्त),
	LSM_HOOK_INIT(key_permission, smack_key_permission),
	LSM_HOOK_INIT(key_माला_लोecurity, smack_key_माला_लोecurity),
#अगर_घोषित CONFIG_KEY_NOTIFICATIONS
	LSM_HOOK_INIT(watch_key, smack_watch_key),
#पूर्ण_अगर
#पूर्ण_अगर /* CONFIG_KEYS */

#अगर_घोषित CONFIG_WATCH_QUEUE
	LSM_HOOK_INIT(post_notअगरication, smack_post_notअगरication),
#पूर्ण_अगर

 /* Audit hooks */
#अगर_घोषित CONFIG_AUDIT
	LSM_HOOK_INIT(audit_rule_init, smack_audit_rule_init),
	LSM_HOOK_INIT(audit_rule_known, smack_audit_rule_known),
	LSM_HOOK_INIT(audit_rule_match, smack_audit_rule_match),
#पूर्ण_अगर /* CONFIG_AUDIT */

	LSM_HOOK_INIT(ismaclabel, smack_ismaclabel),
	LSM_HOOK_INIT(secid_to_secctx, smack_secid_to_secctx),
	LSM_HOOK_INIT(secctx_to_secid, smack_secctx_to_secid),
	LSM_HOOK_INIT(inode_notअगरysecctx, smack_inode_notअगरysecctx),
	LSM_HOOK_INIT(inode_setsecctx, smack_inode_setsecctx),
	LSM_HOOK_INIT(inode_माला_लोecctx, smack_inode_माला_लोecctx),
	LSM_HOOK_INIT(inode_copy_up, smack_inode_copy_up),
	LSM_HOOK_INIT(inode_copy_up_xattr, smack_inode_copy_up_xattr),
	LSM_HOOK_INIT(dentry_create_files_as, smack_dentry_create_files_as),
पूर्ण;


अटल __init व्योम init_smack_known_list(व्योम)
अणु
	/*
	 * Initialize rule list locks
	 */
	mutex_init(&smack_known_huh.smk_rules_lock);
	mutex_init(&smack_known_hat.smk_rules_lock);
	mutex_init(&smack_known_न्यूनमान.smk_rules_lock);
	mutex_init(&smack_known_star.smk_rules_lock);
	mutex_init(&smack_known_web.smk_rules_lock);
	/*
	 * Initialize rule lists
	 */
	INIT_LIST_HEAD(&smack_known_huh.smk_rules);
	INIT_LIST_HEAD(&smack_known_hat.smk_rules);
	INIT_LIST_HEAD(&smack_known_star.smk_rules);
	INIT_LIST_HEAD(&smack_known_न्यूनमान.smk_rules);
	INIT_LIST_HEAD(&smack_known_web.smk_rules);
	/*
	 * Create the known labels list
	 */
	smk_insert_entry(&smack_known_huh);
	smk_insert_entry(&smack_known_hat);
	smk_insert_entry(&smack_known_star);
	smk_insert_entry(&smack_known_न्यूनमान);
	smk_insert_entry(&smack_known_web);
पूर्ण

/**
 * smack_init - initialize the smack प्रणाली
 *
 * Returns 0 on success, -ENOMEM is there's no memory
 */
अटल __init पूर्णांक smack_init(व्योम)
अणु
	काष्ठा cred *cred = (काष्ठा cred *) current->cred;
	काष्ठा task_smack *tsp;

	smack_rule_cache = KMEM_CACHE(smack_rule, 0);
	अगर (!smack_rule_cache)
		वापस -ENOMEM;

	/*
	 * Set the security state क्रम the initial task.
	 */
	tsp = smack_cred(cred);
	init_task_smack(tsp, &smack_known_न्यूनमान, &smack_known_न्यूनमान);

	/*
	 * Register with LSM
	 */
	security_add_hooks(smack_hooks, ARRAY_SIZE(smack_hooks), "smack");
	smack_enabled = 1;

	pr_info("Smack:  Initializing.\n");
#अगर_घोषित CONFIG_SECURITY_SMACK_NETFILTER
	pr_info("Smack:  Netfilter enabled.\n");
#पूर्ण_अगर
#अगर_घोषित SMACK_IPV6_PORT_LABELING
	pr_info("Smack:  IPv6 port labeling enabled.\n");
#पूर्ण_अगर
#अगर_घोषित SMACK_IPV6_SECMARK_LABELING
	pr_info("Smack:  IPv6 Netfilter enabled.\n");
#पूर्ण_अगर

	/* initialize the smack_known_list */
	init_smack_known_list();

	वापस 0;
पूर्ण

/*
 * Smack requires early initialization in order to label
 * all processes and objects when they are created.
 */
DEFINE_LSM(smack) = अणु
	.name = "smack",
	.flags = LSM_FLAG_LEGACY_MAJOR | LSM_FLAG_EXCLUSIVE,
	.blobs = &smack_blob_sizes,
	.init = smack_init,
पूर्ण;
