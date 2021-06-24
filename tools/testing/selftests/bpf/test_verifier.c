<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Testsuite क्रम eBPF verअगरier
 *
 * Copyright (c) 2014 PLUMgrid, http://plumgrid.com
 * Copyright (c) 2017 Facebook
 * Copyright (c) 2018 Covalent IO, Inc. http://covalent.io
 */

#समावेश <endian.h>
#समावेश <यंत्र/types.h>
#समावेश <linux/types.h>
#समावेश <मानक_निवेशt.h>
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <unistd.h>
#समावेश <त्रुटिसं.स>
#समावेश <माला.स>
#समावेश <मानकघोष.स>
#समावेश <stdbool.h>
#समावेश <sched.h>
#समावेश <सीमा.स>
#समावेश <निश्चित.स>

#समावेश <sys/capability.h>

#समावेश <linux/unistd.h>
#समावेश <linux/filter.h>
#समावेश <linux/bpf_perf_event.h>
#समावेश <linux/bpf.h>
#समावेश <linux/अगर_ether.h>
#समावेश <linux/btf.h>

#समावेश <bpf/bpf.h>
#समावेश <bpf/libbpf.h>

#अगर_घोषित HAVE_GENHDR
# include "autoconf.h"
#अन्यथा
# अगर defined(__i386) || defined(__x86_64) || defined(__s390x__) || defined(__aarch64__)
#  define CONFIG_HAVE_EFFICIENT_UNALIGNED_ACCESS 1
# endअगर
#पूर्ण_अगर
#समावेश "bpf_rlimit.h"
#समावेश "bpf_rand.h"
#समावेश "bpf_util.h"
#समावेश "test_btf.h"
#समावेश "../../../include/linux/filter.h"

#घोषणा MAX_INSNS	BPF_MAXINSNS
#घोषणा MAX_TEST_INSNS	1000000
#घोषणा MAX_FIXUPS	8
#घोषणा MAX_NR_MAPS	21
#घोषणा MAX_TEST_RUNS	8
#घोषणा POINTER_VALUE	0xcafe4all
#घोषणा TEST_DATA_LEN	64

#घोषणा F_NEEDS_EFFICIENT_UNALIGNED_ACCESS	(1 << 0)
#घोषणा F_LOAD_WITH_STRICT_ALIGNMENT		(1 << 1)

#घोषणा UNPRIV_SYSCTL "kernel/unprivileged_bpf_disabled"
अटल bool unpriv_disabled = false;
अटल पूर्णांक skips;
अटल bool verbose = false;

काष्ठा bpf_test अणु
	स्थिर अक्षर *descr;
	काष्ठा bpf_insn	insns[MAX_INSNS];
	काष्ठा bpf_insn	*fill_insns;
	पूर्णांक fixup_map_hash_8b[MAX_FIXUPS];
	पूर्णांक fixup_map_hash_48b[MAX_FIXUPS];
	पूर्णांक fixup_map_hash_16b[MAX_FIXUPS];
	पूर्णांक fixup_map_array_48b[MAX_FIXUPS];
	पूर्णांक fixup_map_sockmap[MAX_FIXUPS];
	पूर्णांक fixup_map_sockhash[MAX_FIXUPS];
	पूर्णांक fixup_map_xskmap[MAX_FIXUPS];
	पूर्णांक fixup_map_stacktrace[MAX_FIXUPS];
	पूर्णांक fixup_prog1[MAX_FIXUPS];
	पूर्णांक fixup_prog2[MAX_FIXUPS];
	पूर्णांक fixup_map_in_map[MAX_FIXUPS];
	पूर्णांक fixup_cgroup_storage[MAX_FIXUPS];
	पूर्णांक fixup_percpu_cgroup_storage[MAX_FIXUPS];
	पूर्णांक fixup_map_spin_lock[MAX_FIXUPS];
	पूर्णांक fixup_map_array_ro[MAX_FIXUPS];
	पूर्णांक fixup_map_array_wo[MAX_FIXUPS];
	पूर्णांक fixup_map_array_small[MAX_FIXUPS];
	पूर्णांक fixup_sk_storage_map[MAX_FIXUPS];
	पूर्णांक fixup_map_event_output[MAX_FIXUPS];
	पूर्णांक fixup_map_reuseport_array[MAX_FIXUPS];
	पूर्णांक fixup_map_ringbuf[MAX_FIXUPS];
	/* Expected verअगरier log output क्रम result REJECT or VERBOSE_ACCEPT.
	 * Can be a tab-separated sequence of expected strings. An empty string
	 * means no log verअगरication.
	 */
	स्थिर अक्षर *errstr;
	स्थिर अक्षर *errstr_unpriv;
	uपूर्णांक32_t insn_processed;
	पूर्णांक prog_len;
	क्रमागत अणु
		UNDEF,
		ACCEPT,
		REJECT,
		VERBOSE_ACCEPT,
	पूर्ण result, result_unpriv;
	क्रमागत bpf_prog_type prog_type;
	uपूर्णांक8_t flags;
	व्योम (*fill_helper)(काष्ठा bpf_test *self);
	पूर्णांक runs;
#घोषणा bpf_testdata_काष्ठा_t					\
	काष्ठा अणु						\
		uपूर्णांक32_t retval, retval_unpriv;			\
		जोड़ अणु						\
			__u8 data[TEST_DATA_LEN];		\
			__u64 data64[TEST_DATA_LEN / 8];	\
		पूर्ण;						\
	पूर्ण
	जोड़ अणु
		bpf_testdata_काष्ठा_t;
		bpf_testdata_काष्ठा_t retvals[MAX_TEST_RUNS];
	पूर्ण;
	क्रमागत bpf_attach_type expected_attach_type;
	स्थिर अक्षर *kfunc;
पूर्ण;

/* Note we want this to be 64 bit aligned so that the end of our array is
 * actually the end of the काष्ठाure.
 */
#घोषणा MAX_ENTRIES 11

काष्ठा test_val अणु
	अचिन्हित पूर्णांक index;
	पूर्णांक foo[MAX_ENTRIES];
पूर्ण;

काष्ठा other_val अणु
	दीर्घ दीर्घ foo;
	दीर्घ दीर्घ bar;
पूर्ण;

अटल व्योम bpf_fill_ld_असल_vlan_push_pop(काष्ठा bpf_test *self)
अणु
	/* test: अणुskb->data[0], vlan_pushपूर्ण x 51 + अणुskb->data[0], vlan_popपूर्ण x 51 */
#घोषणा PUSH_CNT 51
	/* jump range is limited to 16 bit. PUSH_CNT of ld_असल needs room */
	अचिन्हित पूर्णांक len = (1 << 15) - PUSH_CNT * 2 * 5 * 6;
	काष्ठा bpf_insn *insn = self->fill_insns;
	पूर्णांक i = 0, j, k = 0;

	insn[i++] = BPF_MOV64_REG(BPF_REG_6, BPF_REG_1);
loop:
	क्रम (j = 0; j < PUSH_CNT; j++) अणु
		insn[i++] = BPF_LD_ABS(BPF_B, 0);
		/* jump to error label */
		insn[i] = BPF_JMP32_IMM(BPF_JNE, BPF_REG_0, 0x34, len - i - 3);
		i++;
		insn[i++] = BPF_MOV64_REG(BPF_REG_1, BPF_REG_6);
		insn[i++] = BPF_MOV64_IMM(BPF_REG_2, 1);
		insn[i++] = BPF_MOV64_IMM(BPF_REG_3, 2);
		insn[i++] = BPF_RAW_INSN(BPF_JMP | BPF_CALL, 0, 0, 0,
					 BPF_FUNC_skb_vlan_push),
		insn[i] = BPF_JMP_IMM(BPF_JNE, BPF_REG_0, 0, len - i - 3);
		i++;
	पूर्ण

	क्रम (j = 0; j < PUSH_CNT; j++) अणु
		insn[i++] = BPF_LD_ABS(BPF_B, 0);
		insn[i] = BPF_JMP32_IMM(BPF_JNE, BPF_REG_0, 0x34, len - i - 3);
		i++;
		insn[i++] = BPF_MOV64_REG(BPF_REG_1, BPF_REG_6);
		insn[i++] = BPF_RAW_INSN(BPF_JMP | BPF_CALL, 0, 0, 0,
					 BPF_FUNC_skb_vlan_pop),
		insn[i] = BPF_JMP_IMM(BPF_JNE, BPF_REG_0, 0, len - i - 3);
		i++;
	पूर्ण
	अगर (++k < 5)
		जाओ loop;

	क्रम (; i < len - 3; i++)
		insn[i] = BPF_ALU64_IMM(BPF_MOV, BPF_REG_0, 0xbef);
	insn[len - 3] = BPF_JMP_A(1);
	/* error label */
	insn[len - 2] = BPF_MOV32_IMM(BPF_REG_0, 0);
	insn[len - 1] = BPF_EXIT_INSN();
	self->prog_len = len;
पूर्ण

अटल व्योम bpf_fill_jump_around_ld_असल(काष्ठा bpf_test *self)
अणु
	काष्ठा bpf_insn *insn = self->fill_insns;
	/* jump range is limited to 16 bit. every ld_असल is replaced by 6 insns,
	 * but on arches like arm, ppc etc, there will be one BPF_ZEXT inserted
	 * to extend the error value of the अंतरभूतd ld_असल sequence which then
	 * contains 7 insns. so, set the भागidend to 7 so the testहाल could
	 * work on all arches.
	 */
	अचिन्हित पूर्णांक len = (1 << 15) / 7;
	पूर्णांक i = 0;

	insn[i++] = BPF_MOV64_REG(BPF_REG_6, BPF_REG_1);
	insn[i++] = BPF_LD_ABS(BPF_B, 0);
	insn[i] = BPF_JMP_IMM(BPF_JEQ, BPF_REG_0, 10, len - i - 2);
	i++;
	जबतक (i < len - 1)
		insn[i++] = BPF_LD_ABS(BPF_B, 1);
	insn[i] = BPF_EXIT_INSN();
	self->prog_len = i + 1;
पूर्ण

अटल व्योम bpf_fill_अक्रम_ld_dw(काष्ठा bpf_test *self)
अणु
	काष्ठा bpf_insn *insn = self->fill_insns;
	uपूर्णांक64_t res = 0;
	पूर्णांक i = 0;

	insn[i++] = BPF_MOV32_IMM(BPF_REG_0, 0);
	जबतक (i < self->retval) अणु
		uपूर्णांक64_t val = bpf_semi_अक्रम_get();
		काष्ठा bpf_insn पंचांगp[2] = अणु BPF_LD_IMM64(BPF_REG_1, val) पूर्ण;

		res ^= val;
		insn[i++] = पंचांगp[0];
		insn[i++] = पंचांगp[1];
		insn[i++] = BPF_ALU64_REG(BPF_XOR, BPF_REG_0, BPF_REG_1);
	पूर्ण
	insn[i++] = BPF_MOV64_REG(BPF_REG_1, BPF_REG_0);
	insn[i++] = BPF_ALU64_IMM(BPF_RSH, BPF_REG_1, 32);
	insn[i++] = BPF_ALU64_REG(BPF_XOR, BPF_REG_0, BPF_REG_1);
	insn[i] = BPF_EXIT_INSN();
	self->prog_len = i + 1;
	res ^= (res >> 32);
	self->retval = (uपूर्णांक32_t)res;
पूर्ण

#घोषणा MAX_JMP_SEQ 8192

/* test the sequence of 8k jumps */
अटल व्योम bpf_fill_scale1(काष्ठा bpf_test *self)
अणु
	काष्ठा bpf_insn *insn = self->fill_insns;
	पूर्णांक i = 0, k = 0;

	insn[i++] = BPF_MOV64_REG(BPF_REG_6, BPF_REG_1);
	/* test to check that the दीर्घ sequence of jumps is acceptable */
	जबतक (k++ < MAX_JMP_SEQ) अणु
		insn[i++] = BPF_RAW_INSN(BPF_JMP | BPF_CALL, 0, 0, 0,
					 BPF_FUNC_get_pअक्रमom_u32);
		insn[i++] = BPF_JMP_IMM(BPF_JEQ, BPF_REG_0, bpf_semi_अक्रम_get(), 2);
		insn[i++] = BPF_MOV64_REG(BPF_REG_1, BPF_REG_10);
		insn[i++] = BPF_STX_MEM(BPF_DW, BPF_REG_1, BPF_REG_6,
					-8 * (k % 64 + 1));
	पूर्ण
	/* is_state_visited() करोesn't allocate state क्रम pruning क्रम every jump.
	 * Hence multiply jmps by 4 to accommodate that heuristic
	 */
	जबतक (i < MAX_TEST_INSNS - MAX_JMP_SEQ * 4)
		insn[i++] = BPF_ALU64_IMM(BPF_MOV, BPF_REG_0, 42);
	insn[i] = BPF_EXIT_INSN();
	self->prog_len = i + 1;
	self->retval = 42;
पूर्ण

/* test the sequence of 8k jumps in inner most function (function depth 8)*/
अटल व्योम bpf_fill_scale2(काष्ठा bpf_test *self)
अणु
	काष्ठा bpf_insn *insn = self->fill_insns;
	पूर्णांक i = 0, k = 0;

#घोषणा FUNC_NEST 7
	क्रम (k = 0; k < FUNC_NEST; k++) अणु
		insn[i++] = BPF_CALL_REL(1);
		insn[i++] = BPF_EXIT_INSN();
	पूर्ण
	insn[i++] = BPF_MOV64_REG(BPF_REG_6, BPF_REG_1);
	/* test to check that the दीर्घ sequence of jumps is acceptable */
	k = 0;
	जबतक (k++ < MAX_JMP_SEQ) अणु
		insn[i++] = BPF_RAW_INSN(BPF_JMP | BPF_CALL, 0, 0, 0,
					 BPF_FUNC_get_pअक्रमom_u32);
		insn[i++] = BPF_JMP_IMM(BPF_JEQ, BPF_REG_0, bpf_semi_अक्रम_get(), 2);
		insn[i++] = BPF_MOV64_REG(BPF_REG_1, BPF_REG_10);
		insn[i++] = BPF_STX_MEM(BPF_DW, BPF_REG_1, BPF_REG_6,
					-8 * (k % (64 - 4 * FUNC_NEST) + 1));
	पूर्ण
	जबतक (i < MAX_TEST_INSNS - MAX_JMP_SEQ * 4)
		insn[i++] = BPF_ALU64_IMM(BPF_MOV, BPF_REG_0, 42);
	insn[i] = BPF_EXIT_INSN();
	self->prog_len = i + 1;
	self->retval = 42;
पूर्ण

अटल व्योम bpf_fill_scale(काष्ठा bpf_test *self)
अणु
	चयन (self->retval) अणु
	हाल 1:
		वापस bpf_fill_scale1(self);
	हाल 2:
		वापस bpf_fill_scale2(self);
	शेष:
		self->prog_len = 0;
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक bpf_fill_torturous_jumps_insn_1(काष्ठा bpf_insn *insn)
अणु
	अचिन्हित पूर्णांक len = 259, hlen = 128;
	पूर्णांक i;

	insn[0] = BPF_EMIT_CALL(BPF_FUNC_get_pअक्रमom_u32);
	क्रम (i = 1; i <= hlen; i++) अणु
		insn[i]        = BPF_JMP_IMM(BPF_JEQ, BPF_REG_0, i, hlen);
		insn[i + hlen] = BPF_JMP_A(hlen - i);
	पूर्ण
	insn[len - 2] = BPF_MOV64_IMM(BPF_REG_0, 1);
	insn[len - 1] = BPF_EXIT_INSN();

	वापस len;
पूर्ण

अटल पूर्णांक bpf_fill_torturous_jumps_insn_2(काष्ठा bpf_insn *insn)
अणु
	अचिन्हित पूर्णांक len = 4100, jmp_off = 2048;
	पूर्णांक i, j;

	insn[0] = BPF_EMIT_CALL(BPF_FUNC_get_pअक्रमom_u32);
	क्रम (i = 1; i <= jmp_off; i++) अणु
		insn[i] = BPF_JMP_IMM(BPF_JEQ, BPF_REG_0, i, jmp_off);
	पूर्ण
	insn[i++] = BPF_JMP_A(jmp_off);
	क्रम (; i <= jmp_off * 2 + 1; i+=16) अणु
		क्रम (j = 0; j < 16; j++) अणु
			insn[i + j] = BPF_JMP_A(16 - j - 1);
		पूर्ण
	पूर्ण

	insn[len - 2] = BPF_MOV64_IMM(BPF_REG_0, 2);
	insn[len - 1] = BPF_EXIT_INSN();

	वापस len;
पूर्ण

अटल व्योम bpf_fill_torturous_jumps(काष्ठा bpf_test *self)
अणु
	काष्ठा bpf_insn *insn = self->fill_insns;
	पूर्णांक i = 0;

	चयन (self->retval) अणु
	हाल 1:
		self->prog_len = bpf_fill_torturous_jumps_insn_1(insn);
		वापस;
	हाल 2:
		self->prog_len = bpf_fill_torturous_jumps_insn_2(insn);
		वापस;
	हाल 3:
		/* मुख्य */
		insn[i++] = BPF_RAW_INSN(BPF_JMP|BPF_CALL, 0, 1, 0, 4);
		insn[i++] = BPF_RAW_INSN(BPF_JMP|BPF_CALL, 0, 1, 0, 262);
		insn[i++] = BPF_ST_MEM(BPF_B, BPF_REG_10, -32, 0);
		insn[i++] = BPF_MOV64_IMM(BPF_REG_0, 3);
		insn[i++] = BPF_EXIT_INSN();

		/* subprog 1 */
		i += bpf_fill_torturous_jumps_insn_1(insn + i);

		/* subprog 2 */
		i += bpf_fill_torturous_jumps_insn_2(insn + i);

		self->prog_len = i;
		वापस;
	शेष:
		self->prog_len = 0;
		अवरोध;
	पूर्ण
पूर्ण

/* BPF_SK_LOOKUP contains 13 inकाष्ठाions, अगर you need to fix up maps */
#घोषणा BPF_SK_LOOKUP(func)						\
	/* काष्ठा bpf_sock_tuple tuple = अणुपूर्ण */				\
	BPF_MOV64_IMM(BPF_REG_2, 0),					\
	BPF_STX_MEM(BPF_W, BPF_REG_10, BPF_REG_2, -8),			\
	BPF_STX_MEM(BPF_DW, BPF_REG_10, BPF_REG_2, -16),		\
	BPF_STX_MEM(BPF_DW, BPF_REG_10, BPF_REG_2, -24),		\
	BPF_STX_MEM(BPF_DW, BPF_REG_10, BPF_REG_2, -32),		\
	BPF_STX_MEM(BPF_DW, BPF_REG_10, BPF_REG_2, -40),		\
	BPF_STX_MEM(BPF_DW, BPF_REG_10, BPF_REG_2, -48),		\
	/* sk = func(ctx, &tuple, माप tuple, 0, 0) */		\
	BPF_MOV64_REG(BPF_REG_2, BPF_REG_10),				\
	BPF_ALU64_IMM(BPF_ADD, BPF_REG_2, -48),				\
	BPF_MOV64_IMM(BPF_REG_3, माप(काष्ठा bpf_sock_tuple)),	\
	BPF_MOV64_IMM(BPF_REG_4, 0),					\
	BPF_MOV64_IMM(BPF_REG_5, 0),					\
	BPF_EMIT_CALL(BPF_FUNC_ ## func)

/* BPF_सूचीECT_PKT_R2 contains 7 inकाष्ठाions, it initializes शेष वापस
 * value पूर्णांकo 0 and करोes necessary preparation क्रम direct packet access
 * through r2. The allowed access range is 8 bytes.
 */
#घोषणा BPF_सूचीECT_PKT_R2						\
	BPF_MOV64_IMM(BPF_REG_0, 0),					\
	BPF_LDX_MEM(BPF_W, BPF_REG_2, BPF_REG_1,			\
		    दुरत्व(काष्ठा __sk_buff, data)),			\
	BPF_LDX_MEM(BPF_W, BPF_REG_3, BPF_REG_1,			\
		    दुरत्व(काष्ठा __sk_buff, data_end)),		\
	BPF_MOV64_REG(BPF_REG_4, BPF_REG_2),				\
	BPF_ALU64_IMM(BPF_ADD, BPF_REG_4, 8),				\
	BPF_JMP_REG(BPF_JLE, BPF_REG_4, BPF_REG_3, 1),			\
	BPF_EXIT_INSN()

/* BPF_RAND_UEXT_R7 contains 4 inकाष्ठाions, it initializes R7 पूर्णांकo a अक्रमom
 * positive u32, and zero-extend it पूर्णांकo 64-bit.
 */
#घोषणा BPF_RAND_UEXT_R7						\
	BPF_RAW_INSN(BPF_JMP | BPF_CALL, 0, 0, 0,			\
		     BPF_FUNC_get_pअक्रमom_u32),				\
	BPF_MOV64_REG(BPF_REG_7, BPF_REG_0),				\
	BPF_ALU64_IMM(BPF_LSH, BPF_REG_7, 33),				\
	BPF_ALU64_IMM(BPF_RSH, BPF_REG_7, 33)

/* BPF_RAND_SEXT_R7 contains 5 inकाष्ठाions, it initializes R7 पूर्णांकo a अक्रमom
 * negative u32, and sign-extend it पूर्णांकo 64-bit.
 */
#घोषणा BPF_RAND_SEXT_R7						\
	BPF_RAW_INSN(BPF_JMP | BPF_CALL, 0, 0, 0,			\
		     BPF_FUNC_get_pअक्रमom_u32),				\
	BPF_MOV64_REG(BPF_REG_7, BPF_REG_0),				\
	BPF_ALU64_IMM(BPF_OR, BPF_REG_7, 0x80000000),			\
	BPF_ALU64_IMM(BPF_LSH, BPF_REG_7, 32),				\
	BPF_ALU64_IMM(BPF_ARSH, BPF_REG_7, 32)

अटल काष्ठा bpf_test tests[] = अणु
#घोषणा FILL_ARRAY
#समावेश <verअगरier/tests.h>
#अघोषित FILL_ARRAY
पूर्ण;

अटल पूर्णांक probe_filter_length(स्थिर काष्ठा bpf_insn *fp)
अणु
	पूर्णांक len;

	क्रम (len = MAX_INSNS - 1; len > 0; --len)
		अगर (fp[len].code != 0 || fp[len].imm != 0)
			अवरोध;
	वापस len + 1;
पूर्ण

अटल bool skip_unsupported_map(क्रमागत bpf_map_type map_type)
अणु
	अगर (!bpf_probe_map_type(map_type, 0)) अणु
		म_लिखो("SKIP (unsupported map type %d)\n", map_type);
		skips++;
		वापस true;
	पूर्ण
	वापस false;
पूर्ण

अटल पूर्णांक __create_map(uपूर्णांक32_t type, uपूर्णांक32_t size_key,
			uपूर्णांक32_t size_value, uपूर्णांक32_t max_elem,
			uपूर्णांक32_t extra_flags)
अणु
	पूर्णांक fd;

	fd = bpf_create_map(type, size_key, size_value, max_elem,
			    (type == BPF_MAP_TYPE_HASH ?
			     BPF_F_NO_PREALLOC : 0) | extra_flags);
	अगर (fd < 0) अणु
		अगर (skip_unsupported_map(type))
			वापस -1;
		म_लिखो("Failed to create hash map '%s'!\n", म_त्रुटि(त्रुटि_सं));
	पूर्ण

	वापस fd;
पूर्ण

अटल पूर्णांक create_map(uपूर्णांक32_t type, uपूर्णांक32_t size_key,
		      uपूर्णांक32_t size_value, uपूर्णांक32_t max_elem)
अणु
	वापस __create_map(type, size_key, size_value, max_elem, 0);
पूर्ण

अटल व्योम update_map(पूर्णांक fd, पूर्णांक index)
अणु
	काष्ठा test_val value = अणु
		.index = (6 + 1) * माप(पूर्णांक),
		.foo[6] = 0xabcdef12,
	पूर्ण;

	निश्चित(!bpf_map_update_elem(fd, &index, &value, 0));
पूर्ण

अटल पूर्णांक create_prog_dummy_simple(क्रमागत bpf_prog_type prog_type, पूर्णांक ret)
अणु
	काष्ठा bpf_insn prog[] = अणु
		BPF_MOV64_IMM(BPF_REG_0, ret),
		BPF_EXIT_INSN(),
	पूर्ण;

	वापस bpf_load_program(prog_type, prog,
				ARRAY_SIZE(prog), "GPL", 0, शून्य, 0);
पूर्ण

अटल पूर्णांक create_prog_dummy_loop(क्रमागत bpf_prog_type prog_type, पूर्णांक mfd,
				  पूर्णांक idx, पूर्णांक ret)
अणु
	काष्ठा bpf_insn prog[] = अणु
		BPF_MOV64_IMM(BPF_REG_3, idx),
		BPF_LD_MAP_FD(BPF_REG_2, mfd),
		BPF_RAW_INSN(BPF_JMP | BPF_CALL, 0, 0, 0,
			     BPF_FUNC_tail_call),
		BPF_MOV64_IMM(BPF_REG_0, ret),
		BPF_EXIT_INSN(),
	पूर्ण;

	वापस bpf_load_program(prog_type, prog,
				ARRAY_SIZE(prog), "GPL", 0, शून्य, 0);
पूर्ण

अटल पूर्णांक create_prog_array(क्रमागत bpf_prog_type prog_type, uपूर्णांक32_t max_elem,
			     पूर्णांक p1key, पूर्णांक p2key, पूर्णांक p3key)
अणु
	पूर्णांक mfd, p1fd, p2fd, p3fd;

	mfd = bpf_create_map(BPF_MAP_TYPE_PROG_ARRAY, माप(पूर्णांक),
			     माप(पूर्णांक), max_elem, 0);
	अगर (mfd < 0) अणु
		अगर (skip_unsupported_map(BPF_MAP_TYPE_PROG_ARRAY))
			वापस -1;
		म_लिखो("Failed to create prog array '%s'!\n", म_त्रुटि(त्रुटि_सं));
		वापस -1;
	पूर्ण

	p1fd = create_prog_dummy_simple(prog_type, 42);
	p2fd = create_prog_dummy_loop(prog_type, mfd, p2key, 41);
	p3fd = create_prog_dummy_simple(prog_type, 24);
	अगर (p1fd < 0 || p2fd < 0 || p3fd < 0)
		जाओ err;
	अगर (bpf_map_update_elem(mfd, &p1key, &p1fd, BPF_ANY) < 0)
		जाओ err;
	अगर (bpf_map_update_elem(mfd, &p2key, &p2fd, BPF_ANY) < 0)
		जाओ err;
	अगर (bpf_map_update_elem(mfd, &p3key, &p3fd, BPF_ANY) < 0) अणु
err:
		बंद(mfd);
		mfd = -1;
	पूर्ण
	बंद(p3fd);
	बंद(p2fd);
	बंद(p1fd);
	वापस mfd;
पूर्ण

अटल पूर्णांक create_map_in_map(व्योम)
अणु
	पूर्णांक inner_map_fd, outer_map_fd;

	inner_map_fd = bpf_create_map(BPF_MAP_TYPE_ARRAY, माप(पूर्णांक),
				      माप(पूर्णांक), 1, 0);
	अगर (inner_map_fd < 0) अणु
		अगर (skip_unsupported_map(BPF_MAP_TYPE_ARRAY))
			वापस -1;
		म_लिखो("Failed to create array '%s'!\n", म_त्रुटि(त्रुटि_सं));
		वापस inner_map_fd;
	पूर्ण

	outer_map_fd = bpf_create_map_in_map(BPF_MAP_TYPE_ARRAY_OF_MAPS, शून्य,
					     माप(पूर्णांक), inner_map_fd, 1, 0);
	अगर (outer_map_fd < 0) अणु
		अगर (skip_unsupported_map(BPF_MAP_TYPE_ARRAY_OF_MAPS))
			वापस -1;
		म_लिखो("Failed to create array of maps '%s'!\n",
		       म_त्रुटि(त्रुटि_सं));
	पूर्ण

	बंद(inner_map_fd);

	वापस outer_map_fd;
पूर्ण

अटल पूर्णांक create_cgroup_storage(bool percpu)
अणु
	क्रमागत bpf_map_type type = percpu ? BPF_MAP_TYPE_PERCPU_CGROUP_STORAGE :
		BPF_MAP_TYPE_CGROUP_STORAGE;
	पूर्णांक fd;

	fd = bpf_create_map(type, माप(काष्ठा bpf_cgroup_storage_key),
			    TEST_DATA_LEN, 0, 0);
	अगर (fd < 0) अणु
		अगर (skip_unsupported_map(type))
			वापस -1;
		म_लिखो("Failed to create cgroup storage '%s'!\n",
		       म_त्रुटि(त्रुटि_सं));
	पूर्ण

	वापस fd;
पूर्ण

/* काष्ठा bpf_spin_lock अणु
 *   पूर्णांक val;
 * पूर्ण;
 * काष्ठा val अणु
 *   पूर्णांक cnt;
 *   काष्ठा bpf_spin_lock l;
 * पूर्ण;
 */
अटल स्थिर अक्षर btf_str_sec[] = "\0bpf_spin_lock\0val\0cnt\0l";
अटल __u32 btf_raw_types[] = अणु
	/* पूर्णांक */
	BTF_TYPE_INT_ENC(0, BTF_INT_SIGNED, 0, 32, 4),  /* [1] */
	/* काष्ठा bpf_spin_lock */                      /* [2] */
	BTF_TYPE_ENC(1, BTF_INFO_ENC(BTF_KIND_STRUCT, 0, 1), 4),
	BTF_MEMBER_ENC(15, 1, 0), /* पूर्णांक val; */
	/* काष्ठा val */                                /* [3] */
	BTF_TYPE_ENC(15, BTF_INFO_ENC(BTF_KIND_STRUCT, 0, 2), 8),
	BTF_MEMBER_ENC(19, 1, 0), /* पूर्णांक cnt; */
	BTF_MEMBER_ENC(23, 2, 32),/* काष्ठा bpf_spin_lock l; */
पूर्ण;

अटल पूर्णांक load_btf(व्योम)
अणु
	काष्ठा btf_header hdr = अणु
		.magic = BTF_MAGIC,
		.version = BTF_VERSION,
		.hdr_len = माप(काष्ठा btf_header),
		.type_len = माप(btf_raw_types),
		.str_off = माप(btf_raw_types),
		.str_len = माप(btf_str_sec),
	पूर्ण;
	व्योम *ptr, *raw_btf;
	पूर्णांक btf_fd;

	ptr = raw_btf = दो_स्मृति(माप(hdr) + माप(btf_raw_types) +
			       माप(btf_str_sec));

	स_नकल(ptr, &hdr, माप(hdr));
	ptr += माप(hdr);
	स_नकल(ptr, btf_raw_types, hdr.type_len);
	ptr += hdr.type_len;
	स_नकल(ptr, btf_str_sec, hdr.str_len);
	ptr += hdr.str_len;

	btf_fd = bpf_load_btf(raw_btf, ptr - raw_btf, 0, 0, 0);
	मुक्त(raw_btf);
	अगर (btf_fd < 0)
		वापस -1;
	वापस btf_fd;
पूर्ण

अटल पूर्णांक create_map_spin_lock(व्योम)
अणु
	काष्ठा bpf_create_map_attr attr = अणु
		.name = "test_map",
		.map_type = BPF_MAP_TYPE_ARRAY,
		.key_size = 4,
		.value_size = 8,
		.max_entries = 1,
		.btf_key_type_id = 1,
		.btf_value_type_id = 3,
	पूर्ण;
	पूर्णांक fd, btf_fd;

	btf_fd = load_btf();
	अगर (btf_fd < 0)
		वापस -1;
	attr.btf_fd = btf_fd;
	fd = bpf_create_map_xattr(&attr);
	अगर (fd < 0)
		म_लिखो("Failed to create map with spin_lock\n");
	वापस fd;
पूर्ण

अटल पूर्णांक create_sk_storage_map(व्योम)
अणु
	काष्ठा bpf_create_map_attr attr = अणु
		.name = "test_map",
		.map_type = BPF_MAP_TYPE_SK_STORAGE,
		.key_size = 4,
		.value_size = 8,
		.max_entries = 0,
		.map_flags = BPF_F_NO_PREALLOC,
		.btf_key_type_id = 1,
		.btf_value_type_id = 3,
	पूर्ण;
	पूर्णांक fd, btf_fd;

	btf_fd = load_btf();
	अगर (btf_fd < 0)
		वापस -1;
	attr.btf_fd = btf_fd;
	fd = bpf_create_map_xattr(&attr);
	बंद(attr.btf_fd);
	अगर (fd < 0)
		म_लिखो("Failed to create sk_storage_map\n");
	वापस fd;
पूर्ण

अटल अक्षर bpf_vlog[अच_पूर्णांक_उच्च >> 8];

अटल व्योम करो_test_fixup(काष्ठा bpf_test *test, क्रमागत bpf_prog_type prog_type,
			  काष्ठा bpf_insn *prog, पूर्णांक *map_fds)
अणु
	पूर्णांक *fixup_map_hash_8b = test->fixup_map_hash_8b;
	पूर्णांक *fixup_map_hash_48b = test->fixup_map_hash_48b;
	पूर्णांक *fixup_map_hash_16b = test->fixup_map_hash_16b;
	पूर्णांक *fixup_map_array_48b = test->fixup_map_array_48b;
	पूर्णांक *fixup_map_sockmap = test->fixup_map_sockmap;
	पूर्णांक *fixup_map_sockhash = test->fixup_map_sockhash;
	पूर्णांक *fixup_map_xskmap = test->fixup_map_xskmap;
	पूर्णांक *fixup_map_stacktrace = test->fixup_map_stacktrace;
	पूर्णांक *fixup_prog1 = test->fixup_prog1;
	पूर्णांक *fixup_prog2 = test->fixup_prog2;
	पूर्णांक *fixup_map_in_map = test->fixup_map_in_map;
	पूर्णांक *fixup_cgroup_storage = test->fixup_cgroup_storage;
	पूर्णांक *fixup_percpu_cgroup_storage = test->fixup_percpu_cgroup_storage;
	पूर्णांक *fixup_map_spin_lock = test->fixup_map_spin_lock;
	पूर्णांक *fixup_map_array_ro = test->fixup_map_array_ro;
	पूर्णांक *fixup_map_array_wo = test->fixup_map_array_wo;
	पूर्णांक *fixup_map_array_small = test->fixup_map_array_small;
	पूर्णांक *fixup_sk_storage_map = test->fixup_sk_storage_map;
	पूर्णांक *fixup_map_event_output = test->fixup_map_event_output;
	पूर्णांक *fixup_map_reuseport_array = test->fixup_map_reuseport_array;
	पूर्णांक *fixup_map_ringbuf = test->fixup_map_ringbuf;

	अगर (test->fill_helper) अणु
		test->fill_insns = सुस्मृति(MAX_TEST_INSNS, माप(काष्ठा bpf_insn));
		test->fill_helper(test);
	पूर्ण

	/* Allocating HTs with 1 elem is fine here, since we only test
	 * क्रम verअगरier and not करो a runसमय lookup, so the only thing
	 * that really matters is value size in this हाल.
	 */
	अगर (*fixup_map_hash_8b) अणु
		map_fds[0] = create_map(BPF_MAP_TYPE_HASH, माप(दीर्घ दीर्घ),
					माप(दीर्घ दीर्घ), 1);
		करो अणु
			prog[*fixup_map_hash_8b].imm = map_fds[0];
			fixup_map_hash_8b++;
		पूर्ण जबतक (*fixup_map_hash_8b);
	पूर्ण

	अगर (*fixup_map_hash_48b) अणु
		map_fds[1] = create_map(BPF_MAP_TYPE_HASH, माप(दीर्घ दीर्घ),
					माप(काष्ठा test_val), 1);
		करो अणु
			prog[*fixup_map_hash_48b].imm = map_fds[1];
			fixup_map_hash_48b++;
		पूर्ण जबतक (*fixup_map_hash_48b);
	पूर्ण

	अगर (*fixup_map_hash_16b) अणु
		map_fds[2] = create_map(BPF_MAP_TYPE_HASH, माप(दीर्घ दीर्घ),
					माप(काष्ठा other_val), 1);
		करो अणु
			prog[*fixup_map_hash_16b].imm = map_fds[2];
			fixup_map_hash_16b++;
		पूर्ण जबतक (*fixup_map_hash_16b);
	पूर्ण

	अगर (*fixup_map_array_48b) अणु
		map_fds[3] = create_map(BPF_MAP_TYPE_ARRAY, माप(पूर्णांक),
					माप(काष्ठा test_val), 1);
		update_map(map_fds[3], 0);
		करो अणु
			prog[*fixup_map_array_48b].imm = map_fds[3];
			fixup_map_array_48b++;
		पूर्ण जबतक (*fixup_map_array_48b);
	पूर्ण

	अगर (*fixup_prog1) अणु
		map_fds[4] = create_prog_array(prog_type, 4, 0, 1, 2);
		करो अणु
			prog[*fixup_prog1].imm = map_fds[4];
			fixup_prog1++;
		पूर्ण जबतक (*fixup_prog1);
	पूर्ण

	अगर (*fixup_prog2) अणु
		map_fds[5] = create_prog_array(prog_type, 8, 7, 1, 2);
		करो अणु
			prog[*fixup_prog2].imm = map_fds[5];
			fixup_prog2++;
		पूर्ण जबतक (*fixup_prog2);
	पूर्ण

	अगर (*fixup_map_in_map) अणु
		map_fds[6] = create_map_in_map();
		करो अणु
			prog[*fixup_map_in_map].imm = map_fds[6];
			fixup_map_in_map++;
		पूर्ण जबतक (*fixup_map_in_map);
	पूर्ण

	अगर (*fixup_cgroup_storage) अणु
		map_fds[7] = create_cgroup_storage(false);
		करो अणु
			prog[*fixup_cgroup_storage].imm = map_fds[7];
			fixup_cgroup_storage++;
		पूर्ण जबतक (*fixup_cgroup_storage);
	पूर्ण

	अगर (*fixup_percpu_cgroup_storage) अणु
		map_fds[8] = create_cgroup_storage(true);
		करो अणु
			prog[*fixup_percpu_cgroup_storage].imm = map_fds[8];
			fixup_percpu_cgroup_storage++;
		पूर्ण जबतक (*fixup_percpu_cgroup_storage);
	पूर्ण
	अगर (*fixup_map_sockmap) अणु
		map_fds[9] = create_map(BPF_MAP_TYPE_SOCKMAP, माप(पूर्णांक),
					माप(पूर्णांक), 1);
		करो अणु
			prog[*fixup_map_sockmap].imm = map_fds[9];
			fixup_map_sockmap++;
		पूर्ण जबतक (*fixup_map_sockmap);
	पूर्ण
	अगर (*fixup_map_sockhash) अणु
		map_fds[10] = create_map(BPF_MAP_TYPE_SOCKHASH, माप(पूर्णांक),
					माप(पूर्णांक), 1);
		करो अणु
			prog[*fixup_map_sockhash].imm = map_fds[10];
			fixup_map_sockhash++;
		पूर्ण जबतक (*fixup_map_sockhash);
	पूर्ण
	अगर (*fixup_map_xskmap) अणु
		map_fds[11] = create_map(BPF_MAP_TYPE_XSKMAP, माप(पूर्णांक),
					माप(पूर्णांक), 1);
		करो अणु
			prog[*fixup_map_xskmap].imm = map_fds[11];
			fixup_map_xskmap++;
		पूर्ण जबतक (*fixup_map_xskmap);
	पूर्ण
	अगर (*fixup_map_stacktrace) अणु
		map_fds[12] = create_map(BPF_MAP_TYPE_STACK_TRACE, माप(u32),
					 माप(u64), 1);
		करो अणु
			prog[*fixup_map_stacktrace].imm = map_fds[12];
			fixup_map_stacktrace++;
		पूर्ण जबतक (*fixup_map_stacktrace);
	पूर्ण
	अगर (*fixup_map_spin_lock) अणु
		map_fds[13] = create_map_spin_lock();
		करो अणु
			prog[*fixup_map_spin_lock].imm = map_fds[13];
			fixup_map_spin_lock++;
		पूर्ण जबतक (*fixup_map_spin_lock);
	पूर्ण
	अगर (*fixup_map_array_ro) अणु
		map_fds[14] = __create_map(BPF_MAP_TYPE_ARRAY, माप(पूर्णांक),
					   माप(काष्ठा test_val), 1,
					   BPF_F_RDONLY_PROG);
		update_map(map_fds[14], 0);
		करो अणु
			prog[*fixup_map_array_ro].imm = map_fds[14];
			fixup_map_array_ro++;
		पूर्ण जबतक (*fixup_map_array_ro);
	पूर्ण
	अगर (*fixup_map_array_wo) अणु
		map_fds[15] = __create_map(BPF_MAP_TYPE_ARRAY, माप(पूर्णांक),
					   माप(काष्ठा test_val), 1,
					   BPF_F_WRONLY_PROG);
		update_map(map_fds[15], 0);
		करो अणु
			prog[*fixup_map_array_wo].imm = map_fds[15];
			fixup_map_array_wo++;
		पूर्ण जबतक (*fixup_map_array_wo);
	पूर्ण
	अगर (*fixup_map_array_small) अणु
		map_fds[16] = __create_map(BPF_MAP_TYPE_ARRAY, माप(पूर्णांक),
					   1, 1, 0);
		update_map(map_fds[16], 0);
		करो अणु
			prog[*fixup_map_array_small].imm = map_fds[16];
			fixup_map_array_small++;
		पूर्ण जबतक (*fixup_map_array_small);
	पूर्ण
	अगर (*fixup_sk_storage_map) अणु
		map_fds[17] = create_sk_storage_map();
		करो अणु
			prog[*fixup_sk_storage_map].imm = map_fds[17];
			fixup_sk_storage_map++;
		पूर्ण जबतक (*fixup_sk_storage_map);
	पूर्ण
	अगर (*fixup_map_event_output) अणु
		map_fds[18] = __create_map(BPF_MAP_TYPE_PERF_EVENT_ARRAY,
					   माप(पूर्णांक), माप(पूर्णांक), 1, 0);
		करो अणु
			prog[*fixup_map_event_output].imm = map_fds[18];
			fixup_map_event_output++;
		पूर्ण जबतक (*fixup_map_event_output);
	पूर्ण
	अगर (*fixup_map_reuseport_array) अणु
		map_fds[19] = __create_map(BPF_MAP_TYPE_REUSEPORT_SOCKARRAY,
					   माप(u32), माप(u64), 1, 0);
		करो अणु
			prog[*fixup_map_reuseport_array].imm = map_fds[19];
			fixup_map_reuseport_array++;
		पूर्ण जबतक (*fixup_map_reuseport_array);
	पूर्ण
	अगर (*fixup_map_ringbuf) अणु
		map_fds[20] = create_map(BPF_MAP_TYPE_RINGBUF, 0,
					   0, 4096);
		करो अणु
			prog[*fixup_map_ringbuf].imm = map_fds[20];
			fixup_map_ringbuf++;
		पूर्ण जबतक (*fixup_map_ringbuf);
	पूर्ण
पूर्ण

काष्ठा libcap अणु
	काष्ठा __user_cap_header_काष्ठा hdr;
	काष्ठा __user_cap_data_काष्ठा data[2];
पूर्ण;

अटल पूर्णांक set_admin(bool admin)
अणु
	cap_t caps;
	/* need CAP_BPF, CAP_NET_ADMIN, CAP_PERFMON to load progs */
	स्थिर cap_value_t cap_net_admin = CAP_NET_ADMIN;
	स्थिर cap_value_t cap_sys_admin = CAP_SYS_ADMIN;
	काष्ठा libcap *cap;
	पूर्णांक ret = -1;

	caps = cap_get_proc();
	अगर (!caps) अणु
		लिखो_त्रुटि("cap_get_proc");
		वापस -1;
	पूर्ण
	cap = (काष्ठा libcap *)caps;
	अगर (cap_set_flag(caps, CAP_EFFECTIVE, 1, &cap_sys_admin, CAP_CLEAR)) अणु
		लिखो_त्रुटि("cap_set_flag clear admin");
		जाओ out;
	पूर्ण
	अगर (cap_set_flag(caps, CAP_EFFECTIVE, 1, &cap_net_admin,
				admin ? CAP_SET : CAP_CLEAR)) अणु
		लिखो_त्रुटि("cap_set_flag set_or_clear net");
		जाओ out;
	पूर्ण
	/* libcap is likely old and simply ignores CAP_BPF and CAP_PERFMON,
	 * so update effective bits manually
	 */
	अगर (admin) अणु
		cap->data[1].effective |= 1 << (38 /* CAP_PERFMON */ - 32);
		cap->data[1].effective |= 1 << (39 /* CAP_BPF */ - 32);
	पूर्ण अन्यथा अणु
		cap->data[1].effective &= ~(1 << (38 - 32));
		cap->data[1].effective &= ~(1 << (39 - 32));
	पूर्ण
	अगर (cap_set_proc(caps)) अणु
		लिखो_त्रुटि("cap_set_proc");
		जाओ out;
	पूर्ण
	ret = 0;
out:
	अगर (cap_मुक्त(caps))
		लिखो_त्रुटि("cap_free");
	वापस ret;
पूर्ण

अटल पूर्णांक करो_prog_test_run(पूर्णांक fd_prog, bool unpriv, uपूर्णांक32_t expected_val,
			    व्योम *data, माप_प्रकार size_data)
अणु
	__u8 पंचांगp[TEST_DATA_LEN << 2];
	__u32 माप_प्रकारmp = माप(पंचांगp);
	uपूर्णांक32_t retval;
	पूर्णांक err, saved_त्रुटि_सं;

	अगर (unpriv)
		set_admin(true);
	err = bpf_prog_test_run(fd_prog, 1, data, size_data,
				पंचांगp, &माप_प्रकारmp, &retval, शून्य);
	saved_त्रुटि_सं = त्रुटि_सं;

	अगर (unpriv)
		set_admin(false);

	अगर (err) अणु
		चयन (saved_त्रुटि_सं) अणु
		हाल 524/*ENOTSUPP*/:
			म_लिखो("Did not run the program (not supported) ");
			वापस 0;
		हाल EPERM:
			अगर (unpriv) अणु
				म_लिखो("Did not run the program (no permission) ");
				वापस 0;
			पूर्ण
			/* fallthrough; */
		शेष:
			म_लिखो("FAIL: Unexpected bpf_prog_test_run error (%s) ",
				म_त्रुटि(saved_त्रुटि_सं));
			वापस err;
		पूर्ण
	पूर्ण

	अगर (retval != expected_val &&
	    expected_val != POINTER_VALUE) अणु
		म_लिखो("FAIL retval %d != %d ", retval, expected_val);
		वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

/* Returns true अगर every part of exp (tab-separated) appears in log, in order.
 *
 * If exp is an empty string, वापसs true.
 */
अटल bool cmp_str_seq(स्थिर अक्षर *log, स्थिर अक्षर *exp)
अणु
	अक्षर needle[200];
	स्थिर अक्षर *p, *q;
	पूर्णांक len;

	करो अणु
		अगर (!म_माप(exp))
			अवरोध;
		p = म_अक्षर(exp, '\t');
		अगर (!p)
			p = exp + म_माप(exp);

		len = p - exp;
		अगर (len >= माप(needle) || !len) अणु
			म_लिखो("FAIL\nTestcase bug\n");
			वापस false;
		पूर्ण
		म_नकलन(needle, exp, len);
		needle[len] = 0;
		q = म_माला(log, needle);
		अगर (!q) अणु
			म_लिखो("FAIL\nUnexpected verifier log!\n"
			       "EXP: %s\nRES:\n", needle);
			वापस false;
		पूर्ण
		log = q + len;
		exp = p + 1;
	पूर्ण जबतक (*p);
	वापस true;
पूर्ण

अटल व्योम करो_test_single(काष्ठा bpf_test *test, bool unpriv,
			   पूर्णांक *passes, पूर्णांक *errors)
अणु
	पूर्णांक fd_prog, expected_ret, alignment_prevented_execution;
	पूर्णांक prog_len, prog_type = test->prog_type;
	काष्ठा bpf_insn *prog = test->insns;
	काष्ठा bpf_load_program_attr attr;
	पूर्णांक run_errs, run_successes;
	पूर्णांक map_fds[MAX_NR_MAPS];
	स्थिर अक्षर *expected_err;
	पूर्णांक saved_त्रुटि_सं;
	पूर्णांक fixup_skips;
	__u32 pflags;
	पूर्णांक i, err;

	क्रम (i = 0; i < MAX_NR_MAPS; i++)
		map_fds[i] = -1;

	अगर (!prog_type)
		prog_type = BPF_PROG_TYPE_SOCKET_FILTER;
	fixup_skips = skips;
	करो_test_fixup(test, prog_type, prog, map_fds);
	अगर (test->fill_insns) अणु
		prog = test->fill_insns;
		prog_len = test->prog_len;
	पूर्ण अन्यथा अणु
		prog_len = probe_filter_length(prog);
	पूर्ण
	/* If there were some map skips during fixup due to missing bpf
	 * features, skip this test.
	 */
	अगर (fixup_skips != skips)
		वापस;

	pflags = BPF_F_TEST_RND_HI32;
	अगर (test->flags & F_LOAD_WITH_STRICT_ALIGNMENT)
		pflags |= BPF_F_STRICT_ALIGNMENT;
	अगर (test->flags & F_NEEDS_EFFICIENT_UNALIGNED_ACCESS)
		pflags |= BPF_F_ANY_ALIGNMENT;
	अगर (test->flags & ~3)
		pflags |= test->flags;

	expected_ret = unpriv && test->result_unpriv != UNDEF ?
		       test->result_unpriv : test->result;
	expected_err = unpriv && test->errstr_unpriv ?
		       test->errstr_unpriv : test->errstr;
	स_रखो(&attr, 0, माप(attr));
	attr.prog_type = prog_type;
	attr.expected_attach_type = test->expected_attach_type;
	attr.insns = prog;
	attr.insns_cnt = prog_len;
	attr.license = "GPL";
	अगर (verbose)
		attr.log_level = 1;
	अन्यथा अगर (expected_ret == VERBOSE_ACCEPT)
		attr.log_level = 2;
	अन्यथा
		attr.log_level = 4;
	attr.prog_flags = pflags;

	अगर (prog_type == BPF_PROG_TYPE_TRACING && test->kfunc) अणु
		attr.attach_btf_id = libbpf_find_vmlinux_btf_id(test->kfunc,
						attr.expected_attach_type);
		अगर (attr.attach_btf_id < 0) अणु
			म_लिखो("FAIL\nFailed to find BTF ID for '%s'!\n",
				test->kfunc);
			(*errors)++;
			वापस;
		पूर्ण
	पूर्ण

	fd_prog = bpf_load_program_xattr(&attr, bpf_vlog, माप(bpf_vlog));
	saved_त्रुटि_सं = त्रुटि_सं;

	/* BPF_PROG_TYPE_TRACING requires more setup and
	 * bpf_probe_prog_type won't give correct answer
	 */
	अगर (fd_prog < 0 && prog_type != BPF_PROG_TYPE_TRACING &&
	    !bpf_probe_prog_type(prog_type, 0)) अणु
		म_लिखो("SKIP (unsupported program type %d)\n", prog_type);
		skips++;
		जाओ बंद_fds;
	पूर्ण

	alignment_prevented_execution = 0;

	अगर (expected_ret == ACCEPT || expected_ret == VERBOSE_ACCEPT) अणु
		अगर (fd_prog < 0) अणु
			म_लिखो("FAIL\nFailed to load prog '%s'!\n",
			       म_त्रुटि(saved_त्रुटि_सं));
			जाओ fail_log;
		पूर्ण
#अगर_अघोषित CONFIG_HAVE_EFFICIENT_UNALIGNED_ACCESS
		अगर (fd_prog >= 0 &&
		    (test->flags & F_NEEDS_EFFICIENT_UNALIGNED_ACCESS))
			alignment_prevented_execution = 1;
#पूर्ण_अगर
		अगर (expected_ret == VERBOSE_ACCEPT && !cmp_str_seq(bpf_vlog, expected_err)) अणु
			जाओ fail_log;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (fd_prog >= 0) अणु
			म_लिखो("FAIL\nUnexpected success to load!\n");
			जाओ fail_log;
		पूर्ण
		अगर (!expected_err || !cmp_str_seq(bpf_vlog, expected_err)) अणु
			म_लिखो("FAIL\nUnexpected error message!\n\tEXP: %s\n\tRES: %s\n",
			      expected_err, bpf_vlog);
			जाओ fail_log;
		पूर्ण
	पूर्ण

	अगर (!unpriv && test->insn_processed) अणु
		uपूर्णांक32_t insn_processed;
		अक्षर *proc;

		proc = म_माला(bpf_vlog, "processed ");
		insn_processed = म_से_प(proc + 10);
		अगर (test->insn_processed != insn_processed) अणु
			म_लिखो("FAIL\nUnexpected insn_processed %u vs %u\n",
			       insn_processed, test->insn_processed);
			जाओ fail_log;
		पूर्ण
	पूर्ण

	अगर (verbose)
		म_लिखो(", verifier log:\n%s", bpf_vlog);

	run_errs = 0;
	run_successes = 0;
	अगर (!alignment_prevented_execution && fd_prog >= 0 && test->runs >= 0) अणु
		uपूर्णांक32_t expected_val;
		पूर्णांक i;

		अगर (!test->runs)
			test->runs = 1;

		क्रम (i = 0; i < test->runs; i++) अणु
			अगर (unpriv && test->retvals[i].retval_unpriv)
				expected_val = test->retvals[i].retval_unpriv;
			अन्यथा
				expected_val = test->retvals[i].retval;

			err = करो_prog_test_run(fd_prog, unpriv, expected_val,
					       test->retvals[i].data,
					       माप(test->retvals[i].data));
			अगर (err) अणु
				म_लिखो("(run %d/%d) ", i + 1, test->runs);
				run_errs++;
			पूर्ण अन्यथा अणु
				run_successes++;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (!run_errs) अणु
		(*passes)++;
		अगर (run_successes > 1)
			म_लिखो("%d cases ", run_successes);
		म_लिखो("OK");
		अगर (alignment_prevented_execution)
			म_लिखो(" (NOTE: not executed due to unknown alignment)");
		म_लिखो("\n");
	पूर्ण अन्यथा अणु
		म_लिखो("\n");
		जाओ fail_log;
	पूर्ण
बंद_fds:
	अगर (test->fill_insns)
		मुक्त(test->fill_insns);
	बंद(fd_prog);
	क्रम (i = 0; i < MAX_NR_MAPS; i++)
		बंद(map_fds[i]);
	sched_yield();
	वापस;
fail_log:
	(*errors)++;
	म_लिखो("%s", bpf_vlog);
	जाओ बंद_fds;
पूर्ण

अटल bool is_admin(व्योम)
अणु
	cap_flag_value_t net_priv = CAP_CLEAR;
	bool perfmon_priv = false;
	bool bpf_priv = false;
	काष्ठा libcap *cap;
	cap_t caps;

#अगर_घोषित CAP_IS_SUPPORTED
	अगर (!CAP_IS_SUPPORTED(CAP_SETFCAP)) अणु
		लिखो_त्रुटि("cap_get_flag");
		वापस false;
	पूर्ण
#पूर्ण_अगर
	caps = cap_get_proc();
	अगर (!caps) अणु
		लिखो_त्रुटि("cap_get_proc");
		वापस false;
	पूर्ण
	cap = (काष्ठा libcap *)caps;
	bpf_priv = cap->data[1].effective & (1 << (39/* CAP_BPF */ - 32));
	perfmon_priv = cap->data[1].effective & (1 << (38/* CAP_PERFMON */ - 32));
	अगर (cap_get_flag(caps, CAP_NET_ADMIN, CAP_EFFECTIVE, &net_priv))
		लिखो_त्रुटि("cap_get_flag NET");
	अगर (cap_मुक्त(caps))
		लिखो_त्रुटि("cap_free");
	वापस bpf_priv && perfmon_priv && net_priv == CAP_SET;
पूर्ण

अटल व्योम get_unpriv_disabled()
अणु
	अक्षर buf[2];
	खाता *fd;

	fd = ख_खोलो("/proc/sys/"UNPRIV_SYSCTL, "r");
	अगर (!fd) अणु
		लिखो_त्रुटि("fopen /proc/sys/"UNPRIV_SYSCTL);
		unpriv_disabled = true;
		वापस;
	पूर्ण
	अगर (ख_माला_लो(buf, 2, fd) == buf && म_से_प(buf))
		unpriv_disabled = true;
	ख_बंद(fd);
पूर्ण

अटल bool test_as_unpriv(काष्ठा bpf_test *test)
अणु
#अगर_अघोषित CONFIG_HAVE_EFFICIENT_UNALIGNED_ACCESS
	/* Some architectures have strict alignment requirements. In
	 * that हाल, the BPF verअगरier detects अगर a program has
	 * unaligned accesses and rejects them. A user can pass
	 * BPF_F_ANY_ALIGNMENT to a program to override this
	 * check. That, however, will only work when a privileged user
	 * loads a program. An unprivileged user loading a program
	 * with this flag will be rejected prior entering the
	 * verअगरier.
	 */
	अगर (test->flags & F_NEEDS_EFFICIENT_UNALIGNED_ACCESS)
		वापस false;
#पूर्ण_अगर
	वापस !test->prog_type ||
	       test->prog_type == BPF_PROG_TYPE_SOCKET_FILTER ||
	       test->prog_type == BPF_PROG_TYPE_CGROUP_SKB;
पूर्ण

अटल पूर्णांक करो_test(bool unpriv, अचिन्हित पूर्णांक from, अचिन्हित पूर्णांक to)
अणु
	पूर्णांक i, passes = 0, errors = 0;

	क्रम (i = from; i < to; i++) अणु
		काष्ठा bpf_test *test = &tests[i];

		/* Program types that are not supported by non-root we
		 * skip right away.
		 */
		अगर (test_as_unpriv(test) && unpriv_disabled) अणु
			म_लिखो("#%d/u %s SKIP\n", i, test->descr);
			skips++;
		पूर्ण अन्यथा अगर (test_as_unpriv(test)) अणु
			अगर (!unpriv)
				set_admin(false);
			म_लिखो("#%d/u %s ", i, test->descr);
			करो_test_single(test, true, &passes, &errors);
			अगर (!unpriv)
				set_admin(true);
		पूर्ण

		अगर (unpriv) अणु
			म_लिखो("#%d/p %s SKIP\n", i, test->descr);
			skips++;
		पूर्ण अन्यथा अणु
			म_लिखो("#%d/p %s ", i, test->descr);
			करो_test_single(test, false, &passes, &errors);
		पूर्ण
	पूर्ण

	म_लिखो("Summary: %d PASSED, %d SKIPPED, %d FAILED\n", passes,
	       skips, errors);
	वापस errors ? निकास_त्रुटि : निकास_सफल;
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर **argv)
अणु
	अचिन्हित पूर्णांक from = 0, to = ARRAY_SIZE(tests);
	bool unpriv = !is_admin();
	पूर्णांक arg = 1;

	अगर (argc > 1 && म_भेद(argv[1], "-v") == 0) अणु
		arg++;
		verbose = true;
		argc--;
	पूर्ण

	अगर (argc == 3) अणु
		अचिन्हित पूर्णांक l = म_से_प(argv[arg]);
		अचिन्हित पूर्णांक u = म_से_प(argv[arg + 1]);

		अगर (l < to && u < to) अणु
			from = l;
			to   = u + 1;
		पूर्ण
	पूर्ण अन्यथा अगर (argc == 2) अणु
		अचिन्हित पूर्णांक t = म_से_प(argv[arg]);

		अगर (t < to) अणु
			from = t;
			to   = t + 1;
		पूर्ण
	पूर्ण

	get_unpriv_disabled();
	अगर (unpriv && unpriv_disabled) अणु
		म_लिखो("Cannot run as unprivileged user with sysctl %s.\n",
		       UNPRIV_SYSCTL);
		वापस निकास_त्रुटि;
	पूर्ण

	bpf_semi_अक्रम_init();
	वापस करो_test(unpriv, from, to);
पूर्ण
