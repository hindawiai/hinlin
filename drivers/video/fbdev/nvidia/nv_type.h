<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __NV_TYPE_H__
#घोषणा __NV_TYPE_H__

#समावेश <linux/fb.h>
#समावेश <linux/types.h>
#समावेश <linux/i2c.h>
#समावेश <linux/i2c-algo-bit.h>
#समावेश <video/vga.h>

#घोषणा NV_ARCH_04  0x04
#घोषणा NV_ARCH_10  0x10
#घोषणा NV_ARCH_20  0x20
#घोषणा NV_ARCH_30  0x30
#घोषणा NV_ARCH_40  0x40

#घोषणा BITMASK(t,b) (((अचिन्हित)(1U << (((t)-(b)+1)))-1)  << (b))
#घोषणा MASKEXPAND(mask) BITMASK(1?mask,0?mask)
#घोषणा SetBF(mask,value) ((value) << (0?mask))
#घोषणा GetBF(var,mask) (((अचिन्हित)((var) & MASKEXPAND(mask))) >> (0?mask) )
#घोषणा SetBitField(value,from,to) SetBF(to, GetBF(value,from))
#घोषणा SetBit(n) (1<<(n))
#घोषणा Set8Bits(value) ((value)&0xff)

#घोषणा V_DBLSCAN  1

प्रकार काष्ठा अणु
	पूर्णांक bitsPerPixel;
	पूर्णांक depth;
	पूर्णांक displayWidth;
	पूर्णांक weight;
पूर्ण NVFBLayout;

#घोषणा NUM_SEQ_REGS		0x05
#घोषणा NUM_CRT_REGS		0x41
#घोषणा NUM_GRC_REGS		0x09
#घोषणा NUM_ATC_REGS		0x15

काष्ठा nvidia_par;

काष्ठा nvidia_i2c_chan अणु
	काष्ठा nvidia_par *par;
	अचिन्हित दीर्घ ddc_base;
	काष्ठा i2c_adapter adapter;
	काष्ठा i2c_algo_bit_data algo;
पूर्ण;

प्रकार काष्ठा _riva_hw_state अणु
	u8 attr[NUM_ATC_REGS];
	u8 crtc[NUM_CRT_REGS];
	u8 gra[NUM_GRC_REGS];
	u8 seq[NUM_SEQ_REGS];
	u8 misc_output;
	u32 bpp;
	u32 width;
	u32 height;
	u32 पूर्णांकerlace;
	u32 repaपूर्णांक0;
	u32 repaपूर्णांक1;
	u32 screen;
	u32 scale;
	u32 dither;
	u32 extra;
	u32 fअगरo;
	u32 pixel;
	u32 horiz;
	u32 arbitration0;
	u32 arbitration1;
	u32 pll;
	u32 pllB;
	u32 vpll;
	u32 vpll2;
	u32 vpllB;
	u32 vpll2B;
	u32 pllsel;
	u32 general;
	u32 crtcOwner;
	u32 head;
	u32 head2;
	u32 config;
	u32 cursorConfig;
	u32 cursor0;
	u32 cursor1;
	u32 cursor2;
	u32 timingH;
	u32 timingV;
	u32 displayV;
	u32 crtcSync;
	u32 control;
पूर्ण RIVA_HW_STATE;

काष्ठा riva_regs अणु
	RIVA_HW_STATE ext;
पूर्ण;

काष्ठा nvidia_par अणु
	RIVA_HW_STATE SavedReg;
	RIVA_HW_STATE ModeReg;
	RIVA_HW_STATE initial_state;
	RIVA_HW_STATE *CurrentState;
	काष्ठा vgastate vgastate;
	u32 pseuकरो_palette[16];
	काष्ठा pci_dev *pci_dev;
	u32 Architecture;
	u32 CursorStart;
	पूर्णांक Chipset;
	अचिन्हित दीर्घ FbAddress;
	u8 __iomem *FbStart;
	u32 FbMapSize;
	u32 FbUsableSize;
	u32 ScratchBufferSize;
	u32 ScratchBufferStart;
	पूर्णांक FpScale;
	u32 MinVClockFreqKHz;
	u32 MaxVClockFreqKHz;
	u32 CrystalFreqKHz;
	u32 RamAmountKBytes;
	u32 IOBase;
	NVFBLayout CurrentLayout;
	पूर्णांक cursor_reset;
	पूर्णांक lockup;
	पूर्णांक videoKey;
	पूर्णांक FlatPanel;
	पूर्णांक FPDither;
	पूर्णांक Television;
	पूर्णांक CRTCnumber;
	पूर्णांक alphaCursor;
	पूर्णांक twoHeads;
	पूर्णांक twoStagePLL;
	पूर्णांक fpScaler;
	पूर्णांक fpWidth;
	पूर्णांक fpHeight;
	पूर्णांक PanelTweak;
	पूर्णांक paneltweak;
	पूर्णांक LVDS;
	पूर्णांक pm_state;
	पूर्णांक reverse_i2c;
	u32 crtcSync_पढ़ो;
	u32 fpSyncs;
	u32 dmaPut;
	u32 dmaCurrent;
	u32 dmaFree;
	u32 dmaMax;
	u32 __iomem *dmaBase;
	u32 currentRop;
	पूर्णांक WaitVSyncPossible;
	पूर्णांक BlendingPossible;
	u32 paletteEnabled;
	u32 क्रमceCRTC;
	u32 खोलो_count;
	u8 DDCBase;
	पूर्णांक wc_cookie;
	काष्ठा nvidia_i2c_chan chan[3];

	अस्थिर u32 __iomem *REGS;
	अस्थिर u32 __iomem *PCRTC0;
	अस्थिर u32 __iomem *PCRTC;
	अस्थिर u32 __iomem *PRAMDAC0;
	अस्थिर u32 __iomem *PFB;
	अस्थिर u32 __iomem *PFIFO;
	अस्थिर u32 __iomem *PGRAPH;
	अस्थिर u32 __iomem *PEXTDEV;
	अस्थिर u32 __iomem *PTIMER;
	अस्थिर u32 __iomem *PMC;
	अस्थिर u32 __iomem *PRAMIN;
	अस्थिर u32 __iomem *FIFO;
	अस्थिर u32 __iomem *CURSOR;
	अस्थिर u8 __iomem *PCIO0;
	अस्थिर u8 __iomem *PCIO;
	अस्थिर u8 __iomem *PVIO;
	अस्थिर u8 __iomem *PDIO0;
	अस्थिर u8 __iomem *PDIO;
	अस्थिर u32 __iomem *PRAMDAC;
पूर्ण;

#पूर्ण_अगर				/* __NV_TYPE_H__ */
