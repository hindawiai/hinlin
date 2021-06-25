<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * PRU-ICSS remoteproc driver क्रम various TI SoCs
 *
 * Copyright (C) 2014-2020 Texas Instruments Incorporated - https://www.ti.com/
 *
 * Author(s):
 *	Suman Anna <s-anna@ti.com>
 *	Andrew F. Davis <afd@ti.com>
 *	Grzegorz Jaszczyk <grzegorz.jaszczyk@linaro.org> क्रम Texas Instruments
 */

#समावेश <linux/bitops.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/irqकरोमुख्य.h>
#समावेश <linux/module.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/pruss_driver.h>
#समावेश <linux/remoteproc.h>

#समावेश "remoteproc_internal.h"
#समावेश "remoteproc_elf_helpers.h"
#समावेश "pru_rproc.h"

/* PRU_ICSS_PRU_CTRL रेजिस्टरs */
#घोषणा PRU_CTRL_CTRL		0x0000
#घोषणा PRU_CTRL_STS		0x0004
#घोषणा PRU_CTRL_WAKEUP_EN	0x0008
#घोषणा PRU_CTRL_CYCLE		0x000C
#घोषणा PRU_CTRL_STALL		0x0010
#घोषणा PRU_CTRL_CTBIR0		0x0020
#घोषणा PRU_CTRL_CTBIR1		0x0024
#घोषणा PRU_CTRL_CTPPR0		0x0028
#घोषणा PRU_CTRL_CTPPR1		0x002C

/* CTRL रेजिस्टर bit-fields */
#घोषणा CTRL_CTRL_SOFT_RST_N	BIT(0)
#घोषणा CTRL_CTRL_EN		BIT(1)
#घोषणा CTRL_CTRL_SLEEPING	BIT(2)
#घोषणा CTRL_CTRL_CTR_EN	BIT(3)
#घोषणा CTRL_CTRL_SINGLE_STEP	BIT(8)
#घोषणा CTRL_CTRL_RUNSTATE	BIT(15)

/* PRU_ICSS_PRU_DEBUG रेजिस्टरs */
#घोषणा PRU_DEBUG_GPREG(x)	(0x0000 + (x) * 4)
#घोषणा PRU_DEBUG_CT_REG(x)	(0x0080 + (x) * 4)

/* PRU/RTU/Tx_PRU Core IRAM address masks */
#घोषणा PRU_IRAM_ADDR_MASK	0x3ffff
#घोषणा PRU0_IRAM_ADDR_MASK	0x34000
#घोषणा PRU1_IRAM_ADDR_MASK	0x38000
#घोषणा RTU0_IRAM_ADDR_MASK	0x4000
#घोषणा RTU1_IRAM_ADDR_MASK	0x6000
#घोषणा TX_PRU0_IRAM_ADDR_MASK	0xa000
#घोषणा TX_PRU1_IRAM_ADDR_MASK	0xc000

/* PRU device addresses क्रम various type of PRU RAMs */
#घोषणा PRU_IRAM_DA	0	/* Inकाष्ठाion RAM */
#घोषणा PRU_PDRAM_DA	0	/* Primary Data RAM */
#घोषणा PRU_SDRAM_DA	0x2000	/* Secondary Data RAM */
#घोषणा PRU_SHRDRAM_DA	0x10000 /* Shared Data RAM */

#घोषणा MAX_PRU_SYS_EVENTS 160

/**
 * क्रमागत pru_iomem - PRU core memory/रेजिस्टर range identअगरiers
 *
 * @PRU_IOMEM_IRAM: PRU Inकाष्ठाion RAM range
 * @PRU_IOMEM_CTRL: PRU Control रेजिस्टर range
 * @PRU_IOMEM_DEBUG: PRU Debug रेजिस्टर range
 * @PRU_IOMEM_MAX: just keep this one at the end
 */
क्रमागत pru_iomem अणु
	PRU_IOMEM_IRAM = 0,
	PRU_IOMEM_CTRL,
	PRU_IOMEM_DEBUG,
	PRU_IOMEM_MAX,
पूर्ण;

/**
 * क्रमागत pru_type - PRU core type identअगरier
 *
 * @PRU_TYPE_PRU: Programmable Real-समय Unit
 * @PRU_TYPE_RTU: Auxiliary Programmable Real-Time Unit
 * @PRU_TYPE_TX_PRU: Transmit Programmable Real-Time Unit
 * @PRU_TYPE_MAX: just keep this one at the end
 */
क्रमागत pru_type अणु
	PRU_TYPE_PRU = 0,
	PRU_TYPE_RTU,
	PRU_TYPE_TX_PRU,
	PRU_TYPE_MAX,
पूर्ण;

/**
 * काष्ठा pru_निजी_data - device data क्रम a PRU core
 * @type: type of the PRU core (PRU, RTU, Tx_PRU)
 * @is_k3: flag used to identअगरy the need क्रम special load handling
 */
काष्ठा pru_निजी_data अणु
	क्रमागत pru_type type;
	अचिन्हित पूर्णांक is_k3 : 1;
पूर्ण;

/**
 * काष्ठा pru_rproc - PRU remoteproc काष्ठाure
 * @id: id of the PRU core within the PRUSS
 * @dev: PRU core device poपूर्णांकer
 * @pruss: back-reference to parent PRUSS काष्ठाure
 * @rproc: remoteproc poपूर्णांकer क्रम this PRU core
 * @data: PRU core specअगरic data
 * @mem_regions: data क्रम each of the PRU memory regions
 * @fw_name: name of firmware image used during loading
 * @mapped_irq: भव पूर्णांकerrupt numbers of created fw specअगरic mapping
 * @pru_पूर्णांकerrupt_map: poपूर्णांकer to पूर्णांकerrupt mapping description (firmware)
 * @pru_पूर्णांकerrupt_map_sz: pru_पूर्णांकerrupt_map size
 * @dbg_single_step: debug state variable to set PRU पूर्णांकo single step mode
 * @dbg_continuous: debug state variable to restore PRU execution mode
 * @evt_count: number of mapped events
 */
काष्ठा pru_rproc अणु
	पूर्णांक id;
	काष्ठा device *dev;
	काष्ठा pruss *pruss;
	काष्ठा rproc *rproc;
	स्थिर काष्ठा pru_निजी_data *data;
	काष्ठा pruss_mem_region mem_regions[PRU_IOMEM_MAX];
	स्थिर अक्षर *fw_name;
	अचिन्हित पूर्णांक *mapped_irq;
	काष्ठा pru_irq_rsc *pru_पूर्णांकerrupt_map;
	माप_प्रकार pru_पूर्णांकerrupt_map_sz;
	u32 dbg_single_step;
	u32 dbg_continuous;
	u8 evt_count;
पूर्ण;

अटल अंतरभूत u32 pru_control_पढ़ो_reg(काष्ठा pru_rproc *pru, अचिन्हित पूर्णांक reg)
अणु
	वापस पढ़ोl_relaxed(pru->mem_regions[PRU_IOMEM_CTRL].va + reg);
पूर्ण

अटल अंतरभूत
व्योम pru_control_ग_लिखो_reg(काष्ठा pru_rproc *pru, अचिन्हित पूर्णांक reg, u32 val)
अणु
	ग_लिखोl_relaxed(val, pru->mem_regions[PRU_IOMEM_CTRL].va + reg);
पूर्ण

अटल अंतरभूत u32 pru_debug_पढ़ो_reg(काष्ठा pru_rproc *pru, अचिन्हित पूर्णांक reg)
अणु
	वापस पढ़ोl_relaxed(pru->mem_regions[PRU_IOMEM_DEBUG].va + reg);
पूर्ण

अटल पूर्णांक regs_show(काष्ठा seq_file *s, व्योम *data)
अणु
	काष्ठा rproc *rproc = s->निजी;
	काष्ठा pru_rproc *pru = rproc->priv;
	पूर्णांक i, nregs = 32;
	u32 pru_sts;
	पूर्णांक pru_is_running;

	seq_माला_दो(s, "============== Control Registers ==============\n");
	seq_म_लिखो(s, "CTRL      := 0x%08x\n",
		   pru_control_पढ़ो_reg(pru, PRU_CTRL_CTRL));
	pru_sts = pru_control_पढ़ो_reg(pru, PRU_CTRL_STS);
	seq_म_लिखो(s, "STS (PC)  := 0x%08x (0x%08x)\n", pru_sts, pru_sts << 2);
	seq_म_लिखो(s, "WAKEUP_EN := 0x%08x\n",
		   pru_control_पढ़ो_reg(pru, PRU_CTRL_WAKEUP_EN));
	seq_म_लिखो(s, "CYCLE     := 0x%08x\n",
		   pru_control_पढ़ो_reg(pru, PRU_CTRL_CYCLE));
	seq_म_लिखो(s, "STALL     := 0x%08x\n",
		   pru_control_पढ़ो_reg(pru, PRU_CTRL_STALL));
	seq_म_लिखो(s, "CTBIR0    := 0x%08x\n",
		   pru_control_पढ़ो_reg(pru, PRU_CTRL_CTBIR0));
	seq_म_लिखो(s, "CTBIR1    := 0x%08x\n",
		   pru_control_पढ़ो_reg(pru, PRU_CTRL_CTBIR1));
	seq_म_लिखो(s, "CTPPR0    := 0x%08x\n",
		   pru_control_पढ़ो_reg(pru, PRU_CTRL_CTPPR0));
	seq_म_लिखो(s, "CTPPR1    := 0x%08x\n",
		   pru_control_पढ़ो_reg(pru, PRU_CTRL_CTPPR1));

	seq_माला_दो(s, "=============== Debug Registers ===============\n");
	pru_is_running = pru_control_पढ़ो_reg(pru, PRU_CTRL_CTRL) &
				CTRL_CTRL_RUNSTATE;
	अगर (pru_is_running) अणु
		seq_माला_दो(s, "PRU is executing, cannot print/access debug registers.\n");
		वापस 0;
	पूर्ण

	क्रम (i = 0; i < nregs; i++) अणु
		seq_म_लिखो(s, "GPREG%-2d := 0x%08x\tCT_REG%-2d := 0x%08x\n",
			   i, pru_debug_पढ़ो_reg(pru, PRU_DEBUG_GPREG(i)),
			   i, pru_debug_पढ़ो_reg(pru, PRU_DEBUG_CT_REG(i)));
	पूर्ण

	वापस 0;
पूर्ण
DEFINE_SHOW_ATTRIBUTE(regs);

/*
 * Control PRU single-step mode
 *
 * This is a debug helper function used क्रम controlling the single-step
 * mode of the PRU. The PRU Debug रेजिस्टरs are not accessible when the
 * PRU is in RUNNING state.
 *
 * Writing a non-zero value sets the PRU पूर्णांकo single-step mode irrespective
 * of its previous state. The PRU mode is saved only on the first set पूर्णांकo
 * a single-step mode. Writing a zero value will restore the PRU पूर्णांकo its
 * original mode.
 */
अटल पूर्णांक pru_rproc_debug_ss_set(व्योम *data, u64 val)
अणु
	काष्ठा rproc *rproc = data;
	काष्ठा pru_rproc *pru = rproc->priv;
	u32 reg_val;

	val = val ? 1 : 0;
	अगर (!val && !pru->dbg_single_step)
		वापस 0;

	reg_val = pru_control_पढ़ो_reg(pru, PRU_CTRL_CTRL);

	अगर (val && !pru->dbg_single_step)
		pru->dbg_continuous = reg_val;

	अगर (val)
		reg_val |= CTRL_CTRL_SINGLE_STEP | CTRL_CTRL_EN;
	अन्यथा
		reg_val = pru->dbg_continuous;

	pru->dbg_single_step = val;
	pru_control_ग_लिखो_reg(pru, PRU_CTRL_CTRL, reg_val);

	वापस 0;
पूर्ण

अटल पूर्णांक pru_rproc_debug_ss_get(व्योम *data, u64 *val)
अणु
	काष्ठा rproc *rproc = data;
	काष्ठा pru_rproc *pru = rproc->priv;

	*val = pru->dbg_single_step;

	वापस 0;
पूर्ण
DEFINE_DEBUGFS_ATTRIBUTE(pru_rproc_debug_ss_fops, pru_rproc_debug_ss_get,
			 pru_rproc_debug_ss_set, "%llu\n");

/*
 * Create PRU-specअगरic debugfs entries
 *
 * The entries are created only अगर the parent remoteproc debugfs directory
 * exists, and will be cleaned up by the remoteproc core.
 */
अटल व्योम pru_rproc_create_debug_entries(काष्ठा rproc *rproc)
अणु
	अगर (!rproc->dbg_dir)
		वापस;

	debugfs_create_file("regs", 0400, rproc->dbg_dir,
			    rproc, &regs_fops);
	debugfs_create_file("single_step", 0600, rproc->dbg_dir,
			    rproc, &pru_rproc_debug_ss_fops);
पूर्ण

अटल व्योम pru_dispose_irq_mapping(काष्ठा pru_rproc *pru)
अणु
	अगर (!pru->mapped_irq)
		वापस;

	जबतक (pru->evt_count) अणु
		pru->evt_count--;
		अगर (pru->mapped_irq[pru->evt_count] > 0)
			irq_dispose_mapping(pru->mapped_irq[pru->evt_count]);
	पूर्ण

	kमुक्त(pru->mapped_irq);
	pru->mapped_irq = शून्य;
पूर्ण

/*
 * Parse the custom PRU पूर्णांकerrupt map resource and configure the INTC
 * appropriately.
 */
अटल पूर्णांक pru_handle_पूर्णांकrmap(काष्ठा rproc *rproc)
अणु
	काष्ठा device *dev = rproc->dev.parent;
	काष्ठा pru_rproc *pru = rproc->priv;
	काष्ठा pru_irq_rsc *rsc = pru->pru_पूर्णांकerrupt_map;
	काष्ठा irq_fwspec fwspec;
	काष्ठा device_node *parent, *irq_parent;
	पूर्णांक i, ret = 0;

	/* not having pru_पूर्णांकerrupt_map is not an error */
	अगर (!rsc)
		वापस 0;

	/* currently supporting only type 0 */
	अगर (rsc->type != 0) अणु
		dev_err(dev, "unsupported rsc type: %d\n", rsc->type);
		वापस -EINVAL;
	पूर्ण

	अगर (rsc->num_evts > MAX_PRU_SYS_EVENTS)
		वापस -EINVAL;

	अगर (माप(*rsc) + rsc->num_evts * माप(काष्ठा pruss_पूर्णांक_map) !=
	    pru->pru_पूर्णांकerrupt_map_sz)
		वापस -EINVAL;

	pru->evt_count = rsc->num_evts;
	pru->mapped_irq = kसुस्मृति(pru->evt_count, माप(अचिन्हित पूर्णांक),
				  GFP_KERNEL);
	अगर (!pru->mapped_irq) अणु
		pru->evt_count = 0;
		वापस -ENOMEM;
	पूर्ण

	/*
	 * parse and fill in प्रणाली event to पूर्णांकerrupt channel and
	 * channel-to-host mapping. The पूर्णांकerrupt controller to be used
	 * क्रम these mappings क्रम a given PRU remoteproc is always its
	 * corresponding sibling PRUSS INTC node.
	 */
	parent = of_get_parent(dev_of_node(pru->dev));
	अगर (!parent) अणु
		kमुक्त(pru->mapped_irq);
		pru->mapped_irq = शून्य;
		pru->evt_count = 0;
		वापस -ENODEV;
	पूर्ण

	irq_parent = of_get_child_by_name(parent, "interrupt-controller");
	of_node_put(parent);
	अगर (!irq_parent) अणु
		kमुक्त(pru->mapped_irq);
		pru->mapped_irq = शून्य;
		pru->evt_count = 0;
		वापस -ENODEV;
	पूर्ण

	fwspec.fwnode = of_node_to_fwnode(irq_parent);
	fwspec.param_count = 3;
	क्रम (i = 0; i < pru->evt_count; i++) अणु
		fwspec.param[0] = rsc->pru_पूर्णांकc_map[i].event;
		fwspec.param[1] = rsc->pru_पूर्णांकc_map[i].chnl;
		fwspec.param[2] = rsc->pru_पूर्णांकc_map[i].host;

		dev_dbg(dev, "mapping%d: event %d, chnl %d, host %d\n",
			i, fwspec.param[0], fwspec.param[1], fwspec.param[2]);

		pru->mapped_irq[i] = irq_create_fwspec_mapping(&fwspec);
		अगर (!pru->mapped_irq[i]) अणु
			dev_err(dev, "failed to get virq for fw mapping %d: event %d chnl %d host %d\n",
				i, fwspec.param[0], fwspec.param[1],
				fwspec.param[2]);
			ret = -EINVAL;
			जाओ map_fail;
		पूर्ण
	पूर्ण
	of_node_put(irq_parent);

	वापस ret;

map_fail:
	pru_dispose_irq_mapping(pru);
	of_node_put(irq_parent);

	वापस ret;
पूर्ण

अटल पूर्णांक pru_rproc_start(काष्ठा rproc *rproc)
अणु
	काष्ठा device *dev = &rproc->dev;
	काष्ठा pru_rproc *pru = rproc->priv;
	स्थिर अक्षर *names[PRU_TYPE_MAX] = अणु "PRU", "RTU", "Tx_PRU" पूर्ण;
	u32 val;
	पूर्णांक ret;

	dev_dbg(dev, "starting %s%d: entry-point = 0x%llx\n",
		names[pru->data->type], pru->id, (rproc->bootaddr >> 2));

	ret = pru_handle_पूर्णांकrmap(rproc);
	/*
	 * reset references to pru पूर्णांकerrupt map - they will stop being valid
	 * after rproc_start वापसs
	 */
	pru->pru_पूर्णांकerrupt_map = शून्य;
	pru->pru_पूर्णांकerrupt_map_sz = 0;
	अगर (ret)
		वापस ret;

	val = CTRL_CTRL_EN | ((rproc->bootaddr >> 2) << 16);
	pru_control_ग_लिखो_reg(pru, PRU_CTRL_CTRL, val);

	वापस 0;
पूर्ण

अटल पूर्णांक pru_rproc_stop(काष्ठा rproc *rproc)
अणु
	काष्ठा device *dev = &rproc->dev;
	काष्ठा pru_rproc *pru = rproc->priv;
	स्थिर अक्षर *names[PRU_TYPE_MAX] = अणु "PRU", "RTU", "Tx_PRU" पूर्ण;
	u32 val;

	dev_dbg(dev, "stopping %s%d\n", names[pru->data->type], pru->id);

	val = pru_control_पढ़ो_reg(pru, PRU_CTRL_CTRL);
	val &= ~CTRL_CTRL_EN;
	pru_control_ग_लिखो_reg(pru, PRU_CTRL_CTRL, val);

	/* dispose irq mapping - new firmware can provide new mapping */
	pru_dispose_irq_mapping(pru);

	वापस 0;
पूर्ण

/*
 * Convert PRU device address (data spaces only) to kernel भव address.
 *
 * Each PRU has access to all data memories within the PRUSS, accessible at
 * dअगरferent ranges. So, look through both its primary and secondary Data
 * RAMs as well as any shared Data RAM to convert a PRU device address to
 * kernel भव address. Data RAM0 is primary Data RAM क्रम PRU0 and Data
 * RAM1 is primary Data RAM क्रम PRU1.
 */
अटल व्योम *pru_d_da_to_va(काष्ठा pru_rproc *pru, u32 da, माप_प्रकार len)
अणु
	काष्ठा pruss_mem_region dram0, dram1, shrd_ram;
	काष्ठा pruss *pruss = pru->pruss;
	u32 offset;
	व्योम *va = शून्य;

	अगर (len == 0)
		वापस शून्य;

	dram0 = pruss->mem_regions[PRUSS_MEM_DRAM0];
	dram1 = pruss->mem_regions[PRUSS_MEM_DRAM1];
	/* PRU1 has its local RAM addresses reversed */
	अगर (pru->id == 1)
		swap(dram0, dram1);
	shrd_ram = pruss->mem_regions[PRUSS_MEM_SHRD_RAM2];

	अगर (da >= PRU_PDRAM_DA && da + len <= PRU_PDRAM_DA + dram0.size) अणु
		offset = da - PRU_PDRAM_DA;
		va = (__क्रमce व्योम *)(dram0.va + offset);
	पूर्ण अन्यथा अगर (da >= PRU_SDRAM_DA &&
		   da + len <= PRU_SDRAM_DA + dram1.size) अणु
		offset = da - PRU_SDRAM_DA;
		va = (__क्रमce व्योम *)(dram1.va + offset);
	पूर्ण अन्यथा अगर (da >= PRU_SHRDRAM_DA &&
		   da + len <= PRU_SHRDRAM_DA + shrd_ram.size) अणु
		offset = da - PRU_SHRDRAM_DA;
		va = (__क्रमce व्योम *)(shrd_ram.va + offset);
	पूर्ण

	वापस va;
पूर्ण

/*
 * Convert PRU device address (inकाष्ठाion space) to kernel भव address.
 *
 * A PRU करोes not have an unअगरied address space. Each PRU has its very own
 * निजी Inकाष्ठाion RAM, and its device address is identical to that of
 * its primary Data RAM device address.
 */
अटल व्योम *pru_i_da_to_va(काष्ठा pru_rproc *pru, u32 da, माप_प्रकार len)
अणु
	u32 offset;
	व्योम *va = शून्य;

	अगर (len == 0)
		वापस शून्य;

	/*
	 * GNU binutils करो not support multiple address spaces. The GNU
	 * linker's शेष linker script places IRAM at an arbitrary high
	 * offset, in order to dअगरferentiate it from DRAM. Hence we need to
	 * strip the artअगरicial offset in the IRAM addresses coming from the
	 * ELF file.
	 *
	 * The TI proprietary linker would never set those higher IRAM address
	 * bits anyway. PRU architecture limits the program counter to 16-bit
	 * word-address range. This in turn corresponds to 18-bit IRAM
	 * byte-address range क्रम ELF.
	 *
	 * Two more bits are added just in हाल to make the final 20-bit mask.
	 * Idea is to have a safeguard in हाल TI decides to add banking
	 * in future SoCs.
	 */
	da &= 0xfffff;

	अगर (da >= PRU_IRAM_DA &&
	    da + len <= PRU_IRAM_DA + pru->mem_regions[PRU_IOMEM_IRAM].size) अणु
		offset = da - PRU_IRAM_DA;
		va = (__क्रमce व्योम *)(pru->mem_regions[PRU_IOMEM_IRAM].va +
				      offset);
	पूर्ण

	वापस va;
पूर्ण

/*
 * Provide address translations क्रम only PRU Data RAMs through the remoteproc
 * core क्रम any PRU client drivers. The PRU Inकाष्ठाion RAM access is restricted
 * only to the PRU loader code.
 */
अटल व्योम *pru_rproc_da_to_va(काष्ठा rproc *rproc, u64 da, माप_प्रकार len, bool *is_iomem)
अणु
	काष्ठा pru_rproc *pru = rproc->priv;

	वापस pru_d_da_to_va(pru, da, len);
पूर्ण

/* PRU-specअगरic address translator used by PRU loader. */
अटल व्योम *pru_da_to_va(काष्ठा rproc *rproc, u64 da, माप_प्रकार len, bool is_iram)
अणु
	काष्ठा pru_rproc *pru = rproc->priv;
	व्योम *va;

	अगर (is_iram)
		va = pru_i_da_to_va(pru, da, len);
	अन्यथा
		va = pru_d_da_to_va(pru, da, len);

	वापस va;
पूर्ण

अटल काष्ठा rproc_ops pru_rproc_ops = अणु
	.start		= pru_rproc_start,
	.stop		= pru_rproc_stop,
	.da_to_va	= pru_rproc_da_to_va,
पूर्ण;

/*
 * Custom memory copy implementation क्रम ICSSG PRU/RTU/Tx_PRU Cores
 *
 * The ICSSG PRU/RTU/Tx_PRU cores have a memory copying issue with IRAM
 * memories, that is not seen on previous generation SoCs. The data is reflected
 * properly in the IRAM memories only क्रम पूर्णांकeger (4-byte) copies. Any unaligned
 * copies result in all the other pre-existing bytes zeroed out within that
 * 4-byte boundary, thereby resulting in wrong text/code in the IRAMs. Also, the
 * IRAM memory port पूर्णांकerface करोes not allow any 8-byte copies (as commonly used
 * by ARM64 स_नकल implementation) and throws an exception. The DRAM memory
 * ports करो not show this behavior.
 */
अटल पूर्णांक pru_rproc_स_नकल(व्योम *dest, स्थिर व्योम *src, माप_प्रकार count)
अणु
	स्थिर u32 *s = src;
	u32 *d = dest;
	माप_प्रकार size = count / 4;
	u32 *पंचांगp_src = शून्य;

	/*
	 * TODO: relax limitation of 4-byte aligned dest addresses and copy
	 * sizes
	 */
	अगर ((दीर्घ)dest % 4 || count % 4)
		वापस -EINVAL;

	/* src offsets in ELF firmware image can be non-aligned */
	अगर ((दीर्घ)src % 4) अणु
		पंचांगp_src = kmemdup(src, count, GFP_KERNEL);
		अगर (!पंचांगp_src)
			वापस -ENOMEM;
		s = पंचांगp_src;
	पूर्ण

	जबतक (size--)
		*d++ = *s++;

	kमुक्त(पंचांगp_src);

	वापस 0;
पूर्ण

अटल पूर्णांक
pru_rproc_load_elf_segments(काष्ठा rproc *rproc, स्थिर काष्ठा firmware *fw)
अणु
	काष्ठा pru_rproc *pru = rproc->priv;
	काष्ठा device *dev = &rproc->dev;
	काष्ठा elf32_hdr *ehdr;
	काष्ठा elf32_phdr *phdr;
	पूर्णांक i, ret = 0;
	स्थिर u8 *elf_data = fw->data;

	ehdr = (काष्ठा elf32_hdr *)elf_data;
	phdr = (काष्ठा elf32_phdr *)(elf_data + ehdr->e_phoff);

	/* go through the available ELF segments */
	क्रम (i = 0; i < ehdr->e_phnum; i++, phdr++) अणु
		u32 da = phdr->p_paddr;
		u32 memsz = phdr->p_memsz;
		u32 filesz = phdr->p_filesz;
		u32 offset = phdr->p_offset;
		bool is_iram;
		व्योम *ptr;

		अगर (phdr->p_type != PT_LOAD || !filesz)
			जारी;

		dev_dbg(dev, "phdr: type %d da 0x%x memsz 0x%x filesz 0x%x\n",
			phdr->p_type, da, memsz, filesz);

		अगर (filesz > memsz) अणु
			dev_err(dev, "bad phdr filesz 0x%x memsz 0x%x\n",
				filesz, memsz);
			ret = -EINVAL;
			अवरोध;
		पूर्ण

		अगर (offset + filesz > fw->size) अणु
			dev_err(dev, "truncated fw: need 0x%x avail 0x%zx\n",
				offset + filesz, fw->size);
			ret = -EINVAL;
			अवरोध;
		पूर्ण

		/* grab the kernel address क्रम this device address */
		is_iram = phdr->p_flags & PF_X;
		ptr = pru_da_to_va(rproc, da, memsz, is_iram);
		अगर (!ptr) अणु
			dev_err(dev, "bad phdr da 0x%x mem 0x%x\n", da, memsz);
			ret = -EINVAL;
			अवरोध;
		पूर्ण

		अगर (pru->data->is_k3) अणु
			ret = pru_rproc_स_नकल(ptr, elf_data + phdr->p_offset,
					       filesz);
			अगर (ret) अणु
				dev_err(dev, "PRU memory copy failed for da 0x%x memsz 0x%x\n",
					da, memsz);
				अवरोध;
			पूर्ण
		पूर्ण अन्यथा अणु
			स_नकल(ptr, elf_data + phdr->p_offset, filesz);
		पूर्ण

		/* skip the memzero logic perक्रमmed by remoteproc ELF loader */
	पूर्ण

	वापस ret;
पूर्ण

अटल स्थिर व्योम *
pru_rproc_find_पूर्णांकerrupt_map(काष्ठा device *dev, स्थिर काष्ठा firmware *fw)
अणु
	काष्ठा elf32_shdr *shdr, *name_table_shdr;
	स्थिर अक्षर *name_table;
	स्थिर u8 *elf_data = fw->data;
	काष्ठा elf32_hdr *ehdr = (काष्ठा elf32_hdr *)elf_data;
	u16 shnum = ehdr->e_shnum;
	u16 shstrndx = ehdr->e_shstrndx;
	पूर्णांक i;

	/* first, get the section header */
	shdr = (काष्ठा elf32_shdr *)(elf_data + ehdr->e_shoff);
	/* compute name table section header entry in shdr array */
	name_table_shdr = shdr + shstrndx;
	/* finally, compute the name table section address in elf */
	name_table = elf_data + name_table_shdr->sh_offset;

	क्रम (i = 0; i < shnum; i++, shdr++) अणु
		u32 size = shdr->sh_size;
		u32 offset = shdr->sh_offset;
		u32 name = shdr->sh_name;

		अगर (म_भेद(name_table + name, ".pru_irq_map"))
			जारी;

		/* make sure we have the entire irq map */
		अगर (offset + size > fw->size || offset + size < size) अणु
			dev_err(dev, ".pru_irq_map section truncated\n");
			वापस ERR_PTR(-EINVAL);
		पूर्ण

		/* make sure irq map has at least the header */
		अगर (माप(काष्ठा pru_irq_rsc) > size) अणु
			dev_err(dev, "header-less .pru_irq_map section\n");
			वापस ERR_PTR(-EINVAL);
		पूर्ण

		वापस shdr;
	पूर्ण

	dev_dbg(dev, "no .pru_irq_map section found for this fw\n");

	वापस शून्य;
पूर्ण

/*
 * Use a custom parse_fw callback function क्रम dealing with PRU firmware
 * specअगरic sections.
 *
 * The firmware blob can contain optional ELF sections: .resource_table section
 * and .pru_irq_map one. The second one contains the PRUSS पूर्णांकerrupt mapping
 * description, which needs to be setup beक्रमe घातering on the PRU core. To
 * aव्योम RAM wastage this ELF section is not mapped to any ELF segment (by the
 * firmware linker) and thereक्रमe is not loaded to PRU memory.
 */
अटल पूर्णांक pru_rproc_parse_fw(काष्ठा rproc *rproc, स्थिर काष्ठा firmware *fw)
अणु
	काष्ठा device *dev = &rproc->dev;
	काष्ठा pru_rproc *pru = rproc->priv;
	स्थिर u8 *elf_data = fw->data;
	स्थिर व्योम *shdr;
	u8 class = fw_elf_get_class(fw);
	u64 sh_offset;
	पूर्णांक ret;

	/* load optional rsc table */
	ret = rproc_elf_load_rsc_table(rproc, fw);
	अगर (ret == -EINVAL)
		dev_dbg(&rproc->dev, "no resource table found for this fw\n");
	अन्यथा अगर (ret)
		वापस ret;

	/* find .pru_पूर्णांकerrupt_map section, not having it is not an error */
	shdr = pru_rproc_find_पूर्णांकerrupt_map(dev, fw);
	अगर (IS_ERR(shdr))
		वापस PTR_ERR(shdr);

	अगर (!shdr)
		वापस 0;

	/* preserve poपूर्णांकer to PRU पूर्णांकerrupt map together with it size */
	sh_offset = elf_shdr_get_sh_offset(class, shdr);
	pru->pru_पूर्णांकerrupt_map = (काष्ठा pru_irq_rsc *)(elf_data + sh_offset);
	pru->pru_पूर्णांकerrupt_map_sz = elf_shdr_get_sh_size(class, shdr);

	वापस 0;
पूर्ण

/*
 * Compute PRU id based on the IRAM addresses. The PRU IRAMs are
 * always at a particular offset within the PRUSS address space.
 */
अटल पूर्णांक pru_rproc_set_id(काष्ठा pru_rproc *pru)
अणु
	पूर्णांक ret = 0;

	चयन (pru->mem_regions[PRU_IOMEM_IRAM].pa & PRU_IRAM_ADDR_MASK) अणु
	हाल TX_PRU0_IRAM_ADDR_MASK:
		fallthrough;
	हाल RTU0_IRAM_ADDR_MASK:
		fallthrough;
	हाल PRU0_IRAM_ADDR_MASK:
		pru->id = 0;
		अवरोध;
	हाल TX_PRU1_IRAM_ADDR_MASK:
		fallthrough;
	हाल RTU1_IRAM_ADDR_MASK:
		fallthrough;
	हाल PRU1_IRAM_ADDR_MASK:
		pru->id = 1;
		अवरोध;
	शेष:
		ret = -EINVAL;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक pru_rproc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा device_node *np = dev->of_node;
	काष्ठा platक्रमm_device *ppdev = to_platक्रमm_device(dev->parent);
	काष्ठा pru_rproc *pru;
	स्थिर अक्षर *fw_name;
	काष्ठा rproc *rproc = शून्य;
	काष्ठा resource *res;
	पूर्णांक i, ret;
	स्थिर काष्ठा pru_निजी_data *data;
	स्थिर अक्षर *mem_names[PRU_IOMEM_MAX] = अणु "iram", "control", "debug" पूर्ण;

	data = of_device_get_match_data(&pdev->dev);
	अगर (!data)
		वापस -ENODEV;

	ret = of_property_पढ़ो_string(np, "firmware-name", &fw_name);
	अगर (ret) अणु
		dev_err(dev, "unable to retrieve firmware-name %d\n", ret);
		वापस ret;
	पूर्ण

	rproc = devm_rproc_alloc(dev, pdev->name, &pru_rproc_ops, fw_name,
				 माप(*pru));
	अगर (!rproc) अणु
		dev_err(dev, "rproc_alloc failed\n");
		वापस -ENOMEM;
	पूर्ण
	/* use a custom load function to deal with PRU-specअगरic quirks */
	rproc->ops->load = pru_rproc_load_elf_segments;

	/* use a custom parse function to deal with PRU-specअगरic resources */
	rproc->ops->parse_fw = pru_rproc_parse_fw;

	/* error recovery is not supported क्रम PRUs */
	rproc->recovery_disabled = true;

	/*
	 * rproc_add will स्वतः-boot the processor normally, but this is not
	 * desired with PRU client driven boot-flow methoकरोlogy. A PRU
	 * application/client driver will boot the corresponding PRU
	 * remote-processor as part of its state machine either through the
	 * remoteproc sysfs पूर्णांकerface or through the equivalent kernel API.
	 */
	rproc->स्वतः_boot = false;

	pru = rproc->priv;
	pru->dev = dev;
	pru->data = data;
	pru->pruss = platक्रमm_get_drvdata(ppdev);
	pru->rproc = rproc;
	pru->fw_name = fw_name;

	क्रम (i = 0; i < ARRAY_SIZE(mem_names); i++) अणु
		res = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM,
						   mem_names[i]);
		pru->mem_regions[i].va = devm_ioremap_resource(dev, res);
		अगर (IS_ERR(pru->mem_regions[i].va)) अणु
			dev_err(dev, "failed to parse and map memory resource %d %s\n",
				i, mem_names[i]);
			ret = PTR_ERR(pru->mem_regions[i].va);
			वापस ret;
		पूर्ण
		pru->mem_regions[i].pa = res->start;
		pru->mem_regions[i].size = resource_size(res);

		dev_dbg(dev, "memory %8s: pa %pa size 0x%zx va %pK\n",
			mem_names[i], &pru->mem_regions[i].pa,
			pru->mem_regions[i].size, pru->mem_regions[i].va);
	पूर्ण

	ret = pru_rproc_set_id(pru);
	अगर (ret < 0)
		वापस ret;

	platक्रमm_set_drvdata(pdev, rproc);

	ret = devm_rproc_add(dev, pru->rproc);
	अगर (ret) अणु
		dev_err(dev, "rproc_add failed: %d\n", ret);
		वापस ret;
	पूर्ण

	pru_rproc_create_debug_entries(rproc);

	dev_dbg(dev, "PRU rproc node %pOF probed successfully\n", np);

	वापस 0;
पूर्ण

अटल पूर्णांक pru_rproc_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा rproc *rproc = platक्रमm_get_drvdata(pdev);

	dev_dbg(dev, "%s: removing rproc %s\n", __func__, rproc->name);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा pru_निजी_data pru_data = अणु
	.type = PRU_TYPE_PRU,
पूर्ण;

अटल स्थिर काष्ठा pru_निजी_data k3_pru_data = अणु
	.type = PRU_TYPE_PRU,
	.is_k3 = 1,
पूर्ण;

अटल स्थिर काष्ठा pru_निजी_data k3_rtu_data = अणु
	.type = PRU_TYPE_RTU,
	.is_k3 = 1,
पूर्ण;

अटल स्थिर काष्ठा pru_निजी_data k3_tx_pru_data = अणु
	.type = PRU_TYPE_TX_PRU,
	.is_k3 = 1,
पूर्ण;

अटल स्थिर काष्ठा of_device_id pru_rproc_match[] = अणु
	अणु .compatible = "ti,am3356-pru",	.data = &pru_data पूर्ण,
	अणु .compatible = "ti,am4376-pru",	.data = &pru_data पूर्ण,
	अणु .compatible = "ti,am5728-pru",	.data = &pru_data पूर्ण,
	अणु .compatible = "ti,k2g-pru",		.data = &pru_data पूर्ण,
	अणु .compatible = "ti,am654-pru",		.data = &k3_pru_data पूर्ण,
	अणु .compatible = "ti,am654-rtu",		.data = &k3_rtu_data पूर्ण,
	अणु .compatible = "ti,am654-tx-pru",	.data = &k3_tx_pru_data पूर्ण,
	अणु .compatible = "ti,j721e-pru",		.data = &k3_pru_data पूर्ण,
	अणु .compatible = "ti,j721e-rtu",		.data = &k3_rtu_data पूर्ण,
	अणु .compatible = "ti,j721e-tx-pru",	.data = &k3_tx_pru_data पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, pru_rproc_match);

अटल काष्ठा platक्रमm_driver pru_rproc_driver = अणु
	.driver = अणु
		.name   = "pru-rproc",
		.of_match_table = pru_rproc_match,
		.suppress_bind_attrs = true,
	पूर्ण,
	.probe  = pru_rproc_probe,
	.हटाओ = pru_rproc_हटाओ,
पूर्ण;
module_platक्रमm_driver(pru_rproc_driver);

MODULE_AUTHOR("Suman Anna <s-anna@ti.com>");
MODULE_AUTHOR("Andrew F. Davis <afd@ti.com>");
MODULE_AUTHOR("Grzegorz Jaszczyk <grzegorz.jaszczyk@linaro.org>");
MODULE_DESCRIPTION("PRU-ICSS Remote Processor Driver");
MODULE_LICENSE("GPL v2");
