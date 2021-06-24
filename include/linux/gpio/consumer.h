<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __LINUX_GPIO_CONSUMER_H
#घोषणा __LINUX_GPIO_CONSUMER_H

#समावेश <linux/bits.h>
#समावेश <linux/bug.h>
#समावेश <linux/compiler_types.h>
#समावेश <linux/err.h>

काष्ठा device;

/**
 * Opaque descriptor क्रम a GPIO. These are obtained using gpiod_get() and are
 * preferable to the old पूर्णांकeger-based handles.
 *
 * Contrary to पूर्णांकegers, a poपूर्णांकer to a gpio_desc is guaranteed to be valid
 * until the GPIO is released.
 */
काष्ठा gpio_desc;

/**
 * Opaque descriptor क्रम a काष्ठाure of GPIO array attributes.  This काष्ठाure
 * is attached to काष्ठा gpiod_descs obtained from gpiod_get_array() and can be
 * passed back to get/set array functions in order to activate fast processing
 * path अगर applicable.
 */
काष्ठा gpio_array;

/**
 * Struct containing an array of descriptors that can be obtained using
 * gpiod_get_array().
 */
काष्ठा gpio_descs अणु
	काष्ठा gpio_array *info;
	अचिन्हित पूर्णांक ndescs;
	काष्ठा gpio_desc *desc[];
पूर्ण;

#घोषणा GPIOD_FLAGS_BIT_सूची_SET		BIT(0)
#घोषणा GPIOD_FLAGS_BIT_सूची_OUT		BIT(1)
#घोषणा GPIOD_FLAGS_BIT_सूची_VAL		BIT(2)
#घोषणा GPIOD_FLAGS_BIT_OPEN_DRAIN	BIT(3)
#घोषणा GPIOD_FLAGS_BIT_NONEXCLUSIVE	BIT(4)

/**
 * Optional flags that can be passed to one of gpiod_* to configure direction
 * and output value. These values cannot be OR'd.
 */
क्रमागत gpiod_flags अणु
	GPIOD_ASIS	= 0,
	GPIOD_IN	= GPIOD_FLAGS_BIT_सूची_SET,
	GPIOD_OUT_LOW	= GPIOD_FLAGS_BIT_सूची_SET | GPIOD_FLAGS_BIT_सूची_OUT,
	GPIOD_OUT_HIGH	= GPIOD_FLAGS_BIT_सूची_SET | GPIOD_FLAGS_BIT_सूची_OUT |
			  GPIOD_FLAGS_BIT_सूची_VAL,
	GPIOD_OUT_LOW_OPEN_DRAIN = GPIOD_OUT_LOW | GPIOD_FLAGS_BIT_OPEN_DRAIN,
	GPIOD_OUT_HIGH_OPEN_DRAIN = GPIOD_OUT_HIGH | GPIOD_FLAGS_BIT_OPEN_DRAIN,
पूर्ण;

#अगर_घोषित CONFIG_GPIOLIB

/* Return the number of GPIOs associated with a device / function */
पूर्णांक gpiod_count(काष्ठा device *dev, स्थिर अक्षर *con_id);

/* Acquire and dispose GPIOs */
काष्ठा gpio_desc *__must_check gpiod_get(काष्ठा device *dev,
					 स्थिर अक्षर *con_id,
					 क्रमागत gpiod_flags flags);
काष्ठा gpio_desc *__must_check gpiod_get_index(काष्ठा device *dev,
					       स्थिर अक्षर *con_id,
					       अचिन्हित पूर्णांक idx,
					       क्रमागत gpiod_flags flags);
काष्ठा gpio_desc *__must_check gpiod_get_optional(काष्ठा device *dev,
						  स्थिर अक्षर *con_id,
						  क्रमागत gpiod_flags flags);
काष्ठा gpio_desc *__must_check gpiod_get_index_optional(काष्ठा device *dev,
							स्थिर अक्षर *con_id,
							अचिन्हित पूर्णांक index,
							क्रमागत gpiod_flags flags);
काष्ठा gpio_descs *__must_check gpiod_get_array(काष्ठा device *dev,
						स्थिर अक्षर *con_id,
						क्रमागत gpiod_flags flags);
काष्ठा gpio_descs *__must_check gpiod_get_array_optional(काष्ठा device *dev,
							स्थिर अक्षर *con_id,
							क्रमागत gpiod_flags flags);
व्योम gpiod_put(काष्ठा gpio_desc *desc);
व्योम gpiod_put_array(काष्ठा gpio_descs *descs);

काष्ठा gpio_desc *__must_check devm_gpiod_get(काष्ठा device *dev,
					      स्थिर अक्षर *con_id,
					      क्रमागत gpiod_flags flags);
काष्ठा gpio_desc *__must_check devm_gpiod_get_index(काष्ठा device *dev,
						    स्थिर अक्षर *con_id,
						    अचिन्हित पूर्णांक idx,
						    क्रमागत gpiod_flags flags);
काष्ठा gpio_desc *__must_check devm_gpiod_get_optional(काष्ठा device *dev,
						       स्थिर अक्षर *con_id,
						       क्रमागत gpiod_flags flags);
काष्ठा gpio_desc *__must_check
devm_gpiod_get_index_optional(काष्ठा device *dev, स्थिर अक्षर *con_id,
			      अचिन्हित पूर्णांक index, क्रमागत gpiod_flags flags);
काष्ठा gpio_descs *__must_check devm_gpiod_get_array(काष्ठा device *dev,
						     स्थिर अक्षर *con_id,
						     क्रमागत gpiod_flags flags);
काष्ठा gpio_descs *__must_check
devm_gpiod_get_array_optional(काष्ठा device *dev, स्थिर अक्षर *con_id,
			      क्रमागत gpiod_flags flags);
व्योम devm_gpiod_put(काष्ठा device *dev, काष्ठा gpio_desc *desc);
व्योम devm_gpiod_unhinge(काष्ठा device *dev, काष्ठा gpio_desc *desc);
व्योम devm_gpiod_put_array(काष्ठा device *dev, काष्ठा gpio_descs *descs);

पूर्णांक gpiod_get_direction(काष्ठा gpio_desc *desc);
पूर्णांक gpiod_direction_input(काष्ठा gpio_desc *desc);
पूर्णांक gpiod_direction_output(काष्ठा gpio_desc *desc, पूर्णांक value);
पूर्णांक gpiod_direction_output_raw(काष्ठा gpio_desc *desc, पूर्णांक value);

/* Value get/set from non-sleeping context */
पूर्णांक gpiod_get_value(स्थिर काष्ठा gpio_desc *desc);
पूर्णांक gpiod_get_array_value(अचिन्हित पूर्णांक array_size,
			  काष्ठा gpio_desc **desc_array,
			  काष्ठा gpio_array *array_info,
			  अचिन्हित दीर्घ *value_biपंचांगap);
व्योम gpiod_set_value(काष्ठा gpio_desc *desc, पूर्णांक value);
पूर्णांक gpiod_set_array_value(अचिन्हित पूर्णांक array_size,
			  काष्ठा gpio_desc **desc_array,
			  काष्ठा gpio_array *array_info,
			  अचिन्हित दीर्घ *value_biपंचांगap);
पूर्णांक gpiod_get_raw_value(स्थिर काष्ठा gpio_desc *desc);
पूर्णांक gpiod_get_raw_array_value(अचिन्हित पूर्णांक array_size,
			      काष्ठा gpio_desc **desc_array,
			      काष्ठा gpio_array *array_info,
			      अचिन्हित दीर्घ *value_biपंचांगap);
व्योम gpiod_set_raw_value(काष्ठा gpio_desc *desc, पूर्णांक value);
पूर्णांक gpiod_set_raw_array_value(अचिन्हित पूर्णांक array_size,
			      काष्ठा gpio_desc **desc_array,
			      काष्ठा gpio_array *array_info,
			      अचिन्हित दीर्घ *value_biपंचांगap);

/* Value get/set from sleeping context */
पूर्णांक gpiod_get_value_cansleep(स्थिर काष्ठा gpio_desc *desc);
पूर्णांक gpiod_get_array_value_cansleep(अचिन्हित पूर्णांक array_size,
				   काष्ठा gpio_desc **desc_array,
				   काष्ठा gpio_array *array_info,
				   अचिन्हित दीर्घ *value_biपंचांगap);
व्योम gpiod_set_value_cansleep(काष्ठा gpio_desc *desc, पूर्णांक value);
पूर्णांक gpiod_set_array_value_cansleep(अचिन्हित पूर्णांक array_size,
				   काष्ठा gpio_desc **desc_array,
				   काष्ठा gpio_array *array_info,
				   अचिन्हित दीर्घ *value_biपंचांगap);
पूर्णांक gpiod_get_raw_value_cansleep(स्थिर काष्ठा gpio_desc *desc);
पूर्णांक gpiod_get_raw_array_value_cansleep(अचिन्हित पूर्णांक array_size,
				       काष्ठा gpio_desc **desc_array,
				       काष्ठा gpio_array *array_info,
				       अचिन्हित दीर्घ *value_biपंचांगap);
व्योम gpiod_set_raw_value_cansleep(काष्ठा gpio_desc *desc, पूर्णांक value);
पूर्णांक gpiod_set_raw_array_value_cansleep(अचिन्हित पूर्णांक array_size,
				       काष्ठा gpio_desc **desc_array,
				       काष्ठा gpio_array *array_info,
				       अचिन्हित दीर्घ *value_biपंचांगap);

पूर्णांक gpiod_set_config(काष्ठा gpio_desc *desc, अचिन्हित दीर्घ config);
पूर्णांक gpiod_set_debounce(काष्ठा gpio_desc *desc, अचिन्हित पूर्णांक debounce);
पूर्णांक gpiod_set_transitory(काष्ठा gpio_desc *desc, bool transitory);
व्योम gpiod_toggle_active_low(काष्ठा gpio_desc *desc);

पूर्णांक gpiod_is_active_low(स्थिर काष्ठा gpio_desc *desc);
पूर्णांक gpiod_cansleep(स्थिर काष्ठा gpio_desc *desc);

पूर्णांक gpiod_to_irq(स्थिर काष्ठा gpio_desc *desc);
पूर्णांक gpiod_set_consumer_name(काष्ठा gpio_desc *desc, स्थिर अक्षर *name);

/* Convert between the old gpio_ and new gpiod_ पूर्णांकerfaces */
काष्ठा gpio_desc *gpio_to_desc(अचिन्हित gpio);
पूर्णांक desc_to_gpio(स्थिर काष्ठा gpio_desc *desc);

/* Child properties पूर्णांकerface */
काष्ठा fwnode_handle;

काष्ठा gpio_desc *fwnode_get_named_gpiod(काष्ठा fwnode_handle *fwnode,
					 स्थिर अक्षर *propname, पूर्णांक index,
					 क्रमागत gpiod_flags dflags,
					 स्थिर अक्षर *label);
काष्ठा gpio_desc *fwnode_gpiod_get_index(काष्ठा fwnode_handle *fwnode,
					 स्थिर अक्षर *con_id, पूर्णांक index,
					 क्रमागत gpiod_flags flags,
					 स्थिर अक्षर *label);
काष्ठा gpio_desc *devm_fwnode_gpiod_get_index(काष्ठा device *dev,
					      काष्ठा fwnode_handle *child,
					      स्थिर अक्षर *con_id, पूर्णांक index,
					      क्रमागत gpiod_flags flags,
					      स्थिर अक्षर *label);

#अन्यथा /* CONFIG_GPIOLIB */

#समावेश <linux/kernel.h>

अटल अंतरभूत पूर्णांक gpiod_count(काष्ठा device *dev, स्थिर अक्षर *con_id)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत काष्ठा gpio_desc *__must_check gpiod_get(काष्ठा device *dev,
						       स्थिर अक्षर *con_id,
						       क्रमागत gpiod_flags flags)
अणु
	वापस ERR_PTR(-ENOSYS);
पूर्ण
अटल अंतरभूत काष्ठा gpio_desc *__must_check
gpiod_get_index(काष्ठा device *dev,
		स्थिर अक्षर *con_id,
		अचिन्हित पूर्णांक idx,
		क्रमागत gpiod_flags flags)
अणु
	वापस ERR_PTR(-ENOSYS);
पूर्ण

अटल अंतरभूत काष्ठा gpio_desc *__must_check
gpiod_get_optional(काष्ठा device *dev, स्थिर अक्षर *con_id,
		   क्रमागत gpiod_flags flags)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत काष्ठा gpio_desc *__must_check
gpiod_get_index_optional(काष्ठा device *dev, स्थिर अक्षर *con_id,
			 अचिन्हित पूर्णांक index, क्रमागत gpiod_flags flags)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत काष्ठा gpio_descs *__must_check
gpiod_get_array(काष्ठा device *dev, स्थिर अक्षर *con_id,
		क्रमागत gpiod_flags flags)
अणु
	वापस ERR_PTR(-ENOSYS);
पूर्ण

अटल अंतरभूत काष्ठा gpio_descs *__must_check
gpiod_get_array_optional(काष्ठा device *dev, स्थिर अक्षर *con_id,
			 क्रमागत gpiod_flags flags)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत व्योम gpiod_put(काष्ठा gpio_desc *desc)
अणु
	might_sleep();

	/* GPIO can never have been requested */
	WARN_ON(desc);
पूर्ण

अटल अंतरभूत व्योम devm_gpiod_unhinge(काष्ठा device *dev,
				      काष्ठा gpio_desc *desc)
अणु
	might_sleep();

	/* GPIO can never have been requested */
	WARN_ON(desc);
पूर्ण

अटल अंतरभूत व्योम gpiod_put_array(काष्ठा gpio_descs *descs)
अणु
	might_sleep();

	/* GPIO can never have been requested */
	WARN_ON(descs);
पूर्ण

अटल अंतरभूत काष्ठा gpio_desc *__must_check
devm_gpiod_get(काष्ठा device *dev,
		 स्थिर अक्षर *con_id,
		 क्रमागत gpiod_flags flags)
अणु
	वापस ERR_PTR(-ENOSYS);
पूर्ण
अटल अंतरभूत
काष्ठा gpio_desc *__must_check
devm_gpiod_get_index(काष्ठा device *dev,
		       स्थिर अक्षर *con_id,
		       अचिन्हित पूर्णांक idx,
		       क्रमागत gpiod_flags flags)
अणु
	वापस ERR_PTR(-ENOSYS);
पूर्ण

अटल अंतरभूत काष्ठा gpio_desc *__must_check
devm_gpiod_get_optional(काष्ठा device *dev, स्थिर अक्षर *con_id,
			  क्रमागत gpiod_flags flags)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत काष्ठा gpio_desc *__must_check
devm_gpiod_get_index_optional(काष्ठा device *dev, स्थिर अक्षर *con_id,
				अचिन्हित पूर्णांक index, क्रमागत gpiod_flags flags)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत काष्ठा gpio_descs *__must_check
devm_gpiod_get_array(काष्ठा device *dev, स्थिर अक्षर *con_id,
		     क्रमागत gpiod_flags flags)
अणु
	वापस ERR_PTR(-ENOSYS);
पूर्ण

अटल अंतरभूत काष्ठा gpio_descs *__must_check
devm_gpiod_get_array_optional(काष्ठा device *dev, स्थिर अक्षर *con_id,
			      क्रमागत gpiod_flags flags)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत व्योम devm_gpiod_put(काष्ठा device *dev, काष्ठा gpio_desc *desc)
अणु
	might_sleep();

	/* GPIO can never have been requested */
	WARN_ON(desc);
पूर्ण

अटल अंतरभूत व्योम devm_gpiod_put_array(काष्ठा device *dev,
					काष्ठा gpio_descs *descs)
अणु
	might_sleep();

	/* GPIO can never have been requested */
	WARN_ON(descs);
पूर्ण


अटल अंतरभूत पूर्णांक gpiod_get_direction(स्थिर काष्ठा gpio_desc *desc)
अणु
	/* GPIO can never have been requested */
	WARN_ON(desc);
	वापस -ENOSYS;
पूर्ण
अटल अंतरभूत पूर्णांक gpiod_direction_input(काष्ठा gpio_desc *desc)
अणु
	/* GPIO can never have been requested */
	WARN_ON(desc);
	वापस -ENOSYS;
पूर्ण
अटल अंतरभूत पूर्णांक gpiod_direction_output(काष्ठा gpio_desc *desc, पूर्णांक value)
अणु
	/* GPIO can never have been requested */
	WARN_ON(desc);
	वापस -ENOSYS;
पूर्ण
अटल अंतरभूत पूर्णांक gpiod_direction_output_raw(काष्ठा gpio_desc *desc, पूर्णांक value)
अणु
	/* GPIO can never have been requested */
	WARN_ON(desc);
	वापस -ENOSYS;
पूर्ण


अटल अंतरभूत पूर्णांक gpiod_get_value(स्थिर काष्ठा gpio_desc *desc)
अणु
	/* GPIO can never have been requested */
	WARN_ON(desc);
	वापस 0;
पूर्ण
अटल अंतरभूत पूर्णांक gpiod_get_array_value(अचिन्हित पूर्णांक array_size,
					काष्ठा gpio_desc **desc_array,
					काष्ठा gpio_array *array_info,
					अचिन्हित दीर्घ *value_biपंचांगap)
अणु
	/* GPIO can never have been requested */
	WARN_ON(desc_array);
	वापस 0;
पूर्ण
अटल अंतरभूत व्योम gpiod_set_value(काष्ठा gpio_desc *desc, पूर्णांक value)
अणु
	/* GPIO can never have been requested */
	WARN_ON(desc);
पूर्ण
अटल अंतरभूत पूर्णांक gpiod_set_array_value(अचिन्हित पूर्णांक array_size,
					काष्ठा gpio_desc **desc_array,
					काष्ठा gpio_array *array_info,
					अचिन्हित दीर्घ *value_biपंचांगap)
अणु
	/* GPIO can never have been requested */
	WARN_ON(desc_array);
	वापस 0;
पूर्ण
अटल अंतरभूत पूर्णांक gpiod_get_raw_value(स्थिर काष्ठा gpio_desc *desc)
अणु
	/* GPIO can never have been requested */
	WARN_ON(desc);
	वापस 0;
पूर्ण
अटल अंतरभूत पूर्णांक gpiod_get_raw_array_value(अचिन्हित पूर्णांक array_size,
					    काष्ठा gpio_desc **desc_array,
					    काष्ठा gpio_array *array_info,
					    अचिन्हित दीर्घ *value_biपंचांगap)
अणु
	/* GPIO can never have been requested */
	WARN_ON(desc_array);
	वापस 0;
पूर्ण
अटल अंतरभूत व्योम gpiod_set_raw_value(काष्ठा gpio_desc *desc, पूर्णांक value)
अणु
	/* GPIO can never have been requested */
	WARN_ON(desc);
पूर्ण
अटल अंतरभूत पूर्णांक gpiod_set_raw_array_value(अचिन्हित पूर्णांक array_size,
					    काष्ठा gpio_desc **desc_array,
					    काष्ठा gpio_array *array_info,
					    अचिन्हित दीर्घ *value_biपंचांगap)
अणु
	/* GPIO can never have been requested */
	WARN_ON(desc_array);
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक gpiod_get_value_cansleep(स्थिर काष्ठा gpio_desc *desc)
अणु
	/* GPIO can never have been requested */
	WARN_ON(desc);
	वापस 0;
पूर्ण
अटल अंतरभूत पूर्णांक gpiod_get_array_value_cansleep(अचिन्हित पूर्णांक array_size,
				     काष्ठा gpio_desc **desc_array,
				     काष्ठा gpio_array *array_info,
				     अचिन्हित दीर्घ *value_biपंचांगap)
अणु
	/* GPIO can never have been requested */
	WARN_ON(desc_array);
	वापस 0;
पूर्ण
अटल अंतरभूत व्योम gpiod_set_value_cansleep(काष्ठा gpio_desc *desc, पूर्णांक value)
अणु
	/* GPIO can never have been requested */
	WARN_ON(desc);
पूर्ण
अटल अंतरभूत पूर्णांक gpiod_set_array_value_cansleep(अचिन्हित पूर्णांक array_size,
					    काष्ठा gpio_desc **desc_array,
					    काष्ठा gpio_array *array_info,
					    अचिन्हित दीर्घ *value_biपंचांगap)
अणु
	/* GPIO can never have been requested */
	WARN_ON(desc_array);
	वापस 0;
पूर्ण
अटल अंतरभूत पूर्णांक gpiod_get_raw_value_cansleep(स्थिर काष्ठा gpio_desc *desc)
अणु
	/* GPIO can never have been requested */
	WARN_ON(desc);
	वापस 0;
पूर्ण
अटल अंतरभूत पूर्णांक gpiod_get_raw_array_value_cansleep(अचिन्हित पूर्णांक array_size,
					       काष्ठा gpio_desc **desc_array,
					       काष्ठा gpio_array *array_info,
					       अचिन्हित दीर्घ *value_biपंचांगap)
अणु
	/* GPIO can never have been requested */
	WARN_ON(desc_array);
	वापस 0;
पूर्ण
अटल अंतरभूत व्योम gpiod_set_raw_value_cansleep(काष्ठा gpio_desc *desc,
						पूर्णांक value)
अणु
	/* GPIO can never have been requested */
	WARN_ON(desc);
पूर्ण
अटल अंतरभूत पूर्णांक gpiod_set_raw_array_value_cansleep(अचिन्हित पूर्णांक array_size,
						काष्ठा gpio_desc **desc_array,
						काष्ठा gpio_array *array_info,
						अचिन्हित दीर्घ *value_biपंचांगap)
अणु
	/* GPIO can never have been requested */
	WARN_ON(desc_array);
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक gpiod_set_config(काष्ठा gpio_desc *desc, अचिन्हित दीर्घ config)
अणु
	/* GPIO can never have been requested */
	WARN_ON(desc);
	वापस -ENOSYS;
पूर्ण

अटल अंतरभूत पूर्णांक gpiod_set_debounce(काष्ठा gpio_desc *desc, अचिन्हित पूर्णांक debounce)
अणु
	/* GPIO can never have been requested */
	WARN_ON(desc);
	वापस -ENOSYS;
पूर्ण

अटल अंतरभूत पूर्णांक gpiod_set_transitory(काष्ठा gpio_desc *desc, bool transitory)
अणु
	/* GPIO can never have been requested */
	WARN_ON(desc);
	वापस -ENOSYS;
पूर्ण

अटल अंतरभूत व्योम gpiod_toggle_active_low(काष्ठा gpio_desc *desc)
अणु
	/* GPIO can never have been requested */
	WARN_ON(desc);
पूर्ण

अटल अंतरभूत पूर्णांक gpiod_is_active_low(स्थिर काष्ठा gpio_desc *desc)
अणु
	/* GPIO can never have been requested */
	WARN_ON(desc);
	वापस 0;
पूर्ण
अटल अंतरभूत पूर्णांक gpiod_cansleep(स्थिर काष्ठा gpio_desc *desc)
अणु
	/* GPIO can never have been requested */
	WARN_ON(desc);
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक gpiod_to_irq(स्थिर काष्ठा gpio_desc *desc)
अणु
	/* GPIO can never have been requested */
	WARN_ON(desc);
	वापस -EINVAL;
पूर्ण

अटल अंतरभूत पूर्णांक gpiod_set_consumer_name(काष्ठा gpio_desc *desc,
					  स्थिर अक्षर *name)
अणु
	/* GPIO can never have been requested */
	WARN_ON(desc);
	वापस -EINVAL;
पूर्ण

अटल अंतरभूत काष्ठा gpio_desc *gpio_to_desc(अचिन्हित gpio)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत पूर्णांक desc_to_gpio(स्थिर काष्ठा gpio_desc *desc)
अणु
	/* GPIO can never have been requested */
	WARN_ON(desc);
	वापस -EINVAL;
पूर्ण

/* Child properties पूर्णांकerface */
काष्ठा fwnode_handle;

अटल अंतरभूत
काष्ठा gpio_desc *fwnode_get_named_gpiod(काष्ठा fwnode_handle *fwnode,
					 स्थिर अक्षर *propname, पूर्णांक index,
					 क्रमागत gpiod_flags dflags,
					 स्थिर अक्षर *label)
अणु
	वापस ERR_PTR(-ENOSYS);
पूर्ण

अटल अंतरभूत
काष्ठा gpio_desc *fwnode_gpiod_get_index(काष्ठा fwnode_handle *fwnode,
					 स्थिर अक्षर *con_id, पूर्णांक index,
					 क्रमागत gpiod_flags flags,
					 स्थिर अक्षर *label)
अणु
	वापस ERR_PTR(-ENOSYS);
पूर्ण

अटल अंतरभूत
काष्ठा gpio_desc *devm_fwnode_gpiod_get_index(काष्ठा device *dev,
					      काष्ठा fwnode_handle *fwnode,
					      स्थिर अक्षर *con_id, पूर्णांक index,
					      क्रमागत gpiod_flags flags,
					      स्थिर अक्षर *label)
अणु
	वापस ERR_PTR(-ENOSYS);
पूर्ण

#पूर्ण_अगर /* CONFIG_GPIOLIB */

अटल अंतरभूत
काष्ठा gpio_desc *devm_fwnode_gpiod_get(काष्ठा device *dev,
					काष्ठा fwnode_handle *fwnode,
					स्थिर अक्षर *con_id,
					क्रमागत gpiod_flags flags,
					स्थिर अक्षर *label)
अणु
	वापस devm_fwnode_gpiod_get_index(dev, fwnode, con_id, 0,
					   flags, label);
पूर्ण

अटल अंतरभूत
काष्ठा gpio_desc *devm_fwnode_get_index_gpiod_from_child(काष्ठा device *dev,
						स्थिर अक्षर *con_id, पूर्णांक index,
						काष्ठा fwnode_handle *child,
						क्रमागत gpiod_flags flags,
						स्थिर अक्षर *label)
अणु
	वापस devm_fwnode_gpiod_get_index(dev, child, con_id, index,
					   flags, label);
पूर्ण

अटल अंतरभूत
काष्ठा gpio_desc *devm_fwnode_get_gpiod_from_child(काष्ठा device *dev,
						   स्थिर अक्षर *con_id,
						   काष्ठा fwnode_handle *child,
						   क्रमागत gpiod_flags flags,
						   स्थिर अक्षर *label)
अणु
	वापस devm_fwnode_gpiod_get_index(dev, child, con_id, 0, flags, label);
पूर्ण

#अगर IS_ENABLED(CONFIG_GPIOLIB) && IS_ENABLED(CONFIG_OF_GPIO)
काष्ठा device_node;

काष्ठा gpio_desc *gpiod_get_from_of_node(काष्ठा device_node *node,
					 स्थिर अक्षर *propname, पूर्णांक index,
					 क्रमागत gpiod_flags dflags,
					 स्थिर अक्षर *label);

#अन्यथा  /* CONFIG_GPIOLIB && CONFIG_OF_GPIO */

काष्ठा device_node;

अटल अंतरभूत
काष्ठा gpio_desc *gpiod_get_from_of_node(काष्ठा device_node *node,
					 स्थिर अक्षर *propname, पूर्णांक index,
					 क्रमागत gpiod_flags dflags,
					 स्थिर अक्षर *label)
अणु
	वापस ERR_PTR(-ENOSYS);
पूर्ण

#पूर्ण_अगर /* CONFIG_GPIOLIB && CONFIG_OF_GPIO */

#अगर_घोषित CONFIG_GPIOLIB
काष्ठा device_node;

काष्ठा gpio_desc *devm_gpiod_get_from_of_node(काष्ठा device *dev,
					      काष्ठा device_node *node,
					      स्थिर अक्षर *propname, पूर्णांक index,
					      क्रमागत gpiod_flags dflags,
					      स्थिर अक्षर *label);

#अन्यथा  /* CONFIG_GPIOLIB */

काष्ठा device_node;

अटल अंतरभूत
काष्ठा gpio_desc *devm_gpiod_get_from_of_node(काष्ठा device *dev,
					      काष्ठा device_node *node,
					      स्थिर अक्षर *propname, पूर्णांक index,
					      क्रमागत gpiod_flags dflags,
					      स्थिर अक्षर *label)
अणु
	वापस ERR_PTR(-ENOSYS);
पूर्ण

#पूर्ण_अगर /* CONFIG_GPIOLIB */

काष्ठा acpi_gpio_params अणु
	अचिन्हित पूर्णांक crs_entry_index;
	अचिन्हित पूर्णांक line_index;
	bool active_low;
पूर्ण;

काष्ठा acpi_gpio_mapping अणु
	स्थिर अक्षर *name;
	स्थिर काष्ठा acpi_gpio_params *data;
	अचिन्हित पूर्णांक size;

/* Ignore IoRestriction field */
#घोषणा ACPI_GPIO_QUIRK_NO_IO_RESTRICTION	BIT(0)
/*
 * When ACPI GPIO mapping table is in use the index parameter inside it
 * refers to the GPIO resource in _CRS method. That index has no
 * distinction of actual type of the resource. When consumer wants to
 * get GpioIo type explicitly, this quirk may be used.
 */
#घोषणा ACPI_GPIO_QUIRK_ONLY_GPIOIO		BIT(1)
/* Use given pin as an असलolute GPIO number in the प्रणाली */
#घोषणा ACPI_GPIO_QUIRK_ABSOLUTE_NUMBER		BIT(2)

	अचिन्हित पूर्णांक quirks;
पूर्ण;

#अगर IS_ENABLED(CONFIG_GPIOLIB) && IS_ENABLED(CONFIG_ACPI)

काष्ठा acpi_device;

पूर्णांक acpi_dev_add_driver_gpios(काष्ठा acpi_device *adev,
			      स्थिर काष्ठा acpi_gpio_mapping *gpios);
व्योम acpi_dev_हटाओ_driver_gpios(काष्ठा acpi_device *adev);

पूर्णांक devm_acpi_dev_add_driver_gpios(काष्ठा device *dev,
				   स्थिर काष्ठा acpi_gpio_mapping *gpios);
व्योम devm_acpi_dev_हटाओ_driver_gpios(काष्ठा device *dev);

#अन्यथा  /* CONFIG_GPIOLIB && CONFIG_ACPI */

काष्ठा acpi_device;

अटल अंतरभूत पूर्णांक acpi_dev_add_driver_gpios(काष्ठा acpi_device *adev,
			      स्थिर काष्ठा acpi_gpio_mapping *gpios)
अणु
	वापस -ENXIO;
पूर्ण
अटल अंतरभूत व्योम acpi_dev_हटाओ_driver_gpios(काष्ठा acpi_device *adev) अणुपूर्ण

अटल अंतरभूत पूर्णांक devm_acpi_dev_add_driver_gpios(काष्ठा device *dev,
			      स्थिर काष्ठा acpi_gpio_mapping *gpios)
अणु
	वापस -ENXIO;
पूर्ण
अटल अंतरभूत व्योम devm_acpi_dev_हटाओ_driver_gpios(काष्ठा device *dev) अणुपूर्ण

#पूर्ण_अगर /* CONFIG_GPIOLIB && CONFIG_ACPI */


#अगर IS_ENABLED(CONFIG_GPIOLIB) && IS_ENABLED(CONFIG_GPIO_SYSFS)

पूर्णांक gpiod_export(काष्ठा gpio_desc *desc, bool direction_may_change);
पूर्णांक gpiod_export_link(काष्ठा device *dev, स्थिर अक्षर *name,
		      काष्ठा gpio_desc *desc);
व्योम gpiod_unexport(काष्ठा gpio_desc *desc);

#अन्यथा  /* CONFIG_GPIOLIB && CONFIG_GPIO_SYSFS */

अटल अंतरभूत पूर्णांक gpiod_export(काष्ठा gpio_desc *desc,
			       bool direction_may_change)
अणु
	वापस -ENOSYS;
पूर्ण

अटल अंतरभूत पूर्णांक gpiod_export_link(काष्ठा device *dev, स्थिर अक्षर *name,
				    काष्ठा gpio_desc *desc)
अणु
	वापस -ENOSYS;
पूर्ण

अटल अंतरभूत व्योम gpiod_unexport(काष्ठा gpio_desc *desc)
अणु
पूर्ण

#पूर्ण_अगर /* CONFIG_GPIOLIB && CONFIG_GPIO_SYSFS */

#पूर्ण_अगर
