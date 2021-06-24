<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2007 Casey Schaufler <हालy@schaufler-ca.com>
 *
 * Author:
 *      Casey Schaufler <हालy@schaufler-ca.com>
 */

#समावेश <linux/types.h>
#समावेश <linux/slab.h>
#समावेश <linux/fs.h>
#समावेश <linux/sched.h>
#समावेश "smack.h"

काष्ठा smack_known smack_known_huh = अणु
	.smk_known	= "?",
	.smk_secid	= 2,
पूर्ण;

काष्ठा smack_known smack_known_hat = अणु
	.smk_known	= "^",
	.smk_secid	= 3,
पूर्ण;

काष्ठा smack_known smack_known_star = अणु
	.smk_known	= "*",
	.smk_secid	= 4,
पूर्ण;

काष्ठा smack_known smack_known_न्यूनमान = अणु
	.smk_known	= "_",
	.smk_secid	= 5,
पूर्ण;

काष्ठा smack_known smack_known_web = अणु
	.smk_known	= "@",
	.smk_secid	= 7,
पूर्ण;

LIST_HEAD(smack_known_list);

/*
 * The initial value needs to be bigger than any of the
 * known values above.
 */
अटल u32 smack_next_secid = 10;

/*
 * what events करो we log
 * can be overwritten at run-समय by /smack/logging
 */
पूर्णांक log_policy = SMACK_AUDIT_DENIED;

/**
 * smk_access_entry - look up matching access rule
 * @subject_label: a poपूर्णांकer to the subject's Smack label
 * @object_label: a poपूर्णांकer to the object's Smack label
 * @rule_list: the list of rules to search
 *
 * This function looks up the subject/object pair in the
 * access rule list and वापसs the access mode. If no
 * entry is found वापसs -ENOENT.
 *
 * NOTE:
 *
 * Earlier versions of this function allowed क्रम labels that
 * were not on the label list. This was करोne to allow क्रम
 * labels to come over the network that had never been seen
 * beक्रमe on this host. Unless the receiving socket has the
 * star label this will always result in a failure check. The
 * star labeled socket हाल is now handled in the networking
 * hooks so there is no हाल where the label is not on the
 * label list. Checking to see अगर the address of two labels
 * is the same is now a reliable test.
 *
 * Do the object check first because that is more
 * likely to dअगरfer.
 *
 * Allowing ग_लिखो access implies allowing locking.
 */
पूर्णांक smk_access_entry(अक्षर *subject_label, अक्षर *object_label,
			काष्ठा list_head *rule_list)
अणु
	पूर्णांक may = -ENOENT;
	काष्ठा smack_rule *srp;

	list_क्रम_each_entry_rcu(srp, rule_list, list) अणु
		अगर (srp->smk_object->smk_known == object_label &&
		    srp->smk_subject->smk_known == subject_label) अणु
			may = srp->smk_access;
			अवरोध;
		पूर्ण
	पूर्ण

	/*
	 * MAY_WRITE implies MAY_LOCK.
	 */
	अगर ((may & MAY_WRITE) == MAY_WRITE)
		may |= MAY_LOCK;
	वापस may;
पूर्ण

/**
 * smk_access - determine अगर a subject has a specअगरic access to an object
 * @subject: a poपूर्णांकer to the subject's Smack label entry
 * @object: a poपूर्णांकer to the object's Smack label entry
 * @request: the access requested, in "MAY" क्रमmat
 * @a : a poपूर्णांकer to the audit data
 *
 * This function looks up the subject/object pair in the
 * access rule list and वापसs 0 अगर the access is permitted,
 * non zero otherwise.
 *
 * Smack labels are shared on smack_list
 */
पूर्णांक smk_access(काष्ठा smack_known *subject, काष्ठा smack_known *object,
	       पूर्णांक request, काष्ठा smk_audit_info *a)
अणु
	पूर्णांक may = MAY_NOT;
	पूर्णांक rc = 0;

	/*
	 * Hardcoded comparisons.
	 */
	/*
	 * A star subject can't access any object.
	 */
	अगर (subject == &smack_known_star) अणु
		rc = -EACCES;
		जाओ out_audit;
	पूर्ण
	/*
	 * An पूर्णांकernet object can be accessed by any subject.
	 * Tasks cannot be asचिन्हित the पूर्णांकernet label.
	 * An पूर्णांकernet subject can access any object.
	 */
	अगर (object == &smack_known_web || subject == &smack_known_web)
		जाओ out_audit;
	/*
	 * A star object can be accessed by any subject.
	 */
	अगर (object == &smack_known_star)
		जाओ out_audit;
	/*
	 * An object can be accessed in any way by a subject
	 * with the same label.
	 */
	अगर (subject->smk_known == object->smk_known)
		जाओ out_audit;
	/*
	 * A hat subject can पढ़ो or lock any object.
	 * A न्यूनमान object can be पढ़ो or locked by any subject.
	 */
	अगर ((request & MAY_ANYREAD) == request ||
	    (request & MAY_LOCK) == request) अणु
		अगर (object == &smack_known_न्यूनमान)
			जाओ out_audit;
		अगर (subject == &smack_known_hat)
			जाओ out_audit;
	पूर्ण
	/*
	 * Beyond here an explicit relationship is required.
	 * If the requested access is contained in the available
	 * access (e.g. पढ़ो is included in पढ़ोग_लिखो) it's
	 * good. A negative response from smk_access_entry()
	 * indicates there is no entry क्रम this pair.
	 */
	rcu_पढ़ो_lock();
	may = smk_access_entry(subject->smk_known, object->smk_known,
			       &subject->smk_rules);
	rcu_पढ़ो_unlock();

	अगर (may <= 0 || (request & may) != request) अणु
		rc = -EACCES;
		जाओ out_audit;
	पूर्ण
#अगर_घोषित CONFIG_SECURITY_SMACK_BRINGUP
	/*
	 * Return a positive value अगर using bringup mode.
	 * This allows the hooks to identअगरy checks that
	 * succeed because of "b" rules.
	 */
	अगर (may & MAY_BRINGUP)
		rc = SMACK_BRINGUP_ALLOW;
#पूर्ण_अगर

out_audit:

#अगर_घोषित CONFIG_SECURITY_SMACK_BRINGUP
	अगर (rc < 0) अणु
		अगर (object == smack_unconfined)
			rc = SMACK_UNCONFINED_OBJECT;
		अगर (subject == smack_unconfined)
			rc = SMACK_UNCONFINED_SUBJECT;
	पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_AUDIT
	अगर (a)
		smack_log(subject->smk_known, object->smk_known,
			  request, rc, a);
#पूर्ण_अगर

	वापस rc;
पूर्ण

/**
 * smk_tskacc - determine अगर a task has a specअगरic access to an object
 * @tsp: a poपूर्णांकer to the subject's task
 * @obj_known: a poपूर्णांकer to the object's label entry
 * @mode: the access requested, in "MAY" क्रमmat
 * @a : common audit data
 *
 * This function checks the subject task's label/object label pair
 * in the access rule list and वापसs 0 अगर the access is permitted,
 * non zero otherwise. It allows that the task may have the capability
 * to override the rules.
 */
पूर्णांक smk_tskacc(काष्ठा task_smack *tsp, काष्ठा smack_known *obj_known,
	       u32 mode, काष्ठा smk_audit_info *a)
अणु
	काष्ठा smack_known *sbj_known = smk_of_task(tsp);
	पूर्णांक may;
	पूर्णांक rc;

	/*
	 * Check the global rule list
	 */
	rc = smk_access(sbj_known, obj_known, mode, शून्य);
	अगर (rc >= 0) अणु
		/*
		 * If there is an entry in the task's rule list
		 * it can further restrict access.
		 */
		may = smk_access_entry(sbj_known->smk_known,
				       obj_known->smk_known,
				       &tsp->smk_rules);
		अगर (may < 0)
			जाओ out_audit;
		अगर ((mode & may) == mode)
			जाओ out_audit;
		rc = -EACCES;
	पूर्ण

	/*
	 * Allow क्रम priviliged to override policy.
	 */
	अगर (rc != 0 && smack_privileged(CAP_MAC_OVERRIDE))
		rc = 0;

out_audit:
#अगर_घोषित CONFIG_AUDIT
	अगर (a)
		smack_log(sbj_known->smk_known, obj_known->smk_known,
			  mode, rc, a);
#पूर्ण_अगर
	वापस rc;
पूर्ण

/**
 * smk_curacc - determine अगर current has a specअगरic access to an object
 * @obj_known: a poपूर्णांकer to the object's Smack label entry
 * @mode: the access requested, in "MAY" क्रमmat
 * @a : common audit data
 *
 * This function checks the current subject label/object label pair
 * in the access rule list and वापसs 0 अगर the access is permitted,
 * non zero otherwise. It allows that current may have the capability
 * to override the rules.
 */
पूर्णांक smk_curacc(काष्ठा smack_known *obj_known,
	       u32 mode, काष्ठा smk_audit_info *a)
अणु
	काष्ठा task_smack *tsp = smack_cred(current_cred());

	वापस smk_tskacc(tsp, obj_known, mode, a);
पूर्ण

#अगर_घोषित CONFIG_AUDIT
/**
 * smack_str_from_perm : helper to transalate an पूर्णांक to a
 * पढ़ोable string
 * @string : the string to fill
 * @access : the पूर्णांक
 *
 */
अटल अंतरभूत व्योम smack_str_from_perm(अक्षर *string, पूर्णांक access)
अणु
	पूर्णांक i = 0;

	अगर (access & MAY_READ)
		string[i++] = 'r';
	अगर (access & MAY_WRITE)
		string[i++] = 'w';
	अगर (access & MAY_EXEC)
		string[i++] = 'x';
	अगर (access & MAY_APPEND)
		string[i++] = 'a';
	अगर (access & MAY_TRANSMUTE)
		string[i++] = 't';
	अगर (access & MAY_LOCK)
		string[i++] = 'l';
	string[i] = '\0';
पूर्ण
/**
 * smack_log_callback - SMACK specअगरic inक्रमmation
 * will be called by generic audit code
 * @ab : the audit_buffer
 * @a  : audit_data
 *
 */
अटल व्योम smack_log_callback(काष्ठा audit_buffer *ab, व्योम *a)
अणु
	काष्ठा common_audit_data *ad = a;
	काष्ठा smack_audit_data *sad = ad->smack_audit_data;
	audit_log_क्रमmat(ab, "lsm=SMACK fn=%s action=%s",
			 ad->smack_audit_data->function,
			 sad->result ? "denied" : "granted");
	audit_log_क्रमmat(ab, " subject=");
	audit_log_untrustedstring(ab, sad->subject);
	audit_log_क्रमmat(ab, " object=");
	audit_log_untrustedstring(ab, sad->object);
	अगर (sad->request[0] == '\0')
		audit_log_क्रमmat(ab, " labels_differ");
	अन्यथा
		audit_log_क्रमmat(ab, " requested=%s", sad->request);
पूर्ण

/**
 *  smack_log - Audit the granting or denial of permissions.
 *  @subject_label : smack label of the requester
 *  @object_label  : smack label of the object being accessed
 *  @request: requested permissions
 *  @result: result from smk_access
 *  @a:  auxiliary audit data
 *
 * Audit the granting or denial of permissions in accordance
 * with the policy.
 */
व्योम smack_log(अक्षर *subject_label, अक्षर *object_label, पूर्णांक request,
	       पूर्णांक result, काष्ठा smk_audit_info *ad)
अणु
#अगर_घोषित CONFIG_SECURITY_SMACK_BRINGUP
	अक्षर request_buffer[SMK_NUM_ACCESS_TYPE + 5];
#अन्यथा
	अक्षर request_buffer[SMK_NUM_ACCESS_TYPE + 1];
#पूर्ण_अगर
	काष्ठा smack_audit_data *sad;
	काष्ठा common_audit_data *a = &ad->a;

	/* check अगर we have to log the current event */
	अगर (result < 0 && (log_policy & SMACK_AUDIT_DENIED) == 0)
		वापस;
	अगर (result == 0 && (log_policy & SMACK_AUDIT_ACCEPT) == 0)
		वापस;

	sad = a->smack_audit_data;

	अगर (sad->function == शून्य)
		sad->function = "unknown";

	/* end preparing the audit data */
	smack_str_from_perm(request_buffer, request);
	sad->subject = subject_label;
	sad->object  = object_label;
#अगर_घोषित CONFIG_SECURITY_SMACK_BRINGUP
	/*
	 * The result may be positive in bringup mode.
	 * A positive result is an allow, but not क्रम normal reasons.
	 * Mark it as successful, but करोn't filter it out even अगर
	 * the logging policy says to करो so.
	 */
	अगर (result == SMACK_UNCONFINED_SUBJECT)
		म_जोड़ो(request_buffer, "(US)");
	अन्यथा अगर (result == SMACK_UNCONFINED_OBJECT)
		म_जोड़ो(request_buffer, "(UO)");

	अगर (result > 0)
		result = 0;
#पूर्ण_अगर
	sad->request = request_buffer;
	sad->result  = result;

	common_lsm_audit(a, smack_log_callback, शून्य);
पूर्ण
#अन्यथा /* #अगर_घोषित CONFIG_AUDIT */
व्योम smack_log(अक्षर *subject_label, अक्षर *object_label, पूर्णांक request,
               पूर्णांक result, काष्ठा smk_audit_info *ad)
अणु
पूर्ण
#पूर्ण_अगर

DEFINE_MUTEX(smack_known_lock);

काष्ठा hlist_head smack_known_hash[SMACK_HASH_SLOTS];

/**
 * smk_insert_entry - insert a smack label पूर्णांकo a hash map,
 *
 * this function must be called under smack_known_lock
 */
व्योम smk_insert_entry(काष्ठा smack_known *skp)
अणु
	अचिन्हित पूर्णांक hash;
	काष्ठा hlist_head *head;

	hash = full_name_hash(शून्य, skp->smk_known, म_माप(skp->smk_known));
	head = &smack_known_hash[hash & (SMACK_HASH_SLOTS - 1)];

	hlist_add_head_rcu(&skp->smk_hashed, head);
	list_add_rcu(&skp->list, &smack_known_list);
पूर्ण

/**
 * smk_find_entry - find a label on the list, वापस the list entry
 * @string: a text string that might be a Smack label
 *
 * Returns a poपूर्णांकer to the entry in the label list that
 * matches the passed string or शून्य अगर not found.
 */
काष्ठा smack_known *smk_find_entry(स्थिर अक्षर *string)
अणु
	अचिन्हित पूर्णांक hash;
	काष्ठा hlist_head *head;
	काष्ठा smack_known *skp;

	hash = full_name_hash(शून्य, string, म_माप(string));
	head = &smack_known_hash[hash & (SMACK_HASH_SLOTS - 1)];

	hlist_क्रम_each_entry_rcu(skp, head, smk_hashed)
		अगर (म_भेद(skp->smk_known, string) == 0)
			वापस skp;

	वापस शून्य;
पूर्ण

/**
 * smk_parse_smack - parse smack label from a text string
 * @string: a text string that might contain a Smack label
 * @len: the maximum size, or zero अगर it is शून्य terminated.
 *
 * Returns a poपूर्णांकer to the clean label or an error code.
 */
अक्षर *smk_parse_smack(स्थिर अक्षर *string, पूर्णांक len)
अणु
	अक्षर *smack;
	पूर्णांक i;

	अगर (len <= 0)
		len = म_माप(string) + 1;

	/*
	 * Reserve a leading '-' as an indicator that
	 * this isn't a label, but an option to पूर्णांकerfaces
	 * including /smack/cipso and /smack/cipso2
	 */
	अगर (string[0] == '-')
		वापस ERR_PTR(-EINVAL);

	क्रम (i = 0; i < len; i++)
		अगर (string[i] > '~' || string[i] <= ' ' || string[i] == '/' ||
		    string[i] == '"' || string[i] == '\\' || string[i] == '\'')
			अवरोध;

	अगर (i == 0 || i >= SMK_LONGLABEL)
		वापस ERR_PTR(-EINVAL);

	smack = kzalloc(i + 1, GFP_NOFS);
	अगर (smack == शून्य)
		वापस ERR_PTR(-ENOMEM);

	म_नकलन(smack, string, i);

	वापस smack;
पूर्ण

/**
 * smk_netlbl_mls - convert a catset to netlabel mls categories
 * @catset: the Smack categories
 * @sap: where to put the netlabel categories
 *
 * Allocates and fills attr.mls
 * Returns 0 on success, error code on failure.
 */
पूर्णांक smk_netlbl_mls(पूर्णांक level, अक्षर *catset, काष्ठा netlbl_lsm_secattr *sap,
			पूर्णांक len)
अणु
	अचिन्हित अक्षर *cp;
	अचिन्हित अक्षर m;
	पूर्णांक cat;
	पूर्णांक rc;
	पूर्णांक byte;

	sap->flags |= NETLBL_SECATTR_MLS_CAT;
	sap->attr.mls.lvl = level;
	sap->attr.mls.cat = शून्य;

	क्रम (cat = 1, cp = catset, byte = 0; byte < len; cp++, byte++)
		क्रम (m = 0x80; m != 0; m >>= 1, cat++) अणु
			अगर ((m & *cp) == 0)
				जारी;
			rc = netlbl_caपंचांगap_setbit(&sap->attr.mls.cat,
						  cat, GFP_NOFS);
			अगर (rc < 0) अणु
				netlbl_caपंचांगap_मुक्त(sap->attr.mls.cat);
				वापस rc;
			पूर्ण
		पूर्ण

	वापस 0;
पूर्ण

/**
 * smack_populate_secattr - fill in the smack_known netlabel inक्रमmation
 * @skp: poपूर्णांकer to the काष्ठाure to fill
 *
 * Populate the netlabel secattr काष्ठाure क्रम a Smack label.
 *
 * Returns 0 unless creating the category mapping fails
 */
पूर्णांक smack_populate_secattr(काष्ठा smack_known *skp)
अणु
	पूर्णांक slen;

	skp->smk_netlabel.attr.secid = skp->smk_secid;
	skp->smk_netlabel.करोमुख्य = skp->smk_known;
	skp->smk_netlabel.cache = netlbl_secattr_cache_alloc(GFP_ATOMIC);
	अगर (skp->smk_netlabel.cache != शून्य) अणु
		skp->smk_netlabel.flags |= NETLBL_SECATTR_CACHE;
		skp->smk_netlabel.cache->मुक्त = शून्य;
		skp->smk_netlabel.cache->data = skp;
	पूर्ण
	skp->smk_netlabel.flags |= NETLBL_SECATTR_SECID |
				   NETLBL_SECATTR_MLS_LVL |
				   NETLBL_SECATTR_DOMAIN;
	/*
	 * If direct labeling works use it.
	 * Otherwise use mapped labeling.
	 */
	slen = म_माप(skp->smk_known);
	अगर (slen < SMK_CIPSOLEN)
		वापस smk_netlbl_mls(smack_cipso_direct, skp->smk_known,
				      &skp->smk_netlabel, slen);

	वापस smk_netlbl_mls(smack_cipso_mapped, (अक्षर *)&skp->smk_secid,
			      &skp->smk_netlabel, माप(skp->smk_secid));
पूर्ण

/**
 * smk_import_entry - import a label, वापस the list entry
 * @string: a text string that might be a Smack label
 * @len: the maximum size, or zero अगर it is शून्य terminated.
 *
 * Returns a poपूर्णांकer to the entry in the label list that
 * matches the passed string, adding it अगर necessary,
 * or an error code.
 */
काष्ठा smack_known *smk_import_entry(स्थिर अक्षर *string, पूर्णांक len)
अणु
	काष्ठा smack_known *skp;
	अक्षर *smack;
	पूर्णांक rc;

	smack = smk_parse_smack(string, len);
	अगर (IS_ERR(smack))
		वापस ERR_CAST(smack);

	mutex_lock(&smack_known_lock);

	skp = smk_find_entry(smack);
	अगर (skp != शून्य)
		जाओ मुक्तout;

	skp = kzalloc(माप(*skp), GFP_NOFS);
	अगर (skp == शून्य) अणु
		skp = ERR_PTR(-ENOMEM);
		जाओ मुक्तout;
	पूर्ण

	skp->smk_known = smack;
	skp->smk_secid = smack_next_secid++;

	rc = smack_populate_secattr(skp);
	अगर (rc >= 0) अणु
		INIT_LIST_HEAD(&skp->smk_rules);
		mutex_init(&skp->smk_rules_lock);
		/*
		 * Make sure that the entry is actually
		 * filled beक्रमe putting it on the list.
		 */
		smk_insert_entry(skp);
		जाओ unlockout;
	पूर्ण
	kमुक्त(skp);
	skp = ERR_PTR(rc);
मुक्तout:
	kमुक्त(smack);
unlockout:
	mutex_unlock(&smack_known_lock);

	वापस skp;
पूर्ण

/**
 * smack_from_secid - find the Smack label associated with a secid
 * @secid: an पूर्णांकeger that might be associated with a Smack label
 *
 * Returns a poपूर्णांकer to the appropriate Smack label entry अगर there is one,
 * otherwise a poपूर्णांकer to the invalid Smack label.
 */
काष्ठा smack_known *smack_from_secid(स्थिर u32 secid)
अणु
	काष्ठा smack_known *skp;

	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(skp, &smack_known_list, list) अणु
		अगर (skp->smk_secid == secid) अणु
			rcu_पढ़ो_unlock();
			वापस skp;
		पूर्ण
	पूर्ण

	/*
	 * If we got this far someone asked क्रम the translation
	 * of a secid that is not on the list.
	 */
	rcu_पढ़ो_unlock();
	वापस &smack_known_huh;
पूर्ण

/*
 * Unless a process is running with one of these labels
 * even having CAP_MAC_OVERRIDE isn't enough to grant
 * privilege to violate MAC policy. If no labels are
 * designated (the empty list हाल) capabilities apply to
 * everyone.
 */
LIST_HEAD(smack_onlycap_list);
DEFINE_MUTEX(smack_onlycap_lock);

/**
 * smack_privileged_cred - are all privilege requirements met by cred
 * @cap: The requested capability
 * @cred: the credential to use
 *
 * Is the task privileged and allowed to be privileged
 * by the onlycap rule.
 *
 * Returns true अगर the task is allowed to be privileged, false अगर it's not.
 */
bool smack_privileged_cred(पूर्णांक cap, स्थिर काष्ठा cred *cred)
अणु
	काष्ठा task_smack *tsp = smack_cred(cred);
	काष्ठा smack_known *skp = tsp->smk_task;
	काष्ठा smack_known_list_elem *sklep;
	पूर्णांक rc;

	rc = cap_capable(cred, &init_user_ns, cap, CAP_OPT_NONE);
	अगर (rc)
		वापस false;

	rcu_पढ़ो_lock();
	अगर (list_empty(&smack_onlycap_list)) अणु
		rcu_पढ़ो_unlock();
		वापस true;
	पूर्ण

	list_क्रम_each_entry_rcu(sklep, &smack_onlycap_list, list) अणु
		अगर (sklep->smk_label == skp) अणु
			rcu_पढ़ो_unlock();
			वापस true;
		पूर्ण
	पूर्ण
	rcu_पढ़ो_unlock();

	वापस false;
पूर्ण

/**
 * smack_privileged - are all privilege requirements met
 * @cap: The requested capability
 *
 * Is the task privileged and allowed to be privileged
 * by the onlycap rule.
 *
 * Returns true अगर the task is allowed to be privileged, false अगर it's not.
 */
bool smack_privileged(पूर्णांक cap)
अणु
	/*
	 * Kernel thपढ़ोs may not have credentials we can use.
	 * The io_uring kernel thपढ़ोs करो have reliable credentials.
	 */
	अगर ((current->flags & (PF_KTHREAD | PF_IO_WORKER)) == PF_KTHREAD)
		वापस true;

	वापस smack_privileged_cred(cap, current_cred());
पूर्ण
