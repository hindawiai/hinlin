<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ASM_ARM_CP15_H
#घोषणा __ASM_ARM_CP15_H

#समावेश <यंत्र/barrier.h>

/*
 * CR1 bits (CP#15 CR1)
 */
#घोषणा CR_M	(1 << 0)	/* MMU enable				*/
#घोषणा CR_A	(1 << 1)	/* Alignment पात enable		*/
#घोषणा CR_C	(1 << 2)	/* Dcache enable			*/
#घोषणा CR_W	(1 << 3)	/* Write buffer enable			*/
#घोषणा CR_P	(1 << 4)	/* 32-bit exception handler		*/
#घोषणा CR_D	(1 << 5)	/* 32-bit data address range		*/
#घोषणा CR_L	(1 << 6)	/* Implementation defined		*/
#घोषणा CR_B	(1 << 7)	/* Big endian				*/
#घोषणा CR_S	(1 << 8)	/* System MMU protection		*/
#घोषणा CR_R	(1 << 9)	/* ROM MMU protection			*/
#घोषणा CR_F	(1 << 10)	/* Implementation defined		*/
#घोषणा CR_Z	(1 << 11)	/* Implementation defined		*/
#घोषणा CR_I	(1 << 12)	/* Icache enable			*/
#घोषणा CR_V	(1 << 13)	/* Vectors relocated to 0xffff0000	*/
#घोषणा CR_RR	(1 << 14)	/* Round Robin cache replacement	*/
#घोषणा CR_L4	(1 << 15)	/* LDR pc can set T bit			*/
#घोषणा CR_DT	(1 << 16)
#अगर_घोषित CONFIG_MMU
#घोषणा CR_HA	(1 << 17)	/* Hardware management of Access Flag   */
#अन्यथा
#घोषणा CR_BR	(1 << 17)	/* MPU Background region enable (PMSA)  */
#पूर्ण_अगर
#घोषणा CR_IT	(1 << 18)
#घोषणा CR_ST	(1 << 19)
#घोषणा CR_FI	(1 << 21)	/* Fast पूर्णांकerrupt (lower latency mode)	*/
#घोषणा CR_U	(1 << 22)	/* Unaligned access operation		*/
#घोषणा CR_XP	(1 << 23)	/* Extended page tables			*/
#घोषणा CR_VE	(1 << 24)	/* Vectored पूर्णांकerrupts			*/
#घोषणा CR_EE	(1 << 25)	/* Exception (Big) Endian		*/
#घोषणा CR_TRE	(1 << 28)	/* TEX remap enable			*/
#घोषणा CR_AFE	(1 << 29)	/* Access flag enable			*/
#घोषणा CR_TE	(1 << 30)	/* Thumb exception enable		*/

#अगर_अघोषित __ASSEMBLY__

#अगर __LINUX_ARM_ARCH__ >= 4
#घोषणा vectors_high()	(get_cr() & CR_V)
#अन्यथा
#घोषणा vectors_high()	(0)
#पूर्ण_अगर

#अगर_घोषित CONFIG_CPU_CP15

#समावेश <यंत्र/vdso/cp15.h>

बाह्य अचिन्हित दीर्घ cr_alignment;	/* defined in entry-armv.S */

अटल अंतरभूत अचिन्हित दीर्घ get_cr(व्योम)
अणु
	अचिन्हित दीर्घ val;
	यंत्र("mrc p15, 0, %0, c1, c0, 0	@ get CR" : "=r" (val) : : "cc");
	वापस val;
पूर्ण

अटल अंतरभूत व्योम set_cr(अचिन्हित दीर्घ val)
अणु
	यंत्र अस्थिर("mcr p15, 0, %0, c1, c0, 0	@ set CR"
	  : : "r" (val) : "cc");
	isb();
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक get_auxcr(व्योम)
अणु
	अचिन्हित पूर्णांक val;
	यंत्र("mrc p15, 0, %0, c1, c0, 1	@ get AUXCR" : "=r" (val));
	वापस val;
पूर्ण

अटल अंतरभूत व्योम set_auxcr(अचिन्हित पूर्णांक val)
अणु
	यंत्र अस्थिर("mcr p15, 0, %0, c1, c0, 1	@ set AUXCR"
	  : : "r" (val));
	isb();
पूर्ण

#घोषणा CPACC_FULL(n)		(3 << (n * 2))
#घोषणा CPACC_SVC(n)		(1 << (n * 2))
#घोषणा CPACC_DISABLE(n)	(0 << (n * 2))

अटल अंतरभूत अचिन्हित पूर्णांक get_copro_access(व्योम)
अणु
	अचिन्हित पूर्णांक val;
	यंत्र("mrc p15, 0, %0, c1, c0, 2 @ get copro access"
	  : "=r" (val) : : "cc");
	वापस val;
पूर्ण

अटल अंतरभूत व्योम set_copro_access(अचिन्हित पूर्णांक val)
अणु
	यंत्र अस्थिर("mcr p15, 0, %0, c1, c0, 2 @ set copro access"
	  : : "r" (val) : "cc");
	isb();
पूर्ण

#अन्यथा /* अगरdef CONFIG_CPU_CP15 */

/*
 * cr_alignment is tightly coupled to cp15 (at least in the minds of the
 * developers). Yielding 0 क्रम machines without a cp15 (and making it
 * पढ़ो-only) is fine क्रम most हालs and saves quite some #अगर_घोषितfery.
 */
#घोषणा cr_alignment	UL(0)

अटल अंतरभूत अचिन्हित दीर्घ get_cr(व्योम)
अणु
	वापस 0;
पूर्ण

#पूर्ण_अगर /* अगरdef CONFIG_CPU_CP15 / अन्यथा */

#पूर्ण_अगर /* अगरndef __ASSEMBLY__ */

#पूर्ण_अगर
