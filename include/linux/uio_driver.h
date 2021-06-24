<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * include/linux/uio_driver.h
 *
 * Copyright(C) 2005, Benedikt Spranger <b.spranger@linutronix.de>
 * Copyright(C) 2005, Thomas Gleixner <tglx@linutronix.de>
 * Copyright(C) 2006, Hans J. Koch <hjk@hansjkoch.de>
 * Copyright(C) 2006, Greg Kroah-Harपंचांगan <greg@kroah.com>
 *
 * Userspace IO driver.
 */

#अगर_अघोषित _UIO_DRIVER_H_
#घोषणा _UIO_DRIVER_H_

#समावेश <linux/device.h>
#समावेश <linux/fs.h>
#समावेश <linux/पूर्णांकerrupt.h>

काष्ठा module;
काष्ठा uio_map;

/**
 * काष्ठा uio_mem - description of a UIO memory region
 * @name:		name of the memory region क्रम identअगरication
 * @addr:               address of the device's memory rounded to page
 *			size (phys_addr is used since addr can be
 *			logical, भव, or physical & phys_addr_t
 *			should always be large enough to handle any of
 *			the address types)
 * @offs:               offset of device memory within the page
 * @size:		size of IO (multiple of page size)
 * @memtype:		type of memory addr poपूर्णांकs to
 * @पूर्णांकernal_addr:	ioremap-ped version of addr, क्रम driver पूर्णांकernal use
 * @map:		क्रम use by the UIO core only.
 */
काष्ठा uio_mem अणु
	स्थिर अक्षर		*name;
	phys_addr_t		addr;
	अचिन्हित दीर्घ		offs;
	resource_माप_प्रकार		size;
	पूर्णांक			memtype;
	व्योम __iomem		*पूर्णांकernal_addr;
	काष्ठा uio_map		*map;
पूर्ण;

#घोषणा MAX_UIO_MAPS	5

काष्ठा uio_portio;

/**
 * काष्ठा uio_port - description of a UIO port region
 * @name:		name of the port region क्रम identअगरication
 * @start:		start of port region
 * @size:		size of port region
 * @porttype:		type of port (see UIO_PORT_* below)
 * @portio:		क्रम use by the UIO core only.
 */
काष्ठा uio_port अणु
	स्थिर अक्षर		*name;
	अचिन्हित दीर्घ		start;
	अचिन्हित दीर्घ		size;
	पूर्णांक			porttype;
	काष्ठा uio_portio	*portio;
पूर्ण;

#घोषणा MAX_UIO_PORT_REGIONS	5

काष्ठा uio_device अणु
	काष्ठा module           *owner;
	काष्ठा device		dev;
	पूर्णांक                     minor;
	atomic_t                event;
	काष्ठा fasync_काष्ठा    *async_queue;
	रुको_queue_head_t       रुको;
	काष्ठा uio_info         *info;
	काष्ठा mutex		info_lock;
	काष्ठा kobject          *map_dir;
	काष्ठा kobject          *portio_dir;
पूर्ण;

/**
 * काष्ठा uio_info - UIO device capabilities
 * @uio_dev:		the UIO device this info beदीर्घs to
 * @name:		device name
 * @version:		device driver version
 * @mem:		list of mappable memory regions, size==0 क्रम end of list
 * @port:		list of port regions, size==0 क्रम end of list
 * @irq:		पूर्णांकerrupt number or UIO_IRQ_CUSTOM
 * @irq_flags:		flags क्रम request_irq()
 * @priv:		optional निजी data
 * @handler:		the device's irq handler
 * @mmap:		mmap operation क्रम this uio device
 * @खोलो:		खोलो operation क्रम this uio device
 * @release:		release operation क्रम this uio device
 * @irqcontrol:		disable/enable irqs when 0/1 is written to /dev/uioX
 */
काष्ठा uio_info अणु
	काष्ठा uio_device	*uio_dev;
	स्थिर अक्षर		*name;
	स्थिर अक्षर		*version;
	काष्ठा uio_mem		mem[MAX_UIO_MAPS];
	काष्ठा uio_port		port[MAX_UIO_PORT_REGIONS];
	दीर्घ			irq;
	अचिन्हित दीर्घ		irq_flags;
	व्योम			*priv;
	irqवापस_t (*handler)(पूर्णांक irq, काष्ठा uio_info *dev_info);
	पूर्णांक (*mmap)(काष्ठा uio_info *info, काष्ठा vm_area_काष्ठा *vma);
	पूर्णांक (*खोलो)(काष्ठा uio_info *info, काष्ठा inode *inode);
	पूर्णांक (*release)(काष्ठा uio_info *info, काष्ठा inode *inode);
	पूर्णांक (*irqcontrol)(काष्ठा uio_info *info, s32 irq_on);
पूर्ण;

बाह्य पूर्णांक __must_check
	__uio_रेजिस्टर_device(काष्ठा module *owner,
			      काष्ठा device *parent,
			      काष्ठा uio_info *info);

/* use a define to aव्योम include chaining to get THIS_MODULE */

/**
 * uio_रेजिस्टर_device - रेजिस्टर a new userspace IO device
 * @parent:	parent device
 * @info:	UIO device capabilities
 *
 * वापसs zero on success or a negative error code.
 */
#घोषणा uio_रेजिस्टर_device(parent, info) \
	__uio_रेजिस्टर_device(THIS_MODULE, parent, info)

बाह्य व्योम uio_unरेजिस्टर_device(काष्ठा uio_info *info);
बाह्य व्योम uio_event_notअगरy(काष्ठा uio_info *info);

बाह्य पूर्णांक __must_check
	__devm_uio_रेजिस्टर_device(काष्ठा module *owner,
				   काष्ठा device *parent,
				   काष्ठा uio_info *info);

/* use a define to aव्योम include chaining to get THIS_MODULE */

/**
 * devm_uio_रेजिस्टर_device - Resource managed uio_रेजिस्टर_device()
 * @parent:	parent device
 * @info:	UIO device capabilities
 *
 * वापसs zero on success or a negative error code.
 */
#घोषणा devm_uio_रेजिस्टर_device(parent, info) \
	__devm_uio_रेजिस्टर_device(THIS_MODULE, parent, info)

/* defines क्रम uio_info->irq */
#घोषणा UIO_IRQ_CUSTOM	-1
#घोषणा UIO_IRQ_NONE	0

/* defines क्रम uio_mem->memtype */
#घोषणा UIO_MEM_NONE	0
#घोषणा UIO_MEM_PHYS	1
#घोषणा UIO_MEM_LOGICAL	2
#घोषणा UIO_MEM_VIRTUAL 3
#घोषणा UIO_MEM_IOVA	4

/* defines क्रम uio_port->porttype */
#घोषणा UIO_PORT_NONE	0
#घोषणा UIO_PORT_X86	1
#घोषणा UIO_PORT_GPIO	2
#घोषणा UIO_PORT_OTHER	3

#पूर्ण_अगर /* _LINUX_UIO_DRIVER_H_ */
