<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित _XT_DCCP_H_
#घोषणा _XT_DCCP_H_

#समावेश <linux/types.h>

#घोषणा XT_DCCP_SRC_PORTS	        0x01
#घोषणा XT_DCCP_DEST_PORTS	        0x02
#घोषणा XT_DCCP_TYPE			0x04
#घोषणा XT_DCCP_OPTION			0x08

#घोषणा XT_DCCP_VALID_FLAGS		0x0f

काष्ठा xt_dccp_info अणु
	__u16 dpts[2];  /* Min, Max */
	__u16 spts[2];  /* Min, Max */

	__u16 flags;
	__u16 invflags;

	__u16 typemask;
	__u8 option;
पूर्ण;

#पूर्ण_अगर /* _XT_DCCP_H_ */

