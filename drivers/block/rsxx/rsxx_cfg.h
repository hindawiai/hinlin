<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
* Filename: rsXX_cfg.h
*
* Authors: Joshua Morris <josh.h.morris@us.ibm.com>
*	Philip Kelleher <pjk1939@linux.vnet.ibm.com>
*
* (C) Copyright 2013 IBM Corporation
*/

#अगर_अघोषित __RSXX_CFG_H__
#घोषणा __RSXX_CFG_H__

/* NOTE: Config values will be saved in network byte order (i.e. Big endian) */
#समावेश <linux/types.h>

/*
 * The card config version must match the driver's expected version. If it करोes
 * not, the DMA पूर्णांकerfaces will not be attached and the user will need to
 * initialize/upgrade the card configuration using the card config utility.
 */
#घोषणा RSXX_CFG_VERSION	4

काष्ठा card_cfg_hdr अणु
	__u32	version;
	__u32	crc;
पूर्ण;

काष्ठा card_cfg_data अणु
	__u32	block_size;
	__u32	stripe_size;
	__u32	venकरोr_id;
	__u32	cache_order;
	काष्ठा अणु
		__u32	mode;	/* Disabled, manual, स्वतः-tune... */
		__u32	count;	/* Number of पूर्णांकr to coalesce     */
		__u32	latency;/* Max रुको समय (in ns)          */
	पूर्ण पूर्णांकr_coal;
पूर्ण;

काष्ठा rsxx_card_cfg अणु
	काष्ठा card_cfg_hdr	hdr;
	काष्ठा card_cfg_data	data;
पूर्ण;

/* Venकरोr ID Values */
#घोषणा RSXX_VENDOR_ID_IBM		0
#घोषणा RSXX_VENDOR_ID_DSI		1
#घोषणा RSXX_VENDOR_COUNT		2

/* Interrupt Coalescing Values */
#घोषणा RSXX_INTR_COAL_DISABLED           0
#घोषणा RSXX_INTR_COAL_EXPLICIT           1
#घोषणा RSXX_INTR_COAL_AUTO_TUNE          2


#पूर्ण_अगर /* __RSXX_CFG_H__ */

