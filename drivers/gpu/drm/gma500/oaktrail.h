<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/**************************************************************************
 * Copyright (c) 2007-2011, Intel Corporation.
 * All Rights Reserved.
 *
 **************************************************************************/

काष्ठा psb_पूर्णांकel_mode_device;

/* MID device specअगरic descriptors */

काष्ठा oaktrail_timing_info अणु
	u16 pixel_घड़ी;
	u8 hactive_lo;
	u8 hblank_lo;
	u8 hblank_hi:4;
	u8 hactive_hi:4;
	u8 vactive_lo;
	u8 vblank_lo;
	u8 vblank_hi:4;
	u8 vactive_hi:4;
	u8 hsync_offset_lo;
	u8 hsync_pulse_width_lo;
	u8 vsync_pulse_width_lo:4;
	u8 vsync_offset_lo:4;
	u8 vsync_pulse_width_hi:2;
	u8 vsync_offset_hi:2;
	u8 hsync_pulse_width_hi:2;
	u8 hsync_offset_hi:2;
	u8 width_mm_lo;
	u8 height_mm_lo;
	u8 height_mm_hi:4;
	u8 width_mm_hi:4;
	u8 hborder;
	u8 vborder;
	u8 unknown0:1;
	u8 hsync_positive:1;
	u8 vsync_positive:1;
	u8 separate_sync:2;
	u8 stereo:1;
	u8 unknown6:1;
	u8 पूर्णांकerlaced:1;
पूर्ण __packed;

काष्ठा gct_r10_timing_info अणु
	u16 pixel_घड़ी;
	u32 hactive_lo:8;
	u32 hactive_hi:4;
	u32 hblank_lo:8;
	u32 hblank_hi:4;
	u32 hsync_offset_lo:8;
	u16 hsync_offset_hi:2;
	u16 hsync_pulse_width_lo:8;
	u16 hsync_pulse_width_hi:2;
	u16 hsync_positive:1;
	u16 rsvd_1:3;
	u8  vactive_lo:8;
	u16 vactive_hi:4;
	u16 vblank_lo:8;
	u16 vblank_hi:4;
	u16 vsync_offset_lo:4;
	u16 vsync_offset_hi:2;
	u16 vsync_pulse_width_lo:4;
	u16 vsync_pulse_width_hi:2;
	u16 vsync_positive:1;
	u16 rsvd_2:3;
पूर्ण __packed;

काष्ठा oaktrail_panel_descriptor_v1 अणु
	u32 Panel_Port_Control; /* 1 dword, Register 0x61180 अगर LVDS */
				/* 0x61190 अगर MIPI */
	u32 Panel_Power_On_Sequencing;/*1 dword,Register 0x61208,*/
	u32 Panel_Power_Off_Sequencing;/*1 dword,Register 0x6120C,*/
	u32 Panel_Power_Cycle_Delay_and_Reference_Divisor;/* 1 dword */
						/* Register 0x61210 */
	काष्ठा oaktrail_timing_info DTD;/*18 bytes, Standard definition */
	u16 Panel_Backlight_Inverter_Descriptor;/* 16 bits, as follows */
				/* Bit 0, Frequency, 15 bits,0 - 32767Hz */
			/* Bit 15, Polarity, 1 bit, 0: Normal, 1: Inverted */
	u16 Panel_MIPI_Display_Descriptor;
			/*16 bits, Defined as follows: */
			/* अगर MIPI, 0x0000 अगर LVDS */
			/* Bit 0, Type, 2 bits, */
			/* 0: Type-1, */
			/* 1: Type-2, */
			/* 2: Type-3, */
			/* 3: Type-4 */
			/* Bit 2, Pixel Format, 4 bits */
			/* Bit0: 16bpp (not supported in LNC), */
			/* Bit1: 18bpp loosely packed, */
			/* Bit2: 18bpp packed, */
			/* Bit3: 24bpp */
			/* Bit 6, Reserved, 2 bits, 00b */
			/* Bit 8, Minimum Supported Frame Rate, 6 bits, 0 - 63Hz */
			/* Bit 14, Reserved, 2 bits, 00b */
पूर्ण __packed;

काष्ठा oaktrail_panel_descriptor_v2 अणु
	u32 Panel_Port_Control; /* 1 dword, Register 0x61180 अगर LVDS */
				/* 0x61190 अगर MIPI */
	u32 Panel_Power_On_Sequencing;/*1 dword,Register 0x61208,*/
	u32 Panel_Power_Off_Sequencing;/*1 dword,Register 0x6120C,*/
	u8 Panel_Power_Cycle_Delay_and_Reference_Divisor;/* 1 byte */
						/* Register 0x61210 */
	काष्ठा oaktrail_timing_info DTD;/*18 bytes, Standard definition */
	u16 Panel_Backlight_Inverter_Descriptor;/*16 bits, as follows*/
				/*Bit 0, Frequency, 16 bits, 0 - 32767Hz*/
	u8 Panel_Initial_Brightness;/* [7:0] 0 - 100% */
			/*Bit 7, Polarity, 1 bit,0: Normal, 1: Inverted*/
	u16 Panel_MIPI_Display_Descriptor;
			/*16 bits, Defined as follows: */
			/* अगर MIPI, 0x0000 अगर LVDS */
			/* Bit 0, Type, 2 bits, */
			/* 0: Type-1, */
			/* 1: Type-2, */
			/* 2: Type-3, */
			/* 3: Type-4 */
			/* Bit 2, Pixel Format, 4 bits */
			/* Bit0: 16bpp (not supported in LNC), */
			/* Bit1: 18bpp loosely packed, */
			/* Bit2: 18bpp packed, */
			/* Bit3: 24bpp */
			/* Bit 6, Reserved, 2 bits, 00b */
			/* Bit 8, Minimum Supported Frame Rate, 6 bits, 0 - 63Hz */
			/* Bit 14, Reserved, 2 bits, 00b */
पूर्ण __packed;

जोड़ oaktrail_panel_rx अणु
	काष्ठा अणु
		u16 NumberOfLanes:2; /*Num of Lanes, 2 bits,0 = 1 lane,*/
			/* 1 = 2 lanes, 2 = 3 lanes, 3 = 4 lanes. */
		u16 MaxLaneFreq:3; /* 0: 100MHz, 1: 200MHz, 2: 300MHz, */
		/*3: 400MHz, 4: 500MHz, 5: 600MHz, 6: 700MHz, 7: 800MHz.*/
		u16 SupportedVideoTransferMode:2; /*0: Non-burst only */
					/* 1: Burst and non-burst */
					/* 2/3: Reserved */
		u16 HSClkBehavior:1; /*0: Continuous, 1: Non-continuous*/
		u16 DuoDisplaySupport:1; /*1 bit,0: No, 1: Yes*/
		u16 ECC_ChecksumCapabilities:1;/*1 bit,0: No, 1: Yes*/
		u16 BidirectionalCommunication:1;/*1 bit,0: No, 1: Yes */
		u16 Rsvd:5;/*5 bits,00000b */
	पूर्ण panelrx;
	u16 panel_receiver;
पूर्ण __packed;

काष्ठा gct_r0 अणु
	जोड़ अणु /*8 bits,Defined as follows: */
		काष्ठा अणु
			u8 PanelType:4; /*4 bits, Bit field क्रम panels*/
					/* 0 - 3: 0 = LVDS, 1 = MIPI*/
					/*2 bits,Specअगरies which of the*/
			u8 BootPanelIndex:2;
					/* 4 panels to use by शेष*/
			u8 BootMIPI_DSI_RxIndex:2;/*Specअगरies which of*/
					/* the 4 MIPI DSI receivers to use*/
		पूर्ण PD;
		u8 PanelDescriptor;
	पूर्ण;
	काष्ठा oaktrail_panel_descriptor_v1 panel[4];/*panel descrs,38 bytes each*/
	जोड़ oaktrail_panel_rx panelrx[4]; /* panel receivers*/
पूर्ण __packed;

काष्ठा gct_r1 अणु
	जोड़ अणु /*8 bits,Defined as follows: */
		काष्ठा अणु
			u8 PanelType:4; /*4 bits, Bit field क्रम panels*/
					/* 0 - 3: 0 = LVDS, 1 = MIPI*/
					/*2 bits,Specअगरies which of the*/
			u8 BootPanelIndex:2;
					/* 4 panels to use by शेष*/
			u8 BootMIPI_DSI_RxIndex:2;/*Specअगरies which of*/
					/* the 4 MIPI DSI receivers to use*/
		पूर्ण PD;
		u8 PanelDescriptor;
	पूर्ण;
	काष्ठा oaktrail_panel_descriptor_v2 panel[4];/*panel descrs,38 bytes each*/
	जोड़ oaktrail_panel_rx panelrx[4]; /* panel receivers*/
पूर्ण __packed;

काष्ठा gct_r10 अणु
	काष्ठा gct_r10_timing_info DTD;
	u16 Panel_MIPI_Display_Descriptor;
	u16 Panel_MIPI_Receiver_Descriptor;
	u16 Panel_Backlight_Inverter_Descriptor;
	u8 Panel_Initial_Brightness;
	u32 MIPI_Ctlr_Init_ptr;
	u32 MIPI_Panel_Init_ptr;
पूर्ण __packed;

काष्ठा oaktrail_gct_data अणु
	u8 bpi; /* boot panel index, number of panel used during boot */
	u8 pt; /* panel type, 4 bit field, 0=lvds, 1=mipi */
	काष्ठा oaktrail_timing_info DTD; /* timing info क्रम the selected panel */
	u32 Panel_Port_Control;
	u32 PP_On_Sequencing;/*1 dword,Register 0x61208,*/
	u32 PP_Off_Sequencing;/*1 dword,Register 0x6120C,*/
	u32 PP_Cycle_Delay;
	u16 Panel_Backlight_Inverter_Descriptor;
	u16 Panel_MIPI_Display_Descriptor;
पूर्ण __packed;

#घोषणा MODE_SETTING_IN_CRTC		0x1
#घोषणा MODE_SETTING_IN_ENCODER		0x2
#घोषणा MODE_SETTING_ON_GOING		0x3
#घोषणा MODE_SETTING_IN_DSR		0x4
#घोषणा MODE_SETTING_ENCODER_DONE	0x8

/*
 *	Moorestown HDMI पूर्णांकerfaces
 */

काष्ठा oaktrail_hdmi_dev अणु
	काष्ठा pci_dev *dev;
	व्योम __iomem *regs;
	अचिन्हित पूर्णांक mmio, mmio_len;
	पूर्णांक dpms_mode;
	काष्ठा hdmi_i2c_dev *i2c_dev;

	/* रेजिस्टर state */
	u32 saveDPLL_CTRL;
	u32 saveDPLL_DIV_CTRL;
	u32 saveDPLL_ADJUST;
	u32 saveDPLL_UPDATE;
	u32 saveDPLL_CLK_ENABLE;
	u32 savePCH_HTOTAL_B;
	u32 savePCH_HBLANK_B;
	u32 savePCH_HSYNC_B;
	u32 savePCH_VTOTAL_B;
	u32 savePCH_VBLANK_B;
	u32 savePCH_VSYNC_B;
	u32 savePCH_PIPEBCONF;
	u32 savePCH_PIPEBSRC;
पूर्ण;

बाह्य व्योम oaktrail_hdmi_setup(काष्ठा drm_device *dev);
बाह्य व्योम oaktrail_hdmi_tearकरोwn(काष्ठा drm_device *dev);
बाह्य पूर्णांक  oaktrail_hdmi_i2c_init(काष्ठा pci_dev *dev);
बाह्य व्योम oaktrail_hdmi_i2c_निकास(काष्ठा pci_dev *dev);
बाह्य व्योम oaktrail_hdmi_save(काष्ठा drm_device *dev);
बाह्य व्योम oaktrail_hdmi_restore(काष्ठा drm_device *dev);
बाह्य व्योम oaktrail_hdmi_init(काष्ठा drm_device *dev, काष्ठा psb_पूर्णांकel_mode_device *mode_dev);
बाह्य पूर्णांक oaktrail_crtc_hdmi_mode_set(काष्ठा drm_crtc *crtc, काष्ठा drm_display_mode *mode,
						काष्ठा drm_display_mode *adjusted_mode, पूर्णांक x, पूर्णांक y,
						काष्ठा drm_framebuffer *old_fb);
बाह्य व्योम oaktrail_crtc_hdmi_dpms(काष्ठा drm_crtc *crtc, पूर्णांक mode);


