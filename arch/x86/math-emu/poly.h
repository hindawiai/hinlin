<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*---------------------------------------------------------------------------+
 |  poly.h                                                                   |
 |                                                                           |
 |  Header file क्रम the FPU-emu poly*.c source files.                        |
 |                                                                           |
 | Copyright (C) 1994,1999                                                   |
 |                       W. Metzenthen, 22 Parker St, Ormond, Vic 3163,      |
 |                       Australia.  E-mail   billm@melbpc.org.au            |
 |                                                                           |
 | Declarations and definitions क्रम functions operating on Xsig (12-byte     |
 | extended-signअगरicand) quantities.                                         |
 |                                                                           |
 +---------------------------------------------------------------------------*/

#अगर_अघोषित _POLY_H
#घोषणा _POLY_H

/* This 12-byte काष्ठाure is used to improve the accuracy of computation
   of transcendental functions.
   Intended to be used to get results better than 8-byte computation
   allows. 9-byte would probably be sufficient.
   */
प्रकार काष्ठा अणु
	अचिन्हित दीर्घ lsw;
	अचिन्हित दीर्घ midw;
	अचिन्हित दीर्घ msw;
पूर्ण Xsig;

यंत्रlinkage व्योम mul64(अचिन्हित दीर्घ दीर्घ स्थिर *a, अचिन्हित दीर्घ दीर्घ स्थिर *b,
		      अचिन्हित दीर्घ दीर्घ *result);
यंत्रlinkage व्योम polynomial_Xsig(Xsig *, स्थिर अचिन्हित दीर्घ दीर्घ *x,
				स्थिर अचिन्हित दीर्घ दीर्घ terms[], स्थिर पूर्णांक n);

यंत्रlinkage व्योम mul32_Xsig(Xsig *, स्थिर अचिन्हित दीर्घ mult);
यंत्रlinkage व्योम mul64_Xsig(Xsig *, स्थिर अचिन्हित दीर्घ दीर्घ *mult);
यंत्रlinkage व्योम mul_Xsig_Xsig(Xsig *dest, स्थिर Xsig *mult);

यंत्रlinkage व्योम shr_Xsig(Xsig *, स्थिर पूर्णांक n);
यंत्रlinkage पूर्णांक round_Xsig(Xsig *);
यंत्रlinkage पूर्णांक norm_Xsig(Xsig *);
यंत्रlinkage व्योम भाग_Xsig(Xsig *x1, स्थिर Xsig *x2, स्थिर Xsig *dest);

/* Macro to extract the most signअगरicant 32 bits from a दीर्घ दीर्घ */
#घोषणा LL_MSW(x)     (((अचिन्हित दीर्घ *)&x)[1])

/* Macro to initialize an Xsig काष्ठा */
#घोषणा MK_XSIG(a,b,c)     अणु c, b, a पूर्ण

/* Macro to access the 8 ms bytes of an Xsig as a दीर्घ दीर्घ */
#घोषणा XSIG_LL(x)         (*(अचिन्हित दीर्घ दीर्घ *)&x.midw)

/*
   Need to run gcc with optimizations on to get these to
   actually be in-line.
   */

/* Multiply two fixed-poपूर्णांक 32 bit numbers, producing a 32 bit result.
   The answer is the ms word of the product. */
/* Some versions of gcc make it dअगरficult to stop eax from being clobbered.
   Merely specअगरying that it is used करोesn't work...
 */
अटल अंतरभूत अचिन्हित दीर्घ mul_32_32(स्थिर अचिन्हित दीर्घ arg1,
				      स्थिर अचिन्हित दीर्घ arg2)
अणु
	पूर्णांक retval;
	यंत्र अस्थिर ("mull %2; movl %%edx,%%eax":"=a" (retval)
		      :"0"(arg1), "g"(arg2)
		      :"dx");
	वापस retval;
पूर्ण

/* Add the 12 byte Xsig x2 to Xsig dest, with no checks क्रम overflow. */
अटल अंतरभूत व्योम add_Xsig_Xsig(Xsig *dest, स्थिर Xsig *x2)
अणु
	यंत्र अस्थिर ("movl %1,%%edi; movl %2,%%esi;\n"
		      "movl (%%esi),%%eax; addl %%eax,(%%edi);\n"
		      "movl 4(%%esi),%%eax; adcl %%eax,4(%%edi);\n"
		      "movl 8(%%esi),%%eax; adcl %%eax,8(%%edi);\n":"=g"
		      (*dest):"g"(dest), "g"(x2)
		      :"ax", "si", "di");
पूर्ण

/* Add the 12 byte Xsig x2 to Xsig dest, adjust exp अगर overflow occurs. */
/* Note: the स्थिरraपूर्णांकs in the यंत्र statement didn't always work properly
   with gcc 2.5.8.  Changing from using edi to using ecx got around the
   problem, but keep fingers crossed! */
अटल अंतरभूत व्योम add_two_Xsig(Xsig *dest, स्थिर Xsig *x2, दीर्घ पूर्णांक *exp)
अणु
	यंत्र अस्थिर ("movl %2,%%ecx; movl %3,%%esi;\n"
		      "movl (%%esi),%%eax; addl %%eax,(%%ecx);\n"
		      "movl 4(%%esi),%%eax; adcl %%eax,4(%%ecx);\n"
		      "movl 8(%%esi),%%eax; adcl %%eax,8(%%ecx);\n"
		      "jnc 0f;\n"
		      "rcrl 8(%%ecx); rcrl 4(%%ecx); rcrl (%%ecx)\n"
		      "movl %4,%%ecx; incl (%%ecx)\n"
		      "movl $1,%%eax; jmp 1f;\n"
		      "0: xorl %%eax,%%eax;\n" "1:\n":"=g" (*exp), "=g"(*dest)
		      :"g"(dest), "g"(x2), "g"(exp)
		      :"cx", "si", "ax");
पूर्ण

/* Negate (subtract from 1.0) the 12 byte Xsig */
/* This is faster in a loop on my 386 than using the "neg" inकाष्ठाion. */
अटल अंतरभूत व्योम negate_Xsig(Xsig *x)
अणु
	यंत्र अस्थिर ("movl %1,%%esi;\n"
		      "xorl %%ecx,%%ecx;\n"
		      "movl %%ecx,%%eax; subl (%%esi),%%eax; movl %%eax,(%%esi);\n"
		      "movl %%ecx,%%eax; sbbl 4(%%esi),%%eax; movl %%eax,4(%%esi);\n"
		      "movl %%ecx,%%eax; sbbl 8(%%esi),%%eax; movl %%eax,8(%%esi);\n":"=g"
		      (*x):"g"(x):"si", "ax", "cx");
पूर्ण

#पूर्ण_अगर /* _POLY_H */
