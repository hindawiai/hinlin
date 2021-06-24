<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */

/* Generic device ID of a discovery table device */
#घोषणा UNCORE_DISCOVERY_TABLE_DEVICE		0x09a7
/* Capability ID क्रम a discovery table device */
#घोषणा UNCORE_EXT_CAP_ID_DISCOVERY		0x23
/* First DVSEC offset */
#घोषणा UNCORE_DISCOVERY_DVSEC_OFFSET		0x8
/* Mask of the supported discovery entry type */
#घोषणा UNCORE_DISCOVERY_DVSEC_ID_MASK		0xffff
/* PMON discovery entry type ID */
#घोषणा UNCORE_DISCOVERY_DVSEC_ID_PMON		0x1
/* Second DVSEC offset */
#घोषणा UNCORE_DISCOVERY_DVSEC2_OFFSET		0xc
/* Mask of the discovery table BAR offset */
#घोषणा UNCORE_DISCOVERY_DVSEC2_BIR_MASK	0x7
/* Discovery table BAR base offset */
#घोषणा UNCORE_DISCOVERY_BIR_BASE		0x10
/* Discovery table BAR step */
#घोषणा UNCORE_DISCOVERY_BIR_STEP		0x4
/* Mask of the discovery table offset */
#घोषणा UNCORE_DISCOVERY_MASK			0xf
/* Global discovery table size */
#घोषणा UNCORE_DISCOVERY_GLOBAL_MAP_SIZE	0x20

#घोषणा UNCORE_DISCOVERY_PCI_DOMAIN(data)	((data >> 28) & 0x7)
#घोषणा UNCORE_DISCOVERY_PCI_BUS(data)		((data >> 20) & 0xff)
#घोषणा UNCORE_DISCOVERY_PCI_DEVFN(data)	((data >> 12) & 0xff)
#घोषणा UNCORE_DISCOVERY_PCI_BOX_CTRL(data)	(data & 0xfff)


#घोषणा uncore_discovery_invalid_unit(unit)			\
	(!unit.table1 || !unit.ctl || !unit.table3 ||	\
	 unit.table1 == -1ULL || unit.ctl == -1ULL ||	\
	 unit.table3 == -1ULL)

#घोषणा GENERIC_PMON_CTL_EV_SEL_MASK	0x000000ff
#घोषणा GENERIC_PMON_CTL_UMASK_MASK	0x0000ff00
#घोषणा GENERIC_PMON_CTL_EDGE_DET	(1 << 18)
#घोषणा GENERIC_PMON_CTL_INVERT		(1 << 23)
#घोषणा GENERIC_PMON_CTL_TRESH_MASK	0xff000000
#घोषणा GENERIC_PMON_RAW_EVENT_MASK	(GENERIC_PMON_CTL_EV_SEL_MASK | \
					 GENERIC_PMON_CTL_UMASK_MASK | \
					 GENERIC_PMON_CTL_EDGE_DET | \
					 GENERIC_PMON_CTL_INVERT | \
					 GENERIC_PMON_CTL_TRESH_MASK)

#घोषणा GENERIC_PMON_BOX_CTL_FRZ	(1 << 0)
#घोषणा GENERIC_PMON_BOX_CTL_RST_CTRL	(1 << 8)
#घोषणा GENERIC_PMON_BOX_CTL_RST_CTRS	(1 << 9)
#घोषणा GENERIC_PMON_BOX_CTL_INT	(GENERIC_PMON_BOX_CTL_RST_CTRL | \
					 GENERIC_PMON_BOX_CTL_RST_CTRS)

क्रमागत uncore_access_type अणु
	UNCORE_ACCESS_MSR	= 0,
	UNCORE_ACCESS_MMIO,
	UNCORE_ACCESS_PCI,

	UNCORE_ACCESS_MAX,
पूर्ण;

काष्ठा uncore_global_discovery अणु
	जोड़ अणु
		u64	table1;
		काष्ठा अणु
			u64	type : 8,
				stride : 8,
				max_units : 10,
				__reserved_1 : 36,
				access_type : 2;
		पूर्ण;
	पूर्ण;

	u64	ctl;		/* Global Control Address */

	जोड़ अणु
		u64	table3;
		काष्ठा अणु
			u64	status_offset : 8,
				num_status : 16,
				__reserved_2 : 40;
		पूर्ण;
	पूर्ण;
पूर्ण;

काष्ठा uncore_unit_discovery अणु
	जोड़ अणु
		u64	table1;
		काष्ठा अणु
			u64	num_regs : 8,
				ctl_offset : 8,
				bit_width : 8,
				ctr_offset : 8,
				status_offset : 8,
				__reserved_1 : 22,
				access_type : 2;
			पूर्ण;
		पूर्ण;

	u64	ctl;		/* Unit Control Address */

	जोड़ अणु
		u64	table3;
		काष्ठा अणु
			u64	box_type : 16,
				box_id : 16,
				__reserved_2 : 32;
		पूर्ण;
	पूर्ण;
पूर्ण;

काष्ठा पूर्णांकel_uncore_discovery_type अणु
	काष्ठा rb_node	node;
	क्रमागत uncore_access_type	access_type;
	u64		box_ctrl;	/* Unit ctrl addr of the first box */
	u64		*box_ctrl_die;	/* Unit ctrl addr of the first box of each die */
	u16		type;		/* Type ID of the uncore block */
	u8		num_counters;
	u8		counter_width;
	u8		ctl_offset;	/* Counter Control 0 offset */
	u8		ctr_offset;	/* Counter 0 offset */
	u16		num_boxes;	/* number of boxes क्रम the uncore block */
	अचिन्हित पूर्णांक	*ids;		/* Box IDs */
	अचिन्हित पूर्णांक	*box_offset;	/* Box offset */
पूर्ण;

bool पूर्णांकel_uncore_has_discovery_tables(व्योम);
व्योम पूर्णांकel_uncore_clear_discovery_tables(व्योम);
व्योम पूर्णांकel_uncore_generic_uncore_cpu_init(व्योम);
पूर्णांक पूर्णांकel_uncore_generic_uncore_pci_init(व्योम);
व्योम पूर्णांकel_uncore_generic_uncore_mmio_init(व्योम);
