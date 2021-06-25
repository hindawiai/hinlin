<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */

#अगर_अघोषित _LINUX_ZYNQMP_IPI_MESSAGE_H_
#घोषणा _LINUX_ZYNQMP_IPI_MESSAGE_H_

/**
 * काष्ठा zynqmp_ipi_message - ZynqMP IPI message काष्ठाure
 * @len:  Length of message
 * @data: message payload
 *
 * This is the काष्ठाure क्रम data used in mbox_send_message
 * the maximum length of data buffer is fixed to 12 bytes.
 * Client is supposed to be aware of this.
 */
काष्ठा zynqmp_ipi_message अणु
	माप_प्रकार len;
	u8 data[];
पूर्ण;

#पूर्ण_अगर /* _LINUX_ZYNQMP_IPI_MESSAGE_H_ */
