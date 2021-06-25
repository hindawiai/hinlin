<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ASM_SH_TRAPS_H
#घोषणा __ASM_SH_TRAPS_H

#समावेश <linux/compiler.h>

# include <यंत्र/traps_32.h>

BUILD_TRAP_HANDLER(address_error);
BUILD_TRAP_HANDLER(debug);
BUILD_TRAP_HANDLER(bug);
BUILD_TRAP_HANDLER(अवरोधpoपूर्णांक);
BUILD_TRAP_HANDLER(singlestep);
BUILD_TRAP_HANDLER(fpu_error);
BUILD_TRAP_HANDLER(fpu_state_restore);
BUILD_TRAP_HANDLER(nmi);

#पूर्ण_अगर /* __ASM_SH_TRAPS_H */
