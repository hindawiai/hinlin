<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * nvmem framework provider.
 *
 * Copyright (C) 2015 Srinivas Kandagatla <srinivas.kandagatla@linaro.org>
 * Copyright (C) 2013 Maxime Ripard <maxime.ripard@मुक्त-electrons.com>
 */

#अगर_अघोषित _LINUX_NVMEM_PROVIDER_H
#घोषणा _LINUX_NVMEM_PROVIDER_H

#समावेश <linux/err.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/gpio/consumer.h>

काष्ठा nvmem_device;
काष्ठा nvmem_cell_info;
प्रकार पूर्णांक (*nvmem_reg_पढ़ो_t)(व्योम *priv, अचिन्हित पूर्णांक offset,
				व्योम *val, माप_प्रकार bytes);
प्रकार पूर्णांक (*nvmem_reg_ग_लिखो_t)(व्योम *priv, अचिन्हित पूर्णांक offset,
				 व्योम *val, माप_प्रकार bytes);

क्रमागत nvmem_type अणु
	NVMEM_TYPE_UNKNOWN = 0,
	NVMEM_TYPE_EEPROM,
	NVMEM_TYPE_OTP,
	NVMEM_TYPE_BATTERY_BACKED,
पूर्ण;

#घोषणा NVMEM_DEVID_NONE	(-1)
#घोषणा NVMEM_DEVID_AUTO	(-2)

/**
 * काष्ठा nvmem_keepout - NVMEM रेजिस्टर keepout range.
 *
 * @start:	The first byte offset to aव्योम.
 * @end:	One beyond the last byte offset to aव्योम.
 * @value:	The byte to fill पढ़ोs with क्रम this region.
 */
काष्ठा nvmem_keepout अणु
	अचिन्हित पूर्णांक start;
	अचिन्हित पूर्णांक end;
	अचिन्हित अक्षर value;
पूर्ण;

/**
 * काष्ठा nvmem_config - NVMEM device configuration
 *
 * @dev:	Parent device.
 * @name:	Optional name.
 * @id:		Optional device ID used in full name. Ignored अगर name is शून्य.
 * @owner:	Poपूर्णांकer to exporter module. Used क्रम refcounting.
 * @cells:	Optional array of pre-defined NVMEM cells.
 * @ncells:	Number of elements in cells.
 * @keepout:	Optional array of keepout ranges (sorted ascending by start).
 * @nkeepout:	Number of elements in the keepout array.
 * @type:	Type of the nvmem storage
 * @पढ़ो_only:	Device is पढ़ो-only.
 * @root_only:	Device is accessibly to root only.
 * @no_of_node:	Device should not use the parent's of_node even if it's !शून्य.
 * @reg_पढ़ो:	Callback to पढ़ो data.
 * @reg_ग_लिखो:	Callback to ग_लिखो data.
 * @size:	Device size.
 * @word_size:	Minimum पढ़ो/ग_लिखो access granularity.
 * @stride:	Minimum पढ़ो/ग_लिखो access stride.
 * @priv:	User context passed to पढ़ो/ग_लिखो callbacks.
 * @wp-gpio:   Write protect pin
 *
 * Note: A शेष "nvmem<id>" name will be asचिन्हित to the device अगर
 * no name is specअगरied in its configuration. In such हाल "<id>" is
 * generated with ida_simple_get() and provided id field is ignored.
 *
 * Note: Specअगरying name and setting id to -1 implies a unique device
 * whose name is provided as-is (kept unaltered).
 */
काष्ठा nvmem_config अणु
	काष्ठा device		*dev;
	स्थिर अक्षर		*name;
	पूर्णांक			id;
	काष्ठा module		*owner;
	काष्ठा gpio_desc	*wp_gpio;
	स्थिर काष्ठा nvmem_cell_info	*cells;
	पूर्णांक			ncells;
	स्थिर काष्ठा nvmem_keepout *keepout;
	अचिन्हित पूर्णांक		nkeepout;
	क्रमागत nvmem_type		type;
	bool			पढ़ो_only;
	bool			root_only;
	bool			no_of_node;
	nvmem_reg_पढ़ो_t	reg_पढ़ो;
	nvmem_reg_ग_लिखो_t	reg_ग_लिखो;
	पूर्णांक	size;
	पूर्णांक	word_size;
	पूर्णांक	stride;
	व्योम	*priv;
	/* To be only used by old driver/misc/eeprom drivers */
	bool			compat;
	काष्ठा device		*base_dev;
पूर्ण;

/**
 * काष्ठा nvmem_cell_table - NVMEM cell definitions क्रम given provider
 *
 * @nvmem_name:		Provider name.
 * @cells:		Array of cell definitions.
 * @ncells:		Number of cell definitions in the array.
 * @node:		List node.
 *
 * This काष्ठाure together with related helper functions is provided क्रम users
 * that करोn't can't access the nvmem provided काष्ठाure but wish to रेजिस्टर
 * cell definitions क्रम it e.g. board files रेजिस्टरing an EEPROM device.
 */
काष्ठा nvmem_cell_table अणु
	स्थिर अक्षर		*nvmem_name;
	स्थिर काष्ठा nvmem_cell_info	*cells;
	माप_प्रकार			ncells;
	काष्ठा list_head	node;
पूर्ण;

#अगर IS_ENABLED(CONFIG_NVMEM)

काष्ठा nvmem_device *nvmem_रेजिस्टर(स्थिर काष्ठा nvmem_config *cfg);
व्योम nvmem_unरेजिस्टर(काष्ठा nvmem_device *nvmem);

काष्ठा nvmem_device *devm_nvmem_रेजिस्टर(काष्ठा device *dev,
					 स्थिर काष्ठा nvmem_config *cfg);

पूर्णांक devm_nvmem_unरेजिस्टर(काष्ठा device *dev, काष्ठा nvmem_device *nvmem);

व्योम nvmem_add_cell_table(काष्ठा nvmem_cell_table *table);
व्योम nvmem_del_cell_table(काष्ठा nvmem_cell_table *table);

#अन्यथा

अटल अंतरभूत काष्ठा nvmem_device *nvmem_रेजिस्टर(स्थिर काष्ठा nvmem_config *c)
अणु
	वापस ERR_PTR(-EOPNOTSUPP);
पूर्ण

अटल अंतरभूत व्योम nvmem_unरेजिस्टर(काष्ठा nvmem_device *nvmem) अणुपूर्ण

अटल अंतरभूत काष्ठा nvmem_device *
devm_nvmem_रेजिस्टर(काष्ठा device *dev, स्थिर काष्ठा nvmem_config *c)
अणु
	वापस nvmem_रेजिस्टर(c);
पूर्ण

अटल अंतरभूत पूर्णांक
devm_nvmem_unरेजिस्टर(काष्ठा device *dev, काष्ठा nvmem_device *nvmem)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल अंतरभूत व्योम nvmem_add_cell_table(काष्ठा nvmem_cell_table *table) अणुपूर्ण
अटल अंतरभूत व्योम nvmem_del_cell_table(काष्ठा nvmem_cell_table *table) अणुपूर्ण

#पूर्ण_अगर /* CONFIG_NVMEM */
#पूर्ण_अगर  /* अगरndef _LINUX_NVMEM_PROVIDER_H */
