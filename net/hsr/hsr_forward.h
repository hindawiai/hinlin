<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright 2011-2014 Autronica Fire and Security AS
 *
 * Author(s):
 *	2011-2014 Arvid Brodin, arvid.brodin@alten.se
 *
 * include file क्रम HSR and PRP.
 */

#अगर_अघोषित __HSR_FORWARD_H
#घोषणा __HSR_FORWARD_H

#समावेश <linux/netdevice.h>
#समावेश "hsr_main.h"

व्योम hsr_क्रमward_skb(काष्ठा sk_buff *skb, काष्ठा hsr_port *port);
काष्ठा sk_buff *prp_create_tagged_frame(काष्ठा hsr_frame_info *frame,
					काष्ठा hsr_port *port);
काष्ठा sk_buff *hsr_create_tagged_frame(काष्ठा hsr_frame_info *frame,
					काष्ठा hsr_port *port);
काष्ठा sk_buff *hsr_get_untagged_frame(काष्ठा hsr_frame_info *frame,
				       काष्ठा hsr_port *port);
काष्ठा sk_buff *prp_get_untagged_frame(काष्ठा hsr_frame_info *frame,
				       काष्ठा hsr_port *port);
bool prp_drop_frame(काष्ठा hsr_frame_info *frame, काष्ठा hsr_port *port);
bool hsr_drop_frame(काष्ठा hsr_frame_info *frame, काष्ठा hsr_port *port);
पूर्णांक prp_fill_frame_info(__be16 proto, काष्ठा sk_buff *skb,
			काष्ठा hsr_frame_info *frame);
पूर्णांक hsr_fill_frame_info(__be16 proto, काष्ठा sk_buff *skb,
			काष्ठा hsr_frame_info *frame);
#पूर्ण_अगर /* __HSR_FORWARD_H */
