<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
#अगर_अघोषित KP2000_CDEV_UAPI_H_
#घोषणा KP2000_CDEV_UAPI_H_
#समावेश <linux/types.h>
#समावेश <linux/ioctl.h>

काष्ठा kp2000_regs अणु
	__u32 card_id;
	__u32 build_version;
	__u32 build_datestamp;
	__u32 build_बारtamp;
	__u32 hw_rev;
	__u64 ssid;
	__u64 ddna;
	__u64 cpld_reg;
पूर्ण;

#घोषणा KP2000_IOCTL_GET_CPLD_REG		_IOR('k', 9, __u32)
#घोषणा KP2000_IOCTL_GET_PCIE_ERROR_REG		_IOR('k', 11, __u32)
#घोषणा KP2000_IOCTL_GET_EVERYTHING		_IOR('k', 8, काष्ठा kp2000_regs*)

#पूर्ण_अगर /* KP2000_CDEV_UAPI_H_ */
