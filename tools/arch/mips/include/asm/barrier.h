<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _TOOLS_LINUX_ASM_MIPS_BARRIER_H
#घोषणा _TOOLS_LINUX_ASM_MIPS_BARRIER_H
/*
 * FIXME: This came from tools/perf/perf-sys.h, where it was first पूर्णांकroduced
 * in c1e028ef40b8d6943b767028ba17d4f2ba020edb, more work needed to make it
 * more बंदly follow the Linux kernel arch/mips/include/यंत्र/barrier.h file.
 * Probably when we जारी work on tools/ Kconfig support to have all the
 * CONFIG_ needed क्रम properly करोing that.
 */
#घोषणा mb()		यंत्र अस्थिर(					\
				".set	mips2\n\t"			\
				"sync\n\t"				\
				".set	mips0"				\
				: /* no output */			\
				: /* no input */			\
				: "memory")
#घोषणा wmb()	mb()
#घोषणा rmb()	mb()

#पूर्ण_अगर /* _TOOLS_LINUX_ASM_MIPS_BARRIER_H */
