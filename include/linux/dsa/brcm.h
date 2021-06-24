<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only
 * Copyright (C) 2014 Broadcom Corporation
 */

/* Included by drivers/net/ethernet/broadcom/bcmsysport.c and
 * net/dsa/tag_brcm.c
 */
#अगर_अघोषित _NET_DSA_BRCM_H
#घोषणा _NET_DSA_BRCM_H

/* Broadcom tag specअगरic helpers to insert and extract queue/port number */
#घोषणा BRCM_TAG_SET_PORT_QUEUE(p, q)	((p) << 8 | q)
#घोषणा BRCM_TAG_GET_PORT(v)		((v) >> 8)
#घोषणा BRCM_TAG_GET_QUEUE(v)		((v) & 0xff)

#पूर्ण_अगर
