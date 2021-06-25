<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Poपूर्णांकer to dma-buf-mapped memory, plus helpers.
 */

#अगर_अघोषित __DMA_BUF_MAP_H__
#घोषणा __DMA_BUF_MAP_H__

#समावेश <linux/पन.स>
#समावेश <linux/माला.स>

/**
 * DOC: overview
 *
 * Calling dma-buf's vmap operation returns a pointer to the buffer's memory.
 * Depending on the location of the buffer, users may have to access it with
 * I/O operations or memory load/store operations. For example, copying to
 * प्रणाली memory could be करोne with स_नकल(), copying to I/O memory would be
 * करोne with स_नकल_toio().
 *
 * .. code-block:: c
 *
 *	व्योम *vaddr = ...; // poपूर्णांकer to प्रणाली memory
 *	स_नकल(vaddr, src, len);
 *
 *	व्योम *vaddr_iomem = ...; // poपूर्णांकer to I/O memory
 *	स_नकल_toio(vaddr, _iomem, src, len);
 *
 * When using dma-buf's vmap operation, the वापसed poपूर्णांकer is encoded as
 * :c:type:`काष्ठा dma_buf_map <dma_buf_map>`.
 * :c:type:`काष्ठा dma_buf_map <dma_buf_map>` stores the buffer's address in
 * प्रणाली or I/O memory and a flag that संकेतs the required method of
 * accessing the buffer. Use the वापसed instance and the helper functions
 * to access the buffer's memory in the correct way.
 *
 * The type :c:type:`काष्ठा dma_buf_map <dma_buf_map>` and its helpers are
 * actually independent from the dma-buf infraकाष्ठाure. When sharing buffers
 * among devices, drivers have to know the location of the memory to access
 * the buffers in a safe way. :c:type:`काष्ठा dma_buf_map <dma_buf_map>`
 * solves this problem क्रम dma-buf and its users. If other drivers or
 * sub-प्रणालीs require similar functionality, the type could be generalized
 * and moved to a more prominent header file.
 *
 * Open-coding access to :c:type:`काष्ठा dma_buf_map <dma_buf_map>` is
 * considered bad style. Rather then accessing its fields directly, use one
 * of the provided helper functions, or implement your own. For example,
 * instances of :c:type:`काष्ठा dma_buf_map <dma_buf_map>` can be initialized
 * अटलally with DMA_BUF_MAP_INIT_VADDR(), or at runसमय with
 * dma_buf_map_set_vaddr(). These helpers will set an address in प्रणाली memory.
 *
 * .. code-block:: c
 *
 *	काष्ठा dma_buf_map map = DMA_BUF_MAP_INIT_VADDR(0xdeadbeaf);
 *
 *	dma_buf_map_set_vaddr(&map. 0xdeadbeaf);
 *
 * To set an address in I/O memory, use dma_buf_map_set_vaddr_iomem().
 *
 * .. code-block:: c
 *
 *	dma_buf_map_set_vaddr_iomem(&map. 0xdeadbeaf);
 *
 * Instances of काष्ठा dma_buf_map करो not have to be cleaned up, but
 * can be cleared to शून्य with dma_buf_map_clear(). Cleared mappings
 * always refer to प्रणाली memory.
 *
 * .. code-block:: c
 *
 *	dma_buf_map_clear(&map);
 *
 * Test अगर a mapping is valid with either dma_buf_map_is_set() or
 * dma_buf_map_is_null().
 *
 * .. code-block:: c
 *
 *	अगर (dma_buf_map_is_set(&map) != dma_buf_map_is_null(&map))
 *		// always true
 *
 * Instances of :c:type:`काष्ठा dma_buf_map <dma_buf_map>` can be compared
 * क्रम equality with dma_buf_map_is_equal(). Mappings the poपूर्णांक to dअगरferent
 * memory spaces, प्रणाली or I/O, are never equal. That's even true अगर both
 * spaces are located in the same address space, both mappings contain the
 * same address value, or both mappings refer to शून्य.
 *
 * .. code-block:: c
 *
 *	काष्ठा dma_buf_map sys_map; // refers to प्रणाली memory
 *	काष्ठा dma_buf_map io_map; // refers to I/O memory
 *
 *	अगर (dma_buf_map_is_equal(&sys_map, &io_map))
 *		// always false
 *
 * A set up instance of काष्ठा dma_buf_map can be used to access or manipulate
 * the buffer memory. Depending on the location of the memory, the provided
 * helpers will pick the correct operations. Data can be copied पूर्णांकo the memory
 * with dma_buf_map_स_नकल_to(). The address can be manipulated with
 * dma_buf_map_incr().
 *
 * .. code-block:: c
 *
 *	स्थिर व्योम *src = ...; // source buffer
 *	माप_प्रकार len = ...; // length of src
 *
 *	dma_buf_map_स_नकल_to(&map, src, len);
 *	dma_buf_map_incr(&map, len); // go to first byte after the स_नकल
 */

/**
 * काष्ठा dma_buf_map - Poपूर्णांकer to vmap'ed dma-buf memory.
 * @vaddr_iomem:	The buffer's address अगर in I/O memory
 * @vaddr:		The buffer's address अगर in प्रणाली memory
 * @is_iomem:		True अगर the dma-buf memory is located in I/O
 *			memory, or false otherwise.
 */
काष्ठा dma_buf_map अणु
	जोड़ अणु
		व्योम __iomem *vaddr_iomem;
		व्योम *vaddr;
	पूर्ण;
	bool is_iomem;
पूर्ण;

/**
 * DMA_BUF_MAP_INIT_VADDR - Initializes काष्ठा dma_buf_map to an address in प्रणाली memory
 * @vaddr_:	A प्रणाली-memory address
 */
#घोषणा DMA_BUF_MAP_INIT_VADDR(vaddr_) \
	अणु \
		.vaddr = (vaddr_), \
		.is_iomem = false, \
	पूर्ण

/**
 * dma_buf_map_set_vaddr - Sets a dma-buf mapping काष्ठाure to an address in प्रणाली memory
 * @map:	The dma-buf mapping काष्ठाure
 * @vaddr:	A प्रणाली-memory address
 *
 * Sets the address and clears the I/O-memory flag.
 */
अटल अंतरभूत व्योम dma_buf_map_set_vaddr(काष्ठा dma_buf_map *map, व्योम *vaddr)
अणु
	map->vaddr = vaddr;
	map->is_iomem = false;
पूर्ण

/**
 * dma_buf_map_set_vaddr_iomem - Sets a dma-buf mapping काष्ठाure to an address in I/O memory
 * @map:		The dma-buf mapping काष्ठाure
 * @vaddr_iomem:	An I/O-memory address
 *
 * Sets the address and the I/O-memory flag.
 */
अटल अंतरभूत व्योम dma_buf_map_set_vaddr_iomem(काष्ठा dma_buf_map *map,
					       व्योम __iomem *vaddr_iomem)
अणु
	map->vaddr_iomem = vaddr_iomem;
	map->is_iomem = true;
पूर्ण

/**
 * dma_buf_map_is_equal - Compares two dma-buf mapping काष्ठाures क्रम equality
 * @lhs:	The dma-buf mapping काष्ठाure
 * @rhs:	A dma-buf mapping काष्ठाure to compare with
 *
 * Two dma-buf mapping काष्ठाures are equal अगर they both refer to the same type of memory
 * and to the same address within that memory.
 *
 * Returns:
 * True is both काष्ठाures are equal, or false otherwise.
 */
अटल अंतरभूत bool dma_buf_map_is_equal(स्थिर काष्ठा dma_buf_map *lhs,
					स्थिर काष्ठा dma_buf_map *rhs)
अणु
	अगर (lhs->is_iomem != rhs->is_iomem)
		वापस false;
	अन्यथा अगर (lhs->is_iomem)
		वापस lhs->vaddr_iomem == rhs->vaddr_iomem;
	अन्यथा
		वापस lhs->vaddr == rhs->vaddr;
पूर्ण

/**
 * dma_buf_map_is_null - Tests क्रम a dma-buf mapping to be शून्य
 * @map:	The dma-buf mapping काष्ठाure
 *
 * Depending on the state of काष्ठा dma_buf_map.is_iomem, tests अगर the
 * mapping is शून्य.
 *
 * Returns:
 * True अगर the mapping is शून्य, or false otherwise.
 */
अटल अंतरभूत bool dma_buf_map_is_null(स्थिर काष्ठा dma_buf_map *map)
अणु
	अगर (map->is_iomem)
		वापस !map->vaddr_iomem;
	वापस !map->vaddr;
पूर्ण

/**
 * dma_buf_map_is_set - Tests is the dma-buf mapping has been set
 * @map:	The dma-buf mapping काष्ठाure
 *
 * Depending on the state of काष्ठा dma_buf_map.is_iomem, tests अगर the
 * mapping has been set.
 *
 * Returns:
 * True अगर the mapping is been set, or false otherwise.
 */
अटल अंतरभूत bool dma_buf_map_is_set(स्थिर काष्ठा dma_buf_map *map)
अणु
	वापस !dma_buf_map_is_null(map);
पूर्ण

/**
 * dma_buf_map_clear - Clears a dma-buf mapping काष्ठाure
 * @map:	The dma-buf mapping काष्ठाure
 *
 * Clears all fields to zero; including काष्ठा dma_buf_map.is_iomem. So
 * mapping काष्ठाures that were set to poपूर्णांक to I/O memory are reset क्रम
 * प्रणाली memory. Poपूर्णांकers are cleared to शून्य. This is the शेष.
 */
अटल अंतरभूत व्योम dma_buf_map_clear(काष्ठा dma_buf_map *map)
अणु
	अगर (map->is_iomem) अणु
		map->vaddr_iomem = शून्य;
		map->is_iomem = false;
	पूर्ण अन्यथा अणु
		map->vaddr = शून्य;
	पूर्ण
पूर्ण

/**
 * dma_buf_map_स_नकल_to - Memcpy पूर्णांकo dma-buf mapping
 * @dst:	The dma-buf mapping काष्ठाure
 * @src:	The source buffer
 * @len:	The number of byte in src
 *
 * Copies data पूर्णांकo a dma-buf mapping. The source buffer is in प्रणाली
 * memory. Depending on the buffer's location, the helper picks the correct
 * method of accessing the memory.
 */
अटल अंतरभूत व्योम dma_buf_map_स_नकल_to(काष्ठा dma_buf_map *dst, स्थिर व्योम *src, माप_प्रकार len)
अणु
	अगर (dst->is_iomem)
		स_नकल_toio(dst->vaddr_iomem, src, len);
	अन्यथा
		स_नकल(dst->vaddr, src, len);
पूर्ण

/**
 * dma_buf_map_incr - Increments the address stored in a dma-buf mapping
 * @map:	The dma-buf mapping काष्ठाure
 * @incr:	The number of bytes to increment
 *
 * Increments the address stored in a dma-buf mapping. Depending on the
 * buffer's location, the correct value will be updated.
 */
अटल अंतरभूत व्योम dma_buf_map_incr(काष्ठा dma_buf_map *map, माप_प्रकार incr)
अणु
	अगर (map->is_iomem)
		map->vaddr_iomem += incr;
	अन्यथा
		map->vaddr += incr;
पूर्ण

#पूर्ण_अगर /* __DMA_BUF_MAP_H__ */
