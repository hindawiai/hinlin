<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * vlock.h - simple voting lock implementation
 *
 * Created by:	Dave Martin, 2012-08-16
 * Copyright:	(C) 2012-2013  Linaro Limited
 */

#अगर_अघोषित __VLOCK_H
#घोषणा __VLOCK_H

#समावेश <यंत्र/mcpm.h>

/* Offsets and sizes are rounded to a word (4 bytes) */
#घोषणा VLOCK_OWNER_OFFSET	0
#घोषणा VLOCK_VOTING_OFFSET	4
#घोषणा VLOCK_VOTING_SIZE	((MAX_CPUS_PER_CLUSTER + 3) / 4 * 4)
#घोषणा VLOCK_SIZE		(VLOCK_VOTING_OFFSET + VLOCK_VOTING_SIZE)
#घोषणा VLOCK_OWNER_NONE	0

#पूर्ण_अगर /* ! __VLOCK_H */
