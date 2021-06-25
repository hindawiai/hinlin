<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * arch/arm/mach-ep93xx/include/mach/uncompress.h
 *
 * Copyright (C) 2006 Lennert Buytenhek <buytenh@wantstofly.org>
 */

#समावेश <mach/ep93xx-regs.h>
#समावेश <यंत्र/mach-types.h>

अटल अचिन्हित अक्षर __raw_पढ़ोb(अचिन्हित पूर्णांक ptr)
अणु
	वापस *((अस्थिर अचिन्हित अक्षर *)ptr);
पूर्ण

अटल अचिन्हित पूर्णांक __raw_पढ़ोl(अचिन्हित पूर्णांक ptr)
अणु
	वापस *((अस्थिर अचिन्हित पूर्णांक *)ptr);
पूर्ण

अटल व्योम __raw_ग_लिखोb(अचिन्हित अक्षर value, अचिन्हित पूर्णांक ptr)
अणु
	*((अस्थिर अचिन्हित अक्षर *)ptr) = value;
पूर्ण

अटल व्योम __raw_ग_लिखोl(अचिन्हित पूर्णांक value, अचिन्हित पूर्णांक ptr)
अणु
	*((अस्थिर अचिन्हित पूर्णांक *)ptr) = value;
पूर्ण

#घोषणा PHYS_UART_DATA		(CONFIG_DEBUG_UART_PHYS + 0x00)
#घोषणा PHYS_UART_FLAG		(CONFIG_DEBUG_UART_PHYS + 0x18)
#घोषणा UART_FLAG_TXFF		0x20

अटल अंतरभूत व्योम अ_दो(पूर्णांक c)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < 10000; i++) अणु
		/* Transmit fअगरo not full? */
		अगर (!(__raw_पढ़ोb(PHYS_UART_FLAG) & UART_FLAG_TXFF))
			अवरोध;
	पूर्ण

	__raw_ग_लिखोb(c, PHYS_UART_DATA);
पूर्ण

अटल अंतरभूत व्योम flush(व्योम)
अणु
पूर्ण


/*
 * Some bootloaders करोn't turn off DMA from the ethernet MAC beक्रमe
 * jumping to linux, which means that we might end up with bits of RX
 * status and packet data scribbled over the uncompressed kernel image.
 * Work around this by resetting the ethernet MAC beक्रमe we uncompress.
 */
#घोषणा PHYS_ETH_SELF_CTL		0x80010020
#घोषणा ETH_SELF_CTL_RESET		0x00000001

अटल व्योम ethernet_reset(व्योम)
अणु
	अचिन्हित पूर्णांक v;

	/* Reset the ethernet MAC.  */
	v = __raw_पढ़ोl(PHYS_ETH_SELF_CTL);
	__raw_ग_लिखोl(v | ETH_SELF_CTL_RESET, PHYS_ETH_SELF_CTL);

	/* Wait क्रम reset to finish.  */
	जबतक (__raw_पढ़ोl(PHYS_ETH_SELF_CTL) & ETH_SELF_CTL_RESET)
		;
पूर्ण

#घोषणा TS72XX_WDT_CONTROL_PHYS_BASE	0x23800000
#घोषणा TS72XX_WDT_FEED_PHYS_BASE	0x23c00000
#घोषणा TS72XX_WDT_FEED_VAL		0x05

अटल व्योम __maybe_unused ts72xx_watchकरोg_disable(व्योम)
अणु
	__raw_ग_लिखोb(TS72XX_WDT_FEED_VAL, TS72XX_WDT_FEED_PHYS_BASE);
	__raw_ग_लिखोb(0, TS72XX_WDT_CONTROL_PHYS_BASE);
पूर्ण

अटल व्योम arch_decomp_setup(व्योम)
अणु
	अगर (machine_is_ts72xx())
		ts72xx_watchकरोg_disable();
	ethernet_reset();
पूर्ण
