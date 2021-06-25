<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * RapidIO configuration space access support
 *
 * Copyright 2005 MontaVista Software, Inc.
 * Matt Porter <mporter@kernel.crashing.org>
 */

#समावेश <linux/rपन.स>
#समावेश <linux/module.h>

#समावेश <linux/rio_drv.h>

/*
 *  Wrappers क्रम all RIO configuration access functions.  They just check
 *  alignment and call the low-level functions poपूर्णांकed to by rio_mport->ops.
 */

#घोषणा RIO_8_BAD 0
#घोषणा RIO_16_BAD (offset & 1)
#घोषणा RIO_32_BAD (offset & 3)

/**
 * RIO_LOP_READ - Generate rio_local_पढ़ो_config_* functions
 * @size: Size of configuration space पढ़ो (8, 16, 32 bits)
 * @type: C type of value argument
 * @len: Length of configuration space पढ़ो (1, 2, 4 bytes)
 *
 * Generates rio_local_पढ़ो_config_* functions used to access
 * configuration space रेजिस्टरs on the local device.
 */
#घोषणा RIO_LOP_READ(size,type,len) \
पूर्णांक __rio_local_पढ़ो_config_##size \
	(काष्ठा rio_mport *mport, u32 offset, type *value)		\
अणु									\
	पूर्णांक res;							\
	u32 data = 0;							\
	अगर (RIO_##size##_BAD) वापस RIO_BAD_SIZE;			\
	res = mport->ops->lcपढ़ो(mport, mport->id, offset, len, &data);	\
	*value = (type)data;						\
	वापस res;							\
पूर्ण

/**
 * RIO_LOP_WRITE - Generate rio_local_ग_लिखो_config_* functions
 * @size: Size of configuration space ग_लिखो (8, 16, 32 bits)
 * @type: C type of value argument
 * @len: Length of configuration space ग_लिखो (1, 2, 4 bytes)
 *
 * Generates rio_local_ग_लिखो_config_* functions used to access
 * configuration space रेजिस्टरs on the local device.
 */
#घोषणा RIO_LOP_WRITE(size,type,len) \
पूर्णांक __rio_local_ग_लिखो_config_##size \
	(काष्ठा rio_mport *mport, u32 offset, type value)		\
अणु									\
	अगर (RIO_##size##_BAD) वापस RIO_BAD_SIZE;			\
	वापस mport->ops->lcग_लिखो(mport, mport->id, offset, len, value);\
पूर्ण

RIO_LOP_READ(8, u8, 1)
RIO_LOP_READ(16, u16, 2)
RIO_LOP_READ(32, u32, 4)
RIO_LOP_WRITE(8, u8, 1)
RIO_LOP_WRITE(16, u16, 2)
RIO_LOP_WRITE(32, u32, 4)

EXPORT_SYMBOL_GPL(__rio_local_पढ़ो_config_8);
EXPORT_SYMBOL_GPL(__rio_local_पढ़ो_config_16);
EXPORT_SYMBOL_GPL(__rio_local_पढ़ो_config_32);
EXPORT_SYMBOL_GPL(__rio_local_ग_लिखो_config_8);
EXPORT_SYMBOL_GPL(__rio_local_ग_लिखो_config_16);
EXPORT_SYMBOL_GPL(__rio_local_ग_लिखो_config_32);

/**
 * RIO_OP_READ - Generate rio_mport_पढ़ो_config_* functions
 * @size: Size of configuration space पढ़ो (8, 16, 32 bits)
 * @type: C type of value argument
 * @len: Length of configuration space पढ़ो (1, 2, 4 bytes)
 *
 * Generates rio_mport_पढ़ो_config_* functions used to access
 * configuration space रेजिस्टरs on the local device.
 */
#घोषणा RIO_OP_READ(size,type,len) \
पूर्णांक rio_mport_पढ़ो_config_##size \
	(काष्ठा rio_mport *mport, u16 destid, u8 hopcount, u32 offset, type *value)	\
अणु									\
	पूर्णांक res;							\
	u32 data = 0;							\
	अगर (RIO_##size##_BAD) वापस RIO_BAD_SIZE;			\
	res = mport->ops->cपढ़ो(mport, mport->id, destid, hopcount, offset, len, &data); \
	*value = (type)data;						\
	वापस res;							\
पूर्ण

/**
 * RIO_OP_WRITE - Generate rio_mport_ग_लिखो_config_* functions
 * @size: Size of configuration space ग_लिखो (8, 16, 32 bits)
 * @type: C type of value argument
 * @len: Length of configuration space ग_लिखो (1, 2, 4 bytes)
 *
 * Generates rio_mport_ग_लिखो_config_* functions used to access
 * configuration space रेजिस्टरs on the local device.
 */
#घोषणा RIO_OP_WRITE(size,type,len) \
पूर्णांक rio_mport_ग_लिखो_config_##size \
	(काष्ठा rio_mport *mport, u16 destid, u8 hopcount, u32 offset, type value)	\
अणु									\
	अगर (RIO_##size##_BAD) वापस RIO_BAD_SIZE;			\
	वापस mport->ops->cग_लिखो(mport, mport->id, destid, hopcount,	\
			offset, len, value);				\
पूर्ण

RIO_OP_READ(8, u8, 1)
RIO_OP_READ(16, u16, 2)
RIO_OP_READ(32, u32, 4)
RIO_OP_WRITE(8, u8, 1)
RIO_OP_WRITE(16, u16, 2)
RIO_OP_WRITE(32, u32, 4)

EXPORT_SYMBOL_GPL(rio_mport_पढ़ो_config_8);
EXPORT_SYMBOL_GPL(rio_mport_पढ़ो_config_16);
EXPORT_SYMBOL_GPL(rio_mport_पढ़ो_config_32);
EXPORT_SYMBOL_GPL(rio_mport_ग_लिखो_config_8);
EXPORT_SYMBOL_GPL(rio_mport_ग_लिखो_config_16);
EXPORT_SYMBOL_GPL(rio_mport_ग_लिखो_config_32);

/**
 * rio_mport_send_करोorbell - Send a करोorbell message
 *
 * @mport: RIO master port
 * @destid: RIO device destination ID
 * @data: Doorbell message data
 *
 * Send a करोorbell message to a RIO device. The करोorbell message
 * has a 16-bit info field provided by the data argument.
 */
पूर्णांक rio_mport_send_करोorbell(काष्ठा rio_mport *mport, u16 destid, u16 data)
अणु
	वापस mport->ops->dsend(mport, mport->id, destid, data);
पूर्ण

EXPORT_SYMBOL_GPL(rio_mport_send_करोorbell);
