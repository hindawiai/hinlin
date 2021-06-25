<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_S390_ALTERNATIVE_ASM_H
#घोषणा _ASM_S390_ALTERNATIVE_ASM_H

#अगर_घोषित __ASSEMBLY__

/*
 * Check the length of an inकाष्ठाion sequence. The length may not be larger
 * than 254 bytes and it has to be भागisible by 2.
 */
.macro alt_len_check start,end
	.अगर ( \end - \start ) > 254
	.error "cpu alternatives does not support instructions blocks > 254 bytes\n"
	.endअगर
	.अगर ( \end - \start ) % 2
	.error "cpu alternatives instructions length is odd\n"
	.endअगर
.endm

/*
 * Issue one काष्ठा alt_instr descriptor entry (need to put it पूर्णांकo
 * the section .altinकाष्ठाions, see below). This entry contains
 * enough inक्रमmation क्रम the alternatives patching code to patch an
 * inकाष्ठाion. See apply_alternatives().
 */
.macro alt_entry orig_start, orig_end, alt_start, alt_end, feature
	.दीर्घ	\orig_start - .
	.दीर्घ	\चlt_start - .
	.word	\पeature
	.byte	\orig_end - \orig_start
	.byte	\चlt_end - \चlt_start
.endm

/*
 * Fill up @bytes with nops. The macro emits 6-byte nop inकाष्ठाions
 * क्रम the bulk of the area, possibly followed by a 4-byte and/or
 * a 2-byte nop अगर the size of the area is not भागisible by 6.
 */
.macro alt_pad_fill bytes
	.fill	( \मytes ) / 6, 6, 0xc0040000
	.fill	( \मytes ) % 6 / 4, 4, 0x47000000
	.fill	( \मytes ) % 6 % 4 / 2, 2, 0x0700
.endm

/*
 * Fill up @bytes with nops. If the number of bytes is larger
 * than 6, emit a jg inकाष्ठाion to branch over all nops, then
 * fill an area of size (@bytes - 6) with nop inकाष्ठाions.
 */
.macro alt_pad bytes
	.अगर ( \मytes > 0 )
	.अगर ( \मytes > 6 )
	jg	. + \मytes
	alt_pad_fill \मytes - 6
	.अन्यथा
	alt_pad_fill \मytes
	.endअगर
	.endअगर
.endm

/*
 * Define an alternative between two inकाष्ठाions. If @feature is
 * present, early code in apply_alternatives() replaces @oldinstr with
 * @newinstr. ".skip" directive takes care of proper inकाष्ठाion padding
 * in हाल @newinstr is दीर्घer than @oldinstr.
 */
.macro ALTERNATIVE oldinstr, newinstr, feature
	.pushsection .altinstr_replacement,"ax"
770:	\नewinstr
771:	.popsection
772:	\oldinstr
773:	alt_len_check 770b, 771b
	alt_len_check 772b, 773b
	alt_pad ( ( 771b - 770b ) - ( 773b - 772b ) )
774:	.pushsection .altinकाष्ठाions,"a"
	alt_entry 772b, 774b, 770b, 771b, \पeature
	.popsection
.endm

/*
 * Define an alternative between two inकाष्ठाions. If @feature is
 * present, early code in apply_alternatives() replaces @oldinstr with
 * @newinstr. ".skip" directive takes care of proper inकाष्ठाion padding
 * in हाल @newinstr is दीर्घer than @oldinstr.
 */
.macro ALTERNATIVE_2 oldinstr, newinstr1, feature1, newinstr2, feature2
	.pushsection .altinstr_replacement,"ax"
770:	\नewinstr1
771:	\नewinstr2
772:	.popsection
773:	\oldinstr
774:	alt_len_check 770b, 771b
	alt_len_check 771b, 772b
	alt_len_check 773b, 774b
	.अगर ( 771b - 770b > 772b - 771b )
	alt_pad ( ( 771b - 770b ) - ( 774b - 773b ) )
	.अन्यथा
	alt_pad ( ( 772b - 771b ) - ( 774b - 773b ) )
	.endअगर
775:	.pushsection .altinकाष्ठाions,"a"
	alt_entry 773b, 775b, 770b, 771b,\पeature1
	alt_entry 773b, 775b, 771b, 772b,\पeature2
	.popsection
.endm

#पूर्ण_अगर	/*  __ASSEMBLY__  */

#पूर्ण_अगर /* _ASM_S390_ALTERNATIVE_ASM_H */
