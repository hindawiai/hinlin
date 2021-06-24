<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 *  Driver क्रम the Conexant CX25821 PCIe bridge
 *
 *  Copyright (C) 2009 Conexant Systems Inc.
 *  Authors  <shu.lin@conexant.com>, <hiep.huynh@conexant.com>
 */

#अगर_अघोषित __ATHENA_SRAM_H__
#घोषणा __ATHENA_SRAM_H__

/* #घोषणा RX_SRAM_START_SIZE        = 0;  //  Start of reserved SRAM */
#घोषणा VID_CMDS_SIZE             80	/* Video CMDS size in bytes */
#घोषणा AUDIO_CMDS_SIZE           80	/* AUDIO CMDS size in bytes */
#घोषणा MBIF_CMDS_SIZE            80	/* MBIF  CMDS size in bytes */

/* #घोषणा RX_SRAM_POOL_START_SIZE   = 0;  //  Start of usable RX SRAM क्रम buffers */
#घोषणा VID_IQ_SIZE               64	/* VID inकाष्ठाion queue size in bytes */
#घोषणा MBIF_IQ_SIZE              64
#घोषणा AUDIO_IQ_SIZE             64	/* AUD inकाष्ठाion queue size in bytes */

#घोषणा VID_CDT_SIZE              64	/* VID cluster descriptor table size in bytes */
#घोषणा MBIF_CDT_SIZE             64	/* MBIF/HBI cluster descriptor table size in bytes */
#घोषणा AUDIO_CDT_SIZE            48	/* AUD cluster descriptor table size in bytes */

/* #घोषणा RX_SRAM_POOL_FREE_SIZE    = 16; //  Start of available RX SRAM */
/* #घोषणा RX_SRAM_END_SIZE          = 0;  //  End of RX SRAM */

/* #घोषणा TX_SRAM_POOL_START_SIZE   = 0;  //  Start of transmit pool SRAM */
/* #घोषणा MSI_DATA_SIZE             = 64; //  Reserved (MSI Data, RISC working stora */

#घोषणा VID_CLUSTER_SIZE          1440	/* VID cluster data line */
#घोषणा AUDIO_CLUSTER_SIZE        128	/* AUDIO cluster data line */
#घोषणा MBIF_CLUSTER_SIZE         1440	/* MBIF/HBI cluster data line */

/* #घोषणा TX_SRAM_POOL_FREE_SIZE    = 704;    //  Start of available TX SRAM */
/* #घोषणा TX_SRAM_END_SIZE          = 0;      //  End of TX SRAM */

/* Receive SRAM */
#घोषणा RX_SRAM_START             0x10000
#घोषणा VID_A_DOWN_CMDS           0x10000
#घोषणा VID_B_DOWN_CMDS           0x10050
#घोषणा VID_C_DOWN_CMDS           0x100A0
#घोषणा VID_D_DOWN_CMDS           0x100F0
#घोषणा VID_E_DOWN_CMDS           0x10140
#घोषणा VID_F_DOWN_CMDS           0x10190
#घोषणा VID_G_DOWN_CMDS           0x101E0
#घोषणा VID_H_DOWN_CMDS           0x10230
#घोषणा VID_A_UP_CMDS             0x10280
#घोषणा VID_B_UP_CMDS             0x102D0
#घोषणा VID_C_UP_CMDS             0x10320
#घोषणा VID_D_UP_CMDS             0x10370
#घोषणा VID_E_UP_CMDS             0x103C0
#घोषणा VID_F_UP_CMDS             0x10410
#घोषणा VID_I_UP_CMDS             0x10460
#घोषणा VID_J_UP_CMDS             0x104B0
#घोषणा AUD_A_DOWN_CMDS           0x10500
#घोषणा AUD_B_DOWN_CMDS           0x10550
#घोषणा AUD_C_DOWN_CMDS           0x105A0
#घोषणा AUD_D_DOWN_CMDS           0x105F0
#घोषणा AUD_A_UP_CMDS             0x10640
#घोषणा AUD_B_UP_CMDS             0x10690
#घोषणा AUD_C_UP_CMDS             0x106E0
#घोषणा AUD_E_UP_CMDS             0x10730
#घोषणा MBIF_A_DOWN_CMDS          0x10780
#घोषणा MBIF_B_DOWN_CMDS          0x107D0
#घोषणा DMA_SCRATCH_PAD           0x10820	/* Scratch pad area from 0x10820 to 0x10B40 */

/* #घोषणा RX_SRAM_POOL_START        = 0x105B0; */

#घोषणा VID_A_IQ                  0x11000
#घोषणा VID_B_IQ                  0x11040
#घोषणा VID_C_IQ                  0x11080
#घोषणा VID_D_IQ                  0x110C0
#घोषणा VID_E_IQ                  0x11100
#घोषणा VID_F_IQ                  0x11140
#घोषणा VID_G_IQ                  0x11180
#घोषणा VID_H_IQ                  0x111C0
#घोषणा VID_I_IQ                  0x11200
#घोषणा VID_J_IQ                  0x11240
#घोषणा AUD_A_IQ                  0x11280
#घोषणा AUD_B_IQ                  0x112C0
#घोषणा AUD_C_IQ                  0x11300
#घोषणा AUD_D_IQ                  0x11340
#घोषणा AUD_E_IQ                  0x11380
#घोषणा MBIF_A_IQ                 0x11000
#घोषणा MBIF_B_IQ                 0x110C0

#घोषणा VID_A_CDT                 0x10C00
#घोषणा VID_B_CDT                 0x10C40
#घोषणा VID_C_CDT                 0x10C80
#घोषणा VID_D_CDT                 0x10CC0
#घोषणा VID_E_CDT                 0x10D00
#घोषणा VID_F_CDT                 0x10D40
#घोषणा VID_G_CDT                 0x10D80
#घोषणा VID_H_CDT                 0x10DC0
#घोषणा VID_I_CDT                 0x10E00
#घोषणा VID_J_CDT                 0x10E40
#घोषणा AUD_A_CDT                 0x10E80
#घोषणा AUD_B_CDT                 0x10EB0
#घोषणा AUD_C_CDT                 0x10EE0
#घोषणा AUD_D_CDT                 0x10F10
#घोषणा AUD_E_CDT                 0x10F40
#घोषणा MBIF_A_CDT                0x10C00
#घोषणा MBIF_B_CDT                0x10CC0

/* Cluster Buffer क्रम RX */
#घोषणा VID_A_UP_CLUSTER_1        0x11400
#घोषणा VID_A_UP_CLUSTER_2        0x119A0
#घोषणा VID_A_UP_CLUSTER_3        0x11F40
#घोषणा VID_A_UP_CLUSTER_4        0x124E0

#घोषणा VID_B_UP_CLUSTER_1        0x12A80
#घोषणा VID_B_UP_CLUSTER_2        0x13020
#घोषणा VID_B_UP_CLUSTER_3        0x135C0
#घोषणा VID_B_UP_CLUSTER_4        0x13B60

#घोषणा VID_C_UP_CLUSTER_1        0x14100
#घोषणा VID_C_UP_CLUSTER_2        0x146A0
#घोषणा VID_C_UP_CLUSTER_3        0x14C40
#घोषणा VID_C_UP_CLUSTER_4        0x151E0

#घोषणा VID_D_UP_CLUSTER_1        0x15780
#घोषणा VID_D_UP_CLUSTER_2        0x15D20
#घोषणा VID_D_UP_CLUSTER_3        0x162C0
#घोषणा VID_D_UP_CLUSTER_4        0x16860

#घोषणा VID_E_UP_CLUSTER_1        0x16E00
#घोषणा VID_E_UP_CLUSTER_2        0x173A0
#घोषणा VID_E_UP_CLUSTER_3        0x17940
#घोषणा VID_E_UP_CLUSTER_4        0x17EE0

#घोषणा VID_F_UP_CLUSTER_1        0x18480
#घोषणा VID_F_UP_CLUSTER_2        0x18A20
#घोषणा VID_F_UP_CLUSTER_3        0x18FC0
#घोषणा VID_F_UP_CLUSTER_4        0x19560

#घोषणा VID_I_UP_CLUSTER_1        0x19B00
#घोषणा VID_I_UP_CLUSTER_2        0x1A0A0
#घोषणा VID_I_UP_CLUSTER_3        0x1A640
#घोषणा VID_I_UP_CLUSTER_4        0x1ABE0

#घोषणा VID_J_UP_CLUSTER_1        0x1B180
#घोषणा VID_J_UP_CLUSTER_2        0x1B720
#घोषणा VID_J_UP_CLUSTER_3        0x1BCC0
#घोषणा VID_J_UP_CLUSTER_4        0x1C260

#घोषणा AUD_A_UP_CLUSTER_1        0x1C800
#घोषणा AUD_A_UP_CLUSTER_2        0x1C880
#घोषणा AUD_A_UP_CLUSTER_3        0x1C900

#घोषणा AUD_B_UP_CLUSTER_1        0x1C980
#घोषणा AUD_B_UP_CLUSTER_2        0x1CA00
#घोषणा AUD_B_UP_CLUSTER_3        0x1CA80

#घोषणा AUD_C_UP_CLUSTER_1        0x1CB00
#घोषणा AUD_C_UP_CLUSTER_2        0x1CB80
#घोषणा AUD_C_UP_CLUSTER_3        0x1CC00

#घोषणा AUD_E_UP_CLUSTER_1        0x1CC80
#घोषणा AUD_E_UP_CLUSTER_2        0x1CD00
#घोषणा AUD_E_UP_CLUSTER_3        0x1CD80

#घोषणा RX_SRAM_POOL_FREE         0x1CE00
#घोषणा RX_SRAM_END               0x1D000

/* Free Receive SRAM    144 Bytes */

/* Transmit SRAM */
#घोषणा TX_SRAM_POOL_START        0x00000

#घोषणा VID_A_DOWN_CLUSTER_1      0x00040
#घोषणा VID_A_DOWN_CLUSTER_2      0x005E0
#घोषणा VID_A_DOWN_CLUSTER_3      0x00B80
#घोषणा VID_A_DOWN_CLUSTER_4      0x01120

#घोषणा VID_B_DOWN_CLUSTER_1      0x016C0
#घोषणा VID_B_DOWN_CLUSTER_2      0x01C60
#घोषणा VID_B_DOWN_CLUSTER_3      0x02200
#घोषणा VID_B_DOWN_CLUSTER_4      0x027A0

#घोषणा VID_C_DOWN_CLUSTER_1      0x02D40
#घोषणा VID_C_DOWN_CLUSTER_2      0x032E0
#घोषणा VID_C_DOWN_CLUSTER_3      0x03880
#घोषणा VID_C_DOWN_CLUSTER_4      0x03E20

#घोषणा VID_D_DOWN_CLUSTER_1      0x043C0
#घोषणा VID_D_DOWN_CLUSTER_2      0x04960
#घोषणा VID_D_DOWN_CLUSTER_3      0x04F00
#घोषणा VID_D_DOWN_CLUSTER_4      0x054A0

#घोषणा VID_E_DOWN_CLUSTER_1      0x05a40
#घोषणा VID_E_DOWN_CLUSTER_2      0x05FE0
#घोषणा VID_E_DOWN_CLUSTER_3      0x06580
#घोषणा VID_E_DOWN_CLUSTER_4      0x06B20

#घोषणा VID_F_DOWN_CLUSTER_1      0x070C0
#घोषणा VID_F_DOWN_CLUSTER_2      0x07660
#घोषणा VID_F_DOWN_CLUSTER_3      0x07C00
#घोषणा VID_F_DOWN_CLUSTER_4      0x081A0

#घोषणा VID_G_DOWN_CLUSTER_1      0x08740
#घोषणा VID_G_DOWN_CLUSTER_2      0x08CE0
#घोषणा VID_G_DOWN_CLUSTER_3      0x09280
#घोषणा VID_G_DOWN_CLUSTER_4      0x09820

#घोषणा VID_H_DOWN_CLUSTER_1      0x09DC0
#घोषणा VID_H_DOWN_CLUSTER_2      0x0A360
#घोषणा VID_H_DOWN_CLUSTER_3      0x0A900
#घोषणा VID_H_DOWN_CLUSTER_4      0x0AEA0

#घोषणा AUD_A_DOWN_CLUSTER_1      0x0B500
#घोषणा AUD_A_DOWN_CLUSTER_2      0x0B580
#घोषणा AUD_A_DOWN_CLUSTER_3      0x0B600

#घोषणा AUD_B_DOWN_CLUSTER_1      0x0B680
#घोषणा AUD_B_DOWN_CLUSTER_2      0x0B700
#घोषणा AUD_B_DOWN_CLUSTER_3      0x0B780

#घोषणा AUD_C_DOWN_CLUSTER_1      0x0B800
#घोषणा AUD_C_DOWN_CLUSTER_2      0x0B880
#घोषणा AUD_C_DOWN_CLUSTER_3      0x0B900

#घोषणा AUD_D_DOWN_CLUSTER_1      0x0B980
#घोषणा AUD_D_DOWN_CLUSTER_2      0x0BA00
#घोषणा AUD_D_DOWN_CLUSTER_3      0x0BA80

#घोषणा TX_SRAM_POOL_FREE         0x0BB00
#घोषणा TX_SRAM_END               0x0C000

#घोषणा BYTES_TO_DWORDS(bcount) ((bcount) >> 2)
#घोषणा BYTES_TO_QWORDS(bcount) ((bcount) >> 3)
#घोषणा BYTES_TO_OWORDS(bcount) ((bcount) >> 4)

#घोषणा VID_IQ_SIZE_DW             BYTES_TO_DWORDS(VID_IQ_SIZE)
#घोषणा VID_CDT_SIZE_QW            BYTES_TO_QWORDS(VID_CDT_SIZE)
#घोषणा VID_CLUSTER_SIZE_OW        BYTES_TO_OWORDS(VID_CLUSTER_SIZE)

#घोषणा AUDIO_IQ_SIZE_DW           BYTES_TO_DWORDS(AUDIO_IQ_SIZE)
#घोषणा AUDIO_CDT_SIZE_QW          BYTES_TO_QWORDS(AUDIO_CDT_SIZE)
#घोषणा AUDIO_CLUSTER_SIZE_QW      BYTES_TO_QWORDS(AUDIO_CLUSTER_SIZE)

#घोषणा MBIF_IQ_SIZE_DW            BYTES_TO_DWORDS(MBIF_IQ_SIZE)
#घोषणा MBIF_CDT_SIZE_QW           BYTES_TO_QWORDS(MBIF_CDT_SIZE)
#घोषणा MBIF_CLUSTER_SIZE_OW       BYTES_TO_OWORDS(MBIF_CLUSTER_SIZE)

#पूर्ण_अगर
