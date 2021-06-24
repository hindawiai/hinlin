<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/*
 * Copyright (C) 2007 Stefan Kopp, Gechingen, Germany
 * Copyright (C) 2008 Novell, Inc.
 * Copyright (C) 2008 Greg Kroah-Harपंचांगan <gregkh@suse.de>
 * Copyright (C) 2015 Dave Penkler <dpenkler@gmail.com>
 * Copyright (C) 2018 IVI Foundation, Inc.
 *
 * This file holds USB स्थिरants defined by the USB Device Class
 * and USB488 Subclass Definitions क्रम Test and Measurement devices
 * published by the USB-IF.
 *
 * It also has the ioctl and capability definitions क्रम the
 * usbपंचांगc kernel driver that userspace needs to know about.
 */

#अगर_अघोषित __LINUX_USB_TMC_H
#घोषणा __LINUX_USB_TMC_H

#समावेश <linux/types.h>   /* __u8 etc */

/* USB TMC status values */
#घोषणा USBTMC_STATUS_SUCCESS				0x01
#घोषणा USBTMC_STATUS_PENDING				0x02
#घोषणा USBTMC_STATUS_FAILED				0x80
#घोषणा USBTMC_STATUS_TRANSFER_NOT_IN_PROGRESS		0x81
#घोषणा USBTMC_STATUS_SPLIT_NOT_IN_PROGRESS		0x82
#घोषणा USBTMC_STATUS_SPLIT_IN_PROGRESS			0x83

/* USB TMC requests values */
#घोषणा USBTMC_REQUEST_INITIATE_ABORT_BULK_OUT		1
#घोषणा USBTMC_REQUEST_CHECK_ABORT_BULK_OUT_STATUS	2
#घोषणा USBTMC_REQUEST_INITIATE_ABORT_BULK_IN		3
#घोषणा USBTMC_REQUEST_CHECK_ABORT_BULK_IN_STATUS	4
#घोषणा USBTMC_REQUEST_INITIATE_CLEAR			5
#घोषणा USBTMC_REQUEST_CHECK_CLEAR_STATUS		6
#घोषणा USBTMC_REQUEST_GET_CAPABILITIES			7
#घोषणा USBTMC_REQUEST_INDICATOR_PULSE			64
#घोषणा USBTMC488_REQUEST_READ_STATUS_BYTE		128
#घोषणा USBTMC488_REQUEST_REN_CONTROL			160
#घोषणा USBTMC488_REQUEST_GOTO_LOCAL			161
#घोषणा USBTMC488_REQUEST_LOCAL_LOCKOUT			162

काष्ठा usbपंचांगc_request अणु
	__u8 bRequestType;
	__u8 bRequest;
	__u16 wValue;
	__u16 wIndex;
	__u16 wLength;
पूर्ण __attribute__ ((packed));

काष्ठा usbपंचांगc_ctrlrequest अणु
	काष्ठा usbपंचांगc_request req;
	व्योम __user *data; /* poपूर्णांकer to user space */
पूर्ण __attribute__ ((packed));

काष्ठा usbपंचांगc_termअक्षर अणु
	__u8 term_अक्षर;
	__u8 term_अक्षर_enabled;
पूर्ण __attribute__ ((packed));

/*
 * usbपंचांगc_message->flags:
 */
#घोषणा USBTMC_FLAG_ASYNC		0x0001
#घोषणा USBTMC_FLAG_APPEND		0x0002
#घोषणा USBTMC_FLAG_IGNORE_TRAILER	0x0004

काष्ठा usbपंचांगc_message अणु
	__u32 transfer_size; /* size of bytes to transfer */
	__u32 transferred; /* size of received/written bytes */
	__u32 flags; /* bit 0: 0 = synchronous; 1 = asynchronous */
	व्योम __user *message; /* poपूर्णांकer to header and data in user space */
पूर्ण __attribute__ ((packed));

/* Request values क्रम USBTMC driver's ioctl entry poपूर्णांक */
#घोषणा USBTMC_IOC_NR			91
#घोषणा USBTMC_IOCTL_INDICATOR_PULSE	_IO(USBTMC_IOC_NR, 1)
#घोषणा USBTMC_IOCTL_CLEAR		_IO(USBTMC_IOC_NR, 2)
#घोषणा USBTMC_IOCTL_ABORT_BULK_OUT	_IO(USBTMC_IOC_NR, 3)
#घोषणा USBTMC_IOCTL_ABORT_BULK_IN	_IO(USBTMC_IOC_NR, 4)
#घोषणा USBTMC_IOCTL_CLEAR_OUT_HALT	_IO(USBTMC_IOC_NR, 6)
#घोषणा USBTMC_IOCTL_CLEAR_IN_HALT	_IO(USBTMC_IOC_NR, 7)
#घोषणा USBTMC_IOCTL_CTRL_REQUEST	_IOWR(USBTMC_IOC_NR, 8, काष्ठा usbपंचांगc_ctrlrequest)
#घोषणा USBTMC_IOCTL_GET_TIMEOUT	_IOR(USBTMC_IOC_NR, 9, __u32)
#घोषणा USBTMC_IOCTL_SET_TIMEOUT	_IOW(USBTMC_IOC_NR, 10, __u32)
#घोषणा USBTMC_IOCTL_EOM_ENABLE	        _IOW(USBTMC_IOC_NR, 11, __u8)
#घोषणा USBTMC_IOCTL_CONFIG_TERMCHAR	_IOW(USBTMC_IOC_NR, 12, काष्ठा usbपंचांगc_termअक्षर)
#घोषणा USBTMC_IOCTL_WRITE		_IOWR(USBTMC_IOC_NR, 13, काष्ठा usbपंचांगc_message)
#घोषणा USBTMC_IOCTL_READ		_IOWR(USBTMC_IOC_NR, 14, काष्ठा usbपंचांगc_message)
#घोषणा USBTMC_IOCTL_WRITE_RESULT	_IOWR(USBTMC_IOC_NR, 15, __u32)
#घोषणा USBTMC_IOCTL_API_VERSION	_IOR(USBTMC_IOC_NR, 16, __u32)

#घोषणा USBTMC488_IOCTL_GET_CAPS	_IOR(USBTMC_IOC_NR, 17, अचिन्हित अक्षर)
#घोषणा USBTMC488_IOCTL_READ_STB	_IOR(USBTMC_IOC_NR, 18, अचिन्हित अक्षर)
#घोषणा USBTMC488_IOCTL_REN_CONTROL	_IOW(USBTMC_IOC_NR, 19, अचिन्हित अक्षर)
#घोषणा USBTMC488_IOCTL_GOTO_LOCAL	_IO(USBTMC_IOC_NR, 20)
#घोषणा USBTMC488_IOCTL_LOCAL_LOCKOUT	_IO(USBTMC_IOC_NR, 21)
#घोषणा USBTMC488_IOCTL_TRIGGER		_IO(USBTMC_IOC_NR, 22)
#घोषणा USBTMC488_IOCTL_WAIT_SRQ	_IOW(USBTMC_IOC_NR, 23, __u32)

#घोषणा USBTMC_IOCTL_MSG_IN_ATTR	_IOR(USBTMC_IOC_NR, 24, __u8)
#घोषणा USBTMC_IOCTL_AUTO_ABORT		_IOW(USBTMC_IOC_NR, 25, __u8)

#घोषणा USBTMC_IOCTL_GET_STB            _IOR(USBTMC_IOC_NR, 26, __u8)
#घोषणा USBTMC_IOCTL_GET_SRQ_STB        _IOR(USBTMC_IOC_NR, 27, __u8)

/* Cancel and cleanup asynchronous calls */
#घोषणा USBTMC_IOCTL_CANCEL_IO		_IO(USBTMC_IOC_NR, 35)
#घोषणा USBTMC_IOCTL_CLEANUP_IO		_IO(USBTMC_IOC_NR, 36)

/* Driver encoded usb488 capabilities */
#घोषणा USBTMC488_CAPABILITY_TRIGGER         1
#घोषणा USBTMC488_CAPABILITY_SIMPLE          2
#घोषणा USBTMC488_CAPABILITY_REN_CONTROL     2
#घोषणा USBTMC488_CAPABILITY_GOTO_LOCAL      2
#घोषणा USBTMC488_CAPABILITY_LOCAL_LOCKOUT   2
#घोषणा USBTMC488_CAPABILITY_488_DOT_2       4
#घोषणा USBTMC488_CAPABILITY_DT1             16
#घोषणा USBTMC488_CAPABILITY_RL1             32
#घोषणा USBTMC488_CAPABILITY_SR1             64
#घोषणा USBTMC488_CAPABILITY_FULL_SCPI       128

#पूर्ण_अगर
