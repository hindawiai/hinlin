<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* auditfilter.c -- filtering of audit events
 *
 * Copyright 2003-2004 Red Hat, Inc.
 * Copyright 2005 Hewlett-Packard Development Company, L.P.
 * Copyright 2005 IBM Corporation
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/audit.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/mutex.h>
#समावेश <linux/fs.h>
#समावेश <linux/namei.h>
#समावेश <linux/netlink.h>
#समावेश <linux/sched.h>
#समावेश <linux/slab.h>
#समावेश <linux/security.h>
#समावेश <net/net_namespace.h>
#समावेश <net/sock.h>
#समावेश "audit.h"

/*
 * Locking model:
 *
 * audit_filter_mutex:
 *		Synchronizes ग_लिखोs and blocking पढ़ोs of audit's filterlist
 *		data.  Rcu is used to traverse the filterlist and access
 *		contents of काष्ठाs audit_entry, audit_watch and opaque
 *		LSM rules during filtering.  If modअगरied, these काष्ठाures
 *		must be copied and replace their counterparts in the filterlist.
 *		An audit_parent काष्ठा is not accessed during filtering, so may
 *		be written directly provided audit_filter_mutex is held.
 */

/* Audit filter lists, defined in <linux/audit.h> */
काष्ठा list_head audit_filter_list[AUDIT_NR_FILTERS] = अणु
	LIST_HEAD_INIT(audit_filter_list[0]),
	LIST_HEAD_INIT(audit_filter_list[1]),
	LIST_HEAD_INIT(audit_filter_list[2]),
	LIST_HEAD_INIT(audit_filter_list[3]),
	LIST_HEAD_INIT(audit_filter_list[4]),
	LIST_HEAD_INIT(audit_filter_list[5]),
	LIST_HEAD_INIT(audit_filter_list[6]),
#अगर AUDIT_NR_FILTERS != 7
#त्रुटि Fix audit_filter_list initialiser
#पूर्ण_अगर
पूर्ण;
अटल काष्ठा list_head audit_rules_list[AUDIT_NR_FILTERS] = अणु
	LIST_HEAD_INIT(audit_rules_list[0]),
	LIST_HEAD_INIT(audit_rules_list[1]),
	LIST_HEAD_INIT(audit_rules_list[2]),
	LIST_HEAD_INIT(audit_rules_list[3]),
	LIST_HEAD_INIT(audit_rules_list[4]),
	LIST_HEAD_INIT(audit_rules_list[5]),
	LIST_HEAD_INIT(audit_rules_list[6]),
पूर्ण;

DEFINE_MUTEX(audit_filter_mutex);

अटल व्योम audit_मुक्त_lsm_field(काष्ठा audit_field *f)
अणु
	चयन (f->type) अणु
	हाल AUDIT_SUBJ_USER:
	हाल AUDIT_SUBJ_ROLE:
	हाल AUDIT_SUBJ_TYPE:
	हाल AUDIT_SUBJ_SEN:
	हाल AUDIT_SUBJ_CLR:
	हाल AUDIT_OBJ_USER:
	हाल AUDIT_OBJ_ROLE:
	हाल AUDIT_OBJ_TYPE:
	हाल AUDIT_OBJ_LEV_LOW:
	हाल AUDIT_OBJ_LEV_HIGH:
		kमुक्त(f->lsm_str);
		security_audit_rule_मुक्त(f->lsm_rule);
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम audit_मुक्त_rule(काष्ठा audit_entry *e)
अणु
	पूर्णांक i;
	काष्ठा audit_krule *erule = &e->rule;

	/* some rules करोn't have associated watches */
	अगर (erule->watch)
		audit_put_watch(erule->watch);
	अगर (erule->fields)
		क्रम (i = 0; i < erule->field_count; i++)
			audit_मुक्त_lsm_field(&erule->fields[i]);
	kमुक्त(erule->fields);
	kमुक्त(erule->filterkey);
	kमुक्त(e);
पूर्ण

व्योम audit_मुक्त_rule_rcu(काष्ठा rcu_head *head)
अणु
	काष्ठा audit_entry *e = container_of(head, काष्ठा audit_entry, rcu);
	audit_मुक्त_rule(e);
पूर्ण

/* Initialize an audit filterlist entry. */
अटल अंतरभूत काष्ठा audit_entry *audit_init_entry(u32 field_count)
अणु
	काष्ठा audit_entry *entry;
	काष्ठा audit_field *fields;

	entry = kzalloc(माप(*entry), GFP_KERNEL);
	अगर (unlikely(!entry))
		वापस शून्य;

	fields = kसुस्मृति(field_count, माप(*fields), GFP_KERNEL);
	अगर (unlikely(!fields)) अणु
		kमुक्त(entry);
		वापस शून्य;
	पूर्ण
	entry->rule.fields = fields;

	वापस entry;
पूर्ण

/* Unpack a filter field's string representation from user-space
 * buffer. */
अक्षर *audit_unpack_string(व्योम **bufp, माप_प्रकार *reमुख्य, माप_प्रकार len)
अणु
	अक्षर *str;

	अगर (!*bufp || (len == 0) || (len > *reमुख्य))
		वापस ERR_PTR(-EINVAL);

	/* Of the currently implemented string fields, PATH_MAX
	 * defines the दीर्घest valid length.
	 */
	अगर (len > PATH_MAX)
		वापस ERR_PTR(-ENAMETOOLONG);

	str = kदो_स्मृति(len + 1, GFP_KERNEL);
	अगर (unlikely(!str))
		वापस ERR_PTR(-ENOMEM);

	स_नकल(str, *bufp, len);
	str[len] = 0;
	*bufp += len;
	*reमुख्य -= len;

	वापस str;
पूर्ण

/* Translate an inode field to kernel representation. */
अटल अंतरभूत पूर्णांक audit_to_inode(काष्ठा audit_krule *krule,
				 काष्ठा audit_field *f)
अणु
	अगर (krule->listnr != AUDIT_FILTER_EXIT ||
	    krule->inode_f || krule->watch || krule->tree ||
	    (f->op != Audit_equal && f->op != Audit_not_equal))
		वापस -EINVAL;

	krule->inode_f = f;
	वापस 0;
पूर्ण

अटल __u32 *classes[AUDIT_SYSCALL_CLASSES];

पूर्णांक __init audit_रेजिस्टर_class(पूर्णांक class, अचिन्हित *list)
अणु
	__u32 *p = kसुस्मृति(AUDIT_BITMASK_SIZE, माप(__u32), GFP_KERNEL);
	अगर (!p)
		वापस -ENOMEM;
	जबतक (*list != ~0U) अणु
		अचिन्हित n = *list++;
		अगर (n >= AUDIT_BITMASK_SIZE * 32 - AUDIT_SYSCALL_CLASSES) अणु
			kमुक्त(p);
			वापस -EINVAL;
		पूर्ण
		p[AUDIT_WORD(n)] |= AUDIT_BIT(n);
	पूर्ण
	अगर (class >= AUDIT_SYSCALL_CLASSES || classes[class]) अणु
		kमुक्त(p);
		वापस -EINVAL;
	पूर्ण
	classes[class] = p;
	वापस 0;
पूर्ण

पूर्णांक audit_match_class(पूर्णांक class, अचिन्हित syscall)
अणु
	अगर (unlikely(syscall >= AUDIT_BITMASK_SIZE * 32))
		वापस 0;
	अगर (unlikely(class >= AUDIT_SYSCALL_CLASSES || !classes[class]))
		वापस 0;
	वापस classes[class][AUDIT_WORD(syscall)] & AUDIT_BIT(syscall);
पूर्ण

#अगर_घोषित CONFIG_AUDITSYSCALL
अटल अंतरभूत पूर्णांक audit_match_class_bits(पूर्णांक class, u32 *mask)
अणु
	पूर्णांक i;

	अगर (classes[class]) अणु
		क्रम (i = 0; i < AUDIT_BITMASK_SIZE; i++)
			अगर (mask[i] & classes[class][i])
				वापस 0;
	पूर्ण
	वापस 1;
पूर्ण

अटल पूर्णांक audit_match_संकेत(काष्ठा audit_entry *entry)
अणु
	काष्ठा audit_field *arch = entry->rule.arch_f;

	अगर (!arch) अणु
		/* When arch is unspecअगरied, we must check both masks on biarch
		 * as syscall number alone is ambiguous. */
		वापस (audit_match_class_bits(AUDIT_CLASS_SIGNAL,
					       entry->rule.mask) &&
			audit_match_class_bits(AUDIT_CLASS_SIGNAL_32,
					       entry->rule.mask));
	पूर्ण

	चयन(audit_classअगरy_arch(arch->val)) अणु
	हाल 0: /* native */
		वापस (audit_match_class_bits(AUDIT_CLASS_SIGNAL,
					       entry->rule.mask));
	हाल 1: /* 32bit on biarch */
		वापस (audit_match_class_bits(AUDIT_CLASS_SIGNAL_32,
					       entry->rule.mask));
	शेष:
		वापस 1;
	पूर्ण
पूर्ण
#पूर्ण_अगर

/* Common user-space to kernel rule translation. */
अटल अंतरभूत काष्ठा audit_entry *audit_to_entry_common(काष्ठा audit_rule_data *rule)
अणु
	अचिन्हित listnr;
	काष्ठा audit_entry *entry;
	पूर्णांक i, err;

	err = -EINVAL;
	listnr = rule->flags & ~AUDIT_FILTER_PREPEND;
	चयन(listnr) अणु
	शेष:
		जाओ निकास_err;
#अगर_घोषित CONFIG_AUDITSYSCALL
	हाल AUDIT_FILTER_ENTRY:
		pr_err("AUDIT_FILTER_ENTRY is deprecated\n");
		जाओ निकास_err;
	हाल AUDIT_FILTER_EXIT:
	हाल AUDIT_FILTER_TASK:
#पूर्ण_अगर
	हाल AUDIT_FILTER_USER:
	हाल AUDIT_FILTER_EXCLUDE:
	हाल AUDIT_FILTER_FS:
		;
	पूर्ण
	अगर (unlikely(rule->action == AUDIT_POSSIBLE)) अणु
		pr_err("AUDIT_POSSIBLE is deprecated\n");
		जाओ निकास_err;
	पूर्ण
	अगर (rule->action != AUDIT_NEVER && rule->action != AUDIT_ALWAYS)
		जाओ निकास_err;
	अगर (rule->field_count > AUDIT_MAX_FIELDS)
		जाओ निकास_err;

	err = -ENOMEM;
	entry = audit_init_entry(rule->field_count);
	अगर (!entry)
		जाओ निकास_err;

	entry->rule.flags = rule->flags & AUDIT_FILTER_PREPEND;
	entry->rule.listnr = listnr;
	entry->rule.action = rule->action;
	entry->rule.field_count = rule->field_count;

	क्रम (i = 0; i < AUDIT_BITMASK_SIZE; i++)
		entry->rule.mask[i] = rule->mask[i];

	क्रम (i = 0; i < AUDIT_SYSCALL_CLASSES; i++) अणु
		पूर्णांक bit = AUDIT_BITMASK_SIZE * 32 - i - 1;
		__u32 *p = &entry->rule.mask[AUDIT_WORD(bit)];
		__u32 *class;

		अगर (!(*p & AUDIT_BIT(bit)))
			जारी;
		*p &= ~AUDIT_BIT(bit);
		class = classes[i];
		अगर (class) अणु
			पूर्णांक j;
			क्रम (j = 0; j < AUDIT_BITMASK_SIZE; j++)
				entry->rule.mask[j] |= class[j];
		पूर्ण
	पूर्ण

	वापस entry;

निकास_err:
	वापस ERR_PTR(err);
पूर्ण

अटल u32 audit_ops[] =
अणु
	[Audit_equal] = AUDIT_EQUAL,
	[Audit_not_equal] = AUDIT_NOT_EQUAL,
	[Audit_biपंचांगask] = AUDIT_BIT_MASK,
	[Audit_bittest] = AUDIT_BIT_TEST,
	[Audit_lt] = AUDIT_LESS_THAN,
	[Audit_gt] = AUDIT_GREATER_THAN,
	[Audit_le] = AUDIT_LESS_THAN_OR_EQUAL,
	[Audit_ge] = AUDIT_GREATER_THAN_OR_EQUAL,
पूर्ण;

अटल u32 audit_to_op(u32 op)
अणु
	u32 n;
	क्रम (n = Audit_equal; n < Audit_bad && audit_ops[n] != op; n++)
		;
	वापस n;
पूर्ण

/* check अगर an audit field is valid */
अटल पूर्णांक audit_field_valid(काष्ठा audit_entry *entry, काष्ठा audit_field *f)
अणु
	चयन (f->type) अणु
	हाल AUDIT_MSGTYPE:
		अगर (entry->rule.listnr != AUDIT_FILTER_EXCLUDE &&
		    entry->rule.listnr != AUDIT_FILTER_USER)
			वापस -EINVAL;
		अवरोध;
	हाल AUDIT_FSTYPE:
		अगर (entry->rule.listnr != AUDIT_FILTER_FS)
			वापस -EINVAL;
		अवरोध;
	पूर्ण

	चयन (entry->rule.listnr) अणु
	हाल AUDIT_FILTER_FS:
		चयन(f->type) अणु
		हाल AUDIT_FSTYPE:
		हाल AUDIT_FILTERKEY:
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	/* Check क्रम valid field type and op */
	चयन (f->type) अणु
	हाल AUDIT_ARG0:
	हाल AUDIT_ARG1:
	हाल AUDIT_ARG2:
	हाल AUDIT_ARG3:
	हाल AUDIT_PERS: /* <uapi/linux/personality.h> */
	हाल AUDIT_DEVMINOR:
		/* all ops are valid */
		अवरोध;
	हाल AUDIT_UID:
	हाल AUDIT_EUID:
	हाल AUDIT_SUID:
	हाल AUDIT_FSUID:
	हाल AUDIT_LOGINUID:
	हाल AUDIT_OBJ_UID:
	हाल AUDIT_GID:
	हाल AUDIT_EGID:
	हाल AUDIT_SGID:
	हाल AUDIT_FSGID:
	हाल AUDIT_OBJ_GID:
	हाल AUDIT_PID:
	हाल AUDIT_MSGTYPE:
	हाल AUDIT_PPID:
	हाल AUDIT_DEVMAJOR:
	हाल AUDIT_EXIT:
	हाल AUDIT_SUCCESS:
	हाल AUDIT_INODE:
	हाल AUDIT_SESSIONID:
	हाल AUDIT_SUBJ_SEN:
	हाल AUDIT_SUBJ_CLR:
	हाल AUDIT_OBJ_LEV_LOW:
	हाल AUDIT_OBJ_LEV_HIGH:
	हाल AUDIT_SADDR_FAM:
		/* bit ops are only useful on syscall args */
		अगर (f->op == Audit_biपंचांगask || f->op == Audit_bittest)
			वापस -EINVAL;
		अवरोध;
	हाल AUDIT_SUBJ_USER:
	हाल AUDIT_SUBJ_ROLE:
	हाल AUDIT_SUBJ_TYPE:
	हाल AUDIT_OBJ_USER:
	हाल AUDIT_OBJ_ROLE:
	हाल AUDIT_OBJ_TYPE:
	हाल AUDIT_WATCH:
	हाल AUDIT_सूची:
	हाल AUDIT_FILTERKEY:
	हाल AUDIT_LOGINUID_SET:
	हाल AUDIT_ARCH:
	हाल AUDIT_FSTYPE:
	हाल AUDIT_PERM:
	हाल AUDIT_खाताTYPE:
	हाल AUDIT_FIELD_COMPARE:
	हाल AUDIT_EXE:
		/* only equal and not equal valid ops */
		अगर (f->op != Audit_not_equal && f->op != Audit_equal)
			वापस -EINVAL;
		अवरोध;
	शेष:
		/* field not recognized */
		वापस -EINVAL;
	पूर्ण

	/* Check क्रम select valid field values */
	चयन (f->type) अणु
	हाल AUDIT_LOGINUID_SET:
		अगर ((f->val != 0) && (f->val != 1))
			वापस -EINVAL;
		अवरोध;
	हाल AUDIT_PERM:
		अगर (f->val & ~15)
			वापस -EINVAL;
		अवरोध;
	हाल AUDIT_खाताTYPE:
		अगर (f->val & ~S_IFMT)
			वापस -EINVAL;
		अवरोध;
	हाल AUDIT_FIELD_COMPARE:
		अगर (f->val > AUDIT_MAX_FIELD_COMPARE)
			वापस -EINVAL;
		अवरोध;
	हाल AUDIT_SADDR_FAM:
		अगर (f->val >= AF_MAX)
			वापस -EINVAL;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

/* Translate काष्ठा audit_rule_data to kernel's rule representation. */
अटल काष्ठा audit_entry *audit_data_to_entry(काष्ठा audit_rule_data *data,
					       माप_प्रकार datasz)
अणु
	पूर्णांक err = 0;
	काष्ठा audit_entry *entry;
	व्योम *bufp;
	माप_प्रकार reमुख्य = datasz - माप(काष्ठा audit_rule_data);
	पूर्णांक i;
	अक्षर *str;
	काष्ठा audit_fsnotअगरy_mark *audit_mark;

	entry = audit_to_entry_common(data);
	अगर (IS_ERR(entry))
		जाओ निकास_noमुक्त;

	bufp = data->buf;
	क्रम (i = 0; i < data->field_count; i++) अणु
		काष्ठा audit_field *f = &entry->rule.fields[i];
		u32 f_val;

		err = -EINVAL;

		f->op = audit_to_op(data->fieldflags[i]);
		अगर (f->op == Audit_bad)
			जाओ निकास_मुक्त;

		f->type = data->fields[i];
		f_val = data->values[i];

		/* Support legacy tests क्रम a valid loginuid */
		अगर ((f->type == AUDIT_LOGINUID) && (f_val == AUDIT_UID_UNSET)) अणु
			f->type = AUDIT_LOGINUID_SET;
			f_val = 0;
			entry->rule.pflags |= AUDIT_LOGINUID_LEGACY;
		पूर्ण

		err = audit_field_valid(entry, f);
		अगर (err)
			जाओ निकास_मुक्त;

		err = -EINVAL;
		चयन (f->type) अणु
		हाल AUDIT_LOGINUID:
		हाल AUDIT_UID:
		हाल AUDIT_EUID:
		हाल AUDIT_SUID:
		हाल AUDIT_FSUID:
		हाल AUDIT_OBJ_UID:
			f->uid = make_kuid(current_user_ns(), f_val);
			अगर (!uid_valid(f->uid))
				जाओ निकास_मुक्त;
			अवरोध;
		हाल AUDIT_GID:
		हाल AUDIT_EGID:
		हाल AUDIT_SGID:
		हाल AUDIT_FSGID:
		हाल AUDIT_OBJ_GID:
			f->gid = make_kgid(current_user_ns(), f_val);
			अगर (!gid_valid(f->gid))
				जाओ निकास_मुक्त;
			अवरोध;
		हाल AUDIT_ARCH:
			f->val = f_val;
			entry->rule.arch_f = f;
			अवरोध;
		हाल AUDIT_SUBJ_USER:
		हाल AUDIT_SUBJ_ROLE:
		हाल AUDIT_SUBJ_TYPE:
		हाल AUDIT_SUBJ_SEN:
		हाल AUDIT_SUBJ_CLR:
		हाल AUDIT_OBJ_USER:
		हाल AUDIT_OBJ_ROLE:
		हाल AUDIT_OBJ_TYPE:
		हाल AUDIT_OBJ_LEV_LOW:
		हाल AUDIT_OBJ_LEV_HIGH:
			str = audit_unpack_string(&bufp, &reमुख्य, f_val);
			अगर (IS_ERR(str)) अणु
				err = PTR_ERR(str);
				जाओ निकास_मुक्त;
			पूर्ण
			entry->rule.buflen += f_val;
			f->lsm_str = str;
			err = security_audit_rule_init(f->type, f->op, str,
						       (व्योम **)&f->lsm_rule);
			/* Keep currently invalid fields around in हाल they
			 * become valid after a policy reload. */
			अगर (err == -EINVAL) अणु
				pr_warn("audit rule for LSM \'%s\' is invalid\n",
					str);
				err = 0;
			पूर्ण अन्यथा अगर (err)
				जाओ निकास_मुक्त;
			अवरोध;
		हाल AUDIT_WATCH:
			str = audit_unpack_string(&bufp, &reमुख्य, f_val);
			अगर (IS_ERR(str)) अणु
				err = PTR_ERR(str);
				जाओ निकास_मुक्त;
			पूर्ण
			err = audit_to_watch(&entry->rule, str, f_val, f->op);
			अगर (err) अणु
				kमुक्त(str);
				जाओ निकास_मुक्त;
			पूर्ण
			entry->rule.buflen += f_val;
			अवरोध;
		हाल AUDIT_सूची:
			str = audit_unpack_string(&bufp, &reमुख्य, f_val);
			अगर (IS_ERR(str)) अणु
				err = PTR_ERR(str);
				जाओ निकास_मुक्त;
			पूर्ण
			err = audit_make_tree(&entry->rule, str, f->op);
			kमुक्त(str);
			अगर (err)
				जाओ निकास_मुक्त;
			entry->rule.buflen += f_val;
			अवरोध;
		हाल AUDIT_INODE:
			f->val = f_val;
			err = audit_to_inode(&entry->rule, f);
			अगर (err)
				जाओ निकास_मुक्त;
			अवरोध;
		हाल AUDIT_FILTERKEY:
			अगर (entry->rule.filterkey || f_val > AUDIT_MAX_KEY_LEN)
				जाओ निकास_मुक्त;
			str = audit_unpack_string(&bufp, &reमुख्य, f_val);
			अगर (IS_ERR(str)) अणु
				err = PTR_ERR(str);
				जाओ निकास_मुक्त;
			पूर्ण
			entry->rule.buflen += f_val;
			entry->rule.filterkey = str;
			अवरोध;
		हाल AUDIT_EXE:
			अगर (entry->rule.exe || f_val > PATH_MAX)
				जाओ निकास_मुक्त;
			str = audit_unpack_string(&bufp, &reमुख्य, f_val);
			अगर (IS_ERR(str)) अणु
				err = PTR_ERR(str);
				जाओ निकास_मुक्त;
			पूर्ण
			audit_mark = audit_alloc_mark(&entry->rule, str, f_val);
			अगर (IS_ERR(audit_mark)) अणु
				kमुक्त(str);
				err = PTR_ERR(audit_mark);
				जाओ निकास_मुक्त;
			पूर्ण
			entry->rule.buflen += f_val;
			entry->rule.exe = audit_mark;
			अवरोध;
		शेष:
			f->val = f_val;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (entry->rule.inode_f && entry->rule.inode_f->op == Audit_not_equal)
		entry->rule.inode_f = शून्य;

निकास_noमुक्त:
	वापस entry;

निकास_मुक्त:
	अगर (entry->rule.tree)
		audit_put_tree(entry->rule.tree); /* that's the temporary one */
	अगर (entry->rule.exe)
		audit_हटाओ_mark(entry->rule.exe); /* that's the ढाँचा one */
	audit_मुक्त_rule(entry);
	वापस ERR_PTR(err);
पूर्ण

/* Pack a filter field's string representation पूर्णांकo data block. */
अटल अंतरभूत माप_प्रकार audit_pack_string(व्योम **bufp, स्थिर अक्षर *str)
अणु
	माप_प्रकार len = म_माप(str);

	स_नकल(*bufp, str, len);
	*bufp += len;

	वापस len;
पूर्ण

/* Translate kernel rule representation to काष्ठा audit_rule_data. */
अटल काष्ठा audit_rule_data *audit_krule_to_data(काष्ठा audit_krule *krule)
अणु
	काष्ठा audit_rule_data *data;
	व्योम *bufp;
	पूर्णांक i;

	data = kदो_स्मृति(माप(*data) + krule->buflen, GFP_KERNEL);
	अगर (unlikely(!data))
		वापस शून्य;
	स_रखो(data, 0, माप(*data));

	data->flags = krule->flags | krule->listnr;
	data->action = krule->action;
	data->field_count = krule->field_count;
	bufp = data->buf;
	क्रम (i = 0; i < data->field_count; i++) अणु
		काष्ठा audit_field *f = &krule->fields[i];

		data->fields[i] = f->type;
		data->fieldflags[i] = audit_ops[f->op];
		चयन(f->type) अणु
		हाल AUDIT_SUBJ_USER:
		हाल AUDIT_SUBJ_ROLE:
		हाल AUDIT_SUBJ_TYPE:
		हाल AUDIT_SUBJ_SEN:
		हाल AUDIT_SUBJ_CLR:
		हाल AUDIT_OBJ_USER:
		हाल AUDIT_OBJ_ROLE:
		हाल AUDIT_OBJ_TYPE:
		हाल AUDIT_OBJ_LEV_LOW:
		हाल AUDIT_OBJ_LEV_HIGH:
			data->buflen += data->values[i] =
				audit_pack_string(&bufp, f->lsm_str);
			अवरोध;
		हाल AUDIT_WATCH:
			data->buflen += data->values[i] =
				audit_pack_string(&bufp,
						  audit_watch_path(krule->watch));
			अवरोध;
		हाल AUDIT_सूची:
			data->buflen += data->values[i] =
				audit_pack_string(&bufp,
						  audit_tree_path(krule->tree));
			अवरोध;
		हाल AUDIT_FILTERKEY:
			data->buflen += data->values[i] =
				audit_pack_string(&bufp, krule->filterkey);
			अवरोध;
		हाल AUDIT_EXE:
			data->buflen += data->values[i] =
				audit_pack_string(&bufp, audit_mark_path(krule->exe));
			अवरोध;
		हाल AUDIT_LOGINUID_SET:
			अगर (krule->pflags & AUDIT_LOGINUID_LEGACY && !f->val) अणु
				data->fields[i] = AUDIT_LOGINUID;
				data->values[i] = AUDIT_UID_UNSET;
				अवरोध;
			पूर्ण
			fallthrough;	/* अगर set */
		शेष:
			data->values[i] = f->val;
		पूर्ण
	पूर्ण
	क्रम (i = 0; i < AUDIT_BITMASK_SIZE; i++) data->mask[i] = krule->mask[i];

	वापस data;
पूर्ण

/* Compare two rules in kernel क्रमmat.  Considered success अगर rules
 * करोn't match. */
अटल पूर्णांक audit_compare_rule(काष्ठा audit_krule *a, काष्ठा audit_krule *b)
अणु
	पूर्णांक i;

	अगर (a->flags != b->flags ||
	    a->pflags != b->pflags ||
	    a->listnr != b->listnr ||
	    a->action != b->action ||
	    a->field_count != b->field_count)
		वापस 1;

	क्रम (i = 0; i < a->field_count; i++) अणु
		अगर (a->fields[i].type != b->fields[i].type ||
		    a->fields[i].op != b->fields[i].op)
			वापस 1;

		चयन(a->fields[i].type) अणु
		हाल AUDIT_SUBJ_USER:
		हाल AUDIT_SUBJ_ROLE:
		हाल AUDIT_SUBJ_TYPE:
		हाल AUDIT_SUBJ_SEN:
		हाल AUDIT_SUBJ_CLR:
		हाल AUDIT_OBJ_USER:
		हाल AUDIT_OBJ_ROLE:
		हाल AUDIT_OBJ_TYPE:
		हाल AUDIT_OBJ_LEV_LOW:
		हाल AUDIT_OBJ_LEV_HIGH:
			अगर (म_भेद(a->fields[i].lsm_str, b->fields[i].lsm_str))
				वापस 1;
			अवरोध;
		हाल AUDIT_WATCH:
			अगर (म_भेद(audit_watch_path(a->watch),
				   audit_watch_path(b->watch)))
				वापस 1;
			अवरोध;
		हाल AUDIT_सूची:
			अगर (म_भेद(audit_tree_path(a->tree),
				   audit_tree_path(b->tree)))
				वापस 1;
			अवरोध;
		हाल AUDIT_FILTERKEY:
			/* both filterkeys exist based on above type compare */
			अगर (म_भेद(a->filterkey, b->filterkey))
				वापस 1;
			अवरोध;
		हाल AUDIT_EXE:
			/* both paths exist based on above type compare */
			अगर (म_भेद(audit_mark_path(a->exe),
				   audit_mark_path(b->exe)))
				वापस 1;
			अवरोध;
		हाल AUDIT_UID:
		हाल AUDIT_EUID:
		हाल AUDIT_SUID:
		हाल AUDIT_FSUID:
		हाल AUDIT_LOGINUID:
		हाल AUDIT_OBJ_UID:
			अगर (!uid_eq(a->fields[i].uid, b->fields[i].uid))
				वापस 1;
			अवरोध;
		हाल AUDIT_GID:
		हाल AUDIT_EGID:
		हाल AUDIT_SGID:
		हाल AUDIT_FSGID:
		हाल AUDIT_OBJ_GID:
			अगर (!gid_eq(a->fields[i].gid, b->fields[i].gid))
				वापस 1;
			अवरोध;
		शेष:
			अगर (a->fields[i].val != b->fields[i].val)
				वापस 1;
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < AUDIT_BITMASK_SIZE; i++)
		अगर (a->mask[i] != b->mask[i])
			वापस 1;

	वापस 0;
पूर्ण

/* Duplicate LSM field inक्रमmation.  The lsm_rule is opaque, so must be
 * re-initialized. */
अटल अंतरभूत पूर्णांक audit_dupe_lsm_field(काष्ठा audit_field *df,
					   काष्ठा audit_field *sf)
अणु
	पूर्णांक ret = 0;
	अक्षर *lsm_str;

	/* our own copy of lsm_str */
	lsm_str = kstrdup(sf->lsm_str, GFP_KERNEL);
	अगर (unlikely(!lsm_str))
		वापस -ENOMEM;
	df->lsm_str = lsm_str;

	/* our own (refreshed) copy of lsm_rule */
	ret = security_audit_rule_init(df->type, df->op, df->lsm_str,
				       (व्योम **)&df->lsm_rule);
	/* Keep currently invalid fields around in हाल they
	 * become valid after a policy reload. */
	अगर (ret == -EINVAL) अणु
		pr_warn("audit rule for LSM \'%s\' is invalid\n",
			df->lsm_str);
		ret = 0;
	पूर्ण

	वापस ret;
पूर्ण

/* Duplicate an audit rule.  This will be a deep copy with the exception
 * of the watch - that poपूर्णांकer is carried over.  The LSM specअगरic fields
 * will be updated in the copy.  The poपूर्णांक is to be able to replace the old
 * rule with the new rule in the filterlist, then मुक्त the old rule.
 * The rlist element is undefined; list manipulations are handled apart from
 * the initial copy. */
काष्ठा audit_entry *audit_dupe_rule(काष्ठा audit_krule *old)
अणु
	u32 fcount = old->field_count;
	काष्ठा audit_entry *entry;
	काष्ठा audit_krule *new;
	अक्षर *fk;
	पूर्णांक i, err = 0;

	entry = audit_init_entry(fcount);
	अगर (unlikely(!entry))
		वापस ERR_PTR(-ENOMEM);

	new = &entry->rule;
	new->flags = old->flags;
	new->pflags = old->pflags;
	new->listnr = old->listnr;
	new->action = old->action;
	क्रम (i = 0; i < AUDIT_BITMASK_SIZE; i++)
		new->mask[i] = old->mask[i];
	new->prio = old->prio;
	new->buflen = old->buflen;
	new->inode_f = old->inode_f;
	new->field_count = old->field_count;

	/*
	 * note that we are OK with not refcounting here; audit_match_tree()
	 * never dereferences tree and we can't get false positives there
	 * since we'd have to have rule gone from the list *and* हटाओd
	 * beक्रमe the chunks found by lookup had been allocated, i.e. beक्रमe
	 * the beginning of list scan.
	 */
	new->tree = old->tree;
	स_नकल(new->fields, old->fields, माप(काष्ठा audit_field) * fcount);

	/* deep copy this inक्रमmation, updating the lsm_rule fields, because
	 * the originals will all be मुक्तd when the old rule is मुक्तd. */
	क्रम (i = 0; i < fcount; i++) अणु
		चयन (new->fields[i].type) अणु
		हाल AUDIT_SUBJ_USER:
		हाल AUDIT_SUBJ_ROLE:
		हाल AUDIT_SUBJ_TYPE:
		हाल AUDIT_SUBJ_SEN:
		हाल AUDIT_SUBJ_CLR:
		हाल AUDIT_OBJ_USER:
		हाल AUDIT_OBJ_ROLE:
		हाल AUDIT_OBJ_TYPE:
		हाल AUDIT_OBJ_LEV_LOW:
		हाल AUDIT_OBJ_LEV_HIGH:
			err = audit_dupe_lsm_field(&new->fields[i],
						       &old->fields[i]);
			अवरोध;
		हाल AUDIT_FILTERKEY:
			fk = kstrdup(old->filterkey, GFP_KERNEL);
			अगर (unlikely(!fk))
				err = -ENOMEM;
			अन्यथा
				new->filterkey = fk;
			अवरोध;
		हाल AUDIT_EXE:
			err = audit_dupe_exe(new, old);
			अवरोध;
		पूर्ण
		अगर (err) अणु
			अगर (new->exe)
				audit_हटाओ_mark(new->exe);
			audit_मुक्त_rule(entry);
			वापस ERR_PTR(err);
		पूर्ण
	पूर्ण

	अगर (old->watch) अणु
		audit_get_watch(old->watch);
		new->watch = old->watch;
	पूर्ण

	वापस entry;
पूर्ण

/* Find an existing audit rule.
 * Caller must hold audit_filter_mutex to prevent stale rule data. */
अटल काष्ठा audit_entry *audit_find_rule(काष्ठा audit_entry *entry,
					   काष्ठा list_head **p)
अणु
	काष्ठा audit_entry *e, *found = शून्य;
	काष्ठा list_head *list;
	पूर्णांक h;

	अगर (entry->rule.inode_f) अणु
		h = audit_hash_ino(entry->rule.inode_f->val);
		*p = list = &audit_inode_hash[h];
	पूर्ण अन्यथा अगर (entry->rule.watch) अणु
		/* we करोn't know the inode number, so must walk entire hash */
		क्रम (h = 0; h < AUDIT_INODE_BUCKETS; h++) अणु
			list = &audit_inode_hash[h];
			list_क्रम_each_entry(e, list, list)
				अगर (!audit_compare_rule(&entry->rule, &e->rule)) अणु
					found = e;
					जाओ out;
				पूर्ण
		पूर्ण
		जाओ out;
	पूर्ण अन्यथा अणु
		*p = list = &audit_filter_list[entry->rule.listnr];
	पूर्ण

	list_क्रम_each_entry(e, list, list)
		अगर (!audit_compare_rule(&entry->rule, &e->rule)) अणु
			found = e;
			जाओ out;
		पूर्ण

out:
	वापस found;
पूर्ण

अटल u64 prio_low = ~0ULL/2;
अटल u64 prio_high = ~0ULL/2 - 1;

/* Add rule to given filterlist अगर not a duplicate. */
अटल अंतरभूत पूर्णांक audit_add_rule(काष्ठा audit_entry *entry)
अणु
	काष्ठा audit_entry *e;
	काष्ठा audit_watch *watch = entry->rule.watch;
	काष्ठा audit_tree *tree = entry->rule.tree;
	काष्ठा list_head *list;
	पूर्णांक err = 0;
#अगर_घोषित CONFIG_AUDITSYSCALL
	पूर्णांक करोnt_count = 0;

	/* If any of these, करोn't count towards total */
	चयन(entry->rule.listnr) अणु
	हाल AUDIT_FILTER_USER:
	हाल AUDIT_FILTER_EXCLUDE:
	हाल AUDIT_FILTER_FS:
		करोnt_count = 1;
	पूर्ण
#पूर्ण_अगर

	mutex_lock(&audit_filter_mutex);
	e = audit_find_rule(entry, &list);
	अगर (e) अणु
		mutex_unlock(&audit_filter_mutex);
		err = -EEXIST;
		/* normally audit_add_tree_rule() will मुक्त it on failure */
		अगर (tree)
			audit_put_tree(tree);
		वापस err;
	पूर्ण

	अगर (watch) अणु
		/* audit_filter_mutex is dropped and re-taken during this call */
		err = audit_add_watch(&entry->rule, &list);
		अगर (err) अणु
			mutex_unlock(&audit_filter_mutex);
			/*
			 * normally audit_add_tree_rule() will मुक्त it
			 * on failure
			 */
			अगर (tree)
				audit_put_tree(tree);
			वापस err;
		पूर्ण
	पूर्ण
	अगर (tree) अणु
		err = audit_add_tree_rule(&entry->rule);
		अगर (err) अणु
			mutex_unlock(&audit_filter_mutex);
			वापस err;
		पूर्ण
	पूर्ण

	entry->rule.prio = ~0ULL;
	अगर (entry->rule.listnr == AUDIT_FILTER_EXIT) अणु
		अगर (entry->rule.flags & AUDIT_FILTER_PREPEND)
			entry->rule.prio = ++prio_high;
		अन्यथा
			entry->rule.prio = --prio_low;
	पूर्ण

	अगर (entry->rule.flags & AUDIT_FILTER_PREPEND) अणु
		list_add(&entry->rule.list,
			 &audit_rules_list[entry->rule.listnr]);
		list_add_rcu(&entry->list, list);
		entry->rule.flags &= ~AUDIT_FILTER_PREPEND;
	पूर्ण अन्यथा अणु
		list_add_tail(&entry->rule.list,
			      &audit_rules_list[entry->rule.listnr]);
		list_add_tail_rcu(&entry->list, list);
	पूर्ण
#अगर_घोषित CONFIG_AUDITSYSCALL
	अगर (!करोnt_count)
		audit_n_rules++;

	अगर (!audit_match_संकेत(entry))
		audit_संकेतs++;
#पूर्ण_अगर
	mutex_unlock(&audit_filter_mutex);

	वापस err;
पूर्ण

/* Remove an existing rule from filterlist. */
पूर्णांक audit_del_rule(काष्ठा audit_entry *entry)
अणु
	काष्ठा audit_entry  *e;
	काष्ठा audit_tree *tree = entry->rule.tree;
	काष्ठा list_head *list;
	पूर्णांक ret = 0;
#अगर_घोषित CONFIG_AUDITSYSCALL
	पूर्णांक करोnt_count = 0;

	/* If any of these, करोn't count towards total */
	चयन(entry->rule.listnr) अणु
	हाल AUDIT_FILTER_USER:
	हाल AUDIT_FILTER_EXCLUDE:
	हाल AUDIT_FILTER_FS:
		करोnt_count = 1;
	पूर्ण
#पूर्ण_अगर

	mutex_lock(&audit_filter_mutex);
	e = audit_find_rule(entry, &list);
	अगर (!e) अणु
		ret = -ENOENT;
		जाओ out;
	पूर्ण

	अगर (e->rule.watch)
		audit_हटाओ_watch_rule(&e->rule);

	अगर (e->rule.tree)
		audit_हटाओ_tree_rule(&e->rule);

	अगर (e->rule.exe)
		audit_हटाओ_mark_rule(&e->rule);

#अगर_घोषित CONFIG_AUDITSYSCALL
	अगर (!करोnt_count)
		audit_n_rules--;

	अगर (!audit_match_संकेत(entry))
		audit_संकेतs--;
#पूर्ण_अगर

	list_del_rcu(&e->list);
	list_del(&e->rule.list);
	call_rcu(&e->rcu, audit_मुक्त_rule_rcu);

out:
	mutex_unlock(&audit_filter_mutex);

	अगर (tree)
		audit_put_tree(tree);	/* that's the temporary one */

	वापस ret;
पूर्ण

/* List rules using काष्ठा audit_rule_data. */
अटल व्योम audit_list_rules(पूर्णांक seq, काष्ठा sk_buff_head *q)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा audit_krule *r;
	पूर्णांक i;

	/* This is a blocking पढ़ो, so use audit_filter_mutex instead of rcu
	 * iterator to sync with list ग_लिखोrs. */
	क्रम (i=0; i<AUDIT_NR_FILTERS; i++) अणु
		list_क्रम_each_entry(r, &audit_rules_list[i], list) अणु
			काष्ठा audit_rule_data *data;

			data = audit_krule_to_data(r);
			अगर (unlikely(!data))
				अवरोध;
			skb = audit_make_reply(seq, AUDIT_LIST_RULES, 0, 1,
					       data,
					       माप(*data) + data->buflen);
			अगर (skb)
				skb_queue_tail(q, skb);
			kमुक्त(data);
		पूर्ण
	पूर्ण
	skb = audit_make_reply(seq, AUDIT_LIST_RULES, 1, 1, शून्य, 0);
	अगर (skb)
		skb_queue_tail(q, skb);
पूर्ण

/* Log rule additions and removals */
अटल व्योम audit_log_rule_change(अक्षर *action, काष्ठा audit_krule *rule, पूर्णांक res)
अणु
	काष्ठा audit_buffer *ab;

	अगर (!audit_enabled)
		वापस;

	ab = audit_log_start(audit_context(), GFP_KERNEL, AUDIT_CONFIG_CHANGE);
	अगर (!ab)
		वापस;
	audit_log_session_info(ab);
	audit_log_task_context(ab);
	audit_log_क्रमmat(ab, " op=%s", action);
	audit_log_key(ab, rule->filterkey);
	audit_log_क्रमmat(ab, " list=%d res=%d", rule->listnr, res);
	audit_log_end(ab);
पूर्ण

/**
 * audit_rule_change - apply all rules to the specअगरied message type
 * @type: audit message type
 * @seq: netlink audit message sequence (serial) number
 * @data: payload data
 * @datasz: size of payload data
 */
पूर्णांक audit_rule_change(पूर्णांक type, पूर्णांक seq, व्योम *data, माप_प्रकार datasz)
अणु
	पूर्णांक err = 0;
	काष्ठा audit_entry *entry;

	चयन (type) अणु
	हाल AUDIT_ADD_RULE:
		entry = audit_data_to_entry(data, datasz);
		अगर (IS_ERR(entry))
			वापस PTR_ERR(entry);
		err = audit_add_rule(entry);
		audit_log_rule_change("add_rule", &entry->rule, !err);
		अवरोध;
	हाल AUDIT_DEL_RULE:
		entry = audit_data_to_entry(data, datasz);
		अगर (IS_ERR(entry))
			वापस PTR_ERR(entry);
		err = audit_del_rule(entry);
		audit_log_rule_change("remove_rule", &entry->rule, !err);
		अवरोध;
	शेष:
		WARN_ON(1);
		वापस -EINVAL;
	पूर्ण

	अगर (err || type == AUDIT_DEL_RULE) अणु
		अगर (entry->rule.exe)
			audit_हटाओ_mark(entry->rule.exe);
		audit_मुक्त_rule(entry);
	पूर्ण

	वापस err;
पूर्ण

/**
 * audit_list_rules_send - list the audit rules
 * @request_skb: skb of request we are replying to (used to target the reply)
 * @seq: netlink audit message sequence (serial) number
 */
पूर्णांक audit_list_rules_send(काष्ठा sk_buff *request_skb, पूर्णांक seq)
अणु
	काष्ठा task_काष्ठा *tsk;
	काष्ठा audit_netlink_list *dest;

	/* We can't just spew out the rules here because we might fill
	 * the available socket buffer space and deadlock रुकोing क्रम
	 * auditctl to पढ़ो from it... which isn't ever going to
	 * happen अगर we're actually running in the context of auditctl
	 * trying to _send_ the stuff */

	dest = kदो_स्मृति(माप(*dest), GFP_KERNEL);
	अगर (!dest)
		वापस -ENOMEM;
	dest->net = get_net(sock_net(NETLINK_CB(request_skb).sk));
	dest->portid = NETLINK_CB(request_skb).portid;
	skb_queue_head_init(&dest->q);

	mutex_lock(&audit_filter_mutex);
	audit_list_rules(seq, &dest->q);
	mutex_unlock(&audit_filter_mutex);

	tsk = kthपढ़ो_run(audit_send_list_thपढ़ो, dest, "audit_send_list");
	अगर (IS_ERR(tsk)) अणु
		skb_queue_purge(&dest->q);
		put_net(dest->net);
		kमुक्त(dest);
		वापस PTR_ERR(tsk);
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक audit_comparator(u32 left, u32 op, u32 right)
अणु
	चयन (op) अणु
	हाल Audit_equal:
		वापस (left == right);
	हाल Audit_not_equal:
		वापस (left != right);
	हाल Audit_lt:
		वापस (left < right);
	हाल Audit_le:
		वापस (left <= right);
	हाल Audit_gt:
		वापस (left > right);
	हाल Audit_ge:
		वापस (left >= right);
	हाल Audit_biपंचांगask:
		वापस (left & right);
	हाल Audit_bittest:
		वापस ((left & right) == right);
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

पूर्णांक audit_uid_comparator(kuid_t left, u32 op, kuid_t right)
अणु
	चयन (op) अणु
	हाल Audit_equal:
		वापस uid_eq(left, right);
	हाल Audit_not_equal:
		वापस !uid_eq(left, right);
	हाल Audit_lt:
		वापस uid_lt(left, right);
	हाल Audit_le:
		वापस uid_lte(left, right);
	हाल Audit_gt:
		वापस uid_gt(left, right);
	हाल Audit_ge:
		वापस uid_gte(left, right);
	हाल Audit_biपंचांगask:
	हाल Audit_bittest:
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

पूर्णांक audit_gid_comparator(kgid_t left, u32 op, kgid_t right)
अणु
	चयन (op) अणु
	हाल Audit_equal:
		वापस gid_eq(left, right);
	हाल Audit_not_equal:
		वापस !gid_eq(left, right);
	हाल Audit_lt:
		वापस gid_lt(left, right);
	हाल Audit_le:
		वापस gid_lte(left, right);
	हाल Audit_gt:
		वापस gid_gt(left, right);
	हाल Audit_ge:
		वापस gid_gte(left, right);
	हाल Audit_biपंचांगask:
	हाल Audit_bittest:
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

/**
 * parent_len - find the length of the parent portion of a pathname
 * @path: pathname of which to determine length
 */
पूर्णांक parent_len(स्थिर अक्षर *path)
अणु
	पूर्णांक plen;
	स्थिर अक्षर *p;

	plen = म_माप(path);

	अगर (plen == 0)
		वापस plen;

	/* disregard trailing slashes */
	p = path + plen - 1;
	जबतक ((*p == '/') && (p > path))
		p--;

	/* walk backward until we find the next slash or hit beginning */
	जबतक ((*p != '/') && (p > path))
		p--;

	/* did we find a slash? Then increment to include it in path */
	अगर (*p == '/')
		p++;

	वापस p - path;
पूर्ण

/**
 * audit_compare_dname_path - compare given dentry name with last component in
 * 			      given path. Return of 0 indicates a match.
 * @dname:	dentry name that we're comparing
 * @path:	full pathname that we're comparing
 * @parentlen:	length of the parent अगर known. Passing in AUDIT_NAME_FULL
 * 		here indicates that we must compute this value.
 */
पूर्णांक audit_compare_dname_path(स्थिर काष्ठा qstr *dname, स्थिर अक्षर *path, पूर्णांक parentlen)
अणु
	पूर्णांक dlen, pathlen;
	स्थिर अक्षर *p;

	dlen = dname->len;
	pathlen = म_माप(path);
	अगर (pathlen < dlen)
		वापस 1;

	parentlen = parentlen == AUDIT_NAME_FULL ? parent_len(path) : parentlen;
	अगर (pathlen - parentlen != dlen)
		वापस 1;

	p = path + parentlen;

	वापस म_भेदन(p, dname->name, dlen);
पूर्ण

पूर्णांक audit_filter(पूर्णांक msgtype, अचिन्हित पूर्णांक listtype)
अणु
	काष्ठा audit_entry *e;
	पूर्णांक ret = 1; /* Audit by शेष */

	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(e, &audit_filter_list[listtype], list) अणु
		पूर्णांक i, result = 0;

		क्रम (i = 0; i < e->rule.field_count; i++) अणु
			काष्ठा audit_field *f = &e->rule.fields[i];
			pid_t pid;
			u32 sid;

			चयन (f->type) अणु
			हाल AUDIT_PID:
				pid = task_pid_nr(current);
				result = audit_comparator(pid, f->op, f->val);
				अवरोध;
			हाल AUDIT_UID:
				result = audit_uid_comparator(current_uid(), f->op, f->uid);
				अवरोध;
			हाल AUDIT_GID:
				result = audit_gid_comparator(current_gid(), f->op, f->gid);
				अवरोध;
			हाल AUDIT_LOGINUID:
				result = audit_uid_comparator(audit_get_loginuid(current),
							      f->op, f->uid);
				अवरोध;
			हाल AUDIT_LOGINUID_SET:
				result = audit_comparator(audit_loginuid_set(current),
							  f->op, f->val);
				अवरोध;
			हाल AUDIT_MSGTYPE:
				result = audit_comparator(msgtype, f->op, f->val);
				अवरोध;
			हाल AUDIT_SUBJ_USER:
			हाल AUDIT_SUBJ_ROLE:
			हाल AUDIT_SUBJ_TYPE:
			हाल AUDIT_SUBJ_SEN:
			हाल AUDIT_SUBJ_CLR:
				अगर (f->lsm_rule) अणु
					security_task_माला_लोecid_subj(current,
								    &sid);
					result = security_audit_rule_match(sid,
						   f->type, f->op, f->lsm_rule);
				पूर्ण
				अवरोध;
			हाल AUDIT_EXE:
				result = audit_exe_compare(current, e->rule.exe);
				अगर (f->op == Audit_not_equal)
					result = !result;
				अवरोध;
			शेष:
				जाओ unlock_and_वापस;
			पूर्ण
			अगर (result < 0) /* error */
				जाओ unlock_and_वापस;
			अगर (!result)
				अवरोध;
		पूर्ण
		अगर (result > 0) अणु
			अगर (e->rule.action == AUDIT_NEVER || listtype == AUDIT_FILTER_EXCLUDE)
				ret = 0;
			अवरोध;
		पूर्ण
	पूर्ण
unlock_and_वापस:
	rcu_पढ़ो_unlock();
	वापस ret;
पूर्ण

अटल पूर्णांक update_lsm_rule(काष्ठा audit_krule *r)
अणु
	काष्ठा audit_entry *entry = container_of(r, काष्ठा audit_entry, rule);
	काष्ठा audit_entry *nentry;
	पूर्णांक err = 0;

	अगर (!security_audit_rule_known(r))
		वापस 0;

	nentry = audit_dupe_rule(r);
	अगर (entry->rule.exe)
		audit_हटाओ_mark(entry->rule.exe);
	अगर (IS_ERR(nentry)) अणु
		/* save the first error encountered क्रम the
		 * वापस value */
		err = PTR_ERR(nentry);
		audit_panic("error updating LSM filters");
		अगर (r->watch)
			list_del(&r->rlist);
		list_del_rcu(&entry->list);
		list_del(&r->list);
	पूर्ण अन्यथा अणु
		अगर (r->watch || r->tree)
			list_replace_init(&r->rlist, &nentry->rule.rlist);
		list_replace_rcu(&entry->list, &nentry->list);
		list_replace(&r->list, &nentry->rule.list);
	पूर्ण
	call_rcu(&entry->rcu, audit_मुक्त_rule_rcu);

	वापस err;
पूर्ण

/* This function will re-initialize the lsm_rule field of all applicable rules.
 * It will traverse the filter lists serarching क्रम rules that contain LSM
 * specअगरic filter fields.  When such a rule is found, it is copied, the
 * LSM field is re-initialized, and the old rule is replaced with the
 * updated rule. */
पूर्णांक audit_update_lsm_rules(व्योम)
अणु
	काष्ठा audit_krule *r, *n;
	पूर्णांक i, err = 0;

	/* audit_filter_mutex synchronizes the ग_लिखोrs */
	mutex_lock(&audit_filter_mutex);

	क्रम (i = 0; i < AUDIT_NR_FILTERS; i++) अणु
		list_क्रम_each_entry_safe(r, n, &audit_rules_list[i], list) अणु
			पूर्णांक res = update_lsm_rule(r);
			अगर (!err)
				err = res;
		पूर्ण
	पूर्ण
	mutex_unlock(&audit_filter_mutex);

	वापस err;
पूर्ण
