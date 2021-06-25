<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __QCOM_MDT_LOADER_H__
#घोषणा __QCOM_MDT_LOADER_H__

#समावेश <linux/types.h>

#घोषणा QCOM_MDT_TYPE_MASK	(7 << 24)
#घोषणा QCOM_MDT_TYPE_HASH	(2 << 24)
#घोषणा QCOM_MDT_RELOCATABLE	BIT(27)

काष्ठा device;
काष्ठा firmware;

#अगर IS_ENABLED(CONFIG_QCOM_MDT_LOADER)

sमाप_प्रकार qcom_mdt_get_size(स्थिर काष्ठा firmware *fw);
पूर्णांक qcom_mdt_load(काष्ठा device *dev, स्थिर काष्ठा firmware *fw,
		  स्थिर अक्षर *fw_name, पूर्णांक pas_id, व्योम *mem_region,
		  phys_addr_t mem_phys, माप_प्रकार mem_size,
		  phys_addr_t *reloc_base);

पूर्णांक qcom_mdt_load_no_init(काष्ठा device *dev, स्थिर काष्ठा firmware *fw,
			  स्थिर अक्षर *fw_name, पूर्णांक pas_id, व्योम *mem_region,
			  phys_addr_t mem_phys, माप_प्रकार mem_size,
			  phys_addr_t *reloc_base);
व्योम *qcom_mdt_पढ़ो_metadata(स्थिर काष्ठा firmware *fw, माप_प्रकार *data_len);

#अन्यथा /* !IS_ENABLED(CONFIG_QCOM_MDT_LOADER) */

अटल अंतरभूत sमाप_प्रकार qcom_mdt_get_size(स्थिर काष्ठा firmware *fw)
अणु
	वापस -ENODEV;
पूर्ण

अटल अंतरभूत पूर्णांक qcom_mdt_load(काष्ठा device *dev, स्थिर काष्ठा firmware *fw,
				स्थिर अक्षर *fw_name, पूर्णांक pas_id,
				व्योम *mem_region, phys_addr_t mem_phys,
				माप_प्रकार mem_size, phys_addr_t *reloc_base)
अणु
	वापस -ENODEV;
पूर्ण

अटल अंतरभूत पूर्णांक qcom_mdt_load_no_init(काष्ठा device *dev,
					स्थिर काष्ठा firmware *fw,
					स्थिर अक्षर *fw_name, पूर्णांक pas_id,
					व्योम *mem_region, phys_addr_t mem_phys,
					माप_प्रकार mem_size,
					phys_addr_t *reloc_base)
अणु
	वापस -ENODEV;
पूर्ण

अटल अंतरभूत व्योम *qcom_mdt_पढ़ो_metadata(स्थिर काष्ठा firmware *fw,
					   माप_प्रकार *data_len)
अणु
	वापस ERR_PTR(-ENODEV);
पूर्ण

#पूर्ण_अगर /* !IS_ENABLED(CONFIG_QCOM_MDT_LOADER) */

#पूर्ण_अगर
