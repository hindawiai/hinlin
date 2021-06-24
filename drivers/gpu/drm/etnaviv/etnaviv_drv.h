<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (C) 2015-2018 Etnaviv Project
 */

#अगर_अघोषित __ETNAVIV_DRV_H__
#घोषणा __ETNAVIV_DRV_H__

#समावेश <linux/list.h>
#समावेश <linux/mm_types.h>
#समावेश <linux/sizes.h>
#समावेश <linux/समय64.h>
#समावेश <linux/types.h>

#समावेश <drm/drm_fb_helper.h>
#समावेश <drm/drm_gem.h>
#समावेश <drm/etnaviv_drm.h>
#समावेश <drm/gpu_scheduler.h>

काष्ठा etnaviv_cmdbuf;
काष्ठा etnaviv_gpu;
काष्ठा etnaviv_mmu;
काष्ठा etnaviv_gem_object;
काष्ठा etnaviv_gem_submit;
काष्ठा etnaviv_iommu_global;

#घोषणा ETNAVIV_SOFTPIN_START_ADDRESS	SZ_4M /* must be >= SUBALLOC_SIZE */

काष्ठा etnaviv_file_निजी अणु
	काष्ठा etnaviv_iommu_context	*mmu;
	काष्ठा drm_sched_entity		sched_entity[ETNA_MAX_PIPES];
पूर्ण;

काष्ठा etnaviv_drm_निजी अणु
	पूर्णांक num_gpus;
	काष्ठा etnaviv_gpu *gpu[ETNA_MAX_PIPES];
	gfp_t shm_gfp_mask;

	काष्ठा etnaviv_cmdbuf_suballoc *cmdbuf_suballoc;
	काष्ठा etnaviv_iommu_global *mmu_global;

	/* list of GEM objects: */
	काष्ठा mutex gem_lock;
	काष्ठा list_head gem_list;
पूर्ण;

पूर्णांक etnaviv_ioctl_gem_submit(काष्ठा drm_device *dev, व्योम *data,
		काष्ठा drm_file *file);

पूर्णांक etnaviv_gem_mmap(काष्ठा file *filp, काष्ठा vm_area_काष्ठा *vma);
पूर्णांक etnaviv_gem_mmap_offset(काष्ठा drm_gem_object *obj, u64 *offset);
काष्ठा sg_table *etnaviv_gem_prime_get_sg_table(काष्ठा drm_gem_object *obj);
पूर्णांक etnaviv_gem_prime_vmap(काष्ठा drm_gem_object *obj, काष्ठा dma_buf_map *map);
पूर्णांक etnaviv_gem_prime_mmap(काष्ठा drm_gem_object *obj,
			   काष्ठा vm_area_काष्ठा *vma);
काष्ठा drm_gem_object *etnaviv_gem_prime_import_sg_table(काष्ठा drm_device *dev,
	काष्ठा dma_buf_attachment *attach, काष्ठा sg_table *sg);
पूर्णांक etnaviv_gem_prime_pin(काष्ठा drm_gem_object *obj);
व्योम etnaviv_gem_prime_unpin(काष्ठा drm_gem_object *obj);
व्योम *etnaviv_gem_vmap(काष्ठा drm_gem_object *obj);
पूर्णांक etnaviv_gem_cpu_prep(काष्ठा drm_gem_object *obj, u32 op,
		काष्ठा drm_etnaviv_बारpec *समयout);
पूर्णांक etnaviv_gem_cpu_fini(काष्ठा drm_gem_object *obj);
व्योम etnaviv_gem_मुक्त_object(काष्ठा drm_gem_object *obj);
पूर्णांक etnaviv_gem_new_handle(काष्ठा drm_device *dev, काष्ठा drm_file *file,
		u32 size, u32 flags, u32 *handle);
पूर्णांक etnaviv_gem_new_userptr(काष्ठा drm_device *dev, काष्ठा drm_file *file,
	uपूर्णांकptr_t ptr, u32 size, u32 flags, u32 *handle);
u16 etnaviv_buffer_init(काष्ठा etnaviv_gpu *gpu);
u16 etnaviv_buffer_config_mmuv2(काष्ठा etnaviv_gpu *gpu, u32 mtlb_addr, u32 safe_addr);
u16 etnaviv_buffer_config_pta(काष्ठा etnaviv_gpu *gpu, अचिन्हित लघु id);
व्योम etnaviv_buffer_end(काष्ठा etnaviv_gpu *gpu);
व्योम etnaviv_sync_poपूर्णांक_queue(काष्ठा etnaviv_gpu *gpu, अचिन्हित पूर्णांक event);
व्योम etnaviv_buffer_queue(काष्ठा etnaviv_gpu *gpu, u32 exec_state,
	काष्ठा etnaviv_iommu_context *mmu,
	अचिन्हित पूर्णांक event, काष्ठा etnaviv_cmdbuf *cmdbuf);
व्योम etnaviv_validate_init(व्योम);
bool etnaviv_cmd_validate_one(काष्ठा etnaviv_gpu *gpu,
	u32 *stream, अचिन्हित पूर्णांक size,
	काष्ठा drm_etnaviv_gem_submit_reloc *relocs, अचिन्हित पूर्णांक reloc_size);

#अगर_घोषित CONFIG_DEBUG_FS
व्योम etnaviv_gem_describe_objects(काष्ठा etnaviv_drm_निजी *priv,
	काष्ठा seq_file *m);
#पूर्ण_अगर

#घोषणा DBG(fmt, ...) DRM_DEBUG(fmt"\n", ##__VA_ARGS__)
#घोषणा VERB(fmt, ...) अगर (0) DRM_DEBUG(fmt"\n", ##__VA_ARGS__)

/*
 * Return the storage size of a काष्ठाure with a variable length array.
 * The array is nelem elements of elem_size, where the base काष्ठाure
 * is defined by base.  If the size overflows माप_प्रकार, वापस zero.
 */
अटल अंतरभूत माप_प्रकार size_vकाष्ठा(माप_प्रकार nelem, माप_प्रकार elem_size, माप_प्रकार base)
अणु
	अगर (elem_size && nelem > (SIZE_MAX - base) / elem_size)
		वापस 0;
	वापस base + nelem * elem_size;
पूर्ण

/*
 * Etnaviv समयouts are specअगरied wrt CLOCK_MONOTONIC, not jअगरfies.
 * We need to calculate the समयout in terms of number of jअगरfies
 * between the specअगरied समयout and the current CLOCK_MONOTONIC समय.
 */
अटल अंतरभूत अचिन्हित दीर्घ etnaviv_समयout_to_jअगरfies(
	स्थिर काष्ठा drm_etnaviv_बारpec *समयout)
अणु
	काष्ठा बारpec64 ts, to = अणु
		.tv_sec = समयout->tv_sec,
		.tv_nsec = समयout->tv_nsec,
	पूर्ण;

	kसमय_get_ts64(&ts);

	/* समयouts beक्रमe "now" have alपढ़ोy expired */
	अगर (बारpec64_compare(&to, &ts) <= 0)
		वापस 0;

	ts = बारpec64_sub(to, ts);

	वापस बारpec64_to_jअगरfies(&ts);
पूर्ण

#पूर्ण_अगर /* __ETNAVIV_DRV_H__ */
