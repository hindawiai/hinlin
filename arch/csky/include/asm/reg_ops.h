<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */

#अगर_अघोषित __ASM_REGS_OPS_H
#घोषणा __ASM_REGS_OPS_H

#घोषणा mfcr(reg)		\
(अणु				\
	अचिन्हित पूर्णांक पंचांगp;	\
	यंत्र अस्थिर(		\
	"mfcr %0, "reg"\n"	\
	: "=r"(पंचांगp)		\
	:			\
	: "memory");		\
	पंचांगp;			\
पूर्ण)

#घोषणा mtcr(reg, val)		\
(अणु				\
	यंत्र अस्थिर(		\
	"mtcr %0, "reg"\n"	\
	:			\
	: "r"(val)		\
	: "memory");		\
पूर्ण)

#पूर्ण_अगर /* __ASM_REGS_OPS_H */
