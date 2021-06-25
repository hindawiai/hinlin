<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __OF_IOMMU_H
#घोषणा __OF_IOMMU_H

#समावेश <linux/device.h>
#समावेश <linux/iommu.h>
#समावेश <linux/of.h>

#अगर_घोषित CONFIG_OF_IOMMU

बाह्य पूर्णांक of_get_dma_winकरोw(काष्ठा device_node *dn, स्थिर अक्षर *prefix,
			     पूर्णांक index, अचिन्हित दीर्घ *busno, dma_addr_t *addr,
			     माप_प्रकार *size);

बाह्य स्थिर काष्ठा iommu_ops *of_iommu_configure(काष्ठा device *dev,
					काष्ठा device_node *master_np,
					स्थिर u32 *id);

#अन्यथा

अटल अंतरभूत पूर्णांक of_get_dma_winकरोw(काष्ठा device_node *dn, स्थिर अक्षर *prefix,
			    पूर्णांक index, अचिन्हित दीर्घ *busno, dma_addr_t *addr,
			    माप_प्रकार *size)
अणु
	वापस -EINVAL;
पूर्ण

अटल अंतरभूत स्थिर काष्ठा iommu_ops *of_iommu_configure(काष्ठा device *dev,
					 काष्ठा device_node *master_np,
					 स्थिर u32 *id)
अणु
	वापस शून्य;
पूर्ण

#पूर्ण_अगर	/* CONFIG_OF_IOMMU */

#पूर्ण_अगर /* __OF_IOMMU_H */
