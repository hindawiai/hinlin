<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/*
 * Broadcom Cable Modem firmware क्रमmat
 */

#अगर_अघोषित __BCM933XX_HCS_H
#घोषणा __BCM933XX_HCS_H

#समावेश <linux/types.h>

काष्ठा bcm_hcs अणु
	__u16 magic;
	__u16 control;
	__u16 rev_maj;
	__u16 rev_min;
	__u32 build_date;
	__u32 filelen;
	__u32 ldaddress;
	अक्षर filename[64];
	__u16 hcs;
	__u16 her_znaet_chto;
	__u32 crc;
पूर्ण;

#पूर्ण_अगर /* __BCM933XX_HCS */
