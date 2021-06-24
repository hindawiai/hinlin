<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
#अगर_अघोषित __NOUVEAU_DRV_H__
#घोषणा __NOUVEAU_DRV_H__

#घोषणा DRIVER_AUTHOR		"Nouveau Project"
#घोषणा DRIVER_EMAIL		"nouveau@lists.freedesktop.org"

#घोषणा DRIVER_NAME		"nouveau"
#घोषणा DRIVER_DESC		"nVidia Riva/TNT/GeForce/Quadro/Tesla/Tegra K1+"
#घोषणा DRIVER_DATE		"20120801"

#घोषणा DRIVER_MAJOR		1
#घोषणा DRIVER_MINOR		3
#घोषणा DRIVER_PATCHLEVEL	1

/*
 * 1.1.1:
 * 	- added support क्रम tiled प्रणाली memory buffer objects
 *      - added support क्रम NOUVEAU_GETPARAM_GRAPH_UNITS on [nvc0,nve0].
 *      - added support क्रम compressed memory storage types on [nvc0,nve0].
 *      - added support क्रम software methods 0x600,0x644,0x6ac on nvc0
 *        to control रेजिस्टरs on the MPs to enable perक्रमmance counters,
 *        and to control the warp error enable mask (OpenGL requires out of
 *        bounds access to local memory to be silently ignored / वापस 0).
 * 1.1.2:
 *      - fixes multiple bugs in flip completion events and बारtamping
 * 1.2.0:
 * 	- object api exposed to userspace
 * 	- fermi,kepler,maxwell zbc
 * 1.2.1:
 *      - allow concurrent access to bo's mapped पढ़ो/ग_लिखो.
 * 1.2.2:
 *      - add NOUVEAU_GEM_DOMAIN_COHERENT flag
 * 1.3.0:
 *      - NVIF ABI modअगरied, safe because only (current) users are test
 *        programs that get directly linked with NVKM.
 * 1.3.1:
 *      - implemented limited ABI16/NVIF पूर्णांकerop
 */

#समावेश <linux/notअगरier.h>

#समावेश <nvअगर/client.h>
#समावेश <nvअगर/device.h>
#समावेश <nvअगर/ioctl.h>
#समावेश <nvअगर/mmu.h>
#समावेश <nvअगर/vmm.h>

#समावेश <drm/drm_connector.h>
#समावेश <drm/drm_device.h>
#समावेश <drm/drm_drv.h>
#समावेश <drm/drm_file.h>

#समावेश <drm/tपंचांग/tपंचांग_bo_api.h>
#समावेश <drm/tपंचांग/tपंचांग_bo_driver.h>
#समावेश <drm/tपंचांग/tपंचांग_placement.h>

#समावेश <drm/drm_audio_component.h>

#समावेश "uapi/drm/nouveau_drm.h"

काष्ठा nouveau_channel;
काष्ठा platक्रमm_device;

#समावेश "nouveau_fence.h"
#समावेश "nouveau_bios.h"
#समावेश "nouveau_vmm.h"

काष्ठा nouveau_drm_tile अणु
	काष्ठा nouveau_fence *fence;
	bool used;
पूर्ण;

क्रमागत nouveau_drm_object_route अणु
	NVDRM_OBJECT_NVIF = NVIF_IOCTL_V0_OWNER_NVIF,
	NVDRM_OBJECT_USIF,
	NVDRM_OBJECT_ABI16,
	NVDRM_OBJECT_ANY = NVIF_IOCTL_V0_OWNER_ANY,
पूर्ण;

क्रमागत nouveau_drm_notअगरy_route अणु
	NVDRM_NOTIFY_NVIF = 0,
	NVDRM_NOTIFY_USIF
पूर्ण;

क्रमागत nouveau_drm_handle अणु
	NVDRM_CHAN    = 0xcccc0000, /* |= client chid */
	NVDRM_NVSW    = 0x55550000,
पूर्ण;

काष्ठा nouveau_cli अणु
	काष्ठा nvअगर_client base;
	काष्ठा nouveau_drm *drm;
	काष्ठा mutex mutex;

	काष्ठा nvअगर_device device;
	काष्ठा nvअगर_mmu mmu;
	काष्ठा nouveau_vmm vmm;
	काष्ठा nouveau_vmm svm;
	स्थिर काष्ठा nvअगर_mclass *mem;

	काष्ठा list_head head;
	व्योम *abi16;
	काष्ठा list_head objects;
	काष्ठा list_head notअगरys;
	अक्षर name[32];

	काष्ठा work_काष्ठा work;
	काष्ठा list_head worker;
	काष्ठा mutex lock;
पूर्ण;

काष्ठा nouveau_cli_work अणु
	व्योम (*func)(काष्ठा nouveau_cli_work *);
	काष्ठा nouveau_cli *cli;
	काष्ठा list_head head;

	काष्ठा dma_fence *fence;
	काष्ठा dma_fence_cb cb;
पूर्ण;

व्योम nouveau_cli_work_queue(काष्ठा nouveau_cli *, काष्ठा dma_fence *,
			    काष्ठा nouveau_cli_work *);

अटल अंतरभूत काष्ठा nouveau_cli *
nouveau_cli(काष्ठा drm_file *fpriv)
अणु
	वापस fpriv ? fpriv->driver_priv : शून्य;
पूर्ण

#समावेश <nvअगर/object.h>
#समावेश <nvअगर/parent.h>

काष्ठा nouveau_drm अणु
	काष्ठा nvअगर_parent parent;
	काष्ठा nouveau_cli master;
	काष्ठा nouveau_cli client;
	काष्ठा drm_device *dev;

	काष्ठा list_head clients;

	u8 old_pm_cap;

	काष्ठा अणु
		काष्ठा agp_bridge_data *bridge;
		u32 base;
		u32 size;
		bool cma;
	पूर्ण agp;

	/* TTM पूर्णांकerface support */
	काष्ठा अणु
		काष्ठा tपंचांग_device bdev;
		atomic_t validate_sequence;
		पूर्णांक (*move)(काष्ठा nouveau_channel *,
			    काष्ठा tपंचांग_buffer_object *,
			    काष्ठा tपंचांग_resource *, काष्ठा tपंचांग_resource *);
		काष्ठा nouveau_channel *chan;
		काष्ठा nvअगर_object copy;
		पूर्णांक mtrr;
		पूर्णांक type_vram;
		पूर्णांक type_host[2];
		पूर्णांक type_ncoh[2];
		काष्ठा mutex io_reserve_mutex;
		काष्ठा list_head io_reserve_lru;
	पूर्ण tपंचांग;

	/* GEM पूर्णांकerface support */
	काष्ठा अणु
		u64 vram_available;
		u64 gart_available;
	पूर्ण gem;

	/* synchronisation */
	व्योम *fence;

	/* Global channel management. */
	काष्ठा अणु
		पूर्णांक nr;
		u64 context_base;
	पूर्ण chan;

	/* context क्रम accelerated drm-पूर्णांकernal operations */
	काष्ठा nouveau_channel *cechan;
	काष्ठा nouveau_channel *channel;
	काष्ठा nvkm_gpuobj *notअगरy;
	काष्ठा nouveau_fbdev *fbcon;
	काष्ठा nvअगर_object ntfy;

	/* nv10-nv40 tiling regions */
	काष्ठा अणु
		काष्ठा nouveau_drm_tile reg[15];
		spinlock_t lock;
	पूर्ण tile;

	/* modesetting */
	काष्ठा nvbios vbios;
	काष्ठा nouveau_display *display;
	काष्ठा work_काष्ठा hpd_work;
	काष्ठा mutex hpd_lock;
	u32 hpd_pending;
	काष्ठा work_काष्ठा fbcon_work;
	पूर्णांक fbcon_new_state;
#अगर_घोषित CONFIG_ACPI
	काष्ठा notअगरier_block acpi_nb;
#पूर्ण_अगर

	/* घातer management */
	काष्ठा nouveau_hwmon *hwmon;
	काष्ठा nouveau_debugfs *debugfs;

	/* led management */
	काष्ठा nouveau_led *led;

	काष्ठा dev_pm_करोमुख्य vga_pm_करोमुख्य;

	काष्ठा nouveau_svm *svm;

	काष्ठा nouveau_dmem *dmem;

	काष्ठा अणु
		काष्ठा drm_audio_component *component;
		काष्ठा mutex lock;
		bool component_रेजिस्टरed;
	पूर्ण audio;
पूर्ण;

अटल अंतरभूत काष्ठा nouveau_drm *
nouveau_drm(काष्ठा drm_device *dev)
अणु
	वापस dev->dev_निजी;
पूर्ण

अटल अंतरभूत bool
nouveau_drm_use_coherent_gpu_mapping(काष्ठा nouveau_drm *drm)
अणु
	काष्ठा nvअगर_mmu *mmu = &drm->client.mmu;
	वापस !(mmu->type[drm->tपंचांग.type_host[0]].type & NVIF_MEM_UNCACHED);
पूर्ण

पूर्णांक nouveau_pmops_suspend(काष्ठा device *);
पूर्णांक nouveau_pmops_resume(काष्ठा device *);
bool nouveau_pmops_runसमय(व्योम);

#समावेश <nvkm/core/tegra.h>

काष्ठा drm_device *
nouveau_platक्रमm_device_create(स्थिर काष्ठा nvkm_device_tegra_func *,
			       काष्ठा platक्रमm_device *, काष्ठा nvkm_device **);
व्योम nouveau_drm_device_हटाओ(काष्ठा drm_device *dev);

#घोषणा NV_PRINTK(l,c,f,a...) करो अणु                                             \
	काष्ठा nouveau_cli *_cli = (c);                                        \
	dev_##l(_cli->drm->dev->dev, "%s: "f, _cli->name, ##a);                \
पूर्ण जबतक(0)

#घोषणा NV_FATAL(drm,f,a...) NV_PRINTK(crit, &(drm)->client, f, ##a)
#घोषणा NV_ERROR(drm,f,a...) NV_PRINTK(err, &(drm)->client, f, ##a)
#घोषणा NV_WARN(drm,f,a...) NV_PRINTK(warn, &(drm)->client, f, ##a)
#घोषणा NV_INFO(drm,f,a...) NV_PRINTK(info, &(drm)->client, f, ##a)

#घोषणा NV_DEBUG(drm,f,a...) करो अणु                                              \
	अगर (drm_debug_enabled(DRM_UT_DRIVER))                                  \
		NV_PRINTK(info, &(drm)->client, f, ##a);                       \
पूर्ण जबतक(0)
#घोषणा NV_ATOMIC(drm,f,a...) करो अणु                                             \
	अगर (drm_debug_enabled(DRM_UT_ATOMIC))                                  \
		NV_PRINTK(info, &(drm)->client, f, ##a);                       \
पूर्ण जबतक(0)

#घोषणा NV_PRINTK_ONCE(l,c,f,a...) NV_PRINTK(l##_once,c,f, ##a)

#घोषणा NV_ERROR_ONCE(drm,f,a...) NV_PRINTK_ONCE(err, &(drm)->client, f, ##a)
#घोषणा NV_WARN_ONCE(drm,f,a...) NV_PRINTK_ONCE(warn, &(drm)->client, f, ##a)
#घोषणा NV_INFO_ONCE(drm,f,a...) NV_PRINTK_ONCE(info, &(drm)->client, f, ##a)

बाह्य पूर्णांक nouveau_modeset;

#पूर्ण_अगर
