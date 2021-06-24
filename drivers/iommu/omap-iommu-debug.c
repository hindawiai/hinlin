<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * omap iommu: debugfs पूर्णांकerface
 *
 * Copyright (C) 2008-2009 Nokia Corporation
 *
 * Written by Hiroshi DOYU <Hiroshi.DOYU@nokia.com>
 */

#समावेश <linux/err.h>
#समावेश <linux/पन.स>
#समावेश <linux/slab.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/debugfs.h>
#समावेश <linux/platक्रमm_data/iommu-omap.h>

#समावेश "omap-iopgtable.h"
#समावेश "omap-iommu.h"

अटल DEFINE_MUTEX(iommu_debug_lock);

अटल काष्ठा dentry *iommu_debug_root;

अटल अंतरभूत bool is_omap_iommu_detached(काष्ठा omap_iommu *obj)
अणु
	वापस !obj->करोमुख्य;
पूर्ण

#घोषणा pr_reg(name)							\
	करो अणु								\
		sमाप_प्रकार bytes;						\
		स्थिर अक्षर *str = "%20s: %08x\n";			\
		स्थिर पूर्णांक maxcol = 32;					\
		bytes = snम_लिखो(p, maxcol, str, __stringअगरy(name),	\
				 iommu_पढ़ो_reg(obj, MMU_##name));	\
		p += bytes;						\
		len -= bytes;						\
		अगर (len < maxcol)					\
			जाओ out;					\
	पूर्ण जबतक (0)

अटल sमाप_प्रकार
omap2_iommu_dump_ctx(काष्ठा omap_iommu *obj, अक्षर *buf, sमाप_प्रकार len)
अणु
	अक्षर *p = buf;

	pr_reg(REVISION);
	pr_reg(IRQSTATUS);
	pr_reg(IRQENABLE);
	pr_reg(WALKING_ST);
	pr_reg(CNTL);
	pr_reg(FAULT_AD);
	pr_reg(TTB);
	pr_reg(LOCK);
	pr_reg(LD_TLB);
	pr_reg(CAM);
	pr_reg(RAM);
	pr_reg(GFLUSH);
	pr_reg(FLUSH_ENTRY);
	pr_reg(READ_CAM);
	pr_reg(READ_RAM);
	pr_reg(EMU_FAULT_AD);
out:
	वापस p - buf;
पूर्ण

अटल sमाप_प्रकार omap_iommu_dump_ctx(काष्ठा omap_iommu *obj, अक्षर *buf,
				   sमाप_प्रकार bytes)
अणु
	अगर (!obj || !buf)
		वापस -EINVAL;

	pm_runसमय_get_sync(obj->dev);

	bytes = omap2_iommu_dump_ctx(obj, buf, bytes);

	pm_runसमय_put_sync(obj->dev);

	वापस bytes;
पूर्ण

अटल sमाप_प्रकार debug_पढ़ो_regs(काष्ठा file *file, अक्षर __user *userbuf,
			       माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा omap_iommu *obj = file->निजी_data;
	अक्षर *p, *buf;
	sमाप_प्रकार bytes;

	अगर (is_omap_iommu_detached(obj))
		वापस -EPERM;

	buf = kदो_स्मृति(count, GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;
	p = buf;

	mutex_lock(&iommu_debug_lock);

	bytes = omap_iommu_dump_ctx(obj, p, count);
	अगर (bytes < 0)
		जाओ err;
	bytes = simple_पढ़ो_from_buffer(userbuf, count, ppos, buf, bytes);

err:
	mutex_unlock(&iommu_debug_lock);
	kमुक्त(buf);

	वापस bytes;
पूर्ण

अटल पूर्णांक
__dump_tlb_entries(काष्ठा omap_iommu *obj, काष्ठा cr_regs *crs, पूर्णांक num)
अणु
	पूर्णांक i;
	काष्ठा iotlb_lock saved;
	काष्ठा cr_regs पंचांगp;
	काष्ठा cr_regs *p = crs;

	pm_runसमय_get_sync(obj->dev);
	iotlb_lock_get(obj, &saved);

	क्रम_each_iotlb_cr(obj, num, i, पंचांगp) अणु
		अगर (!iotlb_cr_valid(&पंचांगp))
			जारी;
		*p++ = पंचांगp;
	पूर्ण

	iotlb_lock_set(obj, &saved);
	pm_runसमय_put_sync(obj->dev);

	वापस  p - crs;
पूर्ण

अटल sमाप_प्रकार iotlb_dump_cr(काष्ठा omap_iommu *obj, काष्ठा cr_regs *cr,
			     काष्ठा seq_file *s)
अणु
	seq_म_लिखो(s, "%08x %08x %01x\n", cr->cam, cr->ram,
		   (cr->cam & MMU_CAM_P) ? 1 : 0);
	वापस 0;
पूर्ण

अटल माप_प्रकार omap_dump_tlb_entries(काष्ठा omap_iommu *obj, काष्ठा seq_file *s)
अणु
	पूर्णांक i, num;
	काष्ठा cr_regs *cr;

	num = obj->nr_tlb_entries;

	cr = kसुस्मृति(num, माप(*cr), GFP_KERNEL);
	अगर (!cr)
		वापस 0;

	num = __dump_tlb_entries(obj, cr, num);
	क्रम (i = 0; i < num; i++)
		iotlb_dump_cr(obj, cr + i, s);
	kमुक्त(cr);

	वापस 0;
पूर्ण

अटल पूर्णांक tlb_show(काष्ठा seq_file *s, व्योम *data)
अणु
	काष्ठा omap_iommu *obj = s->निजी;

	अगर (is_omap_iommu_detached(obj))
		वापस -EPERM;

	mutex_lock(&iommu_debug_lock);

	seq_म_लिखो(s, "%8s %8s\n", "cam:", "ram:");
	seq_माला_दो(s, "-----------------------------------------\n");
	omap_dump_tlb_entries(obj, s);

	mutex_unlock(&iommu_debug_lock);

	वापस 0;
पूर्ण

अटल व्योम dump_ioptable(काष्ठा seq_file *s)
अणु
	पूर्णांक i, j;
	u32 da;
	u32 *iopgd, *iopte;
	काष्ठा omap_iommu *obj = s->निजी;

	spin_lock(&obj->page_table_lock);

	iopgd = iopgd_offset(obj, 0);
	क्रम (i = 0; i < PTRS_PER_IOPGD; i++, iopgd++) अणु
		अगर (!*iopgd)
			जारी;

		अगर (!(*iopgd & IOPGD_TABLE)) अणु
			da = i << IOPGD_SHIFT;
			seq_म_लिखो(s, "1: 0x%08x 0x%08x\n", da, *iopgd);
			जारी;
		पूर्ण

		iopte = iopte_offset(iopgd, 0);
		क्रम (j = 0; j < PTRS_PER_IOPTE; j++, iopte++) अणु
			अगर (!*iopte)
				जारी;

			da = (i << IOPGD_SHIFT) + (j << IOPTE_SHIFT);
			seq_म_लिखो(s, "2: 0x%08x 0x%08x\n", da, *iopte);
		पूर्ण
	पूर्ण

	spin_unlock(&obj->page_table_lock);
पूर्ण

अटल पूर्णांक pagetable_show(काष्ठा seq_file *s, व्योम *data)
अणु
	काष्ठा omap_iommu *obj = s->निजी;

	अगर (is_omap_iommu_detached(obj))
		वापस -EPERM;

	mutex_lock(&iommu_debug_lock);

	seq_म_लिखो(s, "L: %8s %8s\n", "da:", "pte:");
	seq_माला_दो(s, "--------------------------\n");
	dump_ioptable(s);

	mutex_unlock(&iommu_debug_lock);

	वापस 0;
पूर्ण

#घोषणा DEBUG_FOPS_RO(name)						\
	अटल स्थिर काष्ठा file_operations name##_fops = अणु	        \
		.खोलो = simple_खोलो,					\
		.पढ़ो = debug_पढ़ो_##name,				\
		.llseek = generic_file_llseek,				\
	पूर्ण

DEBUG_FOPS_RO(regs);
DEFINE_SHOW_ATTRIBUTE(tlb);
DEFINE_SHOW_ATTRIBUTE(pagetable);

व्योम omap_iommu_debugfs_add(काष्ठा omap_iommu *obj)
अणु
	काष्ठा dentry *d;

	अगर (!iommu_debug_root)
		वापस;

	d = debugfs_create_dir(obj->name, iommu_debug_root);
	obj->debug_dir = d;

	debugfs_create_u32("nr_tlb_entries", 0400, d, &obj->nr_tlb_entries);
	debugfs_create_file("regs", 0400, d, obj, &regs_fops);
	debugfs_create_file("tlb", 0400, d, obj, &tlb_fops);
	debugfs_create_file("pagetable", 0400, d, obj, &pagetable_fops);
पूर्ण

व्योम omap_iommu_debugfs_हटाओ(काष्ठा omap_iommu *obj)
अणु
	अगर (!obj->debug_dir)
		वापस;

	debugfs_हटाओ_recursive(obj->debug_dir);
पूर्ण

व्योम __init omap_iommu_debugfs_init(व्योम)
अणु
	iommu_debug_root = debugfs_create_dir("omap_iommu", शून्य);
पूर्ण

व्योम __निकास omap_iommu_debugfs_निकास(व्योम)
अणु
	debugfs_हटाओ(iommu_debug_root);
पूर्ण
