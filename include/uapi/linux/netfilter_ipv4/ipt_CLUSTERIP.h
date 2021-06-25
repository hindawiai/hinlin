<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित _IPT_CLUSTERIP_H_target
#घोषणा _IPT_CLUSTERIP_H_target

#समावेश <linux/types.h>
#समावेश <linux/अगर_ether.h>

क्रमागत clusterip_hashmode अणु
    CLUSTERIP_HASHMODE_SIP = 0,
    CLUSTERIP_HASHMODE_SIP_SPT,
    CLUSTERIP_HASHMODE_SIP_SPT_DPT,
पूर्ण;

#घोषणा CLUSTERIP_HASHMODE_MAX CLUSTERIP_HASHMODE_SIP_SPT_DPT

#घोषणा CLUSTERIP_MAX_NODES 16

#घोषणा CLUSTERIP_FLAG_NEW 0x00000001

काष्ठा clusterip_config;

काष्ठा ipt_clusterip_tgt_info अणु

	__u32 flags;

	/* only relevant क्रम new ones */
	__u8 clustermac[ETH_ALEN];
	__u16 num_total_nodes;
	__u16 num_local_nodes;
	__u16 local_nodes[CLUSTERIP_MAX_NODES];
	__u32 hash_mode;
	__u32 hash_initval;

	/* Used पूर्णांकernally by the kernel */
	काष्ठा clusterip_config *config;
पूर्ण;

#पूर्ण_अगर /*_IPT_CLUSTERIP_H_target*/
