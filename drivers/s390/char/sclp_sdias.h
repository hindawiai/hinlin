<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * SCLP "store data in absolute storage"
 *
 * Copyright IBM Corp. 2003, 2013
 */

#अगर_अघोषित SCLP_SDIAS_H
#घोषणा SCLP_SDIAS_H

#समावेश "sclp.h"

#घोषणा SDIAS_EQ_STORE_DATA		0x0
#घोषणा SDIAS_EQ_SIZE			0x1
#घोषणा SDIAS_DI_FCP_DUMP		0x0
#घोषणा SDIAS_ASA_SIZE_32		0x0
#घोषणा SDIAS_ASA_SIZE_64		0x1
#घोषणा SDIAS_EVSTATE_ALL_STORED	0x0
#घोषणा SDIAS_EVSTATE_NO_DATA		0x3
#घोषणा SDIAS_EVSTATE_PART_STORED	0x10

काष्ठा sdias_evbuf अणु
	काष्ठा	evbuf_header hdr;
	u8	event_qual;
	u8	data_id;
	u64	reserved2;
	u32	event_id;
	u16	reserved3;
	u8	asa_size;
	u8	event_status;
	u32	reserved4;
	u32	blk_cnt;
	u64	asa;
	u32	reserved5;
	u32	fbn;
	u32	reserved6;
	u32	lbn;
	u16	reserved7;
	u16	dbs;
पूर्ण __packed;

काष्ठा sdias_sccb अणु
	काष्ठा sccb_header	hdr;
	काष्ठा sdias_evbuf	evbuf;
पूर्ण __packed;

#पूर्ण_अगर /* SCLP_SDIAS_H */
