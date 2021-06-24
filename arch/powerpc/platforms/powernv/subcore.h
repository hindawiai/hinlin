<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright 2013, Michael Ellerman, IBM Corporation.
 */

/* These are ordered and tested with <= */
#घोषणा SYNC_STEP_INITIAL	0
#घोषणा SYNC_STEP_UNSPLIT	1	/* Set by secondary when it sees unsplit */
#घोषणा SYNC_STEP_REAL_MODE	2	/* Set by secondary when in real mode  */
#घोषणा SYNC_STEP_FINISHED	3	/* Set by secondary when split/unsplit is करोne */

#अगर_अघोषित __ASSEMBLY__

#अगर_घोषित CONFIG_SMP
व्योम split_core_secondary_loop(u8 *state);
बाह्य व्योम update_subcore_sibling_mask(व्योम);
#अन्यथा
अटल अंतरभूत व्योम update_subcore_sibling_mask(व्योम) अणु पूर्ण
#पूर्ण_अगर /* CONFIG_SMP */

#पूर्ण_अगर /* __ASSEMBLY__ */
