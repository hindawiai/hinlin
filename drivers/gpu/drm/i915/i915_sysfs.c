<शैली गुरु>
/*
 * Copyright तऊ 2012 Intel Corporation
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
 *    Ben Widawsky <ben@bwidawsk.net>
 *
 */

#समावेश <linux/device.h>
#समावेश <linux/module.h>
#समावेश <linux/स्थिति.स>
#समावेश <linux/sysfs.h>

#समावेश "gt/intel_rc6.h"
#समावेश "gt/intel_rps.h"
#समावेश "gt/sysfs_engines.h"

#समावेश "i915_drv.h"
#समावेश "i915_sysfs.h"
#समावेश "intel_pm.h"
#समावेश "intel_sideband.h"

अटल अंतरभूत काष्ठा drm_i915_निजी *kdev_minor_to_i915(काष्ठा device *kdev)
अणु
	काष्ठा drm_minor *minor = dev_get_drvdata(kdev);
	वापस to_i915(minor->dev);
पूर्ण

#अगर_घोषित CONFIG_PM
अटल u32 calc_residency(काष्ठा drm_i915_निजी *dev_priv,
			  i915_reg_t reg)
अणु
	पूर्णांकel_wakeref_t wakeref;
	u64 res = 0;

	with_पूर्णांकel_runसमय_pm(&dev_priv->runसमय_pm, wakeref)
		res = पूर्णांकel_rc6_residency_us(&dev_priv->gt.rc6, reg);

	वापस DIV_ROUND_CLOSEST_ULL(res, 1000);
पूर्ण

अटल sमाप_प्रकार
show_rc6_mask(काष्ठा device *kdev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा drm_i915_निजी *dev_priv = kdev_minor_to_i915(kdev);
	अचिन्हित पूर्णांक mask;

	mask = 0;
	अगर (HAS_RC6(dev_priv))
		mask |= BIT(0);
	अगर (HAS_RC6p(dev_priv))
		mask |= BIT(1);
	अगर (HAS_RC6pp(dev_priv))
		mask |= BIT(2);

	वापस snम_लिखो(buf, PAGE_SIZE, "%x\n", mask);
पूर्ण

अटल sमाप_प्रकार
show_rc6_ms(काष्ठा device *kdev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा drm_i915_निजी *dev_priv = kdev_minor_to_i915(kdev);
	u32 rc6_residency = calc_residency(dev_priv, GEN6_GT_GFX_RC6);
	वापस snम_लिखो(buf, PAGE_SIZE, "%u\n", rc6_residency);
पूर्ण

अटल sमाप_प्रकार
show_rc6p_ms(काष्ठा device *kdev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा drm_i915_निजी *dev_priv = kdev_minor_to_i915(kdev);
	u32 rc6p_residency = calc_residency(dev_priv, GEN6_GT_GFX_RC6p);
	वापस snम_लिखो(buf, PAGE_SIZE, "%u\n", rc6p_residency);
पूर्ण

अटल sमाप_प्रकार
show_rc6pp_ms(काष्ठा device *kdev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा drm_i915_निजी *dev_priv = kdev_minor_to_i915(kdev);
	u32 rc6pp_residency = calc_residency(dev_priv, GEN6_GT_GFX_RC6pp);
	वापस snम_लिखो(buf, PAGE_SIZE, "%u\n", rc6pp_residency);
पूर्ण

अटल sमाप_प्रकार
show_media_rc6_ms(काष्ठा device *kdev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा drm_i915_निजी *dev_priv = kdev_minor_to_i915(kdev);
	u32 rc6_residency = calc_residency(dev_priv, VLV_GT_MEDIA_RC6);
	वापस snम_लिखो(buf, PAGE_SIZE, "%u\n", rc6_residency);
पूर्ण

अटल DEVICE_ATTR(rc6_enable, S_IRUGO, show_rc6_mask, शून्य);
अटल DEVICE_ATTR(rc6_residency_ms, S_IRUGO, show_rc6_ms, शून्य);
अटल DEVICE_ATTR(rc6p_residency_ms, S_IRUGO, show_rc6p_ms, शून्य);
अटल DEVICE_ATTR(rc6pp_residency_ms, S_IRUGO, show_rc6pp_ms, शून्य);
अटल DEVICE_ATTR(media_rc6_residency_ms, S_IRUGO, show_media_rc6_ms, शून्य);

अटल काष्ठा attribute *rc6_attrs[] = अणु
	&dev_attr_rc6_enable.attr,
	&dev_attr_rc6_residency_ms.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group rc6_attr_group = अणु
	.name = घातer_group_name,
	.attrs =  rc6_attrs
पूर्ण;

अटल काष्ठा attribute *rc6p_attrs[] = अणु
	&dev_attr_rc6p_residency_ms.attr,
	&dev_attr_rc6pp_residency_ms.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group rc6p_attr_group = अणु
	.name = घातer_group_name,
	.attrs =  rc6p_attrs
पूर्ण;

अटल काष्ठा attribute *media_rc6_attrs[] = अणु
	&dev_attr_media_rc6_residency_ms.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group media_rc6_attr_group = अणु
	.name = घातer_group_name,
	.attrs =  media_rc6_attrs
पूर्ण;
#पूर्ण_अगर

अटल पूर्णांक l3_access_valid(काष्ठा drm_i915_निजी *i915, loff_t offset)
अणु
	अगर (!HAS_L3_DPF(i915))
		वापस -EPERM;

	अगर (!IS_ALIGNED(offset, माप(u32)))
		वापस -EINVAL;

	अगर (offset >= GEN7_L3LOG_SIZE)
		वापस -ENXIO;

	वापस 0;
पूर्ण

अटल sमाप_प्रकार
i915_l3_पढ़ो(काष्ठा file *filp, काष्ठा kobject *kobj,
	     काष्ठा bin_attribute *attr, अक्षर *buf,
	     loff_t offset, माप_प्रकार count)
अणु
	काष्ठा device *kdev = kobj_to_dev(kobj);
	काष्ठा drm_i915_निजी *i915 = kdev_minor_to_i915(kdev);
	पूर्णांक slice = (पूर्णांक)(uपूर्णांकptr_t)attr->निजी;
	पूर्णांक ret;

	ret = l3_access_valid(i915, offset);
	अगर (ret)
		वापस ret;

	count = round_करोwn(count, माप(u32));
	count = min_t(माप_प्रकार, GEN7_L3LOG_SIZE - offset, count);
	स_रखो(buf, 0, count);

	spin_lock(&i915->gem.contexts.lock);
	अगर (i915->l3_parity.remap_info[slice])
		स_नकल(buf,
		       i915->l3_parity.remap_info[slice] + offset / माप(u32),
		       count);
	spin_unlock(&i915->gem.contexts.lock);

	वापस count;
पूर्ण

अटल sमाप_प्रकार
i915_l3_ग_लिखो(काष्ठा file *filp, काष्ठा kobject *kobj,
	      काष्ठा bin_attribute *attr, अक्षर *buf,
	      loff_t offset, माप_प्रकार count)
अणु
	काष्ठा device *kdev = kobj_to_dev(kobj);
	काष्ठा drm_i915_निजी *i915 = kdev_minor_to_i915(kdev);
	पूर्णांक slice = (पूर्णांक)(uपूर्णांकptr_t)attr->निजी;
	u32 *remap_info, *मुक्तme = शून्य;
	काष्ठा i915_gem_context *ctx;
	पूर्णांक ret;

	ret = l3_access_valid(i915, offset);
	अगर (ret)
		वापस ret;

	अगर (count < माप(u32))
		वापस -EINVAL;

	remap_info = kzalloc(GEN7_L3LOG_SIZE, GFP_KERNEL);
	अगर (!remap_info)
		वापस -ENOMEM;

	spin_lock(&i915->gem.contexts.lock);

	अगर (i915->l3_parity.remap_info[slice]) अणु
		मुक्तme = remap_info;
		remap_info = i915->l3_parity.remap_info[slice];
	पूर्ण अन्यथा अणु
		i915->l3_parity.remap_info[slice] = remap_info;
	पूर्ण

	count = round_करोwn(count, माप(u32));
	स_नकल(remap_info + offset / माप(u32), buf, count);

	/* NB: We defer the remapping until we चयन to the context */
	list_क्रम_each_entry(ctx, &i915->gem.contexts.list, link)
		ctx->remap_slice |= BIT(slice);

	spin_unlock(&i915->gem.contexts.lock);
	kमुक्त(मुक्तme);

	/*
	 * TODO: Ideally we really want a GPU reset here to make sure errors
	 * aren't propagated. Since I cannot find a stable way to reset the GPU
	 * at this poपूर्णांक it is left as a TODO.
	*/

	वापस count;
पूर्ण

अटल स्थिर काष्ठा bin_attribute dpf_attrs = अणु
	.attr = अणु.name = "l3_parity", .mode = (S_IRUSR | S_IWUSR)पूर्ण,
	.size = GEN7_L3LOG_SIZE,
	.पढ़ो = i915_l3_पढ़ो,
	.ग_लिखो = i915_l3_ग_लिखो,
	.mmap = शून्य,
	.निजी = (व्योम *)0
पूर्ण;

अटल स्थिर काष्ठा bin_attribute dpf_attrs_1 = अणु
	.attr = अणु.name = "l3_parity_slice_1", .mode = (S_IRUSR | S_IWUSR)पूर्ण,
	.size = GEN7_L3LOG_SIZE,
	.पढ़ो = i915_l3_पढ़ो,
	.ग_लिखो = i915_l3_ग_लिखो,
	.mmap = शून्य,
	.निजी = (व्योम *)1
पूर्ण;

अटल sमाप_प्रकार gt_act_freq_mhz_show(काष्ठा device *kdev,
				    काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा drm_i915_निजी *i915 = kdev_minor_to_i915(kdev);
	काष्ठा पूर्णांकel_rps *rps = &i915->gt.rps;

	वापस snम_लिखो(buf, PAGE_SIZE, "%d\n",
			पूर्णांकel_rps_पढ़ो_actual_frequency(rps));
पूर्ण

अटल sमाप_प्रकार gt_cur_freq_mhz_show(काष्ठा device *kdev,
				    काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा drm_i915_निजी *i915 = kdev_minor_to_i915(kdev);
	काष्ठा पूर्णांकel_rps *rps = &i915->gt.rps;

	वापस snम_लिखो(buf, PAGE_SIZE, "%d\n",
			पूर्णांकel_gpu_freq(rps, rps->cur_freq));
पूर्ण

अटल sमाप_प्रकार gt_boost_freq_mhz_show(काष्ठा device *kdev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा drm_i915_निजी *i915 = kdev_minor_to_i915(kdev);
	काष्ठा पूर्णांकel_rps *rps = &i915->gt.rps;

	वापस snम_लिखो(buf, PAGE_SIZE, "%d\n",
			पूर्णांकel_gpu_freq(rps, rps->boost_freq));
पूर्ण

अटल sमाप_प्रकार gt_boost_freq_mhz_store(काष्ठा device *kdev,
				       काष्ठा device_attribute *attr,
				       स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा drm_i915_निजी *dev_priv = kdev_minor_to_i915(kdev);
	काष्ठा पूर्णांकel_rps *rps = &dev_priv->gt.rps;
	bool boost = false;
	sमाप_प्रकार ret;
	u32 val;

	ret = kstrtou32(buf, 0, &val);
	अगर (ret)
		वापस ret;

	/* Validate against (अटल) hardware limits */
	val = पूर्णांकel_freq_opcode(rps, val);
	अगर (val < rps->min_freq || val > rps->max_freq)
		वापस -EINVAL;

	mutex_lock(&rps->lock);
	अगर (val != rps->boost_freq) अणु
		rps->boost_freq = val;
		boost = atomic_पढ़ो(&rps->num_रुकोers);
	पूर्ण
	mutex_unlock(&rps->lock);
	अगर (boost)
		schedule_work(&rps->work);

	वापस count;
पूर्ण

अटल sमाप_प्रकार vlv_rpe_freq_mhz_show(काष्ठा device *kdev,
				     काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा drm_i915_निजी *dev_priv = kdev_minor_to_i915(kdev);
	काष्ठा पूर्णांकel_rps *rps = &dev_priv->gt.rps;

	वापस snम_लिखो(buf, PAGE_SIZE, "%d\n",
			पूर्णांकel_gpu_freq(rps, rps->efficient_freq));
पूर्ण

अटल sमाप_प्रकार gt_max_freq_mhz_show(काष्ठा device *kdev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा drm_i915_निजी *dev_priv = kdev_minor_to_i915(kdev);
	काष्ठा पूर्णांकel_rps *rps = &dev_priv->gt.rps;

	वापस snम_लिखो(buf, PAGE_SIZE, "%d\n",
			पूर्णांकel_gpu_freq(rps, rps->max_freq_softlimit));
पूर्ण

अटल sमाप_प्रकार gt_max_freq_mhz_store(काष्ठा device *kdev,
				     काष्ठा device_attribute *attr,
				     स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा drm_i915_निजी *dev_priv = kdev_minor_to_i915(kdev);
	काष्ठा पूर्णांकel_rps *rps = &dev_priv->gt.rps;
	sमाप_प्रकार ret;
	u32 val;

	ret = kstrtou32(buf, 0, &val);
	अगर (ret)
		वापस ret;

	mutex_lock(&rps->lock);

	val = पूर्णांकel_freq_opcode(rps, val);
	अगर (val < rps->min_freq ||
	    val > rps->max_freq ||
	    val < rps->min_freq_softlimit) अणु
		ret = -EINVAL;
		जाओ unlock;
	पूर्ण

	अगर (val > rps->rp0_freq)
		DRM_DEBUG("User requested overclocking to %d\n",
			  पूर्णांकel_gpu_freq(rps, val));

	rps->max_freq_softlimit = val;

	val = clamp_t(पूर्णांक, rps->cur_freq,
		      rps->min_freq_softlimit,
		      rps->max_freq_softlimit);

	/*
	 * We still need *_set_rps to process the new max_delay and
	 * update the पूर्णांकerrupt limits and PMINTRMSK even though
	 * frequency request may be unchanged.
	 */
	पूर्णांकel_rps_set(rps, val);

unlock:
	mutex_unlock(&rps->lock);

	वापस ret ?: count;
पूर्ण

अटल sमाप_प्रकार gt_min_freq_mhz_show(काष्ठा device *kdev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा drm_i915_निजी *dev_priv = kdev_minor_to_i915(kdev);
	काष्ठा पूर्णांकel_rps *rps = &dev_priv->gt.rps;

	वापस snम_लिखो(buf, PAGE_SIZE, "%d\n",
			पूर्णांकel_gpu_freq(rps, rps->min_freq_softlimit));
पूर्ण

अटल sमाप_प्रकार gt_min_freq_mhz_store(काष्ठा device *kdev,
				     काष्ठा device_attribute *attr,
				     स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा drm_i915_निजी *dev_priv = kdev_minor_to_i915(kdev);
	काष्ठा पूर्णांकel_rps *rps = &dev_priv->gt.rps;
	sमाप_प्रकार ret;
	u32 val;

	ret = kstrtou32(buf, 0, &val);
	अगर (ret)
		वापस ret;

	mutex_lock(&rps->lock);

	val = पूर्णांकel_freq_opcode(rps, val);
	अगर (val < rps->min_freq ||
	    val > rps->max_freq ||
	    val > rps->max_freq_softlimit) अणु
		ret = -EINVAL;
		जाओ unlock;
	पूर्ण

	rps->min_freq_softlimit = val;

	val = clamp_t(पूर्णांक, rps->cur_freq,
		      rps->min_freq_softlimit,
		      rps->max_freq_softlimit);

	/*
	 * We still need *_set_rps to process the new min_delay and
	 * update the पूर्णांकerrupt limits and PMINTRMSK even though
	 * frequency request may be unchanged.
	 */
	पूर्णांकel_rps_set(rps, val);

unlock:
	mutex_unlock(&rps->lock);

	वापस ret ?: count;
पूर्ण

अटल DEVICE_ATTR_RO(gt_act_freq_mhz);
अटल DEVICE_ATTR_RO(gt_cur_freq_mhz);
अटल DEVICE_ATTR_RW(gt_boost_freq_mhz);
अटल DEVICE_ATTR_RW(gt_max_freq_mhz);
अटल DEVICE_ATTR_RW(gt_min_freq_mhz);

अटल DEVICE_ATTR_RO(vlv_rpe_freq_mhz);

अटल sमाप_प्रकार gt_rp_mhz_show(काष्ठा device *kdev, काष्ठा device_attribute *attr, अक्षर *buf);
अटल DEVICE_ATTR(gt_RP0_freq_mhz, S_IRUGO, gt_rp_mhz_show, शून्य);
अटल DEVICE_ATTR(gt_RP1_freq_mhz, S_IRUGO, gt_rp_mhz_show, शून्य);
अटल DEVICE_ATTR(gt_RPn_freq_mhz, S_IRUGO, gt_rp_mhz_show, शून्य);

/* For now we have a अटल number of RP states */
अटल sमाप_प्रकार gt_rp_mhz_show(काष्ठा device *kdev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा drm_i915_निजी *dev_priv = kdev_minor_to_i915(kdev);
	काष्ठा पूर्णांकel_rps *rps = &dev_priv->gt.rps;
	u32 val;

	अगर (attr == &dev_attr_gt_RP0_freq_mhz)
		val = पूर्णांकel_gpu_freq(rps, rps->rp0_freq);
	अन्यथा अगर (attr == &dev_attr_gt_RP1_freq_mhz)
		val = पूर्णांकel_gpu_freq(rps, rps->rp1_freq);
	अन्यथा अगर (attr == &dev_attr_gt_RPn_freq_mhz)
		val = पूर्णांकel_gpu_freq(rps, rps->min_freq);
	अन्यथा
		BUG();

	वापस snम_लिखो(buf, PAGE_SIZE, "%d\n", val);
पूर्ण

अटल स्थिर काष्ठा attribute * स्थिर gen6_attrs[] = अणु
	&dev_attr_gt_act_freq_mhz.attr,
	&dev_attr_gt_cur_freq_mhz.attr,
	&dev_attr_gt_boost_freq_mhz.attr,
	&dev_attr_gt_max_freq_mhz.attr,
	&dev_attr_gt_min_freq_mhz.attr,
	&dev_attr_gt_RP0_freq_mhz.attr,
	&dev_attr_gt_RP1_freq_mhz.attr,
	&dev_attr_gt_RPn_freq_mhz.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute * स्थिर vlv_attrs[] = अणु
	&dev_attr_gt_act_freq_mhz.attr,
	&dev_attr_gt_cur_freq_mhz.attr,
	&dev_attr_gt_boost_freq_mhz.attr,
	&dev_attr_gt_max_freq_mhz.attr,
	&dev_attr_gt_min_freq_mhz.attr,
	&dev_attr_gt_RP0_freq_mhz.attr,
	&dev_attr_gt_RP1_freq_mhz.attr,
	&dev_attr_gt_RPn_freq_mhz.attr,
	&dev_attr_vlv_rpe_freq_mhz.attr,
	शून्य,
पूर्ण;

#अगर IS_ENABLED(CONFIG_DRM_I915_CAPTURE_ERROR)

अटल sमाप_प्रकार error_state_पढ़ो(काष्ठा file *filp, काष्ठा kobject *kobj,
				काष्ठा bin_attribute *attr, अक्षर *buf,
				loff_t off, माप_प्रकार count)
अणु

	काष्ठा device *kdev = kobj_to_dev(kobj);
	काष्ठा drm_i915_निजी *i915 = kdev_minor_to_i915(kdev);
	काष्ठा i915_gpu_coredump *gpu;
	sमाप_प्रकार ret;

	gpu = i915_first_error_state(i915);
	अगर (IS_ERR(gpu)) अणु
		ret = PTR_ERR(gpu);
	पूर्ण अन्यथा अगर (gpu) अणु
		ret = i915_gpu_coredump_copy_to_buffer(gpu, buf, off, count);
		i915_gpu_coredump_put(gpu);
	पूर्ण अन्यथा अणु
		स्थिर अक्षर *str = "No error state collected\n";
		माप_प्रकार len = म_माप(str);

		ret = min_t(माप_प्रकार, count, len - off);
		स_नकल(buf, str + off, ret);
	पूर्ण

	वापस ret;
पूर्ण

अटल sमाप_प्रकार error_state_ग_लिखो(काष्ठा file *file, काष्ठा kobject *kobj,
				 काष्ठा bin_attribute *attr, अक्षर *buf,
				 loff_t off, माप_प्रकार count)
अणु
	काष्ठा device *kdev = kobj_to_dev(kobj);
	काष्ठा drm_i915_निजी *dev_priv = kdev_minor_to_i915(kdev);

	drm_dbg(&dev_priv->drm, "Resetting error state\n");
	i915_reset_error_state(dev_priv);

	वापस count;
पूर्ण

अटल स्थिर काष्ठा bin_attribute error_state_attr = अणु
	.attr.name = "error",
	.attr.mode = S_IRUSR | S_IWUSR,
	.size = 0,
	.पढ़ो = error_state_पढ़ो,
	.ग_लिखो = error_state_ग_लिखो,
पूर्ण;

अटल व्योम i915_setup_error_capture(काष्ठा device *kdev)
अणु
	अगर (sysfs_create_bin_file(&kdev->kobj, &error_state_attr))
		DRM_ERROR("error_state sysfs setup failed\n");
पूर्ण

अटल व्योम i915_tearकरोwn_error_capture(काष्ठा device *kdev)
अणु
	sysfs_हटाओ_bin_file(&kdev->kobj, &error_state_attr);
पूर्ण
#अन्यथा
अटल व्योम i915_setup_error_capture(काष्ठा device *kdev) अणुपूर्ण
अटल व्योम i915_tearकरोwn_error_capture(काष्ठा device *kdev) अणुपूर्ण
#पूर्ण_अगर

व्योम i915_setup_sysfs(काष्ठा drm_i915_निजी *dev_priv)
अणु
	काष्ठा device *kdev = dev_priv->drm.primary->kdev;
	पूर्णांक ret;

#अगर_घोषित CONFIG_PM
	अगर (HAS_RC6(dev_priv)) अणु
		ret = sysfs_merge_group(&kdev->kobj,
					&rc6_attr_group);
		अगर (ret)
			drm_err(&dev_priv->drm,
				"RC6 residency sysfs setup failed\n");
	पूर्ण
	अगर (HAS_RC6p(dev_priv)) अणु
		ret = sysfs_merge_group(&kdev->kobj,
					&rc6p_attr_group);
		अगर (ret)
			drm_err(&dev_priv->drm,
				"RC6p residency sysfs setup failed\n");
	पूर्ण
	अगर (IS_VALLEYVIEW(dev_priv) || IS_CHERRYVIEW(dev_priv)) अणु
		ret = sysfs_merge_group(&kdev->kobj,
					&media_rc6_attr_group);
		अगर (ret)
			drm_err(&dev_priv->drm,
				"Media RC6 residency sysfs setup failed\n");
	पूर्ण
#पूर्ण_अगर
	अगर (HAS_L3_DPF(dev_priv)) अणु
		ret = device_create_bin_file(kdev, &dpf_attrs);
		अगर (ret)
			drm_err(&dev_priv->drm,
				"l3 parity sysfs setup failed\n");

		अगर (NUM_L3_SLICES(dev_priv) > 1) अणु
			ret = device_create_bin_file(kdev,
						     &dpf_attrs_1);
			अगर (ret)
				drm_err(&dev_priv->drm,
					"l3 parity slice 1 setup failed\n");
		पूर्ण
	पूर्ण

	ret = 0;
	अगर (IS_VALLEYVIEW(dev_priv) || IS_CHERRYVIEW(dev_priv))
		ret = sysfs_create_files(&kdev->kobj, vlv_attrs);
	अन्यथा अगर (INTEL_GEN(dev_priv) >= 6)
		ret = sysfs_create_files(&kdev->kobj, gen6_attrs);
	अगर (ret)
		drm_err(&dev_priv->drm, "RPS sysfs setup failed\n");

	i915_setup_error_capture(kdev);

	पूर्णांकel_engines_add_sysfs(dev_priv);
पूर्ण

व्योम i915_tearकरोwn_sysfs(काष्ठा drm_i915_निजी *dev_priv)
अणु
	काष्ठा device *kdev = dev_priv->drm.primary->kdev;

	i915_tearकरोwn_error_capture(kdev);

	अगर (IS_VALLEYVIEW(dev_priv) || IS_CHERRYVIEW(dev_priv))
		sysfs_हटाओ_files(&kdev->kobj, vlv_attrs);
	अन्यथा
		sysfs_हटाओ_files(&kdev->kobj, gen6_attrs);
	device_हटाओ_bin_file(kdev,  &dpf_attrs_1);
	device_हटाओ_bin_file(kdev,  &dpf_attrs);
#अगर_घोषित CONFIG_PM
	sysfs_unmerge_group(&kdev->kobj, &rc6_attr_group);
	sysfs_unmerge_group(&kdev->kobj, &rc6p_attr_group);
#पूर्ण_अगर
पूर्ण
