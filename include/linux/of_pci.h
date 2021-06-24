<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __OF_PCI_H
#घोषणा __OF_PCI_H

#समावेश <linux/types.h>
#समावेश <linux/त्रुटिसं.स>

काष्ठा pci_dev;
काष्ठा device_node;

#अगर IS_ENABLED(CONFIG_OF) && IS_ENABLED(CONFIG_PCI)
काष्ठा device_node *of_pci_find_child_device(काष्ठा device_node *parent,
					     अचिन्हित पूर्णांक devfn);
पूर्णांक of_pci_get_devfn(काष्ठा device_node *np);
व्योम of_pci_check_probe_only(व्योम);
#अन्यथा
अटल अंतरभूत काष्ठा device_node *of_pci_find_child_device(काष्ठा device_node *parent,
					     अचिन्हित पूर्णांक devfn)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत पूर्णांक of_pci_get_devfn(काष्ठा device_node *np)
अणु
	वापस -EINVAL;
पूर्ण

अटल अंतरभूत व्योम of_pci_check_probe_only(व्योम) अणु पूर्ण
#पूर्ण_अगर

#अगर IS_ENABLED(CONFIG_OF_IRQ)
पूर्णांक of_irq_parse_and_map_pci(स्थिर काष्ठा pci_dev *dev, u8 slot, u8 pin);
#अन्यथा
अटल अंतरभूत पूर्णांक
of_irq_parse_and_map_pci(स्थिर काष्ठा pci_dev *dev, u8 slot, u8 pin)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर
