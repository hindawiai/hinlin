<शैली गुरु>
 /***************************************************************************\
|*                                                                           *|
|*       Copyright 2003 NVIDIA, Corporation.  All rights reserved.           *|
|*                                                                           *|
|*     NOTICE TO USER:   The source code  is copyrighted under  U.S. and     *|
|*     पूर्णांकernational laws.  Users and possessors of this source code are     *|
|*     hereby granted a nonexclusive,  royalty-मुक्त copyright license to     *|
|*     use this code in inभागidual and commercial software.                  *|
|*                                                                           *|
|*     Any use of this source code must include,  in the user करोcumenta-     *|
|*     tion and  पूर्णांकernal comments to the code,  notices to the end user     *|
|*     as follows:                                                           *|
|*                                                                           *|
|*       Copyright 2003 NVIDIA, Corporation.  All rights reserved.           *|
|*                                                                           *|
|*     NVIDIA, CORPORATION MAKES NO REPRESENTATION ABOUT THE SUITABILITY     *|
|*     OF  THIS SOURCE  CODE  FOR ANY PURPOSE.  IT IS  PROVIDED  "AS IS"     *|
|*     WITHOUT EXPRESS OR IMPLIED WARRANTY OF ANY KIND.  NVIDIA, CORPOR-     *|
|*     ATION DISCLAIMS ALL WARRANTIES  WITH REGARD  TO THIS SOURCE CODE,     *|
|*     INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY, NONINFRINGE-     *|
|*     MENT,  AND FITNESS  FOR A PARTICULAR PURPOSE.   IN NO EVENT SHALL     *|
|*     NVIDIA, CORPORATION  BE LIABLE FOR ANY SPECIAL,  INसूचीECT,  INCI-     *|
|*     DENTAL, OR CONSEQUENTIAL DAMAGES,  OR ANY DAMAGES  WHATSOEVER RE-     *|
|*     SULTING FROM LOSS OF USE,  DATA OR PROFITS,  WHETHER IN AN ACTION     *|
|*     OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION,  ARISING OUT OF     *|
|*     OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOURCE CODE.     *|
|*                                                                           *|
|*     U.S. Government  End  Users.   This source code  is a "commercial     *|
|*     item,"  as that  term is  defined at  48 C.F.R. 2.101 (OCT 1995),     *|
|*     consisting  of "commercial  computer  software"  and  "commercial     *|
|*     computer  software  करोcumentation,"  as such  terms  are  used in     *|
|*     48 C.F.R. 12.212 (SEPT 1995)  and is provided to the U.S. Govern-     *|
|*     ment only as  a commercial end item.   Consistent with  48 C.F.R.     *|
|*     12.212 and  48 C.F.R. 227.7202-1 through  227.7202-4 (JUNE 1995),     *|
|*     all U.S. Government End Users  acquire the source code  with only     *|
|*     those rights set क्रमth herein.                                        *|
|*                                                                           *|
 \***************************************************************************/

/*
 * GPL Licensing Note - According to Mark Vojkovich, author of the Xorg/
 * XFree86 'nv' driver, this source code is provided under MIT-style licensing
 * where the source code is provided "as is" without warranty of any kind.
 * The only usage restriction is क्रम the copyright notices to be retained
 * whenever code is used.
 *
 * Antonino Daplas <adaplas@pol.net> 2005-03-11
 */

#समावेश <video/vga.h>
#समावेश <linux/delay.h>
#समावेश <linux/pci.h>
#समावेश <linux/slab.h>
#समावेश "nv_type.h"
#समावेश "nv_local.h"
#समावेश "nv_proto.h"
/*
 * Override VGA I/O routines.
 */
व्योम NVWriteCrtc(काष्ठा nvidia_par *par, u8 index, u8 value)
अणु
	VGA_WR08(par->PCIO, par->IOBase + 0x04, index);
	VGA_WR08(par->PCIO, par->IOBase + 0x05, value);
पूर्ण
u8 NVReadCrtc(काष्ठा nvidia_par *par, u8 index)
अणु
	VGA_WR08(par->PCIO, par->IOBase + 0x04, index);
	वापस (VGA_RD08(par->PCIO, par->IOBase + 0x05));
पूर्ण
व्योम NVWriteGr(काष्ठा nvidia_par *par, u8 index, u8 value)
अणु
	VGA_WR08(par->PVIO, VGA_GFX_I, index);
	VGA_WR08(par->PVIO, VGA_GFX_D, value);
पूर्ण
u8 NVReadGr(काष्ठा nvidia_par *par, u8 index)
अणु
	VGA_WR08(par->PVIO, VGA_GFX_I, index);
	वापस (VGA_RD08(par->PVIO, VGA_GFX_D));
पूर्ण
व्योम NVWriteSeq(काष्ठा nvidia_par *par, u8 index, u8 value)
अणु
	VGA_WR08(par->PVIO, VGA_SEQ_I, index);
	VGA_WR08(par->PVIO, VGA_SEQ_D, value);
पूर्ण
u8 NVReadSeq(काष्ठा nvidia_par *par, u8 index)
अणु
	VGA_WR08(par->PVIO, VGA_SEQ_I, index);
	वापस (VGA_RD08(par->PVIO, VGA_SEQ_D));
पूर्ण
व्योम NVWriteAttr(काष्ठा nvidia_par *par, u8 index, u8 value)
अणु

	VGA_RD08(par->PCIO, par->IOBase + 0x0a);
	अगर (par->paletteEnabled)
		index &= ~0x20;
	अन्यथा
		index |= 0x20;
	VGA_WR08(par->PCIO, VGA_ATT_IW, index);
	VGA_WR08(par->PCIO, VGA_ATT_W, value);
पूर्ण
u8 NVReadAttr(काष्ठा nvidia_par *par, u8 index)
अणु
	VGA_RD08(par->PCIO, par->IOBase + 0x0a);
	अगर (par->paletteEnabled)
		index &= ~0x20;
	अन्यथा
		index |= 0x20;
	VGA_WR08(par->PCIO, VGA_ATT_IW, index);
	वापस (VGA_RD08(par->PCIO, VGA_ATT_R));
पूर्ण
व्योम NVWriteMiscOut(काष्ठा nvidia_par *par, u8 value)
अणु
	VGA_WR08(par->PVIO, VGA_MIS_W, value);
पूर्ण
u8 NVReadMiscOut(काष्ठा nvidia_par *par)
अणु
	वापस (VGA_RD08(par->PVIO, VGA_MIS_R));
पूर्ण
व्योम NVWriteDacMask(काष्ठा nvidia_par *par, u8 value)
अणु
	VGA_WR08(par->PDIO, VGA_PEL_MSK, value);
पूर्ण
व्योम NVWriteDacReadAddr(काष्ठा nvidia_par *par, u8 value)
अणु
	VGA_WR08(par->PDIO, VGA_PEL_IR, value);
पूर्ण
व्योम NVWriteDacWriteAddr(काष्ठा nvidia_par *par, u8 value)
अणु
	VGA_WR08(par->PDIO, VGA_PEL_IW, value);
पूर्ण
व्योम NVWriteDacData(काष्ठा nvidia_par *par, u8 value)
अणु
	VGA_WR08(par->PDIO, VGA_PEL_D, value);
पूर्ण
u8 NVReadDacData(काष्ठा nvidia_par *par)
अणु
	वापस (VGA_RD08(par->PDIO, VGA_PEL_D));
पूर्ण

अटल पूर्णांक NVIsConnected(काष्ठा nvidia_par *par, पूर्णांक output)
अणु
	अस्थिर u32 __iomem *PRAMDAC = par->PRAMDAC0;
	u32 reg52C, reg608, dac0_reg608 = 0;
	पूर्णांक present;

	अगर (output) अणु
	    dac0_reg608 = NV_RD32(PRAMDAC, 0x0608);
	    PRAMDAC += 0x800;
	पूर्ण

	reg52C = NV_RD32(PRAMDAC, 0x052C);
	reg608 = NV_RD32(PRAMDAC, 0x0608);

	NV_WR32(PRAMDAC, 0x0608, reg608 & ~0x00010000);

	NV_WR32(PRAMDAC, 0x052C, reg52C & 0x0000FEEE);
	msleep(1);
	NV_WR32(PRAMDAC, 0x052C, NV_RD32(PRAMDAC, 0x052C) | 1);

	NV_WR32(par->PRAMDAC0, 0x0610, 0x94050140);
	NV_WR32(par->PRAMDAC0, 0x0608, NV_RD32(par->PRAMDAC0, 0x0608) |
		0x00001000);

	msleep(1);

	present = (NV_RD32(PRAMDAC, 0x0608) & (1 << 28)) ? 1 : 0;

	अगर (present)
		prपूर्णांकk("nvidiafb: CRTC%i analog found\n", output);
	अन्यथा
		prपूर्णांकk("nvidiafb: CRTC%i analog not found\n", output);

	अगर (output)
	    NV_WR32(par->PRAMDAC0, 0x0608, dac0_reg608);

	NV_WR32(PRAMDAC, 0x052C, reg52C);
	NV_WR32(PRAMDAC, 0x0608, reg608);

	वापस present;
पूर्ण

अटल व्योम NVSelectHeadRegisters(काष्ठा nvidia_par *par, पूर्णांक head)
अणु
	अगर (head) अणु
		par->PCIO = par->PCIO0 + 0x2000;
		par->PCRTC = par->PCRTC0 + 0x800;
		par->PRAMDAC = par->PRAMDAC0 + 0x800;
		par->PDIO = par->PDIO0 + 0x2000;
	पूर्ण अन्यथा अणु
		par->PCIO = par->PCIO0;
		par->PCRTC = par->PCRTC0;
		par->PRAMDAC = par->PRAMDAC0;
		par->PDIO = par->PDIO0;
	पूर्ण
पूर्ण

अटल व्योम nv4GetConfig(काष्ठा nvidia_par *par)
अणु
	अगर (NV_RD32(par->PFB, 0x0000) & 0x00000100) अणु
		par->RamAmountKBytes =
		    ((NV_RD32(par->PFB, 0x0000) >> 12) & 0x0F) * 1024 * 2 +
		    1024 * 2;
	पूर्ण अन्यथा अणु
		चयन (NV_RD32(par->PFB, 0x0000) & 0x00000003) अणु
		हाल 0:
			par->RamAmountKBytes = 1024 * 32;
			अवरोध;
		हाल 1:
			par->RamAmountKBytes = 1024 * 4;
			अवरोध;
		हाल 2:
			par->RamAmountKBytes = 1024 * 8;
			अवरोध;
		हाल 3:
		शेष:
			par->RamAmountKBytes = 1024 * 16;
			अवरोध;
		पूर्ण
	पूर्ण
	par->CrystalFreqKHz = (NV_RD32(par->PEXTDEV, 0x0000) & 0x00000040) ?
	    14318 : 13500;
	par->CURSOR = &par->PRAMIN[0x1E00];
	par->MinVClockFreqKHz = 12000;
	par->MaxVClockFreqKHz = 350000;
पूर्ण

अटल व्योम nv10GetConfig(काष्ठा nvidia_par *par)
अणु
	काष्ठा pci_dev *dev;
	u32 implementation = par->Chipset & 0x0ff0;

#अगर_घोषित __BIG_ENDIAN
	/* turn on big endian रेजिस्टर access */
	अगर (!(NV_RD32(par->PMC, 0x0004) & 0x01000001)) अणु
		NV_WR32(par->PMC, 0x0004, 0x01000001);
		mb();
	पूर्ण
#पूर्ण_अगर

	dev = pci_get_करोमुख्य_bus_and_slot(pci_करोमुख्य_nr(par->pci_dev->bus),
					  0, 1);
	अगर ((par->Chipset & 0xffff) == 0x01a0) अणु
		u32 amt;

		pci_पढ़ो_config_dword(dev, 0x7c, &amt);
		par->RamAmountKBytes = (((amt >> 6) & 31) + 1) * 1024;
	पूर्ण अन्यथा अगर ((par->Chipset & 0xffff) == 0x01f0) अणु
		u32 amt;

		pci_पढ़ो_config_dword(dev, 0x84, &amt);
		par->RamAmountKBytes = (((amt >> 4) & 127) + 1) * 1024;
	पूर्ण अन्यथा अणु
		par->RamAmountKBytes =
		    (NV_RD32(par->PFB, 0x020C) & 0xFFF00000) >> 10;
	पूर्ण
	pci_dev_put(dev);

	par->CrystalFreqKHz = (NV_RD32(par->PEXTDEV, 0x0000) & (1 << 6)) ?
	    14318 : 13500;

	अगर (par->twoHeads && (implementation != 0x0110)) अणु
		अगर (NV_RD32(par->PEXTDEV, 0x0000) & (1 << 22))
			par->CrystalFreqKHz = 27000;
	पूर्ण

	par->CURSOR = शून्य;	/* can't set this here */
	par->MinVClockFreqKHz = 12000;
	par->MaxVClockFreqKHz = par->twoStagePLL ? 400000 : 350000;
पूर्ण

पूर्णांक NVCommonSetup(काष्ठा fb_info *info)
अणु
	काष्ठा nvidia_par *par = info->par;
	काष्ठा fb_var_screeninfo *var;
	u16 implementation = par->Chipset & 0x0ff0;
	u8 *edidA = शून्य, *edidB = शून्य;
	काष्ठा fb_monspecs *monitorA, *monitorB;
	काष्ठा fb_monspecs *monA = शून्य, *monB = शून्य;
	पूर्णांक mobile = 0;
	पूर्णांक tvA = 0;
	पूर्णांक tvB = 0;
	पूर्णांक FlatPanel = -1;	/* really means the CRTC is slaved */
	पूर्णांक Television = 0;
	पूर्णांक err = 0;

	var = kzalloc(माप(काष्ठा fb_var_screeninfo), GFP_KERNEL);
	monitorA = kzalloc(माप(काष्ठा fb_monspecs), GFP_KERNEL);
	monitorB = kzalloc(माप(काष्ठा fb_monspecs), GFP_KERNEL);

	अगर (!var || !monitorA || !monitorB) अणु
		err = -ENOMEM;
		जाओ करोne;
	पूर्ण

	par->PRAMIN = par->REGS + (0x00710000 / 4);
	par->PCRTC0 = par->REGS + (0x00600000 / 4);
	par->PRAMDAC0 = par->REGS + (0x00680000 / 4);
	par->PFB = par->REGS + (0x00100000 / 4);
	par->PFIFO = par->REGS + (0x00002000 / 4);
	par->PGRAPH = par->REGS + (0x00400000 / 4);
	par->PEXTDEV = par->REGS + (0x00101000 / 4);
	par->PTIMER = par->REGS + (0x00009000 / 4);
	par->PMC = par->REGS + (0x00000000 / 4);
	par->FIFO = par->REGS + (0x00800000 / 4);

	/* 8 bit रेजिस्टरs */
	par->PCIO0 = (u8 __iomem *) par->REGS + 0x00601000;
	par->PDIO0 = (u8 __iomem *) par->REGS + 0x00681000;
	par->PVIO = (u8 __iomem *) par->REGS + 0x000C0000;

	par->twoHeads = (par->Architecture >= NV_ARCH_10) &&
	    (implementation != 0x0100) &&
	    (implementation != 0x0150) &&
	    (implementation != 0x01A0) && (implementation != 0x0200);

	par->fpScaler = (par->FpScale && par->twoHeads &&
			 (implementation != 0x0110));

	par->twoStagePLL = (implementation == 0x0310) ||
	    (implementation == 0x0340) || (par->Architecture >= NV_ARCH_40);

	par->WaitVSyncPossible = (par->Architecture >= NV_ARCH_10) &&
	    (implementation != 0x0100);

	par->BlendingPossible = ((par->Chipset & 0xffff) != 0x0020);

	/* look क्रम known laptop chips */
	चयन (par->Chipset & 0xffff) अणु
	हाल 0x0112:
	हाल 0x0174:
	हाल 0x0175:
	हाल 0x0176:
	हाल 0x0177:
	हाल 0x0179:
	हाल 0x017C:
	हाल 0x017D:
	हाल 0x0186:
	हाल 0x0187:
	हाल 0x018D:
	हाल 0x01D7:
	हाल 0x0228:
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
	हाल 0x0347:
	हाल 0x0348:
	हाल 0x0349:
	हाल 0x034B:
	हाल 0x034C:
	हाल 0x0160:
	हाल 0x0166:
	हाल 0x0169:
	हाल 0x016B:
	हाल 0x016C:
	हाल 0x016D:
	हाल 0x00C8:
	हाल 0x00CC:
	हाल 0x0144:
	हाल 0x0146:
	हाल 0x0147:
	हाल 0x0148:
	हाल 0x0098:
	हाल 0x0099:
		mobile = 1;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	अगर (par->Architecture == NV_ARCH_04)
		nv4GetConfig(par);
	अन्यथा
		nv10GetConfig(par);

	NVSelectHeadRegisters(par, 0);

	NVLockUnlock(par, 0);

	par->IOBase = (NVReadMiscOut(par) & 0x01) ? 0x3d0 : 0x3b0;

	par->Television = 0;

	nvidia_create_i2c_busses(par);
	अगर (!par->twoHeads) अणु
		par->CRTCnumber = 0;
		अगर (nvidia_probe_i2c_connector(info, 1, &edidA))
			nvidia_probe_of_connector(info, 1, &edidA);
		अगर (edidA && !fb_parse_edid(edidA, var)) अणु
			prपूर्णांकk("nvidiafb: EDID found from BUS1\n");
			monA = monitorA;
			fb_edid_to_monspecs(edidA, monA);
			FlatPanel = (monA->input & FB_DISP_DDI) ? 1 : 0;

			/* NV4 करोesn't support FlatPanels */
			अगर ((par->Chipset & 0x0fff) <= 0x0020)
				FlatPanel = 0;
		पूर्ण अन्यथा अणु
			VGA_WR08(par->PCIO, 0x03D4, 0x28);
			अगर (VGA_RD08(par->PCIO, 0x03D5) & 0x80) अणु
				VGA_WR08(par->PCIO, 0x03D4, 0x33);
				अगर (!(VGA_RD08(par->PCIO, 0x03D5) & 0x01))
					Television = 1;
				FlatPanel = 1;
			पूर्ण अन्यथा अणु
				FlatPanel = 0;
			पूर्ण
			prपूर्णांकk("nvidiafb: HW is currently programmed for %s\n",
			       FlatPanel ? (Television ? "TV" : "DFP") :
			       "CRT");
		पूर्ण

		अगर (par->FlatPanel == -1) अणु
			par->FlatPanel = FlatPanel;
			par->Television = Television;
		पूर्ण अन्यथा अणु
			prपूर्णांकk("nvidiafb: Forcing display type to %s as "
			       "specified\n", par->FlatPanel ? "DFP" : "CRT");
		पूर्ण
	पूर्ण अन्यथा अणु
		u8 outputAfromCRTC, outputBfromCRTC;
		पूर्णांक CRTCnumber = -1;
		u8 slaved_on_A, slaved_on_B;
		पूर्णांक analog_on_A, analog_on_B;
		u32 oldhead;
		u8 cr44;

		अगर (implementation != 0x0110) अणु
			अगर (NV_RD32(par->PRAMDAC0, 0x0000052C) & 0x100)
				outputAfromCRTC = 1;
			अन्यथा
				outputAfromCRTC = 0;
			अगर (NV_RD32(par->PRAMDAC0, 0x0000252C) & 0x100)
				outputBfromCRTC = 1;
			अन्यथा
				outputBfromCRTC = 0;
			analog_on_A = NVIsConnected(par, 0);
			analog_on_B = NVIsConnected(par, 1);
		पूर्ण अन्यथा अणु
			outputAfromCRTC = 0;
			outputBfromCRTC = 1;
			analog_on_A = 0;
			analog_on_B = 0;
		पूर्ण

		VGA_WR08(par->PCIO, 0x03D4, 0x44);
		cr44 = VGA_RD08(par->PCIO, 0x03D5);

		VGA_WR08(par->PCIO, 0x03D5, 3);
		NVSelectHeadRegisters(par, 1);
		NVLockUnlock(par, 0);

		VGA_WR08(par->PCIO, 0x03D4, 0x28);
		slaved_on_B = VGA_RD08(par->PCIO, 0x03D5) & 0x80;
		अगर (slaved_on_B) अणु
			VGA_WR08(par->PCIO, 0x03D4, 0x33);
			tvB = !(VGA_RD08(par->PCIO, 0x03D5) & 0x01);
		पूर्ण

		VGA_WR08(par->PCIO, 0x03D4, 0x44);
		VGA_WR08(par->PCIO, 0x03D5, 0);
		NVSelectHeadRegisters(par, 0);
		NVLockUnlock(par, 0);

		VGA_WR08(par->PCIO, 0x03D4, 0x28);
		slaved_on_A = VGA_RD08(par->PCIO, 0x03D5) & 0x80;
		अगर (slaved_on_A) अणु
			VGA_WR08(par->PCIO, 0x03D4, 0x33);
			tvA = !(VGA_RD08(par->PCIO, 0x03D5) & 0x01);
		पूर्ण

		oldhead = NV_RD32(par->PCRTC0, 0x00000860);
		NV_WR32(par->PCRTC0, 0x00000860, oldhead | 0x00000010);

		अगर (nvidia_probe_i2c_connector(info, 1, &edidA))
			nvidia_probe_of_connector(info, 1, &edidA);
		अगर (edidA && !fb_parse_edid(edidA, var)) अणु
			prपूर्णांकk("nvidiafb: EDID found from BUS1\n");
			monA = monitorA;
			fb_edid_to_monspecs(edidA, monA);
		पूर्ण

		अगर (nvidia_probe_i2c_connector(info, 2, &edidB))
			nvidia_probe_of_connector(info, 2, &edidB);
		अगर (edidB && !fb_parse_edid(edidB, var)) अणु
			prपूर्णांकk("nvidiafb: EDID found from BUS2\n");
			monB = monitorB;
			fb_edid_to_monspecs(edidB, monB);
		पूर्ण

		अगर (slaved_on_A && !tvA) अणु
			CRTCnumber = 0;
			FlatPanel = 1;
			prपूर्णांकk("nvidiafb: CRTC 0 is currently programmed for "
			       "DFP\n");
		पूर्ण अन्यथा अगर (slaved_on_B && !tvB) अणु
			CRTCnumber = 1;
			FlatPanel = 1;
			prपूर्णांकk("nvidiafb: CRTC 1 is currently programmed "
			       "for DFP\n");
		पूर्ण अन्यथा अगर (analog_on_A) अणु
			CRTCnumber = outputAfromCRTC;
			FlatPanel = 0;
			prपूर्णांकk("nvidiafb: CRTC %i appears to have a "
			       "CRT attached\n", CRTCnumber);
		पूर्ण अन्यथा अगर (analog_on_B) अणु
			CRTCnumber = outputBfromCRTC;
			FlatPanel = 0;
			prपूर्णांकk("nvidiafb: CRTC %i appears to have a "
			       "CRT attached\n", CRTCnumber);
		पूर्ण अन्यथा अगर (slaved_on_A) अणु
			CRTCnumber = 0;
			FlatPanel = 1;
			Television = 1;
			prपूर्णांकk("nvidiafb: CRTC 0 is currently programmed "
			       "for TV\n");
		पूर्ण अन्यथा अगर (slaved_on_B) अणु
			CRTCnumber = 1;
			FlatPanel = 1;
			Television = 1;
			prपूर्णांकk("nvidiafb: CRTC 1 is currently programmed for "
			       "TV\n");
		पूर्ण अन्यथा अगर (monA) अणु
			FlatPanel = (monA->input & FB_DISP_DDI) ? 1 : 0;
		पूर्ण अन्यथा अगर (monB) अणु
			FlatPanel = (monB->input & FB_DISP_DDI) ? 1 : 0;
		पूर्ण

		अगर (par->FlatPanel == -1) अणु
			अगर (FlatPanel != -1) अणु
				par->FlatPanel = FlatPanel;
				par->Television = Television;
			पूर्ण अन्यथा अणु
				prपूर्णांकk("nvidiafb: Unable to detect display "
				       "type...\n");
				अगर (mobile) अणु
					prपूर्णांकk("...On a laptop, assuming "
					       "DFP\n");
					par->FlatPanel = 1;
				पूर्ण अन्यथा अणु
					prपूर्णांकk("...Using default of CRT\n");
					par->FlatPanel = 0;
				पूर्ण
			पूर्ण
		पूर्ण अन्यथा अणु
			prपूर्णांकk("nvidiafb: Forcing display type to %s as "
			       "specified\n", par->FlatPanel ? "DFP" : "CRT");
		पूर्ण

		अगर (par->CRTCnumber == -1) अणु
			अगर (CRTCnumber != -1)
				par->CRTCnumber = CRTCnumber;
			अन्यथा अणु
				prपूर्णांकk("nvidiafb: Unable to detect which "
				       "CRTCNumber...\n");
				अगर (par->FlatPanel)
					par->CRTCnumber = 1;
				अन्यथा
					par->CRTCnumber = 0;
				prपूर्णांकk("...Defaulting to CRTCNumber %i\n",
				       par->CRTCnumber);
			पूर्ण
		पूर्ण अन्यथा अणु
			prपूर्णांकk("nvidiafb: Forcing CRTCNumber %i as "
			       "specified\n", par->CRTCnumber);
		पूर्ण

		अगर (monA) अणु
			अगर (((monA->input & FB_DISP_DDI) &&
			     par->FlatPanel) ||
			    ((!(monA->input & FB_DISP_DDI)) &&
			     !par->FlatPanel)) अणु
				अगर (monB) अणु
					fb_destroy_modedb(monB->modedb);
					monB = शून्य;
				पूर्ण
			पूर्ण अन्यथा अणु
				fb_destroy_modedb(monA->modedb);
				monA = शून्य;
			पूर्ण
		पूर्ण

		अगर (monB) अणु
			अगर (((monB->input & FB_DISP_DDI) &&
			     !par->FlatPanel) ||
			    ((!(monB->input & FB_DISP_DDI)) &&
			     par->FlatPanel)) अणु
				fb_destroy_modedb(monB->modedb);
				monB = शून्य;
			पूर्ण अन्यथा
				monA = monB;
		पूर्ण

		अगर (implementation == 0x0110)
			cr44 = par->CRTCnumber * 0x3;

		NV_WR32(par->PCRTC0, 0x00000860, oldhead);

		VGA_WR08(par->PCIO, 0x03D4, 0x44);
		VGA_WR08(par->PCIO, 0x03D5, cr44);
		NVSelectHeadRegisters(par, par->CRTCnumber);
	पूर्ण

	prपूर्णांकk("nvidiafb: Using %s on CRTC %i\n",
	       par->FlatPanel ? (par->Television ? "TV" : "DFP") : "CRT",
	       par->CRTCnumber);

	अगर (par->FlatPanel && !par->Television) अणु
		par->fpWidth = NV_RD32(par->PRAMDAC, 0x0820) + 1;
		par->fpHeight = NV_RD32(par->PRAMDAC, 0x0800) + 1;
		par->fpSyncs = NV_RD32(par->PRAMDAC, 0x0848) & 0x30000033;

		prपूर्णांकk("nvidiafb: Panel size is %i x %i\n", par->fpWidth, par->fpHeight);
	पूर्ण

	अगर (monA)
		info->monspecs = *monA;

	अगर (!par->FlatPanel || !par->twoHeads)
		par->FPDither = 0;

	par->LVDS = 0;
	अगर (par->FlatPanel && par->twoHeads) अणु
		NV_WR32(par->PRAMDAC0, 0x08B0, 0x00010004);
		अगर (NV_RD32(par->PRAMDAC0, 0x08b4) & 1)
			par->LVDS = 1;
		prपूर्णांकk("nvidiafb: Panel is %s\n", par->LVDS ? "LVDS" : "TMDS");
	पूर्ण

	kमुक्त(edidA);
	kमुक्त(edidB);
करोne:
	kमुक्त(var);
	kमुक्त(monitorA);
	kमुक्त(monitorB);
	वापस err;
पूर्ण
