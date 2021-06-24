<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */

#अगर_अघोषित _ASM_RISCV_MMIOWB_H
#घोषणा _ASM_RISCV_MMIOWB_H

/*
 * "o,w" is sufficient to ensure that all ग_लिखोs to the device have completed
 * beक्रमe the ग_लिखो to the spinlock is allowed to commit.
 */
#घोषणा mmiowb()	__यंत्र__ __अस्थिर__ ("fence o,w" : : : "memory");

#समावेश <linux/smp.h>
#समावेश <यंत्र-generic/mmiowb.h>

#पूर्ण_अगर	/* _ASM_RISCV_MMIOWB_H */
