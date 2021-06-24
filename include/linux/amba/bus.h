<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *  linux/include/amba/bus.h
 *
 *  This device type deals with ARM PrimeCells and anything अन्यथा that
 *  presents a proper CID (0xB105F00D) at the end of the I/O रेजिस्टर
 *  region or that is derived from a PrimeCell.
 *
 *  Copyright (C) 2003 Deep Blue Solutions Ltd, All Rights Reserved.
 */
#अगर_अघोषित ASMARM_AMBA_H
#घोषणा ASMARM_AMBA_H

#समावेश <linux/clk.h>
#समावेश <linux/device.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/err.h>
#समावेश <linux/resource.h>
#समावेश <linux/regulator/consumer.h>

#घोषणा AMBA_NR_IRQS	9
#घोषणा AMBA_CID	0xb105f00d
#घोषणा CORESIGHT_CID	0xb105900d

/*
 * CoreSight Architecture specअगरication updates the ID specअगरication
 * क्रम components on the AMBA bus. (ARM IHI 0029E)
 *
 * Bits 15:12 of the CID are the device class.
 *
 * Class 0xF reमुख्यs क्रम PrimeCell and legacy components. (AMBA_CID above)
 * Class 0x9 defines the component as CoreSight (CORESIGHT_CID above)
 * Class 0x0, 0x1, 0xB, 0xE define components that करो not have driver support
 * at present.
 * Class 0x2-0x8,0xA and 0xD-0xD are presently reserved.
 *
 * Reमुख्यing CID bits stay as 0xb105-00d
 */

/**
 * Class 0x9 components use additional values to क्रमm a Unique Component
 * Identअगरier (UCI), where peripheral ID values are identical क्रम dअगरferent
 * components. Passed to the amba bus code from the component driver via
 * the amba_id->data poपूर्णांकer.
 * @devarch	: coresight devarch रेजिस्टर value
 * @devarch_mask: mask bits used क्रम matching. 0 indicates UCI not used.
 * @devtype	: coresight device type value
 * @data	: additional driver data. As we have usurped the original
 *		poपूर्णांकer some devices may still need additional data
 */
काष्ठा amba_cs_uci_id अणु
	अचिन्हित पूर्णांक devarch;
	अचिन्हित पूर्णांक devarch_mask;
	अचिन्हित पूर्णांक devtype;
	व्योम *data;
पूर्ण;

/* define offsets क्रम रेजिस्टरs used by UCI */
#घोषणा UCI_REG_DEVTYPE_OFFSET	0xFCC
#घोषणा UCI_REG_DEVARCH_OFFSET	0xFBC

काष्ठा clk;

काष्ठा amba_device अणु
	काष्ठा device		dev;
	काष्ठा resource		res;
	काष्ठा clk		*pclk;
	काष्ठा device_dma_parameters dma_parms;
	अचिन्हित पूर्णांक		periphid;
	अचिन्हित पूर्णांक		cid;
	काष्ठा amba_cs_uci_id	uci;
	अचिन्हित पूर्णांक		irq[AMBA_NR_IRQS];
	अक्षर			*driver_override;
पूर्ण;

काष्ठा amba_driver अणु
	काष्ठा device_driver	drv;
	पूर्णांक			(*probe)(काष्ठा amba_device *, स्थिर काष्ठा amba_id *);
	व्योम			(*हटाओ)(काष्ठा amba_device *);
	व्योम			(*shutकरोwn)(काष्ठा amba_device *);
	स्थिर काष्ठा amba_id	*id_table;
पूर्ण;

/*
 * Constants क्रम the designer field of the Peripheral ID रेजिस्टर. When bit 7
 * is set to '1', bits [6:0] should be the JEP106 manufacturer identity code.
 */
क्रमागत amba_venकरोr अणु
	AMBA_VENDOR_ARM = 0x41,
	AMBA_VENDOR_ST = 0x80,
	AMBA_VENDOR_QCOM = 0x51,
	AMBA_VENDOR_LSI = 0xb6,
	AMBA_VENDOR_LINUX = 0xfe,	/* This value is not official */
पूर्ण;

/* This is used to generate pseuकरो-ID क्रम AMBA device */
#घोषणा AMBA_LINUX_ID(conf, rev, part) \
	(((conf) & 0xff) << 24 | ((rev) & 0xf) << 20 | \
	AMBA_VENDOR_LINUX << 12 | ((part) & 0xfff))

बाह्य काष्ठा bus_type amba_bustype;

#घोषणा to_amba_device(d)	container_of(d, काष्ठा amba_device, dev)

#घोषणा amba_get_drvdata(d)	dev_get_drvdata(&d->dev)
#घोषणा amba_set_drvdata(d,p)	dev_set_drvdata(&d->dev, p)

#अगर_घोषित CONFIG_ARM_AMBA
पूर्णांक amba_driver_रेजिस्टर(काष्ठा amba_driver *);
व्योम amba_driver_unरेजिस्टर(काष्ठा amba_driver *);
#अन्यथा
अटल अंतरभूत पूर्णांक amba_driver_रेजिस्टर(काष्ठा amba_driver *drv)
अणु
	वापस -EINVAL;
पूर्ण
अटल अंतरभूत व्योम amba_driver_unरेजिस्टर(काष्ठा amba_driver *drv)
अणु
पूर्ण
#पूर्ण_अगर

काष्ठा amba_device *amba_device_alloc(स्थिर अक्षर *, resource_माप_प्रकार, माप_प्रकार);
व्योम amba_device_put(काष्ठा amba_device *);
पूर्णांक amba_device_add(काष्ठा amba_device *, काष्ठा resource *);
पूर्णांक amba_device_रेजिस्टर(काष्ठा amba_device *, काष्ठा resource *);
काष्ठा amba_device *amba_apb_device_add(काष्ठा device *parent, स्थिर अक्षर *name,
					resource_माप_प्रकार base, माप_प्रकार size,
					पूर्णांक irq1, पूर्णांक irq2, व्योम *pdata,
					अचिन्हित पूर्णांक periphid);
काष्ठा amba_device *amba_ahb_device_add(काष्ठा device *parent, स्थिर अक्षर *name,
					resource_माप_प्रकार base, माप_प्रकार size,
					पूर्णांक irq1, पूर्णांक irq2, व्योम *pdata,
					अचिन्हित पूर्णांक periphid);
काष्ठा amba_device *
amba_apb_device_add_res(काष्ठा device *parent, स्थिर अक्षर *name,
			resource_माप_प्रकार base, माप_प्रकार size, पूर्णांक irq1,
			पूर्णांक irq2, व्योम *pdata, अचिन्हित पूर्णांक periphid,
			काष्ठा resource *resbase);
काष्ठा amba_device *
amba_ahb_device_add_res(काष्ठा device *parent, स्थिर अक्षर *name,
			resource_माप_प्रकार base, माप_प्रकार size, पूर्णांक irq1,
			पूर्णांक irq2, व्योम *pdata, अचिन्हित पूर्णांक periphid,
			काष्ठा resource *resbase);
व्योम amba_device_unरेजिस्टर(काष्ठा amba_device *);
काष्ठा amba_device *amba_find_device(स्थिर अक्षर *, काष्ठा device *, अचिन्हित पूर्णांक, अचिन्हित पूर्णांक);
पूर्णांक amba_request_regions(काष्ठा amba_device *, स्थिर अक्षर *);
व्योम amba_release_regions(काष्ठा amba_device *);

अटल अंतरभूत पूर्णांक amba_pclk_enable(काष्ठा amba_device *dev)
अणु
	वापस clk_enable(dev->pclk);
पूर्ण

अटल अंतरभूत व्योम amba_pclk_disable(काष्ठा amba_device *dev)
अणु
	clk_disable(dev->pclk);
पूर्ण

अटल अंतरभूत पूर्णांक amba_pclk_prepare(काष्ठा amba_device *dev)
अणु
	वापस clk_prepare(dev->pclk);
पूर्ण

अटल अंतरभूत व्योम amba_pclk_unprepare(काष्ठा amba_device *dev)
अणु
	clk_unprepare(dev->pclk);
पूर्ण

/* Some drivers करोn't use the काष्ठा amba_device */
#घोषणा AMBA_CONFIG_BITS(a) (((a) >> 24) & 0xff)
#घोषणा AMBA_REV_BITS(a) (((a) >> 20) & 0x0f)
#घोषणा AMBA_MANF_BITS(a) (((a) >> 12) & 0xff)
#घोषणा AMBA_PART_BITS(a) ((a) & 0xfff)

#घोषणा amba_config(d)	AMBA_CONFIG_BITS((d)->periphid)
#घोषणा amba_rev(d)	AMBA_REV_BITS((d)->periphid)
#घोषणा amba_manf(d)	AMBA_MANF_BITS((d)->periphid)
#घोषणा amba_part(d)	AMBA_PART_BITS((d)->periphid)

#घोषणा __AMBA_DEV(busid, data, mask)				\
	अणु							\
		.coherent_dma_mask = mask,			\
		.init_name = busid,				\
		.platक्रमm_data = data,				\
	पूर्ण

/*
 * APB devices करो not themselves have the ability to address memory,
 * so DMA masks should be zero (much like USB peripheral devices.)
 * The DMA controller DMA masks should be used instead (much like
 * USB host controllers in conventional PCs.)
 */
#घोषणा AMBA_APB_DEVICE(name, busid, id, base, irqs, data)	\
काष्ठा amba_device name##_device = अणु				\
	.dev = __AMBA_DEV(busid, data, 0),			\
	.res = DEFINE_RES_MEM(base, SZ_4K),			\
	.irq = irqs,						\
	.periphid = id,						\
पूर्ण

/*
 * AHB devices are DMA capable, so set their DMA masks
 */
#घोषणा AMBA_AHB_DEVICE(name, busid, id, base, irqs, data)	\
काष्ठा amba_device name##_device = अणु				\
	.dev = __AMBA_DEV(busid, data, ~0ULL),			\
	.res = DEFINE_RES_MEM(base, SZ_4K),			\
	.irq = irqs,						\
	.periphid = id,						\
पूर्ण

/*
 * module_amba_driver() - Helper macro क्रम drivers that करोn't करो anything
 * special in module init/निकास.  This eliminates a lot of boilerplate.  Each
 * module may only use this macro once, and calling it replaces module_init()
 * and module_निकास()
 */
#घोषणा module_amba_driver(__amba_drv) \
	module_driver(__amba_drv, amba_driver_रेजिस्टर, amba_driver_unरेजिस्टर)

/*
 * builtin_amba_driver() - Helper macro क्रम drivers that करोn't करो anything
 * special in driver initcall.  This eliminates a lot of boilerplate.  Each
 * driver may only use this macro once, and calling it replaces the instance
 * device_initcall().
 */
#घोषणा builtin_amba_driver(__amba_drv) \
	builtin_driver(__amba_drv, amba_driver_रेजिस्टर)

#पूर्ण_अगर
