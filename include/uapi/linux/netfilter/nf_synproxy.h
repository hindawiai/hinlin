<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित _NF_SYNPROXY_H
#घोषणा _NF_SYNPROXY_H

#समावेश <linux/types.h>

#घोषणा NF_SYNPROXY_OPT_MSS		0x01
#घोषणा NF_SYNPROXY_OPT_WSCALE		0x02
#घोषणा NF_SYNPROXY_OPT_SACK_PERM	0x04
#घोषणा NF_SYNPROXY_OPT_TIMESTAMP	0x08
#घोषणा NF_SYNPROXY_OPT_ECN		0x10
#घोषणा NF_SYNPROXY_OPT_MASK		(NF_SYNPROXY_OPT_MSS | \
					 NF_SYNPROXY_OPT_WSCALE | \
					 NF_SYNPROXY_OPT_SACK_PERM | \
					 NF_SYNPROXY_OPT_TIMESTAMP)

काष्ठा nf_synproxy_info अणु
	__u8	options;
	__u8	wscale;
	__u16	mss;
पूर्ण;

#पूर्ण_अगर /* _NF_SYNPROXY_H */
