<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Definitions specअगरic to SMP platक्रमms.
 *
 * Copyright (C) 2013 ARM Ltd.
 */

#अगर_अघोषित __ASM_SMP_PLAT_H
#घोषणा __ASM_SMP_PLAT_H

#समावेश <linux/cpumask.h>

#समावेश <यंत्र/types.h>

काष्ठा mpidr_hash अणु
	u64	mask;
	u32	shअगरt_aff[4];
	u32	bits;
पूर्ण;

बाह्य काष्ठा mpidr_hash mpidr_hash;

अटल अंतरभूत u32 mpidr_hash_size(व्योम)
अणु
	वापस 1 << mpidr_hash.bits;
पूर्ण

/*
 * Retrieve logical cpu index corresponding to a given MPIDR.Aff*
 *  - mpidr: MPIDR.Aff* bits to be used क्रम the look-up
 *
 * Returns the cpu logical index or -EINVAL on look-up error
 */
अटल अंतरभूत पूर्णांक get_logical_index(u64 mpidr)
अणु
	पूर्णांक cpu;
	क्रम (cpu = 0; cpu < nr_cpu_ids; cpu++)
		अगर (cpu_logical_map(cpu) == mpidr)
			वापस cpu;
	वापस -EINVAL;
पूर्ण

#पूर्ण_अगर /* __ASM_SMP_PLAT_H */
