<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_S390_ALTERNATIVE_H
#घोषणा _ASM_S390_ALTERNATIVE_H

#अगर_अघोषित __ASSEMBLY__

#समावेश <linux/types.h>
#समावेश <linux/मानकघोष.स>
#समावेश <linux/stringअगरy.h>

काष्ठा alt_instr अणु
	s32 instr_offset;	/* original inकाष्ठाion */
	s32 repl_offset;	/* offset to replacement inकाष्ठाion */
	u16 facility;		/* facility bit set क्रम replacement */
	u8  inम_माप;		/* length of original inकाष्ठाion */
	u8  replacementlen;	/* length of new inकाष्ठाion */
पूर्ण __packed;

व्योम apply_alternative_inकाष्ठाions(व्योम);
व्योम apply_alternatives(काष्ठा alt_instr *start, काष्ठा alt_instr *end);

/*
 * |661:       |662:	  |6620      |663:
 * +-----------+---------------------+
 * | oldinstr  | oldinstr_padding    |
 * |	       +----------+----------+
 * |	       |	  |	     |
 * |	       | >6 bytes |6/4/2 nops|
 * |	       |6 bytes jg----------->
 * +-----------+---------------------+
 *		 ^^ अटल padding ^^
 *
 * .altinstr_replacement section
 * +---------------------+-----------+
 * |6641:			     |6651:
 * | alternative instr 1	     |
 * +-----------+---------+- - - - - -+
 * |6642:		 |6652:      |
 * | alternative instr 2 | padding
 * +---------------------+- - - - - -+
 *			  ^ runसमय ^
 *
 * .altinकाष्ठाions section
 * +---------------------------------+
 * | alt_instr entries क्रम each      |
 * | alternative instr		     |
 * +---------------------------------+
 */

#घोषणा b_altinstr(num)	"664"#num
#घोषणा e_altinstr(num)	"665"#num

#घोषणा e_oldinstr_pad_end	"663"
#घोषणा oldinstr_len		"662b-661b"
#घोषणा oldinstr_total_len	e_oldinstr_pad_end"b-661b"
#घोषणा altinstr_len(num)	e_altinstr(num)"b-"b_altinstr(num)"b"
#घोषणा oldinstr_pad_len(num) \
	"-(((" altinstr_len(num) ")-(" oldinstr_len ")) > 0) * " \
	"((" altinstr_len(num) ")-(" oldinstr_len "))"

#घोषणा INSTR_LEN_SANITY_CHECK(len)					\
	".if " len " > 254\n"						\
	"\t.error \"cpu alternatives does not support instructions "	\
		"blocks > 254 bytes\"\n"				\
	".endif\n"							\
	".if (" len ") %% 2\n"						\
	"\t.error \"cpu alternatives instructions length is odd\"\n"	\
	".endif\n"

#घोषणा OLDINSTR_PADDING(oldinstr, num)					\
	".if " oldinstr_pad_len(num) " > 6\n"				\
	"\tjg " e_oldinstr_pad_end "f\n"				\
	"6620:\n"							\
	"\t.fill (" oldinstr_pad_len(num) " - (6620b-662b)) / 2, 2, 0x0700\n" \
	".else\n"							\
	"\t.fill " oldinstr_pad_len(num) " / 6, 6, 0xc0040000\n"	\
	"\t.fill " oldinstr_pad_len(num) " %% 6 / 4, 4, 0x47000000\n"	\
	"\t.fill " oldinstr_pad_len(num) " %% 6 %% 4 / 2, 2, 0x0700\n"	\
	".endif\n"

#घोषणा OLDINSTR(oldinstr, num)						\
	"661:\n\t" oldinstr "\n662:\n"					\
	OLDINSTR_PADDING(oldinstr, num)					\
	e_oldinstr_pad_end ":\n"					\
	INSTR_LEN_SANITY_CHECK(oldinstr_len)

#घोषणा OLDINSTR_2(oldinstr, num1, num2)				\
	"661:\n\t" oldinstr "\n662:\n"					\
	".if " altinstr_len(num1) " < " altinstr_len(num2) "\n"		\
	OLDINSTR_PADDING(oldinstr, num2)				\
	".else\n"							\
	OLDINSTR_PADDING(oldinstr, num1)				\
	".endif\n"							\
	e_oldinstr_pad_end ":\n"					\
	INSTR_LEN_SANITY_CHECK(oldinstr_len)

#घोषणा ALTINSTR_ENTRY(facility, num)					\
	"\t.long 661b - .\n"			/* old inकाष्ठाion */	\
	"\t.long " b_altinstr(num)"b - .\n"	/* alt inकाष्ठाion */	\
	"\t.word " __stringअगरy(facility) "\n"	/* facility bit    */	\
	"\t.byte " oldinstr_total_len "\n"	/* source len	   */	\
	"\t.byte " altinstr_len(num) "\n"	/* alt inकाष्ठाion len */

#घोषणा ALTINSTR_REPLACEMENT(altinstr, num)	/* replacement */	\
	b_altinstr(num)":\n\t" altinstr "\n" e_altinstr(num) ":\n"	\
	INSTR_LEN_SANITY_CHECK(altinstr_len(num))

/* alternative assembly primitive: */
#घोषणा ALTERNATIVE(oldinstr, altinstr, facility) \
	".pushsection .altinstr_replacement, \"ax\"\n"			\
	ALTINSTR_REPLACEMENT(altinstr, 1)				\
	".popsection\n"							\
	OLDINSTR(oldinstr, 1)						\
	".pushsection .altinstructions,\"a\"\n"				\
	ALTINSTR_ENTRY(facility, 1)					\
	".popsection\n"

#घोषणा ALTERNATIVE_2(oldinstr, altinstr1, facility1, altinstr2, facility2)\
	".pushsection .altinstr_replacement, \"ax\"\n"			\
	ALTINSTR_REPLACEMENT(altinstr1, 1)				\
	ALTINSTR_REPLACEMENT(altinstr2, 2)				\
	".popsection\n"							\
	OLDINSTR_2(oldinstr, 1, 2)					\
	".pushsection .altinstructions,\"a\"\n"				\
	ALTINSTR_ENTRY(facility1, 1)					\
	ALTINSTR_ENTRY(facility2, 2)					\
	".popsection\n"

/*
 * Alternative inकाष्ठाions क्रम dअगरferent CPU types or capabilities.
 *
 * This allows to use optimized inकाष्ठाions even on generic binary
 * kernels.
 *
 * oldinstr is padded with jump and nops at compile समय अगर altinstr is
 * दीर्घer. altinstr is padded with jump and nops at run-समय during patching.
 *
 * For non barrier like अंतरभूतs please define new variants
 * without अस्थिर and memory clobber.
 */
#घोषणा alternative(oldinstr, altinstr, facility)			\
	यंत्र_अंतरभूत अस्थिर(ALTERNATIVE(oldinstr, altinstr, facility) : : : "memory")

#घोषणा alternative_2(oldinstr, altinstr1, facility1, altinstr2, facility2) \
	यंत्र_अंतरभूत अस्थिर(ALTERNATIVE_2(oldinstr, altinstr1, facility1,   \
				   altinstr2, facility2) ::: "memory")

/* Alternative अंतरभूत assembly with input. */
#घोषणा alternative_input(oldinstr, newinstr, feature, input...)	\
	यंत्र_अंतरभूत अस्थिर (ALTERNATIVE(oldinstr, newinstr, feature)	\
		: : input)

/* Like alternative_input, but with a single output argument */
#घोषणा alternative_io(oldinstr, altinstr, facility, output, input...)	\
	यंत्र_अंतरभूत अस्थिर(ALTERNATIVE(oldinstr, altinstr, facility)	\
		: output : input)

/* Use this macro अगर more than one output parameter is needed. */
#घोषणा ASM_OUTPUT2(a...) a

/* Use this macro अगर clobbers are needed without inमाला_दो. */
#घोषणा ASM_NO_INPUT_CLOBBER(clobber...) : clobber

#पूर्ण_अगर /* __ASSEMBLY__ */

#पूर्ण_अगर /* _ASM_S390_ALTERNATIVE_H */
