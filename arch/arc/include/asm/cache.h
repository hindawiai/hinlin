<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2004, 2007-2010, 2011-2012 Synopsys, Inc. (www.synopsys.com)
 */

#अगर_अघोषित __ARC_ASM_CACHE_H
#घोषणा __ARC_ASM_CACHE_H

/* In हाल $$ not config, setup a dummy number क्रम rest of kernel */
#अगर_अघोषित CONFIG_ARC_CACHE_LINE_SHIFT
#घोषणा L1_CACHE_SHIFT		6
#अन्यथा
#घोषणा L1_CACHE_SHIFT		CONFIG_ARC_CACHE_LINE_SHIFT
#पूर्ण_अगर

#घोषणा L1_CACHE_BYTES		(1 << L1_CACHE_SHIFT)
#घोषणा CACHE_LINE_MASK		(~(L1_CACHE_BYTES - 1))

/*
 * ARC700 करोesn't cache any access in top 1G (0xc000_0000 to 0xFFFF_FFFF)
 * Ideal क्रम wiring memory mapped peripherals as we करोn't need to करो
 * explicit uncached accesses (LD.di/ST.di) hence more portable drivers
 */
#घोषणा ARC_UNCACHED_ADDR_SPACE	0xc0000000

#अगर_अघोषित __ASSEMBLY__

#समावेश <linux/build_bug.h>

/* Uncached access macros */
#घोषणा arc_पढ़ो_uncached_32(ptr)	\
(अणु					\
	अचिन्हित पूर्णांक __ret;		\
	__यंत्र__ __अस्थिर__(		\
	"	ld.di %0, [%1]	\n"	\
	: "=r"(__ret)			\
	: "r"(ptr));			\
	__ret;				\
पूर्ण)

#घोषणा arc_ग_लिखो_uncached_32(ptr, data)\
(अणु					\
	__यंत्र__ __अस्थिर__(		\
	"	st.di %0, [%1]	\n"	\
	:				\
	: "r"(data), "r"(ptr));		\
पूर्ण)

/* Largest line length क्रम either L1 or L2 is 128 bytes */
#घोषणा SMP_CACHE_BYTES		128
#घोषणा cache_line_size()	SMP_CACHE_BYTES
#घोषणा ARCH_DMA_MINALIGN	SMP_CACHE_BYTES

/*
 * Make sure slab-allocated buffers are 64-bit aligned when atomic64_t uses
 * ARCv2 64-bit atomics (LLOCKD/SCONDD). This guarantess runसमय 64-bit
 * alignment क्रम any atomic64_t embedded in buffer.
 * Default ARCH_SLAB_MINALIGN is __alignof__(दीर्घ दीर्घ) which has a relaxed
 * value of 4 (and not 8) in ARC ABI.
 */
#अगर defined(CONFIG_ARC_HAS_LL64) && defined(CONFIG_ARC_HAS_LLSC)
#घोषणा ARCH_SLAB_MINALIGN	8
#पूर्ण_अगर

बाह्य व्योम arc_cache_init(व्योम);
बाह्य अक्षर *arc_cache_mumbojumbo(पूर्णांक cpu_id, अक्षर *buf, पूर्णांक len);
बाह्य व्योम पढ़ो_decode_cache_bcr(व्योम);

बाह्य पूर्णांक ioc_enable;
बाह्य अचिन्हित दीर्घ perip_base, perip_end;

#पूर्ण_अगर	/* !__ASSEMBLY__ */

/* Inकाष्ठाion cache related Auxiliary रेजिस्टरs */
#घोषणा ARC_REG_IC_BCR		0x77	/* Build Config reg */
#घोषणा ARC_REG_IC_IVIC		0x10
#घोषणा ARC_REG_IC_CTRL		0x11
#घोषणा ARC_REG_IC_IVIR		0x16
#घोषणा ARC_REG_IC_ENDR		0x17
#घोषणा ARC_REG_IC_IVIL		0x19
#घोषणा ARC_REG_IC_PTAG		0x1E
#घोषणा ARC_REG_IC_PTAG_HI	0x1F

/* Bit val in IC_CTRL */
#घोषणा IC_CTRL_DIS		0x1

/* Data cache related Auxiliary रेजिस्टरs */
#घोषणा ARC_REG_DC_BCR		0x72	/* Build Config reg */
#घोषणा ARC_REG_DC_IVDC		0x47
#घोषणा ARC_REG_DC_CTRL		0x48
#घोषणा ARC_REG_DC_IVDL		0x4A
#घोषणा ARC_REG_DC_FLSH		0x4B
#घोषणा ARC_REG_DC_FLDL		0x4C
#घोषणा ARC_REG_DC_STARTR	0x4D
#घोषणा ARC_REG_DC_ENDR		0x4E
#घोषणा ARC_REG_DC_PTAG		0x5C
#घोषणा ARC_REG_DC_PTAG_HI	0x5F

/* Bit val in DC_CTRL */
#घोषणा DC_CTRL_DIS		0x001
#घोषणा DC_CTRL_INV_MODE_FLUSH	0x040
#घोषणा DC_CTRL_FLUSH_STATUS	0x100
#घोषणा DC_CTRL_RGN_OP_INV	0x200
#घोषणा DC_CTRL_RGN_OP_MSK	0x200

/*System-level cache (L2 cache) related Auxiliary रेजिस्टरs */
#घोषणा ARC_REG_SLC_CFG		0x901
#घोषणा ARC_REG_SLC_CTRL	0x903
#घोषणा ARC_REG_SLC_FLUSH	0x904
#घोषणा ARC_REG_SLC_INVALIDATE	0x905
#घोषणा ARC_AUX_SLC_IVDL	0x910
#घोषणा ARC_AUX_SLC_FLDL	0x912
#घोषणा ARC_REG_SLC_RGN_START	0x914
#घोषणा ARC_REG_SLC_RGN_START1	0x915
#घोषणा ARC_REG_SLC_RGN_END	0x916
#घोषणा ARC_REG_SLC_RGN_END1	0x917

/* Bit val in SLC_CONTROL */
#घोषणा SLC_CTRL_DIS		0x001
#घोषणा SLC_CTRL_IM		0x040
#घोषणा SLC_CTRL_BUSY		0x100
#घोषणा SLC_CTRL_RGN_OP_INV	0x200

/* IO coherency related Auxiliary रेजिस्टरs */
#घोषणा ARC_REG_IO_COH_ENABLE	0x500
#घोषणा ARC_IO_COH_ENABLE_BIT	BIT(0)
#घोषणा ARC_REG_IO_COH_PARTIAL	0x501
#घोषणा ARC_IO_COH_PARTIAL_BIT	BIT(0)
#घोषणा ARC_REG_IO_COH_AP0_BASE	0x508
#घोषणा ARC_REG_IO_COH_AP0_SIZE	0x509

#पूर्ण_अगर /* _ASM_CACHE_H */
