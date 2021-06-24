<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ WITH Linux-syscall-note */
/*
 * include/linux/spi/spidev.h
 *
 * Copyright (C) 2006 SWAPP
 *	Andrea Paterniani <a.paterniani@swapp-eng.it>
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License क्रम more details.
 *
 * You should have received a copy of the GNU General Public License
 * aदीर्घ with this program; अगर not, ग_लिखो to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
  */

#अगर_अघोषित SPIDEV_H
#घोषणा SPIDEV_H

#समावेश <linux/types.h>
#समावेश <linux/ioctl.h>
#समावेश <linux/spi/spi.h>

/* IOCTL commands */

#घोषणा SPI_IOC_MAGIC			'k'

/**
 * काष्ठा spi_ioc_transfer - describes a single SPI transfer
 * @tx_buf: Holds poपूर्णांकer to userspace buffer with transmit data, or null.
 *	If no data is provided, zeroes are shअगरted out.
 * @rx_buf: Holds poपूर्णांकer to userspace buffer क्रम receive data, or null.
 * @len: Length of tx and rx buffers, in bytes.
 * @speed_hz: Temporary override of the device's bitrate.
 * @bits_per_word: Temporary override of the device's wordsize.
 * @delay_usecs: If nonzero, how दीर्घ to delay after the last bit transfer
 *	beक्रमe optionally deselecting the device beक्रमe the next transfer.
 * @cs_change: True to deselect device beक्रमe starting the next transfer.
 * @word_delay_usecs: If nonzero, how दीर्घ to रुको between words within one
 *	transfer. This property needs explicit support in the SPI controller,
 *	otherwise it is silently ignored.
 *
 * This काष्ठाure is mapped directly to the kernel spi_transfer काष्ठाure;
 * the fields have the same meanings, except of course that the poपूर्णांकers
 * are in a dअगरferent address space (and may be of dअगरferent sizes in some
 * हालs, such as 32-bit i386 userspace over a 64-bit x86_64 kernel).
 * Zero-initialize the काष्ठाure, including currently unused fields, to
 * accommodate potential future updates.
 *
 * SPI_IOC_MESSAGE gives userspace the equivalent of kernel spi_sync().
 * Pass it an array of related transfers, they'll execute together.
 * Each transfer may be half duplex (either direction) or full duplex.
 *
 *	काष्ठा spi_ioc_transfer mesg[4];
 *	...
 *	status = ioctl(fd, SPI_IOC_MESSAGE(4), mesg);
 *
 * So क्रम example one transfer might send a nine bit command (right aligned
 * in a 16-bit word), the next could पढ़ो a block of 8-bit data beक्रमe
 * terminating that command by temporarily deselecting the chip; the next
 * could send a dअगरferent nine bit command (re-selecting the chip), and the
 * last transfer might ग_लिखो some रेजिस्टर values.
 */
काष्ठा spi_ioc_transfer अणु
	__u64		tx_buf;
	__u64		rx_buf;

	__u32		len;
	__u32		speed_hz;

	__u16		delay_usecs;
	__u8		bits_per_word;
	__u8		cs_change;
	__u8		tx_nbits;
	__u8		rx_nbits;
	__u8		word_delay_usecs;
	__u8		pad;

	/* If the contents of 'struct spi_ioc_transfer' ever change
	 * incompatibly, then the ioctl number (currently 0) must change;
	 * ioctls with स्थिरant size fields get a bit more in the way of
	 * error checking than ones (like this) where that field varies.
	 *
	 * NOTE: काष्ठा layout is the same in 64bit and 32bit userspace.
	 */
पूर्ण;

/* not all platक्रमms use <यंत्र-generic/ioctl.h> or _IOC_TYPECHECK() ... */
#घोषणा SPI_MSGSIZE(N) \
	((((N)*(माप (काष्ठा spi_ioc_transfer))) < (1 << _IOC_SIZEBITS)) \
		? ((N)*(माप (काष्ठा spi_ioc_transfer))) : 0)
#घोषणा SPI_IOC_MESSAGE(N) _IOW(SPI_IOC_MAGIC, 0, अक्षर[SPI_MSGSIZE(N)])


/* Read / Write of SPI mode (SPI_MODE_0..SPI_MODE_3) (limited to 8 bits) */
#घोषणा SPI_IOC_RD_MODE			_IOR(SPI_IOC_MAGIC, 1, __u8)
#घोषणा SPI_IOC_WR_MODE			_IOW(SPI_IOC_MAGIC, 1, __u8)

/* Read / Write SPI bit justअगरication */
#घोषणा SPI_IOC_RD_LSB_FIRST		_IOR(SPI_IOC_MAGIC, 2, __u8)
#घोषणा SPI_IOC_WR_LSB_FIRST		_IOW(SPI_IOC_MAGIC, 2, __u8)

/* Read / Write SPI device word length (1..N) */
#घोषणा SPI_IOC_RD_BITS_PER_WORD	_IOR(SPI_IOC_MAGIC, 3, __u8)
#घोषणा SPI_IOC_WR_BITS_PER_WORD	_IOW(SPI_IOC_MAGIC, 3, __u8)

/* Read / Write SPI device शेष max speed hz */
#घोषणा SPI_IOC_RD_MAX_SPEED_HZ		_IOR(SPI_IOC_MAGIC, 4, __u32)
#घोषणा SPI_IOC_WR_MAX_SPEED_HZ		_IOW(SPI_IOC_MAGIC, 4, __u32)

/* Read / Write of the SPI mode field */
#घोषणा SPI_IOC_RD_MODE32		_IOR(SPI_IOC_MAGIC, 5, __u32)
#घोषणा SPI_IOC_WR_MODE32		_IOW(SPI_IOC_MAGIC, 5, __u32)



#पूर्ण_अगर /* SPIDEV_H */
