<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2007 Casey Schaufler <हालy@schaufler-ca.com>
 *
 * Authors:
 * 	Casey Schaufler <हालy@schaufler-ca.com>
 * 	Ahmed S. Darwish <darwish.07@gmail.com>
 *
 * Special thanks to the authors of selinuxfs.
 *
 *	Karl MacMillan <kmacmillan@tresys.com>
 *	James Morris <jmorris@redhat.com>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/security.h>
#समावेश <linux/mutex.h>
#समावेश <linux/slab.h>
#समावेश <net/net_namespace.h>
#समावेश <net/cipso_ipv4.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/audit.h>
#समावेश <linux/magic.h>
#समावेश <linux/fs_context.h>
#समावेश "smack.h"

#घोषणा BEBITS	(माप(__be32) * 8)
/*
 * smackfs pseuकरो fileप्रणाली.
 */

क्रमागत smk_inos अणु
	SMK_ROOT_INO	= 2,
	SMK_LOAD	= 3,	/* load policy */
	SMK_CIPSO	= 4,	/* load label -> CIPSO mapping */
	SMK_DOI		= 5,	/* CIPSO DOI */
	SMK_सूचीECT	= 6,	/* CIPSO level indicating direct label */
	SMK_AMBIENT	= 7,	/* पूर्णांकernet ambient label */
	SMK_NET4ADDR	= 8,	/* single label hosts */
	SMK_ONLYCAP	= 9,	/* the only "capable" label */
	SMK_LOGGING	= 10,	/* logging */
	SMK_LOAD_SELF	= 11,	/* task specअगरic rules */
	SMK_ACCESSES	= 12,	/* access policy */
	SMK_MAPPED	= 13,	/* CIPSO level indicating mapped label */
	SMK_LOAD2	= 14,	/* load policy with दीर्घ labels */
	SMK_LOAD_SELF2	= 15,	/* load task specअगरic rules with दीर्घ labels */
	SMK_ACCESS2	= 16,	/* make an access check with दीर्घ labels */
	SMK_CIPSO2	= 17,	/* load दीर्घ label -> CIPSO mapping */
	SMK_REVOKE_SUBJ	= 18,	/* set rules with subject label to '-' */
	SMK_CHANGE_RULE	= 19,	/* change or add rules (दीर्घ labels) */
	SMK_SYSLOG	= 20,	/* change syslog label) */
	SMK_PTRACE	= 21,	/* set ptrace rule */
#अगर_घोषित CONFIG_SECURITY_SMACK_BRINGUP
	SMK_UNCONFINED	= 22,	/* define an unconfined label */
#पूर्ण_अगर
#अगर IS_ENABLED(CONFIG_IPV6)
	SMK_NET6ADDR	= 23,	/* single label IPv6 hosts */
#पूर्ण_अगर /* CONFIG_IPV6 */
	SMK_RELABEL_SELF = 24, /* relabel possible without CAP_MAC_ADMIN */
पूर्ण;

/*
 * List locks
 */
अटल DEFINE_MUTEX(smack_cipso_lock);
अटल DEFINE_MUTEX(smack_ambient_lock);
अटल DEFINE_MUTEX(smk_net4addr_lock);
#अगर IS_ENABLED(CONFIG_IPV6)
अटल DEFINE_MUTEX(smk_net6addr_lock);
#पूर्ण_अगर /* CONFIG_IPV6 */

/*
 * This is the "ambient" label क्रम network traffic.
 * If it isn't somehow marked, use this.
 * It can be reset via smackfs/ambient
 */
काष्ठा smack_known *smack_net_ambient;

/*
 * This is the level in a CIPSO header that indicates a
 * smack label is contained directly in the category set.
 * It can be reset via smackfs/direct
 */
पूर्णांक smack_cipso_direct = SMACK_CIPSO_सूचीECT_DEFAULT;

/*
 * This is the level in a CIPSO header that indicates a
 * secid is contained directly in the category set.
 * It can be reset via smackfs/mapped
 */
पूर्णांक smack_cipso_mapped = SMACK_CIPSO_MAPPED_DEFAULT;

#अगर_घोषित CONFIG_SECURITY_SMACK_BRINGUP
/*
 * Allow one label to be unconfined. This is क्रम
 * debugging and application bring-up purposes only.
 * It is bad and wrong, but everyone seems to expect
 * to have it.
 */
काष्ठा smack_known *smack_unconfined;
#पूर्ण_अगर

/*
 * If this value is set restrict syslog use to the label specअगरied.
 * It can be reset via smackfs/syslog
 */
काष्ठा smack_known *smack_syslog_label;

/*
 * Ptrace current rule
 * SMACK_PTRACE_DEFAULT    regular smack ptrace rules (/proc based)
 * SMACK_PTRACE_EXACT      labels must match, but can be overriden with
 *			   CAP_SYS_PTRACE
 * SMACK_PTRACE_DRACONIAN  lables must match, CAP_SYS_PTRACE has no effect
 */
पूर्णांक smack_ptrace_rule = SMACK_PTRACE_DEFAULT;

/*
 * Certain IP addresses may be designated as single label hosts.
 * Packets are sent there unlabeled, but only from tasks that
 * can ग_लिखो to the specअगरied label.
 */

LIST_HEAD(smk_net4addr_list);
#अगर IS_ENABLED(CONFIG_IPV6)
LIST_HEAD(smk_net6addr_list);
#पूर्ण_अगर /* CONFIG_IPV6 */

/*
 * Rule lists are मुख्यtained क्रम each label.
 */
काष्ठा smack_parsed_rule अणु
	काष्ठा smack_known	*smk_subject;
	काष्ठा smack_known	*smk_object;
	पूर्णांक			smk_access1;
	पूर्णांक			smk_access2;
पूर्ण;

अटल पूर्णांक smk_cipso_करोi_value = SMACK_CIPSO_DOI_DEFAULT;

/*
 * Values क्रम parsing cipso rules
 * SMK_DIGITLEN: Length of a digit field in a rule.
 * SMK_CIPSOMIN: Minimum possible cipso rule length.
 * SMK_CIPSOMAX: Maximum possible cipso rule length.
 */
#घोषणा SMK_DIGITLEN 4
#घोषणा SMK_CIPSOMIN (SMK_LABELLEN + 2 * SMK_DIGITLEN)
#घोषणा SMK_CIPSOMAX (SMK_CIPSOMIN + SMACK_CIPSO_MAXCATNUM * SMK_DIGITLEN)

/*
 * Values क्रम parsing MAC rules
 * SMK_ACCESS: Maximum possible combination of access permissions
 * SMK_ACCESSLEN: Maximum length क्रम a rule access field
 * SMK_LOADLEN: Smack rule length
 */
#घोषणा SMK_OACCESS	"rwxa"
#घोषणा SMK_ACCESS	"rwxatl"
#घोषणा SMK_OACCESSLEN	(माप(SMK_OACCESS) - 1)
#घोषणा SMK_ACCESSLEN	(माप(SMK_ACCESS) - 1)
#घोषणा SMK_OLOADLEN	(SMK_LABELLEN + SMK_LABELLEN + SMK_OACCESSLEN)
#घोषणा SMK_LOADLEN	(SMK_LABELLEN + SMK_LABELLEN + SMK_ACCESSLEN)

/*
 * Stricly क्रम CIPSO level manipulation.
 * Set the category bit number in a smack label sized buffer.
 */
अटल अंतरभूत व्योम smack_catset_bit(अचिन्हित पूर्णांक cat, अक्षर *catsetp)
अणु
	अगर (cat == 0 || cat > (SMK_CIPSOLEN * 8))
		वापस;

	catsetp[(cat - 1) / 8] |= 0x80 >> ((cat - 1) % 8);
पूर्ण

/**
 * smk_netlabel_audit_set - fill a netlbl_audit काष्ठा
 * @nap: काष्ठाure to fill
 */
अटल व्योम smk_netlabel_audit_set(काष्ठा netlbl_audit *nap)
अणु
	काष्ठा smack_known *skp = smk_of_current();

	nap->loginuid = audit_get_loginuid(current);
	nap->sessionid = audit_get_sessionid(current);
	nap->secid = skp->smk_secid;
पूर्ण

/*
 * Value क्रम parsing single label host rules
 * "1.2.3.4 X"
 */
#घोषणा SMK_NETLBLADDRMIN	9

/**
 * smk_set_access - add a rule to the rule list or replace an old rule
 * @srp: the rule to add or replace
 * @rule_list: the list of rules
 * @rule_lock: the rule list lock
 *
 * Looks through the current subject/object/access list क्रम
 * the subject/object pair and replaces the access that was
 * there. If the pair isn't found add it with the specअगरied
 * access.
 *
 * Returns 0 अगर nothing goes wrong or -ENOMEM अगर it fails
 * during the allocation of the new pair to add.
 */
अटल पूर्णांक smk_set_access(काष्ठा smack_parsed_rule *srp,
				काष्ठा list_head *rule_list,
				काष्ठा mutex *rule_lock)
अणु
	काष्ठा smack_rule *sp;
	पूर्णांक found = 0;
	पूर्णांक rc = 0;

	mutex_lock(rule_lock);

	/*
	 * Because the object label is less likely to match
	 * than the subject label check it first
	 */
	list_क्रम_each_entry_rcu(sp, rule_list, list) अणु
		अगर (sp->smk_object == srp->smk_object &&
		    sp->smk_subject == srp->smk_subject) अणु
			found = 1;
			sp->smk_access |= srp->smk_access1;
			sp->smk_access &= ~srp->smk_access2;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (found == 0) अणु
		sp = kmem_cache_zalloc(smack_rule_cache, GFP_KERNEL);
		अगर (sp == शून्य) अणु
			rc = -ENOMEM;
			जाओ out;
		पूर्ण

		sp->smk_subject = srp->smk_subject;
		sp->smk_object = srp->smk_object;
		sp->smk_access = srp->smk_access1 & ~srp->smk_access2;

		list_add_rcu(&sp->list, rule_list);
	पूर्ण

out:
	mutex_unlock(rule_lock);
	वापस rc;
पूर्ण

/**
 * smk_perm_from_str - parse smack accesses from a text string
 * @string: a text string that contains a Smack accesses code
 *
 * Returns an पूर्णांकeger with respective bits set क्रम specअगरied accesses.
 */
अटल पूर्णांक smk_perm_from_str(स्थिर अक्षर *string)
अणु
	पूर्णांक perm = 0;
	स्थिर अक्षर *cp;

	क्रम (cp = string; ; cp++)
		चयन (*cp) अणु
		हाल '-':
			अवरोध;
		हाल 'r':
		हाल 'R':
			perm |= MAY_READ;
			अवरोध;
		हाल 'w':
		हाल 'W':
			perm |= MAY_WRITE;
			अवरोध;
		हाल 'x':
		हाल 'X':
			perm |= MAY_EXEC;
			अवरोध;
		हाल 'a':
		हाल 'A':
			perm |= MAY_APPEND;
			अवरोध;
		हाल 't':
		हाल 'T':
			perm |= MAY_TRANSMUTE;
			अवरोध;
		हाल 'l':
		हाल 'L':
			perm |= MAY_LOCK;
			अवरोध;
		हाल 'b':
		हाल 'B':
			perm |= MAY_BRINGUP;
			अवरोध;
		शेष:
			वापस perm;
		पूर्ण
पूर्ण

/**
 * smk_fill_rule - Fill Smack rule from strings
 * @subject: subject label string
 * @object: object label string
 * @access1: access string
 * @access2: string with permissions to be हटाओd
 * @rule: Smack rule
 * @import: अगर non-zero, import labels
 * @len: label length limit
 *
 * Returns 0 on success, appropriate error code on failure.
 */
अटल पूर्णांक smk_fill_rule(स्थिर अक्षर *subject, स्थिर अक्षर *object,
				स्थिर अक्षर *access1, स्थिर अक्षर *access2,
				काष्ठा smack_parsed_rule *rule, पूर्णांक import,
				पूर्णांक len)
अणु
	स्थिर अक्षर *cp;
	काष्ठा smack_known *skp;

	अगर (import) अणु
		rule->smk_subject = smk_import_entry(subject, len);
		अगर (IS_ERR(rule->smk_subject))
			वापस PTR_ERR(rule->smk_subject);

		rule->smk_object = smk_import_entry(object, len);
		अगर (IS_ERR(rule->smk_object))
			वापस PTR_ERR(rule->smk_object);
	पूर्ण अन्यथा अणु
		cp = smk_parse_smack(subject, len);
		अगर (IS_ERR(cp))
			वापस PTR_ERR(cp);
		skp = smk_find_entry(cp);
		kमुक्त(cp);
		अगर (skp == शून्य)
			वापस -ENOENT;
		rule->smk_subject = skp;

		cp = smk_parse_smack(object, len);
		अगर (IS_ERR(cp))
			वापस PTR_ERR(cp);
		skp = smk_find_entry(cp);
		kमुक्त(cp);
		अगर (skp == शून्य)
			वापस -ENOENT;
		rule->smk_object = skp;
	पूर्ण

	rule->smk_access1 = smk_perm_from_str(access1);
	अगर (access2)
		rule->smk_access2 = smk_perm_from_str(access2);
	अन्यथा
		rule->smk_access2 = ~rule->smk_access1;

	वापस 0;
पूर्ण

/**
 * smk_parse_rule - parse Smack rule from load string
 * @data: string to be parsed whose size is SMK_LOADLEN
 * @rule: Smack rule
 * @import: अगर non-zero, import labels
 *
 * Returns 0 on success, -1 on errors.
 */
अटल पूर्णांक smk_parse_rule(स्थिर अक्षर *data, काष्ठा smack_parsed_rule *rule,
				पूर्णांक import)
अणु
	पूर्णांक rc;

	rc = smk_fill_rule(data, data + SMK_LABELLEN,
			   data + SMK_LABELLEN + SMK_LABELLEN, शून्य, rule,
			   import, SMK_LABELLEN);
	वापस rc;
पूर्ण

/**
 * smk_parse_दीर्घ_rule - parse Smack rule from rule string
 * @data: string to be parsed, null terminated
 * @rule: Will be filled with Smack parsed rule
 * @import: अगर non-zero, import labels
 * @tokens: numer of substrings expected in data
 *
 * Returns number of processed bytes on success, -ERRNO on failure.
 */
अटल sमाप_प्रकार smk_parse_दीर्घ_rule(अक्षर *data, काष्ठा smack_parsed_rule *rule,
				पूर्णांक import, पूर्णांक tokens)
अणु
	sमाप_प्रकार cnt = 0;
	अक्षर *tok[4];
	पूर्णांक rc;
	पूर्णांक i;

	/*
	 * Parsing the rule in-place, filling all white-spaces with '\0'
	 */
	क्रम (i = 0; i < tokens; ++i) अणु
		जबतक (है_खाली(data[cnt]))
			data[cnt++] = '\0';

		अगर (data[cnt] == '\0')
			/* Unexpected end of data */
			वापस -EINVAL;

		tok[i] = data + cnt;

		जबतक (data[cnt] && !है_खाली(data[cnt]))
			++cnt;
	पूर्ण
	जबतक (है_खाली(data[cnt]))
		data[cnt++] = '\0';

	जबतक (i < 4)
		tok[i++] = शून्य;

	rc = smk_fill_rule(tok[0], tok[1], tok[2], tok[3], rule, import, 0);
	वापस rc == 0 ? cnt : rc;
पूर्ण

#घोषणा SMK_FIXED24_FMT	0	/* Fixed 24byte label क्रमmat */
#घोषणा SMK_LONG_FMT	1	/* Variable दीर्घ label क्रमmat */
#घोषणा SMK_CHANGE_FMT	2	/* Rule modअगरication क्रमmat */
/**
 * smk_ग_लिखो_rules_list - ग_लिखो() क्रम any /smack rule file
 * @file: file poपूर्णांकer, not actually used
 * @buf: where to get the data from
 * @count: bytes sent
 * @ppos: where to start - must be 0
 * @rule_list: the list of rules to ग_लिखो to
 * @rule_lock: lock क्रम the rule list
 * @क्रमmat: /smack/load or /smack/load2 or /smack/change-rule क्रमmat.
 *
 * Get one smack access rule from above.
 * The क्रमmat क्रम SMK_LONG_FMT is:
 *	"subject<whitespace>object<whitespace>access[<whitespace>...]"
 * The क्रमmat क्रम SMK_FIXED24_FMT is exactly:
 *	"subject                 object                  rwxat"
 * The क्रमmat क्रम SMK_CHANGE_FMT is:
 *	"subject<whitespace>object<whitespace>
 *	 acc_enable<whitespace>acc_disable[<whitespace>...]"
 */
अटल sमाप_प्रकार smk_ग_लिखो_rules_list(काष्ठा file *file, स्थिर अक्षर __user *buf,
					माप_प्रकार count, loff_t *ppos,
					काष्ठा list_head *rule_list,
					काष्ठा mutex *rule_lock, पूर्णांक क्रमmat)
अणु
	काष्ठा smack_parsed_rule rule;
	अक्षर *data;
	पूर्णांक rc;
	पूर्णांक trunc = 0;
	पूर्णांक tokens;
	sमाप_प्रकार cnt = 0;

	/*
	 * No partial ग_लिखोs.
	 * Enough data must be present.
	 */
	अगर (*ppos != 0)
		वापस -EINVAL;

	अगर (क्रमmat == SMK_FIXED24_FMT) अणु
		/*
		 * Minor hack क्रम backward compatibility
		 */
		अगर (count < SMK_OLOADLEN || count > SMK_LOADLEN)
			वापस -EINVAL;
	पूर्ण अन्यथा अणु
		अगर (count >= PAGE_SIZE) अणु
			count = PAGE_SIZE - 1;
			trunc = 1;
		पूर्ण
	पूर्ण

	data = memdup_user_nul(buf, count);
	अगर (IS_ERR(data))
		वापस PTR_ERR(data);

	/*
	 * In हाल of parsing only part of user buf,
	 * aव्योम having partial rule at the data buffer
	 */
	अगर (trunc) अणु
		जबतक (count > 0 && (data[count - 1] != '\n'))
			--count;
		अगर (count == 0) अणु
			rc = -EINVAL;
			जाओ out;
		पूर्ण
	पूर्ण

	data[count] = '\0';
	tokens = (क्रमmat == SMK_CHANGE_FMT ? 4 : 3);
	जबतक (cnt < count) अणु
		अगर (क्रमmat == SMK_FIXED24_FMT) अणु
			rc = smk_parse_rule(data, &rule, 1);
			अगर (rc < 0)
				जाओ out;
			cnt = count;
		पूर्ण अन्यथा अणु
			rc = smk_parse_दीर्घ_rule(data + cnt, &rule, 1, tokens);
			अगर (rc < 0)
				जाओ out;
			अगर (rc == 0) अणु
				rc = -EINVAL;
				जाओ out;
			पूर्ण
			cnt += rc;
		पूर्ण

		अगर (rule_list == शून्य)
			rc = smk_set_access(&rule, &rule.smk_subject->smk_rules,
				&rule.smk_subject->smk_rules_lock);
		अन्यथा
			rc = smk_set_access(&rule, rule_list, rule_lock);

		अगर (rc)
			जाओ out;
	पूर्ण

	rc = cnt;
out:
	kमुक्त(data);
	वापस rc;
पूर्ण

/*
 * Core logic क्रम smackfs seq list operations.
 */

अटल व्योम *smk_seq_start(काष्ठा seq_file *s, loff_t *pos,
				काष्ठा list_head *head)
अणु
	काष्ठा list_head *list;
	पूर्णांक i = *pos;

	rcu_पढ़ो_lock();
	क्रम (list = rcu_dereference(list_next_rcu(head));
		list != head;
		list = rcu_dereference(list_next_rcu(list))) अणु
		अगर (i-- == 0)
			वापस list;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल व्योम *smk_seq_next(काष्ठा seq_file *s, व्योम *v, loff_t *pos,
				काष्ठा list_head *head)
अणु
	काष्ठा list_head *list = v;

	++*pos;
	list = rcu_dereference(list_next_rcu(list));

	वापस (list == head) ? शून्य : list;
पूर्ण

अटल व्योम smk_seq_stop(काष्ठा seq_file *s, व्योम *v)
अणु
	rcu_पढ़ो_unlock();
पूर्ण

अटल व्योम smk_rule_show(काष्ठा seq_file *s, काष्ठा smack_rule *srp, पूर्णांक max)
अणु
	/*
	 * Don't show any rules with label names too दीर्घ क्रम
	 * पूर्णांकerface file (/smack/load or /smack/load2)
	 * because you should expect to be able to ग_लिखो
	 * anything you पढ़ो back.
	 */
	अगर (म_माप(srp->smk_subject->smk_known) >= max ||
	    म_माप(srp->smk_object->smk_known) >= max)
		वापस;

	अगर (srp->smk_access == 0)
		वापस;

	seq_म_लिखो(s, "%s %s",
		   srp->smk_subject->smk_known,
		   srp->smk_object->smk_known);

	seq_अ_दो(s, ' ');

	अगर (srp->smk_access & MAY_READ)
		seq_अ_दो(s, 'r');
	अगर (srp->smk_access & MAY_WRITE)
		seq_अ_दो(s, 'w');
	अगर (srp->smk_access & MAY_EXEC)
		seq_अ_दो(s, 'x');
	अगर (srp->smk_access & MAY_APPEND)
		seq_अ_दो(s, 'a');
	अगर (srp->smk_access & MAY_TRANSMUTE)
		seq_अ_दो(s, 't');
	अगर (srp->smk_access & MAY_LOCK)
		seq_अ_दो(s, 'l');
	अगर (srp->smk_access & MAY_BRINGUP)
		seq_अ_दो(s, 'b');

	seq_अ_दो(s, '\n');
पूर्ण

/*
 * Seq_file पढ़ो operations क्रम /smack/load
 */

अटल व्योम *load2_seq_start(काष्ठा seq_file *s, loff_t *pos)
अणु
	वापस smk_seq_start(s, pos, &smack_known_list);
पूर्ण

अटल व्योम *load2_seq_next(काष्ठा seq_file *s, व्योम *v, loff_t *pos)
अणु
	वापस smk_seq_next(s, v, pos, &smack_known_list);
पूर्ण

अटल पूर्णांक load_seq_show(काष्ठा seq_file *s, व्योम *v)
अणु
	काष्ठा list_head *list = v;
	काष्ठा smack_rule *srp;
	काष्ठा smack_known *skp =
		list_entry_rcu(list, काष्ठा smack_known, list);

	list_क्रम_each_entry_rcu(srp, &skp->smk_rules, list)
		smk_rule_show(s, srp, SMK_LABELLEN);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा seq_operations load_seq_ops = अणु
	.start = load2_seq_start,
	.next  = load2_seq_next,
	.show  = load_seq_show,
	.stop  = smk_seq_stop,
पूर्ण;

/**
 * smk_खोलो_load - खोलो() क्रम /smack/load
 * @inode: inode काष्ठाure representing file
 * @file: "load" file poपूर्णांकer
 *
 * For पढ़ोing, use load_seq_* seq_file पढ़ोing operations.
 */
अटल पूर्णांक smk_खोलो_load(काष्ठा inode *inode, काष्ठा file *file)
अणु
	वापस seq_खोलो(file, &load_seq_ops);
पूर्ण

/**
 * smk_ग_लिखो_load - ग_लिखो() क्रम /smack/load
 * @file: file poपूर्णांकer, not actually used
 * @buf: where to get the data from
 * @count: bytes sent
 * @ppos: where to start - must be 0
 *
 */
अटल sमाप_प्रकार smk_ग_लिखो_load(काष्ठा file *file, स्थिर अक्षर __user *buf,
			      माप_प्रकार count, loff_t *ppos)
अणु
	/*
	 * Must have privilege.
	 * No partial ग_लिखोs.
	 * Enough data must be present.
	 */
	अगर (!smack_privileged(CAP_MAC_ADMIN))
		वापस -EPERM;

	वापस smk_ग_लिखो_rules_list(file, buf, count, ppos, शून्य, शून्य,
				    SMK_FIXED24_FMT);
पूर्ण

अटल स्थिर काष्ठा file_operations smk_load_ops = अणु
	.खोलो           = smk_खोलो_load,
	.पढ़ो		= seq_पढ़ो,
	.llseek         = seq_lseek,
	.ग_लिखो		= smk_ग_लिखो_load,
	.release        = seq_release,
पूर्ण;

/**
 * smk_cipso_करोi - initialize the CIPSO करोमुख्य
 */
अटल व्योम smk_cipso_करोi(व्योम)
अणु
	पूर्णांक rc;
	काष्ठा cipso_v4_करोi *करोip;
	काष्ठा netlbl_audit nai;

	smk_netlabel_audit_set(&nai);

	rc = netlbl_cfg_map_del(शून्य, PF_INET, शून्य, शून्य, &nai);
	अगर (rc != 0)
		prपूर्णांकk(KERN_WARNING "%s:%d remove rc = %d\n",
		       __func__, __LINE__, rc);

	करोip = kदो_स्मृति(माप(काष्ठा cipso_v4_करोi), GFP_KERNEL);
	अगर (करोip == शून्य)
		panic("smack:  Failed to initialize cipso DOI.\n");
	करोip->map.std = शून्य;
	करोip->करोi = smk_cipso_करोi_value;
	करोip->type = CIPSO_V4_MAP_PASS;
	करोip->tags[0] = CIPSO_V4_TAG_RBITMAP;
	क्रम (rc = 1; rc < CIPSO_V4_TAG_MAXCNT; rc++)
		करोip->tags[rc] = CIPSO_V4_TAG_INVALID;

	rc = netlbl_cfg_cipsov4_add(करोip, &nai);
	अगर (rc != 0) अणु
		prपूर्णांकk(KERN_WARNING "%s:%d cipso add rc = %d\n",
		       __func__, __LINE__, rc);
		kमुक्त(करोip);
		वापस;
	पूर्ण
	rc = netlbl_cfg_cipsov4_map_add(करोip->करोi, शून्य, शून्य, शून्य, &nai);
	अगर (rc != 0) अणु
		prपूर्णांकk(KERN_WARNING "%s:%d map add rc = %d\n",
		       __func__, __LINE__, rc);
		kमुक्त(करोip);
		वापस;
	पूर्ण
पूर्ण

/**
 * smk_unlbl_ambient - initialize the unlabeled करोमुख्य
 * @oldambient: previous करोमुख्य string
 */
अटल व्योम smk_unlbl_ambient(अक्षर *oldambient)
अणु
	पूर्णांक rc;
	काष्ठा netlbl_audit nai;

	smk_netlabel_audit_set(&nai);

	अगर (oldambient != शून्य) अणु
		rc = netlbl_cfg_map_del(oldambient, PF_INET, शून्य, शून्य, &nai);
		अगर (rc != 0)
			prपूर्णांकk(KERN_WARNING "%s:%d remove rc = %d\n",
			       __func__, __LINE__, rc);
	पूर्ण
	अगर (smack_net_ambient == शून्य)
		smack_net_ambient = &smack_known_न्यूनमान;

	rc = netlbl_cfg_unlbl_map_add(smack_net_ambient->smk_known, PF_INET,
				      शून्य, शून्य, &nai);
	अगर (rc != 0)
		prपूर्णांकk(KERN_WARNING "%s:%d add rc = %d\n",
		       __func__, __LINE__, rc);
पूर्ण

/*
 * Seq_file पढ़ो operations क्रम /smack/cipso
 */

अटल व्योम *cipso_seq_start(काष्ठा seq_file *s, loff_t *pos)
अणु
	वापस smk_seq_start(s, pos, &smack_known_list);
पूर्ण

अटल व्योम *cipso_seq_next(काष्ठा seq_file *s, व्योम *v, loff_t *pos)
अणु
	वापस smk_seq_next(s, v, pos, &smack_known_list);
पूर्ण

/*
 * Prपूर्णांक cipso labels in क्रमmat:
 * label level[/cat[,cat]]
 */
अटल पूर्णांक cipso_seq_show(काष्ठा seq_file *s, व्योम *v)
अणु
	काष्ठा list_head  *list = v;
	काष्ठा smack_known *skp =
		list_entry_rcu(list, काष्ठा smack_known, list);
	काष्ठा netlbl_lsm_caपंचांगap *cmp = skp->smk_netlabel.attr.mls.cat;
	अक्षर sep = '/';
	पूर्णांक i;

	/*
	 * Don't show a label that could not have been set using
	 * /smack/cipso. This is in support of the notion that
	 * anything पढ़ो from /smack/cipso ought to be ग_लिखोable
	 * to /smack/cipso.
	 *
	 * /smack/cipso2 should be used instead.
	 */
	अगर (म_माप(skp->smk_known) >= SMK_LABELLEN)
		वापस 0;

	seq_म_लिखो(s, "%s %3d", skp->smk_known, skp->smk_netlabel.attr.mls.lvl);

	क्रम (i = netlbl_caपंचांगap_walk(cmp, 0); i >= 0;
	     i = netlbl_caपंचांगap_walk(cmp, i + 1)) अणु
		seq_म_लिखो(s, "%c%d", sep, i);
		sep = ',';
	पूर्ण

	seq_अ_दो(s, '\n');

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा seq_operations cipso_seq_ops = अणु
	.start = cipso_seq_start,
	.next  = cipso_seq_next,
	.show  = cipso_seq_show,
	.stop  = smk_seq_stop,
पूर्ण;

/**
 * smk_खोलो_cipso - खोलो() क्रम /smack/cipso
 * @inode: inode काष्ठाure representing file
 * @file: "cipso" file poपूर्णांकer
 *
 * Connect our cipso_seq_* operations with /smack/cipso
 * file_operations
 */
अटल पूर्णांक smk_खोलो_cipso(काष्ठा inode *inode, काष्ठा file *file)
अणु
	वापस seq_खोलो(file, &cipso_seq_ops);
पूर्ण

/**
 * smk_set_cipso - करो the work क्रम ग_लिखो() क्रम cipso and cipso2
 * @file: file poपूर्णांकer, not actually used
 * @buf: where to get the data from
 * @count: bytes sent
 * @ppos: where to start
 * @क्रमmat: /smack/cipso or /smack/cipso2
 *
 * Accepts only one cipso rule per ग_लिखो call.
 * Returns number of bytes written or error code, as appropriate
 */
अटल sमाप_प्रकार smk_set_cipso(काष्ठा file *file, स्थिर अक्षर __user *buf,
				माप_प्रकार count, loff_t *ppos, पूर्णांक क्रमmat)
अणु
	काष्ठा smack_known *skp;
	काष्ठा netlbl_lsm_secattr ncats;
	अक्षर mapcatset[SMK_CIPSOLEN];
	पूर्णांक maplevel;
	अचिन्हित पूर्णांक cat;
	पूर्णांक catlen;
	sमाप_प्रकार rc = -EINVAL;
	अक्षर *data = शून्य;
	अक्षर *rule;
	पूर्णांक ret;
	पूर्णांक i;

	/*
	 * Must have privilege.
	 * No partial ग_लिखोs.
	 * Enough data must be present.
	 */
	अगर (!smack_privileged(CAP_MAC_ADMIN))
		वापस -EPERM;
	अगर (*ppos != 0)
		वापस -EINVAL;
	अगर (क्रमmat == SMK_FIXED24_FMT &&
	    (count < SMK_CIPSOMIN || count > SMK_CIPSOMAX))
		वापस -EINVAL;

	data = memdup_user_nul(buf, count);
	अगर (IS_ERR(data))
		वापस PTR_ERR(data);

	rule = data;
	/*
	 * Only allow one ग_लिखोr at a समय. Writes should be
	 * quite rare and small in any हाल.
	 */
	mutex_lock(&smack_cipso_lock);

	skp = smk_import_entry(rule, 0);
	अगर (IS_ERR(skp)) अणु
		rc = PTR_ERR(skp);
		जाओ out;
	पूर्ण

	अगर (क्रमmat == SMK_FIXED24_FMT)
		rule += SMK_LABELLEN;
	अन्यथा
		rule += म_माप(skp->smk_known) + 1;

	अगर (rule > data + count) अणु
		rc = -EOVERFLOW;
		जाओ out;
	पूर्ण

	ret = माला_पूछो(rule, "%d", &maplevel);
	अगर (ret != 1 || maplevel < 0 || maplevel > SMACK_CIPSO_MAXLEVEL)
		जाओ out;

	rule += SMK_DIGITLEN;
	अगर (rule > data + count) अणु
		rc = -EOVERFLOW;
		जाओ out;
	पूर्ण

	ret = माला_पूछो(rule, "%d", &catlen);
	अगर (ret != 1 || catlen > SMACK_CIPSO_MAXCATNUM)
		जाओ out;

	अगर (क्रमmat == SMK_FIXED24_FMT &&
	    count != (SMK_CIPSOMIN + catlen * SMK_DIGITLEN))
		जाओ out;

	स_रखो(mapcatset, 0, माप(mapcatset));

	क्रम (i = 0; i < catlen; i++) अणु
		rule += SMK_DIGITLEN;
		अगर (rule > data + count) अणु
			rc = -EOVERFLOW;
			जाओ out;
		पूर्ण
		ret = माला_पूछो(rule, "%u", &cat);
		अगर (ret != 1 || cat > SMACK_CIPSO_MAXCATNUM)
			जाओ out;

		smack_catset_bit(cat, mapcatset);
	पूर्ण

	rc = smk_netlbl_mls(maplevel, mapcatset, &ncats, SMK_CIPSOLEN);
	अगर (rc >= 0) अणु
		netlbl_caपंचांगap_मुक्त(skp->smk_netlabel.attr.mls.cat);
		skp->smk_netlabel.attr.mls.cat = ncats.attr.mls.cat;
		skp->smk_netlabel.attr.mls.lvl = ncats.attr.mls.lvl;
		rc = count;
		/*
		 * This mapping may have been cached, so clear the cache.
		 */
		netlbl_cache_invalidate();
	पूर्ण

out:
	mutex_unlock(&smack_cipso_lock);
	kमुक्त(data);
	वापस rc;
पूर्ण

/**
 * smk_ग_लिखो_cipso - ग_लिखो() क्रम /smack/cipso
 * @file: file poपूर्णांकer, not actually used
 * @buf: where to get the data from
 * @count: bytes sent
 * @ppos: where to start
 *
 * Accepts only one cipso rule per ग_लिखो call.
 * Returns number of bytes written or error code, as appropriate
 */
अटल sमाप_प्रकार smk_ग_लिखो_cipso(काष्ठा file *file, स्थिर अक्षर __user *buf,
			       माप_प्रकार count, loff_t *ppos)
अणु
	वापस smk_set_cipso(file, buf, count, ppos, SMK_FIXED24_FMT);
पूर्ण

अटल स्थिर काष्ठा file_operations smk_cipso_ops = अणु
	.खोलो           = smk_खोलो_cipso,
	.पढ़ो		= seq_पढ़ो,
	.llseek         = seq_lseek,
	.ग_लिखो		= smk_ग_लिखो_cipso,
	.release        = seq_release,
पूर्ण;

/*
 * Seq_file पढ़ो operations क्रम /smack/cipso2
 */

/*
 * Prपूर्णांक cipso labels in क्रमmat:
 * label level[/cat[,cat]]
 */
अटल पूर्णांक cipso2_seq_show(काष्ठा seq_file *s, व्योम *v)
अणु
	काष्ठा list_head  *list = v;
	काष्ठा smack_known *skp =
		list_entry_rcu(list, काष्ठा smack_known, list);
	काष्ठा netlbl_lsm_caपंचांगap *cmp = skp->smk_netlabel.attr.mls.cat;
	अक्षर sep = '/';
	पूर्णांक i;

	seq_म_लिखो(s, "%s %3d", skp->smk_known, skp->smk_netlabel.attr.mls.lvl);

	क्रम (i = netlbl_caपंचांगap_walk(cmp, 0); i >= 0;
	     i = netlbl_caपंचांगap_walk(cmp, i + 1)) अणु
		seq_म_लिखो(s, "%c%d", sep, i);
		sep = ',';
	पूर्ण

	seq_अ_दो(s, '\n');

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा seq_operations cipso2_seq_ops = अणु
	.start = cipso_seq_start,
	.next  = cipso_seq_next,
	.show  = cipso2_seq_show,
	.stop  = smk_seq_stop,
पूर्ण;

/**
 * smk_खोलो_cipso2 - खोलो() क्रम /smack/cipso2
 * @inode: inode काष्ठाure representing file
 * @file: "cipso2" file poपूर्णांकer
 *
 * Connect our cipso_seq_* operations with /smack/cipso2
 * file_operations
 */
अटल पूर्णांक smk_खोलो_cipso2(काष्ठा inode *inode, काष्ठा file *file)
अणु
	वापस seq_खोलो(file, &cipso2_seq_ops);
पूर्ण

/**
 * smk_ग_लिखो_cipso2 - ग_लिखो() क्रम /smack/cipso2
 * @file: file poपूर्णांकer, not actually used
 * @buf: where to get the data from
 * @count: bytes sent
 * @ppos: where to start
 *
 * Accepts only one cipso rule per ग_लिखो call.
 * Returns number of bytes written or error code, as appropriate
 */
अटल sमाप_प्रकार smk_ग_लिखो_cipso2(काष्ठा file *file, स्थिर अक्षर __user *buf,
			      माप_प्रकार count, loff_t *ppos)
अणु
	वापस smk_set_cipso(file, buf, count, ppos, SMK_LONG_FMT);
पूर्ण

अटल स्थिर काष्ठा file_operations smk_cipso2_ops = अणु
	.खोलो           = smk_खोलो_cipso2,
	.पढ़ो		= seq_पढ़ो,
	.llseek         = seq_lseek,
	.ग_लिखो		= smk_ग_लिखो_cipso2,
	.release        = seq_release,
पूर्ण;

/*
 * Seq_file पढ़ो operations क्रम /smack/netlabel
 */

अटल व्योम *net4addr_seq_start(काष्ठा seq_file *s, loff_t *pos)
अणु
	वापस smk_seq_start(s, pos, &smk_net4addr_list);
पूर्ण

अटल व्योम *net4addr_seq_next(काष्ठा seq_file *s, व्योम *v, loff_t *pos)
अणु
	वापस smk_seq_next(s, v, pos, &smk_net4addr_list);
पूर्ण

/*
 * Prपूर्णांक host/label pairs
 */
अटल पूर्णांक net4addr_seq_show(काष्ठा seq_file *s, व्योम *v)
अणु
	काष्ठा list_head *list = v;
	काष्ठा smk_net4addr *skp =
			list_entry_rcu(list, काष्ठा smk_net4addr, list);
	अक्षर *kp = SMACK_CIPSO_OPTION;

	अगर (skp->smk_label != शून्य)
		kp = skp->smk_label->smk_known;
	seq_म_लिखो(s, "%pI4/%d %s\n", &skp->smk_host.s_addr,
			skp->smk_masks, kp);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा seq_operations net4addr_seq_ops = अणु
	.start = net4addr_seq_start,
	.next  = net4addr_seq_next,
	.show  = net4addr_seq_show,
	.stop  = smk_seq_stop,
पूर्ण;

/**
 * smk_खोलो_net4addr - खोलो() क्रम /smack/netlabel
 * @inode: inode काष्ठाure representing file
 * @file: "netlabel" file poपूर्णांकer
 *
 * Connect our net4addr_seq_* operations with /smack/netlabel
 * file_operations
 */
अटल पूर्णांक smk_खोलो_net4addr(काष्ठा inode *inode, काष्ठा file *file)
अणु
	वापस seq_खोलो(file, &net4addr_seq_ops);
पूर्ण

/**
 * smk_net4addr_insert
 * @new : netlabel to insert
 *
 * This helper insert netlabel in the smack_net4addrs list
 * sorted by neपंचांगask length (दीर्घest to smallest)
 * locked by &smk_net4addr_lock in smk_ग_लिखो_net4addr
 *
 */
अटल व्योम smk_net4addr_insert(काष्ठा smk_net4addr *new)
अणु
	काष्ठा smk_net4addr *m;
	काष्ठा smk_net4addr *m_next;

	अगर (list_empty(&smk_net4addr_list)) अणु
		list_add_rcu(&new->list, &smk_net4addr_list);
		वापस;
	पूर्ण

	m = list_entry_rcu(smk_net4addr_list.next,
			   काष्ठा smk_net4addr, list);

	/* the comparison '>' is a bit hacky, but works */
	अगर (new->smk_masks > m->smk_masks) अणु
		list_add_rcu(&new->list, &smk_net4addr_list);
		वापस;
	पूर्ण

	list_क्रम_each_entry_rcu(m, &smk_net4addr_list, list) अणु
		अगर (list_is_last(&m->list, &smk_net4addr_list)) अणु
			list_add_rcu(&new->list, &m->list);
			वापस;
		पूर्ण
		m_next = list_entry_rcu(m->list.next,
					काष्ठा smk_net4addr, list);
		अगर (new->smk_masks > m_next->smk_masks) अणु
			list_add_rcu(&new->list, &m->list);
			वापस;
		पूर्ण
	पूर्ण
पूर्ण


/**
 * smk_ग_लिखो_net4addr - ग_लिखो() क्रम /smack/netlabel
 * @file: file poपूर्णांकer, not actually used
 * @buf: where to get the data from
 * @count: bytes sent
 * @ppos: where to start
 *
 * Accepts only one net4addr per ग_लिखो call.
 * Returns number of bytes written or error code, as appropriate
 */
अटल sमाप_प्रकार smk_ग_लिखो_net4addr(काष्ठा file *file, स्थिर अक्षर __user *buf,
				माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा smk_net4addr *snp;
	काष्ठा sockaddr_in newname;
	अक्षर *smack;
	काष्ठा smack_known *skp = शून्य;
	अक्षर *data;
	अक्षर *host = (अक्षर *)&newname.sin_addr.s_addr;
	पूर्णांक rc;
	काष्ठा netlbl_audit audit_info;
	काष्ठा in_addr mask;
	अचिन्हित पूर्णांक m;
	अचिन्हित पूर्णांक masks;
	पूर्णांक found;
	u32 mask_bits = (1<<31);
	__be32 nsa;
	u32 temp_mask;

	/*
	 * Must have privilege.
	 * No partial ग_लिखोs.
	 * Enough data must be present.
	 * "<addr/mask, as a.b.c.d/e><space><label>"
	 * "<addr, as a.b.c.d><space><label>"
	 */
	अगर (!smack_privileged(CAP_MAC_ADMIN))
		वापस -EPERM;
	अगर (*ppos != 0)
		वापस -EINVAL;
	अगर (count < SMK_NETLBLADDRMIN || count > PAGE_SIZE - 1)
		वापस -EINVAL;

	data = memdup_user_nul(buf, count);
	अगर (IS_ERR(data))
		वापस PTR_ERR(data);

	smack = kzalloc(count + 1, GFP_KERNEL);
	अगर (smack == शून्य) अणु
		rc = -ENOMEM;
		जाओ मुक्त_data_out;
	पूर्ण

	rc = माला_पूछो(data, "%hhd.%hhd.%hhd.%hhd/%u %s",
		&host[0], &host[1], &host[2], &host[3], &masks, smack);
	अगर (rc != 6) अणु
		rc = माला_पूछो(data, "%hhd.%hhd.%hhd.%hhd %s",
			&host[0], &host[1], &host[2], &host[3], smack);
		अगर (rc != 5) अणु
			rc = -EINVAL;
			जाओ मुक्त_out;
		पूर्ण
		m = BEBITS;
		masks = 32;
	पूर्ण
	अगर (masks > BEBITS) अणु
		rc = -EINVAL;
		जाओ मुक्त_out;
	पूर्ण

	/*
	 * If smack begins with '-', it is an option, don't import it
	 */
	अगर (smack[0] != '-') अणु
		skp = smk_import_entry(smack, 0);
		अगर (IS_ERR(skp)) अणु
			rc = PTR_ERR(skp);
			जाओ मुक्त_out;
		पूर्ण
	पूर्ण अन्यथा अणु
		/*
		 * Only the -CIPSO option is supported क्रम IPv4
		 */
		अगर (म_भेद(smack, SMACK_CIPSO_OPTION) != 0) अणु
			rc = -EINVAL;
			जाओ मुक्त_out;
		पूर्ण
	पूर्ण

	क्रम (m = masks, temp_mask = 0; m > 0; m--) अणु
		temp_mask |= mask_bits;
		mask_bits >>= 1;
	पूर्ण
	mask.s_addr = cpu_to_be32(temp_mask);

	newname.sin_addr.s_addr &= mask.s_addr;
	/*
	 * Only allow one ग_लिखोr at a समय. Writes should be
	 * quite rare and small in any हाल.
	 */
	mutex_lock(&smk_net4addr_lock);

	nsa = newname.sin_addr.s_addr;
	/* try to find अगर the prefix is alपढ़ोy in the list */
	found = 0;
	list_क्रम_each_entry_rcu(snp, &smk_net4addr_list, list) अणु
		अगर (snp->smk_host.s_addr == nsa && snp->smk_masks == masks) अणु
			found = 1;
			अवरोध;
		पूर्ण
	पूर्ण
	smk_netlabel_audit_set(&audit_info);

	अगर (found == 0) अणु
		snp = kzalloc(माप(*snp), GFP_KERNEL);
		अगर (snp == शून्य)
			rc = -ENOMEM;
		अन्यथा अणु
			rc = 0;
			snp->smk_host.s_addr = newname.sin_addr.s_addr;
			snp->smk_mask.s_addr = mask.s_addr;
			snp->smk_label = skp;
			snp->smk_masks = masks;
			smk_net4addr_insert(snp);
		पूर्ण
	पूर्ण अन्यथा अणु
		/*
		 * Delete the unlabeled entry, only अगर the previous label
		 * wasn't the special CIPSO option
		 */
		अगर (snp->smk_label != शून्य)
			rc = netlbl_cfg_unlbl_अटल_del(&init_net, शून्य,
					&snp->smk_host, &snp->smk_mask,
					PF_INET, &audit_info);
		अन्यथा
			rc = 0;
		snp->smk_label = skp;
	पूर्ण

	/*
	 * Now tell netlabel about the single label nature of
	 * this host so that incoming packets get labeled.
	 * but only अगर we didn't get the special CIPSO option
	 */
	अगर (rc == 0 && skp != शून्य)
		rc = netlbl_cfg_unlbl_अटल_add(&init_net, शून्य,
			&snp->smk_host, &snp->smk_mask, PF_INET,
			snp->smk_label->smk_secid, &audit_info);

	अगर (rc == 0)
		rc = count;

	mutex_unlock(&smk_net4addr_lock);

मुक्त_out:
	kमुक्त(smack);
मुक्त_data_out:
	kमुक्त(data);

	वापस rc;
पूर्ण

अटल स्थिर काष्ठा file_operations smk_net4addr_ops = अणु
	.खोलो           = smk_खोलो_net4addr,
	.पढ़ो		= seq_पढ़ो,
	.llseek         = seq_lseek,
	.ग_लिखो		= smk_ग_लिखो_net4addr,
	.release        = seq_release,
पूर्ण;

#अगर IS_ENABLED(CONFIG_IPV6)
/*
 * Seq_file पढ़ो operations क्रम /smack/netlabel6
 */

अटल व्योम *net6addr_seq_start(काष्ठा seq_file *s, loff_t *pos)
अणु
	वापस smk_seq_start(s, pos, &smk_net6addr_list);
पूर्ण

अटल व्योम *net6addr_seq_next(काष्ठा seq_file *s, व्योम *v, loff_t *pos)
अणु
	वापस smk_seq_next(s, v, pos, &smk_net6addr_list);
पूर्ण

/*
 * Prपूर्णांक host/label pairs
 */
अटल पूर्णांक net6addr_seq_show(काष्ठा seq_file *s, व्योम *v)
अणु
	काष्ठा list_head *list = v;
	काष्ठा smk_net6addr *skp =
			 list_entry(list, काष्ठा smk_net6addr, list);

	अगर (skp->smk_label != शून्य)
		seq_म_लिखो(s, "%pI6/%d %s\n", &skp->smk_host, skp->smk_masks,
				skp->smk_label->smk_known);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा seq_operations net6addr_seq_ops = अणु
	.start = net6addr_seq_start,
	.next  = net6addr_seq_next,
	.show  = net6addr_seq_show,
	.stop  = smk_seq_stop,
पूर्ण;

/**
 * smk_खोलो_net6addr - खोलो() क्रम /smack/netlabel
 * @inode: inode काष्ठाure representing file
 * @file: "netlabel" file poपूर्णांकer
 *
 * Connect our net6addr_seq_* operations with /smack/netlabel
 * file_operations
 */
अटल पूर्णांक smk_खोलो_net6addr(काष्ठा inode *inode, काष्ठा file *file)
अणु
	वापस seq_खोलो(file, &net6addr_seq_ops);
पूर्ण

/**
 * smk_net6addr_insert
 * @new : entry to insert
 *
 * This inserts an entry in the smack_net6addrs list
 * sorted by neपंचांगask length (दीर्घest to smallest)
 * locked by &smk_net6addr_lock in smk_ग_लिखो_net6addr
 *
 */
अटल व्योम smk_net6addr_insert(काष्ठा smk_net6addr *new)
अणु
	काष्ठा smk_net6addr *m_next;
	काष्ठा smk_net6addr *m;

	अगर (list_empty(&smk_net6addr_list)) अणु
		list_add_rcu(&new->list, &smk_net6addr_list);
		वापस;
	पूर्ण

	m = list_entry_rcu(smk_net6addr_list.next,
			   काष्ठा smk_net6addr, list);

	अगर (new->smk_masks > m->smk_masks) अणु
		list_add_rcu(&new->list, &smk_net6addr_list);
		वापस;
	पूर्ण

	list_क्रम_each_entry_rcu(m, &smk_net6addr_list, list) अणु
		अगर (list_is_last(&m->list, &smk_net6addr_list)) अणु
			list_add_rcu(&new->list, &m->list);
			वापस;
		पूर्ण
		m_next = list_entry_rcu(m->list.next,
					काष्ठा smk_net6addr, list);
		अगर (new->smk_masks > m_next->smk_masks) अणु
			list_add_rcu(&new->list, &m->list);
			वापस;
		पूर्ण
	पूर्ण
पूर्ण


/**
 * smk_ग_लिखो_net6addr - ग_लिखो() क्रम /smack/netlabel
 * @file: file poपूर्णांकer, not actually used
 * @buf: where to get the data from
 * @count: bytes sent
 * @ppos: where to start
 *
 * Accepts only one net6addr per ग_लिखो call.
 * Returns number of bytes written or error code, as appropriate
 */
अटल sमाप_प्रकार smk_ग_लिखो_net6addr(काष्ठा file *file, स्थिर अक्षर __user *buf,
				माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा smk_net6addr *snp;
	काष्ठा in6_addr newname;
	काष्ठा in6_addr fullmask;
	काष्ठा smack_known *skp = शून्य;
	अक्षर *smack;
	अक्षर *data;
	पूर्णांक rc = 0;
	पूर्णांक found = 0;
	पूर्णांक i;
	अचिन्हित पूर्णांक scanned[8];
	अचिन्हित पूर्णांक m;
	अचिन्हित पूर्णांक mask = 128;

	/*
	 * Must have privilege.
	 * No partial ग_लिखोs.
	 * Enough data must be present.
	 * "<addr/mask, as a:b:c:d:e:f:g:h/e><space><label>"
	 * "<addr, as a:b:c:d:e:f:g:h><space><label>"
	 */
	अगर (!smack_privileged(CAP_MAC_ADMIN))
		वापस -EPERM;
	अगर (*ppos != 0)
		वापस -EINVAL;
	अगर (count < SMK_NETLBLADDRMIN || count > PAGE_SIZE - 1)
		वापस -EINVAL;

	data = memdup_user_nul(buf, count);
	अगर (IS_ERR(data))
		वापस PTR_ERR(data);

	smack = kzalloc(count + 1, GFP_KERNEL);
	अगर (smack == शून्य) अणु
		rc = -ENOMEM;
		जाओ मुक्त_data_out;
	पूर्ण

	i = माला_पूछो(data, "%x:%x:%x:%x:%x:%x:%x:%x/%u %s",
			&scanned[0], &scanned[1], &scanned[2], &scanned[3],
			&scanned[4], &scanned[5], &scanned[6], &scanned[7],
			&mask, smack);
	अगर (i != 10) अणु
		i = माला_पूछो(data, "%x:%x:%x:%x:%x:%x:%x:%x %s",
				&scanned[0], &scanned[1], &scanned[2],
				&scanned[3], &scanned[4], &scanned[5],
				&scanned[6], &scanned[7], smack);
		अगर (i != 9) अणु
			rc = -EINVAL;
			जाओ मुक्त_out;
		पूर्ण
	पूर्ण
	अगर (mask > 128) अणु
		rc = -EINVAL;
		जाओ मुक्त_out;
	पूर्ण
	क्रम (i = 0; i < 8; i++) अणु
		अगर (scanned[i] > 0xffff) अणु
			rc = -EINVAL;
			जाओ मुक्त_out;
		पूर्ण
		newname.s6_addr16[i] = htons(scanned[i]);
	पूर्ण

	/*
	 * If smack begins with '-', it is an option, don't import it
	 */
	अगर (smack[0] != '-') अणु
		skp = smk_import_entry(smack, 0);
		अगर (IS_ERR(skp)) अणु
			rc = PTR_ERR(skp);
			जाओ मुक्त_out;
		पूर्ण
	पूर्ण अन्यथा अणु
		/*
		 * Only -DELETE is supported क्रम IPv6
		 */
		अगर (म_भेद(smack, SMACK_DELETE_OPTION) != 0) अणु
			rc = -EINVAL;
			जाओ मुक्त_out;
		पूर्ण
	पूर्ण

	क्रम (i = 0, m = mask; i < 8; i++) अणु
		अगर (m >= 16) अणु
			fullmask.s6_addr16[i] = 0xffff;
			m -= 16;
		पूर्ण अन्यथा अगर (m > 0) अणु
			fullmask.s6_addr16[i] = (1 << m) - 1;
			m = 0;
		पूर्ण अन्यथा
			fullmask.s6_addr16[i] = 0;
		newname.s6_addr16[i] &= fullmask.s6_addr16[i];
	पूर्ण

	/*
	 * Only allow one ग_लिखोr at a समय. Writes should be
	 * quite rare and small in any हाल.
	 */
	mutex_lock(&smk_net6addr_lock);
	/*
	 * Try to find the prefix in the list
	 */
	list_क्रम_each_entry_rcu(snp, &smk_net6addr_list, list) अणु
		अगर (mask != snp->smk_masks)
			जारी;
		क्रम (found = 1, i = 0; i < 8; i++) अणु
			अगर (newname.s6_addr16[i] !=
			    snp->smk_host.s6_addr16[i]) अणु
				found = 0;
				अवरोध;
			पूर्ण
		पूर्ण
		अगर (found == 1)
			अवरोध;
	पूर्ण
	अगर (found == 0) अणु
		snp = kzalloc(माप(*snp), GFP_KERNEL);
		अगर (snp == शून्य)
			rc = -ENOMEM;
		अन्यथा अणु
			snp->smk_host = newname;
			snp->smk_mask = fullmask;
			snp->smk_masks = mask;
			snp->smk_label = skp;
			smk_net6addr_insert(snp);
		पूर्ण
	पूर्ण अन्यथा अणु
		snp->smk_label = skp;
	पूर्ण

	अगर (rc == 0)
		rc = count;

	mutex_unlock(&smk_net6addr_lock);

मुक्त_out:
	kमुक्त(smack);
मुक्त_data_out:
	kमुक्त(data);

	वापस rc;
पूर्ण

अटल स्थिर काष्ठा file_operations smk_net6addr_ops = अणु
	.खोलो           = smk_खोलो_net6addr,
	.पढ़ो		= seq_पढ़ो,
	.llseek         = seq_lseek,
	.ग_लिखो		= smk_ग_लिखो_net6addr,
	.release        = seq_release,
पूर्ण;
#पूर्ण_अगर /* CONFIG_IPV6 */

/**
 * smk_पढ़ो_करोi - पढ़ो() क्रम /smack/करोi
 * @filp: file poपूर्णांकer, not actually used
 * @buf: where to put the result
 * @count: maximum to send aदीर्घ
 * @ppos: where to start
 *
 * Returns number of bytes पढ़ो or error code, as appropriate
 */
अटल sमाप_प्रकार smk_पढ़ो_करोi(काष्ठा file *filp, अक्षर __user *buf,
			    माप_प्रकार count, loff_t *ppos)
अणु
	अक्षर temp[80];
	sमाप_प्रकार rc;

	अगर (*ppos != 0)
		वापस 0;

	प्र_लिखो(temp, "%d", smk_cipso_करोi_value);
	rc = simple_पढ़ो_from_buffer(buf, count, ppos, temp, म_माप(temp));

	वापस rc;
पूर्ण

/**
 * smk_ग_लिखो_करोi - ग_लिखो() क्रम /smack/करोi
 * @file: file poपूर्णांकer, not actually used
 * @buf: where to get the data from
 * @count: bytes sent
 * @ppos: where to start
 *
 * Returns number of bytes written or error code, as appropriate
 */
अटल sमाप_प्रकार smk_ग_लिखो_करोi(काष्ठा file *file, स्थिर अक्षर __user *buf,
			     माप_प्रकार count, loff_t *ppos)
अणु
	अक्षर temp[80];
	पूर्णांक i;

	अगर (!smack_privileged(CAP_MAC_ADMIN))
		वापस -EPERM;

	अगर (count >= माप(temp) || count == 0)
		वापस -EINVAL;

	अगर (copy_from_user(temp, buf, count) != 0)
		वापस -EFAULT;

	temp[count] = '\0';

	अगर (माला_पूछो(temp, "%d", &i) != 1)
		वापस -EINVAL;

	smk_cipso_करोi_value = i;

	smk_cipso_करोi();

	वापस count;
पूर्ण

अटल स्थिर काष्ठा file_operations smk_करोi_ops = अणु
	.पढ़ो		= smk_पढ़ो_करोi,
	.ग_लिखो		= smk_ग_लिखो_करोi,
	.llseek		= शेष_llseek,
पूर्ण;

/**
 * smk_पढ़ो_direct - पढ़ो() क्रम /smack/direct
 * @filp: file poपूर्णांकer, not actually used
 * @buf: where to put the result
 * @count: maximum to send aदीर्घ
 * @ppos: where to start
 *
 * Returns number of bytes पढ़ो or error code, as appropriate
 */
अटल sमाप_प्रकार smk_पढ़ो_direct(काष्ठा file *filp, अक्षर __user *buf,
			       माप_प्रकार count, loff_t *ppos)
अणु
	अक्षर temp[80];
	sमाप_प्रकार rc;

	अगर (*ppos != 0)
		वापस 0;

	प्र_लिखो(temp, "%d", smack_cipso_direct);
	rc = simple_पढ़ो_from_buffer(buf, count, ppos, temp, म_माप(temp));

	वापस rc;
पूर्ण

/**
 * smk_ग_लिखो_direct - ग_लिखो() क्रम /smack/direct
 * @file: file poपूर्णांकer, not actually used
 * @buf: where to get the data from
 * @count: bytes sent
 * @ppos: where to start
 *
 * Returns number of bytes written or error code, as appropriate
 */
अटल sमाप_प्रकार smk_ग_लिखो_direct(काष्ठा file *file, स्थिर अक्षर __user *buf,
				माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा smack_known *skp;
	अक्षर temp[80];
	पूर्णांक i;

	अगर (!smack_privileged(CAP_MAC_ADMIN))
		वापस -EPERM;

	अगर (count >= माप(temp) || count == 0)
		वापस -EINVAL;

	अगर (copy_from_user(temp, buf, count) != 0)
		वापस -EFAULT;

	temp[count] = '\0';

	अगर (माला_पूछो(temp, "%d", &i) != 1)
		वापस -EINVAL;

	/*
	 * Don't do anything if the value hasn't actually changed.
	 * If it is changing reset the level on entries that were
	 * set up to be direct when they were created.
	 */
	अगर (smack_cipso_direct != i) अणु
		mutex_lock(&smack_known_lock);
		list_क्रम_each_entry_rcu(skp, &smack_known_list, list)
			अगर (skp->smk_netlabel.attr.mls.lvl ==
			    smack_cipso_direct)
				skp->smk_netlabel.attr.mls.lvl = i;
		smack_cipso_direct = i;
		mutex_unlock(&smack_known_lock);
	पूर्ण

	वापस count;
पूर्ण

अटल स्थिर काष्ठा file_operations smk_direct_ops = अणु
	.पढ़ो		= smk_पढ़ो_direct,
	.ग_लिखो		= smk_ग_लिखो_direct,
	.llseek		= शेष_llseek,
पूर्ण;

/**
 * smk_पढ़ो_mapped - पढ़ो() क्रम /smack/mapped
 * @filp: file poपूर्णांकer, not actually used
 * @buf: where to put the result
 * @count: maximum to send aदीर्घ
 * @ppos: where to start
 *
 * Returns number of bytes पढ़ो or error code, as appropriate
 */
अटल sमाप_प्रकार smk_पढ़ो_mapped(काष्ठा file *filp, अक्षर __user *buf,
			       माप_प्रकार count, loff_t *ppos)
अणु
	अक्षर temp[80];
	sमाप_प्रकार rc;

	अगर (*ppos != 0)
		वापस 0;

	प्र_लिखो(temp, "%d", smack_cipso_mapped);
	rc = simple_पढ़ो_from_buffer(buf, count, ppos, temp, म_माप(temp));

	वापस rc;
पूर्ण

/**
 * smk_ग_लिखो_mapped - ग_लिखो() क्रम /smack/mapped
 * @file: file poपूर्णांकer, not actually used
 * @buf: where to get the data from
 * @count: bytes sent
 * @ppos: where to start
 *
 * Returns number of bytes written or error code, as appropriate
 */
अटल sमाप_प्रकार smk_ग_लिखो_mapped(काष्ठा file *file, स्थिर अक्षर __user *buf,
				माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा smack_known *skp;
	अक्षर temp[80];
	पूर्णांक i;

	अगर (!smack_privileged(CAP_MAC_ADMIN))
		वापस -EPERM;

	अगर (count >= माप(temp) || count == 0)
		वापस -EINVAL;

	अगर (copy_from_user(temp, buf, count) != 0)
		वापस -EFAULT;

	temp[count] = '\0';

	अगर (माला_पूछो(temp, "%d", &i) != 1)
		वापस -EINVAL;

	/*
	 * Don't do anything if the value hasn't actually changed.
	 * If it is changing reset the level on entries that were
	 * set up to be mapped when they were created.
	 */
	अगर (smack_cipso_mapped != i) अणु
		mutex_lock(&smack_known_lock);
		list_क्रम_each_entry_rcu(skp, &smack_known_list, list)
			अगर (skp->smk_netlabel.attr.mls.lvl ==
			    smack_cipso_mapped)
				skp->smk_netlabel.attr.mls.lvl = i;
		smack_cipso_mapped = i;
		mutex_unlock(&smack_known_lock);
	पूर्ण

	वापस count;
पूर्ण

अटल स्थिर काष्ठा file_operations smk_mapped_ops = अणु
	.पढ़ो		= smk_पढ़ो_mapped,
	.ग_लिखो		= smk_ग_लिखो_mapped,
	.llseek		= शेष_llseek,
पूर्ण;

/**
 * smk_पढ़ो_ambient - पढ़ो() क्रम /smack/ambient
 * @filp: file poपूर्णांकer, not actually used
 * @buf: where to put the result
 * @cn: maximum to send aदीर्घ
 * @ppos: where to start
 *
 * Returns number of bytes पढ़ो or error code, as appropriate
 */
अटल sमाप_प्रकार smk_पढ़ो_ambient(काष्ठा file *filp, अक्षर __user *buf,
				माप_प्रकार cn, loff_t *ppos)
अणु
	sमाप_प्रकार rc;
	पूर्णांक asize;

	अगर (*ppos != 0)
		वापस 0;
	/*
	 * Being careful to aव्योम a problem in the हाल where
	 * smack_net_ambient माला_लो changed in midstream.
	 */
	mutex_lock(&smack_ambient_lock);

	asize = म_माप(smack_net_ambient->smk_known) + 1;

	अगर (cn >= asize)
		rc = simple_पढ़ो_from_buffer(buf, cn, ppos,
					     smack_net_ambient->smk_known,
					     asize);
	अन्यथा
		rc = -EINVAL;

	mutex_unlock(&smack_ambient_lock);

	वापस rc;
पूर्ण

/**
 * smk_ग_लिखो_ambient - ग_लिखो() क्रम /smack/ambient
 * @file: file poपूर्णांकer, not actually used
 * @buf: where to get the data from
 * @count: bytes sent
 * @ppos: where to start
 *
 * Returns number of bytes written or error code, as appropriate
 */
अटल sमाप_प्रकार smk_ग_लिखो_ambient(काष्ठा file *file, स्थिर अक्षर __user *buf,
				 माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा smack_known *skp;
	अक्षर *oldambient;
	अक्षर *data;
	पूर्णांक rc = count;

	अगर (!smack_privileged(CAP_MAC_ADMIN))
		वापस -EPERM;

	/* Enough data must be present */
	अगर (count == 0 || count > PAGE_SIZE)
		वापस -EINVAL;

	data = memdup_user_nul(buf, count);
	अगर (IS_ERR(data))
		वापस PTR_ERR(data);

	skp = smk_import_entry(data, count);
	अगर (IS_ERR(skp)) अणु
		rc = PTR_ERR(skp);
		जाओ out;
	पूर्ण

	mutex_lock(&smack_ambient_lock);

	oldambient = smack_net_ambient->smk_known;
	smack_net_ambient = skp;
	smk_unlbl_ambient(oldambient);

	mutex_unlock(&smack_ambient_lock);

out:
	kमुक्त(data);
	वापस rc;
पूर्ण

अटल स्थिर काष्ठा file_operations smk_ambient_ops = अणु
	.पढ़ो		= smk_पढ़ो_ambient,
	.ग_लिखो		= smk_ग_लिखो_ambient,
	.llseek		= शेष_llseek,
पूर्ण;

/*
 * Seq_file operations क्रम /smack/onlycap
 */
अटल व्योम *onlycap_seq_start(काष्ठा seq_file *s, loff_t *pos)
अणु
	वापस smk_seq_start(s, pos, &smack_onlycap_list);
पूर्ण

अटल व्योम *onlycap_seq_next(काष्ठा seq_file *s, व्योम *v, loff_t *pos)
अणु
	वापस smk_seq_next(s, v, pos, &smack_onlycap_list);
पूर्ण

अटल पूर्णांक onlycap_seq_show(काष्ठा seq_file *s, व्योम *v)
अणु
	काष्ठा list_head *list = v;
	काष्ठा smack_known_list_elem *sklep =
		list_entry_rcu(list, काष्ठा smack_known_list_elem, list);

	seq_माला_दो(s, sklep->smk_label->smk_known);
	seq_अ_दो(s, ' ');

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा seq_operations onlycap_seq_ops = अणु
	.start = onlycap_seq_start,
	.next  = onlycap_seq_next,
	.show  = onlycap_seq_show,
	.stop  = smk_seq_stop,
पूर्ण;

अटल पूर्णांक smk_खोलो_onlycap(काष्ठा inode *inode, काष्ठा file *file)
अणु
	वापस seq_खोलो(file, &onlycap_seq_ops);
पूर्ण

/**
 * smk_list_swap_rcu - swap खुला list with a निजी one in RCU-safe way
 * The caller must hold appropriate mutex to prevent concurrent modअगरications
 * to the खुला list.
 * Private list is assumed to be not accessible to other thपढ़ोs yet.
 *
 * @खुला: खुला list
 * @निजी: निजी list
 */
अटल व्योम smk_list_swap_rcu(काष्ठा list_head *खुला,
			      काष्ठा list_head *निजी)
अणु
	काष्ठा list_head *first, *last;

	अगर (list_empty(खुला)) अणु
		list_splice_init_rcu(निजी, खुला, synchronize_rcu);
	पूर्ण अन्यथा अणु
		/* Remember खुला list beक्रमe replacing it */
		first = खुला->next;
		last = खुला->prev;

		/* Publish निजी list in place of खुला in RCU-safe way */
		निजी->prev->next = खुला;
		निजी->next->prev = खुला;
		rcu_assign_poपूर्णांकer(खुला->next, निजी->next);
		खुला->prev = निजी->prev;

		synchronize_rcu();

		/* When all पढ़ोers are करोne with the old खुला list,
		 * attach it in place of निजी */
		निजी->next = first;
		निजी->prev = last;
		first->prev = निजी;
		last->next = निजी;
	पूर्ण
पूर्ण

/**
 * smk_parse_label_list - parse list of Smack labels, separated by spaces
 *
 * @data: the string to parse
 * @list: destination list
 *
 * Returns zero on success or error code, as appropriate
 */
अटल पूर्णांक smk_parse_label_list(अक्षर *data, काष्ठा list_head *list)
अणु
	अक्षर *tok;
	काष्ठा smack_known *skp;
	काष्ठा smack_known_list_elem *sklep;

	जबतक ((tok = strsep(&data, " ")) != शून्य) अणु
		अगर (!*tok)
			जारी;

		skp = smk_import_entry(tok, 0);
		अगर (IS_ERR(skp))
			वापस PTR_ERR(skp);

		sklep = kzalloc(माप(*sklep), GFP_KERNEL);
		अगर (sklep == शून्य)
			वापस -ENOMEM;

		sklep->smk_label = skp;
		list_add(&sklep->list, list);
	पूर्ण

	वापस 0;
पूर्ण

/**
 * smk_destroy_label_list - destroy a list of smack_known_list_elem
 * @list: header poपूर्णांकer of the list to destroy
 */
व्योम smk_destroy_label_list(काष्ठा list_head *list)
अणु
	काष्ठा smack_known_list_elem *sklep;
	काष्ठा smack_known_list_elem *sklep2;

	list_क्रम_each_entry_safe(sklep, sklep2, list, list)
		kमुक्त(sklep);

	INIT_LIST_HEAD(list);
पूर्ण

/**
 * smk_ग_लिखो_onlycap - ग_लिखो() क्रम smackfs/onlycap
 * @file: file poपूर्णांकer, not actually used
 * @buf: where to get the data from
 * @count: bytes sent
 * @ppos: where to start
 *
 * Returns number of bytes written or error code, as appropriate
 */
अटल sमाप_प्रकार smk_ग_लिखो_onlycap(काष्ठा file *file, स्थिर अक्षर __user *buf,
				 माप_प्रकार count, loff_t *ppos)
अणु
	अक्षर *data;
	LIST_HEAD(list_पंचांगp);
	पूर्णांक rc;

	अगर (!smack_privileged(CAP_MAC_ADMIN))
		वापस -EPERM;

	अगर (count > PAGE_SIZE)
		वापस -EINVAL;

	data = memdup_user_nul(buf, count);
	अगर (IS_ERR(data))
		वापस PTR_ERR(data);

	rc = smk_parse_label_list(data, &list_पंचांगp);
	kमुक्त(data);

	/*
	 * Clear the smack_onlycap on invalid label errors. This means
	 * that we can pass a null string to unset the onlycap value.
	 *
	 * Importing will also reject a label beginning with '-',
	 * so "-usecapabilities" will also work.
	 *
	 * But करो so only on invalid label, not on प्रणाली errors.
	 * The invalid label must be first to count as clearing attempt.
	 */
	अगर (!rc || (rc == -EINVAL && list_empty(&list_पंचांगp))) अणु
		mutex_lock(&smack_onlycap_lock);
		smk_list_swap_rcu(&smack_onlycap_list, &list_पंचांगp);
		mutex_unlock(&smack_onlycap_lock);
		rc = count;
	पूर्ण

	smk_destroy_label_list(&list_पंचांगp);

	वापस rc;
पूर्ण

अटल स्थिर काष्ठा file_operations smk_onlycap_ops = अणु
	.खोलो		= smk_खोलो_onlycap,
	.पढ़ो		= seq_पढ़ो,
	.ग_लिखो		= smk_ग_लिखो_onlycap,
	.llseek		= seq_lseek,
	.release	= seq_release,
पूर्ण;

#अगर_घोषित CONFIG_SECURITY_SMACK_BRINGUP
/**
 * smk_पढ़ो_unconfined - पढ़ो() क्रम smackfs/unconfined
 * @filp: file poपूर्णांकer, not actually used
 * @buf: where to put the result
 * @cn: maximum to send aदीर्घ
 * @ppos: where to start
 *
 * Returns number of bytes पढ़ो or error code, as appropriate
 */
अटल sमाप_प्रकार smk_पढ़ो_unconfined(काष्ठा file *filp, अक्षर __user *buf,
					माप_प्रकार cn, loff_t *ppos)
अणु
	अक्षर *smack = "";
	sमाप_प्रकार rc = -EINVAL;
	पूर्णांक asize;

	अगर (*ppos != 0)
		वापस 0;

	अगर (smack_unconfined != शून्य)
		smack = smack_unconfined->smk_known;

	asize = म_माप(smack) + 1;

	अगर (cn >= asize)
		rc = simple_पढ़ो_from_buffer(buf, cn, ppos, smack, asize);

	वापस rc;
पूर्ण

/**
 * smk_ग_लिखो_unconfined - ग_लिखो() क्रम smackfs/unconfined
 * @file: file poपूर्णांकer, not actually used
 * @buf: where to get the data from
 * @count: bytes sent
 * @ppos: where to start
 *
 * Returns number of bytes written or error code, as appropriate
 */
अटल sमाप_प्रकार smk_ग_लिखो_unconfined(काष्ठा file *file, स्थिर अक्षर __user *buf,
					माप_प्रकार count, loff_t *ppos)
अणु
	अक्षर *data;
	काष्ठा smack_known *skp;
	पूर्णांक rc = count;

	अगर (!smack_privileged(CAP_MAC_ADMIN))
		वापस -EPERM;

	अगर (count > PAGE_SIZE)
		वापस -EINVAL;

	data = memdup_user_nul(buf, count);
	अगर (IS_ERR(data))
		वापस PTR_ERR(data);

	/*
	 * Clear the smack_unconfined on invalid label errors. This means
	 * that we can pass a null string to unset the unconfined value.
	 *
	 * Importing will also reject a label beginning with '-',
	 * so "-confine" will also work.
	 *
	 * But करो so only on invalid label, not on प्रणाली errors.
	 */
	skp = smk_import_entry(data, count);
	अगर (PTR_ERR(skp) == -EINVAL)
		skp = शून्य;
	अन्यथा अगर (IS_ERR(skp)) अणु
		rc = PTR_ERR(skp);
		जाओ मुक्तout;
	पूर्ण

	smack_unconfined = skp;

मुक्तout:
	kमुक्त(data);
	वापस rc;
पूर्ण

अटल स्थिर काष्ठा file_operations smk_unconfined_ops = अणु
	.पढ़ो		= smk_पढ़ो_unconfined,
	.ग_लिखो		= smk_ग_लिखो_unconfined,
	.llseek		= शेष_llseek,
पूर्ण;
#पूर्ण_अगर /* CONFIG_SECURITY_SMACK_BRINGUP */

/**
 * smk_पढ़ो_logging - पढ़ो() क्रम /smack/logging
 * @filp: file poपूर्णांकer, not actually used
 * @buf: where to put the result
 * @count: maximum to send aदीर्घ
 * @ppos: where to start
 *
 * Returns number of bytes पढ़ो or error code, as appropriate
 */
अटल sमाप_प्रकार smk_पढ़ो_logging(काष्ठा file *filp, अक्षर __user *buf,
				माप_प्रकार count, loff_t *ppos)
अणु
	अक्षर temp[32];
	sमाप_प्रकार rc;

	अगर (*ppos != 0)
		वापस 0;

	प्र_लिखो(temp, "%d\n", log_policy);
	rc = simple_पढ़ो_from_buffer(buf, count, ppos, temp, म_माप(temp));
	वापस rc;
पूर्ण

/**
 * smk_ग_लिखो_logging - ग_लिखो() क्रम /smack/logging
 * @file: file poपूर्णांकer, not actually used
 * @buf: where to get the data from
 * @count: bytes sent
 * @ppos: where to start
 *
 * Returns number of bytes written or error code, as appropriate
 */
अटल sमाप_प्रकार smk_ग_लिखो_logging(काष्ठा file *file, स्थिर अक्षर __user *buf,
				माप_प्रकार count, loff_t *ppos)
अणु
	अक्षर temp[32];
	पूर्णांक i;

	अगर (!smack_privileged(CAP_MAC_ADMIN))
		वापस -EPERM;

	अगर (count >= माप(temp) || count == 0)
		वापस -EINVAL;

	अगर (copy_from_user(temp, buf, count) != 0)
		वापस -EFAULT;

	temp[count] = '\0';

	अगर (माला_पूछो(temp, "%d", &i) != 1)
		वापस -EINVAL;
	अगर (i < 0 || i > 3)
		वापस -EINVAL;
	log_policy = i;
	वापस count;
पूर्ण



अटल स्थिर काष्ठा file_operations smk_logging_ops = अणु
	.पढ़ो		= smk_पढ़ो_logging,
	.ग_लिखो		= smk_ग_लिखो_logging,
	.llseek		= शेष_llseek,
पूर्ण;

/*
 * Seq_file पढ़ो operations क्रम /smack/load-self
 */

अटल व्योम *load_self_seq_start(काष्ठा seq_file *s, loff_t *pos)
अणु
	काष्ठा task_smack *tsp = smack_cred(current_cred());

	वापस smk_seq_start(s, pos, &tsp->smk_rules);
पूर्ण

अटल व्योम *load_self_seq_next(काष्ठा seq_file *s, व्योम *v, loff_t *pos)
अणु
	काष्ठा task_smack *tsp = smack_cred(current_cred());

	वापस smk_seq_next(s, v, pos, &tsp->smk_rules);
पूर्ण

अटल पूर्णांक load_self_seq_show(काष्ठा seq_file *s, व्योम *v)
अणु
	काष्ठा list_head *list = v;
	काष्ठा smack_rule *srp =
		list_entry_rcu(list, काष्ठा smack_rule, list);

	smk_rule_show(s, srp, SMK_LABELLEN);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा seq_operations load_self_seq_ops = अणु
	.start = load_self_seq_start,
	.next  = load_self_seq_next,
	.show  = load_self_seq_show,
	.stop  = smk_seq_stop,
पूर्ण;


/**
 * smk_खोलो_load_self - खोलो() क्रम /smack/load-self2
 * @inode: inode काष्ठाure representing file
 * @file: "load" file poपूर्णांकer
 *
 * For पढ़ोing, use load_seq_* seq_file पढ़ोing operations.
 */
अटल पूर्णांक smk_खोलो_load_self(काष्ठा inode *inode, काष्ठा file *file)
अणु
	वापस seq_खोलो(file, &load_self_seq_ops);
पूर्ण

/**
 * smk_ग_लिखो_load_self - ग_लिखो() क्रम /smack/load-self
 * @file: file poपूर्णांकer, not actually used
 * @buf: where to get the data from
 * @count: bytes sent
 * @ppos: where to start - must be 0
 *
 */
अटल sमाप_प्रकार smk_ग_लिखो_load_self(काष्ठा file *file, स्थिर अक्षर __user *buf,
			      माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा task_smack *tsp = smack_cred(current_cred());

	वापस smk_ग_लिखो_rules_list(file, buf, count, ppos, &tsp->smk_rules,
				    &tsp->smk_rules_lock, SMK_FIXED24_FMT);
पूर्ण

अटल स्थिर काष्ठा file_operations smk_load_self_ops = अणु
	.खोलो           = smk_खोलो_load_self,
	.पढ़ो		= seq_पढ़ो,
	.llseek         = seq_lseek,
	.ग_लिखो		= smk_ग_लिखो_load_self,
	.release        = seq_release,
पूर्ण;

/**
 * smk_user_access - handle access check transaction
 * @file: file poपूर्णांकer
 * @buf: data from user space
 * @count: bytes sent
 * @ppos: where to start - must be 0
 * @क्रमmat: /smack/load or /smack/load2 or /smack/change-rule क्रमmat.
 */
अटल sमाप_प्रकार smk_user_access(काष्ठा file *file, स्थिर अक्षर __user *buf,
				माप_प्रकार count, loff_t *ppos, पूर्णांक क्रमmat)
अणु
	काष्ठा smack_parsed_rule rule;
	अक्षर *data;
	पूर्णांक res;

	data = simple_transaction_get(file, buf, count);
	अगर (IS_ERR(data))
		वापस PTR_ERR(data);

	अगर (क्रमmat == SMK_FIXED24_FMT) अणु
		अगर (count < SMK_LOADLEN)
			वापस -EINVAL;
		res = smk_parse_rule(data, &rule, 0);
	पूर्ण अन्यथा अणु
		/*
		 * simple_transaction_get() वापसs null-terminated data
		 */
		res = smk_parse_दीर्घ_rule(data, &rule, 0, 3);
	पूर्ण

	अगर (res >= 0)
		res = smk_access(rule.smk_subject, rule.smk_object,
				 rule.smk_access1, शून्य);
	अन्यथा अगर (res != -ENOENT)
		वापस res;

	/*
	 * smk_access() can वापस a value > 0 in the "bringup" हाल.
	 */
	data[0] = res >= 0 ? '1' : '0';
	data[1] = '\0';

	simple_transaction_set(file, 2);

	अगर (क्रमmat == SMK_FIXED24_FMT)
		वापस SMK_LOADLEN;
	वापस count;
पूर्ण

/**
 * smk_ग_लिखो_access - handle access check transaction
 * @file: file poपूर्णांकer
 * @buf: data from user space
 * @count: bytes sent
 * @ppos: where to start - must be 0
 */
अटल sमाप_प्रकार smk_ग_लिखो_access(काष्ठा file *file, स्थिर अक्षर __user *buf,
				माप_प्रकार count, loff_t *ppos)
अणु
	वापस smk_user_access(file, buf, count, ppos, SMK_FIXED24_FMT);
पूर्ण

अटल स्थिर काष्ठा file_operations smk_access_ops = अणु
	.ग_लिखो		= smk_ग_लिखो_access,
	.पढ़ो		= simple_transaction_पढ़ो,
	.release	= simple_transaction_release,
	.llseek		= generic_file_llseek,
पूर्ण;


/*
 * Seq_file पढ़ो operations क्रम /smack/load2
 */

अटल पूर्णांक load2_seq_show(काष्ठा seq_file *s, व्योम *v)
अणु
	काष्ठा list_head *list = v;
	काष्ठा smack_rule *srp;
	काष्ठा smack_known *skp =
		list_entry_rcu(list, काष्ठा smack_known, list);

	list_क्रम_each_entry_rcu(srp, &skp->smk_rules, list)
		smk_rule_show(s, srp, SMK_LONGLABEL);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा seq_operations load2_seq_ops = अणु
	.start = load2_seq_start,
	.next  = load2_seq_next,
	.show  = load2_seq_show,
	.stop  = smk_seq_stop,
पूर्ण;

/**
 * smk_खोलो_load2 - खोलो() क्रम /smack/load2
 * @inode: inode काष्ठाure representing file
 * @file: "load2" file poपूर्णांकer
 *
 * For पढ़ोing, use load2_seq_* seq_file पढ़ोing operations.
 */
अटल पूर्णांक smk_खोलो_load2(काष्ठा inode *inode, काष्ठा file *file)
अणु
	वापस seq_खोलो(file, &load2_seq_ops);
पूर्ण

/**
 * smk_ग_लिखो_load2 - ग_लिखो() क्रम /smack/load2
 * @file: file poपूर्णांकer, not actually used
 * @buf: where to get the data from
 * @count: bytes sent
 * @ppos: where to start - must be 0
 *
 */
अटल sमाप_प्रकार smk_ग_लिखो_load2(काष्ठा file *file, स्थिर अक्षर __user *buf,
				माप_प्रकार count, loff_t *ppos)
अणु
	/*
	 * Must have privilege.
	 */
	अगर (!smack_privileged(CAP_MAC_ADMIN))
		वापस -EPERM;

	वापस smk_ग_लिखो_rules_list(file, buf, count, ppos, शून्य, शून्य,
				    SMK_LONG_FMT);
पूर्ण

अटल स्थिर काष्ठा file_operations smk_load2_ops = अणु
	.खोलो           = smk_खोलो_load2,
	.पढ़ो		= seq_पढ़ो,
	.llseek         = seq_lseek,
	.ग_लिखो		= smk_ग_लिखो_load2,
	.release        = seq_release,
पूर्ण;

/*
 * Seq_file पढ़ो operations क्रम /smack/load-self2
 */

अटल व्योम *load_self2_seq_start(काष्ठा seq_file *s, loff_t *pos)
अणु
	काष्ठा task_smack *tsp = smack_cred(current_cred());

	वापस smk_seq_start(s, pos, &tsp->smk_rules);
पूर्ण

अटल व्योम *load_self2_seq_next(काष्ठा seq_file *s, व्योम *v, loff_t *pos)
अणु
	काष्ठा task_smack *tsp = smack_cred(current_cred());

	वापस smk_seq_next(s, v, pos, &tsp->smk_rules);
पूर्ण

अटल पूर्णांक load_self2_seq_show(काष्ठा seq_file *s, व्योम *v)
अणु
	काष्ठा list_head *list = v;
	काष्ठा smack_rule *srp =
		list_entry_rcu(list, काष्ठा smack_rule, list);

	smk_rule_show(s, srp, SMK_LONGLABEL);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा seq_operations load_self2_seq_ops = अणु
	.start = load_self2_seq_start,
	.next  = load_self2_seq_next,
	.show  = load_self2_seq_show,
	.stop  = smk_seq_stop,
पूर्ण;

/**
 * smk_खोलो_load_self2 - खोलो() क्रम /smack/load-self2
 * @inode: inode काष्ठाure representing file
 * @file: "load" file poपूर्णांकer
 *
 * For पढ़ोing, use load_seq_* seq_file पढ़ोing operations.
 */
अटल पूर्णांक smk_खोलो_load_self2(काष्ठा inode *inode, काष्ठा file *file)
अणु
	वापस seq_खोलो(file, &load_self2_seq_ops);
पूर्ण

/**
 * smk_ग_लिखो_load_self2 - ग_लिखो() क्रम /smack/load-self2
 * @file: file poपूर्णांकer, not actually used
 * @buf: where to get the data from
 * @count: bytes sent
 * @ppos: where to start - must be 0
 *
 */
अटल sमाप_प्रकार smk_ग_लिखो_load_self2(काष्ठा file *file, स्थिर अक्षर __user *buf,
			      माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा task_smack *tsp = smack_cred(current_cred());

	वापस smk_ग_लिखो_rules_list(file, buf, count, ppos, &tsp->smk_rules,
				    &tsp->smk_rules_lock, SMK_LONG_FMT);
पूर्ण

अटल स्थिर काष्ठा file_operations smk_load_self2_ops = अणु
	.खोलो           = smk_खोलो_load_self2,
	.पढ़ो		= seq_पढ़ो,
	.llseek         = seq_lseek,
	.ग_लिखो		= smk_ग_लिखो_load_self2,
	.release        = seq_release,
पूर्ण;

/**
 * smk_ग_लिखो_access2 - handle access check transaction
 * @file: file poपूर्णांकer
 * @buf: data from user space
 * @count: bytes sent
 * @ppos: where to start - must be 0
 */
अटल sमाप_प्रकार smk_ग_लिखो_access2(काष्ठा file *file, स्थिर अक्षर __user *buf,
					माप_प्रकार count, loff_t *ppos)
अणु
	वापस smk_user_access(file, buf, count, ppos, SMK_LONG_FMT);
पूर्ण

अटल स्थिर काष्ठा file_operations smk_access2_ops = अणु
	.ग_लिखो		= smk_ग_लिखो_access2,
	.पढ़ो		= simple_transaction_पढ़ो,
	.release	= simple_transaction_release,
	.llseek		= generic_file_llseek,
पूर्ण;

/**
 * smk_ग_लिखो_revoke_subj - ग_लिखो() क्रम /smack/revoke-subject
 * @file: file poपूर्णांकer
 * @buf: data from user space
 * @count: bytes sent
 * @ppos: where to start - must be 0
 */
अटल sमाप_प्रकार smk_ग_लिखो_revoke_subj(काष्ठा file *file, स्थिर अक्षर __user *buf,
				माप_प्रकार count, loff_t *ppos)
अणु
	अक्षर *data;
	स्थिर अक्षर *cp;
	काष्ठा smack_known *skp;
	काष्ठा smack_rule *sp;
	काष्ठा list_head *rule_list;
	काष्ठा mutex *rule_lock;
	पूर्णांक rc = count;

	अगर (*ppos != 0)
		वापस -EINVAL;

	अगर (!smack_privileged(CAP_MAC_ADMIN))
		वापस -EPERM;

	अगर (count == 0 || count > SMK_LONGLABEL)
		वापस -EINVAL;

	data = memdup_user(buf, count);
	अगर (IS_ERR(data))
		वापस PTR_ERR(data);

	cp = smk_parse_smack(data, count);
	अगर (IS_ERR(cp)) अणु
		rc = PTR_ERR(cp);
		जाओ out_data;
	पूर्ण

	skp = smk_find_entry(cp);
	अगर (skp == शून्य)
		जाओ out_cp;

	rule_list = &skp->smk_rules;
	rule_lock = &skp->smk_rules_lock;

	mutex_lock(rule_lock);

	list_क्रम_each_entry_rcu(sp, rule_list, list)
		sp->smk_access = 0;

	mutex_unlock(rule_lock);

out_cp:
	kमुक्त(cp);
out_data:
	kमुक्त(data);

	वापस rc;
पूर्ण

अटल स्थिर काष्ठा file_operations smk_revoke_subj_ops = अणु
	.ग_लिखो		= smk_ग_लिखो_revoke_subj,
	.पढ़ो		= simple_transaction_पढ़ो,
	.release	= simple_transaction_release,
	.llseek		= generic_file_llseek,
पूर्ण;

/**
 * smk_init_sysfs - initialize /sys/fs/smackfs
 *
 */
अटल पूर्णांक smk_init_sysfs(व्योम)
अणु
	वापस sysfs_create_mount_poपूर्णांक(fs_kobj, "smackfs");
पूर्ण

/**
 * smk_ग_लिखो_change_rule - ग_लिखो() क्रम /smack/change-rule
 * @file: file poपूर्णांकer
 * @buf: data from user space
 * @count: bytes sent
 * @ppos: where to start - must be 0
 */
अटल sमाप_प्रकार smk_ग_लिखो_change_rule(काष्ठा file *file, स्थिर अक्षर __user *buf,
				माप_प्रकार count, loff_t *ppos)
अणु
	/*
	 * Must have privilege.
	 */
	अगर (!smack_privileged(CAP_MAC_ADMIN))
		वापस -EPERM;

	वापस smk_ग_लिखो_rules_list(file, buf, count, ppos, शून्य, शून्य,
				    SMK_CHANGE_FMT);
पूर्ण

अटल स्थिर काष्ठा file_operations smk_change_rule_ops = अणु
	.ग_लिखो		= smk_ग_लिखो_change_rule,
	.पढ़ो		= simple_transaction_पढ़ो,
	.release	= simple_transaction_release,
	.llseek		= generic_file_llseek,
पूर्ण;

/**
 * smk_पढ़ो_syslog - पढ़ो() क्रम smackfs/syslog
 * @filp: file poपूर्णांकer, not actually used
 * @buf: where to put the result
 * @cn: maximum to send aदीर्घ
 * @ppos: where to start
 *
 * Returns number of bytes पढ़ो or error code, as appropriate
 */
अटल sमाप_प्रकार smk_पढ़ो_syslog(काष्ठा file *filp, अक्षर __user *buf,
				माप_प्रकार cn, loff_t *ppos)
अणु
	काष्ठा smack_known *skp;
	sमाप_प्रकार rc = -EINVAL;
	पूर्णांक asize;

	अगर (*ppos != 0)
		वापस 0;

	अगर (smack_syslog_label == शून्य)
		skp = &smack_known_star;
	अन्यथा
		skp = smack_syslog_label;

	asize = म_माप(skp->smk_known) + 1;

	अगर (cn >= asize)
		rc = simple_पढ़ो_from_buffer(buf, cn, ppos, skp->smk_known,
						asize);

	वापस rc;
पूर्ण

/**
 * smk_ग_लिखो_syslog - ग_लिखो() क्रम smackfs/syslog
 * @file: file poपूर्णांकer, not actually used
 * @buf: where to get the data from
 * @count: bytes sent
 * @ppos: where to start
 *
 * Returns number of bytes written or error code, as appropriate
 */
अटल sमाप_प्रकार smk_ग_लिखो_syslog(काष्ठा file *file, स्थिर अक्षर __user *buf,
				माप_प्रकार count, loff_t *ppos)
अणु
	अक्षर *data;
	काष्ठा smack_known *skp;
	पूर्णांक rc = count;

	अगर (!smack_privileged(CAP_MAC_ADMIN))
		वापस -EPERM;

	/* Enough data must be present */
	अगर (count == 0 || count > PAGE_SIZE)
		वापस -EINVAL;

	data = memdup_user_nul(buf, count);
	अगर (IS_ERR(data))
		वापस PTR_ERR(data);

	skp = smk_import_entry(data, count);
	अगर (IS_ERR(skp))
		rc = PTR_ERR(skp);
	अन्यथा
		smack_syslog_label = skp;

	kमुक्त(data);
	वापस rc;
पूर्ण

अटल स्थिर काष्ठा file_operations smk_syslog_ops = अणु
	.पढ़ो		= smk_पढ़ो_syslog,
	.ग_लिखो		= smk_ग_लिखो_syslog,
	.llseek		= शेष_llseek,
पूर्ण;

/*
 * Seq_file पढ़ो operations क्रम /smack/relabel-self
 */

अटल व्योम *relabel_self_seq_start(काष्ठा seq_file *s, loff_t *pos)
अणु
	काष्ठा task_smack *tsp = smack_cred(current_cred());

	वापस smk_seq_start(s, pos, &tsp->smk_relabel);
पूर्ण

अटल व्योम *relabel_self_seq_next(काष्ठा seq_file *s, व्योम *v, loff_t *pos)
अणु
	काष्ठा task_smack *tsp = smack_cred(current_cred());

	वापस smk_seq_next(s, v, pos, &tsp->smk_relabel);
पूर्ण

अटल पूर्णांक relabel_self_seq_show(काष्ठा seq_file *s, व्योम *v)
अणु
	काष्ठा list_head *list = v;
	काष्ठा smack_known_list_elem *sklep =
		list_entry(list, काष्ठा smack_known_list_elem, list);

	seq_माला_दो(s, sklep->smk_label->smk_known);
	seq_अ_दो(s, ' ');

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा seq_operations relabel_self_seq_ops = अणु
	.start = relabel_self_seq_start,
	.next  = relabel_self_seq_next,
	.show  = relabel_self_seq_show,
	.stop  = smk_seq_stop,
पूर्ण;

/**
 * smk_खोलो_relabel_self - खोलो() क्रम /smack/relabel-self
 * @inode: inode काष्ठाure representing file
 * @file: "relabel-self" file poपूर्णांकer
 *
 * Connect our relabel_self_seq_* operations with /smack/relabel-self
 * file_operations
 */
अटल पूर्णांक smk_खोलो_relabel_self(काष्ठा inode *inode, काष्ठा file *file)
अणु
	वापस seq_खोलो(file, &relabel_self_seq_ops);
पूर्ण

/**
 * smk_ग_लिखो_relabel_self - ग_लिखो() क्रम /smack/relabel-self
 * @file: file poपूर्णांकer, not actually used
 * @buf: where to get the data from
 * @count: bytes sent
 * @ppos: where to start - must be 0
 *
 */
अटल sमाप_प्रकार smk_ग_लिखो_relabel_self(काष्ठा file *file, स्थिर अक्षर __user *buf,
				माप_प्रकार count, loff_t *ppos)
अणु
	अक्षर *data;
	पूर्णांक rc;
	LIST_HEAD(list_पंचांगp);

	/*
	 * Must have privilege.
	 */
	अगर (!smack_privileged(CAP_MAC_ADMIN))
		वापस -EPERM;

	/*
	 * No partial ग_लिखो.
	 * Enough data must be present.
	 */
	अगर (*ppos != 0)
		वापस -EINVAL;
	अगर (count == 0 || count > PAGE_SIZE)
		वापस -EINVAL;

	data = memdup_user_nul(buf, count);
	अगर (IS_ERR(data))
		वापस PTR_ERR(data);

	rc = smk_parse_label_list(data, &list_पंचांगp);
	kमुक्त(data);

	अगर (!rc || (rc == -EINVAL && list_empty(&list_पंचांगp))) अणु
		काष्ठा cred *new;
		काष्ठा task_smack *tsp;

		new = prepare_creds();
		अगर (!new) अणु
			rc = -ENOMEM;
			जाओ out;
		पूर्ण
		tsp = smack_cred(new);
		smk_destroy_label_list(&tsp->smk_relabel);
		list_splice(&list_पंचांगp, &tsp->smk_relabel);
		commit_creds(new);
		वापस count;
	पूर्ण
out:
	smk_destroy_label_list(&list_पंचांगp);
	वापस rc;
पूर्ण

अटल स्थिर काष्ठा file_operations smk_relabel_self_ops = अणु
	.खोलो		= smk_खोलो_relabel_self,
	.पढ़ो		= seq_पढ़ो,
	.llseek		= seq_lseek,
	.ग_लिखो		= smk_ग_लिखो_relabel_self,
	.release	= seq_release,
पूर्ण;

/**
 * smk_पढ़ो_ptrace - पढ़ो() क्रम /smack/ptrace
 * @filp: file poपूर्णांकer, not actually used
 * @buf: where to put the result
 * @count: maximum to send aदीर्घ
 * @ppos: where to start
 *
 * Returns number of bytes पढ़ो or error code, as appropriate
 */
अटल sमाप_प्रकार smk_पढ़ो_ptrace(काष्ठा file *filp, अक्षर __user *buf,
			       माप_प्रकार count, loff_t *ppos)
अणु
	अक्षर temp[32];
	sमाप_प्रकार rc;

	अगर (*ppos != 0)
		वापस 0;

	प्र_लिखो(temp, "%d\n", smack_ptrace_rule);
	rc = simple_पढ़ो_from_buffer(buf, count, ppos, temp, म_माप(temp));
	वापस rc;
पूर्ण

/**
 * smk_ग_लिखो_ptrace - ग_लिखो() क्रम /smack/ptrace
 * @file: file poपूर्णांकer
 * @buf: data from user space
 * @count: bytes sent
 * @ppos: where to start - must be 0
 */
अटल sमाप_प्रकार smk_ग_लिखो_ptrace(काष्ठा file *file, स्थिर अक्षर __user *buf,
				माप_प्रकार count, loff_t *ppos)
अणु
	अक्षर temp[32];
	पूर्णांक i;

	अगर (!smack_privileged(CAP_MAC_ADMIN))
		वापस -EPERM;

	अगर (*ppos != 0 || count >= माप(temp) || count == 0)
		वापस -EINVAL;

	अगर (copy_from_user(temp, buf, count) != 0)
		वापस -EFAULT;

	temp[count] = '\0';

	अगर (माला_पूछो(temp, "%d", &i) != 1)
		वापस -EINVAL;
	अगर (i < SMACK_PTRACE_DEFAULT || i > SMACK_PTRACE_MAX)
		वापस -EINVAL;
	smack_ptrace_rule = i;

	वापस count;
पूर्ण

अटल स्थिर काष्ठा file_operations smk_ptrace_ops = अणु
	.ग_लिखो		= smk_ग_लिखो_ptrace,
	.पढ़ो		= smk_पढ़ो_ptrace,
	.llseek		= शेष_llseek,
पूर्ण;

/**
 * smk_fill_super - fill the smackfs superblock
 * @sb: the empty superblock
 * @fc: unused
 *
 * Fill in the well known entries क्रम the smack fileप्रणाली
 *
 * Returns 0 on success, an error code on failure
 */
अटल पूर्णांक smk_fill_super(काष्ठा super_block *sb, काष्ठा fs_context *fc)
अणु
	पूर्णांक rc;

	अटल स्थिर काष्ठा tree_descr smack_files[] = अणु
		[SMK_LOAD] = अणु
			"load", &smk_load_ops, S_IRUGO|S_IWUSRपूर्ण,
		[SMK_CIPSO] = अणु
			"cipso", &smk_cipso_ops, S_IRUGO|S_IWUSRपूर्ण,
		[SMK_DOI] = अणु
			"doi", &smk_करोi_ops, S_IRUGO|S_IWUSRपूर्ण,
		[SMK_सूचीECT] = अणु
			"direct", &smk_direct_ops, S_IRUGO|S_IWUSRपूर्ण,
		[SMK_AMBIENT] = अणु
			"ambient", &smk_ambient_ops, S_IRUGO|S_IWUSRपूर्ण,
		[SMK_NET4ADDR] = अणु
			"netlabel", &smk_net4addr_ops, S_IRUGO|S_IWUSRपूर्ण,
		[SMK_ONLYCAP] = अणु
			"onlycap", &smk_onlycap_ops, S_IRUGO|S_IWUSRपूर्ण,
		[SMK_LOGGING] = अणु
			"logging", &smk_logging_ops, S_IRUGO|S_IWUSRपूर्ण,
		[SMK_LOAD_SELF] = अणु
			"load-self", &smk_load_self_ops, S_IRUGO|S_IWUGOपूर्ण,
		[SMK_ACCESSES] = अणु
			"access", &smk_access_ops, S_IRUGO|S_IWUGOपूर्ण,
		[SMK_MAPPED] = अणु
			"mapped", &smk_mapped_ops, S_IRUGO|S_IWUSRपूर्ण,
		[SMK_LOAD2] = अणु
			"load2", &smk_load2_ops, S_IRUGO|S_IWUSRपूर्ण,
		[SMK_LOAD_SELF2] = अणु
			"load-self2", &smk_load_self2_ops, S_IRUGO|S_IWUGOपूर्ण,
		[SMK_ACCESS2] = अणु
			"access2", &smk_access2_ops, S_IRUGO|S_IWUGOपूर्ण,
		[SMK_CIPSO2] = अणु
			"cipso2", &smk_cipso2_ops, S_IRUGO|S_IWUSRपूर्ण,
		[SMK_REVOKE_SUBJ] = अणु
			"revoke-subject", &smk_revoke_subj_ops,
			S_IRUGO|S_IWUSRपूर्ण,
		[SMK_CHANGE_RULE] = अणु
			"change-rule", &smk_change_rule_ops, S_IRUGO|S_IWUSRपूर्ण,
		[SMK_SYSLOG] = अणु
			"syslog", &smk_syslog_ops, S_IRUGO|S_IWUSRपूर्ण,
		[SMK_PTRACE] = अणु
			"ptrace", &smk_ptrace_ops, S_IRUGO|S_IWUSRपूर्ण,
#अगर_घोषित CONFIG_SECURITY_SMACK_BRINGUP
		[SMK_UNCONFINED] = अणु
			"unconfined", &smk_unconfined_ops, S_IRUGO|S_IWUSRपूर्ण,
#पूर्ण_अगर
#अगर IS_ENABLED(CONFIG_IPV6)
		[SMK_NET6ADDR] = अणु
			"ipv6host", &smk_net6addr_ops, S_IRUGO|S_IWUSRपूर्ण,
#पूर्ण_अगर /* CONFIG_IPV6 */
		[SMK_RELABEL_SELF] = अणु
			"relabel-self", &smk_relabel_self_ops,
				S_IRUGO|S_IWUGOपूर्ण,
		/* last one */
			अणु""पूर्ण
	पूर्ण;

	rc = simple_fill_super(sb, SMACK_MAGIC, smack_files);
	अगर (rc != 0) अणु
		prपूर्णांकk(KERN_ERR "%s failed %d while creating inodes\n",
			__func__, rc);
		वापस rc;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * smk_get_tree - get the smackfs superblock
 * @fc: The mount context, including any options
 *
 * Just passes everything aदीर्घ.
 *
 * Returns what the lower level code करोes.
 */
अटल पूर्णांक smk_get_tree(काष्ठा fs_context *fc)
अणु
	वापस get_tree_single(fc, smk_fill_super);
पूर्ण

अटल स्थिर काष्ठा fs_context_operations smk_context_ops = अणु
	.get_tree	= smk_get_tree,
पूर्ण;

/**
 * smk_init_fs_context - Initialise a fileप्रणाली context क्रम smackfs
 * @fc: The blank mount context
 */
अटल पूर्णांक smk_init_fs_context(काष्ठा fs_context *fc)
अणु
	fc->ops = &smk_context_ops;
	वापस 0;
पूर्ण

अटल काष्ठा file_प्रणाली_type smk_fs_type = अणु
	.name		= "smackfs",
	.init_fs_context = smk_init_fs_context,
	.समाप्त_sb	= समाप्त_litter_super,
पूर्ण;

अटल काष्ठा vfsmount *smackfs_mount;

/**
 * init_smk_fs - get the smackfs superblock
 *
 * रेजिस्टर the smackfs
 *
 * Do not रेजिस्टर smackfs अगर Smack wasn't enabled
 * on boot. We can not put this method normally under the
 * smack_init() code path since the security subप्रणाली get
 * initialized beक्रमe the vfs caches.
 *
 * Returns true अगर we were not chosen on boot or अगर
 * we were chosen and fileप्रणाली registration succeeded.
 */
अटल पूर्णांक __init init_smk_fs(व्योम)
अणु
	पूर्णांक err;
	पूर्णांक rc;

	अगर (smack_enabled == 0)
		वापस 0;

	err = smk_init_sysfs();
	अगर (err)
		prपूर्णांकk(KERN_ERR "smackfs: sysfs mountpoint problem.\n");

	err = रेजिस्टर_fileप्रणाली(&smk_fs_type);
	अगर (!err) अणु
		smackfs_mount = kern_mount(&smk_fs_type);
		अगर (IS_ERR(smackfs_mount)) अणु
			prपूर्णांकk(KERN_ERR "smackfs:  could not mount!\n");
			err = PTR_ERR(smackfs_mount);
			smackfs_mount = शून्य;
		पूर्ण
	पूर्ण

	smk_cipso_करोi();
	smk_unlbl_ambient(शून्य);

	rc = smack_populate_secattr(&smack_known_न्यूनमान);
	अगर (err == 0 && rc < 0)
		err = rc;
	rc = smack_populate_secattr(&smack_known_hat);
	अगर (err == 0 && rc < 0)
		err = rc;
	rc = smack_populate_secattr(&smack_known_huh);
	अगर (err == 0 && rc < 0)
		err = rc;
	rc = smack_populate_secattr(&smack_known_star);
	अगर (err == 0 && rc < 0)
		err = rc;
	rc = smack_populate_secattr(&smack_known_web);
	अगर (err == 0 && rc < 0)
		err = rc;

	वापस err;
पूर्ण

__initcall(init_smk_fs);
