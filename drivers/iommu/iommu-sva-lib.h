<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * SVA library क्रम IOMMU drivers
 */
#अगर_अघोषित _IOMMU_SVA_LIB_H
#घोषणा _IOMMU_SVA_LIB_H

#समावेश <linux/ioasid.h>
#समावेश <linux/mm_types.h>

पूर्णांक iommu_sva_alloc_pasid(काष्ठा mm_काष्ठा *mm, ioasid_t min, ioasid_t max);
व्योम iommu_sva_मुक्त_pasid(काष्ठा mm_काष्ठा *mm);
काष्ठा mm_काष्ठा *iommu_sva_find(ioasid_t pasid);

/* I/O Page fault */
काष्ठा device;
काष्ठा iommu_fault;
काष्ठा iopf_queue;

#अगर_घोषित CONFIG_IOMMU_SVA_LIB
पूर्णांक iommu_queue_iopf(काष्ठा iommu_fault *fault, व्योम *cookie);

पूर्णांक iopf_queue_add_device(काष्ठा iopf_queue *queue, काष्ठा device *dev);
पूर्णांक iopf_queue_हटाओ_device(काष्ठा iopf_queue *queue,
			     काष्ठा device *dev);
पूर्णांक iopf_queue_flush_dev(काष्ठा device *dev);
काष्ठा iopf_queue *iopf_queue_alloc(स्थिर अक्षर *name);
व्योम iopf_queue_मुक्त(काष्ठा iopf_queue *queue);
पूर्णांक iopf_queue_discard_partial(काष्ठा iopf_queue *queue);

#अन्यथा /* CONFIG_IOMMU_SVA_LIB */
अटल अंतरभूत पूर्णांक iommu_queue_iopf(काष्ठा iommu_fault *fault, व्योम *cookie)
अणु
	वापस -ENODEV;
पूर्ण

अटल अंतरभूत पूर्णांक iopf_queue_add_device(काष्ठा iopf_queue *queue,
					काष्ठा device *dev)
अणु
	वापस -ENODEV;
पूर्ण

अटल अंतरभूत पूर्णांक iopf_queue_हटाओ_device(काष्ठा iopf_queue *queue,
					   काष्ठा device *dev)
अणु
	वापस -ENODEV;
पूर्ण

अटल अंतरभूत पूर्णांक iopf_queue_flush_dev(काष्ठा device *dev)
अणु
	वापस -ENODEV;
पूर्ण

अटल अंतरभूत काष्ठा iopf_queue *iopf_queue_alloc(स्थिर अक्षर *name)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत व्योम iopf_queue_मुक्त(काष्ठा iopf_queue *queue)
अणु
पूर्ण

अटल अंतरभूत पूर्णांक iopf_queue_discard_partial(काष्ठा iopf_queue *queue)
अणु
	वापस -ENODEV;
पूर्ण
#पूर्ण_अगर /* CONFIG_IOMMU_SVA_LIB */
#पूर्ण_अगर /* _IOMMU_SVA_LIB_H */
