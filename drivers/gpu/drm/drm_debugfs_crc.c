<शैली गुरु>
/*
 * Copyright तऊ 2008 Intel Corporation
 * Copyright तऊ 2016 Collabora Ltd
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the next
 * paragraph) shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 *
 * Based on code from the i915 driver.
 * Original author: Damien Lespiau <damien.lespiau@पूर्णांकel.com>
 *
 */

#समावेश <linux/circ_buf.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/debugfs.h>
#समावेश <linux/poll.h>
#समावेश <linux/uaccess.h>

#समावेश <drm/drm_crtc.h>
#समावेश <drm/drm_debugfs_crc.h>
#समावेश <drm/drm_drv.h>
#समावेश <drm/drm_prपूर्णांक.h>

#समावेश "drm_internal.h"

/**
 * DOC: CRC ABI
 *
 * DRM device drivers can provide to userspace CRC inक्रमmation of each frame as
 * it reached a given hardware component (a CRC sampling "source").
 *
 * Userspace can control generation of CRCs in a given CRTC by writing to the
 * file dri/0/crtc-N/crc/control in debugfs, with N being the index of the CRTC.
 * Accepted values are source names (which are driver-specअगरic) and the "auto"
 * keyword, which will let the driver select a शेष source of frame CRCs
 * क्रम this CRTC.
 *
 * Once frame CRC generation is enabled, userspace can capture them by पढ़ोing
 * the dri/0/crtc-N/crc/data file. Each line in that file contains the frame
 * number in the first field and then a number of अचिन्हित पूर्णांकeger fields
 * containing the CRC data. Fields are separated by a single space and the number
 * of CRC fields is source-specअगरic.
 *
 * Note that though in some हालs the CRC is computed in a specअगरied way and on
 * the frame contents as supplied by userspace (eDP 1.3), in general the CRC
 * computation is perक्रमmed in an unspecअगरied way and on frame contents that have
 * been alपढ़ोy processed in also an unspecअगरied way and thus userspace cannot
 * rely on being able to generate matching CRC values क्रम the frame contents that
 * it submits. In this general हाल, the maximum userspace can करो is to compare
 * the reported CRCs of frames that should have the same contents.
 *
 * On the driver side the implementation efक्रमt is minimal, drivers only need to
 * implement &drm_crtc_funcs.set_crc_source and &drm_crtc_funcs.verअगरy_crc_source.
 * The debugfs files are स्वतःmatically set up अगर those vfuncs are set. CRC samples
 * need to be captured in the driver by calling drm_crtc_add_crc_entry().
 * Depending on the driver and HW requirements, &drm_crtc_funcs.set_crc_source
 * may result in a commit (even a full modeset).
 *
 * CRC results must be reliable across non-full-modeset atomic commits, so अगर a
 * commit via DRM_IOCTL_MODE_ATOMIC would disable or otherwise पूर्णांकerfere with
 * CRC generation, then the driver must mark that commit as a full modeset
 * (drm_atomic_crtc_needs_modeset() should वापस true). As a result, to ensure
 * consistent results, generic userspace must re-setup CRC generation after a
 * legacy SETCRTC or an atomic commit with DRM_MODE_ATOMIC_ALLOW_MODESET.
 */

अटल पूर्णांक crc_control_show(काष्ठा seq_file *m, व्योम *data)
अणु
	काष्ठा drm_crtc *crtc = m->निजी;

	अगर (crtc->funcs->get_crc_sources) अणु
		माप_प्रकार count;
		स्थिर अक्षर *स्थिर *sources = crtc->funcs->get_crc_sources(crtc,
									&count);
		माप_प्रकार values_cnt;
		पूर्णांक i;

		अगर (count == 0 || !sources)
			जाओ out;

		क्रम (i = 0; i < count; i++)
			अगर (!crtc->funcs->verअगरy_crc_source(crtc, sources[i],
							    &values_cnt)) अणु
				अगर (म_भेद(sources[i], crtc->crc.source))
					seq_म_लिखो(m, "%s\n", sources[i]);
				अन्यथा
					seq_म_लिखो(m, "%s*\n", sources[i]);
			पूर्ण
	पूर्ण
	वापस 0;

out:
	seq_म_लिखो(m, "%s*\n", crtc->crc.source);
	वापस 0;
पूर्ण

अटल पूर्णांक crc_control_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा drm_crtc *crtc = inode->i_निजी;

	वापस single_खोलो(file, crc_control_show, crtc);
पूर्ण

अटल sमाप_प्रकार crc_control_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *ubuf,
				 माप_प्रकार len, loff_t *offp)
अणु
	काष्ठा seq_file *m = file->निजी_data;
	काष्ठा drm_crtc *crtc = m->निजी;
	काष्ठा drm_crtc_crc *crc = &crtc->crc;
	अक्षर *source;
	माप_प्रकार values_cnt;
	पूर्णांक ret;

	अगर (len == 0)
		वापस 0;

	अगर (len > PAGE_SIZE - 1) अणु
		DRM_DEBUG_KMS("Expected < %lu bytes into crtc crc control\n",
			      PAGE_SIZE);
		वापस -E2BIG;
	पूर्ण

	source = memdup_user_nul(ubuf, len);
	अगर (IS_ERR(source))
		वापस PTR_ERR(source);

	अगर (source[len - 1] == '\n')
		source[len - 1] = '\0';

	ret = crtc->funcs->verअगरy_crc_source(crtc, source, &values_cnt);
	अगर (ret) अणु
		kमुक्त(source);
		वापस ret;
	पूर्ण

	spin_lock_irq(&crc->lock);

	अगर (crc->खोलोed) अणु
		spin_unlock_irq(&crc->lock);
		kमुक्त(source);
		वापस -EBUSY;
	पूर्ण

	kमुक्त(crc->source);
	crc->source = source;

	spin_unlock_irq(&crc->lock);

	*offp += len;
	वापस len;
पूर्ण

अटल स्थिर काष्ठा file_operations drm_crtc_crc_control_fops = अणु
	.owner = THIS_MODULE,
	.खोलो = crc_control_खोलो,
	.पढ़ो = seq_पढ़ो,
	.llseek = seq_lseek,
	.release = single_release,
	.ग_लिखो = crc_control_ग_लिखो
पूर्ण;

अटल पूर्णांक crtc_crc_data_count(काष्ठा drm_crtc_crc *crc)
अणु
	निश्चित_spin_locked(&crc->lock);
	वापस CIRC_CNT(crc->head, crc->tail, DRM_CRC_ENTRIES_NR);
पूर्ण

अटल व्योम crtc_crc_cleanup(काष्ठा drm_crtc_crc *crc)
अणु
	kमुक्त(crc->entries);
	crc->overflow = false;
	crc->entries = शून्य;
	crc->head = 0;
	crc->tail = 0;
	crc->values_cnt = 0;
	crc->खोलोed = false;
पूर्ण

अटल पूर्णांक crtc_crc_खोलो(काष्ठा inode *inode, काष्ठा file *filep)
अणु
	काष्ठा drm_crtc *crtc = inode->i_निजी;
	काष्ठा drm_crtc_crc *crc = &crtc->crc;
	काष्ठा drm_crtc_crc_entry *entries = शून्य;
	माप_प्रकार values_cnt;
	पूर्णांक ret = 0;

	अगर (drm_drv_uses_atomic_modeset(crtc->dev)) अणु
		ret = drm_modeset_lock_single_पूर्णांकerruptible(&crtc->mutex);
		अगर (ret)
			वापस ret;

		अगर (!crtc->state->active)
			ret = -EIO;
		drm_modeset_unlock(&crtc->mutex);

		अगर (ret)
			वापस ret;
	पूर्ण

	ret = crtc->funcs->verअगरy_crc_source(crtc, crc->source, &values_cnt);
	अगर (ret)
		वापस ret;

	अगर (WARN_ON(values_cnt > DRM_MAX_CRC_NR))
		वापस -EINVAL;

	अगर (WARN_ON(values_cnt == 0))
		वापस -EINVAL;

	entries = kसुस्मृति(DRM_CRC_ENTRIES_NR, माप(*entries), GFP_KERNEL);
	अगर (!entries)
		वापस -ENOMEM;

	spin_lock_irq(&crc->lock);
	अगर (!crc->खोलोed) अणु
		crc->खोलोed = true;
		crc->entries = entries;
		crc->values_cnt = values_cnt;
	पूर्ण अन्यथा अणु
		ret = -EBUSY;
	पूर्ण
	spin_unlock_irq(&crc->lock);

	अगर (ret) अणु
		kमुक्त(entries);
		वापस ret;
	पूर्ण

	ret = crtc->funcs->set_crc_source(crtc, crc->source);
	अगर (ret)
		जाओ err;

	वापस 0;

err:
	spin_lock_irq(&crc->lock);
	crtc_crc_cleanup(crc);
	spin_unlock_irq(&crc->lock);
	वापस ret;
पूर्ण

अटल पूर्णांक crtc_crc_release(काष्ठा inode *inode, काष्ठा file *filep)
अणु
	काष्ठा drm_crtc *crtc = filep->f_inode->i_निजी;
	काष्ठा drm_crtc_crc *crc = &crtc->crc;

	/* terminate the infinite जबतक loop अगर 'drm_dp_aux_crc_work' running */
	spin_lock_irq(&crc->lock);
	crc->खोलोed = false;
	spin_unlock_irq(&crc->lock);

	crtc->funcs->set_crc_source(crtc, शून्य);

	spin_lock_irq(&crc->lock);
	crtc_crc_cleanup(crc);
	spin_unlock_irq(&crc->lock);

	वापस 0;
पूर्ण

/*
 * 1 frame field of 10 अक्षरs plus a number of CRC fields of 10 अक्षरs each, space
 * separated, with a newline at the end and null-terminated.
 */
#घोषणा LINE_LEN(values_cnt)	(10 + 11 * values_cnt + 1 + 1)
#घोषणा MAX_LINE_LEN		(LINE_LEN(DRM_MAX_CRC_NR))

अटल sमाप_प्रकार crtc_crc_पढ़ो(काष्ठा file *filep, अक्षर __user *user_buf,
			     माप_प्रकार count, loff_t *pos)
अणु
	काष्ठा drm_crtc *crtc = filep->f_inode->i_निजी;
	काष्ठा drm_crtc_crc *crc = &crtc->crc;
	काष्ठा drm_crtc_crc_entry *entry;
	अक्षर buf[MAX_LINE_LEN];
	पूर्णांक ret, i;

	spin_lock_irq(&crc->lock);

	अगर (!crc->source) अणु
		spin_unlock_irq(&crc->lock);
		वापस 0;
	पूर्ण

	/* Nothing to पढ़ो? */
	जबतक (crtc_crc_data_count(crc) == 0) अणु
		अगर (filep->f_flags & O_NONBLOCK) अणु
			spin_unlock_irq(&crc->lock);
			वापस -EAGAIN;
		पूर्ण

		ret = रुको_event_पूर्णांकerruptible_lock_irq(crc->wq,
							crtc_crc_data_count(crc),
							crc->lock);
		अगर (ret) अणु
			spin_unlock_irq(&crc->lock);
			वापस ret;
		पूर्ण
	पूर्ण

	/* We know we have an entry to be पढ़ो */
	entry = &crc->entries[crc->tail];

	अगर (count < LINE_LEN(crc->values_cnt)) अणु
		spin_unlock_irq(&crc->lock);
		वापस -EINVAL;
	पूर्ण

	BUILD_BUG_ON_NOT_POWER_OF_2(DRM_CRC_ENTRIES_NR);
	crc->tail = (crc->tail + 1) & (DRM_CRC_ENTRIES_NR - 1);

	spin_unlock_irq(&crc->lock);

	अगर (entry->has_frame_counter)
		प्र_लिखो(buf, "0x%08x", entry->frame);
	अन्यथा
		प्र_लिखो(buf, "XXXXXXXXXX");

	क्रम (i = 0; i < crc->values_cnt; i++)
		प्र_लिखो(buf + 10 + i * 11, " 0x%08x", entry->crcs[i]);
	प्र_लिखो(buf + 10 + crc->values_cnt * 11, "\n");

	अगर (copy_to_user(user_buf, buf, LINE_LEN(crc->values_cnt)))
		वापस -EFAULT;

	वापस LINE_LEN(crc->values_cnt);
पूर्ण

अटल __poll_t crtc_crc_poll(काष्ठा file *file, poll_table *रुको)
अणु
	काष्ठा drm_crtc *crtc = file->f_inode->i_निजी;
	काष्ठा drm_crtc_crc *crc = &crtc->crc;
	__poll_t ret = 0;

	poll_रुको(file, &crc->wq, रुको);

	spin_lock_irq(&crc->lock);
	अगर (crc->source && crtc_crc_data_count(crc))
		ret |= EPOLLIN | EPOLLRDNORM;
	spin_unlock_irq(&crc->lock);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा file_operations drm_crtc_crc_data_fops = अणु
	.owner = THIS_MODULE,
	.खोलो = crtc_crc_खोलो,
	.पढ़ो = crtc_crc_पढ़ो,
	.poll = crtc_crc_poll,
	.release = crtc_crc_release,
पूर्ण;

व्योम drm_debugfs_crtc_crc_add(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा dentry *crc_ent;

	अगर (!crtc->funcs->set_crc_source || !crtc->funcs->verअगरy_crc_source)
		वापस;

	crc_ent = debugfs_create_dir("crc", crtc->debugfs_entry);

	debugfs_create_file("control", S_IRUGO | S_IWUSR, crc_ent, crtc,
			    &drm_crtc_crc_control_fops);
	debugfs_create_file("data", S_IRUGO, crc_ent, crtc,
			    &drm_crtc_crc_data_fops);
पूर्ण

/**
 * drm_crtc_add_crc_entry - Add entry with CRC inक्रमmation क्रम a frame
 * @crtc: CRTC to which the frame beदीर्घs
 * @has_frame: whether this entry has a frame number to go with
 * @frame: number of the frame these CRCs are about
 * @crcs: array of CRC values, with length matching #drm_crtc_crc.values_cnt
 *
 * For each frame, the driver polls the source of CRCs क्रम new data and calls
 * this function to add them to the buffer from where userspace पढ़ोs.
 */
पूर्णांक drm_crtc_add_crc_entry(काष्ठा drm_crtc *crtc, bool has_frame,
			   uपूर्णांक32_t frame, uपूर्णांक32_t *crcs)
अणु
	काष्ठा drm_crtc_crc *crc = &crtc->crc;
	काष्ठा drm_crtc_crc_entry *entry;
	पूर्णांक head, tail;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&crc->lock, flags);

	/* Caller may not have noticed yet that userspace has stopped पढ़ोing */
	अगर (!crc->entries) अणु
		spin_unlock_irqrestore(&crc->lock, flags);
		वापस -EINVAL;
	पूर्ण

	head = crc->head;
	tail = crc->tail;

	अगर (CIRC_SPACE(head, tail, DRM_CRC_ENTRIES_NR) < 1) अणु
		bool was_overflow = crc->overflow;

		crc->overflow = true;
		spin_unlock_irqrestore(&crc->lock, flags);

		अगर (!was_overflow)
			DRM_ERROR("Overflow of CRC buffer, userspace reads too slow.\n");

		वापस -ENOBUFS;
	पूर्ण

	entry = &crc->entries[head];
	entry->frame = frame;
	entry->has_frame_counter = has_frame;
	स_नकल(&entry->crcs, crcs, माप(*crcs) * crc->values_cnt);

	head = (head + 1) & (DRM_CRC_ENTRIES_NR - 1);
	crc->head = head;

	spin_unlock_irqrestore(&crc->lock, flags);

	wake_up_पूर्णांकerruptible(&crc->wq);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(drm_crtc_add_crc_entry);
