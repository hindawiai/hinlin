<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * AppArmor security module
 *
 * This file contains AppArmor ipc mediation
 *
 * Copyright (C) 1998-2008 Novell/SUSE
 * Copyright 2009-2017 Canonical Ltd.
 */

#समावेश <linux/gfp.h>
#समावेश <linux/ptrace.h>

#समावेश "include/audit.h"
#समावेश "include/capability.h"
#समावेश "include/cred.h"
#समावेश "include/policy.h"
#समावेश "include/ipc.h"
#समावेश "include/sig_names.h"

/**
 * audit_ptrace_mask - convert mask to permission string
 * @mask: permission mask to convert
 *
 * Returns: poपूर्णांकer to अटल string
 */
अटल स्थिर अक्षर *audit_ptrace_mask(u32 mask)
अणु
	चयन (mask) अणु
	हाल MAY_READ:
		वापस "read";
	हाल MAY_WRITE:
		वापस "trace";
	हाल AA_MAY_BE_READ:
		वापस "readby";
	हाल AA_MAY_BE_TRACED:
		वापस "tracedby";
	पूर्ण
	वापस "";
पूर्ण

/* call back to audit ptrace fields */
अटल व्योम audit_ptrace_cb(काष्ठा audit_buffer *ab, व्योम *va)
अणु
	काष्ठा common_audit_data *sa = va;

	अगर (aad(sa)->request & AA_PTRACE_PERM_MASK) अणु
		audit_log_क्रमmat(ab, " requested_mask=\"%s\"",
				 audit_ptrace_mask(aad(sa)->request));

		अगर (aad(sa)->denied & AA_PTRACE_PERM_MASK) अणु
			audit_log_क्रमmat(ab, " denied_mask=\"%s\"",
					 audit_ptrace_mask(aad(sa)->denied));
		पूर्ण
	पूर्ण
	audit_log_क्रमmat(ab, " peer=");
	aa_label_xaudit(ab, labels_ns(aad(sa)->label), aad(sa)->peer,
			FLAGS_NONE, GFP_ATOMIC);
पूर्ण

/* assumes check क्रम PROखाता_MEDIATES is alपढ़ोy करोne */
/* TODO: conditionals */
अटल पूर्णांक profile_ptrace_perm(काष्ठा aa_profile *profile,
			     काष्ठा aa_label *peer, u32 request,
			     काष्ठा common_audit_data *sa)
अणु
	काष्ठा aa_perms perms = अणु पूर्ण;

	aad(sa)->peer = peer;
	aa_profile_match_label(profile, peer, AA_CLASS_PTRACE, request,
			       &perms);
	aa_apply_modes_to_perms(profile, &perms);
	वापस aa_check_perms(profile, &perms, request, sa, audit_ptrace_cb);
पूर्ण

अटल पूर्णांक profile_tracee_perm(काष्ठा aa_profile *tracee,
			       काष्ठा aa_label *tracer, u32 request,
			       काष्ठा common_audit_data *sa)
अणु
	अगर (profile_unconfined(tracee) || unconfined(tracer) ||
	    !PROखाता_MEDIATES(tracee, AA_CLASS_PTRACE))
		वापस 0;

	वापस profile_ptrace_perm(tracee, tracer, request, sa);
पूर्ण

अटल पूर्णांक profile_tracer_perm(काष्ठा aa_profile *tracer,
			       काष्ठा aa_label *tracee, u32 request,
			       काष्ठा common_audit_data *sa)
अणु
	अगर (profile_unconfined(tracer))
		वापस 0;

	अगर (PROखाता_MEDIATES(tracer, AA_CLASS_PTRACE))
		वापस profile_ptrace_perm(tracer, tracee, request, sa);

	/* profile uses the old style capability check क्रम ptrace */
	अगर (&tracer->label == tracee)
		वापस 0;

	aad(sa)->label = &tracer->label;
	aad(sa)->peer = tracee;
	aad(sa)->request = 0;
	aad(sa)->error = aa_capable(&tracer->label, CAP_SYS_PTRACE,
				    CAP_OPT_NONE);

	वापस aa_audit(AUDIT_APPARMOR_AUTO, tracer, sa, audit_ptrace_cb);
पूर्ण

/**
 * aa_may_ptrace - test अगर tracer task can trace the tracee
 * @tracer: label of the task करोing the tracing  (NOT शून्य)
 * @tracee: task label to be traced
 * @request: permission request
 *
 * Returns: %0 अन्यथा error code अगर permission denied or error
 */
पूर्णांक aa_may_ptrace(काष्ठा aa_label *tracer, काष्ठा aa_label *tracee,
		  u32 request)
अणु
	काष्ठा aa_profile *profile;
	u32 xrequest = request << PTRACE_PERM_SHIFT;
	DEFINE_AUDIT_DATA(sa, LSM_AUDIT_DATA_NONE, OP_PTRACE);

	वापस xcheck_labels(tracer, tracee, profile,
			profile_tracer_perm(profile, tracee, request, &sa),
			profile_tracee_perm(profile, tracer, xrequest, &sa));
पूर्ण


अटल अंतरभूत पूर्णांक map_संकेत_num(पूर्णांक sig)
अणु
	अगर (sig > SIGRTMAX)
		वापस SIGUNKNOWN;
	अन्यथा अगर (sig >= SIGRTMIN)
		वापस sig - SIGRTMIN + SIGRT_BASE;
	अन्यथा अगर (sig < MAXMAPPED_SIG)
		वापस sig_map[sig];
	वापस SIGUNKNOWN;
पूर्ण

/**
 * audit_संकेत_mask - convert mask to permission string
 * @mask: permission mask to convert
 *
 * Returns: poपूर्णांकer to अटल string
 */
अटल स्थिर अक्षर *audit_संकेत_mask(u32 mask)
अणु
	अगर (mask & MAY_READ)
		वापस "receive";
	अगर (mask & MAY_WRITE)
		वापस "send";
	वापस "";
पूर्ण

/**
 * audit_cb - call back क्रम संकेत specअगरic audit fields
 * @ab: audit_buffer  (NOT शून्य)
 * @va: audit काष्ठा to audit values of  (NOT शून्य)
 */
अटल व्योम audit_संकेत_cb(काष्ठा audit_buffer *ab, व्योम *va)
अणु
	काष्ठा common_audit_data *sa = va;

	अगर (aad(sa)->request & AA_SIGNAL_PERM_MASK) अणु
		audit_log_क्रमmat(ab, " requested_mask=\"%s\"",
				 audit_संकेत_mask(aad(sa)->request));
		अगर (aad(sa)->denied & AA_SIGNAL_PERM_MASK) अणु
			audit_log_क्रमmat(ab, " denied_mask=\"%s\"",
					 audit_संकेत_mask(aad(sa)->denied));
		पूर्ण
	पूर्ण
	अगर (aad(sa)->संकेत == SIGUNKNOWN)
		audit_log_क्रमmat(ab, "signal=unknown(%d)",
				 aad(sa)->unmappedsig);
	अन्यथा अगर (aad(sa)->संकेत < MAXMAPPED_SIGNAME)
		audit_log_क्रमmat(ab, " signal=%s", sig_names[aad(sa)->संकेत]);
	अन्यथा
		audit_log_क्रमmat(ab, " signal=rtmin+%d",
				 aad(sa)->संकेत - SIGRT_BASE);
	audit_log_क्रमmat(ab, " peer=");
	aa_label_xaudit(ab, labels_ns(aad(sa)->label), aad(sa)->peer,
			FLAGS_NONE, GFP_ATOMIC);
पूर्ण

अटल पूर्णांक profile_संकेत_perm(काष्ठा aa_profile *profile,
			       काष्ठा aa_label *peer, u32 request,
			       काष्ठा common_audit_data *sa)
अणु
	काष्ठा aa_perms perms;
	अचिन्हित पूर्णांक state;

	अगर (profile_unconfined(profile) ||
	    !PROखाता_MEDIATES(profile, AA_CLASS_SIGNAL))
		वापस 0;

	aad(sa)->peer = peer;
	/* TODO: secondary cache check <profile, profile, perm> */
	state = aa_dfa_next(profile->policy.dfa,
			    profile->policy.start[AA_CLASS_SIGNAL],
			    aad(sa)->संकेत);
	aa_label_match(profile, peer, state, false, request, &perms);
	aa_apply_modes_to_perms(profile, &perms);
	वापस aa_check_perms(profile, &perms, request, sa, audit_संकेत_cb);
पूर्ण

पूर्णांक aa_may_संकेत(काष्ठा aa_label *sender, काष्ठा aa_label *target, पूर्णांक sig)
अणु
	काष्ठा aa_profile *profile;
	DEFINE_AUDIT_DATA(sa, LSM_AUDIT_DATA_NONE, OP_SIGNAL);

	aad(&sa)->संकेत = map_संकेत_num(sig);
	aad(&sa)->unmappedsig = sig;
	वापस xcheck_labels(sender, target, profile,
			profile_संकेत_perm(profile, target, MAY_WRITE, &sa),
			profile_संकेत_perm(profile, sender, MAY_READ, &sa));
पूर्ण
