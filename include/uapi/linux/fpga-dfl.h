<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/*
 * Header File क्रम FPGA DFL User API
 *
 * Copyright (C) 2017-2018 Intel Corporation, Inc.
 *
 * Authors:
 *   Kang Luwei <luwei.kang@पूर्णांकel.com>
 *   Zhang Yi <yi.z.zhang@पूर्णांकel.com>
 *   Wu Hao <hao.wu@पूर्णांकel.com>
 *   Xiao Guangrong <guangrong.xiao@linux.पूर्णांकel.com>
 */

#अगर_अघोषित _UAPI_LINUX_FPGA_DFL_H
#घोषणा _UAPI_LINUX_FPGA_DFL_H

#समावेश <linux/types.h>
#समावेश <linux/ioctl.h>

#घोषणा DFL_FPGA_API_VERSION 0

/*
 * The IOCTL पूर्णांकerface क्रम DFL based FPGA is deचिन्हित क्रम extensibility by
 * embedding the काष्ठाure length (argsz) and flags पूर्णांकo काष्ठाures passed
 * between kernel and userspace. This design referenced the VFIO IOCTL
 * पूर्णांकerface (include/uapi/linux/vfपन.स).
 */

#घोषणा DFL_FPGA_MAGIC 0xB6

#घोषणा DFL_FPGA_BASE 0
#घोषणा DFL_PORT_BASE 0x40
#घोषणा DFL_FME_BASE 0x80

/* Common IOCTLs क्रम both FME and AFU file descriptor */

/**
 * DFL_FPGA_GET_API_VERSION - _IO(DFL_FPGA_MAGIC, DFL_FPGA_BASE + 0)
 *
 * Report the version of the driver API.
 * Return: Driver API Version.
 */

#घोषणा DFL_FPGA_GET_API_VERSION	_IO(DFL_FPGA_MAGIC, DFL_FPGA_BASE + 0)

/**
 * DFL_FPGA_CHECK_EXTENSION - _IO(DFL_FPGA_MAGIC, DFL_FPGA_BASE + 1)
 *
 * Check whether an extension is supported.
 * Return: 0 अगर not supported, otherwise the extension is supported.
 */

#घोषणा DFL_FPGA_CHECK_EXTENSION	_IO(DFL_FPGA_MAGIC, DFL_FPGA_BASE + 1)

/* IOCTLs क्रम AFU file descriptor */

/**
 * DFL_FPGA_PORT_RESET - _IO(DFL_FPGA_MAGIC, DFL_PORT_BASE + 0)
 *
 * Reset the FPGA Port and its AFU. No parameters are supported.
 * Userspace can करो Port reset at any समय, e.g. during DMA or PR. But
 * it should never cause any प्रणाली level issue, only functional failure
 * (e.g. DMA or PR operation failure) and be recoverable from the failure.
 * Return: 0 on success, -त्रुटि_सं of failure
 */

#घोषणा DFL_FPGA_PORT_RESET		_IO(DFL_FPGA_MAGIC, DFL_PORT_BASE + 0)

/**
 * DFL_FPGA_PORT_GET_INFO - _IOR(DFL_FPGA_MAGIC, DFL_PORT_BASE + 1,
 *						काष्ठा dfl_fpga_port_info)
 *
 * Retrieve inक्रमmation about the fpga port.
 * Driver fills the info in provided काष्ठा dfl_fpga_port_info.
 * Return: 0 on success, -त्रुटि_सं on failure.
 */
काष्ठा dfl_fpga_port_info अणु
	/* Input */
	__u32 argsz;		/* Structure length */
	/* Output */
	__u32 flags;		/* Zero क्रम now */
	__u32 num_regions;	/* The number of supported regions */
	__u32 num_umsgs;	/* The number of allocated umsgs */
पूर्ण;

#घोषणा DFL_FPGA_PORT_GET_INFO		_IO(DFL_FPGA_MAGIC, DFL_PORT_BASE + 1)

/**
 * FPGA_PORT_GET_REGION_INFO - _IOWR(FPGA_MAGIC, PORT_BASE + 2,
 *					काष्ठा dfl_fpga_port_region_info)
 *
 * Retrieve inक्रमmation about a device memory region.
 * Caller provides काष्ठा dfl_fpga_port_region_info with index value set.
 * Driver वापसs the region info in other fields.
 * Return: 0 on success, -त्रुटि_सं on failure.
 */
काष्ठा dfl_fpga_port_region_info अणु
	/* input */
	__u32 argsz;		/* Structure length */
	/* Output */
	__u32 flags;		/* Access permission */
#घोषणा DFL_PORT_REGION_READ	(1 << 0)	/* Region is पढ़ोable */
#घोषणा DFL_PORT_REGION_WRITE	(1 << 1)	/* Region is writable */
#घोषणा DFL_PORT_REGION_MMAP	(1 << 2)	/* Can be mmaped to userspace */
	/* Input */
	__u32 index;		/* Region index */
#घोषणा DFL_PORT_REGION_INDEX_AFU	0	/* AFU */
#घोषणा DFL_PORT_REGION_INDEX_STP	1	/* Signal Tap */
	__u32 padding;
	/* Output */
	__u64 size;		/* Region size (bytes) */
	__u64 offset;		/* Region offset from start of device fd */
पूर्ण;

#घोषणा DFL_FPGA_PORT_GET_REGION_INFO	_IO(DFL_FPGA_MAGIC, DFL_PORT_BASE + 2)

/**
 * DFL_FPGA_PORT_DMA_MAP - _IOWR(DFL_FPGA_MAGIC, DFL_PORT_BASE + 3,
 *						काष्ठा dfl_fpga_port_dma_map)
 *
 * Map the dma memory per user_addr and length which are provided by caller.
 * Driver fills the iova in provided काष्ठा afu_port_dma_map.
 * This पूर्णांकerface only accepts page-size aligned user memory क्रम dma mapping.
 * Return: 0 on success, -त्रुटि_सं on failure.
 */
काष्ठा dfl_fpga_port_dma_map अणु
	/* Input */
	__u32 argsz;		/* Structure length */
	__u32 flags;		/* Zero क्रम now */
	__u64 user_addr;        /* Process भव address */
	__u64 length;           /* Length of mapping (bytes)*/
	/* Output */
	__u64 iova;             /* IO भव address */
पूर्ण;

#घोषणा DFL_FPGA_PORT_DMA_MAP		_IO(DFL_FPGA_MAGIC, DFL_PORT_BASE + 3)

/**
 * DFL_FPGA_PORT_DMA_UNMAP - _IOW(FPGA_MAGIC, PORT_BASE + 4,
 *						काष्ठा dfl_fpga_port_dma_unmap)
 *
 * Unmap the dma memory per iova provided by caller.
 * Return: 0 on success, -त्रुटि_सं on failure.
 */
काष्ठा dfl_fpga_port_dma_unmap अणु
	/* Input */
	__u32 argsz;		/* Structure length */
	__u32 flags;		/* Zero क्रम now */
	__u64 iova;		/* IO भव address */
पूर्ण;

#घोषणा DFL_FPGA_PORT_DMA_UNMAP		_IO(DFL_FPGA_MAGIC, DFL_PORT_BASE + 4)

/**
 * काष्ठा dfl_fpga_irq_set - the argument क्रम DFL_FPGA_XXX_SET_IRQ ioctl.
 *
 * @start: Index of the first irq.
 * @count: The number of eventfd handler.
 * @evtfds: Eventfd handlers.
 */
काष्ठा dfl_fpga_irq_set अणु
	__u32 start;
	__u32 count;
	__s32 evtfds[];
पूर्ण;

/**
 * DFL_FPGA_PORT_ERR_GET_IRQ_NUM - _IOR(DFL_FPGA_MAGIC, DFL_PORT_BASE + 5,
 *								__u32 num_irqs)
 *
 * Get the number of irqs supported by the fpga port error reporting निजी
 * feature. Currently hardware supports up to 1 irq.
 * Return: 0 on success, -त्रुटि_सं on failure.
 */
#घोषणा DFL_FPGA_PORT_ERR_GET_IRQ_NUM	_IOR(DFL_FPGA_MAGIC,	\
					     DFL_PORT_BASE + 5, __u32)

/**
 * DFL_FPGA_PORT_ERR_SET_IRQ - _IOW(DFL_FPGA_MAGIC, DFL_PORT_BASE + 6,
 *						काष्ठा dfl_fpga_irq_set)
 *
 * Set fpga port error reporting पूर्णांकerrupt trigger अगर evtfds[n] is valid.
 * Unset related पूर्णांकerrupt trigger अगर evtfds[n] is a negative value.
 * Return: 0 on success, -त्रुटि_सं on failure.
 */
#घोषणा DFL_FPGA_PORT_ERR_SET_IRQ	_IOW(DFL_FPGA_MAGIC,	\
					     DFL_PORT_BASE + 6,	\
					     काष्ठा dfl_fpga_irq_set)

/**
 * DFL_FPGA_PORT_UINT_GET_IRQ_NUM - _IOR(DFL_FPGA_MAGIC, DFL_PORT_BASE + 7,
 *								__u32 num_irqs)
 *
 * Get the number of irqs supported by the fpga AFU पूर्णांकerrupt निजी
 * feature.
 * Return: 0 on success, -त्रुटि_सं on failure.
 */
#घोषणा DFL_FPGA_PORT_UINT_GET_IRQ_NUM	_IOR(DFL_FPGA_MAGIC,	\
					     DFL_PORT_BASE + 7, __u32)

/**
 * DFL_FPGA_PORT_UINT_SET_IRQ - _IOW(DFL_FPGA_MAGIC, DFL_PORT_BASE + 8,
 *						काष्ठा dfl_fpga_irq_set)
 *
 * Set fpga AFU पूर्णांकerrupt trigger अगर evtfds[n] is valid.
 * Unset related पूर्णांकerrupt trigger अगर evtfds[n] is a negative value.
 * Return: 0 on success, -त्रुटि_सं on failure.
 */
#घोषणा DFL_FPGA_PORT_UINT_SET_IRQ	_IOW(DFL_FPGA_MAGIC,	\
					     DFL_PORT_BASE + 8,	\
					     काष्ठा dfl_fpga_irq_set)

/* IOCTLs क्रम FME file descriptor */

/**
 * DFL_FPGA_FME_PORT_PR - _IOW(DFL_FPGA_MAGIC, DFL_FME_BASE + 0,
 *						काष्ठा dfl_fpga_fme_port_pr)
 *
 * Driver करोes Partial Reconfiguration based on Port ID and Buffer (Image)
 * provided by caller.
 * Return: 0 on success, -त्रुटि_सं on failure.
 * If DFL_FPGA_FME_PORT_PR वापसs -EIO, that indicates the HW has detected
 * some errors during PR, under this हाल, the user can fetch HW error info
 * from the status of FME's fpga manager.
 */

काष्ठा dfl_fpga_fme_port_pr अणु
	/* Input */
	__u32 argsz;		/* Structure length */
	__u32 flags;		/* Zero क्रम now */
	__u32 port_id;
	__u32 buffer_size;
	__u64 buffer_address;	/* Userspace address to the buffer क्रम PR */
पूर्ण;

#घोषणा DFL_FPGA_FME_PORT_PR	_IO(DFL_FPGA_MAGIC, DFL_FME_BASE + 0)

/**
 * DFL_FPGA_FME_PORT_RELEASE - _IOW(DFL_FPGA_MAGIC, DFL_FME_BASE + 1,
 *						पूर्णांक port_id)
 *
 * Driver releases the port per Port ID provided by caller.
 * Return: 0 on success, -त्रुटि_सं on failure.
 */
#घोषणा DFL_FPGA_FME_PORT_RELEASE   _IOW(DFL_FPGA_MAGIC, DFL_FME_BASE + 1, पूर्णांक)

/**
 * DFL_FPGA_FME_PORT_ASSIGN - _IOW(DFL_FPGA_MAGIC, DFL_FME_BASE + 2,
 *						पूर्णांक port_id)
 *
 * Driver assigns the port back per Port ID provided by caller.
 * Return: 0 on success, -त्रुटि_सं on failure.
 */
#घोषणा DFL_FPGA_FME_PORT_ASSIGN     _IOW(DFL_FPGA_MAGIC, DFL_FME_BASE + 2, पूर्णांक)

/**
 * DFL_FPGA_FME_ERR_GET_IRQ_NUM - _IOR(DFL_FPGA_MAGIC, DFL_FME_BASE + 3,
 *							__u32 num_irqs)
 *
 * Get the number of irqs supported by the fpga fme error reporting निजी
 * feature. Currently hardware supports up to 1 irq.
 * Return: 0 on success, -त्रुटि_सं on failure.
 */
#घोषणा DFL_FPGA_FME_ERR_GET_IRQ_NUM	_IOR(DFL_FPGA_MAGIC,	\
					     DFL_FME_BASE + 3, __u32)

/**
 * DFL_FPGA_FME_ERR_SET_IRQ - _IOW(DFL_FPGA_MAGIC, DFL_FME_BASE + 4,
 *						काष्ठा dfl_fpga_irq_set)
 *
 * Set fpga fme error reporting पूर्णांकerrupt trigger अगर evtfds[n] is valid.
 * Unset related पूर्णांकerrupt trigger अगर evtfds[n] is a negative value.
 * Return: 0 on success, -त्रुटि_सं on failure.
 */
#घोषणा DFL_FPGA_FME_ERR_SET_IRQ	_IOW(DFL_FPGA_MAGIC,	\
					     DFL_FME_BASE + 4,	\
					     काष्ठा dfl_fpga_irq_set)

#पूर्ण_अगर /* _UAPI_LINUX_FPGA_DFL_H */
