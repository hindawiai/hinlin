<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Qualcomm Peripheral Image Loader helpers
 *
 * Copyright (C) 2016 Linaro Ltd
 * Copyright (C) 2015 Sony Mobile Communications Inc
 * Copyright (c) 2012-2013, The Linux Foundation. All rights reserved.
 */

#समावेश <linux/firmware.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/remoteproc.h>
#समावेश <linux/remoteproc/qcom_rproc.h>
#समावेश <linux/rpmsg/qcom_glink.h>
#समावेश <linux/rpmsg/qcom_smd.h>
#समावेश <linux/slab.h>
#समावेश <linux/soc/qcom/mdt_loader.h>
#समावेश <linux/soc/qcom/sस्मृति.स>

#समावेश "remoteproc_internal.h"
#समावेश "qcom_common.h"

#घोषणा to_glink_subdev(d) container_of(d, काष्ठा qcom_rproc_glink, subdev)
#घोषणा to_smd_subdev(d) container_of(d, काष्ठा qcom_rproc_subdev, subdev)
#घोषणा to_ssr_subdev(d) container_of(d, काष्ठा qcom_rproc_ssr, subdev)

#घोषणा MAX_NUM_OF_SS           10
#घोषणा MAX_REGION_NAME_LENGTH  16
#घोषणा SBL_MINIDUMP_SMEM_ID	602
#घोषणा MD_REGION_VALID		('V' << 24 | 'A' << 16 | 'L' << 8 | 'I' << 0)
#घोषणा MD_SS_ENCR_DONE		('D' << 24 | 'O' << 16 | 'N' << 8 | 'E' << 0)
#घोषणा MD_SS_ENABLED		('E' << 24 | 'N' << 16 | 'B' << 8 | 'L' << 0)

/**
 * काष्ठा minidump_region - Minidump region
 * @name		: Name of the region to be dumped
 * @seq_num:		: Use to dअगरferentiate regions with same name.
 * @valid		: This entry to be dumped (अगर set to 1)
 * @address		: Physical address of region to be dumped
 * @size		: Size of the region
 */
काष्ठा minidump_region अणु
	अक्षर	name[MAX_REGION_NAME_LENGTH];
	__le32	seq_num;
	__le32	valid;
	__le64	address;
	__le64	size;
पूर्ण;

/**
 * काष्ठा minidump_subप्रणाली_toc: Subप्रणाली's SMEM Table of content
 * @status : Subप्रणाली toc init status
 * @enabled : अगर set to 1, this region would be copied during coredump
 * @encryption_status: Encryption status क्रम this subप्रणाली
 * @encryption_required : Decides to encrypt the subप्रणाली regions or not
 * @region_count : Number of regions added in this subप्रणाली toc
 * @regions_baseptr : regions base poपूर्णांकer of the subप्रणाली
 */
काष्ठा minidump_subप्रणाली अणु
	__le32	status;
	__le32	enabled;
	__le32	encryption_status;
	__le32	encryption_required;
	__le32	region_count;
	__le64	regions_baseptr;
पूर्ण;

/**
 * काष्ठा minidump_global_toc: Global Table of Content
 * @status : Global Minidump init status
 * @md_revision : Minidump revision
 * @enabled : Minidump enable status
 * @subप्रणालीs : Array of subप्रणालीs toc
 */
काष्ठा minidump_global_toc अणु
	__le32				status;
	__le32				md_revision;
	__le32				enabled;
	काष्ठा minidump_subप्रणाली	subप्रणालीs[MAX_NUM_OF_SS];
पूर्ण;

काष्ठा qcom_ssr_subप्रणाली अणु
	स्थिर अक्षर *name;
	काष्ठा srcu_notअगरier_head notअगरier_list;
	काष्ठा list_head list;
पूर्ण;

अटल LIST_HEAD(qcom_ssr_subप्रणाली_list);
अटल DEFINE_MUTEX(qcom_ssr_subsys_lock);

अटल व्योम qcom_minidump_cleanup(काष्ठा rproc *rproc)
अणु
	काष्ठा rproc_dump_segment *entry, *पंचांगp;

	list_क्रम_each_entry_safe(entry, पंचांगp, &rproc->dump_segments, node) अणु
		list_del(&entry->node);
		kमुक्त(entry->priv);
		kमुक्त(entry);
	पूर्ण
पूर्ण

अटल पूर्णांक qcom_add_minidump_segments(काष्ठा rproc *rproc, काष्ठा minidump_subप्रणाली *subप्रणाली)
अणु
	काष्ठा minidump_region __iomem *ptr;
	काष्ठा minidump_region region;
	पूर्णांक seg_cnt, i;
	dma_addr_t da;
	माप_प्रकार size;
	अक्षर *name;

	अगर (WARN_ON(!list_empty(&rproc->dump_segments))) अणु
		dev_err(&rproc->dev, "dump segment list already populated\n");
		वापस -EUCLEAN;
	पूर्ण

	seg_cnt = le32_to_cpu(subप्रणाली->region_count);
	ptr = ioremap((अचिन्हित दीर्घ)le64_to_cpu(subप्रणाली->regions_baseptr),
		      seg_cnt * माप(काष्ठा minidump_region));
	अगर (!ptr)
		वापस -EFAULT;

	क्रम (i = 0; i < seg_cnt; i++) अणु
		स_नकल_fromio(&region, ptr + i, माप(region));
		अगर (region.valid == MD_REGION_VALID) अणु
			name = kstrdup(region.name, GFP_KERNEL);
			अगर (!name) अणु
				iounmap(ptr);
				वापस -ENOMEM;
			पूर्ण
			da = le64_to_cpu(region.address);
			size = le32_to_cpu(region.size);
			rproc_coredump_add_custom_segment(rproc, da, size, शून्य, name);
		पूर्ण
	पूर्ण

	iounmap(ptr);
	वापस 0;
पूर्ण

व्योम qcom_minidump(काष्ठा rproc *rproc, अचिन्हित पूर्णांक minidump_id)
अणु
	पूर्णांक ret;
	काष्ठा minidump_subप्रणाली *subप्रणाली;
	काष्ठा minidump_global_toc *toc;

	/* Get Global minidump ToC*/
	toc = qcom_smem_get(QCOM_SMEM_HOST_ANY, SBL_MINIDUMP_SMEM_ID, शून्य);

	/* check अगर global table poपूर्णांकer exists and init is set */
	अगर (IS_ERR(toc) || !toc->status) अणु
		dev_err(&rproc->dev, "Minidump TOC not found in SMEM\n");
		वापस;
	पूर्ण

	/* Get subप्रणाली table of contents using the minidump id */
	subप्रणाली = &toc->subप्रणालीs[minidump_id];

	/**
	 * Collect minidump अगर SS ToC is valid and segment table
	 * is initialized in memory and encryption status is set.
	 */
	अगर (subप्रणाली->regions_baseptr == 0 ||
	    le32_to_cpu(subप्रणाली->status) != 1 ||
	    le32_to_cpu(subप्रणाली->enabled) != MD_SS_ENABLED ||
	    le32_to_cpu(subप्रणाली->encryption_status) != MD_SS_ENCR_DONE) अणु
		dev_err(&rproc->dev, "Minidump not ready, skipping\n");
		वापस;
	पूर्ण

	ret = qcom_add_minidump_segments(rproc, subप्रणाली);
	अगर (ret) अणु
		dev_err(&rproc->dev, "Failed with error: %d while adding minidump entries\n", ret);
		जाओ clean_minidump;
	पूर्ण
	rproc_coredump_using_sections(rproc);
clean_minidump:
	qcom_minidump_cleanup(rproc);
पूर्ण
EXPORT_SYMBOL_GPL(qcom_minidump);

अटल पूर्णांक glink_subdev_start(काष्ठा rproc_subdev *subdev)
अणु
	काष्ठा qcom_rproc_glink *glink = to_glink_subdev(subdev);

	glink->edge = qcom_glink_smem_रेजिस्टर(glink->dev, glink->node);

	वापस PTR_ERR_OR_ZERO(glink->edge);
पूर्ण

अटल व्योम glink_subdev_stop(काष्ठा rproc_subdev *subdev, bool crashed)
अणु
	काष्ठा qcom_rproc_glink *glink = to_glink_subdev(subdev);

	qcom_glink_smem_unरेजिस्टर(glink->edge);
	glink->edge = शून्य;
पूर्ण

अटल व्योम glink_subdev_unprepare(काष्ठा rproc_subdev *subdev)
अणु
	काष्ठा qcom_rproc_glink *glink = to_glink_subdev(subdev);

	qcom_glink_ssr_notअगरy(glink->ssr_name);
पूर्ण

/**
 * qcom_add_glink_subdev() - try to add a GLINK subdevice to rproc
 * @rproc:	rproc handle to parent the subdevice
 * @glink:	reference to a GLINK subdev context
 * @ssr_name:	identअगरier of the associated remoteproc क्रम ssr notअगरications
 */
व्योम qcom_add_glink_subdev(काष्ठा rproc *rproc, काष्ठा qcom_rproc_glink *glink,
			   स्थिर अक्षर *ssr_name)
अणु
	काष्ठा device *dev = &rproc->dev;

	glink->node = of_get_child_by_name(dev->parent->of_node, "glink-edge");
	अगर (!glink->node)
		वापस;

	glink->ssr_name = kstrdup_स्थिर(ssr_name, GFP_KERNEL);
	अगर (!glink->ssr_name)
		वापस;

	glink->dev = dev;
	glink->subdev.start = glink_subdev_start;
	glink->subdev.stop = glink_subdev_stop;
	glink->subdev.unprepare = glink_subdev_unprepare;

	rproc_add_subdev(rproc, &glink->subdev);
पूर्ण
EXPORT_SYMBOL_GPL(qcom_add_glink_subdev);

/**
 * qcom_हटाओ_glink_subdev() - हटाओ a GLINK subdevice from rproc
 * @rproc:	rproc handle
 * @glink:	reference to a GLINK subdev context
 */
व्योम qcom_हटाओ_glink_subdev(काष्ठा rproc *rproc, काष्ठा qcom_rproc_glink *glink)
अणु
	अगर (!glink->node)
		वापस;

	rproc_हटाओ_subdev(rproc, &glink->subdev);
	kमुक्त_स्थिर(glink->ssr_name);
	of_node_put(glink->node);
पूर्ण
EXPORT_SYMBOL_GPL(qcom_हटाओ_glink_subdev);

/**
 * qcom_रेजिस्टर_dump_segments() - रेजिस्टर segments क्रम coredump
 * @rproc:	remoteproc handle
 * @fw:		firmware header
 *
 * Register all segments of the ELF in the remoteproc coredump segment list
 *
 * Return: 0 on success, negative त्रुटि_सं on failure.
 */
पूर्णांक qcom_रेजिस्टर_dump_segments(काष्ठा rproc *rproc,
				स्थिर काष्ठा firmware *fw)
अणु
	स्थिर काष्ठा elf32_phdr *phdrs;
	स्थिर काष्ठा elf32_phdr *phdr;
	स्थिर काष्ठा elf32_hdr *ehdr;
	पूर्णांक ret;
	पूर्णांक i;

	ehdr = (काष्ठा elf32_hdr *)fw->data;
	phdrs = (काष्ठा elf32_phdr *)(ehdr + 1);

	क्रम (i = 0; i < ehdr->e_phnum; i++) अणु
		phdr = &phdrs[i];

		अगर (phdr->p_type != PT_LOAD)
			जारी;

		अगर ((phdr->p_flags & QCOM_MDT_TYPE_MASK) == QCOM_MDT_TYPE_HASH)
			जारी;

		अगर (!phdr->p_memsz)
			जारी;

		ret = rproc_coredump_add_segment(rproc, phdr->p_paddr,
						 phdr->p_memsz);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(qcom_रेजिस्टर_dump_segments);

अटल पूर्णांक smd_subdev_start(काष्ठा rproc_subdev *subdev)
अणु
	काष्ठा qcom_rproc_subdev *smd = to_smd_subdev(subdev);

	smd->edge = qcom_smd_रेजिस्टर_edge(smd->dev, smd->node);

	वापस PTR_ERR_OR_ZERO(smd->edge);
पूर्ण

अटल व्योम smd_subdev_stop(काष्ठा rproc_subdev *subdev, bool crashed)
अणु
	काष्ठा qcom_rproc_subdev *smd = to_smd_subdev(subdev);

	qcom_smd_unरेजिस्टर_edge(smd->edge);
	smd->edge = शून्य;
पूर्ण

/**
 * qcom_add_smd_subdev() - try to add a SMD subdevice to rproc
 * @rproc:	rproc handle to parent the subdevice
 * @smd:	reference to a Qualcomm subdev context
 */
व्योम qcom_add_smd_subdev(काष्ठा rproc *rproc, काष्ठा qcom_rproc_subdev *smd)
अणु
	काष्ठा device *dev = &rproc->dev;

	smd->node = of_get_child_by_name(dev->parent->of_node, "smd-edge");
	अगर (!smd->node)
		वापस;

	smd->dev = dev;
	smd->subdev.start = smd_subdev_start;
	smd->subdev.stop = smd_subdev_stop;

	rproc_add_subdev(rproc, &smd->subdev);
पूर्ण
EXPORT_SYMBOL_GPL(qcom_add_smd_subdev);

/**
 * qcom_हटाओ_smd_subdev() - हटाओ the smd subdevice from rproc
 * @rproc:	rproc handle
 * @smd:	the SMD subdevice to हटाओ
 */
व्योम qcom_हटाओ_smd_subdev(काष्ठा rproc *rproc, काष्ठा qcom_rproc_subdev *smd)
अणु
	अगर (!smd->node)
		वापस;

	rproc_हटाओ_subdev(rproc, &smd->subdev);
	of_node_put(smd->node);
पूर्ण
EXPORT_SYMBOL_GPL(qcom_हटाओ_smd_subdev);

अटल काष्ठा qcom_ssr_subप्रणाली *qcom_ssr_get_subsys(स्थिर अक्षर *name)
अणु
	काष्ठा qcom_ssr_subप्रणाली *info;

	mutex_lock(&qcom_ssr_subsys_lock);
	/* Match in the global qcom_ssr_subप्रणाली_list with name */
	list_क्रम_each_entry(info, &qcom_ssr_subप्रणाली_list, list)
		अगर (!म_भेद(info->name, name))
			जाओ out;

	info = kzalloc(माप(*info), GFP_KERNEL);
	अगर (!info) अणु
		info = ERR_PTR(-ENOMEM);
		जाओ out;
	पूर्ण
	info->name = kstrdup_स्थिर(name, GFP_KERNEL);
	srcu_init_notअगरier_head(&info->notअगरier_list);

	/* Add to global notअगरication list */
	list_add_tail(&info->list, &qcom_ssr_subप्रणाली_list);

out:
	mutex_unlock(&qcom_ssr_subsys_lock);
	वापस info;
पूर्ण

/**
 * qcom_रेजिस्टर_ssr_notअगरier() - रेजिस्टर SSR notअगरication handler
 * @name:	Subप्रणाली's SSR name
 * @nb:		notअगरier_block to be invoked upon subप्रणाली's state change
 *
 * This रेजिस्टरs the @nb notअगरier block as part the notअगरier chain क्रम a
 * remoteproc associated with @name. The notअगरier block's callback
 * will be invoked when the remote processor's SSR events occur
 * (pre/post startup and pre/post shutकरोwn).
 *
 * Return: a subप्रणाली cookie on success, ERR_PTR on failure.
 */
व्योम *qcom_रेजिस्टर_ssr_notअगरier(स्थिर अक्षर *name, काष्ठा notअगरier_block *nb)
अणु
	काष्ठा qcom_ssr_subप्रणाली *info;

	info = qcom_ssr_get_subsys(name);
	अगर (IS_ERR(info))
		वापस info;

	srcu_notअगरier_chain_रेजिस्टर(&info->notअगरier_list, nb);

	वापस &info->notअगरier_list;
पूर्ण
EXPORT_SYMBOL_GPL(qcom_रेजिस्टर_ssr_notअगरier);

/**
 * qcom_unरेजिस्टर_ssr_notअगरier() - unरेजिस्टर SSR notअगरication handler
 * @notअगरy:	subप्रणाली cookie वापसed from qcom_रेजिस्टर_ssr_notअगरier
 * @nb:		notअगरier_block to unरेजिस्टर
 *
 * This function will unरेजिस्टर the notअगरier from the particular notअगरier
 * chain.
 *
 * Return: 0 on success, %ENOENT otherwise.
 */
पूर्णांक qcom_unरेजिस्टर_ssr_notअगरier(व्योम *notअगरy, काष्ठा notअगरier_block *nb)
अणु
	वापस srcu_notअगरier_chain_unरेजिस्टर(notअगरy, nb);
पूर्ण
EXPORT_SYMBOL_GPL(qcom_unरेजिस्टर_ssr_notअगरier);

अटल पूर्णांक ssr_notअगरy_prepare(काष्ठा rproc_subdev *subdev)
अणु
	काष्ठा qcom_rproc_ssr *ssr = to_ssr_subdev(subdev);
	काष्ठा qcom_ssr_notअगरy_data data = अणु
		.name = ssr->info->name,
		.crashed = false,
	पूर्ण;

	srcu_notअगरier_call_chain(&ssr->info->notअगरier_list,
				 QCOM_SSR_BEFORE_POWERUP, &data);
	वापस 0;
पूर्ण

अटल पूर्णांक ssr_notअगरy_start(काष्ठा rproc_subdev *subdev)
अणु
	काष्ठा qcom_rproc_ssr *ssr = to_ssr_subdev(subdev);
	काष्ठा qcom_ssr_notअगरy_data data = अणु
		.name = ssr->info->name,
		.crashed = false,
	पूर्ण;

	srcu_notअगरier_call_chain(&ssr->info->notअगरier_list,
				 QCOM_SSR_AFTER_POWERUP, &data);
	वापस 0;
पूर्ण

अटल व्योम ssr_notअगरy_stop(काष्ठा rproc_subdev *subdev, bool crashed)
अणु
	काष्ठा qcom_rproc_ssr *ssr = to_ssr_subdev(subdev);
	काष्ठा qcom_ssr_notअगरy_data data = अणु
		.name = ssr->info->name,
		.crashed = crashed,
	पूर्ण;

	srcu_notअगरier_call_chain(&ssr->info->notअगरier_list,
				 QCOM_SSR_BEFORE_SHUTDOWN, &data);
पूर्ण

अटल व्योम ssr_notअगरy_unprepare(काष्ठा rproc_subdev *subdev)
अणु
	काष्ठा qcom_rproc_ssr *ssr = to_ssr_subdev(subdev);
	काष्ठा qcom_ssr_notअगरy_data data = अणु
		.name = ssr->info->name,
		.crashed = false,
	पूर्ण;

	srcu_notअगरier_call_chain(&ssr->info->notअगरier_list,
				 QCOM_SSR_AFTER_SHUTDOWN, &data);
पूर्ण

/**
 * qcom_add_ssr_subdev() - रेजिस्टर subdevice as restart notअगरication source
 * @rproc:	rproc handle
 * @ssr:	SSR subdevice handle
 * @ssr_name:	identअगरier to use क्रम notअगरications originating from @rproc
 *
 * As the @ssr is रेजिस्टरed with the @rproc SSR events will be sent to all
 * रेजिस्टरed listeners क्रम the remoteproc when it's SSR events occur
 * (pre/post startup and pre/post shutकरोwn).
 */
व्योम qcom_add_ssr_subdev(काष्ठा rproc *rproc, काष्ठा qcom_rproc_ssr *ssr,
			 स्थिर अक्षर *ssr_name)
अणु
	काष्ठा qcom_ssr_subप्रणाली *info;

	info = qcom_ssr_get_subsys(ssr_name);
	अगर (IS_ERR(info)) अणु
		dev_err(&rproc->dev, "Failed to add ssr subdevice\n");
		वापस;
	पूर्ण

	ssr->info = info;
	ssr->subdev.prepare = ssr_notअगरy_prepare;
	ssr->subdev.start = ssr_notअगरy_start;
	ssr->subdev.stop = ssr_notअगरy_stop;
	ssr->subdev.unprepare = ssr_notअगरy_unprepare;

	rproc_add_subdev(rproc, &ssr->subdev);
पूर्ण
EXPORT_SYMBOL_GPL(qcom_add_ssr_subdev);

/**
 * qcom_हटाओ_ssr_subdev() - हटाओ subdevice as restart notअगरication source
 * @rproc:	rproc handle
 * @ssr:	SSR subdevice handle
 */
व्योम qcom_हटाओ_ssr_subdev(काष्ठा rproc *rproc, काष्ठा qcom_rproc_ssr *ssr)
अणु
	rproc_हटाओ_subdev(rproc, &ssr->subdev);
	ssr->info = शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(qcom_हटाओ_ssr_subdev);

MODULE_DESCRIPTION("Qualcomm Remoteproc helper driver");
MODULE_LICENSE("GPL v2");
