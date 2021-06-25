<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
#अगर_अघोषित __SOUND_CS46XX_H
#घोषणा __SOUND_CS46XX_H

/*
 *  Copyright (c) by Jaroslav Kysela <perex@perex.cz>,
 *		     Cirrus Logic, Inc.
 *  Definitions क्रम Cirrus Logic CS46xx chips
 */

#समावेश <sound/pcm.h>
#समावेश <sound/pcm-indirect.h>
#समावेश <sound/rawmidi.h>
#समावेश <sound/ac97_codec.h>
#समावेश "cs46xx_dsp_spos.h"

/*
 *  Direct रेजिस्टरs
 */

/*
 *  The following define the offsets of the रेजिस्टरs accessed via base address
 *  रेजिस्टर zero on the CS46xx part.
 */
#घोषणा BA0_HISR				0x00000000
#घोषणा BA0_HSR0                                0x00000004
#घोषणा BA0_HICR                                0x00000008
#घोषणा BA0_DMSR                                0x00000100
#घोषणा BA0_HSAR                                0x00000110
#घोषणा BA0_HDAR                                0x00000114
#घोषणा BA0_HDMR                                0x00000118
#घोषणा BA0_HDCR                                0x0000011C
#घोषणा BA0_PFMC                                0x00000200
#घोषणा BA0_PFCV1                               0x00000204
#घोषणा BA0_PFCV2                               0x00000208
#घोषणा BA0_PCICFG00                            0x00000300
#घोषणा BA0_PCICFG04                            0x00000304
#घोषणा BA0_PCICFG08                            0x00000308
#घोषणा BA0_PCICFG0C                            0x0000030C
#घोषणा BA0_PCICFG10                            0x00000310
#घोषणा BA0_PCICFG14                            0x00000314
#घोषणा BA0_PCICFG18                            0x00000318
#घोषणा BA0_PCICFG1C                            0x0000031C
#घोषणा BA0_PCICFG20                            0x00000320
#घोषणा BA0_PCICFG24                            0x00000324
#घोषणा BA0_PCICFG28                            0x00000328
#घोषणा BA0_PCICFG2C                            0x0000032C
#घोषणा BA0_PCICFG30                            0x00000330
#घोषणा BA0_PCICFG34                            0x00000334
#घोषणा BA0_PCICFG38                            0x00000338
#घोषणा BA0_PCICFG3C                            0x0000033C
#घोषणा BA0_CLKCR1                              0x00000400
#घोषणा BA0_CLKCR2                              0x00000404
#घोषणा BA0_PLLM                                0x00000408
#घोषणा BA0_PLLCC                               0x0000040C
#घोषणा BA0_FRR                                 0x00000410 
#घोषणा BA0_CFL1                                0x00000414
#घोषणा BA0_CFL2                                0x00000418
#घोषणा BA0_SERMC1                              0x00000420
#घोषणा BA0_SERMC2                              0x00000424
#घोषणा BA0_SERC1                               0x00000428
#घोषणा BA0_SERC2                               0x0000042C
#घोषणा BA0_SERC3                               0x00000430
#घोषणा BA0_SERC4                               0x00000434
#घोषणा BA0_SERC5                               0x00000438
#घोषणा BA0_SERBSP                              0x0000043C
#घोषणा BA0_SERBST                              0x00000440
#घोषणा BA0_SERBCM                              0x00000444
#घोषणा BA0_SERBAD                              0x00000448
#घोषणा BA0_SERBCF                              0x0000044C
#घोषणा BA0_SERBWP                              0x00000450
#घोषणा BA0_SERBRP                              0x00000454
#अगर_अघोषित NO_CS4612
#घोषणा BA0_ASER_FADDR                          0x00000458
#पूर्ण_अगर
#घोषणा BA0_ACCTL                               0x00000460
#घोषणा BA0_ACSTS                               0x00000464
#घोषणा BA0_ACOSV                               0x00000468
#घोषणा BA0_ACCAD                               0x0000046C
#घोषणा BA0_ACCDA                               0x00000470
#घोषणा BA0_ACISV                               0x00000474
#घोषणा BA0_ACSAD                               0x00000478
#घोषणा BA0_ACSDA                               0x0000047C
#घोषणा BA0_JSPT                                0x00000480
#घोषणा BA0_JSCTL                               0x00000484
#घोषणा BA0_JSC1                                0x00000488
#घोषणा BA0_JSC2                                0x0000048C
#घोषणा BA0_MIDCR                               0x00000490
#घोषणा BA0_MIDSR                               0x00000494
#घोषणा BA0_MIDWP                               0x00000498
#घोषणा BA0_MIDRP                               0x0000049C
#घोषणा BA0_JSIO                                0x000004A0
#अगर_अघोषित NO_CS4612
#घोषणा BA0_ASER_MASTER                         0x000004A4
#पूर्ण_अगर
#घोषणा BA0_CFGI                                0x000004B0
#घोषणा BA0_SSVID                               0x000004B4
#घोषणा BA0_GPIOR                               0x000004B8
#अगर_अघोषित NO_CS4612
#घोषणा BA0_EGPIODR                             0x000004BC
#घोषणा BA0_EGPIOPTR                            0x000004C0
#घोषणा BA0_EGPIOTR                             0x000004C4
#घोषणा BA0_EGPIOWR                             0x000004C8
#घोषणा BA0_EGPIOSR                             0x000004CC
#घोषणा BA0_SERC6                               0x000004D0
#घोषणा BA0_SERC7                               0x000004D4
#घोषणा BA0_SERACC                              0x000004D8
#घोषणा BA0_ACCTL2                              0x000004E0
#घोषणा BA0_ACSTS2                              0x000004E4
#घोषणा BA0_ACOSV2                              0x000004E8
#घोषणा BA0_ACCAD2                              0x000004EC
#घोषणा BA0_ACCDA2                              0x000004F0
#घोषणा BA0_ACISV2                              0x000004F4
#घोषणा BA0_ACSAD2                              0x000004F8
#घोषणा BA0_ACSDA2                              0x000004FC
#घोषणा BA0_IOTAC0                              0x00000500
#घोषणा BA0_IOTAC1                              0x00000504
#घोषणा BA0_IOTAC2                              0x00000508
#घोषणा BA0_IOTAC3                              0x0000050C
#घोषणा BA0_IOTAC4                              0x00000510
#घोषणा BA0_IOTAC5                              0x00000514
#घोषणा BA0_IOTAC6                              0x00000518
#घोषणा BA0_IOTAC7                              0x0000051C
#घोषणा BA0_IOTAC8                              0x00000520
#घोषणा BA0_IOTAC9                              0x00000524
#घोषणा BA0_IOTAC10                             0x00000528
#घोषणा BA0_IOTAC11                             0x0000052C
#घोषणा BA0_IOTFR0                              0x00000540
#घोषणा BA0_IOTFR1                              0x00000544
#घोषणा BA0_IOTFR2                              0x00000548
#घोषणा BA0_IOTFR3                              0x0000054C
#घोषणा BA0_IOTFR4                              0x00000550
#घोषणा BA0_IOTFR5                              0x00000554
#घोषणा BA0_IOTFR6                              0x00000558
#घोषणा BA0_IOTFR7                              0x0000055C
#घोषणा BA0_IOTFIFO                             0x00000580
#घोषणा BA0_IOTRRD                              0x00000584
#घोषणा BA0_IOTFP                               0x00000588
#घोषणा BA0_IOTCR                               0x0000058C
#घोषणा BA0_DPCID                               0x00000590
#घोषणा BA0_DPCIA                               0x00000594
#घोषणा BA0_DPCIC                               0x00000598
#घोषणा BA0_PCPCIR                              0x00000600
#घोषणा BA0_PCPCIG                              0x00000604
#घोषणा BA0_PCPCIEN                             0x00000608
#घोषणा BA0_EPCIPMC                             0x00000610
#पूर्ण_अगर

/*
 *  The following define the offsets of the रेजिस्टरs and memories accessed via
 *  base address रेजिस्टर one on the CS46xx part.
 */
#घोषणा BA1_SP_DMEM0                            0x00000000
#घोषणा BA1_SP_DMEM1                            0x00010000
#घोषणा BA1_SP_PMEM                             0x00020000
#घोषणा BA1_SP_REG				0x00030000
#घोषणा BA1_SPCR                                0x00030000
#घोषणा BA1_DREG                                0x00030004
#घोषणा BA1_DSRWP                               0x00030008
#घोषणा BA1_TWPR                                0x0003000C
#घोषणा BA1_SPWR                                0x00030010
#घोषणा BA1_SPIR                                0x00030014
#घोषणा BA1_FGR1                                0x00030020
#घोषणा BA1_SPCS                                0x00030028
#घोषणा BA1_SDSR                                0x0003002C
#घोषणा BA1_FRMT                                0x00030030
#घोषणा BA1_FRCC                                0x00030034
#घोषणा BA1_FRSC                                0x00030038
#घोषणा BA1_OMNI_MEM                            0x000E0000


/*
 *  The following defines are क्रम the flags in the host पूर्णांकerrupt status
 *  रेजिस्टर.
 */
#घोषणा HISR_VC_MASK                            0x0000FFFF
#घोषणा HISR_VC0                                0x00000001
#घोषणा HISR_VC1                                0x00000002
#घोषणा HISR_VC2                                0x00000004
#घोषणा HISR_VC3                                0x00000008
#घोषणा HISR_VC4                                0x00000010
#घोषणा HISR_VC5                                0x00000020
#घोषणा HISR_VC6                                0x00000040
#घोषणा HISR_VC7                                0x00000080
#घोषणा HISR_VC8                                0x00000100
#घोषणा HISR_VC9                                0x00000200
#घोषणा HISR_VC10                               0x00000400
#घोषणा HISR_VC11                               0x00000800
#घोषणा HISR_VC12                               0x00001000
#घोषणा HISR_VC13                               0x00002000
#घोषणा HISR_VC14                               0x00004000
#घोषणा HISR_VC15                               0x00008000
#घोषणा HISR_INT0                               0x00010000
#घोषणा HISR_INT1                               0x00020000
#घोषणा HISR_DMAI                               0x00040000
#घोषणा HISR_FROVR                              0x00080000
#घोषणा HISR_MIDI                               0x00100000
#अगर_घोषित NO_CS4612
#घोषणा HISR_RESERVED                           0x0FE00000
#अन्यथा
#घोषणा HISR_SBINT                              0x00200000
#घोषणा HISR_RESERVED                           0x0FC00000
#पूर्ण_अगर
#घोषणा HISR_H0P                                0x40000000
#घोषणा HISR_INTENA                             0x80000000

/*
 *  The following defines are क्रम the flags in the host संकेत रेजिस्टर 0.
 */
#घोषणा HSR0_VC_MASK                            0xFFFFFFFF
#घोषणा HSR0_VC16                               0x00000001
#घोषणा HSR0_VC17                               0x00000002
#घोषणा HSR0_VC18                               0x00000004
#घोषणा HSR0_VC19                               0x00000008
#घोषणा HSR0_VC20                               0x00000010
#घोषणा HSR0_VC21                               0x00000020
#घोषणा HSR0_VC22                               0x00000040
#घोषणा HSR0_VC23                               0x00000080
#घोषणा HSR0_VC24                               0x00000100
#घोषणा HSR0_VC25                               0x00000200
#घोषणा HSR0_VC26                               0x00000400
#घोषणा HSR0_VC27                               0x00000800
#घोषणा HSR0_VC28                               0x00001000
#घोषणा HSR0_VC29                               0x00002000
#घोषणा HSR0_VC30                               0x00004000
#घोषणा HSR0_VC31                               0x00008000
#घोषणा HSR0_VC32                               0x00010000
#घोषणा HSR0_VC33                               0x00020000
#घोषणा HSR0_VC34                               0x00040000
#घोषणा HSR0_VC35                               0x00080000
#घोषणा HSR0_VC36                               0x00100000
#घोषणा HSR0_VC37                               0x00200000
#घोषणा HSR0_VC38                               0x00400000
#घोषणा HSR0_VC39                               0x00800000
#घोषणा HSR0_VC40                               0x01000000
#घोषणा HSR0_VC41                               0x02000000
#घोषणा HSR0_VC42                               0x04000000
#घोषणा HSR0_VC43                               0x08000000
#घोषणा HSR0_VC44                               0x10000000
#घोषणा HSR0_VC45                               0x20000000
#घोषणा HSR0_VC46                               0x40000000
#घोषणा HSR0_VC47                               0x80000000

/*
 *  The following defines are क्रम the flags in the host पूर्णांकerrupt control
 *  रेजिस्टर.
 */
#घोषणा HICR_IEV                                0x00000001
#घोषणा HICR_CHGM                               0x00000002

/*
 *  The following defines are क्रम the flags in the DMA status रेजिस्टर.
 */
#घोषणा DMSR_HP                                 0x00000001
#घोषणा DMSR_HR                                 0x00000002
#घोषणा DMSR_SP                                 0x00000004
#घोषणा DMSR_SR                                 0x00000008

/*
 *  The following defines are क्रम the flags in the host DMA source address
 *  रेजिस्टर.
 */
#घोषणा HSAR_HOST_ADDR_MASK                     0xFFFFFFFF
#घोषणा HSAR_DSP_ADDR_MASK                      0x0000FFFF
#घोषणा HSAR_MEMID_MASK                         0x000F0000
#घोषणा HSAR_MEMID_SP_DMEM0                     0x00000000
#घोषणा HSAR_MEMID_SP_DMEM1                     0x00010000
#घोषणा HSAR_MEMID_SP_PMEM                      0x00020000
#घोषणा HSAR_MEMID_SP_DEBUG                     0x00030000
#घोषणा HSAR_MEMID_OMNI_MEM                     0x000E0000
#घोषणा HSAR_END                                0x40000000
#घोषणा HSAR_ERR                                0x80000000

/*
 *  The following defines are क्रम the flags in the host DMA destination address
 *  रेजिस्टर.
 */
#घोषणा HDAR_HOST_ADDR_MASK                     0xFFFFFFFF
#घोषणा HDAR_DSP_ADDR_MASK                      0x0000FFFF
#घोषणा HDAR_MEMID_MASK                         0x000F0000
#घोषणा HDAR_MEMID_SP_DMEM0                     0x00000000
#घोषणा HDAR_MEMID_SP_DMEM1                     0x00010000
#घोषणा HDAR_MEMID_SP_PMEM                      0x00020000
#घोषणा HDAR_MEMID_SP_DEBUG                     0x00030000
#घोषणा HDAR_MEMID_OMNI_MEM                     0x000E0000
#घोषणा HDAR_END                                0x40000000
#घोषणा HDAR_ERR                                0x80000000

/*
 *  The following defines are क्रम the flags in the host DMA control रेजिस्टर.
 */
#घोषणा HDMR_AC_MASK                            0x0000F000
#घोषणा HDMR_AC_8_16                            0x00001000
#घोषणा HDMR_AC_M_S                             0x00002000
#घोषणा HDMR_AC_B_L                             0x00004000
#घोषणा HDMR_AC_S_U                             0x00008000

/*
 *  The following defines are क्रम the flags in the host DMA control रेजिस्टर.
 */
#घोषणा HDCR_COUNT_MASK                         0x000003FF
#घोषणा HDCR_DONE                               0x00004000
#घोषणा HDCR_OPT                                0x00008000
#घोषणा HDCR_WBD                                0x00400000
#घोषणा HDCR_WBS                                0x00800000
#घोषणा HDCR_DMS_MASK                           0x07000000
#घोषणा HDCR_DMS_LINEAR                         0x00000000
#घोषणा HDCR_DMS_16_DWORDS                      0x01000000
#घोषणा HDCR_DMS_32_DWORDS                      0x02000000
#घोषणा HDCR_DMS_64_DWORDS                      0x03000000
#घोषणा HDCR_DMS_128_DWORDS                     0x04000000
#घोषणा HDCR_DMS_256_DWORDS                     0x05000000
#घोषणा HDCR_DMS_512_DWORDS                     0x06000000
#घोषणा HDCR_DMS_1024_DWORDS                    0x07000000
#घोषणा HDCR_DH                                 0x08000000
#घोषणा HDCR_SMS_MASK                           0x70000000
#घोषणा HDCR_SMS_LINEAR                         0x00000000
#घोषणा HDCR_SMS_16_DWORDS                      0x10000000
#घोषणा HDCR_SMS_32_DWORDS                      0x20000000
#घोषणा HDCR_SMS_64_DWORDS                      0x30000000
#घोषणा HDCR_SMS_128_DWORDS                     0x40000000
#घोषणा HDCR_SMS_256_DWORDS                     0x50000000
#घोषणा HDCR_SMS_512_DWORDS                     0x60000000
#घोषणा HDCR_SMS_1024_DWORDS                    0x70000000
#घोषणा HDCR_SH                                 0x80000000
#घोषणा HDCR_COUNT_SHIFT                        0

/*
 *  The following defines are क्रम the flags in the perक्रमmance monitor control
 *  रेजिस्टर.
 */
#घोषणा PFMC_C1SS_MASK                          0x0000001F
#घोषणा PFMC_C1EV                               0x00000020
#घोषणा PFMC_C1RS                               0x00008000
#घोषणा PFMC_C2SS_MASK                          0x001F0000
#घोषणा PFMC_C2EV                               0x00200000
#घोषणा PFMC_C2RS                               0x80000000
#घोषणा PFMC_C1SS_SHIFT                         0
#घोषणा PFMC_C2SS_SHIFT                         16
#घोषणा PFMC_BUS_GRANT                          0
#घोषणा PFMC_GRANT_AFTER_REQ                    1
#घोषणा PFMC_TRANSACTION                        2
#घोषणा PFMC_DWORD_TRANSFER                     3
#घोषणा PFMC_SLAVE_READ                         4
#घोषणा PFMC_SLAVE_WRITE                        5
#घोषणा PFMC_PREEMPTION                         6
#घोषणा PFMC_DISCONNECT_RETRY                   7
#घोषणा PFMC_INTERRUPT                          8
#घोषणा PFMC_BUS_OWNERSHIP                      9
#घोषणा PFMC_TRANSACTION_LAG                    10
#घोषणा PFMC_PCI_CLOCK                          11
#घोषणा PFMC_SERIAL_CLOCK                       12
#घोषणा PFMC_SP_CLOCK                           13

/*
 *  The following defines are क्रम the flags in the perक्रमmance counter value 1
 *  रेजिस्टर.
 */
#घोषणा PFCV1_PC1V_MASK                         0xFFFFFFFF
#घोषणा PFCV1_PC1V_SHIFT                        0

/*
 *  The following defines are क्रम the flags in the perक्रमmance counter value 2
 *  रेजिस्टर.
 */
#घोषणा PFCV2_PC2V_MASK                         0xFFFFFFFF
#घोषणा PFCV2_PC2V_SHIFT                        0

/*
 *  The following defines are क्रम the flags in the घड़ी control रेजिस्टर 1.
 */
#घोषणा CLKCR1_OSCS                             0x00000001
#घोषणा CLKCR1_OSCP                             0x00000002
#घोषणा CLKCR1_PLLSS_MASK                       0x0000000C
#घोषणा CLKCR1_PLLSS_SERIAL                     0x00000000
#घोषणा CLKCR1_PLLSS_CRYSTAL                    0x00000004
#घोषणा CLKCR1_PLLSS_PCI                        0x00000008
#घोषणा CLKCR1_PLLSS_RESERVED                   0x0000000C
#घोषणा CLKCR1_PLLP                             0x00000010
#घोषणा CLKCR1_SWCE                             0x00000020
#घोषणा CLKCR1_PLLOS                            0x00000040

/*
 *  The following defines are क्रम the flags in the घड़ी control रेजिस्टर 2.
 */
#घोषणा CLKCR2_PDIVS_MASK                       0x0000000F
#घोषणा CLKCR2_PDIVS_1                          0x00000001
#घोषणा CLKCR2_PDIVS_2                          0x00000002
#घोषणा CLKCR2_PDIVS_4                          0x00000004
#घोषणा CLKCR2_PDIVS_7                          0x00000007
#घोषणा CLKCR2_PDIVS_8                          0x00000008
#घोषणा CLKCR2_PDIVS_16                         0x00000000

/*
 *  The following defines are क्रम the flags in the PLL multiplier रेजिस्टर.
 */
#घोषणा PLLM_MASK                               0x000000FF
#घोषणा PLLM_SHIFT                              0

/*
 *  The following defines are क्रम the flags in the PLL capacitor coefficient
 *  रेजिस्टर.
 */
#घोषणा PLLCC_CDR_MASK                          0x00000007
#अगर_अघोषित NO_CS4610
#घोषणा PLLCC_CDR_240_350_MHZ                   0x00000000
#घोषणा PLLCC_CDR_184_265_MHZ                   0x00000001
#घोषणा PLLCC_CDR_144_205_MHZ                   0x00000002
#घोषणा PLLCC_CDR_111_160_MHZ                   0x00000003
#घोषणा PLLCC_CDR_87_123_MHZ                    0x00000004
#घोषणा PLLCC_CDR_67_96_MHZ                     0x00000005
#घोषणा PLLCC_CDR_52_74_MHZ                     0x00000006
#घोषणा PLLCC_CDR_45_58_MHZ                     0x00000007
#पूर्ण_अगर
#अगर_अघोषित NO_CS4612
#घोषणा PLLCC_CDR_271_398_MHZ                   0x00000000
#घोषणा PLLCC_CDR_227_330_MHZ                   0x00000001
#घोषणा PLLCC_CDR_167_239_MHZ                   0x00000002
#घोषणा PLLCC_CDR_150_215_MHZ                   0x00000003
#घोषणा PLLCC_CDR_107_154_MHZ                   0x00000004
#घोषणा PLLCC_CDR_98_140_MHZ                    0x00000005
#घोषणा PLLCC_CDR_73_104_MHZ                    0x00000006
#घोषणा PLLCC_CDR_63_90_MHZ                     0x00000007
#पूर्ण_अगर
#घोषणा PLLCC_LPF_MASK                          0x000000F8
#अगर_अघोषित NO_CS4610
#घोषणा PLLCC_LPF_23850_60000_KHZ               0x00000000
#घोषणा PLLCC_LPF_7960_26290_KHZ                0x00000008
#घोषणा PLLCC_LPF_4160_10980_KHZ                0x00000018
#घोषणा PLLCC_LPF_1740_4580_KHZ                 0x00000038
#घोषणा PLLCC_LPF_724_1910_KHZ                  0x00000078
#घोषणा PLLCC_LPF_317_798_KHZ                   0x000000F8
#पूर्ण_अगर
#अगर_अघोषित NO_CS4612
#घोषणा PLLCC_LPF_25580_64530_KHZ               0x00000000
#घोषणा PLLCC_LPF_14360_37270_KHZ               0x00000008
#घोषणा PLLCC_LPF_6100_16020_KHZ                0x00000018
#घोषणा PLLCC_LPF_2540_6690_KHZ                 0x00000038
#घोषणा PLLCC_LPF_1050_2780_KHZ                 0x00000078
#घोषणा PLLCC_LPF_450_1160_KHZ                  0x000000F8
#पूर्ण_अगर

/*
 *  The following defines are क्रम the flags in the feature reporting रेजिस्टर.
 */
#घोषणा FRR_FAB_MASK                            0x00000003
#घोषणा FRR_MASK_MASK                           0x0000001C
#अगर_घोषित NO_CS4612
#घोषणा FRR_CFOP_MASK                           0x000000E0
#अन्यथा
#घोषणा FRR_CFOP_MASK                           0x00000FE0
#पूर्ण_अगर
#घोषणा FRR_CFOP_NOT_DVD                        0x00000020
#घोषणा FRR_CFOP_A3D                            0x00000040
#घोषणा FRR_CFOP_128_PIN                        0x00000080
#अगर_अघोषित NO_CS4612
#घोषणा FRR_CFOP_CS4280                         0x00000800
#पूर्ण_अगर
#घोषणा FRR_FAB_SHIFT                           0
#घोषणा FRR_MASK_SHIFT                          2
#घोषणा FRR_CFOP_SHIFT                          5

/*
 *  The following defines are क्रम the flags in the configuration load 1
 *  रेजिस्टर.
 */
#घोषणा CFL1_CLOCK_SOURCE_MASK                  0x00000003
#घोषणा CFL1_CLOCK_SOURCE_CS423X                0x00000000
#घोषणा CFL1_CLOCK_SOURCE_AC97                  0x00000001
#घोषणा CFL1_CLOCK_SOURCE_CRYSTAL               0x00000002
#घोषणा CFL1_CLOCK_SOURCE_DUAL_AC97             0x00000003
#घोषणा CFL1_VALID_DATA_MASK                    0x000000FF

/*
 *  The following defines are क्रम the flags in the configuration load 2
 *  रेजिस्टर.
 */
#घोषणा CFL2_VALID_DATA_MASK                    0x000000FF

/*
 *  The following defines are क्रम the flags in the serial port master control
 *  रेजिस्टर 1.
 */
#घोषणा SERMC1_MSPE                             0x00000001
#घोषणा SERMC1_PTC_MASK                         0x0000000E
#घोषणा SERMC1_PTC_CS423X                       0x00000000
#घोषणा SERMC1_PTC_AC97                         0x00000002
#घोषणा SERMC1_PTC_DAC                          0x00000004
#घोषणा SERMC1_PLB                              0x00000010
#घोषणा SERMC1_XLB                              0x00000020

/*
 *  The following defines are क्रम the flags in the serial port master control
 *  रेजिस्टर 2.
 */
#घोषणा SERMC2_LROE                             0x00000001
#घोषणा SERMC2_MCOE                             0x00000002
#घोषणा SERMC2_MCDIV                            0x00000004

/*
 *  The following defines are क्रम the flags in the serial port 1 configuration
 *  रेजिस्टर.
 */
#घोषणा SERC1_SO1EN                             0x00000001
#घोषणा SERC1_SO1F_MASK                         0x0000000E
#घोषणा SERC1_SO1F_CS423X                       0x00000000
#घोषणा SERC1_SO1F_AC97                         0x00000002
#घोषणा SERC1_SO1F_DAC                          0x00000004
#घोषणा SERC1_SO1F_SPDIF                        0x00000006

/*
 *  The following defines are क्रम the flags in the serial port 2 configuration
 *  रेजिस्टर.
 */
#घोषणा SERC2_SI1EN                             0x00000001
#घोषणा SERC2_SI1F_MASK                         0x0000000E
#घोषणा SERC2_SI1F_CS423X                       0x00000000
#घोषणा SERC2_SI1F_AC97                         0x00000002
#घोषणा SERC2_SI1F_ADC                          0x00000004
#घोषणा SERC2_SI1F_SPDIF                        0x00000006

/*
 *  The following defines are क्रम the flags in the serial port 3 configuration
 *  रेजिस्टर.
 */
#घोषणा SERC3_SO2EN                             0x00000001
#घोषणा SERC3_SO2F_MASK                         0x00000006
#घोषणा SERC3_SO2F_DAC                          0x00000000
#घोषणा SERC3_SO2F_SPDIF                        0x00000002

/*
 *  The following defines are क्रम the flags in the serial port 4 configuration
 *  रेजिस्टर.
 */
#घोषणा SERC4_SO3EN                             0x00000001
#घोषणा SERC4_SO3F_MASK                         0x00000006
#घोषणा SERC4_SO3F_DAC                          0x00000000
#घोषणा SERC4_SO3F_SPDIF                        0x00000002

/*
 *  The following defines are क्रम the flags in the serial port 5 configuration
 *  रेजिस्टर.
 */
#घोषणा SERC5_SI2EN                             0x00000001
#घोषणा SERC5_SI2F_MASK                         0x00000006
#घोषणा SERC5_SI2F_ADC                          0x00000000
#घोषणा SERC5_SI2F_SPDIF                        0x00000002

/*
 *  The following defines are क्रम the flags in the serial port backकरोor sample
 *  poपूर्णांकer रेजिस्टर.
 */
#घोषणा SERBSP_FSP_MASK                         0x0000000F
#घोषणा SERBSP_FSP_SHIFT                        0

/*
 *  The following defines are क्रम the flags in the serial port backकरोor status
 *  रेजिस्टर.
 */
#घोषणा SERBST_RRDY                             0x00000001
#घोषणा SERBST_WBSY                             0x00000002

/*
 *  The following defines are क्रम the flags in the serial port backकरोor command
 *  रेजिस्टर.
 */
#घोषणा SERBCM_RDC                              0x00000001
#घोषणा SERBCM_WRC                              0x00000002

/*
 *  The following defines are क्रम the flags in the serial port backकरोor address
 *  रेजिस्टर.
 */
#अगर_घोषित NO_CS4612
#घोषणा SERBAD_FAD_MASK                         0x000000FF
#अन्यथा
#घोषणा SERBAD_FAD_MASK                         0x000001FF
#पूर्ण_अगर
#घोषणा SERBAD_FAD_SHIFT                        0

/*
 *  The following defines are क्रम the flags in the serial port backकरोor
 *  configuration रेजिस्टर.
 */
#घोषणा SERBCF_HBP                              0x00000001

/*
 *  The following defines are क्रम the flags in the serial port backकरोor ग_लिखो
 *  port रेजिस्टर.
 */
#घोषणा SERBWP_FWD_MASK                         0x000FFFFF
#घोषणा SERBWP_FWD_SHIFT                        0

/*
 *  The following defines are क्रम the flags in the serial port backकरोor पढ़ो
 *  port रेजिस्टर.
 */
#घोषणा SERBRP_FRD_MASK                         0x000FFFFF
#घोषणा SERBRP_FRD_SHIFT                        0

/*
 *  The following defines are क्रम the flags in the async FIFO address रेजिस्टर.
 */
#अगर_अघोषित NO_CS4612
#घोषणा ASER_FADDR_A1_MASK                      0x000001FF
#घोषणा ASER_FADDR_EN1                          0x00008000
#घोषणा ASER_FADDR_A2_MASK                      0x01FF0000
#घोषणा ASER_FADDR_EN2                          0x80000000
#घोषणा ASER_FADDR_A1_SHIFT                     0
#घोषणा ASER_FADDR_A2_SHIFT                     16
#पूर्ण_अगर

/*
 *  The following defines are क्रम the flags in the AC97 control रेजिस्टर.
 */
#घोषणा ACCTL_RSTN                              0x00000001
#घोषणा ACCTL_ESYN                              0x00000002
#घोषणा ACCTL_VFRM                              0x00000004
#घोषणा ACCTL_DCV                               0x00000008
#घोषणा ACCTL_CRW                               0x00000010
#घोषणा ACCTL_ASYN                              0x00000020
#अगर_अघोषित NO_CS4612
#घोषणा ACCTL_TC                                0x00000040
#पूर्ण_अगर

/*
 *  The following defines are क्रम the flags in the AC97 status रेजिस्टर.
 */
#घोषणा ACSTS_CRDY                              0x00000001
#घोषणा ACSTS_VSTS                              0x00000002
#अगर_अघोषित NO_CS4612
#घोषणा ACSTS_WKUP                              0x00000004
#पूर्ण_अगर

/*
 *  The following defines are क्रम the flags in the AC97 output slot valid
 *  रेजिस्टर.
 */
#घोषणा ACOSV_SLV3                              0x00000001
#घोषणा ACOSV_SLV4                              0x00000002
#घोषणा ACOSV_SLV5                              0x00000004
#घोषणा ACOSV_SLV6                              0x00000008
#घोषणा ACOSV_SLV7                              0x00000010
#घोषणा ACOSV_SLV8                              0x00000020
#घोषणा ACOSV_SLV9                              0x00000040
#घोषणा ACOSV_SLV10                             0x00000080
#घोषणा ACOSV_SLV11                             0x00000100
#घोषणा ACOSV_SLV12                             0x00000200

/*
 *  The following defines are क्रम the flags in the AC97 command address
 *  रेजिस्टर.
 */
#घोषणा ACCAD_CI_MASK                           0x0000007F
#घोषणा ACCAD_CI_SHIFT                          0

/*
 *  The following defines are क्रम the flags in the AC97 command data रेजिस्टर.
 */
#घोषणा ACCDA_CD_MASK                           0x0000FFFF
#घोषणा ACCDA_CD_SHIFT                          0

/*
 *  The following defines are क्रम the flags in the AC97 input slot valid
 *  रेजिस्टर.
 */
#घोषणा ACISV_ISV3                              0x00000001
#घोषणा ACISV_ISV4                              0x00000002
#घोषणा ACISV_ISV5                              0x00000004
#घोषणा ACISV_ISV6                              0x00000008
#घोषणा ACISV_ISV7                              0x00000010
#घोषणा ACISV_ISV8                              0x00000020
#घोषणा ACISV_ISV9                              0x00000040
#घोषणा ACISV_ISV10                             0x00000080
#घोषणा ACISV_ISV11                             0x00000100
#घोषणा ACISV_ISV12                             0x00000200

/*
 *  The following defines are क्रम the flags in the AC97 status address
 *  रेजिस्टर.
 */
#घोषणा ACSAD_SI_MASK                           0x0000007F
#घोषणा ACSAD_SI_SHIFT                          0

/*
 *  The following defines are क्रम the flags in the AC97 status data रेजिस्टर.
 */
#घोषणा ACSDA_SD_MASK                           0x0000FFFF
#घोषणा ACSDA_SD_SHIFT                          0

/*
 *  The following defines are क्रम the flags in the joystick poll/trigger
 *  रेजिस्टर.
 */
#घोषणा JSPT_CAX                                0x00000001
#घोषणा JSPT_CAY                                0x00000002
#घोषणा JSPT_CBX                                0x00000004
#घोषणा JSPT_CBY                                0x00000008
#घोषणा JSPT_BA1                                0x00000010
#घोषणा JSPT_BA2                                0x00000020
#घोषणा JSPT_BB1                                0x00000040
#घोषणा JSPT_BB2                                0x00000080

/*
 *  The following defines are क्रम the flags in the joystick control रेजिस्टर.
 */
#घोषणा JSCTL_SP_MASK                           0x00000003
#घोषणा JSCTL_SP_SLOW                           0x00000000
#घोषणा JSCTL_SP_MEDIUM_SLOW                    0x00000001
#घोषणा JSCTL_SP_MEDIUM_FAST                    0x00000002
#घोषणा JSCTL_SP_FAST                           0x00000003
#घोषणा JSCTL_ARE                               0x00000004

/*
 *  The following defines are क्रम the flags in the joystick coordinate pair 1
 *  पढ़ोback रेजिस्टर.
 */
#घोषणा JSC1_Y1V_MASK                           0x0000FFFF
#घोषणा JSC1_X1V_MASK                           0xFFFF0000
#घोषणा JSC1_Y1V_SHIFT                          0
#घोषणा JSC1_X1V_SHIFT                          16

/*
 *  The following defines are क्रम the flags in the joystick coordinate pair 2
 *  पढ़ोback रेजिस्टर.
 */
#घोषणा JSC2_Y2V_MASK                           0x0000FFFF
#घोषणा JSC2_X2V_MASK                           0xFFFF0000
#घोषणा JSC2_Y2V_SHIFT                          0
#घोषणा JSC2_X2V_SHIFT                          16

/*
 *  The following defines are क्रम the flags in the MIDI control रेजिस्टर.
 */
#घोषणा MIDCR_TXE                               0x00000001	/* Enable transmitting. */
#घोषणा MIDCR_RXE                               0x00000002	/* Enable receiving. */
#घोषणा MIDCR_RIE                               0x00000004	/* Interrupt upon tx पढ़ोy. */
#घोषणा MIDCR_TIE                               0x00000008	/* Interrupt upon rx पढ़ोy. */
#घोषणा MIDCR_MLB                               0x00000010	/* Enable midi loopback. */
#घोषणा MIDCR_MRST                              0x00000020	/* Reset पूर्णांकerface. */

/*
 *  The following defines are क्रम the flags in the MIDI status रेजिस्टर.
 */
#घोषणा MIDSR_TBF                               0x00000001	/* Tx FIFO is full. */
#घोषणा MIDSR_RBE                               0x00000002	/* Rx FIFO is empty. */

/*
 *  The following defines are क्रम the flags in the MIDI ग_लिखो port रेजिस्टर.
 */
#घोषणा MIDWP_MWD_MASK                          0x000000FF
#घोषणा MIDWP_MWD_SHIFT                         0

/*
 *  The following defines are क्रम the flags in the MIDI पढ़ो port रेजिस्टर.
 */
#घोषणा MIDRP_MRD_MASK                          0x000000FF
#घोषणा MIDRP_MRD_SHIFT                         0

/*
 *  The following defines are क्रम the flags in the joystick GPIO रेजिस्टर.
 */
#घोषणा JSIO_DAX                                0x00000001
#घोषणा JSIO_DAY                                0x00000002
#घोषणा JSIO_DBX                                0x00000004
#घोषणा JSIO_DBY                                0x00000008
#घोषणा JSIO_AXOE                               0x00000010
#घोषणा JSIO_AYOE                               0x00000020
#घोषणा JSIO_BXOE                               0x00000040
#घोषणा JSIO_BYOE                               0x00000080

/*
 *  The following defines are क्रम the flags in the master async/sync serial
 *  port enable रेजिस्टर.
 */
#अगर_अघोषित NO_CS4612
#घोषणा ASER_MASTER_ME                          0x00000001
#पूर्ण_अगर

/*
 *  The following defines are क्रम the flags in the configuration पूर्णांकerface
 *  रेजिस्टर.
 */
#घोषणा CFGI_CLK                                0x00000001
#घोषणा CFGI_DOUT                               0x00000002
#घोषणा CFGI_DIN_EEN                            0x00000004
#घोषणा CFGI_EELD                               0x00000008

/*
 *  The following defines are क्रम the flags in the subप्रणाली ID and venकरोr ID
 *  रेजिस्टर.
 */
#घोषणा SSVID_VID_MASK                          0x0000FFFF
#घोषणा SSVID_SID_MASK                          0xFFFF0000
#घोषणा SSVID_VID_SHIFT                         0
#घोषणा SSVID_SID_SHIFT                         16

/*
 *  The following defines are क्रम the flags in the GPIO pin पूर्णांकerface रेजिस्टर.
 */
#घोषणा GPIOR_VOLDN                             0x00000001
#घोषणा GPIOR_VOLUP                             0x00000002
#घोषणा GPIOR_SI2D                              0x00000004
#घोषणा GPIOR_SI2OE                             0x00000008

/*
 *  The following defines are क्रम the flags in the extended GPIO pin direction
 *  रेजिस्टर.
 */
#अगर_अघोषित NO_CS4612
#घोषणा EGPIODR_GPOE0                           0x00000001
#घोषणा EGPIODR_GPOE1                           0x00000002
#घोषणा EGPIODR_GPOE2                           0x00000004
#घोषणा EGPIODR_GPOE3                           0x00000008
#घोषणा EGPIODR_GPOE4                           0x00000010
#घोषणा EGPIODR_GPOE5                           0x00000020
#घोषणा EGPIODR_GPOE6                           0x00000040
#घोषणा EGPIODR_GPOE7                           0x00000080
#घोषणा EGPIODR_GPOE8                           0x00000100
#पूर्ण_अगर

/*
 *  The following defines are क्रम the flags in the extended GPIO pin polarity/
 *  type रेजिस्टर.
 */
#अगर_अघोषित NO_CS4612
#घोषणा EGPIOPTR_GPPT0                          0x00000001
#घोषणा EGPIOPTR_GPPT1                          0x00000002
#घोषणा EGPIOPTR_GPPT2                          0x00000004
#घोषणा EGPIOPTR_GPPT3                          0x00000008
#घोषणा EGPIOPTR_GPPT4                          0x00000010
#घोषणा EGPIOPTR_GPPT5                          0x00000020
#घोषणा EGPIOPTR_GPPT6                          0x00000040
#घोषणा EGPIOPTR_GPPT7                          0x00000080
#घोषणा EGPIOPTR_GPPT8                          0x00000100
#पूर्ण_अगर

/*
 *  The following defines are क्रम the flags in the extended GPIO pin sticky
 *  रेजिस्टर.
 */
#अगर_अघोषित NO_CS4612
#घोषणा EGPIOTR_GPS0                            0x00000001
#घोषणा EGPIOTR_GPS1                            0x00000002
#घोषणा EGPIOTR_GPS2                            0x00000004
#घोषणा EGPIOTR_GPS3                            0x00000008
#घोषणा EGPIOTR_GPS4                            0x00000010
#घोषणा EGPIOTR_GPS5                            0x00000020
#घोषणा EGPIOTR_GPS6                            0x00000040
#घोषणा EGPIOTR_GPS7                            0x00000080
#घोषणा EGPIOTR_GPS8                            0x00000100
#पूर्ण_अगर

/*
 *  The following defines are क्रम the flags in the extended GPIO ping wakeup
 *  रेजिस्टर.
 */
#अगर_अघोषित NO_CS4612
#घोषणा EGPIOWR_GPW0                            0x00000001
#घोषणा EGPIOWR_GPW1                            0x00000002
#घोषणा EGPIOWR_GPW2                            0x00000004
#घोषणा EGPIOWR_GPW3                            0x00000008
#घोषणा EGPIOWR_GPW4                            0x00000010
#घोषणा EGPIOWR_GPW5                            0x00000020
#घोषणा EGPIOWR_GPW6                            0x00000040
#घोषणा EGPIOWR_GPW7                            0x00000080
#घोषणा EGPIOWR_GPW8                            0x00000100
#पूर्ण_अगर

/*
 *  The following defines are क्रम the flags in the extended GPIO pin status
 *  रेजिस्टर.
 */
#अगर_अघोषित NO_CS4612
#घोषणा EGPIOSR_GPS0                            0x00000001
#घोषणा EGPIOSR_GPS1                            0x00000002
#घोषणा EGPIOSR_GPS2                            0x00000004
#घोषणा EGPIOSR_GPS3                            0x00000008
#घोषणा EGPIOSR_GPS4                            0x00000010
#घोषणा EGPIOSR_GPS5                            0x00000020
#घोषणा EGPIOSR_GPS6                            0x00000040
#घोषणा EGPIOSR_GPS7                            0x00000080
#घोषणा EGPIOSR_GPS8                            0x00000100
#पूर्ण_अगर

/*
 *  The following defines are क्रम the flags in the serial port 6 configuration
 *  रेजिस्टर.
 */
#अगर_अघोषित NO_CS4612
#घोषणा SERC6_ASDO2EN                           0x00000001
#पूर्ण_अगर

/*
 *  The following defines are क्रम the flags in the serial port 7 configuration
 *  रेजिस्टर.
 */
#अगर_अघोषित NO_CS4612
#घोषणा SERC7_ASDI2EN                           0x00000001
#घोषणा SERC7_POSILB                            0x00000002
#घोषणा SERC7_SIPOLB                            0x00000004
#घोषणा SERC7_SOSILB                            0x00000008
#घोषणा SERC7_SISOLB                            0x00000010
#पूर्ण_अगर

/*
 *  The following defines are क्रम the flags in the serial port AC link
 *  configuration रेजिस्टर.
 */
#अगर_अघोषित NO_CS4612
#घोषणा SERACC_CHIP_TYPE_MASK                  0x00000001
#घोषणा SERACC_CHIP_TYPE_1_03                  0x00000000
#घोषणा SERACC_CHIP_TYPE_2_0                   0x00000001
#घोषणा SERACC_TWO_CODECS                      0x00000002
#घोषणा SERACC_MDM                             0x00000004
#घोषणा SERACC_HSP                             0x00000008
#घोषणा SERACC_ODT                             0x00000010 /* only CS4630 */
#पूर्ण_अगर

/*
 *  The following defines are क्रम the flags in the AC97 control रेजिस्टर 2.
 */
#अगर_अघोषित NO_CS4612
#घोषणा ACCTL2_RSTN                             0x00000001
#घोषणा ACCTL2_ESYN                             0x00000002
#घोषणा ACCTL2_VFRM                             0x00000004
#घोषणा ACCTL2_DCV                              0x00000008
#घोषणा ACCTL2_CRW                              0x00000010
#घोषणा ACCTL2_ASYN                             0x00000020
#पूर्ण_अगर

/*
 *  The following defines are क्रम the flags in the AC97 status रेजिस्टर 2.
 */
#अगर_अघोषित NO_CS4612
#घोषणा ACSTS2_CRDY                             0x00000001
#घोषणा ACSTS2_VSTS                             0x00000002
#पूर्ण_अगर

/*
 *  The following defines are क्रम the flags in the AC97 output slot valid
 *  रेजिस्टर 2.
 */
#अगर_अघोषित NO_CS4612
#घोषणा ACOSV2_SLV3                             0x00000001
#घोषणा ACOSV2_SLV4                             0x00000002
#घोषणा ACOSV2_SLV5                             0x00000004
#घोषणा ACOSV2_SLV6                             0x00000008
#घोषणा ACOSV2_SLV7                             0x00000010
#घोषणा ACOSV2_SLV8                             0x00000020
#घोषणा ACOSV2_SLV9                             0x00000040
#घोषणा ACOSV2_SLV10                            0x00000080
#घोषणा ACOSV2_SLV11                            0x00000100
#घोषणा ACOSV2_SLV12                            0x00000200
#पूर्ण_अगर

/*
 *  The following defines are क्रम the flags in the AC97 command address
 *  रेजिस्टर 2.
 */
#अगर_अघोषित NO_CS4612
#घोषणा ACCAD2_CI_MASK                          0x0000007F
#घोषणा ACCAD2_CI_SHIFT                         0
#पूर्ण_अगर

/*
 *  The following defines are क्रम the flags in the AC97 command data रेजिस्टर
 *  2.
 */
#अगर_अघोषित NO_CS4612
#घोषणा ACCDA2_CD_MASK                          0x0000FFFF
#घोषणा ACCDA2_CD_SHIFT                         0  
#पूर्ण_अगर

/*
 *  The following defines are क्रम the flags in the AC97 input slot valid
 *  रेजिस्टर 2.
 */
#अगर_अघोषित NO_CS4612
#घोषणा ACISV2_ISV3                             0x00000001
#घोषणा ACISV2_ISV4                             0x00000002
#घोषणा ACISV2_ISV5                             0x00000004
#घोषणा ACISV2_ISV6                             0x00000008
#घोषणा ACISV2_ISV7                             0x00000010
#घोषणा ACISV2_ISV8                             0x00000020
#घोषणा ACISV2_ISV9                             0x00000040
#घोषणा ACISV2_ISV10                            0x00000080
#घोषणा ACISV2_ISV11                            0x00000100
#घोषणा ACISV2_ISV12                            0x00000200
#पूर्ण_अगर

/*
 *  The following defines are क्रम the flags in the AC97 status address
 *  रेजिस्टर 2.
 */
#अगर_अघोषित NO_CS4612
#घोषणा ACSAD2_SI_MASK                          0x0000007F
#घोषणा ACSAD2_SI_SHIFT                         0
#पूर्ण_अगर

/*
 *  The following defines are क्रम the flags in the AC97 status data रेजिस्टर 2.
 */
#अगर_अघोषित NO_CS4612
#घोषणा ACSDA2_SD_MASK                          0x0000FFFF
#घोषणा ACSDA2_SD_SHIFT                         0
#पूर्ण_अगर

/*
 *  The following defines are क्रम the flags in the I/O trap address and control
 *  रेजिस्टरs (all 12).
 */
#अगर_अघोषित NO_CS4612
#घोषणा IOTAC_SA_MASK                           0x0000FFFF
#घोषणा IOTAC_MSK_MASK                          0x000F0000
#घोषणा IOTAC_IODC_MASK                         0x06000000
#घोषणा IOTAC_IODC_16_BIT                       0x00000000
#घोषणा IOTAC_IODC_10_BIT                       0x02000000
#घोषणा IOTAC_IODC_12_BIT                       0x04000000
#घोषणा IOTAC_WSPI                              0x08000000
#घोषणा IOTAC_RSPI                              0x10000000
#घोषणा IOTAC_WSE                               0x20000000
#घोषणा IOTAC_WE                                0x40000000
#घोषणा IOTAC_RE                                0x80000000
#घोषणा IOTAC_SA_SHIFT                          0
#घोषणा IOTAC_MSK_SHIFT                         16
#पूर्ण_अगर

/*
 *  The following defines are क्रम the flags in the I/O trap fast पढ़ो रेजिस्टरs
 *  (all 8).
 */
#अगर_अघोषित NO_CS4612
#घोषणा IOTFR_D_MASK                            0x0000FFFF
#घोषणा IOTFR_A_MASK                            0x000F0000
#घोषणा IOTFR_R_MASK                            0x0F000000
#घोषणा IOTFR_ALL                               0x40000000
#घोषणा IOTFR_VL                                0x80000000
#घोषणा IOTFR_D_SHIFT                           0
#घोषणा IOTFR_A_SHIFT                           16
#घोषणा IOTFR_R_SHIFT                           24
#पूर्ण_अगर

/*
 *  The following defines are क्रम the flags in the I/O trap FIFO रेजिस्टर.
 */
#अगर_अघोषित NO_CS4612
#घोषणा IOTFIFO_BA_MASK                         0x00003FFF
#घोषणा IOTFIFO_S_MASK                          0x00FF0000
#घोषणा IOTFIFO_OF                              0x40000000
#घोषणा IOTFIFO_SPIOF                           0x80000000
#घोषणा IOTFIFO_BA_SHIFT                        0
#घोषणा IOTFIFO_S_SHIFT                         16
#पूर्ण_अगर

/*
 *  The following defines are क्रम the flags in the I/O trap retry पढ़ो data
 *  रेजिस्टर.
 */
#अगर_अघोषित NO_CS4612
#घोषणा IOTRRD_D_MASK                           0x0000FFFF
#घोषणा IOTRRD_RDV                              0x80000000
#घोषणा IOTRRD_D_SHIFT                          0
#पूर्ण_अगर

/*
 *  The following defines are क्रम the flags in the I/O trap FIFO poपूर्णांकer
 *  रेजिस्टर.
 */
#अगर_अघोषित NO_CS4612
#घोषणा IOTFP_CA_MASK                           0x00003FFF
#घोषणा IOTFP_PA_MASK                           0x3FFF0000
#घोषणा IOTFP_CA_SHIFT                          0
#घोषणा IOTFP_PA_SHIFT                          16
#पूर्ण_अगर

/*
 *  The following defines are क्रम the flags in the I/O trap control रेजिस्टर.
 */
#अगर_अघोषित NO_CS4612
#घोषणा IOTCR_ITD                               0x00000001
#घोषणा IOTCR_HRV                               0x00000002
#घोषणा IOTCR_SRV                               0x00000004
#घोषणा IOTCR_DTI                               0x00000008
#घोषणा IOTCR_DFI                               0x00000010
#घोषणा IOTCR_DDP                               0x00000020
#घोषणा IOTCR_JTE                               0x00000040
#घोषणा IOTCR_PPE                               0x00000080
#पूर्ण_अगर

/*
 *  The following defines are क्रम the flags in the direct PCI data रेजिस्टर.
 */
#अगर_अघोषित NO_CS4612
#घोषणा DPCID_D_MASK                            0xFFFFFFFF
#घोषणा DPCID_D_SHIFT                           0
#पूर्ण_अगर

/*
 *  The following defines are क्रम the flags in the direct PCI address रेजिस्टर.
 */
#अगर_अघोषित NO_CS4612
#घोषणा DPCIA_A_MASK                            0xFFFFFFFF
#घोषणा DPCIA_A_SHIFT                           0
#पूर्ण_अगर

/*
 *  The following defines are क्रम the flags in the direct PCI command रेजिस्टर.
 */
#अगर_अघोषित NO_CS4612
#घोषणा DPCIC_C_MASK                            0x0000000F
#घोषणा DPCIC_C_IOREAD                          0x00000002
#घोषणा DPCIC_C_IOWRITE                         0x00000003
#घोषणा DPCIC_BE_MASK                           0x000000F0
#पूर्ण_अगर

/*
 *  The following defines are क्रम the flags in the PC/PCI request रेजिस्टर.
 */
#अगर_अघोषित NO_CS4612
#घोषणा PCPCIR_RDC_MASK                         0x00000007
#घोषणा PCPCIR_C_MASK                           0x00007000
#घोषणा PCPCIR_REQ                              0x00008000
#घोषणा PCPCIR_RDC_SHIFT                        0
#घोषणा PCPCIR_C_SHIFT                          12
#पूर्ण_अगर

/*
 *  The following defines are क्रम the flags in the PC/PCI grant रेजिस्टर.
 */ 
#अगर_अघोषित NO_CS4612
#घोषणा PCPCIG_GDC_MASK                         0x00000007
#घोषणा PCPCIG_VL                               0x00008000
#घोषणा PCPCIG_GDC_SHIFT                        0
#पूर्ण_अगर

/*
 *  The following defines are क्रम the flags in the PC/PCI master enable
 *  रेजिस्टर.
 */
#अगर_अघोषित NO_CS4612
#घोषणा PCPCIEN_EN                              0x00000001
#पूर्ण_अगर

/*
 *  The following defines are क्रम the flags in the extended PCI घातer
 *  management control रेजिस्टर.
 */
#अगर_अघोषित NO_CS4612
#घोषणा EPCIPMC_GWU                             0x00000001
#घोषणा EPCIPMC_FSPC                            0x00000002
#पूर्ण_अगर 

/*
 *  The following defines are क्रम the flags in the SP control रेजिस्टर.
 */
#घोषणा SPCR_RUN                                0x00000001
#घोषणा SPCR_STPFR                              0x00000002
#घोषणा SPCR_RUNFR                              0x00000004
#घोषणा SPCR_TICK                               0x00000008
#घोषणा SPCR_DRQEN                              0x00000020
#घोषणा SPCR_RSTSP                              0x00000040
#घोषणा SPCR_OREN                               0x00000080
#अगर_अघोषित NO_CS4612
#घोषणा SPCR_PCIINT                             0x00000100
#घोषणा SPCR_OINTD                              0x00000200
#घोषणा SPCR_CRE                                0x00008000
#पूर्ण_अगर

/*
 *  The following defines are क्रम the flags in the debug index रेजिस्टर.
 */
#घोषणा DREG_REGID_MASK                         0x0000007F
#घोषणा DREG_DEBUG                              0x00000080
#घोषणा DREG_RGBK_MASK                          0x00000700
#घोषणा DREG_TRAP                               0x00000800
#अगर !defined(NO_CS4612)
#अगर !defined(NO_CS4615)
#घोषणा DREG_TRAPX                              0x00001000
#पूर्ण_अगर
#पूर्ण_अगर
#घोषणा DREG_REGID_SHIFT                        0
#घोषणा DREG_RGBK_SHIFT                         8
#घोषणा DREG_RGBK_REGID_MASK                    0x0000077F
#घोषणा DREG_REGID_R0                           0x00000010
#घोषणा DREG_REGID_R1                           0x00000011
#घोषणा DREG_REGID_R2                           0x00000012
#घोषणा DREG_REGID_R3                           0x00000013
#घोषणा DREG_REGID_R4                           0x00000014
#घोषणा DREG_REGID_R5                           0x00000015
#घोषणा DREG_REGID_R6                           0x00000016
#घोषणा DREG_REGID_R7                           0x00000017
#घोषणा DREG_REGID_R8                           0x00000018
#घोषणा DREG_REGID_R9                           0x00000019
#घोषणा DREG_REGID_RA                           0x0000001A
#घोषणा DREG_REGID_RB                           0x0000001B
#घोषणा DREG_REGID_RC                           0x0000001C
#घोषणा DREG_REGID_RD                           0x0000001D
#घोषणा DREG_REGID_RE                           0x0000001E
#घोषणा DREG_REGID_RF                           0x0000001F
#घोषणा DREG_REGID_RA_BUS_LOW                   0x00000020
#घोषणा DREG_REGID_RA_BUS_HIGH                  0x00000038
#घोषणा DREG_REGID_YBUS_LOW                     0x00000050
#घोषणा DREG_REGID_YBUS_HIGH                    0x00000058
#घोषणा DREG_REGID_TRAP_0                       0x00000100
#घोषणा DREG_REGID_TRAP_1                       0x00000101
#घोषणा DREG_REGID_TRAP_2                       0x00000102
#घोषणा DREG_REGID_TRAP_3                       0x00000103
#घोषणा DREG_REGID_TRAP_4                       0x00000104
#घोषणा DREG_REGID_TRAP_5                       0x00000105
#घोषणा DREG_REGID_TRAP_6                       0x00000106
#घोषणा DREG_REGID_TRAP_7                       0x00000107
#घोषणा DREG_REGID_INसूचीECT_ADDRESS             0x0000010E
#घोषणा DREG_REGID_TOP_OF_STACK                 0x0000010F
#अगर !defined(NO_CS4612)
#अगर !defined(NO_CS4615)
#घोषणा DREG_REGID_TRAP_8                       0x00000110
#घोषणा DREG_REGID_TRAP_9                       0x00000111
#घोषणा DREG_REGID_TRAP_10                      0x00000112
#घोषणा DREG_REGID_TRAP_11                      0x00000113
#घोषणा DREG_REGID_TRAP_12                      0x00000114
#घोषणा DREG_REGID_TRAP_13                      0x00000115
#घोषणा DREG_REGID_TRAP_14                      0x00000116
#घोषणा DREG_REGID_TRAP_15                      0x00000117
#घोषणा DREG_REGID_TRAP_16                      0x00000118
#घोषणा DREG_REGID_TRAP_17                      0x00000119
#घोषणा DREG_REGID_TRAP_18                      0x0000011A
#घोषणा DREG_REGID_TRAP_19                      0x0000011B
#घोषणा DREG_REGID_TRAP_20                      0x0000011C
#घोषणा DREG_REGID_TRAP_21                      0x0000011D
#घोषणा DREG_REGID_TRAP_22                      0x0000011E
#घोषणा DREG_REGID_TRAP_23                      0x0000011F
#पूर्ण_अगर
#पूर्ण_अगर
#घोषणा DREG_REGID_RSA0_LOW                     0x00000200
#घोषणा DREG_REGID_RSA0_HIGH                    0x00000201
#घोषणा DREG_REGID_RSA1_LOW                     0x00000202
#घोषणा DREG_REGID_RSA1_HIGH                    0x00000203
#घोषणा DREG_REGID_RSA2                         0x00000204
#घोषणा DREG_REGID_RSA3                         0x00000205
#घोषणा DREG_REGID_RSI0_LOW                     0x00000206
#घोषणा DREG_REGID_RSI0_HIGH                    0x00000207
#घोषणा DREG_REGID_RSI1                         0x00000208
#घोषणा DREG_REGID_RSI2                         0x00000209
#घोषणा DREG_REGID_SAGUSTATUS                   0x0000020A
#घोषणा DREG_REGID_RSCONFIG01_LOW               0x0000020B
#घोषणा DREG_REGID_RSCONFIG01_HIGH              0x0000020C
#घोषणा DREG_REGID_RSCONFIG23_LOW               0x0000020D
#घोषणा DREG_REGID_RSCONFIG23_HIGH              0x0000020E
#घोषणा DREG_REGID_RSDMA01E                     0x0000020F
#घोषणा DREG_REGID_RSDMA23E                     0x00000210
#घोषणा DREG_REGID_RSD0_LOW                     0x00000211
#घोषणा DREG_REGID_RSD0_HIGH                    0x00000212
#घोषणा DREG_REGID_RSD1_LOW                     0x00000213
#घोषणा DREG_REGID_RSD1_HIGH                    0x00000214
#घोषणा DREG_REGID_RSD2_LOW                     0x00000215
#घोषणा DREG_REGID_RSD2_HIGH                    0x00000216
#घोषणा DREG_REGID_RSD3_LOW                     0x00000217
#घोषणा DREG_REGID_RSD3_HIGH                    0x00000218
#घोषणा DREG_REGID_SRAR_HIGH                    0x0000021A
#घोषणा DREG_REGID_SRAR_LOW                     0x0000021B
#घोषणा DREG_REGID_DMA_STATE                    0x0000021C
#घोषणा DREG_REGID_CURRENT_DMA_STREAM           0x0000021D
#घोषणा DREG_REGID_NEXT_DMA_STREAM              0x0000021E
#घोषणा DREG_REGID_CPU_STATUS                   0x00000300
#घोषणा DREG_REGID_MAC_MODE                     0x00000301
#घोषणा DREG_REGID_STACK_AND_REPEAT             0x00000302
#घोषणा DREG_REGID_INDEX0                       0x00000304
#घोषणा DREG_REGID_INDEX1                       0x00000305
#घोषणा DREG_REGID_DMA_STATE_0_3                0x00000400
#घोषणा DREG_REGID_DMA_STATE_4_7                0x00000404
#घोषणा DREG_REGID_DMA_STATE_8_11               0x00000408
#घोषणा DREG_REGID_DMA_STATE_12_15              0x0000040C
#घोषणा DREG_REGID_DMA_STATE_16_19              0x00000410
#घोषणा DREG_REGID_DMA_STATE_20_23              0x00000414
#घोषणा DREG_REGID_DMA_STATE_24_27              0x00000418
#घोषणा DREG_REGID_DMA_STATE_28_31              0x0000041C
#घोषणा DREG_REGID_DMA_STATE_32_35              0x00000420
#घोषणा DREG_REGID_DMA_STATE_36_39              0x00000424
#घोषणा DREG_REGID_DMA_STATE_40_43              0x00000428
#घोषणा DREG_REGID_DMA_STATE_44_47              0x0000042C
#घोषणा DREG_REGID_DMA_STATE_48_51              0x00000430
#घोषणा DREG_REGID_DMA_STATE_52_55              0x00000434
#घोषणा DREG_REGID_DMA_STATE_56_59              0x00000438
#घोषणा DREG_REGID_DMA_STATE_60_63              0x0000043C
#घोषणा DREG_REGID_DMA_STATE_64_67              0x00000440
#घोषणा DREG_REGID_DMA_STATE_68_71              0x00000444
#घोषणा DREG_REGID_DMA_STATE_72_75              0x00000448
#घोषणा DREG_REGID_DMA_STATE_76_79              0x0000044C
#घोषणा DREG_REGID_DMA_STATE_80_83              0x00000450
#घोषणा DREG_REGID_DMA_STATE_84_87              0x00000454
#घोषणा DREG_REGID_DMA_STATE_88_91              0x00000458
#घोषणा DREG_REGID_DMA_STATE_92_95              0x0000045C
#घोषणा DREG_REGID_TRAP_SELECT                  0x00000500
#घोषणा DREG_REGID_TRAP_WRITE_0                 0x00000500
#घोषणा DREG_REGID_TRAP_WRITE_1                 0x00000501
#घोषणा DREG_REGID_TRAP_WRITE_2                 0x00000502
#घोषणा DREG_REGID_TRAP_WRITE_3                 0x00000503
#घोषणा DREG_REGID_TRAP_WRITE_4                 0x00000504
#घोषणा DREG_REGID_TRAP_WRITE_5                 0x00000505
#घोषणा DREG_REGID_TRAP_WRITE_6                 0x00000506
#घोषणा DREG_REGID_TRAP_WRITE_7                 0x00000507
#अगर !defined(NO_CS4612)
#अगर !defined(NO_CS4615)
#घोषणा DREG_REGID_TRAP_WRITE_8                 0x00000510
#घोषणा DREG_REGID_TRAP_WRITE_9                 0x00000511
#घोषणा DREG_REGID_TRAP_WRITE_10                0x00000512
#घोषणा DREG_REGID_TRAP_WRITE_11                0x00000513
#घोषणा DREG_REGID_TRAP_WRITE_12                0x00000514
#घोषणा DREG_REGID_TRAP_WRITE_13                0x00000515
#घोषणा DREG_REGID_TRAP_WRITE_14                0x00000516
#घोषणा DREG_REGID_TRAP_WRITE_15                0x00000517
#घोषणा DREG_REGID_TRAP_WRITE_16                0x00000518
#घोषणा DREG_REGID_TRAP_WRITE_17                0x00000519
#घोषणा DREG_REGID_TRAP_WRITE_18                0x0000051A
#घोषणा DREG_REGID_TRAP_WRITE_19                0x0000051B
#घोषणा DREG_REGID_TRAP_WRITE_20                0x0000051C
#घोषणा DREG_REGID_TRAP_WRITE_21                0x0000051D
#घोषणा DREG_REGID_TRAP_WRITE_22                0x0000051E
#घोषणा DREG_REGID_TRAP_WRITE_23                0x0000051F
#पूर्ण_अगर
#पूर्ण_अगर
#घोषणा DREG_REGID_MAC0_ACC0_LOW                0x00000600
#घोषणा DREG_REGID_MAC0_ACC1_LOW                0x00000601
#घोषणा DREG_REGID_MAC0_ACC2_LOW                0x00000602
#घोषणा DREG_REGID_MAC0_ACC3_LOW                0x00000603
#घोषणा DREG_REGID_MAC1_ACC0_LOW                0x00000604
#घोषणा DREG_REGID_MAC1_ACC1_LOW                0x00000605
#घोषणा DREG_REGID_MAC1_ACC2_LOW                0x00000606
#घोषणा DREG_REGID_MAC1_ACC3_LOW                0x00000607
#घोषणा DREG_REGID_MAC0_ACC0_MID                0x00000608
#घोषणा DREG_REGID_MAC0_ACC1_MID                0x00000609
#घोषणा DREG_REGID_MAC0_ACC2_MID                0x0000060A
#घोषणा DREG_REGID_MAC0_ACC3_MID                0x0000060B
#घोषणा DREG_REGID_MAC1_ACC0_MID                0x0000060C
#घोषणा DREG_REGID_MAC1_ACC1_MID                0x0000060D
#घोषणा DREG_REGID_MAC1_ACC2_MID                0x0000060E
#घोषणा DREG_REGID_MAC1_ACC3_MID                0x0000060F
#घोषणा DREG_REGID_MAC0_ACC0_HIGH               0x00000610
#घोषणा DREG_REGID_MAC0_ACC1_HIGH               0x00000611
#घोषणा DREG_REGID_MAC0_ACC2_HIGH               0x00000612
#घोषणा DREG_REGID_MAC0_ACC3_HIGH               0x00000613
#घोषणा DREG_REGID_MAC1_ACC0_HIGH               0x00000614
#घोषणा DREG_REGID_MAC1_ACC1_HIGH               0x00000615
#घोषणा DREG_REGID_MAC1_ACC2_HIGH               0x00000616
#घोषणा DREG_REGID_MAC1_ACC3_HIGH               0x00000617
#घोषणा DREG_REGID_RSHOUT_LOW                   0x00000620
#घोषणा DREG_REGID_RSHOUT_MID                   0x00000628
#घोषणा DREG_REGID_RSHOUT_HIGH                  0x00000630

/*
 *  The following defines are क्रम the flags in the DMA stream requestor ग_लिखो
 */
#घोषणा DSRWP_DSR_MASK                          0x0000000F
#घोषणा DSRWP_DSR_BG_RQ                         0x00000001
#घोषणा DSRWP_DSR_PRIORITY_MASK                 0x00000006
#घोषणा DSRWP_DSR_PRIORITY_0                    0x00000000
#घोषणा DSRWP_DSR_PRIORITY_1                    0x00000002
#घोषणा DSRWP_DSR_PRIORITY_2                    0x00000004
#घोषणा DSRWP_DSR_PRIORITY_3                    0x00000006
#घोषणा DSRWP_DSR_RQ_PENDING                    0x00000008

/*
 *  The following defines are क्रम the flags in the trap ग_लिखो port रेजिस्टर.
 */
#घोषणा TWPR_TW_MASK                            0x0000FFFF
#घोषणा TWPR_TW_SHIFT                           0

/*
 *  The following defines are क्रम the flags in the stack poपूर्णांकer ग_लिखो
 *  रेजिस्टर.
 */
#घोषणा SPWR_STKP_MASK                          0x0000000F
#घोषणा SPWR_STKP_SHIFT                         0

/*
 *  The following defines are क्रम the flags in the SP पूर्णांकerrupt रेजिस्टर.
 */
#घोषणा SPIR_FRI                                0x00000001
#घोषणा SPIR_DOI                                0x00000002
#घोषणा SPIR_GPI2                               0x00000004
#घोषणा SPIR_GPI3                               0x00000008
#घोषणा SPIR_IP0                                0x00000010
#घोषणा SPIR_IP1                                0x00000020
#घोषणा SPIR_IP2                                0x00000040
#घोषणा SPIR_IP3                                0x00000080

/*
 *  The following defines are क्रम the flags in the functional group 1 रेजिस्टर.
 */
#घोषणा FGR1_F1S_MASK                           0x0000FFFF
#घोषणा FGR1_F1S_SHIFT                          0

/*
 *  The following defines are क्रम the flags in the SP घड़ी status रेजिस्टर.
 */
#घोषणा SPCS_FRI                                0x00000001
#घोषणा SPCS_DOI                                0x00000002
#घोषणा SPCS_GPI2                               0x00000004
#घोषणा SPCS_GPI3                               0x00000008
#घोषणा SPCS_IP0                                0x00000010
#घोषणा SPCS_IP1                                0x00000020
#घोषणा SPCS_IP2                                0x00000040
#घोषणा SPCS_IP3                                0x00000080
#घोषणा SPCS_SPRUN                              0x00000100
#घोषणा SPCS_SLEEP                              0x00000200
#घोषणा SPCS_FG                                 0x00000400
#घोषणा SPCS_ORUN                               0x00000800
#घोषणा SPCS_IRQ                                0x00001000
#घोषणा SPCS_FGN_MASK                           0x0000E000
#घोषणा SPCS_FGN_SHIFT                          13

/*
 *  The following defines are क्रम the flags in the SP DMA requestor status
 *  रेजिस्टर.
 */
#घोषणा SDSR_DCS_MASK                           0x000000FF
#घोषणा SDSR_DCS_SHIFT                          0
#घोषणा SDSR_DCS_NONE                           0x00000007

/*
 *  The following defines are क्रम the flags in the frame समयr रेजिस्टर.
 */
#घोषणा FRMT_FTV_MASK                           0x0000FFFF
#घोषणा FRMT_FTV_SHIFT                          0

/*
 *  The following defines are क्रम the flags in the frame समयr current count
 *  रेजिस्टर.
 */
#घोषणा FRCC_FCC_MASK                           0x0000FFFF
#घोषणा FRCC_FCC_SHIFT                          0

/*
 *  The following defines are क्रम the flags in the frame समयr save count
 *  रेजिस्टर.
 */
#घोषणा FRSC_FCS_MASK                           0x0000FFFF
#घोषणा FRSC_FCS_SHIFT                          0

/*
 *  The following define the various flags stored in the scatter/gather
 *  descriptors.
 */
#घोषणा DMA_SG_NEXT_ENTRY_MASK                  0x00000FF8
#घोषणा DMA_SG_SAMPLE_END_MASK                  0x0FFF0000
#घोषणा DMA_SG_SAMPLE_END_FLAG                  0x10000000
#घोषणा DMA_SG_LOOP_END_FLAG                    0x20000000
#घोषणा DMA_SG_SIGNAL_END_FLAG                  0x40000000
#घोषणा DMA_SG_SIGNAL_PAGE_FLAG                 0x80000000
#घोषणा DMA_SG_NEXT_ENTRY_SHIFT                 3
#घोषणा DMA_SG_SAMPLE_END_SHIFT                 16

/*
 *  The following define the offsets of the fields within the on-chip generic
 *  DMA requestor.
 */
#घोषणा DMA_RQ_CONTROL1                         0x00000000
#घोषणा DMA_RQ_CONTROL2                         0x00000004
#घोषणा DMA_RQ_SOURCE_ADDR                      0x00000008
#घोषणा DMA_RQ_DESTINATION_ADDR                 0x0000000C
#घोषणा DMA_RQ_NEXT_PAGE_ADDR                   0x00000010
#घोषणा DMA_RQ_NEXT_PAGE_SGDESC                 0x00000014
#घोषणा DMA_RQ_LOOP_START_ADDR                  0x00000018
#घोषणा DMA_RQ_POST_LOOP_ADDR                   0x0000001C
#घोषणा DMA_RQ_PAGE_MAP_ADDR                    0x00000020

/*
 *  The following defines are क्रम the flags in the first control word of the
 *  on-chip generic DMA requestor.
 */
#घोषणा DMA_RQ_C1_COUNT_MASK                    0x000003FF
#घोषणा DMA_RQ_C1_DESTINATION_SCATTER           0x00001000
#घोषणा DMA_RQ_C1_SOURCE_GATHER                 0x00002000
#घोषणा DMA_RQ_C1_DONE_FLAG                     0x00004000
#घोषणा DMA_RQ_C1_OPTIMIZE_STATE                0x00008000
#घोषणा DMA_RQ_C1_SAMPLE_END_STATE_MASK         0x00030000
#घोषणा DMA_RQ_C1_FULL_PAGE                     0x00000000
#घोषणा DMA_RQ_C1_BEFORE_SAMPLE_END             0x00010000
#घोषणा DMA_RQ_C1_PAGE_MAP_ERROR                0x00020000
#घोषणा DMA_RQ_C1_AT_SAMPLE_END                 0x00030000
#घोषणा DMA_RQ_C1_LOOP_END_STATE_MASK           0x000C0000
#घोषणा DMA_RQ_C1_NOT_LOOP_END                  0x00000000
#घोषणा DMA_RQ_C1_BEFORE_LOOP_END               0x00040000
#घोषणा DMA_RQ_C1_2PAGE_LOOP_BEGIN              0x00080000
#घोषणा DMA_RQ_C1_LOOP_BEGIN                    0x000C0000
#घोषणा DMA_RQ_C1_PAGE_MAP_MASK                 0x00300000
#घोषणा DMA_RQ_C1_PM_NONE_PENDING               0x00000000
#घोषणा DMA_RQ_C1_PM_NEXT_PENDING               0x00100000
#घोषणा DMA_RQ_C1_PM_RESERVED                   0x00200000
#घोषणा DMA_RQ_C1_PM_LOOP_NEXT_PENDING          0x00300000
#घोषणा DMA_RQ_C1_WRITEBACK_DEST_FLAG           0x00400000
#घोषणा DMA_RQ_C1_WRITEBACK_SRC_FLAG            0x00800000
#घोषणा DMA_RQ_C1_DEST_SIZE_MASK                0x07000000
#घोषणा DMA_RQ_C1_DEST_LINEAR                   0x00000000
#घोषणा DMA_RQ_C1_DEST_MOD16                    0x01000000
#घोषणा DMA_RQ_C1_DEST_MOD32                    0x02000000
#घोषणा DMA_RQ_C1_DEST_MOD64                    0x03000000
#घोषणा DMA_RQ_C1_DEST_MOD128                   0x04000000
#घोषणा DMA_RQ_C1_DEST_MOD256                   0x05000000
#घोषणा DMA_RQ_C1_DEST_MOD512                   0x06000000
#घोषणा DMA_RQ_C1_DEST_MOD1024                  0x07000000
#घोषणा DMA_RQ_C1_DEST_ON_HOST                  0x08000000
#घोषणा DMA_RQ_C1_SOURCE_SIZE_MASK              0x70000000
#घोषणा DMA_RQ_C1_SOURCE_LINEAR                 0x00000000
#घोषणा DMA_RQ_C1_SOURCE_MOD16                  0x10000000
#घोषणा DMA_RQ_C1_SOURCE_MOD32                  0x20000000
#घोषणा DMA_RQ_C1_SOURCE_MOD64                  0x30000000
#घोषणा DMA_RQ_C1_SOURCE_MOD128                 0x40000000
#घोषणा DMA_RQ_C1_SOURCE_MOD256                 0x50000000
#घोषणा DMA_RQ_C1_SOURCE_MOD512                 0x60000000
#घोषणा DMA_RQ_C1_SOURCE_MOD1024                0x70000000
#घोषणा DMA_RQ_C1_SOURCE_ON_HOST                0x80000000
#घोषणा DMA_RQ_C1_COUNT_SHIFT                   0

/*
 *  The following defines are क्रम the flags in the second control word of the
 *  on-chip generic DMA requestor.
 */
#घोषणा DMA_RQ_C2_VIRTUAL_CHANNEL_MASK          0x0000003F
#घोषणा DMA_RQ_C2_VIRTUAL_SIGNAL_MASK           0x00000300
#घोषणा DMA_RQ_C2_NO_VIRTUAL_SIGNAL             0x00000000
#घोषणा DMA_RQ_C2_SIGNAL_EVERY_DMA              0x00000100
#घोषणा DMA_RQ_C2_SIGNAL_SOURCE_PINGPONG        0x00000200
#घोषणा DMA_RQ_C2_SIGNAL_DEST_PINGPONG          0x00000300
#घोषणा DMA_RQ_C2_AUDIO_CONVERT_MASK            0x0000F000
#घोषणा DMA_RQ_C2_AC_NONE                       0x00000000
#घोषणा DMA_RQ_C2_AC_8_TO_16_BIT                0x00001000
#घोषणा DMA_RQ_C2_AC_MONO_TO_STEREO             0x00002000
#घोषणा DMA_RQ_C2_AC_ENDIAN_CONVERT             0x00004000
#घोषणा DMA_RQ_C2_AC_SIGNED_CONVERT             0x00008000
#घोषणा DMA_RQ_C2_LOOP_END_MASK                 0x0FFF0000
#घोषणा DMA_RQ_C2_LOOP_MASK                     0x30000000
#घोषणा DMA_RQ_C2_NO_LOOP                       0x00000000
#घोषणा DMA_RQ_C2_ONE_PAGE_LOOP                 0x10000000
#घोषणा DMA_RQ_C2_TWO_PAGE_LOOP                 0x20000000
#घोषणा DMA_RQ_C2_MULTI_PAGE_LOOP               0x30000000
#घोषणा DMA_RQ_C2_SIGNAL_LOOP_BACK              0x40000000
#घोषणा DMA_RQ_C2_SIGNAL_POST_BEGIN_PAGE        0x80000000
#घोषणा DMA_RQ_C2_VIRTUAL_CHANNEL_SHIFT         0
#घोषणा DMA_RQ_C2_LOOP_END_SHIFT                16

/*
 *  The following defines are क्रम the flags in the source and destination words
 *  of the on-chip generic DMA requestor.
 */
#घोषणा DMA_RQ_SD_ADDRESS_MASK                  0x0000FFFF
#घोषणा DMA_RQ_SD_MEMORY_ID_MASK                0x000F0000
#घोषणा DMA_RQ_SD_SP_PARAM_ADDR                 0x00000000
#घोषणा DMA_RQ_SD_SP_SAMPLE_ADDR                0x00010000
#घोषणा DMA_RQ_SD_SP_PROGRAM_ADDR               0x00020000
#घोषणा DMA_RQ_SD_SP_DEBUG_ADDR                 0x00030000
#घोषणा DMA_RQ_SD_OMNIMEM_ADDR                  0x000E0000
#घोषणा DMA_RQ_SD_END_FLAG                      0x40000000
#घोषणा DMA_RQ_SD_ERROR_FLAG                    0x80000000
#घोषणा DMA_RQ_SD_ADDRESS_SHIFT                 0

/*
 *  The following defines are क्रम the flags in the page map address word of the
 *  on-chip generic DMA requestor.
 */
#घोषणा DMA_RQ_PMA_LOOP_THIRD_PAGE_ENTRY_MASK   0x00000FF8
#घोषणा DMA_RQ_PMA_PAGE_TABLE_MASK              0xFFFFF000
#घोषणा DMA_RQ_PMA_LOOP_THIRD_PAGE_ENTRY_SHIFT  3
#घोषणा DMA_RQ_PMA_PAGE_TABLE_SHIFT             12

#घोषणा BA1_VARIDEC_BUF_1       0x000

#घोषणा BA1_PDTC                0x0c0    /* BA1_PLAY_DMA_TRANSACTION_COUNT_REG */
#घोषणा BA1_PFIE                0x0c4    /* BA1_PLAY_FORMAT_&_INTERRUPT_ENABLE_REG */
#घोषणा BA1_PBA                 0x0c8    /* BA1_PLAY_BUFFER_ADDRESS */
#घोषणा BA1_PVOL                0x0f8    /* BA1_PLAY_VOLUME_REG */
#घोषणा BA1_PSRC                0x288    /* BA1_PLAY_SAMPLE_RATE_CORRECTION_REG */
#घोषणा BA1_PCTL                0x2a4    /* BA1_PLAY_CONTROL_REG */
#घोषणा BA1_PPI                 0x2b4    /* BA1_PLAY_PHASE_INCREMENT_REG */

#घोषणा BA1_CCTL                0x064    /* BA1_CAPTURE_CONTROL_REG */
#घोषणा BA1_CIE                 0x104    /* BA1_CAPTURE_INTERRUPT_ENABLE_REG */
#घोषणा BA1_CBA                 0x10c    /* BA1_CAPTURE_BUFFER_ADDRESS */
#घोषणा BA1_CSRC                0x2c8    /* BA1_CAPTURE_SAMPLE_RATE_CORRECTION_REG */
#घोषणा BA1_CCI                 0x2d8    /* BA1_CAPTURE_COEFFICIENT_INCREMENT_REG */
#घोषणा BA1_CD                  0x2e0    /* BA1_CAPTURE_DELAY_REG */
#घोषणा BA1_CPI                 0x2f4    /* BA1_CAPTURE_PHASE_INCREMENT_REG */
#घोषणा BA1_CVOL                0x2f8    /* BA1_CAPTURE_VOLUME_REG */

#घोषणा BA1_CFG1                0x134    /* BA1_CAPTURE_FRAME_GROUP_1_REG */
#घोषणा BA1_CFG2                0x138    /* BA1_CAPTURE_FRAME_GROUP_2_REG */
#घोषणा BA1_CCST                0x13c    /* BA1_CAPTURE_CONSTANT_REG */
#घोषणा BA1_CSPB                0x340    /* BA1_CAPTURE_SPB_ADDRESS */

/*
 *
 */

#घोषणा CS46XX_MODE_OUTPUT	(1<<0)	 /* MIDI UART - output */ 
#घोषणा CS46XX_MODE_INPUT	(1<<1)	 /* MIDI UART - input */

/*
 *
 */

#घोषणा SAVE_REG_MAX             0x10
#घोषणा POWER_DOWN_ALL         0x7f0f

/* maxinum number of AC97 codecs connected, AC97 2.0 defined 4 */
#घोषणा MAX_NR_AC97				            4
#घोषणा CS46XX_PRIMARY_CODEC_INDEX          0
#घोषणा CS46XX_SECONDARY_CODEC_INDEX		1
#घोषणा CS46XX_SECONDARY_CODEC_OFFSET		0x80
#घोषणा CS46XX_DSP_CAPTURE_CHANNEL          1

/* capture */
#घोषणा CS46XX_DSP_CAPTURE_CHANNEL          1

/* mixer */
#घोषणा CS46XX_MIXER_SPDIF_INPUT_ELEMENT    1
#घोषणा CS46XX_MIXER_SPDIF_OUTPUT_ELEMENT   2


काष्ठा snd_cs46xx_pcm अणु
	काष्ठा snd_dma_buffer hw_buf;
  
	अचिन्हित पूर्णांक ctl;
	अचिन्हित पूर्णांक shअगरt;	/* Shअगरt count to trasक्रमm frames in bytes */
	काष्ठा snd_pcm_indirect pcm_rec;
	काष्ठा snd_pcm_substream *substream;

	काष्ठा dsp_pcm_channel_descriptor * pcm_channel;

	पूर्णांक pcm_channel_id;    /* Fron Rear, Center Lfe  ... */
पूर्ण;

काष्ठा snd_cs46xx_region अणु
	अक्षर name[24];
	अचिन्हित दीर्घ base;
	व्योम __iomem *remap_addr;
	अचिन्हित दीर्घ size;
	काष्ठा resource *resource;
पूर्ण;

काष्ठा snd_cs46xx अणु
	पूर्णांक irq;
	अचिन्हित दीर्घ ba0_addr;
	अचिन्हित दीर्घ ba1_addr;
	जोड़ अणु
		काष्ठा अणु
			काष्ठा snd_cs46xx_region ba0;
			काष्ठा snd_cs46xx_region data0;
			काष्ठा snd_cs46xx_region data1;
			काष्ठा snd_cs46xx_region pmem;
			काष्ठा snd_cs46xx_region reg;
		पूर्ण name;
		काष्ठा snd_cs46xx_region idx[5];
	पूर्ण region;

	अचिन्हित पूर्णांक mode;
	
	काष्ठा अणु
		काष्ठा snd_dma_buffer hw_buf;

		अचिन्हित पूर्णांक ctl;
		अचिन्हित पूर्णांक shअगरt;	/* Shअगरt count to trasक्रमm frames in bytes */
		काष्ठा snd_pcm_indirect pcm_rec;
		काष्ठा snd_pcm_substream *substream;
	पूर्ण capt;


	पूर्णांक nr_ac97_codecs;
	काष्ठा snd_ac97_bus *ac97_bus;
	काष्ठा snd_ac97 *ac97[MAX_NR_AC97];

	काष्ठा pci_dev *pci;
	काष्ठा snd_card *card;
	काष्ठा snd_pcm *pcm;

	काष्ठा snd_rawmidi *rmidi;
	काष्ठा snd_rawmidi_substream *midi_input;
	काष्ठा snd_rawmidi_substream *midi_output;

	spinlock_t reg_lock;
	अचिन्हित पूर्णांक midcr;
	अचिन्हित पूर्णांक uarपंचांग;

	पूर्णांक amplअगरier;
	व्योम (*amplअगरier_ctrl)(काष्ठा snd_cs46xx *, पूर्णांक);
	व्योम (*active_ctrl)(काष्ठा snd_cs46xx *, पूर्णांक);
  	व्योम (*mixer_init)(काष्ठा snd_cs46xx *);

	पूर्णांक acpi_port;
	काष्ठा snd_kcontrol *eapd_चयन; /* क्रम amplअगरier hack */
	पूर्णांक accept_valid;	/* accept mmap valid (क्रम OSS) */
	पूर्णांक in_suspend;

	काष्ठा gameport *gameport;

#अगर_घोषित CONFIG_SND_CS46XX_NEW_DSP
	काष्ठा mutex spos_mutex;

	काष्ठा dsp_spos_instance * dsp_spos_instance;

	काष्ठा snd_pcm *pcm_rear;
	काष्ठा snd_pcm *pcm_center_lfe;
	काष्ठा snd_pcm *pcm_iec958;

#घोषणा CS46XX_DSP_MODULES	5
	काष्ठा dsp_module_desc *modules[CS46XX_DSP_MODULES];
#अन्यथा /* क्रम compatibility */
	काष्ठा snd_cs46xx_pcm *playback_pcm;
	अचिन्हित पूर्णांक play_ctl;

	काष्ठा ba1_काष्ठा *ba1;
#पूर्ण_अगर

#अगर_घोषित CONFIG_PM_SLEEP
	u32 *saved_regs;
#पूर्ण_अगर
पूर्ण;

पूर्णांक snd_cs46xx_create(काष्ठा snd_card *card,
		      काष्ठा pci_dev *pci,
		      पूर्णांक बाह्यal_amp, पूर्णांक thinkpad,
		      काष्ठा snd_cs46xx **rcodec);
बाह्य स्थिर काष्ठा dev_pm_ops snd_cs46xx_pm;

पूर्णांक snd_cs46xx_pcm(काष्ठा snd_cs46xx *chip, पूर्णांक device);
पूर्णांक snd_cs46xx_pcm_rear(काष्ठा snd_cs46xx *chip, पूर्णांक device);
पूर्णांक snd_cs46xx_pcm_iec958(काष्ठा snd_cs46xx *chip, पूर्णांक device);
पूर्णांक snd_cs46xx_pcm_center_lfe(काष्ठा snd_cs46xx *chip, पूर्णांक device);
पूर्णांक snd_cs46xx_mixer(काष्ठा snd_cs46xx *chip, पूर्णांक spdअगर_device);
पूर्णांक snd_cs46xx_midi(काष्ठा snd_cs46xx *chip, पूर्णांक device);
पूर्णांक snd_cs46xx_start_dsp(काष्ठा snd_cs46xx *chip);
पूर्णांक snd_cs46xx_gameport(काष्ठा snd_cs46xx *chip);

#पूर्ण_अगर /* __SOUND_CS46XX_H */
