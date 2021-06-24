<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
#अगर_अघोषित __NVIF_CLASS_H__
#घोषणा __NVIF_CLASS_H__

/* these class numbers are made up by us, and not nvidia-asचिन्हित */
#घोषणा NVIF_CLASS_CLIENT                            /* अगर0000.h */ -0x00000000

#घोषणा NVIF_CLASS_CONTROL                           /* अगर0001.h */ -0x00000001

#घोषणा NVIF_CLASS_PERFMON                           /* अगर0002.h */ -0x00000002
#घोषणा NVIF_CLASS_PERFDOM                           /* अगर0003.h */ -0x00000003

#घोषणा NVIF_CLASS_SW_NV04                           /* अगर0004.h */ -0x00000004
#घोषणा NVIF_CLASS_SW_NV10                           /* अगर0005.h */ -0x00000005
#घोषणा NVIF_CLASS_SW_NV50                           /* अगर0005.h */ -0x00000006
#घोषणा NVIF_CLASS_SW_GF100                          /* अगर0005.h */ -0x00000007

#घोषणा NVIF_CLASS_MMU                               /* अगर0008.h */  0x80000008
#घोषणा NVIF_CLASS_MMU_NV04                          /* अगर0008.h */  0x80000009
#घोषणा NVIF_CLASS_MMU_NV50                          /* अगर0008.h */  0x80005009
#घोषणा NVIF_CLASS_MMU_GF100                         /* अगर0008.h */  0x80009009

#घोषणा NVIF_CLASS_MEM                               /* अगर000a.h */  0x8000000a
#घोषणा NVIF_CLASS_MEM_NV04                          /* अगर000b.h */  0x8000000b
#घोषणा NVIF_CLASS_MEM_NV50                          /* अगर500b.h */  0x8000500b
#घोषणा NVIF_CLASS_MEM_GF100                         /* अगर900b.h */  0x8000900b

#घोषणा NVIF_CLASS_VMM                               /* अगर000c.h */  0x8000000c
#घोषणा NVIF_CLASS_VMM_NV04                          /* अगर000d.h */  0x8000000d
#घोषणा NVIF_CLASS_VMM_NV50                          /* अगर500d.h */  0x8000500d
#घोषणा NVIF_CLASS_VMM_GF100                         /* अगर900d.h */  0x8000900d
#घोषणा NVIF_CLASS_VMM_GM200                         /* अगरb00d.h */  0x8000b00d
#घोषणा NVIF_CLASS_VMM_GP100                         /* अगरc00d.h */  0x8000c00d

/* the below match nvidia-asचिन्हित (either in hw, or sw) class numbers */
#घोषणा NV_शून्य_CLASS                                                0x00000030

#घोषणा NV_DEVICE                                     /* cl0080.h */ 0x00000080

#घोषणा NV_DMA_FROM_MEMORY                            /* cl0002.h */ 0x00000002
#घोषणा NV_DMA_TO_MEMORY                              /* cl0002.h */ 0x00000003
#घोषणा NV_DMA_IN_MEMORY                              /* cl0002.h */ 0x0000003d

#घोषणा NV50_TWOD                                                    0x0000502d
#घोषणा FERMI_TWOD_A                                                 0x0000902d

#घोषणा NV50_MEMORY_TO_MEMORY_FORMAT                                 0x00005039
#घोषणा FERMI_MEMORY_TO_MEMORY_FORMAT_A                              0x00009039

#घोषणा KEPLER_INLINE_TO_MEMORY_A                                    0x0000a040
#घोषणा KEPLER_INLINE_TO_MEMORY_B                                    0x0000a140

#घोषणा NV04_DISP                                     /* cl0046.h */ 0x00000046

#घोषणा VOLTA_USERMODE_A                                             0x0000c361

#घोषणा MAXWELL_FAULT_BUFFER_A                        /* clb069.h */ 0x0000b069
#घोषणा VOLTA_FAULT_BUFFER_A                          /* clb069.h */ 0x0000c369

#घोषणा NV03_CHANNEL_DMA                              /* cl506b.h */ 0x0000006b
#घोषणा NV10_CHANNEL_DMA                              /* cl506b.h */ 0x0000006e
#घोषणा NV17_CHANNEL_DMA                              /* cl506b.h */ 0x0000176e
#घोषणा NV40_CHANNEL_DMA                              /* cl506b.h */ 0x0000406e
#घोषणा NV50_CHANNEL_DMA                              /* cl506e.h */ 0x0000506e
#घोषणा G82_CHANNEL_DMA                               /* cl826e.h */ 0x0000826e

#घोषणा NV50_CHANNEL_GPFIFO                           /* cl506f.h */ 0x0000506f
#घोषणा G82_CHANNEL_GPFIFO                            /* cl826f.h */ 0x0000826f
#घोषणा FERMI_CHANNEL_GPFIFO                          /* cl906f.h */ 0x0000906f
#घोषणा KEPLER_CHANNEL_GPFIFO_A                       /* cla06f.h */ 0x0000a06f
#घोषणा KEPLER_CHANNEL_GPFIFO_B                       /* cla06f.h */ 0x0000a16f
#घोषणा MAXWELL_CHANNEL_GPFIFO_A                      /* cla06f.h */ 0x0000b06f
#घोषणा PASCAL_CHANNEL_GPFIFO_A                       /* cla06f.h */ 0x0000c06f
#घोषणा VOLTA_CHANNEL_GPFIFO_A                        /* clc36f.h */ 0x0000c36f
#घोषणा TURING_CHANNEL_GPFIFO_A                       /* clc36f.h */ 0x0000c46f

#घोषणा NV50_DISP                                     /* cl5070.h */ 0x00005070
#घोषणा G82_DISP                                      /* cl5070.h */ 0x00008270
#घोषणा GT200_DISP                                    /* cl5070.h */ 0x00008370
#घोषणा GT214_DISP                                    /* cl5070.h */ 0x00008570
#घोषणा GT206_DISP                                    /* cl5070.h */ 0x00008870
#घोषणा GF110_DISP                                    /* cl5070.h */ 0x00009070
#घोषणा GK104_DISP                                    /* cl5070.h */ 0x00009170
#घोषणा GK110_DISP                                    /* cl5070.h */ 0x00009270
#घोषणा GM107_DISP                                    /* cl5070.h */ 0x00009470
#घोषणा GM200_DISP                                    /* cl5070.h */ 0x00009570
#घोषणा GP100_DISP                                    /* cl5070.h */ 0x00009770
#घोषणा GP102_DISP                                    /* cl5070.h */ 0x00009870
#घोषणा GV100_DISP                                    /* cl5070.h */ 0x0000c370
#घोषणा TU102_DISP                                    /* cl5070.h */ 0x0000c570
#घोषणा GA102_DISP                                    /* cl5070.h */ 0x0000c670

#घोषणा GV100_DISP_CAPS                                              0x0000c373

#घोषणा NV31_MPEG                                                    0x00003174
#घोषणा G82_MPEG                                                     0x00008274

#घोषणा NV74_VP2                                                     0x00007476

#घोषणा NV50_DISP_CURSOR                              /* cl507a.h */ 0x0000507a
#घोषणा G82_DISP_CURSOR                               /* cl507a.h */ 0x0000827a
#घोषणा GT214_DISP_CURSOR                             /* cl507a.h */ 0x0000857a
#घोषणा GF110_DISP_CURSOR                             /* cl507a.h */ 0x0000907a
#घोषणा GK104_DISP_CURSOR                             /* cl507a.h */ 0x0000917a
#घोषणा GV100_DISP_CURSOR                             /* cl507a.h */ 0x0000c37a
#घोषणा TU102_DISP_CURSOR                             /* cl507a.h */ 0x0000c57a
#घोषणा GA102_DISP_CURSOR                             /* cl507a.h */ 0x0000c67a

#घोषणा NV50_DISP_OVERLAY                             /* cl507b.h */ 0x0000507b
#घोषणा G82_DISP_OVERLAY                              /* cl507b.h */ 0x0000827b
#घोषणा GT214_DISP_OVERLAY                            /* cl507b.h */ 0x0000857b
#घोषणा GF110_DISP_OVERLAY                            /* cl507b.h */ 0x0000907b
#घोषणा GK104_DISP_OVERLAY                            /* cl507b.h */ 0x0000917b

#घोषणा GV100_DISP_WINDOW_IMM_CHANNEL_DMA             /* clc37b.h */ 0x0000c37b
#घोषणा TU102_DISP_WINDOW_IMM_CHANNEL_DMA             /* clc37b.h */ 0x0000c57b
#घोषणा GA102_DISP_WINDOW_IMM_CHANNEL_DMA             /* clc37b.h */ 0x0000c67b

#घोषणा NV50_DISP_BASE_CHANNEL_DMA                    /* cl507c.h */ 0x0000507c
#घोषणा G82_DISP_BASE_CHANNEL_DMA                     /* cl507c.h */ 0x0000827c
#घोषणा GT200_DISP_BASE_CHANNEL_DMA                   /* cl507c.h */ 0x0000837c
#घोषणा GT214_DISP_BASE_CHANNEL_DMA                   /* cl507c.h */ 0x0000857c
#घोषणा GF110_DISP_BASE_CHANNEL_DMA                   /* cl507c.h */ 0x0000907c
#घोषणा GK104_DISP_BASE_CHANNEL_DMA                   /* cl507c.h */ 0x0000917c
#घोषणा GK110_DISP_BASE_CHANNEL_DMA                   /* cl507c.h */ 0x0000927c

#घोषणा NV50_DISP_CORE_CHANNEL_DMA                    /* cl507d.h */ 0x0000507d
#घोषणा G82_DISP_CORE_CHANNEL_DMA                     /* cl507d.h */ 0x0000827d
#घोषणा GT200_DISP_CORE_CHANNEL_DMA                   /* cl507d.h */ 0x0000837d
#घोषणा GT214_DISP_CORE_CHANNEL_DMA                   /* cl507d.h */ 0x0000857d
#घोषणा GT206_DISP_CORE_CHANNEL_DMA                   /* cl507d.h */ 0x0000887d
#घोषणा GF110_DISP_CORE_CHANNEL_DMA                   /* cl507d.h */ 0x0000907d
#घोषणा GK104_DISP_CORE_CHANNEL_DMA                   /* cl507d.h */ 0x0000917d
#घोषणा GK110_DISP_CORE_CHANNEL_DMA                   /* cl507d.h */ 0x0000927d
#घोषणा GM107_DISP_CORE_CHANNEL_DMA                   /* cl507d.h */ 0x0000947d
#घोषणा GM200_DISP_CORE_CHANNEL_DMA                   /* cl507d.h */ 0x0000957d
#घोषणा GP100_DISP_CORE_CHANNEL_DMA                   /* cl507d.h */ 0x0000977d
#घोषणा GP102_DISP_CORE_CHANNEL_DMA                   /* cl507d.h */ 0x0000987d
#घोषणा GV100_DISP_CORE_CHANNEL_DMA                   /* cl507d.h */ 0x0000c37d
#घोषणा TU102_DISP_CORE_CHANNEL_DMA                   /* cl507d.h */ 0x0000c57d
#घोषणा GA102_DISP_CORE_CHANNEL_DMA                   /* cl507d.h */ 0x0000c67d

#घोषणा NV50_DISP_OVERLAY_CHANNEL_DMA                 /* cl507e.h */ 0x0000507e
#घोषणा G82_DISP_OVERLAY_CHANNEL_DMA                  /* cl507e.h */ 0x0000827e
#घोषणा GT200_DISP_OVERLAY_CHANNEL_DMA                /* cl507e.h */ 0x0000837e
#घोषणा GT214_DISP_OVERLAY_CHANNEL_DMA                /* cl507e.h */ 0x0000857e
#घोषणा GF110_DISP_OVERLAY_CONTROL_DMA                /* cl507e.h */ 0x0000907e
#घोषणा GK104_DISP_OVERLAY_CONTROL_DMA                /* cl507e.h */ 0x0000917e

#घोषणा GV100_DISP_WINDOW_CHANNEL_DMA                 /* clc37e.h */ 0x0000c37e
#घोषणा TU102_DISP_WINDOW_CHANNEL_DMA                 /* clc37e.h */ 0x0000c57e
#घोषणा GA102_DISP_WINDOW_CHANNEL_DMA                 /* clc37e.h */ 0x0000c67e

#घोषणा NV50_TESLA                                                   0x00005097
#घोषणा G82_TESLA                                                    0x00008297
#घोषणा GT200_TESLA                                                  0x00008397
#घोषणा GT214_TESLA                                                  0x00008597
#घोषणा GT21A_TESLA                                                  0x00008697

#घोषणा FERMI_A                                       /* cl9097.h */ 0x00009097
#घोषणा FERMI_B                                       /* cl9097.h */ 0x00009197
#घोषणा FERMI_C                                       /* cl9097.h */ 0x00009297

#घोषणा KEPLER_A                                      /* cl9097.h */ 0x0000a097
#घोषणा KEPLER_B                                      /* cl9097.h */ 0x0000a197
#घोषणा KEPLER_C                                      /* cl9097.h */ 0x0000a297

#घोषणा MAXWELL_A                                     /* cl9097.h */ 0x0000b097
#घोषणा MAXWELL_B                                     /* cl9097.h */ 0x0000b197

#घोषणा PASCAL_A                                      /* cl9097.h */ 0x0000c097
#घोषणा PASCAL_B                                      /* cl9097.h */ 0x0000c197

#घोषणा VOLTA_A                                       /* cl9097.h */ 0x0000c397

#घोषणा TURING_A                                      /* cl9097.h */ 0x0000c597

#घोषणा NV74_BSP                                                     0x000074b0

#घोषणा GT212_MSVLD                                                  0x000085b1
#घोषणा IGT21A_MSVLD                                                 0x000086b1
#घोषणा G98_MSVLD                                                    0x000088b1
#घोषणा GF100_MSVLD                                                  0x000090b1
#घोषणा GK104_MSVLD                                                  0x000095b1

#घोषणा GT212_MSPDEC                                                 0x000085b2
#घोषणा G98_MSPDEC                                                   0x000088b2
#घोषणा GF100_MSPDEC                                                 0x000090b2
#घोषणा GK104_MSPDEC                                                 0x000095b2

#घोषणा GT212_MSPPP                                                  0x000085b3
#घोषणा G98_MSPPP                                                    0x000088b3
#घोषणा GF100_MSPPP                                                  0x000090b3

#घोषणा G98_SEC                                                      0x000088b4

#घोषणा GT212_DMA                                                    0x000085b5
#घोषणा FERMI_DMA                                                    0x000090b5
#घोषणा KEPLER_DMA_COPY_A                                            0x0000a0b5
#घोषणा MAXWELL_DMA_COPY_A                                           0x0000b0b5
#घोषणा PASCAL_DMA_COPY_A                                            0x0000c0b5
#घोषणा PASCAL_DMA_COPY_B                                            0x0000c1b5
#घोषणा VOLTA_DMA_COPY_A                                             0x0000c3b5
#घोषणा TURING_DMA_COPY_A                                            0x0000c5b5

#घोषणा FERMI_DECOMPRESS                                             0x000090b8

#घोषणा NV50_COMPUTE                                                 0x000050c0
#घोषणा GT214_COMPUTE                                                0x000085c0
#घोषणा FERMI_COMPUTE_A                                              0x000090c0
#घोषणा FERMI_COMPUTE_B                                              0x000091c0
#घोषणा KEPLER_COMPUTE_A                                             0x0000a0c0
#घोषणा KEPLER_COMPUTE_B                                             0x0000a1c0
#घोषणा MAXWELL_COMPUTE_A                                            0x0000b0c0
#घोषणा MAXWELL_COMPUTE_B                                            0x0000b1c0
#घोषणा PASCAL_COMPUTE_A                                             0x0000c0c0
#घोषणा PASCAL_COMPUTE_B                                             0x0000c1c0
#घोषणा VOLTA_COMPUTE_A                                              0x0000c3c0
#घोषणा TURING_COMPUTE_A                                             0x0000c5c0

#घोषणा NV74_CIPHER                                                  0x000074c1
#पूर्ण_अगर
