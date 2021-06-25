<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2016 Avago Technologies.  All rights reserved.
 */
#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt
#समावेश <linux/module.h>
#समावेश <linux/parser.h>
#समावेश <uapi/scsi/fc/fc_fs.h>

#समावेश "../host/nvme.h"
#समावेश "../target/nvmet.h"
#समावेश <linux/nvme-fc-driver.h>
#समावेश <linux/nvme-fc.h>


क्रमागत अणु
	NVMF_OPT_ERR		= 0,
	NVMF_OPT_WWNN		= 1 << 0,
	NVMF_OPT_WWPN		= 1 << 1,
	NVMF_OPT_ROLES		= 1 << 2,
	NVMF_OPT_FCADDR		= 1 << 3,
	NVMF_OPT_LPWWNN		= 1 << 4,
	NVMF_OPT_LPWWPN		= 1 << 5,
पूर्ण;

काष्ठा fcloop_ctrl_options अणु
	पूर्णांक			mask;
	u64			wwnn;
	u64			wwpn;
	u32			roles;
	u32			fcaddr;
	u64			lpwwnn;
	u64			lpwwpn;
पूर्ण;

अटल स्थिर match_table_t opt_tokens = अणु
	अणु NVMF_OPT_WWNN,	"wwnn=%s"	पूर्ण,
	अणु NVMF_OPT_WWPN,	"wwpn=%s"	पूर्ण,
	अणु NVMF_OPT_ROLES,	"roles=%d"	पूर्ण,
	अणु NVMF_OPT_FCADDR,	"fcaddr=%x"	पूर्ण,
	अणु NVMF_OPT_LPWWNN,	"lpwwnn=%s"	पूर्ण,
	अणु NVMF_OPT_LPWWPN,	"lpwwpn=%s"	पूर्ण,
	अणु NVMF_OPT_ERR,		शून्य		पूर्ण
पूर्ण;

अटल पूर्णांक fcloop_verअगरy_addr(substring_t *s)
अणु
	माप_प्रकार blen = s->to - s->from + 1;

	अगर (strnlen(s->from, blen) != NVME_FC_TRADDR_HEXNAMELEN + 2 ||
	    म_भेदन(s->from, "0x", 2))
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक
fcloop_parse_options(काष्ठा fcloop_ctrl_options *opts,
		स्थिर अक्षर *buf)
अणु
	substring_t args[MAX_OPT_ARGS];
	अक्षर *options, *o, *p;
	पूर्णांक token, ret = 0;
	u64 token64;

	options = o = kstrdup(buf, GFP_KERNEL);
	अगर (!options)
		वापस -ENOMEM;

	जबतक ((p = strsep(&o, ",\n")) != शून्य) अणु
		अगर (!*p)
			जारी;

		token = match_token(p, opt_tokens, args);
		opts->mask |= token;
		चयन (token) अणु
		हाल NVMF_OPT_WWNN:
			अगर (fcloop_verअगरy_addr(args) ||
			    match_u64(args, &token64)) अणु
				ret = -EINVAL;
				जाओ out_मुक्त_options;
			पूर्ण
			opts->wwnn = token64;
			अवरोध;
		हाल NVMF_OPT_WWPN:
			अगर (fcloop_verअगरy_addr(args) ||
			    match_u64(args, &token64)) अणु
				ret = -EINVAL;
				जाओ out_मुक्त_options;
			पूर्ण
			opts->wwpn = token64;
			अवरोध;
		हाल NVMF_OPT_ROLES:
			अगर (match_पूर्णांक(args, &token)) अणु
				ret = -EINVAL;
				जाओ out_मुक्त_options;
			पूर्ण
			opts->roles = token;
			अवरोध;
		हाल NVMF_OPT_FCADDR:
			अगर (match_hex(args, &token)) अणु
				ret = -EINVAL;
				जाओ out_मुक्त_options;
			पूर्ण
			opts->fcaddr = token;
			अवरोध;
		हाल NVMF_OPT_LPWWNN:
			अगर (fcloop_verअगरy_addr(args) ||
			    match_u64(args, &token64)) अणु
				ret = -EINVAL;
				जाओ out_मुक्त_options;
			पूर्ण
			opts->lpwwnn = token64;
			अवरोध;
		हाल NVMF_OPT_LPWWPN:
			अगर (fcloop_verअगरy_addr(args) ||
			    match_u64(args, &token64)) अणु
				ret = -EINVAL;
				जाओ out_मुक्त_options;
			पूर्ण
			opts->lpwwpn = token64;
			अवरोध;
		शेष:
			pr_warn("unknown parameter or missing value '%s'\n", p);
			ret = -EINVAL;
			जाओ out_मुक्त_options;
		पूर्ण
	पूर्ण

out_मुक्त_options:
	kमुक्त(options);
	वापस ret;
पूर्ण


अटल पूर्णांक
fcloop_parse_nm_options(काष्ठा device *dev, u64 *nname, u64 *pname,
		स्थिर अक्षर *buf)
अणु
	substring_t args[MAX_OPT_ARGS];
	अक्षर *options, *o, *p;
	पूर्णांक token, ret = 0;
	u64 token64;

	*nname = -1;
	*pname = -1;

	options = o = kstrdup(buf, GFP_KERNEL);
	अगर (!options)
		वापस -ENOMEM;

	जबतक ((p = strsep(&o, ",\n")) != शून्य) अणु
		अगर (!*p)
			जारी;

		token = match_token(p, opt_tokens, args);
		चयन (token) अणु
		हाल NVMF_OPT_WWNN:
			अगर (fcloop_verअगरy_addr(args) ||
			    match_u64(args, &token64)) अणु
				ret = -EINVAL;
				जाओ out_मुक्त_options;
			पूर्ण
			*nname = token64;
			अवरोध;
		हाल NVMF_OPT_WWPN:
			अगर (fcloop_verअगरy_addr(args) ||
			    match_u64(args, &token64)) अणु
				ret = -EINVAL;
				जाओ out_मुक्त_options;
			पूर्ण
			*pname = token64;
			अवरोध;
		शेष:
			pr_warn("unknown parameter or missing value '%s'\n", p);
			ret = -EINVAL;
			जाओ out_मुक्त_options;
		पूर्ण
	पूर्ण

out_मुक्त_options:
	kमुक्त(options);

	अगर (!ret) अणु
		अगर (*nname == -1)
			वापस -EINVAL;
		अगर (*pname == -1)
			वापस -EINVAL;
	पूर्ण

	वापस ret;
पूर्ण


#घोषणा LPORT_OPTS	(NVMF_OPT_WWNN | NVMF_OPT_WWPN)

#घोषणा RPORT_OPTS	(NVMF_OPT_WWNN | NVMF_OPT_WWPN |  \
			 NVMF_OPT_LPWWNN | NVMF_OPT_LPWWPN)

#घोषणा TGTPORT_OPTS	(NVMF_OPT_WWNN | NVMF_OPT_WWPN)


अटल DEFINE_SPINLOCK(fcloop_lock);
अटल LIST_HEAD(fcloop_lports);
अटल LIST_HEAD(fcloop_nports);

काष्ठा fcloop_lport अणु
	काष्ठा nvme_fc_local_port *localport;
	काष्ठा list_head lport_list;
	काष्ठा completion unreg_करोne;
पूर्ण;

काष्ठा fcloop_lport_priv अणु
	काष्ठा fcloop_lport *lport;
पूर्ण;

काष्ठा fcloop_rport अणु
	काष्ठा nvme_fc_remote_port	*remoteport;
	काष्ठा nvmet_fc_target_port	*targetport;
	काष्ठा fcloop_nport		*nport;
	काष्ठा fcloop_lport		*lport;
	spinlock_t			lock;
	काष्ठा list_head		ls_list;
	काष्ठा work_काष्ठा		ls_work;
पूर्ण;

काष्ठा fcloop_tport अणु
	काष्ठा nvmet_fc_target_port	*targetport;
	काष्ठा nvme_fc_remote_port	*remoteport;
	काष्ठा fcloop_nport		*nport;
	काष्ठा fcloop_lport		*lport;
	spinlock_t			lock;
	काष्ठा list_head		ls_list;
	काष्ठा work_काष्ठा		ls_work;
पूर्ण;

काष्ठा fcloop_nport अणु
	काष्ठा fcloop_rport *rport;
	काष्ठा fcloop_tport *tport;
	काष्ठा fcloop_lport *lport;
	काष्ठा list_head nport_list;
	काष्ठा kref ref;
	u64 node_name;
	u64 port_name;
	u32 port_role;
	u32 port_id;
पूर्ण;

काष्ठा fcloop_lsreq अणु
	काष्ठा nvmefc_ls_req		*lsreq;
	काष्ठा nvmefc_ls_rsp		ls_rsp;
	पूर्णांक				lsdir;	/* H2T or T2H */
	पूर्णांक				status;
	काष्ठा list_head		ls_list; /* fcloop_rport->ls_list */
पूर्ण;

काष्ठा fcloop_rscn अणु
	काष्ठा fcloop_tport		*tport;
	काष्ठा work_काष्ठा		work;
पूर्ण;

क्रमागत अणु
	INI_IO_START		= 0,
	INI_IO_ACTIVE		= 1,
	INI_IO_ABORTED		= 2,
	INI_IO_COMPLETED	= 3,
पूर्ण;

काष्ठा fcloop_fcpreq अणु
	काष्ठा fcloop_tport		*tport;
	काष्ठा nvmefc_fcp_req		*fcpreq;
	spinlock_t			reqlock;
	u16				status;
	u32				inistate;
	bool				active;
	bool				पातed;
	काष्ठा kref			ref;
	काष्ठा work_काष्ठा		fcp_rcv_work;
	काष्ठा work_काष्ठा		पात_rcv_work;
	काष्ठा work_काष्ठा		tio_करोne_work;
	काष्ठा nvmefc_tgt_fcp_req	tgt_fcp_req;
पूर्ण;

काष्ठा fcloop_ini_fcpreq अणु
	काष्ठा nvmefc_fcp_req		*fcpreq;
	काष्ठा fcloop_fcpreq		*tfcp_req;
	spinlock_t			inilock;
पूर्ण;

अटल अंतरभूत काष्ठा fcloop_lsreq *
ls_rsp_to_lsreq(काष्ठा nvmefc_ls_rsp *lsrsp)
अणु
	वापस container_of(lsrsp, काष्ठा fcloop_lsreq, ls_rsp);
पूर्ण

अटल अंतरभूत काष्ठा fcloop_fcpreq *
tgt_fcp_req_to_fcpreq(काष्ठा nvmefc_tgt_fcp_req *tgt_fcpreq)
अणु
	वापस container_of(tgt_fcpreq, काष्ठा fcloop_fcpreq, tgt_fcp_req);
पूर्ण


अटल पूर्णांक
fcloop_create_queue(काष्ठा nvme_fc_local_port *localport,
			अचिन्हित पूर्णांक qidx, u16 qsize,
			व्योम **handle)
अणु
	*handle = localport;
	वापस 0;
पूर्ण

अटल व्योम
fcloop_delete_queue(काष्ठा nvme_fc_local_port *localport,
			अचिन्हित पूर्णांक idx, व्योम *handle)
अणु
पूर्ण

अटल व्योम
fcloop_rport_lsrqst_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा fcloop_rport *rport =
		container_of(work, काष्ठा fcloop_rport, ls_work);
	काष्ठा fcloop_lsreq *tls_req;

	spin_lock(&rport->lock);
	क्रम (;;) अणु
		tls_req = list_first_entry_or_null(&rport->ls_list,
				काष्ठा fcloop_lsreq, ls_list);
		अगर (!tls_req)
			अवरोध;

		list_del(&tls_req->ls_list);
		spin_unlock(&rport->lock);

		tls_req->lsreq->करोne(tls_req->lsreq, tls_req->status);
		/*
		 * callee may मुक्त memory containing tls_req.
		 * करो not reference lsreq after this.
		 */

		spin_lock(&rport->lock);
	पूर्ण
	spin_unlock(&rport->lock);
पूर्ण

अटल पूर्णांक
fcloop_h2t_ls_req(काष्ठा nvme_fc_local_port *localport,
			काष्ठा nvme_fc_remote_port *remoteport,
			काष्ठा nvmefc_ls_req *lsreq)
अणु
	काष्ठा fcloop_lsreq *tls_req = lsreq->निजी;
	काष्ठा fcloop_rport *rport = remoteport->निजी;
	पूर्णांक ret = 0;

	tls_req->lsreq = lsreq;
	INIT_LIST_HEAD(&tls_req->ls_list);

	अगर (!rport->targetport) अणु
		tls_req->status = -ECONNREFUSED;
		spin_lock(&rport->lock);
		list_add_tail(&rport->ls_list, &tls_req->ls_list);
		spin_unlock(&rport->lock);
		schedule_work(&rport->ls_work);
		वापस ret;
	पूर्ण

	tls_req->status = 0;
	ret = nvmet_fc_rcv_ls_req(rport->targetport, rport,
				  &tls_req->ls_rsp,
				  lsreq->rqstaddr, lsreq->rqstlen);

	वापस ret;
पूर्ण

अटल पूर्णांक
fcloop_h2t_xmt_ls_rsp(काष्ठा nvmet_fc_target_port *targetport,
			काष्ठा nvmefc_ls_rsp *lsrsp)
अणु
	काष्ठा fcloop_lsreq *tls_req = ls_rsp_to_lsreq(lsrsp);
	काष्ठा nvmefc_ls_req *lsreq = tls_req->lsreq;
	काष्ठा fcloop_tport *tport = targetport->निजी;
	काष्ठा nvme_fc_remote_port *remoteport = tport->remoteport;
	काष्ठा fcloop_rport *rport;

	स_नकल(lsreq->rspaddr, lsrsp->rspbuf,
		((lsreq->rsplen < lsrsp->rsplen) ?
				lsreq->rsplen : lsrsp->rsplen));

	lsrsp->करोne(lsrsp);

	अगर (remoteport) अणु
		rport = remoteport->निजी;
		spin_lock(&rport->lock);
		list_add_tail(&rport->ls_list, &tls_req->ls_list);
		spin_unlock(&rport->lock);
		schedule_work(&rport->ls_work);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम
fcloop_tport_lsrqst_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा fcloop_tport *tport =
		container_of(work, काष्ठा fcloop_tport, ls_work);
	काष्ठा fcloop_lsreq *tls_req;

	spin_lock(&tport->lock);
	क्रम (;;) अणु
		tls_req = list_first_entry_or_null(&tport->ls_list,
				काष्ठा fcloop_lsreq, ls_list);
		अगर (!tls_req)
			अवरोध;

		list_del(&tls_req->ls_list);
		spin_unlock(&tport->lock);

		tls_req->lsreq->करोne(tls_req->lsreq, tls_req->status);
		/*
		 * callee may मुक्त memory containing tls_req.
		 * करो not reference lsreq after this.
		 */

		spin_lock(&tport->lock);
	पूर्ण
	spin_unlock(&tport->lock);
पूर्ण

अटल पूर्णांक
fcloop_t2h_ls_req(काष्ठा nvmet_fc_target_port *targetport, व्योम *hosthandle,
			काष्ठा nvmefc_ls_req *lsreq)
अणु
	काष्ठा fcloop_lsreq *tls_req = lsreq->निजी;
	काष्ठा fcloop_tport *tport = targetport->निजी;
	पूर्णांक ret = 0;

	/*
	 * hosthandle should be the dst.rport value.
	 * hosthandle ignored as fcloop currently is
	 * 1:1 tgtport vs remoteport
	 */
	tls_req->lsreq = lsreq;
	INIT_LIST_HEAD(&tls_req->ls_list);

	अगर (!tport->remoteport) अणु
		tls_req->status = -ECONNREFUSED;
		spin_lock(&tport->lock);
		list_add_tail(&tport->ls_list, &tls_req->ls_list);
		spin_unlock(&tport->lock);
		schedule_work(&tport->ls_work);
		वापस ret;
	पूर्ण

	tls_req->status = 0;
	ret = nvme_fc_rcv_ls_req(tport->remoteport, &tls_req->ls_rsp,
				 lsreq->rqstaddr, lsreq->rqstlen);

	वापस ret;
पूर्ण

अटल पूर्णांक
fcloop_t2h_xmt_ls_rsp(काष्ठा nvme_fc_local_port *localport,
			काष्ठा nvme_fc_remote_port *remoteport,
			काष्ठा nvmefc_ls_rsp *lsrsp)
अणु
	काष्ठा fcloop_lsreq *tls_req = ls_rsp_to_lsreq(lsrsp);
	काष्ठा nvmefc_ls_req *lsreq = tls_req->lsreq;
	काष्ठा fcloop_rport *rport = remoteport->निजी;
	काष्ठा nvmet_fc_target_port *targetport = rport->targetport;
	काष्ठा fcloop_tport *tport;

	स_नकल(lsreq->rspaddr, lsrsp->rspbuf,
		((lsreq->rsplen < lsrsp->rsplen) ?
				lsreq->rsplen : lsrsp->rsplen));
	lsrsp->करोne(lsrsp);

	अगर (targetport) अणु
		tport = targetport->निजी;
		spin_lock(&tport->lock);
		list_add_tail(&tport->ls_list, &tls_req->ls_list);
		spin_unlock(&tport->lock);
		schedule_work(&tport->ls_work);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम
fcloop_t2h_host_release(व्योम *hosthandle)
अणु
	/* host handle ignored क्रम now */
पूर्ण

/*
 * Simulate reception of RSCN and converting it to a initiator transport
 * call to rescan a remote port.
 */
अटल व्योम
fcloop_tgt_rscn_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा fcloop_rscn *tgt_rscn =
		container_of(work, काष्ठा fcloop_rscn, work);
	काष्ठा fcloop_tport *tport = tgt_rscn->tport;

	अगर (tport->remoteport)
		nvme_fc_rescan_remoteport(tport->remoteport);
	kमुक्त(tgt_rscn);
पूर्ण

अटल व्योम
fcloop_tgt_discovery_evt(काष्ठा nvmet_fc_target_port *tgtport)
अणु
	काष्ठा fcloop_rscn *tgt_rscn;

	tgt_rscn = kzalloc(माप(*tgt_rscn), GFP_KERNEL);
	अगर (!tgt_rscn)
		वापस;

	tgt_rscn->tport = tgtport->निजी;
	INIT_WORK(&tgt_rscn->work, fcloop_tgt_rscn_work);

	schedule_work(&tgt_rscn->work);
पूर्ण

अटल व्योम
fcloop_tfcp_req_मुक्त(काष्ठा kref *ref)
अणु
	काष्ठा fcloop_fcpreq *tfcp_req =
		container_of(ref, काष्ठा fcloop_fcpreq, ref);

	kमुक्त(tfcp_req);
पूर्ण

अटल व्योम
fcloop_tfcp_req_put(काष्ठा fcloop_fcpreq *tfcp_req)
अणु
	kref_put(&tfcp_req->ref, fcloop_tfcp_req_मुक्त);
पूर्ण

अटल पूर्णांक
fcloop_tfcp_req_get(काष्ठा fcloop_fcpreq *tfcp_req)
अणु
	वापस kref_get_unless_zero(&tfcp_req->ref);
पूर्ण

अटल व्योम
fcloop_call_host_करोne(काष्ठा nvmefc_fcp_req *fcpreq,
			काष्ठा fcloop_fcpreq *tfcp_req, पूर्णांक status)
अणु
	काष्ठा fcloop_ini_fcpreq *inireq = शून्य;

	अगर (fcpreq) अणु
		inireq = fcpreq->निजी;
		spin_lock(&inireq->inilock);
		inireq->tfcp_req = शून्य;
		spin_unlock(&inireq->inilock);

		fcpreq->status = status;
		fcpreq->करोne(fcpreq);
	पूर्ण

	/* release original io reference on tgt काष्ठा */
	fcloop_tfcp_req_put(tfcp_req);
पूर्ण

अटल bool drop_fabric_opcode;
#घोषणा DROP_OPCODE_MASK	0x00FF
/* fabrics opcode will have a bit set above 1st byte */
अटल पूर्णांक drop_opcode = -1;
अटल पूर्णांक drop_instance;
अटल पूर्णांक drop_amount;
अटल पूर्णांक drop_current_cnt;

/*
 * Routine to parse io and determine अगर the io is to be dropped.
 * Returns:
 *  0 अगर io is not obकाष्ठाed
 *  1 अगर io was dropped
 */
अटल पूर्णांक check_क्रम_drop(काष्ठा fcloop_fcpreq *tfcp_req)
अणु
	काष्ठा nvmefc_fcp_req *fcpreq = tfcp_req->fcpreq;
	काष्ठा nvme_fc_cmd_iu *cmdiu = fcpreq->cmdaddr;
	काष्ठा nvme_command *sqe = &cmdiu->sqe;

	अगर (drop_opcode == -1)
		वापस 0;

	pr_info("%s: seq opcd x%02x fctype x%02x: drop F %s op x%02x "
		"inst %d start %d amt %d\n",
		__func__, sqe->common.opcode, sqe->fabrics.fctype,
		drop_fabric_opcode ? "y" : "n",
		drop_opcode, drop_current_cnt, drop_instance, drop_amount);

	अगर ((drop_fabric_opcode &&
	     (sqe->common.opcode != nvme_fabrics_command ||
	      sqe->fabrics.fctype != drop_opcode)) ||
	    (!drop_fabric_opcode && sqe->common.opcode != drop_opcode))
		वापस 0;

	अगर (++drop_current_cnt >= drop_instance) अणु
		अगर (drop_current_cnt >= drop_instance + drop_amount)
			drop_opcode = -1;
		वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम
fcloop_fcp_recv_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा fcloop_fcpreq *tfcp_req =
		container_of(work, काष्ठा fcloop_fcpreq, fcp_rcv_work);
	काष्ठा nvmefc_fcp_req *fcpreq = tfcp_req->fcpreq;
	पूर्णांक ret = 0;
	bool पातed = false;

	spin_lock_irq(&tfcp_req->reqlock);
	चयन (tfcp_req->inistate) अणु
	हाल INI_IO_START:
		tfcp_req->inistate = INI_IO_ACTIVE;
		अवरोध;
	हाल INI_IO_ABORTED:
		पातed = true;
		अवरोध;
	शेष:
		spin_unlock_irq(&tfcp_req->reqlock);
		WARN_ON(1);
		वापस;
	पूर्ण
	spin_unlock_irq(&tfcp_req->reqlock);

	अगर (unlikely(पातed))
		ret = -ECANCELED;
	अन्यथा अणु
		अगर (likely(!check_क्रम_drop(tfcp_req)))
			ret = nvmet_fc_rcv_fcp_req(tfcp_req->tport->targetport,
				&tfcp_req->tgt_fcp_req,
				fcpreq->cmdaddr, fcpreq->cmdlen);
		अन्यथा
			pr_info("%s: dropped command ********\n", __func__);
	पूर्ण
	अगर (ret)
		fcloop_call_host_करोne(fcpreq, tfcp_req, ret);

	वापस;
पूर्ण

अटल व्योम
fcloop_fcp_पात_recv_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा fcloop_fcpreq *tfcp_req =
		container_of(work, काष्ठा fcloop_fcpreq, पात_rcv_work);
	काष्ठा nvmefc_fcp_req *fcpreq;
	bool completed = false;

	spin_lock_irq(&tfcp_req->reqlock);
	fcpreq = tfcp_req->fcpreq;
	चयन (tfcp_req->inistate) अणु
	हाल INI_IO_ABORTED:
		अवरोध;
	हाल INI_IO_COMPLETED:
		completed = true;
		अवरोध;
	शेष:
		spin_unlock_irq(&tfcp_req->reqlock);
		WARN_ON(1);
		वापस;
	पूर्ण
	spin_unlock_irq(&tfcp_req->reqlock);

	अगर (unlikely(completed)) अणु
		/* हटाओ reference taken in original पात करोwncall */
		fcloop_tfcp_req_put(tfcp_req);
		वापस;
	पूर्ण

	अगर (tfcp_req->tport->targetport)
		nvmet_fc_rcv_fcp_पात(tfcp_req->tport->targetport,
					&tfcp_req->tgt_fcp_req);

	spin_lock_irq(&tfcp_req->reqlock);
	tfcp_req->fcpreq = शून्य;
	spin_unlock_irq(&tfcp_req->reqlock);

	fcloop_call_host_करोne(fcpreq, tfcp_req, -ECANCELED);
	/* call_host_करोne releases reference क्रम पात करोwncall */
पूर्ण

/*
 * FCP IO operation करोne by target completion.
 * call back up initiator "done" flows.
 */
अटल व्योम
fcloop_tgt_fcprqst_करोne_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा fcloop_fcpreq *tfcp_req =
		container_of(work, काष्ठा fcloop_fcpreq, tio_करोne_work);
	काष्ठा nvmefc_fcp_req *fcpreq;

	spin_lock_irq(&tfcp_req->reqlock);
	fcpreq = tfcp_req->fcpreq;
	tfcp_req->inistate = INI_IO_COMPLETED;
	spin_unlock_irq(&tfcp_req->reqlock);

	fcloop_call_host_करोne(fcpreq, tfcp_req, tfcp_req->status);
पूर्ण


अटल पूर्णांक
fcloop_fcp_req(काष्ठा nvme_fc_local_port *localport,
			काष्ठा nvme_fc_remote_port *remoteport,
			व्योम *hw_queue_handle,
			काष्ठा nvmefc_fcp_req *fcpreq)
अणु
	काष्ठा fcloop_rport *rport = remoteport->निजी;
	काष्ठा fcloop_ini_fcpreq *inireq = fcpreq->निजी;
	काष्ठा fcloop_fcpreq *tfcp_req;

	अगर (!rport->targetport)
		वापस -ECONNREFUSED;

	tfcp_req = kzalloc(माप(*tfcp_req), GFP_ATOMIC);
	अगर (!tfcp_req)
		वापस -ENOMEM;

	inireq->fcpreq = fcpreq;
	inireq->tfcp_req = tfcp_req;
	spin_lock_init(&inireq->inilock);

	tfcp_req->fcpreq = fcpreq;
	tfcp_req->tport = rport->targetport->निजी;
	tfcp_req->inistate = INI_IO_START;
	spin_lock_init(&tfcp_req->reqlock);
	INIT_WORK(&tfcp_req->fcp_rcv_work, fcloop_fcp_recv_work);
	INIT_WORK(&tfcp_req->पात_rcv_work, fcloop_fcp_पात_recv_work);
	INIT_WORK(&tfcp_req->tio_करोne_work, fcloop_tgt_fcprqst_करोne_work);
	kref_init(&tfcp_req->ref);

	schedule_work(&tfcp_req->fcp_rcv_work);

	वापस 0;
पूर्ण

अटल व्योम
fcloop_fcp_copy_data(u8 op, काष्ठा scatterlist *data_sg,
			काष्ठा scatterlist *io_sg, u32 offset, u32 length)
अणु
	व्योम *data_p, *io_p;
	u32 data_len, io_len, tlen;

	io_p = sg_virt(io_sg);
	io_len = io_sg->length;

	क्रम ( ; offset; ) अणु
		tlen = min_t(u32, offset, io_len);
		offset -= tlen;
		io_len -= tlen;
		अगर (!io_len) अणु
			io_sg = sg_next(io_sg);
			io_p = sg_virt(io_sg);
			io_len = io_sg->length;
		पूर्ण अन्यथा
			io_p += tlen;
	पूर्ण

	data_p = sg_virt(data_sg);
	data_len = data_sg->length;

	क्रम ( ; length; ) अणु
		tlen = min_t(u32, io_len, data_len);
		tlen = min_t(u32, tlen, length);

		अगर (op == NVMET_FCOP_WRITEDATA)
			स_नकल(data_p, io_p, tlen);
		अन्यथा
			स_नकल(io_p, data_p, tlen);

		length -= tlen;

		io_len -= tlen;
		अगर ((!io_len) && (length)) अणु
			io_sg = sg_next(io_sg);
			io_p = sg_virt(io_sg);
			io_len = io_sg->length;
		पूर्ण अन्यथा
			io_p += tlen;

		data_len -= tlen;
		अगर ((!data_len) && (length)) अणु
			data_sg = sg_next(data_sg);
			data_p = sg_virt(data_sg);
			data_len = data_sg->length;
		पूर्ण अन्यथा
			data_p += tlen;
	पूर्ण
पूर्ण

अटल पूर्णांक
fcloop_fcp_op(काष्ठा nvmet_fc_target_port *tgtport,
			काष्ठा nvmefc_tgt_fcp_req *tgt_fcpreq)
अणु
	काष्ठा fcloop_fcpreq *tfcp_req = tgt_fcp_req_to_fcpreq(tgt_fcpreq);
	काष्ठा nvmefc_fcp_req *fcpreq;
	u32 rsplen = 0, xfrlen = 0;
	पूर्णांक fcp_err = 0, active, पातed;
	u8 op = tgt_fcpreq->op;

	spin_lock_irq(&tfcp_req->reqlock);
	fcpreq = tfcp_req->fcpreq;
	active = tfcp_req->active;
	पातed = tfcp_req->पातed;
	tfcp_req->active = true;
	spin_unlock_irq(&tfcp_req->reqlock);

	अगर (unlikely(active))
		/* illegal - call जबतक i/o active */
		वापस -EALREADY;

	अगर (unlikely(पातed)) अणु
		/* target transport has पातed i/o prior */
		spin_lock_irq(&tfcp_req->reqlock);
		tfcp_req->active = false;
		spin_unlock_irq(&tfcp_req->reqlock);
		tgt_fcpreq->transferred_length = 0;
		tgt_fcpreq->fcp_error = -ECANCELED;
		tgt_fcpreq->करोne(tgt_fcpreq);
		वापस 0;
	पूर्ण

	/*
	 * अगर fcpreq is शून्य, the I/O has been पातed (from
	 * initiator side). For the target side, act as अगर all is well
	 * but करोn't actually move data.
	 */

	चयन (op) अणु
	हाल NVMET_FCOP_WRITEDATA:
		xfrlen = tgt_fcpreq->transfer_length;
		अगर (fcpreq) अणु
			fcloop_fcp_copy_data(op, tgt_fcpreq->sg,
					fcpreq->first_sgl, tgt_fcpreq->offset,
					xfrlen);
			fcpreq->transferred_length += xfrlen;
		पूर्ण
		अवरोध;

	हाल NVMET_FCOP_READDATA:
	हाल NVMET_FCOP_READDATA_RSP:
		xfrlen = tgt_fcpreq->transfer_length;
		अगर (fcpreq) अणु
			fcloop_fcp_copy_data(op, tgt_fcpreq->sg,
					fcpreq->first_sgl, tgt_fcpreq->offset,
					xfrlen);
			fcpreq->transferred_length += xfrlen;
		पूर्ण
		अगर (op == NVMET_FCOP_READDATA)
			अवरोध;

		/* Fall-Thru to RSP handling */
		fallthrough;

	हाल NVMET_FCOP_RSP:
		अगर (fcpreq) अणु
			rsplen = ((fcpreq->rsplen < tgt_fcpreq->rsplen) ?
					fcpreq->rsplen : tgt_fcpreq->rsplen);
			स_नकल(fcpreq->rspaddr, tgt_fcpreq->rspaddr, rsplen);
			अगर (rsplen < tgt_fcpreq->rsplen)
				fcp_err = -E2BIG;
			fcpreq->rcv_rsplen = rsplen;
			fcpreq->status = 0;
		पूर्ण
		tfcp_req->status = 0;
		अवरोध;

	शेष:
		fcp_err = -EINVAL;
		अवरोध;
	पूर्ण

	spin_lock_irq(&tfcp_req->reqlock);
	tfcp_req->active = false;
	spin_unlock_irq(&tfcp_req->reqlock);

	tgt_fcpreq->transferred_length = xfrlen;
	tgt_fcpreq->fcp_error = fcp_err;
	tgt_fcpreq->करोne(tgt_fcpreq);

	वापस 0;
पूर्ण

अटल व्योम
fcloop_tgt_fcp_पात(काष्ठा nvmet_fc_target_port *tgtport,
			काष्ठा nvmefc_tgt_fcp_req *tgt_fcpreq)
अणु
	काष्ठा fcloop_fcpreq *tfcp_req = tgt_fcp_req_to_fcpreq(tgt_fcpreq);

	/*
	 * mark पातed only in हाल there were 2 thपढ़ोs in transport
	 * (one करोing io, other करोing पात) and only समाप्तs ops posted
	 * after the पात request
	 */
	spin_lock_irq(&tfcp_req->reqlock);
	tfcp_req->पातed = true;
	spin_unlock_irq(&tfcp_req->reqlock);

	tfcp_req->status = NVME_SC_INTERNAL;

	/*
	 * nothing more to करो. If io wasn't active, the transport should
	 * immediately call the req_release. If it was active, the op
	 * will complete, and the lldd should call req_release.
	 */
पूर्ण

अटल व्योम
fcloop_fcp_req_release(काष्ठा nvmet_fc_target_port *tgtport,
			काष्ठा nvmefc_tgt_fcp_req *tgt_fcpreq)
अणु
	काष्ठा fcloop_fcpreq *tfcp_req = tgt_fcp_req_to_fcpreq(tgt_fcpreq);

	schedule_work(&tfcp_req->tio_करोne_work);
पूर्ण

अटल व्योम
fcloop_h2t_ls_पात(काष्ठा nvme_fc_local_port *localport,
			काष्ठा nvme_fc_remote_port *remoteport,
				काष्ठा nvmefc_ls_req *lsreq)
अणु
पूर्ण

अटल व्योम
fcloop_t2h_ls_पात(काष्ठा nvmet_fc_target_port *targetport,
			व्योम *hosthandle, काष्ठा nvmefc_ls_req *lsreq)
अणु
पूर्ण

अटल व्योम
fcloop_fcp_पात(काष्ठा nvme_fc_local_port *localport,
			काष्ठा nvme_fc_remote_port *remoteport,
			व्योम *hw_queue_handle,
			काष्ठा nvmefc_fcp_req *fcpreq)
अणु
	काष्ठा fcloop_ini_fcpreq *inireq = fcpreq->निजी;
	काष्ठा fcloop_fcpreq *tfcp_req;
	bool पातio = true;

	spin_lock(&inireq->inilock);
	tfcp_req = inireq->tfcp_req;
	अगर (tfcp_req)
		fcloop_tfcp_req_get(tfcp_req);
	spin_unlock(&inireq->inilock);

	अगर (!tfcp_req)
		/* पात has alपढ़ोy been called */
		वापस;

	/* अवरोध initiator/target relationship क्रम io */
	spin_lock_irq(&tfcp_req->reqlock);
	चयन (tfcp_req->inistate) अणु
	हाल INI_IO_START:
	हाल INI_IO_ACTIVE:
		tfcp_req->inistate = INI_IO_ABORTED;
		अवरोध;
	हाल INI_IO_COMPLETED:
		पातio = false;
		अवरोध;
	शेष:
		spin_unlock_irq(&tfcp_req->reqlock);
		WARN_ON(1);
		वापस;
	पूर्ण
	spin_unlock_irq(&tfcp_req->reqlock);

	अगर (पातio)
		/* leave the reference जबतक the work item is scheduled */
		WARN_ON(!schedule_work(&tfcp_req->पात_rcv_work));
	अन्यथा  अणु
		/*
		 * as the io has alपढ़ोy had the करोne callback made,
		 * nothing more to करो. So release the reference taken above
		 */
		fcloop_tfcp_req_put(tfcp_req);
	पूर्ण
पूर्ण

अटल व्योम
fcloop_nport_मुक्त(काष्ठा kref *ref)
अणु
	काष्ठा fcloop_nport *nport =
		container_of(ref, काष्ठा fcloop_nport, ref);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&fcloop_lock, flags);
	list_del(&nport->nport_list);
	spin_unlock_irqrestore(&fcloop_lock, flags);

	kमुक्त(nport);
पूर्ण

अटल व्योम
fcloop_nport_put(काष्ठा fcloop_nport *nport)
अणु
	kref_put(&nport->ref, fcloop_nport_मुक्त);
पूर्ण

अटल पूर्णांक
fcloop_nport_get(काष्ठा fcloop_nport *nport)
अणु
	वापस kref_get_unless_zero(&nport->ref);
पूर्ण

अटल व्योम
fcloop_localport_delete(काष्ठा nvme_fc_local_port *localport)
अणु
	काष्ठा fcloop_lport_priv *lport_priv = localport->निजी;
	काष्ठा fcloop_lport *lport = lport_priv->lport;

	/* release any thपढ़ोs रुकोing क्रम the unreg to complete */
	complete(&lport->unreg_करोne);
पूर्ण

अटल व्योम
fcloop_remoteport_delete(काष्ठा nvme_fc_remote_port *remoteport)
अणु
	काष्ठा fcloop_rport *rport = remoteport->निजी;

	flush_work(&rport->ls_work);
	fcloop_nport_put(rport->nport);
पूर्ण

अटल व्योम
fcloop_targetport_delete(काष्ठा nvmet_fc_target_port *targetport)
अणु
	काष्ठा fcloop_tport *tport = targetport->निजी;

	flush_work(&tport->ls_work);
	fcloop_nport_put(tport->nport);
पूर्ण

#घोषणा	FCLOOP_HW_QUEUES		4
#घोषणा	FCLOOP_SGL_SEGS			256
#घोषणा FCLOOP_DMABOUND_4G		0xFFFFFFFF

अटल काष्ठा nvme_fc_port_ढाँचा fcढाँचा = अणु
	.localport_delete	= fcloop_localport_delete,
	.remoteport_delete	= fcloop_remoteport_delete,
	.create_queue		= fcloop_create_queue,
	.delete_queue		= fcloop_delete_queue,
	.ls_req			= fcloop_h2t_ls_req,
	.fcp_io			= fcloop_fcp_req,
	.ls_पात		= fcloop_h2t_ls_पात,
	.fcp_पात		= fcloop_fcp_पात,
	.xmt_ls_rsp		= fcloop_t2h_xmt_ls_rsp,
	.max_hw_queues		= FCLOOP_HW_QUEUES,
	.max_sgl_segments	= FCLOOP_SGL_SEGS,
	.max_dअगर_sgl_segments	= FCLOOP_SGL_SEGS,
	.dma_boundary		= FCLOOP_DMABOUND_4G,
	/* sizes of additional निजी data क्रम data काष्ठाures */
	.local_priv_sz		= माप(काष्ठा fcloop_lport_priv),
	.remote_priv_sz		= माप(काष्ठा fcloop_rport),
	.lsrqst_priv_sz		= माप(काष्ठा fcloop_lsreq),
	.fcprqst_priv_sz	= माप(काष्ठा fcloop_ini_fcpreq),
पूर्ण;

अटल काष्ठा nvmet_fc_target_ढाँचा tgtढाँचा = अणु
	.targetport_delete	= fcloop_targetport_delete,
	.xmt_ls_rsp		= fcloop_h2t_xmt_ls_rsp,
	.fcp_op			= fcloop_fcp_op,
	.fcp_पात		= fcloop_tgt_fcp_पात,
	.fcp_req_release	= fcloop_fcp_req_release,
	.discovery_event	= fcloop_tgt_discovery_evt,
	.ls_req			= fcloop_t2h_ls_req,
	.ls_पात		= fcloop_t2h_ls_पात,
	.host_release		= fcloop_t2h_host_release,
	.max_hw_queues		= FCLOOP_HW_QUEUES,
	.max_sgl_segments	= FCLOOP_SGL_SEGS,
	.max_dअगर_sgl_segments	= FCLOOP_SGL_SEGS,
	.dma_boundary		= FCLOOP_DMABOUND_4G,
	/* optional features */
	.target_features	= 0,
	/* sizes of additional निजी data क्रम data काष्ठाures */
	.target_priv_sz		= माप(काष्ठा fcloop_tport),
	.lsrqst_priv_sz		= माप(काष्ठा fcloop_lsreq),
पूर्ण;

अटल sमाप_प्रकार
fcloop_create_local_port(काष्ठा device *dev, काष्ठा device_attribute *attr,
		स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा nvme_fc_port_info pinfo;
	काष्ठा fcloop_ctrl_options *opts;
	काष्ठा nvme_fc_local_port *localport;
	काष्ठा fcloop_lport *lport;
	काष्ठा fcloop_lport_priv *lport_priv;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret = -ENOMEM;

	lport = kzalloc(माप(*lport), GFP_KERNEL);
	अगर (!lport)
		वापस -ENOMEM;

	opts = kzalloc(माप(*opts), GFP_KERNEL);
	अगर (!opts)
		जाओ out_मुक्त_lport;

	ret = fcloop_parse_options(opts, buf);
	अगर (ret)
		जाओ out_मुक्त_opts;

	/* everything there ? */
	अगर ((opts->mask & LPORT_OPTS) != LPORT_OPTS) अणु
		ret = -EINVAL;
		जाओ out_मुक्त_opts;
	पूर्ण

	स_रखो(&pinfo, 0, माप(pinfo));
	pinfo.node_name = opts->wwnn;
	pinfo.port_name = opts->wwpn;
	pinfo.port_role = opts->roles;
	pinfo.port_id = opts->fcaddr;

	ret = nvme_fc_रेजिस्टर_localport(&pinfo, &fcढाँचा, शून्य, &localport);
	अगर (!ret) अणु
		/* success */
		lport_priv = localport->निजी;
		lport_priv->lport = lport;

		lport->localport = localport;
		INIT_LIST_HEAD(&lport->lport_list);

		spin_lock_irqsave(&fcloop_lock, flags);
		list_add_tail(&lport->lport_list, &fcloop_lports);
		spin_unlock_irqrestore(&fcloop_lock, flags);
	पूर्ण

out_मुक्त_opts:
	kमुक्त(opts);
out_मुक्त_lport:
	/* मुक्त only अगर we're going to fail */
	अगर (ret)
		kमुक्त(lport);

	वापस ret ? ret : count;
पूर्ण


अटल व्योम
__unlink_local_port(काष्ठा fcloop_lport *lport)
अणु
	list_del(&lport->lport_list);
पूर्ण

अटल पूर्णांक
__रुको_localport_unreg(काष्ठा fcloop_lport *lport)
अणु
	पूर्णांक ret;

	init_completion(&lport->unreg_करोne);

	ret = nvme_fc_unरेजिस्टर_localport(lport->localport);

	रुको_क्रम_completion(&lport->unreg_करोne);

	kमुक्त(lport);

	वापस ret;
पूर्ण


अटल sमाप_प्रकार
fcloop_delete_local_port(काष्ठा device *dev, काष्ठा device_attribute *attr,
		स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा fcloop_lport *tlport, *lport = शून्य;
	u64 nodename, portname;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	ret = fcloop_parse_nm_options(dev, &nodename, &portname, buf);
	अगर (ret)
		वापस ret;

	spin_lock_irqsave(&fcloop_lock, flags);

	list_क्रम_each_entry(tlport, &fcloop_lports, lport_list) अणु
		अगर (tlport->localport->node_name == nodename &&
		    tlport->localport->port_name == portname) अणु
			lport = tlport;
			__unlink_local_port(lport);
			अवरोध;
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&fcloop_lock, flags);

	अगर (!lport)
		वापस -ENOENT;

	ret = __रुको_localport_unreg(lport);

	वापस ret ? ret : count;
पूर्ण

अटल काष्ठा fcloop_nport *
fcloop_alloc_nport(स्थिर अक्षर *buf, माप_प्रकार count, bool remoteport)
अणु
	काष्ठा fcloop_nport *newnport, *nport = शून्य;
	काष्ठा fcloop_lport *पंचांगplport, *lport = शून्य;
	काष्ठा fcloop_ctrl_options *opts;
	अचिन्हित दीर्घ flags;
	u32 opts_mask = (remoteport) ? RPORT_OPTS : TGTPORT_OPTS;
	पूर्णांक ret;

	opts = kzalloc(माप(*opts), GFP_KERNEL);
	अगर (!opts)
		वापस शून्य;

	ret = fcloop_parse_options(opts, buf);
	अगर (ret)
		जाओ out_मुक्त_opts;

	/* everything there ? */
	अगर ((opts->mask & opts_mask) != opts_mask) अणु
		ret = -EINVAL;
		जाओ out_मुक्त_opts;
	पूर्ण

	newnport = kzalloc(माप(*newnport), GFP_KERNEL);
	अगर (!newnport)
		जाओ out_मुक्त_opts;

	INIT_LIST_HEAD(&newnport->nport_list);
	newnport->node_name = opts->wwnn;
	newnport->port_name = opts->wwpn;
	अगर (opts->mask & NVMF_OPT_ROLES)
		newnport->port_role = opts->roles;
	अगर (opts->mask & NVMF_OPT_FCADDR)
		newnport->port_id = opts->fcaddr;
	kref_init(&newnport->ref);

	spin_lock_irqsave(&fcloop_lock, flags);

	list_क्रम_each_entry(पंचांगplport, &fcloop_lports, lport_list) अणु
		अगर (पंचांगplport->localport->node_name == opts->wwnn &&
		    पंचांगplport->localport->port_name == opts->wwpn)
			जाओ out_invalid_opts;

		अगर (पंचांगplport->localport->node_name == opts->lpwwnn &&
		    पंचांगplport->localport->port_name == opts->lpwwpn)
			lport = पंचांगplport;
	पूर्ण

	अगर (remoteport) अणु
		अगर (!lport)
			जाओ out_invalid_opts;
		newnport->lport = lport;
	पूर्ण

	list_क्रम_each_entry(nport, &fcloop_nports, nport_list) अणु
		अगर (nport->node_name == opts->wwnn &&
		    nport->port_name == opts->wwpn) अणु
			अगर ((remoteport && nport->rport) ||
			    (!remoteport && nport->tport)) अणु
				nport = शून्य;
				जाओ out_invalid_opts;
			पूर्ण

			fcloop_nport_get(nport);

			spin_unlock_irqrestore(&fcloop_lock, flags);

			अगर (remoteport)
				nport->lport = lport;
			अगर (opts->mask & NVMF_OPT_ROLES)
				nport->port_role = opts->roles;
			अगर (opts->mask & NVMF_OPT_FCADDR)
				nport->port_id = opts->fcaddr;
			जाओ out_मुक्त_newnport;
		पूर्ण
	पूर्ण

	list_add_tail(&newnport->nport_list, &fcloop_nports);

	spin_unlock_irqrestore(&fcloop_lock, flags);

	kमुक्त(opts);
	वापस newnport;

out_invalid_opts:
	spin_unlock_irqrestore(&fcloop_lock, flags);
out_मुक्त_newnport:
	kमुक्त(newnport);
out_मुक्त_opts:
	kमुक्त(opts);
	वापस nport;
पूर्ण

अटल sमाप_प्रकार
fcloop_create_remote_port(काष्ठा device *dev, काष्ठा device_attribute *attr,
		स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा nvme_fc_remote_port *remoteport;
	काष्ठा fcloop_nport *nport;
	काष्ठा fcloop_rport *rport;
	काष्ठा nvme_fc_port_info pinfo;
	पूर्णांक ret;

	nport = fcloop_alloc_nport(buf, count, true);
	अगर (!nport)
		वापस -EIO;

	स_रखो(&pinfo, 0, माप(pinfo));
	pinfo.node_name = nport->node_name;
	pinfo.port_name = nport->port_name;
	pinfo.port_role = nport->port_role;
	pinfo.port_id = nport->port_id;

	ret = nvme_fc_रेजिस्टर_remoteport(nport->lport->localport,
						&pinfo, &remoteport);
	अगर (ret || !remoteport) अणु
		fcloop_nport_put(nport);
		वापस ret;
	पूर्ण

	/* success */
	rport = remoteport->निजी;
	rport->remoteport = remoteport;
	rport->targetport = (nport->tport) ?  nport->tport->targetport : शून्य;
	अगर (nport->tport) अणु
		nport->tport->remoteport = remoteport;
		nport->tport->lport = nport->lport;
	पूर्ण
	rport->nport = nport;
	rport->lport = nport->lport;
	nport->rport = rport;
	spin_lock_init(&rport->lock);
	INIT_WORK(&rport->ls_work, fcloop_rport_lsrqst_work);
	INIT_LIST_HEAD(&rport->ls_list);

	वापस count;
पूर्ण


अटल काष्ठा fcloop_rport *
__unlink_remote_port(काष्ठा fcloop_nport *nport)
अणु
	काष्ठा fcloop_rport *rport = nport->rport;

	अगर (rport && nport->tport)
		nport->tport->remoteport = शून्य;
	nport->rport = शून्य;

	वापस rport;
पूर्ण

अटल पूर्णांक
__remoteport_unreg(काष्ठा fcloop_nport *nport, काष्ठा fcloop_rport *rport)
अणु
	अगर (!rport)
		वापस -EALREADY;

	वापस nvme_fc_unरेजिस्टर_remoteport(rport->remoteport);
पूर्ण

अटल sमाप_प्रकार
fcloop_delete_remote_port(काष्ठा device *dev, काष्ठा device_attribute *attr,
		स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा fcloop_nport *nport = शून्य, *पंचांगpport;
	अटल काष्ठा fcloop_rport *rport;
	u64 nodename, portname;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	ret = fcloop_parse_nm_options(dev, &nodename, &portname, buf);
	अगर (ret)
		वापस ret;

	spin_lock_irqsave(&fcloop_lock, flags);

	list_क्रम_each_entry(पंचांगpport, &fcloop_nports, nport_list) अणु
		अगर (पंचांगpport->node_name == nodename &&
		    पंचांगpport->port_name == portname && पंचांगpport->rport) अणु
			nport = पंचांगpport;
			rport = __unlink_remote_port(nport);
			अवरोध;
		पूर्ण
	पूर्ण

	spin_unlock_irqrestore(&fcloop_lock, flags);

	अगर (!nport)
		वापस -ENOENT;

	ret = __remoteport_unreg(nport, rport);

	वापस ret ? ret : count;
पूर्ण

अटल sमाप_प्रकार
fcloop_create_target_port(काष्ठा device *dev, काष्ठा device_attribute *attr,
		स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा nvmet_fc_target_port *targetport;
	काष्ठा fcloop_nport *nport;
	काष्ठा fcloop_tport *tport;
	काष्ठा nvmet_fc_port_info tinfo;
	पूर्णांक ret;

	nport = fcloop_alloc_nport(buf, count, false);
	अगर (!nport)
		वापस -EIO;

	tinfo.node_name = nport->node_name;
	tinfo.port_name = nport->port_name;
	tinfo.port_id = nport->port_id;

	ret = nvmet_fc_रेजिस्टर_targetport(&tinfo, &tgtढाँचा, शून्य,
						&targetport);
	अगर (ret) अणु
		fcloop_nport_put(nport);
		वापस ret;
	पूर्ण

	/* success */
	tport = targetport->निजी;
	tport->targetport = targetport;
	tport->remoteport = (nport->rport) ?  nport->rport->remoteport : शून्य;
	अगर (nport->rport)
		nport->rport->targetport = targetport;
	tport->nport = nport;
	tport->lport = nport->lport;
	nport->tport = tport;
	spin_lock_init(&tport->lock);
	INIT_WORK(&tport->ls_work, fcloop_tport_lsrqst_work);
	INIT_LIST_HEAD(&tport->ls_list);

	वापस count;
पूर्ण


अटल काष्ठा fcloop_tport *
__unlink_target_port(काष्ठा fcloop_nport *nport)
अणु
	काष्ठा fcloop_tport *tport = nport->tport;

	अगर (tport && nport->rport)
		nport->rport->targetport = शून्य;
	nport->tport = शून्य;

	वापस tport;
पूर्ण

अटल पूर्णांक
__targetport_unreg(काष्ठा fcloop_nport *nport, काष्ठा fcloop_tport *tport)
अणु
	अगर (!tport)
		वापस -EALREADY;

	वापस nvmet_fc_unरेजिस्टर_targetport(tport->targetport);
पूर्ण

अटल sमाप_प्रकार
fcloop_delete_target_port(काष्ठा device *dev, काष्ठा device_attribute *attr,
		स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा fcloop_nport *nport = शून्य, *पंचांगpport;
	काष्ठा fcloop_tport *tport = शून्य;
	u64 nodename, portname;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	ret = fcloop_parse_nm_options(dev, &nodename, &portname, buf);
	अगर (ret)
		वापस ret;

	spin_lock_irqsave(&fcloop_lock, flags);

	list_क्रम_each_entry(पंचांगpport, &fcloop_nports, nport_list) अणु
		अगर (पंचांगpport->node_name == nodename &&
		    पंचांगpport->port_name == portname && पंचांगpport->tport) अणु
			nport = पंचांगpport;
			tport = __unlink_target_port(nport);
			अवरोध;
		पूर्ण
	पूर्ण

	spin_unlock_irqrestore(&fcloop_lock, flags);

	अगर (!nport)
		वापस -ENOENT;

	ret = __targetport_unreg(nport, tport);

	वापस ret ? ret : count;
पूर्ण

अटल sमाप_प्रकार
fcloop_set_cmd_drop(काष्ठा device *dev, काष्ठा device_attribute *attr,
		स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	अचिन्हित पूर्णांक opcode;
	पूर्णांक starting, amount;

	अगर (माला_पूछो(buf, "%x:%d:%d", &opcode, &starting, &amount) != 3)
		वापस -EBADRQC;

	drop_current_cnt = 0;
	drop_fabric_opcode = (opcode & ~DROP_OPCODE_MASK) ? true : false;
	drop_opcode = (opcode & DROP_OPCODE_MASK);
	drop_instance = starting;
	/* the check to drop routine uses instance + count to know when
	 * to end. Thus, अगर dropping 1 instance, count should be 0.
	 * so subtract 1 from the count.
	 */
	drop_amount = amount - 1;

	pr_info("%s: DROP: Starting at instance %d of%s opcode x%x drop +%d "
		"instances\n",
		__func__, drop_instance, drop_fabric_opcode ? " fabric" : "",
		drop_opcode, drop_amount);

	वापस count;
पूर्ण


अटल DEVICE_ATTR(add_local_port, 0200, शून्य, fcloop_create_local_port);
अटल DEVICE_ATTR(del_local_port, 0200, शून्य, fcloop_delete_local_port);
अटल DEVICE_ATTR(add_remote_port, 0200, शून्य, fcloop_create_remote_port);
अटल DEVICE_ATTR(del_remote_port, 0200, शून्य, fcloop_delete_remote_port);
अटल DEVICE_ATTR(add_target_port, 0200, शून्य, fcloop_create_target_port);
अटल DEVICE_ATTR(del_target_port, 0200, शून्य, fcloop_delete_target_port);
अटल DEVICE_ATTR(set_cmd_drop, 0200, शून्य, fcloop_set_cmd_drop);

अटल काष्ठा attribute *fcloop_dev_attrs[] = अणु
	&dev_attr_add_local_port.attr,
	&dev_attr_del_local_port.attr,
	&dev_attr_add_remote_port.attr,
	&dev_attr_del_remote_port.attr,
	&dev_attr_add_target_port.attr,
	&dev_attr_del_target_port.attr,
	&dev_attr_set_cmd_drop.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group fclopp_dev_attrs_group = अणु
	.attrs		= fcloop_dev_attrs,
पूर्ण;

अटल स्थिर काष्ठा attribute_group *fcloop_dev_attr_groups[] = अणु
	&fclopp_dev_attrs_group,
	शून्य,
पूर्ण;

अटल काष्ठा class *fcloop_class;
अटल काष्ठा device *fcloop_device;


अटल पूर्णांक __init fcloop_init(व्योम)
अणु
	पूर्णांक ret;

	fcloop_class = class_create(THIS_MODULE, "fcloop");
	अगर (IS_ERR(fcloop_class)) अणु
		pr_err("couldn't register class fcloop\n");
		ret = PTR_ERR(fcloop_class);
		वापस ret;
	पूर्ण

	fcloop_device = device_create_with_groups(
				fcloop_class, शून्य, MKDEV(0, 0), शून्य,
				fcloop_dev_attr_groups, "ctl");
	अगर (IS_ERR(fcloop_device)) अणु
		pr_err("couldn't create ctl device!\n");
		ret = PTR_ERR(fcloop_device);
		जाओ out_destroy_class;
	पूर्ण

	get_device(fcloop_device);

	वापस 0;

out_destroy_class:
	class_destroy(fcloop_class);
	वापस ret;
पूर्ण

अटल व्योम __निकास fcloop_निकास(व्योम)
अणु
	काष्ठा fcloop_lport *lport = शून्य;
	काष्ठा fcloop_nport *nport = शून्य;
	काष्ठा fcloop_tport *tport;
	काष्ठा fcloop_rport *rport;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	spin_lock_irqsave(&fcloop_lock, flags);

	क्रम (;;) अणु
		nport = list_first_entry_or_null(&fcloop_nports,
						typeof(*nport), nport_list);
		अगर (!nport)
			अवरोध;

		tport = __unlink_target_port(nport);
		rport = __unlink_remote_port(nport);

		spin_unlock_irqrestore(&fcloop_lock, flags);

		ret = __targetport_unreg(nport, tport);
		अगर (ret)
			pr_warn("%s: Failed deleting target port\n", __func__);

		ret = __remoteport_unreg(nport, rport);
		अगर (ret)
			pr_warn("%s: Failed deleting remote port\n", __func__);

		spin_lock_irqsave(&fcloop_lock, flags);
	पूर्ण

	क्रम (;;) अणु
		lport = list_first_entry_or_null(&fcloop_lports,
						typeof(*lport), lport_list);
		अगर (!lport)
			अवरोध;

		__unlink_local_port(lport);

		spin_unlock_irqrestore(&fcloop_lock, flags);

		ret = __रुको_localport_unreg(lport);
		अगर (ret)
			pr_warn("%s: Failed deleting local port\n", __func__);

		spin_lock_irqsave(&fcloop_lock, flags);
	पूर्ण

	spin_unlock_irqrestore(&fcloop_lock, flags);

	put_device(fcloop_device);

	device_destroy(fcloop_class, MKDEV(0, 0));
	class_destroy(fcloop_class);
पूर्ण

module_init(fcloop_init);
module_निकास(fcloop_निकास);

MODULE_LICENSE("GPL v2");
