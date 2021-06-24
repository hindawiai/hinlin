<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (c) 2015-2016 HGST, a Western Digital Company.
 */

#अगर_अघोषित _NVMET_H
#घोषणा _NVMET_H

#समावेश <linux/dma-mapping.h>
#समावेश <linux/types.h>
#समावेश <linux/device.h>
#समावेश <linux/kref.h>
#समावेश <linux/percpu-refcount.h>
#समावेश <linux/list.h>
#समावेश <linux/mutex.h>
#समावेश <linux/uuid.h>
#समावेश <linux/nvme.h>
#समावेश <linux/configfs.h>
#समावेश <linux/rcupdate.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/radix-tree.h>
#समावेश <linux/t10-pi.h>

#घोषणा NVMET_DEFAULT_VS		NVME_VS(1, 3, 0)

#घोषणा NVMET_ASYNC_EVENTS		4
#घोषणा NVMET_ERROR_LOG_SLOTS		128
#घोषणा NVMET_NO_ERROR_LOC		((u16)-1)
#घोषणा NVMET_DEFAULT_CTRL_MODEL	"Linux"
#घोषणा NVMET_MN_MAX_SIZE		40

/*
 * Supported optional AENs:
 */
#घोषणा NVMET_AEN_CFG_OPTIONAL \
	(NVME_AEN_CFG_NS_ATTR | NVME_AEN_CFG_ANA_CHANGE)
#घोषणा NVMET_DISC_AEN_CFG_OPTIONAL \
	(NVME_AEN_CFG_DISC_CHANGE)

/*
 * Plus mandatory SMART AENs (we'll never send them, but allow enabling them):
 */
#घोषणा NVMET_AEN_CFG_ALL \
	(NVME_SMART_CRIT_SPARE | NVME_SMART_CRIT_TEMPERATURE | \
	 NVME_SMART_CRIT_RELIABILITY | NVME_SMART_CRIT_MEDIA | \
	 NVME_SMART_CRIT_VOLATILE_MEMORY | NVMET_AEN_CFG_OPTIONAL)

/* Helper Macros when NVMe error is NVME_SC_CONNECT_INVALID_PARAM
 * The 16 bit shअगरt is to set IATTR bit to 1, which means offending
 * offset starts in the data section of connect()
 */
#घोषणा IPO_IATTR_CONNECT_DATA(x)	\
	(cpu_to_le32((1 << 16) | (दुरत्व(काष्ठा nvmf_connect_data, x))))
#घोषणा IPO_IATTR_CONNECT_SQE(x)	\
	(cpu_to_le32(दुरत्व(काष्ठा nvmf_connect_command, x)))

काष्ठा nvmet_ns अणु
	काष्ठा percpu_ref	ref;
	काष्ठा block_device	*bdev;
	काष्ठा file		*file;
	bool			पढ़ोonly;
	u32			nsid;
	u32			blksize_shअगरt;
	loff_t			size;
	u8			nguid[16];
	uuid_t			uuid;
	u32			anagrpid;

	bool			buffered_io;
	bool			enabled;
	काष्ठा nvmet_subsys	*subsys;
	स्थिर अक्षर		*device_path;

	काष्ठा config_group	device_group;
	काष्ठा config_group	group;

	काष्ठा completion	disable_करोne;
	mempool_t		*bvec_pool;
	काष्ठा kmem_cache	*bvec_cache;

	पूर्णांक			use_p2pmem;
	काष्ठा pci_dev		*p2p_dev;
	पूर्णांक			pi_type;
	पूर्णांक			metadata_size;
पूर्ण;

अटल अंतरभूत काष्ठा nvmet_ns *to_nvmet_ns(काष्ठा config_item *item)
अणु
	वापस container_of(to_config_group(item), काष्ठा nvmet_ns, group);
पूर्ण

अटल अंतरभूत काष्ठा device *nvmet_ns_dev(काष्ठा nvmet_ns *ns)
अणु
	वापस ns->bdev ? disk_to_dev(ns->bdev->bd_disk) : शून्य;
पूर्ण

काष्ठा nvmet_cq अणु
	u16			qid;
	u16			size;
पूर्ण;

काष्ठा nvmet_sq अणु
	काष्ठा nvmet_ctrl	*ctrl;
	काष्ठा percpu_ref	ref;
	u16			qid;
	u16			size;
	u32			sqhd;
	bool			sqhd_disabled;
	काष्ठा completion	मुक्त_करोne;
	काष्ठा completion	confirm_करोne;
पूर्ण;

काष्ठा nvmet_ana_group अणु
	काष्ठा config_group	group;
	काष्ठा nvmet_port	*port;
	u32			grpid;
पूर्ण;

अटल अंतरभूत काष्ठा nvmet_ana_group *to_ana_group(काष्ठा config_item *item)
अणु
	वापस container_of(to_config_group(item), काष्ठा nvmet_ana_group,
			group);
पूर्ण

/**
 * काष्ठा nvmet_port -	Common काष्ठाure to keep port
 *				inक्रमmation क्रम the target.
 * @entry:		Entry पूर्णांकo referrals or transport list.
 * @disc_addr:		Address inक्रमmation is stored in a क्रमmat defined
 *				क्रम a discovery log page entry.
 * @group:		ConfigFS group क्रम this element's folder.
 * @priv:		Private data क्रम the transport.
 */
काष्ठा nvmet_port अणु
	काष्ठा list_head		entry;
	काष्ठा nvmf_disc_rsp_page_entry	disc_addr;
	काष्ठा config_group		group;
	काष्ठा config_group		subsys_group;
	काष्ठा list_head		subप्रणालीs;
	काष्ठा config_group		referrals_group;
	काष्ठा list_head		referrals;
	काष्ठा list_head		global_entry;
	काष्ठा config_group		ana_groups_group;
	काष्ठा nvmet_ana_group		ana_शेष_group;
	क्रमागत nvme_ana_state		*ana_state;
	व्योम				*priv;
	bool				enabled;
	पूर्णांक				अंतरभूत_data_size;
	स्थिर काष्ठा nvmet_fabrics_ops	*tr_ops;
	bool				pi_enable;
पूर्ण;

अटल अंतरभूत काष्ठा nvmet_port *to_nvmet_port(काष्ठा config_item *item)
अणु
	वापस container_of(to_config_group(item), काष्ठा nvmet_port,
			group);
पूर्ण

अटल अंतरभूत काष्ठा nvmet_port *ana_groups_to_port(
		काष्ठा config_item *item)
अणु
	वापस container_of(to_config_group(item), काष्ठा nvmet_port,
			ana_groups_group);
पूर्ण

काष्ठा nvmet_ctrl अणु
	काष्ठा nvmet_subsys	*subsys;
	काष्ठा nvmet_sq		**sqs;

	bool			reset_tbkas;

	काष्ठा mutex		lock;
	u64			cap;
	u32			cc;
	u32			csts;

	uuid_t			hostid;
	u16			cntlid;
	u32			kato;

	काष्ठा nvmet_port	*port;

	u32			aen_enabled;
	अचिन्हित दीर्घ		aen_masked;
	काष्ठा nvmet_req	*async_event_cmds[NVMET_ASYNC_EVENTS];
	अचिन्हित पूर्णांक		nr_async_event_cmds;
	काष्ठा list_head	async_events;
	काष्ठा work_काष्ठा	async_event_work;

	काष्ठा list_head	subsys_entry;
	काष्ठा kref		ref;
	काष्ठा delayed_work	ka_work;
	काष्ठा work_काष्ठा	fatal_err_work;

	स्थिर काष्ठा nvmet_fabrics_ops *ops;

	__le32			*changed_ns_list;
	u32			nr_changed_ns;

	अक्षर			subsysnqn[NVMF_NQN_FIELD_LEN];
	अक्षर			hostnqn[NVMF_NQN_FIELD_LEN];

	काष्ठा device		*p2p_client;
	काष्ठा radix_tree_root	p2p_ns_map;

	spinlock_t		error_lock;
	u64			err_counter;
	काष्ठा nvme_error_slot	slots[NVMET_ERROR_LOG_SLOTS];
	bool			pi_support;
पूर्ण;

काष्ठा nvmet_subsys अणु
	क्रमागत nvme_subsys_type	type;

	काष्ठा mutex		lock;
	काष्ठा kref		ref;

	काष्ठा xarray		namespaces;
	अचिन्हित पूर्णांक		nr_namespaces;
	अचिन्हित पूर्णांक		max_nsid;
	u16			cntlid_min;
	u16			cntlid_max;

	काष्ठा list_head	ctrls;

	काष्ठा list_head	hosts;
	bool			allow_any_host;

	u16			max_qid;

	u64			ver;
	u64			serial;
	अक्षर			*subsysnqn;
	bool			pi_support;

	काष्ठा config_group	group;

	काष्ठा config_group	namespaces_group;
	काष्ठा config_group	allowed_hosts_group;

	अक्षर			*model_number;

#अगर_घोषित CONFIG_NVME_TARGET_PASSTHRU
	काष्ठा nvme_ctrl	*passthru_ctrl;
	अक्षर			*passthru_ctrl_path;
	काष्ठा config_group	passthru_group;
	अचिन्हित पूर्णांक		admin_समयout;
	अचिन्हित पूर्णांक		io_समयout;
#पूर्ण_अगर /* CONFIG_NVME_TARGET_PASSTHRU */
पूर्ण;

अटल अंतरभूत काष्ठा nvmet_subsys *to_subsys(काष्ठा config_item *item)
अणु
	वापस container_of(to_config_group(item), काष्ठा nvmet_subsys, group);
पूर्ण

अटल अंतरभूत काष्ठा nvmet_subsys *namespaces_to_subsys(
		काष्ठा config_item *item)
अणु
	वापस container_of(to_config_group(item), काष्ठा nvmet_subsys,
			namespaces_group);
पूर्ण

काष्ठा nvmet_host अणु
	काष्ठा config_group	group;
पूर्ण;

अटल अंतरभूत काष्ठा nvmet_host *to_host(काष्ठा config_item *item)
अणु
	वापस container_of(to_config_group(item), काष्ठा nvmet_host, group);
पूर्ण

अटल अंतरभूत अक्षर *nvmet_host_name(काष्ठा nvmet_host *host)
अणु
	वापस config_item_name(&host->group.cg_item);
पूर्ण

काष्ठा nvmet_host_link अणु
	काष्ठा list_head	entry;
	काष्ठा nvmet_host	*host;
पूर्ण;

काष्ठा nvmet_subsys_link अणु
	काष्ठा list_head	entry;
	काष्ठा nvmet_subsys	*subsys;
पूर्ण;

काष्ठा nvmet_req;
काष्ठा nvmet_fabrics_ops अणु
	काष्ठा module *owner;
	अचिन्हित पूर्णांक type;
	अचिन्हित पूर्णांक msdbd;
	अचिन्हित पूर्णांक flags;
#घोषणा NVMF_KEYED_SGLS			(1 << 0)
#घोषणा NVMF_METADATA_SUPPORTED		(1 << 1)
	व्योम (*queue_response)(काष्ठा nvmet_req *req);
	पूर्णांक (*add_port)(काष्ठा nvmet_port *port);
	व्योम (*हटाओ_port)(काष्ठा nvmet_port *port);
	व्योम (*delete_ctrl)(काष्ठा nvmet_ctrl *ctrl);
	व्योम (*disc_traddr)(काष्ठा nvmet_req *req,
			काष्ठा nvmet_port *port, अक्षर *traddr);
	u16 (*install_queue)(काष्ठा nvmet_sq *nvme_sq);
	व्योम (*discovery_chg)(काष्ठा nvmet_port *port);
	u8 (*get_mdts)(स्थिर काष्ठा nvmet_ctrl *ctrl);
पूर्ण;

#घोषणा NVMET_MAX_INLINE_BIOVEC	8
#घोषणा NVMET_MAX_INLINE_DATA_LEN NVMET_MAX_INLINE_BIOVEC * PAGE_SIZE

काष्ठा nvmet_req अणु
	काष्ठा nvme_command	*cmd;
	काष्ठा nvme_completion	*cqe;
	काष्ठा nvmet_sq		*sq;
	काष्ठा nvmet_cq		*cq;
	काष्ठा nvmet_ns		*ns;
	काष्ठा scatterlist	*sg;
	काष्ठा scatterlist	*metadata_sg;
	काष्ठा bio_vec		अंतरभूत_bvec[NVMET_MAX_INLINE_BIOVEC];
	जोड़ अणु
		काष्ठा अणु
			काष्ठा bio      अंतरभूत_bio;
		पूर्ण b;
		काष्ठा अणु
			bool			mpool_alloc;
			काष्ठा kiocb            iocb;
			काष्ठा bio_vec          *bvec;
			काष्ठा work_काष्ठा      work;
		पूर्ण f;
		काष्ठा अणु
			काष्ठा bio		अंतरभूत_bio;
			काष्ठा request		*rq;
			काष्ठा work_काष्ठा      work;
			bool			use_workqueue;
		पूर्ण p;
	पूर्ण;
	पूर्णांक			sg_cnt;
	पूर्णांक			metadata_sg_cnt;
	/* data length as parsed from the SGL descriptor: */
	माप_प्रकार			transfer_len;
	माप_प्रकार			metadata_len;

	काष्ठा nvmet_port	*port;

	व्योम (*execute)(काष्ठा nvmet_req *req);
	स्थिर काष्ठा nvmet_fabrics_ops *ops;

	काष्ठा pci_dev		*p2p_dev;
	काष्ठा device		*p2p_client;
	u16			error_loc;
	u64			error_slba;
पूर्ण;

बाह्य काष्ठा workqueue_काष्ठा *buffered_io_wq;

अटल अंतरभूत व्योम nvmet_set_result(काष्ठा nvmet_req *req, u32 result)
अणु
	req->cqe->result.u32 = cpu_to_le32(result);
पूर्ण

/*
 * NVMe command ग_लिखोs actually are DMA पढ़ोs क्रम us on the target side.
 */
अटल अंतरभूत क्रमागत dma_data_direction
nvmet_data_dir(काष्ठा nvmet_req *req)
अणु
	वापस nvme_is_ग_लिखो(req->cmd) ? DMA_FROM_DEVICE : DMA_TO_DEVICE;
पूर्ण

काष्ठा nvmet_async_event अणु
	काष्ठा list_head	entry;
	u8			event_type;
	u8			event_info;
	u8			log_page;
पूर्ण;

अटल अंतरभूत व्योम nvmet_clear_aen_bit(काष्ठा nvmet_req *req, u32 bn)
अणु
	पूर्णांक rae = le32_to_cpu(req->cmd->common.cdw10) & 1 << 15;

	अगर (!rae)
		clear_bit(bn, &req->sq->ctrl->aen_masked);
पूर्ण

अटल अंतरभूत bool nvmet_aen_bit_disabled(काष्ठा nvmet_ctrl *ctrl, u32 bn)
अणु
	अगर (!(READ_ONCE(ctrl->aen_enabled) & (1 << bn)))
		वापस true;
	वापस test_and_set_bit(bn, &ctrl->aen_masked);
पूर्ण

व्योम nvmet_get_feat_kato(काष्ठा nvmet_req *req);
व्योम nvmet_get_feat_async_event(काष्ठा nvmet_req *req);
u16 nvmet_set_feat_kato(काष्ठा nvmet_req *req);
u16 nvmet_set_feat_async_event(काष्ठा nvmet_req *req, u32 mask);
व्योम nvmet_execute_async_event(काष्ठा nvmet_req *req);
व्योम nvmet_start_keep_alive_समयr(काष्ठा nvmet_ctrl *ctrl);
व्योम nvmet_stop_keep_alive_समयr(काष्ठा nvmet_ctrl *ctrl);

u16 nvmet_parse_connect_cmd(काष्ठा nvmet_req *req);
व्योम nvmet_bdev_set_limits(काष्ठा block_device *bdev, काष्ठा nvme_id_ns *id);
u16 nvmet_bdev_parse_io_cmd(काष्ठा nvmet_req *req);
u16 nvmet_file_parse_io_cmd(काष्ठा nvmet_req *req);
u16 nvmet_parse_admin_cmd(काष्ठा nvmet_req *req);
u16 nvmet_parse_discovery_cmd(काष्ठा nvmet_req *req);
u16 nvmet_parse_fabrics_cmd(काष्ठा nvmet_req *req);

bool nvmet_req_init(काष्ठा nvmet_req *req, काष्ठा nvmet_cq *cq,
		काष्ठा nvmet_sq *sq, स्थिर काष्ठा nvmet_fabrics_ops *ops);
व्योम nvmet_req_uninit(काष्ठा nvmet_req *req);
bool nvmet_check_transfer_len(काष्ठा nvmet_req *req, माप_प्रकार len);
bool nvmet_check_data_len_lte(काष्ठा nvmet_req *req, माप_प्रकार data_len);
व्योम nvmet_req_complete(काष्ठा nvmet_req *req, u16 status);
पूर्णांक nvmet_req_alloc_sgls(काष्ठा nvmet_req *req);
व्योम nvmet_req_मुक्त_sgls(काष्ठा nvmet_req *req);

व्योम nvmet_execute_set_features(काष्ठा nvmet_req *req);
व्योम nvmet_execute_get_features(काष्ठा nvmet_req *req);
व्योम nvmet_execute_keep_alive(काष्ठा nvmet_req *req);

व्योम nvmet_cq_setup(काष्ठा nvmet_ctrl *ctrl, काष्ठा nvmet_cq *cq, u16 qid,
		u16 size);
व्योम nvmet_sq_setup(काष्ठा nvmet_ctrl *ctrl, काष्ठा nvmet_sq *sq, u16 qid,
		u16 size);
व्योम nvmet_sq_destroy(काष्ठा nvmet_sq *sq);
पूर्णांक nvmet_sq_init(काष्ठा nvmet_sq *sq);

व्योम nvmet_ctrl_fatal_error(काष्ठा nvmet_ctrl *ctrl);

व्योम nvmet_update_cc(काष्ठा nvmet_ctrl *ctrl, u32 new);
u16 nvmet_alloc_ctrl(स्थिर अक्षर *subsysnqn, स्थिर अक्षर *hostnqn,
		काष्ठा nvmet_req *req, u32 kato, काष्ठा nvmet_ctrl **ctrlp);
काष्ठा nvmet_ctrl *nvmet_ctrl_find_get(स्थिर अक्षर *subsysnqn,
				       स्थिर अक्षर *hostnqn, u16 cntlid,
				       काष्ठा nvmet_req *req);
व्योम nvmet_ctrl_put(काष्ठा nvmet_ctrl *ctrl);
u16 nvmet_check_ctrl_status(काष्ठा nvmet_req *req);

काष्ठा nvmet_subsys *nvmet_subsys_alloc(स्थिर अक्षर *subsysnqn,
		क्रमागत nvme_subsys_type type);
व्योम nvmet_subsys_put(काष्ठा nvmet_subsys *subsys);
व्योम nvmet_subsys_del_ctrls(काष्ठा nvmet_subsys *subsys);

u16 nvmet_req_find_ns(काष्ठा nvmet_req *req);
व्योम nvmet_put_namespace(काष्ठा nvmet_ns *ns);
पूर्णांक nvmet_ns_enable(काष्ठा nvmet_ns *ns);
व्योम nvmet_ns_disable(काष्ठा nvmet_ns *ns);
काष्ठा nvmet_ns *nvmet_ns_alloc(काष्ठा nvmet_subsys *subsys, u32 nsid);
व्योम nvmet_ns_मुक्त(काष्ठा nvmet_ns *ns);

व्योम nvmet_send_ana_event(काष्ठा nvmet_subsys *subsys,
		काष्ठा nvmet_port *port);
व्योम nvmet_port_send_ana_event(काष्ठा nvmet_port *port);

पूर्णांक nvmet_रेजिस्टर_transport(स्थिर काष्ठा nvmet_fabrics_ops *ops);
व्योम nvmet_unरेजिस्टर_transport(स्थिर काष्ठा nvmet_fabrics_ops *ops);

व्योम nvmet_port_del_ctrls(काष्ठा nvmet_port *port,
			  काष्ठा nvmet_subsys *subsys);

पूर्णांक nvmet_enable_port(काष्ठा nvmet_port *port);
व्योम nvmet_disable_port(काष्ठा nvmet_port *port);

व्योम nvmet_referral_enable(काष्ठा nvmet_port *parent, काष्ठा nvmet_port *port);
व्योम nvmet_referral_disable(काष्ठा nvmet_port *parent, काष्ठा nvmet_port *port);

u16 nvmet_copy_to_sgl(काष्ठा nvmet_req *req, off_t off, स्थिर व्योम *buf,
		माप_प्रकार len);
u16 nvmet_copy_from_sgl(काष्ठा nvmet_req *req, off_t off, व्योम *buf,
		माप_प्रकार len);
u16 nvmet_zero_sgl(काष्ठा nvmet_req *req, off_t off, माप_प्रकार len);

u32 nvmet_get_log_page_len(काष्ठा nvme_command *cmd);
u64 nvmet_get_log_page_offset(काष्ठा nvme_command *cmd);

बाह्य काष्ठा list_head *nvmet_ports;
व्योम nvmet_port_disc_changed(काष्ठा nvmet_port *port,
		काष्ठा nvmet_subsys *subsys);
व्योम nvmet_subsys_disc_changed(काष्ठा nvmet_subsys *subsys,
		काष्ठा nvmet_host *host);
व्योम nvmet_add_async_event(काष्ठा nvmet_ctrl *ctrl, u8 event_type,
		u8 event_info, u8 log_page);

#घोषणा NVMET_QUEUE_SIZE	1024
#घोषणा NVMET_NR_QUEUES		128
#घोषणा NVMET_MAX_CMD		NVMET_QUEUE_SIZE

/*
 * Nice round number that makes a list of nsids fit पूर्णांकo a page.
 * Should become tunable at some poपूर्णांक in the future.
 */
#घोषणा NVMET_MAX_NAMESPACES	1024

/*
 * 0 is not a valid ANA group ID, so we start numbering at 1.
 *
 * ANA Group 1 exists without manual पूर्णांकervention, has namespaces asचिन्हित to it
 * by शेष, and is available in an optimized state through all ports.
 */
#घोषणा NVMET_MAX_ANAGRPS	128
#घोषणा NVMET_DEFAULT_ANA_GRPID	1

#घोषणा NVMET_KAS		10
#घोषणा NVMET_DISC_KATO_MS		120000

पूर्णांक __init nvmet_init_configfs(व्योम);
व्योम __निकास nvmet_निकास_configfs(व्योम);

पूर्णांक __init nvmet_init_discovery(व्योम);
व्योम nvmet_निकास_discovery(व्योम);

बाह्य काष्ठा nvmet_subsys *nvmet_disc_subsys;
बाह्य काष्ठा rw_semaphore nvmet_config_sem;

बाह्य u32 nvmet_ana_group_enabled[NVMET_MAX_ANAGRPS + 1];
बाह्य u64 nvmet_ana_chgcnt;
बाह्य काष्ठा rw_semaphore nvmet_ana_sem;

bool nvmet_host_allowed(काष्ठा nvmet_subsys *subsys, स्थिर अक्षर *hostnqn);

पूर्णांक nvmet_bdev_ns_enable(काष्ठा nvmet_ns *ns);
पूर्णांक nvmet_file_ns_enable(काष्ठा nvmet_ns *ns);
व्योम nvmet_bdev_ns_disable(काष्ठा nvmet_ns *ns);
व्योम nvmet_file_ns_disable(काष्ठा nvmet_ns *ns);
u16 nvmet_bdev_flush(काष्ठा nvmet_req *req);
u16 nvmet_file_flush(काष्ठा nvmet_req *req);
व्योम nvmet_ns_changed(काष्ठा nvmet_subsys *subsys, u32 nsid);
व्योम nvmet_bdev_ns_revalidate(काष्ठा nvmet_ns *ns);
पूर्णांक nvmet_file_ns_revalidate(काष्ठा nvmet_ns *ns);
व्योम nvmet_ns_revalidate(काष्ठा nvmet_ns *ns);

अटल अंतरभूत u32 nvmet_rw_data_len(काष्ठा nvmet_req *req)
अणु
	वापस ((u32)le16_to_cpu(req->cmd->rw.length) + 1) <<
			req->ns->blksize_shअगरt;
पूर्ण

अटल अंतरभूत u32 nvmet_rw_metadata_len(काष्ठा nvmet_req *req)
अणु
	अगर (!IS_ENABLED(CONFIG_BLK_DEV_INTEGRITY))
		वापस 0;
	वापस ((u32)le16_to_cpu(req->cmd->rw.length) + 1) *
			req->ns->metadata_size;
पूर्ण

अटल अंतरभूत u32 nvmet_dsm_len(काष्ठा nvmet_req *req)
अणु
	वापस (le32_to_cpu(req->cmd->dsm.nr) + 1) *
		माप(काष्ठा nvme_dsm_range);
पूर्ण

अटल अंतरभूत काष्ठा nvmet_subsys *nvmet_req_subsys(काष्ठा nvmet_req *req)
अणु
	वापस req->sq->ctrl->subsys;
पूर्ण

#अगर_घोषित CONFIG_NVME_TARGET_PASSTHRU
व्योम nvmet_passthru_subsys_मुक्त(काष्ठा nvmet_subsys *subsys);
पूर्णांक nvmet_passthru_ctrl_enable(काष्ठा nvmet_subsys *subsys);
व्योम nvmet_passthru_ctrl_disable(काष्ठा nvmet_subsys *subsys);
u16 nvmet_parse_passthru_admin_cmd(काष्ठा nvmet_req *req);
u16 nvmet_parse_passthru_io_cmd(काष्ठा nvmet_req *req);
अटल अंतरभूत काष्ठा nvme_ctrl *nvmet_passthru_ctrl(काष्ठा nvmet_subsys *subsys)
अणु
	वापस subsys->passthru_ctrl;
पूर्ण
#अन्यथा /* CONFIG_NVME_TARGET_PASSTHRU */
अटल अंतरभूत व्योम nvmet_passthru_subsys_मुक्त(काष्ठा nvmet_subsys *subsys)
अणु
पूर्ण
अटल अंतरभूत व्योम nvmet_passthru_ctrl_disable(काष्ठा nvmet_subsys *subsys)
अणु
पूर्ण
अटल अंतरभूत u16 nvmet_parse_passthru_admin_cmd(काष्ठा nvmet_req *req)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत u16 nvmet_parse_passthru_io_cmd(काष्ठा nvmet_req *req)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत काष्ठा nvme_ctrl *nvmet_passthru_ctrl(काष्ठा nvmet_subsys *subsys)
अणु
	वापस शून्य;
पूर्ण
#पूर्ण_अगर /* CONFIG_NVME_TARGET_PASSTHRU */

अटल अंतरभूत काष्ठा nvme_ctrl *
nvmet_req_passthru_ctrl(काष्ठा nvmet_req *req)
अणु
	वापस nvmet_passthru_ctrl(nvmet_req_subsys(req));
पूर्ण

u16 त्रुटि_सं_to_nvme_status(काष्ठा nvmet_req *req, पूर्णांक त्रुटि_सं);
u16 nvmet_report_invalid_opcode(काष्ठा nvmet_req *req);

/* Convert a 32-bit number to a 16-bit 0's based number */
अटल अंतरभूत __le16 to0based(u32 a)
अणु
	वापस cpu_to_le16(max(1U, min(1U << 16, a)) - 1);
पूर्ण

अटल अंतरभूत bool nvmet_ns_has_pi(काष्ठा nvmet_ns *ns)
अणु
	अगर (!IS_ENABLED(CONFIG_BLK_DEV_INTEGRITY))
		वापस false;
	वापस ns->pi_type && ns->metadata_size == माप(काष्ठा t10_pi_tuple);
पूर्ण

अटल अंतरभूत __le64 nvmet_sect_to_lba(काष्ठा nvmet_ns *ns, sector_t sect)
अणु
	वापस cpu_to_le64(sect >> (ns->blksize_shअगरt - SECTOR_SHIFT));
पूर्ण

अटल अंतरभूत sector_t nvmet_lba_to_sect(काष्ठा nvmet_ns *ns, __le64 lba)
अणु
	वापस le64_to_cpu(lba) << (ns->blksize_shअगरt - SECTOR_SHIFT);
पूर्ण

अटल अंतरभूत bool nvmet_use_अंतरभूत_bvec(काष्ठा nvmet_req *req)
अणु
	वापस req->transfer_len <= NVMET_MAX_INLINE_DATA_LEN &&
	       req->sg_cnt <= NVMET_MAX_INLINE_BIOVEC;
पूर्ण

#पूर्ण_अगर /* _NVMET_H */
