<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2020, The Linux Foundation. All rights reserved.
 *
 */

#समावेश <linux/debugfs.h>
#समावेश <linux/device.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/list.h>
#समावेश <linux/mhi.h>
#समावेश <linux/module.h>
#समावेश "internal.h"

अटल पूर्णांक mhi_debugfs_states_show(काष्ठा seq_file *m, व्योम *d)
अणु
	काष्ठा mhi_controller *mhi_cntrl = m->निजी;

	/* states */
	seq_म_लिखो(m, "PM state: %s Device: %s MHI state: %s EE: %s wake: %s\n",
		   to_mhi_pm_state_str(mhi_cntrl->pm_state),
		   mhi_is_active(mhi_cntrl) ? "Active" : "Inactive",
		   TO_MHI_STATE_STR(mhi_cntrl->dev_state),
		   TO_MHI_EXEC_STR(mhi_cntrl->ee),
		   mhi_cntrl->wake_set ? "true" : "false");

	/* counters */
	seq_म_लिखो(m, "M0: %u M2: %u M3: %u", mhi_cntrl->M0, mhi_cntrl->M2,
		   mhi_cntrl->M3);

	seq_म_लिखो(m, " device wake: %u pending packets: %u\n",
		   atomic_पढ़ो(&mhi_cntrl->dev_wake),
		   atomic_पढ़ो(&mhi_cntrl->pending_pkts));

	वापस 0;
पूर्ण

अटल पूर्णांक mhi_debugfs_events_show(काष्ठा seq_file *m, व्योम *d)
अणु
	काष्ठा mhi_controller *mhi_cntrl = m->निजी;
	काष्ठा mhi_event *mhi_event;
	काष्ठा mhi_event_ctxt *er_ctxt;
	पूर्णांक i;

	अगर (!mhi_is_active(mhi_cntrl)) अणु
		seq_माला_दो(m, "Device not ready\n");
		वापस -ENODEV;
	पूर्ण

	er_ctxt = mhi_cntrl->mhi_ctxt->er_ctxt;
	mhi_event = mhi_cntrl->mhi_event;
	क्रम (i = 0; i < mhi_cntrl->total_ev_rings;
						i++, er_ctxt++, mhi_event++) अणु
		काष्ठा mhi_ring *ring = &mhi_event->ring;

		अगर (mhi_event->offload_ev) अणु
			seq_म_लिखो(m, "Index: %d is an offload event ring\n",
				   i);
			जारी;
		पूर्ण

		seq_म_लिखो(m, "Index: %d intmod count: %lu time: %lu",
			   i, (er_ctxt->पूर्णांकmod & EV_CTX_INTMODC_MASK) >>
			   EV_CTX_INTMODC_SHIFT,
			   (er_ctxt->पूर्णांकmod & EV_CTX_INTMODT_MASK) >>
			   EV_CTX_INTMODT_SHIFT);

		seq_म_लिखो(m, " base: 0x%0llx len: 0x%llx", er_ctxt->rbase,
			   er_ctxt->rlen);

		seq_म_लिखो(m, " rp: 0x%llx wp: 0x%llx", er_ctxt->rp,
			   er_ctxt->wp);

		seq_म_लिखो(m, " local rp: 0x%pK db: 0x%pad\n", ring->rp,
			   &mhi_event->db_cfg.db_val);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mhi_debugfs_channels_show(काष्ठा seq_file *m, व्योम *d)
अणु
	काष्ठा mhi_controller *mhi_cntrl = m->निजी;
	काष्ठा mhi_chan *mhi_chan;
	काष्ठा mhi_chan_ctxt *chan_ctxt;
	पूर्णांक i;

	अगर (!mhi_is_active(mhi_cntrl)) अणु
		seq_माला_दो(m, "Device not ready\n");
		वापस -ENODEV;
	पूर्ण

	mhi_chan = mhi_cntrl->mhi_chan;
	chan_ctxt = mhi_cntrl->mhi_ctxt->chan_ctxt;
	क्रम (i = 0; i < mhi_cntrl->max_chan; i++, chan_ctxt++, mhi_chan++) अणु
		काष्ठा mhi_ring *ring = &mhi_chan->tre_ring;

		अगर (mhi_chan->offload_ch) अणु
			seq_म_लिखो(m, "%s(%u) is an offload channel\n",
				   mhi_chan->name, mhi_chan->chan);
			जारी;
		पूर्ण

		अगर (!mhi_chan->mhi_dev)
			जारी;

		seq_म_लिखो(m,
			   "%s(%u) state: 0x%lx brstmode: 0x%lx pollcfg: 0x%lx",
			   mhi_chan->name, mhi_chan->chan, (chan_ctxt->chcfg &
			   CHAN_CTX_CHSTATE_MASK) >> CHAN_CTX_CHSTATE_SHIFT,
			   (chan_ctxt->chcfg & CHAN_CTX_BRSTMODE_MASK) >>
			   CHAN_CTX_BRSTMODE_SHIFT, (chan_ctxt->chcfg &
			   CHAN_CTX_POLLCFG_MASK) >> CHAN_CTX_POLLCFG_SHIFT);

		seq_म_लिखो(m, " type: 0x%x event ring: %u", chan_ctxt->chtype,
			   chan_ctxt->erindex);

		seq_म_लिखो(m, " base: 0x%llx len: 0x%llx rp: 0x%llx wp: 0x%llx",
			   chan_ctxt->rbase, chan_ctxt->rlen, chan_ctxt->rp,
			   chan_ctxt->wp);

		seq_म_लिखो(m, " local rp: 0x%pK local wp: 0x%pK db: 0x%pad\n",
			   ring->rp, ring->wp,
			   &mhi_chan->db_cfg.db_val);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mhi_device_info_show(काष्ठा device *dev, व्योम *data)
अणु
	काष्ठा mhi_device *mhi_dev;

	अगर (dev->bus != &mhi_bus_type)
		वापस 0;

	mhi_dev = to_mhi_device(dev);

	seq_म_लिखो((काष्ठा seq_file *)data, "%s: type: %s dev_wake: %u",
		   mhi_dev->name, mhi_dev->dev_type ? "Controller" : "Transfer",
		   mhi_dev->dev_wake);

	/* क्रम transfer device types only */
	अगर (mhi_dev->dev_type == MHI_DEVICE_XFER)
		seq_म_लिखो((काष्ठा seq_file *)data, " channels: %u(UL)/%u(DL)",
			   mhi_dev->ul_chan_id, mhi_dev->dl_chan_id);

	seq_माला_दो((काष्ठा seq_file *)data, "\n");

	वापस 0;
पूर्ण

अटल पूर्णांक mhi_debugfs_devices_show(काष्ठा seq_file *m, व्योम *d)
अणु
	काष्ठा mhi_controller *mhi_cntrl = m->निजी;

	अगर (!mhi_is_active(mhi_cntrl)) अणु
		seq_माला_दो(m, "Device not ready\n");
		वापस -ENODEV;
	पूर्ण

	/* Show controller and client(s) info */
	mhi_device_info_show(&mhi_cntrl->mhi_dev->dev, m);
	device_क्रम_each_child(&mhi_cntrl->mhi_dev->dev, m, mhi_device_info_show);

	वापस 0;
पूर्ण

अटल पूर्णांक mhi_debugfs_regdump_show(काष्ठा seq_file *m, व्योम *d)
अणु
	काष्ठा mhi_controller *mhi_cntrl = m->निजी;
	क्रमागत mhi_state state;
	क्रमागत mhi_ee_type ee;
	पूर्णांक i, ret = -EIO;
	u32 val;
	व्योम __iomem *mhi_base = mhi_cntrl->regs;
	व्योम __iomem *bhi_base = mhi_cntrl->bhi;
	व्योम __iomem *bhie_base = mhi_cntrl->bhie;
	व्योम __iomem *wake_db = mhi_cntrl->wake_db;
	काष्ठा अणु
		स्थिर अक्षर *name;
		पूर्णांक offset;
		व्योम __iomem *base;
	पूर्ण regs[] = अणु
		अणु "MHI_REGLEN", MHIREGLEN, mhi_baseपूर्ण,
		अणु "MHI_VER", MHIVER, mhi_baseपूर्ण,
		अणु "MHI_CFG", MHICFG, mhi_baseपूर्ण,
		अणु "MHI_CTRL", MHICTRL, mhi_baseपूर्ण,
		अणु "MHI_STATUS", MHISTATUS, mhi_baseपूर्ण,
		अणु "MHI_WAKE_DB", 0, wake_dbपूर्ण,
		अणु "BHI_EXECENV", BHI_EXECENV, bhi_baseपूर्ण,
		अणु "BHI_STATUS", BHI_STATUS, bhi_baseपूर्ण,
		अणु "BHI_ERRCODE", BHI_ERRCODE, bhi_baseपूर्ण,
		अणु "BHI_ERRDBG1", BHI_ERRDBG1, bhi_baseपूर्ण,
		अणु "BHI_ERRDBG2", BHI_ERRDBG2, bhi_baseपूर्ण,
		अणु "BHI_ERRDBG3", BHI_ERRDBG3, bhi_baseपूर्ण,
		अणु "BHIE_TXVEC_DB", BHIE_TXVECDB_OFFS, bhie_baseपूर्ण,
		अणु "BHIE_TXVEC_STATUS", BHIE_TXVECSTATUS_OFFS, bhie_baseपूर्ण,
		अणु "BHIE_RXVEC_DB", BHIE_RXVECDB_OFFS, bhie_baseपूर्ण,
		अणु "BHIE_RXVEC_STATUS", BHIE_RXVECSTATUS_OFFS, bhie_baseपूर्ण,
		अणु शून्य पूर्ण,
	पूर्ण;

	अगर (!MHI_REG_ACCESS_VALID(mhi_cntrl->pm_state))
		वापस ret;

	seq_म_लिखो(m, "Host PM state: %s Device state: %s EE: %s\n",
		   to_mhi_pm_state_str(mhi_cntrl->pm_state),
		   TO_MHI_STATE_STR(mhi_cntrl->dev_state),
		   TO_MHI_EXEC_STR(mhi_cntrl->ee));

	state = mhi_get_mhi_state(mhi_cntrl);
	ee = mhi_get_exec_env(mhi_cntrl);
	seq_म_लिखो(m, "Device EE: %s state: %s\n", TO_MHI_EXEC_STR(ee),
		   TO_MHI_STATE_STR(state));

	क्रम (i = 0; regs[i].name; i++) अणु
		अगर (!regs[i].base)
			जारी;
		ret = mhi_पढ़ो_reg(mhi_cntrl, regs[i].base, regs[i].offset,
				   &val);
		अगर (ret)
			जारी;

		seq_म_लिखो(m, "%s: 0x%x\n", regs[i].name, val);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mhi_debugfs_device_wake_show(काष्ठा seq_file *m, व्योम *d)
अणु
	काष्ठा mhi_controller *mhi_cntrl = m->निजी;
	काष्ठा mhi_device *mhi_dev = mhi_cntrl->mhi_dev;

	अगर (!mhi_is_active(mhi_cntrl)) अणु
		seq_माला_दो(m, "Device not ready\n");
		वापस -ENODEV;
	पूर्ण

	seq_म_लिखो(m,
		   "Wake count: %d\n%s\n", mhi_dev->dev_wake,
		   "Usage: echo get/put > device_wake to vote/unvote for M0");

	वापस 0;
पूर्ण

अटल sमाप_प्रकार mhi_debugfs_device_wake_ग_लिखो(काष्ठा file *file,
					     स्थिर अक्षर __user *ubuf,
					     माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा seq_file	*m = file->निजी_data;
	काष्ठा mhi_controller *mhi_cntrl = m->निजी;
	काष्ठा mhi_device *mhi_dev = mhi_cntrl->mhi_dev;
	अक्षर buf[16];
	पूर्णांक ret = -EINVAL;

	अगर (copy_from_user(&buf, ubuf, min_t(माप_प्रकार, माप(buf) - 1, count)))
		वापस -EFAULT;

	अगर (!म_भेदन(buf, "get", 3)) अणु
		ret = mhi_device_get_sync(mhi_dev);
	पूर्ण अन्यथा अगर (!म_भेदन(buf, "put", 3)) अणु
		mhi_device_put(mhi_dev);
		ret = 0;
	पूर्ण

	वापस ret ? ret : count;
पूर्ण

अटल पूर्णांक mhi_debugfs_समयout_ms_show(काष्ठा seq_file *m, व्योम *d)
अणु
	काष्ठा mhi_controller *mhi_cntrl = m->निजी;

	seq_म_लिखो(m, "%u ms\n", mhi_cntrl->समयout_ms);

	वापस 0;
पूर्ण

अटल sमाप_प्रकार mhi_debugfs_समयout_ms_ग_लिखो(काष्ठा file *file,
					    स्थिर अक्षर __user *ubuf,
					    माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा seq_file	*m = file->निजी_data;
	काष्ठा mhi_controller *mhi_cntrl = m->निजी;
	u32 समयout_ms;

	अगर (kstrtou32_from_user(ubuf, count, 0, &समयout_ms))
		वापस -EINVAL;

	mhi_cntrl->समयout_ms = समयout_ms;

	वापस count;
पूर्ण

अटल पूर्णांक mhi_debugfs_states_खोलो(काष्ठा inode *inode, काष्ठा file *fp)
अणु
	वापस single_खोलो(fp, mhi_debugfs_states_show, inode->i_निजी);
पूर्ण

अटल पूर्णांक mhi_debugfs_events_खोलो(काष्ठा inode *inode, काष्ठा file *fp)
अणु
	वापस single_खोलो(fp, mhi_debugfs_events_show, inode->i_निजी);
पूर्ण

अटल पूर्णांक mhi_debugfs_channels_खोलो(काष्ठा inode *inode, काष्ठा file *fp)
अणु
	वापस single_खोलो(fp, mhi_debugfs_channels_show, inode->i_निजी);
पूर्ण

अटल पूर्णांक mhi_debugfs_devices_खोलो(काष्ठा inode *inode, काष्ठा file *fp)
अणु
	वापस single_खोलो(fp, mhi_debugfs_devices_show, inode->i_निजी);
पूर्ण

अटल पूर्णांक mhi_debugfs_regdump_खोलो(काष्ठा inode *inode, काष्ठा file *fp)
अणु
	वापस single_खोलो(fp, mhi_debugfs_regdump_show, inode->i_निजी);
पूर्ण

अटल पूर्णांक mhi_debugfs_device_wake_खोलो(काष्ठा inode *inode, काष्ठा file *fp)
अणु
	वापस single_खोलो(fp, mhi_debugfs_device_wake_show, inode->i_निजी);
पूर्ण

अटल पूर्णांक mhi_debugfs_समयout_ms_खोलो(काष्ठा inode *inode, काष्ठा file *fp)
अणु
	वापस single_खोलो(fp, mhi_debugfs_समयout_ms_show, inode->i_निजी);
पूर्ण

अटल स्थिर काष्ठा file_operations debugfs_states_fops = अणु
	.खोलो = mhi_debugfs_states_खोलो,
	.release = single_release,
	.पढ़ो = seq_पढ़ो,
पूर्ण;

अटल स्थिर काष्ठा file_operations debugfs_events_fops = अणु
	.खोलो = mhi_debugfs_events_खोलो,
	.release = single_release,
	.पढ़ो = seq_पढ़ो,
पूर्ण;

अटल स्थिर काष्ठा file_operations debugfs_channels_fops = अणु
	.खोलो = mhi_debugfs_channels_खोलो,
	.release = single_release,
	.पढ़ो = seq_पढ़ो,
पूर्ण;

अटल स्थिर काष्ठा file_operations debugfs_devices_fops = अणु
	.खोलो = mhi_debugfs_devices_खोलो,
	.release = single_release,
	.पढ़ो = seq_पढ़ो,
पूर्ण;

अटल स्थिर काष्ठा file_operations debugfs_regdump_fops = अणु
	.खोलो = mhi_debugfs_regdump_खोलो,
	.release = single_release,
	.पढ़ो = seq_पढ़ो,
पूर्ण;

अटल स्थिर काष्ठा file_operations debugfs_device_wake_fops = अणु
	.खोलो = mhi_debugfs_device_wake_खोलो,
	.ग_लिखो = mhi_debugfs_device_wake_ग_लिखो,
	.release = single_release,
	.पढ़ो = seq_पढ़ो,
पूर्ण;

अटल स्थिर काष्ठा file_operations debugfs_समयout_ms_fops = अणु
	.खोलो = mhi_debugfs_समयout_ms_खोलो,
	.ग_लिखो = mhi_debugfs_समयout_ms_ग_लिखो,
	.release = single_release,
	.पढ़ो = seq_पढ़ो,
पूर्ण;

अटल काष्ठा dentry *mhi_debugfs_root;

व्योम mhi_create_debugfs(काष्ठा mhi_controller *mhi_cntrl)
अणु
	mhi_cntrl->debugfs_dentry =
			debugfs_create_dir(dev_name(&mhi_cntrl->mhi_dev->dev),
					   mhi_debugfs_root);

	debugfs_create_file("states", 0444, mhi_cntrl->debugfs_dentry,
			    mhi_cntrl, &debugfs_states_fops);
	debugfs_create_file("events", 0444, mhi_cntrl->debugfs_dentry,
			    mhi_cntrl, &debugfs_events_fops);
	debugfs_create_file("channels", 0444, mhi_cntrl->debugfs_dentry,
			    mhi_cntrl, &debugfs_channels_fops);
	debugfs_create_file("devices", 0444, mhi_cntrl->debugfs_dentry,
			    mhi_cntrl, &debugfs_devices_fops);
	debugfs_create_file("regdump", 0444, mhi_cntrl->debugfs_dentry,
			    mhi_cntrl, &debugfs_regdump_fops);
	debugfs_create_file("device_wake", 0644, mhi_cntrl->debugfs_dentry,
			    mhi_cntrl, &debugfs_device_wake_fops);
	debugfs_create_file("timeout_ms", 0644, mhi_cntrl->debugfs_dentry,
			    mhi_cntrl, &debugfs_समयout_ms_fops);
पूर्ण

व्योम mhi_destroy_debugfs(काष्ठा mhi_controller *mhi_cntrl)
अणु
	debugfs_हटाओ_recursive(mhi_cntrl->debugfs_dentry);
	mhi_cntrl->debugfs_dentry = शून्य;
पूर्ण

व्योम mhi_debugfs_init(व्योम)
अणु
	mhi_debugfs_root = debugfs_create_dir(mhi_bus_type.name, शून्य);
पूर्ण

व्योम mhi_debugfs_निकास(व्योम)
अणु
	debugfs_हटाओ_recursive(mhi_debugfs_root);
पूर्ण
