<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/elf.h>
#समावेश <यंत्र/kexec.h>

पूर्णांक arch_kexec_करो_relocs(पूर्णांक r_type, व्योम *loc, अचिन्हित दीर्घ val,
			 अचिन्हित दीर्घ addr)
अणु
	चयन (r_type) अणु
	हाल R_390_NONE:
		अवरोध;
	हाल R_390_8:		/* Direct 8 bit.   */
		*(u8 *)loc = val;
		अवरोध;
	हाल R_390_12:		/* Direct 12 bit.  */
		*(u16 *)loc &= 0xf000;
		*(u16 *)loc |= val & 0xfff;
		अवरोध;
	हाल R_390_16:		/* Direct 16 bit.  */
		*(u16 *)loc = val;
		अवरोध;
	हाल R_390_20:		/* Direct 20 bit.  */
		*(u32 *)loc &= 0xf00000ff;
		*(u32 *)loc |= (val & 0xfff) << 16;	/* DL */
		*(u32 *)loc |= (val & 0xff000) >> 4;	/* DH */
		अवरोध;
	हाल R_390_32:		/* Direct 32 bit.  */
		*(u32 *)loc = val;
		अवरोध;
	हाल R_390_64:		/* Direct 64 bit.  */
	हाल R_390_GLOB_DAT:
	हाल R_390_JMP_SLOT:
		*(u64 *)loc = val;
		अवरोध;
	हाल R_390_PC16:	/* PC relative 16 bit.	*/
		*(u16 *)loc = (val - addr);
		अवरोध;
	हाल R_390_PC16DBL:	/* PC relative 16 bit shअगरted by 1.  */
		*(u16 *)loc = (val - addr) >> 1;
		अवरोध;
	हाल R_390_PC32DBL:	/* PC relative 32 bit shअगरted by 1.  */
		*(u32 *)loc = (val - addr) >> 1;
		अवरोध;
	हाल R_390_PC32:	/* PC relative 32 bit.	*/
		*(u32 *)loc = (val - addr);
		अवरोध;
	हाल R_390_PC64:	/* PC relative 64 bit.	*/
		*(u64 *)loc = (val - addr);
		अवरोध;
	हाल R_390_RELATIVE:
		*(अचिन्हित दीर्घ *) loc = val;
		अवरोध;
	शेष:
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण
