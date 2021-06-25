<शैली गुरु>
/* SPDX-License-Identअगरier: BSD-3-Clause */
/*
 * Remote processor messaging
 *
 * Copyright (C) 2011 Texas Instruments, Inc.
 * Copyright (C) 2011 Google, Inc.
 * All rights reserved.
 */

#अगर_अघोषित _LINUX_RPMSG_H
#घोषणा _LINUX_RPMSG_H

#समावेश <linux/types.h>
#समावेश <linux/device.h>
#समावेश <linux/err.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/kref.h>
#समावेश <linux/mutex.h>
#समावेश <linux/poll.h>
#समावेश <linux/rpmsg/byteorder.h>
#समावेश <uapi/linux/rpmsg.h>

काष्ठा rpmsg_device;
काष्ठा rpmsg_endpoपूर्णांक;
काष्ठा rpmsg_device_ops;
काष्ठा rpmsg_endpoपूर्णांक_ops;

/**
 * काष्ठा rpmsg_channel_info - channel info representation
 * @name: name of service
 * @src: local address
 * @dst: destination address
 */
काष्ठा rpmsg_channel_info अणु
	अक्षर name[RPMSG_NAME_SIZE];
	u32 src;
	u32 dst;
पूर्ण;

/**
 * rpmsg_device - device that beदीर्घ to the rpmsg bus
 * @dev: the device काष्ठा
 * @id: device id (used to match between rpmsg drivers and devices)
 * @driver_override: driver name to क्रमce a match
 * @src: local address
 * @dst: destination address
 * @ept: the rpmsg endpoपूर्णांक of this channel
 * @announce: अगर set, rpmsg will announce the creation/removal of this channel
 * @little_endian: True अगर transport is using little endian byte representation
 */
काष्ठा rpmsg_device अणु
	काष्ठा device dev;
	काष्ठा rpmsg_device_id id;
	अक्षर *driver_override;
	u32 src;
	u32 dst;
	काष्ठा rpmsg_endpoपूर्णांक *ept;
	bool announce;
	bool little_endian;

	स्थिर काष्ठा rpmsg_device_ops *ops;
पूर्ण;

प्रकार पूर्णांक (*rpmsg_rx_cb_t)(काष्ठा rpmsg_device *, व्योम *, पूर्णांक, व्योम *, u32);

/**
 * काष्ठा rpmsg_endpoपूर्णांक - binds a local rpmsg address to its user
 * @rpdev: rpmsg channel device
 * @refcount: when this drops to zero, the ept is deallocated
 * @cb: rx callback handler
 * @cb_lock: must be taken beक्रमe accessing/changing @cb
 * @addr: local rpmsg address
 * @priv: निजी data क्रम the driver's use
 *
 * In essence, an rpmsg endpoपूर्णांक represents a listener on the rpmsg bus, as
 * it binds an rpmsg address with an rx callback handler.
 *
 * Simple rpmsg drivers shouldn't use this काष्ठा directly, because
 * things just work: every rpmsg driver provides an rx callback upon
 * रेजिस्टरing to the bus, and that callback is then bound to its rpmsg
 * address when the driver is probed. When relevant inbound messages arrive
 * (i.e. messages which their dst address equals to the src address of
 * the rpmsg channel), the driver's handler is invoked to process it.
 *
 * More complicated drivers though, that करो need to allocate additional rpmsg
 * addresses, and bind them to dअगरferent rx callbacks, must explicitly
 * create additional endpoपूर्णांकs by themselves (see rpmsg_create_ept()).
 */
काष्ठा rpmsg_endpoपूर्णांक अणु
	काष्ठा rpmsg_device *rpdev;
	काष्ठा kref refcount;
	rpmsg_rx_cb_t cb;
	काष्ठा mutex cb_lock;
	u32 addr;
	व्योम *priv;

	स्थिर काष्ठा rpmsg_endpoपूर्णांक_ops *ops;
पूर्ण;

/**
 * काष्ठा rpmsg_driver - rpmsg driver काष्ठा
 * @drv: underlying device driver
 * @id_table: rpmsg ids serviced by this driver
 * @probe: invoked when a matching rpmsg channel (i.e. device) is found
 * @हटाओ: invoked when the rpmsg channel is हटाओd
 * @callback: invoked when an inbound message is received on the channel
 */
काष्ठा rpmsg_driver अणु
	काष्ठा device_driver drv;
	स्थिर काष्ठा rpmsg_device_id *id_table;
	पूर्णांक (*probe)(काष्ठा rpmsg_device *dev);
	व्योम (*हटाओ)(काष्ठा rpmsg_device *dev);
	पूर्णांक (*callback)(काष्ठा rpmsg_device *, व्योम *, पूर्णांक, व्योम *, u32);
पूर्ण;

अटल अंतरभूत u16 rpmsg16_to_cpu(काष्ठा rpmsg_device *rpdev, __rpmsg16 val)
अणु
	अगर (!rpdev)
		वापस __rpmsg16_to_cpu(rpmsg_is_little_endian(), val);
	अन्यथा
		वापस __rpmsg16_to_cpu(rpdev->little_endian, val);
पूर्ण

अटल अंतरभूत __rpmsg16 cpu_to_rpmsg16(काष्ठा rpmsg_device *rpdev, u16 val)
अणु
	अगर (!rpdev)
		वापस __cpu_to_rpmsg16(rpmsg_is_little_endian(), val);
	अन्यथा
		वापस __cpu_to_rpmsg16(rpdev->little_endian, val);
पूर्ण

अटल अंतरभूत u32 rpmsg32_to_cpu(काष्ठा rpmsg_device *rpdev, __rpmsg32 val)
अणु
	अगर (!rpdev)
		वापस __rpmsg32_to_cpu(rpmsg_is_little_endian(), val);
	अन्यथा
		वापस __rpmsg32_to_cpu(rpdev->little_endian, val);
पूर्ण

अटल अंतरभूत __rpmsg32 cpu_to_rpmsg32(काष्ठा rpmsg_device *rpdev, u32 val)
अणु
	अगर (!rpdev)
		वापस __cpu_to_rpmsg32(rpmsg_is_little_endian(), val);
	अन्यथा
		वापस __cpu_to_rpmsg32(rpdev->little_endian, val);
पूर्ण

अटल अंतरभूत u64 rpmsg64_to_cpu(काष्ठा rpmsg_device *rpdev, __rpmsg64 val)
अणु
	अगर (!rpdev)
		वापस __rpmsg64_to_cpu(rpmsg_is_little_endian(), val);
	अन्यथा
		वापस __rpmsg64_to_cpu(rpdev->little_endian, val);
पूर्ण

अटल अंतरभूत __rpmsg64 cpu_to_rpmsg64(काष्ठा rpmsg_device *rpdev, u64 val)
अणु
	अगर (!rpdev)
		वापस __cpu_to_rpmsg64(rpmsg_is_little_endian(), val);
	अन्यथा
		वापस __cpu_to_rpmsg64(rpdev->little_endian, val);
पूर्ण

#अगर IS_ENABLED(CONFIG_RPMSG)

पूर्णांक rpmsg_रेजिस्टर_device(काष्ठा rpmsg_device *rpdev);
पूर्णांक rpmsg_unरेजिस्टर_device(काष्ठा device *parent,
			    काष्ठा rpmsg_channel_info *chinfo);
पूर्णांक __रेजिस्टर_rpmsg_driver(काष्ठा rpmsg_driver *drv, काष्ठा module *owner);
व्योम unरेजिस्टर_rpmsg_driver(काष्ठा rpmsg_driver *drv);
व्योम rpmsg_destroy_ept(काष्ठा rpmsg_endpoपूर्णांक *);
काष्ठा rpmsg_endpoपूर्णांक *rpmsg_create_ept(काष्ठा rpmsg_device *,
					rpmsg_rx_cb_t cb, व्योम *priv,
					काष्ठा rpmsg_channel_info chinfo);

पूर्णांक rpmsg_send(काष्ठा rpmsg_endpoपूर्णांक *ept, व्योम *data, पूर्णांक len);
पूर्णांक rpmsg_sendto(काष्ठा rpmsg_endpoपूर्णांक *ept, व्योम *data, पूर्णांक len, u32 dst);
पूर्णांक rpmsg_send_offchannel(काष्ठा rpmsg_endpoपूर्णांक *ept, u32 src, u32 dst,
			  व्योम *data, पूर्णांक len);

पूर्णांक rpmsg_trysend(काष्ठा rpmsg_endpoपूर्णांक *ept, व्योम *data, पूर्णांक len);
पूर्णांक rpmsg_trysendto(काष्ठा rpmsg_endpoपूर्णांक *ept, व्योम *data, पूर्णांक len, u32 dst);
पूर्णांक rpmsg_trysend_offchannel(काष्ठा rpmsg_endpoपूर्णांक *ept, u32 src, u32 dst,
			     व्योम *data, पूर्णांक len);

__poll_t rpmsg_poll(काष्ठा rpmsg_endpoपूर्णांक *ept, काष्ठा file *filp,
			poll_table *रुको);

#अन्यथा

अटल अंतरभूत पूर्णांक rpmsg_रेजिस्टर_device(काष्ठा rpmsg_device *rpdev)
अणु
	वापस -ENXIO;
पूर्ण

अटल अंतरभूत पूर्णांक rpmsg_unरेजिस्टर_device(काष्ठा device *parent,
					  काष्ठा rpmsg_channel_info *chinfo)
अणु
	/* This shouldn't be possible */
	WARN_ON(1);

	वापस -ENXIO;
पूर्ण

अटल अंतरभूत पूर्णांक __रेजिस्टर_rpmsg_driver(काष्ठा rpmsg_driver *drv,
					  काष्ठा module *owner)
अणु
	/* This shouldn't be possible */
	WARN_ON(1);

	वापस -ENXIO;
पूर्ण

अटल अंतरभूत व्योम unरेजिस्टर_rpmsg_driver(काष्ठा rpmsg_driver *drv)
अणु
	/* This shouldn't be possible */
	WARN_ON(1);
पूर्ण

अटल अंतरभूत व्योम rpmsg_destroy_ept(काष्ठा rpmsg_endpoपूर्णांक *ept)
अणु
	/* This shouldn't be possible */
	WARN_ON(1);
पूर्ण

अटल अंतरभूत काष्ठा rpmsg_endpoपूर्णांक *rpmsg_create_ept(काष्ठा rpmsg_device *rpdev,
						      rpmsg_rx_cb_t cb,
						      व्योम *priv,
						      काष्ठा rpmsg_channel_info chinfo)
अणु
	/* This shouldn't be possible */
	WARN_ON(1);

	वापस ERR_PTR(-ENXIO);
पूर्ण

अटल अंतरभूत पूर्णांक rpmsg_send(काष्ठा rpmsg_endpoपूर्णांक *ept, व्योम *data, पूर्णांक len)
अणु
	/* This shouldn't be possible */
	WARN_ON(1);

	वापस -ENXIO;
पूर्ण

अटल अंतरभूत पूर्णांक rpmsg_sendto(काष्ठा rpmsg_endpoपूर्णांक *ept, व्योम *data, पूर्णांक len,
			       u32 dst)
अणु
	/* This shouldn't be possible */
	WARN_ON(1);

	वापस -ENXIO;

पूर्ण

अटल अंतरभूत पूर्णांक rpmsg_send_offchannel(काष्ठा rpmsg_endpoपूर्णांक *ept, u32 src,
					u32 dst, व्योम *data, पूर्णांक len)
अणु
	/* This shouldn't be possible */
	WARN_ON(1);

	वापस -ENXIO;
पूर्ण

अटल अंतरभूत पूर्णांक rpmsg_trysend(काष्ठा rpmsg_endpoपूर्णांक *ept, व्योम *data, पूर्णांक len)
अणु
	/* This shouldn't be possible */
	WARN_ON(1);

	वापस -ENXIO;
पूर्ण

अटल अंतरभूत पूर्णांक rpmsg_trysendto(काष्ठा rpmsg_endpoपूर्णांक *ept, व्योम *data,
				  पूर्णांक len, u32 dst)
अणु
	/* This shouldn't be possible */
	WARN_ON(1);

	वापस -ENXIO;
पूर्ण

अटल अंतरभूत पूर्णांक rpmsg_trysend_offchannel(काष्ठा rpmsg_endpoपूर्णांक *ept, u32 src,
					   u32 dst, व्योम *data, पूर्णांक len)
अणु
	/* This shouldn't be possible */
	WARN_ON(1);

	वापस -ENXIO;
पूर्ण

अटल अंतरभूत __poll_t rpmsg_poll(काष्ठा rpmsg_endpoपूर्णांक *ept,
				      काष्ठा file *filp, poll_table *रुको)
अणु
	/* This shouldn't be possible */
	WARN_ON(1);

	वापस 0;
पूर्ण

#पूर्ण_अगर /* IS_ENABLED(CONFIG_RPMSG) */

/* use a macro to aव्योम include chaining to get THIS_MODULE */
#घोषणा रेजिस्टर_rpmsg_driver(drv) \
	__रेजिस्टर_rpmsg_driver(drv, THIS_MODULE)

/**
 * module_rpmsg_driver() - Helper macro क्रम रेजिस्टरing an rpmsg driver
 * @__rpmsg_driver: rpmsg_driver काष्ठा
 *
 * Helper macro क्रम rpmsg drivers which करो not करो anything special in module
 * init/निकास. This eliminates a lot of boilerplate.  Each module may only
 * use this macro once, and calling it replaces module_init() and module_निकास()
 */
#घोषणा module_rpmsg_driver(__rpmsg_driver) \
	module_driver(__rpmsg_driver, रेजिस्टर_rpmsg_driver, \
			unरेजिस्टर_rpmsg_driver)

#पूर्ण_अगर /* _LINUX_RPMSG_H */
