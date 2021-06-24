<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Definitions क्रम Sun3 custom MMU.
 */
#अगर_अघोषित __SUN3_MMU_H__
#घोषणा __SUN3_MMU_H__

#समावेश <linux/types.h>
#समावेश <यंत्र/movs.h>
#समावेश <यंत्र/sun3-head.h>

/* MMU अक्षरacteristics. */
#घोषणा SUN3_SEGMAPS_PER_CONTEXT	2048
#घोषणा SUN3_PMEGS_NUM			256
#घोषणा SUN3_CONTEXTS_NUM               8

#घोषणा SUN3_PMEG_SIZE_BITS	 17
#घोषणा SUN3_PMEG_SIZE		 (1 << SUN3_PMEG_SIZE_BITS)
#घोषणा SUN3_PMEG_MASK		 (SUN3_PMEG_SIZE - 1)

#घोषणा SUN3_PTE_SIZE_BITS       13
#घोषणा SUN3_PTE_SIZE		 (1 << SUN3_PTE_SIZE_BITS)
#घोषणा SUN3_PTE_MASK		 (SUN3_PTE_SIZE - 1)

#घोषणा SUN3_CONTROL_MASK       (0x0FFFFFFC)
#घोषणा SUN3_INVALID_PMEG	255
#घोषणा SUN3_INVALID_CONTEXT 255

#घोषणा AC_IDPROM     0x00000000    /* 34  ID PROM, R/O, byte, 32 bytes      */
#घोषणा AC_PAGEMAP    0x10000000    /* 3   Pagemap R/W, दीर्घ                 */
#घोषणा AC_SEGMAP     0x20000000    /* 3   Segment map, byte                 */
#घोषणा AC_CONTEXT    0x30000000    /* 34c current mmu-context               */
#घोषणा AC_SENABLE    0x40000000    /* 34c प्रणाली dvma/cache/reset enable reg*/
#घोषणा AC_UDVMA_ENB  0x50000000    /* 34  Not used on Sun boards, byte      */
#घोषणा AC_BUS_ERROR  0x60000000    /* 34  Cleared on पढ़ो, byte.            */
#घोषणा AC_SYNC_ERR   0x60000000    /*   c fault type                        */
#घोषणा AC_SYNC_VA    0x60000004    /*   c fault भव address             */
#घोषणा AC_ASYNC_ERR  0x60000008    /*   c asynchronous fault type           */
#घोषणा AC_ASYNC_VA   0x6000000c    /*   c async fault भव address       */
#घोषणा AC_LEDS       0x70000000    /* 34  Zero turns on LEDs, byte          */
#घोषणा AC_CACHETAGS  0x80000000    /* 34c direct access to the VAC tags     */
#घोषणा AC_CACHEDDATA 0x90000000    /* 3 c direct access to the VAC data     */
#घोषणा AC_UDVMA_MAP  0xD0000000    /* 4   Not used on Sun boards, byte      */
#घोषणा AC_VME_VECTOR 0xE0000000    /* 4   For non-Autovector VME, byte      */
#घोषणा AC_BOOT_SCC   0xF0000000    /* 34  bypass to access Zilog 8530. byte.*/

#घोषणा SUN3_PAGE_CHG_MASK (SUN3_PAGE_PGNUM_MASK \
			    | SUN3_PAGE_ACCESSED | SUN3_PAGE_MODIFIED)

/* Bus access type within PTE. */
#घोषणा SUN3_PAGE_TYPE_MASK   (0x0c000000)
#घोषणा SUN3_PAGE_TYPE_MEMORY (0x00000000)
#घोषणा SUN3_PAGE_TYPE_IO     (0x04000000)
#घोषणा SUN3_PAGE_TYPE_VME16  (0x08000000)
#घोषणा SUN3_PAGE_TYPE_VME32  (0x0c000000)

/* Mask क्रम page number within PTE. */
#घोषणा SUN3_PAGE_PGNUM_MASK (0x0007FFFF)

/* Bits within bus-error रेजिस्टर. */
#घोषणा SUN3_BUSERR_WATCHDOG	(0x01)
#घोषणा SUN3_BUSERR_unused	(0x02)
#घोषणा SUN3_BUSERR_FPAENERR	(0x04)
#घोषणा SUN3_BUSERR_FPABERR	(0x08)
#घोषणा SUN3_BUSERR_VMEBERR	(0x10)
#घोषणा SUN3_BUSERR_TIMEOUT	(0x20)
#घोषणा SUN3_BUSERR_PROTERR	(0x40)
#घोषणा SUN3_BUSERR_INVALID	(0x80)

#अगर_अघोषित __ASSEMBLY__

/* Read bus error status रेजिस्टर (implicitly clearing it). */
अटल अंतरभूत अचिन्हित अक्षर sun3_get_buserr(व्योम)
अणु
	अचिन्हित अक्षर sfc, c;

	GET_SFC (sfc);
	SET_SFC (FC_CONTROL);
	GET_CONTROL_BYTE (AC_BUS_ERROR, c);
	SET_SFC (sfc);

	वापस c;
पूर्ण

/* Read segmap from hardware MMU. */
अटल अंतरभूत अचिन्हित दीर्घ sun3_get_segmap(अचिन्हित दीर्घ addr)
अणु
        रेजिस्टर अचिन्हित दीर्घ entry;
        अचिन्हित अक्षर c, sfc;

        GET_SFC (sfc);
        SET_SFC (FC_CONTROL);
        GET_CONTROL_BYTE (AC_SEGMAP | (addr & SUN3_CONTROL_MASK), c);
        SET_SFC (sfc);
        entry = c;

        वापस entry;
पूर्ण

/* Write segmap to hardware MMU. */
अटल अंतरभूत व्योम sun3_put_segmap(अचिन्हित दीर्घ addr, अचिन्हित दीर्घ entry)
अणु
        अचिन्हित अक्षर sfc;

        GET_DFC (sfc);
        SET_DFC (FC_CONTROL);
        SET_CONTROL_BYTE (AC_SEGMAP | (addr & SUN3_CONTROL_MASK), entry);
	SET_DFC (sfc);

        वापस;
पूर्ण

/* Read PTE from hardware MMU. */
अटल अंतरभूत अचिन्हित दीर्घ sun3_get_pte(अचिन्हित दीर्घ addr)
अणु
        रेजिस्टर अचिन्हित दीर्घ entry;
        अचिन्हित अक्षर sfc;

        GET_SFC (sfc);
        SET_SFC (FC_CONTROL);
        GET_CONTROL_WORD (AC_PAGEMAP | (addr & SUN3_CONTROL_MASK), entry);
        SET_SFC (sfc);

        वापस entry;
पूर्ण

/* Write PTE to hardware MMU. */
अटल अंतरभूत व्योम sun3_put_pte(अचिन्हित दीर्घ addr, अचिन्हित दीर्घ entry)
अणु
        अचिन्हित अक्षर sfc;

        GET_DFC (sfc);
        SET_DFC (FC_CONTROL);
        SET_CONTROL_WORD (AC_PAGEMAP | (addr & SUN3_CONTROL_MASK), entry);
	SET_DFC (sfc);

        वापस;
पूर्ण

/* get current context */
अटल अंतरभूत अचिन्हित अक्षर sun3_get_context(व्योम)
अणु
	अचिन्हित अक्षर sfc, c;

	GET_SFC(sfc);
	SET_SFC(FC_CONTROL);
	GET_CONTROL_BYTE(AC_CONTEXT, c);
	SET_SFC(sfc);

	वापस c;
पूर्ण

/* set alternate context */
अटल अंतरभूत व्योम sun3_put_context(अचिन्हित अक्षर c)
अणु
	अचिन्हित अक्षर dfc;
	GET_DFC(dfc);
	SET_DFC(FC_CONTROL);
	SET_CONTROL_BYTE(AC_CONTEXT, c);
	SET_DFC(dfc);

	वापस;
पूर्ण

बाह्य व्योम __iomem *sun3_ioremap(अचिन्हित दीर्घ phys, अचिन्हित दीर्घ size,
			  अचिन्हित दीर्घ type);

बाह्य पूर्णांक sun3_map_test(अचिन्हित दीर्घ addr, अक्षर *val);

#पूर्ण_अगर	/* !__ASSEMBLY__ */

#पूर्ण_अगर	/* !__SUN3_MMU_H__ */
