<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

#समावेश <linux/kernel.h>
#समावेश <linux/jump_label.h>

#समावेश "asm/cacheflush.h"

#घोषणा JUMPLABEL_ERR	"ARC: jump_label: ERROR: "

/* Halt प्रणाली on fatal error to make debug easier */
#घोषणा arc_jl_fatal(क्रमmat...)						\
(अणु									\
	pr_err(JUMPLABEL_ERR क्रमmat);					\
	BUG();								\
पूर्ण)

अटल अंतरभूत u32 arc_gen_nop(व्योम)
अणु
	/* 1x 32bit NOP in middle endian */
	वापस 0x7000264a;
पूर्ण

/*
 * Atomic update of patched inकाष्ठाion is only available अगर this
 * inकाष्ठाion करोesn't cross L1 cache line boundary. You can पढ़ो about
 * the way we achieve this in arc/include/यंत्र/jump_label.h
 */
अटल अंतरभूत व्योम inकाष्ठाion_align_निश्चित(व्योम *addr, पूर्णांक len)
अणु
	अचिन्हित दीर्घ a = (अचिन्हित दीर्घ)addr;

	अगर ((a >> L1_CACHE_SHIFT) != ((a + len - 1) >> L1_CACHE_SHIFT))
		arc_jl_fatal("instruction (addr %px) cross L1 cache line border",
			     addr);
पूर्ण

/*
 * ARCv2 'Branch unconditionally' inकाष्ठाion:
 * 00000ssssssssss1SSSSSSSSSSNRtttt
 * s S[n:0] lower bits चिन्हित immediate (number is bitfield size)
 * S S[m:n+1] upper bits चिन्हित immediate (number is bitfield size)
 * t S[24:21] upper bits चिन्हित immediate (branch unconditionally far)
 * N N <.d> delay slot mode
 * R R Reserved
 */
अटल अंतरभूत u32 arc_gen_branch(jump_label_t pc, jump_label_t target)
अणु
	u32 inकाष्ठाion_l, inकाष्ठाion_r;
	u32 pcl = pc & GENMASK(31, 2);
	u32 u_offset = target - pcl;
	u32 s, S, t;

	/*
	 * Offset in 32-bit branch inकाष्ठाion must to fit पूर्णांकo s25.
	 * Something is terribly broken अगर we get such huge offset within one
	 * function.
	 */
	अगर ((s32)u_offset < -16777216 || (s32)u_offset > 16777214)
		arc_jl_fatal("gen branch with offset (%d) not fit in s25",
			     (s32)u_offset);

	/*
	 * All inकाष्ठाions are aligned by 2 bytes so we should never get offset
	 * here which is not 2 bytes aligned.
	 */
	अगर (u_offset & 0x1)
		arc_jl_fatal("gen branch with offset (%d) unaligned to 2 bytes",
			     (s32)u_offset);

	s = (u_offset >> 1)  & GENMASK(9, 0);
	S = (u_offset >> 11) & GENMASK(9, 0);
	t = (u_offset >> 21) & GENMASK(3, 0);

	/* 00000ssssssssss1 */
	inकाष्ठाion_l = (s << 1) | 0x1;
	/* SSSSSSSSSSNRtttt */
	inकाष्ठाion_r = (S << 6) | t;

	वापस (inकाष्ठाion_r << 16) | (inकाष्ठाion_l & GENMASK(15, 0));
पूर्ण

व्योम arch_jump_label_transक्रमm(काष्ठा jump_entry *entry,
			       क्रमागत jump_label_type type)
अणु
	jump_label_t *instr_addr = (jump_label_t *)entry->code;
	u32 instr;

	inकाष्ठाion_align_निश्चित(instr_addr, JUMP_LABEL_NOP_SIZE);

	अगर (type == JUMP_LABEL_JMP)
		instr = arc_gen_branch(entry->code, entry->target);
	अन्यथा
		instr = arc_gen_nop();

	WRITE_ONCE(*instr_addr, instr);
	flush_icache_range(entry->code, entry->code + JUMP_LABEL_NOP_SIZE);
पूर्ण

व्योम arch_jump_label_transक्रमm_अटल(काष्ठा jump_entry *entry,
				      क्रमागत jump_label_type type)
अणु
	/*
	 * We use only one NOP type (1x, 4 byte) in arch_अटल_branch, so
	 * there's no need to patch an identical NOP over the top of it here.
	 * The generic code calls 'arch_jump_label_transform' अगर the NOP needs
	 * to be replaced by a branch, so 'arch_jump_label_transform_static' is
	 * never called with type other than JUMP_LABEL_NOP.
	 */
	BUG_ON(type != JUMP_LABEL_NOP);
पूर्ण

#अगर_घोषित CONFIG_ARC_DBG_JUMP_LABEL
#घोषणा SELFTEST_MSG	"ARC: instruction generation self-test: "

काष्ठा arc_gen_branch_testdata अणु
	jump_label_t pc;
	jump_label_t target_address;
	u32 expected_instr;
पूर्ण;

अटल __init पूर्णांक branch_gen_test(स्थिर काष्ठा arc_gen_branch_testdata *test)
अणु
	u32 instr_got;

	instr_got = arc_gen_branch(test->pc, test->target_address);
	अगर (instr_got == test->expected_instr)
		वापस 0;

	pr_err(SELFTEST_MSG "FAIL:\n arc_gen_branch(0x%08x, 0x%08x) != 0x%08x, got 0x%08x\n",
	       test->pc, test->target_address,
	       test->expected_instr, instr_got);

	वापस -EFAULT;
पूर्ण

/*
 * Offset field in branch inकाष्ठाion is not continuous. Test all
 * available offset field and sign combinations. Test data is generated
 * from real working code.
 */
अटल स्थिर काष्ठा arc_gen_branch_testdata arcgenbr_test_data[] __initस्थिर = अणु
	अणु0x90007548, 0x90007514, 0xffcf07cdपूर्ण, /* tiny (-52) offs */
	अणु0x9000c9c0, 0x9000c782, 0xffcf05c3पूर्ण, /* tiny (-574) offs */
	अणु0x9000cc1c, 0x9000c782, 0xffcf0367पूर्ण, /* tiny (-1178) offs */
	अणु0x9009dce0, 0x9009d106, 0xff8f0427पूर्ण, /* small (-3034) offs */
	अणु0x9000f5de, 0x90007d30, 0xfc0f0755पूर्ण, /* big  (-30892) offs */
	अणु0x900a2444, 0x90035f64, 0xc9cf0321पूर्ण, /* huge (-443616) offs */
	अणु0x90007514, 0x9000752c, 0x00000019पूर्ण, /* tiny (+24) offs */
	अणु0x9001a578, 0x9001a77a, 0x00000203पूर्ण, /* tiny (+514) offs */
	अणु0x90031ed8, 0x90032634, 0x0000075dपूर्ण, /* tiny (+1884) offs */
	अणु0x9008c7f2, 0x9008d3f0, 0x00400401पूर्ण, /* small (+3072) offs */
	अणु0x9000bb38, 0x9003b340, 0x17c00009पूर्ण, /* big  (+194568) offs */
	अणु0x90008f44, 0x90578d80, 0xb7c2063dपूर्ण  /* huge (+5701180) offs */
पूर्ण;

अटल __init पूर्णांक instr_gen_test(व्योम)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(arcgenbr_test_data); i++)
		अगर (branch_gen_test(&arcgenbr_test_data[i]))
			वापस -EFAULT;

	pr_info(SELFTEST_MSG "OK\n");

	वापस 0;
पूर्ण
early_initcall(instr_gen_test);

#पूर्ण_अगर /* CONFIG_ARC_DBG_JUMP_LABEL */
