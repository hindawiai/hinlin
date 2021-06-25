<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Core registration and callback routines क्रम MTD
 * drivers and users.
 *
 * Copyright तऊ 1999-2010 David Woodhouse <dwmw2@infradead.org>
 * Copyright तऊ 2006      Red Hat UK Limited 
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/ptrace.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/माला.स>
#समावेश <linux/समयr.h>
#समावेश <linux/major.h>
#समावेश <linux/fs.h>
#समावेश <linux/err.h>
#समावेश <linux/ioctl.h>
#समावेश <linux/init.h>
#समावेश <linux/of.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/idr.h>
#समावेश <linux/backing-dev.h>
#समावेश <linux/gfp.h>
#समावेश <linux/slab.h>
#समावेश <linux/reboot.h>
#समावेश <linux/leds.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/nvmem-provider.h>

#समावेश <linux/mtd/mtd.h>
#समावेश <linux/mtd/partitions.h>

#समावेश "mtdcore.h"

काष्ठा backing_dev_info *mtd_bdi;

#अगर_घोषित CONFIG_PM_SLEEP

अटल पूर्णांक mtd_cls_suspend(काष्ठा device *dev)
अणु
	काष्ठा mtd_info *mtd = dev_get_drvdata(dev);

	वापस mtd ? mtd_suspend(mtd) : 0;
पूर्ण

अटल पूर्णांक mtd_cls_resume(काष्ठा device *dev)
अणु
	काष्ठा mtd_info *mtd = dev_get_drvdata(dev);

	अगर (mtd)
		mtd_resume(mtd);
	वापस 0;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(mtd_cls_pm_ops, mtd_cls_suspend, mtd_cls_resume);
#घोषणा MTD_CLS_PM_OPS (&mtd_cls_pm_ops)
#अन्यथा
#घोषणा MTD_CLS_PM_OPS शून्य
#पूर्ण_अगर

अटल काष्ठा class mtd_class = अणु
	.name = "mtd",
	.owner = THIS_MODULE,
	.pm = MTD_CLS_PM_OPS,
पूर्ण;

अटल DEFINE_IDR(mtd_idr);

/* These are exported solely क्रम the purpose of mtd_blkdevs.c. You
   should not use them क्रम _anything_ अन्यथा */
DEFINE_MUTEX(mtd_table_mutex);
EXPORT_SYMBOL_GPL(mtd_table_mutex);

काष्ठा mtd_info *__mtd_next_device(पूर्णांक i)
अणु
	वापस idr_get_next(&mtd_idr, &i);
पूर्ण
EXPORT_SYMBOL_GPL(__mtd_next_device);

अटल LIST_HEAD(mtd_notअगरiers);


#घोषणा MTD_DEVT(index) MKDEV(MTD_CHAR_MAJOR, (index)*2)

/* REVISIT once MTD uses the driver model better, whoever allocates
 * the mtd_info will probably want to use the release() hook...
 */
अटल व्योम mtd_release(काष्ठा device *dev)
अणु
	काष्ठा mtd_info *mtd = dev_get_drvdata(dev);
	dev_t index = MTD_DEVT(mtd->index);

	/* हटाओ /dev/mtdXro node */
	device_destroy(&mtd_class, index + 1);
पूर्ण

अटल sमाप_प्रकार mtd_type_show(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा mtd_info *mtd = dev_get_drvdata(dev);
	अक्षर *type;

	चयन (mtd->type) अणु
	हाल MTD_ABSENT:
		type = "absent";
		अवरोध;
	हाल MTD_RAM:
		type = "ram";
		अवरोध;
	हाल MTD_ROM:
		type = "rom";
		अवरोध;
	हाल MTD_NORFLASH:
		type = "nor";
		अवरोध;
	हाल MTD_न_अंकDFLASH:
		type = "nand";
		अवरोध;
	हाल MTD_DATAFLASH:
		type = "dataflash";
		अवरोध;
	हाल MTD_UBIVOLUME:
		type = "ubi";
		अवरोध;
	हाल MTD_MLCन_अंकDFLASH:
		type = "mlc-nand";
		अवरोध;
	शेष:
		type = "unknown";
	पूर्ण

	वापस snम_लिखो(buf, PAGE_SIZE, "%s\n", type);
पूर्ण
अटल DEVICE_ATTR(type, S_IRUGO, mtd_type_show, शून्य);

अटल sमाप_प्रकार mtd_flags_show(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा mtd_info *mtd = dev_get_drvdata(dev);

	वापस snम_लिखो(buf, PAGE_SIZE, "0x%lx\n", (अचिन्हित दीर्घ)mtd->flags);
पूर्ण
अटल DEVICE_ATTR(flags, S_IRUGO, mtd_flags_show, शून्य);

अटल sमाप_प्रकार mtd_size_show(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा mtd_info *mtd = dev_get_drvdata(dev);

	वापस snम_लिखो(buf, PAGE_SIZE, "%llu\n",
		(अचिन्हित दीर्घ दीर्घ)mtd->size);
पूर्ण
अटल DEVICE_ATTR(size, S_IRUGO, mtd_size_show, शून्य);

अटल sमाप_प्रकार mtd_erasesize_show(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा mtd_info *mtd = dev_get_drvdata(dev);

	वापस snम_लिखो(buf, PAGE_SIZE, "%lu\n", (अचिन्हित दीर्घ)mtd->erasesize);
पूर्ण
अटल DEVICE_ATTR(erasesize, S_IRUGO, mtd_erasesize_show, शून्य);

अटल sमाप_प्रकार mtd_ग_लिखोsize_show(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा mtd_info *mtd = dev_get_drvdata(dev);

	वापस snम_लिखो(buf, PAGE_SIZE, "%lu\n", (अचिन्हित दीर्घ)mtd->ग_लिखोsize);
पूर्ण
अटल DEVICE_ATTR(ग_लिखोsize, S_IRUGO, mtd_ग_लिखोsize_show, शून्य);

अटल sमाप_प्रकार mtd_subpagesize_show(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा mtd_info *mtd = dev_get_drvdata(dev);
	अचिन्हित पूर्णांक subpagesize = mtd->ग_लिखोsize >> mtd->subpage_sft;

	वापस snम_लिखो(buf, PAGE_SIZE, "%u\n", subpagesize);
पूर्ण
अटल DEVICE_ATTR(subpagesize, S_IRUGO, mtd_subpagesize_show, शून्य);

अटल sमाप_प्रकार mtd_oobsize_show(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा mtd_info *mtd = dev_get_drvdata(dev);

	वापस snम_लिखो(buf, PAGE_SIZE, "%lu\n", (अचिन्हित दीर्घ)mtd->oobsize);
पूर्ण
अटल DEVICE_ATTR(oobsize, S_IRUGO, mtd_oobsize_show, शून्य);

अटल sमाप_प्रकार mtd_oobavail_show(काष्ठा device *dev,
				 काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा mtd_info *mtd = dev_get_drvdata(dev);

	वापस snम_लिखो(buf, PAGE_SIZE, "%u\n", mtd->oobavail);
पूर्ण
अटल DEVICE_ATTR(oobavail, S_IRUGO, mtd_oobavail_show, शून्य);

अटल sमाप_प्रकार mtd_numeraseregions_show(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा mtd_info *mtd = dev_get_drvdata(dev);

	वापस snम_लिखो(buf, PAGE_SIZE, "%u\n", mtd->numeraseregions);
पूर्ण
अटल DEVICE_ATTR(numeraseregions, S_IRUGO, mtd_numeraseregions_show,
	शून्य);

अटल sमाप_प्रकार mtd_name_show(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा mtd_info *mtd = dev_get_drvdata(dev);

	वापस snम_लिखो(buf, PAGE_SIZE, "%s\n", mtd->name);
पूर्ण
अटल DEVICE_ATTR(name, S_IRUGO, mtd_name_show, शून्य);

अटल sमाप_प्रकार mtd_ecc_strength_show(काष्ठा device *dev,
				     काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा mtd_info *mtd = dev_get_drvdata(dev);

	वापस snम_लिखो(buf, PAGE_SIZE, "%u\n", mtd->ecc_strength);
पूर्ण
अटल DEVICE_ATTR(ecc_strength, S_IRUGO, mtd_ecc_strength_show, शून्य);

अटल sमाप_प्रकार mtd_bitflip_threshold_show(काष्ठा device *dev,
					  काष्ठा device_attribute *attr,
					  अक्षर *buf)
अणु
	काष्ठा mtd_info *mtd = dev_get_drvdata(dev);

	वापस snम_लिखो(buf, PAGE_SIZE, "%u\n", mtd->bitflip_threshold);
पूर्ण

अटल sमाप_प्रकार mtd_bitflip_threshold_store(काष्ठा device *dev,
					   काष्ठा device_attribute *attr,
					   स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा mtd_info *mtd = dev_get_drvdata(dev);
	अचिन्हित पूर्णांक bitflip_threshold;
	पूर्णांक retval;

	retval = kstrtouपूर्णांक(buf, 0, &bitflip_threshold);
	अगर (retval)
		वापस retval;

	mtd->bitflip_threshold = bitflip_threshold;
	वापस count;
पूर्ण
अटल DEVICE_ATTR(bitflip_threshold, S_IRUGO | S_IWUSR,
		   mtd_bitflip_threshold_show,
		   mtd_bitflip_threshold_store);

अटल sमाप_प्रकार mtd_ecc_step_size_show(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा mtd_info *mtd = dev_get_drvdata(dev);

	वापस snम_लिखो(buf, PAGE_SIZE, "%u\n", mtd->ecc_step_size);

पूर्ण
अटल DEVICE_ATTR(ecc_step_size, S_IRUGO, mtd_ecc_step_size_show, शून्य);

अटल sमाप_प्रकार mtd_ecc_stats_corrected_show(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा mtd_info *mtd = dev_get_drvdata(dev);
	काष्ठा mtd_ecc_stats *ecc_stats = &mtd->ecc_stats;

	वापस snम_लिखो(buf, PAGE_SIZE, "%u\n", ecc_stats->corrected);
पूर्ण
अटल DEVICE_ATTR(corrected_bits, S_IRUGO,
		   mtd_ecc_stats_corrected_show, शून्य);

अटल sमाप_प्रकार mtd_ecc_stats_errors_show(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा mtd_info *mtd = dev_get_drvdata(dev);
	काष्ठा mtd_ecc_stats *ecc_stats = &mtd->ecc_stats;

	वापस snम_लिखो(buf, PAGE_SIZE, "%u\n", ecc_stats->failed);
पूर्ण
अटल DEVICE_ATTR(ecc_failures, S_IRUGO, mtd_ecc_stats_errors_show, शून्य);

अटल sमाप_प्रकार mtd_badblocks_show(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा mtd_info *mtd = dev_get_drvdata(dev);
	काष्ठा mtd_ecc_stats *ecc_stats = &mtd->ecc_stats;

	वापस snम_लिखो(buf, PAGE_SIZE, "%u\n", ecc_stats->badblocks);
पूर्ण
अटल DEVICE_ATTR(bad_blocks, S_IRUGO, mtd_badblocks_show, शून्य);

अटल sमाप_प्रकार mtd_bbtblocks_show(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा mtd_info *mtd = dev_get_drvdata(dev);
	काष्ठा mtd_ecc_stats *ecc_stats = &mtd->ecc_stats;

	वापस snम_लिखो(buf, PAGE_SIZE, "%u\n", ecc_stats->bbtblocks);
पूर्ण
अटल DEVICE_ATTR(bbt_blocks, S_IRUGO, mtd_bbtblocks_show, शून्य);

अटल काष्ठा attribute *mtd_attrs[] = अणु
	&dev_attr_type.attr,
	&dev_attr_flags.attr,
	&dev_attr_size.attr,
	&dev_attr_erasesize.attr,
	&dev_attr_ग_लिखोsize.attr,
	&dev_attr_subpagesize.attr,
	&dev_attr_oobsize.attr,
	&dev_attr_oobavail.attr,
	&dev_attr_numeraseregions.attr,
	&dev_attr_name.attr,
	&dev_attr_ecc_strength.attr,
	&dev_attr_ecc_step_size.attr,
	&dev_attr_corrected_bits.attr,
	&dev_attr_ecc_failures.attr,
	&dev_attr_bad_blocks.attr,
	&dev_attr_bbt_blocks.attr,
	&dev_attr_bitflip_threshold.attr,
	शून्य,
पूर्ण;
ATTRIBUTE_GROUPS(mtd);

अटल स्थिर काष्ठा device_type mtd_devtype = अणु
	.name		= "mtd",
	.groups		= mtd_groups,
	.release	= mtd_release,
पूर्ण;

अटल पूर्णांक mtd_partid_debug_show(काष्ठा seq_file *s, व्योम *p)
अणु
	काष्ठा mtd_info *mtd = s->निजी;

	seq_म_लिखो(s, "%s\n", mtd->dbg.partid);

	वापस 0;
पूर्ण

DEFINE_SHOW_ATTRIBUTE(mtd_partid_debug);

अटल पूर्णांक mtd_partname_debug_show(काष्ठा seq_file *s, व्योम *p)
अणु
	काष्ठा mtd_info *mtd = s->निजी;

	seq_म_लिखो(s, "%s\n", mtd->dbg.partname);

	वापस 0;
पूर्ण

DEFINE_SHOW_ATTRIBUTE(mtd_partname_debug);

अटल काष्ठा dentry *dfs_dir_mtd;

अटल व्योम mtd_debugfs_populate(काष्ठा mtd_info *mtd)
अणु
	काष्ठा device *dev = &mtd->dev;
	काष्ठा dentry *root;

	अगर (IS_ERR_OR_शून्य(dfs_dir_mtd))
		वापस;

	root = debugfs_create_dir(dev_name(dev), dfs_dir_mtd);
	mtd->dbg.dfs_dir = root;

	अगर (mtd->dbg.partid)
		debugfs_create_file("partid", 0400, root, mtd,
				    &mtd_partid_debug_fops);

	अगर (mtd->dbg.partname)
		debugfs_create_file("partname", 0400, root, mtd,
				    &mtd_partname_debug_fops);
पूर्ण

#अगर_अघोषित CONFIG_MMU
अचिन्हित mtd_mmap_capabilities(काष्ठा mtd_info *mtd)
अणु
	चयन (mtd->type) अणु
	हाल MTD_RAM:
		वापस NOMMU_MAP_COPY | NOMMU_MAP_सूचीECT | NOMMU_MAP_EXEC |
			NOMMU_MAP_READ | NOMMU_MAP_WRITE;
	हाल MTD_ROM:
		वापस NOMMU_MAP_COPY | NOMMU_MAP_सूचीECT | NOMMU_MAP_EXEC |
			NOMMU_MAP_READ;
	शेष:
		वापस NOMMU_MAP_COPY;
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(mtd_mmap_capabilities);
#पूर्ण_अगर

अटल पूर्णांक mtd_reboot_notअगरier(काष्ठा notअगरier_block *n, अचिन्हित दीर्घ state,
			       व्योम *cmd)
अणु
	काष्ठा mtd_info *mtd;

	mtd = container_of(n, काष्ठा mtd_info, reboot_notअगरier);
	mtd->_reboot(mtd);

	वापस NOTIFY_DONE;
पूर्ण

/**
 * mtd_wunit_to_pairing_info - get pairing inक्रमmation of a wunit
 * @mtd: poपूर्णांकer to new MTD device info काष्ठाure
 * @wunit: ग_लिखो unit we are पूर्णांकerested in
 * @info: वापसed pairing inक्रमmation
 *
 * Retrieve pairing inक्रमmation associated to the wunit.
 * This is मुख्यly useful when dealing with MLC/TLC न_अंकDs where pages can be
 * paired together, and where programming a page may influence the page it is
 * paired with.
 * The notion of page is replaced by the term wunit (ग_लिखो-unit) to stay
 * consistent with the ->ग_लिखोsize field.
 *
 * The @wunit argument can be extracted from an असलolute offset using
 * mtd_offset_to_wunit(). @info is filled with the pairing inक्रमmation attached
 * to @wunit.
 *
 * From the pairing info the MTD user can find all the wunits paired with
 * @wunit using the following loop:
 *
 * क्रम (i = 0; i < mtd_pairing_groups(mtd); i++) अणु
 *	info.pair = i;
 *	mtd_pairing_info_to_wunit(mtd, &info);
 *	...
 * पूर्ण
 */
पूर्णांक mtd_wunit_to_pairing_info(काष्ठा mtd_info *mtd, पूर्णांक wunit,
			      काष्ठा mtd_pairing_info *info)
अणु
	काष्ठा mtd_info *master = mtd_get_master(mtd);
	पूर्णांक npairs = mtd_wunit_per_eb(master) / mtd_pairing_groups(master);

	अगर (wunit < 0 || wunit >= npairs)
		वापस -EINVAL;

	अगर (master->pairing && master->pairing->get_info)
		वापस master->pairing->get_info(master, wunit, info);

	info->group = 0;
	info->pair = wunit;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(mtd_wunit_to_pairing_info);

/**
 * mtd_pairing_info_to_wunit - get wunit from pairing inक्रमmation
 * @mtd: poपूर्णांकer to new MTD device info काष्ठाure
 * @info: pairing inक्रमmation काष्ठा
 *
 * Returns a positive number representing the wunit associated to the info
 * काष्ठा, or a negative error code.
 *
 * This is the reverse of mtd_wunit_to_pairing_info(), and can help one to
 * iterate over all wunits of a given pair (see mtd_wunit_to_pairing_info()
 * करोc).
 *
 * It can also be used to only program the first page of each pair (i.e.
 * page attached to group 0), which allows one to use an MLC न_अंकD in
 * software-emulated SLC mode:
 *
 * info.group = 0;
 * npairs = mtd_wunit_per_eb(mtd) / mtd_pairing_groups(mtd);
 * क्रम (info.pair = 0; info.pair < npairs; info.pair++) अणु
 *	wunit = mtd_pairing_info_to_wunit(mtd, &info);
 *	mtd_ग_लिखो(mtd, mtd_wunit_to_offset(mtd, blkoffs, wunit),
 *		  mtd->ग_लिखोsize, &retlen, buf + (i * mtd->ग_लिखोsize));
 * पूर्ण
 */
पूर्णांक mtd_pairing_info_to_wunit(काष्ठा mtd_info *mtd,
			      स्थिर काष्ठा mtd_pairing_info *info)
अणु
	काष्ठा mtd_info *master = mtd_get_master(mtd);
	पूर्णांक ngroups = mtd_pairing_groups(master);
	पूर्णांक npairs = mtd_wunit_per_eb(master) / ngroups;

	अगर (!info || info->pair < 0 || info->pair >= npairs ||
	    info->group < 0 || info->group >= ngroups)
		वापस -EINVAL;

	अगर (master->pairing && master->pairing->get_wunit)
		वापस mtd->pairing->get_wunit(master, info);

	वापस info->pair;
पूर्ण
EXPORT_SYMBOL_GPL(mtd_pairing_info_to_wunit);

/**
 * mtd_pairing_groups - get the number of pairing groups
 * @mtd: poपूर्णांकer to new MTD device info काष्ठाure
 *
 * Returns the number of pairing groups.
 *
 * This number is usually equal to the number of bits exposed by a single
 * cell, and can be used in conjunction with mtd_pairing_info_to_wunit()
 * to iterate over all pages of a given pair.
 */
पूर्णांक mtd_pairing_groups(काष्ठा mtd_info *mtd)
अणु
	काष्ठा mtd_info *master = mtd_get_master(mtd);

	अगर (!master->pairing || !master->pairing->ngroups)
		वापस 1;

	वापस master->pairing->ngroups;
पूर्ण
EXPORT_SYMBOL_GPL(mtd_pairing_groups);

अटल पूर्णांक mtd_nvmem_reg_पढ़ो(व्योम *priv, अचिन्हित पूर्णांक offset,
			      व्योम *val, माप_प्रकार bytes)
अणु
	काष्ठा mtd_info *mtd = priv;
	माप_प्रकार retlen;
	पूर्णांक err;

	err = mtd_पढ़ो(mtd, offset, bytes, &retlen, val);
	अगर (err && err != -EUCLEAN)
		वापस err;

	वापस retlen == bytes ? 0 : -EIO;
पूर्ण

अटल पूर्णांक mtd_nvmem_add(काष्ठा mtd_info *mtd)
अणु
	काष्ठा device_node *node = mtd_get_of_node(mtd);
	काष्ठा nvmem_config config = अणुपूर्ण;

	config.id = -1;
	config.dev = &mtd->dev;
	config.name = dev_name(&mtd->dev);
	config.owner = THIS_MODULE;
	config.reg_पढ़ो = mtd_nvmem_reg_पढ़ो;
	config.size = mtd->size;
	config.word_size = 1;
	config.stride = 1;
	config.पढ़ो_only = true;
	config.root_only = true;
	config.no_of_node = !of_device_is_compatible(node, "nvmem-cells");
	config.priv = mtd;

	mtd->nvmem = nvmem_रेजिस्टर(&config);
	अगर (IS_ERR(mtd->nvmem)) अणु
		/* Just ignore अगर there is no NVMEM support in the kernel */
		अगर (PTR_ERR(mtd->nvmem) == -EOPNOTSUPP) अणु
			mtd->nvmem = शून्य;
		पूर्ण अन्यथा अणु
			dev_err(&mtd->dev, "Failed to register NVMEM device\n");
			वापस PTR_ERR(mtd->nvmem);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/**
 *	add_mtd_device - रेजिस्टर an MTD device
 *	@mtd: poपूर्णांकer to new MTD device info काष्ठाure
 *
 *	Add a device to the list of MTD devices present in the प्रणाली, and
 *	notअगरy each currently active MTD 'user' of its arrival. Returns
 *	zero on success or non-zero on failure.
 */

पूर्णांक add_mtd_device(काष्ठा mtd_info *mtd)
अणु
	काष्ठा mtd_info *master = mtd_get_master(mtd);
	काष्ठा mtd_notअगरier *not;
	पूर्णांक i, error;

	/*
	 * May occur, क्रम instance, on buggy drivers which call
	 * mtd_device_parse_रेजिस्टर() multiple बार on the same master MTD,
	 * especially with CONFIG_MTD_PARTITIONED_MASTER=y.
	 */
	अगर (WARN_ONCE(mtd->dev.type, "MTD already registered\n"))
		वापस -EEXIST;

	BUG_ON(mtd->ग_लिखोsize == 0);

	/*
	 * MTD drivers should implement ->_अणुग_लिखो,पढ़ोपूर्ण() or
	 * ->_अणुग_लिखो,पढ़ोपूर्ण_oob(), but not both.
	 */
	अगर (WARN_ON((mtd->_ग_लिखो && mtd->_ग_लिखो_oob) ||
		    (mtd->_पढ़ो && mtd->_पढ़ो_oob)))
		वापस -EINVAL;

	अगर (WARN_ON((!mtd->erasesize || !master->_erase) &&
		    !(mtd->flags & MTD_NO_ERASE)))
		वापस -EINVAL;

	/*
	 * MTD_SLC_ON_MLC_EMULATION can only be set on partitions, when the
	 * master is an MLC न_अंकD and has a proper pairing scheme defined.
	 * We also reject masters that implement ->_ग_लिखोv() क्रम now, because
	 * न_अंकD controller drivers करोn't implement this hook, and adding the
	 * SLC -> MLC address/length conversion to this path is useless अगर we
	 * करोn't have a user.
	 */
	अगर (mtd->flags & MTD_SLC_ON_MLC_EMULATION &&
	    (!mtd_is_partition(mtd) || master->type != MTD_MLCन_अंकDFLASH ||
	     !master->pairing || master->_ग_लिखोv))
		वापस -EINVAL;

	mutex_lock(&mtd_table_mutex);

	i = idr_alloc(&mtd_idr, mtd, 0, 0, GFP_KERNEL);
	अगर (i < 0) अणु
		error = i;
		जाओ fail_locked;
	पूर्ण

	mtd->index = i;
	mtd->usecount = 0;

	/* शेष value अगर not set by driver */
	अगर (mtd->bitflip_threshold == 0)
		mtd->bitflip_threshold = mtd->ecc_strength;

	अगर (mtd->flags & MTD_SLC_ON_MLC_EMULATION) अणु
		पूर्णांक ngroups = mtd_pairing_groups(master);

		mtd->erasesize /= ngroups;
		mtd->size = (u64)mtd_भाग_by_eb(mtd->size, master) *
			    mtd->erasesize;
	पूर्ण

	अगर (is_घातer_of_2(mtd->erasesize))
		mtd->erasesize_shअगरt = ffs(mtd->erasesize) - 1;
	अन्यथा
		mtd->erasesize_shअगरt = 0;

	अगर (is_घातer_of_2(mtd->ग_लिखोsize))
		mtd->ग_लिखोsize_shअगरt = ffs(mtd->ग_लिखोsize) - 1;
	अन्यथा
		mtd->ग_लिखोsize_shअगरt = 0;

	mtd->erasesize_mask = (1 << mtd->erasesize_shअगरt) - 1;
	mtd->ग_लिखोsize_mask = (1 << mtd->ग_लिखोsize_shअगरt) - 1;

	/* Some chips always घातer up locked. Unlock them now */
	अगर ((mtd->flags & MTD_WRITEABLE) && (mtd->flags & MTD_POWERUP_LOCK)) अणु
		error = mtd_unlock(mtd, 0, mtd->size);
		अगर (error && error != -EOPNOTSUPP)
			prपूर्णांकk(KERN_WARNING
			       "%s: unlock failed, writes may not work\n",
			       mtd->name);
		/* Ignore unlock failures? */
		error = 0;
	पूर्ण

	/* Caller should have set dev.parent to match the
	 * physical device, अगर appropriate.
	 */
	mtd->dev.type = &mtd_devtype;
	mtd->dev.class = &mtd_class;
	mtd->dev.devt = MTD_DEVT(i);
	dev_set_name(&mtd->dev, "mtd%d", i);
	dev_set_drvdata(&mtd->dev, mtd);
	of_node_get(mtd_get_of_node(mtd));
	error = device_रेजिस्टर(&mtd->dev);
	अगर (error)
		जाओ fail_added;

	/* Add the nvmem provider */
	error = mtd_nvmem_add(mtd);
	अगर (error)
		जाओ fail_nvmem_add;

	mtd_debugfs_populate(mtd);

	device_create(&mtd_class, mtd->dev.parent, MTD_DEVT(i) + 1, शून्य,
		      "mtd%dro", i);

	pr_debug("mtd: Giving out device %d to %s\n", i, mtd->name);
	/* No need to get a refcount on the module containing
	   the notअगरier, since we hold the mtd_table_mutex */
	list_क्रम_each_entry(not, &mtd_notअगरiers, list)
		not->add(mtd);

	mutex_unlock(&mtd_table_mutex);
	/* We _know_ we aren't being हटाओd, because
	   our caller is still holding us here. So none
	   of this try_ nonsense, and no bitching about it
	   either. :) */
	__module_get(THIS_MODULE);
	वापस 0;

fail_nvmem_add:
	device_unरेजिस्टर(&mtd->dev);
fail_added:
	of_node_put(mtd_get_of_node(mtd));
	idr_हटाओ(&mtd_idr, i);
fail_locked:
	mutex_unlock(&mtd_table_mutex);
	वापस error;
पूर्ण

/**
 *	del_mtd_device - unरेजिस्टर an MTD device
 *	@mtd: poपूर्णांकer to MTD device info काष्ठाure
 *
 *	Remove a device from the list of MTD devices present in the प्रणाली,
 *	and notअगरy each currently active MTD 'user' of its departure.
 *	Returns zero on success or 1 on failure, which currently will happen
 *	अगर the requested device करोes not appear to be present in the list.
 */

पूर्णांक del_mtd_device(काष्ठा mtd_info *mtd)
अणु
	पूर्णांक ret;
	काष्ठा mtd_notअगरier *not;

	mutex_lock(&mtd_table_mutex);

	debugfs_हटाओ_recursive(mtd->dbg.dfs_dir);

	अगर (idr_find(&mtd_idr, mtd->index) != mtd) अणु
		ret = -ENODEV;
		जाओ out_error;
	पूर्ण

	/* No need to get a refcount on the module containing
		the notअगरier, since we hold the mtd_table_mutex */
	list_क्रम_each_entry(not, &mtd_notअगरiers, list)
		not->हटाओ(mtd);

	अगर (mtd->usecount) अणु
		prपूर्णांकk(KERN_NOTICE "Removing MTD device #%d (%s) with use count %d\n",
		       mtd->index, mtd->name, mtd->usecount);
		ret = -EBUSY;
	पूर्ण अन्यथा अणु
		/* Try to हटाओ the NVMEM provider */
		अगर (mtd->nvmem)
			nvmem_unरेजिस्टर(mtd->nvmem);

		device_unरेजिस्टर(&mtd->dev);

		idr_हटाओ(&mtd_idr, mtd->index);
		of_node_put(mtd_get_of_node(mtd));

		module_put(THIS_MODULE);
		ret = 0;
	पूर्ण

out_error:
	mutex_unlock(&mtd_table_mutex);
	वापस ret;
पूर्ण

/*
 * Set a few शेषs based on the parent devices, अगर not provided by the
 * driver
 */
अटल व्योम mtd_set_dev_शेषs(काष्ठा mtd_info *mtd)
अणु
	अगर (mtd->dev.parent) अणु
		अगर (!mtd->owner && mtd->dev.parent->driver)
			mtd->owner = mtd->dev.parent->driver->owner;
		अगर (!mtd->name)
			mtd->name = dev_name(mtd->dev.parent);
	पूर्ण अन्यथा अणु
		pr_debug("mtd device won't show a device symlink in sysfs\n");
	पूर्ण

	INIT_LIST_HEAD(&mtd->partitions);
	mutex_init(&mtd->master.partitions_lock);
	mutex_init(&mtd->master.chrdev_lock);
पूर्ण

/**
 * mtd_device_parse_रेजिस्टर - parse partitions and रेजिस्टर an MTD device.
 *
 * @mtd: the MTD device to रेजिस्टर
 * @types: the list of MTD partition probes to try, see
 *         'parse_mtd_partitions()' क्रम more inक्रमmation
 * @parser_data: MTD partition parser-specअगरic data
 * @parts: fallback partition inक्रमmation to रेजिस्टर, अगर parsing fails;
 *         only valid अगर %nr_parts > %0
 * @nr_parts: the number of partitions in parts, अगर zero then the full
 *            MTD device is रेजिस्टरed अगर no partition info is found
 *
 * This function aggregates MTD partitions parsing (करोne by
 * 'parse_mtd_partitions()') and MTD device and partitions रेजिस्टरing. It
 * basically follows the most common pattern found in many MTD drivers:
 *
 * * If the MTD_PARTITIONED_MASTER option is set, then the device as a whole is
 *   रेजिस्टरed first.
 * * Then It tries to probe partitions on MTD device @mtd using parsers
 *   specअगरied in @types (अगर @types is %शून्य, then the शेष list of parsers
 *   is used, see 'parse_mtd_partitions()' क्रम more inक्रमmation). If none are
 *   found this functions tries to fallback to inक्रमmation specअगरied in
 *   @parts/@nr_parts.
 * * If no partitions were found this function just रेजिस्टरs the MTD device
 *   @mtd and निकासs.
 *
 * Returns zero in हाल of success and a negative error code in हाल of failure.
 */
पूर्णांक mtd_device_parse_रेजिस्टर(काष्ठा mtd_info *mtd, स्थिर अक्षर * स्थिर *types,
			      काष्ठा mtd_part_parser_data *parser_data,
			      स्थिर काष्ठा mtd_partition *parts,
			      पूर्णांक nr_parts)
अणु
	पूर्णांक ret;

	mtd_set_dev_शेषs(mtd);

	अगर (IS_ENABLED(CONFIG_MTD_PARTITIONED_MASTER)) अणु
		ret = add_mtd_device(mtd);
		अगर (ret)
			वापस ret;
	पूर्ण

	/* Prefer parsed partitions over driver-provided fallback */
	ret = parse_mtd_partitions(mtd, types, parser_data);
	अगर (ret == -EPROBE_DEFER)
		जाओ out;

	अगर (ret > 0)
		ret = 0;
	अन्यथा अगर (nr_parts)
		ret = add_mtd_partitions(mtd, parts, nr_parts);
	अन्यथा अगर (!device_is_रेजिस्टरed(&mtd->dev))
		ret = add_mtd_device(mtd);
	अन्यथा
		ret = 0;

	अगर (ret)
		जाओ out;

	/*
	 * FIXME: some drivers unक्रमtunately call this function more than once.
	 * So we have to check अगर we've alपढ़ोy asचिन्हित the reboot notअगरier.
	 *
	 * Generally, we can make multiple calls work क्रम most हालs, but it
	 * करोes cause problems with parse_mtd_partitions() above (e.g.,
	 * cmdlineparts will रेजिस्टर partitions more than once).
	 */
	WARN_ONCE(mtd->_reboot && mtd->reboot_notअगरier.notअगरier_call,
		  "MTD already registered\n");
	अगर (mtd->_reboot && !mtd->reboot_notअगरier.notअगरier_call) अणु
		mtd->reboot_notअगरier.notअगरier_call = mtd_reboot_notअगरier;
		रेजिस्टर_reboot_notअगरier(&mtd->reboot_notअगरier);
	पूर्ण

out:
	अगर (ret && device_is_रेजिस्टरed(&mtd->dev))
		del_mtd_device(mtd);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(mtd_device_parse_रेजिस्टर);

/**
 * mtd_device_unरेजिस्टर - unरेजिस्टर an existing MTD device.
 *
 * @master: the MTD device to unरेजिस्टर.  This will unरेजिस्टर both the master
 *          and any partitions अगर रेजिस्टरed.
 */
पूर्णांक mtd_device_unरेजिस्टर(काष्ठा mtd_info *master)
अणु
	पूर्णांक err;

	अगर (master->_reboot)
		unरेजिस्टर_reboot_notअगरier(&master->reboot_notअगरier);

	err = del_mtd_partitions(master);
	अगर (err)
		वापस err;

	अगर (!device_is_रेजिस्टरed(&master->dev))
		वापस 0;

	वापस del_mtd_device(master);
पूर्ण
EXPORT_SYMBOL_GPL(mtd_device_unरेजिस्टर);

/**
 *	रेजिस्टर_mtd_user - रेजिस्टर a 'user' of MTD devices.
 *	@new: poपूर्णांकer to notअगरier info काष्ठाure
 *
 *	Registers a pair of callbacks function to be called upon addition
 *	or removal of MTD devices. Causes the 'add' callback to be immediately
 *	invoked क्रम each MTD device currently present in the प्रणाली.
 */
व्योम रेजिस्टर_mtd_user (काष्ठा mtd_notअगरier *new)
अणु
	काष्ठा mtd_info *mtd;

	mutex_lock(&mtd_table_mutex);

	list_add(&new->list, &mtd_notअगरiers);

	__module_get(THIS_MODULE);

	mtd_क्रम_each_device(mtd)
		new->add(mtd);

	mutex_unlock(&mtd_table_mutex);
पूर्ण
EXPORT_SYMBOL_GPL(रेजिस्टर_mtd_user);

/**
 *	unरेजिस्टर_mtd_user - unरेजिस्टर a 'user' of MTD devices.
 *	@old: poपूर्णांकer to notअगरier info काष्ठाure
 *
 *	Removes a callback function pair from the list of 'users' to be
 *	notअगरied upon addition or removal of MTD devices. Causes the
 *	'remove' callback to be immediately invoked क्रम each MTD device
 *	currently present in the प्रणाली.
 */
पूर्णांक unरेजिस्टर_mtd_user (काष्ठा mtd_notअगरier *old)
अणु
	काष्ठा mtd_info *mtd;

	mutex_lock(&mtd_table_mutex);

	module_put(THIS_MODULE);

	mtd_क्रम_each_device(mtd)
		old->हटाओ(mtd);

	list_del(&old->list);
	mutex_unlock(&mtd_table_mutex);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(unरेजिस्टर_mtd_user);

/**
 *	get_mtd_device - obtain a validated handle क्रम an MTD device
 *	@mtd: last known address of the required MTD device
 *	@num: पूर्णांकernal device number of the required MTD device
 *
 *	Given a number and शून्य address, वापस the num'th entry in the device
 *	table, अगर any.	Given an address and num == -1, search the device table
 *	क्रम a device with that address and वापस अगर it's still present. Given
 *	both, वापस the num'th driver only अगर its address matches. Return
 *	error code अगर not.
 */
काष्ठा mtd_info *get_mtd_device(काष्ठा mtd_info *mtd, पूर्णांक num)
अणु
	काष्ठा mtd_info *ret = शून्य, *other;
	पूर्णांक err = -ENODEV;

	mutex_lock(&mtd_table_mutex);

	अगर (num == -1) अणु
		mtd_क्रम_each_device(other) अणु
			अगर (other == mtd) अणु
				ret = mtd;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अगर (num >= 0) अणु
		ret = idr_find(&mtd_idr, num);
		अगर (mtd && mtd != ret)
			ret = शून्य;
	पूर्ण

	अगर (!ret) अणु
		ret = ERR_PTR(err);
		जाओ out;
	पूर्ण

	err = __get_mtd_device(ret);
	अगर (err)
		ret = ERR_PTR(err);
out:
	mutex_unlock(&mtd_table_mutex);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(get_mtd_device);


पूर्णांक __get_mtd_device(काष्ठा mtd_info *mtd)
अणु
	काष्ठा mtd_info *master = mtd_get_master(mtd);
	पूर्णांक err;

	अगर (!try_module_get(master->owner))
		वापस -ENODEV;

	अगर (master->_get_device) अणु
		err = master->_get_device(mtd);

		अगर (err) अणु
			module_put(master->owner);
			वापस err;
		पूर्ण
	पूर्ण

	master->usecount++;

	जबतक (mtd->parent) अणु
		mtd->usecount++;
		mtd = mtd->parent;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(__get_mtd_device);

/**
 *	get_mtd_device_nm - obtain a validated handle क्रम an MTD device by
 *	device name
 *	@name: MTD device name to खोलो
 *
 * 	This function वापसs MTD device description काष्ठाure in हाल of
 * 	success and an error code in हाल of failure.
 */
काष्ठा mtd_info *get_mtd_device_nm(स्थिर अक्षर *name)
अणु
	पूर्णांक err = -ENODEV;
	काष्ठा mtd_info *mtd = शून्य, *other;

	mutex_lock(&mtd_table_mutex);

	mtd_क्रम_each_device(other) अणु
		अगर (!म_भेद(name, other->name)) अणु
			mtd = other;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!mtd)
		जाओ out_unlock;

	err = __get_mtd_device(mtd);
	अगर (err)
		जाओ out_unlock;

	mutex_unlock(&mtd_table_mutex);
	वापस mtd;

out_unlock:
	mutex_unlock(&mtd_table_mutex);
	वापस ERR_PTR(err);
पूर्ण
EXPORT_SYMBOL_GPL(get_mtd_device_nm);

व्योम put_mtd_device(काष्ठा mtd_info *mtd)
अणु
	mutex_lock(&mtd_table_mutex);
	__put_mtd_device(mtd);
	mutex_unlock(&mtd_table_mutex);

पूर्ण
EXPORT_SYMBOL_GPL(put_mtd_device);

व्योम __put_mtd_device(काष्ठा mtd_info *mtd)
अणु
	काष्ठा mtd_info *master = mtd_get_master(mtd);

	जबतक (mtd->parent) अणु
		--mtd->usecount;
		BUG_ON(mtd->usecount < 0);
		mtd = mtd->parent;
	पूर्ण

	master->usecount--;

	अगर (master->_put_device)
		master->_put_device(master);

	module_put(master->owner);
पूर्ण
EXPORT_SYMBOL_GPL(__put_mtd_device);

/*
 * Erase is an synchronous operation. Device drivers are epected to वापस a
 * negative error code अगर the operation failed and update instr->fail_addr
 * to poपूर्णांक the portion that was not properly erased.
 */
पूर्णांक mtd_erase(काष्ठा mtd_info *mtd, काष्ठा erase_info *instr)
अणु
	काष्ठा mtd_info *master = mtd_get_master(mtd);
	u64 mst_ofs = mtd_get_master_ofs(mtd, 0);
	काष्ठा erase_info adjinstr;
	पूर्णांक ret;

	instr->fail_addr = MTD_FAIL_ADDR_UNKNOWN;
	adjinstr = *instr;

	अगर (!mtd->erasesize || !master->_erase)
		वापस -ENOTSUPP;

	अगर (instr->addr >= mtd->size || instr->len > mtd->size - instr->addr)
		वापस -EINVAL;
	अगर (!(mtd->flags & MTD_WRITEABLE))
		वापस -EROFS;

	अगर (!instr->len)
		वापस 0;

	ledtrig_mtd_activity();

	अगर (mtd->flags & MTD_SLC_ON_MLC_EMULATION) अणु
		adjinstr.addr = (loff_t)mtd_भाग_by_eb(instr->addr, mtd) *
				master->erasesize;
		adjinstr.len = ((u64)mtd_भाग_by_eb(instr->addr + instr->len, mtd) *
				master->erasesize) -
			       adjinstr.addr;
	पूर्ण

	adjinstr.addr += mst_ofs;

	ret = master->_erase(master, &adjinstr);

	अगर (adjinstr.fail_addr != MTD_FAIL_ADDR_UNKNOWN) अणु
		instr->fail_addr = adjinstr.fail_addr - mst_ofs;
		अगर (mtd->flags & MTD_SLC_ON_MLC_EMULATION) अणु
			instr->fail_addr = mtd_भाग_by_eb(instr->fail_addr,
							 master);
			instr->fail_addr *= mtd->erasesize;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(mtd_erase);

/*
 * This stuff क्रम eXecute-In-Place. phys is optional and may be set to शून्य.
 */
पूर्णांक mtd_poपूर्णांक(काष्ठा mtd_info *mtd, loff_t from, माप_प्रकार len, माप_प्रकार *retlen,
	      व्योम **virt, resource_माप_प्रकार *phys)
अणु
	काष्ठा mtd_info *master = mtd_get_master(mtd);

	*retlen = 0;
	*virt = शून्य;
	अगर (phys)
		*phys = 0;
	अगर (!master->_poपूर्णांक)
		वापस -EOPNOTSUPP;
	अगर (from < 0 || from >= mtd->size || len > mtd->size - from)
		वापस -EINVAL;
	अगर (!len)
		वापस 0;

	from = mtd_get_master_ofs(mtd, from);
	वापस master->_poपूर्णांक(master, from, len, retlen, virt, phys);
पूर्ण
EXPORT_SYMBOL_GPL(mtd_poपूर्णांक);

/* We probably shouldn't allow XIP if the unpoint isn't a शून्य */
पूर्णांक mtd_unpoपूर्णांक(काष्ठा mtd_info *mtd, loff_t from, माप_प्रकार len)
अणु
	काष्ठा mtd_info *master = mtd_get_master(mtd);

	अगर (!master->_unpoपूर्णांक)
		वापस -EOPNOTSUPP;
	अगर (from < 0 || from >= mtd->size || len > mtd->size - from)
		वापस -EINVAL;
	अगर (!len)
		वापस 0;
	वापस master->_unpoपूर्णांक(master, mtd_get_master_ofs(mtd, from), len);
पूर्ण
EXPORT_SYMBOL_GPL(mtd_unpoपूर्णांक);

/*
 * Allow NOMMU mmap() to directly map the device (अगर not शून्य)
 * - वापस the address to which the offset maps
 * - वापस -ENOSYS to indicate refusal to करो the mapping
 */
अचिन्हित दीर्घ mtd_get_unmapped_area(काष्ठा mtd_info *mtd, अचिन्हित दीर्घ len,
				    अचिन्हित दीर्घ offset, अचिन्हित दीर्घ flags)
अणु
	माप_प्रकार retlen;
	व्योम *virt;
	पूर्णांक ret;

	ret = mtd_poपूर्णांक(mtd, offset, len, &retlen, &virt, शून्य);
	अगर (ret)
		वापस ret;
	अगर (retlen != len) अणु
		mtd_unpoपूर्णांक(mtd, offset, retlen);
		वापस -ENOSYS;
	पूर्ण
	वापस (अचिन्हित दीर्घ)virt;
पूर्ण
EXPORT_SYMBOL_GPL(mtd_get_unmapped_area);

अटल व्योम mtd_update_ecc_stats(काष्ठा mtd_info *mtd, काष्ठा mtd_info *master,
				 स्थिर काष्ठा mtd_ecc_stats *old_stats)
अणु
	काष्ठा mtd_ecc_stats dअगरf;

	अगर (master == mtd)
		वापस;

	dअगरf = master->ecc_stats;
	dअगरf.failed -= old_stats->failed;
	dअगरf.corrected -= old_stats->corrected;

	जबतक (mtd->parent) अणु
		mtd->ecc_stats.failed += dअगरf.failed;
		mtd->ecc_stats.corrected += dअगरf.corrected;
		mtd = mtd->parent;
	पूर्ण
पूर्ण

पूर्णांक mtd_पढ़ो(काष्ठा mtd_info *mtd, loff_t from, माप_प्रकार len, माप_प्रकार *retlen,
	     u_अक्षर *buf)
अणु
	काष्ठा mtd_oob_ops ops = अणु
		.len = len,
		.datbuf = buf,
	पूर्ण;
	पूर्णांक ret;

	ret = mtd_पढ़ो_oob(mtd, from, &ops);
	*retlen = ops.retlen;

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(mtd_पढ़ो);

पूर्णांक mtd_ग_लिखो(काष्ठा mtd_info *mtd, loff_t to, माप_प्रकार len, माप_प्रकार *retlen,
	      स्थिर u_अक्षर *buf)
अणु
	काष्ठा mtd_oob_ops ops = अणु
		.len = len,
		.datbuf = (u8 *)buf,
	पूर्ण;
	पूर्णांक ret;

	ret = mtd_ग_लिखो_oob(mtd, to, &ops);
	*retlen = ops.retlen;

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(mtd_ग_लिखो);

/*
 * In blackbox flight recorder like scenarios we want to make successful ग_लिखोs
 * in पूर्णांकerrupt context. panic_ग_लिखो() is only पूर्णांकended to be called when its
 * known the kernel is about to panic and we need the ग_लिखो to succeed. Since
 * the kernel is not going to be running क्रम much दीर्घer, this function can
 * अवरोध locks and delay to ensure the ग_लिखो succeeds (but not sleep).
 */
पूर्णांक mtd_panic_ग_लिखो(काष्ठा mtd_info *mtd, loff_t to, माप_प्रकार len, माप_प्रकार *retlen,
		    स्थिर u_अक्षर *buf)
अणु
	काष्ठा mtd_info *master = mtd_get_master(mtd);

	*retlen = 0;
	अगर (!master->_panic_ग_लिखो)
		वापस -EOPNOTSUPP;
	अगर (to < 0 || to >= mtd->size || len > mtd->size - to)
		वापस -EINVAL;
	अगर (!(mtd->flags & MTD_WRITEABLE))
		वापस -EROFS;
	अगर (!len)
		वापस 0;
	अगर (!master->oops_panic_ग_लिखो)
		master->oops_panic_ग_लिखो = true;

	वापस master->_panic_ग_लिखो(master, mtd_get_master_ofs(mtd, to), len,
				    retlen, buf);
पूर्ण
EXPORT_SYMBOL_GPL(mtd_panic_ग_लिखो);

अटल पूर्णांक mtd_check_oob_ops(काष्ठा mtd_info *mtd, loff_t offs,
			     काष्ठा mtd_oob_ops *ops)
अणु
	/*
	 * Some users are setting ->datbuf or ->oobbuf to शून्य, but are leaving
	 * ->len or ->ooblen uninitialized. Force ->len and ->ooblen to 0 in
	 *  this हाल.
	 */
	अगर (!ops->datbuf)
		ops->len = 0;

	अगर (!ops->oobbuf)
		ops->ooblen = 0;

	अगर (offs < 0 || offs + ops->len > mtd->size)
		वापस -EINVAL;

	अगर (ops->ooblen) अणु
		माप_प्रकार maxooblen;

		अगर (ops->ooboffs >= mtd_oobavail(mtd, ops))
			वापस -EINVAL;

		maxooblen = ((माप_प्रकार)(mtd_भाग_by_ws(mtd->size, mtd) -
				      mtd_भाग_by_ws(offs, mtd)) *
			     mtd_oobavail(mtd, ops)) - ops->ooboffs;
		अगर (ops->ooblen > maxooblen)
			वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mtd_पढ़ो_oob_std(काष्ठा mtd_info *mtd, loff_t from,
			    काष्ठा mtd_oob_ops *ops)
अणु
	काष्ठा mtd_info *master = mtd_get_master(mtd);
	पूर्णांक ret;

	from = mtd_get_master_ofs(mtd, from);
	अगर (master->_पढ़ो_oob)
		ret = master->_पढ़ो_oob(master, from, ops);
	अन्यथा
		ret = master->_पढ़ो(master, from, ops->len, &ops->retlen,
				    ops->datbuf);

	वापस ret;
पूर्ण

अटल पूर्णांक mtd_ग_लिखो_oob_std(काष्ठा mtd_info *mtd, loff_t to,
			     काष्ठा mtd_oob_ops *ops)
अणु
	काष्ठा mtd_info *master = mtd_get_master(mtd);
	पूर्णांक ret;

	to = mtd_get_master_ofs(mtd, to);
	अगर (master->_ग_लिखो_oob)
		ret = master->_ग_लिखो_oob(master, to, ops);
	अन्यथा
		ret = master->_ग_लिखो(master, to, ops->len, &ops->retlen,
				     ops->datbuf);

	वापस ret;
पूर्ण

अटल पूर्णांक mtd_io_emulated_slc(काष्ठा mtd_info *mtd, loff_t start, bool पढ़ो,
			       काष्ठा mtd_oob_ops *ops)
अणु
	काष्ठा mtd_info *master = mtd_get_master(mtd);
	पूर्णांक ngroups = mtd_pairing_groups(master);
	पूर्णांक npairs = mtd_wunit_per_eb(master) / ngroups;
	काष्ठा mtd_oob_ops adjops = *ops;
	अचिन्हित पूर्णांक wunit, oobavail;
	काष्ठा mtd_pairing_info info;
	पूर्णांक max_bitflips = 0;
	u32 ebofs, pageofs;
	loff_t base, pos;

	ebofs = mtd_mod_by_eb(start, mtd);
	base = (loff_t)mtd_भाग_by_eb(start, mtd) * master->erasesize;
	info.group = 0;
	info.pair = mtd_भाग_by_ws(ebofs, mtd);
	pageofs = mtd_mod_by_ws(ebofs, mtd);
	oobavail = mtd_oobavail(mtd, ops);

	जबतक (ops->retlen < ops->len || ops->oobretlen < ops->ooblen) अणु
		पूर्णांक ret;

		अगर (info.pair >= npairs) अणु
			info.pair = 0;
			base += master->erasesize;
		पूर्ण

		wunit = mtd_pairing_info_to_wunit(master, &info);
		pos = mtd_wunit_to_offset(mtd, base, wunit);

		adjops.len = ops->len - ops->retlen;
		अगर (adjops.len > mtd->ग_लिखोsize - pageofs)
			adjops.len = mtd->ग_लिखोsize - pageofs;

		adjops.ooblen = ops->ooblen - ops->oobretlen;
		अगर (adjops.ooblen > oobavail - adjops.ooboffs)
			adjops.ooblen = oobavail - adjops.ooboffs;

		अगर (पढ़ो) अणु
			ret = mtd_पढ़ो_oob_std(mtd, pos + pageofs, &adjops);
			अगर (ret > 0)
				max_bitflips = max(max_bitflips, ret);
		पूर्ण अन्यथा अणु
			ret = mtd_ग_लिखो_oob_std(mtd, pos + pageofs, &adjops);
		पूर्ण

		अगर (ret < 0)
			वापस ret;

		max_bitflips = max(max_bitflips, ret);
		ops->retlen += adjops.retlen;
		ops->oobretlen += adjops.oobretlen;
		adjops.datbuf += adjops.retlen;
		adjops.oobbuf += adjops.oobretlen;
		adjops.ooboffs = 0;
		pageofs = 0;
		info.pair++;
	पूर्ण

	वापस max_bitflips;
पूर्ण

पूर्णांक mtd_पढ़ो_oob(काष्ठा mtd_info *mtd, loff_t from, काष्ठा mtd_oob_ops *ops)
अणु
	काष्ठा mtd_info *master = mtd_get_master(mtd);
	काष्ठा mtd_ecc_stats old_stats = master->ecc_stats;
	पूर्णांक ret_code;

	ops->retlen = ops->oobretlen = 0;

	ret_code = mtd_check_oob_ops(mtd, from, ops);
	अगर (ret_code)
		वापस ret_code;

	ledtrig_mtd_activity();

	/* Check the validity of a potential fallback on mtd->_पढ़ो */
	अगर (!master->_पढ़ो_oob && (!master->_पढ़ो || ops->oobbuf))
		वापस -EOPNOTSUPP;

	अगर (mtd->flags & MTD_SLC_ON_MLC_EMULATION)
		ret_code = mtd_io_emulated_slc(mtd, from, true, ops);
	अन्यथा
		ret_code = mtd_पढ़ो_oob_std(mtd, from, ops);

	mtd_update_ecc_stats(mtd, master, &old_stats);

	/*
	 * In हालs where ops->datbuf != शून्य, mtd->_पढ़ो_oob() has semantics
	 * similar to mtd->_पढ़ो(), वापसing a non-negative पूर्णांकeger
	 * representing max bitflips. In other हालs, mtd->_पढ़ो_oob() may
	 * वापस -EUCLEAN. In all हालs, perक्रमm similar logic to mtd_पढ़ो().
	 */
	अगर (unlikely(ret_code < 0))
		वापस ret_code;
	अगर (mtd->ecc_strength == 0)
		वापस 0;	/* device lacks ecc */
	वापस ret_code >= mtd->bitflip_threshold ? -EUCLEAN : 0;
पूर्ण
EXPORT_SYMBOL_GPL(mtd_पढ़ो_oob);

पूर्णांक mtd_ग_लिखो_oob(काष्ठा mtd_info *mtd, loff_t to,
				काष्ठा mtd_oob_ops *ops)
अणु
	काष्ठा mtd_info *master = mtd_get_master(mtd);
	पूर्णांक ret;

	ops->retlen = ops->oobretlen = 0;

	अगर (!(mtd->flags & MTD_WRITEABLE))
		वापस -EROFS;

	ret = mtd_check_oob_ops(mtd, to, ops);
	अगर (ret)
		वापस ret;

	ledtrig_mtd_activity();

	/* Check the validity of a potential fallback on mtd->_ग_लिखो */
	अगर (!master->_ग_लिखो_oob && (!master->_ग_लिखो || ops->oobbuf))
		वापस -EOPNOTSUPP;

	अगर (mtd->flags & MTD_SLC_ON_MLC_EMULATION)
		वापस mtd_io_emulated_slc(mtd, to, false, ops);

	वापस mtd_ग_लिखो_oob_std(mtd, to, ops);
पूर्ण
EXPORT_SYMBOL_GPL(mtd_ग_लिखो_oob);

/**
 * mtd_ooblayout_ecc - Get the OOB region definition of a specअगरic ECC section
 * @mtd: MTD device काष्ठाure
 * @section: ECC section. Depending on the layout you may have all the ECC
 *	     bytes stored in a single contiguous section, or one section
 *	     per ECC chunk (and someसमय several sections क्रम a single ECC
 *	     ECC chunk)
 * @oobecc: OOB region काष्ठा filled with the appropriate ECC position
 *	    inक्रमmation
 *
 * This function वापसs ECC section inक्रमmation in the OOB area. If you want
 * to get all the ECC bytes inक्रमmation, then you should call
 * mtd_ooblayout_ecc(mtd, section++, oobecc) until it वापसs -दुस्फल.
 *
 * Returns zero on success, a negative error code otherwise.
 */
पूर्णांक mtd_ooblayout_ecc(काष्ठा mtd_info *mtd, पूर्णांक section,
		      काष्ठा mtd_oob_region *oobecc)
अणु
	काष्ठा mtd_info *master = mtd_get_master(mtd);

	स_रखो(oobecc, 0, माप(*oobecc));

	अगर (!master || section < 0)
		वापस -EINVAL;

	अगर (!master->ooblayout || !master->ooblayout->ecc)
		वापस -ENOTSUPP;

	वापस master->ooblayout->ecc(master, section, oobecc);
पूर्ण
EXPORT_SYMBOL_GPL(mtd_ooblayout_ecc);

/**
 * mtd_ooblayout_मुक्त - Get the OOB region definition of a specअगरic मुक्त
 *			section
 * @mtd: MTD device काष्ठाure
 * @section: Free section you are पूर्णांकerested in. Depending on the layout
 *	     you may have all the मुक्त bytes stored in a single contiguous
 *	     section, or one section per ECC chunk plus an extra section
 *	     क्रम the reमुख्यing bytes (or other funky layout).
 * @oobमुक्त: OOB region काष्ठा filled with the appropriate मुक्त position
 *	     inक्रमmation
 *
 * This function वापसs मुक्त bytes position in the OOB area. If you want
 * to get all the मुक्त bytes inक्रमmation, then you should call
 * mtd_ooblayout_मुक्त(mtd, section++, oobमुक्त) until it वापसs -दुस्फल.
 *
 * Returns zero on success, a negative error code otherwise.
 */
पूर्णांक mtd_ooblayout_मुक्त(काष्ठा mtd_info *mtd, पूर्णांक section,
		       काष्ठा mtd_oob_region *oobमुक्त)
अणु
	काष्ठा mtd_info *master = mtd_get_master(mtd);

	स_रखो(oobमुक्त, 0, माप(*oobमुक्त));

	अगर (!master || section < 0)
		वापस -EINVAL;

	अगर (!master->ooblayout || !master->ooblayout->मुक्त)
		वापस -ENOTSUPP;

	वापस master->ooblayout->मुक्त(master, section, oobमुक्त);
पूर्ण
EXPORT_SYMBOL_GPL(mtd_ooblayout_मुक्त);

/**
 * mtd_ooblayout_find_region - Find the region attached to a specअगरic byte
 * @mtd: mtd info काष्ठाure
 * @byte: the byte we are searching क्रम
 * @sectionp: poपूर्णांकer where the section id will be stored
 * @oobregion: used to retrieve the ECC position
 * @iter: iterator function. Should be either mtd_ooblayout_मुक्त or
 *	  mtd_ooblayout_ecc depending on the region type you're searching क्रम
 *
 * This function वापसs the section id and oobregion inक्रमmation of a
 * specअगरic byte. For example, say you want to know where the 4th ECC byte is
 * stored, you'll use:
 *
 * mtd_ooblayout_find_region(mtd, 3, &section, &oobregion, mtd_ooblayout_ecc);
 *
 * Returns zero on success, a negative error code otherwise.
 */
अटल पूर्णांक mtd_ooblayout_find_region(काष्ठा mtd_info *mtd, पूर्णांक byte,
				पूर्णांक *sectionp, काष्ठा mtd_oob_region *oobregion,
				पूर्णांक (*iter)(काष्ठा mtd_info *,
					    पूर्णांक section,
					    काष्ठा mtd_oob_region *oobregion))
अणु
	पूर्णांक pos = 0, ret, section = 0;

	स_रखो(oobregion, 0, माप(*oobregion));

	जबतक (1) अणु
		ret = iter(mtd, section, oobregion);
		अगर (ret)
			वापस ret;

		अगर (pos + oobregion->length > byte)
			अवरोध;

		pos += oobregion->length;
		section++;
	पूर्ण

	/*
	 * Adjust region info to make it start at the beginning at the
	 * 'start' ECC byte.
	 */
	oobregion->offset += byte - pos;
	oobregion->length -= byte - pos;
	*sectionp = section;

	वापस 0;
पूर्ण

/**
 * mtd_ooblayout_find_eccregion - Find the ECC region attached to a specअगरic
 *				  ECC byte
 * @mtd: mtd info काष्ठाure
 * @eccbyte: the byte we are searching क्रम
 * @section: poपूर्णांकer where the section id will be stored
 * @oobregion: OOB region inक्रमmation
 *
 * Works like mtd_ooblayout_find_region() except it searches क्रम a specअगरic ECC
 * byte.
 *
 * Returns zero on success, a negative error code otherwise.
 */
पूर्णांक mtd_ooblayout_find_eccregion(काष्ठा mtd_info *mtd, पूर्णांक eccbyte,
				 पूर्णांक *section,
				 काष्ठा mtd_oob_region *oobregion)
अणु
	वापस mtd_ooblayout_find_region(mtd, eccbyte, section, oobregion,
					 mtd_ooblayout_ecc);
पूर्ण
EXPORT_SYMBOL_GPL(mtd_ooblayout_find_eccregion);

/**
 * mtd_ooblayout_get_bytes - Extract OOB bytes from the oob buffer
 * @mtd: mtd info काष्ठाure
 * @buf: destination buffer to store OOB bytes
 * @oobbuf: OOB buffer
 * @start: first byte to retrieve
 * @nbytes: number of bytes to retrieve
 * @iter: section iterator
 *
 * Extract bytes attached to a specअगरic category (ECC or मुक्त)
 * from the OOB buffer and copy them पूर्णांकo buf.
 *
 * Returns zero on success, a negative error code otherwise.
 */
अटल पूर्णांक mtd_ooblayout_get_bytes(काष्ठा mtd_info *mtd, u8 *buf,
				स्थिर u8 *oobbuf, पूर्णांक start, पूर्णांक nbytes,
				पूर्णांक (*iter)(काष्ठा mtd_info *,
					    पूर्णांक section,
					    काष्ठा mtd_oob_region *oobregion))
अणु
	काष्ठा mtd_oob_region oobregion;
	पूर्णांक section, ret;

	ret = mtd_ooblayout_find_region(mtd, start, &section,
					&oobregion, iter);

	जबतक (!ret) अणु
		पूर्णांक cnt;

		cnt = min_t(पूर्णांक, nbytes, oobregion.length);
		स_नकल(buf, oobbuf + oobregion.offset, cnt);
		buf += cnt;
		nbytes -= cnt;

		अगर (!nbytes)
			अवरोध;

		ret = iter(mtd, ++section, &oobregion);
	पूर्ण

	वापस ret;
पूर्ण

/**
 * mtd_ooblayout_set_bytes - put OOB bytes पूर्णांकo the oob buffer
 * @mtd: mtd info काष्ठाure
 * @buf: source buffer to get OOB bytes from
 * @oobbuf: OOB buffer
 * @start: first OOB byte to set
 * @nbytes: number of OOB bytes to set
 * @iter: section iterator
 *
 * Fill the OOB buffer with data provided in buf. The category (ECC or मुक्त)
 * is selected by passing the appropriate iterator.
 *
 * Returns zero on success, a negative error code otherwise.
 */
अटल पूर्णांक mtd_ooblayout_set_bytes(काष्ठा mtd_info *mtd, स्थिर u8 *buf,
				u8 *oobbuf, पूर्णांक start, पूर्णांक nbytes,
				पूर्णांक (*iter)(काष्ठा mtd_info *,
					    पूर्णांक section,
					    काष्ठा mtd_oob_region *oobregion))
अणु
	काष्ठा mtd_oob_region oobregion;
	पूर्णांक section, ret;

	ret = mtd_ooblayout_find_region(mtd, start, &section,
					&oobregion, iter);

	जबतक (!ret) अणु
		पूर्णांक cnt;

		cnt = min_t(पूर्णांक, nbytes, oobregion.length);
		स_नकल(oobbuf + oobregion.offset, buf, cnt);
		buf += cnt;
		nbytes -= cnt;

		अगर (!nbytes)
			अवरोध;

		ret = iter(mtd, ++section, &oobregion);
	पूर्ण

	वापस ret;
पूर्ण

/**
 * mtd_ooblayout_count_bytes - count the number of bytes in a OOB category
 * @mtd: mtd info काष्ठाure
 * @iter: category iterator
 *
 * Count the number of bytes in a given category.
 *
 * Returns a positive value on success, a negative error code otherwise.
 */
अटल पूर्णांक mtd_ooblayout_count_bytes(काष्ठा mtd_info *mtd,
				पूर्णांक (*iter)(काष्ठा mtd_info *,
					    पूर्णांक section,
					    काष्ठा mtd_oob_region *oobregion))
अणु
	काष्ठा mtd_oob_region oobregion;
	पूर्णांक section = 0, ret, nbytes = 0;

	जबतक (1) अणु
		ret = iter(mtd, section++, &oobregion);
		अगर (ret) अणु
			अगर (ret == -दुस्फल)
				ret = nbytes;
			अवरोध;
		पूर्ण

		nbytes += oobregion.length;
	पूर्ण

	वापस ret;
पूर्ण

/**
 * mtd_ooblayout_get_eccbytes - extract ECC bytes from the oob buffer
 * @mtd: mtd info काष्ठाure
 * @eccbuf: destination buffer to store ECC bytes
 * @oobbuf: OOB buffer
 * @start: first ECC byte to retrieve
 * @nbytes: number of ECC bytes to retrieve
 *
 * Works like mtd_ooblayout_get_bytes(), except it acts on ECC bytes.
 *
 * Returns zero on success, a negative error code otherwise.
 */
पूर्णांक mtd_ooblayout_get_eccbytes(काष्ठा mtd_info *mtd, u8 *eccbuf,
			       स्थिर u8 *oobbuf, पूर्णांक start, पूर्णांक nbytes)
अणु
	वापस mtd_ooblayout_get_bytes(mtd, eccbuf, oobbuf, start, nbytes,
				       mtd_ooblayout_ecc);
पूर्ण
EXPORT_SYMBOL_GPL(mtd_ooblayout_get_eccbytes);

/**
 * mtd_ooblayout_set_eccbytes - set ECC bytes पूर्णांकo the oob buffer
 * @mtd: mtd info काष्ठाure
 * @eccbuf: source buffer to get ECC bytes from
 * @oobbuf: OOB buffer
 * @start: first ECC byte to set
 * @nbytes: number of ECC bytes to set
 *
 * Works like mtd_ooblayout_set_bytes(), except it acts on ECC bytes.
 *
 * Returns zero on success, a negative error code otherwise.
 */
पूर्णांक mtd_ooblayout_set_eccbytes(काष्ठा mtd_info *mtd, स्थिर u8 *eccbuf,
			       u8 *oobbuf, पूर्णांक start, पूर्णांक nbytes)
अणु
	वापस mtd_ooblayout_set_bytes(mtd, eccbuf, oobbuf, start, nbytes,
				       mtd_ooblayout_ecc);
पूर्ण
EXPORT_SYMBOL_GPL(mtd_ooblayout_set_eccbytes);

/**
 * mtd_ooblayout_get_databytes - extract data bytes from the oob buffer
 * @mtd: mtd info काष्ठाure
 * @databuf: destination buffer to store ECC bytes
 * @oobbuf: OOB buffer
 * @start: first ECC byte to retrieve
 * @nbytes: number of ECC bytes to retrieve
 *
 * Works like mtd_ooblayout_get_bytes(), except it acts on मुक्त bytes.
 *
 * Returns zero on success, a negative error code otherwise.
 */
पूर्णांक mtd_ooblayout_get_databytes(काष्ठा mtd_info *mtd, u8 *databuf,
				स्थिर u8 *oobbuf, पूर्णांक start, पूर्णांक nbytes)
अणु
	वापस mtd_ooblayout_get_bytes(mtd, databuf, oobbuf, start, nbytes,
				       mtd_ooblayout_मुक्त);
पूर्ण
EXPORT_SYMBOL_GPL(mtd_ooblayout_get_databytes);

/**
 * mtd_ooblayout_set_databytes - set data bytes पूर्णांकo the oob buffer
 * @mtd: mtd info काष्ठाure
 * @databuf: source buffer to get data bytes from
 * @oobbuf: OOB buffer
 * @start: first ECC byte to set
 * @nbytes: number of ECC bytes to set
 *
 * Works like mtd_ooblayout_set_bytes(), except it acts on मुक्त bytes.
 *
 * Returns zero on success, a negative error code otherwise.
 */
पूर्णांक mtd_ooblayout_set_databytes(काष्ठा mtd_info *mtd, स्थिर u8 *databuf,
				u8 *oobbuf, पूर्णांक start, पूर्णांक nbytes)
अणु
	वापस mtd_ooblayout_set_bytes(mtd, databuf, oobbuf, start, nbytes,
				       mtd_ooblayout_मुक्त);
पूर्ण
EXPORT_SYMBOL_GPL(mtd_ooblayout_set_databytes);

/**
 * mtd_ooblayout_count_मुक्तbytes - count the number of मुक्त bytes in OOB
 * @mtd: mtd info काष्ठाure
 *
 * Works like mtd_ooblayout_count_bytes(), except it count मुक्त bytes.
 *
 * Returns zero on success, a negative error code otherwise.
 */
पूर्णांक mtd_ooblayout_count_मुक्तbytes(काष्ठा mtd_info *mtd)
अणु
	वापस mtd_ooblayout_count_bytes(mtd, mtd_ooblayout_मुक्त);
पूर्ण
EXPORT_SYMBOL_GPL(mtd_ooblayout_count_मुक्तbytes);

/**
 * mtd_ooblayout_count_eccbytes - count the number of ECC bytes in OOB
 * @mtd: mtd info काष्ठाure
 *
 * Works like mtd_ooblayout_count_bytes(), except it count ECC bytes.
 *
 * Returns zero on success, a negative error code otherwise.
 */
पूर्णांक mtd_ooblayout_count_eccbytes(काष्ठा mtd_info *mtd)
अणु
	वापस mtd_ooblayout_count_bytes(mtd, mtd_ooblayout_ecc);
पूर्ण
EXPORT_SYMBOL_GPL(mtd_ooblayout_count_eccbytes);

/*
 * Method to access the protection रेजिस्टर area, present in some flash
 * devices. The user data is one समय programmable but the factory data is पढ़ो
 * only.
 */
पूर्णांक mtd_get_fact_prot_info(काष्ठा mtd_info *mtd, माप_प्रकार len, माप_प्रकार *retlen,
			   काष्ठा otp_info *buf)
अणु
	काष्ठा mtd_info *master = mtd_get_master(mtd);

	अगर (!master->_get_fact_prot_info)
		वापस -EOPNOTSUPP;
	अगर (!len)
		वापस 0;
	वापस master->_get_fact_prot_info(master, len, retlen, buf);
पूर्ण
EXPORT_SYMBOL_GPL(mtd_get_fact_prot_info);

पूर्णांक mtd_पढ़ो_fact_prot_reg(काष्ठा mtd_info *mtd, loff_t from, माप_प्रकार len,
			   माप_प्रकार *retlen, u_अक्षर *buf)
अणु
	काष्ठा mtd_info *master = mtd_get_master(mtd);

	*retlen = 0;
	अगर (!master->_पढ़ो_fact_prot_reg)
		वापस -EOPNOTSUPP;
	अगर (!len)
		वापस 0;
	वापस master->_पढ़ो_fact_prot_reg(master, from, len, retlen, buf);
पूर्ण
EXPORT_SYMBOL_GPL(mtd_पढ़ो_fact_prot_reg);

पूर्णांक mtd_get_user_prot_info(काष्ठा mtd_info *mtd, माप_प्रकार len, माप_प्रकार *retlen,
			   काष्ठा otp_info *buf)
अणु
	काष्ठा mtd_info *master = mtd_get_master(mtd);

	अगर (!master->_get_user_prot_info)
		वापस -EOPNOTSUPP;
	अगर (!len)
		वापस 0;
	वापस master->_get_user_prot_info(master, len, retlen, buf);
पूर्ण
EXPORT_SYMBOL_GPL(mtd_get_user_prot_info);

पूर्णांक mtd_पढ़ो_user_prot_reg(काष्ठा mtd_info *mtd, loff_t from, माप_प्रकार len,
			   माप_प्रकार *retlen, u_अक्षर *buf)
अणु
	काष्ठा mtd_info *master = mtd_get_master(mtd);

	*retlen = 0;
	अगर (!master->_पढ़ो_user_prot_reg)
		वापस -EOPNOTSUPP;
	अगर (!len)
		वापस 0;
	वापस master->_पढ़ो_user_prot_reg(master, from, len, retlen, buf);
पूर्ण
EXPORT_SYMBOL_GPL(mtd_पढ़ो_user_prot_reg);

पूर्णांक mtd_ग_लिखो_user_prot_reg(काष्ठा mtd_info *mtd, loff_t to, माप_प्रकार len,
			    माप_प्रकार *retlen, स्थिर u_अक्षर *buf)
अणु
	काष्ठा mtd_info *master = mtd_get_master(mtd);
	पूर्णांक ret;

	*retlen = 0;
	अगर (!master->_ग_लिखो_user_prot_reg)
		वापस -EOPNOTSUPP;
	अगर (!len)
		वापस 0;
	ret = master->_ग_लिखो_user_prot_reg(master, to, len, retlen, buf);
	अगर (ret)
		वापस ret;

	/*
	 * If no data could be written at all, we are out of memory and
	 * must वापस -ENOSPC.
	 */
	वापस (*retlen) ? 0 : -ENOSPC;
पूर्ण
EXPORT_SYMBOL_GPL(mtd_ग_लिखो_user_prot_reg);

पूर्णांक mtd_lock_user_prot_reg(काष्ठा mtd_info *mtd, loff_t from, माप_प्रकार len)
अणु
	काष्ठा mtd_info *master = mtd_get_master(mtd);

	अगर (!master->_lock_user_prot_reg)
		वापस -EOPNOTSUPP;
	अगर (!len)
		वापस 0;
	वापस master->_lock_user_prot_reg(master, from, len);
पूर्ण
EXPORT_SYMBOL_GPL(mtd_lock_user_prot_reg);

पूर्णांक mtd_erase_user_prot_reg(काष्ठा mtd_info *mtd, loff_t from, माप_प्रकार len)
अणु
	काष्ठा mtd_info *master = mtd_get_master(mtd);

	अगर (!master->_erase_user_prot_reg)
		वापस -EOPNOTSUPP;
	अगर (!len)
		वापस 0;
	वापस master->_erase_user_prot_reg(master, from, len);
पूर्ण
EXPORT_SYMBOL_GPL(mtd_erase_user_prot_reg);

/* Chip-supported device locking */
पूर्णांक mtd_lock(काष्ठा mtd_info *mtd, loff_t ofs, uपूर्णांक64_t len)
अणु
	काष्ठा mtd_info *master = mtd_get_master(mtd);

	अगर (!master->_lock)
		वापस -EOPNOTSUPP;
	अगर (ofs < 0 || ofs >= mtd->size || len > mtd->size - ofs)
		वापस -EINVAL;
	अगर (!len)
		वापस 0;

	अगर (mtd->flags & MTD_SLC_ON_MLC_EMULATION) अणु
		ofs = (loff_t)mtd_भाग_by_eb(ofs, mtd) * master->erasesize;
		len = (u64)mtd_भाग_by_eb(len, mtd) * master->erasesize;
	पूर्ण

	वापस master->_lock(master, mtd_get_master_ofs(mtd, ofs), len);
पूर्ण
EXPORT_SYMBOL_GPL(mtd_lock);

पूर्णांक mtd_unlock(काष्ठा mtd_info *mtd, loff_t ofs, uपूर्णांक64_t len)
अणु
	काष्ठा mtd_info *master = mtd_get_master(mtd);

	अगर (!master->_unlock)
		वापस -EOPNOTSUPP;
	अगर (ofs < 0 || ofs >= mtd->size || len > mtd->size - ofs)
		वापस -EINVAL;
	अगर (!len)
		वापस 0;

	अगर (mtd->flags & MTD_SLC_ON_MLC_EMULATION) अणु
		ofs = (loff_t)mtd_भाग_by_eb(ofs, mtd) * master->erasesize;
		len = (u64)mtd_भाग_by_eb(len, mtd) * master->erasesize;
	पूर्ण

	वापस master->_unlock(master, mtd_get_master_ofs(mtd, ofs), len);
पूर्ण
EXPORT_SYMBOL_GPL(mtd_unlock);

पूर्णांक mtd_is_locked(काष्ठा mtd_info *mtd, loff_t ofs, uपूर्णांक64_t len)
अणु
	काष्ठा mtd_info *master = mtd_get_master(mtd);

	अगर (!master->_is_locked)
		वापस -EOPNOTSUPP;
	अगर (ofs < 0 || ofs >= mtd->size || len > mtd->size - ofs)
		वापस -EINVAL;
	अगर (!len)
		वापस 0;

	अगर (mtd->flags & MTD_SLC_ON_MLC_EMULATION) अणु
		ofs = (loff_t)mtd_भाग_by_eb(ofs, mtd) * master->erasesize;
		len = (u64)mtd_भाग_by_eb(len, mtd) * master->erasesize;
	पूर्ण

	वापस master->_is_locked(master, mtd_get_master_ofs(mtd, ofs), len);
पूर्ण
EXPORT_SYMBOL_GPL(mtd_is_locked);

पूर्णांक mtd_block_isreserved(काष्ठा mtd_info *mtd, loff_t ofs)
अणु
	काष्ठा mtd_info *master = mtd_get_master(mtd);

	अगर (ofs < 0 || ofs >= mtd->size)
		वापस -EINVAL;
	अगर (!master->_block_isreserved)
		वापस 0;

	अगर (mtd->flags & MTD_SLC_ON_MLC_EMULATION)
		ofs = (loff_t)mtd_भाग_by_eb(ofs, mtd) * master->erasesize;

	वापस master->_block_isreserved(master, mtd_get_master_ofs(mtd, ofs));
पूर्ण
EXPORT_SYMBOL_GPL(mtd_block_isreserved);

पूर्णांक mtd_block_isbad(काष्ठा mtd_info *mtd, loff_t ofs)
अणु
	काष्ठा mtd_info *master = mtd_get_master(mtd);

	अगर (ofs < 0 || ofs >= mtd->size)
		वापस -EINVAL;
	अगर (!master->_block_isbad)
		वापस 0;

	अगर (mtd->flags & MTD_SLC_ON_MLC_EMULATION)
		ofs = (loff_t)mtd_भाग_by_eb(ofs, mtd) * master->erasesize;

	वापस master->_block_isbad(master, mtd_get_master_ofs(mtd, ofs));
पूर्ण
EXPORT_SYMBOL_GPL(mtd_block_isbad);

पूर्णांक mtd_block_markbad(काष्ठा mtd_info *mtd, loff_t ofs)
अणु
	काष्ठा mtd_info *master = mtd_get_master(mtd);
	पूर्णांक ret;

	अगर (!master->_block_markbad)
		वापस -EOPNOTSUPP;
	अगर (ofs < 0 || ofs >= mtd->size)
		वापस -EINVAL;
	अगर (!(mtd->flags & MTD_WRITEABLE))
		वापस -EROFS;

	अगर (mtd->flags & MTD_SLC_ON_MLC_EMULATION)
		ofs = (loff_t)mtd_भाग_by_eb(ofs, mtd) * master->erasesize;

	ret = master->_block_markbad(master, mtd_get_master_ofs(mtd, ofs));
	अगर (ret)
		वापस ret;

	जबतक (mtd->parent) अणु
		mtd->ecc_stats.badblocks++;
		mtd = mtd->parent;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(mtd_block_markbad);

/*
 * शेष_mtd_ग_लिखोv - the शेष ग_लिखोv method
 * @mtd: mtd device description object poपूर्णांकer
 * @vecs: the vectors to ग_लिखो
 * @count: count of vectors in @vecs
 * @to: the MTD device offset to ग_लिखो to
 * @retlen: on निकास contains the count of bytes written to the MTD device.
 *
 * This function वापसs zero in हाल of success and a negative error code in
 * हाल of failure.
 */
अटल पूर्णांक शेष_mtd_ग_लिखोv(काष्ठा mtd_info *mtd, स्थिर काष्ठा kvec *vecs,
			      अचिन्हित दीर्घ count, loff_t to, माप_प्रकार *retlen)
अणु
	अचिन्हित दीर्घ i;
	माप_प्रकार totlen = 0, thislen;
	पूर्णांक ret = 0;

	क्रम (i = 0; i < count; i++) अणु
		अगर (!vecs[i].iov_len)
			जारी;
		ret = mtd_ग_लिखो(mtd, to, vecs[i].iov_len, &thislen,
				vecs[i].iov_base);
		totlen += thislen;
		अगर (ret || thislen != vecs[i].iov_len)
			अवरोध;
		to += vecs[i].iov_len;
	पूर्ण
	*retlen = totlen;
	वापस ret;
पूर्ण

/*
 * mtd_ग_लिखोv - the vector-based MTD ग_लिखो method
 * @mtd: mtd device description object poपूर्णांकer
 * @vecs: the vectors to ग_लिखो
 * @count: count of vectors in @vecs
 * @to: the MTD device offset to ग_लिखो to
 * @retlen: on निकास contains the count of bytes written to the MTD device.
 *
 * This function वापसs zero in हाल of success and a negative error code in
 * हाल of failure.
 */
पूर्णांक mtd_ग_लिखोv(काष्ठा mtd_info *mtd, स्थिर काष्ठा kvec *vecs,
	       अचिन्हित दीर्घ count, loff_t to, माप_प्रकार *retlen)
अणु
	काष्ठा mtd_info *master = mtd_get_master(mtd);

	*retlen = 0;
	अगर (!(mtd->flags & MTD_WRITEABLE))
		वापस -EROFS;

	अगर (!master->_ग_लिखोv)
		वापस शेष_mtd_ग_लिखोv(mtd, vecs, count, to, retlen);

	वापस master->_ग_लिखोv(master, vecs, count,
			       mtd_get_master_ofs(mtd, to), retlen);
पूर्ण
EXPORT_SYMBOL_GPL(mtd_ग_लिखोv);

/**
 * mtd_kदो_स्मृति_up_to - allocate a contiguous buffer up to the specअगरied size
 * @mtd: mtd device description object poपूर्णांकer
 * @size: a poपूर्णांकer to the ideal or maximum size of the allocation, poपूर्णांकs
 *        to the actual allocation size on success.
 *
 * This routine attempts to allocate a contiguous kernel buffer up to
 * the specअगरied size, backing off the size of the request exponentially
 * until the request succeeds or until the allocation size falls below
 * the प्रणाली page size. This attempts to make sure it करोes not adversely
 * impact प्रणाली perक्रमmance, so when allocating more than one page, we
 * ask the memory allocator to aव्योम re-trying, swapping, writing back
 * or perक्रमming I/O.
 *
 * Note, this function also makes sure that the allocated buffer is aligned to
 * the MTD device's min. I/O unit, i.e. the "mtd->writesize" value.
 *
 * This is called, क्रम example by mtd_अणुपढ़ो,ग_लिखोपूर्ण and jffs2_scan_medium,
 * to handle smaller (i.e. degraded) buffer allocations under low- or
 * fragmented-memory situations where such reduced allocations, from a
 * requested ideal, are allowed.
 *
 * Returns a poपूर्णांकer to the allocated buffer on success; otherwise, शून्य.
 */
व्योम *mtd_kदो_स्मृति_up_to(स्थिर काष्ठा mtd_info *mtd, माप_प्रकार *size)
अणु
	gfp_t flags = __GFP_NOWARN | __GFP_सूचीECT_RECLAIM | __GFP_NORETRY;
	माप_प्रकार min_alloc = max_t(माप_प्रकार, mtd->ग_लिखोsize, PAGE_SIZE);
	व्योम *kbuf;

	*size = min_t(माप_प्रकार, *size, KMALLOC_MAX_SIZE);

	जबतक (*size > min_alloc) अणु
		kbuf = kदो_स्मृति(*size, flags);
		अगर (kbuf)
			वापस kbuf;

		*size >>= 1;
		*size = ALIGN(*size, mtd->ग_लिखोsize);
	पूर्ण

	/*
	 * For the last resort allocation allow 'kmalloc()' to करो all sorts of
	 * things (ग_लिखो-back, dropping caches, etc) by using GFP_KERNEL.
	 */
	वापस kदो_स्मृति(*size, GFP_KERNEL);
पूर्ण
EXPORT_SYMBOL_GPL(mtd_kदो_स्मृति_up_to);

#अगर_घोषित CONFIG_PROC_FS

/*====================================================================*/
/* Support क्रम /proc/mtd */

अटल पूर्णांक mtd_proc_show(काष्ठा seq_file *m, व्योम *v)
अणु
	काष्ठा mtd_info *mtd;

	seq_माला_दो(m, "dev:    size   erasesize  name\n");
	mutex_lock(&mtd_table_mutex);
	mtd_क्रम_each_device(mtd) अणु
		seq_म_लिखो(m, "mtd%d: %8.8llx %8.8x \"%s\"\n",
			   mtd->index, (अचिन्हित दीर्घ दीर्घ)mtd->size,
			   mtd->erasesize, mtd->name);
	पूर्ण
	mutex_unlock(&mtd_table_mutex);
	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_PROC_FS */

/*====================================================================*/
/* Init code */

अटल काष्ठा backing_dev_info * __init mtd_bdi_init(स्थिर अक्षर *name)
अणु
	काष्ठा backing_dev_info *bdi;
	पूर्णांक ret;

	bdi = bdi_alloc(NUMA_NO_NODE);
	अगर (!bdi)
		वापस ERR_PTR(-ENOMEM);
	bdi->ra_pages = 0;
	bdi->io_pages = 0;

	/*
	 * We put '-0' suffix to the name to get the same name क्रमmat as we
	 * used to get. Since this is called only once, we get a unique name. 
	 */
	ret = bdi_रेजिस्टर(bdi, "%.28s-0", name);
	अगर (ret)
		bdi_put(bdi);

	वापस ret ? ERR_PTR(ret) : bdi;
पूर्ण

अटल काष्ठा proc_dir_entry *proc_mtd;

अटल पूर्णांक __init init_mtd(व्योम)
अणु
	पूर्णांक ret;

	ret = class_रेजिस्टर(&mtd_class);
	अगर (ret)
		जाओ err_reg;

	mtd_bdi = mtd_bdi_init("mtd");
	अगर (IS_ERR(mtd_bdi)) अणु
		ret = PTR_ERR(mtd_bdi);
		जाओ err_bdi;
	पूर्ण

	proc_mtd = proc_create_single("mtd", 0, शून्य, mtd_proc_show);

	ret = init_mtdअक्षर();
	अगर (ret)
		जाओ out_procfs;

	dfs_dir_mtd = debugfs_create_dir("mtd", शून्य);

	वापस 0;

out_procfs:
	अगर (proc_mtd)
		हटाओ_proc_entry("mtd", शून्य);
	bdi_put(mtd_bdi);
err_bdi:
	class_unरेजिस्टर(&mtd_class);
err_reg:
	pr_err("Error registering mtd class or bdi: %d\n", ret);
	वापस ret;
पूर्ण

अटल व्योम __निकास cleanup_mtd(व्योम)
अणु
	debugfs_हटाओ_recursive(dfs_dir_mtd);
	cleanup_mtdअक्षर();
	अगर (proc_mtd)
		हटाओ_proc_entry("mtd", शून्य);
	class_unरेजिस्टर(&mtd_class);
	bdi_put(mtd_bdi);
	idr_destroy(&mtd_idr);
पूर्ण

module_init(init_mtd);
module_निकास(cleanup_mtd);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("David Woodhouse <dwmw2@infradead.org>");
MODULE_DESCRIPTION("Core MTD registration and access routines");
