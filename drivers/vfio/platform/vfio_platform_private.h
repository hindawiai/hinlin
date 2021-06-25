<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2013 - Virtual Open Systems
 * Author: Antonios Motakis <a.motakis@भवखोलोप्रणालीs.com>
 */

#अगर_अघोषित VFIO_PLATFORM_PRIVATE_H
#घोषणा VFIO_PLATFORM_PRIVATE_H

#समावेश <linux/types.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/vfपन.स>

#घोषणा VFIO_PLATFORM_OFFSET_SHIFT   40
#घोषणा VFIO_PLATFORM_OFFSET_MASK (((u64)(1) << VFIO_PLATFORM_OFFSET_SHIFT) - 1)

#घोषणा VFIO_PLATFORM_OFFSET_TO_INDEX(off)	\
	(off >> VFIO_PLATFORM_OFFSET_SHIFT)

#घोषणा VFIO_PLATFORM_INDEX_TO_OFFSET(index)	\
	((u64)(index) << VFIO_PLATFORM_OFFSET_SHIFT)

काष्ठा vfio_platक्रमm_irq अणु
	u32			flags;
	u32			count;
	पूर्णांक			hwirq;
	अक्षर			*name;
	काष्ठा eventfd_ctx	*trigger;
	bool			masked;
	spinlock_t		lock;
	काष्ठा virqfd		*unmask;
	काष्ठा virqfd		*mask;
पूर्ण;

काष्ठा vfio_platक्रमm_region अणु
	u64			addr;
	resource_माप_प्रकार		size;
	u32			flags;
	u32			type;
#घोषणा VFIO_PLATFORM_REGION_TYPE_MMIO	1
#घोषणा VFIO_PLATFORM_REGION_TYPE_PIO	2
	व्योम __iomem		*ioaddr;
पूर्ण;

काष्ठा vfio_platक्रमm_device अणु
	काष्ठा vfio_device		vdev;
	काष्ठा vfio_platक्रमm_region	*regions;
	u32				num_regions;
	काष्ठा vfio_platक्रमm_irq	*irqs;
	u32				num_irqs;
	पूर्णांक				refcnt;
	काष्ठा mutex			igate;
	काष्ठा module			*parent_module;
	स्थिर अक्षर			*compat;
	स्थिर अक्षर			*acpihid;
	काष्ठा module			*reset_module;
	काष्ठा device			*device;

	/*
	 * These fields should be filled by the bus specअगरic binder
	 */
	व्योम		*opaque;
	स्थिर अक्षर	*name;
	uपूर्णांक32_t	flags;
	/* callbacks to discover device resources */
	काष्ठा resource*
		(*get_resource)(काष्ठा vfio_platक्रमm_device *vdev, पूर्णांक i);
	पूर्णांक	(*get_irq)(काष्ठा vfio_platक्रमm_device *vdev, पूर्णांक i);
	पूर्णांक	(*of_reset)(काष्ठा vfio_platक्रमm_device *vdev);

	bool				reset_required;
पूर्ण;

प्रकार पूर्णांक (*vfio_platक्रमm_reset_fn_t)(काष्ठा vfio_platक्रमm_device *vdev);

काष्ठा vfio_platक्रमm_reset_node अणु
	काष्ठा list_head link;
	अक्षर *compat;
	काष्ठा module *owner;
	vfio_platक्रमm_reset_fn_t of_reset;
पूर्ण;

बाह्य पूर्णांक vfio_platक्रमm_probe_common(काष्ठा vfio_platक्रमm_device *vdev,
				      काष्ठा device *dev);
व्योम vfio_platक्रमm_हटाओ_common(काष्ठा vfio_platक्रमm_device *vdev);

बाह्य पूर्णांक vfio_platक्रमm_irq_init(काष्ठा vfio_platक्रमm_device *vdev);
बाह्य व्योम vfio_platक्रमm_irq_cleanup(काष्ठा vfio_platक्रमm_device *vdev);

बाह्य पूर्णांक vfio_platक्रमm_set_irqs_ioctl(काष्ठा vfio_platक्रमm_device *vdev,
					uपूर्णांक32_t flags, अचिन्हित index,
					अचिन्हित start, अचिन्हित count,
					व्योम *data);

बाह्य व्योम __vfio_platक्रमm_रेजिस्टर_reset(काष्ठा vfio_platक्रमm_reset_node *n);
बाह्य व्योम vfio_platक्रमm_unरेजिस्टर_reset(स्थिर अक्षर *compat,
					   vfio_platक्रमm_reset_fn_t fn);
#घोषणा vfio_platक्रमm_रेजिस्टर_reset(__compat, __reset)		\
अटल काष्ठा vfio_platक्रमm_reset_node __reset ## _node = अणु	\
	.owner = THIS_MODULE,					\
	.compat = __compat,					\
	.of_reset = __reset,					\
पूर्ण;								\
__vfio_platक्रमm_रेजिस्टर_reset(&__reset ## _node)

#घोषणा module_vfio_reset_handler(compat, reset)		\
MODULE_ALIAS("vfio-reset:" compat);				\
अटल पूर्णांक __init reset ## _module_init(व्योम)			\
अणु								\
	vfio_platक्रमm_रेजिस्टर_reset(compat, reset);		\
	वापस 0;						\
पूर्ण;								\
अटल व्योम __निकास reset ## _module_निकास(व्योम)			\
अणु								\
	vfio_platक्रमm_unरेजिस्टर_reset(compat, reset);		\
पूर्ण;								\
module_init(reset ## _module_init);				\
module_निकास(reset ## _module_निकास)

#पूर्ण_अगर /* VFIO_PLATFORM_PRIVATE_H */
