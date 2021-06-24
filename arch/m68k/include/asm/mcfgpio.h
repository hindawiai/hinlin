<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Coldfire generic GPIO support.
 *
 * (C) Copyright 2009, Steven King <sfking@fdwdc.com>
 */

#अगर_अघोषित mcfgpio_h
#घोषणा mcfgpio_h

#अगर_घोषित CONFIG_GPIOLIB
#समावेश <यंत्र-generic/gpपन.स>
#अन्यथा

पूर्णांक __mcfgpio_get_value(अचिन्हित gpio);
व्योम __mcfgpio_set_value(अचिन्हित gpio, पूर्णांक value);
पूर्णांक __mcfgpio_direction_input(अचिन्हित gpio);
पूर्णांक __mcfgpio_direction_output(अचिन्हित gpio, पूर्णांक value);
पूर्णांक __mcfgpio_request(अचिन्हित gpio);
व्योम __mcfgpio_मुक्त(अचिन्हित gpio);

/* our alternate 'gpiolib' functions */
अटल अंतरभूत पूर्णांक __gpio_get_value(अचिन्हित gpio)
अणु
	अगर (gpio < MCFGPIO_PIN_MAX)
		वापस __mcfgpio_get_value(gpio);
	अन्यथा
		वापस -EINVAL;
पूर्ण

अटल अंतरभूत व्योम __gpio_set_value(अचिन्हित gpio, पूर्णांक value)
अणु
	अगर (gpio < MCFGPIO_PIN_MAX)
		__mcfgpio_set_value(gpio, value);
पूर्ण

अटल अंतरभूत पूर्णांक __gpio_cansleep(अचिन्हित gpio)
अणु
	अगर (gpio < MCFGPIO_PIN_MAX)
		वापस 0;
	अन्यथा
		वापस -EINVAL;
पूर्ण

अटल अंतरभूत पूर्णांक __gpio_to_irq(अचिन्हित gpio)
अणु
	वापस -EINVAL;
पूर्ण

अटल अंतरभूत पूर्णांक gpio_direction_input(अचिन्हित gpio)
अणु
	अगर (gpio < MCFGPIO_PIN_MAX)
		वापस __mcfgpio_direction_input(gpio);
	अन्यथा
		वापस -EINVAL;
पूर्ण

अटल अंतरभूत पूर्णांक gpio_direction_output(अचिन्हित gpio, पूर्णांक value)
अणु
	अगर (gpio < MCFGPIO_PIN_MAX)
		वापस __mcfgpio_direction_output(gpio, value);
	अन्यथा
		वापस -EINVAL;
पूर्ण

अटल अंतरभूत पूर्णांक gpio_request(अचिन्हित gpio, स्थिर अक्षर *label)
अणु
	अगर (gpio < MCFGPIO_PIN_MAX)
		वापस __mcfgpio_request(gpio);
	अन्यथा
		वापस -EINVAL;
पूर्ण

अटल अंतरभूत व्योम gpio_मुक्त(अचिन्हित gpio)
अणु
	अगर (gpio < MCFGPIO_PIN_MAX)
		__mcfgpio_मुक्त(gpio);
पूर्ण

#पूर्ण_अगर /* CONFIG_GPIOLIB */


/*
 * The Freescale Coldfire family is quite varied in how they implement GPIO.
 * Some parts have 8 bit ports, some have 16bit and some have 32bit; some have
 * only one port, others have multiple ports; some have a single data latch
 * क्रम both input and output, others have a separate pin data रेजिस्टर to पढ़ो
 * input; some require a पढ़ो-modअगरy-ग_लिखो access to change an output, others
 * have set and clear रेजिस्टरs क्रम some of the outमाला_दो; Some have all the
 * GPIOs in a single control area, others have some GPIOs implemented in
 * dअगरferent modules.
 *
 * This implementation attempts accommodate the dअगरferences जबतक presenting
 * a generic पूर्णांकerface that will optimize to as few inकाष्ठाions as possible.
 */
#अगर defined(CONFIG_M5206) || defined(CONFIG_M5206e) || \
    defined(CONFIG_M520x) || defined(CONFIG_M523x) || \
    defined(CONFIG_M527x) || defined(CONFIG_M528x) || \
    defined(CONFIG_M53xx) || defined(CONFIG_M54xx) || \
    defined(CONFIG_M5441x)

/* These parts have GPIO organized by 8 bit ports */

#घोषणा MCFGPIO_PORTTYPE		u8
#घोषणा MCFGPIO_PORTSIZE		8
#घोषणा mcfgpio_पढ़ो(port)		__raw_पढ़ोb(port)
#घोषणा mcfgpio_ग_लिखो(data, port)	__raw_ग_लिखोb(data, port)

#या_अगर defined(CONFIG_M5307) || defined(CONFIG_M5407) || defined(CONFIG_M5272)

/* These parts have GPIO organized by 16 bit ports */

#घोषणा MCFGPIO_PORTTYPE		u16
#घोषणा MCFGPIO_PORTSIZE		16
#घोषणा mcfgpio_पढ़ो(port)		__raw_पढ़ोw(port)
#घोषणा mcfgpio_ग_लिखो(data, port)	__raw_ग_लिखोw(data, port)

#या_अगर defined(CONFIG_M5249) || defined(CONFIG_M525x)

/* These parts have GPIO organized by 32 bit ports */

#घोषणा MCFGPIO_PORTTYPE		u32
#घोषणा MCFGPIO_PORTSIZE		32
#घोषणा mcfgpio_पढ़ो(port)		__raw_पढ़ोl(port)
#घोषणा mcfgpio_ग_लिखो(data, port)	__raw_ग_लिखोl(data, port)

#पूर्ण_अगर

#घोषणा mcfgpio_bit(gpio)		(1 << ((gpio) %  MCFGPIO_PORTSIZE))
#घोषणा mcfgpio_port(gpio)		((gpio) / MCFGPIO_PORTSIZE)

#अगर defined(CONFIG_M520x) || defined(CONFIG_M523x) || \
    defined(CONFIG_M527x) || defined(CONFIG_M528x) || \
    defined(CONFIG_M53xx) || defined(CONFIG_M54xx) || \
    defined(CONFIG_M5441x)
/*
 * These parts have an 'Edge' Port module (बाह्यal पूर्णांकerrupt/GPIO) which uses
 * पढ़ो-modअगरy-ग_लिखो to change an output and a GPIO module which has separate
 * set/clr रेजिस्टरs to directly change outमाला_दो with a single ग_लिखो access.
 */
#अगर defined(CONFIG_M528x)
/*
 * The 528x also has GPIOs in other modules (GPT, QADC) which use
 * पढ़ो-modअगरy-ग_लिखो as well as those controlled by the EPORT and GPIO modules.
 */
#घोषणा MCFGPIO_SCR_START		40
#या_अगर defined(CONFIGM5441x)
/* The m5441x EPORT करोesn't have its own GPIO port, uses PORT C */
#घोषणा MCFGPIO_SCR_START		0
#अन्यथा
#घोषणा MCFGPIO_SCR_START		8
#पूर्ण_अगर

#घोषणा MCFGPIO_SETR_PORT(gpio)		(MCFGPIO_SETR + \
					mcfgpio_port(gpio - MCFGPIO_SCR_START))

#घोषणा MCFGPIO_CLRR_PORT(gpio)		(MCFGPIO_CLRR + \
					mcfgpio_port(gpio - MCFGPIO_SCR_START))
#अन्यथा

#घोषणा MCFGPIO_SCR_START		MCFGPIO_PIN_MAX
/* with MCFGPIO_SCR == MCFGPIO_PIN_MAX, these will be optimized away */
#घोषणा MCFGPIO_SETR_PORT(gpio)		0
#घोषणा MCFGPIO_CLRR_PORT(gpio)		0

#पूर्ण_अगर
/*
 * Coldfire specअगरic helper functions
 */

/* वापस the port pin data रेजिस्टर क्रम a gpio */
अटल अंतरभूत u32 __mcfgpio_ppdr(अचिन्हित gpio)
अणु
#अगर defined(CONFIG_M5206) || defined(CONFIG_M5206e) || \
    defined(CONFIG_M5307) || defined(CONFIG_M5407)
	वापस MCFSIM_PADAT;
#या_अगर defined(CONFIG_M5272)
	अगर (gpio < 16)
		वापस MCFSIM_PADAT;
	अन्यथा अगर (gpio < 32)
		वापस MCFSIM_PBDAT;
	अन्यथा
		वापस MCFSIM_PCDAT;
#या_अगर defined(CONFIG_M5249) || defined(CONFIG_M525x)
	अगर (gpio < 32)
		वापस MCFSIM2_GPIOREAD;
	अन्यथा
		वापस MCFSIM2_GPIO1READ;
#या_अगर defined(CONFIG_M520x) || defined(CONFIG_M523x) || \
      defined(CONFIG_M527x) || defined(CONFIG_M528x) || \
      defined(CONFIG_M53xx) || defined(CONFIG_M54xx) || \
      defined(CONFIG_M5441x)
#अगर !defined(CONFIG_M5441x)
	अगर (gpio < 8)
		वापस MCFEPORT_EPPDR;
#अगर defined(CONFIG_M528x)
	अन्यथा अगर (gpio < 16)
		वापस MCFGPTA_GPTPORT;
	अन्यथा अगर (gpio < 24)
		वापस MCFGPTB_GPTPORT;
	अन्यथा अगर (gpio < 32)
		वापस MCFQADC_PORTQA;
	अन्यथा अगर (gpio < 40)
		वापस MCFQADC_PORTQB;
#पूर्ण_अगर /* defined(CONFIG_M528x) */
	अन्यथा
#पूर्ण_अगर /* !defined(CONFIG_M5441x) */
		वापस MCFGPIO_PPDR + mcfgpio_port(gpio - MCFGPIO_SCR_START);
#अन्यथा
	वापस 0;
#पूर्ण_अगर
पूर्ण

/* वापस the port output data रेजिस्टर क्रम a gpio */
अटल अंतरभूत u32 __mcfgpio_podr(अचिन्हित gpio)
अणु
#अगर defined(CONFIG_M5206) || defined(CONFIG_M5206e) || \
    defined(CONFIG_M5307) || defined(CONFIG_M5407)
	वापस MCFSIM_PADAT;
#या_अगर defined(CONFIG_M5272)
	अगर (gpio < 16)
		वापस MCFSIM_PADAT;
	अन्यथा अगर (gpio < 32)
		वापस MCFSIM_PBDAT;
	अन्यथा
		वापस MCFSIM_PCDAT;
#या_अगर defined(CONFIG_M5249) || defined(CONFIG_M525x)
	अगर (gpio < 32)
		वापस MCFSIM2_GPIOWRITE;
	अन्यथा
		वापस MCFSIM2_GPIO1WRITE;
#या_अगर defined(CONFIG_M520x) || defined(CONFIG_M523x) || \
      defined(CONFIG_M527x) || defined(CONFIG_M528x) || \
      defined(CONFIG_M53xx) || defined(CONFIG_M54xx) || \
      defined(CONFIG_M5441x)
#अगर !defined(CONFIG_M5441x)
	अगर (gpio < 8)
		वापस MCFEPORT_EPDR;
#अगर defined(CONFIG_M528x)
	अन्यथा अगर (gpio < 16)
		वापस MCFGPTA_GPTPORT;
	अन्यथा अगर (gpio < 24)
		वापस MCFGPTB_GPTPORT;
	अन्यथा अगर (gpio < 32)
		वापस MCFQADC_PORTQA;
	अन्यथा अगर (gpio < 40)
		वापस MCFQADC_PORTQB;
#पूर्ण_अगर /* defined(CONFIG_M528x) */
	अन्यथा
#पूर्ण_अगर /* !defined(CONFIG_M5441x) */
		वापस MCFGPIO_PODR + mcfgpio_port(gpio - MCFGPIO_SCR_START);
#अन्यथा
	वापस 0;
#पूर्ण_अगर
पूर्ण

/* वापस the port direction data रेजिस्टर क्रम a gpio */
अटल अंतरभूत u32 __mcfgpio_pddr(अचिन्हित gpio)
अणु
#अगर defined(CONFIG_M5206) || defined(CONFIG_M5206e) || \
    defined(CONFIG_M5307) || defined(CONFIG_M5407)
	वापस MCFSIM_PADDR;
#या_अगर defined(CONFIG_M5272)
	अगर (gpio < 16)
		वापस MCFSIM_PADDR;
	अन्यथा अगर (gpio < 32)
		वापस MCFSIM_PBDDR;
	अन्यथा
		वापस MCFSIM_PCDDR;
#या_अगर defined(CONFIG_M5249) || defined(CONFIG_M525x)
	अगर (gpio < 32)
		वापस MCFSIM2_GPIOENABLE;
	अन्यथा
		वापस MCFSIM2_GPIO1ENABLE;
#या_अगर defined(CONFIG_M520x) || defined(CONFIG_M523x) || \
      defined(CONFIG_M527x) || defined(CONFIG_M528x) || \
      defined(CONFIG_M53xx) || defined(CONFIG_M54xx) || \
      defined(CONFIG_M5441x)
#अगर !defined(CONFIG_M5441x)
	अगर (gpio < 8)
		वापस MCFEPORT_EPDDR;
#अगर defined(CONFIG_M528x)
	अन्यथा अगर (gpio < 16)
		वापस MCFGPTA_GPTDDR;
	अन्यथा अगर (gpio < 24)
		वापस MCFGPTB_GPTDDR;
	अन्यथा अगर (gpio < 32)
		वापस MCFQADC_DDRQA;
	अन्यथा अगर (gpio < 40)
		वापस MCFQADC_DDRQB;
#पूर्ण_अगर /* defined(CONFIG_M528x) */
	अन्यथा
#पूर्ण_अगर /* !defined(CONFIG_M5441x) */
		वापस MCFGPIO_PDDR + mcfgpio_port(gpio - MCFGPIO_SCR_START);
#अन्यथा
	वापस 0;
#पूर्ण_अगर
पूर्ण

#पूर्ण_अगर /* mcfgpio_h */
