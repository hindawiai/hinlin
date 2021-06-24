<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * QLogic Fibre Channel HBA Driver
 * Copyright (c)  2003-2014 QLogic Corporation
 */
#समावेश "qla_def.h"

#समावेश <linux/moduleparam.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/delay.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/mutex.h>
#समावेश <linux/kobject.h>
#समावेश <linux/slab.h>
#समावेश <linux/blk-mq-pci.h>
#समावेश <linux/refcount.h>

#समावेश <scsi/scsi_tcq.h>
#समावेश <scsi/scsicam.h>
#समावेश <scsi/scsi_transport.h>
#समावेश <scsi/scsi_transport_fc.h>

#समावेश "qla_target.h"

/*
 * Driver version
 */
अक्षर qla2x00_version_str[40];

अटल पूर्णांक apidev_major;

/*
 * SRB allocation cache
 */
काष्ठा kmem_cache *srb_cachep;

पूर्णांक ql2xfulldump_on_mpअगरail;
module_param(ql2xfulldump_on_mpअगरail, पूर्णांक, S_IRUGO | S_IWUSR);
MODULE_PARM_DESC(ql2xfulldump_on_mpअगरail,
		 "Set this to take full dump on MPI hang.");

पूर्णांक ql2xenक्रमce_iocb_limit = 1;
module_param(ql2xenक्रमce_iocb_limit, पूर्णांक, S_IRUGO | S_IWUSR);
MODULE_PARM_DESC(ql2xenक्रमce_iocb_limit,
		 "Enforce IOCB throttling, to avoid FW congestion. (default: 1)");

/*
 * CT6 CTX allocation cache
 */
अटल काष्ठा kmem_cache *ctx_cachep;
/*
 * error level क्रम logging
 */
uपूर्णांक ql_errlev = 0x8001;

अटल पूर्णांक ql2xenableclass2;
module_param(ql2xenableclass2, पूर्णांक, S_IRUGO|S_IRUSR);
MODULE_PARM_DESC(ql2xenableclass2,
		"Specify if Class 2 operations are supported from the very "
		"beginning. Default is 0 - class 2 not supported.");


पूर्णांक ql2xlogपूर्णांकimeout = 20;
module_param(ql2xlogपूर्णांकimeout, पूर्णांक, S_IRUGO);
MODULE_PARM_DESC(ql2xlogपूर्णांकimeout,
		"Login timeout value in seconds.");

पूर्णांक qlport_करोwn_retry;
module_param(qlport_करोwn_retry, पूर्णांक, S_IRUGO);
MODULE_PARM_DESC(qlport_करोwn_retry,
		"Maximum number of command retries to a port that returns "
		"a PORT-DOWN status.");

पूर्णांक ql2xplogiअसलentdevice;
module_param(ql2xplogiअसलentdevice, पूर्णांक, S_IRUGO|S_IWUSR);
MODULE_PARM_DESC(ql2xplogiअसलentdevice,
		"Option to enable PLOGI to devices that are not present after "
		"a Fabric scan.  This is needed for several broken switches. "
		"Default is 0 - no PLOGI. 1 - perform PLOGI.");

पूर्णांक ql2xloginretrycount;
module_param(ql2xloginretrycount, पूर्णांक, S_IRUGO);
MODULE_PARM_DESC(ql2xloginretrycount,
		"Specify an alternate value for the NVRAM login retry count.");

पूर्णांक ql2xallocfwdump = 1;
module_param(ql2xallocfwdump, पूर्णांक, S_IRUGO);
MODULE_PARM_DESC(ql2xallocfwdump,
		"Option to enable allocation of memory for a firmware dump "
		"during HBA initialization.  Memory allocation requirements "
		"vary by ISP type.  Default is 1 - allocate memory.");

पूर्णांक ql2xextended_error_logging;
module_param(ql2xextended_error_logging, पूर्णांक, S_IRUGO|S_IWUSR);
module_param_named(logging, ql2xextended_error_logging, पूर्णांक, S_IRUGO|S_IWUSR);
MODULE_PARM_DESC(ql2xextended_error_logging,
		"Option to enable extended error logging,\n"
		"\t\tDefault is 0 - no logging.  0x40000000 - Module Init & Probe.\n"
		"\t\t0x20000000 - Mailbox Cmnds. 0x10000000 - Device Discovery.\n"
		"\t\t0x08000000 - IO tracing.    0x04000000 - DPC Thread.\n"
		"\t\t0x02000000 - Async events.  0x01000000 - Timer routines.\n"
		"\t\t0x00800000 - User space.    0x00400000 - Task Management.\n"
		"\t\t0x00200000 - AER/EEH.       0x00100000 - Multi Q.\n"
		"\t\t0x00080000 - P3P Specific.  0x00040000 - Virtual Port.\n"
		"\t\t0x00020000 - Buffer Dump.   0x00010000 - Misc.\n"
		"\t\t0x00008000 - Verbose.       0x00004000 - Target.\n"
		"\t\t0x00002000 - Target Mgmt.   0x00001000 - Target TMF.\n"
		"\t\t0x7fffffff - For enabling all logs, can be too many logs.\n"
		"\t\t0x1e400000 - Preferred value for capturing essential "
		"debug information (equivalent to old "
		"ql2xextended_error_logging=1).\n"
		"\t\tDo LOGICAL OR of the value to enable more than one level");

पूर्णांक ql2xshअगरtctondsd = 6;
module_param(ql2xshअगरtctondsd, पूर्णांक, S_IRUGO);
MODULE_PARM_DESC(ql2xshअगरtctondsd,
		"Set to control shifting of command type processing "
		"based on total number of SG elements.");

पूर्णांक ql2xfdmienable = 1;
module_param(ql2xfdmienable, पूर्णांक, S_IRUGO|S_IWUSR);
module_param_named(fdmi, ql2xfdmienable, पूर्णांक, S_IRUGO|S_IWUSR);
MODULE_PARM_DESC(ql2xfdmienable,
		"Enables FDMI registrations. "
		"0 - no FDMI registrations. "
		"1 - provide FDMI registrations (default).");

#घोषणा MAX_Q_DEPTH	64
अटल पूर्णांक ql2xmaxqdepth = MAX_Q_DEPTH;
module_param(ql2xmaxqdepth, पूर्णांक, S_IRUGO|S_IWUSR);
MODULE_PARM_DESC(ql2xmaxqdepth,
		"Maximum queue depth to set for each LUN. "
		"Default is 64.");

पूर्णांक ql2xenabledअगर = 2;
module_param(ql2xenabledअगर, पूर्णांक, S_IRUGO);
MODULE_PARM_DESC(ql2xenabledअगर,
		" Enable T10-CRC-DIF:\n"
		" Default is 2.\n"
		"  0 -- No DIF Support\n"
		"  1 -- Enable DIF for all types\n"
		"  2 -- Enable DIF for all types, except Type 0.\n");

#अगर (IS_ENABLED(CONFIG_NVME_FC))
पूर्णांक ql2xnvmeenable = 1;
#अन्यथा
पूर्णांक ql2xnvmeenable;
#पूर्ण_अगर
module_param(ql2xnvmeenable, पूर्णांक, 0644);
MODULE_PARM_DESC(ql2xnvmeenable,
    "Enables NVME support. "
    "0 - no NVMe.  Default is Y");

पूर्णांक ql2xenablehba_err_chk = 2;
module_param(ql2xenablehba_err_chk, पूर्णांक, S_IRUGO|S_IWUSR);
MODULE_PARM_DESC(ql2xenablehba_err_chk,
		" Enable T10-CRC-DIF Error isolation by HBA:\n"
		" Default is 2.\n"
		"  0 -- Error isolation disabled\n"
		"  1 -- Error isolation enabled only for DIX Type 0\n"
		"  2 -- Error isolation enabled for all Types\n");

पूर्णांक ql2xiidmaenable = 1;
module_param(ql2xiidmaenable, पूर्णांक, S_IRUGO);
MODULE_PARM_DESC(ql2xiidmaenable,
		"Enables iIDMA settings "
		"Default is 1 - perform iIDMA. 0 - no iIDMA.");

पूर्णांक ql2xmqsupport = 1;
module_param(ql2xmqsupport, पूर्णांक, S_IRUGO);
MODULE_PARM_DESC(ql2xmqsupport,
		"Enable on demand multiple queue pairs support "
		"Default is 1 for supported. "
		"Set it to 0 to turn off mq qpair support.");

पूर्णांक ql2xfwloadbin;
module_param(ql2xfwloadbin, पूर्णांक, S_IRUGO|S_IWUSR);
module_param_named(fwload, ql2xfwloadbin, पूर्णांक, S_IRUGO|S_IWUSR);
MODULE_PARM_DESC(ql2xfwloadbin,
		"Option to specify location from which to load ISP firmware:.\n"
		" 2 -- load firmware via the request_firmware() (hotplug).\n"
		"      interface.\n"
		" 1 -- load firmware from flash.\n"
		" 0 -- use default semantics.\n");

पूर्णांक ql2xetsenable;
module_param(ql2xetsenable, पूर्णांक, S_IRUGO);
MODULE_PARM_DESC(ql2xetsenable,
		"Enables firmware ETS burst."
		"Default is 0 - skip ETS enablement.");

पूर्णांक ql2xdbwr = 1;
module_param(ql2xdbwr, पूर्णांक, S_IRUGO|S_IWUSR);
MODULE_PARM_DESC(ql2xdbwr,
		"Option to specify scheme for request queue posting.\n"
		" 0 -- Regular doorbell.\n"
		" 1 -- CAMRAM doorbell (faster).\n");

पूर्णांक ql2xtargetreset = 1;
module_param(ql2xtargetreset, पूर्णांक, S_IRUGO);
MODULE_PARM_DESC(ql2xtargetreset,
		 "Enable target reset."
		 "Default is 1 - use hw defaults.");

पूर्णांक ql2xgffidenable;
module_param(ql2xgffidenable, पूर्णांक, S_IRUGO);
MODULE_PARM_DESC(ql2xgffidenable,
		"Enables GFF_ID checks of port type. "
		"Default is 0 - Do not use GFF_ID information.");

पूर्णांक ql2xasyncपंचांगfenable = 1;
module_param(ql2xasyncपंचांगfenable, पूर्णांक, S_IRUGO);
MODULE_PARM_DESC(ql2xasyncपंचांगfenable,
		"Enables issue of TM IOCBs asynchronously via IOCB mechanism"
		"Default is 1 - Issue TM IOCBs via mailbox mechanism.");

पूर्णांक ql2xकरोntresethba;
module_param(ql2xकरोntresethba, पूर्णांक, S_IRUGO|S_IWUSR);
MODULE_PARM_DESC(ql2xकरोntresethba,
		"Option to specify reset behaviour.\n"
		" 0 (Default) -- Reset on failure.\n"
		" 1 -- Do not reset on failure.\n");

uपूर्णांक64_t ql2xmaxlun = MAX_LUNS;
module_param(ql2xmaxlun, ulदीर्घ, S_IRUGO);
MODULE_PARM_DESC(ql2xmaxlun,
		"Defines the maximum LU number to register with the SCSI "
		"midlayer. Default is 65535.");

पूर्णांक ql2xmdcapmask = 0x1F;
module_param(ql2xmdcapmask, पूर्णांक, S_IRUGO);
MODULE_PARM_DESC(ql2xmdcapmask,
		"Set the Minidump driver capture mask level. "
		"Default is 0x1F - Can be set to 0x3, 0x7, 0xF, 0x1F, 0x7F.");

पूर्णांक ql2xmdenable = 1;
module_param(ql2xmdenable, पूर्णांक, S_IRUGO);
MODULE_PARM_DESC(ql2xmdenable,
		"Enable/disable MiniDump. "
		"0 - MiniDump disabled. "
		"1 (Default) - MiniDump enabled.");

पूर्णांक ql2xexlogins;
module_param(ql2xexlogins, uपूर्णांक, S_IRUGO|S_IWUSR);
MODULE_PARM_DESC(ql2xexlogins,
		 "Number of extended Logins. "
		 "0 (Default)- Disabled.");

पूर्णांक ql2xexchoffld = 1024;
module_param(ql2xexchoffld, uपूर्णांक, 0644);
MODULE_PARM_DESC(ql2xexchoffld,
	"Number of target exchanges.");

पूर्णांक ql2xiniexchg = 1024;
module_param(ql2xiniexchg, uपूर्णांक, 0644);
MODULE_PARM_DESC(ql2xiniexchg,
	"Number of initiator exchanges.");

पूर्णांक ql2xfwholdabts;
module_param(ql2xfwholdabts, पूर्णांक, S_IRUGO);
MODULE_PARM_DESC(ql2xfwholdabts,
		"Allow FW to hold status IOCB until ABTS rsp received. "
		"0 (Default) Do not set fw option. "
		"1 - Set fw option to hold ABTS.");

पूर्णांक ql2xmvasynctoatio = 1;
module_param(ql2xmvasynctoatio, पूर्णांक, S_IRUGO|S_IWUSR);
MODULE_PARM_DESC(ql2xmvasynctoatio,
		"Move PUREX, ABTS RX and RIDA IOCBs to ATIOQ"
		"0 (Default). Do not move IOCBs"
		"1 - Move IOCBs.");

पूर्णांक ql2xस्वतःdetectsfp = 1;
module_param(ql2xस्वतःdetectsfp, पूर्णांक, 0444);
MODULE_PARM_DESC(ql2xस्वतःdetectsfp,
		 "Detect SFP range and set appropriate distance.\n"
		 "1 (Default): Enable\n");

पूर्णांक ql2xenablemsix = 1;
module_param(ql2xenablemsix, पूर्णांक, 0444);
MODULE_PARM_DESC(ql2xenablemsix,
		 "Set to enable MSI or MSI-X interrupt mechanism.\n"
		 " Default is 1, enable MSI-X interrupt mechanism.\n"
		 " 0 -- enable traditional pin-based mechanism.\n"
		 " 1 -- enable MSI-X interrupt mechanism.\n"
		 " 2 -- enable MSI interrupt mechanism.\n");

पूर्णांक qla2xuseresexchक्रमels;
module_param(qla2xuseresexchक्रमels, पूर्णांक, 0444);
MODULE_PARM_DESC(qla2xuseresexchक्रमels,
		 "Reserve 1/2 of emergency exchanges for ELS.\n"
		 " 0 (default): disabled");

अटल पूर्णांक ql2xproपंचांगask;
module_param(ql2xproपंचांगask, पूर्णांक, 0644);
MODULE_PARM_DESC(ql2xproपंचांगask,
		 "Override DIF/DIX protection capabilities mask\n"
		 "Default is 0 which sets protection mask based on "
		 "capabilities reported by HBA firmware.\n");

अटल पूर्णांक ql2xprotguard;
module_param(ql2xprotguard, पूर्णांक, 0644);
MODULE_PARM_DESC(ql2xprotguard, "Override choice of DIX checksum\n"
		 "  0 -- Let HBA firmware decide\n"
		 "  1 -- Force T10 CRC\n"
		 "  2 -- Force IP checksum\n");

पूर्णांक ql2xdअगरbundlingपूर्णांकernalbuffers;
module_param(ql2xdअगरbundlingपूर्णांकernalbuffers, पूर्णांक, 0644);
MODULE_PARM_DESC(ql2xdअगरbundlingपूर्णांकernalbuffers,
    "Force using internal buffers for DIF information\n"
    "0 (Default). Based on check.\n"
    "1 Force using internal buffers\n");

पूर्णांक ql2xsmartsan;
module_param(ql2xsmartsan, पूर्णांक, 0444);
module_param_named(smartsan, ql2xsmartsan, पूर्णांक, 0444);
MODULE_PARM_DESC(ql2xsmartsan,
		"Send SmartSAN Management Attributes for FDMI Registration."
		" Default is 0 - No SmartSAN registration,"
		" 1 - Register SmartSAN Management Attributes.");

पूर्णांक ql2xrdpenable;
module_param(ql2xrdpenable, पूर्णांक, 0444);
module_param_named(rdpenable, ql2xrdpenable, पूर्णांक, 0444);
MODULE_PARM_DESC(ql2xrdpenable,
		"Enables RDP responses. "
		"0 - no RDP responses (default). "
		"1 - provide RDP responses.");
पूर्णांक ql2xabts_रुको_nvme = 1;
module_param(ql2xabts_रुको_nvme, पूर्णांक, 0444);
MODULE_PARM_DESC(ql2xabts_रुको_nvme,
		 "To wait for ABTS response on I/O timeouts for NVMe. (default: 1)");


अटल व्योम qla2x00_clear_drv_active(काष्ठा qla_hw_data *);
अटल व्योम qla2x00_मुक्त_device(scsi_qla_host_t *);
अटल पूर्णांक qla2xxx_map_queues(काष्ठा Scsi_Host *shost);
अटल व्योम qla2x00_destroy_deferred_work(काष्ठा qla_hw_data *);


अटल काष्ठा scsi_transport_ढाँचा *qla2xxx_transport_ढाँचा = शून्य;
काष्ठा scsi_transport_ढाँचा *qla2xxx_transport_vport_ढाँचा = शून्य;

/* TODO Convert to अंतरभूतs
 *
 * Timer routines
 */

__अंतरभूत__ व्योम
qla2x00_start_समयr(scsi_qla_host_t *vha, अचिन्हित दीर्घ पूर्णांकerval)
अणु
	समयr_setup(&vha->समयr, qla2x00_समयr, 0);
	vha->समयr.expires = jअगरfies + पूर्णांकerval * HZ;
	add_समयr(&vha->समयr);
	vha->समयr_active = 1;
पूर्ण

अटल अंतरभूत व्योम
qla2x00_restart_समयr(scsi_qla_host_t *vha, अचिन्हित दीर्घ पूर्णांकerval)
अणु
	/* Currently used क्रम 82XX only. */
	अगर (vha->device_flags & DFLG_DEV_FAILED) अणु
		ql_dbg(ql_dbg_समयr, vha, 0x600d,
		    "Device in a failed state, returning.\n");
		वापस;
	पूर्ण

	mod_समयr(&vha->समयr, jअगरfies + पूर्णांकerval * HZ);
पूर्ण

अटल __अंतरभूत__ व्योम
qla2x00_stop_समयr(scsi_qla_host_t *vha)
अणु
	del_समयr_sync(&vha->समयr);
	vha->समयr_active = 0;
पूर्ण

अटल पूर्णांक qla2x00_करो_dpc(व्योम *data);

अटल व्योम qla2x00_rst_aen(scsi_qla_host_t *);

अटल पूर्णांक qla2x00_mem_alloc(काष्ठा qla_hw_data *, uपूर्णांक16_t, uपूर्णांक16_t,
	काष्ठा req_que **, काष्ठा rsp_que **);
अटल व्योम qla2x00_मुक्त_fw_dump(काष्ठा qla_hw_data *);
अटल व्योम qla2x00_mem_मुक्त(काष्ठा qla_hw_data *);
पूर्णांक qla2xxx_mqueuecommand(काष्ठा Scsi_Host *host, काष्ठा scsi_cmnd *cmd,
	काष्ठा qla_qpair *qpair);

/* -------------------------------------------------------------------------- */
अटल व्योम qla_init_base_qpair(काष्ठा scsi_qla_host *vha, काष्ठा req_que *req,
    काष्ठा rsp_que *rsp)
अणु
	काष्ठा qla_hw_data *ha = vha->hw;

	rsp->qpair = ha->base_qpair;
	rsp->req = req;
	ha->base_qpair->hw = ha;
	ha->base_qpair->req = req;
	ha->base_qpair->rsp = rsp;
	ha->base_qpair->vha = vha;
	ha->base_qpair->qp_lock_ptr = &ha->hardware_lock;
	ha->base_qpair->use_shaकरोw_reg = IS_SHADOW_REG_CAPABLE(ha) ? 1 : 0;
	ha->base_qpair->msix = &ha->msix_entries[QLA_MSIX_RSP_Q];
	ha->base_qpair->srb_mempool = ha->srb_mempool;
	INIT_LIST_HEAD(&ha->base_qpair->hपूर्णांकs_list);
	ha->base_qpair->enable_class_2 = ql2xenableclass2;
	/* init qpair to this cpu. Will adjust at run समय. */
	qla_cpu_update(rsp->qpair, raw_smp_processor_id());
	ha->base_qpair->pdev = ha->pdev;

	अगर (IS_QLA27XX(ha) || IS_QLA83XX(ha) || IS_QLA28XX(ha))
		ha->base_qpair->reqq_start_iocbs = qla_83xx_start_iocbs;
पूर्ण

अटल पूर्णांक qla2x00_alloc_queues(काष्ठा qla_hw_data *ha, काष्ठा req_que *req,
				काष्ठा rsp_que *rsp)
अणु
	scsi_qla_host_t *vha = pci_get_drvdata(ha->pdev);

	ha->req_q_map = kसुस्मृति(ha->max_req_queues, माप(काष्ठा req_que *),
				GFP_KERNEL);
	अगर (!ha->req_q_map) अणु
		ql_log(ql_log_fatal, vha, 0x003b,
		    "Unable to allocate memory for request queue ptrs.\n");
		जाओ fail_req_map;
	पूर्ण

	ha->rsp_q_map = kसुस्मृति(ha->max_rsp_queues, माप(काष्ठा rsp_que *),
				GFP_KERNEL);
	अगर (!ha->rsp_q_map) अणु
		ql_log(ql_log_fatal, vha, 0x003c,
		    "Unable to allocate memory for response queue ptrs.\n");
		जाओ fail_rsp_map;
	पूर्ण

	ha->base_qpair = kzalloc(माप(काष्ठा qla_qpair), GFP_KERNEL);
	अगर (ha->base_qpair == शून्य) अणु
		ql_log(ql_log_warn, vha, 0x00e0,
		    "Failed to allocate base queue pair memory.\n");
		जाओ fail_base_qpair;
	पूर्ण

	qla_init_base_qpair(vha, req, rsp);

	अगर ((ql2xmqsupport || ql2xnvmeenable) && ha->max_qpairs) अणु
		ha->queue_pair_map = kसुस्मृति(ha->max_qpairs, माप(काष्ठा qla_qpair *),
			GFP_KERNEL);
		अगर (!ha->queue_pair_map) अणु
			ql_log(ql_log_fatal, vha, 0x0180,
			    "Unable to allocate memory for queue pair ptrs.\n");
			जाओ fail_qpair_map;
		पूर्ण
	पूर्ण

	/*
	 * Make sure we record at least the request and response queue zero in
	 * हाल we need to मुक्त them अगर part of the probe fails.
	 */
	ha->rsp_q_map[0] = rsp;
	ha->req_q_map[0] = req;
	set_bit(0, ha->rsp_qid_map);
	set_bit(0, ha->req_qid_map);
	वापस 0;

fail_qpair_map:
	kमुक्त(ha->base_qpair);
	ha->base_qpair = शून्य;
fail_base_qpair:
	kमुक्त(ha->rsp_q_map);
	ha->rsp_q_map = शून्य;
fail_rsp_map:
	kमुक्त(ha->req_q_map);
	ha->req_q_map = शून्य;
fail_req_map:
	वापस -ENOMEM;
पूर्ण

अटल व्योम qla2x00_मुक्त_req_que(काष्ठा qla_hw_data *ha, काष्ठा req_que *req)
अणु
	अगर (IS_QLAFX00(ha)) अणु
		अगर (req && req->ring_fx00)
			dma_मुक्त_coherent(&ha->pdev->dev,
			    (req->length_fx00 + 1) * माप(request_t),
			    req->ring_fx00, req->dma_fx00);
	पूर्ण अन्यथा अगर (req && req->ring)
		dma_मुक्त_coherent(&ha->pdev->dev,
		(req->length + 1) * माप(request_t),
		req->ring, req->dma);

	अगर (req)
		kमुक्त(req->outstanding_cmds);

	kमुक्त(req);
पूर्ण

अटल व्योम qla2x00_मुक्त_rsp_que(काष्ठा qla_hw_data *ha, काष्ठा rsp_que *rsp)
अणु
	अगर (IS_QLAFX00(ha)) अणु
		अगर (rsp && rsp->ring_fx00)
			dma_मुक्त_coherent(&ha->pdev->dev,
			    (rsp->length_fx00 + 1) * माप(request_t),
			    rsp->ring_fx00, rsp->dma_fx00);
	पूर्ण अन्यथा अगर (rsp && rsp->ring) अणु
		dma_मुक्त_coherent(&ha->pdev->dev,
		(rsp->length + 1) * माप(response_t),
		rsp->ring, rsp->dma);
	पूर्ण
	kमुक्त(rsp);
पूर्ण

अटल व्योम qla2x00_मुक्त_queues(काष्ठा qla_hw_data *ha)
अणु
	काष्ठा req_que *req;
	काष्ठा rsp_que *rsp;
	पूर्णांक cnt;
	अचिन्हित दीर्घ flags;

	अगर (ha->queue_pair_map) अणु
		kमुक्त(ha->queue_pair_map);
		ha->queue_pair_map = शून्य;
	पूर्ण
	अगर (ha->base_qpair) अणु
		kमुक्त(ha->base_qpair);
		ha->base_qpair = शून्य;
	पूर्ण

	spin_lock_irqsave(&ha->hardware_lock, flags);
	क्रम (cnt = 0; cnt < ha->max_req_queues; cnt++) अणु
		अगर (!test_bit(cnt, ha->req_qid_map))
			जारी;

		req = ha->req_q_map[cnt];
		clear_bit(cnt, ha->req_qid_map);
		ha->req_q_map[cnt] = शून्य;

		spin_unlock_irqrestore(&ha->hardware_lock, flags);
		qla2x00_मुक्त_req_que(ha, req);
		spin_lock_irqsave(&ha->hardware_lock, flags);
	पूर्ण
	spin_unlock_irqrestore(&ha->hardware_lock, flags);

	kमुक्त(ha->req_q_map);
	ha->req_q_map = शून्य;


	spin_lock_irqsave(&ha->hardware_lock, flags);
	क्रम (cnt = 0; cnt < ha->max_rsp_queues; cnt++) अणु
		अगर (!test_bit(cnt, ha->rsp_qid_map))
			जारी;

		rsp = ha->rsp_q_map[cnt];
		clear_bit(cnt, ha->rsp_qid_map);
		ha->rsp_q_map[cnt] =  शून्य;
		spin_unlock_irqrestore(&ha->hardware_lock, flags);
		qla2x00_मुक्त_rsp_que(ha, rsp);
		spin_lock_irqsave(&ha->hardware_lock, flags);
	पूर्ण
	spin_unlock_irqrestore(&ha->hardware_lock, flags);

	kमुक्त(ha->rsp_q_map);
	ha->rsp_q_map = शून्य;
पूर्ण

अटल अक्षर *
qla2x00_pci_info_str(काष्ठा scsi_qla_host *vha, अक्षर *str, माप_प्रकार str_len)
अणु
	काष्ठा qla_hw_data *ha = vha->hw;
	अटल स्थिर अक्षर *स्थिर pci_bus_modes[] = अणु
		"33", "66", "100", "133",
	पूर्ण;
	uपूर्णांक16_t pci_bus;

	pci_bus = (ha->pci_attr & (BIT_9 | BIT_10)) >> 9;
	अगर (pci_bus) अणु
		snम_लिखो(str, str_len, "PCI-X (%s MHz)",
			 pci_bus_modes[pci_bus]);
	पूर्ण अन्यथा अणु
		pci_bus = (ha->pci_attr & BIT_8) >> 8;
		snम_लिखो(str, str_len, "PCI (%s MHz)", pci_bus_modes[pci_bus]);
	पूर्ण

	वापस str;
पूर्ण

अटल अक्षर *
qla24xx_pci_info_str(काष्ठा scsi_qla_host *vha, अक्षर *str, माप_प्रकार str_len)
अणु
	अटल स्थिर अक्षर *स्थिर pci_bus_modes[] = अणु
		"33", "66", "100", "133",
	पूर्ण;
	काष्ठा qla_hw_data *ha = vha->hw;
	uपूर्णांक32_t pci_bus;

	अगर (pci_is_pcie(ha->pdev)) अणु
		uपूर्णांक32_t lstat, lspeed, lwidth;
		स्थिर अक्षर *speed_str;

		pcie_capability_पढ़ो_dword(ha->pdev, PCI_EXP_LNKCAP, &lstat);
		lspeed = lstat & PCI_EXP_LNKCAP_SLS;
		lwidth = (lstat & PCI_EXP_LNKCAP_MLW) >> 4;

		चयन (lspeed) अणु
		हाल 1:
			speed_str = "2.5GT/s";
			अवरोध;
		हाल 2:
			speed_str = "5.0GT/s";
			अवरोध;
		हाल 3:
			speed_str = "8.0GT/s";
			अवरोध;
		हाल 4:
			speed_str = "16.0GT/s";
			अवरोध;
		शेष:
			speed_str = "<unknown>";
			अवरोध;
		पूर्ण
		snम_लिखो(str, str_len, "PCIe (%s x%d)", speed_str, lwidth);

		वापस str;
	पूर्ण

	pci_bus = (ha->pci_attr & CSRX_PCIX_BUS_MODE_MASK) >> 8;
	अगर (pci_bus == 0 || pci_bus == 8)
		snम_लिखो(str, str_len, "PCI (%s MHz)",
			 pci_bus_modes[pci_bus >> 3]);
	अन्यथा
		snम_लिखो(str, str_len, "PCI-X Mode %d (%s MHz)",
			 pci_bus & 4 ? 2 : 1,
			 pci_bus_modes[pci_bus & 3]);

	वापस str;
पूर्ण

अटल अक्षर *
qla2x00_fw_version_str(काष्ठा scsi_qla_host *vha, अक्षर *str, माप_प्रकार size)
अणु
	अक्षर un_str[10];
	काष्ठा qla_hw_data *ha = vha->hw;

	snम_लिखो(str, size, "%d.%02d.%02d ", ha->fw_major_version,
	    ha->fw_minor_version, ha->fw_subminor_version);

	अगर (ha->fw_attributes & BIT_9) अणु
		म_जोड़ो(str, "FLX");
		वापस (str);
	पूर्ण

	चयन (ha->fw_attributes & 0xFF) अणु
	हाल 0x7:
		म_जोड़ो(str, "EF");
		अवरोध;
	हाल 0x17:
		म_जोड़ो(str, "TP");
		अवरोध;
	हाल 0x37:
		म_जोड़ो(str, "IP");
		अवरोध;
	हाल 0x77:
		म_जोड़ो(str, "VI");
		अवरोध;
	शेष:
		प्र_लिखो(un_str, "(%x)", ha->fw_attributes);
		म_जोड़ो(str, un_str);
		अवरोध;
	पूर्ण
	अगर (ha->fw_attributes & 0x100)
		म_जोड़ो(str, "X");

	वापस (str);
पूर्ण

अटल अक्षर *
qla24xx_fw_version_str(काष्ठा scsi_qla_host *vha, अक्षर *str, माप_प्रकार size)
अणु
	काष्ठा qla_hw_data *ha = vha->hw;

	snम_लिखो(str, size, "%d.%02d.%02d (%x)", ha->fw_major_version,
	    ha->fw_minor_version, ha->fw_subminor_version, ha->fw_attributes);
	वापस str;
पूर्ण

व्योम qla2x00_sp_मुक्त_dma(srb_t *sp)
अणु
	काष्ठा qla_hw_data *ha = sp->vha->hw;
	काष्ठा scsi_cmnd *cmd = GET_CMD_SP(sp);

	अगर (sp->flags & SRB_DMA_VALID) अणु
		scsi_dma_unmap(cmd);
		sp->flags &= ~SRB_DMA_VALID;
	पूर्ण

	अगर (sp->flags & SRB_CRC_PROT_DMA_VALID) अणु
		dma_unmap_sg(&ha->pdev->dev, scsi_prot_sglist(cmd),
		    scsi_prot_sg_count(cmd), cmd->sc_data_direction);
		sp->flags &= ~SRB_CRC_PROT_DMA_VALID;
	पूर्ण

	अगर (sp->flags & SRB_CRC_CTX_DSD_VALID) अणु
		/* List assured to be having elements */
		qla2x00_clean_dsd_pool(ha, sp->u.scmd.crc_ctx);
		sp->flags &= ~SRB_CRC_CTX_DSD_VALID;
	पूर्ण

	अगर (sp->flags & SRB_CRC_CTX_DMA_VALID) अणु
		काष्ठा crc_context *ctx0 = sp->u.scmd.crc_ctx;

		dma_pool_मुक्त(ha->dl_dma_pool, ctx0, ctx0->crc_ctx_dma);
		sp->flags &= ~SRB_CRC_CTX_DMA_VALID;
	पूर्ण

	अगर (sp->flags & SRB_FCP_CMND_DMA_VALID) अणु
		काष्ठा ct6_dsd *ctx1 = sp->u.scmd.ct6_ctx;

		dma_pool_मुक्त(ha->fcp_cmnd_dma_pool, ctx1->fcp_cmnd,
		    ctx1->fcp_cmnd_dma);
		list_splice(&ctx1->dsd_list, &ha->gbl_dsd_list);
		ha->gbl_dsd_inuse -= ctx1->dsd_use_cnt;
		ha->gbl_dsd_avail += ctx1->dsd_use_cnt;
		mempool_मुक्त(ctx1, ha->ctx_mempool);
	पूर्ण
पूर्ण

व्योम qla2x00_sp_compl(srb_t *sp, पूर्णांक res)
अणु
	काष्ठा scsi_cmnd *cmd = GET_CMD_SP(sp);
	काष्ठा completion *comp = sp->comp;

	sp->मुक्त(sp);
	cmd->result = res;
	CMD_SP(cmd) = शून्य;
	cmd->scsi_करोne(cmd);
	अगर (comp)
		complete(comp);
पूर्ण

व्योम qla2xxx_qpair_sp_मुक्त_dma(srb_t *sp)
अणु
	काष्ठा scsi_cmnd *cmd = GET_CMD_SP(sp);
	काष्ठा qla_hw_data *ha = sp->fcport->vha->hw;

	अगर (sp->flags & SRB_DMA_VALID) अणु
		scsi_dma_unmap(cmd);
		sp->flags &= ~SRB_DMA_VALID;
	पूर्ण

	अगर (sp->flags & SRB_CRC_PROT_DMA_VALID) अणु
		dma_unmap_sg(&ha->pdev->dev, scsi_prot_sglist(cmd),
		    scsi_prot_sg_count(cmd), cmd->sc_data_direction);
		sp->flags &= ~SRB_CRC_PROT_DMA_VALID;
	पूर्ण

	अगर (sp->flags & SRB_CRC_CTX_DSD_VALID) अणु
		/* List assured to be having elements */
		qla2x00_clean_dsd_pool(ha, sp->u.scmd.crc_ctx);
		sp->flags &= ~SRB_CRC_CTX_DSD_VALID;
	पूर्ण

	अगर (sp->flags & SRB_DIF_BUNDL_DMA_VALID) अणु
		काष्ठा crc_context *dअगरctx = sp->u.scmd.crc_ctx;
		काष्ठा dsd_dma *dअगर_dsd, *nxt_dsd;

		list_क्रम_each_entry_safe(dअगर_dsd, nxt_dsd,
		    &dअगरctx->ldअगर_dma_hndl_list, list) अणु
			list_del(&dअगर_dsd->list);
			dma_pool_मुक्त(ha->dअगर_bundl_pool, dअगर_dsd->dsd_addr,
			    dअगर_dsd->dsd_list_dma);
			kमुक्त(dअगर_dsd);
			dअगरctx->no_dअगर_bundl--;
		पूर्ण

		list_क्रम_each_entry_safe(dअगर_dsd, nxt_dsd,
		    &dअगरctx->ldअगर_dsd_list, list) अणु
			list_del(&dअगर_dsd->list);
			dma_pool_मुक्त(ha->dl_dma_pool, dअगर_dsd->dsd_addr,
			    dअगर_dsd->dsd_list_dma);
			kमुक्त(dअगर_dsd);
			dअगरctx->no_ldअगर_dsd--;
		पूर्ण

		अगर (dअगरctx->no_ldअगर_dsd) अणु
			ql_dbg(ql_dbg_tgt+ql_dbg_verbose, sp->vha, 0xe022,
			    "%s: difctx->no_ldif_dsd=%x\n",
			    __func__, dअगरctx->no_ldअगर_dsd);
		पूर्ण

		अगर (dअगरctx->no_dअगर_bundl) अणु
			ql_dbg(ql_dbg_tgt+ql_dbg_verbose, sp->vha, 0xe022,
			    "%s: difctx->no_dif_bundl=%x\n",
			    __func__, dअगरctx->no_dअगर_bundl);
		पूर्ण
		sp->flags &= ~SRB_DIF_BUNDL_DMA_VALID;
	पूर्ण

	अगर (sp->flags & SRB_FCP_CMND_DMA_VALID) अणु
		काष्ठा ct6_dsd *ctx1 = sp->u.scmd.ct6_ctx;

		dma_pool_मुक्त(ha->fcp_cmnd_dma_pool, ctx1->fcp_cmnd,
		    ctx1->fcp_cmnd_dma);
		list_splice(&ctx1->dsd_list, &ha->gbl_dsd_list);
		ha->gbl_dsd_inuse -= ctx1->dsd_use_cnt;
		ha->gbl_dsd_avail += ctx1->dsd_use_cnt;
		mempool_मुक्त(ctx1, ha->ctx_mempool);
		sp->flags &= ~SRB_FCP_CMND_DMA_VALID;
	पूर्ण

	अगर (sp->flags & SRB_CRC_CTX_DMA_VALID) अणु
		काष्ठा crc_context *ctx0 = sp->u.scmd.crc_ctx;

		dma_pool_मुक्त(ha->dl_dma_pool, ctx0, ctx0->crc_ctx_dma);
		sp->flags &= ~SRB_CRC_CTX_DMA_VALID;
	पूर्ण
पूर्ण

व्योम qla2xxx_qpair_sp_compl(srb_t *sp, पूर्णांक res)
अणु
	काष्ठा scsi_cmnd *cmd = GET_CMD_SP(sp);
	काष्ठा completion *comp = sp->comp;

	sp->मुक्त(sp);
	cmd->result = res;
	CMD_SP(cmd) = शून्य;
	cmd->scsi_करोne(cmd);
	अगर (comp)
		complete(comp);
पूर्ण

अटल पूर्णांक
qla2xxx_queuecommand(काष्ठा Scsi_Host *host, काष्ठा scsi_cmnd *cmd)
अणु
	scsi_qla_host_t *vha = shost_priv(host);
	fc_port_t *fcport = (काष्ठा fc_port *) cmd->device->hostdata;
	काष्ठा fc_rport *rport = starget_to_rport(scsi_target(cmd->device));
	काष्ठा qla_hw_data *ha = vha->hw;
	काष्ठा scsi_qla_host *base_vha = pci_get_drvdata(ha->pdev);
	srb_t *sp;
	पूर्णांक rval;

	अगर (unlikely(test_bit(UNLOADING, &base_vha->dpc_flags)) ||
	    WARN_ON_ONCE(!rport)) अणु
		cmd->result = DID_NO_CONNECT << 16;
		जाओ qc24_fail_command;
	पूर्ण

	अगर (ha->mqenable) अणु
		uपूर्णांक32_t tag;
		uपूर्णांक16_t hwq;
		काष्ठा qla_qpair *qpair = शून्य;

		tag = blk_mq_unique_tag(cmd->request);
		hwq = blk_mq_unique_tag_to_hwq(tag);
		qpair = ha->queue_pair_map[hwq];

		अगर (qpair)
			वापस qla2xxx_mqueuecommand(host, cmd, qpair);
	पूर्ण

	अगर (ha->flags.eeh_busy) अणु
		अगर (ha->flags.pci_channel_io_perm_failure) अणु
			ql_dbg(ql_dbg_aer, vha, 0x9010,
			    "PCI Channel IO permanent failure, exiting "
			    "cmd=%p.\n", cmd);
			cmd->result = DID_NO_CONNECT << 16;
		पूर्ण अन्यथा अणु
			ql_dbg(ql_dbg_aer, vha, 0x9011,
			    "EEH_Busy, Requeuing the cmd=%p.\n", cmd);
			cmd->result = DID_REQUEUE << 16;
		पूर्ण
		जाओ qc24_fail_command;
	पूर्ण

	rval = fc_remote_port_chkपढ़ोy(rport);
	अगर (rval) अणु
		cmd->result = rval;
		ql_dbg(ql_dbg_io + ql_dbg_verbose, vha, 0x3003,
		    "fc_remote_port_chkready failed for cmd=%p, rval=0x%x.\n",
		    cmd, rval);
		जाओ qc24_fail_command;
	पूर्ण

	अगर (!vha->flags.dअगरdix_supported &&
		scsi_get_prot_op(cmd) != SCSI_PROT_NORMAL) अणु
			ql_dbg(ql_dbg_io, vha, 0x3004,
			    "DIF Cap not reg, fail DIF capable cmd's:%p.\n",
			    cmd);
			cmd->result = DID_NO_CONNECT << 16;
			जाओ qc24_fail_command;
	पूर्ण

	अगर (!fcport || fcport->deleted) अणु
		cmd->result = DID_IMM_RETRY << 16;
		जाओ qc24_fail_command;
	पूर्ण

	अगर (atomic_पढ़ो(&fcport->state) != FCS_ONLINE || fcport->deleted) अणु
		अगर (atomic_पढ़ो(&fcport->state) == FCS_DEVICE_DEAD ||
			atomic_पढ़ो(&base_vha->loop_state) == LOOP_DEAD) अणु
			ql_dbg(ql_dbg_io, vha, 0x3005,
			    "Returning DNC, fcport_state=%d loop_state=%d.\n",
			    atomic_पढ़ो(&fcport->state),
			    atomic_पढ़ो(&base_vha->loop_state));
			cmd->result = DID_NO_CONNECT << 16;
			जाओ qc24_fail_command;
		पूर्ण
		जाओ qc24_target_busy;
	पूर्ण

	/*
	 * Return target busy अगर we've received a non-zero retry_delay_समयr
	 * in a FCP_RSP.
	 */
	अगर (fcport->retry_delay_बारtamp == 0) अणु
		/* retry delay not set */
	पूर्ण अन्यथा अगर (समय_after(jअगरfies, fcport->retry_delay_बारtamp))
		fcport->retry_delay_बारtamp = 0;
	अन्यथा
		जाओ qc24_target_busy;

	sp = scsi_cmd_priv(cmd);
	qla2xxx_init_sp(sp, vha, vha->hw->base_qpair, fcport);

	sp->u.scmd.cmd = cmd;
	sp->type = SRB_SCSI_CMD;

	CMD_SP(cmd) = (व्योम *)sp;
	sp->मुक्त = qla2x00_sp_मुक्त_dma;
	sp->करोne = qla2x00_sp_compl;

	rval = ha->isp_ops->start_scsi(sp);
	अगर (rval != QLA_SUCCESS) अणु
		ql_dbg(ql_dbg_io + ql_dbg_verbose, vha, 0x3013,
		    "Start scsi failed rval=%d for cmd=%p.\n", rval, cmd);
		जाओ qc24_host_busy_मुक्त_sp;
	पूर्ण

	वापस 0;

qc24_host_busy_मुक्त_sp:
	sp->मुक्त(sp);

qc24_target_busy:
	वापस SCSI_MLQUEUE_TARGET_BUSY;

qc24_fail_command:
	cmd->scsi_करोne(cmd);

	वापस 0;
पूर्ण

/* For MQ supported I/O */
पूर्णांक
qla2xxx_mqueuecommand(काष्ठा Scsi_Host *host, काष्ठा scsi_cmnd *cmd,
    काष्ठा qla_qpair *qpair)
अणु
	scsi_qla_host_t *vha = shost_priv(host);
	fc_port_t *fcport = (काष्ठा fc_port *) cmd->device->hostdata;
	काष्ठा fc_rport *rport = starget_to_rport(scsi_target(cmd->device));
	काष्ठा qla_hw_data *ha = vha->hw;
	काष्ठा scsi_qla_host *base_vha = pci_get_drvdata(ha->pdev);
	srb_t *sp;
	पूर्णांक rval;

	rval = rport ? fc_remote_port_chkपढ़ोy(rport) : (DID_NO_CONNECT << 16);
	अगर (rval) अणु
		cmd->result = rval;
		ql_dbg(ql_dbg_io + ql_dbg_verbose, vha, 0x3076,
		    "fc_remote_port_chkready failed for cmd=%p, rval=0x%x.\n",
		    cmd, rval);
		जाओ qc24_fail_command;
	पूर्ण

	अगर (!qpair->online) अणु
		ql_dbg(ql_dbg_io, vha, 0x3077,
		       "qpair not online. eeh_busy=%d.\n", ha->flags.eeh_busy);
		cmd->result = DID_NO_CONNECT << 16;
		जाओ qc24_fail_command;
	पूर्ण

	अगर (!fcport || fcport->deleted) अणु
		cmd->result = DID_IMM_RETRY << 16;
		जाओ qc24_fail_command;
	पूर्ण

	अगर (atomic_पढ़ो(&fcport->state) != FCS_ONLINE || fcport->deleted) अणु
		अगर (atomic_पढ़ो(&fcport->state) == FCS_DEVICE_DEAD ||
			atomic_पढ़ो(&base_vha->loop_state) == LOOP_DEAD) अणु
			ql_dbg(ql_dbg_io, vha, 0x3077,
			    "Returning DNC, fcport_state=%d loop_state=%d.\n",
			    atomic_पढ़ो(&fcport->state),
			    atomic_पढ़ो(&base_vha->loop_state));
			cmd->result = DID_NO_CONNECT << 16;
			जाओ qc24_fail_command;
		पूर्ण
		जाओ qc24_target_busy;
	पूर्ण

	/*
	 * Return target busy अगर we've received a non-zero retry_delay_समयr
	 * in a FCP_RSP.
	 */
	अगर (fcport->retry_delay_बारtamp == 0) अणु
		/* retry delay not set */
	पूर्ण अन्यथा अगर (समय_after(jअगरfies, fcport->retry_delay_बारtamp))
		fcport->retry_delay_बारtamp = 0;
	अन्यथा
		जाओ qc24_target_busy;

	sp = scsi_cmd_priv(cmd);
	qla2xxx_init_sp(sp, vha, qpair, fcport);

	sp->u.scmd.cmd = cmd;
	sp->type = SRB_SCSI_CMD;
	CMD_SP(cmd) = (व्योम *)sp;
	sp->मुक्त = qla2xxx_qpair_sp_मुक्त_dma;
	sp->करोne = qla2xxx_qpair_sp_compl;

	rval = ha->isp_ops->start_scsi_mq(sp);
	अगर (rval != QLA_SUCCESS) अणु
		ql_dbg(ql_dbg_io + ql_dbg_verbose, vha, 0x3078,
		    "Start scsi failed rval=%d for cmd=%p.\n", rval, cmd);
		जाओ qc24_host_busy_मुक्त_sp;
	पूर्ण

	वापस 0;

qc24_host_busy_मुक्त_sp:
	sp->मुक्त(sp);

qc24_target_busy:
	वापस SCSI_MLQUEUE_TARGET_BUSY;

qc24_fail_command:
	cmd->scsi_करोne(cmd);

	वापस 0;
पूर्ण

/*
 * qla2x00_eh_रुको_on_command
 *    Waits क्रम the command to be वापसed by the Firmware क्रम some
 *    max समय.
 *
 * Input:
 *    cmd = Scsi Command to रुको on.
 *
 * Return:
 *    Completed in समय : QLA_SUCCESS
 *    Did not complete in समय : QLA_FUNCTION_FAILED
 */
अटल पूर्णांक
qla2x00_eh_रुको_on_command(काष्ठा scsi_cmnd *cmd)
अणु
#घोषणा ABORT_POLLING_PERIOD	1000
#घोषणा ABORT_WAIT_ITER		((2 * 1000) / (ABORT_POLLING_PERIOD))
	अचिन्हित दीर्घ रुको_iter = ABORT_WAIT_ITER;
	scsi_qla_host_t *vha = shost_priv(cmd->device->host);
	काष्ठा qla_hw_data *ha = vha->hw;
	पूर्णांक ret = QLA_SUCCESS;

	अगर (unlikely(pci_channel_offline(ha->pdev)) || ha->flags.eeh_busy) अणु
		ql_dbg(ql_dbg_taskm, vha, 0x8005,
		    "Return:eh_wait.\n");
		वापस ret;
	पूर्ण

	जबतक (CMD_SP(cmd) && रुको_iter--) अणु
		msleep(ABORT_POLLING_PERIOD);
	पूर्ण
	अगर (CMD_SP(cmd))
		ret = QLA_FUNCTION_FAILED;

	वापस ret;
पूर्ण

/*
 * qla2x00_रुको_क्रम_hba_online
 *    Wait till the HBA is online after going through
 *    <= MAX_RETRIES_OF_ISP_ABORT  or
 *    finally HBA is disabled ie marked offline
 *
 * Input:
 *     ha - poपूर्णांकer to host adapter काष्ठाure
 *
 * Note:
 *    Does context चयनing-Release SPIN_LOCK
 *    (अगर any) beक्रमe calling this routine.
 *
 * Return:
 *    Success (Adapter is online) : 0
 *    Failed  (Adapter is offline/disabled) : 1
 */
पूर्णांक
qla2x00_रुको_क्रम_hba_online(scsi_qla_host_t *vha)
अणु
	पूर्णांक		वापस_status;
	अचिन्हित दीर्घ	रुको_online;
	काष्ठा qla_hw_data *ha = vha->hw;
	scsi_qla_host_t *base_vha = pci_get_drvdata(ha->pdev);

	रुको_online = jअगरfies + (MAX_LOOP_TIMEOUT * HZ);
	जबतक (((test_bit(ISP_ABORT_NEEDED, &base_vha->dpc_flags)) ||
	    test_bit(ABORT_ISP_ACTIVE, &base_vha->dpc_flags) ||
	    test_bit(ISP_ABORT_RETRY, &base_vha->dpc_flags) ||
	    ha->dpc_active) && समय_beक्रमe(jअगरfies, रुको_online)) अणु

		msleep(1000);
	पूर्ण
	अगर (base_vha->flags.online)
		वापस_status = QLA_SUCCESS;
	अन्यथा
		वापस_status = QLA_FUNCTION_FAILED;

	वापस (वापस_status);
पूर्ण

अटल अंतरभूत पूर्णांक test_fcport_count(scsi_qla_host_t *vha)
अणु
	काष्ठा qla_hw_data *ha = vha->hw;
	अचिन्हित दीर्घ flags;
	पूर्णांक res;

	spin_lock_irqsave(&ha->tgt.sess_lock, flags);
	ql_dbg(ql_dbg_init, vha, 0x00ec,
	    "tgt %p, fcport_count=%d\n",
	    vha, vha->fcport_count);
	res = (vha->fcport_count == 0);
	spin_unlock_irqrestore(&ha->tgt.sess_lock, flags);

	वापस res;
पूर्ण

/*
 * qla2x00_रुको_क्रम_sess_deletion can only be called from हटाओ_one.
 * it has dependency on UNLOADING flag to stop device discovery
 */
व्योम
qla2x00_रुको_क्रम_sess_deletion(scsi_qla_host_t *vha)
अणु
	u8 i;

	qla2x00_mark_all_devices_lost(vha);

	क्रम (i = 0; i < 10; i++) अणु
		अगर (रुको_event_समयout(vha->fcport_रुकोQ,
		    test_fcport_count(vha), HZ) > 0)
			अवरोध;
	पूर्ण

	flush_workqueue(vha->hw->wq);
पूर्ण

/*
 * qla2x00_रुको_क्रम_hba_पढ़ोy
 * Wait till the HBA is पढ़ोy beक्रमe करोing driver unload
 *
 * Input:
 *     ha - poपूर्णांकer to host adapter काष्ठाure
 *
 * Note:
 *    Does context चयनing-Release SPIN_LOCK
 *    (अगर any) beक्रमe calling this routine.
 *
 */
अटल व्योम
qla2x00_रुको_क्रम_hba_पढ़ोy(scsi_qla_host_t *vha)
अणु
	काष्ठा qla_hw_data *ha = vha->hw;
	scsi_qla_host_t *base_vha = pci_get_drvdata(ha->pdev);

	जबतक ((qla2x00_reset_active(vha) || ha->dpc_active ||
		ha->flags.mbox_busy) ||
	       test_bit(FX00_RESET_RECOVERY, &vha->dpc_flags) ||
	       test_bit(FX00_TARGET_SCAN, &vha->dpc_flags)) अणु
		अगर (test_bit(UNLOADING, &base_vha->dpc_flags))
			अवरोध;
		msleep(1000);
	पूर्ण
पूर्ण

पूर्णांक
qla2x00_रुको_क्रम_chip_reset(scsi_qla_host_t *vha)
अणु
	पूर्णांक		वापस_status;
	अचिन्हित दीर्घ	रुको_reset;
	काष्ठा qla_hw_data *ha = vha->hw;
	scsi_qla_host_t *base_vha = pci_get_drvdata(ha->pdev);

	रुको_reset = jअगरfies + (MAX_LOOP_TIMEOUT * HZ);
	जबतक (((test_bit(ISP_ABORT_NEEDED, &base_vha->dpc_flags)) ||
	    test_bit(ABORT_ISP_ACTIVE, &base_vha->dpc_flags) ||
	    test_bit(ISP_ABORT_RETRY, &base_vha->dpc_flags) ||
	    ha->dpc_active) && समय_beक्रमe(jअगरfies, रुको_reset)) अणु

		msleep(1000);

		अगर (!test_bit(ISP_ABORT_NEEDED, &base_vha->dpc_flags) &&
		    ha->flags.chip_reset_करोne)
			अवरोध;
	पूर्ण
	अगर (ha->flags.chip_reset_करोne)
		वापस_status = QLA_SUCCESS;
	अन्यथा
		वापस_status = QLA_FUNCTION_FAILED;

	वापस वापस_status;
पूर्ण

/**************************************************************************
* qla2xxx_eh_पात
*
* Description:
*    The पात function will पात the specअगरied command.
*
* Input:
*    cmd = Linux SCSI command packet to be पातed.
*
* Returns:
*    Either SUCCESS or FAILED.
*
* Note:
*    Only वापस FAILED अगर command not वापसed by firmware.
**************************************************************************/
अटल पूर्णांक
qla2xxx_eh_पात(काष्ठा scsi_cmnd *cmd)
अणु
	scsi_qla_host_t *vha = shost_priv(cmd->device->host);
	DECLARE_COMPLETION_ONSTACK(comp);
	srb_t *sp;
	पूर्णांक ret;
	अचिन्हित पूर्णांक id;
	uपूर्णांक64_t lun;
	पूर्णांक rval;
	काष्ठा qla_hw_data *ha = vha->hw;
	uपूर्णांक32_t ratov_j;
	काष्ठा qla_qpair *qpair;
	अचिन्हित दीर्घ flags;

	अगर (qla2x00_isp_reg_stat(ha)) अणु
		ql_log(ql_log_info, vha, 0x8042,
		    "PCI/Register disconnect, exiting.\n");
		qla_pci_set_eeh_busy(vha);
		वापस FAILED;
	पूर्ण

	ret = fc_block_scsi_eh(cmd);
	अगर (ret != 0)
		वापस ret;

	sp = scsi_cmd_priv(cmd);
	qpair = sp->qpair;

	vha->cmd_समयout_cnt++;

	अगर ((sp->fcport && sp->fcport->deleted) || !qpair)
		वापस SUCCESS;

	spin_lock_irqsave(qpair->qp_lock_ptr, flags);
	sp->comp = &comp;
	spin_unlock_irqrestore(qpair->qp_lock_ptr, flags);


	id = cmd->device->id;
	lun = cmd->device->lun;

	ql_dbg(ql_dbg_taskm, vha, 0x8002,
	    "Aborting from RISC nexus=%ld:%d:%llu sp=%p cmd=%p handle=%x\n",
	    vha->host_no, id, lun, sp, cmd, sp->handle);

	/*
	 * Abort will release the original Command/sp from FW. Let the
	 * original command call scsi_करोne. In वापस, he will wakeup
	 * this sleeping thपढ़ो.
	 */
	rval = ha->isp_ops->पात_command(sp);

	ql_dbg(ql_dbg_taskm, vha, 0x8003,
	       "Abort command mbx cmd=%p, rval=%x.\n", cmd, rval);

	/* Wait क्रम the command completion. */
	ratov_j = ha->r_a_tov/10 * 4 * 1000;
	ratov_j = msecs_to_jअगरfies(ratov_j);
	चयन (rval) अणु
	हाल QLA_SUCCESS:
		अगर (!रुको_क्रम_completion_समयout(&comp, ratov_j)) अणु
			ql_dbg(ql_dbg_taskm, vha, 0xffff,
			    "%s: Abort wait timer (4 * R_A_TOV[%d]) expired\n",
			    __func__, ha->r_a_tov/10);
			ret = FAILED;
		पूर्ण अन्यथा अणु
			ret = SUCCESS;
		पूर्ण
		अवरोध;
	शेष:
		ret = FAILED;
		अवरोध;
	पूर्ण

	sp->comp = शून्य;

	ql_log(ql_log_info, vha, 0x801c,
	    "Abort command issued nexus=%ld:%d:%llu -- %x.\n",
	    vha->host_no, id, lun, ret);

	वापस ret;
पूर्ण

/*
 * Returns: QLA_SUCCESS or QLA_FUNCTION_FAILED.
 */
पूर्णांक
qla2x00_eh_रुको_क्रम_pending_commands(scsi_qla_host_t *vha, अचिन्हित पूर्णांक t,
	uपूर्णांक64_t l, क्रमागत nexus_रुको_type type)
अणु
	पूर्णांक cnt, match, status;
	अचिन्हित दीर्घ flags;
	काष्ठा qla_hw_data *ha = vha->hw;
	काष्ठा req_que *req;
	srb_t *sp;
	काष्ठा scsi_cmnd *cmd;

	status = QLA_SUCCESS;

	spin_lock_irqsave(&ha->hardware_lock, flags);
	req = vha->req;
	क्रम (cnt = 1; status == QLA_SUCCESS &&
		cnt < req->num_outstanding_cmds; cnt++) अणु
		sp = req->outstanding_cmds[cnt];
		अगर (!sp)
			जारी;
		अगर (sp->type != SRB_SCSI_CMD)
			जारी;
		अगर (vha->vp_idx != sp->vha->vp_idx)
			जारी;
		match = 0;
		cmd = GET_CMD_SP(sp);
		चयन (type) अणु
		हाल WAIT_HOST:
			match = 1;
			अवरोध;
		हाल WAIT_TARGET:
			match = cmd->device->id == t;
			अवरोध;
		हाल WAIT_LUN:
			match = (cmd->device->id == t &&
				cmd->device->lun == l);
			अवरोध;
		पूर्ण
		अगर (!match)
			जारी;

		spin_unlock_irqrestore(&ha->hardware_lock, flags);
		status = qla2x00_eh_रुको_on_command(cmd);
		spin_lock_irqsave(&ha->hardware_lock, flags);
	पूर्ण
	spin_unlock_irqrestore(&ha->hardware_lock, flags);

	वापस status;
पूर्ण

अटल अक्षर *reset_errors[] = अणु
	"HBA not online",
	"HBA not ready",
	"Task management failed",
	"Waiting for command completions",
पूर्ण;

अटल पूर्णांक
__qla2xxx_eh_generic_reset(अक्षर *name, क्रमागत nexus_रुको_type type,
    काष्ठा scsi_cmnd *cmd, पूर्णांक (*करो_reset)(काष्ठा fc_port *, uपूर्णांक64_t, पूर्णांक))
अणु
	scsi_qla_host_t *vha = shost_priv(cmd->device->host);
	fc_port_t *fcport = (काष्ठा fc_port *) cmd->device->hostdata;
	पूर्णांक err;

	अगर (!fcport) अणु
		वापस FAILED;
	पूर्ण

	err = fc_block_scsi_eh(cmd);
	अगर (err != 0)
		वापस err;

	अगर (fcport->deleted)
		वापस SUCCESS;

	ql_log(ql_log_info, vha, 0x8009,
	    "%s RESET ISSUED nexus=%ld:%d:%llu cmd=%p.\n", name, vha->host_no,
	    cmd->device->id, cmd->device->lun, cmd);

	err = 0;
	अगर (qla2x00_रुको_क्रम_hba_online(vha) != QLA_SUCCESS) अणु
		ql_log(ql_log_warn, vha, 0x800a,
		    "Wait for hba online failed for cmd=%p.\n", cmd);
		जाओ eh_reset_failed;
	पूर्ण
	err = 2;
	अगर (करो_reset(fcport, cmd->device->lun, 1)
		!= QLA_SUCCESS) अणु
		ql_log(ql_log_warn, vha, 0x800c,
		    "do_reset failed for cmd=%p.\n", cmd);
		जाओ eh_reset_failed;
	पूर्ण
	err = 3;
	अगर (qla2x00_eh_रुको_क्रम_pending_commands(vha, cmd->device->id,
	    cmd->device->lun, type) != QLA_SUCCESS) अणु
		ql_log(ql_log_warn, vha, 0x800d,
		    "wait for pending cmds failed for cmd=%p.\n", cmd);
		जाओ eh_reset_failed;
	पूर्ण

	ql_log(ql_log_info, vha, 0x800e,
	    "%s RESET SUCCEEDED nexus:%ld:%d:%llu cmd=%p.\n", name,
	    vha->host_no, cmd->device->id, cmd->device->lun, cmd);

	वापस SUCCESS;

eh_reset_failed:
	ql_log(ql_log_info, vha, 0x800f,
	    "%s RESET FAILED: %s nexus=%ld:%d:%llu cmd=%p.\n", name,
	    reset_errors[err], vha->host_no, cmd->device->id, cmd->device->lun,
	    cmd);
	vha->reset_cmd_err_cnt++;
	वापस FAILED;
पूर्ण

अटल पूर्णांक
qla2xxx_eh_device_reset(काष्ठा scsi_cmnd *cmd)
अणु
	scsi_qla_host_t *vha = shost_priv(cmd->device->host);
	काष्ठा qla_hw_data *ha = vha->hw;

	अगर (qla2x00_isp_reg_stat(ha)) अणु
		ql_log(ql_log_info, vha, 0x803e,
		    "PCI/Register disconnect, exiting.\n");
		qla_pci_set_eeh_busy(vha);
		वापस FAILED;
	पूर्ण

	वापस __qla2xxx_eh_generic_reset("DEVICE", WAIT_LUN, cmd,
	    ha->isp_ops->lun_reset);
पूर्ण

अटल पूर्णांक
qla2xxx_eh_target_reset(काष्ठा scsi_cmnd *cmd)
अणु
	scsi_qla_host_t *vha = shost_priv(cmd->device->host);
	काष्ठा qla_hw_data *ha = vha->hw;

	अगर (qla2x00_isp_reg_stat(ha)) अणु
		ql_log(ql_log_info, vha, 0x803f,
		    "PCI/Register disconnect, exiting.\n");
		qla_pci_set_eeh_busy(vha);
		वापस FAILED;
	पूर्ण

	वापस __qla2xxx_eh_generic_reset("TARGET", WAIT_TARGET, cmd,
	    ha->isp_ops->target_reset);
पूर्ण

/**************************************************************************
* qla2xxx_eh_bus_reset
*
* Description:
*    The bus reset function will reset the bus and पात any executing
*    commands.
*
* Input:
*    cmd = Linux SCSI command packet of the command that cause the
*          bus reset.
*
* Returns:
*    SUCCESS/FAILURE (defined as macro in scsi.h).
*
**************************************************************************/
अटल पूर्णांक
qla2xxx_eh_bus_reset(काष्ठा scsi_cmnd *cmd)
अणु
	scsi_qla_host_t *vha = shost_priv(cmd->device->host);
	fc_port_t *fcport = (काष्ठा fc_port *) cmd->device->hostdata;
	पूर्णांक ret = FAILED;
	अचिन्हित पूर्णांक id;
	uपूर्णांक64_t lun;
	काष्ठा qla_hw_data *ha = vha->hw;

	अगर (qla2x00_isp_reg_stat(ha)) अणु
		ql_log(ql_log_info, vha, 0x8040,
		    "PCI/Register disconnect, exiting.\n");
		qla_pci_set_eeh_busy(vha);
		वापस FAILED;
	पूर्ण

	id = cmd->device->id;
	lun = cmd->device->lun;

	अगर (!fcport) अणु
		वापस ret;
	पूर्ण

	ret = fc_block_scsi_eh(cmd);
	अगर (ret != 0)
		वापस ret;
	ret = FAILED;

	अगर (qla2x00_chip_is_करोwn(vha))
		वापस ret;

	ql_log(ql_log_info, vha, 0x8012,
	    "BUS RESET ISSUED nexus=%ld:%d:%llu.\n", vha->host_no, id, lun);

	अगर (qla2x00_रुको_क्रम_hba_online(vha) != QLA_SUCCESS) अणु
		ql_log(ql_log_fatal, vha, 0x8013,
		    "Wait for hba online failed board disabled.\n");
		जाओ eh_bus_reset_करोne;
	पूर्ण

	अगर (qla2x00_loop_reset(vha) == QLA_SUCCESS)
		ret = SUCCESS;

	अगर (ret == FAILED)
		जाओ eh_bus_reset_करोne;

	/* Flush outstanding commands. */
	अगर (qla2x00_eh_रुको_क्रम_pending_commands(vha, 0, 0, WAIT_HOST) !=
	    QLA_SUCCESS) अणु
		ql_log(ql_log_warn, vha, 0x8014,
		    "Wait for pending commands failed.\n");
		ret = FAILED;
	पूर्ण

eh_bus_reset_करोne:
	ql_log(ql_log_warn, vha, 0x802b,
	    "BUS RESET %s nexus=%ld:%d:%llu.\n",
	    (ret == FAILED) ? "FAILED" : "SUCCEEDED", vha->host_no, id, lun);

	वापस ret;
पूर्ण

/**************************************************************************
* qla2xxx_eh_host_reset
*
* Description:
*    The reset function will reset the Adapter.
*
* Input:
*      cmd = Linux SCSI command packet of the command that cause the
*            adapter reset.
*
* Returns:
*      Either SUCCESS or FAILED.
*
* Note:
**************************************************************************/
अटल पूर्णांक
qla2xxx_eh_host_reset(काष्ठा scsi_cmnd *cmd)
अणु
	scsi_qla_host_t *vha = shost_priv(cmd->device->host);
	काष्ठा qla_hw_data *ha = vha->hw;
	पूर्णांक ret = FAILED;
	अचिन्हित पूर्णांक id;
	uपूर्णांक64_t lun;
	scsi_qla_host_t *base_vha = pci_get_drvdata(ha->pdev);

	अगर (qla2x00_isp_reg_stat(ha)) अणु
		ql_log(ql_log_info, vha, 0x8041,
		    "PCI/Register disconnect, exiting.\n");
		qla_pci_set_eeh_busy(vha);
		वापस SUCCESS;
	पूर्ण

	id = cmd->device->id;
	lun = cmd->device->lun;

	ql_log(ql_log_info, vha, 0x8018,
	    "ADAPTER RESET ISSUED nexus=%ld:%d:%llu.\n", vha->host_no, id, lun);

	/*
	 * No poपूर्णांक in issuing another reset अगर one is active.  Also करो not
	 * attempt a reset अगर we are updating flash.
	 */
	अगर (qla2x00_reset_active(vha) || ha->optrom_state != QLA_SWAITING)
		जाओ eh_host_reset_lock;

	अगर (vha != base_vha) अणु
		अगर (qla2x00_vp_पात_isp(vha))
			जाओ eh_host_reset_lock;
	पूर्ण अन्यथा अणु
		अगर (IS_P3P_TYPE(vha->hw)) अणु
			अगर (!qla82xx_fcoe_ctx_reset(vha)) अणु
				/* Ctx reset success */
				ret = SUCCESS;
				जाओ eh_host_reset_lock;
			पूर्ण
			/* fall thru अगर ctx reset failed */
		पूर्ण
		अगर (ha->wq)
			flush_workqueue(ha->wq);

		set_bit(ABORT_ISP_ACTIVE, &base_vha->dpc_flags);
		अगर (ha->isp_ops->पात_isp(base_vha)) अणु
			clear_bit(ABORT_ISP_ACTIVE, &base_vha->dpc_flags);
			/* failed. schedule dpc to try */
			set_bit(ISP_ABORT_NEEDED, &base_vha->dpc_flags);

			अगर (qla2x00_रुको_क्रम_hba_online(vha) != QLA_SUCCESS) अणु
				ql_log(ql_log_warn, vha, 0x802a,
				    "wait for hba online failed.\n");
				जाओ eh_host_reset_lock;
			पूर्ण
		पूर्ण
		clear_bit(ABORT_ISP_ACTIVE, &base_vha->dpc_flags);
	पूर्ण

	/* Waiting क्रम command to be वापसed to OS.*/
	अगर (qla2x00_eh_रुको_क्रम_pending_commands(vha, 0, 0, WAIT_HOST) ==
		QLA_SUCCESS)
		ret = SUCCESS;

eh_host_reset_lock:
	ql_log(ql_log_info, vha, 0x8017,
	    "ADAPTER RESET %s nexus=%ld:%d:%llu.\n",
	    (ret == FAILED) ? "FAILED" : "SUCCEEDED", vha->host_no, id, lun);

	वापस ret;
पूर्ण

/*
* qla2x00_loop_reset
*      Issue loop reset.
*
* Input:
*      ha = adapter block poपूर्णांकer.
*
* Returns:
*      0 = success
*/
पूर्णांक
qla2x00_loop_reset(scsi_qla_host_t *vha)
अणु
	पूर्णांक ret;
	काष्ठा fc_port *fcport;
	काष्ठा qla_hw_data *ha = vha->hw;

	अगर (IS_QLAFX00(ha)) अणु
		वापस qlafx00_loop_reset(vha);
	पूर्ण

	अगर (ql2xtargetreset == 1 && ha->flags.enable_target_reset) अणु
		list_क्रम_each_entry(fcport, &vha->vp_fcports, list) अणु
			अगर (fcport->port_type != FCT_TARGET)
				जारी;

			ret = ha->isp_ops->target_reset(fcport, 0, 0);
			अगर (ret != QLA_SUCCESS) अणु
				ql_dbg(ql_dbg_taskm, vha, 0x802c,
				    "Bus Reset failed: Reset=%d "
				    "d_id=%x.\n", ret, fcport->d_id.b24);
			पूर्ण
		पूर्ण
	पूर्ण


	अगर (ha->flags.enable_lip_full_login && !IS_CNA_CAPABLE(ha)) अणु
		atomic_set(&vha->loop_state, LOOP_DOWN);
		atomic_set(&vha->loop_करोwn_समयr, LOOP_DOWN_TIME);
		qla2x00_mark_all_devices_lost(vha);
		ret = qla2x00_full_login_lip(vha);
		अगर (ret != QLA_SUCCESS) अणु
			ql_dbg(ql_dbg_taskm, vha, 0x802d,
			    "full_login_lip=%d.\n", ret);
		पूर्ण
	पूर्ण

	अगर (ha->flags.enable_lip_reset) अणु
		ret = qla2x00_lip_reset(vha);
		अगर (ret != QLA_SUCCESS)
			ql_dbg(ql_dbg_taskm, vha, 0x802e,
			    "lip_reset failed (%d).\n", ret);
	पूर्ण

	/* Issue marker command only when we are going to start the I/O */
	vha->marker_needed = 1;

	वापस QLA_SUCCESS;
पूर्ण

/*
 * The caller must ensure that no completion पूर्णांकerrupts will happen
 * जबतक this function is in progress.
 */
अटल व्योम qla2x00_पात_srb(काष्ठा qla_qpair *qp, srb_t *sp, स्थिर पूर्णांक res,
			      अचिन्हित दीर्घ *flags)
	__releases(qp->qp_lock_ptr)
	__acquires(qp->qp_lock_ptr)
अणु
	DECLARE_COMPLETION_ONSTACK(comp);
	scsi_qla_host_t *vha = qp->vha;
	काष्ठा qla_hw_data *ha = vha->hw;
	काष्ठा scsi_cmnd *cmd = GET_CMD_SP(sp);
	पूर्णांक rval;
	bool ret_cmd;
	uपूर्णांक32_t ratov_j;

	lockdep_निश्चित_held(qp->qp_lock_ptr);

	अगर (qla2x00_chip_is_करोwn(vha)) अणु
		sp->करोne(sp, res);
		वापस;
	पूर्ण

	अगर (sp->type == SRB_NVME_CMD || sp->type == SRB_NVME_LS ||
	    (sp->type == SRB_SCSI_CMD && !ha->flags.eeh_busy &&
	     !test_bit(ABORT_ISP_ACTIVE, &vha->dpc_flags) &&
	     !qla2x00_isp_reg_stat(ha))) अणु
		अगर (sp->comp) अणु
			sp->करोne(sp, res);
			वापस;
		पूर्ण

		sp->comp = &comp;
		spin_unlock_irqrestore(qp->qp_lock_ptr, *flags);

		rval = ha->isp_ops->पात_command(sp);
		/* Wait क्रम command completion. */
		ret_cmd = false;
		ratov_j = ha->r_a_tov/10 * 4 * 1000;
		ratov_j = msecs_to_jअगरfies(ratov_j);
		चयन (rval) अणु
		हाल QLA_SUCCESS:
			अगर (रुको_क्रम_completion_समयout(&comp, ratov_j)) अणु
				ql_dbg(ql_dbg_taskm, vha, 0xffff,
				    "%s: Abort wait timer (4 * R_A_TOV[%d]) expired\n",
				    __func__, ha->r_a_tov/10);
				ret_cmd = true;
			पूर्ण
			/* अन्यथा FW वापस SP to driver */
			अवरोध;
		शेष:
			ret_cmd = true;
			अवरोध;
		पूर्ण

		spin_lock_irqsave(qp->qp_lock_ptr, *flags);
		अगर (ret_cmd && blk_mq_request_started(cmd->request))
			sp->करोne(sp, res);
	पूर्ण अन्यथा अणु
		sp->करोne(sp, res);
	पूर्ण
पूर्ण

/*
 * The caller must ensure that no completion पूर्णांकerrupts will happen
 * जबतक this function is in progress.
 */
अटल व्योम
__qla2x00_पात_all_cmds(काष्ठा qla_qpair *qp, पूर्णांक res)
अणु
	पूर्णांक cnt;
	अचिन्हित दीर्घ flags;
	srb_t *sp;
	scsi_qla_host_t *vha = qp->vha;
	काष्ठा qla_hw_data *ha = vha->hw;
	काष्ठा req_que *req;
	काष्ठा qla_tgt *tgt = vha->vha_tgt.qla_tgt;
	काष्ठा qla_tgt_cmd *cmd;

	अगर (!ha->req_q_map)
		वापस;
	spin_lock_irqsave(qp->qp_lock_ptr, flags);
	req = qp->req;
	क्रम (cnt = 1; cnt < req->num_outstanding_cmds; cnt++) अणु
		sp = req->outstanding_cmds[cnt];
		अगर (sp) अणु
			चयन (sp->cmd_type) अणु
			हाल TYPE_SRB:
				qla2x00_पात_srb(qp, sp, res, &flags);
				अवरोध;
			हाल TYPE_TGT_CMD:
				अगर (!vha->hw->tgt.tgt_ops || !tgt ||
				    qla_ini_mode_enabled(vha)) अणु
					ql_dbg(ql_dbg_tgt_mgt, vha, 0xf003,
					    "HOST-ABORT-HNDLR: dpc_flags=%lx. Target mode disabled\n",
					    vha->dpc_flags);
					जारी;
				पूर्ण
				cmd = (काष्ठा qla_tgt_cmd *)sp;
				cmd->पातed = 1;
				अवरोध;
			हाल TYPE_TGT_TMCMD:
				/* Skip task management functions. */
				अवरोध;
			शेष:
				अवरोध;
			पूर्ण
			req->outstanding_cmds[cnt] = शून्य;
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(qp->qp_lock_ptr, flags);
पूर्ण

/*
 * The caller must ensure that no completion पूर्णांकerrupts will happen
 * जबतक this function is in progress.
 */
व्योम
qla2x00_पात_all_cmds(scsi_qla_host_t *vha, पूर्णांक res)
अणु
	पूर्णांक que;
	काष्ठा qla_hw_data *ha = vha->hw;

	/* Continue only अगर initialization complete. */
	अगर (!ha->base_qpair)
		वापस;
	__qla2x00_पात_all_cmds(ha->base_qpair, res);

	अगर (!ha->queue_pair_map)
		वापस;
	क्रम (que = 0; que < ha->max_qpairs; que++) अणु
		अगर (!ha->queue_pair_map[que])
			जारी;

		__qla2x00_पात_all_cmds(ha->queue_pair_map[que], res);
	पूर्ण
पूर्ण

अटल पूर्णांक
qla2xxx_slave_alloc(काष्ठा scsi_device *sdev)
अणु
	काष्ठा fc_rport *rport = starget_to_rport(scsi_target(sdev));

	अगर (!rport || fc_remote_port_chkपढ़ोy(rport))
		वापस -ENXIO;

	sdev->hostdata = *(fc_port_t **)rport->dd_data;

	वापस 0;
पूर्ण

अटल पूर्णांक
qla2xxx_slave_configure(काष्ठा scsi_device *sdev)
अणु
	scsi_qla_host_t *vha = shost_priv(sdev->host);
	काष्ठा req_que *req = vha->req;

	अगर (IS_T10_PI_CAPABLE(vha->hw))
		blk_queue_update_dma_alignment(sdev->request_queue, 0x7);

	scsi_change_queue_depth(sdev, req->max_q_depth);
	वापस 0;
पूर्ण

अटल व्योम
qla2xxx_slave_destroy(काष्ठा scsi_device *sdev)
अणु
	sdev->hostdata = शून्य;
पूर्ण

/**
 * qla2x00_config_dma_addressing() - Configure OS DMA addressing method.
 * @ha: HA context
 *
 * At निकास, the @ha's flags.enable_64bit_addressing set to indicated
 * supported addressing method.
 */
अटल व्योम
qla2x00_config_dma_addressing(काष्ठा qla_hw_data *ha)
अणु
	/* Assume a 32bit DMA mask. */
	ha->flags.enable_64bit_addressing = 0;

	अगर (!dma_set_mask(&ha->pdev->dev, DMA_BIT_MASK(64))) अणु
		/* Any upper-dword bits set? */
		अगर (MSD(dma_get_required_mask(&ha->pdev->dev)) &&
		    !dma_set_coherent_mask(&ha->pdev->dev, DMA_BIT_MASK(64))) अणु
			/* Ok, a 64bit DMA mask is applicable. */
			ha->flags.enable_64bit_addressing = 1;
			ha->isp_ops->calc_req_entries = qla2x00_calc_iocbs_64;
			ha->isp_ops->build_iocbs = qla2x00_build_scsi_iocbs_64;
			वापस;
		पूर्ण
	पूर्ण

	dma_set_mask(&ha->pdev->dev, DMA_BIT_MASK(32));
	dma_set_coherent_mask(&ha->pdev->dev, DMA_BIT_MASK(32));
पूर्ण

अटल व्योम
qla2x00_enable_पूर्णांकrs(काष्ठा qla_hw_data *ha)
अणु
	अचिन्हित दीर्घ flags = 0;
	काष्ठा device_reg_2xxx __iomem *reg = &ha->iobase->isp;

	spin_lock_irqsave(&ha->hardware_lock, flags);
	ha->पूर्णांकerrupts_on = 1;
	/* enable risc and host पूर्णांकerrupts */
	wrt_reg_word(&reg->ictrl, ICR_EN_INT | ICR_EN_RISC);
	rd_reg_word(&reg->ictrl);
	spin_unlock_irqrestore(&ha->hardware_lock, flags);

पूर्ण

अटल व्योम
qla2x00_disable_पूर्णांकrs(काष्ठा qla_hw_data *ha)
अणु
	अचिन्हित दीर्घ flags = 0;
	काष्ठा device_reg_2xxx __iomem *reg = &ha->iobase->isp;

	spin_lock_irqsave(&ha->hardware_lock, flags);
	ha->पूर्णांकerrupts_on = 0;
	/* disable risc and host पूर्णांकerrupts */
	wrt_reg_word(&reg->ictrl, 0);
	rd_reg_word(&reg->ictrl);
	spin_unlock_irqrestore(&ha->hardware_lock, flags);
पूर्ण

अटल व्योम
qla24xx_enable_पूर्णांकrs(काष्ठा qla_hw_data *ha)
अणु
	अचिन्हित दीर्घ flags = 0;
	काष्ठा device_reg_24xx __iomem *reg = &ha->iobase->isp24;

	spin_lock_irqsave(&ha->hardware_lock, flags);
	ha->पूर्णांकerrupts_on = 1;
	wrt_reg_dword(&reg->ictrl, ICRX_EN_RISC_INT);
	rd_reg_dword(&reg->ictrl);
	spin_unlock_irqrestore(&ha->hardware_lock, flags);
पूर्ण

अटल व्योम
qla24xx_disable_पूर्णांकrs(काष्ठा qla_hw_data *ha)
अणु
	अचिन्हित दीर्घ flags = 0;
	काष्ठा device_reg_24xx __iomem *reg = &ha->iobase->isp24;

	अगर (IS_NOPOLLING_TYPE(ha))
		वापस;
	spin_lock_irqsave(&ha->hardware_lock, flags);
	ha->पूर्णांकerrupts_on = 0;
	wrt_reg_dword(&reg->ictrl, 0);
	rd_reg_dword(&reg->ictrl);
	spin_unlock_irqrestore(&ha->hardware_lock, flags);
पूर्ण

अटल पूर्णांक
qla2x00_iospace_config(काष्ठा qla_hw_data *ha)
अणु
	resource_माप_प्रकार pio;
	uपूर्णांक16_t msix;

	अगर (pci_request_selected_regions(ha->pdev, ha->bars,
	    QLA2XXX_DRIVER_NAME)) अणु
		ql_log_pci(ql_log_fatal, ha->pdev, 0x0011,
		    "Failed to reserve PIO/MMIO regions (%s), aborting.\n",
		    pci_name(ha->pdev));
		जाओ iospace_error_निकास;
	पूर्ण
	अगर (!(ha->bars & 1))
		जाओ skip_pio;

	/* We only need PIO क्रम Flash operations on ISP2312 v2 chips. */
	pio = pci_resource_start(ha->pdev, 0);
	अगर (pci_resource_flags(ha->pdev, 0) & IORESOURCE_IO) अणु
		अगर (pci_resource_len(ha->pdev, 0) < MIN_IOBASE_LEN) अणु
			ql_log_pci(ql_log_warn, ha->pdev, 0x0012,
			    "Invalid pci I/O region size (%s).\n",
			    pci_name(ha->pdev));
			pio = 0;
		पूर्ण
	पूर्ण अन्यथा अणु
		ql_log_pci(ql_log_warn, ha->pdev, 0x0013,
		    "Region #0 no a PIO resource (%s).\n",
		    pci_name(ha->pdev));
		pio = 0;
	पूर्ण
	ha->pio_address = pio;
	ql_dbg_pci(ql_dbg_init, ha->pdev, 0x0014,
	    "PIO address=%llu.\n",
	    (अचिन्हित दीर्घ दीर्घ)ha->pio_address);

skip_pio:
	/* Use MMIO operations क्रम all accesses. */
	अगर (!(pci_resource_flags(ha->pdev, 1) & IORESOURCE_MEM)) अणु
		ql_log_pci(ql_log_fatal, ha->pdev, 0x0015,
		    "Region #1 not an MMIO resource (%s), aborting.\n",
		    pci_name(ha->pdev));
		जाओ iospace_error_निकास;
	पूर्ण
	अगर (pci_resource_len(ha->pdev, 1) < MIN_IOBASE_LEN) अणु
		ql_log_pci(ql_log_fatal, ha->pdev, 0x0016,
		    "Invalid PCI mem region size (%s), aborting.\n",
		    pci_name(ha->pdev));
		जाओ iospace_error_निकास;
	पूर्ण

	ha->iobase = ioremap(pci_resource_start(ha->pdev, 1), MIN_IOBASE_LEN);
	अगर (!ha->iobase) अणु
		ql_log_pci(ql_log_fatal, ha->pdev, 0x0017,
		    "Cannot remap MMIO (%s), aborting.\n",
		    pci_name(ha->pdev));
		जाओ iospace_error_निकास;
	पूर्ण

	/* Determine queue resources */
	ha->max_req_queues = ha->max_rsp_queues = 1;
	ha->msix_count = QLA_BASE_VECTORS;

	/* Check अगर FW supports MQ or not */
	अगर (!(ha->fw_attributes & BIT_6))
		जाओ mqiobase_निकास;

	अगर (!ql2xmqsupport || !ql2xnvmeenable ||
	    (!IS_QLA25XX(ha) && !IS_QLA81XX(ha)))
		जाओ mqiobase_निकास;

	ha->mqiobase = ioremap(pci_resource_start(ha->pdev, 3),
			pci_resource_len(ha->pdev, 3));
	अगर (ha->mqiobase) अणु
		ql_dbg_pci(ql_dbg_init, ha->pdev, 0x0018,
		    "MQIO Base=%p.\n", ha->mqiobase);
		/* Read MSIX vector size of the board */
		pci_पढ़ो_config_word(ha->pdev, QLA_PCI_MSIX_CONTROL, &msix);
		ha->msix_count = msix + 1;
		/* Max queues are bounded by available msix vectors */
		/* MB पूर्णांकerrupt uses 1 vector */
		ha->max_req_queues = ha->msix_count - 1;
		ha->max_rsp_queues = ha->max_req_queues;
		/* Queue pairs is the max value minus the base queue pair */
		ha->max_qpairs = ha->max_rsp_queues - 1;
		ql_dbg_pci(ql_dbg_init, ha->pdev, 0x0188,
		    "Max no of queues pairs: %d.\n", ha->max_qpairs);

		ql_log_pci(ql_log_info, ha->pdev, 0x001a,
		    "MSI-X vector count: %d.\n", ha->msix_count);
	पूर्ण अन्यथा
		ql_log_pci(ql_log_info, ha->pdev, 0x001b,
		    "BAR 3 not enabled.\n");

mqiobase_निकास:
	ql_dbg_pci(ql_dbg_init, ha->pdev, 0x001c,
	    "MSIX Count: %d.\n", ha->msix_count);
	वापस (0);

iospace_error_निकास:
	वापस (-ENOMEM);
पूर्ण


अटल पूर्णांक
qla83xx_iospace_config(काष्ठा qla_hw_data *ha)
अणु
	uपूर्णांक16_t msix;

	अगर (pci_request_selected_regions(ha->pdev, ha->bars,
	    QLA2XXX_DRIVER_NAME)) अणु
		ql_log_pci(ql_log_fatal, ha->pdev, 0x0117,
		    "Failed to reserve PIO/MMIO regions (%s), aborting.\n",
		    pci_name(ha->pdev));

		जाओ iospace_error_निकास;
	पूर्ण

	/* Use MMIO operations क्रम all accesses. */
	अगर (!(pci_resource_flags(ha->pdev, 0) & IORESOURCE_MEM)) अणु
		ql_log_pci(ql_log_warn, ha->pdev, 0x0118,
		    "Invalid pci I/O region size (%s).\n",
		    pci_name(ha->pdev));
		जाओ iospace_error_निकास;
	पूर्ण
	अगर (pci_resource_len(ha->pdev, 0) < MIN_IOBASE_LEN) अणु
		ql_log_pci(ql_log_warn, ha->pdev, 0x0119,
		    "Invalid PCI mem region size (%s), aborting\n",
			pci_name(ha->pdev));
		जाओ iospace_error_निकास;
	पूर्ण

	ha->iobase = ioremap(pci_resource_start(ha->pdev, 0), MIN_IOBASE_LEN);
	अगर (!ha->iobase) अणु
		ql_log_pci(ql_log_fatal, ha->pdev, 0x011a,
		    "Cannot remap MMIO (%s), aborting.\n",
		    pci_name(ha->pdev));
		जाओ iospace_error_निकास;
	पूर्ण

	/* 64bit PCI BAR - BAR2 will correspoond to region 4 */
	/* 83XX 26XX always use MQ type access क्रम queues
	 * - mbar 2, a.k.a region 4 */
	ha->max_req_queues = ha->max_rsp_queues = 1;
	ha->msix_count = QLA_BASE_VECTORS;
	ha->mqiobase = ioremap(pci_resource_start(ha->pdev, 4),
			pci_resource_len(ha->pdev, 4));

	अगर (!ha->mqiobase) अणु
		ql_log_pci(ql_log_fatal, ha->pdev, 0x011d,
		    "BAR2/region4 not enabled\n");
		जाओ mqiobase_निकास;
	पूर्ण

	ha->msixbase = ioremap(pci_resource_start(ha->pdev, 2),
			pci_resource_len(ha->pdev, 2));
	अगर (ha->msixbase) अणु
		/* Read MSIX vector size of the board */
		pci_पढ़ो_config_word(ha->pdev,
		    QLA_83XX_PCI_MSIX_CONTROL, &msix);
		ha->msix_count = (msix & PCI_MSIX_FLAGS_QSIZE)  + 1;
		/*
		 * By शेष, driver uses at least two msix vectors
		 * (शेष & rspq)
		 */
		अगर (ql2xmqsupport || ql2xnvmeenable) अणु
			/* MB पूर्णांकerrupt uses 1 vector */
			ha->max_req_queues = ha->msix_count - 1;

			/* ATIOQ needs 1 vector. That's 1 less QPair */
			अगर (QLA_TGT_MODE_ENABLED())
				ha->max_req_queues--;

			ha->max_rsp_queues = ha->max_req_queues;

			/* Queue pairs is the max value minus
			 * the base queue pair */
			ha->max_qpairs = ha->max_req_queues - 1;
			ql_dbg_pci(ql_dbg_init, ha->pdev, 0x00e3,
			    "Max no of queues pairs: %d.\n", ha->max_qpairs);
		पूर्ण
		ql_log_pci(ql_log_info, ha->pdev, 0x011c,
		    "MSI-X vector count: %d.\n", ha->msix_count);
	पूर्ण अन्यथा
		ql_log_pci(ql_log_info, ha->pdev, 0x011e,
		    "BAR 1 not enabled.\n");

mqiobase_निकास:
	ql_dbg_pci(ql_dbg_init, ha->pdev, 0x011f,
	    "MSIX Count: %d.\n", ha->msix_count);
	वापस 0;

iospace_error_निकास:
	वापस -ENOMEM;
पूर्ण

अटल काष्ठा isp_operations qla2100_isp_ops = अणु
	.pci_config		= qla2100_pci_config,
	.reset_chip		= qla2x00_reset_chip,
	.chip_diag		= qla2x00_chip_diag,
	.config_rings		= qla2x00_config_rings,
	.reset_adapter		= qla2x00_reset_adapter,
	.nvram_config		= qla2x00_nvram_config,
	.update_fw_options	= qla2x00_update_fw_options,
	.load_risc		= qla2x00_load_risc,
	.pci_info_str		= qla2x00_pci_info_str,
	.fw_version_str		= qla2x00_fw_version_str,
	.पूर्णांकr_handler		= qla2100_पूर्णांकr_handler,
	.enable_पूर्णांकrs		= qla2x00_enable_पूर्णांकrs,
	.disable_पूर्णांकrs		= qla2x00_disable_पूर्णांकrs,
	.पात_command		= qla2x00_पात_command,
	.target_reset		= qla2x00_पात_target,
	.lun_reset		= qla2x00_lun_reset,
	.fabric_login		= qla2x00_login_fabric,
	.fabric_logout		= qla2x00_fabric_logout,
	.calc_req_entries	= qla2x00_calc_iocbs_32,
	.build_iocbs		= qla2x00_build_scsi_iocbs_32,
	.prep_ms_iocb		= qla2x00_prep_ms_iocb,
	.prep_ms_fdmi_iocb	= qla2x00_prep_ms_fdmi_iocb,
	.पढ़ो_nvram		= qla2x00_पढ़ो_nvram_data,
	.ग_लिखो_nvram		= qla2x00_ग_लिखो_nvram_data,
	.fw_dump		= qla2100_fw_dump,
	.beacon_on		= शून्य,
	.beacon_off		= शून्य,
	.beacon_blink		= शून्य,
	.पढ़ो_optrom		= qla2x00_पढ़ो_optrom_data,
	.ग_लिखो_optrom		= qla2x00_ग_लिखो_optrom_data,
	.get_flash_version	= qla2x00_get_flash_version,
	.start_scsi		= qla2x00_start_scsi,
	.start_scsi_mq          = शून्य,
	.पात_isp		= qla2x00_पात_isp,
	.iospace_config     	= qla2x00_iospace_config,
	.initialize_adapter	= qla2x00_initialize_adapter,
पूर्ण;

अटल काष्ठा isp_operations qla2300_isp_ops = अणु
	.pci_config		= qla2300_pci_config,
	.reset_chip		= qla2x00_reset_chip,
	.chip_diag		= qla2x00_chip_diag,
	.config_rings		= qla2x00_config_rings,
	.reset_adapter		= qla2x00_reset_adapter,
	.nvram_config		= qla2x00_nvram_config,
	.update_fw_options	= qla2x00_update_fw_options,
	.load_risc		= qla2x00_load_risc,
	.pci_info_str		= qla2x00_pci_info_str,
	.fw_version_str		= qla2x00_fw_version_str,
	.पूर्णांकr_handler		= qla2300_पूर्णांकr_handler,
	.enable_पूर्णांकrs		= qla2x00_enable_पूर्णांकrs,
	.disable_पूर्णांकrs		= qla2x00_disable_पूर्णांकrs,
	.पात_command		= qla2x00_पात_command,
	.target_reset		= qla2x00_पात_target,
	.lun_reset		= qla2x00_lun_reset,
	.fabric_login		= qla2x00_login_fabric,
	.fabric_logout		= qla2x00_fabric_logout,
	.calc_req_entries	= qla2x00_calc_iocbs_32,
	.build_iocbs		= qla2x00_build_scsi_iocbs_32,
	.prep_ms_iocb		= qla2x00_prep_ms_iocb,
	.prep_ms_fdmi_iocb	= qla2x00_prep_ms_fdmi_iocb,
	.पढ़ो_nvram		= qla2x00_पढ़ो_nvram_data,
	.ग_लिखो_nvram		= qla2x00_ग_लिखो_nvram_data,
	.fw_dump		= qla2300_fw_dump,
	.beacon_on		= qla2x00_beacon_on,
	.beacon_off		= qla2x00_beacon_off,
	.beacon_blink		= qla2x00_beacon_blink,
	.पढ़ो_optrom		= qla2x00_पढ़ो_optrom_data,
	.ग_लिखो_optrom		= qla2x00_ग_लिखो_optrom_data,
	.get_flash_version	= qla2x00_get_flash_version,
	.start_scsi		= qla2x00_start_scsi,
	.start_scsi_mq          = शून्य,
	.पात_isp		= qla2x00_पात_isp,
	.iospace_config		= qla2x00_iospace_config,
	.initialize_adapter	= qla2x00_initialize_adapter,
पूर्ण;

अटल काष्ठा isp_operations qla24xx_isp_ops = अणु
	.pci_config		= qla24xx_pci_config,
	.reset_chip		= qla24xx_reset_chip,
	.chip_diag		= qla24xx_chip_diag,
	.config_rings		= qla24xx_config_rings,
	.reset_adapter		= qla24xx_reset_adapter,
	.nvram_config		= qla24xx_nvram_config,
	.update_fw_options	= qla24xx_update_fw_options,
	.load_risc		= qla24xx_load_risc,
	.pci_info_str		= qla24xx_pci_info_str,
	.fw_version_str		= qla24xx_fw_version_str,
	.पूर्णांकr_handler		= qla24xx_पूर्णांकr_handler,
	.enable_पूर्णांकrs		= qla24xx_enable_पूर्णांकrs,
	.disable_पूर्णांकrs		= qla24xx_disable_पूर्णांकrs,
	.पात_command		= qla24xx_पात_command,
	.target_reset		= qla24xx_पात_target,
	.lun_reset		= qla24xx_lun_reset,
	.fabric_login		= qla24xx_login_fabric,
	.fabric_logout		= qla24xx_fabric_logout,
	.calc_req_entries	= शून्य,
	.build_iocbs		= शून्य,
	.prep_ms_iocb		= qla24xx_prep_ms_iocb,
	.prep_ms_fdmi_iocb	= qla24xx_prep_ms_fdmi_iocb,
	.पढ़ो_nvram		= qla24xx_पढ़ो_nvram_data,
	.ग_लिखो_nvram		= qla24xx_ग_लिखो_nvram_data,
	.fw_dump		= qla24xx_fw_dump,
	.beacon_on		= qla24xx_beacon_on,
	.beacon_off		= qla24xx_beacon_off,
	.beacon_blink		= qla24xx_beacon_blink,
	.पढ़ो_optrom		= qla24xx_पढ़ो_optrom_data,
	.ग_लिखो_optrom		= qla24xx_ग_लिखो_optrom_data,
	.get_flash_version	= qla24xx_get_flash_version,
	.start_scsi		= qla24xx_start_scsi,
	.start_scsi_mq          = शून्य,
	.पात_isp		= qla2x00_पात_isp,
	.iospace_config		= qla2x00_iospace_config,
	.initialize_adapter	= qla2x00_initialize_adapter,
पूर्ण;

अटल काष्ठा isp_operations qla25xx_isp_ops = अणु
	.pci_config		= qla25xx_pci_config,
	.reset_chip		= qla24xx_reset_chip,
	.chip_diag		= qla24xx_chip_diag,
	.config_rings		= qla24xx_config_rings,
	.reset_adapter		= qla24xx_reset_adapter,
	.nvram_config		= qla24xx_nvram_config,
	.update_fw_options	= qla24xx_update_fw_options,
	.load_risc		= qla24xx_load_risc,
	.pci_info_str		= qla24xx_pci_info_str,
	.fw_version_str		= qla24xx_fw_version_str,
	.पूर्णांकr_handler		= qla24xx_पूर्णांकr_handler,
	.enable_पूर्णांकrs		= qla24xx_enable_पूर्णांकrs,
	.disable_पूर्णांकrs		= qla24xx_disable_पूर्णांकrs,
	.पात_command		= qla24xx_पात_command,
	.target_reset		= qla24xx_पात_target,
	.lun_reset		= qla24xx_lun_reset,
	.fabric_login		= qla24xx_login_fabric,
	.fabric_logout		= qla24xx_fabric_logout,
	.calc_req_entries	= शून्य,
	.build_iocbs		= शून्य,
	.prep_ms_iocb		= qla24xx_prep_ms_iocb,
	.prep_ms_fdmi_iocb	= qla24xx_prep_ms_fdmi_iocb,
	.पढ़ो_nvram		= qla25xx_पढ़ो_nvram_data,
	.ग_लिखो_nvram		= qla25xx_ग_लिखो_nvram_data,
	.fw_dump		= qla25xx_fw_dump,
	.beacon_on		= qla24xx_beacon_on,
	.beacon_off		= qla24xx_beacon_off,
	.beacon_blink		= qla24xx_beacon_blink,
	.पढ़ो_optrom		= qla25xx_पढ़ो_optrom_data,
	.ग_लिखो_optrom		= qla24xx_ग_लिखो_optrom_data,
	.get_flash_version	= qla24xx_get_flash_version,
	.start_scsi		= qla24xx_dअगर_start_scsi,
	.start_scsi_mq          = qla2xxx_dअगर_start_scsi_mq,
	.पात_isp		= qla2x00_पात_isp,
	.iospace_config		= qla2x00_iospace_config,
	.initialize_adapter	= qla2x00_initialize_adapter,
पूर्ण;

अटल काष्ठा isp_operations qla81xx_isp_ops = अणु
	.pci_config		= qla25xx_pci_config,
	.reset_chip		= qla24xx_reset_chip,
	.chip_diag		= qla24xx_chip_diag,
	.config_rings		= qla24xx_config_rings,
	.reset_adapter		= qla24xx_reset_adapter,
	.nvram_config		= qla81xx_nvram_config,
	.update_fw_options	= qla24xx_update_fw_options,
	.load_risc		= qla81xx_load_risc,
	.pci_info_str		= qla24xx_pci_info_str,
	.fw_version_str		= qla24xx_fw_version_str,
	.पूर्णांकr_handler		= qla24xx_पूर्णांकr_handler,
	.enable_पूर्णांकrs		= qla24xx_enable_पूर्णांकrs,
	.disable_पूर्णांकrs		= qla24xx_disable_पूर्णांकrs,
	.पात_command		= qla24xx_पात_command,
	.target_reset		= qla24xx_पात_target,
	.lun_reset		= qla24xx_lun_reset,
	.fabric_login		= qla24xx_login_fabric,
	.fabric_logout		= qla24xx_fabric_logout,
	.calc_req_entries	= शून्य,
	.build_iocbs		= शून्य,
	.prep_ms_iocb		= qla24xx_prep_ms_iocb,
	.prep_ms_fdmi_iocb	= qla24xx_prep_ms_fdmi_iocb,
	.पढ़ो_nvram		= शून्य,
	.ग_लिखो_nvram		= शून्य,
	.fw_dump		= qla81xx_fw_dump,
	.beacon_on		= qla24xx_beacon_on,
	.beacon_off		= qla24xx_beacon_off,
	.beacon_blink		= qla83xx_beacon_blink,
	.पढ़ो_optrom		= qla25xx_पढ़ो_optrom_data,
	.ग_लिखो_optrom		= qla24xx_ग_लिखो_optrom_data,
	.get_flash_version	= qla24xx_get_flash_version,
	.start_scsi		= qla24xx_dअगर_start_scsi,
	.start_scsi_mq          = qla2xxx_dअगर_start_scsi_mq,
	.पात_isp		= qla2x00_पात_isp,
	.iospace_config		= qla2x00_iospace_config,
	.initialize_adapter	= qla2x00_initialize_adapter,
पूर्ण;

अटल काष्ठा isp_operations qla82xx_isp_ops = अणु
	.pci_config		= qla82xx_pci_config,
	.reset_chip		= qla82xx_reset_chip,
	.chip_diag		= qla24xx_chip_diag,
	.config_rings		= qla82xx_config_rings,
	.reset_adapter		= qla24xx_reset_adapter,
	.nvram_config		= qla81xx_nvram_config,
	.update_fw_options	= qla24xx_update_fw_options,
	.load_risc		= qla82xx_load_risc,
	.pci_info_str		= qla24xx_pci_info_str,
	.fw_version_str		= qla24xx_fw_version_str,
	.पूर्णांकr_handler		= qla82xx_पूर्णांकr_handler,
	.enable_पूर्णांकrs		= qla82xx_enable_पूर्णांकrs,
	.disable_पूर्णांकrs		= qla82xx_disable_पूर्णांकrs,
	.पात_command		= qla24xx_पात_command,
	.target_reset		= qla24xx_पात_target,
	.lun_reset		= qla24xx_lun_reset,
	.fabric_login		= qla24xx_login_fabric,
	.fabric_logout		= qla24xx_fabric_logout,
	.calc_req_entries	= शून्य,
	.build_iocbs		= शून्य,
	.prep_ms_iocb		= qla24xx_prep_ms_iocb,
	.prep_ms_fdmi_iocb	= qla24xx_prep_ms_fdmi_iocb,
	.पढ़ो_nvram		= qla24xx_पढ़ो_nvram_data,
	.ग_लिखो_nvram		= qla24xx_ग_लिखो_nvram_data,
	.fw_dump		= qla82xx_fw_dump,
	.beacon_on		= qla82xx_beacon_on,
	.beacon_off		= qla82xx_beacon_off,
	.beacon_blink		= शून्य,
	.पढ़ो_optrom		= qla82xx_पढ़ो_optrom_data,
	.ग_लिखो_optrom		= qla82xx_ग_लिखो_optrom_data,
	.get_flash_version	= qla82xx_get_flash_version,
	.start_scsi             = qla82xx_start_scsi,
	.start_scsi_mq          = शून्य,
	.पात_isp		= qla82xx_पात_isp,
	.iospace_config     	= qla82xx_iospace_config,
	.initialize_adapter	= qla2x00_initialize_adapter,
पूर्ण;

अटल काष्ठा isp_operations qla8044_isp_ops = अणु
	.pci_config		= qla82xx_pci_config,
	.reset_chip		= qla82xx_reset_chip,
	.chip_diag		= qla24xx_chip_diag,
	.config_rings		= qla82xx_config_rings,
	.reset_adapter		= qla24xx_reset_adapter,
	.nvram_config		= qla81xx_nvram_config,
	.update_fw_options	= qla24xx_update_fw_options,
	.load_risc		= qla82xx_load_risc,
	.pci_info_str		= qla24xx_pci_info_str,
	.fw_version_str		= qla24xx_fw_version_str,
	.पूर्णांकr_handler		= qla8044_पूर्णांकr_handler,
	.enable_पूर्णांकrs		= qla82xx_enable_पूर्णांकrs,
	.disable_पूर्णांकrs		= qla82xx_disable_पूर्णांकrs,
	.पात_command		= qla24xx_पात_command,
	.target_reset		= qla24xx_पात_target,
	.lun_reset		= qla24xx_lun_reset,
	.fabric_login		= qla24xx_login_fabric,
	.fabric_logout		= qla24xx_fabric_logout,
	.calc_req_entries	= शून्य,
	.build_iocbs		= शून्य,
	.prep_ms_iocb		= qla24xx_prep_ms_iocb,
	.prep_ms_fdmi_iocb	= qla24xx_prep_ms_fdmi_iocb,
	.पढ़ो_nvram		= शून्य,
	.ग_लिखो_nvram		= शून्य,
	.fw_dump		= qla8044_fw_dump,
	.beacon_on		= qla82xx_beacon_on,
	.beacon_off		= qla82xx_beacon_off,
	.beacon_blink		= शून्य,
	.पढ़ो_optrom		= qla8044_पढ़ो_optrom_data,
	.ग_लिखो_optrom		= qla8044_ग_लिखो_optrom_data,
	.get_flash_version	= qla82xx_get_flash_version,
	.start_scsi             = qla82xx_start_scsi,
	.start_scsi_mq          = शून्य,
	.पात_isp		= qla8044_पात_isp,
	.iospace_config		= qla82xx_iospace_config,
	.initialize_adapter	= qla2x00_initialize_adapter,
पूर्ण;

अटल काष्ठा isp_operations qla83xx_isp_ops = अणु
	.pci_config		= qla25xx_pci_config,
	.reset_chip		= qla24xx_reset_chip,
	.chip_diag		= qla24xx_chip_diag,
	.config_rings		= qla24xx_config_rings,
	.reset_adapter		= qla24xx_reset_adapter,
	.nvram_config		= qla81xx_nvram_config,
	.update_fw_options	= qla24xx_update_fw_options,
	.load_risc		= qla81xx_load_risc,
	.pci_info_str		= qla24xx_pci_info_str,
	.fw_version_str		= qla24xx_fw_version_str,
	.पूर्णांकr_handler		= qla24xx_पूर्णांकr_handler,
	.enable_पूर्णांकrs		= qla24xx_enable_पूर्णांकrs,
	.disable_पूर्णांकrs		= qla24xx_disable_पूर्णांकrs,
	.पात_command		= qla24xx_पात_command,
	.target_reset		= qla24xx_पात_target,
	.lun_reset		= qla24xx_lun_reset,
	.fabric_login		= qla24xx_login_fabric,
	.fabric_logout		= qla24xx_fabric_logout,
	.calc_req_entries	= शून्य,
	.build_iocbs		= शून्य,
	.prep_ms_iocb		= qla24xx_prep_ms_iocb,
	.prep_ms_fdmi_iocb	= qla24xx_prep_ms_fdmi_iocb,
	.पढ़ो_nvram		= शून्य,
	.ग_लिखो_nvram		= शून्य,
	.fw_dump		= qla83xx_fw_dump,
	.beacon_on		= qla24xx_beacon_on,
	.beacon_off		= qla24xx_beacon_off,
	.beacon_blink		= qla83xx_beacon_blink,
	.पढ़ो_optrom		= qla25xx_पढ़ो_optrom_data,
	.ग_लिखो_optrom		= qla24xx_ग_लिखो_optrom_data,
	.get_flash_version	= qla24xx_get_flash_version,
	.start_scsi		= qla24xx_dअगर_start_scsi,
	.start_scsi_mq          = qla2xxx_dअगर_start_scsi_mq,
	.पात_isp		= qla2x00_पात_isp,
	.iospace_config		= qla83xx_iospace_config,
	.initialize_adapter	= qla2x00_initialize_adapter,
पूर्ण;

अटल काष्ठा isp_operations qlafx00_isp_ops = अणु
	.pci_config		= qlafx00_pci_config,
	.reset_chip		= qlafx00_soft_reset,
	.chip_diag		= qlafx00_chip_diag,
	.config_rings		= qlafx00_config_rings,
	.reset_adapter		= qlafx00_soft_reset,
	.nvram_config		= शून्य,
	.update_fw_options	= शून्य,
	.load_risc		= शून्य,
	.pci_info_str		= qlafx00_pci_info_str,
	.fw_version_str		= qlafx00_fw_version_str,
	.पूर्णांकr_handler		= qlafx00_पूर्णांकr_handler,
	.enable_पूर्णांकrs		= qlafx00_enable_पूर्णांकrs,
	.disable_पूर्णांकrs		= qlafx00_disable_पूर्णांकrs,
	.पात_command		= qla24xx_async_पात_command,
	.target_reset		= qlafx00_पात_target,
	.lun_reset		= qlafx00_lun_reset,
	.fabric_login		= शून्य,
	.fabric_logout		= शून्य,
	.calc_req_entries	= शून्य,
	.build_iocbs		= शून्य,
	.prep_ms_iocb		= qla24xx_prep_ms_iocb,
	.prep_ms_fdmi_iocb	= qla24xx_prep_ms_fdmi_iocb,
	.पढ़ो_nvram		= qla24xx_पढ़ो_nvram_data,
	.ग_लिखो_nvram		= qla24xx_ग_लिखो_nvram_data,
	.fw_dump		= शून्य,
	.beacon_on		= qla24xx_beacon_on,
	.beacon_off		= qla24xx_beacon_off,
	.beacon_blink		= शून्य,
	.पढ़ो_optrom		= qla24xx_पढ़ो_optrom_data,
	.ग_लिखो_optrom		= qla24xx_ग_लिखो_optrom_data,
	.get_flash_version	= qla24xx_get_flash_version,
	.start_scsi		= qlafx00_start_scsi,
	.start_scsi_mq          = शून्य,
	.पात_isp		= qlafx00_पात_isp,
	.iospace_config		= qlafx00_iospace_config,
	.initialize_adapter	= qlafx00_initialize_adapter,
पूर्ण;

अटल काष्ठा isp_operations qla27xx_isp_ops = अणु
	.pci_config		= qla25xx_pci_config,
	.reset_chip		= qla24xx_reset_chip,
	.chip_diag		= qla24xx_chip_diag,
	.config_rings		= qla24xx_config_rings,
	.reset_adapter		= qla24xx_reset_adapter,
	.nvram_config		= qla81xx_nvram_config,
	.update_fw_options	= qla24xx_update_fw_options,
	.load_risc		= qla81xx_load_risc,
	.pci_info_str		= qla24xx_pci_info_str,
	.fw_version_str		= qla24xx_fw_version_str,
	.पूर्णांकr_handler		= qla24xx_पूर्णांकr_handler,
	.enable_पूर्णांकrs		= qla24xx_enable_पूर्णांकrs,
	.disable_पूर्णांकrs		= qla24xx_disable_पूर्णांकrs,
	.पात_command		= qla24xx_पात_command,
	.target_reset		= qla24xx_पात_target,
	.lun_reset		= qla24xx_lun_reset,
	.fabric_login		= qla24xx_login_fabric,
	.fabric_logout		= qla24xx_fabric_logout,
	.calc_req_entries	= शून्य,
	.build_iocbs		= शून्य,
	.prep_ms_iocb		= qla24xx_prep_ms_iocb,
	.prep_ms_fdmi_iocb	= qla24xx_prep_ms_fdmi_iocb,
	.पढ़ो_nvram		= शून्य,
	.ग_लिखो_nvram		= शून्य,
	.fw_dump		= qla27xx_fwdump,
	.mpi_fw_dump		= qla27xx_mpi_fwdump,
	.beacon_on		= qla24xx_beacon_on,
	.beacon_off		= qla24xx_beacon_off,
	.beacon_blink		= qla83xx_beacon_blink,
	.पढ़ो_optrom		= qla25xx_पढ़ो_optrom_data,
	.ग_लिखो_optrom		= qla24xx_ग_लिखो_optrom_data,
	.get_flash_version	= qla24xx_get_flash_version,
	.start_scsi		= qla24xx_dअगर_start_scsi,
	.start_scsi_mq          = qla2xxx_dअगर_start_scsi_mq,
	.पात_isp		= qla2x00_पात_isp,
	.iospace_config		= qla83xx_iospace_config,
	.initialize_adapter	= qla2x00_initialize_adapter,
पूर्ण;

अटल अंतरभूत व्योम
qla2x00_set_isp_flags(काष्ठा qla_hw_data *ha)
अणु
	ha->device_type = DT_EXTENDED_IDS;
	चयन (ha->pdev->device) अणु
	हाल PCI_DEVICE_ID_QLOGIC_ISP2100:
		ha->isp_type |= DT_ISP2100;
		ha->device_type &= ~DT_EXTENDED_IDS;
		ha->fw_srisc_address = RISC_START_ADDRESS_2100;
		अवरोध;
	हाल PCI_DEVICE_ID_QLOGIC_ISP2200:
		ha->isp_type |= DT_ISP2200;
		ha->device_type &= ~DT_EXTENDED_IDS;
		ha->fw_srisc_address = RISC_START_ADDRESS_2100;
		अवरोध;
	हाल PCI_DEVICE_ID_QLOGIC_ISP2300:
		ha->isp_type |= DT_ISP2300;
		ha->device_type |= DT_ZIO_SUPPORTED;
		ha->fw_srisc_address = RISC_START_ADDRESS_2300;
		अवरोध;
	हाल PCI_DEVICE_ID_QLOGIC_ISP2312:
		ha->isp_type |= DT_ISP2312;
		ha->device_type |= DT_ZIO_SUPPORTED;
		ha->fw_srisc_address = RISC_START_ADDRESS_2300;
		अवरोध;
	हाल PCI_DEVICE_ID_QLOGIC_ISP2322:
		ha->isp_type |= DT_ISP2322;
		ha->device_type |= DT_ZIO_SUPPORTED;
		अगर (ha->pdev->subप्रणाली_venकरोr == 0x1028 &&
		    ha->pdev->subप्रणाली_device == 0x0170)
			ha->device_type |= DT_OEM_001;
		ha->fw_srisc_address = RISC_START_ADDRESS_2300;
		अवरोध;
	हाल PCI_DEVICE_ID_QLOGIC_ISP6312:
		ha->isp_type |= DT_ISP6312;
		ha->fw_srisc_address = RISC_START_ADDRESS_2300;
		अवरोध;
	हाल PCI_DEVICE_ID_QLOGIC_ISP6322:
		ha->isp_type |= DT_ISP6322;
		ha->fw_srisc_address = RISC_START_ADDRESS_2300;
		अवरोध;
	हाल PCI_DEVICE_ID_QLOGIC_ISP2422:
		ha->isp_type |= DT_ISP2422;
		ha->device_type |= DT_ZIO_SUPPORTED;
		ha->device_type |= DT_FWI2;
		ha->device_type |= DT_IIDMA;
		ha->fw_srisc_address = RISC_START_ADDRESS_2400;
		अवरोध;
	हाल PCI_DEVICE_ID_QLOGIC_ISP2432:
		ha->isp_type |= DT_ISP2432;
		ha->device_type |= DT_ZIO_SUPPORTED;
		ha->device_type |= DT_FWI2;
		ha->device_type |= DT_IIDMA;
		ha->fw_srisc_address = RISC_START_ADDRESS_2400;
		अवरोध;
	हाल PCI_DEVICE_ID_QLOGIC_ISP8432:
		ha->isp_type |= DT_ISP8432;
		ha->device_type |= DT_ZIO_SUPPORTED;
		ha->device_type |= DT_FWI2;
		ha->device_type |= DT_IIDMA;
		ha->fw_srisc_address = RISC_START_ADDRESS_2400;
		अवरोध;
	हाल PCI_DEVICE_ID_QLOGIC_ISP5422:
		ha->isp_type |= DT_ISP5422;
		ha->device_type |= DT_FWI2;
		ha->fw_srisc_address = RISC_START_ADDRESS_2400;
		अवरोध;
	हाल PCI_DEVICE_ID_QLOGIC_ISP5432:
		ha->isp_type |= DT_ISP5432;
		ha->device_type |= DT_FWI2;
		ha->fw_srisc_address = RISC_START_ADDRESS_2400;
		अवरोध;
	हाल PCI_DEVICE_ID_QLOGIC_ISP2532:
		ha->isp_type |= DT_ISP2532;
		ha->device_type |= DT_ZIO_SUPPORTED;
		ha->device_type |= DT_FWI2;
		ha->device_type |= DT_IIDMA;
		ha->fw_srisc_address = RISC_START_ADDRESS_2400;
		अवरोध;
	हाल PCI_DEVICE_ID_QLOGIC_ISP8001:
		ha->isp_type |= DT_ISP8001;
		ha->device_type |= DT_ZIO_SUPPORTED;
		ha->device_type |= DT_FWI2;
		ha->device_type |= DT_IIDMA;
		ha->fw_srisc_address = RISC_START_ADDRESS_2400;
		अवरोध;
	हाल PCI_DEVICE_ID_QLOGIC_ISP8021:
		ha->isp_type |= DT_ISP8021;
		ha->device_type |= DT_ZIO_SUPPORTED;
		ha->device_type |= DT_FWI2;
		ha->fw_srisc_address = RISC_START_ADDRESS_2400;
		/* Initialize 82XX ISP flags */
		qla82xx_init_flags(ha);
		अवरोध;
	 हाल PCI_DEVICE_ID_QLOGIC_ISP8044:
		ha->isp_type |= DT_ISP8044;
		ha->device_type |= DT_ZIO_SUPPORTED;
		ha->device_type |= DT_FWI2;
		ha->fw_srisc_address = RISC_START_ADDRESS_2400;
		/* Initialize 82XX ISP flags */
		qla82xx_init_flags(ha);
		अवरोध;
	हाल PCI_DEVICE_ID_QLOGIC_ISP2031:
		ha->isp_type |= DT_ISP2031;
		ha->device_type |= DT_ZIO_SUPPORTED;
		ha->device_type |= DT_FWI2;
		ha->device_type |= DT_IIDMA;
		ha->device_type |= DT_T10_PI;
		ha->fw_srisc_address = RISC_START_ADDRESS_2400;
		अवरोध;
	हाल PCI_DEVICE_ID_QLOGIC_ISP8031:
		ha->isp_type |= DT_ISP8031;
		ha->device_type |= DT_ZIO_SUPPORTED;
		ha->device_type |= DT_FWI2;
		ha->device_type |= DT_IIDMA;
		ha->device_type |= DT_T10_PI;
		ha->fw_srisc_address = RISC_START_ADDRESS_2400;
		अवरोध;
	हाल PCI_DEVICE_ID_QLOGIC_ISPF001:
		ha->isp_type |= DT_ISPFX00;
		अवरोध;
	हाल PCI_DEVICE_ID_QLOGIC_ISP2071:
		ha->isp_type |= DT_ISP2071;
		ha->device_type |= DT_ZIO_SUPPORTED;
		ha->device_type |= DT_FWI2;
		ha->device_type |= DT_IIDMA;
		ha->device_type |= DT_T10_PI;
		ha->fw_srisc_address = RISC_START_ADDRESS_2400;
		अवरोध;
	हाल PCI_DEVICE_ID_QLOGIC_ISP2271:
		ha->isp_type |= DT_ISP2271;
		ha->device_type |= DT_ZIO_SUPPORTED;
		ha->device_type |= DT_FWI2;
		ha->device_type |= DT_IIDMA;
		ha->device_type |= DT_T10_PI;
		ha->fw_srisc_address = RISC_START_ADDRESS_2400;
		अवरोध;
	हाल PCI_DEVICE_ID_QLOGIC_ISP2261:
		ha->isp_type |= DT_ISP2261;
		ha->device_type |= DT_ZIO_SUPPORTED;
		ha->device_type |= DT_FWI2;
		ha->device_type |= DT_IIDMA;
		ha->device_type |= DT_T10_PI;
		ha->fw_srisc_address = RISC_START_ADDRESS_2400;
		अवरोध;
	हाल PCI_DEVICE_ID_QLOGIC_ISP2081:
	हाल PCI_DEVICE_ID_QLOGIC_ISP2089:
		ha->isp_type |= DT_ISP2081;
		ha->device_type |= DT_ZIO_SUPPORTED;
		ha->device_type |= DT_FWI2;
		ha->device_type |= DT_IIDMA;
		ha->device_type |= DT_T10_PI;
		ha->fw_srisc_address = RISC_START_ADDRESS_2400;
		अवरोध;
	हाल PCI_DEVICE_ID_QLOGIC_ISP2281:
	हाल PCI_DEVICE_ID_QLOGIC_ISP2289:
		ha->isp_type |= DT_ISP2281;
		ha->device_type |= DT_ZIO_SUPPORTED;
		ha->device_type |= DT_FWI2;
		ha->device_type |= DT_IIDMA;
		ha->device_type |= DT_T10_PI;
		ha->fw_srisc_address = RISC_START_ADDRESS_2400;
		अवरोध;
	पूर्ण

	अगर (IS_QLA82XX(ha))
		ha->port_no = ha->portnum & 1;
	अन्यथा अणु
		/* Get adapter physical port no from पूर्णांकerrupt pin रेजिस्टर. */
		pci_पढ़ो_config_byte(ha->pdev, PCI_INTERRUPT_PIN, &ha->port_no);
		अगर (IS_QLA25XX(ha) || IS_QLA2031(ha) ||
		    IS_QLA27XX(ha) || IS_QLA28XX(ha))
			ha->port_no--;
		अन्यथा
			ha->port_no = !(ha->port_no & 1);
	पूर्ण

	ql_dbg_pci(ql_dbg_init, ha->pdev, 0x000b,
	    "device_type=0x%x port=%d fw_srisc_address=0x%x.\n",
	    ha->device_type, ha->port_no, ha->fw_srisc_address);
पूर्ण

अटल व्योम
qla2xxx_scan_start(काष्ठा Scsi_Host *shost)
अणु
	scsi_qla_host_t *vha = shost_priv(shost);

	अगर (vha->hw->flags.running_gold_fw)
		वापस;

	set_bit(LOOP_RESYNC_NEEDED, &vha->dpc_flags);
	set_bit(LOCAL_LOOP_UPDATE, &vha->dpc_flags);
	set_bit(RSCN_UPDATE, &vha->dpc_flags);
	set_bit(NPIV_CONFIG_NEEDED, &vha->dpc_flags);
पूर्ण

अटल पूर्णांक
qla2xxx_scan_finished(काष्ठा Scsi_Host *shost, अचिन्हित दीर्घ समय)
अणु
	scsi_qla_host_t *vha = shost_priv(shost);

	अगर (test_bit(UNLOADING, &vha->dpc_flags))
		वापस 1;
	अगर (!vha->host)
		वापस 1;
	अगर (समय > vha->hw->loop_reset_delay * HZ)
		वापस 1;

	वापस atomic_पढ़ो(&vha->loop_state) == LOOP_READY;
पूर्ण

अटल व्योम qla2x00_iocb_work_fn(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा scsi_qla_host *vha = container_of(work,
		काष्ठा scsi_qla_host, iocb_work);
	काष्ठा qla_hw_data *ha = vha->hw;
	काष्ठा scsi_qla_host *base_vha = pci_get_drvdata(ha->pdev);
	पूर्णांक i = 2;
	अचिन्हित दीर्घ flags;

	अगर (test_bit(UNLOADING, &base_vha->dpc_flags))
		वापस;

	जबतक (!list_empty(&vha->work_list) && i > 0) अणु
		qla2x00_करो_work(vha);
		i--;
	पूर्ण

	spin_lock_irqsave(&vha->work_lock, flags);
	clear_bit(IOCB_WORK_ACTIVE, &vha->dpc_flags);
	spin_unlock_irqrestore(&vha->work_lock, flags);
पूर्ण

/*
 * PCI driver पूर्णांकerface
 */
अटल पूर्णांक
qla2x00_probe_one(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *id)
अणु
	पूर्णांक	ret = -ENODEV;
	काष्ठा Scsi_Host *host;
	scsi_qla_host_t *base_vha = शून्य;
	काष्ठा qla_hw_data *ha;
	अक्षर pci_info[30];
	अक्षर fw_str[30], wq_name[30];
	काष्ठा scsi_host_ढाँचा *sht;
	पूर्णांक bars, mem_only = 0;
	uपूर्णांक16_t req_length = 0, rsp_length = 0;
	काष्ठा req_que *req = शून्य;
	काष्ठा rsp_que *rsp = शून्य;
	पूर्णांक i;

	bars = pci_select_bars(pdev, IORESOURCE_MEM | IORESOURCE_IO);
	sht = &qla2xxx_driver_ढाँचा;
	अगर (pdev->device == PCI_DEVICE_ID_QLOGIC_ISP2422 ||
	    pdev->device == PCI_DEVICE_ID_QLOGIC_ISP2432 ||
	    pdev->device == PCI_DEVICE_ID_QLOGIC_ISP8432 ||
	    pdev->device == PCI_DEVICE_ID_QLOGIC_ISP5422 ||
	    pdev->device == PCI_DEVICE_ID_QLOGIC_ISP5432 ||
	    pdev->device == PCI_DEVICE_ID_QLOGIC_ISP2532 ||
	    pdev->device == PCI_DEVICE_ID_QLOGIC_ISP8001 ||
	    pdev->device == PCI_DEVICE_ID_QLOGIC_ISP8021 ||
	    pdev->device == PCI_DEVICE_ID_QLOGIC_ISP2031 ||
	    pdev->device == PCI_DEVICE_ID_QLOGIC_ISP8031 ||
	    pdev->device == PCI_DEVICE_ID_QLOGIC_ISPF001 ||
	    pdev->device == PCI_DEVICE_ID_QLOGIC_ISP8044 ||
	    pdev->device == PCI_DEVICE_ID_QLOGIC_ISP2071 ||
	    pdev->device == PCI_DEVICE_ID_QLOGIC_ISP2271 ||
	    pdev->device == PCI_DEVICE_ID_QLOGIC_ISP2261 ||
	    pdev->device == PCI_DEVICE_ID_QLOGIC_ISP2081 ||
	    pdev->device == PCI_DEVICE_ID_QLOGIC_ISP2281 ||
	    pdev->device == PCI_DEVICE_ID_QLOGIC_ISP2089 ||
	    pdev->device == PCI_DEVICE_ID_QLOGIC_ISP2289) अणु
		bars = pci_select_bars(pdev, IORESOURCE_MEM);
		mem_only = 1;
		ql_dbg_pci(ql_dbg_init, pdev, 0x0007,
		    "Mem only adapter.\n");
	पूर्ण
	ql_dbg_pci(ql_dbg_init, pdev, 0x0008,
	    "Bars=%d.\n", bars);

	अगर (mem_only) अणु
		अगर (pci_enable_device_mem(pdev))
			वापस ret;
	पूर्ण अन्यथा अणु
		अगर (pci_enable_device(pdev))
			वापस ret;
	पूर्ण

	/* This may fail but that's ok */
	pci_enable_pcie_error_reporting(pdev);

	ha = kzalloc(माप(काष्ठा qla_hw_data), GFP_KERNEL);
	अगर (!ha) अणु
		ql_log_pci(ql_log_fatal, pdev, 0x0009,
		    "Unable to allocate memory for ha.\n");
		जाओ disable_device;
	पूर्ण
	ql_dbg_pci(ql_dbg_init, pdev, 0x000a,
	    "Memory allocated for ha=%p.\n", ha);
	ha->pdev = pdev;
	INIT_LIST_HEAD(&ha->tgt.q_full_list);
	spin_lock_init(&ha->tgt.q_full_lock);
	spin_lock_init(&ha->tgt.sess_lock);
	spin_lock_init(&ha->tgt.atio_lock);

	atomic_set(&ha->nvme_active_aen_cnt, 0);

	/* Clear our data area */
	ha->bars = bars;
	ha->mem_only = mem_only;
	spin_lock_init(&ha->hardware_lock);
	spin_lock_init(&ha->vport_slock);
	mutex_init(&ha->selflogin_lock);
	mutex_init(&ha->optrom_mutex);

	/* Set ISP-type inक्रमmation. */
	qla2x00_set_isp_flags(ha);

	/* Set EEH reset type to fundamental अगर required by hba */
	अगर (IS_QLA24XX(ha) || IS_QLA25XX(ha) || IS_QLA81XX(ha) ||
	    IS_QLA83XX(ha) || IS_QLA27XX(ha) || IS_QLA28XX(ha))
		pdev->needs_freset = 1;

	ha->prev_topology = 0;
	ha->init_cb_size = माप(init_cb_t);
	ha->link_data_rate = PORT_SPEED_UNKNOWN;
	ha->optrom_size = OPTROM_SIZE_2300;
	ha->max_exchg = FW_MAX_EXCHANGES_CNT;
	atomic_set(&ha->num_pend_mbx_stage1, 0);
	atomic_set(&ha->num_pend_mbx_stage2, 0);
	atomic_set(&ha->num_pend_mbx_stage3, 0);
	atomic_set(&ha->zio_threshold, DEFAULT_ZIO_THRESHOLD);
	ha->last_zio_threshold = DEFAULT_ZIO_THRESHOLD;

	/* Assign ISP specअगरic operations. */
	अगर (IS_QLA2100(ha)) अणु
		ha->max_fibre_devices = MAX_FIBRE_DEVICES_2100;
		ha->mbx_count = MAILBOX_REGISTER_COUNT_2100;
		req_length = REQUEST_ENTRY_CNT_2100;
		rsp_length = RESPONSE_ENTRY_CNT_2100;
		ha->max_loop_id = SNS_LAST_LOOP_ID_2100;
		ha->gid_list_info_size = 4;
		ha->flash_conf_off = ~0;
		ha->flash_data_off = ~0;
		ha->nvram_conf_off = ~0;
		ha->nvram_data_off = ~0;
		ha->isp_ops = &qla2100_isp_ops;
	पूर्ण अन्यथा अगर (IS_QLA2200(ha)) अणु
		ha->max_fibre_devices = MAX_FIBRE_DEVICES_2100;
		ha->mbx_count = MAILBOX_REGISTER_COUNT_2200;
		req_length = REQUEST_ENTRY_CNT_2200;
		rsp_length = RESPONSE_ENTRY_CNT_2100;
		ha->max_loop_id = SNS_LAST_LOOP_ID_2100;
		ha->gid_list_info_size = 4;
		ha->flash_conf_off = ~0;
		ha->flash_data_off = ~0;
		ha->nvram_conf_off = ~0;
		ha->nvram_data_off = ~0;
		ha->isp_ops = &qla2100_isp_ops;
	पूर्ण अन्यथा अगर (IS_QLA23XX(ha)) अणु
		ha->max_fibre_devices = MAX_FIBRE_DEVICES_2100;
		ha->mbx_count = MAILBOX_REGISTER_COUNT;
		req_length = REQUEST_ENTRY_CNT_2200;
		rsp_length = RESPONSE_ENTRY_CNT_2300;
		ha->max_loop_id = SNS_LAST_LOOP_ID_2300;
		ha->gid_list_info_size = 6;
		अगर (IS_QLA2322(ha) || IS_QLA6322(ha))
			ha->optrom_size = OPTROM_SIZE_2322;
		ha->flash_conf_off = ~0;
		ha->flash_data_off = ~0;
		ha->nvram_conf_off = ~0;
		ha->nvram_data_off = ~0;
		ha->isp_ops = &qla2300_isp_ops;
	पूर्ण अन्यथा अगर (IS_QLA24XX_TYPE(ha)) अणु
		ha->max_fibre_devices = MAX_FIBRE_DEVICES_2400;
		ha->mbx_count = MAILBOX_REGISTER_COUNT;
		req_length = REQUEST_ENTRY_CNT_24XX;
		rsp_length = RESPONSE_ENTRY_CNT_2300;
		ha->tgt.atio_q_length = ATIO_ENTRY_CNT_24XX;
		ha->max_loop_id = SNS_LAST_LOOP_ID_2300;
		ha->init_cb_size = माप(काष्ठा mid_init_cb_24xx);
		ha->gid_list_info_size = 8;
		ha->optrom_size = OPTROM_SIZE_24XX;
		ha->nvram_npiv_size = QLA_MAX_VPORTS_QLA24XX;
		ha->isp_ops = &qla24xx_isp_ops;
		ha->flash_conf_off = FARX_ACCESS_FLASH_CONF;
		ha->flash_data_off = FARX_ACCESS_FLASH_DATA;
		ha->nvram_conf_off = FARX_ACCESS_NVRAM_CONF;
		ha->nvram_data_off = FARX_ACCESS_NVRAM_DATA;
	पूर्ण अन्यथा अगर (IS_QLA25XX(ha)) अणु
		ha->max_fibre_devices = MAX_FIBRE_DEVICES_2400;
		ha->mbx_count = MAILBOX_REGISTER_COUNT;
		req_length = REQUEST_ENTRY_CNT_24XX;
		rsp_length = RESPONSE_ENTRY_CNT_2300;
		ha->tgt.atio_q_length = ATIO_ENTRY_CNT_24XX;
		ha->max_loop_id = SNS_LAST_LOOP_ID_2300;
		ha->init_cb_size = माप(काष्ठा mid_init_cb_24xx);
		ha->gid_list_info_size = 8;
		ha->optrom_size = OPTROM_SIZE_25XX;
		ha->nvram_npiv_size = QLA_MAX_VPORTS_QLA25XX;
		ha->isp_ops = &qla25xx_isp_ops;
		ha->flash_conf_off = FARX_ACCESS_FLASH_CONF;
		ha->flash_data_off = FARX_ACCESS_FLASH_DATA;
		ha->nvram_conf_off = FARX_ACCESS_NVRAM_CONF;
		ha->nvram_data_off = FARX_ACCESS_NVRAM_DATA;
	पूर्ण अन्यथा अगर (IS_QLA81XX(ha)) अणु
		ha->max_fibre_devices = MAX_FIBRE_DEVICES_2400;
		ha->mbx_count = MAILBOX_REGISTER_COUNT;
		req_length = REQUEST_ENTRY_CNT_24XX;
		rsp_length = RESPONSE_ENTRY_CNT_2300;
		ha->tgt.atio_q_length = ATIO_ENTRY_CNT_24XX;
		ha->max_loop_id = SNS_LAST_LOOP_ID_2300;
		ha->init_cb_size = माप(काष्ठा mid_init_cb_81xx);
		ha->gid_list_info_size = 8;
		ha->optrom_size = OPTROM_SIZE_81XX;
		ha->nvram_npiv_size = QLA_MAX_VPORTS_QLA25XX;
		ha->isp_ops = &qla81xx_isp_ops;
		ha->flash_conf_off = FARX_ACCESS_FLASH_CONF_81XX;
		ha->flash_data_off = FARX_ACCESS_FLASH_DATA_81XX;
		ha->nvram_conf_off = ~0;
		ha->nvram_data_off = ~0;
	पूर्ण अन्यथा अगर (IS_QLA82XX(ha)) अणु
		ha->max_fibre_devices = MAX_FIBRE_DEVICES_2400;
		ha->mbx_count = MAILBOX_REGISTER_COUNT;
		req_length = REQUEST_ENTRY_CNT_82XX;
		rsp_length = RESPONSE_ENTRY_CNT_82XX;
		ha->max_loop_id = SNS_LAST_LOOP_ID_2300;
		ha->init_cb_size = माप(काष्ठा mid_init_cb_81xx);
		ha->gid_list_info_size = 8;
		ha->optrom_size = OPTROM_SIZE_82XX;
		ha->nvram_npiv_size = QLA_MAX_VPORTS_QLA25XX;
		ha->isp_ops = &qla82xx_isp_ops;
		ha->flash_conf_off = FARX_ACCESS_FLASH_CONF;
		ha->flash_data_off = FARX_ACCESS_FLASH_DATA;
		ha->nvram_conf_off = FARX_ACCESS_NVRAM_CONF;
		ha->nvram_data_off = FARX_ACCESS_NVRAM_DATA;
	पूर्ण अन्यथा अगर (IS_QLA8044(ha)) अणु
		ha->max_fibre_devices = MAX_FIBRE_DEVICES_2400;
		ha->mbx_count = MAILBOX_REGISTER_COUNT;
		req_length = REQUEST_ENTRY_CNT_82XX;
		rsp_length = RESPONSE_ENTRY_CNT_82XX;
		ha->max_loop_id = SNS_LAST_LOOP_ID_2300;
		ha->init_cb_size = माप(काष्ठा mid_init_cb_81xx);
		ha->gid_list_info_size = 8;
		ha->optrom_size = OPTROM_SIZE_83XX;
		ha->nvram_npiv_size = QLA_MAX_VPORTS_QLA25XX;
		ha->isp_ops = &qla8044_isp_ops;
		ha->flash_conf_off = FARX_ACCESS_FLASH_CONF;
		ha->flash_data_off = FARX_ACCESS_FLASH_DATA;
		ha->nvram_conf_off = FARX_ACCESS_NVRAM_CONF;
		ha->nvram_data_off = FARX_ACCESS_NVRAM_DATA;
	पूर्ण अन्यथा अगर (IS_QLA83XX(ha)) अणु
		ha->portnum = PCI_FUNC(ha->pdev->devfn);
		ha->max_fibre_devices = MAX_FIBRE_DEVICES_2400;
		ha->mbx_count = MAILBOX_REGISTER_COUNT;
		req_length = REQUEST_ENTRY_CNT_83XX;
		rsp_length = RESPONSE_ENTRY_CNT_83XX;
		ha->tgt.atio_q_length = ATIO_ENTRY_CNT_24XX;
		ha->max_loop_id = SNS_LAST_LOOP_ID_2300;
		ha->init_cb_size = माप(काष्ठा mid_init_cb_81xx);
		ha->gid_list_info_size = 8;
		ha->optrom_size = OPTROM_SIZE_83XX;
		ha->nvram_npiv_size = QLA_MAX_VPORTS_QLA25XX;
		ha->isp_ops = &qla83xx_isp_ops;
		ha->flash_conf_off = FARX_ACCESS_FLASH_CONF_81XX;
		ha->flash_data_off = FARX_ACCESS_FLASH_DATA_81XX;
		ha->nvram_conf_off = ~0;
		ha->nvram_data_off = ~0;
	पूर्ण  अन्यथा अगर (IS_QLAFX00(ha)) अणु
		ha->max_fibre_devices = MAX_FIBRE_DEVICES_FX00;
		ha->mbx_count = MAILBOX_REGISTER_COUNT_FX00;
		ha->aen_mbx_count = AEN_MAILBOX_REGISTER_COUNT_FX00;
		req_length = REQUEST_ENTRY_CNT_FX00;
		rsp_length = RESPONSE_ENTRY_CNT_FX00;
		ha->isp_ops = &qlafx00_isp_ops;
		ha->port_करोwn_retry_count = 30; /* शेष value */
		ha->mr.fw_hbt_cnt = QLAFX00_HEARTBEAT_INTERVAL;
		ha->mr.fw_reset_समयr_tick = QLAFX00_RESET_INTERVAL;
		ha->mr.fw_critemp_समयr_tick = QLAFX00_CRITEMP_INTERVAL;
		ha->mr.fw_hbt_en = 1;
		ha->mr.host_info_resend = false;
		ha->mr.hinfo_resend_समयr_tick = QLAFX00_HINFO_RESEND_INTERVAL;
	पूर्ण अन्यथा अगर (IS_QLA27XX(ha)) अणु
		ha->portnum = PCI_FUNC(ha->pdev->devfn);
		ha->max_fibre_devices = MAX_FIBRE_DEVICES_2400;
		ha->mbx_count = MAILBOX_REGISTER_COUNT;
		req_length = REQUEST_ENTRY_CNT_83XX;
		rsp_length = RESPONSE_ENTRY_CNT_83XX;
		ha->tgt.atio_q_length = ATIO_ENTRY_CNT_24XX;
		ha->max_loop_id = SNS_LAST_LOOP_ID_2300;
		ha->init_cb_size = माप(काष्ठा mid_init_cb_81xx);
		ha->gid_list_info_size = 8;
		ha->optrom_size = OPTROM_SIZE_83XX;
		ha->nvram_npiv_size = QLA_MAX_VPORTS_QLA25XX;
		ha->isp_ops = &qla27xx_isp_ops;
		ha->flash_conf_off = FARX_ACCESS_FLASH_CONF_81XX;
		ha->flash_data_off = FARX_ACCESS_FLASH_DATA_81XX;
		ha->nvram_conf_off = ~0;
		ha->nvram_data_off = ~0;
	पूर्ण अन्यथा अगर (IS_QLA28XX(ha)) अणु
		ha->portnum = PCI_FUNC(ha->pdev->devfn);
		ha->max_fibre_devices = MAX_FIBRE_DEVICES_2400;
		ha->mbx_count = MAILBOX_REGISTER_COUNT;
		req_length = REQUEST_ENTRY_CNT_24XX;
		rsp_length = RESPONSE_ENTRY_CNT_2300;
		ha->tgt.atio_q_length = ATIO_ENTRY_CNT_24XX;
		ha->max_loop_id = SNS_LAST_LOOP_ID_2300;
		ha->init_cb_size = माप(काष्ठा mid_init_cb_81xx);
		ha->gid_list_info_size = 8;
		ha->optrom_size = OPTROM_SIZE_28XX;
		ha->nvram_npiv_size = QLA_MAX_VPORTS_QLA25XX;
		ha->isp_ops = &qla27xx_isp_ops;
		ha->flash_conf_off = FARX_ACCESS_FLASH_CONF_28XX;
		ha->flash_data_off = FARX_ACCESS_FLASH_DATA_28XX;
		ha->nvram_conf_off = ~0;
		ha->nvram_data_off = ~0;
	पूर्ण

	ql_dbg_pci(ql_dbg_init, pdev, 0x001e,
	    "mbx_count=%d, req_length=%d, "
	    "rsp_length=%d, max_loop_id=%d, init_cb_size=%d, "
	    "gid_list_info_size=%d, optrom_size=%d, nvram_npiv_size=%d, "
	    "max_fibre_devices=%d.\n",
	    ha->mbx_count, req_length, rsp_length, ha->max_loop_id,
	    ha->init_cb_size, ha->gid_list_info_size, ha->optrom_size,
	    ha->nvram_npiv_size, ha->max_fibre_devices);
	ql_dbg_pci(ql_dbg_init, pdev, 0x001f,
	    "isp_ops=%p, flash_conf_off=%d, "
	    "flash_data_off=%d, nvram_conf_off=%d, nvram_data_off=%d.\n",
	    ha->isp_ops, ha->flash_conf_off, ha->flash_data_off,
	    ha->nvram_conf_off, ha->nvram_data_off);

	/* Configure PCI I/O space */
	ret = ha->isp_ops->iospace_config(ha);
	अगर (ret)
		जाओ iospace_config_failed;

	ql_log_pci(ql_log_info, pdev, 0x001d,
	    "Found an ISP%04X irq %d iobase 0x%p.\n",
	    pdev->device, pdev->irq, ha->iobase);
	mutex_init(&ha->vport_lock);
	mutex_init(&ha->mq_lock);
	init_completion(&ha->mbx_cmd_comp);
	complete(&ha->mbx_cmd_comp);
	init_completion(&ha->mbx_पूर्णांकr_comp);
	init_completion(&ha->dcbx_comp);
	init_completion(&ha->lb_portup_comp);

	set_bit(0, (अचिन्हित दीर्घ *) ha->vp_idx_map);

	qla2x00_config_dma_addressing(ha);
	ql_dbg_pci(ql_dbg_init, pdev, 0x0020,
	    "64 Bit addressing is %s.\n",
	    ha->flags.enable_64bit_addressing ? "enable" :
	    "disable");
	ret = qla2x00_mem_alloc(ha, req_length, rsp_length, &req, &rsp);
	अगर (ret) अणु
		ql_log_pci(ql_log_fatal, pdev, 0x0031,
		    "Failed to allocate memory for adapter, aborting.\n");

		जाओ probe_hw_failed;
	पूर्ण

	req->max_q_depth = MAX_Q_DEPTH;
	अगर (ql2xmaxqdepth != 0 && ql2xmaxqdepth <= 0xffffU)
		req->max_q_depth = ql2xmaxqdepth;


	base_vha = qla2x00_create_host(sht, ha);
	अगर (!base_vha) अणु
		ret = -ENOMEM;
		जाओ probe_hw_failed;
	पूर्ण

	pci_set_drvdata(pdev, base_vha);
	set_bit(PFLG_DRIVER_PROBING, &base_vha->pci_flags);

	host = base_vha->host;
	base_vha->req = req;
	अगर (IS_QLA2XXX_MIDTYPE(ha))
		base_vha->mgmt_svr_loop_id =
			qla2x00_reserve_mgmt_server_loop_id(base_vha);
	अन्यथा
		base_vha->mgmt_svr_loop_id = MANAGEMENT_SERVER +
						base_vha->vp_idx;

	/* Setup fcport ढाँचा काष्ठाure. */
	ha->mr.fcport.vha = base_vha;
	ha->mr.fcport.port_type = FCT_UNKNOWN;
	ha->mr.fcport.loop_id = FC_NO_LOOP_ID;
	qla2x00_set_fcport_state(&ha->mr.fcport, FCS_UNCONFIGURED);
	ha->mr.fcport.supported_classes = FC_COS_UNSPECIFIED;
	ha->mr.fcport.scan_state = 1;

	qla2xxx_reset_stats(host, QLA2XX_HW_ERROR | QLA2XX_SHT_LNK_DWN |
			    QLA2XX_INT_ERR | QLA2XX_CMD_TIMEOUT |
			    QLA2XX_RESET_CMD_ERR | QLA2XX_TGT_SHT_LNK_DOWN);

	/* Set the SG table size based on ISP type */
	अगर (!IS_FWI2_CAPABLE(ha)) अणु
		अगर (IS_QLA2100(ha))
			host->sg_tablesize = 32;
	पूर्ण अन्यथा अणु
		अगर (!IS_QLA82XX(ha))
			host->sg_tablesize = QLA_SG_ALL;
	पूर्ण
	host->max_id = ha->max_fibre_devices;
	host->cmd_per_lun = 3;
	host->unique_id = host->host_no;
	अगर (IS_T10_PI_CAPABLE(ha) && ql2xenabledअगर)
		host->max_cmd_len = 32;
	अन्यथा
		host->max_cmd_len = MAX_CMDSZ;
	host->max_channel = MAX_BUSES - 1;
	/* Older HBAs support only 16-bit LUNs */
	अगर (!IS_QLAFX00(ha) && !IS_FWI2_CAPABLE(ha) &&
	    ql2xmaxlun > 0xffff)
		host->max_lun = 0xffff;
	अन्यथा
		host->max_lun = ql2xmaxlun;
	host->transportt = qla2xxx_transport_ढाँचा;
	sht->venकरोr_id = (SCSI_NL_VID_TYPE_PCI | PCI_VENDOR_ID_QLOGIC);

	ql_dbg(ql_dbg_init, base_vha, 0x0033,
	    "max_id=%d this_id=%d "
	    "cmd_per_len=%d unique_id=%d max_cmd_len=%d max_channel=%d "
	    "max_lun=%llu transportt=%p, vendor_id=%llu.\n", host->max_id,
	    host->this_id, host->cmd_per_lun, host->unique_id,
	    host->max_cmd_len, host->max_channel, host->max_lun,
	    host->transportt, sht->venकरोr_id);

	INIT_WORK(&base_vha->iocb_work, qla2x00_iocb_work_fn);

	/* Set up the irqs */
	ret = qla2x00_request_irqs(ha, rsp);
	अगर (ret)
		जाओ probe_failed;

	/* Alloc arrays of request and response ring ptrs */
	ret = qla2x00_alloc_queues(ha, req, rsp);
	अगर (ret) अणु
		ql_log(ql_log_fatal, base_vha, 0x003d,
		    "Failed to allocate memory for queue pointers..."
		    "aborting.\n");
		ret = -ENODEV;
		जाओ probe_failed;
	पूर्ण

	अगर (ha->mqenable) अणु
		/* number of hardware queues supported by blk/scsi-mq*/
		host->nr_hw_queues = ha->max_qpairs;

		ql_dbg(ql_dbg_init, base_vha, 0x0192,
			"blk/scsi-mq enabled, HW queues = %d.\n", host->nr_hw_queues);
	पूर्ण अन्यथा अणु
		अगर (ql2xnvmeenable) अणु
			host->nr_hw_queues = ha->max_qpairs;
			ql_dbg(ql_dbg_init, base_vha, 0x0194,
			    "FC-NVMe support is enabled, HW queues=%d\n",
			    host->nr_hw_queues);
		पूर्ण अन्यथा अणु
			ql_dbg(ql_dbg_init, base_vha, 0x0193,
			    "blk/scsi-mq disabled.\n");
		पूर्ण
	पूर्ण

	qlt_probe_one_stage1(base_vha, ha);

	pci_save_state(pdev);

	/* Assign back poपूर्णांकers */
	rsp->req = req;
	req->rsp = rsp;

	अगर (IS_QLAFX00(ha)) अणु
		ha->rsp_q_map[0] = rsp;
		ha->req_q_map[0] = req;
		set_bit(0, ha->req_qid_map);
		set_bit(0, ha->rsp_qid_map);
	पूर्ण

	/* FWI2-capable only. */
	req->req_q_in = &ha->iobase->isp24.req_q_in;
	req->req_q_out = &ha->iobase->isp24.req_q_out;
	rsp->rsp_q_in = &ha->iobase->isp24.rsp_q_in;
	rsp->rsp_q_out = &ha->iobase->isp24.rsp_q_out;
	अगर (ha->mqenable || IS_QLA83XX(ha) || IS_QLA27XX(ha) ||
	    IS_QLA28XX(ha)) अणु
		req->req_q_in = &ha->mqiobase->isp25mq.req_q_in;
		req->req_q_out = &ha->mqiobase->isp25mq.req_q_out;
		rsp->rsp_q_in = &ha->mqiobase->isp25mq.rsp_q_in;
		rsp->rsp_q_out =  &ha->mqiobase->isp25mq.rsp_q_out;
	पूर्ण

	अगर (IS_QLAFX00(ha)) अणु
		req->req_q_in = &ha->iobase->ispfx00.req_q_in;
		req->req_q_out = &ha->iobase->ispfx00.req_q_out;
		rsp->rsp_q_in = &ha->iobase->ispfx00.rsp_q_in;
		rsp->rsp_q_out = &ha->iobase->ispfx00.rsp_q_out;
	पूर्ण

	अगर (IS_P3P_TYPE(ha)) अणु
		req->req_q_out = &ha->iobase->isp82.req_q_out[0];
		rsp->rsp_q_in = &ha->iobase->isp82.rsp_q_in[0];
		rsp->rsp_q_out = &ha->iobase->isp82.rsp_q_out[0];
	पूर्ण

	ql_dbg(ql_dbg_multiq, base_vha, 0xc009,
	    "rsp_q_map=%p req_q_map=%p rsp->req=%p req->rsp=%p.\n",
	    ha->rsp_q_map, ha->req_q_map, rsp->req, req->rsp);
	ql_dbg(ql_dbg_multiq, base_vha, 0xc00a,
	    "req->req_q_in=%p req->req_q_out=%p "
	    "rsp->rsp_q_in=%p rsp->rsp_q_out=%p.\n",
	    req->req_q_in, req->req_q_out,
	    rsp->rsp_q_in, rsp->rsp_q_out);
	ql_dbg(ql_dbg_init, base_vha, 0x003e,
	    "rsp_q_map=%p req_q_map=%p rsp->req=%p req->rsp=%p.\n",
	    ha->rsp_q_map, ha->req_q_map, rsp->req, req->rsp);
	ql_dbg(ql_dbg_init, base_vha, 0x003f,
	    "req->req_q_in=%p req->req_q_out=%p rsp->rsp_q_in=%p rsp->rsp_q_out=%p.\n",
	    req->req_q_in, req->req_q_out, rsp->rsp_q_in, rsp->rsp_q_out);

	ha->wq = alloc_workqueue("qla2xxx_wq", WQ_MEM_RECLAIM, 0);
	अगर (unlikely(!ha->wq)) अणु
		ret = -ENOMEM;
		जाओ probe_failed;
	पूर्ण

	अगर (ha->isp_ops->initialize_adapter(base_vha)) अणु
		ql_log(ql_log_fatal, base_vha, 0x00d6,
		    "Failed to initialize adapter - Adapter flags %x.\n",
		    base_vha->device_flags);

		अगर (IS_QLA82XX(ha)) अणु
			qla82xx_idc_lock(ha);
			qla82xx_wr_32(ha, QLA82XX_CRB_DEV_STATE,
				QLA8XXX_DEV_FAILED);
			qla82xx_idc_unlock(ha);
			ql_log(ql_log_fatal, base_vha, 0x00d7,
			    "HW State: FAILED.\n");
		पूर्ण अन्यथा अगर (IS_QLA8044(ha)) अणु
			qla8044_idc_lock(ha);
			qla8044_wr_direct(base_vha,
				QLA8044_CRB_DEV_STATE_INDEX,
				QLA8XXX_DEV_FAILED);
			qla8044_idc_unlock(ha);
			ql_log(ql_log_fatal, base_vha, 0x0150,
			    "HW State: FAILED.\n");
		पूर्ण

		ret = -ENODEV;
		जाओ probe_failed;
	पूर्ण

	अगर (IS_QLAFX00(ha))
		host->can_queue = QLAFX00_MAX_CANQUEUE;
	अन्यथा
		host->can_queue = req->num_outstanding_cmds - 10;

	ql_dbg(ql_dbg_init, base_vha, 0x0032,
	    "can_queue=%d, req=%p, mgmt_svr_loop_id=%d, sg_tablesize=%d.\n",
	    host->can_queue, base_vha->req,
	    base_vha->mgmt_svr_loop_id, host->sg_tablesize);

	अगर (ha->mqenable) अणु
		bool startit = false;

		अगर (QLA_TGT_MODE_ENABLED())
			startit = false;

		अगर (ql2x_ini_mode == QLA2XXX_INI_MODE_ENABLED)
			startit = true;

		/* Create start of day qpairs क्रम Block MQ */
		क्रम (i = 0; i < ha->max_qpairs; i++)
			qla2xxx_create_qpair(base_vha, 5, 0, startit);
	पूर्ण
	qla_init_iocb_limit(base_vha);

	अगर (ha->flags.running_gold_fw)
		जाओ skip_dpc;

	/*
	 * Startup the kernel thपढ़ो क्रम this host adapter
	 */
	ha->dpc_thपढ़ो = kthपढ़ो_create(qla2x00_करो_dpc, ha,
	    "%s_dpc", base_vha->host_str);
	अगर (IS_ERR(ha->dpc_thपढ़ो)) अणु
		ql_log(ql_log_fatal, base_vha, 0x00ed,
		    "Failed to start DPC thread.\n");
		ret = PTR_ERR(ha->dpc_thपढ़ो);
		ha->dpc_thपढ़ो = शून्य;
		जाओ probe_failed;
	पूर्ण
	ql_dbg(ql_dbg_init, base_vha, 0x00ee,
	    "DPC thread started successfully.\n");

	/*
	 * If we're not coming up in initiator mode, we might sit क्रम
	 * a जबतक without waking up the dpc thपढ़ो, which leads to a
	 * stuck process warning.  So just kick the dpc once here and
	 * let the kthपढ़ो start (and go back to sleep in qla2x00_करो_dpc).
	 */
	qla2xxx_wake_dpc(base_vha);

	INIT_WORK(&ha->board_disable, qla2x00_disable_board_on_pci_error);

	अगर (IS_QLA8031(ha) || IS_MCTP_CAPABLE(ha)) अणु
		प्र_लिखो(wq_name, "qla2xxx_%lu_dpc_lp_wq", base_vha->host_no);
		ha->dpc_lp_wq = create_singlethपढ़ो_workqueue(wq_name);
		INIT_WORK(&ha->idc_aen, qla83xx_service_idc_aen);

		प्र_लिखो(wq_name, "qla2xxx_%lu_dpc_hp_wq", base_vha->host_no);
		ha->dpc_hp_wq = create_singlethपढ़ो_workqueue(wq_name);
		INIT_WORK(&ha->nic_core_reset, qla83xx_nic_core_reset_work);
		INIT_WORK(&ha->idc_state_handler,
		    qla83xx_idc_state_handler_work);
		INIT_WORK(&ha->nic_core_unrecoverable,
		    qla83xx_nic_core_unrecoverable_work);
	पूर्ण

skip_dpc:
	list_add_tail(&base_vha->list, &ha->vp_list);
	base_vha->host->irq = ha->pdev->irq;

	/* Initialized the समयr */
	qla2x00_start_समयr(base_vha, WATCH_INTERVAL);
	ql_dbg(ql_dbg_init, base_vha, 0x00ef,
	    "Started qla2x00_timer with "
	    "interval=%d.\n", WATCH_INTERVAL);
	ql_dbg(ql_dbg_init, base_vha, 0x00f0,
	    "Detected hba at address=%p.\n",
	    ha);

	अगर (IS_T10_PI_CAPABLE(ha) && ql2xenabledअगर) अणु
		अगर (ha->fw_attributes & BIT_4) अणु
			पूर्णांक prot = 0, guard;

			base_vha->flags.dअगरdix_supported = 1;
			ql_dbg(ql_dbg_init, base_vha, 0x00f1,
			    "Registering for DIF/DIX type 1 and 3 protection.\n");
			अगर (ql2xenabledअगर == 1)
				prot = SHOST_DIX_TYPE0_PROTECTION;
			अगर (ql2xproपंचांगask)
				scsi_host_set_prot(host, ql2xproपंचांगask);
			अन्यथा
				scsi_host_set_prot(host,
				    prot | SHOST_DIF_TYPE1_PROTECTION
				    | SHOST_DIF_TYPE2_PROTECTION
				    | SHOST_DIF_TYPE3_PROTECTION
				    | SHOST_DIX_TYPE1_PROTECTION
				    | SHOST_DIX_TYPE2_PROTECTION
				    | SHOST_DIX_TYPE3_PROTECTION);

			guard = SHOST_DIX_GUARD_CRC;

			अगर (IS_PI_IPGUARD_CAPABLE(ha) &&
			    (ql2xenabledअगर > 1 || IS_PI_DIFB_DIX0_CAPABLE(ha)))
				guard |= SHOST_DIX_GUARD_IP;

			अगर (ql2xprotguard)
				scsi_host_set_guard(host, ql2xprotguard);
			अन्यथा
				scsi_host_set_guard(host, guard);
		पूर्ण अन्यथा
			base_vha->flags.dअगरdix_supported = 0;
	पूर्ण

	ha->isp_ops->enable_पूर्णांकrs(ha);

	अगर (IS_QLAFX00(ha)) अणु
		ret = qlafx00_fx_disc(base_vha,
			&base_vha->hw->mr.fcport, FXDISC_GET_CONFIG_INFO);
		host->sg_tablesize = (ha->mr.extended_io_enabled) ?
		    QLA_SG_ALL : 128;
	पूर्ण

	ret = scsi_add_host(host, &pdev->dev);
	अगर (ret)
		जाओ probe_failed;

	base_vha->flags.init_करोne = 1;
	base_vha->flags.online = 1;
	ha->prev_minidump_failed = 0;

	ql_dbg(ql_dbg_init, base_vha, 0x00f2,
	    "Init done and hba is online.\n");

	अगर (qla_ini_mode_enabled(base_vha) ||
		qla_dual_mode_enabled(base_vha))
		scsi_scan_host(host);
	अन्यथा
		ql_dbg(ql_dbg_init, base_vha, 0x0122,
			"skipping scsi_scan_host() for non-initiator port\n");

	qla2x00_alloc_sysfs_attr(base_vha);

	अगर (IS_QLAFX00(ha)) अणु
		ret = qlafx00_fx_disc(base_vha,
			&base_vha->hw->mr.fcport, FXDISC_GET_PORT_INFO);

		/* Register प्रणाली inक्रमmation */
		ret =  qlafx00_fx_disc(base_vha,
			&base_vha->hw->mr.fcport, FXDISC_REG_HOST_INFO);
	पूर्ण

	qla2x00_init_host_attr(base_vha);

	qla2x00_dfs_setup(base_vha);

	ql_log(ql_log_info, base_vha, 0x00fb,
	    "QLogic %s - %s.\n", ha->model_number, ha->model_desc);
	ql_log(ql_log_info, base_vha, 0x00fc,
	    "ISP%04X: %s @ %s hdma%c host#=%ld fw=%s.\n",
	    pdev->device, ha->isp_ops->pci_info_str(base_vha, pci_info,
						       माप(pci_info)),
	    pci_name(pdev), ha->flags.enable_64bit_addressing ? '+' : '-',
	    base_vha->host_no,
	    ha->isp_ops->fw_version_str(base_vha, fw_str, माप(fw_str)));

	qlt_add_target(ha, base_vha);

	clear_bit(PFLG_DRIVER_PROBING, &base_vha->pci_flags);

	अगर (test_bit(UNLOADING, &base_vha->dpc_flags))
		वापस -ENODEV;

	वापस 0;

probe_failed:
	अगर (base_vha->gnl.l) अणु
		dma_मुक्त_coherent(&ha->pdev->dev, base_vha->gnl.size,
				base_vha->gnl.l, base_vha->gnl.ldma);
		base_vha->gnl.l = शून्य;
	पूर्ण

	अगर (base_vha->समयr_active)
		qla2x00_stop_समयr(base_vha);
	base_vha->flags.online = 0;
	अगर (ha->dpc_thपढ़ो) अणु
		काष्ठा task_काष्ठा *t = ha->dpc_thपढ़ो;

		ha->dpc_thपढ़ो = शून्य;
		kthपढ़ो_stop(t);
	पूर्ण

	qla2x00_मुक्त_device(base_vha);
	scsi_host_put(base_vha->host);
	/*
	 * Need to शून्य out local req/rsp after
	 * qla2x00_मुक्त_device => qla2x00_मुक्त_queues मुक्तs
	 * what these are poपूर्णांकing to. Or अन्यथा we'll
	 * fall over below in qla2x00_मुक्त_req/rsp_que.
	 */
	req = शून्य;
	rsp = शून्य;

probe_hw_failed:
	qla2x00_mem_मुक्त(ha);
	qla2x00_मुक्त_req_que(ha, req);
	qla2x00_मुक्त_rsp_que(ha, rsp);
	qla2x00_clear_drv_active(ha);

iospace_config_failed:
	अगर (IS_P3P_TYPE(ha)) अणु
		अगर (!ha->nx_pcibase)
			iounmap((device_reg_t *)ha->nx_pcibase);
		अगर (!ql2xdbwr)
			iounmap((device_reg_t *)ha->nxdb_wr_ptr);
	पूर्ण अन्यथा अणु
		अगर (ha->iobase)
			iounmap(ha->iobase);
		अगर (ha->cregbase)
			iounmap(ha->cregbase);
	पूर्ण
	pci_release_selected_regions(ha->pdev, ha->bars);
	kमुक्त(ha);

disable_device:
	pci_disable_device(pdev);
	वापस ret;
पूर्ण

अटल व्योम __qla_set_हटाओ_flag(scsi_qla_host_t *base_vha)
अणु
	scsi_qla_host_t *vp;
	अचिन्हित दीर्घ flags;
	काष्ठा qla_hw_data *ha;

	अगर (!base_vha)
		वापस;

	ha = base_vha->hw;

	spin_lock_irqsave(&ha->vport_slock, flags);
	list_क्रम_each_entry(vp, &ha->vp_list, list)
		set_bit(PFLG_DRIVER_REMOVING, &vp->pci_flags);

	/*
	 * Indicate device removal to prevent future board_disable
	 * and रुको until any pending board_disable has completed.
	 */
	set_bit(PFLG_DRIVER_REMOVING, &base_vha->pci_flags);
	spin_unlock_irqrestore(&ha->vport_slock, flags);
पूर्ण

अटल व्योम
qla2x00_shutकरोwn(काष्ठा pci_dev *pdev)
अणु
	scsi_qla_host_t *vha;
	काष्ठा qla_hw_data  *ha;

	vha = pci_get_drvdata(pdev);
	ha = vha->hw;

	ql_log(ql_log_info, vha, 0xfffa,
		"Adapter shutdown\n");

	/*
	 * Prevent future board_disable and रुको
	 * until any pending board_disable has completed.
	 */
	__qla_set_हटाओ_flag(vha);
	cancel_work_sync(&ha->board_disable);

	अगर (!atomic_पढ़ो(&pdev->enable_cnt))
		वापस;

	/* Notअगरy ISPFX00 firmware */
	अगर (IS_QLAFX00(ha))
		qlafx00_driver_shutकरोwn(vha, 20);

	/* Turn-off FCE trace */
	अगर (ha->flags.fce_enabled) अणु
		qla2x00_disable_fce_trace(vha, शून्य, शून्य);
		ha->flags.fce_enabled = 0;
	पूर्ण

	/* Turn-off EFT trace */
	अगर (ha->eft)
		qla2x00_disable_eft_trace(vha);

	अगर (IS_QLA25XX(ha) ||  IS_QLA2031(ha) || IS_QLA27XX(ha) ||
	    IS_QLA28XX(ha)) अणु
		अगर (ha->flags.fw_started)
			qla2x00_पात_isp_cleanup(vha);
	पूर्ण अन्यथा अणु
		/* Stop currently executing firmware. */
		qla2x00_try_to_stop_firmware(vha);
	पूर्ण

	/* Disable समयr */
	अगर (vha->समयr_active)
		qla2x00_stop_समयr(vha);

	/* Turn adapter off line */
	vha->flags.online = 0;

	/* turn-off पूर्णांकerrupts on the card */
	अगर (ha->पूर्णांकerrupts_on) अणु
		vha->flags.init_करोne = 0;
		ha->isp_ops->disable_पूर्णांकrs(ha);
	पूर्ण

	qla2x00_मुक्त_irqs(vha);

	qla2x00_मुक्त_fw_dump(ha);

	pci_disable_device(pdev);
	ql_log(ql_log_info, vha, 0xfffe,
		"Adapter shutdown successfully.\n");
पूर्ण

/* Deletes all the भव ports क्रम a given ha */
अटल व्योम
qla2x00_delete_all_vps(काष्ठा qla_hw_data *ha, scsi_qla_host_t *base_vha)
अणु
	scsi_qla_host_t *vha;
	अचिन्हित दीर्घ flags;

	mutex_lock(&ha->vport_lock);
	जबतक (ha->cur_vport_count) अणु
		spin_lock_irqsave(&ha->vport_slock, flags);

		BUG_ON(base_vha->list.next == &ha->vp_list);
		/* This assumes first entry in ha->vp_list is always base vha */
		vha = list_first_entry(&base_vha->list, scsi_qla_host_t, list);
		scsi_host_get(vha->host);

		spin_unlock_irqrestore(&ha->vport_slock, flags);
		mutex_unlock(&ha->vport_lock);

		qla_nvme_delete(vha);

		fc_vport_terminate(vha->fc_vport);
		scsi_host_put(vha->host);

		mutex_lock(&ha->vport_lock);
	पूर्ण
	mutex_unlock(&ha->vport_lock);
पूर्ण

/* Stops all deferred work thपढ़ोs */
अटल व्योम
qla2x00_destroy_deferred_work(काष्ठा qla_hw_data *ha)
अणु
	/* Cancel all work and destroy DPC workqueues */
	अगर (ha->dpc_lp_wq) अणु
		cancel_work_sync(&ha->idc_aen);
		destroy_workqueue(ha->dpc_lp_wq);
		ha->dpc_lp_wq = शून्य;
	पूर्ण

	अगर (ha->dpc_hp_wq) अणु
		cancel_work_sync(&ha->nic_core_reset);
		cancel_work_sync(&ha->idc_state_handler);
		cancel_work_sync(&ha->nic_core_unrecoverable);
		destroy_workqueue(ha->dpc_hp_wq);
		ha->dpc_hp_wq = शून्य;
	पूर्ण

	/* Kill the kernel thपढ़ो क्रम this host */
	अगर (ha->dpc_thपढ़ो) अणु
		काष्ठा task_काष्ठा *t = ha->dpc_thपढ़ो;

		/*
		 * qla2xxx_wake_dpc checks क्रम ->dpc_thपढ़ो
		 * so we need to zero it out.
		 */
		ha->dpc_thपढ़ो = शून्य;
		kthपढ़ो_stop(t);
	पूर्ण
पूर्ण

अटल व्योम
qla2x00_unmap_iobases(काष्ठा qla_hw_data *ha)
अणु
	अगर (IS_QLA82XX(ha)) अणु

		iounmap((device_reg_t *)ha->nx_pcibase);
		अगर (!ql2xdbwr)
			iounmap((device_reg_t *)ha->nxdb_wr_ptr);
	पूर्ण अन्यथा अणु
		अगर (ha->iobase)
			iounmap(ha->iobase);

		अगर (ha->cregbase)
			iounmap(ha->cregbase);

		अगर (ha->mqiobase)
			iounmap(ha->mqiobase);

		अगर ((IS_QLA83XX(ha) || IS_QLA27XX(ha) || IS_QLA28XX(ha)) &&
		    ha->msixbase)
			iounmap(ha->msixbase);
	पूर्ण
पूर्ण

अटल व्योम
qla2x00_clear_drv_active(काष्ठा qla_hw_data *ha)
अणु
	अगर (IS_QLA8044(ha)) अणु
		qla8044_idc_lock(ha);
		qla8044_clear_drv_active(ha);
		qla8044_idc_unlock(ha);
	पूर्ण अन्यथा अगर (IS_QLA82XX(ha)) अणु
		qla82xx_idc_lock(ha);
		qla82xx_clear_drv_active(ha);
		qla82xx_idc_unlock(ha);
	पूर्ण
पूर्ण

अटल व्योम
qla2x00_हटाओ_one(काष्ठा pci_dev *pdev)
अणु
	scsi_qla_host_t *base_vha;
	काष्ठा qla_hw_data  *ha;

	base_vha = pci_get_drvdata(pdev);
	ha = base_vha->hw;
	ql_log(ql_log_info, base_vha, 0xb079,
	    "Removing driver\n");
	__qla_set_हटाओ_flag(base_vha);
	cancel_work_sync(&ha->board_disable);

	/*
	 * If the PCI device is disabled then there was a PCI-disconnect and
	 * qla2x00_disable_board_on_pci_error has taken care of most of the
	 * resources.
	 */
	अगर (!atomic_पढ़ो(&pdev->enable_cnt)) अणु
		dma_मुक्त_coherent(&ha->pdev->dev, base_vha->gnl.size,
		    base_vha->gnl.l, base_vha->gnl.ldma);
		base_vha->gnl.l = शून्य;
		scsi_host_put(base_vha->host);
		kमुक्त(ha);
		pci_set_drvdata(pdev, शून्य);
		वापस;
	पूर्ण
	qla2x00_रुको_क्रम_hba_पढ़ोy(base_vha);

	/*
	 * अगर UNLOADING flag is alपढ़ोy set, then जारी unload,
	 * where it was set first.
	 */
	अगर (test_and_set_bit(UNLOADING, &base_vha->dpc_flags))
		वापस;

	अगर (IS_QLA25XX(ha) || IS_QLA2031(ha) || IS_QLA27XX(ha) ||
	    IS_QLA28XX(ha)) अणु
		अगर (ha->flags.fw_started)
			qla2x00_पात_isp_cleanup(base_vha);
	पूर्ण अन्यथा अगर (!IS_QLAFX00(ha)) अणु
		अगर (IS_QLA8031(ha)) अणु
			ql_dbg(ql_dbg_p3p, base_vha, 0xb07e,
			    "Clearing fcoe driver presence.\n");
			अगर (qla83xx_clear_drv_presence(base_vha) != QLA_SUCCESS)
				ql_dbg(ql_dbg_p3p, base_vha, 0xb079,
				    "Error while clearing DRV-Presence.\n");
		पूर्ण

		qla2x00_try_to_stop_firmware(base_vha);
	पूर्ण

	qla2x00_रुको_क्रम_sess_deletion(base_vha);

	qla_nvme_delete(base_vha);

	dma_मुक्त_coherent(&ha->pdev->dev,
		base_vha->gnl.size, base_vha->gnl.l, base_vha->gnl.ldma);

	base_vha->gnl.l = शून्य;

	vमुक्त(base_vha->scan.l);

	अगर (IS_QLAFX00(ha))
		qlafx00_driver_shutकरोwn(base_vha, 20);

	qla2x00_delete_all_vps(ha, base_vha);

	qla2x00_dfs_हटाओ(base_vha);

	qla84xx_put_chip(base_vha);

	/* Disable समयr */
	अगर (base_vha->समयr_active)
		qla2x00_stop_समयr(base_vha);

	base_vha->flags.online = 0;

	/* मुक्त DMA memory */
	अगर (ha->exlogin_buf)
		qla2x00_मुक्त_exlogin_buffer(ha);

	/* मुक्त DMA memory */
	अगर (ha->exchoffld_buf)
		qla2x00_मुक्त_exchoffld_buffer(ha);

	qla2x00_destroy_deferred_work(ha);

	qlt_हटाओ_target(ha, base_vha);

	qla2x00_मुक्त_sysfs_attr(base_vha, true);

	fc_हटाओ_host(base_vha->host);
	qlt_हटाओ_target_resources(ha);

	scsi_हटाओ_host(base_vha->host);

	qla2x00_मुक्त_device(base_vha);

	qla2x00_clear_drv_active(ha);

	scsi_host_put(base_vha->host);

	qla2x00_unmap_iobases(ha);

	pci_release_selected_regions(ha->pdev, ha->bars);
	kमुक्त(ha);

	pci_disable_pcie_error_reporting(pdev);

	pci_disable_device(pdev);
पूर्ण

अटल अंतरभूत व्योम
qla24xx_मुक्त_purex_list(काष्ठा purex_list *list)
अणु
	काष्ठा list_head *item, *next;
	uदीर्घ flags;

	spin_lock_irqsave(&list->lock, flags);
	list_क्रम_each_safe(item, next, &list->head) अणु
		list_del(item);
		kमुक्त(list_entry(item, काष्ठा purex_item, list));
	पूर्ण
	spin_unlock_irqrestore(&list->lock, flags);
पूर्ण

अटल व्योम
qla2x00_मुक्त_device(scsi_qla_host_t *vha)
अणु
	काष्ठा qla_hw_data *ha = vha->hw;

	qla2x00_पात_all_cmds(vha, DID_NO_CONNECT << 16);

	/* Disable समयr */
	अगर (vha->समयr_active)
		qla2x00_stop_समयr(vha);

	qla25xx_delete_queues(vha);
	vha->flags.online = 0;

	/* turn-off पूर्णांकerrupts on the card */
	अगर (ha->पूर्णांकerrupts_on) अणु
		vha->flags.init_करोne = 0;
		ha->isp_ops->disable_पूर्णांकrs(ha);
	पूर्ण

	qla2x00_मुक्त_fcports(vha);

	qla2x00_मुक्त_irqs(vha);

	/* Flush the work queue and हटाओ it */
	अगर (ha->wq) अणु
		flush_workqueue(ha->wq);
		destroy_workqueue(ha->wq);
		ha->wq = शून्य;
	पूर्ण


	qla24xx_मुक्त_purex_list(&vha->purex_list);

	qla2x00_mem_मुक्त(ha);

	qla82xx_md_मुक्त(vha);

	qla2x00_मुक्त_queues(ha);
पूर्ण

व्योम qla2x00_मुक्त_fcports(काष्ठा scsi_qla_host *vha)
अणु
	fc_port_t *fcport, *tfcport;

	list_क्रम_each_entry_safe(fcport, tfcport, &vha->vp_fcports, list)
		qla2x00_मुक्त_fcport(fcport);
पूर्ण

अटल अंतरभूत व्योम
qla2x00_schedule_rport_del(काष्ठा scsi_qla_host *vha, fc_port_t *fcport)
अणु
	पूर्णांक now;

	अगर (!fcport->rport)
		वापस;

	अगर (fcport->rport) अणु
		ql_dbg(ql_dbg_disc, fcport->vha, 0x2109,
		    "%s %8phN. rport %p roles %x\n",
		    __func__, fcport->port_name, fcport->rport,
		    fcport->rport->roles);
		fc_remote_port_delete(fcport->rport);
	पूर्ण
	qlt_करो_generation_tick(vha, &now);
पूर्ण

/*
 * qla2x00_mark_device_lost Updates fcport state when device goes offline.
 *
 * Input: ha = adapter block poपूर्णांकer.  fcport = port काष्ठाure poपूर्णांकer.
 *
 * Return: None.
 *
 * Context:
 */
व्योम qla2x00_mark_device_lost(scsi_qla_host_t *vha, fc_port_t *fcport,
    पूर्णांक करो_login)
अणु
	अगर (IS_QLAFX00(vha->hw)) अणु
		qla2x00_set_fcport_state(fcport, FCS_DEVICE_LOST);
		qla2x00_schedule_rport_del(vha, fcport);
		वापस;
	पूर्ण

	अगर (atomic_पढ़ो(&fcport->state) == FCS_ONLINE &&
	    vha->vp_idx == fcport->vha->vp_idx) अणु
		qla2x00_set_fcport_state(fcport, FCS_DEVICE_LOST);
		qla2x00_schedule_rport_del(vha, fcport);
	पूर्ण
	/*
	 * We may need to retry the login, so करोn't change the state of the
	 * port but करो the retries.
	 */
	अगर (atomic_पढ़ो(&fcport->state) != FCS_DEVICE_DEAD)
		qla2x00_set_fcport_state(fcport, FCS_DEVICE_LOST);

	अगर (!करो_login)
		वापस;

	set_bit(RELOGIN_NEEDED, &vha->dpc_flags);
पूर्ण

व्योम
qla2x00_mark_all_devices_lost(scsi_qla_host_t *vha)
अणु
	fc_port_t *fcport;

	ql_dbg(ql_dbg_disc, vha, 0x20f1,
	    "Mark all dev lost\n");

	list_क्रम_each_entry(fcport, &vha->vp_fcports, list) अणु
		fcport->scan_state = 0;
		qlt_schedule_sess_क्रम_deletion(fcport);
	पूर्ण
पूर्ण

अटल व्योम qla2x00_set_reserved_loop_ids(काष्ठा qla_hw_data *ha)
अणु
	पूर्णांक i;

	अगर (IS_FWI2_CAPABLE(ha))
		वापस;

	क्रम (i = 0; i < SNS_FIRST_LOOP_ID; i++)
		set_bit(i, ha->loop_id_map);
	set_bit(MANAGEMENT_SERVER, ha->loop_id_map);
	set_bit(BROADCAST, ha->loop_id_map);
पूर्ण

/*
* qla2x00_mem_alloc
*      Allocates adapter memory.
*
* Returns:
*      0  = success.
*      !0  = failure.
*/
अटल पूर्णांक
qla2x00_mem_alloc(काष्ठा qla_hw_data *ha, uपूर्णांक16_t req_len, uपूर्णांक16_t rsp_len,
	काष्ठा req_que **req, काष्ठा rsp_que **rsp)
अणु
	अक्षर	name[16];

	ha->init_cb = dma_alloc_coherent(&ha->pdev->dev, ha->init_cb_size,
		&ha->init_cb_dma, GFP_KERNEL);
	अगर (!ha->init_cb)
		जाओ fail;

	अगर (qlt_mem_alloc(ha) < 0)
		जाओ fail_मुक्त_init_cb;

	ha->gid_list = dma_alloc_coherent(&ha->pdev->dev,
		qla2x00_gid_list_size(ha), &ha->gid_list_dma, GFP_KERNEL);
	अगर (!ha->gid_list)
		जाओ fail_मुक्त_tgt_mem;

	ha->srb_mempool = mempool_create_slab_pool(SRB_MIN_REQ, srb_cachep);
	अगर (!ha->srb_mempool)
		जाओ fail_मुक्त_gid_list;

	अगर (IS_P3P_TYPE(ha)) अणु
		/* Allocate cache क्रम CT6 Ctx. */
		अगर (!ctx_cachep) अणु
			ctx_cachep = kmem_cache_create("qla2xxx_ctx",
				माप(काष्ठा ct6_dsd), 0,
				SLAB_HWCACHE_ALIGN, शून्य);
			अगर (!ctx_cachep)
				जाओ fail_मुक्त_srb_mempool;
		पूर्ण
		ha->ctx_mempool = mempool_create_slab_pool(SRB_MIN_REQ,
			ctx_cachep);
		अगर (!ha->ctx_mempool)
			जाओ fail_मुक्त_srb_mempool;
		ql_dbg_pci(ql_dbg_init, ha->pdev, 0x0021,
		    "ctx_cachep=%p ctx_mempool=%p.\n",
		    ctx_cachep, ha->ctx_mempool);
	पूर्ण

	/* Get memory क्रम cached NVRAM */
	ha->nvram = kzalloc(MAX_NVRAM_SIZE, GFP_KERNEL);
	अगर (!ha->nvram)
		जाओ fail_मुक्त_ctx_mempool;

	snम_लिखो(name, माप(name), "%s_%d", QLA2XXX_DRIVER_NAME,
		ha->pdev->device);
	ha->s_dma_pool = dma_pool_create(name, &ha->pdev->dev,
		DMA_POOL_SIZE, 8, 0);
	अगर (!ha->s_dma_pool)
		जाओ fail_मुक्त_nvram;

	ql_dbg_pci(ql_dbg_init, ha->pdev, 0x0022,
	    "init_cb=%p gid_list=%p, srb_mempool=%p s_dma_pool=%p.\n",
	    ha->init_cb, ha->gid_list, ha->srb_mempool, ha->s_dma_pool);

	अगर (IS_P3P_TYPE(ha) || ql2xenabledअगर) अणु
		ha->dl_dma_pool = dma_pool_create(name, &ha->pdev->dev,
			DSD_LIST_DMA_POOL_SIZE, 8, 0);
		अगर (!ha->dl_dma_pool) अणु
			ql_log_pci(ql_log_fatal, ha->pdev, 0x0023,
			    "Failed to allocate memory for dl_dma_pool.\n");
			जाओ fail_s_dma_pool;
		पूर्ण

		ha->fcp_cmnd_dma_pool = dma_pool_create(name, &ha->pdev->dev,
			FCP_CMND_DMA_POOL_SIZE, 8, 0);
		अगर (!ha->fcp_cmnd_dma_pool) अणु
			ql_log_pci(ql_log_fatal, ha->pdev, 0x0024,
			    "Failed to allocate memory for fcp_cmnd_dma_pool.\n");
			जाओ fail_dl_dma_pool;
		पूर्ण

		अगर (ql2xenabledअगर) अणु
			u64 bufsize = DIF_BUNDLING_DMA_POOL_SIZE;
			काष्ठा dsd_dma *dsd, *nxt;
			uपूर्णांक i;
			/* Creata a DMA pool of buffers क्रम DIF bundling */
			ha->dअगर_bundl_pool = dma_pool_create(name,
			    &ha->pdev->dev, DIF_BUNDLING_DMA_POOL_SIZE, 8, 0);
			अगर (!ha->dअगर_bundl_pool) अणु
				ql_dbg_pci(ql_dbg_init, ha->pdev, 0x0024,
				    "%s: failed create dif_bundl_pool\n",
				    __func__);
				जाओ fail_dअगर_bundl_dma_pool;
			पूर्ण

			INIT_LIST_HEAD(&ha->pool.good.head);
			INIT_LIST_HEAD(&ha->pool.unusable.head);
			ha->pool.good.count = 0;
			ha->pool.unusable.count = 0;
			क्रम (i = 0; i < 128; i++) अणु
				dsd = kzalloc(माप(*dsd), GFP_ATOMIC);
				अगर (!dsd) अणु
					ql_dbg_pci(ql_dbg_init, ha->pdev,
					    0xe0ee, "%s: failed alloc dsd\n",
					    __func__);
					वापस 1;
				पूर्ण
				ha->dअगर_bundle_kallocs++;

				dsd->dsd_addr = dma_pool_alloc(
				    ha->dअगर_bundl_pool, GFP_ATOMIC,
				    &dsd->dsd_list_dma);
				अगर (!dsd->dsd_addr) अणु
					ql_dbg_pci(ql_dbg_init, ha->pdev,
					    0xe0ee,
					    "%s: failed alloc ->dsd_addr\n",
					    __func__);
					kमुक्त(dsd);
					ha->dअगर_bundle_kallocs--;
					जारी;
				पूर्ण
				ha->dअगर_bundle_dma_allocs++;

				/*
				 * अगर DMA buffer crosses 4G boundary,
				 * put it on bad list
				 */
				अगर (MSD(dsd->dsd_list_dma) ^
				    MSD(dsd->dsd_list_dma + bufsize)) अणु
					list_add_tail(&dsd->list,
					    &ha->pool.unusable.head);
					ha->pool.unusable.count++;
				पूर्ण अन्यथा अणु
					list_add_tail(&dsd->list,
					    &ha->pool.good.head);
					ha->pool.good.count++;
				पूर्ण
			पूर्ण

			/* वापस the good ones back to the pool */
			list_क्रम_each_entry_safe(dsd, nxt,
			    &ha->pool.good.head, list) अणु
				list_del(&dsd->list);
				dma_pool_मुक्त(ha->dअगर_bundl_pool,
				    dsd->dsd_addr, dsd->dsd_list_dma);
				ha->dअगर_bundle_dma_allocs--;
				kमुक्त(dsd);
				ha->dअगर_bundle_kallocs--;
			पूर्ण

			ql_dbg_pci(ql_dbg_init, ha->pdev, 0x0024,
			    "%s: dif dma pool (good=%u unusable=%u)\n",
			    __func__, ha->pool.good.count,
			    ha->pool.unusable.count);
		पूर्ण

		ql_dbg_pci(ql_dbg_init, ha->pdev, 0x0025,
		    "dl_dma_pool=%p fcp_cmnd_dma_pool=%p dif_bundl_pool=%p.\n",
		    ha->dl_dma_pool, ha->fcp_cmnd_dma_pool,
		    ha->dअगर_bundl_pool);
	पूर्ण

	/* Allocate memory क्रम SNS commands */
	अगर (IS_QLA2100(ha) || IS_QLA2200(ha)) अणु
	/* Get consistent memory allocated क्रम SNS commands */
		ha->sns_cmd = dma_alloc_coherent(&ha->pdev->dev,
		माप(काष्ठा sns_cmd_pkt), &ha->sns_cmd_dma, GFP_KERNEL);
		अगर (!ha->sns_cmd)
			जाओ fail_dma_pool;
		ql_dbg_pci(ql_dbg_init, ha->pdev, 0x0026,
		    "sns_cmd: %p.\n", ha->sns_cmd);
	पूर्ण अन्यथा अणु
	/* Get consistent memory allocated क्रम MS IOCB */
		ha->ms_iocb = dma_pool_alloc(ha->s_dma_pool, GFP_KERNEL,
			&ha->ms_iocb_dma);
		अगर (!ha->ms_iocb)
			जाओ fail_dma_pool;
	/* Get consistent memory allocated क्रम CT SNS commands */
		ha->ct_sns = dma_alloc_coherent(&ha->pdev->dev,
			माप(काष्ठा ct_sns_pkt), &ha->ct_sns_dma, GFP_KERNEL);
		अगर (!ha->ct_sns)
			जाओ fail_मुक्त_ms_iocb;
		ql_dbg_pci(ql_dbg_init, ha->pdev, 0x0027,
		    "ms_iocb=%p ct_sns=%p.\n",
		    ha->ms_iocb, ha->ct_sns);
	पूर्ण

	/* Allocate memory क्रम request ring */
	*req = kzalloc(माप(काष्ठा req_que), GFP_KERNEL);
	अगर (!*req) अणु
		ql_log_pci(ql_log_fatal, ha->pdev, 0x0028,
		    "Failed to allocate memory for req.\n");
		जाओ fail_req;
	पूर्ण
	(*req)->length = req_len;
	(*req)->ring = dma_alloc_coherent(&ha->pdev->dev,
		((*req)->length + 1) * माप(request_t),
		&(*req)->dma, GFP_KERNEL);
	अगर (!(*req)->ring) अणु
		ql_log_pci(ql_log_fatal, ha->pdev, 0x0029,
		    "Failed to allocate memory for req_ring.\n");
		जाओ fail_req_ring;
	पूर्ण
	/* Allocate memory क्रम response ring */
	*rsp = kzalloc(माप(काष्ठा rsp_que), GFP_KERNEL);
	अगर (!*rsp) अणु
		ql_log_pci(ql_log_fatal, ha->pdev, 0x002a,
		    "Failed to allocate memory for rsp.\n");
		जाओ fail_rsp;
	पूर्ण
	(*rsp)->hw = ha;
	(*rsp)->length = rsp_len;
	(*rsp)->ring = dma_alloc_coherent(&ha->pdev->dev,
		((*rsp)->length + 1) * माप(response_t),
		&(*rsp)->dma, GFP_KERNEL);
	अगर (!(*rsp)->ring) अणु
		ql_log_pci(ql_log_fatal, ha->pdev, 0x002b,
		    "Failed to allocate memory for rsp_ring.\n");
		जाओ fail_rsp_ring;
	पूर्ण
	(*req)->rsp = *rsp;
	(*rsp)->req = *req;
	ql_dbg_pci(ql_dbg_init, ha->pdev, 0x002c,
	    "req=%p req->length=%d req->ring=%p rsp=%p "
	    "rsp->length=%d rsp->ring=%p.\n",
	    *req, (*req)->length, (*req)->ring, *rsp, (*rsp)->length,
	    (*rsp)->ring);
	/* Allocate memory क्रम NVRAM data क्रम vports */
	अगर (ha->nvram_npiv_size) अणु
		ha->npiv_info = kसुस्मृति(ha->nvram_npiv_size,
					माप(काष्ठा qla_npiv_entry),
					GFP_KERNEL);
		अगर (!ha->npiv_info) अणु
			ql_log_pci(ql_log_fatal, ha->pdev, 0x002d,
			    "Failed to allocate memory for npiv_info.\n");
			जाओ fail_npiv_info;
		पूर्ण
	पूर्ण अन्यथा
		ha->npiv_info = शून्य;

	/* Get consistent memory allocated क्रम EX-INIT-CB. */
	अगर (IS_CNA_CAPABLE(ha) || IS_QLA2031(ha) || IS_QLA27XX(ha) ||
	    IS_QLA28XX(ha)) अणु
		ha->ex_init_cb = dma_pool_alloc(ha->s_dma_pool, GFP_KERNEL,
		    &ha->ex_init_cb_dma);
		अगर (!ha->ex_init_cb)
			जाओ fail_ex_init_cb;
		ql_dbg_pci(ql_dbg_init, ha->pdev, 0x002e,
		    "ex_init_cb=%p.\n", ha->ex_init_cb);
	पूर्ण

	/* Get consistent memory allocated क्रम Special Features-CB. */
	अगर (IS_QLA27XX(ha) || IS_QLA28XX(ha)) अणु
		ha->sf_init_cb = dma_pool_zalloc(ha->s_dma_pool, GFP_KERNEL,
						&ha->sf_init_cb_dma);
		अगर (!ha->sf_init_cb)
			जाओ fail_sf_init_cb;
		ql_dbg_pci(ql_dbg_init, ha->pdev, 0x0199,
			   "sf_init_cb=%p.\n", ha->sf_init_cb);
	पूर्ण

	INIT_LIST_HEAD(&ha->gbl_dsd_list);

	/* Get consistent memory allocated क्रम Async Port-Database. */
	अगर (!IS_FWI2_CAPABLE(ha)) अणु
		ha->async_pd = dma_pool_alloc(ha->s_dma_pool, GFP_KERNEL,
			&ha->async_pd_dma);
		अगर (!ha->async_pd)
			जाओ fail_async_pd;
		ql_dbg_pci(ql_dbg_init, ha->pdev, 0x002f,
		    "async_pd=%p.\n", ha->async_pd);
	पूर्ण

	INIT_LIST_HEAD(&ha->vp_list);

	/* Allocate memory क्रम our loop_id biपंचांगap */
	ha->loop_id_map = kसुस्मृति(BITS_TO_LONGS(LOOPID_MAP_SIZE),
				  माप(दीर्घ),
				  GFP_KERNEL);
	अगर (!ha->loop_id_map)
		जाओ fail_loop_id_map;
	अन्यथा अणु
		qla2x00_set_reserved_loop_ids(ha);
		ql_dbg_pci(ql_dbg_init, ha->pdev, 0x0123,
		    "loop_id_map=%p.\n", ha->loop_id_map);
	पूर्ण

	ha->sfp_data = dma_alloc_coherent(&ha->pdev->dev,
	    SFP_DEV_SIZE, &ha->sfp_data_dma, GFP_KERNEL);
	अगर (!ha->sfp_data) अणु
		ql_dbg_pci(ql_dbg_init, ha->pdev, 0x011b,
		    "Unable to allocate memory for SFP read-data.\n");
		जाओ fail_sfp_data;
	पूर्ण

	ha->flt = dma_alloc_coherent(&ha->pdev->dev,
	    माप(काष्ठा qla_flt_header) + FLT_REGIONS_SIZE, &ha->flt_dma,
	    GFP_KERNEL);
	अगर (!ha->flt) अणु
		ql_dbg_pci(ql_dbg_init, ha->pdev, 0x011b,
		    "Unable to allocate memory for FLT.\n");
		जाओ fail_flt_buffer;
	पूर्ण

	वापस 0;

fail_flt_buffer:
	dma_मुक्त_coherent(&ha->pdev->dev, SFP_DEV_SIZE,
	    ha->sfp_data, ha->sfp_data_dma);
fail_sfp_data:
	kमुक्त(ha->loop_id_map);
fail_loop_id_map:
	dma_pool_मुक्त(ha->s_dma_pool, ha->async_pd, ha->async_pd_dma);
fail_async_pd:
	dma_pool_मुक्त(ha->s_dma_pool, ha->sf_init_cb, ha->sf_init_cb_dma);
fail_sf_init_cb:
	dma_pool_मुक्त(ha->s_dma_pool, ha->ex_init_cb, ha->ex_init_cb_dma);
fail_ex_init_cb:
	kमुक्त(ha->npiv_info);
fail_npiv_info:
	dma_मुक्त_coherent(&ha->pdev->dev, ((*rsp)->length + 1) *
		माप(response_t), (*rsp)->ring, (*rsp)->dma);
	(*rsp)->ring = शून्य;
	(*rsp)->dma = 0;
fail_rsp_ring:
	kमुक्त(*rsp);
	*rsp = शून्य;
fail_rsp:
	dma_मुक्त_coherent(&ha->pdev->dev, ((*req)->length + 1) *
		माप(request_t), (*req)->ring, (*req)->dma);
	(*req)->ring = शून्य;
	(*req)->dma = 0;
fail_req_ring:
	kमुक्त(*req);
	*req = शून्य;
fail_req:
	dma_मुक्त_coherent(&ha->pdev->dev, माप(काष्ठा ct_sns_pkt),
		ha->ct_sns, ha->ct_sns_dma);
	ha->ct_sns = शून्य;
	ha->ct_sns_dma = 0;
fail_मुक्त_ms_iocb:
	dma_pool_मुक्त(ha->s_dma_pool, ha->ms_iocb, ha->ms_iocb_dma);
	ha->ms_iocb = शून्य;
	ha->ms_iocb_dma = 0;

	अगर (ha->sns_cmd)
		dma_मुक्त_coherent(&ha->pdev->dev, माप(काष्ठा sns_cmd_pkt),
		    ha->sns_cmd, ha->sns_cmd_dma);
fail_dma_pool:
	अगर (ql2xenabledअगर) अणु
		काष्ठा dsd_dma *dsd, *nxt;

		list_क्रम_each_entry_safe(dsd, nxt, &ha->pool.unusable.head,
		    list) अणु
			list_del(&dsd->list);
			dma_pool_मुक्त(ha->dअगर_bundl_pool, dsd->dsd_addr,
			    dsd->dsd_list_dma);
			ha->dअगर_bundle_dma_allocs--;
			kमुक्त(dsd);
			ha->dअगर_bundle_kallocs--;
			ha->pool.unusable.count--;
		पूर्ण
		dma_pool_destroy(ha->dअगर_bundl_pool);
		ha->dअगर_bundl_pool = शून्य;
	पूर्ण

fail_dअगर_bundl_dma_pool:
	अगर (IS_QLA82XX(ha) || ql2xenabledअगर) अणु
		dma_pool_destroy(ha->fcp_cmnd_dma_pool);
		ha->fcp_cmnd_dma_pool = शून्य;
	पूर्ण
fail_dl_dma_pool:
	अगर (IS_QLA82XX(ha) || ql2xenabledअगर) अणु
		dma_pool_destroy(ha->dl_dma_pool);
		ha->dl_dma_pool = शून्य;
	पूर्ण
fail_s_dma_pool:
	dma_pool_destroy(ha->s_dma_pool);
	ha->s_dma_pool = शून्य;
fail_मुक्त_nvram:
	kमुक्त(ha->nvram);
	ha->nvram = शून्य;
fail_मुक्त_ctx_mempool:
	mempool_destroy(ha->ctx_mempool);
	ha->ctx_mempool = शून्य;
fail_मुक्त_srb_mempool:
	mempool_destroy(ha->srb_mempool);
	ha->srb_mempool = शून्य;
fail_मुक्त_gid_list:
	dma_मुक्त_coherent(&ha->pdev->dev, qla2x00_gid_list_size(ha),
	ha->gid_list,
	ha->gid_list_dma);
	ha->gid_list = शून्य;
	ha->gid_list_dma = 0;
fail_मुक्त_tgt_mem:
	qlt_mem_मुक्त(ha);
fail_मुक्त_init_cb:
	dma_मुक्त_coherent(&ha->pdev->dev, ha->init_cb_size, ha->init_cb,
	ha->init_cb_dma);
	ha->init_cb = शून्य;
	ha->init_cb_dma = 0;
fail:
	ql_log(ql_log_fatal, शून्य, 0x0030,
	    "Memory allocation failure.\n");
	वापस -ENOMEM;
पूर्ण

पूर्णांक
qla2x00_set_exlogins_buffer(scsi_qla_host_t *vha)
अणु
	पूर्णांक rval;
	uपूर्णांक16_t	size, max_cnt;
	uपूर्णांक32_t temp;
	काष्ठा qla_hw_data *ha = vha->hw;

	/* Return अगर we करोn't need to alloacate any extended logins */
	अगर (ql2xexlogins <= MAX_FIBRE_DEVICES_2400)
		वापस QLA_SUCCESS;

	अगर (!IS_EXLOGIN_OFFLD_CAPABLE(ha))
		वापस QLA_SUCCESS;

	ql_log(ql_log_info, vha, 0xd021, "EXLOGIN count: %d.\n", ql2xexlogins);
	max_cnt = 0;
	rval = qla_get_exlogin_status(vha, &size, &max_cnt);
	अगर (rval != QLA_SUCCESS) अणु
		ql_log_pci(ql_log_fatal, ha->pdev, 0xd029,
		    "Failed to get exlogin status.\n");
		वापस rval;
	पूर्ण

	temp = (ql2xexlogins > max_cnt) ? max_cnt : ql2xexlogins;
	temp *= size;

	अगर (temp != ha->exlogin_size) अणु
		qla2x00_मुक्त_exlogin_buffer(ha);
		ha->exlogin_size = temp;

		ql_log(ql_log_info, vha, 0xd024,
		    "EXLOGIN: max_logins=%d, portdb=0x%x, total=%d.\n",
		    max_cnt, size, temp);

		ql_log(ql_log_info, vha, 0xd025,
		    "EXLOGIN: requested size=0x%x\n", ha->exlogin_size);

		/* Get consistent memory क्रम extended logins */
		ha->exlogin_buf = dma_alloc_coherent(&ha->pdev->dev,
			ha->exlogin_size, &ha->exlogin_buf_dma, GFP_KERNEL);
		अगर (!ha->exlogin_buf) अणु
			ql_log_pci(ql_log_fatal, ha->pdev, 0xd02a,
		    "Failed to allocate memory for exlogin_buf_dma.\n");
			वापस -ENOMEM;
		पूर्ण
	पूर्ण

	/* Now configure the dma buffer */
	rval = qla_set_exlogin_mem_cfg(vha, ha->exlogin_buf_dma);
	अगर (rval) अणु
		ql_log(ql_log_fatal, vha, 0xd033,
		    "Setup extended login buffer  ****FAILED****.\n");
		qla2x00_मुक्त_exlogin_buffer(ha);
	पूर्ण

	वापस rval;
पूर्ण

/*
* qla2x00_मुक्त_exlogin_buffer
*
* Input:
*	ha = adapter block poपूर्णांकer
*/
व्योम
qla2x00_मुक्त_exlogin_buffer(काष्ठा qla_hw_data *ha)
अणु
	अगर (ha->exlogin_buf) अणु
		dma_मुक्त_coherent(&ha->pdev->dev, ha->exlogin_size,
		    ha->exlogin_buf, ha->exlogin_buf_dma);
		ha->exlogin_buf = शून्य;
		ha->exlogin_size = 0;
	पूर्ण
पूर्ण

अटल व्योम
qla2x00_number_of_exch(scsi_qla_host_t *vha, u32 *ret_cnt, u16 max_cnt)
अणु
	u32 temp;
	काष्ठा init_cb_81xx *icb = (काष्ठा init_cb_81xx *)&vha->hw->init_cb;
	*ret_cnt = FW_DEF_EXCHANGES_CNT;

	अगर (max_cnt > vha->hw->max_exchg)
		max_cnt = vha->hw->max_exchg;

	अगर (qla_ini_mode_enabled(vha)) अणु
		अगर (vha->ql2xiniexchg > max_cnt)
			vha->ql2xiniexchg = max_cnt;

		अगर (vha->ql2xiniexchg > FW_DEF_EXCHANGES_CNT)
			*ret_cnt = vha->ql2xiniexchg;

	पूर्ण अन्यथा अगर (qla_tgt_mode_enabled(vha)) अणु
		अगर (vha->ql2xexchoffld > max_cnt) अणु
			vha->ql2xexchoffld = max_cnt;
			icb->exchange_count = cpu_to_le16(vha->ql2xexchoffld);
		पूर्ण

		अगर (vha->ql2xexchoffld > FW_DEF_EXCHANGES_CNT)
			*ret_cnt = vha->ql2xexchoffld;
	पूर्ण अन्यथा अगर (qla_dual_mode_enabled(vha)) अणु
		temp = vha->ql2xiniexchg + vha->ql2xexchoffld;
		अगर (temp > max_cnt) अणु
			vha->ql2xiniexchg -= (temp - max_cnt)/2;
			vha->ql2xexchoffld -= (((temp - max_cnt)/2) + 1);
			temp = max_cnt;
			icb->exchange_count = cpu_to_le16(vha->ql2xexchoffld);
		पूर्ण

		अगर (temp > FW_DEF_EXCHANGES_CNT)
			*ret_cnt = temp;
	पूर्ण
पूर्ण

पूर्णांक
qla2x00_set_exchoffld_buffer(scsi_qla_host_t *vha)
अणु
	पूर्णांक rval;
	u16	size, max_cnt;
	u32 actual_cnt, totsz;
	काष्ठा qla_hw_data *ha = vha->hw;

	अगर (!ha->flags.exchoffld_enabled)
		वापस QLA_SUCCESS;

	अगर (!IS_EXCHG_OFFLD_CAPABLE(ha))
		वापस QLA_SUCCESS;

	max_cnt = 0;
	rval = qla_get_exchoffld_status(vha, &size, &max_cnt);
	अगर (rval != QLA_SUCCESS) अणु
		ql_log_pci(ql_log_fatal, ha->pdev, 0xd012,
		    "Failed to get exlogin status.\n");
		वापस rval;
	पूर्ण

	qla2x00_number_of_exch(vha, &actual_cnt, max_cnt);
	ql_log(ql_log_info, vha, 0xd014,
	    "Actual exchange offload count: %d.\n", actual_cnt);

	totsz = actual_cnt * size;

	अगर (totsz != ha->exchoffld_size) अणु
		qla2x00_मुक्त_exchoffld_buffer(ha);
		अगर (actual_cnt <= FW_DEF_EXCHANGES_CNT) अणु
			ha->exchoffld_size = 0;
			ha->flags.exchoffld_enabled = 0;
			वापस QLA_SUCCESS;
		पूर्ण

		ha->exchoffld_size = totsz;

		ql_log(ql_log_info, vha, 0xd016,
		    "Exchange offload: max_count=%d, actual count=%d entry sz=0x%x, total sz=0x%x\n",
		    max_cnt, actual_cnt, size, totsz);

		ql_log(ql_log_info, vha, 0xd017,
		    "Exchange Buffers requested size = 0x%x\n",
		    ha->exchoffld_size);

		/* Get consistent memory क्रम extended logins */
		ha->exchoffld_buf = dma_alloc_coherent(&ha->pdev->dev,
			ha->exchoffld_size, &ha->exchoffld_buf_dma, GFP_KERNEL);
		अगर (!ha->exchoffld_buf) अणु
			ql_log_pci(ql_log_fatal, ha->pdev, 0xd013,
			"Failed to allocate memory for Exchange Offload.\n");

			अगर (ha->max_exchg >
			    (FW_DEF_EXCHANGES_CNT + REDUCE_EXCHANGES_CNT)) अणु
				ha->max_exchg -= REDUCE_EXCHANGES_CNT;
			पूर्ण अन्यथा अगर (ha->max_exchg >
			    (FW_DEF_EXCHANGES_CNT + 512)) अणु
				ha->max_exchg -= 512;
			पूर्ण अन्यथा अणु
				ha->flags.exchoffld_enabled = 0;
				ql_log_pci(ql_log_fatal, ha->pdev, 0xd013,
				    "Disabling Exchange offload due to lack of memory\n");
			पूर्ण
			ha->exchoffld_size = 0;

			वापस -ENOMEM;
		पूर्ण
	पूर्ण अन्यथा अगर (!ha->exchoffld_buf || (actual_cnt <= FW_DEF_EXCHANGES_CNT)) अणु
		/* pathological हाल */
		qla2x00_मुक्त_exchoffld_buffer(ha);
		ha->exchoffld_size = 0;
		ha->flags.exchoffld_enabled = 0;
		ql_log(ql_log_info, vha, 0xd016,
		    "Exchange offload not enable: offld size=%d, actual count=%d entry sz=0x%x, total sz=0x%x.\n",
		    ha->exchoffld_size, actual_cnt, size, totsz);
		वापस 0;
	पूर्ण

	/* Now configure the dma buffer */
	rval = qla_set_exchoffld_mem_cfg(vha);
	अगर (rval) अणु
		ql_log(ql_log_fatal, vha, 0xd02e,
		    "Setup exchange offload buffer ****FAILED****.\n");
		qla2x00_मुक्त_exchoffld_buffer(ha);
	पूर्ण अन्यथा अणु
		/* re-adjust number of target exchange */
		काष्ठा init_cb_81xx *icb = (काष्ठा init_cb_81xx *)ha->init_cb;

		अगर (qla_ini_mode_enabled(vha))
			icb->exchange_count = 0;
		अन्यथा
			icb->exchange_count = cpu_to_le16(vha->ql2xexchoffld);
	पूर्ण

	वापस rval;
पूर्ण

/*
* qla2x00_मुक्त_exchoffld_buffer
*
* Input:
*	ha = adapter block poपूर्णांकer
*/
व्योम
qla2x00_मुक्त_exchoffld_buffer(काष्ठा qla_hw_data *ha)
अणु
	अगर (ha->exchoffld_buf) अणु
		dma_मुक्त_coherent(&ha->pdev->dev, ha->exchoffld_size,
		    ha->exchoffld_buf, ha->exchoffld_buf_dma);
		ha->exchoffld_buf = शून्य;
		ha->exchoffld_size = 0;
	पूर्ण
पूर्ण

/*
* qla2x00_मुक्त_fw_dump
*	Frees fw dump stuff.
*
* Input:
*	ha = adapter block poपूर्णांकer
*/
अटल व्योम
qla2x00_मुक्त_fw_dump(काष्ठा qla_hw_data *ha)
अणु
	काष्ठा fwdt *fwdt = ha->fwdt;
	uपूर्णांक j;

	अगर (ha->fce)
		dma_मुक्त_coherent(&ha->pdev->dev,
		    FCE_SIZE, ha->fce, ha->fce_dma);

	अगर (ha->eft)
		dma_मुक्त_coherent(&ha->pdev->dev,
		    EFT_SIZE, ha->eft, ha->eft_dma);

	vमुक्त(ha->fw_dump);

	ha->fce = शून्य;
	ha->fce_dma = 0;
	ha->flags.fce_enabled = 0;
	ha->eft = शून्य;
	ha->eft_dma = 0;
	ha->fw_dumped = false;
	ha->fw_dump_cap_flags = 0;
	ha->fw_dump_पढ़ोing = 0;
	ha->fw_dump = शून्य;
	ha->fw_dump_len = 0;

	क्रम (j = 0; j < 2; j++, fwdt++) अणु
		vमुक्त(fwdt->ढाँचा);
		fwdt->ढाँचा = शून्य;
		fwdt->length = 0;
	पूर्ण
पूर्ण

/*
* qla2x00_mem_मुक्त
*      Frees all adapter allocated memory.
*
* Input:
*      ha = adapter block poपूर्णांकer.
*/
अटल व्योम
qla2x00_mem_मुक्त(काष्ठा qla_hw_data *ha)
अणु
	qla2x00_मुक्त_fw_dump(ha);

	अगर (ha->mctp_dump)
		dma_मुक्त_coherent(&ha->pdev->dev, MCTP_DUMP_SIZE, ha->mctp_dump,
		    ha->mctp_dump_dma);
	ha->mctp_dump = शून्य;

	mempool_destroy(ha->srb_mempool);
	ha->srb_mempool = शून्य;

	अगर (ha->dcbx_tlv)
		dma_मुक्त_coherent(&ha->pdev->dev, DCBX_TLV_DATA_SIZE,
		    ha->dcbx_tlv, ha->dcbx_tlv_dma);
	ha->dcbx_tlv = शून्य;

	अगर (ha->xgmac_data)
		dma_मुक्त_coherent(&ha->pdev->dev, XGMAC_DATA_SIZE,
		    ha->xgmac_data, ha->xgmac_data_dma);
	ha->xgmac_data = शून्य;

	अगर (ha->sns_cmd)
		dma_मुक्त_coherent(&ha->pdev->dev, माप(काष्ठा sns_cmd_pkt),
		ha->sns_cmd, ha->sns_cmd_dma);
	ha->sns_cmd = शून्य;
	ha->sns_cmd_dma = 0;

	अगर (ha->ct_sns)
		dma_मुक्त_coherent(&ha->pdev->dev, माप(काष्ठा ct_sns_pkt),
		ha->ct_sns, ha->ct_sns_dma);
	ha->ct_sns = शून्य;
	ha->ct_sns_dma = 0;

	अगर (ha->sfp_data)
		dma_मुक्त_coherent(&ha->pdev->dev, SFP_DEV_SIZE, ha->sfp_data,
		    ha->sfp_data_dma);
	ha->sfp_data = शून्य;

	अगर (ha->flt)
		dma_मुक्त_coherent(&ha->pdev->dev,
		    माप(काष्ठा qla_flt_header) + FLT_REGIONS_SIZE,
		    ha->flt, ha->flt_dma);
	ha->flt = शून्य;
	ha->flt_dma = 0;

	अगर (ha->ms_iocb)
		dma_pool_मुक्त(ha->s_dma_pool, ha->ms_iocb, ha->ms_iocb_dma);
	ha->ms_iocb = शून्य;
	ha->ms_iocb_dma = 0;

	अगर (ha->sf_init_cb)
		dma_pool_मुक्त(ha->s_dma_pool,
			      ha->sf_init_cb, ha->sf_init_cb_dma);

	अगर (ha->ex_init_cb)
		dma_pool_मुक्त(ha->s_dma_pool,
			ha->ex_init_cb, ha->ex_init_cb_dma);
	ha->ex_init_cb = शून्य;
	ha->ex_init_cb_dma = 0;

	अगर (ha->async_pd)
		dma_pool_मुक्त(ha->s_dma_pool, ha->async_pd, ha->async_pd_dma);
	ha->async_pd = शून्य;
	ha->async_pd_dma = 0;

	dma_pool_destroy(ha->s_dma_pool);
	ha->s_dma_pool = शून्य;

	अगर (ha->gid_list)
		dma_मुक्त_coherent(&ha->pdev->dev, qla2x00_gid_list_size(ha),
		ha->gid_list, ha->gid_list_dma);
	ha->gid_list = शून्य;
	ha->gid_list_dma = 0;

	अगर (IS_QLA82XX(ha)) अणु
		अगर (!list_empty(&ha->gbl_dsd_list)) अणु
			काष्ठा dsd_dma *dsd_ptr, *tdsd_ptr;

			/* clean up allocated prev pool */
			list_क्रम_each_entry_safe(dsd_ptr,
				tdsd_ptr, &ha->gbl_dsd_list, list) अणु
				dma_pool_मुक्त(ha->dl_dma_pool,
				dsd_ptr->dsd_addr, dsd_ptr->dsd_list_dma);
				list_del(&dsd_ptr->list);
				kमुक्त(dsd_ptr);
			पूर्ण
		पूर्ण
	पूर्ण

	dma_pool_destroy(ha->dl_dma_pool);
	ha->dl_dma_pool = शून्य;

	dma_pool_destroy(ha->fcp_cmnd_dma_pool);
	ha->fcp_cmnd_dma_pool = शून्य;

	mempool_destroy(ha->ctx_mempool);
	ha->ctx_mempool = शून्य;

	अगर (ql2xenabledअगर && ha->dअगर_bundl_pool) अणु
		काष्ठा dsd_dma *dsd, *nxt;

		list_क्रम_each_entry_safe(dsd, nxt, &ha->pool.unusable.head,
					 list) अणु
			list_del(&dsd->list);
			dma_pool_मुक्त(ha->dअगर_bundl_pool, dsd->dsd_addr,
				      dsd->dsd_list_dma);
			ha->dअगर_bundle_dma_allocs--;
			kमुक्त(dsd);
			ha->dअगर_bundle_kallocs--;
			ha->pool.unusable.count--;
		पूर्ण
		list_क्रम_each_entry_safe(dsd, nxt, &ha->pool.good.head, list) अणु
			list_del(&dsd->list);
			dma_pool_मुक्त(ha->dअगर_bundl_pool, dsd->dsd_addr,
				      dsd->dsd_list_dma);
			ha->dअगर_bundle_dma_allocs--;
			kमुक्त(dsd);
			ha->dअगर_bundle_kallocs--;
		पूर्ण
	पूर्ण

	dma_pool_destroy(ha->dअगर_bundl_pool);
	ha->dअगर_bundl_pool = शून्य;

	qlt_mem_मुक्त(ha);

	अगर (ha->init_cb)
		dma_मुक्त_coherent(&ha->pdev->dev, ha->init_cb_size,
			ha->init_cb, ha->init_cb_dma);
	ha->init_cb = शून्य;
	ha->init_cb_dma = 0;

	vमुक्त(ha->optrom_buffer);
	ha->optrom_buffer = शून्य;
	kमुक्त(ha->nvram);
	ha->nvram = शून्य;
	kमुक्त(ha->npiv_info);
	ha->npiv_info = शून्य;
	kमुक्त(ha->swl);
	ha->swl = शून्य;
	kमुक्त(ha->loop_id_map);
	ha->sf_init_cb = शून्य;
	ha->sf_init_cb_dma = 0;
	ha->loop_id_map = शून्य;
पूर्ण

काष्ठा scsi_qla_host *qla2x00_create_host(काष्ठा scsi_host_ढाँचा *sht,
						काष्ठा qla_hw_data *ha)
अणु
	काष्ठा Scsi_Host *host;
	काष्ठा scsi_qla_host *vha = शून्य;

	host = scsi_host_alloc(sht, माप(scsi_qla_host_t));
	अगर (!host) अणु
		ql_log_pci(ql_log_fatal, ha->pdev, 0x0107,
		    "Failed to allocate host from the scsi layer, aborting.\n");
		वापस शून्य;
	पूर्ण

	/* Clear our data area */
	vha = shost_priv(host);
	स_रखो(vha, 0, माप(scsi_qla_host_t));

	vha->host = host;
	vha->host_no = host->host_no;
	vha->hw = ha;

	vha->qlini_mode = ql2x_ini_mode;
	vha->ql2xexchoffld = ql2xexchoffld;
	vha->ql2xiniexchg = ql2xiniexchg;

	INIT_LIST_HEAD(&vha->vp_fcports);
	INIT_LIST_HEAD(&vha->work_list);
	INIT_LIST_HEAD(&vha->list);
	INIT_LIST_HEAD(&vha->qla_cmd_list);
	INIT_LIST_HEAD(&vha->qla_sess_op_cmd_list);
	INIT_LIST_HEAD(&vha->logo_list);
	INIT_LIST_HEAD(&vha->plogi_ack_list);
	INIT_LIST_HEAD(&vha->qp_list);
	INIT_LIST_HEAD(&vha->gnl.fcports);
	INIT_LIST_HEAD(&vha->gpnid_list);
	INIT_WORK(&vha->iocb_work, qla2x00_iocb_work_fn);

	INIT_LIST_HEAD(&vha->purex_list.head);
	spin_lock_init(&vha->purex_list.lock);

	spin_lock_init(&vha->work_lock);
	spin_lock_init(&vha->cmd_list_lock);
	init_रुकोqueue_head(&vha->fcport_रुकोQ);
	init_रुकोqueue_head(&vha->vref_रुकोq);

	vha->gnl.size = माप(काष्ठा get_name_list_extended) *
			(ha->max_loop_id + 1);
	vha->gnl.l = dma_alloc_coherent(&ha->pdev->dev,
	    vha->gnl.size, &vha->gnl.ldma, GFP_KERNEL);
	अगर (!vha->gnl.l) अणु
		ql_log(ql_log_fatal, vha, 0xd04a,
		    "Alloc failed for name list.\n");
		scsi_host_put(vha->host);
		वापस शून्य;
	पूर्ण

	/* toकरो: what about ext login? */
	vha->scan.size = ha->max_fibre_devices * माप(काष्ठा fab_scan_rp);
	vha->scan.l = vदो_स्मृति(vha->scan.size);
	अगर (!vha->scan.l) अणु
		ql_log(ql_log_fatal, vha, 0xd04a,
		    "Alloc failed for scan database.\n");
		dma_मुक्त_coherent(&ha->pdev->dev, vha->gnl.size,
		    vha->gnl.l, vha->gnl.ldma);
		vha->gnl.l = शून्य;
		scsi_host_put(vha->host);
		वापस शून्य;
	पूर्ण
	INIT_DELAYED_WORK(&vha->scan.scan_work, qla_scan_work_fn);

	प्र_लिखो(vha->host_str, "%s_%lu", QLA2XXX_DRIVER_NAME, vha->host_no);
	ql_dbg(ql_dbg_init, vha, 0x0041,
	    "Allocated the host=%p hw=%p vha=%p dev_name=%s",
	    vha->host, vha->hw, vha,
	    dev_name(&(ha->pdev->dev)));

	वापस vha;
पूर्ण

काष्ठा qla_work_evt *
qla2x00_alloc_work(काष्ठा scsi_qla_host *vha, क्रमागत qla_work_type type)
अणु
	काष्ठा qla_work_evt *e;
	uपूर्णांक8_t bail;

	अगर (test_bit(UNLOADING, &vha->dpc_flags))
		वापस शून्य;

	QLA_VHA_MARK_BUSY(vha, bail);
	अगर (bail)
		वापस शून्य;

	e = kzalloc(माप(काष्ठा qla_work_evt), GFP_ATOMIC);
	अगर (!e) अणु
		QLA_VHA_MARK_NOT_BUSY(vha);
		वापस शून्य;
	पूर्ण

	INIT_LIST_HEAD(&e->list);
	e->type = type;
	e->flags = QLA_EVT_FLAG_FREE;
	वापस e;
पूर्ण

पूर्णांक
qla2x00_post_work(काष्ठा scsi_qla_host *vha, काष्ठा qla_work_evt *e)
अणु
	अचिन्हित दीर्घ flags;
	bool q = false;

	spin_lock_irqsave(&vha->work_lock, flags);
	list_add_tail(&e->list, &vha->work_list);

	अगर (!test_and_set_bit(IOCB_WORK_ACTIVE, &vha->dpc_flags))
		q = true;

	spin_unlock_irqrestore(&vha->work_lock, flags);

	अगर (q)
		queue_work(vha->hw->wq, &vha->iocb_work);

	वापस QLA_SUCCESS;
पूर्ण

पूर्णांक
qla2x00_post_aen_work(काष्ठा scsi_qla_host *vha, क्रमागत fc_host_event_code code,
    u32 data)
अणु
	काष्ठा qla_work_evt *e;

	e = qla2x00_alloc_work(vha, QLA_EVT_AEN);
	अगर (!e)
		वापस QLA_FUNCTION_FAILED;

	e->u.aen.code = code;
	e->u.aen.data = data;
	वापस qla2x00_post_work(vha, e);
पूर्ण

पूर्णांक
qla2x00_post_idc_ack_work(काष्ठा scsi_qla_host *vha, uपूर्णांक16_t *mb)
अणु
	काष्ठा qla_work_evt *e;

	e = qla2x00_alloc_work(vha, QLA_EVT_IDC_ACK);
	अगर (!e)
		वापस QLA_FUNCTION_FAILED;

	स_नकल(e->u.idc_ack.mb, mb, QLA_IDC_ACK_REGS * माप(uपूर्णांक16_t));
	वापस qla2x00_post_work(vha, e);
पूर्ण

#घोषणा qla2x00_post_async_work(name, type)	\
पूर्णांक qla2x00_post_async_##name##_work(		\
    काष्ठा scsi_qla_host *vha,			\
    fc_port_t *fcport, uपूर्णांक16_t *data)		\
अणु						\
	काष्ठा qla_work_evt *e;			\
						\
	e = qla2x00_alloc_work(vha, type);	\
	अगर (!e)					\
		वापस QLA_FUNCTION_FAILED;	\
						\
	e->u.logio.fcport = fcport;		\
	अगर (data) अणु				\
		e->u.logio.data[0] = data[0];	\
		e->u.logio.data[1] = data[1];	\
	पूर्ण					\
	fcport->flags |= FCF_ASYNC_ACTIVE;	\
	वापस qla2x00_post_work(vha, e);	\
पूर्ण

qla2x00_post_async_work(login, QLA_EVT_ASYNC_LOGIN);
qla2x00_post_async_work(logout, QLA_EVT_ASYNC_LOGOUT);
qla2x00_post_async_work(adisc, QLA_EVT_ASYNC_ADISC);
qla2x00_post_async_work(prlo, QLA_EVT_ASYNC_PRLO);
qla2x00_post_async_work(prlo_करोne, QLA_EVT_ASYNC_PRLO_DONE);

पूर्णांक
qla2x00_post_uevent_work(काष्ठा scsi_qla_host *vha, u32 code)
अणु
	काष्ठा qla_work_evt *e;

	e = qla2x00_alloc_work(vha, QLA_EVT_UEVENT);
	अगर (!e)
		वापस QLA_FUNCTION_FAILED;

	e->u.uevent.code = code;
	वापस qla2x00_post_work(vha, e);
पूर्ण

अटल व्योम
qla2x00_uevent_emit(काष्ठा scsi_qla_host *vha, u32 code)
अणु
	अक्षर event_string[40];
	अक्षर *envp[] = अणु event_string, शून्य पूर्ण;

	चयन (code) अणु
	हाल QLA_UEVENT_CODE_FW_DUMP:
		snम_लिखो(event_string, माप(event_string), "FW_DUMP=%lu",
		    vha->host_no);
		अवरोध;
	शेष:
		/* करो nothing */
		अवरोध;
	पूर्ण
	kobject_uevent_env(&vha->hw->pdev->dev.kobj, KOBJ_CHANGE, envp);
पूर्ण

पूर्णांक
qlafx00_post_aenfx_work(काष्ठा scsi_qla_host *vha,  uपूर्णांक32_t evtcode,
			uपूर्णांक32_t *data, पूर्णांक cnt)
अणु
	काष्ठा qla_work_evt *e;

	e = qla2x00_alloc_work(vha, QLA_EVT_AENFX);
	अगर (!e)
		वापस QLA_FUNCTION_FAILED;

	e->u.aenfx.evtcode = evtcode;
	e->u.aenfx.count = cnt;
	स_नकल(e->u.aenfx.mbx, data, माप(*data) * cnt);
	वापस qla2x00_post_work(vha, e);
पूर्ण

व्योम qla24xx_sched_upd_fcport(fc_port_t *fcport)
अणु
	अचिन्हित दीर्घ flags;

	अगर (IS_SW_RESV_ADDR(fcport->d_id))
		वापस;

	spin_lock_irqsave(&fcport->vha->work_lock, flags);
	अगर (fcport->disc_state == DSC_UPD_FCPORT) अणु
		spin_unlock_irqrestore(&fcport->vha->work_lock, flags);
		वापस;
	पूर्ण
	fcport->jअगरfies_at_registration = jअगरfies;
	fcport->sec_since_registration = 0;
	fcport->next_disc_state = DSC_DELETED;
	qla2x00_set_fcport_disc_state(fcport, DSC_UPD_FCPORT);
	spin_unlock_irqrestore(&fcport->vha->work_lock, flags);

	queue_work(प्रणाली_unbound_wq, &fcport->reg_work);
पूर्ण

अटल
व्योम qla24xx_create_new_sess(काष्ठा scsi_qla_host *vha, काष्ठा qla_work_evt *e)
अणु
	अचिन्हित दीर्घ flags;
	fc_port_t *fcport =  शून्य, *tfcp;
	काष्ठा qlt_plogi_ack_t *pla =
	    (काष्ठा qlt_plogi_ack_t *)e->u.new_sess.pla;
	uपूर्णांक8_t मुक्त_fcport = 0;

	ql_dbg(ql_dbg_disc, vha, 0xffff,
	    "%s %d %8phC enter\n",
	    __func__, __LINE__, e->u.new_sess.port_name);

	spin_lock_irqsave(&vha->hw->tgt.sess_lock, flags);
	fcport = qla2x00_find_fcport_by_wwpn(vha, e->u.new_sess.port_name, 1);
	अगर (fcport) अणु
		fcport->d_id = e->u.new_sess.id;
		अगर (pla) अणु
			fcport->fw_login_state = DSC_LS_PLOGI_PEND;
			स_नकल(fcport->node_name,
			    pla->iocb.u.isp24.u.plogi.node_name,
			    WWN_SIZE);
			qlt_plogi_ack_link(vha, pla, fcport, QLT_PLOGI_LINK_SAME_WWN);
			/* we took an extra ref_count to prevent PLOGI ACK when
			 * fcport/sess has not been created.
			 */
			pla->ref_count--;
		पूर्ण
	पूर्ण अन्यथा अणु
		spin_unlock_irqrestore(&vha->hw->tgt.sess_lock, flags);
		fcport = qla2x00_alloc_fcport(vha, GFP_KERNEL);
		अगर (fcport) अणु
			fcport->d_id = e->u.new_sess.id;
			fcport->flags |= FCF_FABRIC_DEVICE;
			fcport->fw_login_state = DSC_LS_PLOGI_PEND;
			fcport->tgt_लघु_link_करोwn_cnt = 0;

			स_नकल(fcport->port_name, e->u.new_sess.port_name,
			    WWN_SIZE);

			fcport->fc4_type = e->u.new_sess.fc4_type;
			अगर (e->u.new_sess.fc4_type & FS_FCP_IS_N2N) अणु
				fcport->dm_login_expire = jअगरfies +
					QLA_N2N_WAIT_TIME * HZ;
				fcport->fc4_type = FS_FC4TYPE_FCP;
				fcport->n2n_flag = 1;
				अगर (vha->flags.nvme_enabled)
					fcport->fc4_type |= FS_FC4TYPE_NVME;
			पूर्ण

		पूर्ण अन्यथा अणु
			ql_dbg(ql_dbg_disc, vha, 0xffff,
				   "%s %8phC mem alloc fail.\n",
				   __func__, e->u.new_sess.port_name);

			अगर (pla) अणु
				list_del(&pla->list);
				kmem_cache_मुक्त(qla_tgt_plogi_cachep, pla);
			पूर्ण
			वापस;
		पूर्ण

		spin_lock_irqsave(&vha->hw->tgt.sess_lock, flags);
		/* search again to make sure no one अन्यथा got ahead */
		tfcp = qla2x00_find_fcport_by_wwpn(vha,
		    e->u.new_sess.port_name, 1);
		अगर (tfcp) अणु
			/* should rarily happen */
			ql_dbg(ql_dbg_disc, vha, 0xffff,
			    "%s %8phC found existing fcport b4 add. DS %d LS %d\n",
			    __func__, tfcp->port_name, tfcp->disc_state,
			    tfcp->fw_login_state);

			मुक्त_fcport = 1;
		पूर्ण अन्यथा अणु
			list_add_tail(&fcport->list, &vha->vp_fcports);

		पूर्ण
		अगर (pla) अणु
			qlt_plogi_ack_link(vha, pla, fcport,
			    QLT_PLOGI_LINK_SAME_WWN);
			pla->ref_count--;
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&vha->hw->tgt.sess_lock, flags);

	अगर (fcport) अणु
		fcport->id_changed = 1;
		fcport->scan_state = QLA_FCPORT_FOUND;
		fcport->chip_reset = vha->hw->base_qpair->chip_reset;
		स_नकल(fcport->node_name, e->u.new_sess.node_name, WWN_SIZE);

		अगर (pla) अणु
			अगर (pla->iocb.u.isp24.status_subcode == ELS_PRLI) अणु
				u16 wd3_lo;

				fcport->fw_login_state = DSC_LS_PRLI_PEND;
				fcport->local = 0;
				fcport->loop_id =
					le16_to_cpu(
					    pla->iocb.u.isp24.nport_handle);
				fcport->fw_login_state = DSC_LS_PRLI_PEND;
				wd3_lo =
				    le16_to_cpu(
					pla->iocb.u.isp24.u.prli.wd3_lo);

				अगर (wd3_lo & BIT_7)
					fcport->conf_compl_supported = 1;

				अगर ((wd3_lo & BIT_4) == 0)
					fcport->port_type = FCT_INITIATOR;
				अन्यथा
					fcport->port_type = FCT_TARGET;
			पूर्ण
			qlt_plogi_ack_unref(vha, pla);
		पूर्ण अन्यथा अणु
			fc_port_t *dfcp = शून्य;

			spin_lock_irqsave(&vha->hw->tgt.sess_lock, flags);
			tfcp = qla2x00_find_fcport_by_nportid(vha,
			    &e->u.new_sess.id, 1);
			अगर (tfcp && (tfcp != fcport)) अणु
				/*
				 * We have a conflict fcport with same NportID.
				 */
				ql_dbg(ql_dbg_disc, vha, 0xffff,
				    "%s %8phC found conflict b4 add. DS %d LS %d\n",
				    __func__, tfcp->port_name, tfcp->disc_state,
				    tfcp->fw_login_state);

				चयन (tfcp->disc_state) अणु
				हाल DSC_DELETED:
					अवरोध;
				हाल DSC_DELETE_PEND:
					fcport->login_छोड़ो = 1;
					tfcp->conflict = fcport;
					अवरोध;
				शेष:
					fcport->login_छोड़ो = 1;
					tfcp->conflict = fcport;
					dfcp = tfcp;
					अवरोध;
				पूर्ण
			पूर्ण
			spin_unlock_irqrestore(&vha->hw->tgt.sess_lock, flags);
			अगर (dfcp)
				qlt_schedule_sess_क्रम_deletion(tfcp);

			अगर (N2N_TOPO(vha->hw)) अणु
				fcport->flags &= ~FCF_FABRIC_DEVICE;
				fcport->keep_nport_handle = 1;
				अगर (vha->flags.nvme_enabled) अणु
					fcport->fc4_type =
					    (FS_FC4TYPE_NVME | FS_FC4TYPE_FCP);
					fcport->n2n_flag = 1;
				पूर्ण
				fcport->fw_login_state = 0;

				schedule_delayed_work(&vha->scan.scan_work, 5);
			पूर्ण अन्यथा अणु
				qla24xx_fcport_handle_login(vha, fcport);
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (मुक्त_fcport) अणु
		qla2x00_मुक्त_fcport(fcport);
		अगर (pla) अणु
			list_del(&pla->list);
			kmem_cache_मुक्त(qla_tgt_plogi_cachep, pla);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम qla_sp_retry(काष्ठा scsi_qla_host *vha, काष्ठा qla_work_evt *e)
अणु
	काष्ठा srb *sp = e->u.iosb.sp;
	पूर्णांक rval;

	rval = qla2x00_start_sp(sp);
	अगर (rval != QLA_SUCCESS) अणु
		ql_dbg(ql_dbg_disc, vha, 0x2043,
		    "%s: %s: Re-issue IOCB failed (%d).\n",
		    __func__, sp->name, rval);
		qla24xx_sp_unmap(vha, sp);
	पूर्ण
पूर्ण

व्योम
qla2x00_करो_work(काष्ठा scsi_qla_host *vha)
अणु
	काष्ठा qla_work_evt *e, *पंचांगp;
	अचिन्हित दीर्घ flags;
	LIST_HEAD(work);
	पूर्णांक rc;

	spin_lock_irqsave(&vha->work_lock, flags);
	list_splice_init(&vha->work_list, &work);
	spin_unlock_irqrestore(&vha->work_lock, flags);

	list_क्रम_each_entry_safe(e, पंचांगp, &work, list) अणु
		rc = QLA_SUCCESS;
		चयन (e->type) अणु
		हाल QLA_EVT_AEN:
			fc_host_post_event(vha->host, fc_get_event_number(),
			    e->u.aen.code, e->u.aen.data);
			अवरोध;
		हाल QLA_EVT_IDC_ACK:
			qla81xx_idc_ack(vha, e->u.idc_ack.mb);
			अवरोध;
		हाल QLA_EVT_ASYNC_LOGIN:
			qla2x00_async_login(vha, e->u.logio.fcport,
			    e->u.logio.data);
			अवरोध;
		हाल QLA_EVT_ASYNC_LOGOUT:
			rc = qla2x00_async_logout(vha, e->u.logio.fcport);
			अवरोध;
		हाल QLA_EVT_ASYNC_ADISC:
			qla2x00_async_adisc(vha, e->u.logio.fcport,
			    e->u.logio.data);
			अवरोध;
		हाल QLA_EVT_UEVENT:
			qla2x00_uevent_emit(vha, e->u.uevent.code);
			अवरोध;
		हाल QLA_EVT_AENFX:
			qlafx00_process_aen(vha, e);
			अवरोध;
		हाल QLA_EVT_GPNID:
			qla24xx_async_gpnid(vha, &e->u.gpnid.id);
			अवरोध;
		हाल QLA_EVT_UNMAP:
			qla24xx_sp_unmap(vha, e->u.iosb.sp);
			अवरोध;
		हाल QLA_EVT_RELOGIN:
			qla2x00_relogin(vha);
			अवरोध;
		हाल QLA_EVT_NEW_SESS:
			qla24xx_create_new_sess(vha, e);
			अवरोध;
		हाल QLA_EVT_GPDB:
			qla24xx_async_gpdb(vha, e->u.fcport.fcport,
			    e->u.fcport.opt);
			अवरोध;
		हाल QLA_EVT_PRLI:
			qla24xx_async_prli(vha, e->u.fcport.fcport);
			अवरोध;
		हाल QLA_EVT_GPSC:
			qla24xx_async_gpsc(vha, e->u.fcport.fcport);
			अवरोध;
		हाल QLA_EVT_GNL:
			qla24xx_async_gnl(vha, e->u.fcport.fcport);
			अवरोध;
		हाल QLA_EVT_NACK:
			qla24xx_करो_nack_work(vha, e);
			अवरोध;
		हाल QLA_EVT_ASYNC_PRLO:
			rc = qla2x00_async_prlo(vha, e->u.logio.fcport);
			अवरोध;
		हाल QLA_EVT_ASYNC_PRLO_DONE:
			qla2x00_async_prlo_करोne(vha, e->u.logio.fcport,
			    e->u.logio.data);
			अवरोध;
		हाल QLA_EVT_GPNFT:
			qla24xx_async_gpnft(vha, e->u.gpnft.fc4_type,
			    e->u.gpnft.sp);
			अवरोध;
		हाल QLA_EVT_GPNFT_DONE:
			qla24xx_async_gpnft_करोne(vha, e->u.iosb.sp);
			अवरोध;
		हाल QLA_EVT_GNNFT_DONE:
			qla24xx_async_gnnft_करोne(vha, e->u.iosb.sp);
			अवरोध;
		हाल QLA_EVT_GNNID:
			qla24xx_async_gnnid(vha, e->u.fcport.fcport);
			अवरोध;
		हाल QLA_EVT_GFPNID:
			qla24xx_async_gfpnid(vha, e->u.fcport.fcport);
			अवरोध;
		हाल QLA_EVT_SP_RETRY:
			qla_sp_retry(vha, e);
			अवरोध;
		हाल QLA_EVT_IIDMA:
			qla_करो_iidma_work(vha, e->u.fcport.fcport);
			अवरोध;
		हाल QLA_EVT_ELS_PLOGI:
			qla24xx_els_dcmd2_iocb(vha, ELS_DCMD_PLOGI,
			    e->u.fcport.fcport, false);
			अवरोध;
		पूर्ण

		अगर (rc == EAGAIN) अणु
			/* put 'work' at head of 'vha->work_list' */
			spin_lock_irqsave(&vha->work_lock, flags);
			list_splice(&work, &vha->work_list);
			spin_unlock_irqrestore(&vha->work_lock, flags);
			अवरोध;
		पूर्ण
		list_del_init(&e->list);
		अगर (e->flags & QLA_EVT_FLAG_FREE)
			kमुक्त(e);

		/* For each work completed decrement vha ref count */
		QLA_VHA_MARK_NOT_BUSY(vha);
	पूर्ण
पूर्ण

पूर्णांक qla24xx_post_relogin_work(काष्ठा scsi_qla_host *vha)
अणु
	काष्ठा qla_work_evt *e;

	e = qla2x00_alloc_work(vha, QLA_EVT_RELOGIN);

	अगर (!e) अणु
		set_bit(RELOGIN_NEEDED, &vha->dpc_flags);
		वापस QLA_FUNCTION_FAILED;
	पूर्ण

	वापस qla2x00_post_work(vha, e);
पूर्ण

/* Relogins all the fcports of a vport
 * Context: dpc thपढ़ो
 */
व्योम qla2x00_relogin(काष्ठा scsi_qla_host *vha)
अणु
	fc_port_t       *fcport;
	पूर्णांक status, relogin_needed = 0;
	काष्ठा event_arg ea;

	list_क्रम_each_entry(fcport, &vha->vp_fcports, list) अणु
		/*
		 * If the port is not ONLINE then try to login
		 * to it अगर we haven't run out of retries.
		 */
		अगर (atomic_पढ़ो(&fcport->state) != FCS_ONLINE &&
		    fcport->login_retry) अणु
			अगर (fcport->scan_state != QLA_FCPORT_FOUND ||
			    fcport->disc_state == DSC_LOGIN_COMPLETE)
				जारी;

			अगर (fcport->flags & (FCF_ASYNC_SENT|FCF_ASYNC_ACTIVE) ||
				fcport->disc_state == DSC_DELETE_PEND) अणु
				relogin_needed = 1;
			पूर्ण अन्यथा अणु
				अगर (vha->hw->current_topology != ISP_CFG_NL) अणु
					स_रखो(&ea, 0, माप(ea));
					ea.fcport = fcport;
					qla24xx_handle_relogin_event(vha, &ea);
				पूर्ण अन्यथा अगर (vha->hw->current_topology ==
				    ISP_CFG_NL) अणु
					fcport->login_retry--;
					status =
					    qla2x00_local_device_login(vha,
						fcport);
					अगर (status == QLA_SUCCESS) अणु
						fcport->old_loop_id =
						    fcport->loop_id;
						ql_dbg(ql_dbg_disc, vha, 0x2003,
						    "Port login OK: logged in ID 0x%x.\n",
						    fcport->loop_id);
						qla2x00_update_fcport
							(vha, fcport);
					पूर्ण अन्यथा अगर (status == 1) अणु
						set_bit(RELOGIN_NEEDED,
						    &vha->dpc_flags);
						/* retry the login again */
						ql_dbg(ql_dbg_disc, vha, 0x2007,
						    "Retrying %d login again loop_id 0x%x.\n",
						    fcport->login_retry,
						    fcport->loop_id);
					पूर्ण अन्यथा अणु
						fcport->login_retry = 0;
					पूर्ण

					अगर (fcport->login_retry == 0 &&
					    status != QLA_SUCCESS)
						qla2x00_clear_loop_id(fcport);
				पूर्ण
			पूर्ण
		पूर्ण
		अगर (test_bit(LOOP_RESYNC_NEEDED, &vha->dpc_flags))
			अवरोध;
	पूर्ण

	अगर (relogin_needed)
		set_bit(RELOGIN_NEEDED, &vha->dpc_flags);

	ql_dbg(ql_dbg_disc, vha, 0x400e,
	    "Relogin end.\n");
पूर्ण

/* Schedule work on any of the dpc-workqueues */
व्योम
qla83xx_schedule_work(scsi_qla_host_t *base_vha, पूर्णांक work_code)
अणु
	काष्ठा qla_hw_data *ha = base_vha->hw;

	चयन (work_code) अणु
	हाल MBA_IDC_AEN: /* 0x8200 */
		अगर (ha->dpc_lp_wq)
			queue_work(ha->dpc_lp_wq, &ha->idc_aen);
		अवरोध;

	हाल QLA83XX_NIC_CORE_RESET: /* 0x1 */
		अगर (!ha->flags.nic_core_reset_hdlr_active) अणु
			अगर (ha->dpc_hp_wq)
				queue_work(ha->dpc_hp_wq, &ha->nic_core_reset);
		पूर्ण अन्यथा
			ql_dbg(ql_dbg_p3p, base_vha, 0xb05e,
			    "NIC Core reset is already active. Skip "
			    "scheduling it again.\n");
		अवरोध;
	हाल QLA83XX_IDC_STATE_HANDLER: /* 0x2 */
		अगर (ha->dpc_hp_wq)
			queue_work(ha->dpc_hp_wq, &ha->idc_state_handler);
		अवरोध;
	हाल QLA83XX_NIC_CORE_UNRECOVERABLE: /* 0x3 */
		अगर (ha->dpc_hp_wq)
			queue_work(ha->dpc_hp_wq, &ha->nic_core_unrecoverable);
		अवरोध;
	शेष:
		ql_log(ql_log_warn, base_vha, 0xb05f,
		    "Unknown work-code=0x%x.\n", work_code);
	पूर्ण

	वापस;
पूर्ण

/* Work: Perक्रमm NIC Core Unrecoverable state handling */
व्योम
qla83xx_nic_core_unrecoverable_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा qla_hw_data *ha =
		container_of(work, काष्ठा qla_hw_data, nic_core_unrecoverable);
	scsi_qla_host_t *base_vha = pci_get_drvdata(ha->pdev);
	uपूर्णांक32_t dev_state = 0;

	qla83xx_idc_lock(base_vha, 0);
	qla83xx_rd_reg(base_vha, QLA83XX_IDC_DEV_STATE, &dev_state);
	qla83xx_reset_ownership(base_vha);
	अगर (ha->flags.nic_core_reset_owner) अणु
		ha->flags.nic_core_reset_owner = 0;
		qla83xx_wr_reg(base_vha, QLA83XX_IDC_DEV_STATE,
		    QLA8XXX_DEV_FAILED);
		ql_log(ql_log_info, base_vha, 0xb060, "HW State: FAILED.\n");
		qla83xx_schedule_work(base_vha, QLA83XX_IDC_STATE_HANDLER);
	पूर्ण
	qla83xx_idc_unlock(base_vha, 0);
पूर्ण

/* Work: Execute IDC state handler */
व्योम
qla83xx_idc_state_handler_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा qla_hw_data *ha =
		container_of(work, काष्ठा qla_hw_data, idc_state_handler);
	scsi_qla_host_t *base_vha = pci_get_drvdata(ha->pdev);
	uपूर्णांक32_t dev_state = 0;

	qla83xx_idc_lock(base_vha, 0);
	qla83xx_rd_reg(base_vha, QLA83XX_IDC_DEV_STATE, &dev_state);
	अगर (dev_state == QLA8XXX_DEV_FAILED ||
			dev_state == QLA8XXX_DEV_NEED_QUIESCENT)
		qla83xx_idc_state_handler(base_vha);
	qla83xx_idc_unlock(base_vha, 0);
पूर्ण

अटल पूर्णांक
qla83xx_check_nic_core_fw_alive(scsi_qla_host_t *base_vha)
अणु
	पूर्णांक rval = QLA_SUCCESS;
	अचिन्हित दीर्घ heart_beat_रुको = jअगरfies + (1 * HZ);
	uपूर्णांक32_t heart_beat_counter1, heart_beat_counter2;

	करो अणु
		अगर (समय_after(jअगरfies, heart_beat_रुको)) अणु
			ql_dbg(ql_dbg_p3p, base_vha, 0xb07c,
			    "Nic Core f/w is not alive.\n");
			rval = QLA_FUNCTION_FAILED;
			अवरोध;
		पूर्ण

		qla83xx_idc_lock(base_vha, 0);
		qla83xx_rd_reg(base_vha, QLA83XX_FW_HEARTBEAT,
		    &heart_beat_counter1);
		qla83xx_idc_unlock(base_vha, 0);
		msleep(100);
		qla83xx_idc_lock(base_vha, 0);
		qla83xx_rd_reg(base_vha, QLA83XX_FW_HEARTBEAT,
		    &heart_beat_counter2);
		qla83xx_idc_unlock(base_vha, 0);
	पूर्ण जबतक (heart_beat_counter1 == heart_beat_counter2);

	वापस rval;
पूर्ण

/* Work: Perक्रमm NIC Core Reset handling */
व्योम
qla83xx_nic_core_reset_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा qla_hw_data *ha =
		container_of(work, काष्ठा qla_hw_data, nic_core_reset);
	scsi_qla_host_t *base_vha = pci_get_drvdata(ha->pdev);
	uपूर्णांक32_t dev_state = 0;

	अगर (IS_QLA2031(ha)) अणु
		अगर (qla2xxx_mctp_dump(base_vha) != QLA_SUCCESS)
			ql_log(ql_log_warn, base_vha, 0xb081,
			    "Failed to dump mctp\n");
		वापस;
	पूर्ण

	अगर (!ha->flags.nic_core_reset_hdlr_active) अणु
		अगर (qla83xx_check_nic_core_fw_alive(base_vha) == QLA_SUCCESS) अणु
			qla83xx_idc_lock(base_vha, 0);
			qla83xx_rd_reg(base_vha, QLA83XX_IDC_DEV_STATE,
			    &dev_state);
			qla83xx_idc_unlock(base_vha, 0);
			अगर (dev_state != QLA8XXX_DEV_NEED_RESET) अणु
				ql_dbg(ql_dbg_p3p, base_vha, 0xb07a,
				    "Nic Core f/w is alive.\n");
				वापस;
			पूर्ण
		पूर्ण

		ha->flags.nic_core_reset_hdlr_active = 1;
		अगर (qla83xx_nic_core_reset(base_vha)) अणु
			/* NIC Core reset failed. */
			ql_dbg(ql_dbg_p3p, base_vha, 0xb061,
			    "NIC Core reset failed.\n");
		पूर्ण
		ha->flags.nic_core_reset_hdlr_active = 0;
	पूर्ण
पूर्ण

/* Work: Handle 8200 IDC aens */
व्योम
qla83xx_service_idc_aen(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा qla_hw_data *ha =
		container_of(work, काष्ठा qla_hw_data, idc_aen);
	scsi_qla_host_t *base_vha = pci_get_drvdata(ha->pdev);
	uपूर्णांक32_t dev_state, idc_control;

	qla83xx_idc_lock(base_vha, 0);
	qla83xx_rd_reg(base_vha, QLA83XX_IDC_DEV_STATE, &dev_state);
	qla83xx_rd_reg(base_vha, QLA83XX_IDC_CONTROL, &idc_control);
	qla83xx_idc_unlock(base_vha, 0);
	अगर (dev_state == QLA8XXX_DEV_NEED_RESET) अणु
		अगर (idc_control & QLA83XX_IDC_GRACEFUL_RESET) अणु
			ql_dbg(ql_dbg_p3p, base_vha, 0xb062,
			    "Application requested NIC Core Reset.\n");
			qla83xx_schedule_work(base_vha, QLA83XX_NIC_CORE_RESET);
		पूर्ण अन्यथा अगर (qla83xx_check_nic_core_fw_alive(base_vha) ==
		    QLA_SUCCESS) अणु
			ql_dbg(ql_dbg_p3p, base_vha, 0xb07b,
			    "Other protocol driver requested NIC Core Reset.\n");
			qla83xx_schedule_work(base_vha, QLA83XX_NIC_CORE_RESET);
		पूर्ण
	पूर्ण अन्यथा अगर (dev_state == QLA8XXX_DEV_FAILED ||
			dev_state == QLA8XXX_DEV_NEED_QUIESCENT) अणु
		qla83xx_schedule_work(base_vha, QLA83XX_IDC_STATE_HANDLER);
	पूर्ण
पूर्ण

/*
 * Control the frequency of IDC lock retries
 */
#घोषणा QLA83XX_WAIT_LOGIC_MS	100

अटल पूर्णांक
qla83xx_क्रमce_lock_recovery(scsi_qla_host_t *base_vha)
अणु
	पूर्णांक rval;
	uपूर्णांक32_t data;
	uपूर्णांक32_t idc_lck_rcvry_stage_mask = 0x3;
	uपूर्णांक32_t idc_lck_rcvry_owner_mask = 0x3c;
	काष्ठा qla_hw_data *ha = base_vha->hw;

	ql_dbg(ql_dbg_p3p, base_vha, 0xb086,
	    "Trying force recovery of the IDC lock.\n");

	rval = qla83xx_rd_reg(base_vha, QLA83XX_IDC_LOCK_RECOVERY, &data);
	अगर (rval)
		वापस rval;

	अगर ((data & idc_lck_rcvry_stage_mask) > 0) अणु
		वापस QLA_SUCCESS;
	पूर्ण अन्यथा अणु
		data = (IDC_LOCK_RECOVERY_STAGE1) | (ha->portnum << 2);
		rval = qla83xx_wr_reg(base_vha, QLA83XX_IDC_LOCK_RECOVERY,
		    data);
		अगर (rval)
			वापस rval;

		msleep(200);

		rval = qla83xx_rd_reg(base_vha, QLA83XX_IDC_LOCK_RECOVERY,
		    &data);
		अगर (rval)
			वापस rval;

		अगर (((data & idc_lck_rcvry_owner_mask) >> 2) == ha->portnum) अणु
			data &= (IDC_LOCK_RECOVERY_STAGE2 |
					~(idc_lck_rcvry_stage_mask));
			rval = qla83xx_wr_reg(base_vha,
			    QLA83XX_IDC_LOCK_RECOVERY, data);
			अगर (rval)
				वापस rval;

			/* Forcefully perक्रमm IDC UnLock */
			rval = qla83xx_rd_reg(base_vha, QLA83XX_DRIVER_UNLOCK,
			    &data);
			अगर (rval)
				वापस rval;
			/* Clear lock-id by setting 0xff */
			rval = qla83xx_wr_reg(base_vha, QLA83XX_DRIVER_LOCKID,
			    0xff);
			अगर (rval)
				वापस rval;
			/* Clear lock-recovery by setting 0x0 */
			rval = qla83xx_wr_reg(base_vha,
			    QLA83XX_IDC_LOCK_RECOVERY, 0x0);
			अगर (rval)
				वापस rval;
		पूर्ण अन्यथा
			वापस QLA_SUCCESS;
	पूर्ण

	वापस rval;
पूर्ण

अटल पूर्णांक
qla83xx_idc_lock_recovery(scsi_qla_host_t *base_vha)
अणु
	पूर्णांक rval = QLA_SUCCESS;
	uपूर्णांक32_t o_drv_lockid, n_drv_lockid;
	अचिन्हित दीर्घ lock_recovery_समयout;

	lock_recovery_समयout = jअगरfies + QLA83XX_MAX_LOCK_RECOVERY_WAIT;
retry_lockid:
	rval = qla83xx_rd_reg(base_vha, QLA83XX_DRIVER_LOCKID, &o_drv_lockid);
	अगर (rval)
		जाओ निकास;

	/* MAX रुको समय beक्रमe क्रमcing IDC Lock recovery = 2 secs */
	अगर (समय_after_eq(jअगरfies, lock_recovery_समयout)) अणु
		अगर (qla83xx_क्रमce_lock_recovery(base_vha) == QLA_SUCCESS)
			वापस QLA_SUCCESS;
		अन्यथा
			वापस QLA_FUNCTION_FAILED;
	पूर्ण

	rval = qla83xx_rd_reg(base_vha, QLA83XX_DRIVER_LOCKID, &n_drv_lockid);
	अगर (rval)
		जाओ निकास;

	अगर (o_drv_lockid == n_drv_lockid) अणु
		msleep(QLA83XX_WAIT_LOGIC_MS);
		जाओ retry_lockid;
	पूर्ण अन्यथा
		वापस QLA_SUCCESS;

निकास:
	वापस rval;
पूर्ण

/*
 * Context: task, can sleep
 */
व्योम
qla83xx_idc_lock(scsi_qla_host_t *base_vha, uपूर्णांक16_t requester_id)
अणु
	uपूर्णांक32_t data;
	uपूर्णांक32_t lock_owner;
	काष्ठा qla_hw_data *ha = base_vha->hw;

	might_sleep();

	/* IDC-lock implementation using driver-lock/lock-id remote रेजिस्टरs */
retry_lock:
	अगर (qla83xx_rd_reg(base_vha, QLA83XX_DRIVER_LOCK, &data)
	    == QLA_SUCCESS) अणु
		अगर (data) अणु
			/* Setting lock-id to our function-number */
			qla83xx_wr_reg(base_vha, QLA83XX_DRIVER_LOCKID,
			    ha->portnum);
		पूर्ण अन्यथा अणु
			qla83xx_rd_reg(base_vha, QLA83XX_DRIVER_LOCKID,
			    &lock_owner);
			ql_dbg(ql_dbg_p3p, base_vha, 0xb063,
			    "Failed to acquire IDC lock, acquired by %d, "
			    "retrying...\n", lock_owner);

			/* Retry/Perक्रमm IDC-Lock recovery */
			अगर (qla83xx_idc_lock_recovery(base_vha)
			    == QLA_SUCCESS) अणु
				msleep(QLA83XX_WAIT_LOGIC_MS);
				जाओ retry_lock;
			पूर्ण अन्यथा
				ql_log(ql_log_warn, base_vha, 0xb075,
				    "IDC Lock recovery FAILED.\n");
		पूर्ण

	पूर्ण

	वापस;
पूर्ण

अटल bool
qla25xx_rdp_rsp_reduce_size(काष्ठा scsi_qla_host *vha,
	काष्ठा purex_entry_24xx *purex)
अणु
	अक्षर fwstr[16];
	u32 sid = purex->s_id[2] << 16 | purex->s_id[1] << 8 | purex->s_id[0];
	काष्ठा port_database_24xx *pdb;

	/* Doमुख्य Controller is always logged-out. */
	/* अगर RDP request is not from Doमुख्य Controller: */
	अगर (sid != 0xfffc01)
		वापस false;

	ql_dbg(ql_dbg_init, vha, 0x0181, "%s: s_id=%#x\n", __func__, sid);

	pdb = kzalloc(माप(*pdb), GFP_KERNEL);
	अगर (!pdb) अणु
		ql_dbg(ql_dbg_init, vha, 0x0181,
		    "%s: Failed allocate pdb\n", __func__);
	पूर्ण अन्यथा अगर (qla24xx_get_port_database(vha,
				le16_to_cpu(purex->nport_handle), pdb)) अणु
		ql_dbg(ql_dbg_init, vha, 0x0181,
		    "%s: Failed get pdb sid=%x\n", __func__, sid);
	पूर्ण अन्यथा अगर (pdb->current_login_state != PDS_PLOGI_COMPLETE &&
	    pdb->current_login_state != PDS_PRLI_COMPLETE) अणु
		ql_dbg(ql_dbg_init, vha, 0x0181,
		    "%s: Port not logged in sid=%#x\n", __func__, sid);
	पूर्ण अन्यथा अणु
		/* RDP request is from logged in port */
		kमुक्त(pdb);
		वापस false;
	पूर्ण
	kमुक्त(pdb);

	vha->hw->isp_ops->fw_version_str(vha, fwstr, माप(fwstr));
	fwstr[म_खोज(fwstr, " ")] = 0;
	/* अगर FW version allows RDP response length upto 2048 bytes: */
	अगर (म_भेद(fwstr, "8.09.00") > 0 || म_भेद(fwstr, "8.05.65") == 0)
		वापस false;

	ql_dbg(ql_dbg_init, vha, 0x0181, "%s: fw=%s\n", __func__, fwstr);

	/* RDP response length is to be reduced to maximum 256 bytes */
	वापस true;
पूर्ण

/*
 * Function Name: qla24xx_process_purex_iocb
 *
 * Description:
 * Prepare a RDP response and send to Fabric चयन
 *
 * PARAMETERS:
 * vha:	SCSI qla host
 * purex: RDP request received by HBA
 */
व्योम qla24xx_process_purex_rdp(काष्ठा scsi_qla_host *vha,
			       काष्ठा purex_item *item)
अणु
	काष्ठा qla_hw_data *ha = vha->hw;
	काष्ठा purex_entry_24xx *purex =
	    (काष्ठा purex_entry_24xx *)&item->iocb;
	dma_addr_t rsp_els_dma;
	dma_addr_t rsp_payload_dma;
	dma_addr_t stat_dma;
	dma_addr_t sfp_dma;
	काष्ठा els_entry_24xx *rsp_els = शून्य;
	काष्ठा rdp_rsp_payload *rsp_payload = शून्य;
	काष्ठा link_statistics *stat = शून्य;
	uपूर्णांक8_t *sfp = शून्य;
	uपूर्णांक16_t sfp_flags = 0;
	uपूर्णांक rsp_payload_length = माप(*rsp_payload);
	पूर्णांक rval;

	ql_dbg(ql_dbg_init + ql_dbg_verbose, vha, 0x0180,
	    "%s: Enter\n", __func__);

	ql_dbg(ql_dbg_init + ql_dbg_verbose, vha, 0x0181,
	    "-------- ELS REQ -------\n");
	ql_dump_buffer(ql_dbg_init + ql_dbg_verbose, vha, 0x0182,
	    purex, माप(*purex));

	अगर (qla25xx_rdp_rsp_reduce_size(vha, purex)) अणु
		rsp_payload_length =
		    दुरत्व(typeof(*rsp_payload), optical_elmt_desc);
		ql_dbg(ql_dbg_init, vha, 0x0181,
		    "Reducing RSP payload length to %u bytes...\n",
		    rsp_payload_length);
	पूर्ण

	rsp_els = dma_alloc_coherent(&ha->pdev->dev, माप(*rsp_els),
	    &rsp_els_dma, GFP_KERNEL);
	अगर (!rsp_els) अणु
		ql_log(ql_log_warn, vha, 0x0183,
		    "Failed allocate dma buffer ELS RSP.\n");
		जाओ dealloc;
	पूर्ण

	rsp_payload = dma_alloc_coherent(&ha->pdev->dev, माप(*rsp_payload),
	    &rsp_payload_dma, GFP_KERNEL);
	अगर (!rsp_payload) अणु
		ql_log(ql_log_warn, vha, 0x0184,
		    "Failed allocate dma buffer ELS RSP payload.\n");
		जाओ dealloc;
	पूर्ण

	sfp = dma_alloc_coherent(&ha->pdev->dev, SFP_RTDI_LEN,
	    &sfp_dma, GFP_KERNEL);

	stat = dma_alloc_coherent(&ha->pdev->dev, माप(*stat),
	    &stat_dma, GFP_KERNEL);

	/* Prepare Response IOCB */
	rsp_els->entry_type = ELS_IOCB_TYPE;
	rsp_els->entry_count = 1;
	rsp_els->sys_define = 0;
	rsp_els->entry_status = 0;
	rsp_els->handle = 0;
	rsp_els->nport_handle = purex->nport_handle;
	rsp_els->tx_dsd_count = cpu_to_le16(1);
	rsp_els->vp_index = purex->vp_idx;
	rsp_els->sof_type = EST_SOFI3;
	rsp_els->rx_xchg_address = purex->rx_xchg_addr;
	rsp_els->rx_dsd_count = 0;
	rsp_els->opcode = purex->els_frame_payload[0];

	rsp_els->d_id[0] = purex->s_id[0];
	rsp_els->d_id[1] = purex->s_id[1];
	rsp_els->d_id[2] = purex->s_id[2];

	rsp_els->control_flags = cpu_to_le16(EPD_ELS_ACC);
	rsp_els->rx_byte_count = 0;
	rsp_els->tx_byte_count = cpu_to_le32(rsp_payload_length);

	put_unaligned_le64(rsp_payload_dma, &rsp_els->tx_address);
	rsp_els->tx_len = rsp_els->tx_byte_count;

	rsp_els->rx_address = 0;
	rsp_els->rx_len = 0;

	/* Prepare Response Payload */
	rsp_payload->hdr.cmd = cpu_to_be32(0x2 << 24); /* LS_ACC */
	rsp_payload->hdr.len = cpu_to_be32(le32_to_cpu(rsp_els->tx_byte_count) -
					   माप(rsp_payload->hdr));

	/* Link service Request Info Descriptor */
	rsp_payload->ls_req_info_desc.desc_tag = cpu_to_be32(0x1);
	rsp_payload->ls_req_info_desc.desc_len =
	    cpu_to_be32(RDP_DESC_LEN(rsp_payload->ls_req_info_desc));
	rsp_payload->ls_req_info_desc.req_payload_word_0 =
	    cpu_to_be32p((uपूर्णांक32_t *)purex->els_frame_payload);

	/* Link service Request Info Descriptor 2 */
	rsp_payload->ls_req_info_desc2.desc_tag = cpu_to_be32(0x1);
	rsp_payload->ls_req_info_desc2.desc_len =
	    cpu_to_be32(RDP_DESC_LEN(rsp_payload->ls_req_info_desc2));
	rsp_payload->ls_req_info_desc2.req_payload_word_0 =
	    cpu_to_be32p((uपूर्णांक32_t *)purex->els_frame_payload);


	rsp_payload->sfp_diag_desc.desc_tag = cpu_to_be32(0x10000);
	rsp_payload->sfp_diag_desc.desc_len =
		cpu_to_be32(RDP_DESC_LEN(rsp_payload->sfp_diag_desc));

	अगर (sfp) अणु
		/* SFP Flags */
		स_रखो(sfp, 0, SFP_RTDI_LEN);
		rval = qla2x00_पढ़ो_sfp(vha, sfp_dma, sfp, 0xa0, 0x7, 2, 0);
		अगर (!rval) अणु
			/* SFP Flags bits 3-0: Port Tx Laser Type */
			अगर (sfp[0] & BIT_2 || sfp[1] & (BIT_6|BIT_5))
				sfp_flags |= BIT_0; /* लघु wave */
			अन्यथा अगर (sfp[0] & BIT_1)
				sfp_flags |= BIT_1; /* दीर्घ wave 1310nm */
			अन्यथा अगर (sfp[1] & BIT_4)
				sfp_flags |= BIT_1|BIT_0; /* दीर्घ wave 1550nm */
		पूर्ण

		/* SFP Type */
		स_रखो(sfp, 0, SFP_RTDI_LEN);
		rval = qla2x00_पढ़ो_sfp(vha, sfp_dma, sfp, 0xa0, 0x0, 1, 0);
		अगर (!rval) अणु
			sfp_flags |= BIT_4; /* optical */
			अगर (sfp[0] == 0x3)
				sfp_flags |= BIT_6; /* sfp+ */
		पूर्ण

		rsp_payload->sfp_diag_desc.sfp_flags = cpu_to_be16(sfp_flags);

		/* SFP Diagnostics */
		स_रखो(sfp, 0, SFP_RTDI_LEN);
		rval = qla2x00_पढ़ो_sfp(vha, sfp_dma, sfp, 0xa2, 0x60, 10, 0);
		अगर (!rval) अणु
			__be16 *trx = (__क्रमce __be16 *)sfp; /* alपढ़ोy be16 */
			rsp_payload->sfp_diag_desc.temperature = trx[0];
			rsp_payload->sfp_diag_desc.vcc = trx[1];
			rsp_payload->sfp_diag_desc.tx_bias = trx[2];
			rsp_payload->sfp_diag_desc.tx_घातer = trx[3];
			rsp_payload->sfp_diag_desc.rx_घातer = trx[4];
		पूर्ण
	पूर्ण

	/* Port Speed Descriptor */
	rsp_payload->port_speed_desc.desc_tag = cpu_to_be32(0x10001);
	rsp_payload->port_speed_desc.desc_len =
	    cpu_to_be32(RDP_DESC_LEN(rsp_payload->port_speed_desc));
	rsp_payload->port_speed_desc.speed_capab = cpu_to_be16(
	    qla25xx_fdmi_port_speed_capability(ha));
	rsp_payload->port_speed_desc.operating_speed = cpu_to_be16(
	    qla25xx_fdmi_port_speed_currently(ha));

	/* Link Error Status Descriptor */
	rsp_payload->ls_err_desc.desc_tag = cpu_to_be32(0x10002);
	rsp_payload->ls_err_desc.desc_len =
		cpu_to_be32(RDP_DESC_LEN(rsp_payload->ls_err_desc));

	अगर (stat) अणु
		rval = qla24xx_get_isp_stats(vha, stat, stat_dma, 0);
		अगर (!rval) अणु
			rsp_payload->ls_err_desc.link_fail_cnt =
			    cpu_to_be32(le32_to_cpu(stat->link_fail_cnt));
			rsp_payload->ls_err_desc.loss_sync_cnt =
			    cpu_to_be32(le32_to_cpu(stat->loss_sync_cnt));
			rsp_payload->ls_err_desc.loss_sig_cnt =
			    cpu_to_be32(le32_to_cpu(stat->loss_sig_cnt));
			rsp_payload->ls_err_desc.prim_seq_err_cnt =
			    cpu_to_be32(le32_to_cpu(stat->prim_seq_err_cnt));
			rsp_payload->ls_err_desc.inval_xmit_word_cnt =
			    cpu_to_be32(le32_to_cpu(stat->inval_xmit_word_cnt));
			rsp_payload->ls_err_desc.inval_crc_cnt =
			    cpu_to_be32(le32_to_cpu(stat->inval_crc_cnt));
			rsp_payload->ls_err_desc.pn_port_phy_type |= BIT_6;
		पूर्ण
	पूर्ण

	/* Portname Descriptor */
	rsp_payload->port_name_diag_desc.desc_tag = cpu_to_be32(0x10003);
	rsp_payload->port_name_diag_desc.desc_len =
	    cpu_to_be32(RDP_DESC_LEN(rsp_payload->port_name_diag_desc));
	स_नकल(rsp_payload->port_name_diag_desc.WWNN,
	    vha->node_name,
	    माप(rsp_payload->port_name_diag_desc.WWNN));
	स_नकल(rsp_payload->port_name_diag_desc.WWPN,
	    vha->port_name,
	    माप(rsp_payload->port_name_diag_desc.WWPN));

	/* F-Port Portname Descriptor */
	rsp_payload->port_name_direct_desc.desc_tag = cpu_to_be32(0x10003);
	rsp_payload->port_name_direct_desc.desc_len =
	    cpu_to_be32(RDP_DESC_LEN(rsp_payload->port_name_direct_desc));
	स_नकल(rsp_payload->port_name_direct_desc.WWNN,
	    vha->fabric_node_name,
	    माप(rsp_payload->port_name_direct_desc.WWNN));
	स_नकल(rsp_payload->port_name_direct_desc.WWPN,
	    vha->fabric_port_name,
	    माप(rsp_payload->port_name_direct_desc.WWPN));

	/* Bufer Credit Descriptor */
	rsp_payload->buffer_credit_desc.desc_tag = cpu_to_be32(0x10006);
	rsp_payload->buffer_credit_desc.desc_len =
		cpu_to_be32(RDP_DESC_LEN(rsp_payload->buffer_credit_desc));
	rsp_payload->buffer_credit_desc.fcport_b2b = 0;
	rsp_payload->buffer_credit_desc.attached_fcport_b2b = cpu_to_be32(0);
	rsp_payload->buffer_credit_desc.fcport_rtt = cpu_to_be32(0);

	अगर (ha->flags.plogi_ढाँचा_valid) अणु
		uपूर्णांक32_t पंचांगp =
		be16_to_cpu(ha->plogi_els_payld.fl_csp.sp_bb_cred);
		rsp_payload->buffer_credit_desc.fcport_b2b = cpu_to_be32(पंचांगp);
	पूर्ण

	अगर (rsp_payload_length < माप(*rsp_payload))
		जाओ send;

	/* Optical Element Descriptor, Temperature */
	rsp_payload->optical_elmt_desc[0].desc_tag = cpu_to_be32(0x10007);
	rsp_payload->optical_elmt_desc[0].desc_len =
		cpu_to_be32(RDP_DESC_LEN(*rsp_payload->optical_elmt_desc));
	/* Optical Element Descriptor, Voltage */
	rsp_payload->optical_elmt_desc[1].desc_tag = cpu_to_be32(0x10007);
	rsp_payload->optical_elmt_desc[1].desc_len =
		cpu_to_be32(RDP_DESC_LEN(*rsp_payload->optical_elmt_desc));
	/* Optical Element Descriptor, Tx Bias Current */
	rsp_payload->optical_elmt_desc[2].desc_tag = cpu_to_be32(0x10007);
	rsp_payload->optical_elmt_desc[2].desc_len =
		cpu_to_be32(RDP_DESC_LEN(*rsp_payload->optical_elmt_desc));
	/* Optical Element Descriptor, Tx Power */
	rsp_payload->optical_elmt_desc[3].desc_tag = cpu_to_be32(0x10007);
	rsp_payload->optical_elmt_desc[3].desc_len =
		cpu_to_be32(RDP_DESC_LEN(*rsp_payload->optical_elmt_desc));
	/* Optical Element Descriptor, Rx Power */
	rsp_payload->optical_elmt_desc[4].desc_tag = cpu_to_be32(0x10007);
	rsp_payload->optical_elmt_desc[4].desc_len =
		cpu_to_be32(RDP_DESC_LEN(*rsp_payload->optical_elmt_desc));

	अगर (sfp) अणु
		स_रखो(sfp, 0, SFP_RTDI_LEN);
		rval = qla2x00_पढ़ो_sfp(vha, sfp_dma, sfp, 0xa2, 0, 64, 0);
		अगर (!rval) अणु
			__be16 *trx = (__क्रमce __be16 *)sfp; /* alपढ़ोy be16 */

			/* Optical Element Descriptor, Temperature */
			rsp_payload->optical_elmt_desc[0].high_alarm = trx[0];
			rsp_payload->optical_elmt_desc[0].low_alarm = trx[1];
			rsp_payload->optical_elmt_desc[0].high_warn = trx[2];
			rsp_payload->optical_elmt_desc[0].low_warn = trx[3];
			rsp_payload->optical_elmt_desc[0].element_flags =
			    cpu_to_be32(1 << 28);

			/* Optical Element Descriptor, Voltage */
			rsp_payload->optical_elmt_desc[1].high_alarm = trx[4];
			rsp_payload->optical_elmt_desc[1].low_alarm = trx[5];
			rsp_payload->optical_elmt_desc[1].high_warn = trx[6];
			rsp_payload->optical_elmt_desc[1].low_warn = trx[7];
			rsp_payload->optical_elmt_desc[1].element_flags =
			    cpu_to_be32(2 << 28);

			/* Optical Element Descriptor, Tx Bias Current */
			rsp_payload->optical_elmt_desc[2].high_alarm = trx[8];
			rsp_payload->optical_elmt_desc[2].low_alarm = trx[9];
			rsp_payload->optical_elmt_desc[2].high_warn = trx[10];
			rsp_payload->optical_elmt_desc[2].low_warn = trx[11];
			rsp_payload->optical_elmt_desc[2].element_flags =
			    cpu_to_be32(3 << 28);

			/* Optical Element Descriptor, Tx Power */
			rsp_payload->optical_elmt_desc[3].high_alarm = trx[12];
			rsp_payload->optical_elmt_desc[3].low_alarm = trx[13];
			rsp_payload->optical_elmt_desc[3].high_warn = trx[14];
			rsp_payload->optical_elmt_desc[3].low_warn = trx[15];
			rsp_payload->optical_elmt_desc[3].element_flags =
			    cpu_to_be32(4 << 28);

			/* Optical Element Descriptor, Rx Power */
			rsp_payload->optical_elmt_desc[4].high_alarm = trx[16];
			rsp_payload->optical_elmt_desc[4].low_alarm = trx[17];
			rsp_payload->optical_elmt_desc[4].high_warn = trx[18];
			rsp_payload->optical_elmt_desc[4].low_warn = trx[19];
			rsp_payload->optical_elmt_desc[4].element_flags =
			    cpu_to_be32(5 << 28);
		पूर्ण

		स_रखो(sfp, 0, SFP_RTDI_LEN);
		rval = qla2x00_पढ़ो_sfp(vha, sfp_dma, sfp, 0xa2, 112, 64, 0);
		अगर (!rval) अणु
			/* Temperature high/low alarm/warning */
			rsp_payload->optical_elmt_desc[0].element_flags |=
			    cpu_to_be32(
				(sfp[0] >> 7 & 1) << 3 |
				(sfp[0] >> 6 & 1) << 2 |
				(sfp[4] >> 7 & 1) << 1 |
				(sfp[4] >> 6 & 1) << 0);

			/* Voltage high/low alarm/warning */
			rsp_payload->optical_elmt_desc[1].element_flags |=
			    cpu_to_be32(
				(sfp[0] >> 5 & 1) << 3 |
				(sfp[0] >> 4 & 1) << 2 |
				(sfp[4] >> 5 & 1) << 1 |
				(sfp[4] >> 4 & 1) << 0);

			/* Tx Bias Current high/low alarm/warning */
			rsp_payload->optical_elmt_desc[2].element_flags |=
			    cpu_to_be32(
				(sfp[0] >> 3 & 1) << 3 |
				(sfp[0] >> 2 & 1) << 2 |
				(sfp[4] >> 3 & 1) << 1 |
				(sfp[4] >> 2 & 1) << 0);

			/* Tx Power high/low alarm/warning */
			rsp_payload->optical_elmt_desc[3].element_flags |=
			    cpu_to_be32(
				(sfp[0] >> 1 & 1) << 3 |
				(sfp[0] >> 0 & 1) << 2 |
				(sfp[4] >> 1 & 1) << 1 |
				(sfp[4] >> 0 & 1) << 0);

			/* Rx Power high/low alarm/warning */
			rsp_payload->optical_elmt_desc[4].element_flags |=
			    cpu_to_be32(
				(sfp[1] >> 7 & 1) << 3 |
				(sfp[1] >> 6 & 1) << 2 |
				(sfp[5] >> 7 & 1) << 1 |
				(sfp[5] >> 6 & 1) << 0);
		पूर्ण
	पूर्ण

	/* Optical Product Data Descriptor */
	rsp_payload->optical_prod_desc.desc_tag = cpu_to_be32(0x10008);
	rsp_payload->optical_prod_desc.desc_len =
		cpu_to_be32(RDP_DESC_LEN(rsp_payload->optical_prod_desc));

	अगर (sfp) अणु
		स_रखो(sfp, 0, SFP_RTDI_LEN);
		rval = qla2x00_पढ़ो_sfp(vha, sfp_dma, sfp, 0xa0, 20, 64, 0);
		अगर (!rval) अणु
			स_नकल(rsp_payload->optical_prod_desc.venकरोr_name,
			    sfp + 0,
			    माप(rsp_payload->optical_prod_desc.venकरोr_name));
			स_नकल(rsp_payload->optical_prod_desc.part_number,
			    sfp + 20,
			    माप(rsp_payload->optical_prod_desc.part_number));
			स_नकल(rsp_payload->optical_prod_desc.revision,
			    sfp + 36,
			    माप(rsp_payload->optical_prod_desc.revision));
			स_नकल(rsp_payload->optical_prod_desc.serial_number,
			    sfp + 48,
			    माप(rsp_payload->optical_prod_desc.serial_number));
		पूर्ण

		स_रखो(sfp, 0, SFP_RTDI_LEN);
		rval = qla2x00_पढ़ो_sfp(vha, sfp_dma, sfp, 0xa0, 84, 8, 0);
		अगर (!rval) अणु
			स_नकल(rsp_payload->optical_prod_desc.date,
			    sfp + 0,
			    माप(rsp_payload->optical_prod_desc.date));
		पूर्ण
	पूर्ण

send:
	ql_dbg(ql_dbg_init, vha, 0x0183,
	    "Sending ELS Response to RDP Request...\n");
	ql_dbg(ql_dbg_init + ql_dbg_verbose, vha, 0x0184,
	    "-------- ELS RSP -------\n");
	ql_dump_buffer(ql_dbg_init + ql_dbg_verbose, vha, 0x0185,
	    rsp_els, माप(*rsp_els));
	ql_dbg(ql_dbg_init + ql_dbg_verbose, vha, 0x0186,
	    "-------- ELS RSP PAYLOAD -------\n");
	ql_dump_buffer(ql_dbg_init + ql_dbg_verbose, vha, 0x0187,
	    rsp_payload, rsp_payload_length);

	rval = qla2x00_issue_iocb(vha, rsp_els, rsp_els_dma, 0);

	अगर (rval) अणु
		ql_log(ql_log_warn, vha, 0x0188,
		    "%s: iocb failed to execute -> %x\n", __func__, rval);
	पूर्ण अन्यथा अगर (rsp_els->comp_status) अणु
		ql_log(ql_log_warn, vha, 0x0189,
		    "%s: iocb failed to complete -> completion=%#x subcode=(%#x,%#x)\n",
		    __func__, rsp_els->comp_status,
		    rsp_els->error_subcode_1, rsp_els->error_subcode_2);
	पूर्ण अन्यथा अणु
		ql_dbg(ql_dbg_init, vha, 0x018a, "%s: done.\n", __func__);
	पूर्ण

dealloc:
	अगर (stat)
		dma_मुक्त_coherent(&ha->pdev->dev, माप(*stat),
		    stat, stat_dma);
	अगर (sfp)
		dma_मुक्त_coherent(&ha->pdev->dev, SFP_RTDI_LEN,
		    sfp, sfp_dma);
	अगर (rsp_payload)
		dma_मुक्त_coherent(&ha->pdev->dev, माप(*rsp_payload),
		    rsp_payload, rsp_payload_dma);
	अगर (rsp_els)
		dma_मुक्त_coherent(&ha->pdev->dev, माप(*rsp_els),
		    rsp_els, rsp_els_dma);
पूर्ण

व्योम
qla24xx_मुक्त_purex_item(काष्ठा purex_item *item)
अणु
	अगर (item == &item->vha->शेष_item)
		स_रखो(&item->vha->शेष_item, 0, माप(काष्ठा purex_item));
	अन्यथा
		kमुक्त(item);
पूर्ण

व्योम qla24xx_process_purex_list(काष्ठा purex_list *list)
अणु
	काष्ठा list_head head = LIST_HEAD_INIT(head);
	काष्ठा purex_item *item, *next;
	uदीर्घ flags;

	spin_lock_irqsave(&list->lock, flags);
	list_splice_init(&list->head, &head);
	spin_unlock_irqrestore(&list->lock, flags);

	list_क्रम_each_entry_safe(item, next, &head, list) अणु
		list_del(&item->list);
		item->process_item(item->vha, item);
		qla24xx_मुक्त_purex_item(item);
	पूर्ण
पूर्ण

/*
 * Context: task, can sleep
 */
व्योम
qla83xx_idc_unlock(scsi_qla_host_t *base_vha, uपूर्णांक16_t requester_id)
अणु
#अगर 0
	uपूर्णांक16_t options = (requester_id << 15) | BIT_7;
#पूर्ण_अगर
	uपूर्णांक16_t retry;
	uपूर्णांक32_t data;
	काष्ठा qla_hw_data *ha = base_vha->hw;

	might_sleep();

	/* IDC-unlock implementation using driver-unlock/lock-id
	 * remote रेजिस्टरs
	 */
	retry = 0;
retry_unlock:
	अगर (qla83xx_rd_reg(base_vha, QLA83XX_DRIVER_LOCKID, &data)
	    == QLA_SUCCESS) अणु
		अगर (data == ha->portnum) अणु
			qla83xx_rd_reg(base_vha, QLA83XX_DRIVER_UNLOCK, &data);
			/* Clearing lock-id by setting 0xff */
			qla83xx_wr_reg(base_vha, QLA83XX_DRIVER_LOCKID, 0xff);
		पूर्ण अन्यथा अगर (retry < 10) अणु
			/* SV: XXX: IDC unlock retrying needed here? */

			/* Retry क्रम IDC-unlock */
			msleep(QLA83XX_WAIT_LOGIC_MS);
			retry++;
			ql_dbg(ql_dbg_p3p, base_vha, 0xb064,
			    "Failed to release IDC lock, retrying=%d\n", retry);
			जाओ retry_unlock;
		पूर्ण
	पूर्ण अन्यथा अगर (retry < 10) अणु
		/* Retry क्रम IDC-unlock */
		msleep(QLA83XX_WAIT_LOGIC_MS);
		retry++;
		ql_dbg(ql_dbg_p3p, base_vha, 0xb065,
		    "Failed to read drv-lockid, retrying=%d\n", retry);
		जाओ retry_unlock;
	पूर्ण

	वापस;

#अगर 0
	/* XXX: IDC-unlock implementation using access-control mbx */
	retry = 0;
retry_unlock2:
	अगर (qla83xx_access_control(base_vha, options, 0, 0, शून्य)) अणु
		अगर (retry < 10) अणु
			/* Retry क्रम IDC-unlock */
			msleep(QLA83XX_WAIT_LOGIC_MS);
			retry++;
			ql_dbg(ql_dbg_p3p, base_vha, 0xb066,
			    "Failed to release IDC lock, retrying=%d\n", retry);
			जाओ retry_unlock2;
		पूर्ण
	पूर्ण

	वापस;
#पूर्ण_अगर
पूर्ण

पूर्णांक
__qla83xx_set_drv_presence(scsi_qla_host_t *vha)
अणु
	पूर्णांक rval = QLA_SUCCESS;
	काष्ठा qla_hw_data *ha = vha->hw;
	uपूर्णांक32_t drv_presence;

	rval = qla83xx_rd_reg(vha, QLA83XX_IDC_DRV_PRESENCE, &drv_presence);
	अगर (rval == QLA_SUCCESS) अणु
		drv_presence |= (1 << ha->portnum);
		rval = qla83xx_wr_reg(vha, QLA83XX_IDC_DRV_PRESENCE,
		    drv_presence);
	पूर्ण

	वापस rval;
पूर्ण

पूर्णांक
qla83xx_set_drv_presence(scsi_qla_host_t *vha)
अणु
	पूर्णांक rval = QLA_SUCCESS;

	qla83xx_idc_lock(vha, 0);
	rval = __qla83xx_set_drv_presence(vha);
	qla83xx_idc_unlock(vha, 0);

	वापस rval;
पूर्ण

पूर्णांक
__qla83xx_clear_drv_presence(scsi_qla_host_t *vha)
अणु
	पूर्णांक rval = QLA_SUCCESS;
	काष्ठा qla_hw_data *ha = vha->hw;
	uपूर्णांक32_t drv_presence;

	rval = qla83xx_rd_reg(vha, QLA83XX_IDC_DRV_PRESENCE, &drv_presence);
	अगर (rval == QLA_SUCCESS) अणु
		drv_presence &= ~(1 << ha->portnum);
		rval = qla83xx_wr_reg(vha, QLA83XX_IDC_DRV_PRESENCE,
		    drv_presence);
	पूर्ण

	वापस rval;
पूर्ण

पूर्णांक
qla83xx_clear_drv_presence(scsi_qla_host_t *vha)
अणु
	पूर्णांक rval = QLA_SUCCESS;

	qla83xx_idc_lock(vha, 0);
	rval = __qla83xx_clear_drv_presence(vha);
	qla83xx_idc_unlock(vha, 0);

	वापस rval;
पूर्ण

अटल व्योम
qla83xx_need_reset_handler(scsi_qla_host_t *vha)
अणु
	काष्ठा qla_hw_data *ha = vha->hw;
	uपूर्णांक32_t drv_ack, drv_presence;
	अचिन्हित दीर्घ ack_समयout;

	/* Wait क्रम IDC ACK from all functions (DRV-ACK == DRV-PRESENCE) */
	ack_समयout = jअगरfies + (ha->fcoe_reset_समयout * HZ);
	जबतक (1) अणु
		qla83xx_rd_reg(vha, QLA83XX_IDC_DRIVER_ACK, &drv_ack);
		qla83xx_rd_reg(vha, QLA83XX_IDC_DRV_PRESENCE, &drv_presence);
		अगर ((drv_ack & drv_presence) == drv_presence)
			अवरोध;

		अगर (समय_after_eq(jअगरfies, ack_समयout)) अणु
			ql_log(ql_log_warn, vha, 0xb067,
			    "RESET ACK TIMEOUT! drv_presence=0x%x "
			    "drv_ack=0x%x\n", drv_presence, drv_ack);
			/*
			 * The function(s) which did not ack in समय are क्रमced
			 * to withdraw any further participation in the IDC
			 * reset.
			 */
			अगर (drv_ack != drv_presence)
				qla83xx_wr_reg(vha, QLA83XX_IDC_DRV_PRESENCE,
				    drv_ack);
			अवरोध;
		पूर्ण

		qla83xx_idc_unlock(vha, 0);
		msleep(1000);
		qla83xx_idc_lock(vha, 0);
	पूर्ण

	qla83xx_wr_reg(vha, QLA83XX_IDC_DEV_STATE, QLA8XXX_DEV_COLD);
	ql_log(ql_log_info, vha, 0xb068, "HW State: COLD/RE-INIT.\n");
पूर्ण

अटल पूर्णांक
qla83xx_device_bootstrap(scsi_qla_host_t *vha)
अणु
	पूर्णांक rval = QLA_SUCCESS;
	uपूर्णांक32_t idc_control;

	qla83xx_wr_reg(vha, QLA83XX_IDC_DEV_STATE, QLA8XXX_DEV_INITIALIZING);
	ql_log(ql_log_info, vha, 0xb069, "HW State: INITIALIZING.\n");

	/* Clearing IDC-Control Graceful-Reset Bit beक्रमe resetting f/w */
	__qla83xx_get_idc_control(vha, &idc_control);
	idc_control &= ~QLA83XX_IDC_GRACEFUL_RESET;
	__qla83xx_set_idc_control(vha, 0);

	qla83xx_idc_unlock(vha, 0);
	rval = qla83xx_restart_nic_firmware(vha);
	qla83xx_idc_lock(vha, 0);

	अगर (rval != QLA_SUCCESS) अणु
		ql_log(ql_log_fatal, vha, 0xb06a,
		    "Failed to restart NIC f/w.\n");
		qla83xx_wr_reg(vha, QLA83XX_IDC_DEV_STATE, QLA8XXX_DEV_FAILED);
		ql_log(ql_log_info, vha, 0xb06b, "HW State: FAILED.\n");
	पूर्ण अन्यथा अणु
		ql_dbg(ql_dbg_p3p, vha, 0xb06c,
		    "Success in restarting nic f/w.\n");
		qla83xx_wr_reg(vha, QLA83XX_IDC_DEV_STATE, QLA8XXX_DEV_READY);
		ql_log(ql_log_info, vha, 0xb06d, "HW State: READY.\n");
	पूर्ण

	वापस rval;
पूर्ण

/* Assumes idc_lock always held on entry */
पूर्णांक
qla83xx_idc_state_handler(scsi_qla_host_t *base_vha)
अणु
	काष्ठा qla_hw_data *ha = base_vha->hw;
	पूर्णांक rval = QLA_SUCCESS;
	अचिन्हित दीर्घ dev_init_समयout;
	uपूर्णांक32_t dev_state;

	/* Wait क्रम MAX-INIT-TIMEOUT क्रम the device to go पढ़ोy */
	dev_init_समयout = jअगरfies + (ha->fcoe_dev_init_समयout * HZ);

	जबतक (1) अणु

		अगर (समय_after_eq(jअगरfies, dev_init_समयout)) अणु
			ql_log(ql_log_warn, base_vha, 0xb06e,
			    "Initialization TIMEOUT!\n");
			/* Init समयout. Disable further NIC Core
			 * communication.
			 */
			qla83xx_wr_reg(base_vha, QLA83XX_IDC_DEV_STATE,
				QLA8XXX_DEV_FAILED);
			ql_log(ql_log_info, base_vha, 0xb06f,
			    "HW State: FAILED.\n");
		पूर्ण

		qla83xx_rd_reg(base_vha, QLA83XX_IDC_DEV_STATE, &dev_state);
		चयन (dev_state) अणु
		हाल QLA8XXX_DEV_READY:
			अगर (ha->flags.nic_core_reset_owner)
				qla83xx_idc_audit(base_vha,
				    IDC_AUDIT_COMPLETION);
			ha->flags.nic_core_reset_owner = 0;
			ql_dbg(ql_dbg_p3p, base_vha, 0xb070,
			    "Reset_owner reset by 0x%x.\n",
			    ha->portnum);
			जाओ निकास;
		हाल QLA8XXX_DEV_COLD:
			अगर (ha->flags.nic_core_reset_owner)
				rval = qla83xx_device_bootstrap(base_vha);
			अन्यथा अणु
			/* Wait क्रम AEN to change device-state */
				qla83xx_idc_unlock(base_vha, 0);
				msleep(1000);
				qla83xx_idc_lock(base_vha, 0);
			पूर्ण
			अवरोध;
		हाल QLA8XXX_DEV_INITIALIZING:
			/* Wait क्रम AEN to change device-state */
			qla83xx_idc_unlock(base_vha, 0);
			msleep(1000);
			qla83xx_idc_lock(base_vha, 0);
			अवरोध;
		हाल QLA8XXX_DEV_NEED_RESET:
			अगर (!ql2xकरोntresethba && ha->flags.nic_core_reset_owner)
				qla83xx_need_reset_handler(base_vha);
			अन्यथा अणु
				/* Wait क्रम AEN to change device-state */
				qla83xx_idc_unlock(base_vha, 0);
				msleep(1000);
				qla83xx_idc_lock(base_vha, 0);
			पूर्ण
			/* reset समयout value after need reset handler */
			dev_init_समयout = jअगरfies +
			    (ha->fcoe_dev_init_समयout * HZ);
			अवरोध;
		हाल QLA8XXX_DEV_NEED_QUIESCENT:
			/* XXX: DEBUG क्रम now */
			qla83xx_idc_unlock(base_vha, 0);
			msleep(1000);
			qla83xx_idc_lock(base_vha, 0);
			अवरोध;
		हाल QLA8XXX_DEV_QUIESCENT:
			/* XXX: DEBUG क्रम now */
			अगर (ha->flags.quiesce_owner)
				जाओ निकास;

			qla83xx_idc_unlock(base_vha, 0);
			msleep(1000);
			qla83xx_idc_lock(base_vha, 0);
			dev_init_समयout = jअगरfies +
			    (ha->fcoe_dev_init_समयout * HZ);
			अवरोध;
		हाल QLA8XXX_DEV_FAILED:
			अगर (ha->flags.nic_core_reset_owner)
				qla83xx_idc_audit(base_vha,
				    IDC_AUDIT_COMPLETION);
			ha->flags.nic_core_reset_owner = 0;
			__qla83xx_clear_drv_presence(base_vha);
			qla83xx_idc_unlock(base_vha, 0);
			qla8xxx_dev_failed_handler(base_vha);
			rval = QLA_FUNCTION_FAILED;
			qla83xx_idc_lock(base_vha, 0);
			जाओ निकास;
		हाल QLA8XXX_BAD_VALUE:
			qla83xx_idc_unlock(base_vha, 0);
			msleep(1000);
			qla83xx_idc_lock(base_vha, 0);
			अवरोध;
		शेष:
			ql_log(ql_log_warn, base_vha, 0xb071,
			    "Unknown Device State: %x.\n", dev_state);
			qla83xx_idc_unlock(base_vha, 0);
			qla8xxx_dev_failed_handler(base_vha);
			rval = QLA_FUNCTION_FAILED;
			qla83xx_idc_lock(base_vha, 0);
			जाओ निकास;
		पूर्ण
	पूर्ण

निकास:
	वापस rval;
पूर्ण

व्योम
qla2x00_disable_board_on_pci_error(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा qla_hw_data *ha = container_of(work, काष्ठा qla_hw_data,
	    board_disable);
	काष्ठा pci_dev *pdev = ha->pdev;
	scsi_qla_host_t *base_vha = pci_get_drvdata(ha->pdev);

	ql_log(ql_log_warn, base_vha, 0x015b,
	    "Disabling adapter.\n");

	अगर (!atomic_पढ़ो(&pdev->enable_cnt)) अणु
		ql_log(ql_log_info, base_vha, 0xfffc,
		    "PCI device disabled, no action req for PCI error=%lx\n",
		    base_vha->pci_flags);
		वापस;
	पूर्ण

	/*
	 * अगर UNLOADING flag is alपढ़ोy set, then जारी unload,
	 * where it was set first.
	 */
	अगर (test_and_set_bit(UNLOADING, &base_vha->dpc_flags))
		वापस;

	qla2x00_रुको_क्रम_sess_deletion(base_vha);

	qla2x00_delete_all_vps(ha, base_vha);

	qla2x00_पात_all_cmds(base_vha, DID_NO_CONNECT << 16);

	qla2x00_dfs_हटाओ(base_vha);

	qla84xx_put_chip(base_vha);

	अगर (base_vha->समयr_active)
		qla2x00_stop_समयr(base_vha);

	base_vha->flags.online = 0;

	qla2x00_destroy_deferred_work(ha);

	/*
	 * Do not try to stop beacon blink as it will issue a mailbox
	 * command.
	 */
	qla2x00_मुक्त_sysfs_attr(base_vha, false);

	fc_हटाओ_host(base_vha->host);

	scsi_हटाओ_host(base_vha->host);

	base_vha->flags.init_करोne = 0;
	qla25xx_delete_queues(base_vha);
	qla2x00_मुक्त_fcports(base_vha);
	qla2x00_मुक्त_irqs(base_vha);
	qla2x00_mem_मुक्त(ha);
	qla82xx_md_मुक्त(base_vha);
	qla2x00_मुक्त_queues(ha);

	qla2x00_unmap_iobases(ha);

	pci_release_selected_regions(ha->pdev, ha->bars);
	pci_disable_pcie_error_reporting(pdev);
	pci_disable_device(pdev);

	/*
	 * Let qla2x00_हटाओ_one cleanup qla_hw_data on device removal.
	 */
पूर्ण

/**************************************************************************
* qla2x00_करो_dpc
*   This kernel thपढ़ो is a task that is schedule by the पूर्णांकerrupt handler
*   to perक्रमm the background processing क्रम पूर्णांकerrupts.
*
* Notes:
* This task always run in the context of a kernel thपढ़ो.  It
* is kick-off by the driver's detect code and starts up
* up one per adapter. It immediately goes to sleep and रुकोs क्रम
* some fibre event.  When either the पूर्णांकerrupt handler or
* the समयr routine detects a event it will one of the task
* bits then wake us up.
**************************************************************************/
अटल पूर्णांक
qla2x00_करो_dpc(व्योम *data)
अणु
	scsi_qla_host_t *base_vha;
	काष्ठा qla_hw_data *ha;
	uपूर्णांक32_t online;
	काष्ठा qla_qpair *qpair;

	ha = (काष्ठा qla_hw_data *)data;
	base_vha = pci_get_drvdata(ha->pdev);

	set_user_nice(current, MIN_NICE);

	set_current_state(TASK_INTERRUPTIBLE);
	जबतक (!kthपढ़ो_should_stop()) अणु
		ql_dbg(ql_dbg_dpc, base_vha, 0x4000,
		    "DPC handler sleeping.\n");

		schedule();

		अगर (test_and_clear_bit(DO_EEH_RECOVERY, &base_vha->dpc_flags))
			qla_pci_set_eeh_busy(base_vha);

		अगर (!base_vha->flags.init_करोne || ha->flags.mbox_busy)
			जाओ end_loop;

		अगर (ha->flags.eeh_busy) अणु
			ql_dbg(ql_dbg_dpc, base_vha, 0x4003,
			    "eeh_busy=%d.\n", ha->flags.eeh_busy);
			जाओ end_loop;
		पूर्ण

		ha->dpc_active = 1;

		ql_dbg(ql_dbg_dpc + ql_dbg_verbose, base_vha, 0x4001,
		    "DPC handler waking up, dpc_flags=0x%lx.\n",
		    base_vha->dpc_flags);

		अगर (test_bit(UNLOADING, &base_vha->dpc_flags))
			अवरोध;

		अगर (IS_P3P_TYPE(ha)) अणु
			अगर (IS_QLA8044(ha)) अणु
				अगर (test_and_clear_bit(ISP_UNRECOVERABLE,
					&base_vha->dpc_flags)) अणु
					qla8044_idc_lock(ha);
					qla8044_wr_direct(base_vha,
						QLA8044_CRB_DEV_STATE_INDEX,
						QLA8XXX_DEV_FAILED);
					qla8044_idc_unlock(ha);
					ql_log(ql_log_info, base_vha, 0x4004,
						"HW State: FAILED.\n");
					qla8044_device_state_handler(base_vha);
					जारी;
				पूर्ण

			पूर्ण अन्यथा अणु
				अगर (test_and_clear_bit(ISP_UNRECOVERABLE,
					&base_vha->dpc_flags)) अणु
					qla82xx_idc_lock(ha);
					qla82xx_wr_32(ha, QLA82XX_CRB_DEV_STATE,
						QLA8XXX_DEV_FAILED);
					qla82xx_idc_unlock(ha);
					ql_log(ql_log_info, base_vha, 0x0151,
						"HW State: FAILED.\n");
					qla82xx_device_state_handler(base_vha);
					जारी;
				पूर्ण
			पूर्ण

			अगर (test_and_clear_bit(FCOE_CTX_RESET_NEEDED,
				&base_vha->dpc_flags)) अणु

				ql_dbg(ql_dbg_dpc, base_vha, 0x4005,
				    "FCoE context reset scheduled.\n");
				अगर (!(test_and_set_bit(ABORT_ISP_ACTIVE,
					&base_vha->dpc_flags))) अणु
					अगर (qla82xx_fcoe_ctx_reset(base_vha)) अणु
						/* FCoE-ctx reset failed.
						 * Escalate to chip-reset
						 */
						set_bit(ISP_ABORT_NEEDED,
							&base_vha->dpc_flags);
					पूर्ण
					clear_bit(ABORT_ISP_ACTIVE,
						&base_vha->dpc_flags);
				पूर्ण

				ql_dbg(ql_dbg_dpc, base_vha, 0x4006,
				    "FCoE context reset end.\n");
			पूर्ण
		पूर्ण अन्यथा अगर (IS_QLAFX00(ha)) अणु
			अगर (test_and_clear_bit(ISP_UNRECOVERABLE,
				&base_vha->dpc_flags)) अणु
				ql_dbg(ql_dbg_dpc, base_vha, 0x4020,
				    "Firmware Reset Recovery\n");
				अगर (qlafx00_reset_initialize(base_vha)) अणु
					/* Failed. Abort isp later. */
					अगर (!test_bit(UNLOADING,
					    &base_vha->dpc_flags)) अणु
						set_bit(ISP_UNRECOVERABLE,
						    &base_vha->dpc_flags);
						ql_dbg(ql_dbg_dpc, base_vha,
						    0x4021,
						    "Reset Recovery Failed\n");
					पूर्ण
				पूर्ण
			पूर्ण

			अगर (test_and_clear_bit(FX00_TARGET_SCAN,
				&base_vha->dpc_flags)) अणु
				ql_dbg(ql_dbg_dpc, base_vha, 0x4022,
				    "ISPFx00 Target Scan scheduled\n");
				अगर (qlafx00_rescan_isp(base_vha)) अणु
					अगर (!test_bit(UNLOADING,
					    &base_vha->dpc_flags))
						set_bit(ISP_UNRECOVERABLE,
						    &base_vha->dpc_flags);
					ql_dbg(ql_dbg_dpc, base_vha, 0x401e,
					    "ISPFx00 Target Scan Failed\n");
				पूर्ण
				ql_dbg(ql_dbg_dpc, base_vha, 0x401f,
				    "ISPFx00 Target Scan End\n");
			पूर्ण
			अगर (test_and_clear_bit(FX00_HOST_INFO_RESEND,
				&base_vha->dpc_flags)) अणु
				ql_dbg(ql_dbg_dpc, base_vha, 0x4023,
				    "ISPFx00 Host Info resend scheduled\n");
				qlafx00_fx_disc(base_vha,
				    &base_vha->hw->mr.fcport,
				    FXDISC_REG_HOST_INFO);
			पूर्ण
		पूर्ण

		अगर (test_and_clear_bit(DETECT_SFP_CHANGE,
		    &base_vha->dpc_flags)) अणु
			/* Semantic:
			 *  - NO-OP -- aरुको next ISP-ABORT. Preferred method
			 *             to minimize disruptions that will occur
			 *             when a क्रमced chip-reset occurs.
			 *  - Force -- ISP-ABORT scheduled.
			 */
			/* set_bit(ISP_ABORT_NEEDED, &base_vha->dpc_flags); */
		पूर्ण

		अगर (test_and_clear_bit
		    (ISP_ABORT_NEEDED, &base_vha->dpc_flags) &&
		    !test_bit(UNLOADING, &base_vha->dpc_flags)) अणु
			bool करो_reset = true;

			चयन (base_vha->qlini_mode) अणु
			हाल QLA2XXX_INI_MODE_ENABLED:
				अवरोध;
			हाल QLA2XXX_INI_MODE_DISABLED:
				अगर (!qla_tgt_mode_enabled(base_vha) &&
				    !ha->flags.fw_started)
					करो_reset = false;
				अवरोध;
			हाल QLA2XXX_INI_MODE_DUAL:
				अगर (!qla_dual_mode_enabled(base_vha) &&
				    !ha->flags.fw_started)
					करो_reset = false;
				अवरोध;
			शेष:
				अवरोध;
			पूर्ण

			अगर (करो_reset && !(test_and_set_bit(ABORT_ISP_ACTIVE,
			    &base_vha->dpc_flags))) अणु
				base_vha->flags.online = 1;
				ql_dbg(ql_dbg_dpc, base_vha, 0x4007,
				    "ISP abort scheduled.\n");
				अगर (ha->isp_ops->पात_isp(base_vha)) अणु
					/* failed. retry later */
					set_bit(ISP_ABORT_NEEDED,
					    &base_vha->dpc_flags);
				पूर्ण
				clear_bit(ABORT_ISP_ACTIVE,
						&base_vha->dpc_flags);
				ql_dbg(ql_dbg_dpc, base_vha, 0x4008,
				    "ISP abort end.\n");
			पूर्ण
		पूर्ण

		अगर (test_bit(PROCESS_PUREX_IOCB, &base_vha->dpc_flags)) अणु
			अगर (atomic_पढ़ो(&base_vha->loop_state) == LOOP_READY) अणु
				qla24xx_process_purex_list
					(&base_vha->purex_list);
				clear_bit(PROCESS_PUREX_IOCB,
				    &base_vha->dpc_flags);
			पूर्ण
		पूर्ण

		अगर (test_and_clear_bit(FCPORT_UPDATE_NEEDED,
		    &base_vha->dpc_flags)) अणु
			qla2x00_update_fcports(base_vha);
		पूर्ण

		अगर (IS_QLAFX00(ha))
			जाओ loop_resync_check;

		अगर (test_bit(ISP_QUIESCE_NEEDED, &base_vha->dpc_flags)) अणु
			ql_dbg(ql_dbg_dpc, base_vha, 0x4009,
			    "Quiescence mode scheduled.\n");
			अगर (IS_P3P_TYPE(ha)) अणु
				अगर (IS_QLA82XX(ha))
					qla82xx_device_state_handler(base_vha);
				अगर (IS_QLA8044(ha))
					qla8044_device_state_handler(base_vha);
				clear_bit(ISP_QUIESCE_NEEDED,
				    &base_vha->dpc_flags);
				अगर (!ha->flags.quiesce_owner) अणु
					qla2x00_perक्रमm_loop_resync(base_vha);
					अगर (IS_QLA82XX(ha)) अणु
						qla82xx_idc_lock(ha);
						qla82xx_clear_qsnt_पढ़ोy(
						    base_vha);
						qla82xx_idc_unlock(ha);
					पूर्ण अन्यथा अगर (IS_QLA8044(ha)) अणु
						qla8044_idc_lock(ha);
						qla8044_clear_qsnt_पढ़ोy(
						    base_vha);
						qla8044_idc_unlock(ha);
					पूर्ण
				पूर्ण
			पूर्ण अन्यथा अणु
				clear_bit(ISP_QUIESCE_NEEDED,
				    &base_vha->dpc_flags);
				qla2x00_quiesce_io(base_vha);
			पूर्ण
			ql_dbg(ql_dbg_dpc, base_vha, 0x400a,
			    "Quiescence mode end.\n");
		पूर्ण

		अगर (test_and_clear_bit(RESET_MARKER_NEEDED,
				&base_vha->dpc_flags) &&
		    (!(test_and_set_bit(RESET_ACTIVE, &base_vha->dpc_flags)))) अणु

			ql_dbg(ql_dbg_dpc, base_vha, 0x400b,
			    "Reset marker scheduled.\n");
			qla2x00_rst_aen(base_vha);
			clear_bit(RESET_ACTIVE, &base_vha->dpc_flags);
			ql_dbg(ql_dbg_dpc, base_vha, 0x400c,
			    "Reset marker end.\n");
		पूर्ण

		/* Retry each device up to login retry count */
		अगर (test_bit(RELOGIN_NEEDED, &base_vha->dpc_flags) &&
		    !test_bit(LOOP_RESYNC_NEEDED, &base_vha->dpc_flags) &&
		    atomic_पढ़ो(&base_vha->loop_state) != LOOP_DOWN) अणु

			अगर (!base_vha->relogin_jअगर ||
			    समय_after_eq(jअगरfies, base_vha->relogin_jअगर)) अणु
				base_vha->relogin_jअगर = jअगरfies + HZ;
				clear_bit(RELOGIN_NEEDED, &base_vha->dpc_flags);

				ql_dbg(ql_dbg_disc, base_vha, 0x400d,
				    "Relogin scheduled.\n");
				qla24xx_post_relogin_work(base_vha);
			पूर्ण
		पूर्ण
loop_resync_check:
		अगर (test_and_clear_bit(LOOP_RESYNC_NEEDED,
		    &base_vha->dpc_flags)) अणु

			ql_dbg(ql_dbg_dpc, base_vha, 0x400f,
			    "Loop resync scheduled.\n");

			अगर (!(test_and_set_bit(LOOP_RESYNC_ACTIVE,
			    &base_vha->dpc_flags))) अणु

				qla2x00_loop_resync(base_vha);

				clear_bit(LOOP_RESYNC_ACTIVE,
						&base_vha->dpc_flags);
			पूर्ण

			ql_dbg(ql_dbg_dpc, base_vha, 0x4010,
			    "Loop resync end.\n");
		पूर्ण

		अगर (IS_QLAFX00(ha))
			जाओ पूर्णांकr_on_check;

		अगर (test_bit(NPIV_CONFIG_NEEDED, &base_vha->dpc_flags) &&
		    atomic_पढ़ो(&base_vha->loop_state) == LOOP_READY) अणु
			clear_bit(NPIV_CONFIG_NEEDED, &base_vha->dpc_flags);
			qla2xxx_flash_npiv_conf(base_vha);
		पूर्ण

पूर्णांकr_on_check:
		अगर (!ha->पूर्णांकerrupts_on)
			ha->isp_ops->enable_पूर्णांकrs(ha);

		अगर (test_and_clear_bit(BEACON_BLINK_NEEDED,
					&base_vha->dpc_flags)) अणु
			अगर (ha->beacon_blink_led == 1)
				ha->isp_ops->beacon_blink(base_vha);
		पूर्ण

		/* qpair online check */
		अगर (test_and_clear_bit(QPAIR_ONLINE_CHECK_NEEDED,
		    &base_vha->dpc_flags)) अणु
			अगर (ha->flags.eeh_busy ||
			    ha->flags.pci_channel_io_perm_failure)
				online = 0;
			अन्यथा
				online = 1;

			mutex_lock(&ha->mq_lock);
			list_क्रम_each_entry(qpair, &base_vha->qp_list,
			    qp_list_elem)
			qpair->online = online;
			mutex_unlock(&ha->mq_lock);
		पूर्ण

		अगर (test_and_clear_bit(SET_ZIO_THRESHOLD_NEEDED,
				       &base_vha->dpc_flags)) अणु
			u16 threshold = ha->nvme_last_rptd_aen + ha->last_zio_threshold;

			अगर (threshold > ha->orig_fw_xcb_count)
				threshold = ha->orig_fw_xcb_count;

			ql_log(ql_log_info, base_vha, 0xffffff,
			       "SET ZIO Activity exchange threshold to %d.\n",
			       threshold);
			अगर (qla27xx_set_zio_threshold(base_vha, threshold)) अणु
				ql_log(ql_log_info, base_vha, 0xffffff,
				       "Unable to SET ZIO Activity exchange threshold to %d.\n",
				       threshold);
			पूर्ण
		पूर्ण

		अगर (!IS_QLAFX00(ha))
			qla2x00_करो_dpc_all_vps(base_vha);

		अगर (test_and_clear_bit(N2N_LINK_RESET,
			&base_vha->dpc_flags)) अणु
			qla2x00_lip_reset(base_vha);
		पूर्ण

		ha->dpc_active = 0;
end_loop:
		set_current_state(TASK_INTERRUPTIBLE);
	पूर्ण /* End of जबतक(1) */
	__set_current_state(TASK_RUNNING);

	ql_dbg(ql_dbg_dpc, base_vha, 0x4011,
	    "DPC handler exiting.\n");

	/*
	 * Make sure that nobody tries to wake us up again.
	 */
	ha->dpc_active = 0;

	/* Cleanup any residual CTX SRBs. */
	qla2x00_पात_all_cmds(base_vha, DID_NO_CONNECT << 16);

	वापस 0;
पूर्ण

व्योम
qla2xxx_wake_dpc(काष्ठा scsi_qla_host *vha)
अणु
	काष्ठा qla_hw_data *ha = vha->hw;
	काष्ठा task_काष्ठा *t = ha->dpc_thपढ़ो;

	अगर (!test_bit(UNLOADING, &vha->dpc_flags) && t)
		wake_up_process(t);
पूर्ण

/*
*  qla2x00_rst_aen
*      Processes asynchronous reset.
*
* Input:
*      ha  = adapter block poपूर्णांकer.
*/
अटल व्योम
qla2x00_rst_aen(scsi_qla_host_t *vha)
अणु
	अगर (vha->flags.online && !vha->flags.reset_active &&
	    !atomic_पढ़ो(&vha->loop_करोwn_समयr) &&
	    !(test_bit(ABORT_ISP_ACTIVE, &vha->dpc_flags))) अणु
		करो अणु
			clear_bit(RESET_MARKER_NEEDED, &vha->dpc_flags);

			/*
			 * Issue marker command only when we are going to start
			 * the I/O.
			 */
			vha->marker_needed = 1;
		पूर्ण जबतक (!atomic_पढ़ो(&vha->loop_करोwn_समयr) &&
		    (test_bit(RESET_MARKER_NEEDED, &vha->dpc_flags)));
	पूर्ण
पूर्ण

/**************************************************************************
*   qla2x00_समयr
*
* Description:
*   One second समयr
*
* Context: Interrupt
***************************************************************************/
व्योम
qla2x00_समयr(काष्ठा समयr_list *t)
अणु
	scsi_qla_host_t *vha = from_समयr(vha, t, समयr);
	अचिन्हित दीर्घ	cpu_flags = 0;
	पूर्णांक		start_dpc = 0;
	पूर्णांक		index;
	srb_t		*sp;
	uपूर्णांक16_t        w;
	काष्ठा qla_hw_data *ha = vha->hw;
	काष्ठा req_que *req;
	अचिन्हित दीर्घ flags;
	fc_port_t *fcport = शून्य;

	अगर (ha->flags.eeh_busy) अणु
		ql_dbg(ql_dbg_समयr, vha, 0x6000,
		    "EEH = %d, restarting timer.\n",
		    ha->flags.eeh_busy);
		qla2x00_restart_समयr(vha, WATCH_INTERVAL);
		वापस;
	पूर्ण

	/*
	 * Hardware पढ़ो to उठाओ pending EEH errors during mailbox रुकोs. If
	 * the पढ़ो वापसs -1 then disable the board.
	 */
	अगर (!pci_channel_offline(ha->pdev)) अणु
		pci_पढ़ो_config_word(ha->pdev, PCI_VENDOR_ID, &w);
		qla2x00_check_reg16_क्रम_disconnect(vha, w);
	पूर्ण

	/* Make sure qla82xx_watchकरोg is run only क्रम physical port */
	अगर (!vha->vp_idx && IS_P3P_TYPE(ha)) अणु
		अगर (test_bit(ISP_QUIESCE_NEEDED, &vha->dpc_flags))
			start_dpc++;
		अगर (IS_QLA82XX(ha))
			qla82xx_watchकरोg(vha);
		अन्यथा अगर (IS_QLA8044(ha))
			qla8044_watchकरोg(vha);
	पूर्ण

	अगर (!vha->vp_idx && IS_QLAFX00(ha))
		qlafx00_समयr_routine(vha);

	अगर (vha->link_करोwn_समय < QLA2XX_MAX_LINK_DOWN_TIME)
		vha->link_करोwn_समय++;

	spin_lock_irqsave(&vha->hw->tgt.sess_lock, flags);
	list_क्रम_each_entry(fcport, &vha->vp_fcports, list) अणु
		अगर (fcport->tgt_link_करोwn_समय < QLA2XX_MAX_LINK_DOWN_TIME)
			fcport->tgt_link_करोwn_समय++;
	पूर्ण
	spin_unlock_irqrestore(&vha->hw->tgt.sess_lock, flags);

	/* Loop करोwn handler. */
	अगर (atomic_पढ़ो(&vha->loop_करोwn_समयr) > 0 &&
	    !(test_bit(ABORT_ISP_ACTIVE, &vha->dpc_flags)) &&
	    !(test_bit(FCOE_CTX_RESET_NEEDED, &vha->dpc_flags))
		&& vha->flags.online) अणु

		अगर (atomic_पढ़ो(&vha->loop_करोwn_समयr) ==
		    vha->loop_करोwn_पात_समय) अणु

			ql_log(ql_log_info, vha, 0x6008,
			    "Loop down - aborting the queues before time expires.\n");

			अगर (!IS_QLA2100(ha) && vha->link_करोwn_समयout)
				atomic_set(&vha->loop_state, LOOP_DEAD);

			/*
			 * Schedule an ISP पात to वापस any FCP2-device
			 * commands.
			 */
			/* NPIV - scan physical port only */
			अगर (!vha->vp_idx) अणु
				spin_lock_irqsave(&ha->hardware_lock,
				    cpu_flags);
				req = ha->req_q_map[0];
				क्रम (index = 1;
				    index < req->num_outstanding_cmds;
				    index++) अणु
					fc_port_t *sfcp;

					sp = req->outstanding_cmds[index];
					अगर (!sp)
						जारी;
					अगर (sp->cmd_type != TYPE_SRB)
						जारी;
					अगर (sp->type != SRB_SCSI_CMD)
						जारी;
					sfcp = sp->fcport;
					अगर (!(sfcp->flags & FCF_FCP2_DEVICE))
						जारी;

					अगर (IS_QLA82XX(ha))
						set_bit(FCOE_CTX_RESET_NEEDED,
							&vha->dpc_flags);
					अन्यथा
						set_bit(ISP_ABORT_NEEDED,
							&vha->dpc_flags);
					अवरोध;
				पूर्ण
				spin_unlock_irqrestore(&ha->hardware_lock,
								cpu_flags);
			पूर्ण
			start_dpc++;
		पूर्ण

		/* अगर the loop has been करोwn क्रम 4 minutes, reinit adapter */
		अगर (atomic_dec_and_test(&vha->loop_करोwn_समयr) != 0) अणु
			अगर (!(vha->device_flags & DFLG_NO_CABLE)) अणु
				ql_log(ql_log_warn, vha, 0x6009,
				    "Loop down - aborting ISP.\n");

				अगर (IS_QLA82XX(ha))
					set_bit(FCOE_CTX_RESET_NEEDED,
						&vha->dpc_flags);
				अन्यथा
					set_bit(ISP_ABORT_NEEDED,
						&vha->dpc_flags);
			पूर्ण
		पूर्ण
		ql_dbg(ql_dbg_समयr, vha, 0x600a,
		    "Loop down - seconds remaining %d.\n",
		    atomic_पढ़ो(&vha->loop_करोwn_समयr));
	पूर्ण
	/* Check अगर beacon LED needs to be blinked क्रम physical host only */
	अगर (!vha->vp_idx && (ha->beacon_blink_led == 1)) अणु
		/* There is no beacon_blink function क्रम ISP82xx */
		अगर (!IS_P3P_TYPE(ha)) अणु
			set_bit(BEACON_BLINK_NEEDED, &vha->dpc_flags);
			start_dpc++;
		पूर्ण
	पूर्ण

	/* Process any deferred work. */
	अगर (!list_empty(&vha->work_list)) अणु
		अचिन्हित दीर्घ flags;
		bool q = false;

		spin_lock_irqsave(&vha->work_lock, flags);
		अगर (!test_and_set_bit(IOCB_WORK_ACTIVE, &vha->dpc_flags))
			q = true;
		spin_unlock_irqrestore(&vha->work_lock, flags);
		अगर (q)
			queue_work(vha->hw->wq, &vha->iocb_work);
	पूर्ण

	/*
	 * FC-NVME
	 * see अगर the active AEN count has changed from what was last reported.
	 */
	index = atomic_पढ़ो(&ha->nvme_active_aen_cnt);
	अगर (!vha->vp_idx &&
	    (index != ha->nvme_last_rptd_aen) &&
	    ha->zio_mode == QLA_ZIO_MODE_6 &&
	    !ha->flags.host_shutting_करोwn) अणु
		ha->nvme_last_rptd_aen = atomic_पढ़ो(&ha->nvme_active_aen_cnt);
		ql_log(ql_log_info, vha, 0x3002,
		    "nvme: Sched: Set ZIO exchange threshold to %d.\n",
		    ha->nvme_last_rptd_aen);
		set_bit(SET_ZIO_THRESHOLD_NEEDED, &vha->dpc_flags);
		start_dpc++;
	पूर्ण

	अगर (!vha->vp_idx &&
	    atomic_पढ़ो(&ha->zio_threshold) != ha->last_zio_threshold &&
	    IS_ZIO_THRESHOLD_CAPABLE(ha)) अणु
		ql_log(ql_log_info, vha, 0x3002,
		    "Sched: Set ZIO exchange threshold to %d.\n",
		    ha->last_zio_threshold);
		ha->last_zio_threshold = atomic_पढ़ो(&ha->zio_threshold);
		set_bit(SET_ZIO_THRESHOLD_NEEDED, &vha->dpc_flags);
		start_dpc++;
	पूर्ण

	/* Schedule the DPC routine अगर needed */
	अगर ((test_bit(ISP_ABORT_NEEDED, &vha->dpc_flags) ||
	    test_bit(LOOP_RESYNC_NEEDED, &vha->dpc_flags) ||
	    test_bit(FCPORT_UPDATE_NEEDED, &vha->dpc_flags) ||
	    start_dpc ||
	    test_bit(RESET_MARKER_NEEDED, &vha->dpc_flags) ||
	    test_bit(BEACON_BLINK_NEEDED, &vha->dpc_flags) ||
	    test_bit(ISP_UNRECOVERABLE, &vha->dpc_flags) ||
	    test_bit(FCOE_CTX_RESET_NEEDED, &vha->dpc_flags) ||
	    test_bit(VP_DPC_NEEDED, &vha->dpc_flags) ||
	    test_bit(RELOGIN_NEEDED, &vha->dpc_flags) ||
	    test_bit(PROCESS_PUREX_IOCB, &vha->dpc_flags))) अणु
		ql_dbg(ql_dbg_समयr, vha, 0x600b,
		    "isp_abort_needed=%d loop_resync_needed=%d "
		    "fcport_update_needed=%d start_dpc=%d "
		    "reset_marker_needed=%d",
		    test_bit(ISP_ABORT_NEEDED, &vha->dpc_flags),
		    test_bit(LOOP_RESYNC_NEEDED, &vha->dpc_flags),
		    test_bit(FCPORT_UPDATE_NEEDED, &vha->dpc_flags),
		    start_dpc,
		    test_bit(RESET_MARKER_NEEDED, &vha->dpc_flags));
		ql_dbg(ql_dbg_समयr, vha, 0x600c,
		    "beacon_blink_needed=%d isp_unrecoverable=%d "
		    "fcoe_ctx_reset_needed=%d vp_dpc_needed=%d "
		    "relogin_needed=%d, Process_purex_iocb=%d.\n",
		    test_bit(BEACON_BLINK_NEEDED, &vha->dpc_flags),
		    test_bit(ISP_UNRECOVERABLE, &vha->dpc_flags),
		    test_bit(FCOE_CTX_RESET_NEEDED, &vha->dpc_flags),
		    test_bit(VP_DPC_NEEDED, &vha->dpc_flags),
		    test_bit(RELOGIN_NEEDED, &vha->dpc_flags),
		    test_bit(PROCESS_PUREX_IOCB, &vha->dpc_flags));
		qla2xxx_wake_dpc(vha);
	पूर्ण

	qla2x00_restart_समयr(vha, WATCH_INTERVAL);
पूर्ण

/* Firmware पूर्णांकerface routines. */

#घोषणा FW_ISP21XX	0
#घोषणा FW_ISP22XX	1
#घोषणा FW_ISP2300	2
#घोषणा FW_ISP2322	3
#घोषणा FW_ISP24XX	4
#घोषणा FW_ISP25XX	5
#घोषणा FW_ISP81XX	6
#घोषणा FW_ISP82XX	7
#घोषणा FW_ISP2031	8
#घोषणा FW_ISP8031	9
#घोषणा FW_ISP27XX	10
#घोषणा FW_ISP28XX	11

#घोषणा FW_खाता_ISP21XX	"ql2100_fw.bin"
#घोषणा FW_खाता_ISP22XX	"ql2200_fw.bin"
#घोषणा FW_खाता_ISP2300	"ql2300_fw.bin"
#घोषणा FW_खाता_ISP2322	"ql2322_fw.bin"
#घोषणा FW_खाता_ISP24XX	"ql2400_fw.bin"
#घोषणा FW_खाता_ISP25XX	"ql2500_fw.bin"
#घोषणा FW_खाता_ISP81XX	"ql8100_fw.bin"
#घोषणा FW_खाता_ISP82XX	"ql8200_fw.bin"
#घोषणा FW_खाता_ISP2031	"ql2600_fw.bin"
#घोषणा FW_खाता_ISP8031	"ql8300_fw.bin"
#घोषणा FW_खाता_ISP27XX	"ql2700_fw.bin"
#घोषणा FW_खाता_ISP28XX	"ql2800_fw.bin"


अटल DEFINE_MUTEX(qla_fw_lock);

अटल काष्ठा fw_blob qla_fw_blobs[] = अणु
	अणु .name = FW_खाता_ISP21XX, .segs = अणु 0x1000, 0 पूर्ण, पूर्ण,
	अणु .name = FW_खाता_ISP22XX, .segs = अणु 0x1000, 0 पूर्ण, पूर्ण,
	अणु .name = FW_खाता_ISP2300, .segs = अणु 0x800, 0 पूर्ण, पूर्ण,
	अणु .name = FW_खाता_ISP2322, .segs = अणु 0x800, 0x1c000, 0x1e000, 0 पूर्ण, पूर्ण,
	अणु .name = FW_खाता_ISP24XX, पूर्ण,
	अणु .name = FW_खाता_ISP25XX, पूर्ण,
	अणु .name = FW_खाता_ISP81XX, पूर्ण,
	अणु .name = FW_खाता_ISP82XX, पूर्ण,
	अणु .name = FW_खाता_ISP2031, पूर्ण,
	अणु .name = FW_खाता_ISP8031, पूर्ण,
	अणु .name = FW_खाता_ISP27XX, पूर्ण,
	अणु .name = FW_खाता_ISP28XX, पूर्ण,
	अणु .name = शून्य, पूर्ण,
पूर्ण;

काष्ठा fw_blob *
qla2x00_request_firmware(scsi_qla_host_t *vha)
अणु
	काष्ठा qla_hw_data *ha = vha->hw;
	काष्ठा fw_blob *blob;

	अगर (IS_QLA2100(ha)) अणु
		blob = &qla_fw_blobs[FW_ISP21XX];
	पूर्ण अन्यथा अगर (IS_QLA2200(ha)) अणु
		blob = &qla_fw_blobs[FW_ISP22XX];
	पूर्ण अन्यथा अगर (IS_QLA2300(ha) || IS_QLA2312(ha) || IS_QLA6312(ha)) अणु
		blob = &qla_fw_blobs[FW_ISP2300];
	पूर्ण अन्यथा अगर (IS_QLA2322(ha) || IS_QLA6322(ha)) अणु
		blob = &qla_fw_blobs[FW_ISP2322];
	पूर्ण अन्यथा अगर (IS_QLA24XX_TYPE(ha)) अणु
		blob = &qla_fw_blobs[FW_ISP24XX];
	पूर्ण अन्यथा अगर (IS_QLA25XX(ha)) अणु
		blob = &qla_fw_blobs[FW_ISP25XX];
	पूर्ण अन्यथा अगर (IS_QLA81XX(ha)) अणु
		blob = &qla_fw_blobs[FW_ISP81XX];
	पूर्ण अन्यथा अगर (IS_QLA82XX(ha)) अणु
		blob = &qla_fw_blobs[FW_ISP82XX];
	पूर्ण अन्यथा अगर (IS_QLA2031(ha)) अणु
		blob = &qla_fw_blobs[FW_ISP2031];
	पूर्ण अन्यथा अगर (IS_QLA8031(ha)) अणु
		blob = &qla_fw_blobs[FW_ISP8031];
	पूर्ण अन्यथा अगर (IS_QLA27XX(ha)) अणु
		blob = &qla_fw_blobs[FW_ISP27XX];
	पूर्ण अन्यथा अगर (IS_QLA28XX(ha)) अणु
		blob = &qla_fw_blobs[FW_ISP28XX];
	पूर्ण अन्यथा अणु
		वापस शून्य;
	पूर्ण

	अगर (!blob->name)
		वापस शून्य;

	mutex_lock(&qla_fw_lock);
	अगर (blob->fw)
		जाओ out;

	अगर (request_firmware(&blob->fw, blob->name, &ha->pdev->dev)) अणु
		ql_log(ql_log_warn, vha, 0x0063,
		    "Failed to load firmware image (%s).\n", blob->name);
		blob->fw = शून्य;
		blob = शून्य;
	पूर्ण

out:
	mutex_unlock(&qla_fw_lock);
	वापस blob;
पूर्ण

अटल व्योम
qla2x00_release_firmware(व्योम)
अणु
	काष्ठा fw_blob *blob;

	mutex_lock(&qla_fw_lock);
	क्रम (blob = qla_fw_blobs; blob->name; blob++)
		release_firmware(blob->fw);
	mutex_unlock(&qla_fw_lock);
पूर्ण

अटल व्योम qla_pci_error_cleanup(scsi_qla_host_t *vha)
अणु
	काष्ठा qla_hw_data *ha = vha->hw;
	scsi_qla_host_t *base_vha = pci_get_drvdata(ha->pdev);
	काष्ठा qla_qpair *qpair = शून्य;
	काष्ठा scsi_qla_host *vp;
	fc_port_t *fcport;
	पूर्णांक i;
	अचिन्हित दीर्घ flags;

	ql_dbg(ql_dbg_aer, vha, 0x9000,
	       "%s\n", __func__);
	ha->chip_reset++;

	ha->base_qpair->chip_reset = ha->chip_reset;
	क्रम (i = 0; i < ha->max_qpairs; i++) अणु
		अगर (ha->queue_pair_map[i])
			ha->queue_pair_map[i]->chip_reset =
			    ha->base_qpair->chip_reset;
	पूर्ण

	/*
	 * purge mailbox might take a जबतक. Slot Reset/chip reset
	 * will take care of the purge
	 */

	mutex_lock(&ha->mq_lock);
	ha->base_qpair->online = 0;
	list_क्रम_each_entry(qpair, &base_vha->qp_list, qp_list_elem)
		qpair->online = 0;
	wmb();
	mutex_unlock(&ha->mq_lock);

	qla2x00_mark_all_devices_lost(vha);

	spin_lock_irqsave(&ha->vport_slock, flags);
	list_क्रम_each_entry(vp, &ha->vp_list, list) अणु
		atomic_inc(&vp->vref_count);
		spin_unlock_irqrestore(&ha->vport_slock, flags);
		qla2x00_mark_all_devices_lost(vp);
		spin_lock_irqsave(&ha->vport_slock, flags);
		atomic_dec(&vp->vref_count);
	पूर्ण
	spin_unlock_irqrestore(&ha->vport_slock, flags);

	/* Clear all async request states across all VPs. */
	list_क्रम_each_entry(fcport, &vha->vp_fcports, list)
		fcport->flags &= ~(FCF_LOGIN_NEEDED | FCF_ASYNC_SENT);

	spin_lock_irqsave(&ha->vport_slock, flags);
	list_क्रम_each_entry(vp, &ha->vp_list, list) अणु
		atomic_inc(&vp->vref_count);
		spin_unlock_irqrestore(&ha->vport_slock, flags);
		list_क्रम_each_entry(fcport, &vp->vp_fcports, list)
			fcport->flags &= ~(FCF_LOGIN_NEEDED | FCF_ASYNC_SENT);
		spin_lock_irqsave(&ha->vport_slock, flags);
		atomic_dec(&vp->vref_count);
	पूर्ण
	spin_unlock_irqrestore(&ha->vport_slock, flags);
पूर्ण


अटल pci_ers_result_t
qla2xxx_pci_error_detected(काष्ठा pci_dev *pdev, pci_channel_state_t state)
अणु
	scsi_qla_host_t *vha = pci_get_drvdata(pdev);
	काष्ठा qla_hw_data *ha = vha->hw;
	pci_ers_result_t ret = PCI_ERS_RESULT_NEED_RESET;

	ql_log(ql_log_warn, vha, 0x9000,
	       "PCI error detected, state %x.\n", state);
	ha->pci_error_state = QLA_PCI_ERR_DETECTED;

	अगर (!atomic_पढ़ो(&pdev->enable_cnt)) अणु
		ql_log(ql_log_info, vha, 0xffff,
			"PCI device is disabled,state %x\n", state);
		ret = PCI_ERS_RESULT_NEED_RESET;
		जाओ out;
	पूर्ण

	चयन (state) अणु
	हाल pci_channel_io_normal:
		ha->flags.eeh_busy = 0;
		अगर (ql2xmqsupport || ql2xnvmeenable) अणु
			set_bit(QPAIR_ONLINE_CHECK_NEEDED, &vha->dpc_flags);
			qla2xxx_wake_dpc(vha);
		पूर्ण
		ret = PCI_ERS_RESULT_CAN_RECOVER;
		अवरोध;
	हाल pci_channel_io_frozen:
		qla_pci_set_eeh_busy(vha);
		ret = PCI_ERS_RESULT_NEED_RESET;
		अवरोध;
	हाल pci_channel_io_perm_failure:
		ha->flags.pci_channel_io_perm_failure = 1;
		qla2x00_पात_all_cmds(vha, DID_NO_CONNECT << 16);
		अगर (ql2xmqsupport || ql2xnvmeenable) अणु
			set_bit(QPAIR_ONLINE_CHECK_NEEDED, &vha->dpc_flags);
			qla2xxx_wake_dpc(vha);
		पूर्ण
		ret = PCI_ERS_RESULT_DISCONNECT;
	पूर्ण
out:
	ql_dbg(ql_dbg_aer, vha, 0x600d,
	       "PCI error detected returning [%x].\n", ret);
	वापस ret;
पूर्ण

अटल pci_ers_result_t
qla2xxx_pci_mmio_enabled(काष्ठा pci_dev *pdev)
अणु
	पूर्णांक risc_छोड़ोd = 0;
	uपूर्णांक32_t stat;
	अचिन्हित दीर्घ flags;
	scsi_qla_host_t *base_vha = pci_get_drvdata(pdev);
	काष्ठा qla_hw_data *ha = base_vha->hw;
	काष्ठा device_reg_2xxx __iomem *reg = &ha->iobase->isp;
	काष्ठा device_reg_24xx __iomem *reg24 = &ha->iobase->isp24;

	ql_log(ql_log_warn, base_vha, 0x9000,
	       "mmio enabled\n");

	ha->pci_error_state = QLA_PCI_MMIO_ENABLED;
	अगर (IS_QLA82XX(ha))
		वापस PCI_ERS_RESULT_RECOVERED;

	spin_lock_irqsave(&ha->hardware_lock, flags);
	अगर (IS_QLA2100(ha) || IS_QLA2200(ha))अणु
		stat = rd_reg_word(&reg->hccr);
		अगर (stat & HCCR_RISC_PAUSE)
			risc_छोड़ोd = 1;
	पूर्ण अन्यथा अगर (IS_QLA23XX(ha)) अणु
		stat = rd_reg_dword(&reg->u.isp2300.host_status);
		अगर (stat & HSR_RISC_PAUSED)
			risc_छोड़ोd = 1;
	पूर्ण अन्यथा अगर (IS_FWI2_CAPABLE(ha)) अणु
		stat = rd_reg_dword(&reg24->host_status);
		अगर (stat & HSRX_RISC_PAUSED)
			risc_छोड़ोd = 1;
	पूर्ण
	spin_unlock_irqrestore(&ha->hardware_lock, flags);

	अगर (risc_छोड़ोd) अणु
		ql_log(ql_log_info, base_vha, 0x9003,
		    "RISC paused -- mmio_enabled, Dumping firmware.\n");
		qla2xxx_dump_fw(base_vha);
	पूर्ण
	/* set PCI_ERS_RESULT_NEED_RESET to trigger call to qla2xxx_pci_slot_reset */
	ql_dbg(ql_dbg_aer, base_vha, 0x600d,
	       "mmio enabled returning.\n");
	वापस PCI_ERS_RESULT_NEED_RESET;
पूर्ण

अटल pci_ers_result_t
qla2xxx_pci_slot_reset(काष्ठा pci_dev *pdev)
अणु
	pci_ers_result_t ret = PCI_ERS_RESULT_DISCONNECT;
	scsi_qla_host_t *base_vha = pci_get_drvdata(pdev);
	काष्ठा qla_hw_data *ha = base_vha->hw;
	पूर्णांक rc;
	काष्ठा qla_qpair *qpair = शून्य;

	ql_log(ql_log_warn, base_vha, 0x9004,
	       "Slot Reset.\n");

	ha->pci_error_state = QLA_PCI_SLOT_RESET;
	/* Workaround: qla2xxx driver which access hardware earlier
	 * needs error state to be pci_channel_io_online.
	 * Otherwise mailbox command बारout.
	 */
	pdev->error_state = pci_channel_io_normal;

	pci_restore_state(pdev);

	/* pci_restore_state() clears the saved_state flag of the device
	 * save restored state which resets saved_state flag
	 */
	pci_save_state(pdev);

	अगर (ha->mem_only)
		rc = pci_enable_device_mem(pdev);
	अन्यथा
		rc = pci_enable_device(pdev);

	अगर (rc) अणु
		ql_log(ql_log_warn, base_vha, 0x9005,
		    "Can't re-enable PCI device after reset.\n");
		जाओ निकास_slot_reset;
	पूर्ण


	अगर (ha->isp_ops->pci_config(base_vha))
		जाओ निकास_slot_reset;

	mutex_lock(&ha->mq_lock);
	list_क्रम_each_entry(qpair, &base_vha->qp_list, qp_list_elem)
		qpair->online = 1;
	mutex_unlock(&ha->mq_lock);

	ha->flags.eeh_busy = 0;
	base_vha->flags.online = 1;
	set_bit(ABORT_ISP_ACTIVE, &base_vha->dpc_flags);
	ha->isp_ops->पात_isp(base_vha);
	clear_bit(ABORT_ISP_ACTIVE, &base_vha->dpc_flags);

	अगर (qla2x00_isp_reg_stat(ha)) अणु
		ha->flags.eeh_busy = 1;
		qla_pci_error_cleanup(base_vha);
		ql_log(ql_log_warn, base_vha, 0x9005,
		       "Device unable to recover from PCI error.\n");
	पूर्ण अन्यथा अणु
		ret =  PCI_ERS_RESULT_RECOVERED;
	पूर्ण

निकास_slot_reset:
	ql_dbg(ql_dbg_aer, base_vha, 0x900e,
	    "Slot Reset returning %x.\n", ret);

	वापस ret;
पूर्ण

अटल व्योम
qla2xxx_pci_resume(काष्ठा pci_dev *pdev)
अणु
	scsi_qla_host_t *base_vha = pci_get_drvdata(pdev);
	काष्ठा qla_hw_data *ha = base_vha->hw;
	पूर्णांक ret;

	ql_log(ql_log_warn, base_vha, 0x900f,
	       "Pci Resume.\n");


	ret = qla2x00_रुको_क्रम_hba_online(base_vha);
	अगर (ret != QLA_SUCCESS) अणु
		ql_log(ql_log_fatal, base_vha, 0x9002,
		    "The device failed to resume I/O from slot/link_reset.\n");
	पूर्ण
	ha->pci_error_state = QLA_PCI_RESUME;
	ql_dbg(ql_dbg_aer, base_vha, 0x600d,
	       "Pci Resume returning.\n");
पूर्ण

व्योम qla_pci_set_eeh_busy(काष्ठा scsi_qla_host *vha)
अणु
	काष्ठा qla_hw_data *ha = vha->hw;
	काष्ठा scsi_qla_host *base_vha = pci_get_drvdata(ha->pdev);
	bool करो_cleanup = false;
	अचिन्हित दीर्घ flags;

	अगर (ha->flags.eeh_busy)
		वापस;

	spin_lock_irqsave(&base_vha->work_lock, flags);
	अगर (!ha->flags.eeh_busy) अणु
		ha->flags.eeh_busy = 1;
		करो_cleanup = true;
	पूर्ण
	spin_unlock_irqrestore(&base_vha->work_lock, flags);

	अगर (करो_cleanup)
		qla_pci_error_cleanup(base_vha);
पूर्ण

/*
 * this routine will schedule a task to छोड़ो IO from पूर्णांकerrupt context
 * अगर caller sees a PCIE error event (रेजिस्टर पढ़ो = 0xf's)
 */
व्योम qla_schedule_eeh_work(काष्ठा scsi_qla_host *vha)
अणु
	काष्ठा qla_hw_data *ha = vha->hw;
	काष्ठा scsi_qla_host *base_vha = pci_get_drvdata(ha->pdev);

	अगर (ha->flags.eeh_busy)
		वापस;

	set_bit(DO_EEH_RECOVERY, &base_vha->dpc_flags);
	qla2xxx_wake_dpc(base_vha);
पूर्ण

अटल व्योम
qla_pci_reset_prepare(काष्ठा pci_dev *pdev)
अणु
	scsi_qla_host_t *base_vha = pci_get_drvdata(pdev);
	काष्ठा qla_hw_data *ha = base_vha->hw;
	काष्ठा qla_qpair *qpair;

	ql_log(ql_log_warn, base_vha, 0xffff,
	    "%s.\n", __func__);

	/*
	 * PCI FLR/function reset is about to reset the
	 * slot. Stop the chip to stop all DMA access.
	 * It is assumed that pci_reset_करोne will be called
	 * after FLR to resume Chip operation.
	 */
	ha->flags.eeh_busy = 1;
	mutex_lock(&ha->mq_lock);
	list_क्रम_each_entry(qpair, &base_vha->qp_list, qp_list_elem)
		qpair->online = 0;
	mutex_unlock(&ha->mq_lock);

	set_bit(ABORT_ISP_ACTIVE, &base_vha->dpc_flags);
	qla2x00_पात_isp_cleanup(base_vha);
	qla2x00_पात_all_cmds(base_vha, DID_RESET << 16);
पूर्ण

अटल व्योम
qla_pci_reset_करोne(काष्ठा pci_dev *pdev)
अणु
	scsi_qla_host_t *base_vha = pci_get_drvdata(pdev);
	काष्ठा qla_hw_data *ha = base_vha->hw;
	काष्ठा qla_qpair *qpair;

	ql_log(ql_log_warn, base_vha, 0xffff,
	    "%s.\n", __func__);

	/*
	 * FLR just completed by PCI layer. Resume adapter
	 */
	ha->flags.eeh_busy = 0;
	mutex_lock(&ha->mq_lock);
	list_क्रम_each_entry(qpair, &base_vha->qp_list, qp_list_elem)
		qpair->online = 1;
	mutex_unlock(&ha->mq_lock);

	base_vha->flags.online = 1;
	ha->isp_ops->पात_isp(base_vha);
	clear_bit(ABORT_ISP_ACTIVE, &base_vha->dpc_flags);
पूर्ण

अटल पूर्णांक qla2xxx_map_queues(काष्ठा Scsi_Host *shost)
अणु
	पूर्णांक rc;
	scsi_qla_host_t *vha = (scsi_qla_host_t *)shost->hostdata;
	काष्ठा blk_mq_queue_map *qmap = &shost->tag_set.map[HCTX_TYPE_DEFAULT];

	अगर (USER_CTRL_IRQ(vha->hw) || !vha->hw->mqiobase)
		rc = blk_mq_map_queues(qmap);
	अन्यथा
		rc = blk_mq_pci_map_queues(qmap, vha->hw->pdev, vha->irq_offset);
	वापस rc;
पूर्ण

काष्ठा scsi_host_ढाँचा qla2xxx_driver_ढाँचा = अणु
	.module			= THIS_MODULE,
	.name			= QLA2XXX_DRIVER_NAME,
	.queuecommand		= qla2xxx_queuecommand,

	.eh_समयd_out		= fc_eh_समयd_out,
	.eh_पात_handler	= qla2xxx_eh_पात,
	.eh_should_retry_cmd	= fc_eh_should_retry_cmd,
	.eh_device_reset_handler = qla2xxx_eh_device_reset,
	.eh_target_reset_handler = qla2xxx_eh_target_reset,
	.eh_bus_reset_handler	= qla2xxx_eh_bus_reset,
	.eh_host_reset_handler	= qla2xxx_eh_host_reset,

	.slave_configure	= qla2xxx_slave_configure,

	.slave_alloc		= qla2xxx_slave_alloc,
	.slave_destroy		= qla2xxx_slave_destroy,
	.scan_finished		= qla2xxx_scan_finished,
	.scan_start		= qla2xxx_scan_start,
	.change_queue_depth	= scsi_change_queue_depth,
	.map_queues             = qla2xxx_map_queues,
	.this_id		= -1,
	.cmd_per_lun		= 3,
	.sg_tablesize		= SG_ALL,

	.max_sectors		= 0xFFFF,
	.shost_attrs		= qla2x00_host_attrs,

	.supported_mode		= MODE_INITIATOR,
	.track_queue_depth	= 1,
	.cmd_size		= माप(srb_t),
पूर्ण;

अटल स्थिर काष्ठा pci_error_handlers qla2xxx_err_handler = अणु
	.error_detected = qla2xxx_pci_error_detected,
	.mmio_enabled = qla2xxx_pci_mmio_enabled,
	.slot_reset = qla2xxx_pci_slot_reset,
	.resume = qla2xxx_pci_resume,
	.reset_prepare = qla_pci_reset_prepare,
	.reset_करोne = qla_pci_reset_करोne,
पूर्ण;

अटल काष्ठा pci_device_id qla2xxx_pci_tbl[] = अणु
	अणु PCI_DEVICE(PCI_VENDOR_ID_QLOGIC, PCI_DEVICE_ID_QLOGIC_ISP2100) पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_QLOGIC, PCI_DEVICE_ID_QLOGIC_ISP2200) पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_QLOGIC, PCI_DEVICE_ID_QLOGIC_ISP2300) पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_QLOGIC, PCI_DEVICE_ID_QLOGIC_ISP2312) पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_QLOGIC, PCI_DEVICE_ID_QLOGIC_ISP2322) पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_QLOGIC, PCI_DEVICE_ID_QLOGIC_ISP6312) पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_QLOGIC, PCI_DEVICE_ID_QLOGIC_ISP6322) पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_QLOGIC, PCI_DEVICE_ID_QLOGIC_ISP2422) पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_QLOGIC, PCI_DEVICE_ID_QLOGIC_ISP2432) पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_QLOGIC, PCI_DEVICE_ID_QLOGIC_ISP8432) पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_QLOGIC, PCI_DEVICE_ID_QLOGIC_ISP5422) पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_QLOGIC, PCI_DEVICE_ID_QLOGIC_ISP5432) पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_QLOGIC, PCI_DEVICE_ID_QLOGIC_ISP2532) पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_QLOGIC, PCI_DEVICE_ID_QLOGIC_ISP2031) पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_QLOGIC, PCI_DEVICE_ID_QLOGIC_ISP8001) पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_QLOGIC, PCI_DEVICE_ID_QLOGIC_ISP8021) पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_QLOGIC, PCI_DEVICE_ID_QLOGIC_ISP8031) पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_QLOGIC, PCI_DEVICE_ID_QLOGIC_ISPF001) पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_QLOGIC, PCI_DEVICE_ID_QLOGIC_ISP8044) पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_QLOGIC, PCI_DEVICE_ID_QLOGIC_ISP2071) पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_QLOGIC, PCI_DEVICE_ID_QLOGIC_ISP2271) पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_QLOGIC, PCI_DEVICE_ID_QLOGIC_ISP2261) पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_QLOGIC, PCI_DEVICE_ID_QLOGIC_ISP2061) पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_QLOGIC, PCI_DEVICE_ID_QLOGIC_ISP2081) पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_QLOGIC, PCI_DEVICE_ID_QLOGIC_ISP2281) पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_QLOGIC, PCI_DEVICE_ID_QLOGIC_ISP2089) पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_QLOGIC, PCI_DEVICE_ID_QLOGIC_ISP2289) पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(pci, qla2xxx_pci_tbl);

अटल काष्ठा pci_driver qla2xxx_pci_driver = अणु
	.name		= QLA2XXX_DRIVER_NAME,
	.driver		= अणु
		.owner		= THIS_MODULE,
	पूर्ण,
	.id_table	= qla2xxx_pci_tbl,
	.probe		= qla2x00_probe_one,
	.हटाओ		= qla2x00_हटाओ_one,
	.shutकरोwn	= qla2x00_shutकरोwn,
	.err_handler	= &qla2xxx_err_handler,
पूर्ण;

अटल स्थिर काष्ठा file_operations apidev_fops = अणु
	.owner = THIS_MODULE,
	.llseek = noop_llseek,
पूर्ण;

/**
 * qla2x00_module_init - Module initialization.
 **/
अटल पूर्णांक __init
qla2x00_module_init(व्योम)
अणु
	पूर्णांक ret = 0;

	BUILD_BUG_ON(माप(cmd_a64_entry_t) != 64);
	BUILD_BUG_ON(माप(cmd_entry_t) != 64);
	BUILD_BUG_ON(माप(cont_a64_entry_t) != 64);
	BUILD_BUG_ON(माप(cont_entry_t) != 64);
	BUILD_BUG_ON(माप(init_cb_t) != 96);
	BUILD_BUG_ON(माप(mrk_entry_t) != 64);
	BUILD_BUG_ON(माप(ms_iocb_entry_t) != 64);
	BUILD_BUG_ON(माप(request_t) != 64);
	BUILD_BUG_ON(माप(काष्ठा पात_entry_24xx) != 64);
	BUILD_BUG_ON(माप(काष्ठा पात_iocb_entry_fx00) != 64);
	BUILD_BUG_ON(माप(काष्ठा abts_entry_24xx) != 64);
	BUILD_BUG_ON(माप(काष्ठा access_chip_84xx) != 64);
	BUILD_BUG_ON(माप(काष्ठा access_chip_rsp_84xx) != 64);
	BUILD_BUG_ON(माप(काष्ठा cmd_bidir) != 64);
	BUILD_BUG_ON(माप(काष्ठा cmd_nvme) != 64);
	BUILD_BUG_ON(माप(काष्ठा cmd_type_6) != 64);
	BUILD_BUG_ON(माप(काष्ठा cmd_type_7) != 64);
	BUILD_BUG_ON(माप(काष्ठा cmd_type_7_fx00) != 64);
	BUILD_BUG_ON(माप(काष्ठा cmd_type_crc_2) != 64);
	BUILD_BUG_ON(माप(काष्ठा ct_entry_24xx) != 64);
	BUILD_BUG_ON(माप(काष्ठा ct_fdmi1_hba_attributes) != 2344);
	BUILD_BUG_ON(माप(काष्ठा ct_fdmi2_hba_attributes) != 4424);
	BUILD_BUG_ON(माप(काष्ठा ct_fdmi2_port_attributes) != 4164);
	BUILD_BUG_ON(माप(काष्ठा ct_fdmi_hba_attr) != 260);
	BUILD_BUG_ON(माप(काष्ठा ct_fdmi_port_attr) != 260);
	BUILD_BUG_ON(माप(काष्ठा ct_rsp_hdr) != 16);
	BUILD_BUG_ON(माप(काष्ठा ctio_crc2_to_fw) != 64);
	BUILD_BUG_ON(माप(काष्ठा device_reg_24xx) != 256);
	BUILD_BUG_ON(माप(काष्ठा device_reg_25xxmq) != 24);
	BUILD_BUG_ON(माप(काष्ठा device_reg_2xxx) != 256);
	BUILD_BUG_ON(माप(काष्ठा device_reg_82xx) != 1288);
	BUILD_BUG_ON(माप(काष्ठा device_reg_fx00) != 216);
	BUILD_BUG_ON(माप(काष्ठा els_entry_24xx) != 64);
	BUILD_BUG_ON(माप(काष्ठा els_sts_entry_24xx) != 64);
	BUILD_BUG_ON(माप(काष्ठा fxdisc_entry_fx00) != 64);
	BUILD_BUG_ON(माप(काष्ठा imm_ntfy_from_isp) != 64);
	BUILD_BUG_ON(माप(काष्ठा init_cb_24xx) != 128);
	BUILD_BUG_ON(माप(काष्ठा init_cb_81xx) != 128);
	BUILD_BUG_ON(माप(काष्ठा logio_entry_24xx) != 64);
	BUILD_BUG_ON(माप(काष्ठा mbx_entry) != 64);
	BUILD_BUG_ON(माप(काष्ठा mid_init_cb_24xx) != 5252);
	BUILD_BUG_ON(माप(काष्ठा mrk_entry_24xx) != 64);
	BUILD_BUG_ON(माप(काष्ठा nvram_24xx) != 512);
	BUILD_BUG_ON(माप(काष्ठा nvram_81xx) != 512);
	BUILD_BUG_ON(माप(काष्ठा pt_ls4_request) != 64);
	BUILD_BUG_ON(माप(काष्ठा pt_ls4_rx_unsol) != 64);
	BUILD_BUG_ON(माप(काष्ठा purex_entry_24xx) != 64);
	BUILD_BUG_ON(माप(काष्ठा qla2100_fw_dump) != 123634);
	BUILD_BUG_ON(माप(काष्ठा qla2300_fw_dump) != 136100);
	BUILD_BUG_ON(माप(काष्ठा qla24xx_fw_dump) != 37976);
	BUILD_BUG_ON(माप(काष्ठा qla25xx_fw_dump) != 39228);
	BUILD_BUG_ON(माप(काष्ठा qla2xxx_fce_chain) != 52);
	BUILD_BUG_ON(माप(काष्ठा qla2xxx_fw_dump) != 136172);
	BUILD_BUG_ON(माप(काष्ठा qla2xxx_mq_chain) != 524);
	BUILD_BUG_ON(माप(काष्ठा qla2xxx_mqueue_chain) != 8);
	BUILD_BUG_ON(माप(काष्ठा qla2xxx_mqueue_header) != 12);
	BUILD_BUG_ON(माप(काष्ठा qla2xxx_offld_chain) != 24);
	BUILD_BUG_ON(माप(काष्ठा qla81xx_fw_dump) != 39420);
	BUILD_BUG_ON(माप(काष्ठा qla82xx_uri_data_desc) != 28);
	BUILD_BUG_ON(माप(काष्ठा qla82xx_uri_table_desc) != 32);
	BUILD_BUG_ON(माप(काष्ठा qla83xx_fw_dump) != 51196);
	BUILD_BUG_ON(माप(काष्ठा qla_fcp_prio_cfg) != FCP_PRIO_CFG_SIZE);
	BUILD_BUG_ON(माप(काष्ठा qla_fdt_layout) != 128);
	BUILD_BUG_ON(माप(काष्ठा qla_flt_header) != 8);
	BUILD_BUG_ON(माप(काष्ठा qla_flt_region) != 16);
	BUILD_BUG_ON(माप(काष्ठा qla_npiv_entry) != 24);
	BUILD_BUG_ON(माप(काष्ठा qla_npiv_header) != 16);
	BUILD_BUG_ON(माप(काष्ठा rdp_rsp_payload) != 336);
	BUILD_BUG_ON(माप(काष्ठा sns_cmd_pkt) != 2064);
	BUILD_BUG_ON(माप(काष्ठा sts_entry_24xx) != 64);
	BUILD_BUG_ON(माप(काष्ठा tsk_mgmt_entry) != 64);
	BUILD_BUG_ON(माप(काष्ठा tsk_mgmt_entry_fx00) != 64);
	BUILD_BUG_ON(माप(काष्ठा verअगरy_chip_entry_84xx) != 64);
	BUILD_BUG_ON(माप(काष्ठा verअगरy_chip_rsp_84xx) != 52);
	BUILD_BUG_ON(माप(काष्ठा vf_evfp_entry_24xx) != 56);
	BUILD_BUG_ON(माप(काष्ठा vp_config_entry_24xx) != 64);
	BUILD_BUG_ON(माप(काष्ठा vp_ctrl_entry_24xx) != 64);
	BUILD_BUG_ON(माप(काष्ठा vp_rpt_id_entry_24xx) != 64);
	BUILD_BUG_ON(माप(sts21_entry_t) != 64);
	BUILD_BUG_ON(माप(sts22_entry_t) != 64);
	BUILD_BUG_ON(माप(sts_cont_entry_t) != 64);
	BUILD_BUG_ON(माप(sts_entry_t) != 64);
	BUILD_BUG_ON(माप(sw_info_t) != 32);
	BUILD_BUG_ON(माप(target_id_t) != 2);

	/* Allocate cache क्रम SRBs. */
	srb_cachep = kmem_cache_create("qla2xxx_srbs", माप(srb_t), 0,
	    SLAB_HWCACHE_ALIGN, शून्य);
	अगर (srb_cachep == शून्य) अणु
		ql_log(ql_log_fatal, शून्य, 0x0001,
		    "Unable to allocate SRB cache...Failing load!.\n");
		वापस -ENOMEM;
	पूर्ण

	/* Initialize target kmem_cache and mem_pools */
	ret = qlt_init();
	अगर (ret < 0) अणु
		जाओ destroy_cache;
	पूर्ण अन्यथा अगर (ret > 0) अणु
		/*
		 * If initiator mode is explictly disabled by qlt_init(),
		 * prevent scsi_transport_fc.c:fc_scsi_scan_rport() from
		 * perक्रमming scsi_scan_target() during LOOP UP event.
		 */
		qla2xxx_transport_functions.disable_target_scan = 1;
		qla2xxx_transport_vport_functions.disable_target_scan = 1;
	पूर्ण

	/* Derive version string. */
	म_नकल(qla2x00_version_str, QLA2XXX_VERSION);
	अगर (ql2xextended_error_logging)
		म_जोड़ो(qla2x00_version_str, "-debug");
	अगर (ql2xextended_error_logging == 1)
		ql2xextended_error_logging = QL_DBG_DEFAULT1_MASK;

	अगर (ql2x_ini_mode == QLA2XXX_INI_MODE_DUAL)
		qla_insert_tgt_attrs();

	qla2xxx_transport_ढाँचा =
	    fc_attach_transport(&qla2xxx_transport_functions);
	अगर (!qla2xxx_transport_ढाँचा) अणु
		ql_log(ql_log_fatal, शून्य, 0x0002,
		    "fc_attach_transport failed...Failing load!.\n");
		ret = -ENODEV;
		जाओ qlt_निकास;
	पूर्ण

	apidev_major = रेजिस्टर_chrdev(0, QLA2XXX_APIDEV, &apidev_fops);
	अगर (apidev_major < 0) अणु
		ql_log(ql_log_fatal, शून्य, 0x0003,
		    "Unable to register char device %s.\n", QLA2XXX_APIDEV);
	पूर्ण

	qla2xxx_transport_vport_ढाँचा =
	    fc_attach_transport(&qla2xxx_transport_vport_functions);
	अगर (!qla2xxx_transport_vport_ढाँचा) अणु
		ql_log(ql_log_fatal, शून्य, 0x0004,
		    "fc_attach_transport vport failed...Failing load!.\n");
		ret = -ENODEV;
		जाओ unreg_chrdev;
	पूर्ण
	ql_log(ql_log_info, शून्य, 0x0005,
	    "QLogic Fibre Channel HBA Driver: %s.\n",
	    qla2x00_version_str);
	ret = pci_रेजिस्टर_driver(&qla2xxx_pci_driver);
	अगर (ret) अणु
		ql_log(ql_log_fatal, शून्य, 0x0006,
		    "pci_register_driver failed...ret=%d Failing load!.\n",
		    ret);
		जाओ release_vport_transport;
	पूर्ण
	वापस ret;

release_vport_transport:
	fc_release_transport(qla2xxx_transport_vport_ढाँचा);

unreg_chrdev:
	अगर (apidev_major >= 0)
		unरेजिस्टर_chrdev(apidev_major, QLA2XXX_APIDEV);
	fc_release_transport(qla2xxx_transport_ढाँचा);

qlt_निकास:
	qlt_निकास();

destroy_cache:
	kmem_cache_destroy(srb_cachep);
	वापस ret;
पूर्ण

/**
 * qla2x00_module_निकास - Module cleanup.
 **/
अटल व्योम __निकास
qla2x00_module_निकास(व्योम)
अणु
	pci_unरेजिस्टर_driver(&qla2xxx_pci_driver);
	qla2x00_release_firmware();
	kmem_cache_destroy(ctx_cachep);
	fc_release_transport(qla2xxx_transport_vport_ढाँचा);
	अगर (apidev_major >= 0)
		unरेजिस्टर_chrdev(apidev_major, QLA2XXX_APIDEV);
	fc_release_transport(qla2xxx_transport_ढाँचा);
	qlt_निकास();
	kmem_cache_destroy(srb_cachep);
पूर्ण

module_init(qla2x00_module_init);
module_निकास(qla2x00_module_निकास);

MODULE_AUTHOR("QLogic Corporation");
MODULE_DESCRIPTION("QLogic Fibre Channel HBA Driver");
MODULE_LICENSE("GPL");
MODULE_FIRMWARE(FW_खाता_ISP21XX);
MODULE_FIRMWARE(FW_खाता_ISP22XX);
MODULE_FIRMWARE(FW_खाता_ISP2300);
MODULE_FIRMWARE(FW_खाता_ISP2322);
MODULE_FIRMWARE(FW_खाता_ISP24XX);
MODULE_FIRMWARE(FW_खाता_ISP25XX);
