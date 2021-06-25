<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
// Copyright (C) 2005-2017 Andes Technology Corporation

#अगर_अघोषित __NDS32_ASM_BARRIER_H
#घोषणा __NDS32_ASM_BARRIER_H

#अगर_अघोषित __ASSEMBLY__
#घोषणा mb()		यंत्र अस्थिर("msync all":::"memory")
#घोषणा rmb()		यंत्र अस्थिर("msync all":::"memory")
#घोषणा wmb()		यंत्र अस्थिर("msync store":::"memory")
#समावेश <यंत्र-generic/barrier.h>

#पूर्ण_अगर	/* __ASSEMBLY__ */

#पूर्ण_अगर	/* __NDS32_ASM_BARRIER_H */
