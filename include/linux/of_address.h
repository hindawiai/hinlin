<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __OF_ADDRESS_H
#घोषणा __OF_ADDRESS_H
#समावेश <linux/ioport.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/of.h>
#समावेश <linux/पन.स>

काष्ठा of_bus;

काष्ठा of_pci_range_parser अणु
	काष्ठा device_node *node;
	काष्ठा of_bus *bus;
	स्थिर __be32 *range;
	स्थिर __be32 *end;
	पूर्णांक na;
	पूर्णांक ns;
	पूर्णांक pna;
	bool dma;
पूर्ण;
#घोषणा of_range_parser of_pci_range_parser

काष्ठा of_pci_range अणु
	जोड़ अणु
		u64 pci_addr;
		u64 bus_addr;
	पूर्ण;
	u64 cpu_addr;
	u64 size;
	u32 flags;
पूर्ण;
#घोषणा of_range of_pci_range

#घोषणा क्रम_each_of_pci_range(parser, range) \
	क्रम (; of_pci_range_parser_one(parser, range);)
#घोषणा क्रम_each_of_range क्रम_each_of_pci_range

/* Translate a DMA address from device space to CPU space */
बाह्य u64 of_translate_dma_address(काष्ठा device_node *dev,
				    स्थिर __be32 *in_addr);

#अगर_घोषित CONFIG_OF_ADDRESS
बाह्य u64 of_translate_address(काष्ठा device_node *np, स्थिर __be32 *addr);
बाह्य पूर्णांक of_address_to_resource(काष्ठा device_node *dev, पूर्णांक index,
				  काष्ठा resource *r);
बाह्य व्योम __iomem *of_iomap(काष्ठा device_node *device, पूर्णांक index);
व्योम __iomem *of_io_request_and_map(काष्ठा device_node *device,
				    पूर्णांक index, स्थिर अक्षर *name);

/* Extract an address from a device, वापसs the region size and
 * the address space flags too. The PCI version uses a BAR number
 * instead of an असलolute index
 */
बाह्य स्थिर __be32 *of_get_address(काष्ठा device_node *dev, पूर्णांक index,
			   u64 *size, अचिन्हित पूर्णांक *flags);

बाह्य पूर्णांक of_pci_range_parser_init(काष्ठा of_pci_range_parser *parser,
			काष्ठा device_node *node);
बाह्य पूर्णांक of_pci_dma_range_parser_init(काष्ठा of_pci_range_parser *parser,
			काष्ठा device_node *node);
बाह्य काष्ठा of_pci_range *of_pci_range_parser_one(
					काष्ठा of_pci_range_parser *parser,
					काष्ठा of_pci_range *range);
बाह्य bool of_dma_is_coherent(काष्ठा device_node *np);
#अन्यथा /* CONFIG_OF_ADDRESS */
अटल अंतरभूत व्योम __iomem *of_io_request_and_map(काष्ठा device_node *device,
						  पूर्णांक index, स्थिर अक्षर *name)
अणु
	वापस IOMEM_ERR_PTR(-EINVAL);
पूर्ण

अटल अंतरभूत u64 of_translate_address(काष्ठा device_node *np,
				       स्थिर __be32 *addr)
अणु
	वापस OF_BAD_ADDR;
पूर्ण

अटल अंतरभूत स्थिर __be32 *of_get_address(काष्ठा device_node *dev, पूर्णांक index,
					u64 *size, अचिन्हित पूर्णांक *flags)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत पूर्णांक of_pci_range_parser_init(काष्ठा of_pci_range_parser *parser,
			काष्ठा device_node *node)
अणु
	वापस -ENOSYS;
पूर्ण

अटल अंतरभूत पूर्णांक of_pci_dma_range_parser_init(काष्ठा of_pci_range_parser *parser,
			काष्ठा device_node *node)
अणु
	वापस -ENOSYS;
पूर्ण

अटल अंतरभूत काष्ठा of_pci_range *of_pci_range_parser_one(
					काष्ठा of_pci_range_parser *parser,
					काष्ठा of_pci_range *range)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत bool of_dma_is_coherent(काष्ठा device_node *np)
अणु
	वापस false;
पूर्ण
#पूर्ण_अगर /* CONFIG_OF_ADDRESS */

#अगर_घोषित CONFIG_OF
बाह्य पूर्णांक of_address_to_resource(काष्ठा device_node *dev, पूर्णांक index,
				  काष्ठा resource *r);
व्योम __iomem *of_iomap(काष्ठा device_node *node, पूर्णांक index);
#अन्यथा
अटल अंतरभूत पूर्णांक of_address_to_resource(काष्ठा device_node *dev, पूर्णांक index,
					 काष्ठा resource *r)
अणु
	वापस -EINVAL;
पूर्ण

अटल अंतरभूत व्योम __iomem *of_iomap(काष्ठा device_node *device, पूर्णांक index)
अणु
	वापस शून्य;
पूर्ण
#पूर्ण_अगर
#घोषणा of_range_parser_init of_pci_range_parser_init

#अगर defined(CONFIG_OF_ADDRESS) && defined(CONFIG_PCI)
बाह्य स्थिर __be32 *of_get_pci_address(काष्ठा device_node *dev, पूर्णांक bar_no,
			       u64 *size, अचिन्हित पूर्णांक *flags);
बाह्य पूर्णांक of_pci_address_to_resource(काष्ठा device_node *dev, पूर्णांक bar,
				      काष्ठा resource *r);
बाह्य पूर्णांक of_pci_range_to_resource(काष्ठा of_pci_range *range,
				    काष्ठा device_node *np,
				    काष्ठा resource *res);
#अन्यथा /* CONFIG_OF_ADDRESS && CONFIG_PCI */
अटल अंतरभूत पूर्णांक of_pci_address_to_resource(काष्ठा device_node *dev, पूर्णांक bar,
				             काष्ठा resource *r)
अणु
	वापस -ENOSYS;
पूर्ण

अटल अंतरभूत स्थिर __be32 *of_get_pci_address(काष्ठा device_node *dev,
		पूर्णांक bar_no, u64 *size, अचिन्हित पूर्णांक *flags)
अणु
	वापस शून्य;
पूर्ण
अटल अंतरभूत पूर्णांक of_pci_range_to_resource(काष्ठा of_pci_range *range,
					   काष्ठा device_node *np,
					   काष्ठा resource *res)
अणु
	वापस -ENOSYS;
पूर्ण
#पूर्ण_अगर /* CONFIG_OF_ADDRESS && CONFIG_PCI */

#पूर्ण_अगर /* __OF_ADDRESS_H */
