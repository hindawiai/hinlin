<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (C) 2018 Cadence Design Systems Inc.
 *
 * Author: Boris Brezillon <boris.brezillon@bootlin.com>
 */

#अगर_अघोषित I3C_MASTER_H
#घोषणा I3C_MASTER_H

#समावेश <यंत्र/bitsperदीर्घ.h>

#समावेश <linux/bitops.h>
#समावेश <linux/i2c.h>
#समावेश <linux/i3c/ccc.h>
#समावेश <linux/i3c/device.h>
#समावेश <linux/rwsem.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/workqueue.h>

#घोषणा I3C_HOT_JOIN_ADDR		0x2
#घोषणा I3C_BROADCAST_ADDR		0x7e
#घोषणा I3C_MAX_ADDR			GENMASK(6, 0)

काष्ठा i3c_master_controller;
काष्ठा i3c_bus;
काष्ठा i2c_device;
काष्ठा i3c_device;

/**
 * काष्ठा i3c_i2c_dev_desc - Common part of the I3C/I2C device descriptor
 * @node: node element used to insert the slot पूर्णांकo the I2C or I3C device
 *	  list
 * @master: I3C master that instantiated this device. Will be used to करो
 *	    I2C/I3C transfers
 * @master_priv: master निजी data asचिन्हित to the device. Can be used to
 *		 add master specअगरic inक्रमmation
 *
 * This काष्ठाure is describing common I3C/I2C dev inक्रमmation.
 */
काष्ठा i3c_i2c_dev_desc अणु
	काष्ठा list_head node;
	काष्ठा i3c_master_controller *master;
	व्योम *master_priv;
पूर्ण;

#घोषणा I3C_LVR_I2C_INDEX_MASK		GENMASK(7, 5)
#घोषणा I3C_LVR_I2C_INDEX(x)		((x) << 5)
#घोषणा I3C_LVR_I2C_FM_MODE		BIT(4)

#घोषणा I2C_MAX_ADDR			GENMASK(6, 0)

/**
 * काष्ठा i2c_dev_boardinfo - I2C device board inक्रमmation
 * @node: used to insert the boardinfo object in the I2C boardinfo list
 * @base: regular I2C board inक्रमmation
 * @lvr: LVR (Legacy Virtual Register) needed by the I3C core to know about
 *	 the I2C device limitations
 *
 * This काष्ठाure is used to attach board-level inक्रमmation to an I2C device.
 * Each I2C device connected on the I3C bus should have one.
 */
काष्ठा i2c_dev_boardinfo अणु
	काष्ठा list_head node;
	काष्ठा i2c_board_info base;
	u8 lvr;
पूर्ण;

/**
 * काष्ठा i2c_dev_desc - I2C device descriptor
 * @common: common part of the I2C device descriptor
 * @boardinfo: poपूर्णांकer to the boardinfo attached to this I2C device
 * @dev: I2C device object रेजिस्टरed to the I2C framework
 * @addr: I2C device address
 * @lvr: LVR (Legacy Virtual Register) needed by the I3C core to know about
 *	 the I2C device limitations
 *
 * Each I2C device connected on the bus will have an i2c_dev_desc.
 * This object is created by the core and later attached to the controller
 * using &काष्ठा_i3c_master_controller->ops->attach_i2c_dev().
 *
 * &काष्ठा_i2c_dev_desc is the पूर्णांकernal representation of an I2C device
 * connected on an I3C bus. This object is also passed to all
 * &काष्ठा_i3c_master_controller_ops hooks.
 */
काष्ठा i2c_dev_desc अणु
	काष्ठा i3c_i2c_dev_desc common;
	स्थिर काष्ठा i2c_dev_boardinfo *boardinfo;
	काष्ठा i2c_client *dev;
	u16 addr;
	u8 lvr;
पूर्ण;

/**
 * काष्ठा i3c_ibi_slot - I3C IBI (In-Band Interrupt) slot
 * @work: work associated to this slot. The IBI handler will be called from
 *	  there
 * @dev: the I3C device that has generated this IBI
 * @len: length of the payload associated to this IBI
 * @data: payload buffer
 *
 * An IBI slot is an object pre-allocated by the controller and used when an
 * IBI comes in.
 * Every समय an IBI comes in, the I3C master driver should find a मुक्त IBI
 * slot in its IBI slot pool, retrieve the IBI payload and queue the IBI using
 * i3c_master_queue_ibi().
 *
 * How IBI slots are allocated is left to the I3C master driver, though, क्रम
 * simple kदो_स्मृति-based allocation, the generic IBI slot pool can be used.
 */
काष्ठा i3c_ibi_slot अणु
	काष्ठा work_काष्ठा work;
	काष्ठा i3c_dev_desc *dev;
	अचिन्हित पूर्णांक len;
	व्योम *data;
पूर्ण;

/**
 * काष्ठा i3c_device_ibi_info - IBI inक्रमmation attached to a specअगरic device
 * @all_ibis_handled: used to be inक्रमmed when no more IBIs are रुकोing to be
 *		      processed. Used by i3c_device_disable_ibi() to रुको क्रम
 *		      all IBIs to be dequeued
 * @pending_ibis: count the number of pending IBIs. Each pending IBI has its
 *		  work element queued to the controller workqueue
 * @max_payload_len: maximum payload length क्रम an IBI coming from this device.
 *		     this value is specअगरied when calling
 *		     i3c_device_request_ibi() and should not change at run
 *		     समय. All messages IBIs exceeding this limit should be
 *		     rejected by the master
 * @num_slots: number of IBI slots reserved क्रम this device
 * @enabled: reflect the IBI status
 * @handler: IBI handler specअगरied at i3c_device_request_ibi() call समय. This
 *	     handler will be called from the controller workqueue, and as such
 *	     is allowed to sleep (though it is recommended to process the IBI
 *	     as fast as possible to not stall processing of other IBIs queued
 *	     on the same workqueue).
 *	     New I3C messages can be sent from the IBI handler
 *
 * The &काष्ठा_i3c_device_ibi_info object is allocated when
 * i3c_device_request_ibi() is called and attached to a specअगरic device. This
 * object is here to manage IBIs coming from a specअगरic I3C device.
 *
 * Note that this काष्ठाure is the generic view of the IBI management
 * infraकाष्ठाure. I3C master drivers may have their own पूर्णांकernal
 * representation which they can associate to the device using
 * controller-निजी data.
 */
काष्ठा i3c_device_ibi_info अणु
	काष्ठा completion all_ibis_handled;
	atomic_t pending_ibis;
	अचिन्हित पूर्णांक max_payload_len;
	अचिन्हित पूर्णांक num_slots;
	अचिन्हित पूर्णांक enabled;
	व्योम (*handler)(काष्ठा i3c_device *dev,
			स्थिर काष्ठा i3c_ibi_payload *payload);
पूर्ण;

/**
 * काष्ठा i3c_dev_boardinfo - I3C device board inक्रमmation
 * @node: used to insert the boardinfo object in the I3C boardinfo list
 * @init_dyn_addr: initial dynamic address requested by the FW. We provide no
 *		   guarantee that the device will end up using this address,
 *		   but try our best to assign this specअगरic address to the
 *		   device
 * @अटल_addr: अटल address the I3C device listen on beक्रमe it's been
 *		 asचिन्हित a dynamic address by the master. Will be used during
 *		 bus initialization to assign it a specअगरic dynamic address
 *		 beक्रमe starting DAA (Dynamic Address Assignment)
 * @pid: I3C Provisional ID exposed by the device. This is a unique identअगरier
 *	 that may be used to attach boardinfo to i3c_dev_desc when the device
 *	 करोes not have a अटल address
 * @of_node: optional DT node in हाल the device has been described in the DT
 *
 * This काष्ठाure is used to attach board-level inक्रमmation to an I3C device.
 * Not all I3C devices connected on the bus will have a boardinfo. It's only
 * needed अगर you want to attach extra resources to a device or assign it a
 * specअगरic dynamic address.
 */
काष्ठा i3c_dev_boardinfo अणु
	काष्ठा list_head node;
	u8 init_dyn_addr;
	u8 अटल_addr;
	u64 pid;
	काष्ठा device_node *of_node;
पूर्ण;

/**
 * काष्ठा i3c_dev_desc - I3C device descriptor
 * @common: common part of the I3C device descriptor
 * @info: I3C device inक्रमmation. Will be स्वतःmatically filled when you create
 *	  your device with i3c_master_add_i3c_dev_locked()
 * @ibi_lock: lock used to protect the &काष्ठा_i3c_device->ibi
 * @ibi: IBI info attached to a device. Should be शून्य until
 *	 i3c_device_request_ibi() is called
 * @dev: poपूर्णांकer to the I3C device object exposed to I3C device drivers. This
 *	 should never be accessed from I3C master controller drivers. Only core
 *	 code should manipulate it in when updating the dev <-> desc link or
 *	 when propagating IBI events to the driver
 * @boardinfo: poपूर्णांकer to the boardinfo attached to this I3C device
 *
 * Internal representation of an I3C device. This object is only used by the
 * core and passed to I3C master controller drivers when they're requested to
 * करो some operations on the device.
 * The core मुख्यtains the link between the पूर्णांकernal I3C dev descriptor and the
 * object exposed to the I3C device drivers (&काष्ठा_i3c_device).
 */
काष्ठा i3c_dev_desc अणु
	काष्ठा i3c_i2c_dev_desc common;
	काष्ठा i3c_device_info info;
	काष्ठा mutex ibi_lock;
	काष्ठा i3c_device_ibi_info *ibi;
	काष्ठा i3c_device *dev;
	स्थिर काष्ठा i3c_dev_boardinfo *boardinfo;
पूर्ण;

/**
 * काष्ठा i3c_device - I3C device object
 * @dev: device object to रेजिस्टर the I3C dev to the device model
 * @desc: poपूर्णांकer to an i3c device descriptor object. This link is updated
 *	  every समय the I3C device is rediscovered with a dअगरferent dynamic
 *	  address asचिन्हित
 * @bus: I3C bus this device is attached to
 *
 * I3C device object exposed to I3C device drivers. The takes care of linking
 * this object to the relevant &काष्ठा_i3c_dev_desc one.
 * All I3C devs on the I3C bus are represented, including I3C masters. For each
 * of them, we have an instance of &काष्ठा i3c_device.
 */
काष्ठा i3c_device अणु
	काष्ठा device dev;
	काष्ठा i3c_dev_desc *desc;
	काष्ठा i3c_bus *bus;
पूर्ण;

/*
 * The I3C specअगरication says the maximum number of devices connected on the
 * bus is 11, but this number depends on बाह्यal parameters like trace length,
 * capacitive load per Device, and the types of Devices present on the Bus.
 * I3C master can also have limitations, so this number is just here as a
 * reference and should be adjusted on a per-controller/per-board basis.
 */
#घोषणा I3C_BUS_MAX_DEVS		11

#घोषणा I3C_BUS_MAX_I3C_SCL_RATE	12900000
#घोषणा I3C_BUS_TYP_I3C_SCL_RATE	12500000
#घोषणा I3C_BUS_I2C_FM_PLUS_SCL_RATE	1000000
#घोषणा I3C_BUS_I2C_FM_SCL_RATE		400000
#घोषणा I3C_BUS_TLOW_OD_MIN_NS		200

/**
 * क्रमागत i3c_bus_mode - I3C bus mode
 * @I3C_BUS_MODE_PURE: only I3C devices are connected to the bus. No limitation
 *		       expected
 * @I3C_BUS_MODE_MIXED_FAST: I2C devices with 50ns spike filter are present on
 *			     the bus. The only impact in this mode is that the
 *			     high SCL pulse has to stay below 50ns to trick I2C
 *			     devices when transmitting I3C frames
 * @I3C_BUS_MODE_MIXED_LIMITED: I2C devices without 50ns spike filter are
 *				present on the bus. However they allow
 *				compliance up to the maximum SDR SCL घड़ी
 *				frequency.
 * @I3C_BUS_MODE_MIXED_SLOW: I2C devices without 50ns spike filter are present
 *			     on the bus
 */
क्रमागत i3c_bus_mode अणु
	I3C_BUS_MODE_PURE,
	I3C_BUS_MODE_MIXED_FAST,
	I3C_BUS_MODE_MIXED_LIMITED,
	I3C_BUS_MODE_MIXED_SLOW,
पूर्ण;

/**
 * क्रमागत i3c_addr_slot_status - I3C address slot status
 * @I3C_ADDR_SLOT_FREE: address is मुक्त
 * @I3C_ADDR_SLOT_RSVD: address is reserved
 * @I3C_ADDR_SLOT_I2C_DEV: address is asचिन्हित to an I2C device
 * @I3C_ADDR_SLOT_I3C_DEV: address is asचिन्हित to an I3C device
 * @I3C_ADDR_SLOT_STATUS_MASK: address slot mask
 *
 * On an I3C bus, addresses are asचिन्हित dynamically, and we need to know which
 * addresses are मुक्त to use and which ones are alपढ़ोy asचिन्हित.
 *
 * Addresses marked as reserved are those reserved by the I3C protocol
 * (broadcast address, ...).
 */
क्रमागत i3c_addr_slot_status अणु
	I3C_ADDR_SLOT_FREE,
	I3C_ADDR_SLOT_RSVD,
	I3C_ADDR_SLOT_I2C_DEV,
	I3C_ADDR_SLOT_I3C_DEV,
	I3C_ADDR_SLOT_STATUS_MASK = 3,
पूर्ण;

/**
 * काष्ठा i3c_bus - I3C bus object
 * @cur_master: I3C master currently driving the bus. Since I3C is multi-master
 *		this can change over the समय. Will be used to let a master
 *		know whether it needs to request bus ownership beक्रमe sending
 *		a frame or not
 * @id: bus ID. Asचिन्हित by the framework when रेजिस्टर the bus
 * @addrslots: a biपंचांगap with 2-bits per-slot to encode the address status and
 *	       ease the DAA (Dynamic Address Assignment) procedure (see
 *	       &क्रमागत i3c_addr_slot_status)
 * @mode: bus mode (see &क्रमागत i3c_bus_mode)
 * @scl_rate.i3c: maximum rate क्रम the घड़ी संकेत when करोing I3C SDR/priv
 *		  transfers
 * @scl_rate.i2c: maximum rate क्रम the घड़ी संकेत when करोing I2C transfers
 * @scl_rate: SCL संकेत rate क्रम I3C and I2C mode
 * @devs.i3c: contains a list of I3C device descriptors representing I3C
 *	      devices connected on the bus and successfully attached to the
 *	      I3C master
 * @devs.i2c: contains a list of I2C device descriptors representing I2C
 *	      devices connected on the bus and successfully attached to the
 *	      I3C master
 * @devs: 2 lists containing all I3C/I2C devices connected to the bus
 * @lock: पढ़ो/ग_लिखो lock on the bus. This is needed to protect against
 *	  operations that have an impact on the whole bus and the devices
 *	  connected to it. For example, when asking slaves to drop their
 *	  dynamic address (RSTDAA CCC), we need to make sure no one is trying
 *	  to send I3C frames to these devices.
 *	  Note that this lock करोes not protect against concurrency between
 *	  devices: several drivers can send dअगरferent I3C/I2C frames through
 *	  the same master in parallel. This is the responsibility of the
 *	  master to guarantee that frames are actually sent sequentially and
 *	  not पूर्णांकerlaced
 *
 * The I3C bus is represented with its own object and not implicitly described
 * by the I3C master to cope with the multi-master functionality, where one bus
 * can be shared amongst several masters, each of them requesting bus ownership
 * when they need to.
 */
काष्ठा i3c_bus अणु
	काष्ठा i3c_dev_desc *cur_master;
	पूर्णांक id;
	अचिन्हित दीर्घ addrslots[((I2C_MAX_ADDR + 1) * 2) / BITS_PER_LONG];
	क्रमागत i3c_bus_mode mode;
	काष्ठा अणु
		अचिन्हित दीर्घ i3c;
		अचिन्हित दीर्घ i2c;
	पूर्ण scl_rate;
	काष्ठा अणु
		काष्ठा list_head i3c;
		काष्ठा list_head i2c;
	पूर्ण devs;
	काष्ठा rw_semaphore lock;
पूर्ण;

/**
 * काष्ठा i3c_master_controller_ops - I3C master methods
 * @bus_init: hook responsible क्रम the I3C bus initialization. You should at
 *	      least call master_set_info() from there and set the bus mode.
 *	      You can also put controller specअगरic initialization in there.
 *	      This method is mandatory.
 * @bus_cleanup: cleanup everything करोne in
 *		 &i3c_master_controller_ops->bus_init().
 *		 This method is optional.
 * @attach_i3c_dev: called every समय an I3C device is attached to the bus. It
 *		    can be after a DAA or when a device is अटलally declared
 *		    by the FW, in which हाल it will only have a अटल address
 *		    and the dynamic address will be 0.
 *		    When this function is called, device inक्रमmation have not
 *		    been retrieved yet.
 *		    This is a good place to attach master controller specअगरic
 *		    data to I3C devices.
 *		    This method is optional.
 * @reattach_i3c_dev: called every समय an I3C device has its addressed
 *		      changed. It can be because the device has been घातered
 *		      करोwn and has lost its address, or it can happen when a
 *		      device had a अटल address and has been asचिन्हित a
 *		      dynamic address with SETDASA.
 *		      This method is optional.
 * @detach_i3c_dev: called when an I3C device is detached from the bus. Usually
 *		    happens when the master device is unरेजिस्टरed.
 *		    This method is optional.
 * @करो_daa: करो a DAA (Dynamic Address Assignment) procedure. This is procedure
 *	    should send an ENTDAA CCC command and then add all devices
 *	    discovered sure the DAA using i3c_master_add_i3c_dev_locked().
 *	    Add devices added with i3c_master_add_i3c_dev_locked() will then be
 *	    attached or re-attached to the controller.
 *	    This method is mandatory.
 * @supports_ccc_cmd: should वापस true अगर the CCC command is supported, false
 *		      otherwise.
 *		      This method is optional, अगर not provided the core assumes
 *		      all CCC commands are supported.
 * @send_ccc_cmd: send a CCC command
 *		  This method is mandatory.
 * @priv_xfers: करो one or several निजी I3C SDR transfers
 *		This method is mandatory.
 * @attach_i2c_dev: called every समय an I2C device is attached to the bus.
 *		    This is a good place to attach master controller specअगरic
 *		    data to I2C devices.
 *		    This method is optional.
 * @detach_i2c_dev: called when an I2C device is detached from the bus. Usually
 *		    happens when the master device is unरेजिस्टरed.
 *		    This method is optional.
 * @i2c_xfers: करो one or several I2C transfers. Note that, unlike i3c
 *	       transfers, the core करोes not guarantee that buffers attached to
 *	       the transfers are DMA-safe. If drivers want to have DMA-safe
 *	       buffers, they should use the i2c_get_dma_safe_msg_buf()
 *	       and i2c_put_dma_safe_msg_buf() helpers provided by the I2C
 *	       framework.
 *	       This method is mandatory.
 * @request_ibi: attach an IBI handler to an I3C device. This implies defining
 *		 an IBI handler and the स्थिरraपूर्णांकs of the IBI (maximum payload
 *		 length and number of pre-allocated slots).
 *		 Some controllers support less IBI-capable devices than regular
 *		 devices, so this method might वापस -%EBUSY अगर there's no
 *		 more space क्रम an extra IBI registration
 *		 This method is optional.
 * @मुक्त_ibi: मुक्त an IBI previously requested with ->request_ibi(). The IBI
 *	      should have been disabled with ->disable_irq() prior to that
 *	      This method is mandatory only अगर ->request_ibi is not शून्य.
 * @enable_ibi: enable the IBI. Only valid अगर ->request_ibi() has been called
 *		prior to ->enable_ibi(). The controller should first enable
 *		the IBI on the controller end (क्रम example, unmask the hardware
 *		IRQ) and then send the ENEC CCC command (with the IBI flag set)
 *		to the I3C device.
 *		This method is mandatory only अगर ->request_ibi is not शून्य.
 * @disable_ibi: disable an IBI. First send the DISEC CCC command with the IBI
 *		 flag set and then deactivate the hardware IRQ on the
 *		 controller end.
 *		 This method is mandatory only अगर ->request_ibi is not शून्य.
 * @recycle_ibi_slot: recycle an IBI slot. Called every समय an IBI has been
 *		      processed by its handler. The IBI slot should be put back
 *		      in the IBI slot pool so that the controller can re-use it
 *		      क्रम a future IBI
 *		      This method is mandatory only अगर ->request_ibi is not
 *		      शून्य.
 */
काष्ठा i3c_master_controller_ops अणु
	पूर्णांक (*bus_init)(काष्ठा i3c_master_controller *master);
	व्योम (*bus_cleanup)(काष्ठा i3c_master_controller *master);
	पूर्णांक (*attach_i3c_dev)(काष्ठा i3c_dev_desc *dev);
	पूर्णांक (*reattach_i3c_dev)(काष्ठा i3c_dev_desc *dev, u8 old_dyn_addr);
	व्योम (*detach_i3c_dev)(काष्ठा i3c_dev_desc *dev);
	पूर्णांक (*करो_daa)(काष्ठा i3c_master_controller *master);
	bool (*supports_ccc_cmd)(काष्ठा i3c_master_controller *master,
				 स्थिर काष्ठा i3c_ccc_cmd *cmd);
	पूर्णांक (*send_ccc_cmd)(काष्ठा i3c_master_controller *master,
			    काष्ठा i3c_ccc_cmd *cmd);
	पूर्णांक (*priv_xfers)(काष्ठा i3c_dev_desc *dev,
			  काष्ठा i3c_priv_xfer *xfers,
			  पूर्णांक nxfers);
	पूर्णांक (*attach_i2c_dev)(काष्ठा i2c_dev_desc *dev);
	व्योम (*detach_i2c_dev)(काष्ठा i2c_dev_desc *dev);
	पूर्णांक (*i2c_xfers)(काष्ठा i2c_dev_desc *dev,
			 स्थिर काष्ठा i2c_msg *xfers, पूर्णांक nxfers);
	पूर्णांक (*request_ibi)(काष्ठा i3c_dev_desc *dev,
			   स्थिर काष्ठा i3c_ibi_setup *req);
	व्योम (*मुक्त_ibi)(काष्ठा i3c_dev_desc *dev);
	पूर्णांक (*enable_ibi)(काष्ठा i3c_dev_desc *dev);
	पूर्णांक (*disable_ibi)(काष्ठा i3c_dev_desc *dev);
	व्योम (*recycle_ibi_slot)(काष्ठा i3c_dev_desc *dev,
				 काष्ठा i3c_ibi_slot *slot);
पूर्ण;

/**
 * काष्ठा i3c_master_controller - I3C master controller object
 * @dev: device to be रेजिस्टरed to the device-model
 * @this: an I3C device object representing this master. This device will be
 *	  added to the list of I3C devs available on the bus
 * @i2c: I2C adapter used क्रम backward compatibility. This adapter is
 *	 रेजिस्टरed to the I2C subप्रणाली to be as transparent as possible to
 *	 existing I2C drivers
 * @ops: master operations. See &काष्ठा i3c_master_controller_ops
 * @secondary: true अगर the master is a secondary master
 * @init_करोne: true when the bus initialization is करोne
 * @boardinfo.i3c: list of I3C  boardinfo objects
 * @boardinfo.i2c: list of I2C boardinfo objects
 * @boardinfo: board-level inक्रमmation attached to devices connected on the bus
 * @bus: I3C bus exposed by this master
 * @wq: workqueue used to execute IBI handlers. Can also be used by master
 *	drivers अगर they need to postpone operations that need to take place
 *	in a thपढ़ो context. Typical examples are Hot Join processing which
 *	requires taking the bus lock in मुख्यtenance, which in turn, can only
 *	be करोne from a sleep-able context
 *
 * A &काष्ठा i3c_master_controller has to be रेजिस्टरed to the I3C subप्रणाली
 * through i3c_master_रेजिस्टर(). None of &काष्ठा i3c_master_controller fields
 * should be set manually, just pass appropriate values to
 * i3c_master_रेजिस्टर().
 */
काष्ठा i3c_master_controller अणु
	काष्ठा device dev;
	काष्ठा i3c_dev_desc *this;
	काष्ठा i2c_adapter i2c;
	स्थिर काष्ठा i3c_master_controller_ops *ops;
	अचिन्हित पूर्णांक secondary : 1;
	अचिन्हित पूर्णांक init_करोne : 1;
	काष्ठा अणु
		काष्ठा list_head i3c;
		काष्ठा list_head i2c;
	पूर्ण boardinfo;
	काष्ठा i3c_bus bus;
	काष्ठा workqueue_काष्ठा *wq;
पूर्ण;

/**
 * i3c_bus_क्रम_each_i2cdev() - iterate over all I2C devices present on the bus
 * @bus: the I3C bus
 * @dev: an I2C device descriptor poपूर्णांकer updated to poपूर्णांक to the current slot
 *	 at each iteration of the loop
 *
 * Iterate over all I2C devs present on the bus.
 */
#घोषणा i3c_bus_क्रम_each_i2cdev(bus, dev)				\
	list_क्रम_each_entry(dev, &(bus)->devs.i2c, common.node)

/**
 * i3c_bus_क्रम_each_i3cdev() - iterate over all I3C devices present on the bus
 * @bus: the I3C bus
 * @dev: and I3C device descriptor poपूर्णांकer updated to poपूर्णांक to the current slot
 *	 at each iteration of the loop
 *
 * Iterate over all I3C devs present on the bus.
 */
#घोषणा i3c_bus_क्रम_each_i3cdev(bus, dev)				\
	list_क्रम_each_entry(dev, &(bus)->devs.i3c, common.node)

पूर्णांक i3c_master_करो_i2c_xfers(काष्ठा i3c_master_controller *master,
			    स्थिर काष्ठा i2c_msg *xfers,
			    पूर्णांक nxfers);

पूर्णांक i3c_master_disec_locked(काष्ठा i3c_master_controller *master, u8 addr,
			    u8 evts);
पूर्णांक i3c_master_enec_locked(काष्ठा i3c_master_controller *master, u8 addr,
			   u8 evts);
पूर्णांक i3c_master_entdaa_locked(काष्ठा i3c_master_controller *master);
पूर्णांक i3c_master_defslvs_locked(काष्ठा i3c_master_controller *master);

पूर्णांक i3c_master_get_मुक्त_addr(काष्ठा i3c_master_controller *master,
			     u8 start_addr);

पूर्णांक i3c_master_add_i3c_dev_locked(काष्ठा i3c_master_controller *master,
				  u8 addr);
पूर्णांक i3c_master_करो_daa(काष्ठा i3c_master_controller *master);

पूर्णांक i3c_master_set_info(काष्ठा i3c_master_controller *master,
			स्थिर काष्ठा i3c_device_info *info);

पूर्णांक i3c_master_रेजिस्टर(काष्ठा i3c_master_controller *master,
			काष्ठा device *parent,
			स्थिर काष्ठा i3c_master_controller_ops *ops,
			bool secondary);
पूर्णांक i3c_master_unरेजिस्टर(काष्ठा i3c_master_controller *master);

/**
 * i3c_dev_get_master_data() - get master निजी data attached to an I3C
 *			       device descriptor
 * @dev: the I3C device descriptor to get निजी data from
 *
 * Return: the निजी data previously attached with i3c_dev_set_master_data()
 *	   or शून्य अगर no data has been attached to the device.
 */
अटल अंतरभूत व्योम *i3c_dev_get_master_data(स्थिर काष्ठा i3c_dev_desc *dev)
अणु
	वापस dev->common.master_priv;
पूर्ण

/**
 * i3c_dev_set_master_data() - attach master निजी data to an I3C device
 *			       descriptor
 * @dev: the I3C device descriptor to attach निजी data to
 * @data: निजी data
 *
 * This functions allows a master controller to attach per-device निजी data
 * which can then be retrieved with i3c_dev_get_master_data().
 */
अटल अंतरभूत व्योम i3c_dev_set_master_data(काष्ठा i3c_dev_desc *dev,
					   व्योम *data)
अणु
	dev->common.master_priv = data;
पूर्ण

/**
 * i2c_dev_get_master_data() - get master निजी data attached to an I2C
 *			       device descriptor
 * @dev: the I2C device descriptor to get निजी data from
 *
 * Return: the निजी data previously attached with i2c_dev_set_master_data()
 *	   or शून्य अगर no data has been attached to the device.
 */
अटल अंतरभूत व्योम *i2c_dev_get_master_data(स्थिर काष्ठा i2c_dev_desc *dev)
अणु
	वापस dev->common.master_priv;
पूर्ण

/**
 * i2c_dev_set_master_data() - attach master निजी data to an I2C device
 *			       descriptor
 * @dev: the I2C device descriptor to attach निजी data to
 * @data: निजी data
 *
 * This functions allows a master controller to attach per-device निजी data
 * which can then be retrieved with i2c_device_get_master_data().
 */
अटल अंतरभूत व्योम i2c_dev_set_master_data(काष्ठा i2c_dev_desc *dev,
					   व्योम *data)
अणु
	dev->common.master_priv = data;
पूर्ण

/**
 * i3c_dev_get_master() - get master used to communicate with a device
 * @dev: I3C dev
 *
 * Return: the master controller driving @dev
 */
अटल अंतरभूत काष्ठा i3c_master_controller *
i3c_dev_get_master(काष्ठा i3c_dev_desc *dev)
अणु
	वापस dev->common.master;
पूर्ण

/**
 * i2c_dev_get_master() - get master used to communicate with a device
 * @dev: I2C dev
 *
 * Return: the master controller driving @dev
 */
अटल अंतरभूत काष्ठा i3c_master_controller *
i2c_dev_get_master(काष्ठा i2c_dev_desc *dev)
अणु
	वापस dev->common.master;
पूर्ण

/**
 * i3c_master_get_bus() - get the bus attached to a master
 * @master: master object
 *
 * Return: the I3C bus @master is connected to
 */
अटल अंतरभूत काष्ठा i3c_bus *
i3c_master_get_bus(काष्ठा i3c_master_controller *master)
अणु
	वापस &master->bus;
पूर्ण

काष्ठा i3c_generic_ibi_pool;

काष्ठा i3c_generic_ibi_pool *
i3c_generic_ibi_alloc_pool(काष्ठा i3c_dev_desc *dev,
			   स्थिर काष्ठा i3c_ibi_setup *req);
व्योम i3c_generic_ibi_मुक्त_pool(काष्ठा i3c_generic_ibi_pool *pool);

काष्ठा i3c_ibi_slot *
i3c_generic_ibi_get_मुक्त_slot(काष्ठा i3c_generic_ibi_pool *pool);
व्योम i3c_generic_ibi_recycle_slot(काष्ठा i3c_generic_ibi_pool *pool,
				  काष्ठा i3c_ibi_slot *slot);

व्योम i3c_master_queue_ibi(काष्ठा i3c_dev_desc *dev, काष्ठा i3c_ibi_slot *slot);

काष्ठा i3c_ibi_slot *i3c_master_get_मुक्त_ibi_slot(काष्ठा i3c_dev_desc *dev);

#पूर्ण_अगर /* I3C_MASTER_H */
