<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copied from the kernel sources:
 *
 * Copyright (C) 1999, 2000  Niibe Yutaka  &  Kaz Kojima
 * Copyright (C) 2002 Paul Mundt
 */
#अगर_अघोषित __TOOLS_LINUX_ASM_SH_BARRIER_H
#घोषणा __TOOLS_LINUX_ASM_SH_BARRIER_H

/*
 * A brief note on ctrl_barrier(), the control रेजिस्टर ग_लिखो barrier.
 *
 * Legacy SH cores typically require a sequence of 8 nops after
 * modअगरication of a control रेजिस्टर in order क्रम the changes to take
 * effect. On newer cores (like the sh4a and sh5) this is accomplished
 * with icbi.
 *
 * Also note that on sh4a in the icbi हाल we can क्रमego a synco क्रम the
 * ग_लिखो barrier, as it's not necessary क्रम control रेजिस्टरs.
 *
 * Historically we have only करोne this type of barrier क्रम the MMUCR, but
 * it's also necessary क्रम the CCR, so we make it generic here instead.
 */
#अगर defined(__SH4A__)
#घोषणा mb()		__यंत्र__ __अस्थिर__ ("synco": : :"memory")
#घोषणा rmb()		mb()
#घोषणा wmb()		mb()
#पूर्ण_अगर

#समावेश <यंत्र-generic/barrier.h>

#पूर्ण_अगर /* __TOOLS_LINUX_ASM_SH_BARRIER_H */
