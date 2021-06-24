<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Qualcomm Technologies HIDMA debug file
 *
 * Copyright (c) 2015-2016, The Linux Foundation. All rights reserved.
 */

#समावेश <linux/debugfs.h>
#समावेश <linux/device.h>
#समावेश <linux/list.h>
#समावेश <linux/pm_runसमय.स>

#समावेश "hidma.h"

अटल व्योम hidma_ll_chstats(काष्ठा seq_file *s, व्योम *llhndl, u32 tre_ch)
अणु
	काष्ठा hidma_lldev *lldev = llhndl;
	काष्ठा hidma_tre *tre;
	u32 length;
	dma_addr_t src_start;
	dma_addr_t dest_start;
	u32 *tre_local;

	अगर (tre_ch >= lldev->nr_tres) अणु
		dev_err(lldev->dev, "invalid TRE number in chstats:%d", tre_ch);
		वापस;
	पूर्ण
	tre = &lldev->trepool[tre_ch];
	seq_म_लिखो(s, "------Channel %d -----\n", tre_ch);
	seq_म_लिखो(s, "allocated=%d\n", atomic_पढ़ो(&tre->allocated));
	seq_म_लिखो(s, "queued = 0x%x\n", tre->queued);
	seq_म_लिखो(s, "err_info = 0x%x\n", tre->err_info);
	seq_म_लिखो(s, "err_code = 0x%x\n", tre->err_code);
	seq_म_लिखो(s, "status = 0x%x\n", tre->status);
	seq_म_लिखो(s, "idx = 0x%x\n", tre->idx);
	seq_म_लिखो(s, "dma_sig = 0x%x\n", tre->dma_sig);
	seq_म_लिखो(s, "dev_name=%s\n", tre->dev_name);
	seq_म_लिखो(s, "callback=%p\n", tre->callback);
	seq_म_लिखो(s, "data=%p\n", tre->data);
	seq_म_लिखो(s, "tre_index = 0x%x\n", tre->tre_index);

	tre_local = &tre->tre_local[0];
	src_start = tre_local[HIDMA_TRE_SRC_LOW_IDX];
	src_start = ((u64) (tre_local[HIDMA_TRE_SRC_HI_IDX]) << 32) + src_start;
	dest_start = tre_local[HIDMA_TRE_DEST_LOW_IDX];
	dest_start += ((u64) (tre_local[HIDMA_TRE_DEST_HI_IDX]) << 32);
	length = tre_local[HIDMA_TRE_LEN_IDX];

	seq_म_लिखो(s, "src=%pap\n", &src_start);
	seq_म_लिखो(s, "dest=%pap\n", &dest_start);
	seq_म_लिखो(s, "length = 0x%x\n", length);
पूर्ण

अटल व्योम hidma_ll_devstats(काष्ठा seq_file *s, व्योम *llhndl)
अणु
	काष्ठा hidma_lldev *lldev = llhndl;

	seq_माला_दो(s, "------Device -----\n");
	seq_म_लिखो(s, "lldev init = 0x%x\n", lldev->initialized);
	seq_म_लिखो(s, "trch_state = 0x%x\n", lldev->trch_state);
	seq_म_लिखो(s, "evch_state = 0x%x\n", lldev->evch_state);
	seq_म_लिखो(s, "chidx = 0x%x\n", lldev->chidx);
	seq_म_लिखो(s, "nr_tres = 0x%x\n", lldev->nr_tres);
	seq_म_लिखो(s, "trca=%p\n", lldev->trca);
	seq_म_लिखो(s, "tre_ring=%p\n", lldev->tre_ring);
	seq_म_लिखो(s, "tre_ring_handle=%pap\n", &lldev->tre_dma);
	seq_म_लिखो(s, "tre_ring_size = 0x%x\n", lldev->tre_ring_size);
	seq_म_लिखो(s, "tre_processed_off = 0x%x\n", lldev->tre_processed_off);
	seq_म_लिखो(s, "pending_tre_count=%d\n",
			atomic_पढ़ो(&lldev->pending_tre_count));
	seq_म_लिखो(s, "evca=%p\n", lldev->evca);
	seq_म_लिखो(s, "evre_ring=%p\n", lldev->evre_ring);
	seq_म_लिखो(s, "evre_ring_handle=%pap\n", &lldev->evre_dma);
	seq_म_लिखो(s, "evre_ring_size = 0x%x\n", lldev->evre_ring_size);
	seq_म_लिखो(s, "evre_processed_off = 0x%x\n", lldev->evre_processed_off);
	seq_म_लिखो(s, "tre_write_offset = 0x%x\n", lldev->tre_ग_लिखो_offset);
पूर्ण

/*
 * hidma_chan_show: display HIDMA channel statistics
 *
 * Display the statistics क्रम the current HIDMA भव channel device.
 */
अटल पूर्णांक hidma_chan_show(काष्ठा seq_file *s, व्योम *unused)
अणु
	काष्ठा hidma_chan *mchan = s->निजी;
	काष्ठा hidma_desc *mdesc;
	काष्ठा hidma_dev *dmadev = mchan->dmadev;

	pm_runसमय_get_sync(dmadev->ddev.dev);
	seq_म_लिखो(s, "paused=%u\n", mchan->छोड़ोd);
	seq_म_लिखो(s, "dma_sig=%u\n", mchan->dma_sig);
	seq_माला_दो(s, "prepared\n");
	list_क्रम_each_entry(mdesc, &mchan->prepared, node)
		hidma_ll_chstats(s, mchan->dmadev->lldev, mdesc->tre_ch);

	seq_माला_दो(s, "active\n");
	list_क्रम_each_entry(mdesc, &mchan->active, node)
		hidma_ll_chstats(s, mchan->dmadev->lldev, mdesc->tre_ch);

	seq_माला_दो(s, "completed\n");
	list_क्रम_each_entry(mdesc, &mchan->completed, node)
		hidma_ll_chstats(s, mchan->dmadev->lldev, mdesc->tre_ch);

	hidma_ll_devstats(s, mchan->dmadev->lldev);
	pm_runसमय_mark_last_busy(dmadev->ddev.dev);
	pm_runसमय_put_स्वतःsuspend(dmadev->ddev.dev);
	वापस 0;
पूर्ण

/*
 * hidma_dma_show: display HIDMA device info
 *
 * Display the info क्रम the current HIDMA device.
 */
अटल पूर्णांक hidma_dma_show(काष्ठा seq_file *s, व्योम *unused)
अणु
	काष्ठा hidma_dev *dmadev = s->निजी;
	resource_माप_प्रकार sz;

	seq_म_लिखो(s, "nr_descriptors=%d\n", dmadev->nr_descriptors);
	seq_म_लिखो(s, "dev_trca=%p\n", &dmadev->dev_trca);
	seq_म_लिखो(s, "dev_trca_phys=%pa\n", &dmadev->trca_resource->start);
	sz = resource_size(dmadev->trca_resource);
	seq_म_लिखो(s, "dev_trca_size=%pa\n", &sz);
	seq_म_लिखो(s, "dev_evca=%p\n", &dmadev->dev_evca);
	seq_म_लिखो(s, "dev_evca_phys=%pa\n", &dmadev->evca_resource->start);
	sz = resource_size(dmadev->evca_resource);
	seq_म_लिखो(s, "dev_evca_size=%pa\n", &sz);
	वापस 0;
पूर्ण

DEFINE_SHOW_ATTRIBUTE(hidma_chan);
DEFINE_SHOW_ATTRIBUTE(hidma_dma);

व्योम hidma_debug_uninit(काष्ठा hidma_dev *dmadev)
अणु
	debugfs_हटाओ_recursive(dmadev->debugfs);
पूर्ण

व्योम hidma_debug_init(काष्ठा hidma_dev *dmadev)
अणु
	पूर्णांक chidx = 0;
	काष्ठा list_head *position = शून्य;
	काष्ठा dentry *dir;

	dmadev->debugfs = debugfs_create_dir(dev_name(dmadev->ddev.dev), शून्य);

	/* walk through the भव channel list */
	list_क्रम_each(position, &dmadev->ddev.channels) अणु
		काष्ठा hidma_chan *chan;

		chan = list_entry(position, काष्ठा hidma_chan,
				  chan.device_node);
		प्र_लिखो(chan->dbg_name, "chan%d", chidx);
		dir = debugfs_create_dir(chan->dbg_name,
						   dmadev->debugfs);
		debugfs_create_file("stats", S_IRUGO, dir, chan,
				    &hidma_chan_fops);
		chidx++;
	पूर्ण

	debugfs_create_file("stats", S_IRUGO, dmadev->debugfs, dmadev,
			    &hidma_dma_fops);
पूर्ण
