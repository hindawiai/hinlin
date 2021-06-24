<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ WITH Linux-syscall-note */
/*
 * i2c.h - definitions क्रम the I2C bus पूर्णांकerface
 *
 * Copyright (C) 1995-2000 Simon G. Vogl
 * With some changes from Kyथघsti Mथअlkki <kmalkki@cc.hut.fi> and
 * Froकरो Looijaard <froकरोl@dds.nl>
 */

#अगर_अघोषित _UAPI_LINUX_I2C_H
#घोषणा _UAPI_LINUX_I2C_H

#समावेश <linux/types.h>

/**
 * काष्ठा i2c_msg - an I2C transaction segment beginning with START
 *
 * @addr: Slave address, either 7 or 10 bits. When this is a 10 bit address,
 *   %I2C_M_TEN must be set in @flags and the adapter must support
 *   %I2C_FUNC_10BIT_ADDR.
 *
 * @flags:
 *   Supported by all adapters:
 *   %I2C_M_RD: पढ़ो data (from slave to master). Guaranteed to be 0x0001!
 *
 *   Optional:
 *   %I2C_M_DMA_SAFE: the buffer of this message is DMA safe. Makes only sense
 *     in kernelspace, because userspace buffers are copied anyway
 *
 *   Only अगर I2C_FUNC_10BIT_ADDR is set:
 *   %I2C_M_TEN: this is a 10 bit chip address
 *
 *   Only अगर I2C_FUNC_SMBUS_READ_BLOCK_DATA is set:
 *   %I2C_M_RECV_LEN: message length will be first received byte
 *
 *   Only अगर I2C_FUNC_NOSTART is set:
 *   %I2C_M_NOSTART: skip repeated start sequence

 *   Only अगर I2C_FUNC_PROTOCOL_MANGLING is set:
 *   %I2C_M_NO_RD_ACK: in a पढ़ो message, master ACK/NACK bit is skipped
 *   %I2C_M_IGNORE_NAK: treat NACK from client as ACK
 *   %I2C_M_REV_सूची_ADDR: toggles the Rd/Wr bit
 *   %I2C_M_STOP: क्रमce a STOP condition after the message
 *
 * @len: Number of data bytes in @buf being पढ़ो from or written to the I2C
 *   slave address. For पढ़ो transactions where %I2C_M_RECV_LEN is set, the
 *   caller guarantees that this buffer can hold up to %I2C_SMBUS_BLOCK_MAX
 *   bytes in addition to the initial length byte sent by the slave (plus,
 *   अगर used, the SMBus PEC); and this value will be incremented by the number
 *   of block data bytes received.
 *
 * @buf: The buffer पूर्णांकo which data is पढ़ो, or from which it's written.
 *
 * An i2c_msg is the low level representation of one segment of an I2C
 * transaction.  It is visible to drivers in the @i2c_transfer() procedure,
 * to userspace from i2c-dev, and to I2C adapter drivers through the
 * @i2c_adapter.@master_xfer() method.
 *
 * Except when I2C "protocol mangling" is used, all I2C adapters implement
 * the standard rules क्रम I2C transactions.  Each transaction begins with a
 * START.  That is followed by the slave address, and a bit encoding पढ़ो
 * versus ग_लिखो.  Then follow all the data bytes, possibly including a byte
 * with SMBus PEC.  The transfer terminates with a NAK, or when all those
 * bytes have been transferred and ACKed.  If this is the last message in a
 * group, it is followed by a STOP.  Otherwise it is followed by the next
 * @i2c_msg transaction segment, beginning with a (repeated) START.
 *
 * Alternatively, when the adapter supports %I2C_FUNC_PROTOCOL_MANGLING then
 * passing certain @flags may have changed those standard protocol behaviors.
 * Those flags are only क्रम use with broken/nonconक्रमming slaves, and with
 * adapters which are known to support the specअगरic mangling options they need.
 */
काष्ठा i2c_msg अणु
	__u16 addr;
	__u16 flags;
#घोषणा I2C_M_RD		0x0001	/* guaranteed to be 0x0001! */
#घोषणा I2C_M_TEN		0x0010	/* use only अगर I2C_FUNC_10BIT_ADDR */
#घोषणा I2C_M_DMA_SAFE		0x0200	/* use only in kernel space */
#घोषणा I2C_M_RECV_LEN		0x0400	/* use only अगर I2C_FUNC_SMBUS_READ_BLOCK_DATA */
#घोषणा I2C_M_NO_RD_ACK		0x0800	/* use only अगर I2C_FUNC_PROTOCOL_MANGLING */
#घोषणा I2C_M_IGNORE_NAK	0x1000	/* use only अगर I2C_FUNC_PROTOCOL_MANGLING */
#घोषणा I2C_M_REV_सूची_ADDR	0x2000	/* use only अगर I2C_FUNC_PROTOCOL_MANGLING */
#घोषणा I2C_M_NOSTART		0x4000	/* use only अगर I2C_FUNC_NOSTART */
#घोषणा I2C_M_STOP		0x8000	/* use only अगर I2C_FUNC_PROTOCOL_MANGLING */
	__u16 len;
	__u8 *buf;
पूर्ण;

/* To determine what functionality is present */

#घोषणा I2C_FUNC_I2C			0x00000001
#घोषणा I2C_FUNC_10BIT_ADDR		0x00000002 /* required क्रम I2C_M_TEN */
#घोषणा I2C_FUNC_PROTOCOL_MANGLING	0x00000004 /* required क्रम I2C_M_IGNORE_NAK etc. */
#घोषणा I2C_FUNC_SMBUS_PEC		0x00000008
#घोषणा I2C_FUNC_NOSTART		0x00000010 /* required क्रम I2C_M_NOSTART */
#घोषणा I2C_FUNC_SLAVE			0x00000020
#घोषणा I2C_FUNC_SMBUS_BLOCK_PROC_CALL	0x00008000 /* SMBus 2.0 or later */
#घोषणा I2C_FUNC_SMBUS_QUICK		0x00010000
#घोषणा I2C_FUNC_SMBUS_READ_BYTE	0x00020000
#घोषणा I2C_FUNC_SMBUS_WRITE_BYTE	0x00040000
#घोषणा I2C_FUNC_SMBUS_READ_BYTE_DATA	0x00080000
#घोषणा I2C_FUNC_SMBUS_WRITE_BYTE_DATA	0x00100000
#घोषणा I2C_FUNC_SMBUS_READ_WORD_DATA	0x00200000
#घोषणा I2C_FUNC_SMBUS_WRITE_WORD_DATA	0x00400000
#घोषणा I2C_FUNC_SMBUS_PROC_CALL	0x00800000
#घोषणा I2C_FUNC_SMBUS_READ_BLOCK_DATA	0x01000000 /* required क्रम I2C_M_RECV_LEN */
#घोषणा I2C_FUNC_SMBUS_WRITE_BLOCK_DATA 0x02000000
#घोषणा I2C_FUNC_SMBUS_READ_I2C_BLOCK	0x04000000 /* I2C-like block xfer  */
#घोषणा I2C_FUNC_SMBUS_WRITE_I2C_BLOCK	0x08000000 /* w/ 1-byte reg. addr. */
#घोषणा I2C_FUNC_SMBUS_HOST_NOTIFY	0x10000000 /* SMBus 2.0 or later */

#घोषणा I2C_FUNC_SMBUS_BYTE		(I2C_FUNC_SMBUS_READ_BYTE | \
					 I2C_FUNC_SMBUS_WRITE_BYTE)
#घोषणा I2C_FUNC_SMBUS_BYTE_DATA	(I2C_FUNC_SMBUS_READ_BYTE_DATA | \
					 I2C_FUNC_SMBUS_WRITE_BYTE_DATA)
#घोषणा I2C_FUNC_SMBUS_WORD_DATA	(I2C_FUNC_SMBUS_READ_WORD_DATA | \
					 I2C_FUNC_SMBUS_WRITE_WORD_DATA)
#घोषणा I2C_FUNC_SMBUS_BLOCK_DATA	(I2C_FUNC_SMBUS_READ_BLOCK_DATA | \
					 I2C_FUNC_SMBUS_WRITE_BLOCK_DATA)
#घोषणा I2C_FUNC_SMBUS_I2C_BLOCK	(I2C_FUNC_SMBUS_READ_I2C_BLOCK | \
					 I2C_FUNC_SMBUS_WRITE_I2C_BLOCK)

#घोषणा I2C_FUNC_SMBUS_EMUL		(I2C_FUNC_SMBUS_QUICK | \
					 I2C_FUNC_SMBUS_BYTE | \
					 I2C_FUNC_SMBUS_BYTE_DATA | \
					 I2C_FUNC_SMBUS_WORD_DATA | \
					 I2C_FUNC_SMBUS_PROC_CALL | \
					 I2C_FUNC_SMBUS_WRITE_BLOCK_DATA | \
					 I2C_FUNC_SMBUS_I2C_BLOCK | \
					 I2C_FUNC_SMBUS_PEC)

/* अगर I2C_M_RECV_LEN is also supported */
#घोषणा I2C_FUNC_SMBUS_EMUL_ALL		(I2C_FUNC_SMBUS_EMUL | \
					 I2C_FUNC_SMBUS_READ_BLOCK_DATA | \
					 I2C_FUNC_SMBUS_BLOCK_PROC_CALL)

/*
 * Data क्रम SMBus Messages
 */
#घोषणा I2C_SMBUS_BLOCK_MAX	32	/* As specअगरied in SMBus standard */
जोड़ i2c_smbus_data अणु
	__u8 byte;
	__u16 word;
	__u8 block[I2C_SMBUS_BLOCK_MAX + 2]; /* block[0] is used क्रम length */
			       /* and one more क्रम user-space compatibility */
पूर्ण;

/* i2c_smbus_xfer पढ़ो or ग_लिखो markers */
#घोषणा I2C_SMBUS_READ	1
#घोषणा I2C_SMBUS_WRITE	0

/* SMBus transaction types (size parameter in the above functions)
   Note: these no दीर्घer correspond to the (arbitrary) PIIX4 पूर्णांकernal codes! */
#घोषणा I2C_SMBUS_QUICK		    0
#घोषणा I2C_SMBUS_BYTE		    1
#घोषणा I2C_SMBUS_BYTE_DATA	    2
#घोषणा I2C_SMBUS_WORD_DATA	    3
#घोषणा I2C_SMBUS_PROC_CALL	    4
#घोषणा I2C_SMBUS_BLOCK_DATA	    5
#घोषणा I2C_SMBUS_I2C_BLOCK_BROKEN  6
#घोषणा I2C_SMBUS_BLOCK_PROC_CALL   7		/* SMBus 2.0 */
#घोषणा I2C_SMBUS_I2C_BLOCK_DATA    8

#पूर्ण_अगर /* _UAPI_LINUX_I2C_H */
