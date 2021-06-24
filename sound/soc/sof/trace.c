<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0-only OR BSD-3-Clause)
//
// This file is provided under a dual BSD/GPLv2 license.  When using or
// redistributing this file, you may करो so under either license.
//
// Copyright(c) 2018 Intel Corporation. All rights reserved.
//
// Author: Liam Girdwood <liam.r.girdwood@linux.पूर्णांकel.com>
//

#समावेश <linux/debugfs.h>
#समावेश <linux/sched/संकेत.स>
#समावेश "sof-priv.h"
#समावेश "ops.h"

#घोषणा TRACE_FILTER_ELEMENTS_PER_ENTRY 4
#घोषणा TRACE_FILTER_MAX_CONFIG_STRING_LENGTH 1024

अटल पूर्णांक trace_filter_append_elem(काष्ठा snd_sof_dev *sdev, uपूर्णांक32_t key, uपूर्णांक32_t value,
				    काष्ठा sof_ipc_trace_filter_elem *elem_list,
				    पूर्णांक capacity, पूर्णांक *counter)
अणु
	अगर (*counter >= capacity)
		वापस -ENOMEM;

	elem_list[*counter].key = key;
	elem_list[*counter].value = value;
	++*counter;

	वापस 0;
पूर्ण

अटल पूर्णांक trace_filter_parse_entry(काष्ठा snd_sof_dev *sdev, स्थिर अक्षर *line,
				    काष्ठा sof_ipc_trace_filter_elem *elem,
				    पूर्णांक capacity, पूर्णांक *counter)
अणु
	पूर्णांक len = म_माप(line);
	पूर्णांक cnt = *counter;
	uपूर्णांक32_t uuid_id;
	पूर्णांक log_level;
	पूर्णांक pipe_id;
	पूर्णांक comp_id;
	पूर्णांक पढ़ो;
	पूर्णांक ret;

	/* ignore empty content */
	ret = माला_पूछो(line, " %n", &पढ़ो);
	अगर (!ret && पढ़ो == len)
		वापस len;

	ret = माला_पूछो(line, " %d %x %d %d %n", &log_level, &uuid_id, &pipe_id, &comp_id, &पढ़ो);
	अगर (ret != TRACE_FILTER_ELEMENTS_PER_ENTRY || पढ़ो != len) अणु
		dev_err(sdev->dev, "error: invalid trace filter entry '%s'\n", line);
		वापस -EINVAL;
	पूर्ण

	अगर (uuid_id > 0) अणु
		ret = trace_filter_append_elem(sdev, SOF_IPC_TRACE_FILTER_ELEM_BY_UUID,
					       uuid_id, elem, capacity, &cnt);
		अगर (ret)
			वापस ret;
	पूर्ण
	अगर (pipe_id >= 0) अणु
		ret = trace_filter_append_elem(sdev, SOF_IPC_TRACE_FILTER_ELEM_BY_PIPE,
					       pipe_id, elem, capacity, &cnt);
		अगर (ret)
			वापस ret;
	पूर्ण
	अगर (comp_id >= 0) अणु
		ret = trace_filter_append_elem(sdev, SOF_IPC_TRACE_FILTER_ELEM_BY_COMP,
					       comp_id, elem, capacity, &cnt);
		अगर (ret)
			वापस ret;
	पूर्ण

	ret = trace_filter_append_elem(sdev, SOF_IPC_TRACE_FILTER_ELEM_SET_LEVEL |
				       SOF_IPC_TRACE_FILTER_ELEM_FIN,
				       log_level, elem, capacity, &cnt);
	अगर (ret)
		वापस ret;

	/* update counter only when parsing whole entry passed */
	*counter = cnt;

	वापस len;
पूर्ण

अटल पूर्णांक trace_filter_parse(काष्ठा snd_sof_dev *sdev, अक्षर *string,
			      पूर्णांक *out_elem_cnt,
			      काष्ठा sof_ipc_trace_filter_elem **out)
अणु
	अटल स्थिर अक्षर entry_delimiter[] = ";";
	अक्षर *entry = string;
	पूर्णांक capacity = 0;
	पूर्णांक entry_len;
	पूर्णांक cnt = 0;

	/*
	 * Each entry contains at least 1, up to TRACE_FILTER_ELEMENTS_PER_ENTRY
	 * IPC elements, depending on content. Calculate IPC elements capacity
	 * क्रम the input string where each element is set.
	 */
	जबतक (entry) अणु
		capacity += TRACE_FILTER_ELEMENTS_PER_ENTRY;
		entry = म_अक्षर(entry + 1, entry_delimiter[0]);
	पूर्ण
	*out = kदो_स्मृति(capacity * माप(**out), GFP_KERNEL);
	अगर (!*out)
		वापस -ENOMEM;

	/* split input string by ';', and parse each entry separately in trace_filter_parse_entry */
	जबतक ((entry = strsep(&string, entry_delimiter))) अणु
		entry_len = trace_filter_parse_entry(sdev, entry, *out, capacity, &cnt);
		अगर (entry_len < 0) अणु
			dev_err(sdev->dev, "error: %s failed for '%s', %d\n", __func__, entry,
				entry_len);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	*out_elem_cnt = cnt;

	वापस 0;
पूर्ण

अटल पूर्णांक sof_ipc_trace_update_filter(काष्ठा snd_sof_dev *sdev, पूर्णांक num_elems,
				       काष्ठा sof_ipc_trace_filter_elem *elems)
अणु
	काष्ठा sof_ipc_trace_filter *msg;
	काष्ठा sof_ipc_reply reply;
	माप_प्रकार size;
	पूर्णांक ret;

	size = काष्ठा_size(msg, elems, num_elems);
	अगर (size > SOF_IPC_MSG_MAX_SIZE)
		वापस -EINVAL;

	msg = kदो_स्मृति(size, GFP_KERNEL);
	अगर (!msg)
		वापस -ENOMEM;

	msg->hdr.size = size;
	msg->hdr.cmd = SOF_IPC_GLB_TRACE_MSG | SOF_IPC_TRACE_FILTER_UPDATE;
	msg->elem_cnt = num_elems;
	स_नकल(&msg->elems[0], elems, num_elems * माप(*elems));

	ret = pm_runसमय_get_sync(sdev->dev);
	अगर (ret < 0 && ret != -EACCES) अणु
		pm_runसमय_put_noidle(sdev->dev);
		dev_err(sdev->dev, "error: enabling device failed: %d\n", ret);
		जाओ error;
	पूर्ण
	ret = sof_ipc_tx_message(sdev->ipc, msg->hdr.cmd, msg, msg->hdr.size,
				 &reply, माप(reply));
	pm_runसमय_mark_last_busy(sdev->dev);
	pm_runसमय_put_स्वतःsuspend(sdev->dev);

error:
	kमुक्त(msg);
	वापस ret ? ret : reply.error;
पूर्ण

अटल sमाप_प्रकार sof_dfsentry_trace_filter_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *from,
					       माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा snd_sof_dfsentry *dfse = file->निजी_data;
	काष्ठा sof_ipc_trace_filter_elem *elems = शून्य;
	काष्ठा snd_sof_dev *sdev = dfse->sdev;
	loff_t pos = 0;
	पूर्णांक num_elems;
	अक्षर *string;
	पूर्णांक ret;

	अगर (count > TRACE_FILTER_MAX_CONFIG_STRING_LENGTH) अणु
		dev_err(sdev->dev, "%s too long input, %zu > %d\n", __func__, count,
			TRACE_FILTER_MAX_CONFIG_STRING_LENGTH);
		वापस -EINVAL;
	पूर्ण

	string = kदो_स्मृति(count + 1, GFP_KERNEL);
	अगर (!string)
		वापस -ENOMEM;

	/* निश्चित null termination */
	string[count] = 0;
	ret = simple_ग_लिखो_to_buffer(string, count, &pos, from, count);
	अगर (ret < 0)
		जाओ error;

	ret = trace_filter_parse(sdev, string, &num_elems, &elems);
	अगर (ret < 0) अणु
		dev_err(sdev->dev, "error: fail in trace_filter_parse, %d\n", ret);
		जाओ error;
	पूर्ण

	अगर (num_elems) अणु
		ret = sof_ipc_trace_update_filter(sdev, num_elems, elems);
		अगर (ret < 0) अणु
			dev_err(sdev->dev, "error: fail in sof_ipc_trace_update_filter %d\n", ret);
			जाओ error;
		पूर्ण
	पूर्ण
	ret = count;
error:
	kमुक्त(string);
	kमुक्त(elems);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा file_operations sof_dfs_trace_filter_fops = अणु
	.खोलो = simple_खोलो,
	.ग_लिखो = sof_dfsentry_trace_filter_ग_लिखो,
	.llseek = शेष_llseek,
पूर्ण;

अटल पूर्णांक trace_debugfs_filter_create(काष्ठा snd_sof_dev *sdev)
अणु
	काष्ठा snd_sof_dfsentry *dfse;

	dfse = devm_kzalloc(sdev->dev, माप(*dfse), GFP_KERNEL);
	अगर (!dfse)
		वापस -ENOMEM;

	dfse->sdev = sdev;
	dfse->type = SOF_DFSENTRY_TYPE_BUF;

	debugfs_create_file("filter", 0200, sdev->debugfs_root, dfse,
			    &sof_dfs_trace_filter_fops);
	/* add to dfsentry list */
	list_add(&dfse->list, &sdev->dfsentry_list);

	वापस 0;
पूर्ण

अटल माप_प्रकार sof_trace_avail(काष्ठा snd_sof_dev *sdev,
			      loff_t pos, माप_प्रकार buffer_size)
अणु
	loff_t host_offset = READ_ONCE(sdev->host_offset);

	/*
	 * If host offset is less than local pos, it means ग_लिखो poपूर्णांकer of
	 * host DMA buffer has been wrapped. We should output the trace data
	 * at the end of host DMA buffer at first.
	 */
	अगर (host_offset < pos)
		वापस buffer_size - pos;

	/* If there is available trace data now, it is unnecessary to रुको. */
	अगर (host_offset > pos)
		वापस host_offset - pos;

	वापस 0;
पूर्ण

अटल माप_प्रकार sof_रुको_trace_avail(काष्ठा snd_sof_dev *sdev,
				   loff_t pos, माप_प्रकार buffer_size)
अणु
	रुको_queue_entry_t रुको;
	माप_प्रकार ret = sof_trace_avail(sdev, pos, buffer_size);

	/* data immediately available */
	अगर (ret)
		वापस ret;

	अगर (!sdev->dtrace_is_enabled && sdev->dtrace_draining) अणु
		/*
		 * tracing has ended and all traces have been
		 * पढ़ो by client, वापस खातापूर्ण
		 */
		sdev->dtrace_draining = false;
		वापस 0;
	पूर्ण

	/* रुको क्रम available trace data from FW */
	init_रुकोqueue_entry(&रुको, current);
	set_current_state(TASK_INTERRUPTIBLE);
	add_रुको_queue(&sdev->trace_sleep, &रुको);

	अगर (!संकेत_pending(current)) अणु
		/* set समयout to max value, no error code */
		schedule_समयout(MAX_SCHEDULE_TIMEOUT);
	पूर्ण
	हटाओ_रुको_queue(&sdev->trace_sleep, &रुको);

	वापस sof_trace_avail(sdev, pos, buffer_size);
पूर्ण

अटल sमाप_प्रकार sof_dfsentry_trace_पढ़ो(काष्ठा file *file, अक्षर __user *buffer,
				       माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा snd_sof_dfsentry *dfse = file->निजी_data;
	काष्ठा snd_sof_dev *sdev = dfse->sdev;
	अचिन्हित दीर्घ rem;
	loff_t lpos = *ppos;
	माप_प्रकार avail, buffer_size = dfse->size;
	u64 lpos_64;

	/* make sure we know about any failures on the DSP side */
	sdev->dtrace_error = false;

	/* check pos and count */
	अगर (lpos < 0)
		वापस -EINVAL;
	अगर (!count)
		वापस 0;

	/* check क्रम buffer wrap and count overflow */
	lpos_64 = lpos;
	lpos = करो_भाग(lpos_64, buffer_size);

	अगर (count > buffer_size - lpos) /* min() not used to aव्योम sparse warnings */
		count = buffer_size - lpos;

	/* get available count based on current host offset */
	avail = sof_रुको_trace_avail(sdev, lpos, buffer_size);
	अगर (sdev->dtrace_error) अणु
		dev_err(sdev->dev, "error: trace IO error\n");
		वापस -EIO;
	पूर्ण

	/* make sure count is <= avail */
	count = avail > count ? count : avail;

	/* copy available trace data to debugfs */
	rem = copy_to_user(buffer, ((u8 *)(dfse->buf) + lpos), count);
	अगर (rem)
		वापस -EFAULT;

	*ppos += count;

	/* move debugfs पढ़ोing position */
	वापस count;
पूर्ण

अटल पूर्णांक sof_dfsentry_trace_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा snd_sof_dfsentry *dfse = inode->i_निजी;
	काष्ठा snd_sof_dev *sdev = dfse->sdev;

	/* aव्योम duplicate traces at next खोलो */
	अगर (!sdev->dtrace_is_enabled)
		sdev->host_offset = 0;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा file_operations sof_dfs_trace_fops = अणु
	.खोलो = simple_खोलो,
	.पढ़ो = sof_dfsentry_trace_पढ़ो,
	.llseek = शेष_llseek,
	.release = sof_dfsentry_trace_release,
पूर्ण;

अटल पूर्णांक trace_debugfs_create(काष्ठा snd_sof_dev *sdev)
अणु
	काष्ठा snd_sof_dfsentry *dfse;
	पूर्णांक ret;

	अगर (!sdev)
		वापस -EINVAL;

	ret = trace_debugfs_filter_create(sdev);
	अगर (ret < 0)
		dev_err(sdev->dev, "error: fail in %s, %d", __func__, ret);

	dfse = devm_kzalloc(sdev->dev, माप(*dfse), GFP_KERNEL);
	अगर (!dfse)
		वापस -ENOMEM;

	dfse->type = SOF_DFSENTRY_TYPE_BUF;
	dfse->buf = sdev->dmatb.area;
	dfse->size = sdev->dmatb.bytes;
	dfse->sdev = sdev;

	debugfs_create_file("trace", 0444, sdev->debugfs_root, dfse,
			    &sof_dfs_trace_fops);

	वापस 0;
पूर्ण

पूर्णांक snd_sof_init_trace_ipc(काष्ठा snd_sof_dev *sdev)
अणु
	काष्ठा sof_ipc_fw_पढ़ोy *पढ़ोy = &sdev->fw_पढ़ोy;
	काष्ठा sof_ipc_fw_version *v = &पढ़ोy->version;
	काष्ठा sof_ipc_dma_trace_params_ext params;
	काष्ठा sof_ipc_reply ipc_reply;
	पूर्णांक ret;

	अगर (!sdev->dtrace_is_supported)
		वापस 0;

	अगर (sdev->dtrace_is_enabled || !sdev->dma_trace_pages)
		वापस -EINVAL;

	/* set IPC parameters */
	params.hdr.cmd = SOF_IPC_GLB_TRACE_MSG;
	/* PARAMS_EXT is only supported from ABI 3.7.0 onwards */
	अगर (v->abi_version >= SOF_ABI_VER(3, 7, 0)) अणु
		params.hdr.size = माप(काष्ठा sof_ipc_dma_trace_params_ext);
		params.hdr.cmd |= SOF_IPC_TRACE_DMA_PARAMS_EXT;
		params.बारtamp_ns = kसमय_get(); /* in nanosecond */
	पूर्ण अन्यथा अणु
		params.hdr.size = माप(काष्ठा sof_ipc_dma_trace_params);
		params.hdr.cmd |= SOF_IPC_TRACE_DMA_PARAMS;
	पूर्ण
	params.buffer.phy_addr = sdev->dmatp.addr;
	params.buffer.size = sdev->dmatb.bytes;
	params.buffer.pages = sdev->dma_trace_pages;
	params.stream_tag = 0;

	sdev->host_offset = 0;
	sdev->dtrace_draining = false;

	ret = snd_sof_dma_trace_init(sdev, &params.stream_tag);
	अगर (ret < 0) अणु
		dev_err(sdev->dev,
			"error: fail in snd_sof_dma_trace_init %d\n", ret);
		वापस ret;
	पूर्ण
	dev_dbg(sdev->dev, "stream_tag: %d\n", params.stream_tag);

	/* send IPC to the DSP */
	ret = sof_ipc_tx_message(sdev->ipc,
				 params.hdr.cmd, &params, माप(params),
				 &ipc_reply, माप(ipc_reply));
	अगर (ret < 0) अणु
		dev_err(sdev->dev,
			"error: can't set params for DMA for trace %d\n", ret);
		जाओ trace_release;
	पूर्ण

	ret = snd_sof_dma_trace_trigger(sdev, SNDRV_PCM_TRIGGER_START);
	अगर (ret < 0) अणु
		dev_err(sdev->dev,
			"error: snd_sof_dma_trace_trigger: start: %d\n", ret);
		जाओ trace_release;
	पूर्ण

	sdev->dtrace_is_enabled = true;

	वापस 0;

trace_release:
	snd_sof_dma_trace_release(sdev);
	वापस ret;
पूर्ण

पूर्णांक snd_sof_init_trace(काष्ठा snd_sof_dev *sdev)
अणु
	पूर्णांक ret;

	अगर (!sdev->dtrace_is_supported)
		वापस 0;

	/* set false beक्रमe start initialization */
	sdev->dtrace_is_enabled = false;

	/* allocate trace page table buffer */
	ret = snd_dma_alloc_pages(SNDRV_DMA_TYPE_DEV, sdev->dev,
				  PAGE_SIZE, &sdev->dmatp);
	अगर (ret < 0) अणु
		dev_err(sdev->dev,
			"error: can't alloc page table for trace %d\n", ret);
		वापस ret;
	पूर्ण

	/* allocate trace data buffer */
	ret = snd_dma_alloc_pages(SNDRV_DMA_TYPE_DEV_SG, sdev->dev,
				  DMA_BUF_SIZE_FOR_TRACE, &sdev->dmatb);
	अगर (ret < 0) अणु
		dev_err(sdev->dev,
			"error: can't alloc buffer for trace %d\n", ret);
		जाओ page_err;
	पूर्ण

	/* create compressed page table क्रम audio firmware */
	ret = snd_sof_create_page_table(sdev->dev, &sdev->dmatb,
					sdev->dmatp.area, sdev->dmatb.bytes);
	अगर (ret < 0)
		जाओ table_err;

	sdev->dma_trace_pages = ret;
	dev_dbg(sdev->dev, "dma_trace_pages: %d\n", sdev->dma_trace_pages);

	अगर (sdev->first_boot) अणु
		ret = trace_debugfs_create(sdev);
		अगर (ret < 0)
			जाओ table_err;
	पूर्ण

	init_रुकोqueue_head(&sdev->trace_sleep);

	ret = snd_sof_init_trace_ipc(sdev);
	अगर (ret < 0)
		जाओ table_err;

	वापस 0;
table_err:
	sdev->dma_trace_pages = 0;
	snd_dma_मुक्त_pages(&sdev->dmatb);
page_err:
	snd_dma_मुक्त_pages(&sdev->dmatp);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(snd_sof_init_trace);

पूर्णांक snd_sof_trace_update_pos(काष्ठा snd_sof_dev *sdev,
			     काष्ठा sof_ipc_dma_trace_posn *posn)
अणु
	अगर (!sdev->dtrace_is_supported)
		वापस 0;

	अगर (sdev->dtrace_is_enabled && sdev->host_offset != posn->host_offset) अणु
		sdev->host_offset = posn->host_offset;
		wake_up(&sdev->trace_sleep);
	पूर्ण

	अगर (posn->overflow != 0)
		dev_err(sdev->dev,
			"error: DSP trace buffer overflow %u bytes. Total messages %d\n",
			posn->overflow, posn->messages);

	वापस 0;
पूर्ण

/* an error has occurred within the DSP that prevents further trace */
व्योम snd_sof_trace_notअगरy_क्रम_error(काष्ठा snd_sof_dev *sdev)
अणु
	अगर (!sdev->dtrace_is_supported)
		वापस;

	अगर (sdev->dtrace_is_enabled) अणु
		dev_err(sdev->dev, "error: waking up any trace sleepers\n");
		sdev->dtrace_error = true;
		wake_up(&sdev->trace_sleep);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(snd_sof_trace_notअगरy_क्रम_error);

व्योम snd_sof_release_trace(काष्ठा snd_sof_dev *sdev)
अणु
	पूर्णांक ret;

	अगर (!sdev->dtrace_is_supported || !sdev->dtrace_is_enabled)
		वापस;

	ret = snd_sof_dma_trace_trigger(sdev, SNDRV_PCM_TRIGGER_STOP);
	अगर (ret < 0)
		dev_err(sdev->dev,
			"error: snd_sof_dma_trace_trigger: stop: %d\n", ret);

	ret = snd_sof_dma_trace_release(sdev);
	अगर (ret < 0)
		dev_err(sdev->dev,
			"error: fail in snd_sof_dma_trace_release %d\n", ret);

	sdev->dtrace_is_enabled = false;
	sdev->dtrace_draining = true;
	wake_up(&sdev->trace_sleep);
पूर्ण
EXPORT_SYMBOL(snd_sof_release_trace);

व्योम snd_sof_मुक्त_trace(काष्ठा snd_sof_dev *sdev)
अणु
	अगर (!sdev->dtrace_is_supported)
		वापस;

	snd_sof_release_trace(sdev);

	अगर (sdev->dma_trace_pages) अणु
		snd_dma_मुक्त_pages(&sdev->dmatb);
		snd_dma_मुक्त_pages(&sdev->dmatp);
		sdev->dma_trace_pages = 0;
	पूर्ण
पूर्ण
EXPORT_SYMBOL(snd_sof_मुक्त_trace);
