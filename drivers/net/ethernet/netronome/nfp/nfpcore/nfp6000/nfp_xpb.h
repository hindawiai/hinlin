<शैली गुरु>
/* SPDX-License-Identअगरier: (GPL-2.0-only OR BSD-2-Clause) */
/* Copyright (C) 2015-2017 Netronome Systems, Inc. */

/*
 * nfp_xpb.h
 * Author: Jason McMullan <jason.mcmullan@netronome.com>
 */

#अगर_अघोषित NFP6000_XPB_H
#घोषणा NFP6000_XPB_H

/* For use with NFP6000 Databook "XPB Addressing" section
 */
#घोषणा NFP_XPB_OVERLAY(island)  (((island) & 0x3f) << 24)

#घोषणा NFP_XPB_ISLAND(island)   (NFP_XPB_OVERLAY(island) + 0x60000)

#घोषणा NFP_XPB_ISLAND_of(offset) (((offset) >> 24) & 0x3F)

/* For use with NFP6000 Databook "XPB Island and Device IDs" chapter
 */
#घोषणा NFP_XPB_DEVICE(island, slave, device) \
	(NFP_XPB_OVERLAY(island) | \
	 (((slave) & 3) << 22) | \
	 (((device) & 0x3f) << 16))

#पूर्ण_अगर /* NFP6000_XPB_H */
