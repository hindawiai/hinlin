<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश "archinsn.h"
#समावेश "event.h"
#समावेश "machine.h"
#समावेश "thread.h"
#समावेश "symbol.h"
#समावेश "../../../../arch/x86/include/asm/insn.h"

व्योम arch_fetch_insn(काष्ठा perf_sample *sample,
		     काष्ठा thपढ़ो *thपढ़ो,
		     काष्ठा machine *machine)
अणु
	काष्ठा insn insn;
	पूर्णांक len, ret;
	bool is64bit = false;

	अगर (!sample->ip)
		वापस;
	len = thपढ़ो__स_नकल(thपढ़ो, machine, sample->insn, sample->ip, माप(sample->insn), &is64bit);
	अगर (len <= 0)
		वापस;

	ret = insn_decode(&insn, sample->insn, len,
			  is64bit ? INSN_MODE_64 : INSN_MODE_32);
	अगर (ret >= 0 && insn.length <= len)
		sample->insn_len = insn.length;
पूर्ण
