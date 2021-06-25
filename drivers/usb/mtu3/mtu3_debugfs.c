<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * mtu3_debugfs.c - debugfs पूर्णांकerface
 *
 * Copyright (C) 2019 MediaTek Inc.
 *
 * Author: Chunfeng Yun <chunfeng.yun@mediatek.com>
 */

#समावेश <linux/uaccess.h>

#समावेश "mtu3.h"
#समावेश "mtu3_dr.h"
#समावेश "mtu3_debug.h"

#घोषणा dump_रेजिस्टर(nm)		\
अणु					\
	.name = __stringअगरy(nm),	\
	.offset = U3D_ ##nm,		\
पूर्ण

#घोषणा dump_prb_reg(nm, os)	\
अणु				\
	.name = nm,		\
	.offset = os,		\
पूर्ण

अटल स्थिर काष्ठा debugfs_reg32 mtu3_ippc_regs[] = अणु
	dump_रेजिस्टर(SSUSB_IP_PW_CTRL0),
	dump_रेजिस्टर(SSUSB_IP_PW_CTRL1),
	dump_रेजिस्टर(SSUSB_IP_PW_CTRL2),
	dump_रेजिस्टर(SSUSB_IP_PW_CTRL3),
	dump_रेजिस्टर(SSUSB_OTG_STS),
	dump_रेजिस्टर(SSUSB_IP_XHCI_CAP),
	dump_रेजिस्टर(SSUSB_IP_DEV_CAP),
	dump_रेजिस्टर(SSUSB_U3_CTRL_0P),
	dump_रेजिस्टर(SSUSB_U2_CTRL_0P),
	dump_रेजिस्टर(SSUSB_HW_ID),
	dump_रेजिस्टर(SSUSB_HW_SUB_ID),
	dump_रेजिस्टर(SSUSB_IP_SPARE0),
पूर्ण;

अटल स्थिर काष्ठा debugfs_reg32 mtu3_dev_regs[] = अणु
	dump_रेजिस्टर(LV1ISR),
	dump_रेजिस्टर(LV1IER),
	dump_रेजिस्टर(EPISR),
	dump_रेजिस्टर(EPIER),
	dump_रेजिस्टर(EP0CSR),
	dump_रेजिस्टर(RXCOUNT0),
	dump_रेजिस्टर(QISAR0),
	dump_रेजिस्टर(QIER0),
	dump_रेजिस्टर(QISAR1),
	dump_रेजिस्टर(QIER1),
	dump_रेजिस्टर(CAP_EPNTXFFSZ),
	dump_रेजिस्टर(CAP_EPNRXFFSZ),
	dump_रेजिस्टर(CAP_EPINFO),
	dump_रेजिस्टर(MISC_CTRL),
पूर्ण;

अटल स्थिर काष्ठा debugfs_reg32 mtu3_csr_regs[] = अणु
	dump_रेजिस्टर(DEVICE_CONF),
	dump_रेजिस्टर(DEV_LINK_INTR_ENABLE),
	dump_रेजिस्टर(DEV_LINK_INTR),
	dump_रेजिस्टर(LTSSM_CTRL),
	dump_रेजिस्टर(USB3_CONFIG),
	dump_रेजिस्टर(LINK_STATE_MACHINE),
	dump_रेजिस्टर(LTSSM_INTR_ENABLE),
	dump_रेजिस्टर(LTSSM_INTR),
	dump_रेजिस्टर(U3U2_SWITCH_CTRL),
	dump_रेजिस्टर(POWER_MANAGEMENT),
	dump_रेजिस्टर(DEVICE_CONTROL),
	dump_रेजिस्टर(COMMON_USB_INTR_ENABLE),
	dump_रेजिस्टर(COMMON_USB_INTR),
	dump_रेजिस्टर(USB20_MISC_CONTROL),
	dump_रेजिस्टर(USB20_OPSTATE),
पूर्ण;

अटल पूर्णांक mtu3_link_state_show(काष्ठा seq_file *sf, व्योम *unused)
अणु
	काष्ठा mtu3 *mtu = sf->निजी;
	व्योम __iomem *mbase = mtu->mac_base;

	seq_म_लिखो(sf, "opstate: %#x, ltssm: %#x\n",
		   mtu3_पढ़ोl(mbase, U3D_USB20_OPSTATE),
		   LTSSM_STATE(mtu3_पढ़ोl(mbase, U3D_LINK_STATE_MACHINE)));

	वापस 0;
पूर्ण

अटल पूर्णांक mtu3_ep_used_show(काष्ठा seq_file *sf, व्योम *unused)
अणु
	काष्ठा mtu3 *mtu = sf->निजी;
	काष्ठा mtu3_ep *mep;
	अचिन्हित दीर्घ flags;
	पूर्णांक used = 0;
	पूर्णांक i;

	spin_lock_irqsave(&mtu->lock, flags);

	क्रम (i = 0; i < mtu->num_eps; i++) अणु
		mep = mtu->in_eps + i;
		अगर (mep->flags & MTU3_EP_ENABLED) अणु
			seq_म_लिखो(sf, "%s - type: %d\n", mep->name, mep->type);
			used++;
		पूर्ण

		mep = mtu->out_eps + i;
		अगर (mep->flags & MTU3_EP_ENABLED) अणु
			seq_म_लिखो(sf, "%s - type: %d\n", mep->name, mep->type);
			used++;
		पूर्ण
	पूर्ण
	seq_म_लिखो(sf, "total used: %d eps\n", used);

	spin_unlock_irqrestore(&mtu->lock, flags);

	वापस 0;
पूर्ण

DEFINE_SHOW_ATTRIBUTE(mtu3_link_state);
DEFINE_SHOW_ATTRIBUTE(mtu3_ep_used);

अटल व्योम mtu3_debugfs_regset(काष्ठा mtu3 *mtu, व्योम __iomem *base,
				स्थिर काष्ठा debugfs_reg32 *regs, माप_प्रकार nregs,
				स्थिर अक्षर *name, काष्ठा dentry *parent)
अणु
	काष्ठा debugfs_regset32 *regset;
	काष्ठा mtu3_regset *mregs;

	mregs = devm_kzalloc(mtu->dev, माप(*mregs), GFP_KERNEL);
	अगर (!mregs)
		वापस;

	प्र_लिखो(mregs->name, "%s", name);
	regset = &mregs->regset;
	regset->regs = regs;
	regset->nregs = nregs;
	regset->base = base;

	debugfs_create_regset32(mregs->name, 0444, parent, regset);
पूर्ण

अटल व्योम mtu3_debugfs_ep_regset(काष्ठा mtu3 *mtu, काष्ठा mtu3_ep *mep,
				   काष्ठा dentry *parent)
अणु
	काष्ठा debugfs_reg32 *regs;
	पूर्णांक epnum = mep->epnum;
	पूर्णांक in = mep->is_in;

	regs = devm_kसुस्मृति(mtu->dev, 7, माप(*regs), GFP_KERNEL);
	अगर (!regs)
		वापस;

	regs[0].name = in ? "TCR0" : "RCR0";
	regs[0].offset = in ? MU3D_EP_TXCR0(epnum) : MU3D_EP_RXCR0(epnum);
	regs[1].name = in ? "TCR1" : "RCR1";
	regs[1].offset = in ? MU3D_EP_TXCR1(epnum) : MU3D_EP_RXCR1(epnum);
	regs[2].name = in ? "TCR2" : "RCR2";
	regs[2].offset = in ? MU3D_EP_TXCR2(epnum) : MU3D_EP_RXCR2(epnum);
	regs[3].name = in ? "TQHIAR" : "RQHIAR";
	regs[3].offset = in ? USB_QMU_TQHIAR(epnum) : USB_QMU_RQHIAR(epnum);
	regs[4].name = in ? "TQCSR" : "RQCSR";
	regs[4].offset = in ? USB_QMU_TQCSR(epnum) : USB_QMU_RQCSR(epnum);
	regs[5].name = in ? "TQSAR" : "RQSAR";
	regs[5].offset = in ? USB_QMU_TQSAR(epnum) : USB_QMU_RQSAR(epnum);
	regs[6].name = in ? "TQCPR" : "RQCPR";
	regs[6].offset = in ? USB_QMU_TQCPR(epnum) : USB_QMU_RQCPR(epnum);

	mtu3_debugfs_regset(mtu, mtu->mac_base, regs, 7, "ep-regs", parent);
पूर्ण

अटल पूर्णांक mtu3_ep_info_show(काष्ठा seq_file *sf, व्योम *unused)
अणु
	काष्ठा mtu3_ep *mep = sf->निजी;
	काष्ठा mtu3 *mtu = mep->mtu;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&mtu->lock, flags);
	seq_म_लिखो(sf, "ep - type:%d, maxp:%d, slot:%d, flags:%x\n",
		   mep->type, mep->maxp, mep->slot, mep->flags);
	spin_unlock_irqrestore(&mtu->lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक mtu3_fअगरo_show(काष्ठा seq_file *sf, व्योम *unused)
अणु
	काष्ठा mtu3_ep *mep = sf->निजी;
	काष्ठा mtu3 *mtu = mep->mtu;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&mtu->lock, flags);
	seq_म_लिखो(sf, "fifo - seg_size:%d, addr:%d, size:%d\n",
		   mep->fअगरo_seg_size, mep->fअगरo_addr, mep->fअगरo_size);
	spin_unlock_irqrestore(&mtu->lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक mtu3_qmu_ring_show(काष्ठा seq_file *sf, व्योम *unused)
अणु
	काष्ठा mtu3_ep *mep = sf->निजी;
	काष्ठा mtu3 *mtu = mep->mtu;
	काष्ठा mtu3_gpd_ring *ring;
	अचिन्हित दीर्घ flags;

	ring = &mep->gpd_ring;
	spin_lock_irqsave(&mtu->lock, flags);
	seq_म_लिखो(sf,
		   "qmu-ring - dma:%pad, start:%p, end:%p, enq:%p, dep:%p\n",
		   &ring->dma, ring->start, ring->end,
		   ring->enqueue, ring->dequeue);
	spin_unlock_irqrestore(&mtu->lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक mtu3_qmu_gpd_show(काष्ठा seq_file *sf, व्योम *unused)
अणु
	काष्ठा mtu3_ep *mep = sf->निजी;
	काष्ठा mtu3 *mtu = mep->mtu;
	काष्ठा mtu3_gpd_ring *ring;
	काष्ठा qmu_gpd *gpd;
	dma_addr_t dma;
	अचिन्हित दीर्घ flags;
	पूर्णांक i;

	spin_lock_irqsave(&mtu->lock, flags);
	ring = &mep->gpd_ring;
	gpd = ring->start;
	अगर (!gpd || !(mep->flags & MTU3_EP_ENABLED)) अणु
		seq_माला_दो(sf, "empty!\n");
		जाओ out;
	पूर्ण

	क्रम (i = 0; i < MAX_GPD_NUM; i++, gpd++) अणु
		dma = ring->dma + i * माप(*gpd);
		seq_म_लिखो(sf, "gpd.%03d -> %pad, %p: %08x %08x %08x %08x\n",
			   i, &dma, gpd, gpd->dw0_info, gpd->next_gpd,
			   gpd->buffer, gpd->dw3_info);
	पूर्ण

out:
	spin_unlock_irqrestore(&mtu->lock, flags);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा mtu3_file_map mtu3_ep_files[] = अणु
	अणु"ep-info", mtu3_ep_info_show, पूर्ण,
	अणु"fifo", mtu3_fअगरo_show, पूर्ण,
	अणु"qmu-ring", mtu3_qmu_ring_show, पूर्ण,
	अणु"qmu-gpd", mtu3_qmu_gpd_show, पूर्ण,
पूर्ण;

अटल पूर्णांक mtu3_ep_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	स्थिर अक्षर *file_name = file_dentry(file)->d_iname;
	स्थिर काष्ठा mtu3_file_map *f_map;
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(mtu3_ep_files); i++) अणु
		f_map = &mtu3_ep_files[i];

		अगर (म_भेद(f_map->name, file_name) == 0)
			अवरोध;
	पूर्ण

	वापस single_खोलो(file, f_map->show, inode->i_निजी);
पूर्ण

अटल स्थिर काष्ठा file_operations mtu3_ep_fops = अणु
	.खोलो = mtu3_ep_खोलो,
	.पढ़ो = seq_पढ़ो,
	.llseek = seq_lseek,
	.release = single_release,
पूर्ण;

अटल स्थिर काष्ठा debugfs_reg32 mtu3_prb_regs[] = अणु
	dump_prb_reg("enable", U3D_SSUSB_PRB_CTRL0),
	dump_prb_reg("byte-sell", U3D_SSUSB_PRB_CTRL1),
	dump_prb_reg("byte-selh", U3D_SSUSB_PRB_CTRL2),
	dump_prb_reg("module-sel", U3D_SSUSB_PRB_CTRL3),
	dump_prb_reg("sw-out", U3D_SSUSB_PRB_CTRL4),
	dump_prb_reg("data", U3D_SSUSB_PRB_CTRL5),
पूर्ण;

अटल पूर्णांक mtu3_probe_show(काष्ठा seq_file *sf, व्योम *unused)
अणु
	स्थिर अक्षर *file_name = file_dentry(sf->file)->d_iname;
	काष्ठा mtu3 *mtu = sf->निजी;
	स्थिर काष्ठा debugfs_reg32 *regs;
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(mtu3_prb_regs); i++) अणु
		regs = &mtu3_prb_regs[i];

		अगर (म_भेद(regs->name, file_name) == 0)
			अवरोध;
	पूर्ण

	seq_म_लिखो(sf, "0x%04x - 0x%08x\n", (u32)regs->offset,
		   mtu3_पढ़ोl(mtu->ippc_base, (u32)regs->offset));

	वापस 0;
पूर्ण

अटल पूर्णांक mtu3_probe_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	वापस single_खोलो(file, mtu3_probe_show, inode->i_निजी);
पूर्ण

अटल sमाप_प्रकार mtu3_probe_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *ubuf,
				माप_प्रकार count, loff_t *ppos)
अणु
	स्थिर अक्षर *file_name = file_dentry(file)->d_iname;
	काष्ठा seq_file *sf = file->निजी_data;
	काष्ठा mtu3 *mtu = sf->निजी;
	स्थिर काष्ठा debugfs_reg32 *regs;
	अक्षर buf[32];
	u32 val;
	पूर्णांक i;

	अगर (copy_from_user(&buf, ubuf, min_t(माप_प्रकार, माप(buf) - 1, count)))
		वापस -EFAULT;

	अगर (kstrtou32(buf, 0, &val))
		वापस -EINVAL;

	क्रम (i = 0; i < ARRAY_SIZE(mtu3_prb_regs); i++) अणु
		regs = &mtu3_prb_regs[i];

		अगर (म_भेद(regs->name, file_name) == 0)
			अवरोध;
	पूर्ण
	mtu3_ग_लिखोl(mtu->ippc_base, (u32)regs->offset, val);

	वापस count;
पूर्ण

अटल स्थिर काष्ठा file_operations mtu3_probe_fops = अणु
	.खोलो = mtu3_probe_खोलो,
	.ग_लिखो = mtu3_probe_ग_लिखो,
	.पढ़ो = seq_पढ़ो,
	.llseek = seq_lseek,
	.release = single_release,
पूर्ण;

अटल व्योम mtu3_debugfs_create_prb_files(काष्ठा mtu3 *mtu)
अणु
	काष्ठा ssusb_mtk *ssusb = mtu->ssusb;
	स्थिर काष्ठा debugfs_reg32 *regs;
	काष्ठा dentry *dir_prb;
	पूर्णांक i;

	dir_prb = debugfs_create_dir("probe", ssusb->dbgfs_root);

	क्रम (i = 0; i < ARRAY_SIZE(mtu3_prb_regs); i++) अणु
		regs = &mtu3_prb_regs[i];
		debugfs_create_file(regs->name, 0644, dir_prb,
				    mtu, &mtu3_probe_fops);
	पूर्ण

	mtu3_debugfs_regset(mtu, mtu->ippc_base, mtu3_prb_regs,
			    ARRAY_SIZE(mtu3_prb_regs), "regs", dir_prb);
पूर्ण

अटल व्योम mtu3_debugfs_create_ep_dir(काष्ठा mtu3_ep *mep,
				       काष्ठा dentry *parent)
अणु
	स्थिर काष्ठा mtu3_file_map *files;
	काष्ठा dentry *dir_ep;
	पूर्णांक i;

	dir_ep = debugfs_create_dir(mep->name, parent);
	mtu3_debugfs_ep_regset(mep->mtu, mep, dir_ep);

	क्रम (i = 0; i < ARRAY_SIZE(mtu3_ep_files); i++) अणु
		files = &mtu3_ep_files[i];

		debugfs_create_file(files->name, 0444, dir_ep,
				    mep, &mtu3_ep_fops);
	पूर्ण
पूर्ण

अटल व्योम mtu3_debugfs_create_ep_dirs(काष्ठा mtu3 *mtu)
अणु
	काष्ठा ssusb_mtk *ssusb = mtu->ssusb;
	काष्ठा dentry *dir_eps;
	पूर्णांक i;

	dir_eps = debugfs_create_dir("eps", ssusb->dbgfs_root);

	क्रम (i = 1; i < mtu->num_eps; i++) अणु
		mtu3_debugfs_create_ep_dir(mtu->in_eps + i, dir_eps);
		mtu3_debugfs_create_ep_dir(mtu->out_eps + i, dir_eps);
	पूर्ण
पूर्ण

व्योम ssusb_dev_debugfs_init(काष्ठा ssusb_mtk *ssusb)
अणु
	काष्ठा mtu3 *mtu = ssusb->u3d;
	काष्ठा dentry *dir_regs;

	dir_regs = debugfs_create_dir("regs", ssusb->dbgfs_root);

	mtu3_debugfs_regset(mtu, mtu->ippc_base,
			    mtu3_ippc_regs, ARRAY_SIZE(mtu3_ippc_regs),
			    "reg-ippc", dir_regs);

	mtu3_debugfs_regset(mtu, mtu->mac_base,
			    mtu3_dev_regs, ARRAY_SIZE(mtu3_dev_regs),
			    "reg-dev", dir_regs);

	mtu3_debugfs_regset(mtu, mtu->mac_base,
			    mtu3_csr_regs, ARRAY_SIZE(mtu3_csr_regs),
			    "reg-csr", dir_regs);

	mtu3_debugfs_create_ep_dirs(mtu);

	mtu3_debugfs_create_prb_files(mtu);

	debugfs_create_file("link-state", 0444, ssusb->dbgfs_root,
			    mtu, &mtu3_link_state_fops);
	debugfs_create_file("ep-used", 0444, ssusb->dbgfs_root,
			    mtu, &mtu3_ep_used_fops);
पूर्ण

अटल पूर्णांक ssusb_mode_show(काष्ठा seq_file *sf, व्योम *unused)
अणु
	काष्ठा ssusb_mtk *ssusb = sf->निजी;

	seq_म_लिखो(sf, "current mode: %s(%s drd)\n(echo device/host)\n",
		   ssusb->is_host ? "host" : "device",
		   ssusb->otg_चयन.manual_drd_enabled ? "manual" : "auto");

	वापस 0;
पूर्ण

अटल पूर्णांक ssusb_mode_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	वापस single_खोलो(file, ssusb_mode_show, inode->i_निजी);
पूर्ण

अटल sमाप_प्रकार ssusb_mode_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *ubuf,
				माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा seq_file *sf = file->निजी_data;
	काष्ठा ssusb_mtk *ssusb = sf->निजी;
	अक्षर buf[16];

	अगर (copy_from_user(&buf, ubuf, min_t(माप_प्रकार, माप(buf) - 1, count)))
		वापस -EFAULT;

	अगर (!म_भेदन(buf, "host", 4) && !ssusb->is_host) अणु
		ssusb_mode_चयन(ssusb, 1);
	पूर्ण अन्यथा अगर (!म_भेदन(buf, "device", 6) && ssusb->is_host) अणु
		ssusb_mode_चयन(ssusb, 0);
	पूर्ण अन्यथा अणु
		dev_err(ssusb->dev, "wrong or duplicated setting\n");
		वापस -EINVAL;
	पूर्ण

	वापस count;
पूर्ण

अटल स्थिर काष्ठा file_operations ssusb_mode_fops = अणु
	.खोलो = ssusb_mode_खोलो,
	.ग_लिखो = ssusb_mode_ग_लिखो,
	.पढ़ो = seq_पढ़ो,
	.llseek = seq_lseek,
	.release = single_release,
पूर्ण;

अटल पूर्णांक ssusb_vbus_show(काष्ठा seq_file *sf, व्योम *unused)
अणु
	काष्ठा ssusb_mtk *ssusb = sf->निजी;
	काष्ठा otg_चयन_mtk *otg_sx = &ssusb->otg_चयन;

	seq_म_लिखो(sf, "vbus state: %s\n(echo on/off)\n",
		   regulator_is_enabled(otg_sx->vbus) ? "on" : "off");

	वापस 0;
पूर्ण

अटल पूर्णांक ssusb_vbus_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	वापस single_खोलो(file, ssusb_vbus_show, inode->i_निजी);
पूर्ण

अटल sमाप_प्रकार ssusb_vbus_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *ubuf,
				माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा seq_file *sf = file->निजी_data;
	काष्ठा ssusb_mtk *ssusb = sf->निजी;
	काष्ठा otg_चयन_mtk *otg_sx = &ssusb->otg_चयन;
	अक्षर buf[16];
	bool enable;

	अगर (copy_from_user(&buf, ubuf, min_t(माप_प्रकार, माप(buf) - 1, count)))
		वापस -EFAULT;

	अगर (kstrtobool(buf, &enable)) अणु
		dev_err(ssusb->dev, "wrong setting\n");
		वापस -EINVAL;
	पूर्ण

	ssusb_set_vbus(otg_sx, enable);

	वापस count;
पूर्ण

अटल स्थिर काष्ठा file_operations ssusb_vbus_fops = अणु
	.खोलो = ssusb_vbus_खोलो,
	.ग_लिखो = ssusb_vbus_ग_लिखो,
	.पढ़ो = seq_पढ़ो,
	.llseek = seq_lseek,
	.release = single_release,
पूर्ण;

व्योम ssusb_dr_debugfs_init(काष्ठा ssusb_mtk *ssusb)
अणु
	काष्ठा dentry *root = ssusb->dbgfs_root;

	debugfs_create_file("mode", 0644, root, ssusb, &ssusb_mode_fops);
	debugfs_create_file("vbus", 0644, root, ssusb, &ssusb_vbus_fops);
पूर्ण

व्योम ssusb_debugfs_create_root(काष्ठा ssusb_mtk *ssusb)
अणु
	ssusb->dbgfs_root =
		debugfs_create_dir(dev_name(ssusb->dev), usb_debug_root);
पूर्ण

व्योम ssusb_debugfs_हटाओ_root(काष्ठा ssusb_mtk *ssusb)
अणु
	debugfs_हटाओ_recursive(ssusb->dbgfs_root);
	ssusb->dbgfs_root = शून्य;
पूर्ण
