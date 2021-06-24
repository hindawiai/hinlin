<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * SPU file प्रणाली
 *
 * (C) Copyright IBM Deutschland Entwicklung GmbH 2005
 *
 * Author: Arnd Bergmann <arndb@de.ibm.com>
 */
#अगर_अघोषित SPUFS_H
#घोषणा SPUFS_H

#समावेश <linux/kref.h>
#समावेश <linux/mutex.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/fs.h>
#समावेश <linux/cpumask.h>
#समावेश <linux/sched/संकेत.स>

#समावेश <यंत्र/spu.h>
#समावेश <यंत्र/spu_csa.h>
#समावेश <यंत्र/spu_info.h>

#घोषणा SPUFS_PS_MAP_SIZE	0x20000
#घोषणा SPUFS_MFC_MAP_SIZE	0x1000
#घोषणा SPUFS_CNTL_MAP_SIZE	0x1000
#घोषणा SPUFS_SIGNAL_MAP_SIZE	PAGE_SIZE
#घोषणा SPUFS_MSS_MAP_SIZE	0x1000

/* The magic number क्रम our file प्रणाली */
क्रमागत अणु
	SPUFS_MAGIC = 0x23c9b64e,
पूर्ण;

काष्ठा spu_context_ops;
काष्ठा spu_gang;

/* ctx->sched_flags */
क्रमागत अणु
	SPU_SCHED_NOTIFY_ACTIVE,
	SPU_SCHED_WAS_ACTIVE,	/* was active upon spu_acquire_saved()  */
	SPU_SCHED_SPU_RUN,	/* context is within spu_run */
पूर्ण;

क्रमागत अणु
	SWITCH_LOG_बफ_मानE = 4096,
पूर्ण;

क्रमागत अणु
	SWITCH_LOG_START,
	SWITCH_LOG_STOP,
	SWITCH_LOG_EXIT,
पूर्ण;

काष्ठा चयन_log अणु
	रुको_queue_head_t	रुको;
	अचिन्हित दीर्घ		head;
	अचिन्हित दीर्घ		tail;
	काष्ठा चयन_log_entry अणु
		काष्ठा बारpec64 tstamp;
		s32		spu_id;
		u32		type;
		u32		val;
		u64		समयbase;
	पूर्ण log[];
पूर्ण;

काष्ठा spu_context अणु
	काष्ठा spu *spu;		  /* poपूर्णांकer to a physical SPU */
	काष्ठा spu_state csa;		  /* SPU context save area. */
	spinlock_t mmio_lock;		  /* protects mmio access */
	काष्ठा address_space *local_store; /* local store mapping.  */
	काष्ठा address_space *mfc;	   /* 'mfc' area mappings. */
	काष्ठा address_space *cntl;	   /* 'control' area mappings. */
	काष्ठा address_space *संकेत1;	   /* 'signal1' area mappings. */
	काष्ठा address_space *संकेत2;	   /* 'signal2' area mappings. */
	काष्ठा address_space *mss;	   /* 'mss' area mappings. */
	काष्ठा address_space *psmap;	   /* 'psmap' area mappings. */
	काष्ठा mutex mapping_lock;
	u64 object_id;		   /* user space poपूर्णांकer क्रम oprofile */

	क्रमागत अणु SPU_STATE_RUNNABLE, SPU_STATE_SAVED पूर्ण state;
	काष्ठा mutex state_mutex;
	काष्ठा mutex run_mutex;

	काष्ठा mm_काष्ठा *owner;

	काष्ठा kref kref;
	रुको_queue_head_t ibox_wq;
	रुको_queue_head_t wbox_wq;
	रुको_queue_head_t stop_wq;
	रुको_queue_head_t mfc_wq;
	रुको_queue_head_t run_wq;
	u32 tagरुको;
	काष्ठा spu_context_ops *ops;
	काष्ठा work_काष्ठा reap_work;
	अचिन्हित दीर्घ flags;
	अचिन्हित दीर्घ event_वापस;

	काष्ठा list_head gang_list;
	काष्ठा spu_gang *gang;
	काष्ठा kref *prof_priv_kref;
	व्योम ( * prof_priv_release) (काष्ठा kref *kref);

	/* owner thपढ़ो */
	pid_t tid;

	/* scheduler fields */
	काष्ठा list_head rq;
	अचिन्हित पूर्णांक समय_slice;
	अचिन्हित दीर्घ sched_flags;
	cpumask_t cpus_allowed;
	पूर्णांक policy;
	पूर्णांक prio;
	पूर्णांक last_ran;

	/* statistics */
	काष्ठा अणु
		/* updates रक्षित by ctx->state_mutex */
		क्रमागत spu_utilization_state util_state;
		अचिन्हित दीर्घ दीर्घ tstamp;	/* समय of last state चयन */
		अचिन्हित दीर्घ दीर्घ बार[SPU_UTIL_MAX];
		अचिन्हित दीर्घ दीर्घ vol_ctx_चयन;
		अचिन्हित दीर्घ दीर्घ invol_ctx_चयन;
		अचिन्हित दीर्घ दीर्घ min_flt;
		अचिन्हित दीर्घ दीर्घ maj_flt;
		अचिन्हित दीर्घ दीर्घ hash_flt;
		अचिन्हित दीर्घ दीर्घ slb_flt;
		अचिन्हित दीर्घ दीर्घ slb_flt_base; /* # at last ctx चयन */
		अचिन्हित दीर्घ दीर्घ class2_पूर्णांकr;
		अचिन्हित दीर्घ दीर्घ class2_पूर्णांकr_base; /* # at last ctx चयन */
		अचिन्हित दीर्घ दीर्घ libassist;
	पूर्ण stats;

	/* context चयन log */
	काष्ठा चयन_log *चयन_log;

	काष्ठा list_head aff_list;
	पूर्णांक aff_head;
	पूर्णांक aff_offset;
पूर्ण;

काष्ठा spu_gang अणु
	काष्ठा list_head list;
	काष्ठा mutex mutex;
	काष्ठा kref kref;
	पूर्णांक contexts;

	काष्ठा spu_context *aff_ref_ctx;
	काष्ठा list_head aff_list_head;
	काष्ठा mutex aff_mutex;
	पूर्णांक aff_flags;
	काष्ठा spu *aff_ref_spu;
	atomic_t aff_sched_count;
पूर्ण;

/* Flag bits क्रम spu_gang aff_flags */
#घोषणा AFF_OFFSETS_SET		1
#घोषणा AFF_MERGED		2

काष्ठा mfc_dma_command अणु
	पूर्णांक32_t pad;	/* reserved */
	uपूर्णांक32_t lsa;	/* local storage address */
	uपूर्णांक64_t ea;	/* effective address */
	uपूर्णांक16_t size;	/* transfer size */
	uपूर्णांक16_t tag;	/* command tag */
	uपूर्णांक16_t class;	/* class ID */
	uपूर्णांक16_t cmd;	/* command opcode */
पूर्ण;


/* SPU context query/set operations. */
काष्ठा spu_context_ops अणु
	पूर्णांक (*mbox_पढ़ो) (काष्ठा spu_context * ctx, u32 * data);
	 u32(*mbox_stat_पढ़ो) (काष्ठा spu_context * ctx);
	__poll_t (*mbox_stat_poll)(काष्ठा spu_context *ctx, __poll_t events);
	पूर्णांक (*ibox_पढ़ो) (काष्ठा spu_context * ctx, u32 * data);
	पूर्णांक (*wbox_ग_लिखो) (काष्ठा spu_context * ctx, u32 data);
	 u32(*संकेत1_पढ़ो) (काष्ठा spu_context * ctx);
	व्योम (*संकेत1_ग_लिखो) (काष्ठा spu_context * ctx, u32 data);
	 u32(*संकेत2_पढ़ो) (काष्ठा spu_context * ctx);
	व्योम (*संकेत2_ग_लिखो) (काष्ठा spu_context * ctx, u32 data);
	व्योम (*संकेत1_type_set) (काष्ठा spu_context * ctx, u64 val);
	 u64(*संकेत1_type_get) (काष्ठा spu_context * ctx);
	व्योम (*संकेत2_type_set) (काष्ठा spu_context * ctx, u64 val);
	 u64(*संकेत2_type_get) (काष्ठा spu_context * ctx);
	 u32(*npc_पढ़ो) (काष्ठा spu_context * ctx);
	व्योम (*npc_ग_लिखो) (काष्ठा spu_context * ctx, u32 data);
	 u32(*status_पढ़ो) (काष्ठा spu_context * ctx);
	अक्षर*(*get_ls) (काष्ठा spu_context * ctx);
	व्योम (*privcntl_ग_लिखो) (काष्ठा spu_context *ctx, u64 data);
	 u32 (*runcntl_पढ़ो) (काष्ठा spu_context * ctx);
	व्योम (*runcntl_ग_लिखो) (काष्ठा spu_context * ctx, u32 data);
	व्योम (*runcntl_stop) (काष्ठा spu_context * ctx);
	व्योम (*master_start) (काष्ठा spu_context * ctx);
	व्योम (*master_stop) (काष्ठा spu_context * ctx);
	पूर्णांक (*set_mfc_query)(काष्ठा spu_context * ctx, u32 mask, u32 mode);
	u32 (*पढ़ो_mfc_tagstatus)(काष्ठा spu_context * ctx);
	u32 (*get_mfc_मुक्त_elements)(काष्ठा spu_context *ctx);
	पूर्णांक (*send_mfc_command)(काष्ठा spu_context * ctx,
				काष्ठा mfc_dma_command * cmd);
	व्योम (*dma_info_पढ़ो) (काष्ठा spu_context * ctx,
			       काष्ठा spu_dma_info * info);
	व्योम (*proxydma_info_पढ़ो) (काष्ठा spu_context * ctx,
				    काष्ठा spu_proxydma_info * info);
	व्योम (*restart_dma)(काष्ठा spu_context *ctx);
पूर्ण;

बाह्य काष्ठा spu_context_ops spu_hw_ops;
बाह्य काष्ठा spu_context_ops spu_backing_ops;

काष्ठा spufs_inode_info अणु
	काष्ठा spu_context *i_ctx;
	काष्ठा spu_gang *i_gang;
	काष्ठा inode vfs_inode;
	पूर्णांक i_खोलोers;
पूर्ण;
#घोषणा SPUFS_I(inode) \
	container_of(inode, काष्ठा spufs_inode_info, vfs_inode)

काष्ठा spufs_tree_descr अणु
	स्थिर अक्षर *name;
	स्थिर काष्ठा file_operations *ops;
	umode_t mode;
	माप_प्रकार size;
पूर्ण;

बाह्य स्थिर काष्ठा spufs_tree_descr spufs_dir_contents[];
बाह्य स्थिर काष्ठा spufs_tree_descr spufs_dir_nosched_contents[];
बाह्य स्थिर काष्ठा spufs_tree_descr spufs_dir_debug_contents[];

/* प्रणाली call implementation */
बाह्य काष्ठा spufs_calls spufs_calls;
काष्ठा coredump_params;
दीर्घ spufs_run_spu(काष्ठा spu_context *ctx, u32 *npc, u32 *status);
दीर्घ spufs_create(काष्ठा path *nd, काष्ठा dentry *dentry, अचिन्हित पूर्णांक flags,
			umode_t mode, काष्ठा file *filp);
/* ELF coredump callbacks क्रम writing SPU ELF notes */
बाह्य पूर्णांक spufs_coredump_extra_notes_size(व्योम);
बाह्य पूर्णांक spufs_coredump_extra_notes_ग_लिखो(काष्ठा coredump_params *cprm);

बाह्य स्थिर काष्ठा file_operations spufs_context_fops;

/* gang management */
काष्ठा spu_gang *alloc_spu_gang(व्योम);
काष्ठा spu_gang *get_spu_gang(काष्ठा spu_gang *gang);
पूर्णांक put_spu_gang(काष्ठा spu_gang *gang);
व्योम spu_gang_हटाओ_ctx(काष्ठा spu_gang *gang, काष्ठा spu_context *ctx);
व्योम spu_gang_add_ctx(काष्ठा spu_gang *gang, काष्ठा spu_context *ctx);

/* fault handling */
पूर्णांक spufs_handle_class1(काष्ठा spu_context *ctx);
पूर्णांक spufs_handle_class0(काष्ठा spu_context *ctx);

/* affinity */
काष्ठा spu *affinity_check(काष्ठा spu_context *ctx);

/* context management */
बाह्य atomic_t nr_spu_contexts;
अटल अंतरभूत पूर्णांक __must_check spu_acquire(काष्ठा spu_context *ctx)
अणु
	वापस mutex_lock_पूर्णांकerruptible(&ctx->state_mutex);
पूर्ण

अटल अंतरभूत व्योम spu_release(काष्ठा spu_context *ctx)
अणु
	mutex_unlock(&ctx->state_mutex);
पूर्ण

काष्ठा spu_context * alloc_spu_context(काष्ठा spu_gang *gang);
व्योम destroy_spu_context(काष्ठा kref *kref);
काष्ठा spu_context * get_spu_context(काष्ठा spu_context *ctx);
पूर्णांक put_spu_context(काष्ठा spu_context *ctx);
व्योम spu_unmap_mappings(काष्ठा spu_context *ctx);

व्योम spu_क्रमget(काष्ठा spu_context *ctx);
पूर्णांक __must_check spu_acquire_saved(काष्ठा spu_context *ctx);
व्योम spu_release_saved(काष्ठा spu_context *ctx);

पूर्णांक spu_stopped(काष्ठा spu_context *ctx, u32 * stat);
व्योम spu_del_from_rq(काष्ठा spu_context *ctx);
पूर्णांक spu_activate(काष्ठा spu_context *ctx, अचिन्हित दीर्घ flags);
व्योम spu_deactivate(काष्ठा spu_context *ctx);
व्योम spu_yield(काष्ठा spu_context *ctx);
व्योम spu_चयन_log_notअगरy(काष्ठा spu *spu, काष्ठा spu_context *ctx,
		u32 type, u32 val);
व्योम spu_set_बारlice(काष्ठा spu_context *ctx);
व्योम spu_update_sched_info(काष्ठा spu_context *ctx);
व्योम __spu_update_sched_info(काष्ठा spu_context *ctx);
पूर्णांक __init spu_sched_init(व्योम);
व्योम spu_sched_निकास(व्योम);

बाह्य अक्षर *isolated_loader;

/*
 * spufs_रुको
 *	Same as रुको_event_पूर्णांकerruptible(), except that here
 *	we need to call spu_release(ctx) beक्रमe sleeping, and
 *	then spu_acquire(ctx) when awoken.
 *
 * 	Returns with state_mutex re-acquired when successful or
 * 	with -ERESTARTSYS and the state_mutex dropped when पूर्णांकerrupted.
 */

#घोषणा spufs_रुको(wq, condition)					\
(अणु									\
	पूर्णांक __ret = 0;							\
	DEFINE_WAIT(__रुको);						\
	क्रम (;;) अणु							\
		prepare_to_रुको(&(wq), &__रुको, TASK_INTERRUPTIBLE);	\
		अगर (condition)						\
			अवरोध;						\
		spu_release(ctx);					\
		अगर (संकेत_pending(current)) अणु				\
			__ret = -ERESTARTSYS;				\
			अवरोध;						\
		पूर्ण							\
		schedule();						\
		__ret = spu_acquire(ctx);				\
		अगर (__ret)						\
			अवरोध;						\
	पूर्ण								\
	finish_रुको(&(wq), &__रुको);					\
	__ret;								\
पूर्ण)

माप_प्रकार spu_wbox_ग_लिखो(काष्ठा spu_context *ctx, u32 data);
माप_प्रकार spu_ibox_पढ़ो(काष्ठा spu_context *ctx, u32 *data);

/* irq callback funcs. */
व्योम spufs_ibox_callback(काष्ठा spu *spu);
व्योम spufs_wbox_callback(काष्ठा spu *spu);
व्योम spufs_stop_callback(काष्ठा spu *spu, पूर्णांक irq);
व्योम spufs_mfc_callback(काष्ठा spu *spu);
व्योम spufs_dma_callback(काष्ठा spu *spu, पूर्णांक type);

बाह्य काष्ठा spu_coredump_calls spufs_coredump_calls;
काष्ठा spufs_coredump_पढ़ोer अणु
	अक्षर *name;
	sमाप_प्रकार (*dump)(काष्ठा spu_context *ctx, काष्ठा coredump_params *cprm);
	u64 (*get)(काष्ठा spu_context *ctx);
	माप_प्रकार size;
पूर्ण;
बाह्य स्थिर काष्ठा spufs_coredump_पढ़ोer spufs_coredump_पढ़ो[];
बाह्य पूर्णांक spufs_coredump_num_notes;

बाह्य पूर्णांक spu_init_csa(काष्ठा spu_state *csa);
बाह्य व्योम spu_fini_csa(काष्ठा spu_state *csa);
बाह्य पूर्णांक spu_save(काष्ठा spu_state *prev, काष्ठा spu *spu);
बाह्य पूर्णांक spu_restore(काष्ठा spu_state *new, काष्ठा spu *spu);
बाह्य पूर्णांक spu_चयन(काष्ठा spu_state *prev, काष्ठा spu_state *new,
		      काष्ठा spu *spu);
बाह्य पूर्णांक spu_alloc_lscsa(काष्ठा spu_state *csa);
बाह्य व्योम spu_मुक्त_lscsa(काष्ठा spu_state *csa);

बाह्य व्योम spuctx_चयन_state(काष्ठा spu_context *ctx,
		क्रमागत spu_utilization_state new_state);

#पूर्ण_अगर
