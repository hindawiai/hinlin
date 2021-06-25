<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ WITH Linux-syscall-note */
/*
 * i2c-dev.h - I2C bus अक्षर device पूर्णांकerface
 *
 * Copyright (C) 1995-97 Simon G. Vogl
 * Copyright (C) 1998-99 Froकरो Looijaard <froकरोl@dds.nl>
 */

#अगर_अघोषित _UAPI_LINUX_I2C_DEV_H
#घोषणा _UAPI_LINUX_I2C_DEV_H

#समावेश <linux/types.h>
#समावेश <linux/compiler.h>

/* /dev/i2c-X ioctl commands.  The ioctl's parameter is always an
 * अचिन्हित दीर्घ, except क्रम:
 *	- I2C_FUNCS, takes poपूर्णांकer to an अचिन्हित दीर्घ
 *	- I2C_RDWR, takes poपूर्णांकer to काष्ठा i2c_rdwr_ioctl_data
 *	- I2C_SMBUS, takes poपूर्णांकer to काष्ठा i2c_smbus_ioctl_data
 */
#घोषणा I2C_RETRIES	0x0701	/* number of बार a device address should
				   be polled when not acknowledging */
#घोषणा I2C_TIMEOUT	0x0702	/* set समयout in units of 10 ms */

/* NOTE: Slave address is 7 or 10 bits, but 10-bit addresses
 * are NOT supported! (due to code brokenness)
 */
#घोषणा I2C_SLAVE	0x0703	/* Use this slave address */
#घोषणा I2C_SLAVE_FORCE	0x0706	/* Use this slave address, even अगर it
				   is alपढ़ोy in use by a driver! */
#घोषणा I2C_TENBIT	0x0704	/* 0 क्रम 7 bit addrs, != 0 क्रम 10 bit */

#घोषणा I2C_FUNCS	0x0705	/* Get the adapter functionality mask */

#घोषणा I2C_RDWR	0x0707	/* Combined R/W transfer (one STOP only) */

#घोषणा I2C_PEC		0x0708	/* != 0 to use PEC with SMBus */
#घोषणा I2C_SMBUS	0x0720	/* SMBus transfer */


/* This is the काष्ठाure as used in the I2C_SMBUS ioctl call */
काष्ठा i2c_smbus_ioctl_data अणु
	__u8 पढ़ो_ग_लिखो;
	__u8 command;
	__u32 size;
	जोड़ i2c_smbus_data __user *data;
पूर्ण;

/* This is the काष्ठाure as used in the I2C_RDWR ioctl call */
काष्ठा i2c_rdwr_ioctl_data अणु
	काष्ठा i2c_msg __user *msgs;	/* poपूर्णांकers to i2c_msgs */
	__u32 nmsgs;			/* number of i2c_msgs */
पूर्ण;

#घोषणा  I2C_RDWR_IOCTL_MAX_MSGS	42
/* Originally defined with a typo, keep it क्रम compatibility */
#घोषणा  I2C_RDRW_IOCTL_MAX_MSGS	I2C_RDWR_IOCTL_MAX_MSGS


#पूर्ण_अगर /* _UAPI_LINUX_I2C_DEV_H */
