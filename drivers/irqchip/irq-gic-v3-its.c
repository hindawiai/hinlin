<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2013-2017 ARM Limited, All Rights Reserved.
 * Author: Marc Zyngier <marc.zyngier@arm.com>
 */

#समावेश <linux/acpi.h>
#समावेश <linux/acpi_iort.h>
#समावेश <linux/bitfield.h>
#समावेश <linux/biपंचांगap.h>
#समावेश <linux/cpu.h>
#समावेश <linux/crash_dump.h>
#समावेश <linux/delay.h>
#समावेश <linux/dma-iommu.h>
#समावेश <linux/efi.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/iopoll.h>
#समावेश <linux/irqकरोमुख्य.h>
#समावेश <linux/list.h>
#समावेश <linux/log2.h>
#समावेश <linux/memblock.h>
#समावेश <linux/mm.h>
#समावेश <linux/msi.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/of_pci.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/percpu.h>
#समावेश <linux/slab.h>
#समावेश <linux/syscore_ops.h>

#समावेश <linux/irqchip.h>
#समावेश <linux/irqchip/arm-gic-v3.h>
#समावेश <linux/irqchip/arm-gic-v4.h>

#समावेश <यंत्र/cputype.h>
#समावेश <यंत्र/exception.h>

#समावेश "irq-gic-common.h"

#घोषणा ITS_FLAGS_CMDQ_NEEDS_FLUSHING		(1ULL << 0)
#घोषणा ITS_FLAGS_WORKAROUND_CAVIUM_22375	(1ULL << 1)
#घोषणा ITS_FLAGS_WORKAROUND_CAVIUM_23144	(1ULL << 2)

#घोषणा RDIST_FLAGS_PROPBASE_NEEDS_FLUSHING	(1 << 0)
#घोषणा RDIST_FLAGS_RD_TABLES_PREALLOCATED	(1 << 1)

अटल u32 lpi_id_bits;

/*
 * We allocate memory क्रम PROPBASE to cover 2 ^ lpi_id_bits LPIs to
 * deal with (one configuration byte per पूर्णांकerrupt). PENDBASE has to
 * be 64kB aligned (one bit per LPI, plus 8192 bits क्रम SPI/PPI/SGI).
 */
#घोषणा LPI_NRBITS		lpi_id_bits
#घोषणा LPI_PROPBASE_SZ		ALIGN(BIT(LPI_NRBITS), SZ_64K)
#घोषणा LPI_PENDBASE_SZ		ALIGN(BIT(LPI_NRBITS) / 8, SZ_64K)

#घोषणा LPI_PROP_DEFAULT_PRIO	GICD_INT_DEF_PRI

/*
 * Collection काष्ठाure - just an ID, and a redistributor address to
 * ping. We use one per CPU as a bag of पूर्णांकerrupts asचिन्हित to this
 * CPU.
 */
काष्ठा its_collection अणु
	u64			target_address;
	u16			col_id;
पूर्ण;

/*
 * The ITS_BASER काष्ठाure - contains memory inक्रमmation, cached
 * value of BASER रेजिस्टर configuration and ITS page size.
 */
काष्ठा its_baser अणु
	व्योम		*base;
	u64		val;
	u32		order;
	u32		psz;
पूर्ण;

काष्ठा its_device;

/*
 * The ITS काष्ठाure - contains most of the infraकाष्ठाure, with the
 * top-level MSI करोमुख्य, the command queue, the collections, and the
 * list of devices writing to it.
 *
 * dev_alloc_lock has to be taken क्रम device allocations, जबतक the
 * spinlock must be taken to parse data काष्ठाures such as the device
 * list.
 */
काष्ठा its_node अणु
	raw_spinlock_t		lock;
	काष्ठा mutex		dev_alloc_lock;
	काष्ठा list_head	entry;
	व्योम __iomem		*base;
	व्योम __iomem		*sgir_base;
	phys_addr_t		phys_base;
	काष्ठा its_cmd_block	*cmd_base;
	काष्ठा its_cmd_block	*cmd_ग_लिखो;
	काष्ठा its_baser	tables[GITS_BASER_NR_REGS];
	काष्ठा its_collection	*collections;
	काष्ठा fwnode_handle	*fwnode_handle;
	u64			(*get_msi_base)(काष्ठा its_device *its_dev);
	u64			typer;
	u64			cbaser_save;
	u32			ctlr_save;
	u32			mpidr;
	काष्ठा list_head	its_device_list;
	u64			flags;
	अचिन्हित दीर्घ		list_nr;
	पूर्णांक			numa_node;
	अचिन्हित पूर्णांक		msi_करोमुख्य_flags;
	u32			pre_its_base; /* क्रम Socionext Synquacer */
	पूर्णांक			vlpi_redist_offset;
पूर्ण;

#घोषणा is_v4(its)		(!!((its)->typer & GITS_TYPER_VLPIS))
#घोषणा is_v4_1(its)		(!!((its)->typer & GITS_TYPER_VMAPP))
#घोषणा device_ids(its)		(FIELD_GET(GITS_TYPER_DEVBITS, (its)->typer) + 1)

#घोषणा ITS_ITT_ALIGN		SZ_256

/* The maximum number of VPEID bits supported by VLPI commands */
#घोषणा ITS_MAX_VPEID_BITS						\
	(अणु								\
		पूर्णांक nvpeid = 16;					\
		अगर (gic_rdists->has_rvpeid &&				\
		    gic_rdists->gicd_typer2 & GICD_TYPER2_VIL)		\
			nvpeid = 1 + (gic_rdists->gicd_typer2 &		\
				      GICD_TYPER2_VID);			\
									\
		nvpeid;							\
	पूर्ण)
#घोषणा ITS_MAX_VPEID		(1 << (ITS_MAX_VPEID_BITS))

/* Convert page order to size in bytes */
#घोषणा PAGE_ORDER_TO_SIZE(o)	(PAGE_SIZE << (o))

काष्ठा event_lpi_map अणु
	अचिन्हित दीर्घ		*lpi_map;
	u16			*col_map;
	irq_hw_number_t		lpi_base;
	पूर्णांक			nr_lpis;
	raw_spinlock_t		vlpi_lock;
	काष्ठा its_vm		*vm;
	काष्ठा its_vlpi_map	*vlpi_maps;
	पूर्णांक			nr_vlpis;
पूर्ण;

/*
 * The ITS view of a device - beदीर्घs to an ITS, owns an पूर्णांकerrupt
 * translation table, and a list of पूर्णांकerrupts.  If it some of its
 * LPIs are injected पूर्णांकo a guest (GICv4), the event_map.vm field
 * indicates which one.
 */
काष्ठा its_device अणु
	काष्ठा list_head	entry;
	काष्ठा its_node		*its;
	काष्ठा event_lpi_map	event_map;
	व्योम			*itt;
	u32			nr_ites;
	u32			device_id;
	bool			shared;
पूर्ण;

अटल काष्ठा अणु
	raw_spinlock_t		lock;
	काष्ठा its_device	*dev;
	काष्ठा its_vpe		**vpes;
	पूर्णांक			next_victim;
पूर्ण vpe_proxy;

काष्ठा cpu_lpi_count अणु
	atomic_t	managed;
	atomic_t	unmanaged;
पूर्ण;

अटल DEFINE_PER_CPU(काष्ठा cpu_lpi_count, cpu_lpi_count);

अटल LIST_HEAD(its_nodes);
अटल DEFINE_RAW_SPINLOCK(its_lock);
अटल काष्ठा rdists *gic_rdists;
अटल काष्ठा irq_करोमुख्य *its_parent;

अटल अचिन्हित दीर्घ its_list_map;
अटल u16 vmovp_seq_num;
अटल DEFINE_RAW_SPINLOCK(vmovp_lock);

अटल DEFINE_IDA(its_vpeid_ida);

#घोषणा gic_data_rdist()		(raw_cpu_ptr(gic_rdists->rdist))
#घोषणा gic_data_rdist_cpu(cpu)		(per_cpu_ptr(gic_rdists->rdist, cpu))
#घोषणा gic_data_rdist_rd_base()	(gic_data_rdist()->rd_base)
#घोषणा gic_data_rdist_vlpi_base()	(gic_data_rdist_rd_base() + SZ_128K)

/*
 * Skip ITSs that have no vLPIs mapped, unless we're on GICv4.1, as we
 * always have vSGIs mapped.
 */
अटल bool require_its_list_vmovp(काष्ठा its_vm *vm, काष्ठा its_node *its)
अणु
	वापस (gic_rdists->has_rvpeid || vm->vlpi_count[its->list_nr]);
पूर्ण

अटल u16 get_its_list(काष्ठा its_vm *vm)
अणु
	काष्ठा its_node *its;
	अचिन्हित दीर्घ its_list = 0;

	list_क्रम_each_entry(its, &its_nodes, entry) अणु
		अगर (!is_v4(its))
			जारी;

		अगर (require_its_list_vmovp(vm, its))
			__set_bit(its->list_nr, &its_list);
	पूर्ण

	वापस (u16)its_list;
पूर्ण

अटल अंतरभूत u32 its_get_event_id(काष्ठा irq_data *d)
अणु
	काष्ठा its_device *its_dev = irq_data_get_irq_chip_data(d);
	वापस d->hwirq - its_dev->event_map.lpi_base;
पूर्ण

अटल काष्ठा its_collection *dev_event_to_col(काष्ठा its_device *its_dev,
					       u32 event)
अणु
	काष्ठा its_node *its = its_dev->its;

	वापस its->collections + its_dev->event_map.col_map[event];
पूर्ण

अटल काष्ठा its_vlpi_map *dev_event_to_vlpi_map(काष्ठा its_device *its_dev,
					       u32 event)
अणु
	अगर (WARN_ON_ONCE(event >= its_dev->event_map.nr_lpis))
		वापस शून्य;

	वापस &its_dev->event_map.vlpi_maps[event];
पूर्ण

अटल काष्ठा its_vlpi_map *get_vlpi_map(काष्ठा irq_data *d)
अणु
	अगर (irqd_is_क्रमwarded_to_vcpu(d)) अणु
		काष्ठा its_device *its_dev = irq_data_get_irq_chip_data(d);
		u32 event = its_get_event_id(d);

		वापस dev_event_to_vlpi_map(its_dev, event);
	पूर्ण

	वापस शून्य;
पूर्ण

अटल पूर्णांक vpe_to_cpuid_lock(काष्ठा its_vpe *vpe, अचिन्हित दीर्घ *flags)
अणु
	raw_spin_lock_irqsave(&vpe->vpe_lock, *flags);
	वापस vpe->col_idx;
पूर्ण

अटल व्योम vpe_to_cpuid_unlock(काष्ठा its_vpe *vpe, अचिन्हित दीर्घ flags)
अणु
	raw_spin_unlock_irqrestore(&vpe->vpe_lock, flags);
पूर्ण

अटल पूर्णांक irq_to_cpuid_lock(काष्ठा irq_data *d, अचिन्हित दीर्घ *flags)
अणु
	काष्ठा its_vlpi_map *map = get_vlpi_map(d);
	पूर्णांक cpu;

	अगर (map) अणु
		cpu = vpe_to_cpuid_lock(map->vpe, flags);
	पूर्ण अन्यथा अणु
		/* Physical LPIs are alपढ़ोy locked via the irq_desc lock */
		काष्ठा its_device *its_dev = irq_data_get_irq_chip_data(d);
		cpu = its_dev->event_map.col_map[its_get_event_id(d)];
		/* Keep GCC quiet... */
		*flags = 0;
	पूर्ण

	वापस cpu;
पूर्ण

अटल व्योम irq_to_cpuid_unlock(काष्ठा irq_data *d, अचिन्हित दीर्घ flags)
अणु
	काष्ठा its_vlpi_map *map = get_vlpi_map(d);

	अगर (map)
		vpe_to_cpuid_unlock(map->vpe, flags);
पूर्ण

अटल काष्ठा its_collection *valid_col(काष्ठा its_collection *col)
अणु
	अगर (WARN_ON_ONCE(col->target_address & GENMASK_ULL(15, 0)))
		वापस शून्य;

	वापस col;
पूर्ण

अटल काष्ठा its_vpe *valid_vpe(काष्ठा its_node *its, काष्ठा its_vpe *vpe)
अणु
	अगर (valid_col(its->collections + vpe->col_idx))
		वापस vpe;

	वापस शून्य;
पूर्ण

/*
 * ITS command descriptors - parameters to be encoded in a command
 * block.
 */
काष्ठा its_cmd_desc अणु
	जोड़ अणु
		काष्ठा अणु
			काष्ठा its_device *dev;
			u32 event_id;
		पूर्ण its_inv_cmd;

		काष्ठा अणु
			काष्ठा its_device *dev;
			u32 event_id;
		पूर्ण its_clear_cmd;

		काष्ठा अणु
			काष्ठा its_device *dev;
			u32 event_id;
		पूर्ण its_पूर्णांक_cmd;

		काष्ठा अणु
			काष्ठा its_device *dev;
			पूर्णांक valid;
		पूर्ण its_mapd_cmd;

		काष्ठा अणु
			काष्ठा its_collection *col;
			पूर्णांक valid;
		पूर्ण its_mapc_cmd;

		काष्ठा अणु
			काष्ठा its_device *dev;
			u32 phys_id;
			u32 event_id;
		पूर्ण its_mapti_cmd;

		काष्ठा अणु
			काष्ठा its_device *dev;
			काष्ठा its_collection *col;
			u32 event_id;
		पूर्ण its_movi_cmd;

		काष्ठा अणु
			काष्ठा its_device *dev;
			u32 event_id;
		पूर्ण its_discard_cmd;

		काष्ठा अणु
			काष्ठा its_collection *col;
		पूर्ण its_invall_cmd;

		काष्ठा अणु
			काष्ठा its_vpe *vpe;
		पूर्ण its_vinvall_cmd;

		काष्ठा अणु
			काष्ठा its_vpe *vpe;
			काष्ठा its_collection *col;
			bool valid;
		पूर्ण its_vmapp_cmd;

		काष्ठा अणु
			काष्ठा its_vpe *vpe;
			काष्ठा its_device *dev;
			u32 virt_id;
			u32 event_id;
			bool db_enabled;
		पूर्ण its_vmapti_cmd;

		काष्ठा अणु
			काष्ठा its_vpe *vpe;
			काष्ठा its_device *dev;
			u32 event_id;
			bool db_enabled;
		पूर्ण its_vmovi_cmd;

		काष्ठा अणु
			काष्ठा its_vpe *vpe;
			काष्ठा its_collection *col;
			u16 seq_num;
			u16 its_list;
		पूर्ण its_vmovp_cmd;

		काष्ठा अणु
			काष्ठा its_vpe *vpe;
		पूर्ण its_invdb_cmd;

		काष्ठा अणु
			काष्ठा its_vpe *vpe;
			u8 sgi;
			u8 priority;
			bool enable;
			bool group;
			bool clear;
		पूर्ण its_vsgi_cmd;
	पूर्ण;
पूर्ण;

/*
 * The ITS command block, which is what the ITS actually parses.
 */
काष्ठा its_cmd_block अणु
	जोड़ अणु
		u64	raw_cmd[4];
		__le64	raw_cmd_le[4];
	पूर्ण;
पूर्ण;

#घोषणा ITS_CMD_QUEUE_SZ		SZ_64K
#घोषणा ITS_CMD_QUEUE_NR_ENTRIES	(ITS_CMD_QUEUE_SZ / माप(काष्ठा its_cmd_block))

प्रकार काष्ठा its_collection *(*its_cmd_builder_t)(काष्ठा its_node *,
						    काष्ठा its_cmd_block *,
						    काष्ठा its_cmd_desc *);

प्रकार काष्ठा its_vpe *(*its_cmd_vbuilder_t)(काष्ठा its_node *,
					      काष्ठा its_cmd_block *,
					      काष्ठा its_cmd_desc *);

अटल व्योम its_mask_encode(u64 *raw_cmd, u64 val, पूर्णांक h, पूर्णांक l)
अणु
	u64 mask = GENMASK_ULL(h, l);
	*raw_cmd &= ~mask;
	*raw_cmd |= (val << l) & mask;
पूर्ण

अटल व्योम its_encode_cmd(काष्ठा its_cmd_block *cmd, u8 cmd_nr)
अणु
	its_mask_encode(&cmd->raw_cmd[0], cmd_nr, 7, 0);
पूर्ण

अटल व्योम its_encode_devid(काष्ठा its_cmd_block *cmd, u32 devid)
अणु
	its_mask_encode(&cmd->raw_cmd[0], devid, 63, 32);
पूर्ण

अटल व्योम its_encode_event_id(काष्ठा its_cmd_block *cmd, u32 id)
अणु
	its_mask_encode(&cmd->raw_cmd[1], id, 31, 0);
पूर्ण

अटल व्योम its_encode_phys_id(काष्ठा its_cmd_block *cmd, u32 phys_id)
अणु
	its_mask_encode(&cmd->raw_cmd[1], phys_id, 63, 32);
पूर्ण

अटल व्योम its_encode_size(काष्ठा its_cmd_block *cmd, u8 size)
अणु
	its_mask_encode(&cmd->raw_cmd[1], size, 4, 0);
पूर्ण

अटल व्योम its_encode_itt(काष्ठा its_cmd_block *cmd, u64 itt_addr)
अणु
	its_mask_encode(&cmd->raw_cmd[2], itt_addr >> 8, 51, 8);
पूर्ण

अटल व्योम its_encode_valid(काष्ठा its_cmd_block *cmd, पूर्णांक valid)
अणु
	its_mask_encode(&cmd->raw_cmd[2], !!valid, 63, 63);
पूर्ण

अटल व्योम its_encode_target(काष्ठा its_cmd_block *cmd, u64 target_addr)
अणु
	its_mask_encode(&cmd->raw_cmd[2], target_addr >> 16, 51, 16);
पूर्ण

अटल व्योम its_encode_collection(काष्ठा its_cmd_block *cmd, u16 col)
अणु
	its_mask_encode(&cmd->raw_cmd[2], col, 15, 0);
पूर्ण

अटल व्योम its_encode_vpeid(काष्ठा its_cmd_block *cmd, u16 vpeid)
अणु
	its_mask_encode(&cmd->raw_cmd[1], vpeid, 47, 32);
पूर्ण

अटल व्योम its_encode_virt_id(काष्ठा its_cmd_block *cmd, u32 virt_id)
अणु
	its_mask_encode(&cmd->raw_cmd[2], virt_id, 31, 0);
पूर्ण

अटल व्योम its_encode_db_phys_id(काष्ठा its_cmd_block *cmd, u32 db_phys_id)
अणु
	its_mask_encode(&cmd->raw_cmd[2], db_phys_id, 63, 32);
पूर्ण

अटल व्योम its_encode_db_valid(काष्ठा its_cmd_block *cmd, bool db_valid)
अणु
	its_mask_encode(&cmd->raw_cmd[2], db_valid, 0, 0);
पूर्ण

अटल व्योम its_encode_seq_num(काष्ठा its_cmd_block *cmd, u16 seq_num)
अणु
	its_mask_encode(&cmd->raw_cmd[0], seq_num, 47, 32);
पूर्ण

अटल व्योम its_encode_its_list(काष्ठा its_cmd_block *cmd, u16 its_list)
अणु
	its_mask_encode(&cmd->raw_cmd[1], its_list, 15, 0);
पूर्ण

अटल व्योम its_encode_vpt_addr(काष्ठा its_cmd_block *cmd, u64 vpt_pa)
अणु
	its_mask_encode(&cmd->raw_cmd[3], vpt_pa >> 16, 51, 16);
पूर्ण

अटल व्योम its_encode_vpt_size(काष्ठा its_cmd_block *cmd, u8 vpt_size)
अणु
	its_mask_encode(&cmd->raw_cmd[3], vpt_size, 4, 0);
पूर्ण

अटल व्योम its_encode_vconf_addr(काष्ठा its_cmd_block *cmd, u64 vconf_pa)
अणु
	its_mask_encode(&cmd->raw_cmd[0], vconf_pa >> 16, 51, 16);
पूर्ण

अटल व्योम its_encode_alloc(काष्ठा its_cmd_block *cmd, bool alloc)
अणु
	its_mask_encode(&cmd->raw_cmd[0], alloc, 8, 8);
पूर्ण

अटल व्योम its_encode_ptz(काष्ठा its_cmd_block *cmd, bool ptz)
अणु
	its_mask_encode(&cmd->raw_cmd[0], ptz, 9, 9);
पूर्ण

अटल व्योम its_encode_vmapp_शेष_db(काष्ठा its_cmd_block *cmd,
					u32 vpe_db_lpi)
अणु
	its_mask_encode(&cmd->raw_cmd[1], vpe_db_lpi, 31, 0);
पूर्ण

अटल व्योम its_encode_vmovp_शेष_db(काष्ठा its_cmd_block *cmd,
					u32 vpe_db_lpi)
अणु
	its_mask_encode(&cmd->raw_cmd[3], vpe_db_lpi, 31, 0);
पूर्ण

अटल व्योम its_encode_db(काष्ठा its_cmd_block *cmd, bool db)
अणु
	its_mask_encode(&cmd->raw_cmd[2], db, 63, 63);
पूर्ण

अटल व्योम its_encode_sgi_पूर्णांकid(काष्ठा its_cmd_block *cmd, u8 sgi)
अणु
	its_mask_encode(&cmd->raw_cmd[0], sgi, 35, 32);
पूर्ण

अटल व्योम its_encode_sgi_priority(काष्ठा its_cmd_block *cmd, u8 prio)
अणु
	its_mask_encode(&cmd->raw_cmd[0], prio >> 4, 23, 20);
पूर्ण

अटल व्योम its_encode_sgi_group(काष्ठा its_cmd_block *cmd, bool grp)
अणु
	its_mask_encode(&cmd->raw_cmd[0], grp, 10, 10);
पूर्ण

अटल व्योम its_encode_sgi_clear(काष्ठा its_cmd_block *cmd, bool clr)
अणु
	its_mask_encode(&cmd->raw_cmd[0], clr, 9, 9);
पूर्ण

अटल व्योम its_encode_sgi_enable(काष्ठा its_cmd_block *cmd, bool en)
अणु
	its_mask_encode(&cmd->raw_cmd[0], en, 8, 8);
पूर्ण

अटल अंतरभूत व्योम its_fixup_cmd(काष्ठा its_cmd_block *cmd)
अणु
	/* Let's fixup BE commands */
	cmd->raw_cmd_le[0] = cpu_to_le64(cmd->raw_cmd[0]);
	cmd->raw_cmd_le[1] = cpu_to_le64(cmd->raw_cmd[1]);
	cmd->raw_cmd_le[2] = cpu_to_le64(cmd->raw_cmd[2]);
	cmd->raw_cmd_le[3] = cpu_to_le64(cmd->raw_cmd[3]);
पूर्ण

अटल काष्ठा its_collection *its_build_mapd_cmd(काष्ठा its_node *its,
						 काष्ठा its_cmd_block *cmd,
						 काष्ठा its_cmd_desc *desc)
अणु
	अचिन्हित दीर्घ itt_addr;
	u8 size = ilog2(desc->its_mapd_cmd.dev->nr_ites);

	itt_addr = virt_to_phys(desc->its_mapd_cmd.dev->itt);
	itt_addr = ALIGN(itt_addr, ITS_ITT_ALIGN);

	its_encode_cmd(cmd, GITS_CMD_MAPD);
	its_encode_devid(cmd, desc->its_mapd_cmd.dev->device_id);
	its_encode_size(cmd, size - 1);
	its_encode_itt(cmd, itt_addr);
	its_encode_valid(cmd, desc->its_mapd_cmd.valid);

	its_fixup_cmd(cmd);

	वापस शून्य;
पूर्ण

अटल काष्ठा its_collection *its_build_mapc_cmd(काष्ठा its_node *its,
						 काष्ठा its_cmd_block *cmd,
						 काष्ठा its_cmd_desc *desc)
अणु
	its_encode_cmd(cmd, GITS_CMD_MAPC);
	its_encode_collection(cmd, desc->its_mapc_cmd.col->col_id);
	its_encode_target(cmd, desc->its_mapc_cmd.col->target_address);
	its_encode_valid(cmd, desc->its_mapc_cmd.valid);

	its_fixup_cmd(cmd);

	वापस desc->its_mapc_cmd.col;
पूर्ण

अटल काष्ठा its_collection *its_build_mapti_cmd(काष्ठा its_node *its,
						  काष्ठा its_cmd_block *cmd,
						  काष्ठा its_cmd_desc *desc)
अणु
	काष्ठा its_collection *col;

	col = dev_event_to_col(desc->its_mapti_cmd.dev,
			       desc->its_mapti_cmd.event_id);

	its_encode_cmd(cmd, GITS_CMD_MAPTI);
	its_encode_devid(cmd, desc->its_mapti_cmd.dev->device_id);
	its_encode_event_id(cmd, desc->its_mapti_cmd.event_id);
	its_encode_phys_id(cmd, desc->its_mapti_cmd.phys_id);
	its_encode_collection(cmd, col->col_id);

	its_fixup_cmd(cmd);

	वापस valid_col(col);
पूर्ण

अटल काष्ठा its_collection *its_build_movi_cmd(काष्ठा its_node *its,
						 काष्ठा its_cmd_block *cmd,
						 काष्ठा its_cmd_desc *desc)
अणु
	काष्ठा its_collection *col;

	col = dev_event_to_col(desc->its_movi_cmd.dev,
			       desc->its_movi_cmd.event_id);

	its_encode_cmd(cmd, GITS_CMD_MOVI);
	its_encode_devid(cmd, desc->its_movi_cmd.dev->device_id);
	its_encode_event_id(cmd, desc->its_movi_cmd.event_id);
	its_encode_collection(cmd, desc->its_movi_cmd.col->col_id);

	its_fixup_cmd(cmd);

	वापस valid_col(col);
पूर्ण

अटल काष्ठा its_collection *its_build_discard_cmd(काष्ठा its_node *its,
						    काष्ठा its_cmd_block *cmd,
						    काष्ठा its_cmd_desc *desc)
अणु
	काष्ठा its_collection *col;

	col = dev_event_to_col(desc->its_discard_cmd.dev,
			       desc->its_discard_cmd.event_id);

	its_encode_cmd(cmd, GITS_CMD_DISCARD);
	its_encode_devid(cmd, desc->its_discard_cmd.dev->device_id);
	its_encode_event_id(cmd, desc->its_discard_cmd.event_id);

	its_fixup_cmd(cmd);

	वापस valid_col(col);
पूर्ण

अटल काष्ठा its_collection *its_build_inv_cmd(काष्ठा its_node *its,
						काष्ठा its_cmd_block *cmd,
						काष्ठा its_cmd_desc *desc)
अणु
	काष्ठा its_collection *col;

	col = dev_event_to_col(desc->its_inv_cmd.dev,
			       desc->its_inv_cmd.event_id);

	its_encode_cmd(cmd, GITS_CMD_INV);
	its_encode_devid(cmd, desc->its_inv_cmd.dev->device_id);
	its_encode_event_id(cmd, desc->its_inv_cmd.event_id);

	its_fixup_cmd(cmd);

	वापस valid_col(col);
पूर्ण

अटल काष्ठा its_collection *its_build_पूर्णांक_cmd(काष्ठा its_node *its,
						काष्ठा its_cmd_block *cmd,
						काष्ठा its_cmd_desc *desc)
अणु
	काष्ठा its_collection *col;

	col = dev_event_to_col(desc->its_पूर्णांक_cmd.dev,
			       desc->its_पूर्णांक_cmd.event_id);

	its_encode_cmd(cmd, GITS_CMD_INT);
	its_encode_devid(cmd, desc->its_पूर्णांक_cmd.dev->device_id);
	its_encode_event_id(cmd, desc->its_पूर्णांक_cmd.event_id);

	its_fixup_cmd(cmd);

	वापस valid_col(col);
पूर्ण

अटल काष्ठा its_collection *its_build_clear_cmd(काष्ठा its_node *its,
						  काष्ठा its_cmd_block *cmd,
						  काष्ठा its_cmd_desc *desc)
अणु
	काष्ठा its_collection *col;

	col = dev_event_to_col(desc->its_clear_cmd.dev,
			       desc->its_clear_cmd.event_id);

	its_encode_cmd(cmd, GITS_CMD_CLEAR);
	its_encode_devid(cmd, desc->its_clear_cmd.dev->device_id);
	its_encode_event_id(cmd, desc->its_clear_cmd.event_id);

	its_fixup_cmd(cmd);

	वापस valid_col(col);
पूर्ण

अटल काष्ठा its_collection *its_build_invall_cmd(काष्ठा its_node *its,
						   काष्ठा its_cmd_block *cmd,
						   काष्ठा its_cmd_desc *desc)
अणु
	its_encode_cmd(cmd, GITS_CMD_INVALL);
	its_encode_collection(cmd, desc->its_invall_cmd.col->col_id);

	its_fixup_cmd(cmd);

	वापस शून्य;
पूर्ण

अटल काष्ठा its_vpe *its_build_vinvall_cmd(काष्ठा its_node *its,
					     काष्ठा its_cmd_block *cmd,
					     काष्ठा its_cmd_desc *desc)
अणु
	its_encode_cmd(cmd, GITS_CMD_VINVALL);
	its_encode_vpeid(cmd, desc->its_vinvall_cmd.vpe->vpe_id);

	its_fixup_cmd(cmd);

	वापस valid_vpe(its, desc->its_vinvall_cmd.vpe);
पूर्ण

अटल काष्ठा its_vpe *its_build_vmapp_cmd(काष्ठा its_node *its,
					   काष्ठा its_cmd_block *cmd,
					   काष्ठा its_cmd_desc *desc)
अणु
	अचिन्हित दीर्घ vpt_addr, vconf_addr;
	u64 target;
	bool alloc;

	its_encode_cmd(cmd, GITS_CMD_VMAPP);
	its_encode_vpeid(cmd, desc->its_vmapp_cmd.vpe->vpe_id);
	its_encode_valid(cmd, desc->its_vmapp_cmd.valid);

	अगर (!desc->its_vmapp_cmd.valid) अणु
		अगर (is_v4_1(its)) अणु
			alloc = !atomic_dec_वापस(&desc->its_vmapp_cmd.vpe->vmapp_count);
			its_encode_alloc(cmd, alloc);
		पूर्ण

		जाओ out;
	पूर्ण

	vpt_addr = virt_to_phys(page_address(desc->its_vmapp_cmd.vpe->vpt_page));
	target = desc->its_vmapp_cmd.col->target_address + its->vlpi_redist_offset;

	its_encode_target(cmd, target);
	its_encode_vpt_addr(cmd, vpt_addr);
	its_encode_vpt_size(cmd, LPI_NRBITS - 1);

	अगर (!is_v4_1(its))
		जाओ out;

	vconf_addr = virt_to_phys(page_address(desc->its_vmapp_cmd.vpe->its_vm->vprop_page));

	alloc = !atomic_fetch_inc(&desc->its_vmapp_cmd.vpe->vmapp_count);

	its_encode_alloc(cmd, alloc);

	/*
	 * GICv4.1 provides a way to get the VLPI state, which needs the vPE
	 * to be unmapped first, and in this हाल, we may remap the vPE
	 * back जबतक the VPT is not empty. So we can't assume that the
	 * VPT is empty on map. This is why we never advertise PTZ.
	 */
	its_encode_ptz(cmd, false);
	its_encode_vconf_addr(cmd, vconf_addr);
	its_encode_vmapp_शेष_db(cmd, desc->its_vmapp_cmd.vpe->vpe_db_lpi);

out:
	its_fixup_cmd(cmd);

	वापस valid_vpe(its, desc->its_vmapp_cmd.vpe);
पूर्ण

अटल काष्ठा its_vpe *its_build_vmapti_cmd(काष्ठा its_node *its,
					    काष्ठा its_cmd_block *cmd,
					    काष्ठा its_cmd_desc *desc)
अणु
	u32 db;

	अगर (!is_v4_1(its) && desc->its_vmapti_cmd.db_enabled)
		db = desc->its_vmapti_cmd.vpe->vpe_db_lpi;
	अन्यथा
		db = 1023;

	its_encode_cmd(cmd, GITS_CMD_VMAPTI);
	its_encode_devid(cmd, desc->its_vmapti_cmd.dev->device_id);
	its_encode_vpeid(cmd, desc->its_vmapti_cmd.vpe->vpe_id);
	its_encode_event_id(cmd, desc->its_vmapti_cmd.event_id);
	its_encode_db_phys_id(cmd, db);
	its_encode_virt_id(cmd, desc->its_vmapti_cmd.virt_id);

	its_fixup_cmd(cmd);

	वापस valid_vpe(its, desc->its_vmapti_cmd.vpe);
पूर्ण

अटल काष्ठा its_vpe *its_build_vmovi_cmd(काष्ठा its_node *its,
					   काष्ठा its_cmd_block *cmd,
					   काष्ठा its_cmd_desc *desc)
अणु
	u32 db;

	अगर (!is_v4_1(its) && desc->its_vmovi_cmd.db_enabled)
		db = desc->its_vmovi_cmd.vpe->vpe_db_lpi;
	अन्यथा
		db = 1023;

	its_encode_cmd(cmd, GITS_CMD_VMOVI);
	its_encode_devid(cmd, desc->its_vmovi_cmd.dev->device_id);
	its_encode_vpeid(cmd, desc->its_vmovi_cmd.vpe->vpe_id);
	its_encode_event_id(cmd, desc->its_vmovi_cmd.event_id);
	its_encode_db_phys_id(cmd, db);
	its_encode_db_valid(cmd, true);

	its_fixup_cmd(cmd);

	वापस valid_vpe(its, desc->its_vmovi_cmd.vpe);
पूर्ण

अटल काष्ठा its_vpe *its_build_vmovp_cmd(काष्ठा its_node *its,
					   काष्ठा its_cmd_block *cmd,
					   काष्ठा its_cmd_desc *desc)
अणु
	u64 target;

	target = desc->its_vmovp_cmd.col->target_address + its->vlpi_redist_offset;
	its_encode_cmd(cmd, GITS_CMD_VMOVP);
	its_encode_seq_num(cmd, desc->its_vmovp_cmd.seq_num);
	its_encode_its_list(cmd, desc->its_vmovp_cmd.its_list);
	its_encode_vpeid(cmd, desc->its_vmovp_cmd.vpe->vpe_id);
	its_encode_target(cmd, target);

	अगर (is_v4_1(its)) अणु
		its_encode_db(cmd, true);
		its_encode_vmovp_शेष_db(cmd, desc->its_vmovp_cmd.vpe->vpe_db_lpi);
	पूर्ण

	its_fixup_cmd(cmd);

	वापस valid_vpe(its, desc->its_vmovp_cmd.vpe);
पूर्ण

अटल काष्ठा its_vpe *its_build_vinv_cmd(काष्ठा its_node *its,
					  काष्ठा its_cmd_block *cmd,
					  काष्ठा its_cmd_desc *desc)
अणु
	काष्ठा its_vlpi_map *map;

	map = dev_event_to_vlpi_map(desc->its_inv_cmd.dev,
				    desc->its_inv_cmd.event_id);

	its_encode_cmd(cmd, GITS_CMD_INV);
	its_encode_devid(cmd, desc->its_inv_cmd.dev->device_id);
	its_encode_event_id(cmd, desc->its_inv_cmd.event_id);

	its_fixup_cmd(cmd);

	वापस valid_vpe(its, map->vpe);
पूर्ण

अटल काष्ठा its_vpe *its_build_vपूर्णांक_cmd(काष्ठा its_node *its,
					  काष्ठा its_cmd_block *cmd,
					  काष्ठा its_cmd_desc *desc)
अणु
	काष्ठा its_vlpi_map *map;

	map = dev_event_to_vlpi_map(desc->its_पूर्णांक_cmd.dev,
				    desc->its_पूर्णांक_cmd.event_id);

	its_encode_cmd(cmd, GITS_CMD_INT);
	its_encode_devid(cmd, desc->its_पूर्णांक_cmd.dev->device_id);
	its_encode_event_id(cmd, desc->its_पूर्णांक_cmd.event_id);

	its_fixup_cmd(cmd);

	वापस valid_vpe(its, map->vpe);
पूर्ण

अटल काष्ठा its_vpe *its_build_vclear_cmd(काष्ठा its_node *its,
					    काष्ठा its_cmd_block *cmd,
					    काष्ठा its_cmd_desc *desc)
अणु
	काष्ठा its_vlpi_map *map;

	map = dev_event_to_vlpi_map(desc->its_clear_cmd.dev,
				    desc->its_clear_cmd.event_id);

	its_encode_cmd(cmd, GITS_CMD_CLEAR);
	its_encode_devid(cmd, desc->its_clear_cmd.dev->device_id);
	its_encode_event_id(cmd, desc->its_clear_cmd.event_id);

	its_fixup_cmd(cmd);

	वापस valid_vpe(its, map->vpe);
पूर्ण

अटल काष्ठा its_vpe *its_build_invdb_cmd(काष्ठा its_node *its,
					   काष्ठा its_cmd_block *cmd,
					   काष्ठा its_cmd_desc *desc)
अणु
	अगर (WARN_ON(!is_v4_1(its)))
		वापस शून्य;

	its_encode_cmd(cmd, GITS_CMD_INVDB);
	its_encode_vpeid(cmd, desc->its_invdb_cmd.vpe->vpe_id);

	its_fixup_cmd(cmd);

	वापस valid_vpe(its, desc->its_invdb_cmd.vpe);
पूर्ण

अटल काष्ठा its_vpe *its_build_vsgi_cmd(काष्ठा its_node *its,
					  काष्ठा its_cmd_block *cmd,
					  काष्ठा its_cmd_desc *desc)
अणु
	अगर (WARN_ON(!is_v4_1(its)))
		वापस शून्य;

	its_encode_cmd(cmd, GITS_CMD_VSGI);
	its_encode_vpeid(cmd, desc->its_vsgi_cmd.vpe->vpe_id);
	its_encode_sgi_पूर्णांकid(cmd, desc->its_vsgi_cmd.sgi);
	its_encode_sgi_priority(cmd, desc->its_vsgi_cmd.priority);
	its_encode_sgi_group(cmd, desc->its_vsgi_cmd.group);
	its_encode_sgi_clear(cmd, desc->its_vsgi_cmd.clear);
	its_encode_sgi_enable(cmd, desc->its_vsgi_cmd.enable);

	its_fixup_cmd(cmd);

	वापस valid_vpe(its, desc->its_vsgi_cmd.vpe);
पूर्ण

अटल u64 its_cmd_ptr_to_offset(काष्ठा its_node *its,
				 काष्ठा its_cmd_block *ptr)
अणु
	वापस (ptr - its->cmd_base) * माप(*ptr);
पूर्ण

अटल पूर्णांक its_queue_full(काष्ठा its_node *its)
अणु
	पूर्णांक widx;
	पूर्णांक ridx;

	widx = its->cmd_ग_लिखो - its->cmd_base;
	ridx = पढ़ोl_relaxed(its->base + GITS_CREADR) / माप(काष्ठा its_cmd_block);

	/* This is incredibly unlikely to happen, unless the ITS locks up. */
	अगर (((widx + 1) % ITS_CMD_QUEUE_NR_ENTRIES) == ridx)
		वापस 1;

	वापस 0;
पूर्ण

अटल काष्ठा its_cmd_block *its_allocate_entry(काष्ठा its_node *its)
अणु
	काष्ठा its_cmd_block *cmd;
	u32 count = 1000000;	/* 1s! */

	जबतक (its_queue_full(its)) अणु
		count--;
		अगर (!count) अणु
			pr_err_ratelimited("ITS queue not draining\n");
			वापस शून्य;
		पूर्ण
		cpu_relax();
		udelay(1);
	पूर्ण

	cmd = its->cmd_ग_लिखो++;

	/* Handle queue wrapping */
	अगर (its->cmd_ग_लिखो == (its->cmd_base + ITS_CMD_QUEUE_NR_ENTRIES))
		its->cmd_ग_लिखो = its->cmd_base;

	/* Clear command  */
	cmd->raw_cmd[0] = 0;
	cmd->raw_cmd[1] = 0;
	cmd->raw_cmd[2] = 0;
	cmd->raw_cmd[3] = 0;

	वापस cmd;
पूर्ण

अटल काष्ठा its_cmd_block *its_post_commands(काष्ठा its_node *its)
अणु
	u64 wr = its_cmd_ptr_to_offset(its, its->cmd_ग_लिखो);

	ग_लिखोl_relaxed(wr, its->base + GITS_CWRITER);

	वापस its->cmd_ग_लिखो;
पूर्ण

अटल व्योम its_flush_cmd(काष्ठा its_node *its, काष्ठा its_cmd_block *cmd)
अणु
	/*
	 * Make sure the commands written to memory are observable by
	 * the ITS.
	 */
	अगर (its->flags & ITS_FLAGS_CMDQ_NEEDS_FLUSHING)
		gic_flush_dcache_to_poc(cmd, माप(*cmd));
	अन्यथा
		dsb(ishst);
पूर्ण

अटल पूर्णांक its_रुको_क्रम_range_completion(काष्ठा its_node *its,
					 u64	prev_idx,
					 काष्ठा its_cmd_block *to)
अणु
	u64 rd_idx, to_idx, linear_idx;
	u32 count = 1000000;	/* 1s! */

	/* Linearize to_idx अगर the command set has wrapped around */
	to_idx = its_cmd_ptr_to_offset(its, to);
	अगर (to_idx < prev_idx)
		to_idx += ITS_CMD_QUEUE_SZ;

	linear_idx = prev_idx;

	जबतक (1) अणु
		s64 delta;

		rd_idx = पढ़ोl_relaxed(its->base + GITS_CREADR);

		/*
		 * Compute the पढ़ो poपूर्णांकer progress, taking the
		 * potential wrap-around पूर्णांकo account.
		 */
		delta = rd_idx - prev_idx;
		अगर (rd_idx < prev_idx)
			delta += ITS_CMD_QUEUE_SZ;

		linear_idx += delta;
		अगर (linear_idx >= to_idx)
			अवरोध;

		count--;
		अगर (!count) अणु
			pr_err_ratelimited("ITS queue timeout (%llu %llu)\n",
					   to_idx, linear_idx);
			वापस -1;
		पूर्ण
		prev_idx = rd_idx;
		cpu_relax();
		udelay(1);
	पूर्ण

	वापस 0;
पूर्ण

/* Warning, macro hell follows */
#घोषणा BUILD_SINGLE_CMD_FUNC(name, buildtype, synctype, buildfn)	\
व्योम name(काष्ठा its_node *its,						\
	  buildtype builder,						\
	  काष्ठा its_cmd_desc *desc)					\
अणु									\
	काष्ठा its_cmd_block *cmd, *sync_cmd, *next_cmd;		\
	synctype *sync_obj;						\
	अचिन्हित दीर्घ flags;						\
	u64 rd_idx;							\
									\
	raw_spin_lock_irqsave(&its->lock, flags);			\
									\
	cmd = its_allocate_entry(its);					\
	अगर (!cmd) अणु		/* We're soooooo screewed... */		\
		raw_spin_unlock_irqrestore(&its->lock, flags);		\
		वापस;							\
	पूर्ण								\
	sync_obj = builder(its, cmd, desc);				\
	its_flush_cmd(its, cmd);					\
									\
	अगर (sync_obj) अणु							\
		sync_cmd = its_allocate_entry(its);			\
		अगर (!sync_cmd)						\
			जाओ post;					\
									\
		buildfn(its, sync_cmd, sync_obj);			\
		its_flush_cmd(its, sync_cmd);				\
	पूर्ण								\
									\
post:									\
	rd_idx = पढ़ोl_relaxed(its->base + GITS_CREADR);		\
	next_cmd = its_post_commands(its);				\
	raw_spin_unlock_irqrestore(&its->lock, flags);			\
									\
	अगर (its_रुको_क्रम_range_completion(its, rd_idx, next_cmd))	\
		pr_err_ratelimited("ITS cmd %ps failed\n", builder);	\
पूर्ण

अटल व्योम its_build_sync_cmd(काष्ठा its_node *its,
			       काष्ठा its_cmd_block *sync_cmd,
			       काष्ठा its_collection *sync_col)
अणु
	its_encode_cmd(sync_cmd, GITS_CMD_SYNC);
	its_encode_target(sync_cmd, sync_col->target_address);

	its_fixup_cmd(sync_cmd);
पूर्ण

अटल BUILD_SINGLE_CMD_FUNC(its_send_single_command, its_cmd_builder_t,
			     काष्ठा its_collection, its_build_sync_cmd)

अटल व्योम its_build_vsync_cmd(काष्ठा its_node *its,
				काष्ठा its_cmd_block *sync_cmd,
				काष्ठा its_vpe *sync_vpe)
अणु
	its_encode_cmd(sync_cmd, GITS_CMD_VSYNC);
	its_encode_vpeid(sync_cmd, sync_vpe->vpe_id);

	its_fixup_cmd(sync_cmd);
पूर्ण

अटल BUILD_SINGLE_CMD_FUNC(its_send_single_vcommand, its_cmd_vbuilder_t,
			     काष्ठा its_vpe, its_build_vsync_cmd)

अटल व्योम its_send_पूर्णांक(काष्ठा its_device *dev, u32 event_id)
अणु
	काष्ठा its_cmd_desc desc;

	desc.its_पूर्णांक_cmd.dev = dev;
	desc.its_पूर्णांक_cmd.event_id = event_id;

	its_send_single_command(dev->its, its_build_पूर्णांक_cmd, &desc);
पूर्ण

अटल व्योम its_send_clear(काष्ठा its_device *dev, u32 event_id)
अणु
	काष्ठा its_cmd_desc desc;

	desc.its_clear_cmd.dev = dev;
	desc.its_clear_cmd.event_id = event_id;

	its_send_single_command(dev->its, its_build_clear_cmd, &desc);
पूर्ण

अटल व्योम its_send_inv(काष्ठा its_device *dev, u32 event_id)
अणु
	काष्ठा its_cmd_desc desc;

	desc.its_inv_cmd.dev = dev;
	desc.its_inv_cmd.event_id = event_id;

	its_send_single_command(dev->its, its_build_inv_cmd, &desc);
पूर्ण

अटल व्योम its_send_mapd(काष्ठा its_device *dev, पूर्णांक valid)
अणु
	काष्ठा its_cmd_desc desc;

	desc.its_mapd_cmd.dev = dev;
	desc.its_mapd_cmd.valid = !!valid;

	its_send_single_command(dev->its, its_build_mapd_cmd, &desc);
पूर्ण

अटल व्योम its_send_mapc(काष्ठा its_node *its, काष्ठा its_collection *col,
			  पूर्णांक valid)
अणु
	काष्ठा its_cmd_desc desc;

	desc.its_mapc_cmd.col = col;
	desc.its_mapc_cmd.valid = !!valid;

	its_send_single_command(its, its_build_mapc_cmd, &desc);
पूर्ण

अटल व्योम its_send_mapti(काष्ठा its_device *dev, u32 irq_id, u32 id)
अणु
	काष्ठा its_cmd_desc desc;

	desc.its_mapti_cmd.dev = dev;
	desc.its_mapti_cmd.phys_id = irq_id;
	desc.its_mapti_cmd.event_id = id;

	its_send_single_command(dev->its, its_build_mapti_cmd, &desc);
पूर्ण

अटल व्योम its_send_movi(काष्ठा its_device *dev,
			  काष्ठा its_collection *col, u32 id)
अणु
	काष्ठा its_cmd_desc desc;

	desc.its_movi_cmd.dev = dev;
	desc.its_movi_cmd.col = col;
	desc.its_movi_cmd.event_id = id;

	its_send_single_command(dev->its, its_build_movi_cmd, &desc);
पूर्ण

अटल व्योम its_send_discard(काष्ठा its_device *dev, u32 id)
अणु
	काष्ठा its_cmd_desc desc;

	desc.its_discard_cmd.dev = dev;
	desc.its_discard_cmd.event_id = id;

	its_send_single_command(dev->its, its_build_discard_cmd, &desc);
पूर्ण

अटल व्योम its_send_invall(काष्ठा its_node *its, काष्ठा its_collection *col)
अणु
	काष्ठा its_cmd_desc desc;

	desc.its_invall_cmd.col = col;

	its_send_single_command(its, its_build_invall_cmd, &desc);
पूर्ण

अटल व्योम its_send_vmapti(काष्ठा its_device *dev, u32 id)
अणु
	काष्ठा its_vlpi_map *map = dev_event_to_vlpi_map(dev, id);
	काष्ठा its_cmd_desc desc;

	desc.its_vmapti_cmd.vpe = map->vpe;
	desc.its_vmapti_cmd.dev = dev;
	desc.its_vmapti_cmd.virt_id = map->vपूर्णांकid;
	desc.its_vmapti_cmd.event_id = id;
	desc.its_vmapti_cmd.db_enabled = map->db_enabled;

	its_send_single_vcommand(dev->its, its_build_vmapti_cmd, &desc);
पूर्ण

अटल व्योम its_send_vmovi(काष्ठा its_device *dev, u32 id)
अणु
	काष्ठा its_vlpi_map *map = dev_event_to_vlpi_map(dev, id);
	काष्ठा its_cmd_desc desc;

	desc.its_vmovi_cmd.vpe = map->vpe;
	desc.its_vmovi_cmd.dev = dev;
	desc.its_vmovi_cmd.event_id = id;
	desc.its_vmovi_cmd.db_enabled = map->db_enabled;

	its_send_single_vcommand(dev->its, its_build_vmovi_cmd, &desc);
पूर्ण

अटल व्योम its_send_vmapp(काष्ठा its_node *its,
			   काष्ठा its_vpe *vpe, bool valid)
अणु
	काष्ठा its_cmd_desc desc;

	desc.its_vmapp_cmd.vpe = vpe;
	desc.its_vmapp_cmd.valid = valid;
	desc.its_vmapp_cmd.col = &its->collections[vpe->col_idx];

	its_send_single_vcommand(its, its_build_vmapp_cmd, &desc);
पूर्ण

अटल व्योम its_send_vmovp(काष्ठा its_vpe *vpe)
अणु
	काष्ठा its_cmd_desc desc = अणुपूर्ण;
	काष्ठा its_node *its;
	अचिन्हित दीर्घ flags;
	पूर्णांक col_id = vpe->col_idx;

	desc.its_vmovp_cmd.vpe = vpe;

	अगर (!its_list_map) अणु
		its = list_first_entry(&its_nodes, काष्ठा its_node, entry);
		desc.its_vmovp_cmd.col = &its->collections[col_id];
		its_send_single_vcommand(its, its_build_vmovp_cmd, &desc);
		वापस;
	पूर्ण

	/*
	 * Yet another marvel of the architecture. If using the
	 * its_list "feature", we need to make sure that all ITSs
	 * receive all VMOVP commands in the same order. The only way
	 * to guarantee this is to make vmovp a serialization poपूर्णांक.
	 *
	 * Wall <-- Head.
	 */
	raw_spin_lock_irqsave(&vmovp_lock, flags);

	desc.its_vmovp_cmd.seq_num = vmovp_seq_num++;
	desc.its_vmovp_cmd.its_list = get_its_list(vpe->its_vm);

	/* Emit VMOVPs */
	list_क्रम_each_entry(its, &its_nodes, entry) अणु
		अगर (!is_v4(its))
			जारी;

		अगर (!require_its_list_vmovp(vpe->its_vm, its))
			जारी;

		desc.its_vmovp_cmd.col = &its->collections[col_id];
		its_send_single_vcommand(its, its_build_vmovp_cmd, &desc);
	पूर्ण

	raw_spin_unlock_irqrestore(&vmovp_lock, flags);
पूर्ण

अटल व्योम its_send_vinvall(काष्ठा its_node *its, काष्ठा its_vpe *vpe)
अणु
	काष्ठा its_cmd_desc desc;

	desc.its_vinvall_cmd.vpe = vpe;
	its_send_single_vcommand(its, its_build_vinvall_cmd, &desc);
पूर्ण

अटल व्योम its_send_vinv(काष्ठा its_device *dev, u32 event_id)
अणु
	काष्ठा its_cmd_desc desc;

	/*
	 * There is no real VINV command. This is just a normal INV,
	 * with a VSYNC instead of a SYNC.
	 */
	desc.its_inv_cmd.dev = dev;
	desc.its_inv_cmd.event_id = event_id;

	its_send_single_vcommand(dev->its, its_build_vinv_cmd, &desc);
पूर्ण

अटल व्योम its_send_vपूर्णांक(काष्ठा its_device *dev, u32 event_id)
अणु
	काष्ठा its_cmd_desc desc;

	/*
	 * There is no real VINT command. This is just a normal INT,
	 * with a VSYNC instead of a SYNC.
	 */
	desc.its_पूर्णांक_cmd.dev = dev;
	desc.its_पूर्णांक_cmd.event_id = event_id;

	its_send_single_vcommand(dev->its, its_build_vपूर्णांक_cmd, &desc);
पूर्ण

अटल व्योम its_send_vclear(काष्ठा its_device *dev, u32 event_id)
अणु
	काष्ठा its_cmd_desc desc;

	/*
	 * There is no real VCLEAR command. This is just a normal CLEAR,
	 * with a VSYNC instead of a SYNC.
	 */
	desc.its_clear_cmd.dev = dev;
	desc.its_clear_cmd.event_id = event_id;

	its_send_single_vcommand(dev->its, its_build_vclear_cmd, &desc);
पूर्ण

अटल व्योम its_send_invdb(काष्ठा its_node *its, काष्ठा its_vpe *vpe)
अणु
	काष्ठा its_cmd_desc desc;

	desc.its_invdb_cmd.vpe = vpe;
	its_send_single_vcommand(its, its_build_invdb_cmd, &desc);
पूर्ण

/*
 * irqchip functions - assumes MSI, mostly.
 */
अटल व्योम lpi_ग_लिखो_config(काष्ठा irq_data *d, u8 clr, u8 set)
अणु
	काष्ठा its_vlpi_map *map = get_vlpi_map(d);
	irq_hw_number_t hwirq;
	व्योम *va;
	u8 *cfg;

	अगर (map) अणु
		va = page_address(map->vm->vprop_page);
		hwirq = map->vपूर्णांकid;

		/* Remember the updated property */
		map->properties &= ~clr;
		map->properties |= set | LPI_PROP_GROUP1;
	पूर्ण अन्यथा अणु
		va = gic_rdists->prop_table_va;
		hwirq = d->hwirq;
	पूर्ण

	cfg = va + hwirq - 8192;
	*cfg &= ~clr;
	*cfg |= set | LPI_PROP_GROUP1;

	/*
	 * Make the above ग_लिखो visible to the redistributors.
	 * And yes, we're flushing exactly: One. Single. Byte.
	 * Humpf...
	 */
	अगर (gic_rdists->flags & RDIST_FLAGS_PROPBASE_NEEDS_FLUSHING)
		gic_flush_dcache_to_poc(cfg, माप(*cfg));
	अन्यथा
		dsb(ishst);
पूर्ण

अटल व्योम रुको_क्रम_syncr(व्योम __iomem *rdbase)
अणु
	जबतक (पढ़ोl_relaxed(rdbase + GICR_SYNCR) & 1)
		cpu_relax();
पूर्ण

अटल व्योम direct_lpi_inv(काष्ठा irq_data *d)
अणु
	काष्ठा its_vlpi_map *map = get_vlpi_map(d);
	व्योम __iomem *rdbase;
	अचिन्हित दीर्घ flags;
	u64 val;
	पूर्णांक cpu;

	अगर (map) अणु
		काष्ठा its_device *its_dev = irq_data_get_irq_chip_data(d);

		WARN_ON(!is_v4_1(its_dev->its));

		val  = GICR_INVLPIR_V;
		val |= FIELD_PREP(GICR_INVLPIR_VPEID, map->vpe->vpe_id);
		val |= FIELD_PREP(GICR_INVLPIR_INTID, map->vपूर्णांकid);
	पूर्ण अन्यथा अणु
		val = d->hwirq;
	पूर्ण

	/* Target the redistributor this LPI is currently routed to */
	cpu = irq_to_cpuid_lock(d, &flags);
	raw_spin_lock(&gic_data_rdist_cpu(cpu)->rd_lock);
	rdbase = per_cpu_ptr(gic_rdists->rdist, cpu)->rd_base;
	gic_ग_लिखो_lpir(val, rdbase + GICR_INVLPIR);

	रुको_क्रम_syncr(rdbase);
	raw_spin_unlock(&gic_data_rdist_cpu(cpu)->rd_lock);
	irq_to_cpuid_unlock(d, flags);
पूर्ण

अटल व्योम lpi_update_config(काष्ठा irq_data *d, u8 clr, u8 set)
अणु
	काष्ठा its_device *its_dev = irq_data_get_irq_chip_data(d);

	lpi_ग_लिखो_config(d, clr, set);
	अगर (gic_rdists->has_direct_lpi &&
	    (is_v4_1(its_dev->its) || !irqd_is_क्रमwarded_to_vcpu(d)))
		direct_lpi_inv(d);
	अन्यथा अगर (!irqd_is_क्रमwarded_to_vcpu(d))
		its_send_inv(its_dev, its_get_event_id(d));
	अन्यथा
		its_send_vinv(its_dev, its_get_event_id(d));
पूर्ण

अटल व्योम its_vlpi_set_करोorbell(काष्ठा irq_data *d, bool enable)
अणु
	काष्ठा its_device *its_dev = irq_data_get_irq_chip_data(d);
	u32 event = its_get_event_id(d);
	काष्ठा its_vlpi_map *map;

	/*
	 * GICv4.1 करोes away with the per-LPI nonsense, nothing to करो
	 * here.
	 */
	अगर (is_v4_1(its_dev->its))
		वापस;

	map = dev_event_to_vlpi_map(its_dev, event);

	अगर (map->db_enabled == enable)
		वापस;

	map->db_enabled = enable;

	/*
	 * More fun with the architecture:
	 *
	 * Ideally, we'd issue a VMAPTI to set the करोorbell to its LPI
	 * value or to 1023, depending on the enable bit. But that
	 * would be issuing a mapping क्रम an /existing/ DevID+EventID
	 * pair, which is UNPREDICTABLE. Instead, let's issue a VMOVI
	 * to the /same/ vPE, using this opportunity to adjust the
	 * करोorbell. Mouahahahaha. We loves it, Precious.
	 */
	its_send_vmovi(its_dev, event);
पूर्ण

अटल व्योम its_mask_irq(काष्ठा irq_data *d)
अणु
	अगर (irqd_is_क्रमwarded_to_vcpu(d))
		its_vlpi_set_करोorbell(d, false);

	lpi_update_config(d, LPI_PROP_ENABLED, 0);
पूर्ण

अटल व्योम its_unmask_irq(काष्ठा irq_data *d)
अणु
	अगर (irqd_is_क्रमwarded_to_vcpu(d))
		its_vlpi_set_करोorbell(d, true);

	lpi_update_config(d, 0, LPI_PROP_ENABLED);
पूर्ण

अटल __maybe_unused u32 its_पढ़ो_lpi_count(काष्ठा irq_data *d, पूर्णांक cpu)
अणु
	अगर (irqd_affinity_is_managed(d))
		वापस atomic_पढ़ो(&per_cpu_ptr(&cpu_lpi_count, cpu)->managed);

	वापस atomic_पढ़ो(&per_cpu_ptr(&cpu_lpi_count, cpu)->unmanaged);
पूर्ण

अटल व्योम its_inc_lpi_count(काष्ठा irq_data *d, पूर्णांक cpu)
अणु
	अगर (irqd_affinity_is_managed(d))
		atomic_inc(&per_cpu_ptr(&cpu_lpi_count, cpu)->managed);
	अन्यथा
		atomic_inc(&per_cpu_ptr(&cpu_lpi_count, cpu)->unmanaged);
पूर्ण

अटल व्योम its_dec_lpi_count(काष्ठा irq_data *d, पूर्णांक cpu)
अणु
	अगर (irqd_affinity_is_managed(d))
		atomic_dec(&per_cpu_ptr(&cpu_lpi_count, cpu)->managed);
	अन्यथा
		atomic_dec(&per_cpu_ptr(&cpu_lpi_count, cpu)->unmanaged);
पूर्ण

अटल अचिन्हित पूर्णांक cpumask_pick_least_loaded(काष्ठा irq_data *d,
					      स्थिर काष्ठा cpumask *cpu_mask)
अणु
	अचिन्हित पूर्णांक cpu = nr_cpu_ids, पंचांगp;
	पूर्णांक count = S32_MAX;

	क्रम_each_cpu(पंचांगp, cpu_mask) अणु
		पूर्णांक this_count = its_पढ़ो_lpi_count(d, पंचांगp);
		अगर (this_count < count) अणु
			cpu = पंचांगp;
		        count = this_count;
		पूर्ण
	पूर्ण

	वापस cpu;
पूर्ण

/*
 * As suggested by Thomas Gleixner in:
 * https://lore.kernel.org/r/87h80q2aoc.fsf@nanos.tec.linutronix.de
 */
अटल पूर्णांक its_select_cpu(काष्ठा irq_data *d,
			  स्थिर काष्ठा cpumask *aff_mask)
अणु
	काष्ठा its_device *its_dev = irq_data_get_irq_chip_data(d);
	cpumask_var_t पंचांगpmask;
	पूर्णांक cpu, node;

	अगर (!alloc_cpumask_var(&पंचांगpmask, GFP_ATOMIC))
		वापस -ENOMEM;

	node = its_dev->its->numa_node;

	अगर (!irqd_affinity_is_managed(d)) अणु
		/* First try the NUMA node */
		अगर (node != NUMA_NO_NODE) अणु
			/*
			 * Try the पूर्णांकersection of the affinity mask and the
			 * node mask (and the online mask, just to be safe).
			 */
			cpumask_and(पंचांगpmask, cpumask_of_node(node), aff_mask);
			cpumask_and(पंचांगpmask, पंचांगpmask, cpu_online_mask);

			/*
			 * Ideally, we would check अगर the mask is empty, and
			 * try again on the full node here.
			 *
			 * But it turns out that the way ACPI describes the
			 * affinity क्रम ITSs only deals about memory, and
			 * not target CPUs, so it cannot describe a single
			 * ITS placed next to two NUMA nodes.
			 *
			 * Instead, just fallback on the online mask. This
			 * भागerges from Thomas' suggestion above.
			 */
			cpu = cpumask_pick_least_loaded(d, पंचांगpmask);
			अगर (cpu < nr_cpu_ids)
				जाओ out;

			/* If we can't cross sockets, give up */
			अगर ((its_dev->its->flags & ITS_FLAGS_WORKAROUND_CAVIUM_23144))
				जाओ out;

			/* If the above failed, expand the search */
		पूर्ण

		/* Try the पूर्णांकersection of the affinity and online masks */
		cpumask_and(पंचांगpmask, aff_mask, cpu_online_mask);

		/* If that करोesn't fly, the online mask is the last resort */
		अगर (cpumask_empty(पंचांगpmask))
			cpumask_copy(पंचांगpmask, cpu_online_mask);

		cpu = cpumask_pick_least_loaded(d, पंचांगpmask);
	पूर्ण अन्यथा अणु
		cpumask_and(पंचांगpmask, irq_data_get_affinity_mask(d), cpu_online_mask);

		/* If we cannot cross sockets, limit the search to that node */
		अगर ((its_dev->its->flags & ITS_FLAGS_WORKAROUND_CAVIUM_23144) &&
		    node != NUMA_NO_NODE)
			cpumask_and(पंचांगpmask, पंचांगpmask, cpumask_of_node(node));

		cpu = cpumask_pick_least_loaded(d, पंचांगpmask);
	पूर्ण
out:
	मुक्त_cpumask_var(पंचांगpmask);

	pr_debug("IRQ%d -> %*pbl CPU%d\n", d->irq, cpumask_pr_args(aff_mask), cpu);
	वापस cpu;
पूर्ण

अटल पूर्णांक its_set_affinity(काष्ठा irq_data *d, स्थिर काष्ठा cpumask *mask_val,
			    bool क्रमce)
अणु
	काष्ठा its_device *its_dev = irq_data_get_irq_chip_data(d);
	काष्ठा its_collection *target_col;
	u32 id = its_get_event_id(d);
	पूर्णांक cpu, prev_cpu;

	/* A क्रमwarded पूर्णांकerrupt should use irq_set_vcpu_affinity */
	अगर (irqd_is_क्रमwarded_to_vcpu(d))
		वापस -EINVAL;

	prev_cpu = its_dev->event_map.col_map[id];
	its_dec_lpi_count(d, prev_cpu);

	अगर (!क्रमce)
		cpu = its_select_cpu(d, mask_val);
	अन्यथा
		cpu = cpumask_pick_least_loaded(d, mask_val);

	अगर (cpu < 0 || cpu >= nr_cpu_ids)
		जाओ err;

	/* करोn't set the affinity when the target cpu is same as current one */
	अगर (cpu != prev_cpu) अणु
		target_col = &its_dev->its->collections[cpu];
		its_send_movi(its_dev, target_col, id);
		its_dev->event_map.col_map[id] = cpu;
		irq_data_update_effective_affinity(d, cpumask_of(cpu));
	पूर्ण

	its_inc_lpi_count(d, cpu);

	वापस IRQ_SET_MASK_OK_DONE;

err:
	its_inc_lpi_count(d, prev_cpu);
	वापस -EINVAL;
पूर्ण

अटल u64 its_irq_get_msi_base(काष्ठा its_device *its_dev)
अणु
	काष्ठा its_node *its = its_dev->its;

	वापस its->phys_base + GITS_TRANSLATER;
पूर्ण

अटल व्योम its_irq_compose_msi_msg(काष्ठा irq_data *d, काष्ठा msi_msg *msg)
अणु
	काष्ठा its_device *its_dev = irq_data_get_irq_chip_data(d);
	काष्ठा its_node *its;
	u64 addr;

	its = its_dev->its;
	addr = its->get_msi_base(its_dev);

	msg->address_lo		= lower_32_bits(addr);
	msg->address_hi		= upper_32_bits(addr);
	msg->data		= its_get_event_id(d);

	iommu_dma_compose_msi_msg(irq_data_get_msi_desc(d), msg);
पूर्ण

अटल पूर्णांक its_irq_set_irqchip_state(काष्ठा irq_data *d,
				     क्रमागत irqchip_irq_state which,
				     bool state)
अणु
	काष्ठा its_device *its_dev = irq_data_get_irq_chip_data(d);
	u32 event = its_get_event_id(d);

	अगर (which != IRQCHIP_STATE_PENDING)
		वापस -EINVAL;

	अगर (irqd_is_क्रमwarded_to_vcpu(d)) अणु
		अगर (state)
			its_send_vपूर्णांक(its_dev, event);
		अन्यथा
			its_send_vclear(its_dev, event);
	पूर्ण अन्यथा अणु
		अगर (state)
			its_send_पूर्णांक(its_dev, event);
		अन्यथा
			its_send_clear(its_dev, event);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक its_irq_retrigger(काष्ठा irq_data *d)
अणु
	वापस !its_irq_set_irqchip_state(d, IRQCHIP_STATE_PENDING, true);
पूर्ण

/*
 * Two favourable हालs:
 *
 * (a) Either we have a GICv4.1, and all vPEs have to be mapped at all बार
 *     क्रम vSGI delivery
 *
 * (b) Or the ITSs करो not use a list map, meaning that VMOVP is cheap enough
 *     and we're better off mapping all VPEs always
 *
 * If neither (a) nor (b) is true, then we map vPEs on demand.
 *
 */
अटल bool gic_requires_eager_mapping(व्योम)
अणु
	अगर (!its_list_map || gic_rdists->has_rvpeid)
		वापस true;

	वापस false;
पूर्ण

अटल व्योम its_map_vm(काष्ठा its_node *its, काष्ठा its_vm *vm)
अणु
	अचिन्हित दीर्घ flags;

	अगर (gic_requires_eager_mapping())
		वापस;

	raw_spin_lock_irqsave(&vmovp_lock, flags);

	/*
	 * If the VM wasn't mapped yet, iterate over the vpes and get
	 * them mapped now.
	 */
	vm->vlpi_count[its->list_nr]++;

	अगर (vm->vlpi_count[its->list_nr] == 1) अणु
		पूर्णांक i;

		क्रम (i = 0; i < vm->nr_vpes; i++) अणु
			काष्ठा its_vpe *vpe = vm->vpes[i];
			काष्ठा irq_data *d = irq_get_irq_data(vpe->irq);

			/* Map the VPE to the first possible CPU */
			vpe->col_idx = cpumask_first(cpu_online_mask);
			its_send_vmapp(its, vpe, true);
			its_send_vinvall(its, vpe);
			irq_data_update_effective_affinity(d, cpumask_of(vpe->col_idx));
		पूर्ण
	पूर्ण

	raw_spin_unlock_irqrestore(&vmovp_lock, flags);
पूर्ण

अटल व्योम its_unmap_vm(काष्ठा its_node *its, काष्ठा its_vm *vm)
अणु
	अचिन्हित दीर्घ flags;

	/* Not using the ITS list? Everything is always mapped. */
	अगर (gic_requires_eager_mapping())
		वापस;

	raw_spin_lock_irqsave(&vmovp_lock, flags);

	अगर (!--vm->vlpi_count[its->list_nr]) अणु
		पूर्णांक i;

		क्रम (i = 0; i < vm->nr_vpes; i++)
			its_send_vmapp(its, vm->vpes[i], false);
	पूर्ण

	raw_spin_unlock_irqrestore(&vmovp_lock, flags);
पूर्ण

अटल पूर्णांक its_vlpi_map(काष्ठा irq_data *d, काष्ठा its_cmd_info *info)
अणु
	काष्ठा its_device *its_dev = irq_data_get_irq_chip_data(d);
	u32 event = its_get_event_id(d);
	पूर्णांक ret = 0;

	अगर (!info->map)
		वापस -EINVAL;

	raw_spin_lock(&its_dev->event_map.vlpi_lock);

	अगर (!its_dev->event_map.vm) अणु
		काष्ठा its_vlpi_map *maps;

		maps = kसुस्मृति(its_dev->event_map.nr_lpis, माप(*maps),
			       GFP_ATOMIC);
		अगर (!maps) अणु
			ret = -ENOMEM;
			जाओ out;
		पूर्ण

		its_dev->event_map.vm = info->map->vm;
		its_dev->event_map.vlpi_maps = maps;
	पूर्ण अन्यथा अगर (its_dev->event_map.vm != info->map->vm) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	/* Get our निजी copy of the mapping inक्रमmation */
	its_dev->event_map.vlpi_maps[event] = *info->map;

	अगर (irqd_is_क्रमwarded_to_vcpu(d)) अणु
		/* Alपढ़ोy mapped, move it around */
		its_send_vmovi(its_dev, event);
	पूर्ण अन्यथा अणु
		/* Ensure all the VPEs are mapped on this ITS */
		its_map_vm(its_dev->its, info->map->vm);

		/*
		 * Flag the पूर्णांकerrupt as क्रमwarded so that we can
		 * start poking the भव property table.
		 */
		irqd_set_क्रमwarded_to_vcpu(d);

		/* Write out the property to the prop table */
		lpi_ग_लिखो_config(d, 0xff, info->map->properties);

		/* Drop the physical mapping */
		its_send_discard(its_dev, event);

		/* and install the भव one */
		its_send_vmapti(its_dev, event);

		/* Increment the number of VLPIs */
		its_dev->event_map.nr_vlpis++;
	पूर्ण

out:
	raw_spin_unlock(&its_dev->event_map.vlpi_lock);
	वापस ret;
पूर्ण

अटल पूर्णांक its_vlpi_get(काष्ठा irq_data *d, काष्ठा its_cmd_info *info)
अणु
	काष्ठा its_device *its_dev = irq_data_get_irq_chip_data(d);
	काष्ठा its_vlpi_map *map;
	पूर्णांक ret = 0;

	raw_spin_lock(&its_dev->event_map.vlpi_lock);

	map = get_vlpi_map(d);

	अगर (!its_dev->event_map.vm || !map) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	/* Copy our mapping inक्रमmation to the incoming request */
	*info->map = *map;

out:
	raw_spin_unlock(&its_dev->event_map.vlpi_lock);
	वापस ret;
पूर्ण

अटल पूर्णांक its_vlpi_unmap(काष्ठा irq_data *d)
अणु
	काष्ठा its_device *its_dev = irq_data_get_irq_chip_data(d);
	u32 event = its_get_event_id(d);
	पूर्णांक ret = 0;

	raw_spin_lock(&its_dev->event_map.vlpi_lock);

	अगर (!its_dev->event_map.vm || !irqd_is_क्रमwarded_to_vcpu(d)) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	/* Drop the भव mapping */
	its_send_discard(its_dev, event);

	/* and restore the physical one */
	irqd_clr_क्रमwarded_to_vcpu(d);
	its_send_mapti(its_dev, d->hwirq, event);
	lpi_update_config(d, 0xff, (LPI_PROP_DEFAULT_PRIO |
				    LPI_PROP_ENABLED |
				    LPI_PROP_GROUP1));

	/* Potentially unmap the VM from this ITS */
	its_unmap_vm(its_dev->its, its_dev->event_map.vm);

	/*
	 * Drop the refcount and make the device available again अगर
	 * this was the last VLPI.
	 */
	अगर (!--its_dev->event_map.nr_vlpis) अणु
		its_dev->event_map.vm = शून्य;
		kमुक्त(its_dev->event_map.vlpi_maps);
	पूर्ण

out:
	raw_spin_unlock(&its_dev->event_map.vlpi_lock);
	वापस ret;
पूर्ण

अटल पूर्णांक its_vlpi_prop_update(काष्ठा irq_data *d, काष्ठा its_cmd_info *info)
अणु
	काष्ठा its_device *its_dev = irq_data_get_irq_chip_data(d);

	अगर (!its_dev->event_map.vm || !irqd_is_क्रमwarded_to_vcpu(d))
		वापस -EINVAL;

	अगर (info->cmd_type == PROP_UPDATE_AND_INV_VLPI)
		lpi_update_config(d, 0xff, info->config);
	अन्यथा
		lpi_ग_लिखो_config(d, 0xff, info->config);
	its_vlpi_set_करोorbell(d, !!(info->config & LPI_PROP_ENABLED));

	वापस 0;
पूर्ण

अटल पूर्णांक its_irq_set_vcpu_affinity(काष्ठा irq_data *d, व्योम *vcpu_info)
अणु
	काष्ठा its_device *its_dev = irq_data_get_irq_chip_data(d);
	काष्ठा its_cmd_info *info = vcpu_info;

	/* Need a v4 ITS */
	अगर (!is_v4(its_dev->its))
		वापस -EINVAL;

	/* Unmap request? */
	अगर (!info)
		वापस its_vlpi_unmap(d);

	चयन (info->cmd_type) अणु
	हाल MAP_VLPI:
		वापस its_vlpi_map(d, info);

	हाल GET_VLPI:
		वापस its_vlpi_get(d, info);

	हाल PROP_UPDATE_VLPI:
	हाल PROP_UPDATE_AND_INV_VLPI:
		वापस its_vlpi_prop_update(d, info);

	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल काष्ठा irq_chip its_irq_chip = अणु
	.name			= "ITS",
	.irq_mask		= its_mask_irq,
	.irq_unmask		= its_unmask_irq,
	.irq_eoi		= irq_chip_eoi_parent,
	.irq_set_affinity	= its_set_affinity,
	.irq_compose_msi_msg	= its_irq_compose_msi_msg,
	.irq_set_irqchip_state	= its_irq_set_irqchip_state,
	.irq_retrigger		= its_irq_retrigger,
	.irq_set_vcpu_affinity	= its_irq_set_vcpu_affinity,
पूर्ण;


/*
 * How we allocate LPIs:
 *
 * lpi_range_list contains ranges of LPIs that are to available to
 * allocate from. To allocate LPIs, just pick the first range that
 * fits the required allocation, and reduce it by the required
 * amount. Once empty, हटाओ the range from the list.
 *
 * To मुक्त a range of LPIs, add a मुक्त range to the list, sort it and
 * merge the result अगर the new range happens to be adjacent to an
 * alपढ़ोy मुक्त block.
 *
 * The consequence of the above is that allocation is cost is low, but
 * मुक्तing is expensive. We assumes that मुक्तing rarely occurs.
 */
#घोषणा ITS_MAX_LPI_NRBITS	16 /* 64K LPIs */

अटल DEFINE_MUTEX(lpi_range_lock);
अटल LIST_HEAD(lpi_range_list);

काष्ठा lpi_range अणु
	काष्ठा list_head	entry;
	u32			base_id;
	u32			span;
पूर्ण;

अटल काष्ठा lpi_range *mk_lpi_range(u32 base, u32 span)
अणु
	काष्ठा lpi_range *range;

	range = kदो_स्मृति(माप(*range), GFP_KERNEL);
	अगर (range) अणु
		range->base_id = base;
		range->span = span;
	पूर्ण

	वापस range;
पूर्ण

अटल पूर्णांक alloc_lpi_range(u32 nr_lpis, u32 *base)
अणु
	काष्ठा lpi_range *range, *पंचांगp;
	पूर्णांक err = -ENOSPC;

	mutex_lock(&lpi_range_lock);

	list_क्रम_each_entry_safe(range, पंचांगp, &lpi_range_list, entry) अणु
		अगर (range->span >= nr_lpis) अणु
			*base = range->base_id;
			range->base_id += nr_lpis;
			range->span -= nr_lpis;

			अगर (range->span == 0) अणु
				list_del(&range->entry);
				kमुक्त(range);
			पूर्ण

			err = 0;
			अवरोध;
		पूर्ण
	पूर्ण

	mutex_unlock(&lpi_range_lock);

	pr_debug("ITS: alloc %u:%u\n", *base, nr_lpis);
	वापस err;
पूर्ण

अटल व्योम merge_lpi_ranges(काष्ठा lpi_range *a, काष्ठा lpi_range *b)
अणु
	अगर (&a->entry == &lpi_range_list || &b->entry == &lpi_range_list)
		वापस;
	अगर (a->base_id + a->span != b->base_id)
		वापस;
	b->base_id = a->base_id;
	b->span += a->span;
	list_del(&a->entry);
	kमुक्त(a);
पूर्ण

अटल पूर्णांक मुक्त_lpi_range(u32 base, u32 nr_lpis)
अणु
	काष्ठा lpi_range *new, *old;

	new = mk_lpi_range(base, nr_lpis);
	अगर (!new)
		वापस -ENOMEM;

	mutex_lock(&lpi_range_lock);

	list_क्रम_each_entry_reverse(old, &lpi_range_list, entry) अणु
		अगर (old->base_id < base)
			अवरोध;
	पूर्ण
	/*
	 * old is the last element with ->base_id smaller than base,
	 * so new goes right after it. If there are no elements with
	 * ->base_id smaller than base, &old->entry ends up poपूर्णांकing
	 * at the head of the list, and inserting new it the start of
	 * the list is the right thing to करो in that हाल as well.
	 */
	list_add(&new->entry, &old->entry);
	/*
	 * Now check अगर we can merge with the preceding and/or
	 * following ranges.
	 */
	merge_lpi_ranges(old, new);
	merge_lpi_ranges(new, list_next_entry(new, entry));

	mutex_unlock(&lpi_range_lock);
	वापस 0;
पूर्ण

अटल पूर्णांक __init its_lpi_init(u32 id_bits)
अणु
	u32 lpis = (1UL << id_bits) - 8192;
	u32 numlpis;
	पूर्णांक err;

	numlpis = 1UL << GICD_TYPER_NUM_LPIS(gic_rdists->gicd_typer);

	अगर (numlpis > 2 && !WARN_ON(numlpis > lpis)) अणु
		lpis = numlpis;
		pr_info("ITS: Using hypervisor restricted LPI range [%u]\n",
			lpis);
	पूर्ण

	/*
	 * Initializing the allocator is just the same as मुक्तing the
	 * full range of LPIs.
	 */
	err = मुक्त_lpi_range(8192, lpis);
	pr_debug("ITS: Allocator initialized for %u LPIs\n", lpis);
	वापस err;
पूर्ण

अटल अचिन्हित दीर्घ *its_lpi_alloc(पूर्णांक nr_irqs, u32 *base, पूर्णांक *nr_ids)
अणु
	अचिन्हित दीर्घ *biपंचांगap = शून्य;
	पूर्णांक err = 0;

	करो अणु
		err = alloc_lpi_range(nr_irqs, base);
		अगर (!err)
			अवरोध;

		nr_irqs /= 2;
	पूर्ण जबतक (nr_irqs > 0);

	अगर (!nr_irqs)
		err = -ENOSPC;

	अगर (err)
		जाओ out;

	biपंचांगap = kसुस्मृति(BITS_TO_LONGS(nr_irqs), माप (दीर्घ), GFP_ATOMIC);
	अगर (!biपंचांगap)
		जाओ out;

	*nr_ids = nr_irqs;

out:
	अगर (!biपंचांगap)
		*base = *nr_ids = 0;

	वापस biपंचांगap;
पूर्ण

अटल व्योम its_lpi_मुक्त(अचिन्हित दीर्घ *biपंचांगap, u32 base, u32 nr_ids)
अणु
	WARN_ON(मुक्त_lpi_range(base, nr_ids));
	kमुक्त(biपंचांगap);
पूर्ण

अटल व्योम gic_reset_prop_table(व्योम *va)
अणु
	/* Priority 0xa0, Group-1, disabled */
	स_रखो(va, LPI_PROP_DEFAULT_PRIO | LPI_PROP_GROUP1, LPI_PROPBASE_SZ);

	/* Make sure the GIC will observe the written configuration */
	gic_flush_dcache_to_poc(va, LPI_PROPBASE_SZ);
पूर्ण

अटल काष्ठा page *its_allocate_prop_table(gfp_t gfp_flags)
अणु
	काष्ठा page *prop_page;

	prop_page = alloc_pages(gfp_flags, get_order(LPI_PROPBASE_SZ));
	अगर (!prop_page)
		वापस शून्य;

	gic_reset_prop_table(page_address(prop_page));

	वापस prop_page;
पूर्ण

अटल व्योम its_मुक्त_prop_table(काष्ठा page *prop_page)
अणु
	मुक्त_pages((अचिन्हित दीर्घ)page_address(prop_page),
		   get_order(LPI_PROPBASE_SZ));
पूर्ण

अटल bool gic_check_reserved_range(phys_addr_t addr, अचिन्हित दीर्घ size)
अणु
	phys_addr_t start, end, addr_end;
	u64 i;

	/*
	 * We करोn't bother checking क्रम a kdump kernel as by
	 * स्थिरruction, the LPI tables are out of this kernel's
	 * memory map.
	 */
	अगर (is_kdump_kernel())
		वापस true;

	addr_end = addr + size - 1;

	क्रम_each_reserved_mem_range(i, &start, &end) अणु
		अगर (addr >= start && addr_end <= end)
			वापस true;
	पूर्ण

	/* Not found, not a good sign... */
	pr_warn("GICv3: Expected reserved range [%pa:%pa], not found\n",
		&addr, &addr_end);
	add_taपूर्णांक(TAINT_CRAP, LOCKDEP_STILL_OK);
	वापस false;
पूर्ण

अटल पूर्णांक gic_reserve_range(phys_addr_t addr, अचिन्हित दीर्घ size)
अणु
	अगर (efi_enabled(EFI_CONFIG_TABLES))
		वापस efi_mem_reserve_persistent(addr, size);

	वापस 0;
पूर्ण

अटल पूर्णांक __init its_setup_lpi_prop_table(व्योम)
अणु
	अगर (gic_rdists->flags & RDIST_FLAGS_RD_TABLES_PREALLOCATED) अणु
		u64 val;

		val = gicr_पढ़ो_propbaser(gic_data_rdist_rd_base() + GICR_PROPBASER);
		lpi_id_bits = (val & GICR_PROPBASER_IDBITS_MASK) + 1;

		gic_rdists->prop_table_pa = val & GENMASK_ULL(51, 12);
		gic_rdists->prop_table_va = memremap(gic_rdists->prop_table_pa,
						     LPI_PROPBASE_SZ,
						     MEMREMAP_WB);
		gic_reset_prop_table(gic_rdists->prop_table_va);
	पूर्ण अन्यथा अणु
		काष्ठा page *page;

		lpi_id_bits = min_t(u32,
				    GICD_TYPER_ID_BITS(gic_rdists->gicd_typer),
				    ITS_MAX_LPI_NRBITS);
		page = its_allocate_prop_table(GFP_NOWAIT);
		अगर (!page) अणु
			pr_err("Failed to allocate PROPBASE\n");
			वापस -ENOMEM;
		पूर्ण

		gic_rdists->prop_table_pa = page_to_phys(page);
		gic_rdists->prop_table_va = page_address(page);
		WARN_ON(gic_reserve_range(gic_rdists->prop_table_pa,
					  LPI_PROPBASE_SZ));
	पूर्ण

	pr_info("GICv3: using LPI property table @%pa\n",
		&gic_rdists->prop_table_pa);

	वापस its_lpi_init(lpi_id_bits);
पूर्ण

अटल स्थिर अक्षर *its_base_type_string[] = अणु
	[GITS_BASER_TYPE_DEVICE]	= "Devices",
	[GITS_BASER_TYPE_VCPU]		= "Virtual CPUs",
	[GITS_BASER_TYPE_RESERVED3]	= "Reserved (3)",
	[GITS_BASER_TYPE_COLLECTION]	= "Interrupt Collections",
	[GITS_BASER_TYPE_RESERVED5] 	= "Reserved (5)",
	[GITS_BASER_TYPE_RESERVED6] 	= "Reserved (6)",
	[GITS_BASER_TYPE_RESERVED7] 	= "Reserved (7)",
पूर्ण;

अटल u64 its_पढ़ो_baser(काष्ठा its_node *its, काष्ठा its_baser *baser)
अणु
	u32 idx = baser - its->tables;

	वापस gits_पढ़ो_baser(its->base + GITS_BASER + (idx << 3));
पूर्ण

अटल व्योम its_ग_लिखो_baser(काष्ठा its_node *its, काष्ठा its_baser *baser,
			    u64 val)
अणु
	u32 idx = baser - its->tables;

	gits_ग_लिखो_baser(val, its->base + GITS_BASER + (idx << 3));
	baser->val = its_पढ़ो_baser(its, baser);
पूर्ण

अटल पूर्णांक its_setup_baser(काष्ठा its_node *its, काष्ठा its_baser *baser,
			   u64 cache, u64 shr, u32 order, bool indirect)
अणु
	u64 val = its_पढ़ो_baser(its, baser);
	u64 esz = GITS_BASER_ENTRY_SIZE(val);
	u64 type = GITS_BASER_TYPE(val);
	u64 baser_phys, पंचांगp;
	u32 alloc_pages, psz;
	काष्ठा page *page;
	व्योम *base;

	psz = baser->psz;
	alloc_pages = (PAGE_ORDER_TO_SIZE(order) / psz);
	अगर (alloc_pages > GITS_BASER_PAGES_MAX) अणु
		pr_warn("ITS@%pa: %s too large, reduce ITS pages %u->%u\n",
			&its->phys_base, its_base_type_string[type],
			alloc_pages, GITS_BASER_PAGES_MAX);
		alloc_pages = GITS_BASER_PAGES_MAX;
		order = get_order(GITS_BASER_PAGES_MAX * psz);
	पूर्ण

	page = alloc_pages_node(its->numa_node, GFP_KERNEL | __GFP_ZERO, order);
	अगर (!page)
		वापस -ENOMEM;

	base = (व्योम *)page_address(page);
	baser_phys = virt_to_phys(base);

	/* Check अगर the physical address of the memory is above 48bits */
	अगर (IS_ENABLED(CONFIG_ARM64_64K_PAGES) && (baser_phys >> 48)) अणु

		/* 52bit PA is supported only when PageSize=64K */
		अगर (psz != SZ_64K) अणु
			pr_err("ITS: no 52bit PA support when psz=%d\n", psz);
			मुक्त_pages((अचिन्हित दीर्घ)base, order);
			वापस -ENXIO;
		पूर्ण

		/* Convert 52bit PA to 48bit field */
		baser_phys = GITS_BASER_PHYS_52_to_48(baser_phys);
	पूर्ण

retry_baser:
	val = (baser_phys					 |
		(type << GITS_BASER_TYPE_SHIFT)			 |
		((esz - 1) << GITS_BASER_ENTRY_SIZE_SHIFT)	 |
		((alloc_pages - 1) << GITS_BASER_PAGES_SHIFT)	 |
		cache						 |
		shr						 |
		GITS_BASER_VALID);

	val |=	indirect ? GITS_BASER_INसूचीECT : 0x0;

	चयन (psz) अणु
	हाल SZ_4K:
		val |= GITS_BASER_PAGE_SIZE_4K;
		अवरोध;
	हाल SZ_16K:
		val |= GITS_BASER_PAGE_SIZE_16K;
		अवरोध;
	हाल SZ_64K:
		val |= GITS_BASER_PAGE_SIZE_64K;
		अवरोध;
	पूर्ण

	its_ग_लिखो_baser(its, baser, val);
	पंचांगp = baser->val;

	अगर ((val ^ पंचांगp) & GITS_BASER_SHAREABILITY_MASK) अणु
		/*
		 * Shareability didn't stick. Just use
		 * whatever the पढ़ो reported, which is likely
		 * to be the only thing this redistributor
		 * supports. If that's zero, make it
		 * non-cacheable as well.
		 */
		shr = पंचांगp & GITS_BASER_SHAREABILITY_MASK;
		अगर (!shr) अणु
			cache = GITS_BASER_nC;
			gic_flush_dcache_to_poc(base, PAGE_ORDER_TO_SIZE(order));
		पूर्ण
		जाओ retry_baser;
	पूर्ण

	अगर (val != पंचांगp) अणु
		pr_err("ITS@%pa: %s doesn't stick: %llx %llx\n",
		       &its->phys_base, its_base_type_string[type],
		       val, पंचांगp);
		मुक्त_pages((अचिन्हित दीर्घ)base, order);
		वापस -ENXIO;
	पूर्ण

	baser->order = order;
	baser->base = base;
	baser->psz = psz;
	पंचांगp = indirect ? GITS_LVL1_ENTRY_SIZE : esz;

	pr_info("ITS@%pa: allocated %d %s @%lx (%s, esz %d, psz %dK, shr %d)\n",
		&its->phys_base, (पूर्णांक)(PAGE_ORDER_TO_SIZE(order) / (पूर्णांक)पंचांगp),
		its_base_type_string[type],
		(अचिन्हित दीर्घ)virt_to_phys(base),
		indirect ? "indirect" : "flat", (पूर्णांक)esz,
		psz / SZ_1K, (पूर्णांक)shr >> GITS_BASER_SHAREABILITY_SHIFT);

	वापस 0;
पूर्ण

अटल bool its_parse_indirect_baser(काष्ठा its_node *its,
				     काष्ठा its_baser *baser,
				     u32 *order, u32 ids)
अणु
	u64 पंचांगp = its_पढ़ो_baser(its, baser);
	u64 type = GITS_BASER_TYPE(पंचांगp);
	u64 esz = GITS_BASER_ENTRY_SIZE(पंचांगp);
	u64 val = GITS_BASER_InnerShareable | GITS_BASER_RaWaWb;
	u32 new_order = *order;
	u32 psz = baser->psz;
	bool indirect = false;

	/* No need to enable Indirection अगर memory requirement < (psz*2)bytes */
	अगर ((esz << ids) > (psz * 2)) अणु
		/*
		 * Find out whether hw supports a single or two-level table by
		 * table by पढ़ोing bit at offset '62' after writing '1' to it.
		 */
		its_ग_लिखो_baser(its, baser, val | GITS_BASER_INसूचीECT);
		indirect = !!(baser->val & GITS_BASER_INसूचीECT);

		अगर (indirect) अणु
			/*
			 * The size of the lvl2 table is equal to ITS page size
			 * which is 'psz'. For computing lvl1 table size,
			 * subtract ID bits that sparse lvl2 table from 'ids'
			 * which is reported by ITS hardware बार lvl1 table
			 * entry size.
			 */
			ids -= ilog2(psz / (पूर्णांक)esz);
			esz = GITS_LVL1_ENTRY_SIZE;
		पूर्ण
	पूर्ण

	/*
	 * Allocate as many entries as required to fit the
	 * range of device IDs that the ITS can grok... The ID
	 * space being incredibly sparse, this results in a
	 * massive waste of memory अगर two-level device table
	 * feature is not supported by hardware.
	 */
	new_order = max_t(u32, get_order(esz << ids), new_order);
	अगर (new_order >= MAX_ORDER) अणु
		new_order = MAX_ORDER - 1;
		ids = ilog2(PAGE_ORDER_TO_SIZE(new_order) / (पूर्णांक)esz);
		pr_warn("ITS@%pa: %s Table too large, reduce ids %llu->%u\n",
			&its->phys_base, its_base_type_string[type],
			device_ids(its), ids);
	पूर्ण

	*order = new_order;

	वापस indirect;
पूर्ण

अटल u32 compute_common_aff(u64 val)
अणु
	u32 aff, clpiaff;

	aff = FIELD_GET(GICR_TYPER_AFFINITY, val);
	clpiaff = FIELD_GET(GICR_TYPER_COMMON_LPI_AFF, val);

	वापस aff & ~(GENMASK(31, 0) >> (clpiaff * 8));
पूर्ण

अटल u32 compute_its_aff(काष्ठा its_node *its)
अणु
	u64 val;
	u32 svpet;

	/*
	 * Reencode the ITS SVPET and MPIDR as a GICR_TYPER, and compute
	 * the resulting affinity. We then use that to see अगर this match
	 * our own affinity.
	 */
	svpet = FIELD_GET(GITS_TYPER_SVPET, its->typer);
	val  = FIELD_PREP(GICR_TYPER_COMMON_LPI_AFF, svpet);
	val |= FIELD_PREP(GICR_TYPER_AFFINITY, its->mpidr);
	वापस compute_common_aff(val);
पूर्ण

अटल काष्ठा its_node *find_sibling_its(काष्ठा its_node *cur_its)
अणु
	काष्ठा its_node *its;
	u32 aff;

	अगर (!FIELD_GET(GITS_TYPER_SVPET, cur_its->typer))
		वापस शून्य;

	aff = compute_its_aff(cur_its);

	list_क्रम_each_entry(its, &its_nodes, entry) अणु
		u64 baser;

		अगर (!is_v4_1(its) || its == cur_its)
			जारी;

		अगर (!FIELD_GET(GITS_TYPER_SVPET, its->typer))
			जारी;

		अगर (aff != compute_its_aff(its))
			जारी;

		/* GICv4.1 guarantees that the vPE table is GITS_BASER2 */
		baser = its->tables[2].val;
		अगर (!(baser & GITS_BASER_VALID))
			जारी;

		वापस its;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल व्योम its_मुक्त_tables(काष्ठा its_node *its)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < GITS_BASER_NR_REGS; i++) अणु
		अगर (its->tables[i].base) अणु
			मुक्त_pages((अचिन्हित दीर्घ)its->tables[i].base,
				   its->tables[i].order);
			its->tables[i].base = शून्य;
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक its_probe_baser_psz(काष्ठा its_node *its, काष्ठा its_baser *baser)
अणु
	u64 psz = SZ_64K;

	जबतक (psz) अणु
		u64 val, gpsz;

		val = its_पढ़ो_baser(its, baser);
		val &= ~GITS_BASER_PAGE_SIZE_MASK;

		चयन (psz) अणु
		हाल SZ_64K:
			gpsz = GITS_BASER_PAGE_SIZE_64K;
			अवरोध;
		हाल SZ_16K:
			gpsz = GITS_BASER_PAGE_SIZE_16K;
			अवरोध;
		हाल SZ_4K:
		शेष:
			gpsz = GITS_BASER_PAGE_SIZE_4K;
			अवरोध;
		पूर्ण

		gpsz >>= GITS_BASER_PAGE_SIZE_SHIFT;

		val |= FIELD_PREP(GITS_BASER_PAGE_SIZE_MASK, gpsz);
		its_ग_लिखो_baser(its, baser, val);

		अगर (FIELD_GET(GITS_BASER_PAGE_SIZE_MASK, baser->val) == gpsz)
			अवरोध;

		चयन (psz) अणु
		हाल SZ_64K:
			psz = SZ_16K;
			अवरोध;
		हाल SZ_16K:
			psz = SZ_4K;
			अवरोध;
		हाल SZ_4K:
		शेष:
			वापस -1;
		पूर्ण
	पूर्ण

	baser->psz = psz;
	वापस 0;
पूर्ण

अटल पूर्णांक its_alloc_tables(काष्ठा its_node *its)
अणु
	u64 shr = GITS_BASER_InnerShareable;
	u64 cache = GITS_BASER_RaWaWb;
	पूर्णांक err, i;

	अगर (its->flags & ITS_FLAGS_WORKAROUND_CAVIUM_22375)
		/* erratum 24313: ignore memory access type */
		cache = GITS_BASER_nCnB;

	क्रम (i = 0; i < GITS_BASER_NR_REGS; i++) अणु
		काष्ठा its_baser *baser = its->tables + i;
		u64 val = its_पढ़ो_baser(its, baser);
		u64 type = GITS_BASER_TYPE(val);
		bool indirect = false;
		u32 order;

		अगर (type == GITS_BASER_TYPE_NONE)
			जारी;

		अगर (its_probe_baser_psz(its, baser)) अणु
			its_मुक्त_tables(its);
			वापस -ENXIO;
		पूर्ण

		order = get_order(baser->psz);

		चयन (type) अणु
		हाल GITS_BASER_TYPE_DEVICE:
			indirect = its_parse_indirect_baser(its, baser, &order,
							    device_ids(its));
			अवरोध;

		हाल GITS_BASER_TYPE_VCPU:
			अगर (is_v4_1(its)) अणु
				काष्ठा its_node *sibling;

				WARN_ON(i != 2);
				अगर ((sibling = find_sibling_its(its))) अणु
					*baser = sibling->tables[2];
					its_ग_लिखो_baser(its, baser, baser->val);
					जारी;
				पूर्ण
			पूर्ण

			indirect = its_parse_indirect_baser(its, baser, &order,
							    ITS_MAX_VPEID_BITS);
			अवरोध;
		पूर्ण

		err = its_setup_baser(its, baser, cache, shr, order, indirect);
		अगर (err < 0) अणु
			its_मुक्त_tables(its);
			वापस err;
		पूर्ण

		/* Update settings which will be used क्रम next BASERn */
		cache = baser->val & GITS_BASER_CACHEABILITY_MASK;
		shr = baser->val & GITS_BASER_SHAREABILITY_MASK;
	पूर्ण

	वापस 0;
पूर्ण

अटल u64 inherit_vpe_l1_table_from_its(व्योम)
अणु
	काष्ठा its_node *its;
	u64 val;
	u32 aff;

	val = gic_पढ़ो_typer(gic_data_rdist_rd_base() + GICR_TYPER);
	aff = compute_common_aff(val);

	list_क्रम_each_entry(its, &its_nodes, entry) अणु
		u64 baser, addr;

		अगर (!is_v4_1(its))
			जारी;

		अगर (!FIELD_GET(GITS_TYPER_SVPET, its->typer))
			जारी;

		अगर (aff != compute_its_aff(its))
			जारी;

		/* GICv4.1 guarantees that the vPE table is GITS_BASER2 */
		baser = its->tables[2].val;
		अगर (!(baser & GITS_BASER_VALID))
			जारी;

		/* We have a winner! */
		gic_data_rdist()->vpe_l1_base = its->tables[2].base;

		val  = GICR_VPROPBASER_4_1_VALID;
		अगर (baser & GITS_BASER_INसूचीECT)
			val |= GICR_VPROPBASER_4_1_INसूचीECT;
		val |= FIELD_PREP(GICR_VPROPBASER_4_1_PAGE_SIZE,
				  FIELD_GET(GITS_BASER_PAGE_SIZE_MASK, baser));
		चयन (FIELD_GET(GITS_BASER_PAGE_SIZE_MASK, baser)) अणु
		हाल GIC_PAGE_SIZE_64K:
			addr = GITS_BASER_ADDR_48_to_52(baser);
			अवरोध;
		शेष:
			addr = baser & GENMASK_ULL(47, 12);
			अवरोध;
		पूर्ण
		val |= FIELD_PREP(GICR_VPROPBASER_4_1_ADDR, addr >> 12);
		val |= FIELD_PREP(GICR_VPROPBASER_SHAREABILITY_MASK,
				  FIELD_GET(GITS_BASER_SHAREABILITY_MASK, baser));
		val |= FIELD_PREP(GICR_VPROPBASER_INNER_CACHEABILITY_MASK,
				  FIELD_GET(GITS_BASER_INNER_CACHEABILITY_MASK, baser));
		val |= FIELD_PREP(GICR_VPROPBASER_4_1_SIZE, GITS_BASER_NR_PAGES(baser) - 1);

		वापस val;
	पूर्ण

	वापस 0;
पूर्ण

अटल u64 inherit_vpe_l1_table_from_rd(cpumask_t **mask)
अणु
	u32 aff;
	u64 val;
	पूर्णांक cpu;

	val = gic_पढ़ो_typer(gic_data_rdist_rd_base() + GICR_TYPER);
	aff = compute_common_aff(val);

	क्रम_each_possible_cpu(cpu) अणु
		व्योम __iomem *base = gic_data_rdist_cpu(cpu)->rd_base;

		अगर (!base || cpu == smp_processor_id())
			जारी;

		val = gic_पढ़ो_typer(base + GICR_TYPER);
		अगर (aff != compute_common_aff(val))
			जारी;

		/*
		 * At this poपूर्णांक, we have a victim. This particular CPU
		 * has alपढ़ोy booted, and has an affinity that matches
		 * ours wrt CommonLPIAff. Let's use its own VPROPBASER.
		 * Make sure we करोn't ग_लिखो the Z bit in that हाल.
		 */
		val = gicr_पढ़ो_vpropbaser(base + SZ_128K + GICR_VPROPBASER);
		val &= ~GICR_VPROPBASER_4_1_Z;

		gic_data_rdist()->vpe_l1_base = gic_data_rdist_cpu(cpu)->vpe_l1_base;
		*mask = gic_data_rdist_cpu(cpu)->vpe_table_mask;

		वापस val;
	पूर्ण

	वापस 0;
पूर्ण

अटल bool allocate_vpe_l2_table(पूर्णांक cpu, u32 id)
अणु
	व्योम __iomem *base = gic_data_rdist_cpu(cpu)->rd_base;
	अचिन्हित पूर्णांक psz, esz, idx, npg, gpsz;
	u64 val;
	काष्ठा page *page;
	__le64 *table;

	अगर (!gic_rdists->has_rvpeid)
		वापस true;

	/* Skip non-present CPUs */
	अगर (!base)
		वापस true;

	val  = gicr_पढ़ो_vpropbaser(base + SZ_128K + GICR_VPROPBASER);

	esz  = FIELD_GET(GICR_VPROPBASER_4_1_ENTRY_SIZE, val) + 1;
	gpsz = FIELD_GET(GICR_VPROPBASER_4_1_PAGE_SIZE, val);
	npg  = FIELD_GET(GICR_VPROPBASER_4_1_SIZE, val) + 1;

	चयन (gpsz) अणु
	शेष:
		WARN_ON(1);
		fallthrough;
	हाल GIC_PAGE_SIZE_4K:
		psz = SZ_4K;
		अवरोध;
	हाल GIC_PAGE_SIZE_16K:
		psz = SZ_16K;
		अवरोध;
	हाल GIC_PAGE_SIZE_64K:
		psz = SZ_64K;
		अवरोध;
	पूर्ण

	/* Don't allow vpe_id that exceeds single, flat table limit */
	अगर (!(val & GICR_VPROPBASER_4_1_INसूचीECT))
		वापस (id < (npg * psz / (esz * SZ_8)));

	/* Compute 1st level table index & check अगर that exceeds table limit */
	idx = id >> ilog2(psz / (esz * SZ_8));
	अगर (idx >= (npg * psz / GITS_LVL1_ENTRY_SIZE))
		वापस false;

	table = gic_data_rdist_cpu(cpu)->vpe_l1_base;

	/* Allocate memory क्रम 2nd level table */
	अगर (!table[idx]) अणु
		page = alloc_pages(GFP_KERNEL | __GFP_ZERO, get_order(psz));
		अगर (!page)
			वापस false;

		/* Flush Lvl2 table to PoC अगर hw करोesn't support coherency */
		अगर (!(val & GICR_VPROPBASER_SHAREABILITY_MASK))
			gic_flush_dcache_to_poc(page_address(page), psz);

		table[idx] = cpu_to_le64(page_to_phys(page) | GITS_BASER_VALID);

		/* Flush Lvl1 entry to PoC अगर hw करोesn't support coherency */
		अगर (!(val & GICR_VPROPBASER_SHAREABILITY_MASK))
			gic_flush_dcache_to_poc(table + idx, GITS_LVL1_ENTRY_SIZE);

		/* Ensure updated table contents are visible to RD hardware */
		dsb(sy);
	पूर्ण

	वापस true;
पूर्ण

अटल पूर्णांक allocate_vpe_l1_table(व्योम)
अणु
	व्योम __iomem *vlpi_base = gic_data_rdist_vlpi_base();
	u64 val, gpsz, npg, pa;
	अचिन्हित पूर्णांक psz = SZ_64K;
	अचिन्हित पूर्णांक np, epp, esz;
	काष्ठा page *page;

	अगर (!gic_rdists->has_rvpeid)
		वापस 0;

	/*
	 * अगर VPENDBASER.Valid is set, disable any previously programmed
	 * VPE by setting PendingLast जबतक clearing Valid. This has the
	 * effect of making sure no करोorbell will be generated and we can
	 * then safely clear VPROPBASER.Valid.
	 */
	अगर (gicr_पढ़ो_vpendbaser(vlpi_base + GICR_VPENDBASER) & GICR_VPENDBASER_Valid)
		gicr_ग_लिखो_vpendbaser(GICR_VPENDBASER_PendingLast,
				      vlpi_base + GICR_VPENDBASER);

	/*
	 * If we can inherit the configuration from another RD, let's करो
	 * so. Otherwise, we have to go through the allocation process. We
	 * assume that all RDs have the exact same requirements, as
	 * nothing will work otherwise.
	 */
	val = inherit_vpe_l1_table_from_rd(&gic_data_rdist()->vpe_table_mask);
	अगर (val & GICR_VPROPBASER_4_1_VALID)
		जाओ out;

	gic_data_rdist()->vpe_table_mask = kzalloc(माप(cpumask_t), GFP_ATOMIC);
	अगर (!gic_data_rdist()->vpe_table_mask)
		वापस -ENOMEM;

	val = inherit_vpe_l1_table_from_its();
	अगर (val & GICR_VPROPBASER_4_1_VALID)
		जाओ out;

	/* First probe the page size */
	val = FIELD_PREP(GICR_VPROPBASER_4_1_PAGE_SIZE, GIC_PAGE_SIZE_64K);
	gicr_ग_लिखो_vpropbaser(val, vlpi_base + GICR_VPROPBASER);
	val = gicr_पढ़ो_vpropbaser(vlpi_base + GICR_VPROPBASER);
	gpsz = FIELD_GET(GICR_VPROPBASER_4_1_PAGE_SIZE, val);
	esz = FIELD_GET(GICR_VPROPBASER_4_1_ENTRY_SIZE, val);

	चयन (gpsz) अणु
	शेष:
		gpsz = GIC_PAGE_SIZE_4K;
		fallthrough;
	हाल GIC_PAGE_SIZE_4K:
		psz = SZ_4K;
		अवरोध;
	हाल GIC_PAGE_SIZE_16K:
		psz = SZ_16K;
		अवरोध;
	हाल GIC_PAGE_SIZE_64K:
		psz = SZ_64K;
		अवरोध;
	पूर्ण

	/*
	 * Start populating the रेजिस्टर from scratch, including RO fields
	 * (which we want to prपूर्णांक in debug हालs...)
	 */
	val = 0;
	val |= FIELD_PREP(GICR_VPROPBASER_4_1_PAGE_SIZE, gpsz);
	val |= FIELD_PREP(GICR_VPROPBASER_4_1_ENTRY_SIZE, esz);

	/* How many entries per GIC page? */
	esz++;
	epp = psz / (esz * SZ_8);

	/*
	 * If we need more than just a single L1 page, flag the table
	 * as indirect and compute the number of required L1 pages.
	 */
	अगर (epp < ITS_MAX_VPEID) अणु
		पूर्णांक nl2;

		val |= GICR_VPROPBASER_4_1_INसूचीECT;

		/* Number of L2 pages required to cover the VPEID space */
		nl2 = DIV_ROUND_UP(ITS_MAX_VPEID, epp);

		/* Number of L1 pages to poपूर्णांक to the L2 pages */
		npg = DIV_ROUND_UP(nl2 * SZ_8, psz);
	पूर्ण अन्यथा अणु
		npg = 1;
	पूर्ण

	val |= FIELD_PREP(GICR_VPROPBASER_4_1_SIZE, npg - 1);

	/* Right, that's the number of CPU pages we need क्रम L1 */
	np = DIV_ROUND_UP(npg * psz, PAGE_SIZE);

	pr_debug("np = %d, npg = %lld, psz = %d, epp = %d, esz = %d\n",
		 np, npg, psz, epp, esz);
	page = alloc_pages(GFP_ATOMIC | __GFP_ZERO, get_order(np * PAGE_SIZE));
	अगर (!page)
		वापस -ENOMEM;

	gic_data_rdist()->vpe_l1_base = page_address(page);
	pa = virt_to_phys(page_address(page));
	WARN_ON(!IS_ALIGNED(pa, psz));

	val |= FIELD_PREP(GICR_VPROPBASER_4_1_ADDR, pa >> 12);
	val |= GICR_VPROPBASER_RaWb;
	val |= GICR_VPROPBASER_InnerShareable;
	val |= GICR_VPROPBASER_4_1_Z;
	val |= GICR_VPROPBASER_4_1_VALID;

out:
	gicr_ग_लिखो_vpropbaser(val, vlpi_base + GICR_VPROPBASER);
	cpumask_set_cpu(smp_processor_id(), gic_data_rdist()->vpe_table_mask);

	pr_debug("CPU%d: VPROPBASER = %llx %*pbl\n",
		 smp_processor_id(), val,
		 cpumask_pr_args(gic_data_rdist()->vpe_table_mask));

	वापस 0;
पूर्ण

अटल पूर्णांक its_alloc_collections(काष्ठा its_node *its)
अणु
	पूर्णांक i;

	its->collections = kसुस्मृति(nr_cpu_ids, माप(*its->collections),
				   GFP_KERNEL);
	अगर (!its->collections)
		वापस -ENOMEM;

	क्रम (i = 0; i < nr_cpu_ids; i++)
		its->collections[i].target_address = ~0ULL;

	वापस 0;
पूर्ण

अटल काष्ठा page *its_allocate_pending_table(gfp_t gfp_flags)
अणु
	काष्ठा page *pend_page;

	pend_page = alloc_pages(gfp_flags | __GFP_ZERO,
				get_order(LPI_PENDBASE_SZ));
	अगर (!pend_page)
		वापस शून्य;

	/* Make sure the GIC will observe the zero-ed page */
	gic_flush_dcache_to_poc(page_address(pend_page), LPI_PENDBASE_SZ);

	वापस pend_page;
पूर्ण

अटल व्योम its_मुक्त_pending_table(काष्ठा page *pt)
अणु
	मुक्त_pages((अचिन्हित दीर्घ)page_address(pt), get_order(LPI_PENDBASE_SZ));
पूर्ण

/*
 * Booting with kdump and LPIs enabled is generally fine. Any other
 * हाल is wrong in the असलence of firmware/EFI support.
 */
अटल bool enabled_lpis_allowed(व्योम)
अणु
	phys_addr_t addr;
	u64 val;

	/* Check whether the property table is in a reserved region */
	val = gicr_पढ़ो_propbaser(gic_data_rdist_rd_base() + GICR_PROPBASER);
	addr = val & GENMASK_ULL(51, 12);

	वापस gic_check_reserved_range(addr, LPI_PROPBASE_SZ);
पूर्ण

अटल पूर्णांक __init allocate_lpi_tables(व्योम)
अणु
	u64 val;
	पूर्णांक err, cpu;

	/*
	 * If LPIs are enabled जबतक we run this from the boot CPU,
	 * flag the RD tables as pre-allocated अगर the stars करो align.
	 */
	val = पढ़ोl_relaxed(gic_data_rdist_rd_base() + GICR_CTLR);
	अगर ((val & GICR_CTLR_ENABLE_LPIS) && enabled_lpis_allowed()) अणु
		gic_rdists->flags |= (RDIST_FLAGS_RD_TABLES_PREALLOCATED |
				      RDIST_FLAGS_PROPBASE_NEEDS_FLUSHING);
		pr_info("GICv3: Using preallocated redistributor tables\n");
	पूर्ण

	err = its_setup_lpi_prop_table();
	अगर (err)
		वापस err;

	/*
	 * We allocate all the pending tables anyway, as we may have a
	 * mix of RDs that have had LPIs enabled, and some that
	 * करोn't. We'll मुक्त the unused ones as each CPU comes online.
	 */
	क्रम_each_possible_cpu(cpu) अणु
		काष्ठा page *pend_page;

		pend_page = its_allocate_pending_table(GFP_NOWAIT);
		अगर (!pend_page) अणु
			pr_err("Failed to allocate PENDBASE for CPU%d\n", cpu);
			वापस -ENOMEM;
		पूर्ण

		gic_data_rdist_cpu(cpu)->pend_page = pend_page;
	पूर्ण

	वापस 0;
पूर्ण

अटल u64 its_clear_vpend_valid(व्योम __iomem *vlpi_base, u64 clr, u64 set)
अणु
	u32 count = 1000000;	/* 1s! */
	bool clean;
	u64 val;

	val = gicr_पढ़ो_vpendbaser(vlpi_base + GICR_VPENDBASER);
	val &= ~GICR_VPENDBASER_Valid;
	val &= ~clr;
	val |= set;
	gicr_ग_लिखो_vpendbaser(val, vlpi_base + GICR_VPENDBASER);

	करो अणु
		val = gicr_पढ़ो_vpendbaser(vlpi_base + GICR_VPENDBASER);
		clean = !(val & GICR_VPENDBASER_Dirty);
		अगर (!clean) अणु
			count--;
			cpu_relax();
			udelay(1);
		पूर्ण
	पूर्ण जबतक (!clean && count);

	अगर (unlikely(val & GICR_VPENDBASER_Dirty)) अणु
		pr_err_ratelimited("ITS virtual pending table not cleaning\n");
		val |= GICR_VPENDBASER_PendingLast;
	पूर्ण

	वापस val;
पूर्ण

अटल व्योम its_cpu_init_lpis(व्योम)
अणु
	व्योम __iomem *rbase = gic_data_rdist_rd_base();
	काष्ठा page *pend_page;
	phys_addr_t paddr;
	u64 val, पंचांगp;

	अगर (gic_data_rdist()->lpi_enabled)
		वापस;

	val = पढ़ोl_relaxed(rbase + GICR_CTLR);
	अगर ((gic_rdists->flags & RDIST_FLAGS_RD_TABLES_PREALLOCATED) &&
	    (val & GICR_CTLR_ENABLE_LPIS)) अणु
		/*
		 * Check that we get the same property table on all
		 * RDs. If we करोn't, this is hopeless.
		 */
		paddr = gicr_पढ़ो_propbaser(rbase + GICR_PROPBASER);
		paddr &= GENMASK_ULL(51, 12);
		अगर (WARN_ON(gic_rdists->prop_table_pa != paddr))
			add_taपूर्णांक(TAINT_CRAP, LOCKDEP_STILL_OK);

		paddr = gicr_पढ़ो_pendbaser(rbase + GICR_PENDBASER);
		paddr &= GENMASK_ULL(51, 16);

		WARN_ON(!gic_check_reserved_range(paddr, LPI_PENDBASE_SZ));
		its_मुक्त_pending_table(gic_data_rdist()->pend_page);
		gic_data_rdist()->pend_page = शून्य;

		जाओ out;
	पूर्ण

	pend_page = gic_data_rdist()->pend_page;
	paddr = page_to_phys(pend_page);
	WARN_ON(gic_reserve_range(paddr, LPI_PENDBASE_SZ));

	/* set PROPBASE */
	val = (gic_rdists->prop_table_pa |
	       GICR_PROPBASER_InnerShareable |
	       GICR_PROPBASER_RaWaWb |
	       ((LPI_NRBITS - 1) & GICR_PROPBASER_IDBITS_MASK));

	gicr_ग_लिखो_propbaser(val, rbase + GICR_PROPBASER);
	पंचांगp = gicr_पढ़ो_propbaser(rbase + GICR_PROPBASER);

	अगर ((पंचांगp ^ val) & GICR_PROPBASER_SHAREABILITY_MASK) अणु
		अगर (!(पंचांगp & GICR_PROPBASER_SHAREABILITY_MASK)) अणु
			/*
			 * The HW reports non-shareable, we must
			 * हटाओ the cacheability attributes as
			 * well.
			 */
			val &= ~(GICR_PROPBASER_SHAREABILITY_MASK |
				 GICR_PROPBASER_CACHEABILITY_MASK);
			val |= GICR_PROPBASER_nC;
			gicr_ग_लिखो_propbaser(val, rbase + GICR_PROPBASER);
		पूर्ण
		pr_info_once("GIC: using cache flushing for LPI property table\n");
		gic_rdists->flags |= RDIST_FLAGS_PROPBASE_NEEDS_FLUSHING;
	पूर्ण

	/* set PENDBASE */
	val = (page_to_phys(pend_page) |
	       GICR_PENDBASER_InnerShareable |
	       GICR_PENDBASER_RaWaWb);

	gicr_ग_लिखो_pendbaser(val, rbase + GICR_PENDBASER);
	पंचांगp = gicr_पढ़ो_pendbaser(rbase + GICR_PENDBASER);

	अगर (!(पंचांगp & GICR_PENDBASER_SHAREABILITY_MASK)) अणु
		/*
		 * The HW reports non-shareable, we must हटाओ the
		 * cacheability attributes as well.
		 */
		val &= ~(GICR_PENDBASER_SHAREABILITY_MASK |
			 GICR_PENDBASER_CACHEABILITY_MASK);
		val |= GICR_PENDBASER_nC;
		gicr_ग_लिखो_pendbaser(val, rbase + GICR_PENDBASER);
	पूर्ण

	/* Enable LPIs */
	val = पढ़ोl_relaxed(rbase + GICR_CTLR);
	val |= GICR_CTLR_ENABLE_LPIS;
	ग_लिखोl_relaxed(val, rbase + GICR_CTLR);

	अगर (gic_rdists->has_vlpis && !gic_rdists->has_rvpeid) अणु
		व्योम __iomem *vlpi_base = gic_data_rdist_vlpi_base();

		/*
		 * It's possible क्रम CPU to receive VLPIs beक्रमe it is
		 * scheduled as a vPE, especially क्रम the first CPU, and the
		 * VLPI with INTID larger than 2^(IDbits+1) will be considered
		 * as out of range and dropped by GIC.
		 * So we initialize IDbits to known value to aव्योम VLPI drop.
		 */
		val = (LPI_NRBITS - 1) & GICR_VPROPBASER_IDBITS_MASK;
		pr_debug("GICv4: CPU%d: Init IDbits to 0x%llx for GICR_VPROPBASER\n",
			smp_processor_id(), val);
		gicr_ग_लिखो_vpropbaser(val, vlpi_base + GICR_VPROPBASER);

		/*
		 * Also clear Valid bit of GICR_VPENDBASER, in हाल some
		 * ancient programming माला_लो left in and has possibility of
		 * corrupting memory.
		 */
		val = its_clear_vpend_valid(vlpi_base, 0, 0);
	पूर्ण

	अगर (allocate_vpe_l1_table()) अणु
		/*
		 * If the allocation has failed, we're in massive trouble.
		 * Disable direct injection, and pray that no VM was
		 * alपढ़ोy running...
		 */
		gic_rdists->has_rvpeid = false;
		gic_rdists->has_vlpis = false;
	पूर्ण

	/* Make sure the GIC has seen the above */
	dsb(sy);
out:
	gic_data_rdist()->lpi_enabled = true;
	pr_info("GICv3: CPU%d: using %s LPI pending table @%pa\n",
		smp_processor_id(),
		gic_data_rdist()->pend_page ? "allocated" : "reserved",
		&paddr);
पूर्ण

अटल व्योम its_cpu_init_collection(काष्ठा its_node *its)
अणु
	पूर्णांक cpu = smp_processor_id();
	u64 target;

	/* aव्योम cross node collections and its mapping */
	अगर (its->flags & ITS_FLAGS_WORKAROUND_CAVIUM_23144) अणु
		काष्ठा device_node *cpu_node;

		cpu_node = of_get_cpu_node(cpu, शून्य);
		अगर (its->numa_node != NUMA_NO_NODE &&
			its->numa_node != of_node_to_nid(cpu_node))
			वापस;
	पूर्ण

	/*
	 * We now have to bind each collection to its target
	 * redistributor.
	 */
	अगर (gic_पढ़ो_typer(its->base + GITS_TYPER) & GITS_TYPER_PTA) अणु
		/*
		 * This ITS wants the physical address of the
		 * redistributor.
		 */
		target = gic_data_rdist()->phys_base;
	पूर्ण अन्यथा अणु
		/* This ITS wants a linear CPU number. */
		target = gic_पढ़ो_typer(gic_data_rdist_rd_base() + GICR_TYPER);
		target = GICR_TYPER_CPU_NUMBER(target) << 16;
	पूर्ण

	/* Perक्रमm collection mapping */
	its->collections[cpu].target_address = target;
	its->collections[cpu].col_id = cpu;

	its_send_mapc(its, &its->collections[cpu], 1);
	its_send_invall(its, &its->collections[cpu]);
पूर्ण

अटल व्योम its_cpu_init_collections(व्योम)
अणु
	काष्ठा its_node *its;

	raw_spin_lock(&its_lock);

	list_क्रम_each_entry(its, &its_nodes, entry)
		its_cpu_init_collection(its);

	raw_spin_unlock(&its_lock);
पूर्ण

अटल काष्ठा its_device *its_find_device(काष्ठा its_node *its, u32 dev_id)
अणु
	काष्ठा its_device *its_dev = शून्य, *पंचांगp;
	अचिन्हित दीर्घ flags;

	raw_spin_lock_irqsave(&its->lock, flags);

	list_क्रम_each_entry(पंचांगp, &its->its_device_list, entry) अणु
		अगर (पंचांगp->device_id == dev_id) अणु
			its_dev = पंचांगp;
			अवरोध;
		पूर्ण
	पूर्ण

	raw_spin_unlock_irqrestore(&its->lock, flags);

	वापस its_dev;
पूर्ण

अटल काष्ठा its_baser *its_get_baser(काष्ठा its_node *its, u32 type)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < GITS_BASER_NR_REGS; i++) अणु
		अगर (GITS_BASER_TYPE(its->tables[i].val) == type)
			वापस &its->tables[i];
	पूर्ण

	वापस शून्य;
पूर्ण

अटल bool its_alloc_table_entry(काष्ठा its_node *its,
				  काष्ठा its_baser *baser, u32 id)
अणु
	काष्ठा page *page;
	u32 esz, idx;
	__le64 *table;

	/* Don't allow device id that exceeds single, flat table limit */
	esz = GITS_BASER_ENTRY_SIZE(baser->val);
	अगर (!(baser->val & GITS_BASER_INसूचीECT))
		वापस (id < (PAGE_ORDER_TO_SIZE(baser->order) / esz));

	/* Compute 1st level table index & check अगर that exceeds table limit */
	idx = id >> ilog2(baser->psz / esz);
	अगर (idx >= (PAGE_ORDER_TO_SIZE(baser->order) / GITS_LVL1_ENTRY_SIZE))
		वापस false;

	table = baser->base;

	/* Allocate memory क्रम 2nd level table */
	अगर (!table[idx]) अणु
		page = alloc_pages_node(its->numa_node, GFP_KERNEL | __GFP_ZERO,
					get_order(baser->psz));
		अगर (!page)
			वापस false;

		/* Flush Lvl2 table to PoC अगर hw करोesn't support coherency */
		अगर (!(baser->val & GITS_BASER_SHAREABILITY_MASK))
			gic_flush_dcache_to_poc(page_address(page), baser->psz);

		table[idx] = cpu_to_le64(page_to_phys(page) | GITS_BASER_VALID);

		/* Flush Lvl1 entry to PoC अगर hw करोesn't support coherency */
		अगर (!(baser->val & GITS_BASER_SHAREABILITY_MASK))
			gic_flush_dcache_to_poc(table + idx, GITS_LVL1_ENTRY_SIZE);

		/* Ensure updated table contents are visible to ITS hardware */
		dsb(sy);
	पूर्ण

	वापस true;
पूर्ण

अटल bool its_alloc_device_table(काष्ठा its_node *its, u32 dev_id)
अणु
	काष्ठा its_baser *baser;

	baser = its_get_baser(its, GITS_BASER_TYPE_DEVICE);

	/* Don't allow device id that exceeds ITS hardware limit */
	अगर (!baser)
		वापस (ilog2(dev_id) < device_ids(its));

	वापस its_alloc_table_entry(its, baser, dev_id);
पूर्ण

अटल bool its_alloc_vpe_table(u32 vpe_id)
अणु
	काष्ठा its_node *its;
	पूर्णांक cpu;

	/*
	 * Make sure the L2 tables are allocated on *all* v4 ITSs. We
	 * could try and only करो it on ITSs corresponding to devices
	 * that have पूर्णांकerrupts targeted at this VPE, but the
	 * complनिकासy becomes crazy (and you have tons of memory
	 * anyway, right?).
	 */
	list_क्रम_each_entry(its, &its_nodes, entry) अणु
		काष्ठा its_baser *baser;

		अगर (!is_v4(its))
			जारी;

		baser = its_get_baser(its, GITS_BASER_TYPE_VCPU);
		अगर (!baser)
			वापस false;

		अगर (!its_alloc_table_entry(its, baser, vpe_id))
			वापस false;
	पूर्ण

	/* Non v4.1? No need to iterate RDs and go back early. */
	अगर (!gic_rdists->has_rvpeid)
		वापस true;

	/*
	 * Make sure the L2 tables are allocated क्रम all copies of
	 * the L1 table on *all* v4.1 RDs.
	 */
	क्रम_each_possible_cpu(cpu) अणु
		अगर (!allocate_vpe_l2_table(cpu, vpe_id))
			वापस false;
	पूर्ण

	वापस true;
पूर्ण

अटल काष्ठा its_device *its_create_device(काष्ठा its_node *its, u32 dev_id,
					    पूर्णांक nvecs, bool alloc_lpis)
अणु
	काष्ठा its_device *dev;
	अचिन्हित दीर्घ *lpi_map = शून्य;
	अचिन्हित दीर्घ flags;
	u16 *col_map = शून्य;
	व्योम *itt;
	पूर्णांक lpi_base;
	पूर्णांक nr_lpis;
	पूर्णांक nr_ites;
	पूर्णांक sz;

	अगर (!its_alloc_device_table(its, dev_id))
		वापस शून्य;

	अगर (WARN_ON(!is_घातer_of_2(nvecs)))
		nvecs = roundup_घात_of_two(nvecs);

	dev = kzalloc(माप(*dev), GFP_KERNEL);
	/*
	 * Even अगर the device wants a single LPI, the ITT must be
	 * sized as a घातer of two (and you need at least one bit...).
	 */
	nr_ites = max(2, nvecs);
	sz = nr_ites * (FIELD_GET(GITS_TYPER_ITT_ENTRY_SIZE, its->typer) + 1);
	sz = max(sz, ITS_ITT_ALIGN) + ITS_ITT_ALIGN - 1;
	itt = kzalloc_node(sz, GFP_KERNEL, its->numa_node);
	अगर (alloc_lpis) अणु
		lpi_map = its_lpi_alloc(nvecs, &lpi_base, &nr_lpis);
		अगर (lpi_map)
			col_map = kसुस्मृति(nr_lpis, माप(*col_map),
					  GFP_KERNEL);
	पूर्ण अन्यथा अणु
		col_map = kसुस्मृति(nr_ites, माप(*col_map), GFP_KERNEL);
		nr_lpis = 0;
		lpi_base = 0;
	पूर्ण

	अगर (!dev || !itt ||  !col_map || (!lpi_map && alloc_lpis)) अणु
		kमुक्त(dev);
		kमुक्त(itt);
		kमुक्त(lpi_map);
		kमुक्त(col_map);
		वापस शून्य;
	पूर्ण

	gic_flush_dcache_to_poc(itt, sz);

	dev->its = its;
	dev->itt = itt;
	dev->nr_ites = nr_ites;
	dev->event_map.lpi_map = lpi_map;
	dev->event_map.col_map = col_map;
	dev->event_map.lpi_base = lpi_base;
	dev->event_map.nr_lpis = nr_lpis;
	raw_spin_lock_init(&dev->event_map.vlpi_lock);
	dev->device_id = dev_id;
	INIT_LIST_HEAD(&dev->entry);

	raw_spin_lock_irqsave(&its->lock, flags);
	list_add(&dev->entry, &its->its_device_list);
	raw_spin_unlock_irqrestore(&its->lock, flags);

	/* Map device to its ITT */
	its_send_mapd(dev, 1);

	वापस dev;
पूर्ण

अटल व्योम its_मुक्त_device(काष्ठा its_device *its_dev)
अणु
	अचिन्हित दीर्घ flags;

	raw_spin_lock_irqsave(&its_dev->its->lock, flags);
	list_del(&its_dev->entry);
	raw_spin_unlock_irqrestore(&its_dev->its->lock, flags);
	kमुक्त(its_dev->event_map.col_map);
	kमुक्त(its_dev->itt);
	kमुक्त(its_dev);
पूर्ण

अटल पूर्णांक its_alloc_device_irq(काष्ठा its_device *dev, पूर्णांक nvecs, irq_hw_number_t *hwirq)
अणु
	पूर्णांक idx;

	/* Find a मुक्त LPI region in lpi_map and allocate them. */
	idx = biपंचांगap_find_मुक्त_region(dev->event_map.lpi_map,
				      dev->event_map.nr_lpis,
				      get_count_order(nvecs));
	अगर (idx < 0)
		वापस -ENOSPC;

	*hwirq = dev->event_map.lpi_base + idx;

	वापस 0;
पूर्ण

अटल पूर्णांक its_msi_prepare(काष्ठा irq_करोमुख्य *करोमुख्य, काष्ठा device *dev,
			   पूर्णांक nvec, msi_alloc_info_t *info)
अणु
	काष्ठा its_node *its;
	काष्ठा its_device *its_dev;
	काष्ठा msi_करोमुख्य_info *msi_info;
	u32 dev_id;
	पूर्णांक err = 0;

	/*
	 * We ignore "dev" entirely, and rely on the dev_id that has
	 * been passed via the scratchpad. This limits this करोमुख्य's
	 * usefulness to upper layers that definitely know that they
	 * are built on top of the ITS.
	 */
	dev_id = info->scratchpad[0].ul;

	msi_info = msi_get_करोमुख्य_info(करोमुख्य);
	its = msi_info->data;

	अगर (!gic_rdists->has_direct_lpi &&
	    vpe_proxy.dev &&
	    vpe_proxy.dev->its == its &&
	    dev_id == vpe_proxy.dev->device_id) अणु
		/* Bad luck. Get yourself a better implementation */
		WARN_ONCE(1, "DevId %x clashes with GICv4 VPE proxy device\n",
			  dev_id);
		वापस -EINVAL;
	पूर्ण

	mutex_lock(&its->dev_alloc_lock);
	its_dev = its_find_device(its, dev_id);
	अगर (its_dev) अणु
		/*
		 * We alपढ़ोy have seen this ID, probably through
		 * another alias (PCI bridge of some sort). No need to
		 * create the device.
		 */
		its_dev->shared = true;
		pr_debug("Reusing ITT for devID %x\n", dev_id);
		जाओ out;
	पूर्ण

	its_dev = its_create_device(its, dev_id, nvec, true);
	अगर (!its_dev) अणु
		err = -ENOMEM;
		जाओ out;
	पूर्ण

	अगर (info->flags & MSI_ALLOC_FLAGS_PROXY_DEVICE)
		its_dev->shared = true;

	pr_debug("ITT %d entries, %d bits\n", nvec, ilog2(nvec));
out:
	mutex_unlock(&its->dev_alloc_lock);
	info->scratchpad[0].ptr = its_dev;
	वापस err;
पूर्ण

अटल काष्ठा msi_करोमुख्य_ops its_msi_करोमुख्य_ops = अणु
	.msi_prepare	= its_msi_prepare,
पूर्ण;

अटल पूर्णांक its_irq_gic_करोमुख्य_alloc(काष्ठा irq_करोमुख्य *करोमुख्य,
				    अचिन्हित पूर्णांक virq,
				    irq_hw_number_t hwirq)
अणु
	काष्ठा irq_fwspec fwspec;

	अगर (irq_करोमुख्य_get_of_node(करोमुख्य->parent)) अणु
		fwspec.fwnode = करोमुख्य->parent->fwnode;
		fwspec.param_count = 3;
		fwspec.param[0] = GIC_IRQ_TYPE_LPI;
		fwspec.param[1] = hwirq;
		fwspec.param[2] = IRQ_TYPE_EDGE_RISING;
	पूर्ण अन्यथा अगर (is_fwnode_irqchip(करोमुख्य->parent->fwnode)) अणु
		fwspec.fwnode = करोमुख्य->parent->fwnode;
		fwspec.param_count = 2;
		fwspec.param[0] = hwirq;
		fwspec.param[1] = IRQ_TYPE_EDGE_RISING;
	पूर्ण अन्यथा अणु
		वापस -EINVAL;
	पूर्ण

	वापस irq_करोमुख्य_alloc_irqs_parent(करोमुख्य, virq, 1, &fwspec);
पूर्ण

अटल पूर्णांक its_irq_करोमुख्य_alloc(काष्ठा irq_करोमुख्य *करोमुख्य, अचिन्हित पूर्णांक virq,
				अचिन्हित पूर्णांक nr_irqs, व्योम *args)
अणु
	msi_alloc_info_t *info = args;
	काष्ठा its_device *its_dev = info->scratchpad[0].ptr;
	काष्ठा its_node *its = its_dev->its;
	काष्ठा irq_data *irqd;
	irq_hw_number_t hwirq;
	पूर्णांक err;
	पूर्णांक i;

	err = its_alloc_device_irq(its_dev, nr_irqs, &hwirq);
	अगर (err)
		वापस err;

	err = iommu_dma_prepare_msi(info->desc, its->get_msi_base(its_dev));
	अगर (err)
		वापस err;

	क्रम (i = 0; i < nr_irqs; i++) अणु
		err = its_irq_gic_करोमुख्य_alloc(करोमुख्य, virq + i, hwirq + i);
		अगर (err)
			वापस err;

		irq_करोमुख्य_set_hwirq_and_chip(करोमुख्य, virq + i,
					      hwirq + i, &its_irq_chip, its_dev);
		irqd = irq_get_irq_data(virq + i);
		irqd_set_single_target(irqd);
		irqd_set_affinity_on_activate(irqd);
		pr_debug("ID:%d pID:%d vID:%d\n",
			 (पूर्णांक)(hwirq + i - its_dev->event_map.lpi_base),
			 (पूर्णांक)(hwirq + i), virq + i);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक its_irq_करोमुख्य_activate(काष्ठा irq_करोमुख्य *करोमुख्य,
				   काष्ठा irq_data *d, bool reserve)
अणु
	काष्ठा its_device *its_dev = irq_data_get_irq_chip_data(d);
	u32 event = its_get_event_id(d);
	पूर्णांक cpu;

	cpu = its_select_cpu(d, cpu_online_mask);
	अगर (cpu < 0 || cpu >= nr_cpu_ids)
		वापस -EINVAL;

	its_inc_lpi_count(d, cpu);
	its_dev->event_map.col_map[event] = cpu;
	irq_data_update_effective_affinity(d, cpumask_of(cpu));

	/* Map the GIC IRQ and event to the device */
	its_send_mapti(its_dev, d->hwirq, event);
	वापस 0;
पूर्ण

अटल व्योम its_irq_करोमुख्य_deactivate(काष्ठा irq_करोमुख्य *करोमुख्य,
				      काष्ठा irq_data *d)
अणु
	काष्ठा its_device *its_dev = irq_data_get_irq_chip_data(d);
	u32 event = its_get_event_id(d);

	its_dec_lpi_count(d, its_dev->event_map.col_map[event]);
	/* Stop the delivery of पूर्णांकerrupts */
	its_send_discard(its_dev, event);
पूर्ण

अटल व्योम its_irq_करोमुख्य_मुक्त(काष्ठा irq_करोमुख्य *करोमुख्य, अचिन्हित पूर्णांक virq,
				अचिन्हित पूर्णांक nr_irqs)
अणु
	काष्ठा irq_data *d = irq_करोमुख्य_get_irq_data(करोमुख्य, virq);
	काष्ठा its_device *its_dev = irq_data_get_irq_chip_data(d);
	काष्ठा its_node *its = its_dev->its;
	पूर्णांक i;

	biपंचांगap_release_region(its_dev->event_map.lpi_map,
			      its_get_event_id(irq_करोमुख्य_get_irq_data(करोमुख्य, virq)),
			      get_count_order(nr_irqs));

	क्रम (i = 0; i < nr_irqs; i++) अणु
		काष्ठा irq_data *data = irq_करोमुख्य_get_irq_data(करोमुख्य,
								virq + i);
		/* Nuke the entry in the करोमुख्य */
		irq_करोमुख्य_reset_irq_data(data);
	पूर्ण

	mutex_lock(&its->dev_alloc_lock);

	/*
	 * If all पूर्णांकerrupts have been मुक्तd, start mopping the
	 * न्यूनमान. This is conditioned on the device not being shared.
	 */
	अगर (!its_dev->shared &&
	    biपंचांगap_empty(its_dev->event_map.lpi_map,
			 its_dev->event_map.nr_lpis)) अणु
		its_lpi_मुक्त(its_dev->event_map.lpi_map,
			     its_dev->event_map.lpi_base,
			     its_dev->event_map.nr_lpis);

		/* Unmap device/itt */
		its_send_mapd(its_dev, 0);
		its_मुक्त_device(its_dev);
	पूर्ण

	mutex_unlock(&its->dev_alloc_lock);

	irq_करोमुख्य_मुक्त_irqs_parent(करोमुख्य, virq, nr_irqs);
पूर्ण

अटल स्थिर काष्ठा irq_करोमुख्य_ops its_करोमुख्य_ops = अणु
	.alloc			= its_irq_करोमुख्य_alloc,
	.मुक्त			= its_irq_करोमुख्य_मुक्त,
	.activate		= its_irq_करोमुख्य_activate,
	.deactivate		= its_irq_करोमुख्य_deactivate,
पूर्ण;

/*
 * This is insane.
 *
 * If a GICv4.0 करोesn't implement Direct LPIs (which is extremely
 * likely), the only way to perक्रमm an invalidate is to use a fake
 * device to issue an INV command, implying that the LPI has first
 * been mapped to some event on that device. Since this is not exactly
 * cheap, we try to keep that mapping around as दीर्घ as possible, and
 * only issue an UNMAP अगर we're लघु on available slots.
 *
 * Broken by design(पंचांग).
 *
 * GICv4.1, on the other hand, mandates that we're able to invalidate
 * by writing to a MMIO रेजिस्टर. It करोesn't implement the whole of
 * DirectLPI, but that's good enough. And most of the time, we don't
 * even have to invalidate anything, as the redistributor can be told
 * whether to generate a करोorbell or not (we thus leave it enabled,
 * always).
 */
अटल व्योम its_vpe_db_proxy_unmap_locked(काष्ठा its_vpe *vpe)
अणु
	/* GICv4.1 करोesn't use a proxy, so nothing to करो here */
	अगर (gic_rdists->has_rvpeid)
		वापस;

	/* Alपढ़ोy unmapped? */
	अगर (vpe->vpe_proxy_event == -1)
		वापस;

	its_send_discard(vpe_proxy.dev, vpe->vpe_proxy_event);
	vpe_proxy.vpes[vpe->vpe_proxy_event] = शून्य;

	/*
	 * We करोn't track empty slots at all, so let's move the
	 * next_victim poपूर्णांकer अगर we can quickly reuse that slot
	 * instead of nuking an existing entry. Not clear that this is
	 * always a win though, and this might just generate a ripple
	 * effect... Let's just hope VPEs don't migrate too often.
	 */
	अगर (vpe_proxy.vpes[vpe_proxy.next_victim])
		vpe_proxy.next_victim = vpe->vpe_proxy_event;

	vpe->vpe_proxy_event = -1;
पूर्ण

अटल व्योम its_vpe_db_proxy_unmap(काष्ठा its_vpe *vpe)
अणु
	/* GICv4.1 करोesn't use a proxy, so nothing to करो here */
	अगर (gic_rdists->has_rvpeid)
		वापस;

	अगर (!gic_rdists->has_direct_lpi) अणु
		अचिन्हित दीर्घ flags;

		raw_spin_lock_irqsave(&vpe_proxy.lock, flags);
		its_vpe_db_proxy_unmap_locked(vpe);
		raw_spin_unlock_irqrestore(&vpe_proxy.lock, flags);
	पूर्ण
पूर्ण

अटल व्योम its_vpe_db_proxy_map_locked(काष्ठा its_vpe *vpe)
अणु
	/* GICv4.1 करोesn't use a proxy, so nothing to करो here */
	अगर (gic_rdists->has_rvpeid)
		वापस;

	/* Alपढ़ोy mapped? */
	अगर (vpe->vpe_proxy_event != -1)
		वापस;

	/* This slot was alपढ़ोy allocated. Kick the other VPE out. */
	अगर (vpe_proxy.vpes[vpe_proxy.next_victim])
		its_vpe_db_proxy_unmap_locked(vpe_proxy.vpes[vpe_proxy.next_victim]);

	/* Map the new VPE instead */
	vpe_proxy.vpes[vpe_proxy.next_victim] = vpe;
	vpe->vpe_proxy_event = vpe_proxy.next_victim;
	vpe_proxy.next_victim = (vpe_proxy.next_victim + 1) % vpe_proxy.dev->nr_ites;

	vpe_proxy.dev->event_map.col_map[vpe->vpe_proxy_event] = vpe->col_idx;
	its_send_mapti(vpe_proxy.dev, vpe->vpe_db_lpi, vpe->vpe_proxy_event);
पूर्ण

अटल व्योम its_vpe_db_proxy_move(काष्ठा its_vpe *vpe, पूर्णांक from, पूर्णांक to)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा its_collection *target_col;

	/* GICv4.1 करोesn't use a proxy, so nothing to करो here */
	अगर (gic_rdists->has_rvpeid)
		वापस;

	अगर (gic_rdists->has_direct_lpi) अणु
		व्योम __iomem *rdbase;

		rdbase = per_cpu_ptr(gic_rdists->rdist, from)->rd_base;
		gic_ग_लिखो_lpir(vpe->vpe_db_lpi, rdbase + GICR_CLRLPIR);
		रुको_क्रम_syncr(rdbase);

		वापस;
	पूर्ण

	raw_spin_lock_irqsave(&vpe_proxy.lock, flags);

	its_vpe_db_proxy_map_locked(vpe);

	target_col = &vpe_proxy.dev->its->collections[to];
	its_send_movi(vpe_proxy.dev, target_col, vpe->vpe_proxy_event);
	vpe_proxy.dev->event_map.col_map[vpe->vpe_proxy_event] = to;

	raw_spin_unlock_irqrestore(&vpe_proxy.lock, flags);
पूर्ण

अटल पूर्णांक its_vpe_set_affinity(काष्ठा irq_data *d,
				स्थिर काष्ठा cpumask *mask_val,
				bool क्रमce)
अणु
	काष्ठा its_vpe *vpe = irq_data_get_irq_chip_data(d);
	पूर्णांक from, cpu = cpumask_first(mask_val);
	अचिन्हित दीर्घ flags;

	/*
	 * Changing affinity is mega expensive, so let's be as lazy as
	 * we can and only करो it अगर we really have to. Also, अगर mapped
	 * पूर्णांकo the proxy device, we need to move the करोorbell
	 * पूर्णांकerrupt to its new location.
	 *
	 * Another thing is that changing the affinity of a vPE affects
	 * *other पूर्णांकerrupts* such as all the vLPIs that are routed to
	 * this vPE. This means that the irq_desc lock is not enough to
	 * protect us, and that we must ensure nobody samples vpe->col_idx
	 * during the update, hence the lock below which must also be
	 * taken on any vLPI handling path that evaluates vpe->col_idx.
	 */
	from = vpe_to_cpuid_lock(vpe, &flags);
	अगर (from == cpu)
		जाओ out;

	vpe->col_idx = cpu;

	/*
	 * GICv4.1 allows us to skip VMOVP अगर moving to a cpu whose RD
	 * is sharing its VPE table with the current one.
	 */
	अगर (gic_data_rdist_cpu(cpu)->vpe_table_mask &&
	    cpumask_test_cpu(from, gic_data_rdist_cpu(cpu)->vpe_table_mask))
		जाओ out;

	its_send_vmovp(vpe);
	its_vpe_db_proxy_move(vpe, from, cpu);

out:
	irq_data_update_effective_affinity(d, cpumask_of(cpu));
	vpe_to_cpuid_unlock(vpe, flags);

	वापस IRQ_SET_MASK_OK_DONE;
पूर्ण

अटल व्योम its_रुको_vpt_parse_complete(व्योम)
अणु
	व्योम __iomem *vlpi_base = gic_data_rdist_vlpi_base();
	u64 val;

	अगर (!gic_rdists->has_vpend_valid_dirty)
		वापस;

	WARN_ON_ONCE(पढ़ोq_relaxed_poll_समयout_atomic(vlpi_base + GICR_VPENDBASER,
						       val,
						       !(val & GICR_VPENDBASER_Dirty),
						       1, 500));
पूर्ण

अटल व्योम its_vpe_schedule(काष्ठा its_vpe *vpe)
अणु
	व्योम __iomem *vlpi_base = gic_data_rdist_vlpi_base();
	u64 val;

	/* Schedule the VPE */
	val  = virt_to_phys(page_address(vpe->its_vm->vprop_page)) &
		GENMASK_ULL(51, 12);
	val |= (LPI_NRBITS - 1) & GICR_VPROPBASER_IDBITS_MASK;
	val |= GICR_VPROPBASER_RaWb;
	val |= GICR_VPROPBASER_InnerShareable;
	gicr_ग_लिखो_vpropbaser(val, vlpi_base + GICR_VPROPBASER);

	val  = virt_to_phys(page_address(vpe->vpt_page)) &
		GENMASK_ULL(51, 16);
	val |= GICR_VPENDBASER_RaWaWb;
	val |= GICR_VPENDBASER_InnerShareable;
	/*
	 * There is no good way of finding out अगर the pending table is
	 * empty as we can race against the करोorbell पूर्णांकerrupt very
	 * easily. So in the end, vpe->pending_last is only an
	 * indication that the vcpu has something pending, not one
	 * that the pending table is empty. A good implementation
	 * would be able to पढ़ो its coarse map pretty quickly anyway,
	 * making this a tolerable issue.
	 */
	val |= GICR_VPENDBASER_PendingLast;
	val |= vpe->idai ? GICR_VPENDBASER_IDAI : 0;
	val |= GICR_VPENDBASER_Valid;
	gicr_ग_लिखो_vpendbaser(val, vlpi_base + GICR_VPENDBASER);
पूर्ण

अटल व्योम its_vpe_deschedule(काष्ठा its_vpe *vpe)
अणु
	व्योम __iomem *vlpi_base = gic_data_rdist_vlpi_base();
	u64 val;

	val = its_clear_vpend_valid(vlpi_base, 0, 0);

	vpe->idai = !!(val & GICR_VPENDBASER_IDAI);
	vpe->pending_last = !!(val & GICR_VPENDBASER_PendingLast);
पूर्ण

अटल व्योम its_vpe_invall(काष्ठा its_vpe *vpe)
अणु
	काष्ठा its_node *its;

	list_क्रम_each_entry(its, &its_nodes, entry) अणु
		अगर (!is_v4(its))
			जारी;

		अगर (its_list_map && !vpe->its_vm->vlpi_count[its->list_nr])
			जारी;

		/*
		 * Sending a VINVALL to a single ITS is enough, as all
		 * we need is to reach the redistributors.
		 */
		its_send_vinvall(its, vpe);
		वापस;
	पूर्ण
पूर्ण

अटल पूर्णांक its_vpe_set_vcpu_affinity(काष्ठा irq_data *d, व्योम *vcpu_info)
अणु
	काष्ठा its_vpe *vpe = irq_data_get_irq_chip_data(d);
	काष्ठा its_cmd_info *info = vcpu_info;

	चयन (info->cmd_type) अणु
	हाल SCHEDULE_VPE:
		its_vpe_schedule(vpe);
		वापस 0;

	हाल DESCHEDULE_VPE:
		its_vpe_deschedule(vpe);
		वापस 0;

	हाल COMMIT_VPE:
		its_रुको_vpt_parse_complete();
		वापस 0;

	हाल INVALL_VPE:
		its_vpe_invall(vpe);
		वापस 0;

	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल व्योम its_vpe_send_cmd(काष्ठा its_vpe *vpe,
			     व्योम (*cmd)(काष्ठा its_device *, u32))
अणु
	अचिन्हित दीर्घ flags;

	raw_spin_lock_irqsave(&vpe_proxy.lock, flags);

	its_vpe_db_proxy_map_locked(vpe);
	cmd(vpe_proxy.dev, vpe->vpe_proxy_event);

	raw_spin_unlock_irqrestore(&vpe_proxy.lock, flags);
पूर्ण

अटल व्योम its_vpe_send_inv(काष्ठा irq_data *d)
अणु
	काष्ठा its_vpe *vpe = irq_data_get_irq_chip_data(d);

	अगर (gic_rdists->has_direct_lpi) अणु
		व्योम __iomem *rdbase;

		/* Target the redistributor this VPE is currently known on */
		raw_spin_lock(&gic_data_rdist_cpu(vpe->col_idx)->rd_lock);
		rdbase = per_cpu_ptr(gic_rdists->rdist, vpe->col_idx)->rd_base;
		gic_ग_लिखो_lpir(d->parent_data->hwirq, rdbase + GICR_INVLPIR);
		रुको_क्रम_syncr(rdbase);
		raw_spin_unlock(&gic_data_rdist_cpu(vpe->col_idx)->rd_lock);
	पूर्ण अन्यथा अणु
		its_vpe_send_cmd(vpe, its_send_inv);
	पूर्ण
पूर्ण

अटल व्योम its_vpe_mask_irq(काष्ठा irq_data *d)
अणु
	/*
	 * We need to unmask the LPI, which is described by the parent
	 * irq_data. Instead of calling पूर्णांकo the parent (which won't
	 * exactly करो the right thing, let's simply use the
	 * parent_data poपूर्णांकer. Yes, I'm naughty.
	 */
	lpi_ग_लिखो_config(d->parent_data, LPI_PROP_ENABLED, 0);
	its_vpe_send_inv(d);
पूर्ण

अटल व्योम its_vpe_unmask_irq(काष्ठा irq_data *d)
अणु
	/* Same hack as above... */
	lpi_ग_लिखो_config(d->parent_data, 0, LPI_PROP_ENABLED);
	its_vpe_send_inv(d);
पूर्ण

अटल पूर्णांक its_vpe_set_irqchip_state(काष्ठा irq_data *d,
				     क्रमागत irqchip_irq_state which,
				     bool state)
अणु
	काष्ठा its_vpe *vpe = irq_data_get_irq_chip_data(d);

	अगर (which != IRQCHIP_STATE_PENDING)
		वापस -EINVAL;

	अगर (gic_rdists->has_direct_lpi) अणु
		व्योम __iomem *rdbase;

		rdbase = per_cpu_ptr(gic_rdists->rdist, vpe->col_idx)->rd_base;
		अगर (state) अणु
			gic_ग_लिखो_lpir(vpe->vpe_db_lpi, rdbase + GICR_SETLPIR);
		पूर्ण अन्यथा अणु
			gic_ग_लिखो_lpir(vpe->vpe_db_lpi, rdbase + GICR_CLRLPIR);
			रुको_क्रम_syncr(rdbase);
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (state)
			its_vpe_send_cmd(vpe, its_send_पूर्णांक);
		अन्यथा
			its_vpe_send_cmd(vpe, its_send_clear);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक its_vpe_retrigger(काष्ठा irq_data *d)
अणु
	वापस !its_vpe_set_irqchip_state(d, IRQCHIP_STATE_PENDING, true);
पूर्ण

अटल काष्ठा irq_chip its_vpe_irq_chip = अणु
	.name			= "GICv4-vpe",
	.irq_mask		= its_vpe_mask_irq,
	.irq_unmask		= its_vpe_unmask_irq,
	.irq_eoi		= irq_chip_eoi_parent,
	.irq_set_affinity	= its_vpe_set_affinity,
	.irq_retrigger		= its_vpe_retrigger,
	.irq_set_irqchip_state	= its_vpe_set_irqchip_state,
	.irq_set_vcpu_affinity	= its_vpe_set_vcpu_affinity,
पूर्ण;

अटल काष्ठा its_node *find_4_1_its(व्योम)
अणु
	अटल काष्ठा its_node *its = शून्य;

	अगर (!its) अणु
		list_क्रम_each_entry(its, &its_nodes, entry) अणु
			अगर (is_v4_1(its))
				वापस its;
		पूर्ण

		/* Oops? */
		its = शून्य;
	पूर्ण

	वापस its;
पूर्ण

अटल व्योम its_vpe_4_1_send_inv(काष्ठा irq_data *d)
अणु
	काष्ठा its_vpe *vpe = irq_data_get_irq_chip_data(d);
	काष्ठा its_node *its;

	/*
	 * GICv4.1 wants करोorbells to be invalidated using the
	 * INVDB command in order to be broadcast to all RDs. Send
	 * it to the first valid ITS, and let the HW करो its magic.
	 */
	its = find_4_1_its();
	अगर (its)
		its_send_invdb(its, vpe);
पूर्ण

अटल व्योम its_vpe_4_1_mask_irq(काष्ठा irq_data *d)
अणु
	lpi_ग_लिखो_config(d->parent_data, LPI_PROP_ENABLED, 0);
	its_vpe_4_1_send_inv(d);
पूर्ण

अटल व्योम its_vpe_4_1_unmask_irq(काष्ठा irq_data *d)
अणु
	lpi_ग_लिखो_config(d->parent_data, 0, LPI_PROP_ENABLED);
	its_vpe_4_1_send_inv(d);
पूर्ण

अटल व्योम its_vpe_4_1_schedule(काष्ठा its_vpe *vpe,
				 काष्ठा its_cmd_info *info)
अणु
	व्योम __iomem *vlpi_base = gic_data_rdist_vlpi_base();
	u64 val = 0;

	/* Schedule the VPE */
	val |= GICR_VPENDBASER_Valid;
	val |= info->g0en ? GICR_VPENDBASER_4_1_VGRP0EN : 0;
	val |= info->g1en ? GICR_VPENDBASER_4_1_VGRP1EN : 0;
	val |= FIELD_PREP(GICR_VPENDBASER_4_1_VPEID, vpe->vpe_id);

	gicr_ग_लिखो_vpendbaser(val, vlpi_base + GICR_VPENDBASER);
पूर्ण

अटल व्योम its_vpe_4_1_deschedule(काष्ठा its_vpe *vpe,
				   काष्ठा its_cmd_info *info)
अणु
	व्योम __iomem *vlpi_base = gic_data_rdist_vlpi_base();
	u64 val;

	अगर (info->req_db) अणु
		अचिन्हित दीर्घ flags;

		/*
		 * vPE is going to block: make the vPE non-resident with
		 * PendingLast clear and DB set. The GIC guarantees that अगर
		 * we पढ़ो-back PendingLast clear, then a करोorbell will be
		 * delivered when an पूर्णांकerrupt comes.
		 *
		 * Note the locking to deal with the concurrent update of
		 * pending_last from the करोorbell पूर्णांकerrupt handler that can
		 * run concurrently.
		 */
		raw_spin_lock_irqsave(&vpe->vpe_lock, flags);
		val = its_clear_vpend_valid(vlpi_base,
					    GICR_VPENDBASER_PendingLast,
					    GICR_VPENDBASER_4_1_DB);
		vpe->pending_last = !!(val & GICR_VPENDBASER_PendingLast);
		raw_spin_unlock_irqrestore(&vpe->vpe_lock, flags);
	पूर्ण अन्यथा अणु
		/*
		 * We're not blocking, so just make the vPE non-resident
		 * with PendingLast set, indicating that we'll be back.
		 */
		val = its_clear_vpend_valid(vlpi_base,
					    0,
					    GICR_VPENDBASER_PendingLast);
		vpe->pending_last = true;
	पूर्ण
पूर्ण

अटल व्योम its_vpe_4_1_invall(काष्ठा its_vpe *vpe)
अणु
	व्योम __iomem *rdbase;
	अचिन्हित दीर्घ flags;
	u64 val;
	पूर्णांक cpu;

	val  = GICR_INVALLR_V;
	val |= FIELD_PREP(GICR_INVALLR_VPEID, vpe->vpe_id);

	/* Target the redistributor this vPE is currently known on */
	cpu = vpe_to_cpuid_lock(vpe, &flags);
	raw_spin_lock(&gic_data_rdist_cpu(cpu)->rd_lock);
	rdbase = per_cpu_ptr(gic_rdists->rdist, cpu)->rd_base;
	gic_ग_लिखो_lpir(val, rdbase + GICR_INVALLR);

	रुको_क्रम_syncr(rdbase);
	raw_spin_unlock(&gic_data_rdist_cpu(cpu)->rd_lock);
	vpe_to_cpuid_unlock(vpe, flags);
पूर्ण

अटल पूर्णांक its_vpe_4_1_set_vcpu_affinity(काष्ठा irq_data *d, व्योम *vcpu_info)
अणु
	काष्ठा its_vpe *vpe = irq_data_get_irq_chip_data(d);
	काष्ठा its_cmd_info *info = vcpu_info;

	चयन (info->cmd_type) अणु
	हाल SCHEDULE_VPE:
		its_vpe_4_1_schedule(vpe, info);
		वापस 0;

	हाल DESCHEDULE_VPE:
		its_vpe_4_1_deschedule(vpe, info);
		वापस 0;

	हाल COMMIT_VPE:
		its_रुको_vpt_parse_complete();
		वापस 0;

	हाल INVALL_VPE:
		its_vpe_4_1_invall(vpe);
		वापस 0;

	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल काष्ठा irq_chip its_vpe_4_1_irq_chip = अणु
	.name			= "GICv4.1-vpe",
	.irq_mask		= its_vpe_4_1_mask_irq,
	.irq_unmask		= its_vpe_4_1_unmask_irq,
	.irq_eoi		= irq_chip_eoi_parent,
	.irq_set_affinity	= its_vpe_set_affinity,
	.irq_set_vcpu_affinity	= its_vpe_4_1_set_vcpu_affinity,
पूर्ण;

अटल व्योम its_configure_sgi(काष्ठा irq_data *d, bool clear)
अणु
	काष्ठा its_vpe *vpe = irq_data_get_irq_chip_data(d);
	काष्ठा its_cmd_desc desc;

	desc.its_vsgi_cmd.vpe = vpe;
	desc.its_vsgi_cmd.sgi = d->hwirq;
	desc.its_vsgi_cmd.priority = vpe->sgi_config[d->hwirq].priority;
	desc.its_vsgi_cmd.enable = vpe->sgi_config[d->hwirq].enabled;
	desc.its_vsgi_cmd.group = vpe->sgi_config[d->hwirq].group;
	desc.its_vsgi_cmd.clear = clear;

	/*
	 * GICv4.1 allows us to send VSGI commands to any ITS as दीर्घ as the
	 * destination VPE is mapped there. Since we map them eagerly at
	 * activation समय, we're pretty sure the first GICv4.1 ITS will करो.
	 */
	its_send_single_vcommand(find_4_1_its(), its_build_vsgi_cmd, &desc);
पूर्ण

अटल व्योम its_sgi_mask_irq(काष्ठा irq_data *d)
अणु
	काष्ठा its_vpe *vpe = irq_data_get_irq_chip_data(d);

	vpe->sgi_config[d->hwirq].enabled = false;
	its_configure_sgi(d, false);
पूर्ण

अटल व्योम its_sgi_unmask_irq(काष्ठा irq_data *d)
अणु
	काष्ठा its_vpe *vpe = irq_data_get_irq_chip_data(d);

	vpe->sgi_config[d->hwirq].enabled = true;
	its_configure_sgi(d, false);
पूर्ण

अटल पूर्णांक its_sgi_set_affinity(काष्ठा irq_data *d,
				स्थिर काष्ठा cpumask *mask_val,
				bool क्रमce)
अणु
	/*
	 * There is no notion of affinity क्रम भव SGIs, at least
	 * not on the host (since they can only be targeting a vPE).
	 * Tell the kernel we've करोne whatever it asked क्रम.
	 */
	irq_data_update_effective_affinity(d, mask_val);
	वापस IRQ_SET_MASK_OK;
पूर्ण

अटल पूर्णांक its_sgi_set_irqchip_state(काष्ठा irq_data *d,
				     क्रमागत irqchip_irq_state which,
				     bool state)
अणु
	अगर (which != IRQCHIP_STATE_PENDING)
		वापस -EINVAL;

	अगर (state) अणु
		काष्ठा its_vpe *vpe = irq_data_get_irq_chip_data(d);
		काष्ठा its_node *its = find_4_1_its();
		u64 val;

		val  = FIELD_PREP(GITS_SGIR_VPEID, vpe->vpe_id);
		val |= FIELD_PREP(GITS_SGIR_VINTID, d->hwirq);
		ग_लिखोq_relaxed(val, its->sgir_base + GITS_SGIR - SZ_128K);
	पूर्ण अन्यथा अणु
		its_configure_sgi(d, true);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक its_sgi_get_irqchip_state(काष्ठा irq_data *d,
				     क्रमागत irqchip_irq_state which, bool *val)
अणु
	काष्ठा its_vpe *vpe = irq_data_get_irq_chip_data(d);
	व्योम __iomem *base;
	अचिन्हित दीर्घ flags;
	u32 count = 1000000;	/* 1s! */
	u32 status;
	पूर्णांक cpu;

	अगर (which != IRQCHIP_STATE_PENDING)
		वापस -EINVAL;

	/*
	 * Locking galore! We can race against two dअगरferent events:
	 *
	 * - Concurrent vPE affinity change: we must make sure it cannot
	 *   happen, or we'll talk to the wrong redistributor. This is
	 *   identical to what happens with vLPIs.
	 *
	 * - Concurrent VSGIPENDR access: As it involves accessing two
	 *   MMIO रेजिस्टरs, this must be made atomic one way or another.
	 */
	cpu = vpe_to_cpuid_lock(vpe, &flags);
	raw_spin_lock(&gic_data_rdist_cpu(cpu)->rd_lock);
	base = gic_data_rdist_cpu(cpu)->rd_base + SZ_128K;
	ग_लिखोl_relaxed(vpe->vpe_id, base + GICR_VSGIR);
	करो अणु
		status = पढ़ोl_relaxed(base + GICR_VSGIPENDR);
		अगर (!(status & GICR_VSGIPENDR_BUSY))
			जाओ out;

		count--;
		अगर (!count) अणु
			pr_err_ratelimited("Unable to get SGI status\n");
			जाओ out;
		पूर्ण
		cpu_relax();
		udelay(1);
	पूर्ण जबतक (count);

out:
	raw_spin_unlock(&gic_data_rdist_cpu(cpu)->rd_lock);
	vpe_to_cpuid_unlock(vpe, flags);

	अगर (!count)
		वापस -ENXIO;

	*val = !!(status & (1 << d->hwirq));

	वापस 0;
पूर्ण

अटल पूर्णांक its_sgi_set_vcpu_affinity(काष्ठा irq_data *d, व्योम *vcpu_info)
अणु
	काष्ठा its_vpe *vpe = irq_data_get_irq_chip_data(d);
	काष्ठा its_cmd_info *info = vcpu_info;

	चयन (info->cmd_type) अणु
	हाल PROP_UPDATE_VSGI:
		vpe->sgi_config[d->hwirq].priority = info->priority;
		vpe->sgi_config[d->hwirq].group = info->group;
		its_configure_sgi(d, false);
		वापस 0;

	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल काष्ठा irq_chip its_sgi_irq_chip = अणु
	.name			= "GICv4.1-sgi",
	.irq_mask		= its_sgi_mask_irq,
	.irq_unmask		= its_sgi_unmask_irq,
	.irq_set_affinity	= its_sgi_set_affinity,
	.irq_set_irqchip_state	= its_sgi_set_irqchip_state,
	.irq_get_irqchip_state	= its_sgi_get_irqchip_state,
	.irq_set_vcpu_affinity	= its_sgi_set_vcpu_affinity,
पूर्ण;

अटल पूर्णांक its_sgi_irq_करोमुख्य_alloc(काष्ठा irq_करोमुख्य *करोमुख्य,
				    अचिन्हित पूर्णांक virq, अचिन्हित पूर्णांक nr_irqs,
				    व्योम *args)
अणु
	काष्ठा its_vpe *vpe = args;
	पूर्णांक i;

	/* Yes, we करो want 16 SGIs */
	WARN_ON(nr_irqs != 16);

	क्रम (i = 0; i < 16; i++) अणु
		vpe->sgi_config[i].priority = 0;
		vpe->sgi_config[i].enabled = false;
		vpe->sgi_config[i].group = false;

		irq_करोमुख्य_set_hwirq_and_chip(करोमुख्य, virq + i, i,
					      &its_sgi_irq_chip, vpe);
		irq_set_status_flags(virq + i, IRQ_DISABLE_UNLAZY);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम its_sgi_irq_करोमुख्य_मुक्त(काष्ठा irq_करोमुख्य *करोमुख्य,
				    अचिन्हित पूर्णांक virq,
				    अचिन्हित पूर्णांक nr_irqs)
अणु
	/* Nothing to करो */
पूर्ण

अटल पूर्णांक its_sgi_irq_करोमुख्य_activate(काष्ठा irq_करोमुख्य *करोमुख्य,
				       काष्ठा irq_data *d, bool reserve)
अणु
	/* Write out the initial SGI configuration */
	its_configure_sgi(d, false);
	वापस 0;
पूर्ण

अटल व्योम its_sgi_irq_करोमुख्य_deactivate(काष्ठा irq_करोमुख्य *करोमुख्य,
					  काष्ठा irq_data *d)
अणु
	काष्ठा its_vpe *vpe = irq_data_get_irq_chip_data(d);

	/*
	 * The VSGI command is awkward:
	 *
	 * - To change the configuration, CLEAR must be set to false,
	 *   leaving the pending bit unchanged.
	 * - To clear the pending bit, CLEAR must be set to true, leaving
	 *   the configuration unchanged.
	 *
	 * You just can't करो both at once, hence the two commands below.
	 */
	vpe->sgi_config[d->hwirq].enabled = false;
	its_configure_sgi(d, false);
	its_configure_sgi(d, true);
पूर्ण

अटल स्थिर काष्ठा irq_करोमुख्य_ops its_sgi_करोमुख्य_ops = अणु
	.alloc		= its_sgi_irq_करोमुख्य_alloc,
	.मुक्त		= its_sgi_irq_करोमुख्य_मुक्त,
	.activate	= its_sgi_irq_करोमुख्य_activate,
	.deactivate	= its_sgi_irq_करोमुख्य_deactivate,
पूर्ण;

अटल पूर्णांक its_vpe_id_alloc(व्योम)
अणु
	वापस ida_simple_get(&its_vpeid_ida, 0, ITS_MAX_VPEID, GFP_KERNEL);
पूर्ण

अटल व्योम its_vpe_id_मुक्त(u16 id)
अणु
	ida_simple_हटाओ(&its_vpeid_ida, id);
पूर्ण

अटल पूर्णांक its_vpe_init(काष्ठा its_vpe *vpe)
अणु
	काष्ठा page *vpt_page;
	पूर्णांक vpe_id;

	/* Allocate vpe_id */
	vpe_id = its_vpe_id_alloc();
	अगर (vpe_id < 0)
		वापस vpe_id;

	/* Allocate VPT */
	vpt_page = its_allocate_pending_table(GFP_KERNEL);
	अगर (!vpt_page) अणु
		its_vpe_id_मुक्त(vpe_id);
		वापस -ENOMEM;
	पूर्ण

	अगर (!its_alloc_vpe_table(vpe_id)) अणु
		its_vpe_id_मुक्त(vpe_id);
		its_मुक्त_pending_table(vpt_page);
		वापस -ENOMEM;
	पूर्ण

	raw_spin_lock_init(&vpe->vpe_lock);
	vpe->vpe_id = vpe_id;
	vpe->vpt_page = vpt_page;
	अगर (gic_rdists->has_rvpeid)
		atomic_set(&vpe->vmapp_count, 0);
	अन्यथा
		vpe->vpe_proxy_event = -1;

	वापस 0;
पूर्ण

अटल व्योम its_vpe_tearकरोwn(काष्ठा its_vpe *vpe)
अणु
	its_vpe_db_proxy_unmap(vpe);
	its_vpe_id_मुक्त(vpe->vpe_id);
	its_मुक्त_pending_table(vpe->vpt_page);
पूर्ण

अटल व्योम its_vpe_irq_करोमुख्य_मुक्त(काष्ठा irq_करोमुख्य *करोमुख्य,
				    अचिन्हित पूर्णांक virq,
				    अचिन्हित पूर्णांक nr_irqs)
अणु
	काष्ठा its_vm *vm = करोमुख्य->host_data;
	पूर्णांक i;

	irq_करोमुख्य_मुक्त_irqs_parent(करोमुख्य, virq, nr_irqs);

	क्रम (i = 0; i < nr_irqs; i++) अणु
		काष्ठा irq_data *data = irq_करोमुख्य_get_irq_data(करोमुख्य,
								virq + i);
		काष्ठा its_vpe *vpe = irq_data_get_irq_chip_data(data);

		BUG_ON(vm != vpe->its_vm);

		clear_bit(data->hwirq, vm->db_biपंचांगap);
		its_vpe_tearकरोwn(vpe);
		irq_करोमुख्य_reset_irq_data(data);
	पूर्ण

	अगर (biपंचांगap_empty(vm->db_biपंचांगap, vm->nr_db_lpis)) अणु
		its_lpi_मुक्त(vm->db_biपंचांगap, vm->db_lpi_base, vm->nr_db_lpis);
		its_मुक्त_prop_table(vm->vprop_page);
	पूर्ण
पूर्ण

अटल पूर्णांक its_vpe_irq_करोमुख्य_alloc(काष्ठा irq_करोमुख्य *करोमुख्य, अचिन्हित पूर्णांक virq,
				    अचिन्हित पूर्णांक nr_irqs, व्योम *args)
अणु
	काष्ठा irq_chip *irqchip = &its_vpe_irq_chip;
	काष्ठा its_vm *vm = args;
	अचिन्हित दीर्घ *biपंचांगap;
	काष्ठा page *vprop_page;
	पूर्णांक base, nr_ids, i, err = 0;

	BUG_ON(!vm);

	biपंचांगap = its_lpi_alloc(roundup_घात_of_two(nr_irqs), &base, &nr_ids);
	अगर (!biपंचांगap)
		वापस -ENOMEM;

	अगर (nr_ids < nr_irqs) अणु
		its_lpi_मुक्त(biपंचांगap, base, nr_ids);
		वापस -ENOMEM;
	पूर्ण

	vprop_page = its_allocate_prop_table(GFP_KERNEL);
	अगर (!vprop_page) अणु
		its_lpi_मुक्त(biपंचांगap, base, nr_ids);
		वापस -ENOMEM;
	पूर्ण

	vm->db_biपंचांगap = biपंचांगap;
	vm->db_lpi_base = base;
	vm->nr_db_lpis = nr_ids;
	vm->vprop_page = vprop_page;

	अगर (gic_rdists->has_rvpeid)
		irqchip = &its_vpe_4_1_irq_chip;

	क्रम (i = 0; i < nr_irqs; i++) अणु
		vm->vpes[i]->vpe_db_lpi = base + i;
		err = its_vpe_init(vm->vpes[i]);
		अगर (err)
			अवरोध;
		err = its_irq_gic_करोमुख्य_alloc(करोमुख्य, virq + i,
					       vm->vpes[i]->vpe_db_lpi);
		अगर (err)
			अवरोध;
		irq_करोमुख्य_set_hwirq_and_chip(करोमुख्य, virq + i, i,
					      irqchip, vm->vpes[i]);
		set_bit(i, biपंचांगap);
	पूर्ण

	अगर (err) अणु
		अगर (i > 0)
			its_vpe_irq_करोमुख्य_मुक्त(करोमुख्य, virq, i - 1);

		its_lpi_मुक्त(biपंचांगap, base, nr_ids);
		its_मुक्त_prop_table(vprop_page);
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक its_vpe_irq_करोमुख्य_activate(काष्ठा irq_करोमुख्य *करोमुख्य,
				       काष्ठा irq_data *d, bool reserve)
अणु
	काष्ठा its_vpe *vpe = irq_data_get_irq_chip_data(d);
	काष्ठा its_node *its;

	/*
	 * If we use the list map, we issue VMAPP on demand... Unless
	 * we're on a GICv4.1 and we eagerly map the VPE on all ITSs
	 * so that VSGIs can work.
	 */
	अगर (!gic_requires_eager_mapping())
		वापस 0;

	/* Map the VPE to the first possible CPU */
	vpe->col_idx = cpumask_first(cpu_online_mask);

	list_क्रम_each_entry(its, &its_nodes, entry) अणु
		अगर (!is_v4(its))
			जारी;

		its_send_vmapp(its, vpe, true);
		its_send_vinvall(its, vpe);
	पूर्ण

	irq_data_update_effective_affinity(d, cpumask_of(vpe->col_idx));

	वापस 0;
पूर्ण

अटल व्योम its_vpe_irq_करोमुख्य_deactivate(काष्ठा irq_करोमुख्य *करोमुख्य,
					  काष्ठा irq_data *d)
अणु
	काष्ठा its_vpe *vpe = irq_data_get_irq_chip_data(d);
	काष्ठा its_node *its;

	/*
	 * If we use the list map on GICv4.0, we unmap the VPE once no
	 * VLPIs are associated with the VM.
	 */
	अगर (!gic_requires_eager_mapping())
		वापस;

	list_क्रम_each_entry(its, &its_nodes, entry) अणु
		अगर (!is_v4(its))
			जारी;

		its_send_vmapp(its, vpe, false);
	पूर्ण

	/*
	 * There may be a direct पढ़ो to the VPT after unmapping the
	 * vPE, to guarantee the validity of this, we make the VPT
	 * memory coherent with the CPU caches here.
	 */
	अगर (find_4_1_its() && !atomic_पढ़ो(&vpe->vmapp_count))
		gic_flush_dcache_to_poc(page_address(vpe->vpt_page),
					LPI_PENDBASE_SZ);
पूर्ण

अटल स्थिर काष्ठा irq_करोमुख्य_ops its_vpe_करोमुख्य_ops = अणु
	.alloc			= its_vpe_irq_करोमुख्य_alloc,
	.मुक्त			= its_vpe_irq_करोमुख्य_मुक्त,
	.activate		= its_vpe_irq_करोमुख्य_activate,
	.deactivate		= its_vpe_irq_करोमुख्य_deactivate,
पूर्ण;

अटल पूर्णांक its_क्रमce_quiescent(व्योम __iomem *base)
अणु
	u32 count = 1000000;	/* 1s */
	u32 val;

	val = पढ़ोl_relaxed(base + GITS_CTLR);
	/*
	 * GIC architecture specअगरication requires the ITS to be both
	 * disabled and quiescent क्रम ग_लिखोs to GITS_BASER<n> or
	 * GITS_CBASER to not have UNPREDICTABLE results.
	 */
	अगर ((val & GITS_CTLR_QUIESCENT) && !(val & GITS_CTLR_ENABLE))
		वापस 0;

	/* Disable the generation of all पूर्णांकerrupts to this ITS */
	val &= ~(GITS_CTLR_ENABLE | GITS_CTLR_ImDe);
	ग_लिखोl_relaxed(val, base + GITS_CTLR);

	/* Poll GITS_CTLR and रुको until ITS becomes quiescent */
	जबतक (1) अणु
		val = पढ़ोl_relaxed(base + GITS_CTLR);
		अगर (val & GITS_CTLR_QUIESCENT)
			वापस 0;

		count--;
		अगर (!count)
			वापस -EBUSY;

		cpu_relax();
		udelay(1);
	पूर्ण
पूर्ण

अटल bool __maybe_unused its_enable_quirk_cavium_22375(व्योम *data)
अणु
	काष्ठा its_node *its = data;

	/* erratum 22375: only alloc 8MB table size (20 bits) */
	its->typer &= ~GITS_TYPER_DEVBITS;
	its->typer |= FIELD_PREP(GITS_TYPER_DEVBITS, 20 - 1);
	its->flags |= ITS_FLAGS_WORKAROUND_CAVIUM_22375;

	वापस true;
पूर्ण

अटल bool __maybe_unused its_enable_quirk_cavium_23144(व्योम *data)
अणु
	काष्ठा its_node *its = data;

	its->flags |= ITS_FLAGS_WORKAROUND_CAVIUM_23144;

	वापस true;
पूर्ण

अटल bool __maybe_unused its_enable_quirk_qdf2400_e0065(व्योम *data)
अणु
	काष्ठा its_node *its = data;

	/* On QDF2400, the size of the ITE is 16Bytes */
	its->typer &= ~GITS_TYPER_ITT_ENTRY_SIZE;
	its->typer |= FIELD_PREP(GITS_TYPER_ITT_ENTRY_SIZE, 16 - 1);

	वापस true;
पूर्ण

अटल u64 its_irq_get_msi_base_pre_its(काष्ठा its_device *its_dev)
अणु
	काष्ठा its_node *its = its_dev->its;

	/*
	 * The Socionext Synquacer SoC has a so-called 'pre-ITS',
	 * which maps 32-bit ग_लिखोs targeted at a separate winकरोw of
	 * size '4 << device_id_bits' onto ग_लिखोs to GITS_TRANSLATER
	 * with device ID taken from bits [device_id_bits + 1:2] of
	 * the winकरोw offset.
	 */
	वापस its->pre_its_base + (its_dev->device_id << 2);
पूर्ण

अटल bool __maybe_unused its_enable_quirk_socionext_synquacer(व्योम *data)
अणु
	काष्ठा its_node *its = data;
	u32 pre_its_winकरोw[2];
	u32 ids;

	अगर (!fwnode_property_पढ़ो_u32_array(its->fwnode_handle,
					   "socionext,synquacer-pre-its",
					   pre_its_winकरोw,
					   ARRAY_SIZE(pre_its_winकरोw))) अणु

		its->pre_its_base = pre_its_winकरोw[0];
		its->get_msi_base = its_irq_get_msi_base_pre_its;

		ids = ilog2(pre_its_winकरोw[1]) - 2;
		अगर (device_ids(its) > ids) अणु
			its->typer &= ~GITS_TYPER_DEVBITS;
			its->typer |= FIELD_PREP(GITS_TYPER_DEVBITS, ids - 1);
		पूर्ण

		/* the pre-ITS अवरोधs isolation, so disable MSI remapping */
		its->msi_करोमुख्य_flags &= ~IRQ_DOMAIN_FLAG_MSI_REMAP;
		वापस true;
	पूर्ण
	वापस false;
पूर्ण

अटल bool __maybe_unused its_enable_quirk_hip07_161600802(व्योम *data)
अणु
	काष्ठा its_node *its = data;

	/*
	 * Hip07 insists on using the wrong address क्रम the VLPI
	 * page. Trick it पूर्णांकo करोing the right thing...
	 */
	its->vlpi_redist_offset = SZ_128K;
	वापस true;
पूर्ण

अटल स्थिर काष्ठा gic_quirk its_quirks[] = अणु
#अगर_घोषित CONFIG_CAVIUM_ERRATUM_22375
	अणु
		.desc	= "ITS: Cavium errata 22375, 24313",
		.iidr	= 0xa100034c,	/* ThunderX pass 1.x */
		.mask	= 0xffff0fff,
		.init	= its_enable_quirk_cavium_22375,
	पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_CAVIUM_ERRATUM_23144
	अणु
		.desc	= "ITS: Cavium erratum 23144",
		.iidr	= 0xa100034c,	/* ThunderX pass 1.x */
		.mask	= 0xffff0fff,
		.init	= its_enable_quirk_cavium_23144,
	पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_QCOM_QDF2400_ERRATUM_0065
	अणु
		.desc	= "ITS: QDF2400 erratum 0065",
		.iidr	= 0x00001070, /* QDF2400 ITS rev 1.x */
		.mask	= 0xffffffff,
		.init	= its_enable_quirk_qdf2400_e0065,
	पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_SOCIONEXT_SYNQUACER_PREITS
	अणु
		/*
		 * The Socionext Synquacer SoC incorporates ARM's own GIC-500
		 * implementation, but with a 'pre-ITS' added that requires
		 * special handling in software.
		 */
		.desc	= "ITS: Socionext Synquacer pre-ITS",
		.iidr	= 0x0001143b,
		.mask	= 0xffffffff,
		.init	= its_enable_quirk_socionext_synquacer,
	पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_HISILICON_ERRATUM_161600802
	अणु
		.desc	= "ITS: Hip07 erratum 161600802",
		.iidr	= 0x00000004,
		.mask	= 0xffffffff,
		.init	= its_enable_quirk_hip07_161600802,
	पूर्ण,
#पूर्ण_अगर
	अणु
	पूर्ण
पूर्ण;

अटल व्योम its_enable_quirks(काष्ठा its_node *its)
अणु
	u32 iidr = पढ़ोl_relaxed(its->base + GITS_IIDR);

	gic_enable_quirks(iidr, its_quirks, its);
पूर्ण

अटल पूर्णांक its_save_disable(व्योम)
अणु
	काष्ठा its_node *its;
	पूर्णांक err = 0;

	raw_spin_lock(&its_lock);
	list_क्रम_each_entry(its, &its_nodes, entry) अणु
		व्योम __iomem *base;

		base = its->base;
		its->ctlr_save = पढ़ोl_relaxed(base + GITS_CTLR);
		err = its_क्रमce_quiescent(base);
		अगर (err) अणु
			pr_err("ITS@%pa: failed to quiesce: %d\n",
			       &its->phys_base, err);
			ग_लिखोl_relaxed(its->ctlr_save, base + GITS_CTLR);
			जाओ err;
		पूर्ण

		its->cbaser_save = gits_पढ़ो_cbaser(base + GITS_CBASER);
	पूर्ण

err:
	अगर (err) अणु
		list_क्रम_each_entry_जारी_reverse(its, &its_nodes, entry) अणु
			व्योम __iomem *base;

			base = its->base;
			ग_लिखोl_relaxed(its->ctlr_save, base + GITS_CTLR);
		पूर्ण
	पूर्ण
	raw_spin_unlock(&its_lock);

	वापस err;
पूर्ण

अटल व्योम its_restore_enable(व्योम)
अणु
	काष्ठा its_node *its;
	पूर्णांक ret;

	raw_spin_lock(&its_lock);
	list_क्रम_each_entry(its, &its_nodes, entry) अणु
		व्योम __iomem *base;
		पूर्णांक i;

		base = its->base;

		/*
		 * Make sure that the ITS is disabled. If it fails to quiesce,
		 * करोn't restore it since writing to CBASER or BASER<n>
		 * रेजिस्टरs is undefined according to the GIC v3 ITS
		 * Specअगरication.
		 *
		 * Firmware resuming with the ITS enabled is terminally broken.
		 */
		WARN_ON(पढ़ोl_relaxed(base + GITS_CTLR) & GITS_CTLR_ENABLE);
		ret = its_क्रमce_quiescent(base);
		अगर (ret) अणु
			pr_err("ITS@%pa: failed to quiesce on resume: %d\n",
			       &its->phys_base, ret);
			जारी;
		पूर्ण

		gits_ग_लिखो_cbaser(its->cbaser_save, base + GITS_CBASER);

		/*
		 * Writing CBASER resets CREADR to 0, so make CWRITER and
		 * cmd_ग_लिखो line up with it.
		 */
		its->cmd_ग_लिखो = its->cmd_base;
		gits_ग_लिखो_cग_लिखोr(0, base + GITS_CWRITER);

		/* Restore GITS_BASER from the value cache. */
		क्रम (i = 0; i < GITS_BASER_NR_REGS; i++) अणु
			काष्ठा its_baser *baser = &its->tables[i];

			अगर (!(baser->val & GITS_BASER_VALID))
				जारी;

			its_ग_लिखो_baser(its, baser, baser->val);
		पूर्ण
		ग_लिखोl_relaxed(its->ctlr_save, base + GITS_CTLR);

		/*
		 * Reinit the collection अगर it's stored in the ITS. This is
		 * indicated by the col_id being less than the HCC field.
		 * CID < HCC as specअगरied in the GIC v3 Documentation.
		 */
		अगर (its->collections[smp_processor_id()].col_id <
		    GITS_TYPER_HCC(gic_पढ़ो_typer(base + GITS_TYPER)))
			its_cpu_init_collection(its);
	पूर्ण
	raw_spin_unlock(&its_lock);
पूर्ण

अटल काष्ठा syscore_ops its_syscore_ops = अणु
	.suspend = its_save_disable,
	.resume = its_restore_enable,
पूर्ण;

अटल पूर्णांक its_init_करोमुख्य(काष्ठा fwnode_handle *handle, काष्ठा its_node *its)
अणु
	काष्ठा irq_करोमुख्य *inner_करोमुख्य;
	काष्ठा msi_करोमुख्य_info *info;

	info = kzalloc(माप(*info), GFP_KERNEL);
	अगर (!info)
		वापस -ENOMEM;

	inner_करोमुख्य = irq_करोमुख्य_create_tree(handle, &its_करोमुख्य_ops, its);
	अगर (!inner_करोमुख्य) अणु
		kमुक्त(info);
		वापस -ENOMEM;
	पूर्ण

	inner_करोमुख्य->parent = its_parent;
	irq_करोमुख्य_update_bus_token(inner_करोमुख्य, DOMAIN_BUS_NEXUS);
	inner_करोमुख्य->flags |= its->msi_करोमुख्य_flags;
	info->ops = &its_msi_करोमुख्य_ops;
	info->data = its;
	inner_करोमुख्य->host_data = info;

	वापस 0;
पूर्ण

अटल पूर्णांक its_init_vpe_करोमुख्य(व्योम)
अणु
	काष्ठा its_node *its;
	u32 devid;
	पूर्णांक entries;

	अगर (gic_rdists->has_direct_lpi) अणु
		pr_info("ITS: Using DirectLPI for VPE invalidation\n");
		वापस 0;
	पूर्ण

	/* Any ITS will करो, even अगर not v4 */
	its = list_first_entry(&its_nodes, काष्ठा its_node, entry);

	entries = roundup_घात_of_two(nr_cpu_ids);
	vpe_proxy.vpes = kसुस्मृति(entries, माप(*vpe_proxy.vpes),
				 GFP_KERNEL);
	अगर (!vpe_proxy.vpes) अणु
		pr_err("ITS: Can't allocate GICv4 proxy device array\n");
		वापस -ENOMEM;
	पूर्ण

	/* Use the last possible DevID */
	devid = GENMASK(device_ids(its) - 1, 0);
	vpe_proxy.dev = its_create_device(its, devid, entries, false);
	अगर (!vpe_proxy.dev) अणु
		kमुक्त(vpe_proxy.vpes);
		pr_err("ITS: Can't allocate GICv4 proxy device\n");
		वापस -ENOMEM;
	पूर्ण

	BUG_ON(entries > vpe_proxy.dev->nr_ites);

	raw_spin_lock_init(&vpe_proxy.lock);
	vpe_proxy.next_victim = 0;
	pr_info("ITS: Allocated DevID %x as GICv4 proxy device (%d slots)\n",
		devid, vpe_proxy.dev->nr_ites);

	वापस 0;
पूर्ण

अटल पूर्णांक __init its_compute_its_list_map(काष्ठा resource *res,
					   व्योम __iomem *its_base)
अणु
	पूर्णांक its_number;
	u32 ctlr;

	/*
	 * This is assumed to be करोne early enough that we're
	 * guaranteed to be single-thपढ़ोed, hence no
	 * locking. Should this change, we should address
	 * this.
	 */
	its_number = find_first_zero_bit(&its_list_map, GICv4_ITS_LIST_MAX);
	अगर (its_number >= GICv4_ITS_LIST_MAX) अणु
		pr_err("ITS@%pa: No ITSList entry available!\n",
		       &res->start);
		वापस -EINVAL;
	पूर्ण

	ctlr = पढ़ोl_relaxed(its_base + GITS_CTLR);
	ctlr &= ~GITS_CTLR_ITS_NUMBER;
	ctlr |= its_number << GITS_CTLR_ITS_NUMBER_SHIFT;
	ग_लिखोl_relaxed(ctlr, its_base + GITS_CTLR);
	ctlr = पढ़ोl_relaxed(its_base + GITS_CTLR);
	अगर ((ctlr & GITS_CTLR_ITS_NUMBER) != (its_number << GITS_CTLR_ITS_NUMBER_SHIFT)) अणु
		its_number = ctlr & GITS_CTLR_ITS_NUMBER;
		its_number >>= GITS_CTLR_ITS_NUMBER_SHIFT;
	पूर्ण

	अगर (test_and_set_bit(its_number, &its_list_map)) अणु
		pr_err("ITS@%pa: Duplicate ITSList entry %d\n",
		       &res->start, its_number);
		वापस -EINVAL;
	पूर्ण

	वापस its_number;
पूर्ण

अटल पूर्णांक __init its_probe_one(काष्ठा resource *res,
				काष्ठा fwnode_handle *handle, पूर्णांक numa_node)
अणु
	काष्ठा its_node *its;
	व्योम __iomem *its_base;
	u32 val, ctlr;
	u64 baser, पंचांगp, typer;
	काष्ठा page *page;
	पूर्णांक err;

	its_base = ioremap(res->start, SZ_64K);
	अगर (!its_base) अणु
		pr_warn("ITS@%pa: Unable to map ITS registers\n", &res->start);
		वापस -ENOMEM;
	पूर्ण

	val = पढ़ोl_relaxed(its_base + GITS_PIDR2) & GIC_PIDR2_ARCH_MASK;
	अगर (val != 0x30 && val != 0x40) अणु
		pr_warn("ITS@%pa: No ITS detected, giving up\n", &res->start);
		err = -ENODEV;
		जाओ out_unmap;
	पूर्ण

	err = its_क्रमce_quiescent(its_base);
	अगर (err) अणु
		pr_warn("ITS@%pa: Failed to quiesce, giving up\n", &res->start);
		जाओ out_unmap;
	पूर्ण

	pr_info("ITS %pR\n", res);

	its = kzalloc(माप(*its), GFP_KERNEL);
	अगर (!its) अणु
		err = -ENOMEM;
		जाओ out_unmap;
	पूर्ण

	raw_spin_lock_init(&its->lock);
	mutex_init(&its->dev_alloc_lock);
	INIT_LIST_HEAD(&its->entry);
	INIT_LIST_HEAD(&its->its_device_list);
	typer = gic_पढ़ो_typer(its_base + GITS_TYPER);
	its->typer = typer;
	its->base = its_base;
	its->phys_base = res->start;
	अगर (is_v4(its)) अणु
		अगर (!(typer & GITS_TYPER_VMOVP)) अणु
			err = its_compute_its_list_map(res, its_base);
			अगर (err < 0)
				जाओ out_मुक्त_its;

			its->list_nr = err;

			pr_info("ITS@%pa: Using ITS number %d\n",
				&res->start, err);
		पूर्ण अन्यथा अणु
			pr_info("ITS@%pa: Single VMOVP capable\n", &res->start);
		पूर्ण

		अगर (is_v4_1(its)) अणु
			u32 svpet = FIELD_GET(GITS_TYPER_SVPET, typer);

			its->sgir_base = ioremap(res->start + SZ_128K, SZ_64K);
			अगर (!its->sgir_base) अणु
				err = -ENOMEM;
				जाओ out_मुक्त_its;
			पूर्ण

			its->mpidr = पढ़ोl_relaxed(its_base + GITS_MPIDR);

			pr_info("ITS@%pa: Using GICv4.1 mode %08x %08x\n",
				&res->start, its->mpidr, svpet);
		पूर्ण
	पूर्ण

	its->numa_node = numa_node;

	page = alloc_pages_node(its->numa_node, GFP_KERNEL | __GFP_ZERO,
				get_order(ITS_CMD_QUEUE_SZ));
	अगर (!page) अणु
		err = -ENOMEM;
		जाओ out_unmap_sgir;
	पूर्ण
	its->cmd_base = (व्योम *)page_address(page);
	its->cmd_ग_लिखो = its->cmd_base;
	its->fwnode_handle = handle;
	its->get_msi_base = its_irq_get_msi_base;
	its->msi_करोमुख्य_flags = IRQ_DOMAIN_FLAG_MSI_REMAP;

	its_enable_quirks(its);

	err = its_alloc_tables(its);
	अगर (err)
		जाओ out_मुक्त_cmd;

	err = its_alloc_collections(its);
	अगर (err)
		जाओ out_मुक्त_tables;

	baser = (virt_to_phys(its->cmd_base)	|
		 GITS_CBASER_RaWaWb		|
		 GITS_CBASER_InnerShareable	|
		 (ITS_CMD_QUEUE_SZ / SZ_4K - 1)	|
		 GITS_CBASER_VALID);

	gits_ग_लिखो_cbaser(baser, its->base + GITS_CBASER);
	पंचांगp = gits_पढ़ो_cbaser(its->base + GITS_CBASER);

	अगर ((पंचांगp ^ baser) & GITS_CBASER_SHAREABILITY_MASK) अणु
		अगर (!(पंचांगp & GITS_CBASER_SHAREABILITY_MASK)) अणु
			/*
			 * The HW reports non-shareable, we must
			 * हटाओ the cacheability attributes as
			 * well.
			 */
			baser &= ~(GITS_CBASER_SHAREABILITY_MASK |
				   GITS_CBASER_CACHEABILITY_MASK);
			baser |= GITS_CBASER_nC;
			gits_ग_लिखो_cbaser(baser, its->base + GITS_CBASER);
		पूर्ण
		pr_info("ITS: using cache flushing for cmd queue\n");
		its->flags |= ITS_FLAGS_CMDQ_NEEDS_FLUSHING;
	पूर्ण

	gits_ग_लिखो_cग_लिखोr(0, its->base + GITS_CWRITER);
	ctlr = पढ़ोl_relaxed(its->base + GITS_CTLR);
	ctlr |= GITS_CTLR_ENABLE;
	अगर (is_v4(its))
		ctlr |= GITS_CTLR_ImDe;
	ग_लिखोl_relaxed(ctlr, its->base + GITS_CTLR);

	err = its_init_करोमुख्य(handle, its);
	अगर (err)
		जाओ out_मुक्त_tables;

	raw_spin_lock(&its_lock);
	list_add(&its->entry, &its_nodes);
	raw_spin_unlock(&its_lock);

	वापस 0;

out_मुक्त_tables:
	its_मुक्त_tables(its);
out_मुक्त_cmd:
	मुक्त_pages((अचिन्हित दीर्घ)its->cmd_base, get_order(ITS_CMD_QUEUE_SZ));
out_unmap_sgir:
	अगर (its->sgir_base)
		iounmap(its->sgir_base);
out_मुक्त_its:
	kमुक्त(its);
out_unmap:
	iounmap(its_base);
	pr_err("ITS@%pa: failed probing (%d)\n", &res->start, err);
	वापस err;
पूर्ण

अटल bool gic_rdists_supports_plpis(व्योम)
अणु
	वापस !!(gic_पढ़ो_typer(gic_data_rdist_rd_base() + GICR_TYPER) & GICR_TYPER_PLPIS);
पूर्ण

अटल पूर्णांक redist_disable_lpis(व्योम)
अणु
	व्योम __iomem *rbase = gic_data_rdist_rd_base();
	u64 समयout = USEC_PER_SEC;
	u64 val;

	अगर (!gic_rdists_supports_plpis()) अणु
		pr_info("CPU%d: LPIs not supported\n", smp_processor_id());
		वापस -ENXIO;
	पूर्ण

	val = पढ़ोl_relaxed(rbase + GICR_CTLR);
	अगर (!(val & GICR_CTLR_ENABLE_LPIS))
		वापस 0;

	/*
	 * If coming via a CPU hotplug event, we करोn't need to disable
	 * LPIs beक्रमe trying to re-enable them. They are alपढ़ोy
	 * configured and all is well in the world.
	 *
	 * If running with pपुनः_स्मृतिated tables, there is nothing to करो.
	 */
	अगर (gic_data_rdist()->lpi_enabled ||
	    (gic_rdists->flags & RDIST_FLAGS_RD_TABLES_PREALLOCATED))
		वापस 0;

	/*
	 * From that poपूर्णांक on, we only try to करो some damage control.
	 */
	pr_warn("GICv3: CPU%d: Booted with LPIs enabled, memory probably corrupted\n",
		smp_processor_id());
	add_taपूर्णांक(TAINT_CRAP, LOCKDEP_STILL_OK);

	/* Disable LPIs */
	val &= ~GICR_CTLR_ENABLE_LPIS;
	ग_लिखोl_relaxed(val, rbase + GICR_CTLR);

	/* Make sure any change to GICR_CTLR is observable by the GIC */
	dsb(sy);

	/*
	 * Software must observe RWP==0 after clearing GICR_CTLR.EnableLPIs
	 * from 1 to 0 beक्रमe programming GICR_PENDअणुPROPपूर्णBASER रेजिस्टरs.
	 * Error out अगर we समय out रुकोing क्रम RWP to clear.
	 */
	जबतक (पढ़ोl_relaxed(rbase + GICR_CTLR) & GICR_CTLR_RWP) अणु
		अगर (!समयout) अणु
			pr_err("CPU%d: Timeout while disabling LPIs\n",
			       smp_processor_id());
			वापस -ETIMEDOUT;
		पूर्ण
		udelay(1);
		समयout--;
	पूर्ण

	/*
	 * After it has been written to 1, it is IMPLEMENTATION
	 * DEFINED whether GICR_CTLR.EnableLPI becomes RES1 or can be
	 * cleared to 0. Error out अगर clearing the bit failed.
	 */
	अगर (पढ़ोl_relaxed(rbase + GICR_CTLR) & GICR_CTLR_ENABLE_LPIS) अणु
		pr_err("CPU%d: Failed to disable LPIs\n", smp_processor_id());
		वापस -EBUSY;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक its_cpu_init(व्योम)
अणु
	अगर (!list_empty(&its_nodes)) अणु
		पूर्णांक ret;

		ret = redist_disable_lpis();
		अगर (ret)
			वापस ret;

		its_cpu_init_lpis();
		its_cpu_init_collections();
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id its_device_id[] = अणु
	अणु	.compatible	= "arm,gic-v3-its",	पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल पूर्णांक __init its_of_probe(काष्ठा device_node *node)
अणु
	काष्ठा device_node *np;
	काष्ठा resource res;

	क्रम (np = of_find_matching_node(node, its_device_id); np;
	     np = of_find_matching_node(np, its_device_id)) अणु
		अगर (!of_device_is_available(np))
			जारी;
		अगर (!of_property_पढ़ो_bool(np, "msi-controller")) अणु
			pr_warn("%pOF: no msi-controller property, ITS ignored\n",
				np);
			जारी;
		पूर्ण

		अगर (of_address_to_resource(np, 0, &res)) अणु
			pr_warn("%pOF: no regs?\n", np);
			जारी;
		पूर्ण

		its_probe_one(&res, &np->fwnode, of_node_to_nid(np));
	पूर्ण
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_ACPI

#घोषणा ACPI_GICV3_ITS_MEM_SIZE (SZ_128K)

#अगर_घोषित CONFIG_ACPI_NUMA
काष्ठा its_srat_map अणु
	/* numa node id */
	u32	numa_node;
	/* GIC ITS ID */
	u32	its_id;
पूर्ण;

अटल काष्ठा its_srat_map *its_srat_maps __initdata;
अटल पूर्णांक its_in_srat __initdata;

अटल पूर्णांक __init acpi_get_its_numa_node(u32 its_id)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < its_in_srat; i++) अणु
		अगर (its_id == its_srat_maps[i].its_id)
			वापस its_srat_maps[i].numa_node;
	पूर्ण
	वापस NUMA_NO_NODE;
पूर्ण

अटल पूर्णांक __init gic_acpi_match_srat_its(जोड़ acpi_subtable_headers *header,
					  स्थिर अचिन्हित दीर्घ end)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक __init gic_acpi_parse_srat_its(जोड़ acpi_subtable_headers *header,
			 स्थिर अचिन्हित दीर्घ end)
अणु
	पूर्णांक node;
	काष्ठा acpi_srat_gic_its_affinity *its_affinity;

	its_affinity = (काष्ठा acpi_srat_gic_its_affinity *)header;
	अगर (!its_affinity)
		वापस -EINVAL;

	अगर (its_affinity->header.length < माप(*its_affinity)) अणु
		pr_err("SRAT: Invalid header length %d in ITS affinity\n",
			its_affinity->header.length);
		वापस -EINVAL;
	पूर्ण

	/*
	 * Note that in theory a new proximity node could be created by this
	 * entry as it is an SRAT resource allocation काष्ठाure.
	 * We करो not currently support करोing so.
	 */
	node = pxm_to_node(its_affinity->proximity_करोमुख्य);

	अगर (node == NUMA_NO_NODE || node >= MAX_NUMNODES) अणु
		pr_err("SRAT: Invalid NUMA node %d in ITS affinity\n", node);
		वापस 0;
	पूर्ण

	its_srat_maps[its_in_srat].numa_node = node;
	its_srat_maps[its_in_srat].its_id = its_affinity->its_id;
	its_in_srat++;
	pr_info("SRAT: PXM %d -> ITS %d -> Node %d\n",
		its_affinity->proximity_करोमुख्य, its_affinity->its_id, node);

	वापस 0;
पूर्ण

अटल व्योम __init acpi_table_parse_srat_its(व्योम)
अणु
	पूर्णांक count;

	count = acpi_table_parse_entries(ACPI_SIG_SRAT,
			माप(काष्ठा acpi_table_srat),
			ACPI_SRAT_TYPE_GIC_ITS_AFFINITY,
			gic_acpi_match_srat_its, 0);
	अगर (count <= 0)
		वापस;

	its_srat_maps = kदो_स्मृति_array(count, माप(काष्ठा its_srat_map),
				      GFP_KERNEL);
	अगर (!its_srat_maps) अणु
		pr_warn("SRAT: Failed to allocate memory for its_srat_maps!\n");
		वापस;
	पूर्ण

	acpi_table_parse_entries(ACPI_SIG_SRAT,
			माप(काष्ठा acpi_table_srat),
			ACPI_SRAT_TYPE_GIC_ITS_AFFINITY,
			gic_acpi_parse_srat_its, 0);
पूर्ण

/* मुक्त the its_srat_maps after ITS probing */
अटल व्योम __init acpi_its_srat_maps_मुक्त(व्योम)
अणु
	kमुक्त(its_srat_maps);
पूर्ण
#अन्यथा
अटल व्योम __init acpi_table_parse_srat_its(व्योम)	अणु पूर्ण
अटल पूर्णांक __init acpi_get_its_numa_node(u32 its_id) अणु वापस NUMA_NO_NODE; पूर्ण
अटल व्योम __init acpi_its_srat_maps_मुक्त(व्योम) अणु पूर्ण
#पूर्ण_अगर

अटल पूर्णांक __init gic_acpi_parse_madt_its(जोड़ acpi_subtable_headers *header,
					  स्थिर अचिन्हित दीर्घ end)
अणु
	काष्ठा acpi_madt_generic_translator *its_entry;
	काष्ठा fwnode_handle *करोm_handle;
	काष्ठा resource res;
	पूर्णांक err;

	its_entry = (काष्ठा acpi_madt_generic_translator *)header;
	स_रखो(&res, 0, माप(res));
	res.start = its_entry->base_address;
	res.end = its_entry->base_address + ACPI_GICV3_ITS_MEM_SIZE - 1;
	res.flags = IORESOURCE_MEM;

	करोm_handle = irq_करोमुख्य_alloc_fwnode(&res.start);
	अगर (!करोm_handle) अणु
		pr_err("ITS@%pa: Unable to allocate GICv3 ITS domain token\n",
		       &res.start);
		वापस -ENOMEM;
	पूर्ण

	err = iort_रेजिस्टर_करोमुख्य_token(its_entry->translation_id, res.start,
					 करोm_handle);
	अगर (err) अणु
		pr_err("ITS@%pa: Unable to register GICv3 ITS domain token (ITS ID %d) to IORT\n",
		       &res.start, its_entry->translation_id);
		जाओ करोm_err;
	पूर्ण

	err = its_probe_one(&res, करोm_handle,
			acpi_get_its_numa_node(its_entry->translation_id));
	अगर (!err)
		वापस 0;

	iort_deरेजिस्टर_करोमुख्य_token(its_entry->translation_id);
करोm_err:
	irq_करोमुख्य_मुक्त_fwnode(करोm_handle);
	वापस err;
पूर्ण

अटल व्योम __init its_acpi_probe(व्योम)
अणु
	acpi_table_parse_srat_its();
	acpi_table_parse_madt(ACPI_MADT_TYPE_GENERIC_TRANSLATOR,
			      gic_acpi_parse_madt_its, 0);
	acpi_its_srat_maps_मुक्त();
पूर्ण
#अन्यथा
अटल व्योम __init its_acpi_probe(व्योम) अणु पूर्ण
#पूर्ण_अगर

पूर्णांक __init its_init(काष्ठा fwnode_handle *handle, काष्ठा rdists *rdists,
		    काष्ठा irq_करोमुख्य *parent_करोमुख्य)
अणु
	काष्ठा device_node *of_node;
	काष्ठा its_node *its;
	bool has_v4 = false;
	bool has_v4_1 = false;
	पूर्णांक err;

	gic_rdists = rdists;

	its_parent = parent_करोमुख्य;
	of_node = to_of_node(handle);
	अगर (of_node)
		its_of_probe(of_node);
	अन्यथा
		its_acpi_probe();

	अगर (list_empty(&its_nodes)) अणु
		pr_warn("ITS: No ITS available, not enabling LPIs\n");
		वापस -ENXIO;
	पूर्ण

	err = allocate_lpi_tables();
	अगर (err)
		वापस err;

	list_क्रम_each_entry(its, &its_nodes, entry) अणु
		has_v4 |= is_v4(its);
		has_v4_1 |= is_v4_1(its);
	पूर्ण

	/* Don't bother with inconsistent प्रणालीs */
	अगर (WARN_ON(!has_v4_1 && rdists->has_rvpeid))
		rdists->has_rvpeid = false;

	अगर (has_v4 & rdists->has_vlpis) अणु
		स्थिर काष्ठा irq_करोमुख्य_ops *sgi_ops;

		अगर (has_v4_1)
			sgi_ops = &its_sgi_करोमुख्य_ops;
		अन्यथा
			sgi_ops = शून्य;

		अगर (its_init_vpe_करोमुख्य() ||
		    its_init_v4(parent_करोमुख्य, &its_vpe_करोमुख्य_ops, sgi_ops)) अणु
			rdists->has_vlpis = false;
			pr_err("ITS: Disabling GICv4 support\n");
		पूर्ण
	पूर्ण

	रेजिस्टर_syscore_ops(&its_syscore_ops);

	वापस 0;
पूर्ण
