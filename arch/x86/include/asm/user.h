<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_X86_USER_H
#घोषणा _ASM_X86_USER_H

#अगर_घोषित CONFIG_X86_32
# include <यंत्र/user_32.h>
#अन्यथा
# include <यंत्र/user_64.h>
#पूर्ण_अगर

#समावेश <यंत्र/types.h>

काष्ठा user_ymmh_regs अणु
	/* 16 * 16 bytes क्रम each YMMH-reg */
	__u32 ymmh_space[64];
पूर्ण;

काष्ठा user_xstate_header अणु
	__u64 xfeatures;
	__u64 reserved1[2];
	__u64 reserved2[5];
पूर्ण;

/*
 * The काष्ठाure layout of user_xstateregs, used क्रम exporting the
 * extended रेजिस्टर state through ptrace and core-dump (NT_X86_XSTATE note)
 * पूर्णांकerfaces will be same as the memory layout of xsave used by the processor
 * (except क्रम the bytes 464..511, which can be used by the software) and hence
 * the size of this काष्ठाure varies depending on the features supported by the
 * processor and OS. The size of the काष्ठाure that users need to use can be
 * obtained by करोing:
 *     cpuid_count(0xd, 0, &eax, &ptrace_xstateregs_काष्ठा_size, &ecx, &edx);
 * i.e., cpuid.(eax=0xd,ecx=0).ebx will be the size that user (debuggers, etc.)
 * need to use.
 *
 * For now, only the first 8 bytes of the software usable bytes[464..471] will
 * be used and will be set to OS enabled xstate mask (which is same as the
 * 64bit mask वापसed by the xgetbv's xCR0).  Users (analyzing core dump
 * remotely, etc.) can use this mask as well as the mask saved in the
 * xstate_hdr bytes and पूर्णांकerpret what states the processor/OS supports
 * and what states are in modअगरied/initialized conditions क्रम the
 * particular process/thपढ़ो.
 *
 * Also when the user modअगरies certain state FP/SSE/etc through the
 * ptrace पूर्णांकerface, they must ensure that the header.xfeatures
 * bytes[512..519] of the memory layout are updated correspondingly.
 * i.e., क्रम example when FP state is modअगरied to a non-init state,
 * header.xfeatures's bit 0 must be set to '1', when SSE is modअगरied to
 * non-init state, header.xfeatures's bit 1 must to be set to '1', etc.
 */
#घोषणा USER_XSTATE_FX_SW_WORDS 6
#घोषणा USER_XSTATE_XCR0_WORD	0

काष्ठा user_xstateregs अणु
	काष्ठा अणु
		__u64 fpx_space[58];
		__u64 xstate_fx_sw[USER_XSTATE_FX_SW_WORDS];
	पूर्ण i387;
	काष्ठा user_xstate_header header;
	काष्ठा user_ymmh_regs ymmh;
	/* further processor state extensions go here */
पूर्ण;

#पूर्ण_अगर /* _ASM_X86_USER_H */
