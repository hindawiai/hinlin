<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित __LINUX_TC_EM_TEXT_H
#घोषणा __LINUX_TC_EM_TEXT_H

#समावेश <linux/types.h>
#समावेश <linux/pkt_cls.h>

#घोषणा TC_EM_TEXT_ALGOSIZ	16

काष्ठा tcf_em_text अणु
	अक्षर		algo[TC_EM_TEXT_ALGOSIZ];
	__u16		from_offset;
	__u16		to_offset;
	__u16		pattern_len;
	__u8		from_layer:4;
	__u8		to_layer:4;
	__u8		pad;
पूर्ण;

#पूर्ण_अगर
