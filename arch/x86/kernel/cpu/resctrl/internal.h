<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_X86_RESCTRL_INTERNAL_H
#घोषणा _ASM_X86_RESCTRL_INTERNAL_H

#समावेश <linux/sched.h>
#समावेश <linux/kernfs.h>
#समावेश <linux/fs_context.h>
#समावेश <linux/jump_label.h>

#घोषणा MSR_IA32_L3_QOS_CFG		0xc81
#घोषणा MSR_IA32_L2_QOS_CFG		0xc82
#घोषणा MSR_IA32_L3_CBM_BASE		0xc90
#घोषणा MSR_IA32_L2_CBM_BASE		0xd10
#घोषणा MSR_IA32_MBA_THRTL_BASE		0xd50
#घोषणा MSR_IA32_MBA_BW_BASE		0xc0000200

#घोषणा MSR_IA32_QM_CTR			0x0c8e
#घोषणा MSR_IA32_QM_EVTSEL		0x0c8d

#घोषणा L3_QOS_CDP_ENABLE		0x01ULL

#घोषणा L2_QOS_CDP_ENABLE		0x01ULL

/*
 * Event IDs are used to program IA32_QM_EVTSEL beक्रमe पढ़ोing event
 * counter from IA32_QM_CTR
 */
#घोषणा QOS_L3_OCCUP_EVENT_ID		0x01
#घोषणा QOS_L3_MBM_TOTAL_EVENT_ID	0x02
#घोषणा QOS_L3_MBM_LOCAL_EVENT_ID	0x03

#घोषणा CQM_LIMBOCHECK_INTERVAL	1000

#घोषणा MBM_CNTR_WIDTH_BASE		24
#घोषणा MBM_OVERFLOW_INTERVAL		1000
#घोषणा MAX_MBA_BW			100u
#घोषणा MBA_IS_LINEAR			0x4
#घोषणा MBA_MAX_MBPS			U32_MAX
#घोषणा MAX_MBA_BW_AMD			0x800
#घोषणा MBM_CNTR_WIDTH_OFFSET_AMD	20

#घोषणा RMID_VAL_ERROR			BIT_ULL(63)
#घोषणा RMID_VAL_UNAVAIL		BIT_ULL(62)
/*
 * With the above fields in use 62 bits reमुख्य in MSR_IA32_QM_CTR क्रम
 * data to be वापसed. The counter width is discovered from the hardware
 * as an offset from MBM_CNTR_WIDTH_BASE.
 */
#घोषणा MBM_CNTR_WIDTH_OFFSET_MAX (62 - MBM_CNTR_WIDTH_BASE)


काष्ठा rdt_fs_context अणु
	काष्ठा kernfs_fs_context	kfc;
	bool				enable_cdpl2;
	bool				enable_cdpl3;
	bool				enable_mba_mbps;
पूर्ण;

अटल अंतरभूत काष्ठा rdt_fs_context *rdt_fc2context(काष्ठा fs_context *fc)
अणु
	काष्ठा kernfs_fs_context *kfc = fc->fs_निजी;

	वापस container_of(kfc, काष्ठा rdt_fs_context, kfc);
पूर्ण

DECLARE_STATIC_KEY_FALSE(rdt_enable_key);
DECLARE_STATIC_KEY_FALSE(rdt_mon_enable_key);

/**
 * काष्ठा mon_evt - Entry in the event list of a resource
 * @evtid:		event id
 * @name:		name of the event
 */
काष्ठा mon_evt अणु
	u32			evtid;
	अक्षर			*name;
	काष्ठा list_head	list;
पूर्ण;

/**
 * काष्ठा mon_data_bits - Monitoring details क्रम each event file
 * @rid:               Resource id associated with the event file.
 * @evtid:             Event id associated with the event file
 * @करोmid:             The करोमुख्य to which the event file beदीर्घs
 */
जोड़ mon_data_bits अणु
	व्योम *priv;
	काष्ठा अणु
		अचिन्हित पूर्णांक rid	: 10;
		अचिन्हित पूर्णांक evtid	: 8;
		अचिन्हित पूर्णांक करोmid	: 14;
	पूर्ण u;
पूर्ण;

काष्ठा rmid_पढ़ो अणु
	काष्ठा rdtgroup		*rgrp;
	काष्ठा rdt_resource	*r;
	काष्ठा rdt_करोमुख्य	*d;
	पूर्णांक			evtid;
	bool			first;
	u64			val;
पूर्ण;

बाह्य अचिन्हित पूर्णांक resctrl_cqm_threshold;
बाह्य bool rdt_alloc_capable;
बाह्य bool rdt_mon_capable;
बाह्य अचिन्हित पूर्णांक rdt_mon_features;

क्रमागत rdt_group_type अणु
	RDTCTRL_GROUP = 0,
	RDTMON_GROUP,
	RDT_NUM_GROUP,
पूर्ण;

/**
 * क्रमागत rdtgrp_mode - Mode of a RDT resource group
 * @RDT_MODE_SHAREABLE: This resource group allows sharing of its allocations
 * @RDT_MODE_EXCLUSIVE: No sharing of this resource group's allocations allowed
 * @RDT_MODE_PSEUDO_LOCKSETUP: Resource group will be used क्रम Pseuकरो-Locking
 * @RDT_MODE_PSEUDO_LOCKED: No sharing of this resource group's allocations
 *                          allowed AND the allocations are Cache Pseuकरो-Locked
 *
 * The mode of a resource group enables control over the allowed overlap
 * between allocations associated with dअगरferent resource groups (classes
 * of service). User is able to modअगरy the mode of a resource group by
 * writing to the "mode" resctrl file associated with the resource group.
 *
 * The "shareable", "exclusive", and "pseudo-locksetup" modes are set by
 * writing the appropriate text to the "mode" file. A resource group enters
 * "pseudo-locked" mode after the schemata is written जबतक the resource
 * group is in "pseudo-locksetup" mode.
 */
क्रमागत rdtgrp_mode अणु
	RDT_MODE_SHAREABLE = 0,
	RDT_MODE_EXCLUSIVE,
	RDT_MODE_PSEUDO_LOCKSETUP,
	RDT_MODE_PSEUDO_LOCKED,

	/* Must be last */
	RDT_NUM_MODES,
पूर्ण;

/**
 * काष्ठा mongroup - store mon group's data in resctrl fs.
 * @mon_data_kn		kernlfs node क्रम the mon_data directory
 * @parent:			parent rdtgrp
 * @crdtgrp_list:		child rdtgroup node list
 * @rmid:			rmid क्रम this rdtgroup
 */
काष्ठा mongroup अणु
	काष्ठा kernfs_node	*mon_data_kn;
	काष्ठा rdtgroup		*parent;
	काष्ठा list_head	crdtgrp_list;
	u32			rmid;
पूर्ण;

/**
 * काष्ठा pseuकरो_lock_region - pseuकरो-lock region inक्रमmation
 * @r:			RDT resource to which this pseuकरो-locked region
 *			beदीर्घs
 * @d:			RDT करोमुख्य to which this pseuकरो-locked region
 *			beदीर्घs
 * @cbm:		biपंचांगask of the pseuकरो-locked region
 * @lock_thपढ़ो_wq:	रुकोqueue used to रुको on the pseuकरो-locking thपढ़ो
 *			completion
 * @thपढ़ो_करोne:	variable used by रुकोqueue to test अगर pseuकरो-locking
 *			thपढ़ो completed
 * @cpu:		core associated with the cache on which the setup code
 *			will be run
 * @line_size:		size of the cache lines
 * @size:		size of pseuकरो-locked region in bytes
 * @kmem:		the kernel memory associated with pseuकरो-locked region
 * @minor:		minor number of अक्षरacter device associated with this
 *			region
 * @debugfs_dir:	poपूर्णांकer to this region's directory in the debugfs
 *			fileप्रणाली
 * @pm_reqs:		Power management QoS requests related to this region
 */
काष्ठा pseuकरो_lock_region अणु
	काष्ठा rdt_resource	*r;
	काष्ठा rdt_करोमुख्य	*d;
	u32			cbm;
	रुको_queue_head_t	lock_thपढ़ो_wq;
	पूर्णांक			thपढ़ो_करोne;
	पूर्णांक			cpu;
	अचिन्हित पूर्णांक		line_size;
	अचिन्हित पूर्णांक		size;
	व्योम			*kmem;
	अचिन्हित पूर्णांक		minor;
	काष्ठा dentry		*debugfs_dir;
	काष्ठा list_head	pm_reqs;
पूर्ण;

/**
 * काष्ठा rdtgroup - store rdtgroup's data in resctrl file प्रणाली.
 * @kn:				kernfs node
 * @rdtgroup_list:		linked list क्रम all rdtgroups
 * @closid:			closid क्रम this rdtgroup
 * @cpu_mask:			CPUs asचिन्हित to this rdtgroup
 * @flags:			status bits
 * @रुकोcount:			how many cpus expect to find this
 *				group when they acquire rdtgroup_mutex
 * @type:			indicates type of this rdtgroup - either
 *				monitor only or ctrl_mon group
 * @mon:			mongroup related data
 * @mode:			mode of resource group
 * @plr:			pseuकरो-locked region
 */
काष्ठा rdtgroup अणु
	काष्ठा kernfs_node		*kn;
	काष्ठा list_head		rdtgroup_list;
	u32				closid;
	काष्ठा cpumask			cpu_mask;
	पूर्णांक				flags;
	atomic_t			रुकोcount;
	क्रमागत rdt_group_type		type;
	काष्ठा mongroup			mon;
	क्रमागत rdtgrp_mode		mode;
	काष्ठा pseuकरो_lock_region	*plr;
पूर्ण;

/* rdtgroup.flags */
#घोषणा	RDT_DELETED		1

/* rftype.flags */
#घोषणा RFTYPE_FLAGS_CPUS_LIST	1

/*
 * Define the file type flags क्रम base and info directories.
 */
#घोषणा RFTYPE_INFO			BIT(0)
#घोषणा RFTYPE_BASE			BIT(1)
#घोषणा RF_CTRLSHIFT			4
#घोषणा RF_MONSHIFT			5
#घोषणा RF_TOPSHIFT			6
#घोषणा RFTYPE_CTRL			BIT(RF_CTRLSHIFT)
#घोषणा RFTYPE_MON			BIT(RF_MONSHIFT)
#घोषणा RFTYPE_TOP			BIT(RF_TOPSHIFT)
#घोषणा RFTYPE_RES_CACHE		BIT(8)
#घोषणा RFTYPE_RES_MB			BIT(9)
#घोषणा RF_CTRL_INFO			(RFTYPE_INFO | RFTYPE_CTRL)
#घोषणा RF_MON_INFO			(RFTYPE_INFO | RFTYPE_MON)
#घोषणा RF_TOP_INFO			(RFTYPE_INFO | RFTYPE_TOP)
#घोषणा RF_CTRL_BASE			(RFTYPE_BASE | RFTYPE_CTRL)

/* List of all resource groups */
बाह्य काष्ठा list_head rdt_all_groups;

बाह्य पूर्णांक max_name_width, max_data_width;

पूर्णांक __init rdtgroup_init(व्योम);
व्योम __निकास rdtgroup_निकास(व्योम);

/**
 * काष्ठा rftype - describe each file in the resctrl file प्रणाली
 * @name:	File name
 * @mode:	Access mode
 * @kf_ops:	File operations
 * @flags:	File specअगरic RFTYPE_FLAGS_* flags
 * @fflags:	File specअगरic RF_* or RFTYPE_* flags
 * @seq_show:	Show content of the file
 * @ग_लिखो:	Write to the file
 */
काष्ठा rftype अणु
	अक्षर			*name;
	umode_t			mode;
	स्थिर काष्ठा kernfs_ops	*kf_ops;
	अचिन्हित दीर्घ		flags;
	अचिन्हित दीर्घ		fflags;

	पूर्णांक (*seq_show)(काष्ठा kernfs_खोलो_file *of,
			काष्ठा seq_file *sf, व्योम *v);
	/*
	 * ग_लिखो() is the generic ग_लिखो callback which maps directly to
	 * kernfs ग_लिखो operation and overrides all other operations.
	 * Maximum ग_लिखो size is determined by ->max_ग_लिखो_len.
	 */
	sमाप_प्रकार (*ग_लिखो)(काष्ठा kernfs_खोलो_file *of,
			 अक्षर *buf, माप_प्रकार nbytes, loff_t off);
पूर्ण;

/**
 * काष्ठा mbm_state - status क्रम each MBM counter in each करोमुख्य
 * @chunks:	Total data moved (multiply by rdt_group.mon_scale to get bytes)
 * @prev_msr	Value of IA32_QM_CTR क्रम this RMID last समय we पढ़ो it
 * @prev_bw_msr:Value of previous IA32_QM_CTR क्रम bandwidth counting
 * @prev_bw	The most recent bandwidth in MBps
 * @delta_bw	Dअगरference between the current and previous bandwidth
 * @delta_comp	Indicates whether to compute the delta_bw
 */
काष्ठा mbm_state अणु
	u64	chunks;
	u64	prev_msr;
	u64	prev_bw_msr;
	u32	prev_bw;
	u32	delta_bw;
	bool	delta_comp;
पूर्ण;

/**
 * काष्ठा rdt_करोमुख्य - group of cpus sharing an RDT resource
 * @list:	all instances of this resource
 * @id:		unique id क्रम this instance
 * @cpu_mask:	which cpus share this resource
 * @rmid_busy_llc:
 *		biपंचांगap of which limbo RMIDs are above threshold
 * @mbm_total:	saved state क्रम MBM total bandwidth
 * @mbm_local:	saved state क्रम MBM local bandwidth
 * @mbm_over:	worker to periodically पढ़ो MBM h/w counters
 * @cqm_limbo:	worker to periodically पढ़ो CQM h/w counters
 * @mbm_work_cpu:
 *		worker cpu क्रम MBM h/w counters
 * @cqm_work_cpu:
 *		worker cpu क्रम CQM h/w counters
 * @ctrl_val:	array of cache or mem ctrl values (indexed by CLOSID)
 * @mbps_val:	When mba_sc is enabled, this holds the bandwidth in MBps
 * @new_ctrl:	new ctrl value to be loaded
 * @have_new_ctrl: did user provide new_ctrl क्रम this करोमुख्य
 * @plr:	pseuकरो-locked region (अगर any) associated with करोमुख्य
 */
काष्ठा rdt_करोमुख्य अणु
	काष्ठा list_head		list;
	पूर्णांक				id;
	काष्ठा cpumask			cpu_mask;
	अचिन्हित दीर्घ			*rmid_busy_llc;
	काष्ठा mbm_state		*mbm_total;
	काष्ठा mbm_state		*mbm_local;
	काष्ठा delayed_work		mbm_over;
	काष्ठा delayed_work		cqm_limbo;
	पूर्णांक				mbm_work_cpu;
	पूर्णांक				cqm_work_cpu;
	u32				*ctrl_val;
	u32				*mbps_val;
	u32				new_ctrl;
	bool				have_new_ctrl;
	काष्ठा pseuकरो_lock_region	*plr;
पूर्ण;

/**
 * काष्ठा msr_param - set a range of MSRs from a करोमुख्य
 * @res:       The resource to use
 * @low:       Beginning index from base MSR
 * @high:      End index
 */
काष्ठा msr_param अणु
	काष्ठा rdt_resource	*res;
	पूर्णांक			low;
	पूर्णांक			high;
पूर्ण;

/**
 * काष्ठा rdt_cache - Cache allocation related data
 * @cbm_len:		Length of the cache bit mask
 * @min_cbm_bits:	Minimum number of consecutive bits to be set
 * @cbm_idx_mult:	Multiplier of CBM index
 * @cbm_idx_offset:	Offset of CBM index. CBM index is computed by:
 *			closid * cbm_idx_multi + cbm_idx_offset
 *			in a cache bit mask
 * @shareable_bits:	Biपंचांगask of shareable resource with other
 *			executing entities
 * @arch_has_sparse_biपंचांगaps:	True अगर a biपंचांगap like f00f is valid.
 * @arch_has_empty_biपंचांगaps:	True अगर the '0' biपंचांगap is valid.
 * @arch_has_per_cpu_cfg:	True अगर QOS_CFG रेजिस्टर क्रम this cache
 *				level has CPU scope.
 */
काष्ठा rdt_cache अणु
	अचिन्हित पूर्णांक	cbm_len;
	अचिन्हित पूर्णांक	min_cbm_bits;
	अचिन्हित पूर्णांक	cbm_idx_mult;
	अचिन्हित पूर्णांक	cbm_idx_offset;
	अचिन्हित पूर्णांक	shareable_bits;
	bool		arch_has_sparse_biपंचांगaps;
	bool		arch_has_empty_biपंचांगaps;
	bool		arch_has_per_cpu_cfg;
पूर्ण;

/**
 * क्रमागत membw_throttle_mode - System's memory bandwidth throttling mode
 * @THREAD_THROTTLE_UNDEFINED:	Not relevant to the प्रणाली
 * @THREAD_THROTTLE_MAX:	Memory bandwidth is throttled at the core
 *				always using smallest bandwidth percentage
 *				asचिन्हित to thपढ़ोs, aka "max throttling"
 * @THREAD_THROTTLE_PER_THREAD:	Memory bandwidth is throttled at the thपढ़ो
 */
क्रमागत membw_throttle_mode अणु
	THREAD_THROTTLE_UNDEFINED = 0,
	THREAD_THROTTLE_MAX,
	THREAD_THROTTLE_PER_THREAD,
पूर्ण;

/**
 * काष्ठा rdt_membw - Memory bandwidth allocation related data
 * @min_bw:		Minimum memory bandwidth percentage user can request
 * @bw_gran:		Granularity at which the memory bandwidth is allocated
 * @delay_linear:	True अगर memory B/W delay is in linear scale
 * @arch_needs_linear:	True अगर we can't configure non-linear resources
 * @throttle_mode:	Bandwidth throttling mode when thपढ़ोs request
 *			dअगरferent memory bandwidths
 * @mba_sc:		True अगर MBA software controller(mba_sc) is enabled
 * @mb_map:		Mapping of memory B/W percentage to memory B/W delay
 */
काष्ठा rdt_membw अणु
	u32				min_bw;
	u32				bw_gran;
	u32				delay_linear;
	bool				arch_needs_linear;
	क्रमागत membw_throttle_mode	throttle_mode;
	bool				mba_sc;
	u32				*mb_map;
पूर्ण;

अटल अंतरभूत bool is_llc_occupancy_enabled(व्योम)
अणु
	वापस (rdt_mon_features & (1 << QOS_L3_OCCUP_EVENT_ID));
पूर्ण

अटल अंतरभूत bool is_mbm_total_enabled(व्योम)
अणु
	वापस (rdt_mon_features & (1 << QOS_L3_MBM_TOTAL_EVENT_ID));
पूर्ण

अटल अंतरभूत bool is_mbm_local_enabled(व्योम)
अणु
	वापस (rdt_mon_features & (1 << QOS_L3_MBM_LOCAL_EVENT_ID));
पूर्ण

अटल अंतरभूत bool is_mbm_enabled(व्योम)
अणु
	वापस (is_mbm_total_enabled() || is_mbm_local_enabled());
पूर्ण

अटल अंतरभूत bool is_mbm_event(पूर्णांक e)
अणु
	वापस (e >= QOS_L3_MBM_TOTAL_EVENT_ID &&
		e <= QOS_L3_MBM_LOCAL_EVENT_ID);
पूर्ण

काष्ठा rdt_parse_data अणु
	काष्ठा rdtgroup		*rdtgrp;
	अक्षर			*buf;
पूर्ण;

/**
 * काष्ठा rdt_resource - attributes of an RDT resource
 * @rid:		The index of the resource
 * @alloc_enabled:	Is allocation enabled on this machine
 * @mon_enabled:	Is monitoring enabled क्रम this feature
 * @alloc_capable:	Is allocation available on this machine
 * @mon_capable:	Is monitor feature available on this machine
 * @name:		Name to use in "schemata" file
 * @num_closid:		Number of CLOSIDs available
 * @cache_level:	Which cache level defines scope of this resource
 * @शेष_ctrl:	Specअगरies शेष cache cbm or memory B/W percent.
 * @msr_base:		Base MSR address क्रम CBMs
 * @msr_update:		Function poपूर्णांकer to update QOS MSRs
 * @data_width:		Character width of data when displaying
 * @करोमुख्यs:		All करोमुख्यs क्रम this resource
 * @cache:		Cache allocation related data
 * @क्रमmat_str:		Per resource क्रमmat string to show करोमुख्य value
 * @parse_ctrlval:	Per resource function poपूर्णांकer to parse control values
 * @evt_list:		List of monitoring events
 * @num_rmid:		Number of RMIDs available
 * @mon_scale:		cqm counter * mon_scale = occupancy in bytes
 * @fflags:		flags to choose base and info files
 */
काष्ठा rdt_resource अणु
	पूर्णांक			rid;
	bool			alloc_enabled;
	bool			mon_enabled;
	bool			alloc_capable;
	bool			mon_capable;
	अक्षर			*name;
	पूर्णांक			num_closid;
	पूर्णांक			cache_level;
	u32			शेष_ctrl;
	अचिन्हित पूर्णांक		msr_base;
	व्योम (*msr_update)	(काष्ठा rdt_करोमुख्य *d, काष्ठा msr_param *m,
				 काष्ठा rdt_resource *r);
	पूर्णांक			data_width;
	काष्ठा list_head	करोमुख्यs;
	काष्ठा rdt_cache	cache;
	काष्ठा rdt_membw	membw;
	स्थिर अक्षर		*क्रमmat_str;
	पूर्णांक (*parse_ctrlval)(काष्ठा rdt_parse_data *data,
			     काष्ठा rdt_resource *r,
			     काष्ठा rdt_करोमुख्य *d);
	काष्ठा list_head	evt_list;
	पूर्णांक			num_rmid;
	अचिन्हित पूर्णांक		mon_scale;
	अचिन्हित पूर्णांक		mbm_width;
	अचिन्हित दीर्घ		fflags;
पूर्ण;

पूर्णांक parse_cbm(काष्ठा rdt_parse_data *data, काष्ठा rdt_resource *r,
	      काष्ठा rdt_करोमुख्य *d);
पूर्णांक parse_bw(काष्ठा rdt_parse_data *data, काष्ठा rdt_resource *r,
	     काष्ठा rdt_करोमुख्य *d);

बाह्य काष्ठा mutex rdtgroup_mutex;

बाह्य काष्ठा rdt_resource rdt_resources_all[];
बाह्य काष्ठा rdtgroup rdtgroup_शेष;
DECLARE_STATIC_KEY_FALSE(rdt_alloc_enable_key);

बाह्य काष्ठा dentry *debugfs_resctrl;

क्रमागत अणु
	RDT_RESOURCE_L3,
	RDT_RESOURCE_L3DATA,
	RDT_RESOURCE_L3CODE,
	RDT_RESOURCE_L2,
	RDT_RESOURCE_L2DATA,
	RDT_RESOURCE_L2CODE,
	RDT_RESOURCE_MBA,

	/* Must be the last */
	RDT_NUM_RESOURCES,
पूर्ण;

#घोषणा क्रम_each_rdt_resource(r)					      \
	क्रम (r = rdt_resources_all; r < rdt_resources_all + RDT_NUM_RESOURCES;\
	     r++)

#घोषणा क्रम_each_capable_rdt_resource(r)				      \
	क्रम (r = rdt_resources_all; r < rdt_resources_all + RDT_NUM_RESOURCES;\
	     r++)							      \
		अगर (r->alloc_capable || r->mon_capable)

#घोषणा क्रम_each_alloc_capable_rdt_resource(r)				      \
	क्रम (r = rdt_resources_all; r < rdt_resources_all + RDT_NUM_RESOURCES;\
	     r++)							      \
		अगर (r->alloc_capable)

#घोषणा क्रम_each_mon_capable_rdt_resource(r)				      \
	क्रम (r = rdt_resources_all; r < rdt_resources_all + RDT_NUM_RESOURCES;\
	     r++)							      \
		अगर (r->mon_capable)

#घोषणा क्रम_each_alloc_enabled_rdt_resource(r)				      \
	क्रम (r = rdt_resources_all; r < rdt_resources_all + RDT_NUM_RESOURCES;\
	     r++)							      \
		अगर (r->alloc_enabled)

#घोषणा क्रम_each_mon_enabled_rdt_resource(r)				      \
	क्रम (r = rdt_resources_all; r < rdt_resources_all + RDT_NUM_RESOURCES;\
	     r++)							      \
		अगर (r->mon_enabled)

/* CPUID.(EAX=10H, ECX=ResID=1).EAX */
जोड़ cpuid_0x10_1_eax अणु
	काष्ठा अणु
		अचिन्हित पूर्णांक cbm_len:5;
	पूर्ण split;
	अचिन्हित पूर्णांक full;
पूर्ण;

/* CPUID.(EAX=10H, ECX=ResID=3).EAX */
जोड़ cpuid_0x10_3_eax अणु
	काष्ठा अणु
		अचिन्हित पूर्णांक max_delay:12;
	पूर्ण split;
	अचिन्हित पूर्णांक full;
पूर्ण;

/* CPUID.(EAX=10H, ECX=ResID).EDX */
जोड़ cpuid_0x10_x_edx अणु
	काष्ठा अणु
		अचिन्हित पूर्णांक cos_max:16;
	पूर्ण split;
	अचिन्हित पूर्णांक full;
पूर्ण;

व्योम rdt_last_cmd_clear(व्योम);
व्योम rdt_last_cmd_माला_दो(स्थिर अक्षर *s);
__म_लिखो(1, 2)
व्योम rdt_last_cmd_म_लिखो(स्थिर अक्षर *fmt, ...);

व्योम rdt_ctrl_update(व्योम *arg);
काष्ठा rdtgroup *rdtgroup_kn_lock_live(काष्ठा kernfs_node *kn);
व्योम rdtgroup_kn_unlock(काष्ठा kernfs_node *kn);
पूर्णांक rdtgroup_kn_mode_restrict(काष्ठा rdtgroup *r, स्थिर अक्षर *name);
पूर्णांक rdtgroup_kn_mode_restore(काष्ठा rdtgroup *r, स्थिर अक्षर *name,
			     umode_t mask);
काष्ठा rdt_करोमुख्य *rdt_find_करोमुख्य(काष्ठा rdt_resource *r, पूर्णांक id,
				   काष्ठा list_head **pos);
sमाप_प्रकार rdtgroup_schemata_ग_लिखो(काष्ठा kernfs_खोलो_file *of,
				अक्षर *buf, माप_प्रकार nbytes, loff_t off);
पूर्णांक rdtgroup_schemata_show(काष्ठा kernfs_खोलो_file *of,
			   काष्ठा seq_file *s, व्योम *v);
bool rdtgroup_cbm_overlaps(काष्ठा rdt_resource *r, काष्ठा rdt_करोमुख्य *d,
			   अचिन्हित दीर्घ cbm, पूर्णांक closid, bool exclusive);
अचिन्हित पूर्णांक rdtgroup_cbm_to_size(काष्ठा rdt_resource *r, काष्ठा rdt_करोमुख्य *d,
				  अचिन्हित दीर्घ cbm);
क्रमागत rdtgrp_mode rdtgroup_mode_by_closid(पूर्णांक closid);
पूर्णांक rdtgroup_tasks_asचिन्हित(काष्ठा rdtgroup *r);
पूर्णांक rdtgroup_locksetup_enter(काष्ठा rdtgroup *rdtgrp);
पूर्णांक rdtgroup_locksetup_निकास(काष्ठा rdtgroup *rdtgrp);
bool rdtgroup_cbm_overlaps_pseuकरो_locked(काष्ठा rdt_करोमुख्य *d, अचिन्हित दीर्घ cbm);
bool rdtgroup_pseuकरो_locked_in_hierarchy(काष्ठा rdt_करोमुख्य *d);
पूर्णांक rdt_pseuकरो_lock_init(व्योम);
व्योम rdt_pseuकरो_lock_release(व्योम);
पूर्णांक rdtgroup_pseuकरो_lock_create(काष्ठा rdtgroup *rdtgrp);
व्योम rdtgroup_pseuकरो_lock_हटाओ(काष्ठा rdtgroup *rdtgrp);
काष्ठा rdt_करोमुख्य *get_करोमुख्य_from_cpu(पूर्णांक cpu, काष्ठा rdt_resource *r);
पूर्णांक update_करोमुख्यs(काष्ठा rdt_resource *r, पूर्णांक closid);
पूर्णांक closids_supported(व्योम);
व्योम closid_मुक्त(पूर्णांक closid);
पूर्णांक alloc_rmid(व्योम);
व्योम मुक्त_rmid(u32 rmid);
पूर्णांक rdt_get_mon_l3_config(काष्ठा rdt_resource *r);
व्योम mon_event_count(व्योम *info);
पूर्णांक rdtgroup_mondata_show(काष्ठा seq_file *m, व्योम *arg);
व्योम सूची_हटाओ_mondata_subdir_allrdtgrp(काष्ठा rdt_resource *r,
				    अचिन्हित पूर्णांक करोm_id);
व्योम सूची_गढ़ो_mondata_subdir_allrdtgrp(काष्ठा rdt_resource *r,
				    काष्ठा rdt_करोमुख्य *d);
व्योम mon_event_पढ़ो(काष्ठा rmid_पढ़ो *rr, काष्ठा rdt_resource *r,
		    काष्ठा rdt_करोमुख्य *d, काष्ठा rdtgroup *rdtgrp,
		    पूर्णांक evtid, पूर्णांक first);
व्योम mbm_setup_overflow_handler(काष्ठा rdt_करोमुख्य *करोm,
				अचिन्हित दीर्घ delay_ms);
व्योम mbm_handle_overflow(काष्ठा work_काष्ठा *work);
व्योम __init पूर्णांकel_rdt_mbm_apply_quirk(व्योम);
bool is_mba_sc(काष्ठा rdt_resource *r);
व्योम setup_शेष_ctrlval(काष्ठा rdt_resource *r, u32 *dc, u32 *dm);
u32 delay_bw_map(अचिन्हित दीर्घ bw, काष्ठा rdt_resource *r);
व्योम cqm_setup_limbo_handler(काष्ठा rdt_करोमुख्य *करोm, अचिन्हित दीर्घ delay_ms);
व्योम cqm_handle_limbo(काष्ठा work_काष्ठा *work);
bool has_busy_rmid(काष्ठा rdt_resource *r, काष्ठा rdt_करोमुख्य *d);
व्योम __check_limbo(काष्ठा rdt_करोमुख्य *d, bool क्रमce_मुक्त);
व्योम rdt_करोमुख्य_reconfigure_cdp(काष्ठा rdt_resource *r);
व्योम __init thपढ़ो_throttle_mode_init(व्योम);

#पूर्ण_अगर /* _ASM_X86_RESCTRL_INTERNAL_H */
