<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Interface to booleans in the security server. This is exported
 * क्रम the selinuxfs.
 *
 * Author: Karl MacMillan <kmacmillan@tresys.com>
 *
 * Copyright (C) 2003 - 2004 Tresys Technology, LLC
 */

#अगर_अघोषित _SELINUX_CONDITIONAL_H_
#घोषणा _SELINUX_CONDITIONAL_H_

#समावेश "security.h"

पूर्णांक security_get_bools(काष्ठा selinux_policy *policy,
		       u32 *len, अक्षर ***names, पूर्णांक **values);

पूर्णांक security_set_bools(काष्ठा selinux_state *state, u32 len, पूर्णांक *values);

पूर्णांक security_get_bool_value(काष्ठा selinux_state *state, u32 index);

#पूर्ण_अगर
