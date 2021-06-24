<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * IPWireless 3G PCMCIA Network Driver
 *
 * Original code
 *   by Stephen Blackheath <stephen@blacksapphire.com>,
 *      Ben Martel <benm@symmetric.co.nz>
 *
 * Copyrighted as follows:
 *   Copyright (C) 2004 by Symmetric Systems Ltd (NZ)
 *
 * Various driver changes and reग_लिखोs, port to new kernels
 *   Copyright (C) 2006-2007 Jiri Kosina
 *
 * Misc code cleanups and updates
 *   Copyright (C) 2007 David Sterba
 */

#अगर_अघोषित _IPWIRELESS_CS_HARDWARE_H_
#घोषणा _IPWIRELESS_CS_HARDWARE_H_

#समावेश <linux/types.h>
#समावेश <linux/sched.h>
#समावेश <linux/पूर्णांकerrupt.h>

#घोषणा IPW_CONTROL_LINE_CTS 0x0001
#घोषणा IPW_CONTROL_LINE_DCD 0x0002
#घोषणा IPW_CONTROL_LINE_DSR 0x0004
#घोषणा IPW_CONTROL_LINE_RI  0x0008
#घोषणा IPW_CONTROL_LINE_DTR 0x0010
#घोषणा IPW_CONTROL_LINE_RTS 0x0020

काष्ठा ipw_hardware;
काष्ठा ipw_network;

काष्ठा ipw_hardware *ipwireless_hardware_create(व्योम);
व्योम ipwireless_hardware_मुक्त(काष्ठा ipw_hardware *hw);
irqवापस_t ipwireless_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id);
पूर्णांक ipwireless_set_DTR(काष्ठा ipw_hardware *hw, अचिन्हित पूर्णांक channel_idx,
		पूर्णांक state);
पूर्णांक ipwireless_set_RTS(काष्ठा ipw_hardware *hw, अचिन्हित पूर्णांक channel_idx,
		पूर्णांक state);
पूर्णांक ipwireless_send_packet(काष्ठा ipw_hardware *hw,
			    अचिन्हित पूर्णांक channel_idx,
			    स्थिर अचिन्हित अक्षर *data,
			    अचिन्हित पूर्णांक length,
			    व्योम (*packet_sent_callback) (व्योम *cb,
							  अचिन्हित पूर्णांक length),
			    व्योम *sent_cb_data);
व्योम ipwireless_associate_network(काष्ठा ipw_hardware *hw,
		काष्ठा ipw_network *net);
व्योम ipwireless_stop_पूर्णांकerrupts(काष्ठा ipw_hardware *hw);
व्योम ipwireless_init_hardware_v1(काष्ठा ipw_hardware *hw,
				 अचिन्हित पूर्णांक base_port,
				 व्योम __iomem *attr_memory,
				 व्योम __iomem *common_memory,
				 पूर्णांक is_v2_card,
				 व्योम (*reboot_cb) (व्योम *data),
				 व्योम *reboot_cb_data);
व्योम ipwireless_init_hardware_v2_v3(काष्ठा ipw_hardware *hw);
व्योम ipwireless_sleep(अचिन्हित पूर्णांक tenths);

#पूर्ण_अगर
