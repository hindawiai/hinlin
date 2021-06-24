<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Hypervisor Maपूर्णांकenance Interrupt (HMI) handling.
 *
 * Copyright 2015 IBM Corporation
 * Author: Mahesh Salgaonkar <mahesh@linux.vnet.ibm.com>
 */

#अघोषित DEBUG

#समावेश <linux/types.h>
#समावेश <linux/compiler.h>
#समावेश <यंत्र/paca.h>
#समावेश <यंत्र/hmi.h>
#समावेश <यंत्र/processor.h>

व्योम रुको_क्रम_subcore_guest_निकास(व्योम)
अणु
	पूर्णांक i;

	/*
	 * शून्य biपंचांगap poपूर्णांकer indicates that KVM module hasn't
	 * been loaded yet and hence no guests are running.
	 * If no KVM is in use, no need to co-ordinate among thपढ़ोs
	 * as all of them will always be in host and no one is going
	 * to modअगरy TB other than the opal hmi handler.
	 * Hence, just वापस from here.
	 */
	अगर (!local_paca->sibling_subcore_state)
		वापस;

	क्रम (i = 0; i < MAX_SUBCORE_PER_CORE; i++)
		जबतक (local_paca->sibling_subcore_state->in_guest[i])
			cpu_relax();
पूर्ण

व्योम रुको_क्रम_tb_resync(व्योम)
अणु
	अगर (!local_paca->sibling_subcore_state)
		वापस;

	जबतक (test_bit(CORE_TB_RESYNC_REQ_BIT,
				&local_paca->sibling_subcore_state->flags))
		cpu_relax();
पूर्ण
