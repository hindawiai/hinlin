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
 */

#अगर_अघोषित __BASEBAND_H__
#घोषणा __BASEBAND_H__

#समावेश "device.h"

/*
 * Registers in the BASEBAND
 */
#घोषणा BB_MAX_CONTEXT_SIZE 256

/*
 * Baseband RF pair definition in eeprom (Bits 6..0)
 */

#घोषणा PREAMBLE_LONG   0
#घोषणा PREAMBLE_SHORT  1

#घोषणा F5G             0
#घोषणा F2_4G           1

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

अचिन्हित पूर्णांक bb_get_frame_समय(अचिन्हित अक्षर by_preamble_type,
			       अचिन्हित अक्षर by_pkt_type,
			       अचिन्हित पूर्णांक cb_frame_length,
			       अचिन्हित लघु w_rate);

व्योम vnt_get_phy_field(काष्ठा vnt_निजी *priv, u32 frame_length,
		       u16 tx_rate, u8 pkt_type, काष्ठा vnt_phy_field *phy);

bool bb_पढ़ो_embedded(काष्ठा vnt_निजी *priv, अचिन्हित अक्षर by_bb_addr,
		      अचिन्हित अक्षर *pby_data);
bool bb_ग_लिखो_embedded(काष्ठा vnt_निजी *priv, अचिन्हित अक्षर by_bb_addr,
		       अचिन्हित अक्षर by_data);

व्योम bb_set_लघु_slot_समय(काष्ठा vnt_निजी *priv);
व्योम bb_set_vga_gain_offset(काष्ठा vnt_निजी *priv, अचिन्हित अक्षर by_data);

/* VT3253 Baseband */
bool bb_vt3253_init(काष्ठा vnt_निजी *priv);
व्योम bb_software_reset(काष्ठा vnt_निजी *priv);
व्योम bb_घातer_save_mode_on(काष्ठा vnt_निजी *priv);
व्योम bb_घातer_save_mode_off(काष्ठा vnt_निजी *priv);
व्योम bb_set_tx_antenna_mode(काष्ठा vnt_निजी *priv,
			    अचिन्हित अक्षर by_antenna_mode);
व्योम bb_set_rx_antenna_mode(काष्ठा vnt_निजी *priv,
			    अचिन्हित अक्षर by_antenna_mode);
व्योम bb_set_deep_sleep(काष्ठा vnt_निजी *priv, अचिन्हित अक्षर by_local_id);

#पूर्ण_अगर /* __BASEBAND_H__ */
