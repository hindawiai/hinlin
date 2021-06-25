<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __LINUX_GPIO_DRIVER_H
#घोषणा __LINUX_GPIO_DRIVER_H

#समावेश <linux/device.h>
#समावेश <linux/types.h>
#समावेश <linux/irq.h>
#समावेश <linux/irqchip/chained_irq.h>
#समावेश <linux/irqकरोमुख्य.h>
#समावेश <linux/lockdep.h>
#समावेश <linux/pinctrl/pinctrl.h>
#समावेश <linux/pinctrl/pinconf-generic.h>

काष्ठा gpio_desc;
काष्ठा of_phandle_args;
काष्ठा device_node;
काष्ठा seq_file;
काष्ठा gpio_device;
काष्ठा module;
क्रमागत gpiod_flags;
क्रमागत gpio_lookup_flags;

काष्ठा gpio_chip;

#घोषणा GPIO_LINE_सूचीECTION_IN	1
#घोषणा GPIO_LINE_सूचीECTION_OUT	0

/**
 * काष्ठा gpio_irq_chip - GPIO पूर्णांकerrupt controller
 */
काष्ठा gpio_irq_chip अणु
	/**
	 * @chip:
	 *
	 * GPIO IRQ chip implementation, provided by GPIO driver.
	 */
	काष्ठा irq_chip *chip;

	/**
	 * @करोमुख्य:
	 *
	 * Interrupt translation करोमुख्य; responsible क्रम mapping between GPIO
	 * hwirq number and Linux IRQ number.
	 */
	काष्ठा irq_करोमुख्य *करोमुख्य;

	/**
	 * @करोमुख्य_ops:
	 *
	 * Table of पूर्णांकerrupt करोमुख्य operations क्रम this IRQ chip.
	 */
	स्थिर काष्ठा irq_करोमुख्य_ops *करोमुख्य_ops;

#अगर_घोषित CONFIG_IRQ_DOMAIN_HIERARCHY
	/**
	 * @fwnode:
	 *
	 * Firmware node corresponding to this gpiochip/irqchip, necessary
	 * क्रम hierarchical irqकरोमुख्य support.
	 */
	काष्ठा fwnode_handle *fwnode;

	/**
	 * @parent_करोमुख्य:
	 *
	 * If non-शून्य, will be set as the parent of this GPIO पूर्णांकerrupt
	 * controller's IRQ करोमुख्य to establish a hierarchical पूर्णांकerrupt
	 * करोमुख्य. The presence of this will activate the hierarchical
	 * पूर्णांकerrupt support.
	 */
	काष्ठा irq_करोमुख्य *parent_करोमुख्य;

	/**
	 * @child_to_parent_hwirq:
	 *
	 * This callback translates a child hardware IRQ offset to a parent
	 * hardware IRQ offset on a hierarchical पूर्णांकerrupt chip. The child
	 * hardware IRQs correspond to the GPIO index 0..ngpio-1 (see the
	 * ngpio field of काष्ठा gpio_chip) and the corresponding parent
	 * hardware IRQ and type (such as IRQ_TYPE_*) shall be वापसed by
	 * the driver. The driver can calculate this from an offset or using
	 * a lookup table or whatever method is best क्रम this chip. Return
	 * 0 on successful translation in the driver.
	 *
	 * If some ranges of hardware IRQs करो not have a corresponding parent
	 * HWIRQ, वापस -EINVAL, but also make sure to fill in @valid_mask and
	 * @need_valid_mask to make these GPIO lines unavailable क्रम
	 * translation.
	 */
	पूर्णांक (*child_to_parent_hwirq)(काष्ठा gpio_chip *gc,
				     अचिन्हित पूर्णांक child_hwirq,
				     अचिन्हित पूर्णांक child_type,
				     अचिन्हित पूर्णांक *parent_hwirq,
				     अचिन्हित पूर्णांक *parent_type);

	/**
	 * @populate_parent_alloc_arg :
	 *
	 * This optional callback allocates and populates the specअगरic काष्ठा
	 * क्रम the parent's IRQ करोमुख्य. If this is not specअगरied, then
	 * &gpiochip_populate_parent_fwspec_twocell will be used. A four-cell
	 * variant named &gpiochip_populate_parent_fwspec_fourcell is also
	 * available.
	 */
	व्योम *(*populate_parent_alloc_arg)(काष्ठा gpio_chip *gc,
				       अचिन्हित पूर्णांक parent_hwirq,
				       अचिन्हित पूर्णांक parent_type);

	/**
	 * @child_offset_to_irq:
	 *
	 * This optional callback is used to translate the child's GPIO line
	 * offset on the GPIO chip to an IRQ number क्रम the GPIO to_irq()
	 * callback. If this is not specअगरied, then a शेष callback will be
	 * provided that वापसs the line offset.
	 */
	अचिन्हित पूर्णांक (*child_offset_to_irq)(काष्ठा gpio_chip *gc,
					    अचिन्हित पूर्णांक pin);

	/**
	 * @child_irq_करोमुख्य_ops:
	 *
	 * The IRQ करोमुख्य operations that will be used क्रम this GPIO IRQ
	 * chip. If no operations are provided, then शेष callbacks will
	 * be populated to setup the IRQ hierarchy. Some drivers need to
	 * supply their own translate function.
	 */
	काष्ठा irq_करोमुख्य_ops child_irq_करोमुख्य_ops;
#पूर्ण_अगर

	/**
	 * @handler:
	 *
	 * The IRQ handler to use (often a predefined IRQ core function) क्रम
	 * GPIO IRQs, provided by GPIO driver.
	 */
	irq_flow_handler_t handler;

	/**
	 * @शेष_type:
	 *
	 * Default IRQ triggering type applied during GPIO driver
	 * initialization, provided by GPIO driver.
	 */
	अचिन्हित पूर्णांक शेष_type;

	/**
	 * @lock_key:
	 *
	 * Per GPIO IRQ chip lockdep class क्रम IRQ lock.
	 */
	काष्ठा lock_class_key *lock_key;

	/**
	 * @request_key:
	 *
	 * Per GPIO IRQ chip lockdep class क्रम IRQ request.
	 */
	काष्ठा lock_class_key *request_key;

	/**
	 * @parent_handler:
	 *
	 * The पूर्णांकerrupt handler क्रम the GPIO chip's parent पूर्णांकerrupts, may be
	 * शून्य अगर the parent पूर्णांकerrupts are nested rather than cascaded.
	 */
	irq_flow_handler_t parent_handler;

	/**
	 * @parent_handler_data:
	 *
	 * Data associated, and passed to, the handler क्रम the parent
	 * पूर्णांकerrupt.
	 */
	व्योम *parent_handler_data;

	/**
	 * @num_parents:
	 *
	 * The number of पूर्णांकerrupt parents of a GPIO chip.
	 */
	अचिन्हित पूर्णांक num_parents;

	/**
	 * @parents:
	 *
	 * A list of पूर्णांकerrupt parents of a GPIO chip. This is owned by the
	 * driver, so the core will only reference this list, not modअगरy it.
	 */
	अचिन्हित पूर्णांक *parents;

	/**
	 * @map:
	 *
	 * A list of पूर्णांकerrupt parents क्रम each line of a GPIO chip.
	 */
	अचिन्हित पूर्णांक *map;

	/**
	 * @thपढ़ोed:
	 *
	 * True अगर set the पूर्णांकerrupt handling uses nested thपढ़ोs.
	 */
	bool thपढ़ोed;

	/**
	 * @init_hw: optional routine to initialize hardware beक्रमe
	 * an IRQ chip will be added. This is quite useful when
	 * a particular driver wants to clear IRQ related रेजिस्टरs
	 * in order to aव्योम undesired events.
	 */
	पूर्णांक (*init_hw)(काष्ठा gpio_chip *gc);

	/**
	 * @init_valid_mask: optional routine to initialize @valid_mask, to be
	 * used अगर not all GPIO lines are valid पूर्णांकerrupts. Someबार some
	 * lines just cannot fire पूर्णांकerrupts, and this routine, when defined,
	 * is passed a biपंचांगap in "valid_mask" and it will have ngpios
	 * bits from 0..(ngpios-1) set to "1" as in valid. The callback can
	 * then directly set some bits to "0" अगर they cannot be used क्रम
	 * पूर्णांकerrupts.
	 */
	व्योम (*init_valid_mask)(काष्ठा gpio_chip *gc,
				अचिन्हित दीर्घ *valid_mask,
				अचिन्हित पूर्णांक ngpios);

	/**
	 * @valid_mask:
	 *
	 * If not %शून्य, holds biपंचांगask of GPIOs which are valid to be included
	 * in IRQ करोमुख्य of the chip.
	 */
	अचिन्हित दीर्घ *valid_mask;

	/**
	 * @first:
	 *
	 * Required क्रम अटल IRQ allocation. If set, irq_करोमुख्य_add_simple()
	 * will allocate and map all IRQs during initialization.
	 */
	अचिन्हित पूर्णांक first;

	/**
	 * @irq_enable:
	 *
	 * Store old irq_chip irq_enable callback
	 */
	व्योम		(*irq_enable)(काष्ठा irq_data *data);

	/**
	 * @irq_disable:
	 *
	 * Store old irq_chip irq_disable callback
	 */
	व्योम		(*irq_disable)(काष्ठा irq_data *data);
	/**
	 * @irq_unmask:
	 *
	 * Store old irq_chip irq_unmask callback
	 */
	व्योम		(*irq_unmask)(काष्ठा irq_data *data);

	/**
	 * @irq_mask:
	 *
	 * Store old irq_chip irq_mask callback
	 */
	व्योम		(*irq_mask)(काष्ठा irq_data *data);
पूर्ण;

/**
 * काष्ठा gpio_chip - असलtract a GPIO controller
 * @label: a functional name क्रम the GPIO device, such as a part
 *	number or the name of the SoC IP-block implementing it.
 * @gpiodev: the पूर्णांकernal state holder, opaque काष्ठा
 * @parent: optional parent device providing the GPIOs
 * @owner: helps prevent removal of modules exporting active GPIOs
 * @request: optional hook क्रम chip-specअगरic activation, such as
 *	enabling module घातer and घड़ी; may sleep
 * @मुक्त: optional hook क्रम chip-specअगरic deactivation, such as
 *	disabling module घातer and घड़ी; may sleep
 * @get_direction: वापसs direction क्रम संकेत "offset", 0=out, 1=in,
 *	(same as GPIO_LINE_सूचीECTION_OUT / GPIO_LINE_सूचीECTION_IN),
 *	or negative error. It is recommended to always implement this
 *	function, even on input-only or output-only gpio chips.
 * @direction_input: configures संकेत "offset" as input, or वापसs error
 *	This can be omitted on input-only or output-only gpio chips.
 * @direction_output: configures संकेत "offset" as output, or वापसs error
 *	This can be omitted on input-only or output-only gpio chips.
 * @get: वापसs value क्रम संकेत "offset", 0=low, 1=high, or negative error
 * @get_multiple: पढ़ोs values क्रम multiple संकेतs defined by "mask" and
 *	stores them in "bits", वापसs 0 on success or negative error
 * @set: assigns output value क्रम संकेत "offset"
 * @set_multiple: assigns output values क्रम multiple संकेतs defined by "mask"
 * @set_config: optional hook क्रम all kinds of settings. Uses the same
 *	packed config क्रमmat as generic pinconf.
 * @to_irq: optional hook supporting non-अटल gpio_to_irq() mappings;
 *	implementation may not sleep
 * @dbg_show: optional routine to show contents in debugfs; शेष code
 *	will be used when this is omitted, but custom code can show extra
 *	state (such as pullup/pullकरोwn configuration).
 * @init_valid_mask: optional routine to initialize @valid_mask, to be used अगर
 *	not all GPIOs are valid.
 * @add_pin_ranges: optional routine to initialize pin ranges, to be used when
 *	requires special mapping of the pins that provides GPIO functionality.
 *	It is called after adding GPIO chip and beक्रमe adding IRQ chip.
 * @base: identअगरies the first GPIO number handled by this chip;
 *	or, अगर negative during registration, requests dynamic ID allocation.
 *	DEPRECATION: providing anything non-negative and nailing the base
 *	offset of GPIO chips is deprecated. Please pass -1 as base to
 *	let gpiolib select the chip base in all possible हालs. We want to
 *	get rid of the अटल GPIO number space in the दीर्घ run.
 * @ngpio: the number of GPIOs handled by this controller; the last GPIO
 *	handled is (base + ngpio - 1).
 * @names: अगर set, must be an array of strings to use as alternative
 *      names क्रम the GPIOs in this chip. Any entry in the array
 *      may be शून्य अगर there is no alias क्रम the GPIO, however the
 *      array must be @ngpio entries दीर्घ.  A name can include a single prपूर्णांकk
 *      क्रमmat specअगरier क्रम an अचिन्हित पूर्णांक.  It is substituted by the actual
 *      number of the gpio.
 * @can_sleep: flag must be set अगरf get()/set() methods sleep, as they
 *	must जबतक accessing GPIO expander chips over I2C or SPI. This
 *	implies that अगर the chip supports IRQs, these IRQs need to be thपढ़ोed
 *	as the chip access may sleep when e.g. पढ़ोing out the IRQ status
 *	रेजिस्टरs.
 * @पढ़ो_reg: पढ़ोer function क्रम generic GPIO
 * @ग_लिखो_reg: ग_लिखोr function क्रम generic GPIO
 * @be_bits: अगर the generic GPIO has big endian bit order (bit 31 is representing
 *	line 0, bit 30 is line 1 ... bit 0 is line 31) this is set to true by the
 *	generic GPIO core. It is क्रम पूर्णांकernal housekeeping only.
 * @reg_dat: data (in) रेजिस्टर क्रम generic GPIO
 * @reg_set: output set रेजिस्टर (out=high) क्रम generic GPIO
 * @reg_clr: output clear रेजिस्टर (out=low) क्रम generic GPIO
 * @reg_dir_out: direction out setting रेजिस्टर क्रम generic GPIO
 * @reg_dir_in: direction in setting रेजिस्टर क्रम generic GPIO
 * @bgpio_dir_unपढ़ोable: indicates that the direction रेजिस्टर(s) cannot
 *	be पढ़ो and we need to rely on out पूर्णांकernal state tracking.
 * @bgpio_bits: number of रेजिस्टर bits used क्रम a generic GPIO i.e.
 *	<रेजिस्टर width> * 8
 * @bgpio_lock: used to lock chip->bgpio_data. Also, this is needed to keep
 *	shaकरोwed and real data रेजिस्टरs ग_लिखोs together.
 * @bgpio_data:	shaकरोwed data रेजिस्टर क्रम generic GPIO to clear/set bits
 *	safely.
 * @bgpio_dir: shaकरोwed direction रेजिस्टर क्रम generic GPIO to clear/set
 *	direction safely. A "1" in this word means the line is set as
 *	output.
 *
 * A gpio_chip can help platक्रमms असलtract various sources of GPIOs so
 * they can all be accessed through a common programming पूर्णांकerface.
 * Example sources would be SOC controllers, FPGAs, multअगरunction
 * chips, dedicated GPIO expanders, and so on.
 *
 * Each chip controls a number of संकेतs, identअगरied in method calls
 * by "offset" values in the range 0..(@ngpio - 1).  When those संकेतs
 * are referenced through calls like gpio_get_value(gpio), the offset
 * is calculated by subtracting @base from the gpio number.
 */
काष्ठा gpio_chip अणु
	स्थिर अक्षर		*label;
	काष्ठा gpio_device	*gpiodev;
	काष्ठा device		*parent;
	काष्ठा module		*owner;

	पूर्णांक			(*request)(काष्ठा gpio_chip *gc,
						अचिन्हित पूर्णांक offset);
	व्योम			(*मुक्त)(काष्ठा gpio_chip *gc,
						अचिन्हित पूर्णांक offset);
	पूर्णांक			(*get_direction)(काष्ठा gpio_chip *gc,
						अचिन्हित पूर्णांक offset);
	पूर्णांक			(*direction_input)(काष्ठा gpio_chip *gc,
						अचिन्हित पूर्णांक offset);
	पूर्णांक			(*direction_output)(काष्ठा gpio_chip *gc,
						अचिन्हित पूर्णांक offset, पूर्णांक value);
	पूर्णांक			(*get)(काष्ठा gpio_chip *gc,
						अचिन्हित पूर्णांक offset);
	पूर्णांक			(*get_multiple)(काष्ठा gpio_chip *gc,
						अचिन्हित दीर्घ *mask,
						अचिन्हित दीर्घ *bits);
	व्योम			(*set)(काष्ठा gpio_chip *gc,
						अचिन्हित पूर्णांक offset, पूर्णांक value);
	व्योम			(*set_multiple)(काष्ठा gpio_chip *gc,
						अचिन्हित दीर्घ *mask,
						अचिन्हित दीर्घ *bits);
	पूर्णांक			(*set_config)(काष्ठा gpio_chip *gc,
					      अचिन्हित पूर्णांक offset,
					      अचिन्हित दीर्घ config);
	पूर्णांक			(*to_irq)(काष्ठा gpio_chip *gc,
						अचिन्हित पूर्णांक offset);

	व्योम			(*dbg_show)(काष्ठा seq_file *s,
						काष्ठा gpio_chip *gc);

	पूर्णांक			(*init_valid_mask)(काष्ठा gpio_chip *gc,
						   अचिन्हित दीर्घ *valid_mask,
						   अचिन्हित पूर्णांक ngpios);

	पूर्णांक			(*add_pin_ranges)(काष्ठा gpio_chip *gc);

	पूर्णांक			base;
	u16			ngpio;
	स्थिर अक्षर		*स्थिर *names;
	bool			can_sleep;

#अगर IS_ENABLED(CONFIG_GPIO_GENERIC)
	अचिन्हित दीर्घ (*पढ़ो_reg)(व्योम __iomem *reg);
	व्योम (*ग_लिखो_reg)(व्योम __iomem *reg, अचिन्हित दीर्घ data);
	bool be_bits;
	व्योम __iomem *reg_dat;
	व्योम __iomem *reg_set;
	व्योम __iomem *reg_clr;
	व्योम __iomem *reg_dir_out;
	व्योम __iomem *reg_dir_in;
	bool bgpio_dir_unपढ़ोable;
	पूर्णांक bgpio_bits;
	spinlock_t bgpio_lock;
	अचिन्हित दीर्घ bgpio_data;
	अचिन्हित दीर्घ bgpio_dir;
#पूर्ण_अगर /* CONFIG_GPIO_GENERIC */

#अगर_घोषित CONFIG_GPIOLIB_IRQCHIP
	/*
	 * With CONFIG_GPIOLIB_IRQCHIP we get an irqchip inside the gpiolib
	 * to handle IRQs क्रम most practical हालs.
	 */

	/**
	 * @irq:
	 *
	 * Integrates पूर्णांकerrupt chip functionality with the GPIO chip. Can be
	 * used to handle IRQs क्रम most practical हालs.
	 */
	काष्ठा gpio_irq_chip irq;
#पूर्ण_अगर /* CONFIG_GPIOLIB_IRQCHIP */

	/**
	 * @valid_mask:
	 *
	 * If not %शून्य, holds biपंचांगask of GPIOs which are valid to be used
	 * from the chip.
	 */
	अचिन्हित दीर्घ *valid_mask;

#अगर defined(CONFIG_OF_GPIO)
	/*
	 * If CONFIG_OF_GPIO is enabled, then all GPIO controllers described in
	 * the device tree स्वतःmatically may have an OF translation
	 */

	/**
	 * @of_node:
	 *
	 * Poपूर्णांकer to a device tree node representing this GPIO controller.
	 */
	काष्ठा device_node *of_node;

	/**
	 * @of_gpio_n_cells:
	 *
	 * Number of cells used to क्रमm the GPIO specअगरier.
	 */
	अचिन्हित पूर्णांक of_gpio_n_cells;

	/**
	 * @of_xlate:
	 *
	 * Callback to translate a device tree GPIO specअगरier पूर्णांकo a chip-
	 * relative GPIO number and flags.
	 */
	पूर्णांक (*of_xlate)(काष्ठा gpio_chip *gc,
			स्थिर काष्ठा of_phandle_args *gpiospec, u32 *flags);
#पूर्ण_अगर /* CONFIG_OF_GPIO */
पूर्ण;

बाह्य स्थिर अक्षर *gpiochip_is_requested(काष्ठा gpio_chip *gc,
			अचिन्हित पूर्णांक offset);

/**
 * क्रम_each_requested_gpio_in_range - iterates over requested GPIOs in a given range
 * @chip:	the chip to query
 * @i:		loop variable
 * @base:	first GPIO in the range
 * @size:	amount of GPIOs to check starting from @base
 * @label:	label of current GPIO
 */
#घोषणा क्रम_each_requested_gpio_in_range(chip, i, base, size, label)			\
	क्रम (i = 0; i < size; i++)							\
		अगर ((label = gpiochip_is_requested(chip, base + i)) == शून्य) अणुपूर्ण अन्यथा

/* Iterates over all requested GPIO of the given @chip */
#घोषणा क्रम_each_requested_gpio(chip, i, label)						\
	क्रम_each_requested_gpio_in_range(chip, i, 0, chip->ngpio, label)

/* add/हटाओ chips */
बाह्य पूर्णांक gpiochip_add_data_with_key(काष्ठा gpio_chip *gc, व्योम *data,
				      काष्ठा lock_class_key *lock_key,
				      काष्ठा lock_class_key *request_key);

/**
 * gpiochip_add_data() - रेजिस्टर a gpio_chip
 * @gc: the chip to रेजिस्टर, with gc->base initialized
 * @data: driver-निजी data associated with this chip
 *
 * Context: potentially beक्रमe irqs will work
 *
 * When gpiochip_add_data() is called very early during boot, so that GPIOs
 * can be मुक्तly used, the gc->parent device must be रेजिस्टरed beक्रमe
 * the gpio framework's arch_initcall().  Otherwise sysfs initialization
 * क्रम GPIOs will fail rudely.
 *
 * gpiochip_add_data() must only be called after gpiolib initialization,
 * i.e. after core_initcall().
 *
 * If gc->base is negative, this requests dynamic assignment of
 * a range of valid GPIOs.
 *
 * Returns:
 * A negative त्रुटि_सं अगर the chip can't be रेजिस्टरed, such as because the
 * gc->base is invalid or alपढ़ोy associated with a dअगरferent chip.
 * Otherwise it वापसs zero as a success code.
 */
#अगर_घोषित CONFIG_LOCKDEP
#घोषणा gpiochip_add_data(gc, data) (अणु		\
		अटल काष्ठा lock_class_key lock_key;	\
		अटल काष्ठा lock_class_key request_key;	  \
		gpiochip_add_data_with_key(gc, data, &lock_key, \
					   &request_key);	  \
	पूर्ण)
#घोषणा devm_gpiochip_add_data(dev, gc, data) (अणु \
		अटल काष्ठा lock_class_key lock_key;	\
		अटल काष्ठा lock_class_key request_key;	  \
		devm_gpiochip_add_data_with_key(dev, gc, data, &lock_key, \
					   &request_key);	  \
	पूर्ण)
#अन्यथा
#घोषणा gpiochip_add_data(gc, data) gpiochip_add_data_with_key(gc, data, शून्य, शून्य)
#घोषणा devm_gpiochip_add_data(dev, gc, data) \
	devm_gpiochip_add_data_with_key(dev, gc, data, शून्य, शून्य)
#पूर्ण_अगर /* CONFIG_LOCKDEP */

अटल अंतरभूत पूर्णांक gpiochip_add(काष्ठा gpio_chip *gc)
अणु
	वापस gpiochip_add_data(gc, शून्य);
पूर्ण
बाह्य व्योम gpiochip_हटाओ(काष्ठा gpio_chip *gc);
बाह्य पूर्णांक devm_gpiochip_add_data_with_key(काष्ठा device *dev, काष्ठा gpio_chip *gc, व्योम *data,
					   काष्ठा lock_class_key *lock_key,
					   काष्ठा lock_class_key *request_key);

बाह्य काष्ठा gpio_chip *gpiochip_find(व्योम *data,
			      पूर्णांक (*match)(काष्ठा gpio_chip *gc, व्योम *data));

bool gpiochip_line_is_irq(काष्ठा gpio_chip *gc, अचिन्हित पूर्णांक offset);
पूर्णांक gpiochip_reqres_irq(काष्ठा gpio_chip *gc, अचिन्हित पूर्णांक offset);
व्योम gpiochip_relres_irq(काष्ठा gpio_chip *gc, अचिन्हित पूर्णांक offset);
व्योम gpiochip_disable_irq(काष्ठा gpio_chip *gc, अचिन्हित पूर्णांक offset);
व्योम gpiochip_enable_irq(काष्ठा gpio_chip *gc, अचिन्हित पूर्णांक offset);

/* Line status inquiry क्रम drivers */
bool gpiochip_line_is_खोलो_drain(काष्ठा gpio_chip *gc, अचिन्हित पूर्णांक offset);
bool gpiochip_line_is_खोलो_source(काष्ठा gpio_chip *gc, अचिन्हित पूर्णांक offset);

/* Sleep persistence inquiry क्रम drivers */
bool gpiochip_line_is_persistent(काष्ठा gpio_chip *gc, अचिन्हित पूर्णांक offset);
bool gpiochip_line_is_valid(स्थिर काष्ठा gpio_chip *gc, अचिन्हित पूर्णांक offset);

/* get driver data */
व्योम *gpiochip_get_data(काष्ठा gpio_chip *gc);

काष्ठा bgpio_pdata अणु
	स्थिर अक्षर *label;
	पूर्णांक base;
	पूर्णांक ngpio;
पूर्ण;

#अगर_घोषित CONFIG_IRQ_DOMAIN_HIERARCHY

व्योम *gpiochip_populate_parent_fwspec_twocell(काष्ठा gpio_chip *gc,
					     अचिन्हित पूर्णांक parent_hwirq,
					     अचिन्हित पूर्णांक parent_type);
व्योम *gpiochip_populate_parent_fwspec_fourcell(काष्ठा gpio_chip *gc,
					      अचिन्हित पूर्णांक parent_hwirq,
					      अचिन्हित पूर्णांक parent_type);

#अन्यथा

अटल अंतरभूत व्योम *gpiochip_populate_parent_fwspec_twocell(काष्ठा gpio_chip *gc,
						    अचिन्हित पूर्णांक parent_hwirq,
						    अचिन्हित पूर्णांक parent_type)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत व्योम *gpiochip_populate_parent_fwspec_fourcell(काष्ठा gpio_chip *gc,
						     अचिन्हित पूर्णांक parent_hwirq,
						     अचिन्हित पूर्णांक parent_type)
अणु
	वापस शून्य;
पूर्ण

#पूर्ण_अगर /* CONFIG_IRQ_DOMAIN_HIERARCHY */

पूर्णांक bgpio_init(काष्ठा gpio_chip *gc, काष्ठा device *dev,
	       अचिन्हित दीर्घ sz, व्योम __iomem *dat, व्योम __iomem *set,
	       व्योम __iomem *clr, व्योम __iomem *dirout, व्योम __iomem *dirin,
	       अचिन्हित दीर्घ flags);

#घोषणा BGPIOF_BIG_ENDIAN		BIT(0)
#घोषणा BGPIOF_UNREADABLE_REG_SET	BIT(1) /* reg_set is unपढ़ोable */
#घोषणा BGPIOF_UNREADABLE_REG_सूची	BIT(2) /* reg_dir is unपढ़ोable */
#घोषणा BGPIOF_BIG_ENDIAN_BYTE_ORDER	BIT(3)
#घोषणा BGPIOF_READ_OUTPUT_REG_SET	BIT(4) /* reg_set stores output value */
#घोषणा BGPIOF_NO_OUTPUT		BIT(5) /* only input */
#घोषणा BGPIOF_NO_SET_ON_INPUT		BIT(6)

पूर्णांक gpiochip_irq_map(काष्ठा irq_करोमुख्य *d, अचिन्हित पूर्णांक irq,
		     irq_hw_number_t hwirq);
व्योम gpiochip_irq_unmap(काष्ठा irq_करोमुख्य *d, अचिन्हित पूर्णांक irq);

पूर्णांक gpiochip_irq_करोमुख्य_activate(काष्ठा irq_करोमुख्य *करोमुख्य,
				 काष्ठा irq_data *data, bool reserve);
व्योम gpiochip_irq_करोमुख्य_deactivate(काष्ठा irq_करोमुख्य *करोमुख्य,
				    काष्ठा irq_data *data);

bool gpiochip_irqchip_irq_valid(स्थिर काष्ठा gpio_chip *gc,
				अचिन्हित पूर्णांक offset);

#अगर_घोषित CONFIG_GPIOLIB_IRQCHIP
पूर्णांक gpiochip_irqchip_add_करोमुख्य(काष्ठा gpio_chip *gc,
				काष्ठा irq_करोमुख्य *करोमुख्य);
#अन्यथा
अटल अंतरभूत पूर्णांक gpiochip_irqchip_add_करोमुख्य(काष्ठा gpio_chip *gc,
					      काष्ठा irq_करोमुख्य *करोमुख्य)
अणु
	WARN_ON(1);
	वापस -EINVAL;
पूर्ण
#पूर्ण_अगर

पूर्णांक gpiochip_generic_request(काष्ठा gpio_chip *gc, अचिन्हित पूर्णांक offset);
व्योम gpiochip_generic_मुक्त(काष्ठा gpio_chip *gc, अचिन्हित पूर्णांक offset);
पूर्णांक gpiochip_generic_config(काष्ठा gpio_chip *gc, अचिन्हित पूर्णांक offset,
			    अचिन्हित दीर्घ config);

/**
 * काष्ठा gpio_pin_range - pin range controlled by a gpio chip
 * @node: list क्रम मुख्यtaining set of pin ranges, used पूर्णांकernally
 * @pctldev: pinctrl device which handles corresponding pins
 * @range: actual range of pins controlled by a gpio controller
 */
काष्ठा gpio_pin_range अणु
	काष्ठा list_head node;
	काष्ठा pinctrl_dev *pctldev;
	काष्ठा pinctrl_gpio_range range;
पूर्ण;

#अगर_घोषित CONFIG_PINCTRL

पूर्णांक gpiochip_add_pin_range(काष्ठा gpio_chip *gc, स्थिर अक्षर *pinctl_name,
			   अचिन्हित पूर्णांक gpio_offset, अचिन्हित पूर्णांक pin_offset,
			   अचिन्हित पूर्णांक npins);
पूर्णांक gpiochip_add_pingroup_range(काष्ठा gpio_chip *gc,
			काष्ठा pinctrl_dev *pctldev,
			अचिन्हित पूर्णांक gpio_offset, स्थिर अक्षर *pin_group);
व्योम gpiochip_हटाओ_pin_ranges(काष्ठा gpio_chip *gc);

#अन्यथा /* ! CONFIG_PINCTRL */

अटल अंतरभूत पूर्णांक
gpiochip_add_pin_range(काष्ठा gpio_chip *gc, स्थिर अक्षर *pinctl_name,
		       अचिन्हित पूर्णांक gpio_offset, अचिन्हित पूर्णांक pin_offset,
		       अचिन्हित पूर्णांक npins)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत पूर्णांक
gpiochip_add_pingroup_range(काष्ठा gpio_chip *gc,
			काष्ठा pinctrl_dev *pctldev,
			अचिन्हित पूर्णांक gpio_offset, स्थिर अक्षर *pin_group)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम
gpiochip_हटाओ_pin_ranges(काष्ठा gpio_chip *gc)
अणु
पूर्ण

#पूर्ण_अगर /* CONFIG_PINCTRL */

काष्ठा gpio_desc *gpiochip_request_own_desc(काष्ठा gpio_chip *gc,
					    अचिन्हित पूर्णांक hwnum,
					    स्थिर अक्षर *label,
					    क्रमागत gpio_lookup_flags lflags,
					    क्रमागत gpiod_flags dflags);
व्योम gpiochip_मुक्त_own_desc(काष्ठा gpio_desc *desc);

#अगर_घोषित CONFIG_GPIOLIB

/* lock/unlock as IRQ */
पूर्णांक gpiochip_lock_as_irq(काष्ठा gpio_chip *gc, अचिन्हित पूर्णांक offset);
व्योम gpiochip_unlock_as_irq(काष्ठा gpio_chip *gc, अचिन्हित पूर्णांक offset);


काष्ठा gpio_chip *gpiod_to_chip(स्थिर काष्ठा gpio_desc *desc);

#अन्यथा /* CONFIG_GPIOLIB */

अटल अंतरभूत काष्ठा gpio_chip *gpiod_to_chip(स्थिर काष्ठा gpio_desc *desc)
अणु
	/* GPIO can never have been requested */
	WARN_ON(1);
	वापस ERR_PTR(-ENODEV);
पूर्ण

अटल अंतरभूत पूर्णांक gpiochip_lock_as_irq(काष्ठा gpio_chip *gc,
				       अचिन्हित पूर्णांक offset)
अणु
	WARN_ON(1);
	वापस -EINVAL;
पूर्ण

अटल अंतरभूत व्योम gpiochip_unlock_as_irq(काष्ठा gpio_chip *gc,
					  अचिन्हित पूर्णांक offset)
अणु
	WARN_ON(1);
पूर्ण
#पूर्ण_अगर /* CONFIG_GPIOLIB */

#पूर्ण_अगर /* __LINUX_GPIO_DRIVER_H */
