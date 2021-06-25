<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright(c) 2019 Intel Corporation. All rights rsvd. */
#अगर_अघोषित _IDXD_H_
#घोषणा _IDXD_H_

#समावेश <linux/sbiपंचांगap.h>
#समावेश <linux/dmaengine.h>
#समावेश <linux/percpu-rwsem.h>
#समावेश <linux/रुको.h>
#समावेश <linux/cdev.h>
#समावेश <linux/idr.h>
#समावेश <linux/pci.h>
#समावेश <linux/perf_event.h>
#समावेश "registers.h"

#घोषणा IDXD_DRIVER_VERSION	"1.00"

बाह्य काष्ठा kmem_cache *idxd_desc_pool;

काष्ठा idxd_device;
काष्ठा idxd_wq;

#घोषणा IDXD_REG_TIMEOUT	50
#घोषणा IDXD_DRAIN_TIMEOUT	5000

क्रमागत idxd_type अणु
	IDXD_TYPE_UNKNOWN = -1,
	IDXD_TYPE_DSA = 0,
	IDXD_TYPE_IAX,
	IDXD_TYPE_MAX,
पूर्ण;

#घोषणा IDXD_NAME_SIZE		128
#घोषणा IDXD_PMU_EVENT_MAX	64

काष्ठा idxd_device_driver अणु
	काष्ठा device_driver drv;
पूर्ण;

काष्ठा idxd_irq_entry अणु
	काष्ठा idxd_device *idxd;
	पूर्णांक id;
	पूर्णांक vector;
	काष्ठा llist_head pending_llist;
	काष्ठा list_head work_list;
	/*
	 * Lock to protect access between irq thपढ़ो process descriptor
	 * and irq thपढ़ो processing error descriptor.
	 */
	spinlock_t list_lock;
पूर्ण;

काष्ठा idxd_group अणु
	काष्ठा device conf_dev;
	काष्ठा idxd_device *idxd;
	काष्ठा grpcfg grpcfg;
	पूर्णांक id;
	पूर्णांक num_engines;
	पूर्णांक num_wqs;
	bool use_token_limit;
	u8 tokens_allowed;
	u8 tokens_reserved;
	पूर्णांक tc_a;
	पूर्णांक tc_b;
पूर्ण;

काष्ठा idxd_pmu अणु
	काष्ठा idxd_device *idxd;

	काष्ठा perf_event *event_list[IDXD_PMU_EVENT_MAX];
	पूर्णांक n_events;

	DECLARE_BITMAP(used_mask, IDXD_PMU_EVENT_MAX);

	काष्ठा pmu pmu;
	अक्षर name[IDXD_NAME_SIZE];
	पूर्णांक cpu;

	पूर्णांक n_counters;
	पूर्णांक counter_width;
	पूर्णांक n_event_categories;

	bool per_counter_caps_supported;
	अचिन्हित दीर्घ supported_event_categories;

	अचिन्हित दीर्घ supported_filters;
	पूर्णांक n_filters;

	काष्ठा hlist_node cpuhp_node;
पूर्ण;

#घोषणा IDXD_MAX_PRIORITY	0xf

क्रमागत idxd_wq_state अणु
	IDXD_WQ_DISABLED = 0,
	IDXD_WQ_ENABLED,
पूर्ण;

क्रमागत idxd_wq_flag अणु
	WQ_FLAG_DEDICATED = 0,
	WQ_FLAG_BLOCK_ON_FAULT,
पूर्ण;

क्रमागत idxd_wq_type अणु
	IDXD_WQT_NONE = 0,
	IDXD_WQT_KERNEL,
	IDXD_WQT_USER,
पूर्ण;

काष्ठा idxd_cdev अणु
	काष्ठा idxd_wq *wq;
	काष्ठा cdev cdev;
	काष्ठा device dev;
	पूर्णांक minor;
पूर्ण;

#घोषणा IDXD_ALLOCATED_BATCH_SIZE	128U
#घोषणा WQ_NAME_SIZE   1024
#घोषणा WQ_TYPE_SIZE   10

क्रमागत idxd_op_type अणु
	IDXD_OP_BLOCK = 0,
	IDXD_OP_NONBLOCK = 1,
पूर्ण;

क्रमागत idxd_complete_type अणु
	IDXD_COMPLETE_NORMAL = 0,
	IDXD_COMPLETE_ABORT,
	IDXD_COMPLETE_DEV_FAIL,
पूर्ण;

काष्ठा idxd_dma_chan अणु
	काष्ठा dma_chan chan;
	काष्ठा idxd_wq *wq;
पूर्ण;

काष्ठा idxd_wq अणु
	व्योम __iomem *portal;
	काष्ठा percpu_ref wq_active;
	काष्ठा completion wq_dead;
	काष्ठा device conf_dev;
	काष्ठा idxd_cdev *idxd_cdev;
	काष्ठा रुको_queue_head err_queue;
	काष्ठा idxd_device *idxd;
	पूर्णांक id;
	क्रमागत idxd_wq_type type;
	काष्ठा idxd_group *group;
	पूर्णांक client_count;
	काष्ठा mutex wq_lock;	/* mutex क्रम workqueue */
	u32 size;
	u32 threshold;
	u32 priority;
	क्रमागत idxd_wq_state state;
	अचिन्हित दीर्घ flags;
	जोड़ wqcfg *wqcfg;
	u32 vec_ptr;		/* पूर्णांकerrupt steering */
	काष्ठा dsa_hw_desc **hw_descs;
	पूर्णांक num_descs;
	जोड़ अणु
		काष्ठा dsa_completion_record *compls;
		काष्ठा iax_completion_record *iax_compls;
	पूर्ण;
	व्योम *compls_raw;
	dma_addr_t compls_addr;
	dma_addr_t compls_addr_raw;
	पूर्णांक compls_size;
	काष्ठा idxd_desc **descs;
	काष्ठा sbiपंचांगap_queue sbq;
	काष्ठा idxd_dma_chan *idxd_chan;
	अक्षर name[WQ_NAME_SIZE + 1];
	u64 max_xfer_bytes;
	u32 max_batch_size;
	bool ats_dis;
पूर्ण;

काष्ठा idxd_engine अणु
	काष्ठा device conf_dev;
	पूर्णांक id;
	काष्ठा idxd_group *group;
	काष्ठा idxd_device *idxd;
पूर्ण;

/* shaकरोw रेजिस्टरs */
काष्ठा idxd_hw अणु
	u32 version;
	जोड़ gen_cap_reg gen_cap;
	जोड़ wq_cap_reg wq_cap;
	जोड़ group_cap_reg group_cap;
	जोड़ engine_cap_reg engine_cap;
	काष्ठा opcap opcap;
	u32 cmd_cap;
पूर्ण;

क्रमागत idxd_device_state अणु
	IDXD_DEV_HALTED = -1,
	IDXD_DEV_DISABLED = 0,
	IDXD_DEV_CONF_READY,
	IDXD_DEV_ENABLED,
पूर्ण;

क्रमागत idxd_device_flag अणु
	IDXD_FLAG_CONFIGURABLE = 0,
	IDXD_FLAG_CMD_RUNNING,
	IDXD_FLAG_PASID_ENABLED,
पूर्ण;

काष्ठा idxd_dma_dev अणु
	काष्ठा idxd_device *idxd;
	काष्ठा dma_device dma;
पूर्ण;

काष्ठा idxd_driver_data अणु
	स्थिर अक्षर *name_prefix;
	क्रमागत idxd_type type;
	काष्ठा device_type *dev_type;
	पूर्णांक compl_size;
	पूर्णांक align;
पूर्ण;

काष्ठा idxd_device अणु
	काष्ठा device conf_dev;
	काष्ठा idxd_driver_data *data;
	काष्ठा list_head list;
	काष्ठा idxd_hw hw;
	क्रमागत idxd_device_state state;
	अचिन्हित दीर्घ flags;
	पूर्णांक id;
	पूर्णांक major;
	u8 cmd_status;

	काष्ठा pci_dev *pdev;
	व्योम __iomem *reg_base;

	spinlock_t dev_lock;	/* spinlock क्रम device */
	spinlock_t cmd_lock;	/* spinlock क्रम device commands */
	काष्ठा completion *cmd_करोne;
	काष्ठा idxd_group **groups;
	काष्ठा idxd_wq **wqs;
	काष्ठा idxd_engine **engines;

	काष्ठा iommu_sva *sva;
	अचिन्हित पूर्णांक pasid;

	पूर्णांक num_groups;

	u32 msix_perm_offset;
	u32 wqcfg_offset;
	u32 grpcfg_offset;
	u32 perfmon_offset;

	u64 max_xfer_bytes;
	u32 max_batch_size;
	पूर्णांक max_groups;
	पूर्णांक max_engines;
	पूर्णांक max_tokens;
	पूर्णांक max_wqs;
	पूर्णांक max_wq_size;
	पूर्णांक token_limit;
	पूर्णांक nr_tokens;		/* non-reserved tokens */
	अचिन्हित पूर्णांक wqcfg_size;

	जोड़ sw_err_reg sw_err;
	रुको_queue_head_t cmd_रुकोq;
	पूर्णांक num_wq_irqs;
	काष्ठा idxd_irq_entry *irq_entries;

	काष्ठा idxd_dma_dev *idxd_dma;
	काष्ठा workqueue_काष्ठा *wq;
	काष्ठा work_काष्ठा work;

	पूर्णांक *पूर्णांक_handles;

	काष्ठा idxd_pmu *idxd_pmu;
पूर्ण;

/* IDXD software descriptor */
काष्ठा idxd_desc अणु
	जोड़ अणु
		काष्ठा dsa_hw_desc *hw;
		काष्ठा iax_hw_desc *iax_hw;
	पूर्ण;
	dma_addr_t desc_dma;
	जोड़ अणु
		काष्ठा dsa_completion_record *completion;
		काष्ठा iax_completion_record *iax_completion;
	पूर्ण;
	dma_addr_t compl_dma;
	काष्ठा dma_async_tx_descriptor txd;
	काष्ठा llist_node llnode;
	काष्ठा list_head list;
	पूर्णांक id;
	पूर्णांक cpu;
	अचिन्हित पूर्णांक vector;
	काष्ठा idxd_wq *wq;
पूर्ण;

#घोषणा confdev_to_idxd(dev) container_of(dev, काष्ठा idxd_device, conf_dev)
#घोषणा confdev_to_wq(dev) container_of(dev, काष्ठा idxd_wq, conf_dev)

बाह्य काष्ठा bus_type dsa_bus_type;
बाह्य काष्ठा bus_type iax_bus_type;

बाह्य bool support_enqcmd;
बाह्य काष्ठा ida idxd_ida;
बाह्य काष्ठा device_type dsa_device_type;
बाह्य काष्ठा device_type iax_device_type;
बाह्य काष्ठा device_type idxd_wq_device_type;
बाह्य काष्ठा device_type idxd_engine_device_type;
बाह्य काष्ठा device_type idxd_group_device_type;

अटल अंतरभूत bool is_dsa_dev(काष्ठा device *dev)
अणु
	वापस dev->type == &dsa_device_type;
पूर्ण

अटल अंतरभूत bool is_iax_dev(काष्ठा device *dev)
अणु
	वापस dev->type == &iax_device_type;
पूर्ण

अटल अंतरभूत bool is_idxd_dev(काष्ठा device *dev)
अणु
	वापस is_dsa_dev(dev) || is_iax_dev(dev);
पूर्ण

अटल अंतरभूत bool is_idxd_wq_dev(काष्ठा device *dev)
अणु
	वापस dev->type == &idxd_wq_device_type;
पूर्ण

अटल अंतरभूत bool is_idxd_wq_dmaengine(काष्ठा idxd_wq *wq)
अणु
	अगर (wq->type == IDXD_WQT_KERNEL && म_भेद(wq->name, "dmaengine") == 0)
		वापस true;
	वापस false;
पूर्ण

अटल अंतरभूत bool is_idxd_wq_cdev(काष्ठा idxd_wq *wq)
अणु
	वापस wq->type == IDXD_WQT_USER;
पूर्ण

अटल अंतरभूत bool wq_dedicated(काष्ठा idxd_wq *wq)
अणु
	वापस test_bit(WQ_FLAG_DEDICATED, &wq->flags);
पूर्ण

अटल अंतरभूत bool wq_shared(काष्ठा idxd_wq *wq)
अणु
	वापस !test_bit(WQ_FLAG_DEDICATED, &wq->flags);
पूर्ण

अटल अंतरभूत bool device_pasid_enabled(काष्ठा idxd_device *idxd)
अणु
	वापस test_bit(IDXD_FLAG_PASID_ENABLED, &idxd->flags);
पूर्ण

अटल अंतरभूत bool device_swq_supported(काष्ठा idxd_device *idxd)
अणु
	वापस (support_enqcmd && device_pasid_enabled(idxd));
पूर्ण

क्रमागत idxd_portal_prot अणु
	IDXD_PORTAL_UNLIMITED = 0,
	IDXD_PORTAL_LIMITED,
पूर्ण;

क्रमागत idxd_पूर्णांकerrupt_type अणु
	IDXD_IRQ_MSIX = 0,
	IDXD_IRQ_IMS,
पूर्ण;

अटल अंतरभूत पूर्णांक idxd_get_wq_portal_offset(क्रमागत idxd_portal_prot prot)
अणु
	वापस prot * 0x1000;
पूर्ण

अटल अंतरभूत पूर्णांक idxd_get_wq_portal_full_offset(पूर्णांक wq_id,
						 क्रमागत idxd_portal_prot prot)
अणु
	वापस ((wq_id * 4) << PAGE_SHIFT) + idxd_get_wq_portal_offset(prot);
पूर्ण

अटल अंतरभूत व्योम idxd_wq_get(काष्ठा idxd_wq *wq)
अणु
	wq->client_count++;
पूर्ण

अटल अंतरभूत व्योम idxd_wq_put(काष्ठा idxd_wq *wq)
अणु
	wq->client_count--;
पूर्ण

अटल अंतरभूत पूर्णांक idxd_wq_refcount(काष्ठा idxd_wq *wq)
अणु
	वापस wq->client_count;
पूर्ण;

पूर्णांक idxd_रेजिस्टर_bus_type(व्योम);
व्योम idxd_unरेजिस्टर_bus_type(व्योम);
पूर्णांक idxd_रेजिस्टर_devices(काष्ठा idxd_device *idxd);
व्योम idxd_unरेजिस्टर_devices(काष्ठा idxd_device *idxd);
पूर्णांक idxd_रेजिस्टर_driver(व्योम);
व्योम idxd_unरेजिस्टर_driver(व्योम);
व्योम idxd_wqs_quiesce(काष्ठा idxd_device *idxd);

/* device पूर्णांकerrupt control */
व्योम idxd_msix_perm_setup(काष्ठा idxd_device *idxd);
व्योम idxd_msix_perm_clear(काष्ठा idxd_device *idxd);
irqवापस_t idxd_misc_thपढ़ो(पूर्णांक vec, व्योम *data);
irqवापस_t idxd_wq_thपढ़ो(पूर्णांक irq, व्योम *data);
व्योम idxd_mask_error_पूर्णांकerrupts(काष्ठा idxd_device *idxd);
व्योम idxd_unmask_error_पूर्णांकerrupts(काष्ठा idxd_device *idxd);
व्योम idxd_mask_msix_vectors(काष्ठा idxd_device *idxd);
व्योम idxd_mask_msix_vector(काष्ठा idxd_device *idxd, पूर्णांक vec_id);
व्योम idxd_unmask_msix_vector(काष्ठा idxd_device *idxd, पूर्णांक vec_id);

/* device control */
पूर्णांक idxd_device_init_reset(काष्ठा idxd_device *idxd);
पूर्णांक idxd_device_enable(काष्ठा idxd_device *idxd);
पूर्णांक idxd_device_disable(काष्ठा idxd_device *idxd);
व्योम idxd_device_reset(काष्ठा idxd_device *idxd);
व्योम idxd_device_cleanup(काष्ठा idxd_device *idxd);
पूर्णांक idxd_device_config(काष्ठा idxd_device *idxd);
व्योम idxd_device_wqs_clear_state(काष्ठा idxd_device *idxd);
व्योम idxd_device_drain_pasid(काष्ठा idxd_device *idxd, पूर्णांक pasid);
पूर्णांक idxd_device_load_config(काष्ठा idxd_device *idxd);
पूर्णांक idxd_device_request_पूर्णांक_handle(काष्ठा idxd_device *idxd, पूर्णांक idx, पूर्णांक *handle,
				   क्रमागत idxd_पूर्णांकerrupt_type irq_type);
पूर्णांक idxd_device_release_पूर्णांक_handle(काष्ठा idxd_device *idxd, पूर्णांक handle,
				   क्रमागत idxd_पूर्णांकerrupt_type irq_type);

/* work queue control */
व्योम idxd_wqs_unmap_portal(काष्ठा idxd_device *idxd);
पूर्णांक idxd_wq_alloc_resources(काष्ठा idxd_wq *wq);
व्योम idxd_wq_मुक्त_resources(काष्ठा idxd_wq *wq);
पूर्णांक idxd_wq_enable(काष्ठा idxd_wq *wq);
पूर्णांक idxd_wq_disable(काष्ठा idxd_wq *wq);
व्योम idxd_wq_drain(काष्ठा idxd_wq *wq);
व्योम idxd_wq_reset(काष्ठा idxd_wq *wq);
पूर्णांक idxd_wq_map_portal(काष्ठा idxd_wq *wq);
व्योम idxd_wq_unmap_portal(काष्ठा idxd_wq *wq);
व्योम idxd_wq_disable_cleanup(काष्ठा idxd_wq *wq);
पूर्णांक idxd_wq_set_pasid(काष्ठा idxd_wq *wq, पूर्णांक pasid);
पूर्णांक idxd_wq_disable_pasid(काष्ठा idxd_wq *wq);
व्योम idxd_wq_quiesce(काष्ठा idxd_wq *wq);
पूर्णांक idxd_wq_init_percpu_ref(काष्ठा idxd_wq *wq);

/* submission */
पूर्णांक idxd_submit_desc(काष्ठा idxd_wq *wq, काष्ठा idxd_desc *desc);
काष्ठा idxd_desc *idxd_alloc_desc(काष्ठा idxd_wq *wq, क्रमागत idxd_op_type optype);
व्योम idxd_मुक्त_desc(काष्ठा idxd_wq *wq, काष्ठा idxd_desc *desc);

/* dmaengine */
पूर्णांक idxd_रेजिस्टर_dma_device(काष्ठा idxd_device *idxd);
व्योम idxd_unरेजिस्टर_dma_device(काष्ठा idxd_device *idxd);
पूर्णांक idxd_रेजिस्टर_dma_channel(काष्ठा idxd_wq *wq);
व्योम idxd_unरेजिस्टर_dma_channel(काष्ठा idxd_wq *wq);
व्योम idxd_parse_completion_status(u8 status, क्रमागत dmaengine_tx_result *res);
व्योम idxd_dma_complete_txd(काष्ठा idxd_desc *desc,
			   क्रमागत idxd_complete_type comp_type);

/* cdev */
पूर्णांक idxd_cdev_रेजिस्टर(व्योम);
व्योम idxd_cdev_हटाओ(व्योम);
पूर्णांक idxd_cdev_get_major(काष्ठा idxd_device *idxd);
पूर्णांक idxd_wq_add_cdev(काष्ठा idxd_wq *wq);
व्योम idxd_wq_del_cdev(काष्ठा idxd_wq *wq);

/* perfmon */
#अगर IS_ENABLED(CONFIG_INTEL_IDXD_PERFMON)
पूर्णांक perfmon_pmu_init(काष्ठा idxd_device *idxd);
व्योम perfmon_pmu_हटाओ(काष्ठा idxd_device *idxd);
व्योम perfmon_counter_overflow(काष्ठा idxd_device *idxd);
व्योम perfmon_init(व्योम);
व्योम perfmon_निकास(व्योम);
#अन्यथा
अटल अंतरभूत पूर्णांक perfmon_pmu_init(काष्ठा idxd_device *idxd) अणु वापस 0; पूर्ण
अटल अंतरभूत व्योम perfmon_pmu_हटाओ(काष्ठा idxd_device *idxd) अणुपूर्ण
अटल अंतरभूत व्योम perfmon_counter_overflow(काष्ठा idxd_device *idxd) अणुपूर्ण
अटल अंतरभूत व्योम perfmon_init(व्योम) अणुपूर्ण
अटल अंतरभूत व्योम perfmon_निकास(व्योम) अणुपूर्ण
#पूर्ण_अगर

#पूर्ण_अगर
