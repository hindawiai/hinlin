<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
#समावेश <linux/of.h>	/* linux/of.h माला_लो to determine #समावेश ordering */
#अगर_अघोषित _SPARC_PROM_H
#घोषणा _SPARC_PROM_H
#अगर_घोषित __KERNEL__

/*
 * Definitions क्रम talking to the Open Firmware PROM on
 * Power Macपूर्णांकosh computers.
 *
 * Copyright (C) 1996-2005 Paul Mackerras.
 *
 * Updates क्रम PPC64 by Peter Bergner & David Engebretsen, IBM Corp.
 * Updates क्रम SPARC by David S. Miller
 */
#समावेश <linux/types.h>
#समावेश <linux/of_pdt.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/mutex.h>
#समावेश <linux/atomic.h>
#समावेश <linux/irqकरोमुख्य.h>

#घोषणा of_compat_cmp(s1, s2, l)	म_भेदन((s1), (s2), (l))
#घोषणा of_prop_cmp(s1, s2)		strहालcmp((s1), (s2))
#घोषणा of_node_cmp(s1, s2)		म_भेद((s1), (s2))

काष्ठा of_irq_controller अणु
	अचिन्हित पूर्णांक	(*irq_build)(काष्ठा device_node *, अचिन्हित पूर्णांक, व्योम *);
	व्योम		*data;
पूर्ण;

काष्ठा device_node *of_find_node_by_cpuid(पूर्णांक cpuid);
पूर्णांक of_set_property(काष्ठा device_node *node, स्थिर अक्षर *name, व्योम *val, पूर्णांक len);
बाह्य काष्ठा mutex of_set_property_mutex;
पूर्णांक of_getपूर्णांकprop_शेष(काष्ठा device_node *np,
			  स्थिर अक्षर *name,
				 पूर्णांक def);
पूर्णांक of_find_in_proplist(स्थिर अक्षर *list, स्थिर अक्षर *match, पूर्णांक len);

व्योम prom_build_devicetree(व्योम);
व्योम of_populate_present_mask(व्योम);
व्योम of_fill_in_cpu_data(व्योम);

काष्ठा resource;
व्योम __iomem *of_ioremap(काष्ठा resource *res, अचिन्हित दीर्घ offset, अचिन्हित दीर्घ size, अक्षर *name);
व्योम of_iounmap(काष्ठा resource *res, व्योम __iomem *base, अचिन्हित दीर्घ size);

बाह्य काष्ठा device_node *of_console_device;
बाह्य अक्षर *of_console_path;
बाह्य अक्षर *of_console_options;

व्योम irq_trans_init(काष्ठा device_node *dp);
अक्षर *build_path_component(काष्ठा device_node *dp);

#पूर्ण_अगर /* __KERNEL__ */
#पूर्ण_अगर /* _SPARC_PROM_H */
