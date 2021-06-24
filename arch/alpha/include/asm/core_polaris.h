<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ALPHA_POLARIS__H__
#घोषणा __ALPHA_POLARIS__H__

#समावेश <linux/types.h>
#समावेश <यंत्र/compiler.h>

/*
 * POLARIS is the पूर्णांकernal name क्रम a core logic chipset which provides
 * memory controller and PCI access क्रम the 21164PC chip based प्रणालीs.
 *
 * This file is based on:
 *
 * Polaris System Controller
 * Device Functional Specअगरication
 * 22-Jan-98
 * Rev. 4.2
 *
 */

/* Polaris memory regions */
#घोषणा POLARIS_SPARSE_MEM_BASE		(IDENT_ADDR + 0xf800000000UL)
#घोषणा POLARIS_DENSE_MEM_BASE		(IDENT_ADDR + 0xf900000000UL)
#घोषणा POLARIS_SPARSE_IO_BASE		(IDENT_ADDR + 0xf980000000UL)
#घोषणा POLARIS_SPARSE_CONFIG_BASE	(IDENT_ADDR + 0xf9c0000000UL)
#घोषणा POLARIS_IACK_BASE		(IDENT_ADDR + 0xf9f8000000UL)
#घोषणा POLARIS_DENSE_IO_BASE		(IDENT_ADDR + 0xf9fc000000UL)
#घोषणा POLARIS_DENSE_CONFIG_BASE	(IDENT_ADDR + 0xf9fe000000UL)

#घोषणा POLARIS_IACK_SC			POLARIS_IACK_BASE

/* The Polaris command/status रेजिस्टरs live in PCI Config space क्रम
 * bus 0/device 0.  As such, they may be bytes, words, or द्विगुनwords.
 */
#घोषणा POLARIS_W_VENID		(POLARIS_DENSE_CONFIG_BASE)
#घोषणा POLARIS_W_DEVID		(POLARIS_DENSE_CONFIG_BASE+2)
#घोषणा POLARIS_W_CMD		(POLARIS_DENSE_CONFIG_BASE+4)
#घोषणा POLARIS_W_STATUS	(POLARIS_DENSE_CONFIG_BASE+6)

/*
 * Data काष्ठाure क्रम handling POLARIS machine checks:
 */
काष्ठा el_POLARIS_sysdata_mcheck अणु
    u_दीर्घ      psc_status;
    u_दीर्घ	psc_pcictl0;
    u_दीर्घ	psc_pcictl1;
    u_दीर्घ	psc_pcictl2;
पूर्ण;

#अगर_घोषित __KERNEL__

#अगर_अघोषित __EXTERN_INLINE
#घोषणा __EXTERN_INLINE बाह्य अंतरभूत
#घोषणा __IO_EXTERN_INLINE
#पूर्ण_अगर

/*
 * I/O functions:
 *
 * POLARIS, the PCI/memory support chipset क्रम the PCA56 (21164PC)
 * processors, can use either a sparse address  mapping scheme, or the 
 * so-called byte-word PCI address space, to get at PCI memory and I/O.
 *
 * However, we will support only the BWX क्रमm.
 */

/*
 * Memory functions.  Polaris allows all accesses (byte/word
 * as well as दीर्घ/quad) to be करोne through dense space.
 *
 * We will only support DENSE access via BWX insns.
 */

__EXTERN_INLINE व्योम __iomem *polaris_ioporपंचांगap(अचिन्हित दीर्घ addr)
अणु
	वापस (व्योम __iomem *)(addr + POLARIS_DENSE_IO_BASE);
पूर्ण

__EXTERN_INLINE व्योम __iomem *polaris_ioremap(अचिन्हित दीर्घ addr,
					      अचिन्हित दीर्घ size)
अणु
	वापस (व्योम __iomem *)(addr + POLARIS_DENSE_MEM_BASE);
पूर्ण

__EXTERN_INLINE पूर्णांक polaris_is_ioaddr(अचिन्हित दीर्घ addr)
अणु
	वापस addr >= POLARIS_SPARSE_MEM_BASE;
पूर्ण

__EXTERN_INLINE पूर्णांक polaris_is_mmio(स्थिर अस्थिर व्योम __iomem *addr)
अणु
	वापस (अचिन्हित दीर्घ)addr < POLARIS_SPARSE_IO_BASE;
पूर्ण

#अघोषित __IO_PREFIX
#घोषणा __IO_PREFIX		polaris
#घोषणा polaris_trivial_rw_bw	1
#घोषणा polaris_trivial_rw_lq	1
#घोषणा polaris_trivial_io_bw	1
#घोषणा polaris_trivial_io_lq	1
#घोषणा polaris_trivial_iounmap	1
#समावेश <यंत्र/io_trivial.h>

#अगर_घोषित __IO_EXTERN_INLINE
#अघोषित __EXTERN_INLINE
#अघोषित __IO_EXTERN_INLINE
#पूर्ण_अगर

#पूर्ण_अगर /* __KERNEL__ */

#पूर्ण_अगर /* __ALPHA_POLARIS__H__ */
