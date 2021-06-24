<शैली गुरु>
/* SPDX--License-Identअगरier: GPL-2.0 */

#अगर_अघोषित __PLATFORM_EARLY__
#घोषणा __PLATFORM_EARLY__

#समावेश <linux/types.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/slab.h>

काष्ठा sh_early_platक्रमm_driver अणु
	स्थिर अक्षर *class_str;
	काष्ठा platक्रमm_driver *pdrv;
	काष्ठा list_head list;
	पूर्णांक requested_id;
	अक्षर *buffer;
	पूर्णांक bufsize;
पूर्ण;

#घोषणा EARLY_PLATFORM_ID_UNSET -2
#घोषणा EARLY_PLATFORM_ID_ERROR -3

बाह्य पूर्णांक sh_early_platक्रमm_driver_रेजिस्टर(काष्ठा sh_early_platक्रमm_driver *epdrv,
					  अक्षर *buf);
बाह्य व्योम sh_early_platक्रमm_add_devices(काष्ठा platक्रमm_device **devs, पूर्णांक num);

अटल अंतरभूत पूर्णांक is_sh_early_platक्रमm_device(काष्ठा platक्रमm_device *pdev)
अणु
	वापस !pdev->dev.driver;
पूर्ण

बाह्य व्योम sh_early_platक्रमm_driver_रेजिस्टर_all(अक्षर *class_str);
बाह्य पूर्णांक sh_early_platक्रमm_driver_probe(अक्षर *class_str,
				       पूर्णांक nr_probe, पूर्णांक user_only);

#घोषणा sh_early_platक्रमm_init(class_string, platdrv)		\
	sh_early_platक्रमm_init_buffer(class_string, platdrv, शून्य, 0)

#अगर_अघोषित MODULE
#घोषणा sh_early_platक्रमm_init_buffer(class_string, platdrv, buf, bufsiz)	\
अटल __initdata काष्ठा sh_early_platक्रमm_driver early_driver = अणु		\
	.class_str = class_string,					\
	.buffer = buf,							\
	.bufsize = bufsiz,						\
	.pdrv = platdrv,						\
	.requested_id = EARLY_PLATFORM_ID_UNSET,			\
पूर्ण;									\
अटल पूर्णांक __init sh_early_platक्रमm_driver_setup_func(अक्षर *buffer)	\
अणु									\
	वापस sh_early_platक्रमm_driver_रेजिस्टर(&early_driver, buffer);	\
पूर्ण									\
early_param(class_string, sh_early_platक्रमm_driver_setup_func)
#अन्यथा /* MODULE */
#घोषणा sh_early_platक्रमm_init_buffer(class_string, platdrv, buf, bufsiz)	\
अटल अंतरभूत अक्षर *sh_early_platक्रमm_driver_setup_func(व्योम)		\
अणु									\
	वापस bufsiz ? buf : शून्य;					\
पूर्ण
#पूर्ण_अगर /* MODULE */

#पूर्ण_अगर /* __PLATFORM_EARLY__ */
