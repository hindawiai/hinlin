<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
    NetWinder Floating Poपूर्णांक Emulator
    (c) Rebel.COM, 1998,1999
    (c) Philip Blundell, 2001

    Direct questions, comments to Scott Bambrough <scottb@netwinder.org>

*/

#समावेश "fpa11.h"
#समावेश "fpopcode.h"

#समावेश "fpmodule.h"
#समावेश "fpmodule.inl"

#समावेश <linux/compiler.h>
#समावेश <linux/माला.स>

/* Reset the FPA11 chip.  Called to initialize and reset the emulator. */
अटल व्योम resetFPA11(व्योम)
अणु
	पूर्णांक i;
	FPA11 *fpa11 = GET_FPA11();

	/* initialize the रेजिस्टर type array */
	क्रम (i = 0; i <= 7; i++) अणु
		fpa11->fType[i] = typeNone;
	पूर्ण

	/* FPSR: set प्रणाली id to FP_EMULATOR, set AC, clear all other bits */
	fpa11->fpsr = FP_EMULATOR | BIT_AC;
पूर्ण

पूर्णांक8 SetRoundingMode(स्थिर अचिन्हित पूर्णांक opcode)
अणु
	चयन (opcode & MASK_ROUNDING_MODE) अणु
	शेष:
	हाल ROUND_TO_NEAREST:
		वापस भग्न_round_nearest_even;

	हाल ROUND_TO_PLUS_अनन्त:
		वापस भग्न_round_up;

	हाल ROUND_TO_MINUS_अनन्त:
		वापस भग्न_round_करोwn;

	हाल ROUND_TO_ZERO:
		वापस भग्न_round_to_zero;
	पूर्ण
पूर्ण

पूर्णांक8 SetRoundingPrecision(स्थिर अचिन्हित पूर्णांक opcode)
अणु
#अगर_घोषित CONFIG_FPE_NWFPE_XP
	चयन (opcode & MASK_ROUNDING_PRECISION) अणु
	हाल ROUND_SINGLE:
		वापस 32;

	हाल ROUND_DOUBLE:
		वापस 64;

	हाल ROUND_EXTENDED:
		वापस 80;

	शेष:
		वापस 80;
	पूर्ण
#पूर्ण_अगर
	वापस 80;
पूर्ण

व्योम nwfpe_init_fpa(जोड़ fp_state *fp)
अणु
	FPA11 *fpa11 = (FPA11 *)fp;
#अगर_घोषित NWFPE_DEBUG
	prपूर्णांकk("NWFPE: setting up state.\n");
#पूर्ण_अगर
 	स_रखो(fpa11, 0, माप(FPA11));
	resetFPA11();
	fpa11->initflag = 1;
पूर्ण

/* Emulate the inकाष्ठाion in the opcode. */
अचिन्हित पूर्णांक EmulateAll(अचिन्हित पूर्णांक opcode)
अणु
	अचिन्हित पूर्णांक code;

#अगर_घोषित NWFPE_DEBUG
	prपूर्णांकk("NWFPE: emulating opcode %08x\n", opcode);
#पूर्ण_अगर
	code = opcode & 0x00000f00;
	अगर (code == 0x00000100 || code == 0x00000200) अणु
		/* For coprocessor 1 or 2 (FPA11) */
		code = opcode & 0x0e000000;
		अगर (code == 0x0e000000) अणु
			अगर (opcode & 0x00000010) अणु
				/* Emulate conversion opcodes. */
				/* Emulate रेजिस्टर transfer opcodes. */
				/* Emulate comparison opcodes. */
				वापस EmulateCPRT(opcode);
			पूर्ण अन्यथा अणु
				/* Emulate monadic arithmetic opcodes. */
				/* Emulate dyadic arithmetic opcodes. */
				वापस EmulateCPDO(opcode);
			पूर्ण
		पूर्ण अन्यथा अगर (code == 0x0c000000) अणु
			/* Emulate load/store opcodes. */
			/* Emulate load/store multiple opcodes. */
			वापस EmulateCPDT(opcode);
		पूर्ण
	पूर्ण

	/* Invalid inकाष्ठाion detected.  Return FALSE. */
	वापस 0;
पूर्ण
