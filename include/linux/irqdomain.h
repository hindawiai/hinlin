<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * irq_करोमुख्य - IRQ translation करोमुख्यs
 *
 * Translation infraकाष्ठाure between hw and linux irq numbers.  This is
 * helpful क्रम पूर्णांकerrupt controllers to implement mapping between hardware
 * irq numbers and the Linux irq number space.
 *
 * irq_करोमुख्यs also have hooks क्रम translating device tree or other
 * firmware पूर्णांकerrupt representations पूर्णांकo a hardware irq number that
 * can be mapped back to a Linux irq number without any extra platक्रमm
 * support code.
 *
 * Interrupt controller "domain" data काष्ठाure. This could be defined as a
 * irq करोमुख्य controller. That is, it handles the mapping between hardware
 * and भव पूर्णांकerrupt numbers क्रम a given पूर्णांकerrupt करोमुख्य. The करोमुख्य
 * काष्ठाure is generally created by the PIC code क्रम a given PIC instance
 * (though a करोमुख्य can cover more than one PIC अगर they have a flat number
 * model). It's the करोमुख्य callbacks that are responsible क्रम setting the
 * irq_chip on a given irq_desc after it's been mapped.
 *
 * The host code and data काष्ठाures use a fwnode_handle poपूर्णांकer to
 * identअगरy the करोमुख्य. In some हालs, and in order to preserve source
 * code compatibility, this fwnode poपूर्णांकer is "upgraded" to a DT
 * device_node. For those firmware infraकाष्ठाures that करो not provide
 * a unique identअगरier क्रम an पूर्णांकerrupt controller, the irq_करोमुख्य
 * code offers a fwnode allocator.
 */

#अगर_अघोषित _LINUX_IRQDOMAIN_H
#घोषणा _LINUX_IRQDOMAIN_H

#समावेश <linux/types.h>
#समावेश <linux/irqhandler.h>
#समावेश <linux/of.h>
#समावेश <linux/mutex.h>
#समावेश <linux/radix-tree.h>

काष्ठा device_node;
काष्ठा fwnode_handle;
काष्ठा irq_करोमुख्य;
काष्ठा irq_chip;
काष्ठा irq_data;
काष्ठा cpumask;
काष्ठा seq_file;
काष्ठा irq_affinity_desc;

/* Number of irqs reserved क्रम a legacy isa controller */
#घोषणा NUM_ISA_INTERRUPTS	16

#घोषणा IRQ_DOMAIN_IRQ_SPEC_PARAMS 16

/**
 * काष्ठा irq_fwspec - generic IRQ specअगरier काष्ठाure
 *
 * @fwnode:		Poपूर्णांकer to a firmware-specअगरic descriptor
 * @param_count:	Number of device-specअगरic parameters
 * @param:		Device-specअगरic parameters
 *
 * This काष्ठाure, directly modeled after of_phandle_args, is used to
 * pass a device-specअगरic description of an पूर्णांकerrupt.
 */
काष्ठा irq_fwspec अणु
	काष्ठा fwnode_handle *fwnode;
	पूर्णांक param_count;
	u32 param[IRQ_DOMAIN_IRQ_SPEC_PARAMS];
पूर्ण;

/*
 * Should several करोमुख्यs have the same device node, but serve
 * dअगरferent purposes (क्रम example one करोमुख्य is क्रम PCI/MSI, and the
 * other क्रम wired IRQs), they can be distinguished using a
 * bus-specअगरic token. Most करोमुख्यs are expected to only carry
 * DOMAIN_BUS_ANY.
 */
क्रमागत irq_करोमुख्य_bus_token अणु
	DOMAIN_BUS_ANY		= 0,
	DOMAIN_BUS_WIRED,
	DOMAIN_BUS_GENERIC_MSI,
	DOMAIN_BUS_PCI_MSI,
	DOMAIN_BUS_PLATFORM_MSI,
	DOMAIN_BUS_NEXUS,
	DOMAIN_BUS_IPI,
	DOMAIN_BUS_FSL_MC_MSI,
	DOMAIN_BUS_TI_SCI_INTA_MSI,
	DOMAIN_BUS_WAKEUP,
	DOMAIN_BUS_VMD_MSI,
पूर्ण;

/**
 * काष्ठा irq_करोमुख्य_ops - Methods क्रम irq_करोमुख्य objects
 * @match: Match an पूर्णांकerrupt controller device node to a host, वापसs
 *         1 on a match
 * @map: Create or update a mapping between a भव irq number and a hw
 *       irq number. This is called only once क्रम a given mapping.
 * @unmap: Dispose of such a mapping
 * @xlate: Given a device tree node and पूर्णांकerrupt specअगरier, decode
 *         the hardware irq number and linux irq type value.
 *
 * Functions below are provided by the driver and called whenever a new mapping
 * is created or an old mapping is disposed. The driver can then proceed to
 * whatever पूर्णांकernal data काष्ठाures management is required. It also needs
 * to setup the irq_desc when वापसing from map().
 */
काष्ठा irq_करोमुख्य_ops अणु
	पूर्णांक (*match)(काष्ठा irq_करोमुख्य *d, काष्ठा device_node *node,
		     क्रमागत irq_करोमुख्य_bus_token bus_token);
	पूर्णांक (*select)(काष्ठा irq_करोमुख्य *d, काष्ठा irq_fwspec *fwspec,
		      क्रमागत irq_करोमुख्य_bus_token bus_token);
	पूर्णांक (*map)(काष्ठा irq_करोमुख्य *d, अचिन्हित पूर्णांक virq, irq_hw_number_t hw);
	व्योम (*unmap)(काष्ठा irq_करोमुख्य *d, अचिन्हित पूर्णांक virq);
	पूर्णांक (*xlate)(काष्ठा irq_करोमुख्य *d, काष्ठा device_node *node,
		     स्थिर u32 *पूर्णांकspec, अचिन्हित पूर्णांक पूर्णांकsize,
		     अचिन्हित दीर्घ *out_hwirq, अचिन्हित पूर्णांक *out_type);
#अगर_घोषित	CONFIG_IRQ_DOMAIN_HIERARCHY
	/* extended V2 पूर्णांकerfaces to support hierarchy irq_करोमुख्यs */
	पूर्णांक (*alloc)(काष्ठा irq_करोमुख्य *d, अचिन्हित पूर्णांक virq,
		     अचिन्हित पूर्णांक nr_irqs, व्योम *arg);
	व्योम (*मुक्त)(काष्ठा irq_करोमुख्य *d, अचिन्हित पूर्णांक virq,
		     अचिन्हित पूर्णांक nr_irqs);
	पूर्णांक (*activate)(काष्ठा irq_करोमुख्य *d, काष्ठा irq_data *irqd, bool reserve);
	व्योम (*deactivate)(काष्ठा irq_करोमुख्य *d, काष्ठा irq_data *irq_data);
	पूर्णांक (*translate)(काष्ठा irq_करोमुख्य *d, काष्ठा irq_fwspec *fwspec,
			 अचिन्हित दीर्घ *out_hwirq, अचिन्हित पूर्णांक *out_type);
#पूर्ण_अगर
#अगर_घोषित CONFIG_GENERIC_IRQ_DEBUGFS
	व्योम (*debug_show)(काष्ठा seq_file *m, काष्ठा irq_करोमुख्य *d,
			   काष्ठा irq_data *irqd, पूर्णांक ind);
#पूर्ण_अगर
पूर्ण;

बाह्य काष्ठा irq_करोमुख्य_ops irq_generic_chip_ops;

काष्ठा irq_करोमुख्य_chip_generic;

/**
 * काष्ठा irq_करोमुख्य - Hardware पूर्णांकerrupt number translation object
 * @link: Element in global irq_करोमुख्य list.
 * @name: Name of पूर्णांकerrupt करोमुख्य
 * @ops: poपूर्णांकer to irq_करोमुख्य methods
 * @host_data: निजी data poपूर्णांकer क्रम use by owner.  Not touched by irq_करोमुख्य
 *             core code.
 * @flags: host per irq_करोमुख्य flags
 * @mapcount: The number of mapped पूर्णांकerrupts
 *
 * Optional elements
 * @fwnode: Poपूर्णांकer to firmware node associated with the irq_करोमुख्य. Pretty easy
 *          to swap it क्रम the of_node via the irq_करोमुख्य_get_of_node accessor
 * @gc: Poपूर्णांकer to a list of generic chips. There is a helper function क्रम
 *      setting up one or more generic chips क्रम पूर्णांकerrupt controllers
 *      drivers using the generic chip library which uses this poपूर्णांकer.
 * @parent: Poपूर्णांकer to parent irq_करोमुख्य to support hierarchy irq_करोमुख्यs
 *
 * Revmap data, used पूर्णांकernally by irq_करोमुख्य
 * @revmap_direct_max_irq: The largest hwirq that can be set क्रम controllers that
 *                         support direct mapping
 * @revmap_size: Size of the linear map table @linear_revmap[]
 * @revmap_tree: Radix map tree क्रम hwirqs that करोn't fit in the linear map
 * @linear_revmap: Linear table of hwirq->virq reverse mappings
 */
काष्ठा irq_करोमुख्य अणु
	काष्ठा list_head link;
	स्थिर अक्षर *name;
	स्थिर काष्ठा irq_करोमुख्य_ops *ops;
	व्योम *host_data;
	अचिन्हित पूर्णांक flags;
	अचिन्हित पूर्णांक mapcount;

	/* Optional data */
	काष्ठा fwnode_handle *fwnode;
	क्रमागत irq_करोमुख्य_bus_token bus_token;
	काष्ठा irq_करोमुख्य_chip_generic *gc;
#अगर_घोषित	CONFIG_IRQ_DOMAIN_HIERARCHY
	काष्ठा irq_करोमुख्य *parent;
#पूर्ण_अगर

	/* reverse map data. The linear map माला_लो appended to the irq_करोमुख्य */
	irq_hw_number_t hwirq_max;
	अचिन्हित पूर्णांक revmap_direct_max_irq;
	अचिन्हित पूर्णांक revmap_size;
	काष्ठा radix_tree_root revmap_tree;
	काष्ठा mutex revmap_tree_mutex;
	अचिन्हित पूर्णांक linear_revmap[];
पूर्ण;

/* Irq करोमुख्य flags */
क्रमागत अणु
	/* Irq करोमुख्य is hierarchical */
	IRQ_DOMAIN_FLAG_HIERARCHY	= (1 << 0),

	/* Irq करोमुख्य name was allocated in __irq_करोमुख्य_add() */
	IRQ_DOMAIN_NAME_ALLOCATED	= (1 << 1),

	/* Irq करोमुख्य is an IPI करोमुख्य with virq per cpu */
	IRQ_DOMAIN_FLAG_IPI_PER_CPU	= (1 << 2),

	/* Irq करोमुख्य is an IPI करोमुख्य with single virq */
	IRQ_DOMAIN_FLAG_IPI_SINGLE	= (1 << 3),

	/* Irq करोमुख्य implements MSIs */
	IRQ_DOMAIN_FLAG_MSI		= (1 << 4),

	/* Irq करोमुख्य implements MSI remapping */
	IRQ_DOMAIN_FLAG_MSI_REMAP	= (1 << 5),

	/*
	 * Quirk to handle MSI implementations which करो not provide
	 * masking. Currently known to affect x86, but partially
	 * handled in core code.
	 */
	IRQ_DOMAIN_MSI_NOMASK_QUIRK	= (1 << 6),

	/*
	 * Flags starting from IRQ_DOMAIN_FLAG_NONCORE are reserved
	 * क्रम implementation specअगरic purposes and ignored by the
	 * core code.
	 */
	IRQ_DOMAIN_FLAG_NONCORE		= (1 << 16),
पूर्ण;

अटल अंतरभूत काष्ठा device_node *irq_करोमुख्य_get_of_node(काष्ठा irq_करोमुख्य *d)
अणु
	वापस to_of_node(d->fwnode);
पूर्ण

#अगर_घोषित CONFIG_IRQ_DOMAIN
काष्ठा fwnode_handle *__irq_करोमुख्य_alloc_fwnode(अचिन्हित पूर्णांक type, पूर्णांक id,
						स्थिर अक्षर *name, phys_addr_t *pa);

क्रमागत अणु
	IRQCHIP_FWNODE_REAL,
	IRQCHIP_FWNODE_NAMED,
	IRQCHIP_FWNODE_NAMED_ID,
पूर्ण;

अटल अंतरभूत
काष्ठा fwnode_handle *irq_करोमुख्य_alloc_named_fwnode(स्थिर अक्षर *name)
अणु
	वापस __irq_करोमुख्य_alloc_fwnode(IRQCHIP_FWNODE_NAMED, 0, name, शून्य);
पूर्ण

अटल अंतरभूत
काष्ठा fwnode_handle *irq_करोमुख्य_alloc_named_id_fwnode(स्थिर अक्षर *name, पूर्णांक id)
अणु
	वापस __irq_करोमुख्य_alloc_fwnode(IRQCHIP_FWNODE_NAMED_ID, id, name,
					 शून्य);
पूर्ण

अटल अंतरभूत काष्ठा fwnode_handle *irq_करोमुख्य_alloc_fwnode(phys_addr_t *pa)
अणु
	वापस __irq_करोमुख्य_alloc_fwnode(IRQCHIP_FWNODE_REAL, 0, शून्य, pa);
पूर्ण

व्योम irq_करोमुख्य_मुक्त_fwnode(काष्ठा fwnode_handle *fwnode);
काष्ठा irq_करोमुख्य *__irq_करोमुख्य_add(काष्ठा fwnode_handle *fwnode, पूर्णांक size,
				    irq_hw_number_t hwirq_max, पूर्णांक direct_max,
				    स्थिर काष्ठा irq_करोमुख्य_ops *ops,
				    व्योम *host_data);
काष्ठा irq_करोमुख्य *irq_करोमुख्य_create_simple(काष्ठा fwnode_handle *fwnode,
					    अचिन्हित पूर्णांक size,
					    अचिन्हित पूर्णांक first_irq,
					    स्थिर काष्ठा irq_करोमुख्य_ops *ops,
					    व्योम *host_data);
काष्ठा irq_करोमुख्य *irq_करोमुख्य_add_legacy(काष्ठा device_node *of_node,
					 अचिन्हित पूर्णांक size,
					 अचिन्हित पूर्णांक first_irq,
					 irq_hw_number_t first_hwirq,
					 स्थिर काष्ठा irq_करोमुख्य_ops *ops,
					 व्योम *host_data);
काष्ठा irq_करोमुख्य *irq_करोमुख्य_create_legacy(काष्ठा fwnode_handle *fwnode,
					    अचिन्हित पूर्णांक size,
					    अचिन्हित पूर्णांक first_irq,
					    irq_hw_number_t first_hwirq,
					    स्थिर काष्ठा irq_करोमुख्य_ops *ops,
					    व्योम *host_data);
बाह्य काष्ठा irq_करोमुख्य *irq_find_matching_fwspec(काष्ठा irq_fwspec *fwspec,
						   क्रमागत irq_करोमुख्य_bus_token bus_token);
बाह्य bool irq_करोमुख्य_check_msi_remap(व्योम);
बाह्य व्योम irq_set_शेष_host(काष्ठा irq_करोमुख्य *host);
बाह्य काष्ठा irq_करोमुख्य *irq_get_शेष_host(व्योम);
बाह्य पूर्णांक irq_करोमुख्य_alloc_descs(पूर्णांक virq, अचिन्हित पूर्णांक nr_irqs,
				  irq_hw_number_t hwirq, पूर्णांक node,
				  स्थिर काष्ठा irq_affinity_desc *affinity);

अटल अंतरभूत काष्ठा fwnode_handle *of_node_to_fwnode(काष्ठा device_node *node)
अणु
	वापस node ? &node->fwnode : शून्य;
पूर्ण

बाह्य स्थिर काष्ठा fwnode_operations irqchip_fwnode_ops;

अटल अंतरभूत bool is_fwnode_irqchip(काष्ठा fwnode_handle *fwnode)
अणु
	वापस fwnode && fwnode->ops == &irqchip_fwnode_ops;
पूर्ण

बाह्य व्योम irq_करोमुख्य_update_bus_token(काष्ठा irq_करोमुख्य *करोमुख्य,
					क्रमागत irq_करोमुख्य_bus_token bus_token);

अटल अंतरभूत
काष्ठा irq_करोमुख्य *irq_find_matching_fwnode(काष्ठा fwnode_handle *fwnode,
					    क्रमागत irq_करोमुख्य_bus_token bus_token)
अणु
	काष्ठा irq_fwspec fwspec = अणु
		.fwnode = fwnode,
	पूर्ण;

	वापस irq_find_matching_fwspec(&fwspec, bus_token);
पूर्ण

अटल अंतरभूत काष्ठा irq_करोमुख्य *irq_find_matching_host(काष्ठा device_node *node,
							क्रमागत irq_करोमुख्य_bus_token bus_token)
अणु
	वापस irq_find_matching_fwnode(of_node_to_fwnode(node), bus_token);
पूर्ण

अटल अंतरभूत काष्ठा irq_करोमुख्य *irq_find_host(काष्ठा device_node *node)
अणु
	काष्ठा irq_करोमुख्य *d;

	d = irq_find_matching_host(node, DOMAIN_BUS_WIRED);
	अगर (!d)
		d = irq_find_matching_host(node, DOMAIN_BUS_ANY);

	वापस d;
पूर्ण

अटल अंतरभूत काष्ठा irq_करोमुख्य *irq_करोमुख्य_add_simple(काष्ठा device_node *of_node,
						       अचिन्हित पूर्णांक size,
						       अचिन्हित पूर्णांक first_irq,
						       स्थिर काष्ठा irq_करोमुख्य_ops *ops,
						       व्योम *host_data)
अणु
	वापस irq_करोमुख्य_create_simple(of_node_to_fwnode(of_node), size, first_irq, ops, host_data);
पूर्ण

/**
 * irq_करोमुख्य_add_linear() - Allocate and रेजिस्टर a linear revmap irq_करोमुख्य.
 * @of_node: poपूर्णांकer to पूर्णांकerrupt controller's device tree node.
 * @size: Number of पूर्णांकerrupts in the करोमुख्य.
 * @ops: map/unmap करोमुख्य callbacks
 * @host_data: Controller निजी data poपूर्णांकer
 */
अटल अंतरभूत काष्ठा irq_करोमुख्य *irq_करोमुख्य_add_linear(काष्ठा device_node *of_node,
					 अचिन्हित पूर्णांक size,
					 स्थिर काष्ठा irq_करोमुख्य_ops *ops,
					 व्योम *host_data)
अणु
	वापस __irq_करोमुख्य_add(of_node_to_fwnode(of_node), size, size, 0, ops, host_data);
पूर्ण
अटल अंतरभूत काष्ठा irq_करोमुख्य *irq_करोमुख्य_add_nomap(काष्ठा device_node *of_node,
					 अचिन्हित पूर्णांक max_irq,
					 स्थिर काष्ठा irq_करोमुख्य_ops *ops,
					 व्योम *host_data)
अणु
	वापस __irq_करोमुख्य_add(of_node_to_fwnode(of_node), 0, max_irq, max_irq, ops, host_data);
पूर्ण
अटल अंतरभूत काष्ठा irq_करोमुख्य *irq_करोमुख्य_add_legacy_isa(
				काष्ठा device_node *of_node,
				स्थिर काष्ठा irq_करोमुख्य_ops *ops,
				व्योम *host_data)
अणु
	वापस irq_करोमुख्य_add_legacy(of_node, NUM_ISA_INTERRUPTS, 0, 0, ops,
				     host_data);
पूर्ण
अटल अंतरभूत काष्ठा irq_करोमुख्य *irq_करोमुख्य_add_tree(काष्ठा device_node *of_node,
					 स्थिर काष्ठा irq_करोमुख्य_ops *ops,
					 व्योम *host_data)
अणु
	वापस __irq_करोमुख्य_add(of_node_to_fwnode(of_node), 0, ~0, 0, ops, host_data);
पूर्ण

अटल अंतरभूत काष्ठा irq_करोमुख्य *irq_करोमुख्य_create_linear(काष्ठा fwnode_handle *fwnode,
					 अचिन्हित पूर्णांक size,
					 स्थिर काष्ठा irq_करोमुख्य_ops *ops,
					 व्योम *host_data)
अणु
	वापस __irq_करोमुख्य_add(fwnode, size, size, 0, ops, host_data);
पूर्ण

अटल अंतरभूत काष्ठा irq_करोमुख्य *irq_करोमुख्य_create_tree(काष्ठा fwnode_handle *fwnode,
					 स्थिर काष्ठा irq_करोमुख्य_ops *ops,
					 व्योम *host_data)
अणु
	वापस __irq_करोमुख्य_add(fwnode, 0, ~0, 0, ops, host_data);
पूर्ण

बाह्य व्योम irq_करोमुख्य_हटाओ(काष्ठा irq_करोमुख्य *host);

बाह्य पूर्णांक irq_करोमुख्य_associate(काष्ठा irq_करोमुख्य *करोमुख्य, अचिन्हित पूर्णांक irq,
					irq_hw_number_t hwirq);
बाह्य व्योम irq_करोमुख्य_associate_many(काष्ठा irq_करोमुख्य *करोमुख्य,
				      अचिन्हित पूर्णांक irq_base,
				      irq_hw_number_t hwirq_base, पूर्णांक count);

बाह्य अचिन्हित पूर्णांक irq_create_mapping_affinity(काष्ठा irq_करोमुख्य *host,
				      irq_hw_number_t hwirq,
				      स्थिर काष्ठा irq_affinity_desc *affinity);
बाह्य अचिन्हित पूर्णांक irq_create_fwspec_mapping(काष्ठा irq_fwspec *fwspec);
बाह्य व्योम irq_dispose_mapping(अचिन्हित पूर्णांक virq);

अटल अंतरभूत अचिन्हित पूर्णांक irq_create_mapping(काष्ठा irq_करोमुख्य *host,
					      irq_hw_number_t hwirq)
अणु
	वापस irq_create_mapping_affinity(host, hwirq, शून्य);
पूर्ण


/**
 * irq_linear_revmap() - Find a linux irq from a hw irq number.
 * @करोमुख्य: करोमुख्य owning this hardware पूर्णांकerrupt
 * @hwirq: hardware irq number in that करोमुख्य space
 *
 * This is a fast path alternative to irq_find_mapping() that can be
 * called directly by irq controller code to save a handful of
 * inकाष्ठाions. It is always safe to call, but won't find irqs mapped
 * using the radix tree.
 */
अटल अंतरभूत अचिन्हित पूर्णांक irq_linear_revmap(काष्ठा irq_करोमुख्य *करोमुख्य,
					     irq_hw_number_t hwirq)
अणु
	वापस hwirq < करोमुख्य->revmap_size ? करोमुख्य->linear_revmap[hwirq] : 0;
पूर्ण
बाह्य अचिन्हित पूर्णांक irq_find_mapping(काष्ठा irq_करोमुख्य *host,
				     irq_hw_number_t hwirq);
बाह्य अचिन्हित पूर्णांक irq_create_direct_mapping(काष्ठा irq_करोमुख्य *host);

बाह्य स्थिर काष्ठा irq_करोमुख्य_ops irq_करोमुख्य_simple_ops;

/* stock xlate functions */
पूर्णांक irq_करोमुख्य_xlate_onecell(काष्ठा irq_करोमुख्य *d, काष्ठा device_node *ctrlr,
			स्थिर u32 *पूर्णांकspec, अचिन्हित पूर्णांक पूर्णांकsize,
			irq_hw_number_t *out_hwirq, अचिन्हित पूर्णांक *out_type);
पूर्णांक irq_करोमुख्य_xlate_twocell(काष्ठा irq_करोमुख्य *d, काष्ठा device_node *ctrlr,
			स्थिर u32 *पूर्णांकspec, अचिन्हित पूर्णांक पूर्णांकsize,
			irq_hw_number_t *out_hwirq, अचिन्हित पूर्णांक *out_type);
पूर्णांक irq_करोमुख्य_xlate_onetwocell(काष्ठा irq_करोमुख्य *d, काष्ठा device_node *ctrlr,
			स्थिर u32 *पूर्णांकspec, अचिन्हित पूर्णांक पूर्णांकsize,
			irq_hw_number_t *out_hwirq, अचिन्हित पूर्णांक *out_type);

पूर्णांक irq_करोमुख्य_translate_twocell(काष्ठा irq_करोमुख्य *d,
				 काष्ठा irq_fwspec *fwspec,
				 अचिन्हित दीर्घ *out_hwirq,
				 अचिन्हित पूर्णांक *out_type);

पूर्णांक irq_करोमुख्य_translate_onecell(काष्ठा irq_करोमुख्य *d,
				 काष्ठा irq_fwspec *fwspec,
				 अचिन्हित दीर्घ *out_hwirq,
				 अचिन्हित पूर्णांक *out_type);

/* IPI functions */
पूर्णांक irq_reserve_ipi(काष्ठा irq_करोमुख्य *करोमुख्य, स्थिर काष्ठा cpumask *dest);
पूर्णांक irq_destroy_ipi(अचिन्हित पूर्णांक irq, स्थिर काष्ठा cpumask *dest);

/* V2 पूर्णांकerfaces to support hierarchy IRQ करोमुख्यs. */
बाह्य काष्ठा irq_data *irq_करोमुख्य_get_irq_data(काष्ठा irq_करोमुख्य *करोमुख्य,
						अचिन्हित पूर्णांक virq);
बाह्य व्योम irq_करोमुख्य_set_info(काष्ठा irq_करोमुख्य *करोमुख्य, अचिन्हित पूर्णांक virq,
				irq_hw_number_t hwirq, काष्ठा irq_chip *chip,
				व्योम *chip_data, irq_flow_handler_t handler,
				व्योम *handler_data, स्थिर अक्षर *handler_name);
बाह्य व्योम irq_करोमुख्य_reset_irq_data(काष्ठा irq_data *irq_data);
#अगर_घोषित	CONFIG_IRQ_DOMAIN_HIERARCHY
बाह्य काष्ठा irq_करोमुख्य *irq_करोमुख्य_create_hierarchy(काष्ठा irq_करोमुख्य *parent,
			अचिन्हित पूर्णांक flags, अचिन्हित पूर्णांक size,
			काष्ठा fwnode_handle *fwnode,
			स्थिर काष्ठा irq_करोमुख्य_ops *ops, व्योम *host_data);

अटल अंतरभूत काष्ठा irq_करोमुख्य *irq_करोमुख्य_add_hierarchy(काष्ठा irq_करोमुख्य *parent,
					    अचिन्हित पूर्णांक flags,
					    अचिन्हित पूर्णांक size,
					    काष्ठा device_node *node,
					    स्थिर काष्ठा irq_करोमुख्य_ops *ops,
					    व्योम *host_data)
अणु
	वापस irq_करोमुख्य_create_hierarchy(parent, flags, size,
					   of_node_to_fwnode(node),
					   ops, host_data);
पूर्ण

बाह्य पूर्णांक __irq_करोमुख्य_alloc_irqs(काष्ठा irq_करोमुख्य *करोमुख्य, पूर्णांक irq_base,
				   अचिन्हित पूर्णांक nr_irqs, पूर्णांक node, व्योम *arg,
				   bool पुनः_स्मृति,
				   स्थिर काष्ठा irq_affinity_desc *affinity);
बाह्य व्योम irq_करोमुख्य_मुक्त_irqs(अचिन्हित पूर्णांक virq, अचिन्हित पूर्णांक nr_irqs);
बाह्य पूर्णांक irq_करोमुख्य_activate_irq(काष्ठा irq_data *irq_data, bool early);
बाह्य व्योम irq_करोमुख्य_deactivate_irq(काष्ठा irq_data *irq_data);

अटल अंतरभूत पूर्णांक irq_करोमुख्य_alloc_irqs(काष्ठा irq_करोमुख्य *करोमुख्य,
			अचिन्हित पूर्णांक nr_irqs, पूर्णांक node, व्योम *arg)
अणु
	वापस __irq_करोमुख्य_alloc_irqs(करोमुख्य, -1, nr_irqs, node, arg, false,
				       शून्य);
पूर्ण

बाह्य पूर्णांक irq_करोमुख्य_alloc_irqs_hierarchy(काष्ठा irq_करोमुख्य *करोमुख्य,
					   अचिन्हित पूर्णांक irq_base,
					   अचिन्हित पूर्णांक nr_irqs, व्योम *arg);
बाह्य पूर्णांक irq_करोमुख्य_set_hwirq_and_chip(काष्ठा irq_करोमुख्य *करोमुख्य,
					 अचिन्हित पूर्णांक virq,
					 irq_hw_number_t hwirq,
					 काष्ठा irq_chip *chip,
					 व्योम *chip_data);
बाह्य व्योम irq_करोमुख्य_मुक्त_irqs_common(काष्ठा irq_करोमुख्य *करोमुख्य,
					अचिन्हित पूर्णांक virq,
					अचिन्हित पूर्णांक nr_irqs);
बाह्य व्योम irq_करोमुख्य_मुक्त_irqs_top(काष्ठा irq_करोमुख्य *करोमुख्य,
				     अचिन्हित पूर्णांक virq, अचिन्हित पूर्णांक nr_irqs);

बाह्य पूर्णांक irq_करोमुख्य_push_irq(काष्ठा irq_करोमुख्य *करोमुख्य, पूर्णांक virq, व्योम *arg);
बाह्य पूर्णांक irq_करोमुख्य_pop_irq(काष्ठा irq_करोमुख्य *करोमुख्य, पूर्णांक virq);

बाह्य पूर्णांक irq_करोमुख्य_alloc_irqs_parent(काष्ठा irq_करोमुख्य *करोमुख्य,
					अचिन्हित पूर्णांक irq_base,
					अचिन्हित पूर्णांक nr_irqs, व्योम *arg);

बाह्य व्योम irq_करोमुख्य_मुक्त_irqs_parent(काष्ठा irq_करोमुख्य *करोमुख्य,
					अचिन्हित पूर्णांक irq_base,
					अचिन्हित पूर्णांक nr_irqs);

बाह्य पूर्णांक irq_करोमुख्य_disconnect_hierarchy(काष्ठा irq_करोमुख्य *करोमुख्य,
					   अचिन्हित पूर्णांक virq);

अटल अंतरभूत bool irq_करोमुख्य_is_hierarchy(काष्ठा irq_करोमुख्य *करोमुख्य)
अणु
	वापस करोमुख्य->flags & IRQ_DOMAIN_FLAG_HIERARCHY;
पूर्ण

अटल अंतरभूत bool irq_करोमुख्य_is_ipi(काष्ठा irq_करोमुख्य *करोमुख्य)
अणु
	वापस करोमुख्य->flags &
		(IRQ_DOMAIN_FLAG_IPI_PER_CPU | IRQ_DOMAIN_FLAG_IPI_SINGLE);
पूर्ण

अटल अंतरभूत bool irq_करोमुख्य_is_ipi_per_cpu(काष्ठा irq_करोमुख्य *करोमुख्य)
अणु
	वापस करोमुख्य->flags & IRQ_DOMAIN_FLAG_IPI_PER_CPU;
पूर्ण

अटल अंतरभूत bool irq_करोमुख्य_is_ipi_single(काष्ठा irq_करोमुख्य *करोमुख्य)
अणु
	वापस करोमुख्य->flags & IRQ_DOMAIN_FLAG_IPI_SINGLE;
पूर्ण

अटल अंतरभूत bool irq_करोमुख्य_is_msi(काष्ठा irq_करोमुख्य *करोमुख्य)
अणु
	वापस करोमुख्य->flags & IRQ_DOMAIN_FLAG_MSI;
पूर्ण

अटल अंतरभूत bool irq_करोमुख्य_is_msi_remap(काष्ठा irq_करोमुख्य *करोमुख्य)
अणु
	वापस करोमुख्य->flags & IRQ_DOMAIN_FLAG_MSI_REMAP;
पूर्ण

बाह्य bool irq_करोमुख्य_hierarchical_is_msi_remap(काष्ठा irq_करोमुख्य *करोमुख्य);

#अन्यथा	/* CONFIG_IRQ_DOMAIN_HIERARCHY */
अटल अंतरभूत पूर्णांक irq_करोमुख्य_alloc_irqs(काष्ठा irq_करोमुख्य *करोमुख्य,
			अचिन्हित पूर्णांक nr_irqs, पूर्णांक node, व्योम *arg)
अणु
	वापस -1;
पूर्ण

अटल अंतरभूत व्योम irq_करोमुख्य_मुक्त_irqs(अचिन्हित पूर्णांक virq,
					अचिन्हित पूर्णांक nr_irqs) अणु पूर्ण

अटल अंतरभूत bool irq_करोमुख्य_is_hierarchy(काष्ठा irq_करोमुख्य *करोमुख्य)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत bool irq_करोमुख्य_is_ipi(काष्ठा irq_करोमुख्य *करोमुख्य)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत bool irq_करोमुख्य_is_ipi_per_cpu(काष्ठा irq_करोमुख्य *करोमुख्य)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत bool irq_करोमुख्य_is_ipi_single(काष्ठा irq_करोमुख्य *करोमुख्य)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत bool irq_करोमुख्य_is_msi(काष्ठा irq_करोमुख्य *करोमुख्य)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत bool irq_करोमुख्य_is_msi_remap(काष्ठा irq_करोमुख्य *करोमुख्य)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत bool
irq_करोमुख्य_hierarchical_is_msi_remap(काष्ठा irq_करोमुख्य *करोमुख्य)
अणु
	वापस false;
पूर्ण
#पूर्ण_अगर	/* CONFIG_IRQ_DOMAIN_HIERARCHY */

#अन्यथा /* CONFIG_IRQ_DOMAIN */
अटल अंतरभूत व्योम irq_dispose_mapping(अचिन्हित पूर्णांक virq) अणु पूर्ण
अटल अंतरभूत काष्ठा irq_करोमुख्य *irq_find_matching_fwnode(
	काष्ठा fwnode_handle *fwnode, क्रमागत irq_करोमुख्य_bus_token bus_token)
अणु
	वापस शून्य;
पूर्ण
अटल अंतरभूत bool irq_करोमुख्य_check_msi_remap(व्योम)
अणु
	वापस false;
पूर्ण
#पूर्ण_अगर /* !CONFIG_IRQ_DOMAIN */

#पूर्ण_अगर /* _LINUX_IRQDOMAIN_H */
