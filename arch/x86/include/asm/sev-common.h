<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * AMD SEV header common between the guest and the hypervisor.
 *
 * Author: Brijesh Singh <brijesh.singh@amd.com>
 */

#अगर_अघोषित __ASM_X86_SEV_COMMON_H
#घोषणा __ASM_X86_SEV_COMMON_H

#घोषणा GHCB_MSR_INFO_POS		0
#घोषणा GHCB_MSR_INFO_MASK		(BIT_ULL(12) - 1)

#घोषणा GHCB_MSR_SEV_INFO_RESP		0x001
#घोषणा GHCB_MSR_SEV_INFO_REQ		0x002
#घोषणा GHCB_MSR_VER_MAX_POS		48
#घोषणा GHCB_MSR_VER_MAX_MASK		0xffff
#घोषणा GHCB_MSR_VER_MIN_POS		32
#घोषणा GHCB_MSR_VER_MIN_MASK		0xffff
#घोषणा GHCB_MSR_CBIT_POS		24
#घोषणा GHCB_MSR_CBIT_MASK		0xff
#घोषणा GHCB_MSR_SEV_INFO(_max, _min, _cbit)				\
	((((_max) & GHCB_MSR_VER_MAX_MASK) << GHCB_MSR_VER_MAX_POS) |	\
	 (((_min) & GHCB_MSR_VER_MIN_MASK) << GHCB_MSR_VER_MIN_POS) |	\
	 (((_cbit) & GHCB_MSR_CBIT_MASK) << GHCB_MSR_CBIT_POS) |	\
	 GHCB_MSR_SEV_INFO_RESP)
#घोषणा GHCB_MSR_INFO(v)		((v) & 0xfffUL)
#घोषणा GHCB_MSR_PROTO_MAX(v)		(((v) >> GHCB_MSR_VER_MAX_POS) & GHCB_MSR_VER_MAX_MASK)
#घोषणा GHCB_MSR_PROTO_MIN(v)		(((v) >> GHCB_MSR_VER_MIN_POS) & GHCB_MSR_VER_MIN_MASK)

#घोषणा GHCB_MSR_CPUID_REQ		0x004
#घोषणा GHCB_MSR_CPUID_RESP		0x005
#घोषणा GHCB_MSR_CPUID_FUNC_POS		32
#घोषणा GHCB_MSR_CPUID_FUNC_MASK	0xffffffff
#घोषणा GHCB_MSR_CPUID_VALUE_POS	32
#घोषणा GHCB_MSR_CPUID_VALUE_MASK	0xffffffff
#घोषणा GHCB_MSR_CPUID_REG_POS		30
#घोषणा GHCB_MSR_CPUID_REG_MASK		0x3
#घोषणा GHCB_CPUID_REQ_EAX		0
#घोषणा GHCB_CPUID_REQ_EBX		1
#घोषणा GHCB_CPUID_REQ_ECX		2
#घोषणा GHCB_CPUID_REQ_EDX		3
#घोषणा GHCB_CPUID_REQ(fn, reg)		\
		(GHCB_MSR_CPUID_REQ | \
		(((अचिन्हित दीर्घ)reg & GHCB_MSR_CPUID_REG_MASK) << GHCB_MSR_CPUID_REG_POS) | \
		(((अचिन्हित दीर्घ)fn) << GHCB_MSR_CPUID_FUNC_POS))

#घोषणा GHCB_MSR_TERM_REQ		0x100
#घोषणा GHCB_MSR_TERM_REASON_SET_POS	12
#घोषणा GHCB_MSR_TERM_REASON_SET_MASK	0xf
#घोषणा GHCB_MSR_TERM_REASON_POS	16
#घोषणा GHCB_MSR_TERM_REASON_MASK	0xff
#घोषणा GHCB_SEV_TERM_REASON(reason_set, reason_val)						  \
	(((((u64)reason_set) &  GHCB_MSR_TERM_REASON_SET_MASK) << GHCB_MSR_TERM_REASON_SET_POS) | \
	((((u64)reason_val) & GHCB_MSR_TERM_REASON_MASK) << GHCB_MSR_TERM_REASON_POS))

#घोषणा GHCB_SEV_ES_REASON_GENERAL_REQUEST	0
#घोषणा GHCB_SEV_ES_REASON_PROTOCOL_UNSUPPORTED	1

#घोषणा GHCB_RESP_CODE(v)		((v) & GHCB_MSR_INFO_MASK)

#पूर्ण_अगर
