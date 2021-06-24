<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Remote processor framework
 *
 * Copyright (C) 2011 Texas Instruments, Inc.
 * Copyright (C) 2011 Google, Inc.
 *
 * Ohad Ben-Cohen <ohad@wizery.com>
 * Brian Swetland <swetland@google.com>
 */

#अगर_अघोषित REMOTEPROC_INTERNAL_H
#घोषणा REMOTEPROC_INTERNAL_H

#समावेश <linux/irqवापस.h>
#समावेश <linux/firmware.h>

काष्ठा rproc;

काष्ठा rproc_debug_trace अणु
	काष्ठा rproc *rproc;
	काष्ठा dentry *tfile;
	काष्ठा list_head node;
	काष्ठा rproc_mem_entry trace_mem;
पूर्ण;

/* from remoteproc_core.c */
व्योम rproc_release(काष्ठा kref *kref);
irqवापस_t rproc_vq_पूर्णांकerrupt(काष्ठा rproc *rproc, पूर्णांक vq_id);
व्योम rproc_vdev_release(काष्ठा kref *ref);
पूर्णांक rproc_of_parse_firmware(काष्ठा device *dev, पूर्णांक index,
			    स्थिर अक्षर **fw_name);

/* from remoteproc_virtio.c */
पूर्णांक rproc_add_virtio_dev(काष्ठा rproc_vdev *rvdev, पूर्णांक id);
पूर्णांक rproc_हटाओ_virtio_dev(काष्ठा device *dev, व्योम *data);

/* from remoteproc_debugfs.c */
व्योम rproc_हटाओ_trace_file(काष्ठा dentry *tfile);
काष्ठा dentry *rproc_create_trace_file(स्थिर अक्षर *name, काष्ठा rproc *rproc,
				       काष्ठा rproc_debug_trace *trace);
व्योम rproc_delete_debug_dir(काष्ठा rproc *rproc);
व्योम rproc_create_debug_dir(काष्ठा rproc *rproc);
व्योम rproc_init_debugfs(व्योम);
व्योम rproc_निकास_debugfs(व्योम);

/* from remoteproc_sysfs.c */
बाह्य काष्ठा class rproc_class;
पूर्णांक rproc_init_sysfs(व्योम);
व्योम rproc_निकास_sysfs(व्योम);

/* from remoteproc_coredump.c */
व्योम rproc_coredump_cleanup(काष्ठा rproc *rproc);
व्योम rproc_coredump(काष्ठा rproc *rproc);

#अगर_घोषित CONFIG_REMOTEPROC_CDEV
व्योम rproc_init_cdev(व्योम);
व्योम rproc_निकास_cdev(व्योम);
पूर्णांक rproc_अक्षर_device_add(काष्ठा rproc *rproc);
व्योम rproc_अक्षर_device_हटाओ(काष्ठा rproc *rproc);
#अन्यथा
अटल अंतरभूत व्योम rproc_init_cdev(व्योम)
अणु
पूर्ण

अटल अंतरभूत व्योम rproc_निकास_cdev(व्योम)
अणु
पूर्ण

/*
 * The अक्षरacter device पूर्णांकerface is an optional feature, अगर it is not enabled
 * the function should not वापस an error.
 */
अटल अंतरभूत पूर्णांक rproc_अक्षर_device_add(काष्ठा rproc *rproc)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम  rproc_अक्षर_device_हटाओ(काष्ठा rproc *rproc)
अणु
पूर्ण
#पूर्ण_अगर

व्योम rproc_मुक्त_vring(काष्ठा rproc_vring *rvring);
पूर्णांक rproc_alloc_vring(काष्ठा rproc_vdev *rvdev, पूर्णांक i);

व्योम *rproc_da_to_va(काष्ठा rproc *rproc, u64 da, माप_प्रकार len, bool *is_iomem);
phys_addr_t rproc_va_to_pa(व्योम *cpu_addr);
पूर्णांक rproc_trigger_recovery(काष्ठा rproc *rproc);

पूर्णांक rproc_elf_sanity_check(काष्ठा rproc *rproc, स्थिर काष्ठा firmware *fw);
u64 rproc_elf_get_boot_addr(काष्ठा rproc *rproc, स्थिर काष्ठा firmware *fw);
पूर्णांक rproc_elf_load_segments(काष्ठा rproc *rproc, स्थिर काष्ठा firmware *fw);
पूर्णांक rproc_elf_load_rsc_table(काष्ठा rproc *rproc, स्थिर काष्ठा firmware *fw);
काष्ठा resource_table *rproc_elf_find_loaded_rsc_table(काष्ठा rproc *rproc,
						       स्थिर काष्ठा firmware *fw);
काष्ठा rproc_mem_entry *
rproc_find_carveout_by_name(काष्ठा rproc *rproc, स्थिर अक्षर *name, ...);

अटल अंतरभूत पूर्णांक rproc_prepare_device(काष्ठा rproc *rproc)
अणु
	अगर (rproc->ops->prepare)
		वापस rproc->ops->prepare(rproc);

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक rproc_unprepare_device(काष्ठा rproc *rproc)
अणु
	अगर (rproc->ops->unprepare)
		वापस rproc->ops->unprepare(rproc);

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक rproc_attach_device(काष्ठा rproc *rproc)
अणु
	अगर (rproc->ops->attach)
		वापस rproc->ops->attach(rproc);

	वापस 0;
पूर्ण

अटल अंतरभूत
पूर्णांक rproc_fw_sanity_check(काष्ठा rproc *rproc, स्थिर काष्ठा firmware *fw)
अणु
	अगर (rproc->ops->sanity_check)
		वापस rproc->ops->sanity_check(rproc, fw);

	वापस 0;
पूर्ण

अटल अंतरभूत
u64 rproc_get_boot_addr(काष्ठा rproc *rproc, स्थिर काष्ठा firmware *fw)
अणु
	अगर (rproc->ops->get_boot_addr)
		वापस rproc->ops->get_boot_addr(rproc, fw);

	वापस 0;
पूर्ण

अटल अंतरभूत
पूर्णांक rproc_load_segments(काष्ठा rproc *rproc, स्थिर काष्ठा firmware *fw)
अणु
	अगर (rproc->ops->load)
		वापस rproc->ops->load(rproc, fw);

	वापस -EINVAL;
पूर्ण

अटल अंतरभूत पूर्णांक rproc_parse_fw(काष्ठा rproc *rproc, स्थिर काष्ठा firmware *fw)
अणु
	अगर (rproc->ops->parse_fw)
		वापस rproc->ops->parse_fw(rproc, fw);

	वापस 0;
पूर्ण

अटल अंतरभूत
पूर्णांक rproc_handle_rsc(काष्ठा rproc *rproc, u32 rsc_type, व्योम *rsc, पूर्णांक offset,
		     पूर्णांक avail)
अणु
	अगर (rproc->ops->handle_rsc)
		वापस rproc->ops->handle_rsc(rproc, rsc_type, rsc, offset,
					      avail);

	वापस RSC_IGNORED;
पूर्ण

अटल अंतरभूत
काष्ठा resource_table *rproc_find_loaded_rsc_table(काष्ठा rproc *rproc,
						   स्थिर काष्ठा firmware *fw)
अणु
	अगर (rproc->ops->find_loaded_rsc_table)
		वापस rproc->ops->find_loaded_rsc_table(rproc, fw);

	वापस शून्य;
पूर्ण

अटल अंतरभूत
काष्ठा resource_table *rproc_get_loaded_rsc_table(काष्ठा rproc *rproc,
						  माप_प्रकार *size)
अणु
	अगर (rproc->ops->get_loaded_rsc_table)
		वापस rproc->ops->get_loaded_rsc_table(rproc, size);

	वापस शून्य;
पूर्ण

अटल अंतरभूत
bool rproc_u64_fit_in_माप_प्रकार(u64 val)
अणु
	अगर (माप(माप_प्रकार) == माप(u64))
		वापस true;

	वापस (val <= (माप_प्रकार) -1);
पूर्ण

#पूर्ण_अगर /* REMOTEPROC_INTERNAL_H */
