<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * KVM/MIPS: COP0 access histogram
 *
 * Copyright (C) 2012  MIPS Technologies, Inc.  All rights reserved.
 * Authors: Sanjay Lal <sanjayl@kymasys.com>
 */

#समावेश <linux/kvm_host.h>

अक्षर *kvm_cop0_str[N_MIPS_COPROC_REGS] = अणु
	"Index",
	"Random",
	"EntryLo0",
	"EntryLo1",
	"Context",
	"PG Mask",
	"Wired",
	"HWREna",
	"BadVAddr",
	"Count",
	"EntryHI",
	"Compare",
	"Status",
	"Cause",
	"EXC PC",
	"PRID",
	"Config",
	"LLAddr",
	"Watch Lo",
	"Watch Hi",
	"X Context",
	"Reserved",
	"Impl Dep",
	"Debug",
	"DEPC",
	"PerfCnt",
	"ErrCtl",
	"CacheErr",
	"TagLo",
	"TagHi",
	"ErrorEPC",
	"DESAVE"
पूर्ण;

व्योम kvm_mips_dump_stats(काष्ठा kvm_vcpu *vcpu)
अणु
#अगर_घोषित CONFIG_KVM_MIPS_DEBUG_COP0_COUNTERS
	पूर्णांक i, j;

	kvm_info("\nKVM VCPU[%d] COP0 Access Profile:\n", vcpu->vcpu_id);
	क्रम (i = 0; i < N_MIPS_COPROC_REGS; i++) अणु
		क्रम (j = 0; j < N_MIPS_COPROC_SEL; j++) अणु
			अगर (vcpu->arch.cop0->stat[i][j])
				kvm_info("%s[%d]: %lu\n", kvm_cop0_str[i], j,
					 vcpu->arch.cop0->stat[i][j]);
		पूर्ण
	पूर्ण
#पूर्ण_अगर
पूर्ण
