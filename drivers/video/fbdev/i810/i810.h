<शैली गुरु>
/*-*- linux-c -*-
 *  linux/drivers/video/i810.h -- Intel 810 General Definitions/Declarations
 *
 *      Copyright (C) 2001 Antonino Daplas<adaplas@pol.net>
 *      All Rights Reserved      
 *
 *
 *  This file is subject to the terms and conditions of the GNU General Public
 *  License. See the file COPYING in the मुख्य directory of this archive क्रम
 *  more details.
 */

#अगर_अघोषित __I810_H__
#घोषणा __I810_H__

#समावेश <linux/list.h>
#समावेश <linux/agp_backend.h>
#समावेश <linux/fb.h>
#समावेश <linux/i2c.h>
#समावेश <linux/i2c-algo-bit.h>
#समावेश <video/vga.h>

/* Fence */
#घोषणा TILEWALK_X            (0 << 12)
#घोषणा TILEWALK_Y            (1 << 12)

/* Raster ops */
#घोषणा COLOR_COPY_ROP        0xF0
#घोषणा PAT_COPY_ROP          0xCC
#घोषणा CLEAR_ROP             0x00
#घोषणा WHITE_ROP             0xFF
#घोषणा INVERT_ROP            0x55
#घोषणा XOR_ROP               0x5A

/* 2D Engine definitions */
#घोषणा SOLIDPATTERN          0x80000000
#घोषणा NONSOLID              0x00000000
#घोषणा BPP8                  (0 << 24)
#घोषणा BPP16                 (1 << 24)
#घोषणा BPP24                 (2 << 24)

#घोषणा PIXCONF8              (2 << 16)
#घोषणा PIXCONF15             (4 << 16)
#घोषणा PIXCONF16             (5 << 16)
#घोषणा PIXCONF24             (6 << 16)
#घोषणा PIXCONF32             (7 << 16)

#घोषणा DYN_COLOR_EN          (1 << 26)
#घोषणा DYN_COLOR_DIS         (0 << 26)
#घोषणा INCREMENT             0x00000000
#घोषणा DECREMENT             (0x01 << 30)
#घोषणा ARB_ON                0x00000001
#घोषणा ARB_OFF               0x00000000
#घोषणा SYNC_FLIP             0x00000000
#घोषणा ASYNC_FLIP            0x00000040
#घोषणा OPTYPE_MASK           0xE0000000
#घोषणा PARSER_MASK           0x001F8000 
#घोषणा D2_MASK               0x001FC000         /* 2D mask */

/* Inकाष्ठाion type */
/* There are more but pertains to 3D */
#घोषणा PARSER                0x00000000
#घोषणा BLIT                  (0x02 << 29)
#घोषणा RENDER                (0x03 << 29)
            
/* Parser */
#घोषणा NOP                   0x00               /* No operation, padding */
#घोषणा BP_INT                (0x01 << 23)         /* Breakpoपूर्णांक पूर्णांकerrupt */
#घोषणा USR_INT               (0x02 << 23)         /* User पूर्णांकerrupt */
#घोषणा WAIT_FOR_EVNT         (0x03 << 23)         /* Wait क्रम event */
#घोषणा FLUSH                 (0x04 << 23)              
#घोषणा CONTEXT_SEL           (0x05 << 23)
#घोषणा REPORT_HEAD           (0x07 << 23)
#घोषणा ARB_ON_OFF            (0x08 << 23)
#घोषणा OVERLAY_FLIP          (0x11 << 23)
#घोषणा LOAD_SCAN_INC         (0x12 << 23)
#घोषणा LOAD_SCAN_EX          (0x13 << 23)
#घोषणा FRONT_BUFFER          (0x14 << 23)
#घोषणा DEST_BUFFER           (0x15 << 23)
#घोषणा Z_BUFFER              (0x16 << 23)       

#घोषणा STORE_DWORD_IMM       (0x20 << 23)
#घोषणा STORE_DWORD_IDX       (0x21 << 23)
#घोषणा BATCH_BUFFER          (0x30 << 23)

/* Blit */
#घोषणा SETUP_BLIT                      0x00
#घोषणा SETUP_MONO_PATTERN_SL_BLT       (0x10 << 22)
#घोषणा PIXEL_BLT                       (0x20 << 22)
#घोषणा SCANLINE_BLT                    (0x21 << 22)
#घोषणा TEXT_BLT                        (0x22 << 22)
#घोषणा TEXT_IMM_BLT                    (0x30 << 22)
#घोषणा COLOR_BLT                       (0x40 << 22)
#घोषणा MONO_PAT_BLIT                   (0x42 << 22)
#घोषणा SOURCE_COPY_BLIT                (0x43 << 22)
#घोषणा MONO_SOURCE_COPY_BLIT           (0x44 << 22)
#घोषणा SOURCE_COPY_IMMEDIATE           (0x60 << 22)
#घोषणा MONO_SOURCE_COPY_IMMEDIATE      (0x61 << 22)

#घोषणा VERSION_MAJOR            0
#घोषणा VERSION_MINOR            9
#घोषणा VERSION_TEENIE           0
#घोषणा BRANCH_VERSION           ""


/* mvo: पूर्णांकel i815 */
#अगर_अघोषित PCI_DEVICE_ID_INTEL_82815_100
  #घोषणा PCI_DEVICE_ID_INTEL_82815_100           0x1102
#पूर्ण_अगर
#अगर_अघोषित PCI_DEVICE_ID_INTEL_82815_NOAGP
  #घोषणा PCI_DEVICE_ID_INTEL_82815_NOAGP         0x1112
#पूर्ण_अगर
#अगर_अघोषित PCI_DEVICE_ID_INTEL_82815_FULL_CTRL
  #घोषणा PCI_DEVICE_ID_INTEL_82815_FULL_CTRL     0x1130
#पूर्ण_अगर 

/* General Defines */
#घोषणा I810_PAGESIZE               4096
#घोषणा MAX_DMA_SIZE                (1024 * 4096)
#घोषणा SAREA_SIZE                  4096
#घोषणा PCI_I810_MISCC              0x72
#घोषणा MMIO_SIZE                   (512*1024)
#घोषणा GTT_SIZE                    (16*1024) 
#घोषणा RINGBUFFER_SIZE             (64*1024)
#घोषणा CURSOR_SIZE                 4096 
#घोषणा OFF                         0
#घोषणा ON                          1
#घोषणा MAX_KEY                     256
#घोषणा WAIT_COUNT                  10000000
#घोषणा IRING_PAD                   8
#घोषणा FONTDATAMAX                 8192
/* Masks (AND ops) and OR's */
#घोषणा FB_START_MASK               (0x3f << (32 - 6))
#घोषणा MMIO_ADDR_MASK              (0x1FFF << (32 - 13))
#घोषणा FREQ_MASK                   (1 << 4)
#घोषणा SCR_OFF                     0x20
#घोषणा DRAM_ON                     0x08            
#घोषणा DRAM_OFF                    0xE7
#घोषणा PG_ENABLE_MASK              0x01
#घोषणा RING_SIZE_MASK              (RINGBUFFER_SIZE - 1)

/* defines क्रम restoring रेजिस्टरs partially */
#घोषणा ADDR_MAP_MASK               (0x07 << 5)
#घोषणा DISP_CTRL                   ~0
#घोषणा PIXCONF_0                   (0x64 << 8)
#घोषणा PIXCONF_2                   (0xF3 << 24)
#घोषणा PIXCONF_1                   (0xF0 << 16)
#घोषणा MN_MASK                     0x3FF03FF
#घोषणा P_OR                        (0x7 << 4)                    
#घोषणा DAC_BIT                     (1 << 16)
#घोषणा INTERLACE_BIT               (1 << 7)
#घोषणा IER_MASK                    (3 << 13)
#घोषणा IMR_MASK                    (3 << 13)

/* Power Management */
#घोषणा DPMS_MASK                   0xF0000
#घोषणा POWERON                     0x00000
#घोषणा STANDBY                     0x20000
#घोषणा SUSPEND                     0x80000
#घोषणा POWERDOWN                   0xA0000
#घोषणा EMR_MASK                    ~0x3F
#घोषणा FW_BLC_MASK                 ~(0x3F|(7 << 8)|(0x3F << 12)|(7 << 20))

/* Ringbuffer */
#घोषणा RBUFFER_START_MASK          0xFFFFF000
#घोषणा RBUFFER_SIZE_MASK           0x001FF000
#घोषणा RBUFFER_HEAD_MASK           0x001FFFFC
#घोषणा RBUFFER_TAIL_MASK           0x001FFFF8

/* Video Timings */
#घोषणा REF_FREQ                    24000000
#घोषणा TARGET_N_MAX                30

#घोषणा MAX_PIXELCLOCK              230000000
#घोषणा MIN_PIXELCLOCK               15000000
#घोषणा VFMAX                       60
#घोषणा VFMIN                       60
#घोषणा HFMAX                       30000
#घोषणा HFMIN                       29000

/* Cursor */
#घोषणा CURSOR_ENABLE_MASK          0x1000             
#घोषणा CURSOR_MODE_64_TRANS        4
#घोषणा CURSOR_MODE_64_XOR	    5
#घोषणा CURSOR_MODE_64_3C	    6	
#घोषणा COORD_INACTIVE              0
#घोषणा COORD_ACTIVE                (1 << 4)
#घोषणा EXTENDED_PALETTE	    1
  
/* AGP Memory Types*/
#घोषणा AGP_NORMAL_MEMORY           0
#घोषणा AGP_DCACHE_MEMORY	    1
#घोषणा AGP_PHYSICAL_MEMORY         2

/* Allocated resource Flags */
#घोषणा FRAMEBUFFER_REQ             1
#घोषणा MMIO_REQ                    2
#घोषणा PCI_DEVICE_ENABLED          4
#घोषणा HAS_FONTCACHE               8 

/* driver flags */
#घोषणा HAS_ACCELERATION            2
#घोषणा ALWAYS_SYNC                 4
#घोषणा LOCKUP                      8

काष्ठा gtt_data अणु
	काष्ठा agp_memory *i810_fb_memory;
	काष्ठा agp_memory *i810_cursor_memory;
पूर्ण;

काष्ठा mode_रेजिस्टरs अणु
	u32 pixघड़ी, M, N, P;
	u8 cr00, cr01, cr02, cr03;
	u8 cr04, cr05, cr06, cr07;
	u8 cr09, cr10, cr11, cr12;
	u8 cr13, cr15, cr16, cr30;
	u8 cr31, cr32, cr33, cr35, cr39;
	u32 bpp8_100, bpp16_100;
	u32 bpp24_100, bpp8_133;
	u32 bpp16_133, bpp24_133;
	u8 msr;
पूर्ण;

काष्ठा heap_data अणु
        अचिन्हित दीर्घ physical;
	__u8 __iomem *भव;
	u32 offset;
	u32 size;
पूर्ण;	

काष्ठा state_रेजिस्टरs अणु
	u32 dclk_1d, dclk_2d, dclk_0ds;
	u32 pixconf, fw_blc, pgtbl_ctl;
	u32 fence0, hws_pga, dplystas;
	u16 bltcntl, hwstam, ier, iir, imr;
	u8 cr00, cr01, cr02, cr03, cr04;
	u8 cr05, cr06, cr07, cr08, cr09;
	u8 cr10, cr11, cr12, cr13, cr14;
	u8 cr15, cr16, cr17, cr80, gr10;
	u8 cr30, cr31, cr32, cr33, cr35;
	u8 cr39, cr41, cr70, sr01, msr;
पूर्ण;

काष्ठा i810fb_par;

काष्ठा i810fb_i2c_chan अणु
	काष्ठा i810fb_par *par;
	काष्ठा i2c_adapter adapter;
	काष्ठा i2c_algo_bit_data algo;
	अचिन्हित दीर्घ ddc_base;
पूर्ण;

काष्ठा i810fb_par अणु
	काष्ठा mode_रेजिस्टरs    regs;
	काष्ठा state_रेजिस्टरs   hw_state;
	काष्ठा gtt_data          i810_gtt;
	काष्ठा fb_ops            i810fb_ops;
	काष्ठा pci_dev           *dev;
	काष्ठा heap_data         aperture;
	काष्ठा heap_data         fb;
	काष्ठा heap_data         iring;
	काष्ठा heap_data         cursor_heap;
	काष्ठा vgastate          state;
	काष्ठा i810fb_i2c_chan   chan[3];
	काष्ठा mutex		 खोलो_lock;
	अचिन्हित पूर्णांक		 use_count;
	u32 pseuकरो_palette[16];
	अचिन्हित दीर्घ mmio_start_phys;
	u8 __iomem *mmio_start_भव;
	u8 *edid;
	u32 pitch;
	u32 pixconf;
	u32 watermark;
	u32 mem_freq;
	u32 res_flags;
	u32 dev_flags;
	u32 cur_tail;
	u32 depth;
	u32 blit_bpp;
	u32 ovract;
	u32 cur_state;
	u32 ddc_num;
	पूर्णांक wc_cookie;
	u16 bltcntl;
	u8 पूर्णांकerlace;
पूर्ण;

/* 
 * Register I/O
 */
#घोषणा i810_पढ़ोb(where, mmio) पढ़ोb(mmio + where)
#घोषणा i810_पढ़ोw(where, mmio) पढ़ोw(mmio + where)
#घोषणा i810_पढ़ोl(where, mmio) पढ़ोl(mmio + where)
#घोषणा i810_ग_लिखोb(where, mmio, val) ग_लिखोb(val, mmio + where) 
#घोषणा i810_ग_लिखोw(where, mmio, val) ग_लिखोw(val, mmio + where)
#घोषणा i810_ग_लिखोl(where, mmio, val) ग_लिखोl(val, mmio + where)

#पूर्ण_अगर /* __I810_H__ */
