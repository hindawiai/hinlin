<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * linux/fs/nfs/callback.h
 *
 * Copyright (C) 2004 Trond Myklebust
 *
 * NFSv4 callback definitions
 */
#अगर_अघोषित __LINUX_FS_NFS_CALLBACK_H
#घोषणा __LINUX_FS_NFS_CALLBACK_H
#समावेश <linux/sunrpc/svc.h>

#घोषणा NFS4_CALLBACK 0x40000000
#घोषणा NFS4_CALLBACK_XDRSIZE 2048
#घोषणा NFS4_CALLBACK_बफ_मानE (1024 + NFS4_CALLBACK_XDRSIZE)

क्रमागत nfs4_callback_procnum अणु
	CB_शून्य = 0,
	CB_COMPOUND = 1,
पूर्ण;

क्रमागत nfs4_callback_opnum अणु
	OP_CB_GETATTR = 3,
	OP_CB_RECALL  = 4,
/* Callback operations new to NFSv4.1 */
	OP_CB_LAYOUTRECALL  = 5,
	OP_CB_NOTIFY        = 6,
	OP_CB_PUSH_DELEG    = 7,
	OP_CB_RECALL_ANY    = 8,
	OP_CB_RECALLABLE_OBJ_AVAIL = 9,
	OP_CB_RECALL_SLOT   = 10,
	OP_CB_SEQUENCE      = 11,
	OP_CB_WANTS_CANCELLED = 12,
	OP_CB_NOTIFY_LOCK   = 13,
	OP_CB_NOTIFY_DEVICEID = 14,
/* Callback operations new to NFSv4.2 */
	OP_CB_OFFLOAD = 15,
	OP_CB_ILLEGAL = 10044,
पूर्ण;

काष्ठा nfs4_slot;
काष्ठा cb_process_state अणु
	__be32			drc_status;
	काष्ठा nfs_client	*clp;
	काष्ठा nfs4_slot	*slot;
	u32			minorversion;
	काष्ठा net		*net;
पूर्ण;

काष्ठा cb_compound_hdr_arg अणु
	अचिन्हित पूर्णांक taglen;
	स्थिर अक्षर *tag;
	अचिन्हित पूर्णांक minorversion;
	अचिन्हित पूर्णांक cb_ident; /* v4.0 callback identअगरier */
	अचिन्हित nops;
पूर्ण;

काष्ठा cb_compound_hdr_res अणु
	__be32 *status;
	अचिन्हित पूर्णांक taglen;
	स्थिर अक्षर *tag;
	__be32 *nops;
पूर्ण;

काष्ठा cb_getattrargs अणु
	काष्ठा nfs_fh fh;
	uपूर्णांक32_t biपंचांगap[2];
पूर्ण;

काष्ठा cb_getattrres अणु
	__be32 status;
	uपूर्णांक32_t biपंचांगap[2];
	uपूर्णांक64_t size;
	uपूर्णांक64_t change_attr;
	काष्ठा बारpec64 स_समय;
	काष्ठा बारpec64 mसमय;
पूर्ण;

काष्ठा cb_recallargs अणु
	काष्ठा nfs_fh fh;
	nfs4_stateid stateid;
	uपूर्णांक32_t truncate;
पूर्ण;

#अगर defined(CONFIG_NFS_V4_1)

काष्ठा referring_call अणु
	uपूर्णांक32_t			rc_sequenceid;
	uपूर्णांक32_t			rc_slotid;
पूर्ण;

काष्ठा referring_call_list अणु
	काष्ठा nfs4_sessionid		rcl_sessionid;
	uपूर्णांक32_t			rcl_nrefcalls;
	काष्ठा referring_call 		*rcl_refcalls;
पूर्ण;

काष्ठा cb_sequenceargs अणु
	काष्ठा sockaddr			*csa_addr;
	काष्ठा nfs4_sessionid		csa_sessionid;
	uपूर्णांक32_t			csa_sequenceid;
	uपूर्णांक32_t			csa_slotid;
	uपूर्णांक32_t			csa_highestslotid;
	uपूर्णांक32_t			csa_cachethis;
	uपूर्णांक32_t			csa_nrclists;
	काष्ठा referring_call_list	*csa_rclists;
पूर्ण;

काष्ठा cb_sequenceres अणु
	__be32				csr_status;
	काष्ठा nfs4_sessionid		csr_sessionid;
	uपूर्णांक32_t			csr_sequenceid;
	uपूर्णांक32_t			csr_slotid;
	uपूर्णांक32_t			csr_highestslotid;
	uपूर्णांक32_t			csr_target_highestslotid;
पूर्ण;

बाह्य __be32 nfs4_callback_sequence(व्योम *argp, व्योम *resp,
				       काष्ठा cb_process_state *cps);

#घोषणा RCA4_TYPE_MASK_RDATA_DLG	0
#घोषणा RCA4_TYPE_MASK_WDATA_DLG	1
#घोषणा RCA4_TYPE_MASK_सूची_DLG         2
#घोषणा RCA4_TYPE_MASK_खाता_LAYOUT     3
#घोषणा RCA4_TYPE_MASK_BLK_LAYOUT      4
#घोषणा RCA4_TYPE_MASK_OBJ_LAYOUT_MIN  8
#घोषणा RCA4_TYPE_MASK_OBJ_LAYOUT_MAX  9
#घोषणा RCA4_TYPE_MASK_OTHER_LAYOUT_MIN 12
#घोषणा RCA4_TYPE_MASK_OTHER_LAYOUT_MAX 15
#घोषणा PNFS_FF_RCA4_TYPE_MASK_READ 16
#घोषणा PNFS_FF_RCA4_TYPE_MASK_RW 17
#घोषणा RCA4_TYPE_MASK_ALL 0x3f31f

काष्ठा cb_recallanyargs अणु
	uपूर्णांक32_t	craa_objs_to_keep;
	uपूर्णांक32_t	craa_type_mask;
पूर्ण;

बाह्य __be32 nfs4_callback_recallany(व्योम *argp, व्योम *resp,
					काष्ठा cb_process_state *cps);

काष्ठा cb_recallslotargs अणु
	uपूर्णांक32_t	crsa_target_highest_slotid;
पूर्ण;
बाह्य __be32 nfs4_callback_recallslot(व्योम *argp, व्योम *resp,
					 काष्ठा cb_process_state *cps);

काष्ठा cb_layoutrecallargs अणु
	uपूर्णांक32_t		cbl_recall_type;
	uपूर्णांक32_t		cbl_layout_type;
	uपूर्णांक32_t		cbl_layoutchanged;
	जोड़ अणु
		काष्ठा अणु
			काष्ठा nfs_fh		cbl_fh;
			काष्ठा pnfs_layout_range cbl_range;
			nfs4_stateid		cbl_stateid;
		पूर्ण;
		काष्ठा nfs_fsid		cbl_fsid;
	पूर्ण;
पूर्ण;

बाह्य __be32 nfs4_callback_layoutrecall(व्योम *argp, व्योम *resp,
		काष्ठा cb_process_state *cps);

काष्ठा cb_devicenotअगरyitem अणु
	uपूर्णांक32_t		cbd_notअगरy_type;
	uपूर्णांक32_t		cbd_layout_type;
	काष्ठा nfs4_deviceid	cbd_dev_id;
	uपूर्णांक32_t		cbd_immediate;
पूर्ण;

काष्ठा cb_devicenotअगरyargs अणु
	पूर्णांक				 ndevs;
	काष्ठा cb_devicenotअगरyitem	 *devs;
पूर्ण;

बाह्य __be32 nfs4_callback_devicenotअगरy(व्योम *argp, व्योम *resp,
		काष्ठा cb_process_state *cps);

काष्ठा cb_notअगरy_lock_args अणु
	काष्ठा nfs_fh			cbnl_fh;
	काष्ठा nfs_lowner		cbnl_owner;
	bool				cbnl_valid;
पूर्ण;

बाह्य __be32 nfs4_callback_notअगरy_lock(व्योम *argp, व्योम *resp,
					 काष्ठा cb_process_state *cps);
#पूर्ण_अगर /* CONFIG_NFS_V4_1 */
#अगर_घोषित CONFIG_NFS_V4_2
काष्ठा cb_offloadargs अणु
	काष्ठा nfs_fh		coa_fh;
	nfs4_stateid		coa_stateid;
	uपूर्णांक32_t		error;
	uपूर्णांक64_t		wr_count;
	काष्ठा nfs_ग_लिखोverf	wr_ग_लिखोverf;
पूर्ण;

बाह्य __be32 nfs4_callback_offload(व्योम *args, व्योम *dummy,
				    काष्ठा cb_process_state *cps);
#पूर्ण_अगर /* CONFIG_NFS_V4_2 */
बाह्य पूर्णांक check_gss_callback_principal(काष्ठा nfs_client *, काष्ठा svc_rqst *);
बाह्य __be32 nfs4_callback_getattr(व्योम *argp, व्योम *resp,
				    काष्ठा cb_process_state *cps);
बाह्य __be32 nfs4_callback_recall(व्योम *argp, व्योम *resp,
				   काष्ठा cb_process_state *cps);
#अगर IS_ENABLED(CONFIG_NFS_V4)
बाह्य पूर्णांक nfs_callback_up(u32 minorversion, काष्ठा rpc_xprt *xprt);
बाह्य व्योम nfs_callback_करोwn(पूर्णांक minorversion, काष्ठा net *net);
#पूर्ण_अगर /* CONFIG_NFS_V4 */
/*
 * nfs41: Callbacks are expected to not cause substantial latency,
 * so we limit their concurrency to 1 by setting up the maximum number
 * of slots क्रम the backchannel.
 */
#घोषणा NFS41_BC_MIN_CALLBACKS 1
#घोषणा NFS41_BC_MAX_CALLBACKS 1

#घोषणा NFS4_MIN_NR_CALLBACK_THREADS 1

बाह्य अचिन्हित पूर्णांक nfs_callback_set_tcpport;
बाह्य अचिन्हित लघु nfs_callback_nr_thपढ़ोs;

#पूर्ण_अगर /* __LINUX_FS_NFS_CALLBACK_H */
