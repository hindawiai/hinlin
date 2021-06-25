<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * CCI cache coherent पूर्णांकerconnect support
 *
 * Copyright (C) 2013 ARM Ltd.
 */

#अगर_अघोषित __LINUX_ARM_CCI_H
#घोषणा __LINUX_ARM_CCI_H

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/types.h>

#समावेश <यंत्र/arm-cci.h>

काष्ठा device_node;

#अगर_घोषित CONFIG_ARM_CCI
बाह्य bool cci_probed(व्योम);
#अन्यथा
अटल अंतरभूत bool cci_probed(व्योम) अणु वापस false; पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_ARM_CCI400_PORT_CTRL
बाह्य पूर्णांक cci_ace_get_port(काष्ठा device_node *dn);
बाह्य पूर्णांक cci_disable_port_by_cpu(u64 mpidr);
बाह्य पूर्णांक __cci_control_port_by_device(काष्ठा device_node *dn, bool enable);
बाह्य पूर्णांक __cci_control_port_by_index(u32 port, bool enable);
#अन्यथा
अटल अंतरभूत पूर्णांक cci_ace_get_port(काष्ठा device_node *dn)
अणु
	वापस -ENODEV;
पूर्ण
अटल अंतरभूत पूर्णांक cci_disable_port_by_cpu(u64 mpidr) अणु वापस -ENODEV; पूर्ण
अटल अंतरभूत पूर्णांक __cci_control_port_by_device(काष्ठा device_node *dn,
					       bool enable)
अणु
	वापस -ENODEV;
पूर्ण
अटल अंतरभूत पूर्णांक __cci_control_port_by_index(u32 port, bool enable)
अणु
	वापस -ENODEV;
पूर्ण
#पूर्ण_अगर

#घोषणा cci_disable_port_by_device(dev) \
	__cci_control_port_by_device(dev, false)
#घोषणा cci_enable_port_by_device(dev) \
	__cci_control_port_by_device(dev, true)
#घोषणा cci_disable_port_by_index(dev) \
	__cci_control_port_by_index(dev, false)
#घोषणा cci_enable_port_by_index(dev) \
	__cci_control_port_by_index(dev, true)

#पूर्ण_अगर
