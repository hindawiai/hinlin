<शैली गुरु>
/*
 * fp_decode.h
 *
 * Copyright Roman Zippel, 1997.  All rights reserved.
 *
 * Redistribution and use in source and binary क्रमms, with or without
 * modअगरication, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, and the entire permission notice in its entirety,
 *    including the disclaimer of warranties.
 * 2. Redistributions in binary क्रमm must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    करोcumentation and/or other materials provided with the distribution.
 * 3. The name of the author may not be used to enकरोrse or promote
 *    products derived from this software without specअगरic prior
 *    written permission.
 *
 * ALTERNATIVELY, this product may be distributed under the terms of
 * the GNU General Public License, in which हाल the provisions of the GPL are
 * required INSTEAD OF the above restrictions.  (This clause is
 * necessary due to a potential bad पूर्णांकeraction between the GPL and
 * the restrictions contained in a BSD-style copyright.)
 *
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY सूचीECT,
 * INसूचीECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
 * OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#अगर_अघोषित _FP_DECODE_H
#घोषणा _FP_DECODE_H

/* These macros करो the dirty work of the instr decoding, several variables
 * can be defined in the source file to modअगरy the work of these macros,
 * currently the following variables are used:
 * ...
 * The रेजिस्टर usage:
 * d0 - will contain source opeअक्रम क्रम data direct mode,
 *	otherwise scratch रेजिस्टर
 * d1 - upper 16bit are reserved क्रम caller
 *	lower 16bit may contain further arguments,
 *	is destroyed during decoding
 * d2 - contains first two inकाष्ठाion words,
 *	first word will be used क्रम extension word
 * a0 - will poपूर्णांक to source/dest opeअक्रम क्रम any indirect mode
 *	otherwise scratch रेजिस्टर
 * a1 - scratch रेजिस्टर
 * a2 - base addr to the task काष्ठाure
 *
 * the current implementation करोesn't check क्रम every disallowed
 * addressing mode (e.g. pc relative modes as destination), as दीर्घ
 * as it only means a new addressing mode, which should not appear
 * in a program and that करोesn't crash the emulation, I think it's
 * not a problem to allow these modes.
 */

करो_fmovem=0
करो_fmovem_cr=0
करो_no_pc_mode=0
करो_fscc=0

| first decoding of the instr type
| this separates the conditional instr
.macro	fp_decode_cond_instr_type
	bfextu	%d2अणु#8,#2पूर्ण,%d0
	jmp	([0f:w,%pc,%d0*4])

	.align	4
0:
|	.दीर्घ	"f<op>","fscc/fdbcc"
|	.दीर्घ	"fbccw","fbccl"
.endm

| second decoding of the instr type
| this separates most move instr
.macro	fp_decode_move_instr_type
	bfextu	%d2अणु#16,#3पूर्ण,%d0
	jmp	([0f:w,%pc,%d0*4])

	.align	4
0:
|	.दीर्घ	"f<op> fpx,fpx","invalid instr"
|	.दीर्घ	"f<op> <ea>,fpx","fmove fpx,<ea>"
|	.दीर्घ	"fmovem <ea>,fpcr","fmovem <ea>,fpx"
|	.दीर्घ	"fmovem fpcr,<ea>","fmovem fpx,<ea>"
.endm

| extract the source specअगरier, specअगरies
| either source fp रेजिस्टर or data क्रमmat
.macro	fp_decode_sourcespec
	bfextu	%d2अणु#19,#3पूर्ण,%d0
.endm

| decode destination क्रमmat क्रम fmove reg,ea
.macro	fp_decode_dest_क्रमmat
	bfextu	%d2अणु#19,#3पूर्ण,%d0
.endm

| decode source रेजिस्टर क्रम fmove reg,ea
.macro	fp_decode_src_reg
	bfextu	%d2अणु#22,#3पूर्ण,%d0
.endm

| extract the addressing mode
| it depends on the instr which of the modes is valid
.macro	fp_decode_addr_mode
	bfextu	%d2अणु#10,#3पूर्ण,%d0
	jmp	([0f:w,%pc,%d0*4])

	.align	4
0:
|	.दीर्घ	"data register direct","addr register direct"
|	.दीर्घ	"addr register indirect"
|	.दीर्घ	"addr register indirect postincrement"
|	.दीर्घ	"addr register indirect predecrement"
|	.दीर्घ	"addr register + index16"
|	.दीर्घ	"extension mode1","extension mode2"
.endm

| extract the रेजिस्टर क्रम the addressing mode
.macro	fp_decode_addr_reg
	bfextu	%d2अणु#13,#3पूर्ण,%d0
.endm

| decode the 8bit displacement from the brief extension word
.macro	fp_decode_disp8
	move.b	%d2,%d0
	ext.w	%d0
.endm

| decode the index of the brief/full extension word
.macro	fp_decode_index
	bfextu	%d2अणु#17,#3पूर्ण,%d0		| get the रेजिस्टर nr
	btst	#15,%d2			| test क्रम data/addr रेजिस्टर
	jne	1\@f
	म_लिखो	PDECODE,"d%d",1,%d0
	jsr	fp_get_data_reg
	jra	2\@f
1\@:	म_लिखो	PDECODE,"a%d",1,%d0
	jsr	fp_get_addr_reg
	move.l	%a0,%d0
2\@:
debug	lea	"'l'.w,%a0"
	btst	#11,%d2			| 16/32 bit size?
	jne	3\@f
debug	lea	"'w'.w,%a0"
	ext.l	%d0
3\@:	म_लिखो	PDECODE,":%c",1,%a0
	move.w	%d2,%d1			| scale factor
	rol.w	#7,%d1
	and.w	#3,%d1
debug	move.l	"%d1,-(%sp)"
debug	ext.l	"%d1"
	म_लिखो	PDECODE,":%d",1,%d1
debug	move.l	"(%sp)+,%d1"
	lsl.l	%d1,%d0
.endm

| decode the base displacement size
.macro	fp_decode_basedisp
	bfextu	%d2अणु#26,#2पूर्ण,%d0
	jmp	([0f:w,%pc,%d0*4])

	.align	4
0:
|	.दीर्घ	"reserved","null displacement"
|	.दीर्घ	"word displacement","long displacement"
.endm

.macro	fp_decode_outerdisp
	bfextu	%d2अणु#30,#2पूर्ण,%d0
	jmp	([0f:w,%pc,%d0*4])

	.align	4
0:
|	.दीर्घ	"no memory indirect action/reserved","null outer displacement"
|	.दीर्घ	"word outer displacement","long outer displacement"
.endm

| get the extension word and test क्रम brief or full extension type
.macro	fp_get_test_extword label
	fp_get_instr_word %d2,fp_err_ua1
	btst	#8,%d2
	jne	\label
.endm


| test अगर %pc is the base रेजिस्टर क्रम the indirect addr mode
.macro	fp_test_basereg_d16	label
	btst	#20,%d2
	jeq	\label
.endm

| test अगर %pc is the base रेजिस्टर क्रम one of the extended modes
.macro	fp_test_basereg_ext	label
	btst	#19,%d2
	jeq	\label
.endm

.macro	fp_test_suppr_index label
	btst	#6,%d2
	jne	\label
.endm


| addressing mode: data रेजिस्टर direct
.macro	fp_mode_data_direct
	fp_decode_addr_reg
	म_लिखो	PDECODE,"d%d",1,%d0
.endm

| addressing mode: address रेजिस्टर indirect
.macro	fp_mode_addr_indirect
	fp_decode_addr_reg
	म_लिखो	PDECODE,"(a%d)",1,%d0
	jsr	fp_get_addr_reg
.endm

| adjust stack क्रम byte moves from/to stack
.macro	fp_test_sp_byte_move
	.अगर	!करो_fmovem
	.अगर	करो_fscc
	move.w	#6,%d1
	.endअगर
	cmp.w	#7,%d0
	jne	1\@f
	.अगर	!करो_fscc
	cmp.w	#6,%d1
	jne	1\@f
	.endअगर
	move.w	#4,%d1
1\@:
	.endअगर
.endm

| addressing mode: address रेजिस्टर indirect with postincrement
.macro	fp_mode_addr_indirect_postinc
	fp_decode_addr_reg
	म_लिखो	PDECODE,"(a%d)+",1,%d0
	fp_test_sp_byte_move
	jsr	fp_get_addr_reg
	move.l	%a0,%a1			| save addr
	.अगर	करो_fmovem
	lea	(%a0,%d1.w*4),%a0
	.अगर	!करो_fmovem_cr
	lea	(%a0,%d1.w*8),%a0
	.endअगर
	.अन्यथा
	add.w	(fp_datasize,%d1.w*2),%a0
	.endअगर
	jsr	fp_put_addr_reg
	move.l	%a1,%a0
.endm

| addressing mode: address रेजिस्टर indirect with predecrement
.macro	fp_mode_addr_indirect_predec
	fp_decode_addr_reg
	म_लिखो	PDECODE,"-(a%d)",1,%d0
	fp_test_sp_byte_move
	jsr	fp_get_addr_reg
	.अगर	करो_fmovem
	.अगर	!करो_fmovem_cr
	lea	(-12,%a0),%a1		| setup to addr of 1st reg to move
	neg.w	%d1
	lea	(%a0,%d1.w*4),%a0
	add.w	%d1,%d1
	lea	(%a0,%d1.w*4),%a0
	jsr	fp_put_addr_reg
	move.l	%a1,%a0
	.अन्यथा
	neg.w	%d1
	lea	(%a0,%d1.w*4),%a0
	jsr	fp_put_addr_reg
	.endअगर
	.अन्यथा
	sub.w	(fp_datasize,%d1.w*2),%a0
	jsr	fp_put_addr_reg
	.endअगर
.endm

| addressing mode: address रेजिस्टर/programm counter indirect
|		   with 16bit displacement
.macro	fp_mode_addr_indirect_disp16
	.अगर	!करो_no_pc_mode
	fp_test_basereg_d16 1f
	म_लिखो	PDECODE,"pc"
	fp_get_pc %a0
	jra	2f
	.endअगर
1:	fp_decode_addr_reg
	म_लिखो	PDECODE,"a%d",1,%d0
	jsr	fp_get_addr_reg
2:	fp_get_instr_word %a1,fp_err_ua1
	म_लिखो	PDECODE,"@(%x)",1,%a1
	add.l	%a1,%a0
.endm

| perक्रमm preindex (अगर I/IS == 0xx and xx != 00)
.macro	fp_करो_preindex
	moveq	#3,%d0
	and.w	%d2,%d0
	jeq	1f
	btst	#2,%d2
	jne	1f
	म_लिखो	PDECODE,")@("
	getuser.l (%a1),%a1,fp_err_ua1,%a1
debug	jra	"2f"
1:	म_लिखो	PDECODE,","
2:
.endm

| perक्रमm postindex (अगर I/IS == 1xx)
.macro	fp_करो_postindex
	btst	#2,%d2
	jeq	1f
	म_लिखो	PDECODE,")@("
	getuser.l (%a1),%a1,fp_err_ua1,%a1
debug	jra	"2f"
1:	म_लिखो	PDECODE,","
2:
.endm

| all other indirect addressing modes will finally end up here
.macro	fp_mode_addr_indirect_exपंचांगode0
	.अगर	!करो_no_pc_mode
	fp_test_basereg_ext 1f
	म_लिखो	PDECODE,"pc"
	fp_get_pc %a0
	jra	2f
	.endअगर
1:	fp_decode_addr_reg
	म_लिखो	PDECODE,"a%d",1,%d0
	jsr	fp_get_addr_reg
2:	move.l	%a0,%a1
	swap	%d2
	fp_get_test_extword 3f
	| addressing mode: address रेजिस्टर/programm counter indirect
	|		   with index and 8bit displacement
	fp_decode_disp8
debug	ext.l	"%d0"
	म_लिखो	PDECODE,"@(%x,",1,%d0
	add.w	%d0,%a1
	fp_decode_index
	add.l	%d0,%a1
	म_लिखो	PDECODE,")"
	jra	9f
3:	| addressing mode: address रेजिस्टर/programm counter memory indirect
	|		   with base and/or outer displacement
	btst	#7,%d2			| base रेजिस्टर suppressed?
	jeq	1f
	म_लिखो	PDECODE,"!"
	sub.l	%a1,%a1
1:	म_लिखो	PDECODE,"@("
	fp_decode_basedisp

	.दीर्घ	fp_ill,1f
	.दीर्घ	2f,3f

#अगर_घोषित FPU_EMU_DEBUG
1:	म_लिखो	PDECODE,"0"		| null base displacement
	jra	1f
#पूर्ण_अगर
2:	fp_get_instr_word %a0,fp_err_ua1 | 16bit base displacement
	म_लिखो	PDECODE,"%x:w",1,%a0
	jra	4f
3:	fp_get_instr_दीर्घ %a0,fp_err_ua1 | 32bit base displacement
	म_लिखो	PDECODE,"%x:l",1,%a0
4:	add.l	%a0,%a1
1:
	fp_करो_postindex
	fp_test_suppr_index 1f
	fp_decode_index
	add.l	%d0,%a1
1:	fp_करो_preindex

	fp_decode_outerdisp

	.दीर्घ	5f,1f
	.दीर्घ	2f,3f

#अगर_घोषित FPU_EMU_DEBUG
1:	म_लिखो	PDECODE,"0"		| null outer displacement
	jra	1f
#पूर्ण_अगर
2:	fp_get_instr_word %a0,fp_err_ua1 | 16bit outer displacement
	म_लिखो	PDECODE,"%x:w",1,%a0
	jra	4f
3:	fp_get_instr_दीर्घ %a0,fp_err_ua1 | 32bit outer displacement
	म_लिखो	PDECODE,"%x:l",1,%a0
4:	add.l	%a0,%a1
1:
5:	म_लिखो	PDECODE,")"
9:	move.l	%a1,%a0
	swap	%d2
.endm

| get the असलolute लघु address from user space
.macro	fp_mode_असल_लघु
	fp_get_instr_word %a0,fp_err_ua1
	म_लिखो	PDECODE,"%x.w",1,%a0
.endm

| get the असलolute दीर्घ address from user space
.macro	fp_mode_असल_दीर्घ
	fp_get_instr_दीर्घ %a0,fp_err_ua1
	म_लिखो	PDECODE,"%x.l",1,%a0
.endm

#पूर्ण_अगर /* _FP_DECODE_H */
