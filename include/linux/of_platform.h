<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
#अगर_अघोषित _LINUX_OF_PLATFORM_H
#घोषणा _LINUX_OF_PLATFORM_H
/*
 *    Copyright (C) 2006 Benjamin Herrenschmidt, IBM Corp.
 *			 <benh@kernel.crashing.org>
 */

#समावेश <linux/device.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/pm.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>

/**
 * काष्ठा of_dev_auxdata - lookup table entry क्रम device names & platक्रमm_data
 * @compatible: compatible value of node to match against node
 * @phys_addr: Start address of रेजिस्टरs to match against node
 * @name: Name to assign क्रम matching nodes
 * @platक्रमm_data: platक्रमm_data to assign क्रम matching nodes
 *
 * This lookup table allows the caller of of_platक्रमm_populate() to override
 * the names of devices when creating devices from the device tree.  The table
 * should be terminated with an empty entry.  It also allows the platक्रमm_data
 * poपूर्णांकer to be set.
 *
 * The reason क्रम this functionality is that some Linux infraकाष्ठाure uses
 * the device name to look up a specअगरic device, but the Linux-specअगरic names
 * are not encoded पूर्णांकo the device tree, so the kernel needs to provide specअगरic
 * values.
 *
 * Note: Using an auxdata lookup table should be considered a last resort when
 * converting a platक्रमm to use the DT.  Normally the स्वतःmatically generated
 * device name will not matter, and drivers should obtain data from the device
 * node instead of from an anonymous platक्रमm_data poपूर्णांकer.
 */
काष्ठा of_dev_auxdata अणु
	अक्षर *compatible;
	resource_माप_प्रकार phys_addr;
	अक्षर *name;
	व्योम *platक्रमm_data;
पूर्ण;

/* Macro to simplअगरy populating a lookup table */
#घोषणा OF_DEV_AUXDATA(_compat,_phys,_name,_pdata) \
	अणु .compatible = _compat, .phys_addr = _phys, .name = _name, \
	  .platक्रमm_data = _pdata पूर्ण

बाह्य स्थिर काष्ठा of_device_id of_शेष_bus_match_table[];

/* Platक्रमm drivers रेजिस्टर/unरेजिस्टर */
बाह्य काष्ठा platक्रमm_device *of_device_alloc(काष्ठा device_node *np,
					 स्थिर अक्षर *bus_id,
					 काष्ठा device *parent);
#अगर_घोषित CONFIG_OF
बाह्य काष्ठा platक्रमm_device *of_find_device_by_node(काष्ठा device_node *np);
#अन्यथा
अटल अंतरभूत काष्ठा platक्रमm_device *of_find_device_by_node(काष्ठा device_node *np)
अणु
	वापस शून्य;
पूर्ण
#पूर्ण_अगर

/* Platक्रमm devices and busses creation */
बाह्य काष्ठा platक्रमm_device *of_platक्रमm_device_create(काष्ठा device_node *np,
						   स्थिर अक्षर *bus_id,
						   काष्ठा device *parent);

बाह्य पूर्णांक of_platक्रमm_device_destroy(काष्ठा device *dev, व्योम *data);
बाह्य पूर्णांक of_platक्रमm_bus_probe(काष्ठा device_node *root,
				 स्थिर काष्ठा of_device_id *matches,
				 काष्ठा device *parent);
#अगर_घोषित CONFIG_OF_ADDRESS
बाह्य पूर्णांक of_platक्रमm_populate(काष्ठा device_node *root,
				स्थिर काष्ठा of_device_id *matches,
				स्थिर काष्ठा of_dev_auxdata *lookup,
				काष्ठा device *parent);
बाह्य पूर्णांक of_platक्रमm_शेष_populate(काष्ठा device_node *root,
					स्थिर काष्ठा of_dev_auxdata *lookup,
					काष्ठा device *parent);
बाह्य व्योम of_platक्रमm_depopulate(काष्ठा device *parent);

बाह्य पूर्णांक devm_of_platक्रमm_populate(काष्ठा device *dev);

बाह्य व्योम devm_of_platक्रमm_depopulate(काष्ठा device *dev);
#अन्यथा
अटल अंतरभूत पूर्णांक of_platक्रमm_populate(काष्ठा device_node *root,
					स्थिर काष्ठा of_device_id *matches,
					स्थिर काष्ठा of_dev_auxdata *lookup,
					काष्ठा device *parent)
अणु
	वापस -ENODEV;
पूर्ण
अटल अंतरभूत पूर्णांक of_platक्रमm_शेष_populate(काष्ठा device_node *root,
					       स्थिर काष्ठा of_dev_auxdata *lookup,
					       काष्ठा device *parent)
अणु
	वापस -ENODEV;
पूर्ण
अटल अंतरभूत व्योम of_platक्रमm_depopulate(काष्ठा device *parent) अणु पूर्ण

अटल अंतरभूत पूर्णांक devm_of_platक्रमm_populate(काष्ठा device *dev)
अणु
	वापस -ENODEV;
पूर्ण

अटल अंतरभूत व्योम devm_of_platक्रमm_depopulate(काष्ठा device *dev) अणु पूर्ण
#पूर्ण_अगर

#अगर defined(CONFIG_OF_DYNAMIC) && defined(CONFIG_OF_ADDRESS)
बाह्य व्योम of_platक्रमm_रेजिस्टर_reconfig_notअगरier(व्योम);
#अन्यथा
अटल अंतरभूत व्योम of_platक्रमm_रेजिस्टर_reconfig_notअगरier(व्योम) अणु पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर	/* _LINUX_OF_PLATFORM_H */
