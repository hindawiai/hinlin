<शैली गुरु>
/*
 * GPIO functions क्रम Au1000, Au1500, Au1100, Au1550, Au1200
 *
 * Copyright (c) 2009 Manuel Lauss.
 *
 * Licensed under the terms outlined in the file COPYING.
 */

#अगर_अघोषित _ALCHEMY_GPIO_AU1000_H_
#घोषणा _ALCHEMY_GPIO_AU1000_H_

#समावेश <यंत्र/mach-au1x00/au1000.h>

/* The शेष GPIO numberspace as करोcumented in the Alchemy manuals.
 * GPIO0-31 from GPIO1 block,	GPIO200-215 from GPIO2 block.
 */
#घोषणा ALCHEMY_GPIO1_BASE	0
#घोषणा ALCHEMY_GPIO2_BASE	200

#घोषणा ALCHEMY_GPIO1_NUM	32
#घोषणा ALCHEMY_GPIO2_NUM	16
#घोषणा ALCHEMY_GPIO1_MAX	(ALCHEMY_GPIO1_BASE + ALCHEMY_GPIO1_NUM - 1)
#घोषणा ALCHEMY_GPIO2_MAX	(ALCHEMY_GPIO2_BASE + ALCHEMY_GPIO2_NUM - 1)

#घोषणा MAKE_IRQ(पूर्णांकc, off)	(AU1000_INTC##पूर्णांकc##_INT_BASE + (off))

/* GPIO1 रेजिस्टरs within SYS_ area */
#घोषणा AU1000_SYS_TRIOUTRD	0x100
#घोषणा AU1000_SYS_TRIOUTCLR	0x100
#घोषणा AU1000_SYS_OUTPUTRD	0x108
#घोषणा AU1000_SYS_OUTPUTSET	0x108
#घोषणा AU1000_SYS_OUTPUTCLR	0x10C
#घोषणा AU1000_SYS_PINSTATERD	0x110
#घोषणा AU1000_SYS_PININPUTEN	0x110

/* रेजिस्टर offsets within GPIO2 block */
#घोषणा AU1000_GPIO2_सूची	0x00
#घोषणा AU1000_GPIO2_OUTPUT	0x08
#घोषणा AU1000_GPIO2_PINSTATE	0x0C
#घोषणा AU1000_GPIO2_INTENABLE	0x10
#घोषणा AU1000_GPIO2_ENABLE	0x14

काष्ठा gpio;

अटल अंतरभूत पूर्णांक au1000_gpio1_to_irq(पूर्णांक gpio)
अणु
	वापस MAKE_IRQ(1, gpio - ALCHEMY_GPIO1_BASE);
पूर्ण

अटल अंतरभूत पूर्णांक au1000_gpio2_to_irq(पूर्णांक gpio)
अणु
	वापस -ENXIO;
पूर्ण

अटल अंतरभूत पूर्णांक au1000_irq_to_gpio(पूर्णांक irq)
अणु
	अगर ((irq >= AU1000_GPIO0_INT) && (irq <= AU1000_GPIO31_INT))
		वापस ALCHEMY_GPIO1_BASE + (irq - AU1000_GPIO0_INT) + 0;

	वापस -ENXIO;
पूर्ण

अटल अंतरभूत पूर्णांक au1500_gpio1_to_irq(पूर्णांक gpio)
अणु
	gpio -= ALCHEMY_GPIO1_BASE;

	चयन (gpio) अणु
	हाल 0 ... 15:
	हाल 20:
	हाल 23 ... 28: वापस MAKE_IRQ(1, gpio);
	पूर्ण

	वापस -ENXIO;
पूर्ण

अटल अंतरभूत पूर्णांक au1500_gpio2_to_irq(पूर्णांक gpio)
अणु
	gpio -= ALCHEMY_GPIO2_BASE;

	चयन (gpio) अणु
	हाल 0 ... 3:	वापस MAKE_IRQ(1, 16 + gpio - 0);
	हाल 4 ... 5:	वापस MAKE_IRQ(1, 21 + gpio - 4);
	हाल 6 ... 7:	वापस MAKE_IRQ(1, 29 + gpio - 6);
	पूर्ण

	वापस -ENXIO;
पूर्ण

अटल अंतरभूत पूर्णांक au1500_irq_to_gpio(पूर्णांक irq)
अणु
	चयन (irq) अणु
	हाल AU1500_GPIO0_INT ... AU1500_GPIO15_INT:
	हाल AU1500_GPIO20_INT:
	हाल AU1500_GPIO23_INT ... AU1500_GPIO28_INT:
		वापस ALCHEMY_GPIO1_BASE + (irq - AU1500_GPIO0_INT) + 0;
	हाल AU1500_GPIO200_INT ... AU1500_GPIO203_INT:
		वापस ALCHEMY_GPIO2_BASE + (irq - AU1500_GPIO200_INT) + 0;
	हाल AU1500_GPIO204_INT ... AU1500_GPIO205_INT:
		वापस ALCHEMY_GPIO2_BASE + (irq - AU1500_GPIO204_INT) + 4;
	हाल AU1500_GPIO206_INT ... AU1500_GPIO207_INT:
		वापस ALCHEMY_GPIO2_BASE + (irq - AU1500_GPIO206_INT) + 6;
	हाल AU1500_GPIO208_215_INT:
		वापस ALCHEMY_GPIO2_BASE + 8;
	पूर्ण

	वापस -ENXIO;
पूर्ण

अटल अंतरभूत पूर्णांक au1100_gpio1_to_irq(पूर्णांक gpio)
अणु
	वापस MAKE_IRQ(1, gpio - ALCHEMY_GPIO1_BASE);
पूर्ण

अटल अंतरभूत पूर्णांक au1100_gpio2_to_irq(पूर्णांक gpio)
अणु
	gpio -= ALCHEMY_GPIO2_BASE;

	अगर ((gpio >= 8) && (gpio <= 15))
		वापस MAKE_IRQ(0, 29);		/* shared GPIO208_215 */

	वापस -ENXIO;
पूर्ण

अटल अंतरभूत पूर्णांक au1100_irq_to_gpio(पूर्णांक irq)
अणु
	चयन (irq) अणु
	हाल AU1100_GPIO0_INT ... AU1100_GPIO31_INT:
		वापस ALCHEMY_GPIO1_BASE + (irq - AU1100_GPIO0_INT) + 0;
	हाल AU1100_GPIO208_215_INT:
		वापस ALCHEMY_GPIO2_BASE + 8;
	पूर्ण

	वापस -ENXIO;
पूर्ण

अटल अंतरभूत पूर्णांक au1550_gpio1_to_irq(पूर्णांक gpio)
अणु
	gpio -= ALCHEMY_GPIO1_BASE;

	चयन (gpio) अणु
	हाल 0 ... 15:
	हाल 20 ... 28: वापस MAKE_IRQ(1, gpio);
	हाल 16 ... 17: वापस MAKE_IRQ(1, 18 + gpio - 16);
	पूर्ण

	वापस -ENXIO;
पूर्ण

अटल अंतरभूत पूर्णांक au1550_gpio2_to_irq(पूर्णांक gpio)
अणु
	gpio -= ALCHEMY_GPIO2_BASE;

	चयन (gpio) अणु
	हाल 0:		वापस MAKE_IRQ(1, 16);
	हाल 1 ... 5:	वापस MAKE_IRQ(1, 17); /* shared GPIO201_205 */
	हाल 6 ... 7:	वापस MAKE_IRQ(1, 29 + gpio - 6);
	हाल 8 ... 15:	वापस MAKE_IRQ(1, 31); /* shared GPIO208_215 */
	पूर्ण

	वापस -ENXIO;
पूर्ण

अटल अंतरभूत पूर्णांक au1550_irq_to_gpio(पूर्णांक irq)
अणु
	चयन (irq) अणु
	हाल AU1550_GPIO0_INT ... AU1550_GPIO15_INT:
		वापस ALCHEMY_GPIO1_BASE + (irq - AU1550_GPIO0_INT) + 0;
	हाल AU1550_GPIO200_INT:
	हाल AU1550_GPIO201_205_INT:
		वापस ALCHEMY_GPIO2_BASE + (irq - AU1550_GPIO200_INT) + 0;
	हाल AU1550_GPIO16_INT ... AU1550_GPIO28_INT:
		वापस ALCHEMY_GPIO1_BASE + (irq - AU1550_GPIO16_INT) + 16;
	हाल AU1550_GPIO206_INT ... AU1550_GPIO208_215_INT:
		वापस ALCHEMY_GPIO2_BASE + (irq - AU1550_GPIO206_INT) + 6;
	पूर्ण

	वापस -ENXIO;
पूर्ण

अटल अंतरभूत पूर्णांक au1200_gpio1_to_irq(पूर्णांक gpio)
अणु
	वापस MAKE_IRQ(1, gpio - ALCHEMY_GPIO1_BASE);
पूर्ण

अटल अंतरभूत पूर्णांक au1200_gpio2_to_irq(पूर्णांक gpio)
अणु
	gpio -= ALCHEMY_GPIO2_BASE;

	चयन (gpio) अणु
	हाल 0 ... 2:	वापस MAKE_IRQ(0, 5 + gpio - 0);
	हाल 3:		वापस MAKE_IRQ(0, 22);
	हाल 4 ... 7:	वापस MAKE_IRQ(0, 24 + gpio - 4);
	हाल 8 ... 15:	वापस MAKE_IRQ(0, 28); /* shared GPIO208_215 */
	पूर्ण

	वापस -ENXIO;
पूर्ण

अटल अंतरभूत पूर्णांक au1200_irq_to_gpio(पूर्णांक irq)
अणु
	चयन (irq) अणु
	हाल AU1200_GPIO0_INT ... AU1200_GPIO31_INT:
		वापस ALCHEMY_GPIO1_BASE + (irq - AU1200_GPIO0_INT) + 0;
	हाल AU1200_GPIO200_INT ... AU1200_GPIO202_INT:
		वापस ALCHEMY_GPIO2_BASE + (irq - AU1200_GPIO200_INT) + 0;
	हाल AU1200_GPIO203_INT:
		वापस ALCHEMY_GPIO2_BASE + 3;
	हाल AU1200_GPIO204_INT ... AU1200_GPIO208_215_INT:
		वापस ALCHEMY_GPIO2_BASE + (irq - AU1200_GPIO204_INT) + 4;
	पूर्ण

	वापस -ENXIO;
पूर्ण

/*
 * GPIO1 block macros क्रम common linux gpio functions.
 */
अटल अंतरभूत व्योम alchemy_gpio1_set_value(पूर्णांक gpio, पूर्णांक v)
अणु
	अचिन्हित दीर्घ mask = 1 << (gpio - ALCHEMY_GPIO1_BASE);
	अचिन्हित दीर्घ r = v ? AU1000_SYS_OUTPUTSET : AU1000_SYS_OUTPUTCLR;
	alchemy_wrsys(mask, r);
पूर्ण

अटल अंतरभूत पूर्णांक alchemy_gpio1_get_value(पूर्णांक gpio)
अणु
	अचिन्हित दीर्घ mask = 1 << (gpio - ALCHEMY_GPIO1_BASE);
	वापस alchemy_rdsys(AU1000_SYS_PINSTATERD) & mask;
पूर्ण

अटल अंतरभूत पूर्णांक alchemy_gpio1_direction_input(पूर्णांक gpio)
अणु
	अचिन्हित दीर्घ mask = 1 << (gpio - ALCHEMY_GPIO1_BASE);
	alchemy_wrsys(mask, AU1000_SYS_TRIOUTCLR);
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक alchemy_gpio1_direction_output(पूर्णांक gpio, पूर्णांक v)
अणु
	/* hardware चयनes to "output" mode when one of the two
	 * "set_value" रेजिस्टरs is accessed.
	 */
	alchemy_gpio1_set_value(gpio, v);
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक alchemy_gpio1_is_valid(पूर्णांक gpio)
अणु
	वापस ((gpio >= ALCHEMY_GPIO1_BASE) && (gpio <= ALCHEMY_GPIO1_MAX));
पूर्ण

अटल अंतरभूत पूर्णांक alchemy_gpio1_to_irq(पूर्णांक gpio)
अणु
	चयन (alchemy_get_cputype()) अणु
	हाल ALCHEMY_CPU_AU1000:
		वापस au1000_gpio1_to_irq(gpio);
	हाल ALCHEMY_CPU_AU1100:
		वापस au1100_gpio1_to_irq(gpio);
	हाल ALCHEMY_CPU_AU1500:
		वापस au1500_gpio1_to_irq(gpio);
	हाल ALCHEMY_CPU_AU1550:
		वापस au1550_gpio1_to_irq(gpio);
	हाल ALCHEMY_CPU_AU1200:
		वापस au1200_gpio1_to_irq(gpio);
	पूर्ण
	वापस -ENXIO;
पूर्ण

/* On Au1000, Au1500 and Au1100 GPIOs won't work as inमाला_दो beक्रमe
 * SYS_PININPUTEN is written to at least once.  On Au1550/Au1200/Au1300 this
 * रेजिस्टर enables use of GPIOs as wake source.
 */
अटल अंतरभूत व्योम alchemy_gpio1_input_enable(व्योम)
अणु
	व्योम __iomem *base = (व्योम __iomem *)KSEG1ADDR(AU1000_SYS_PHYS_ADDR);
	__raw_ग_लिखोl(0, base + 0x110);		/* the ग_लिखो op is key */
	wmb();
पूर्ण

/*
 * GPIO2 block macros क्रम common linux GPIO functions. The 'gpio'
 * parameter must be in range of ALCHEMY_GPIO2_BASE..ALCHEMY_GPIO2_MAX.
 */
अटल अंतरभूत व्योम __alchemy_gpio2_mod_dir(पूर्णांक gpio, पूर्णांक to_out)
अणु
	व्योम __iomem *base = (व्योम __iomem *)KSEG1ADDR(AU1500_GPIO2_PHYS_ADDR);
	अचिन्हित दीर्घ mask = 1 << (gpio - ALCHEMY_GPIO2_BASE);
	अचिन्हित दीर्घ d = __raw_पढ़ोl(base + AU1000_GPIO2_सूची);

	अगर (to_out)
		d |= mask;
	अन्यथा
		d &= ~mask;
	__raw_ग_लिखोl(d, base + AU1000_GPIO2_सूची);
	wmb();
पूर्ण

अटल अंतरभूत व्योम alchemy_gpio2_set_value(पूर्णांक gpio, पूर्णांक v)
अणु
	व्योम __iomem *base = (व्योम __iomem *)KSEG1ADDR(AU1500_GPIO2_PHYS_ADDR);
	अचिन्हित दीर्घ mask;
	mask = ((v) ? 0x00010001 : 0x00010000) << (gpio - ALCHEMY_GPIO2_BASE);
	__raw_ग_लिखोl(mask, base + AU1000_GPIO2_OUTPUT);
	wmb();
पूर्ण

अटल अंतरभूत पूर्णांक alchemy_gpio2_get_value(पूर्णांक gpio)
अणु
	व्योम __iomem *base = (व्योम __iomem *)KSEG1ADDR(AU1500_GPIO2_PHYS_ADDR);
	वापस __raw_पढ़ोl(base + AU1000_GPIO2_PINSTATE) &
				(1 << (gpio - ALCHEMY_GPIO2_BASE));
पूर्ण

अटल अंतरभूत पूर्णांक alchemy_gpio2_direction_input(पूर्णांक gpio)
अणु
	अचिन्हित दीर्घ flags;
	local_irq_save(flags);
	__alchemy_gpio2_mod_dir(gpio, 0);
	local_irq_restore(flags);
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक alchemy_gpio2_direction_output(पूर्णांक gpio, पूर्णांक v)
अणु
	अचिन्हित दीर्घ flags;
	alchemy_gpio2_set_value(gpio, v);
	local_irq_save(flags);
	__alchemy_gpio2_mod_dir(gpio, 1);
	local_irq_restore(flags);
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक alchemy_gpio2_is_valid(पूर्णांक gpio)
अणु
	वापस ((gpio >= ALCHEMY_GPIO2_BASE) && (gpio <= ALCHEMY_GPIO2_MAX));
पूर्ण

अटल अंतरभूत पूर्णांक alchemy_gpio2_to_irq(पूर्णांक gpio)
अणु
	चयन (alchemy_get_cputype()) अणु
	हाल ALCHEMY_CPU_AU1000:
		वापस au1000_gpio2_to_irq(gpio);
	हाल ALCHEMY_CPU_AU1100:
		वापस au1100_gpio2_to_irq(gpio);
	हाल ALCHEMY_CPU_AU1500:
		वापस au1500_gpio2_to_irq(gpio);
	हाल ALCHEMY_CPU_AU1550:
		वापस au1550_gpio2_to_irq(gpio);
	हाल ALCHEMY_CPU_AU1200:
		वापस au1200_gpio2_to_irq(gpio);
	पूर्ण
	वापस -ENXIO;
पूर्ण

/**********************************************************************/

/* GPIO2 shared पूर्णांकerrupts and control */

अटल अंतरभूत व्योम __alchemy_gpio2_mod_पूर्णांक(पूर्णांक gpio2, पूर्णांक en)
अणु
	व्योम __iomem *base = (व्योम __iomem *)KSEG1ADDR(AU1500_GPIO2_PHYS_ADDR);
	अचिन्हित दीर्घ r = __raw_पढ़ोl(base + AU1000_GPIO2_INTENABLE);
	अगर (en)
		r |= 1 << gpio2;
	अन्यथा
		r &= ~(1 << gpio2);
	__raw_ग_लिखोl(r, base + AU1000_GPIO2_INTENABLE);
	wmb();
पूर्ण

/**
 * alchemy_gpio2_enable_पूर्णांक - Enable a GPIO2 pins' shared irq contribution.
 * @gpio2:	The GPIO2 pin to activate (200...215).
 *
 * GPIO208-215 have one shared पूर्णांकerrupt line to the INTC.  They are
 * and'ed with a per-pin enable bit and finally or'ed together to क्रमm
 * a single irq request (useful क्रम active-high sources).
 * With this function, a pins' inभागidual contribution to the पूर्णांक request
 * can be enabled.  As with all other GPIO-based पूर्णांकerrupts, the INTC
 * must be programmed to accept the GPIO208_215 पूर्णांकerrupt as well.
 *
 * NOTE: Calling this macro is only necessary क्रम GPIO208-215; all other
 * GPIO2-based पूर्णांकerrupts have their own request to the INTC.  Please
 * consult your Alchemy databook क्रम more inक्रमmation!
 *
 * NOTE: On the Au1550, GPIOs 201-205 also have a shared पूर्णांकerrupt request
 * line to the INTC, GPIO201_205.  This function can be used क्रम those
 * as well.
 *
 * NOTE: 'gpio2' parameter must be in range of the GPIO2 numberspace
 * (200-215 by शेष). No sanity checks are made,
 */
अटल अंतरभूत व्योम alchemy_gpio2_enable_पूर्णांक(पूर्णांक gpio2)
अणु
	अचिन्हित दीर्घ flags;

	gpio2 -= ALCHEMY_GPIO2_BASE;

	/* Au1100/Au1500 have GPIO208-215 enable bits at 0..7 */
	चयन (alchemy_get_cputype()) अणु
	हाल ALCHEMY_CPU_AU1100:
	हाल ALCHEMY_CPU_AU1500:
		gpio2 -= 8;
	पूर्ण

	local_irq_save(flags);
	__alchemy_gpio2_mod_पूर्णांक(gpio2, 1);
	local_irq_restore(flags);
पूर्ण

/**
 * alchemy_gpio2_disable_पूर्णांक - Disable a GPIO2 pins' shared irq contribution.
 * @gpio2:	The GPIO2 pin to activate (200...215).
 *
 * see function alchemy_gpio2_enable_पूर्णांक() क्रम more inक्रमmation.
 */
अटल अंतरभूत व्योम alchemy_gpio2_disable_पूर्णांक(पूर्णांक gpio2)
अणु
	अचिन्हित दीर्घ flags;

	gpio2 -= ALCHEMY_GPIO2_BASE;

	/* Au1100/Au1500 have GPIO208-215 enable bits at 0..7 */
	चयन (alchemy_get_cputype()) अणु
	हाल ALCHEMY_CPU_AU1100:
	हाल ALCHEMY_CPU_AU1500:
		gpio2 -= 8;
	पूर्ण

	local_irq_save(flags);
	__alchemy_gpio2_mod_पूर्णांक(gpio2, 0);
	local_irq_restore(flags);
पूर्ण

/**
 * alchemy_gpio2_enable -  Activate GPIO2 block.
 *
 * The GPIO2 block must be enabled excplicitly to work.	 On प्रणालीs
 * where this isn't करोne by the bootloader, this macro can be used.
 */
अटल अंतरभूत व्योम alchemy_gpio2_enable(व्योम)
अणु
	व्योम __iomem *base = (व्योम __iomem *)KSEG1ADDR(AU1500_GPIO2_PHYS_ADDR);
	__raw_ग_लिखोl(3, base + AU1000_GPIO2_ENABLE);	/* reset, घड़ी enabled */
	wmb();
	__raw_ग_लिखोl(1, base + AU1000_GPIO2_ENABLE);	/* घड़ी enabled */
	wmb();
पूर्ण

/**
 * alchemy_gpio2_disable - disable GPIO2 block.
 *
 * Disable and put GPIO2 block in low-घातer mode.
 */
अटल अंतरभूत व्योम alchemy_gpio2_disable(व्योम)
अणु
	व्योम __iomem *base = (व्योम __iomem *)KSEG1ADDR(AU1500_GPIO2_PHYS_ADDR);
	__raw_ग_लिखोl(2, base + AU1000_GPIO2_ENABLE);	/* reset, घड़ी disabled */
	wmb();
पूर्ण

/**********************************************************************/

/* wrappers क्रम on-chip gpios; can be used beक्रमe gpio chips have been
 * रेजिस्टरed with gpiolib.
 */
अटल अंतरभूत पूर्णांक alchemy_gpio_direction_input(पूर्णांक gpio)
अणु
	वापस (gpio >= ALCHEMY_GPIO2_BASE) ?
		alchemy_gpio2_direction_input(gpio) :
		alchemy_gpio1_direction_input(gpio);
पूर्ण

अटल अंतरभूत पूर्णांक alchemy_gpio_direction_output(पूर्णांक gpio, पूर्णांक v)
अणु
	वापस (gpio >= ALCHEMY_GPIO2_BASE) ?
		alchemy_gpio2_direction_output(gpio, v) :
		alchemy_gpio1_direction_output(gpio, v);
पूर्ण

अटल अंतरभूत पूर्णांक alchemy_gpio_get_value(पूर्णांक gpio)
अणु
	वापस (gpio >= ALCHEMY_GPIO2_BASE) ?
		alchemy_gpio2_get_value(gpio) :
		alchemy_gpio1_get_value(gpio);
पूर्ण

अटल अंतरभूत व्योम alchemy_gpio_set_value(पूर्णांक gpio, पूर्णांक v)
अणु
	अगर (gpio >= ALCHEMY_GPIO2_BASE)
		alchemy_gpio2_set_value(gpio, v);
	अन्यथा
		alchemy_gpio1_set_value(gpio, v);
पूर्ण

अटल अंतरभूत पूर्णांक alchemy_gpio_is_valid(पूर्णांक gpio)
अणु
	वापस (gpio >= ALCHEMY_GPIO2_BASE) ?
		alchemy_gpio2_is_valid(gpio) :
		alchemy_gpio1_is_valid(gpio);
पूर्ण

अटल अंतरभूत पूर्णांक alchemy_gpio_cansleep(पूर्णांक gpio)
अणु
	वापस 0;	/* Alchemy never माला_लो tired */
पूर्ण

अटल अंतरभूत पूर्णांक alchemy_gpio_to_irq(पूर्णांक gpio)
अणु
	वापस (gpio >= ALCHEMY_GPIO2_BASE) ?
		alchemy_gpio2_to_irq(gpio) :
		alchemy_gpio1_to_irq(gpio);
पूर्ण

अटल अंतरभूत पूर्णांक alchemy_irq_to_gpio(पूर्णांक irq)
अणु
	चयन (alchemy_get_cputype()) अणु
	हाल ALCHEMY_CPU_AU1000:
		वापस au1000_irq_to_gpio(irq);
	हाल ALCHEMY_CPU_AU1100:
		वापस au1100_irq_to_gpio(irq);
	हाल ALCHEMY_CPU_AU1500:
		वापस au1500_irq_to_gpio(irq);
	हाल ALCHEMY_CPU_AU1550:
		वापस au1550_irq_to_gpio(irq);
	हाल ALCHEMY_CPU_AU1200:
		वापस au1200_irq_to_gpio(irq);
	पूर्ण
	वापस -ENXIO;
पूर्ण

#पूर्ण_अगर /* _ALCHEMY_GPIO_AU1000_H_ */
