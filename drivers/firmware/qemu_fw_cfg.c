<शैली गुरु>
/*
 * drivers/firmware/qemu_fw_cfg.c
 *
 * Copyright 2015 Carnegie Mellon University
 *
 * Expose entries from QEMU's firmware configuration (fw_cfg) device in
 * sysfs (पढ़ो-only, under "/sys/firmware/qemu_fw_cfg/...").
 *
 * The fw_cfg device may be instantiated via either an ACPI node (on x86
 * and select subsets of aarch64), a Device Tree node (on arm), or using
 * a kernel module (or command line) parameter with the following syntax:
 *
 *      [qemu_fw_cfg.]ioport=<size>@<base>[:<ctrl_off>:<data_off>[:<dma_off>]]
 * or
 *      [qemu_fw_cfg.]mmio=<size>@<base>[:<ctrl_off>:<data_off>[:<dma_off>]]
 *
 * where:
 *      <size>     := size of ioport or mmio range
 *      <base>     := physical base address of ioport or mmio range
 *      <ctrl_off> := (optional) offset of control रेजिस्टर
 *      <data_off> := (optional) offset of data रेजिस्टर
 *      <dma_off> := (optional) offset of dma रेजिस्टर
 *
 * e.g.:
 *      qemu_fw_cfg.ioport=12@0x510:0:1:4	(the शेष on x86)
 * or
 *      qemu_fw_cfg.mmio=16@0x9020000:8:0:16	(the शेष on arm)
 */

#समावेश <linux/module.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/acpi.h>
#समावेश <linux/slab.h>
#समावेश <linux/पन.स>
#समावेश <linux/ioport.h>
#समावेश <uapi/linux/qemu_fw_cfg.h>
#समावेश <linux/delay.h>
#समावेश <linux/crash_dump.h>
#समावेश <linux/crash_core.h>

MODULE_AUTHOR("Gabriel L. Somlo <somlo@cmu.edu>");
MODULE_DESCRIPTION("QEMU fw_cfg sysfs support");
MODULE_LICENSE("GPL");

/* fw_cfg revision attribute, in /sys/firmware/qemu_fw_cfg top-level dir. */
अटल u32 fw_cfg_rev;

/* fw_cfg device i/o रेजिस्टर addresses */
अटल bool fw_cfg_is_mmio;
अटल phys_addr_t fw_cfg_p_base;
अटल resource_माप_प्रकार fw_cfg_p_size;
अटल व्योम __iomem *fw_cfg_dev_base;
अटल व्योम __iomem *fw_cfg_reg_ctrl;
अटल व्योम __iomem *fw_cfg_reg_data;
अटल व्योम __iomem *fw_cfg_reg_dma;

/* atomic access to fw_cfg device (potentially slow i/o, so using mutex) */
अटल DEFINE_MUTEX(fw_cfg_dev_lock);

/* pick appropriate endianness क्रम selector key */
अटल व्योम fw_cfg_sel_endianness(u16 key)
अणु
	अगर (fw_cfg_is_mmio)
		ioग_लिखो16be(key, fw_cfg_reg_ctrl);
	अन्यथा
		ioग_लिखो16(key, fw_cfg_reg_ctrl);
पूर्ण

#अगर_घोषित CONFIG_CRASH_CORE
अटल अंतरभूत bool fw_cfg_dma_enabled(व्योम)
अणु
	वापस (fw_cfg_rev & FW_CFG_VERSION_DMA) && fw_cfg_reg_dma;
पूर्ण

/* qemu fw_cfg device is sync today, but spec says it may become async */
अटल व्योम fw_cfg_रुको_क्रम_control(काष्ठा fw_cfg_dma_access *d)
अणु
	क्रम (;;) अणु
		u32 ctrl = be32_to_cpu(READ_ONCE(d->control));

		/* करो not reorder the पढ़ो to d->control */
		rmb();
		अगर ((ctrl & ~FW_CFG_DMA_CTL_ERROR) == 0)
			वापस;

		cpu_relax();
	पूर्ण
पूर्ण

अटल sमाप_प्रकार fw_cfg_dma_transfer(व्योम *address, u32 length, u32 control)
अणु
	phys_addr_t dma;
	काष्ठा fw_cfg_dma_access *d = शून्य;
	sमाप_प्रकार ret = length;

	d = kदो_स्मृति(माप(*d), GFP_KERNEL);
	अगर (!d) अणु
		ret = -ENOMEM;
		जाओ end;
	पूर्ण

	/* fw_cfg device करोes not need IOMMU protection, so use physical addresses */
	*d = (काष्ठा fw_cfg_dma_access) अणु
		.address = cpu_to_be64(address ? virt_to_phys(address) : 0),
		.length = cpu_to_be32(length),
		.control = cpu_to_be32(control)
	पूर्ण;

	dma = virt_to_phys(d);

	ioग_लिखो32be((u64)dma >> 32, fw_cfg_reg_dma);
	/* क्रमce memory to sync beक्रमe notअगरying device via MMIO */
	wmb();
	ioग_लिखो32be(dma, fw_cfg_reg_dma + 4);

	fw_cfg_रुको_क्रम_control(d);

	अगर (be32_to_cpu(READ_ONCE(d->control)) & FW_CFG_DMA_CTL_ERROR) अणु
		ret = -EIO;
	पूर्ण

end:
	kमुक्त(d);

	वापस ret;
पूर्ण
#पूर्ण_अगर

/* पढ़ो chunk of given fw_cfg blob (caller responsible क्रम sanity-check) */
अटल sमाप_प्रकार fw_cfg_पढ़ो_blob(u16 key,
				व्योम *buf, loff_t pos, माप_प्रकार count)
अणु
	u32 glk = -1U;
	acpi_status status;

	/* If we have ACPI, ensure mutual exclusion against any potential
	 * device access by the firmware, e.g. via AML methods:
	 */
	status = acpi_acquire_global_lock(ACPI_WAIT_FOREVER, &glk);
	अगर (ACPI_FAILURE(status) && status != AE_NOT_CONFIGURED) अणु
		/* Should never get here */
		WARN(1, "fw_cfg_read_blob: Failed to lock ACPI!\n");
		स_रखो(buf, 0, count);
		वापस -EINVAL;
	पूर्ण

	mutex_lock(&fw_cfg_dev_lock);
	fw_cfg_sel_endianness(key);
	जबतक (pos-- > 0)
		ioपढ़ो8(fw_cfg_reg_data);
	ioपढ़ो8_rep(fw_cfg_reg_data, buf, count);
	mutex_unlock(&fw_cfg_dev_lock);

	acpi_release_global_lock(glk);
	वापस count;
पूर्ण

#अगर_घोषित CONFIG_CRASH_CORE
/* ग_लिखो chunk of given fw_cfg blob (caller responsible क्रम sanity-check) */
अटल sमाप_प्रकार fw_cfg_ग_लिखो_blob(u16 key,
				 व्योम *buf, loff_t pos, माप_प्रकार count)
अणु
	u32 glk = -1U;
	acpi_status status;
	sमाप_प्रकार ret = count;

	/* If we have ACPI, ensure mutual exclusion against any potential
	 * device access by the firmware, e.g. via AML methods:
	 */
	status = acpi_acquire_global_lock(ACPI_WAIT_FOREVER, &glk);
	अगर (ACPI_FAILURE(status) && status != AE_NOT_CONFIGURED) अणु
		/* Should never get here */
		WARN(1, "%s: Failed to lock ACPI!\n", __func__);
		वापस -EINVAL;
	पूर्ण

	mutex_lock(&fw_cfg_dev_lock);
	अगर (pos == 0) अणु
		ret = fw_cfg_dma_transfer(buf, count, key << 16
					  | FW_CFG_DMA_CTL_SELECT
					  | FW_CFG_DMA_CTL_WRITE);
	पूर्ण अन्यथा अणु
		fw_cfg_sel_endianness(key);
		ret = fw_cfg_dma_transfer(शून्य, pos, FW_CFG_DMA_CTL_SKIP);
		अगर (ret < 0)
			जाओ end;
		ret = fw_cfg_dma_transfer(buf, count, FW_CFG_DMA_CTL_WRITE);
	पूर्ण

end:
	mutex_unlock(&fw_cfg_dev_lock);

	acpi_release_global_lock(glk);

	वापस ret;
पूर्ण
#पूर्ण_अगर /* CONFIG_CRASH_CORE */

/* clean up fw_cfg device i/o */
अटल व्योम fw_cfg_io_cleanup(व्योम)
अणु
	अगर (fw_cfg_is_mmio) अणु
		iounmap(fw_cfg_dev_base);
		release_mem_region(fw_cfg_p_base, fw_cfg_p_size);
	पूर्ण अन्यथा अणु
		ioport_unmap(fw_cfg_dev_base);
		release_region(fw_cfg_p_base, fw_cfg_p_size);
	पूर्ण
पूर्ण

/* arch-specअगरic ctrl & data रेजिस्टर offsets are not available in ACPI, DT */
#अगर !(defined(FW_CFG_CTRL_OFF) && defined(FW_CFG_DATA_OFF))
# अगर (defined(CONFIG_ARM) || defined(CONFIG_ARM64))
#  define FW_CFG_CTRL_OFF 0x08
#  define FW_CFG_DATA_OFF 0x00
#  define FW_CFG_DMA_OFF 0x10
# elअगर defined(CONFIG_PARISC)	/* parisc */
#  define FW_CFG_CTRL_OFF 0x00
#  define FW_CFG_DATA_OFF 0x04
# elअगर (defined(CONFIG_PPC_PMAC) || defined(CONFIG_SPARC32)) /* ppc/mac,sun4m */
#  define FW_CFG_CTRL_OFF 0x00
#  define FW_CFG_DATA_OFF 0x02
# elअगर (defined(CONFIG_X86) || defined(CONFIG_SPARC64)) /* x86, sun4u */
#  define FW_CFG_CTRL_OFF 0x00
#  define FW_CFG_DATA_OFF 0x01
#  define FW_CFG_DMA_OFF 0x04
# अन्यथा
#  error "QEMU FW_CFG not available on this architecture!"
# endअगर
#पूर्ण_अगर

/* initialize fw_cfg device i/o from platक्रमm data */
अटल पूर्णांक fw_cfg_करो_platक्रमm_probe(काष्ठा platक्रमm_device *pdev)
अणु
	अक्षर sig[FW_CFG_SIG_SIZE];
	काष्ठा resource *range, *ctrl, *data, *dma;

	/* acquire i/o range details */
	fw_cfg_is_mmio = false;
	range = platक्रमm_get_resource(pdev, IORESOURCE_IO, 0);
	अगर (!range) अणु
		fw_cfg_is_mmio = true;
		range = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
		अगर (!range)
			वापस -EINVAL;
	पूर्ण
	fw_cfg_p_base = range->start;
	fw_cfg_p_size = resource_size(range);

	अगर (fw_cfg_is_mmio) अणु
		अगर (!request_mem_region(fw_cfg_p_base,
					fw_cfg_p_size, "fw_cfg_mem"))
			वापस -EBUSY;
		fw_cfg_dev_base = ioremap(fw_cfg_p_base, fw_cfg_p_size);
		अगर (!fw_cfg_dev_base) अणु
			release_mem_region(fw_cfg_p_base, fw_cfg_p_size);
			वापस -EFAULT;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (!request_region(fw_cfg_p_base,
				    fw_cfg_p_size, "fw_cfg_io"))
			वापस -EBUSY;
		fw_cfg_dev_base = ioport_map(fw_cfg_p_base, fw_cfg_p_size);
		अगर (!fw_cfg_dev_base) अणु
			release_region(fw_cfg_p_base, fw_cfg_p_size);
			वापस -EFAULT;
		पूर्ण
	पूर्ण

	/* were custom रेजिस्टर offsets provided (e.g. on the command line)? */
	ctrl = platक्रमm_get_resource_byname(pdev, IORESOURCE_REG, "ctrl");
	data = platक्रमm_get_resource_byname(pdev, IORESOURCE_REG, "data");
	dma = platक्रमm_get_resource_byname(pdev, IORESOURCE_REG, "dma");
	अगर (ctrl && data) अणु
		fw_cfg_reg_ctrl = fw_cfg_dev_base + ctrl->start;
		fw_cfg_reg_data = fw_cfg_dev_base + data->start;
	पूर्ण अन्यथा अणु
		/* use architecture-specअगरic offsets */
		fw_cfg_reg_ctrl = fw_cfg_dev_base + FW_CFG_CTRL_OFF;
		fw_cfg_reg_data = fw_cfg_dev_base + FW_CFG_DATA_OFF;
	पूर्ण

	अगर (dma)
		fw_cfg_reg_dma = fw_cfg_dev_base + dma->start;
#अगर_घोषित FW_CFG_DMA_OFF
	अन्यथा
		fw_cfg_reg_dma = fw_cfg_dev_base + FW_CFG_DMA_OFF;
#पूर्ण_अगर

	/* verअगरy fw_cfg device signature */
	अगर (fw_cfg_पढ़ो_blob(FW_CFG_SIGNATURE, sig,
				0, FW_CFG_SIG_SIZE) < 0 ||
		स_भेद(sig, "QEMU", FW_CFG_SIG_SIZE) != 0) अणु
		fw_cfg_io_cleanup();
		वापस -ENODEV;
	पूर्ण

	वापस 0;
पूर्ण

अटल sमाप_प्रकार fw_cfg_showrev(काष्ठा kobject *k, काष्ठा attribute *a, अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "%u\n", fw_cfg_rev);
पूर्ण

अटल स्थिर काष्ठा अणु
	काष्ठा attribute attr;
	sमाप_प्रकार (*show)(काष्ठा kobject *k, काष्ठा attribute *a, अक्षर *buf);
पूर्ण fw_cfg_rev_attr = अणु
	.attr = अणु .name = "rev", .mode = S_IRUSR पूर्ण,
	.show = fw_cfg_showrev,
पूर्ण;

/* fw_cfg_sysfs_entry type */
काष्ठा fw_cfg_sysfs_entry अणु
	काष्ठा kobject kobj;
	u32 size;
	u16 select;
	अक्षर name[FW_CFG_MAX_खाता_PATH];
	काष्ठा list_head list;
पूर्ण;

#अगर_घोषित CONFIG_CRASH_CORE
अटल sमाप_प्रकार fw_cfg_ग_लिखो_vmcoreinfo(स्थिर काष्ठा fw_cfg_file *f)
अणु
	अटल काष्ठा fw_cfg_vmcoreinfo *data;
	sमाप_प्रकार ret;

	data = kदो_स्मृति(माप(काष्ठा fw_cfg_vmcoreinfo), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	*data = (काष्ठा fw_cfg_vmcoreinfo) अणु
		.guest_क्रमmat = cpu_to_le16(FW_CFG_VMCOREINFO_FORMAT_ELF),
		.size = cpu_to_le32(VMCOREINFO_NOTE_SIZE),
		.paddr = cpu_to_le64(paddr_vmcoreinfo_note())
	पूर्ण;
	/* spare ourself पढ़ोing host क्रमmat support क्रम now since we
	 * करोn't know what अन्यथा to क्रमmat - host may ignore ours
	 */
	ret = fw_cfg_ग_लिखो_blob(be16_to_cpu(f->select), data,
				0, माप(काष्ठा fw_cfg_vmcoreinfo));

	kमुक्त(data);
	वापस ret;
पूर्ण
#पूर्ण_अगर /* CONFIG_CRASH_CORE */

/* get fw_cfg_sysfs_entry from kobject member */
अटल अंतरभूत काष्ठा fw_cfg_sysfs_entry *to_entry(काष्ठा kobject *kobj)
अणु
	वापस container_of(kobj, काष्ठा fw_cfg_sysfs_entry, kobj);
पूर्ण

/* fw_cfg_sysfs_attribute type */
काष्ठा fw_cfg_sysfs_attribute अणु
	काष्ठा attribute attr;
	sमाप_प्रकार (*show)(काष्ठा fw_cfg_sysfs_entry *entry, अक्षर *buf);
पूर्ण;

/* get fw_cfg_sysfs_attribute from attribute member */
अटल अंतरभूत काष्ठा fw_cfg_sysfs_attribute *to_attr(काष्ठा attribute *attr)
अणु
	वापस container_of(attr, काष्ठा fw_cfg_sysfs_attribute, attr);
पूर्ण

/* global cache of fw_cfg_sysfs_entry objects */
अटल LIST_HEAD(fw_cfg_entry_cache);

/* kobjects हटाओd lazily by kernel, mutual exclusion needed */
अटल DEFINE_SPINLOCK(fw_cfg_cache_lock);

अटल अंतरभूत व्योम fw_cfg_sysfs_cache_enlist(काष्ठा fw_cfg_sysfs_entry *entry)
अणु
	spin_lock(&fw_cfg_cache_lock);
	list_add_tail(&entry->list, &fw_cfg_entry_cache);
	spin_unlock(&fw_cfg_cache_lock);
पूर्ण

अटल अंतरभूत व्योम fw_cfg_sysfs_cache_delist(काष्ठा fw_cfg_sysfs_entry *entry)
अणु
	spin_lock(&fw_cfg_cache_lock);
	list_del(&entry->list);
	spin_unlock(&fw_cfg_cache_lock);
पूर्ण

अटल व्योम fw_cfg_sysfs_cache_cleanup(व्योम)
अणु
	काष्ठा fw_cfg_sysfs_entry *entry, *next;

	list_क्रम_each_entry_safe(entry, next, &fw_cfg_entry_cache, list) अणु
		/* will end up invoking fw_cfg_sysfs_cache_delist()
		 * via each object's release() method (i.e. deकाष्ठाor)
		 */
		kobject_put(&entry->kobj);
	पूर्ण
पूर्ण

/* शेष_attrs: per-entry attributes and show methods */

#घोषणा FW_CFG_SYSFS_ATTR(_attr) \
काष्ठा fw_cfg_sysfs_attribute fw_cfg_sysfs_attr_##_attr = अणु \
	.attr = अणु .name = __stringअगरy(_attr), .mode = S_IRUSR पूर्ण, \
	.show = fw_cfg_sysfs_show_##_attr, \
पूर्ण

अटल sमाप_प्रकार fw_cfg_sysfs_show_size(काष्ठा fw_cfg_sysfs_entry *e, अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "%u\n", e->size);
पूर्ण

अटल sमाप_प्रकार fw_cfg_sysfs_show_key(काष्ठा fw_cfg_sysfs_entry *e, अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "%u\n", e->select);
पूर्ण

अटल sमाप_प्रकार fw_cfg_sysfs_show_name(काष्ठा fw_cfg_sysfs_entry *e, अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "%s\n", e->name);
पूर्ण

अटल FW_CFG_SYSFS_ATTR(size);
अटल FW_CFG_SYSFS_ATTR(key);
अटल FW_CFG_SYSFS_ATTR(name);

अटल काष्ठा attribute *fw_cfg_sysfs_entry_attrs[] = अणु
	&fw_cfg_sysfs_attr_size.attr,
	&fw_cfg_sysfs_attr_key.attr,
	&fw_cfg_sysfs_attr_name.attr,
	शून्य,
पूर्ण;

/* sysfs_ops: find fw_cfg_[entry, attribute] and call appropriate show method */
अटल sमाप_प्रकार fw_cfg_sysfs_attr_show(काष्ठा kobject *kobj, काष्ठा attribute *a,
				      अक्षर *buf)
अणु
	काष्ठा fw_cfg_sysfs_entry *entry = to_entry(kobj);
	काष्ठा fw_cfg_sysfs_attribute *attr = to_attr(a);

	वापस attr->show(entry, buf);
पूर्ण

अटल स्थिर काष्ठा sysfs_ops fw_cfg_sysfs_attr_ops = अणु
	.show = fw_cfg_sysfs_attr_show,
पूर्ण;

/* release: deकाष्ठाor, to be called via kobject_put() */
अटल व्योम fw_cfg_sysfs_release_entry(काष्ठा kobject *kobj)
अणु
	काष्ठा fw_cfg_sysfs_entry *entry = to_entry(kobj);

	fw_cfg_sysfs_cache_delist(entry);
	kमुक्त(entry);
पूर्ण

/* kobj_type: ties together all properties required to रेजिस्टर an entry */
अटल काष्ठा kobj_type fw_cfg_sysfs_entry_ktype = अणु
	.शेष_attrs = fw_cfg_sysfs_entry_attrs,
	.sysfs_ops = &fw_cfg_sysfs_attr_ops,
	.release = fw_cfg_sysfs_release_entry,
पूर्ण;

/* raw-पढ़ो method and attribute */
अटल sमाप_प्रकार fw_cfg_sysfs_पढ़ो_raw(काष्ठा file *filp, काष्ठा kobject *kobj,
				     काष्ठा bin_attribute *bin_attr,
				     अक्षर *buf, loff_t pos, माप_प्रकार count)
अणु
	काष्ठा fw_cfg_sysfs_entry *entry = to_entry(kobj);

	अगर (pos > entry->size)
		वापस -EINVAL;

	अगर (count > entry->size - pos)
		count = entry->size - pos;

	वापस fw_cfg_पढ़ो_blob(entry->select, buf, pos, count);
पूर्ण

अटल काष्ठा bin_attribute fw_cfg_sysfs_attr_raw = अणु
	.attr = अणु .name = "raw", .mode = S_IRUSR पूर्ण,
	.पढ़ो = fw_cfg_sysfs_पढ़ो_raw,
पूर्ण;

/*
 * Create a kset subdirectory matching each '/' delimited स_नाम token
 * in 'name', starting with sysfs kset/folder 'dir'; At the end, create
 * a symlink directed at the given 'target'.
 * NOTE: We करो this on a best-efक्रमt basis, since 'name' is not guaranteed
 * to be a well-behaved path name. Whenever a symlink vs. kset directory
 * name collision occurs, the kernel will issue big scary warnings जबतक
 * refusing to add the offending link or directory. We follow up with our
 * own, slightly less scary error messages explaining the situation :)
 */
अटल पूर्णांक fw_cfg_build_symlink(काष्ठा kset *dir,
				काष्ठा kobject *target, स्थिर अक्षर *name)
अणु
	पूर्णांक ret;
	काष्ठा kset *subdir;
	काष्ठा kobject *ko;
	अक्षर *name_copy, *p, *tok;

	अगर (!dir || !target || !name || !*name)
		वापस -EINVAL;

	/* clone a copy of name क्रम parsing */
	name_copy = p = kstrdup(name, GFP_KERNEL);
	अगर (!name_copy)
		वापस -ENOMEM;

	/* create folders क्रम each स_नाम token, then symlink क्रम basename */
	जबतक ((tok = strsep(&p, "/")) && *tok) अणु

		/* last (basename) token? If so, add symlink here */
		अगर (!p || !*p) अणु
			ret = sysfs_create_link(&dir->kobj, target, tok);
			अवरोध;
		पूर्ण

		/* करोes the current dir contain an item named after tok ? */
		ko = kset_find_obj(dir, tok);
		अगर (ko) अणु
			/* drop reference added by kset_find_obj */
			kobject_put(ko);

			/* ko MUST be a kset - we're about to use it as one ! */
			अगर (ko->ktype != dir->kobj.ktype) अणु
				ret = -EINVAL;
				अवरोध;
			पूर्ण

			/* descend पूर्णांकo alपढ़ोy existing subdirectory */
			dir = to_kset(ko);
		पूर्ण अन्यथा अणु
			/* create new subdirectory kset */
			subdir = kzalloc(माप(काष्ठा kset), GFP_KERNEL);
			अगर (!subdir) अणु
				ret = -ENOMEM;
				अवरोध;
			पूर्ण
			subdir->kobj.kset = dir;
			subdir->kobj.ktype = dir->kobj.ktype;
			ret = kobject_set_name(&subdir->kobj, "%s", tok);
			अगर (ret) अणु
				kमुक्त(subdir);
				अवरोध;
			पूर्ण
			ret = kset_रेजिस्टर(subdir);
			अगर (ret) अणु
				kमुक्त(subdir);
				अवरोध;
			पूर्ण

			/* descend पूर्णांकo newly created subdirectory */
			dir = subdir;
		पूर्ण
	पूर्ण

	/* we're करोne with cloned copy of name */
	kमुक्त(name_copy);
	वापस ret;
पूर्ण

/* recursively unरेजिस्टर fw_cfg/by_name/ kset directory tree */
अटल व्योम fw_cfg_kset_unरेजिस्टर_recursive(काष्ठा kset *kset)
अणु
	काष्ठा kobject *k, *next;

	list_क्रम_each_entry_safe(k, next, &kset->list, entry)
		/* all set members are ksets too, but check just in हाल... */
		अगर (k->ktype == kset->kobj.ktype)
			fw_cfg_kset_unरेजिस्टर_recursive(to_kset(k));

	/* symlinks are cleanly and स्वतःmatically हटाओd with the directory */
	kset_unरेजिस्टर(kset);
पूर्ण

/* kobjects & kset representing top-level, by_key, and by_name folders */
अटल काष्ठा kobject *fw_cfg_top_ko;
अटल काष्ठा kobject *fw_cfg_sel_ko;
अटल काष्ठा kset *fw_cfg_fname_kset;

/* रेजिस्टर an inभागidual fw_cfg file */
अटल पूर्णांक fw_cfg_रेजिस्टर_file(स्थिर काष्ठा fw_cfg_file *f)
अणु
	पूर्णांक err;
	काष्ठा fw_cfg_sysfs_entry *entry;

#अगर_घोषित CONFIG_CRASH_CORE
	अगर (fw_cfg_dma_enabled() &&
		म_भेद(f->name, FW_CFG_VMCOREINFO_खाताNAME) == 0 &&
		!is_kdump_kernel()) अणु
		अगर (fw_cfg_ग_लिखो_vmcoreinfo(f) < 0)
			pr_warn("fw_cfg: failed to write vmcoreinfo");
	पूर्ण
#पूर्ण_अगर

	/* allocate new entry */
	entry = kzalloc(माप(*entry), GFP_KERNEL);
	अगर (!entry)
		वापस -ENOMEM;

	/* set file entry inक्रमmation */
	entry->size = be32_to_cpu(f->size);
	entry->select = be16_to_cpu(f->select);
	स_नकल(entry->name, f->name, FW_CFG_MAX_खाता_PATH);

	/* रेजिस्टर entry under "/sys/firmware/qemu_fw_cfg/by_key/" */
	err = kobject_init_and_add(&entry->kobj, &fw_cfg_sysfs_entry_ktype,
				   fw_cfg_sel_ko, "%d", entry->select);
	अगर (err) अणु
		kobject_put(&entry->kobj);
		वापस err;
	पूर्ण

	/* add raw binary content access */
	err = sysfs_create_bin_file(&entry->kobj, &fw_cfg_sysfs_attr_raw);
	अगर (err)
		जाओ err_add_raw;

	/* try adding "/sys/firmware/qemu_fw_cfg/by_name/" symlink */
	fw_cfg_build_symlink(fw_cfg_fname_kset, &entry->kobj, entry->name);

	/* success, add entry to global cache */
	fw_cfg_sysfs_cache_enlist(entry);
	वापस 0;

err_add_raw:
	kobject_del(&entry->kobj);
	kमुक्त(entry);
	वापस err;
पूर्ण

/* iterate over all fw_cfg directory entries, रेजिस्टरing each one */
अटल पूर्णांक fw_cfg_रेजिस्टर_dir_entries(व्योम)
अणु
	पूर्णांक ret = 0;
	__be32 files_count;
	u32 count, i;
	काष्ठा fw_cfg_file *dir;
	माप_प्रकार dir_size;

	ret = fw_cfg_पढ़ो_blob(FW_CFG_खाता_सूची, &files_count,
			0, माप(files_count));
	अगर (ret < 0)
		वापस ret;

	count = be32_to_cpu(files_count);
	dir_size = count * माप(काष्ठा fw_cfg_file);

	dir = kदो_स्मृति(dir_size, GFP_KERNEL);
	अगर (!dir)
		वापस -ENOMEM;

	ret = fw_cfg_पढ़ो_blob(FW_CFG_खाता_सूची, dir,
			माप(files_count), dir_size);
	अगर (ret < 0)
		जाओ end;

	क्रम (i = 0; i < count; i++) अणु
		ret = fw_cfg_रेजिस्टर_file(&dir[i]);
		अगर (ret)
			अवरोध;
	पूर्ण

end:
	kमुक्त(dir);
	वापस ret;
पूर्ण

/* unरेजिस्टर top-level or by_key folder */
अटल अंतरभूत व्योम fw_cfg_kobj_cleanup(काष्ठा kobject *kobj)
अणु
	kobject_del(kobj);
	kobject_put(kobj);
पूर्ण

अटल पूर्णांक fw_cfg_sysfs_probe(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक err;
	__le32 rev;

	/* NOTE: If we supported multiple fw_cfg devices, we'd first create
	 * a subdirectory named after e.g. pdev->id, then hang per-device
	 * by_key (and by_name) subdirectories underneath it. However, only
	 * one fw_cfg device exist प्रणाली-wide, so अगर one was alपढ़ोy found
	 * earlier, we might as well stop here.
	 */
	अगर (fw_cfg_sel_ko)
		वापस -EBUSY;

	/* create by_key and by_name subdirs of /sys/firmware/qemu_fw_cfg/ */
	err = -ENOMEM;
	fw_cfg_sel_ko = kobject_create_and_add("by_key", fw_cfg_top_ko);
	अगर (!fw_cfg_sel_ko)
		जाओ err_sel;
	fw_cfg_fname_kset = kset_create_and_add("by_name", शून्य, fw_cfg_top_ko);
	अगर (!fw_cfg_fname_kset)
		जाओ err_name;

	/* initialize fw_cfg device i/o from platक्रमm data */
	err = fw_cfg_करो_platक्रमm_probe(pdev);
	अगर (err)
		जाओ err_probe;

	/* get revision number, add matching top-level attribute */
	err = fw_cfg_पढ़ो_blob(FW_CFG_ID, &rev, 0, माप(rev));
	अगर (err < 0)
		जाओ err_probe;

	fw_cfg_rev = le32_to_cpu(rev);
	err = sysfs_create_file(fw_cfg_top_ko, &fw_cfg_rev_attr.attr);
	अगर (err)
		जाओ err_rev;

	/* process fw_cfg file directory entry, रेजिस्टरing each file */
	err = fw_cfg_रेजिस्टर_dir_entries();
	अगर (err)
		जाओ err_dir;

	/* success */
	pr_debug("fw_cfg: loaded.\n");
	वापस 0;

err_dir:
	fw_cfg_sysfs_cache_cleanup();
	sysfs_हटाओ_file(fw_cfg_top_ko, &fw_cfg_rev_attr.attr);
err_rev:
	fw_cfg_io_cleanup();
err_probe:
	fw_cfg_kset_unरेजिस्टर_recursive(fw_cfg_fname_kset);
err_name:
	fw_cfg_kobj_cleanup(fw_cfg_sel_ko);
err_sel:
	वापस err;
पूर्ण

अटल पूर्णांक fw_cfg_sysfs_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	pr_debug("fw_cfg: unloading.\n");
	fw_cfg_sysfs_cache_cleanup();
	sysfs_हटाओ_file(fw_cfg_top_ko, &fw_cfg_rev_attr.attr);
	fw_cfg_io_cleanup();
	fw_cfg_kset_unरेजिस्टर_recursive(fw_cfg_fname_kset);
	fw_cfg_kobj_cleanup(fw_cfg_sel_ko);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id fw_cfg_sysfs_mmio_match[] = अणु
	अणु .compatible = "qemu,fw-cfg-mmio", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, fw_cfg_sysfs_mmio_match);

#अगर_घोषित CONFIG_ACPI
अटल स्थिर काष्ठा acpi_device_id fw_cfg_sysfs_acpi_match[] = अणु
	अणु FW_CFG_ACPI_DEVICE_ID, पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(acpi, fw_cfg_sysfs_acpi_match);
#पूर्ण_अगर

अटल काष्ठा platक्रमm_driver fw_cfg_sysfs_driver = अणु
	.probe = fw_cfg_sysfs_probe,
	.हटाओ = fw_cfg_sysfs_हटाओ,
	.driver = अणु
		.name = "fw_cfg",
		.of_match_table = fw_cfg_sysfs_mmio_match,
		.acpi_match_table = ACPI_PTR(fw_cfg_sysfs_acpi_match),
	पूर्ण,
पूर्ण;

#अगर_घोषित CONFIG_FW_CFG_SYSFS_CMDLINE

अटल काष्ठा platक्रमm_device *fw_cfg_cmdline_dev;

/* this probably beदीर्घs in e.g. include/linux/types.h,
 * but right now we are the only ones करोing it...
 */
#अगर_घोषित CONFIG_PHYS_ADDR_T_64BIT
#घोषणा __PHYS_ADDR_PREFIX "ll"
#अन्यथा
#घोषणा __PHYS_ADDR_PREFIX ""
#पूर्ण_अगर

/* use special म_पूछो/म_लिखो modअगरier क्रम phys_addr_t, resource_माप_प्रकार */
#घोषणा PH_ADDR_SCAN_FMT "@%" __PHYS_ADDR_PREFIX "i%n" \
			 ":%" __PHYS_ADDR_PREFIX "i" \
			 ":%" __PHYS_ADDR_PREFIX "i%n" \
			 ":%" __PHYS_ADDR_PREFIX "i%n"

#घोषणा PH_ADDR_PR_1_FMT "0x%" __PHYS_ADDR_PREFIX "x@" \
			 "0x%" __PHYS_ADDR_PREFIX "x"

#घोषणा PH_ADDR_PR_3_FMT PH_ADDR_PR_1_FMT \
			 ":%" __PHYS_ADDR_PREFIX "u" \
			 ":%" __PHYS_ADDR_PREFIX "u"

#घोषणा PH_ADDR_PR_4_FMT PH_ADDR_PR_3_FMT \
			 ":%" __PHYS_ADDR_PREFIX "u"

अटल पूर्णांक fw_cfg_cmdline_set(स्थिर अक्षर *arg, स्थिर काष्ठा kernel_param *kp)
अणु
	काष्ठा resource res[4] = अणुपूर्ण;
	अक्षर *str;
	phys_addr_t base;
	resource_माप_प्रकार size, ctrl_off, data_off, dma_off;
	पूर्णांक processed, consumed = 0;

	/* only one fw_cfg device can exist प्रणाली-wide, so अगर one
	 * was processed on the command line alपढ़ोy, we might as
	 * well stop here.
	 */
	अगर (fw_cfg_cmdline_dev) अणु
		/* aव्योम leaking previously रेजिस्टरed device */
		platक्रमm_device_unरेजिस्टर(fw_cfg_cmdline_dev);
		वापस -EINVAL;
	पूर्ण

	/* consume "<size>" portion of command line argument */
	size = memparse(arg, &str);

	/* get "@<base>[:<ctrl_off>:<data_off>[:<dma_off>]]" chunks */
	processed = माला_पूछो(str, PH_ADDR_SCAN_FMT,
			   &base, &consumed,
			   &ctrl_off, &data_off, &consumed,
			   &dma_off, &consumed);

	/* माला_पूछो() must process precisely 1, 3 or 4 chunks:
	 * <base> is mandatory, optionally followed by <ctrl_off>
	 * and <data_off>, and <dma_off>;
	 * there must be no extra अक्षरacters after the last chunk,
	 * so str[consumed] must be '\0'.
	 */
	अगर (str[consumed] ||
	    (processed != 1 && processed != 3 && processed != 4))
		वापस -EINVAL;

	res[0].start = base;
	res[0].end = base + size - 1;
	res[0].flags = !म_भेद(kp->name, "mmio") ? IORESOURCE_MEM :
						   IORESOURCE_IO;

	/* insert रेजिस्टर offsets, अगर provided */
	अगर (processed > 1) अणु
		res[1].name = "ctrl";
		res[1].start = ctrl_off;
		res[1].flags = IORESOURCE_REG;
		res[2].name = "data";
		res[2].start = data_off;
		res[2].flags = IORESOURCE_REG;
	पूर्ण
	अगर (processed > 3) अणु
		res[3].name = "dma";
		res[3].start = dma_off;
		res[3].flags = IORESOURCE_REG;
	पूर्ण

	/* "processed" happens to nicely match the number of resources
	 * we need to pass in to this platक्रमm device.
	 */
	fw_cfg_cmdline_dev = platक्रमm_device_रेजिस्टर_simple("fw_cfg",
					PLATFORM_DEVID_NONE, res, processed);

	वापस PTR_ERR_OR_ZERO(fw_cfg_cmdline_dev);
पूर्ण

अटल पूर्णांक fw_cfg_cmdline_get(अक्षर *buf, स्थिर काष्ठा kernel_param *kp)
अणु
	/* stay silent अगर device was not configured via the command
	 * line, or अगर the parameter name (ioport/mmio) करोesn't match
	 * the device setting
	 */
	अगर (!fw_cfg_cmdline_dev ||
	    (!म_भेद(kp->name, "mmio") ^
	     (fw_cfg_cmdline_dev->resource[0].flags == IORESOURCE_MEM)))
		वापस 0;

	चयन (fw_cfg_cmdline_dev->num_resources) अणु
	हाल 1:
		वापस snम_लिखो(buf, PAGE_SIZE, PH_ADDR_PR_1_FMT,
				resource_size(&fw_cfg_cmdline_dev->resource[0]),
				fw_cfg_cmdline_dev->resource[0].start);
	हाल 3:
		वापस snम_लिखो(buf, PAGE_SIZE, PH_ADDR_PR_3_FMT,
				resource_size(&fw_cfg_cmdline_dev->resource[0]),
				fw_cfg_cmdline_dev->resource[0].start,
				fw_cfg_cmdline_dev->resource[1].start,
				fw_cfg_cmdline_dev->resource[2].start);
	हाल 4:
		वापस snम_लिखो(buf, PAGE_SIZE, PH_ADDR_PR_4_FMT,
				resource_size(&fw_cfg_cmdline_dev->resource[0]),
				fw_cfg_cmdline_dev->resource[0].start,
				fw_cfg_cmdline_dev->resource[1].start,
				fw_cfg_cmdline_dev->resource[2].start,
				fw_cfg_cmdline_dev->resource[3].start);
	पूर्ण

	/* Should never get here */
	WARN(1, "Unexpected number of resources: %d\n",
		fw_cfg_cmdline_dev->num_resources);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा kernel_param_ops fw_cfg_cmdline_param_ops = अणु
	.set = fw_cfg_cmdline_set,
	.get = fw_cfg_cmdline_get,
पूर्ण;

device_param_cb(ioport, &fw_cfg_cmdline_param_ops, शून्य, S_IRUSR);
device_param_cb(mmio, &fw_cfg_cmdline_param_ops, शून्य, S_IRUSR);

#पूर्ण_अगर /* CONFIG_FW_CFG_SYSFS_CMDLINE */

अटल पूर्णांक __init fw_cfg_sysfs_init(व्योम)
अणु
	पूर्णांक ret;

	/* create /sys/firmware/qemu_fw_cfg/ top level directory */
	fw_cfg_top_ko = kobject_create_and_add("qemu_fw_cfg", firmware_kobj);
	अगर (!fw_cfg_top_ko)
		वापस -ENOMEM;

	ret = platक्रमm_driver_रेजिस्टर(&fw_cfg_sysfs_driver);
	अगर (ret)
		fw_cfg_kobj_cleanup(fw_cfg_top_ko);

	वापस ret;
पूर्ण

अटल व्योम __निकास fw_cfg_sysfs_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&fw_cfg_sysfs_driver);

#अगर_घोषित CONFIG_FW_CFG_SYSFS_CMDLINE
	platक्रमm_device_unरेजिस्टर(fw_cfg_cmdline_dev);
#पूर्ण_अगर

	/* clean up /sys/firmware/qemu_fw_cfg/ */
	fw_cfg_kobj_cleanup(fw_cfg_top_ko);
पूर्ण

module_init(fw_cfg_sysfs_init);
module_निकास(fw_cfg_sysfs_निकास);
