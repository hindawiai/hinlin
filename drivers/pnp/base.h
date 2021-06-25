<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (C) 2008 Hewlett-Packard Development Company, L.P.
 *	Bjorn Helgaas <bjorn.helgaas@hp.com>
 */

बाह्य काष्ठा mutex pnp_lock;
बाह्य स्थिर काष्ठा attribute_group *pnp_dev_groups[];
व्योम *pnp_alloc(दीर्घ size);

पूर्णांक pnp_रेजिस्टर_protocol(काष्ठा pnp_protocol *protocol);
व्योम pnp_unरेजिस्टर_protocol(काष्ठा pnp_protocol *protocol);

#घोषणा PNP_EISA_ID_MASK 0x7fffffff
व्योम pnp_eisa_id_to_string(u32 id, अक्षर *str);
काष्ठा pnp_dev *pnp_alloc_dev(काष्ठा pnp_protocol *, पूर्णांक id,
			      स्थिर अक्षर *pnpid);
काष्ठा pnp_card *pnp_alloc_card(काष्ठा pnp_protocol *, पूर्णांक id, अक्षर *pnpid);

पूर्णांक pnp_add_device(काष्ठा pnp_dev *dev);
काष्ठा pnp_id *pnp_add_id(काष्ठा pnp_dev *dev, स्थिर अक्षर *id);

पूर्णांक pnp_add_card(काष्ठा pnp_card *card);
व्योम pnp_हटाओ_card(काष्ठा pnp_card *card);
पूर्णांक pnp_add_card_device(काष्ठा pnp_card *card, काष्ठा pnp_dev *dev);
व्योम pnp_हटाओ_card_device(काष्ठा pnp_dev *dev);

काष्ठा pnp_port अणु
	resource_माप_प्रकार min;	/* min base number */
	resource_माप_प्रकार max;	/* max base number */
	resource_माप_प्रकार align;	/* align boundary */
	resource_माप_प्रकार size;	/* size of range */
	अचिन्हित अक्षर flags;	/* port flags */
पूर्ण;

#घोषणा PNP_IRQ_NR 256
प्रकार काष्ठा अणु DECLARE_BITMAP(bits, PNP_IRQ_NR); पूर्ण pnp_irq_mask_t;

काष्ठा pnp_irq अणु
	pnp_irq_mask_t map;	/* biपंचांगap क्रम IRQ lines */
	अचिन्हित अक्षर flags;	/* IRQ flags */
पूर्ण;

काष्ठा pnp_dma अणु
	अचिन्हित अक्षर map;	/* biपंचांगask क्रम DMA channels */
	अचिन्हित अक्षर flags;	/* DMA flags */
पूर्ण;

काष्ठा pnp_mem अणु
	resource_माप_प्रकार min;	/* min base number */
	resource_माप_प्रकार max;	/* max base number */
	resource_माप_प्रकार align;	/* align boundary */
	resource_माप_प्रकार size;	/* size of range */
	अचिन्हित अक्षर flags;	/* memory flags */
पूर्ण;

#घोषणा PNP_OPTION_DEPENDENT		0x80000000
#घोषणा PNP_OPTION_SET_MASK		0xffff
#घोषणा PNP_OPTION_SET_SHIFT		12
#घोषणा PNP_OPTION_PRIORITY_MASK	0xfff
#घोषणा PNP_OPTION_PRIORITY_SHIFT	0

#घोषणा PNP_RES_PRIORITY_PREFERRED	0
#घोषणा PNP_RES_PRIORITY_ACCEPTABLE	1
#घोषणा PNP_RES_PRIORITY_FUNCTIONAL	2
#घोषणा PNP_RES_PRIORITY_INVALID	PNP_OPTION_PRIORITY_MASK

काष्ठा pnp_option अणु
	काष्ठा list_head list;
	अचिन्हित पूर्णांक flags;	/* independent/dependent, set, priority */

	अचिन्हित दीर्घ type;	/* IORESOURCE_अणुIO,MEM,IRQ,DMAपूर्ण */
	जोड़ अणु
		काष्ठा pnp_port port;
		काष्ठा pnp_irq irq;
		काष्ठा pnp_dma dma;
		काष्ठा pnp_mem mem;
	पूर्ण u;
पूर्ण;

पूर्णांक pnp_रेजिस्टर_irq_resource(काष्ठा pnp_dev *dev, अचिन्हित पूर्णांक option_flags,
			      pnp_irq_mask_t *map, अचिन्हित अक्षर flags);
पूर्णांक pnp_रेजिस्टर_dma_resource(काष्ठा pnp_dev *dev, अचिन्हित पूर्णांक option_flags,
			      अचिन्हित अक्षर map, अचिन्हित अक्षर flags);
पूर्णांक pnp_रेजिस्टर_port_resource(काष्ठा pnp_dev *dev, अचिन्हित पूर्णांक option_flags,
			       resource_माप_प्रकार min, resource_माप_प्रकार max,
			       resource_माप_प्रकार align, resource_माप_प्रकार size,
			       अचिन्हित अक्षर flags);
पूर्णांक pnp_रेजिस्टर_mem_resource(काष्ठा pnp_dev *dev, अचिन्हित पूर्णांक option_flags,
			      resource_माप_प्रकार min, resource_माप_प्रकार max,
			      resource_माप_प्रकार align, resource_माप_प्रकार size,
			      अचिन्हित अक्षर flags);

अटल अंतरभूत पूर्णांक pnp_option_is_dependent(काष्ठा pnp_option *option)
अणु
	वापस option->flags & PNP_OPTION_DEPENDENT ? 1 : 0;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक pnp_option_set(काष्ठा pnp_option *option)
अणु
	वापस (option->flags >> PNP_OPTION_SET_SHIFT) & PNP_OPTION_SET_MASK;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक pnp_option_priority(काष्ठा pnp_option *option)
अणु
	वापस (option->flags >> PNP_OPTION_PRIORITY_SHIFT) &
	    PNP_OPTION_PRIORITY_MASK;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक pnp_new_dependent_set(काष्ठा pnp_dev *dev,
						 पूर्णांक priority)
अणु
	अचिन्हित पूर्णांक flags;

	अगर (priority > PNP_RES_PRIORITY_FUNCTIONAL) अणु
		dev_warn(&dev->dev, "invalid dependent option priority %d "
			 "clipped to %d", priority,
			 PNP_RES_PRIORITY_INVALID);
		priority = PNP_RES_PRIORITY_INVALID;
	पूर्ण

	flags = PNP_OPTION_DEPENDENT |
	    ((dev->num_dependent_sets & PNP_OPTION_SET_MASK) <<
		PNP_OPTION_SET_SHIFT) |
	    ((priority & PNP_OPTION_PRIORITY_MASK) <<
		PNP_OPTION_PRIORITY_SHIFT);

	dev->num_dependent_sets++;

	वापस flags;
पूर्ण

अक्षर *pnp_option_priority_name(काष्ठा pnp_option *option);
व्योम dbg_pnp_show_option(काष्ठा pnp_dev *dev, काष्ठा pnp_option *option);

व्योम pnp_init_resources(काष्ठा pnp_dev *dev);

व्योम pnp_fixup_device(काष्ठा pnp_dev *dev);
व्योम pnp_मुक्त_options(काष्ठा pnp_dev *dev);
पूर्णांक __pnp_add_device(काष्ठा pnp_dev *dev);
व्योम __pnp_हटाओ_device(काष्ठा pnp_dev *dev);

पूर्णांक pnp_check_port(काष्ठा pnp_dev *dev, काष्ठा resource *res);
पूर्णांक pnp_check_mem(काष्ठा pnp_dev *dev, काष्ठा resource *res);
पूर्णांक pnp_check_irq(काष्ठा pnp_dev *dev, काष्ठा resource *res);
#अगर_घोषित CONFIG_ISA_DMA_API
पूर्णांक pnp_check_dma(काष्ठा pnp_dev *dev, काष्ठा resource *res);
#पूर्ण_अगर

अक्षर *pnp_resource_type_name(काष्ठा resource *res);
व्योम dbg_pnp_show_resources(काष्ठा pnp_dev *dev, अक्षर *desc);

व्योम pnp_मुक्त_resources(काष्ठा pnp_dev *dev);
अचिन्हित दीर्घ pnp_resource_type(काष्ठा resource *res);

काष्ठा pnp_resource अणु
	काष्ठा list_head list;
	काष्ठा resource res;
पूर्ण;

व्योम pnp_मुक्त_resource(काष्ठा pnp_resource *pnp_res);

काष्ठा pnp_resource *pnp_add_resource(काष्ठा pnp_dev *dev,
				      काष्ठा resource *res);
काष्ठा pnp_resource *pnp_add_irq_resource(काष्ठा pnp_dev *dev, पूर्णांक irq,
					  पूर्णांक flags);
काष्ठा pnp_resource *pnp_add_dma_resource(काष्ठा pnp_dev *dev, पूर्णांक dma,
					  पूर्णांक flags);
काष्ठा pnp_resource *pnp_add_io_resource(काष्ठा pnp_dev *dev,
					 resource_माप_प्रकार start,
					 resource_माप_प्रकार end, पूर्णांक flags);
काष्ठा pnp_resource *pnp_add_mem_resource(काष्ठा pnp_dev *dev,
					  resource_माप_प्रकार start,
					  resource_माप_प्रकार end, पूर्णांक flags);
काष्ठा pnp_resource *pnp_add_bus_resource(काष्ठा pnp_dev *dev,
					  resource_माप_प्रकार start,
					  resource_माप_प्रकार end);

बाह्य पूर्णांक pnp_debug;

#अगर defined(CONFIG_PNP_DEBUG_MESSAGES)
#घोषणा pnp_dbg(dev, क्रमmat, arg...)					\
	(अणु अगर (pnp_debug) dev_prपूर्णांकk(KERN_DEBUG, dev, क्रमmat, ## arg); 0; पूर्ण)
#अन्यथा
#घोषणा pnp_dbg(dev, क्रमmat, arg...)					\
	(अणु अगर (0) dev_prपूर्णांकk(KERN_DEBUG, dev, क्रमmat, ## arg); 0; पूर्ण)
#पूर्ण_अगर
