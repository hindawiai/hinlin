<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * TI K3 DSP Remote Processor(s) driver
 *
 * Copyright (C) 2018-2020 Texas Instruments Incorporated - https://www.ti.com/
 *	Suman Anna <s-anna@ti.com>
 */

#समावेश <linux/पन.स>
#समावेश <linux/mailbox_client.h>
#समावेश <linux/module.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_reserved_स्मृति.स>
#समावेश <linux/omap-mailbox.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/remoteproc.h>
#समावेश <linux/reset.h>
#समावेश <linux/slab.h>

#समावेश "omap_remoteproc.h"
#समावेश "remoteproc_internal.h"
#समावेश "ti_sci_proc.h"

#घोषणा KEYSTONE_RPROC_LOCAL_ADDRESS_MASK	(SZ_16M - 1)

/**
 * काष्ठा k3_dsp_mem - पूर्णांकernal memory काष्ठाure
 * @cpu_addr: MPU भव address of the memory region
 * @bus_addr: Bus address used to access the memory region
 * @dev_addr: Device address of the memory region from DSP view
 * @size: Size of the memory region
 */
काष्ठा k3_dsp_mem अणु
	व्योम __iomem *cpu_addr;
	phys_addr_t bus_addr;
	u32 dev_addr;
	माप_प्रकार size;
पूर्ण;

/**
 * काष्ठा k3_dsp_mem_data - memory definitions क्रम a DSP
 * @name: name क्रम this memory entry
 * @dev_addr: device address क्रम the memory entry
 */
काष्ठा k3_dsp_mem_data अणु
	स्थिर अक्षर *name;
	स्थिर u32 dev_addr;
पूर्ण;

/**
 * काष्ठा k3_dsp_dev_data - device data काष्ठाure क्रम a DSP
 * @mems: poपूर्णांकer to memory definitions क्रम a DSP
 * @num_mems: number of memory regions in @mems
 * @boot_align_addr: boot vector address alignment granularity
 * @uses_lreset: flag to denote the need क्रम local reset management
 */
काष्ठा k3_dsp_dev_data अणु
	स्थिर काष्ठा k3_dsp_mem_data *mems;
	u32 num_mems;
	u32 boot_align_addr;
	bool uses_lreset;
पूर्ण;

/**
 * काष्ठा k3_dsp_rproc - k3 DSP remote processor driver काष्ठाure
 * @dev: cached device poपूर्णांकer
 * @rproc: remoteproc device handle
 * @mem: पूर्णांकernal memory regions data
 * @num_mems: number of पूर्णांकernal memory regions
 * @rmem: reserved memory regions data
 * @num_rmems: number of reserved memory regions
 * @reset: reset control handle
 * @data: poपूर्णांकer to DSP-specअगरic device data
 * @tsp: TI-SCI processor control handle
 * @ti_sci: TI-SCI handle
 * @ti_sci_id: TI-SCI device identअगरier
 * @mbox: mailbox channel handle
 * @client: mailbox client to request the mailbox channel
 */
काष्ठा k3_dsp_rproc अणु
	काष्ठा device *dev;
	काष्ठा rproc *rproc;
	काष्ठा k3_dsp_mem *mem;
	पूर्णांक num_mems;
	काष्ठा k3_dsp_mem *rmem;
	पूर्णांक num_rmems;
	काष्ठा reset_control *reset;
	स्थिर काष्ठा k3_dsp_dev_data *data;
	काष्ठा ti_sci_proc *tsp;
	स्थिर काष्ठा ti_sci_handle *ti_sci;
	u32 ti_sci_id;
	काष्ठा mbox_chan *mbox;
	काष्ठा mbox_client client;
पूर्ण;

/**
 * k3_dsp_rproc_mbox_callback() - inbound mailbox message handler
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
अटल व्योम k3_dsp_rproc_mbox_callback(काष्ठा mbox_client *client, व्योम *data)
अणु
	काष्ठा k3_dsp_rproc *kproc = container_of(client, काष्ठा k3_dsp_rproc,
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
		dev_err(dev, "K3 DSP rproc %s crashed\n", name);
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

/*
 * Kick the remote processor to notअगरy about pending unprocessed messages.
 * The vqid usage is not used and is inconsequential, as the kick is perक्रमmed
 * through a simulated GPIO (a bit in an IPC पूर्णांकerrupt-triggering रेजिस्टर),
 * the remote processor is expected to process both its Tx and Rx virtqueues.
 */
अटल व्योम k3_dsp_rproc_kick(काष्ठा rproc *rproc, पूर्णांक vqid)
अणु
	काष्ठा k3_dsp_rproc *kproc = rproc->priv;
	काष्ठा device *dev = rproc->dev.parent;
	mbox_msg_t msg = (mbox_msg_t)vqid;
	पूर्णांक ret;

	/* send the index of the triggered virtqueue in the mailbox payload */
	ret = mbox_send_message(kproc->mbox, (व्योम *)msg);
	अगर (ret < 0)
		dev_err(dev, "failed to send mailbox message, status = %d\n",
			ret);
पूर्ण

/* Put the DSP processor पूर्णांकo reset */
अटल पूर्णांक k3_dsp_rproc_reset(काष्ठा k3_dsp_rproc *kproc)
अणु
	काष्ठा device *dev = kproc->dev;
	पूर्णांक ret;

	ret = reset_control_निश्चित(kproc->reset);
	अगर (ret) अणु
		dev_err(dev, "local-reset assert failed, ret = %d\n", ret);
		वापस ret;
	पूर्ण

	अगर (kproc->data->uses_lreset)
		वापस ret;

	ret = kproc->ti_sci->ops.dev_ops.put_device(kproc->ti_sci,
						    kproc->ti_sci_id);
	अगर (ret) अणु
		dev_err(dev, "module-reset assert failed, ret = %d\n", ret);
		अगर (reset_control_deनिश्चित(kproc->reset))
			dev_warn(dev, "local-reset deassert back failed\n");
	पूर्ण

	वापस ret;
पूर्ण

/* Release the DSP processor from reset */
अटल पूर्णांक k3_dsp_rproc_release(काष्ठा k3_dsp_rproc *kproc)
अणु
	काष्ठा device *dev = kproc->dev;
	पूर्णांक ret;

	अगर (kproc->data->uses_lreset)
		जाओ lreset;

	ret = kproc->ti_sci->ops.dev_ops.get_device(kproc->ti_sci,
						    kproc->ti_sci_id);
	अगर (ret) अणु
		dev_err(dev, "module-reset deassert failed, ret = %d\n", ret);
		वापस ret;
	पूर्ण

lreset:
	ret = reset_control_deनिश्चित(kproc->reset);
	अगर (ret) अणु
		dev_err(dev, "local-reset deassert failed, ret = %d\n", ret);
		अगर (kproc->ti_sci->ops.dev_ops.put_device(kproc->ti_sci,
							  kproc->ti_sci_id))
			dev_warn(dev, "module-reset assert back failed\n");
	पूर्ण

	वापस ret;
पूर्ण

/*
 * The C66x DSP cores have a local reset that affects only the CPU, and a
 * generic module reset that घातers on the device and allows the DSP पूर्णांकernal
 * memories to be accessed जबतक the local reset is निश्चितed. This function is
 * used to release the global reset on C66x DSPs to allow loading पूर्णांकo the DSP
 * पूर्णांकernal RAMs. The .prepare() ops is invoked by remoteproc core beक्रमe any
 * firmware loading, and is followed by the .start() ops after loading to
 * actually let the C66x DSP cores run.
 */
अटल पूर्णांक k3_dsp_rproc_prepare(काष्ठा rproc *rproc)
अणु
	काष्ठा k3_dsp_rproc *kproc = rproc->priv;
	काष्ठा device *dev = kproc->dev;
	पूर्णांक ret;

	ret = kproc->ti_sci->ops.dev_ops.get_device(kproc->ti_sci,
						    kproc->ti_sci_id);
	अगर (ret)
		dev_err(dev, "module-reset deassert failed, cannot enable internal RAM loading, ret = %d\n",
			ret);

	वापस ret;
पूर्ण

/*
 * This function implements the .unprepare() ops and perक्रमms the complimentary
 * operations to that of the .prepare() ops. The function is used to निश्चित the
 * global reset on applicable C66x cores. This completes the second portion of
 * घातering करोwn the C66x DSP cores. The cores themselves are only halted in the
 * .stop() callback through the local reset, and the .unprepare() ops is invoked
 * by the remoteproc core after the remoteproc is stopped to balance the global
 * reset.
 */
अटल पूर्णांक k3_dsp_rproc_unprepare(काष्ठा rproc *rproc)
अणु
	काष्ठा k3_dsp_rproc *kproc = rproc->priv;
	काष्ठा device *dev = kproc->dev;
	पूर्णांक ret;

	ret = kproc->ti_sci->ops.dev_ops.put_device(kproc->ti_sci,
						    kproc->ti_sci_id);
	अगर (ret)
		dev_err(dev, "module-reset assert failed, ret = %d\n", ret);

	वापस ret;
पूर्ण

/*
 * Power up the DSP remote processor.
 *
 * This function will be invoked only after the firmware क्रम this rproc
 * was loaded, parsed successfully, and all of its resource requirements
 * were met.
 */
अटल पूर्णांक k3_dsp_rproc_start(काष्ठा rproc *rproc)
अणु
	काष्ठा k3_dsp_rproc *kproc = rproc->priv;
	काष्ठा mbox_client *client = &kproc->client;
	काष्ठा device *dev = kproc->dev;
	u32 boot_addr;
	पूर्णांक ret;

	client->dev = dev;
	client->tx_करोne = शून्य;
	client->rx_callback = k3_dsp_rproc_mbox_callback;
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
	अगर (boot_addr & (kproc->data->boot_align_addr - 1)) अणु
		dev_err(dev, "invalid boot address 0x%x, must be aligned on a 0x%x boundary\n",
			boot_addr, kproc->data->boot_align_addr);
		ret = -EINVAL;
		जाओ put_mbox;
	पूर्ण

	dev_err(dev, "booting DSP core using boot addr = 0x%x\n", boot_addr);
	ret = ti_sci_proc_set_config(kproc->tsp, boot_addr, 0, 0);
	अगर (ret)
		जाओ put_mbox;

	ret = k3_dsp_rproc_release(kproc);
	अगर (ret)
		जाओ put_mbox;

	वापस 0;

put_mbox:
	mbox_मुक्त_channel(kproc->mbox);
	वापस ret;
पूर्ण

/*
 * Stop the DSP remote processor.
 *
 * This function माला_दो the DSP processor पूर्णांकo reset, and finishes processing
 * of any pending messages.
 */
अटल पूर्णांक k3_dsp_rproc_stop(काष्ठा rproc *rproc)
अणु
	काष्ठा k3_dsp_rproc *kproc = rproc->priv;

	mbox_मुक्त_channel(kproc->mbox);

	k3_dsp_rproc_reset(kproc);

	वापस 0;
पूर्ण

/*
 * Custom function to translate a DSP device address (पूर्णांकernal RAMs only) to a
 * kernel भव address.  The DSPs can access their RAMs at either an पूर्णांकernal
 * address visible only from a DSP, or at the SoC-level bus address. Both these
 * addresses need to be looked through क्रम translation. The translated addresses
 * can be used either by the remoteproc core क्रम loading (when using kernel
 * remoteproc loader), or by any rpmsg bus drivers.
 */
अटल व्योम *k3_dsp_rproc_da_to_va(काष्ठा rproc *rproc, u64 da, माप_प्रकार len, bool *is_iomem)
अणु
	काष्ठा k3_dsp_rproc *kproc = rproc->priv;
	व्योम __iomem *va = शून्य;
	phys_addr_t bus_addr;
	u32 dev_addr, offset;
	माप_प्रकार size;
	पूर्णांक i;

	अगर (len == 0)
		वापस शून्य;

	क्रम (i = 0; i < kproc->num_mems; i++) अणु
		bus_addr = kproc->mem[i].bus_addr;
		dev_addr = kproc->mem[i].dev_addr;
		size = kproc->mem[i].size;

		अगर (da < KEYSTONE_RPROC_LOCAL_ADDRESS_MASK) अणु
			/* handle DSP-view addresses */
			अगर (da >= dev_addr &&
			    ((da + len) <= (dev_addr + size))) अणु
				offset = da - dev_addr;
				va = kproc->mem[i].cpu_addr + offset;
				वापस (__क्रमce व्योम *)va;
			पूर्ण
		पूर्ण अन्यथा अणु
			/* handle SoC-view addresses */
			अगर (da >= bus_addr &&
			    (da + len) <= (bus_addr + size)) अणु
				offset = da - bus_addr;
				va = kproc->mem[i].cpu_addr + offset;
				वापस (__क्रमce व्योम *)va;
			पूर्ण
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

अटल स्थिर काष्ठा rproc_ops k3_dsp_rproc_ops = अणु
	.start		= k3_dsp_rproc_start,
	.stop		= k3_dsp_rproc_stop,
	.kick		= k3_dsp_rproc_kick,
	.da_to_va	= k3_dsp_rproc_da_to_va,
पूर्ण;

अटल पूर्णांक k3_dsp_rproc_of_get_memories(काष्ठा platक्रमm_device *pdev,
					काष्ठा k3_dsp_rproc *kproc)
अणु
	स्थिर काष्ठा k3_dsp_dev_data *data = kproc->data;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा resource *res;
	पूर्णांक num_mems = 0;
	पूर्णांक i;

	num_mems = kproc->data->num_mems;
	kproc->mem = devm_kसुस्मृति(kproc->dev, num_mems,
				  माप(*kproc->mem), GFP_KERNEL);
	अगर (!kproc->mem)
		वापस -ENOMEM;

	क्रम (i = 0; i < num_mems; i++) अणु
		res = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM,
						   data->mems[i].name);
		अगर (!res) अणु
			dev_err(dev, "found no memory resource for %s\n",
				data->mems[i].name);
			वापस -EINVAL;
		पूर्ण
		अगर (!devm_request_mem_region(dev, res->start,
					     resource_size(res),
					     dev_name(dev))) अणु
			dev_err(dev, "could not request %s region for resource\n",
				data->mems[i].name);
			वापस -EBUSY;
		पूर्ण

		kproc->mem[i].cpu_addr = devm_ioremap_wc(dev, res->start,
							 resource_size(res));
		अगर (!kproc->mem[i].cpu_addr) अणु
			dev_err(dev, "failed to map %s memory\n",
				data->mems[i].name);
			वापस -ENOMEM;
		पूर्ण
		kproc->mem[i].bus_addr = res->start;
		kproc->mem[i].dev_addr = data->mems[i].dev_addr;
		kproc->mem[i].size = resource_size(res);

		dev_dbg(dev, "memory %8s: bus addr %pa size 0x%zx va %pK da 0x%x\n",
			data->mems[i].name, &kproc->mem[i].bus_addr,
			kproc->mem[i].size, kproc->mem[i].cpu_addr,
			kproc->mem[i].dev_addr);
	पूर्ण
	kproc->num_mems = num_mems;

	वापस 0;
पूर्ण

अटल पूर्णांक k3_dsp_reserved_mem_init(काष्ठा k3_dsp_rproc *kproc)
अणु
	काष्ठा device *dev = kproc->dev;
	काष्ठा device_node *np = dev->of_node;
	काष्ठा device_node *rmem_np;
	काष्ठा reserved_mem *rmem;
	पूर्णांक num_rmems;
	पूर्णांक ret, i;

	num_rmems = of_property_count_elems_of_size(np, "memory-region",
						    माप(phandle));
	अगर (num_rmems <= 0) अणु
		dev_err(dev, "device does not reserved memory regions, ret = %d\n",
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
		/* 64-bit address regions currently not supported */
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
	of_reserved_mem_device_release(kproc->dev);
	वापस ret;
पूर्ण

अटल व्योम k3_dsp_reserved_mem_निकास(काष्ठा k3_dsp_rproc *kproc)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < kproc->num_rmems; i++)
		iounmap(kproc->rmem[i].cpu_addr);
	kमुक्त(kproc->rmem);

	of_reserved_mem_device_release(kproc->dev);
पूर्ण

अटल
काष्ठा ti_sci_proc *k3_dsp_rproc_of_get_tsp(काष्ठा device *dev,
					    स्थिर काष्ठा ti_sci_handle *sci)
अणु
	काष्ठा ti_sci_proc *tsp;
	u32 temp[2];
	पूर्णांक ret;

	ret = of_property_पढ़ो_u32_array(dev->of_node, "ti,sci-proc-ids",
					 temp, 2);
	अगर (ret < 0)
		वापस ERR_PTR(ret);

	tsp = kzalloc(माप(*tsp), GFP_KERNEL);
	अगर (!tsp)
		वापस ERR_PTR(-ENOMEM);

	tsp->dev = dev;
	tsp->sci = sci;
	tsp->ops = &sci->ops.proc_ops;
	tsp->proc_id = temp[0];
	tsp->host_id = temp[1];

	वापस tsp;
पूर्ण

अटल पूर्णांक k3_dsp_rproc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा device_node *np = dev->of_node;
	स्थिर काष्ठा k3_dsp_dev_data *data;
	काष्ठा k3_dsp_rproc *kproc;
	काष्ठा rproc *rproc;
	स्थिर अक्षर *fw_name;
	पूर्णांक ret = 0;
	पूर्णांक ret1;

	data = of_device_get_match_data(dev);
	अगर (!data)
		वापस -ENODEV;

	ret = rproc_of_parse_firmware(dev, 0, &fw_name);
	अगर (ret) अणु
		dev_err(dev, "failed to parse firmware-name property, ret = %d\n",
			ret);
		वापस ret;
	पूर्ण

	rproc = rproc_alloc(dev, dev_name(dev), &k3_dsp_rproc_ops, fw_name,
			    माप(*kproc));
	अगर (!rproc)
		वापस -ENOMEM;

	rproc->has_iommu = false;
	rproc->recovery_disabled = true;
	अगर (data->uses_lreset) अणु
		rproc->ops->prepare = k3_dsp_rproc_prepare;
		rproc->ops->unprepare = k3_dsp_rproc_unprepare;
	पूर्ण
	kproc = rproc->priv;
	kproc->rproc = rproc;
	kproc->dev = dev;
	kproc->data = data;

	kproc->ti_sci = ti_sci_get_by_phandle(np, "ti,sci");
	अगर (IS_ERR(kproc->ti_sci)) अणु
		ret = PTR_ERR(kproc->ti_sci);
		अगर (ret != -EPROBE_DEFER) अणु
			dev_err(dev, "failed to get ti-sci handle, ret = %d\n",
				ret);
		पूर्ण
		kproc->ti_sci = शून्य;
		जाओ मुक्त_rproc;
	पूर्ण

	ret = of_property_पढ़ो_u32(np, "ti,sci-dev-id", &kproc->ti_sci_id);
	अगर (ret) अणु
		dev_err(dev, "missing 'ti,sci-dev-id' property\n");
		जाओ put_sci;
	पूर्ण

	kproc->reset = devm_reset_control_get_exclusive(dev, शून्य);
	अगर (IS_ERR(kproc->reset)) अणु
		ret = PTR_ERR(kproc->reset);
		dev_err(dev, "failed to get reset, status = %d\n", ret);
		जाओ put_sci;
	पूर्ण

	kproc->tsp = k3_dsp_rproc_of_get_tsp(dev, kproc->ti_sci);
	अगर (IS_ERR(kproc->tsp)) अणु
		dev_err(dev, "failed to construct ti-sci proc control, ret = %d\n",
			ret);
		ret = PTR_ERR(kproc->tsp);
		जाओ put_sci;
	पूर्ण

	ret = ti_sci_proc_request(kproc->tsp);
	अगर (ret < 0) अणु
		dev_err(dev, "ti_sci_proc_request failed, ret = %d\n", ret);
		जाओ मुक्त_tsp;
	पूर्ण

	ret = k3_dsp_rproc_of_get_memories(pdev, kproc);
	अगर (ret)
		जाओ release_tsp;

	ret = k3_dsp_reserved_mem_init(kproc);
	अगर (ret) अणु
		dev_err(dev, "reserved memory init failed, ret = %d\n", ret);
		जाओ release_tsp;
	पूर्ण

	/*
	 * ensure the DSP local reset is निश्चितed to ensure the DSP करोesn't
	 * execute bogus code in .prepare() when the module reset is released.
	 */
	अगर (data->uses_lreset) अणु
		ret = reset_control_status(kproc->reset);
		अगर (ret < 0) अणु
			dev_err(dev, "failed to get reset status, status = %d\n",
				ret);
			जाओ release_mem;
		पूर्ण अन्यथा अगर (ret == 0) अणु
			dev_warn(dev, "local reset is deasserted for device\n");
			k3_dsp_rproc_reset(kproc);
		पूर्ण
	पूर्ण

	ret = rproc_add(rproc);
	अगर (ret) अणु
		dev_err(dev, "failed to add register device with remoteproc core, status = %d\n",
			ret);
		जाओ release_mem;
	पूर्ण

	platक्रमm_set_drvdata(pdev, kproc);

	वापस 0;

release_mem:
	k3_dsp_reserved_mem_निकास(kproc);
release_tsp:
	ret1 = ti_sci_proc_release(kproc->tsp);
	अगर (ret1)
		dev_err(dev, "failed to release proc, ret = %d\n", ret1);
मुक्त_tsp:
	kमुक्त(kproc->tsp);
put_sci:
	ret1 = ti_sci_put_handle(kproc->ti_sci);
	अगर (ret1)
		dev_err(dev, "failed to put ti_sci handle, ret = %d\n", ret1);
मुक्त_rproc:
	rproc_मुक्त(rproc);
	वापस ret;
पूर्ण

अटल पूर्णांक k3_dsp_rproc_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा k3_dsp_rproc *kproc = platक्रमm_get_drvdata(pdev);
	काष्ठा device *dev = &pdev->dev;
	पूर्णांक ret;

	rproc_del(kproc->rproc);

	ret = ti_sci_proc_release(kproc->tsp);
	अगर (ret)
		dev_err(dev, "failed to release proc, ret = %d\n", ret);

	kमुक्त(kproc->tsp);

	ret = ti_sci_put_handle(kproc->ti_sci);
	अगर (ret)
		dev_err(dev, "failed to put ti_sci handle, ret = %d\n", ret);

	k3_dsp_reserved_mem_निकास(kproc);
	rproc_मुक्त(kproc->rproc);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा k3_dsp_mem_data c66_mems[] = अणु
	अणु .name = "l2sram", .dev_addr = 0x800000 पूर्ण,
	अणु .name = "l1pram", .dev_addr = 0xe00000 पूर्ण,
	अणु .name = "l1dram", .dev_addr = 0xf00000 पूर्ण,
पूर्ण;

/* C71x cores only have a L1P Cache, there are no L1P SRAMs */
अटल स्थिर काष्ठा k3_dsp_mem_data c71_mems[] = अणु
	अणु .name = "l2sram", .dev_addr = 0x800000 पूर्ण,
	अणु .name = "l1dram", .dev_addr = 0xe00000 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा k3_dsp_dev_data c66_data = अणु
	.mems = c66_mems,
	.num_mems = ARRAY_SIZE(c66_mems),
	.boot_align_addr = SZ_1K,
	.uses_lreset = true,
पूर्ण;

अटल स्थिर काष्ठा k3_dsp_dev_data c71_data = अणु
	.mems = c71_mems,
	.num_mems = ARRAY_SIZE(c71_mems),
	.boot_align_addr = SZ_2M,
	.uses_lreset = false,
पूर्ण;

अटल स्थिर काष्ठा of_device_id k3_dsp_of_match[] = अणु
	अणु .compatible = "ti,j721e-c66-dsp", .data = &c66_data, पूर्ण,
	अणु .compatible = "ti,j721e-c71-dsp", .data = &c71_data, पूर्ण,
	अणु /* sentinel */ पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, k3_dsp_of_match);

अटल काष्ठा platक्रमm_driver k3_dsp_rproc_driver = अणु
	.probe	= k3_dsp_rproc_probe,
	.हटाओ	= k3_dsp_rproc_हटाओ,
	.driver	= अणु
		.name = "k3-dsp-rproc",
		.of_match_table = k3_dsp_of_match,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(k3_dsp_rproc_driver);

MODULE_AUTHOR("Suman Anna <s-anna@ti.com>");
MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("TI K3 DSP Remoteproc driver");
