<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Written 2000 by Andi Kleen */
#अगर_अघोषित _ASM_X86_DESC_DEFS_H
#घोषणा _ASM_X86_DESC_DEFS_H

/*
 * Segment descriptor काष्ठाure definitions, usable from both x86_64 and i386
 * archs.
 */

#अगर_अघोषित __ASSEMBLY__

#समावेश <linux/types.h>

/* 8 byte segment descriptor */
काष्ठा desc_काष्ठा अणु
	u16	limit0;
	u16	base0;
	u16	base1: 8, type: 4, s: 1, dpl: 2, p: 1;
	u16	limit1: 4, avl: 1, l: 1, d: 1, g: 1, base2: 8;
पूर्ण __attribute__((packed));

#घोषणा GDT_ENTRY_INIT(flags, base, limit)			\
	अणु							\
		.limit0		= (u16) (limit),		\
		.limit1		= ((limit) >> 16) & 0x0F,	\
		.base0		= (u16) (base),			\
		.base1		= ((base) >> 16) & 0xFF,	\
		.base2		= ((base) >> 24) & 0xFF,	\
		.type		= (flags & 0x0f),		\
		.s		= (flags >> 4) & 0x01,		\
		.dpl		= (flags >> 5) & 0x03,		\
		.p		= (flags >> 7) & 0x01,		\
		.avl		= (flags >> 12) & 0x01,		\
		.l		= (flags >> 13) & 0x01,		\
		.d		= (flags >> 14) & 0x01,		\
		.g		= (flags >> 15) & 0x01,		\
	पूर्ण

क्रमागत अणु
	GATE_INTERRUPT = 0xE,
	GATE_TRAP = 0xF,
	GATE_CALL = 0xC,
	GATE_TASK = 0x5,
पूर्ण;

क्रमागत अणु
	DESC_TSS = 0x9,
	DESC_LDT = 0x2,
	DESCTYPE_S = 0x10,	/* !प्रणाली */
पूर्ण;

/* LDT or TSS descriptor in the GDT. */
काष्ठा ldttss_desc अणु
	u16	limit0;
	u16	base0;

	u16	base1 : 8, type : 5, dpl : 2, p : 1;
	u16	limit1 : 4, zero0 : 3, g : 1, base2 : 8;
#अगर_घोषित CONFIG_X86_64
	u32	base3;
	u32	zero1;
#पूर्ण_अगर
पूर्ण __attribute__((packed));

प्रकार काष्ठा ldttss_desc ldt_desc;
प्रकार काष्ठा ldttss_desc tss_desc;

काष्ठा idt_bits अणु
	u16		ist	: 3,
			zero	: 5,
			type	: 5,
			dpl	: 2,
			p	: 1;
पूर्ण __attribute__((packed));

काष्ठा idt_data अणु
	अचिन्हित पूर्णांक	vector;
	अचिन्हित पूर्णांक	segment;
	काष्ठा idt_bits	bits;
	स्थिर व्योम	*addr;
पूर्ण;

काष्ठा gate_काष्ठा अणु
	u16		offset_low;
	u16		segment;
	काष्ठा idt_bits	bits;
	u16		offset_middle;
#अगर_घोषित CONFIG_X86_64
	u32		offset_high;
	u32		reserved;
#पूर्ण_अगर
पूर्ण __attribute__((packed));

प्रकार काष्ठा gate_काष्ठा gate_desc;

अटल अंतरभूत अचिन्हित दीर्घ gate_offset(स्थिर gate_desc *g)
अणु
#अगर_घोषित CONFIG_X86_64
	वापस g->offset_low | ((अचिन्हित दीर्घ)g->offset_middle << 16) |
		((अचिन्हित दीर्घ) g->offset_high << 32);
#अन्यथा
	वापस g->offset_low | ((अचिन्हित दीर्घ)g->offset_middle << 16);
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ gate_segment(स्थिर gate_desc *g)
अणु
	वापस g->segment;
पूर्ण

काष्ठा desc_ptr अणु
	अचिन्हित लघु size;
	अचिन्हित दीर्घ address;
पूर्ण __attribute__((packed)) ;

#पूर्ण_अगर /* !__ASSEMBLY__ */

/* Boot IDT definitions */
#घोषणा	BOOT_IDT_ENTRIES	32

/* Access rights as वापसed by LAR */
#घोषणा AR_TYPE_RODATA		(0 * (1 << 9))
#घोषणा AR_TYPE_RWDATA		(1 * (1 << 9))
#घोषणा AR_TYPE_RODATA_EXPDOWN	(2 * (1 << 9))
#घोषणा AR_TYPE_RWDATA_EXPDOWN	(3 * (1 << 9))
#घोषणा AR_TYPE_XOCODE		(4 * (1 << 9))
#घोषणा AR_TYPE_XRCODE		(5 * (1 << 9))
#घोषणा AR_TYPE_XOCODE_CONF	(6 * (1 << 9))
#घोषणा AR_TYPE_XRCODE_CONF	(7 * (1 << 9))
#घोषणा AR_TYPE_MASK		(7 * (1 << 9))

#घोषणा AR_DPL0			(0 * (1 << 13))
#घोषणा AR_DPL3			(3 * (1 << 13))
#घोषणा AR_DPL_MASK		(3 * (1 << 13))

#घोषणा AR_A			(1 << 8)   /* "Accessed" */
#घोषणा AR_S			(1 << 12)  /* If clear, "System" segment */
#घोषणा AR_P			(1 << 15)  /* "Present" */
#घोषणा AR_AVL			(1 << 20)  /* "AVaiLable" (no HW effect) */
#घोषणा AR_L			(1 << 21)  /* "Long mode" क्रम code segments */
#घोषणा AR_DB			(1 << 22)  /* D/B, effect depends on type */
#घोषणा AR_G			(1 << 23)  /* "Granularity" (limit in pages) */

#पूर्ण_अगर /* _ASM_X86_DESC_DEFS_H */
