<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित ASMARM_DMA_MAPPING_H
#घोषणा ASMARM_DMA_MAPPING_H

#अगर_घोषित __KERNEL__

#समावेश <linux/mm_types.h>
#समावेश <linux/scatterlist.h>

#समावेश <xen/xen.h>
#समावेश <यंत्र/xen/hypervisor.h>

बाह्य स्थिर काष्ठा dma_map_ops arm_dma_ops;
बाह्य स्थिर काष्ठा dma_map_ops arm_coherent_dma_ops;

अटल अंतरभूत स्थिर काष्ठा dma_map_ops *get_arch_dma_ops(काष्ठा bus_type *bus)
अणु
	अगर (IS_ENABLED(CONFIG_MMU) && !IS_ENABLED(CONFIG_ARM_LPAE))
		वापस &arm_dma_ops;
	वापस शून्य;
पूर्ण

/**
 * arm_dma_alloc - allocate consistent memory क्रम DMA
 * @dev: valid काष्ठा device poपूर्णांकer, or शून्य क्रम ISA and EISA-like devices
 * @size: required memory size
 * @handle: bus-specअगरic DMA address
 * @attrs: optinal attributes that specअगरic mapping properties
 *
 * Allocate some memory क्रम a device क्रम perक्रमming DMA.  This function
 * allocates pages, and will वापस the CPU-viewed address, and sets @handle
 * to be the device-viewed address.
 */
बाह्य व्योम *arm_dma_alloc(काष्ठा device *dev, माप_प्रकार size, dma_addr_t *handle,
			   gfp_t gfp, अचिन्हित दीर्घ attrs);

/**
 * arm_dma_मुक्त - मुक्त memory allocated by arm_dma_alloc
 * @dev: valid काष्ठा device poपूर्णांकer, or शून्य क्रम ISA and EISA-like devices
 * @size: size of memory originally requested in dma_alloc_coherent
 * @cpu_addr: CPU-view address वापसed from dma_alloc_coherent
 * @handle: device-view address वापसed from dma_alloc_coherent
 * @attrs: optinal attributes that specअगरic mapping properties
 *
 * Free (and unmap) a DMA buffer previously allocated by
 * arm_dma_alloc().
 *
 * References to memory and mappings associated with cpu_addr/handle
 * during and after this call executing are illegal.
 */
बाह्य व्योम arm_dma_मुक्त(काष्ठा device *dev, माप_प्रकार size, व्योम *cpu_addr,
			 dma_addr_t handle, अचिन्हित दीर्घ attrs);

/**
 * arm_dma_mmap - map a coherent DMA allocation पूर्णांकo user space
 * @dev: valid काष्ठा device poपूर्णांकer, or शून्य क्रम ISA and EISA-like devices
 * @vma: vm_area_काष्ठा describing requested user mapping
 * @cpu_addr: kernel CPU-view address वापसed from dma_alloc_coherent
 * @handle: device-view address वापसed from dma_alloc_coherent
 * @size: size of memory originally requested in dma_alloc_coherent
 * @attrs: optinal attributes that specअगरic mapping properties
 *
 * Map a coherent DMA buffer previously allocated by dma_alloc_coherent
 * पूर्णांकo user space.  The coherent DMA buffer must not be मुक्तd by the
 * driver until the user space mapping has been released.
 */
बाह्य पूर्णांक arm_dma_mmap(काष्ठा device *dev, काष्ठा vm_area_काष्ठा *vma,
			व्योम *cpu_addr, dma_addr_t dma_addr, माप_प्रकार size,
			अचिन्हित दीर्घ attrs);

/*
 * For SA-1111, IXP425, and ADI प्रणालीs  the dma-mapping functions are "magic"
 * and utilize bounce buffers as needed to work around limited DMA winकरोws.
 *
 * On the SA-1111, a bug limits DMA to only certain regions of RAM.
 * On the IXP425, the PCI inbound winकरोw is 64MB (256MB total RAM)
 * On some ADI engineering प्रणालीs, PCI inbound winकरोw is 32MB (12MB total RAM)
 *
 * The following are helper functions used by the dmabounce subystem
 *
 */

/**
 * dmabounce_रेजिस्टर_dev
 *
 * @dev: valid काष्ठा device poपूर्णांकer
 * @small_buf_size: size of buffers to use with small buffer pool
 * @large_buf_size: size of buffers to use with large buffer pool (can be 0)
 * @needs_bounce_fn: called to determine whether buffer needs bouncing
 *
 * This function should be called by low-level platक्रमm code to रेजिस्टर
 * a device as requireing DMA buffer bouncing. The function will allocate
 * appropriate DMA pools क्रम the device.
 */
बाह्य पूर्णांक dmabounce_रेजिस्टर_dev(काष्ठा device *, अचिन्हित दीर्घ,
		अचिन्हित दीर्घ, पूर्णांक (*)(काष्ठा device *, dma_addr_t, माप_प्रकार));

/**
 * dmabounce_unरेजिस्टर_dev
 *
 * @dev: valid काष्ठा device poपूर्णांकer
 *
 * This function should be called by low-level platक्रमm code when device
 * that was previously रेजिस्टरed with dmabounce_रेजिस्टर_dev is हटाओd
 * from the प्रणाली.
 *
 */
बाह्य व्योम dmabounce_unरेजिस्टर_dev(काष्ठा device *);



/*
 * The scatter list versions of the above methods.
 */
बाह्य पूर्णांक arm_dma_map_sg(काष्ठा device *, काष्ठा scatterlist *, पूर्णांक,
		क्रमागत dma_data_direction, अचिन्हित दीर्घ attrs);
बाह्य व्योम arm_dma_unmap_sg(काष्ठा device *, काष्ठा scatterlist *, पूर्णांक,
		क्रमागत dma_data_direction, अचिन्हित दीर्घ attrs);
बाह्य व्योम arm_dma_sync_sg_क्रम_cpu(काष्ठा device *, काष्ठा scatterlist *, पूर्णांक,
		क्रमागत dma_data_direction);
बाह्य व्योम arm_dma_sync_sg_क्रम_device(काष्ठा device *, काष्ठा scatterlist *, पूर्णांक,
		क्रमागत dma_data_direction);
बाह्य पूर्णांक arm_dma_get_sgtable(काष्ठा device *dev, काष्ठा sg_table *sgt,
		व्योम *cpu_addr, dma_addr_t dma_addr, माप_प्रकार size,
		अचिन्हित दीर्घ attrs);

#पूर्ण_अगर /* __KERNEL__ */
#पूर्ण_अगर
