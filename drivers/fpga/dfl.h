<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Driver Header File क्रम FPGA Device Feature List (DFL) Support
 *
 * Copyright (C) 2017-2018 Intel Corporation, Inc.
 *
 * Authors:
 *   Kang Luwei <luwei.kang@पूर्णांकel.com>
 *   Zhang Yi <yi.z.zhang@पूर्णांकel.com>
 *   Wu Hao <hao.wu@पूर्णांकel.com>
 *   Xiao Guangrong <guangrong.xiao@linux.पूर्णांकel.com>
 */

#अगर_अघोषित __FPGA_DFL_H
#घोषणा __FPGA_DFL_H

#समावेश <linux/bitfield.h>
#समावेश <linux/cdev.h>
#समावेश <linux/delay.h>
#समावेश <linux/eventfd.h>
#समावेश <linux/fs.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/iopoll.h>
#समावेश <linux/io-64-nonatomic-lo-hi.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>
#समावेश <linux/uuid.h>
#समावेश <linux/fpga/fpga-region.h>

/* maximum supported number of ports */
#घोषणा MAX_DFL_FPGA_PORT_NUM 4
/* plus one क्रम fme device */
#घोषणा MAX_DFL_FEATURE_DEV_NUM    (MAX_DFL_FPGA_PORT_NUM + 1)

/* Reserved 0xfe क्रम Header Group Register and 0xff क्रम AFU */
#घोषणा FEATURE_ID_FIU_HEADER		0xfe
#घोषणा FEATURE_ID_AFU			0xff

#घोषणा FME_FEATURE_ID_HEADER		FEATURE_ID_FIU_HEADER
#घोषणा FME_FEATURE_ID_THERMAL_MGMT	0x1
#घोषणा FME_FEATURE_ID_POWER_MGMT	0x2
#घोषणा FME_FEATURE_ID_GLOBAL_IPERF	0x3
#घोषणा FME_FEATURE_ID_GLOBAL_ERR	0x4
#घोषणा FME_FEATURE_ID_PR_MGMT		0x5
#घोषणा FME_FEATURE_ID_HSSI		0x6
#घोषणा FME_FEATURE_ID_GLOBAL_DPERF	0x7

#घोषणा PORT_FEATURE_ID_HEADER		FEATURE_ID_FIU_HEADER
#घोषणा PORT_FEATURE_ID_AFU		FEATURE_ID_AFU
#घोषणा PORT_FEATURE_ID_ERROR		0x10
#घोषणा PORT_FEATURE_ID_UMSG		0x11
#घोषणा PORT_FEATURE_ID_UINT		0x12
#घोषणा PORT_FEATURE_ID_STP		0x13

/*
 * Device Feature Header Register Set
 *
 * For FIUs, they all have DFH + GUID + NEXT_AFU as common header रेजिस्टरs.
 * For AFUs, they have DFH + GUID as common header रेजिस्टरs.
 * For निजी features, they only have DFH रेजिस्टर as common header.
 */
#घोषणा DFH			0x0
#घोषणा GUID_L			0x8
#घोषणा GUID_H			0x10
#घोषणा NEXT_AFU		0x18

#घोषणा DFH_SIZE		0x8

/* Device Feature Header Register Bitfield */
#घोषणा DFH_ID			GENMASK_ULL(11, 0)	/* Feature ID */
#घोषणा DFH_ID_FIU_FME		0
#घोषणा DFH_ID_FIU_PORT		1
#घोषणा DFH_REVISION		GENMASK_ULL(15, 12)	/* Feature revision */
#घोषणा DFH_NEXT_HDR_OFST	GENMASK_ULL(39, 16)	/* Offset to next DFH */
#घोषणा DFH_EOL			BIT_ULL(40)		/* End of list */
#घोषणा DFH_TYPE		GENMASK_ULL(63, 60)	/* Feature type */
#घोषणा DFH_TYPE_AFU		1
#घोषणा DFH_TYPE_PRIVATE	3
#घोषणा DFH_TYPE_FIU		4

/* Next AFU Register Bitfield */
#घोषणा NEXT_AFU_NEXT_DFH_OFST	GENMASK_ULL(23, 0)	/* Offset to next AFU */

/* FME Header Register Set */
#घोषणा FME_HDR_DFH		DFH
#घोषणा FME_HDR_GUID_L		GUID_L
#घोषणा FME_HDR_GUID_H		GUID_H
#घोषणा FME_HDR_NEXT_AFU	NEXT_AFU
#घोषणा FME_HDR_CAP		0x30
#घोषणा FME_HDR_PORT_OFST(n)	(0x38 + ((n) * 0x8))
#घोषणा FME_HDR_BITSTREAM_ID	0x60
#घोषणा FME_HDR_BITSTREAM_MD	0x68

/* FME Fab Capability Register Bitfield */
#घोषणा FME_CAP_FABRIC_VERID	GENMASK_ULL(7, 0)	/* Fabric version ID */
#घोषणा FME_CAP_SOCKET_ID	BIT_ULL(8)		/* Socket ID */
#घोषणा FME_CAP_PCIE0_LINK_AVL	BIT_ULL(12)		/* PCIE0 Link */
#घोषणा FME_CAP_PCIE1_LINK_AVL	BIT_ULL(13)		/* PCIE1 Link */
#घोषणा FME_CAP_COHR_LINK_AVL	BIT_ULL(14)		/* Coherent Link */
#घोषणा FME_CAP_IOMMU_AVL	BIT_ULL(16)		/* IOMMU available */
#घोषणा FME_CAP_NUM_PORTS	GENMASK_ULL(19, 17)	/* Number of ports */
#घोषणा FME_CAP_ADDR_WIDTH	GENMASK_ULL(29, 24)	/* Address bus width */
#घोषणा FME_CAP_CACHE_SIZE	GENMASK_ULL(43, 32)	/* cache size in KB */
#घोषणा FME_CAP_CACHE_ASSOC	GENMASK_ULL(47, 44)	/* Associativity */

/* FME Port Offset Register Bitfield */
/* Offset to port device feature header */
#घोषणा FME_PORT_OFST_DFH_OFST	GENMASK_ULL(23, 0)
/* PCI Bar ID क्रम this port */
#घोषणा FME_PORT_OFST_BAR_ID	GENMASK_ULL(34, 32)
/* AFU MMIO access permission. 1 - VF, 0 - PF. */
#घोषणा FME_PORT_OFST_ACC_CTRL	BIT_ULL(55)
#घोषणा FME_PORT_OFST_ACC_PF	0
#घोषणा FME_PORT_OFST_ACC_VF	1
#घोषणा FME_PORT_OFST_IMP	BIT_ULL(60)

/* FME Error Capability Register */
#घोषणा FME_ERROR_CAP		0x70

/* FME Error Capability Register Bitfield */
#घोषणा FME_ERROR_CAP_SUPP_INT	BIT_ULL(0)		/* Interrupt Support */
#घोषणा FME_ERROR_CAP_INT_VECT	GENMASK_ULL(12, 1)	/* Interrupt vector */

/* PORT Header Register Set */
#घोषणा PORT_HDR_DFH		DFH
#घोषणा PORT_HDR_GUID_L		GUID_L
#घोषणा PORT_HDR_GUID_H		GUID_H
#घोषणा PORT_HDR_NEXT_AFU	NEXT_AFU
#घोषणा PORT_HDR_CAP		0x30
#घोषणा PORT_HDR_CTRL		0x38
#घोषणा PORT_HDR_STS		0x40
#घोषणा PORT_HDR_USRCLK_CMD0	0x50
#घोषणा PORT_HDR_USRCLK_CMD1	0x58
#घोषणा PORT_HDR_USRCLK_STS0	0x60
#घोषणा PORT_HDR_USRCLK_STS1	0x68

/* Port Capability Register Bitfield */
#घोषणा PORT_CAP_PORT_NUM	GENMASK_ULL(1, 0)	/* ID of this port */
#घोषणा PORT_CAP_MMIO_SIZE	GENMASK_ULL(23, 8)	/* MMIO size in KB */
#घोषणा PORT_CAP_SUPP_INT_NUM	GENMASK_ULL(35, 32)	/* Interrupts num */

/* Port Control Register Bitfield */
#घोषणा PORT_CTRL_SFTRST	BIT_ULL(0)		/* Port soft reset */
/* Latency tolerance reporting. '1' >= 40us, '0' < 40us.*/
#घोषणा PORT_CTRL_LATENCY	BIT_ULL(2)
#घोषणा PORT_CTRL_SFTRST_ACK	BIT_ULL(4)		/* HW ack क्रम reset */

/* Port Status Register Bitfield */
#घोषणा PORT_STS_AP2_EVT	BIT_ULL(13)		/* AP2 event detected */
#घोषणा PORT_STS_AP1_EVT	BIT_ULL(12)		/* AP1 event detected */
#घोषणा PORT_STS_PWR_STATE	GENMASK_ULL(11, 8)	/* AFU घातer states */
#घोषणा PORT_STS_PWR_STATE_NORM 0
#घोषणा PORT_STS_PWR_STATE_AP1	1			/* 50% throttling */
#घोषणा PORT_STS_PWR_STATE_AP2	2			/* 90% throttling */
#घोषणा PORT_STS_PWR_STATE_AP6	6			/* 100% throttling */

/* Port Error Capability Register */
#घोषणा PORT_ERROR_CAP		0x38

/* Port Error Capability Register Bitfield */
#घोषणा PORT_ERROR_CAP_SUPP_INT	BIT_ULL(0)		/* Interrupt Support */
#घोषणा PORT_ERROR_CAP_INT_VECT	GENMASK_ULL(12, 1)	/* Interrupt vector */

/* Port Uपूर्णांक Capability Register */
#घोषणा PORT_UINT_CAP		0x8

/* Port Uपूर्णांक Capability Register Bitfield */
#घोषणा PORT_UINT_CAP_INT_NUM	GENMASK_ULL(11, 0)	/* Interrupts num */
#घोषणा PORT_UINT_CAP_FST_VECT	GENMASK_ULL(23, 12)	/* First Vector */

/**
 * काष्ठा dfl_fpga_port_ops - port ops
 *
 * @name: name of this port ops, to match with port platक्रमm device.
 * @owner: poपूर्णांकer to the module which owns this port ops.
 * @node: node to link port ops to global list.
 * @get_id: get port id from hardware.
 * @enable_set: enable/disable the port.
 */
काष्ठा dfl_fpga_port_ops अणु
	स्थिर अक्षर *name;
	काष्ठा module *owner;
	काष्ठा list_head node;
	पूर्णांक (*get_id)(काष्ठा platक्रमm_device *pdev);
	पूर्णांक (*enable_set)(काष्ठा platक्रमm_device *pdev, bool enable);
पूर्ण;

व्योम dfl_fpga_port_ops_add(काष्ठा dfl_fpga_port_ops *ops);
व्योम dfl_fpga_port_ops_del(काष्ठा dfl_fpga_port_ops *ops);
काष्ठा dfl_fpga_port_ops *dfl_fpga_port_ops_get(काष्ठा platक्रमm_device *pdev);
व्योम dfl_fpga_port_ops_put(काष्ठा dfl_fpga_port_ops *ops);
पूर्णांक dfl_fpga_check_port_id(काष्ठा platक्रमm_device *pdev, व्योम *pport_id);

/**
 * काष्ठा dfl_feature_id - dfl निजी feature id
 *
 * @id: unique dfl निजी feature id.
 */
काष्ठा dfl_feature_id अणु
	u16 id;
पूर्ण;

/**
 * काष्ठा dfl_feature_driver - dfl निजी feature driver
 *
 * @id_table: id_table क्रम dfl निजी features supported by this driver.
 * @ops: ops of this dfl निजी feature driver.
 */
काष्ठा dfl_feature_driver अणु
	स्थिर काष्ठा dfl_feature_id *id_table;
	स्थिर काष्ठा dfl_feature_ops *ops;
पूर्ण;

/**
 * काष्ठा dfl_feature_irq_ctx - dfl निजी feature पूर्णांकerrupt context
 *
 * @irq: Linux IRQ number of this पूर्णांकerrupt.
 * @trigger: eventfd context to संकेत when पूर्णांकerrupt happens.
 * @name: irq name needed when requesting irq.
 */
काष्ठा dfl_feature_irq_ctx अणु
	पूर्णांक irq;
	काष्ठा eventfd_ctx *trigger;
	अक्षर *name;
पूर्ण;

/**
 * काष्ठा dfl_feature - sub feature of the feature devices
 *
 * @dev: ptr to pdev of the feature device which has the sub feature.
 * @id: sub feature id.
 * @resource_index: each sub feature has one mmio resource क्रम its रेजिस्टरs.
 *		    this index is used to find its mmio resource from the
 *		    feature dev (platक्रमm device)'s reources.
 * @ioaddr: mapped mmio resource address.
 * @irq_ctx: पूर्णांकerrupt context list.
 * @nr_irqs: number of पूर्णांकerrupt contexts.
 * @ops: ops of this sub feature.
 * @ddev: ptr to the dfl device of this sub feature.
 * @priv: priv data of this feature.
 */
काष्ठा dfl_feature अणु
	काष्ठा platक्रमm_device *dev;
	u16 id;
	पूर्णांक resource_index;
	व्योम __iomem *ioaddr;
	काष्ठा dfl_feature_irq_ctx *irq_ctx;
	अचिन्हित पूर्णांक nr_irqs;
	स्थिर काष्ठा dfl_feature_ops *ops;
	काष्ठा dfl_device *ddev;
	व्योम *priv;
पूर्ण;

#घोषणा FEATURE_DEV_ID_UNUSED	(-1)

/**
 * काष्ठा dfl_feature_platक्रमm_data - platक्रमm data क्रम feature devices
 *
 * @node: node to link feature devs to container device's port_dev_list.
 * @lock: mutex to protect platक्रमm data.
 * @cdev: cdev of feature dev.
 * @dev: ptr to platक्रमm device linked with this platक्रमm data.
 * @dfl_cdev: ptr to container device.
 * @id: id used क्रम this feature device.
 * @disable_count: count क्रम port disable.
 * @excl_खोलो: set on feature device exclusive खोलो.
 * @खोलो_count: count क्रम feature device खोलो.
 * @num: number क्रम sub features.
 * @निजी: ptr to feature dev निजी data.
 * @features: sub features of this feature dev.
 */
काष्ठा dfl_feature_platक्रमm_data अणु
	काष्ठा list_head node;
	काष्ठा mutex lock;
	काष्ठा cdev cdev;
	काष्ठा platक्रमm_device *dev;
	काष्ठा dfl_fpga_cdev *dfl_cdev;
	पूर्णांक id;
	अचिन्हित पूर्णांक disable_count;
	bool excl_खोलो;
	पूर्णांक खोलो_count;
	व्योम *निजी;
	पूर्णांक num;
	काष्ठा dfl_feature features[];
पूर्ण;

अटल अंतरभूत
पूर्णांक dfl_feature_dev_use_begin(काष्ठा dfl_feature_platक्रमm_data *pdata,
			      bool excl)
अणु
	अगर (pdata->excl_खोलो)
		वापस -EBUSY;

	अगर (excl) अणु
		अगर (pdata->खोलो_count)
			वापस -EBUSY;

		pdata->excl_खोलो = true;
	पूर्ण
	pdata->खोलो_count++;

	वापस 0;
पूर्ण

अटल अंतरभूत
व्योम dfl_feature_dev_use_end(काष्ठा dfl_feature_platक्रमm_data *pdata)
अणु
	pdata->excl_खोलो = false;

	अगर (WARN_ON(pdata->खोलो_count <= 0))
		वापस;

	pdata->खोलो_count--;
पूर्ण

अटल अंतरभूत
पूर्णांक dfl_feature_dev_use_count(काष्ठा dfl_feature_platक्रमm_data *pdata)
अणु
	वापस pdata->खोलो_count;
पूर्ण

अटल अंतरभूत
व्योम dfl_fpga_pdata_set_निजी(काष्ठा dfl_feature_platक्रमm_data *pdata,
				व्योम *निजी)
अणु
	pdata->निजी = निजी;
पूर्ण

अटल अंतरभूत
व्योम *dfl_fpga_pdata_get_निजी(काष्ठा dfl_feature_platक्रमm_data *pdata)
अणु
	वापस pdata->निजी;
पूर्ण

काष्ठा dfl_feature_ops अणु
	पूर्णांक (*init)(काष्ठा platक्रमm_device *pdev, काष्ठा dfl_feature *feature);
	व्योम (*uinit)(काष्ठा platक्रमm_device *pdev,
		      काष्ठा dfl_feature *feature);
	दीर्घ (*ioctl)(काष्ठा platक्रमm_device *pdev, काष्ठा dfl_feature *feature,
		      अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg);
पूर्ण;

#घोषणा DFL_FPGA_FEATURE_DEV_FME		"dfl-fme"
#घोषणा DFL_FPGA_FEATURE_DEV_PORT		"dfl-port"

व्योम dfl_fpga_dev_feature_uinit(काष्ठा platक्रमm_device *pdev);
पूर्णांक dfl_fpga_dev_feature_init(काष्ठा platक्रमm_device *pdev,
			      काष्ठा dfl_feature_driver *feature_drvs);

पूर्णांक dfl_fpga_dev_ops_रेजिस्टर(काष्ठा platक्रमm_device *pdev,
			      स्थिर काष्ठा file_operations *fops,
			      काष्ठा module *owner);
व्योम dfl_fpga_dev_ops_unरेजिस्टर(काष्ठा platक्रमm_device *pdev);

अटल अंतरभूत
काष्ठा platक्रमm_device *dfl_fpga_inode_to_feature_dev(काष्ठा inode *inode)
अणु
	काष्ठा dfl_feature_platक्रमm_data *pdata;

	pdata = container_of(inode->i_cdev, काष्ठा dfl_feature_platक्रमm_data,
			     cdev);
	वापस pdata->dev;
पूर्ण

#घोषणा dfl_fpga_dev_क्रम_each_feature(pdata, feature)			    \
	क्रम ((feature) = (pdata)->features;				    \
	   (feature) < (pdata)->features + (pdata)->num; (feature)++)

अटल अंतरभूत
काष्ठा dfl_feature *dfl_get_feature_by_id(काष्ठा device *dev, u16 id)
अणु
	काष्ठा dfl_feature_platक्रमm_data *pdata = dev_get_platdata(dev);
	काष्ठा dfl_feature *feature;

	dfl_fpga_dev_क्रम_each_feature(pdata, feature)
		अगर (feature->id == id)
			वापस feature;

	वापस शून्य;
पूर्ण

अटल अंतरभूत
व्योम __iomem *dfl_get_feature_ioaddr_by_id(काष्ठा device *dev, u16 id)
अणु
	काष्ठा dfl_feature *feature = dfl_get_feature_by_id(dev, id);

	अगर (feature && feature->ioaddr)
		वापस feature->ioaddr;

	WARN_ON(1);
	वापस शून्य;
पूर्ण

अटल अंतरभूत bool is_dfl_feature_present(काष्ठा device *dev, u16 id)
अणु
	वापस !!dfl_get_feature_ioaddr_by_id(dev, id);
पूर्ण

अटल अंतरभूत
काष्ठा device *dfl_fpga_pdata_to_parent(काष्ठा dfl_feature_platक्रमm_data *pdata)
अणु
	वापस pdata->dev->dev.parent->parent;
पूर्ण

अटल अंतरभूत bool dfl_feature_is_fme(व्योम __iomem *base)
अणु
	u64 v = पढ़ोq(base + DFH);

	वापस (FIELD_GET(DFH_TYPE, v) == DFH_TYPE_FIU) &&
		(FIELD_GET(DFH_ID, v) == DFH_ID_FIU_FME);
पूर्ण

अटल अंतरभूत bool dfl_feature_is_port(व्योम __iomem *base)
अणु
	u64 v = पढ़ोq(base + DFH);

	वापस (FIELD_GET(DFH_TYPE, v) == DFH_TYPE_FIU) &&
		(FIELD_GET(DFH_ID, v) == DFH_ID_FIU_PORT);
पूर्ण

अटल अंतरभूत u8 dfl_feature_revision(व्योम __iomem *base)
अणु
	वापस (u8)FIELD_GET(DFH_REVISION, पढ़ोq(base + DFH));
पूर्ण

/**
 * काष्ठा dfl_fpga_क्रमागत_info - DFL FPGA क्रमागतeration inक्रमmation
 *
 * @dev: parent device.
 * @dfls: list of device feature lists.
 * @nr_irqs: number of irqs क्रम all feature devices.
 * @irq_table: Linux IRQ numbers क्रम all irqs, indexed by hw irq numbers.
 */
काष्ठा dfl_fpga_क्रमागत_info अणु
	काष्ठा device *dev;
	काष्ठा list_head dfls;
	अचिन्हित पूर्णांक nr_irqs;
	पूर्णांक *irq_table;
पूर्ण;

/**
 * काष्ठा dfl_fpga_क्रमागत_dfl - DFL FPGA क्रमागतeration device feature list info
 *
 * @start: base address of this device feature list.
 * @len: size of this device feature list.
 * @node: node in list of device feature lists.
 */
काष्ठा dfl_fpga_क्रमागत_dfl अणु
	resource_माप_प्रकार start;
	resource_माप_प्रकार len;
	काष्ठा list_head node;
पूर्ण;

काष्ठा dfl_fpga_क्रमागत_info *dfl_fpga_क्रमागत_info_alloc(काष्ठा device *dev);
पूर्णांक dfl_fpga_क्रमागत_info_add_dfl(काष्ठा dfl_fpga_क्रमागत_info *info,
			       resource_माप_प्रकार start, resource_माप_प्रकार len);
पूर्णांक dfl_fpga_क्रमागत_info_add_irq(काष्ठा dfl_fpga_क्रमागत_info *info,
			       अचिन्हित पूर्णांक nr_irqs, पूर्णांक *irq_table);
व्योम dfl_fpga_क्रमागत_info_मुक्त(काष्ठा dfl_fpga_क्रमागत_info *info);

/**
 * काष्ठा dfl_fpga_cdev - container device of DFL based FPGA
 *
 * @parent: parent device of this container device.
 * @region: base fpga region.
 * @fme_dev: FME feature device under this container device.
 * @lock: mutex lock to protect the port device list.
 * @port_dev_list: list of all port feature devices under this container device.
 * @released_port_num: released port number under this container device.
 */
काष्ठा dfl_fpga_cdev अणु
	काष्ठा device *parent;
	काष्ठा fpga_region *region;
	काष्ठा device *fme_dev;
	काष्ठा mutex lock;
	काष्ठा list_head port_dev_list;
	पूर्णांक released_port_num;
पूर्ण;

काष्ठा dfl_fpga_cdev *
dfl_fpga_feature_devs_क्रमागतerate(काष्ठा dfl_fpga_क्रमागत_info *info);
व्योम dfl_fpga_feature_devs_हटाओ(काष्ठा dfl_fpga_cdev *cdev);

/*
 * need to drop the device reference with put_device() after use port platक्रमm
 * device वापसed by __dfl_fpga_cdev_find_port and dfl_fpga_cdev_find_port
 * functions.
 */
काष्ठा platक्रमm_device *
__dfl_fpga_cdev_find_port(काष्ठा dfl_fpga_cdev *cdev, व्योम *data,
			  पूर्णांक (*match)(काष्ठा platक्रमm_device *, व्योम *));

अटल अंतरभूत काष्ठा platक्रमm_device *
dfl_fpga_cdev_find_port(काष्ठा dfl_fpga_cdev *cdev, व्योम *data,
			पूर्णांक (*match)(काष्ठा platक्रमm_device *, व्योम *))
अणु
	काष्ठा platक्रमm_device *pdev;

	mutex_lock(&cdev->lock);
	pdev = __dfl_fpga_cdev_find_port(cdev, data, match);
	mutex_unlock(&cdev->lock);

	वापस pdev;
पूर्ण

पूर्णांक dfl_fpga_cdev_release_port(काष्ठा dfl_fpga_cdev *cdev, पूर्णांक port_id);
पूर्णांक dfl_fpga_cdev_assign_port(काष्ठा dfl_fpga_cdev *cdev, पूर्णांक port_id);
व्योम dfl_fpga_cdev_config_ports_pf(काष्ठा dfl_fpga_cdev *cdev);
पूर्णांक dfl_fpga_cdev_config_ports_vf(काष्ठा dfl_fpga_cdev *cdev, पूर्णांक num_vf);
पूर्णांक dfl_fpga_set_irq_triggers(काष्ठा dfl_feature *feature, अचिन्हित पूर्णांक start,
			      अचिन्हित पूर्णांक count, पूर्णांक32_t *fds);
दीर्घ dfl_feature_ioctl_get_num_irqs(काष्ठा platक्रमm_device *pdev,
				    काष्ठा dfl_feature *feature,
				    अचिन्हित दीर्घ arg);
दीर्घ dfl_feature_ioctl_set_irq(काष्ठा platक्रमm_device *pdev,
			       काष्ठा dfl_feature *feature,
			       अचिन्हित दीर्घ arg);

#पूर्ण_अगर /* __FPGA_DFL_H */
