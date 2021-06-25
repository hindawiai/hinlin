<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _VME_USER_H_
#घोषणा _VME_USER_H_

#घोषणा VME_USER_BUS_MAX	1

/*
 * VMEbus Master Winकरोw Configuration Structure
 */
काष्ठा vme_master अणु
	__u32 enable;		/* State of Winकरोw */
	__u64 vme_addr;		/* Starting Address on the VMEbus */
	__u64 size;		/* Winकरोw Size */
	__u32 aspace;		/* Address Space */
	__u32 cycle;		/* Cycle properties */
	__u32 dwidth;		/* Maximum Data Width */
#अगर 0
	अक्षर prefetchenable;		/* Prefetch Read Enable State */
	पूर्णांक prefetchsize;		/* Prefetch Read Size (Cache Lines) */
	अक्षर wrpostenable;		/* Write Post State */
#पूर्ण_अगर
पूर्ण __packed;

/*
 * IOCTL Commands and काष्ठाures
 */

/* Magic number क्रम use in ioctls */
#घोषणा VME_IOC_MAGIC 0xAE

/* VMEbus Slave Winकरोw Configuration Structure */
काष्ठा vme_slave अणु
	__u32 enable;		/* State of Winकरोw */
	__u64 vme_addr;		/* Starting Address on the VMEbus */
	__u64 size;		/* Winकरोw Size */
	__u32 aspace;		/* Address Space */
	__u32 cycle;		/* Cycle properties */
#अगर 0
	अक्षर wrpostenable;		/* Write Post State */
	अक्षर rmwlock;			/* Lock PCI during RMW Cycles */
	अक्षर data64bitcapable;		/* non-VMEbus capable of 64-bit Data */
#पूर्ण_अगर
पूर्ण __packed;

काष्ठा vme_irq_id अणु
	__u8 level;
	__u8 statid;
पूर्ण;

#घोषणा VME_GET_SLAVE _IOR(VME_IOC_MAGIC, 1, काष्ठा vme_slave)
#घोषणा VME_SET_SLAVE _IOW(VME_IOC_MAGIC, 2, काष्ठा vme_slave)
#घोषणा VME_GET_MASTER _IOR(VME_IOC_MAGIC, 3, काष्ठा vme_master)
#घोषणा VME_SET_MASTER _IOW(VME_IOC_MAGIC, 4, काष्ठा vme_master)
#घोषणा VME_IRQ_GEN _IOW(VME_IOC_MAGIC, 5, काष्ठा vme_irq_id)

#पूर्ण_अगर /* _VME_USER_H_ */

