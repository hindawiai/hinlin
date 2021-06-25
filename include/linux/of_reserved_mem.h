<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __OF_RESERVED_MEM_H
#घोषणा __OF_RESERVED_MEM_H

#समावेश <linux/device.h>
#समावेश <linux/of.h>

काष्ठा of_phandle_args;
काष्ठा reserved_mem_ops;

काष्ठा reserved_mem अणु
	स्थिर अक्षर			*name;
	अचिन्हित दीर्घ			fdt_node;
	अचिन्हित दीर्घ			phandle;
	स्थिर काष्ठा reserved_mem_ops	*ops;
	phys_addr_t			base;
	phys_addr_t			size;
	व्योम				*priv;
पूर्ण;

काष्ठा reserved_mem_ops अणु
	पूर्णांक	(*device_init)(काष्ठा reserved_mem *rmem,
			       काष्ठा device *dev);
	व्योम	(*device_release)(काष्ठा reserved_mem *rmem,
				  काष्ठा device *dev);
पूर्ण;

प्रकार पूर्णांक (*reservedmem_of_init_fn)(काष्ठा reserved_mem *rmem);

#घोषणा RESERVEDMEM_OF_DECLARE(name, compat, init)			\
	_OF_DECLARE(reservedmem, name, compat, init, reservedmem_of_init_fn)

#अगर_घोषित CONFIG_OF_RESERVED_MEM

पूर्णांक of_reserved_mem_device_init_by_idx(काष्ठा device *dev,
				       काष्ठा device_node *np, पूर्णांक idx);
पूर्णांक of_reserved_mem_device_init_by_name(काष्ठा device *dev,
					काष्ठा device_node *np,
					स्थिर अक्षर *name);
व्योम of_reserved_mem_device_release(काष्ठा device *dev);

व्योम fdt_init_reserved_mem(व्योम);
व्योम fdt_reserved_mem_save_node(अचिन्हित दीर्घ node, स्थिर अक्षर *uname,
			       phys_addr_t base, phys_addr_t size);
काष्ठा reserved_mem *of_reserved_mem_lookup(काष्ठा device_node *np);
#अन्यथा
अटल अंतरभूत पूर्णांक of_reserved_mem_device_init_by_idx(काष्ठा device *dev,
					काष्ठा device_node *np, पूर्णांक idx)
अणु
	वापस -ENOSYS;
पूर्ण

अटल अंतरभूत पूर्णांक of_reserved_mem_device_init_by_name(काष्ठा device *dev,
						      काष्ठा device_node *np,
						      स्थिर अक्षर *name)
अणु
	वापस -ENOSYS;
पूर्ण

अटल अंतरभूत व्योम of_reserved_mem_device_release(काष्ठा device *pdev) अणु पूर्ण

अटल अंतरभूत व्योम fdt_init_reserved_mem(व्योम) अणु पूर्ण
अटल अंतरभूत व्योम fdt_reserved_mem_save_node(अचिन्हित दीर्घ node,
		स्थिर अक्षर *uname, phys_addr_t base, phys_addr_t size) अणु पूर्ण
अटल अंतरभूत काष्ठा reserved_mem *of_reserved_mem_lookup(काष्ठा device_node *np)
अणु
	वापस शून्य;
पूर्ण
#पूर्ण_अगर

/**
 * of_reserved_mem_device_init() - assign reserved memory region to given device
 * @dev:	Poपूर्णांकer to the device to configure
 *
 * This function assigns respective DMA-mapping operations based on the first
 * reserved memory region specअगरied by 'memory-region' property in device tree
 * node of the given device.
 *
 * Returns error code or zero on success.
 */
अटल अंतरभूत पूर्णांक of_reserved_mem_device_init(काष्ठा device *dev)
अणु
	वापस of_reserved_mem_device_init_by_idx(dev, dev->of_node, 0);
पूर्ण

#पूर्ण_अगर /* __OF_RESERVED_MEM_H */
