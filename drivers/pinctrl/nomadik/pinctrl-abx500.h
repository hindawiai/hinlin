<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित PINCTRL_PINCTRL_ABx500_H
#घोषणा PINCTRL_PINCTRL_ABx500_H

/* Package definitions */
#घोषणा PINCTRL_AB8500	0
#घोषणा PINCTRL_AB8505	1

/* pins alternate function */
क्रमागत abx500_pin_func अणु
	ABX500_DEFAULT,
	ABX500_ALT_A,
	ABX500_ALT_B,
	ABX500_ALT_C,
पूर्ण;

क्रमागत abx500_gpio_pull_upकरोwn अणु
	ABX500_GPIO_PULL_DOWN = 0x0,
	ABX500_GPIO_PULL_NONE = 0x1,
	ABX500_GPIO_PULL_UP = 0x3,
पूर्ण;

क्रमागत abx500_gpio_vinsel अणु
	ABX500_GPIO_VINSEL_VBAT = 0x0,
	ABX500_GPIO_VINSEL_VIN_1V8 = 0x1,
	ABX500_GPIO_VINSEL_VDD_BIF = 0x2,
पूर्ण;

/**
 * काष्ठा abx500_function - ABx500 pinctrl mux function
 * @name: The name of the function, exported to pinctrl core.
 * @groups: An array of pin groups that may select this function.
 * @ngroups: The number of entries in @groups.
 */
काष्ठा abx500_function अणु
	स्थिर अक्षर *name;
	स्थिर अक्षर * स्थिर *groups;
	अचिन्हित ngroups;
पूर्ण;

/**
 * काष्ठा abx500_pingroup - describes a ABx500 pin group
 * @name: the name of this specअगरic pin group
 * @pins: an array of discrete physical pins used in this group, taken
 *	from the driver-local pin क्रमागतeration space
 * @num_pins: the number of pins in this group array, i.e. the number of
 *	elements in .pins so we can iterate over that array
 * @altsetting: the altsetting to apply to all pins in this group to
 *	configure them to be used by a function
 */
काष्ठा abx500_pingroup अणु
	स्थिर अक्षर *name;
	स्थिर अचिन्हित पूर्णांक *pins;
	स्थिर अचिन्हित npins;
	पूर्णांक altsetting;
पूर्ण;

#घोषणा ALTERNATE_FUNCTIONS(pin, sel_bit, alt1, alt2, alta, altb, altc)	\
अणु									\
	.pin_number = pin,						\
	.gpiosel_bit = sel_bit,						\
	.alt_bit1 = alt1,						\
	.alt_bit2 = alt2,						\
	.alta_val = alta,						\
	.altb_val = altb,						\
	.altc_val = altc,						\
पूर्ण

#घोषणा UNUSED -1
/**
 * काष्ठा alternate_functions
 * @pin_number:		The pin number
 * @gpiosel_bit:	Control bit in GPIOSEL रेजिस्टर,
 * @alt_bit1:		First AlternateFunction bit used to select the
 *			alternate function
 * @alt_bit2:		Second AlternateFunction bit used to select the
 *			alternate function
 *
 *			these 3 following fields are necessary due to none
 *			coherency on how to select the altA, altB and altC
 *			function between the ABx500 SOC family when using
 *			alternatfunc रेजिस्टर.
 * @alta_val:		value to ग_लिखो in alternatfunc to select altA function
 * @altb_val:		value to ग_लिखो in alternatfunc to select altB function
 * @altc_val:		value to ग_लिखो in alternatfunc to select altC function
 */
काष्ठा alternate_functions अणु
	अचिन्हित pin_number;
	s8 gpiosel_bit;
	s8 alt_bit1;
	s8 alt_bit2;
	u8 alta_val;
	u8 altb_val;
	u8 altc_val;
पूर्ण;

#घोषणा GPIO_IRQ_CLUSTER(a, b, c)	\
अणु					\
	.start = a,			\
	.end = b,			\
	.to_irq = c,			\
पूर्ण

/**
 * काष्ठा abx500_gpio_irq_cluster - indicates GPIOs which are पूर्णांकerrupt
 *			capable
 * @start:		The pin number of the first pin पूर्णांकerrupt capable
 * @end:		The pin number of the last pin पूर्णांकerrupt capable
 * @to_irq:		The ABx500 GPIO's associated IRQs are clustered
 *                      together throughout the पूर्णांकerrupt numbers at irregular
 *                      पूर्णांकervals. To solve this quandary, we will place the
 *                      पढ़ो-in values पूर्णांकo the cluster inक्रमmation table
 */

काष्ठा abx500_gpio_irq_cluster अणु
	पूर्णांक start;
	पूर्णांक end;
	पूर्णांक to_irq;
पूर्ण;

/**
 * काष्ठा abx500_pinrange - map pin numbers to GPIO offsets
 * @offset:		offset पूर्णांकo the GPIO local numberspace, incidentally
 *			identical to the offset पूर्णांकo the local pin numberspace
 * @npins:		number of pins to map from both offsets
 * @altfunc:		altfunc setting to be used to enable GPIO on a pin in
 *			this range (may vary)
 */
काष्ठा abx500_pinrange अणु
	अचिन्हित पूर्णांक offset;
	अचिन्हित पूर्णांक npins;
	पूर्णांक altfunc;
पूर्ण;

#घोषणा ABX500_PINRANGE(a, b, c) अणु .offset = a, .npins = b, .altfunc = c पूर्ण

/**
 * काष्ठा abx500_pinctrl_soc_data - ABx500 pin controller per-SoC configuration
 * @gpio_ranges:	An array of GPIO ranges क्रम this SoC
 * @gpio_num_ranges:	The number of GPIO ranges क्रम this SoC
 * @pins:		An array describing all pins the pin controller affects.
 *			All pins which are also GPIOs must be listed first within the
 *			array, and be numbered identically to the GPIO controller's
 *			numbering.
 * @npins:		The number of entries in @pins.
 * @functions:		The functions supported on this SoC.
 * @nfunction:		The number of entries in @functions.
 * @groups:		An array describing all pin groups the pin SoC supports.
 * @ngroups:		The number of entries in @groups.
 * @alternate_functions: array describing pins which supports alternate and
 *			how to set it.
 * @gpio_irq_cluster:	An array of GPIO पूर्णांकerrupt capable क्रम this SoC
 * @ngpio_irq_cluster:	The number of GPIO inetrrupt capable क्रम this SoC
 * @irq_gpio_rising_offset: Interrupt offset used as base to compute specअगरic
 *			setting strategy of the rising पूर्णांकerrupt line
 * @irq_gpio_falling_offset: Interrupt offset used as base to compute specअगरic
 *			setting strategy of the falling पूर्णांकerrupt line
 * @irq_gpio_factor:	Factor used to compute specअगरic setting strategy of
 *			the पूर्णांकerrupt line
 */

काष्ठा abx500_pinctrl_soc_data अणु
	स्थिर काष्ठा abx500_pinrange *gpio_ranges;
	अचिन्हित gpio_num_ranges;
	स्थिर काष्ठा pinctrl_pin_desc *pins;
	अचिन्हित npins;
	स्थिर काष्ठा abx500_function *functions;
	अचिन्हित nfunctions;
	स्थिर काष्ठा abx500_pingroup *groups;
	अचिन्हित ngroups;
	काष्ठा alternate_functions *alternate_functions;
	काष्ठा abx500_gpio_irq_cluster *gpio_irq_cluster;
	अचिन्हित ngpio_irq_cluster;
	पूर्णांक irq_gpio_rising_offset;
	पूर्णांक irq_gpio_falling_offset;
	पूर्णांक irq_gpio_factor;
पूर्ण;

#अगर_घोषित CONFIG_PINCTRL_AB8500

व्योम abx500_pinctrl_ab8500_init(काष्ठा abx500_pinctrl_soc_data **soc);

#अन्यथा

अटल अंतरभूत व्योम
abx500_pinctrl_ab8500_init(काष्ठा abx500_pinctrl_soc_data **soc)
अणु
पूर्ण

#पूर्ण_अगर

#अगर_घोषित CONFIG_PINCTRL_AB8505

व्योम abx500_pinctrl_ab8505_init(काष्ठा abx500_pinctrl_soc_data **soc);

#अन्यथा

अटल अंतरभूत व्योम
abx500_pinctrl_ab8505_init(काष्ठा abx500_pinctrl_soc_data **soc)
अणु
पूर्ण

#पूर्ण_अगर

#पूर्ण_अगर /* PINCTRL_PINCTRL_ABx500_H */
