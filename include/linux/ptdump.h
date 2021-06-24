<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */

#अगर_अघोषित _LINUX_PTDUMP_H
#घोषणा _LINUX_PTDUMP_H

#समावेश <linux/mm_types.h>

काष्ठा ptdump_range अणु
	अचिन्हित दीर्घ start;
	अचिन्हित दीर्घ end;
पूर्ण;

काष्ठा ptdump_state अणु
	/* level is 0:PGD to 4:PTE, or -1 अगर unknown */
	व्योम (*note_page)(काष्ठा ptdump_state *st, अचिन्हित दीर्घ addr,
			  पूर्णांक level, u64 val);
	व्योम (*effective_prot)(काष्ठा ptdump_state *st, पूर्णांक level, u64 val);
	स्थिर काष्ठा ptdump_range *range;
पूर्ण;

व्योम ptdump_walk_pgd(काष्ठा ptdump_state *st, काष्ठा mm_काष्ठा *mm, pgd_t *pgd);

#पूर्ण_अगर /* _LINUX_PTDUMP_H */
