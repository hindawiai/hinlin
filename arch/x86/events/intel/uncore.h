<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#समावेश <linux/slab.h>
#समावेश <linux/pci.h>
#समावेश <यंत्र/apicdef.h>
#समावेश <linux/io-64-nonatomic-lo-hi.h>

#समावेश <linux/perf_event.h>
#समावेश "../perf_event.h"

#घोषणा UNCORE_PMU_NAME_LEN		32
#घोषणा UNCORE_PMU_HRTIMER_INTERVAL	(60LL * NSEC_PER_SEC)
#घोषणा UNCORE_SNB_IMC_HRTIMER_INTERVAL (5ULL * NSEC_PER_SEC)

#घोषणा UNCORE_FIXED_EVENT		0xff
#घोषणा UNCORE_PMC_IDX_MAX_GENERIC	8
#घोषणा UNCORE_PMC_IDX_MAX_FIXED	1
#घोषणा UNCORE_PMC_IDX_MAX_FREERUNNING	1
#घोषणा UNCORE_PMC_IDX_FIXED		UNCORE_PMC_IDX_MAX_GENERIC
#घोषणा UNCORE_PMC_IDX_FREERUNNING	(UNCORE_PMC_IDX_FIXED + \
					UNCORE_PMC_IDX_MAX_FIXED)
#घोषणा UNCORE_PMC_IDX_MAX		(UNCORE_PMC_IDX_FREERUNNING + \
					UNCORE_PMC_IDX_MAX_FREERUNNING)

#घोषणा UNCORE_PCI_DEV_FULL_DATA(dev, func, type, idx)	\
		((dev << 24) | (func << 16) | (type << 8) | idx)
#घोषणा UNCORE_PCI_DEV_DATA(type, idx)	((type << 8) | idx)
#घोषणा UNCORE_PCI_DEV_DEV(data)	((data >> 24) & 0xff)
#घोषणा UNCORE_PCI_DEV_FUNC(data)	((data >> 16) & 0xff)
#घोषणा UNCORE_PCI_DEV_TYPE(data)	((data >> 8) & 0xff)
#घोषणा UNCORE_PCI_DEV_IDX(data)	(data & 0xff)
#घोषणा UNCORE_EXTRA_PCI_DEV		0xff
#घोषणा UNCORE_EXTRA_PCI_DEV_MAX	4

#घोषणा UNCORE_EVENT_CONSTRAINT(c, n) EVENT_CONSTRAINT(c, n, 0xff)

काष्ठा pci_extra_dev अणु
	काष्ठा pci_dev *dev[UNCORE_EXTRA_PCI_DEV_MAX];
पूर्ण;

काष्ठा पूर्णांकel_uncore_ops;
काष्ठा पूर्णांकel_uncore_pmu;
काष्ठा पूर्णांकel_uncore_box;
काष्ठा uncore_event_desc;
काष्ठा मुक्तrunning_counters;
काष्ठा पूर्णांकel_uncore_topology;

काष्ठा पूर्णांकel_uncore_type अणु
	स्थिर अक्षर *name;
	पूर्णांक num_counters;
	पूर्णांक num_boxes;
	पूर्णांक perf_ctr_bits;
	पूर्णांक fixed_ctr_bits;
	पूर्णांक num_मुक्तrunning_types;
	पूर्णांक type_id;
	अचिन्हित perf_ctr;
	अचिन्हित event_ctl;
	अचिन्हित event_mask;
	अचिन्हित event_mask_ext;
	अचिन्हित fixed_ctr;
	अचिन्हित fixed_ctl;
	अचिन्हित box_ctl;
	u64 *box_ctls;	/* Unit ctrl addr of the first box of each die */
	जोड़ अणु
		अचिन्हित msr_offset;
		अचिन्हित mmio_offset;
	पूर्ण;
	अचिन्हित mmio_map_size;
	अचिन्हित num_shared_regs:8;
	अचिन्हित single_fixed:1;
	अचिन्हित pair_ctr_ctl:1;
	जोड़ अणु
		अचिन्हित *msr_offsets;
		अचिन्हित *pci_offsets;
		अचिन्हित *mmio_offsets;
	पूर्ण;
	अचिन्हित *box_ids;
	काष्ठा event_स्थिरraपूर्णांक unस्थिरraपूर्णांकed;
	काष्ठा event_स्थिरraपूर्णांक *स्थिरraपूर्णांकs;
	काष्ठा पूर्णांकel_uncore_pmu *pmus;
	काष्ठा पूर्णांकel_uncore_ops *ops;
	काष्ठा uncore_event_desc *event_descs;
	काष्ठा मुक्तrunning_counters *मुक्तrunning;
	स्थिर काष्ठा attribute_group *attr_groups[4];
	स्थिर काष्ठा attribute_group **attr_update;
	काष्ठा pmu *pmu; /* क्रम custom pmu ops */
	/*
	 * Uncore PMU would store relevant platक्रमm topology configuration here
	 * to identअगरy which platक्रमm component each PMON block of that type is
	 * supposed to monitor.
	 */
	काष्ठा पूर्णांकel_uncore_topology *topology;
	/*
	 * Optional callbacks क्रम managing mapping of Uncore units to PMONs
	 */
	पूर्णांक (*set_mapping)(काष्ठा पूर्णांकel_uncore_type *type);
	व्योम (*cleanup_mapping)(काष्ठा पूर्णांकel_uncore_type *type);
पूर्ण;

#घोषणा pmu_group attr_groups[0]
#घोषणा क्रमmat_group attr_groups[1]
#घोषणा events_group attr_groups[2]

काष्ठा पूर्णांकel_uncore_ops अणु
	व्योम (*init_box)(काष्ठा पूर्णांकel_uncore_box *);
	व्योम (*निकास_box)(काष्ठा पूर्णांकel_uncore_box *);
	व्योम (*disable_box)(काष्ठा पूर्णांकel_uncore_box *);
	व्योम (*enable_box)(काष्ठा पूर्णांकel_uncore_box *);
	व्योम (*disable_event)(काष्ठा पूर्णांकel_uncore_box *, काष्ठा perf_event *);
	व्योम (*enable_event)(काष्ठा पूर्णांकel_uncore_box *, काष्ठा perf_event *);
	u64 (*पढ़ो_counter)(काष्ठा पूर्णांकel_uncore_box *, काष्ठा perf_event *);
	पूर्णांक (*hw_config)(काष्ठा पूर्णांकel_uncore_box *, काष्ठा perf_event *);
	काष्ठा event_स्थिरraपूर्णांक *(*get_स्थिरraपूर्णांक)(काष्ठा पूर्णांकel_uncore_box *,
						   काष्ठा perf_event *);
	व्योम (*put_स्थिरraपूर्णांक)(काष्ठा पूर्णांकel_uncore_box *, काष्ठा perf_event *);
पूर्ण;

काष्ठा पूर्णांकel_uncore_pmu अणु
	काष्ठा pmu			pmu;
	अक्षर				name[UNCORE_PMU_NAME_LEN];
	पूर्णांक				pmu_idx;
	पूर्णांक				func_id;
	bool				रेजिस्टरed;
	atomic_t			activeboxes;
	काष्ठा पूर्णांकel_uncore_type	*type;
	काष्ठा पूर्णांकel_uncore_box		**boxes;
पूर्ण;

काष्ठा पूर्णांकel_uncore_extra_reg अणु
	raw_spinlock_t lock;
	u64 config, config1, config2;
	atomic_t ref;
पूर्ण;

काष्ठा पूर्णांकel_uncore_box अणु
	पूर्णांक dieid;	/* Logical die ID */
	पूर्णांक n_active;	/* number of active events */
	पूर्णांक n_events;
	पूर्णांक cpu;	/* cpu to collect events */
	अचिन्हित दीर्घ flags;
	atomic_t refcnt;
	काष्ठा perf_event *events[UNCORE_PMC_IDX_MAX];
	काष्ठा perf_event *event_list[UNCORE_PMC_IDX_MAX];
	काष्ठा event_स्थिरraपूर्णांक *event_स्थिरraपूर्णांक[UNCORE_PMC_IDX_MAX];
	अचिन्हित दीर्घ active_mask[BITS_TO_LONGS(UNCORE_PMC_IDX_MAX)];
	u64 tags[UNCORE_PMC_IDX_MAX];
	काष्ठा pci_dev *pci_dev;
	काष्ठा पूर्णांकel_uncore_pmu *pmu;
	u64 hrसमयr_duration; /* hrसमयr समयout क्रम this box */
	काष्ठा hrसमयr hrसमयr;
	काष्ठा list_head list;
	काष्ठा list_head active_list;
	व्योम __iomem *io_addr;
	काष्ठा पूर्णांकel_uncore_extra_reg shared_regs[];
पूर्ण;

/* CFL uncore 8th cbox MSRs */
#घोषणा CFL_UNC_CBO_7_PERFEVTSEL0		0xf70
#घोषणा CFL_UNC_CBO_7_PER_CTR0			0xf76

#घोषणा UNCORE_BOX_FLAG_INITIATED		0
/* event config रेजिस्टरs are 8-byte apart */
#घोषणा UNCORE_BOX_FLAG_CTL_OFFS8		1
/* CFL 8th CBOX has dअगरferent MSR space */
#घोषणा UNCORE_BOX_FLAG_CFL8_CBOX_MSR_OFFS	2

काष्ठा uncore_event_desc अणु
	काष्ठा device_attribute attr;
	स्थिर अक्षर *config;
पूर्ण;

काष्ठा मुक्तrunning_counters अणु
	अचिन्हित पूर्णांक counter_base;
	अचिन्हित पूर्णांक counter_offset;
	अचिन्हित पूर्णांक box_offset;
	अचिन्हित पूर्णांक num_counters;
	अचिन्हित पूर्णांक bits;
	अचिन्हित *box_offsets;
पूर्ण;

काष्ठा पूर्णांकel_uncore_topology अणु
	u64 configuration;
	पूर्णांक segment;
पूर्ण;

काष्ठा pci2phy_map अणु
	काष्ठा list_head list;
	पूर्णांक segment;
	पूर्णांक pbus_to_dieid[256];
पूर्ण;

काष्ठा pci2phy_map *__find_pci2phy_map(पूर्णांक segment);
पूर्णांक uncore_pcibus_to_dieid(काष्ठा pci_bus *bus);
पूर्णांक uncore_die_to_segment(पूर्णांक die);

sमाप_प्रकार uncore_event_show(काष्ठा device *dev,
			  काष्ठा device_attribute *attr, अक्षर *buf);

अटल अंतरभूत काष्ठा पूर्णांकel_uncore_pmu *dev_to_uncore_pmu(काष्ठा device *dev)
अणु
	वापस container_of(dev_get_drvdata(dev), काष्ठा पूर्णांकel_uncore_pmu, pmu);
पूर्ण

#घोषणा to_device_attribute(n)	container_of(n, काष्ठा device_attribute, attr)
#घोषणा to_dev_ext_attribute(n)	container_of(n, काष्ठा dev_ext_attribute, attr)
#घोषणा attr_to_ext_attr(n)	to_dev_ext_attribute(to_device_attribute(n))

बाह्य पूर्णांक __uncore_max_dies;
#घोषणा uncore_max_dies()	(__uncore_max_dies)

#घोषणा INTEL_UNCORE_EVENT_DESC(_name, _config)			\
अणु								\
	.attr	= __ATTR(_name, 0444, uncore_event_show, शून्य),	\
	.config	= _config,					\
पूर्ण

#घोषणा DEFINE_UNCORE_FORMAT_ATTR(_var, _name, _क्रमmat)			\
अटल sमाप_प्रकार __uncore_##_var##_show(काष्ठा device *dev,		\
				काष्ठा device_attribute *attr,		\
				अक्षर *page)				\
अणु									\
	BUILD_BUG_ON(माप(_क्रमmat) >= PAGE_SIZE);			\
	वापस प्र_लिखो(page, _क्रमmat "\n");				\
पूर्ण									\
अटल काष्ठा device_attribute क्रमmat_attr_##_var =			\
	__ATTR(_name, 0444, __uncore_##_var##_show, शून्य)

अटल अंतरभूत bool uncore_pmc_fixed(पूर्णांक idx)
अणु
	वापस idx == UNCORE_PMC_IDX_FIXED;
पूर्ण

अटल अंतरभूत bool uncore_pmc_मुक्तrunning(पूर्णांक idx)
अणु
	वापस idx == UNCORE_PMC_IDX_FREERUNNING;
पूर्ण

अटल अंतरभूत bool uncore_mmio_is_valid_offset(काष्ठा पूर्णांकel_uncore_box *box,
					       अचिन्हित दीर्घ offset)
अणु
	अगर (offset < box->pmu->type->mmio_map_size)
		वापस true;

	pr_warn_once("perf uncore: Invalid offset 0x%lx exceeds mapped area of %s.\n",
		     offset, box->pmu->type->name);

	वापस false;
पूर्ण

अटल अंतरभूत
अचिन्हित पूर्णांक uncore_mmio_box_ctl(काष्ठा पूर्णांकel_uncore_box *box)
अणु
	वापस box->pmu->type->box_ctl +
	       box->pmu->type->mmio_offset * box->pmu->pmu_idx;
पूर्ण

अटल अंतरभूत अचिन्हित uncore_pci_box_ctl(काष्ठा पूर्णांकel_uncore_box *box)
अणु
	वापस box->pmu->type->box_ctl;
पूर्ण

अटल अंतरभूत अचिन्हित uncore_pci_fixed_ctl(काष्ठा पूर्णांकel_uncore_box *box)
अणु
	वापस box->pmu->type->fixed_ctl;
पूर्ण

अटल अंतरभूत अचिन्हित uncore_pci_fixed_ctr(काष्ठा पूर्णांकel_uncore_box *box)
अणु
	वापस box->pmu->type->fixed_ctr;
पूर्ण

अटल अंतरभूत
अचिन्हित uncore_pci_event_ctl(काष्ठा पूर्णांकel_uncore_box *box, पूर्णांक idx)
अणु
	अगर (test_bit(UNCORE_BOX_FLAG_CTL_OFFS8, &box->flags))
		वापस idx * 8 + box->pmu->type->event_ctl;

	वापस idx * 4 + box->pmu->type->event_ctl;
पूर्ण

अटल अंतरभूत
अचिन्हित uncore_pci_perf_ctr(काष्ठा पूर्णांकel_uncore_box *box, पूर्णांक idx)
अणु
	वापस idx * 8 + box->pmu->type->perf_ctr;
पूर्ण

अटल अंतरभूत अचिन्हित uncore_msr_box_offset(काष्ठा पूर्णांकel_uncore_box *box)
अणु
	काष्ठा पूर्णांकel_uncore_pmu *pmu = box->pmu;
	वापस pmu->type->msr_offsets ?
		pmu->type->msr_offsets[pmu->pmu_idx] :
		pmu->type->msr_offset * pmu->pmu_idx;
पूर्ण

अटल अंतरभूत अचिन्हित uncore_msr_box_ctl(काष्ठा पूर्णांकel_uncore_box *box)
अणु
	अगर (!box->pmu->type->box_ctl)
		वापस 0;
	वापस box->pmu->type->box_ctl + uncore_msr_box_offset(box);
पूर्ण

अटल अंतरभूत अचिन्हित uncore_msr_fixed_ctl(काष्ठा पूर्णांकel_uncore_box *box)
अणु
	अगर (!box->pmu->type->fixed_ctl)
		वापस 0;
	वापस box->pmu->type->fixed_ctl + uncore_msr_box_offset(box);
पूर्ण

अटल अंतरभूत अचिन्हित uncore_msr_fixed_ctr(काष्ठा पूर्णांकel_uncore_box *box)
अणु
	वापस box->pmu->type->fixed_ctr + uncore_msr_box_offset(box);
पूर्ण


/*
 * In the uncore करोcument, there is no event-code asचिन्हित to मुक्त running
 * counters. Some events need to be defined to indicate the मुक्त running
 * counters. The events are encoded as event-code + umask-code.
 *
 * The event-code क्रम all मुक्त running counters is 0xff, which is the same as
 * the fixed counters.
 *
 * The umask-code is used to distinguish a fixed counter and a मुक्त running
 * counter, and dअगरferent types of मुक्त running counters.
 * - For fixed counters, the umask-code is 0x0X.
 *   X indicates the index of the fixed counter, which starts from 0.
 * - For मुक्त running counters, the umask-code uses the rest of the space.
 *   It would bare the क्रमmat of 0xXY.
 *   X stands क्रम the type of मुक्त running counters, which starts from 1.
 *   Y stands क्रम the index of मुक्त running counters of same type, which
 *   starts from 0.
 *
 * For example, there are three types of IIO मुक्त running counters on Skylake
 * server, IO CLOCKS counters, BANDWIDTH counters and UTILIZATION counters.
 * The event-code क्रम all the मुक्त running counters is 0xff.
 * 'ioclk' is the first counter of IO CLOCKS. IO CLOCKS is the first type,
 * which umask-code starts from 0x10.
 * So 'ioclk' is encoded as event=0xff,umask=0x10
 * 'bw_in_port2' is the third counter of BANDWIDTH counters. BANDWIDTH is
 * the second type, which umask-code starts from 0x20.
 * So 'bw_in_port2' is encoded as event=0xff,umask=0x22
 */
अटल अंतरभूत अचिन्हित पूर्णांक uncore_मुक्तrunning_idx(u64 config)
अणु
	वापस ((config >> 8) & 0xf);
पूर्ण

#घोषणा UNCORE_FREERUNNING_UMASK_START		0x10

अटल अंतरभूत अचिन्हित पूर्णांक uncore_मुक्तrunning_type(u64 config)
अणु
	वापस ((((config >> 8) - UNCORE_FREERUNNING_UMASK_START) >> 4) & 0xf);
पूर्ण

अटल अंतरभूत
अचिन्हित पूर्णांक uncore_मुक्तrunning_counter(काष्ठा पूर्णांकel_uncore_box *box,
					काष्ठा perf_event *event)
अणु
	अचिन्हित पूर्णांक type = uncore_मुक्तrunning_type(event->hw.config);
	अचिन्हित पूर्णांक idx = uncore_मुक्तrunning_idx(event->hw.config);
	काष्ठा पूर्णांकel_uncore_pmu *pmu = box->pmu;

	वापस pmu->type->मुक्तrunning[type].counter_base +
	       pmu->type->मुक्तrunning[type].counter_offset * idx +
	       (pmu->type->मुक्तrunning[type].box_offsets ?
	        pmu->type->मुक्तrunning[type].box_offsets[pmu->pmu_idx] :
	        pmu->type->मुक्तrunning[type].box_offset * pmu->pmu_idx);
पूर्ण

अटल अंतरभूत
अचिन्हित uncore_msr_event_ctl(काष्ठा पूर्णांकel_uncore_box *box, पूर्णांक idx)
अणु
	अगर (test_bit(UNCORE_BOX_FLAG_CFL8_CBOX_MSR_OFFS, &box->flags)) अणु
		वापस CFL_UNC_CBO_7_PERFEVTSEL0 +
		       (box->pmu->type->pair_ctr_ctl ? 2 * idx : idx);
	पूर्ण अन्यथा अणु
		वापस box->pmu->type->event_ctl +
		       (box->pmu->type->pair_ctr_ctl ? 2 * idx : idx) +
		       uncore_msr_box_offset(box);
	पूर्ण
पूर्ण

अटल अंतरभूत
अचिन्हित uncore_msr_perf_ctr(काष्ठा पूर्णांकel_uncore_box *box, पूर्णांक idx)
अणु
	अगर (test_bit(UNCORE_BOX_FLAG_CFL8_CBOX_MSR_OFFS, &box->flags)) अणु
		वापस CFL_UNC_CBO_7_PER_CTR0 +
		       (box->pmu->type->pair_ctr_ctl ? 2 * idx : idx);
	पूर्ण अन्यथा अणु
		वापस box->pmu->type->perf_ctr +
		       (box->pmu->type->pair_ctr_ctl ? 2 * idx : idx) +
		       uncore_msr_box_offset(box);
	पूर्ण
पूर्ण

अटल अंतरभूत
अचिन्हित uncore_fixed_ctl(काष्ठा पूर्णांकel_uncore_box *box)
अणु
	अगर (box->pci_dev || box->io_addr)
		वापस uncore_pci_fixed_ctl(box);
	अन्यथा
		वापस uncore_msr_fixed_ctl(box);
पूर्ण

अटल अंतरभूत
अचिन्हित uncore_fixed_ctr(काष्ठा पूर्णांकel_uncore_box *box)
अणु
	अगर (box->pci_dev || box->io_addr)
		वापस uncore_pci_fixed_ctr(box);
	अन्यथा
		वापस uncore_msr_fixed_ctr(box);
पूर्ण

अटल अंतरभूत
अचिन्हित uncore_event_ctl(काष्ठा पूर्णांकel_uncore_box *box, पूर्णांक idx)
अणु
	अगर (box->pci_dev || box->io_addr)
		वापस uncore_pci_event_ctl(box, idx);
	अन्यथा
		वापस uncore_msr_event_ctl(box, idx);
पूर्ण

अटल अंतरभूत
अचिन्हित uncore_perf_ctr(काष्ठा पूर्णांकel_uncore_box *box, पूर्णांक idx)
अणु
	अगर (box->pci_dev || box->io_addr)
		वापस uncore_pci_perf_ctr(box, idx);
	अन्यथा
		वापस uncore_msr_perf_ctr(box, idx);
पूर्ण

अटल अंतरभूत पूर्णांक uncore_perf_ctr_bits(काष्ठा पूर्णांकel_uncore_box *box)
अणु
	वापस box->pmu->type->perf_ctr_bits;
पूर्ण

अटल अंतरभूत पूर्णांक uncore_fixed_ctr_bits(काष्ठा पूर्णांकel_uncore_box *box)
अणु
	वापस box->pmu->type->fixed_ctr_bits;
पूर्ण

अटल अंतरभूत
अचिन्हित पूर्णांक uncore_मुक्तrunning_bits(काष्ठा पूर्णांकel_uncore_box *box,
				     काष्ठा perf_event *event)
अणु
	अचिन्हित पूर्णांक type = uncore_मुक्तrunning_type(event->hw.config);

	वापस box->pmu->type->मुक्तrunning[type].bits;
पूर्ण

अटल अंतरभूत पूर्णांक uncore_num_मुक्तrunning(काष्ठा पूर्णांकel_uncore_box *box,
					 काष्ठा perf_event *event)
अणु
	अचिन्हित पूर्णांक type = uncore_मुक्तrunning_type(event->hw.config);

	वापस box->pmu->type->मुक्तrunning[type].num_counters;
पूर्ण

अटल अंतरभूत पूर्णांक uncore_num_मुक्तrunning_types(काष्ठा पूर्णांकel_uncore_box *box,
					       काष्ठा perf_event *event)
अणु
	वापस box->pmu->type->num_मुक्तrunning_types;
पूर्ण

अटल अंतरभूत bool check_valid_मुक्तrunning_event(काष्ठा पूर्णांकel_uncore_box *box,
						 काष्ठा perf_event *event)
अणु
	अचिन्हित पूर्णांक type = uncore_मुक्तrunning_type(event->hw.config);
	अचिन्हित पूर्णांक idx = uncore_मुक्तrunning_idx(event->hw.config);

	वापस (type < uncore_num_मुक्तrunning_types(box, event)) &&
	       (idx < uncore_num_मुक्तrunning(box, event));
पूर्ण

अटल अंतरभूत पूर्णांक uncore_num_counters(काष्ठा पूर्णांकel_uncore_box *box)
अणु
	वापस box->pmu->type->num_counters;
पूर्ण

अटल अंतरभूत bool is_मुक्तrunning_event(काष्ठा perf_event *event)
अणु
	u64 cfg = event->attr.config;

	वापस ((cfg & UNCORE_FIXED_EVENT) == UNCORE_FIXED_EVENT) &&
	       (((cfg >> 8) & 0xff) >= UNCORE_FREERUNNING_UMASK_START);
पूर्ण

/* Check and reject invalid config */
अटल अंतरभूत पूर्णांक uncore_मुक्तrunning_hw_config(काष्ठा पूर्णांकel_uncore_box *box,
					       काष्ठा perf_event *event)
अणु
	अगर (is_मुक्तrunning_event(event))
		वापस 0;

	वापस -EINVAL;
पूर्ण

अटल अंतरभूत व्योम uncore_disable_event(काष्ठा पूर्णांकel_uncore_box *box,
				काष्ठा perf_event *event)
अणु
	box->pmu->type->ops->disable_event(box, event);
पूर्ण

अटल अंतरभूत व्योम uncore_enable_event(काष्ठा पूर्णांकel_uncore_box *box,
				काष्ठा perf_event *event)
अणु
	box->pmu->type->ops->enable_event(box, event);
पूर्ण

अटल अंतरभूत u64 uncore_पढ़ो_counter(काष्ठा पूर्णांकel_uncore_box *box,
				काष्ठा perf_event *event)
अणु
	वापस box->pmu->type->ops->पढ़ो_counter(box, event);
पूर्ण

अटल अंतरभूत व्योम uncore_box_init(काष्ठा पूर्णांकel_uncore_box *box)
अणु
	अगर (!test_and_set_bit(UNCORE_BOX_FLAG_INITIATED, &box->flags)) अणु
		अगर (box->pmu->type->ops->init_box)
			box->pmu->type->ops->init_box(box);
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम uncore_box_निकास(काष्ठा पूर्णांकel_uncore_box *box)
अणु
	अगर (test_and_clear_bit(UNCORE_BOX_FLAG_INITIATED, &box->flags)) अणु
		अगर (box->pmu->type->ops->निकास_box)
			box->pmu->type->ops->निकास_box(box);
	पूर्ण
पूर्ण

अटल अंतरभूत bool uncore_box_is_fake(काष्ठा पूर्णांकel_uncore_box *box)
अणु
	वापस (box->dieid < 0);
पूर्ण

अटल अंतरभूत काष्ठा पूर्णांकel_uncore_pmu *uncore_event_to_pmu(काष्ठा perf_event *event)
अणु
	वापस container_of(event->pmu, काष्ठा पूर्णांकel_uncore_pmu, pmu);
पूर्ण

अटल अंतरभूत काष्ठा पूर्णांकel_uncore_box *uncore_event_to_box(काष्ठा perf_event *event)
अणु
	वापस event->pmu_निजी;
पूर्ण

काष्ठा पूर्णांकel_uncore_box *uncore_pmu_to_box(काष्ठा पूर्णांकel_uncore_pmu *pmu, पूर्णांक cpu);
u64 uncore_msr_पढ़ो_counter(काष्ठा पूर्णांकel_uncore_box *box, काष्ठा perf_event *event);
व्योम uncore_mmio_निकास_box(काष्ठा पूर्णांकel_uncore_box *box);
u64 uncore_mmio_पढ़ो_counter(काष्ठा पूर्णांकel_uncore_box *box,
			     काष्ठा perf_event *event);
व्योम uncore_pmu_start_hrसमयr(काष्ठा पूर्णांकel_uncore_box *box);
व्योम uncore_pmu_cancel_hrसमयr(काष्ठा पूर्णांकel_uncore_box *box);
व्योम uncore_pmu_event_start(काष्ठा perf_event *event, पूर्णांक flags);
व्योम uncore_pmu_event_stop(काष्ठा perf_event *event, पूर्णांक flags);
पूर्णांक uncore_pmu_event_add(काष्ठा perf_event *event, पूर्णांक flags);
व्योम uncore_pmu_event_del(काष्ठा perf_event *event, पूर्णांक flags);
व्योम uncore_pmu_event_पढ़ो(काष्ठा perf_event *event);
व्योम uncore_perf_event_update(काष्ठा पूर्णांकel_uncore_box *box, काष्ठा perf_event *event);
काष्ठा event_स्थिरraपूर्णांक *
uncore_get_स्थिरraपूर्णांक(काष्ठा पूर्णांकel_uncore_box *box, काष्ठा perf_event *event);
व्योम uncore_put_स्थिरraपूर्णांक(काष्ठा पूर्णांकel_uncore_box *box, काष्ठा perf_event *event);
u64 uncore_shared_reg_config(काष्ठा पूर्णांकel_uncore_box *box, पूर्णांक idx);

बाह्य काष्ठा पूर्णांकel_uncore_type *empty_uncore[];
बाह्य काष्ठा पूर्णांकel_uncore_type **uncore_msr_uncores;
बाह्य काष्ठा पूर्णांकel_uncore_type **uncore_pci_uncores;
बाह्य काष्ठा पूर्णांकel_uncore_type **uncore_mmio_uncores;
बाह्य काष्ठा pci_driver *uncore_pci_driver;
बाह्य काष्ठा pci_driver *uncore_pci_sub_driver;
बाह्य raw_spinlock_t pci2phy_map_lock;
बाह्य काष्ठा list_head pci2phy_map_head;
बाह्य काष्ठा pci_extra_dev *uncore_extra_pci_dev;
बाह्य काष्ठा event_स्थिरraपूर्णांक uncore_स्थिरraपूर्णांक_empty;

/* uncore_snb.c */
पूर्णांक snb_uncore_pci_init(व्योम);
पूर्णांक ivb_uncore_pci_init(व्योम);
पूर्णांक hsw_uncore_pci_init(व्योम);
पूर्णांक bdw_uncore_pci_init(व्योम);
पूर्णांक skl_uncore_pci_init(व्योम);
व्योम snb_uncore_cpu_init(व्योम);
व्योम nhm_uncore_cpu_init(व्योम);
व्योम skl_uncore_cpu_init(व्योम);
व्योम icl_uncore_cpu_init(व्योम);
व्योम adl_uncore_cpu_init(व्योम);
व्योम tgl_uncore_cpu_init(व्योम);
व्योम tgl_uncore_mmio_init(व्योम);
व्योम tgl_l_uncore_mmio_init(व्योम);
पूर्णांक snb_pci2phy_map_init(पूर्णांक devid);

/* uncore_snbep.c */
पूर्णांक snbep_uncore_pci_init(व्योम);
व्योम snbep_uncore_cpu_init(व्योम);
पूर्णांक ivbep_uncore_pci_init(व्योम);
व्योम ivbep_uncore_cpu_init(व्योम);
पूर्णांक hswep_uncore_pci_init(व्योम);
व्योम hswep_uncore_cpu_init(व्योम);
पूर्णांक bdx_uncore_pci_init(व्योम);
व्योम bdx_uncore_cpu_init(व्योम);
पूर्णांक knl_uncore_pci_init(व्योम);
व्योम knl_uncore_cpu_init(व्योम);
पूर्णांक skx_uncore_pci_init(व्योम);
व्योम skx_uncore_cpu_init(व्योम);
पूर्णांक snr_uncore_pci_init(व्योम);
व्योम snr_uncore_cpu_init(व्योम);
व्योम snr_uncore_mmio_init(व्योम);
पूर्णांक icx_uncore_pci_init(व्योम);
व्योम icx_uncore_cpu_init(व्योम);
व्योम icx_uncore_mmio_init(व्योम);

/* uncore_nhmex.c */
व्योम nhmex_uncore_cpu_init(व्योम);
