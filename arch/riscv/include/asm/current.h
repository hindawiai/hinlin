<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Based on arm/arm64/include/यंत्र/current.h
 *
 * Copyright (C) 2016 ARM
 * Copyright (C) 2017 SiFive
 */


#अगर_अघोषित _ASM_RISCV_CURRENT_H
#घोषणा _ASM_RISCV_CURRENT_H

#समावेश <linux/bug.h>
#समावेश <linux/compiler.h>

#अगर_अघोषित __ASSEMBLY__

काष्ठा task_काष्ठा;

रेजिस्टर काष्ठा task_काष्ठा *riscv_current_is_tp __यंत्र__("tp");

/*
 * This only works because "struct thread_info" is at offset 0 from "काष्ठा
 * task_काष्ठा".  This स्थिरraपूर्णांक seems to be necessary on other architectures
 * as well, but __चयन_to enक्रमces it.  We can't check TASK_TI here because
 * <यंत्र/यंत्र-offsets.h> includes this, and I can't get the definition of "काष्ठा
 * task_काष्ठा" here due to some header ordering problems.
 */
अटल __always_अंतरभूत काष्ठा task_काष्ठा *get_current(व्योम)
अणु
	वापस riscv_current_is_tp;
पूर्ण

#घोषणा current get_current()

#पूर्ण_अगर /* __ASSEMBLY__ */

#पूर्ण_अगर /* _ASM_RISCV_CURRENT_H */
