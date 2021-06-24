<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित _UAPIASM_SCHID_H
#घोषणा _UAPIASM_SCHID_H

#समावेश <linux/types.h>

काष्ठा subchannel_id अणु
	__u32 cssid : 8;
	__u32 : 4;
	__u32 m : 1;
	__u32 ssid : 2;
	__u32 one : 1;
	__u32 sch_no : 16;
पूर्ण __attribute__ ((packed, aligned(4)));


#पूर्ण_अगर /* _UAPIASM_SCHID_H */
