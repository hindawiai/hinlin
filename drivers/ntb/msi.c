<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0 OR BSD-3-Clause)

#समावेश <linux/irq.h>
#समावेश <linux/module.h>
#समावेश <linux/ntb.h>
#समावेश <linux/msi.h>
#समावेश <linux/pci.h>

काष्ठा ntb_msi अणु
	u64 base_addr;
	u64 end_addr;

	व्योम (*desc_changed)(व्योम *ctx);

	u32 __iomem *peer_mws[];
पूर्ण;

/**
 * ntb_msi_init() - Initialize the MSI context
 * @ntb:	NTB device context
 *
 * This function must be called beक्रमe any other ntb_msi function.
 * It initializes the context क्रम MSI operations and maps
 * the peer memory winकरोws.
 *
 * This function reserves the last N outbound memory winकरोws (where N
 * is the number of peers).
 *
 * Return: Zero on success, otherwise a negative error number.
 */
पूर्णांक ntb_msi_init(काष्ठा ntb_dev *ntb,
		 व्योम (*desc_changed)(व्योम *ctx))
अणु
	phys_addr_t mw_phys_addr;
	resource_माप_प्रकार mw_size;
	माप_प्रकार काष्ठा_size;
	पूर्णांक peer_widx;
	पूर्णांक peers;
	पूर्णांक ret;
	पूर्णांक i;

	peers = ntb_peer_port_count(ntb);
	अगर (peers <= 0)
		वापस -EINVAL;

	काष्ठा_size = माप(*ntb->msi) + माप(*ntb->msi->peer_mws) * peers;

	ntb->msi = devm_kzalloc(&ntb->dev, काष्ठा_size, GFP_KERNEL);
	अगर (!ntb->msi)
		वापस -ENOMEM;

	ntb->msi->desc_changed = desc_changed;

	क्रम (i = 0; i < peers; i++) अणु
		peer_widx = ntb_peer_mw_count(ntb) - 1 - i;

		ret = ntb_peer_mw_get_addr(ntb, peer_widx, &mw_phys_addr,
					   &mw_size);
		अगर (ret)
			जाओ unroll;

		ntb->msi->peer_mws[i] = devm_ioremap(&ntb->dev, mw_phys_addr,
						     mw_size);
		अगर (!ntb->msi->peer_mws[i]) अणु
			ret = -EFAULT;
			जाओ unroll;
		पूर्ण
	पूर्ण

	वापस 0;

unroll:
	क्रम (i = 0; i < peers; i++)
		अगर (ntb->msi->peer_mws[i])
			devm_iounmap(&ntb->dev, ntb->msi->peer_mws[i]);

	devm_kमुक्त(&ntb->dev, ntb->msi);
	ntb->msi = शून्य;
	वापस ret;
पूर्ण
EXPORT_SYMBOL(ntb_msi_init);

/**
 * ntb_msi_setup_mws() - Initialize the MSI inbound memory winकरोws
 * @ntb:	NTB device context
 *
 * This function sets up the required inbound memory winकरोws. It should be
 * called from a work function after a link up event.
 *
 * Over the entire network, this function will reserves the last N
 * inbound memory winकरोws क्रम each peer (where N is the number of peers).
 *
 * ntb_msi_init() must be called beक्रमe this function.
 *
 * Return: Zero on success, otherwise a negative error number.
 */
पूर्णांक ntb_msi_setup_mws(काष्ठा ntb_dev *ntb)
अणु
	काष्ठा msi_desc *desc;
	u64 addr;
	पूर्णांक peer, peer_widx;
	resource_माप_प्रकार addr_align, size_align, size_max;
	resource_माप_प्रकार mw_size = SZ_32K;
	resource_माप_प्रकार mw_min_size = mw_size;
	पूर्णांक i;
	पूर्णांक ret;

	अगर (!ntb->msi)
		वापस -EINVAL;

	desc = first_msi_entry(&ntb->pdev->dev);
	addr = desc->msg.address_lo + ((uपूर्णांक64_t)desc->msg.address_hi << 32);

	क्रम (peer = 0; peer < ntb_peer_port_count(ntb); peer++) अणु
		peer_widx = ntb_peer_highest_mw_idx(ntb, peer);
		अगर (peer_widx < 0)
			वापस peer_widx;

		ret = ntb_mw_get_align(ntb, peer, peer_widx, &addr_align,
				       शून्य, शून्य);
		अगर (ret)
			वापस ret;

		addr &= ~(addr_align - 1);
	पूर्ण

	क्रम (peer = 0; peer < ntb_peer_port_count(ntb); peer++) अणु
		peer_widx = ntb_peer_highest_mw_idx(ntb, peer);
		अगर (peer_widx < 0) अणु
			ret = peer_widx;
			जाओ error_out;
		पूर्ण

		ret = ntb_mw_get_align(ntb, peer, peer_widx, शून्य,
				       &size_align, &size_max);
		अगर (ret)
			जाओ error_out;

		mw_size = round_up(mw_size, size_align);
		mw_size = max(mw_size, size_max);
		अगर (mw_size < mw_min_size)
			mw_min_size = mw_size;

		ret = ntb_mw_set_trans(ntb, peer, peer_widx,
				       addr, mw_size);
		अगर (ret)
			जाओ error_out;
	पूर्ण

	ntb->msi->base_addr = addr;
	ntb->msi->end_addr = addr + mw_min_size;

	वापस 0;

error_out:
	क्रम (i = 0; i < peer; i++) अणु
		peer_widx = ntb_peer_highest_mw_idx(ntb, peer);
		अगर (peer_widx < 0)
			जारी;

		ntb_mw_clear_trans(ntb, i, peer_widx);
	पूर्ण

	वापस ret;
पूर्ण
EXPORT_SYMBOL(ntb_msi_setup_mws);

/**
 * ntb_msi_clear_mws() - Clear all inbound memory winकरोws
 * @ntb:	NTB device context
 *
 * This function tears करोwn the resources used by ntb_msi_setup_mws().
 */
व्योम ntb_msi_clear_mws(काष्ठा ntb_dev *ntb)
अणु
	पूर्णांक peer;
	पूर्णांक peer_widx;

	क्रम (peer = 0; peer < ntb_peer_port_count(ntb); peer++) अणु
		peer_widx = ntb_peer_highest_mw_idx(ntb, peer);
		अगर (peer_widx < 0)
			जारी;

		ntb_mw_clear_trans(ntb, peer, peer_widx);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(ntb_msi_clear_mws);

काष्ठा ntb_msi_devres अणु
	काष्ठा ntb_dev *ntb;
	काष्ठा msi_desc *entry;
	काष्ठा ntb_msi_desc *msi_desc;
पूर्ण;

अटल पूर्णांक ntb_msi_set_desc(काष्ठा ntb_dev *ntb, काष्ठा msi_desc *entry,
			    काष्ठा ntb_msi_desc *msi_desc)
अणु
	u64 addr;

	addr = entry->msg.address_lo +
		((uपूर्णांक64_t)entry->msg.address_hi << 32);

	अगर (addr < ntb->msi->base_addr || addr >= ntb->msi->end_addr) अणु
		dev_warn_once(&ntb->dev,
			      "IRQ %d: MSI Address not within the memory window (%llx, [%llx %llx])\n",
			      entry->irq, addr, ntb->msi->base_addr,
			      ntb->msi->end_addr);
		वापस -EFAULT;
	पूर्ण

	msi_desc->addr_offset = addr - ntb->msi->base_addr;
	msi_desc->data = entry->msg.data;

	वापस 0;
पूर्ण

अटल व्योम ntb_msi_ग_लिखो_msg(काष्ठा msi_desc *entry, व्योम *data)
अणु
	काष्ठा ntb_msi_devres *dr = data;

	WARN_ON(ntb_msi_set_desc(dr->ntb, entry, dr->msi_desc));

	अगर (dr->ntb->msi->desc_changed)
		dr->ntb->msi->desc_changed(dr->ntb->ctx);
पूर्ण

अटल व्योम ntbm_msi_callback_release(काष्ठा device *dev, व्योम *res)
अणु
	काष्ठा ntb_msi_devres *dr = res;

	dr->entry->ग_लिखो_msi_msg = शून्य;
	dr->entry->ग_लिखो_msi_msg_data = शून्य;
पूर्ण

अटल पूर्णांक ntbm_msi_setup_callback(काष्ठा ntb_dev *ntb, काष्ठा msi_desc *entry,
				   काष्ठा ntb_msi_desc *msi_desc)
अणु
	काष्ठा ntb_msi_devres *dr;

	dr = devres_alloc(ntbm_msi_callback_release,
			  माप(काष्ठा ntb_msi_devres), GFP_KERNEL);
	अगर (!dr)
		वापस -ENOMEM;

	dr->ntb = ntb;
	dr->entry = entry;
	dr->msi_desc = msi_desc;

	devres_add(&ntb->dev, dr);

	dr->entry->ग_लिखो_msi_msg = ntb_msi_ग_लिखो_msg;
	dr->entry->ग_लिखो_msi_msg_data = dr;

	वापस 0;
पूर्ण

/**
 * ntbm_msi_request_thपढ़ोed_irq() - allocate an MSI पूर्णांकerrupt
 * @ntb:	NTB device context
 * @handler:	Function to be called when the IRQ occurs
 * @thपढ़ो_fn:  Function to be called in a thपढ़ोed पूर्णांकerrupt context. शून्य
 *              क्रम clients which handle everything in @handler
 * @devname:    An ascii name क्रम the claiming device, dev_name(dev) अगर शून्य
 * @dev_id:     A cookie passed back to the handler function
 *
 * This function assigns an पूर्णांकerrupt handler to an unused
 * MSI पूर्णांकerrupt and वापसs the descriptor used to trigger
 * it. The descriptor can then be sent to a peer to trigger
 * the पूर्णांकerrupt.
 *
 * The पूर्णांकerrupt resource is managed with devres so it will
 * be स्वतःmatically मुक्तd when the NTB device is torn करोwn.
 *
 * If an IRQ allocated with this function needs to be मुक्तd
 * separately, ntbm_मुक्त_irq() must be used.
 *
 * Return: IRQ number asचिन्हित on success, otherwise a negative error number.
 */
पूर्णांक ntbm_msi_request_thपढ़ोed_irq(काष्ठा ntb_dev *ntb, irq_handler_t handler,
				  irq_handler_t thपढ़ो_fn,
				  स्थिर अक्षर *name, व्योम *dev_id,
				  काष्ठा ntb_msi_desc *msi_desc)
अणु
	काष्ठा msi_desc *entry;
	पूर्णांक ret;

	अगर (!ntb->msi)
		वापस -EINVAL;

	क्रम_each_pci_msi_entry(entry, ntb->pdev) अणु
		अगर (irq_has_action(entry->irq))
			जारी;

		ret = devm_request_thपढ़ोed_irq(&ntb->dev, entry->irq, handler,
						thपढ़ो_fn, 0, name, dev_id);
		अगर (ret)
			जारी;

		अगर (ntb_msi_set_desc(ntb, entry, msi_desc)) अणु
			devm_मुक्त_irq(&ntb->dev, entry->irq, dev_id);
			जारी;
		पूर्ण

		ret = ntbm_msi_setup_callback(ntb, entry, msi_desc);
		अगर (ret) अणु
			devm_मुक्त_irq(&ntb->dev, entry->irq, dev_id);
			वापस ret;
		पूर्ण


		वापस entry->irq;
	पूर्ण

	वापस -ENODEV;
पूर्ण
EXPORT_SYMBOL(ntbm_msi_request_thपढ़ोed_irq);

अटल पूर्णांक ntbm_msi_callback_match(काष्ठा device *dev, व्योम *res, व्योम *data)
अणु
	काष्ठा ntb_dev *ntb = dev_ntb(dev);
	काष्ठा ntb_msi_devres *dr = res;

	वापस dr->ntb == ntb && dr->entry == data;
पूर्ण

/**
 * ntbm_msi_मुक्त_irq() - मुक्त an पूर्णांकerrupt
 * @ntb:	NTB device context
 * @irq:	Interrupt line to मुक्त
 * @dev_id:	Device identity to मुक्त
 *
 * This function should be used to manually मुक्त IRQs allocated with
 * ntbm_request_[thपढ़ोed_]irq().
 */
व्योम ntbm_msi_मुक्त_irq(काष्ठा ntb_dev *ntb, अचिन्हित पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा msi_desc *entry = irq_get_msi_desc(irq);

	entry->ग_लिखो_msi_msg = शून्य;
	entry->ग_लिखो_msi_msg_data = शून्य;

	WARN_ON(devres_destroy(&ntb->dev, ntbm_msi_callback_release,
			       ntbm_msi_callback_match, entry));

	devm_मुक्त_irq(&ntb->dev, irq, dev_id);
पूर्ण
EXPORT_SYMBOL(ntbm_msi_मुक्त_irq);

/**
 * ntb_msi_peer_trigger() - Trigger an पूर्णांकerrupt handler on a peer
 * @ntb:	NTB device context
 * @peer:	Peer index
 * @desc:	MSI descriptor data which triggers the पूर्णांकerrupt
 *
 * This function triggers an पूर्णांकerrupt on a peer. It requires
 * the descriptor काष्ठाure to have been passed from that peer
 * by some other means.
 *
 * Return: Zero on success, otherwise a negative error number.
 */
पूर्णांक ntb_msi_peer_trigger(काष्ठा ntb_dev *ntb, पूर्णांक peer,
			 काष्ठा ntb_msi_desc *desc)
अणु
	पूर्णांक idx;

	अगर (!ntb->msi)
		वापस -EINVAL;

	idx = desc->addr_offset / माप(*ntb->msi->peer_mws[peer]);

	ioग_लिखो32(desc->data, &ntb->msi->peer_mws[peer][idx]);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(ntb_msi_peer_trigger);

/**
 * ntb_msi_peer_addr() - Get the DMA address to trigger a peer's MSI पूर्णांकerrupt
 * @ntb:	NTB device context
 * @peer:	Peer index
 * @desc:	MSI descriptor data which triggers the पूर्णांकerrupt
 * @msi_addr:   Physical address to trigger the पूर्णांकerrupt
 *
 * This function allows using DMA engines to trigger an पूर्णांकerrupt
 * (क्रम example, trigger an पूर्णांकerrupt to process the data after
 * sending it). To trigger the पूर्णांकerrupt, ग_लिखो @desc.data to the address
 * वापसed in @msi_addr
 *
 * Return: Zero on success, otherwise a negative error number.
 */
पूर्णांक ntb_msi_peer_addr(काष्ठा ntb_dev *ntb, पूर्णांक peer,
		      काष्ठा ntb_msi_desc *desc,
		      phys_addr_t *msi_addr)
अणु
	पूर्णांक peer_widx = ntb_peer_mw_count(ntb) - 1 - peer;
	phys_addr_t mw_phys_addr;
	पूर्णांक ret;

	ret = ntb_peer_mw_get_addr(ntb, peer_widx, &mw_phys_addr, शून्य);
	अगर (ret)
		वापस ret;

	अगर (msi_addr)
		*msi_addr = mw_phys_addr + desc->addr_offset;

	वापस 0;
पूर्ण
EXPORT_SYMBOL(ntb_msi_peer_addr);
