<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * ACPI helpers क्रम GPIO API
 *
 * Copyright (C) 2012,2019 Intel Corporation
 */

#अगर_अघोषित GPIOLIB_ACPI_H
#घोषणा GPIOLIB_ACPI_H

काष्ठा acpi_device;

/**
 * काष्ठा acpi_gpio_info - ACPI GPIO specअगरic inक्रमmation
 * @adev: reference to ACPI device which consumes GPIO resource
 * @flags: GPIO initialization flags
 * @gpioपूर्णांक: अगर %true this GPIO is of type GpioInt otherwise type is GpioIo
 * @pin_config: pin bias as provided by ACPI
 * @polarity: पूर्णांकerrupt polarity as provided by ACPI
 * @triggering: triggering type as provided by ACPI
 * @debounce: debounce समयout as provided by ACPI
 * @quirks: Linux specअगरic quirks as provided by काष्ठा acpi_gpio_mapping
 */
काष्ठा acpi_gpio_info अणु
	काष्ठा acpi_device *adev;
	क्रमागत gpiod_flags flags;
	bool gpioपूर्णांक;
	पूर्णांक pin_config;
	पूर्णांक polarity;
	पूर्णांक triggering;
	अचिन्हित पूर्णांक debounce;
	अचिन्हित पूर्णांक quirks;
पूर्ण;

#अगर_घोषित CONFIG_ACPI
व्योम acpi_gpiochip_add(काष्ठा gpio_chip *chip);
व्योम acpi_gpiochip_हटाओ(काष्ठा gpio_chip *chip);

व्योम acpi_gpio_dev_init(काष्ठा gpio_chip *gc, काष्ठा gpio_device *gdev);

व्योम acpi_gpiochip_request_पूर्णांकerrupts(काष्ठा gpio_chip *chip);
व्योम acpi_gpiochip_मुक्त_पूर्णांकerrupts(काष्ठा gpio_chip *chip);

पूर्णांक acpi_gpio_update_gpiod_flags(क्रमागत gpiod_flags *flags,
				 काष्ठा acpi_gpio_info *info);
पूर्णांक acpi_gpio_update_gpiod_lookup_flags(अचिन्हित दीर्घ *lookupflags,
					काष्ठा acpi_gpio_info *info);

काष्ठा gpio_desc *acpi_find_gpio(काष्ठा device *dev,
				 स्थिर अक्षर *con_id,
				 अचिन्हित पूर्णांक idx,
				 क्रमागत gpiod_flags *dflags,
				 अचिन्हित दीर्घ *lookupflags);
काष्ठा gpio_desc *acpi_node_get_gpiod(काष्ठा fwnode_handle *fwnode,
				      स्थिर अक्षर *propname, पूर्णांक index,
				      काष्ठा acpi_gpio_info *info);

पूर्णांक acpi_gpio_count(काष्ठा device *dev, स्थिर अक्षर *con_id);
#अन्यथा
अटल अंतरभूत व्योम acpi_gpiochip_add(काष्ठा gpio_chip *chip) अणु पूर्ण
अटल अंतरभूत व्योम acpi_gpiochip_हटाओ(काष्ठा gpio_chip *chip) अणु पूर्ण

अटल अंतरभूत व्योम acpi_gpio_dev_init(काष्ठा gpio_chip *gc, काष्ठा gpio_device *gdev) अणु पूर्ण

अटल अंतरभूत व्योम
acpi_gpiochip_request_पूर्णांकerrupts(काष्ठा gpio_chip *chip) अणु पूर्ण

अटल अंतरभूत व्योम
acpi_gpiochip_मुक्त_पूर्णांकerrupts(काष्ठा gpio_chip *chip) अणु पूर्ण

अटल अंतरभूत पूर्णांक
acpi_gpio_update_gpiod_flags(क्रमागत gpiod_flags *flags, काष्ठा acpi_gpio_info *info)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत पूर्णांक
acpi_gpio_update_gpiod_lookup_flags(अचिन्हित दीर्घ *lookupflags,
				    काष्ठा acpi_gpio_info *info)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत काष्ठा gpio_desc *
acpi_find_gpio(काष्ठा device *dev, स्थिर अक्षर *con_id,
	       अचिन्हित पूर्णांक idx, क्रमागत gpiod_flags *dflags,
	       अचिन्हित दीर्घ *lookupflags)
अणु
	वापस ERR_PTR(-ENOENT);
पूर्ण
अटल अंतरभूत काष्ठा gpio_desc *
acpi_node_get_gpiod(काष्ठा fwnode_handle *fwnode, स्थिर अक्षर *propname,
		    पूर्णांक index, काष्ठा acpi_gpio_info *info)
अणु
	वापस ERR_PTR(-ENXIO);
पूर्ण
अटल अंतरभूत पूर्णांक acpi_gpio_count(काष्ठा device *dev, स्थिर अक्षर *con_id)
अणु
	वापस -ENODEV;
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* GPIOLIB_ACPI_H */
