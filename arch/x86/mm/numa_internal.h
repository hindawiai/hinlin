<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __X86_MM_NUMA_INTERNAL_H
#घोषणा __X86_MM_NUMA_INTERNAL_H

#समावेश <linux/types.h>
#समावेश <यंत्र/numa.h>

काष्ठा numa_memblk अणु
	u64			start;
	u64			end;
	पूर्णांक			nid;
पूर्ण;

काष्ठा numa_meminfo अणु
	पूर्णांक			nr_blks;
	काष्ठा numa_memblk	blk[NR_NODE_MEMBLKS];
पूर्ण;

व्योम __init numa_हटाओ_memblk_from(पूर्णांक idx, काष्ठा numa_meminfo *mi);
पूर्णांक __init numa_cleanup_meminfo(काष्ठा numa_meminfo *mi);
व्योम __init numa_reset_distance(व्योम);

व्योम __init x86_numa_init(व्योम);

#अगर_घोषित CONFIG_NUMA_EMU
व्योम __init numa_emulation(काष्ठा numa_meminfo *numa_meminfo,
			   पूर्णांक numa_dist_cnt);
#अन्यथा
अटल अंतरभूत व्योम numa_emulation(काष्ठा numa_meminfo *numa_meminfo,
				  पूर्णांक numa_dist_cnt)
अणु पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर	/* __X86_MM_NUMA_INTERNAL_H */
