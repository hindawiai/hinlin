<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/*
 * Copyright(c) 2007 Intel Corporation. All rights reserved.
 *
 * Maपूर्णांकained at www.Open-FCoE.org
 */

#अगर_अघोषित _FC_NS_H_
#घोषणा	_FC_NS_H_

#समावेश <linux/types.h>

/*
 * Fibre Channel Services - Name Service (dNS)
 * From T11.org FC-GS-2 Rev 5.3 November 1998.
 */

/*
 * Common-transport sub-type क्रम Name Server.
 */
#घोषणा	FC_NS_SUBTYPE	    2	/* fs_ct_hdr.ct_fs_subtype */

/*
 * Name server Requests.
 * Note:  this is an incomplete list, some unused requests are omitted.
 */
क्रमागत fc_ns_req अणु
	FC_NS_GA_NXT =	0x0100,		/* get all next */
	FC_NS_GI_A =	0x0101,		/* get identअगरiers - scope */
	FC_NS_GPN_ID =	0x0112,		/* get port name by ID */
	FC_NS_GNN_ID =	0x0113,		/* get node name by ID */
	FC_NS_GSPN_ID = 0x0118,		/* get symbolic port name */
	FC_NS_GID_PN =	0x0121,		/* get ID क्रम port name */
	FC_NS_GID_NN =	0x0131,		/* get IDs क्रम node name */
	FC_NS_GID_FT =	0x0171,		/* get IDs by FC4 type */
	FC_NS_GPN_FT =	0x0172,		/* get port names by FC4 type */
	FC_NS_GID_PT =	0x01a1,		/* get IDs by port type */
	FC_NS_RPN_ID =	0x0212,		/* reg port name क्रम ID */
	FC_NS_RNN_ID =	0x0213,		/* reg node name क्रम ID */
	FC_NS_RFT_ID =	0x0217,		/* reg FC4 type क्रम ID */
	FC_NS_RSPN_ID =	0x0218,		/* reg symbolic port name */
	FC_NS_RFF_ID =	0x021f,		/* reg FC4 Features क्रम ID */
	FC_NS_RSNN_NN =	0x0239,		/* reg symbolic node name */
पूर्ण;

/*
 * Port type values.
 */
क्रमागत fc_ns_pt अणु
	FC_NS_UNID_PORT = 0x00,	/* unidentअगरied */
	FC_NS_N_PORT =	0x01,	/* N port */
	FC_NS_NL_PORT =	0x02,	/* NL port */
	FC_NS_FNL_PORT = 0x03,	/* F/NL port */
	FC_NS_NX_PORT =	0x7f,	/* Nx port */
	FC_NS_F_PORT =	0x81,	/* F port */
	FC_NS_FL_PORT =	0x82,	/* FL port */
	FC_NS_E_PORT =	0x84,	/* E port */
	FC_NS_B_PORT =	0x85,	/* B port */
पूर्ण;

/*
 * Port type object.
 */
काष्ठा fc_ns_pt_obj अणु
	__u8		pt_type;
पूर्ण;

/*
 * Port ID object
 */
काष्ठा fc_ns_fid अणु
	__u8		fp_flags;	/* flags क्रम responses only */
	__u8		fp_fid[3];
पूर्ण;

/*
 * fp_flags in port ID object, क्रम responses only.
 */
#घोषणा	FC_NS_FID_LAST	0x80		/* last object */

/*
 * FC4-types object.
 */
#घोषणा	FC_NS_TYPES	256	/* number of possible FC-4 types */
#घोषणा	FC_NS_BPW	32	/* bits per word in biपंचांगap */

काष्ठा fc_ns_fts अणु
	__be32	ff_type_map[FC_NS_TYPES / FC_NS_BPW]; /* biपंचांगap of FC-4 types */
पूर्ण;

/*
 * FC4-features object.
 */
काष्ठा fc_ns_ff	अणु
	__be32	fd_feat[FC_NS_TYPES * 4 / FC_NS_BPW]; /* 4-bits per FC-type */
पूर्ण;

/*
 * GID_PT request.
 */
काष्ठा fc_ns_gid_pt अणु
	__u8		fn_pt_type;
	__u8		fn_करोमुख्य_id_scope;
	__u8		fn_area_id_scope;
	__u8		fn_resvd;
पूर्ण;

/*
 * GID_FT or GPN_FT request.
 */
काष्ठा fc_ns_gid_ft अणु
	__u8		fn_resvd;
	__u8		fn_करोमुख्य_id_scope;
	__u8		fn_area_id_scope;
	__u8		fn_fc4_type;
पूर्ण;

/*
 * GPN_FT response.
 */
काष्ठा fc_gpn_ft_resp अणु
	__u8		fp_flags;	/* see fp_flags definitions above */
	__u8		fp_fid[3];	/* port ID */
	__be32		fp_resvd;
	__be64		fp_wwpn;	/* port name */
पूर्ण;

/*
 * GID_PN request
 */
काष्ठा fc_ns_gid_pn अणु
	__be64     fn_wwpn;    /* port name */
पूर्ण;

/*
 * GID_PN response or GSPN_ID request
 */
काष्ठा fc_gid_pn_resp अणु
	__u8      fp_resvd;
	__u8      fp_fid[3];     /* port ID */
पूर्ण;

/*
 * GSPN_ID response
 */
काष्ठा fc_gspn_resp अणु
	__u8	fp_name_len;
	अक्षर	fp_name[];
पूर्ण;

/*
 * RFT_ID request - रेजिस्टर FC-4 types क्रम ID.
 */
काष्ठा fc_ns_rft_id अणु
	काष्ठा fc_ns_fid fr_fid;	/* port ID object */
	काष्ठा fc_ns_fts fr_fts;	/* FC-4 types object */
पूर्ण;

/*
 * RPN_ID request - रेजिस्टर port name क्रम ID.
 * RNN_ID request - रेजिस्टर node name क्रम ID.
 */
काष्ठा fc_ns_rn_id अणु
	काष्ठा fc_ns_fid fr_fid;	/* port ID object */
	__be64		fr_wwn;		/* node name or port name */
पूर्ण __attribute__((__packed__));

/*
 * RSNN_NN request - रेजिस्टर symbolic node name
 */
काष्ठा fc_ns_rsnn अणु
	__be64		fr_wwn;		/* node name */
	__u8		fr_name_len;
	अक्षर		fr_name[];
पूर्ण __attribute__((__packed__));

/*
 * RSPN_ID request - रेजिस्टर symbolic port name
 */
काष्ठा fc_ns_rspn अणु
	काष्ठा fc_ns_fid fr_fid;	/* port ID object */
	__u8		fr_name_len;
	अक्षर		fr_name[];
पूर्ण __attribute__((__packed__));

/*
 * RFF_ID request - रेजिस्टर FC-4 Features क्रम ID.
 */
काष्ठा fc_ns_rff_id अणु
	काष्ठा fc_ns_fid fr_fid;	/* port ID object */
	__u8		fr_resvd[2];
	__u8		fr_feat;	/* FC-4 Feature bits */
	__u8		fr_type;	/* FC-4 type */
पूर्ण __attribute__((__packed__));

#पूर्ण_अगर /* _FC_NS_H_ */
