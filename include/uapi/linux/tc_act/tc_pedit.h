<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित __LINUX_TC_PED_H
#घोषणा __LINUX_TC_PED_H

#समावेश <linux/types.h>
#समावेश <linux/pkt_cls.h>

क्रमागत अणु
	TCA_PEDIT_UNSPEC,
	TCA_PEDIT_TM,
	TCA_PEDIT_PARMS,
	TCA_PEDIT_PAD,
	TCA_PEDIT_PARMS_EX,
	TCA_PEDIT_KEYS_EX,
	TCA_PEDIT_KEY_EX,
	__TCA_PEDIT_MAX
पूर्ण;

#घोषणा TCA_PEDIT_MAX (__TCA_PEDIT_MAX - 1)

क्रमागत अणु
	TCA_PEDIT_KEY_EX_HTYPE = 1,
	TCA_PEDIT_KEY_EX_CMD = 2,
	__TCA_PEDIT_KEY_EX_MAX
पूर्ण;

#घोषणा TCA_PEDIT_KEY_EX_MAX (__TCA_PEDIT_KEY_EX_MAX - 1)

 /* TCA_PEDIT_KEY_EX_HDR_TYPE_NETWROK is a special हाल क्रम legacy users. It
  * means no specअगरic header type - offset is relative to the network layer
  */
क्रमागत pedit_header_type अणु
	TCA_PEDIT_KEY_EX_HDR_TYPE_NETWORK = 0,
	TCA_PEDIT_KEY_EX_HDR_TYPE_ETH = 1,
	TCA_PEDIT_KEY_EX_HDR_TYPE_IP4 = 2,
	TCA_PEDIT_KEY_EX_HDR_TYPE_IP6 = 3,
	TCA_PEDIT_KEY_EX_HDR_TYPE_TCP = 4,
	TCA_PEDIT_KEY_EX_HDR_TYPE_UDP = 5,
	__PEDIT_HDR_TYPE_MAX,
पूर्ण;

#घोषणा TCA_PEDIT_HDR_TYPE_MAX (__PEDIT_HDR_TYPE_MAX - 1)

क्रमागत pedit_cmd अणु
	TCA_PEDIT_KEY_EX_CMD_SET = 0,
	TCA_PEDIT_KEY_EX_CMD_ADD = 1,
	__PEDIT_CMD_MAX,
पूर्ण;

#घोषणा TCA_PEDIT_CMD_MAX (__PEDIT_CMD_MAX - 1)

काष्ठा tc_pedit_key अणु
	__u32           mask;  /* AND */
	__u32           val;   /*XOR */
	__u32           off;  /*offset */
	__u32           at;
	__u32           offmask;
	__u32           shअगरt;
पूर्ण;

काष्ठा tc_pedit_sel अणु
	tc_gen;
	अचिन्हित अक्षर           nkeys;
	अचिन्हित अक्षर           flags;
	काष्ठा tc_pedit_key     keys[0];
पूर्ण;

#घोषणा tc_pedit tc_pedit_sel

#पूर्ण_अगर
