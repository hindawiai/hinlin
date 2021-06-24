<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (C) 2018 MIPS Tech, LLC
 * Author: Matt Redfearn <matt.redfearn@mips.com>
 */

#अगर_अघोषित __MIPS_ASM_ISA_REV_H__
#घोषणा __MIPS_ASM_ISA_REV_H__

/*
 * The ISA revision level. This is 0 क्रम MIPS I to V and N क्रम
 * MIPSअणु32,64पूर्णrN.
 */

/* If the compiler has defined __mips_isa_rev, believe it. */
#अगर_घोषित __mips_isa_rev
#घोषणा MIPS_ISA_REV __mips_isa_rev
#अन्यथा
/* The compiler hasn't defined the isa rev so assume it's MIPS I - V (0) */
#घोषणा MIPS_ISA_REV 0
#पूर्ण_अगर


#पूर्ण_अगर /* __MIPS_ASM_ISA_REV_H__ */
