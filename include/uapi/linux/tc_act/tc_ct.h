<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित __UAPI_TC_CT_H
#घोषणा __UAPI_TC_CT_H

#समावेश <linux/types.h>
#समावेश <linux/pkt_cls.h>

क्रमागत अणु
	TCA_CT_UNSPEC,
	TCA_CT_PARMS,
	TCA_CT_TM,
	TCA_CT_ACTION,		/* u16 */
	TCA_CT_ZONE,		/* u16 */
	TCA_CT_MARK,		/* u32 */
	TCA_CT_MARK_MASK,	/* u32 */
	TCA_CT_LABELS,		/* u128 */
	TCA_CT_LABELS_MASK,	/* u128 */
	TCA_CT_NAT_IPV4_MIN,	/* be32 */
	TCA_CT_NAT_IPV4_MAX,	/* be32 */
	TCA_CT_NAT_IPV6_MIN,	/* काष्ठा in6_addr */
	TCA_CT_NAT_IPV6_MAX,	/* काष्ठा in6_addr */
	TCA_CT_NAT_PORT_MIN,	/* be16 */
	TCA_CT_NAT_PORT_MAX,	/* be16 */
	TCA_CT_PAD,
	__TCA_CT_MAX
पूर्ण;

#घोषणा TCA_CT_MAX (__TCA_CT_MAX - 1)

#घोषणा TCA_CT_ACT_COMMIT	(1 << 0)
#घोषणा TCA_CT_ACT_FORCE	(1 << 1)
#घोषणा TCA_CT_ACT_CLEAR	(1 << 2)
#घोषणा TCA_CT_ACT_NAT		(1 << 3)
#घोषणा TCA_CT_ACT_NAT_SRC	(1 << 4)
#घोषणा TCA_CT_ACT_NAT_DST	(1 << 5)

काष्ठा tc_ct अणु
	tc_gen;
पूर्ण;

#पूर्ण_अगर /* __UAPI_TC_CT_H */
