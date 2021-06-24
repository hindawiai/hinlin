<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * arch/sh/boards/mach-x3proto/ilsel.c
 *
 * Helper routines क्रम SH-X3 proto board ILSEL.
 *
 * Copyright (C) 2007 - 2010  Paul Mundt
 */
#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/biपंचांगap.h>
#समावेश <linux/पन.स>
#समावेश <mach/ilsel.h>

/*
 * ILSEL is split across:
 *
 *	ILSEL0 - 0xb8100004 [ Levels  1 -  4 ]
 *	ILSEL1 - 0xb8100006 [ Levels  5 -  8 ]
 *	ILSEL2 - 0xb8100008 [ Levels  9 - 12 ]
 *	ILSEL3 - 0xb810000a [ Levels 13 - 15 ]
 *
 * With each level being relative to an ilsel_source_t.
 */
#घोषणा ILSEL_BASE	0xb8100004
#घोषणा ILSEL_LEVELS	15

/*
 * ILSEL level map, in descending order from the highest level करोwn.
 *
 * Supported levels are 1 - 15 spपढ़ो across ILSEL0 - ILSEL4, mapping
 * directly to IRLs. As the IRQs are numbered in reverse order relative
 * to the पूर्णांकerrupt level, the level map is carefully managed to ensure a
 * 1:1 mapping between the bit position and the IRQ number.
 *
 * This careful स्थिरructions allows ilsel_enable*() to be referenced
 * directly क्रम hooking up an ILSEL set and getting back an IRQ which can
 * subsequently be used क्रम पूर्णांकernal accounting in the (optional) disable
 * path.
 */
अटल अचिन्हित दीर्घ ilsel_level_map;

अटल अंतरभूत अचिन्हित पूर्णांक ilsel_offset(अचिन्हित पूर्णांक bit)
अणु
	वापस ILSEL_LEVELS - bit - 1;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ mk_ilsel_addr(अचिन्हित पूर्णांक bit)
अणु
	वापस ILSEL_BASE + ((ilsel_offset(bit) >> 1) & ~0x1);
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक mk_ilsel_shअगरt(अचिन्हित पूर्णांक bit)
अणु
	वापस (ilsel_offset(bit) & 0x3) << 2;
पूर्ण

अटल व्योम __ilsel_enable(ilsel_source_t set, अचिन्हित पूर्णांक bit)
अणु
	अचिन्हित पूर्णांक पंचांगp, shअगरt;
	अचिन्हित दीर्घ addr;

	pr_notice("enabling ILSEL set %d\n", set);

	addr = mk_ilsel_addr(bit);
	shअगरt = mk_ilsel_shअगरt(bit);

	pr_debug("%s: bit#%d: addr - 0x%08lx (shift %d, set %d)\n",
		 __func__, bit, addr, shअगरt, set);

	पंचांगp = __raw_पढ़ोw(addr);
	पंचांगp &= ~(0xf << shअगरt);
	पंचांगp |= set << shअगरt;
	__raw_ग_लिखोw(पंचांगp, addr);
पूर्ण

/**
 * ilsel_enable - Enable an ILSEL set.
 * @set: ILSEL source (see ilsel_source_t क्रमागत in include/यंत्र-sh/ilsel.h).
 *
 * Enables a given non-aliased ILSEL source (<= ILSEL_KEY) at the highest
 * available पूर्णांकerrupt level. Callers should take care to order callsites
 * noting descending पूर्णांकerrupt levels. Aliasing FPGA and बाह्यal board
 * IRQs need to use ilsel_enable_fixed().
 *
 * The वापस value is an IRQ number that can later be taken करोwn with
 * ilsel_disable().
 */
पूर्णांक ilsel_enable(ilsel_source_t set)
अणु
	अचिन्हित पूर्णांक bit;

	अगर (unlikely(set > ILSEL_KEY)) अणु
		pr_err("Aliased sources must use ilsel_enable_fixed()\n");
		वापस -EINVAL;
	पूर्ण

	करो अणु
		bit = find_first_zero_bit(&ilsel_level_map, ILSEL_LEVELS);
	पूर्ण जबतक (test_and_set_bit(bit, &ilsel_level_map));

	__ilsel_enable(set, bit);

	वापस bit;
पूर्ण
EXPORT_SYMBOL_GPL(ilsel_enable);

/**
 * ilsel_enable_fixed - Enable an ILSEL set at a fixed पूर्णांकerrupt level
 * @set: ILSEL source (see ilsel_source_t क्रमागत in include/यंत्र-sh/ilsel.h).
 * @level: Interrupt level (1 - 15)
 *
 * Enables a given ILSEL source at a fixed पूर्णांकerrupt level. Necessary
 * both क्रम level reservation as well as क्रम aliased sources that only
 * exist on special ILSEL#s.
 *
 * Returns an IRQ number (as ilsel_enable()).
 */
पूर्णांक ilsel_enable_fixed(ilsel_source_t set, अचिन्हित पूर्णांक level)
अणु
	अचिन्हित पूर्णांक bit = ilsel_offset(level - 1);

	अगर (test_and_set_bit(bit, &ilsel_level_map))
		वापस -EBUSY;

	__ilsel_enable(set, bit);

	वापस bit;
पूर्ण
EXPORT_SYMBOL_GPL(ilsel_enable_fixed);

/**
 * ilsel_disable - Disable an ILSEL set
 * @irq: Bit position क्रम ILSEL set value (retval from enable routines)
 *
 * Disable a previously enabled ILSEL set.
 */
व्योम ilsel_disable(अचिन्हित पूर्णांक irq)
अणु
	अचिन्हित दीर्घ addr;
	अचिन्हित पूर्णांक पंचांगp;

	pr_notice("disabling ILSEL set %d\n", irq);

	addr = mk_ilsel_addr(irq);

	पंचांगp = __raw_पढ़ोw(addr);
	पंचांगp &= ~(0xf << mk_ilsel_shअगरt(irq));
	__raw_ग_लिखोw(पंचांगp, addr);

	clear_bit(irq, &ilsel_level_map);
पूर्ण
EXPORT_SYMBOL_GPL(ilsel_disable);
