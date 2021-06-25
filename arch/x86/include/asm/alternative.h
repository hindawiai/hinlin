<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_X86_ALTERNATIVE_H
#घोषणा _ASM_X86_ALTERNATIVE_H

#समावेश <linux/types.h>
#समावेश <linux/stringअगरy.h>
#समावेश <यंत्र/यंत्र.h>

#घोषणा ALTINSTR_FLAG_INV	(1 << 15)
#घोषणा ALT_NOT(feat)		((feat) | ALTINSTR_FLAG_INV)

#अगर_अघोषित __ASSEMBLY__

#समावेश <linux/मानकघोष.स>

/*
 * Alternative अंतरभूत assembly क्रम SMP.
 *
 * The LOCK_PREFIX macro defined here replaces the LOCK and
 * LOCK_PREFIX macros used everywhere in the source tree.
 *
 * SMP alternatives use the same data काष्ठाures as the other
 * alternatives and the X86_FEATURE_UP flag to indicate the हाल of a
 * UP प्रणाली running a SMP kernel.  The existing apply_alternatives()
 * works fine क्रम patching a SMP kernel क्रम UP.
 *
 * The SMP alternative tables can be kept after boot and contain both
 * UP and SMP versions of the inकाष्ठाions to allow चयनing back to
 * SMP at runसमय, when hotplugging in a new CPU, which is especially
 * useful in भवized environments.
 *
 * The very common lock prefix is handled as special हाल in a
 * separate table which is a pure address list without replacement ptr
 * and size inक्रमmation.  That keeps the table sizes small.
 */

#अगर_घोषित CONFIG_SMP
#घोषणा LOCK_PREFIX_HERE \
		".pushsection .smp_locks,\"a\"\n"	\
		".balign 4\n"				\
		".long 671f - .\n" /* offset */		\
		".popsection\n"				\
		"671:"

#घोषणा LOCK_PREFIX LOCK_PREFIX_HERE "\n\tlock; "

#अन्यथा /* ! CONFIG_SMP */
#घोषणा LOCK_PREFIX_HERE ""
#घोषणा LOCK_PREFIX ""
#पूर्ण_अगर

/*
 * objtool annotation to ignore the alternatives and only consider the original
 * inकाष्ठाion(s).
 */
#घोषणा ANNOTATE_IGNORE_ALTERNATIVE				\
	"999:\n\t"						\
	".pushsection .discard.ignore_alts\n\t"			\
	".long 999b - .\n\t"					\
	".popsection\n\t"

काष्ठा alt_instr अणु
	s32 instr_offset;	/* original inकाष्ठाion */
	s32 repl_offset;	/* offset to replacement inकाष्ठाion */
	u16 cpuid;		/* cpuid bit set क्रम replacement */
	u8  inम_माप;		/* length of original inकाष्ठाion */
	u8  replacementlen;	/* length of new inकाष्ठाion */
पूर्ण __packed;

/*
 * Debug flag that can be tested to see whether alternative
 * inकाष्ठाions were patched in alपढ़ोy:
 */
बाह्य पूर्णांक alternatives_patched;

बाह्य व्योम alternative_inकाष्ठाions(व्योम);
बाह्य व्योम apply_alternatives(काष्ठा alt_instr *start, काष्ठा alt_instr *end);

काष्ठा module;

#अगर_घोषित CONFIG_SMP
बाह्य व्योम alternatives_smp_module_add(काष्ठा module *mod, अक्षर *name,
					व्योम *locks, व्योम *locks_end,
					व्योम *text, व्योम *text_end);
बाह्य व्योम alternatives_smp_module_del(काष्ठा module *mod);
बाह्य व्योम alternatives_enable_smp(व्योम);
बाह्य पूर्णांक alternatives_text_reserved(व्योम *start, व्योम *end);
बाह्य bool skip_smp_alternatives;
#अन्यथा
अटल अंतरभूत व्योम alternatives_smp_module_add(काष्ठा module *mod, अक्षर *name,
					       व्योम *locks, व्योम *locks_end,
					       व्योम *text, व्योम *text_end) अणुपूर्ण
अटल अंतरभूत व्योम alternatives_smp_module_del(काष्ठा module *mod) अणुपूर्ण
अटल अंतरभूत व्योम alternatives_enable_smp(व्योम) अणुपूर्ण
अटल अंतरभूत पूर्णांक alternatives_text_reserved(व्योम *start, व्योम *end)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर	/* CONFIG_SMP */

#घोषणा b_replacement(num)	"664"#num
#घोषणा e_replacement(num)	"665"#num

#घोषणा alt_end_marker		"663"
#घोषणा alt_slen		"662b-661b"
#घोषणा alt_total_slen		alt_end_marker"b-661b"
#घोषणा alt_rlen(num)		e_replacement(num)"f-"b_replacement(num)"f"

#घोषणा OLDINSTR(oldinstr, num)						\
	"# ALT: oldnstr\n"						\
	"661:\n\t" oldinstr "\n662:\n"					\
	"# ALT: padding\n"						\
	".skip -(((" alt_rlen(num) ")-(" alt_slen ")) > 0) * "		\
		"((" alt_rlen(num) ")-(" alt_slen ")),0x90\n"		\
	alt_end_marker ":\n"

/*
 * gas compatible max based on the idea from:
 * http://graphics.stanक्रमd.edu/~seander/bithacks.hपंचांगl#IntegerMinOrMax
 *
 * The additional "-" is needed because gas uses a "true" value of -1.
 */
#घोषणा alt_max_लघु(a, b)	"((" a ") ^ (((" a ") ^ (" b ")) & -(-((" a ") < (" b ")))))"

/*
 * Pad the second replacement alternative with additional NOPs अगर it is
 * additionally दीर्घer than the first replacement alternative.
 */
#घोषणा OLDINSTR_2(oldinstr, num1, num2) \
	"# ALT: oldinstr2\n"									\
	"661:\n\t" oldinstr "\n662:\n"								\
	"# ALT: padding2\n"									\
	".skip -((" alt_max_लघु(alt_rlen(num1), alt_rlen(num2)) " - (" alt_slen ")) > 0) * "	\
		"(" alt_max_लघु(alt_rlen(num1), alt_rlen(num2)) " - (" alt_slen ")), 0x90\n"	\
	alt_end_marker ":\n"

#घोषणा OLDINSTR_3(oldinsn, n1, n2, n3)								\
	"# ALT: oldinstr3\n"									\
	"661:\n\t" oldinsn "\n662:\n"								\
	"# ALT: padding3\n"									\
	".skip -((" alt_max_लघु(alt_max_लघु(alt_rlen(n1), alt_rlen(n2)), alt_rlen(n3))	\
		" - (" alt_slen ")) > 0) * "							\
		"(" alt_max_लघु(alt_max_लघु(alt_rlen(n1), alt_rlen(n2)), alt_rlen(n3))	\
		" - (" alt_slen ")), 0x90\n"							\
	alt_end_marker ":\n"

#घोषणा ALTINSTR_ENTRY(feature, num)					      \
	" .long 661b - .\n"				/* label           */ \
	" .long " b_replacement(num)"f - .\n"		/* new inकाष्ठाion */ \
	" .word " __stringअगरy(feature) "\n"		/* feature bit     */ \
	" .byte " alt_total_slen "\n"			/* source len      */ \
	" .byte " alt_rlen(num) "\n"			/* replacement len */

#घोषणा ALTINSTR_REPLACEMENT(newinstr, num)		/* replacement */	\
	"# ALT: replacement " #num "\n"						\
	b_replacement(num)":\n\t" newinstr "\n" e_replacement(num) ":\n"

/* alternative assembly primitive: */
#घोषणा ALTERNATIVE(oldinstr, newinstr, feature)			\
	OLDINSTR(oldinstr, 1)						\
	".pushsection .altinstructions,\"a\"\n"				\
	ALTINSTR_ENTRY(feature, 1)					\
	".popsection\n"							\
	".pushsection .altinstr_replacement, \"ax\"\n"			\
	ALTINSTR_REPLACEMENT(newinstr, 1)				\
	".popsection\n"

#घोषणा ALTERNATIVE_2(oldinstr, newinstr1, feature1, newinstr2, feature2)\
	OLDINSTR_2(oldinstr, 1, 2)					\
	".pushsection .altinstructions,\"a\"\n"				\
	ALTINSTR_ENTRY(feature1, 1)					\
	ALTINSTR_ENTRY(feature2, 2)					\
	".popsection\n"							\
	".pushsection .altinstr_replacement, \"ax\"\n"			\
	ALTINSTR_REPLACEMENT(newinstr1, 1)				\
	ALTINSTR_REPLACEMENT(newinstr2, 2)				\
	".popsection\n"

/* If @feature is set, patch in @newinstr_yes, otherwise @newinstr_no. */
#घोषणा ALTERNATIVE_TERNARY(oldinstr, feature, newinstr_yes, newinstr_no) \
	ALTERNATIVE_2(oldinstr, newinstr_no, X86_FEATURE_ALWAYS,	\
		      newinstr_yes, feature)

#घोषणा ALTERNATIVE_3(oldinsn, newinsn1, feat1, newinsn2, feat2, newinsn3, feat3) \
	OLDINSTR_3(oldinsn, 1, 2, 3)						\
	".pushsection .altinstructions,\"a\"\n"					\
	ALTINSTR_ENTRY(feat1, 1)						\
	ALTINSTR_ENTRY(feat2, 2)						\
	ALTINSTR_ENTRY(feat3, 3)						\
	".popsection\n"								\
	".pushsection .altinstr_replacement, \"ax\"\n"				\
	ALTINSTR_REPLACEMENT(newinsn1, 1)					\
	ALTINSTR_REPLACEMENT(newinsn2, 2)					\
	ALTINSTR_REPLACEMENT(newinsn3, 3)					\
	".popsection\n"

/*
 * Alternative inकाष्ठाions क्रम dअगरferent CPU types or capabilities.
 *
 * This allows to use optimized inकाष्ठाions even on generic binary
 * kernels.
 *
 * length of oldinstr must be दीर्घer or equal the length of newinstr
 * It can be padded with nops as needed.
 *
 * For non barrier like अंतरभूतs please define new variants
 * without अस्थिर and memory clobber.
 */
#घोषणा alternative(oldinstr, newinstr, feature)			\
	यंत्र_अंतरभूत अस्थिर (ALTERNATIVE(oldinstr, newinstr, feature) : : : "memory")

#घोषणा alternative_2(oldinstr, newinstr1, feature1, newinstr2, feature2) \
	यंत्र_अंतरभूत अस्थिर(ALTERNATIVE_2(oldinstr, newinstr1, feature1, newinstr2, feature2) ::: "memory")

#घोषणा alternative_ternary(oldinstr, feature, newinstr_yes, newinstr_no) \
	यंत्र_अंतरभूत अस्थिर(ALTERNATIVE_TERNARY(oldinstr, feature, newinstr_yes, newinstr_no) ::: "memory")

/*
 * Alternative अंतरभूत assembly with input.
 *
 * Peculiarities:
 * No memory clobber here.
 * Argument numbers start with 1.
 * Leaving an unused argument 0 to keep API compatibility.
 */
#घोषणा alternative_input(oldinstr, newinstr, feature, input...)	\
	यंत्र_अंतरभूत अस्थिर (ALTERNATIVE(oldinstr, newinstr, feature)	\
		: : "i" (0), ## input)

/*
 * This is similar to alternative_input. But it has two features and
 * respective inकाष्ठाions.
 *
 * If CPU has feature2, newinstr2 is used.
 * Otherwise, अगर CPU has feature1, newinstr1 is used.
 * Otherwise, oldinstr is used.
 */
#घोषणा alternative_input_2(oldinstr, newinstr1, feature1, newinstr2,	     \
			   feature2, input...)				     \
	यंत्र_अंतरभूत अस्थिर(ALTERNATIVE_2(oldinstr, newinstr1, feature1,     \
		newinstr2, feature2)					     \
		: : "i" (0), ## input)

/* Like alternative_input, but with a single output argument */
#घोषणा alternative_io(oldinstr, newinstr, feature, output, input...)	\
	यंत्र_अंतरभूत अस्थिर (ALTERNATIVE(oldinstr, newinstr, feature)	\
		: output : "i" (0), ## input)

/* Like alternative_io, but क्रम replacing a direct call with another one. */
#घोषणा alternative_call(oldfunc, newfunc, feature, output, input...)	\
	यंत्र_अंतरभूत अस्थिर (ALTERNATIVE("call %P[old]", "call %P[new]", feature) \
		: output : [old] "i" (oldfunc), [new] "i" (newfunc), ## input)

/*
 * Like alternative_call, but there are two features and respective functions.
 * If CPU has feature2, function2 is used.
 * Otherwise, अगर CPU has feature1, function1 is used.
 * Otherwise, old function is used.
 */
#घोषणा alternative_call_2(oldfunc, newfunc1, feature1, newfunc2, feature2,   \
			   output, input...)				      \
	यंत्र_अंतरभूत अस्थिर (ALTERNATIVE_2("call %P[old]", "call %P[new1]", feature1,\
		"call %P[new2]", feature2)				      \
		: output, ASM_CALL_CONSTRAINT				      \
		: [old] "i" (oldfunc), [new1] "i" (newfunc1),		      \
		  [new2] "i" (newfunc2), ## input)

/*
 * use this macro(s) अगर you need more than one output parameter
 * in alternative_io
 */
#घोषणा ASM_OUTPUT2(a...) a

/*
 * use this macro अगर you need clobbers but no inमाला_दो in
 * alternative_अणुinput,io,callपूर्ण()
 */
#घोषणा ASM_NO_INPUT_CLOBBER(clbr...) "i" (0) : clbr

#अन्यथा /* __ASSEMBLY__ */

#अगर_घोषित CONFIG_SMP
	.macro LOCK_PREFIX
672:	lock
	.pushsection .smp_locks,"a"
	.balign 4
	.दीर्घ 672b - .
	.popsection
	.endm
#अन्यथा
	.macro LOCK_PREFIX
	.endm
#पूर्ण_अगर

/*
 * objtool annotation to ignore the alternatives and only consider the original
 * inकाष्ठाion(s).
 */
.macro ANNOTATE_IGNORE_ALTERNATIVE
	.Lannotate_\@:
	.pushsection .discard.ignore_alts
	.दीर्घ .Lannotate_\@ - .
	.popsection
.endm

/*
 * Issue one काष्ठा alt_instr descriptor entry (need to put it पूर्णांकo
 * the section .altinकाष्ठाions, see below). This entry contains
 * enough inक्रमmation क्रम the alternatives patching code to patch an
 * inकाष्ठाion. See apply_alternatives().
 */
.macro altinकाष्ठाion_entry orig alt feature orig_len alt_len
	.दीर्घ \orig - .
	.दीर्घ \चlt - .
	.word \पeature
	.byte \orig_len
	.byte \चlt_len
.endm

/*
 * Define an alternative between two inकाष्ठाions. If @feature is
 * present, early code in apply_alternatives() replaces @oldinstr with
 * @newinstr. ".skip" directive takes care of proper inकाष्ठाion padding
 * in हाल @newinstr is दीर्घer than @oldinstr.
 */
.macro ALTERNATIVE oldinstr, newinstr, feature
140:
	\oldinstr
141:
	.skip -(((144f-143f)-(141b-140b)) > 0) * ((144f-143f)-(141b-140b)),0x90
142:

	.pushsection .altinकाष्ठाions,"a"
	altinकाष्ठाion_entry 140b,143f,\पeature,142b-140b,144f-143f
	.popsection

	.pushsection .altinstr_replacement,"ax"
143:
	\नewinstr
144:
	.popsection
.endm

#घोषणा old_len			141b-140b
#घोषणा new_len1		144f-143f
#घोषणा new_len2		145f-144f

/*
 * gas compatible max based on the idea from:
 * http://graphics.stanक्रमd.edu/~seander/bithacks.hपंचांगl#IntegerMinOrMax
 *
 * The additional "-" is needed because gas uses a "true" value of -1.
 */
#घोषणा alt_max_लघु(a, b)	((a) ^ (((a) ^ (b)) & -(-((a) < (b)))))


/*
 * Same as ALTERNATIVE macro above but क्रम two alternatives. If CPU
 * has @feature1, it replaces @oldinstr with @newinstr1. If CPU has
 * @feature2, it replaces @oldinstr with @feature2.
 */
.macro ALTERNATIVE_2 oldinstr, newinstr1, feature1, newinstr2, feature2
140:
	\oldinstr
141:
	.skip -((alt_max_लघु(new_len1, new_len2) - (old_len)) > 0) * \
		(alt_max_लघु(new_len1, new_len2) - (old_len)),0x90
142:

	.pushsection .altinकाष्ठाions,"a"
	altinकाष्ठाion_entry 140b,143f,\पeature1,142b-140b,144f-143f
	altinकाष्ठाion_entry 140b,144f,\पeature2,142b-140b,145f-144f
	.popsection

	.pushsection .altinstr_replacement,"ax"
143:
	\नewinstr1
144:
	\नewinstr2
145:
	.popsection
.endm

/* If @feature is set, patch in @newinstr_yes, otherwise @newinstr_no. */
#घोषणा ALTERNATIVE_TERNARY(oldinstr, feature, newinstr_yes, newinstr_no) \
	ALTERNATIVE_2 oldinstr, newinstr_no, X86_FEATURE_ALWAYS,	\
	newinstr_yes, feature

#पूर्ण_अगर /* __ASSEMBLY__ */

#पूर्ण_अगर /* _ASM_X86_ALTERNATIVE_H */
