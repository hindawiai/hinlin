<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * AppArmor security module
 *
 * This file contains AppArmor network mediation
 *
 * Copyright (C) 1998-2008 Novell/SUSE
 * Copyright 2009-2017 Canonical Ltd.
 */

#समावेश "include/apparmor.h"
#समावेश "include/audit.h"
#समावेश "include/cred.h"
#समावेश "include/label.h"
#समावेश "include/net.h"
#समावेश "include/policy.h"
#समावेश "include/secid.h"

#समावेश "net_names.h"


काष्ठा aa_sfs_entry aa_sfs_entry_network[] = अणु
	AA_SFS_खाता_STRING("af_mask",	AA_SFS_AF_MASK),
	अणु पूर्ण
पूर्ण;

अटल स्थिर अक्षर * स्थिर net_mask_names[] = अणु
	"unknown",
	"send",
	"receive",
	"unknown",

	"create",
	"shutdown",
	"connect",
	"unknown",

	"setattr",
	"getattr",
	"setcred",
	"getcred",

	"chmod",
	"chown",
	"chgrp",
	"lock",

	"mmap",
	"mprot",
	"unknown",
	"unknown",

	"accept",
	"bind",
	"listen",
	"unknown",

	"setopt",
	"getopt",
	"unknown",
	"unknown",

	"unknown",
	"unknown",
	"unknown",
	"unknown",
पूर्ण;


/* audit callback क्रम net specअगरic fields */
व्योम audit_net_cb(काष्ठा audit_buffer *ab, व्योम *va)
अणु
	काष्ठा common_audit_data *sa = va;

	अगर (address_family_names[sa->u.net->family])
		audit_log_क्रमmat(ab, " family=\"%s\"",
				 address_family_names[sa->u.net->family]);
	अन्यथा
		audit_log_क्रमmat(ab, " family=\"unknown(%d)\"",
				 sa->u.net->family);
	अगर (sock_type_names[aad(sa)->net.type])
		audit_log_क्रमmat(ab, " sock_type=\"%s\"",
				 sock_type_names[aad(sa)->net.type]);
	अन्यथा
		audit_log_क्रमmat(ab, " sock_type=\"unknown(%d)\"",
				 aad(sa)->net.type);
	audit_log_क्रमmat(ab, " protocol=%d", aad(sa)->net.protocol);

	अगर (aad(sa)->request & NET_PERMS_MASK) अणु
		audit_log_क्रमmat(ab, " requested_mask=");
		aa_audit_perm_mask(ab, aad(sa)->request, शून्य, 0,
				   net_mask_names, NET_PERMS_MASK);

		अगर (aad(sa)->denied & NET_PERMS_MASK) अणु
			audit_log_क्रमmat(ab, " denied_mask=");
			aa_audit_perm_mask(ab, aad(sa)->denied, शून्य, 0,
					   net_mask_names, NET_PERMS_MASK);
		पूर्ण
	पूर्ण
	अगर (aad(sa)->peer) अणु
		audit_log_क्रमmat(ab, " peer=");
		aa_label_xaudit(ab, labels_ns(aad(sa)->label), aad(sa)->peer,
				FLAGS_NONE, GFP_ATOMIC);
	पूर्ण
पूर्ण

/* Generic af perm */
पूर्णांक aa_profile_af_perm(काष्ठा aa_profile *profile, काष्ठा common_audit_data *sa,
		       u32 request, u16 family, पूर्णांक type)
अणु
	काष्ठा aa_perms perms = अणु पूर्ण;
	अचिन्हित पूर्णांक state;
	__be16 buffer[2];

	AA_BUG(family >= AF_MAX);
	AA_BUG(type < 0 || type >= SOCK_MAX);

	अगर (profile_unconfined(profile))
		वापस 0;
	state = PROखाता_MEDIATES(profile, AA_CLASS_NET);
	अगर (!state)
		वापस 0;

	buffer[0] = cpu_to_be16(family);
	buffer[1] = cpu_to_be16((u16) type);
	state = aa_dfa_match_len(profile->policy.dfa, state, (अक्षर *) &buffer,
				 4);
	aa_compute_perms(profile->policy.dfa, state, &perms);
	aa_apply_modes_to_perms(profile, &perms);

	वापस aa_check_perms(profile, &perms, request, sa, audit_net_cb);
पूर्ण

पूर्णांक aa_af_perm(काष्ठा aa_label *label, स्थिर अक्षर *op, u32 request, u16 family,
	       पूर्णांक type, पूर्णांक protocol)
अणु
	काष्ठा aa_profile *profile;
	DEFINE_AUDIT_NET(sa, op, शून्य, family, type, protocol);

	वापस fn_क्रम_each_confined(label, profile,
			aa_profile_af_perm(profile, &sa, request, family,
					   type));
पूर्ण

अटल पूर्णांक aa_label_sk_perm(काष्ठा aa_label *label, स्थिर अक्षर *op, u32 request,
			    काष्ठा sock *sk)
अणु
	पूर्णांक error = 0;

	AA_BUG(!label);
	AA_BUG(!sk);

	अगर (!unconfined(label)) अणु
		काष्ठा aa_profile *profile;
		DEFINE_AUDIT_SK(sa, op, sk);

		error = fn_क्रम_each_confined(label, profile,
			    aa_profile_af_sk_perm(profile, &sa, request, sk));
	पूर्ण

	वापस error;
पूर्ण

पूर्णांक aa_sk_perm(स्थिर अक्षर *op, u32 request, काष्ठा sock *sk)
अणु
	काष्ठा aa_label *label;
	पूर्णांक error;

	AA_BUG(!sk);
	AA_BUG(in_पूर्णांकerrupt());

	/* TODO: चयन to begin_current_label ???? */
	label = begin_current_label_crit_section();
	error = aa_label_sk_perm(label, op, request, sk);
	end_current_label_crit_section(label);

	वापस error;
पूर्ण


पूर्णांक aa_sock_file_perm(काष्ठा aa_label *label, स्थिर अक्षर *op, u32 request,
		      काष्ठा socket *sock)
अणु
	AA_BUG(!label);
	AA_BUG(!sock);
	AA_BUG(!sock->sk);

	वापस aa_label_sk_perm(label, op, request, sock->sk);
पूर्ण

#अगर_घोषित CONFIG_NETWORK_SECMARK
अटल पूर्णांक apparmor_secmark_init(काष्ठा aa_secmark *secmark)
अणु
	काष्ठा aa_label *label;

	अगर (secmark->label[0] == '*') अणु
		secmark->secid = AA_SECID_WILDCARD;
		वापस 0;
	पूर्ण

	label = aa_label_strn_parse(&root_ns->unconfined->label,
				    secmark->label, म_माप(secmark->label),
				    GFP_ATOMIC, false, false);

	अगर (IS_ERR(label))
		वापस PTR_ERR(label);

	secmark->secid = label->secid;

	वापस 0;
पूर्ण

अटल पूर्णांक aa_secmark_perm(काष्ठा aa_profile *profile, u32 request, u32 secid,
			   काष्ठा common_audit_data *sa)
अणु
	पूर्णांक i, ret;
	काष्ठा aa_perms perms = अणु पूर्ण;

	अगर (profile->secmark_count == 0)
		वापस 0;

	क्रम (i = 0; i < profile->secmark_count; i++) अणु
		अगर (!profile->secmark[i].secid) अणु
			ret = apparmor_secmark_init(&profile->secmark[i]);
			अगर (ret)
				वापस ret;
		पूर्ण

		अगर (profile->secmark[i].secid == secid ||
		    profile->secmark[i].secid == AA_SECID_WILDCARD) अणु
			अगर (profile->secmark[i].deny)
				perms.deny = ALL_PERMS_MASK;
			अन्यथा
				perms.allow = ALL_PERMS_MASK;

			अगर (profile->secmark[i].audit)
				perms.audit = ALL_PERMS_MASK;
		पूर्ण
	पूर्ण

	aa_apply_modes_to_perms(profile, &perms);

	वापस aa_check_perms(profile, &perms, request, sa, audit_net_cb);
पूर्ण

पूर्णांक apparmor_secmark_check(काष्ठा aa_label *label, अक्षर *op, u32 request,
			   u32 secid, स्थिर काष्ठा sock *sk)
अणु
	काष्ठा aa_profile *profile;
	DEFINE_AUDIT_SK(sa, op, sk);

	वापस fn_क्रम_each_confined(label, profile,
				    aa_secmark_perm(profile, request, secid,
						    &sa));
पूर्ण
#पूर्ण_अगर
