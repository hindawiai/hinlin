<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * IBM PowerPC Virtual I/O Infraकाष्ठाure Support.
 *
 * Copyright (c) 2003 IBM Corp.
 *  Dave Engebretsen engebret@us.ibm.com
 *  Santiago Leon santil@us.ibm.com
 */

#अगर_अघोषित _ASM_POWERPC_VIO_H
#घोषणा _ASM_POWERPC_VIO_H
#अगर_घोषित __KERNEL__

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/device.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/scatterlist.h>

#समावेश <यंत्र/hvcall.h>

/*
 * Architecture-specअगरic स्थिरants क्रम drivers to
 * extract attributes of the device using vio_get_attribute()
 */
#घोषणा VETH_MAC_ADDR "local-mac-address"
#घोषणा VETH_MCAST_FILTER_SIZE "ibm,mac-address-filters"

/* End architecture-specअगरic स्थिरants */

#घोषणा h_vio_संकेत(ua, mode) \
  plpar_hcall_norets(H_VIO_SIGNAL, ua, mode)

#घोषणा VIO_IRQ_DISABLE		0UL
#घोषणा VIO_IRQ_ENABLE		1UL

/*
 * VIO CMO minimum entitlement क्रम all devices and spare entitlement
 */
#घोषणा VIO_CMO_MIN_ENT 1562624

बाह्य काष्ठा bus_type vio_bus_type;

काष्ठा iommu_table;

/*
 * Platक्रमm Facilities Option (PFO)-specअगरic data
 */

/* Starting unit address क्रम PFO devices on the VIO BUS */
#घोषणा VIO_BASE_PFO_UA	0x50000000

/**
 * vio_pfo_op - PFO operation parameters
 *
 * @flags: h_call subfunctions and modअगरiers
 * @in: Input data block logical real address
 * @inlen: If non-negative, the length of the input data block.  If negative,
 *	the length of the input data descriptor list in bytes.
 * @out: Output data block logical real address
 * @outlen: If non-negative, the length of the input data block.  If negative,
 *	the length of the input data descriptor list in bytes.
 * @csbcpb: Logical real address of the 4k naturally-aligned storage block
 *	containing the CSB & optional FC field specअगरic CPB
 * @समयout: # of milliseconds to retry h_call, 0 क्रम no समयout.
 * @hcall_err: poपूर्णांकer to वापस the h_call वापस value, अन्यथा शून्य
 */
काष्ठा vio_pfo_op अणु
	u64 flags;
	s64 in;
	s64 inlen;
	s64 out;
	s64 outlen;
	u64 csbcpb;
	व्योम *करोne;
	अचिन्हित दीर्घ handle;
	अचिन्हित पूर्णांक समयout;
	दीर्घ hcall_err;
पूर्ण;

/* End PFO specअगरic data */

क्रमागत vio_dev_family अणु
	VDEVICE,	/* The OF node is a child of /vdevice */
	PFO,		/* The OF node is a child of /ibm,platक्रमm-facilities */
पूर्ण;

/**
 * vio_dev - This काष्ठाure is used to describe भव I/O devices.
 *
 * @desired: set from वापस of driver's get_desired_dma() function
 * @entitled: bytes of IO data that has been reserved क्रम this device.
 * @allocated: bytes of IO data currently in use by the device.
 * @allocs_failed: number of DMA failures due to insufficient entitlement.
 */
काष्ठा vio_dev अणु
	स्थिर अक्षर *name;
	स्थिर अक्षर *type;
	uपूर्णांक32_t unit_address;
	uपूर्णांक32_t resource_id;
	अचिन्हित पूर्णांक irq;
	काष्ठा अणु
		माप_प्रकार desired;
		माप_प्रकार entitled;
		माप_प्रकार allocated;
		atomic_t allocs_failed;
	पूर्ण cmo;
	क्रमागत vio_dev_family family;
	काष्ठा device dev;
पूर्ण;

काष्ठा vio_driver अणु
	स्थिर अक्षर *name;
	स्थिर काष्ठा vio_device_id *id_table;
	पूर्णांक (*probe)(काष्ठा vio_dev *dev, स्थिर काष्ठा vio_device_id *id);
	व्योम (*हटाओ)(काष्ठा vio_dev *dev);
	व्योम (*shutकरोwn)(काष्ठा vio_dev *dev);
	/* A driver must have a get_desired_dma() function to
	 * be loaded in a CMO environment अगर it uses DMA.
	 */
	अचिन्हित दीर्घ (*get_desired_dma)(काष्ठा vio_dev *dev);
	स्थिर काष्ठा dev_pm_ops *pm;
	काष्ठा device_driver driver;
पूर्ण;

बाह्य पूर्णांक __vio_रेजिस्टर_driver(काष्ठा vio_driver *drv, काष्ठा module *owner,
				 स्थिर अक्षर *mod_name);
/*
 * vio_रेजिस्टर_driver must be a macro so that KBUILD_MODNAME can be expanded
 */
#घोषणा vio_रेजिस्टर_driver(driver)		\
	__vio_रेजिस्टर_driver(driver, THIS_MODULE, KBUILD_MODNAME)
बाह्य व्योम vio_unरेजिस्टर_driver(काष्ठा vio_driver *drv);

बाह्य पूर्णांक vio_cmo_entitlement_update(माप_प्रकार);
बाह्य व्योम vio_cmo_set_dev_desired(काष्ठा vio_dev *viodev, माप_प्रकार desired);

बाह्य व्योम vio_unरेजिस्टर_device(काष्ठा vio_dev *dev);

बाह्य पूर्णांक vio_h_cop_sync(काष्ठा vio_dev *vdev, काष्ठा vio_pfo_op *op);

काष्ठा device_node;

बाह्य काष्ठा vio_dev *vio_रेजिस्टर_device_node(
		काष्ठा device_node *node_vdev);
बाह्य स्थिर व्योम *vio_get_attribute(काष्ठा vio_dev *vdev, अक्षर *which,
		पूर्णांक *length);
#अगर_घोषित CONFIG_PPC_PSERIES
बाह्य काष्ठा vio_dev *vio_find_node(काष्ठा device_node *vnode);
बाह्य पूर्णांक vio_enable_पूर्णांकerrupts(काष्ठा vio_dev *dev);
बाह्य पूर्णांक vio_disable_पूर्णांकerrupts(काष्ठा vio_dev *dev);
#अन्यथा
अटल अंतरभूत पूर्णांक vio_enable_पूर्णांकerrupts(काष्ठा vio_dev *dev)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल अंतरभूत काष्ठा vio_driver *to_vio_driver(काष्ठा device_driver *drv)
अणु
	वापस container_of(drv, काष्ठा vio_driver, driver);
पूर्ण

अटल अंतरभूत काष्ठा vio_dev *to_vio_dev(काष्ठा device *dev)
अणु
	वापस container_of(dev, काष्ठा vio_dev, dev);
पूर्ण

#पूर्ण_अगर /* __KERNEL__ */
#पूर्ण_अगर /* _ASM_POWERPC_VIO_H */
