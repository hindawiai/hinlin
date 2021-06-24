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
// Generic debug routines used to export DSP MMIO and memories to userspace
// क्रम firmware debugging.
//

#समावेश <linux/debugfs.h>
#समावेश <linux/पन.स>
#समावेश <linux/pm_runसमय.स>
#समावेश <sound/sof/ext_manअगरest.h>
#समावेश <sound/sof/debug.h>
#समावेश "sof-priv.h"
#समावेश "ops.h"

#अगर IS_ENABLED(CONFIG_SND_SOC_SOF_DEBUG_PROBES)
#समावेश "probe.h"

/**
 * strsplit_u32 - Split string पूर्णांकo sequence of u32 tokens
 * @buf:	String to split पूर्णांकo tokens.
 * @delim:	String containing delimiter अक्षरacters.
 * @tkns:	Returned u32 sequence poपूर्णांकer.
 * @num_tkns:	Returned number of tokens obtained.
 */
अटल पूर्णांक
strsplit_u32(अक्षर **buf, स्थिर अक्षर *delim, u32 **tkns, माप_प्रकार *num_tkns)
अणु
	अक्षर *s;
	u32 *data, *पंचांगp;
	माप_प्रकार count = 0;
	माप_प्रकार cap = 32;
	पूर्णांक ret = 0;

	*tkns = शून्य;
	*num_tkns = 0;
	data = kसुस्मृति(cap, माप(*data), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	जबतक ((s = strsep(buf, delim)) != शून्य) अणु
		ret = kstrtouपूर्णांक(s, 0, data + count);
		अगर (ret)
			जाओ निकास;
		अगर (++count >= cap) अणु
			cap *= 2;
			पंचांगp = kपुनः_स्मृति(data, cap * माप(*data), GFP_KERNEL);
			अगर (!पंचांगp) अणु
				ret = -ENOMEM;
				जाओ निकास;
			पूर्ण
			data = पंचांगp;
		पूर्ण
	पूर्ण

	अगर (!count)
		जाओ निकास;
	*tkns = kmemdup(data, count * माप(*data), GFP_KERNEL);
	अगर (*tkns == शून्य) अणु
		ret = -ENOMEM;
		जाओ निकास;
	पूर्ण
	*num_tkns = count;

निकास:
	kमुक्त(data);
	वापस ret;
पूर्ण

अटल पूर्णांक tokenize_input(स्थिर अक्षर __user *from, माप_प्रकार count,
		loff_t *ppos, u32 **tkns, माप_प्रकार *num_tkns)
अणु
	अक्षर *buf;
	पूर्णांक ret;

	buf = kदो_स्मृति(count + 1, GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;

	ret = simple_ग_लिखो_to_buffer(buf, count, ppos, from, count);
	अगर (ret != count) अणु
		ret = ret >= 0 ? -EIO : ret;
		जाओ निकास;
	पूर्ण

	buf[count] = '\0';
	ret = strsplit_u32((अक्षर **)&buf, ",", tkns, num_tkns);
निकास:
	kमुक्त(buf);
	वापस ret;
पूर्ण

अटल sमाप_प्रकार probe_poपूर्णांकs_पढ़ो(काष्ठा file *file,
		अक्षर __user *to, माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा snd_sof_dfsentry *dfse = file->निजी_data;
	काष्ठा snd_sof_dev *sdev = dfse->sdev;
	काष्ठा sof_probe_poपूर्णांक_desc *desc;
	माप_प्रकार num_desc, len = 0;
	अक्षर *buf;
	पूर्णांक i, ret;

	अगर (sdev->extractor_stream_tag == SOF_PROBE_INVALID_NODE_ID) अणु
		dev_warn(sdev->dev, "no extractor stream running\n");
		वापस -ENOENT;
	पूर्ण

	buf = kzalloc(PAGE_SIZE, GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;

	ret = sof_ipc_probe_poपूर्णांकs_info(sdev, &desc, &num_desc);
	अगर (ret < 0)
		जाओ निकास;

	क्रम (i = 0; i < num_desc; i++) अणु
		ret = snम_लिखो(buf + len, PAGE_SIZE - len,
			"Id: %#010x  Purpose: %d  Node id: %#x\n",
			desc[i].buffer_id, desc[i].purpose, desc[i].stream_tag);
		अगर (ret < 0)
			जाओ मुक्त_desc;
		len += ret;
	पूर्ण

	ret = simple_पढ़ो_from_buffer(to, count, ppos, buf, len);
मुक्त_desc:
	kमुक्त(desc);
निकास:
	kमुक्त(buf);
	वापस ret;
पूर्ण

अटल sमाप_प्रकार probe_poपूर्णांकs_ग_लिखो(काष्ठा file *file,
		स्थिर अक्षर __user *from, माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा snd_sof_dfsentry *dfse = file->निजी_data;
	काष्ठा snd_sof_dev *sdev = dfse->sdev;
	काष्ठा sof_probe_poपूर्णांक_desc *desc;
	माप_प्रकार num_tkns, bytes;
	u32 *tkns;
	पूर्णांक ret;

	अगर (sdev->extractor_stream_tag == SOF_PROBE_INVALID_NODE_ID) अणु
		dev_warn(sdev->dev, "no extractor stream running\n");
		वापस -ENOENT;
	पूर्ण

	ret = tokenize_input(from, count, ppos, &tkns, &num_tkns);
	अगर (ret < 0)
		वापस ret;
	bytes = माप(*tkns) * num_tkns;
	अगर (!num_tkns || (bytes % माप(*desc))) अणु
		ret = -EINVAL;
		जाओ निकास;
	पूर्ण

	desc = (काष्ठा sof_probe_poपूर्णांक_desc *)tkns;
	ret = sof_ipc_probe_poपूर्णांकs_add(sdev,
			desc, bytes / माप(*desc));
	अगर (!ret)
		ret = count;
निकास:
	kमुक्त(tkns);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा file_operations probe_poपूर्णांकs_fops = अणु
	.खोलो = simple_खोलो,
	.पढ़ो = probe_poपूर्णांकs_पढ़ो,
	.ग_लिखो = probe_poपूर्णांकs_ग_लिखो,
	.llseek = शेष_llseek,
पूर्ण;

अटल sमाप_प्रकार probe_poपूर्णांकs_हटाओ_ग_लिखो(काष्ठा file *file,
		स्थिर अक्षर __user *from, माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा snd_sof_dfsentry *dfse = file->निजी_data;
	काष्ठा snd_sof_dev *sdev = dfse->sdev;
	माप_प्रकार num_tkns;
	u32 *tkns;
	पूर्णांक ret;

	अगर (sdev->extractor_stream_tag == SOF_PROBE_INVALID_NODE_ID) अणु
		dev_warn(sdev->dev, "no extractor stream running\n");
		वापस -ENOENT;
	पूर्ण

	ret = tokenize_input(from, count, ppos, &tkns, &num_tkns);
	अगर (ret < 0)
		वापस ret;
	अगर (!num_tkns) अणु
		ret = -EINVAL;
		जाओ निकास;
	पूर्ण

	ret = sof_ipc_probe_poपूर्णांकs_हटाओ(sdev, tkns, num_tkns);
	अगर (!ret)
		ret = count;
निकास:
	kमुक्त(tkns);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा file_operations probe_poपूर्णांकs_हटाओ_fops = अणु
	.खोलो = simple_खोलो,
	.ग_लिखो = probe_poपूर्णांकs_हटाओ_ग_लिखो,
	.llseek = शेष_llseek,
पूर्ण;

अटल पूर्णांक snd_sof_debugfs_probe_item(काष्ठा snd_sof_dev *sdev,
				 स्थिर अक्षर *name, mode_t mode,
				 स्थिर काष्ठा file_operations *fops)
अणु
	काष्ठा snd_sof_dfsentry *dfse;

	dfse = devm_kzalloc(sdev->dev, माप(*dfse), GFP_KERNEL);
	अगर (!dfse)
		वापस -ENOMEM;

	dfse->type = SOF_DFSENTRY_TYPE_BUF;
	dfse->sdev = sdev;

	debugfs_create_file(name, mode, sdev->debugfs_root, dfse, fops);
	/* add to dfsentry list */
	list_add(&dfse->list, &sdev->dfsentry_list);

	वापस 0;
पूर्ण
#पूर्ण_अगर

#अगर IS_ENABLED(CONFIG_SND_SOC_SOF_DEBUG_IPC_FLOOD_TEST)
#घोषणा MAX_IPC_FLOOD_DURATION_MS 1000
#घोषणा MAX_IPC_FLOOD_COUNT 10000
#घोषणा IPC_FLOOD_TEST_RESULT_LEN 512

अटल पूर्णांक sof_debug_ipc_flood_test(काष्ठा snd_sof_dev *sdev,
				    काष्ठा snd_sof_dfsentry *dfse,
				    bool flood_duration_test,
				    अचिन्हित दीर्घ ipc_duration_ms,
				    अचिन्हित दीर्घ ipc_count)
अणु
	काष्ठा sof_ipc_cmd_hdr hdr;
	काष्ठा sof_ipc_reply reply;
	u64 min_response_समय = U64_MAX;
	kसमय_प्रकार start, end, test_end;
	u64 avg_response_समय = 0;
	u64 max_response_समय = 0;
	u64 ipc_response_समय;
	पूर्णांक i = 0;
	पूर्णांक ret;

	/* configure test IPC */
	hdr.cmd = SOF_IPC_GLB_TEST_MSG | SOF_IPC_TEST_IPC_FLOOD;
	hdr.size = माप(hdr);

	/* set test end समय क्रम duration flood test */
	अगर (flood_duration_test)
		test_end = kसमय_get_ns() + ipc_duration_ms * NSEC_PER_MSEC;

	/* send test IPC's */
	जबतक (1) अणु
		start = kसमय_get();
		ret = sof_ipc_tx_message(sdev->ipc, hdr.cmd, &hdr, hdr.size,
					 &reply, माप(reply));
		end = kसमय_get();

		अगर (ret < 0)
			अवरोध;

		/* compute min and max response बार */
		ipc_response_समय = kसमय_प्रकारo_ns(kसमय_sub(end, start));
		min_response_समय = min(min_response_समय, ipc_response_समय);
		max_response_समय = max(max_response_समय, ipc_response_समय);

		/* sum up response बार */
		avg_response_समय += ipc_response_समय;
		i++;

		/* test complete? */
		अगर (flood_duration_test) अणु
			अगर (kसमय_प्रकारo_ns(end) >= test_end)
				अवरोध;
		पूर्ण अन्यथा अणु
			अगर (i == ipc_count)
				अवरोध;
		पूर्ण
	पूर्ण

	अगर (ret < 0)
		dev_err(sdev->dev,
			"error: ipc flood test failed at %d iterations\n", i);

	/* वापस अगर the first IPC fails */
	अगर (!i)
		वापस ret;

	/* compute average response समय */
	करो_भाग(avg_response_समय, i);

	/* clear previous test output */
	स_रखो(dfse->cache_buf, 0, IPC_FLOOD_TEST_RESULT_LEN);

	अगर (flood_duration_test) अणु
		dev_dbg(sdev->dev, "IPC Flood test duration: %lums\n",
			ipc_duration_ms);
		snम_लिखो(dfse->cache_buf, IPC_FLOOD_TEST_RESULT_LEN,
			 "IPC Flood test duration: %lums\n", ipc_duration_ms);
	पूर्ण

	dev_dbg(sdev->dev,
		"IPC Flood count: %d, Avg response time: %lluns\n",
		i, avg_response_समय);
	dev_dbg(sdev->dev, "Max response time: %lluns\n",
		max_response_समय);
	dev_dbg(sdev->dev, "Min response time: %lluns\n",
		min_response_समय);

	/* क्रमmat output string */
	snम_लिखो(dfse->cache_buf + म_माप(dfse->cache_buf),
		 IPC_FLOOD_TEST_RESULT_LEN - म_माप(dfse->cache_buf),
		 "IPC Flood count: %d\nAvg response time: %lluns\n",
		 i, avg_response_समय);

	snम_लिखो(dfse->cache_buf + म_माप(dfse->cache_buf),
		 IPC_FLOOD_TEST_RESULT_LEN - म_माप(dfse->cache_buf),
		 "Max response time: %lluns\nMin response time: %lluns\n",
		 max_response_समय, min_response_समय);

	वापस ret;
पूर्ण
#पूर्ण_अगर

अटल sमाप_प्रकार sof_dfsentry_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *buffer,
				  माप_प्रकार count, loff_t *ppos)
अणु
#अगर IS_ENABLED(CONFIG_SND_SOC_SOF_DEBUG_IPC_FLOOD_TEST)
	काष्ठा snd_sof_dfsentry *dfse = file->निजी_data;
	काष्ठा snd_sof_dev *sdev = dfse->sdev;
	अचिन्हित दीर्घ ipc_duration_ms = 0;
	bool flood_duration_test = false;
	अचिन्हित दीर्घ ipc_count = 0;
	काष्ठा dentry *dentry;
	पूर्णांक err;
#पूर्ण_अगर
	माप_प्रकार size;
	अक्षर *string;
	पूर्णांक ret;

	string = kzalloc(count+1, GFP_KERNEL);
	अगर (!string)
		वापस -ENOMEM;

	size = simple_ग_लिखो_to_buffer(string, count, ppos, buffer, count);
	ret = size;

#अगर IS_ENABLED(CONFIG_SND_SOC_SOF_DEBUG_IPC_FLOOD_TEST)
	/*
	 * ग_लिखो op is only supported क्रम ipc_flood_count or
	 * ipc_flood_duration_ms debugfs entries aपंचांग.
	 * ipc_flood_count floods the DSP with the number of IPC's specअगरied.
	 * ipc_duration_ms test floods the DSP क्रम the समय specअगरied
	 * in the debugfs entry.
	 */
	dentry = file->f_path.dentry;
	अगर (म_भेद(dentry->d_name.name, "ipc_flood_count") &&
	    म_भेद(dentry->d_name.name, "ipc_flood_duration_ms")) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	अगर (!म_भेद(dentry->d_name.name, "ipc_flood_duration_ms"))
		flood_duration_test = true;

	/* test completion criterion */
	अगर (flood_duration_test)
		ret = kम_से_अदीर्घ(string, 0, &ipc_duration_ms);
	अन्यथा
		ret = kम_से_अदीर्घ(string, 0, &ipc_count);
	अगर (ret < 0)
		जाओ out;

	/* limit max duration/ipc count क्रम flood test */
	अगर (flood_duration_test) अणु
		अगर (!ipc_duration_ms) अणु
			ret = size;
			जाओ out;
		पूर्ण

		/* find the minimum. min() is not used to aव्योम warnings */
		अगर (ipc_duration_ms > MAX_IPC_FLOOD_DURATION_MS)
			ipc_duration_ms = MAX_IPC_FLOOD_DURATION_MS;
	पूर्ण अन्यथा अणु
		अगर (!ipc_count) अणु
			ret = size;
			जाओ out;
		पूर्ण

		/* find the minimum. min() is not used to aव्योम warnings */
		अगर (ipc_count > MAX_IPC_FLOOD_COUNT)
			ipc_count = MAX_IPC_FLOOD_COUNT;
	पूर्ण

	ret = pm_runसमय_get_sync(sdev->dev);
	अगर (ret < 0 && ret != -EACCES) अणु
		dev_err_ratelimited(sdev->dev,
				    "error: debugfs write failed to resume %d\n",
				    ret);
		pm_runसमय_put_noidle(sdev->dev);
		जाओ out;
	पूर्ण

	/* flood test */
	ret = sof_debug_ipc_flood_test(sdev, dfse, flood_duration_test,
				       ipc_duration_ms, ipc_count);

	pm_runसमय_mark_last_busy(sdev->dev);
	err = pm_runसमय_put_स्वतःsuspend(sdev->dev);
	अगर (err < 0)
		dev_err_ratelimited(sdev->dev,
				    "error: debugfs write failed to idle %d\n",
				    err);

	/* वापस size अगर test is successful */
	अगर (ret >= 0)
		ret = size;
out:
#पूर्ण_अगर
	kमुक्त(string);
	वापस ret;
पूर्ण

अटल sमाप_प्रकार sof_dfsentry_पढ़ो(काष्ठा file *file, अक्षर __user *buffer,
				 माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा snd_sof_dfsentry *dfse = file->निजी_data;
	काष्ठा snd_sof_dev *sdev = dfse->sdev;
	loff_t pos = *ppos;
	माप_प्रकार size_ret;
	पूर्णांक skip = 0;
	पूर्णांक size;
	u8 *buf;

#अगर IS_ENABLED(CONFIG_SND_SOC_SOF_DEBUG_IPC_FLOOD_TEST)
	काष्ठा dentry *dentry;

	dentry = file->f_path.dentry;
	अगर ((!म_भेद(dentry->d_name.name, "ipc_flood_count") ||
	     !म_भेद(dentry->d_name.name, "ipc_flood_duration_ms"))) अणु
		अगर (*ppos)
			वापस 0;

		count = म_माप(dfse->cache_buf);
		size_ret = copy_to_user(buffer, dfse->cache_buf, count);
		अगर (size_ret)
			वापस -EFAULT;

		*ppos += count;
		वापस count;
	पूर्ण
#पूर्ण_अगर
	size = dfse->size;

	/* validate position & count */
	अगर (pos < 0)
		वापस -EINVAL;
	अगर (pos >= size || !count)
		वापस 0;
	/* find the minimum. min() is not used since it adds sparse warnings */
	अगर (count > size - pos)
		count = size - pos;

	/* align io पढ़ो start to u32 multiple */
	pos = ALIGN_DOWN(pos, 4);

	/* पूर्णांकermediate buffer size must be u32 multiple */
	size = ALIGN(count, 4);

	/* अगर start position is unaligned, पढ़ो extra u32 */
	अगर (unlikely(pos != *ppos)) अणु
		skip = *ppos - pos;
		अगर (pos + size + 4 < dfse->size)
			size += 4;
	पूर्ण

	buf = kzalloc(size, GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;

	अगर (dfse->type == SOF_DFSENTRY_TYPE_IOMEM) अणु
#अगर IS_ENABLED(CONFIG_SND_SOC_SOF_DEBUG_ENABLE_DEBUGFS_CACHE)
		/*
		 * If the DSP is active: copy from IO.
		 * If the DSP is suspended:
		 *	- Copy from IO अगर the memory is always accessible.
		 *	- Otherwise, copy from cached buffer.
		 */
		अगर (pm_runसमय_active(sdev->dev) ||
		    dfse->access_type == SOF_DEBUGFS_ACCESS_ALWAYS) अणु
			स_नकल_fromio(buf, dfse->io_mem + pos, size);
		पूर्ण अन्यथा अणु
			dev_info(sdev->dev,
				 "Copying cached debugfs data\n");
			स_नकल(buf, dfse->cache_buf + pos, size);
		पूर्ण
#अन्यथा
		/* अगर the DSP is in D3 */
		अगर (!pm_runसमय_active(sdev->dev) &&
		    dfse->access_type == SOF_DEBUGFS_ACCESS_D0_ONLY) अणु
			dev_err(sdev->dev,
				"error: debugfs entry cannot be read in DSP D3\n");
			kमुक्त(buf);
			वापस -EINVAL;
		पूर्ण

		स_नकल_fromio(buf, dfse->io_mem + pos, size);
#पूर्ण_अगर
	पूर्ण अन्यथा अणु
		स_नकल(buf, ((u8 *)(dfse->buf) + pos), size);
	पूर्ण

	/* copy to userspace */
	size_ret = copy_to_user(buffer, buf + skip, count);

	kमुक्त(buf);

	/* update count & position अगर copy succeeded */
	अगर (size_ret)
		वापस -EFAULT;

	*ppos = pos + count;

	वापस count;
पूर्ण

अटल स्थिर काष्ठा file_operations sof_dfs_fops = अणु
	.खोलो = simple_खोलो,
	.पढ़ो = sof_dfsentry_पढ़ो,
	.llseek = शेष_llseek,
	.ग_लिखो = sof_dfsentry_ग_लिखो,
पूर्ण;

/* create FS entry क्रम debug files that can expose DSP memories, रेजिस्टरs */
पूर्णांक snd_sof_debugfs_io_item(काष्ठा snd_sof_dev *sdev,
			    व्योम __iomem *base, माप_प्रकार size,
			    स्थिर अक्षर *name,
			    क्रमागत sof_debugfs_access_type access_type)
अणु
	काष्ठा snd_sof_dfsentry *dfse;

	अगर (!sdev)
		वापस -EINVAL;

	dfse = devm_kzalloc(sdev->dev, माप(*dfse), GFP_KERNEL);
	अगर (!dfse)
		वापस -ENOMEM;

	dfse->type = SOF_DFSENTRY_TYPE_IOMEM;
	dfse->io_mem = base;
	dfse->size = size;
	dfse->sdev = sdev;
	dfse->access_type = access_type;

#अगर IS_ENABLED(CONFIG_SND_SOC_SOF_DEBUG_ENABLE_DEBUGFS_CACHE)
	/*
	 * allocate cache buffer that will be used to save the mem winकरोw
	 * contents prior to suspend
	 */
	अगर (access_type == SOF_DEBUGFS_ACCESS_D0_ONLY) अणु
		dfse->cache_buf = devm_kzalloc(sdev->dev, size, GFP_KERNEL);
		अगर (!dfse->cache_buf)
			वापस -ENOMEM;
	पूर्ण
#पूर्ण_अगर

	debugfs_create_file(name, 0444, sdev->debugfs_root, dfse,
			    &sof_dfs_fops);

	/* add to dfsentry list */
	list_add(&dfse->list, &sdev->dfsentry_list);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(snd_sof_debugfs_io_item);

/* create FS entry क्रम debug files to expose kernel memory */
पूर्णांक snd_sof_debugfs_buf_item(काष्ठा snd_sof_dev *sdev,
			     व्योम *base, माप_प्रकार size,
			     स्थिर अक्षर *name, mode_t mode)
अणु
	काष्ठा snd_sof_dfsentry *dfse;

	अगर (!sdev)
		वापस -EINVAL;

	dfse = devm_kzalloc(sdev->dev, माप(*dfse), GFP_KERNEL);
	अगर (!dfse)
		वापस -ENOMEM;

	dfse->type = SOF_DFSENTRY_TYPE_BUF;
	dfse->buf = base;
	dfse->size = size;
	dfse->sdev = sdev;

#अगर IS_ENABLED(CONFIG_SND_SOC_SOF_DEBUG_IPC_FLOOD_TEST)
	अगर (!म_भेदन(name, "ipc_flood", म_माप("ipc_flood"))) अणु
		/*
		 * cache_buf is unused क्रम SOF_DFSENTRY_TYPE_BUF debugfs entries.
		 * So, use it to save the results of the last IPC flood test.
		 */
		dfse->cache_buf = devm_kzalloc(sdev->dev, IPC_FLOOD_TEST_RESULT_LEN,
					       GFP_KERNEL);
		अगर (!dfse->cache_buf)
			वापस -ENOMEM;
	पूर्ण
#पूर्ण_अगर

	debugfs_create_file(name, mode, sdev->debugfs_root, dfse,
			    &sof_dfs_fops);
	/* add to dfsentry list */
	list_add(&dfse->list, &sdev->dfsentry_list);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(snd_sof_debugfs_buf_item);

अटल पूर्णांक memory_info_update(काष्ठा snd_sof_dev *sdev, अक्षर *buf, माप_प्रकार buff_size)
अणु
	काष्ठा sof_ipc_cmd_hdr msg = अणु
		.size = माप(काष्ठा sof_ipc_cmd_hdr),
		.cmd = SOF_IPC_GLB_DEBUG | SOF_IPC_DEBUG_MEM_USAGE,
	पूर्ण;
	काष्ठा sof_ipc_dbg_mem_usage *reply;
	पूर्णांक len;
	पूर्णांक ret;
	पूर्णांक i;

	reply = kदो_स्मृति(SOF_IPC_MSG_MAX_SIZE, GFP_KERNEL);
	अगर (!reply)
		वापस -ENOMEM;

	ret = pm_runसमय_get_sync(sdev->dev);
	अगर (ret < 0 && ret != -EACCES) अणु
		pm_runसमय_put_noidle(sdev->dev);
		dev_err(sdev->dev, "error: enabling device failed: %d\n", ret);
		जाओ error;
	पूर्ण

	ret = sof_ipc_tx_message(sdev->ipc, msg.cmd, &msg, msg.size, reply, SOF_IPC_MSG_MAX_SIZE);
	pm_runसमय_mark_last_busy(sdev->dev);
	pm_runसमय_put_स्वतःsuspend(sdev->dev);
	अगर (ret < 0 || reply->rhdr.error < 0) अणु
		ret = min(ret, reply->rhdr.error);
		dev_err(sdev->dev, "error: reading memory info failed, %d\n", ret);
		जाओ error;
	पूर्ण

	अगर (काष्ठा_size(reply, elems, reply->num_elems) != reply->rhdr.hdr.size) अणु
		dev_err(sdev->dev, "error: invalid memory info ipc struct size, %d\n",
			reply->rhdr.hdr.size);
		ret = -EINVAL;
		जाओ error;
	पूर्ण

	क्रम (i = 0, len = 0; i < reply->num_elems; i++) अणु
		ret = snम_लिखो(buf + len, buff_size - len, "zone %d.%d used %#8x free %#8x\n",
			       reply->elems[i].zone, reply->elems[i].id,
			       reply->elems[i].used, reply->elems[i].मुक्त);
		अगर (ret < 0)
			जाओ error;
		len += ret;
	पूर्ण

	ret = len;
error:
	kमुक्त(reply);
	वापस ret;
पूर्ण

अटल sमाप_प्रकार memory_info_पढ़ो(काष्ठा file *file, अक्षर __user *to, माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा snd_sof_dfsentry *dfse = file->निजी_data;
	काष्ठा snd_sof_dev *sdev = dfse->sdev;
	पूर्णांक data_length;

	/* पढ़ो memory info from FW only once क्रम each file पढ़ो */
	अगर (!*ppos) अणु
		dfse->buf_data_size = 0;
		data_length = memory_info_update(sdev, dfse->buf, dfse->size);
		अगर (data_length < 0)
			वापस data_length;
		dfse->buf_data_size = data_length;
	पूर्ण

	वापस simple_पढ़ो_from_buffer(to, count, ppos, dfse->buf, dfse->buf_data_size);
पूर्ण

अटल पूर्णांक memory_info_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा snd_sof_dfsentry *dfse = inode->i_निजी;
	काष्ठा snd_sof_dev *sdev = dfse->sdev;

	file->निजी_data = dfse;

	/* allocate buffer memory only in first खोलो run, to save memory when unused */
	अगर (!dfse->buf) अणु
		dfse->buf = devm_kदो_स्मृति(sdev->dev, PAGE_SIZE, GFP_KERNEL);
		अगर (!dfse->buf)
			वापस -ENOMEM;
		dfse->size = PAGE_SIZE;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा file_operations memory_info_fops = अणु
	.खोलो = memory_info_खोलो,
	.पढ़ो = memory_info_पढ़ो,
	.llseek = शेष_llseek,
पूर्ण;

पूर्णांक snd_sof_dbg_memory_info_init(काष्ठा snd_sof_dev *sdev)
अणु
	काष्ठा snd_sof_dfsentry *dfse;

	dfse = devm_kzalloc(sdev->dev, माप(*dfse), GFP_KERNEL);
	अगर (!dfse)
		वापस -ENOMEM;

	/* करोn't allocate buffer beक्रमe first usage, to save memory when unused */
	dfse->type = SOF_DFSENTRY_TYPE_BUF;
	dfse->sdev = sdev;

	debugfs_create_file("memory_info", 0444, sdev->debugfs_root, dfse, &memory_info_fops);

	/* add to dfsentry list */
	list_add(&dfse->list, &sdev->dfsentry_list);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(snd_sof_dbg_memory_info_init);

पूर्णांक snd_sof_dbg_init(काष्ठा snd_sof_dev *sdev)
अणु
	स्थिर काष्ठा snd_sof_dsp_ops *ops = sof_ops(sdev);
	स्थिर काष्ठा snd_sof_debugfs_map *map;
	पूर्णांक i;
	पूर्णांक err;

	/* use "sof" as top level debugFS dir */
	sdev->debugfs_root = debugfs_create_dir("sof", शून्य);

	/* init dfsentry list */
	INIT_LIST_HEAD(&sdev->dfsentry_list);

	/* create debugFS files क्रम platक्रमm specअगरic MMIO/DSP memories */
	क्रम (i = 0; i < ops->debug_map_count; i++) अणु
		map = &ops->debug_map[i];

		err = snd_sof_debugfs_io_item(sdev, sdev->bar[map->bar] +
					      map->offset, map->size,
					      map->name, map->access_type);
		/* errors are only due to memory allocation, not debugfs */
		अगर (err < 0)
			वापस err;
	पूर्ण

#अगर IS_ENABLED(CONFIG_SND_SOC_SOF_DEBUG_PROBES)
	err = snd_sof_debugfs_probe_item(sdev, "probe_points",
			0644, &probe_poपूर्णांकs_fops);
	अगर (err < 0)
		वापस err;
	err = snd_sof_debugfs_probe_item(sdev, "probe_points_remove",
			0200, &probe_poपूर्णांकs_हटाओ_fops);
	अगर (err < 0)
		वापस err;
#पूर्ण_अगर

#अगर IS_ENABLED(CONFIG_SND_SOC_SOF_DEBUG_IPC_FLOOD_TEST)
	/* create पढ़ो-ग_लिखो ipc_flood_count debugfs entry */
	err = snd_sof_debugfs_buf_item(sdev, शून्य, 0,
				       "ipc_flood_count", 0666);

	/* errors are only due to memory allocation, not debugfs */
	अगर (err < 0)
		वापस err;

	/* create पढ़ो-ग_लिखो ipc_flood_duration_ms debugfs entry */
	err = snd_sof_debugfs_buf_item(sdev, शून्य, 0,
				       "ipc_flood_duration_ms", 0666);

	/* errors are only due to memory allocation, not debugfs */
	अगर (err < 0)
		वापस err;
#पूर्ण_अगर

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(snd_sof_dbg_init);

व्योम snd_sof_मुक्त_debug(काष्ठा snd_sof_dev *sdev)
अणु
	debugfs_हटाओ_recursive(sdev->debugfs_root);
पूर्ण
EXPORT_SYMBOL_GPL(snd_sof_मुक्त_debug);

व्योम snd_sof_handle_fw_exception(काष्ठा snd_sof_dev *sdev)
अणु
	अगर (IS_ENABLED(CONFIG_SND_SOC_SOF_DEBUG_RETAIN_DSP_CONTEXT) ||
	    (sof_core_debug & SOF_DBG_RETAIN_CTX)) अणु
		/* should we prevent DSP entering D3 ? */
		dev_info(sdev->dev, "info: preventing DSP entering D3 state to preserve context\n");
		pm_runसमय_get_noresume(sdev->dev);
	पूर्ण

	/* dump vital inक्रमmation to the logs */
	snd_sof_dsp_dbg_dump(sdev, SOF_DBG_DUMP_REGS | SOF_DBG_DUMP_MBOX);
	snd_sof_ipc_dump(sdev);
	snd_sof_trace_notअगरy_क्रम_error(sdev);
पूर्ण
EXPORT_SYMBOL(snd_sof_handle_fw_exception);
