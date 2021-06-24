<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Abilis Systems Single DVB-T Receiver
 * Copyright (C) 2008 Pierrick Hascoet <pierrick.hascoet@abilis.com>
 */
#घोषणा MAX_FW_PKT_SIZE	64

बाह्य पूर्णांक dual_tuner;

काष्ठा as10x_raw_fw_pkt अणु
	अचिन्हित अक्षर address[4];
	अचिन्हित अक्षर data[MAX_FW_PKT_SIZE - 6];
पूर्ण __packed;

काष्ठा as10x_fw_pkt_t अणु
	जोड़ अणु
		अचिन्हित अक्षर request[2];
		अचिन्हित अक्षर length[2];
	पूर्ण __packed u;
	काष्ठा as10x_raw_fw_pkt raw;
पूर्ण __packed;

#अगर_घोषित __KERNEL__
पूर्णांक as102_fw_upload(काष्ठा as10x_bus_adapter_t *bus_adap);
#पूर्ण_अगर
