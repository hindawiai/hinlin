<शैली गुरु>
/* SPDX-License-Identअगरier: (GPL-2.0+ OR BSD-3-Clause) */
/*
 * Copyright 2013-2016 Freescale Semiconductor Inc.
 * Copyright 2016,2019-2020 NXP
 */

#अगर_अघोषित VFIO_FSL_MC_PRIVATE_H
#घोषणा VFIO_FSL_MC_PRIVATE_H

#घोषणा VFIO_FSL_MC_OFFSET_SHIFT    40
#घोषणा VFIO_FSL_MC_OFFSET_MASK (((u64)(1) << VFIO_FSL_MC_OFFSET_SHIFT) - 1)

#घोषणा VFIO_FSL_MC_OFFSET_TO_INDEX(off) ((off) >> VFIO_FSL_MC_OFFSET_SHIFT)

#घोषणा VFIO_FSL_MC_INDEX_TO_OFFSET(index)	\
	((u64)(index) << VFIO_FSL_MC_OFFSET_SHIFT)

काष्ठा vfio_fsl_mc_irq अणु
	u32         flags;
	u32         count;
	काष्ठा eventfd_ctx  *trigger;
	अक्षर            *name;
पूर्ण;

काष्ठा vfio_fsl_mc_reflck अणु
	काष्ठा kref		kref;
	काष्ठा mutex		lock;
पूर्ण;

काष्ठा vfio_fsl_mc_region अणु
	u32			flags;
	u32			type;
	u64			addr;
	resource_माप_प्रकार		size;
	व्योम __iomem		*ioaddr;
पूर्ण;

काष्ठा vfio_fsl_mc_device अणु
	काष्ठा vfio_device		vdev;
	काष्ठा fsl_mc_device		*mc_dev;
	काष्ठा notअगरier_block        nb;
	पूर्णांक				refcnt;
	काष्ठा vfio_fsl_mc_region	*regions;
	काष्ठा vfio_fsl_mc_reflck   *reflck;
	काष्ठा mutex         igate;
	काष्ठा vfio_fsl_mc_irq      *mc_irqs;
पूर्ण;

बाह्य पूर्णांक vfio_fsl_mc_set_irqs_ioctl(काष्ठा vfio_fsl_mc_device *vdev,
			       u32 flags, अचिन्हित पूर्णांक index,
			       अचिन्हित पूर्णांक start, अचिन्हित पूर्णांक count,
			       व्योम *data);

व्योम vfio_fsl_mc_irqs_cleanup(काष्ठा vfio_fsl_mc_device *vdev);

#पूर्ण_अगर /* VFIO_FSL_MC_PRIVATE_H */
