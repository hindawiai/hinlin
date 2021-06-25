<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * TI K3 R5F (MCU) Remote Processor driver
 *
 * Copyright (C) 2017-2020 Texas Instruments Incorporated - https://www.ti.com/
 *	Suman Anna <s-anna@ti.com>
 */

#समावेश <linux/dma-mapping.h>
#समावेश <linux/err.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mailbox_client.h>
#समावेश <linux/module.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_reserved_स्मृति.स>
#समावेश <linux/omap-mailbox.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/remoteproc.h>
#समावेश <linux/reset.h>
#समावेश <linux/slab.h>

#समावेश "omap_remoteproc.h"
#समावेश "remoteproc_internal.h"
#समावेश "ti_sci_proc.h"

/* This address can either be क्रम ATCM or BTCM with the other at address 0x0 */
#घोषणा K3_R5_TCM_DEV_ADDR	0x41010000

/* R5 TI-SCI Processor Configuration Flags */
#घोषणा PROC_BOOT_CFG_FLAG_R5_DBG_EN			0x00000001
#घोषणा PROC_BOOT_CFG_FLAG_R5_DBG_NIDEN			0x00000002
#घोषणा PROC_BOOT_CFG_FLAG_R5_LOCKSTEP			0x00000100
#घोषणा PROC_BOOT_CFG_FLAG_R5_TEINIT			0x00000200
#घोषणा PROC_BOOT_CFG_FLAG_R5_NMFI_EN			0x00000400
#घोषणा PROC_BOOT_CFG_FLAG_R5_TCM_RSTBASE		0x00000800
#घोषणा PROC_BOOT_CFG_FLAG_R5_BTCM_EN			0x00001000
#घोषणा PROC_BOOT_CFG_FLAG_R5_ATCM_EN			0x00002000
/* Available from J7200 SoCs onwards */
#घोषणा PROC_BOOT_CFG_FLAG_R5_MEM_INIT_DIS		0x00004000

/* R5 TI-SCI Processor Control Flags */
#घोषणा PROC_BOOT_CTRL_FLAG_R5_CORE_HALT		0x00000001

/* R5 TI-SCI Processor Status Flags */
#घोषणा PROC_BOOT_STATUS_FLAG_R5_WFE			0x00000001
#घोषणा PROC_BOOT_STATUS_FLAG_R5_WFI			0x00000002
#घोषणा PROC_BOOT_STATUS_FLAG_R5_CLK_GATED		0x00000004
#घोषणा PROC_BOOT_STATUS_FLAG_R5_LOCKSTEP_PERMITTED	0x00000100

/**
 * काष्ठा k3_r5_mem - पूर्णांकernal memory काष्ठाure
 * @cpu_addr: MPU भव address of the memory region
 * @bus_addr: Bus address used to access the memory region
 * @dev_addr: Device address from remoteproc view
 * @size: Size of the memory region
 */
काष्ठा k3_r5_mem अणु
	व्योम __iomem *cpu_addr;
	phys_addr_t bus_addr;
	u32 dev_addr;
	माप_प्रकार size;
पूर्ण;

क्रमागत cluster_mode अणु
	CLUSTER_MODE_SPLIT = 0,
	CLUSTER_MODE_LOCKSTEP,
पूर्ण;

/**
 * काष्ठा k3_r5_soc_data - match data to handle SoC variations
 * @tcm_is_द्विगुन: flag to denote the larger unअगरied TCMs in certain modes
 * @tcm_ecc_स्वतःinit: flag to denote the स्वतः-initialization of TCMs क्रम ECC
 */
काष्ठा k3_r5_soc_data अणु
	bool tcm_is_द्विगुन;
	bool tcm_ecc_स्वतःinit;
पूर्ण;

/**
 * काष्ठा k3_r5_cluster - K3 R5F Cluster काष्ठाure
 * @dev: cached device poपूर्णांकer
 * @mode: Mode to configure the Cluster - Split or LockStep
 * @cores: list of R5 cores within the cluster
 * @soc_data: SoC-specअगरic feature data क्रम a R5FSS
 */
काष्ठा k3_r5_cluster अणु
	काष्ठा device *dev;
	क्रमागत cluster_mode mode;
	काष्ठा list_head cores;
	स्थिर काष्ठा k3_r5_soc_data *soc_data;
पूर्ण;

/**
 * काष्ठा k3_r5_core - K3 R5 core काष्ठाure
 * @elem: linked list item
 * @dev: cached device poपूर्णांकer
 * @rproc: rproc handle representing this core
 * @mem: पूर्णांकernal memory regions data
 * @sram: on-chip SRAM memory regions data
 * @num_mems: number of पूर्णांकernal memory regions
 * @num_sram: number of on-chip SRAM memory regions
 * @reset: reset control handle
 * @tsp: TI-SCI processor control handle
 * @ti_sci: TI-SCI handle
 * @ti_sci_id: TI-SCI device identअगरier
 * @atcm_enable: flag to control ATCM enablement
 * @btcm_enable: flag to control BTCM enablement
 * @loczrama: flag to dictate which TCM is at device address 0x0
 */
काष्ठा k3_r5_core अणु
	काष्ठा list_head elem;
	काष्ठा device *dev;
	काष्ठा rproc *rproc;
	काष्ठा k3_r5_mem *mem;
	काष्ठा k3_r5_mem *sram;
	पूर्णांक num_mems;
	पूर्णांक num_sram;
	काष्ठा reset_control *reset;
	काष्ठा ti_sci_proc *tsp;
	स्थिर काष्ठा ti_sci_handle *ti_sci;
	u32 ti_sci_id;
	u32 atcm_enable;
	u32 btcm_enable;
	u32 loczrama;
पूर्ण;

/**
 * काष्ठा k3_r5_rproc - K3 remote processor state
 * @dev: cached device poपूर्णांकer
 * @cluster: cached poपूर्णांकer to parent cluster काष्ठाure
 * @mbox: mailbox channel handle
 * @client: mailbox client to request the mailbox channel
 * @rproc: rproc handle
 * @core: cached poपूर्णांकer to r5 core काष्ठाure being used
 * @rmem: reserved memory regions data
 * @num_rmems: number of reserved memory regions
 */
काष्ठा k3_r5_rproc अणु
	काष्ठा device *dev;
	काष्ठा k3_r5_cluster *cluster;
	काष्ठा mbox_chan *mbox;
	काष्ठा mbox_client client;
	काष्ठा rproc *rproc;
	काष्ठा k3_r5_core *core;
	काष्ठा k3_r5_mem *rmem;
	पूर्णांक num_rmems;
पूर्ण;

/**
 * k3_r5_rproc_mbox_callback() - inbound mailbox message handler
 * @client: mailbox client poपूर्णांकer used क्रम requesting the mailbox channel
 * @data: mailbox payload
 *
 * This handler is invoked by the OMAP mailbox driver whenever a mailbox
 * message is received. Usually, the mailbox payload simply contains
 * the index of the virtqueue that is kicked by the remote processor,
 * and we let remoteproc core handle it.
 *
 * In addition to virtqueue indices, we also have some out-of-band values
 * that indicate dअगरferent events. Those values are deliberately very
 * large so they करोn't coincide with virtqueue indices.
 */
अटल व्योम k3_r5_rproc_mbox_callback(काष्ठा mbox_client *client, व्योम *data)
अणु
	काष्ठा k3_r5_rproc *kproc = container_of(client, काष्ठा k3_r5_rproc,
						client);
	काष्ठा device *dev = kproc->rproc->dev.parent;
	स्थिर अक्षर *name = kproc->rproc->name;
	u32 msg = omap_mbox_message(data);

	dev_dbg(dev, "mbox msg: 0x%x\n", msg);

	चयन (msg) अणु
	हाल RP_MBOX_CRASH:
		/*
		 * remoteproc detected an exception, but error recovery is not
		 * supported. So, just log this क्रम now
		 */
		dev_err(dev, "K3 R5F rproc %s crashed\n", name);
		अवरोध;
	हाल RP_MBOX_ECHO_REPLY:
		dev_info(dev, "received echo reply from %s\n", name);
		अवरोध;
	शेष:
		/* silently handle all other valid messages */
		अगर (msg >= RP_MBOX_READY && msg < RP_MBOX_END_MSG)
			वापस;
		अगर (msg > kproc->rproc->max_notअगरyid) अणु
			dev_dbg(dev, "dropping unknown message 0x%x", msg);
			वापस;
		पूर्ण
		/* msg contains the index of the triggered vring */
		अगर (rproc_vq_पूर्णांकerrupt(kproc->rproc, msg) == IRQ_NONE)
			dev_dbg(dev, "no message was found in vqid %d\n", msg);
	पूर्ण
पूर्ण

/* kick a virtqueue */
अटल व्योम k3_r5_rproc_kick(काष्ठा rproc *rproc, पूर्णांक vqid)
अणु
	काष्ठा k3_r5_rproc *kproc = rproc->priv;
	काष्ठा device *dev = rproc->dev.parent;
	mbox_msg_t msg = (mbox_msg_t)vqid;
	पूर्णांक ret;

	/* send the index of the triggered virtqueue in the mailbox payload */
	ret = mbox_send_message(kproc->mbox, (व्योम *)msg);
	अगर (ret < 0)
		dev_err(dev, "failed to send mailbox message, status = %d\n",
			ret);
पूर्ण

अटल पूर्णांक k3_r5_split_reset(काष्ठा k3_r5_core *core)
अणु
	पूर्णांक ret;

	ret = reset_control_निश्चित(core->reset);
	अगर (ret) अणु
		dev_err(core->dev, "local-reset assert failed, ret = %d\n",
			ret);
		वापस ret;
	पूर्ण

	ret = core->ti_sci->ops.dev_ops.put_device(core->ti_sci,
						   core->ti_sci_id);
	अगर (ret) अणु
		dev_err(core->dev, "module-reset assert failed, ret = %d\n",
			ret);
		अगर (reset_control_deनिश्चित(core->reset))
			dev_warn(core->dev, "local-reset deassert back failed\n");
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक k3_r5_split_release(काष्ठा k3_r5_core *core)
अणु
	पूर्णांक ret;

	ret = core->ti_sci->ops.dev_ops.get_device(core->ti_sci,
						   core->ti_sci_id);
	अगर (ret) अणु
		dev_err(core->dev, "module-reset deassert failed, ret = %d\n",
			ret);
		वापस ret;
	पूर्ण

	ret = reset_control_deनिश्चित(core->reset);
	अगर (ret) अणु
		dev_err(core->dev, "local-reset deassert failed, ret = %d\n",
			ret);
		अगर (core->ti_sci->ops.dev_ops.put_device(core->ti_sci,
							 core->ti_sci_id))
			dev_warn(core->dev, "module-reset assert back failed\n");
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक k3_r5_lockstep_reset(काष्ठा k3_r5_cluster *cluster)
अणु
	काष्ठा k3_r5_core *core;
	पूर्णांक ret;

	/* निश्चित local reset on all applicable cores */
	list_क्रम_each_entry(core, &cluster->cores, elem) अणु
		ret = reset_control_निश्चित(core->reset);
		अगर (ret) अणु
			dev_err(core->dev, "local-reset assert failed, ret = %d\n",
				ret);
			core = list_prev_entry(core, elem);
			जाओ unroll_local_reset;
		पूर्ण
	पूर्ण

	/* disable PSC modules on all applicable cores */
	list_क्रम_each_entry(core, &cluster->cores, elem) अणु
		ret = core->ti_sci->ops.dev_ops.put_device(core->ti_sci,
							   core->ti_sci_id);
		अगर (ret) अणु
			dev_err(core->dev, "module-reset assert failed, ret = %d\n",
				ret);
			जाओ unroll_module_reset;
		पूर्ण
	पूर्ण

	वापस 0;

unroll_module_reset:
	list_क्रम_each_entry_जारी_reverse(core, &cluster->cores, elem) अणु
		अगर (core->ti_sci->ops.dev_ops.put_device(core->ti_sci,
							 core->ti_sci_id))
			dev_warn(core->dev, "module-reset assert back failed\n");
	पूर्ण
	core = list_last_entry(&cluster->cores, काष्ठा k3_r5_core, elem);
unroll_local_reset:
	list_क्रम_each_entry_from_reverse(core, &cluster->cores, elem) अणु
		अगर (reset_control_deनिश्चित(core->reset))
			dev_warn(core->dev, "local-reset deassert back failed\n");
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक k3_r5_lockstep_release(काष्ठा k3_r5_cluster *cluster)
अणु
	काष्ठा k3_r5_core *core;
	पूर्णांक ret;

	/* enable PSC modules on all applicable cores */
	list_क्रम_each_entry_reverse(core, &cluster->cores, elem) अणु
		ret = core->ti_sci->ops.dev_ops.get_device(core->ti_sci,
							   core->ti_sci_id);
		अगर (ret) अणु
			dev_err(core->dev, "module-reset deassert failed, ret = %d\n",
				ret);
			core = list_next_entry(core, elem);
			जाओ unroll_module_reset;
		पूर्ण
	पूर्ण

	/* deनिश्चित local reset on all applicable cores */
	list_क्रम_each_entry_reverse(core, &cluster->cores, elem) अणु
		ret = reset_control_deनिश्चित(core->reset);
		अगर (ret) अणु
			dev_err(core->dev, "module-reset deassert failed, ret = %d\n",
				ret);
			जाओ unroll_local_reset;
		पूर्ण
	पूर्ण

	वापस 0;

unroll_local_reset:
	list_क्रम_each_entry_जारी(core, &cluster->cores, elem) अणु
		अगर (reset_control_निश्चित(core->reset))
			dev_warn(core->dev, "local-reset assert back failed\n");
	पूर्ण
	core = list_first_entry(&cluster->cores, काष्ठा k3_r5_core, elem);
unroll_module_reset:
	list_क्रम_each_entry_from(core, &cluster->cores, elem) अणु
		अगर (core->ti_sci->ops.dev_ops.put_device(core->ti_sci,
							 core->ti_sci_id))
			dev_warn(core->dev, "module-reset assert back failed\n");
	पूर्ण

	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक k3_r5_core_halt(काष्ठा k3_r5_core *core)
अणु
	वापस ti_sci_proc_set_control(core->tsp,
				       PROC_BOOT_CTRL_FLAG_R5_CORE_HALT, 0);
पूर्ण

अटल अंतरभूत पूर्णांक k3_r5_core_run(काष्ठा k3_r5_core *core)
अणु
	वापस ti_sci_proc_set_control(core->tsp,
				       0, PROC_BOOT_CTRL_FLAG_R5_CORE_HALT);
पूर्ण

/*
 * The R5F cores have controls क्रम both a reset and a halt/run. The code
 * execution from DDR requires the initial boot-strapping code to be run
 * from the पूर्णांकernal TCMs. This function is used to release the resets on
 * applicable cores to allow loading पूर्णांकo the TCMs. The .prepare() ops is
 * invoked by remoteproc core beक्रमe any firmware loading, and is followed
 * by the .start() ops after loading to actually let the R5 cores run.
 */
अटल पूर्णांक k3_r5_rproc_prepare(काष्ठा rproc *rproc)
अणु
	काष्ठा k3_r5_rproc *kproc = rproc->priv;
	काष्ठा k3_r5_cluster *cluster = kproc->cluster;
	काष्ठा k3_r5_core *core = kproc->core;
	काष्ठा device *dev = kproc->dev;
	u32 ctrl = 0, cfg = 0, stat = 0;
	u64 boot_vec = 0;
	bool mem_init_dis;
	पूर्णांक ret;

	ret = ti_sci_proc_get_status(core->tsp, &boot_vec, &cfg, &ctrl, &stat);
	अगर (ret < 0)
		वापस ret;
	mem_init_dis = !!(cfg & PROC_BOOT_CFG_FLAG_R5_MEM_INIT_DIS);

	ret = (cluster->mode == CLUSTER_MODE_LOCKSTEP) ?
		k3_r5_lockstep_release(cluster) : k3_r5_split_release(core);
	अगर (ret) अणु
		dev_err(dev, "unable to enable cores for TCM loading, ret = %d\n",
			ret);
		वापस ret;
	पूर्ण

	/*
	 * Newer IP revisions like on J7200 SoCs support h/w स्वतः-initialization
	 * of TCMs, so there is no need to perक्रमm the s/w memzero. This bit is
	 * configurable through System Firmware, the शेष value करोes perक्रमm
	 * स्वतः-init, but account क्रम it in हाल it is disabled
	 */
	अगर (cluster->soc_data->tcm_ecc_स्वतःinit && !mem_init_dis) अणु
		dev_dbg(dev, "leveraging h/w init for TCM memories\n");
		वापस 0;
	पूर्ण

	/*
	 * Zero out both TCMs unconditionally (access from v8 Arm core is not
	 * affected by ATCM & BTCM enable configuration values) so that ECC
	 * can be effective on all TCM addresses.
	 */
	dev_dbg(dev, "zeroing out ATCM memory\n");
	स_रखो(core->mem[0].cpu_addr, 0x00, core->mem[0].size);

	dev_dbg(dev, "zeroing out BTCM memory\n");
	स_रखो(core->mem[1].cpu_addr, 0x00, core->mem[1].size);

	वापस 0;
पूर्ण

/*
 * This function implements the .unprepare() ops and perक्रमms the complimentary
 * operations to that of the .prepare() ops. The function is used to निश्चित the
 * resets on all applicable cores क्रम the rproc device (depending on LockStep
 * or Split mode). This completes the second portion of घातering करोwn the R5F
 * cores. The cores themselves are only halted in the .stop() ops, and the
 * .unprepare() ops is invoked by the remoteproc core after the remoteproc is
 * stopped.
 */
अटल पूर्णांक k3_r5_rproc_unprepare(काष्ठा rproc *rproc)
अणु
	काष्ठा k3_r5_rproc *kproc = rproc->priv;
	काष्ठा k3_r5_cluster *cluster = kproc->cluster;
	काष्ठा k3_r5_core *core = kproc->core;
	काष्ठा device *dev = kproc->dev;
	पूर्णांक ret;

	ret = (cluster->mode == CLUSTER_MODE_LOCKSTEP) ?
		k3_r5_lockstep_reset(cluster) : k3_r5_split_reset(core);
	अगर (ret)
		dev_err(dev, "unable to disable cores, ret = %d\n", ret);

	वापस ret;
पूर्ण

/*
 * The R5F start sequence includes two dअगरferent operations
 * 1. Configure the boot vector क्रम R5F core(s)
 * 2. Unhalt/Run the R5F core(s)
 *
 * The sequence is dअगरferent between LockStep and Split modes. The LockStep
 * mode requires the boot vector to be configured only क्रम Core0, and then
 * unhalt both the cores to start the execution - Core1 needs to be unhalted
 * first followed by Core0. The Split-mode requires that Core0 to be मुख्यtained
 * always in a higher घातer state that Core1 (implying Core1 needs to be started
 * always only after Core0 is started).
 */
अटल पूर्णांक k3_r5_rproc_start(काष्ठा rproc *rproc)
अणु
	काष्ठा k3_r5_rproc *kproc = rproc->priv;
	काष्ठा k3_r5_cluster *cluster = kproc->cluster;
	काष्ठा mbox_client *client = &kproc->client;
	काष्ठा device *dev = kproc->dev;
	काष्ठा k3_r5_core *core;
	u32 boot_addr;
	पूर्णांक ret;

	client->dev = dev;
	client->tx_करोne = शून्य;
	client->rx_callback = k3_r5_rproc_mbox_callback;
	client->tx_block = false;
	client->knows_txकरोne = false;

	kproc->mbox = mbox_request_channel(client, 0);
	अगर (IS_ERR(kproc->mbox)) अणु
		ret = -EBUSY;
		dev_err(dev, "mbox_request_channel failed: %ld\n",
			PTR_ERR(kproc->mbox));
		वापस ret;
	पूर्ण

	/*
	 * Ping the remote processor, this is only क्रम sanity-sake क्रम now;
	 * there is no functional effect whatsoever.
	 *
	 * Note that the reply will _not_ arrive immediately: this message
	 * will रुको in the mailbox fअगरo until the remote processor is booted.
	 */
	ret = mbox_send_message(kproc->mbox, (व्योम *)RP_MBOX_ECHO_REQUEST);
	अगर (ret < 0) अणु
		dev_err(dev, "mbox_send_message failed: %d\n", ret);
		जाओ put_mbox;
	पूर्ण

	boot_addr = rproc->bootaddr;
	/* TODO: add boot_addr sanity checking */
	dev_dbg(dev, "booting R5F core using boot addr = 0x%x\n", boot_addr);

	/* boot vector need not be programmed क्रम Core1 in LockStep mode */
	core = kproc->core;
	ret = ti_sci_proc_set_config(core->tsp, boot_addr, 0, 0);
	अगर (ret)
		जाओ put_mbox;

	/* unhalt/run all applicable cores */
	अगर (cluster->mode == CLUSTER_MODE_LOCKSTEP) अणु
		list_क्रम_each_entry_reverse(core, &cluster->cores, elem) अणु
			ret = k3_r5_core_run(core);
			अगर (ret)
				जाओ unroll_core_run;
		पूर्ण
	पूर्ण अन्यथा अणु
		ret = k3_r5_core_run(core);
		अगर (ret)
			जाओ put_mbox;
	पूर्ण

	वापस 0;

unroll_core_run:
	list_क्रम_each_entry_जारी(core, &cluster->cores, elem) अणु
		अगर (k3_r5_core_halt(core))
			dev_warn(core->dev, "core halt back failed\n");
	पूर्ण
put_mbox:
	mbox_मुक्त_channel(kproc->mbox);
	वापस ret;
पूर्ण

/*
 * The R5F stop function includes the following operations
 * 1. Halt R5F core(s)
 *
 * The sequence is dअगरferent between LockStep and Split modes, and the order
 * of cores the operations are perक्रमmed are also in general reverse to that
 * of the start function. The LockStep mode requires each operation to be
 * perक्रमmed first on Core0 followed by Core1. The Split-mode requires that
 * Core0 to be मुख्यtained always in a higher घातer state that Core1 (implying
 * Core1 needs to be stopped first beक्रमe Core0).
 *
 * Note that the R5F halt operation in general is not effective when the R5F
 * core is running, but is needed to make sure the core won't run after
 * deनिश्चितing the reset the subsequent समय. The निश्चितing of reset can
 * be करोne here, but is preferred to be करोne in the .unprepare() ops - this
 * मुख्यtains the symmetric behavior between the .start(), .stop(), .prepare()
 * and .unprepare() ops, and also balances them well between sysfs 'state'
 * flow and device bind/unbind or module removal.
 */
अटल पूर्णांक k3_r5_rproc_stop(काष्ठा rproc *rproc)
अणु
	काष्ठा k3_r5_rproc *kproc = rproc->priv;
	काष्ठा k3_r5_cluster *cluster = kproc->cluster;
	काष्ठा k3_r5_core *core = kproc->core;
	पूर्णांक ret;

	/* halt all applicable cores */
	अगर (cluster->mode == CLUSTER_MODE_LOCKSTEP) अणु
		list_क्रम_each_entry(core, &cluster->cores, elem) अणु
			ret = k3_r5_core_halt(core);
			अगर (ret) अणु
				core = list_prev_entry(core, elem);
				जाओ unroll_core_halt;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		ret = k3_r5_core_halt(core);
		अगर (ret)
			जाओ out;
	पूर्ण

	mbox_मुक्त_channel(kproc->mbox);

	वापस 0;

unroll_core_halt:
	list_क्रम_each_entry_from_reverse(core, &cluster->cores, elem) अणु
		अगर (k3_r5_core_run(core))
			dev_warn(core->dev, "core run back failed\n");
	पूर्ण
out:
	वापस ret;
पूर्ण

/*
 * Internal Memory translation helper
 *
 * Custom function implementing the rproc .da_to_va ops to provide address
 * translation (device address to kernel भव address) क्रम पूर्णांकernal RAMs
 * present in a DSP or IPU device). The translated addresses can be used
 * either by the remoteproc core क्रम loading, or by any rpmsg bus drivers.
 */
अटल व्योम *k3_r5_rproc_da_to_va(काष्ठा rproc *rproc, u64 da, माप_प्रकार len, bool *is_iomem)
अणु
	काष्ठा k3_r5_rproc *kproc = rproc->priv;
	काष्ठा k3_r5_core *core = kproc->core;
	व्योम __iomem *va = शून्य;
	phys_addr_t bus_addr;
	u32 dev_addr, offset;
	माप_प्रकार size;
	पूर्णांक i;

	अगर (len == 0)
		वापस शून्य;

	/* handle both R5 and SoC views of ATCM and BTCM */
	क्रम (i = 0; i < core->num_mems; i++) अणु
		bus_addr = core->mem[i].bus_addr;
		dev_addr = core->mem[i].dev_addr;
		size = core->mem[i].size;

		/* handle R5-view addresses of TCMs */
		अगर (da >= dev_addr && ((da + len) <= (dev_addr + size))) अणु
			offset = da - dev_addr;
			va = core->mem[i].cpu_addr + offset;
			वापस (__क्रमce व्योम *)va;
		पूर्ण

		/* handle SoC-view addresses of TCMs */
		अगर (da >= bus_addr && ((da + len) <= (bus_addr + size))) अणु
			offset = da - bus_addr;
			va = core->mem[i].cpu_addr + offset;
			वापस (__क्रमce व्योम *)va;
		पूर्ण
	पूर्ण

	/* handle any SRAM regions using SoC-view addresses */
	क्रम (i = 0; i < core->num_sram; i++) अणु
		dev_addr = core->sram[i].dev_addr;
		size = core->sram[i].size;

		अगर (da >= dev_addr && ((da + len) <= (dev_addr + size))) अणु
			offset = da - dev_addr;
			va = core->sram[i].cpu_addr + offset;
			वापस (__क्रमce व्योम *)va;
		पूर्ण
	पूर्ण

	/* handle अटल DDR reserved memory regions */
	क्रम (i = 0; i < kproc->num_rmems; i++) अणु
		dev_addr = kproc->rmem[i].dev_addr;
		size = kproc->rmem[i].size;

		अगर (da >= dev_addr && ((da + len) <= (dev_addr + size))) अणु
			offset = da - dev_addr;
			va = kproc->rmem[i].cpu_addr + offset;
			वापस (__क्रमce व्योम *)va;
		पूर्ण
	पूर्ण

	वापस शून्य;
पूर्ण

अटल स्थिर काष्ठा rproc_ops k3_r5_rproc_ops = अणु
	.prepare	= k3_r5_rproc_prepare,
	.unprepare	= k3_r5_rproc_unprepare,
	.start		= k3_r5_rproc_start,
	.stop		= k3_r5_rproc_stop,
	.kick		= k3_r5_rproc_kick,
	.da_to_va	= k3_r5_rproc_da_to_va,
पूर्ण;

/*
 * Internal R5F Core configuration
 *
 * Each R5FSS has a cluster-level setting क्रम configuring the processor
 * subप्रणाली either in a safety/fault-tolerant LockStep mode or a perक्रमmance
 * oriented Split mode. Each R5F core has a number of settings to either
 * enable/disable each of the TCMs, control which TCM appears at the R5F core's
 * address 0x0. These settings need to be configured beक्रमe the resets क्रम the
 * corresponding core are released. These settings are all रक्षित and managed
 * by the System Processor.
 *
 * This function is used to pre-configure these settings क्रम each R5F core, and
 * the configuration is all करोne through various ti_sci_proc functions that
 * communicate with the System Processor. The function also ensures that both
 * the cores are halted beक्रमe the .prepare() step.
 *
 * The function is called from k3_r5_cluster_rproc_init() and is invoked either
 * once (in LockStep mode) or twice (in Split mode). Support क्रम LockStep-mode
 * is dictated by an eFUSE रेजिस्टर bit, and the config settings retrieved from
 * DT are adjusted accordingly as per the permitted cluster mode. All cluster
 * level settings like Cluster mode and TEINIT (exception handling state
 * dictating ARM or Thumb mode) can only be set and retrieved using Core0.
 *
 * The function behavior is dअगरferent based on the cluster mode. The R5F cores
 * are configured independently as per their inभागidual settings in Split mode.
 * They are identically configured in LockStep mode using the primary Core0
 * settings. However, some inभागidual settings cannot be set in LockStep mode.
 * This is overcome by चयनing to Split-mode initially and then programming
 * both the cores with the same settings, beक्रमe reconfiguing again क्रम
 * LockStep mode.
 */
अटल पूर्णांक k3_r5_rproc_configure(काष्ठा k3_r5_rproc *kproc)
अणु
	काष्ठा k3_r5_cluster *cluster = kproc->cluster;
	काष्ठा device *dev = kproc->dev;
	काष्ठा k3_r5_core *core0, *core, *temp;
	u32 ctrl = 0, cfg = 0, stat = 0;
	u32 set_cfg = 0, clr_cfg = 0;
	u64 boot_vec = 0;
	bool lockstep_en;
	पूर्णांक ret;

	core0 = list_first_entry(&cluster->cores, काष्ठा k3_r5_core, elem);
	core = (cluster->mode == CLUSTER_MODE_LOCKSTEP) ? core0 : kproc->core;

	ret = ti_sci_proc_get_status(core->tsp, &boot_vec, &cfg, &ctrl,
				     &stat);
	अगर (ret < 0)
		वापस ret;

	dev_dbg(dev, "boot_vector = 0x%llx, cfg = 0x%x ctrl = 0x%x stat = 0x%x\n",
		boot_vec, cfg, ctrl, stat);

	lockstep_en = !!(stat & PROC_BOOT_STATUS_FLAG_R5_LOCKSTEP_PERMITTED);
	अगर (!lockstep_en && cluster->mode == CLUSTER_MODE_LOCKSTEP) अणु
		dev_err(cluster->dev, "lockstep mode not permitted, force configuring for split-mode\n");
		cluster->mode = CLUSTER_MODE_SPLIT;
	पूर्ण

	/* always enable ARM mode and set boot vector to 0 */
	boot_vec = 0x0;
	अगर (core == core0) अणु
		clr_cfg = PROC_BOOT_CFG_FLAG_R5_TEINIT;
		/*
		 * LockStep configuration bit is Read-only on Split-mode _only_
		 * devices and प्रणाली firmware will NACK any requests with the
		 * bit configured, so program it only on permitted devices
		 */
		अगर (lockstep_en)
			clr_cfg |= PROC_BOOT_CFG_FLAG_R5_LOCKSTEP;
	पूर्ण

	अगर (core->atcm_enable)
		set_cfg |= PROC_BOOT_CFG_FLAG_R5_ATCM_EN;
	अन्यथा
		clr_cfg |= PROC_BOOT_CFG_FLAG_R5_ATCM_EN;

	अगर (core->btcm_enable)
		set_cfg |= PROC_BOOT_CFG_FLAG_R5_BTCM_EN;
	अन्यथा
		clr_cfg |= PROC_BOOT_CFG_FLAG_R5_BTCM_EN;

	अगर (core->loczrama)
		set_cfg |= PROC_BOOT_CFG_FLAG_R5_TCM_RSTBASE;
	अन्यथा
		clr_cfg |= PROC_BOOT_CFG_FLAG_R5_TCM_RSTBASE;

	अगर (cluster->mode == CLUSTER_MODE_LOCKSTEP) अणु
		/*
		 * work around प्रणाली firmware limitations to make sure both
		 * cores are programmed symmetrically in LockStep. LockStep
		 * and TEINIT config is only allowed with Core0.
		 */
		list_क्रम_each_entry(temp, &cluster->cores, elem) अणु
			ret = k3_r5_core_halt(temp);
			अगर (ret)
				जाओ out;

			अगर (temp != core) अणु
				clr_cfg &= ~PROC_BOOT_CFG_FLAG_R5_LOCKSTEP;
				clr_cfg &= ~PROC_BOOT_CFG_FLAG_R5_TEINIT;
			पूर्ण
			ret = ti_sci_proc_set_config(temp->tsp, boot_vec,
						     set_cfg, clr_cfg);
			अगर (ret)
				जाओ out;
		पूर्ण

		set_cfg = PROC_BOOT_CFG_FLAG_R5_LOCKSTEP;
		clr_cfg = 0;
		ret = ti_sci_proc_set_config(core->tsp, boot_vec,
					     set_cfg, clr_cfg);
	पूर्ण अन्यथा अणु
		ret = k3_r5_core_halt(core);
		अगर (ret)
			जाओ out;

		ret = ti_sci_proc_set_config(core->tsp, boot_vec,
					     set_cfg, clr_cfg);
	पूर्ण

out:
	वापस ret;
पूर्ण

अटल पूर्णांक k3_r5_reserved_mem_init(काष्ठा k3_r5_rproc *kproc)
अणु
	काष्ठा device *dev = kproc->dev;
	काष्ठा device_node *np = dev_of_node(dev);
	काष्ठा device_node *rmem_np;
	काष्ठा reserved_mem *rmem;
	पूर्णांक num_rmems;
	पूर्णांक ret, i;

	num_rmems = of_property_count_elems_of_size(np, "memory-region",
						    माप(phandle));
	अगर (num_rmems <= 0) अणु
		dev_err(dev, "device does not have reserved memory regions, ret = %d\n",
			num_rmems);
		वापस -EINVAL;
	पूर्ण
	अगर (num_rmems < 2) अणु
		dev_err(dev, "device needs atleast two memory regions to be defined, num = %d\n",
			num_rmems);
		वापस -EINVAL;
	पूर्ण

	/* use reserved memory region 0 क्रम vring DMA allocations */
	ret = of_reserved_mem_device_init_by_idx(dev, np, 0);
	अगर (ret) अणु
		dev_err(dev, "device cannot initialize DMA pool, ret = %d\n",
			ret);
		वापस ret;
	पूर्ण

	num_rmems--;
	kproc->rmem = kसुस्मृति(num_rmems, माप(*kproc->rmem), GFP_KERNEL);
	अगर (!kproc->rmem) अणु
		ret = -ENOMEM;
		जाओ release_rmem;
	पूर्ण

	/* use reमुख्यing reserved memory regions क्रम अटल carveouts */
	क्रम (i = 0; i < num_rmems; i++) अणु
		rmem_np = of_parse_phandle(np, "memory-region", i + 1);
		अगर (!rmem_np) अणु
			ret = -EINVAL;
			जाओ unmap_rmem;
		पूर्ण

		rmem = of_reserved_mem_lookup(rmem_np);
		अगर (!rmem) अणु
			of_node_put(rmem_np);
			ret = -EINVAL;
			जाओ unmap_rmem;
		पूर्ण
		of_node_put(rmem_np);

		kproc->rmem[i].bus_addr = rmem->base;
		/*
		 * R5Fs करो not have an MMU, but have a Region Address Translator
		 * (RAT) module that provides a fixed entry translation between
		 * the 32-bit processor addresses to 64-bit bus addresses. The
		 * RAT is programmable only by the R5F cores. Support क्रम RAT
		 * is currently not supported, so 64-bit address regions are not
		 * supported. The असलence of MMUs implies that the R5F device
		 * addresses/supported memory regions are restricted to 32-bit
		 * bus addresses, and are identical
		 */
		kproc->rmem[i].dev_addr = (u32)rmem->base;
		kproc->rmem[i].size = rmem->size;
		kproc->rmem[i].cpu_addr = ioremap_wc(rmem->base, rmem->size);
		अगर (!kproc->rmem[i].cpu_addr) अणु
			dev_err(dev, "failed to map reserved memory#%d at %pa of size %pa\n",
				i + 1, &rmem->base, &rmem->size);
			ret = -ENOMEM;
			जाओ unmap_rmem;
		पूर्ण

		dev_dbg(dev, "reserved memory%d: bus addr %pa size 0x%zx va %pK da 0x%x\n",
			i + 1, &kproc->rmem[i].bus_addr,
			kproc->rmem[i].size, kproc->rmem[i].cpu_addr,
			kproc->rmem[i].dev_addr);
	पूर्ण
	kproc->num_rmems = num_rmems;

	वापस 0;

unmap_rmem:
	क्रम (i--; i >= 0; i--)
		iounmap(kproc->rmem[i].cpu_addr);
	kमुक्त(kproc->rmem);
release_rmem:
	of_reserved_mem_device_release(dev);
	वापस ret;
पूर्ण

अटल व्योम k3_r5_reserved_mem_निकास(काष्ठा k3_r5_rproc *kproc)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < kproc->num_rmems; i++)
		iounmap(kproc->rmem[i].cpu_addr);
	kमुक्त(kproc->rmem);

	of_reserved_mem_device_release(kproc->dev);
पूर्ण

/*
 * Each R5F core within a typical R5FSS instance has a total of 64 KB of TCMs,
 * split equally पूर्णांकo two 32 KB banks between ATCM and BTCM. The TCMs from both
 * cores are usable in Split-mode, but only the Core0 TCMs can be used in
 * LockStep-mode. The newer revisions of the R5FSS IP maximizes these TCMs by
 * leveraging the Core1 TCMs as well in certain modes where they would have
 * otherwise been unusable (Eg: LockStep-mode on J7200 SoCs). This is करोne by
 * making a Core1 TCM visible immediately after the corresponding Core0 TCM.
 * The SoC memory map uses the larger 64 KB sizes क्रम the Core0 TCMs, and the
 * dts representation reflects this increased size on supported SoCs. The Core0
 * TCM sizes thereक्रमe have to be adjusted to only half the original size in
 * Split mode.
 */
अटल व्योम k3_r5_adjust_tcm_sizes(काष्ठा k3_r5_rproc *kproc)
अणु
	काष्ठा k3_r5_cluster *cluster = kproc->cluster;
	काष्ठा k3_r5_core *core = kproc->core;
	काष्ठा device *cdev = core->dev;
	काष्ठा k3_r5_core *core0;

	अगर (cluster->mode == CLUSTER_MODE_LOCKSTEP ||
	    !cluster->soc_data->tcm_is_द्विगुन)
		वापस;

	core0 = list_first_entry(&cluster->cores, काष्ठा k3_r5_core, elem);
	अगर (core == core0) अणु
		WARN_ON(core->mem[0].size != SZ_64K);
		WARN_ON(core->mem[1].size != SZ_64K);

		core->mem[0].size /= 2;
		core->mem[1].size /= 2;

		dev_dbg(cdev, "adjusted TCM sizes, ATCM = 0x%zx BTCM = 0x%zx\n",
			core->mem[0].size, core->mem[1].size);
	पूर्ण
पूर्ण

अटल पूर्णांक k3_r5_cluster_rproc_init(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा k3_r5_cluster *cluster = platक्रमm_get_drvdata(pdev);
	काष्ठा device *dev = &pdev->dev;
	काष्ठा k3_r5_rproc *kproc;
	काष्ठा k3_r5_core *core, *core1;
	काष्ठा device *cdev;
	स्थिर अक्षर *fw_name;
	काष्ठा rproc *rproc;
	पूर्णांक ret;

	core1 = list_last_entry(&cluster->cores, काष्ठा k3_r5_core, elem);
	list_क्रम_each_entry(core, &cluster->cores, elem) अणु
		cdev = core->dev;
		ret = rproc_of_parse_firmware(cdev, 0, &fw_name);
		अगर (ret) अणु
			dev_err(dev, "failed to parse firmware-name property, ret = %d\n",
				ret);
			जाओ out;
		पूर्ण

		rproc = rproc_alloc(cdev, dev_name(cdev), &k3_r5_rproc_ops,
				    fw_name, माप(*kproc));
		अगर (!rproc) अणु
			ret = -ENOMEM;
			जाओ out;
		पूर्ण

		/* K3 R5s have a Region Address Translator (RAT) but no MMU */
		rproc->has_iommu = false;
		/* error recovery is not supported at present */
		rproc->recovery_disabled = true;

		kproc = rproc->priv;
		kproc->cluster = cluster;
		kproc->core = core;
		kproc->dev = cdev;
		kproc->rproc = rproc;
		core->rproc = rproc;

		ret = k3_r5_rproc_configure(kproc);
		अगर (ret) अणु
			dev_err(dev, "initial configure failed, ret = %d\n",
				ret);
			जाओ err_config;
		पूर्ण

		k3_r5_adjust_tcm_sizes(kproc);

		ret = k3_r5_reserved_mem_init(kproc);
		अगर (ret) अणु
			dev_err(dev, "reserved memory init failed, ret = %d\n",
				ret);
			जाओ err_config;
		पूर्ण

		ret = rproc_add(rproc);
		अगर (ret) अणु
			dev_err(dev, "rproc_add failed, ret = %d\n", ret);
			जाओ err_add;
		पूर्ण

		/* create only one rproc in lockstep mode */
		अगर (cluster->mode == CLUSTER_MODE_LOCKSTEP)
			अवरोध;
	पूर्ण

	वापस 0;

err_split:
	rproc_del(rproc);
err_add:
	k3_r5_reserved_mem_निकास(kproc);
err_config:
	rproc_मुक्त(rproc);
	core->rproc = शून्य;
out:
	/* unकरो core0 upon any failures on core1 in split-mode */
	अगर (cluster->mode == CLUSTER_MODE_SPLIT && core == core1) अणु
		core = list_prev_entry(core, elem);
		rproc = core->rproc;
		kproc = rproc->priv;
		जाओ err_split;
	पूर्ण
	वापस ret;
पूर्ण

अटल व्योम k3_r5_cluster_rproc_निकास(व्योम *data)
अणु
	काष्ठा k3_r5_cluster *cluster = platक्रमm_get_drvdata(data);
	काष्ठा k3_r5_rproc *kproc;
	काष्ठा k3_r5_core *core;
	काष्ठा rproc *rproc;

	/*
	 * lockstep mode has only one rproc associated with first core, whereas
	 * split-mode has two rprocs associated with each core, and requires
	 * that core1 be घातered करोwn first
	 */
	core = (cluster->mode == CLUSTER_MODE_LOCKSTEP) ?
		list_first_entry(&cluster->cores, काष्ठा k3_r5_core, elem) :
		list_last_entry(&cluster->cores, काष्ठा k3_r5_core, elem);

	list_क्रम_each_entry_from_reverse(core, &cluster->cores, elem) अणु
		rproc = core->rproc;
		kproc = rproc->priv;

		rproc_del(rproc);

		k3_r5_reserved_mem_निकास(kproc);

		rproc_मुक्त(rproc);
		core->rproc = शून्य;
	पूर्ण
पूर्ण

अटल पूर्णांक k3_r5_core_of_get_पूर्णांकernal_memories(काष्ठा platक्रमm_device *pdev,
					       काष्ठा k3_r5_core *core)
अणु
	अटल स्थिर अक्षर * स्थिर mem_names[] = अणु"atcm", "btcm"पूर्ण;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा resource *res;
	पूर्णांक num_mems;
	पूर्णांक i;

	num_mems = ARRAY_SIZE(mem_names);
	core->mem = devm_kसुस्मृति(dev, num_mems, माप(*core->mem), GFP_KERNEL);
	अगर (!core->mem)
		वापस -ENOMEM;

	क्रम (i = 0; i < num_mems; i++) अणु
		res = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM,
						   mem_names[i]);
		अगर (!res) अणु
			dev_err(dev, "found no memory resource for %s\n",
				mem_names[i]);
			वापस -EINVAL;
		पूर्ण
		अगर (!devm_request_mem_region(dev, res->start,
					     resource_size(res),
					     dev_name(dev))) अणु
			dev_err(dev, "could not request %s region for resource\n",
				mem_names[i]);
			वापस -EBUSY;
		पूर्ण

		/*
		 * TCMs are deचिन्हित in general to support RAM-like backing
		 * memories. So, map these as Normal Non-Cached memories. This
		 * also aव्योमs/fixes any potential alignment faults due to
		 * unaligned data accesses when using स_नकल() or स_रखो()
		 * functions (normally seen with device type memory).
		 */
		core->mem[i].cpu_addr = devm_ioremap_wc(dev, res->start,
							resource_size(res));
		अगर (!core->mem[i].cpu_addr) अणु
			dev_err(dev, "failed to map %s memory\n", mem_names[i]);
			वापस -ENOMEM;
		पूर्ण
		core->mem[i].bus_addr = res->start;

		/*
		 * TODO:
		 * The R5F cores can place ATCM & BTCM anywhere in its address
		 * based on the corresponding Region Registers in the System
		 * Control coprocessor. For now, place ATCM and BTCM at
		 * addresses 0 and 0x41010000 (same as the bus address on AM65x
		 * SoCs) based on loczrama setting
		 */
		अगर (!म_भेद(mem_names[i], "atcm")) अणु
			core->mem[i].dev_addr = core->loczrama ?
							0 : K3_R5_TCM_DEV_ADDR;
		पूर्ण अन्यथा अणु
			core->mem[i].dev_addr = core->loczrama ?
							K3_R5_TCM_DEV_ADDR : 0;
		पूर्ण
		core->mem[i].size = resource_size(res);

		dev_dbg(dev, "memory %5s: bus addr %pa size 0x%zx va %pK da 0x%x\n",
			mem_names[i], &core->mem[i].bus_addr,
			core->mem[i].size, core->mem[i].cpu_addr,
			core->mem[i].dev_addr);
	पूर्ण
	core->num_mems = num_mems;

	वापस 0;
पूर्ण

अटल पूर्णांक k3_r5_core_of_get_sram_memories(काष्ठा platक्रमm_device *pdev,
					   काष्ठा k3_r5_core *core)
अणु
	काष्ठा device_node *np = pdev->dev.of_node;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा device_node *sram_np;
	काष्ठा resource res;
	पूर्णांक num_sram;
	पूर्णांक i, ret;

	num_sram = of_property_count_elems_of_size(np, "sram", माप(phandle));
	अगर (num_sram <= 0) अणु
		dev_dbg(dev, "device does not use reserved on-chip memories, num_sram = %d\n",
			num_sram);
		वापस 0;
	पूर्ण

	core->sram = devm_kसुस्मृति(dev, num_sram, माप(*core->sram), GFP_KERNEL);
	अगर (!core->sram)
		वापस -ENOMEM;

	क्रम (i = 0; i < num_sram; i++) अणु
		sram_np = of_parse_phandle(np, "sram", i);
		अगर (!sram_np)
			वापस -EINVAL;

		अगर (!of_device_is_available(sram_np)) अणु
			of_node_put(sram_np);
			वापस -EINVAL;
		पूर्ण

		ret = of_address_to_resource(sram_np, 0, &res);
		of_node_put(sram_np);
		अगर (ret)
			वापस -EINVAL;

		core->sram[i].bus_addr = res.start;
		core->sram[i].dev_addr = res.start;
		core->sram[i].size = resource_size(&res);
		core->sram[i].cpu_addr = devm_ioremap_wc(dev, res.start,
							 resource_size(&res));
		अगर (!core->sram[i].cpu_addr) अणु
			dev_err(dev, "failed to parse and map sram%d memory at %pad\n",
				i, &res.start);
			वापस -ENOMEM;
		पूर्ण

		dev_dbg(dev, "memory sram%d: bus addr %pa size 0x%zx va %pK da 0x%x\n",
			i, &core->sram[i].bus_addr,
			core->sram[i].size, core->sram[i].cpu_addr,
			core->sram[i].dev_addr);
	पूर्ण
	core->num_sram = num_sram;

	वापस 0;
पूर्ण

अटल
काष्ठा ti_sci_proc *k3_r5_core_of_get_tsp(काष्ठा device *dev,
					  स्थिर काष्ठा ti_sci_handle *sci)
अणु
	काष्ठा ti_sci_proc *tsp;
	u32 temp[2];
	पूर्णांक ret;

	ret = of_property_पढ़ो_u32_array(dev_of_node(dev), "ti,sci-proc-ids",
					 temp, 2);
	अगर (ret < 0)
		वापस ERR_PTR(ret);

	tsp = devm_kzalloc(dev, माप(*tsp), GFP_KERNEL);
	अगर (!tsp)
		वापस ERR_PTR(-ENOMEM);

	tsp->dev = dev;
	tsp->sci = sci;
	tsp->ops = &sci->ops.proc_ops;
	tsp->proc_id = temp[0];
	tsp->host_id = temp[1];

	वापस tsp;
पूर्ण

अटल पूर्णांक k3_r5_core_of_init(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा device_node *np = dev_of_node(dev);
	काष्ठा k3_r5_core *core;
	पूर्णांक ret;

	अगर (!devres_खोलो_group(dev, k3_r5_core_of_init, GFP_KERNEL))
		वापस -ENOMEM;

	core = devm_kzalloc(dev, माप(*core), GFP_KERNEL);
	अगर (!core) अणु
		ret = -ENOMEM;
		जाओ err;
	पूर्ण

	core->dev = dev;
	/*
	 * Use SoC Power-on-Reset values as शेष अगर no DT properties are
	 * used to dictate the TCM configurations
	 */
	core->atcm_enable = 0;
	core->btcm_enable = 1;
	core->loczrama = 1;

	ret = of_property_पढ़ो_u32(np, "ti,atcm-enable", &core->atcm_enable);
	अगर (ret < 0 && ret != -EINVAL) अणु
		dev_err(dev, "invalid format for ti,atcm-enable, ret = %d\n",
			ret);
		जाओ err;
	पूर्ण

	ret = of_property_पढ़ो_u32(np, "ti,btcm-enable", &core->btcm_enable);
	अगर (ret < 0 && ret != -EINVAL) अणु
		dev_err(dev, "invalid format for ti,btcm-enable, ret = %d\n",
			ret);
		जाओ err;
	पूर्ण

	ret = of_property_पढ़ो_u32(np, "ti,loczrama", &core->loczrama);
	अगर (ret < 0 && ret != -EINVAL) अणु
		dev_err(dev, "invalid format for ti,loczrama, ret = %d\n", ret);
		जाओ err;
	पूर्ण

	core->ti_sci = devm_ti_sci_get_by_phandle(dev, "ti,sci");
	अगर (IS_ERR(core->ti_sci)) अणु
		ret = PTR_ERR(core->ti_sci);
		अगर (ret != -EPROBE_DEFER) अणु
			dev_err(dev, "failed to get ti-sci handle, ret = %d\n",
				ret);
		पूर्ण
		core->ti_sci = शून्य;
		जाओ err;
	पूर्ण

	ret = of_property_पढ़ो_u32(np, "ti,sci-dev-id", &core->ti_sci_id);
	अगर (ret) अणु
		dev_err(dev, "missing 'ti,sci-dev-id' property\n");
		जाओ err;
	पूर्ण

	core->reset = devm_reset_control_get_exclusive(dev, शून्य);
	अगर (IS_ERR_OR_शून्य(core->reset)) अणु
		ret = PTR_ERR_OR_ZERO(core->reset);
		अगर (!ret)
			ret = -ENODEV;
		अगर (ret != -EPROBE_DEFER) अणु
			dev_err(dev, "failed to get reset handle, ret = %d\n",
				ret);
		पूर्ण
		जाओ err;
	पूर्ण

	core->tsp = k3_r5_core_of_get_tsp(dev, core->ti_sci);
	अगर (IS_ERR(core->tsp)) अणु
		dev_err(dev, "failed to construct ti-sci proc control, ret = %d\n",
			ret);
		ret = PTR_ERR(core->tsp);
		जाओ err;
	पूर्ण

	ret = k3_r5_core_of_get_पूर्णांकernal_memories(pdev, core);
	अगर (ret) अणु
		dev_err(dev, "failed to get internal memories, ret = %d\n",
			ret);
		जाओ err;
	पूर्ण

	ret = k3_r5_core_of_get_sram_memories(pdev, core);
	अगर (ret) अणु
		dev_err(dev, "failed to get sram memories, ret = %d\n", ret);
		जाओ err;
	पूर्ण

	ret = ti_sci_proc_request(core->tsp);
	अगर (ret < 0) अणु
		dev_err(dev, "ti_sci_proc_request failed, ret = %d\n", ret);
		जाओ err;
	पूर्ण

	platक्रमm_set_drvdata(pdev, core);
	devres_बंद_group(dev, k3_r5_core_of_init);

	वापस 0;

err:
	devres_release_group(dev, k3_r5_core_of_init);
	वापस ret;
पूर्ण

/*
 * मुक्त the resources explicitly since driver model is not being used
 * क्रम the child R5F devices
 */
अटल व्योम k3_r5_core_of_निकास(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा k3_r5_core *core = platक्रमm_get_drvdata(pdev);
	काष्ठा device *dev = &pdev->dev;
	पूर्णांक ret;

	ret = ti_sci_proc_release(core->tsp);
	अगर (ret)
		dev_err(dev, "failed to release proc, ret = %d\n", ret);

	platक्रमm_set_drvdata(pdev, शून्य);
	devres_release_group(dev, k3_r5_core_of_init);
पूर्ण

अटल व्योम k3_r5_cluster_of_निकास(व्योम *data)
अणु
	काष्ठा k3_r5_cluster *cluster = platक्रमm_get_drvdata(data);
	काष्ठा platक्रमm_device *cpdev;
	काष्ठा k3_r5_core *core, *temp;

	list_क्रम_each_entry_safe_reverse(core, temp, &cluster->cores, elem) अणु
		list_del(&core->elem);
		cpdev = to_platक्रमm_device(core->dev);
		k3_r5_core_of_निकास(cpdev);
	पूर्ण
पूर्ण

अटल पूर्णांक k3_r5_cluster_of_init(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा k3_r5_cluster *cluster = platक्रमm_get_drvdata(pdev);
	काष्ठा device *dev = &pdev->dev;
	काष्ठा device_node *np = dev_of_node(dev);
	काष्ठा platक्रमm_device *cpdev;
	काष्ठा device_node *child;
	काष्ठा k3_r5_core *core;
	पूर्णांक ret;

	क्रम_each_available_child_of_node(np, child) अणु
		cpdev = of_find_device_by_node(child);
		अगर (!cpdev) अणु
			ret = -ENODEV;
			dev_err(dev, "could not get R5 core platform device\n");
			जाओ fail;
		पूर्ण

		ret = k3_r5_core_of_init(cpdev);
		अगर (ret) अणु
			dev_err(dev, "k3_r5_core_of_init failed, ret = %d\n",
				ret);
			put_device(&cpdev->dev);
			जाओ fail;
		पूर्ण

		core = platक्रमm_get_drvdata(cpdev);
		put_device(&cpdev->dev);
		list_add_tail(&core->elem, &cluster->cores);
	पूर्ण

	वापस 0;

fail:
	k3_r5_cluster_of_निकास(pdev);
	वापस ret;
पूर्ण

अटल पूर्णांक k3_r5_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा device_node *np = dev_of_node(dev);
	काष्ठा k3_r5_cluster *cluster;
	स्थिर काष्ठा k3_r5_soc_data *data;
	पूर्णांक ret;
	पूर्णांक num_cores;

	data = of_device_get_match_data(&pdev->dev);
	अगर (!data) अणु
		dev_err(dev, "SoC-specific data is not defined\n");
		वापस -ENODEV;
	पूर्ण

	cluster = devm_kzalloc(dev, माप(*cluster), GFP_KERNEL);
	अगर (!cluster)
		वापस -ENOMEM;

	cluster->dev = dev;
	cluster->mode = CLUSTER_MODE_LOCKSTEP;
	cluster->soc_data = data;
	INIT_LIST_HEAD(&cluster->cores);

	ret = of_property_पढ़ो_u32(np, "ti,cluster-mode", &cluster->mode);
	अगर (ret < 0 && ret != -EINVAL) अणु
		dev_err(dev, "invalid format for ti,cluster-mode, ret = %d\n",
			ret);
		वापस ret;
	पूर्ण

	num_cores = of_get_available_child_count(np);
	अगर (num_cores != 2) अणु
		dev_err(dev, "MCU cluster requires both R5F cores to be enabled, num_cores = %d\n",
			num_cores);
		वापस -ENODEV;
	पूर्ण

	platक्रमm_set_drvdata(pdev, cluster);

	ret = devm_of_platक्रमm_populate(dev);
	अगर (ret) अणु
		dev_err(dev, "devm_of_platform_populate failed, ret = %d\n",
			ret);
		वापस ret;
	पूर्ण

	ret = k3_r5_cluster_of_init(pdev);
	अगर (ret) अणु
		dev_err(dev, "k3_r5_cluster_of_init failed, ret = %d\n", ret);
		वापस ret;
	पूर्ण

	ret = devm_add_action_or_reset(dev, k3_r5_cluster_of_निकास, pdev);
	अगर (ret)
		वापस ret;

	ret = k3_r5_cluster_rproc_init(pdev);
	अगर (ret) अणु
		dev_err(dev, "k3_r5_cluster_rproc_init failed, ret = %d\n",
			ret);
		वापस ret;
	पूर्ण

	ret = devm_add_action_or_reset(dev, k3_r5_cluster_rproc_निकास, pdev);
	अगर (ret)
		वापस ret;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा k3_r5_soc_data am65_j721e_soc_data = अणु
	.tcm_is_द्विगुन = false,
	.tcm_ecc_स्वतःinit = false,
पूर्ण;

अटल स्थिर काष्ठा k3_r5_soc_data j7200_soc_data = अणु
	.tcm_is_द्विगुन = true,
	.tcm_ecc_स्वतःinit = true,
पूर्ण;

अटल स्थिर काष्ठा of_device_id k3_r5_of_match[] = अणु
	अणु .compatible = "ti,am654-r5fss", .data = &am65_j721e_soc_data, पूर्ण,
	अणु .compatible = "ti,j721e-r5fss", .data = &am65_j721e_soc_data, पूर्ण,
	अणु .compatible = "ti,j7200-r5fss", .data = &j7200_soc_data, पूर्ण,
	अणु /* sentinel */ पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, k3_r5_of_match);

अटल काष्ठा platक्रमm_driver k3_r5_rproc_driver = अणु
	.probe = k3_r5_probe,
	.driver = अणु
		.name = "k3_r5_rproc",
		.of_match_table = k3_r5_of_match,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(k3_r5_rproc_driver);

MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("TI K3 R5F remote processor driver");
MODULE_AUTHOR("Suman Anna <s-anna@ti.com>");
