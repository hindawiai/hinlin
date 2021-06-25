<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __OF_IRQ_H
#घोषणा __OF_IRQ_H

#समावेश <linux/types.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/irq.h>
#समावेश <linux/irqकरोमुख्य.h>
#समावेश <linux/ioport.h>
#समावेश <linux/of.h>

प्रकार पूर्णांक (*of_irq_init_cb_t)(काष्ठा device_node *, काष्ठा device_node *);

/*
 * Workarounds only applied to 32bit घातermac machines
 */
#घोषणा OF_IMAP_OLDWORLD_MAC	0x00000001
#घोषणा OF_IMAP_NO_PHANDLE	0x00000002

#अगर defined(CONFIG_PPC32) && defined(CONFIG_PPC_PMAC)
बाह्य अचिन्हित पूर्णांक of_irq_workarounds;
बाह्य काष्ठा device_node *of_irq_dflt_pic;
बाह्य पूर्णांक of_irq_parse_oldworld(काष्ठा device_node *device, पूर्णांक index,
			       काष्ठा of_phandle_args *out_irq);
#अन्यथा /* CONFIG_PPC32 && CONFIG_PPC_PMAC */
#घोषणा of_irq_workarounds (0)
#घोषणा of_irq_dflt_pic (शून्य)
अटल अंतरभूत पूर्णांक of_irq_parse_oldworld(काष्ठा device_node *device, पूर्णांक index,
				      काष्ठा of_phandle_args *out_irq)
अणु
	वापस -EINVAL;
पूर्ण
#पूर्ण_अगर /* CONFIG_PPC32 && CONFIG_PPC_PMAC */

बाह्य पूर्णांक of_irq_parse_raw(स्थिर __be32 *addr, काष्ठा of_phandle_args *out_irq);
बाह्य अचिन्हित पूर्णांक irq_create_of_mapping(काष्ठा of_phandle_args *irq_data);
बाह्य पूर्णांक of_irq_to_resource(काष्ठा device_node *dev, पूर्णांक index,
			      काष्ठा resource *r);

बाह्य व्योम of_irq_init(स्थिर काष्ठा of_device_id *matches);

#अगर_घोषित CONFIG_OF_IRQ
बाह्य पूर्णांक of_irq_parse_one(काष्ठा device_node *device, पूर्णांक index,
			  काष्ठा of_phandle_args *out_irq);
बाह्य पूर्णांक of_irq_count(काष्ठा device_node *dev);
बाह्य पूर्णांक of_irq_get(काष्ठा device_node *dev, पूर्णांक index);
बाह्य पूर्णांक of_irq_get_byname(काष्ठा device_node *dev, स्थिर अक्षर *name);
बाह्य पूर्णांक of_irq_to_resource_table(काष्ठा device_node *dev,
		काष्ठा resource *res, पूर्णांक nr_irqs);
बाह्य काष्ठा device_node *of_irq_find_parent(काष्ठा device_node *child);
बाह्य काष्ठा irq_करोमुख्य *of_msi_get_करोमुख्य(काष्ठा device *dev,
					    काष्ठा device_node *np,
					    क्रमागत irq_करोमुख्य_bus_token token);
बाह्य काष्ठा irq_करोमुख्य *of_msi_map_get_device_करोमुख्य(काष्ठा device *dev,
							u32 id,
							u32 bus_token);
बाह्य व्योम of_msi_configure(काष्ठा device *dev, काष्ठा device_node *np);
u32 of_msi_map_id(काष्ठा device *dev, काष्ठा device_node *msi_np, u32 id_in);
#अन्यथा
अटल अंतरभूत पूर्णांक of_irq_parse_one(काष्ठा device_node *device, पूर्णांक index,
				   काष्ठा of_phandle_args *out_irq)
अणु
	वापस -EINVAL;
पूर्ण
अटल अंतरभूत पूर्णांक of_irq_count(काष्ठा device_node *dev)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत पूर्णांक of_irq_get(काष्ठा device_node *dev, पूर्णांक index)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत पूर्णांक of_irq_get_byname(काष्ठा device_node *dev, स्थिर अक्षर *name)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत पूर्णांक of_irq_to_resource_table(काष्ठा device_node *dev,
					   काष्ठा resource *res, पूर्णांक nr_irqs)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत व्योम *of_irq_find_parent(काष्ठा device_node *child)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत काष्ठा irq_करोमुख्य *of_msi_get_करोमुख्य(काष्ठा device *dev,
						   काष्ठा device_node *np,
						   क्रमागत irq_करोमुख्य_bus_token token)
अणु
	वापस शून्य;
पूर्ण
अटल अंतरभूत काष्ठा irq_करोमुख्य *of_msi_map_get_device_करोमुख्य(काष्ठा device *dev,
						u32 id, u32 bus_token)
अणु
	वापस शून्य;
पूर्ण
अटल अंतरभूत व्योम of_msi_configure(काष्ठा device *dev, काष्ठा device_node *np)
अणु
पूर्ण
अटल अंतरभूत u32 of_msi_map_id(काष्ठा device *dev,
				 काष्ठा device_node *msi_np, u32 id_in)
अणु
	वापस id_in;
पूर्ण
#पूर्ण_अगर

#अगर defined(CONFIG_OF_IRQ) || defined(CONFIG_SPARC)
/*
 * irq_of_parse_and_map() is used by all OF enabled platक्रमms; but SPARC
 * implements it dअगरferently.  However, the prototype is the same क्रम all,
 * so declare it here regardless of the CONFIG_OF_IRQ setting.
 */
बाह्य अचिन्हित पूर्णांक irq_of_parse_and_map(काष्ठा device_node *node, पूर्णांक index);

#अन्यथा /* !CONFIG_OF && !CONFIG_SPARC */
अटल अंतरभूत अचिन्हित पूर्णांक irq_of_parse_and_map(काष्ठा device_node *dev,
						पूर्णांक index)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर /* !CONFIG_OF */

#पूर्ण_अगर /* __OF_IRQ_H */
