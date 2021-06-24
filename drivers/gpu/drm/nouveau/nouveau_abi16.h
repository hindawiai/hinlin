<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
#अगर_अघोषित __NOUVEAU_ABI16_H__
#घोषणा __NOUVEAU_ABI16_H__

#घोषणा ABI16_IOCTL_ARGS                                                       \
	काष्ठा drm_device *dev, व्योम *data, काष्ठा drm_file *file_priv

पूर्णांक nouveau_abi16_ioctl_getparam(ABI16_IOCTL_ARGS);
पूर्णांक nouveau_abi16_ioctl_channel_alloc(ABI16_IOCTL_ARGS);
पूर्णांक nouveau_abi16_ioctl_channel_मुक्त(ABI16_IOCTL_ARGS);
पूर्णांक nouveau_abi16_ioctl_grobj_alloc(ABI16_IOCTL_ARGS);
पूर्णांक nouveau_abi16_ioctl_notअगरierobj_alloc(ABI16_IOCTL_ARGS);
पूर्णांक nouveau_abi16_ioctl_gpuobj_मुक्त(ABI16_IOCTL_ARGS);

काष्ठा nouveau_abi16_ntfy अणु
	काष्ठा nvअगर_object object;
	काष्ठा list_head head;
	काष्ठा nvkm_mm_node *node;
पूर्ण;

काष्ठा nouveau_abi16_chan अणु
	काष्ठा list_head head;
	काष्ठा nouveau_channel *chan;
	काष्ठा list_head notअगरiers;
	काष्ठा nouveau_bo *ntfy;
	काष्ठा nouveau_vma *ntfy_vma;
	काष्ठा nvkm_mm  heap;
पूर्ण;

काष्ठा nouveau_abi16 अणु
	काष्ठा nvअगर_device device;
	काष्ठा list_head channels;
	u64 handles;
पूर्ण;

काष्ठा nouveau_abi16 *nouveau_abi16_get(काष्ठा drm_file *);
पूर्णांक  nouveau_abi16_put(काष्ठा nouveau_abi16 *, पूर्णांक);
व्योम nouveau_abi16_fini(काष्ठा nouveau_abi16 *);
s32  nouveau_abi16_swclass(काष्ठा nouveau_drm *);
पूर्णांक  nouveau_abi16_usअगर(काष्ठा drm_file *, व्योम *data, u32 size);

#घोषणा NOUVEAU_GEM_DOMAIN_VRAM      (1 << 1)
#घोषणा NOUVEAU_GEM_DOMAIN_GART      (1 << 2)

काष्ठा drm_nouveau_channel_alloc अणु
	uपूर्णांक32_t     fb_ctxdma_handle;
	uपूर्णांक32_t     tt_ctxdma_handle;

	पूर्णांक          channel;
	uपूर्णांक32_t     pushbuf_करोमुख्यs;

	/* Notअगरier memory */
	uपूर्णांक32_t     notअगरier_handle;

	/* DRM-enक्रमced subchannel assignments */
	काष्ठा अणु
		uपूर्णांक32_t handle;
		uपूर्णांक32_t grclass;
	पूर्ण subchan[8];
	uपूर्णांक32_t nr_subchan;
पूर्ण;

काष्ठा drm_nouveau_channel_मुक्त अणु
	पूर्णांक channel;
पूर्ण;

काष्ठा drm_nouveau_grobj_alloc अणु
	पूर्णांक      channel;
	uपूर्णांक32_t handle;
	पूर्णांक      class;
पूर्ण;

काष्ठा drm_nouveau_notअगरierobj_alloc अणु
	uपूर्णांक32_t channel;
	uपूर्णांक32_t handle;
	uपूर्णांक32_t size;
	uपूर्णांक32_t offset;
पूर्ण;

काष्ठा drm_nouveau_gpuobj_मुक्त अणु
	पूर्णांक      channel;
	uपूर्णांक32_t handle;
पूर्ण;

#घोषणा NOUVEAU_GETPARAM_PCI_VENDOR      3
#घोषणा NOUVEAU_GETPARAM_PCI_DEVICE      4
#घोषणा NOUVEAU_GETPARAM_BUS_TYPE        5
#घोषणा NOUVEAU_GETPARAM_FB_SIZE         8
#घोषणा NOUVEAU_GETPARAM_AGP_SIZE        9
#घोषणा NOUVEAU_GETPARAM_CHIPSET_ID      11
#घोषणा NOUVEAU_GETPARAM_VM_VRAM_BASE    12
#घोषणा NOUVEAU_GETPARAM_GRAPH_UNITS     13
#घोषणा NOUVEAU_GETPARAM_PTIMER_TIME     14
#घोषणा NOUVEAU_GETPARAM_HAS_BO_USAGE    15
#घोषणा NOUVEAU_GETPARAM_HAS_PAGEFLIP    16
काष्ठा drm_nouveau_getparam अणु
	uपूर्णांक64_t param;
	uपूर्णांक64_t value;
पूर्ण;

काष्ठा drm_nouveau_setparam अणु
	uपूर्णांक64_t param;
	uपूर्णांक64_t value;
पूर्ण;

#घोषणा DRM_IOCTL_NOUVEAU_GETPARAM           DRM_IOWR(DRM_COMMAND_BASE + DRM_NOUVEAU_GETPARAM, काष्ठा drm_nouveau_getparam)
#घोषणा DRM_IOCTL_NOUVEAU_SETPARAM           DRM_IOWR(DRM_COMMAND_BASE + DRM_NOUVEAU_SETPARAM, काष्ठा drm_nouveau_setparam)
#घोषणा DRM_IOCTL_NOUVEAU_CHANNEL_ALLOC      DRM_IOWR(DRM_COMMAND_BASE + DRM_NOUVEAU_CHANNEL_ALLOC, काष्ठा drm_nouveau_channel_alloc)
#घोषणा DRM_IOCTL_NOUVEAU_CHANNEL_FREE       DRM_IOW (DRM_COMMAND_BASE + DRM_NOUVEAU_CHANNEL_FREE, काष्ठा drm_nouveau_channel_मुक्त)
#घोषणा DRM_IOCTL_NOUVEAU_GROBJ_ALLOC        DRM_IOW (DRM_COMMAND_BASE + DRM_NOUVEAU_GROBJ_ALLOC, काष्ठा drm_nouveau_grobj_alloc)
#घोषणा DRM_IOCTL_NOUVEAU_NOTIFIEROBJ_ALLOC  DRM_IOWR(DRM_COMMAND_BASE + DRM_NOUVEAU_NOTIFIEROBJ_ALLOC, काष्ठा drm_nouveau_notअगरierobj_alloc)
#घोषणा DRM_IOCTL_NOUVEAU_GPUOBJ_FREE        DRM_IOW (DRM_COMMAND_BASE + DRM_NOUVEAU_GPUOBJ_FREE, काष्ठा drm_nouveau_gpuobj_मुक्त)

#पूर्ण_अगर
