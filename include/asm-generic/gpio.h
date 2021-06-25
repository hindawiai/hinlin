<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_GENERIC_GPIO_H
#घोषणा _ASM_GENERIC_GPIO_H

#समावेश <linux/types.h>
#समावेश <linux/त्रुटिसं.स>

#अगर_घोषित CONFIG_GPIOLIB

#समावेश <linux/compiler.h>
#समावेश <linux/gpio/driver.h>
#समावेश <linux/gpio/consumer.h>

/* Platक्रमms may implement their GPIO पूर्णांकerface with library code,
 * at a small perक्रमmance cost क्रम non-अंतरभूतd operations and some
 * extra memory (क्रम code and क्रम per-GPIO table entries).
 *
 * While the GPIO programming पूर्णांकerface defines valid GPIO numbers
 * to be in the range 0..MAX_INT, this library restricts them to the
 * smaller range 0..ARCH_NR_GPIOS-1.
 *
 * ARCH_NR_GPIOS is somewhat arbitrary; it usually reflects the sum of
 * builtin/SoC GPIOs plus a number of GPIOs on expanders; the latter is
 * actually an estimate of a board-specअगरic value.
 */

#अगर_अघोषित ARCH_NR_GPIOS
#अगर defined(CONFIG_ARCH_NR_GPIO) && CONFIG_ARCH_NR_GPIO > 0
#घोषणा ARCH_NR_GPIOS CONFIG_ARCH_NR_GPIO
#अन्यथा
#घोषणा ARCH_NR_GPIOS		512
#पूर्ण_अगर
#पूर्ण_अगर

/*
 * "valid" GPIO numbers are nonnegative and may be passed to
 * setup routines like gpio_request().  only some valid numbers
 * can successfully be requested and used.
 *
 * Invalid GPIO numbers are useful क्रम indicating no-such-GPIO in
 * platक्रमm data and other tables.
 */

अटल अंतरभूत bool gpio_is_valid(पूर्णांक number)
अणु
	वापस number >= 0 && number < ARCH_NR_GPIOS;
पूर्ण

काष्ठा device;
काष्ठा gpio;
काष्ठा seq_file;
काष्ठा module;
काष्ठा device_node;
काष्ठा gpio_desc;

/* caller holds gpio_lock *OR* gpio is marked as requested */
अटल अंतरभूत काष्ठा gpio_chip *gpio_to_chip(अचिन्हित gpio)
अणु
	वापस gpiod_to_chip(gpio_to_desc(gpio));
पूर्ण

/* Always use the library code क्रम GPIO management calls,
 * or when sleeping may be involved.
 */
बाह्य पूर्णांक gpio_request(अचिन्हित gpio, स्थिर अक्षर *label);
बाह्य व्योम gpio_मुक्त(अचिन्हित gpio);

अटल अंतरभूत पूर्णांक gpio_direction_input(अचिन्हित gpio)
अणु
	वापस gpiod_direction_input(gpio_to_desc(gpio));
पूर्ण
अटल अंतरभूत पूर्णांक gpio_direction_output(अचिन्हित gpio, पूर्णांक value)
अणु
	वापस gpiod_direction_output_raw(gpio_to_desc(gpio), value);
पूर्ण

अटल अंतरभूत पूर्णांक gpio_set_debounce(अचिन्हित gpio, अचिन्हित debounce)
अणु
	वापस gpiod_set_debounce(gpio_to_desc(gpio), debounce);
पूर्ण

अटल अंतरभूत पूर्णांक gpio_get_value_cansleep(अचिन्हित gpio)
अणु
	वापस gpiod_get_raw_value_cansleep(gpio_to_desc(gpio));
पूर्ण
अटल अंतरभूत व्योम gpio_set_value_cansleep(अचिन्हित gpio, पूर्णांक value)
अणु
	वापस gpiod_set_raw_value_cansleep(gpio_to_desc(gpio), value);
पूर्ण


/* A platक्रमm's <यंत्र/gpपन.स> code may want to अंतरभूत the I/O calls when
 * the GPIO is स्थिरant and refers to some always-present controller,
 * giving direct access to chip रेजिस्टरs and tight bitbanging loops.
 */
अटल अंतरभूत पूर्णांक __gpio_get_value(अचिन्हित gpio)
अणु
	वापस gpiod_get_raw_value(gpio_to_desc(gpio));
पूर्ण
अटल अंतरभूत व्योम __gpio_set_value(अचिन्हित gpio, पूर्णांक value)
अणु
	वापस gpiod_set_raw_value(gpio_to_desc(gpio), value);
पूर्ण

अटल अंतरभूत पूर्णांक __gpio_cansleep(अचिन्हित gpio)
अणु
	वापस gpiod_cansleep(gpio_to_desc(gpio));
पूर्ण

अटल अंतरभूत पूर्णांक __gpio_to_irq(अचिन्हित gpio)
अणु
	वापस gpiod_to_irq(gpio_to_desc(gpio));
पूर्ण

बाह्य पूर्णांक gpio_request_one(अचिन्हित gpio, अचिन्हित दीर्घ flags, स्थिर अक्षर *label);
बाह्य पूर्णांक gpio_request_array(स्थिर काष्ठा gpio *array, माप_प्रकार num);
बाह्य व्योम gpio_मुक्त_array(स्थिर काष्ठा gpio *array, माप_प्रकार num);

/*
 * A sysfs पूर्णांकerface can be exported by inभागidual drivers अगर they want,
 * but more typically is configured entirely from userspace.
 */
अटल अंतरभूत पूर्णांक gpio_export(अचिन्हित gpio, bool direction_may_change)
अणु
	वापस gpiod_export(gpio_to_desc(gpio), direction_may_change);
पूर्ण

अटल अंतरभूत पूर्णांक gpio_export_link(काष्ठा device *dev, स्थिर अक्षर *name,
				   अचिन्हित gpio)
अणु
	वापस gpiod_export_link(dev, name, gpio_to_desc(gpio));
पूर्ण

अटल अंतरभूत व्योम gpio_unexport(अचिन्हित gpio)
अणु
	gpiod_unexport(gpio_to_desc(gpio));
पूर्ण

#अन्यथा	/* !CONFIG_GPIOLIB */

#समावेश <linux/kernel.h>

अटल अंतरभूत bool gpio_is_valid(पूर्णांक number)
अणु
	/* only non-negative numbers are valid */
	वापस number >= 0;
पूर्ण

/* platक्रमms that करोn't directly support access to GPIOs through I2C, SPI,
 * or other blocking infraकाष्ठाure can use these wrappers.
 */

अटल अंतरभूत पूर्णांक gpio_cansleep(अचिन्हित gpio)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक gpio_get_value_cansleep(अचिन्हित gpio)
अणु
	might_sleep();
	वापस __gpio_get_value(gpio);
पूर्ण

अटल अंतरभूत व्योम gpio_set_value_cansleep(अचिन्हित gpio, पूर्णांक value)
अणु
	might_sleep();
	__gpio_set_value(gpio, value);
पूर्ण

#पूर्ण_अगर /* !CONFIG_GPIOLIB */

#पूर्ण_अगर /* _ASM_GENERIC_GPIO_H */
