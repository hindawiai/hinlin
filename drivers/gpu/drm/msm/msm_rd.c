<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2013 Red Hat
 * Author: Rob Clark <robdclark@gmail.com>
 */

/* For debugging crashes, userspace can:
 *
 *   tail -f /sys/kernel/debug/dri/<minor>/rd > logfile.rd
 *
 * to log the cmdstream in a क्रमmat that is understood by मुक्तdreno/cffdump
 * utility.  By comparing the last successfully completed fence #, to the
 * cmdstream क्रम the next fence, you can narrow करोwn which process and submit
 * caused the gpu crash/lockup.
 *
 * Additionally:
 *
 *   tail -f /sys/kernel/debug/dri/<minor>/hangrd > logfile.rd
 *
 * will capture just the cmdstream from submits which triggered a GPU hang.
 *
 * This bypasses drm_debugfs_create_files() मुख्यly because we need to use
 * our own fops क्रम a bit more control.  In particular, we करोn't want to
 * करो anything अगर userspace करोesn't have the debugfs file खोलो.
 *
 * The module-param "rd_full", which शेषs to false, enables snapshotting
 * all (non-written) buffers in the submit, rather than just cmdstream bo's.
 * This is useful to capture the contents of (क्रम example) vbo's or textures,
 * or shader programs (अगर not emitted अंतरभूत in cmdstream).
 */

#समावेश <linux/circ_buf.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/kfअगरo.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/रुको.h>

#समावेश <drm/drm_file.h>

#समावेश "msm_drv.h"
#समावेश "msm_gpu.h"
#समावेश "msm_gem.h"

bool rd_full = false;
MODULE_PARM_DESC(rd_full, "If true, $debugfs/.../rd will snapshot all buffer contents");
module_param_named(rd_full, rd_full, bool, 0600);

#अगर_घोषित CONFIG_DEBUG_FS

क्रमागत rd_sect_type अणु
	RD_NONE,
	RD_TEST,       /* ascii text */
	RD_CMD,        /* ascii text */
	RD_GPUADDR,    /* u32 gpuaddr, u32 size */
	RD_CONTEXT,    /* raw dump */
	RD_CMDSTREAM,  /* raw dump */
	RD_CMDSTREAM_ADDR, /* gpu addr of cmdstream */
	RD_PARAM,      /* u32 param_type, u32 param_val, u32 bitlen */
	RD_FLUSH,      /* empty, clear previous params */
	RD_PROGRAM,    /* shader program, raw dump */
	RD_VERT_SHADER,
	RD_FRAG_SHADER,
	RD_BUFFER_CONTENTS,
	RD_GPU_ID,
पूर्ण;

#घोषणा BUF_SZ 512  /* should be घातer of 2 */

/* space used: */
#घोषणा circ_count(circ) \
	(CIRC_CNT((circ)->head, (circ)->tail, BUF_SZ))
#घोषणा circ_count_to_end(circ) \
	(CIRC_CNT_TO_END((circ)->head, (circ)->tail, BUF_SZ))
/* space available: */
#घोषणा circ_space(circ) \
	(CIRC_SPACE((circ)->head, (circ)->tail, BUF_SZ))
#घोषणा circ_space_to_end(circ) \
	(CIRC_SPACE_TO_END((circ)->head, (circ)->tail, BUF_SZ))

काष्ठा msm_rd_state अणु
	काष्ठा drm_device *dev;

	bool खोलो;

	/* current submit to पढ़ो out: */
	काष्ठा msm_gem_submit *submit;

	/* fअगरo access is synchronized on the producer side by
	 * काष्ठा_mutex held by submit code (otherwise we could
	 * end up w/ cmds logged in dअगरferent order than they
	 * were executed).  And पढ़ो_lock synchronizes the पढ़ोs
	 */
	काष्ठा mutex पढ़ो_lock;

	रुको_queue_head_t fअगरo_event;
	काष्ठा circ_buf fअगरo;

	अक्षर buf[BUF_SZ];
पूर्ण;

अटल व्योम rd_ग_लिखो(काष्ठा msm_rd_state *rd, स्थिर व्योम *buf, पूर्णांक sz)
अणु
	काष्ठा circ_buf *fअगरo = &rd->fअगरo;
	स्थिर अक्षर *ptr = buf;

	जबतक (sz > 0) अणु
		अक्षर *fptr = &fअगरo->buf[fअगरo->head];
		पूर्णांक n;

		रुको_event(rd->fअगरo_event, circ_space(&rd->fअगरo) > 0 || !rd->खोलो);
		अगर (!rd->खोलो)
			वापस;

		/* Note that smp_load_acquire() is not strictly required
		 * as CIRC_SPACE_TO_END() करोes not access the tail more
		 * than once.
		 */
		n = min(sz, circ_space_to_end(&rd->fअगरo));
		स_नकल(fptr, ptr, n);

		smp_store_release(&fअगरo->head, (fअगरo->head + n) & (BUF_SZ - 1));
		sz  -= n;
		ptr += n;

		wake_up_all(&rd->fअगरo_event);
	पूर्ण
पूर्ण

अटल व्योम rd_ग_लिखो_section(काष्ठा msm_rd_state *rd,
		क्रमागत rd_sect_type type, स्थिर व्योम *buf, पूर्णांक sz)
अणु
	rd_ग_लिखो(rd, &type, 4);
	rd_ग_लिखो(rd, &sz, 4);
	rd_ग_लिखो(rd, buf, sz);
पूर्ण

अटल sमाप_प्रकार rd_पढ़ो(काष्ठा file *file, अक्षर __user *buf,
		माप_प्रकार sz, loff_t *ppos)
अणु
	काष्ठा msm_rd_state *rd = file->निजी_data;
	काष्ठा circ_buf *fअगरo = &rd->fअगरo;
	स्थिर अक्षर *fptr = &fअगरo->buf[fअगरo->tail];
	पूर्णांक n = 0, ret = 0;

	mutex_lock(&rd->पढ़ो_lock);

	ret = रुको_event_पूर्णांकerruptible(rd->fअगरo_event,
			circ_count(&rd->fअगरo) > 0);
	अगर (ret)
		जाओ out;

	/* Note that smp_load_acquire() is not strictly required
	 * as CIRC_CNT_TO_END() करोes not access the head more than
	 * once.
	 */
	n = min_t(पूर्णांक, sz, circ_count_to_end(&rd->fअगरo));
	अगर (copy_to_user(buf, fptr, n)) अणु
		ret = -EFAULT;
		जाओ out;
	पूर्ण

	smp_store_release(&fअगरo->tail, (fअगरo->tail + n) & (BUF_SZ - 1));
	*ppos += n;

	wake_up_all(&rd->fअगरo_event);

out:
	mutex_unlock(&rd->पढ़ो_lock);
	अगर (ret)
		वापस ret;
	वापस n;
पूर्ण

अटल पूर्णांक rd_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा msm_rd_state *rd = inode->i_निजी;
	काष्ठा drm_device *dev = rd->dev;
	काष्ठा msm_drm_निजी *priv = dev->dev_निजी;
	काष्ठा msm_gpu *gpu = priv->gpu;
	uपूर्णांक64_t val;
	uपूर्णांक32_t gpu_id;
	पूर्णांक ret = 0;

	mutex_lock(&dev->काष्ठा_mutex);

	अगर (rd->खोलो || !gpu) अणु
		ret = -EBUSY;
		जाओ out;
	पूर्ण

	file->निजी_data = rd;
	rd->खोलो = true;

	/* the parsing tools need to know gpu-id to know which
	 * रेजिस्टर database to load.
	 */
	gpu->funcs->get_param(gpu, MSM_PARAM_GPU_ID, &val);
	gpu_id = val;

	rd_ग_लिखो_section(rd, RD_GPU_ID, &gpu_id, माप(gpu_id));

out:
	mutex_unlock(&dev->काष्ठा_mutex);
	वापस ret;
पूर्ण

अटल पूर्णांक rd_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा msm_rd_state *rd = inode->i_निजी;

	rd->खोलो = false;
	wake_up_all(&rd->fअगरo_event);

	वापस 0;
पूर्ण


अटल स्थिर काष्ठा file_operations rd_debugfs_fops = अणु
	.owner = THIS_MODULE,
	.खोलो = rd_खोलो,
	.पढ़ो = rd_पढ़ो,
	.llseek = no_llseek,
	.release = rd_release,
पूर्ण;


अटल व्योम rd_cleanup(काष्ठा msm_rd_state *rd)
अणु
	अगर (!rd)
		वापस;

	mutex_destroy(&rd->पढ़ो_lock);
	kमुक्त(rd);
पूर्ण

अटल काष्ठा msm_rd_state *rd_init(काष्ठा drm_minor *minor, स्थिर अक्षर *name)
अणु
	काष्ठा msm_rd_state *rd;

	rd = kzalloc(माप(*rd), GFP_KERNEL);
	अगर (!rd)
		वापस ERR_PTR(-ENOMEM);

	rd->dev = minor->dev;
	rd->fअगरo.buf = rd->buf;

	mutex_init(&rd->पढ़ो_lock);

	init_रुकोqueue_head(&rd->fअगरo_event);

	debugfs_create_file(name, S_IFREG | S_IRUGO, minor->debugfs_root, rd,
			    &rd_debugfs_fops);

	वापस rd;
पूर्ण

पूर्णांक msm_rd_debugfs_init(काष्ठा drm_minor *minor)
अणु
	काष्ठा msm_drm_निजी *priv = minor->dev->dev_निजी;
	काष्ठा msm_rd_state *rd;
	पूर्णांक ret;

	/* only create on first minor: */
	अगर (priv->rd)
		वापस 0;

	rd = rd_init(minor, "rd");
	अगर (IS_ERR(rd)) अणु
		ret = PTR_ERR(rd);
		जाओ fail;
	पूर्ण

	priv->rd = rd;

	rd = rd_init(minor, "hangrd");
	अगर (IS_ERR(rd)) अणु
		ret = PTR_ERR(rd);
		जाओ fail;
	पूर्ण

	priv->hangrd = rd;

	वापस 0;

fail:
	msm_rd_debugfs_cleanup(priv);
	वापस ret;
पूर्ण

व्योम msm_rd_debugfs_cleanup(काष्ठा msm_drm_निजी *priv)
अणु
	rd_cleanup(priv->rd);
	priv->rd = शून्य;

	rd_cleanup(priv->hangrd);
	priv->hangrd = शून्य;
पूर्ण

अटल व्योम snapshot_buf(काष्ठा msm_rd_state *rd,
		काष्ठा msm_gem_submit *submit, पूर्णांक idx,
		uपूर्णांक64_t iova, uपूर्णांक32_t size, bool full)
अणु
	काष्ठा msm_gem_object *obj = submit->bos[idx].obj;
	अचिन्हित offset = 0;
	स्थिर अक्षर *buf;

	अगर (iova) अणु
		offset = iova - submit->bos[idx].iova;
	पूर्ण अन्यथा अणु
		iova = submit->bos[idx].iova;
		size = obj->base.size;
	पूर्ण

	/*
	 * Always ग_लिखो the GPUADDR header so can get a complete list of all the
	 * buffers in the cmd
	 */
	rd_ग_लिखो_section(rd, RD_GPUADDR,
			(uपूर्णांक32_t[3])अणु iova, size, iova >> 32 पूर्ण, 12);

	अगर (!full)
		वापस;

	/* But only dump the contents of buffers marked READ */
	अगर (!(submit->bos[idx].flags & MSM_SUBMIT_BO_READ))
		वापस;

	buf = msm_gem_get_vaddr_active(&obj->base);
	अगर (IS_ERR(buf))
		वापस;

	buf += offset;

	rd_ग_लिखो_section(rd, RD_BUFFER_CONTENTS, buf, size);

	msm_gem_put_vaddr_locked(&obj->base);
पूर्ण

/* called under काष्ठा_mutex */
व्योम msm_rd_dump_submit(काष्ठा msm_rd_state *rd, काष्ठा msm_gem_submit *submit,
		स्थिर अक्षर *fmt, ...)
अणु
	काष्ठा drm_device *dev = submit->dev;
	काष्ठा task_काष्ठा *task;
	अक्षर msg[256];
	पूर्णांक i, n;

	अगर (!rd->खोलो)
		वापस;

	/* writing पूर्णांकo fअगरo is serialized by caller, and
	 * rd->पढ़ो_lock is used to serialize the पढ़ोs
	 */
	WARN_ON(!mutex_is_locked(&dev->काष्ठा_mutex));

	अगर (fmt) अणु
		बहु_सूची args;

		बहु_शुरू(args, fmt);
		n = vscnम_लिखो(msg, माप(msg), fmt, args);
		बहु_पूर्ण(args);

		rd_ग_लिखो_section(rd, RD_CMD, msg, ALIGN(n, 4));
	पूर्ण

	rcu_पढ़ो_lock();
	task = pid_task(submit->pid, PIDTYPE_PID);
	अगर (task) अणु
		n = scnम_लिखो(msg, माप(msg), "%.*s/%d: fence=%u",
				TASK_COMM_LEN, task->comm,
				pid_nr(submit->pid), submit->seqno);
	पूर्ण अन्यथा अणु
		n = scnम_लिखो(msg, माप(msg), "???/%d: fence=%u",
				pid_nr(submit->pid), submit->seqno);
	पूर्ण
	rcu_पढ़ो_unlock();

	rd_ग_लिखो_section(rd, RD_CMD, msg, ALIGN(n, 4));

	क्रम (i = 0; i < submit->nr_bos; i++)
		snapshot_buf(rd, submit, i, 0, 0, should_dump(submit, i));

	क्रम (i = 0; i < submit->nr_cmds; i++) अणु
		uपूर्णांक32_t szd  = submit->cmd[i].size; /* in dwords */

		/* snapshot cmdstream bo's (if we haven't alपढ़ोy): */
		अगर (!should_dump(submit, i)) अणु
			snapshot_buf(rd, submit, submit->cmd[i].idx,
					submit->cmd[i].iova, szd * 4, true);
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < submit->nr_cmds; i++) अणु
		uपूर्णांक64_t iova = submit->cmd[i].iova;
		uपूर्णांक32_t szd  = submit->cmd[i].size; /* in dwords */

		चयन (submit->cmd[i].type) अणु
		हाल MSM_SUBMIT_CMD_IB_TARGET_BUF:
			/* ignore IB-tarमाला_लो, we've logged the buffer, the
			 * parser tool will follow the IB based on the logged
			 * buffer/gpuaddr, so nothing more to करो.
			 */
			अवरोध;
		हाल MSM_SUBMIT_CMD_CTX_RESTORE_BUF:
		हाल MSM_SUBMIT_CMD_BUF:
			rd_ग_लिखो_section(rd, RD_CMDSTREAM_ADDR,
				(uपूर्णांक32_t[3])अणु iova, szd, iova >> 32 पूर्ण, 12);
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण
#पूर्ण_अगर
