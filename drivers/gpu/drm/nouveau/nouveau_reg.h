<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */

#घोषणा NV04_PFB_BOOT_0						0x00100000
#	define NV04_PFB_BOOT_0_RAM_AMOUNT			0x00000003
#	define NV04_PFB_BOOT_0_RAM_AMOUNT_32MB			0x00000000
#	define NV04_PFB_BOOT_0_RAM_AMOUNT_4MB			0x00000001
#	define NV04_PFB_BOOT_0_RAM_AMOUNT_8MB			0x00000002
#	define NV04_PFB_BOOT_0_RAM_AMOUNT_16MB			0x00000003
#	define NV04_PFB_BOOT_0_RAM_WIDTH_128			0x00000004
#	define NV04_PFB_BOOT_0_RAM_TYPE				0x00000028
#	define NV04_PFB_BOOT_0_RAM_TYPE_SGRAM_8MBIT		0x00000000
#	define NV04_PFB_BOOT_0_RAM_TYPE_SGRAM_16MBIT		0x00000008
#	define NV04_PFB_BOOT_0_RAM_TYPE_SGRAM_16MBIT_4BANK	0x00000010
#	define NV04_PFB_BOOT_0_RAM_TYPE_SDRAM_16MBIT		0x00000018
#	define NV04_PFB_BOOT_0_RAM_TYPE_SDRAM_64MBIT		0x00000020
#	define NV04_PFB_BOOT_0_RAM_TYPE_SDRAM_64MBITX16		0x00000028
#	define NV04_PFB_BOOT_0_UMA_ENABLE			0x00000100
#	define NV04_PFB_BOOT_0_UMA_SIZE				0x0000f000
#घोषणा NV04_PFB_DEBUG_0					0x00100080
#	define NV04_PFB_DEBUG_0_PAGE_MODE			0x00000001
#	define NV04_PFB_DEBUG_0_REFRESH_OFF			0x00000010
#	define NV04_PFB_DEBUG_0_REFRESH_COUNTX64		0x00003f00
#	define NV04_PFB_DEBUG_0_REFRESH_SLOW_CLK		0x00004000
#	define NV04_PFB_DEBUG_0_SAFE_MODE			0x00008000
#	define NV04_PFB_DEBUG_0_ALOM_ENABLE			0x00010000
#	define NV04_PFB_DEBUG_0_CASOE				0x00100000
#	define NV04_PFB_DEBUG_0_CKE_INVERT			0x10000000
#	define NV04_PFB_DEBUG_0_REFINC				0x20000000
#	define NV04_PFB_DEBUG_0_SAVE_POWER_OFF			0x40000000
#घोषणा NV04_PFB_CFG0						0x00100200
#	define NV04_PFB_CFG0_SCRAMBLE				0x20000000
#घोषणा NV04_PFB_CFG1						0x00100204
#घोषणा NV04_PFB_FIFO_DATA					0x0010020c
#	define NV10_PFB_FIFO_DATA_RAM_AMOUNT_MB_MASK		0xfff00000
#	define NV10_PFB_FIFO_DATA_RAM_AMOUNT_MB_SHIFT		20
#घोषणा NV10_PFB_REFCTRL					0x00100210
#	define NV10_PFB_REFCTRL_VALID_1				(1 << 31)
#घोषणा NV04_PFB_PAD						0x0010021c
#	define NV04_PFB_PAD_CKE_NORMAL				(1 << 0)
#घोषणा NV10_PFB_TILE(i)                              (0x00100240 + (i*16))
#घोषणा NV10_PFB_TILE__SIZE					8
#घोषणा NV10_PFB_TLIMIT(i)                            (0x00100244 + (i*16))
#घोषणा NV10_PFB_TSIZE(i)                             (0x00100248 + (i*16))
#घोषणा NV10_PFB_TSTATUS(i)                           (0x0010024c + (i*16))
#घोषणा NV04_PFB_REF						0x001002d0
#	define NV04_PFB_REF_CMD_REFRESH				(1 << 0)
#घोषणा NV04_PFB_PRE						0x001002d4
#	define NV04_PFB_PRE_CMD_PRECHARGE			(1 << 0)
#घोषणा NV20_PFB_ZCOMP(i)                              (0x00100300 + 4*(i))
#	define NV20_PFB_ZCOMP_MODE_32				(4 << 24)
#	define NV20_PFB_ZCOMP_EN				(1 << 31)
#	define NV25_PFB_ZCOMP_MODE_16				(1 << 20)
#	define NV25_PFB_ZCOMP_MODE_32				(2 << 20)
#घोषणा NV10_PFB_CLOSE_PAGE2					0x0010033c
#घोषणा NV04_PFB_SCRAMBLE(i)                         (0x00100400 + 4 * (i))
#घोषणा NV40_PFB_TILE(i)                              (0x00100600 + (i*16))
#घोषणा NV40_PFB_TILE__SIZE_0					12
#घोषणा NV40_PFB_TILE__SIZE_1					15
#घोषणा NV40_PFB_TLIMIT(i)                            (0x00100604 + (i*16))
#घोषणा NV40_PFB_TSIZE(i)                             (0x00100608 + (i*16))
#घोषणा NV40_PFB_TSTATUS(i)                           (0x0010060c + (i*16))
#घोषणा NV40_PFB_UNK_800					0x00100800

#घोषणा NV_PEXTDEV_BOOT_0					0x00101000
#घोषणा NV_PEXTDEV_BOOT_0_RAMCFG				0x0000003c
#	define NV_PEXTDEV_BOOT_0_STRAP_FP_IFACE_12BIT		(8 << 12)
#घोषणा NV_PEXTDEV_BOOT_3					0x0010100c

#घोषणा NV_RAMIN                                           0x00700000

#घोषणा NV_RAMHT_HANDLE_OFFSET                             0
#घोषणा NV_RAMHT_CONTEXT_OFFSET                            4
#    define NV_RAMHT_CONTEXT_VALID                         (1<<31)
#    define NV_RAMHT_CONTEXT_CHANNEL_SHIFT                 24
#    define NV_RAMHT_CONTEXT_ENGINE_SHIFT                  16
#        define NV_RAMHT_CONTEXT_ENGINE_SW           0
#        define NV_RAMHT_CONTEXT_ENGINE_GRAPHICS           1
#    define NV_RAMHT_CONTEXT_INSTANCE_SHIFT                0
#    define NV40_RAMHT_CONTEXT_CHANNEL_SHIFT               23
#    define NV40_RAMHT_CONTEXT_ENGINE_SHIFT                20
#    define NV40_RAMHT_CONTEXT_INSTANCE_SHIFT              0

/* Some object classes we care about in the drm */
#घोषणा NV_CLASS_DMA_FROM_MEMORY                           0x00000002
#घोषणा NV_CLASS_DMA_TO_MEMORY                             0x00000003
#घोषणा NV_CLASS_शून्य                                      0x00000030
#घोषणा NV_CLASS_DMA_IN_MEMORY                             0x0000003D

#घोषणा NV03_USER(i)                             (0x00800000+(i*NV03_USER_SIZE))
#घोषणा NV03_USER__SIZE                                                       16
#घोषणा NV10_USER__SIZE                                                       32
#घोषणा NV03_USER_SIZE                                                0x00010000
#घोषणा NV03_USER_DMA_PUT(i)                     (0x00800040+(i*NV03_USER_SIZE))
#घोषणा NV03_USER_DMA_PUT__SIZE                                               16
#घोषणा NV10_USER_DMA_PUT__SIZE                                               32
#घोषणा NV03_USER_DMA_GET(i)                     (0x00800044+(i*NV03_USER_SIZE))
#घोषणा NV03_USER_DMA_GET__SIZE                                               16
#घोषणा NV10_USER_DMA_GET__SIZE                                               32
#घोषणा NV03_USER_REF_CNT(i)                     (0x00800048+(i*NV03_USER_SIZE))
#घोषणा NV03_USER_REF_CNT__SIZE                                               16
#घोषणा NV10_USER_REF_CNT__SIZE                                               32

#घोषणा NV40_USER(i)                             (0x00c00000+(i*NV40_USER_SIZE))
#घोषणा NV40_USER_SIZE                                                0x00001000
#घोषणा NV40_USER_DMA_PUT(i)                     (0x00c00040+(i*NV40_USER_SIZE))
#घोषणा NV40_USER_DMA_PUT__SIZE                                               32
#घोषणा NV40_USER_DMA_GET(i)                     (0x00c00044+(i*NV40_USER_SIZE))
#घोषणा NV40_USER_DMA_GET__SIZE                                               32
#घोषणा NV40_USER_REF_CNT(i)                     (0x00c00048+(i*NV40_USER_SIZE))
#घोषणा NV40_USER_REF_CNT__SIZE                                               32

#घोषणा NV50_USER(i)                             (0x00c00000+(i*NV50_USER_SIZE))
#घोषणा NV50_USER_SIZE                                                0x00002000
#घोषणा NV50_USER_DMA_PUT(i)                     (0x00c00040+(i*NV50_USER_SIZE))
#घोषणा NV50_USER_DMA_PUT__SIZE                                              128
#घोषणा NV50_USER_DMA_GET(i)                     (0x00c00044+(i*NV50_USER_SIZE))
#घोषणा NV50_USER_DMA_GET__SIZE                                              128
#घोषणा NV50_USER_REF_CNT(i)                     (0x00c00048+(i*NV50_USER_SIZE))
#घोषणा NV50_USER_REF_CNT__SIZE                                              128

#घोषणा NV03_FIFO_SIZE                                     0x8000UL

#घोषणा NV03_PMC_BOOT_0                                    0x00000000
#घोषणा NV03_PMC_BOOT_1                                    0x00000004
#घोषणा NV03_PMC_INTR_0                                    0x00000100
#    define NV_PMC_INTR_0_PFIFO_PENDING                        (1<<8)
#    define NV_PMC_INTR_0_PGRAPH_PENDING                      (1<<12)
#    define NV_PMC_INTR_0_NV50_I2C_PENDING                    (1<<21)
#    define NV_PMC_INTR_0_CRTC0_PENDING                       (1<<24)
#    define NV_PMC_INTR_0_CRTC1_PENDING                       (1<<25)
#    define NV_PMC_INTR_0_NV50_DISPLAY_PENDING                (1<<26)
#    define NV_PMC_INTR_0_CRTCn_PENDING                       (3<<24)
#घोषणा NV03_PMC_INTR_EN_0                                 0x00000140
#    define NV_PMC_INTR_EN_0_MASTER_ENABLE                     (1<<0)
#घोषणा NV03_PMC_ENABLE                                    0x00000200
#    define NV_PMC_ENABLE_PFIFO                                (1<<8)
#    define NV_PMC_ENABLE_PGRAPH                              (1<<12)
/* Disabling the below bit अवरोधs newer (G7X only?) mobile chipsets,
 * the card will hang early on in the X init process.
 */
#    define NV_PMC_ENABLE_UNK13                               (1<<13)
#घोषणा NV40_PMC_GRAPH_UNITS				   0x00001540
#घोषणा NV40_PMC_BACKLIGHT				   0x000015f0
#	define NV40_PMC_BACKLIGHT_MASK			   0x001f0000
#घोषणा NV40_PMC_1700                                      0x00001700
#घोषणा NV40_PMC_1704                                      0x00001704
#घोषणा NV40_PMC_1708                                      0x00001708
#घोषणा NV40_PMC_170C                                      0x0000170C

/* probably PMC ? */
#घोषणा NV50_PUNK_BAR0_PRAMIN                              0x00001700
#घोषणा NV50_PUNK_BAR_CFG_BASE                             0x00001704
#घोषणा NV50_PUNK_BAR_CFG_BASE_VALID                          (1<<30)
#घोषणा NV50_PUNK_BAR1_CTXDMA                              0x00001708
#घोषणा NV50_PUNK_BAR1_CTXDMA_VALID                           (1<<31)
#घोषणा NV50_PUNK_BAR3_CTXDMA                              0x0000170C
#घोषणा NV50_PUNK_BAR3_CTXDMA_VALID                           (1<<31)
#घोषणा NV50_PUNK_UNK1710                                  0x00001710

#घोषणा NV04_PBUS_PCI_NV_1                                 0x00001804
#घोषणा NV04_PBUS_PCI_NV_19                                0x0000184C
#घोषणा NV04_PBUS_PCI_NV_20				0x00001850
#	define NV04_PBUS_PCI_NV_20_ROM_SHADOW_DISABLED		(0 << 0)
#	define NV04_PBUS_PCI_NV_20_ROM_SHADOW_ENABLED		(1 << 0)

#घोषणा NV04_PTIMER_INTR_0                                 0x00009100
#घोषणा NV04_PTIMER_INTR_EN_0                              0x00009140
#घोषणा NV04_PTIMER_NUMERATOR                              0x00009200
#घोषणा NV04_PTIMER_DENOMINATOR                            0x00009210
#घोषणा NV04_PTIMER_TIME_0                                 0x00009400
#घोषणा NV04_PTIMER_TIME_1                                 0x00009410
#घोषणा NV04_PTIMER_ALARM_0                                0x00009420

#घोषणा NV04_PGRAPH_DEBUG_0                                0x00400080
#घोषणा NV04_PGRAPH_DEBUG_1                                0x00400084
#घोषणा NV04_PGRAPH_DEBUG_2                                0x00400088
#घोषणा NV04_PGRAPH_DEBUG_3                                0x0040008c
#घोषणा NV10_PGRAPH_DEBUG_4                                0x00400090
#घोषणा NV03_PGRAPH_INTR                                   0x00400100
#घोषणा NV03_PGRAPH_NSTATUS                                0x00400104
#    define NV04_PGRAPH_NSTATUS_STATE_IN_USE                  (1<<11)
#    define NV04_PGRAPH_NSTATUS_INVALID_STATE                 (1<<12)
#    define NV04_PGRAPH_NSTATUS_BAD_ARGUMENT                  (1<<13)
#    define NV04_PGRAPH_NSTATUS_PROTECTION_FAULT              (1<<14)
#    define NV10_PGRAPH_NSTATUS_STATE_IN_USE                  (1<<23)
#    define NV10_PGRAPH_NSTATUS_INVALID_STATE                 (1<<24)
#    define NV10_PGRAPH_NSTATUS_BAD_ARGUMENT                  (1<<25)
#    define NV10_PGRAPH_NSTATUS_PROTECTION_FAULT              (1<<26)
#घोषणा NV03_PGRAPH_NSOURCE                                0x00400108
#    define NV03_PGRAPH_NSOURCE_NOTIFICATION                   (1<<0)
#    define NV03_PGRAPH_NSOURCE_DATA_ERROR                     (1<<1)
#    define NV03_PGRAPH_NSOURCE_PROTECTION_ERROR               (1<<2)
#    define NV03_PGRAPH_NSOURCE_RANGE_EXCEPTION                (1<<3)
#    define NV03_PGRAPH_NSOURCE_LIMIT_COLOR                    (1<<4)
#    define NV03_PGRAPH_NSOURCE_LIMIT_ZETA                     (1<<5)
#    define NV03_PGRAPH_NSOURCE_ILLEGAL_MTHD                   (1<<6)
#    define NV03_PGRAPH_NSOURCE_DMA_R_PROTECTION               (1<<7)
#    define NV03_PGRAPH_NSOURCE_DMA_W_PROTECTION               (1<<8)
#    define NV03_PGRAPH_NSOURCE_FORMAT_EXCEPTION               (1<<9)
#    define NV03_PGRAPH_NSOURCE_PATCH_EXCEPTION               (1<<10)
#    define NV03_PGRAPH_NSOURCE_STATE_INVALID                 (1<<11)
#    define NV03_PGRAPH_NSOURCE_DOUBLE_NOTIFY                 (1<<12)
#    define NV03_PGRAPH_NSOURCE_NOTIFY_IN_USE                 (1<<13)
#    define NV03_PGRAPH_NSOURCE_METHOD_CNT                    (1<<14)
#    define NV03_PGRAPH_NSOURCE_BFR_NOTIFICATION              (1<<15)
#    define NV03_PGRAPH_NSOURCE_DMA_VTX_PROTECTION            (1<<16)
#    define NV03_PGRAPH_NSOURCE_DMA_WIDTH_A                   (1<<17)
#    define NV03_PGRAPH_NSOURCE_DMA_WIDTH_B                   (1<<18)
#घोषणा NV03_PGRAPH_INTR_EN                                0x00400140
#घोषणा NV40_PGRAPH_INTR_EN                                0x0040013C
#    define NV_PGRAPH_INTR_NOTIFY                              (1<<0)
#    define NV_PGRAPH_INTR_MISSING_HW                          (1<<4)
#    define NV_PGRAPH_INTR_CONTEXT_SWITCH                     (1<<12)
#    define NV_PGRAPH_INTR_BUFFER_NOTIFY                      (1<<16)
#    define NV_PGRAPH_INTR_ERROR                              (1<<20)
#घोषणा NV10_PGRAPH_CTX_CONTROL                            0x00400144
#घोषणा NV10_PGRAPH_CTX_USER                               0x00400148
#घोषणा NV10_PGRAPH_CTX_SWITCH(i)                         (0x0040014C + 0x4*(i))
#घोषणा NV04_PGRAPH_CTX_SWITCH1                            0x00400160
#घोषणा NV10_PGRAPH_CTX_CACHE(i, j)                       (0x00400160	\
							   + 0x4*(i) + 0x20*(j))
#घोषणा NV04_PGRAPH_CTX_SWITCH2                            0x00400164
#घोषणा NV04_PGRAPH_CTX_SWITCH3                            0x00400168
#घोषणा NV04_PGRAPH_CTX_SWITCH4                            0x0040016C
#घोषणा NV04_PGRAPH_CTX_CONTROL                            0x00400170
#घोषणा NV04_PGRAPH_CTX_USER                               0x00400174
#घोषणा NV04_PGRAPH_CTX_CACHE1                             0x00400180
#घोषणा NV03_PGRAPH_CTX_CONTROL                            0x00400190
#घोषणा NV03_PGRAPH_CTX_USER                               0x00400194
#घोषणा NV04_PGRAPH_CTX_CACHE2                             0x004001A0
#घोषणा NV04_PGRAPH_CTX_CACHE3                             0x004001C0
#घोषणा NV04_PGRAPH_CTX_CACHE4                             0x004001E0
#घोषणा NV40_PGRAPH_CTXCTL_0304                            0x00400304
#घोषणा NV40_PGRAPH_CTXCTL_0304_XFER_CTX                   0x00000001
#घोषणा NV40_PGRAPH_CTXCTL_UCODE_STAT                      0x00400308
#घोषणा NV40_PGRAPH_CTXCTL_UCODE_STAT_IP_MASK              0xff000000
#घोषणा NV40_PGRAPH_CTXCTL_UCODE_STAT_IP_SHIFT                     24
#घोषणा NV40_PGRAPH_CTXCTL_UCODE_STAT_OP_MASK              0x00ffffff
#घोषणा NV40_PGRAPH_CTXCTL_0310                            0x00400310
#घोषणा NV40_PGRAPH_CTXCTL_0310_XFER_SAVE                  0x00000020
#घोषणा NV40_PGRAPH_CTXCTL_0310_XFER_LOAD                  0x00000040
#घोषणा NV40_PGRAPH_CTXCTL_030C                            0x0040030c
#घोषणा NV40_PGRAPH_CTXCTL_UCODE_INDEX                     0x00400324
#घोषणा NV40_PGRAPH_CTXCTL_UCODE_DATA                      0x00400328
#घोषणा NV40_PGRAPH_CTXCTL_CUR                             0x0040032c
#घोषणा NV40_PGRAPH_CTXCTL_CUR_LOADED                      0x01000000
#घोषणा NV40_PGRAPH_CTXCTL_CUR_INSTANCE                    0x000FFFFF
#घोषणा NV40_PGRAPH_CTXCTL_NEXT                            0x00400330
#घोषणा NV40_PGRAPH_CTXCTL_NEXT_INSTANCE                   0x000fffff
#घोषणा NV50_PGRAPH_CTXCTL_CUR                             0x0040032c
#घोषणा NV50_PGRAPH_CTXCTL_CUR_LOADED                      0x80000000
#घोषणा NV50_PGRAPH_CTXCTL_CUR_INSTANCE                    0x00ffffff
#घोषणा NV50_PGRAPH_CTXCTL_NEXT                            0x00400330
#घोषणा NV50_PGRAPH_CTXCTL_NEXT_INSTANCE                   0x00ffffff
#घोषणा NV03_PGRAPH_ABS_X_RAM                              0x00400400
#घोषणा NV03_PGRAPH_ABS_Y_RAM                              0x00400480
#घोषणा NV03_PGRAPH_X_MISC                                 0x00400500
#घोषणा NV03_PGRAPH_Y_MISC                                 0x00400504
#घोषणा NV04_PGRAPH_VALID1                                 0x00400508
#घोषणा NV04_PGRAPH_SOURCE_COLOR                           0x0040050C
#घोषणा NV04_PGRAPH_MISC24_0                               0x00400510
#घोषणा NV03_PGRAPH_XY_LOGIC_MISC0                         0x00400514
#घोषणा NV03_PGRAPH_XY_LOGIC_MISC1                         0x00400518
#घोषणा NV03_PGRAPH_XY_LOGIC_MISC2                         0x0040051C
#घोषणा NV03_PGRAPH_XY_LOGIC_MISC3                         0x00400520
#घोषणा NV03_PGRAPH_CLIPX_0                                0x00400524
#घोषणा NV03_PGRAPH_CLIPX_1                                0x00400528
#घोषणा NV03_PGRAPH_CLIPY_0                                0x0040052C
#घोषणा NV03_PGRAPH_CLIPY_1                                0x00400530
#घोषणा NV03_PGRAPH_ABS_ICLIP_XMAX                         0x00400534
#घोषणा NV03_PGRAPH_ABS_ICLIP_YMAX                         0x00400538
#घोषणा NV03_PGRAPH_ABS_UCLIP_XMIN                         0x0040053C
#घोषणा NV03_PGRAPH_ABS_UCLIP_YMIN                         0x00400540
#घोषणा NV03_PGRAPH_ABS_UCLIP_XMAX                         0x00400544
#घोषणा NV03_PGRAPH_ABS_UCLIP_YMAX                         0x00400548
#घोषणा NV03_PGRAPH_ABS_UCLIPA_XMIN                        0x00400560
#घोषणा NV03_PGRAPH_ABS_UCLIPA_YMIN                        0x00400564
#घोषणा NV03_PGRAPH_ABS_UCLIPA_XMAX                        0x00400568
#घोषणा NV03_PGRAPH_ABS_UCLIPA_YMAX                        0x0040056C
#घोषणा NV04_PGRAPH_MISC24_1                               0x00400570
#घोषणा NV04_PGRAPH_MISC24_2                               0x00400574
#घोषणा NV04_PGRAPH_VALID2                                 0x00400578
#घोषणा NV04_PGRAPH_PASSTHRU_0                             0x0040057C
#घोषणा NV04_PGRAPH_PASSTHRU_1                             0x00400580
#घोषणा NV04_PGRAPH_PASSTHRU_2                             0x00400584
#घोषणा NV10_PGRAPH_DIMX_TEXTURE                           0x00400588
#घोषणा NV10_PGRAPH_WDIMX_TEXTURE                          0x0040058C
#घोषणा NV04_PGRAPH_COMBINE_0_ALPHA                        0x00400590
#घोषणा NV04_PGRAPH_COMBINE_0_COLOR                        0x00400594
#घोषणा NV04_PGRAPH_COMBINE_1_ALPHA                        0x00400598
#घोषणा NV04_PGRAPH_COMBINE_1_COLOR                        0x0040059C
#घोषणा NV04_PGRAPH_FORMAT_0                               0x004005A8
#घोषणा NV04_PGRAPH_FORMAT_1                               0x004005AC
#घोषणा NV04_PGRAPH_FILTER_0                               0x004005B0
#घोषणा NV04_PGRAPH_FILTER_1                               0x004005B4
#घोषणा NV03_PGRAPH_MONO_COLOR0                            0x00400600
#घोषणा NV04_PGRAPH_ROP3                                   0x00400604
#घोषणा NV04_PGRAPH_BETA_AND                               0x00400608
#घोषणा NV04_PGRAPH_BETA_PREMULT                           0x0040060C
#घोषणा NV04_PGRAPH_LIMIT_VIOL_PIX                         0x00400610
#घोषणा NV04_PGRAPH_FORMATS                                0x00400618
#घोषणा NV10_PGRAPH_DEBUG_2                                0x00400620
#घोषणा NV04_PGRAPH_BOFFSET0                               0x00400640
#घोषणा NV04_PGRAPH_BOFFSET1                               0x00400644
#घोषणा NV04_PGRAPH_BOFFSET2                               0x00400648
#घोषणा NV04_PGRAPH_BOFFSET3                               0x0040064C
#घोषणा NV04_PGRAPH_BOFFSET4                               0x00400650
#घोषणा NV04_PGRAPH_BOFFSET5                               0x00400654
#घोषणा NV04_PGRAPH_BBASE0                                 0x00400658
#घोषणा NV04_PGRAPH_BBASE1                                 0x0040065C
#घोषणा NV04_PGRAPH_BBASE2                                 0x00400660
#घोषणा NV04_PGRAPH_BBASE3                                 0x00400664
#घोषणा NV04_PGRAPH_BBASE4                                 0x00400668
#घोषणा NV04_PGRAPH_BBASE5                                 0x0040066C
#घोषणा NV04_PGRAPH_BPITCH0                                0x00400670
#घोषणा NV04_PGRAPH_BPITCH1                                0x00400674
#घोषणा NV04_PGRAPH_BPITCH2                                0x00400678
#घोषणा NV04_PGRAPH_BPITCH3                                0x0040067C
#घोषणा NV04_PGRAPH_BPITCH4                                0x00400680
#घोषणा NV04_PGRAPH_BLIMIT0                                0x00400684
#घोषणा NV04_PGRAPH_BLIMIT1                                0x00400688
#घोषणा NV04_PGRAPH_BLIMIT2                                0x0040068C
#घोषणा NV04_PGRAPH_BLIMIT3                                0x00400690
#घोषणा NV04_PGRAPH_BLIMIT4                                0x00400694
#घोषणा NV04_PGRAPH_BLIMIT5                                0x00400698
#घोषणा NV04_PGRAPH_BSWIZZLE2                              0x0040069C
#घोषणा NV04_PGRAPH_BSWIZZLE5                              0x004006A0
#घोषणा NV03_PGRAPH_STATUS                                 0x004006B0
#घोषणा NV04_PGRAPH_STATUS                                 0x00400700
#    define NV40_PGRAPH_STATUS_SYNC_STALL                  0x00004000
#घोषणा NV04_PGRAPH_TRAPPED_ADDR                           0x00400704
#घोषणा NV04_PGRAPH_TRAPPED_DATA                           0x00400708
#घोषणा NV04_PGRAPH_SURFACE                                0x0040070C
#घोषणा NV10_PGRAPH_TRAPPED_DATA_HIGH                      0x0040070C
#घोषणा NV04_PGRAPH_STATE                                  0x00400710
#घोषणा NV10_PGRAPH_SURFACE                                0x00400710
#घोषणा NV04_PGRAPH_NOTIFY                                 0x00400714
#घोषणा NV10_PGRAPH_STATE                                  0x00400714
#घोषणा NV10_PGRAPH_NOTIFY                                 0x00400718

#घोषणा NV04_PGRAPH_FIFO                                   0x00400720

#घोषणा NV04_PGRAPH_BPIXEL                                 0x00400724
#घोषणा NV10_PGRAPH_RDI_INDEX                              0x00400750
#घोषणा NV04_PGRAPH_FFINTFC_ST2                            0x00400754
#घोषणा NV10_PGRAPH_RDI_DATA                               0x00400754
#घोषणा NV04_PGRAPH_DMA_PITCH                              0x00400760
#घोषणा NV10_PGRAPH_FFINTFC_FIFO_PTR                       0x00400760
#घोषणा NV04_PGRAPH_DVD_COLORFMT                           0x00400764
#घोषणा NV10_PGRAPH_FFINTFC_ST2                            0x00400764
#घोषणा NV04_PGRAPH_SCALED_FORMAT                          0x00400768
#घोषणा NV10_PGRAPH_FFINTFC_ST2_DL                         0x00400768
#घोषणा NV10_PGRAPH_FFINTFC_ST2_DH                         0x0040076c
#घोषणा NV10_PGRAPH_DMA_PITCH                              0x00400770
#घोषणा NV10_PGRAPH_DVD_COLORFMT                           0x00400774
#घोषणा NV10_PGRAPH_SCALED_FORMAT                          0x00400778
#घोषणा NV20_PGRAPH_CHANNEL_CTX_TABLE                      0x00400780
#घोषणा NV20_PGRAPH_CHANNEL_CTX_POINTER                    0x00400784
#घोषणा NV20_PGRAPH_CHANNEL_CTX_XFER                       0x00400788
#घोषणा NV20_PGRAPH_CHANNEL_CTX_XFER_LOAD                  0x00000001
#घोषणा NV20_PGRAPH_CHANNEL_CTX_XFER_SAVE                  0x00000002
#घोषणा NV04_PGRAPH_PATT_COLOR0                            0x00400800
#घोषणा NV04_PGRAPH_PATT_COLOR1                            0x00400804
#घोषणा NV04_PGRAPH_PATTERN                                0x00400808
#घोषणा NV04_PGRAPH_PATTERN_SHAPE                          0x00400810
#घोषणा NV04_PGRAPH_CHROMA                                 0x00400814
#घोषणा NV04_PGRAPH_CONTROL0                               0x00400818
#घोषणा NV04_PGRAPH_CONTROL1                               0x0040081C
#घोषणा NV04_PGRAPH_CONTROL2                               0x00400820
#घोषणा NV04_PGRAPH_BLEND                                  0x00400824
#घोषणा NV04_PGRAPH_STORED_FMT                             0x00400830
#घोषणा NV04_PGRAPH_PATT_COLORRAM                          0x00400900
#घोषणा NV20_PGRAPH_TILE(i)                                (0x00400900 + (i*16))
#घोषणा NV20_PGRAPH_TLIMIT(i)                              (0x00400904 + (i*16))
#घोषणा NV20_PGRAPH_TSIZE(i)                               (0x00400908 + (i*16))
#घोषणा NV20_PGRAPH_TSTATUS(i)                             (0x0040090C + (i*16))
#घोषणा NV20_PGRAPH_ZCOMP(i)                               (0x00400980 + 4*(i))
#घोषणा NV10_PGRAPH_TILE(i)                                (0x00400B00 + (i*16))
#घोषणा NV10_PGRAPH_TLIMIT(i)                              (0x00400B04 + (i*16))
#घोषणा NV10_PGRAPH_TSIZE(i)                               (0x00400B08 + (i*16))
#घोषणा NV10_PGRAPH_TSTATUS(i)                             (0x00400B0C + (i*16))
#घोषणा NV04_PGRAPH_U_RAM                                  0x00400D00
#घोषणा NV47_PGRAPH_TILE(i)                                (0x00400D00 + (i*16))
#घोषणा NV47_PGRAPH_TLIMIT(i)                              (0x00400D04 + (i*16))
#घोषणा NV47_PGRAPH_TSIZE(i)                               (0x00400D08 + (i*16))
#घोषणा NV47_PGRAPH_TSTATUS(i)                             (0x00400D0C + (i*16))
#घोषणा NV04_PGRAPH_V_RAM                                  0x00400D40
#घोषणा NV04_PGRAPH_W_RAM                                  0x00400D80
#घोषणा NV10_PGRAPH_COMBINER0_IN_ALPHA                     0x00400E40
#घोषणा NV10_PGRAPH_COMBINER1_IN_ALPHA                     0x00400E44
#घोषणा NV10_PGRAPH_COMBINER0_IN_RGB                       0x00400E48
#घोषणा NV10_PGRAPH_COMBINER1_IN_RGB                       0x00400E4C
#घोषणा NV10_PGRAPH_COMBINER_COLOR0                        0x00400E50
#घोषणा NV10_PGRAPH_COMBINER_COLOR1                        0x00400E54
#घोषणा NV10_PGRAPH_COMBINER0_OUT_ALPHA                    0x00400E58
#घोषणा NV10_PGRAPH_COMBINER1_OUT_ALPHA                    0x00400E5C
#घोषणा NV10_PGRAPH_COMBINER0_OUT_RGB                      0x00400E60
#घोषणा NV10_PGRAPH_COMBINER1_OUT_RGB                      0x00400E64
#घोषणा NV10_PGRAPH_COMBINER_FINAL0                        0x00400E68
#घोषणा NV10_PGRAPH_COMBINER_FINAL1                        0x00400E6C
#घोषणा NV10_PGRAPH_WINDOWCLIP_HORIZONTAL                  0x00400F00
#घोषणा NV10_PGRAPH_WINDOWCLIP_VERTICAL                    0x00400F20
#घोषणा NV10_PGRAPH_XFMODE0                                0x00400F40
#घोषणा NV10_PGRAPH_XFMODE1                                0x00400F44
#घोषणा NV10_PGRAPH_GLOBALSTATE0                           0x00400F48
#घोषणा NV10_PGRAPH_GLOBALSTATE1                           0x00400F4C
#घोषणा NV10_PGRAPH_PIPE_ADDRESS                           0x00400F50
#घोषणा NV10_PGRAPH_PIPE_DATA                              0x00400F54
#घोषणा NV04_PGRAPH_DMA_START_0                            0x00401000
#घोषणा NV04_PGRAPH_DMA_START_1                            0x00401004
#घोषणा NV04_PGRAPH_DMA_LENGTH                             0x00401008
#घोषणा NV04_PGRAPH_DMA_MISC                               0x0040100C
#घोषणा NV04_PGRAPH_DMA_DATA_0                             0x00401020
#घोषणा NV04_PGRAPH_DMA_DATA_1                             0x00401024
#घोषणा NV04_PGRAPH_DMA_RM                                 0x00401030
#घोषणा NV04_PGRAPH_DMA_A_XLATE_INST                       0x00401040
#घोषणा NV04_PGRAPH_DMA_A_CONTROL                          0x00401044
#घोषणा NV04_PGRAPH_DMA_A_LIMIT                            0x00401048
#घोषणा NV04_PGRAPH_DMA_A_TLB_PTE                          0x0040104C
#घोषणा NV04_PGRAPH_DMA_A_TLB_TAG                          0x00401050
#घोषणा NV04_PGRAPH_DMA_A_ADJ_OFFSET                       0x00401054
#घोषणा NV04_PGRAPH_DMA_A_OFFSET                           0x00401058
#घोषणा NV04_PGRAPH_DMA_A_SIZE                             0x0040105C
#घोषणा NV04_PGRAPH_DMA_A_Y_SIZE                           0x00401060
#घोषणा NV04_PGRAPH_DMA_B_XLATE_INST                       0x00401080
#घोषणा NV04_PGRAPH_DMA_B_CONTROL                          0x00401084
#घोषणा NV04_PGRAPH_DMA_B_LIMIT                            0x00401088
#घोषणा NV04_PGRAPH_DMA_B_TLB_PTE                          0x0040108C
#घोषणा NV04_PGRAPH_DMA_B_TLB_TAG                          0x00401090
#घोषणा NV04_PGRAPH_DMA_B_ADJ_OFFSET                       0x00401094
#घोषणा NV04_PGRAPH_DMA_B_OFFSET                           0x00401098
#घोषणा NV04_PGRAPH_DMA_B_SIZE                             0x0040109C
#घोषणा NV04_PGRAPH_DMA_B_Y_SIZE                           0x004010A0
#घोषणा NV40_PGRAPH_TILE1(i)                               (0x00406900 + (i*16))
#घोषणा NV40_PGRAPH_TLIMIT1(i)                             (0x00406904 + (i*16))
#घोषणा NV40_PGRAPH_TSIZE1(i)                              (0x00406908 + (i*16))
#घोषणा NV40_PGRAPH_TSTATUS1(i)                            (0x0040690C + (i*16))


/* It's a guess that this works on NV03. Confirmed on NV04, though */
#घोषणा NV04_PFIFO_DELAY_0                                 0x00002040
#घोषणा NV04_PFIFO_DMA_TIMESLICE                           0x00002044
#घोषणा NV04_PFIFO_NEXT_CHANNEL                            0x00002050
#घोषणा NV03_PFIFO_INTR_0                                  0x00002100
#घोषणा NV03_PFIFO_INTR_EN_0                               0x00002140
#    define NV_PFIFO_INTR_CACHE_ERROR                          (1<<0)
#    define NV_PFIFO_INTR_RUNOUT                               (1<<4)
#    define NV_PFIFO_INTR_RUNOUT_OVERFLOW                      (1<<8)
#    define NV_PFIFO_INTR_DMA_PUSHER                          (1<<12)
#    define NV_PFIFO_INTR_DMA_PT                              (1<<16)
#    define NV_PFIFO_INTR_SEMAPHORE                           (1<<20)
#    define NV_PFIFO_INTR_ACQUIRE_TIMEOUT                     (1<<24)
#घोषणा NV03_PFIFO_RAMHT                                   0x00002210
#घोषणा NV03_PFIFO_RAMFC                                   0x00002214
#घोषणा NV03_PFIFO_RAMRO                                   0x00002218
#घोषणा NV40_PFIFO_RAMFC                                   0x00002220
#घोषणा NV03_PFIFO_CACHES                                  0x00002500
#घोषणा NV04_PFIFO_MODE                                    0x00002504
#घोषणा NV04_PFIFO_DMA                                     0x00002508
#घोषणा NV04_PFIFO_SIZE                                    0x0000250c
#घोषणा NV50_PFIFO_CTX_TABLE(c)                        (0x2600+(c)*4)
#घोषणा NV50_PFIFO_CTX_TABLE__SIZE                                128
#घोषणा NV50_PFIFO_CTX_TABLE_CHANNEL_ENABLED                  (1<<31)
#घोषणा NV50_PFIFO_CTX_TABLE_UNK30_BAD                        (1<<30)
#घोषणा NV50_PFIFO_CTX_TABLE_INSTANCE_MASK_G80             0x0FFFFFFF
#घोषणा NV50_PFIFO_CTX_TABLE_INSTANCE_MASK_G84             0x00FFFFFF
#घोषणा NV03_PFIFO_CACHE0_PUSH0                            0x00003000
#घोषणा NV03_PFIFO_CACHE0_PULL0                            0x00003040
#घोषणा NV04_PFIFO_CACHE0_PULL0                            0x00003050
#घोषणा NV04_PFIFO_CACHE0_PULL1                            0x00003054
#घोषणा NV03_PFIFO_CACHE1_PUSH0                            0x00003200
#घोषणा NV03_PFIFO_CACHE1_PUSH1                            0x00003204
#घोषणा NV03_PFIFO_CACHE1_PUSH1_DMA                            (1<<8)
#घोषणा NV40_PFIFO_CACHE1_PUSH1_DMA                           (1<<16)
#घोषणा NV03_PFIFO_CACHE1_PUSH1_CHID_MASK                  0x0000000f
#घोषणा NV10_PFIFO_CACHE1_PUSH1_CHID_MASK                  0x0000001f
#घोषणा NV50_PFIFO_CACHE1_PUSH1_CHID_MASK                  0x0000007f
#घोषणा NV03_PFIFO_CACHE1_PUT                              0x00003210
#घोषणा NV04_PFIFO_CACHE1_DMA_PUSH                         0x00003220
#घोषणा NV04_PFIFO_CACHE1_DMA_FETCH                        0x00003224
#    define NV_PFIFO_CACHE1_DMA_FETCH_TRIG_8_BYTES         0x00000000
#    define NV_PFIFO_CACHE1_DMA_FETCH_TRIG_16_BYTES        0x00000008
#    define NV_PFIFO_CACHE1_DMA_FETCH_TRIG_24_BYTES        0x00000010
#    define NV_PFIFO_CACHE1_DMA_FETCH_TRIG_32_BYTES        0x00000018
#    define NV_PFIFO_CACHE1_DMA_FETCH_TRIG_40_BYTES        0x00000020
#    define NV_PFIFO_CACHE1_DMA_FETCH_TRIG_48_BYTES        0x00000028
#    define NV_PFIFO_CACHE1_DMA_FETCH_TRIG_56_BYTES        0x00000030
#    define NV_PFIFO_CACHE1_DMA_FETCH_TRIG_64_BYTES        0x00000038
#    define NV_PFIFO_CACHE1_DMA_FETCH_TRIG_72_BYTES        0x00000040
#    define NV_PFIFO_CACHE1_DMA_FETCH_TRIG_80_BYTES        0x00000048
#    define NV_PFIFO_CACHE1_DMA_FETCH_TRIG_88_BYTES        0x00000050
#    define NV_PFIFO_CACHE1_DMA_FETCH_TRIG_96_BYTES        0x00000058
#    define NV_PFIFO_CACHE1_DMA_FETCH_TRIG_104_BYTES       0x00000060
#    define NV_PFIFO_CACHE1_DMA_FETCH_TRIG_112_BYTES       0x00000068
#    define NV_PFIFO_CACHE1_DMA_FETCH_TRIG_120_BYTES       0x00000070
#    define NV_PFIFO_CACHE1_DMA_FETCH_TRIG_128_BYTES       0x00000078
#    define NV_PFIFO_CACHE1_DMA_FETCH_TRIG_136_BYTES       0x00000080
#    define NV_PFIFO_CACHE1_DMA_FETCH_TRIG_144_BYTES       0x00000088
#    define NV_PFIFO_CACHE1_DMA_FETCH_TRIG_152_BYTES       0x00000090
#    define NV_PFIFO_CACHE1_DMA_FETCH_TRIG_160_BYTES       0x00000098
#    define NV_PFIFO_CACHE1_DMA_FETCH_TRIG_168_BYTES       0x000000A0
#    define NV_PFIFO_CACHE1_DMA_FETCH_TRIG_176_BYTES       0x000000A8
#    define NV_PFIFO_CACHE1_DMA_FETCH_TRIG_184_BYTES       0x000000B0
#    define NV_PFIFO_CACHE1_DMA_FETCH_TRIG_192_BYTES       0x000000B8
#    define NV_PFIFO_CACHE1_DMA_FETCH_TRIG_200_BYTES       0x000000C0
#    define NV_PFIFO_CACHE1_DMA_FETCH_TRIG_208_BYTES       0x000000C8
#    define NV_PFIFO_CACHE1_DMA_FETCH_TRIG_216_BYTES       0x000000D0
#    define NV_PFIFO_CACHE1_DMA_FETCH_TRIG_224_BYTES       0x000000D8
#    define NV_PFIFO_CACHE1_DMA_FETCH_TRIG_232_BYTES       0x000000E0
#    define NV_PFIFO_CACHE1_DMA_FETCH_TRIG_240_BYTES       0x000000E8
#    define NV_PFIFO_CACHE1_DMA_FETCH_TRIG_248_BYTES       0x000000F0
#    define NV_PFIFO_CACHE1_DMA_FETCH_TRIG_256_BYTES       0x000000F8
#    define NV_PFIFO_CACHE1_DMA_FETCH_SIZE                 0x0000E000
#    define NV_PFIFO_CACHE1_DMA_FETCH_SIZE_32_BYTES        0x00000000
#    define NV_PFIFO_CACHE1_DMA_FETCH_SIZE_64_BYTES        0x00002000
#    define NV_PFIFO_CACHE1_DMA_FETCH_SIZE_96_BYTES        0x00004000
#    define NV_PFIFO_CACHE1_DMA_FETCH_SIZE_128_BYTES       0x00006000
#    define NV_PFIFO_CACHE1_DMA_FETCH_SIZE_160_BYTES       0x00008000
#    define NV_PFIFO_CACHE1_DMA_FETCH_SIZE_192_BYTES       0x0000A000
#    define NV_PFIFO_CACHE1_DMA_FETCH_SIZE_224_BYTES       0x0000C000
#    define NV_PFIFO_CACHE1_DMA_FETCH_SIZE_256_BYTES       0x0000E000
#    define NV_PFIFO_CACHE1_DMA_FETCH_MAX_REQS             0x001F0000
#    define NV_PFIFO_CACHE1_DMA_FETCH_MAX_REQS_0           0x00000000
#    define NV_PFIFO_CACHE1_DMA_FETCH_MAX_REQS_1           0x00010000
#    define NV_PFIFO_CACHE1_DMA_FETCH_MAX_REQS_2           0x00020000
#    define NV_PFIFO_CACHE1_DMA_FETCH_MAX_REQS_3           0x00030000
#    define NV_PFIFO_CACHE1_DMA_FETCH_MAX_REQS_4           0x00040000
#    define NV_PFIFO_CACHE1_DMA_FETCH_MAX_REQS_5           0x00050000
#    define NV_PFIFO_CACHE1_DMA_FETCH_MAX_REQS_6           0x00060000
#    define NV_PFIFO_CACHE1_DMA_FETCH_MAX_REQS_7           0x00070000
#    define NV_PFIFO_CACHE1_DMA_FETCH_MAX_REQS_8           0x00080000
#    define NV_PFIFO_CACHE1_DMA_FETCH_MAX_REQS_9           0x00090000
#    define NV_PFIFO_CACHE1_DMA_FETCH_MAX_REQS_10          0x000A0000
#    define NV_PFIFO_CACHE1_DMA_FETCH_MAX_REQS_11          0x000B0000
#    define NV_PFIFO_CACHE1_DMA_FETCH_MAX_REQS_12          0x000C0000
#    define NV_PFIFO_CACHE1_DMA_FETCH_MAX_REQS_13          0x000D0000
#    define NV_PFIFO_CACHE1_DMA_FETCH_MAX_REQS_14          0x000E0000
#    define NV_PFIFO_CACHE1_DMA_FETCH_MAX_REQS_15          0x000F0000
#    define NV_PFIFO_CACHE1_ENDIAN                         0x80000000
#    define NV_PFIFO_CACHE1_LITTLE_ENDIAN                  0x7FFFFFFF
#    define NV_PFIFO_CACHE1_BIG_ENDIAN                     0x80000000
#घोषणा NV04_PFIFO_CACHE1_DMA_STATE                        0x00003228
#घोषणा NV04_PFIFO_CACHE1_DMA_INSTANCE                     0x0000322c
#घोषणा NV04_PFIFO_CACHE1_DMA_CTL                          0x00003230
#घोषणा NV04_PFIFO_CACHE1_DMA_PUT                          0x00003240
#घोषणा NV04_PFIFO_CACHE1_DMA_GET                          0x00003244
#घोषणा NV10_PFIFO_CACHE1_REF_CNT                          0x00003248
#घोषणा NV10_PFIFO_CACHE1_DMA_SUBROUTINE                   0x0000324C
#घोषणा NV03_PFIFO_CACHE1_PULL0                            0x00003240
#घोषणा NV04_PFIFO_CACHE1_PULL0                            0x00003250
#    define NV04_PFIFO_CACHE1_PULL0_HASH_FAILED            0x00000010
#    define NV04_PFIFO_CACHE1_PULL0_HASH_BUSY              0x00001000
#घोषणा NV03_PFIFO_CACHE1_PULL1                            0x00003250
#घोषणा NV04_PFIFO_CACHE1_PULL1                            0x00003254
#घोषणा NV04_PFIFO_CACHE1_HASH                             0x00003258
#घोषणा NV10_PFIFO_CACHE1_ACQUIRE_TIMEOUT                  0x00003260
#घोषणा NV10_PFIFO_CACHE1_ACQUIRE_TIMESTAMP                0x00003264
#घोषणा NV10_PFIFO_CACHE1_ACQUIRE_VALUE                    0x00003268
#घोषणा NV10_PFIFO_CACHE1_SEMAPHORE                        0x0000326C
#घोषणा NV03_PFIFO_CACHE1_GET                              0x00003270
#घोषणा NV04_PFIFO_CACHE1_ENGINE                           0x00003280
#घोषणा NV04_PFIFO_CACHE1_DMA_DCOUNT                       0x000032A0
#घोषणा NV40_PFIFO_GRCTX_INSTANCE                          0x000032E0
#घोषणा NV40_PFIFO_UNK32E4                                 0x000032E4
#घोषणा NV04_PFIFO_CACHE1_METHOD(i)                (0x00003800+(i*8))
#घोषणा NV04_PFIFO_CACHE1_DATA(i)                  (0x00003804+(i*8))
#घोषणा NV40_PFIFO_CACHE1_METHOD(i)                (0x00090000+(i*8))
#घोषणा NV40_PFIFO_CACHE1_DATA(i)                  (0x00090004+(i*8))

#घोषणा NV_CRTC0_INTSTAT                                   0x00600100
#घोषणा NV_CRTC0_INTEN                                     0x00600140
#घोषणा NV_CRTC1_INTSTAT                                   0x00602100
#घोषणा NV_CRTC1_INTEN                                     0x00602140
#    define NV_CRTC_INTR_VBLANK                                (1<<0)

#घोषणा NV04_PRAMIN						0x00700000

/* Fअगरo commands. These are not regs, neither masks */
#घोषणा NV03_FIFO_CMD_JUMP                                 0x20000000
#घोषणा NV03_FIFO_CMD_JUMP_OFFSET_MASK                     0x1ffffffc
#घोषणा NV03_FIFO_CMD_REWIND                               (NV03_FIFO_CMD_JUMP | (0 & NV03_FIFO_CMD_JUMP_OFFSET_MASK))

/* This is a partial import from rules-ng, a few things may be duplicated.
 * Eventually we should completely import everything from rules-ng.
 * For the moment check rules-ng क्रम करोcs.
  */

#घोषणा NV50_PMC                                            0x00000000
#घोषणा NV50_PMC__LEN                                              0x1
#घोषणा NV50_PMC__ESIZE                                         0x2000
#    define NV50_PMC_BOOT_0                                 0x00000000
#        define NV50_PMC_BOOT_0_REVISION                    0x000000ff
#        define NV50_PMC_BOOT_0_REVISION__SHIFT                      0
#        define NV50_PMC_BOOT_0_ARCH                        0x0ff00000
#        define NV50_PMC_BOOT_0_ARCH__SHIFT                         20
#    define NV50_PMC_INTR_0                                 0x00000100
#        define NV50_PMC_INTR_0_PFIFO                           (1<<8)
#        define NV50_PMC_INTR_0_PGRAPH                         (1<<12)
#        define NV50_PMC_INTR_0_PTIMER                         (1<<20)
#        define NV50_PMC_INTR_0_HOTPLUG                        (1<<21)
#        define NV50_PMC_INTR_0_DISPLAY                        (1<<26)
#    define NV50_PMC_INTR_EN_0                              0x00000140
#        define NV50_PMC_INTR_EN_0_MASTER                       (1<<0)
#            define NV50_PMC_INTR_EN_0_MASTER_DISABLED          (0<<0)
#            define NV50_PMC_INTR_EN_0_MASTER_ENABLED           (1<<0)
#    define NV50_PMC_ENABLE                                 0x00000200
#        define NV50_PMC_ENABLE_PFIFO                           (1<<8)
#        define NV50_PMC_ENABLE_PGRAPH                         (1<<12)

#घोषणा NV50_PCONNECTOR                                     0x0000e000
#घोषणा NV50_PCONNECTOR__LEN                                       0x1
#घोषणा NV50_PCONNECTOR__ESIZE                                  0x1000
#    define NV50_PCONNECTOR_HOTPLUG_INTR                    0x0000e050
#        define NV50_PCONNECTOR_HOTPLUG_INTR_PLUG_I2C0          (1<<0)
#        define NV50_PCONNECTOR_HOTPLUG_INTR_PLUG_I2C1          (1<<1)
#        define NV50_PCONNECTOR_HOTPLUG_INTR_PLUG_I2C2          (1<<2)
#        define NV50_PCONNECTOR_HOTPLUG_INTR_PLUG_I2C3          (1<<3)
#        define NV50_PCONNECTOR_HOTPLUG_INTR_UNPLUG_I2C0       (1<<16)
#        define NV50_PCONNECTOR_HOTPLUG_INTR_UNPLUG_I2C1       (1<<17)
#        define NV50_PCONNECTOR_HOTPLUG_INTR_UNPLUG_I2C2       (1<<18)
#        define NV50_PCONNECTOR_HOTPLUG_INTR_UNPLUG_I2C3       (1<<19)
#    define NV50_PCONNECTOR_HOTPLUG_CTRL                    0x0000e054
#        define NV50_PCONNECTOR_HOTPLUG_CTRL_PLUG_I2C0          (1<<0)
#        define NV50_PCONNECTOR_HOTPLUG_CTRL_PLUG_I2C1          (1<<1)
#        define NV50_PCONNECTOR_HOTPLUG_CTRL_PLUG_I2C2          (1<<2)
#        define NV50_PCONNECTOR_HOTPLUG_CTRL_PLUG_I2C3          (1<<3)
#        define NV50_PCONNECTOR_HOTPLUG_CTRL_UNPLUG_I2C0       (1<<16)
#        define NV50_PCONNECTOR_HOTPLUG_CTRL_UNPLUG_I2C1       (1<<17)
#        define NV50_PCONNECTOR_HOTPLUG_CTRL_UNPLUG_I2C2       (1<<18)
#        define NV50_PCONNECTOR_HOTPLUG_CTRL_UNPLUG_I2C3       (1<<19)
#    define NV50_PCONNECTOR_HOTPLUG_STATE                   0x0000e104
#        define NV50_PCONNECTOR_HOTPLUG_STATE_PIN_CONNECTED_I2C0 (1<<2)
#        define NV50_PCONNECTOR_HOTPLUG_STATE_PIN_CONNECTED_I2C1 (1<<6)
#        define NV50_PCONNECTOR_HOTPLUG_STATE_PIN_CONNECTED_I2C2 (1<<10)
#        define NV50_PCONNECTOR_HOTPLUG_STATE_PIN_CONNECTED_I2C3 (1<<14)
#    define NV50_PCONNECTOR_I2C_PORT_0                      0x0000e138
#    define NV50_PCONNECTOR_I2C_PORT_1                      0x0000e150
#    define NV50_PCONNECTOR_I2C_PORT_2                      0x0000e168
#    define NV50_PCONNECTOR_I2C_PORT_3                      0x0000e180
#    define NV50_PCONNECTOR_I2C_PORT_4                      0x0000e240
#    define NV50_PCONNECTOR_I2C_PORT_5                      0x0000e258

#घोषणा NV50_AUXCH_DATA_OUT(i, n)            ((n) * 4 + (i) * 0x50 + 0x0000e4c0)
#घोषणा NV50_AUXCH_DATA_OUT__SIZE                                             4
#घोषणा NV50_AUXCH_DATA_IN(i, n)             ((n) * 4 + (i) * 0x50 + 0x0000e4d0)
#घोषणा NV50_AUXCH_DATA_IN__SIZE                                              4
#घोषणा NV50_AUXCH_ADDR(i)                             ((i) * 0x50 + 0x0000e4e0)
#घोषणा NV50_AUXCH_CTRL(i)                             ((i) * 0x50 + 0x0000e4e4)
#घोषणा NV50_AUXCH_CTRL_LINKSTAT                                     0x01000000
#घोषणा NV50_AUXCH_CTRL_LINKSTAT_NOT_READY                           0x00000000
#घोषणा NV50_AUXCH_CTRL_LINKSTAT_READY                               0x01000000
#घोषणा NV50_AUXCH_CTRL_LINKEN                                       0x00100000
#घोषणा NV50_AUXCH_CTRL_LINKEN_DISABLED                              0x00000000
#घोषणा NV50_AUXCH_CTRL_LINKEN_ENABLED                               0x00100000
#घोषणा NV50_AUXCH_CTRL_EXEC                                         0x00010000
#घोषणा NV50_AUXCH_CTRL_EXEC_COMPLETE                                0x00000000
#घोषणा NV50_AUXCH_CTRL_EXEC_IN_PROCESS                              0x00010000
#घोषणा NV50_AUXCH_CTRL_CMD                                          0x0000f000
#घोषणा NV50_AUXCH_CTRL_CMD_SHIFT                                            12
#घोषणा NV50_AUXCH_CTRL_LEN                                          0x0000000f
#घोषणा NV50_AUXCH_CTRL_LEN_SHIFT                                             0
#घोषणा NV50_AUXCH_STAT(i)                             ((i) * 0x50 + 0x0000e4e8)
#घोषणा NV50_AUXCH_STAT_STATE                                        0x10000000
#घोषणा NV50_AUXCH_STAT_STATE_NOT_READY                              0x00000000
#घोषणा NV50_AUXCH_STAT_STATE_READY                                  0x10000000
#घोषणा NV50_AUXCH_STAT_REPLY                                        0x000f0000
#घोषणा NV50_AUXCH_STAT_REPLY_AUX                                    0x00030000
#घोषणा NV50_AUXCH_STAT_REPLY_AUX_ACK                                0x00000000
#घोषणा NV50_AUXCH_STAT_REPLY_AUX_NACK                               0x00010000
#घोषणा NV50_AUXCH_STAT_REPLY_AUX_DEFER                              0x00020000
#घोषणा NV50_AUXCH_STAT_REPLY_I2C                                    0x000c0000
#घोषणा NV50_AUXCH_STAT_REPLY_I2C_ACK                                0x00000000
#घोषणा NV50_AUXCH_STAT_REPLY_I2C_NACK                               0x00040000
#घोषणा NV50_AUXCH_STAT_REPLY_I2C_DEFER                              0x00080000
#घोषणा NV50_AUXCH_STAT_COUNT                                        0x0000001f

#घोषणा NV50_PBUS                                           0x00088000
#घोषणा NV50_PBUS__LEN                                             0x1
#घोषणा NV50_PBUS__ESIZE                                        0x1000
#    define NV50_PBUS_PCI_ID                                0x00088000
#        define NV50_PBUS_PCI_ID_VENDOR_ID                  0x0000ffff
#        define NV50_PBUS_PCI_ID_VENDOR_ID__SHIFT                    0
#        define NV50_PBUS_PCI_ID_DEVICE_ID                  0xffff0000
#        define NV50_PBUS_PCI_ID_DEVICE_ID__SHIFT                   16

#घोषणा NV50_PFB                                            0x00100000
#घोषणा NV50_PFB__LEN                                              0x1
#घोषणा NV50_PFB__ESIZE                                         0x1000

#घोषणा NV50_PEXTDEV                                        0x00101000
#घोषणा NV50_PEXTDEV__LEN                                          0x1
#घोषणा NV50_PEXTDEV__ESIZE                                     0x1000

#घोषणा NV50_PROM                                           0x00300000
#घोषणा NV50_PROM__LEN                                             0x1
#घोषणा NV50_PROM__ESIZE                                       0x10000

#घोषणा NV50_PGRAPH                                         0x00400000
#घोषणा NV50_PGRAPH__LEN                                           0x1
#घोषणा NV50_PGRAPH__ESIZE                                     0x10000

#घोषणा NV50_PDISPLAY                                                0x00610000
#घोषणा NV50_PDISPLAY_OBJECTS                                        0x00610010
#घोषणा NV50_PDISPLAY_INTR_0                                         0x00610020
#घोषणा NV50_PDISPLAY_INTR_1                                         0x00610024
#घोषणा NV50_PDISPLAY_INTR_1_VBLANK_CRTC                             0x0000000c
#घोषणा NV50_PDISPLAY_INTR_1_VBLANK_CRTC_SHIFT                                2
#घोषणा NV50_PDISPLAY_INTR_1_VBLANK_CRTC_(n)                   (1 << ((n) + 2))
#घोषणा NV50_PDISPLAY_INTR_1_VBLANK_CRTC_0                           0x00000004
#घोषणा NV50_PDISPLAY_INTR_1_VBLANK_CRTC_1                           0x00000008
#घोषणा NV50_PDISPLAY_INTR_1_CLK_UNK10                               0x00000010
#घोषणा NV50_PDISPLAY_INTR_1_CLK_UNK20                               0x00000020
#घोषणा NV50_PDISPLAY_INTR_1_CLK_UNK40                               0x00000040
#घोषणा NV50_PDISPLAY_INTR_EN_0                                      0x00610028
#घोषणा NV50_PDISPLAY_INTR_EN_1                                      0x0061002c
#घोषणा NV50_PDISPLAY_INTR_EN_1_VBLANK_CRTC                          0x0000000c
#घोषणा NV50_PDISPLAY_INTR_EN_1_VBLANK_CRTC_(n)                 (1 << ((n) + 2))
#घोषणा NV50_PDISPLAY_INTR_EN_1_VBLANK_CRTC_0                        0x00000004
#घोषणा NV50_PDISPLAY_INTR_EN_1_VBLANK_CRTC_1                        0x00000008
#घोषणा NV50_PDISPLAY_INTR_EN_1_CLK_UNK10                            0x00000010
#घोषणा NV50_PDISPLAY_INTR_EN_1_CLK_UNK20                            0x00000020
#घोषणा NV50_PDISPLAY_INTR_EN_1_CLK_UNK40                            0x00000040
#घोषणा NV50_PDISPLAY_UNK30_CTRL                                     0x00610030
#घोषणा NV50_PDISPLAY_UNK30_CTRL_UPDATE_VCLK0                        0x00000200
#घोषणा NV50_PDISPLAY_UNK30_CTRL_UPDATE_VCLK1                        0x00000400
#घोषणा NV50_PDISPLAY_UNK30_CTRL_PENDING                             0x80000000
#घोषणा NV50_PDISPLAY_TRAPPED_ADDR(i)                  ((i) * 0x08 + 0x00610080)
#घोषणा NV50_PDISPLAY_TRAPPED_DATA(i)                  ((i) * 0x08 + 0x00610084)
#घोषणा NV50_PDISPLAY_EVO_CTRL(i)                      ((i) * 0x10 + 0x00610200)
#घोषणा NV50_PDISPLAY_EVO_CTRL_DMA                                   0x00000010
#घोषणा NV50_PDISPLAY_EVO_CTRL_DMA_DISABLED                          0x00000000
#घोषणा NV50_PDISPLAY_EVO_CTRL_DMA_ENABLED                           0x00000010
#घोषणा NV50_PDISPLAY_EVO_DMA_CB(i)                    ((i) * 0x10 + 0x00610204)
#घोषणा NV50_PDISPLAY_EVO_DMA_CB_LOCATION                            0x00000002
#घोषणा NV50_PDISPLAY_EVO_DMA_CB_LOCATION_VRAM                       0x00000000
#घोषणा NV50_PDISPLAY_EVO_DMA_CB_LOCATION_SYSTEM                     0x00000002
#घोषणा NV50_PDISPLAY_EVO_DMA_CB_VALID                               0x00000001
#घोषणा NV50_PDISPLAY_EVO_UNK2(i)                      ((i) * 0x10 + 0x00610208)
#घोषणा NV50_PDISPLAY_EVO_HASH_TAG(i)                  ((i) * 0x10 + 0x0061020c)

#घोषणा NV50_PDISPLAY_CURSOR                                         0x00610270
#घोषणा NV50_PDISPLAY_CURSOR_CURSOR_CTRL2(i)           ((i) * 0x10 + 0x00610270)
#घोषणा NV50_PDISPLAY_CURSOR_CURSOR_CTRL2_ON                         0x00000001
#घोषणा NV50_PDISPLAY_CURSOR_CURSOR_CTRL2_STATUS                     0x00030000
#घोषणा NV50_PDISPLAY_CURSOR_CURSOR_CTRL2_STATUS_ACTIVE              0x00010000

#घोषणा NV50_PDISPLAY_PIO_CTRL                                       0x00610300
#घोषणा NV50_PDISPLAY_PIO_CTRL_PENDING                               0x80000000
#घोषणा NV50_PDISPLAY_PIO_CTRL_MTHD                                  0x00001ffc
#घोषणा NV50_PDISPLAY_PIO_CTRL_ENABLED                               0x00000001
#घोषणा NV50_PDISPLAY_PIO_DATA                                       0x00610304

#घोषणा NV50_PDISPLAY_CRTC_P(i, r)        ((i) * 0x540 + NV50_PDISPLAY_CRTC_##r)
#घोषणा NV50_PDISPLAY_CRTC_C(i, r)    (4 + (i) * 0x540 + NV50_PDISPLAY_CRTC_##r)
#घोषणा NV50_PDISPLAY_CRTC_UNK_0A18 /* mthd 0x0900 */                0x00610a18
#घोषणा NV50_PDISPLAY_CRTC_CLUT_MODE                                 0x00610a24
#घोषणा NV50_PDISPLAY_CRTC_INTERLACE                                 0x00610a48
#घोषणा NV50_PDISPLAY_CRTC_SCALE_CTRL                                0x00610a50
#घोषणा NV50_PDISPLAY_CRTC_CURSOR_CTRL                               0x00610a58
#घोषणा NV50_PDISPLAY_CRTC_UNK0A78 /* mthd 0x0904 */                 0x00610a78
#घोषणा NV50_PDISPLAY_CRTC_UNK0AB8                                   0x00610ab8
#घोषणा NV50_PDISPLAY_CRTC_DEPTH                                     0x00610ac8
#घोषणा NV50_PDISPLAY_CRTC_CLOCK                                     0x00610ad0
#घोषणा NV50_PDISPLAY_CRTC_COLOR_CTRL                                0x00610ae0
#घोषणा NV50_PDISPLAY_CRTC_SYNC_START_TO_BLANK_END                   0x00610ae8
#घोषणा NV50_PDISPLAY_CRTC_MODE_UNK1                                 0x00610af0
#घोषणा NV50_PDISPLAY_CRTC_DISPLAY_TOTAL                             0x00610af8
#घोषणा NV50_PDISPLAY_CRTC_SYNC_DURATION                             0x00610b00
#घोषणा NV50_PDISPLAY_CRTC_MODE_UNK2                                 0x00610b08
#घोषणा NV50_PDISPLAY_CRTC_UNK_0B10 /* mthd 0x0828 */                0x00610b10
#घोषणा NV50_PDISPLAY_CRTC_FB_SIZE                                   0x00610b18
#घोषणा NV50_PDISPLAY_CRTC_FB_PITCH                                  0x00610b20
#घोषणा NV50_PDISPLAY_CRTC_FB_PITCH_LINEAR                           0x00100000
#घोषणा NV50_PDISPLAY_CRTC_FB_POS                                    0x00610b28
#घोषणा NV50_PDISPLAY_CRTC_SCALE_CENTER_OFFSET                       0x00610b38
#घोषणा NV50_PDISPLAY_CRTC_REAL_RES                                  0x00610b40
#घोषणा NV50_PDISPLAY_CRTC_SCALE_RES1                                0x00610b48
#घोषणा NV50_PDISPLAY_CRTC_SCALE_RES2                                0x00610b50

#घोषणा NV50_PDISPLAY_DAC_MODE_CTRL_P(i)                (0x00610b58 + (i) * 0x8)
#घोषणा NV50_PDISPLAY_DAC_MODE_CTRL_C(i)                (0x00610b5c + (i) * 0x8)
#घोषणा NV50_PDISPLAY_SOR_MODE_CTRL_P(i)                (0x00610b70 + (i) * 0x8)
#घोषणा NV50_PDISPLAY_SOR_MODE_CTRL_C(i)                (0x00610b74 + (i) * 0x8)
#घोषणा NV50_PDISPLAY_EXT_MODE_CTRL_P(i)                (0x00610b80 + (i) * 0x8)
#घोषणा NV50_PDISPLAY_EXT_MODE_CTRL_C(i)                (0x00610b84 + (i) * 0x8)
#घोषणा NV50_PDISPLAY_DAC_MODE_CTRL2_P(i)               (0x00610bdc + (i) * 0x8)
#घोषणा NV50_PDISPLAY_DAC_MODE_CTRL2_C(i)               (0x00610be0 + (i) * 0x8)
#घोषणा NV90_PDISPLAY_SOR_MODE_CTRL_P(i)                (0x00610794 + (i) * 0x8)
#घोषणा NV90_PDISPLAY_SOR_MODE_CTRL_C(i)                (0x00610798 + (i) * 0x8)

#घोषणा NV50_PDISPLAY_CRTC_CLK                                       0x00614000
#घोषणा NV50_PDISPLAY_CRTC_CLK_CTRL1(i)                 ((i) * 0x800 + 0x614100)
#घोषणा NV50_PDISPLAY_CRTC_CLK_CTRL1_CONNECTED                       0x00000600
#घोषणा NV50_PDISPLAY_CRTC_CLK_VPLL_A(i)                ((i) * 0x800 + 0x614104)
#घोषणा NV50_PDISPLAY_CRTC_CLK_VPLL_B(i)                ((i) * 0x800 + 0x614108)
#घोषणा NV50_PDISPLAY_CRTC_CLK_CTRL2(i)                 ((i) * 0x800 + 0x614200)

#घोषणा NV50_PDISPLAY_DAC_CLK                                        0x00614000
#घोषणा NV50_PDISPLAY_DAC_CLK_CTRL2(i)                  ((i) * 0x800 + 0x614280)

#घोषणा NV50_PDISPLAY_SOR_CLK                                        0x00614000
#घोषणा NV50_PDISPLAY_SOR_CLK_CTRL2(i)                  ((i) * 0x800 + 0x614300)

#घोषणा NV50_PDISPLAY_VGACRTC(r)                                ((r) + 0x619400)

#घोषणा NV50_PDISPLAY_DAC                                            0x0061a000
#घोषणा NV50_PDISPLAY_DAC_DPMS_CTRL(i)                (0x0061a004 + (i) * 0x800)
#घोषणा NV50_PDISPLAY_DAC_DPMS_CTRL_HSYNC_OFF                        0x00000001
#घोषणा NV50_PDISPLAY_DAC_DPMS_CTRL_VSYNC_OFF                        0x00000004
#घोषणा NV50_PDISPLAY_DAC_DPMS_CTRL_BLANKED                          0x00000010
#घोषणा NV50_PDISPLAY_DAC_DPMS_CTRL_OFF                              0x00000040
#घोषणा NV50_PDISPLAY_DAC_DPMS_CTRL_PENDING                          0x80000000
#घोषणा NV50_PDISPLAY_DAC_LOAD_CTRL(i)                (0x0061a00c + (i) * 0x800)
#घोषणा NV50_PDISPLAY_DAC_LOAD_CTRL_ACTIVE                           0x00100000
#घोषणा NV50_PDISPLAY_DAC_LOAD_CTRL_PRESENT                          0x38000000
#घोषणा NV50_PDISPLAY_DAC_LOAD_CTRL_DONE                             0x80000000
#घोषणा NV50_PDISPLAY_DAC_CLK_CTRL1(i)                (0x0061a010 + (i) * 0x800)
#घोषणा NV50_PDISPLAY_DAC_CLK_CTRL1_CONNECTED                        0x00000600

#घोषणा NV50_PDISPLAY_SOR                                            0x0061c000
#घोषणा NV50_PDISPLAY_SOR_DPMS_CTRL(i)                (0x0061c004 + (i) * 0x800)
#घोषणा NV50_PDISPLAY_SOR_DPMS_CTRL_PENDING                          0x80000000
#घोषणा NV50_PDISPLAY_SOR_DPMS_CTRL_ON                               0x00000001
#घोषणा NV50_PDISPLAY_SOR_CLK_CTRL1(i)                (0x0061c008 + (i) * 0x800)
#घोषणा NV50_PDISPLAY_SOR_CLK_CTRL1_CONNECTED                        0x00000600
#घोषणा NV50_PDISPLAY_SOR_DPMS_STATE(i)               (0x0061c030 + (i) * 0x800)
#घोषणा NV50_PDISPLAY_SOR_DPMS_STATE_ACTIVE                          0x00030000
#घोषणा NV50_PDISPLAY_SOR_DPMS_STATE_BLANKED                         0x00080000
#घोषणा NV50_PDISPLAY_SOR_DPMS_STATE_WAIT                            0x10000000
#घोषणा NV50_PDISP_SOR_PWM_DIV(i)                     (0x0061c080 + (i) * 0x800)
#घोषणा NV50_PDISP_SOR_PWM_CTL(i)                     (0x0061c084 + (i) * 0x800)
#घोषणा NV50_PDISP_SOR_PWM_CTL_NEW                                   0x80000000
#घोषणा NVA3_PDISP_SOR_PWM_CTL_UNK                                   0x40000000
#घोषणा NV50_PDISP_SOR_PWM_CTL_VAL                                   0x000007ff
#घोषणा NVA3_PDISP_SOR_PWM_CTL_VAL                                   0x00ffffff
#घोषणा NV50_SOR_DP_CTRL(i, l)           (0x0061c10c + (i) * 0x800 + (l) * 0x80)
#घोषणा NV50_SOR_DP_CTRL_ENABLED                                     0x00000001
#घोषणा NV50_SOR_DP_CTRL_ENHANCED_FRAME_ENABLED                      0x00004000
#घोषणा NV50_SOR_DP_CTRL_LANE_MASK                                   0x001f0000
#घोषणा NV50_SOR_DP_CTRL_LANE_0_ENABLED                              0x00010000
#घोषणा NV50_SOR_DP_CTRL_LANE_1_ENABLED                              0x00020000
#घोषणा NV50_SOR_DP_CTRL_LANE_2_ENABLED                              0x00040000
#घोषणा NV50_SOR_DP_CTRL_LANE_3_ENABLED                              0x00080000
#घोषणा NV50_SOR_DP_CTRL_TRAINING_PATTERN                            0x0f000000
#घोषणा NV50_SOR_DP_CTRL_TRAINING_PATTERN_DISABLED                   0x00000000
#घोषणा NV50_SOR_DP_CTRL_TRAINING_PATTERN_1                          0x01000000
#घोषणा NV50_SOR_DP_CTRL_TRAINING_PATTERN_2                          0x02000000
#घोषणा NV50_SOR_DP_UNK118(i, l)         (0x0061c118 + (i) * 0x800 + (l) * 0x80)
#घोषणा NV50_SOR_DP_UNK120(i, l)         (0x0061c120 + (i) * 0x800 + (l) * 0x80)
#घोषणा NV50_SOR_DP_SCFG(i, l)           (0x0061c128 + (i) * 0x800 + (l) * 0x80)
#घोषणा NV50_SOR_DP_UNK130(i, l)         (0x0061c130 + (i) * 0x800 + (l) * 0x80)

#घोषणा NV50_PDISPLAY_USER(i)                        ((i) * 0x1000 + 0x00640000)
#घोषणा NV50_PDISPLAY_USER_PUT(i)                    ((i) * 0x1000 + 0x00640000)
#घोषणा NV50_PDISPLAY_USER_GET(i)                    ((i) * 0x1000 + 0x00640004)

#घोषणा NV50_PDISPLAY_CURSOR_USER                                    0x00647000
#घोषणा NV50_PDISPLAY_CURSOR_USER_POS_CTRL(i)        ((i) * 0x1000 + 0x00647080)
#घोषणा NV50_PDISPLAY_CURSOR_USER_POS(i)             ((i) * 0x1000 + 0x00647084)
