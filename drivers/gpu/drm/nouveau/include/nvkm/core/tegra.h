<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
#अगर_अघोषित __NVKM_DEVICE_TEGRA_H__
#घोषणा __NVKM_DEVICE_TEGRA_H__
#समावेश <core/device.h>
#समावेश <core/mm.h>

काष्ठा nvkm_device_tegra अणु
	स्थिर काष्ठा nvkm_device_tegra_func *func;
	काष्ठा nvkm_device device;
	काष्ठा platक्रमm_device *pdev;
	पूर्णांक irq;

	काष्ठा reset_control *rst;
	काष्ठा clk *clk;
	काष्ठा clk *clk_ref;
	काष्ठा clk *clk_pwr;

	काष्ठा regulator *vdd;

	काष्ठा अणु
		/*
		 * Protects accesses to mm from subप्रणालीs
		 */
		काष्ठा mutex mutex;

		काष्ठा nvkm_mm mm;
		काष्ठा iommu_करोमुख्य *करोमुख्य;
		अचिन्हित दीर्घ pgshअगरt;
	पूर्ण iommu;

	पूर्णांक gpu_speeकरो;
	पूर्णांक gpu_speeकरो_id;
पूर्ण;

काष्ठा nvkm_device_tegra_func अणु
	/*
	 * If an IOMMU is used, indicates which address bit will trigger a
	 * IOMMU translation when set (when this bit is not set, IOMMU is
	 * bypassed). A value of 0 means an IOMMU is never used.
	 */
	u8 iommu_bit;
	/*
	 * Whether the chip requires a reference घड़ी
	 */
	bool require_ref_clk;
	/*
	 * Whether the chip requires the VDD regulator
	 */
	bool require_vdd;
पूर्ण;

पूर्णांक nvkm_device_tegra_new(स्थिर काष्ठा nvkm_device_tegra_func *,
			  काष्ठा platक्रमm_device *,
			  स्थिर अक्षर *cfg, स्थिर अक्षर *dbg,
			  bool detect, bool mmio, u64 subdev_mask,
			  काष्ठा nvkm_device **);
#पूर्ण_अगर
