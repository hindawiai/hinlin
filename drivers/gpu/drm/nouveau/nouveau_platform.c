<शैली गुरु>
/*
 * Copyright (c) 2014, NVIDIA CORPORATION. All rights reserved.
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */
#समावेश "nouveau_platform.h"

अटल पूर्णांक nouveau_platक्रमm_probe(काष्ठा platक्रमm_device *pdev)
अणु
	स्थिर काष्ठा nvkm_device_tegra_func *func;
	काष्ठा nvkm_device *device = शून्य;
	काष्ठा drm_device *drm;
	पूर्णांक ret;

	func = of_device_get_match_data(&pdev->dev);

	drm = nouveau_platक्रमm_device_create(func, pdev, &device);
	अगर (IS_ERR(drm))
		वापस PTR_ERR(drm);

	ret = drm_dev_रेजिस्टर(drm, 0);
	अगर (ret < 0) अणु
		drm_dev_put(drm);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक nouveau_platक्रमm_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा drm_device *dev = platक्रमm_get_drvdata(pdev);
	nouveau_drm_device_हटाओ(dev);
	वापस 0;
पूर्ण

#अगर IS_ENABLED(CONFIG_OF)
अटल स्थिर काष्ठा nvkm_device_tegra_func gk20a_platक्रमm_data = अणु
	.iommu_bit = 34,
	.require_vdd = true,
पूर्ण;

अटल स्थिर काष्ठा nvkm_device_tegra_func gm20b_platक्रमm_data = अणु
	.iommu_bit = 34,
	.require_vdd = true,
	.require_ref_clk = true,
पूर्ण;

अटल स्थिर काष्ठा nvkm_device_tegra_func gp10b_platक्रमm_data = अणु
	.iommu_bit = 36,
	/* घातer provided by generic PM करोमुख्यs */
	.require_vdd = false,
पूर्ण;

अटल स्थिर काष्ठा of_device_id nouveau_platक्रमm_match[] = अणु
	अणु
		.compatible = "nvidia,gk20a",
		.data = &gk20a_platक्रमm_data,
	पूर्ण,
	अणु
		.compatible = "nvidia,gm20b",
		.data = &gm20b_platक्रमm_data,
	पूर्ण,
	अणु
		.compatible = "nvidia,gp10b",
		.data = &gp10b_platक्रमm_data,
	पूर्ण,
	अणु पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(of, nouveau_platक्रमm_match);
#पूर्ण_अगर

काष्ठा platक्रमm_driver nouveau_platक्रमm_driver = अणु
	.driver = अणु
		.name = "nouveau",
		.of_match_table = of_match_ptr(nouveau_platक्रमm_match),
	पूर्ण,
	.probe = nouveau_platक्रमm_probe,
	.हटाओ = nouveau_platक्रमm_हटाओ,
पूर्ण;
