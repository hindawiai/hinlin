<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित LINUX_MSI_H
#घोषणा LINUX_MSI_H

#समावेश <linux/kobject.h>
#समावेश <linux/list.h>
#समावेश <यंत्र/msi.h>

/* Dummy shaकरोw काष्ठाures अगर an architecture करोes not define them */
#अगर_अघोषित arch_msi_msg_addr_lo
प्रकार काष्ठा arch_msi_msg_addr_lo अणु
	u32	address_lo;
पूर्ण __attribute__ ((packed)) arch_msi_msg_addr_lo_t;
#पूर्ण_अगर

#अगर_अघोषित arch_msi_msg_addr_hi
प्रकार काष्ठा arch_msi_msg_addr_hi अणु
	u32	address_hi;
पूर्ण __attribute__ ((packed)) arch_msi_msg_addr_hi_t;
#पूर्ण_अगर

#अगर_अघोषित arch_msi_msg_data
प्रकार काष्ठा arch_msi_msg_data अणु
	u32	data;
पूर्ण __attribute__ ((packed)) arch_msi_msg_data_t;
#पूर्ण_अगर

/**
 * msi_msg - Representation of a MSI message
 * @address_lo:		Low 32 bits of msi message address
 * @arch_addrlo:	Architecture specअगरic shaकरोw of @address_lo
 * @address_hi:		High 32 bits of msi message address
 *			(only used when device supports it)
 * @arch_addrhi:	Architecture specअगरic shaकरोw of @address_hi
 * @data:		MSI message data (usually 16 bits)
 * @arch_data:		Architecture specअगरic shaकरोw of @data
 */
काष्ठा msi_msg अणु
	जोड़ अणु
		u32			address_lo;
		arch_msi_msg_addr_lo_t	arch_addr_lo;
	पूर्ण;
	जोड़ अणु
		u32			address_hi;
		arch_msi_msg_addr_hi_t	arch_addr_hi;
	पूर्ण;
	जोड़ अणु
		u32			data;
		arch_msi_msg_data_t	arch_data;
	पूर्ण;
पूर्ण;

बाह्य पूर्णांक pci_msi_ignore_mask;
/* Helper functions */
काष्ठा irq_data;
काष्ठा msi_desc;
काष्ठा pci_dev;
काष्ठा platक्रमm_msi_priv_data;
व्योम __get_cached_msi_msg(काष्ठा msi_desc *entry, काष्ठा msi_msg *msg);
#अगर_घोषित CONFIG_GENERIC_MSI_IRQ
व्योम get_cached_msi_msg(अचिन्हित पूर्णांक irq, काष्ठा msi_msg *msg);
#अन्यथा
अटल अंतरभूत व्योम get_cached_msi_msg(अचिन्हित पूर्णांक irq, काष्ठा msi_msg *msg)
अणु
पूर्ण
#पूर्ण_अगर

प्रकार व्योम (*irq_ग_लिखो_msi_msg_t)(काष्ठा msi_desc *desc,
				    काष्ठा msi_msg *msg);

/**
 * platक्रमm_msi_desc - Platक्रमm device specअगरic msi descriptor data
 * @msi_priv_data:	Poपूर्णांकer to platक्रमm निजी data
 * @msi_index:		The index of the MSI descriptor क्रम multi MSI
 */
काष्ठा platक्रमm_msi_desc अणु
	काष्ठा platक्रमm_msi_priv_data	*msi_priv_data;
	u16				msi_index;
पूर्ण;

/**
 * fsl_mc_msi_desc - FSL-MC device specअगरic msi descriptor data
 * @msi_index:		The index of the MSI descriptor
 */
काष्ठा fsl_mc_msi_desc अणु
	u16				msi_index;
पूर्ण;

/**
 * ti_sci_पूर्णांकa_msi_desc - TISCI based INTA specअगरic msi descriptor data
 * @dev_index: TISCI device index
 */
काष्ठा ti_sci_पूर्णांकa_msi_desc अणु
	u16	dev_index;
पूर्ण;

/**
 * काष्ठा msi_desc - Descriptor काष्ठाure क्रम MSI based पूर्णांकerrupts
 * @list:	List head क्रम management
 * @irq:	The base पूर्णांकerrupt number
 * @nvec_used:	The number of vectors used
 * @dev:	Poपूर्णांकer to the device which uses this descriptor
 * @msg:	The last set MSI message cached क्रम reuse
 * @affinity:	Optional poपूर्णांकer to a cpu affinity mask क्रम this descriptor
 *
 * @ग_लिखो_msi_msg:	Callback that may be called when the MSI message
 *			address or data changes
 * @ग_लिखो_msi_msg_data:	Data parameter क्रम the callback.
 *
 * @masked:	[PCI MSI/X] Mask bits
 * @is_msix:	[PCI MSI/X] True अगर MSI-X
 * @multiple:	[PCI MSI/X] log2 num of messages allocated
 * @multi_cap:	[PCI MSI/X] log2 num of messages supported
 * @maskbit:	[PCI MSI/X] Mask-Pending bit supported?
 * @is_64:	[PCI MSI/X] Address size: 0=32bit 1=64bit
 * @entry_nr:	[PCI MSI/X] Entry which is described by this descriptor
 * @शेष_irq:[PCI MSI/X] The शेष pre-asचिन्हित non-MSI irq
 * @mask_pos:	[PCI MSI]   Mask रेजिस्टर position
 * @mask_base:	[PCI MSI-X] Mask रेजिस्टर base address
 * @platक्रमm:	[platक्रमm]  Platक्रमm device specअगरic msi descriptor data
 * @fsl_mc:	[fsl-mc]    FSL MC device specअगरic msi descriptor data
 * @पूर्णांकa:	[INTA]	    TISCI based INTA specअगरic msi descriptor data
 */
काष्ठा msi_desc अणु
	/* Shared device/bus type independent data */
	काष्ठा list_head		list;
	अचिन्हित पूर्णांक			irq;
	अचिन्हित पूर्णांक			nvec_used;
	काष्ठा device			*dev;
	काष्ठा msi_msg			msg;
	काष्ठा irq_affinity_desc	*affinity;
#अगर_घोषित CONFIG_IRQ_MSI_IOMMU
	स्थिर व्योम			*iommu_cookie;
#पूर्ण_अगर

	व्योम (*ग_लिखो_msi_msg)(काष्ठा msi_desc *entry, व्योम *data);
	व्योम *ग_लिखो_msi_msg_data;

	जोड़ अणु
		/* PCI MSI/X specअगरic data */
		काष्ठा अणु
			u32 masked;
			काष्ठा अणु
				u8	is_msix		: 1;
				u8	multiple	: 3;
				u8	multi_cap	: 3;
				u8	maskbit		: 1;
				u8	is_64		: 1;
				u8	is_भव	: 1;
				u16	entry_nr;
				अचिन्हित शेष_irq;
			पूर्ण msi_attrib;
			जोड़ अणु
				u8	mask_pos;
				व्योम __iomem *mask_base;
			पूर्ण;
		पूर्ण;

		/*
		 * Non PCI variants add their data काष्ठाure here. New
		 * entries need to use a named काष्ठाure. We want
		 * proper name spaces क्रम this. The PCI part is
		 * anonymous क्रम now as it would require an immediate
		 * tree wide cleanup.
		 */
		काष्ठा platक्रमm_msi_desc platक्रमm;
		काष्ठा fsl_mc_msi_desc fsl_mc;
		काष्ठा ti_sci_पूर्णांकa_msi_desc पूर्णांकa;
	पूर्ण;
पूर्ण;

/* Helpers to hide काष्ठा msi_desc implementation details */
#घोषणा msi_desc_to_dev(desc)		((desc)->dev)
#घोषणा dev_to_msi_list(dev)		(&(dev)->msi_list)
#घोषणा first_msi_entry(dev)		\
	list_first_entry(dev_to_msi_list((dev)), काष्ठा msi_desc, list)
#घोषणा क्रम_each_msi_entry(desc, dev)	\
	list_क्रम_each_entry((desc), dev_to_msi_list((dev)), list)
#घोषणा क्रम_each_msi_entry_safe(desc, पंचांगp, dev)	\
	list_क्रम_each_entry_safe((desc), (पंचांगp), dev_to_msi_list((dev)), list)
#घोषणा क्रम_each_msi_vector(desc, __irq, dev)				\
	क्रम_each_msi_entry((desc), (dev))				\
		अगर ((desc)->irq)					\
			क्रम (__irq = (desc)->irq;			\
			     __irq < ((desc)->irq + (desc)->nvec_used);	\
			     __irq++)

#अगर_घोषित CONFIG_IRQ_MSI_IOMMU
अटल अंतरभूत स्थिर व्योम *msi_desc_get_iommu_cookie(काष्ठा msi_desc *desc)
अणु
	वापस desc->iommu_cookie;
पूर्ण

अटल अंतरभूत व्योम msi_desc_set_iommu_cookie(काष्ठा msi_desc *desc,
					     स्थिर व्योम *iommu_cookie)
अणु
	desc->iommu_cookie = iommu_cookie;
पूर्ण
#अन्यथा
अटल अंतरभूत स्थिर व्योम *msi_desc_get_iommu_cookie(काष्ठा msi_desc *desc)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत व्योम msi_desc_set_iommu_cookie(काष्ठा msi_desc *desc,
					     स्थिर व्योम *iommu_cookie)
अणु
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_PCI_MSI
#घोषणा first_pci_msi_entry(pdev)	first_msi_entry(&(pdev)->dev)
#घोषणा क्रम_each_pci_msi_entry(desc, pdev)	\
	क्रम_each_msi_entry((desc), &(pdev)->dev)

काष्ठा pci_dev *msi_desc_to_pci_dev(काष्ठा msi_desc *desc);
व्योम *msi_desc_to_pci_sysdata(काष्ठा msi_desc *desc);
व्योम pci_ग_लिखो_msi_msg(अचिन्हित पूर्णांक irq, काष्ठा msi_msg *msg);
#अन्यथा /* CONFIG_PCI_MSI */
अटल अंतरभूत व्योम *msi_desc_to_pci_sysdata(काष्ठा msi_desc *desc)
अणु
	वापस शून्य;
पूर्ण
अटल अंतरभूत व्योम pci_ग_लिखो_msi_msg(अचिन्हित पूर्णांक irq, काष्ठा msi_msg *msg)
अणु
पूर्ण
#पूर्ण_अगर /* CONFIG_PCI_MSI */

काष्ठा msi_desc *alloc_msi_entry(काष्ठा device *dev, पूर्णांक nvec,
				 स्थिर काष्ठा irq_affinity_desc *affinity);
व्योम मुक्त_msi_entry(काष्ठा msi_desc *entry);
व्योम __pci_पढ़ो_msi_msg(काष्ठा msi_desc *entry, काष्ठा msi_msg *msg);
व्योम __pci_ग_लिखो_msi_msg(काष्ठा msi_desc *entry, काष्ठा msi_msg *msg);

u32 __pci_msix_desc_mask_irq(काष्ठा msi_desc *desc, u32 flag);
u32 __pci_msi_desc_mask_irq(काष्ठा msi_desc *desc, u32 mask, u32 flag);
व्योम pci_msi_mask_irq(काष्ठा irq_data *data);
व्योम pci_msi_unmask_irq(काष्ठा irq_data *data);

/*
 * The arch hooks to setup up msi irqs. Default functions are implemented
 * as weak symbols so that they /can/ be overriden by architecture specअगरic
 * code अगर needed. These hooks can only be enabled by the architecture.
 *
 * If CONFIG_PCI_MSI_ARCH_FALLBACKS is not selected they are replaced by
 * stubs with warnings.
 */
#अगर_घोषित CONFIG_PCI_MSI_ARCH_FALLBACKS
पूर्णांक arch_setup_msi_irq(काष्ठा pci_dev *dev, काष्ठा msi_desc *desc);
व्योम arch_tearकरोwn_msi_irq(अचिन्हित पूर्णांक irq);
पूर्णांक arch_setup_msi_irqs(काष्ठा pci_dev *dev, पूर्णांक nvec, पूर्णांक type);
व्योम arch_tearकरोwn_msi_irqs(काष्ठा pci_dev *dev);
#अन्यथा
अटल अंतरभूत पूर्णांक arch_setup_msi_irqs(काष्ठा pci_dev *dev, पूर्णांक nvec, पूर्णांक type)
अणु
	WARN_ON_ONCE(1);
	वापस -ENODEV;
पूर्ण

अटल अंतरभूत व्योम arch_tearकरोwn_msi_irqs(काष्ठा pci_dev *dev)
अणु
	WARN_ON_ONCE(1);
पूर्ण
#पूर्ण_अगर

/*
 * The restore hooks are still available as they are useful even
 * क्रम fully irq करोमुख्य based setups. Courtesy to XEN/X86.
 */
व्योम arch_restore_msi_irqs(काष्ठा pci_dev *dev);
व्योम शेष_restore_msi_irqs(काष्ठा pci_dev *dev);

#अगर_घोषित CONFIG_GENERIC_MSI_IRQ_DOMAIN

#समावेश <linux/irqhandler.h>

काष्ठा irq_करोमुख्य;
काष्ठा irq_करोमुख्य_ops;
काष्ठा irq_chip;
काष्ठा device_node;
काष्ठा fwnode_handle;
काष्ठा msi_करोमुख्य_info;

/**
 * काष्ठा msi_करोमुख्य_ops - MSI पूर्णांकerrupt करोमुख्य callbacks
 * @get_hwirq:		Retrieve the resulting hw irq number
 * @msi_init:		Doमुख्य specअगरic init function क्रम MSI पूर्णांकerrupts
 * @msi_मुक्त:		Doमुख्य specअगरic function to मुक्त a MSI पूर्णांकerrupts
 * @msi_check:		Callback क्रम verअगरication of the करोमुख्य/info/dev data
 * @msi_prepare:	Prepare the allocation of the पूर्णांकerrupts in the करोमुख्य
 * @msi_finish:		Optional callback to finalize the allocation
 * @set_desc:		Set the msi descriptor क्रम an पूर्णांकerrupt
 * @handle_error:	Optional error handler अगर the allocation fails
 * @करोमुख्य_alloc_irqs:	Optional function to override the शेष allocation
 *			function.
 * @करोमुख्य_मुक्त_irqs:	Optional function to override the शेष मुक्त
 *			function.
 *
 * @get_hwirq, @msi_init and @msi_मुक्त are callbacks used by
 * msi_create_irq_करोमुख्य() and related पूर्णांकerfaces
 *
 * @msi_check, @msi_prepare, @msi_finish, @set_desc and @handle_error
 * are callbacks used by msi_करोमुख्य_alloc_irqs() and related
 * पूर्णांकerfaces which are based on msi_desc.
 *
 * @करोमुख्य_alloc_irqs, @करोमुख्य_मुक्त_irqs can be used to override the
 * शेष allocation/मुक्त functions (__msi_करोमुख्य_alloc/मुक्त_irqs). This
 * is initially क्रम a wrapper around XENs seperate MSI universe which can't
 * be wrapped पूर्णांकo the regular irq करोमुख्यs concepts by mere mortals.  This
 * allows to universally use msi_करोमुख्य_alloc/मुक्त_irqs without having to
 * special हाल XEN all over the place.
 *
 * Contrary to other operations @करोमुख्य_alloc_irqs and @करोमुख्य_मुक्त_irqs
 * are set to the शेष implementation अगर शून्य and even when
 * MSI_FLAG_USE_DEF_DOM_OPS is not set to aव्योम अवरोधing existing users and
 * because these callbacks are obviously mandatory.
 *
 * This is NOT meant to be abused, but it can be useful to build wrappers
 * क्रम specialized MSI irq करोमुख्यs which need extra work beक्रमe and after
 * calling __msi_करोमुख्य_alloc_irqs()/__msi_करोमुख्य_मुक्त_irqs().
 */
काष्ठा msi_करोमुख्य_ops अणु
	irq_hw_number_t	(*get_hwirq)(काष्ठा msi_करोमुख्य_info *info,
				     msi_alloc_info_t *arg);
	पूर्णांक		(*msi_init)(काष्ठा irq_करोमुख्य *करोमुख्य,
				    काष्ठा msi_करोमुख्य_info *info,
				    अचिन्हित पूर्णांक virq, irq_hw_number_t hwirq,
				    msi_alloc_info_t *arg);
	व्योम		(*msi_मुक्त)(काष्ठा irq_करोमुख्य *करोमुख्य,
				    काष्ठा msi_करोमुख्य_info *info,
				    अचिन्हित पूर्णांक virq);
	पूर्णांक		(*msi_check)(काष्ठा irq_करोमुख्य *करोमुख्य,
				     काष्ठा msi_करोमुख्य_info *info,
				     काष्ठा device *dev);
	पूर्णांक		(*msi_prepare)(काष्ठा irq_करोमुख्य *करोमुख्य,
				       काष्ठा device *dev, पूर्णांक nvec,
				       msi_alloc_info_t *arg);
	व्योम		(*msi_finish)(msi_alloc_info_t *arg, पूर्णांक retval);
	व्योम		(*set_desc)(msi_alloc_info_t *arg,
				    काष्ठा msi_desc *desc);
	पूर्णांक		(*handle_error)(काष्ठा irq_करोमुख्य *करोमुख्य,
					काष्ठा msi_desc *desc, पूर्णांक error);
	पूर्णांक		(*करोमुख्य_alloc_irqs)(काष्ठा irq_करोमुख्य *करोमुख्य,
					     काष्ठा device *dev, पूर्णांक nvec);
	व्योम		(*करोमुख्य_मुक्त_irqs)(काष्ठा irq_करोमुख्य *करोमुख्य,
					    काष्ठा device *dev);
पूर्ण;

/**
 * काष्ठा msi_करोमुख्य_info - MSI पूर्णांकerrupt करोमुख्य data
 * @flags:		Flags to decribe features and capabilities
 * @ops:		The callback data काष्ठाure
 * @chip:		Optional: associated पूर्णांकerrupt chip
 * @chip_data:		Optional: associated पूर्णांकerrupt chip data
 * @handler:		Optional: associated पूर्णांकerrupt flow handler
 * @handler_data:	Optional: associated पूर्णांकerrupt flow handler data
 * @handler_name:	Optional: associated पूर्णांकerrupt flow handler name
 * @data:		Optional: करोमुख्य specअगरic data
 */
काष्ठा msi_करोमुख्य_info अणु
	u32			flags;
	काष्ठा msi_करोमुख्य_ops	*ops;
	काष्ठा irq_chip		*chip;
	व्योम			*chip_data;
	irq_flow_handler_t	handler;
	व्योम			*handler_data;
	स्थिर अक्षर		*handler_name;
	व्योम			*data;
पूर्ण;

/* Flags क्रम msi_करोमुख्य_info */
क्रमागत अणु
	/*
	 * Init non implemented ops callbacks with शेष MSI करोमुख्य
	 * callbacks.
	 */
	MSI_FLAG_USE_DEF_DOM_OPS	= (1 << 0),
	/*
	 * Init non implemented chip callbacks with शेष MSI chip
	 * callbacks.
	 */
	MSI_FLAG_USE_DEF_CHIP_OPS	= (1 << 1),
	/* Support multiple PCI MSI पूर्णांकerrupts */
	MSI_FLAG_MULTI_PCI_MSI		= (1 << 2),
	/* Support PCI MSIX पूर्णांकerrupts */
	MSI_FLAG_PCI_MSIX		= (1 << 3),
	/* Needs early activate, required क्रम PCI */
	MSI_FLAG_ACTIVATE_EARLY		= (1 << 4),
	/*
	 * Must reactivate when irq is started even when
	 * MSI_FLAG_ACTIVATE_EARLY has been set.
	 */
	MSI_FLAG_MUST_REACTIVATE	= (1 << 5),
	/* Is level-triggered capable, using two messages */
	MSI_FLAG_LEVEL_CAPABLE		= (1 << 6),
पूर्ण;

पूर्णांक msi_करोमुख्य_set_affinity(काष्ठा irq_data *data, स्थिर काष्ठा cpumask *mask,
			    bool क्रमce);

काष्ठा irq_करोमुख्य *msi_create_irq_करोमुख्य(काष्ठा fwnode_handle *fwnode,
					 काष्ठा msi_करोमुख्य_info *info,
					 काष्ठा irq_करोमुख्य *parent);
पूर्णांक __msi_करोमुख्य_alloc_irqs(काष्ठा irq_करोमुख्य *करोमुख्य, काष्ठा device *dev,
			    पूर्णांक nvec);
पूर्णांक msi_करोमुख्य_alloc_irqs(काष्ठा irq_करोमुख्य *करोमुख्य, काष्ठा device *dev,
			  पूर्णांक nvec);
व्योम __msi_करोमुख्य_मुक्त_irqs(काष्ठा irq_करोमुख्य *करोमुख्य, काष्ठा device *dev);
व्योम msi_करोमुख्य_मुक्त_irqs(काष्ठा irq_करोमुख्य *करोमुख्य, काष्ठा device *dev);
काष्ठा msi_करोमुख्य_info *msi_get_करोमुख्य_info(काष्ठा irq_करोमुख्य *करोमुख्य);

काष्ठा irq_करोमुख्य *platक्रमm_msi_create_irq_करोमुख्य(काष्ठा fwnode_handle *fwnode,
						  काष्ठा msi_करोमुख्य_info *info,
						  काष्ठा irq_करोमुख्य *parent);
पूर्णांक platक्रमm_msi_करोमुख्य_alloc_irqs(काष्ठा device *dev, अचिन्हित पूर्णांक nvec,
				   irq_ग_लिखो_msi_msg_t ग_लिखो_msi_msg);
व्योम platक्रमm_msi_करोमुख्य_मुक्त_irqs(काष्ठा device *dev);

/* When an MSI करोमुख्य is used as an पूर्णांकermediate करोमुख्य */
पूर्णांक msi_करोमुख्य_prepare_irqs(काष्ठा irq_करोमुख्य *करोमुख्य, काष्ठा device *dev,
			    पूर्णांक nvec, msi_alloc_info_t *args);
पूर्णांक msi_करोमुख्य_populate_irqs(काष्ठा irq_करोमुख्य *करोमुख्य, काष्ठा device *dev,
			     पूर्णांक virq, पूर्णांक nvec, msi_alloc_info_t *args);
काष्ठा irq_करोमुख्य *
__platक्रमm_msi_create_device_करोमुख्य(काष्ठा device *dev,
				    अचिन्हित पूर्णांक nvec,
				    bool is_tree,
				    irq_ग_लिखो_msi_msg_t ग_लिखो_msi_msg,
				    स्थिर काष्ठा irq_करोमुख्य_ops *ops,
				    व्योम *host_data);

#घोषणा platक्रमm_msi_create_device_करोमुख्य(dev, nvec, ग_लिखो, ops, data)	\
	__platक्रमm_msi_create_device_करोमुख्य(dev, nvec, false, ग_लिखो, ops, data)
#घोषणा platक्रमm_msi_create_device_tree_करोमुख्य(dev, nvec, ग_लिखो, ops, data) \
	__platक्रमm_msi_create_device_करोमुख्य(dev, nvec, true, ग_लिखो, ops, data)

पूर्णांक platक्रमm_msi_करोमुख्य_alloc(काष्ठा irq_करोमुख्य *करोमुख्य, अचिन्हित पूर्णांक virq,
			      अचिन्हित पूर्णांक nr_irqs);
व्योम platक्रमm_msi_करोमुख्य_मुक्त(काष्ठा irq_करोमुख्य *करोमुख्य, अचिन्हित पूर्णांक virq,
			      अचिन्हित पूर्णांक nvec);
व्योम *platक्रमm_msi_get_host_data(काष्ठा irq_करोमुख्य *करोमुख्य);
#पूर्ण_अगर /* CONFIG_GENERIC_MSI_IRQ_DOMAIN */

#अगर_घोषित CONFIG_PCI_MSI_IRQ_DOMAIN
व्योम pci_msi_करोमुख्य_ग_लिखो_msg(काष्ठा irq_data *irq_data, काष्ठा msi_msg *msg);
काष्ठा irq_करोमुख्य *pci_msi_create_irq_करोमुख्य(काष्ठा fwnode_handle *fwnode,
					     काष्ठा msi_करोमुख्य_info *info,
					     काष्ठा irq_करोमुख्य *parent);
पूर्णांक pci_msi_करोमुख्य_check_cap(काष्ठा irq_करोमुख्य *करोमुख्य,
			     काष्ठा msi_करोमुख्य_info *info, काष्ठा device *dev);
u32 pci_msi_करोमुख्य_get_msi_rid(काष्ठा irq_करोमुख्य *करोमुख्य, काष्ठा pci_dev *pdev);
काष्ठा irq_करोमुख्य *pci_msi_get_device_करोमुख्य(काष्ठा pci_dev *pdev);
bool pci_dev_has_special_msi_करोमुख्य(काष्ठा pci_dev *pdev);
#अन्यथा
अटल अंतरभूत काष्ठा irq_करोमुख्य *pci_msi_get_device_करोमुख्य(काष्ठा pci_dev *pdev)
अणु
	वापस शून्य;
पूर्ण
#पूर्ण_अगर /* CONFIG_PCI_MSI_IRQ_DOMAIN */

#पूर्ण_अगर /* LINUX_MSI_H */
