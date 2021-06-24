<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Analog Devices ADV7511 HDMI Transmitter Device Driver
 *
 * Copyright 2013 Cisco Systems, Inc. and/or its affiliates. All rights reserved.
 */

#अगर_अघोषित ADV7511_H
#घोषणा ADV7511_H

/* notअगरy events */
#घोषणा ADV7511_MONITOR_DETECT 0
#घोषणा ADV7511_EDID_DETECT 1


काष्ठा adv7511_monitor_detect अणु
	पूर्णांक present;
पूर्ण;

काष्ठा adv7511_edid_detect अणु
	पूर्णांक present;
	पूर्णांक segment;
	uपूर्णांक16_t phys_addr;
पूर्ण;

काष्ठा adv7511_platक्रमm_data अणु
	u8 i2c_edid;
	u8 i2c_cec;
	u8 i2c_pkपंचांगem;
	u32 cec_clk;
पूर्ण;

#पूर्ण_अगर
