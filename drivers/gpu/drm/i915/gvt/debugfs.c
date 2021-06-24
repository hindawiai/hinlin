<शैली गुरु>
/*
 * Copyright(c) 2011-2017 Intel Corporation. All rights reserved.
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
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
#समावेश <linux/debugfs.h>
#समावेश <linux/list_sort.h>
#समावेश "i915_drv.h"
#समावेश "gvt.h"

काष्ठा mmio_dअगरf_param अणु
	काष्ठा पूर्णांकel_vgpu *vgpu;
	पूर्णांक total;
	पूर्णांक dअगरf;
	काष्ठा list_head dअगरf_mmio_list;
पूर्ण;

काष्ठा dअगरf_mmio अणु
	काष्ठा list_head node;
	u32 offset;
	u32 preg;
	u32 vreg;
पूर्ण;

/* Compare two dअगरf_mmio items. */
अटल पूर्णांक mmio_offset_compare(व्योम *priv,
	स्थिर काष्ठा list_head *a, स्थिर काष्ठा list_head *b)
अणु
	काष्ठा dअगरf_mmio *ma;
	काष्ठा dअगरf_mmio *mb;

	ma = container_of(a, काष्ठा dअगरf_mmio, node);
	mb = container_of(b, काष्ठा dअगरf_mmio, node);
	अगर (ma->offset < mb->offset)
		वापस -1;
	अन्यथा अगर (ma->offset > mb->offset)
		वापस 1;
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक mmio_dअगरf_handler(काष्ठा पूर्णांकel_gvt *gvt,
				    u32 offset, व्योम *data)
अणु
	काष्ठा mmio_dअगरf_param *param = data;
	काष्ठा dअगरf_mmio *node;
	u32 preg, vreg;

	preg = पूर्णांकel_uncore_पढ़ो_notrace(gvt->gt->uncore, _MMIO(offset));
	vreg = vgpu_vreg(param->vgpu, offset);

	अगर (preg != vreg) अणु
		node = kदो_स्मृति(माप(*node), GFP_ATOMIC);
		अगर (!node)
			वापस -ENOMEM;

		node->offset = offset;
		node->preg = preg;
		node->vreg = vreg;
		list_add(&node->node, &param->dअगरf_mmio_list);
		param->dअगरf++;
	पूर्ण
	param->total++;
	वापस 0;
पूर्ण

/* Show the all the dअगरferent values of tracked mmio. */
अटल पूर्णांक vgpu_mmio_dअगरf_show(काष्ठा seq_file *s, व्योम *unused)
अणु
	काष्ठा पूर्णांकel_vgpu *vgpu = s->निजी;
	काष्ठा पूर्णांकel_gvt *gvt = vgpu->gvt;
	काष्ठा mmio_dअगरf_param param = अणु
		.vgpu = vgpu,
		.total = 0,
		.dअगरf = 0,
	पूर्ण;
	काष्ठा dअगरf_mmio *node, *next;

	INIT_LIST_HEAD(&param.dअगरf_mmio_list);

	mutex_lock(&gvt->lock);
	spin_lock_bh(&gvt->scheduler.mmio_context_lock);

	mmio_hw_access_pre(gvt->gt);
	/* Recognize all the dअगरf mmios to list. */
	पूर्णांकel_gvt_क्रम_each_tracked_mmio(gvt, mmio_dअगरf_handler, &param);
	mmio_hw_access_post(gvt->gt);

	spin_unlock_bh(&gvt->scheduler.mmio_context_lock);
	mutex_unlock(&gvt->lock);

	/* In an ascending order by mmio offset. */
	list_sort(शून्य, &param.dअगरf_mmio_list, mmio_offset_compare);

	seq_म_लिखो(s, "%-8s %-8s %-8s %-8s\n", "Offset", "HW", "vGPU", "Diff");
	list_क्रम_each_entry_safe(node, next, &param.dअगरf_mmio_list, node) अणु
		u32 dअगरf = node->preg ^ node->vreg;

		seq_म_लिखो(s, "%08x %08x %08x %*pbl\n",
			   node->offset, node->preg, node->vreg,
			   32, &dअगरf);
		list_del(&node->node);
		kमुक्त(node);
	पूर्ण
	seq_म_लिखो(s, "Total: %d, Diff: %d\n", param.total, param.dअगरf);
	वापस 0;
पूर्ण
DEFINE_SHOW_ATTRIBUTE(vgpu_mmio_dअगरf);

अटल पूर्णांक
vgpu_scan_nonprivbb_get(व्योम *data, u64 *val)
अणु
	काष्ठा पूर्णांकel_vgpu *vgpu = (काष्ठा पूर्णांकel_vgpu *)data;

	*val = vgpu->scan_nonprivbb;
	वापस 0;
पूर्ण

/*
 * set/unset bit engine_id of vgpu->scan_nonprivbb to turn on/off scanning
 * of non-privileged batch buffer. e.g.
 * अगर vgpu->scan_nonprivbb=3, then it will scan non-privileged batch buffer
 * on engine 0 and 1.
 */
अटल पूर्णांक
vgpu_scan_nonprivbb_set(व्योम *data, u64 val)
अणु
	काष्ठा पूर्णांकel_vgpu *vgpu = (काष्ठा पूर्णांकel_vgpu *)data;

	vgpu->scan_nonprivbb = val;
	वापस 0;
पूर्ण

DEFINE_SIMPLE_ATTRIBUTE(vgpu_scan_nonprivbb_fops,
			vgpu_scan_nonprivbb_get, vgpu_scan_nonprivbb_set,
			"0x%llx\n");

/**
 * पूर्णांकel_gvt_debugfs_add_vgpu - रेजिस्टर debugfs entries क्रम a vGPU
 * @vgpu: a vGPU
 */
व्योम पूर्णांकel_gvt_debugfs_add_vgpu(काष्ठा पूर्णांकel_vgpu *vgpu)
अणु
	अक्षर name[16] = "";

	snम_लिखो(name, 16, "vgpu%d", vgpu->id);
	vgpu->debugfs = debugfs_create_dir(name, vgpu->gvt->debugfs_root);

	debugfs_create_bool("active", 0444, vgpu->debugfs, &vgpu->active);
	debugfs_create_file("mmio_diff", 0444, vgpu->debugfs, vgpu,
			    &vgpu_mmio_dअगरf_fops);
	debugfs_create_file("scan_nonprivbb", 0644, vgpu->debugfs, vgpu,
			    &vgpu_scan_nonprivbb_fops);
पूर्ण

/**
 * पूर्णांकel_gvt_debugfs_हटाओ_vgpu - हटाओ debugfs entries of a vGPU
 * @vgpu: a vGPU
 */
व्योम पूर्णांकel_gvt_debugfs_हटाओ_vgpu(काष्ठा पूर्णांकel_vgpu *vgpu)
अणु
	debugfs_हटाओ_recursive(vgpu->debugfs);
	vgpu->debugfs = शून्य;
पूर्ण

/**
 * पूर्णांकel_gvt_debugfs_init - रेजिस्टर gvt debugfs root entry
 * @gvt: GVT device
 */
व्योम पूर्णांकel_gvt_debugfs_init(काष्ठा पूर्णांकel_gvt *gvt)
अणु
	काष्ठा drm_minor *minor = gvt->gt->i915->drm.primary;

	gvt->debugfs_root = debugfs_create_dir("gvt", minor->debugfs_root);

	debugfs_create_uदीर्घ("num_tracked_mmio", 0444, gvt->debugfs_root,
			     &gvt->mmio.num_tracked_mmio);
पूर्ण

/**
 * पूर्णांकel_gvt_debugfs_clean - हटाओ debugfs entries
 * @gvt: GVT device
 */
व्योम पूर्णांकel_gvt_debugfs_clean(काष्ठा पूर्णांकel_gvt *gvt)
अणु
	debugfs_हटाओ_recursive(gvt->debugfs_root);
	gvt->debugfs_root = शून्य;
पूर्ण
