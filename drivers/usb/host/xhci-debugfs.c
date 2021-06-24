<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * xhci-debugfs.c - xHCI debugfs पूर्णांकerface
 *
 * Copyright (C) 2017 Intel Corporation
 *
 * Author: Lu Baolu <baolu.lu@linux.पूर्णांकel.com>
 */

#समावेश <linux/slab.h>
#समावेश <linux/uaccess.h>

#समावेश "xhci.h"
#समावेश "xhci-debugfs.h"

अटल स्थिर काष्ठा debugfs_reg32 xhci_cap_regs[] = अणु
	dump_रेजिस्टर(CAPLENGTH),
	dump_रेजिस्टर(HCSPARAMS1),
	dump_रेजिस्टर(HCSPARAMS2),
	dump_रेजिस्टर(HCSPARAMS3),
	dump_रेजिस्टर(HCCPARAMS1),
	dump_रेजिस्टर(DOORBELLOFF),
	dump_रेजिस्टर(RUNTIMखातापूर्णF),
	dump_रेजिस्टर(HCCPARAMS2),
पूर्ण;

अटल स्थिर काष्ठा debugfs_reg32 xhci_op_regs[] = अणु
	dump_रेजिस्टर(USBCMD),
	dump_रेजिस्टर(USBSTS),
	dump_रेजिस्टर(PAGESIZE),
	dump_रेजिस्टर(DNCTRL),
	dump_रेजिस्टर(CRCR),
	dump_रेजिस्टर(DCBAAP_LOW),
	dump_रेजिस्टर(DCBAAP_HIGH),
	dump_रेजिस्टर(CONFIG),
पूर्ण;

अटल स्थिर काष्ठा debugfs_reg32 xhci_runसमय_regs[] = अणु
	dump_रेजिस्टर(MFINDEX),
	dump_रेजिस्टर(IR0_IMAN),
	dump_रेजिस्टर(IR0_IMOD),
	dump_रेजिस्टर(IR0_ERSTSZ),
	dump_रेजिस्टर(IR0_ERSTBA_LOW),
	dump_रेजिस्टर(IR0_ERSTBA_HIGH),
	dump_रेजिस्टर(IR0_ERDP_LOW),
	dump_रेजिस्टर(IR0_ERDP_HIGH),
पूर्ण;

अटल स्थिर काष्ठा debugfs_reg32 xhci_extcap_legsup[] = अणु
	dump_रेजिस्टर(EXTCAP_USBLEGSUP),
	dump_रेजिस्टर(EXTCAP_USBLEGCTLSTS),
पूर्ण;

अटल स्थिर काष्ठा debugfs_reg32 xhci_extcap_protocol[] = अणु
	dump_रेजिस्टर(EXTCAP_REVISION),
	dump_रेजिस्टर(EXTCAP_NAME),
	dump_रेजिस्टर(EXTCAP_PORTINFO),
	dump_रेजिस्टर(EXTCAP_PORTTYPE),
	dump_रेजिस्टर(EXTCAP_MANTISSA1),
	dump_रेजिस्टर(EXTCAP_MANTISSA2),
	dump_रेजिस्टर(EXTCAP_MANTISSA3),
	dump_रेजिस्टर(EXTCAP_MANTISSA4),
	dump_रेजिस्टर(EXTCAP_MANTISSA5),
	dump_रेजिस्टर(EXTCAP_MANTISSA6),
पूर्ण;

अटल स्थिर काष्ठा debugfs_reg32 xhci_extcap_dbc[] = अणु
	dump_रेजिस्टर(EXTCAP_DBC_CAPABILITY),
	dump_रेजिस्टर(EXTCAP_DBC_DOORBELL),
	dump_रेजिस्टर(EXTCAP_DBC_ERSTSIZE),
	dump_रेजिस्टर(EXTCAP_DBC_ERST_LOW),
	dump_रेजिस्टर(EXTCAP_DBC_ERST_HIGH),
	dump_रेजिस्टर(EXTCAP_DBC_ERDP_LOW),
	dump_रेजिस्टर(EXTCAP_DBC_ERDP_HIGH),
	dump_रेजिस्टर(EXTCAP_DBC_CONTROL),
	dump_रेजिस्टर(EXTCAP_DBC_STATUS),
	dump_रेजिस्टर(EXTCAP_DBC_PORTSC),
	dump_रेजिस्टर(EXTCAP_DBC_CONT_LOW),
	dump_रेजिस्टर(EXTCAP_DBC_CONT_HIGH),
	dump_रेजिस्टर(EXTCAP_DBC_DEVINFO1),
	dump_रेजिस्टर(EXTCAP_DBC_DEVINFO2),
पूर्ण;

अटल काष्ठा dentry *xhci_debugfs_root;

अटल काष्ठा xhci_regset *xhci_debugfs_alloc_regset(काष्ठा xhci_hcd *xhci)
अणु
	काष्ठा xhci_regset	*regset;

	regset = kzalloc(माप(*regset), GFP_KERNEL);
	अगर (!regset)
		वापस शून्य;

	/*
	 * The allocation and मुक्त of regset are executed in order.
	 * We needn't a lock here.
	 */
	INIT_LIST_HEAD(&regset->list);
	list_add_tail(&regset->list, &xhci->regset_list);

	वापस regset;
पूर्ण

अटल व्योम xhci_debugfs_मुक्त_regset(काष्ठा xhci_regset *regset)
अणु
	अगर (!regset)
		वापस;

	list_del(&regset->list);
	kमुक्त(regset);
पूर्ण

__म_लिखो(6, 7)
अटल व्योम xhci_debugfs_regset(काष्ठा xhci_hcd *xhci, u32 base,
				स्थिर काष्ठा debugfs_reg32 *regs,
				माप_प्रकार nregs, काष्ठा dentry *parent,
				स्थिर अक्षर *fmt, ...)
अणु
	काष्ठा xhci_regset	*rgs;
	बहु_सूची			args;
	काष्ठा debugfs_regset32	*regset;
	काष्ठा usb_hcd		*hcd = xhci_to_hcd(xhci);

	rgs = xhci_debugfs_alloc_regset(xhci);
	अगर (!rgs)
		वापस;

	बहु_शुरू(args, fmt);
	vsnम_लिखो(rgs->name, माप(rgs->name), fmt, args);
	बहु_पूर्ण(args);

	regset = &rgs->regset;
	regset->regs = regs;
	regset->nregs = nregs;
	regset->base = hcd->regs + base;

	debugfs_create_regset32((स्थिर अक्षर *)rgs->name, 0444, parent, regset);
पूर्ण

अटल व्योम xhci_debugfs_extcap_regset(काष्ठा xhci_hcd *xhci, पूर्णांक cap_id,
				       स्थिर काष्ठा debugfs_reg32 *regs,
				       माप_प्रकार n, स्थिर अक्षर *cap_name)
अणु
	u32			offset;
	पूर्णांक			index = 0;
	माप_प्रकार			psic, nregs = n;
	व्योम __iomem		*base = &xhci->cap_regs->hc_capbase;

	offset = xhci_find_next_ext_cap(base, 0, cap_id);
	जबतक (offset) अणु
		अगर (cap_id == XHCI_EXT_CAPS_PROTOCOL) अणु
			psic = XHCI_EXT_PORT_PSIC(पढ़ोl(base + offset + 8));
			nregs = min(4 + psic, n);
		पूर्ण

		xhci_debugfs_regset(xhci, offset, regs, nregs,
				    xhci->debugfs_root, "%s:%02d",
				    cap_name, index);
		offset = xhci_find_next_ext_cap(base, offset, cap_id);
		index++;
	पूर्ण
पूर्ण

अटल पूर्णांक xhci_ring_enqueue_show(काष्ठा seq_file *s, व्योम *unused)
अणु
	dma_addr_t		dma;
	काष्ठा xhci_ring	*ring = *(काष्ठा xhci_ring **)s->निजी;

	dma = xhci_trb_virt_to_dma(ring->enq_seg, ring->enqueue);
	seq_म_लिखो(s, "%pad\n", &dma);

	वापस 0;
पूर्ण

अटल पूर्णांक xhci_ring_dequeue_show(काष्ठा seq_file *s, व्योम *unused)
अणु
	dma_addr_t		dma;
	काष्ठा xhci_ring	*ring = *(काष्ठा xhci_ring **)s->निजी;

	dma = xhci_trb_virt_to_dma(ring->deq_seg, ring->dequeue);
	seq_म_लिखो(s, "%pad\n", &dma);

	वापस 0;
पूर्ण

अटल पूर्णांक xhci_ring_cycle_show(काष्ठा seq_file *s, व्योम *unused)
अणु
	काष्ठा xhci_ring	*ring = *(काष्ठा xhci_ring **)s->निजी;

	seq_म_लिखो(s, "%d\n", ring->cycle_state);

	वापस 0;
पूर्ण

अटल व्योम xhci_ring_dump_segment(काष्ठा seq_file *s,
				   काष्ठा xhci_segment *seg)
अणु
	पूर्णांक			i;
	dma_addr_t		dma;
	जोड़ xhci_trb		*trb;

	क्रम (i = 0; i < TRBS_PER_SEGMENT; i++) अणु
		trb = &seg->trbs[i];
		dma = seg->dma + i * माप(*trb);
		seq_म_लिखो(s, "%pad: %s\n", &dma,
			   xhci_decode_trb(le32_to_cpu(trb->generic.field[0]),
					   le32_to_cpu(trb->generic.field[1]),
					   le32_to_cpu(trb->generic.field[2]),
					   le32_to_cpu(trb->generic.field[3])));
	पूर्ण
पूर्ण

अटल पूर्णांक xhci_ring_trb_show(काष्ठा seq_file *s, व्योम *unused)
अणु
	पूर्णांक			i;
	काष्ठा xhci_ring	*ring = *(काष्ठा xhci_ring **)s->निजी;
	काष्ठा xhci_segment	*seg = ring->first_seg;

	क्रम (i = 0; i < ring->num_segs; i++) अणु
		xhci_ring_dump_segment(s, seg);
		seg = seg->next;
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा xhci_file_map ring_files[] = अणु
	अणु"enqueue",		xhci_ring_enqueue_show, पूर्ण,
	अणु"dequeue",		xhci_ring_dequeue_show, पूर्ण,
	अणु"cycle",		xhci_ring_cycle_show, पूर्ण,
	अणु"trbs",		xhci_ring_trb_show, पूर्ण,
पूर्ण;

अटल पूर्णांक xhci_ring_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	पूर्णांक			i;
	काष्ठा xhci_file_map	*f_map;
	स्थिर अक्षर		*file_name = file_dentry(file)->d_iname;

	क्रम (i = 0; i < ARRAY_SIZE(ring_files); i++) अणु
		f_map = &ring_files[i];

		अगर (म_भेद(f_map->name, file_name) == 0)
			अवरोध;
	पूर्ण

	वापस single_खोलो(file, f_map->show, inode->i_निजी);
पूर्ण

अटल स्थिर काष्ठा file_operations xhci_ring_fops = अणु
	.खोलो			= xhci_ring_खोलो,
	.पढ़ो			= seq_पढ़ो,
	.llseek			= seq_lseek,
	.release		= single_release,
पूर्ण;

अटल पूर्णांक xhci_slot_context_show(काष्ठा seq_file *s, व्योम *unused)
अणु
	काष्ठा xhci_hcd		*xhci;
	काष्ठा xhci_slot_ctx	*slot_ctx;
	काष्ठा xhci_slot_priv	*priv = s->निजी;
	काष्ठा xhci_virt_device	*dev = priv->dev;

	xhci = hcd_to_xhci(bus_to_hcd(dev->udev->bus));
	slot_ctx = xhci_get_slot_ctx(xhci, dev->out_ctx);
	seq_म_लिखो(s, "%pad: %s\n", &dev->out_ctx->dma,
		   xhci_decode_slot_context(le32_to_cpu(slot_ctx->dev_info),
					    le32_to_cpu(slot_ctx->dev_info2),
					    le32_to_cpu(slot_ctx->tt_info),
					    le32_to_cpu(slot_ctx->dev_state)));

	वापस 0;
पूर्ण

अटल पूर्णांक xhci_endpoपूर्णांक_context_show(काष्ठा seq_file *s, व्योम *unused)
अणु
	पूर्णांक			ep_index;
	dma_addr_t		dma;
	काष्ठा xhci_hcd		*xhci;
	काष्ठा xhci_ep_ctx	*ep_ctx;
	काष्ठा xhci_slot_priv	*priv = s->निजी;
	काष्ठा xhci_virt_device	*dev = priv->dev;

	xhci = hcd_to_xhci(bus_to_hcd(dev->udev->bus));

	क्रम (ep_index = 0; ep_index < 31; ep_index++) अणु
		ep_ctx = xhci_get_ep_ctx(xhci, dev->out_ctx, ep_index);
		dma = dev->out_ctx->dma + (ep_index + 1) * CTX_SIZE(xhci->hcc_params);
		seq_म_लिखो(s, "%pad: %s\n", &dma,
			   xhci_decode_ep_context(le32_to_cpu(ep_ctx->ep_info),
						  le32_to_cpu(ep_ctx->ep_info2),
						  le64_to_cpu(ep_ctx->deq),
						  le32_to_cpu(ep_ctx->tx_info)));
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक xhci_device_name_show(काष्ठा seq_file *s, व्योम *unused)
अणु
	काष्ठा xhci_slot_priv	*priv = s->निजी;
	काष्ठा xhci_virt_device	*dev = priv->dev;

	seq_म_लिखो(s, "%s\n", dev_name(&dev->udev->dev));

	वापस 0;
पूर्ण

अटल काष्ठा xhci_file_map context_files[] = अणु
	अणु"name",		xhci_device_name_show, पूर्ण,
	अणु"slot-context",	xhci_slot_context_show, पूर्ण,
	अणु"ep-context",		xhci_endpoपूर्णांक_context_show, पूर्ण,
पूर्ण;

अटल पूर्णांक xhci_context_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	पूर्णांक			i;
	काष्ठा xhci_file_map	*f_map;
	स्थिर अक्षर		*file_name = file_dentry(file)->d_iname;

	क्रम (i = 0; i < ARRAY_SIZE(context_files); i++) अणु
		f_map = &context_files[i];

		अगर (म_भेद(f_map->name, file_name) == 0)
			अवरोध;
	पूर्ण

	वापस single_खोलो(file, f_map->show, inode->i_निजी);
पूर्ण

अटल स्थिर काष्ठा file_operations xhci_context_fops = अणु
	.खोलो			= xhci_context_खोलो,
	.पढ़ो			= seq_पढ़ो,
	.llseek			= seq_lseek,
	.release		= single_release,
पूर्ण;



अटल पूर्णांक xhci_portsc_show(काष्ठा seq_file *s, व्योम *unused)
अणु
	काष्ठा xhci_port	*port = s->निजी;
	u32			portsc;

	portsc = पढ़ोl(port->addr);
	seq_म_लिखो(s, "%s\n", xhci_decode_portsc(portsc));

	वापस 0;
पूर्ण

अटल पूर्णांक xhci_port_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	वापस single_खोलो(file, xhci_portsc_show, inode->i_निजी);
पूर्ण

अटल sमाप_प्रकार xhci_port_ग_लिखो(काष्ठा file *file,  स्थिर अक्षर __user *ubuf,
			       माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा seq_file         *s = file->निजी_data;
	काष्ठा xhci_port	*port = s->निजी;
	काष्ठा xhci_hcd		*xhci = hcd_to_xhci(port->rhub->hcd);
	अक्षर                    buf[32];
	u32			portsc;
	अचिन्हित दीर्घ		flags;

	अगर (copy_from_user(&buf, ubuf, min_t(माप_प्रकार, माप(buf) - 1, count)))
		वापस -EFAULT;

	अगर (!म_भेदन(buf, "compliance", 10)) अणु
		/* If CTC is clear, compliance is enabled by शेष */
		अगर (!HCC2_CTC(xhci->hcc_params2))
			वापस count;
		spin_lock_irqsave(&xhci->lock, flags);
		/* compliance mode can only be enabled on ports in RxDetect */
		portsc = पढ़ोl(port->addr);
		अगर ((portsc & PORT_PLS_MASK) != XDEV_RXDETECT) अणु
			spin_unlock_irqrestore(&xhci->lock, flags);
			वापस -EPERM;
		पूर्ण
		portsc = xhci_port_state_to_neutral(portsc);
		portsc &= ~PORT_PLS_MASK;
		portsc |= PORT_LINK_STROBE | XDEV_COMP_MODE;
		ग_लिखोl(portsc, port->addr);
		spin_unlock_irqrestore(&xhci->lock, flags);
	पूर्ण अन्यथा अणु
		वापस -EINVAL;
	पूर्ण
	वापस count;
पूर्ण

अटल स्थिर काष्ठा file_operations port_fops = अणु
	.खोलो			= xhci_port_खोलो,
	.ग_लिखो                  = xhci_port_ग_लिखो,
	.पढ़ो			= seq_पढ़ो,
	.llseek			= seq_lseek,
	.release		= single_release,
पूर्ण;

अटल व्योम xhci_debugfs_create_files(काष्ठा xhci_hcd *xhci,
				      काष्ठा xhci_file_map *files,
				      माप_प्रकार nentries, व्योम *data,
				      काष्ठा dentry *parent,
				      स्थिर काष्ठा file_operations *fops)
अणु
	पूर्णांक			i;

	क्रम (i = 0; i < nentries; i++)
		debugfs_create_file(files[i].name, 0444, parent, data, fops);
पूर्ण

अटल काष्ठा dentry *xhci_debugfs_create_ring_dir(काष्ठा xhci_hcd *xhci,
						   काष्ठा xhci_ring **ring,
						   स्थिर अक्षर *name,
						   काष्ठा dentry *parent)
अणु
	काष्ठा dentry		*dir;

	dir = debugfs_create_dir(name, parent);
	xhci_debugfs_create_files(xhci, ring_files, ARRAY_SIZE(ring_files),
				  ring, dir, &xhci_ring_fops);

	वापस dir;
पूर्ण

अटल व्योम xhci_debugfs_create_context_files(काष्ठा xhci_hcd *xhci,
					      काष्ठा dentry *parent,
					      पूर्णांक slot_id)
अणु
	काष्ठा xhci_virt_device	*dev = xhci->devs[slot_id];

	xhci_debugfs_create_files(xhci, context_files,
				  ARRAY_SIZE(context_files),
				  dev->debugfs_निजी,
				  parent, &xhci_context_fops);
पूर्ण

व्योम xhci_debugfs_create_endpoपूर्णांक(काष्ठा xhci_hcd *xhci,
				  काष्ठा xhci_virt_device *dev,
				  पूर्णांक ep_index)
अणु
	काष्ठा xhci_ep_priv	*epriv;
	काष्ठा xhci_slot_priv	*spriv = dev->debugfs_निजी;

	अगर (!spriv)
		वापस;

	अगर (spriv->eps[ep_index])
		वापस;

	epriv = kzalloc(माप(*epriv), GFP_KERNEL);
	अगर (!epriv)
		वापस;

	epriv->show_ring = dev->eps[ep_index].ring;

	snम_लिखो(epriv->name, माप(epriv->name), "ep%02d", ep_index);
	epriv->root = xhci_debugfs_create_ring_dir(xhci,
						   &epriv->show_ring,
						   epriv->name,
						   spriv->root);
	spriv->eps[ep_index] = epriv;
पूर्ण

व्योम xhci_debugfs_हटाओ_endpoपूर्णांक(काष्ठा xhci_hcd *xhci,
				  काष्ठा xhci_virt_device *dev,
				  पूर्णांक ep_index)
अणु
	काष्ठा xhci_ep_priv	*epriv;
	काष्ठा xhci_slot_priv	*spriv = dev->debugfs_निजी;

	अगर (!spriv || !spriv->eps[ep_index])
		वापस;

	epriv = spriv->eps[ep_index];
	debugfs_हटाओ_recursive(epriv->root);
	spriv->eps[ep_index] = शून्य;
	kमुक्त(epriv);
पूर्ण

अटल पूर्णांक xhci_stream_id_show(काष्ठा seq_file *s, व्योम *unused)
अणु
	काष्ठा xhci_ep_priv	*epriv = s->निजी;

	अगर (!epriv->stream_info)
		वापस -EPERM;

	seq_म_लिखो(s, "Show stream ID %d trb ring, supported [1 - %d]\n",
		   epriv->stream_id, epriv->stream_info->num_streams - 1);

	वापस 0;
पूर्ण

अटल पूर्णांक xhci_stream_id_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	वापस single_खोलो(file, xhci_stream_id_show, inode->i_निजी);
पूर्ण

अटल sमाप_प्रकार xhci_stream_id_ग_लिखो(काष्ठा file *file,  स्थिर अक्षर __user *ubuf,
			       माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा seq_file         *s = file->निजी_data;
	काष्ठा xhci_ep_priv	*epriv = s->निजी;
	पूर्णांक			ret;
	u16			stream_id; /* MaxPStreams + 1 <= 16 */

	अगर (!epriv->stream_info)
		वापस -EPERM;

	/* Decimal number */
	ret = kstrtou16_from_user(ubuf, count, 10, &stream_id);
	अगर (ret)
		वापस ret;

	अगर (stream_id == 0 || stream_id >= epriv->stream_info->num_streams)
		वापस -EINVAL;

	epriv->stream_id = stream_id;
	epriv->show_ring = epriv->stream_info->stream_rings[stream_id];

	वापस count;
पूर्ण

अटल स्थिर काष्ठा file_operations stream_id_fops = अणु
	.खोलो			= xhci_stream_id_खोलो,
	.ग_लिखो                  = xhci_stream_id_ग_लिखो,
	.पढ़ो			= seq_पढ़ो,
	.llseek			= seq_lseek,
	.release		= single_release,
पूर्ण;

अटल पूर्णांक xhci_stream_context_array_show(काष्ठा seq_file *s, व्योम *unused)
अणु
	काष्ठा xhci_ep_priv	*epriv = s->निजी;
	काष्ठा xhci_stream_ctx	*stream_ctx;
	dma_addr_t		dma;
	पूर्णांक			id;

	अगर (!epriv->stream_info)
		वापस -EPERM;

	seq_म_लिखो(s, "Allocated %d streams and %d stream context array entries\n",
			epriv->stream_info->num_streams,
			epriv->stream_info->num_stream_ctxs);

	क्रम (id = 0; id < epriv->stream_info->num_stream_ctxs; id++) अणु
		stream_ctx = epriv->stream_info->stream_ctx_array + id;
		dma = epriv->stream_info->ctx_array_dma + id * 16;
		अगर (id < epriv->stream_info->num_streams)
			seq_म_लिखो(s, "%pad stream id %d deq %016llx\n", &dma,
				   id, le64_to_cpu(stream_ctx->stream_ring));
		अन्यथा
			seq_म_लिखो(s, "%pad stream context entry not used deq %016llx\n",
				   &dma, le64_to_cpu(stream_ctx->stream_ring));
	पूर्ण

	वापस 0;
पूर्ण
DEFINE_SHOW_ATTRIBUTE(xhci_stream_context_array);

व्योम xhci_debugfs_create_stream_files(काष्ठा xhci_hcd *xhci,
				      काष्ठा xhci_virt_device *dev,
				      पूर्णांक ep_index)
अणु
	काष्ठा xhci_slot_priv	*spriv = dev->debugfs_निजी;
	काष्ठा xhci_ep_priv	*epriv;

	अगर (!spriv || !spriv->eps[ep_index] ||
	    !dev->eps[ep_index].stream_info)
		वापस;

	epriv = spriv->eps[ep_index];
	epriv->stream_info = dev->eps[ep_index].stream_info;

	/* Show trb ring of stream ID 1 by शेष */
	epriv->stream_id = 1;
	epriv->show_ring = epriv->stream_info->stream_rings[1];
	debugfs_create_file("stream_id", 0644,
			    epriv->root, epriv,
			    &stream_id_fops);
	debugfs_create_file("stream_context_array", 0444,
			    epriv->root, epriv,
			    &xhci_stream_context_array_fops);
पूर्ण

व्योम xhci_debugfs_create_slot(काष्ठा xhci_hcd *xhci, पूर्णांक slot_id)
अणु
	काष्ठा xhci_slot_priv	*priv;
	काष्ठा xhci_virt_device	*dev = xhci->devs[slot_id];

	priv = kzalloc(माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस;

	snम_लिखो(priv->name, माप(priv->name), "%02d", slot_id);
	priv->root = debugfs_create_dir(priv->name, xhci->debugfs_slots);
	priv->dev = dev;
	dev->debugfs_निजी = priv;

	xhci_debugfs_create_ring_dir(xhci, &dev->eps[0].ring,
				     "ep00", priv->root);

	xhci_debugfs_create_context_files(xhci, priv->root, slot_id);
पूर्ण

व्योम xhci_debugfs_हटाओ_slot(काष्ठा xhci_hcd *xhci, पूर्णांक slot_id)
अणु
	पूर्णांक			i;
	काष्ठा xhci_slot_priv	*priv;
	काष्ठा xhci_virt_device	*dev = xhci->devs[slot_id];

	अगर (!dev || !dev->debugfs_निजी)
		वापस;

	priv = dev->debugfs_निजी;

	debugfs_हटाओ_recursive(priv->root);

	क्रम (i = 0; i < 31; i++)
		kमुक्त(priv->eps[i]);

	kमुक्त(priv);
	dev->debugfs_निजी = शून्य;
पूर्ण

अटल व्योम xhci_debugfs_create_ports(काष्ठा xhci_hcd *xhci,
				      काष्ठा dentry *parent)
अणु
	अचिन्हित पूर्णांक		num_ports;
	अक्षर			port_name[8];
	काष्ठा xhci_port	*port;
	काष्ठा dentry		*dir;

	num_ports = HCS_MAX_PORTS(xhci->hcs_params1);

	parent = debugfs_create_dir("ports", parent);

	जबतक (num_ports--) अणु
		scnम_लिखो(port_name, माप(port_name), "port%02d",
			  num_ports + 1);
		dir = debugfs_create_dir(port_name, parent);
		port = &xhci->hw_ports[num_ports];
		debugfs_create_file("portsc", 0644, dir, port, &port_fops);
	पूर्ण
पूर्ण

व्योम xhci_debugfs_init(काष्ठा xhci_hcd *xhci)
अणु
	काष्ठा device		*dev = xhci_to_hcd(xhci)->self.controller;

	xhci->debugfs_root = debugfs_create_dir(dev_name(dev),
						xhci_debugfs_root);

	INIT_LIST_HEAD(&xhci->regset_list);

	xhci_debugfs_regset(xhci,
			    0,
			    xhci_cap_regs, ARRAY_SIZE(xhci_cap_regs),
			    xhci->debugfs_root, "reg-cap");

	xhci_debugfs_regset(xhci,
			    HC_LENGTH(पढ़ोl(&xhci->cap_regs->hc_capbase)),
			    xhci_op_regs, ARRAY_SIZE(xhci_op_regs),
			    xhci->debugfs_root, "reg-op");

	xhci_debugfs_regset(xhci,
			    पढ़ोl(&xhci->cap_regs->run_regs_off) & RTSOFF_MASK,
			    xhci_runसमय_regs, ARRAY_SIZE(xhci_runसमय_regs),
			    xhci->debugfs_root, "reg-runtime");

	xhci_debugfs_extcap_regset(xhci, XHCI_EXT_CAPS_LEGACY,
				   xhci_extcap_legsup,
				   ARRAY_SIZE(xhci_extcap_legsup),
				   "reg-ext-legsup");

	xhci_debugfs_extcap_regset(xhci, XHCI_EXT_CAPS_PROTOCOL,
				   xhci_extcap_protocol,
				   ARRAY_SIZE(xhci_extcap_protocol),
				   "reg-ext-protocol");

	xhci_debugfs_extcap_regset(xhci, XHCI_EXT_CAPS_DEBUG,
				   xhci_extcap_dbc,
				   ARRAY_SIZE(xhci_extcap_dbc),
				   "reg-ext-dbc");

	xhci_debugfs_create_ring_dir(xhci, &xhci->cmd_ring,
				     "command-ring",
				     xhci->debugfs_root);

	xhci_debugfs_create_ring_dir(xhci, &xhci->event_ring,
				     "event-ring",
				     xhci->debugfs_root);

	xhci->debugfs_slots = debugfs_create_dir("devices", xhci->debugfs_root);

	xhci_debugfs_create_ports(xhci, xhci->debugfs_root);
पूर्ण

व्योम xhci_debugfs_निकास(काष्ठा xhci_hcd *xhci)
अणु
	काष्ठा xhci_regset	*rgs, *पंचांगp;

	debugfs_हटाओ_recursive(xhci->debugfs_root);
	xhci->debugfs_root = शून्य;
	xhci->debugfs_slots = शून्य;

	list_क्रम_each_entry_safe(rgs, पंचांगp, &xhci->regset_list, list)
		xhci_debugfs_मुक्त_regset(rgs);
पूर्ण

व्योम __init xhci_debugfs_create_root(व्योम)
अणु
	xhci_debugfs_root = debugfs_create_dir("xhci", usb_debug_root);
पूर्ण

व्योम __निकास xhci_debugfs_हटाओ_root(व्योम)
अणु
	debugfs_हटाओ_recursive(xhci_debugfs_root);
	xhci_debugfs_root = शून्य;
पूर्ण
