<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright(c) 2009 Intel Corporation. All rights reserved.
 *
 * Maपूर्णांकained at www.Open-FCoE.org
 */

#अगर_अघोषित _FC_LIBFC_H_
#घोषणा _FC_LIBFC_H_

#घोषणा FC_LIBFC_LOGGING 0x01 /* General logging, not categorized */
#घोषणा FC_LPORT_LOGGING 0x02 /* lport layer logging */
#घोषणा FC_DISC_LOGGING	 0x04 /* discovery layer logging */
#घोषणा FC_RPORT_LOGGING 0x08 /* rport layer logging */
#घोषणा FC_FCP_LOGGING	 0x10 /* I/O path logging */
#घोषणा FC_EM_LOGGING	 0x20 /* Exchange Manager logging */
#घोषणा FC_EXCH_LOGGING	 0x40 /* Exchange/Sequence logging */
#घोषणा FC_SCSI_LOGGING	 0x80 /* SCSI logging (mostly error handling) */

बाह्य अचिन्हित पूर्णांक fc_debug_logging;

#घोषणा FC_CHECK_LOGGING(LEVEL, CMD)			\
	करो अणु						\
		अगर (unlikely(fc_debug_logging & LEVEL))	\
			करो अणु				\
				CMD;			\
			पूर्ण जबतक (0);			\
	पूर्ण जबतक (0)

#घोषणा FC_LIBFC_DBG(fmt, args...)					\
	FC_CHECK_LOGGING(FC_LIBFC_LOGGING,				\
			 pr_info("libfc: " fmt, ##args))

#घोषणा FC_LPORT_DBG(lport, fmt, args...)				\
	FC_CHECK_LOGGING(FC_LPORT_LOGGING,				\
			 pr_info("host%u: lport %6.6x: " fmt,		\
				 (lport)->host->host_no,		\
				 (lport)->port_id, ##args))

#घोषणा FC_DISC_DBG(disc, fmt, args...)					\
	FC_CHECK_LOGGING(FC_DISC_LOGGING,				\
			 pr_info("host%u: disc: " fmt,			\
				 fc_disc_lport(disc)->host->host_no,	\
				 ##args))

#घोषणा FC_RPORT_ID_DBG(lport, port_id, fmt, args...)			\
	FC_CHECK_LOGGING(FC_RPORT_LOGGING,				\
			 pr_info("host%u: rport %6.6x: " fmt,		\
				 (lport)->host->host_no,		\
				 (port_id), ##args))

#घोषणा FC_RPORT_DBG(rdata, fmt, args...)				\
	FC_RPORT_ID_DBG((rdata)->local_port, (rdata)->ids.port_id, fmt, ##args)

#घोषणा FC_FCP_DBG(pkt, fmt, args...)					\
	FC_CHECK_LOGGING(FC_FCP_LOGGING,				\
	अणु								\
		अगर ((pkt)->seq_ptr) अणु					\
			काष्ठा fc_exch *_ep = शून्य;			\
			_ep = fc_seq_exch((pkt)->seq_ptr);		\
			pr_info("host%u: fcp: %6.6x: "			\
				"xid %04x-%04x: " fmt,			\
				(pkt)->lp->host->host_no,		\
				(pkt)->rport->port_id,			\
				(_ep)->oxid, (_ep)->rxid, ##args);	\
		पूर्ण अन्यथा अणु						\
			pr_info("host%u: fcp: %6.6x: " fmt,		\
				(pkt)->lp->host->host_no,		\
				(pkt)->rport->port_id, ##args);		\
		पूर्ण							\
	पूर्ण)

#घोषणा FC_EXCH_DBG(exch, fmt, args...)					\
	FC_CHECK_LOGGING(FC_EXCH_LOGGING,				\
			 pr_info("host%u: xid %4x: " fmt,		\
				 (exch)->lp->host->host_no,		\
				 exch->xid, ##args))

#घोषणा FC_SCSI_DBG(lport, fmt, args...)				\
	FC_CHECK_LOGGING(FC_SCSI_LOGGING,				\
			 pr_info("host%u: scsi: " fmt,			\
				 (lport)->host->host_no, ##args))

/*
 * FC-4 Providers.
 */
बाह्य काष्ठा fc4_prov *fc_active_prov[];	/* providers without recv */
बाह्य काष्ठा fc4_prov *fc_passive_prov[];	/* providers with recv */
बाह्य काष्ठा mutex fc_prov_mutex;		/* lock over table changes */

बाह्य काष्ठा fc4_prov fc_rport_t0_prov;	/* type 0 provider */
बाह्य काष्ठा fc4_prov fc_lport_els_prov;	/* ELS provider */
बाह्य काष्ठा fc4_prov fc_rport_fcp_init;	/* FCP initiator provider */

/*
 * Set up direct-data placement क्रम this I/O request
 */
व्योम fc_fcp_ddp_setup(काष्ठा fc_fcp_pkt *fsp, u16 xid);
व्योम fc_fcp_ddp_करोne(काष्ठा fc_fcp_pkt *fsp);

/*
 * Module setup functions
 */
पूर्णांक fc_setup_exch_mgr(व्योम);
व्योम fc_destroy_exch_mgr(व्योम);
पूर्णांक fc_setup_rport(व्योम);
व्योम fc_destroy_rport(व्योम);
पूर्णांक fc_setup_fcp(व्योम);
व्योम fc_destroy_fcp(व्योम);

/*
 * Internal libfc functions
 */
स्थिर अक्षर *fc_els_resp_type(काष्ठा fc_frame *);
बाह्य व्योम fc_fc4_add_lport(काष्ठा fc_lport *);
बाह्य व्योम fc_fc4_del_lport(काष्ठा fc_lport *);
बाह्य व्योम fc_fc4_conf_lport_params(काष्ठा fc_lport *, क्रमागत fc_fh_type);

/*
 * Copies a buffer पूर्णांकo an sg list
 */
u32 fc_copy_buffer_to_sglist(व्योम *buf, माप_प्रकार len,
			     काष्ठा scatterlist *sg,
			     u32 *nents, माप_प्रकार *offset,
			     u32 *crc);

#पूर्ण_अगर /* _FC_LIBFC_H_ */
