<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _INTELFB_H
#घोषणा _INTELFB_H

/* $DHD: पूर्णांकelfb/पूर्णांकelfb.h,v 1.40 2003/06/27 15:06:25 dawes Exp $ */

#समावेश <linux/agp_backend.h>
#समावेश <linux/fb.h>

#अगर_घोषित CONFIG_FB_INTEL_I2C
#समावेश <linux/i2c.h>
#समावेश <linux/i2c-algo-bit.h>
#पूर्ण_अगर

/*** Version/name ***/
#घोषणा INTELFB_VERSION			"0.9.6"
#घोषणा INTELFB_MODULE_NAME		"intelfb"
#घोषणा SUPPORTED_CHIPSETS		"830M/845G/852GM/855GM/865G/915G/915GM/945G/945GM/945GME/965G/965GM"


/*** Debug/feature defines ***/

#अगर_अघोषित DEBUG
#घोषणा DEBUG				0
#पूर्ण_अगर

#अगर_अघोषित VERBOSE
#घोषणा VERBOSE				0
#पूर्ण_अगर

#अगर_अघोषित REGDUMP
#घोषणा REGDUMP				0
#पूर्ण_अगर

#अगर_अघोषित DETECT_VGA_CLASS_ONLY
#घोषणा DETECT_VGA_CLASS_ONLY		1
#पूर्ण_अगर

#अगर_अघोषित ALLOCATE_FOR_PANNING
#घोषणा ALLOCATE_FOR_PANNING		1
#पूर्ण_अगर

#अगर_अघोषित PREFERRED_MODE
#घोषणा PREFERRED_MODE			"1024x768-32@70"
#पूर्ण_अगर

/*** hw-related values ***/

/* Resource Allocation */
#घोषणा INTELFB_FB_ACQUIRED                 1
#घोषणा INTELFB_MMIO_ACQUIRED               2

/* PCI ids क्रम supported devices */
#घोषणा PCI_DEVICE_ID_INTEL_830M	0x3577
#घोषणा PCI_DEVICE_ID_INTEL_845G	0x2562
#घोषणा PCI_DEVICE_ID_INTEL_85XGM	0x3582
#घोषणा PCI_DEVICE_ID_INTEL_854		0x358E
#घोषणा PCI_DEVICE_ID_INTEL_865G	0x2572
#घोषणा PCI_DEVICE_ID_INTEL_915G	0x2582
#घोषणा PCI_DEVICE_ID_INTEL_915GM	0x2592
#घोषणा PCI_DEVICE_ID_INTEL_945G	0x2772
#घोषणा PCI_DEVICE_ID_INTEL_945GM	0x27A2
#घोषणा PCI_DEVICE_ID_INTEL_945GME	0x27AE
#घोषणा PCI_DEVICE_ID_INTEL_965G	0x29A2
#घोषणा PCI_DEVICE_ID_INTEL_965GM	0x2A02

/* Size of MMIO region */
#घोषणा INTEL_REG_SIZE			0x80000

#घोषणा STRIDE_ALIGNMENT		16
#घोषणा STRIDE_ALIGNMENT_I9XX		64

#घोषणा PALETTE_8_ENTRIES		256


/*** Macros ***/

/* basic arithmetic */
#घोषणा KB(x)			((x) * 1024)
#घोषणा MB(x)			((x) * 1024 * 1024)
#घोषणा BtoKB(x)		((x) / 1024)
#घोषणा BtoMB(x)		((x) / 1024 / 1024)

#घोषणा GTT_PAGE_SIZE           KB(4)

#घोषणा ROUND_UP_TO(x, y)	(((x) + (y) - 1) / (y) * (y))
#घोषणा ROUND_DOWN_TO(x, y)	((x) / (y) * (y))
#घोषणा ROUND_UP_TO_PAGE(x)	ROUND_UP_TO((x), GTT_PAGE_SIZE)
#घोषणा ROUND_DOWN_TO_PAGE(x)	ROUND_DOWN_TO((x), GTT_PAGE_SIZE)

/* messages */
#घोषणा PFX			INTELFB_MODULE_NAME ": "

#घोषणा ERR_MSG(fmt, args...)	prपूर्णांकk(KERN_ERR PFX fmt, ## args)
#घोषणा WRN_MSG(fmt, args...)	prपूर्णांकk(KERN_WARNING PFX fmt, ## args)
#घोषणा NOT_MSG(fmt, args...)	prपूर्णांकk(KERN_NOTICE PFX fmt, ## args)
#घोषणा INF_MSG(fmt, args...)	prपूर्णांकk(KERN_INFO PFX fmt, ## args)
#अगर DEBUG
#घोषणा DBG_MSG(fmt, args...)	prपूर्णांकk(KERN_DEBUG PFX fmt, ## args)
#अन्यथा
#घोषणा DBG_MSG(fmt, args...)	जबतक (0) prपूर्णांकk(fmt, ## args)
#पूर्ण_अगर

/* get commonly used poपूर्णांकers */
#घोषणा GET_DINFO(info)		(info)->par

/* misc macros */
#घोषणा ACCEL(d, i)                                                     \
	((d)->accel && !(d)->ring_lockup &&                             \
	 ((i)->var.accel_flags & FB_ACCELF_TEXT))

/*#घोषणा NOACCEL_CHIPSET(d)						\
	((d)->chipset != INTEL_865G)*/
#घोषणा NOACCEL_CHIPSET(d)						\
	(0)

#घोषणा FIXED_MODE(d) ((d)->fixed_mode)

/*** Driver parameters ***/

#घोषणा RINGBUFFER_SIZE		KB(64)
#घोषणा HW_CURSOR_SIZE		KB(4)

/* Intel agpgart driver */
#घोषणा AGP_PHYSICAL_MEMORY     2

/* store inक्रमmation about an Ixxx DVO */
/* The i830->i865 use multiple DVOs with multiple i2cs */
/* the i915, i945 have a single sDVO i2c bus - which is dअगरferent */
#घोषणा MAX_OUTPUTS 6

/* these are outमाला_दो from the chip - पूर्णांकegrated only
   बाह्यal chips are via DVO or SDVO output */
#घोषणा INTELFB_OUTPUT_UNUSED 0
#घोषणा INTELFB_OUTPUT_ANALOG 1
#घोषणा INTELFB_OUTPUT_DVO 2
#घोषणा INTELFB_OUTPUT_SDVO 3
#घोषणा INTELFB_OUTPUT_LVDS 4
#घोषणा INTELFB_OUTPUT_TVOUT 5

#घोषणा INTELFB_DVO_CHIP_NONE 0
#घोषणा INTELFB_DVO_CHIP_LVDS 1
#घोषणा INTELFB_DVO_CHIP_TMDS 2
#घोषणा INTELFB_DVO_CHIP_TVOUT 4

#घोषणा INTELFB_OUTPUT_PIPE_NC  0
#घोषणा INTELFB_OUTPUT_PIPE_A   1
#घोषणा INTELFB_OUTPUT_PIPE_B   2

/*** Data Types ***/

/* supported chipsets */
क्रमागत पूर्णांकel_chips अणु
	INTEL_830M,
	INTEL_845G,
	INTEL_85XGM,
	INTEL_852GM,
	INTEL_852GME,
	INTEL_854,
	INTEL_855GM,
	INTEL_855GME,
	INTEL_865G,
	INTEL_915G,
	INTEL_915GM,
	INTEL_945G,
	INTEL_945GM,
	INTEL_945GME,
	INTEL_965G,
	INTEL_965GM,
पूर्ण;

काष्ठा पूर्णांकelfb_hwstate अणु
	u32 vga0_भागisor;
	u32 vga1_भागisor;
	u32 vga_pd;
	u32 dpll_a;
	u32 dpll_b;
	u32 fpa0;
	u32 fpa1;
	u32 fpb0;
	u32 fpb1;
	u32 palette_a[PALETTE_8_ENTRIES];
	u32 palette_b[PALETTE_8_ENTRIES];
	u32 htotal_a;
	u32 hblank_a;
	u32 hsync_a;
	u32 vtotal_a;
	u32 vblank_a;
	u32 vsync_a;
	u32 src_size_a;
	u32 bclrpat_a;
	u32 htotal_b;
	u32 hblank_b;
	u32 hsync_b;
	u32 vtotal_b;
	u32 vblank_b;
	u32 vsync_b;
	u32 src_size_b;
	u32 bclrpat_b;
	u32 adpa;
	u32 dvoa;
	u32 dvob;
	u32 dvoc;
	u32 dvoa_srcdim;
	u32 dvob_srcdim;
	u32 dvoc_srcdim;
	u32 lvds;
	u32 pipe_a_conf;
	u32 pipe_b_conf;
	u32 disp_arb;
	u32 cursor_a_control;
	u32 cursor_b_control;
	u32 cursor_a_base;
	u32 cursor_b_base;
	u32 cursor_size;
	u32 disp_a_ctrl;
	u32 disp_b_ctrl;
	u32 disp_a_base;
	u32 disp_b_base;
	u32 cursor_a_palette[4];
	u32 cursor_b_palette[4];
	u32 disp_a_stride;
	u32 disp_b_stride;
	u32 vgacntrl;
	u32 add_id;
	u32 swf0x[7];
	u32 swf1x[7];
	u32 swf3x[3];
	u32 fence[8];
	u32 instpm;
	u32 mem_mode;
	u32 fw_blc_0;
	u32 fw_blc_1;
	u16 hwstam;
	u16 ier;
	u16 iir;
	u16 imr;
पूर्ण;

काष्ठा पूर्णांकelfb_heap_data अणु
	u32 physical;
	u8 __iomem *भव;
	u32 offset;		/* in GATT pages */
	u32 size;		/* in bytes */
पूर्ण;

#अगर_घोषित CONFIG_FB_INTEL_I2C
काष्ठा पूर्णांकelfb_i2c_chan अणु
    काष्ठा पूर्णांकelfb_info *dinfo;
    u32 reg;
    काष्ठा i2c_adapter adapter;
    काष्ठा i2c_algo_bit_data algo;
पूर्ण;
#पूर्ण_अगर

काष्ठा पूर्णांकelfb_output_rec अणु
    पूर्णांक type;
    पूर्णांक pipe;
    पूर्णांक flags;

#अगर_घोषित CONFIG_FB_INTEL_I2C
    काष्ठा पूर्णांकelfb_i2c_chan i2c_bus;
    काष्ठा पूर्णांकelfb_i2c_chan ddc_bus;
#पूर्ण_अगर
पूर्ण;

काष्ठा पूर्णांकelfb_vsync अणु
	रुको_queue_head_t रुको;
	अचिन्हित पूर्णांक count;
	पूर्णांक pan_display;
	u32 pan_offset;
पूर्ण;

काष्ठा पूर्णांकelfb_info अणु
	काष्ठा fb_info *info;
	स्थिर काष्ठा fb_ops *fbops;
	काष्ठा pci_dev *pdev;

	काष्ठा पूर्णांकelfb_hwstate save_state;

	/* agpgart काष्ठाs */
	काष्ठा agp_memory *gtt_fb_mem;     /* use all stolen memory or vram */
	काष्ठा agp_memory *gtt_ring_mem;   /* ring buffer */
	काष्ठा agp_memory *gtt_cursor_mem; /* hw cursor */

	/* use a gart reserved fb mem */
	u8 fbmem_gart;

	पूर्णांक wc_cookie;

	/* heap data */
	काष्ठा पूर्णांकelfb_heap_data aperture;
	काष्ठा पूर्णांकelfb_heap_data fb;
	काष्ठा पूर्णांकelfb_heap_data ring;
	काष्ठा पूर्णांकelfb_heap_data cursor;

	/* mmio regs */
	u32 mmio_base_phys;
	u8 __iomem *mmio_base;

	/* fb start offset (in bytes) */
	u32 fb_start;

	/* ring buffer */
	u32 ring_head;
	u32 ring_tail;
	u32 ring_tail_mask;
	u32 ring_space;
	u32 ring_lockup;

	/* palette */
	u32 pseuकरो_palette[16];

	/* chip info */
	पूर्णांक pci_chipset;
	पूर्णांक chipset;
	स्थिर अक्षर *name;
	पूर्णांक mobile;

	/* current mode */
	पूर्णांक bpp, depth;
	u32 visual;
	पूर्णांक xres, yres, pitch;
	पूर्णांक pixघड़ी;

	/* current pipe */
	पूर्णांक pipe;

	/* some flags */
	पूर्णांक accel;
	पूर्णांक hwcursor;
	पूर्णांक fixed_mode;
	पूर्णांक ring_active;
	पूर्णांक flag;
	अचिन्हित दीर्घ irq_flags;
	पूर्णांक खोलो;

	/* vsync */
	काष्ठा पूर्णांकelfb_vsync vsync;
	spinlock_t पूर्णांक_lock;

	/* hw cursor */
	पूर्णांक cursor_on;
	पूर्णांक cursor_blanked;
	u8  cursor_src[64];

	/* initial parameters */
	पूर्णांक initial_vga;
	काष्ठा fb_var_screeninfo initial_var;
	u32 initial_fb_base;
	u32 initial_video_ram;
	u32 initial_pitch;

	/* driver रेजिस्टरed */
	पूर्णांक रेजिस्टरed;

	/* index पूर्णांकo plls */
	पूर्णांक pll_index;

	/* outमाला_दो */
	पूर्णांक num_outमाला_दो;
	काष्ठा पूर्णांकelfb_output_rec output[MAX_OUTPUTS];
पूर्ण;

#घोषणा IS_I9XX(dinfo) (((dinfo)->chipset == INTEL_915G) ||	\
			((dinfo)->chipset == INTEL_915GM) ||	\
			((dinfo)->chipset == INTEL_945G) ||	\
			((dinfo)->chipset == INTEL_945GM) ||	\
			((dinfo)->chipset == INTEL_945GME) ||	\
			((dinfo)->chipset == INTEL_965G) ||	\
			((dinfo)->chipset == INTEL_965GM))

/*** function prototypes ***/

बाह्य पूर्णांक पूर्णांकelfb_var_to_depth(स्थिर काष्ठा fb_var_screeninfo *var);

#अगर_घोषित CONFIG_FB_INTEL_I2C
बाह्य व्योम पूर्णांकelfb_create_i2c_busses(काष्ठा पूर्णांकelfb_info *dinfo);
बाह्य व्योम पूर्णांकelfb_delete_i2c_busses(काष्ठा पूर्णांकelfb_info *dinfo);
#पूर्ण_अगर

#पूर्ण_अगर /* _INTELFB_H */
