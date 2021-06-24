<शैली गुरु>
#अगर_अघोषित _IOMMU_H
#घोषणा _IOMMU_H 1

#समावेश <linux/pci.h>

काष्ठा parisc_device;
काष्ठा ioc;

अटल अंतरभूत काष्ठा pci_hba_data *parisc_walk_tree(काष्ठा device *dev)
अणु
	काष्ठा device *otherdev;

	अगर (likely(dev->platक्रमm_data))
		वापस dev->platक्रमm_data;

	/* OK, just traverse the bus to find it */
	क्रम (otherdev = dev->parent;
	     otherdev;
	     otherdev = otherdev->parent) अणु
		अगर (otherdev->platक्रमm_data) अणु
			dev->platक्रमm_data = otherdev->platक्रमm_data;
			अवरोध;
		पूर्ण
	पूर्ण

	वापस dev->platक्रमm_data;
पूर्ण

अटल अंतरभूत काष्ठा ioc *GET_IOC(काष्ठा device *dev)
अणु
	काष्ठा pci_hba_data *pdata = parisc_walk_tree(dev);

	अगर (!pdata)
		वापस शून्य;
	वापस pdata->iommu;
पूर्ण

#अगर_घोषित CONFIG_IOMMU_CCIO
व्योम *ccio_get_iommu(स्थिर काष्ठा parisc_device *dev);
पूर्णांक ccio_request_resource(स्थिर काष्ठा parisc_device *dev,
		काष्ठा resource *res);
पूर्णांक ccio_allocate_resource(स्थिर काष्ठा parisc_device *dev,
		काष्ठा resource *res, अचिन्हित दीर्घ size,
		अचिन्हित दीर्घ min, अचिन्हित दीर्घ max, अचिन्हित दीर्घ align);
#अन्यथा /* !CONFIG_IOMMU_CCIO */
#घोषणा ccio_get_iommu(dev) शून्य
#घोषणा ccio_request_resource(dev, res) insert_resource(&iomem_resource, res)
#घोषणा ccio_allocate_resource(dev, res, size, min, max, align) \
		allocate_resource(&iomem_resource, res, size, min, max, \
				align, शून्य, शून्य)
#पूर्ण_अगर /* !CONFIG_IOMMU_CCIO */

व्योम *sba_get_iommu(काष्ठा parisc_device *dev);

#पूर्ण_अगर /* _IOMMU_H */
