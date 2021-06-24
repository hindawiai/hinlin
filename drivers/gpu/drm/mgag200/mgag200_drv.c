<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright 2012 Red Hat
 *
 * Authors: Matthew Garrett
 *          Dave Airlie
 */

#समावेश <linux/console.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/vदो_स्मृति.h>

#समावेश <drm/drm_drv.h>
#समावेश <drm/drm_file.h>
#समावेश <drm/drm_ioctl.h>
#समावेश <drm/drm_pciids.h>

#समावेश "mgag200_drv.h"

पूर्णांक mgag200_modeset = -1;
MODULE_PARM_DESC(modeset, "Disable/Enable modesetting");
module_param_named(modeset, mgag200_modeset, पूर्णांक, 0400);

/*
 * DRM driver
 */

DEFINE_DRM_GEM_FOPS(mgag200_driver_fops);

अटल स्थिर काष्ठा drm_driver mgag200_driver = अणु
	.driver_features = DRIVER_ATOMIC | DRIVER_GEM | DRIVER_MODESET,
	.fops = &mgag200_driver_fops,
	.name = DRIVER_NAME,
	.desc = DRIVER_DESC,
	.date = DRIVER_DATE,
	.major = DRIVER_MAJOR,
	.minor = DRIVER_MINOR,
	.patchlevel = DRIVER_PATCHLEVEL,
	DRM_GEM_SHMEM_DRIVER_OPS,
पूर्ण;

/*
 * DRM device
 */

अटल bool mgag200_has_sgram(काष्ठा mga_device *mdev)
अणु
	काष्ठा drm_device *dev = &mdev->base;
	काष्ठा pci_dev *pdev = to_pci_dev(dev->dev);
	u32 option;
	पूर्णांक ret;

	ret = pci_पढ़ो_config_dword(pdev, PCI_MGA_OPTION, &option);
	अगर (drm_WARN(dev, ret, "failed to read PCI config dword: %d\n", ret))
		वापस false;

	वापस !!(option & PCI_MGA_OPTION_HARDPWMSK);
पूर्ण

अटल पूर्णांक mgag200_regs_init(काष्ठा mga_device *mdev)
अणु
	काष्ठा drm_device *dev = &mdev->base;
	काष्ठा pci_dev *pdev = to_pci_dev(dev->dev);
	u32 option, option2;
	u8 crtcext3;

	चयन (mdev->type) अणु
	हाल G200_PCI:
	हाल G200_AGP:
		अगर (mgag200_has_sgram(mdev))
			option = 0x4049cd21;
		अन्यथा
			option = 0x40499121;
		option2 = 0x00008000;
		अवरोध;
	हाल G200_SE_A:
	हाल G200_SE_B:
		option = 0x40049120;
		अगर (mgag200_has_sgram(mdev))
			option |= PCI_MGA_OPTION_HARDPWMSK;
		option2 = 0x00008000;
		अवरोध;
	हाल G200_WB:
	हाल G200_EW3:
		option = 0x41049120;
		option2 = 0x0000b000;
		अवरोध;
	हाल G200_EV:
		option = 0x00000120;
		option2 = 0x0000b000;
		अवरोध;
	हाल G200_EH:
	हाल G200_EH3:
		option = 0x00000120;
		option2 = 0x0000b000;
		अवरोध;
	शेष:
		option = 0;
		option2 = 0;
	पूर्ण

	अगर (option)
		pci_ग_लिखो_config_dword(pdev, PCI_MGA_OPTION, option);
	अगर (option2)
		pci_ग_लिखो_config_dword(pdev, PCI_MGA_OPTION2, option2);

	/* BAR 1 contains रेजिस्टरs */
	mdev->rmmio_base = pci_resource_start(pdev, 1);
	mdev->rmmio_size = pci_resource_len(pdev, 1);

	अगर (!devm_request_mem_region(dev->dev, mdev->rmmio_base,
				     mdev->rmmio_size, "mgadrmfb_mmio")) अणु
		drm_err(dev, "can't reserve mmio registers\n");
		वापस -ENOMEM;
	पूर्ण

	mdev->rmmio = pcim_iomap(pdev, 1, 0);
	अगर (mdev->rmmio == शून्य)
		वापस -ENOMEM;

	RREG_ECRT(0x03, crtcext3);
	crtcext3 |= MGAREG_CRTCEXT3_MGAMODE;
	WREG_ECRT(0x03, crtcext3);

	वापस 0;
पूर्ण

अटल व्योम mgag200_g200_पूर्णांकerpret_bios(काष्ठा mga_device *mdev,
					स्थिर अचिन्हित अक्षर *bios,
					माप_प्रकार size)
अणु
	अटल स्थिर अक्षर matrox[] = अणु'M', 'A', 'T', 'R', 'O', 'X'पूर्ण;
	अटल स्थिर अचिन्हित पूर्णांक expected_length[6] = अणु
		0, 64, 64, 64, 128, 128
	पूर्ण;
	काष्ठा drm_device *dev = &mdev->base;
	स्थिर अचिन्हित अक्षर *pins;
	अचिन्हित पूर्णांक pins_len, version;
	पूर्णांक offset;
	पूर्णांक पंचांगp;

	/* Test क्रम MATROX string. */
	अगर (size < 45 + माप(matrox))
		वापस;
	अगर (स_भेद(&bios[45], matrox, माप(matrox)) != 0)
		वापस;

	/* Get the PInS offset. */
	अगर (size < MGA_BIOS_OFFSET + 2)
		वापस;
	offset = (bios[MGA_BIOS_OFFSET + 1] << 8) | bios[MGA_BIOS_OFFSET];

	/* Get PInS data काष्ठाure. */

	अगर (size < offset + 6)
		वापस;
	pins = bios + offset;
	अगर (pins[0] == 0x2e && pins[1] == 0x41) अणु
		version = pins[5];
		pins_len = pins[2];
	पूर्ण अन्यथा अणु
		version = 1;
		pins_len = pins[0] + (pins[1] << 8);
	पूर्ण

	अगर (version < 1 || version > 5) अणु
		drm_warn(dev, "Unknown BIOS PInS version: %d\n", version);
		वापस;
	पूर्ण
	अगर (pins_len != expected_length[version]) अणु
		drm_warn(dev, "Unexpected BIOS PInS size: %d expected: %d\n",
			 pins_len, expected_length[version]);
		वापस;
	पूर्ण
	अगर (size < offset + pins_len)
		वापस;

	drm_dbg_kms(dev, "MATROX BIOS PInS version %d size: %d found\n",
		    version, pins_len);

	/* Extract the घड़ी values */

	चयन (version) अणु
	हाल 1:
		पंचांगp = pins[24] + (pins[25] << 8);
		अगर (पंचांगp)
			mdev->model.g200.pclk_max = पंचांगp * 10;
		अवरोध;
	हाल 2:
		अगर (pins[41] != 0xff)
			mdev->model.g200.pclk_max = (pins[41] + 100) * 1000;
		अवरोध;
	हाल 3:
		अगर (pins[36] != 0xff)
			mdev->model.g200.pclk_max = (pins[36] + 100) * 1000;
		अगर (pins[52] & 0x20)
			mdev->model.g200.ref_clk = 14318;
		अवरोध;
	हाल 4:
		अगर (pins[39] != 0xff)
			mdev->model.g200.pclk_max = pins[39] * 4 * 1000;
		अगर (pins[92] & 0x01)
			mdev->model.g200.ref_clk = 14318;
		अवरोध;
	हाल 5:
		पंचांगp = pins[4] ? 8000 : 6000;
		अगर (pins[123] != 0xff)
			mdev->model.g200.pclk_min = pins[123] * पंचांगp;
		अगर (pins[38] != 0xff)
			mdev->model.g200.pclk_max = pins[38] * पंचांगp;
		अगर (pins[110] & 0x01)
			mdev->model.g200.ref_clk = 14318;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम mgag200_g200_init_refclk(काष्ठा mga_device *mdev)
अणु
	काष्ठा drm_device *dev = &mdev->base;
	काष्ठा pci_dev *pdev = to_pci_dev(dev->dev);
	अचिन्हित अक्षर __iomem *rom;
	अचिन्हित अक्षर *bios;
	माप_प्रकार size;

	mdev->model.g200.pclk_min = 50000;
	mdev->model.g200.pclk_max = 230000;
	mdev->model.g200.ref_clk = 27050;

	rom = pci_map_rom(pdev, &size);
	अगर (!rom)
		वापस;

	bios = vदो_स्मृति(size);
	अगर (!bios)
		जाओ out;
	स_नकल_fromio(bios, rom, size);

	अगर (size != 0 && bios[0] == 0x55 && bios[1] == 0xaa)
		mgag200_g200_पूर्णांकerpret_bios(mdev, bios, size);

	drm_dbg_kms(dev, "pclk_min: %ld pclk_max: %ld ref_clk: %ld\n",
		    mdev->model.g200.pclk_min, mdev->model.g200.pclk_max,
		    mdev->model.g200.ref_clk);

	vमुक्त(bios);
out:
	pci_unmap_rom(pdev, rom);
पूर्ण

अटल व्योम mgag200_g200se_init_unique_id(काष्ठा mga_device *mdev)
अणु
	काष्ठा drm_device *dev = &mdev->base;

	/* stash G200 SE model number क्रम later use */
	mdev->model.g200se.unique_rev_id = RREG32(0x1e24);

	drm_dbg(dev, "G200 SE unique revision id is 0x%x\n",
		mdev->model.g200se.unique_rev_id);
पूर्ण

अटल पूर्णांक mgag200_device_init(काष्ठा mga_device *mdev, अचिन्हित दीर्घ flags)
अणु
	काष्ठा drm_device *dev = &mdev->base;
	पूर्णांक ret;

	mdev->flags = mgag200_flags_from_driver_data(flags);
	mdev->type = mgag200_type_from_driver_data(flags);

	ret = mgag200_regs_init(mdev);
	अगर (ret)
		वापस ret;

	अगर (mdev->type == G200_PCI || mdev->type == G200_AGP)
		mgag200_g200_init_refclk(mdev);
	अन्यथा अगर (IS_G200_SE(mdev))
		mgag200_g200se_init_unique_id(mdev);

	ret = mgag200_mm_init(mdev);
	अगर (ret)
		वापस ret;

	ret = mgag200_modeset_init(mdev);
	अगर (ret) अणु
		drm_err(dev, "Fatal error during modeset init: %d\n", ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा mga_device *
mgag200_device_create(काष्ठा pci_dev *pdev, अचिन्हित दीर्घ flags)
अणु
	काष्ठा drm_device *dev;
	काष्ठा mga_device *mdev;
	पूर्णांक ret;

	mdev = devm_drm_dev_alloc(&pdev->dev, &mgag200_driver,
				  काष्ठा mga_device, base);
	अगर (IS_ERR(mdev))
		वापस mdev;
	dev = &mdev->base;

	pci_set_drvdata(pdev, dev);

	ret = mgag200_device_init(mdev, flags);
	अगर (ret)
		वापस ERR_PTR(ret);

	वापस mdev;
पूर्ण

/*
 * PCI driver
 */

अटल स्थिर काष्ठा pci_device_id mgag200_pciidlist[] = अणु
	अणु PCI_VENDOR_ID_MATROX, 0x520, PCI_ANY_ID, PCI_ANY_ID, 0, 0, G200_PCI पूर्ण,
	अणु PCI_VENDOR_ID_MATROX, 0x521, PCI_ANY_ID, PCI_ANY_ID, 0, 0, G200_AGP पूर्ण,
	अणु PCI_VENDOR_ID_MATROX, 0x522, PCI_ANY_ID, PCI_ANY_ID, 0, 0,
		G200_SE_A | MGAG200_FLAG_HW_BUG_NO_STARTADDपूर्ण,
	अणु PCI_VENDOR_ID_MATROX, 0x524, PCI_ANY_ID, PCI_ANY_ID, 0, 0, G200_SE_B पूर्ण,
	अणु PCI_VENDOR_ID_MATROX, 0x530, PCI_ANY_ID, PCI_ANY_ID, 0, 0, G200_EV पूर्ण,
	अणु PCI_VENDOR_ID_MATROX, 0x532, PCI_ANY_ID, PCI_ANY_ID, 0, 0, G200_WB पूर्ण,
	अणु PCI_VENDOR_ID_MATROX, 0x533, PCI_ANY_ID, PCI_ANY_ID, 0, 0, G200_EH पूर्ण,
	अणु PCI_VENDOR_ID_MATROX, 0x534, PCI_ANY_ID, PCI_ANY_ID, 0, 0, G200_ER पूर्ण,
	अणु PCI_VENDOR_ID_MATROX, 0x536, PCI_ANY_ID, PCI_ANY_ID, 0, 0, G200_EW3 पूर्ण,
	अणु PCI_VENDOR_ID_MATROX, 0x538, PCI_ANY_ID, PCI_ANY_ID, 0, 0, G200_EH3 पूर्ण,
	अणु0,पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(pci, mgag200_pciidlist);

अटल पूर्णांक
mgag200_pci_probe(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *ent)
अणु
	काष्ठा mga_device *mdev;
	काष्ठा drm_device *dev;
	पूर्णांक ret;

	drm_fb_helper_हटाओ_conflicting_pci_framebuffers(pdev, "mgag200drmfb");

	ret = pcim_enable_device(pdev);
	अगर (ret)
		वापस ret;

	mdev = mgag200_device_create(pdev, ent->driver_data);
	अगर (IS_ERR(mdev))
		वापस PTR_ERR(mdev);
	dev = &mdev->base;

	ret = drm_dev_रेजिस्टर(dev, ent->driver_data);
	अगर (ret)
		वापस ret;

	drm_fbdev_generic_setup(dev, 0);

	वापस 0;
पूर्ण

अटल व्योम mgag200_pci_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा drm_device *dev = pci_get_drvdata(pdev);

	drm_dev_unरेजिस्टर(dev);
पूर्ण

अटल काष्ठा pci_driver mgag200_pci_driver = अणु
	.name = DRIVER_NAME,
	.id_table = mgag200_pciidlist,
	.probe = mgag200_pci_probe,
	.हटाओ = mgag200_pci_हटाओ,
पूर्ण;

अटल पूर्णांक __init mgag200_init(व्योम)
अणु
	अगर (vgacon_text_क्रमce() && mgag200_modeset == -1)
		वापस -EINVAL;

	अगर (mgag200_modeset == 0)
		वापस -EINVAL;

	वापस pci_रेजिस्टर_driver(&mgag200_pci_driver);
पूर्ण

अटल व्योम __निकास mgag200_निकास(व्योम)
अणु
	pci_unरेजिस्टर_driver(&mgag200_pci_driver);
पूर्ण

module_init(mgag200_init);
module_निकास(mgag200_निकास);

MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_LICENSE("GPL");
