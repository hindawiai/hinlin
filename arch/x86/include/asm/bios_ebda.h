<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_X86_BIOS_EBDA_H
#घोषणा _ASM_X86_BIOS_EBDA_H

#समावेश <यंत्र/पन.स>

/*
 * Returns physical address of EBDA.  Returns 0 अगर there is no EBDA.
 */
अटल अंतरभूत अचिन्हित पूर्णांक get_bios_ebda(व्योम)
अणु
	/*
	 * There is a real-mode segmented poपूर्णांकer poपूर्णांकing to the
	 * 4K EBDA area at 0x40E.
	 */
	अचिन्हित पूर्णांक address = *(अचिन्हित लघु *)phys_to_virt(0x40E);
	address <<= 4;
	वापस address;	/* 0 means none */
पूर्ण

व्योम reserve_bios_regions(व्योम);

#अगर_घोषित CONFIG_X86_CHECK_BIOS_CORRUPTION
/*
 * This is obviously not a great place क्रम this, but we want to be
 * able to scatter it around anywhere in the kernel.
 */
व्योम check_क्रम_bios_corruption(व्योम);
व्योम start_periodic_check_क्रम_corruption(व्योम);
#अन्यथा
अटल अंतरभूत व्योम check_क्रम_bios_corruption(व्योम)
अणु
पूर्ण

अटल अंतरभूत व्योम start_periodic_check_क्रम_corruption(व्योम)
अणु
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* _ASM_X86_BIOS_EBDA_H */
