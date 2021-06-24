<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * AppArmor security module
 *
 * This file contains AppArmor capability mediation definitions.
 *
 * Copyright (C) 1998-2008 Novell/SUSE
 * Copyright 2009-2013 Canonical Ltd.
 */

#अगर_अघोषित __AA_CAPABILITY_H
#घोषणा __AA_CAPABILITY_H

#समावेश <linux/sched.h>

#समावेश "apparmorfs.h"

काष्ठा aa_label;

/* aa_caps - confinement data क्रम capabilities
 * @allowed: capabilities mask
 * @audit: caps that are to be audited
 * @denied: caps that are explicitly denied
 * @quiet: caps that should not be audited
 * @समाप्त: caps that when requested will result in the task being समाप्तed
 * @extended: caps that are subject finer grained mediation
 */
काष्ठा aa_caps अणु
	kernel_cap_t allow;
	kernel_cap_t audit;
	kernel_cap_t denied;
	kernel_cap_t quiet;
	kernel_cap_t समाप्त;
	kernel_cap_t extended;
पूर्ण;

बाह्य काष्ठा aa_sfs_entry aa_sfs_entry_caps[];

पूर्णांक aa_capable(काष्ठा aa_label *label, पूर्णांक cap, अचिन्हित पूर्णांक opts);

अटल अंतरभूत व्योम aa_मुक्त_cap_rules(काष्ठा aa_caps *caps)
अणु
	/* NOP */
पूर्ण

#पूर्ण_अगर /* __AA_CAPBILITY_H */
