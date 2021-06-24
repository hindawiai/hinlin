<शैली गुरु>
/*
 *  linux/drivers/video/kyro/STG4000Reg.h
 *
 *  Copyright (C) 2002 STMicroelectronics
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file COPYING in the मुख्य directory of this archive
 * क्रम more details.
 */

#अगर_अघोषित _STG4000REG_H
#घोषणा _STG4000REG_H

#घोषणा DWFILL अचिन्हित दीर्घ :32
#घोषणा WFILL अचिन्हित लघु :16

/*
 * Macros that access memory mapped card रेजिस्टरs in PCI space
 * Add an appropriate section क्रम your OS or processor architecture.
 */
#अगर defined(__KERNEL__)
#समावेश <यंत्र/page.h>
#समावेश <यंत्र/पन.स>
#घोषणा STG_WRITE_REG(reg,data) (ग_लिखोl(data,&pSTGReg->reg))
#घोषणा STG_READ_REG(reg)      (पढ़ोl(&pSTGReg->reg))
#अन्यथा
#घोषणा STG_WRITE_REG(reg,data) (pSTGReg->reg = data)
#घोषणा STG_READ_REG(reg)      (pSTGReg->reg)
#पूर्ण_अगर /* __KERNEL__ */

#घोषणा SET_BIT(n) (1<<(n))
#घोषणा CLEAR_BIT(n) (पंचांगp &= ~(1<<n))
#घोषणा CLEAR_BITS_FRM_TO(frm, to) \
अणु\
पूर्णांक i; \
    क्रम(i = frm; i<= to; i++) \
	अणु \
	    पंचांगp &= ~(1<<i); \
	पूर्ण \
पूर्ण

#घोषणा CLEAR_BIT_2(n) (usTemp &= ~(1<<n))
#घोषणा CLEAR_BITS_FRM_TO_2(frm, to) \
अणु\
पूर्णांक i; \
    क्रम(i = frm; i<= to; i++) \
	अणु \
	    usTemp &= ~(1<<i); \
	पूर्ण \
पूर्ण

/* LUT select */
प्रकार क्रमागत _LUT_USES अणु
	NO_LUT = 0, RESERVED, GRAPHICS, OVERLAY
पूर्ण LUT_USES;

/* Primary surface pixel क्रमmat select */
प्रकार क्रमागत _PIXEL_FORMAT अणु
	_8BPP = 0, _15BPP, _16BPP, _24BPP, _32BPP
पूर्ण PIXEL_FORMAT;

/* Overlay blending mode select */
प्रकार क्रमागत _BLEND_MODE अणु
	GRAPHICS_MODE = 0, COLOR_KEY, PER_PIXEL_ALPHA, GLOBAL_ALPHA,
	CK_PIXEL_ALPHA, CK_GLOBAL_ALPHA
पूर्ण OVRL_BLEND_MODE;

/* Overlay Pixel क्रमmat select */
प्रकार क्रमागत _OVRL_PIX_FORMAT अणु
	UYVY, VYUY, YUYV, YVYU
पूर्ण OVRL_PIX_FORMAT;

/* Register Table */
प्रकार काष्ठा अणु
	/* 0h  */
	अस्थिर u32 Thपढ़ो0Enable;	/* 0x0000 */
	अस्थिर u32 Thपढ़ो1Enable;	/* 0x0004 */
	अस्थिर u32 Thपढ़ो0Recover;	/* 0x0008 */
	अस्थिर u32 Thपढ़ो1Recover;	/* 0x000C */
	अस्थिर u32 Thपढ़ो0Step;	/* 0x0010 */
	अस्थिर u32 Thपढ़ो1Step;	/* 0x0014 */
	अस्थिर u32 VideoInStatus;	/* 0x0018 */
	अस्थिर u32 Core2InSignStart;	/* 0x001C */
	अस्थिर u32 Core1ResetVector;	/* 0x0020 */
	अस्थिर u32 Core1ROMOffset;	/* 0x0024 */
	अस्थिर u32 Core1ArbiterPriority;	/* 0x0028 */
	अस्थिर u32 VideoInControl;	/* 0x002C */
	अस्थिर u32 VideoInReg0CtrlA;	/* 0x0030 */
	अस्थिर u32 VideoInReg0CtrlB;	/* 0x0034 */
	अस्थिर u32 VideoInReg1CtrlA;	/* 0x0038 */
	अस्थिर u32 VideoInReg1CtrlB;	/* 0x003C */
	अस्थिर u32 Thपढ़ो0Kicker;	/* 0x0040 */
	अस्थिर u32 Core2InputSign;	/* 0x0044 */
	अस्थिर u32 Thपढ़ो0ProgCtr;	/* 0x0048 */
	अस्थिर u32 Thपढ़ो1ProgCtr;	/* 0x004C */
	अस्थिर u32 Thपढ़ो1Kicker;	/* 0x0050 */
	अस्थिर u32 GPRegister1;	/* 0x0054 */
	अस्थिर u32 GPRegister2;	/* 0x0058 */
	अस्थिर u32 GPRegister3;	/* 0x005C */
	अस्थिर u32 GPRegister4;	/* 0x0060 */
	अस्थिर u32 SerialIntA;	/* 0x0064 */

	अस्थिर u32 Fill0[6];	/* GAP 0x0068 - 0x007C */

	अस्थिर u32 SoftwareReset;	/* 0x0080 */
	अस्थिर u32 SerialIntB;	/* 0x0084 */

	अस्थिर u32 Fill1[37];	/* GAP 0x0088 - 0x011C */

	अस्थिर u32 ROMELQV;	/* 0x011C */
	अस्थिर u32 WLWH;	/* 0x0120 */
	अस्थिर u32 ROMELWL;	/* 0x0124 */

	अस्थिर u32 dwFill_1;	/* GAP 0x0128 */

	अस्थिर u32 IntStatus;	/* 0x012C */
	अस्थिर u32 IntMask;	/* 0x0130 */
	अस्थिर u32 IntClear;	/* 0x0134 */

	अस्थिर u32 Fill2[6];	/* GAP 0x0138 - 0x014C */

	अस्थिर u32 ROMGPIOA;	/* 0x0150 */
	अस्थिर u32 ROMGPIOB;	/* 0x0154 */
	अस्थिर u32 ROMGPIOC;	/* 0x0158 */
	अस्थिर u32 ROMGPIOD;	/* 0x015C */

	अस्थिर u32 Fill3[2];	/* GAP 0x0160 - 0x0168 */

	अस्थिर u32 AGPIntID;	/* 0x0168 */
	अस्थिर u32 AGPIntClassCode;	/* 0x016C */
	अस्थिर u32 AGPIntBIST;	/* 0x0170 */
	अस्थिर u32 AGPIntSSID;	/* 0x0174 */
	अस्थिर u32 AGPIntPMCSR;	/* 0x0178 */
	अस्थिर u32 VGAFrameBufBase;	/* 0x017C */
	अस्थिर u32 VGANotअगरy;	/* 0x0180 */
	अस्थिर u32 DACPLLMode;	/* 0x0184 */
	अस्थिर u32 Core1VideoClockDiv;	/* 0x0188 */
	अस्थिर u32 AGPIntStat;	/* 0x018C */

	/*
	   अस्थिर u32 Fill4[0x0400/4 - 0x0190/4]; //GAP 0x0190 - 0x0400
	   अस्थिर u32 Fill5[0x05FC/4 - 0x0400/4]; //GAP 0x0400 - 0x05FC Fog Table
	   अस्थिर u32 Fill6[0x0604/4 - 0x0600/4]; //GAP 0x0600 - 0x0604
	   अस्थिर u32 Fill7[0x0680/4 - 0x0608/4]; //GAP 0x0608 - 0x0680
	   अस्थिर u32 Fill8[0x07FC/4 - 0x0684/4]; //GAP 0x0684 - 0x07FC
	 */
	अस्थिर u32 Fill4[412];	/* 0x0190 - 0x07FC */

	अस्थिर u32 TACtrlStreamBase;	/* 0x0800 */
	अस्थिर u32 TAObjDataBase;	/* 0x0804 */
	अस्थिर u32 TAPtrDataBase;	/* 0x0808 */
	अस्थिर u32 TARegionDataBase;	/* 0x080C */
	अस्थिर u32 TATailPtrBase;	/* 0x0810 */
	अस्थिर u32 TAPtrRegionSize;	/* 0x0814 */
	अस्थिर u32 TAConfiguration;	/* 0x0818 */
	अस्थिर u32 TAObjDataStartAddr;	/* 0x081C */
	अस्थिर u32 TAObjDataEndAddr;	/* 0x0820 */
	अस्थिर u32 TAXScreenClip;	/* 0x0824 */
	अस्थिर u32 TAYScreenClip;	/* 0x0828 */
	अस्थिर u32 TARHWClamp;	/* 0x082C */
	अस्थिर u32 TARHWCompare;	/* 0x0830 */
	अस्थिर u32 TAStart;	/* 0x0834 */
	अस्थिर u32 TAObjReStart;	/* 0x0838 */
	अस्थिर u32 TAPtrReStart;	/* 0x083C */
	अस्थिर u32 TAStatus1;	/* 0x0840 */
	अस्थिर u32 TAStatus2;	/* 0x0844 */
	अस्थिर u32 TAIntStatus;	/* 0x0848 */
	अस्थिर u32 TAIntMask;	/* 0x084C */

	अस्थिर u32 Fill5[235];	/* GAP 0x0850 - 0x0BF8 */

	अस्थिर u32 TextureAddrThresh;	/* 0x0BFC */
	अस्थिर u32 Core1Translation;	/* 0x0C00 */
	अस्थिर u32 TextureAddrReMap;	/* 0x0C04 */
	अस्थिर u32 RenderOutAGPRemap;	/* 0x0C08 */
	अस्थिर u32 _3DRegionReadTrans;	/* 0x0C0C */
	अस्थिर u32 _3DPtrReadTrans;	/* 0x0C10 */
	अस्थिर u32 _3DParamReadTrans;	/* 0x0C14 */
	अस्थिर u32 _3DRegionReadThresh;	/* 0x0C18 */
	अस्थिर u32 _3DPtrReadThresh;	/* 0x0C1C */
	अस्थिर u32 _3DParamReadThresh;	/* 0x0C20 */
	अस्थिर u32 _3DRegionReadAGPRemap;	/* 0x0C24 */
	अस्थिर u32 _3DPtrReadAGPRemap;	/* 0x0C28 */
	अस्थिर u32 _3DParamReadAGPRemap;	/* 0x0C2C */
	अस्थिर u32 ZBufferAGPRemap;	/* 0x0C30 */
	अस्थिर u32 TAIndexAGPRemap;	/* 0x0C34 */
	अस्थिर u32 TAVertexAGPRemap;	/* 0x0C38 */
	अस्थिर u32 TAUVAddrTrans;	/* 0x0C3C */
	अस्थिर u32 TATailPtrCacheTrans;	/* 0x0C40 */
	अस्थिर u32 TAParamWriteTrans;	/* 0x0C44 */
	अस्थिर u32 TAPtrWriteTrans;	/* 0x0C48 */
	अस्थिर u32 TAParamWriteThresh;	/* 0x0C4C */
	अस्थिर u32 TAPtrWriteThresh;	/* 0x0C50 */
	अस्थिर u32 TATailPtrCacheAGPRe;	/* 0x0C54 */
	अस्थिर u32 TAParamWriteAGPRe;	/* 0x0C58 */
	अस्थिर u32 TAPtrWriteAGPRe;	/* 0x0C5C */
	अस्थिर u32 SDRAMArbiterConf;	/* 0x0C60 */
	अस्थिर u32 SDRAMConf0;	/* 0x0C64 */
	अस्थिर u32 SDRAMConf1;	/* 0x0C68 */
	अस्थिर u32 SDRAMConf2;	/* 0x0C6C */
	अस्थिर u32 SDRAMRefresh;	/* 0x0C70 */
	अस्थिर u32 SDRAMPowerStat;	/* 0x0C74 */

	अस्थिर u32 Fill6[2];	/* GAP 0x0C78 - 0x0C7C */

	अस्थिर u32 RAMBistData;	/* 0x0C80 */
	अस्थिर u32 RAMBistCtrl;	/* 0x0C84 */
	अस्थिर u32 FIFOBistKey;	/* 0x0C88 */
	अस्थिर u32 RAMBistResult;	/* 0x0C8C */
	अस्थिर u32 FIFOBistResult;	/* 0x0C90 */

	/*
	   अस्थिर u32 Fill11[0x0CBC/4 - 0x0C94/4]; //GAP 0x0C94 - 0x0CBC
	   अस्थिर u32 Fill12[0x0CD0/4 - 0x0CC0/4]; //GAP 0x0CC0 - 0x0CD0 3DRegisters
	 */

	अस्थिर u32 Fill7[16];	/* 0x0c94 - 0x0cd0 */

	अस्थिर u32 SDRAMAddrSign;	/* 0x0CD4 */
	अस्थिर u32 SDRAMDataSign;	/* 0x0CD8 */
	अस्थिर u32 SDRAMSignConf;	/* 0x0CDC */

	/* DWFILL; //GAP 0x0CE0 */
	अस्थिर u32 dwFill_2;

	अस्थिर u32 ISPSignature;	/* 0x0CE4 */

	अस्थिर u32 Fill8[454];	/*GAP 0x0CE8 - 0x13FC */

	अस्थिर u32 DACPrimAddress;	/* 0x1400 */
	अस्थिर u32 DACPrimSize;	/* 0x1404 */
	अस्थिर u32 DACCursorAddr;	/* 0x1408 */
	अस्थिर u32 DACCursorCtrl;	/* 0x140C */
	अस्थिर u32 DACOverlayAddr;	/* 0x1410 */
	अस्थिर u32 DACOverlayUAddr;	/* 0x1414 */
	अस्थिर u32 DACOverlayVAddr;	/* 0x1418 */
	अस्थिर u32 DACOverlaySize;	/* 0x141C */
	अस्थिर u32 DACOverlayVtDec;	/* 0x1420 */

	अस्थिर u32 Fill9[9];	/* GAP 0x1424 - 0x1444 */

	अस्थिर u32 DACVerticalScal;	/* 0x1448 */
	अस्थिर u32 DACPixelFormat;	/* 0x144C */
	अस्थिर u32 DACHorizontalScal;	/* 0x1450 */
	अस्थिर u32 DACVidWinStart;	/* 0x1454 */
	अस्थिर u32 DACVidWinEnd;	/* 0x1458 */
	अस्थिर u32 DACBlendCtrl;	/* 0x145C */
	अस्थिर u32 DACHorTim1;	/* 0x1460 */
	अस्थिर u32 DACHorTim2;	/* 0x1464 */
	अस्थिर u32 DACHorTim3;	/* 0x1468 */
	अस्थिर u32 DACVerTim1;	/* 0x146C */
	अस्थिर u32 DACVerTim2;	/* 0x1470 */
	अस्थिर u32 DACVerTim3;	/* 0x1474 */
	अस्थिर u32 DACBorderColor;	/* 0x1478 */
	अस्थिर u32 DACSyncCtrl;	/* 0x147C */
	अस्थिर u32 DACStreamCtrl;	/* 0x1480 */
	अस्थिर u32 DACLUTAddress;	/* 0x1484 */
	अस्थिर u32 DACLUTData;	/* 0x1488 */
	अस्थिर u32 DACBurstCtrl;	/* 0x148C */
	अस्थिर u32 DACCrcTrigger;	/* 0x1490 */
	अस्थिर u32 DACCrcDone;	/* 0x1494 */
	अस्थिर u32 DACCrcResult1;	/* 0x1498 */
	अस्थिर u32 DACCrcResult2;	/* 0x149C */
	अस्थिर u32 DACLinecount;	/* 0x14A0 */

	अस्थिर u32 Fill10[151];	/*GAP 0x14A4 - 0x16FC */

	अस्थिर u32 DigVidPortCtrl;	/* 0x1700 */
	अस्थिर u32 DigVidPortStat;	/* 0x1704 */

	/*
	   अस्थिर u32 Fill11[0x1FFC/4 - 0x1708/4]; //GAP 0x1708 - 0x1FFC
	   अस्थिर u32 Fill17[0x3000/4 - 0x2FFC/4]; //GAP 0x2000 - 0x2FFC ALUT
	 */

	अस्थिर u32 Fill11[1598];

	/* DWFILL; //GAP 0x3000          ALUT 256MB offset */
	अस्थिर u32 Fill_3;

पूर्ण STG4000REG;

#पूर्ण_अगर /* _STG4000REG_H */
