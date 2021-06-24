<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2008 IBM Corporation
 * Author: Mimi Zohar <zohar@us.ibm.com>
 *
 * ima_policy.c
 *	- initialize शेष measure policy rules
 */

#समावेश <linux/init.h>
#समावेश <linux/list.h>
#समावेश <linux/kernel_पढ़ो_file.h>
#समावेश <linux/fs.h>
#समावेश <linux/security.h>
#समावेश <linux/magic.h>
#समावेश <linux/parser.h>
#समावेश <linux/slab.h>
#समावेश <linux/rculist.h>
#समावेश <linux/genhd.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/ima.h>

#समावेश "ima.h"

/* flags definitions */
#घोषणा IMA_FUNC	0x0001
#घोषणा IMA_MASK	0x0002
#घोषणा IMA_FSMAGIC	0x0004
#घोषणा IMA_UID		0x0008
#घोषणा IMA_FOWNER	0x0010
#घोषणा IMA_FSUUID	0x0020
#घोषणा IMA_INMASK	0x0040
#घोषणा IMA_EUID	0x0080
#घोषणा IMA_PCR		0x0100
#घोषणा IMA_FSNAME	0x0200
#घोषणा IMA_KEYRINGS	0x0400
#घोषणा IMA_LABEL	0x0800

#घोषणा UNKNOWN		0
#घोषणा MEASURE		0x0001	/* same as IMA_MEASURE */
#घोषणा DONT_MEASURE	0x0002
#घोषणा APPRAISE	0x0004	/* same as IMA_APPRAISE */
#घोषणा DONT_APPRAISE	0x0008
#घोषणा AUDIT		0x0040
#घोषणा HASH		0x0100
#घोषणा DONT_HASH	0x0200

#घोषणा INVALID_PCR(a) (((a) < 0) || \
	(a) >= (माप_field(काष्ठा पूर्णांकegrity_iपूर्णांक_cache, measured_pcrs) * 8))

पूर्णांक ima_policy_flag;
अटल पूर्णांक temp_ima_appउठाओ;
अटल पूर्णांक build_ima_appउठाओ __ro_after_init;

#घोषणा MAX_LSM_RULES 6
क्रमागत lsm_rule_types अणु LSM_OBJ_USER, LSM_OBJ_ROLE, LSM_OBJ_TYPE,
	LSM_SUBJ_USER, LSM_SUBJ_ROLE, LSM_SUBJ_TYPE
पूर्ण;

क्रमागत policy_types अणु ORIGINAL_TCB = 1, DEFAULT_TCB पूर्ण;

क्रमागत policy_rule_list अणु IMA_DEFAULT_POLICY = 1, IMA_CUSTOM_POLICY पूर्ण;

काष्ठा ima_rule_opt_list अणु
	माप_प्रकार count;
	अक्षर *items[];
पूर्ण;

काष्ठा ima_rule_entry अणु
	काष्ठा list_head list;
	पूर्णांक action;
	अचिन्हित पूर्णांक flags;
	क्रमागत ima_hooks func;
	पूर्णांक mask;
	अचिन्हित दीर्घ fsmagic;
	uuid_t fsuuid;
	kuid_t uid;
	kuid_t fowner;
	bool (*uid_op)(kuid_t, kuid_t);    /* Handlers क्रम चालकs       */
	bool (*fowner_op)(kuid_t, kuid_t); /* uid_eq(), uid_gt(), uid_lt() */
	पूर्णांक pcr;
	काष्ठा अणु
		व्योम *rule;	/* LSM file metadata specअगरic */
		अक्षर *args_p;	/* audit value */
		पूर्णांक type;	/* audit type */
	पूर्ण lsm[MAX_LSM_RULES];
	अक्षर *fsname;
	काष्ठा ima_rule_opt_list *keyrings; /* Measure keys added to these keyrings */
	काष्ठा ima_rule_opt_list *label; /* Measure data grouped under this label */
	काष्ठा ima_ढाँचा_desc *ढाँचा;
पूर्ण;

/*
 * Without LSM specअगरic knowledge, the शेष policy can only be
 * written in terms of .action, .func, .mask, .fsmagic, .uid, and .fowner
 */

/*
 * The minimum rule set to allow क्रम full TCB coverage.  Measures all files
 * खोलोed or mmap क्रम exec and everything पढ़ो by root.  Dangerous because
 * normal users can easily run the machine out of memory simply building
 * and running executables.
 */
अटल काष्ठा ima_rule_entry करोnt_measure_rules[] __ro_after_init = अणु
	अणु.action = DONT_MEASURE, .fsmagic = PROC_SUPER_MAGIC, .flags = IMA_FSMAGICपूर्ण,
	अणु.action = DONT_MEASURE, .fsmagic = SYSFS_MAGIC, .flags = IMA_FSMAGICपूर्ण,
	अणु.action = DONT_MEASURE, .fsmagic = DEBUGFS_MAGIC, .flags = IMA_FSMAGICपूर्ण,
	अणु.action = DONT_MEASURE, .fsmagic = TMPFS_MAGIC, .flags = IMA_FSMAGICपूर्ण,
	अणु.action = DONT_MEASURE, .fsmagic = DEVPTS_SUPER_MAGIC, .flags = IMA_FSMAGICपूर्ण,
	अणु.action = DONT_MEASURE, .fsmagic = BINFMTFS_MAGIC, .flags = IMA_FSMAGICपूर्ण,
	अणु.action = DONT_MEASURE, .fsmagic = SECURITYFS_MAGIC, .flags = IMA_FSMAGICपूर्ण,
	अणु.action = DONT_MEASURE, .fsmagic = SELINUX_MAGIC, .flags = IMA_FSMAGICपूर्ण,
	अणु.action = DONT_MEASURE, .fsmagic = SMACK_MAGIC, .flags = IMA_FSMAGICपूर्ण,
	अणु.action = DONT_MEASURE, .fsmagic = CGROUP_SUPER_MAGIC,
	 .flags = IMA_FSMAGICपूर्ण,
	अणु.action = DONT_MEASURE, .fsmagic = CGROUP2_SUPER_MAGIC,
	 .flags = IMA_FSMAGICपूर्ण,
	अणु.action = DONT_MEASURE, .fsmagic = NSFS_MAGIC, .flags = IMA_FSMAGICपूर्ण,
	अणु.action = DONT_MEASURE, .fsmagic = EFIVARFS_MAGIC, .flags = IMA_FSMAGICपूर्ण
पूर्ण;

अटल काष्ठा ima_rule_entry original_measurement_rules[] __ro_after_init = अणु
	अणु.action = MEASURE, .func = MMAP_CHECK, .mask = MAY_EXEC,
	 .flags = IMA_FUNC | IMA_MASKपूर्ण,
	अणु.action = MEASURE, .func = BPRM_CHECK, .mask = MAY_EXEC,
	 .flags = IMA_FUNC | IMA_MASKपूर्ण,
	अणु.action = MEASURE, .func = खाता_CHECK, .mask = MAY_READ,
	 .uid = GLOBAL_ROOT_UID, .uid_op = &uid_eq,
	 .flags = IMA_FUNC | IMA_MASK | IMA_UIDपूर्ण,
	अणु.action = MEASURE, .func = MODULE_CHECK, .flags = IMA_FUNCपूर्ण,
	अणु.action = MEASURE, .func = FIRMWARE_CHECK, .flags = IMA_FUNCपूर्ण,
पूर्ण;

अटल काष्ठा ima_rule_entry शेष_measurement_rules[] __ro_after_init = अणु
	अणु.action = MEASURE, .func = MMAP_CHECK, .mask = MAY_EXEC,
	 .flags = IMA_FUNC | IMA_MASKपूर्ण,
	अणु.action = MEASURE, .func = BPRM_CHECK, .mask = MAY_EXEC,
	 .flags = IMA_FUNC | IMA_MASKपूर्ण,
	अणु.action = MEASURE, .func = खाता_CHECK, .mask = MAY_READ,
	 .uid = GLOBAL_ROOT_UID, .uid_op = &uid_eq,
	 .flags = IMA_FUNC | IMA_INMASK | IMA_EUIDपूर्ण,
	अणु.action = MEASURE, .func = खाता_CHECK, .mask = MAY_READ,
	 .uid = GLOBAL_ROOT_UID, .uid_op = &uid_eq,
	 .flags = IMA_FUNC | IMA_INMASK | IMA_UIDपूर्ण,
	अणु.action = MEASURE, .func = MODULE_CHECK, .flags = IMA_FUNCपूर्ण,
	अणु.action = MEASURE, .func = FIRMWARE_CHECK, .flags = IMA_FUNCपूर्ण,
	अणु.action = MEASURE, .func = POLICY_CHECK, .flags = IMA_FUNCपूर्ण,
पूर्ण;

अटल काष्ठा ima_rule_entry शेष_appउठाओ_rules[] __ro_after_init = अणु
	अणु.action = DONT_APPRAISE, .fsmagic = PROC_SUPER_MAGIC, .flags = IMA_FSMAGICपूर्ण,
	अणु.action = DONT_APPRAISE, .fsmagic = SYSFS_MAGIC, .flags = IMA_FSMAGICपूर्ण,
	अणु.action = DONT_APPRAISE, .fsmagic = DEBUGFS_MAGIC, .flags = IMA_FSMAGICपूर्ण,
	अणु.action = DONT_APPRAISE, .fsmagic = TMPFS_MAGIC, .flags = IMA_FSMAGICपूर्ण,
	अणु.action = DONT_APPRAISE, .fsmagic = RAMFS_MAGIC, .flags = IMA_FSMAGICपूर्ण,
	अणु.action = DONT_APPRAISE, .fsmagic = DEVPTS_SUPER_MAGIC, .flags = IMA_FSMAGICपूर्ण,
	अणु.action = DONT_APPRAISE, .fsmagic = BINFMTFS_MAGIC, .flags = IMA_FSMAGICपूर्ण,
	अणु.action = DONT_APPRAISE, .fsmagic = SECURITYFS_MAGIC, .flags = IMA_FSMAGICपूर्ण,
	अणु.action = DONT_APPRAISE, .fsmagic = SELINUX_MAGIC, .flags = IMA_FSMAGICपूर्ण,
	अणु.action = DONT_APPRAISE, .fsmagic = SMACK_MAGIC, .flags = IMA_FSMAGICपूर्ण,
	अणु.action = DONT_APPRAISE, .fsmagic = NSFS_MAGIC, .flags = IMA_FSMAGICपूर्ण,
	अणु.action = DONT_APPRAISE, .fsmagic = EFIVARFS_MAGIC, .flags = IMA_FSMAGICपूर्ण,
	अणु.action = DONT_APPRAISE, .fsmagic = CGROUP_SUPER_MAGIC, .flags = IMA_FSMAGICपूर्ण,
	अणु.action = DONT_APPRAISE, .fsmagic = CGROUP2_SUPER_MAGIC, .flags = IMA_FSMAGICपूर्ण,
#अगर_घोषित CONFIG_IMA_WRITE_POLICY
	अणु.action = APPRAISE, .func = POLICY_CHECK,
	.flags = IMA_FUNC | IMA_DIGSIG_REQUIREDपूर्ण,
#पूर्ण_अगर
#अगर_अघोषित CONFIG_IMA_APPRAISE_SIGNED_INIT
	अणु.action = APPRAISE, .fowner = GLOBAL_ROOT_UID, .fowner_op = &uid_eq,
	 .flags = IMA_FOWNERपूर्ण,
#अन्यथा
	/* क्रमce signature */
	अणु.action = APPRAISE, .fowner = GLOBAL_ROOT_UID, .fowner_op = &uid_eq,
	 .flags = IMA_FOWNER | IMA_DIGSIG_REQUIREDपूर्ण,
#पूर्ण_अगर
पूर्ण;

अटल काष्ठा ima_rule_entry build_appउठाओ_rules[] __ro_after_init = अणु
#अगर_घोषित CONFIG_IMA_APPRAISE_REQUIRE_MODULE_SIGS
	अणु.action = APPRAISE, .func = MODULE_CHECK,
	 .flags = IMA_FUNC | IMA_DIGSIG_REQUIREDपूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_IMA_APPRAISE_REQUIRE_FIRMWARE_SIGS
	अणु.action = APPRAISE, .func = FIRMWARE_CHECK,
	 .flags = IMA_FUNC | IMA_DIGSIG_REQUIREDपूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_IMA_APPRAISE_REQUIRE_KEXEC_SIGS
	अणु.action = APPRAISE, .func = KEXEC_KERNEL_CHECK,
	 .flags = IMA_FUNC | IMA_DIGSIG_REQUIREDपूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_IMA_APPRAISE_REQUIRE_POLICY_SIGS
	अणु.action = APPRAISE, .func = POLICY_CHECK,
	 .flags = IMA_FUNC | IMA_DIGSIG_REQUIREDपूर्ण,
#पूर्ण_अगर
पूर्ण;

अटल काष्ठा ima_rule_entry secure_boot_rules[] __ro_after_init = अणु
	अणु.action = APPRAISE, .func = MODULE_CHECK,
	 .flags = IMA_FUNC | IMA_DIGSIG_REQUIREDपूर्ण,
	अणु.action = APPRAISE, .func = FIRMWARE_CHECK,
	 .flags = IMA_FUNC | IMA_DIGSIG_REQUIREDपूर्ण,
	अणु.action = APPRAISE, .func = KEXEC_KERNEL_CHECK,
	 .flags = IMA_FUNC | IMA_DIGSIG_REQUIREDपूर्ण,
	अणु.action = APPRAISE, .func = POLICY_CHECK,
	 .flags = IMA_FUNC | IMA_DIGSIG_REQUIREDपूर्ण,
पूर्ण;

अटल काष्ठा ima_rule_entry critical_data_rules[] __ro_after_init = अणु
	अणु.action = MEASURE, .func = CRITICAL_DATA, .flags = IMA_FUNCपूर्ण,
पूर्ण;

/* An array of architecture specअगरic rules */
अटल काष्ठा ima_rule_entry *arch_policy_entry __ro_after_init;

अटल LIST_HEAD(ima_शेष_rules);
अटल LIST_HEAD(ima_policy_rules);
अटल LIST_HEAD(ima_temp_rules);
अटल काष्ठा list_head *ima_rules = &ima_शेष_rules;

अटल पूर्णांक ima_policy __initdata;

अटल पूर्णांक __init शेष_measure_policy_setup(अक्षर *str)
अणु
	अगर (ima_policy)
		वापस 1;

	ima_policy = ORIGINAL_TCB;
	वापस 1;
पूर्ण
__setup("ima_tcb", शेष_measure_policy_setup);

अटल bool ima_use_appउठाओ_tcb __initdata;
अटल bool ima_use_secure_boot __initdata;
अटल bool ima_use_critical_data __initdata;
अटल bool ima_fail_unverअगरiable_sigs __ro_after_init;
अटल पूर्णांक __init policy_setup(अक्षर *str)
अणु
	अक्षर *p;

	जबतक ((p = strsep(&str, " |\n")) != शून्य) अणु
		अगर (*p == ' ')
			जारी;
		अगर ((म_भेद(p, "tcb") == 0) && !ima_policy)
			ima_policy = DEFAULT_TCB;
		अन्यथा अगर (म_भेद(p, "appraise_tcb") == 0)
			ima_use_appउठाओ_tcb = true;
		अन्यथा अगर (म_भेद(p, "secure_boot") == 0)
			ima_use_secure_boot = true;
		अन्यथा अगर (म_भेद(p, "critical_data") == 0)
			ima_use_critical_data = true;
		अन्यथा अगर (म_भेद(p, "fail_securely") == 0)
			ima_fail_unverअगरiable_sigs = true;
		अन्यथा
			pr_err("policy \"%s\" not found", p);
	पूर्ण

	वापस 1;
पूर्ण
__setup("ima_policy=", policy_setup);

अटल पूर्णांक __init शेष_appउठाओ_policy_setup(अक्षर *str)
अणु
	ima_use_appउठाओ_tcb = true;
	वापस 1;
पूर्ण
__setup("ima_appraise_tcb", शेष_appउठाओ_policy_setup);

अटल काष्ठा ima_rule_opt_list *ima_alloc_rule_opt_list(स्थिर substring_t *src)
अणु
	काष्ठा ima_rule_opt_list *opt_list;
	माप_प्रकार count = 0;
	अक्षर *src_copy;
	अक्षर *cur, *next;
	माप_प्रकार i;

	src_copy = match_strdup(src);
	अगर (!src_copy)
		वापस ERR_PTR(-ENOMEM);

	next = src_copy;
	जबतक ((cur = strsep(&next, "|"))) अणु
		/* Don't accept an empty list item */
		अगर (!(*cur)) अणु
			kमुक्त(src_copy);
			वापस ERR_PTR(-EINVAL);
		पूर्ण
		count++;
	पूर्ण

	/* Don't accept an empty list */
	अगर (!count) अणु
		kमुक्त(src_copy);
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	opt_list = kzalloc(काष्ठा_size(opt_list, items, count), GFP_KERNEL);
	अगर (!opt_list) अणु
		kमुक्त(src_copy);
		वापस ERR_PTR(-ENOMEM);
	पूर्ण

	/*
	 * strsep() has alपढ़ोy replaced all instances of '|' with '\0',
	 * leaving a byte sequence of NUL-terminated strings. Reference each
	 * string with the array of items.
	 *
	 * IMPORTANT: Ownership of the allocated buffer is transferred from
	 * src_copy to the first element in the items array. To मुक्त the
	 * buffer, kमुक्त() must only be called on the first element of the
	 * array.
	 */
	क्रम (i = 0, cur = src_copy; i < count; i++) अणु
		opt_list->items[i] = cur;
		cur = म_अक्षर(cur, '\0') + 1;
	पूर्ण
	opt_list->count = count;

	वापस opt_list;
पूर्ण

अटल व्योम ima_मुक्त_rule_opt_list(काष्ठा ima_rule_opt_list *opt_list)
अणु
	अगर (!opt_list)
		वापस;

	अगर (opt_list->count) अणु
		kमुक्त(opt_list->items[0]);
		opt_list->count = 0;
	पूर्ण

	kमुक्त(opt_list);
पूर्ण

अटल व्योम ima_lsm_मुक्त_rule(काष्ठा ima_rule_entry *entry)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < MAX_LSM_RULES; i++) अणु
		ima_filter_rule_मुक्त(entry->lsm[i].rule);
		kमुक्त(entry->lsm[i].args_p);
	पूर्ण
पूर्ण

अटल व्योम ima_मुक्त_rule(काष्ठा ima_rule_entry *entry)
अणु
	अगर (!entry)
		वापस;

	/*
	 * entry->ढाँचा->fields may be allocated in ima_parse_rule() but that
	 * reference is owned by the corresponding ima_ढाँचा_desc element in
	 * the defined_ढाँचाs list and cannot be मुक्तd here
	 */
	kमुक्त(entry->fsname);
	ima_मुक्त_rule_opt_list(entry->keyrings);
	ima_lsm_मुक्त_rule(entry);
	kमुक्त(entry);
पूर्ण

अटल काष्ठा ima_rule_entry *ima_lsm_copy_rule(काष्ठा ima_rule_entry *entry)
अणु
	काष्ठा ima_rule_entry *nentry;
	पूर्णांक i;

	/*
	 * Immutable elements are copied over as poपूर्णांकers and data; only
	 * lsm rules can change
	 */
	nentry = kmemdup(entry, माप(*nentry), GFP_KERNEL);
	अगर (!nentry)
		वापस शून्य;

	स_रखो(nentry->lsm, 0, माप_field(काष्ठा ima_rule_entry, lsm));

	क्रम (i = 0; i < MAX_LSM_RULES; i++) अणु
		अगर (!entry->lsm[i].args_p)
			जारी;

		nentry->lsm[i].type = entry->lsm[i].type;
		nentry->lsm[i].args_p = entry->lsm[i].args_p;
		/*
		 * Remove the reference from entry so that the associated
		 * memory will not be मुक्तd during a later call to
		 * ima_lsm_मुक्त_rule(entry).
		 */
		entry->lsm[i].args_p = शून्य;

		ima_filter_rule_init(nentry->lsm[i].type, Audit_equal,
				     nentry->lsm[i].args_p,
				     &nentry->lsm[i].rule);
		अगर (!nentry->lsm[i].rule)
			pr_warn("rule for LSM \'%s\' is undefined\n",
				nentry->lsm[i].args_p);
	पूर्ण
	वापस nentry;
पूर्ण

अटल पूर्णांक ima_lsm_update_rule(काष्ठा ima_rule_entry *entry)
अणु
	काष्ठा ima_rule_entry *nentry;

	nentry = ima_lsm_copy_rule(entry);
	अगर (!nentry)
		वापस -ENOMEM;

	list_replace_rcu(&entry->list, &nentry->list);
	synchronize_rcu();
	/*
	 * ima_lsm_copy_rule() shallow copied all references, except क्रम the
	 * LSM references, from entry to nentry so we only want to मुक्त the LSM
	 * references and the entry itself. All other memory refrences will now
	 * be owned by nentry.
	 */
	ima_lsm_मुक्त_rule(entry);
	kमुक्त(entry);

	वापस 0;
पूर्ण

अटल bool ima_rule_contains_lsm_cond(काष्ठा ima_rule_entry *entry)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < MAX_LSM_RULES; i++)
		अगर (entry->lsm[i].args_p)
			वापस true;

	वापस false;
पूर्ण

/*
 * The LSM policy can be reloaded, leaving the IMA LSM based rules referring
 * to the old, stale LSM policy.  Update the IMA LSM based rules to reflect
 * the reloaded LSM policy.
 */
अटल व्योम ima_lsm_update_rules(व्योम)
अणु
	काष्ठा ima_rule_entry *entry, *e;
	पूर्णांक result;

	list_क्रम_each_entry_safe(entry, e, &ima_policy_rules, list) अणु
		अगर (!ima_rule_contains_lsm_cond(entry))
			जारी;

		result = ima_lsm_update_rule(entry);
		अगर (result) अणु
			pr_err("lsm rule update error %d\n", result);
			वापस;
		पूर्ण
	पूर्ण
पूर्ण

पूर्णांक ima_lsm_policy_change(काष्ठा notअगरier_block *nb, अचिन्हित दीर्घ event,
			  व्योम *lsm_data)
अणु
	अगर (event != LSM_POLICY_CHANGE)
		वापस NOTIFY_DONE;

	ima_lsm_update_rules();
	वापस NOTIFY_OK;
पूर्ण

/**
 * ima_match_rule_data - determine whether func_data matches the policy rule
 * @rule: a poपूर्णांकer to a rule
 * @func_data: data to match against the measure rule data
 * @cred: a poपूर्णांकer to a credentials काष्ठाure क्रम user validation
 *
 * Returns true अगर func_data matches one in the rule, false otherwise.
 */
अटल bool ima_match_rule_data(काष्ठा ima_rule_entry *rule,
				स्थिर अक्षर *func_data,
				स्थिर काष्ठा cred *cred)
अणु
	स्थिर काष्ठा ima_rule_opt_list *opt_list = शून्य;
	bool matched = false;
	माप_प्रकार i;

	अगर ((rule->flags & IMA_UID) && !rule->uid_op(cred->uid, rule->uid))
		वापस false;

	चयन (rule->func) अणु
	हाल KEY_CHECK:
		अगर (!rule->keyrings)
			वापस true;

		opt_list = rule->keyrings;
		अवरोध;
	हाल CRITICAL_DATA:
		अगर (!rule->label)
			वापस true;

		opt_list = rule->label;
		अवरोध;
	शेष:
		वापस false;
	पूर्ण

	अगर (!func_data)
		वापस false;

	क्रम (i = 0; i < opt_list->count; i++) अणु
		अगर (!म_भेद(opt_list->items[i], func_data)) अणु
			matched = true;
			अवरोध;
		पूर्ण
	पूर्ण

	वापस matched;
पूर्ण

/**
 * ima_match_rules - determine whether an inode matches the policy rule.
 * @rule: a poपूर्णांकer to a rule
 * @mnt_userns:	user namespace of the mount the inode was found from
 * @inode: a poपूर्णांकer to an inode
 * @cred: a poपूर्णांकer to a credentials काष्ठाure क्रम user validation
 * @secid: the secid of the task to be validated
 * @func: LIM hook identअगरier
 * @mask: requested action (MAY_READ | MAY_WRITE | MAY_APPEND | MAY_EXEC)
 * @func_data: func specअगरic data, may be शून्य
 *
 * Returns true on rule match, false on failure.
 */
अटल bool ima_match_rules(काष्ठा ima_rule_entry *rule,
			    काष्ठा user_namespace *mnt_userns,
			    काष्ठा inode *inode, स्थिर काष्ठा cred *cred,
			    u32 secid, क्रमागत ima_hooks func, पूर्णांक mask,
			    स्थिर अक्षर *func_data)
अणु
	पूर्णांक i;

	अगर ((rule->flags & IMA_FUNC) &&
	    (rule->func != func && func != POST_SETATTR))
		वापस false;

	चयन (func) अणु
	हाल KEY_CHECK:
	हाल CRITICAL_DATA:
		वापस ((rule->func == func) &&
			ima_match_rule_data(rule, func_data, cred));
	शेष:
		अवरोध;
	पूर्ण

	अगर ((rule->flags & IMA_MASK) &&
	    (rule->mask != mask && func != POST_SETATTR))
		वापस false;
	अगर ((rule->flags & IMA_INMASK) &&
	    (!(rule->mask & mask) && func != POST_SETATTR))
		वापस false;
	अगर ((rule->flags & IMA_FSMAGIC)
	    && rule->fsmagic != inode->i_sb->s_magic)
		वापस false;
	अगर ((rule->flags & IMA_FSNAME)
	    && म_भेद(rule->fsname, inode->i_sb->s_type->name))
		वापस false;
	अगर ((rule->flags & IMA_FSUUID) &&
	    !uuid_equal(&rule->fsuuid, &inode->i_sb->s_uuid))
		वापस false;
	अगर ((rule->flags & IMA_UID) && !rule->uid_op(cred->uid, rule->uid))
		वापस false;
	अगर (rule->flags & IMA_EUID) अणु
		अगर (has_capability_noaudit(current, CAP_SETUID)) अणु
			अगर (!rule->uid_op(cred->euid, rule->uid)
			    && !rule->uid_op(cred->suid, rule->uid)
			    && !rule->uid_op(cred->uid, rule->uid))
				वापस false;
		पूर्ण अन्यथा अगर (!rule->uid_op(cred->euid, rule->uid))
			वापस false;
	पूर्ण

	अगर ((rule->flags & IMA_FOWNER) &&
	    !rule->fowner_op(i_uid_पूर्णांकo_mnt(mnt_userns, inode), rule->fowner))
		वापस false;
	क्रम (i = 0; i < MAX_LSM_RULES; i++) अणु
		पूर्णांक rc = 0;
		u32 osid;

		अगर (!rule->lsm[i].rule) अणु
			अगर (!rule->lsm[i].args_p)
				जारी;
			अन्यथा
				वापस false;
		पूर्ण
		चयन (i) अणु
		हाल LSM_OBJ_USER:
		हाल LSM_OBJ_ROLE:
		हाल LSM_OBJ_TYPE:
			security_inode_माला_लोecid(inode, &osid);
			rc = ima_filter_rule_match(osid, rule->lsm[i].type,
						   Audit_equal,
						   rule->lsm[i].rule);
			अवरोध;
		हाल LSM_SUBJ_USER:
		हाल LSM_SUBJ_ROLE:
		हाल LSM_SUBJ_TYPE:
			rc = ima_filter_rule_match(secid, rule->lsm[i].type,
						   Audit_equal,
						   rule->lsm[i].rule);
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
		अगर (!rc)
			वापस false;
	पूर्ण
	वापस true;
पूर्ण

/*
 * In addition to knowing that we need to appउठाओ the file in general,
 * we need to dअगरferentiate between calling hooks, क्रम hook specअगरic rules.
 */
अटल पूर्णांक get_subaction(काष्ठा ima_rule_entry *rule, क्रमागत ima_hooks func)
अणु
	अगर (!(rule->flags & IMA_FUNC))
		वापस IMA_खाता_APPRAISE;

	चयन (func) अणु
	हाल MMAP_CHECK:
		वापस IMA_MMAP_APPRAISE;
	हाल BPRM_CHECK:
		वापस IMA_BPRM_APPRAISE;
	हाल CREDS_CHECK:
		वापस IMA_CREDS_APPRAISE;
	हाल खाता_CHECK:
	हाल POST_SETATTR:
		वापस IMA_खाता_APPRAISE;
	हाल MODULE_CHECK ... MAX_CHECK - 1:
	शेष:
		वापस IMA_READ_APPRAISE;
	पूर्ण
पूर्ण

/**
 * ima_match_policy - decision based on LSM and other conditions
 * @mnt_userns:	user namespace of the mount the inode was found from
 * @inode: poपूर्णांकer to an inode क्रम which the policy decision is being made
 * @cred: poपूर्णांकer to a credentials काष्ठाure क्रम which the policy decision is
 *        being made
 * @secid: LSM secid of the task to be validated
 * @func: IMA hook identअगरier
 * @mask: requested action (MAY_READ | MAY_WRITE | MAY_APPEND | MAY_EXEC)
 * @pcr: set the pcr to extend
 * @ढाँचा_desc: the ढाँचा that should be used क्रम this rule
 * @func_data: func specअगरic data, may be शून्य
 *
 * Measure decision based on func/mask/fsmagic and LSM(subj/obj/type)
 * conditions.
 *
 * Since the IMA policy may be updated multiple बार we need to lock the
 * list when walking it.  Reads are many orders of magnitude more numerous
 * than ग_लिखोs so ima_match_policy() is classical RCU candidate.
 */
पूर्णांक ima_match_policy(काष्ठा user_namespace *mnt_userns, काष्ठा inode *inode,
		     स्थिर काष्ठा cred *cred, u32 secid, क्रमागत ima_hooks func,
		     पूर्णांक mask, पूर्णांक flags, पूर्णांक *pcr,
		     काष्ठा ima_ढाँचा_desc **ढाँचा_desc,
		     स्थिर अक्षर *func_data)
अणु
	काष्ठा ima_rule_entry *entry;
	पूर्णांक action = 0, acपंचांगask = flags | (flags << 1);

	अगर (ढाँचा_desc && !*ढाँचा_desc)
		*ढाँचा_desc = ima_ढाँचा_desc_current();

	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(entry, ima_rules, list) अणु

		अगर (!(entry->action & acपंचांगask))
			जारी;

		अगर (!ima_match_rules(entry, mnt_userns, inode, cred, secid,
				     func, mask, func_data))
			जारी;

		action |= entry->flags & IMA_ACTION_FLAGS;

		action |= entry->action & IMA_DO_MASK;
		अगर (entry->action & IMA_APPRAISE) अणु
			action |= get_subaction(entry, func);
			action &= ~IMA_HASH;
			अगर (ima_fail_unverअगरiable_sigs)
				action |= IMA_FAIL_UNVERIFIABLE_SIGS;
		पूर्ण


		अगर (entry->action & IMA_DO_MASK)
			acपंचांगask &= ~(entry->action | entry->action << 1);
		अन्यथा
			acपंचांगask &= ~(entry->action | entry->action >> 1);

		अगर ((pcr) && (entry->flags & IMA_PCR))
			*pcr = entry->pcr;

		अगर (ढाँचा_desc && entry->ढाँचा)
			*ढाँचा_desc = entry->ढाँचा;

		अगर (!acपंचांगask)
			अवरोध;
	पूर्ण
	rcu_पढ़ो_unlock();

	वापस action;
पूर्ण

/*
 * Initialize the ima_policy_flag variable based on the currently
 * loaded policy.  Based on this flag, the decision to लघु circuit
 * out of a function or not call the function in the first place
 * can be made earlier.
 */
व्योम ima_update_policy_flag(व्योम)
अणु
	काष्ठा ima_rule_entry *entry;

	list_क्रम_each_entry(entry, ima_rules, list) अणु
		अगर (entry->action & IMA_DO_MASK)
			ima_policy_flag |= entry->action;
	पूर्ण

	ima_appउठाओ |= (build_ima_appउठाओ | temp_ima_appउठाओ);
	अगर (!ima_appउठाओ)
		ima_policy_flag &= ~IMA_APPRAISE;
पूर्ण

अटल पूर्णांक ima_appउठाओ_flag(क्रमागत ima_hooks func)
अणु
	अगर (func == MODULE_CHECK)
		वापस IMA_APPRAISE_MODULES;
	अन्यथा अगर (func == FIRMWARE_CHECK)
		वापस IMA_APPRAISE_FIRMWARE;
	अन्यथा अगर (func == POLICY_CHECK)
		वापस IMA_APPRAISE_POLICY;
	अन्यथा अगर (func == KEXEC_KERNEL_CHECK)
		वापस IMA_APPRAISE_KEXEC;
	वापस 0;
पूर्ण

अटल व्योम add_rules(काष्ठा ima_rule_entry *entries, पूर्णांक count,
		      क्रमागत policy_rule_list policy_rule)
अणु
	पूर्णांक i = 0;

	क्रम (i = 0; i < count; i++) अणु
		काष्ठा ima_rule_entry *entry;

		अगर (policy_rule & IMA_DEFAULT_POLICY)
			list_add_tail(&entries[i].list, &ima_शेष_rules);

		अगर (policy_rule & IMA_CUSTOM_POLICY) अणु
			entry = kmemdup(&entries[i], माप(*entry),
					GFP_KERNEL);
			अगर (!entry)
				जारी;

			list_add_tail(&entry->list, &ima_policy_rules);
		पूर्ण
		अगर (entries[i].action == APPRAISE) अणु
			अगर (entries != build_appउठाओ_rules)
				temp_ima_appउठाओ |=
					ima_appउठाओ_flag(entries[i].func);
			अन्यथा
				build_ima_appउठाओ |=
					ima_appउठाओ_flag(entries[i].func);
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक ima_parse_rule(अक्षर *rule, काष्ठा ima_rule_entry *entry);

अटल पूर्णांक __init ima_init_arch_policy(व्योम)
अणु
	स्थिर अक्षर * स्थिर *arch_rules;
	स्थिर अक्षर * स्थिर *rules;
	पूर्णांक arch_entries = 0;
	पूर्णांक i = 0;

	arch_rules = arch_get_ima_policy();
	अगर (!arch_rules)
		वापस arch_entries;

	/* Get number of rules */
	क्रम (rules = arch_rules; *rules != शून्य; rules++)
		arch_entries++;

	arch_policy_entry = kसुस्मृति(arch_entries + 1,
				    माप(*arch_policy_entry), GFP_KERNEL);
	अगर (!arch_policy_entry)
		वापस 0;

	/* Convert each policy string rules to काष्ठा ima_rule_entry क्रमmat */
	क्रम (rules = arch_rules, i = 0; *rules != शून्य; rules++) अणु
		अक्षर rule[255];
		पूर्णांक result;

		result = strlcpy(rule, *rules, माप(rule));

		INIT_LIST_HEAD(&arch_policy_entry[i].list);
		result = ima_parse_rule(rule, &arch_policy_entry[i]);
		अगर (result) अणु
			pr_warn("Skipping unknown architecture policy rule: %s\n",
				rule);
			स_रखो(&arch_policy_entry[i], 0,
			       माप(*arch_policy_entry));
			जारी;
		पूर्ण
		i++;
	पूर्ण
	वापस i;
पूर्ण

/**
 * ima_init_policy - initialize the शेष measure rules.
 *
 * ima_rules poपूर्णांकs to either the ima_शेष_rules or the
 * the new ima_policy_rules.
 */
व्योम __init ima_init_policy(व्योम)
अणु
	पूर्णांक build_appउठाओ_entries, arch_entries;

	/* अगर !ima_policy, we load NO शेष rules */
	अगर (ima_policy)
		add_rules(करोnt_measure_rules, ARRAY_SIZE(करोnt_measure_rules),
			  IMA_DEFAULT_POLICY);

	चयन (ima_policy) अणु
	हाल ORIGINAL_TCB:
		add_rules(original_measurement_rules,
			  ARRAY_SIZE(original_measurement_rules),
			  IMA_DEFAULT_POLICY);
		अवरोध;
	हाल DEFAULT_TCB:
		add_rules(शेष_measurement_rules,
			  ARRAY_SIZE(शेष_measurement_rules),
			  IMA_DEFAULT_POLICY);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	/*
	 * Based on runसमय secure boot flags, insert arch specअगरic measurement
	 * and appउठाओ rules requiring file signatures क्रम both the initial
	 * and custom policies, prior to other appउठाओ rules.
	 * (Highest priority)
	 */
	arch_entries = ima_init_arch_policy();
	अगर (!arch_entries)
		pr_info("No architecture policies found\n");
	अन्यथा
		add_rules(arch_policy_entry, arch_entries,
			  IMA_DEFAULT_POLICY | IMA_CUSTOM_POLICY);

	/*
	 * Insert the builtin "secure_boot" policy rules requiring file
	 * signatures, prior to other appउठाओ rules.
	 */
	अगर (ima_use_secure_boot)
		add_rules(secure_boot_rules, ARRAY_SIZE(secure_boot_rules),
			  IMA_DEFAULT_POLICY);

	/*
	 * Insert the build समय appउठाओ rules requiring file signatures
	 * क्रम both the initial and custom policies, prior to other appउठाओ
	 * rules. As the secure boot rules includes all of the build समय
	 * rules, include either one or the other set of rules, but not both.
	 */
	build_appउठाओ_entries = ARRAY_SIZE(build_appउठाओ_rules);
	अगर (build_appउठाओ_entries) अणु
		अगर (ima_use_secure_boot)
			add_rules(build_appउठाओ_rules, build_appउठाओ_entries,
				  IMA_CUSTOM_POLICY);
		अन्यथा
			add_rules(build_appउठाओ_rules, build_appउठाओ_entries,
				  IMA_DEFAULT_POLICY | IMA_CUSTOM_POLICY);
	पूर्ण

	अगर (ima_use_appउठाओ_tcb)
		add_rules(शेष_appउठाओ_rules,
			  ARRAY_SIZE(शेष_appउठाओ_rules),
			  IMA_DEFAULT_POLICY);

	अगर (ima_use_critical_data)
		add_rules(critical_data_rules,
			  ARRAY_SIZE(critical_data_rules),
			  IMA_DEFAULT_POLICY);

	ima_update_policy_flag();
पूर्ण

/* Make sure we have a valid policy, at least containing some rules. */
पूर्णांक ima_check_policy(व्योम)
अणु
	अगर (list_empty(&ima_temp_rules))
		वापस -EINVAL;
	वापस 0;
पूर्ण

/**
 * ima_update_policy - update शेष_rules with new measure rules
 *
 * Called on file .release to update the शेष rules with a complete new
 * policy.  What we करो here is to splice ima_policy_rules and ima_temp_rules so
 * they make a queue.  The policy may be updated multiple बार and this is the
 * RCU updater.
 *
 * Policy rules are never deleted so ima_policy_flag माला_लो zeroed only once when
 * we चयन from the शेष policy to user defined.
 */
व्योम ima_update_policy(व्योम)
अणु
	काष्ठा list_head *policy = &ima_policy_rules;

	list_splice_tail_init_rcu(&ima_temp_rules, policy, synchronize_rcu);

	अगर (ima_rules != policy) अणु
		ima_policy_flag = 0;
		ima_rules = policy;

		/*
		 * IMA architecture specअगरic policy rules are specअगरied
		 * as strings and converted to an array of ima_entry_rules
		 * on boot.  After loading a custom policy, मुक्त the
		 * architecture specअगरic rules stored as an array.
		 */
		kमुक्त(arch_policy_entry);
	पूर्ण
	ima_update_policy_flag();

	/* Custom IMA policy has been loaded */
	ima_process_queued_keys();
पूर्ण

/* Keep the क्रमागतeration in sync with the policy_tokens! */
क्रमागत अणु
	Opt_measure, Opt_करोnt_measure,
	Opt_appउठाओ, Opt_करोnt_appउठाओ,
	Opt_audit, Opt_hash, Opt_करोnt_hash,
	Opt_obj_user, Opt_obj_role, Opt_obj_type,
	Opt_subj_user, Opt_subj_role, Opt_subj_type,
	Opt_func, Opt_mask, Opt_fsmagic, Opt_fsname,
	Opt_fsuuid, Opt_uid_eq, Opt_euid_eq, Opt_fowner_eq,
	Opt_uid_gt, Opt_euid_gt, Opt_fowner_gt,
	Opt_uid_lt, Opt_euid_lt, Opt_fowner_lt,
	Opt_appउठाओ_type, Opt_appउठाओ_flag,
	Opt_permit_directio, Opt_pcr, Opt_ढाँचा, Opt_keyrings,
	Opt_label, Opt_err
पूर्ण;

अटल स्थिर match_table_t policy_tokens = अणु
	अणुOpt_measure, "measure"पूर्ण,
	अणुOpt_करोnt_measure, "dont_measure"पूर्ण,
	अणुOpt_appउठाओ, "appraise"पूर्ण,
	अणुOpt_करोnt_appउठाओ, "dont_appraise"पूर्ण,
	अणुOpt_audit, "audit"पूर्ण,
	अणुOpt_hash, "hash"पूर्ण,
	अणुOpt_करोnt_hash, "dont_hash"पूर्ण,
	अणुOpt_obj_user, "obj_user=%s"पूर्ण,
	अणुOpt_obj_role, "obj_role=%s"पूर्ण,
	अणुOpt_obj_type, "obj_type=%s"पूर्ण,
	अणुOpt_subj_user, "subj_user=%s"पूर्ण,
	अणुOpt_subj_role, "subj_role=%s"पूर्ण,
	अणुOpt_subj_type, "subj_type=%s"पूर्ण,
	अणुOpt_func, "func=%s"पूर्ण,
	अणुOpt_mask, "mask=%s"पूर्ण,
	अणुOpt_fsmagic, "fsmagic=%s"पूर्ण,
	अणुOpt_fsname, "fsname=%s"पूर्ण,
	अणुOpt_fsuuid, "fsuuid=%s"पूर्ण,
	अणुOpt_uid_eq, "uid=%s"पूर्ण,
	अणुOpt_euid_eq, "euid=%s"पूर्ण,
	अणुOpt_fowner_eq, "fowner=%s"पूर्ण,
	अणुOpt_uid_gt, "uid>%s"पूर्ण,
	अणुOpt_euid_gt, "euid>%s"पूर्ण,
	अणुOpt_fowner_gt, "fowner>%s"पूर्ण,
	अणुOpt_uid_lt, "uid<%s"पूर्ण,
	अणुOpt_euid_lt, "euid<%s"पूर्ण,
	अणुOpt_fowner_lt, "fowner<%s"पूर्ण,
	अणुOpt_appउठाओ_type, "appraise_type=%s"पूर्ण,
	अणुOpt_appउठाओ_flag, "appraise_flag=%s"पूर्ण,
	अणुOpt_permit_directio, "permit_directio"पूर्ण,
	अणुOpt_pcr, "pcr=%s"पूर्ण,
	अणुOpt_ढाँचा, "template=%s"पूर्ण,
	अणुOpt_keyrings, "keyrings=%s"पूर्ण,
	अणुOpt_label, "label=%s"पूर्ण,
	अणुOpt_err, शून्यपूर्ण
पूर्ण;

अटल पूर्णांक ima_lsm_rule_init(काष्ठा ima_rule_entry *entry,
			     substring_t *args, पूर्णांक lsm_rule, पूर्णांक audit_type)
अणु
	पूर्णांक result;

	अगर (entry->lsm[lsm_rule].rule)
		वापस -EINVAL;

	entry->lsm[lsm_rule].args_p = match_strdup(args);
	अगर (!entry->lsm[lsm_rule].args_p)
		वापस -ENOMEM;

	entry->lsm[lsm_rule].type = audit_type;
	result = ima_filter_rule_init(entry->lsm[lsm_rule].type, Audit_equal,
				      entry->lsm[lsm_rule].args_p,
				      &entry->lsm[lsm_rule].rule);
	अगर (!entry->lsm[lsm_rule].rule) अणु
		pr_warn("rule for LSM \'%s\' is undefined\n",
			entry->lsm[lsm_rule].args_p);

		अगर (ima_rules == &ima_शेष_rules) अणु
			kमुक्त(entry->lsm[lsm_rule].args_p);
			entry->lsm[lsm_rule].args_p = शून्य;
			result = -EINVAL;
		पूर्ण अन्यथा
			result = 0;
	पूर्ण

	वापस result;
पूर्ण

अटल व्योम ima_log_string_op(काष्ठा audit_buffer *ab, अक्षर *key, अक्षर *value,
			      bool (*rule_चालक)(kuid_t, kuid_t))
अणु
	अगर (!ab)
		वापस;

	अगर (rule_चालक == &uid_gt)
		audit_log_क्रमmat(ab, "%s>", key);
	अन्यथा अगर (rule_चालक == &uid_lt)
		audit_log_क्रमmat(ab, "%s<", key);
	अन्यथा
		audit_log_क्रमmat(ab, "%s=", key);
	audit_log_क्रमmat(ab, "%s ", value);
पूर्ण
अटल व्योम ima_log_string(काष्ठा audit_buffer *ab, अक्षर *key, अक्षर *value)
अणु
	ima_log_string_op(ab, key, value, शून्य);
पूर्ण

/*
 * Validating the appended signature included in the measurement list requires
 * the file hash calculated without the appended signature (i.e., the 'd-modsig'
 * field). Thereक्रमe, notअगरy the user अगर they have the 'modsig' field but not
 * the 'd-modsig' field in the ढाँचा.
 */
अटल व्योम check_ढाँचा_modsig(स्थिर काष्ठा ima_ढाँचा_desc *ढाँचा)
अणु
#घोषणा MSG "template with 'modsig' field also needs 'd-modsig' field\n"
	bool has_modsig, has_dmodsig;
	अटल bool checked;
	पूर्णांक i;

	/* We only need to notअगरy the user once. */
	अगर (checked)
		वापस;

	has_modsig = has_dmodsig = false;
	क्रम (i = 0; i < ढाँचा->num_fields; i++) अणु
		अगर (!म_भेद(ढाँचा->fields[i]->field_id, "modsig"))
			has_modsig = true;
		अन्यथा अगर (!म_भेद(ढाँचा->fields[i]->field_id, "d-modsig"))
			has_dmodsig = true;
	पूर्ण

	अगर (has_modsig && !has_dmodsig)
		pr_notice(MSG);

	checked = true;
#अघोषित MSG
पूर्ण

अटल bool ima_validate_rule(काष्ठा ima_rule_entry *entry)
अणु
	/* Ensure that the action is set and is compatible with the flags */
	अगर (entry->action == UNKNOWN)
		वापस false;

	अगर (entry->action != MEASURE && entry->flags & IMA_PCR)
		वापस false;

	अगर (entry->action != APPRAISE &&
	    entry->flags & (IMA_DIGSIG_REQUIRED | IMA_MODSIG_ALLOWED | IMA_CHECK_BLACKLIST))
		वापस false;

	/*
	 * The IMA_FUNC bit must be set अगर and only अगर there's a valid hook
	 * function specअगरied, and vice versa. Enक्रमcing this property allows
	 * क्रम the NONE हाल below to validate a rule without an explicit hook
	 * function.
	 */
	अगर (((entry->flags & IMA_FUNC) && entry->func == NONE) ||
	    (!(entry->flags & IMA_FUNC) && entry->func != NONE))
		वापस false;

	/*
	 * Ensure that the hook function is compatible with the other
	 * components of the rule
	 */
	चयन (entry->func) अणु
	हाल NONE:
	हाल खाता_CHECK:
	हाल MMAP_CHECK:
	हाल BPRM_CHECK:
	हाल CREDS_CHECK:
	हाल POST_SETATTR:
	हाल FIRMWARE_CHECK:
	हाल POLICY_CHECK:
		अगर (entry->flags & ~(IMA_FUNC | IMA_MASK | IMA_FSMAGIC |
				     IMA_UID | IMA_FOWNER | IMA_FSUUID |
				     IMA_INMASK | IMA_EUID | IMA_PCR |
				     IMA_FSNAME | IMA_DIGSIG_REQUIRED |
				     IMA_PERMIT_सूचीECTIO))
			वापस false;

		अवरोध;
	हाल MODULE_CHECK:
	हाल KEXEC_KERNEL_CHECK:
	हाल KEXEC_INITRAMFS_CHECK:
		अगर (entry->flags & ~(IMA_FUNC | IMA_MASK | IMA_FSMAGIC |
				     IMA_UID | IMA_FOWNER | IMA_FSUUID |
				     IMA_INMASK | IMA_EUID | IMA_PCR |
				     IMA_FSNAME | IMA_DIGSIG_REQUIRED |
				     IMA_PERMIT_सूचीECTIO | IMA_MODSIG_ALLOWED |
				     IMA_CHECK_BLACKLIST))
			वापस false;

		अवरोध;
	हाल KEXEC_CMDLINE:
		अगर (entry->action & ~(MEASURE | DONT_MEASURE))
			वापस false;

		अगर (entry->flags & ~(IMA_FUNC | IMA_FSMAGIC | IMA_UID |
				     IMA_FOWNER | IMA_FSUUID | IMA_EUID |
				     IMA_PCR | IMA_FSNAME))
			वापस false;

		अवरोध;
	हाल KEY_CHECK:
		अगर (entry->action & ~(MEASURE | DONT_MEASURE))
			वापस false;

		अगर (entry->flags & ~(IMA_FUNC | IMA_UID | IMA_PCR |
				     IMA_KEYRINGS))
			वापस false;

		अगर (ima_rule_contains_lsm_cond(entry))
			वापस false;

		अवरोध;
	हाल CRITICAL_DATA:
		अगर (entry->action & ~(MEASURE | DONT_MEASURE))
			वापस false;

		अगर (entry->flags & ~(IMA_FUNC | IMA_UID | IMA_PCR |
				     IMA_LABEL))
			वापस false;

		अगर (ima_rule_contains_lsm_cond(entry))
			वापस false;

		अवरोध;
	शेष:
		वापस false;
	पूर्ण

	/* Ensure that combinations of flags are compatible with each other */
	अगर (entry->flags & IMA_CHECK_BLACKLIST &&
	    !(entry->flags & IMA_MODSIG_ALLOWED))
		वापस false;

	वापस true;
पूर्ण

अटल पूर्णांक ima_parse_rule(अक्षर *rule, काष्ठा ima_rule_entry *entry)
अणु
	काष्ठा audit_buffer *ab;
	अक्षर *from;
	अक्षर *p;
	bool uid_token;
	काष्ठा ima_ढाँचा_desc *ढाँचा_desc;
	पूर्णांक result = 0;

	ab = पूर्णांकegrity_audit_log_start(audit_context(), GFP_KERNEL,
				       AUDIT_INTEGRITY_POLICY_RULE);

	entry->uid = INVALID_UID;
	entry->fowner = INVALID_UID;
	entry->uid_op = &uid_eq;
	entry->fowner_op = &uid_eq;
	entry->action = UNKNOWN;
	जबतक ((p = strsep(&rule, " \t")) != शून्य) अणु
		substring_t args[MAX_OPT_ARGS];
		पूर्णांक token;
		अचिन्हित दीर्घ lnum;

		अगर (result < 0)
			अवरोध;
		अगर ((*p == '\0') || (*p == ' ') || (*p == '\t'))
			जारी;
		token = match_token(p, policy_tokens, args);
		चयन (token) अणु
		हाल Opt_measure:
			ima_log_string(ab, "action", "measure");

			अगर (entry->action != UNKNOWN)
				result = -EINVAL;

			entry->action = MEASURE;
			अवरोध;
		हाल Opt_करोnt_measure:
			ima_log_string(ab, "action", "dont_measure");

			अगर (entry->action != UNKNOWN)
				result = -EINVAL;

			entry->action = DONT_MEASURE;
			अवरोध;
		हाल Opt_appउठाओ:
			ima_log_string(ab, "action", "appraise");

			अगर (entry->action != UNKNOWN)
				result = -EINVAL;

			entry->action = APPRAISE;
			अवरोध;
		हाल Opt_करोnt_appउठाओ:
			ima_log_string(ab, "action", "dont_appraise");

			अगर (entry->action != UNKNOWN)
				result = -EINVAL;

			entry->action = DONT_APPRAISE;
			अवरोध;
		हाल Opt_audit:
			ima_log_string(ab, "action", "audit");

			अगर (entry->action != UNKNOWN)
				result = -EINVAL;

			entry->action = AUDIT;
			अवरोध;
		हाल Opt_hash:
			ima_log_string(ab, "action", "hash");

			अगर (entry->action != UNKNOWN)
				result = -EINVAL;

			entry->action = HASH;
			अवरोध;
		हाल Opt_करोnt_hash:
			ima_log_string(ab, "action", "dont_hash");

			अगर (entry->action != UNKNOWN)
				result = -EINVAL;

			entry->action = DONT_HASH;
			अवरोध;
		हाल Opt_func:
			ima_log_string(ab, "func", args[0].from);

			अगर (entry->func)
				result = -EINVAL;

			अगर (म_भेद(args[0].from, "FILE_CHECK") == 0)
				entry->func = खाता_CHECK;
			/* PATH_CHECK is क्रम backwards compat */
			अन्यथा अगर (म_भेद(args[0].from, "PATH_CHECK") == 0)
				entry->func = खाता_CHECK;
			अन्यथा अगर (म_भेद(args[0].from, "MODULE_CHECK") == 0)
				entry->func = MODULE_CHECK;
			अन्यथा अगर (म_भेद(args[0].from, "FIRMWARE_CHECK") == 0)
				entry->func = FIRMWARE_CHECK;
			अन्यथा अगर ((म_भेद(args[0].from, "FILE_MMAP") == 0)
				|| (म_भेद(args[0].from, "MMAP_CHECK") == 0))
				entry->func = MMAP_CHECK;
			अन्यथा अगर (म_भेद(args[0].from, "BPRM_CHECK") == 0)
				entry->func = BPRM_CHECK;
			अन्यथा अगर (म_भेद(args[0].from, "CREDS_CHECK") == 0)
				entry->func = CREDS_CHECK;
			अन्यथा अगर (म_भेद(args[0].from, "KEXEC_KERNEL_CHECK") ==
				 0)
				entry->func = KEXEC_KERNEL_CHECK;
			अन्यथा अगर (म_भेद(args[0].from, "KEXEC_INITRAMFS_CHECK")
				 == 0)
				entry->func = KEXEC_INITRAMFS_CHECK;
			अन्यथा अगर (म_भेद(args[0].from, "POLICY_CHECK") == 0)
				entry->func = POLICY_CHECK;
			अन्यथा अगर (म_भेद(args[0].from, "KEXEC_CMDLINE") == 0)
				entry->func = KEXEC_CMDLINE;
			अन्यथा अगर (IS_ENABLED(CONFIG_IMA_MEASURE_ASYMMETRIC_KEYS) &&
				 म_भेद(args[0].from, "KEY_CHECK") == 0)
				entry->func = KEY_CHECK;
			अन्यथा अगर (म_भेद(args[0].from, "CRITICAL_DATA") == 0)
				entry->func = CRITICAL_DATA;
			अन्यथा
				result = -EINVAL;
			अगर (!result)
				entry->flags |= IMA_FUNC;
			अवरोध;
		हाल Opt_mask:
			ima_log_string(ab, "mask", args[0].from);

			अगर (entry->mask)
				result = -EINVAL;

			from = args[0].from;
			अगर (*from == '^')
				from++;

			अगर ((म_भेद(from, "MAY_EXEC")) == 0)
				entry->mask = MAY_EXEC;
			अन्यथा अगर (म_भेद(from, "MAY_WRITE") == 0)
				entry->mask = MAY_WRITE;
			अन्यथा अगर (म_भेद(from, "MAY_READ") == 0)
				entry->mask = MAY_READ;
			अन्यथा अगर (म_भेद(from, "MAY_APPEND") == 0)
				entry->mask = MAY_APPEND;
			अन्यथा
				result = -EINVAL;
			अगर (!result)
				entry->flags |= (*args[0].from == '^')
				     ? IMA_INMASK : IMA_MASK;
			अवरोध;
		हाल Opt_fsmagic:
			ima_log_string(ab, "fsmagic", args[0].from);

			अगर (entry->fsmagic) अणु
				result = -EINVAL;
				अवरोध;
			पूर्ण

			result = kम_से_अदीर्घ(args[0].from, 16, &entry->fsmagic);
			अगर (!result)
				entry->flags |= IMA_FSMAGIC;
			अवरोध;
		हाल Opt_fsname:
			ima_log_string(ab, "fsname", args[0].from);

			entry->fsname = kstrdup(args[0].from, GFP_KERNEL);
			अगर (!entry->fsname) अणु
				result = -ENOMEM;
				अवरोध;
			पूर्ण
			result = 0;
			entry->flags |= IMA_FSNAME;
			अवरोध;
		हाल Opt_keyrings:
			ima_log_string(ab, "keyrings", args[0].from);

			अगर (!IS_ENABLED(CONFIG_IMA_MEASURE_ASYMMETRIC_KEYS) ||
			    entry->keyrings) अणु
				result = -EINVAL;
				अवरोध;
			पूर्ण

			entry->keyrings = ima_alloc_rule_opt_list(args);
			अगर (IS_ERR(entry->keyrings)) अणु
				result = PTR_ERR(entry->keyrings);
				entry->keyrings = शून्य;
				अवरोध;
			पूर्ण

			entry->flags |= IMA_KEYRINGS;
			अवरोध;
		हाल Opt_label:
			ima_log_string(ab, "label", args[0].from);

			अगर (entry->label) अणु
				result = -EINVAL;
				अवरोध;
			पूर्ण

			entry->label = ima_alloc_rule_opt_list(args);
			अगर (IS_ERR(entry->label)) अणु
				result = PTR_ERR(entry->label);
				entry->label = शून्य;
				अवरोध;
			पूर्ण

			entry->flags |= IMA_LABEL;
			अवरोध;
		हाल Opt_fsuuid:
			ima_log_string(ab, "fsuuid", args[0].from);

			अगर (!uuid_is_null(&entry->fsuuid)) अणु
				result = -EINVAL;
				अवरोध;
			पूर्ण

			result = uuid_parse(args[0].from, &entry->fsuuid);
			अगर (!result)
				entry->flags |= IMA_FSUUID;
			अवरोध;
		हाल Opt_uid_gt:
		हाल Opt_euid_gt:
			entry->uid_op = &uid_gt;
			fallthrough;
		हाल Opt_uid_lt:
		हाल Opt_euid_lt:
			अगर ((token == Opt_uid_lt) || (token == Opt_euid_lt))
				entry->uid_op = &uid_lt;
			fallthrough;
		हाल Opt_uid_eq:
		हाल Opt_euid_eq:
			uid_token = (token == Opt_uid_eq) ||
				    (token == Opt_uid_gt) ||
				    (token == Opt_uid_lt);

			ima_log_string_op(ab, uid_token ? "uid" : "euid",
					  args[0].from, entry->uid_op);

			अगर (uid_valid(entry->uid)) अणु
				result = -EINVAL;
				अवरोध;
			पूर्ण

			result = kम_से_अदीर्घ(args[0].from, 10, &lnum);
			अगर (!result) अणु
				entry->uid = make_kuid(current_user_ns(),
						       (uid_t) lnum);
				अगर (!uid_valid(entry->uid) ||
				    (uid_t)lnum != lnum)
					result = -EINVAL;
				अन्यथा
					entry->flags |= uid_token
					    ? IMA_UID : IMA_EUID;
			पूर्ण
			अवरोध;
		हाल Opt_fowner_gt:
			entry->fowner_op = &uid_gt;
			fallthrough;
		हाल Opt_fowner_lt:
			अगर (token == Opt_fowner_lt)
				entry->fowner_op = &uid_lt;
			fallthrough;
		हाल Opt_fowner_eq:
			ima_log_string_op(ab, "fowner", args[0].from,
					  entry->fowner_op);

			अगर (uid_valid(entry->fowner)) अणु
				result = -EINVAL;
				अवरोध;
			पूर्ण

			result = kम_से_अदीर्घ(args[0].from, 10, &lnum);
			अगर (!result) अणु
				entry->fowner = make_kuid(current_user_ns(), (uid_t)lnum);
				अगर (!uid_valid(entry->fowner) || (((uid_t)lnum) != lnum))
					result = -EINVAL;
				अन्यथा
					entry->flags |= IMA_FOWNER;
			पूर्ण
			अवरोध;
		हाल Opt_obj_user:
			ima_log_string(ab, "obj_user", args[0].from);
			result = ima_lsm_rule_init(entry, args,
						   LSM_OBJ_USER,
						   AUDIT_OBJ_USER);
			अवरोध;
		हाल Opt_obj_role:
			ima_log_string(ab, "obj_role", args[0].from);
			result = ima_lsm_rule_init(entry, args,
						   LSM_OBJ_ROLE,
						   AUDIT_OBJ_ROLE);
			अवरोध;
		हाल Opt_obj_type:
			ima_log_string(ab, "obj_type", args[0].from);
			result = ima_lsm_rule_init(entry, args,
						   LSM_OBJ_TYPE,
						   AUDIT_OBJ_TYPE);
			अवरोध;
		हाल Opt_subj_user:
			ima_log_string(ab, "subj_user", args[0].from);
			result = ima_lsm_rule_init(entry, args,
						   LSM_SUBJ_USER,
						   AUDIT_SUBJ_USER);
			अवरोध;
		हाल Opt_subj_role:
			ima_log_string(ab, "subj_role", args[0].from);
			result = ima_lsm_rule_init(entry, args,
						   LSM_SUBJ_ROLE,
						   AUDIT_SUBJ_ROLE);
			अवरोध;
		हाल Opt_subj_type:
			ima_log_string(ab, "subj_type", args[0].from);
			result = ima_lsm_rule_init(entry, args,
						   LSM_SUBJ_TYPE,
						   AUDIT_SUBJ_TYPE);
			अवरोध;
		हाल Opt_appउठाओ_type:
			ima_log_string(ab, "appraise_type", args[0].from);
			अगर ((म_भेद(args[0].from, "imasig")) == 0)
				entry->flags |= IMA_DIGSIG_REQUIRED;
			अन्यथा अगर (IS_ENABLED(CONFIG_IMA_APPRAISE_MODSIG) &&
				 म_भेद(args[0].from, "imasig|modsig") == 0)
				entry->flags |= IMA_DIGSIG_REQUIRED |
						IMA_MODSIG_ALLOWED;
			अन्यथा
				result = -EINVAL;
			अवरोध;
		हाल Opt_appउठाओ_flag:
			ima_log_string(ab, "appraise_flag", args[0].from);
			अगर (IS_ENABLED(CONFIG_IMA_APPRAISE_MODSIG) &&
			    म_माला(args[0].from, "blacklist"))
				entry->flags |= IMA_CHECK_BLACKLIST;
			अन्यथा
				result = -EINVAL;
			अवरोध;
		हाल Opt_permit_directio:
			entry->flags |= IMA_PERMIT_सूचीECTIO;
			अवरोध;
		हाल Opt_pcr:
			ima_log_string(ab, "pcr", args[0].from);

			result = kstrtoपूर्णांक(args[0].from, 10, &entry->pcr);
			अगर (result || INVALID_PCR(entry->pcr))
				result = -EINVAL;
			अन्यथा
				entry->flags |= IMA_PCR;

			अवरोध;
		हाल Opt_ढाँचा:
			ima_log_string(ab, "template", args[0].from);
			अगर (entry->action != MEASURE) अणु
				result = -EINVAL;
				अवरोध;
			पूर्ण
			ढाँचा_desc = lookup_ढाँचा_desc(args[0].from);
			अगर (!ढाँचा_desc || entry->ढाँचा) अणु
				result = -EINVAL;
				अवरोध;
			पूर्ण

			/*
			 * ढाँचा_desc_init_fields() करोes nothing अगर
			 * the ढाँचा is alपढ़ोy initialised, so
			 * it's safe to करो this unconditionally
			 */
			ढाँचा_desc_init_fields(ढाँचा_desc->fmt,
						 &(ढाँचा_desc->fields),
						 &(ढाँचा_desc->num_fields));
			entry->ढाँचा = ढाँचा_desc;
			अवरोध;
		हाल Opt_err:
			ima_log_string(ab, "UNKNOWN", p);
			result = -EINVAL;
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (!result && !ima_validate_rule(entry))
		result = -EINVAL;
	अन्यथा अगर (entry->action == APPRAISE)
		temp_ima_appउठाओ |= ima_appउठाओ_flag(entry->func);

	अगर (!result && entry->flags & IMA_MODSIG_ALLOWED) अणु
		ढाँचा_desc = entry->ढाँचा ? entry->ढाँचा :
						  ima_ढाँचा_desc_current();
		check_ढाँचा_modsig(ढाँचा_desc);
	पूर्ण

	audit_log_क्रमmat(ab, "res=%d", !result);
	audit_log_end(ab);
	वापस result;
पूर्ण

/**
 * ima_parse_add_rule - add a rule to ima_policy_rules
 * @rule - ima measurement policy rule
 *
 * Aव्योम locking by allowing just one ग_लिखोr at a समय in ima_ग_लिखो_policy()
 * Returns the length of the rule parsed, an error code on failure
 */
sमाप_प्रकार ima_parse_add_rule(अक्षर *rule)
अणु
	अटल स्थिर अक्षर op[] = "update_policy";
	अक्षर *p;
	काष्ठा ima_rule_entry *entry;
	sमाप_प्रकार result, len;
	पूर्णांक audit_info = 0;

	p = strsep(&rule, "\n");
	len = म_माप(p) + 1;
	p += म_अखोज(p, " \t");

	अगर (*p == '#' || *p == '\0')
		वापस len;

	entry = kzalloc(माप(*entry), GFP_KERNEL);
	अगर (!entry) अणु
		पूर्णांकegrity_audit_msg(AUDIT_INTEGRITY_STATUS, शून्य,
				    शून्य, op, "-ENOMEM", -ENOMEM, audit_info);
		वापस -ENOMEM;
	पूर्ण

	INIT_LIST_HEAD(&entry->list);

	result = ima_parse_rule(p, entry);
	अगर (result) अणु
		ima_मुक्त_rule(entry);
		पूर्णांकegrity_audit_msg(AUDIT_INTEGRITY_STATUS, शून्य,
				    शून्य, op, "invalid-policy", result,
				    audit_info);
		वापस result;
	पूर्ण

	list_add_tail(&entry->list, &ima_temp_rules);

	वापस len;
पूर्ण

/**
 * ima_delete_rules() called to cleanup invalid in-flight policy.
 * We करोn't need locking as we operate on the temp list, which is
 * dअगरferent from the active one.  There is also only one user of
 * ima_delete_rules() at a समय.
 */
व्योम ima_delete_rules(व्योम)
अणु
	काष्ठा ima_rule_entry *entry, *पंचांगp;

	temp_ima_appउठाओ = 0;
	list_क्रम_each_entry_safe(entry, पंचांगp, &ima_temp_rules, list) अणु
		list_del(&entry->list);
		ima_मुक्त_rule(entry);
	पूर्ण
पूर्ण

#घोषणा __ima_hook_stringअगरy(func, str)	(#func),

स्थिर अक्षर *स्थिर func_tokens[] = अणु
	__ima_hooks(__ima_hook_stringअगरy)
पूर्ण;

#अगर_घोषित	CONFIG_IMA_READ_POLICY
क्रमागत अणु
	mask_exec = 0, mask_ग_लिखो, mask_पढ़ो, mask_append
पूर्ण;

अटल स्थिर अक्षर *स्थिर mask_tokens[] = अणु
	"^MAY_EXEC",
	"^MAY_WRITE",
	"^MAY_READ",
	"^MAY_APPEND"
पूर्ण;

व्योम *ima_policy_start(काष्ठा seq_file *m, loff_t *pos)
अणु
	loff_t l = *pos;
	काष्ठा ima_rule_entry *entry;

	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(entry, ima_rules, list) अणु
		अगर (!l--) अणु
			rcu_पढ़ो_unlock();
			वापस entry;
		पूर्ण
	पूर्ण
	rcu_पढ़ो_unlock();
	वापस शून्य;
पूर्ण

व्योम *ima_policy_next(काष्ठा seq_file *m, व्योम *v, loff_t *pos)
अणु
	काष्ठा ima_rule_entry *entry = v;

	rcu_पढ़ो_lock();
	entry = list_entry_rcu(entry->list.next, काष्ठा ima_rule_entry, list);
	rcu_पढ़ो_unlock();
	(*pos)++;

	वापस (&entry->list == ima_rules) ? शून्य : entry;
पूर्ण

व्योम ima_policy_stop(काष्ठा seq_file *m, व्योम *v)
अणु
पूर्ण

#घोषणा pt(token)	policy_tokens[token].pattern
#घोषणा mt(token)	mask_tokens[token]

/*
 * policy_func_show - display the ima_hooks policy rule
 */
अटल व्योम policy_func_show(काष्ठा seq_file *m, क्रमागत ima_hooks func)
अणु
	अगर (func > 0 && func < MAX_CHECK)
		seq_म_लिखो(m, "func=%s ", func_tokens[func]);
	अन्यथा
		seq_म_लिखो(m, "func=%d ", func);
पूर्ण

अटल व्योम ima_show_rule_opt_list(काष्ठा seq_file *m,
				   स्थिर काष्ठा ima_rule_opt_list *opt_list)
अणु
	माप_प्रकार i;

	क्रम (i = 0; i < opt_list->count; i++)
		seq_म_लिखो(m, "%s%s", i ? "|" : "", opt_list->items[i]);
पूर्ण

पूर्णांक ima_policy_show(काष्ठा seq_file *m, व्योम *v)
अणु
	काष्ठा ima_rule_entry *entry = v;
	पूर्णांक i;
	अक्षर tbuf[64] = अणु0,पूर्ण;
	पूर्णांक offset = 0;

	rcu_पढ़ो_lock();

	अगर (entry->action & MEASURE)
		seq_माला_दो(m, pt(Opt_measure));
	अगर (entry->action & DONT_MEASURE)
		seq_माला_दो(m, pt(Opt_करोnt_measure));
	अगर (entry->action & APPRAISE)
		seq_माला_दो(m, pt(Opt_appउठाओ));
	अगर (entry->action & DONT_APPRAISE)
		seq_माला_दो(m, pt(Opt_करोnt_appउठाओ));
	अगर (entry->action & AUDIT)
		seq_माला_दो(m, pt(Opt_audit));
	अगर (entry->action & HASH)
		seq_माला_दो(m, pt(Opt_hash));
	अगर (entry->action & DONT_HASH)
		seq_माला_दो(m, pt(Opt_करोnt_hash));

	seq_माला_दो(m, " ");

	अगर (entry->flags & IMA_FUNC)
		policy_func_show(m, entry->func);

	अगर ((entry->flags & IMA_MASK) || (entry->flags & IMA_INMASK)) अणु
		अगर (entry->flags & IMA_MASK)
			offset = 1;
		अगर (entry->mask & MAY_EXEC)
			seq_म_लिखो(m, pt(Opt_mask), mt(mask_exec) + offset);
		अगर (entry->mask & MAY_WRITE)
			seq_म_लिखो(m, pt(Opt_mask), mt(mask_ग_लिखो) + offset);
		अगर (entry->mask & MAY_READ)
			seq_म_लिखो(m, pt(Opt_mask), mt(mask_पढ़ो) + offset);
		अगर (entry->mask & MAY_APPEND)
			seq_म_लिखो(m, pt(Opt_mask), mt(mask_append) + offset);
		seq_माला_दो(m, " ");
	पूर्ण

	अगर (entry->flags & IMA_FSMAGIC) अणु
		snम_लिखो(tbuf, माप(tbuf), "0x%lx", entry->fsmagic);
		seq_म_लिखो(m, pt(Opt_fsmagic), tbuf);
		seq_माला_दो(m, " ");
	पूर्ण

	अगर (entry->flags & IMA_FSNAME) अणु
		snम_लिखो(tbuf, माप(tbuf), "%s", entry->fsname);
		seq_म_लिखो(m, pt(Opt_fsname), tbuf);
		seq_माला_दो(m, " ");
	पूर्ण

	अगर (entry->flags & IMA_KEYRINGS) अणु
		seq_माला_दो(m, "keyrings=");
		ima_show_rule_opt_list(m, entry->keyrings);
		seq_माला_दो(m, " ");
	पूर्ण

	अगर (entry->flags & IMA_LABEL) अणु
		seq_माला_दो(m, "label=");
		ima_show_rule_opt_list(m, entry->label);
		seq_माला_दो(m, " ");
	पूर्ण

	अगर (entry->flags & IMA_PCR) अणु
		snम_लिखो(tbuf, माप(tbuf), "%d", entry->pcr);
		seq_म_लिखो(m, pt(Opt_pcr), tbuf);
		seq_माला_दो(m, " ");
	पूर्ण

	अगर (entry->flags & IMA_FSUUID) अणु
		seq_म_लिखो(m, "fsuuid=%pU", &entry->fsuuid);
		seq_माला_दो(m, " ");
	पूर्ण

	अगर (entry->flags & IMA_UID) अणु
		snम_लिखो(tbuf, माप(tbuf), "%d", __kuid_val(entry->uid));
		अगर (entry->uid_op == &uid_gt)
			seq_म_लिखो(m, pt(Opt_uid_gt), tbuf);
		अन्यथा अगर (entry->uid_op == &uid_lt)
			seq_म_लिखो(m, pt(Opt_uid_lt), tbuf);
		अन्यथा
			seq_म_लिखो(m, pt(Opt_uid_eq), tbuf);
		seq_माला_दो(m, " ");
	पूर्ण

	अगर (entry->flags & IMA_EUID) अणु
		snम_लिखो(tbuf, माप(tbuf), "%d", __kuid_val(entry->uid));
		अगर (entry->uid_op == &uid_gt)
			seq_म_लिखो(m, pt(Opt_euid_gt), tbuf);
		अन्यथा अगर (entry->uid_op == &uid_lt)
			seq_म_लिखो(m, pt(Opt_euid_lt), tbuf);
		अन्यथा
			seq_म_लिखो(m, pt(Opt_euid_eq), tbuf);
		seq_माला_दो(m, " ");
	पूर्ण

	अगर (entry->flags & IMA_FOWNER) अणु
		snम_लिखो(tbuf, माप(tbuf), "%d", __kuid_val(entry->fowner));
		अगर (entry->fowner_op == &uid_gt)
			seq_म_लिखो(m, pt(Opt_fowner_gt), tbuf);
		अन्यथा अगर (entry->fowner_op == &uid_lt)
			seq_म_लिखो(m, pt(Opt_fowner_lt), tbuf);
		अन्यथा
			seq_म_लिखो(m, pt(Opt_fowner_eq), tbuf);
		seq_माला_दो(m, " ");
	पूर्ण

	क्रम (i = 0; i < MAX_LSM_RULES; i++) अणु
		अगर (entry->lsm[i].rule) अणु
			चयन (i) अणु
			हाल LSM_OBJ_USER:
				seq_म_लिखो(m, pt(Opt_obj_user),
					   entry->lsm[i].args_p);
				अवरोध;
			हाल LSM_OBJ_ROLE:
				seq_म_लिखो(m, pt(Opt_obj_role),
					   entry->lsm[i].args_p);
				अवरोध;
			हाल LSM_OBJ_TYPE:
				seq_म_लिखो(m, pt(Opt_obj_type),
					   entry->lsm[i].args_p);
				अवरोध;
			हाल LSM_SUBJ_USER:
				seq_म_लिखो(m, pt(Opt_subj_user),
					   entry->lsm[i].args_p);
				अवरोध;
			हाल LSM_SUBJ_ROLE:
				seq_म_लिखो(m, pt(Opt_subj_role),
					   entry->lsm[i].args_p);
				अवरोध;
			हाल LSM_SUBJ_TYPE:
				seq_म_लिखो(m, pt(Opt_subj_type),
					   entry->lsm[i].args_p);
				अवरोध;
			पूर्ण
			seq_माला_दो(m, " ");
		पूर्ण
	पूर्ण
	अगर (entry->ढाँचा)
		seq_म_लिखो(m, "template=%s ", entry->ढाँचा->name);
	अगर (entry->flags & IMA_DIGSIG_REQUIRED) अणु
		अगर (entry->flags & IMA_MODSIG_ALLOWED)
			seq_माला_दो(m, "appraise_type=imasig|modsig ");
		अन्यथा
			seq_माला_दो(m, "appraise_type=imasig ");
	पूर्ण
	अगर (entry->flags & IMA_CHECK_BLACKLIST)
		seq_माला_दो(m, "appraise_flag=check_blacklist ");
	अगर (entry->flags & IMA_PERMIT_सूचीECTIO)
		seq_माला_दो(m, "permit_directio ");
	rcu_पढ़ो_unlock();
	seq_माला_दो(m, "\n");
	वापस 0;
पूर्ण
#पूर्ण_अगर	/* CONFIG_IMA_READ_POLICY */

#अगर defined(CONFIG_IMA_APPRAISE) && defined(CONFIG_INTEGRITY_TRUSTED_KEYRING)
/*
 * ima_appउठाओ_signature: whether IMA will appउठाओ a given function using
 * an IMA digital signature. This is restricted to हालs where the kernel
 * has a set of built-in trusted keys in order to aव्योम an attacker simply
 * loading additional keys.
 */
bool ima_appउठाओ_signature(क्रमागत kernel_पढ़ो_file_id id)
अणु
	काष्ठा ima_rule_entry *entry;
	bool found = false;
	क्रमागत ima_hooks func;

	अगर (id >= READING_MAX_ID)
		वापस false;

	func = पढ़ो_idmap[id] ?: खाता_CHECK;

	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(entry, ima_rules, list) अणु
		अगर (entry->action != APPRAISE)
			जारी;

		/*
		 * A generic entry will match, but otherwise require that it
		 * match the func we're looking क्रम
		 */
		अगर (entry->func && entry->func != func)
			जारी;

		/*
		 * We require this to be a digital signature, not a raw IMA
		 * hash.
		 */
		अगर (entry->flags & IMA_DIGSIG_REQUIRED)
			found = true;

		/*
		 * We've found a rule that matches, so अवरोध now even अगर it
		 * didn't require a digital signature - a later rule that करोes
		 * won't override it, so would be a false positive.
		 */
		अवरोध;
	पूर्ण

	rcu_पढ़ो_unlock();
	वापस found;
पूर्ण
#पूर्ण_अगर /* CONFIG_IMA_APPRAISE && CONFIG_INTEGRITY_TRUSTED_KEYRING */
