<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ WITH Linux-syscall-note */
#अगर_अघोषित _UAPI_LINUX_FSI_H
#घोषणा _UAPI_LINUX_FSI_H

#समावेश <linux/types.h>
#समावेश <linux/ioctl.h>

/*
 * /dev/scom "raw" ioctl पूर्णांकerface
 *
 * The driver supports a high level "read/write" पूर्णांकerface which
 * handles retries and converts the status to Linux error codes,
 * however low level tools an debugger need to access the "raw"
 * HW status inक्रमmation and पूर्णांकerpret it themselves, so this
 * ioctl पूर्णांकerface is also provided क्रम their use हाल.
 */

/* Structure क्रम SCOM पढ़ो/ग_लिखो */
काष्ठा scom_access अणु
	__u64	addr;		/* SCOM address, supports indirect */
	__u64	data;		/* SCOM data (in क्रम ग_लिखो, out क्रम पढ़ो) */
	__u64	mask;		/* Data mask क्रम ग_लिखोs */
	__u32	पूर्णांकf_errors;	/* Interface error flags */
#घोषणा SCOM_INTF_ERR_PARITY		0x00000001 /* Parity error */
#घोषणा SCOM_INTF_ERR_PROTECTION	0x00000002 /* Blocked by secure boot */
#घोषणा SCOM_INTF_ERR_ABORT		0x00000004 /* PIB reset during access */
#घोषणा SCOM_INTF_ERR_UNKNOWN		0x80000000 /* Unknown error */
	/*
	 * Note: Any other bit set in पूर्णांकf_errors need to be considered as an
	 * error. Future implementations may define new error conditions. The
	 * pib_status below is only valid अगर पूर्णांकf_errors is 0.
	 */
	__u8	pib_status;	/* 3-bit PIB status */
#घोषणा SCOM_PIB_SUCCESS	0	/* Access successful */
#घोषणा SCOM_PIB_BLOCKED	1	/* PIB blocked, pls retry */
#घोषणा SCOM_PIB_OFFLINE	2	/* Chiplet offline */
#घोषणा SCOM_PIB_PARTIAL	3	/* Partial good */
#घोषणा SCOM_PIB_BAD_ADDR	4	/* Invalid address */
#घोषणा SCOM_PIB_CLK_ERR	5	/* Clock error */
#घोषणा SCOM_PIB_PARITY_ERR	6	/* Parity error on the PIB bus */
#घोषणा SCOM_PIB_TIMEOUT	7	/* Bus समयout */
	__u8	pad;
पूर्ण;

/* Flags क्रम SCOM check */
#घोषणा SCOM_CHECK_SUPPORTED	0x00000001	/* Interface supported */
#घोषणा SCOM_CHECK_PROTECTED	0x00000002	/* Interface blocked by secure boot */

/* Flags क्रम SCOM reset */
#घोषणा SCOM_RESET_INTF		0x00000001	/* Reset पूर्णांकerface */
#घोषणा SCOM_RESET_PIB		0x00000002	/* Reset PIB */

#घोषणा FSI_SCOM_CHECK	_IOR('s', 0x00, __u32)
#घोषणा FSI_SCOM_READ	_IOWR('s', 0x01, काष्ठा scom_access)
#घोषणा FSI_SCOM_WRITE	_IOWR('s', 0x02, काष्ठा scom_access)
#घोषणा FSI_SCOM_RESET	_IOW('s', 0x03, __u32)

#पूर्ण_अगर /* _UAPI_LINUX_FSI_H */
