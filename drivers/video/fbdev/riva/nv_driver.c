<शैली गुरु>
/* $XConsortium: nv_driver.c /मुख्य/3 1996/10/28 05:13:37 kaleb $ */
/*
 * Copyright 1996-1997  David J. McKay
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
 * DAVID J. MCKAY BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF
 * OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

/*
 * GPL licensing note -- nVidia is allowing a liberal पूर्णांकerpretation of
 * the करोcumentation restriction above, to merely say that this nVidia's
 * copyright and disclaimer should be included with all code derived
 * from this source.  -- Jeff Garzik <jgarzik@pobox.com>, 01/Nov/99 
 */

/* Hacked together from mga driver and 3.3.4 NVIDIA driver by Jarno Paananen
   <jpaana@s2.org> */

/* $XFree86: xc/programs/Xserver/hw/xमुक्त86/drivers/nv/nv_setup.c,v 1.18 2002/08/0
5 20:47:06 mvojkovi Exp $ */

#समावेश <linux/delay.h>
#समावेश <linux/pci.h>
#समावेश <linux/pci_ids.h>
#समावेश "nv_type.h"
#समावेश "rivafb.h"
#समावेश "nvreg.h"

#घोषणा PFX "rivafb: "

अटल अंतरभूत अचिन्हित अक्षर MISCin(काष्ठा riva_par *par)
अणु
	वापस (VGA_RD08(par->riva.PVIO, 0x3cc));
पूर्ण

अटल Bool 
riva_is_connected(काष्ठा riva_par *par, Bool second)
अणु
	अस्थिर U032 __iomem *PRAMDAC = par->riva.PRAMDAC0;
	U032 reg52C, reg608;
	Bool present;

	अगर(second) PRAMDAC += 0x800;

	reg52C = NV_RD32(PRAMDAC, 0x052C);
	reg608 = NV_RD32(PRAMDAC, 0x0608);

	NV_WR32(PRAMDAC, 0x0608, reg608 & ~0x00010000);

	NV_WR32(PRAMDAC, 0x052C, reg52C & 0x0000FEEE);
	mdelay(1); 
	NV_WR32(PRAMDAC, 0x052C, NV_RD32(PRAMDAC, 0x052C) | 1);

	NV_WR32(par->riva.PRAMDAC0, 0x0610, 0x94050140);
	NV_WR32(par->riva.PRAMDAC0, 0x0608, 0x00001000);

	mdelay(1);

	present = (NV_RD32(PRAMDAC, 0x0608) & (1 << 28)) ? TRUE : FALSE;

	NV_WR32(par->riva.PRAMDAC0, 0x0608,
		NV_RD32(par->riva.PRAMDAC0, 0x0608) & 0x0000EFFF);

	NV_WR32(PRAMDAC, 0x052C, reg52C);
	NV_WR32(PRAMDAC, 0x0608, reg608);

	वापस present;
पूर्ण

अटल व्योम
riva_override_CRTC(काष्ठा riva_par *par)
अणु
	prपूर्णांकk(KERN_INFO PFX
		"Detected CRTC controller %i being used\n",
		par->SecondCRTC ? 1 : 0);

	अगर(par->क्रमceCRTC != -1) अणु
		prपूर्णांकk(KERN_INFO PFX
			"Forcing usage of CRTC %i\n", par->क्रमceCRTC);
		par->SecondCRTC = par->क्रमceCRTC;
	पूर्ण
पूर्ण

अटल व्योम
riva_is_second(काष्ठा riva_par *par)
अणु
	अगर (par->FlatPanel == 1) अणु
		चयन(par->Chipset & 0xffff) अणु
		हाल 0x0174:
		हाल 0x0175:
		हाल 0x0176:
		हाल 0x0177:
		हाल 0x0179:
		हाल 0x017C:
		हाल 0x017D:
		हाल 0x0186:
		हाल 0x0187:
		/* this might not be a good शेष क्रम the chips below */
		हाल 0x0286:
		हाल 0x028C:
		हाल 0x0316:
		हाल 0x0317:
		हाल 0x031A:
		हाल 0x031B:
		हाल 0x031C:
		हाल 0x031D:
		हाल 0x031E:
		हाल 0x031F:
		हाल 0x0324:
		हाल 0x0325:
		हाल 0x0328:
		हाल 0x0329:
		हाल 0x032C:
		हाल 0x032D:
			par->SecondCRTC = TRUE;
			अवरोध;
		शेष:
			par->SecondCRTC = FALSE;
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर(riva_is_connected(par, 0)) अणु

			अगर (NV_RD32(par->riva.PRAMDAC0, 0x0000052C) & 0x100)
				par->SecondCRTC = TRUE;
			अन्यथा
				par->SecondCRTC = FALSE;
		पूर्ण अन्यथा 
		अगर (riva_is_connected(par, 1)) अणु
			अगर(NV_RD32(par->riva.PRAMDAC0, 0x0000252C) & 0x100)
				par->SecondCRTC = TRUE;
			अन्यथा
				par->SecondCRTC = FALSE;
		पूर्ण अन्यथा /* शेष */
			par->SecondCRTC = FALSE;
	पूर्ण
	riva_override_CRTC(par);
पूर्ण

अचिन्हित दीर्घ riva_get_memlen(काष्ठा riva_par *par)
अणु
	RIVA_HW_INST *chip = &par->riva;
	अचिन्हित दीर्घ memlen = 0;
	अचिन्हित पूर्णांक chipset = par->Chipset;
	काष्ठा pci_dev* dev;
	u32 amt;
	पूर्णांक करोमुख्य = pci_करोमुख्य_nr(par->pdev->bus);

	चयन (chip->Architecture) अणु
	हाल NV_ARCH_03:
		अगर (NV_RD32(chip->PFB, 0x00000000) & 0x00000020) अणु
			अगर (((NV_RD32(chip->PMC, 0x00000000) & 0xF0) == 0x20)
			    && ((NV_RD32(chip->PMC, 0x00000000)&0x0F)>=0x02)) अणु
				/*
				 * SDRAM 128 ZX.
				 */
				चयन (NV_RD32(chip->PFB,0x00000000) & 0x03) अणु
				हाल 2:
					memlen = 1024 * 4;
					अवरोध;
				हाल 1:
					memlen = 1024 * 2;
					अवरोध;
				शेष:
					memlen = 1024 * 8;
					अवरोध;
				पूर्ण
			पूर्ण अन्यथा अणु
				memlen = 1024 * 8;
			पूर्ण            
		पूर्ण अन्यथा 	अणु
			/*
			 * SGRAM 128.
			 */
			चयन (NV_RD32(chip->PFB, 0x00000000) & 0x00000003) अणु
			हाल 0:
				memlen = 1024 * 8;
				अवरोध;
			हाल 2:
				memlen = 1024 * 4;
				अवरोध;
			शेष:
				memlen = 1024 * 2;
				अवरोध;
			पूर्ण
		पूर्ण        
		अवरोध;
	हाल NV_ARCH_04:
		अगर (NV_RD32(chip->PFB, 0x00000000) & 0x00000100) अणु
			memlen = ((NV_RD32(chip->PFB, 0x00000000)>>12)&0x0F) *
				1024 * 2 + 1024 * 2;
		पूर्ण अन्यथा अणु
			चयन (NV_RD32(chip->PFB, 0x00000000) & 0x00000003) अणु
			हाल 0:
				memlen = 1024 * 32;
				अवरोध;
			हाल 1:
				memlen = 1024 * 4;
				अवरोध;
			हाल 2:
				memlen = 1024 * 8;
				अवरोध;
			हाल 3:
			शेष:
				memlen = 1024 * 16;
				अवरोध;
			पूर्ण
		पूर्ण
		अवरोध;
	हाल NV_ARCH_10:
	हाल NV_ARCH_20:
	हाल NV_ARCH_30:
		अगर(chipset == NV_CHIP_IGEFORCE2) अणु

			dev = pci_get_करोमुख्य_bus_and_slot(करोमुख्य, 0, 1);
			pci_पढ़ो_config_dword(dev, 0x7C, &amt);
			pci_dev_put(dev);
			memlen = (((amt >> 6) & 31) + 1) * 1024;
		पूर्ण अन्यथा अगर (chipset == NV_CHIP_0x01F0) अणु
			dev = pci_get_करोमुख्य_bus_and_slot(करोमुख्य, 0, 1);
			pci_पढ़ो_config_dword(dev, 0x84, &amt);
			pci_dev_put(dev);
			memlen = (((amt >> 4) & 127) + 1) * 1024;
		पूर्ण अन्यथा अणु
			चयन ((NV_RD32(chip->PFB, 0x0000020C) >> 20) &
				0x000000FF)अणु
			हाल 0x02:
				memlen = 1024 * 2;
				अवरोध;
			हाल 0x04:
				memlen = 1024 * 4;
				अवरोध;
			हाल 0x08:
				memlen = 1024 * 8;
				अवरोध;
			हाल 0x10:
				memlen = 1024 * 16;
				अवरोध;
			हाल 0x20:
				memlen = 1024 * 32;
				अवरोध;
			हाल 0x40:
				memlen = 1024 * 64;
				अवरोध;
			हाल 0x80:
				memlen = 1024 * 128;
				अवरोध;
			शेष:
				memlen = 1024 * 16;
				अवरोध;
			पूर्ण
		पूर्ण
		अवरोध;
	पूर्ण
	वापस memlen;
पूर्ण

अचिन्हित दीर्घ riva_get_maxdclk(काष्ठा riva_par *par)
अणु
	RIVA_HW_INST *chip = &par->riva;
	अचिन्हित दीर्घ dclk = 0;

	चयन (chip->Architecture) अणु
	हाल NV_ARCH_03:
		अगर (NV_RD32(chip->PFB, 0x00000000) & 0x00000020) अणु
			अगर (((NV_RD32(chip->PMC, 0x00000000) & 0xF0) == 0x20)
			    && ((NV_RD32(chip->PMC,0x00000000)&0x0F) >= 0x02)) अणु
				/*
				 * SDRAM 128 ZX.
				 */
				dclk = 800000;
			पूर्ण अन्यथा अणु
				dclk = 1000000;
			पूर्ण            
		पूर्ण अन्यथा अणु
			/*
			 * SGRAM 128.
			 */
			dclk = 1000000;
		पूर्ण 
		अवरोध;
	हाल NV_ARCH_04:
	हाल NV_ARCH_10:
	हाल NV_ARCH_20:
	हाल NV_ARCH_30:
		चयन ((NV_RD32(chip->PFB, 0x00000000) >> 3) & 0x00000003) अणु
		हाल 3:
			dclk = 800000;
			अवरोध;
		शेष:
			dclk = 1000000;
			अवरोध;
		पूर्ण
		अवरोध;
	पूर्ण
	वापस dclk;
पूर्ण

व्योम
riva_common_setup(काष्ठा riva_par *par)
अणु
	par->riva.EnableIRQ = 0;
	par->riva.PRAMDAC0 =
		(अस्थिर U032 __iomem *)(par->ctrl_base + 0x00680000);
	par->riva.PFB =
		(अस्थिर U032 __iomem *)(par->ctrl_base + 0x00100000);
	par->riva.PFIFO =
		(अस्थिर U032 __iomem *)(par->ctrl_base + 0x00002000);
	par->riva.PGRAPH =
		(अस्थिर U032 __iomem *)(par->ctrl_base + 0x00400000);
	par->riva.PEXTDEV =
		(अस्थिर U032 __iomem *)(par->ctrl_base + 0x00101000);
	par->riva.PTIMER =
		(अस्थिर U032 __iomem *)(par->ctrl_base + 0x00009000);
	par->riva.PMC =
		(अस्थिर U032 __iomem *)(par->ctrl_base + 0x00000000);
	par->riva.FIFO =
		(अस्थिर U032 __iomem *)(par->ctrl_base + 0x00800000);
	par->riva.PCIO0 = par->ctrl_base + 0x00601000;
	par->riva.PDIO0 = par->ctrl_base + 0x00681000;
	par->riva.PVIO = par->ctrl_base + 0x000C0000;

	par->riva.IO = (MISCin(par) & 0x01) ? 0x3D0 : 0x3B0;
	
	अगर (par->FlatPanel == -1) अणु
		चयन (par->Chipset & 0xffff) अणु
		हाल 0x0112:   /* known laptop chips */
		हाल 0x0174:
		हाल 0x0175:
		हाल 0x0176:
		हाल 0x0177:
		हाल 0x0179:
		हाल 0x017C:
		हाल 0x017D:
		हाल 0x0186:
		हाल 0x0187:
		हाल 0x0286:
		हाल 0x028C:
		हाल 0x0316:
		हाल 0x0317:
		हाल 0x031A:
		हाल 0x031B:
		हाल 0x031C:
		हाल 0x031D:
		हाल 0x031E:
		हाल 0x031F:
		हाल 0x0324:
		हाल 0x0325:
		हाल 0x0328:
		हाल 0x0329:
		हाल 0x032C:
		हाल 0x032D:
			prपूर्णांकk(KERN_INFO PFX 
				"On a laptop.  Assuming Digital Flat Panel\n");
			par->FlatPanel = 1;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण
	
	चयन (par->Chipset & 0x0ff0) अणु
	हाल 0x0110:
		अगर (par->Chipset == NV_CHIP_GEFORCE2_GO)
			par->SecondCRTC = TRUE; 
#अगर defined(__घातerpc__)
		अगर (par->FlatPanel == 1)
			par->SecondCRTC = TRUE;
#पूर्ण_अगर
		riva_override_CRTC(par);
		अवरोध;
	हाल 0x0170:
	हाल 0x0180:
	हाल 0x01F0:
	हाल 0x0250:
	हाल 0x0280:
	हाल 0x0300:
	हाल 0x0310:
	हाल 0x0320:
	हाल 0x0330:
	हाल 0x0340:
		riva_is_second(par);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	अगर (par->SecondCRTC) अणु
		par->riva.PCIO = par->riva.PCIO0 + 0x2000;
		par->riva.PCRTC = par->riva.PCRTC0 + 0x800;
		par->riva.PRAMDAC = par->riva.PRAMDAC0 + 0x800;
		par->riva.PDIO = par->riva.PDIO0 + 0x2000;
	पूर्ण अन्यथा अणु
		par->riva.PCIO = par->riva.PCIO0;
		par->riva.PCRTC = par->riva.PCRTC0;
		par->riva.PRAMDAC = par->riva.PRAMDAC0;
		par->riva.PDIO = par->riva.PDIO0;
	पूर्ण

	अगर (par->FlatPanel == -1) अणु
		/* Fix me, need x86 DDC code */
		par->FlatPanel = 0;
	पूर्ण
	par->riva.flatPanel = (par->FlatPanel > 0) ? TRUE : FALSE;

	RivaGetConfig(&par->riva, par->pdev, par->Chipset);
पूर्ण

