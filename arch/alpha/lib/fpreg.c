<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * arch/alpha/lib/fpreg.c
 *
 * (C) Copyright 1998 Linus Torvalds
 */

#समावेश <linux/compiler.h>
#समावेश <linux/export.h>

#अगर defined(CONFIG_ALPHA_EV6) || defined(CONFIG_ALPHA_EV67)
#घोषणा STT(reg,val)  यंत्र अस्थिर ("ftoit $f"#reg",%0" : "=r"(val));
#अन्यथा
#घोषणा STT(reg,val)  यंत्र अस्थिर ("stt $f"#reg",%0" : "=m"(val));
#पूर्ण_अगर

अचिन्हित दीर्घ
alpha_पढ़ो_fp_reg (अचिन्हित दीर्घ reg)
अणु
	अचिन्हित दीर्घ val;

	चयन (reg) अणु
	      हाल  0: STT( 0, val); अवरोध;
	      हाल  1: STT( 1, val); अवरोध;
	      हाल  2: STT( 2, val); अवरोध;
	      हाल  3: STT( 3, val); अवरोध;
	      हाल  4: STT( 4, val); अवरोध;
	      हाल  5: STT( 5, val); अवरोध;
	      हाल  6: STT( 6, val); अवरोध;
	      हाल  7: STT( 7, val); अवरोध;
	      हाल  8: STT( 8, val); अवरोध;
	      हाल  9: STT( 9, val); अवरोध;
	      हाल 10: STT(10, val); अवरोध;
	      हाल 11: STT(11, val); अवरोध;
	      हाल 12: STT(12, val); अवरोध;
	      हाल 13: STT(13, val); अवरोध;
	      हाल 14: STT(14, val); अवरोध;
	      हाल 15: STT(15, val); अवरोध;
	      हाल 16: STT(16, val); अवरोध;
	      हाल 17: STT(17, val); अवरोध;
	      हाल 18: STT(18, val); अवरोध;
	      हाल 19: STT(19, val); अवरोध;
	      हाल 20: STT(20, val); अवरोध;
	      हाल 21: STT(21, val); अवरोध;
	      हाल 22: STT(22, val); अवरोध;
	      हाल 23: STT(23, val); अवरोध;
	      हाल 24: STT(24, val); अवरोध;
	      हाल 25: STT(25, val); अवरोध;
	      हाल 26: STT(26, val); अवरोध;
	      हाल 27: STT(27, val); अवरोध;
	      हाल 28: STT(28, val); अवरोध;
	      हाल 29: STT(29, val); अवरोध;
	      हाल 30: STT(30, val); अवरोध;
	      हाल 31: STT(31, val); अवरोध;
	      शेष: वापस 0;
	पूर्ण
	वापस val;
पूर्ण
EXPORT_SYMBOL(alpha_पढ़ो_fp_reg);

#अगर defined(CONFIG_ALPHA_EV6) || defined(CONFIG_ALPHA_EV67)
#घोषणा LDT(reg,val)  यंत्र अस्थिर ("itoft %0,$f"#reg : : "r"(val));
#अन्यथा
#घोषणा LDT(reg,val)  यंत्र अस्थिर ("ldt $f"#reg",%0" : : "m"(val));
#पूर्ण_अगर

व्योम
alpha_ग_लिखो_fp_reg (अचिन्हित दीर्घ reg, अचिन्हित दीर्घ val)
अणु
	चयन (reg) अणु
	      हाल  0: LDT( 0, val); अवरोध;
	      हाल  1: LDT( 1, val); अवरोध;
	      हाल  2: LDT( 2, val); अवरोध;
	      हाल  3: LDT( 3, val); अवरोध;
	      हाल  4: LDT( 4, val); अवरोध;
	      हाल  5: LDT( 5, val); अवरोध;
	      हाल  6: LDT( 6, val); अवरोध;
	      हाल  7: LDT( 7, val); अवरोध;
	      हाल  8: LDT( 8, val); अवरोध;
	      हाल  9: LDT( 9, val); अवरोध;
	      हाल 10: LDT(10, val); अवरोध;
	      हाल 11: LDT(11, val); अवरोध;
	      हाल 12: LDT(12, val); अवरोध;
	      हाल 13: LDT(13, val); अवरोध;
	      हाल 14: LDT(14, val); अवरोध;
	      हाल 15: LDT(15, val); अवरोध;
	      हाल 16: LDT(16, val); अवरोध;
	      हाल 17: LDT(17, val); अवरोध;
	      हाल 18: LDT(18, val); अवरोध;
	      हाल 19: LDT(19, val); अवरोध;
	      हाल 20: LDT(20, val); अवरोध;
	      हाल 21: LDT(21, val); अवरोध;
	      हाल 22: LDT(22, val); अवरोध;
	      हाल 23: LDT(23, val); अवरोध;
	      हाल 24: LDT(24, val); अवरोध;
	      हाल 25: LDT(25, val); अवरोध;
	      हाल 26: LDT(26, val); अवरोध;
	      हाल 27: LDT(27, val); अवरोध;
	      हाल 28: LDT(28, val); अवरोध;
	      हाल 29: LDT(29, val); अवरोध;
	      हाल 30: LDT(30, val); अवरोध;
	      हाल 31: LDT(31, val); अवरोध;
	पूर्ण
पूर्ण
EXPORT_SYMBOL(alpha_ग_लिखो_fp_reg);

#अगर defined(CONFIG_ALPHA_EV6) || defined(CONFIG_ALPHA_EV67)
#घोषणा STS(reg,val)  यंत्र अस्थिर ("ftois $f"#reg",%0" : "=r"(val));
#अन्यथा
#घोषणा STS(reg,val)  यंत्र अस्थिर ("sts $f"#reg",%0" : "=m"(val));
#पूर्ण_अगर

अचिन्हित दीर्घ
alpha_पढ़ो_fp_reg_s (अचिन्हित दीर्घ reg)
अणु
	अचिन्हित दीर्घ val;

	चयन (reg) अणु
	      हाल  0: STS( 0, val); अवरोध;
	      हाल  1: STS( 1, val); अवरोध;
	      हाल  2: STS( 2, val); अवरोध;
	      हाल  3: STS( 3, val); अवरोध;
	      हाल  4: STS( 4, val); अवरोध;
	      हाल  5: STS( 5, val); अवरोध;
	      हाल  6: STS( 6, val); अवरोध;
	      हाल  7: STS( 7, val); अवरोध;
	      हाल  8: STS( 8, val); अवरोध;
	      हाल  9: STS( 9, val); अवरोध;
	      हाल 10: STS(10, val); अवरोध;
	      हाल 11: STS(11, val); अवरोध;
	      हाल 12: STS(12, val); अवरोध;
	      हाल 13: STS(13, val); अवरोध;
	      हाल 14: STS(14, val); अवरोध;
	      हाल 15: STS(15, val); अवरोध;
	      हाल 16: STS(16, val); अवरोध;
	      हाल 17: STS(17, val); अवरोध;
	      हाल 18: STS(18, val); अवरोध;
	      हाल 19: STS(19, val); अवरोध;
	      हाल 20: STS(20, val); अवरोध;
	      हाल 21: STS(21, val); अवरोध;
	      हाल 22: STS(22, val); अवरोध;
	      हाल 23: STS(23, val); अवरोध;
	      हाल 24: STS(24, val); अवरोध;
	      हाल 25: STS(25, val); अवरोध;
	      हाल 26: STS(26, val); अवरोध;
	      हाल 27: STS(27, val); अवरोध;
	      हाल 28: STS(28, val); अवरोध;
	      हाल 29: STS(29, val); अवरोध;
	      हाल 30: STS(30, val); अवरोध;
	      हाल 31: STS(31, val); अवरोध;
	      शेष: वापस 0;
	पूर्ण
	वापस val;
पूर्ण
EXPORT_SYMBOL(alpha_पढ़ो_fp_reg_s);

#अगर defined(CONFIG_ALPHA_EV6) || defined(CONFIG_ALPHA_EV67)
#घोषणा LDS(reg,val)  यंत्र अस्थिर ("itofs %0,$f"#reg : : "r"(val));
#अन्यथा
#घोषणा LDS(reg,val)  यंत्र अस्थिर ("lds $f"#reg",%0" : : "m"(val));
#पूर्ण_अगर

व्योम
alpha_ग_लिखो_fp_reg_s (अचिन्हित दीर्घ reg, अचिन्हित दीर्घ val)
अणु
	चयन (reg) अणु
	      हाल  0: LDS( 0, val); अवरोध;
	      हाल  1: LDS( 1, val); अवरोध;
	      हाल  2: LDS( 2, val); अवरोध;
	      हाल  3: LDS( 3, val); अवरोध;
	      हाल  4: LDS( 4, val); अवरोध;
	      हाल  5: LDS( 5, val); अवरोध;
	      हाल  6: LDS( 6, val); अवरोध;
	      हाल  7: LDS( 7, val); अवरोध;
	      हाल  8: LDS( 8, val); अवरोध;
	      हाल  9: LDS( 9, val); अवरोध;
	      हाल 10: LDS(10, val); अवरोध;
	      हाल 11: LDS(11, val); अवरोध;
	      हाल 12: LDS(12, val); अवरोध;
	      हाल 13: LDS(13, val); अवरोध;
	      हाल 14: LDS(14, val); अवरोध;
	      हाल 15: LDS(15, val); अवरोध;
	      हाल 16: LDS(16, val); अवरोध;
	      हाल 17: LDS(17, val); अवरोध;
	      हाल 18: LDS(18, val); अवरोध;
	      हाल 19: LDS(19, val); अवरोध;
	      हाल 20: LDS(20, val); अवरोध;
	      हाल 21: LDS(21, val); अवरोध;
	      हाल 22: LDS(22, val); अवरोध;
	      हाल 23: LDS(23, val); अवरोध;
	      हाल 24: LDS(24, val); अवरोध;
	      हाल 25: LDS(25, val); अवरोध;
	      हाल 26: LDS(26, val); अवरोध;
	      हाल 27: LDS(27, val); अवरोध;
	      हाल 28: LDS(28, val); अवरोध;
	      हाल 29: LDS(29, val); अवरोध;
	      हाल 30: LDS(30, val); अवरोध;
	      हाल 31: LDS(31, val); अवरोध;
	पूर्ण
पूर्ण
EXPORT_SYMBOL(alpha_ग_लिखो_fp_reg_s);
