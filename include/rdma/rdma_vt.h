<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR BSD-3-Clause */
/*
 * Copyright(c) 2016 - 2019 Intel Corporation.
 */

#अगर_अघोषित DEF_RDMA_VT_H
#घोषणा DEF_RDMA_VT_H

/*
 * Structure that low level drivers will populate in order to रेजिस्टर with the
 * rdmavt layer.
 */

#समावेश <linux/spinlock.h>
#समावेश <linux/list.h>
#समावेश <linux/hash.h>
#समावेश <rdma/ib_verbs.h>
#समावेश <rdma/ib_mad.h>
#समावेश <rdma/rdmavt_mr.h>

#घोषणा RVT_MAX_PKEY_VALUES 16

#घोषणा RVT_MAX_TRAP_LEN 100 /* Limit pending trap list */
#घोषणा RVT_MAX_TRAP_LISTS 5 /*((IB_NOTICE_TYPE_INFO & 0x0F) + 1)*/
#घोषणा RVT_TRAP_TIMEOUT 4096 /* 4.096 usec */

काष्ठा trap_list अणु
	u32 list_len;
	काष्ठा list_head list;
पूर्ण;

काष्ठा rvt_qp;
काष्ठा rvt_qpn_table;
काष्ठा rvt_ibport अणु
	काष्ठा rvt_qp __rcu *qp[2];
	काष्ठा ib_mad_agent *send_agent;	/* agent क्रम SMI (traps) */
	काष्ठा rb_root mcast_tree;
	spinlock_t lock;		/* protect changes in this काष्ठा */

	/* non-zero when समयr is set */
	अचिन्हित दीर्घ mkey_lease_समयout;
	अचिन्हित दीर्घ trap_समयout;
	__be64 gid_prefix;      /* in network order */
	__be64 mkey;
	u64 tid;
	u32 port_cap_flags;
	u16 port_cap3_flags;
	u32 pma_sample_start;
	u32 pma_sample_पूर्णांकerval;
	__be16 pma_counter_select[5];
	u16 pma_tag;
	u16 mkey_lease_period;
	u32 sm_lid;
	u8 sm_sl;
	u8 mkeyprot;
	u8 subnet_समयout;
	u8 vl_high_limit;

	/*
	 * Driver is expected to keep these up to date. These
	 * counters are inक्रमmational only and not required to be
	 * completely accurate.
	 */
	u64 n_rc_resends;
	u64 n_seq_naks;
	u64 n_rdma_seq;
	u64 n_rnr_naks;
	u64 n_other_naks;
	u64 n_loop_pkts;
	u64 n_pkt_drops;
	u64 n_vl15_dropped;
	u64 n_rc_समयouts;
	u64 n_dmaरुको;
	u64 n_unaligned;
	u64 n_rc_dupreq;
	u64 n_rc_seqnak;
	u64 n_rc_crरुकोs;
	u16 pkey_violations;
	u16 qkey_violations;
	u16 mkey_violations;

	/* Hot-path per CPU counters to aव्योम cacheline trading to update */
	u64 z_rc_acks;
	u64 z_rc_qacks;
	u64 z_rc_delayed_comp;
	u64 __percpu *rc_acks;
	u64 __percpu *rc_qacks;
	u64 __percpu *rc_delayed_comp;

	व्योम *priv; /* driver निजी data */

	/*
	 * The pkey table is allocated and मुख्यtained by the driver. Drivers
	 * need to have access to this beक्रमe रेजिस्टरing with rdmav. However
	 * rdmavt will need access to it so drivers need to provide this during
	 * the attach port API call.
	 */
	u16 *pkey_table;

	काष्ठा rvt_ah *sm_ah;

	/*
	 * Keep a list of traps that have not been repressed.  They will be
	 * resent based on trap_समयr.
	 */
	काष्ठा trap_list trap_lists[RVT_MAX_TRAP_LISTS];
	काष्ठा समयr_list trap_समयr;
पूर्ण;

#घोषणा RVT_CQN_MAX 16 /* maximum length of cq name */

#घोषणा RVT_SGE_COPY_MEMCPY	0
#घोषणा RVT_SGE_COPY_CACHELESS	1
#घोषणा RVT_SGE_COPY_ADAPTIVE	2

/*
 * Things that are driver specअगरic, module parameters in hfi1 and qib
 */
काष्ठा rvt_driver_params अणु
	काष्ठा ib_device_attr props;

	/*
	 * Anything driver specअगरic that is not covered by props
	 * For instance special module parameters. Goes here.
	 */
	अचिन्हित पूर्णांक lkey_table_size;
	अचिन्हित पूर्णांक qp_table_size;
	अचिन्हित पूर्णांक sge_copy_mode;
	अचिन्हित पूर्णांक wss_threshold;
	अचिन्हित पूर्णांक wss_clean_period;
	पूर्णांक qpn_start;
	पूर्णांक qpn_inc;
	पूर्णांक qpn_res_start;
	पूर्णांक qpn_res_end;
	पूर्णांक nports;
	पूर्णांक npkeys;
	पूर्णांक node;
	पूर्णांक psn_mask;
	पूर्णांक psn_shअगरt;
	पूर्णांक psn_modअगरy_mask;
	u32 core_cap_flags;
	u32 max_mad_size;
	u8 qos_shअगरt;
	u8 max_rdma_atomic;
	u8 extra_rdma_atomic;
	u8 reserved_operations;
पूर्ण;

/* User context */
काष्ठा rvt_ucontext अणु
	काष्ठा ib_ucontext ibucontext;
पूर्ण;

/* Protection करोमुख्य */
काष्ठा rvt_pd अणु
	काष्ठा ib_pd ibpd;
	bool user;
पूर्ण;

/* Address handle */
काष्ठा rvt_ah अणु
	काष्ठा ib_ah ibah;
	काष्ठा rdma_ah_attr attr;
	u8 vl;
	u8 log_pmtu;
पूर्ण;

/*
 * This काष्ठाure is used by rvt_mmap() to validate an offset
 * when an mmap() request is made.  The vm_area_काष्ठा then uses
 * this as its vm_निजी_data.
 */
काष्ठा rvt_mmap_info अणु
	काष्ठा list_head pending_mmaps;
	काष्ठा ib_ucontext *context;
	व्योम *obj;
	__u64 offset;
	काष्ठा kref ref;
	u32 size;
पूर्ण;

/* memory working set size */
काष्ठा rvt_wss अणु
	अचिन्हित दीर्घ *entries;
	atomic_t total_count;
	atomic_t clean_counter;
	atomic_t clean_entry;

	पूर्णांक threshold;
	पूर्णांक num_entries;
	दीर्घ pages_mask;
	अचिन्हित पूर्णांक clean_period;
पूर्ण;

काष्ठा rvt_dev_info;
काष्ठा rvt_swqe;
काष्ठा rvt_driver_provided अणु
	/*
	 * Which functions are required depends on which verbs rdmavt is
	 * providing and which verbs the driver is overriding. See
	 * check_support() क्रम details.
	 */

	/* hot path callकरोwns in a single cacheline */

	/*
	 * Give the driver a notice that there is send work to करो. It is up to
	 * the driver to generally push the packets out, this just queues the
	 * work with the driver. There are two variants here. The no_lock
	 * version requires the s_lock not to be held. The other assumes the
	 * s_lock is held.
	 */
	bool (*schedule_send)(काष्ठा rvt_qp *qp);
	bool (*schedule_send_no_lock)(काष्ठा rvt_qp *qp);

	/*
	 * Driver specअगरic work request setup and checking.
	 * This function is allowed to perक्रमm any setup, checks, or
	 * adjusपंचांगents required to the SWQE in order to be usable by
	 * underlying protocols. This includes निजी data काष्ठाure
	 * allocations.
	 */
	पूर्णांक (*setup_wqe)(काष्ठा rvt_qp *qp, काष्ठा rvt_swqe *wqe,
			 bool *call_send);

	/*
	 * Someबार rdmavt needs to kick the driver's send progress. That is
	 * करोne by this call back.
	 */
	व्योम (*करो_send)(काष्ठा rvt_qp *qp);

	/*
	 * Returns a poपूर्णांकer to the underlying hardware's PCI device. This is
	 * used to display inक्रमmation as to what hardware is being referenced
	 * in an output message
	 */
	काष्ठा pci_dev * (*get_pci_dev)(काष्ठा rvt_dev_info *rdi);

	/*
	 * Allocate a निजी queue pair data काष्ठाure क्रम driver specअगरic
	 * inक्रमmation which is opaque to rdmavt.  Errors are वापसed via
	 * ERR_PTR(err).  The driver is मुक्त to वापस शून्य or a valid
	 * poपूर्णांकer.
	 */
	व्योम * (*qp_priv_alloc)(काष्ठा rvt_dev_info *rdi, काष्ठा rvt_qp *qp);

	/*
	 * Init a काष्ठाure allocated with qp_priv_alloc(). This should be
	 * called after all qp fields have been initialized in rdmavt.
	 */
	पूर्णांक (*qp_priv_init)(काष्ठा rvt_dev_info *rdi, काष्ठा rvt_qp *qp,
			    काष्ठा ib_qp_init_attr *init_attr);

	/*
	 * Free the driver's निजी qp काष्ठाure.
	 */
	व्योम (*qp_priv_मुक्त)(काष्ठा rvt_dev_info *rdi, काष्ठा rvt_qp *qp);

	/*
	 * Inक्रमm the driver the particular qp in question has been reset so
	 * that it can clean up anything it needs to.
	 */
	व्योम (*notअगरy_qp_reset)(काष्ठा rvt_qp *qp);

	/*
	 * Get a path mtu from the driver based on qp attributes.
	 */
	पूर्णांक (*get_pmtu_from_attr)(काष्ठा rvt_dev_info *rdi, काष्ठा rvt_qp *qp,
				  काष्ठा ib_qp_attr *attr);

	/*
	 * Notअगरy driver that it needs to flush any outstanding IO requests that
	 * are रुकोing on a qp.
	 */
	व्योम (*flush_qp_रुकोers)(काष्ठा rvt_qp *qp);

	/*
	 * Notअगरy driver to stop its queue of sending packets. Nothing अन्यथा
	 * should be posted to the queue pair after this has been called.
	 */
	व्योम (*stop_send_queue)(काष्ठा rvt_qp *qp);

	/*
	 * Have the driver drain any in progress operations
	 */
	व्योम (*quiesce_qp)(काष्ठा rvt_qp *qp);

	/*
	 * Inक्रमm the driver a qp has went to error state.
	 */
	व्योम (*notअगरy_error_qp)(काष्ठा rvt_qp *qp);

	/*
	 * Get an MTU क्रम a qp.
	 */
	u32 (*mtu_from_qp)(काष्ठा rvt_dev_info *rdi, काष्ठा rvt_qp *qp,
			   u32 pmtu);
	/*
	 * Convert an mtu to a path mtu
	 */
	पूर्णांक (*mtu_to_path_mtu)(u32 mtu);

	/*
	 * Get the guid of a port in big endian byte order
	 */
	पूर्णांक (*get_guid_be)(काष्ठा rvt_dev_info *rdi, काष्ठा rvt_ibport *rvp,
			   पूर्णांक guid_index, __be64 *guid);

	/*
	 * Query driver क्रम the state of the port.
	 */
	पूर्णांक (*query_port_state)(काष्ठा rvt_dev_info *rdi, u32 port_num,
				काष्ठा ib_port_attr *props);

	/*
	 * Tell driver to shutकरोwn a port
	 */
	पूर्णांक (*shut_करोwn_port)(काष्ठा rvt_dev_info *rdi, u32 port_num);

	/* Tell driver to send a trap क्रम changed  port capabilities */
	व्योम (*cap_mask_chg)(काष्ठा rvt_dev_info *rdi, u32 port_num);

	/*
	 * The following functions can be safely ignored completely. Any use of
	 * these is checked क्रम शून्य beक्रमe blindly calling. Rdmavt should also
	 * be functional अगर drivers omit these.
	 */

	/* Called to inक्रमm the driver that all qps should now be मुक्तd. */
	अचिन्हित (*मुक्त_all_qps)(काष्ठा rvt_dev_info *rdi);

	/* Driver specअगरic AH validation */
	पूर्णांक (*check_ah)(काष्ठा ib_device *, काष्ठा rdma_ah_attr *);

	/* Inक्रमm the driver a new AH has been created */
	व्योम (*notअगरy_new_ah)(काष्ठा ib_device *, काष्ठा rdma_ah_attr *,
			      काष्ठा rvt_ah *);

	/* Let the driver pick the next queue pair number*/
	पूर्णांक (*alloc_qpn)(काष्ठा rvt_dev_info *rdi, काष्ठा rvt_qpn_table *qpt,
			 क्रमागत ib_qp_type type, u32 port_num);

	/* Determine अगर its safe or allowed to modअगरy the qp */
	पूर्णांक (*check_modअगरy_qp)(काष्ठा rvt_qp *qp, काष्ठा ib_qp_attr *attr,
			       पूर्णांक attr_mask, काष्ठा ib_udata *udata);

	/* Driver specअगरic QP modअगरication/notअगरication-of */
	व्योम (*modअगरy_qp)(काष्ठा rvt_qp *qp, काष्ठा ib_qp_attr *attr,
			  पूर्णांक attr_mask, काष्ठा ib_udata *udata);

	/* Notअगरy driver a mad agent has been created */
	व्योम (*notअगरy_create_mad_agent)(काष्ठा rvt_dev_info *rdi, पूर्णांक port_idx);

	/* Notअगरy driver a mad agent has been हटाओd */
	व्योम (*notअगरy_मुक्त_mad_agent)(काष्ठा rvt_dev_info *rdi, पूर्णांक port_idx);

	/* Notअगरy driver to restart rc */
	व्योम (*notअगरy_restart_rc)(काष्ठा rvt_qp *qp, u32 psn, पूर्णांक रुको);

	/* Get and वापस CPU to pin CQ processing thपढ़ो */
	पूर्णांक (*comp_vect_cpu_lookup)(काष्ठा rvt_dev_info *rdi, पूर्णांक comp_vect);
पूर्ण;

काष्ठा rvt_dev_info अणु
	काष्ठा ib_device ibdev; /* Keep this first. Nothing above here */

	/*
	 * Prior to calling क्रम registration the driver will be responsible क्रम
	 * allocating space क्रम this काष्ठाure.
	 *
	 * The driver will also be responsible क्रम filling in certain members of
	 * dparms.props. The driver needs to fill in dparms exactly as it would
	 * want values reported to a ULP. This will be वापसed to the caller
	 * in rdmavt's device. The driver should also thereक्रमe refrain from
	 * modअगरying this directly after registration with rdmavt.
	 */

	/* Driver specअगरic properties */
	काष्ठा rvt_driver_params dparms;

	/* post send table */
	स्थिर काष्ठा rvt_operation_params *post_parms;

	/* opcode translation table */
	स्थिर क्रमागत ib_wc_opcode *wc_opcode;

	/* Driver specअगरic helper functions */
	काष्ठा rvt_driver_provided driver_f;

	काष्ठा rvt_mregion __rcu *dma_mr;
	काष्ठा rvt_lkey_table lkey_table;

	/* Internal use */
	पूर्णांक n_pds_allocated;
	spinlock_t n_pds_lock; /* Protect pd allocated count */

	पूर्णांक n_ahs_allocated;
	spinlock_t n_ahs_lock; /* Protect ah allocated count */

	u32 n_srqs_allocated;
	spinlock_t n_srqs_lock; /* Protect srqs allocated count */

	पूर्णांक flags;
	काष्ठा rvt_ibport **ports;

	/* QP */
	काष्ठा rvt_qp_ibdev *qp_dev;
	u32 n_qps_allocated;    /* number of QPs allocated क्रम device */
	u32 n_rc_qps;		/* number of RC QPs allocated क्रम device */
	u32 busy_jअगरfies;	/* समयout scaling based on RC QP count */
	spinlock_t n_qps_lock;	/* protect qps, rc qps and busy jअगरfy counts */

	/* memory maps */
	काष्ठा list_head pending_mmaps;
	spinlock_t mmap_offset_lock; /* protect mmap_offset */
	u32 mmap_offset;
	spinlock_t pending_lock; /* protect pending mmap list */

	/* CQ */
	u32 n_cqs_allocated;    /* number of CQs allocated क्रम device */
	spinlock_t n_cqs_lock; /* protect count of in use cqs */

	/* Multicast */
	u32 n_mcast_grps_allocated; /* number of mcast groups allocated */
	spinlock_t n_mcast_grps_lock;

	/* Memory Working Set Size */
	काष्ठा rvt_wss *wss;
पूर्ण;

/**
 * rvt_set_ibdev_name - Craft an IB device name from client info
 * @rdi: poपूर्णांकer to the client rvt_dev_info काष्ठाure
 * @name: client specअगरic name
 * @unit: client specअगरic unit number.
 */
अटल अंतरभूत व्योम rvt_set_ibdev_name(काष्ठा rvt_dev_info *rdi,
				      स्थिर अक्षर *fmt, स्थिर अक्षर *name,
				      स्थिर पूर्णांक unit)
अणु
	/*
	 * FIXME: rvt and its users want to touch the ibdev beक्रमe
	 * registration and have things like the name work. We करोn't have the
	 * infraकाष्ठाure in the core to support this directly today, hack it
	 * to work by setting the name manually here.
	 */
	dev_set_name(&rdi->ibdev.dev, fmt, name, unit);
	strlcpy(rdi->ibdev.name, dev_name(&rdi->ibdev.dev), IB_DEVICE_NAME_MAX);
पूर्ण

/**
 * rvt_get_ibdev_name - वापस the IB name
 * @rdi: rdmavt device
 *
 * Return the रेजिस्टरed name of the device.
 */
अटल अंतरभूत स्थिर अक्षर *rvt_get_ibdev_name(स्थिर काष्ठा rvt_dev_info *rdi)
अणु
	वापस dev_name(&rdi->ibdev.dev);
पूर्ण

अटल अंतरभूत काष्ठा rvt_pd *ibpd_to_rvtpd(काष्ठा ib_pd *ibpd)
अणु
	वापस container_of(ibpd, काष्ठा rvt_pd, ibpd);
पूर्ण

अटल अंतरभूत काष्ठा rvt_ah *ibah_to_rvtah(काष्ठा ib_ah *ibah)
अणु
	वापस container_of(ibah, काष्ठा rvt_ah, ibah);
पूर्ण

अटल अंतरभूत काष्ठा rvt_dev_info *ib_to_rvt(काष्ठा ib_device *ibdev)
अणु
	वापस  container_of(ibdev, काष्ठा rvt_dev_info, ibdev);
पूर्ण

अटल अंतरभूत अचिन्हित rvt_get_npkeys(काष्ठा rvt_dev_info *rdi)
अणु
	/*
	 * All ports have same number of pkeys.
	 */
	वापस rdi->dparms.npkeys;
पूर्ण

/*
 * Return the max atomic suitable क्रम determining
 * the size of the ack ring buffer in a QP.
 */
अटल अंतरभूत अचिन्हित पूर्णांक rvt_max_atomic(काष्ठा rvt_dev_info *rdi)
अणु
	वापस rdi->dparms.max_rdma_atomic +
		rdi->dparms.extra_rdma_atomic + 1;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक rvt_size_atomic(काष्ठा rvt_dev_info *rdi)
अणु
	वापस rdi->dparms.max_rdma_atomic +
		rdi->dparms.extra_rdma_atomic;
पूर्ण

/*
 * Return the indexed PKEY from the port PKEY table.
 */
अटल अंतरभूत u16 rvt_get_pkey(काष्ठा rvt_dev_info *rdi,
			       पूर्णांक port_index,
			       अचिन्हित index)
अणु
	अगर (index >= rvt_get_npkeys(rdi))
		वापस 0;
	अन्यथा
		वापस rdi->ports[port_index]->pkey_table[index];
पूर्ण

काष्ठा rvt_dev_info *rvt_alloc_device(माप_प्रकार size, पूर्णांक nports);
व्योम rvt_dealloc_device(काष्ठा rvt_dev_info *rdi);
पूर्णांक rvt_रेजिस्टर_device(काष्ठा rvt_dev_info *rvd);
व्योम rvt_unरेजिस्टर_device(काष्ठा rvt_dev_info *rvd);
पूर्णांक rvt_check_ah(काष्ठा ib_device *ibdev, काष्ठा rdma_ah_attr *ah_attr);
पूर्णांक rvt_init_port(काष्ठा rvt_dev_info *rdi, काष्ठा rvt_ibport *port,
		  पूर्णांक port_index, u16 *pkey_table);
पूर्णांक rvt_fast_reg_mr(काष्ठा rvt_qp *qp, काष्ठा ib_mr *ibmr, u32 key,
		    पूर्णांक access);
पूर्णांक rvt_invalidate_rkey(काष्ठा rvt_qp *qp, u32 rkey);
पूर्णांक rvt_rkey_ok(काष्ठा rvt_qp *qp, काष्ठा rvt_sge *sge,
		u32 len, u64 vaddr, u32 rkey, पूर्णांक acc);
पूर्णांक rvt_lkey_ok(काष्ठा rvt_lkey_table *rkt, काष्ठा rvt_pd *pd,
		काष्ठा rvt_sge *isge, काष्ठा rvt_sge *last_sge,
		काष्ठा ib_sge *sge, पूर्णांक acc);
काष्ठा rvt_mcast *rvt_mcast_find(काष्ठा rvt_ibport *ibp, जोड़ ib_gid *mgid,
				 u16 lid);

#पूर्ण_अगर          /* DEF_RDMA_VT_H */
