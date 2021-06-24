<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * SafeSetID Linux Security Module
 *
 * Author: Micah Morton <mortonm@chromium.org>
 *
 * Copyright (C) 2018 The Chromium OS Authors.
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License version 2, as
 * published by the Free Software Foundation.
 *
 */
#अगर_अघोषित _SAFESETID_H
#घोषणा _SAFESETID_H

#समावेश <linux/types.h>
#समावेश <linux/uidgid.h>
#समावेश <linux/hashtable.h>

/* Flag indicating whether initialization completed */
बाह्य पूर्णांक safesetid_initialized;

क्रमागत sid_policy_type अणु
	SIDPOL_DEFAULT, /* source ID is unaffected by policy */
	SIDPOL_CONSTRAINED, /* source ID is affected by policy */
	SIDPOL_ALLOWED /* target ID explicitly allowed */
पूर्ण;

प्रकार जोड़ अणु
	kuid_t uid;
	kgid_t gid;
पूर्ण kid_t;

क्रमागत setid_type अणु
	UID,
	GID
पूर्ण;

/*
 * Hash table entry to store safesetid policy signअगरying that 'src_id'
 * can set*id to 'dst_id'.
 */
काष्ठा setid_rule अणु
	काष्ठा hlist_node next;
	kid_t src_id;
	kid_t dst_id;

	/* Flag to संकेत अगर rule is क्रम UID's or GID's */
	क्रमागत setid_type type;
पूर्ण;

#घोषणा SETID_HASH_BITS 8 /* 256 buckets in hash table */

/* Extension of INVALID_UID/INVALID_GID क्रम kid_t type */
#घोषणा INVALID_ID (kid_t)अणु.uid = INVALID_UIDपूर्ण

काष्ठा setid_ruleset अणु
	DECLARE_HASHTABLE(rules, SETID_HASH_BITS);
	अक्षर *policy_str;
	काष्ठा rcu_head rcu;

	//Flag to संकेत अगर ruleset is क्रम UID's or GID's
	क्रमागत setid_type type;
पूर्ण;

क्रमागत sid_policy_type _setid_policy_lookup(काष्ठा setid_ruleset *policy,
		kid_t src, kid_t dst);

बाह्य काष्ठा setid_ruleset __rcu *safesetid_setuid_rules;
बाह्य काष्ठा setid_ruleset __rcu *safesetid_setgid_rules;

#पूर्ण_अगर /* _SAFESETID_H */
