<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * SELinux support क्रम the Audit LSM hooks
 *
 * Author: James Morris <jmorris@redhat.com>
 *
 * Copyright (C) 2005 Red Hat, Inc., James Morris <jmorris@redhat.com>
 * Copyright (C) 2006 Trusted Computer Solutions, Inc. <dgoeddel@trustedcs.com>
 * Copyright (C) 2006 IBM Corporation, Timothy R. Chavez <tinytim@us.ibm.com>
 */

#अगर_अघोषित _SELINUX_AUDIT_H
#घोषणा _SELINUX_AUDIT_H

/**
 *	selinux_audit_rule_init - alloc/init an selinux audit rule काष्ठाure.
 *	@field: the field this rule refers to
 *	@op: the operater the rule uses
 *	@rulestr: the text "target" of the rule
 *	@rule: poपूर्णांकer to the new rule काष्ठाure वापसed via this
 *
 *	Returns 0 अगर successful, -त्रुटि_सं अगर not.  On success, the rule काष्ठाure
 *	will be allocated पूर्णांकernally.  The caller must मुक्त this काष्ठाure with
 *	selinux_audit_rule_मुक्त() after use.
 */
पूर्णांक selinux_audit_rule_init(u32 field, u32 op, अक्षर *rulestr, व्योम **rule);

/**
 *	selinux_audit_rule_मुक्त - मुक्त an selinux audit rule काष्ठाure.
 *	@rule: poपूर्णांकer to the audit rule to be मुक्तd
 *
 *	This will मुक्त all memory associated with the given rule.
 *	If @rule is शून्य, no operation is perक्रमmed.
 */
व्योम selinux_audit_rule_मुक्त(व्योम *rule);

/**
 *	selinux_audit_rule_match - determine अगर a context ID matches a rule.
 *	@sid: the context ID to check
 *	@field: the field this rule refers to
 *	@op: the operater the rule uses
 *	@rule: poपूर्णांकer to the audit rule to check against
 *
 *	Returns 1 अगर the context id matches the rule, 0 अगर it करोes not, and
 *	-त्रुटि_सं on failure.
 */
पूर्णांक selinux_audit_rule_match(u32 sid, u32 field, u32 op, व्योम *rule);

/**
 *	selinux_audit_rule_known - check to see अगर rule contains selinux fields.
 *	@rule: rule to be checked
 *	Returns 1 अगर there are selinux fields specअगरied in the rule, 0 otherwise.
 */
पूर्णांक selinux_audit_rule_known(काष्ठा audit_krule *krule);

#पूर्ण_अगर /* _SELINUX_AUDIT_H */

