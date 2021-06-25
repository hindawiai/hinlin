<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *    Common helper functions क्रम kprobes and uprobes
 *
 *    Copyright IBM Corp. 2014
 */

#समावेश <linux/त्रुटिसं.स>
#समावेश <यंत्र/kprobes.h>
#समावेश <यंत्र/dis.h>

पूर्णांक probe_is_prohibited_opcode(u16 *insn)
अणु
	अगर (!is_known_insn((अचिन्हित अक्षर *)insn))
		वापस -EINVAL;
	चयन (insn[0] >> 8) अणु
	हाल 0x0c:	/* bassm */
	हाल 0x0b:	/* bsm	 */
	हाल 0x83:	/* diag  */
	हाल 0x44:	/* ex	 */
	हाल 0xac:	/* stnsm */
	हाल 0xad:	/* stosm */
		वापस -EINVAL;
	हाल 0xc6:
		चयन (insn[0] & 0x0f) अणु
		हाल 0x00: /* exrl   */
			वापस -EINVAL;
		पूर्ण
	पूर्ण
	चयन (insn[0]) अणु
	हाल 0x0101:	/* pr	 */
	हाल 0xb25a:	/* bsa	 */
	हाल 0xb240:	/* bakr  */
	हाल 0xb258:	/* bsg	 */
	हाल 0xb218:	/* pc	 */
	हाल 0xb228:	/* pt	 */
	हाल 0xb98d:	/* epsw	 */
	हाल 0xe560:	/* tbegin */
	हाल 0xe561:	/* tbeginc */
	हाल 0xb2f8:	/* tend	 */
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक probe_get_fixup_type(u16 *insn)
अणु
	/* शेष fixup method */
	पूर्णांक fixup = FIXUP_PSW_NORMAL;

	चयन (insn[0] >> 8) अणु
	हाल 0x05:	/* balr	*/
	हाल 0x0d:	/* basr */
		fixup = FIXUP_RETURN_REGISTER;
		/* अगर r2 = 0, no branch will be taken */
		अगर ((insn[0] & 0x0f) == 0)
			fixup |= FIXUP_BRANCH_NOT_TAKEN;
		अवरोध;
	हाल 0x06:	/* bctr	*/
	हाल 0x07:	/* bcr	*/
		fixup = FIXUP_BRANCH_NOT_TAKEN;
		अवरोध;
	हाल 0x45:	/* bal	*/
	हाल 0x4d:	/* bas	*/
		fixup = FIXUP_RETURN_REGISTER;
		अवरोध;
	हाल 0x47:	/* bc	*/
	हाल 0x46:	/* bct	*/
	हाल 0x86:	/* bxh	*/
	हाल 0x87:	/* bxle	*/
		fixup = FIXUP_BRANCH_NOT_TAKEN;
		अवरोध;
	हाल 0x82:	/* lpsw	*/
		fixup = FIXUP_NOT_REQUIRED;
		अवरोध;
	हाल 0xb2:	/* lpswe */
		अगर ((insn[0] & 0xff) == 0xb2)
			fixup = FIXUP_NOT_REQUIRED;
		अवरोध;
	हाल 0xa7:	/* bras	*/
		अगर ((insn[0] & 0x0f) == 0x05)
			fixup |= FIXUP_RETURN_REGISTER;
		अवरोध;
	हाल 0xc0:
		अगर ((insn[0] & 0x0f) == 0x05)	/* brasl */
			fixup |= FIXUP_RETURN_REGISTER;
		अवरोध;
	हाल 0xeb:
		चयन (insn[2] & 0xff) अणु
		हाल 0x44: /* bxhg  */
		हाल 0x45: /* bxleg */
			fixup = FIXUP_BRANCH_NOT_TAKEN;
			अवरोध;
		पूर्ण
		अवरोध;
	हाल 0xe3:	/* bctg	*/
		अगर ((insn[2] & 0xff) == 0x46)
			fixup = FIXUP_BRANCH_NOT_TAKEN;
		अवरोध;
	हाल 0xec:
		चयन (insn[2] & 0xff) अणु
		हाल 0xe5: /* clgrb */
		हाल 0xe6: /* cgrb  */
		हाल 0xf6: /* crb   */
		हाल 0xf7: /* clrb  */
		हाल 0xfc: /* cgib  */
		हाल 0xfd: /* cglib */
		हाल 0xfe: /* cib   */
		हाल 0xff: /* clib  */
			fixup = FIXUP_BRANCH_NOT_TAKEN;
			अवरोध;
		पूर्ण
		अवरोध;
	पूर्ण
	वापस fixup;
पूर्ण

पूर्णांक probe_is_insn_relative_दीर्घ(u16 *insn)
अणु
	/* Check अगर we have a RIL-b or RIL-c क्रमmat inकाष्ठाion which
	 * we need to modअगरy in order to aव्योम inकाष्ठाion emulation. */
	चयन (insn[0] >> 8) अणु
	हाल 0xc0:
		अगर ((insn[0] & 0x0f) == 0x00) /* larl */
			वापस true;
		अवरोध;
	हाल 0xc4:
		चयन (insn[0] & 0x0f) अणु
		हाल 0x02: /* llhrl  */
		हाल 0x04: /* lghrl  */
		हाल 0x05: /* lhrl   */
		हाल 0x06: /* llghrl */
		हाल 0x07: /* sthrl  */
		हाल 0x08: /* lgrl   */
		हाल 0x0b: /* stgrl  */
		हाल 0x0c: /* lgfrl  */
		हाल 0x0d: /* lrl    */
		हाल 0x0e: /* llgfrl */
		हाल 0x0f: /* strl   */
			वापस true;
		पूर्ण
		अवरोध;
	हाल 0xc6:
		चयन (insn[0] & 0x0f) अणु
		हाल 0x02: /* pfdrl  */
		हाल 0x04: /* cghrl  */
		हाल 0x05: /* chrl   */
		हाल 0x06: /* clghrl */
		हाल 0x07: /* clhrl  */
		हाल 0x08: /* cgrl   */
		हाल 0x0a: /* clgrl  */
		हाल 0x0c: /* cgfrl  */
		हाल 0x0d: /* crl    */
		हाल 0x0e: /* clgfrl */
		हाल 0x0f: /* clrl   */
			वापस true;
		पूर्ण
		अवरोध;
	पूर्ण
	वापस false;
पूर्ण
