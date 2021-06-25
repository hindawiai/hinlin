<शैली गुरु>
/*
 * Copyright 2008 Red Hat Inc.
 * Copyright 2009 Jerome Glisse.
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
 * THE COPYRIGHT HOLDER(S) OR AUTHOR(S) BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * Authors:
 *    Dave Airlie
 *    Jerome Glisse <glisse@मुक्तdesktop.org>
 */

#समावेश <linux/pci.h>

#समावेश <drm/drm_agpsupport.h>
#समावेश <drm/drm_device.h>
#समावेश <drm/radeon_drm.h>

#समावेश "radeon.h"

#अगर IS_ENABLED(CONFIG_AGP)

काष्ठा radeon_agpmode_quirk अणु
	u32 hostbridge_venकरोr;
	u32 hostbridge_device;
	u32 chip_venकरोr;
	u32 chip_device;
	u32 subsys_venकरोr;
	u32 subsys_device;
	u32 शेष_mode;
पूर्ण;

अटल काष्ठा radeon_agpmode_quirk radeon_agpmode_quirk_list[] = अणु
	/* Intel E7505 Memory Controller Hub / RV350 AR [Radeon 9600XT] Needs AGPMode 4 (deb #515326) */
	अणु PCI_VENDOR_ID_INTEL, 0x2550, PCI_VENDOR_ID_ATI, 0x4152, 0x1458, 0x4038, 4पूर्ण,
	/* Intel 82865G/PE/P DRAM Controller/Host-Hub / Mobility 9800 Needs AGPMode 4 (deb #462590) */
	अणु PCI_VENDOR_ID_INTEL, 0x2570, PCI_VENDOR_ID_ATI, 0x4a4e, PCI_VENDOR_ID_DELL, 0x5106, 4पूर्ण,
	/* Intel 82865G/PE/P DRAM Controller/Host-Hub / RV280 [Radeon 9200 SE] Needs AGPMode 4 (lp #300304) */
	अणु PCI_VENDOR_ID_INTEL, 0x2570, PCI_VENDOR_ID_ATI, 0x5964,
		0x148c, 0x2073, 4पूर्ण,
	/* Intel 82855PM Processor to I/O Controller / Mobility M6 LY Needs AGPMode 1 (deb #467235) */
	अणु PCI_VENDOR_ID_INTEL, 0x3340, PCI_VENDOR_ID_ATI, 0x4c59,
		PCI_VENDOR_ID_IBM, 0x052f, 1पूर्ण,
	/* Intel 82855PM host bridge / Mobility 9600 M10 RV350 Needs AGPMode 1 (lp #195051) */
	अणु PCI_VENDOR_ID_INTEL, 0x3340, PCI_VENDOR_ID_ATI, 0x4e50,
		PCI_VENDOR_ID_IBM, 0x0550, 1पूर्ण,
	/* Intel 82855PM host bridge / RV250/M9 GL [Mobility FireGL 9000/Radeon 9000] needs AGPMode 1 (Thinkpad T40p) */
	अणु PCI_VENDOR_ID_INTEL, 0x3340, PCI_VENDOR_ID_ATI, 0x4c66,
		PCI_VENDOR_ID_IBM, 0x054d, 1पूर्ण,
	/* Intel 82855PM host bridge / Mobility M7 needs AGPMode 1 */
	अणु PCI_VENDOR_ID_INTEL, 0x3340, PCI_VENDOR_ID_ATI, 0x4c57,
		PCI_VENDOR_ID_IBM, 0x0530, 1पूर्ण,
	/* Intel 82855PM host bridge / FireGL Mobility T2 RV350 Needs AGPMode 2 (fकरो #20647) */
	अणु PCI_VENDOR_ID_INTEL, 0x3340, PCI_VENDOR_ID_ATI, 0x4e54,
		PCI_VENDOR_ID_IBM, 0x054f, 2पूर्ण,
	/* Intel 82855PM host bridge / Mobility M9+ / VaioPCG-V505DX Needs AGPMode 2 (fकरो #17928) */
	अणु PCI_VENDOR_ID_INTEL, 0x3340, PCI_VENDOR_ID_ATI, 0x5c61,
		PCI_VENDOR_ID_SONY, 0x816b, 2पूर्ण,
	/* Intel 82855PM Processor to I/O Controller / Mobility M9+ Needs AGPMode 8 (phoronix क्रमum) */
	अणु PCI_VENDOR_ID_INTEL, 0x3340, PCI_VENDOR_ID_ATI, 0x5c61,
		PCI_VENDOR_ID_SONY, 0x8195, 8पूर्ण,
	/* Intel 82830 830 Chipset Host Bridge / Mobility M6 LY Needs AGPMode 2 (fकरो #17360)*/
	अणु PCI_VENDOR_ID_INTEL, 0x3575, PCI_VENDOR_ID_ATI, 0x4c59,
		PCI_VENDOR_ID_DELL, 0x00e3, 2पूर्ण,
	/* Intel 82852/82855 host bridge / Mobility FireGL 9000 RV250 Needs AGPMode 1 (lp #296617) */
	अणु PCI_VENDOR_ID_INTEL, 0x3580, PCI_VENDOR_ID_ATI, 0x4c66,
		PCI_VENDOR_ID_DELL, 0x0149, 1पूर्ण,
	/* Intel 82855PM host bridge / Mobility FireGL 9000 RV250 Needs AGPMode 1 क्रम suspend/resume */
	अणु PCI_VENDOR_ID_INTEL, 0x3340, PCI_VENDOR_ID_ATI, 0x4c66,
		PCI_VENDOR_ID_IBM, 0x0531, 1पूर्ण,
	/* Intel 82852/82855 host bridge / Mobility 9600 M10 RV350 Needs AGPMode 1 (deb #467460) */
	अणु PCI_VENDOR_ID_INTEL, 0x3580, PCI_VENDOR_ID_ATI, 0x4e50,
		0x1025, 0x0061, 1पूर्ण,
	/* Intel 82852/82855 host bridge / Mobility 9600 M10 RV350 Needs AGPMode 1 (lp #203007) */
	अणु PCI_VENDOR_ID_INTEL, 0x3580, PCI_VENDOR_ID_ATI, 0x4e50,
		0x1025, 0x0064, 1पूर्ण,
	/* Intel 82852/82855 host bridge / Mobility 9600 M10 RV350 Needs AGPMode 1 (lp #141551) */
	अणु PCI_VENDOR_ID_INTEL, 0x3580, PCI_VENDOR_ID_ATI, 0x4e50,
		PCI_VENDOR_ID_ASUSTEK, 0x1942, 1पूर्ण,
	/* Intel 82852/82855 host bridge / Mobility 9600/9700 Needs AGPMode 1 (deb #510208) */
	अणु PCI_VENDOR_ID_INTEL, 0x3580, PCI_VENDOR_ID_ATI, 0x4e50,
		0x10cf, 0x127f, 1पूर्ण,
	/* ASRock K7VT4A+ AGP 8x / ATI Radeon 9250 AGP Needs AGPMode 4 (lp #133192) */
	अणु 0x1849, 0x3189, PCI_VENDOR_ID_ATI, 0x5960,
		0x1787, 0x5960, 4पूर्ण,
	/* VIA K8M800 Host Bridge / RV280 [Radeon 9200 PRO] Needs AGPMode 4 (fकरो #12544) */
	अणु PCI_VENDOR_ID_VIA, 0x0204, PCI_VENDOR_ID_ATI, 0x5960,
		0x17af, 0x2020, 4पूर्ण,
	/* VIA KT880 Host Bridge / RV350 [Radeon 9550] Needs AGPMode 4 (fकरो #19981) */
	अणु PCI_VENDOR_ID_VIA, 0x0269, PCI_VENDOR_ID_ATI, 0x4153,
		PCI_VENDOR_ID_ASUSTEK, 0x003c, 4पूर्ण,
	/* VIA VT8363 Host Bridge / R200 QL [Radeon 8500] Needs AGPMode 2 (lp #141551) */
	अणु PCI_VENDOR_ID_VIA, 0x0305, PCI_VENDOR_ID_ATI, 0x514c,
		PCI_VENDOR_ID_ATI, 0x013a, 2पूर्ण,
	/* VIA VT82C693A Host Bridge / RV280 [Radeon 9200 PRO] Needs AGPMode 2 (deb #515512) */
	अणु PCI_VENDOR_ID_VIA, 0x0691, PCI_VENDOR_ID_ATI, 0x5960,
		PCI_VENDOR_ID_ASUSTEK, 0x004c, 2पूर्ण,
	/* VIA VT82C693A Host Bridge / RV280 [Radeon 9200 PRO] Needs AGPMode 2 */
	अणु PCI_VENDOR_ID_VIA, 0x0691, PCI_VENDOR_ID_ATI, 0x5960,
		PCI_VENDOR_ID_ASUSTEK, 0x0054, 2पूर्ण,
	/* VIA VT8377 Host Bridge / R200 QM [Radeon 9100] Needs AGPMode 4 (deb #461144) */
	अणु PCI_VENDOR_ID_VIA, 0x3189, PCI_VENDOR_ID_ATI, 0x514d,
		0x174b, 0x7149, 4पूर्ण,
	/* VIA VT8377 Host Bridge / RV280 [Radeon 9200 PRO] Needs AGPMode 4 (lp #312693) */
	अणु PCI_VENDOR_ID_VIA, 0x3189, PCI_VENDOR_ID_ATI, 0x5960,
		0x1462, 0x0380, 4पूर्ण,
	/* VIA VT8377 Host Bridge / RV280 Needs AGPMode 4 (ati ML) */
	अणु PCI_VENDOR_ID_VIA, 0x3189, PCI_VENDOR_ID_ATI, 0x5964,
		0x148c, 0x2073, 4पूर्ण,
	/* ATI Host Bridge / RV280 [M9+] Needs AGPMode 1 (phoronix क्रमum) */
	अणु PCI_VENDOR_ID_ATI, 0xcbb2, PCI_VENDOR_ID_ATI, 0x5c61,
		PCI_VENDOR_ID_SONY, 0x8175, 1पूर्ण,
	अणु 0, 0, 0, 0, 0, 0, 0 पूर्ण,
पूर्ण;
#पूर्ण_अगर

पूर्णांक radeon_agp_init(काष्ठा radeon_device *rdev)
अणु
#अगर IS_ENABLED(CONFIG_AGP)
	काष्ठा radeon_agpmode_quirk *p = radeon_agpmode_quirk_list;
	काष्ठा drm_agp_mode mode;
	काष्ठा drm_agp_info info;
	uपूर्णांक32_t agp_status;
	पूर्णांक शेष_mode;
	bool is_v3;
	पूर्णांक ret;

	/* Acquire AGP. */
	ret = drm_agp_acquire(rdev->ddev);
	अगर (ret) अणु
		DRM_ERROR("Unable to acquire AGP: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = drm_agp_info(rdev->ddev, &info);
	अगर (ret) अणु
		drm_agp_release(rdev->ddev);
		DRM_ERROR("Unable to get AGP info: %d\n", ret);
		वापस ret;
	पूर्ण

	अगर (rdev->ddev->agp->agp_info.aper_size < 32) अणु
		drm_agp_release(rdev->ddev);
		dev_warn(rdev->dev, "AGP aperture too small (%zuM) "
			"need at least 32M, disabling AGP\n",
			rdev->ddev->agp->agp_info.aper_size);
		वापस -EINVAL;
	पूर्ण

	mode.mode = info.mode;
	/* chips with the agp to pcie bridge करोn't have the AGP_STATUS रेजिस्टर
	 * Just use the whatever mode the host sets up.
	 */
	अगर (rdev->family <= CHIP_RV350)
		agp_status = (RREG32(RADEON_AGP_STATUS) | RADEON_AGPv3_MODE) & mode.mode;
	अन्यथा
		agp_status = mode.mode;
	is_v3 = !!(agp_status & RADEON_AGPv3_MODE);

	अगर (is_v3) अणु
		शेष_mode = (agp_status & RADEON_AGPv3_8X_MODE) ? 8 : 4;
	पूर्ण अन्यथा अणु
		अगर (agp_status & RADEON_AGP_4X_MODE) अणु
			शेष_mode = 4;
		पूर्ण अन्यथा अगर (agp_status & RADEON_AGP_2X_MODE) अणु
			शेष_mode = 2;
		पूर्ण अन्यथा अणु
			शेष_mode = 1;
		पूर्ण
	पूर्ण

	/* Apply AGPMode Quirks */
	जबतक (p && p->chip_device != 0) अणु
		अगर (info.id_venकरोr == p->hostbridge_venकरोr &&
		    info.id_device == p->hostbridge_device &&
		    rdev->pdev->venकरोr == p->chip_venकरोr &&
		    rdev->pdev->device == p->chip_device &&
		    rdev->pdev->subप्रणाली_venकरोr == p->subsys_venकरोr &&
		    rdev->pdev->subप्रणाली_device == p->subsys_device) अणु
			शेष_mode = p->शेष_mode;
		पूर्ण
		++p;
	पूर्ण

	अगर (radeon_agpmode > 0) अणु
		अगर ((radeon_agpmode < (is_v3 ? 4 : 1)) ||
		    (radeon_agpmode > (is_v3 ? 8 : 4)) ||
		    (radeon_agpmode & (radeon_agpmode - 1))) अणु
			DRM_ERROR("Illegal AGP Mode: %d (valid %s), leaving at %d\n",
				  radeon_agpmode, is_v3 ? "4, 8" : "1, 2, 4",
				  शेष_mode);
			radeon_agpmode = शेष_mode;
		पूर्ण अन्यथा अणु
			DRM_INFO("AGP mode requested: %d\n", radeon_agpmode);
		पूर्ण
	पूर्ण अन्यथा अणु
		radeon_agpmode = शेष_mode;
	पूर्ण

	mode.mode &= ~RADEON_AGP_MODE_MASK;
	अगर (is_v3) अणु
		चयन (radeon_agpmode) अणु
		हाल 8:
			mode.mode |= RADEON_AGPv3_8X_MODE;
			अवरोध;
		हाल 4:
		शेष:
			mode.mode |= RADEON_AGPv3_4X_MODE;
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु
		चयन (radeon_agpmode) अणु
		हाल 4:
			mode.mode |= RADEON_AGP_4X_MODE;
			अवरोध;
		हाल 2:
			mode.mode |= RADEON_AGP_2X_MODE;
			अवरोध;
		हाल 1:
		शेष:
			mode.mode |= RADEON_AGP_1X_MODE;
			अवरोध;
		पूर्ण
	पूर्ण

	mode.mode &= ~RADEON_AGP_FW_MODE; /* disable fw */
	ret = drm_agp_enable(rdev->ddev, mode);
	अगर (ret) अणु
		DRM_ERROR("Unable to enable AGP (mode = 0x%lx)\n", mode.mode);
		drm_agp_release(rdev->ddev);
		वापस ret;
	पूर्ण

	rdev->mc.agp_base = rdev->ddev->agp->agp_info.aper_base;
	rdev->mc.gtt_size = rdev->ddev->agp->agp_info.aper_size << 20;
	rdev->mc.gtt_start = rdev->mc.agp_base;
	rdev->mc.gtt_end = rdev->mc.gtt_start + rdev->mc.gtt_size - 1;
	dev_info(rdev->dev, "GTT: %lluM 0x%08llX - 0x%08llX\n",
		rdev->mc.gtt_size >> 20, rdev->mc.gtt_start, rdev->mc.gtt_end);

	/* workaround some hw issues */
	अगर (rdev->family < CHIP_R200) अणु
		WREG32(RADEON_AGP_CNTL, RREG32(RADEON_AGP_CNTL) | 0x000e0000);
	पूर्ण
	वापस 0;
#अन्यथा
	वापस 0;
#पूर्ण_अगर
पूर्ण

व्योम radeon_agp_resume(काष्ठा radeon_device *rdev)
अणु
#अगर IS_ENABLED(CONFIG_AGP)
	पूर्णांक r;
	अगर (rdev->flags & RADEON_IS_AGP) अणु
		r = radeon_agp_init(rdev);
		अगर (r)
			dev_warn(rdev->dev, "radeon AGP reinit failed\n");
	पूर्ण
#पूर्ण_अगर
पूर्ण

व्योम radeon_agp_fini(काष्ठा radeon_device *rdev)
अणु
#अगर IS_ENABLED(CONFIG_AGP)
	अगर (rdev->ddev->agp && rdev->ddev->agp->acquired) अणु
		drm_agp_release(rdev->ddev);
	पूर्ण
#पूर्ण_अगर
पूर्ण

व्योम radeon_agp_suspend(काष्ठा radeon_device *rdev)
अणु
	radeon_agp_fini(rdev);
पूर्ण
