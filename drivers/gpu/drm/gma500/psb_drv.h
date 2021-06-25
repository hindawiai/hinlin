<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/**************************************************************************
 * Copyright (c) 2007-2011, Intel Corporation.
 * All Rights Reserved.
 *
 **************************************************************************/

#अगर_अघोषित _PSB_DRV_H_
#घोषणा _PSB_DRV_H_

#समावेश <linux/kref.h>
#समावेश <linux/mm_types.h>

#समावेश <drm/drm_device.h>

#समावेश "gma_display.h"
#समावेश "gtt.h"
#समावेश "intel_bios.h"
#समावेश "mmu.h"
#समावेश "oaktrail.h"
#समावेश "opregion.h"
#समावेश "power.h"
#समावेश "psb_intel_drv.h"
#समावेश "psb_reg.h"

#घोषणा DRIVER_AUTHOR "Alan Cox <alan@linux.intel.com> and others"

#घोषणा DRIVER_NAME "gma500"
#घोषणा DRIVER_DESC "DRM driver for the Intel GMA500, GMA600, GMA3600, GMA3650"
#घोषणा DRIVER_DATE "20140314"

#घोषणा DRIVER_MAJOR 1
#घोषणा DRIVER_MINOR 0
#घोषणा DRIVER_PATCHLEVEL 0

/* Append new drm mode definition here, align with libdrm definition */
#घोषणा DRM_MODE_SCALE_NO_SCALE   	2

क्रमागत अणु
	CHIP_PSB_8108 = 0,		/* Poulsbo */
	CHIP_PSB_8109 = 1,		/* Poulsbo */
	CHIP_MRST_4100 = 2,		/* Moorestown/Oaktrail */
पूर्ण;

#घोषणा IS_PSB(drm) ((to_pci_dev((drm)->dev)->device & 0xfffe) == 0x8108)
#घोषणा IS_MRST(drm) ((to_pci_dev((drm)->dev)->device & 0xfff0) == 0x4100)
#घोषणा IS_CDV(drm) ((to_pci_dev((drm)->dev)->device & 0xfff0) == 0x0be0)

/* Hardware offsets */
#घोषणा PSB_VDC_OFFSET		 0x00000000
#घोषणा PSB_VDC_SIZE		 0x000080000
#घोषणा MRST_MMIO_SIZE		 0x0000C0000
#घोषणा PSB_SGX_SIZE		 0x8000
#घोषणा PSB_SGX_OFFSET		 0x00040000
#घोषणा MRST_SGX_OFFSET		 0x00080000

/* PCI resource identअगरiers */
#घोषणा PSB_MMIO_RESOURCE	 0
#घोषणा PSB_AUX_RESOURCE	 0
#घोषणा PSB_GATT_RESOURCE	 2
#घोषणा PSB_GTT_RESOURCE	 3

/* PCI configuration */
#घोषणा PSB_GMCH_CTRL		 0x52
#घोषणा PSB_BSM			 0x5C
#घोषणा _PSB_GMCH_ENABLED	 0x4
#घोषणा PSB_PGETBL_CTL		 0x2020
#घोषणा _PSB_PGETBL_ENABLED	 0x00000001
#घोषणा PSB_SGX_2D_SLAVE_PORT	 0x4000
#घोषणा PSB_LPC_GBA		 0x44

/* TODO: To get rid of */
#घोषणा PSB_TT_PRIV0_LIMIT	 (256*1024*1024)
#घोषणा PSB_TT_PRIV0_PLIMIT	 (PSB_TT_PRIV0_LIMIT >> PAGE_SHIFT)

/* SGX side MMU definitions (these can probably go) */

/* Flags क्रम बाह्यal memory type field */
#घोषणा PSB_MMU_CACHED_MEMORY	  0x0001	/* Bind to MMU only */
#घोषणा PSB_MMU_RO_MEMORY	  0x0002	/* MMU RO memory */
#घोषणा PSB_MMU_WO_MEMORY	  0x0004	/* MMU WO memory */

/* PTE's and PDE's */
#घोषणा PSB_PDE_MASK		  0x003FFFFF
#घोषणा PSB_PDE_SHIFT		  22
#घोषणा PSB_PTE_SHIFT		  12

/* Cache control */
#घोषणा PSB_PTE_VALID		  0x0001	/* PTE / PDE valid */
#घोषणा PSB_PTE_WO		  0x0002	/* Write only */
#घोषणा PSB_PTE_RO		  0x0004	/* Read only */
#घोषणा PSB_PTE_CACHED		  0x0008	/* CPU cache coherent */

/* VDC रेजिस्टरs and bits */
#घोषणा PSB_MSVDX_CLOCKGATING	  0x2064
#घोषणा PSB_TOPAZ_CLOCKGATING	  0x2068
#घोषणा PSB_HWSTAM		  0x2098
#घोषणा PSB_INSTPM		  0x20C0
#घोषणा PSB_INT_IDENTITY_R        0x20A4
#घोषणा _PSB_IRQ_ASLE		  (1<<0)
#घोषणा _MDFLD_PIPEC_EVENT_FLAG   (1<<2)
#घोषणा _MDFLD_PIPEC_VBLANK_FLAG  (1<<3)
#घोषणा _PSB_DPST_PIPEB_FLAG      (1<<4)
#घोषणा _MDFLD_PIPEB_EVENT_FLAG   (1<<4)
#घोषणा _PSB_VSYNC_PIPEB_FLAG	  (1<<5)
#घोषणा _PSB_DPST_PIPEA_FLAG      (1<<6)
#घोषणा _PSB_PIPEA_EVENT_FLAG     (1<<6)
#घोषणा _PSB_VSYNC_PIPEA_FLAG	  (1<<7)
#घोषणा _PSB_IRQ_DISP_HOTSYNC	  (1<<17)
#घोषणा _PSB_IRQ_SGX_FLAG	  (1<<18)
#घोषणा _PSB_IRQ_MSVDX_FLAG	  (1<<19)
#घोषणा _LNC_IRQ_TOPAZ_FLAG	  (1<<20)

#घोषणा _PSB_PIPE_EVENT_FLAG	(_PSB_VSYNC_PIPEA_FLAG | \
				 _PSB_VSYNC_PIPEB_FLAG)

#घोषणा PSB_INT_IDENTITY_R	  0x20A4
#घोषणा PSB_INT_MASK_R		  0x20A8
#घोषणा PSB_INT_ENABLE_R	  0x20A0

#घोषणा _PSB_MMU_ER_MASK      0x0001FF00
#घोषणा _PSB_MMU_ER_HOST      (1 << 16)
#घोषणा GPIOA			0x5010
#घोषणा GPIOB			0x5014
#घोषणा GPIOC			0x5018
#घोषणा GPIOD			0x501c
#घोषणा GPIOE			0x5020
#घोषणा GPIOF			0x5024
#घोषणा GPIOG			0x5028
#घोषणा GPIOH			0x502c
#घोषणा GPIO_CLOCK_सूची_MASK		(1 << 0)
#घोषणा GPIO_CLOCK_सूची_IN		(0 << 1)
#घोषणा GPIO_CLOCK_सूची_OUT		(1 << 1)
#घोषणा GPIO_CLOCK_VAL_MASK		(1 << 2)
#घोषणा GPIO_CLOCK_VAL_OUT		(1 << 3)
#घोषणा GPIO_CLOCK_VAL_IN		(1 << 4)
#घोषणा GPIO_CLOCK_PULLUP_DISABLE	(1 << 5)
#घोषणा GPIO_DATA_सूची_MASK		(1 << 8)
#घोषणा GPIO_DATA_सूची_IN		(0 << 9)
#घोषणा GPIO_DATA_सूची_OUT		(1 << 9)
#घोषणा GPIO_DATA_VAL_MASK		(1 << 10)
#घोषणा GPIO_DATA_VAL_OUT		(1 << 11)
#घोषणा GPIO_DATA_VAL_IN		(1 << 12)
#घोषणा GPIO_DATA_PULLUP_DISABLE	(1 << 13)

#घोषणा VCLK_DIVISOR_VGA0   0x6000
#घोषणा VCLK_DIVISOR_VGA1   0x6004
#घोषणा VCLK_POST_DIV	    0x6010

#घोषणा PSB_COMM_2D (PSB_ENGINE_2D << 4)
#घोषणा PSB_COMM_3D (PSB_ENGINE_3D << 4)
#घोषणा PSB_COMM_TA (PSB_ENGINE_TA << 4)
#घोषणा PSB_COMM_HP (PSB_ENGINE_HP << 4)
#घोषणा PSB_COMM_USER_IRQ (1024 >> 2)
#घोषणा PSB_COMM_USER_IRQ_LOST (PSB_COMM_USER_IRQ + 1)
#घोषणा PSB_COMM_FW (2048 >> 2)

#घोषणा PSB_UIRQ_VISTEST	       1
#घोषणा PSB_UIRQ_OOM_REPLY	       2
#घोषणा PSB_UIRQ_FIRE_TA_REPLY	       3
#घोषणा PSB_UIRQ_FIRE_RASTER_REPLY     4

#घोषणा PSB_2D_SIZE (256*1024*1024)
#घोषणा PSB_MAX_RELOC_PAGES 1024

#घोषणा PSB_LOW_REG_OFFS 0x0204
#घोषणा PSB_HIGH_REG_OFFS 0x0600

#घोषणा PSB_NUM_VBLANKS 2


#घोषणा PSB_2D_SIZE (256*1024*1024)
#घोषणा PSB_MAX_RELOC_PAGES 1024

#घोषणा PSB_LOW_REG_OFFS 0x0204
#घोषणा PSB_HIGH_REG_OFFS 0x0600

#घोषणा PSB_NUM_VBLANKS 2
#घोषणा PSB_WATCHDOG_DELAY (HZ * 2)
#घोषणा PSB_LID_DELAY (HZ / 10)

#घोषणा PSB_PWR_STATE_ON		1
#घोषणा PSB_PWR_STATE_OFF		2

#घोषणा PSB_PMPOLICY_NOPM		0
#घोषणा PSB_PMPOLICY_CLOCKGATING	1
#घोषणा PSB_PMPOLICY_POWERDOWN		2

#घोषणा PSB_PMSTATE_POWERUP		0
#घोषणा PSB_PMSTATE_CLOCKGATED		1
#घोषणा PSB_PMSTATE_POWERDOWN		2
#घोषणा PSB_PCIx_MSI_ADDR_LOC		0x94
#घोषणा PSB_PCIx_MSI_DATA_LOC		0x98

/* Medfield crystal settings */
#घोषणा KSEL_CRYSTAL_19 1
#घोषणा KSEL_BYPASS_19 5
#घोषणा KSEL_BYPASS_25 6
#घोषणा KSEL_BYPASS_83_100 7

काष्ठा drm_fb_helper;

काष्ठा opregion_header;
काष्ठा opregion_acpi;
काष्ठा opregion_swsci;
काष्ठा opregion_asle;

काष्ठा psb_पूर्णांकel_opregion अणु
	काष्ठा opregion_header *header;
	काष्ठा opregion_acpi *acpi;
	काष्ठा opregion_swsci *swsci;
	काष्ठा opregion_asle *asle;
	व्योम *vbt;
	u32 __iomem *lid_state;
	काष्ठा work_काष्ठा asle_work;
पूर्ण;

काष्ठा sdvo_device_mapping अणु
	u8 initialized;
	u8 dvo_port;
	u8 slave_addr;
	u8 dvo_wiring;
	u8 i2c_pin;
	u8 i2c_speed;
	u8 ddc_pin;
पूर्ण;

काष्ठा पूर्णांकel_gmbus अणु
	काष्ठा i2c_adapter adapter;
	काष्ठा i2c_adapter *क्रमce_bit;
	u32 reg0;
पूर्ण;

/* Register offset maps */
काष्ठा psb_offset अणु
	u32	fp0;
	u32	fp1;
	u32	cntr;
	u32	conf;
	u32	src;
	u32	dpll;
	u32	dpll_md;
	u32	htotal;
	u32	hblank;
	u32	hsync;
	u32	vtotal;
	u32	vblank;
	u32	vsync;
	u32	stride;
	u32	size;
	u32	pos;
	u32	surf;
	u32	addr;
	u32	base;
	u32	status;
	u32	linoff;
	u32	tileoff;
	u32	palette;
पूर्ण;

/*
 *	Register save state. This is used to hold the context when the
 *	device is घातered off. In the हाल of Oaktrail this can (but करोes not
 *	yet) include screen blank. Operations occuring during the save
 *	update the रेजिस्टर cache instead.
 */

/* Common status क्रम pipes */
काष्ठा psb_pipe अणु
	u32	fp0;
	u32	fp1;
	u32	cntr;
	u32	conf;
	u32	src;
	u32	dpll;
	u32	dpll_md;
	u32	htotal;
	u32	hblank;
	u32	hsync;
	u32	vtotal;
	u32	vblank;
	u32	vsync;
	u32	stride;
	u32	size;
	u32	pos;
	u32	base;
	u32	surf;
	u32	addr;
	u32	status;
	u32	linoff;
	u32	tileoff;
	u32	palette[256];
पूर्ण;

काष्ठा psb_state अणु
	uपूर्णांक32_t saveVCLK_DIVISOR_VGA0;
	uपूर्णांक32_t saveVCLK_DIVISOR_VGA1;
	uपूर्णांक32_t saveVCLK_POST_DIV;
	uपूर्णांक32_t saveVGACNTRL;
	uपूर्णांक32_t saveADPA;
	uपूर्णांक32_t saveLVDS;
	uपूर्णांक32_t saveDVOA;
	uपूर्णांक32_t saveDVOB;
	uपूर्णांक32_t saveDVOC;
	uपूर्णांक32_t savePP_ON;
	uपूर्णांक32_t savePP_OFF;
	uपूर्णांक32_t savePP_CONTROL;
	uपूर्णांक32_t savePP_CYCLE;
	uपूर्णांक32_t savePFIT_CONTROL;
	uपूर्णांक32_t saveCLOCKGATING;
	uपूर्णांक32_t saveDSPARB;
	uपूर्णांक32_t savePFIT_AUTO_RATIOS;
	uपूर्णांक32_t savePFIT_PGM_RATIOS;
	uपूर्णांक32_t savePP_ON_DELAYS;
	uपूर्णांक32_t savePP_OFF_DELAYS;
	uपूर्णांक32_t savePP_DIVISOR;
	uपूर्णांक32_t saveBCLRPAT_A;
	uपूर्णांक32_t saveBCLRPAT_B;
	uपूर्णांक32_t savePERF_MODE;
	uपूर्णांक32_t saveDSPFW1;
	uपूर्णांक32_t saveDSPFW2;
	uपूर्णांक32_t saveDSPFW3;
	uपूर्णांक32_t saveDSPFW4;
	uपूर्णांक32_t saveDSPFW5;
	uपूर्णांक32_t saveDSPFW6;
	uपूर्णांक32_t saveCHICKENBIT;
	uपूर्णांक32_t saveDSPACURSOR_CTRL;
	uपूर्णांक32_t saveDSPBCURSOR_CTRL;
	uपूर्णांक32_t saveDSPACURSOR_BASE;
	uपूर्णांक32_t saveDSPBCURSOR_BASE;
	uपूर्णांक32_t saveDSPACURSOR_POS;
	uपूर्णांक32_t saveDSPBCURSOR_POS;
	uपूर्णांक32_t saveOV_OVADD;
	uपूर्णांक32_t saveOV_OGAMC0;
	uपूर्णांक32_t saveOV_OGAMC1;
	uपूर्णांक32_t saveOV_OGAMC2;
	uपूर्णांक32_t saveOV_OGAMC3;
	uपूर्णांक32_t saveOV_OGAMC4;
	uपूर्णांक32_t saveOV_OGAMC5;
	uपूर्णांक32_t saveOVC_OVADD;
	uपूर्णांक32_t saveOVC_OGAMC0;
	uपूर्णांक32_t saveOVC_OGAMC1;
	uपूर्णांक32_t saveOVC_OGAMC2;
	uपूर्णांक32_t saveOVC_OGAMC3;
	uपूर्णांक32_t saveOVC_OGAMC4;
	uपूर्णांक32_t saveOVC_OGAMC5;

	/* DPST रेजिस्टर save */
	uपूर्णांक32_t saveHISTOGRAM_INT_CONTROL_REG;
	uपूर्णांक32_t saveHISTOGRAM_LOGIC_CONTROL_REG;
	uपूर्णांक32_t savePWM_CONTROL_LOGIC;
पूर्ण;

काष्ठा cdv_state अणु
	uपूर्णांक32_t saveDSPCLK_GATE_D;
	uपूर्णांक32_t saveRAMCLK_GATE_D;
	uपूर्णांक32_t saveDSPARB;
	uपूर्णांक32_t saveDSPFW[6];
	uपूर्णांक32_t saveADPA;
	uपूर्णांक32_t savePP_CONTROL;
	uपूर्णांक32_t savePFIT_PGM_RATIOS;
	uपूर्णांक32_t saveLVDS;
	uपूर्णांक32_t savePFIT_CONTROL;
	uपूर्णांक32_t savePP_ON_DELAYS;
	uपूर्णांक32_t savePP_OFF_DELAYS;
	uपूर्णांक32_t savePP_CYCLE;
	uपूर्णांक32_t saveVGACNTRL;
	uपूर्णांक32_t saveIER;
	uपूर्णांक32_t saveIMR;
	u8	 saveLBB;
पूर्ण;

काष्ठा psb_save_area अणु
	काष्ठा psb_pipe pipe[3];
	uपूर्णांक32_t saveBSM;
	uपूर्णांक32_t saveVBT;
	जोड़ अणु
	        काष्ठा psb_state psb;
		काष्ठा cdv_state cdv;
	पूर्ण;
	uपूर्णांक32_t saveBLC_PWM_CTL2;
	uपूर्णांक32_t saveBLC_PWM_CTL;
पूर्ण;

काष्ठा psb_ops;

#घोषणा PSB_NUM_PIPE		3

काष्ठा पूर्णांकel_scu_ipc_dev;

काष्ठा drm_psb_निजी अणु
	काष्ठा drm_device *dev;
	काष्ठा pci_dev *aux_pdev; /* Currently only used by mrst */
	काष्ठा pci_dev *lpc_pdev; /* Currently only used by mrst */
	स्थिर काष्ठा psb_ops *ops;
	स्थिर काष्ठा psb_offset *regmap;

	काष्ठा child_device_config *child_dev;
	पूर्णांक child_dev_num;

	काष्ठा psb_gtt gtt;

	/* GTT Memory manager */
	काष्ठा psb_gtt_mm *gtt_mm;
	काष्ठा page *scratch_page;
	u32 __iomem *gtt_map;
	uपूर्णांक32_t stolen_base;
	u8 __iomem *vram_addr;
	अचिन्हित दीर्घ vram_stolen_size;
	पूर्णांक gtt_initialized;
	u16 gmch_ctrl;		/* Saved GTT setup */
	u32 pge_ctl;

	काष्ठा mutex gtt_mutex;
	काष्ठा resource *gtt_mem;	/* Our PCI resource */

	काष्ठा mutex mmap_mutex;

	काष्ठा psb_mmu_driver *mmu;
	काष्ठा psb_mmu_pd *pf_pd;

	/* Register base */
	uपूर्णांक8_t __iomem *sgx_reg;
	uपूर्णांक8_t __iomem *vdc_reg;
	uपूर्णांक8_t __iomem *aux_reg; /* Auxillary vdc pipe regs */
	uपूर्णांक16_t lpc_gpio_base;
	uपूर्णांक32_t gatt_मुक्त_offset;

	/* Fencing / irq */
	uपूर्णांक32_t vdc_irq_mask;
	uपूर्णांक32_t pipestat[PSB_NUM_PIPE];

	spinlock_t irqmask_lock;

	/* Power */
	bool suspended;
	bool display_घातer;
	पूर्णांक display_count;

	/* Modesetting */
	काष्ठा psb_पूर्णांकel_mode_device mode_dev;
	bool modeset;	/* true अगर we have करोne the mode_device setup */

	काष्ठा drm_crtc *plane_to_crtc_mapping[PSB_NUM_PIPE];
	काष्ठा drm_crtc *pipe_to_crtc_mapping[PSB_NUM_PIPE];
	uपूर्णांक32_t num_pipe;

	/* OSPM info (Power management base) (TODO: can go ?) */
	uपूर्णांक32_t ospm_base;

	/* Sizes info */
	u32 fuse_reg_value;
	u32 video_device_fuse;

	/* PCI revision ID क्रम B0:D2:F0 */
	uपूर्णांक8_t platक्रमm_rev_id;

	/* gmbus */
	काष्ठा पूर्णांकel_gmbus *gmbus;
	uपूर्णांक8_t __iomem *gmbus_reg;

	/* Used by SDVO */
	पूर्णांक crt_ddc_pin;
	/* FIXME: The mappings should be parsed from bios but क्रम now we can
		  pretend there are no mappings available */
	काष्ठा sdvo_device_mapping sdvo_mappings[2];
	u32 hotplug_supported_mask;
	काष्ठा drm_property *broadcast_rgb_property;
	काष्ठा drm_property *क्रमce_audio_property;

	/* LVDS info */
	पूर्णांक backlight_duty_cycle;	/* restore backlight to this value */
	bool panel_wants_dither;
	काष्ठा drm_display_mode *panel_fixed_mode;
	काष्ठा drm_display_mode *lfp_lvds_vbt_mode;
	काष्ठा drm_display_mode *sdvo_lvds_vbt_mode;

	काष्ठा bdb_lvds_backlight *lvds_bl; /* LVDS backlight info from VBT */
	काष्ठा psb_पूर्णांकel_i2c_chan *lvds_i2c_bus; /* FIXME: Remove this? */

	/* Feature bits from the VBIOS */
	अचिन्हित पूर्णांक पूर्णांक_tv_support:1;
	अचिन्हित पूर्णांक lvds_dither:1;
	अचिन्हित पूर्णांक lvds_vbt:1;
	अचिन्हित पूर्णांक पूर्णांक_crt_support:1;
	अचिन्हित पूर्णांक lvds_use_ssc:1;
	पूर्णांक lvds_ssc_freq;
	bool is_lvds_on;
	bool is_mipi_on;
	bool lvds_enabled_in_vbt;
	u32 mipi_ctrl_display;

	अचिन्हित पूर्णांक core_freq;
	uपूर्णांक32_t iLVDS_enable;

	/* Runसमय PM state */
	पूर्णांक rpm_enabled;

	/* MID specअगरic */
	bool has_gct;
	काष्ठा oaktrail_gct_data gct_data;

	/* Oaktrail HDMI state */
	काष्ठा oaktrail_hdmi_dev *hdmi_priv;

	/* Register state */
	काष्ठा psb_save_area regs;

	/* MSI reg save */
	uपूर्णांक32_t msi_addr;
	uपूर्णांक32_t msi_data;

	/* Hotplug handling */
	काष्ठा work_काष्ठा hotplug_work;

	/* LID-Switch */
	spinlock_t lid_lock;
	काष्ठा समयr_list lid_समयr;
	काष्ठा psb_पूर्णांकel_opregion opregion;
	u32 lid_last_state;

	/* Watchकरोg */
	uपूर्णांक32_t apm_reg;
	uपूर्णांक16_t apm_base;

	/*
	 * Used क्रम modअगरying backlight from
	 * xअक्रमr -- consider removing and using HAL instead
	 */
	काष्ठा पूर्णांकel_scu_ipc_dev *scu;
	काष्ठा backlight_device *backlight_device;
	काष्ठा drm_property *backlight_property;
	bool backlight_enabled;
	पूर्णांक backlight_level;
	uपूर्णांक32_t blc_adj1;
	uपूर्णांक32_t blc_adj2;

	काष्ठा drm_fb_helper *fb_helper;

	/* Panel brightness */
	पूर्णांक brightness;
	पूर्णांक brightness_adjusted;

	bool dsr_enable;
	u32 dsr_fb_update;
	bool dpi_panel_on[3];
	व्योम *dsi_configs[2];
	u32 bpp;
	u32 bpp2;

	u32 pipeconf[3];
	u32 dspcntr[3];

	bool dplla_96mhz;	/* DPLL data from the VBT */

	काष्ठा अणु
		पूर्णांक rate;
		पूर्णांक lanes;
		पूर्णांक preemphasis;
		पूर्णांक vswing;

		bool initialized;
		bool support;
		पूर्णांक bpp;
		काष्ठा edp_घातer_seq pps;
	पूर्ण edp;
	uपूर्णांक8_t panel_type;
पूर्ण;


/* Operations क्रम each board type */
काष्ठा psb_ops अणु
	स्थिर अक्षर *name;
	पूर्णांक pipes;		/* Number of output pipes */
	पूर्णांक crtcs;		/* Number of CRTCs */
	पूर्णांक sgx_offset;		/* Base offset of SGX device */
	पूर्णांक hdmi_mask;		/* Mask of HDMI CRTCs */
	पूर्णांक lvds_mask;		/* Mask of LVDS CRTCs */
	पूर्णांक sdvo_mask;		/* Mask of SDVO CRTCs */
	पूर्णांक cursor_needs_phys;  /* If cursor base reg need physical address */

	/* Sub functions */
	काष्ठा drm_crtc_helper_funcs स्थिर *crtc_helper;
	काष्ठा drm_crtc_funcs स्थिर *crtc_funcs;
	स्थिर काष्ठा gma_घड़ी_funcs *घड़ी_funcs;

	/* Setup hooks */
	पूर्णांक (*chip_setup)(काष्ठा drm_device *dev);
	व्योम (*chip_tearकरोwn)(काष्ठा drm_device *dev);
	/* Optional helper caller after modeset */
	व्योम (*errata)(काष्ठा drm_device *dev);

	/* Display management hooks */
	पूर्णांक (*output_init)(काष्ठा drm_device *dev);
	पूर्णांक (*hotplug)(काष्ठा drm_device *dev);
	व्योम (*hotplug_enable)(काष्ठा drm_device *dev, bool on);
	/* Power management hooks */
	व्योम (*init_pm)(काष्ठा drm_device *dev);
	पूर्णांक (*save_regs)(काष्ठा drm_device *dev);
	पूर्णांक (*restore_regs)(काष्ठा drm_device *dev);
	व्योम (*save_crtc)(काष्ठा drm_crtc *crtc);
	व्योम (*restore_crtc)(काष्ठा drm_crtc *crtc);
	पूर्णांक (*घातer_up)(काष्ठा drm_device *dev);
	पूर्णांक (*घातer_करोwn)(काष्ठा drm_device *dev);
	व्योम (*update_wm)(काष्ठा drm_device *dev, काष्ठा drm_crtc *crtc);
	व्योम (*disable_sr)(काष्ठा drm_device *dev);

	व्योम (*lvds_bl_घातer)(काष्ठा drm_device *dev, bool on);
#अगर_घोषित CONFIG_BACKLIGHT_CLASS_DEVICE
	/* Backlight */
	पूर्णांक (*backlight_init)(काष्ठा drm_device *dev);
#पूर्ण_अगर
	पूर्णांक i2c_bus;		/* I2C bus identअगरier क्रम Moorestown */
पूर्ण;



बाह्य पूर्णांक drm_crtc_probe_output_modes(काष्ठा drm_device *dev, पूर्णांक, पूर्णांक);
बाह्य पूर्णांक drm_pick_crtcs(काष्ठा drm_device *dev);

अटल अंतरभूत काष्ठा drm_psb_निजी *psb_priv(काष्ठा drm_device *dev)
अणु
	वापस (काष्ठा drm_psb_निजी *) dev->dev_निजी;
पूर्ण

/* psb_irq.c */
बाह्य irqवापस_t psb_irq_handler(पूर्णांक irq, व्योम *arg);
बाह्य व्योम psb_irq_preinstall(काष्ठा drm_device *dev);
बाह्य पूर्णांक psb_irq_postinstall(काष्ठा drm_device *dev);
बाह्य व्योम psb_irq_uninstall(काष्ठा drm_device *dev);

बाह्य व्योम psb_irq_uninstall_islands(काष्ठा drm_device *dev, पूर्णांक hw_islands);
बाह्य पूर्णांक psb_vblank_रुको2(काष्ठा drm_device *dev, अचिन्हित पूर्णांक *sequence);
बाह्य पूर्णांक psb_vblank_रुको(काष्ठा drm_device *dev, अचिन्हित पूर्णांक *sequence);
बाह्य पूर्णांक psb_enable_vblank(काष्ठा drm_crtc *crtc);
बाह्य व्योम psb_disable_vblank(काष्ठा drm_crtc *crtc);
व्योम
psb_enable_pipestat(काष्ठा drm_psb_निजी *dev_priv, पूर्णांक pipe, u32 mask);

व्योम
psb_disable_pipestat(काष्ठा drm_psb_निजी *dev_priv, पूर्णांक pipe, u32 mask);

बाह्य u32 psb_get_vblank_counter(काष्ठा drm_crtc *crtc);

/* framebuffer.c */
बाह्य पूर्णांक psbfb_probed(काष्ठा drm_device *dev);
बाह्य पूर्णांक psbfb_हटाओ(काष्ठा drm_device *dev,
			काष्ठा drm_framebuffer *fb);
/* accel_2d.c */
बाह्य व्योम psb_spank(काष्ठा drm_psb_निजी *dev_priv);

/* psb_reset.c */
बाह्य व्योम psb_lid_समयr_init(काष्ठा drm_psb_निजी *dev_priv);
बाह्य व्योम psb_lid_समयr_takeकरोwn(काष्ठा drm_psb_निजी *dev_priv);
बाह्य व्योम psb_prपूर्णांक_pagefault(काष्ठा drm_psb_निजी *dev_priv);

/* modesetting */
बाह्य व्योम psb_modeset_init(काष्ठा drm_device *dev);
बाह्य व्योम psb_modeset_cleanup(काष्ठा drm_device *dev);
बाह्य पूर्णांक psb_fbdev_init(काष्ठा drm_device *dev);

/* backlight.c */
पूर्णांक gma_backlight_init(काष्ठा drm_device *dev);
व्योम gma_backlight_निकास(काष्ठा drm_device *dev);
व्योम gma_backlight_disable(काष्ठा drm_device *dev);
व्योम gma_backlight_enable(काष्ठा drm_device *dev);
व्योम gma_backlight_set(काष्ठा drm_device *dev, पूर्णांक v);

/* oaktrail_crtc.c */
बाह्य स्थिर काष्ठा drm_crtc_helper_funcs oaktrail_helper_funcs;

/* oaktrail_lvds.c */
बाह्य व्योम oaktrail_lvds_init(काष्ठा drm_device *dev,
		    काष्ठा psb_पूर्णांकel_mode_device *mode_dev);

/* psb_पूर्णांकel_display.c */
बाह्य स्थिर काष्ठा drm_crtc_helper_funcs psb_पूर्णांकel_helper_funcs;
बाह्य स्थिर काष्ठा drm_crtc_funcs gma_पूर्णांकel_crtc_funcs;

/* psb_पूर्णांकel_lvds.c */
बाह्य स्थिर काष्ठा drm_connector_helper_funcs
					psb_पूर्णांकel_lvds_connector_helper_funcs;
बाह्य स्थिर काष्ठा drm_connector_funcs psb_पूर्णांकel_lvds_connector_funcs;

/* gem.c */
बाह्य पूर्णांक psb_gem_dumb_create(काष्ठा drm_file *file, काष्ठा drm_device *dev,
			काष्ठा drm_mode_create_dumb *args);

/* psb_device.c */
बाह्य स्थिर काष्ठा psb_ops psb_chip_ops;

/* oaktrail_device.c */
बाह्य स्थिर काष्ठा psb_ops oaktrail_chip_ops;

/* cdv_device.c */
बाह्य स्थिर काष्ठा psb_ops cdv_chip_ops;

/* Debug prपूर्णांक bits setting */
#घोषणा PSB_D_GENERAL (1 << 0)
#घोषणा PSB_D_INIT    (1 << 1)
#घोषणा PSB_D_IRQ     (1 << 2)
#घोषणा PSB_D_ENTRY   (1 << 3)
/* debug the get H/V BP/FP count */
#घोषणा PSB_D_HV      (1 << 4)
#घोषणा PSB_D_DBI_BF  (1 << 5)
#घोषणा PSB_D_PM      (1 << 6)
#घोषणा PSB_D_RENDER  (1 << 7)
#घोषणा PSB_D_REG     (1 << 8)
#घोषणा PSB_D_MSVDX   (1 << 9)
#घोषणा PSB_D_TOPAZ   (1 << 10)

बाह्य पूर्णांक drm_idle_check_पूर्णांकerval;

/* Utilities */
अटल अंतरभूत u32 MRST_MSG_READ32(पूर्णांक करोमुख्य, uपूर्णांक port, uपूर्णांक offset)
अणु
	पूर्णांक mcr = (0xD0<<24) | (port << 16) | (offset << 8);
	uपूर्णांक32_t ret_val = 0;
	काष्ठा pci_dev *pci_root = pci_get_करोमुख्य_bus_and_slot(करोमुख्य, 0, 0);
	pci_ग_लिखो_config_dword(pci_root, 0xD0, mcr);
	pci_पढ़ो_config_dword(pci_root, 0xD4, &ret_val);
	pci_dev_put(pci_root);
	वापस ret_val;
पूर्ण
अटल अंतरभूत व्योम MRST_MSG_WRITE32(पूर्णांक करोमुख्य, uपूर्णांक port, uपूर्णांक offset,
				    u32 value)
अणु
	पूर्णांक mcr = (0xE0<<24) | (port << 16) | (offset << 8) | 0xF0;
	काष्ठा pci_dev *pci_root = pci_get_करोमुख्य_bus_and_slot(करोमुख्य, 0, 0);
	pci_ग_लिखो_config_dword(pci_root, 0xD4, value);
	pci_ग_लिखो_config_dword(pci_root, 0xD0, mcr);
	pci_dev_put(pci_root);
पूर्ण

अटल अंतरभूत uपूर्णांक32_t REGISTER_READ(काष्ठा drm_device *dev, uपूर्णांक32_t reg)
अणु
	काष्ठा drm_psb_निजी *dev_priv = dev->dev_निजी;
	वापस ioपढ़ो32(dev_priv->vdc_reg + reg);
पूर्ण

अटल अंतरभूत uपूर्णांक32_t REGISTER_READ_AUX(काष्ठा drm_device *dev, uपूर्णांक32_t reg)
अणु
	काष्ठा drm_psb_निजी *dev_priv = dev->dev_निजी;
	वापस ioपढ़ो32(dev_priv->aux_reg + reg);
पूर्ण

#घोषणा REG_READ(reg)	       REGISTER_READ(dev, (reg))
#घोषणा REG_READ_AUX(reg)      REGISTER_READ_AUX(dev, (reg))

/* Useful क्रम post पढ़ोs */
अटल अंतरभूत uपूर्णांक32_t REGISTER_READ_WITH_AUX(काष्ठा drm_device *dev,
					      uपूर्णांक32_t reg, पूर्णांक aux)
अणु
	uपूर्णांक32_t val;

	अगर (aux)
		val = REG_READ_AUX(reg);
	अन्यथा
		val = REG_READ(reg);

	वापस val;
पूर्ण

#घोषणा REG_READ_WITH_AUX(reg, aux) REGISTER_READ_WITH_AUX(dev, (reg), (aux))

अटल अंतरभूत व्योम REGISTER_WRITE(काष्ठा drm_device *dev, uपूर्णांक32_t reg,
				  uपूर्णांक32_t val)
अणु
	काष्ठा drm_psb_निजी *dev_priv = dev->dev_निजी;
	ioग_लिखो32((val), dev_priv->vdc_reg + (reg));
पूर्ण

अटल अंतरभूत व्योम REGISTER_WRITE_AUX(काष्ठा drm_device *dev, uपूर्णांक32_t reg,
				      uपूर्णांक32_t val)
अणु
	काष्ठा drm_psb_निजी *dev_priv = dev->dev_निजी;
	ioग_लिखो32((val), dev_priv->aux_reg + (reg));
पूर्ण

#घोषणा REG_WRITE(reg, val)	REGISTER_WRITE(dev, (reg), (val))
#घोषणा REG_WRITE_AUX(reg, val)	REGISTER_WRITE_AUX(dev, (reg), (val))

अटल अंतरभूत व्योम REGISTER_WRITE_WITH_AUX(काष्ठा drm_device *dev, uपूर्णांक32_t reg,
				      uपूर्णांक32_t val, पूर्णांक aux)
अणु
	अगर (aux)
		REG_WRITE_AUX(reg, val);
	अन्यथा
		REG_WRITE(reg, val);
पूर्ण

#घोषणा REG_WRITE_WITH_AUX(reg, val, aux) REGISTER_WRITE_WITH_AUX(dev, (reg), (val), (aux))

अटल अंतरभूत व्योम REGISTER_WRITE16(काष्ठा drm_device *dev,
					uपूर्णांक32_t reg, uपूर्णांक32_t val)
अणु
	काष्ठा drm_psb_निजी *dev_priv = dev->dev_निजी;
	ioग_लिखो16((val), dev_priv->vdc_reg + (reg));
पूर्ण

#घोषणा REG_WRITE16(reg, val)	  REGISTER_WRITE16(dev, (reg), (val))

अटल अंतरभूत व्योम REGISTER_WRITE8(काष्ठा drm_device *dev,
				       uपूर्णांक32_t reg, uपूर्णांक32_t val)
अणु
	काष्ठा drm_psb_निजी *dev_priv = dev->dev_निजी;
	ioग_लिखो8((val), dev_priv->vdc_reg + (reg));
पूर्ण

#घोषणा REG_WRITE8(reg, val)		REGISTER_WRITE8(dev, (reg), (val))

#घोषणा PSB_WVDC32(_val, _offs)		ioग_लिखो32(_val, dev_priv->vdc_reg + (_offs))
#घोषणा PSB_RVDC32(_offs)		ioपढ़ो32(dev_priv->vdc_reg + (_offs))

/* #घोषणा TRAP_SGX_PM_FAULT 1 */
#अगर_घोषित TRAP_SGX_PM_FAULT
#घोषणा PSB_RSGX32(_offs)						\
(अणु									\
	अगर (inl(dev_priv->apm_base + PSB_APM_STS) & 0x3) अणु		\
		pr_err("access sgx when it's off!! (READ) %s, %d\n",	\
		       __खाता__, __LINE__);				\
		melay(1000);						\
	पूर्ण								\
	ioपढ़ो32(dev_priv->sgx_reg + (_offs));				\
पूर्ण)
#अन्यथा
#घोषणा PSB_RSGX32(_offs)		ioपढ़ो32(dev_priv->sgx_reg + (_offs))
#पूर्ण_अगर
#घोषणा PSB_WSGX32(_val, _offs)		ioग_लिखो32(_val, dev_priv->sgx_reg + (_offs))

#घोषणा MSVDX_REG_DUMP 0

#घोषणा PSB_WMSVDX32(_val, _offs)	ioग_लिखो32(_val, dev_priv->msvdx_reg + (_offs))
#घोषणा PSB_RMSVDX32(_offs)		ioपढ़ो32(dev_priv->msvdx_reg + (_offs))

#पूर्ण_अगर
