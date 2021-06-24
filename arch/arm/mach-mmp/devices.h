<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __MACH_DEVICE_H
#घोषणा __MACH_DEVICE_H

#समावेश <linux/types.h>

#घोषणा MAX_RESOURCE_DMA	2

/* काष्ठाure क्रम describing the on-chip devices */
काष्ठा pxa_device_desc अणु
	स्थिर अक्षर	*dev_name;
	स्थिर अक्षर	*drv_name;
	पूर्णांक		id;
	पूर्णांक		irq;
	अचिन्हित दीर्घ	start;
	अचिन्हित दीर्घ	size;
	पूर्णांक		dma[MAX_RESOURCE_DMA];
पूर्ण;

#घोषणा PXA168_DEVICE(_name, _drv, _id, _irq, _start, _size, _dma...)	\
काष्ठा pxa_device_desc pxa168_device_##_name __initdata = अणु		\
	.dev_name	= "pxa168-" #_name,				\
	.drv_name	= _drv,						\
	.id		= _id,						\
	.irq		= IRQ_PXA168_##_irq,				\
	.start		= _start,					\
	.size		= _size,					\
	.dma		= अणु _dma पूर्ण,					\
पूर्ण;

#घोषणा PXA910_DEVICE(_name, _drv, _id, _irq, _start, _size, _dma...)	\
काष्ठा pxa_device_desc pxa910_device_##_name __initdata = अणु		\
	.dev_name	= "pxa910-" #_name,				\
	.drv_name	= _drv,						\
	.id		= _id,						\
	.irq		= IRQ_PXA910_##_irq,				\
	.start		= _start,					\
	.size		= _size,					\
	.dma		= अणु _dma पूर्ण,					\
पूर्ण;

#घोषणा MMP2_DEVICE(_name, _drv, _id, _irq, _start, _size, _dma...)	\
काष्ठा pxa_device_desc mmp2_device_##_name __initdata = अणु		\
	.dev_name	= "mmp2-" #_name,				\
	.drv_name	= _drv,						\
	.id		= _id,						\
	.irq		= IRQ_MMP2_##_irq,				\
	.start		= _start,					\
	.size		= _size,					\
	.dma		= अणु _dma पूर्ण,					\
पूर्ण

बाह्य पूर्णांक pxa_रेजिस्टर_device(काष्ठा pxa_device_desc *, व्योम *, माप_प्रकार);
बाह्य पूर्णांक pxa_usb_phy_init(व्योम __iomem *phy_reg);
बाह्य व्योम pxa_usb_phy_deinit(व्योम __iomem *phy_reg);

#पूर्ण_अगर /* __MACH_DEVICE_H */
