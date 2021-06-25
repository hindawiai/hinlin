<शैली गुरु>
/* auditsc.c -- System-call auditing support
 * Handles all प्रणाली-call specअगरic auditing features.
 *
 * Copyright 2003-2004 Red Hat Inc., Durham, North Carolina.
 * Copyright 2005 Hewlett-Packard Development Company, L.P.
 * Copyright (C) 2005, 2006 IBM Corporation
 * All Rights Reserved.
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License क्रम more details.
 *
 * You should have received a copy of the GNU General Public License
 * aदीर्घ with this program; अगर not, ग_लिखो to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * Written by Rickard E. (Rik) Faith <faith@redhat.com>
 *
 * Many of the ideas implemented here are from Stephen C. Tweedie,
 * especially the idea of aव्योमing a copy by using getname.
 *
 * The method क्रम actual पूर्णांकerception of syscall entry and निकास (not in
 * this file -- see entry.S) is based on a GPL'd patch written by
 * okir@suse.de and Copyright 2003 SuSE Linux AG.
 *
 * POSIX message queue support added by George Wilson <ltcgcw@us.ibm.com>,
 * 2006.
 *
 * The support of additional filter rules compares (>, <, >=, <=) was
 * added by Dustin Kirkland <dustin.kirkland@us.ibm.com>, 2005.
 *
 * Modअगरied by Amy Grअगरfis <amy.grअगरfis@hp.com> to collect additional
 * fileप्रणाली inक्रमmation.
 *
 * Subject and object context labeling support added by <danjones@us.ibm.com>
 * and <dustin.kirkland@us.ibm.com> क्रम LSPP certअगरication compliance.
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/init.h>
#समावेश <यंत्र/types.h>
#समावेश <linux/atomic.h>
#समावेश <linux/fs.h>
#समावेश <linux/namei.h>
#समावेश <linux/mm.h>
#समावेश <linux/export.h>
#समावेश <linux/slab.h>
#समावेश <linux/mount.h>
#समावेश <linux/socket.h>
#समावेश <linux/mqueue.h>
#समावेश <linux/audit.h>
#समावेश <linux/personality.h>
#समावेश <linux/समय.स>
#समावेश <linux/netlink.h>
#समावेश <linux/compiler.h>
#समावेश <यंत्र/unistd.h>
#समावेश <linux/security.h>
#समावेश <linux/list.h>
#समावेश <linux/binfmts.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/syscalls.h>
#समावेश <यंत्र/syscall.h>
#समावेश <linux/capability.h>
#समावेश <linux/fs_काष्ठा.h>
#समावेश <linux/compat.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/माला.स>
#समावेश <linux/uaccess.h>
#समावेश <linux/fsnotअगरy_backend.h>
#समावेश <uapi/linux/सीमा.स>
#समावेश <uapi/linux/netfilter/nf_tables.h>

#समावेश "audit.h"

/* flags stating the success क्रम a syscall */
#घोषणा AUDITSC_INVALID 0
#घोषणा AUDITSC_SUCCESS 1
#घोषणा AUDITSC_FAILURE 2

/* no execve audit message should be दीर्घer than this (userspace limits),
 * see the note near the top of audit_log_execve_info() about this value */
#घोषणा MAX_EXECVE_AUDIT_LEN 7500

/* max length to prपूर्णांक of cmdline/proctitle value during audit */
#घोषणा MAX_PROCTITLE_AUDIT_LEN 128

/* number of audit rules */
पूर्णांक audit_n_rules;

/* determines whether we collect data क्रम संकेतs sent */
पूर्णांक audit_संकेतs;

काष्ठा audit_aux_data अणु
	काष्ठा audit_aux_data	*next;
	पूर्णांक			type;
पूर्ण;

/* Number of target pids per aux काष्ठा. */
#घोषणा AUDIT_AUX_PIDS	16

काष्ठा audit_aux_data_pids अणु
	काष्ठा audit_aux_data	d;
	pid_t			target_pid[AUDIT_AUX_PIDS];
	kuid_t			target_auid[AUDIT_AUX_PIDS];
	kuid_t			target_uid[AUDIT_AUX_PIDS];
	अचिन्हित पूर्णांक		target_sessionid[AUDIT_AUX_PIDS];
	u32			target_sid[AUDIT_AUX_PIDS];
	अक्षर 			target_comm[AUDIT_AUX_PIDS][TASK_COMM_LEN];
	पूर्णांक			pid_count;
पूर्ण;

काष्ठा audit_aux_data_bprm_fcaps अणु
	काष्ठा audit_aux_data	d;
	काष्ठा audit_cap_data	fcap;
	अचिन्हित पूर्णांक		fcap_ver;
	काष्ठा audit_cap_data	old_pcap;
	काष्ठा audit_cap_data	new_pcap;
पूर्ण;

काष्ठा audit_tree_refs अणु
	काष्ठा audit_tree_refs *next;
	काष्ठा audit_chunk *c[31];
पूर्ण;

काष्ठा audit_nfcfgop_tab अणु
	क्रमागत audit_nfcfgop	op;
	स्थिर अक्षर		*s;
पूर्ण;

अटल स्थिर काष्ठा audit_nfcfgop_tab audit_nfcfgs[] = अणु
	अणु AUDIT_XT_OP_REGISTER,			"xt_register"		   पूर्ण,
	अणु AUDIT_XT_OP_REPLACE,			"xt_replace"		   पूर्ण,
	अणु AUDIT_XT_OP_UNREGISTER,		"xt_unregister"		   पूर्ण,
	अणु AUDIT_NFT_OP_TABLE_REGISTER,		"nft_register_table"	   पूर्ण,
	अणु AUDIT_NFT_OP_TABLE_UNREGISTER,	"nft_unregister_table"	   पूर्ण,
	अणु AUDIT_NFT_OP_CHAIN_REGISTER,		"nft_register_chain"	   पूर्ण,
	अणु AUDIT_NFT_OP_CHAIN_UNREGISTER,	"nft_unregister_chain"	   पूर्ण,
	अणु AUDIT_NFT_OP_RULE_REGISTER,		"nft_register_rule"	   पूर्ण,
	अणु AUDIT_NFT_OP_RULE_UNREGISTER,		"nft_unregister_rule"	   पूर्ण,
	अणु AUDIT_NFT_OP_SET_REGISTER,		"nft_register_set"	   पूर्ण,
	अणु AUDIT_NFT_OP_SET_UNREGISTER,		"nft_unregister_set"	   पूर्ण,
	अणु AUDIT_NFT_OP_SETELEM_REGISTER,	"nft_register_setelem"	   पूर्ण,
	अणु AUDIT_NFT_OP_SETELEM_UNREGISTER,	"nft_unregister_setelem"   पूर्ण,
	अणु AUDIT_NFT_OP_GEN_REGISTER,		"nft_register_gen"	   पूर्ण,
	अणु AUDIT_NFT_OP_OBJ_REGISTER,		"nft_register_obj"	   पूर्ण,
	अणु AUDIT_NFT_OP_OBJ_UNREGISTER,		"nft_unregister_obj"	   पूर्ण,
	अणु AUDIT_NFT_OP_OBJ_RESET,		"nft_reset_obj"		   पूर्ण,
	अणु AUDIT_NFT_OP_FLOWTABLE_REGISTER,	"nft_register_flowtable"   पूर्ण,
	अणु AUDIT_NFT_OP_FLOWTABLE_UNREGISTER,	"nft_unregister_flowtable" पूर्ण,
	अणु AUDIT_NFT_OP_INVALID,			"nft_invalid"		   पूर्ण,
पूर्ण;

अटल पूर्णांक audit_match_perm(काष्ठा audit_context *ctx, पूर्णांक mask)
अणु
	अचिन्हित n;
	अगर (unlikely(!ctx))
		वापस 0;
	n = ctx->major;

	चयन (audit_classअगरy_syscall(ctx->arch, n)) अणु
	हाल 0:	/* native */
		अगर ((mask & AUDIT_PERM_WRITE) &&
		     audit_match_class(AUDIT_CLASS_WRITE, n))
			वापस 1;
		अगर ((mask & AUDIT_PERM_READ) &&
		     audit_match_class(AUDIT_CLASS_READ, n))
			वापस 1;
		अगर ((mask & AUDIT_PERM_ATTR) &&
		     audit_match_class(AUDIT_CLASS_CHATTR, n))
			वापस 1;
		वापस 0;
	हाल 1: /* 32bit on biarch */
		अगर ((mask & AUDIT_PERM_WRITE) &&
		     audit_match_class(AUDIT_CLASS_WRITE_32, n))
			वापस 1;
		अगर ((mask & AUDIT_PERM_READ) &&
		     audit_match_class(AUDIT_CLASS_READ_32, n))
			वापस 1;
		अगर ((mask & AUDIT_PERM_ATTR) &&
		     audit_match_class(AUDIT_CLASS_CHATTR_32, n))
			वापस 1;
		वापस 0;
	हाल 2: /* खोलो */
		वापस mask & ACC_MODE(ctx->argv[1]);
	हाल 3: /* खोलोat */
		वापस mask & ACC_MODE(ctx->argv[2]);
	हाल 4: /* socketcall */
		वापस ((mask & AUDIT_PERM_WRITE) && ctx->argv[0] == SYS_BIND);
	हाल 5: /* execve */
		वापस mask & AUDIT_PERM_EXEC;
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

अटल पूर्णांक audit_match_filetype(काष्ठा audit_context *ctx, पूर्णांक val)
अणु
	काष्ठा audit_names *n;
	umode_t mode = (umode_t)val;

	अगर (unlikely(!ctx))
		वापस 0;

	list_क्रम_each_entry(n, &ctx->names_list, list) अणु
		अगर ((n->ino != AUDIT_INO_UNSET) &&
		    ((n->mode & S_IFMT) == mode))
			वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * We keep a linked list of fixed-sized (31 poपूर्णांकer) arrays of audit_chunk *;
 * ->first_trees poपूर्णांकs to its beginning, ->trees - to the current end of data.
 * ->tree_count is the number of मुक्त entries in array poपूर्णांकed to by ->trees.
 * Original condition is (शून्य, शून्य, 0); as soon as it grows we never revert to शून्य,
 * "empty" becomes (p, p, 31) afterwards.  We करोn't shrink the list (and seriously,
 * it's going to reमुख्य 1-element क्रम almost any setup) until we मुक्त context itself.
 * References in it _are_ dropped - at the same समय we मुक्त/drop aux stuff.
 */

अटल व्योम audit_set_auditable(काष्ठा audit_context *ctx)
अणु
	अगर (!ctx->prio) अणु
		ctx->prio = 1;
		ctx->current_state = AUDIT_RECORD_CONTEXT;
	पूर्ण
पूर्ण

अटल पूर्णांक put_tree_ref(काष्ठा audit_context *ctx, काष्ठा audit_chunk *chunk)
अणु
	काष्ठा audit_tree_refs *p = ctx->trees;
	पूर्णांक left = ctx->tree_count;
	अगर (likely(left)) अणु
		p->c[--left] = chunk;
		ctx->tree_count = left;
		वापस 1;
	पूर्ण
	अगर (!p)
		वापस 0;
	p = p->next;
	अगर (p) अणु
		p->c[30] = chunk;
		ctx->trees = p;
		ctx->tree_count = 30;
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक grow_tree_refs(काष्ठा audit_context *ctx)
अणु
	काष्ठा audit_tree_refs *p = ctx->trees;
	ctx->trees = kzalloc(माप(काष्ठा audit_tree_refs), GFP_KERNEL);
	अगर (!ctx->trees) अणु
		ctx->trees = p;
		वापस 0;
	पूर्ण
	अगर (p)
		p->next = ctx->trees;
	अन्यथा
		ctx->first_trees = ctx->trees;
	ctx->tree_count = 31;
	वापस 1;
पूर्ण

अटल व्योम unroll_tree_refs(काष्ठा audit_context *ctx,
		      काष्ठा audit_tree_refs *p, पूर्णांक count)
अणु
	काष्ठा audit_tree_refs *q;
	पूर्णांक n;
	अगर (!p) अणु
		/* we started with empty chain */
		p = ctx->first_trees;
		count = 31;
		/* अगर the very first allocation has failed, nothing to करो */
		अगर (!p)
			वापस;
	पूर्ण
	n = count;
	क्रम (q = p; q != ctx->trees; q = q->next, n = 31) अणु
		जबतक (n--) अणु
			audit_put_chunk(q->c[n]);
			q->c[n] = शून्य;
		पूर्ण
	पूर्ण
	जबतक (n-- > ctx->tree_count) अणु
		audit_put_chunk(q->c[n]);
		q->c[n] = शून्य;
	पूर्ण
	ctx->trees = p;
	ctx->tree_count = count;
पूर्ण

अटल व्योम मुक्त_tree_refs(काष्ठा audit_context *ctx)
अणु
	काष्ठा audit_tree_refs *p, *q;
	क्रम (p = ctx->first_trees; p; p = q) अणु
		q = p->next;
		kमुक्त(p);
	पूर्ण
पूर्ण

अटल पूर्णांक match_tree_refs(काष्ठा audit_context *ctx, काष्ठा audit_tree *tree)
अणु
	काष्ठा audit_tree_refs *p;
	पूर्णांक n;
	अगर (!tree)
		वापस 0;
	/* full ones */
	क्रम (p = ctx->first_trees; p != ctx->trees; p = p->next) अणु
		क्रम (n = 0; n < 31; n++)
			अगर (audit_tree_match(p->c[n], tree))
				वापस 1;
	पूर्ण
	/* partial */
	अगर (p) अणु
		क्रम (n = ctx->tree_count; n < 31; n++)
			अगर (audit_tree_match(p->c[n], tree))
				वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक audit_compare_uid(kuid_t uid,
			     काष्ठा audit_names *name,
			     काष्ठा audit_field *f,
			     काष्ठा audit_context *ctx)
अणु
	काष्ठा audit_names *n;
	पूर्णांक rc;
 
	अगर (name) अणु
		rc = audit_uid_comparator(uid, f->op, name->uid);
		अगर (rc)
			वापस rc;
	पूर्ण
 
	अगर (ctx) अणु
		list_क्रम_each_entry(n, &ctx->names_list, list) अणु
			rc = audit_uid_comparator(uid, f->op, n->uid);
			अगर (rc)
				वापस rc;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक audit_compare_gid(kgid_t gid,
			     काष्ठा audit_names *name,
			     काष्ठा audit_field *f,
			     काष्ठा audit_context *ctx)
अणु
	काष्ठा audit_names *n;
	पूर्णांक rc;
 
	अगर (name) अणु
		rc = audit_gid_comparator(gid, f->op, name->gid);
		अगर (rc)
			वापस rc;
	पूर्ण
 
	अगर (ctx) अणु
		list_क्रम_each_entry(n, &ctx->names_list, list) अणु
			rc = audit_gid_comparator(gid, f->op, n->gid);
			अगर (rc)
				वापस rc;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक audit_field_compare(काष्ठा task_काष्ठा *tsk,
			       स्थिर काष्ठा cred *cred,
			       काष्ठा audit_field *f,
			       काष्ठा audit_context *ctx,
			       काष्ठा audit_names *name)
अणु
	चयन (f->val) अणु
	/* process to file object comparisons */
	हाल AUDIT_COMPARE_UID_TO_OBJ_UID:
		वापस audit_compare_uid(cred->uid, name, f, ctx);
	हाल AUDIT_COMPARE_GID_TO_OBJ_GID:
		वापस audit_compare_gid(cred->gid, name, f, ctx);
	हाल AUDIT_COMPARE_EUID_TO_OBJ_UID:
		वापस audit_compare_uid(cred->euid, name, f, ctx);
	हाल AUDIT_COMPARE_EGID_TO_OBJ_GID:
		वापस audit_compare_gid(cred->egid, name, f, ctx);
	हाल AUDIT_COMPARE_AUID_TO_OBJ_UID:
		वापस audit_compare_uid(audit_get_loginuid(tsk), name, f, ctx);
	हाल AUDIT_COMPARE_SUID_TO_OBJ_UID:
		वापस audit_compare_uid(cred->suid, name, f, ctx);
	हाल AUDIT_COMPARE_SGID_TO_OBJ_GID:
		वापस audit_compare_gid(cred->sgid, name, f, ctx);
	हाल AUDIT_COMPARE_FSUID_TO_OBJ_UID:
		वापस audit_compare_uid(cred->fsuid, name, f, ctx);
	हाल AUDIT_COMPARE_FSGID_TO_OBJ_GID:
		वापस audit_compare_gid(cred->fsgid, name, f, ctx);
	/* uid comparisons */
	हाल AUDIT_COMPARE_UID_TO_AUID:
		वापस audit_uid_comparator(cred->uid, f->op,
					    audit_get_loginuid(tsk));
	हाल AUDIT_COMPARE_UID_TO_EUID:
		वापस audit_uid_comparator(cred->uid, f->op, cred->euid);
	हाल AUDIT_COMPARE_UID_TO_SUID:
		वापस audit_uid_comparator(cred->uid, f->op, cred->suid);
	हाल AUDIT_COMPARE_UID_TO_FSUID:
		वापस audit_uid_comparator(cred->uid, f->op, cred->fsuid);
	/* auid comparisons */
	हाल AUDIT_COMPARE_AUID_TO_EUID:
		वापस audit_uid_comparator(audit_get_loginuid(tsk), f->op,
					    cred->euid);
	हाल AUDIT_COMPARE_AUID_TO_SUID:
		वापस audit_uid_comparator(audit_get_loginuid(tsk), f->op,
					    cred->suid);
	हाल AUDIT_COMPARE_AUID_TO_FSUID:
		वापस audit_uid_comparator(audit_get_loginuid(tsk), f->op,
					    cred->fsuid);
	/* euid comparisons */
	हाल AUDIT_COMPARE_EUID_TO_SUID:
		वापस audit_uid_comparator(cred->euid, f->op, cred->suid);
	हाल AUDIT_COMPARE_EUID_TO_FSUID:
		वापस audit_uid_comparator(cred->euid, f->op, cred->fsuid);
	/* suid comparisons */
	हाल AUDIT_COMPARE_SUID_TO_FSUID:
		वापस audit_uid_comparator(cred->suid, f->op, cred->fsuid);
	/* gid comparisons */
	हाल AUDIT_COMPARE_GID_TO_EGID:
		वापस audit_gid_comparator(cred->gid, f->op, cred->egid);
	हाल AUDIT_COMPARE_GID_TO_SGID:
		वापस audit_gid_comparator(cred->gid, f->op, cred->sgid);
	हाल AUDIT_COMPARE_GID_TO_FSGID:
		वापस audit_gid_comparator(cred->gid, f->op, cred->fsgid);
	/* egid comparisons */
	हाल AUDIT_COMPARE_EGID_TO_SGID:
		वापस audit_gid_comparator(cred->egid, f->op, cred->sgid);
	हाल AUDIT_COMPARE_EGID_TO_FSGID:
		वापस audit_gid_comparator(cred->egid, f->op, cred->fsgid);
	/* sgid comparison */
	हाल AUDIT_COMPARE_SGID_TO_FSGID:
		वापस audit_gid_comparator(cred->sgid, f->op, cred->fsgid);
	शेष:
		WARN(1, "Missing AUDIT_COMPARE define.  Report as a bug\n");
		वापस 0;
	पूर्ण
	वापस 0;
पूर्ण

/* Determine अगर any context name data matches a rule's watch data */
/* Compare a task_काष्ठा with an audit_rule.  Return 1 on match, 0
 * otherwise.
 *
 * If task_creation is true, this is an explicit indication that we are
 * filtering a task rule at task creation समय.  This and tsk == current are
 * the only situations where tsk->cred may be accessed without an rcu पढ़ो lock.
 */
अटल पूर्णांक audit_filter_rules(काष्ठा task_काष्ठा *tsk,
			      काष्ठा audit_krule *rule,
			      काष्ठा audit_context *ctx,
			      काष्ठा audit_names *name,
			      क्रमागत audit_state *state,
			      bool task_creation)
अणु
	स्थिर काष्ठा cred *cred;
	पूर्णांक i, need_sid = 1;
	u32 sid;
	अचिन्हित पूर्णांक sessionid;

	cred = rcu_dereference_check(tsk->cred, tsk == current || task_creation);

	क्रम (i = 0; i < rule->field_count; i++) अणु
		काष्ठा audit_field *f = &rule->fields[i];
		काष्ठा audit_names *n;
		पूर्णांक result = 0;
		pid_t pid;

		चयन (f->type) अणु
		हाल AUDIT_PID:
			pid = task_tgid_nr(tsk);
			result = audit_comparator(pid, f->op, f->val);
			अवरोध;
		हाल AUDIT_PPID:
			अगर (ctx) अणु
				अगर (!ctx->ppid)
					ctx->ppid = task_ppid_nr(tsk);
				result = audit_comparator(ctx->ppid, f->op, f->val);
			पूर्ण
			अवरोध;
		हाल AUDIT_EXE:
			result = audit_exe_compare(tsk, rule->exe);
			अगर (f->op == Audit_not_equal)
				result = !result;
			अवरोध;
		हाल AUDIT_UID:
			result = audit_uid_comparator(cred->uid, f->op, f->uid);
			अवरोध;
		हाल AUDIT_EUID:
			result = audit_uid_comparator(cred->euid, f->op, f->uid);
			अवरोध;
		हाल AUDIT_SUID:
			result = audit_uid_comparator(cred->suid, f->op, f->uid);
			अवरोध;
		हाल AUDIT_FSUID:
			result = audit_uid_comparator(cred->fsuid, f->op, f->uid);
			अवरोध;
		हाल AUDIT_GID:
			result = audit_gid_comparator(cred->gid, f->op, f->gid);
			अगर (f->op == Audit_equal) अणु
				अगर (!result)
					result = groups_search(cred->group_info, f->gid);
			पूर्ण अन्यथा अगर (f->op == Audit_not_equal) अणु
				अगर (result)
					result = !groups_search(cred->group_info, f->gid);
			पूर्ण
			अवरोध;
		हाल AUDIT_EGID:
			result = audit_gid_comparator(cred->egid, f->op, f->gid);
			अगर (f->op == Audit_equal) अणु
				अगर (!result)
					result = groups_search(cred->group_info, f->gid);
			पूर्ण अन्यथा अगर (f->op == Audit_not_equal) अणु
				अगर (result)
					result = !groups_search(cred->group_info, f->gid);
			पूर्ण
			अवरोध;
		हाल AUDIT_SGID:
			result = audit_gid_comparator(cred->sgid, f->op, f->gid);
			अवरोध;
		हाल AUDIT_FSGID:
			result = audit_gid_comparator(cred->fsgid, f->op, f->gid);
			अवरोध;
		हाल AUDIT_SESSIONID:
			sessionid = audit_get_sessionid(tsk);
			result = audit_comparator(sessionid, f->op, f->val);
			अवरोध;
		हाल AUDIT_PERS:
			result = audit_comparator(tsk->personality, f->op, f->val);
			अवरोध;
		हाल AUDIT_ARCH:
			अगर (ctx)
				result = audit_comparator(ctx->arch, f->op, f->val);
			अवरोध;

		हाल AUDIT_EXIT:
			अगर (ctx && ctx->वापस_valid != AUDITSC_INVALID)
				result = audit_comparator(ctx->वापस_code, f->op, f->val);
			अवरोध;
		हाल AUDIT_SUCCESS:
			अगर (ctx && ctx->वापस_valid != AUDITSC_INVALID) अणु
				अगर (f->val)
					result = audit_comparator(ctx->वापस_valid, f->op, AUDITSC_SUCCESS);
				अन्यथा
					result = audit_comparator(ctx->वापस_valid, f->op, AUDITSC_FAILURE);
			पूर्ण
			अवरोध;
		हाल AUDIT_DEVMAJOR:
			अगर (name) अणु
				अगर (audit_comparator(MAJOR(name->dev), f->op, f->val) ||
				    audit_comparator(MAJOR(name->rdev), f->op, f->val))
					++result;
			पूर्ण अन्यथा अगर (ctx) अणु
				list_क्रम_each_entry(n, &ctx->names_list, list) अणु
					अगर (audit_comparator(MAJOR(n->dev), f->op, f->val) ||
					    audit_comparator(MAJOR(n->rdev), f->op, f->val)) अणु
						++result;
						अवरोध;
					पूर्ण
				पूर्ण
			पूर्ण
			अवरोध;
		हाल AUDIT_DEVMINOR:
			अगर (name) अणु
				अगर (audit_comparator(MINOR(name->dev), f->op, f->val) ||
				    audit_comparator(MINOR(name->rdev), f->op, f->val))
					++result;
			पूर्ण अन्यथा अगर (ctx) अणु
				list_क्रम_each_entry(n, &ctx->names_list, list) अणु
					अगर (audit_comparator(MINOR(n->dev), f->op, f->val) ||
					    audit_comparator(MINOR(n->rdev), f->op, f->val)) अणु
						++result;
						अवरोध;
					पूर्ण
				पूर्ण
			पूर्ण
			अवरोध;
		हाल AUDIT_INODE:
			अगर (name)
				result = audit_comparator(name->ino, f->op, f->val);
			अन्यथा अगर (ctx) अणु
				list_क्रम_each_entry(n, &ctx->names_list, list) अणु
					अगर (audit_comparator(n->ino, f->op, f->val)) अणु
						++result;
						अवरोध;
					पूर्ण
				पूर्ण
			पूर्ण
			अवरोध;
		हाल AUDIT_OBJ_UID:
			अगर (name) अणु
				result = audit_uid_comparator(name->uid, f->op, f->uid);
			पूर्ण अन्यथा अगर (ctx) अणु
				list_क्रम_each_entry(n, &ctx->names_list, list) अणु
					अगर (audit_uid_comparator(n->uid, f->op, f->uid)) अणु
						++result;
						अवरोध;
					पूर्ण
				पूर्ण
			पूर्ण
			अवरोध;
		हाल AUDIT_OBJ_GID:
			अगर (name) अणु
				result = audit_gid_comparator(name->gid, f->op, f->gid);
			पूर्ण अन्यथा अगर (ctx) अणु
				list_क्रम_each_entry(n, &ctx->names_list, list) अणु
					अगर (audit_gid_comparator(n->gid, f->op, f->gid)) अणु
						++result;
						अवरोध;
					पूर्ण
				पूर्ण
			पूर्ण
			अवरोध;
		हाल AUDIT_WATCH:
			अगर (name) अणु
				result = audit_watch_compare(rule->watch,
							     name->ino,
							     name->dev);
				अगर (f->op == Audit_not_equal)
					result = !result;
			पूर्ण
			अवरोध;
		हाल AUDIT_सूची:
			अगर (ctx) अणु
				result = match_tree_refs(ctx, rule->tree);
				अगर (f->op == Audit_not_equal)
					result = !result;
			पूर्ण
			अवरोध;
		हाल AUDIT_LOGINUID:
			result = audit_uid_comparator(audit_get_loginuid(tsk),
						      f->op, f->uid);
			अवरोध;
		हाल AUDIT_LOGINUID_SET:
			result = audit_comparator(audit_loginuid_set(tsk), f->op, f->val);
			अवरोध;
		हाल AUDIT_SADDR_FAM:
			अगर (ctx->sockaddr)
				result = audit_comparator(ctx->sockaddr->ss_family,
							  f->op, f->val);
			अवरोध;
		हाल AUDIT_SUBJ_USER:
		हाल AUDIT_SUBJ_ROLE:
		हाल AUDIT_SUBJ_TYPE:
		हाल AUDIT_SUBJ_SEN:
		हाल AUDIT_SUBJ_CLR:
			/* NOTE: this may वापस negative values indicating
			   a temporary error.  We simply treat this as a
			   match क्रम now to aव्योम losing inक्रमmation that
			   may be wanted.   An error message will also be
			   logged upon error */
			अगर (f->lsm_rule) अणु
				अगर (need_sid) अणु
					security_task_माला_लोecid_subj(tsk, &sid);
					need_sid = 0;
				पूर्ण
				result = security_audit_rule_match(sid, f->type,
								   f->op,
								   f->lsm_rule);
			पूर्ण
			अवरोध;
		हाल AUDIT_OBJ_USER:
		हाल AUDIT_OBJ_ROLE:
		हाल AUDIT_OBJ_TYPE:
		हाल AUDIT_OBJ_LEV_LOW:
		हाल AUDIT_OBJ_LEV_HIGH:
			/* The above note क्रम AUDIT_SUBJ_USER...AUDIT_SUBJ_CLR
			   also applies here */
			अगर (f->lsm_rule) अणु
				/* Find files that match */
				अगर (name) अणु
					result = security_audit_rule_match(
								name->osid,
								f->type,
								f->op,
								f->lsm_rule);
				पूर्ण अन्यथा अगर (ctx) अणु
					list_क्रम_each_entry(n, &ctx->names_list, list) अणु
						अगर (security_audit_rule_match(
								n->osid,
								f->type,
								f->op,
								f->lsm_rule)) अणु
							++result;
							अवरोध;
						पूर्ण
					पूर्ण
				पूर्ण
				/* Find ipc objects that match */
				अगर (!ctx || ctx->type != AUDIT_IPC)
					अवरोध;
				अगर (security_audit_rule_match(ctx->ipc.osid,
							      f->type, f->op,
							      f->lsm_rule))
					++result;
			पूर्ण
			अवरोध;
		हाल AUDIT_ARG0:
		हाल AUDIT_ARG1:
		हाल AUDIT_ARG2:
		हाल AUDIT_ARG3:
			अगर (ctx)
				result = audit_comparator(ctx->argv[f->type-AUDIT_ARG0], f->op, f->val);
			अवरोध;
		हाल AUDIT_FILTERKEY:
			/* ignore this field क्रम filtering */
			result = 1;
			अवरोध;
		हाल AUDIT_PERM:
			result = audit_match_perm(ctx, f->val);
			अगर (f->op == Audit_not_equal)
				result = !result;
			अवरोध;
		हाल AUDIT_खाताTYPE:
			result = audit_match_filetype(ctx, f->val);
			अगर (f->op == Audit_not_equal)
				result = !result;
			अवरोध;
		हाल AUDIT_FIELD_COMPARE:
			result = audit_field_compare(tsk, cred, f, ctx, name);
			अवरोध;
		पूर्ण
		अगर (!result)
			वापस 0;
	पूर्ण

	अगर (ctx) अणु
		अगर (rule->prio <= ctx->prio)
			वापस 0;
		अगर (rule->filterkey) अणु
			kमुक्त(ctx->filterkey);
			ctx->filterkey = kstrdup(rule->filterkey, GFP_ATOMIC);
		पूर्ण
		ctx->prio = rule->prio;
	पूर्ण
	चयन (rule->action) अणु
	हाल AUDIT_NEVER:
		*state = AUDIT_DISABLED;
		अवरोध;
	हाल AUDIT_ALWAYS:
		*state = AUDIT_RECORD_CONTEXT;
		अवरोध;
	पूर्ण
	वापस 1;
पूर्ण

/* At process creation समय, we can determine अगर प्रणाली-call auditing is
 * completely disabled क्रम this task.  Since we only have the task
 * काष्ठाure at this poपूर्णांक, we can only check uid and gid.
 */
अटल क्रमागत audit_state audit_filter_task(काष्ठा task_काष्ठा *tsk, अक्षर **key)
अणु
	काष्ठा audit_entry *e;
	क्रमागत audit_state   state;

	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(e, &audit_filter_list[AUDIT_FILTER_TASK], list) अणु
		अगर (audit_filter_rules(tsk, &e->rule, शून्य, शून्य,
				       &state, true)) अणु
			अगर (state == AUDIT_RECORD_CONTEXT)
				*key = kstrdup(e->rule.filterkey, GFP_ATOMIC);
			rcu_पढ़ो_unlock();
			वापस state;
		पूर्ण
	पूर्ण
	rcu_पढ़ो_unlock();
	वापस AUDIT_BUILD_CONTEXT;
पूर्ण

अटल पूर्णांक audit_in_mask(स्थिर काष्ठा audit_krule *rule, अचिन्हित दीर्घ val)
अणु
	पूर्णांक word, bit;

	अगर (val > 0xffffffff)
		वापस false;

	word = AUDIT_WORD(val);
	अगर (word >= AUDIT_BITMASK_SIZE)
		वापस false;

	bit = AUDIT_BIT(val);

	वापस rule->mask[word] & bit;
पूर्ण

/* At syscall निकास समय, this filter is called अगर the audit_state is
 * not low enough that auditing cannot take place, but is also not
 * high enough that we alपढ़ोy know we have to ग_लिखो an audit record
 * (i.e., the state is AUDIT_SETUP_CONTEXT or AUDIT_BUILD_CONTEXT).
 */
अटल व्योम audit_filter_syscall(काष्ठा task_काष्ठा *tsk,
				 काष्ठा audit_context *ctx)
अणु
	काष्ठा audit_entry *e;
	क्रमागत audit_state state;

	अगर (auditd_test_task(tsk))
		वापस;

	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(e, &audit_filter_list[AUDIT_FILTER_EXIT], list) अणु
		अगर (audit_in_mask(&e->rule, ctx->major) &&
		    audit_filter_rules(tsk, &e->rule, ctx, शून्य,
				       &state, false)) अणु
			rcu_पढ़ो_unlock();
			ctx->current_state = state;
			वापस;
		पूर्ण
	पूर्ण
	rcu_पढ़ो_unlock();
	वापस;
पूर्ण

/*
 * Given an audit_name check the inode hash table to see अगर they match.
 * Called holding the rcu पढ़ो lock to protect the use of audit_inode_hash
 */
अटल पूर्णांक audit_filter_inode_name(काष्ठा task_काष्ठा *tsk,
				   काष्ठा audit_names *n,
				   काष्ठा audit_context *ctx) अणु
	पूर्णांक h = audit_hash_ino((u32)n->ino);
	काष्ठा list_head *list = &audit_inode_hash[h];
	काष्ठा audit_entry *e;
	क्रमागत audit_state state;

	list_क्रम_each_entry_rcu(e, list, list) अणु
		अगर (audit_in_mask(&e->rule, ctx->major) &&
		    audit_filter_rules(tsk, &e->rule, ctx, n, &state, false)) अणु
			ctx->current_state = state;
			वापस 1;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

/* At syscall निकास समय, this filter is called अगर any audit_names have been
 * collected during syscall processing.  We only check rules in sublists at hash
 * buckets applicable to the inode numbers in audit_names.
 * Regarding audit_state, same rules apply as क्रम audit_filter_syscall().
 */
व्योम audit_filter_inodes(काष्ठा task_काष्ठा *tsk, काष्ठा audit_context *ctx)
अणु
	काष्ठा audit_names *n;

	अगर (auditd_test_task(tsk))
		वापस;

	rcu_पढ़ो_lock();

	list_क्रम_each_entry(n, &ctx->names_list, list) अणु
		अगर (audit_filter_inode_name(tsk, n, ctx))
			अवरोध;
	पूर्ण
	rcu_पढ़ो_unlock();
पूर्ण

अटल अंतरभूत व्योम audit_proctitle_मुक्त(काष्ठा audit_context *context)
अणु
	kमुक्त(context->proctitle.value);
	context->proctitle.value = शून्य;
	context->proctitle.len = 0;
पूर्ण

अटल अंतरभूत व्योम audit_मुक्त_module(काष्ठा audit_context *context)
अणु
	अगर (context->type == AUDIT_KERN_MODULE) अणु
		kमुक्त(context->module.name);
		context->module.name = शून्य;
	पूर्ण
पूर्ण
अटल अंतरभूत व्योम audit_मुक्त_names(काष्ठा audit_context *context)
अणु
	काष्ठा audit_names *n, *next;

	list_क्रम_each_entry_safe(n, next, &context->names_list, list) अणु
		list_del(&n->list);
		अगर (n->name)
			putname(n->name);
		अगर (n->should_मुक्त)
			kमुक्त(n);
	पूर्ण
	context->name_count = 0;
	path_put(&context->pwd);
	context->pwd.dentry = शून्य;
	context->pwd.mnt = शून्य;
पूर्ण

अटल अंतरभूत व्योम audit_मुक्त_aux(काष्ठा audit_context *context)
अणु
	काष्ठा audit_aux_data *aux;

	जबतक ((aux = context->aux)) अणु
		context->aux = aux->next;
		kमुक्त(aux);
	पूर्ण
	जबतक ((aux = context->aux_pids)) अणु
		context->aux_pids = aux->next;
		kमुक्त(aux);
	पूर्ण
पूर्ण

अटल अंतरभूत काष्ठा audit_context *audit_alloc_context(क्रमागत audit_state state)
अणु
	काष्ठा audit_context *context;

	context = kzalloc(माप(*context), GFP_KERNEL);
	अगर (!context)
		वापस शून्य;
	context->state = state;
	context->prio = state == AUDIT_RECORD_CONTEXT ? ~0ULL : 0;
	INIT_LIST_HEAD(&context->समाप्तed_trees);
	INIT_LIST_HEAD(&context->names_list);
	context->fds[0] = -1;
	context->वापस_valid = AUDITSC_INVALID;
	वापस context;
पूर्ण

/**
 * audit_alloc - allocate an audit context block क्रम a task
 * @tsk: task
 *
 * Filter on the task inक्रमmation and allocate a per-task audit context
 * अगर necessary.  Doing so turns on प्रणाली call auditing क्रम the
 * specअगरied task.  This is called from copy_process, so no lock is
 * needed.
 */
पूर्णांक audit_alloc(काष्ठा task_काष्ठा *tsk)
अणु
	काष्ठा audit_context *context;
	क्रमागत audit_state     state;
	अक्षर *key = शून्य;

	अगर (likely(!audit_ever_enabled))
		वापस 0; /* Return अगर not auditing. */

	state = audit_filter_task(tsk, &key);
	अगर (state == AUDIT_DISABLED) अणु
		clear_task_syscall_work(tsk, SYSCALL_AUDIT);
		वापस 0;
	पूर्ण

	अगर (!(context = audit_alloc_context(state))) अणु
		kमुक्त(key);
		audit_log_lost("out of memory in audit_alloc");
		वापस -ENOMEM;
	पूर्ण
	context->filterkey = key;

	audit_set_context(tsk, context);
	set_task_syscall_work(tsk, SYSCALL_AUDIT);
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम audit_मुक्त_context(काष्ठा audit_context *context)
अणु
	audit_मुक्त_module(context);
	audit_मुक्त_names(context);
	unroll_tree_refs(context, शून्य, 0);
	मुक्त_tree_refs(context);
	audit_मुक्त_aux(context);
	kमुक्त(context->filterkey);
	kमुक्त(context->sockaddr);
	audit_proctitle_मुक्त(context);
	kमुक्त(context);
पूर्ण

अटल पूर्णांक audit_log_pid_context(काष्ठा audit_context *context, pid_t pid,
				 kuid_t auid, kuid_t uid, अचिन्हित पूर्णांक sessionid,
				 u32 sid, अक्षर *comm)
अणु
	काष्ठा audit_buffer *ab;
	अक्षर *ctx = शून्य;
	u32 len;
	पूर्णांक rc = 0;

	ab = audit_log_start(context, GFP_KERNEL, AUDIT_OBJ_PID);
	अगर (!ab)
		वापस rc;

	audit_log_क्रमmat(ab, "opid=%d oauid=%d ouid=%d oses=%d", pid,
			 from_kuid(&init_user_ns, auid),
			 from_kuid(&init_user_ns, uid), sessionid);
	अगर (sid) अणु
		अगर (security_secid_to_secctx(sid, &ctx, &len)) अणु
			audit_log_क्रमmat(ab, " obj=(none)");
			rc = 1;
		पूर्ण अन्यथा अणु
			audit_log_क्रमmat(ab, " obj=%s", ctx);
			security_release_secctx(ctx, len);
		पूर्ण
	पूर्ण
	audit_log_क्रमmat(ab, " ocomm=");
	audit_log_untrustedstring(ab, comm);
	audit_log_end(ab);

	वापस rc;
पूर्ण

अटल व्योम audit_log_execve_info(काष्ठा audit_context *context,
				  काष्ठा audit_buffer **ab)
अणु
	दीर्घ len_max;
	दीर्घ len_rem;
	दीर्घ len_full;
	दीर्घ len_buf;
	दीर्घ len_abuf = 0;
	दीर्घ len_पंचांगp;
	bool require_data;
	bool encode;
	अचिन्हित पूर्णांक iter;
	अचिन्हित पूर्णांक arg;
	अक्षर *buf_head;
	अक्षर *buf;
	स्थिर अक्षर __user *p = (स्थिर अक्षर __user *)current->mm->arg_start;

	/* NOTE: this buffer needs to be large enough to hold all the non-arg
	 *       data we put in the audit record क्रम this argument (see the
	 *       code below) ... at this poपूर्णांक in समय 96 is plenty */
	अक्षर abuf[96];

	/* NOTE: we set MAX_EXECVE_AUDIT_LEN to a rather arbitrary limit, the
	 *       current value of 7500 is not as important as the fact that it
	 *       is less than 8k, a setting of 7500 gives us plenty of wiggle
	 *       room अगर we go over a little bit in the logging below */
	WARN_ON_ONCE(MAX_EXECVE_AUDIT_LEN > 7500);
	len_max = MAX_EXECVE_AUDIT_LEN;

	/* scratch buffer to hold the userspace args */
	buf_head = kदो_स्मृति(MAX_EXECVE_AUDIT_LEN + 1, GFP_KERNEL);
	अगर (!buf_head) अणु
		audit_panic("out of memory for argv string");
		वापस;
	पूर्ण
	buf = buf_head;

	audit_log_क्रमmat(*ab, "argc=%d", context->execve.argc);

	len_rem = len_max;
	len_buf = 0;
	len_full = 0;
	require_data = true;
	encode = false;
	iter = 0;
	arg = 0;
	करो अणु
		/* NOTE: we करोn't ever want to trust this value क्रम anything
		 *       serious, but the audit record क्रमmat insists we
		 *       provide an argument length क्रम really दीर्घ arguments,
		 *       e.g. > MAX_EXECVE_AUDIT_LEN, so we have no choice but
		 *       to use म_नकलन_from_user() to obtain this value क्रम
		 *       recording in the log, although we करोn't use it
		 *       anywhere here to aव्योम a द्विगुन-fetch problem */
		अगर (len_full == 0)
			len_full = strnlen_user(p, MAX_ARG_STRLEN) - 1;

		/* पढ़ो more data from userspace */
		अगर (require_data) अणु
			/* can we make more room in the buffer? */
			अगर (buf != buf_head) अणु
				स_हटाओ(buf_head, buf, len_buf);
				buf = buf_head;
			पूर्ण

			/* fetch as much as we can of the argument */
			len_पंचांगp = म_नकलन_from_user(&buf_head[len_buf], p,
						    len_max - len_buf);
			अगर (len_पंचांगp == -EFAULT) अणु
				/* unable to copy from userspace */
				send_sig(SIGKILL, current, 0);
				जाओ out;
			पूर्ण अन्यथा अगर (len_पंचांगp == (len_max - len_buf)) अणु
				/* buffer is not large enough */
				require_data = true;
				/* NOTE: अगर we are going to span multiple
				 *       buffers क्रमce the encoding so we stand
				 *       a chance at a sane len_full value and
				 *       consistent record encoding */
				encode = true;
				len_full = len_full * 2;
				p += len_पंचांगp;
			पूर्ण अन्यथा अणु
				require_data = false;
				अगर (!encode)
					encode = audit_string_contains_control(
								buf, len_पंचांगp);
				/* try to use a trusted value क्रम len_full */
				अगर (len_full < len_max)
					len_full = (encode ?
						    len_पंचांगp * 2 : len_पंचांगp);
				p += len_पंचांगp + 1;
			पूर्ण
			len_buf += len_पंचांगp;
			buf_head[len_buf] = '\0';

			/* length of the buffer in the audit record? */
			len_abuf = (encode ? len_buf * 2 : len_buf + 2);
		पूर्ण

		/* ग_लिखो as much as we can to the audit log */
		अगर (len_buf >= 0) अणु
			/* NOTE: some magic numbers here - basically अगर we
			 *       can't fit a reasonable amount of data पूर्णांकo the
			 *       existing audit buffer, flush it and start with
			 *       a new buffer */
			अगर ((माप(abuf) + 8) > len_rem) अणु
				len_rem = len_max;
				audit_log_end(*ab);
				*ab = audit_log_start(context,
						      GFP_KERNEL, AUDIT_EXECVE);
				अगर (!*ab)
					जाओ out;
			पूर्ण

			/* create the non-arg portion of the arg record */
			len_पंचांगp = 0;
			अगर (require_data || (iter > 0) ||
			    ((len_abuf + माप(abuf)) > len_rem)) अणु
				अगर (iter == 0) अणु
					len_पंचांगp += snम_लिखो(&abuf[len_पंचांगp],
							माप(abuf) - len_पंचांगp,
							" a%d_len=%lu",
							arg, len_full);
				पूर्ण
				len_पंचांगp += snम_लिखो(&abuf[len_पंचांगp],
						    माप(abuf) - len_पंचांगp,
						    " a%d[%d]=", arg, iter++);
			पूर्ण अन्यथा
				len_पंचांगp += snम_लिखो(&abuf[len_पंचांगp],
						    माप(abuf) - len_पंचांगp,
						    " a%d=", arg);
			WARN_ON(len_पंचांगp >= माप(abuf));
			abuf[माप(abuf) - 1] = '\0';

			/* log the arg in the audit record */
			audit_log_क्रमmat(*ab, "%s", abuf);
			len_rem -= len_पंचांगp;
			len_पंचांगp = len_buf;
			अगर (encode) अणु
				अगर (len_abuf > len_rem)
					len_पंचांगp = len_rem / 2; /* encoding */
				audit_log_n_hex(*ab, buf, len_पंचांगp);
				len_rem -= len_पंचांगp * 2;
				len_abuf -= len_पंचांगp * 2;
			पूर्ण अन्यथा अणु
				अगर (len_abuf > len_rem)
					len_पंचांगp = len_rem - 2; /* quotes */
				audit_log_n_string(*ab, buf, len_पंचांगp);
				len_rem -= len_पंचांगp + 2;
				/* करोn't subtract the "2" because we still need
				 * to add quotes to the reमुख्यing string */
				len_abuf -= len_पंचांगp;
			पूर्ण
			len_buf -= len_पंचांगp;
			buf += len_पंचांगp;
		पूर्ण

		/* पढ़ोy to move to the next argument? */
		अगर ((len_buf == 0) && !require_data) अणु
			arg++;
			iter = 0;
			len_full = 0;
			require_data = true;
			encode = false;
		पूर्ण
	पूर्ण जबतक (arg < context->execve.argc);

	/* NOTE: the caller handles the final audit_log_end() call */

out:
	kमुक्त(buf_head);
पूर्ण

अटल व्योम audit_log_cap(काष्ठा audit_buffer *ab, अक्षर *prefix,
			  kernel_cap_t *cap)
अणु
	पूर्णांक i;

	अगर (cap_isclear(*cap)) अणु
		audit_log_क्रमmat(ab, " %s=0", prefix);
		वापस;
	पूर्ण
	audit_log_क्रमmat(ab, " %s=", prefix);
	CAP_FOR_EACH_U32(i)
		audit_log_क्रमmat(ab, "%08x", cap->cap[CAP_LAST_U32 - i]);
पूर्ण

अटल व्योम audit_log_fcaps(काष्ठा audit_buffer *ab, काष्ठा audit_names *name)
अणु
	अगर (name->fcap_ver == -1) अणु
		audit_log_क्रमmat(ab, " cap_fe=? cap_fver=? cap_fp=? cap_fi=?");
		वापस;
	पूर्ण
	audit_log_cap(ab, "cap_fp", &name->fcap.permitted);
	audit_log_cap(ab, "cap_fi", &name->fcap.inheritable);
	audit_log_क्रमmat(ab, " cap_fe=%d cap_fver=%x cap_frootid=%d",
			 name->fcap.fE, name->fcap_ver,
			 from_kuid(&init_user_ns, name->fcap.rootid));
पूर्ण

अटल व्योम show_special(काष्ठा audit_context *context, पूर्णांक *call_panic)
अणु
	काष्ठा audit_buffer *ab;
	पूर्णांक i;

	ab = audit_log_start(context, GFP_KERNEL, context->type);
	अगर (!ab)
		वापस;

	चयन (context->type) अणु
	हाल AUDIT_SOCKETCALL: अणु
		पूर्णांक nargs = context->socketcall.nargs;
		audit_log_क्रमmat(ab, "nargs=%d", nargs);
		क्रम (i = 0; i < nargs; i++)
			audit_log_क्रमmat(ab, " a%d=%lx", i,
				context->socketcall.args[i]);
		अवरोध; पूर्ण
	हाल AUDIT_IPC: अणु
		u32 osid = context->ipc.osid;

		audit_log_क्रमmat(ab, "ouid=%u ogid=%u mode=%#ho",
				 from_kuid(&init_user_ns, context->ipc.uid),
				 from_kgid(&init_user_ns, context->ipc.gid),
				 context->ipc.mode);
		अगर (osid) अणु
			अक्षर *ctx = शून्य;
			u32 len;
			अगर (security_secid_to_secctx(osid, &ctx, &len)) अणु
				audit_log_क्रमmat(ab, " osid=%u", osid);
				*call_panic = 1;
			पूर्ण अन्यथा अणु
				audit_log_क्रमmat(ab, " obj=%s", ctx);
				security_release_secctx(ctx, len);
			पूर्ण
		पूर्ण
		अगर (context->ipc.has_perm) अणु
			audit_log_end(ab);
			ab = audit_log_start(context, GFP_KERNEL,
					     AUDIT_IPC_SET_PERM);
			अगर (unlikely(!ab))
				वापस;
			audit_log_क्रमmat(ab,
				"qbytes=%lx ouid=%u ogid=%u mode=%#ho",
				context->ipc.qbytes,
				context->ipc.perm_uid,
				context->ipc.perm_gid,
				context->ipc.perm_mode);
		पूर्ण
		अवरोध; पूर्ण
	हाल AUDIT_MQ_OPEN:
		audit_log_क्रमmat(ab,
			"oflag=0x%x mode=%#ho mq_flags=0x%lx mq_maxmsg=%ld "
			"mq_msgsize=%ld mq_curmsgs=%ld",
			context->mq_खोलो.oflag, context->mq_खोलो.mode,
			context->mq_खोलो.attr.mq_flags,
			context->mq_खोलो.attr.mq_maxmsg,
			context->mq_खोलो.attr.mq_msgsize,
			context->mq_खोलो.attr.mq_curmsgs);
		अवरोध;
	हाल AUDIT_MQ_SENDRECV:
		audit_log_क्रमmat(ab,
			"mqdes=%d msg_len=%zd msg_prio=%u "
			"abs_timeout_sec=%lld abs_timeout_nsec=%ld",
			context->mq_sendrecv.mqdes,
			context->mq_sendrecv.msg_len,
			context->mq_sendrecv.msg_prio,
			(दीर्घ दीर्घ) context->mq_sendrecv.असल_समयout.tv_sec,
			context->mq_sendrecv.असल_समयout.tv_nsec);
		अवरोध;
	हाल AUDIT_MQ_NOTIFY:
		audit_log_क्रमmat(ab, "mqdes=%d sigev_signo=%d",
				context->mq_notअगरy.mqdes,
				context->mq_notअगरy.sigev_signo);
		अवरोध;
	हाल AUDIT_MQ_GETSETATTR: अणु
		काष्ठा mq_attr *attr = &context->mq_माला_लोetattr.mqstat;
		audit_log_क्रमmat(ab,
			"mqdes=%d mq_flags=0x%lx mq_maxmsg=%ld mq_msgsize=%ld "
			"mq_curmsgs=%ld ",
			context->mq_माला_लोetattr.mqdes,
			attr->mq_flags, attr->mq_maxmsg,
			attr->mq_msgsize, attr->mq_curmsgs);
		अवरोध; पूर्ण
	हाल AUDIT_CAPSET:
		audit_log_क्रमmat(ab, "pid=%d", context->capset.pid);
		audit_log_cap(ab, "cap_pi", &context->capset.cap.inheritable);
		audit_log_cap(ab, "cap_pp", &context->capset.cap.permitted);
		audit_log_cap(ab, "cap_pe", &context->capset.cap.effective);
		audit_log_cap(ab, "cap_pa", &context->capset.cap.ambient);
		अवरोध;
	हाल AUDIT_MMAP:
		audit_log_क्रमmat(ab, "fd=%d flags=0x%x", context->mmap.fd,
				 context->mmap.flags);
		अवरोध;
	हाल AUDIT_EXECVE:
		audit_log_execve_info(context, &ab);
		अवरोध;
	हाल AUDIT_KERN_MODULE:
		audit_log_क्रमmat(ab, "name=");
		अगर (context->module.name) अणु
			audit_log_untrustedstring(ab, context->module.name);
		पूर्ण अन्यथा
			audit_log_क्रमmat(ab, "(null)");

		अवरोध;
	पूर्ण
	audit_log_end(ab);
पूर्ण

अटल अंतरभूत पूर्णांक audit_proctitle_rtrim(अक्षर *proctitle, पूर्णांक len)
अणु
	अक्षर *end = proctitle + len - 1;
	जबतक (end > proctitle && !है_छाप(*end))
		end--;

	/* catch the हाल where proctitle is only 1 non-prपूर्णांक अक्षरacter */
	len = end - proctitle + 1;
	len -= है_छाप(proctitle[len-1]) == 0;
	वापस len;
पूर्ण

/*
 * audit_log_name - produce AUDIT_PATH record from काष्ठा audit_names
 * @context: audit_context क्रम the task
 * @n: audit_names काष्ठाure with reportable details
 * @path: optional path to report instead of audit_names->name
 * @record_num: record number to report when handling a list of names
 * @call_panic: optional poपूर्णांकer to पूर्णांक that will be updated अगर secid fails
 */
अटल व्योम audit_log_name(काष्ठा audit_context *context, काष्ठा audit_names *n,
		    स्थिर काष्ठा path *path, पूर्णांक record_num, पूर्णांक *call_panic)
अणु
	काष्ठा audit_buffer *ab;

	ab = audit_log_start(context, GFP_KERNEL, AUDIT_PATH);
	अगर (!ab)
		वापस;

	audit_log_क्रमmat(ab, "item=%d", record_num);

	अगर (path)
		audit_log_d_path(ab, " name=", path);
	अन्यथा अगर (n->name) अणु
		चयन (n->name_len) अणु
		हाल AUDIT_NAME_FULL:
			/* log the full path */
			audit_log_क्रमmat(ab, " name=");
			audit_log_untrustedstring(ab, n->name->name);
			अवरोध;
		हाल 0:
			/* name was specअगरied as a relative path and the
			 * directory component is the cwd
			 */
			अगर (context->pwd.dentry && context->pwd.mnt)
				audit_log_d_path(ab, " name=", &context->pwd);
			अन्यथा
				audit_log_क्रमmat(ab, " name=(null)");
			अवरोध;
		शेष:
			/* log the name's directory component */
			audit_log_क्रमmat(ab, " name=");
			audit_log_n_untrustedstring(ab, n->name->name,
						    n->name_len);
		पूर्ण
	पूर्ण अन्यथा
		audit_log_क्रमmat(ab, " name=(null)");

	अगर (n->ino != AUDIT_INO_UNSET)
		audit_log_क्रमmat(ab, " inode=%lu dev=%02x:%02x mode=%#ho ouid=%u ogid=%u rdev=%02x:%02x",
				 n->ino,
				 MAJOR(n->dev),
				 MINOR(n->dev),
				 n->mode,
				 from_kuid(&init_user_ns, n->uid),
				 from_kgid(&init_user_ns, n->gid),
				 MAJOR(n->rdev),
				 MINOR(n->rdev));
	अगर (n->osid != 0) अणु
		अक्षर *ctx = शून्य;
		u32 len;

		अगर (security_secid_to_secctx(
			n->osid, &ctx, &len)) अणु
			audit_log_क्रमmat(ab, " osid=%u", n->osid);
			अगर (call_panic)
				*call_panic = 2;
		पूर्ण अन्यथा अणु
			audit_log_क्रमmat(ab, " obj=%s", ctx);
			security_release_secctx(ctx, len);
		पूर्ण
	पूर्ण

	/* log the audit_names record type */
	चयन (n->type) अणु
	हाल AUDIT_TYPE_NORMAL:
		audit_log_क्रमmat(ab, " nametype=NORMAL");
		अवरोध;
	हाल AUDIT_TYPE_PARENT:
		audit_log_क्रमmat(ab, " nametype=PARENT");
		अवरोध;
	हाल AUDIT_TYPE_CHILD_DELETE:
		audit_log_क्रमmat(ab, " nametype=DELETE");
		अवरोध;
	हाल AUDIT_TYPE_CHILD_CREATE:
		audit_log_क्रमmat(ab, " nametype=CREATE");
		अवरोध;
	शेष:
		audit_log_क्रमmat(ab, " nametype=UNKNOWN");
		अवरोध;
	पूर्ण

	audit_log_fcaps(ab, n);
	audit_log_end(ab);
पूर्ण

अटल व्योम audit_log_proctitle(व्योम)
अणु
	पूर्णांक res;
	अक्षर *buf;
	अक्षर *msg = "(null)";
	पूर्णांक len = म_माप(msg);
	काष्ठा audit_context *context = audit_context();
	काष्ठा audit_buffer *ab;

	ab = audit_log_start(context, GFP_KERNEL, AUDIT_PROCTITLE);
	अगर (!ab)
		वापस;	/* audit_panic or being filtered */

	audit_log_क्रमmat(ab, "proctitle=");

	/* Not  cached */
	अगर (!context->proctitle.value) अणु
		buf = kदो_स्मृति(MAX_PROCTITLE_AUDIT_LEN, GFP_KERNEL);
		अगर (!buf)
			जाओ out;
		/* Historically called this from procfs naming */
		res = get_cmdline(current, buf, MAX_PROCTITLE_AUDIT_LEN);
		अगर (res == 0) अणु
			kमुक्त(buf);
			जाओ out;
		पूर्ण
		res = audit_proctitle_rtrim(buf, res);
		अगर (res == 0) अणु
			kमुक्त(buf);
			जाओ out;
		पूर्ण
		context->proctitle.value = buf;
		context->proctitle.len = res;
	पूर्ण
	msg = context->proctitle.value;
	len = context->proctitle.len;
out:
	audit_log_n_untrustedstring(ab, msg, len);
	audit_log_end(ab);
पूर्ण

अटल व्योम audit_log_निकास(व्योम)
अणु
	पूर्णांक i, call_panic = 0;
	काष्ठा audit_context *context = audit_context();
	काष्ठा audit_buffer *ab;
	काष्ठा audit_aux_data *aux;
	काष्ठा audit_names *n;

	context->personality = current->personality;

	ab = audit_log_start(context, GFP_KERNEL, AUDIT_SYSCALL);
	अगर (!ab)
		वापस;		/* audit_panic has been called */
	audit_log_क्रमmat(ab, "arch=%x syscall=%d",
			 context->arch, context->major);
	अगर (context->personality != PER_LINUX)
		audit_log_क्रमmat(ab, " per=%lx", context->personality);
	अगर (context->वापस_valid != AUDITSC_INVALID)
		audit_log_क्रमmat(ab, " success=%s exit=%ld",
				 (context->वापस_valid==AUDITSC_SUCCESS)?"yes":"no",
				 context->वापस_code);

	audit_log_क्रमmat(ab,
			 " a0=%lx a1=%lx a2=%lx a3=%lx items=%d",
			 context->argv[0],
			 context->argv[1],
			 context->argv[2],
			 context->argv[3],
			 context->name_count);

	audit_log_task_info(ab);
	audit_log_key(ab, context->filterkey);
	audit_log_end(ab);

	क्रम (aux = context->aux; aux; aux = aux->next) अणु

		ab = audit_log_start(context, GFP_KERNEL, aux->type);
		अगर (!ab)
			जारी; /* audit_panic has been called */

		चयन (aux->type) अणु

		हाल AUDIT_BPRM_FCAPS: अणु
			काष्ठा audit_aux_data_bprm_fcaps *axs = (व्योम *)aux;
			audit_log_क्रमmat(ab, "fver=%x", axs->fcap_ver);
			audit_log_cap(ab, "fp", &axs->fcap.permitted);
			audit_log_cap(ab, "fi", &axs->fcap.inheritable);
			audit_log_क्रमmat(ab, " fe=%d", axs->fcap.fE);
			audit_log_cap(ab, "old_pp", &axs->old_pcap.permitted);
			audit_log_cap(ab, "old_pi", &axs->old_pcap.inheritable);
			audit_log_cap(ab, "old_pe", &axs->old_pcap.effective);
			audit_log_cap(ab, "old_pa", &axs->old_pcap.ambient);
			audit_log_cap(ab, "pp", &axs->new_pcap.permitted);
			audit_log_cap(ab, "pi", &axs->new_pcap.inheritable);
			audit_log_cap(ab, "pe", &axs->new_pcap.effective);
			audit_log_cap(ab, "pa", &axs->new_pcap.ambient);
			audit_log_क्रमmat(ab, " frootid=%d",
					 from_kuid(&init_user_ns,
						   axs->fcap.rootid));
			अवरोध; पूर्ण

		पूर्ण
		audit_log_end(ab);
	पूर्ण

	अगर (context->type)
		show_special(context, &call_panic);

	अगर (context->fds[0] >= 0) अणु
		ab = audit_log_start(context, GFP_KERNEL, AUDIT_FD_PAIR);
		अगर (ab) अणु
			audit_log_क्रमmat(ab, "fd0=%d fd1=%d",
					context->fds[0], context->fds[1]);
			audit_log_end(ab);
		पूर्ण
	पूर्ण

	अगर (context->sockaddr_len) अणु
		ab = audit_log_start(context, GFP_KERNEL, AUDIT_SOCKADDR);
		अगर (ab) अणु
			audit_log_क्रमmat(ab, "saddr=");
			audit_log_n_hex(ab, (व्योम *)context->sockaddr,
					context->sockaddr_len);
			audit_log_end(ab);
		पूर्ण
	पूर्ण

	क्रम (aux = context->aux_pids; aux; aux = aux->next) अणु
		काष्ठा audit_aux_data_pids *axs = (व्योम *)aux;

		क्रम (i = 0; i < axs->pid_count; i++)
			अगर (audit_log_pid_context(context, axs->target_pid[i],
						  axs->target_auid[i],
						  axs->target_uid[i],
						  axs->target_sessionid[i],
						  axs->target_sid[i],
						  axs->target_comm[i]))
				call_panic = 1;
	पूर्ण

	अगर (context->target_pid &&
	    audit_log_pid_context(context, context->target_pid,
				  context->target_auid, context->target_uid,
				  context->target_sessionid,
				  context->target_sid, context->target_comm))
			call_panic = 1;

	अगर (context->pwd.dentry && context->pwd.mnt) अणु
		ab = audit_log_start(context, GFP_KERNEL, AUDIT_CWD);
		अगर (ab) अणु
			audit_log_d_path(ab, "cwd=", &context->pwd);
			audit_log_end(ab);
		पूर्ण
	पूर्ण

	i = 0;
	list_क्रम_each_entry(n, &context->names_list, list) अणु
		अगर (n->hidden)
			जारी;
		audit_log_name(context, n, शून्य, i++, &call_panic);
	पूर्ण

	audit_log_proctitle();

	/* Send end of event record to help user space know we are finished */
	ab = audit_log_start(context, GFP_KERNEL, AUDIT_EOE);
	अगर (ab)
		audit_log_end(ab);
	अगर (call_panic)
		audit_panic("error converting sid to string");
पूर्ण

/**
 * __audit_मुक्त - मुक्त a per-task audit context
 * @tsk: task whose audit context block to मुक्त
 *
 * Called from copy_process and करो_निकास
 */
व्योम __audit_मुक्त(काष्ठा task_काष्ठा *tsk)
अणु
	काष्ठा audit_context *context = tsk->audit_context;

	अगर (!context)
		वापस;

	अगर (!list_empty(&context->समाप्तed_trees))
		audit_समाप्त_trees(context);

	/* We are called either by करो_निकास() or the विभाजन() error handling code;
	 * in the क्रमmer हाल tsk == current and in the latter tsk is a
	 * अक्रमom task_काष्ठा that करोesn't doesn't have any meaningful data we
	 * need to log via audit_log_निकास().
	 */
	अगर (tsk == current && !context->dummy && context->in_syscall) अणु
		context->वापस_valid = AUDITSC_INVALID;
		context->वापस_code = 0;

		audit_filter_syscall(tsk, context);
		audit_filter_inodes(tsk, context);
		अगर (context->current_state == AUDIT_RECORD_CONTEXT)
			audit_log_निकास();
	पूर्ण

	audit_set_context(tsk, शून्य);
	audit_मुक्त_context(context);
पूर्ण

/**
 * __audit_syscall_entry - fill in an audit record at syscall entry
 * @major: major syscall type (function)
 * @a1: additional syscall रेजिस्टर 1
 * @a2: additional syscall रेजिस्टर 2
 * @a3: additional syscall रेजिस्टर 3
 * @a4: additional syscall रेजिस्टर 4
 *
 * Fill in audit context at syscall entry.  This only happens अगर the
 * audit context was created when the task was created and the state or
 * filters demand the audit context be built.  If the state from the
 * per-task filter or from the per-syscall filter is AUDIT_RECORD_CONTEXT,
 * then the record will be written at syscall निकास समय (otherwise, it
 * will only be written अगर another part of the kernel requests that it
 * be written).
 */
व्योम __audit_syscall_entry(पूर्णांक major, अचिन्हित दीर्घ a1, अचिन्हित दीर्घ a2,
			   अचिन्हित दीर्घ a3, अचिन्हित दीर्घ a4)
अणु
	काष्ठा audit_context *context = audit_context();
	क्रमागत audit_state     state;

	अगर (!audit_enabled || !context)
		वापस;

	BUG_ON(context->in_syscall || context->name_count);

	state = context->state;
	अगर (state == AUDIT_DISABLED)
		वापस;

	context->dummy = !audit_n_rules;
	अगर (!context->dummy && state == AUDIT_BUILD_CONTEXT) अणु
		context->prio = 0;
		अगर (auditd_test_task(current))
			वापस;
	पूर्ण

	context->arch	    = syscall_get_arch(current);
	context->major      = major;
	context->argv[0]    = a1;
	context->argv[1]    = a2;
	context->argv[2]    = a3;
	context->argv[3]    = a4;
	context->serial     = 0;
	context->in_syscall = 1;
	context->current_state  = state;
	context->ppid       = 0;
	kसमय_get_coarse_real_ts64(&context->स_समय);
पूर्ण

/**
 * __audit_syscall_निकास - deallocate audit context after a प्रणाली call
 * @success: success value of the syscall
 * @वापस_code: वापस value of the syscall
 *
 * Tear करोwn after प्रणाली call.  If the audit context has been marked as
 * auditable (either because of the AUDIT_RECORD_CONTEXT state from
 * filtering, or because some other part of the kernel wrote an audit
 * message), then ग_लिखो out the syscall inक्रमmation.  In call हालs,
 * मुक्त the names stored from getname().
 */
व्योम __audit_syscall_निकास(पूर्णांक success, दीर्घ वापस_code)
अणु
	काष्ठा audit_context *context;

	context = audit_context();
	अगर (!context)
		वापस;

	अगर (!list_empty(&context->समाप्तed_trees))
		audit_समाप्त_trees(context);

	अगर (!context->dummy && context->in_syscall) अणु
		अगर (success)
			context->वापस_valid = AUDITSC_SUCCESS;
		अन्यथा
			context->वापस_valid = AUDITSC_FAILURE;

		/*
		 * we need to fix up the वापस code in the audit logs अगर the
		 * actual वापस codes are later going to be fixed up by the
		 * arch specअगरic संकेत handlers
		 *
		 * This is actually a test क्रम:
		 * (rc == ERESTARTSYS ) || (rc == ERESTARTNOINTR) ||
		 * (rc == ERESTARTNOHAND) || (rc == ERESTART_RESTARTBLOCK)
		 *
		 * but is faster than a bunch of ||
		 */
		अगर (unlikely(वापस_code <= -ERESTARTSYS) &&
		    (वापस_code >= -ERESTART_RESTARTBLOCK) &&
		    (वापस_code != -ENOIOCTLCMD))
			context->वापस_code = -EINTR;
		अन्यथा
			context->वापस_code  = वापस_code;

		audit_filter_syscall(current, context);
		audit_filter_inodes(current, context);
		अगर (context->current_state == AUDIT_RECORD_CONTEXT)
			audit_log_निकास();
	पूर्ण

	context->in_syscall = 0;
	context->prio = context->state == AUDIT_RECORD_CONTEXT ? ~0ULL : 0;

	audit_मुक्त_module(context);
	audit_मुक्त_names(context);
	unroll_tree_refs(context, शून्य, 0);
	audit_मुक्त_aux(context);
	context->aux = शून्य;
	context->aux_pids = शून्य;
	context->target_pid = 0;
	context->target_sid = 0;
	context->sockaddr_len = 0;
	context->type = 0;
	context->fds[0] = -1;
	अगर (context->state != AUDIT_RECORD_CONTEXT) अणु
		kमुक्त(context->filterkey);
		context->filterkey = शून्य;
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम handle_one(स्थिर काष्ठा inode *inode)
अणु
	काष्ठा audit_context *context;
	काष्ठा audit_tree_refs *p;
	काष्ठा audit_chunk *chunk;
	पूर्णांक count;
	अगर (likely(!inode->i_fsnotअगरy_marks))
		वापस;
	context = audit_context();
	p = context->trees;
	count = context->tree_count;
	rcu_पढ़ो_lock();
	chunk = audit_tree_lookup(inode);
	rcu_पढ़ो_unlock();
	अगर (!chunk)
		वापस;
	अगर (likely(put_tree_ref(context, chunk)))
		वापस;
	अगर (unlikely(!grow_tree_refs(context))) अणु
		pr_warn("out of memory, audit has lost a tree reference\n");
		audit_set_auditable(context);
		audit_put_chunk(chunk);
		unroll_tree_refs(context, p, count);
		वापस;
	पूर्ण
	put_tree_ref(context, chunk);
पूर्ण

अटल व्योम handle_path(स्थिर काष्ठा dentry *dentry)
अणु
	काष्ठा audit_context *context;
	काष्ठा audit_tree_refs *p;
	स्थिर काष्ठा dentry *d, *parent;
	काष्ठा audit_chunk *drop;
	अचिन्हित दीर्घ seq;
	पूर्णांक count;

	context = audit_context();
	p = context->trees;
	count = context->tree_count;
retry:
	drop = शून्य;
	d = dentry;
	rcu_पढ़ो_lock();
	seq = पढ़ो_seqbegin(&नाम_lock);
	क्रम(;;) अणु
		काष्ठा inode *inode = d_backing_inode(d);
		अगर (inode && unlikely(inode->i_fsnotअगरy_marks)) अणु
			काष्ठा audit_chunk *chunk;
			chunk = audit_tree_lookup(inode);
			अगर (chunk) अणु
				अगर (unlikely(!put_tree_ref(context, chunk))) अणु
					drop = chunk;
					अवरोध;
				पूर्ण
			पूर्ण
		पूर्ण
		parent = d->d_parent;
		अगर (parent == d)
			अवरोध;
		d = parent;
	पूर्ण
	अगर (unlikely(पढ़ो_seqretry(&नाम_lock, seq) || drop)) अणु  /* in this order */
		rcu_पढ़ो_unlock();
		अगर (!drop) अणु
			/* just a race with नाम */
			unroll_tree_refs(context, p, count);
			जाओ retry;
		पूर्ण
		audit_put_chunk(drop);
		अगर (grow_tree_refs(context)) अणु
			/* OK, got more space */
			unroll_tree_refs(context, p, count);
			जाओ retry;
		पूर्ण
		/* too bad */
		pr_warn("out of memory, audit has lost a tree reference\n");
		unroll_tree_refs(context, p, count);
		audit_set_auditable(context);
		वापस;
	पूर्ण
	rcu_पढ़ो_unlock();
पूर्ण

अटल काष्ठा audit_names *audit_alloc_name(काष्ठा audit_context *context,
						अचिन्हित अक्षर type)
अणु
	काष्ठा audit_names *aname;

	अगर (context->name_count < AUDIT_NAMES) अणु
		aname = &context->pपुनः_स्मृतिated_names[context->name_count];
		स_रखो(aname, 0, माप(*aname));
	पूर्ण अन्यथा अणु
		aname = kzalloc(माप(*aname), GFP_NOFS);
		अगर (!aname)
			वापस शून्य;
		aname->should_मुक्त = true;
	पूर्ण

	aname->ino = AUDIT_INO_UNSET;
	aname->type = type;
	list_add_tail(&aname->list, &context->names_list);

	context->name_count++;
	अगर (!context->pwd.dentry)
		get_fs_pwd(current->fs, &context->pwd);
	वापस aname;
पूर्ण

/**
 * __audit_reusename - fill out filename with info from existing entry
 * @uptr: userland ptr to pathname
 *
 * Search the audit_names list क्रम the current audit context. If there is an
 * existing entry with a matching "uptr" then वापस the filename
 * associated with that audit_name. If not, वापस शून्य.
 */
काष्ठा filename *
__audit_reusename(स्थिर __user अक्षर *uptr)
अणु
	काष्ठा audit_context *context = audit_context();
	काष्ठा audit_names *n;

	list_क्रम_each_entry(n, &context->names_list, list) अणु
		अगर (!n->name)
			जारी;
		अगर (n->name->uptr == uptr) अणु
			n->name->refcnt++;
			वापस n->name;
		पूर्ण
	पूर्ण
	वापस शून्य;
पूर्ण

/**
 * __audit_getname - add a name to the list
 * @name: name to add
 *
 * Add a name to the list of audit names क्रम this context.
 * Called from fs/namei.c:getname().
 */
व्योम __audit_getname(काष्ठा filename *name)
अणु
	काष्ठा audit_context *context = audit_context();
	काष्ठा audit_names *n;

	अगर (!context->in_syscall)
		वापस;

	n = audit_alloc_name(context, AUDIT_TYPE_UNKNOWN);
	अगर (!n)
		वापस;

	n->name = name;
	n->name_len = AUDIT_NAME_FULL;
	name->aname = n;
	name->refcnt++;
पूर्ण

अटल अंतरभूत पूर्णांक audit_copy_fcaps(काष्ठा audit_names *name,
				   स्थिर काष्ठा dentry *dentry)
अणु
	काष्ठा cpu_vfs_cap_data caps;
	पूर्णांक rc;

	अगर (!dentry)
		वापस 0;

	rc = get_vfs_caps_from_disk(&init_user_ns, dentry, &caps);
	अगर (rc)
		वापस rc;

	name->fcap.permitted = caps.permitted;
	name->fcap.inheritable = caps.inheritable;
	name->fcap.fE = !!(caps.magic_etc & VFS_CAP_FLAGS_EFFECTIVE);
	name->fcap.rootid = caps.rootid;
	name->fcap_ver = (caps.magic_etc & VFS_CAP_REVISION_MASK) >>
				VFS_CAP_REVISION_SHIFT;

	वापस 0;
पूर्ण

/* Copy inode data पूर्णांकo an audit_names. */
अटल व्योम audit_copy_inode(काष्ठा audit_names *name,
			     स्थिर काष्ठा dentry *dentry,
			     काष्ठा inode *inode, अचिन्हित पूर्णांक flags)
अणु
	name->ino   = inode->i_ino;
	name->dev   = inode->i_sb->s_dev;
	name->mode  = inode->i_mode;
	name->uid   = inode->i_uid;
	name->gid   = inode->i_gid;
	name->rdev  = inode->i_rdev;
	security_inode_माला_लोecid(inode, &name->osid);
	अगर (flags & AUDIT_INODE_NOEVAL) अणु
		name->fcap_ver = -1;
		वापस;
	पूर्ण
	audit_copy_fcaps(name, dentry);
पूर्ण

/**
 * __audit_inode - store the inode and device from a lookup
 * @name: name being audited
 * @dentry: dentry being audited
 * @flags: attributes क्रम this particular entry
 */
व्योम __audit_inode(काष्ठा filename *name, स्थिर काष्ठा dentry *dentry,
		   अचिन्हित पूर्णांक flags)
अणु
	काष्ठा audit_context *context = audit_context();
	काष्ठा inode *inode = d_backing_inode(dentry);
	काष्ठा audit_names *n;
	bool parent = flags & AUDIT_INODE_PARENT;
	काष्ठा audit_entry *e;
	काष्ठा list_head *list = &audit_filter_list[AUDIT_FILTER_FS];
	पूर्णांक i;

	अगर (!context->in_syscall)
		वापस;

	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(e, list, list) अणु
		क्रम (i = 0; i < e->rule.field_count; i++) अणु
			काष्ठा audit_field *f = &e->rule.fields[i];

			अगर (f->type == AUDIT_FSTYPE
			    && audit_comparator(inode->i_sb->s_magic,
						f->op, f->val)
			    && e->rule.action == AUDIT_NEVER) अणु
				rcu_पढ़ो_unlock();
				वापस;
			पूर्ण
		पूर्ण
	पूर्ण
	rcu_पढ़ो_unlock();

	अगर (!name)
		जाओ out_alloc;

	/*
	 * If we have a poपूर्णांकer to an audit_names entry alपढ़ोy, then we can
	 * just use it directly अगर the type is correct.
	 */
	n = name->aname;
	अगर (n) अणु
		अगर (parent) अणु
			अगर (n->type == AUDIT_TYPE_PARENT ||
			    n->type == AUDIT_TYPE_UNKNOWN)
				जाओ out;
		पूर्ण अन्यथा अणु
			अगर (n->type != AUDIT_TYPE_PARENT)
				जाओ out;
		पूर्ण
	पूर्ण

	list_क्रम_each_entry_reverse(n, &context->names_list, list) अणु
		अगर (n->ino) अणु
			/* valid inode number, use that क्रम the comparison */
			अगर (n->ino != inode->i_ino ||
			    n->dev != inode->i_sb->s_dev)
				जारी;
		पूर्ण अन्यथा अगर (n->name) अणु
			/* inode number has not been set, check the name */
			अगर (म_भेद(n->name->name, name->name))
				जारी;
		पूर्ण अन्यथा
			/* no inode and no name (?!) ... this is odd ... */
			जारी;

		/* match the correct record type */
		अगर (parent) अणु
			अगर (n->type == AUDIT_TYPE_PARENT ||
			    n->type == AUDIT_TYPE_UNKNOWN)
				जाओ out;
		पूर्ण अन्यथा अणु
			अगर (n->type != AUDIT_TYPE_PARENT)
				जाओ out;
		पूर्ण
	पूर्ण

out_alloc:
	/* unable to find an entry with both a matching name and type */
	n = audit_alloc_name(context, AUDIT_TYPE_UNKNOWN);
	अगर (!n)
		वापस;
	अगर (name) अणु
		n->name = name;
		name->refcnt++;
	पूर्ण

out:
	अगर (parent) अणु
		n->name_len = n->name ? parent_len(n->name->name) : AUDIT_NAME_FULL;
		n->type = AUDIT_TYPE_PARENT;
		अगर (flags & AUDIT_INODE_HIDDEN)
			n->hidden = true;
	पूर्ण अन्यथा अणु
		n->name_len = AUDIT_NAME_FULL;
		n->type = AUDIT_TYPE_NORMAL;
	पूर्ण
	handle_path(dentry);
	audit_copy_inode(n, dentry, inode, flags & AUDIT_INODE_NOEVAL);
पूर्ण

व्योम __audit_file(स्थिर काष्ठा file *file)
अणु
	__audit_inode(शून्य, file->f_path.dentry, 0);
पूर्ण

/**
 * __audit_inode_child - collect inode info क्रम created/हटाओd objects
 * @parent: inode of dentry parent
 * @dentry: dentry being audited
 * @type:   AUDIT_TYPE_* value that we're looking क्रम
 *
 * For syscalls that create or हटाओ fileप्रणाली objects, audit_inode
 * can only collect inक्रमmation क्रम the fileप्रणाली object's parent.
 * This call updates the audit context with the child's inक्रमmation.
 * Syscalls that create a new fileप्रणाली object must be hooked after
 * the object is created.  Syscalls that हटाओ a fileप्रणाली object
 * must be hooked prior, in order to capture the target inode during
 * unsuccessful attempts.
 */
व्योम __audit_inode_child(काष्ठा inode *parent,
			 स्थिर काष्ठा dentry *dentry,
			 स्थिर अचिन्हित अक्षर type)
अणु
	काष्ठा audit_context *context = audit_context();
	काष्ठा inode *inode = d_backing_inode(dentry);
	स्थिर काष्ठा qstr *dname = &dentry->d_name;
	काष्ठा audit_names *n, *found_parent = शून्य, *found_child = शून्य;
	काष्ठा audit_entry *e;
	काष्ठा list_head *list = &audit_filter_list[AUDIT_FILTER_FS];
	पूर्णांक i;

	अगर (!context->in_syscall)
		वापस;

	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(e, list, list) अणु
		क्रम (i = 0; i < e->rule.field_count; i++) अणु
			काष्ठा audit_field *f = &e->rule.fields[i];

			अगर (f->type == AUDIT_FSTYPE
			    && audit_comparator(parent->i_sb->s_magic,
						f->op, f->val)
			    && e->rule.action == AUDIT_NEVER) अणु
				rcu_पढ़ो_unlock();
				वापस;
			पूर्ण
		पूर्ण
	पूर्ण
	rcu_पढ़ो_unlock();

	अगर (inode)
		handle_one(inode);

	/* look क्रम a parent entry first */
	list_क्रम_each_entry(n, &context->names_list, list) अणु
		अगर (!n->name ||
		    (n->type != AUDIT_TYPE_PARENT &&
		     n->type != AUDIT_TYPE_UNKNOWN))
			जारी;

		अगर (n->ino == parent->i_ino && n->dev == parent->i_sb->s_dev &&
		    !audit_compare_dname_path(dname,
					      n->name->name, n->name_len)) अणु
			अगर (n->type == AUDIT_TYPE_UNKNOWN)
				n->type = AUDIT_TYPE_PARENT;
			found_parent = n;
			अवरोध;
		पूर्ण
	पूर्ण

	/* is there a matching child entry? */
	list_क्रम_each_entry(n, &context->names_list, list) अणु
		/* can only match entries that have a name */
		अगर (!n->name ||
		    (n->type != type && n->type != AUDIT_TYPE_UNKNOWN))
			जारी;

		अगर (!म_भेद(dname->name, n->name->name) ||
		    !audit_compare_dname_path(dname, n->name->name,
						found_parent ?
						found_parent->name_len :
						AUDIT_NAME_FULL)) अणु
			अगर (n->type == AUDIT_TYPE_UNKNOWN)
				n->type = type;
			found_child = n;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!found_parent) अणु
		/* create a new, "anonymous" parent record */
		n = audit_alloc_name(context, AUDIT_TYPE_PARENT);
		अगर (!n)
			वापस;
		audit_copy_inode(n, शून्य, parent, 0);
	पूर्ण

	अगर (!found_child) अणु
		found_child = audit_alloc_name(context, type);
		अगर (!found_child)
			वापस;

		/* Re-use the name beदीर्घing to the slot क्रम a matching parent
		 * directory. All names क्रम this context are relinquished in
		 * audit_मुक्त_names() */
		अगर (found_parent) अणु
			found_child->name = found_parent->name;
			found_child->name_len = AUDIT_NAME_FULL;
			found_child->name->refcnt++;
		पूर्ण
	पूर्ण

	अगर (inode)
		audit_copy_inode(found_child, dentry, inode, 0);
	अन्यथा
		found_child->ino = AUDIT_INO_UNSET;
पूर्ण
EXPORT_SYMBOL_GPL(__audit_inode_child);

/**
 * auditsc_get_stamp - get local copies of audit_context values
 * @ctx: audit_context क्रम the task
 * @t: बारpec64 to store समय recorded in the audit_context
 * @serial: serial value that is recorded in the audit_context
 *
 * Also sets the context as auditable.
 */
पूर्णांक auditsc_get_stamp(काष्ठा audit_context *ctx,
		       काष्ठा बारpec64 *t, अचिन्हित पूर्णांक *serial)
अणु
	अगर (!ctx->in_syscall)
		वापस 0;
	अगर (!ctx->serial)
		ctx->serial = audit_serial();
	t->tv_sec  = ctx->स_समय.tv_sec;
	t->tv_nsec = ctx->स_समय.tv_nsec;
	*serial    = ctx->serial;
	अगर (!ctx->prio) अणु
		ctx->prio = 1;
		ctx->current_state = AUDIT_RECORD_CONTEXT;
	पूर्ण
	वापस 1;
पूर्ण

/**
 * __audit_mq_खोलो - record audit data क्रम a POSIX MQ खोलो
 * @oflag: खोलो flag
 * @mode: mode bits
 * @attr: queue attributes
 *
 */
व्योम __audit_mq_खोलो(पूर्णांक oflag, umode_t mode, काष्ठा mq_attr *attr)
अणु
	काष्ठा audit_context *context = audit_context();

	अगर (attr)
		स_नकल(&context->mq_खोलो.attr, attr, माप(काष्ठा mq_attr));
	अन्यथा
		स_रखो(&context->mq_खोलो.attr, 0, माप(काष्ठा mq_attr));

	context->mq_खोलो.oflag = oflag;
	context->mq_खोलो.mode = mode;

	context->type = AUDIT_MQ_OPEN;
पूर्ण

/**
 * __audit_mq_sendrecv - record audit data क्रम a POSIX MQ समयd send/receive
 * @mqdes: MQ descriptor
 * @msg_len: Message length
 * @msg_prio: Message priority
 * @असल_समयout: Message समयout in असलolute समय
 *
 */
व्योम __audit_mq_sendrecv(mqd_t mqdes, माप_प्रकार msg_len, अचिन्हित पूर्णांक msg_prio,
			स्थिर काष्ठा बारpec64 *असल_समयout)
अणु
	काष्ठा audit_context *context = audit_context();
	काष्ठा बारpec64 *p = &context->mq_sendrecv.असल_समयout;

	अगर (असल_समयout)
		स_नकल(p, असल_समयout, माप(*p));
	अन्यथा
		स_रखो(p, 0, माप(*p));

	context->mq_sendrecv.mqdes = mqdes;
	context->mq_sendrecv.msg_len = msg_len;
	context->mq_sendrecv.msg_prio = msg_prio;

	context->type = AUDIT_MQ_SENDRECV;
पूर्ण

/**
 * __audit_mq_notअगरy - record audit data क्रम a POSIX MQ notअगरy
 * @mqdes: MQ descriptor
 * @notअगरication: Notअगरication event
 *
 */

व्योम __audit_mq_notअगरy(mqd_t mqdes, स्थिर काष्ठा sigevent *notअगरication)
अणु
	काष्ठा audit_context *context = audit_context();

	अगर (notअगरication)
		context->mq_notअगरy.sigev_signo = notअगरication->sigev_signo;
	अन्यथा
		context->mq_notअगरy.sigev_signo = 0;

	context->mq_notअगरy.mqdes = mqdes;
	context->type = AUDIT_MQ_NOTIFY;
पूर्ण

/**
 * __audit_mq_माला_लोetattr - record audit data क्रम a POSIX MQ get/set attribute
 * @mqdes: MQ descriptor
 * @mqstat: MQ flags
 *
 */
व्योम __audit_mq_माला_लोetattr(mqd_t mqdes, काष्ठा mq_attr *mqstat)
अणु
	काष्ठा audit_context *context = audit_context();
	context->mq_माला_लोetattr.mqdes = mqdes;
	context->mq_माला_लोetattr.mqstat = *mqstat;
	context->type = AUDIT_MQ_GETSETATTR;
पूर्ण

/**
 * __audit_ipc_obj - record audit data क्रम ipc object
 * @ipcp: ipc permissions
 *
 */
व्योम __audit_ipc_obj(काष्ठा kern_ipc_perm *ipcp)
अणु
	काष्ठा audit_context *context = audit_context();
	context->ipc.uid = ipcp->uid;
	context->ipc.gid = ipcp->gid;
	context->ipc.mode = ipcp->mode;
	context->ipc.has_perm = 0;
	security_ipc_माला_लोecid(ipcp, &context->ipc.osid);
	context->type = AUDIT_IPC;
पूर्ण

/**
 * __audit_ipc_set_perm - record audit data क्रम new ipc permissions
 * @qbytes: msgq bytes
 * @uid: msgq user id
 * @gid: msgq group id
 * @mode: msgq mode (permissions)
 *
 * Called only after audit_ipc_obj().
 */
व्योम __audit_ipc_set_perm(अचिन्हित दीर्घ qbytes, uid_t uid, gid_t gid, umode_t mode)
अणु
	काष्ठा audit_context *context = audit_context();

	context->ipc.qbytes = qbytes;
	context->ipc.perm_uid = uid;
	context->ipc.perm_gid = gid;
	context->ipc.perm_mode = mode;
	context->ipc.has_perm = 1;
पूर्ण

व्योम __audit_bprm(काष्ठा linux_binprm *bprm)
अणु
	काष्ठा audit_context *context = audit_context();

	context->type = AUDIT_EXECVE;
	context->execve.argc = bprm->argc;
पूर्ण


/**
 * __audit_socketcall - record audit data क्रम sys_socketcall
 * @nargs: number of args, which should not be more than AUDITSC_ARGS.
 * @args: args array
 *
 */
पूर्णांक __audit_socketcall(पूर्णांक nargs, अचिन्हित दीर्घ *args)
अणु
	काष्ठा audit_context *context = audit_context();

	अगर (nargs <= 0 || nargs > AUDITSC_ARGS || !args)
		वापस -EINVAL;
	context->type = AUDIT_SOCKETCALL;
	context->socketcall.nargs = nargs;
	स_नकल(context->socketcall.args, args, nargs * माप(अचिन्हित दीर्घ));
	वापस 0;
पूर्ण

/**
 * __audit_fd_pair - record audit data क्रम pipe and socketpair
 * @fd1: the first file descriptor
 * @fd2: the second file descriptor
 *
 */
व्योम __audit_fd_pair(पूर्णांक fd1, पूर्णांक fd2)
अणु
	काष्ठा audit_context *context = audit_context();
	context->fds[0] = fd1;
	context->fds[1] = fd2;
पूर्ण

/**
 * __audit_sockaddr - record audit data क्रम sys_bind, sys_connect, sys_sendto
 * @len: data length in user space
 * @a: data address in kernel space
 *
 * Returns 0 क्रम success or शून्य context or < 0 on error.
 */
पूर्णांक __audit_sockaddr(पूर्णांक len, व्योम *a)
अणु
	काष्ठा audit_context *context = audit_context();

	अगर (!context->sockaddr) अणु
		व्योम *p = kदो_स्मृति(माप(काष्ठा sockaddr_storage), GFP_KERNEL);
		अगर (!p)
			वापस -ENOMEM;
		context->sockaddr = p;
	पूर्ण

	context->sockaddr_len = len;
	स_नकल(context->sockaddr, a, len);
	वापस 0;
पूर्ण

व्योम __audit_ptrace(काष्ठा task_काष्ठा *t)
अणु
	काष्ठा audit_context *context = audit_context();

	context->target_pid = task_tgid_nr(t);
	context->target_auid = audit_get_loginuid(t);
	context->target_uid = task_uid(t);
	context->target_sessionid = audit_get_sessionid(t);
	security_task_माला_लोecid_obj(t, &context->target_sid);
	स_नकल(context->target_comm, t->comm, TASK_COMM_LEN);
पूर्ण

/**
 * audit_संकेत_info_syscall - record संकेत info क्रम syscalls
 * @t: task being संकेतed
 *
 * If the audit subप्रणाली is being terminated, record the task (pid)
 * and uid that is करोing that.
 */
पूर्णांक audit_संकेत_info_syscall(काष्ठा task_काष्ठा *t)
अणु
	काष्ठा audit_aux_data_pids *axp;
	काष्ठा audit_context *ctx = audit_context();
	kuid_t t_uid = task_uid(t);

	अगर (!audit_संकेतs || audit_dummy_context())
		वापस 0;

	/* optimize the common हाल by putting first संकेत recipient directly
	 * in audit_context */
	अगर (!ctx->target_pid) अणु
		ctx->target_pid = task_tgid_nr(t);
		ctx->target_auid = audit_get_loginuid(t);
		ctx->target_uid = t_uid;
		ctx->target_sessionid = audit_get_sessionid(t);
		security_task_माला_लोecid_obj(t, &ctx->target_sid);
		स_नकल(ctx->target_comm, t->comm, TASK_COMM_LEN);
		वापस 0;
	पूर्ण

	axp = (व्योम *)ctx->aux_pids;
	अगर (!axp || axp->pid_count == AUDIT_AUX_PIDS) अणु
		axp = kzalloc(माप(*axp), GFP_ATOMIC);
		अगर (!axp)
			वापस -ENOMEM;

		axp->d.type = AUDIT_OBJ_PID;
		axp->d.next = ctx->aux_pids;
		ctx->aux_pids = (व्योम *)axp;
	पूर्ण
	BUG_ON(axp->pid_count >= AUDIT_AUX_PIDS);

	axp->target_pid[axp->pid_count] = task_tgid_nr(t);
	axp->target_auid[axp->pid_count] = audit_get_loginuid(t);
	axp->target_uid[axp->pid_count] = t_uid;
	axp->target_sessionid[axp->pid_count] = audit_get_sessionid(t);
	security_task_माला_लोecid_obj(t, &axp->target_sid[axp->pid_count]);
	स_नकल(axp->target_comm[axp->pid_count], t->comm, TASK_COMM_LEN);
	axp->pid_count++;

	वापस 0;
पूर्ण

/**
 * __audit_log_bprm_fcaps - store inक्रमmation about a loading bprm and relevant fcaps
 * @bprm: poपूर्णांकer to the bprm being processed
 * @new: the proposed new credentials
 * @old: the old credentials
 *
 * Simply check अगर the proc alपढ़ोy has the caps given by the file and अगर not
 * store the priv escalation info क्रम later auditing at the end of the syscall
 *
 * -Eric
 */
पूर्णांक __audit_log_bprm_fcaps(काष्ठा linux_binprm *bprm,
			   स्थिर काष्ठा cred *new, स्थिर काष्ठा cred *old)
अणु
	काष्ठा audit_aux_data_bprm_fcaps *ax;
	काष्ठा audit_context *context = audit_context();
	काष्ठा cpu_vfs_cap_data vcaps;

	ax = kदो_स्मृति(माप(*ax), GFP_KERNEL);
	अगर (!ax)
		वापस -ENOMEM;

	ax->d.type = AUDIT_BPRM_FCAPS;
	ax->d.next = context->aux;
	context->aux = (व्योम *)ax;

	get_vfs_caps_from_disk(&init_user_ns,
			       bprm->file->f_path.dentry, &vcaps);

	ax->fcap.permitted = vcaps.permitted;
	ax->fcap.inheritable = vcaps.inheritable;
	ax->fcap.fE = !!(vcaps.magic_etc & VFS_CAP_FLAGS_EFFECTIVE);
	ax->fcap.rootid = vcaps.rootid;
	ax->fcap_ver = (vcaps.magic_etc & VFS_CAP_REVISION_MASK) >> VFS_CAP_REVISION_SHIFT;

	ax->old_pcap.permitted   = old->cap_permitted;
	ax->old_pcap.inheritable = old->cap_inheritable;
	ax->old_pcap.effective   = old->cap_effective;
	ax->old_pcap.ambient     = old->cap_ambient;

	ax->new_pcap.permitted   = new->cap_permitted;
	ax->new_pcap.inheritable = new->cap_inheritable;
	ax->new_pcap.effective   = new->cap_effective;
	ax->new_pcap.ambient     = new->cap_ambient;
	वापस 0;
पूर्ण

/**
 * __audit_log_capset - store inक्रमmation about the arguments to the capset syscall
 * @new: the new credentials
 * @old: the old (current) credentials
 *
 * Record the arguments userspace sent to sys_capset क्रम later prपूर्णांकing by the
 * audit प्रणाली अगर applicable
 */
व्योम __audit_log_capset(स्थिर काष्ठा cred *new, स्थिर काष्ठा cred *old)
अणु
	काष्ठा audit_context *context = audit_context();
	context->capset.pid = task_tgid_nr(current);
	context->capset.cap.effective   = new->cap_effective;
	context->capset.cap.inheritable = new->cap_effective;
	context->capset.cap.permitted   = new->cap_permitted;
	context->capset.cap.ambient     = new->cap_ambient;
	context->type = AUDIT_CAPSET;
पूर्ण

व्योम __audit_mmap_fd(पूर्णांक fd, पूर्णांक flags)
अणु
	काष्ठा audit_context *context = audit_context();
	context->mmap.fd = fd;
	context->mmap.flags = flags;
	context->type = AUDIT_MMAP;
पूर्ण

व्योम __audit_log_kern_module(अक्षर *name)
अणु
	काष्ठा audit_context *context = audit_context();

	context->module.name = kstrdup(name, GFP_KERNEL);
	अगर (!context->module.name)
		audit_log_lost("out of memory in __audit_log_kern_module");
	context->type = AUDIT_KERN_MODULE;
पूर्ण

व्योम __audit_fanotअगरy(अचिन्हित पूर्णांक response)
अणु
	audit_log(audit_context(), GFP_KERNEL,
		AUDIT_FANOTIFY,	"resp=%u", response);
पूर्ण

व्योम __audit_tk_injoffset(काष्ठा बारpec64 offset)
अणु
	audit_log(audit_context(), GFP_KERNEL, AUDIT_TIME_INJOFFSET,
		  "sec=%lli nsec=%li",
		  (दीर्घ दीर्घ)offset.tv_sec, offset.tv_nsec);
पूर्ण

अटल व्योम audit_log_ntp_val(स्थिर काष्ठा audit_ntp_data *ad,
			      स्थिर अक्षर *op, क्रमागत audit_ntp_type type)
अणु
	स्थिर काष्ठा audit_ntp_val *val = &ad->vals[type];

	अगर (val->newval == val->oldval)
		वापस;

	audit_log(audit_context(), GFP_KERNEL, AUDIT_TIME_ADJNTPVAL,
		  "op=%s old=%lli new=%lli", op, val->oldval, val->newval);
पूर्ण

व्योम __audit_ntp_log(स्थिर काष्ठा audit_ntp_data *ad)
अणु
	audit_log_ntp_val(ad, "offset",	AUDIT_NTP_OFFSET);
	audit_log_ntp_val(ad, "freq",	AUDIT_NTP_FREQ);
	audit_log_ntp_val(ad, "status",	AUDIT_NTP_STATUS);
	audit_log_ntp_val(ad, "tai",	AUDIT_NTP_TAI);
	audit_log_ntp_val(ad, "tick",	AUDIT_NTP_TICK);
	audit_log_ntp_val(ad, "adjust",	AUDIT_NTP_ADJUST);
पूर्ण

व्योम __audit_log_nfcfg(स्थिर अक्षर *name, u8 af, अचिन्हित पूर्णांक nentries,
		       क्रमागत audit_nfcfgop op, gfp_t gfp)
अणु
	काष्ठा audit_buffer *ab;
	अक्षर comm[माप(current->comm)];

	ab = audit_log_start(audit_context(), gfp, AUDIT_NETFILTER_CFG);
	अगर (!ab)
		वापस;
	audit_log_क्रमmat(ab, "table=%s family=%u entries=%u op=%s",
			 name, af, nentries, audit_nfcfgs[op].s);

	audit_log_क्रमmat(ab, " pid=%u", task_pid_nr(current));
	audit_log_task_context(ab); /* subj= */
	audit_log_क्रमmat(ab, " comm=");
	audit_log_untrustedstring(ab, get_task_comm(comm, current));
	audit_log_end(ab);
पूर्ण
EXPORT_SYMBOL_GPL(__audit_log_nfcfg);

अटल व्योम audit_log_task(काष्ठा audit_buffer *ab)
अणु
	kuid_t auid, uid;
	kgid_t gid;
	अचिन्हित पूर्णांक sessionid;
	अक्षर comm[माप(current->comm)];

	auid = audit_get_loginuid(current);
	sessionid = audit_get_sessionid(current);
	current_uid_gid(&uid, &gid);

	audit_log_क्रमmat(ab, "auid=%u uid=%u gid=%u ses=%u",
			 from_kuid(&init_user_ns, auid),
			 from_kuid(&init_user_ns, uid),
			 from_kgid(&init_user_ns, gid),
			 sessionid);
	audit_log_task_context(ab);
	audit_log_क्रमmat(ab, " pid=%d comm=", task_tgid_nr(current));
	audit_log_untrustedstring(ab, get_task_comm(comm, current));
	audit_log_d_path_exe(ab, current->mm);
पूर्ण

/**
 * audit_core_dumps - record inक्रमmation about processes that end abnormally
 * @signr: संकेत value
 *
 * If a process ends with a core dump, something fishy is going on and we
 * should record the event क्रम investigation.
 */
व्योम audit_core_dumps(दीर्घ signr)
अणु
	काष्ठा audit_buffer *ab;

	अगर (!audit_enabled)
		वापस;

	अगर (signr == SIGQUIT)	/* करोn't care क्रम those */
		वापस;

	ab = audit_log_start(audit_context(), GFP_KERNEL, AUDIT_ANOM_ABEND);
	अगर (unlikely(!ab))
		वापस;
	audit_log_task(ab);
	audit_log_क्रमmat(ab, " sig=%ld res=1", signr);
	audit_log_end(ab);
पूर्ण

/**
 * audit_seccomp - record inक्रमmation about a seccomp action
 * @syscall: syscall number
 * @signr: संकेत value
 * @code: the seccomp action
 *
 * Record the inक्रमmation associated with a seccomp action. Event filtering क्रम
 * seccomp actions that are not to be logged is करोne in seccomp_log().
 * Thereक्रमe, this function क्रमces auditing independent of the audit_enabled
 * and dummy context state because seccomp actions should be logged even when
 * audit is not in use.
 */
व्योम audit_seccomp(अचिन्हित दीर्घ syscall, दीर्घ signr, पूर्णांक code)
अणु
	काष्ठा audit_buffer *ab;

	ab = audit_log_start(audit_context(), GFP_KERNEL, AUDIT_SECCOMP);
	अगर (unlikely(!ab))
		वापस;
	audit_log_task(ab);
	audit_log_क्रमmat(ab, " sig=%ld arch=%x syscall=%ld compat=%d ip=0x%lx code=0x%x",
			 signr, syscall_get_arch(current), syscall,
			 in_compat_syscall(), KSTK_EIP(current), code);
	audit_log_end(ab);
पूर्ण

व्योम audit_seccomp_actions_logged(स्थिर अक्षर *names, स्थिर अक्षर *old_names,
				  पूर्णांक res)
अणु
	काष्ठा audit_buffer *ab;

	अगर (!audit_enabled)
		वापस;

	ab = audit_log_start(audit_context(), GFP_KERNEL,
			     AUDIT_CONFIG_CHANGE);
	अगर (unlikely(!ab))
		वापस;

	audit_log_क्रमmat(ab,
			 "op=seccomp-logging actions=%s old-actions=%s res=%d",
			 names, old_names, res);
	audit_log_end(ab);
पूर्ण

काष्ठा list_head *audit_समाप्तed_trees(व्योम)
अणु
	काष्ठा audit_context *ctx = audit_context();
	अगर (likely(!ctx || !ctx->in_syscall))
		वापस शून्य;
	वापस &ctx->समाप्तed_trees;
पूर्ण
