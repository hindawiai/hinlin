<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * nvmem framework consumer.
 *
 * Copyright (C) 2015 Srinivas Kandagatla <srinivas.kandagatla@linaro.org>
 * Copyright (C) 2013 Maxime Ripard <maxime.ripard@मुक्त-electrons.com>
 */

#अगर_अघोषित _LINUX_NVMEM_CONSUMER_H
#घोषणा _LINUX_NVMEM_CONSUMER_H

#समावेश <linux/err.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/notअगरier.h>

काष्ठा device;
काष्ठा device_node;
/* consumer cookie */
काष्ठा nvmem_cell;
काष्ठा nvmem_device;

काष्ठा nvmem_cell_info अणु
	स्थिर अक्षर		*name;
	अचिन्हित पूर्णांक		offset;
	अचिन्हित पूर्णांक		bytes;
	अचिन्हित पूर्णांक		bit_offset;
	अचिन्हित पूर्णांक		nbits;
पूर्ण;

/**
 * काष्ठा nvmem_cell_lookup - cell lookup entry
 *
 * @nvmem_name:	Name of the provider.
 * @cell_name:	Name of the nvmem cell as defined in the name field of
 *		काष्ठा nvmem_cell_info.
 * @dev_id:	Name of the consumer device that will be associated with
 *		this cell.
 * @con_id:	Connector id क्रम this cell lookup.
 */
काष्ठा nvmem_cell_lookup अणु
	स्थिर अक्षर		*nvmem_name;
	स्थिर अक्षर		*cell_name;
	स्थिर अक्षर		*dev_id;
	स्थिर अक्षर		*con_id;
	काष्ठा list_head	node;
पूर्ण;

क्रमागत अणु
	NVMEM_ADD = 1,
	NVMEM_REMOVE,
	NVMEM_CELL_ADD,
	NVMEM_CELL_REMOVE,
पूर्ण;

#अगर IS_ENABLED(CONFIG_NVMEM)

/* Cell based पूर्णांकerface */
काष्ठा nvmem_cell *nvmem_cell_get(काष्ठा device *dev, स्थिर अक्षर *id);
काष्ठा nvmem_cell *devm_nvmem_cell_get(काष्ठा device *dev, स्थिर अक्षर *id);
व्योम nvmem_cell_put(काष्ठा nvmem_cell *cell);
व्योम devm_nvmem_cell_put(काष्ठा device *dev, काष्ठा nvmem_cell *cell);
व्योम *nvmem_cell_पढ़ो(काष्ठा nvmem_cell *cell, माप_प्रकार *len);
पूर्णांक nvmem_cell_ग_लिखो(काष्ठा nvmem_cell *cell, व्योम *buf, माप_प्रकार len);
पूर्णांक nvmem_cell_पढ़ो_u8(काष्ठा device *dev, स्थिर अक्षर *cell_id, u8 *val);
पूर्णांक nvmem_cell_पढ़ो_u16(काष्ठा device *dev, स्थिर अक्षर *cell_id, u16 *val);
पूर्णांक nvmem_cell_पढ़ो_u32(काष्ठा device *dev, स्थिर अक्षर *cell_id, u32 *val);
पूर्णांक nvmem_cell_पढ़ो_u64(काष्ठा device *dev, स्थिर अक्षर *cell_id, u64 *val);
पूर्णांक nvmem_cell_पढ़ो_variable_le_u32(काष्ठा device *dev, स्थिर अक्षर *cell_id,
				    u32 *val);
पूर्णांक nvmem_cell_पढ़ो_variable_le_u64(काष्ठा device *dev, स्थिर अक्षर *cell_id,
				    u64 *val);

/* direct nvmem device पढ़ो/ग_लिखो पूर्णांकerface */
काष्ठा nvmem_device *nvmem_device_get(काष्ठा device *dev, स्थिर अक्षर *name);
काष्ठा nvmem_device *devm_nvmem_device_get(काष्ठा device *dev,
					   स्थिर अक्षर *name);
व्योम nvmem_device_put(काष्ठा nvmem_device *nvmem);
व्योम devm_nvmem_device_put(काष्ठा device *dev, काष्ठा nvmem_device *nvmem);
पूर्णांक nvmem_device_पढ़ो(काष्ठा nvmem_device *nvmem, अचिन्हित पूर्णांक offset,
		      माप_प्रकार bytes, व्योम *buf);
पूर्णांक nvmem_device_ग_लिखो(काष्ठा nvmem_device *nvmem, अचिन्हित पूर्णांक offset,
		       माप_प्रकार bytes, व्योम *buf);
sमाप_प्रकार nvmem_device_cell_पढ़ो(काष्ठा nvmem_device *nvmem,
			   काष्ठा nvmem_cell_info *info, व्योम *buf);
पूर्णांक nvmem_device_cell_ग_लिखो(काष्ठा nvmem_device *nvmem,
			    काष्ठा nvmem_cell_info *info, व्योम *buf);

स्थिर अक्षर *nvmem_dev_name(काष्ठा nvmem_device *nvmem);

व्योम nvmem_add_cell_lookups(काष्ठा nvmem_cell_lookup *entries,
			    माप_प्रकार nentries);
व्योम nvmem_del_cell_lookups(काष्ठा nvmem_cell_lookup *entries,
			    माप_प्रकार nentries);

पूर्णांक nvmem_रेजिस्टर_notअगरier(काष्ठा notअगरier_block *nb);
पूर्णांक nvmem_unरेजिस्टर_notअगरier(काष्ठा notअगरier_block *nb);

काष्ठा nvmem_device *nvmem_device_find(व्योम *data,
			पूर्णांक (*match)(काष्ठा device *dev, स्थिर व्योम *data));

#अन्यथा

अटल अंतरभूत काष्ठा nvmem_cell *nvmem_cell_get(काष्ठा device *dev,
						स्थिर अक्षर *id)
अणु
	वापस ERR_PTR(-EOPNOTSUPP);
पूर्ण

अटल अंतरभूत काष्ठा nvmem_cell *devm_nvmem_cell_get(काष्ठा device *dev,
						     स्थिर अक्षर *id)
अणु
	वापस ERR_PTR(-EOPNOTSUPP);
पूर्ण

अटल अंतरभूत व्योम devm_nvmem_cell_put(काष्ठा device *dev,
				       काष्ठा nvmem_cell *cell)
अणु

पूर्ण
अटल अंतरभूत व्योम nvmem_cell_put(काष्ठा nvmem_cell *cell)
अणु
पूर्ण

अटल अंतरभूत व्योम *nvmem_cell_पढ़ो(काष्ठा nvmem_cell *cell, माप_प्रकार *len)
अणु
	वापस ERR_PTR(-EOPNOTSUPP);
पूर्ण

अटल अंतरभूत पूर्णांक nvmem_cell_ग_लिखो(काष्ठा nvmem_cell *cell,
				   व्योम *buf, माप_प्रकार len)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल अंतरभूत पूर्णांक nvmem_cell_पढ़ो_u16(काष्ठा device *dev,
				      स्थिर अक्षर *cell_id, u16 *val)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल अंतरभूत पूर्णांक nvmem_cell_पढ़ो_u32(काष्ठा device *dev,
				      स्थिर अक्षर *cell_id, u32 *val)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल अंतरभूत पूर्णांक nvmem_cell_पढ़ो_u64(काष्ठा device *dev,
				      स्थिर अक्षर *cell_id, u64 *val)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल अंतरभूत काष्ठा nvmem_device *nvmem_device_get(काष्ठा device *dev,
						    स्थिर अक्षर *name)
अणु
	वापस ERR_PTR(-EOPNOTSUPP);
पूर्ण

अटल अंतरभूत काष्ठा nvmem_device *devm_nvmem_device_get(काष्ठा device *dev,
							 स्थिर अक्षर *name)
अणु
	वापस ERR_PTR(-EOPNOTSUPP);
पूर्ण

अटल अंतरभूत व्योम nvmem_device_put(काष्ठा nvmem_device *nvmem)
अणु
पूर्ण

अटल अंतरभूत व्योम devm_nvmem_device_put(काष्ठा device *dev,
					 काष्ठा nvmem_device *nvmem)
अणु
पूर्ण

अटल अंतरभूत sमाप_प्रकार nvmem_device_cell_पढ़ो(काष्ठा nvmem_device *nvmem,
					 काष्ठा nvmem_cell_info *info,
					 व्योम *buf)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल अंतरभूत पूर्णांक nvmem_device_cell_ग_लिखो(काष्ठा nvmem_device *nvmem,
					  काष्ठा nvmem_cell_info *info,
					  व्योम *buf)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल अंतरभूत पूर्णांक nvmem_device_पढ़ो(काष्ठा nvmem_device *nvmem,
				    अचिन्हित पूर्णांक offset, माप_प्रकार bytes,
				    व्योम *buf)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल अंतरभूत पूर्णांक nvmem_device_ग_लिखो(काष्ठा nvmem_device *nvmem,
				     अचिन्हित पूर्णांक offset, माप_प्रकार bytes,
				     व्योम *buf)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल अंतरभूत स्थिर अक्षर *nvmem_dev_name(काष्ठा nvmem_device *nvmem)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत व्योम
nvmem_add_cell_lookups(काष्ठा nvmem_cell_lookup *entries, माप_प्रकार nentries) अणुपूर्ण
अटल अंतरभूत व्योम
nvmem_del_cell_lookups(काष्ठा nvmem_cell_lookup *entries, माप_प्रकार nentries) अणुपूर्ण

अटल अंतरभूत पूर्णांक nvmem_रेजिस्टर_notअगरier(काष्ठा notअगरier_block *nb)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल अंतरभूत पूर्णांक nvmem_unरेजिस्टर_notअगरier(काष्ठा notअगरier_block *nb)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल अंतरभूत काष्ठा nvmem_device *nvmem_device_find(व्योम *data,
			पूर्णांक (*match)(काष्ठा device *dev, स्थिर व्योम *data))
अणु
	वापस शून्य;
पूर्ण

#पूर्ण_अगर /* CONFIG_NVMEM */

#अगर IS_ENABLED(CONFIG_NVMEM) && IS_ENABLED(CONFIG_OF)
काष्ठा nvmem_cell *of_nvmem_cell_get(काष्ठा device_node *np,
				     स्थिर अक्षर *id);
काष्ठा nvmem_device *of_nvmem_device_get(काष्ठा device_node *np,
					 स्थिर अक्षर *name);
#अन्यथा
अटल अंतरभूत काष्ठा nvmem_cell *of_nvmem_cell_get(काष्ठा device_node *np,
						   स्थिर अक्षर *id)
अणु
	वापस ERR_PTR(-EOPNOTSUPP);
पूर्ण

अटल अंतरभूत काष्ठा nvmem_device *of_nvmem_device_get(काष्ठा device_node *np,
						       स्थिर अक्षर *name)
अणु
	वापस ERR_PTR(-EOPNOTSUPP);
पूर्ण
#पूर्ण_अगर /* CONFIG_NVMEM && CONFIG_OF */

#पूर्ण_अगर  /* अगरndef _LINUX_NVMEM_CONSUMER_H */
