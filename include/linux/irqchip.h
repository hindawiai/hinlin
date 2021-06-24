<शैली गुरु>
/*
 * Copyright (C) 2012 Thomas Petazzoni
 *
 * Thomas Petazzoni <thomas.petazzoni@मुक्त-electrons.com>
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2.  This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */

#अगर_अघोषित _LINUX_IRQCHIP_H
#घोषणा _LINUX_IRQCHIP_H

#समावेश <linux/acpi.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>

/*
 * This macro must be used by the dअगरferent irqchip drivers to declare
 * the association between their DT compatible string and their
 * initialization function.
 *
 * @name: name that must be unique across all IRQCHIP_DECLARE of the
 * same file.
 * @compstr: compatible string of the irqchip driver
 * @fn: initialization function
 */
#घोषणा IRQCHIP_DECLARE(name, compat, fn) OF_DECLARE_2(irqchip, name, compat, fn)

बाह्य पूर्णांक platक्रमm_irqchip_probe(काष्ठा platक्रमm_device *pdev);

#घोषणा IRQCHIP_PLATFORM_DRIVER_BEGIN(drv_name) \
अटल स्थिर काष्ठा of_device_id drv_name##_irqchip_match_table[] = अणु

#घोषणा IRQCHIP_MATCH(compat, fn) अणु .compatible = compat, .data = fn पूर्ण,

#घोषणा IRQCHIP_PLATFORM_DRIVER_END(drv_name)				\
	अणुपूर्ण,								\
पूर्ण;									\
MODULE_DEVICE_TABLE(of, drv_name##_irqchip_match_table);		\
अटल काष्ठा platक्रमm_driver drv_name##_driver = अणु		\
	.probe  = platक्रमm_irqchip_probe,				\
	.driver = अणु							\
		.name = #drv_name,					\
		.owner = THIS_MODULE,					\
		.of_match_table = drv_name##_irqchip_match_table,	\
		.suppress_bind_attrs = true,				\
	पूर्ण,								\
पूर्ण;									\
builtin_platक्रमm_driver(drv_name##_driver)

/*
 * This macro must be used by the dअगरferent irqchip drivers to declare
 * the association between their version and their initialization function.
 *
 * @name: name that must be unique across all IRQCHIP_ACPI_DECLARE of the
 * same file.
 * @subtable: Subtable to be identअगरied in MADT
 * @validate: Function to be called on that subtable to check its validity.
 *            Can be शून्य.
 * @data: data to be checked by the validate function.
 * @fn: initialization function
 */
#घोषणा IRQCHIP_ACPI_DECLARE(name, subtable, validate, data, fn)	\
	ACPI_DECLARE_SUBTABLE_PROBE_ENTRY(irqchip, name,		\
					  ACPI_SIG_MADT, subtable,	\
					  validate, data, fn)

#अगर_घोषित CONFIG_IRQCHIP
व्योम irqchip_init(व्योम);
#अन्यथा
अटल अंतरभूत व्योम irqchip_init(व्योम) अणुपूर्ण
#पूर्ण_अगर

#पूर्ण_अगर
