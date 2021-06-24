<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * Copyright (c) 1996, 2003 VIA Networking Technologies, Inc.
 * All rights reserved.
 *
 * File: baseband.h
 *
 * Purpose: Implement functions to access baseband
 *
 * Author: Jerry Chen
 *
 * Date: Jun. 5, 2002
 *
 * Revision History:
 *      06-10-2003 Bryan YC Fan:  Re-ग_लिखो codes to support VT3253 spec.
 *      08-26-2003 Kyle Hsu    :  Add defines of packet type and TX rate.
 */

#अगर_अघोषित __BASEBAND_H__
#घोषणा __BASEBAND_H__

#समावेश "device.h"

#घोषणा PREAMBLE_LONG   0
#घोषणा PREAMBLE_SHORT  1

/*
 * Registers in the BASEBAND
 */
#घोषणा BB_MAX_CONTEXT_SIZE 256

#घोषणा C_SIFS_A      16      /* usec */
#घोषणा C_SIFS_BG     10

#घोषणा C_EIFS      80      /* usec */

#घोषणा C_SLOT_SHORT   9      /* usec */
#घोषणा C_SLOT_LONG   20

#घोषणा C_CWMIN_A     15       /* slot समय */
#घोषणा C_CWMIN_B     31

#घोषणा C_CWMAX      1023     /* slot समय */

/* 0:11A 1:11B 2:11G */
#घोषणा BB_TYPE_11A    0
#घोषणा BB_TYPE_11B    1
#घोषणा BB_TYPE_11G    2

/* 0:11a, 1:11b, 2:11gb (only CCK in BasicRate), 3:11ga (OFDM in BasicRate) */
#घोषणा PK_TYPE_11A     0
#घोषणा PK_TYPE_11B     1
#घोषणा PK_TYPE_11GB    2
#घोषणा PK_TYPE_11GA    3

#घोषणा TOP_RATE_54M        0x80000000
#घोषणा TOP_RATE_48M        0x40000000
#घोषणा TOP_RATE_36M        0x20000000
#घोषणा TOP_RATE_24M        0x10000000
#घोषणा TOP_RATE_18M        0x08000000
#घोषणा TOP_RATE_12M        0x04000000
#घोषणा TOP_RATE_11M        0x02000000
#घोषणा TOP_RATE_9M         0x01000000
#घोषणा TOP_RATE_6M         0x00800000
#घोषणा TOP_RATE_55M        0x00400000
#घोषणा TOP_RATE_2M         0x00200000
#घोषणा TOP_RATE_1M         0x00100000

पूर्णांक vnt_set_लघु_slot_समय(काष्ठा vnt_निजी *priv);
पूर्णांक vnt_set_vga_gain_offset(काष्ठा vnt_निजी *priv, u8 data);
पूर्णांक vnt_set_antenna_mode(काष्ठा vnt_निजी *priv, u8 antenna_mode);
पूर्णांक vnt_vt3184_init(काष्ठा vnt_निजी *priv);
पूर्णांक vnt_set_deep_sleep(काष्ठा vnt_निजी *priv);
पूर्णांक vnt_निकास_deep_sleep(काष्ठा vnt_निजी *priv);
पूर्णांक vnt_update_pre_ed_threshold(काष्ठा vnt_निजी *priv, पूर्णांक scanning);

#पूर्ण_अगर /* __BASEBAND_H__ */
