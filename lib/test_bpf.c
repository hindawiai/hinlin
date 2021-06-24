<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Testsuite क्रम BPF पूर्णांकerpreter and BPF JIT compiler
 *
 * Copyright (c) 2011-2014 PLUMgrid, http://plumgrid.com
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/filter.h>
#समावेश <linux/bpf.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/sched.h>

/* General test specअगरic settings */
#घोषणा MAX_SUBTESTS	3
#घोषणा MAX_TESTRUNS	1000
#घोषणा MAX_DATA	128
#घोषणा MAX_INSNS	512
#घोषणा MAX_K		0xffffFFFF

/* Few स्थिरants used to init test 'skb' */
#घोषणा SKB_TYPE	3
#घोषणा SKB_MARK	0x1234aaaa
#घोषणा SKB_HASH	0x1234aaab
#घोषणा SKB_QUEUE_MAP	123
#घोषणा SKB_VLAN_TCI	0xffff
#घोषणा SKB_VLAN_PRESENT	1
#घोषणा SKB_DEV_IFINDEX	577
#घोषणा SKB_DEV_TYPE	588

/* Redefine REGs to make tests less verbose */
#घोषणा R0		BPF_REG_0
#घोषणा R1		BPF_REG_1
#घोषणा R2		BPF_REG_2
#घोषणा R3		BPF_REG_3
#घोषणा R4		BPF_REG_4
#घोषणा R5		BPF_REG_5
#घोषणा R6		BPF_REG_6
#घोषणा R7		BPF_REG_7
#घोषणा R8		BPF_REG_8
#घोषणा R9		BPF_REG_9
#घोषणा R10		BPF_REG_10

/* Flags that can be passed to test हालs */
#घोषणा FLAG_NO_DATA		BIT(0)
#घोषणा FLAG_EXPECTED_FAIL	BIT(1)
#घोषणा FLAG_SKB_FRAG		BIT(2)

क्रमागत अणु
	CLASSIC  = BIT(6),	/* Old BPF inकाष्ठाions only. */
	INTERNAL = BIT(7),	/* Extended inकाष्ठाion set.  */
पूर्ण;

#घोषणा TEST_TYPE_MASK		(CLASSIC | INTERNAL)

काष्ठा bpf_test अणु
	स्थिर अक्षर *descr;
	जोड़ अणु
		काष्ठा sock_filter insns[MAX_INSNS];
		काष्ठा bpf_insn insns_पूर्णांक[MAX_INSNS];
		काष्ठा अणु
			व्योम *insns;
			अचिन्हित पूर्णांक len;
		पूर्ण ptr;
	पूर्ण u;
	__u8 aux;
	__u8 data[MAX_DATA];
	काष्ठा अणु
		पूर्णांक data_size;
		__u32 result;
	पूर्ण test[MAX_SUBTESTS];
	पूर्णांक (*fill_helper)(काष्ठा bpf_test *self);
	पूर्णांक expected_errcode; /* used when FLAG_EXPECTED_FAIL is set in the aux */
	__u8 frag_data[MAX_DATA];
	पूर्णांक stack_depth; /* क्रम eBPF only, since tests करोn't call verअगरier */
पूर्ण;

/* Large test हालs need separate allocation and fill handler. */

अटल पूर्णांक bpf_fill_maxinsns1(काष्ठा bpf_test *self)
अणु
	अचिन्हित पूर्णांक len = BPF_MAXINSNS;
	काष्ठा sock_filter *insn;
	__u32 k = ~0;
	पूर्णांक i;

	insn = kदो_स्मृति_array(len, माप(*insn), GFP_KERNEL);
	अगर (!insn)
		वापस -ENOMEM;

	क्रम (i = 0; i < len; i++, k--)
		insn[i] = __BPF_STMT(BPF_RET | BPF_K, k);

	self->u.ptr.insns = insn;
	self->u.ptr.len = len;

	वापस 0;
पूर्ण

अटल पूर्णांक bpf_fill_maxinsns2(काष्ठा bpf_test *self)
अणु
	अचिन्हित पूर्णांक len = BPF_MAXINSNS;
	काष्ठा sock_filter *insn;
	पूर्णांक i;

	insn = kदो_स्मृति_array(len, माप(*insn), GFP_KERNEL);
	अगर (!insn)
		वापस -ENOMEM;

	क्रम (i = 0; i < len; i++)
		insn[i] = __BPF_STMT(BPF_RET | BPF_K, 0xfefefefe);

	self->u.ptr.insns = insn;
	self->u.ptr.len = len;

	वापस 0;
पूर्ण

अटल पूर्णांक bpf_fill_maxinsns3(काष्ठा bpf_test *self)
अणु
	अचिन्हित पूर्णांक len = BPF_MAXINSNS;
	काष्ठा sock_filter *insn;
	काष्ठा rnd_state rnd;
	पूर्णांक i;

	insn = kदो_स्मृति_array(len, माप(*insn), GFP_KERNEL);
	अगर (!insn)
		वापस -ENOMEM;

	pअक्रमom_seed_state(&rnd, 3141592653589793238ULL);

	क्रम (i = 0; i < len - 1; i++) अणु
		__u32 k = pअक्रमom_u32_state(&rnd);

		insn[i] = __BPF_STMT(BPF_ALU | BPF_ADD | BPF_K, k);
	पूर्ण

	insn[len - 1] = __BPF_STMT(BPF_RET | BPF_A, 0);

	self->u.ptr.insns = insn;
	self->u.ptr.len = len;

	वापस 0;
पूर्ण

अटल पूर्णांक bpf_fill_maxinsns4(काष्ठा bpf_test *self)
अणु
	अचिन्हित पूर्णांक len = BPF_MAXINSNS + 1;
	काष्ठा sock_filter *insn;
	पूर्णांक i;

	insn = kदो_स्मृति_array(len, माप(*insn), GFP_KERNEL);
	अगर (!insn)
		वापस -ENOMEM;

	क्रम (i = 0; i < len; i++)
		insn[i] = __BPF_STMT(BPF_RET | BPF_K, 0xfefefefe);

	self->u.ptr.insns = insn;
	self->u.ptr.len = len;

	वापस 0;
पूर्ण

अटल पूर्णांक bpf_fill_maxinsns5(काष्ठा bpf_test *self)
अणु
	अचिन्हित पूर्णांक len = BPF_MAXINSNS;
	काष्ठा sock_filter *insn;
	पूर्णांक i;

	insn = kदो_स्मृति_array(len, माप(*insn), GFP_KERNEL);
	अगर (!insn)
		वापस -ENOMEM;

	insn[0] = __BPF_JUMP(BPF_JMP | BPF_JA, len - 2, 0, 0);

	क्रम (i = 1; i < len - 1; i++)
		insn[i] = __BPF_STMT(BPF_RET | BPF_K, 0xfefefefe);

	insn[len - 1] = __BPF_STMT(BPF_RET | BPF_K, 0xabababab);

	self->u.ptr.insns = insn;
	self->u.ptr.len = len;

	वापस 0;
पूर्ण

अटल पूर्णांक bpf_fill_maxinsns6(काष्ठा bpf_test *self)
अणु
	अचिन्हित पूर्णांक len = BPF_MAXINSNS;
	काष्ठा sock_filter *insn;
	पूर्णांक i;

	insn = kदो_स्मृति_array(len, माप(*insn), GFP_KERNEL);
	अगर (!insn)
		वापस -ENOMEM;

	क्रम (i = 0; i < len - 1; i++)
		insn[i] = __BPF_STMT(BPF_LD | BPF_W | BPF_ABS, SKF_AD_OFF +
				     SKF_AD_VLAN_TAG_PRESENT);

	insn[len - 1] = __BPF_STMT(BPF_RET | BPF_A, 0);

	self->u.ptr.insns = insn;
	self->u.ptr.len = len;

	वापस 0;
पूर्ण

अटल पूर्णांक bpf_fill_maxinsns7(काष्ठा bpf_test *self)
अणु
	अचिन्हित पूर्णांक len = BPF_MAXINSNS;
	काष्ठा sock_filter *insn;
	पूर्णांक i;

	insn = kदो_स्मृति_array(len, माप(*insn), GFP_KERNEL);
	अगर (!insn)
		वापस -ENOMEM;

	क्रम (i = 0; i < len - 4; i++)
		insn[i] = __BPF_STMT(BPF_LD | BPF_W | BPF_ABS, SKF_AD_OFF +
				     SKF_AD_CPU);

	insn[len - 4] = __BPF_STMT(BPF_MISC | BPF_TAX, 0);
	insn[len - 3] = __BPF_STMT(BPF_LD | BPF_W | BPF_ABS, SKF_AD_OFF +
				   SKF_AD_CPU);
	insn[len - 2] = __BPF_STMT(BPF_ALU | BPF_SUB | BPF_X, 0);
	insn[len - 1] = __BPF_STMT(BPF_RET | BPF_A, 0);

	self->u.ptr.insns = insn;
	self->u.ptr.len = len;

	वापस 0;
पूर्ण

अटल पूर्णांक bpf_fill_maxinsns8(काष्ठा bpf_test *self)
अणु
	अचिन्हित पूर्णांक len = BPF_MAXINSNS;
	काष्ठा sock_filter *insn;
	पूर्णांक i, jmp_off = len - 3;

	insn = kदो_स्मृति_array(len, माप(*insn), GFP_KERNEL);
	अगर (!insn)
		वापस -ENOMEM;

	insn[0] = __BPF_STMT(BPF_LD | BPF_IMM, 0xffffffff);

	क्रम (i = 1; i < len - 1; i++)
		insn[i] = __BPF_JUMP(BPF_JMP | BPF_JGT, 0xffffffff, jmp_off--, 0);

	insn[len - 1] = __BPF_STMT(BPF_RET | BPF_A, 0);

	self->u.ptr.insns = insn;
	self->u.ptr.len = len;

	वापस 0;
पूर्ण

अटल पूर्णांक bpf_fill_maxinsns9(काष्ठा bpf_test *self)
अणु
	अचिन्हित पूर्णांक len = BPF_MAXINSNS;
	काष्ठा bpf_insn *insn;
	पूर्णांक i;

	insn = kदो_स्मृति_array(len, माप(*insn), GFP_KERNEL);
	अगर (!insn)
		वापस -ENOMEM;

	insn[0] = BPF_JMP_IMM(BPF_JA, 0, 0, len - 2);
	insn[1] = BPF_ALU32_IMM(BPF_MOV, R0, 0xcbababab);
	insn[2] = BPF_EXIT_INSN();

	क्रम (i = 3; i < len - 2; i++)
		insn[i] = BPF_ALU32_IMM(BPF_MOV, R0, 0xfefefefe);

	insn[len - 2] = BPF_EXIT_INSN();
	insn[len - 1] = BPF_JMP_IMM(BPF_JA, 0, 0, -(len - 1));

	self->u.ptr.insns = insn;
	self->u.ptr.len = len;

	वापस 0;
पूर्ण

अटल पूर्णांक bpf_fill_maxinsns10(काष्ठा bpf_test *self)
अणु
	अचिन्हित पूर्णांक len = BPF_MAXINSNS, hlen = len - 2;
	काष्ठा bpf_insn *insn;
	पूर्णांक i;

	insn = kदो_स्मृति_array(len, माप(*insn), GFP_KERNEL);
	अगर (!insn)
		वापस -ENOMEM;

	क्रम (i = 0; i < hlen / 2; i++)
		insn[i] = BPF_JMP_IMM(BPF_JA, 0, 0, hlen - 2 - 2 * i);
	क्रम (i = hlen - 1; i > hlen / 2; i--)
		insn[i] = BPF_JMP_IMM(BPF_JA, 0, 0, hlen - 1 - 2 * i);

	insn[hlen / 2] = BPF_JMP_IMM(BPF_JA, 0, 0, hlen / 2 - 1);
	insn[hlen]     = BPF_ALU32_IMM(BPF_MOV, R0, 0xabababac);
	insn[hlen + 1] = BPF_EXIT_INSN();

	self->u.ptr.insns = insn;
	self->u.ptr.len = len;

	वापस 0;
पूर्ण

अटल पूर्णांक __bpf_fill_ja(काष्ठा bpf_test *self, अचिन्हित पूर्णांक len,
			 अचिन्हित पूर्णांक plen)
अणु
	काष्ठा sock_filter *insn;
	अचिन्हित पूर्णांक rlen;
	पूर्णांक i, j;

	insn = kदो_स्मृति_array(len, माप(*insn), GFP_KERNEL);
	अगर (!insn)
		वापस -ENOMEM;

	rlen = (len % plen) - 1;

	क्रम (i = 0; i + plen < len; i += plen)
		क्रम (j = 0; j < plen; j++)
			insn[i + j] = __BPF_JUMP(BPF_JMP | BPF_JA,
						 plen - 1 - j, 0, 0);
	क्रम (j = 0; j < rlen; j++)
		insn[i + j] = __BPF_JUMP(BPF_JMP | BPF_JA, rlen - 1 - j,
					 0, 0);

	insn[len - 1] = __BPF_STMT(BPF_RET | BPF_K, 0xababcbac);

	self->u.ptr.insns = insn;
	self->u.ptr.len = len;

	वापस 0;
पूर्ण

अटल पूर्णांक bpf_fill_maxinsns11(काष्ठा bpf_test *self)
अणु
	/* Hits 70 passes on x86_64 and triggers NOPs padding. */
	वापस __bpf_fill_ja(self, BPF_MAXINSNS, 68);
पूर्ण

अटल पूर्णांक bpf_fill_maxinsns12(काष्ठा bpf_test *self)
अणु
	अचिन्हित पूर्णांक len = BPF_MAXINSNS;
	काष्ठा sock_filter *insn;
	पूर्णांक i = 0;

	insn = kदो_स्मृति_array(len, माप(*insn), GFP_KERNEL);
	अगर (!insn)
		वापस -ENOMEM;

	insn[0] = __BPF_JUMP(BPF_JMP | BPF_JA, len - 2, 0, 0);

	क्रम (i = 1; i < len - 1; i++)
		insn[i] = __BPF_STMT(BPF_LDX | BPF_B | BPF_MSH, 0);

	insn[len - 1] = __BPF_STMT(BPF_RET | BPF_K, 0xabababab);

	self->u.ptr.insns = insn;
	self->u.ptr.len = len;

	वापस 0;
पूर्ण

अटल पूर्णांक bpf_fill_maxinsns13(काष्ठा bpf_test *self)
अणु
	अचिन्हित पूर्णांक len = BPF_MAXINSNS;
	काष्ठा sock_filter *insn;
	पूर्णांक i = 0;

	insn = kदो_स्मृति_array(len, माप(*insn), GFP_KERNEL);
	अगर (!insn)
		वापस -ENOMEM;

	क्रम (i = 0; i < len - 3; i++)
		insn[i] = __BPF_STMT(BPF_LDX | BPF_B | BPF_MSH, 0);

	insn[len - 3] = __BPF_STMT(BPF_LD | BPF_IMM, 0xabababab);
	insn[len - 2] = __BPF_STMT(BPF_ALU | BPF_XOR | BPF_X, 0);
	insn[len - 1] = __BPF_STMT(BPF_RET | BPF_A, 0);

	self->u.ptr.insns = insn;
	self->u.ptr.len = len;

	वापस 0;
पूर्ण

अटल पूर्णांक bpf_fill_ja(काष्ठा bpf_test *self)
अणु
	/* Hits exactly 11 passes on x86_64 JIT. */
	वापस __bpf_fill_ja(self, 12, 9);
पूर्ण

अटल पूर्णांक bpf_fill_ld_असल_get_processor_id(काष्ठा bpf_test *self)
अणु
	अचिन्हित पूर्णांक len = BPF_MAXINSNS;
	काष्ठा sock_filter *insn;
	पूर्णांक i;

	insn = kदो_स्मृति_array(len, माप(*insn), GFP_KERNEL);
	अगर (!insn)
		वापस -ENOMEM;

	क्रम (i = 0; i < len - 1; i += 2) अणु
		insn[i] = __BPF_STMT(BPF_LD | BPF_B | BPF_ABS, 0);
		insn[i + 1] = __BPF_STMT(BPF_LD | BPF_W | BPF_ABS,
					 SKF_AD_OFF + SKF_AD_CPU);
	पूर्ण

	insn[len - 1] = __BPF_STMT(BPF_RET | BPF_K, 0xbee);

	self->u.ptr.insns = insn;
	self->u.ptr.len = len;

	वापस 0;
पूर्ण

अटल पूर्णांक __bpf_fill_stxdw(काष्ठा bpf_test *self, पूर्णांक size)
अणु
	अचिन्हित पूर्णांक len = BPF_MAXINSNS;
	काष्ठा bpf_insn *insn;
	पूर्णांक i;

	insn = kदो_स्मृति_array(len, माप(*insn), GFP_KERNEL);
	अगर (!insn)
		वापस -ENOMEM;

	insn[0] = BPF_ALU32_IMM(BPF_MOV, R0, 1);
	insn[1] = BPF_ST_MEM(size, R10, -40, 42);

	क्रम (i = 2; i < len - 2; i++)
		insn[i] = BPF_STX_XADD(size, R10, R0, -40);

	insn[len - 2] = BPF_LDX_MEM(size, R0, R10, -40);
	insn[len - 1] = BPF_EXIT_INSN();

	self->u.ptr.insns = insn;
	self->u.ptr.len = len;
	self->stack_depth = 40;

	वापस 0;
पूर्ण

अटल पूर्णांक bpf_fill_stxw(काष्ठा bpf_test *self)
अणु
	वापस __bpf_fill_stxdw(self, BPF_W);
पूर्ण

अटल पूर्णांक bpf_fill_stxdw(काष्ठा bpf_test *self)
अणु
	वापस __bpf_fill_stxdw(self, BPF_DW);
पूर्ण

अटल काष्ठा bpf_test tests[] = अणु
	अणु
		"TAX",
		.u.insns = अणु
			BPF_STMT(BPF_LD | BPF_IMM, 1),
			BPF_STMT(BPF_MISC | BPF_TAX, 0),
			BPF_STMT(BPF_LD | BPF_IMM, 2),
			BPF_STMT(BPF_ALU | BPF_ADD | BPF_X, 0),
			BPF_STMT(BPF_ALU | BPF_NEG, 0), /* A == -3 */
			BPF_STMT(BPF_MISC | BPF_TAX, 0),
			BPF_STMT(BPF_LD | BPF_LEN, 0),
			BPF_STMT(BPF_ALU | BPF_ADD | BPF_X, 0),
			BPF_STMT(BPF_MISC | BPF_TAX, 0), /* X == len - 3 */
			BPF_STMT(BPF_LD | BPF_B | BPF_IND, 1),
			BPF_STMT(BPF_RET | BPF_A, 0)
		पूर्ण,
		CLASSIC,
		अणु 10, 20, 30, 40, 50 पूर्ण,
		अणु अणु 2, 10 पूर्ण, अणु 3, 20 पूर्ण, अणु 4, 30 पूर्ण पूर्ण,
	पूर्ण,
	अणु
		"TXA",
		.u.insns = अणु
			BPF_STMT(BPF_LDX | BPF_LEN, 0),
			BPF_STMT(BPF_MISC | BPF_TXA, 0),
			BPF_STMT(BPF_ALU | BPF_ADD | BPF_X, 0),
			BPF_STMT(BPF_RET | BPF_A, 0) /* A == len * 2 */
		पूर्ण,
		CLASSIC,
		अणु 10, 20, 30, 40, 50 पूर्ण,
		अणु अणु 1, 2 पूर्ण, अणु 3, 6 पूर्ण, अणु 4, 8 पूर्ण पूर्ण,
	पूर्ण,
	अणु
		"ADD_SUB_MUL_K",
		.u.insns = अणु
			BPF_STMT(BPF_LD | BPF_IMM, 1),
			BPF_STMT(BPF_ALU | BPF_ADD | BPF_K, 2),
			BPF_STMT(BPF_LDX | BPF_IMM, 3),
			BPF_STMT(BPF_ALU | BPF_SUB | BPF_X, 0),
			BPF_STMT(BPF_ALU | BPF_ADD | BPF_K, 0xffffffff),
			BPF_STMT(BPF_ALU | BPF_MUL | BPF_K, 3),
			BPF_STMT(BPF_RET | BPF_A, 0)
		पूर्ण,
		CLASSIC | FLAG_NO_DATA,
		अणु पूर्ण,
		अणु अणु 0, 0xfffffffd पूर्ण पूर्ण
	पूर्ण,
	अणु
		"DIV_MOD_KX",
		.u.insns = अणु
			BPF_STMT(BPF_LD | BPF_IMM, 8),
			BPF_STMT(BPF_ALU | BPF_DIV | BPF_K, 2),
			BPF_STMT(BPF_MISC | BPF_TAX, 0),
			BPF_STMT(BPF_LD | BPF_IMM, 0xffffffff),
			BPF_STMT(BPF_ALU | BPF_DIV | BPF_X, 0),
			BPF_STMT(BPF_MISC | BPF_TAX, 0),
			BPF_STMT(BPF_LD | BPF_IMM, 0xffffffff),
			BPF_STMT(BPF_ALU | BPF_DIV | BPF_K, 0x70000000),
			BPF_STMT(BPF_MISC | BPF_TAX, 0),
			BPF_STMT(BPF_LD | BPF_IMM, 0xffffffff),
			BPF_STMT(BPF_ALU | BPF_MOD | BPF_X, 0),
			BPF_STMT(BPF_MISC | BPF_TAX, 0),
			BPF_STMT(BPF_LD | BPF_IMM, 0xffffffff),
			BPF_STMT(BPF_ALU | BPF_MOD | BPF_K, 0x70000000),
			BPF_STMT(BPF_ALU | BPF_ADD | BPF_X, 0),
			BPF_STMT(BPF_RET | BPF_A, 0)
		पूर्ण,
		CLASSIC | FLAG_NO_DATA,
		अणु पूर्ण,
		अणु अणु 0, 0x20000000 पूर्ण पूर्ण
	पूर्ण,
	अणु
		"AND_OR_LSH_K",
		.u.insns = अणु
			BPF_STMT(BPF_LD | BPF_IMM, 0xff),
			BPF_STMT(BPF_ALU | BPF_AND | BPF_K, 0xf0),
			BPF_STMT(BPF_ALU | BPF_LSH | BPF_K, 27),
			BPF_STMT(BPF_MISC | BPF_TAX, 0),
			BPF_STMT(BPF_LD | BPF_IMM, 0xf),
			BPF_STMT(BPF_ALU | BPF_OR | BPF_K, 0xf0),
			BPF_STMT(BPF_ALU | BPF_ADD | BPF_X, 0),
			BPF_STMT(BPF_RET | BPF_A, 0)
		पूर्ण,
		CLASSIC | FLAG_NO_DATA,
		अणु पूर्ण,
		अणु अणु 0, 0x800000ff पूर्ण, अणु 1, 0x800000ff पूर्ण पूर्ण,
	पूर्ण,
	अणु
		"LD_IMM_0",
		.u.insns = अणु
			BPF_STMT(BPF_LD | BPF_IMM, 0), /* ld #0 */
			BPF_JUMP(BPF_JMP | BPF_JEQ | BPF_K, 0, 1, 0),
			BPF_STMT(BPF_RET | BPF_K, 0),
			BPF_STMT(BPF_RET | BPF_K, 1),
		पूर्ण,
		CLASSIC,
		अणु पूर्ण,
		अणु अणु 1, 1 पूर्ण पूर्ण,
	पूर्ण,
	अणु
		"LD_IND",
		.u.insns = अणु
			BPF_STMT(BPF_LDX | BPF_LEN, 0),
			BPF_STMT(BPF_LD | BPF_H | BPF_IND, MAX_K),
			BPF_STMT(BPF_RET | BPF_K, 1)
		पूर्ण,
		CLASSIC,
		अणु पूर्ण,
		अणु अणु 1, 0 पूर्ण, अणु 10, 0 पूर्ण, अणु 60, 0 पूर्ण पूर्ण,
	पूर्ण,
	अणु
		"LD_ABS",
		.u.insns = अणु
			BPF_STMT(BPF_LD | BPF_W | BPF_ABS, 1000),
			BPF_STMT(BPF_RET | BPF_K, 1)
		पूर्ण,
		CLASSIC,
		अणु पूर्ण,
		अणु अणु 1, 0 पूर्ण, अणु 10, 0 पूर्ण, अणु 60, 0 पूर्ण पूर्ण,
	पूर्ण,
	अणु
		"LD_ABS_LL",
		.u.insns = अणु
			BPF_STMT(BPF_LD | BPF_B | BPF_ABS, SKF_LL_OFF),
			BPF_STMT(BPF_MISC | BPF_TAX, 0),
			BPF_STMT(BPF_LD | BPF_B | BPF_ABS, SKF_LL_OFF + 1),
			BPF_STMT(BPF_ALU | BPF_ADD | BPF_X, 0),
			BPF_STMT(BPF_RET | BPF_A, 0)
		पूर्ण,
		CLASSIC,
		अणु 1, 2, 3 पूर्ण,
		अणु अणु 1, 0 पूर्ण, अणु 2, 3 पूर्ण पूर्ण,
	पूर्ण,
	अणु
		"LD_IND_LL",
		.u.insns = अणु
			BPF_STMT(BPF_LD | BPF_IMM, SKF_LL_OFF - 1),
			BPF_STMT(BPF_LDX | BPF_LEN, 0),
			BPF_STMT(BPF_ALU | BPF_ADD | BPF_X, 0),
			BPF_STMT(BPF_MISC | BPF_TAX, 0),
			BPF_STMT(BPF_LD | BPF_B | BPF_IND, 0),
			BPF_STMT(BPF_RET | BPF_A, 0)
		पूर्ण,
		CLASSIC,
		अणु 1, 2, 3, 0xff पूर्ण,
		अणु अणु 1, 1 पूर्ण, अणु 3, 3 पूर्ण, अणु 4, 0xff पूर्ण पूर्ण,
	पूर्ण,
	अणु
		"LD_ABS_NET",
		.u.insns = अणु
			BPF_STMT(BPF_LD | BPF_B | BPF_ABS, SKF_NET_OFF),
			BPF_STMT(BPF_MISC | BPF_TAX, 0),
			BPF_STMT(BPF_LD | BPF_B | BPF_ABS, SKF_NET_OFF + 1),
			BPF_STMT(BPF_ALU | BPF_ADD | BPF_X, 0),
			BPF_STMT(BPF_RET | BPF_A, 0)
		पूर्ण,
		CLASSIC,
		अणु 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 3 पूर्ण,
		अणु अणु 15, 0 पूर्ण, अणु 16, 3 पूर्ण पूर्ण,
	पूर्ण,
	अणु
		"LD_IND_NET",
		.u.insns = अणु
			BPF_STMT(BPF_LD | BPF_IMM, SKF_NET_OFF - 15),
			BPF_STMT(BPF_LDX | BPF_LEN, 0),
			BPF_STMT(BPF_ALU | BPF_ADD | BPF_X, 0),
			BPF_STMT(BPF_MISC | BPF_TAX, 0),
			BPF_STMT(BPF_LD | BPF_B | BPF_IND, 0),
			BPF_STMT(BPF_RET | BPF_A, 0)
		पूर्ण,
		CLASSIC,
		अणु 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 3 पूर्ण,
		अणु अणु 14, 0 पूर्ण, अणु 15, 1 पूर्ण, अणु 17, 3 पूर्ण पूर्ण,
	पूर्ण,
	अणु
		"LD_PKTTYPE",
		.u.insns = अणु
			BPF_STMT(BPF_LD | BPF_W | BPF_ABS,
				 SKF_AD_OFF + SKF_AD_PKTTYPE),
			BPF_JUMP(BPF_JMP | BPF_JEQ | BPF_K, SKB_TYPE, 1, 0),
			BPF_STMT(BPF_RET | BPF_K, 1),
			BPF_STMT(BPF_LD | BPF_W | BPF_ABS,
				 SKF_AD_OFF + SKF_AD_PKTTYPE),
			BPF_JUMP(BPF_JMP | BPF_JEQ | BPF_K, SKB_TYPE, 1, 0),
			BPF_STMT(BPF_RET | BPF_K, 1),
			BPF_STMT(BPF_LD | BPF_W | BPF_ABS,
				 SKF_AD_OFF + SKF_AD_PKTTYPE),
			BPF_JUMP(BPF_JMP | BPF_JEQ | BPF_K, SKB_TYPE, 1, 0),
			BPF_STMT(BPF_RET | BPF_K, 1),
			BPF_STMT(BPF_RET | BPF_A, 0)
		पूर्ण,
		CLASSIC,
		अणु पूर्ण,
		अणु अणु 1, 3 पूर्ण, अणु 10, 3 पूर्ण पूर्ण,
	पूर्ण,
	अणु
		"LD_MARK",
		.u.insns = अणु
			BPF_STMT(BPF_LD | BPF_W | BPF_ABS,
				 SKF_AD_OFF + SKF_AD_MARK),
			BPF_STMT(BPF_RET | BPF_A, 0)
		पूर्ण,
		CLASSIC,
		अणु पूर्ण,
		अणु अणु 1, SKB_MARKपूर्ण, अणु 10, SKB_MARKपूर्ण पूर्ण,
	पूर्ण,
	अणु
		"LD_RXHASH",
		.u.insns = अणु
			BPF_STMT(BPF_LD | BPF_W | BPF_ABS,
				 SKF_AD_OFF + SKF_AD_RXHASH),
			BPF_STMT(BPF_RET | BPF_A, 0)
		पूर्ण,
		CLASSIC,
		अणु पूर्ण,
		अणु अणु 1, SKB_HASHपूर्ण, अणु 10, SKB_HASHपूर्ण पूर्ण,
	पूर्ण,
	अणु
		"LD_QUEUE",
		.u.insns = अणु
			BPF_STMT(BPF_LD | BPF_W | BPF_ABS,
				 SKF_AD_OFF + SKF_AD_QUEUE),
			BPF_STMT(BPF_RET | BPF_A, 0)
		पूर्ण,
		CLASSIC,
		अणु पूर्ण,
		अणु अणु 1, SKB_QUEUE_MAP पूर्ण, अणु 10, SKB_QUEUE_MAP पूर्ण पूर्ण,
	पूर्ण,
	अणु
		"LD_PROTOCOL",
		.u.insns = अणु
			BPF_STMT(BPF_LD | BPF_B | BPF_ABS, 1),
			BPF_JUMP(BPF_JMP | BPF_JEQ | BPF_K, 20, 1, 0),
			BPF_STMT(BPF_RET | BPF_K, 0),
			BPF_STMT(BPF_LD | BPF_W | BPF_ABS,
				 SKF_AD_OFF + SKF_AD_PROTOCOL),
			BPF_STMT(BPF_MISC | BPF_TAX, 0),
			BPF_STMT(BPF_LD | BPF_B | BPF_ABS, 2),
			BPF_JUMP(BPF_JMP | BPF_JEQ | BPF_K, 30, 1, 0),
			BPF_STMT(BPF_RET | BPF_K, 0),
			BPF_STMT(BPF_MISC | BPF_TXA, 0),
			BPF_STMT(BPF_RET | BPF_A, 0)
		पूर्ण,
		CLASSIC,
		अणु 10, 20, 30 पूर्ण,
		अणु अणु 10, ETH_P_IP पूर्ण, अणु 100, ETH_P_IP पूर्ण पूर्ण,
	पूर्ण,
	अणु
		"LD_VLAN_TAG",
		.u.insns = अणु
			BPF_STMT(BPF_LD | BPF_W | BPF_ABS,
				 SKF_AD_OFF + SKF_AD_VLAN_TAG),
			BPF_STMT(BPF_RET | BPF_A, 0)
		पूर्ण,
		CLASSIC,
		अणु पूर्ण,
		अणु
			अणु 1, SKB_VLAN_TCI पूर्ण,
			अणु 10, SKB_VLAN_TCI पूर्ण
		पूर्ण,
	पूर्ण,
	अणु
		"LD_VLAN_TAG_PRESENT",
		.u.insns = अणु
			BPF_STMT(BPF_LD | BPF_W | BPF_ABS,
				 SKF_AD_OFF + SKF_AD_VLAN_TAG_PRESENT),
			BPF_STMT(BPF_RET | BPF_A, 0)
		पूर्ण,
		CLASSIC,
		अणु पूर्ण,
		अणु
			अणु 1, SKB_VLAN_PRESENT पूर्ण,
			अणु 10, SKB_VLAN_PRESENT पूर्ण
		पूर्ण,
	पूर्ण,
	अणु
		"LD_IFINDEX",
		.u.insns = अणु
			BPF_STMT(BPF_LD | BPF_W | BPF_ABS,
				 SKF_AD_OFF + SKF_AD_IFINDEX),
			BPF_STMT(BPF_RET | BPF_A, 0)
		पूर्ण,
		CLASSIC,
		अणु पूर्ण,
		अणु अणु 1, SKB_DEV_IFINDEX पूर्ण, अणु 10, SKB_DEV_IFINDEX पूर्ण पूर्ण,
	पूर्ण,
	अणु
		"LD_HATYPE",
		.u.insns = अणु
			BPF_STMT(BPF_LD | BPF_W | BPF_ABS,
				 SKF_AD_OFF + SKF_AD_HATYPE),
			BPF_STMT(BPF_RET | BPF_A, 0)
		पूर्ण,
		CLASSIC,
		अणु पूर्ण,
		अणु अणु 1, SKB_DEV_TYPE पूर्ण, अणु 10, SKB_DEV_TYPE पूर्ण पूर्ण,
	पूर्ण,
	अणु
		"LD_CPU",
		.u.insns = अणु
			BPF_STMT(BPF_LD | BPF_W | BPF_ABS,
				 SKF_AD_OFF + SKF_AD_CPU),
			BPF_STMT(BPF_MISC | BPF_TAX, 0),
			BPF_STMT(BPF_LD | BPF_W | BPF_ABS,
				 SKF_AD_OFF + SKF_AD_CPU),
			BPF_STMT(BPF_ALU | BPF_SUB | BPF_X, 0),
			BPF_STMT(BPF_RET | BPF_A, 0)
		पूर्ण,
		CLASSIC,
		अणु पूर्ण,
		अणु अणु 1, 0 पूर्ण, अणु 10, 0 पूर्ण पूर्ण,
	पूर्ण,
	अणु
		"LD_NLATTR",
		.u.insns = अणु
			BPF_STMT(BPF_LDX | BPF_IMM, 2),
			BPF_STMT(BPF_MISC | BPF_TXA, 0),
			BPF_STMT(BPF_LDX | BPF_IMM, 3),
			BPF_STMT(BPF_LD | BPF_W | BPF_ABS,
				 SKF_AD_OFF + SKF_AD_NLATTR),
			BPF_STMT(BPF_RET | BPF_A, 0)
		पूर्ण,
		CLASSIC,
#अगर_घोषित __BIG_ENDIAN
		अणु 0xff, 0xff, 0, 4, 0, 2, 0, 4, 0, 3 पूर्ण,
#अन्यथा
		अणु 0xff, 0xff, 4, 0, 2, 0, 4, 0, 3, 0 पूर्ण,
#पूर्ण_अगर
		अणु अणु 4, 0 पूर्ण, अणु 20, 6 पूर्ण पूर्ण,
	पूर्ण,
	अणु
		"LD_NLATTR_NEST",
		.u.insns = अणु
			BPF_STMT(BPF_LD | BPF_IMM, 2),
			BPF_STMT(BPF_LDX | BPF_IMM, 3),
			BPF_STMT(BPF_LD | BPF_W | BPF_ABS,
				 SKF_AD_OFF + SKF_AD_NLATTR_NEST),
			BPF_STMT(BPF_LD | BPF_IMM, 2),
			BPF_STMT(BPF_LD | BPF_W | BPF_ABS,
				 SKF_AD_OFF + SKF_AD_NLATTR_NEST),
			BPF_STMT(BPF_LD | BPF_IMM, 2),
			BPF_STMT(BPF_LD | BPF_W | BPF_ABS,
				 SKF_AD_OFF + SKF_AD_NLATTR_NEST),
			BPF_STMT(BPF_LD | BPF_IMM, 2),
			BPF_STMT(BPF_LD | BPF_W | BPF_ABS,
				 SKF_AD_OFF + SKF_AD_NLATTR_NEST),
			BPF_STMT(BPF_LD | BPF_IMM, 2),
			BPF_STMT(BPF_LD | BPF_W | BPF_ABS,
				 SKF_AD_OFF + SKF_AD_NLATTR_NEST),
			BPF_STMT(BPF_LD | BPF_IMM, 2),
			BPF_STMT(BPF_LD | BPF_W | BPF_ABS,
				 SKF_AD_OFF + SKF_AD_NLATTR_NEST),
			BPF_STMT(BPF_LD | BPF_IMM, 2),
			BPF_STMT(BPF_LD | BPF_W | BPF_ABS,
				 SKF_AD_OFF + SKF_AD_NLATTR_NEST),
			BPF_STMT(BPF_LD | BPF_IMM, 2),
			BPF_STMT(BPF_LD | BPF_W | BPF_ABS,
				 SKF_AD_OFF + SKF_AD_NLATTR_NEST),
			BPF_STMT(BPF_RET | BPF_A, 0)
		पूर्ण,
		CLASSIC,
#अगर_घोषित __BIG_ENDIAN
		अणु 0xff, 0xff, 0, 12, 0, 1, 0, 4, 0, 2, 0, 4, 0, 3 पूर्ण,
#अन्यथा
		अणु 0xff, 0xff, 12, 0, 1, 0, 4, 0, 2, 0, 4, 0, 3, 0 पूर्ण,
#पूर्ण_अगर
		अणु अणु 4, 0 पूर्ण, अणु 20, 10 पूर्ण पूर्ण,
	पूर्ण,
	अणु
		"LD_PAYLOAD_OFF",
		.u.insns = अणु
			BPF_STMT(BPF_LD | BPF_W | BPF_ABS,
				 SKF_AD_OFF + SKF_AD_PAY_OFFSET),
			BPF_STMT(BPF_LD | BPF_W | BPF_ABS,
				 SKF_AD_OFF + SKF_AD_PAY_OFFSET),
			BPF_STMT(BPF_LD | BPF_W | BPF_ABS,
				 SKF_AD_OFF + SKF_AD_PAY_OFFSET),
			BPF_STMT(BPF_LD | BPF_W | BPF_ABS,
				 SKF_AD_OFF + SKF_AD_PAY_OFFSET),
			BPF_STMT(BPF_LD | BPF_W | BPF_ABS,
				 SKF_AD_OFF + SKF_AD_PAY_OFFSET),
			BPF_STMT(BPF_RET | BPF_A, 0)
		पूर्ण,
		CLASSIC,
		/* 00:00:00:00:00:00 > 00:00:00:00:00:00, ethtype IPv4 (0x0800),
		 * length 98: 127.0.0.1 > 127.0.0.1: ICMP echo request,
		 * id 9737, seq 1, length 64
		 */
		अणु 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		  0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		  0x08, 0x00,
		  0x45, 0x00, 0x00, 0x54, 0xac, 0x8b, 0x40, 0x00, 0x40,
		  0x01, 0x90, 0x1b, 0x7f, 0x00, 0x00, 0x01 पूर्ण,
		अणु अणु 30, 0 पूर्ण, अणु 100, 42 पूर्ण पूर्ण,
	पूर्ण,
	अणु
		"LD_ANC_XOR",
		.u.insns = अणु
			BPF_STMT(BPF_LD | BPF_IMM, 10),
			BPF_STMT(BPF_LDX | BPF_IMM, 300),
			BPF_STMT(BPF_LD | BPF_W | BPF_ABS,
				 SKF_AD_OFF + SKF_AD_ALU_XOR_X),
			BPF_STMT(BPF_RET | BPF_A, 0)
		पूर्ण,
		CLASSIC,
		अणु पूर्ण,
		अणु अणु 4, 0xA ^ 300 पूर्ण, अणु 20, 0xA ^ 300 पूर्ण पूर्ण,
	पूर्ण,
	अणु
		"SPILL_FILL",
		.u.insns = अणु
			BPF_STMT(BPF_LDX | BPF_LEN, 0),
			BPF_STMT(BPF_LD | BPF_IMM, 2),
			BPF_STMT(BPF_ALU | BPF_RSH, 1),
			BPF_STMT(BPF_ALU | BPF_XOR | BPF_X, 0),
			BPF_STMT(BPF_ST, 1), /* M1 = 1 ^ len */
			BPF_STMT(BPF_ALU | BPF_XOR | BPF_K, 0x80000000),
			BPF_STMT(BPF_ST, 2), /* M2 = 1 ^ len ^ 0x80000000 */
			BPF_STMT(BPF_STX, 15), /* M3 = len */
			BPF_STMT(BPF_LDX | BPF_MEM, 1),
			BPF_STMT(BPF_LD | BPF_MEM, 2),
			BPF_STMT(BPF_ALU | BPF_XOR | BPF_X, 0),
			BPF_STMT(BPF_LDX | BPF_MEM, 15),
			BPF_STMT(BPF_ALU | BPF_XOR | BPF_X, 0),
			BPF_STMT(BPF_RET | BPF_A, 0)
		पूर्ण,
		CLASSIC,
		अणु पूर्ण,
		अणु अणु 1, 0x80000001 पूर्ण, अणु 2, 0x80000002 पूर्ण, अणु 60, 0x80000000 ^ 60 पूर्ण पूर्ण
	पूर्ण,
	अणु
		"JEQ",
		.u.insns = अणु
			BPF_STMT(BPF_LDX | BPF_LEN, 0),
			BPF_STMT(BPF_LD | BPF_B | BPF_ABS, 2),
			BPF_JUMP(BPF_JMP | BPF_JEQ | BPF_X, 0, 0, 1),
			BPF_STMT(BPF_RET | BPF_K, 1),
			BPF_STMT(BPF_RET | BPF_K, MAX_K)
		पूर्ण,
		CLASSIC,
		अणु 3, 3, 3, 3, 3 पूर्ण,
		अणु अणु 1, 0 पूर्ण, अणु 3, 1 पूर्ण, अणु 4, MAX_K पूर्ण पूर्ण,
	पूर्ण,
	अणु
		"JGT",
		.u.insns = अणु
			BPF_STMT(BPF_LDX | BPF_LEN, 0),
			BPF_STMT(BPF_LD | BPF_B | BPF_ABS, 2),
			BPF_JUMP(BPF_JMP | BPF_JGT | BPF_X, 0, 0, 1),
			BPF_STMT(BPF_RET | BPF_K, 1),
			BPF_STMT(BPF_RET | BPF_K, MAX_K)
		पूर्ण,
		CLASSIC,
		अणु 4, 4, 4, 3, 3 पूर्ण,
		अणु अणु 2, 0 पूर्ण, अणु 3, 1 पूर्ण, अणु 4, MAX_K पूर्ण पूर्ण,
	पूर्ण,
	अणु
		"JGE (jt 0), test 1",
		.u.insns = अणु
			BPF_STMT(BPF_LDX | BPF_LEN, 0),
			BPF_STMT(BPF_LD | BPF_B | BPF_ABS, 2),
			BPF_JUMP(BPF_JMP | BPF_JGE | BPF_X, 0, 0, 1),
			BPF_STMT(BPF_RET | BPF_K, 1),
			BPF_STMT(BPF_RET | BPF_K, MAX_K)
		पूर्ण,
		CLASSIC,
		अणु 4, 4, 4, 3, 3 पूर्ण,
		अणु अणु 2, 0 पूर्ण, अणु 3, 1 पूर्ण, अणु 4, 1 पूर्ण पूर्ण,
	पूर्ण,
	अणु
		"JGE (jt 0), test 2",
		.u.insns = अणु
			BPF_STMT(BPF_LDX | BPF_LEN, 0),
			BPF_STMT(BPF_LD | BPF_B | BPF_ABS, 2),
			BPF_JUMP(BPF_JMP | BPF_JGE | BPF_X, 0, 0, 1),
			BPF_STMT(BPF_RET | BPF_K, 1),
			BPF_STMT(BPF_RET | BPF_K, MAX_K)
		पूर्ण,
		CLASSIC,
		अणु 4, 4, 5, 3, 3 पूर्ण,
		अणु अणु 4, 1 पूर्ण, अणु 5, 1 पूर्ण, अणु 6, MAX_K पूर्ण पूर्ण,
	पूर्ण,
	अणु
		"JGE",
		.u.insns = अणु
			BPF_STMT(BPF_LDX | BPF_LEN, 0),
			BPF_STMT(BPF_LD | BPF_B | BPF_IND, MAX_K),
			BPF_JUMP(BPF_JMP | BPF_JGE | BPF_K, 1, 1, 0),
			BPF_STMT(BPF_RET | BPF_K, 10),
			BPF_JUMP(BPF_JMP | BPF_JGE | BPF_K, 2, 1, 0),
			BPF_STMT(BPF_RET | BPF_K, 20),
			BPF_JUMP(BPF_JMP | BPF_JGE | BPF_K, 3, 1, 0),
			BPF_STMT(BPF_RET | BPF_K, 30),
			BPF_JUMP(BPF_JMP | BPF_JGE | BPF_K, 4, 1, 0),
			BPF_STMT(BPF_RET | BPF_K, 40),
			BPF_STMT(BPF_RET | BPF_K, MAX_K)
		पूर्ण,
		CLASSIC,
		अणु 1, 2, 3, 4, 5 पूर्ण,
		अणु अणु 1, 20 पूर्ण, अणु 3, 40 पूर्ण, अणु 5, MAX_K पूर्ण पूर्ण,
	पूर्ण,
	अणु
		"JSET",
		.u.insns = अणु
			BPF_JUMP(BPF_JMP | BPF_JA, 0, 0, 0),
			BPF_JUMP(BPF_JMP | BPF_JA, 1, 1, 1),
			BPF_JUMP(BPF_JMP | BPF_JA, 0, 0, 0),
			BPF_JUMP(BPF_JMP | BPF_JA, 0, 0, 0),
			BPF_STMT(BPF_LDX | BPF_LEN, 0),
			BPF_STMT(BPF_MISC | BPF_TXA, 0),
			BPF_STMT(BPF_ALU | BPF_SUB | BPF_K, 4),
			BPF_STMT(BPF_MISC | BPF_TAX, 0),
			BPF_STMT(BPF_LD | BPF_W | BPF_IND, 0),
			BPF_JUMP(BPF_JMP | BPF_JSET | BPF_K, 1, 0, 1),
			BPF_STMT(BPF_RET | BPF_K, 10),
			BPF_JUMP(BPF_JMP | BPF_JSET | BPF_K, 0x80000000, 0, 1),
			BPF_STMT(BPF_RET | BPF_K, 20),
			BPF_JUMP(BPF_JMP | BPF_JSET | BPF_K, 0xffffff, 1, 0),
			BPF_STMT(BPF_RET | BPF_K, 30),
			BPF_JUMP(BPF_JMP | BPF_JSET | BPF_K, 0xffffff, 1, 0),
			BPF_STMT(BPF_RET | BPF_K, 30),
			BPF_JUMP(BPF_JMP | BPF_JSET | BPF_K, 0xffffff, 1, 0),
			BPF_STMT(BPF_RET | BPF_K, 30),
			BPF_JUMP(BPF_JMP | BPF_JSET | BPF_K, 0xffffff, 1, 0),
			BPF_STMT(BPF_RET | BPF_K, 30),
			BPF_JUMP(BPF_JMP | BPF_JSET | BPF_K, 0xffffff, 1, 0),
			BPF_STMT(BPF_RET | BPF_K, 30),
			BPF_STMT(BPF_RET | BPF_K, MAX_K)
		पूर्ण,
		CLASSIC,
		अणु 0, 0xAA, 0x55, 1 पूर्ण,
		अणु अणु 4, 10 पूर्ण, अणु 5, 20 पूर्ण, अणु 6, MAX_K पूर्ण पूर्ण,
	पूर्ण,
	अणु
		"tcpdump port 22",
		.u.insns = अणु
			BPF_STMT(BPF_LD | BPF_H | BPF_ABS, 12),
			BPF_JUMP(BPF_JMP | BPF_JEQ | BPF_K, 0x86dd, 0, 8), /* IPv6 */
			BPF_STMT(BPF_LD | BPF_B | BPF_ABS, 20),
			BPF_JUMP(BPF_JMP | BPF_JEQ | BPF_K, 0x84, 2, 0),
			BPF_JUMP(BPF_JMP | BPF_JEQ | BPF_K, 0x6, 1, 0),
			BPF_JUMP(BPF_JMP | BPF_JEQ | BPF_K, 0x11, 0, 17),
			BPF_STMT(BPF_LD | BPF_H | BPF_ABS, 54),
			BPF_JUMP(BPF_JMP | BPF_JEQ | BPF_K, 22, 14, 0),
			BPF_STMT(BPF_LD | BPF_H | BPF_ABS, 56),
			BPF_JUMP(BPF_JMP | BPF_JEQ | BPF_K, 22, 12, 13),
			BPF_JUMP(BPF_JMP | BPF_JEQ | BPF_K, 0x0800, 0, 12), /* IPv4 */
			BPF_STMT(BPF_LD | BPF_B | BPF_ABS, 23),
			BPF_JUMP(BPF_JMP | BPF_JEQ | BPF_K, 0x84, 2, 0),
			BPF_JUMP(BPF_JMP | BPF_JEQ | BPF_K, 0x6, 1, 0),
			BPF_JUMP(BPF_JMP | BPF_JEQ | BPF_K, 0x11, 0, 8),
			BPF_STMT(BPF_LD | BPF_H | BPF_ABS, 20),
			BPF_JUMP(BPF_JMP | BPF_JSET | BPF_K, 0x1fff, 6, 0),
			BPF_STMT(BPF_LDX | BPF_B | BPF_MSH, 14),
			BPF_STMT(BPF_LD | BPF_H | BPF_IND, 14),
			BPF_JUMP(BPF_JMP | BPF_JEQ | BPF_K, 22, 2, 0),
			BPF_STMT(BPF_LD | BPF_H | BPF_IND, 16),
			BPF_JUMP(BPF_JMP | BPF_JEQ | BPF_K, 22, 0, 1),
			BPF_STMT(BPF_RET | BPF_K, 0xffff),
			BPF_STMT(BPF_RET | BPF_K, 0),
		पूर्ण,
		CLASSIC,
		/* 3c:07:54:43:e5:76 > 10:bf:48:d6:43:d6, ethertype IPv4(0x0800)
		 * length 114: 10.1.1.149.49700 > 10.1.2.10.22: Flags [P.],
		 * seq 1305692979:1305693027, ack 3650467037, win 65535,
		 * options [nop,nop,TS val 2502645400 ecr 3971138], length 48
		 */
		अणु 0x10, 0xbf, 0x48, 0xd6, 0x43, 0xd6,
		  0x3c, 0x07, 0x54, 0x43, 0xe5, 0x76,
		  0x08, 0x00,
		  0x45, 0x10, 0x00, 0x64, 0x75, 0xb5,
		  0x40, 0x00, 0x40, 0x06, 0xad, 0x2e, /* IP header */
		  0x0a, 0x01, 0x01, 0x95, /* ip src */
		  0x0a, 0x01, 0x02, 0x0a, /* ip dst */
		  0xc2, 0x24,
		  0x00, 0x16 /* dst port */ पूर्ण,
		अणु अणु 10, 0 पूर्ण, अणु 30, 0 पूर्ण, अणु 100, 65535 पूर्ण पूर्ण,
	पूर्ण,
	अणु
		"tcpdump complex",
		.u.insns = अणु
			/* tcpdump -nei eth0 'tcp port 22 and (((ip[2:2] -
			 * ((ip[0]&0xf)<<2)) - ((tcp[12]&0xf0)>>2)) != 0) and
			 * (len > 115 or len < 30000000000)' -d
			 */
			BPF_STMT(BPF_LD | BPF_H | BPF_ABS, 12),
			BPF_JUMP(BPF_JMP | BPF_JEQ | BPF_K, 0x86dd, 30, 0),
			BPF_JUMP(BPF_JMP | BPF_JEQ | BPF_K, 0x800, 0, 29),
			BPF_STMT(BPF_LD | BPF_B | BPF_ABS, 23),
			BPF_JUMP(BPF_JMP | BPF_JEQ | BPF_K, 0x6, 0, 27),
			BPF_STMT(BPF_LD | BPF_H | BPF_ABS, 20),
			BPF_JUMP(BPF_JMP | BPF_JSET | BPF_K, 0x1fff, 25, 0),
			BPF_STMT(BPF_LDX | BPF_B | BPF_MSH, 14),
			BPF_STMT(BPF_LD | BPF_H | BPF_IND, 14),
			BPF_JUMP(BPF_JMP | BPF_JEQ | BPF_K, 22, 2, 0),
			BPF_STMT(BPF_LD | BPF_H | BPF_IND, 16),
			BPF_JUMP(BPF_JMP | BPF_JEQ | BPF_K, 22, 0, 20),
			BPF_STMT(BPF_LD | BPF_H | BPF_ABS, 16),
			BPF_STMT(BPF_ST, 1),
			BPF_STMT(BPF_LD | BPF_B | BPF_ABS, 14),
			BPF_STMT(BPF_ALU | BPF_AND | BPF_K, 0xf),
			BPF_STMT(BPF_ALU | BPF_LSH | BPF_K, 2),
			BPF_STMT(BPF_MISC | BPF_TAX, 0x5), /* libpcap emits K on TAX */
			BPF_STMT(BPF_LD | BPF_MEM, 1),
			BPF_STMT(BPF_ALU | BPF_SUB | BPF_X, 0),
			BPF_STMT(BPF_ST, 5),
			BPF_STMT(BPF_LDX | BPF_B | BPF_MSH, 14),
			BPF_STMT(BPF_LD | BPF_B | BPF_IND, 26),
			BPF_STMT(BPF_ALU | BPF_AND | BPF_K, 0xf0),
			BPF_STMT(BPF_ALU | BPF_RSH | BPF_K, 2),
			BPF_STMT(BPF_MISC | BPF_TAX, 0x9), /* libpcap emits K on TAX */
			BPF_STMT(BPF_LD | BPF_MEM, 5),
			BPF_JUMP(BPF_JMP | BPF_JEQ | BPF_X, 0, 4, 0),
			BPF_STMT(BPF_LD | BPF_LEN, 0),
			BPF_JUMP(BPF_JMP | BPF_JGT | BPF_K, 0x73, 1, 0),
			BPF_JUMP(BPF_JMP | BPF_JGE | BPF_K, 0xfc23ac00, 1, 0),
			BPF_STMT(BPF_RET | BPF_K, 0xffff),
			BPF_STMT(BPF_RET | BPF_K, 0),
		पूर्ण,
		CLASSIC,
		अणु 0x10, 0xbf, 0x48, 0xd6, 0x43, 0xd6,
		  0x3c, 0x07, 0x54, 0x43, 0xe5, 0x76,
		  0x08, 0x00,
		  0x45, 0x10, 0x00, 0x64, 0x75, 0xb5,
		  0x40, 0x00, 0x40, 0x06, 0xad, 0x2e, /* IP header */
		  0x0a, 0x01, 0x01, 0x95, /* ip src */
		  0x0a, 0x01, 0x02, 0x0a, /* ip dst */
		  0xc2, 0x24,
		  0x00, 0x16 /* dst port */ पूर्ण,
		अणु अणु 10, 0 पूर्ण, अणु 30, 0 पूर्ण, अणु 100, 65535 पूर्ण पूर्ण,
	पूर्ण,
	अणु
		"RET_A",
		.u.insns = अणु
			/* check that unitialized X and A contain zeros */
			BPF_STMT(BPF_MISC | BPF_TXA, 0),
			BPF_STMT(BPF_RET | BPF_A, 0)
		पूर्ण,
		CLASSIC,
		अणु पूर्ण,
		अणु अणु1, 0पूर्ण, अणु2, 0पूर्ण पूर्ण,
	पूर्ण,
	अणु
		"INT: ADD trivial",
		.u.insns_पूर्णांक = अणु
			BPF_ALU64_IMM(BPF_MOV, R1, 1),
			BPF_ALU64_IMM(BPF_ADD, R1, 2),
			BPF_ALU64_IMM(BPF_MOV, R2, 3),
			BPF_ALU64_REG(BPF_SUB, R1, R2),
			BPF_ALU64_IMM(BPF_ADD, R1, -1),
			BPF_ALU64_IMM(BPF_MUL, R1, 3),
			BPF_ALU64_REG(BPF_MOV, R0, R1),
			BPF_EXIT_INSN(),
		पूर्ण,
		INTERNAL,
		अणु पूर्ण,
		अणु अणु 0, 0xfffffffd पूर्ण पूर्ण
	पूर्ण,
	अणु
		"INT: MUL_X",
		.u.insns_पूर्णांक = अणु
			BPF_ALU64_IMM(BPF_MOV, R0, -1),
			BPF_ALU64_IMM(BPF_MOV, R1, -1),
			BPF_ALU64_IMM(BPF_MOV, R2, 3),
			BPF_ALU64_REG(BPF_MUL, R1, R2),
			BPF_JMP_IMM(BPF_JEQ, R1, 0xfffffffd, 1),
			BPF_EXIT_INSN(),
			BPF_ALU64_IMM(BPF_MOV, R0, 1),
			BPF_EXIT_INSN(),
		पूर्ण,
		INTERNAL,
		अणु पूर्ण,
		अणु अणु 0, 1 पूर्ण पूर्ण
	पूर्ण,
	अणु
		"INT: MUL_X2",
		.u.insns_पूर्णांक = अणु
			BPF_ALU32_IMM(BPF_MOV, R0, -1),
			BPF_ALU32_IMM(BPF_MOV, R1, -1),
			BPF_ALU32_IMM(BPF_MOV, R2, 3),
			BPF_ALU64_REG(BPF_MUL, R1, R2),
			BPF_ALU64_IMM(BPF_RSH, R1, 8),
			BPF_JMP_IMM(BPF_JEQ, R1, 0x2ffffff, 1),
			BPF_EXIT_INSN(),
			BPF_ALU32_IMM(BPF_MOV, R0, 1),
			BPF_EXIT_INSN(),
		पूर्ण,
		INTERNAL,
		अणु पूर्ण,
		अणु अणु 0, 1 पूर्ण पूर्ण
	पूर्ण,
	अणु
		"INT: MUL32_X",
		.u.insns_पूर्णांक = अणु
			BPF_ALU32_IMM(BPF_MOV, R0, -1),
			BPF_ALU64_IMM(BPF_MOV, R1, -1),
			BPF_ALU32_IMM(BPF_MOV, R2, 3),
			BPF_ALU32_REG(BPF_MUL, R1, R2),
			BPF_ALU64_IMM(BPF_RSH, R1, 8),
			BPF_JMP_IMM(BPF_JEQ, R1, 0xffffff, 1),
			BPF_EXIT_INSN(),
			BPF_ALU32_IMM(BPF_MOV, R0, 1),
			BPF_EXIT_INSN(),
		पूर्ण,
		INTERNAL,
		अणु पूर्ण,
		अणु अणु 0, 1 पूर्ण पूर्ण
	पूर्ण,
	अणु
		/* Have to test all रेजिस्टर combinations, since
		 * JITing of dअगरferent रेजिस्टरs will produce
		 * dअगरferent यंत्र code.
		 */
		"INT: ADD 64-bit",
		.u.insns_पूर्णांक = अणु
			BPF_ALU64_IMM(BPF_MOV, R0, 0),
			BPF_ALU64_IMM(BPF_MOV, R1, 1),
			BPF_ALU64_IMM(BPF_MOV, R2, 2),
			BPF_ALU64_IMM(BPF_MOV, R3, 3),
			BPF_ALU64_IMM(BPF_MOV, R4, 4),
			BPF_ALU64_IMM(BPF_MOV, R5, 5),
			BPF_ALU64_IMM(BPF_MOV, R6, 6),
			BPF_ALU64_IMM(BPF_MOV, R7, 7),
			BPF_ALU64_IMM(BPF_MOV, R8, 8),
			BPF_ALU64_IMM(BPF_MOV, R9, 9),
			BPF_ALU64_IMM(BPF_ADD, R0, 20),
			BPF_ALU64_IMM(BPF_ADD, R1, 20),
			BPF_ALU64_IMM(BPF_ADD, R2, 20),
			BPF_ALU64_IMM(BPF_ADD, R3, 20),
			BPF_ALU64_IMM(BPF_ADD, R4, 20),
			BPF_ALU64_IMM(BPF_ADD, R5, 20),
			BPF_ALU64_IMM(BPF_ADD, R6, 20),
			BPF_ALU64_IMM(BPF_ADD, R7, 20),
			BPF_ALU64_IMM(BPF_ADD, R8, 20),
			BPF_ALU64_IMM(BPF_ADD, R9, 20),
			BPF_ALU64_IMM(BPF_SUB, R0, 10),
			BPF_ALU64_IMM(BPF_SUB, R1, 10),
			BPF_ALU64_IMM(BPF_SUB, R2, 10),
			BPF_ALU64_IMM(BPF_SUB, R3, 10),
			BPF_ALU64_IMM(BPF_SUB, R4, 10),
			BPF_ALU64_IMM(BPF_SUB, R5, 10),
			BPF_ALU64_IMM(BPF_SUB, R6, 10),
			BPF_ALU64_IMM(BPF_SUB, R7, 10),
			BPF_ALU64_IMM(BPF_SUB, R8, 10),
			BPF_ALU64_IMM(BPF_SUB, R9, 10),
			BPF_ALU64_REG(BPF_ADD, R0, R0),
			BPF_ALU64_REG(BPF_ADD, R0, R1),
			BPF_ALU64_REG(BPF_ADD, R0, R2),
			BPF_ALU64_REG(BPF_ADD, R0, R3),
			BPF_ALU64_REG(BPF_ADD, R0, R4),
			BPF_ALU64_REG(BPF_ADD, R0, R5),
			BPF_ALU64_REG(BPF_ADD, R0, R6),
			BPF_ALU64_REG(BPF_ADD, R0, R7),
			BPF_ALU64_REG(BPF_ADD, R0, R8),
			BPF_ALU64_REG(BPF_ADD, R0, R9), /* R0 == 155 */
			BPF_JMP_IMM(BPF_JEQ, R0, 155, 1),
			BPF_EXIT_INSN(),
			BPF_ALU64_REG(BPF_ADD, R1, R0),
			BPF_ALU64_REG(BPF_ADD, R1, R1),
			BPF_ALU64_REG(BPF_ADD, R1, R2),
			BPF_ALU64_REG(BPF_ADD, R1, R3),
			BPF_ALU64_REG(BPF_ADD, R1, R4),
			BPF_ALU64_REG(BPF_ADD, R1, R5),
			BPF_ALU64_REG(BPF_ADD, R1, R6),
			BPF_ALU64_REG(BPF_ADD, R1, R7),
			BPF_ALU64_REG(BPF_ADD, R1, R8),
			BPF_ALU64_REG(BPF_ADD, R1, R9), /* R1 == 456 */
			BPF_JMP_IMM(BPF_JEQ, R1, 456, 1),
			BPF_EXIT_INSN(),
			BPF_ALU64_REG(BPF_ADD, R2, R0),
			BPF_ALU64_REG(BPF_ADD, R2, R1),
			BPF_ALU64_REG(BPF_ADD, R2, R2),
			BPF_ALU64_REG(BPF_ADD, R2, R3),
			BPF_ALU64_REG(BPF_ADD, R2, R4),
			BPF_ALU64_REG(BPF_ADD, R2, R5),
			BPF_ALU64_REG(BPF_ADD, R2, R6),
			BPF_ALU64_REG(BPF_ADD, R2, R7),
			BPF_ALU64_REG(BPF_ADD, R2, R8),
			BPF_ALU64_REG(BPF_ADD, R2, R9), /* R2 == 1358 */
			BPF_JMP_IMM(BPF_JEQ, R2, 1358, 1),
			BPF_EXIT_INSN(),
			BPF_ALU64_REG(BPF_ADD, R3, R0),
			BPF_ALU64_REG(BPF_ADD, R3, R1),
			BPF_ALU64_REG(BPF_ADD, R3, R2),
			BPF_ALU64_REG(BPF_ADD, R3, R3),
			BPF_ALU64_REG(BPF_ADD, R3, R4),
			BPF_ALU64_REG(BPF_ADD, R3, R5),
			BPF_ALU64_REG(BPF_ADD, R3, R6),
			BPF_ALU64_REG(BPF_ADD, R3, R7),
			BPF_ALU64_REG(BPF_ADD, R3, R8),
			BPF_ALU64_REG(BPF_ADD, R3, R9), /* R3 == 4063 */
			BPF_JMP_IMM(BPF_JEQ, R3, 4063, 1),
			BPF_EXIT_INSN(),
			BPF_ALU64_REG(BPF_ADD, R4, R0),
			BPF_ALU64_REG(BPF_ADD, R4, R1),
			BPF_ALU64_REG(BPF_ADD, R4, R2),
			BPF_ALU64_REG(BPF_ADD, R4, R3),
			BPF_ALU64_REG(BPF_ADD, R4, R4),
			BPF_ALU64_REG(BPF_ADD, R4, R5),
			BPF_ALU64_REG(BPF_ADD, R4, R6),
			BPF_ALU64_REG(BPF_ADD, R4, R7),
			BPF_ALU64_REG(BPF_ADD, R4, R8),
			BPF_ALU64_REG(BPF_ADD, R4, R9), /* R4 == 12177 */
			BPF_JMP_IMM(BPF_JEQ, R4, 12177, 1),
			BPF_EXIT_INSN(),
			BPF_ALU64_REG(BPF_ADD, R5, R0),
			BPF_ALU64_REG(BPF_ADD, R5, R1),
			BPF_ALU64_REG(BPF_ADD, R5, R2),
			BPF_ALU64_REG(BPF_ADD, R5, R3),
			BPF_ALU64_REG(BPF_ADD, R5, R4),
			BPF_ALU64_REG(BPF_ADD, R5, R5),
			BPF_ALU64_REG(BPF_ADD, R5, R6),
			BPF_ALU64_REG(BPF_ADD, R5, R7),
			BPF_ALU64_REG(BPF_ADD, R5, R8),
			BPF_ALU64_REG(BPF_ADD, R5, R9), /* R5 == 36518 */
			BPF_JMP_IMM(BPF_JEQ, R5, 36518, 1),
			BPF_EXIT_INSN(),
			BPF_ALU64_REG(BPF_ADD, R6, R0),
			BPF_ALU64_REG(BPF_ADD, R6, R1),
			BPF_ALU64_REG(BPF_ADD, R6, R2),
			BPF_ALU64_REG(BPF_ADD, R6, R3),
			BPF_ALU64_REG(BPF_ADD, R6, R4),
			BPF_ALU64_REG(BPF_ADD, R6, R5),
			BPF_ALU64_REG(BPF_ADD, R6, R6),
			BPF_ALU64_REG(BPF_ADD, R6, R7),
			BPF_ALU64_REG(BPF_ADD, R6, R8),
			BPF_ALU64_REG(BPF_ADD, R6, R9), /* R6 == 109540 */
			BPF_JMP_IMM(BPF_JEQ, R6, 109540, 1),
			BPF_EXIT_INSN(),
			BPF_ALU64_REG(BPF_ADD, R7, R0),
			BPF_ALU64_REG(BPF_ADD, R7, R1),
			BPF_ALU64_REG(BPF_ADD, R7, R2),
			BPF_ALU64_REG(BPF_ADD, R7, R3),
			BPF_ALU64_REG(BPF_ADD, R7, R4),
			BPF_ALU64_REG(BPF_ADD, R7, R5),
			BPF_ALU64_REG(BPF_ADD, R7, R6),
			BPF_ALU64_REG(BPF_ADD, R7, R7),
			BPF_ALU64_REG(BPF_ADD, R7, R8),
			BPF_ALU64_REG(BPF_ADD, R7, R9), /* R7 == 328605 */
			BPF_JMP_IMM(BPF_JEQ, R7, 328605, 1),
			BPF_EXIT_INSN(),
			BPF_ALU64_REG(BPF_ADD, R8, R0),
			BPF_ALU64_REG(BPF_ADD, R8, R1),
			BPF_ALU64_REG(BPF_ADD, R8, R2),
			BPF_ALU64_REG(BPF_ADD, R8, R3),
			BPF_ALU64_REG(BPF_ADD, R8, R4),
			BPF_ALU64_REG(BPF_ADD, R8, R5),
			BPF_ALU64_REG(BPF_ADD, R8, R6),
			BPF_ALU64_REG(BPF_ADD, R8, R7),
			BPF_ALU64_REG(BPF_ADD, R8, R8),
			BPF_ALU64_REG(BPF_ADD, R8, R9), /* R8 == 985799 */
			BPF_JMP_IMM(BPF_JEQ, R8, 985799, 1),
			BPF_EXIT_INSN(),
			BPF_ALU64_REG(BPF_ADD, R9, R0),
			BPF_ALU64_REG(BPF_ADD, R9, R1),
			BPF_ALU64_REG(BPF_ADD, R9, R2),
			BPF_ALU64_REG(BPF_ADD, R9, R3),
			BPF_ALU64_REG(BPF_ADD, R9, R4),
			BPF_ALU64_REG(BPF_ADD, R9, R5),
			BPF_ALU64_REG(BPF_ADD, R9, R6),
			BPF_ALU64_REG(BPF_ADD, R9, R7),
			BPF_ALU64_REG(BPF_ADD, R9, R8),
			BPF_ALU64_REG(BPF_ADD, R9, R9), /* R9 == 2957380 */
			BPF_ALU64_REG(BPF_MOV, R0, R9),
			BPF_EXIT_INSN(),
		पूर्ण,
		INTERNAL,
		अणु पूर्ण,
		अणु अणु 0, 2957380 पूर्ण पूर्ण
	पूर्ण,
	अणु
		"INT: ADD 32-bit",
		.u.insns_पूर्णांक = अणु
			BPF_ALU32_IMM(BPF_MOV, R0, 20),
			BPF_ALU32_IMM(BPF_MOV, R1, 1),
			BPF_ALU32_IMM(BPF_MOV, R2, 2),
			BPF_ALU32_IMM(BPF_MOV, R3, 3),
			BPF_ALU32_IMM(BPF_MOV, R4, 4),
			BPF_ALU32_IMM(BPF_MOV, R5, 5),
			BPF_ALU32_IMM(BPF_MOV, R6, 6),
			BPF_ALU32_IMM(BPF_MOV, R7, 7),
			BPF_ALU32_IMM(BPF_MOV, R8, 8),
			BPF_ALU32_IMM(BPF_MOV, R9, 9),
			BPF_ALU64_IMM(BPF_ADD, R1, 10),
			BPF_ALU64_IMM(BPF_ADD, R2, 10),
			BPF_ALU64_IMM(BPF_ADD, R3, 10),
			BPF_ALU64_IMM(BPF_ADD, R4, 10),
			BPF_ALU64_IMM(BPF_ADD, R5, 10),
			BPF_ALU64_IMM(BPF_ADD, R6, 10),
			BPF_ALU64_IMM(BPF_ADD, R7, 10),
			BPF_ALU64_IMM(BPF_ADD, R8, 10),
			BPF_ALU64_IMM(BPF_ADD, R9, 10),
			BPF_ALU32_REG(BPF_ADD, R0, R1),
			BPF_ALU32_REG(BPF_ADD, R0, R2),
			BPF_ALU32_REG(BPF_ADD, R0, R3),
			BPF_ALU32_REG(BPF_ADD, R0, R4),
			BPF_ALU32_REG(BPF_ADD, R0, R5),
			BPF_ALU32_REG(BPF_ADD, R0, R6),
			BPF_ALU32_REG(BPF_ADD, R0, R7),
			BPF_ALU32_REG(BPF_ADD, R0, R8),
			BPF_ALU32_REG(BPF_ADD, R0, R9), /* R0 == 155 */
			BPF_JMP_IMM(BPF_JEQ, R0, 155, 1),
			BPF_EXIT_INSN(),
			BPF_ALU32_REG(BPF_ADD, R1, R0),
			BPF_ALU32_REG(BPF_ADD, R1, R1),
			BPF_ALU32_REG(BPF_ADD, R1, R2),
			BPF_ALU32_REG(BPF_ADD, R1, R3),
			BPF_ALU32_REG(BPF_ADD, R1, R4),
			BPF_ALU32_REG(BPF_ADD, R1, R5),
			BPF_ALU32_REG(BPF_ADD, R1, R6),
			BPF_ALU32_REG(BPF_ADD, R1, R7),
			BPF_ALU32_REG(BPF_ADD, R1, R8),
			BPF_ALU32_REG(BPF_ADD, R1, R9), /* R1 == 456 */
			BPF_JMP_IMM(BPF_JEQ, R1, 456, 1),
			BPF_EXIT_INSN(),
			BPF_ALU32_REG(BPF_ADD, R2, R0),
			BPF_ALU32_REG(BPF_ADD, R2, R1),
			BPF_ALU32_REG(BPF_ADD, R2, R2),
			BPF_ALU32_REG(BPF_ADD, R2, R3),
			BPF_ALU32_REG(BPF_ADD, R2, R4),
			BPF_ALU32_REG(BPF_ADD, R2, R5),
			BPF_ALU32_REG(BPF_ADD, R2, R6),
			BPF_ALU32_REG(BPF_ADD, R2, R7),
			BPF_ALU32_REG(BPF_ADD, R2, R8),
			BPF_ALU32_REG(BPF_ADD, R2, R9), /* R2 == 1358 */
			BPF_JMP_IMM(BPF_JEQ, R2, 1358, 1),
			BPF_EXIT_INSN(),
			BPF_ALU32_REG(BPF_ADD, R3, R0),
			BPF_ALU32_REG(BPF_ADD, R3, R1),
			BPF_ALU32_REG(BPF_ADD, R3, R2),
			BPF_ALU32_REG(BPF_ADD, R3, R3),
			BPF_ALU32_REG(BPF_ADD, R3, R4),
			BPF_ALU32_REG(BPF_ADD, R3, R5),
			BPF_ALU32_REG(BPF_ADD, R3, R6),
			BPF_ALU32_REG(BPF_ADD, R3, R7),
			BPF_ALU32_REG(BPF_ADD, R3, R8),
			BPF_ALU32_REG(BPF_ADD, R3, R9), /* R3 == 4063 */
			BPF_JMP_IMM(BPF_JEQ, R3, 4063, 1),
			BPF_EXIT_INSN(),
			BPF_ALU32_REG(BPF_ADD, R4, R0),
			BPF_ALU32_REG(BPF_ADD, R4, R1),
			BPF_ALU32_REG(BPF_ADD, R4, R2),
			BPF_ALU32_REG(BPF_ADD, R4, R3),
			BPF_ALU32_REG(BPF_ADD, R4, R4),
			BPF_ALU32_REG(BPF_ADD, R4, R5),
			BPF_ALU32_REG(BPF_ADD, R4, R6),
			BPF_ALU32_REG(BPF_ADD, R4, R7),
			BPF_ALU32_REG(BPF_ADD, R4, R8),
			BPF_ALU32_REG(BPF_ADD, R4, R9), /* R4 == 12177 */
			BPF_JMP_IMM(BPF_JEQ, R4, 12177, 1),
			BPF_EXIT_INSN(),
			BPF_ALU32_REG(BPF_ADD, R5, R0),
			BPF_ALU32_REG(BPF_ADD, R5, R1),
			BPF_ALU32_REG(BPF_ADD, R5, R2),
			BPF_ALU32_REG(BPF_ADD, R5, R3),
			BPF_ALU32_REG(BPF_ADD, R5, R4),
			BPF_ALU32_REG(BPF_ADD, R5, R5),
			BPF_ALU32_REG(BPF_ADD, R5, R6),
			BPF_ALU32_REG(BPF_ADD, R5, R7),
			BPF_ALU32_REG(BPF_ADD, R5, R8),
			BPF_ALU32_REG(BPF_ADD, R5, R9), /* R5 == 36518 */
			BPF_JMP_IMM(BPF_JEQ, R5, 36518, 1),
			BPF_EXIT_INSN(),
			BPF_ALU32_REG(BPF_ADD, R6, R0),
			BPF_ALU32_REG(BPF_ADD, R6, R1),
			BPF_ALU32_REG(BPF_ADD, R6, R2),
			BPF_ALU32_REG(BPF_ADD, R6, R3),
			BPF_ALU32_REG(BPF_ADD, R6, R4),
			BPF_ALU32_REG(BPF_ADD, R6, R5),
			BPF_ALU32_REG(BPF_ADD, R6, R6),
			BPF_ALU32_REG(BPF_ADD, R6, R7),
			BPF_ALU32_REG(BPF_ADD, R6, R8),
			BPF_ALU32_REG(BPF_ADD, R6, R9), /* R6 == 109540 */
			BPF_JMP_IMM(BPF_JEQ, R6, 109540, 1),
			BPF_EXIT_INSN(),
			BPF_ALU32_REG(BPF_ADD, R7, R0),
			BPF_ALU32_REG(BPF_ADD, R7, R1),
			BPF_ALU32_REG(BPF_ADD, R7, R2),
			BPF_ALU32_REG(BPF_ADD, R7, R3),
			BPF_ALU32_REG(BPF_ADD, R7, R4),
			BPF_ALU32_REG(BPF_ADD, R7, R5),
			BPF_ALU32_REG(BPF_ADD, R7, R6),
			BPF_ALU32_REG(BPF_ADD, R7, R7),
			BPF_ALU32_REG(BPF_ADD, R7, R8),
			BPF_ALU32_REG(BPF_ADD, R7, R9), /* R7 == 328605 */
			BPF_JMP_IMM(BPF_JEQ, R7, 328605, 1),
			BPF_EXIT_INSN(),
			BPF_ALU32_REG(BPF_ADD, R8, R0),
			BPF_ALU32_REG(BPF_ADD, R8, R1),
			BPF_ALU32_REG(BPF_ADD, R8, R2),
			BPF_ALU32_REG(BPF_ADD, R8, R3),
			BPF_ALU32_REG(BPF_ADD, R8, R4),
			BPF_ALU32_REG(BPF_ADD, R8, R5),
			BPF_ALU32_REG(BPF_ADD, R8, R6),
			BPF_ALU32_REG(BPF_ADD, R8, R7),
			BPF_ALU32_REG(BPF_ADD, R8, R8),
			BPF_ALU32_REG(BPF_ADD, R8, R9), /* R8 == 985799 */
			BPF_JMP_IMM(BPF_JEQ, R8, 985799, 1),
			BPF_EXIT_INSN(),
			BPF_ALU32_REG(BPF_ADD, R9, R0),
			BPF_ALU32_REG(BPF_ADD, R9, R1),
			BPF_ALU32_REG(BPF_ADD, R9, R2),
			BPF_ALU32_REG(BPF_ADD, R9, R3),
			BPF_ALU32_REG(BPF_ADD, R9, R4),
			BPF_ALU32_REG(BPF_ADD, R9, R5),
			BPF_ALU32_REG(BPF_ADD, R9, R6),
			BPF_ALU32_REG(BPF_ADD, R9, R7),
			BPF_ALU32_REG(BPF_ADD, R9, R8),
			BPF_ALU32_REG(BPF_ADD, R9, R9), /* R9 == 2957380 */
			BPF_ALU32_REG(BPF_MOV, R0, R9),
			BPF_EXIT_INSN(),
		पूर्ण,
		INTERNAL,
		अणु पूर्ण,
		अणु अणु 0, 2957380 पूर्ण पूर्ण
	पूर्ण,
	अणु	/* Mainly checking JIT here. */
		"INT: SUB",
		.u.insns_पूर्णांक = अणु
			BPF_ALU64_IMM(BPF_MOV, R0, 0),
			BPF_ALU64_IMM(BPF_MOV, R1, 1),
			BPF_ALU64_IMM(BPF_MOV, R2, 2),
			BPF_ALU64_IMM(BPF_MOV, R3, 3),
			BPF_ALU64_IMM(BPF_MOV, R4, 4),
			BPF_ALU64_IMM(BPF_MOV, R5, 5),
			BPF_ALU64_IMM(BPF_MOV, R6, 6),
			BPF_ALU64_IMM(BPF_MOV, R7, 7),
			BPF_ALU64_IMM(BPF_MOV, R8, 8),
			BPF_ALU64_IMM(BPF_MOV, R9, 9),
			BPF_ALU64_REG(BPF_SUB, R0, R0),
			BPF_ALU64_REG(BPF_SUB, R0, R1),
			BPF_ALU64_REG(BPF_SUB, R0, R2),
			BPF_ALU64_REG(BPF_SUB, R0, R3),
			BPF_ALU64_REG(BPF_SUB, R0, R4),
			BPF_ALU64_REG(BPF_SUB, R0, R5),
			BPF_ALU64_REG(BPF_SUB, R0, R6),
			BPF_ALU64_REG(BPF_SUB, R0, R7),
			BPF_ALU64_REG(BPF_SUB, R0, R8),
			BPF_ALU64_REG(BPF_SUB, R0, R9),
			BPF_ALU64_IMM(BPF_SUB, R0, 10),
			BPF_JMP_IMM(BPF_JEQ, R0, -55, 1),
			BPF_EXIT_INSN(),
			BPF_ALU64_REG(BPF_SUB, R1, R0),
			BPF_ALU64_REG(BPF_SUB, R1, R2),
			BPF_ALU64_REG(BPF_SUB, R1, R3),
			BPF_ALU64_REG(BPF_SUB, R1, R4),
			BPF_ALU64_REG(BPF_SUB, R1, R5),
			BPF_ALU64_REG(BPF_SUB, R1, R6),
			BPF_ALU64_REG(BPF_SUB, R1, R7),
			BPF_ALU64_REG(BPF_SUB, R1, R8),
			BPF_ALU64_REG(BPF_SUB, R1, R9),
			BPF_ALU64_IMM(BPF_SUB, R1, 10),
			BPF_ALU64_REG(BPF_SUB, R2, R0),
			BPF_ALU64_REG(BPF_SUB, R2, R1),
			BPF_ALU64_REG(BPF_SUB, R2, R3),
			BPF_ALU64_REG(BPF_SUB, R2, R4),
			BPF_ALU64_REG(BPF_SUB, R2, R5),
			BPF_ALU64_REG(BPF_SUB, R2, R6),
			BPF_ALU64_REG(BPF_SUB, R2, R7),
			BPF_ALU64_REG(BPF_SUB, R2, R8),
			BPF_ALU64_REG(BPF_SUB, R2, R9),
			BPF_ALU64_IMM(BPF_SUB, R2, 10),
			BPF_ALU64_REG(BPF_SUB, R3, R0),
			BPF_ALU64_REG(BPF_SUB, R3, R1),
			BPF_ALU64_REG(BPF_SUB, R3, R2),
			BPF_ALU64_REG(BPF_SUB, R3, R4),
			BPF_ALU64_REG(BPF_SUB, R3, R5),
			BPF_ALU64_REG(BPF_SUB, R3, R6),
			BPF_ALU64_REG(BPF_SUB, R3, R7),
			BPF_ALU64_REG(BPF_SUB, R3, R8),
			BPF_ALU64_REG(BPF_SUB, R3, R9),
			BPF_ALU64_IMM(BPF_SUB, R3, 10),
			BPF_ALU64_REG(BPF_SUB, R4, R0),
			BPF_ALU64_REG(BPF_SUB, R4, R1),
			BPF_ALU64_REG(BPF_SUB, R4, R2),
			BPF_ALU64_REG(BPF_SUB, R4, R3),
			BPF_ALU64_REG(BPF_SUB, R4, R5),
			BPF_ALU64_REG(BPF_SUB, R4, R6),
			BPF_ALU64_REG(BPF_SUB, R4, R7),
			BPF_ALU64_REG(BPF_SUB, R4, R8),
			BPF_ALU64_REG(BPF_SUB, R4, R9),
			BPF_ALU64_IMM(BPF_SUB, R4, 10),
			BPF_ALU64_REG(BPF_SUB, R5, R0),
			BPF_ALU64_REG(BPF_SUB, R5, R1),
			BPF_ALU64_REG(BPF_SUB, R5, R2),
			BPF_ALU64_REG(BPF_SUB, R5, R3),
			BPF_ALU64_REG(BPF_SUB, R5, R4),
			BPF_ALU64_REG(BPF_SUB, R5, R6),
			BPF_ALU64_REG(BPF_SUB, R5, R7),
			BPF_ALU64_REG(BPF_SUB, R5, R8),
			BPF_ALU64_REG(BPF_SUB, R5, R9),
			BPF_ALU64_IMM(BPF_SUB, R5, 10),
			BPF_ALU64_REG(BPF_SUB, R6, R0),
			BPF_ALU64_REG(BPF_SUB, R6, R1),
			BPF_ALU64_REG(BPF_SUB, R6, R2),
			BPF_ALU64_REG(BPF_SUB, R6, R3),
			BPF_ALU64_REG(BPF_SUB, R6, R4),
			BPF_ALU64_REG(BPF_SUB, R6, R5),
			BPF_ALU64_REG(BPF_SUB, R6, R7),
			BPF_ALU64_REG(BPF_SUB, R6, R8),
			BPF_ALU64_REG(BPF_SUB, R6, R9),
			BPF_ALU64_IMM(BPF_SUB, R6, 10),
			BPF_ALU64_REG(BPF_SUB, R7, R0),
			BPF_ALU64_REG(BPF_SUB, R7, R1),
			BPF_ALU64_REG(BPF_SUB, R7, R2),
			BPF_ALU64_REG(BPF_SUB, R7, R3),
			BPF_ALU64_REG(BPF_SUB, R7, R4),
			BPF_ALU64_REG(BPF_SUB, R7, R5),
			BPF_ALU64_REG(BPF_SUB, R7, R6),
			BPF_ALU64_REG(BPF_SUB, R7, R8),
			BPF_ALU64_REG(BPF_SUB, R7, R9),
			BPF_ALU64_IMM(BPF_SUB, R7, 10),
			BPF_ALU64_REG(BPF_SUB, R8, R0),
			BPF_ALU64_REG(BPF_SUB, R8, R1),
			BPF_ALU64_REG(BPF_SUB, R8, R2),
			BPF_ALU64_REG(BPF_SUB, R8, R3),
			BPF_ALU64_REG(BPF_SUB, R8, R4),
			BPF_ALU64_REG(BPF_SUB, R8, R5),
			BPF_ALU64_REG(BPF_SUB, R8, R6),
			BPF_ALU64_REG(BPF_SUB, R8, R7),
			BPF_ALU64_REG(BPF_SUB, R8, R9),
			BPF_ALU64_IMM(BPF_SUB, R8, 10),
			BPF_ALU64_REG(BPF_SUB, R9, R0),
			BPF_ALU64_REG(BPF_SUB, R9, R1),
			BPF_ALU64_REG(BPF_SUB, R9, R2),
			BPF_ALU64_REG(BPF_SUB, R9, R3),
			BPF_ALU64_REG(BPF_SUB, R9, R4),
			BPF_ALU64_REG(BPF_SUB, R9, R5),
			BPF_ALU64_REG(BPF_SUB, R9, R6),
			BPF_ALU64_REG(BPF_SUB, R9, R7),
			BPF_ALU64_REG(BPF_SUB, R9, R8),
			BPF_ALU64_IMM(BPF_SUB, R9, 10),
			BPF_ALU64_IMM(BPF_SUB, R0, 10),
			BPF_ALU64_IMM(BPF_NEG, R0, 0),
			BPF_ALU64_REG(BPF_SUB, R0, R1),
			BPF_ALU64_REG(BPF_SUB, R0, R2),
			BPF_ALU64_REG(BPF_SUB, R0, R3),
			BPF_ALU64_REG(BPF_SUB, R0, R4),
			BPF_ALU64_REG(BPF_SUB, R0, R5),
			BPF_ALU64_REG(BPF_SUB, R0, R6),
			BPF_ALU64_REG(BPF_SUB, R0, R7),
			BPF_ALU64_REG(BPF_SUB, R0, R8),
			BPF_ALU64_REG(BPF_SUB, R0, R9),
			BPF_EXIT_INSN(),
		पूर्ण,
		INTERNAL,
		अणु पूर्ण,
		अणु अणु 0, 11 पूर्ण पूर्ण
	पूर्ण,
	अणु	/* Mainly checking JIT here. */
		"INT: XOR",
		.u.insns_पूर्णांक = अणु
			BPF_ALU64_REG(BPF_SUB, R0, R0),
			BPF_ALU64_REG(BPF_XOR, R1, R1),
			BPF_JMP_REG(BPF_JEQ, R0, R1, 1),
			BPF_EXIT_INSN(),
			BPF_ALU64_IMM(BPF_MOV, R0, 10),
			BPF_ALU64_IMM(BPF_MOV, R1, -1),
			BPF_ALU64_REG(BPF_SUB, R1, R1),
			BPF_ALU64_REG(BPF_XOR, R2, R2),
			BPF_JMP_REG(BPF_JEQ, R1, R2, 1),
			BPF_EXIT_INSN(),
			BPF_ALU64_REG(BPF_SUB, R2, R2),
			BPF_ALU64_REG(BPF_XOR, R3, R3),
			BPF_ALU64_IMM(BPF_MOV, R0, 10),
			BPF_ALU64_IMM(BPF_MOV, R1, -1),
			BPF_JMP_REG(BPF_JEQ, R2, R3, 1),
			BPF_EXIT_INSN(),
			BPF_ALU64_REG(BPF_SUB, R3, R3),
			BPF_ALU64_REG(BPF_XOR, R4, R4),
			BPF_ALU64_IMM(BPF_MOV, R2, 1),
			BPF_ALU64_IMM(BPF_MOV, R5, -1),
			BPF_JMP_REG(BPF_JEQ, R3, R4, 1),
			BPF_EXIT_INSN(),
			BPF_ALU64_REG(BPF_SUB, R4, R4),
			BPF_ALU64_REG(BPF_XOR, R5, R5),
			BPF_ALU64_IMM(BPF_MOV, R3, 1),
			BPF_ALU64_IMM(BPF_MOV, R7, -1),
			BPF_JMP_REG(BPF_JEQ, R5, R4, 1),
			BPF_EXIT_INSN(),
			BPF_ALU64_IMM(BPF_MOV, R5, 1),
			BPF_ALU64_REG(BPF_SUB, R5, R5),
			BPF_ALU64_REG(BPF_XOR, R6, R6),
			BPF_ALU64_IMM(BPF_MOV, R1, 1),
			BPF_ALU64_IMM(BPF_MOV, R8, -1),
			BPF_JMP_REG(BPF_JEQ, R5, R6, 1),
			BPF_EXIT_INSN(),
			BPF_ALU64_REG(BPF_SUB, R6, R6),
			BPF_ALU64_REG(BPF_XOR, R7, R7),
			BPF_JMP_REG(BPF_JEQ, R7, R6, 1),
			BPF_EXIT_INSN(),
			BPF_ALU64_REG(BPF_SUB, R7, R7),
			BPF_ALU64_REG(BPF_XOR, R8, R8),
			BPF_JMP_REG(BPF_JEQ, R7, R8, 1),
			BPF_EXIT_INSN(),
			BPF_ALU64_REG(BPF_SUB, R8, R8),
			BPF_ALU64_REG(BPF_XOR, R9, R9),
			BPF_JMP_REG(BPF_JEQ, R9, R8, 1),
			BPF_EXIT_INSN(),
			BPF_ALU64_REG(BPF_SUB, R9, R9),
			BPF_ALU64_REG(BPF_XOR, R0, R0),
			BPF_JMP_REG(BPF_JEQ, R9, R0, 1),
			BPF_EXIT_INSN(),
			BPF_ALU64_REG(BPF_SUB, R1, R1),
			BPF_ALU64_REG(BPF_XOR, R0, R0),
			BPF_JMP_REG(BPF_JEQ, R9, R0, 2),
			BPF_ALU64_IMM(BPF_MOV, R0, 0),
			BPF_EXIT_INSN(),
			BPF_ALU64_IMM(BPF_MOV, R0, 1),
			BPF_EXIT_INSN(),
		पूर्ण,
		INTERNAL,
		अणु पूर्ण,
		अणु अणु 0, 1 पूर्ण पूर्ण
	पूर्ण,
	अणु	/* Mainly checking JIT here. */
		"INT: MUL",
		.u.insns_पूर्णांक = अणु
			BPF_ALU64_IMM(BPF_MOV, R0, 11),
			BPF_ALU64_IMM(BPF_MOV, R1, 1),
			BPF_ALU64_IMM(BPF_MOV, R2, 2),
			BPF_ALU64_IMM(BPF_MOV, R3, 3),
			BPF_ALU64_IMM(BPF_MOV, R4, 4),
			BPF_ALU64_IMM(BPF_MOV, R5, 5),
			BPF_ALU64_IMM(BPF_MOV, R6, 6),
			BPF_ALU64_IMM(BPF_MOV, R7, 7),
			BPF_ALU64_IMM(BPF_MOV, R8, 8),
			BPF_ALU64_IMM(BPF_MOV, R9, 9),
			BPF_ALU64_REG(BPF_MUL, R0, R0),
			BPF_ALU64_REG(BPF_MUL, R0, R1),
			BPF_ALU64_REG(BPF_MUL, R0, R2),
			BPF_ALU64_REG(BPF_MUL, R0, R3),
			BPF_ALU64_REG(BPF_MUL, R0, R4),
			BPF_ALU64_REG(BPF_MUL, R0, R5),
			BPF_ALU64_REG(BPF_MUL, R0, R6),
			BPF_ALU64_REG(BPF_MUL, R0, R7),
			BPF_ALU64_REG(BPF_MUL, R0, R8),
			BPF_ALU64_REG(BPF_MUL, R0, R9),
			BPF_ALU64_IMM(BPF_MUL, R0, 10),
			BPF_JMP_IMM(BPF_JEQ, R0, 439084800, 1),
			BPF_EXIT_INSN(),
			BPF_ALU64_REG(BPF_MUL, R1, R0),
			BPF_ALU64_REG(BPF_MUL, R1, R2),
			BPF_ALU64_REG(BPF_MUL, R1, R3),
			BPF_ALU64_REG(BPF_MUL, R1, R4),
			BPF_ALU64_REG(BPF_MUL, R1, R5),
			BPF_ALU64_REG(BPF_MUL, R1, R6),
			BPF_ALU64_REG(BPF_MUL, R1, R7),
			BPF_ALU64_REG(BPF_MUL, R1, R8),
			BPF_ALU64_REG(BPF_MUL, R1, R9),
			BPF_ALU64_IMM(BPF_MUL, R1, 10),
			BPF_ALU64_REG(BPF_MOV, R2, R1),
			BPF_ALU64_IMM(BPF_RSH, R2, 32),
			BPF_JMP_IMM(BPF_JEQ, R2, 0x5a924, 1),
			BPF_EXIT_INSN(),
			BPF_ALU64_IMM(BPF_LSH, R1, 32),
			BPF_ALU64_IMM(BPF_ARSH, R1, 32),
			BPF_JMP_IMM(BPF_JEQ, R1, 0xebb90000, 1),
			BPF_EXIT_INSN(),
			BPF_ALU64_REG(BPF_MUL, R2, R0),
			BPF_ALU64_REG(BPF_MUL, R2, R1),
			BPF_ALU64_REG(BPF_MUL, R2, R3),
			BPF_ALU64_REG(BPF_MUL, R2, R4),
			BPF_ALU64_REG(BPF_MUL, R2, R5),
			BPF_ALU64_REG(BPF_MUL, R2, R6),
			BPF_ALU64_REG(BPF_MUL, R2, R7),
			BPF_ALU64_REG(BPF_MUL, R2, R8),
			BPF_ALU64_REG(BPF_MUL, R2, R9),
			BPF_ALU64_IMM(BPF_MUL, R2, 10),
			BPF_ALU64_IMM(BPF_RSH, R2, 32),
			BPF_ALU64_REG(BPF_MOV, R0, R2),
			BPF_EXIT_INSN(),
		पूर्ण,
		INTERNAL,
		अणु पूर्ण,
		अणु अणु 0, 0x35d97ef2 पूर्ण पूर्ण
	पूर्ण,
	अणु	/* Mainly checking JIT here. */
		"MOV REG64",
		.u.insns_पूर्णांक = अणु
			BPF_LD_IMM64(R0, 0xffffffffffffffffLL),
			BPF_MOV64_REG(R1, R0),
			BPF_MOV64_REG(R2, R1),
			BPF_MOV64_REG(R3, R2),
			BPF_MOV64_REG(R4, R3),
			BPF_MOV64_REG(R5, R4),
			BPF_MOV64_REG(R6, R5),
			BPF_MOV64_REG(R7, R6),
			BPF_MOV64_REG(R8, R7),
			BPF_MOV64_REG(R9, R8),
			BPF_ALU64_IMM(BPF_MOV, R0, 0),
			BPF_ALU64_IMM(BPF_MOV, R1, 0),
			BPF_ALU64_IMM(BPF_MOV, R2, 0),
			BPF_ALU64_IMM(BPF_MOV, R3, 0),
			BPF_ALU64_IMM(BPF_MOV, R4, 0),
			BPF_ALU64_IMM(BPF_MOV, R5, 0),
			BPF_ALU64_IMM(BPF_MOV, R6, 0),
			BPF_ALU64_IMM(BPF_MOV, R7, 0),
			BPF_ALU64_IMM(BPF_MOV, R8, 0),
			BPF_ALU64_IMM(BPF_MOV, R9, 0),
			BPF_ALU64_REG(BPF_ADD, R0, R0),
			BPF_ALU64_REG(BPF_ADD, R0, R1),
			BPF_ALU64_REG(BPF_ADD, R0, R2),
			BPF_ALU64_REG(BPF_ADD, R0, R3),
			BPF_ALU64_REG(BPF_ADD, R0, R4),
			BPF_ALU64_REG(BPF_ADD, R0, R5),
			BPF_ALU64_REG(BPF_ADD, R0, R6),
			BPF_ALU64_REG(BPF_ADD, R0, R7),
			BPF_ALU64_REG(BPF_ADD, R0, R8),
			BPF_ALU64_REG(BPF_ADD, R0, R9),
			BPF_ALU64_IMM(BPF_ADD, R0, 0xfefe),
			BPF_EXIT_INSN(),
		पूर्ण,
		INTERNAL,
		अणु पूर्ण,
		अणु अणु 0, 0xfefe पूर्ण पूर्ण
	पूर्ण,
	अणु	/* Mainly checking JIT here. */
		"MOV REG32",
		.u.insns_पूर्णांक = अणु
			BPF_LD_IMM64(R0, 0xffffffffffffffffLL),
			BPF_MOV64_REG(R1, R0),
			BPF_MOV64_REG(R2, R1),
			BPF_MOV64_REG(R3, R2),
			BPF_MOV64_REG(R4, R3),
			BPF_MOV64_REG(R5, R4),
			BPF_MOV64_REG(R6, R5),
			BPF_MOV64_REG(R7, R6),
			BPF_MOV64_REG(R8, R7),
			BPF_MOV64_REG(R9, R8),
			BPF_ALU32_IMM(BPF_MOV, R0, 0),
			BPF_ALU32_IMM(BPF_MOV, R1, 0),
			BPF_ALU32_IMM(BPF_MOV, R2, 0),
			BPF_ALU32_IMM(BPF_MOV, R3, 0),
			BPF_ALU32_IMM(BPF_MOV, R4, 0),
			BPF_ALU32_IMM(BPF_MOV, R5, 0),
			BPF_ALU32_IMM(BPF_MOV, R6, 0),
			BPF_ALU32_IMM(BPF_MOV, R7, 0),
			BPF_ALU32_IMM(BPF_MOV, R8, 0),
			BPF_ALU32_IMM(BPF_MOV, R9, 0),
			BPF_ALU64_REG(BPF_ADD, R0, R0),
			BPF_ALU64_REG(BPF_ADD, R0, R1),
			BPF_ALU64_REG(BPF_ADD, R0, R2),
			BPF_ALU64_REG(BPF_ADD, R0, R3),
			BPF_ALU64_REG(BPF_ADD, R0, R4),
			BPF_ALU64_REG(BPF_ADD, R0, R5),
			BPF_ALU64_REG(BPF_ADD, R0, R6),
			BPF_ALU64_REG(BPF_ADD, R0, R7),
			BPF_ALU64_REG(BPF_ADD, R0, R8),
			BPF_ALU64_REG(BPF_ADD, R0, R9),
			BPF_ALU64_IMM(BPF_ADD, R0, 0xfefe),
			BPF_EXIT_INSN(),
		पूर्ण,
		INTERNAL,
		अणु पूर्ण,
		अणु अणु 0, 0xfefe पूर्ण पूर्ण
	पूर्ण,
	अणु	/* Mainly checking JIT here. */
		"LD IMM64",
		.u.insns_पूर्णांक = अणु
			BPF_LD_IMM64(R0, 0xffffffffffffffffLL),
			BPF_MOV64_REG(R1, R0),
			BPF_MOV64_REG(R2, R1),
			BPF_MOV64_REG(R3, R2),
			BPF_MOV64_REG(R4, R3),
			BPF_MOV64_REG(R5, R4),
			BPF_MOV64_REG(R6, R5),
			BPF_MOV64_REG(R7, R6),
			BPF_MOV64_REG(R8, R7),
			BPF_MOV64_REG(R9, R8),
			BPF_LD_IMM64(R0, 0x0LL),
			BPF_LD_IMM64(R1, 0x0LL),
			BPF_LD_IMM64(R2, 0x0LL),
			BPF_LD_IMM64(R3, 0x0LL),
			BPF_LD_IMM64(R4, 0x0LL),
			BPF_LD_IMM64(R5, 0x0LL),
			BPF_LD_IMM64(R6, 0x0LL),
			BPF_LD_IMM64(R7, 0x0LL),
			BPF_LD_IMM64(R8, 0x0LL),
			BPF_LD_IMM64(R9, 0x0LL),
			BPF_ALU64_REG(BPF_ADD, R0, R0),
			BPF_ALU64_REG(BPF_ADD, R0, R1),
			BPF_ALU64_REG(BPF_ADD, R0, R2),
			BPF_ALU64_REG(BPF_ADD, R0, R3),
			BPF_ALU64_REG(BPF_ADD, R0, R4),
			BPF_ALU64_REG(BPF_ADD, R0, R5),
			BPF_ALU64_REG(BPF_ADD, R0, R6),
			BPF_ALU64_REG(BPF_ADD, R0, R7),
			BPF_ALU64_REG(BPF_ADD, R0, R8),
			BPF_ALU64_REG(BPF_ADD, R0, R9),
			BPF_ALU64_IMM(BPF_ADD, R0, 0xfefe),
			BPF_EXIT_INSN(),
		पूर्ण,
		INTERNAL,
		अणु पूर्ण,
		अणु अणु 0, 0xfefe पूर्ण पूर्ण
	पूर्ण,
	अणु
		"INT: ALU MIX",
		.u.insns_पूर्णांक = अणु
			BPF_ALU64_IMM(BPF_MOV, R0, 11),
			BPF_ALU64_IMM(BPF_ADD, R0, -1),
			BPF_ALU64_IMM(BPF_MOV, R2, 2),
			BPF_ALU64_IMM(BPF_XOR, R2, 3),
			BPF_ALU64_REG(BPF_DIV, R0, R2),
			BPF_JMP_IMM(BPF_JEQ, R0, 10, 1),
			BPF_EXIT_INSN(),
			BPF_ALU64_IMM(BPF_MOD, R0, 3),
			BPF_JMP_IMM(BPF_JEQ, R0, 1, 1),
			BPF_EXIT_INSN(),
			BPF_ALU64_IMM(BPF_MOV, R0, -1),
			BPF_EXIT_INSN(),
		पूर्ण,
		INTERNAL,
		अणु पूर्ण,
		अणु अणु 0, -1 पूर्ण पूर्ण
	पूर्ण,
	अणु
		"INT: shifts by register",
		.u.insns_पूर्णांक = अणु
			BPF_MOV64_IMM(R0, -1234),
			BPF_MOV64_IMM(R1, 1),
			BPF_ALU32_REG(BPF_RSH, R0, R1),
			BPF_JMP_IMM(BPF_JEQ, R0, 0x7ffffd97, 1),
			BPF_EXIT_INSN(),
			BPF_MOV64_IMM(R2, 1),
			BPF_ALU64_REG(BPF_LSH, R0, R2),
			BPF_MOV32_IMM(R4, -1234),
			BPF_JMP_REG(BPF_JEQ, R0, R4, 1),
			BPF_EXIT_INSN(),
			BPF_ALU64_IMM(BPF_AND, R4, 63),
			BPF_ALU64_REG(BPF_LSH, R0, R4), /* R0 <= 46 */
			BPF_MOV64_IMM(R3, 47),
			BPF_ALU64_REG(BPF_ARSH, R0, R3),
			BPF_JMP_IMM(BPF_JEQ, R0, -617, 1),
			BPF_EXIT_INSN(),
			BPF_MOV64_IMM(R2, 1),
			BPF_ALU64_REG(BPF_LSH, R4, R2), /* R4 = 46 << 1 */
			BPF_JMP_IMM(BPF_JEQ, R4, 92, 1),
			BPF_EXIT_INSN(),
			BPF_MOV64_IMM(R4, 4),
			BPF_ALU64_REG(BPF_LSH, R4, R4), /* R4 = 4 << 4 */
			BPF_JMP_IMM(BPF_JEQ, R4, 64, 1),
			BPF_EXIT_INSN(),
			BPF_MOV64_IMM(R4, 5),
			BPF_ALU32_REG(BPF_LSH, R4, R4), /* R4 = 5 << 5 */
			BPF_JMP_IMM(BPF_JEQ, R4, 160, 1),
			BPF_EXIT_INSN(),
			BPF_MOV64_IMM(R0, -1),
			BPF_EXIT_INSN(),
		पूर्ण,
		INTERNAL,
		अणु पूर्ण,
		अणु अणु 0, -1 पूर्ण पूर्ण
	पूर्ण,
	अणु
		"check: missing ret",
		.u.insns = अणु
			BPF_STMT(BPF_LD | BPF_IMM, 1),
		पूर्ण,
		CLASSIC | FLAG_NO_DATA | FLAG_EXPECTED_FAIL,
		अणु पूर्ण,
		अणु पूर्ण,
		.fill_helper = शून्य,
		.expected_errcode = -EINVAL,
	पूर्ण,
	अणु
		"check: div_k_0",
		.u.insns = अणु
			BPF_STMT(BPF_ALU | BPF_DIV | BPF_K, 0),
			BPF_STMT(BPF_RET | BPF_K, 0)
		पूर्ण,
		CLASSIC | FLAG_NO_DATA | FLAG_EXPECTED_FAIL,
		अणु पूर्ण,
		अणु पूर्ण,
		.fill_helper = शून्य,
		.expected_errcode = -EINVAL,
	पूर्ण,
	अणु
		"check: unknown insn",
		.u.insns = अणु
			/* seccomp insn, rejected in socket filter */
			BPF_STMT(BPF_LDX | BPF_W | BPF_ABS, 0),
			BPF_STMT(BPF_RET | BPF_K, 0)
		पूर्ण,
		CLASSIC | FLAG_EXPECTED_FAIL,
		अणु पूर्ण,
		अणु पूर्ण,
		.fill_helper = शून्य,
		.expected_errcode = -EINVAL,
	पूर्ण,
	अणु
		"check: out of range spill/fill",
		.u.insns = अणु
			BPF_STMT(BPF_STX, 16),
			BPF_STMT(BPF_RET | BPF_K, 0)
		पूर्ण,
		CLASSIC | FLAG_NO_DATA | FLAG_EXPECTED_FAIL,
		अणु पूर्ण,
		अणु पूर्ण,
		.fill_helper = शून्य,
		.expected_errcode = -EINVAL,
	पूर्ण,
	अणु
		"JUMPS + HOLES",
		.u.insns = अणु
			BPF_STMT(BPF_LD | BPF_H | BPF_ABS, 0),
			BPF_JUMP(BPF_JMP | BPF_JGE, 0, 13, 15),
			BPF_STMT(BPF_LD | BPF_H | BPF_ABS, 0),
			BPF_STMT(BPF_LD | BPF_H | BPF_ABS, 0),
			BPF_STMT(BPF_LD | BPF_H | BPF_ABS, 0),
			BPF_STMT(BPF_LD | BPF_H | BPF_ABS, 0),
			BPF_STMT(BPF_LD | BPF_H | BPF_ABS, 0),
			BPF_STMT(BPF_LD | BPF_H | BPF_ABS, 0),
			BPF_STMT(BPF_LD | BPF_H | BPF_ABS, 0),
			BPF_STMT(BPF_LD | BPF_H | BPF_ABS, 0),
			BPF_STMT(BPF_LD | BPF_H | BPF_ABS, 0),
			BPF_STMT(BPF_LD | BPF_H | BPF_ABS, 0),
			BPF_STMT(BPF_LD | BPF_H | BPF_ABS, 0),
			BPF_STMT(BPF_LD | BPF_H | BPF_ABS, 0),
			BPF_STMT(BPF_LD | BPF_H | BPF_ABS, 0),
			BPF_JUMP(BPF_JMP | BPF_JEQ, 0x90c2894d, 3, 4),
			BPF_STMT(BPF_LD | BPF_H | BPF_ABS, 0),
			BPF_JUMP(BPF_JMP | BPF_JEQ, 0x90c2894d, 1, 2),
			BPF_STMT(BPF_LD | BPF_H | BPF_ABS, 0),
			BPF_JUMP(BPF_JMP | BPF_JGE, 0, 14, 15),
			BPF_JUMP(BPF_JMP | BPF_JGE, 0, 13, 14),
			BPF_STMT(BPF_LD | BPF_H | BPF_ABS, 0),
			BPF_STMT(BPF_LD | BPF_H | BPF_ABS, 0),
			BPF_STMT(BPF_LD | BPF_H | BPF_ABS, 0),
			BPF_STMT(BPF_LD | BPF_H | BPF_ABS, 0),
			BPF_STMT(BPF_LD | BPF_H | BPF_ABS, 0),
			BPF_STMT(BPF_LD | BPF_H | BPF_ABS, 0),
			BPF_STMT(BPF_LD | BPF_H | BPF_ABS, 0),
			BPF_STMT(BPF_LD | BPF_H | BPF_ABS, 0),
			BPF_STMT(BPF_LD | BPF_H | BPF_ABS, 0),
			BPF_STMT(BPF_LD | BPF_H | BPF_ABS, 0),
			BPF_STMT(BPF_LD | BPF_H | BPF_ABS, 0),
			BPF_STMT(BPF_LD | BPF_H | BPF_ABS, 0),
			BPF_STMT(BPF_LD | BPF_H | BPF_ABS, 0),
			BPF_JUMP(BPF_JMP | BPF_JEQ, 0x2ac28349, 2, 3),
			BPF_JUMP(BPF_JMP | BPF_JEQ, 0x2ac28349, 1, 2),
			BPF_STMT(BPF_LD | BPF_H | BPF_ABS, 0),
			BPF_JUMP(BPF_JMP | BPF_JGE, 0, 14, 15),
			BPF_JUMP(BPF_JMP | BPF_JGE, 0, 13, 14),
			BPF_STMT(BPF_LD | BPF_H | BPF_ABS, 0),
			BPF_STMT(BPF_LD | BPF_H | BPF_ABS, 0),
			BPF_STMT(BPF_LD | BPF_H | BPF_ABS, 0),
			BPF_STMT(BPF_LD | BPF_H | BPF_ABS, 0),
			BPF_STMT(BPF_LD | BPF_H | BPF_ABS, 0),
			BPF_STMT(BPF_LD | BPF_H | BPF_ABS, 0),
			BPF_STMT(BPF_LD | BPF_H | BPF_ABS, 0),
			BPF_STMT(BPF_LD | BPF_H | BPF_ABS, 0),
			BPF_STMT(BPF_LD | BPF_H | BPF_ABS, 0),
			BPF_STMT(BPF_LD | BPF_H | BPF_ABS, 0),
			BPF_STMT(BPF_LD | BPF_H | BPF_ABS, 0),
			BPF_STMT(BPF_LD | BPF_H | BPF_ABS, 0),
			BPF_STMT(BPF_LD | BPF_H | BPF_ABS, 0),
			BPF_JUMP(BPF_JMP | BPF_JEQ, 0x90d2ff41, 2, 3),
			BPF_JUMP(BPF_JMP | BPF_JEQ, 0x90d2ff41, 1, 2),
			BPF_STMT(BPF_LD | BPF_H | BPF_ABS, 0),
			BPF_STMT(BPF_RET | BPF_A, 0),
			BPF_STMT(BPF_RET | BPF_A, 0),
		पूर्ण,
		CLASSIC,
		अणु 0x00, 0x1b, 0x21, 0x3c, 0x9d, 0xf8,
		  0x90, 0xe2, 0xba, 0x0a, 0x56, 0xb4,
		  0x08, 0x00,
		  0x45, 0x00, 0x00, 0x28, 0x00, 0x00,
		  0x20, 0x00, 0x40, 0x11, 0x00, 0x00, /* IP header */
		  0xc0, 0xa8, 0x33, 0x01,
		  0xc0, 0xa8, 0x33, 0x02,
		  0xbb, 0xb6,
		  0xa9, 0xfa,
		  0x00, 0x14, 0x00, 0x00,
		  0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc,
		  0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc,
		  0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc,
		  0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc,
		  0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc,
		  0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc,
		  0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc,
		  0xcc, 0xcc, 0xcc, 0xcc पूर्ण,
		अणु अणु 88, 0x001b पूर्ण पूर्ण
	पूर्ण,
	अणु
		"check: RET X",
		.u.insns = अणु
			BPF_STMT(BPF_RET | BPF_X, 0),
		पूर्ण,
		CLASSIC | FLAG_NO_DATA | FLAG_EXPECTED_FAIL,
		अणु पूर्ण,
		अणु पूर्ण,
		.fill_helper = शून्य,
		.expected_errcode = -EINVAL,
	पूर्ण,
	अणु
		"check: LDX + RET X",
		.u.insns = अणु
			BPF_STMT(BPF_LDX | BPF_IMM, 42),
			BPF_STMT(BPF_RET | BPF_X, 0),
		पूर्ण,
		CLASSIC | FLAG_NO_DATA | FLAG_EXPECTED_FAIL,
		अणु पूर्ण,
		अणु पूर्ण,
		.fill_helper = शून्य,
		.expected_errcode = -EINVAL,
	पूर्ण,
	अणु	/* Mainly checking JIT here. */
		"M[]: alt STX + LDX",
		.u.insns = अणु
			BPF_STMT(BPF_LDX | BPF_IMM, 100),
			BPF_STMT(BPF_STX, 0),
			BPF_STMT(BPF_LDX | BPF_MEM, 0),
			BPF_STMT(BPF_MISC | BPF_TXA, 0),
			BPF_STMT(BPF_ALU | BPF_ADD | BPF_K, 1),
			BPF_STMT(BPF_MISC | BPF_TAX, 0),
			BPF_STMT(BPF_STX, 1),
			BPF_STMT(BPF_LDX | BPF_MEM, 1),
			BPF_STMT(BPF_MISC | BPF_TXA, 0),
			BPF_STMT(BPF_ALU | BPF_ADD | BPF_K, 1),
			BPF_STMT(BPF_MISC | BPF_TAX, 0),
			BPF_STMT(BPF_STX, 2),
			BPF_STMT(BPF_LDX | BPF_MEM, 2),
			BPF_STMT(BPF_MISC | BPF_TXA, 0),
			BPF_STMT(BPF_ALU | BPF_ADD | BPF_K, 1),
			BPF_STMT(BPF_MISC | BPF_TAX, 0),
			BPF_STMT(BPF_STX, 3),
			BPF_STMT(BPF_LDX | BPF_MEM, 3),
			BPF_STMT(BPF_MISC | BPF_TXA, 0),
			BPF_STMT(BPF_ALU | BPF_ADD | BPF_K, 1),
			BPF_STMT(BPF_MISC | BPF_TAX, 0),
			BPF_STMT(BPF_STX, 4),
			BPF_STMT(BPF_LDX | BPF_MEM, 4),
			BPF_STMT(BPF_MISC | BPF_TXA, 0),
			BPF_STMT(BPF_ALU | BPF_ADD | BPF_K, 1),
			BPF_STMT(BPF_MISC | BPF_TAX, 0),
			BPF_STMT(BPF_STX, 5),
			BPF_STMT(BPF_LDX | BPF_MEM, 5),
			BPF_STMT(BPF_MISC | BPF_TXA, 0),
			BPF_STMT(BPF_ALU | BPF_ADD | BPF_K, 1),
			BPF_STMT(BPF_MISC | BPF_TAX, 0),
			BPF_STMT(BPF_STX, 6),
			BPF_STMT(BPF_LDX | BPF_MEM, 6),
			BPF_STMT(BPF_MISC | BPF_TXA, 0),
			BPF_STMT(BPF_ALU | BPF_ADD | BPF_K, 1),
			BPF_STMT(BPF_MISC | BPF_TAX, 0),
			BPF_STMT(BPF_STX, 7),
			BPF_STMT(BPF_LDX | BPF_MEM, 7),
			BPF_STMT(BPF_MISC | BPF_TXA, 0),
			BPF_STMT(BPF_ALU | BPF_ADD | BPF_K, 1),
			BPF_STMT(BPF_MISC | BPF_TAX, 0),
			BPF_STMT(BPF_STX, 8),
			BPF_STMT(BPF_LDX | BPF_MEM, 8),
			BPF_STMT(BPF_MISC | BPF_TXA, 0),
			BPF_STMT(BPF_ALU | BPF_ADD | BPF_K, 1),
			BPF_STMT(BPF_MISC | BPF_TAX, 0),
			BPF_STMT(BPF_STX, 9),
			BPF_STMT(BPF_LDX | BPF_MEM, 9),
			BPF_STMT(BPF_MISC | BPF_TXA, 0),
			BPF_STMT(BPF_ALU | BPF_ADD | BPF_K, 1),
			BPF_STMT(BPF_MISC | BPF_TAX, 0),
			BPF_STMT(BPF_STX, 10),
			BPF_STMT(BPF_LDX | BPF_MEM, 10),
			BPF_STMT(BPF_MISC | BPF_TXA, 0),
			BPF_STMT(BPF_ALU | BPF_ADD | BPF_K, 1),
			BPF_STMT(BPF_MISC | BPF_TAX, 0),
			BPF_STMT(BPF_STX, 11),
			BPF_STMT(BPF_LDX | BPF_MEM, 11),
			BPF_STMT(BPF_MISC | BPF_TXA, 0),
			BPF_STMT(BPF_ALU | BPF_ADD | BPF_K, 1),
			BPF_STMT(BPF_MISC | BPF_TAX, 0),
			BPF_STMT(BPF_STX, 12),
			BPF_STMT(BPF_LDX | BPF_MEM, 12),
			BPF_STMT(BPF_MISC | BPF_TXA, 0),
			BPF_STMT(BPF_ALU | BPF_ADD | BPF_K, 1),
			BPF_STMT(BPF_MISC | BPF_TAX, 0),
			BPF_STMT(BPF_STX, 13),
			BPF_STMT(BPF_LDX | BPF_MEM, 13),
			BPF_STMT(BPF_MISC | BPF_TXA, 0),
			BPF_STMT(BPF_ALU | BPF_ADD | BPF_K, 1),
			BPF_STMT(BPF_MISC | BPF_TAX, 0),
			BPF_STMT(BPF_STX, 14),
			BPF_STMT(BPF_LDX | BPF_MEM, 14),
			BPF_STMT(BPF_MISC | BPF_TXA, 0),
			BPF_STMT(BPF_ALU | BPF_ADD | BPF_K, 1),
			BPF_STMT(BPF_MISC | BPF_TAX, 0),
			BPF_STMT(BPF_STX, 15),
			BPF_STMT(BPF_LDX | BPF_MEM, 15),
			BPF_STMT(BPF_MISC | BPF_TXA, 0),
			BPF_STMT(BPF_ALU | BPF_ADD | BPF_K, 1),
			BPF_STMT(BPF_MISC | BPF_TAX, 0),
			BPF_STMT(BPF_RET | BPF_A, 0),
		पूर्ण,
		CLASSIC | FLAG_NO_DATA,
		अणु पूर्ण,
		अणु अणु 0, 116 पूर्ण पूर्ण,
	पूर्ण,
	अणु	/* Mainly checking JIT here. */
		"M[]: full STX + full LDX",
		.u.insns = अणु
			BPF_STMT(BPF_LDX | BPF_IMM, 0xbadfeedb),
			BPF_STMT(BPF_STX, 0),
			BPF_STMT(BPF_LDX | BPF_IMM, 0xecabedae),
			BPF_STMT(BPF_STX, 1),
			BPF_STMT(BPF_LDX | BPF_IMM, 0xafccfeaf),
			BPF_STMT(BPF_STX, 2),
			BPF_STMT(BPF_LDX | BPF_IMM, 0xbffdcedc),
			BPF_STMT(BPF_STX, 3),
			BPF_STMT(BPF_LDX | BPF_IMM, 0xfbbbdccb),
			BPF_STMT(BPF_STX, 4),
			BPF_STMT(BPF_LDX | BPF_IMM, 0xfbabcbda),
			BPF_STMT(BPF_STX, 5),
			BPF_STMT(BPF_LDX | BPF_IMM, 0xaedecbdb),
			BPF_STMT(BPF_STX, 6),
			BPF_STMT(BPF_LDX | BPF_IMM, 0xadebbade),
			BPF_STMT(BPF_STX, 7),
			BPF_STMT(BPF_LDX | BPF_IMM, 0xfcfcfaec),
			BPF_STMT(BPF_STX, 8),
			BPF_STMT(BPF_LDX | BPF_IMM, 0xbcdddbdc),
			BPF_STMT(BPF_STX, 9),
			BPF_STMT(BPF_LDX | BPF_IMM, 0xfeefdfac),
			BPF_STMT(BPF_STX, 10),
			BPF_STMT(BPF_LDX | BPF_IMM, 0xcddcdeea),
			BPF_STMT(BPF_STX, 11),
			BPF_STMT(BPF_LDX | BPF_IMM, 0xaccfaebb),
			BPF_STMT(BPF_STX, 12),
			BPF_STMT(BPF_LDX | BPF_IMM, 0xbdcccdcf),
			BPF_STMT(BPF_STX, 13),
			BPF_STMT(BPF_LDX | BPF_IMM, 0xaaedecde),
			BPF_STMT(BPF_STX, 14),
			BPF_STMT(BPF_LDX | BPF_IMM, 0xfaeacdad),
			BPF_STMT(BPF_STX, 15),
			BPF_STMT(BPF_LDX | BPF_MEM, 0),
			BPF_STMT(BPF_MISC | BPF_TXA, 0),
			BPF_STMT(BPF_LDX | BPF_MEM, 1),
			BPF_STMT(BPF_ALU | BPF_ADD | BPF_X, 0),
			BPF_STMT(BPF_LDX | BPF_MEM, 2),
			BPF_STMT(BPF_ALU | BPF_ADD | BPF_X, 0),
			BPF_STMT(BPF_LDX | BPF_MEM, 3),
			BPF_STMT(BPF_ALU | BPF_ADD | BPF_X, 0),
			BPF_STMT(BPF_LDX | BPF_MEM, 4),
			BPF_STMT(BPF_ALU | BPF_ADD | BPF_X, 0),
			BPF_STMT(BPF_LDX | BPF_MEM, 5),
			BPF_STMT(BPF_ALU | BPF_ADD | BPF_X, 0),
			BPF_STMT(BPF_LDX | BPF_MEM, 6),
			BPF_STMT(BPF_ALU | BPF_ADD | BPF_X, 0),
			BPF_STMT(BPF_LDX | BPF_MEM, 7),
			BPF_STMT(BPF_ALU | BPF_ADD | BPF_X, 0),
			BPF_STMT(BPF_LDX | BPF_MEM, 8),
			BPF_STMT(BPF_ALU | BPF_ADD | BPF_X, 0),
			BPF_STMT(BPF_LDX | BPF_MEM, 9),
			BPF_STMT(BPF_ALU | BPF_ADD | BPF_X, 0),
			BPF_STMT(BPF_LDX | BPF_MEM, 10),
			BPF_STMT(BPF_ALU | BPF_ADD | BPF_X, 0),
			BPF_STMT(BPF_LDX | BPF_MEM, 11),
			BPF_STMT(BPF_ALU | BPF_ADD | BPF_X, 0),
			BPF_STMT(BPF_LDX | BPF_MEM, 12),
			BPF_STMT(BPF_ALU | BPF_ADD | BPF_X, 0),
			BPF_STMT(BPF_LDX | BPF_MEM, 13),
			BPF_STMT(BPF_ALU | BPF_ADD | BPF_X, 0),
			BPF_STMT(BPF_LDX | BPF_MEM, 14),
			BPF_STMT(BPF_ALU | BPF_ADD | BPF_X, 0),
			BPF_STMT(BPF_LDX | BPF_MEM, 15),
			BPF_STMT(BPF_ALU | BPF_ADD | BPF_X, 0),
			BPF_STMT(BPF_RET | BPF_A, 0),
		पूर्ण,
		CLASSIC | FLAG_NO_DATA,
		अणु पूर्ण,
		अणु अणु 0, 0x2a5a5e5 पूर्ण पूर्ण,
	पूर्ण,
	अणु
		"check: SKF_AD_MAX",
		.u.insns = अणु
			BPF_STMT(BPF_LD | BPF_W | BPF_ABS,
				 SKF_AD_OFF + SKF_AD_MAX),
			BPF_STMT(BPF_RET | BPF_A, 0),
		पूर्ण,
		CLASSIC | FLAG_NO_DATA | FLAG_EXPECTED_FAIL,
		अणु पूर्ण,
		अणु पूर्ण,
		.fill_helper = शून्य,
		.expected_errcode = -EINVAL,
	पूर्ण,
	अणु	/* Passes checker but fails during runसमय. */
		"LD [SKF_AD_OFF-1]",
		.u.insns = अणु
			BPF_STMT(BPF_LD | BPF_W | BPF_ABS,
				 SKF_AD_OFF - 1),
			BPF_STMT(BPF_RET | BPF_K, 1),
		पूर्ण,
		CLASSIC,
		अणु पूर्ण,
		अणु अणु 1, 0 पूर्ण पूर्ण,
	पूर्ण,
	अणु
		"load 64-bit immediate",
		.u.insns_पूर्णांक = अणु
			BPF_LD_IMM64(R1, 0x567800001234LL),
			BPF_MOV64_REG(R2, R1),
			BPF_MOV64_REG(R3, R2),
			BPF_ALU64_IMM(BPF_RSH, R2, 32),
			BPF_ALU64_IMM(BPF_LSH, R3, 32),
			BPF_ALU64_IMM(BPF_RSH, R3, 32),
			BPF_ALU64_IMM(BPF_MOV, R0, 0),
			BPF_JMP_IMM(BPF_JEQ, R2, 0x5678, 1),
			BPF_EXIT_INSN(),
			BPF_JMP_IMM(BPF_JEQ, R3, 0x1234, 1),
			BPF_EXIT_INSN(),
			BPF_LD_IMM64(R0, 0x1ffffffffLL),
			BPF_ALU64_IMM(BPF_RSH, R0, 32), /* R0 = 1 */
			BPF_EXIT_INSN(),
		पूर्ण,
		INTERNAL,
		अणु पूर्ण,
		अणु अणु 0, 1 पूर्ण पूर्ण
	पूर्ण,
	/* BPF_ALU | BPF_MOV | BPF_X */
	अणु
		"ALU_MOV_X: dst = 2",
		.u.insns_पूर्णांक = अणु
			BPF_ALU32_IMM(BPF_MOV, R1, 2),
			BPF_ALU32_REG(BPF_MOV, R0, R1),
			BPF_EXIT_INSN(),
		पूर्ण,
		INTERNAL,
		अणु पूर्ण,
		अणु अणु 0, 2 पूर्ण पूर्ण,
	पूर्ण,
	अणु
		"ALU_MOV_X: dst = 4294967295",
		.u.insns_पूर्णांक = अणु
			BPF_ALU32_IMM(BPF_MOV, R1, 4294967295U),
			BPF_ALU32_REG(BPF_MOV, R0, R1),
			BPF_EXIT_INSN(),
		पूर्ण,
		INTERNAL,
		अणु पूर्ण,
		अणु अणु 0, 4294967295U पूर्ण पूर्ण,
	पूर्ण,
	अणु
		"ALU64_MOV_X: dst = 2",
		.u.insns_पूर्णांक = अणु
			BPF_ALU32_IMM(BPF_MOV, R1, 2),
			BPF_ALU64_REG(BPF_MOV, R0, R1),
			BPF_EXIT_INSN(),
		पूर्ण,
		INTERNAL,
		अणु पूर्ण,
		अणु अणु 0, 2 पूर्ण पूर्ण,
	पूर्ण,
	अणु
		"ALU64_MOV_X: dst = 4294967295",
		.u.insns_पूर्णांक = अणु
			BPF_ALU32_IMM(BPF_MOV, R1, 4294967295U),
			BPF_ALU64_REG(BPF_MOV, R0, R1),
			BPF_EXIT_INSN(),
		पूर्ण,
		INTERNAL,
		अणु पूर्ण,
		अणु अणु 0, 4294967295U पूर्ण पूर्ण,
	पूर्ण,
	/* BPF_ALU | BPF_MOV | BPF_K */
	अणु
		"ALU_MOV_K: dst = 2",
		.u.insns_पूर्णांक = अणु
			BPF_ALU32_IMM(BPF_MOV, R0, 2),
			BPF_EXIT_INSN(),
		पूर्ण,
		INTERNAL,
		अणु पूर्ण,
		अणु अणु 0, 2 पूर्ण पूर्ण,
	पूर्ण,
	अणु
		"ALU_MOV_K: dst = 4294967295",
		.u.insns_पूर्णांक = अणु
			BPF_ALU32_IMM(BPF_MOV, R0, 4294967295U),
			BPF_EXIT_INSN(),
		पूर्ण,
		INTERNAL,
		अणु पूर्ण,
		अणु अणु 0, 4294967295U पूर्ण पूर्ण,
	पूर्ण,
	अणु
		"ALU_MOV_K: 0x0000ffffffff0000 = 0x00000000ffffffff",
		.u.insns_पूर्णांक = अणु
			BPF_LD_IMM64(R2, 0x0000ffffffff0000LL),
			BPF_LD_IMM64(R3, 0x00000000ffffffffLL),
			BPF_ALU32_IMM(BPF_MOV, R2, 0xffffffff),
			BPF_JMP_REG(BPF_JEQ, R2, R3, 2),
			BPF_MOV32_IMM(R0, 2),
			BPF_EXIT_INSN(),
			BPF_MOV32_IMM(R0, 1),
			BPF_EXIT_INSN(),
		पूर्ण,
		INTERNAL,
		अणु पूर्ण,
		अणु अणु 0, 0x1 पूर्ण पूर्ण,
	पूर्ण,
	अणु
		"ALU64_MOV_K: dst = 2",
		.u.insns_पूर्णांक = अणु
			BPF_ALU64_IMM(BPF_MOV, R0, 2),
			BPF_EXIT_INSN(),
		पूर्ण,
		INTERNAL,
		अणु पूर्ण,
		अणु अणु 0, 2 पूर्ण पूर्ण,
	पूर्ण,
	अणु
		"ALU64_MOV_K: dst = 2147483647",
		.u.insns_पूर्णांक = अणु
			BPF_ALU64_IMM(BPF_MOV, R0, 2147483647),
			BPF_EXIT_INSN(),
		पूर्ण,
		INTERNAL,
		अणु पूर्ण,
		अणु अणु 0, 2147483647 पूर्ण पूर्ण,
	पूर्ण,
	अणु
		"ALU64_OR_K: dst = 0x0",
		.u.insns_पूर्णांक = अणु
			BPF_LD_IMM64(R2, 0x0000ffffffff0000LL),
			BPF_LD_IMM64(R3, 0x0),
			BPF_ALU64_IMM(BPF_MOV, R2, 0x0),
			BPF_JMP_REG(BPF_JEQ, R2, R3, 2),
			BPF_MOV32_IMM(R0, 2),
			BPF_EXIT_INSN(),
			BPF_MOV32_IMM(R0, 1),
			BPF_EXIT_INSN(),
		पूर्ण,
		INTERNAL,
		अणु पूर्ण,
		अणु अणु 0, 0x1 पूर्ण पूर्ण,
	पूर्ण,
	अणु
		"ALU64_MOV_K: dst = -1",
		.u.insns_पूर्णांक = अणु
			BPF_LD_IMM64(R2, 0x0000ffffffff0000LL),
			BPF_LD_IMM64(R3, 0xffffffffffffffffLL),
			BPF_ALU64_IMM(BPF_MOV, R2, 0xffffffff),
			BPF_JMP_REG(BPF_JEQ, R2, R3, 2),
			BPF_MOV32_IMM(R0, 2),
			BPF_EXIT_INSN(),
			BPF_MOV32_IMM(R0, 1),
			BPF_EXIT_INSN(),
		पूर्ण,
		INTERNAL,
		अणु पूर्ण,
		अणु अणु 0, 0x1 पूर्ण पूर्ण,
	पूर्ण,
	/* BPF_ALU | BPF_ADD | BPF_X */
	अणु
		"ALU_ADD_X: 1 + 2 = 3",
		.u.insns_पूर्णांक = अणु
			BPF_LD_IMM64(R0, 1),
			BPF_ALU32_IMM(BPF_MOV, R1, 2),
			BPF_ALU32_REG(BPF_ADD, R0, R1),
			BPF_EXIT_INSN(),
		पूर्ण,
		INTERNAL,
		अणु पूर्ण,
		अणु अणु 0, 3 पूर्ण पूर्ण,
	पूर्ण,
	अणु
		"ALU_ADD_X: 1 + 4294967294 = 4294967295",
		.u.insns_पूर्णांक = अणु
			BPF_LD_IMM64(R0, 1),
			BPF_ALU32_IMM(BPF_MOV, R1, 4294967294U),
			BPF_ALU32_REG(BPF_ADD, R0, R1),
			BPF_EXIT_INSN(),
		पूर्ण,
		INTERNAL,
		अणु पूर्ण,
		अणु अणु 0, 4294967295U पूर्ण पूर्ण,
	पूर्ण,
	अणु
		"ALU_ADD_X: 2 + 4294967294 = 0",
		.u.insns_पूर्णांक = अणु
			BPF_LD_IMM64(R0, 2),
			BPF_LD_IMM64(R1, 4294967294U),
			BPF_ALU32_REG(BPF_ADD, R0, R1),
			BPF_JMP_IMM(BPF_JEQ, R0, 0, 2),
			BPF_ALU32_IMM(BPF_MOV, R0, 0),
			BPF_EXIT_INSN(),
			BPF_ALU32_IMM(BPF_MOV, R0, 1),
			BPF_EXIT_INSN(),
		पूर्ण,
		INTERNAL,
		अणु पूर्ण,
		अणु अणु 0, 1 पूर्ण पूर्ण,
	पूर्ण,
	अणु
		"ALU64_ADD_X: 1 + 2 = 3",
		.u.insns_पूर्णांक = अणु
			BPF_LD_IMM64(R0, 1),
			BPF_ALU32_IMM(BPF_MOV, R1, 2),
			BPF_ALU64_REG(BPF_ADD, R0, R1),
			BPF_EXIT_INSN(),
		पूर्ण,
		INTERNAL,
		अणु पूर्ण,
		अणु अणु 0, 3 पूर्ण पूर्ण,
	पूर्ण,
	अणु
		"ALU64_ADD_X: 1 + 4294967294 = 4294967295",
		.u.insns_पूर्णांक = अणु
			BPF_LD_IMM64(R0, 1),
			BPF_ALU32_IMM(BPF_MOV, R1, 4294967294U),
			BPF_ALU64_REG(BPF_ADD, R0, R1),
			BPF_EXIT_INSN(),
		पूर्ण,
		INTERNAL,
		अणु पूर्ण,
		अणु अणु 0, 4294967295U पूर्ण पूर्ण,
	पूर्ण,
	अणु
		"ALU64_ADD_X: 2 + 4294967294 = 4294967296",
		.u.insns_पूर्णांक = अणु
			BPF_LD_IMM64(R0, 2),
			BPF_LD_IMM64(R1, 4294967294U),
			BPF_LD_IMM64(R2, 4294967296ULL),
			BPF_ALU64_REG(BPF_ADD, R0, R1),
			BPF_JMP_REG(BPF_JEQ, R0, R2, 2),
			BPF_MOV32_IMM(R0, 0),
			BPF_EXIT_INSN(),
			BPF_MOV32_IMM(R0, 1),
			BPF_EXIT_INSN(),
		पूर्ण,
		INTERNAL,
		अणु पूर्ण,
		अणु अणु 0, 1 पूर्ण पूर्ण,
	पूर्ण,
	/* BPF_ALU | BPF_ADD | BPF_K */
	अणु
		"ALU_ADD_K: 1 + 2 = 3",
		.u.insns_पूर्णांक = अणु
			BPF_LD_IMM64(R0, 1),
			BPF_ALU32_IMM(BPF_ADD, R0, 2),
			BPF_EXIT_INSN(),
		पूर्ण,
		INTERNAL,
		अणु पूर्ण,
		अणु अणु 0, 3 पूर्ण पूर्ण,
	पूर्ण,
	अणु
		"ALU_ADD_K: 3 + 0 = 3",
		.u.insns_पूर्णांक = अणु
			BPF_LD_IMM64(R0, 3),
			BPF_ALU32_IMM(BPF_ADD, R0, 0),
			BPF_EXIT_INSN(),
		पूर्ण,
		INTERNAL,
		अणु पूर्ण,
		अणु अणु 0, 3 पूर्ण पूर्ण,
	पूर्ण,
	अणु
		"ALU_ADD_K: 1 + 4294967294 = 4294967295",
		.u.insns_पूर्णांक = अणु
			BPF_LD_IMM64(R0, 1),
			BPF_ALU32_IMM(BPF_ADD, R0, 4294967294U),
			BPF_EXIT_INSN(),
		पूर्ण,
		INTERNAL,
		अणु पूर्ण,
		अणु अणु 0, 4294967295U पूर्ण पूर्ण,
	पूर्ण,
	अणु
		"ALU_ADD_K: 4294967294 + 2 = 0",
		.u.insns_पूर्णांक = अणु
			BPF_LD_IMM64(R0, 4294967294U),
			BPF_ALU32_IMM(BPF_ADD, R0, 2),
			BPF_JMP_IMM(BPF_JEQ, R0, 0, 2),
			BPF_ALU32_IMM(BPF_MOV, R0, 0),
			BPF_EXIT_INSN(),
			BPF_ALU32_IMM(BPF_MOV, R0, 1),
			BPF_EXIT_INSN(),
		पूर्ण,
		INTERNAL,
		अणु पूर्ण,
		अणु अणु 0, 1 पूर्ण पूर्ण,
	पूर्ण,
	अणु
		"ALU_ADD_K: 0 + (-1) = 0x00000000ffffffff",
		.u.insns_पूर्णांक = अणु
			BPF_LD_IMM64(R2, 0x0),
			BPF_LD_IMM64(R3, 0x00000000ffffffff),
			BPF_ALU32_IMM(BPF_ADD, R2, 0xffffffff),
			BPF_JMP_REG(BPF_JEQ, R2, R3, 2),
			BPF_MOV32_IMM(R0, 2),
			BPF_EXIT_INSN(),
			BPF_MOV32_IMM(R0, 1),
			BPF_EXIT_INSN(),
		पूर्ण,
		INTERNAL,
		अणु पूर्ण,
		अणु अणु 0, 0x1 पूर्ण पूर्ण,
	पूर्ण,
	अणु
		"ALU_ADD_K: 0 + 0xffff = 0xffff",
		.u.insns_पूर्णांक = अणु
			BPF_LD_IMM64(R2, 0x0),
			BPF_LD_IMM64(R3, 0xffff),
			BPF_ALU32_IMM(BPF_ADD, R2, 0xffff),
			BPF_JMP_REG(BPF_JEQ, R2, R3, 2),
			BPF_MOV32_IMM(R0, 2),
			BPF_EXIT_INSN(),
			BPF_MOV32_IMM(R0, 1),
			BPF_EXIT_INSN(),
		पूर्ण,
		INTERNAL,
		अणु पूर्ण,
		अणु अणु 0, 0x1 पूर्ण पूर्ण,
	पूर्ण,
	अणु
		"ALU_ADD_K: 0 + 0x7fffffff = 0x7fffffff",
		.u.insns_पूर्णांक = अणु
			BPF_LD_IMM64(R2, 0x0),
			BPF_LD_IMM64(R3, 0x7fffffff),
			BPF_ALU32_IMM(BPF_ADD, R2, 0x7fffffff),
			BPF_JMP_REG(BPF_JEQ, R2, R3, 2),
			BPF_MOV32_IMM(R0, 2),
			BPF_EXIT_INSN(),
			BPF_MOV32_IMM(R0, 1),
			BPF_EXIT_INSN(),
		पूर्ण,
		INTERNAL,
		अणु पूर्ण,
		अणु अणु 0, 0x1 पूर्ण पूर्ण,
	पूर्ण,
	अणु
		"ALU_ADD_K: 0 + 0x80000000 = 0x80000000",
		.u.insns_पूर्णांक = अणु
			BPF_LD_IMM64(R2, 0x0),
			BPF_LD_IMM64(R3, 0x80000000),
			BPF_ALU32_IMM(BPF_ADD, R2, 0x80000000),
			BPF_JMP_REG(BPF_JEQ, R2, R3, 2),
			BPF_MOV32_IMM(R0, 2),
			BPF_EXIT_INSN(),
			BPF_MOV32_IMM(R0, 1),
			BPF_EXIT_INSN(),
		पूर्ण,
		INTERNAL,
		अणु पूर्ण,
		अणु अणु 0, 0x1 पूर्ण पूर्ण,
	पूर्ण,
	अणु
		"ALU_ADD_K: 0 + 0x80008000 = 0x80008000",
		.u.insns_पूर्णांक = अणु
			BPF_LD_IMM64(R2, 0x0),
			BPF_LD_IMM64(R3, 0x80008000),
			BPF_ALU32_IMM(BPF_ADD, R2, 0x80008000),
			BPF_JMP_REG(BPF_JEQ, R2, R3, 2),
			BPF_MOV32_IMM(R0, 2),
			BPF_EXIT_INSN(),
			BPF_MOV32_IMM(R0, 1),
			BPF_EXIT_INSN(),
		पूर्ण,
		INTERNAL,
		अणु पूर्ण,
		अणु अणु 0, 0x1 पूर्ण पूर्ण,
	पूर्ण,
	अणु
		"ALU64_ADD_K: 1 + 2 = 3",
		.u.insns_पूर्णांक = अणु
			BPF_LD_IMM64(R0, 1),
			BPF_ALU64_IMM(BPF_ADD, R0, 2),
			BPF_EXIT_INSN(),
		पूर्ण,
		INTERNAL,
		अणु पूर्ण,
		अणु अणु 0, 3 पूर्ण पूर्ण,
	पूर्ण,
	अणु
		"ALU64_ADD_K: 3 + 0 = 3",
		.u.insns_पूर्णांक = अणु
			BPF_LD_IMM64(R0, 3),
			BPF_ALU64_IMM(BPF_ADD, R0, 0),
			BPF_EXIT_INSN(),
		पूर्ण,
		INTERNAL,
		अणु पूर्ण,
		अणु अणु 0, 3 पूर्ण पूर्ण,
	पूर्ण,
	अणु
		"ALU64_ADD_K: 1 + 2147483646 = 2147483647",
		.u.insns_पूर्णांक = अणु
			BPF_LD_IMM64(R0, 1),
			BPF_ALU64_IMM(BPF_ADD, R0, 2147483646),
			BPF_EXIT_INSN(),
		पूर्ण,
		INTERNAL,
		अणु पूर्ण,
		अणु अणु 0, 2147483647 पूर्ण पूर्ण,
	पूर्ण,
	अणु
		"ALU64_ADD_K: 4294967294 + 2 = 4294967296",
		.u.insns_पूर्णांक = अणु
			BPF_LD_IMM64(R0, 4294967294U),
			BPF_LD_IMM64(R1, 4294967296ULL),
			BPF_ALU64_IMM(BPF_ADD, R0, 2),
			BPF_JMP_REG(BPF_JEQ, R0, R1, 2),
			BPF_ALU32_IMM(BPF_MOV, R0, 0),
			BPF_EXIT_INSN(),
			BPF_ALU32_IMM(BPF_MOV, R0, 1),
			BPF_EXIT_INSN(),
		पूर्ण,
		INTERNAL,
		अणु पूर्ण,
		अणु अणु 0, 1 पूर्ण पूर्ण,
	पूर्ण,
	अणु
		"ALU64_ADD_K: 2147483646 + -2147483647 = -1",
		.u.insns_पूर्णांक = अणु
			BPF_LD_IMM64(R0, 2147483646),
			BPF_ALU64_IMM(BPF_ADD, R0, -2147483647),
			BPF_EXIT_INSN(),
		पूर्ण,
		INTERNAL,
		अणु पूर्ण,
		अणु अणु 0, -1 पूर्ण पूर्ण,
	पूर्ण,
	अणु
		"ALU64_ADD_K: 1 + 0 = 1",
		.u.insns_पूर्णांक = अणु
			BPF_LD_IMM64(R2, 0x1),
			BPF_LD_IMM64(R3, 0x1),
			BPF_ALU64_IMM(BPF_ADD, R2, 0x0),
			BPF_JMP_REG(BPF_JEQ, R2, R3, 2),
			BPF_MOV32_IMM(R0, 2),
			BPF_EXIT_INSN(),
			BPF_MOV32_IMM(R0, 1),
			BPF_EXIT_INSN(),
		पूर्ण,
		INTERNAL,
		अणु पूर्ण,
		अणु अणु 0, 0x1 पूर्ण पूर्ण,
	पूर्ण,
	अणु
		"ALU64_ADD_K: 0 + (-1) = 0xffffffffffffffff",
		.u.insns_पूर्णांक = अणु
			BPF_LD_IMM64(R2, 0x0),
			BPF_LD_IMM64(R3, 0xffffffffffffffffLL),
			BPF_ALU64_IMM(BPF_ADD, R2, 0xffffffff),
			BPF_JMP_REG(BPF_JEQ, R2, R3, 2),
			BPF_MOV32_IMM(R0, 2),
			BPF_EXIT_INSN(),
			BPF_MOV32_IMM(R0, 1),
			BPF_EXIT_INSN(),
		पूर्ण,
		INTERNAL,
		अणु पूर्ण,
		अणु अणु 0, 0x1 पूर्ण पूर्ण,
	पूर्ण,
	अणु
		"ALU64_ADD_K: 0 + 0xffff = 0xffff",
		.u.insns_पूर्णांक = अणु
			BPF_LD_IMM64(R2, 0x0),
			BPF_LD_IMM64(R3, 0xffff),
			BPF_ALU64_IMM(BPF_ADD, R2, 0xffff),
			BPF_JMP_REG(BPF_JEQ, R2, R3, 2),
			BPF_MOV32_IMM(R0, 2),
			BPF_EXIT_INSN(),
			BPF_MOV32_IMM(R0, 1),
			BPF_EXIT_INSN(),
		पूर्ण,
		INTERNAL,
		अणु पूर्ण,
		अणु अणु 0, 0x1 पूर्ण पूर्ण,
	पूर्ण,
	अणु
		"ALU64_ADD_K: 0 + 0x7fffffff = 0x7fffffff",
		.u.insns_पूर्णांक = अणु
			BPF_LD_IMM64(R2, 0x0),
			BPF_LD_IMM64(R3, 0x7fffffff),
			BPF_ALU64_IMM(BPF_ADD, R2, 0x7fffffff),
			BPF_JMP_REG(BPF_JEQ, R2, R3, 2),
			BPF_MOV32_IMM(R0, 2),
			BPF_EXIT_INSN(),
			BPF_MOV32_IMM(R0, 1),
			BPF_EXIT_INSN(),
		पूर्ण,
		INTERNAL,
		अणु पूर्ण,
		अणु अणु 0, 0x1 पूर्ण पूर्ण,
	पूर्ण,
	अणु
		"ALU64_ADD_K: 0 + 0x80000000 = 0xffffffff80000000",
		.u.insns_पूर्णांक = अणु
			BPF_LD_IMM64(R2, 0x0),
			BPF_LD_IMM64(R3, 0xffffffff80000000LL),
			BPF_ALU64_IMM(BPF_ADD, R2, 0x80000000),
			BPF_JMP_REG(BPF_JEQ, R2, R3, 2),
			BPF_MOV32_IMM(R0, 2),
			BPF_EXIT_INSN(),
			BPF_MOV32_IMM(R0, 1),
			BPF_EXIT_INSN(),
		पूर्ण,
		INTERNAL,
		अणु पूर्ण,
		अणु अणु 0, 0x1 पूर्ण पूर्ण,
	पूर्ण,
	अणु
		"ALU_ADD_K: 0 + 0x80008000 = 0xffffffff80008000",
		.u.insns_पूर्णांक = अणु
			BPF_LD_IMM64(R2, 0x0),
			BPF_LD_IMM64(R3, 0xffffffff80008000LL),
			BPF_ALU64_IMM(BPF_ADD, R2, 0x80008000),
			BPF_JMP_REG(BPF_JEQ, R2, R3, 2),
			BPF_MOV32_IMM(R0, 2),
			BPF_EXIT_INSN(),
			BPF_MOV32_IMM(R0, 1),
			BPF_EXIT_INSN(),
		पूर्ण,
		INTERNAL,
		अणु पूर्ण,
		अणु अणु 0, 0x1 पूर्ण पूर्ण,
	पूर्ण,
	/* BPF_ALU | BPF_SUB | BPF_X */
	अणु
		"ALU_SUB_X: 3 - 1 = 2",
		.u.insns_पूर्णांक = अणु
			BPF_LD_IMM64(R0, 3),
			BPF_ALU32_IMM(BPF_MOV, R1, 1),
			BPF_ALU32_REG(BPF_SUB, R0, R1),
			BPF_EXIT_INSN(),
		पूर्ण,
		INTERNAL,
		अणु पूर्ण,
		अणु अणु 0, 2 पूर्ण पूर्ण,
	पूर्ण,
	अणु
		"ALU_SUB_X: 4294967295 - 4294967294 = 1",
		.u.insns_पूर्णांक = अणु
			BPF_LD_IMM64(R0, 4294967295U),
			BPF_ALU32_IMM(BPF_MOV, R1, 4294967294U),
			BPF_ALU32_REG(BPF_SUB, R0, R1),
			BPF_EXIT_INSN(),
		पूर्ण,
		INTERNAL,
		अणु पूर्ण,
		अणु अणु 0, 1 पूर्ण पूर्ण,
	पूर्ण,
	अणु
		"ALU64_SUB_X: 3 - 1 = 2",
		.u.insns_पूर्णांक = अणु
			BPF_LD_IMM64(R0, 3),
			BPF_ALU32_IMM(BPF_MOV, R1, 1),
			BPF_ALU64_REG(BPF_SUB, R0, R1),
			BPF_EXIT_INSN(),
		पूर्ण,
		INTERNAL,
		अणु पूर्ण,
		अणु अणु 0, 2 पूर्ण पूर्ण,
	पूर्ण,
	अणु
		"ALU64_SUB_X: 4294967295 - 4294967294 = 1",
		.u.insns_पूर्णांक = अणु
			BPF_LD_IMM64(R0, 4294967295U),
			BPF_ALU32_IMM(BPF_MOV, R1, 4294967294U),
			BPF_ALU64_REG(BPF_SUB, R0, R1),
			BPF_EXIT_INSN(),
		पूर्ण,
		INTERNAL,
		अणु पूर्ण,
		अणु अणु 0, 1 पूर्ण पूर्ण,
	पूर्ण,
	/* BPF_ALU | BPF_SUB | BPF_K */
	अणु
		"ALU_SUB_K: 3 - 1 = 2",
		.u.insns_पूर्णांक = अणु
			BPF_LD_IMM64(R0, 3),
			BPF_ALU32_IMM(BPF_SUB, R0, 1),
			BPF_EXIT_INSN(),
		पूर्ण,
		INTERNAL,
		अणु पूर्ण,
		अणु अणु 0, 2 पूर्ण पूर्ण,
	पूर्ण,
	अणु
		"ALU_SUB_K: 3 - 0 = 3",
		.u.insns_पूर्णांक = अणु
			BPF_LD_IMM64(R0, 3),
			BPF_ALU32_IMM(BPF_SUB, R0, 0),
			BPF_EXIT_INSN(),
		पूर्ण,
		INTERNAL,
		अणु पूर्ण,
		अणु अणु 0, 3 पूर्ण पूर्ण,
	पूर्ण,
	अणु
		"ALU_SUB_K: 4294967295 - 4294967294 = 1",
		.u.insns_पूर्णांक = अणु
			BPF_LD_IMM64(R0, 4294967295U),
			BPF_ALU32_IMM(BPF_SUB, R0, 4294967294U),
			BPF_EXIT_INSN(),
		पूर्ण,
		INTERNAL,
		अणु पूर्ण,
		अणु अणु 0, 1 पूर्ण पूर्ण,
	पूर्ण,
	अणु
		"ALU64_SUB_K: 3 - 1 = 2",
		.u.insns_पूर्णांक = अणु
			BPF_LD_IMM64(R0, 3),
			BPF_ALU64_IMM(BPF_SUB, R0, 1),
			BPF_EXIT_INSN(),
		पूर्ण,
		INTERNAL,
		अणु पूर्ण,
		अणु अणु 0, 2 पूर्ण पूर्ण,
	पूर्ण,
	अणु
		"ALU64_SUB_K: 3 - 0 = 3",
		.u.insns_पूर्णांक = अणु
			BPF_LD_IMM64(R0, 3),
			BPF_ALU64_IMM(BPF_SUB, R0, 0),
			BPF_EXIT_INSN(),
		पूर्ण,
		INTERNAL,
		अणु पूर्ण,
		अणु अणु 0, 3 पूर्ण पूर्ण,
	पूर्ण,
	अणु
		"ALU64_SUB_K: 4294967294 - 4294967295 = -1",
		.u.insns_पूर्णांक = अणु
			BPF_LD_IMM64(R0, 4294967294U),
			BPF_ALU64_IMM(BPF_SUB, R0, 4294967295U),
			BPF_EXIT_INSN(),
		पूर्ण,
		INTERNAL,
		अणु पूर्ण,
		अणु अणु 0, -1 पूर्ण पूर्ण,
	पूर्ण,
	अणु
		"ALU64_ADD_K: 2147483646 - 2147483647 = -1",
		.u.insns_पूर्णांक = अणु
			BPF_LD_IMM64(R0, 2147483646),
			BPF_ALU64_IMM(BPF_SUB, R0, 2147483647),
			BPF_EXIT_INSN(),
		पूर्ण,
		INTERNAL,
		अणु पूर्ण,
		अणु अणु 0, -1 पूर्ण पूर्ण,
	पूर्ण,
	/* BPF_ALU | BPF_MUL | BPF_X */
	अणु
		"ALU_MUL_X: 2 * 3 = 6",
		.u.insns_पूर्णांक = अणु
			BPF_LD_IMM64(R0, 2),
			BPF_ALU32_IMM(BPF_MOV, R1, 3),
			BPF_ALU32_REG(BPF_MUL, R0, R1),
			BPF_EXIT_INSN(),
		पूर्ण,
		INTERNAL,
		अणु पूर्ण,
		अणु अणु 0, 6 पूर्ण पूर्ण,
	पूर्ण,
	अणु
		"ALU_MUL_X: 2 * 0x7FFFFFF8 = 0xFFFFFFF0",
		.u.insns_पूर्णांक = अणु
			BPF_LD_IMM64(R0, 2),
			BPF_ALU32_IMM(BPF_MOV, R1, 0x7FFFFFF8),
			BPF_ALU32_REG(BPF_MUL, R0, R1),
			BPF_EXIT_INSN(),
		पूर्ण,
		INTERNAL,
		अणु पूर्ण,
		अणु अणु 0, 0xFFFFFFF0 पूर्ण पूर्ण,
	पूर्ण,
	अणु
		"ALU_MUL_X: -1 * -1 = 1",
		.u.insns_पूर्णांक = अणु
			BPF_LD_IMM64(R0, -1),
			BPF_ALU32_IMM(BPF_MOV, R1, -1),
			BPF_ALU32_REG(BPF_MUL, R0, R1),
			BPF_EXIT_INSN(),
		पूर्ण,
		INTERNAL,
		अणु पूर्ण,
		अणु अणु 0, 1 पूर्ण पूर्ण,
	पूर्ण,
	अणु
		"ALU64_MUL_X: 2 * 3 = 6",
		.u.insns_पूर्णांक = अणु
			BPF_LD_IMM64(R0, 2),
			BPF_ALU32_IMM(BPF_MOV, R1, 3),
			BPF_ALU64_REG(BPF_MUL, R0, R1),
			BPF_EXIT_INSN(),
		पूर्ण,
		INTERNAL,
		अणु पूर्ण,
		अणु अणु 0, 6 पूर्ण पूर्ण,
	पूर्ण,
	अणु
		"ALU64_MUL_X: 1 * 2147483647 = 2147483647",
		.u.insns_पूर्णांक = अणु
			BPF_LD_IMM64(R0, 1),
			BPF_ALU32_IMM(BPF_MOV, R1, 2147483647),
			BPF_ALU64_REG(BPF_MUL, R0, R1),
			BPF_EXIT_INSN(),
		पूर्ण,
		INTERNAL,
		अणु पूर्ण,
		अणु अणु 0, 2147483647 पूर्ण पूर्ण,
	पूर्ण,
	/* BPF_ALU | BPF_MUL | BPF_K */
	अणु
		"ALU_MUL_K: 2 * 3 = 6",
		.u.insns_पूर्णांक = अणु
			BPF_LD_IMM64(R0, 2),
			BPF_ALU32_IMM(BPF_MUL, R0, 3),
			BPF_EXIT_INSN(),
		पूर्ण,
		INTERNAL,
		अणु पूर्ण,
		अणु अणु 0, 6 पूर्ण पूर्ण,
	पूर्ण,
	अणु
		"ALU_MUL_K: 3 * 1 = 3",
		.u.insns_पूर्णांक = अणु
			BPF_LD_IMM64(R0, 3),
			BPF_ALU32_IMM(BPF_MUL, R0, 1),
			BPF_EXIT_INSN(),
		पूर्ण,
		INTERNAL,
		अणु पूर्ण,
		अणु अणु 0, 3 पूर्ण पूर्ण,
	पूर्ण,
	अणु
		"ALU_MUL_K: 2 * 0x7FFFFFF8 = 0xFFFFFFF0",
		.u.insns_पूर्णांक = अणु
			BPF_LD_IMM64(R0, 2),
			BPF_ALU32_IMM(BPF_MUL, R0, 0x7FFFFFF8),
			BPF_EXIT_INSN(),
		पूर्ण,
		INTERNAL,
		अणु पूर्ण,
		अणु अणु 0, 0xFFFFFFF0 पूर्ण पूर्ण,
	पूर्ण,
	अणु
		"ALU_MUL_K: 1 * (-1) = 0x00000000ffffffff",
		.u.insns_पूर्णांक = अणु
			BPF_LD_IMM64(R2, 0x1),
			BPF_LD_IMM64(R3, 0x00000000ffffffff),
			BPF_ALU32_IMM(BPF_MUL, R2, 0xffffffff),
			BPF_JMP_REG(BPF_JEQ, R2, R3, 2),
			BPF_MOV32_IMM(R0, 2),
			BPF_EXIT_INSN(),
			BPF_MOV32_IMM(R0, 1),
			BPF_EXIT_INSN(),
		पूर्ण,
		INTERNAL,
		अणु पूर्ण,
		अणु अणु 0, 0x1 पूर्ण पूर्ण,
	पूर्ण,
	अणु
		"ALU64_MUL_K: 2 * 3 = 6",
		.u.insns_पूर्णांक = अणु
			BPF_LD_IMM64(R0, 2),
			BPF_ALU64_IMM(BPF_MUL, R0, 3),
			BPF_EXIT_INSN(),
		पूर्ण,
		INTERNAL,
		अणु पूर्ण,
		अणु अणु 0, 6 पूर्ण पूर्ण,
	पूर्ण,
	अणु
		"ALU64_MUL_K: 3 * 1 = 3",
		.u.insns_पूर्णांक = अणु
			BPF_LD_IMM64(R0, 3),
			BPF_ALU64_IMM(BPF_MUL, R0, 1),
			BPF_EXIT_INSN(),
		पूर्ण,
		INTERNAL,
		अणु पूर्ण,
		अणु अणु 0, 3 पूर्ण पूर्ण,
	पूर्ण,
	अणु
		"ALU64_MUL_K: 1 * 2147483647 = 2147483647",
		.u.insns_पूर्णांक = अणु
			BPF_LD_IMM64(R0, 1),
			BPF_ALU64_IMM(BPF_MUL, R0, 2147483647),
			BPF_EXIT_INSN(),
		पूर्ण,
		INTERNAL,
		अणु पूर्ण,
		अणु अणु 0, 2147483647 पूर्ण पूर्ण,
	पूर्ण,
	अणु
		"ALU64_MUL_K: 1 * -2147483647 = -2147483647",
		.u.insns_पूर्णांक = अणु
			BPF_LD_IMM64(R0, 1),
			BPF_ALU64_IMM(BPF_MUL, R0, -2147483647),
			BPF_EXIT_INSN(),
		पूर्ण,
		INTERNAL,
		अणु पूर्ण,
		अणु अणु 0, -2147483647 पूर्ण पूर्ण,
	पूर्ण,
	अणु
		"ALU64_MUL_K: 1 * (-1) = 0xffffffffffffffff",
		.u.insns_पूर्णांक = अणु
			BPF_LD_IMM64(R2, 0x1),
			BPF_LD_IMM64(R3, 0xffffffffffffffffLL),
			BPF_ALU64_IMM(BPF_MUL, R2, 0xffffffff),
			BPF_JMP_REG(BPF_JEQ, R2, R3, 2),
			BPF_MOV32_IMM(R0, 2),
			BPF_EXIT_INSN(),
			BPF_MOV32_IMM(R0, 1),
			BPF_EXIT_INSN(),
		पूर्ण,
		INTERNAL,
		अणु पूर्ण,
		अणु अणु 0, 0x1 पूर्ण पूर्ण,
	पूर्ण,
	/* BPF_ALU | BPF_DIV | BPF_X */
	अणु
		"ALU_DIV_X: 6 / 2 = 3",
		.u.insns_पूर्णांक = अणु
			BPF_LD_IMM64(R0, 6),
			BPF_ALU32_IMM(BPF_MOV, R1, 2),
			BPF_ALU32_REG(BPF_DIV, R0, R1),
			BPF_EXIT_INSN(),
		पूर्ण,
		INTERNAL,
		अणु पूर्ण,
		अणु अणु 0, 3 पूर्ण पूर्ण,
	पूर्ण,
	अणु
		"ALU_DIV_X: 4294967295 / 4294967295 = 1",
		.u.insns_पूर्णांक = अणु
			BPF_LD_IMM64(R0, 4294967295U),
			BPF_ALU32_IMM(BPF_MOV, R1, 4294967295U),
			BPF_ALU32_REG(BPF_DIV, R0, R1),
			BPF_EXIT_INSN(),
		पूर्ण,
		INTERNAL,
		अणु पूर्ण,
		अणु अणु 0, 1 पूर्ण पूर्ण,
	पूर्ण,
	अणु
		"ALU64_DIV_X: 6 / 2 = 3",
		.u.insns_पूर्णांक = अणु
			BPF_LD_IMM64(R0, 6),
			BPF_ALU32_IMM(BPF_MOV, R1, 2),
			BPF_ALU64_REG(BPF_DIV, R0, R1),
			BPF_EXIT_INSN(),
		पूर्ण,
		INTERNAL,
		अणु पूर्ण,
		अणु अणु 0, 3 पूर्ण पूर्ण,
	पूर्ण,
	अणु
		"ALU64_DIV_X: 2147483647 / 2147483647 = 1",
		.u.insns_पूर्णांक = अणु
			BPF_LD_IMM64(R0, 2147483647),
			BPF_ALU32_IMM(BPF_MOV, R1, 2147483647),
			BPF_ALU64_REG(BPF_DIV, R0, R1),
			BPF_EXIT_INSN(),
		पूर्ण,
		INTERNAL,
		अणु पूर्ण,
		अणु अणु 0, 1 पूर्ण पूर्ण,
	पूर्ण,
	अणु
		"ALU64_DIV_X: 0xffffffffffffffff / (-1) = 0x0000000000000001",
		.u.insns_पूर्णांक = अणु
			BPF_LD_IMM64(R2, 0xffffffffffffffffLL),
			BPF_LD_IMM64(R4, 0xffffffffffffffffLL),
			BPF_LD_IMM64(R3, 0x0000000000000001LL),
			BPF_ALU64_REG(BPF_DIV, R2, R4),
			BPF_JMP_REG(BPF_JEQ, R2, R3, 2),
			BPF_MOV32_IMM(R0, 2),
			BPF_EXIT_INSN(),
			BPF_MOV32_IMM(R0, 1),
			BPF_EXIT_INSN(),
		पूर्ण,
		INTERNAL,
		अणु पूर्ण,
		अणु अणु 0, 0x1 पूर्ण पूर्ण,
	पूर्ण,
	/* BPF_ALU | BPF_DIV | BPF_K */
	अणु
		"ALU_DIV_K: 6 / 2 = 3",
		.u.insns_पूर्णांक = अणु
			BPF_LD_IMM64(R0, 6),
			BPF_ALU32_IMM(BPF_DIV, R0, 2),
			BPF_EXIT_INSN(),
		पूर्ण,
		INTERNAL,
		अणु पूर्ण,
		अणु अणु 0, 3 पूर्ण पूर्ण,
	पूर्ण,
	अणु
		"ALU_DIV_K: 3 / 1 = 3",
		.u.insns_पूर्णांक = अणु
			BPF_LD_IMM64(R0, 3),
			BPF_ALU32_IMM(BPF_DIV, R0, 1),
			BPF_EXIT_INSN(),
		पूर्ण,
		INTERNAL,
		अणु पूर्ण,
		अणु अणु 0, 3 पूर्ण पूर्ण,
	पूर्ण,
	अणु
		"ALU_DIV_K: 4294967295 / 4294967295 = 1",
		.u.insns_पूर्णांक = अणु
			BPF_LD_IMM64(R0, 4294967295U),
			BPF_ALU32_IMM(BPF_DIV, R0, 4294967295U),
			BPF_EXIT_INSN(),
		पूर्ण,
		INTERNAL,
		अणु पूर्ण,
		अणु अणु 0, 1 पूर्ण पूर्ण,
	पूर्ण,
	अणु
		"ALU_DIV_K: 0xffffffffffffffff / (-1) = 0x1",
		.u.insns_पूर्णांक = अणु
			BPF_LD_IMM64(R2, 0xffffffffffffffffLL),
			BPF_LD_IMM64(R3, 0x1UL),
			BPF_ALU32_IMM(BPF_DIV, R2, 0xffffffff),
			BPF_JMP_REG(BPF_JEQ, R2, R3, 2),
			BPF_MOV32_IMM(R0, 2),
			BPF_EXIT_INSN(),
			BPF_MOV32_IMM(R0, 1),
			BPF_EXIT_INSN(),
		पूर्ण,
		INTERNAL,
		अणु पूर्ण,
		अणु अणु 0, 0x1 पूर्ण पूर्ण,
	पूर्ण,
	अणु
		"ALU64_DIV_K: 6 / 2 = 3",
		.u.insns_पूर्णांक = अणु
			BPF_LD_IMM64(R0, 6),
			BPF_ALU64_IMM(BPF_DIV, R0, 2),
			BPF_EXIT_INSN(),
		पूर्ण,
		INTERNAL,
		अणु पूर्ण,
		अणु अणु 0, 3 पूर्ण पूर्ण,
	पूर्ण,
	अणु
		"ALU64_DIV_K: 3 / 1 = 3",
		.u.insns_पूर्णांक = अणु
			BPF_LD_IMM64(R0, 3),
			BPF_ALU64_IMM(BPF_DIV, R0, 1),
			BPF_EXIT_INSN(),
		पूर्ण,
		INTERNAL,
		अणु पूर्ण,
		अणु अणु 0, 3 पूर्ण पूर्ण,
	पूर्ण,
	अणु
		"ALU64_DIV_K: 2147483647 / 2147483647 = 1",
		.u.insns_पूर्णांक = अणु
			BPF_LD_IMM64(R0, 2147483647),
			BPF_ALU64_IMM(BPF_DIV, R0, 2147483647),
			BPF_EXIT_INSN(),
		पूर्ण,
		INTERNAL,
		अणु पूर्ण,
		अणु अणु 0, 1 पूर्ण पूर्ण,
	पूर्ण,
	अणु
		"ALU64_DIV_K: 0xffffffffffffffff / (-1) = 0x0000000000000001",
		.u.insns_पूर्णांक = अणु
			BPF_LD_IMM64(R2, 0xffffffffffffffffLL),
			BPF_LD_IMM64(R3, 0x0000000000000001LL),
			BPF_ALU64_IMM(BPF_DIV, R2, 0xffffffff),
			BPF_JMP_REG(BPF_JEQ, R2, R3, 2),
			BPF_MOV32_IMM(R0, 2),
			BPF_EXIT_INSN(),
			BPF_MOV32_IMM(R0, 1),
			BPF_EXIT_INSN(),
		पूर्ण,
		INTERNAL,
		अणु पूर्ण,
		अणु अणु 0, 0x1 पूर्ण पूर्ण,
	पूर्ण,
	/* BPF_ALU | BPF_MOD | BPF_X */
	अणु
		"ALU_MOD_X: 3 % 2 = 1",
		.u.insns_पूर्णांक = अणु
			BPF_LD_IMM64(R0, 3),
			BPF_ALU32_IMM(BPF_MOV, R1, 2),
			BPF_ALU32_REG(BPF_MOD, R0, R1),
			BPF_EXIT_INSN(),
		पूर्ण,
		INTERNAL,
		अणु पूर्ण,
		अणु अणु 0, 1 पूर्ण पूर्ण,
	पूर्ण,
	अणु
		"ALU_MOD_X: 4294967295 % 4294967293 = 2",
		.u.insns_पूर्णांक = अणु
			BPF_LD_IMM64(R0, 4294967295U),
			BPF_ALU32_IMM(BPF_MOV, R1, 4294967293U),
			BPF_ALU32_REG(BPF_MOD, R0, R1),
			BPF_EXIT_INSN(),
		पूर्ण,
		INTERNAL,
		अणु पूर्ण,
		अणु अणु 0, 2 पूर्ण पूर्ण,
	पूर्ण,
	अणु
		"ALU64_MOD_X: 3 % 2 = 1",
		.u.insns_पूर्णांक = अणु
			BPF_LD_IMM64(R0, 3),
			BPF_ALU32_IMM(BPF_MOV, R1, 2),
			BPF_ALU64_REG(BPF_MOD, R0, R1),
			BPF_EXIT_INSN(),
		पूर्ण,
		INTERNAL,
		अणु पूर्ण,
		अणु अणु 0, 1 पूर्ण पूर्ण,
	पूर्ण,
	अणु
		"ALU64_MOD_X: 2147483647 % 2147483645 = 2",
		.u.insns_पूर्णांक = अणु
			BPF_LD_IMM64(R0, 2147483647),
			BPF_ALU32_IMM(BPF_MOV, R1, 2147483645),
			BPF_ALU64_REG(BPF_MOD, R0, R1),
			BPF_EXIT_INSN(),
		पूर्ण,
		INTERNAL,
		अणु पूर्ण,
		अणु अणु 0, 2 पूर्ण पूर्ण,
	पूर्ण,
	/* BPF_ALU | BPF_MOD | BPF_K */
	अणु
		"ALU_MOD_K: 3 % 2 = 1",
		.u.insns_पूर्णांक = अणु
			BPF_LD_IMM64(R0, 3),
			BPF_ALU32_IMM(BPF_MOD, R0, 2),
			BPF_EXIT_INSN(),
		पूर्ण,
		INTERNAL,
		अणु पूर्ण,
		अणु अणु 0, 1 पूर्ण पूर्ण,
	पूर्ण,
	अणु
		"ALU_MOD_K: 3 % 1 = 0",
		.u.insns_पूर्णांक = अणु
			BPF_LD_IMM64(R0, 3),
			BPF_ALU32_IMM(BPF_MOD, R0, 1),
			BPF_EXIT_INSN(),
		पूर्ण,
		INTERNAL,
		अणु पूर्ण,
		अणु अणु 0, 0 पूर्ण पूर्ण,
	पूर्ण,
	अणु
		"ALU_MOD_K: 4294967295 % 4294967293 = 2",
		.u.insns_पूर्णांक = अणु
			BPF_LD_IMM64(R0, 4294967295U),
			BPF_ALU32_IMM(BPF_MOD, R0, 4294967293U),
			BPF_EXIT_INSN(),
		पूर्ण,
		INTERNAL,
		अणु पूर्ण,
		अणु अणु 0, 2 पूर्ण पूर्ण,
	पूर्ण,
	अणु
		"ALU64_MOD_K: 3 % 2 = 1",
		.u.insns_पूर्णांक = अणु
			BPF_LD_IMM64(R0, 3),
			BPF_ALU64_IMM(BPF_MOD, R0, 2),
			BPF_EXIT_INSN(),
		पूर्ण,
		INTERNAL,
		अणु पूर्ण,
		अणु अणु 0, 1 पूर्ण पूर्ण,
	पूर्ण,
	अणु
		"ALU64_MOD_K: 3 % 1 = 0",
		.u.insns_पूर्णांक = अणु
			BPF_LD_IMM64(R0, 3),
			BPF_ALU64_IMM(BPF_MOD, R0, 1),
			BPF_EXIT_INSN(),
		पूर्ण,
		INTERNAL,
		अणु पूर्ण,
		अणु अणु 0, 0 पूर्ण पूर्ण,
	पूर्ण,
	अणु
		"ALU64_MOD_K: 2147483647 % 2147483645 = 2",
		.u.insns_पूर्णांक = अणु
			BPF_LD_IMM64(R0, 2147483647),
			BPF_ALU64_IMM(BPF_MOD, R0, 2147483645),
			BPF_EXIT_INSN(),
		पूर्ण,
		INTERNAL,
		अणु पूर्ण,
		अणु अणु 0, 2 पूर्ण पूर्ण,
	पूर्ण,
	/* BPF_ALU | BPF_AND | BPF_X */
	अणु
		"ALU_AND_X: 3 & 2 = 2",
		.u.insns_पूर्णांक = अणु
			BPF_LD_IMM64(R0, 3),
			BPF_ALU32_IMM(BPF_MOV, R1, 2),
			BPF_ALU32_REG(BPF_AND, R0, R1),
			BPF_EXIT_INSN(),
		पूर्ण,
		INTERNAL,
		अणु पूर्ण,
		अणु अणु 0, 2 पूर्ण पूर्ण,
	पूर्ण,
	अणु
		"ALU_AND_X: 0xffffffff & 0xffffffff = 0xffffffff",
		.u.insns_पूर्णांक = अणु
			BPF_LD_IMM64(R0, 0xffffffff),
			BPF_ALU32_IMM(BPF_MOV, R1, 0xffffffff),
			BPF_ALU32_REG(BPF_AND, R0, R1),
			BPF_EXIT_INSN(),
		पूर्ण,
		INTERNAL,
		अणु पूर्ण,
		अणु अणु 0, 0xffffffff पूर्ण पूर्ण,
	पूर्ण,
	अणु
		"ALU64_AND_X: 3 & 2 = 2",
		.u.insns_पूर्णांक = अणु
			BPF_LD_IMM64(R0, 3),
			BPF_ALU32_IMM(BPF_MOV, R1, 2),
			BPF_ALU64_REG(BPF_AND, R0, R1),
			BPF_EXIT_INSN(),
		पूर्ण,
		INTERNAL,
		अणु पूर्ण,
		अणु अणु 0, 2 पूर्ण पूर्ण,
	पूर्ण,
	अणु
		"ALU64_AND_X: 0xffffffff & 0xffffffff = 0xffffffff",
		.u.insns_पूर्णांक = अणु
			BPF_LD_IMM64(R0, 0xffffffff),
			BPF_ALU32_IMM(BPF_MOV, R1, 0xffffffff),
			BPF_ALU64_REG(BPF_AND, R0, R1),
			BPF_EXIT_INSN(),
		पूर्ण,
		INTERNAL,
		अणु पूर्ण,
		अणु अणु 0, 0xffffffff पूर्ण पूर्ण,
	पूर्ण,
	/* BPF_ALU | BPF_AND | BPF_K */
	अणु
		"ALU_AND_K: 3 & 2 = 2",
		.u.insns_पूर्णांक = अणु
			BPF_LD_IMM64(R0, 3),
			BPF_ALU32_IMM(BPF_AND, R0, 2),
			BPF_EXIT_INSN(),
		पूर्ण,
		INTERNAL,
		अणु पूर्ण,
		अणु अणु 0, 2 पूर्ण पूर्ण,
	पूर्ण,
	अणु
		"ALU_AND_K: 0xffffffff & 0xffffffff = 0xffffffff",
		.u.insns_पूर्णांक = अणु
			BPF_LD_IMM64(R0, 0xffffffff),
			BPF_ALU32_IMM(BPF_AND, R0, 0xffffffff),
			BPF_EXIT_INSN(),
		पूर्ण,
		INTERNAL,
		अणु पूर्ण,
		अणु अणु 0, 0xffffffff पूर्ण पूर्ण,
	पूर्ण,
	अणु
		"ALU64_AND_K: 3 & 2 = 2",
		.u.insns_पूर्णांक = अणु
			BPF_LD_IMM64(R0, 3),
			BPF_ALU64_IMM(BPF_AND, R0, 2),
			BPF_EXIT_INSN(),
		पूर्ण,
		INTERNAL,
		अणु पूर्ण,
		अणु अणु 0, 2 पूर्ण पूर्ण,
	पूर्ण,
	अणु
		"ALU64_AND_K: 0xffffffff & 0xffffffff = 0xffffffff",
		.u.insns_पूर्णांक = अणु
			BPF_LD_IMM64(R0, 0xffffffff),
			BPF_ALU64_IMM(BPF_AND, R0, 0xffffffff),
			BPF_EXIT_INSN(),
		पूर्ण,
		INTERNAL,
		अणु पूर्ण,
		अणु अणु 0, 0xffffffff पूर्ण पूर्ण,
	पूर्ण,
	अणु
		"ALU64_AND_K: 0x0000ffffffff0000 & 0x0 = 0x0000ffff00000000",
		.u.insns_पूर्णांक = अणु
			BPF_LD_IMM64(R2, 0x0000ffffffff0000LL),
			BPF_LD_IMM64(R3, 0x0000000000000000LL),
			BPF_ALU64_IMM(BPF_AND, R2, 0x0),
			BPF_JMP_REG(BPF_JEQ, R2, R3, 2),
			BPF_MOV32_IMM(R0, 2),
			BPF_EXIT_INSN(),
			BPF_MOV32_IMM(R0, 1),
			BPF_EXIT_INSN(),
		पूर्ण,
		INTERNAL,
		अणु पूर्ण,
		अणु अणु 0, 0x1 पूर्ण पूर्ण,
	पूर्ण,
	अणु
		"ALU64_AND_K: 0x0000ffffffff0000 & -1 = 0x0000ffffffffffff",
		.u.insns_पूर्णांक = अणु
			BPF_LD_IMM64(R2, 0x0000ffffffff0000LL),
			BPF_LD_IMM64(R3, 0x0000ffffffff0000LL),
			BPF_ALU64_IMM(BPF_AND, R2, 0xffffffff),
			BPF_JMP_REG(BPF_JEQ, R2, R3, 2),
			BPF_MOV32_IMM(R0, 2),
			BPF_EXIT_INSN(),
			BPF_MOV32_IMM(R0, 1),
			BPF_EXIT_INSN(),
		पूर्ण,
		INTERNAL,
		अणु पूर्ण,
		अणु अणु 0, 0x1 पूर्ण पूर्ण,
	पूर्ण,
	अणु
		"ALU64_AND_K: 0xffffffffffffffff & -1 = 0xffffffffffffffff",
		.u.insns_पूर्णांक = अणु
			BPF_LD_IMM64(R2, 0xffffffffffffffffLL),
			BPF_LD_IMM64(R3, 0xffffffffffffffffLL),
			BPF_ALU64_IMM(BPF_AND, R2, 0xffffffff),
			BPF_JMP_REG(BPF_JEQ, R2, R3, 2),
			BPF_MOV32_IMM(R0, 2),
			BPF_EXIT_INSN(),
			BPF_MOV32_IMM(R0, 1),
			BPF_EXIT_INSN(),
		पूर्ण,
		INTERNAL,
		अणु पूर्ण,
		अणु अणु 0, 0x1 पूर्ण पूर्ण,
	पूर्ण,
	/* BPF_ALU | BPF_OR | BPF_X */
	अणु
		"ALU_OR_X: 1 | 2 = 3",
		.u.insns_पूर्णांक = अणु
			BPF_LD_IMM64(R0, 1),
			BPF_ALU32_IMM(BPF_MOV, R1, 2),
			BPF_ALU32_REG(BPF_OR, R0, R1),
			BPF_EXIT_INSN(),
		पूर्ण,
		INTERNAL,
		अणु पूर्ण,
		अणु अणु 0, 3 पूर्ण पूर्ण,
	पूर्ण,
	अणु
		"ALU_OR_X: 0x0 | 0xffffffff = 0xffffffff",
		.u.insns_पूर्णांक = अणु
			BPF_LD_IMM64(R0, 0),
			BPF_ALU32_IMM(BPF_MOV, R1, 0xffffffff),
			BPF_ALU32_REG(BPF_OR, R0, R1),
			BPF_EXIT_INSN(),
		पूर्ण,
		INTERNAL,
		अणु पूर्ण,
		अणु अणु 0, 0xffffffff पूर्ण पूर्ण,
	पूर्ण,
	अणु
		"ALU64_OR_X: 1 | 2 = 3",
		.u.insns_पूर्णांक = अणु
			BPF_LD_IMM64(R0, 1),
			BPF_ALU32_IMM(BPF_MOV, R1, 2),
			BPF_ALU64_REG(BPF_OR, R0, R1),
			BPF_EXIT_INSN(),
		पूर्ण,
		INTERNAL,
		अणु पूर्ण,
		अणु अणु 0, 3 पूर्ण पूर्ण,
	पूर्ण,
	अणु
		"ALU64_OR_X: 0 | 0xffffffff = 0xffffffff",
		.u.insns_पूर्णांक = अणु
			BPF_LD_IMM64(R0, 0),
			BPF_ALU32_IMM(BPF_MOV, R1, 0xffffffff),
			BPF_ALU64_REG(BPF_OR, R0, R1),
			BPF_EXIT_INSN(),
		पूर्ण,
		INTERNAL,
		अणु पूर्ण,
		अणु अणु 0, 0xffffffff पूर्ण पूर्ण,
	पूर्ण,
	/* BPF_ALU | BPF_OR | BPF_K */
	अणु
		"ALU_OR_K: 1 | 2 = 3",
		.u.insns_पूर्णांक = अणु
			BPF_LD_IMM64(R0, 1),
			BPF_ALU32_IMM(BPF_OR, R0, 2),
			BPF_EXIT_INSN(),
		पूर्ण,
		INTERNAL,
		अणु पूर्ण,
		अणु अणु 0, 3 पूर्ण पूर्ण,
	पूर्ण,
	अणु
		"ALU_OR_K: 0 & 0xffffffff = 0xffffffff",
		.u.insns_पूर्णांक = अणु
			BPF_LD_IMM64(R0, 0),
			BPF_ALU32_IMM(BPF_OR, R0, 0xffffffff),
			BPF_EXIT_INSN(),
		पूर्ण,
		INTERNAL,
		अणु पूर्ण,
		अणु अणु 0, 0xffffffff पूर्ण पूर्ण,
	पूर्ण,
	अणु
		"ALU64_OR_K: 1 | 2 = 3",
		.u.insns_पूर्णांक = अणु
			BPF_LD_IMM64(R0, 1),
			BPF_ALU64_IMM(BPF_OR, R0, 2),
			BPF_EXIT_INSN(),
		पूर्ण,
		INTERNAL,
		अणु पूर्ण,
		अणु अणु 0, 3 पूर्ण पूर्ण,
	पूर्ण,
	अणु
		"ALU64_OR_K: 0 & 0xffffffff = 0xffffffff",
		.u.insns_पूर्णांक = अणु
			BPF_LD_IMM64(R0, 0),
			BPF_ALU64_IMM(BPF_OR, R0, 0xffffffff),
			BPF_EXIT_INSN(),
		पूर्ण,
		INTERNAL,
		अणु पूर्ण,
		अणु अणु 0, 0xffffffff पूर्ण पूर्ण,
	पूर्ण,
	अणु
		"ALU64_OR_K: 0x0000ffffffff0000 | 0x0 = 0x0000ffff00000000",
		.u.insns_पूर्णांक = अणु
			BPF_LD_IMM64(R2, 0x0000ffffffff0000LL),
			BPF_LD_IMM64(R3, 0x0000ffffffff0000LL),
			BPF_ALU64_IMM(BPF_OR, R2, 0x0),
			BPF_JMP_REG(BPF_JEQ, R2, R3, 2),
			BPF_MOV32_IMM(R0, 2),
			BPF_EXIT_INSN(),
			BPF_MOV32_IMM(R0, 1),
			BPF_EXIT_INSN(),
		पूर्ण,
		INTERNAL,
		अणु पूर्ण,
		अणु अणु 0, 0x1 पूर्ण पूर्ण,
	पूर्ण,
	अणु
		"ALU64_OR_K: 0x0000ffffffff0000 | -1 = 0xffffffffffffffff",
		.u.insns_पूर्णांक = अणु
			BPF_LD_IMM64(R2, 0x0000ffffffff0000LL),
			BPF_LD_IMM64(R3, 0xffffffffffffffffLL),
			BPF_ALU64_IMM(BPF_OR, R2, 0xffffffff),
			BPF_JMP_REG(BPF_JEQ, R2, R3, 2),
			BPF_MOV32_IMM(R0, 2),
			BPF_EXIT_INSN(),
			BPF_MOV32_IMM(R0, 1),
			BPF_EXIT_INSN(),
		पूर्ण,
		INTERNAL,
		अणु पूर्ण,
		अणु अणु 0, 0x1 पूर्ण पूर्ण,
	पूर्ण,
	अणु
		"ALU64_OR_K: 0x000000000000000 | -1 = 0xffffffffffffffff",
		.u.insns_पूर्णांक = अणु
			BPF_LD_IMM64(R2, 0x0000000000000000LL),
			BPF_LD_IMM64(R3, 0xffffffffffffffffLL),
			BPF_ALU64_IMM(BPF_OR, R2, 0xffffffff),
			BPF_JMP_REG(BPF_JEQ, R2, R3, 2),
			BPF_MOV32_IMM(R0, 2),
			BPF_EXIT_INSN(),
			BPF_MOV32_IMM(R0, 1),
			BPF_EXIT_INSN(),
		पूर्ण,
		INTERNAL,
		अणु पूर्ण,
		अणु अणु 0, 0x1 पूर्ण पूर्ण,
	पूर्ण,
	/* BPF_ALU | BPF_XOR | BPF_X */
	अणु
		"ALU_XOR_X: 5 ^ 6 = 3",
		.u.insns_पूर्णांक = अणु
			BPF_LD_IMM64(R0, 5),
			BPF_ALU32_IMM(BPF_MOV, R1, 6),
			BPF_ALU32_REG(BPF_XOR, R0, R1),
			BPF_EXIT_INSN(),
		पूर्ण,
		INTERNAL,
		अणु पूर्ण,
		अणु अणु 0, 3 पूर्ण पूर्ण,
	पूर्ण,
	अणु
		"ALU_XOR_X: 0x1 ^ 0xffffffff = 0xfffffffe",
		.u.insns_पूर्णांक = अणु
			BPF_LD_IMM64(R0, 1),
			BPF_ALU32_IMM(BPF_MOV, R1, 0xffffffff),
			BPF_ALU32_REG(BPF_XOR, R0, R1),
			BPF_EXIT_INSN(),
		पूर्ण,
		INTERNAL,
		अणु पूर्ण,
		अणु अणु 0, 0xfffffffe पूर्ण पूर्ण,
	पूर्ण,
	अणु
		"ALU64_XOR_X: 5 ^ 6 = 3",
		.u.insns_पूर्णांक = अणु
			BPF_LD_IMM64(R0, 5),
			BPF_ALU32_IMM(BPF_MOV, R1, 6),
			BPF_ALU64_REG(BPF_XOR, R0, R1),
			BPF_EXIT_INSN(),
		पूर्ण,
		INTERNAL,
		अणु पूर्ण,
		अणु अणु 0, 3 पूर्ण पूर्ण,
	पूर्ण,
	अणु
		"ALU64_XOR_X: 1 ^ 0xffffffff = 0xfffffffe",
		.u.insns_पूर्णांक = अणु
			BPF_LD_IMM64(R0, 1),
			BPF_ALU32_IMM(BPF_MOV, R1, 0xffffffff),
			BPF_ALU64_REG(BPF_XOR, R0, R1),
			BPF_EXIT_INSN(),
		पूर्ण,
		INTERNAL,
		अणु पूर्ण,
		अणु अणु 0, 0xfffffffe पूर्ण पूर्ण,
	पूर्ण,
	/* BPF_ALU | BPF_XOR | BPF_K */
	अणु
		"ALU_XOR_K: 5 ^ 6 = 3",
		.u.insns_पूर्णांक = अणु
			BPF_LD_IMM64(R0, 5),
			BPF_ALU32_IMM(BPF_XOR, R0, 6),
			BPF_EXIT_INSN(),
		पूर्ण,
		INTERNAL,
		अणु पूर्ण,
		अणु अणु 0, 3 पूर्ण पूर्ण,
	पूर्ण,
	अणु
		"ALU_XOR_K: 1 ^ 0xffffffff = 0xfffffffe",
		.u.insns_पूर्णांक = अणु
			BPF_LD_IMM64(R0, 1),
			BPF_ALU32_IMM(BPF_XOR, R0, 0xffffffff),
			BPF_EXIT_INSN(),
		पूर्ण,
		INTERNAL,
		अणु पूर्ण,
		अणु अणु 0, 0xfffffffe पूर्ण पूर्ण,
	पूर्ण,
	अणु
		"ALU64_XOR_K: 5 ^ 6 = 3",
		.u.insns_पूर्णांक = अणु
			BPF_LD_IMM64(R0, 5),
			BPF_ALU64_IMM(BPF_XOR, R0, 6),
			BPF_EXIT_INSN(),
		पूर्ण,
		INTERNAL,
		अणु पूर्ण,
		अणु अणु 0, 3 पूर्ण पूर्ण,
	पूर्ण,
	अणु
		"ALU64_XOR_K: 1 & 0xffffffff = 0xfffffffe",
		.u.insns_पूर्णांक = अणु
			BPF_LD_IMM64(R0, 1),
			BPF_ALU64_IMM(BPF_XOR, R0, 0xffffffff),
			BPF_EXIT_INSN(),
		पूर्ण,
		INTERNAL,
		अणु पूर्ण,
		अणु अणु 0, 0xfffffffe पूर्ण पूर्ण,
	पूर्ण,
	अणु
		"ALU64_XOR_K: 0x0000ffffffff0000 ^ 0x0 = 0x0000ffffffff0000",
		.u.insns_पूर्णांक = अणु
			BPF_LD_IMM64(R2, 0x0000ffffffff0000LL),
			BPF_LD_IMM64(R3, 0x0000ffffffff0000LL),
			BPF_ALU64_IMM(BPF_XOR, R2, 0x0),
			BPF_JMP_REG(BPF_JEQ, R2, R3, 2),
			BPF_MOV32_IMM(R0, 2),
			BPF_EXIT_INSN(),
			BPF_MOV32_IMM(R0, 1),
			BPF_EXIT_INSN(),
		पूर्ण,
		INTERNAL,
		अणु पूर्ण,
		अणु अणु 0, 0x1 पूर्ण पूर्ण,
	पूर्ण,
	अणु
		"ALU64_XOR_K: 0x0000ffffffff0000 ^ -1 = 0xffff00000000ffff",
		.u.insns_पूर्णांक = अणु
			BPF_LD_IMM64(R2, 0x0000ffffffff0000LL),
			BPF_LD_IMM64(R3, 0xffff00000000ffffLL),
			BPF_ALU64_IMM(BPF_XOR, R2, 0xffffffff),
			BPF_JMP_REG(BPF_JEQ, R2, R3, 2),
			BPF_MOV32_IMM(R0, 2),
			BPF_EXIT_INSN(),
			BPF_MOV32_IMM(R0, 1),
			BPF_EXIT_INSN(),
		पूर्ण,
		INTERNAL,
		अणु पूर्ण,
		अणु अणु 0, 0x1 पूर्ण पूर्ण,
	पूर्ण,
	अणु
		"ALU64_XOR_K: 0x000000000000000 ^ -1 = 0xffffffffffffffff",
		.u.insns_पूर्णांक = अणु
			BPF_LD_IMM64(R2, 0x0000000000000000LL),
			BPF_LD_IMM64(R3, 0xffffffffffffffffLL),
			BPF_ALU64_IMM(BPF_XOR, R2, 0xffffffff),
			BPF_JMP_REG(BPF_JEQ, R2, R3, 2),
			BPF_MOV32_IMM(R0, 2),
			BPF_EXIT_INSN(),
			BPF_MOV32_IMM(R0, 1),
			BPF_EXIT_INSN(),
		पूर्ण,
		INTERNAL,
		अणु पूर्ण,
		अणु अणु 0, 0x1 पूर्ण पूर्ण,
	पूर्ण,
	/* BPF_ALU | BPF_LSH | BPF_X */
	अणु
		"ALU_LSH_X: 1 << 1 = 2",
		.u.insns_पूर्णांक = अणु
			BPF_LD_IMM64(R0, 1),
			BPF_ALU32_IMM(BPF_MOV, R1, 1),
			BPF_ALU32_REG(BPF_LSH, R0, R1),
			BPF_EXIT_INSN(),
		पूर्ण,
		INTERNAL,
		अणु पूर्ण,
		अणु अणु 0, 2 पूर्ण पूर्ण,
	पूर्ण,
	अणु
		"ALU_LSH_X: 1 << 31 = 0x80000000",
		.u.insns_पूर्णांक = अणु
			BPF_LD_IMM64(R0, 1),
			BPF_ALU32_IMM(BPF_MOV, R1, 31),
			BPF_ALU32_REG(BPF_LSH, R0, R1),
			BPF_EXIT_INSN(),
		पूर्ण,
		INTERNAL,
		अणु पूर्ण,
		अणु अणु 0, 0x80000000 पूर्ण पूर्ण,
	पूर्ण,
	अणु
		"ALU64_LSH_X: 1 << 1 = 2",
		.u.insns_पूर्णांक = अणु
			BPF_LD_IMM64(R0, 1),
			BPF_ALU32_IMM(BPF_MOV, R1, 1),
			BPF_ALU64_REG(BPF_LSH, R0, R1),
			BPF_EXIT_INSN(),
		पूर्ण,
		INTERNAL,
		अणु पूर्ण,
		अणु अणु 0, 2 पूर्ण पूर्ण,
	पूर्ण,
	अणु
		"ALU64_LSH_X: 1 << 31 = 0x80000000",
		.u.insns_पूर्णांक = अणु
			BPF_LD_IMM64(R0, 1),
			BPF_ALU32_IMM(BPF_MOV, R1, 31),
			BPF_ALU64_REG(BPF_LSH, R0, R1),
			BPF_EXIT_INSN(),
		पूर्ण,
		INTERNAL,
		अणु पूर्ण,
		अणु अणु 0, 0x80000000 पूर्ण पूर्ण,
	पूर्ण,
	/* BPF_ALU | BPF_LSH | BPF_K */
	अणु
		"ALU_LSH_K: 1 << 1 = 2",
		.u.insns_पूर्णांक = अणु
			BPF_LD_IMM64(R0, 1),
			BPF_ALU32_IMM(BPF_LSH, R0, 1),
			BPF_EXIT_INSN(),
		पूर्ण,
		INTERNAL,
		अणु पूर्ण,
		अणु अणु 0, 2 पूर्ण पूर्ण,
	पूर्ण,
	अणु
		"ALU_LSH_K: 1 << 31 = 0x80000000",
		.u.insns_पूर्णांक = अणु
			BPF_LD_IMM64(R0, 1),
			BPF_ALU32_IMM(BPF_LSH, R0, 31),
			BPF_EXIT_INSN(),
		पूर्ण,
		INTERNAL,
		अणु पूर्ण,
		अणु अणु 0, 0x80000000 पूर्ण पूर्ण,
	पूर्ण,
	अणु
		"ALU64_LSH_K: 1 << 1 = 2",
		.u.insns_पूर्णांक = अणु
			BPF_LD_IMM64(R0, 1),
			BPF_ALU64_IMM(BPF_LSH, R0, 1),
			BPF_EXIT_INSN(),
		पूर्ण,
		INTERNAL,
		अणु पूर्ण,
		अणु अणु 0, 2 पूर्ण पूर्ण,
	पूर्ण,
	अणु
		"ALU64_LSH_K: 1 << 31 = 0x80000000",
		.u.insns_पूर्णांक = अणु
			BPF_LD_IMM64(R0, 1),
			BPF_ALU64_IMM(BPF_LSH, R0, 31),
			BPF_EXIT_INSN(),
		पूर्ण,
		INTERNAL,
		अणु पूर्ण,
		अणु अणु 0, 0x80000000 पूर्ण पूर्ण,
	पूर्ण,
	/* BPF_ALU | BPF_RSH | BPF_X */
	अणु
		"ALU_RSH_X: 2 >> 1 = 1",
		.u.insns_पूर्णांक = अणु
			BPF_LD_IMM64(R0, 2),
			BPF_ALU32_IMM(BPF_MOV, R1, 1),
			BPF_ALU32_REG(BPF_RSH, R0, R1),
			BPF_EXIT_INSN(),
		पूर्ण,
		INTERNAL,
		अणु पूर्ण,
		अणु अणु 0, 1 पूर्ण पूर्ण,
	पूर्ण,
	अणु
		"ALU_RSH_X: 0x80000000 >> 31 = 1",
		.u.insns_पूर्णांक = अणु
			BPF_LD_IMM64(R0, 0x80000000),
			BPF_ALU32_IMM(BPF_MOV, R1, 31),
			BPF_ALU32_REG(BPF_RSH, R0, R1),
			BPF_EXIT_INSN(),
		पूर्ण,
		INTERNAL,
		अणु पूर्ण,
		अणु अणु 0, 1 पूर्ण पूर्ण,
	पूर्ण,
	अणु
		"ALU64_RSH_X: 2 >> 1 = 1",
		.u.insns_पूर्णांक = अणु
			BPF_LD_IMM64(R0, 2),
			BPF_ALU32_IMM(BPF_MOV, R1, 1),
			BPF_ALU64_REG(BPF_RSH, R0, R1),
			BPF_EXIT_INSN(),
		पूर्ण,
		INTERNAL,
		अणु पूर्ण,
		अणु अणु 0, 1 पूर्ण पूर्ण,
	पूर्ण,
	अणु
		"ALU64_RSH_X: 0x80000000 >> 31 = 1",
		.u.insns_पूर्णांक = अणु
			BPF_LD_IMM64(R0, 0x80000000),
			BPF_ALU32_IMM(BPF_MOV, R1, 31),
			BPF_ALU64_REG(BPF_RSH, R0, R1),
			BPF_EXIT_INSN(),
		पूर्ण,
		INTERNAL,
		अणु पूर्ण,
		अणु अणु 0, 1 पूर्ण पूर्ण,
	पूर्ण,
	/* BPF_ALU | BPF_RSH | BPF_K */
	अणु
		"ALU_RSH_K: 2 >> 1 = 1",
		.u.insns_पूर्णांक = अणु
			BPF_LD_IMM64(R0, 2),
			BPF_ALU32_IMM(BPF_RSH, R0, 1),
			BPF_EXIT_INSN(),
		पूर्ण,
		INTERNAL,
		अणु पूर्ण,
		अणु अणु 0, 1 पूर्ण पूर्ण,
	पूर्ण,
	अणु
		"ALU_RSH_K: 0x80000000 >> 31 = 1",
		.u.insns_पूर्णांक = अणु
			BPF_LD_IMM64(R0, 0x80000000),
			BPF_ALU32_IMM(BPF_RSH, R0, 31),
			BPF_EXIT_INSN(),
		पूर्ण,
		INTERNAL,
		अणु पूर्ण,
		अणु अणु 0, 1 पूर्ण पूर्ण,
	पूर्ण,
	अणु
		"ALU64_RSH_K: 2 >> 1 = 1",
		.u.insns_पूर्णांक = अणु
			BPF_LD_IMM64(R0, 2),
			BPF_ALU64_IMM(BPF_RSH, R0, 1),
			BPF_EXIT_INSN(),
		पूर्ण,
		INTERNAL,
		अणु पूर्ण,
		अणु अणु 0, 1 पूर्ण पूर्ण,
	पूर्ण,
	अणु
		"ALU64_RSH_K: 0x80000000 >> 31 = 1",
		.u.insns_पूर्णांक = अणु
			BPF_LD_IMM64(R0, 0x80000000),
			BPF_ALU64_IMM(BPF_RSH, R0, 31),
			BPF_EXIT_INSN(),
		पूर्ण,
		INTERNAL,
		अणु पूर्ण,
		अणु अणु 0, 1 पूर्ण पूर्ण,
	पूर्ण,
	/* BPF_ALU | BPF_ARSH | BPF_X */
	अणु
		"ALU_ARSH_X: 0xff00ff0000000000 >> 40 = 0xffffffffffff00ff",
		.u.insns_पूर्णांक = अणु
			BPF_LD_IMM64(R0, 0xff00ff0000000000LL),
			BPF_ALU32_IMM(BPF_MOV, R1, 40),
			BPF_ALU64_REG(BPF_ARSH, R0, R1),
			BPF_EXIT_INSN(),
		पूर्ण,
		INTERNAL,
		अणु पूर्ण,
		अणु अणु 0, 0xffff00ff पूर्ण पूर्ण,
	पूर्ण,
	/* BPF_ALU | BPF_ARSH | BPF_K */
	अणु
		"ALU_ARSH_K: 0xff00ff0000000000 >> 40 = 0xffffffffffff00ff",
		.u.insns_पूर्णांक = अणु
			BPF_LD_IMM64(R0, 0xff00ff0000000000LL),
			BPF_ALU64_IMM(BPF_ARSH, R0, 40),
			BPF_EXIT_INSN(),
		पूर्ण,
		INTERNAL,
		अणु पूर्ण,
		अणु अणु 0, 0xffff00ff पूर्ण पूर्ण,
	पूर्ण,
	/* BPF_ALU | BPF_NEG */
	अणु
		"ALU_NEG: -(3) = -3",
		.u.insns_पूर्णांक = अणु
			BPF_ALU32_IMM(BPF_MOV, R0, 3),
			BPF_ALU32_IMM(BPF_NEG, R0, 0),
			BPF_EXIT_INSN(),
		पूर्ण,
		INTERNAL,
		अणु पूर्ण,
		अणु अणु 0, -3 पूर्ण पूर्ण,
	पूर्ण,
	अणु
		"ALU_NEG: -(-3) = 3",
		.u.insns_पूर्णांक = अणु
			BPF_ALU32_IMM(BPF_MOV, R0, -3),
			BPF_ALU32_IMM(BPF_NEG, R0, 0),
			BPF_EXIT_INSN(),
		पूर्ण,
		INTERNAL,
		अणु पूर्ण,
		अणु अणु 0, 3 पूर्ण पूर्ण,
	पूर्ण,
	अणु
		"ALU64_NEG: -(3) = -3",
		.u.insns_पूर्णांक = अणु
			BPF_LD_IMM64(R0, 3),
			BPF_ALU64_IMM(BPF_NEG, R0, 0),
			BPF_EXIT_INSN(),
		पूर्ण,
		INTERNAL,
		अणु पूर्ण,
		अणु अणु 0, -3 पूर्ण पूर्ण,
	पूर्ण,
	अणु
		"ALU64_NEG: -(-3) = 3",
		.u.insns_पूर्णांक = अणु
			BPF_LD_IMM64(R0, -3),
			BPF_ALU64_IMM(BPF_NEG, R0, 0),
			BPF_EXIT_INSN(),
		पूर्ण,
		INTERNAL,
		अणु पूर्ण,
		अणु अणु 0, 3 पूर्ण पूर्ण,
	पूर्ण,
	/* BPF_ALU | BPF_END | BPF_FROM_BE */
	अणु
		"ALU_END_FROM_BE 16: 0x0123456789abcdef -> 0xcdef",
		.u.insns_पूर्णांक = अणु
			BPF_LD_IMM64(R0, 0x0123456789abcdefLL),
			BPF_ENDIAN(BPF_FROM_BE, R0, 16),
			BPF_EXIT_INSN(),
		पूर्ण,
		INTERNAL,
		अणु पूर्ण,
		अणु अणु 0,  cpu_to_be16(0xcdef) पूर्ण पूर्ण,
	पूर्ण,
	अणु
		"ALU_END_FROM_BE 32: 0x0123456789abcdef -> 0x89abcdef",
		.u.insns_पूर्णांक = अणु
			BPF_LD_IMM64(R0, 0x0123456789abcdefLL),
			BPF_ENDIAN(BPF_FROM_BE, R0, 32),
			BPF_ALU64_REG(BPF_MOV, R1, R0),
			BPF_ALU64_IMM(BPF_RSH, R1, 32),
			BPF_ALU32_REG(BPF_ADD, R0, R1), /* R1 = 0 */
			BPF_EXIT_INSN(),
		पूर्ण,
		INTERNAL,
		अणु पूर्ण,
		अणु अणु 0, cpu_to_be32(0x89abcdef) पूर्ण पूर्ण,
	पूर्ण,
	अणु
		"ALU_END_FROM_BE 64: 0x0123456789abcdef -> 0x89abcdef",
		.u.insns_पूर्णांक = अणु
			BPF_LD_IMM64(R0, 0x0123456789abcdefLL),
			BPF_ENDIAN(BPF_FROM_BE, R0, 64),
			BPF_EXIT_INSN(),
		पूर्ण,
		INTERNAL,
		अणु पूर्ण,
		अणु अणु 0, (u32) cpu_to_be64(0x0123456789abcdefLL) पूर्ण पूर्ण,
	पूर्ण,
	/* BPF_ALU | BPF_END | BPF_FROM_LE */
	अणु
		"ALU_END_FROM_LE 16: 0x0123456789abcdef -> 0xefcd",
		.u.insns_पूर्णांक = अणु
			BPF_LD_IMM64(R0, 0x0123456789abcdefLL),
			BPF_ENDIAN(BPF_FROM_LE, R0, 16),
			BPF_EXIT_INSN(),
		पूर्ण,
		INTERNAL,
		अणु पूर्ण,
		अणु अणु 0, cpu_to_le16(0xcdef) पूर्ण पूर्ण,
	पूर्ण,
	अणु
		"ALU_END_FROM_LE 32: 0x0123456789abcdef -> 0xefcdab89",
		.u.insns_पूर्णांक = अणु
			BPF_LD_IMM64(R0, 0x0123456789abcdefLL),
			BPF_ENDIAN(BPF_FROM_LE, R0, 32),
			BPF_ALU64_REG(BPF_MOV, R1, R0),
			BPF_ALU64_IMM(BPF_RSH, R1, 32),
			BPF_ALU32_REG(BPF_ADD, R0, R1), /* R1 = 0 */
			BPF_EXIT_INSN(),
		पूर्ण,
		INTERNAL,
		अणु पूर्ण,
		अणु अणु 0, cpu_to_le32(0x89abcdef) पूर्ण पूर्ण,
	पूर्ण,
	अणु
		"ALU_END_FROM_LE 64: 0x0123456789abcdef -> 0x67452301",
		.u.insns_पूर्णांक = अणु
			BPF_LD_IMM64(R0, 0x0123456789abcdefLL),
			BPF_ENDIAN(BPF_FROM_LE, R0, 64),
			BPF_EXIT_INSN(),
		पूर्ण,
		INTERNAL,
		अणु पूर्ण,
		अणु अणु 0, (u32) cpu_to_le64(0x0123456789abcdefLL) पूर्ण पूर्ण,
	पूर्ण,
	/* BPF_ST(X) | BPF_MEM | BPF_B/H/W/DW */
	अणु
		"ST_MEM_B: Store/Load byte: max negative",
		.u.insns_पूर्णांक = अणु
			BPF_ALU32_IMM(BPF_MOV, R0, 1),
			BPF_ST_MEM(BPF_B, R10, -40, 0xff),
			BPF_LDX_MEM(BPF_B, R0, R10, -40),
			BPF_EXIT_INSN(),
		पूर्ण,
		INTERNAL,
		अणु पूर्ण,
		अणु अणु 0, 0xff पूर्ण पूर्ण,
		.stack_depth = 40,
	पूर्ण,
	अणु
		"ST_MEM_B: Store/Load byte: max positive",
		.u.insns_पूर्णांक = अणु
			BPF_ALU32_IMM(BPF_MOV, R0, 1),
			BPF_ST_MEM(BPF_H, R10, -40, 0x7f),
			BPF_LDX_MEM(BPF_H, R0, R10, -40),
			BPF_EXIT_INSN(),
		पूर्ण,
		INTERNAL,
		अणु पूर्ण,
		अणु अणु 0, 0x7f पूर्ण पूर्ण,
		.stack_depth = 40,
	पूर्ण,
	अणु
		"STX_MEM_B: Store/Load byte: max negative",
		.u.insns_पूर्णांक = अणु
			BPF_LD_IMM64(R0, 0),
			BPF_LD_IMM64(R1, 0xffLL),
			BPF_STX_MEM(BPF_B, R10, R1, -40),
			BPF_LDX_MEM(BPF_B, R0, R10, -40),
			BPF_EXIT_INSN(),
		पूर्ण,
		INTERNAL,
		अणु पूर्ण,
		अणु अणु 0, 0xff पूर्ण पूर्ण,
		.stack_depth = 40,
	पूर्ण,
	अणु
		"ST_MEM_H: Store/Load half word: max negative",
		.u.insns_पूर्णांक = अणु
			BPF_ALU32_IMM(BPF_MOV, R0, 1),
			BPF_ST_MEM(BPF_H, R10, -40, 0xffff),
			BPF_LDX_MEM(BPF_H, R0, R10, -40),
			BPF_EXIT_INSN(),
		पूर्ण,
		INTERNAL,
		अणु पूर्ण,
		अणु अणु 0, 0xffff पूर्ण पूर्ण,
		.stack_depth = 40,
	पूर्ण,
	अणु
		"ST_MEM_H: Store/Load half word: max positive",
		.u.insns_पूर्णांक = अणु
			BPF_ALU32_IMM(BPF_MOV, R0, 1),
			BPF_ST_MEM(BPF_H, R10, -40, 0x7fff),
			BPF_LDX_MEM(BPF_H, R0, R10, -40),
			BPF_EXIT_INSN(),
		पूर्ण,
		INTERNAL,
		अणु पूर्ण,
		अणु अणु 0, 0x7fff पूर्ण पूर्ण,
		.stack_depth = 40,
	पूर्ण,
	अणु
		"STX_MEM_H: Store/Load half word: max negative",
		.u.insns_पूर्णांक = अणु
			BPF_LD_IMM64(R0, 0),
			BPF_LD_IMM64(R1, 0xffffLL),
			BPF_STX_MEM(BPF_H, R10, R1, -40),
			BPF_LDX_MEM(BPF_H, R0, R10, -40),
			BPF_EXIT_INSN(),
		पूर्ण,
		INTERNAL,
		अणु पूर्ण,
		अणु अणु 0, 0xffff पूर्ण पूर्ण,
		.stack_depth = 40,
	पूर्ण,
	अणु
		"ST_MEM_W: Store/Load word: max negative",
		.u.insns_पूर्णांक = अणु
			BPF_ALU32_IMM(BPF_MOV, R0, 1),
			BPF_ST_MEM(BPF_W, R10, -40, 0xffffffff),
			BPF_LDX_MEM(BPF_W, R0, R10, -40),
			BPF_EXIT_INSN(),
		पूर्ण,
		INTERNAL,
		अणु पूर्ण,
		अणु अणु 0, 0xffffffff पूर्ण पूर्ण,
		.stack_depth = 40,
	पूर्ण,
	अणु
		"ST_MEM_W: Store/Load word: max positive",
		.u.insns_पूर्णांक = अणु
			BPF_ALU32_IMM(BPF_MOV, R0, 1),
			BPF_ST_MEM(BPF_W, R10, -40, 0x7fffffff),
			BPF_LDX_MEM(BPF_W, R0, R10, -40),
			BPF_EXIT_INSN(),
		पूर्ण,
		INTERNAL,
		अणु पूर्ण,
		अणु अणु 0, 0x7fffffff पूर्ण पूर्ण,
		.stack_depth = 40,
	पूर्ण,
	अणु
		"STX_MEM_W: Store/Load word: max negative",
		.u.insns_पूर्णांक = अणु
			BPF_LD_IMM64(R0, 0),
			BPF_LD_IMM64(R1, 0xffffffffLL),
			BPF_STX_MEM(BPF_W, R10, R1, -40),
			BPF_LDX_MEM(BPF_W, R0, R10, -40),
			BPF_EXIT_INSN(),
		पूर्ण,
		INTERNAL,
		अणु पूर्ण,
		अणु अणु 0, 0xffffffff पूर्ण पूर्ण,
		.stack_depth = 40,
	पूर्ण,
	अणु
		"ST_MEM_DW: Store/Load double word: max negative",
		.u.insns_पूर्णांक = अणु
			BPF_ALU32_IMM(BPF_MOV, R0, 1),
			BPF_ST_MEM(BPF_DW, R10, -40, 0xffffffff),
			BPF_LDX_MEM(BPF_DW, R0, R10, -40),
			BPF_EXIT_INSN(),
		पूर्ण,
		INTERNAL,
		अणु पूर्ण,
		अणु अणु 0, 0xffffffff पूर्ण पूर्ण,
		.stack_depth = 40,
	पूर्ण,
	अणु
		"ST_MEM_DW: Store/Load double word: max negative 2",
		.u.insns_पूर्णांक = अणु
			BPF_LD_IMM64(R2, 0xffff00000000ffffLL),
			BPF_LD_IMM64(R3, 0xffffffffffffffffLL),
			BPF_ST_MEM(BPF_DW, R10, -40, 0xffffffff),
			BPF_LDX_MEM(BPF_DW, R2, R10, -40),
			BPF_JMP_REG(BPF_JEQ, R2, R3, 2),
			BPF_MOV32_IMM(R0, 2),
			BPF_EXIT_INSN(),
			BPF_MOV32_IMM(R0, 1),
			BPF_EXIT_INSN(),
		पूर्ण,
		INTERNAL,
		अणु पूर्ण,
		अणु अणु 0, 0x1 पूर्ण पूर्ण,
		.stack_depth = 40,
	पूर्ण,
	अणु
		"ST_MEM_DW: Store/Load double word: max positive",
		.u.insns_पूर्णांक = अणु
			BPF_ALU32_IMM(BPF_MOV, R0, 1),
			BPF_ST_MEM(BPF_DW, R10, -40, 0x7fffffff),
			BPF_LDX_MEM(BPF_DW, R0, R10, -40),
			BPF_EXIT_INSN(),
		पूर्ण,
		INTERNAL,
		अणु पूर्ण,
		अणु अणु 0, 0x7fffffff पूर्ण पूर्ण,
		.stack_depth = 40,
	पूर्ण,
	अणु
		"STX_MEM_DW: Store/Load double word: max negative",
		.u.insns_पूर्णांक = अणु
			BPF_LD_IMM64(R0, 0),
			BPF_LD_IMM64(R1, 0xffffffffffffffffLL),
			BPF_STX_MEM(BPF_W, R10, R1, -40),
			BPF_LDX_MEM(BPF_W, R0, R10, -40),
			BPF_EXIT_INSN(),
		पूर्ण,
		INTERNAL,
		अणु पूर्ण,
		अणु अणु 0, 0xffffffff पूर्ण पूर्ण,
		.stack_depth = 40,
	पूर्ण,
	/* BPF_STX | BPF_ATOMIC | BPF_W/DW */
	अणु
		"STX_XADD_W: Test: 0x12 + 0x10 = 0x22",
		.u.insns_पूर्णांक = अणु
			BPF_ALU32_IMM(BPF_MOV, R0, 0x12),
			BPF_ST_MEM(BPF_W, R10, -40, 0x10),
			BPF_ATOMIC_OP(BPF_W, BPF_ADD, R10, R0, -40),
			BPF_LDX_MEM(BPF_W, R0, R10, -40),
			BPF_EXIT_INSN(),
		पूर्ण,
		INTERNAL,
		अणु पूर्ण,
		अणु अणु 0, 0x22 पूर्ण पूर्ण,
		.stack_depth = 40,
	पूर्ण,
	अणु
		"STX_XADD_W: Test side-effects, r10: 0x12 + 0x10 = 0x22",
		.u.insns_पूर्णांक = अणु
			BPF_ALU64_REG(BPF_MOV, R1, R10),
			BPF_ALU32_IMM(BPF_MOV, R0, 0x12),
			BPF_ST_MEM(BPF_W, R10, -40, 0x10),
			BPF_ATOMIC_OP(BPF_W, BPF_ADD, R10, R0, -40),
			BPF_ALU64_REG(BPF_MOV, R0, R10),
			BPF_ALU64_REG(BPF_SUB, R0, R1),
			BPF_EXIT_INSN(),
		पूर्ण,
		INTERNAL,
		अणु पूर्ण,
		अणु अणु 0, 0 पूर्ण पूर्ण,
		.stack_depth = 40,
	पूर्ण,
	अणु
		"STX_XADD_W: Test side-effects, r0: 0x12 + 0x10 = 0x22",
		.u.insns_पूर्णांक = अणु
			BPF_ALU32_IMM(BPF_MOV, R0, 0x12),
			BPF_ST_MEM(BPF_W, R10, -40, 0x10),
			BPF_ATOMIC_OP(BPF_W, BPF_ADD, R10, R0, -40),
			BPF_EXIT_INSN(),
		पूर्ण,
		INTERNAL,
		अणु पूर्ण,
		अणु अणु 0, 0x12 पूर्ण पूर्ण,
		.stack_depth = 40,
	पूर्ण,
	अणु
		"STX_XADD_W: X + 1 + 1 + 1 + ...",
		अणु पूर्ण,
		INTERNAL,
		अणु पूर्ण,
		अणु अणु 0, 4134 पूर्ण पूर्ण,
		.fill_helper = bpf_fill_stxw,
	पूर्ण,
	अणु
		"STX_XADD_DW: Test: 0x12 + 0x10 = 0x22",
		.u.insns_पूर्णांक = अणु
			BPF_ALU32_IMM(BPF_MOV, R0, 0x12),
			BPF_ST_MEM(BPF_DW, R10, -40, 0x10),
			BPF_ATOMIC_OP(BPF_DW, BPF_ADD, R10, R0, -40),
			BPF_LDX_MEM(BPF_DW, R0, R10, -40),
			BPF_EXIT_INSN(),
		पूर्ण,
		INTERNAL,
		अणु पूर्ण,
		अणु अणु 0, 0x22 पूर्ण पूर्ण,
		.stack_depth = 40,
	पूर्ण,
	अणु
		"STX_XADD_DW: Test side-effects, r10: 0x12 + 0x10 = 0x22",
		.u.insns_पूर्णांक = अणु
			BPF_ALU64_REG(BPF_MOV, R1, R10),
			BPF_ALU32_IMM(BPF_MOV, R0, 0x12),
			BPF_ST_MEM(BPF_DW, R10, -40, 0x10),
			BPF_ATOMIC_OP(BPF_DW, BPF_ADD, R10, R0, -40),
			BPF_ALU64_REG(BPF_MOV, R0, R10),
			BPF_ALU64_REG(BPF_SUB, R0, R1),
			BPF_EXIT_INSN(),
		पूर्ण,
		INTERNAL,
		अणु पूर्ण,
		अणु अणु 0, 0 पूर्ण पूर्ण,
		.stack_depth = 40,
	पूर्ण,
	अणु
		"STX_XADD_DW: Test side-effects, r0: 0x12 + 0x10 = 0x22",
		.u.insns_पूर्णांक = अणु
			BPF_ALU32_IMM(BPF_MOV, R0, 0x12),
			BPF_ST_MEM(BPF_DW, R10, -40, 0x10),
			BPF_ATOMIC_OP(BPF_DW, BPF_ADD, R10, R0, -40),
			BPF_EXIT_INSN(),
		पूर्ण,
		INTERNAL,
		अणु पूर्ण,
		अणु अणु 0, 0x12 पूर्ण पूर्ण,
		.stack_depth = 40,
	पूर्ण,
	अणु
		"STX_XADD_DW: X + 1 + 1 + 1 + ...",
		अणु पूर्ण,
		INTERNAL,
		अणु पूर्ण,
		अणु अणु 0, 4134 पूर्ण पूर्ण,
		.fill_helper = bpf_fill_stxdw,
	पूर्ण,
	/* BPF_JMP | BPF_EXIT */
	अणु
		"JMP_EXIT",
		.u.insns_पूर्णांक = अणु
			BPF_ALU32_IMM(BPF_MOV, R0, 0x4711),
			BPF_EXIT_INSN(),
			BPF_ALU32_IMM(BPF_MOV, R0, 0x4712),
		पूर्ण,
		INTERNAL,
		अणु पूर्ण,
		अणु अणु 0, 0x4711 पूर्ण पूर्ण,
	पूर्ण,
	/* BPF_JMP | BPF_JA */
	अणु
		"JMP_JA: Unconditional jump: if (true) return 1",
		.u.insns_पूर्णांक = अणु
			BPF_ALU32_IMM(BPF_MOV, R0, 0),
			BPF_JMP_IMM(BPF_JA, 0, 0, 1),
			BPF_EXIT_INSN(),
			BPF_ALU32_IMM(BPF_MOV, R0, 1),
			BPF_EXIT_INSN(),
		पूर्ण,
		INTERNAL,
		अणु पूर्ण,
		अणु अणु 0, 1 पूर्ण पूर्ण,
	पूर्ण,
	/* BPF_JMP | BPF_JSLT | BPF_K */
	अणु
		"JMP_JSLT_K: Signed jump: if (-2 < -1) return 1",
		.u.insns_पूर्णांक = अणु
			BPF_ALU32_IMM(BPF_MOV, R0, 0),
			BPF_LD_IMM64(R1, 0xfffffffffffffffeLL),
			BPF_JMP_IMM(BPF_JSLT, R1, -1, 1),
			BPF_EXIT_INSN(),
			BPF_ALU32_IMM(BPF_MOV, R0, 1),
			BPF_EXIT_INSN(),
		पूर्ण,
		INTERNAL,
		अणु पूर्ण,
		अणु अणु 0, 1 पूर्ण पूर्ण,
	पूर्ण,
	अणु
		"JMP_JSLT_K: Signed jump: if (-1 < -1) return 0",
		.u.insns_पूर्णांक = अणु
			BPF_ALU32_IMM(BPF_MOV, R0, 1),
			BPF_LD_IMM64(R1, 0xffffffffffffffffLL),
			BPF_JMP_IMM(BPF_JSLT, R1, -1, 1),
			BPF_EXIT_INSN(),
			BPF_ALU32_IMM(BPF_MOV, R0, 0),
			BPF_EXIT_INSN(),
		पूर्ण,
		INTERNAL,
		अणु पूर्ण,
		अणु अणु 0, 1 पूर्ण पूर्ण,
	पूर्ण,
	/* BPF_JMP | BPF_JSGT | BPF_K */
	अणु
		"JMP_JSGT_K: Signed jump: if (-1 > -2) return 1",
		.u.insns_पूर्णांक = अणु
			BPF_ALU32_IMM(BPF_MOV, R0, 0),
			BPF_LD_IMM64(R1, 0xffffffffffffffffLL),
			BPF_JMP_IMM(BPF_JSGT, R1, -2, 1),
			BPF_EXIT_INSN(),
			BPF_ALU32_IMM(BPF_MOV, R0, 1),
			BPF_EXIT_INSN(),
		पूर्ण,
		INTERNAL,
		अणु पूर्ण,
		अणु अणु 0, 1 पूर्ण पूर्ण,
	पूर्ण,
	अणु
		"JMP_JSGT_K: Signed jump: if (-1 > -1) return 0",
		.u.insns_पूर्णांक = अणु
			BPF_ALU32_IMM(BPF_MOV, R0, 1),
			BPF_LD_IMM64(R1, 0xffffffffffffffffLL),
			BPF_JMP_IMM(BPF_JSGT, R1, -1, 1),
			BPF_EXIT_INSN(),
			BPF_ALU32_IMM(BPF_MOV, R0, 0),
			BPF_EXIT_INSN(),
		पूर्ण,
		INTERNAL,
		अणु पूर्ण,
		अणु अणु 0, 1 पूर्ण पूर्ण,
	पूर्ण,
	/* BPF_JMP | BPF_JSLE | BPF_K */
	अणु
		"JMP_JSLE_K: Signed jump: if (-2 <= -1) return 1",
		.u.insns_पूर्णांक = अणु
			BPF_ALU32_IMM(BPF_MOV, R0, 0),
			BPF_LD_IMM64(R1, 0xfffffffffffffffeLL),
			BPF_JMP_IMM(BPF_JSLE, R1, -1, 1),
			BPF_EXIT_INSN(),
			BPF_ALU32_IMM(BPF_MOV, R0, 1),
			BPF_EXIT_INSN(),
		पूर्ण,
		INTERNAL,
		अणु पूर्ण,
		अणु अणु 0, 1 पूर्ण पूर्ण,
	पूर्ण,
	अणु
		"JMP_JSLE_K: Signed jump: if (-1 <= -1) return 1",
		.u.insns_पूर्णांक = अणु
			BPF_ALU32_IMM(BPF_MOV, R0, 0),
			BPF_LD_IMM64(R1, 0xffffffffffffffffLL),
			BPF_JMP_IMM(BPF_JSLE, R1, -1, 1),
			BPF_EXIT_INSN(),
			BPF_ALU32_IMM(BPF_MOV, R0, 1),
			BPF_EXIT_INSN(),
		पूर्ण,
		INTERNAL,
		अणु पूर्ण,
		अणु अणु 0, 1 पूर्ण पूर्ण,
	पूर्ण,
	अणु
		"JMP_JSLE_K: Signed jump: value walk 1",
		.u.insns_पूर्णांक = अणु
			BPF_ALU32_IMM(BPF_MOV, R0, 0),
			BPF_LD_IMM64(R1, 3),
			BPF_JMP_IMM(BPF_JSLE, R1, 0, 6),
			BPF_ALU64_IMM(BPF_SUB, R1, 1),
			BPF_JMP_IMM(BPF_JSLE, R1, 0, 4),
			BPF_ALU64_IMM(BPF_SUB, R1, 1),
			BPF_JMP_IMM(BPF_JSLE, R1, 0, 2),
			BPF_ALU64_IMM(BPF_SUB, R1, 1),
			BPF_JMP_IMM(BPF_JSLE, R1, 0, 1),
			BPF_EXIT_INSN(),		/* bad निकास */
			BPF_ALU32_IMM(BPF_MOV, R0, 1),	/* good निकास */
			BPF_EXIT_INSN(),
		पूर्ण,
		INTERNAL,
		अणु पूर्ण,
		अणु अणु 0, 1 पूर्ण पूर्ण,
	पूर्ण,
	अणु
		"JMP_JSLE_K: Signed jump: value walk 2",
		.u.insns_पूर्णांक = अणु
			BPF_ALU32_IMM(BPF_MOV, R0, 0),
			BPF_LD_IMM64(R1, 3),
			BPF_JMP_IMM(BPF_JSLE, R1, 0, 4),
			BPF_ALU64_IMM(BPF_SUB, R1, 2),
			BPF_JMP_IMM(BPF_JSLE, R1, 0, 2),
			BPF_ALU64_IMM(BPF_SUB, R1, 2),
			BPF_JMP_IMM(BPF_JSLE, R1, 0, 1),
			BPF_EXIT_INSN(),		/* bad निकास */
			BPF_ALU32_IMM(BPF_MOV, R0, 1),	/* good निकास */
			BPF_EXIT_INSN(),
		पूर्ण,
		INTERNAL,
		अणु पूर्ण,
		अणु अणु 0, 1 पूर्ण पूर्ण,
	पूर्ण,
	/* BPF_JMP | BPF_JSGE | BPF_K */
	अणु
		"JMP_JSGE_K: Signed jump: if (-1 >= -2) return 1",
		.u.insns_पूर्णांक = अणु
			BPF_ALU32_IMM(BPF_MOV, R0, 0),
			BPF_LD_IMM64(R1, 0xffffffffffffffffLL),
			BPF_JMP_IMM(BPF_JSGE, R1, -2, 1),
			BPF_EXIT_INSN(),
			BPF_ALU32_IMM(BPF_MOV, R0, 1),
			BPF_EXIT_INSN(),
		पूर्ण,
		INTERNAL,
		अणु पूर्ण,
		अणु अणु 0, 1 पूर्ण पूर्ण,
	पूर्ण,
	अणु
		"JMP_JSGE_K: Signed jump: if (-1 >= -1) return 1",
		.u.insns_पूर्णांक = अणु
			BPF_ALU32_IMM(BPF_MOV, R0, 0),
			BPF_LD_IMM64(R1, 0xffffffffffffffffLL),
			BPF_JMP_IMM(BPF_JSGE, R1, -1, 1),
			BPF_EXIT_INSN(),
			BPF_ALU32_IMM(BPF_MOV, R0, 1),
			BPF_EXIT_INSN(),
		पूर्ण,
		INTERNAL,
		अणु पूर्ण,
		अणु अणु 0, 1 पूर्ण पूर्ण,
	पूर्ण,
	अणु
		"JMP_JSGE_K: Signed jump: value walk 1",
		.u.insns_पूर्णांक = अणु
			BPF_ALU32_IMM(BPF_MOV, R0, 0),
			BPF_LD_IMM64(R1, -3),
			BPF_JMP_IMM(BPF_JSGE, R1, 0, 6),
			BPF_ALU64_IMM(BPF_ADD, R1, 1),
			BPF_JMP_IMM(BPF_JSGE, R1, 0, 4),
			BPF_ALU64_IMM(BPF_ADD, R1, 1),
			BPF_JMP_IMM(BPF_JSGE, R1, 0, 2),
			BPF_ALU64_IMM(BPF_ADD, R1, 1),
			BPF_JMP_IMM(BPF_JSGE, R1, 0, 1),
			BPF_EXIT_INSN(),		/* bad निकास */
			BPF_ALU32_IMM(BPF_MOV, R0, 1),	/* good निकास */
			BPF_EXIT_INSN(),
		पूर्ण,
		INTERNAL,
		अणु पूर्ण,
		अणु अणु 0, 1 पूर्ण पूर्ण,
	पूर्ण,
	अणु
		"JMP_JSGE_K: Signed jump: value walk 2",
		.u.insns_पूर्णांक = अणु
			BPF_ALU32_IMM(BPF_MOV, R0, 0),
			BPF_LD_IMM64(R1, -3),
			BPF_JMP_IMM(BPF_JSGE, R1, 0, 4),
			BPF_ALU64_IMM(BPF_ADD, R1, 2),
			BPF_JMP_IMM(BPF_JSGE, R1, 0, 2),
			BPF_ALU64_IMM(BPF_ADD, R1, 2),
			BPF_JMP_IMM(BPF_JSGE, R1, 0, 1),
			BPF_EXIT_INSN(),		/* bad निकास */
			BPF_ALU32_IMM(BPF_MOV, R0, 1),	/* good निकास */
			BPF_EXIT_INSN(),
		पूर्ण,
		INTERNAL,
		अणु पूर्ण,
		अणु अणु 0, 1 पूर्ण पूर्ण,
	पूर्ण,
	/* BPF_JMP | BPF_JGT | BPF_K */
	अणु
		"JMP_JGT_K: if (3 > 2) return 1",
		.u.insns_पूर्णांक = अणु
			BPF_ALU32_IMM(BPF_MOV, R0, 0),
			BPF_LD_IMM64(R1, 3),
			BPF_JMP_IMM(BPF_JGT, R1, 2, 1),
			BPF_EXIT_INSN(),
			BPF_ALU32_IMM(BPF_MOV, R0, 1),
			BPF_EXIT_INSN(),
		पूर्ण,
		INTERNAL,
		अणु पूर्ण,
		अणु अणु 0, 1 पूर्ण पूर्ण,
	पूर्ण,
	अणु
		"JMP_JGT_K: Unsigned jump: if (-1 > 1) return 1",
		.u.insns_पूर्णांक = अणु
			BPF_ALU32_IMM(BPF_MOV, R0, 0),
			BPF_LD_IMM64(R1, -1),
			BPF_JMP_IMM(BPF_JGT, R1, 1, 1),
			BPF_EXIT_INSN(),
			BPF_ALU32_IMM(BPF_MOV, R0, 1),
			BPF_EXIT_INSN(),
		पूर्ण,
		INTERNAL,
		अणु पूर्ण,
		अणु अणु 0, 1 पूर्ण पूर्ण,
	पूर्ण,
	/* BPF_JMP | BPF_JLT | BPF_K */
	अणु
		"JMP_JLT_K: if (2 < 3) return 1",
		.u.insns_पूर्णांक = अणु
			BPF_ALU32_IMM(BPF_MOV, R0, 0),
			BPF_LD_IMM64(R1, 2),
			BPF_JMP_IMM(BPF_JLT, R1, 3, 1),
			BPF_EXIT_INSN(),
			BPF_ALU32_IMM(BPF_MOV, R0, 1),
			BPF_EXIT_INSN(),
		पूर्ण,
		INTERNAL,
		अणु पूर्ण,
		अणु अणु 0, 1 पूर्ण पूर्ण,
	पूर्ण,
	अणु
		"JMP_JGT_K: Unsigned jump: if (1 < -1) return 1",
		.u.insns_पूर्णांक = अणु
			BPF_ALU32_IMM(BPF_MOV, R0, 0),
			BPF_LD_IMM64(R1, 1),
			BPF_JMP_IMM(BPF_JLT, R1, -1, 1),
			BPF_EXIT_INSN(),
			BPF_ALU32_IMM(BPF_MOV, R0, 1),
			BPF_EXIT_INSN(),
		पूर्ण,
		INTERNAL,
		अणु पूर्ण,
		अणु अणु 0, 1 पूर्ण पूर्ण,
	पूर्ण,
	/* BPF_JMP | BPF_JGE | BPF_K */
	अणु
		"JMP_JGE_K: if (3 >= 2) return 1",
		.u.insns_पूर्णांक = अणु
			BPF_ALU32_IMM(BPF_MOV, R0, 0),
			BPF_LD_IMM64(R1, 3),
			BPF_JMP_IMM(BPF_JGE, R1, 2, 1),
			BPF_EXIT_INSN(),
			BPF_ALU32_IMM(BPF_MOV, R0, 1),
			BPF_EXIT_INSN(),
		पूर्ण,
		INTERNAL,
		अणु पूर्ण,
		अणु अणु 0, 1 पूर्ण पूर्ण,
	पूर्ण,
	/* BPF_JMP | BPF_JLE | BPF_K */
	अणु
		"JMP_JLE_K: if (2 <= 3) return 1",
		.u.insns_पूर्णांक = अणु
			BPF_ALU32_IMM(BPF_MOV, R0, 0),
			BPF_LD_IMM64(R1, 2),
			BPF_JMP_IMM(BPF_JLE, R1, 3, 1),
			BPF_EXIT_INSN(),
			BPF_ALU32_IMM(BPF_MOV, R0, 1),
			BPF_EXIT_INSN(),
		पूर्ण,
		INTERNAL,
		अणु पूर्ण,
		अणु अणु 0, 1 पूर्ण पूर्ण,
	पूर्ण,
	/* BPF_JMP | BPF_JGT | BPF_K jump backwards */
	अणु
		"JMP_JGT_K: if (3 > 2) return 1 (jump backwards)",
		.u.insns_पूर्णांक = अणु
			BPF_JMP_IMM(BPF_JA, 0, 0, 2), /* जाओ start */
			BPF_ALU32_IMM(BPF_MOV, R0, 1), /* out: */
			BPF_EXIT_INSN(),
			BPF_ALU32_IMM(BPF_MOV, R0, 0), /* start: */
			BPF_LD_IMM64(R1, 3), /* note: this takes 2 insns */
			BPF_JMP_IMM(BPF_JGT, R1, 2, -6), /* जाओ out */
			BPF_EXIT_INSN(),
		पूर्ण,
		INTERNAL,
		अणु पूर्ण,
		अणु अणु 0, 1 पूर्ण पूर्ण,
	पूर्ण,
	अणु
		"JMP_JGE_K: if (3 >= 3) return 1",
		.u.insns_पूर्णांक = अणु
			BPF_ALU32_IMM(BPF_MOV, R0, 0),
			BPF_LD_IMM64(R1, 3),
			BPF_JMP_IMM(BPF_JGE, R1, 3, 1),
			BPF_EXIT_INSN(),
			BPF_ALU32_IMM(BPF_MOV, R0, 1),
			BPF_EXIT_INSN(),
		पूर्ण,
		INTERNAL,
		अणु पूर्ण,
		अणु अणु 0, 1 पूर्ण पूर्ण,
	पूर्ण,
	/* BPF_JMP | BPF_JLT | BPF_K jump backwards */
	अणु
		"JMP_JGT_K: if (2 < 3) return 1 (jump backwards)",
		.u.insns_पूर्णांक = अणु
			BPF_JMP_IMM(BPF_JA, 0, 0, 2), /* जाओ start */
			BPF_ALU32_IMM(BPF_MOV, R0, 1), /* out: */
			BPF_EXIT_INSN(),
			BPF_ALU32_IMM(BPF_MOV, R0, 0), /* start: */
			BPF_LD_IMM64(R1, 2), /* note: this takes 2 insns */
			BPF_JMP_IMM(BPF_JLT, R1, 3, -6), /* जाओ out */
			BPF_EXIT_INSN(),
		पूर्ण,
		INTERNAL,
		अणु पूर्ण,
		अणु अणु 0, 1 पूर्ण पूर्ण,
	पूर्ण,
	अणु
		"JMP_JLE_K: if (3 <= 3) return 1",
		.u.insns_पूर्णांक = अणु
			BPF_ALU32_IMM(BPF_MOV, R0, 0),
			BPF_LD_IMM64(R1, 3),
			BPF_JMP_IMM(BPF_JLE, R1, 3, 1),
			BPF_EXIT_INSN(),
			BPF_ALU32_IMM(BPF_MOV, R0, 1),
			BPF_EXIT_INSN(),
		पूर्ण,
		INTERNAL,
		अणु पूर्ण,
		अणु अणु 0, 1 पूर्ण पूर्ण,
	पूर्ण,
	/* BPF_JMP | BPF_JNE | BPF_K */
	अणु
		"JMP_JNE_K: if (3 != 2) return 1",
		.u.insns_पूर्णांक = अणु
			BPF_ALU32_IMM(BPF_MOV, R0, 0),
			BPF_LD_IMM64(R1, 3),
			BPF_JMP_IMM(BPF_JNE, R1, 2, 1),
			BPF_EXIT_INSN(),
			BPF_ALU32_IMM(BPF_MOV, R0, 1),
			BPF_EXIT_INSN(),
		पूर्ण,
		INTERNAL,
		अणु पूर्ण,
		अणु अणु 0, 1 पूर्ण पूर्ण,
	पूर्ण,
	/* BPF_JMP | BPF_JEQ | BPF_K */
	अणु
		"JMP_JEQ_K: if (3 == 3) return 1",
		.u.insns_पूर्णांक = अणु
			BPF_ALU32_IMM(BPF_MOV, R0, 0),
			BPF_LD_IMM64(R1, 3),
			BPF_JMP_IMM(BPF_JEQ, R1, 3, 1),
			BPF_EXIT_INSN(),
			BPF_ALU32_IMM(BPF_MOV, R0, 1),
			BPF_EXIT_INSN(),
		पूर्ण,
		INTERNAL,
		अणु पूर्ण,
		अणु अणु 0, 1 पूर्ण पूर्ण,
	पूर्ण,
	/* BPF_JMP | BPF_JSET | BPF_K */
	अणु
		"JMP_JSET_K: if (0x3 & 0x2) return 1",
		.u.insns_पूर्णांक = अणु
			BPF_ALU32_IMM(BPF_MOV, R0, 0),
			BPF_LD_IMM64(R1, 3),
			BPF_JMP_IMM(BPF_JSET, R1, 2, 1),
			BPF_EXIT_INSN(),
			BPF_ALU32_IMM(BPF_MOV, R0, 1),
			BPF_EXIT_INSN(),
		पूर्ण,
		INTERNAL,
		अणु पूर्ण,
		अणु अणु 0, 1 पूर्ण पूर्ण,
	पूर्ण,
	अणु
		"JMP_JSET_K: if (0x3 & 0xffffffff) return 1",
		.u.insns_पूर्णांक = अणु
			BPF_ALU32_IMM(BPF_MOV, R0, 0),
			BPF_LD_IMM64(R1, 3),
			BPF_JMP_IMM(BPF_JSET, R1, 0xffffffff, 1),
			BPF_EXIT_INSN(),
			BPF_ALU32_IMM(BPF_MOV, R0, 1),
			BPF_EXIT_INSN(),
		पूर्ण,
		INTERNAL,
		अणु पूर्ण,
		अणु अणु 0, 1 पूर्ण पूर्ण,
	पूर्ण,
	/* BPF_JMP | BPF_JSGT | BPF_X */
	अणु
		"JMP_JSGT_X: Signed jump: if (-1 > -2) return 1",
		.u.insns_पूर्णांक = अणु
			BPF_ALU32_IMM(BPF_MOV, R0, 0),
			BPF_LD_IMM64(R1, -1),
			BPF_LD_IMM64(R2, -2),
			BPF_JMP_REG(BPF_JSGT, R1, R2, 1),
			BPF_EXIT_INSN(),
			BPF_ALU32_IMM(BPF_MOV, R0, 1),
			BPF_EXIT_INSN(),
		पूर्ण,
		INTERNAL,
		अणु पूर्ण,
		अणु अणु 0, 1 पूर्ण पूर्ण,
	पूर्ण,
	अणु
		"JMP_JSGT_X: Signed jump: if (-1 > -1) return 0",
		.u.insns_पूर्णांक = अणु
			BPF_ALU32_IMM(BPF_MOV, R0, 1),
			BPF_LD_IMM64(R1, -1),
			BPF_LD_IMM64(R2, -1),
			BPF_JMP_REG(BPF_JSGT, R1, R2, 1),
			BPF_EXIT_INSN(),
			BPF_ALU32_IMM(BPF_MOV, R0, 0),
			BPF_EXIT_INSN(),
		पूर्ण,
		INTERNAL,
		अणु पूर्ण,
		अणु अणु 0, 1 पूर्ण पूर्ण,
	पूर्ण,
	/* BPF_JMP | BPF_JSLT | BPF_X */
	अणु
		"JMP_JSLT_X: Signed jump: if (-2 < -1) return 1",
		.u.insns_पूर्णांक = अणु
			BPF_ALU32_IMM(BPF_MOV, R0, 0),
			BPF_LD_IMM64(R1, -1),
			BPF_LD_IMM64(R2, -2),
			BPF_JMP_REG(BPF_JSLT, R2, R1, 1),
			BPF_EXIT_INSN(),
			BPF_ALU32_IMM(BPF_MOV, R0, 1),
			BPF_EXIT_INSN(),
		पूर्ण,
		INTERNAL,
		अणु पूर्ण,
		अणु अणु 0, 1 पूर्ण पूर्ण,
	पूर्ण,
	अणु
		"JMP_JSLT_X: Signed jump: if (-1 < -1) return 0",
		.u.insns_पूर्णांक = अणु
			BPF_ALU32_IMM(BPF_MOV, R0, 1),
			BPF_LD_IMM64(R1, -1),
			BPF_LD_IMM64(R2, -1),
			BPF_JMP_REG(BPF_JSLT, R1, R2, 1),
			BPF_EXIT_INSN(),
			BPF_ALU32_IMM(BPF_MOV, R0, 0),
			BPF_EXIT_INSN(),
		पूर्ण,
		INTERNAL,
		अणु पूर्ण,
		अणु अणु 0, 1 पूर्ण पूर्ण,
	पूर्ण,
	/* BPF_JMP | BPF_JSGE | BPF_X */
	अणु
		"JMP_JSGE_X: Signed jump: if (-1 >= -2) return 1",
		.u.insns_पूर्णांक = अणु
			BPF_ALU32_IMM(BPF_MOV, R0, 0),
			BPF_LD_IMM64(R1, -1),
			BPF_LD_IMM64(R2, -2),
			BPF_JMP_REG(BPF_JSGE, R1, R2, 1),
			BPF_EXIT_INSN(),
			BPF_ALU32_IMM(BPF_MOV, R0, 1),
			BPF_EXIT_INSN(),
		पूर्ण,
		INTERNAL,
		अणु पूर्ण,
		अणु अणु 0, 1 पूर्ण पूर्ण,
	पूर्ण,
	अणु
		"JMP_JSGE_X: Signed jump: if (-1 >= -1) return 1",
		.u.insns_पूर्णांक = अणु
			BPF_ALU32_IMM(BPF_MOV, R0, 0),
			BPF_LD_IMM64(R1, -1),
			BPF_LD_IMM64(R2, -1),
			BPF_JMP_REG(BPF_JSGE, R1, R2, 1),
			BPF_EXIT_INSN(),
			BPF_ALU32_IMM(BPF_MOV, R0, 1),
			BPF_EXIT_INSN(),
		पूर्ण,
		INTERNAL,
		अणु पूर्ण,
		अणु अणु 0, 1 पूर्ण पूर्ण,
	पूर्ण,
	/* BPF_JMP | BPF_JSLE | BPF_X */
	अणु
		"JMP_JSLE_X: Signed jump: if (-2 <= -1) return 1",
		.u.insns_पूर्णांक = अणु
			BPF_ALU32_IMM(BPF_MOV, R0, 0),
			BPF_LD_IMM64(R1, -1),
			BPF_LD_IMM64(R2, -2),
			BPF_JMP_REG(BPF_JSLE, R2, R1, 1),
			BPF_EXIT_INSN(),
			BPF_ALU32_IMM(BPF_MOV, R0, 1),
			BPF_EXIT_INSN(),
		पूर्ण,
		INTERNAL,
		अणु पूर्ण,
		अणु अणु 0, 1 पूर्ण पूर्ण,
	पूर्ण,
	अणु
		"JMP_JSLE_X: Signed jump: if (-1 <= -1) return 1",
		.u.insns_पूर्णांक = अणु
			BPF_ALU32_IMM(BPF_MOV, R0, 0),
			BPF_LD_IMM64(R1, -1),
			BPF_LD_IMM64(R2, -1),
			BPF_JMP_REG(BPF_JSLE, R1, R2, 1),
			BPF_EXIT_INSN(),
			BPF_ALU32_IMM(BPF_MOV, R0, 1),
			BPF_EXIT_INSN(),
		पूर्ण,
		INTERNAL,
		अणु पूर्ण,
		अणु अणु 0, 1 पूर्ण पूर्ण,
	पूर्ण,
	/* BPF_JMP | BPF_JGT | BPF_X */
	अणु
		"JMP_JGT_X: if (3 > 2) return 1",
		.u.insns_पूर्णांक = अणु
			BPF_ALU32_IMM(BPF_MOV, R0, 0),
			BPF_LD_IMM64(R1, 3),
			BPF_LD_IMM64(R2, 2),
			BPF_JMP_REG(BPF_JGT, R1, R2, 1),
			BPF_EXIT_INSN(),
			BPF_ALU32_IMM(BPF_MOV, R0, 1),
			BPF_EXIT_INSN(),
		पूर्ण,
		INTERNAL,
		अणु पूर्ण,
		अणु अणु 0, 1 पूर्ण पूर्ण,
	पूर्ण,
	अणु
		"JMP_JGT_X: Unsigned jump: if (-1 > 1) return 1",
		.u.insns_पूर्णांक = अणु
			BPF_ALU32_IMM(BPF_MOV, R0, 0),
			BPF_LD_IMM64(R1, -1),
			BPF_LD_IMM64(R2, 1),
			BPF_JMP_REG(BPF_JGT, R1, R2, 1),
			BPF_EXIT_INSN(),
			BPF_ALU32_IMM(BPF_MOV, R0, 1),
			BPF_EXIT_INSN(),
		पूर्ण,
		INTERNAL,
		अणु पूर्ण,
		अणु अणु 0, 1 पूर्ण पूर्ण,
	पूर्ण,
	/* BPF_JMP | BPF_JLT | BPF_X */
	अणु
		"JMP_JLT_X: if (2 < 3) return 1",
		.u.insns_पूर्णांक = अणु
			BPF_ALU32_IMM(BPF_MOV, R0, 0),
			BPF_LD_IMM64(R1, 3),
			BPF_LD_IMM64(R2, 2),
			BPF_JMP_REG(BPF_JLT, R2, R1, 1),
			BPF_EXIT_INSN(),
			BPF_ALU32_IMM(BPF_MOV, R0, 1),
			BPF_EXIT_INSN(),
		पूर्ण,
		INTERNAL,
		अणु पूर्ण,
		अणु अणु 0, 1 पूर्ण पूर्ण,
	पूर्ण,
	अणु
		"JMP_JLT_X: Unsigned jump: if (1 < -1) return 1",
		.u.insns_पूर्णांक = अणु
			BPF_ALU32_IMM(BPF_MOV, R0, 0),
			BPF_LD_IMM64(R1, -1),
			BPF_LD_IMM64(R2, 1),
			BPF_JMP_REG(BPF_JLT, R2, R1, 1),
			BPF_EXIT_INSN(),
			BPF_ALU32_IMM(BPF_MOV, R0, 1),
			BPF_EXIT_INSN(),
		पूर्ण,
		INTERNAL,
		अणु पूर्ण,
		अणु अणु 0, 1 पूर्ण पूर्ण,
	पूर्ण,
	/* BPF_JMP | BPF_JGE | BPF_X */
	अणु
		"JMP_JGE_X: if (3 >= 2) return 1",
		.u.insns_पूर्णांक = अणु
			BPF_ALU32_IMM(BPF_MOV, R0, 0),
			BPF_LD_IMM64(R1, 3),
			BPF_LD_IMM64(R2, 2),
			BPF_JMP_REG(BPF_JGE, R1, R2, 1),
			BPF_EXIT_INSN(),
			BPF_ALU32_IMM(BPF_MOV, R0, 1),
			BPF_EXIT_INSN(),
		पूर्ण,
		INTERNAL,
		अणु पूर्ण,
		अणु अणु 0, 1 पूर्ण पूर्ण,
	पूर्ण,
	अणु
		"JMP_JGE_X: if (3 >= 3) return 1",
		.u.insns_पूर्णांक = अणु
			BPF_ALU32_IMM(BPF_MOV, R0, 0),
			BPF_LD_IMM64(R1, 3),
			BPF_LD_IMM64(R2, 3),
			BPF_JMP_REG(BPF_JGE, R1, R2, 1),
			BPF_EXIT_INSN(),
			BPF_ALU32_IMM(BPF_MOV, R0, 1),
			BPF_EXIT_INSN(),
		पूर्ण,
		INTERNAL,
		अणु पूर्ण,
		अणु अणु 0, 1 पूर्ण पूर्ण,
	पूर्ण,
	/* BPF_JMP | BPF_JLE | BPF_X */
	अणु
		"JMP_JLE_X: if (2 <= 3) return 1",
		.u.insns_पूर्णांक = अणु
			BPF_ALU32_IMM(BPF_MOV, R0, 0),
			BPF_LD_IMM64(R1, 3),
			BPF_LD_IMM64(R2, 2),
			BPF_JMP_REG(BPF_JLE, R2, R1, 1),
			BPF_EXIT_INSN(),
			BPF_ALU32_IMM(BPF_MOV, R0, 1),
			BPF_EXIT_INSN(),
		पूर्ण,
		INTERNAL,
		अणु पूर्ण,
		अणु अणु 0, 1 पूर्ण पूर्ण,
	पूर्ण,
	अणु
		"JMP_JLE_X: if (3 <= 3) return 1",
		.u.insns_पूर्णांक = अणु
			BPF_ALU32_IMM(BPF_MOV, R0, 0),
			BPF_LD_IMM64(R1, 3),
			BPF_LD_IMM64(R2, 3),
			BPF_JMP_REG(BPF_JLE, R1, R2, 1),
			BPF_EXIT_INSN(),
			BPF_ALU32_IMM(BPF_MOV, R0, 1),
			BPF_EXIT_INSN(),
		पूर्ण,
		INTERNAL,
		अणु पूर्ण,
		अणु अणु 0, 1 पूर्ण पूर्ण,
	पूर्ण,
	अणु
		/* Mainly testing JIT + imm64 here. */
		"JMP_JGE_X: ldimm64 test 1",
		.u.insns_पूर्णांक = अणु
			BPF_ALU32_IMM(BPF_MOV, R0, 0),
			BPF_LD_IMM64(R1, 3),
			BPF_LD_IMM64(R2, 2),
			BPF_JMP_REG(BPF_JGE, R1, R2, 2),
			BPF_LD_IMM64(R0, 0xffffffffffffffffULL),
			BPF_LD_IMM64(R0, 0xeeeeeeeeeeeeeeeeULL),
			BPF_EXIT_INSN(),
		पूर्ण,
		INTERNAL,
		अणु पूर्ण,
		अणु अणु 0, 0xeeeeeeeeU पूर्ण पूर्ण,
	पूर्ण,
	अणु
		"JMP_JGE_X: ldimm64 test 2",
		.u.insns_पूर्णांक = अणु
			BPF_ALU32_IMM(BPF_MOV, R0, 0),
			BPF_LD_IMM64(R1, 3),
			BPF_LD_IMM64(R2, 2),
			BPF_JMP_REG(BPF_JGE, R1, R2, 0),
			BPF_LD_IMM64(R0, 0xffffffffffffffffULL),
			BPF_EXIT_INSN(),
		पूर्ण,
		INTERNAL,
		अणु पूर्ण,
		अणु अणु 0, 0xffffffffU पूर्ण पूर्ण,
	पूर्ण,
	अणु
		"JMP_JGE_X: ldimm64 test 3",
		.u.insns_पूर्णांक = अणु
			BPF_ALU32_IMM(BPF_MOV, R0, 1),
			BPF_LD_IMM64(R1, 3),
			BPF_LD_IMM64(R2, 2),
			BPF_JMP_REG(BPF_JGE, R1, R2, 4),
			BPF_LD_IMM64(R0, 0xffffffffffffffffULL),
			BPF_LD_IMM64(R0, 0xeeeeeeeeeeeeeeeeULL),
			BPF_EXIT_INSN(),
		पूर्ण,
		INTERNAL,
		अणु पूर्ण,
		अणु अणु 0, 1 पूर्ण पूर्ण,
	पूर्ण,
	अणु
		"JMP_JLE_X: ldimm64 test 1",
		.u.insns_पूर्णांक = अणु
			BPF_ALU32_IMM(BPF_MOV, R0, 0),
			BPF_LD_IMM64(R1, 3),
			BPF_LD_IMM64(R2, 2),
			BPF_JMP_REG(BPF_JLE, R2, R1, 2),
			BPF_LD_IMM64(R0, 0xffffffffffffffffULL),
			BPF_LD_IMM64(R0, 0xeeeeeeeeeeeeeeeeULL),
			BPF_EXIT_INSN(),
		पूर्ण,
		INTERNAL,
		अणु पूर्ण,
		अणु अणु 0, 0xeeeeeeeeU पूर्ण पूर्ण,
	पूर्ण,
	अणु
		"JMP_JLE_X: ldimm64 test 2",
		.u.insns_पूर्णांक = अणु
			BPF_ALU32_IMM(BPF_MOV, R0, 0),
			BPF_LD_IMM64(R1, 3),
			BPF_LD_IMM64(R2, 2),
			BPF_JMP_REG(BPF_JLE, R2, R1, 0),
			BPF_LD_IMM64(R0, 0xffffffffffffffffULL),
			BPF_EXIT_INSN(),
		पूर्ण,
		INTERNAL,
		अणु पूर्ण,
		अणु अणु 0, 0xffffffffU पूर्ण पूर्ण,
	पूर्ण,
	अणु
		"JMP_JLE_X: ldimm64 test 3",
		.u.insns_पूर्णांक = अणु
			BPF_ALU32_IMM(BPF_MOV, R0, 1),
			BPF_LD_IMM64(R1, 3),
			BPF_LD_IMM64(R2, 2),
			BPF_JMP_REG(BPF_JLE, R2, R1, 4),
			BPF_LD_IMM64(R0, 0xffffffffffffffffULL),
			BPF_LD_IMM64(R0, 0xeeeeeeeeeeeeeeeeULL),
			BPF_EXIT_INSN(),
		पूर्ण,
		INTERNAL,
		अणु पूर्ण,
		अणु अणु 0, 1 पूर्ण पूर्ण,
	पूर्ण,
	/* BPF_JMP | BPF_JNE | BPF_X */
	अणु
		"JMP_JNE_X: if (3 != 2) return 1",
		.u.insns_पूर्णांक = अणु
			BPF_ALU32_IMM(BPF_MOV, R0, 0),
			BPF_LD_IMM64(R1, 3),
			BPF_LD_IMM64(R2, 2),
			BPF_JMP_REG(BPF_JNE, R1, R2, 1),
			BPF_EXIT_INSN(),
			BPF_ALU32_IMM(BPF_MOV, R0, 1),
			BPF_EXIT_INSN(),
		पूर्ण,
		INTERNAL,
		अणु पूर्ण,
		अणु अणु 0, 1 पूर्ण पूर्ण,
	पूर्ण,
	/* BPF_JMP | BPF_JEQ | BPF_X */
	अणु
		"JMP_JEQ_X: if (3 == 3) return 1",
		.u.insns_पूर्णांक = अणु
			BPF_ALU32_IMM(BPF_MOV, R0, 0),
			BPF_LD_IMM64(R1, 3),
			BPF_LD_IMM64(R2, 3),
			BPF_JMP_REG(BPF_JEQ, R1, R2, 1),
			BPF_EXIT_INSN(),
			BPF_ALU32_IMM(BPF_MOV, R0, 1),
			BPF_EXIT_INSN(),
		पूर्ण,
		INTERNAL,
		अणु पूर्ण,
		अणु अणु 0, 1 पूर्ण पूर्ण,
	पूर्ण,
	/* BPF_JMP | BPF_JSET | BPF_X */
	अणु
		"JMP_JSET_X: if (0x3 & 0x2) return 1",
		.u.insns_पूर्णांक = अणु
			BPF_ALU32_IMM(BPF_MOV, R0, 0),
			BPF_LD_IMM64(R1, 3),
			BPF_LD_IMM64(R2, 2),
			BPF_JMP_REG(BPF_JSET, R1, R2, 1),
			BPF_EXIT_INSN(),
			BPF_ALU32_IMM(BPF_MOV, R0, 1),
			BPF_EXIT_INSN(),
		पूर्ण,
		INTERNAL,
		अणु पूर्ण,
		अणु अणु 0, 1 पूर्ण पूर्ण,
	पूर्ण,
	अणु
		"JMP_JSET_X: if (0x3 & 0xffffffff) return 1",
		.u.insns_पूर्णांक = अणु
			BPF_ALU32_IMM(BPF_MOV, R0, 0),
			BPF_LD_IMM64(R1, 3),
			BPF_LD_IMM64(R2, 0xffffffff),
			BPF_JMP_REG(BPF_JSET, R1, R2, 1),
			BPF_EXIT_INSN(),
			BPF_ALU32_IMM(BPF_MOV, R0, 1),
			BPF_EXIT_INSN(),
		पूर्ण,
		INTERNAL,
		अणु पूर्ण,
		अणु अणु 0, 1 पूर्ण पूर्ण,
	पूर्ण,
	अणु
		"JMP_JA: Jump, gap, jump, ...",
		अणु पूर्ण,
		CLASSIC | FLAG_NO_DATA,
		अणु पूर्ण,
		अणु अणु 0, 0xababcbac पूर्ण पूर्ण,
		.fill_helper = bpf_fill_ja,
	पूर्ण,
	अणु	/* Mainly checking JIT here. */
		"BPF_MAXINSNS: Maximum possible literals",
		अणु पूर्ण,
		CLASSIC | FLAG_NO_DATA,
		अणु पूर्ण,
		अणु अणु 0, 0xffffffff पूर्ण पूर्ण,
		.fill_helper = bpf_fill_maxinsns1,
	पूर्ण,
	अणु	/* Mainly checking JIT here. */
		"BPF_MAXINSNS: Single literal",
		अणु पूर्ण,
		CLASSIC | FLAG_NO_DATA,
		अणु पूर्ण,
		अणु अणु 0, 0xfefefefe पूर्ण पूर्ण,
		.fill_helper = bpf_fill_maxinsns2,
	पूर्ण,
	अणु	/* Mainly checking JIT here. */
		"BPF_MAXINSNS: Run/add until end",
		अणु पूर्ण,
		CLASSIC | FLAG_NO_DATA,
		अणु पूर्ण,
		अणु अणु 0, 0x947bf368 पूर्ण पूर्ण,
		.fill_helper = bpf_fill_maxinsns3,
	पूर्ण,
	अणु
		"BPF_MAXINSNS: Too many instructions",
		अणु पूर्ण,
		CLASSIC | FLAG_NO_DATA | FLAG_EXPECTED_FAIL,
		अणु पूर्ण,
		अणु पूर्ण,
		.fill_helper = bpf_fill_maxinsns4,
		.expected_errcode = -EINVAL,
	पूर्ण,
	अणु	/* Mainly checking JIT here. */
		"BPF_MAXINSNS: Very long jump",
		अणु पूर्ण,
		CLASSIC | FLAG_NO_DATA,
		अणु पूर्ण,
		अणु अणु 0, 0xabababab पूर्ण पूर्ण,
		.fill_helper = bpf_fill_maxinsns5,
	पूर्ण,
	अणु	/* Mainly checking JIT here. */
		"BPF_MAXINSNS: Ctx heavy transformations",
		अणु पूर्ण,
		CLASSIC,
		अणु पूर्ण,
		अणु
			अणु  1, SKB_VLAN_PRESENT पूर्ण,
			अणु 10, SKB_VLAN_PRESENT पूर्ण
		पूर्ण,
		.fill_helper = bpf_fill_maxinsns6,
	पूर्ण,
	अणु	/* Mainly checking JIT here. */
		"BPF_MAXINSNS: Call heavy transformations",
		अणु पूर्ण,
		CLASSIC | FLAG_NO_DATA,
		अणु पूर्ण,
		अणु अणु 1, 0 पूर्ण, अणु 10, 0 पूर्ण पूर्ण,
		.fill_helper = bpf_fill_maxinsns7,
	पूर्ण,
	अणु	/* Mainly checking JIT here. */
		"BPF_MAXINSNS: Jump heavy test",
		अणु पूर्ण,
		CLASSIC | FLAG_NO_DATA,
		अणु पूर्ण,
		अणु अणु 0, 0xffffffff पूर्ण पूर्ण,
		.fill_helper = bpf_fill_maxinsns8,
	पूर्ण,
	अणु	/* Mainly checking JIT here. */
		"BPF_MAXINSNS: Very long jump backwards",
		अणु पूर्ण,
		INTERNAL | FLAG_NO_DATA,
		अणु पूर्ण,
		अणु अणु 0, 0xcbababab पूर्ण पूर्ण,
		.fill_helper = bpf_fill_maxinsns9,
	पूर्ण,
	अणु	/* Mainly checking JIT here. */
		"BPF_MAXINSNS: Edge hopping nuthouse",
		अणु पूर्ण,
		INTERNAL | FLAG_NO_DATA,
		अणु पूर्ण,
		अणु अणु 0, 0xabababac पूर्ण पूर्ण,
		.fill_helper = bpf_fill_maxinsns10,
	पूर्ण,
	अणु
		"BPF_MAXINSNS: Jump, gap, jump, ...",
		अणु पूर्ण,
		CLASSIC | FLAG_NO_DATA,
		अणु पूर्ण,
		अणु अणु 0, 0xababcbac पूर्ण पूर्ण,
		.fill_helper = bpf_fill_maxinsns11,
	पूर्ण,
	अणु
		"BPF_MAXINSNS: jump over MSH",
		अणु पूर्ण,
		CLASSIC | FLAG_EXPECTED_FAIL,
		अणु 0xfa, 0xfb, 0xfc, 0xfd, पूर्ण,
		अणु अणु 4, 0xabababab पूर्ण पूर्ण,
		.fill_helper = bpf_fill_maxinsns12,
		.expected_errcode = -EINVAL,
	पूर्ण,
	अणु
		"BPF_MAXINSNS: exec all MSH",
		अणु पूर्ण,
		CLASSIC,
		अणु 0xfa, 0xfb, 0xfc, 0xfd, पूर्ण,
		अणु अणु 4, 0xababab83 पूर्ण पूर्ण,
		.fill_helper = bpf_fill_maxinsns13,
	पूर्ण,
	अणु
		"BPF_MAXINSNS: ld_abs+get_processor_id",
		अणु पूर्ण,
		CLASSIC,
		अणु पूर्ण,
		अणु अणु 1, 0xbee पूर्ण पूर्ण,
		.fill_helper = bpf_fill_ld_असल_get_processor_id,
	पूर्ण,
	/*
	 * LD_IND / LD_ABS on fragmented SKBs
	 */
	अणु
		"LD_IND byte frag",
		.u.insns = अणु
			BPF_STMT(BPF_LDX | BPF_IMM, 0x40),
			BPF_STMT(BPF_LD | BPF_IND | BPF_B, 0x0),
			BPF_STMT(BPF_RET | BPF_A, 0x0),
		पूर्ण,
		CLASSIC | FLAG_SKB_FRAG,
		अणु पूर्ण,
		अणु अणु0x40, 0x42पूर्ण पूर्ण,
		.frag_data = अणु
			0x42, 0x00, 0x00, 0x00,
			0x43, 0x44, 0x00, 0x00,
			0x21, 0x07, 0x19, 0x83,
		पूर्ण,
	पूर्ण,
	अणु
		"LD_IND halfword frag",
		.u.insns = अणु
			BPF_STMT(BPF_LDX | BPF_IMM, 0x40),
			BPF_STMT(BPF_LD | BPF_IND | BPF_H, 0x4),
			BPF_STMT(BPF_RET | BPF_A, 0x0),
		पूर्ण,
		CLASSIC | FLAG_SKB_FRAG,
		अणु पूर्ण,
		अणु अणु0x40, 0x4344पूर्ण पूर्ण,
		.frag_data = अणु
			0x42, 0x00, 0x00, 0x00,
			0x43, 0x44, 0x00, 0x00,
			0x21, 0x07, 0x19, 0x83,
		पूर्ण,
	पूर्ण,
	अणु
		"LD_IND word frag",
		.u.insns = अणु
			BPF_STMT(BPF_LDX | BPF_IMM, 0x40),
			BPF_STMT(BPF_LD | BPF_IND | BPF_W, 0x8),
			BPF_STMT(BPF_RET | BPF_A, 0x0),
		पूर्ण,
		CLASSIC | FLAG_SKB_FRAG,
		अणु पूर्ण,
		अणु अणु0x40, 0x21071983पूर्ण पूर्ण,
		.frag_data = अणु
			0x42, 0x00, 0x00, 0x00,
			0x43, 0x44, 0x00, 0x00,
			0x21, 0x07, 0x19, 0x83,
		पूर्ण,
	पूर्ण,
	अणु
		"LD_IND halfword mixed head/frag",
		.u.insns = अणु
			BPF_STMT(BPF_LDX | BPF_IMM, 0x40),
			BPF_STMT(BPF_LD | BPF_IND | BPF_H, -0x1),
			BPF_STMT(BPF_RET | BPF_A, 0x0),
		पूर्ण,
		CLASSIC | FLAG_SKB_FRAG,
		अणु [0x3e] = 0x25, [0x3f] = 0x05, पूर्ण,
		अणु अणु0x40, 0x0519पूर्ण पूर्ण,
		.frag_data = अणु 0x19, 0x82 पूर्ण,
	पूर्ण,
	अणु
		"LD_IND word mixed head/frag",
		.u.insns = अणु
			BPF_STMT(BPF_LDX | BPF_IMM, 0x40),
			BPF_STMT(BPF_LD | BPF_IND | BPF_W, -0x2),
			BPF_STMT(BPF_RET | BPF_A, 0x0),
		पूर्ण,
		CLASSIC | FLAG_SKB_FRAG,
		अणु [0x3e] = 0x25, [0x3f] = 0x05, पूर्ण,
		अणु अणु0x40, 0x25051982पूर्ण पूर्ण,
		.frag_data = अणु 0x19, 0x82 पूर्ण,
	पूर्ण,
	अणु
		"LD_ABS byte frag",
		.u.insns = अणु
			BPF_STMT(BPF_LD | BPF_ABS | BPF_B, 0x40),
			BPF_STMT(BPF_RET | BPF_A, 0x0),
		पूर्ण,
		CLASSIC | FLAG_SKB_FRAG,
		अणु पूर्ण,
		अणु अणु0x40, 0x42पूर्ण पूर्ण,
		.frag_data = अणु
			0x42, 0x00, 0x00, 0x00,
			0x43, 0x44, 0x00, 0x00,
			0x21, 0x07, 0x19, 0x83,
		पूर्ण,
	पूर्ण,
	अणु
		"LD_ABS halfword frag",
		.u.insns = अणु
			BPF_STMT(BPF_LD | BPF_ABS | BPF_H, 0x44),
			BPF_STMT(BPF_RET | BPF_A, 0x0),
		पूर्ण,
		CLASSIC | FLAG_SKB_FRAG,
		अणु पूर्ण,
		अणु अणु0x40, 0x4344पूर्ण पूर्ण,
		.frag_data = अणु
			0x42, 0x00, 0x00, 0x00,
			0x43, 0x44, 0x00, 0x00,
			0x21, 0x07, 0x19, 0x83,
		पूर्ण,
	पूर्ण,
	अणु
		"LD_ABS word frag",
		.u.insns = अणु
			BPF_STMT(BPF_LD | BPF_ABS | BPF_W, 0x48),
			BPF_STMT(BPF_RET | BPF_A, 0x0),
		पूर्ण,
		CLASSIC | FLAG_SKB_FRAG,
		अणु पूर्ण,
		अणु अणु0x40, 0x21071983पूर्ण पूर्ण,
		.frag_data = अणु
			0x42, 0x00, 0x00, 0x00,
			0x43, 0x44, 0x00, 0x00,
			0x21, 0x07, 0x19, 0x83,
		पूर्ण,
	पूर्ण,
	अणु
		"LD_ABS halfword mixed head/frag",
		.u.insns = अणु
			BPF_STMT(BPF_LD | BPF_ABS | BPF_H, 0x3f),
			BPF_STMT(BPF_RET | BPF_A, 0x0),
		पूर्ण,
		CLASSIC | FLAG_SKB_FRAG,
		अणु [0x3e] = 0x25, [0x3f] = 0x05, पूर्ण,
		अणु अणु0x40, 0x0519पूर्ण पूर्ण,
		.frag_data = अणु 0x19, 0x82 पूर्ण,
	पूर्ण,
	अणु
		"LD_ABS word mixed head/frag",
		.u.insns = अणु
			BPF_STMT(BPF_LD | BPF_ABS | BPF_W, 0x3e),
			BPF_STMT(BPF_RET | BPF_A, 0x0),
		पूर्ण,
		CLASSIC | FLAG_SKB_FRAG,
		अणु [0x3e] = 0x25, [0x3f] = 0x05, पूर्ण,
		अणु अणु0x40, 0x25051982पूर्ण पूर्ण,
		.frag_data = अणु 0x19, 0x82 पूर्ण,
	पूर्ण,
	/*
	 * LD_IND / LD_ABS on non fragmented SKBs
	 */
	अणु
		/*
		 * this tests that the JIT/पूर्णांकerpreter correctly resets X
		 * beक्रमe using it in an LD_IND inकाष्ठाion.
		 */
		"LD_IND byte default X",
		.u.insns = अणु
			BPF_STMT(BPF_LD | BPF_IND | BPF_B, 0x1),
			BPF_STMT(BPF_RET | BPF_A, 0x0),
		पूर्ण,
		CLASSIC,
		अणु [0x1] = 0x42 पूर्ण,
		अणु अणु0x40, 0x42 पूर्ण पूर्ण,
	पूर्ण,
	अणु
		"LD_IND byte positive offset",
		.u.insns = अणु
			BPF_STMT(BPF_LDX | BPF_IMM, 0x3e),
			BPF_STMT(BPF_LD | BPF_IND | BPF_B, 0x1),
			BPF_STMT(BPF_RET | BPF_A, 0x0),
		पूर्ण,
		CLASSIC,
		अणु [0x3c] = 0x25, [0x3d] = 0x05,  [0x3e] = 0x19, [0x3f] = 0x82 पूर्ण,
		अणु अणु0x40, 0x82 पूर्ण पूर्ण,
	पूर्ण,
	अणु
		"LD_IND byte negative offset",
		.u.insns = अणु
			BPF_STMT(BPF_LDX | BPF_IMM, 0x3e),
			BPF_STMT(BPF_LD | BPF_IND | BPF_B, -0x1),
			BPF_STMT(BPF_RET | BPF_A, 0x0),
		पूर्ण,
		CLASSIC,
		अणु [0x3c] = 0x25, [0x3d] = 0x05,  [0x3e] = 0x19, [0x3f] = 0x82 पूर्ण,
		अणु अणु0x40, 0x05 पूर्ण पूर्ण,
	पूर्ण,
	अणु
		"LD_IND byte positive offset, all ff",
		.u.insns = अणु
			BPF_STMT(BPF_LDX | BPF_IMM, 0x3e),
			BPF_STMT(BPF_LD | BPF_IND | BPF_B, 0x1),
			BPF_STMT(BPF_RET | BPF_A, 0x0),
		पूर्ण,
		CLASSIC,
		अणु [0x3c] = 0xff, [0x3d] = 0xff,  [0x3e] = 0xff, [0x3f] = 0xff पूर्ण,
		अणु अणु0x40, 0xff पूर्ण पूर्ण,
	पूर्ण,
	अणु
		"LD_IND byte positive offset, out of bounds",
		.u.insns = अणु
			BPF_STMT(BPF_LDX | BPF_IMM, 0x3e),
			BPF_STMT(BPF_LD | BPF_IND | BPF_B, 0x1),
			BPF_STMT(BPF_RET | BPF_A, 0x0),
		पूर्ण,
		CLASSIC,
		अणु [0x3c] = 0x25, [0x3d] = 0x05,  [0x3e] = 0x19, [0x3f] = 0x82 पूर्ण,
		अणु अणु0x3f, 0 पूर्ण, पूर्ण,
	पूर्ण,
	अणु
		"LD_IND byte negative offset, out of bounds",
		.u.insns = अणु
			BPF_STMT(BPF_LDX | BPF_IMM, 0x3e),
			BPF_STMT(BPF_LD | BPF_IND | BPF_B, -0x3f),
			BPF_STMT(BPF_RET | BPF_A, 0x0),
		पूर्ण,
		CLASSIC,
		अणु [0x3c] = 0x25, [0x3d] = 0x05,  [0x3e] = 0x19, [0x3f] = 0x82 पूर्ण,
		अणु अणु0x3f, 0 पूर्ण पूर्ण,
	पूर्ण,
	अणु
		"LD_IND byte negative offset, multiple calls",
		.u.insns = अणु
			BPF_STMT(BPF_LDX | BPF_IMM, 0x3b),
			BPF_STMT(BPF_LD | BPF_IND | BPF_B, SKF_LL_OFF + 1),
			BPF_STMT(BPF_LD | BPF_IND | BPF_B, SKF_LL_OFF + 2),
			BPF_STMT(BPF_LD | BPF_IND | BPF_B, SKF_LL_OFF + 3),
			BPF_STMT(BPF_LD | BPF_IND | BPF_B, SKF_LL_OFF + 4),
			BPF_STMT(BPF_RET | BPF_A, 0x0),
		पूर्ण,
		CLASSIC,
		अणु [0x3c] = 0x25, [0x3d] = 0x05,  [0x3e] = 0x19, [0x3f] = 0x82 पूर्ण,
		अणु अणु0x40, 0x82 पूर्ण, पूर्ण,
	पूर्ण,
	अणु
		"LD_IND halfword positive offset",
		.u.insns = अणु
			BPF_STMT(BPF_LDX | BPF_IMM, 0x20),
			BPF_STMT(BPF_LD | BPF_IND | BPF_H, 0x2),
			BPF_STMT(BPF_RET | BPF_A, 0x0),
		पूर्ण,
		CLASSIC,
		अणु
			[0x1c] = 0xaa, [0x1d] = 0x55,
			[0x1e] = 0xbb, [0x1f] = 0x66,
			[0x20] = 0xcc, [0x21] = 0x77,
			[0x22] = 0xdd, [0x23] = 0x88,
		पूर्ण,
		अणु अणु0x40, 0xdd88 पूर्ण पूर्ण,
	पूर्ण,
	अणु
		"LD_IND halfword negative offset",
		.u.insns = अणु
			BPF_STMT(BPF_LDX | BPF_IMM, 0x20),
			BPF_STMT(BPF_LD | BPF_IND | BPF_H, -0x2),
			BPF_STMT(BPF_RET | BPF_A, 0x0),
		पूर्ण,
		CLASSIC,
		अणु
			[0x1c] = 0xaa, [0x1d] = 0x55,
			[0x1e] = 0xbb, [0x1f] = 0x66,
			[0x20] = 0xcc, [0x21] = 0x77,
			[0x22] = 0xdd, [0x23] = 0x88,
		पूर्ण,
		अणु अणु0x40, 0xbb66 पूर्ण पूर्ण,
	पूर्ण,
	अणु
		"LD_IND halfword unaligned",
		.u.insns = अणु
			BPF_STMT(BPF_LDX | BPF_IMM, 0x20),
			BPF_STMT(BPF_LD | BPF_IND | BPF_H, -0x1),
			BPF_STMT(BPF_RET | BPF_A, 0x0),
		पूर्ण,
		CLASSIC,
		अणु
			[0x1c] = 0xaa, [0x1d] = 0x55,
			[0x1e] = 0xbb, [0x1f] = 0x66,
			[0x20] = 0xcc, [0x21] = 0x77,
			[0x22] = 0xdd, [0x23] = 0x88,
		पूर्ण,
		अणु अणु0x40, 0x66cc पूर्ण पूर्ण,
	पूर्ण,
	अणु
		"LD_IND halfword positive offset, all ff",
		.u.insns = अणु
			BPF_STMT(BPF_LDX | BPF_IMM, 0x3d),
			BPF_STMT(BPF_LD | BPF_IND | BPF_H, 0x1),
			BPF_STMT(BPF_RET | BPF_A, 0x0),
		पूर्ण,
		CLASSIC,
		अणु [0x3c] = 0xff, [0x3d] = 0xff,  [0x3e] = 0xff, [0x3f] = 0xff पूर्ण,
		अणु अणु0x40, 0xffff पूर्ण पूर्ण,
	पूर्ण,
	अणु
		"LD_IND halfword positive offset, out of bounds",
		.u.insns = अणु
			BPF_STMT(BPF_LDX | BPF_IMM, 0x3e),
			BPF_STMT(BPF_LD | BPF_IND | BPF_H, 0x1),
			BPF_STMT(BPF_RET | BPF_A, 0x0),
		पूर्ण,
		CLASSIC,
		अणु [0x3c] = 0x25, [0x3d] = 0x05,  [0x3e] = 0x19, [0x3f] = 0x82 पूर्ण,
		अणु अणु0x3f, 0 पूर्ण, पूर्ण,
	पूर्ण,
	अणु
		"LD_IND halfword negative offset, out of bounds",
		.u.insns = अणु
			BPF_STMT(BPF_LDX | BPF_IMM, 0x3e),
			BPF_STMT(BPF_LD | BPF_IND | BPF_H, -0x3f),
			BPF_STMT(BPF_RET | BPF_A, 0x0),
		पूर्ण,
		CLASSIC,
		अणु [0x3c] = 0x25, [0x3d] = 0x05,  [0x3e] = 0x19, [0x3f] = 0x82 पूर्ण,
		अणु अणु0x3f, 0 पूर्ण पूर्ण,
	पूर्ण,
	अणु
		"LD_IND word positive offset",
		.u.insns = अणु
			BPF_STMT(BPF_LDX | BPF_IMM, 0x20),
			BPF_STMT(BPF_LD | BPF_IND | BPF_W, 0x4),
			BPF_STMT(BPF_RET | BPF_A, 0x0),
		पूर्ण,
		CLASSIC,
		अणु
			[0x1c] = 0xaa, [0x1d] = 0x55,
			[0x1e] = 0xbb, [0x1f] = 0x66,
			[0x20] = 0xcc, [0x21] = 0x77,
			[0x22] = 0xdd, [0x23] = 0x88,
			[0x24] = 0xee, [0x25] = 0x99,
			[0x26] = 0xff, [0x27] = 0xaa,
		पूर्ण,
		अणु अणु0x40, 0xee99ffaa पूर्ण पूर्ण,
	पूर्ण,
	अणु
		"LD_IND word negative offset",
		.u.insns = अणु
			BPF_STMT(BPF_LDX | BPF_IMM, 0x20),
			BPF_STMT(BPF_LD | BPF_IND | BPF_W, -0x4),
			BPF_STMT(BPF_RET | BPF_A, 0x0),
		पूर्ण,
		CLASSIC,
		अणु
			[0x1c] = 0xaa, [0x1d] = 0x55,
			[0x1e] = 0xbb, [0x1f] = 0x66,
			[0x20] = 0xcc, [0x21] = 0x77,
			[0x22] = 0xdd, [0x23] = 0x88,
			[0x24] = 0xee, [0x25] = 0x99,
			[0x26] = 0xff, [0x27] = 0xaa,
		पूर्ण,
		अणु अणु0x40, 0xaa55bb66 पूर्ण पूर्ण,
	पूर्ण,
	अणु
		"LD_IND word unaligned (addr & 3 == 2)",
		.u.insns = अणु
			BPF_STMT(BPF_LDX | BPF_IMM, 0x20),
			BPF_STMT(BPF_LD | BPF_IND | BPF_W, -0x2),
			BPF_STMT(BPF_RET | BPF_A, 0x0),
		पूर्ण,
		CLASSIC,
		अणु
			[0x1c] = 0xaa, [0x1d] = 0x55,
			[0x1e] = 0xbb, [0x1f] = 0x66,
			[0x20] = 0xcc, [0x21] = 0x77,
			[0x22] = 0xdd, [0x23] = 0x88,
			[0x24] = 0xee, [0x25] = 0x99,
			[0x26] = 0xff, [0x27] = 0xaa,
		पूर्ण,
		अणु अणु0x40, 0xbb66cc77 पूर्ण पूर्ण,
	पूर्ण,
	अणु
		"LD_IND word unaligned (addr & 3 == 1)",
		.u.insns = अणु
			BPF_STMT(BPF_LDX | BPF_IMM, 0x20),
			BPF_STMT(BPF_LD | BPF_IND | BPF_W, -0x3),
			BPF_STMT(BPF_RET | BPF_A, 0x0),
		पूर्ण,
		CLASSIC,
		अणु
			[0x1c] = 0xaa, [0x1d] = 0x55,
			[0x1e] = 0xbb, [0x1f] = 0x66,
			[0x20] = 0xcc, [0x21] = 0x77,
			[0x22] = 0xdd, [0x23] = 0x88,
			[0x24] = 0xee, [0x25] = 0x99,
			[0x26] = 0xff, [0x27] = 0xaa,
		पूर्ण,
		अणु अणु0x40, 0x55bb66cc पूर्ण पूर्ण,
	पूर्ण,
	अणु
		"LD_IND word unaligned (addr & 3 == 3)",
		.u.insns = अणु
			BPF_STMT(BPF_LDX | BPF_IMM, 0x20),
			BPF_STMT(BPF_LD | BPF_IND | BPF_W, -0x1),
			BPF_STMT(BPF_RET | BPF_A, 0x0),
		पूर्ण,
		CLASSIC,
		अणु
			[0x1c] = 0xaa, [0x1d] = 0x55,
			[0x1e] = 0xbb, [0x1f] = 0x66,
			[0x20] = 0xcc, [0x21] = 0x77,
			[0x22] = 0xdd, [0x23] = 0x88,
			[0x24] = 0xee, [0x25] = 0x99,
			[0x26] = 0xff, [0x27] = 0xaa,
		पूर्ण,
		अणु अणु0x40, 0x66cc77dd पूर्ण पूर्ण,
	पूर्ण,
	अणु
		"LD_IND word positive offset, all ff",
		.u.insns = अणु
			BPF_STMT(BPF_LDX | BPF_IMM, 0x3b),
			BPF_STMT(BPF_LD | BPF_IND | BPF_W, 0x1),
			BPF_STMT(BPF_RET | BPF_A, 0x0),
		पूर्ण,
		CLASSIC,
		अणु [0x3c] = 0xff, [0x3d] = 0xff,  [0x3e] = 0xff, [0x3f] = 0xff पूर्ण,
		अणु अणु0x40, 0xffffffff पूर्ण पूर्ण,
	पूर्ण,
	अणु
		"LD_IND word positive offset, out of bounds",
		.u.insns = अणु
			BPF_STMT(BPF_LDX | BPF_IMM, 0x3e),
			BPF_STMT(BPF_LD | BPF_IND | BPF_W, 0x1),
			BPF_STMT(BPF_RET | BPF_A, 0x0),
		पूर्ण,
		CLASSIC,
		अणु [0x3c] = 0x25, [0x3d] = 0x05,  [0x3e] = 0x19, [0x3f] = 0x82 पूर्ण,
		अणु अणु0x3f, 0 पूर्ण, पूर्ण,
	पूर्ण,
	अणु
		"LD_IND word negative offset, out of bounds",
		.u.insns = अणु
			BPF_STMT(BPF_LDX | BPF_IMM, 0x3e),
			BPF_STMT(BPF_LD | BPF_IND | BPF_W, -0x3f),
			BPF_STMT(BPF_RET | BPF_A, 0x0),
		पूर्ण,
		CLASSIC,
		अणु [0x3c] = 0x25, [0x3d] = 0x05,  [0x3e] = 0x19, [0x3f] = 0x82 पूर्ण,
		अणु अणु0x3f, 0 पूर्ण पूर्ण,
	पूर्ण,
	अणु
		"LD_ABS byte",
		.u.insns = अणु
			BPF_STMT(BPF_LD | BPF_ABS | BPF_B, 0x20),
			BPF_STMT(BPF_RET | BPF_A, 0x0),
		पूर्ण,
		CLASSIC,
		अणु
			[0x1c] = 0xaa, [0x1d] = 0x55,
			[0x1e] = 0xbb, [0x1f] = 0x66,
			[0x20] = 0xcc, [0x21] = 0x77,
			[0x22] = 0xdd, [0x23] = 0x88,
			[0x24] = 0xee, [0x25] = 0x99,
			[0x26] = 0xff, [0x27] = 0xaa,
		पूर्ण,
		अणु अणु0x40, 0xcc पूर्ण पूर्ण,
	पूर्ण,
	अणु
		"LD_ABS byte positive offset, all ff",
		.u.insns = अणु
			BPF_STMT(BPF_LD | BPF_ABS | BPF_B, 0x3f),
			BPF_STMT(BPF_RET | BPF_A, 0x0),
		पूर्ण,
		CLASSIC,
		अणु [0x3c] = 0xff, [0x3d] = 0xff,  [0x3e] = 0xff, [0x3f] = 0xff पूर्ण,
		अणु अणु0x40, 0xff पूर्ण पूर्ण,
	पूर्ण,
	अणु
		"LD_ABS byte positive offset, out of bounds",
		.u.insns = अणु
			BPF_STMT(BPF_LD | BPF_ABS | BPF_B, 0x3f),
			BPF_STMT(BPF_RET | BPF_A, 0x0),
		पूर्ण,
		CLASSIC,
		अणु [0x3c] = 0x25, [0x3d] = 0x05,  [0x3e] = 0x19, [0x3f] = 0x82 पूर्ण,
		अणु अणु0x3f, 0 पूर्ण, पूर्ण,
	पूर्ण,
	अणु
		"LD_ABS byte negative offset, out of bounds load",
		.u.insns = अणु
			BPF_STMT(BPF_LD | BPF_ABS | BPF_B, -1),
			BPF_STMT(BPF_RET | BPF_A, 0x0),
		पूर्ण,
		CLASSIC | FLAG_EXPECTED_FAIL,
		.expected_errcode = -EINVAL,
	पूर्ण,
	अणु
		"LD_ABS byte negative offset, in bounds",
		.u.insns = अणु
			BPF_STMT(BPF_LD | BPF_ABS | BPF_B, SKF_LL_OFF + 0x3f),
			BPF_STMT(BPF_RET | BPF_A, 0x0),
		पूर्ण,
		CLASSIC,
		अणु [0x3c] = 0x25, [0x3d] = 0x05,  [0x3e] = 0x19, [0x3f] = 0x82 पूर्ण,
		अणु अणु0x40, 0x82 पूर्ण, पूर्ण,
	पूर्ण,
	अणु
		"LD_ABS byte negative offset, out of bounds",
		.u.insns = अणु
			BPF_STMT(BPF_LD | BPF_ABS | BPF_B, SKF_LL_OFF + 0x3f),
			BPF_STMT(BPF_RET | BPF_A, 0x0),
		पूर्ण,
		CLASSIC,
		अणु [0x3c] = 0x25, [0x3d] = 0x05,  [0x3e] = 0x19, [0x3f] = 0x82 पूर्ण,
		अणु अणु0x3f, 0 पूर्ण, पूर्ण,
	पूर्ण,
	अणु
		"LD_ABS byte negative offset, multiple calls",
		.u.insns = अणु
			BPF_STMT(BPF_LD | BPF_ABS | BPF_B, SKF_LL_OFF + 0x3c),
			BPF_STMT(BPF_LD | BPF_ABS | BPF_B, SKF_LL_OFF + 0x3d),
			BPF_STMT(BPF_LD | BPF_ABS | BPF_B, SKF_LL_OFF + 0x3e),
			BPF_STMT(BPF_LD | BPF_ABS | BPF_B, SKF_LL_OFF + 0x3f),
			BPF_STMT(BPF_RET | BPF_A, 0x0),
		पूर्ण,
		CLASSIC,
		अणु [0x3c] = 0x25, [0x3d] = 0x05,  [0x3e] = 0x19, [0x3f] = 0x82 पूर्ण,
		अणु अणु0x40, 0x82 पूर्ण, पूर्ण,
	पूर्ण,
	अणु
		"LD_ABS halfword",
		.u.insns = अणु
			BPF_STMT(BPF_LD | BPF_ABS | BPF_H, 0x22),
			BPF_STMT(BPF_RET | BPF_A, 0x0),
		पूर्ण,
		CLASSIC,
		अणु
			[0x1c] = 0xaa, [0x1d] = 0x55,
			[0x1e] = 0xbb, [0x1f] = 0x66,
			[0x20] = 0xcc, [0x21] = 0x77,
			[0x22] = 0xdd, [0x23] = 0x88,
			[0x24] = 0xee, [0x25] = 0x99,
			[0x26] = 0xff, [0x27] = 0xaa,
		पूर्ण,
		अणु अणु0x40, 0xdd88 पूर्ण पूर्ण,
	पूर्ण,
	अणु
		"LD_ABS halfword unaligned",
		.u.insns = अणु
			BPF_STMT(BPF_LD | BPF_ABS | BPF_H, 0x25),
			BPF_STMT(BPF_RET | BPF_A, 0x0),
		पूर्ण,
		CLASSIC,
		अणु
			[0x1c] = 0xaa, [0x1d] = 0x55,
			[0x1e] = 0xbb, [0x1f] = 0x66,
			[0x20] = 0xcc, [0x21] = 0x77,
			[0x22] = 0xdd, [0x23] = 0x88,
			[0x24] = 0xee, [0x25] = 0x99,
			[0x26] = 0xff, [0x27] = 0xaa,
		पूर्ण,
		अणु अणु0x40, 0x99ff पूर्ण पूर्ण,
	पूर्ण,
	अणु
		"LD_ABS halfword positive offset, all ff",
		.u.insns = अणु
			BPF_STMT(BPF_LD | BPF_ABS | BPF_H, 0x3e),
			BPF_STMT(BPF_RET | BPF_A, 0x0),
		पूर्ण,
		CLASSIC,
		अणु [0x3c] = 0xff, [0x3d] = 0xff,  [0x3e] = 0xff, [0x3f] = 0xff पूर्ण,
		अणु अणु0x40, 0xffff पूर्ण पूर्ण,
	पूर्ण,
	अणु
		"LD_ABS halfword positive offset, out of bounds",
		.u.insns = अणु
			BPF_STMT(BPF_LD | BPF_ABS | BPF_H, 0x3f),
			BPF_STMT(BPF_RET | BPF_A, 0x0),
		पूर्ण,
		CLASSIC,
		अणु [0x3c] = 0x25, [0x3d] = 0x05,  [0x3e] = 0x19, [0x3f] = 0x82 पूर्ण,
		अणु अणु0x3f, 0 पूर्ण, पूर्ण,
	पूर्ण,
	अणु
		"LD_ABS halfword negative offset, out of bounds load",
		.u.insns = अणु
			BPF_STMT(BPF_LD | BPF_ABS | BPF_H, -1),
			BPF_STMT(BPF_RET | BPF_A, 0x0),
		पूर्ण,
		CLASSIC | FLAG_EXPECTED_FAIL,
		.expected_errcode = -EINVAL,
	पूर्ण,
	अणु
		"LD_ABS halfword negative offset, in bounds",
		.u.insns = अणु
			BPF_STMT(BPF_LD | BPF_ABS | BPF_H, SKF_LL_OFF + 0x3e),
			BPF_STMT(BPF_RET | BPF_A, 0x0),
		पूर्ण,
		CLASSIC,
		अणु [0x3c] = 0x25, [0x3d] = 0x05,  [0x3e] = 0x19, [0x3f] = 0x82 पूर्ण,
		अणु अणु0x40, 0x1982 पूर्ण, पूर्ण,
	पूर्ण,
	अणु
		"LD_ABS halfword negative offset, out of bounds",
		.u.insns = अणु
			BPF_STMT(BPF_LD | BPF_ABS | BPF_H, SKF_LL_OFF + 0x3e),
			BPF_STMT(BPF_RET | BPF_A, 0x0),
		पूर्ण,
		CLASSIC,
		अणु [0x3c] = 0x25, [0x3d] = 0x05,  [0x3e] = 0x19, [0x3f] = 0x82 पूर्ण,
		अणु अणु0x3f, 0 पूर्ण, पूर्ण,
	पूर्ण,
	अणु
		"LD_ABS word",
		.u.insns = अणु
			BPF_STMT(BPF_LD | BPF_ABS | BPF_W, 0x1c),
			BPF_STMT(BPF_RET | BPF_A, 0x0),
		पूर्ण,
		CLASSIC,
		अणु
			[0x1c] = 0xaa, [0x1d] = 0x55,
			[0x1e] = 0xbb, [0x1f] = 0x66,
			[0x20] = 0xcc, [0x21] = 0x77,
			[0x22] = 0xdd, [0x23] = 0x88,
			[0x24] = 0xee, [0x25] = 0x99,
			[0x26] = 0xff, [0x27] = 0xaa,
		पूर्ण,
		अणु अणु0x40, 0xaa55bb66 पूर्ण पूर्ण,
	पूर्ण,
	अणु
		"LD_ABS word unaligned (addr & 3 == 2)",
		.u.insns = अणु
			BPF_STMT(BPF_LD | BPF_ABS | BPF_W, 0x22),
			BPF_STMT(BPF_RET | BPF_A, 0x0),
		पूर्ण,
		CLASSIC,
		अणु
			[0x1c] = 0xaa, [0x1d] = 0x55,
			[0x1e] = 0xbb, [0x1f] = 0x66,
			[0x20] = 0xcc, [0x21] = 0x77,
			[0x22] = 0xdd, [0x23] = 0x88,
			[0x24] = 0xee, [0x25] = 0x99,
			[0x26] = 0xff, [0x27] = 0xaa,
		पूर्ण,
		अणु अणु0x40, 0xdd88ee99 पूर्ण पूर्ण,
	पूर्ण,
	अणु
		"LD_ABS word unaligned (addr & 3 == 1)",
		.u.insns = अणु
			BPF_STMT(BPF_LD | BPF_ABS | BPF_W, 0x21),
			BPF_STMT(BPF_RET | BPF_A, 0x0),
		पूर्ण,
		CLASSIC,
		अणु
			[0x1c] = 0xaa, [0x1d] = 0x55,
			[0x1e] = 0xbb, [0x1f] = 0x66,
			[0x20] = 0xcc, [0x21] = 0x77,
			[0x22] = 0xdd, [0x23] = 0x88,
			[0x24] = 0xee, [0x25] = 0x99,
			[0x26] = 0xff, [0x27] = 0xaa,
		पूर्ण,
		अणु अणु0x40, 0x77dd88ee पूर्ण पूर्ण,
	पूर्ण,
	अणु
		"LD_ABS word unaligned (addr & 3 == 3)",
		.u.insns = अणु
			BPF_STMT(BPF_LD | BPF_ABS | BPF_W, 0x23),
			BPF_STMT(BPF_RET | BPF_A, 0x0),
		पूर्ण,
		CLASSIC,
		अणु
			[0x1c] = 0xaa, [0x1d] = 0x55,
			[0x1e] = 0xbb, [0x1f] = 0x66,
			[0x20] = 0xcc, [0x21] = 0x77,
			[0x22] = 0xdd, [0x23] = 0x88,
			[0x24] = 0xee, [0x25] = 0x99,
			[0x26] = 0xff, [0x27] = 0xaa,
		पूर्ण,
		अणु अणु0x40, 0x88ee99ff पूर्ण पूर्ण,
	पूर्ण,
	अणु
		"LD_ABS word positive offset, all ff",
		.u.insns = अणु
			BPF_STMT(BPF_LD | BPF_ABS | BPF_W, 0x3c),
			BPF_STMT(BPF_RET | BPF_A, 0x0),
		पूर्ण,
		CLASSIC,
		अणु [0x3c] = 0xff, [0x3d] = 0xff,  [0x3e] = 0xff, [0x3f] = 0xff पूर्ण,
		अणु अणु0x40, 0xffffffff पूर्ण पूर्ण,
	पूर्ण,
	अणु
		"LD_ABS word positive offset, out of bounds",
		.u.insns = अणु
			BPF_STMT(BPF_LD | BPF_ABS | BPF_W, 0x3f),
			BPF_STMT(BPF_RET | BPF_A, 0x0),
		पूर्ण,
		CLASSIC,
		अणु [0x3c] = 0x25, [0x3d] = 0x05,  [0x3e] = 0x19, [0x3f] = 0x82 पूर्ण,
		अणु अणु0x3f, 0 पूर्ण, पूर्ण,
	पूर्ण,
	अणु
		"LD_ABS word negative offset, out of bounds load",
		.u.insns = अणु
			BPF_STMT(BPF_LD | BPF_ABS | BPF_W, -1),
			BPF_STMT(BPF_RET | BPF_A, 0x0),
		पूर्ण,
		CLASSIC | FLAG_EXPECTED_FAIL,
		.expected_errcode = -EINVAL,
	पूर्ण,
	अणु
		"LD_ABS word negative offset, in bounds",
		.u.insns = अणु
			BPF_STMT(BPF_LD | BPF_ABS | BPF_W, SKF_LL_OFF + 0x3c),
			BPF_STMT(BPF_RET | BPF_A, 0x0),
		पूर्ण,
		CLASSIC,
		अणु [0x3c] = 0x25, [0x3d] = 0x05,  [0x3e] = 0x19, [0x3f] = 0x82 पूर्ण,
		अणु अणु0x40, 0x25051982 पूर्ण, पूर्ण,
	पूर्ण,
	अणु
		"LD_ABS word negative offset, out of bounds",
		.u.insns = अणु
			BPF_STMT(BPF_LD | BPF_ABS | BPF_W, SKF_LL_OFF + 0x3c),
			BPF_STMT(BPF_RET | BPF_A, 0x0),
		पूर्ण,
		CLASSIC,
		अणु [0x3c] = 0x25, [0x3d] = 0x05,  [0x3e] = 0x19, [0x3f] = 0x82 पूर्ण,
		अणु अणु0x3f, 0 पूर्ण, पूर्ण,
	पूर्ण,
	अणु
		"LDX_MSH standalone, preserved A",
		.u.insns = अणु
			BPF_STMT(BPF_LD | BPF_IMM, 0xffeebbaa),
			BPF_STMT(BPF_LDX | BPF_B | BPF_MSH, 0x3c),
			BPF_STMT(BPF_RET | BPF_A, 0x0),
		पूर्ण,
		CLASSIC,
		अणु [0x3c] = 0x25, [0x3d] = 0x05,  [0x3e] = 0x19, [0x3f] = 0x82 पूर्ण,
		अणु अणु0x40, 0xffeebbaa पूर्ण, पूर्ण,
	पूर्ण,
	अणु
		"LDX_MSH standalone, preserved A 2",
		.u.insns = अणु
			BPF_STMT(BPF_LD | BPF_IMM, 0x175e9d63),
			BPF_STMT(BPF_LDX | BPF_B | BPF_MSH, 0x3c),
			BPF_STMT(BPF_LDX | BPF_B | BPF_MSH, 0x3d),
			BPF_STMT(BPF_LDX | BPF_B | BPF_MSH, 0x3e),
			BPF_STMT(BPF_LDX | BPF_B | BPF_MSH, 0x3f),
			BPF_STMT(BPF_RET | BPF_A, 0x0),
		पूर्ण,
		CLASSIC,
		अणु [0x3c] = 0x25, [0x3d] = 0x05,  [0x3e] = 0x19, [0x3f] = 0x82 पूर्ण,
		अणु अणु0x40, 0x175e9d63 पूर्ण, पूर्ण,
	पूर्ण,
	अणु
		"LDX_MSH standalone, test result 1",
		.u.insns = अणु
			BPF_STMT(BPF_LD | BPF_IMM, 0xffeebbaa),
			BPF_STMT(BPF_LDX | BPF_B | BPF_MSH, 0x3c),
			BPF_STMT(BPF_MISC | BPF_TXA, 0),
			BPF_STMT(BPF_RET | BPF_A, 0x0),
		पूर्ण,
		CLASSIC,
		अणु [0x3c] = 0x25, [0x3d] = 0x05,  [0x3e] = 0x19, [0x3f] = 0x82 पूर्ण,
		अणु अणु0x40, 0x14 पूर्ण, पूर्ण,
	पूर्ण,
	अणु
		"LDX_MSH standalone, test result 2",
		.u.insns = अणु
			BPF_STMT(BPF_LD | BPF_IMM, 0xffeebbaa),
			BPF_STMT(BPF_LDX | BPF_B | BPF_MSH, 0x3e),
			BPF_STMT(BPF_MISC | BPF_TXA, 0),
			BPF_STMT(BPF_RET | BPF_A, 0x0),
		पूर्ण,
		CLASSIC,
		अणु [0x3c] = 0x25, [0x3d] = 0x05,  [0x3e] = 0x19, [0x3f] = 0x82 पूर्ण,
		अणु अणु0x40, 0x24 पूर्ण, पूर्ण,
	पूर्ण,
	अणु
		"LDX_MSH standalone, negative offset",
		.u.insns = अणु
			BPF_STMT(BPF_LD | BPF_IMM, 0xffeebbaa),
			BPF_STMT(BPF_LDX | BPF_B | BPF_MSH, -1),
			BPF_STMT(BPF_MISC | BPF_TXA, 0),
			BPF_STMT(BPF_RET | BPF_A, 0x0),
		पूर्ण,
		CLASSIC,
		अणु [0x3c] = 0x25, [0x3d] = 0x05,  [0x3e] = 0x19, [0x3f] = 0x82 पूर्ण,
		अणु अणु0x40, 0 पूर्ण, पूर्ण,
	पूर्ण,
	अणु
		"LDX_MSH standalone, negative offset 2",
		.u.insns = अणु
			BPF_STMT(BPF_LD | BPF_IMM, 0xffeebbaa),
			BPF_STMT(BPF_LDX | BPF_B | BPF_MSH, SKF_LL_OFF + 0x3e),
			BPF_STMT(BPF_MISC | BPF_TXA, 0),
			BPF_STMT(BPF_RET | BPF_A, 0x0),
		पूर्ण,
		CLASSIC,
		अणु [0x3c] = 0x25, [0x3d] = 0x05,  [0x3e] = 0x19, [0x3f] = 0x82 पूर्ण,
		अणु अणु0x40, 0x24 पूर्ण, पूर्ण,
	पूर्ण,
	अणु
		"LDX_MSH standalone, out of bounds",
		.u.insns = अणु
			BPF_STMT(BPF_LD | BPF_IMM, 0xffeebbaa),
			BPF_STMT(BPF_LDX | BPF_B | BPF_MSH, 0x40),
			BPF_STMT(BPF_MISC | BPF_TXA, 0),
			BPF_STMT(BPF_RET | BPF_A, 0x0),
		पूर्ण,
		CLASSIC,
		अणु [0x3c] = 0x25, [0x3d] = 0x05,  [0x3e] = 0x19, [0x3f] = 0x82 पूर्ण,
		अणु अणु0x40, 0 पूर्ण, पूर्ण,
	पूर्ण,
	/*
	 * verअगरy that the पूर्णांकerpreter or JIT correctly sets A and X
	 * to 0.
	 */
	अणु
		"ADD default X",
		.u.insns = अणु
			/*
			 * A = 0x42
			 * A = A + X
			 * ret A
			 */
			BPF_STMT(BPF_LD | BPF_IMM, 0x42),
			BPF_STMT(BPF_ALU | BPF_ADD | BPF_X, 0),
			BPF_STMT(BPF_RET | BPF_A, 0x0),
		पूर्ण,
		CLASSIC | FLAG_NO_DATA,
		अणुपूर्ण,
		अणु अणु0x1, 0x42 पूर्ण पूर्ण,
	पूर्ण,
	अणु
		"ADD default A",
		.u.insns = अणु
			/*
			 * A = A + 0x42
			 * ret A
			 */
			BPF_STMT(BPF_ALU | BPF_ADD | BPF_K, 0x42),
			BPF_STMT(BPF_RET | BPF_A, 0x0),
		पूर्ण,
		CLASSIC | FLAG_NO_DATA,
		अणुपूर्ण,
		अणु अणु0x1, 0x42 पूर्ण पूर्ण,
	पूर्ण,
	अणु
		"SUB default X",
		.u.insns = अणु
			/*
			 * A = 0x66
			 * A = A - X
			 * ret A
			 */
			BPF_STMT(BPF_LD | BPF_IMM, 0x66),
			BPF_STMT(BPF_ALU | BPF_SUB | BPF_X, 0),
			BPF_STMT(BPF_RET | BPF_A, 0x0),
		पूर्ण,
		CLASSIC | FLAG_NO_DATA,
		अणुपूर्ण,
		अणु अणु0x1, 0x66 पूर्ण पूर्ण,
	पूर्ण,
	अणु
		"SUB default A",
		.u.insns = अणु
			/*
			 * A = A - -0x66
			 * ret A
			 */
			BPF_STMT(BPF_ALU | BPF_SUB | BPF_K, -0x66),
			BPF_STMT(BPF_RET | BPF_A, 0x0),
		पूर्ण,
		CLASSIC | FLAG_NO_DATA,
		अणुपूर्ण,
		अणु अणु0x1, 0x66 पूर्ण पूर्ण,
	पूर्ण,
	अणु
		"MUL default X",
		.u.insns = अणु
			/*
			 * A = 0x42
			 * A = A * X
			 * ret A
			 */
			BPF_STMT(BPF_LD | BPF_IMM, 0x42),
			BPF_STMT(BPF_ALU | BPF_MUL | BPF_X, 0),
			BPF_STMT(BPF_RET | BPF_A, 0x0),
		पूर्ण,
		CLASSIC | FLAG_NO_DATA,
		अणुपूर्ण,
		अणु अणु0x1, 0x0 पूर्ण पूर्ण,
	पूर्ण,
	अणु
		"MUL default A",
		.u.insns = अणु
			/*
			 * A = A * 0x66
			 * ret A
			 */
			BPF_STMT(BPF_ALU | BPF_MUL | BPF_K, 0x66),
			BPF_STMT(BPF_RET | BPF_A, 0x0),
		पूर्ण,
		CLASSIC | FLAG_NO_DATA,
		अणुपूर्ण,
		अणु अणु0x1, 0x0 पूर्ण पूर्ण,
	पूर्ण,
	अणु
		"DIV default X",
		.u.insns = अणु
			/*
			 * A = 0x42
			 * A = A / X ; this halt the filter execution अगर X is 0
			 * ret 0x42
			 */
			BPF_STMT(BPF_LD | BPF_IMM, 0x42),
			BPF_STMT(BPF_ALU | BPF_DIV | BPF_X, 0),
			BPF_STMT(BPF_RET | BPF_K, 0x42),
		पूर्ण,
		CLASSIC | FLAG_NO_DATA,
		अणुपूर्ण,
		अणु अणु0x1, 0x0 पूर्ण पूर्ण,
	पूर्ण,
	अणु
		"DIV default A",
		.u.insns = अणु
			/*
			 * A = A / 1
			 * ret A
			 */
			BPF_STMT(BPF_ALU | BPF_DIV | BPF_K, 0x1),
			BPF_STMT(BPF_RET | BPF_A, 0x0),
		पूर्ण,
		CLASSIC | FLAG_NO_DATA,
		अणुपूर्ण,
		अणु अणु0x1, 0x0 पूर्ण पूर्ण,
	पूर्ण,
	अणु
		"MOD default X",
		.u.insns = अणु
			/*
			 * A = 0x42
			 * A = A mod X ; this halt the filter execution अगर X is 0
			 * ret 0x42
			 */
			BPF_STMT(BPF_LD | BPF_IMM, 0x42),
			BPF_STMT(BPF_ALU | BPF_MOD | BPF_X, 0),
			BPF_STMT(BPF_RET | BPF_K, 0x42),
		पूर्ण,
		CLASSIC | FLAG_NO_DATA,
		अणुपूर्ण,
		अणु अणु0x1, 0x0 पूर्ण पूर्ण,
	पूर्ण,
	अणु
		"MOD default A",
		.u.insns = अणु
			/*
			 * A = A mod 1
			 * ret A
			 */
			BPF_STMT(BPF_ALU | BPF_MOD | BPF_K, 0x1),
			BPF_STMT(BPF_RET | BPF_A, 0x0),
		पूर्ण,
		CLASSIC | FLAG_NO_DATA,
		अणुपूर्ण,
		अणु अणु0x1, 0x0 पूर्ण पूर्ण,
	पूर्ण,
	अणु
		"JMP EQ default A",
		.u.insns = अणु
			/*
			 * cmp A, 0x0, 0, 1
			 * ret 0x42
			 * ret 0x66
			 */
			BPF_JUMP(BPF_JMP | BPF_JEQ | BPF_K, 0x0, 0, 1),
			BPF_STMT(BPF_RET | BPF_K, 0x42),
			BPF_STMT(BPF_RET | BPF_K, 0x66),
		पूर्ण,
		CLASSIC | FLAG_NO_DATA,
		अणुपूर्ण,
		अणु अणु0x1, 0x42 पूर्ण पूर्ण,
	पूर्ण,
	अणु
		"JMP EQ default X",
		.u.insns = अणु
			/*
			 * A = 0x0
			 * cmp A, X, 0, 1
			 * ret 0x42
			 * ret 0x66
			 */
			BPF_STMT(BPF_LD | BPF_IMM, 0x0),
			BPF_JUMP(BPF_JMP | BPF_JEQ | BPF_X, 0x0, 0, 1),
			BPF_STMT(BPF_RET | BPF_K, 0x42),
			BPF_STMT(BPF_RET | BPF_K, 0x66),
		पूर्ण,
		CLASSIC | FLAG_NO_DATA,
		अणुपूर्ण,
		अणु अणु0x1, 0x42 पूर्ण पूर्ण,
	पूर्ण,
	/* Checking पूर्णांकerpreter vs JIT wrt चिन्हित extended imms. */
	अणु
		"JNE signed compare, test 1",
		.u.insns_पूर्णांक = अणु
			BPF_ALU32_IMM(BPF_MOV, R1, 0xfefbbc12),
			BPF_ALU32_IMM(BPF_MOV, R3, 0xffff0000),
			BPF_MOV64_REG(R2, R1),
			BPF_ALU64_REG(BPF_AND, R2, R3),
			BPF_ALU32_IMM(BPF_MOV, R0, 1),
			BPF_JMP_IMM(BPF_JNE, R2, -17104896, 1),
			BPF_ALU32_IMM(BPF_MOV, R0, 2),
			BPF_EXIT_INSN(),
		पूर्ण,
		INTERNAL,
		अणु पूर्ण,
		अणु अणु 0, 1 पूर्ण पूर्ण,
	पूर्ण,
	अणु
		"JNE signed compare, test 2",
		.u.insns_पूर्णांक = अणु
			BPF_ALU32_IMM(BPF_MOV, R1, 0xfefbbc12),
			BPF_ALU32_IMM(BPF_MOV, R3, 0xffff0000),
			BPF_MOV64_REG(R2, R1),
			BPF_ALU64_REG(BPF_AND, R2, R3),
			BPF_ALU32_IMM(BPF_MOV, R0, 1),
			BPF_JMP_IMM(BPF_JNE, R2, 0xfefb0000, 1),
			BPF_ALU32_IMM(BPF_MOV, R0, 2),
			BPF_EXIT_INSN(),
		पूर्ण,
		INTERNAL,
		अणु पूर्ण,
		अणु अणु 0, 1 पूर्ण पूर्ण,
	पूर्ण,
	अणु
		"JNE signed compare, test 3",
		.u.insns_पूर्णांक = अणु
			BPF_ALU32_IMM(BPF_MOV, R1, 0xfefbbc12),
			BPF_ALU32_IMM(BPF_MOV, R3, 0xffff0000),
			BPF_ALU32_IMM(BPF_MOV, R4, 0xfefb0000),
			BPF_MOV64_REG(R2, R1),
			BPF_ALU64_REG(BPF_AND, R2, R3),
			BPF_ALU32_IMM(BPF_MOV, R0, 1),
			BPF_JMP_REG(BPF_JNE, R2, R4, 1),
			BPF_ALU32_IMM(BPF_MOV, R0, 2),
			BPF_EXIT_INSN(),
		पूर्ण,
		INTERNAL,
		अणु पूर्ण,
		अणु अणु 0, 2 पूर्ण पूर्ण,
	पूर्ण,
	अणु
		"JNE signed compare, test 4",
		.u.insns_पूर्णांक = अणु
			BPF_LD_IMM64(R1, -17104896),
			BPF_ALU32_IMM(BPF_MOV, R0, 1),
			BPF_JMP_IMM(BPF_JNE, R1, -17104896, 1),
			BPF_ALU32_IMM(BPF_MOV, R0, 2),
			BPF_EXIT_INSN(),
		पूर्ण,
		INTERNAL,
		अणु पूर्ण,
		अणु अणु 0, 2 पूर्ण पूर्ण,
	पूर्ण,
	अणु
		"JNE signed compare, test 5",
		.u.insns_पूर्णांक = अणु
			BPF_LD_IMM64(R1, 0xfefb0000),
			BPF_ALU32_IMM(BPF_MOV, R0, 1),
			BPF_JMP_IMM(BPF_JNE, R1, 0xfefb0000, 1),
			BPF_ALU32_IMM(BPF_MOV, R0, 2),
			BPF_EXIT_INSN(),
		पूर्ण,
		INTERNAL,
		अणु पूर्ण,
		अणु अणु 0, 1 पूर्ण पूर्ण,
	पूर्ण,
	अणु
		"JNE signed compare, test 6",
		.u.insns_पूर्णांक = अणु
			BPF_LD_IMM64(R1, 0x7efb0000),
			BPF_ALU32_IMM(BPF_MOV, R0, 1),
			BPF_JMP_IMM(BPF_JNE, R1, 0x7efb0000, 1),
			BPF_ALU32_IMM(BPF_MOV, R0, 2),
			BPF_EXIT_INSN(),
		पूर्ण,
		INTERNAL,
		अणु पूर्ण,
		अणु अणु 0, 2 पूर्ण पूर्ण,
	पूर्ण,
	अणु
		"JNE signed compare, test 7",
		.u.insns = अणु
			BPF_STMT(BPF_LD | BPF_IMM, 0xffff0000),
			BPF_STMT(BPF_MISC | BPF_TAX, 0),
			BPF_STMT(BPF_LD | BPF_IMM, 0xfefbbc12),
			BPF_STMT(BPF_ALU | BPF_AND | BPF_X, 0),
			BPF_JUMP(BPF_JMP | BPF_JEQ | BPF_K, 0xfefb0000, 1, 0),
			BPF_STMT(BPF_RET | BPF_K, 1),
			BPF_STMT(BPF_RET | BPF_K, 2),
		पूर्ण,
		CLASSIC | FLAG_NO_DATA,
		अणुपूर्ण,
		अणु अणु 0, 2 पूर्ण पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा net_device dev;

अटल काष्ठा sk_buff *populate_skb(अक्षर *buf, पूर्णांक size)
अणु
	काष्ठा sk_buff *skb;

	अगर (size >= MAX_DATA)
		वापस शून्य;

	skb = alloc_skb(MAX_DATA, GFP_KERNEL);
	अगर (!skb)
		वापस शून्य;

	__skb_put_data(skb, buf, size);

	/* Initialize a fake skb with test pattern. */
	skb_reset_mac_header(skb);
	skb->protocol = htons(ETH_P_IP);
	skb->pkt_type = SKB_TYPE;
	skb->mark = SKB_MARK;
	skb->hash = SKB_HASH;
	skb->queue_mapping = SKB_QUEUE_MAP;
	skb->vlan_tci = SKB_VLAN_TCI;
	skb->vlan_present = SKB_VLAN_PRESENT;
	skb->vlan_proto = htons(ETH_P_IP);
	dev_net_set(&dev, &init_net);
	skb->dev = &dev;
	skb->dev->अगरindex = SKB_DEV_IFINDEX;
	skb->dev->type = SKB_DEV_TYPE;
	skb_set_network_header(skb, min(size, ETH_HLEN));

	वापस skb;
पूर्ण

अटल व्योम *generate_test_data(काष्ठा bpf_test *test, पूर्णांक sub)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा page *page;

	अगर (test->aux & FLAG_NO_DATA)
		वापस शून्य;

	/* Test हाल expects an skb, so populate one. Various
	 * subtests generate skbs of dअगरferent sizes based on
	 * the same data.
	 */
	skb = populate_skb(test->data, test->test[sub].data_size);
	अगर (!skb)
		वापस शून्य;

	अगर (test->aux & FLAG_SKB_FRAG) अणु
		/*
		 * when the test requires a fragmented skb, add a
		 * single fragment to the skb, filled with
		 * test->frag_data.
		 */
		व्योम *ptr;

		page = alloc_page(GFP_KERNEL);

		अगर (!page)
			जाओ err_kमुक्त_skb;

		ptr = kmap(page);
		अगर (!ptr)
			जाओ err_मुक्त_page;
		स_नकल(ptr, test->frag_data, MAX_DATA);
		kunmap(page);
		skb_add_rx_frag(skb, 0, page, 0, MAX_DATA, MAX_DATA);
	पूर्ण

	वापस skb;

err_मुक्त_page:
	__मुक्त_page(page);
err_kमुक्त_skb:
	kमुक्त_skb(skb);
	वापस शून्य;
पूर्ण

अटल व्योम release_test_data(स्थिर काष्ठा bpf_test *test, व्योम *data)
अणु
	अगर (test->aux & FLAG_NO_DATA)
		वापस;

	kमुक्त_skb(data);
पूर्ण

अटल पूर्णांक filter_length(पूर्णांक which)
अणु
	काष्ठा sock_filter *fp;
	पूर्णांक len;

	अगर (tests[which].fill_helper)
		वापस tests[which].u.ptr.len;

	fp = tests[which].u.insns;
	क्रम (len = MAX_INSNS - 1; len > 0; --len)
		अगर (fp[len].code != 0 || fp[len].k != 0)
			अवरोध;

	वापस len + 1;
पूर्ण

अटल व्योम *filter_poपूर्णांकer(पूर्णांक which)
अणु
	अगर (tests[which].fill_helper)
		वापस tests[which].u.ptr.insns;
	अन्यथा
		वापस tests[which].u.insns;
पूर्ण

अटल काष्ठा bpf_prog *generate_filter(पूर्णांक which, पूर्णांक *err)
अणु
	__u8 test_type = tests[which].aux & TEST_TYPE_MASK;
	अचिन्हित पूर्णांक flen = filter_length(which);
	व्योम *fptr = filter_poपूर्णांकer(which);
	काष्ठा sock_fprog_kern fprog;
	काष्ठा bpf_prog *fp;

	चयन (test_type) अणु
	हाल CLASSIC:
		fprog.filter = fptr;
		fprog.len = flen;

		*err = bpf_prog_create(&fp, &fprog);
		अगर (tests[which].aux & FLAG_EXPECTED_FAIL) अणु
			अगर (*err == tests[which].expected_errcode) अणु
				pr_cont("PASS\n");
				/* Verअगरier rejected filter as expected. */
				*err = 0;
				वापस शून्य;
			पूर्ण अन्यथा अणु
				pr_cont("UNEXPECTED_PASS\n");
				/* Verअगरier didn't reject the test that's
				 * bad enough, just वापस!
				 */
				*err = -EINVAL;
				वापस शून्य;
			पूर्ण
		पूर्ण
		अगर (*err) अणु
			pr_cont("FAIL to prog_create err=%d len=%d\n",
				*err, fprog.len);
			वापस शून्य;
		पूर्ण
		अवरोध;

	हाल INTERNAL:
		fp = bpf_prog_alloc(bpf_prog_size(flen), 0);
		अगर (fp == शून्य) अणु
			pr_cont("UNEXPECTED_FAIL no memory left\n");
			*err = -ENOMEM;
			वापस शून्य;
		पूर्ण

		fp->len = flen;
		/* Type करोesn't really matter here as long as it's not unspec. */
		fp->type = BPF_PROG_TYPE_SOCKET_FILTER;
		स_नकल(fp->insnsi, fptr, fp->len * माप(काष्ठा bpf_insn));
		fp->aux->stack_depth = tests[which].stack_depth;

		/* We cannot error here as we करोn't need type compatibility
		 * checks.
		 */
		fp = bpf_prog_select_runसमय(fp, err);
		अगर (*err) अणु
			pr_cont("FAIL to select_runtime err=%d\n", *err);
			वापस शून्य;
		पूर्ण
		अवरोध;
	पूर्ण

	*err = 0;
	वापस fp;
पूर्ण

अटल व्योम release_filter(काष्ठा bpf_prog *fp, पूर्णांक which)
अणु
	__u8 test_type = tests[which].aux & TEST_TYPE_MASK;

	चयन (test_type) अणु
	हाल CLASSIC:
		bpf_prog_destroy(fp);
		अवरोध;
	हाल INTERNAL:
		bpf_prog_मुक्त(fp);
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक __run_one(स्थिर काष्ठा bpf_prog *fp, स्थिर व्योम *data,
		     पूर्णांक runs, u64 *duration)
अणु
	u64 start, finish;
	पूर्णांक ret = 0, i;

	migrate_disable();
	start = kसमय_get_ns();

	क्रम (i = 0; i < runs; i++)
		ret = BPF_PROG_RUN(fp, data);

	finish = kसमय_get_ns();
	migrate_enable();

	*duration = finish - start;
	करो_भाग(*duration, runs);

	वापस ret;
पूर्ण

अटल पूर्णांक run_one(स्थिर काष्ठा bpf_prog *fp, काष्ठा bpf_test *test)
अणु
	पूर्णांक err_cnt = 0, i, runs = MAX_TESTRUNS;

	क्रम (i = 0; i < MAX_SUBTESTS; i++) अणु
		व्योम *data;
		u64 duration;
		u32 ret;

		अगर (test->test[i].data_size == 0 &&
		    test->test[i].result == 0)
			अवरोध;

		data = generate_test_data(test, i);
		अगर (!data && !(test->aux & FLAG_NO_DATA)) अणु
			pr_cont("data generation failed ");
			err_cnt++;
			अवरोध;
		पूर्ण
		ret = __run_one(fp, data, runs, &duration);
		release_test_data(test, data);

		अगर (ret == test->test[i].result) अणु
			pr_cont("%lld ", duration);
		पूर्ण अन्यथा अणु
			pr_cont("ret %d != %d ", ret,
				test->test[i].result);
			err_cnt++;
		पूर्ण
	पूर्ण

	वापस err_cnt;
पूर्ण

अटल अक्षर test_name[64];
module_param_string(test_name, test_name, माप(test_name), 0);

अटल पूर्णांक test_id = -1;
module_param(test_id, पूर्णांक, 0);

अटल पूर्णांक test_range[2] = अणु 0, ARRAY_SIZE(tests) - 1 पूर्ण;
module_param_array(test_range, पूर्णांक, शून्य, 0);

अटल __init पूर्णांक find_test_index(स्थिर अक्षर *test_name)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(tests); i++) अणु
		अगर (!म_भेद(tests[i].descr, test_name))
			वापस i;
	पूर्ण
	वापस -1;
पूर्ण

अटल __init पूर्णांक prepare_bpf_tests(व्योम)
अणु
	पूर्णांक i;

	अगर (test_id >= 0) अणु
		/*
		 * अगर a test_id was specअगरied, use test_range to
		 * cover only that test.
		 */
		अगर (test_id >= ARRAY_SIZE(tests)) अणु
			pr_err("test_bpf: invalid test_id specified.\n");
			वापस -EINVAL;
		पूर्ण

		test_range[0] = test_id;
		test_range[1] = test_id;
	पूर्ण अन्यथा अगर (*test_name) अणु
		/*
		 * अगर a test_name was specअगरied, find it and setup
		 * test_range to cover only that test.
		 */
		पूर्णांक idx = find_test_index(test_name);

		अगर (idx < 0) अणु
			pr_err("test_bpf: no test named '%s' found.\n",
			       test_name);
			वापस -EINVAL;
		पूर्ण
		test_range[0] = idx;
		test_range[1] = idx;
	पूर्ण अन्यथा अणु
		/*
		 * check that the supplied test_range is valid.
		 */
		अगर (test_range[0] >= ARRAY_SIZE(tests) ||
		    test_range[1] >= ARRAY_SIZE(tests) ||
		    test_range[0] < 0 || test_range[1] < 0) अणु
			pr_err("test_bpf: test_range is out of bound.\n");
			वापस -EINVAL;
		पूर्ण

		अगर (test_range[1] < test_range[0]) अणु
			pr_err("test_bpf: test_range is ending before it starts.\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(tests); i++) अणु
		अगर (tests[i].fill_helper &&
		    tests[i].fill_helper(&tests[i]) < 0)
			वापस -ENOMEM;
	पूर्ण

	वापस 0;
पूर्ण

अटल __init व्योम destroy_bpf_tests(व्योम)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(tests); i++) अणु
		अगर (tests[i].fill_helper)
			kमुक्त(tests[i].u.ptr.insns);
	पूर्ण
पूर्ण

अटल bool exclude_test(पूर्णांक test_id)
अणु
	वापस test_id < test_range[0] || test_id > test_range[1];
पूर्ण

अटल __init काष्ठा sk_buff *build_test_skb(व्योम)
अणु
	u32 headroom = NET_SKB_PAD + NET_IP_ALIGN + ETH_HLEN;
	काष्ठा sk_buff *skb[2];
	काष्ठा page *page[2];
	पूर्णांक i, data_size = 8;

	क्रम (i = 0; i < 2; i++) अणु
		page[i] = alloc_page(GFP_KERNEL);
		अगर (!page[i]) अणु
			अगर (i == 0)
				जाओ err_page0;
			अन्यथा
				जाओ err_page1;
		पूर्ण

		/* this will set skb[i]->head_frag */
		skb[i] = dev_alloc_skb(headroom + data_size);
		अगर (!skb[i]) अणु
			अगर (i == 0)
				जाओ err_skb0;
			अन्यथा
				जाओ err_skb1;
		पूर्ण

		skb_reserve(skb[i], headroom);
		skb_put(skb[i], data_size);
		skb[i]->protocol = htons(ETH_P_IP);
		skb_reset_network_header(skb[i]);
		skb_set_mac_header(skb[i], -ETH_HLEN);

		skb_add_rx_frag(skb[i], 0, page[i], 0, 64, 64);
		// skb_headlen(skb[i]): 8, skb[i]->head_frag = 1
	पूर्ण

	/* setup shinfo */
	skb_shinfo(skb[0])->gso_size = 1448;
	skb_shinfo(skb[0])->gso_type = SKB_GSO_TCPV4;
	skb_shinfo(skb[0])->gso_type |= SKB_GSO_DODGY;
	skb_shinfo(skb[0])->gso_segs = 0;
	skb_shinfo(skb[0])->frag_list = skb[1];

	/* adjust skb[0]'s len */
	skb[0]->len += skb[1]->len;
	skb[0]->data_len += skb[1]->data_len;
	skb[0]->truesize += skb[1]->truesize;

	वापस skb[0];

err_skb1:
	__मुक्त_page(page[1]);
err_page1:
	kमुक्त_skb(skb[0]);
err_skb0:
	__मुक्त_page(page[0]);
err_page0:
	वापस शून्य;
पूर्ण

अटल __init काष्ठा sk_buff *build_test_skb_linear_no_head_frag(व्योम)
अणु
	अचिन्हित पूर्णांक alloc_size = 2000;
	अचिन्हित पूर्णांक headroom = 102, करोffset = 72, data_size = 1308;
	काष्ठा sk_buff *skb[2];
	पूर्णांक i;

	/* skbs linked in a frag_list, both with linear data, with head_frag=0
	 * (data allocated by kदो_स्मृति), both have tcp data of 1308 bytes
	 * (total payload is 2616 bytes).
	 * Data offset is 72 bytes (40 ipv6 hdr, 32 tcp hdr). Some headroom.
	 */
	क्रम (i = 0; i < 2; i++) अणु
		skb[i] = alloc_skb(alloc_size, GFP_KERNEL);
		अगर (!skb[i]) अणु
			अगर (i == 0)
				जाओ err_skb0;
			अन्यथा
				जाओ err_skb1;
		पूर्ण

		skb[i]->protocol = htons(ETH_P_IPV6);
		skb_reserve(skb[i], headroom);
		skb_put(skb[i], करोffset + data_size);
		skb_reset_network_header(skb[i]);
		अगर (i == 0)
			skb_reset_mac_header(skb[i]);
		अन्यथा
			skb_set_mac_header(skb[i], -ETH_HLEN);
		__skb_pull(skb[i], करोffset);
	पूर्ण

	/* setup shinfo.
	 * mimic bpf_skb_proto_4_to_6, which resets gso_segs and assigns a
	 * reduced gso_size.
	 */
	skb_shinfo(skb[0])->gso_size = 1288;
	skb_shinfo(skb[0])->gso_type = SKB_GSO_TCPV6 | SKB_GSO_DODGY;
	skb_shinfo(skb[0])->gso_segs = 0;
	skb_shinfo(skb[0])->frag_list = skb[1];

	/* adjust skb[0]'s len */
	skb[0]->len += skb[1]->len;
	skb[0]->data_len += skb[1]->len;
	skb[0]->truesize += skb[1]->truesize;

	वापस skb[0];

err_skb1:
	kमुक्त_skb(skb[0]);
err_skb0:
	वापस शून्य;
पूर्ण

काष्ठा skb_segment_test अणु
	स्थिर अक्षर *descr;
	काष्ठा sk_buff *(*build_skb)(व्योम);
	netdev_features_t features;
पूर्ण;

अटल काष्ठा skb_segment_test skb_segment_tests[] __initस्थिर = अणु
	अणु
		.descr = "gso_with_rx_frags",
		.build_skb = build_test_skb,
		.features = NETIF_F_SG | NETIF_F_GSO_PARTIAL | NETIF_F_IP_CSUM |
			    NETIF_F_IPV6_CSUM | NETIF_F_RXCSUM
	पूर्ण,
	अणु
		.descr = "gso_linear_no_head_frag",
		.build_skb = build_test_skb_linear_no_head_frag,
		.features = NETIF_F_SG | NETIF_F_FRAGLIST |
			    NETIF_F_HW_VLAN_CTAG_TX | NETIF_F_GSO |
			    NETIF_F_LLTX_BIT | NETIF_F_GRO |
			    NETIF_F_IPV6_CSUM | NETIF_F_RXCSUM |
			    NETIF_F_HW_VLAN_STAG_TX_BIT
	पूर्ण
पूर्ण;

अटल __init पूर्णांक test_skb_segment_single(स्थिर काष्ठा skb_segment_test *test)
अणु
	काष्ठा sk_buff *skb, *segs;
	पूर्णांक ret = -1;

	skb = test->build_skb();
	अगर (!skb) अणु
		pr_info("%s: failed to build_test_skb", __func__);
		जाओ करोne;
	पूर्ण

	segs = skb_segment(skb, test->features);
	अगर (!IS_ERR(segs)) अणु
		kमुक्त_skb_list(segs);
		ret = 0;
	पूर्ण
	kमुक्त_skb(skb);
करोne:
	वापस ret;
पूर्ण

अटल __init पूर्णांक test_skb_segment(व्योम)
अणु
	पूर्णांक i, err_cnt = 0, pass_cnt = 0;

	क्रम (i = 0; i < ARRAY_SIZE(skb_segment_tests); i++) अणु
		स्थिर काष्ठा skb_segment_test *test = &skb_segment_tests[i];

		pr_info("#%d %s ", i, test->descr);

		अगर (test_skb_segment_single(test)) अणु
			pr_cont("FAIL\n");
			err_cnt++;
		पूर्ण अन्यथा अणु
			pr_cont("PASS\n");
			pass_cnt++;
		पूर्ण
	पूर्ण

	pr_info("%s: Summary: %d PASSED, %d FAILED\n", __func__,
		pass_cnt, err_cnt);
	वापस err_cnt ? -EINVAL : 0;
पूर्ण

अटल __init पूर्णांक test_bpf(व्योम)
अणु
	पूर्णांक i, err_cnt = 0, pass_cnt = 0;
	पूर्णांक jit_cnt = 0, run_cnt = 0;

	क्रम (i = 0; i < ARRAY_SIZE(tests); i++) अणु
		काष्ठा bpf_prog *fp;
		पूर्णांक err;

		cond_resched();
		अगर (exclude_test(i))
			जारी;

		pr_info("#%d %s ", i, tests[i].descr);

		fp = generate_filter(i, &err);
		अगर (fp == शून्य) अणु
			अगर (err == 0) अणु
				pass_cnt++;
				जारी;
			पूर्ण
			err_cnt++;
			जारी;
		पूर्ण

		pr_cont("jited:%u ", fp->jited);

		run_cnt++;
		अगर (fp->jited)
			jit_cnt++;

		err = run_one(fp, &tests[i]);
		release_filter(fp, i);

		अगर (err) अणु
			pr_cont("FAIL (%d times)\n", err);
			err_cnt++;
		पूर्ण अन्यथा अणु
			pr_cont("PASS\n");
			pass_cnt++;
		पूर्ण
	पूर्ण

	pr_info("Summary: %d PASSED, %d FAILED, [%d/%d JIT'ed]\n",
		pass_cnt, err_cnt, jit_cnt, run_cnt);

	वापस err_cnt ? -EINVAL : 0;
पूर्ण

अटल पूर्णांक __init test_bpf_init(व्योम)
अणु
	पूर्णांक ret;

	ret = prepare_bpf_tests();
	अगर (ret < 0)
		वापस ret;

	ret = test_bpf();
	destroy_bpf_tests();
	अगर (ret)
		वापस ret;

	वापस test_skb_segment();
पूर्ण

अटल व्योम __निकास test_bpf_निकास(व्योम)
अणु
पूर्ण

module_init(test_bpf_init);
module_निकास(test_bpf_निकास);

MODULE_LICENSE("GPL");
