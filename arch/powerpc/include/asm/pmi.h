<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
#अगर_अघोषित _POWERPC_PMI_H
#घोषणा _POWERPC_PMI_H

/*
 * Definitions क्रम talking with PMI device on PowerPC
 *
 * PMI (Platक्रमm Management Interrupt) is a way to communicate
 * with the BMC (Baseboard Management Controller) via पूर्णांकerrupts.
 * Unlike IPMI it is bidirectional and has a low latency.
 *
 * (C) Copyright IBM Deutschland Entwicklung GmbH 2005
 *
 * Author: Christian Krafft <krafft@de.ibm.com>
 */

#अगर_घोषित __KERNEL__

#घोषणा PMI_TYPE_FREQ_CHANGE	0x01
#घोषणा PMI_TYPE_POWER_BUTTON	0x02
#घोषणा PMI_READ_TYPE		0
#घोषणा PMI_READ_DATA0		1
#घोषणा PMI_READ_DATA1		2
#घोषणा PMI_READ_DATA2		3
#घोषणा PMI_WRITE_TYPE		4
#घोषणा PMI_WRITE_DATA0		5
#घोषणा PMI_WRITE_DATA1		6
#घोषणा PMI_WRITE_DATA2		7

#घोषणा PMI_ACK			0x80

#घोषणा PMI_TIMEOUT		100

प्रकार काष्ठा अणु
	u8	type;
	u8	data0;
	u8	data1;
	u8	data2;
पूर्ण pmi_message_t;

काष्ठा pmi_handler अणु
	काष्ठा list_head node;
	u8 type;
	व्योम (*handle_pmi_message) (pmi_message_t);
पूर्ण;

पूर्णांक pmi_रेजिस्टर_handler(काष्ठा pmi_handler *);
व्योम pmi_unरेजिस्टर_handler(काष्ठा pmi_handler *);

पूर्णांक pmi_send_message(pmi_message_t);

#पूर्ण_अगर /* __KERNEL__ */
#पूर्ण_अगर /* _POWERPC_PMI_H */
