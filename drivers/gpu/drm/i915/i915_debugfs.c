<शैली गुरु>
/*
 * Copyright तऊ 2008 Intel Corporation
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
 * Authors:
 *    Eric Anholt <eric@anholt.net>
 *    Keith Packard <keithp@keithp.com>
 *
 */

#समावेश <linux/sched/mm.h>
#समावेश <linux/sort.h>

#समावेश <drm/drm_debugfs.h>

#समावेश "gem/i915_gem_context.h"
#समावेश "gt/intel_gt_buffer_pool.h"
#समावेश "gt/intel_gt_clock_utils.h"
#समावेश "gt/intel_gt.h"
#समावेश "gt/intel_gt_pm.h"
#समावेश "gt/intel_gt_requests.h"
#समावेश "gt/intel_reset.h"
#समावेश "gt/intel_rc6.h"
#समावेश "gt/intel_rps.h"
#समावेश "gt/intel_sseu_debugfs.h"

#समावेश "i915_debugfs.h"
#समावेश "i915_debugfs_params.h"
#समावेश "i915_irq.h"
#समावेश "i915_scheduler.h"
#समावेश "i915_trace.h"
#समावेश "intel_pm.h"
#समावेश "intel_sideband.h"

अटल अंतरभूत काष्ठा drm_i915_निजी *node_to_i915(काष्ठा drm_info_node *node)
अणु
	वापस to_i915(node->minor->dev);
पूर्ण

अटल पूर्णांक i915_capabilities(काष्ठा seq_file *m, व्योम *data)
अणु
	काष्ठा drm_i915_निजी *i915 = node_to_i915(m->निजी);
	काष्ठा drm_prपूर्णांकer p = drm_seq_file_prपूर्णांकer(m);

	seq_म_लिखो(m, "pch: %d\n", INTEL_PCH_TYPE(i915));

	पूर्णांकel_device_info_prपूर्णांक_अटल(INTEL_INFO(i915), &p);
	पूर्णांकel_device_info_prपूर्णांक_runसमय(RUNTIME_INFO(i915), &p);
	पूर्णांकel_gt_info_prपूर्णांक(&i915->gt.info, &p);
	पूर्णांकel_driver_caps_prपूर्णांक(&i915->caps, &p);

	kernel_param_lock(THIS_MODULE);
	i915_params_dump(&i915->params, &p);
	kernel_param_unlock(THIS_MODULE);

	वापस 0;
पूर्ण

अटल अक्षर get_tiling_flag(काष्ठा drm_i915_gem_object *obj)
अणु
	चयन (i915_gem_object_get_tiling(obj)) अणु
	शेष:
	हाल I915_TILING_NONE: वापस ' ';
	हाल I915_TILING_X: वापस 'X';
	हाल I915_TILING_Y: वापस 'Y';
	पूर्ण
पूर्ण

अटल अक्षर get_global_flag(काष्ठा drm_i915_gem_object *obj)
अणु
	वापस READ_ONCE(obj->userfault_count) ? 'g' : ' ';
पूर्ण

अटल अक्षर get_pin_mapped_flag(काष्ठा drm_i915_gem_object *obj)
अणु
	वापस obj->mm.mapping ? 'M' : ' ';
पूर्ण

अटल स्थिर अक्षर *
stringअगरy_page_sizes(अचिन्हित पूर्णांक page_sizes, अक्षर *buf, माप_प्रकार len)
अणु
	माप_प्रकार x = 0;

	चयन (page_sizes) अणु
	हाल 0:
		वापस "";
	हाल I915_GTT_PAGE_SIZE_4K:
		वापस "4K";
	हाल I915_GTT_PAGE_SIZE_64K:
		वापस "64K";
	हाल I915_GTT_PAGE_SIZE_2M:
		वापस "2M";
	शेष:
		अगर (!buf)
			वापस "M";

		अगर (page_sizes & I915_GTT_PAGE_SIZE_2M)
			x += snम_लिखो(buf + x, len - x, "2M, ");
		अगर (page_sizes & I915_GTT_PAGE_SIZE_64K)
			x += snम_लिखो(buf + x, len - x, "64K, ");
		अगर (page_sizes & I915_GTT_PAGE_SIZE_4K)
			x += snम_लिखो(buf + x, len - x, "4K, ");
		buf[x-2] = '\0';

		वापस buf;
	पूर्ण
पूर्ण

व्योम
i915_debugfs_describe_obj(काष्ठा seq_file *m, काष्ठा drm_i915_gem_object *obj)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(obj->base.dev);
	काष्ठा पूर्णांकel_engine_cs *engine;
	काष्ठा i915_vma *vma;
	पूर्णांक pin_count = 0;

	seq_म_लिखो(m, "%pK: %c%c%c %8zdKiB %02x %02x %s%s%s",
		   &obj->base,
		   get_tiling_flag(obj),
		   get_global_flag(obj),
		   get_pin_mapped_flag(obj),
		   obj->base.size / 1024,
		   obj->पढ़ो_करोमुख्यs,
		   obj->ग_लिखो_करोमुख्य,
		   i915_cache_level_str(dev_priv, obj->cache_level),
		   obj->mm.dirty ? " dirty" : "",
		   obj->mm.madv == I915_MADV_DONTNEED ? " purgeable" : "");
	अगर (obj->base.name)
		seq_म_लिखो(m, " (name: %d)", obj->base.name);

	spin_lock(&obj->vma.lock);
	list_क्रम_each_entry(vma, &obj->vma.list, obj_link) अणु
		अगर (!drm_mm_node_allocated(&vma->node))
			जारी;

		spin_unlock(&obj->vma.lock);

		अगर (i915_vma_is_pinned(vma))
			pin_count++;

		seq_म_लिखो(m, " (%sgtt offset: %08llx, size: %08llx, pages: %s",
			   i915_vma_is_ggtt(vma) ? "g" : "pp",
			   vma->node.start, vma->node.size,
			   stringअगरy_page_sizes(vma->page_sizes.gtt, शून्य, 0));
		अगर (i915_vma_is_ggtt(vma)) अणु
			चयन (vma->ggtt_view.type) अणु
			हाल I915_GGTT_VIEW_NORMAL:
				seq_माला_दो(m, ", normal");
				अवरोध;

			हाल I915_GGTT_VIEW_PARTIAL:
				seq_म_लिखो(m, ", partial [%08llx+%x]",
					   vma->ggtt_view.partial.offset << PAGE_SHIFT,
					   vma->ggtt_view.partial.size << PAGE_SHIFT);
				अवरोध;

			हाल I915_GGTT_VIEW_ROTATED:
				seq_म_लिखो(m, ", rotated [(%ux%u, src_stride=%u, dst_stride=%u, offset=%u), (%ux%u, src_stride=%u, dst_stride=%u, offset=%u)]",
					   vma->ggtt_view.rotated.plane[0].width,
					   vma->ggtt_view.rotated.plane[0].height,
					   vma->ggtt_view.rotated.plane[0].src_stride,
					   vma->ggtt_view.rotated.plane[0].dst_stride,
					   vma->ggtt_view.rotated.plane[0].offset,
					   vma->ggtt_view.rotated.plane[1].width,
					   vma->ggtt_view.rotated.plane[1].height,
					   vma->ggtt_view.rotated.plane[1].src_stride,
					   vma->ggtt_view.rotated.plane[1].dst_stride,
					   vma->ggtt_view.rotated.plane[1].offset);
				अवरोध;

			हाल I915_GGTT_VIEW_REMAPPED:
				seq_म_लिखो(m, ", remapped [(%ux%u, src_stride=%u, dst_stride=%u, offset=%u), (%ux%u, src_stride=%u, dst_stride=%u, offset=%u)]",
					   vma->ggtt_view.remapped.plane[0].width,
					   vma->ggtt_view.remapped.plane[0].height,
					   vma->ggtt_view.remapped.plane[0].src_stride,
					   vma->ggtt_view.remapped.plane[0].dst_stride,
					   vma->ggtt_view.remapped.plane[0].offset,
					   vma->ggtt_view.remapped.plane[1].width,
					   vma->ggtt_view.remapped.plane[1].height,
					   vma->ggtt_view.remapped.plane[1].src_stride,
					   vma->ggtt_view.remapped.plane[1].dst_stride,
					   vma->ggtt_view.remapped.plane[1].offset);
				अवरोध;

			शेष:
				MISSING_CASE(vma->ggtt_view.type);
				अवरोध;
			पूर्ण
		पूर्ण
		अगर (vma->fence)
			seq_म_लिखो(m, " , fence: %d", vma->fence->id);
		seq_माला_दो(m, ")");

		spin_lock(&obj->vma.lock);
	पूर्ण
	spin_unlock(&obj->vma.lock);

	seq_म_लिखो(m, " (pinned x %d)", pin_count);
	अगर (i915_gem_object_is_stolen(obj))
		seq_म_लिखो(m, " (stolen: %08llx)", obj->stolen->start);
	अगर (i915_gem_object_is_framebuffer(obj))
		seq_म_लिखो(m, " (fb)");

	engine = i915_gem_object_last_ग_लिखो_engine(obj);
	अगर (engine)
		seq_म_लिखो(m, " (%s)", engine->name);
पूर्ण

अटल पूर्णांक i915_gem_object_info(काष्ठा seq_file *m, व्योम *data)
अणु
	काष्ठा drm_i915_निजी *i915 = node_to_i915(m->निजी);
	काष्ठा पूर्णांकel_memory_region *mr;
	क्रमागत पूर्णांकel_region_id id;

	seq_म_लिखो(m, "%u shrinkable [%u free] objects, %llu bytes\n",
		   i915->mm.shrink_count,
		   atomic_पढ़ो(&i915->mm.मुक्त_count),
		   i915->mm.shrink_memory);
	क्रम_each_memory_region(mr, i915, id)
		seq_म_लिखो(m, "%s: total:%pa, available:%pa bytes\n",
			   mr->name, &mr->total, &mr->avail);

	वापस 0;
पूर्ण

#अगर IS_ENABLED(CONFIG_DRM_I915_CAPTURE_ERROR)
अटल sमाप_प्रकार gpu_state_पढ़ो(काष्ठा file *file, अक्षर __user *ubuf,
			      माप_प्रकार count, loff_t *pos)
अणु
	काष्ठा i915_gpu_coredump *error;
	sमाप_प्रकार ret;
	व्योम *buf;

	error = file->निजी_data;
	अगर (!error)
		वापस 0;

	/* Bounce buffer required because of kernfs __user API convenience. */
	buf = kदो_स्मृति(count, GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;

	ret = i915_gpu_coredump_copy_to_buffer(error, buf, *pos, count);
	अगर (ret <= 0)
		जाओ out;

	अगर (!copy_to_user(ubuf, buf, ret))
		*pos += ret;
	अन्यथा
		ret = -EFAULT;

out:
	kमुक्त(buf);
	वापस ret;
पूर्ण

अटल पूर्णांक gpu_state_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	i915_gpu_coredump_put(file->निजी_data);
	वापस 0;
पूर्ण

अटल पूर्णांक i915_gpu_info_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा drm_i915_निजी *i915 = inode->i_निजी;
	काष्ठा i915_gpu_coredump *gpu;
	पूर्णांकel_wakeref_t wakeref;

	gpu = शून्य;
	with_पूर्णांकel_runसमय_pm(&i915->runसमय_pm, wakeref)
		gpu = i915_gpu_coredump(&i915->gt, ALL_ENGINES);
	अगर (IS_ERR(gpu))
		वापस PTR_ERR(gpu);

	file->निजी_data = gpu;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा file_operations i915_gpu_info_fops = अणु
	.owner = THIS_MODULE,
	.खोलो = i915_gpu_info_खोलो,
	.पढ़ो = gpu_state_पढ़ो,
	.llseek = शेष_llseek,
	.release = gpu_state_release,
पूर्ण;

अटल sमाप_प्रकार
i915_error_state_ग_लिखो(काष्ठा file *filp,
		       स्थिर अक्षर __user *ubuf,
		       माप_प्रकार cnt,
		       loff_t *ppos)
अणु
	काष्ठा i915_gpu_coredump *error = filp->निजी_data;

	अगर (!error)
		वापस 0;

	drm_dbg(&error->i915->drm, "Resetting error state\n");
	i915_reset_error_state(error->i915);

	वापस cnt;
पूर्ण

अटल पूर्णांक i915_error_state_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा i915_gpu_coredump *error;

	error = i915_first_error_state(inode->i_निजी);
	अगर (IS_ERR(error))
		वापस PTR_ERR(error);

	file->निजी_data  = error;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा file_operations i915_error_state_fops = अणु
	.owner = THIS_MODULE,
	.खोलो = i915_error_state_खोलो,
	.पढ़ो = gpu_state_पढ़ो,
	.ग_लिखो = i915_error_state_ग_लिखो,
	.llseek = शेष_llseek,
	.release = gpu_state_release,
पूर्ण;
#पूर्ण_अगर

अटल पूर्णांक i915_frequency_info(काष्ठा seq_file *m, व्योम *unused)
अणु
	काष्ठा drm_i915_निजी *dev_priv = node_to_i915(m->निजी);
	काष्ठा पूर्णांकel_uncore *uncore = &dev_priv->uncore;
	काष्ठा पूर्णांकel_rps *rps = &dev_priv->gt.rps;
	पूर्णांकel_wakeref_t wakeref;

	wakeref = पूर्णांकel_runसमय_pm_get(&dev_priv->runसमय_pm);

	अगर (IS_GEN(dev_priv, 5)) अणु
		u16 rgvswctl = पूर्णांकel_uncore_पढ़ो16(uncore, MEMSWCTL);
		u16 rgvstat = पूर्णांकel_uncore_पढ़ो16(uncore, MEMSTAT_ILK);

		seq_म_लिखो(m, "Requested P-state: %d\n", (rgvswctl >> 8) & 0xf);
		seq_म_लिखो(m, "Requested VID: %d\n", rgvswctl & 0x3f);
		seq_म_लिखो(m, "Current VID: %d\n", (rgvstat & MEMSTAT_VID_MASK) >>
			   MEMSTAT_VID_SHIFT);
		seq_म_लिखो(m, "Current P-state: %d\n",
			   (rgvstat & MEMSTAT_PSTATE_MASK) >> MEMSTAT_PSTATE_SHIFT);
	पूर्ण अन्यथा अगर (IS_VALLEYVIEW(dev_priv) || IS_CHERRYVIEW(dev_priv)) अणु
		u32 rpmodectl, freq_sts;

		rpmodectl = पूर्णांकel_uncore_पढ़ो(&dev_priv->uncore, GEN6_RP_CONTROL);
		seq_म_लिखो(m, "Video Turbo Mode: %s\n",
			   yesno(rpmodectl & GEN6_RP_MEDIA_TURBO));
		seq_म_लिखो(m, "HW control enabled: %s\n",
			   yesno(rpmodectl & GEN6_RP_ENABLE));
		seq_म_लिखो(m, "SW control enabled: %s\n",
			   yesno((rpmodectl & GEN6_RP_MEDIA_MODE_MASK) ==
				  GEN6_RP_MEDIA_SW_MODE));

		vlv_punit_get(dev_priv);
		freq_sts = vlv_punit_पढ़ो(dev_priv, PUNIT_REG_GPU_FREQ_STS);
		vlv_punit_put(dev_priv);

		seq_म_लिखो(m, "PUNIT_REG_GPU_FREQ_STS: 0x%08x\n", freq_sts);
		seq_म_लिखो(m, "DDR freq: %d MHz\n", dev_priv->mem_freq);

		seq_म_लिखो(m, "actual GPU freq: %d MHz\n",
			   पूर्णांकel_gpu_freq(rps, (freq_sts >> 8) & 0xff));

		seq_म_लिखो(m, "current GPU freq: %d MHz\n",
			   पूर्णांकel_gpu_freq(rps, rps->cur_freq));

		seq_म_लिखो(m, "max GPU freq: %d MHz\n",
			   पूर्णांकel_gpu_freq(rps, rps->max_freq));

		seq_म_लिखो(m, "min GPU freq: %d MHz\n",
			   पूर्णांकel_gpu_freq(rps, rps->min_freq));

		seq_म_लिखो(m, "idle GPU freq: %d MHz\n",
			   पूर्णांकel_gpu_freq(rps, rps->idle_freq));

		seq_म_लिखो(m,
			   "efficient (RPe) frequency: %d MHz\n",
			   पूर्णांकel_gpu_freq(rps, rps->efficient_freq));
	पूर्ण अन्यथा अगर (INTEL_GEN(dev_priv) >= 6) अणु
		u32 rp_state_limits;
		u32 gt_perf_status;
		u32 rp_state_cap;
		u32 rpmodectl, rpinclimit, rpdeclimit;
		u32 rpstat, cagf, reqf;
		u32 rpupei, rpcurup, rpprevup;
		u32 rpकरोwnei, rpcurकरोwn, rpprevकरोwn;
		u32 pm_ier, pm_imr, pm_isr, pm_iir, pm_mask;
		पूर्णांक max_freq;

		rp_state_limits = पूर्णांकel_uncore_पढ़ो(&dev_priv->uncore, GEN6_RP_STATE_LIMITS);
		अगर (IS_GEN9_LP(dev_priv)) अणु
			rp_state_cap = पूर्णांकel_uncore_पढ़ो(&dev_priv->uncore, BXT_RP_STATE_CAP);
			gt_perf_status = पूर्णांकel_uncore_पढ़ो(&dev_priv->uncore, BXT_GT_PERF_STATUS);
		पूर्ण अन्यथा अणु
			rp_state_cap = पूर्णांकel_uncore_पढ़ो(&dev_priv->uncore, GEN6_RP_STATE_CAP);
			gt_perf_status = पूर्णांकel_uncore_पढ़ो(&dev_priv->uncore, GEN6_GT_PERF_STATUS);
		पूर्ण

		/* RPSTAT1 is in the GT घातer well */
		पूर्णांकel_uncore_क्रमcewake_get(&dev_priv->uncore, FORCEWAKE_ALL);

		reqf = पूर्णांकel_uncore_पढ़ो(&dev_priv->uncore, GEN6_RPNSWREQ);
		अगर (INTEL_GEN(dev_priv) >= 9)
			reqf >>= 23;
		अन्यथा अणु
			reqf &= ~GEN6_TURBO_DISABLE;
			अगर (IS_HASWELL(dev_priv) || IS_BROADWELL(dev_priv))
				reqf >>= 24;
			अन्यथा
				reqf >>= 25;
		पूर्ण
		reqf = पूर्णांकel_gpu_freq(rps, reqf);

		rpmodectl = पूर्णांकel_uncore_पढ़ो(&dev_priv->uncore, GEN6_RP_CONTROL);
		rpinclimit = पूर्णांकel_uncore_पढ़ो(&dev_priv->uncore, GEN6_RP_UP_THRESHOLD);
		rpdeclimit = पूर्णांकel_uncore_पढ़ो(&dev_priv->uncore, GEN6_RP_DOWN_THRESHOLD);

		rpstat = पूर्णांकel_uncore_पढ़ो(&dev_priv->uncore, GEN6_RPSTAT1);
		rpupei = पूर्णांकel_uncore_पढ़ो(&dev_priv->uncore, GEN6_RP_CUR_UP_EI) & GEN6_CURICONT_MASK;
		rpcurup = पूर्णांकel_uncore_पढ़ो(&dev_priv->uncore, GEN6_RP_CUR_UP) & GEN6_CURBSYTAVG_MASK;
		rpprevup = पूर्णांकel_uncore_पढ़ो(&dev_priv->uncore, GEN6_RP_PREV_UP) & GEN6_CURBSYTAVG_MASK;
		rpकरोwnei = पूर्णांकel_uncore_पढ़ो(&dev_priv->uncore, GEN6_RP_CUR_DOWN_EI) & GEN6_CURIAVG_MASK;
		rpcurकरोwn = पूर्णांकel_uncore_पढ़ो(&dev_priv->uncore, GEN6_RP_CUR_DOWN) & GEN6_CURBSYTAVG_MASK;
		rpprevकरोwn = पूर्णांकel_uncore_पढ़ो(&dev_priv->uncore, GEN6_RP_PREV_DOWN) & GEN6_CURBSYTAVG_MASK;
		cagf = पूर्णांकel_rps_पढ़ो_actual_frequency(rps);

		पूर्णांकel_uncore_क्रमcewake_put(&dev_priv->uncore, FORCEWAKE_ALL);

		अगर (INTEL_GEN(dev_priv) >= 11) अणु
			pm_ier = पूर्णांकel_uncore_पढ़ो(&dev_priv->uncore, GEN11_GPM_WGBOXPERF_INTR_ENABLE);
			pm_imr = पूर्णांकel_uncore_पढ़ो(&dev_priv->uncore, GEN11_GPM_WGBOXPERF_INTR_MASK);
			/*
			 * The equivalent to the PM ISR & IIR cannot be पढ़ो
			 * without affecting the current state of the प्रणाली
			 */
			pm_isr = 0;
			pm_iir = 0;
		पूर्ण अन्यथा अगर (INTEL_GEN(dev_priv) >= 8) अणु
			pm_ier = पूर्णांकel_uncore_पढ़ो(&dev_priv->uncore, GEN8_GT_IER(2));
			pm_imr = पूर्णांकel_uncore_पढ़ो(&dev_priv->uncore, GEN8_GT_IMR(2));
			pm_isr = पूर्णांकel_uncore_पढ़ो(&dev_priv->uncore, GEN8_GT_ISR(2));
			pm_iir = पूर्णांकel_uncore_पढ़ो(&dev_priv->uncore, GEN8_GT_IIR(2));
		पूर्ण अन्यथा अणु
			pm_ier = पूर्णांकel_uncore_पढ़ो(&dev_priv->uncore, GEN6_PMIER);
			pm_imr = पूर्णांकel_uncore_पढ़ो(&dev_priv->uncore, GEN6_PMIMR);
			pm_isr = पूर्णांकel_uncore_पढ़ो(&dev_priv->uncore, GEN6_PMISR);
			pm_iir = पूर्णांकel_uncore_पढ़ो(&dev_priv->uncore, GEN6_PMIIR);
		पूर्ण
		pm_mask = पूर्णांकel_uncore_पढ़ो(&dev_priv->uncore, GEN6_PMINTRMSK);

		seq_म_लिखो(m, "Video Turbo Mode: %s\n",
			   yesno(rpmodectl & GEN6_RP_MEDIA_TURBO));
		seq_म_लिखो(m, "HW control enabled: %s\n",
			   yesno(rpmodectl & GEN6_RP_ENABLE));
		seq_म_लिखो(m, "SW control enabled: %s\n",
			   yesno((rpmodectl & GEN6_RP_MEDIA_MODE_MASK) ==
				  GEN6_RP_MEDIA_SW_MODE));

		seq_म_लिखो(m, "PM IER=0x%08x IMR=0x%08x, MASK=0x%08x\n",
			   pm_ier, pm_imr, pm_mask);
		अगर (INTEL_GEN(dev_priv) <= 10)
			seq_म_लिखो(m, "PM ISR=0x%08x IIR=0x%08x\n",
				   pm_isr, pm_iir);
		seq_म_लिखो(m, "pm_intrmsk_mbz: 0x%08x\n",
			   rps->pm_पूर्णांकrmsk_mbz);
		seq_म_लिखो(m, "GT_PERF_STATUS: 0x%08x\n", gt_perf_status);
		seq_म_लिखो(m, "Render p-state ratio: %d\n",
			   (gt_perf_status & (INTEL_GEN(dev_priv) >= 9 ? 0x1ff00 : 0xff00)) >> 8);
		seq_म_लिखो(m, "Render p-state VID: %d\n",
			   gt_perf_status & 0xff);
		seq_म_लिखो(m, "Render p-state limit: %d\n",
			   rp_state_limits & 0xff);
		seq_म_लिखो(m, "RPSTAT1: 0x%08x\n", rpstat);
		seq_म_लिखो(m, "RPMODECTL: 0x%08x\n", rpmodectl);
		seq_म_लिखो(m, "RPINCLIMIT: 0x%08x\n", rpinclimit);
		seq_म_लिखो(m, "RPDECLIMIT: 0x%08x\n", rpdeclimit);
		seq_म_लिखो(m, "RPNSWREQ: %dMHz\n", reqf);
		seq_म_लिखो(m, "CAGF: %dMHz\n", cagf);
		seq_म_लिखो(m, "RP CUR UP EI: %d (%lldns)\n",
			   rpupei,
			   पूर्णांकel_gt_pm_पूर्णांकerval_to_ns(&dev_priv->gt, rpupei));
		seq_म_लिखो(m, "RP CUR UP: %d (%lldun)\n",
			   rpcurup,
			   पूर्णांकel_gt_pm_पूर्णांकerval_to_ns(&dev_priv->gt, rpcurup));
		seq_म_लिखो(m, "RP PREV UP: %d (%lldns)\n",
			   rpprevup,
			   पूर्णांकel_gt_pm_पूर्णांकerval_to_ns(&dev_priv->gt, rpprevup));
		seq_म_लिखो(m, "Up threshold: %d%%\n",
			   rps->घातer.up_threshold);

		seq_म_लिखो(m, "RP CUR DOWN EI: %d (%lldns)\n",
			   rpकरोwnei,
			   पूर्णांकel_gt_pm_पूर्णांकerval_to_ns(&dev_priv->gt,
						      rpकरोwnei));
		seq_म_लिखो(m, "RP CUR DOWN: %d (%lldns)\n",
			   rpcurकरोwn,
			   पूर्णांकel_gt_pm_पूर्णांकerval_to_ns(&dev_priv->gt,
						      rpcurकरोwn));
		seq_म_लिखो(m, "RP PREV DOWN: %d (%lldns)\n",
			   rpprevकरोwn,
			   पूर्णांकel_gt_pm_पूर्णांकerval_to_ns(&dev_priv->gt,
						      rpprevकरोwn));
		seq_म_लिखो(m, "Down threshold: %d%%\n",
			   rps->घातer.करोwn_threshold);

		max_freq = (IS_GEN9_LP(dev_priv) ? rp_state_cap >> 0 :
			    rp_state_cap >> 16) & 0xff;
		max_freq *= (IS_GEN9_BC(dev_priv) ||
			     INTEL_GEN(dev_priv) >= 10 ? GEN9_FREQ_SCALER : 1);
		seq_म_लिखो(m, "Lowest (RPN) frequency: %dMHz\n",
			   पूर्णांकel_gpu_freq(rps, max_freq));

		max_freq = (rp_state_cap & 0xff00) >> 8;
		max_freq *= (IS_GEN9_BC(dev_priv) ||
			     INTEL_GEN(dev_priv) >= 10 ? GEN9_FREQ_SCALER : 1);
		seq_म_लिखो(m, "Nominal (RP1) frequency: %dMHz\n",
			   पूर्णांकel_gpu_freq(rps, max_freq));

		max_freq = (IS_GEN9_LP(dev_priv) ? rp_state_cap >> 16 :
			    rp_state_cap >> 0) & 0xff;
		max_freq *= (IS_GEN9_BC(dev_priv) ||
			     INTEL_GEN(dev_priv) >= 10 ? GEN9_FREQ_SCALER : 1);
		seq_म_लिखो(m, "Max non-overclocked (RP0) frequency: %dMHz\n",
			   पूर्णांकel_gpu_freq(rps, max_freq));
		seq_म_लिखो(m, "Max overclocked frequency: %dMHz\n",
			   पूर्णांकel_gpu_freq(rps, rps->max_freq));

		seq_म_लिखो(m, "Current freq: %d MHz\n",
			   पूर्णांकel_gpu_freq(rps, rps->cur_freq));
		seq_म_लिखो(m, "Actual freq: %d MHz\n", cagf);
		seq_म_लिखो(m, "Idle freq: %d MHz\n",
			   पूर्णांकel_gpu_freq(rps, rps->idle_freq));
		seq_म_लिखो(m, "Min freq: %d MHz\n",
			   पूर्णांकel_gpu_freq(rps, rps->min_freq));
		seq_म_लिखो(m, "Boost freq: %d MHz\n",
			   पूर्णांकel_gpu_freq(rps, rps->boost_freq));
		seq_म_लिखो(m, "Max freq: %d MHz\n",
			   पूर्णांकel_gpu_freq(rps, rps->max_freq));
		seq_म_लिखो(m,
			   "efficient (RPe) frequency: %d MHz\n",
			   पूर्णांकel_gpu_freq(rps, rps->efficient_freq));
	पूर्ण अन्यथा अणु
		seq_माला_दो(m, "no P-state info available\n");
	पूर्ण

	seq_म_लिखो(m, "Current CD clock frequency: %d kHz\n", dev_priv->cdclk.hw.cdclk);
	seq_म_लिखो(m, "Max CD clock frequency: %d kHz\n", dev_priv->max_cdclk_freq);
	seq_म_लिखो(m, "Max pixel clock frequency: %d kHz\n", dev_priv->max_करोtclk_freq);

	पूर्णांकel_runसमय_pm_put(&dev_priv->runसमय_pm, wakeref);
	वापस 0;
पूर्ण

अटल स्थिर अक्षर *swizzle_string(अचिन्हित swizzle)
अणु
	चयन (swizzle) अणु
	हाल I915_BIT_6_SWIZZLE_NONE:
		वापस "none";
	हाल I915_BIT_6_SWIZZLE_9:
		वापस "bit9";
	हाल I915_BIT_6_SWIZZLE_9_10:
		वापस "bit9/bit10";
	हाल I915_BIT_6_SWIZZLE_9_11:
		वापस "bit9/bit11";
	हाल I915_BIT_6_SWIZZLE_9_10_11:
		वापस "bit9/bit10/bit11";
	हाल I915_BIT_6_SWIZZLE_9_17:
		वापस "bit9/bit17";
	हाल I915_BIT_6_SWIZZLE_9_10_17:
		वापस "bit9/bit10/bit17";
	हाल I915_BIT_6_SWIZZLE_UNKNOWN:
		वापस "unknown";
	पूर्ण

	वापस "bug";
पूर्ण

अटल पूर्णांक i915_swizzle_info(काष्ठा seq_file *m, व्योम *data)
अणु
	काष्ठा drm_i915_निजी *dev_priv = node_to_i915(m->निजी);
	काष्ठा पूर्णांकel_uncore *uncore = &dev_priv->uncore;
	पूर्णांकel_wakeref_t wakeref;

	seq_म_लिखो(m, "bit6 swizzle for X-tiling = %s\n",
		   swizzle_string(dev_priv->ggtt.bit_6_swizzle_x));
	seq_म_लिखो(m, "bit6 swizzle for Y-tiling = %s\n",
		   swizzle_string(dev_priv->ggtt.bit_6_swizzle_y));

	अगर (dev_priv->quirks & QUIRK_PIN_SWIZZLED_PAGES)
		seq_माला_दो(m, "L-shaped memory detected\n");

	/* On BDW+, swizzling is not used. See detect_bit_6_swizzle() */
	अगर (INTEL_GEN(dev_priv) >= 8 || IS_VALLEYVIEW(dev_priv))
		वापस 0;

	wakeref = पूर्णांकel_runसमय_pm_get(&dev_priv->runसमय_pm);

	अगर (IS_GEN_RANGE(dev_priv, 3, 4)) अणु
		seq_म_लिखो(m, "DDC = 0x%08x\n",
			   पूर्णांकel_uncore_पढ़ो(uncore, DCC));
		seq_म_लिखो(m, "DDC2 = 0x%08x\n",
			   पूर्णांकel_uncore_पढ़ो(uncore, DCC2));
		seq_म_लिखो(m, "C0DRB3 = 0x%04x\n",
			   पूर्णांकel_uncore_पढ़ो16(uncore, C0DRB3));
		seq_म_लिखो(m, "C1DRB3 = 0x%04x\n",
			   पूर्णांकel_uncore_पढ़ो16(uncore, C1DRB3));
	पूर्ण अन्यथा अगर (INTEL_GEN(dev_priv) >= 6) अणु
		seq_म_लिखो(m, "MAD_DIMM_C0 = 0x%08x\n",
			   पूर्णांकel_uncore_पढ़ो(uncore, MAD_DIMM_C0));
		seq_म_लिखो(m, "MAD_DIMM_C1 = 0x%08x\n",
			   पूर्णांकel_uncore_पढ़ो(uncore, MAD_DIMM_C1));
		seq_म_लिखो(m, "MAD_DIMM_C2 = 0x%08x\n",
			   पूर्णांकel_uncore_पढ़ो(uncore, MAD_DIMM_C2));
		seq_म_लिखो(m, "TILECTL = 0x%08x\n",
			   पूर्णांकel_uncore_पढ़ो(uncore, TILECTL));
		अगर (INTEL_GEN(dev_priv) >= 8)
			seq_म_लिखो(m, "GAMTARBMODE = 0x%08x\n",
				   पूर्णांकel_uncore_पढ़ो(uncore, GAMTARBMODE));
		अन्यथा
			seq_म_लिखो(m, "ARB_MODE = 0x%08x\n",
				   पूर्णांकel_uncore_पढ़ो(uncore, ARB_MODE));
		seq_म_लिखो(m, "DISP_ARB_CTL = 0x%08x\n",
			   पूर्णांकel_uncore_पढ़ो(uncore, DISP_ARB_CTL));
	पूर्ण

	पूर्णांकel_runसमय_pm_put(&dev_priv->runसमय_pm, wakeref);

	वापस 0;
पूर्ण

अटल पूर्णांक i915_rps_boost_info(काष्ठा seq_file *m, व्योम *data)
अणु
	काष्ठा drm_i915_निजी *dev_priv = node_to_i915(m->निजी);
	काष्ठा पूर्णांकel_rps *rps = &dev_priv->gt.rps;

	seq_म_लिखो(m, "RPS enabled? %s\n", yesno(पूर्णांकel_rps_is_enabled(rps)));
	seq_म_लिखो(m, "RPS active? %s\n", yesno(पूर्णांकel_rps_is_active(rps)));
	seq_म_लिखो(m, "GPU busy? %s\n", yesno(dev_priv->gt.awake));
	seq_म_लिखो(m, "Boosts outstanding? %d\n",
		   atomic_पढ़ो(&rps->num_रुकोers));
	seq_म_लिखो(m, "Interactive? %d\n", READ_ONCE(rps->घातer.पूर्णांकeractive));
	seq_म_लिखो(m, "Frequency requested %d, actual %d\n",
		   पूर्णांकel_gpu_freq(rps, rps->cur_freq),
		   पूर्णांकel_rps_पढ़ो_actual_frequency(rps));
	seq_म_लिखो(m, "  min hard:%d, soft:%d; max soft:%d, hard:%d\n",
		   पूर्णांकel_gpu_freq(rps, rps->min_freq),
		   पूर्णांकel_gpu_freq(rps, rps->min_freq_softlimit),
		   पूर्णांकel_gpu_freq(rps, rps->max_freq_softlimit),
		   पूर्णांकel_gpu_freq(rps, rps->max_freq));
	seq_म_लिखो(m, "  idle:%d, efficient:%d, boost:%d\n",
		   पूर्णांकel_gpu_freq(rps, rps->idle_freq),
		   पूर्णांकel_gpu_freq(rps, rps->efficient_freq),
		   पूर्णांकel_gpu_freq(rps, rps->boost_freq));

	seq_म_लिखो(m, "Wait boosts: %d\n", READ_ONCE(rps->boosts));

	वापस 0;
पूर्ण

अटल पूर्णांक i915_runसमय_pm_status(काष्ठा seq_file *m, व्योम *unused)
अणु
	काष्ठा drm_i915_निजी *dev_priv = node_to_i915(m->निजी);
	काष्ठा pci_dev *pdev = to_pci_dev(dev_priv->drm.dev);

	अगर (!HAS_RUNTIME_PM(dev_priv))
		seq_माला_दो(m, "Runtime power management not supported\n");

	seq_म_लिखो(m, "Runtime power status: %s\n",
		   enableddisabled(!dev_priv->घातer_करोमुख्यs.init_wakeref));

	seq_म_लिखो(m, "GPU idle: %s\n", yesno(!dev_priv->gt.awake));
	seq_म_लिखो(m, "IRQs disabled: %s\n",
		   yesno(!पूर्णांकel_irqs_enabled(dev_priv)));
#अगर_घोषित CONFIG_PM
	seq_म_लिखो(m, "Usage count: %d\n",
		   atomic_पढ़ो(&dev_priv->drm.dev->घातer.usage_count));
#अन्यथा
	seq_म_लिखो(m, "Device Power Management (CONFIG_PM) disabled\n");
#पूर्ण_अगर
	seq_म_लिखो(m, "PCI device power state: %s [%d]\n",
		   pci_घातer_name(pdev->current_state),
		   pdev->current_state);

	अगर (IS_ENABLED(CONFIG_DRM_I915_DEBUG_RUNTIME_PM)) अणु
		काष्ठा drm_prपूर्णांकer p = drm_seq_file_prपूर्णांकer(m);

		prपूर्णांक_पूर्णांकel_runसमय_pm_wakeref(&dev_priv->runसमय_pm, &p);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक i915_engine_info(काष्ठा seq_file *m, व्योम *unused)
अणु
	काष्ठा drm_i915_निजी *i915 = node_to_i915(m->निजी);
	काष्ठा पूर्णांकel_engine_cs *engine;
	पूर्णांकel_wakeref_t wakeref;
	काष्ठा drm_prपूर्णांकer p;

	wakeref = पूर्णांकel_runसमय_pm_get(&i915->runसमय_pm);

	seq_म_लिखो(m, "GT awake? %s [%d], %llums\n",
		   yesno(i915->gt.awake),
		   atomic_पढ़ो(&i915->gt.wakeref.count),
		   kसमय_प्रकारo_ms(पूर्णांकel_gt_get_awake_समय(&i915->gt)));
	seq_म_लिखो(m, "CS timestamp frequency: %u Hz, %d ns\n",
		   i915->gt.घड़ी_frequency,
		   i915->gt.घड़ी_period_ns);

	p = drm_seq_file_prपूर्णांकer(m);
	क्रम_each_uabi_engine(engine, i915)
		पूर्णांकel_engine_dump(engine, &p, "%s\n", engine->name);

	पूर्णांकel_gt_show_समयlines(&i915->gt, &p, i915_request_show_with_schedule);

	पूर्णांकel_runसमय_pm_put(&i915->runसमय_pm, wakeref);

	वापस 0;
पूर्ण

अटल पूर्णांक i915_wa_रेजिस्टरs(काष्ठा seq_file *m, व्योम *unused)
अणु
	काष्ठा drm_i915_निजी *i915 = node_to_i915(m->निजी);
	काष्ठा पूर्णांकel_engine_cs *engine;

	क्रम_each_uabi_engine(engine, i915) अणु
		स्थिर काष्ठा i915_wa_list *wal = &engine->ctx_wa_list;
		स्थिर काष्ठा i915_wa *wa;
		अचिन्हित पूर्णांक count;

		count = wal->count;
		अगर (!count)
			जारी;

		seq_म_लिखो(m, "%s: Workarounds applied: %u\n",
			   engine->name, count);

		क्रम (wa = wal->list; count--; wa++)
			seq_म_लिखो(m, "0x%X: 0x%08X, mask: 0x%08X\n",
				   i915_mmio_reg_offset(wa->reg),
				   wa->set, wa->clr);

		seq_म_लिखो(m, "\n");
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
i915_wedged_get(व्योम *data, u64 *val)
अणु
	काष्ठा drm_i915_निजी *i915 = data;
	पूर्णांक ret = पूर्णांकel_gt_terminally_wedged(&i915->gt);

	चयन (ret) अणु
	हाल -EIO:
		*val = 1;
		वापस 0;
	हाल 0:
		*val = 0;
		वापस 0;
	शेष:
		वापस ret;
	पूर्ण
पूर्ण

अटल पूर्णांक
i915_wedged_set(व्योम *data, u64 val)
अणु
	काष्ठा drm_i915_निजी *i915 = data;

	/* Flush any previous reset beक्रमe applying क्रम a new one */
	रुको_event(i915->gt.reset.queue,
		   !test_bit(I915_RESET_BACKOFF, &i915->gt.reset.flags));

	पूर्णांकel_gt_handle_error(&i915->gt, val, I915_ERROR_CAPTURE,
			      "Manually set wedged engine mask = %llx", val);
	वापस 0;
पूर्ण

DEFINE_SIMPLE_ATTRIBUTE(i915_wedged_fops,
			i915_wedged_get, i915_wedged_set,
			"%llu\n");

अटल पूर्णांक
i915_perf_noa_delay_set(व्योम *data, u64 val)
अणु
	काष्ठा drm_i915_निजी *i915 = data;

	/*
	 * This would lead to infinite रुकोs as we're करोing बारtamp
	 * dअगरference on the CS with only 32bits.
	 */
	अगर (पूर्णांकel_gt_ns_to_घड़ी_पूर्णांकerval(&i915->gt, val) > U32_MAX)
		वापस -EINVAL;

	atomic64_set(&i915->perf.noa_programming_delay, val);
	वापस 0;
पूर्ण

अटल पूर्णांक
i915_perf_noa_delay_get(व्योम *data, u64 *val)
अणु
	काष्ठा drm_i915_निजी *i915 = data;

	*val = atomic64_पढ़ो(&i915->perf.noa_programming_delay);
	वापस 0;
पूर्ण

DEFINE_SIMPLE_ATTRIBUTE(i915_perf_noa_delay_fops,
			i915_perf_noa_delay_get,
			i915_perf_noa_delay_set,
			"%llu\n");

#घोषणा DROP_UNBOUND	BIT(0)
#घोषणा DROP_BOUND	BIT(1)
#घोषणा DROP_RETIRE	BIT(2)
#घोषणा DROP_ACTIVE	BIT(3)
#घोषणा DROP_FREED	BIT(4)
#घोषणा DROP_SHRINK_ALL	BIT(5)
#घोषणा DROP_IDLE	BIT(6)
#घोषणा DROP_RESET_ACTIVE	BIT(7)
#घोषणा DROP_RESET_SEQNO	BIT(8)
#घोषणा DROP_RCU	BIT(9)
#घोषणा DROP_ALL (DROP_UNBOUND	| \
		  DROP_BOUND	| \
		  DROP_RETIRE	| \
		  DROP_ACTIVE	| \
		  DROP_FREED	| \
		  DROP_SHRINK_ALL |\
		  DROP_IDLE	| \
		  DROP_RESET_ACTIVE | \
		  DROP_RESET_SEQNO | \
		  DROP_RCU)
अटल पूर्णांक
i915_drop_caches_get(व्योम *data, u64 *val)
अणु
	*val = DROP_ALL;

	वापस 0;
पूर्ण
अटल पूर्णांक
gt_drop_caches(काष्ठा पूर्णांकel_gt *gt, u64 val)
अणु
	पूर्णांक ret;

	अगर (val & DROP_RESET_ACTIVE &&
	    रुको_क्रम(पूर्णांकel_engines_are_idle(gt), I915_IDLE_ENGINES_TIMEOUT))
		पूर्णांकel_gt_set_wedged(gt);

	अगर (val & DROP_RETIRE)
		पूर्णांकel_gt_retire_requests(gt);

	अगर (val & (DROP_IDLE | DROP_ACTIVE)) अणु
		ret = पूर्णांकel_gt_रुको_क्रम_idle(gt, MAX_SCHEDULE_TIMEOUT);
		अगर (ret)
			वापस ret;
	पूर्ण

	अगर (val & DROP_IDLE) अणु
		ret = पूर्णांकel_gt_pm_रुको_क्रम_idle(gt);
		अगर (ret)
			वापस ret;
	पूर्ण

	अगर (val & DROP_RESET_ACTIVE && पूर्णांकel_gt_terminally_wedged(gt))
		पूर्णांकel_gt_handle_error(gt, ALL_ENGINES, 0, शून्य);

	अगर (val & DROP_FREED)
		पूर्णांकel_gt_flush_buffer_pool(gt);

	वापस 0;
पूर्ण

अटल पूर्णांक
i915_drop_caches_set(व्योम *data, u64 val)
अणु
	काष्ठा drm_i915_निजी *i915 = data;
	पूर्णांक ret;

	DRM_DEBUG("Dropping caches: 0x%08llx [0x%08llx]\n",
		  val, val & DROP_ALL);

	ret = gt_drop_caches(&i915->gt, val);
	अगर (ret)
		वापस ret;

	fs_reclaim_acquire(GFP_KERNEL);
	अगर (val & DROP_BOUND)
		i915_gem_shrink(शून्य, i915, दीर्घ_उच्च, शून्य, I915_SHRINK_BOUND);

	अगर (val & DROP_UNBOUND)
		i915_gem_shrink(शून्य, i915, दीर्घ_उच्च, शून्य, I915_SHRINK_UNBOUND);

	अगर (val & DROP_SHRINK_ALL)
		i915_gem_shrink_all(i915);
	fs_reclaim_release(GFP_KERNEL);

	अगर (val & DROP_RCU)
		rcu_barrier();

	अगर (val & DROP_FREED)
		i915_gem_drain_मुक्तd_objects(i915);

	वापस 0;
पूर्ण

DEFINE_SIMPLE_ATTRIBUTE(i915_drop_caches_fops,
			i915_drop_caches_get, i915_drop_caches_set,
			"0x%08llx\n");

अटल पूर्णांक i915_sseu_status(काष्ठा seq_file *m, व्योम *unused)
अणु
	काष्ठा drm_i915_निजी *i915 = node_to_i915(m->निजी);
	काष्ठा पूर्णांकel_gt *gt = &i915->gt;

	वापस पूर्णांकel_sseu_status(m, gt);
पूर्ण

अटल पूर्णांक i915_क्रमcewake_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा drm_i915_निजी *i915 = inode->i_निजी;
	काष्ठा पूर्णांकel_gt *gt = &i915->gt;

	atomic_inc(&gt->user_wakeref);
	पूर्णांकel_gt_pm_get(gt);
	अगर (INTEL_GEN(i915) >= 6)
		पूर्णांकel_uncore_क्रमcewake_user_get(gt->uncore);

	वापस 0;
पूर्ण

अटल पूर्णांक i915_क्रमcewake_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा drm_i915_निजी *i915 = inode->i_निजी;
	काष्ठा पूर्णांकel_gt *gt = &i915->gt;

	अगर (INTEL_GEN(i915) >= 6)
		पूर्णांकel_uncore_क्रमcewake_user_put(&i915->uncore);
	पूर्णांकel_gt_pm_put(gt);
	atomic_dec(&gt->user_wakeref);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा file_operations i915_क्रमcewake_fops = अणु
	.owner = THIS_MODULE,
	.खोलो = i915_क्रमcewake_खोलो,
	.release = i915_क्रमcewake_release,
पूर्ण;

अटल स्थिर काष्ठा drm_info_list i915_debugfs_list[] = अणु
	अणु"i915_capabilities", i915_capabilities, 0पूर्ण,
	अणु"i915_gem_objects", i915_gem_object_info, 0पूर्ण,
	अणु"i915_frequency_info", i915_frequency_info, 0पूर्ण,
	अणु"i915_swizzle_info", i915_swizzle_info, 0पूर्ण,
	अणु"i915_runtime_pm_status", i915_runसमय_pm_status, 0पूर्ण,
	अणु"i915_engine_info", i915_engine_info, 0पूर्ण,
	अणु"i915_wa_registers", i915_wa_रेजिस्टरs, 0पूर्ण,
	अणु"i915_sseu_status", i915_sseu_status, 0पूर्ण,
	अणु"i915_rps_boost_info", i915_rps_boost_info, 0पूर्ण,
पूर्ण;
#घोषणा I915_DEBUGFS_ENTRIES ARRAY_SIZE(i915_debugfs_list)

अटल स्थिर काष्ठा i915_debugfs_files अणु
	स्थिर अक्षर *name;
	स्थिर काष्ठा file_operations *fops;
पूर्ण i915_debugfs_files[] = अणु
	अणु"i915_perf_noa_delay", &i915_perf_noa_delay_fopsपूर्ण,
	अणु"i915_wedged", &i915_wedged_fopsपूर्ण,
	अणु"i915_gem_drop_caches", &i915_drop_caches_fopsपूर्ण,
#अगर IS_ENABLED(CONFIG_DRM_I915_CAPTURE_ERROR)
	अणु"i915_error_state", &i915_error_state_fopsपूर्ण,
	अणु"i915_gpu_info", &i915_gpu_info_fopsपूर्ण,
#पूर्ण_अगर
पूर्ण;

व्योम i915_debugfs_रेजिस्टर(काष्ठा drm_i915_निजी *dev_priv)
अणु
	काष्ठा drm_minor *minor = dev_priv->drm.primary;
	पूर्णांक i;

	i915_debugfs_params(dev_priv);

	debugfs_create_file("i915_forcewake_user", S_IRUSR, minor->debugfs_root,
			    to_i915(minor->dev), &i915_क्रमcewake_fops);
	क्रम (i = 0; i < ARRAY_SIZE(i915_debugfs_files); i++) अणु
		debugfs_create_file(i915_debugfs_files[i].name,
				    S_IRUGO | S_IWUSR,
				    minor->debugfs_root,
				    to_i915(minor->dev),
				    i915_debugfs_files[i].fops);
	पूर्ण

	drm_debugfs_create_files(i915_debugfs_list,
				 I915_DEBUGFS_ENTRIES,
				 minor->debugfs_root, minor);
पूर्ण
