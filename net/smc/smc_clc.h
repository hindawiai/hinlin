<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 *  Shared Memory Communications over RDMA (SMC-R) and RoCE
 *
 *  CLC (connection layer control) handshake over initial TCP socket to
 *  prepare क्रम RDMA traffic
 *
 *  Copyright IBM Corp. 2016
 *
 *  Author(s):  Ursula Braun <ubraun@linux.vnet.ibm.com>
 */

#अगर_अघोषित _SMC_CLC_H
#घोषणा _SMC_CLC_H

#समावेश <rdma/ib_verbs.h>

#समावेश "smc.h"

#घोषणा SMC_CLC_PROPOSAL	0x01
#घोषणा SMC_CLC_ACCEPT		0x02
#घोषणा SMC_CLC_CONFIRM		0x03
#घोषणा SMC_CLC_DECLINE		0x04

#घोषणा SMC_TYPE_R		0		/* SMC-R only		      */
#घोषणा SMC_TYPE_D		1		/* SMC-D only		      */
#घोषणा SMC_TYPE_N		2		/* neither SMC-R nor SMC-D    */
#घोषणा SMC_TYPE_B		3		/* SMC-R and SMC-D	      */
#घोषणा CLC_WAIT_TIME		(6 * HZ)	/* max. रुको समय on clcsock  */
#घोषणा CLC_WAIT_TIME_SHORT	HZ		/* लघु रुको समय on clcsock */
#घोषणा SMC_CLC_DECL_MEM	0x01010000  /* insufficient memory resources  */
#घोषणा SMC_CLC_DECL_TIMEOUT_CL	0x02010000  /* समयout w4 QP confirm link     */
#घोषणा SMC_CLC_DECL_TIMEOUT_AL	0x02020000  /* समयout w4 QP add link	      */
#घोषणा SMC_CLC_DECL_CNFERR	0x03000000  /* configuration error            */
#घोषणा SMC_CLC_DECL_PEERNOSMC	0x03010000  /* peer did not indicate SMC      */
#घोषणा SMC_CLC_DECL_IPSEC	0x03020000  /* IPsec usage		      */
#घोषणा SMC_CLC_DECL_NOSMCDEV	0x03030000  /* no SMC device found (R or D)   */
#घोषणा SMC_CLC_DECL_NOSMCDDEV	0x03030001  /* no SMC-D device found	      */
#घोषणा SMC_CLC_DECL_NOSMCRDEV	0x03030002  /* no SMC-R device found	      */
#घोषणा SMC_CLC_DECL_NOISM2SUPP	0x03030003  /* hardware has no ISMv2 support  */
#घोषणा SMC_CLC_DECL_NOV2EXT	0x03030004  /* peer sent no clc v2 extension  */
#घोषणा SMC_CLC_DECL_NOV2DEXT	0x03030005  /* peer sent no clc SMC-Dv2 ext.  */
#घोषणा SMC_CLC_DECL_NOSEID	0x03030006  /* peer sent no SEID	      */
#घोषणा SMC_CLC_DECL_NOSMCD2DEV	0x03030007  /* no SMC-Dv2 device found	      */
#घोषणा SMC_CLC_DECL_MODEUNSUPP	0x03040000  /* smc modes करो not match (R or D)*/
#घोषणा SMC_CLC_DECL_RMBE_EC	0x03050000  /* peer has eyecatcher in RMBE    */
#घोषणा SMC_CLC_DECL_OPTUNSUPP	0x03060000  /* fastखोलो sockopt not supported */
#घोषणा SMC_CLC_DECL_DIFFPREFIX	0x03070000  /* IP prefix / subnet mismatch    */
#घोषणा SMC_CLC_DECL_GETVLANERR	0x03080000  /* err to get vlan id of ip device*/
#घोषणा SMC_CLC_DECL_ISMVLANERR	0x03090000  /* err to reg vlan id on ism dev  */
#घोषणा SMC_CLC_DECL_NOACTLINK	0x030a0000  /* no active smc-r link in lgr    */
#घोषणा SMC_CLC_DECL_NOSRVLINK	0x030b0000  /* SMC-R link from srv not found  */
#घोषणा SMC_CLC_DECL_VERSMISMAT	0x030c0000  /* SMC version mismatch	      */
#घोषणा SMC_CLC_DECL_MAX_DMB	0x030d0000  /* SMC-D DMB limit exceeded       */
#घोषणा SMC_CLC_DECL_SYNCERR	0x04000000  /* synchronization error          */
#घोषणा SMC_CLC_DECL_PEERDECL	0x05000000  /* peer declined during handshake */
#घोषणा SMC_CLC_DECL_INTERR	0x09990000  /* पूर्णांकernal error		      */
#घोषणा SMC_CLC_DECL_ERR_RTOK	0x09990001  /*	 rtoken handling failed       */
#घोषणा SMC_CLC_DECL_ERR_RDYLNK	0x09990002  /*	 ib पढ़ोy link failed	      */
#घोषणा SMC_CLC_DECL_ERR_REGRMB	0x09990003  /*	 reg rmb failed		      */

#घोषणा SMC_FIRST_CONTACT_MASK	0b10	/* first contact bit within typev2 */

काष्ठा smc_clc_msg_hdr अणु	/* header1 of clc messages */
	u8 eyecatcher[4];	/* eye catcher */
	u8 type;		/* proposal / accept / confirm / decline */
	__be16 length;
#अगर defined(__BIG_ENDIAN_BITFIELD)
	u8 version : 4,
	   typev2  : 2,
	   typev1  : 2;
#या_अगर defined(__LITTLE_ENDIAN_BITFIELD)
	u8 typev1  : 2,
	   typev2  : 2,
	   version : 4;
#पूर्ण_अगर
पूर्ण __packed;			/* क्रमmat defined in RFC7609 */

काष्ठा smc_clc_msg_trail अणु	/* trailer of clc messages */
	u8 eyecatcher[4];
पूर्ण;

काष्ठा smc_clc_msg_local अणु	/* header2 of clc messages */
	u8 id_क्रम_peer[SMC_SYSTEMID_LEN]; /* unique प्रणाली id */
	u8 gid[16];		/* gid of ib_device port */
	u8 mac[6];		/* mac of ib_device port */
पूर्ण;

/* Struct would be 4 byte aligned, but it is used in an array that is sent
 * to peers and must conक्रमm to RFC7609, hence we need to use packed here.
 */
काष्ठा smc_clc_ipv6_prefix अणु
	काष्ठा in6_addr prefix;
	u8 prefix_len;
पूर्ण __packed;			/* क्रमmat defined in RFC7609 */

#अगर defined(__BIG_ENDIAN_BITFIELD)
काष्ठा smc_clc_v2_flag अणु
	u8 release : 4,
	   rsvd    : 3,
	   seid    : 1;
पूर्ण;
#या_अगर defined(__LITTLE_ENDIAN_BITFIELD)
काष्ठा smc_clc_v2_flag अणु
	u8 seid   : 1,
	rsvd      : 3,
	release   : 4;
पूर्ण;
#पूर्ण_अगर

काष्ठा smc_clnt_opts_area_hdr अणु
	u8 eid_cnt;		/* number of user defined EIDs */
	u8 ism_gid_cnt;		/* number of ISMv2 GIDs */
	u8 reserved1;
	काष्ठा smc_clc_v2_flag flag;
	u8 reserved2[2];
	__be16 smcd_v2_ext_offset; /* SMC-Dv2 Extension Offset */
पूर्ण;

काष्ठा smc_clc_smcd_gid_chid अणु
	__be64 gid;		/* ISM GID */
	__be16 chid;		/* ISMv2 CHID */
पूर्ण __packed;		/* क्रमmat defined in
			 * IBM Shared Memory Communications Version 2
			 * (https://www.ibm.com/support/pages/node/6326337)
			 */

काष्ठा smc_clc_v2_extension अणु
	काष्ठा smc_clnt_opts_area_hdr hdr;
	u8 roce[16];		/* RoCEv2 GID */
	u8 reserved[16];
	u8 user_eids[][SMC_MAX_EID_LEN];
पूर्ण;

काष्ठा smc_clc_msg_proposal_prefix अणु	/* prefix part of clc proposal message*/
	__be32 outgoing_subnet;	/* subnet mask */
	u8 prefix_len;		/* number of signअगरicant bits in mask */
	u8 reserved[2];
	u8 ipv6_prefixes_cnt;	/* number of IPv6 prefixes in prefix array */
पूर्ण __aligned(4);

काष्ठा smc_clc_msg_smcd अणु	/* SMC-D GID inक्रमmation */
	काष्ठा smc_clc_smcd_gid_chid ism; /* ISM native GID+CHID of requestor */
	__be16 v2_ext_offset;	/* SMC Version 2 Extension Offset */
	u8 reserved[28];
पूर्ण;

काष्ठा smc_clc_smcd_v2_extension अणु
	u8 प्रणाली_eid[SMC_MAX_EID_LEN];
	u8 reserved[16];
	काष्ठा smc_clc_smcd_gid_chid gidchid[];
पूर्ण;

काष्ठा smc_clc_msg_proposal अणु	/* clc proposal message sent by Linux */
	काष्ठा smc_clc_msg_hdr hdr;
	काष्ठा smc_clc_msg_local lcl;
	__be16 iparea_offset;	/* offset to IP address inक्रमmation area */
पूर्ण __aligned(4);

#घोषणा SMC_CLC_MAX_V6_PREFIX		8

काष्ठा smc_clc_msg_proposal_area अणु
	काष्ठा smc_clc_msg_proposal		pclc_base;
	काष्ठा smc_clc_msg_smcd			pclc_smcd;
	काष्ठा smc_clc_msg_proposal_prefix	pclc_prfx;
	काष्ठा smc_clc_ipv6_prefix	pclc_prfx_ipv6[SMC_CLC_MAX_V6_PREFIX];
	काष्ठा smc_clc_v2_extension		pclc_v2_ext;
	काष्ठा smc_clc_smcd_v2_extension	pclc_smcd_v2_ext;
	काष्ठा smc_clc_smcd_gid_chid		pclc_gidchids[SMC_MAX_ISM_DEVS];
	काष्ठा smc_clc_msg_trail		pclc_trl;
पूर्ण;

काष्ठा smcr_clc_msg_accept_confirm अणु	/* SMCR accept/confirm */
	काष्ठा smc_clc_msg_local lcl;
	u8 qpn[3];			/* QP number */
	__be32 rmb_rkey;		/* RMB rkey */
	u8 rmbe_idx;			/* Index of RMBE in RMB */
	__be32 rmbe_alert_token;	/* unique connection id */
 #अगर defined(__BIG_ENDIAN_BITFIELD)
	u8 rmbe_size : 4,		/* buf size (compressed) */
	   qp_mtu   : 4;		/* QP mtu */
#या_अगर defined(__LITTLE_ENDIAN_BITFIELD)
	u8 qp_mtu   : 4,
	   rmbe_size : 4;
#पूर्ण_अगर
	u8 reserved;
	__be64 rmb_dma_addr;	/* RMB भव address */
	u8 reserved2;
	u8 psn[3];		/* packet sequence number */
पूर्ण __packed;

काष्ठा smcd_clc_msg_accept_confirm_common अणु	/* SMCD accept/confirm */
	u64 gid;		/* Sender GID */
	u64 token;		/* DMB token */
	u8 dmbe_idx;		/* DMBE index */
#अगर defined(__BIG_ENDIAN_BITFIELD)
	u8 dmbe_size : 4,	/* buf size (compressed) */
	   reserved3 : 4;
#या_अगर defined(__LITTLE_ENDIAN_BITFIELD)
	u8 reserved3 : 4,
	   dmbe_size : 4;
#पूर्ण_अगर
	u16 reserved4;
	__be32 linkid;		/* Link identअगरier */
पूर्ण __packed;

#घोषणा SMC_CLC_OS_ZOS		1
#घोषणा SMC_CLC_OS_LINUX	2
#घोषणा SMC_CLC_OS_AIX		3

काष्ठा smc_clc_first_contact_ext अणु
	u8 reserved1;
#अगर defined(__BIG_ENDIAN_BITFIELD)
	u8 os_type : 4,
	   release : 4;
#या_अगर defined(__LITTLE_ENDIAN_BITFIELD)
	u8 release : 4,
	   os_type : 4;
#पूर्ण_अगर
	u8 reserved2[2];
	u8 hostname[SMC_MAX_HOSTNAME_LEN];
पूर्ण;

काष्ठा smc_clc_msg_accept_confirm अणु	/* clc accept / confirm message */
	काष्ठा smc_clc_msg_hdr hdr;
	जोड़ अणु
		काष्ठा smcr_clc_msg_accept_confirm r0; /* SMC-R */
		काष्ठा अणु /* SMC-D */
			काष्ठा smcd_clc_msg_accept_confirm_common d0;
			u32 reserved5[3];
		पूर्ण;
	पूर्ण;
पूर्ण __packed;			/* क्रमmat defined in RFC7609 */

काष्ठा smc_clc_msg_accept_confirm_v2 अणु	/* clc accept / confirm message */
	काष्ठा smc_clc_msg_hdr hdr;
	जोड़ अणु
		काष्ठा smcr_clc_msg_accept_confirm r0; /* SMC-R */
		काष्ठा अणु /* SMC-D */
			काष्ठा smcd_clc_msg_accept_confirm_common d0;
			__be16 chid;
			u8 eid[SMC_MAX_EID_LEN];
			u8 reserved5[8];
		पूर्ण;
	पूर्ण;
पूर्ण;

काष्ठा smc_clc_msg_decline अणु	/* clc decline message */
	काष्ठा smc_clc_msg_hdr hdr;
	u8 id_क्रम_peer[SMC_SYSTEMID_LEN]; /* sender peer_id */
	__be32 peer_diagnosis;	/* diagnosis inक्रमmation */
#अगर defined(__BIG_ENDIAN_BITFIELD)
	u8 os_type  : 4,
	   reserved : 4;
#या_अगर defined(__LITTLE_ENDIAN_BITFIELD)
	u8 reserved : 4,
	   os_type  : 4;
#पूर्ण_अगर
	u8 reserved2[3];
	काष्ठा smc_clc_msg_trail trl; /* eye catcher "SMCD" or "SMCR" EBCDIC */
पूर्ण __aligned(4);

/* determine start of the prefix area within the proposal message */
अटल अंतरभूत काष्ठा smc_clc_msg_proposal_prefix *
smc_clc_proposal_get_prefix(काष्ठा smc_clc_msg_proposal *pclc)
अणु
	वापस (काष्ठा smc_clc_msg_proposal_prefix *)
	       ((u8 *)pclc + माप(*pclc) + ntohs(pclc->iparea_offset));
पूर्ण

अटल अंतरभूत bool smcr_indicated(पूर्णांक smc_type)
अणु
	वापस smc_type == SMC_TYPE_R || smc_type == SMC_TYPE_B;
पूर्ण

अटल अंतरभूत bool smcd_indicated(पूर्णांक smc_type)
अणु
	वापस smc_type == SMC_TYPE_D || smc_type == SMC_TYPE_B;
पूर्ण

/* get SMC-D info from proposal message */
अटल अंतरभूत काष्ठा smc_clc_msg_smcd *
smc_get_clc_msg_smcd(काष्ठा smc_clc_msg_proposal *prop)
अणु
	अगर (smcd_indicated(prop->hdr.typev1) &&
	    ntohs(prop->iparea_offset) != माप(काष्ठा smc_clc_msg_smcd))
		वापस शून्य;

	वापस (काष्ठा smc_clc_msg_smcd *)(prop + 1);
पूर्ण

अटल अंतरभूत काष्ठा smc_clc_v2_extension *
smc_get_clc_v2_ext(काष्ठा smc_clc_msg_proposal *prop)
अणु
	काष्ठा smc_clc_msg_smcd *prop_smcd = smc_get_clc_msg_smcd(prop);

	अगर (!prop_smcd || !ntohs(prop_smcd->v2_ext_offset))
		वापस शून्य;

	वापस (काष्ठा smc_clc_v2_extension *)
	       ((u8 *)prop_smcd +
	       दुरत्व(काष्ठा smc_clc_msg_smcd, v2_ext_offset) +
	       माप(prop_smcd->v2_ext_offset) +
	       ntohs(prop_smcd->v2_ext_offset));
पूर्ण

अटल अंतरभूत काष्ठा smc_clc_smcd_v2_extension *
smc_get_clc_smcd_v2_ext(काष्ठा smc_clc_v2_extension *prop_v2ext)
अणु
	अगर (!prop_v2ext)
		वापस शून्य;
	अगर (!ntohs(prop_v2ext->hdr.smcd_v2_ext_offset))
		वापस शून्य;

	वापस (काष्ठा smc_clc_smcd_v2_extension *)
		((u8 *)prop_v2ext +
		 दुरत्व(काष्ठा smc_clc_v2_extension, hdr) +
		 दुरत्व(काष्ठा smc_clnt_opts_area_hdr, smcd_v2_ext_offset) +
		 माप(prop_v2ext->hdr.smcd_v2_ext_offset) +
		 ntohs(prop_v2ext->hdr.smcd_v2_ext_offset));
पूर्ण

काष्ठा smcd_dev;
काष्ठा smc_init_info;

पूर्णांक smc_clc_prfx_match(काष्ठा socket *clcsock,
		       काष्ठा smc_clc_msg_proposal_prefix *prop);
पूर्णांक smc_clc_रुको_msg(काष्ठा smc_sock *smc, व्योम *buf, पूर्णांक buflen,
		     u8 expected_type, अचिन्हित दीर्घ समयout);
पूर्णांक smc_clc_send_decline(काष्ठा smc_sock *smc, u32 peer_diag_info, u8 version);
पूर्णांक smc_clc_send_proposal(काष्ठा smc_sock *smc, काष्ठा smc_init_info *ini);
पूर्णांक smc_clc_send_confirm(काष्ठा smc_sock *smc, bool clnt_first_contact,
			 u8 version);
पूर्णांक smc_clc_send_accept(काष्ठा smc_sock *smc, bool srv_first_contact,
			u8 version);
व्योम smc_clc_init(व्योम) __init;
व्योम smc_clc_get_hostname(u8 **host);

#पूर्ण_अगर
