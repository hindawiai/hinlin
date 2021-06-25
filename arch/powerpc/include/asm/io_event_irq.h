<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright 2010, 2011 Mark Nelson and Tseng-Hui (Frank) Lin, IBM Corporation
 */

#अगर_अघोषित _ASM_POWERPC_IO_EVENT_IRQ_H
#घोषणा _ASM_POWERPC_IO_EVENT_IRQ_H

#समावेश <linux/types.h>
#समावेश <linux/notअगरier.h>

#घोषणा PSERIES_IOEI_RPC_MAX_LEN 216

#घोषणा PSERIES_IOEI_TYPE_ERR_DETECTED		0x01
#घोषणा PSERIES_IOEI_TYPE_ERR_RECOVERED		0x02
#घोषणा PSERIES_IOEI_TYPE_EVENT			0x03
#घोषणा PSERIES_IOEI_TYPE_RPC_PASS_THRU		0x04

#घोषणा PSERIES_IOEI_SUBTYPE_NOT_APP		0x00
#घोषणा PSERIES_IOEI_SUBTYPE_REBALANCE_REQ	0x01
#घोषणा PSERIES_IOEI_SUBTYPE_NODE_ONLINE	0x03
#घोषणा PSERIES_IOEI_SUBTYPE_NODE_OFFLINE	0x04
#घोषणा PSERIES_IOEI_SUBTYPE_DUMP_SIZE_CHANGE	0x05
#घोषणा PSERIES_IOEI_SUBTYPE_TORRENT_IRV_UPDATE	0x06
#घोषणा PSERIES_IOEI_SUBTYPE_TORRENT_HFI_CFGED	0x07

#घोषणा PSERIES_IOEI_SCOPE_NOT_APP		0x00
#घोषणा PSERIES_IOEI_SCOPE_RIO_HUB		0x36
#घोषणा PSERIES_IOEI_SCOPE_RIO_BRIDGE		0x37
#घोषणा PSERIES_IOEI_SCOPE_PHB			0x38
#घोषणा PSERIES_IOEI_SCOPE_EADS_GLOBAL		0x39
#घोषणा PSERIES_IOEI_SCOPE_EADS_SLOT		0x3A
#घोषणा PSERIES_IOEI_SCOPE_TORRENT_HUB		0x3B
#घोषणा PSERIES_IOEI_SCOPE_SERVICE_PROC		0x51

/* Platक्रमm Event Log Format, Version 6, data portition of IO event section */
काष्ठा pseries_io_event अणु
	uपूर्णांक8_t event_type;		/* 0x00 IO-Event Type		*/
	uपूर्णांक8_t rpc_data_len;		/* 0x01 RPC data length		*/
	uपूर्णांक8_t scope;			/* 0x02 Error/Event Scope	*/
	uपूर्णांक8_t event_subtype;		/* 0x03 I/O-Event Sub-Type	*/
	uपूर्णांक32_t drc_index;		/* 0x04 DRC Index		*/
	uपूर्णांक8_t rpc_data[PSERIES_IOEI_RPC_MAX_LEN];
					/* 0x08 RPC Data (0-216 bytes,	*/
					/* padded to 4 bytes alignment)	*/
पूर्ण;

बाह्य काष्ठा atomic_notअगरier_head pseries_ioei_notअगरier_list;

#पूर्ण_अगर /* _ASM_POWERPC_IO_EVENT_IRQ_H */
