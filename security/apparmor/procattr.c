<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * AppArmor security module
 *
 * This file contains AppArmor /proc/<pid>/attr/ पूर्णांकerface functions
 *
 * Copyright (C) 1998-2008 Novell/SUSE
 * Copyright 2009-2010 Canonical Ltd.
 */

#समावेश "include/apparmor.h"
#समावेश "include/cred.h"
#समावेश "include/policy.h"
#समावेश "include/policy_ns.h"
#समावेश "include/domain.h"
#समावेश "include/procattr.h"


/**
 * aa_getprocattr - Return the profile inक्रमmation क्रम @profile
 * @profile: the profile to prपूर्णांक profile info about  (NOT शून्य)
 * @string: Returns - string containing the profile info (NOT शून्य)
 *
 * Returns: length of @string on success अन्यथा error on failure
 *
 * Requires: profile != शून्य
 *
 * Creates a string containing the namespace_name://profile_name क्रम
 * @profile.
 *
 * Returns: size of string placed in @string अन्यथा error code on failure
 */
पूर्णांक aa_getprocattr(काष्ठा aa_label *label, अक्षर **string)
अणु
	काष्ठा aa_ns *ns = labels_ns(label);
	काष्ठा aa_ns *current_ns = aa_get_current_ns();
	पूर्णांक len;

	अगर (!aa_ns_visible(current_ns, ns, true)) अणु
		aa_put_ns(current_ns);
		वापस -EACCES;
	पूर्ण

	len = aa_label_snxprपूर्णांक(शून्य, 0, current_ns, label,
				FLAG_SHOW_MODE | FLAG_VIEW_SUBNS |
				FLAG_HIDDEN_UNCONFINED);
	AA_BUG(len < 0);

	*string = kदो_स्मृति(len + 2, GFP_KERNEL);
	अगर (!*string) अणु
		aa_put_ns(current_ns);
		वापस -ENOMEM;
	पूर्ण

	len = aa_label_snxprपूर्णांक(*string, len + 2, current_ns, label,
				FLAG_SHOW_MODE | FLAG_VIEW_SUBNS |
				FLAG_HIDDEN_UNCONFINED);
	अगर (len < 0) अणु
		aa_put_ns(current_ns);
		वापस len;
	पूर्ण

	(*string)[len] = '\n';
	(*string)[len + 1] = 0;

	aa_put_ns(current_ns);
	वापस len + 1;
पूर्ण

/**
 * split_token_from_name - separate a string of क्रमm  <token>^<name>
 * @op: operation being checked
 * @args: string to parse  (NOT शून्य)
 * @token: stores वापसed parsed token value  (NOT शून्य)
 *
 * Returns: start position of name after token अन्यथा शून्य on failure
 */
अटल अक्षर *split_token_from_name(स्थिर अक्षर *op, अक्षर *args, u64 *token)
अणु
	अक्षर *name;

	*token = simple_म_से_अदीर्घl(args, &name, 16);
	अगर ((name == args) || *name != '^') अणु
		AA_ERROR("%s: Invalid input '%s'", op, args);
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	name++;			/* skip ^ */
	अगर (!*name)
		name = शून्य;
	वापस name;
पूर्ण

/**
 * aa_setprocattr_chagnehat - handle procattr पूर्णांकerface to change_hat
 * @args: args received from writing to /proc/<pid>/attr/current (NOT शून्य)
 * @size: size of the args
 * @flags: set of flags governing behavior
 *
 * Returns: %0 or error code अगर change_hat fails
 */
पूर्णांक aa_setprocattr_changehat(अक्षर *args, माप_प्रकार size, पूर्णांक flags)
अणु
	अक्षर *hat;
	u64 token;
	स्थिर अक्षर *hats[16];		/* current hard limit on # of names */
	पूर्णांक count = 0;

	hat = split_token_from_name(OP_CHANGE_HAT, args, &token);
	अगर (IS_ERR(hat))
		वापस PTR_ERR(hat);

	अगर (!hat && !token) अणु
		AA_ERROR("change_hat: Invalid input, NULL hat and NULL magic");
		वापस -EINVAL;
	पूर्ण

	अगर (hat) अणु
		/* set up hat name vector, args guaranteed null terminated
		 * at args[size] by setprocattr.
		 *
		 * If there are multiple hat names in the buffer each is
		 * separated by a \0.  Ie. userspace ग_लिखोs them pre tokenized
		 */
		अक्षर *end = args + size;
		क्रम (count = 0; (hat < end) && count < 16; ++count) अणु
			अक्षर *next = hat + म_माप(hat) + 1;
			hats[count] = hat;
			AA_DEBUG("%s: (pid %d) Magic 0x%llx count %d hat '%s'\n"
				 , __func__, current->pid, token, count, hat);
			hat = next;
		पूर्ण
	पूर्ण अन्यथा
		AA_DEBUG("%s: (pid %d) Magic 0x%llx count %d Hat '%s'\n",
			 __func__, current->pid, token, count, "<NULL>");

	वापस aa_change_hat(hats, count, token, flags);
पूर्ण
