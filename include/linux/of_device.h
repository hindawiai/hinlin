<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_OF_DEVICE_H
#घोषणा _LINUX_OF_DEVICE_H

#समावेश <linux/cpu.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/of_platक्रमm.h> /* temporary until merge */

#समावेश <linux/of.h>
#समावेश <linux/mod_devicetable.h>

काष्ठा device;

#अगर_घोषित CONFIG_OF
बाह्य स्थिर काष्ठा of_device_id *of_match_device(
	स्थिर काष्ठा of_device_id *matches, स्थिर काष्ठा device *dev);

/**
 * of_driver_match_device - Tell अगर a driver's of_match_table matches a device.
 * @drv: the device_driver काष्ठाure to test
 * @dev: the device काष्ठाure to match against
 */
अटल अंतरभूत पूर्णांक of_driver_match_device(काष्ठा device *dev,
					 स्थिर काष्ठा device_driver *drv)
अणु
	वापस of_match_device(drv->of_match_table, dev) != शून्य;
पूर्ण

बाह्य पूर्णांक of_device_add(काष्ठा platक्रमm_device *pdev);
बाह्य पूर्णांक of_device_रेजिस्टर(काष्ठा platक्रमm_device *ofdev);
बाह्य व्योम of_device_unरेजिस्टर(काष्ठा platक्रमm_device *ofdev);

बाह्य स्थिर व्योम *of_device_get_match_data(स्थिर काष्ठा device *dev);

बाह्य sमाप_प्रकार of_device_modalias(काष्ठा device *dev, अक्षर *str, sमाप_प्रकार len);
बाह्य पूर्णांक of_device_request_module(काष्ठा device *dev);

बाह्य व्योम of_device_uevent(काष्ठा device *dev, काष्ठा kobj_uevent_env *env);
बाह्य पूर्णांक of_device_uevent_modalias(काष्ठा device *dev, काष्ठा kobj_uevent_env *env);

अटल अंतरभूत काष्ठा device_node *of_cpu_device_node_get(पूर्णांक cpu)
अणु
	काष्ठा device *cpu_dev;
	cpu_dev = get_cpu_device(cpu);
	अगर (!cpu_dev)
		वापस of_get_cpu_node(cpu, शून्य);
	वापस of_node_get(cpu_dev->of_node);
पूर्ण

पूर्णांक of_dma_configure_id(काष्ठा device *dev,
		     काष्ठा device_node *np,
		     bool क्रमce_dma, स्थिर u32 *id);
अटल अंतरभूत पूर्णांक of_dma_configure(काष्ठा device *dev,
				   काष्ठा device_node *np,
				   bool क्रमce_dma)
अणु
	वापस of_dma_configure_id(dev, np, क्रमce_dma, शून्य);
पूर्ण
#अन्यथा /* CONFIG_OF */

अटल अंतरभूत पूर्णांक of_driver_match_device(काष्ठा device *dev,
					 स्थिर काष्ठा device_driver *drv)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम of_device_uevent(काष्ठा device *dev,
			काष्ठा kobj_uevent_env *env) अणु पूर्ण

अटल अंतरभूत स्थिर व्योम *of_device_get_match_data(स्थिर काष्ठा device *dev)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत पूर्णांक of_device_modalias(काष्ठा device *dev,
				     अक्षर *str, sमाप_प्रकार len)
अणु
	वापस -ENODEV;
पूर्ण

अटल अंतरभूत पूर्णांक of_device_request_module(काष्ठा device *dev)
अणु
	वापस -ENODEV;
पूर्ण

अटल अंतरभूत पूर्णांक of_device_uevent_modalias(काष्ठा device *dev,
				   काष्ठा kobj_uevent_env *env)
अणु
	वापस -ENODEV;
पूर्ण

अटल अंतरभूत स्थिर काष्ठा of_device_id *of_match_device(
		स्थिर काष्ठा of_device_id *matches, स्थिर काष्ठा device *dev)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत काष्ठा device_node *of_cpu_device_node_get(पूर्णांक cpu)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत पूर्णांक of_dma_configure_id(काष्ठा device *dev,
				   काष्ठा device_node *np,
				   bool क्रमce_dma)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत पूर्णांक of_dma_configure(काष्ठा device *dev,
				   काष्ठा device_node *np,
				   bool क्रमce_dma)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_OF */

#पूर्ण_अगर /* _LINUX_OF_DEVICE_H */
