<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (C) STMicroelectronics SA 2014
 * Authors: Fabien Dessenne <fabien.dessenne@st.com> क्रम STMicroelectronics.
 */

काष्ठा bdisp_node अणु
	/* 0 - General */
	u32 nip;
	u32 cic;
	u32 ins;
	u32 ack;
	/* 1 - Target */
	u32 tba;
	u32 tty;
	u32 txy;
	u32 tsz;
	/* 2 - Color Fill */
	u32 s1cf;
	u32 s2cf;
	/* 3 - Source 1 */
	u32 s1ba;
	u32 s1ty;
	u32 s1xy;
	u32 s1sz_tsz;
	/* 4 - Source 2 */
	u32 s2ba;
	u32 s2ty;
	u32 s2xy;
	u32 s2sz;
	/* 5 - Source 3 */
	u32 s3ba;
	u32 s3ty;
	u32 s3xy;
	u32 s3sz;
	/* 6 - Clipping */
	u32 cwo;
	u32 cws;
	/* 7 - CLUT */
	u32 cco;
	u32 cml;
	/* 8 - Filter & Mask */
	u32 fctl;
	u32 pmk;
	/* 9 - Chroma Filter */
	u32 rsf;
	u32 rzi;
	u32 hfp;
	u32 vfp;
	/* 10 - Luma Filter */
	u32 y_rsf;
	u32 y_rzi;
	u32 y_hfp;
	u32 y_vfp;
	/* 11 - Flicker */
	u32 ff0;
	u32 ff1;
	u32 ff2;
	u32 ff3;
	/* 12 - Color Key */
	u32 key1;
	u32 key2;
	/* 14 - Static Address & User */
	u32 sar;
	u32 usr;
	/* 15 - Input Versatile Matrix */
	u32 ivmx0;
	u32 ivmx1;
	u32 ivmx2;
	u32 ivmx3;
	/* 16 - Output Versatile Matrix */
	u32 ovmx0;
	u32 ovmx1;
	u32 ovmx2;
	u32 ovmx3;
	/* 17 - Pace */
	u32 pace;
	/* 18 - VC1R & DEI */
	u32 vc1r;
	u32 dei;
	/* 19 - Gradient Fill */
	u32 hgf;
	u32 vgf;
पूर्ण;

/* HW रेजिस्टरs : अटल */
#घोषणा BLT_CTL                 0x0A00
#घोषणा BLT_ITS                 0x0A04
#घोषणा BLT_STA1                0x0A08
#घोषणा BLT_AQ1_CTL             0x0A60
#घोषणा BLT_AQ1_IP              0x0A64
#घोषणा BLT_AQ1_LNA             0x0A68
#घोषणा BLT_AQ1_STA             0x0A6C
#घोषणा BLT_ITM0                0x0AD0
/* HW रेजिस्टरs : plugs */
#घोषणा BLT_PLUGS1_OP2          0x0B04
#घोषणा BLT_PLUGS1_CHZ          0x0B08
#घोषणा BLT_PLUGS1_MSZ          0x0B0C
#घोषणा BLT_PLUGS1_PGZ          0x0B10
#घोषणा BLT_PLUGS2_OP2          0x0B24
#घोषणा BLT_PLUGS2_CHZ          0x0B28
#घोषणा BLT_PLUGS2_MSZ          0x0B2C
#घोषणा BLT_PLUGS2_PGZ          0x0B30
#घोषणा BLT_PLUGS3_OP2          0x0B44
#घोषणा BLT_PLUGS3_CHZ          0x0B48
#घोषणा BLT_PLUGS3_MSZ          0x0B4C
#घोषणा BLT_PLUGS3_PGZ          0x0B50
#घोषणा BLT_PLUGT_OP2           0x0B84
#घोषणा BLT_PLUGT_CHZ           0x0B88
#घोषणा BLT_PLUGT_MSZ           0x0B8C
#घोषणा BLT_PLUGT_PGZ           0x0B90
/* HW रेजिस्टरs : node */
#घोषणा BLT_NIP                 0x0C00
#घोषणा BLT_CIC                 0x0C04
#घोषणा BLT_INS                 0x0C08
#घोषणा BLT_ACK                 0x0C0C
#घोषणा BLT_TBA                 0x0C10
#घोषणा BLT_TTY                 0x0C14
#घोषणा BLT_TXY                 0x0C18
#घोषणा BLT_TSZ                 0x0C1C
#घोषणा BLT_S1BA                0x0C28
#घोषणा BLT_S1TY                0x0C2C
#घोषणा BLT_S1XY                0x0C30
#घोषणा BLT_S2BA                0x0C38
#घोषणा BLT_S2TY                0x0C3C
#घोषणा BLT_S2XY                0x0C40
#घोषणा BLT_S2SZ                0x0C44
#घोषणा BLT_S3BA                0x0C48
#घोषणा BLT_S3TY                0x0C4C
#घोषणा BLT_S3XY                0x0C50
#घोषणा BLT_S3SZ                0x0C54
#घोषणा BLT_FCTL                0x0C68
#घोषणा BLT_RSF                 0x0C70
#घोषणा BLT_RZI                 0x0C74
#घोषणा BLT_HFP                 0x0C78
#घोषणा BLT_VFP                 0x0C7C
#घोषणा BLT_Y_RSF               0x0C80
#घोषणा BLT_Y_RZI               0x0C84
#घोषणा BLT_Y_HFP               0x0C88
#घोषणा BLT_Y_VFP               0x0C8C
#घोषणा BLT_IVMX0               0x0CC0
#घोषणा BLT_IVMX1               0x0CC4
#घोषणा BLT_IVMX2               0x0CC8
#घोषणा BLT_IVMX3               0x0CCC
#घोषणा BLT_OVMX0               0x0CD0
#घोषणा BLT_OVMX1               0x0CD4
#घोषणा BLT_OVMX2               0x0CD8
#घोषणा BLT_OVMX3               0x0CDC
#घोषणा BLT_DEI                 0x0CEC
/* HW रेजिस्टरs : filters */
#घोषणा BLT_HFC_N               0x0D00
#घोषणा BLT_VFC_N               0x0D90
#घोषणा BLT_Y_HFC_N             0x0E00
#घोषणा BLT_Y_VFC_N             0x0E90
#घोषणा BLT_NB_H_COEF           16
#घोषणा BLT_NB_V_COEF           10

/* Registers values */
#घोषणा BLT_CTL_RESET           BIT(31)         /* Global soft reset */

#घोषणा BLT_ITS_AQ1_LNA         BIT(12)         /* AQ1 LNA reached */

#घोषणा BLT_STA1_IDLE           BIT(0)          /* BDISP idle */

#घोषणा BLT_AQ1_CTL_CFG         0x80400003      /* Enable, P3, LNA reached */

#घोषणा BLT_INS_S1_MASK         (BIT(0) | BIT(1) | BIT(2))
#घोषणा BLT_INS_S1_OFF          0x00000000      /* src1 disabled */
#घोषणा BLT_INS_S1_MEM          0x00000001      /* src1 fetched from memory */
#घोषणा BLT_INS_S1_CF           0x00000003      /* src1 color fill */
#घोषणा BLT_INS_S1_COPY         0x00000004      /* src1 direct copy */
#घोषणा BLT_INS_S1_FILL         0x00000007      /* src1 firect fill */
#घोषणा BLT_INS_S2_MASK         (BIT(3) | BIT(4))
#घोषणा BLT_INS_S2_OFF          0x00000000      /* src2 disabled */
#घोषणा BLT_INS_S2_MEM          0x00000008      /* src2 fetched from memory */
#घोषणा BLT_INS_S2_CF           0x00000018      /* src2 color fill */
#घोषणा BLT_INS_S3_MASK         BIT(5)
#घोषणा BLT_INS_S3_OFF          0x00000000      /* src3 disabled */
#घोषणा BLT_INS_S3_MEM          0x00000020      /* src3 fetched from memory */
#घोषणा BLT_INS_IVMX            BIT(6)          /* Input versatile matrix */
#घोषणा BLT_INS_CLUT            BIT(7)          /* Color Look Up Table */
#घोषणा BLT_INS_SCALE           BIT(8)          /* Scaling */
#घोषणा BLT_INS_FLICK           BIT(9)          /* Flicker filter */
#घोषणा BLT_INS_CLIP            BIT(10)         /* Clipping */
#घोषणा BLT_INS_CKEY            BIT(11)         /* Color key */
#घोषणा BLT_INS_OVMX            BIT(12)         /* Output versatile matrix */
#घोषणा BLT_INS_DEI             BIT(13)         /* Deपूर्णांकerlace */
#घोषणा BLT_INS_PMASK           BIT(14)         /* Plane mask */
#घोषणा BLT_INS_VC1R            BIT(17)         /* VC1 Range mapping */
#घोषणा BLT_INS_ROTATE          BIT(18)         /* Rotation */
#घोषणा BLT_INS_GRAD            BIT(19)         /* Gradient fill */
#घोषणा BLT_INS_AQLOCK          BIT(29)         /* AQ lock */
#घोषणा BLT_INS_PACE            BIT(30)         /* Pace करोwn */
#घोषणा BLT_INS_IRQ             BIT(31)         /* Raise IRQ when node करोne */
#घोषणा BLT_CIC_ALL_GRP         0x000FDFFC      /* all valid groups present */
#घोषणा BLT_ACK_BYPASS_S2S3     0x00000007      /* Bypass src2 and src3 */

#घोषणा BLT_TTY_COL_SHIFT       16              /* Color क्रमmat */
#घोषणा BLT_TTY_COL_MASK        0x001F0000      /* Color क्रमmat mask */
#घोषणा BLT_TTY_ALPHA_R         BIT(21)         /* Alpha range */
#घोषणा BLT_TTY_CR_NOT_CB       BIT(22)         /* CR not Cb */
#घोषणा BLT_TTY_MB              BIT(23)         /* MB frame / field*/
#घोषणा BLT_TTY_HSO             BIT(24)         /* H scan order */
#घोषणा BLT_TTY_VSO             BIT(25)         /* V scan order */
#घोषणा BLT_TTY_DITHER          BIT(26)         /* Dithering */
#घोषणा BLT_TTY_CHROMA          BIT(27)         /* Write chroma / luma */
#घोषणा BLT_TTY_BIG_END         BIT(30)         /* Big endianness */

#घोषणा BLT_S1TY_A1_SUBSET      BIT(22)         /* A1 subset */
#घोषणा BLT_S1TY_CHROMA_EXT     BIT(26)         /* Chroma Extended */
#घोषणा BTL_S1TY_SUBBYTE        BIT(28)         /* Sub-byte fmt, pixel order */
#घोषणा BLT_S1TY_RGB_EXP        BIT(29)         /* RGB expansion mode */

#घोषणा BLT_S2TY_A1_SUBSET      BIT(22)         /* A1 subset */
#घोषणा BLT_S2TY_CHROMA_EXT     BIT(26)         /* Chroma Extended */
#घोषणा BTL_S2TY_SUBBYTE        BIT(28)         /* Sub-byte fmt, pixel order */
#घोषणा BLT_S2TY_RGB_EXP        BIT(29)         /* RGB expansion mode */

#घोषणा BLT_S3TY_BLANK_ACC      BIT(26)         /* Blank access */

#घोषणा BLT_FCTL_HV_SCALE       0x00000055      /* H/V resize + color filter */
#घोषणा BLT_FCTL_Y_HV_SCALE     0x33000000      /* Luma version */

#घोषणा BLT_FCTL_HV_SAMPLE      0x00000044      /* H/V resize */
#घोषणा BLT_FCTL_Y_HV_SAMPLE    0x22000000      /* Luma version */

#घोषणा BLT_RZI_DEFAULT         0x20003000      /* H/VNB_repeat = 3/2 */

/* Color क्रमmat */
#घोषणा BDISP_RGB565            0x00            /* RGB565 */
#घोषणा BDISP_RGB888            0x01            /* RGB888 */
#घोषणा BDISP_XRGB8888          0x02            /* RGB888_32 */
#घोषणा BDISP_ARGB8888          0x05            /* ARGB888 */
#घोषणा BDISP_NV12              0x16            /* YCbCr42x R2B */
#घोषणा BDISP_YUV_3B            0x1E            /* YUV (3 buffer) */
