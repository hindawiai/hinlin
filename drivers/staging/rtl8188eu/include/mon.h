<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * RTL8188EU monitor पूर्णांकerface
 *
 * Copyright (C) 2015 Jakub Sitnicki
 */

/*
 * Monitor पूर्णांकerface receives all transmitted and received IEEE 802.11
 * frames, both Data and Management, and passes them up to userspace
 * preserving the WLAN headers.
 */

#अगर_अघोषित _MON_H_
#घोषणा _MON_H_

काष्ठा net_device;
काष्ठा recv_frame;
काष्ठा xmit_frame;

काष्ठा net_device *rtl88eu_mon_init(व्योम);
व्योम rtl88eu_mon_deinit(काष्ठा net_device *dev);

व्योम rtl88eu_mon_recv_hook(काष्ठा net_device *dev, काष्ठा recv_frame *frame);
व्योम rtl88eu_mon_xmit_hook(काष्ठा net_device *dev, काष्ठा xmit_frame *frame,
			   uपूर्णांक frag_len);

#पूर्ण_अगर /* _MON_H_ */
