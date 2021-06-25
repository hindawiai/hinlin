<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0
 *
 * Copyright (C) 2019 Texas Instruments Incorporated - https://www.ti.com/
 */

#अगर_अघोषित __LINUX_MTD_HYPERBUS_H__
#घोषणा __LINUX_MTD_HYPERBUS_H__

#समावेश <linux/mtd/map.h>

/* HyperBus command bits */
#घोषणा HYPERBUS_RW	0x80	/* R/W# */
#घोषणा HYPERBUS_RW_WRITE 0
#घोषणा HYPERBUS_RW_READ 0x80
#घोषणा HYPERBUS_AS	0x40	/* Address Space */
#घोषणा HYPERBUS_AS_MEM	0
#घोषणा HYPERBUS_AS_REG	0x40
#घोषणा HYPERBUS_BT	0x20	/* Burst Type */
#घोषणा HYPERBUS_BT_WRAPPED 0
#घोषणा HYPERBUS_BT_LINEAR 0x20

क्रमागत hyperbus_memtype अणु
	HYPERFLASH,
	HYPERRAM,
पूर्ण;

/**
 * काष्ठा hyperbus_device - काष्ठा representing HyperBus slave device
 * @map: map_info काष्ठा क्रम accessing MMIO HyperBus flash memory
 * @np: poपूर्णांकer to HyperBus slave device node
 * @mtd: poपूर्णांकer to MTD काष्ठा
 * @ctlr: poपूर्णांकer to HyperBus controller काष्ठा
 * @memtype: type of memory device: HyperFlash or HyperRAM
 * @priv: poपूर्णांकer to controller specअगरic per device निजी data
 */

काष्ठा hyperbus_device अणु
	काष्ठा map_info map;
	काष्ठा device_node *np;
	काष्ठा mtd_info *mtd;
	काष्ठा hyperbus_ctlr *ctlr;
	क्रमागत hyperbus_memtype memtype;
	व्योम *priv;
पूर्ण;

/**
 * काष्ठा hyperbus_ops - काष्ठा representing custom HyperBus operations
 * @पढ़ो16: पढ़ो 16 bit of data from flash in a single burst. Used to पढ़ो
 *          from non शेष address space, such as ID/CFI space
 * @ग_लिखो16: ग_लिखो 16 bit of data to flash in a single burst. Used to
 *           send cmd to flash or ग_लिखो single 16 bit word at a समय.
 * @copy_from: copy data from flash memory
 * @copy_to: copy data to flash memory
 * @calibrate: calibrate HyperBus controller
 */

काष्ठा hyperbus_ops अणु
	u16 (*पढ़ो16)(काष्ठा hyperbus_device *hbdev, अचिन्हित दीर्घ addr);
	व्योम (*ग_लिखो16)(काष्ठा hyperbus_device *hbdev,
			अचिन्हित दीर्घ addr, u16 val);
	व्योम (*copy_from)(काष्ठा hyperbus_device *hbdev, व्योम *to,
			  अचिन्हित दीर्घ from, sमाप_प्रकार len);
	व्योम (*copy_to)(काष्ठा hyperbus_device *dev, अचिन्हित दीर्घ to,
			स्थिर व्योम *from, sमाप_प्रकार len);
	पूर्णांक (*calibrate)(काष्ठा hyperbus_device *dev);
पूर्ण;

/**
 * काष्ठा hyperbus_ctlr - काष्ठा representing HyperBus controller
 * @dev: poपूर्णांकer to HyperBus controller device
 * @calibrated: flag to indicate ctlr calibration sequence is complete
 * @ops: HyperBus controller ops
 */
काष्ठा hyperbus_ctlr अणु
	काष्ठा device *dev;
	bool calibrated;

	स्थिर काष्ठा hyperbus_ops *ops;
पूर्ण;

/**
 * hyperbus_रेजिस्टर_device - probe and रेजिस्टर a HyperBus slave memory device
 * @hbdev: hyperbus_device काष्ठा with dev, np and ctlr field populated
 *
 * Return: 0 क्रम success, others क्रम failure.
 */
पूर्णांक hyperbus_रेजिस्टर_device(काष्ठा hyperbus_device *hbdev);

/**
 * hyperbus_unरेजिस्टर_device - deरेजिस्टर HyperBus slave memory device
 * @hbdev: hyperbus_device to be unरेजिस्टरed
 *
 * Return: 0 क्रम success, others क्रम failure.
 */
पूर्णांक hyperbus_unरेजिस्टर_device(काष्ठा hyperbus_device *hbdev);

#पूर्ण_अगर /* __LINUX_MTD_HYPERBUS_H__ */
