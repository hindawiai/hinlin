<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * gpio-au1300.h -- GPIO control क्रम Au1300 GPIC and compatibles.
 *
 * Copyright (c) 2009-2011 Manuel Lauss <manuel.lauss@googlemail.com>
 */

#अगर_अघोषित _GPIO_AU1300_H_
#घोषणा _GPIO_AU1300_H_

#समावेश <यंत्र/addrspace.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/mach-au1x00/au1000.h>

काष्ठा gpio;
काष्ठा gpio_chip;

/* with the current GPIC design, up to 128 GPIOs are possible.
 * The only implementation so far is in the Au1300, which has 75 बाह्यally
 * available GPIOs.
 */
#घोषणा AU1300_GPIO_BASE	0
#घोषणा AU1300_GPIO_NUM		75
#घोषणा AU1300_GPIO_MAX		(AU1300_GPIO_BASE + AU1300_GPIO_NUM - 1)

#घोषणा AU1300_GPIC_ADDR	\
	(व्योम __iomem *)KSEG1ADDR(AU1300_GPIC_PHYS_ADDR)

अटल अंतरभूत पूर्णांक au1300_gpio_get_value(अचिन्हित पूर्णांक gpio)
अणु
	व्योम __iomem *roff = AU1300_GPIC_ADDR;
	पूर्णांक bit;

	gpio -= AU1300_GPIO_BASE;
	roff += GPIC_GPIO_BANKOFF(gpio);
	bit = GPIC_GPIO_TO_BIT(gpio);
	वापस __raw_पढ़ोl(roff + AU1300_GPIC_PINVAL) & bit;
पूर्ण

अटल अंतरभूत पूर्णांक au1300_gpio_direction_input(अचिन्हित पूर्णांक gpio)
अणु
	व्योम __iomem *roff = AU1300_GPIC_ADDR;
	अचिन्हित दीर्घ bit;

	gpio -= AU1300_GPIO_BASE;

	roff += GPIC_GPIO_BANKOFF(gpio);
	bit = GPIC_GPIO_TO_BIT(gpio);
	__raw_ग_लिखोl(bit, roff + AU1300_GPIC_DEVCLR);
	wmb();

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक au1300_gpio_set_value(अचिन्हित पूर्णांक gpio, पूर्णांक v)
अणु
	व्योम __iomem *roff = AU1300_GPIC_ADDR;
	अचिन्हित दीर्घ bit;

	gpio -= AU1300_GPIO_BASE;

	roff += GPIC_GPIO_BANKOFF(gpio);
	bit = GPIC_GPIO_TO_BIT(gpio);
	__raw_ग_लिखोl(bit, roff + (v ? AU1300_GPIC_PINVAL
				    : AU1300_GPIC_PINVALCLR));
	wmb();

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक au1300_gpio_direction_output(अचिन्हित पूर्णांक gpio, पूर्णांक v)
अणु
	/* hw चयनes to output स्वतःmatically */
	वापस au1300_gpio_set_value(gpio, v);
पूर्ण

अटल अंतरभूत पूर्णांक au1300_gpio_to_irq(अचिन्हित पूर्णांक gpio)
अणु
	वापस AU1300_FIRST_INT + (gpio - AU1300_GPIO_BASE);
पूर्ण

अटल अंतरभूत पूर्णांक au1300_irq_to_gpio(अचिन्हित पूर्णांक irq)
अणु
	वापस (irq - AU1300_FIRST_INT) + AU1300_GPIO_BASE;
पूर्ण

अटल अंतरभूत पूर्णांक au1300_gpio_is_valid(अचिन्हित पूर्णांक gpio)
अणु
	पूर्णांक ret;

	चयन (alchemy_get_cputype()) अणु
	हाल ALCHEMY_CPU_AU1300:
		ret = ((gpio >= AU1300_GPIO_BASE) && (gpio <= AU1300_GPIO_MAX));
		अवरोध;
	शेष:
		ret = 0;
	पूर्ण
	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक au1300_gpio_cansleep(अचिन्हित पूर्णांक gpio)
अणु
	वापस 0;
पूर्ण

/* hardware remembers gpio 0-63 levels on घातerup */
अटल अंतरभूत पूर्णांक au1300_gpio_getinitlvl(अचिन्हित पूर्णांक gpio)
अणु
	व्योम __iomem *roff = AU1300_GPIC_ADDR;
	अचिन्हित दीर्घ v;

	अगर (unlikely(gpio > 63))
		वापस 0;
	अन्यथा अगर (gpio > 31) अणु
		gpio -= 32;
		roff += 4;
	पूर्ण

	v = __raw_पढ़ोl(roff + AU1300_GPIC_RSTVAL);
	वापस (v >> gpio) & 1;
पूर्ण

#पूर्ण_अगर /* _GPIO_AU1300_H_ */
