<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * The Kernel Concurrency Sanitizer (KCSAN) infraकाष्ठाure. Public पूर्णांकerface and
 * data काष्ठाures to set up runसमय. See kcsan-checks.h क्रम explicit checks and
 * modअगरiers. For more info please see Documentation/dev-tools/kcsan.rst.
 *
 * Copyright (C) 2019, Google LLC.
 */

#अगर_अघोषित _LINUX_KCSAN_H
#घोषणा _LINUX_KCSAN_H

#समावेश <linux/kcsan-checks.h>
#समावेश <linux/types.h>

#अगर_घोषित CONFIG_KCSAN

/*
 * Context क्रम each thपढ़ो of execution: क्रम tasks, this is stored in
 * task_काष्ठा, and पूर्णांकerrupts access पूर्णांकernal per-CPU storage.
 */
काष्ठा kcsan_ctx अणु
	पूर्णांक disable_count; /* disable counter */
	पूर्णांक atomic_next; /* number of following atomic ops */

	/*
	 * We distinguish between: (a) nestable atomic regions that may contain
	 * other nestable regions; and (b) flat atomic regions that करो not keep
	 * track of nesting. Both (a) and (b) are entirely independent of each
	 * other, and a flat region may be started in a nestable region or
	 * vice-versa.
	 *
	 * This is required because, क्रम example, in the annotations क्रम
	 * seqlocks, we declare seqlock ग_लिखोr critical sections as (a) nestable
	 * atomic regions, but पढ़ोer critical sections as (b) flat atomic
	 * regions, but have encountered हालs where seqlock पढ़ोer critical
	 * sections are contained within ग_लिखोr critical sections (the opposite
	 * may be possible, too).
	 *
	 * To support these हालs, we independently track the depth of nesting
	 * क्रम (a), and whether the leaf level is flat क्रम (b).
	 */
	पूर्णांक atomic_nest_count;
	bool in_flat_atomic;

	/*
	 * Access mask क्रम all accesses अगर non-zero.
	 */
	अचिन्हित दीर्घ access_mask;

	/* List of scoped accesses. */
	काष्ठा list_head scoped_accesses;
पूर्ण;

/**
 * kcsan_init - initialize KCSAN runसमय
 */
व्योम kcsan_init(व्योम);

#अन्यथा /* CONFIG_KCSAN */

अटल अंतरभूत व्योम kcsan_init(व्योम)			अणु पूर्ण

#पूर्ण_अगर /* CONFIG_KCSAN */

#पूर्ण_अगर /* _LINUX_KCSAN_H */
