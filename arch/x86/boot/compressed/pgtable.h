<शैली गुरु>
#अगर_अघोषित BOOT_COMPRESSED_PAGETABLE_H
#घोषणा BOOT_COMPRESSED_PAGETABLE_H

#घोषणा TRAMPOLINE_32BIT_SIZE		(2 * PAGE_SIZE)

#घोषणा TRAMPOLINE_32BIT_PGTABLE_OFFSET	0

#घोषणा TRAMPOLINE_32BIT_CODE_OFFSET	PAGE_SIZE
#घोषणा TRAMPOLINE_32BIT_CODE_SIZE	0x70

#घोषणा TRAMPOLINE_32BIT_STACK_END	TRAMPOLINE_32BIT_SIZE

#अगर_अघोषित __ASSEMBLER__

बाह्य अचिन्हित दीर्घ *trampoline_32bit;

बाह्य व्योम trampoline_32bit_src(व्योम *वापस_ptr);

#पूर्ण_अगर /* __ASSEMBLER__ */
#पूर्ण_अगर /* BOOT_COMPRESSED_PAGETABLE_H */
