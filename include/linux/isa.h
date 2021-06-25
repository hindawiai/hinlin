<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * ISA bus.
 */

#अगर_अघोषित __LINUX_ISA_H
#घोषणा __LINUX_ISA_H

#समावेश <linux/device.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/kernel.h>

काष्ठा isa_driver अणु
	पूर्णांक (*match)(काष्ठा device *, अचिन्हित पूर्णांक);
	पूर्णांक (*probe)(काष्ठा device *, अचिन्हित पूर्णांक);
	व्योम (*हटाओ)(काष्ठा device *, अचिन्हित पूर्णांक);
	व्योम (*shutकरोwn)(काष्ठा device *, अचिन्हित पूर्णांक);
	पूर्णांक (*suspend)(काष्ठा device *, अचिन्हित पूर्णांक, pm_message_t);
	पूर्णांक (*resume)(काष्ठा device *, अचिन्हित पूर्णांक);

	काष्ठा device_driver driver;
	काष्ठा device *devices;
पूर्ण;

#घोषणा to_isa_driver(x) container_of((x), काष्ठा isa_driver, driver)

#अगर_घोषित CONFIG_ISA_BUS_API
पूर्णांक isa_रेजिस्टर_driver(काष्ठा isa_driver *, अचिन्हित पूर्णांक);
व्योम isa_unरेजिस्टर_driver(काष्ठा isa_driver *);
#अन्यथा
अटल अंतरभूत पूर्णांक isa_रेजिस्टर_driver(काष्ठा isa_driver *d, अचिन्हित पूर्णांक i)
अणु
	वापस -ENODEV;
पूर्ण

अटल अंतरभूत व्योम isa_unरेजिस्टर_driver(काष्ठा isa_driver *d)
अणु
पूर्ण
#पूर्ण_अगर

/**
 * module_isa_driver() - Helper macro क्रम रेजिस्टरing a ISA driver
 * @__isa_driver: isa_driver काष्ठा
 * @__num_isa_dev: number of devices to रेजिस्टर
 *
 * Helper macro क्रम ISA drivers which करो not करो anything special in module
 * init/निकास. This eliminates a lot of boilerplate code. Each module may only
 * use this macro once, and calling it replaces module_init and module_निकास.
 */
#घोषणा module_isa_driver(__isa_driver, __num_isa_dev) \
अटल पूर्णांक __init __isa_driver##_init(व्योम) \
अणु \
	वापस isa_रेजिस्टर_driver(&(__isa_driver), __num_isa_dev); \
पूर्ण \
module_init(__isa_driver##_init); \
अटल व्योम __निकास __isa_driver##_निकास(व्योम) \
अणु \
	isa_unरेजिस्टर_driver(&(__isa_driver)); \
पूर्ण \
module_निकास(__isa_driver##_निकास);

/**
 * max_num_isa_dev() - Maximum possible number रेजिस्टरed of an ISA device
 * @__ida_dev_ext: ISA device address extent
 *
 * The highest base address possible क्रम an ISA device is 0x3FF; this results in
 * 1024 possible base addresses. Dividing the number of possible base addresses
 * by the address extent taken by each device results in the maximum number of
 * devices on a प्रणाली.
 */
#घोषणा max_num_isa_dev(__isa_dev_ext) (1024 / __isa_dev_ext)

#पूर्ण_अगर /* __LINUX_ISA_H */
