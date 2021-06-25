<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * NVEC: NVIDIA compliant embedded controller पूर्णांकerface
 *
 * Copyright (C) 2011 The AC100 Kernel Team <ac100@lists.launchpad.net>
 *
 * Authors:  Pierre-Hugues Husson <phhusson@मुक्त.fr>
 *           Ilya Petrov <ilya.muromec@gmail.com>
 *           Marc Dietrich <marvin24@gmx.de>
 *           Julian Andres Klode <jak@jak-linux.org>
 */

#अगर_अघोषित __LINUX_MFD_NVEC
#घोषणा __LINUX_MFD_NVEC

#समावेश <linux/atomic.h>
#समावेश <linux/clk.h>
#समावेश <linux/completion.h>
#समावेश <linux/list.h>
#समावेश <linux/mutex.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/reset.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/workqueue.h>

/* NVEC_POOL_SIZE - Size of the pool in &काष्ठा nvec_msg */
#घोषणा NVEC_POOL_SIZE	64

/*
 * NVEC_MSG_SIZE - Maximum size of the data field of &काष्ठा nvec_msg.
 *
 * A message must store up to a SMBus block operation which consists of
 * one command byte, one count byte, and up to 32 payload bytes = 34
 * byte.
 */
#घोषणा NVEC_MSG_SIZE	34

/**
 * क्रमागत nvec_event_size - The size of an event message
 * @NVEC_2BYTES: The message has one command byte and one data byte
 * @NVEC_3BYTES: The message has one command byte and two data bytes
 * @NVEC_VAR_SIZE: The message has one command byte, one count byte, and has
 *                 up to as many bytes as the number in the count byte. The
 *                 maximum is 32
 *
 * Events can be fixed or variable sized. This is useless on other message
 * types, which are always variable sized.
 */
क्रमागत nvec_event_size अणु
	NVEC_2BYTES,
	NVEC_3BYTES,
	NVEC_VAR_SIZE,
पूर्ण;

/**
 * क्रमागत nvec_msg_type - The type of a message
 * @NVEC_SYS: A प्रणाली request/response
 * @NVEC_BAT: A battery request/response
 * @NVEC_KBD: A keyboard request/response
 * @NVEC_PS2: A mouse request/response
 * @NVEC_CNTL: A EC control request/response
 * @NVEC_KB_EVT: An event from the keyboard
 * @NVEC_PS2_EVT: An event from the mouse
 *
 * Events can be fixed or variable sized. This is useless on other message
 * types, which are always variable sized.
 */
क्रमागत nvec_msg_type अणु
	NVEC_SYS = 1,
	NVEC_BAT,
	NVEC_GPIO,
	NVEC_SLEEP,
	NVEC_KBD,
	NVEC_PS2,
	NVEC_CNTL,
	NVEC_OEM0 = 0x0d,
	NVEC_KB_EVT = 0x80,
	NVEC_PS2_EVT,
पूर्ण;

/**
 * काष्ठा nvec_msg - A buffer क्रम a single message
 * @node: Messages are part of various lists in a &काष्ठा nvec_chip
 * @data: The data of the message
 * @size: For TX messages, the number of bytes used in @data
 * @pos:  For RX messages, the current position to ग_लिखो to. For TX messages,
 *        the position to पढ़ो from.
 * @used: Used क्रम the message pool to mark a message as मुक्त/allocated.
 *
 * This काष्ठाure is used to hold outgoing and incoming messages. Outgoing
 * messages have a dअगरferent क्रमmat than incoming messages, and that is not
 * करोcumented yet.
 */
काष्ठा nvec_msg अणु
	काष्ठा list_head node;
	अचिन्हित अक्षर data[NVEC_MSG_SIZE];
	अचिन्हित लघु size;
	अचिन्हित लघु pos;
	atomic_t used;
पूर्ण;

/**
 * काष्ठा nvec_chip - A single connection to an NVIDIA Embedded controller
 * @dev: The device
 * @gpio: The same as क्रम &काष्ठा nvec_platक्रमm_data
 * @irq: The IRQ of the I2C device
 * @i2c_addr: The address of the I2C slave
 * @base: The base of the memory mapped region of the I2C device
 * @i2c_clk: The घड़ी of the I2C device
 * @rst: The reset of the I2C device
 * @notअगरier_list: Notअगरiers to be called on received messages, see
 *                 nvec_रेजिस्टर_notअगरier()
 * @rx_data: Received messages that have to be processed
 * @tx_data: Messages रुकोing to be sent to the controller
 * @nvec_status_notअगरier: Internal notअगरier (see nvec_status_notअगरier())
 * @rx_work: A work काष्ठाure क्रम the RX worker nvec_dispatch()
 * @tx_work: A work काष्ठाure क्रम the TX worker nvec_request_master()
 * @wq: The work queue in which @rx_work and @tx_work are executed
 * @rx: The message currently being retrieved or %शून्य
 * @msg_pool: A pool of messages क्रम allocation
 * @tx: The message currently being transferred
 * @tx_scratch: Used क्रम building pseuकरो messages
 * @ec_transfer: A completion that will be completed once a message has been
 *               received (see nvec_rx_completed())
 * @tx_lock: Spinlock क्रम modअगरications on @tx_data
 * @rx_lock: Spinlock क्रम modअगरications on @rx_data
 * @sync_ग_लिखो_mutex: A mutex क्रम nvec_ग_लिखो_sync()
 * @sync_ग_लिखो: A completion to संकेत that a synchronous message is complete
 * @sync_ग_लिखो_pending: The first two bytes of the request (type and subtype)
 * @last_sync_msg: The last synchronous message.
 * @state: State of our finite state machine used in nvec_पूर्णांकerrupt()
 */
काष्ठा nvec_chip अणु
	काष्ठा device *dev;
	काष्ठा gpio_desc *gpiod;
	पूर्णांक irq;
	u32 i2c_addr;
	व्योम __iomem *base;
	काष्ठा clk *i2c_clk;
	काष्ठा reset_control *rst;
	काष्ठा atomic_notअगरier_head notअगरier_list;
	काष्ठा list_head rx_data, tx_data;
	काष्ठा notअगरier_block nvec_status_notअगरier;
	काष्ठा work_काष्ठा rx_work, tx_work;
	काष्ठा workqueue_काष्ठा *wq;
	काष्ठा nvec_msg msg_pool[NVEC_POOL_SIZE];
	काष्ठा nvec_msg *rx;

	काष्ठा nvec_msg *tx;
	काष्ठा nvec_msg tx_scratch;
	काष्ठा completion ec_transfer;

	spinlock_t tx_lock, rx_lock;

	/* sync ग_लिखो stuff */
	काष्ठा mutex sync_ग_लिखो_mutex;
	काष्ठा completion sync_ग_लिखो;
	u16 sync_ग_लिखो_pending;
	काष्ठा nvec_msg *last_sync_msg;

	पूर्णांक state;
पूर्ण;

पूर्णांक nvec_ग_लिखो_async(काष्ठा nvec_chip *nvec, स्थिर अचिन्हित अक्षर *data,
		     लघु size);

पूर्णांक nvec_ग_लिखो_sync(काष्ठा nvec_chip *nvec,
		    स्थिर अचिन्हित अक्षर *data, लघु size,
		    काष्ठा nvec_msg **msg);

पूर्णांक nvec_रेजिस्टर_notअगरier(काष्ठा nvec_chip *nvec,
			   काष्ठा notअगरier_block *nb,
			   अचिन्हित पूर्णांक events);

पूर्णांक nvec_unरेजिस्टर_notअगरier(काष्ठा nvec_chip *dev, काष्ठा notअगरier_block *nb);

व्योम nvec_msg_मुक्त(काष्ठा nvec_chip *nvec, काष्ठा nvec_msg *msg);

#पूर्ण_अगर
