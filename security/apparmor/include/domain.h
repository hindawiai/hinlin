<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * AppArmor security module
 *
 * This file contains AppArmor security करोमुख्य transition function definitions.
 *
 * Copyright (C) 1998-2008 Novell/SUSE
 * Copyright 2009-2010 Canonical Ltd.
 */

#समावेश <linux/binfmts.h>
#समावेश <linux/types.h>

#समावेश "label.h"

#अगर_अघोषित __AA_DOMAIN_H
#घोषणा __AA_DOMAIN_H

काष्ठा aa_करोमुख्य अणु
	पूर्णांक size;
	अक्षर **table;
पूर्ण;

#घोषणा AA_CHANGE_NOFLAGS 0
#घोषणा AA_CHANGE_TEST 1
#घोषणा AA_CHANGE_CHILD 2
#घोषणा AA_CHANGE_ONEXEC  4
#घोषणा AA_CHANGE_STACK 8

काष्ठा aa_label *x_table_lookup(काष्ठा aa_profile *profile, u32 xindex,
				स्थिर अक्षर **name);

पूर्णांक apparmor_bprm_creds_क्रम_exec(काष्ठा linux_binprm *bprm);

व्योम aa_मुक्त_करोमुख्य_entries(काष्ठा aa_करोमुख्य *करोमुख्य);
पूर्णांक aa_change_hat(स्थिर अक्षर *hats[], पूर्णांक count, u64 token, पूर्णांक flags);
पूर्णांक aa_change_profile(स्थिर अक्षर *fqname, पूर्णांक flags);

#पूर्ण_अगर /* __AA_DOMAIN_H */
