<शैली गुरु>
/*
 * Copyright 2010 Advanced Micro Devices, Inc.
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE COPYRIGHT HOLDER(S) OR AUTHOR(S) BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * Authors: Alex Deucher
 */
#अगर_अघोषित _BTCD_H_
#घोषणा _BTCD_H_

/* pm रेजिस्टरs */

#घोषणा GENERAL_PWRMGT                                  0x63c
#       define GLOBAL_PWRMGT_EN                         (1 << 0)
#       define STATIC_PM_EN                             (1 << 1)
#       define THERMAL_PROTECTION_DIS                   (1 << 2)
#       define THERMAL_PROTECTION_TYPE                  (1 << 3)
#       define ENABLE_GEN2PCIE                          (1 << 4)
#       define ENABLE_GEN2XSP                           (1 << 5)
#       define SW_SMIO_INDEX(x)                         ((x) << 6)
#       define SW_SMIO_INDEX_MASK                       (3 << 6)
#       define SW_SMIO_INDEX_SHIFT                      6
#       define LOW_VOLT_D2_ACPI                         (1 << 8)
#       define LOW_VOLT_D3_ACPI                         (1 << 9)
#       define VOLT_PWRMGT_EN                           (1 << 10)
#       define BACKBIAS_PAD_EN                          (1 << 18)
#       define BACKBIAS_VALUE                           (1 << 19)
#       define DYN_SPREAD_SPECTRUM_EN                   (1 << 23)
#       define AC_DC_SW                                 (1 << 24)

#घोषणा TARGET_AND_CURRENT_PROखाता_INDEX                  0x66c
#       define CURRENT_PROखाता_INDEX_MASK                 (0xf << 4)
#       define CURRENT_PROखाता_INDEX_SHIFT                4

#घोषणा	CG_BIF_REQ_AND_RSP				0x7f4
#घोषणा		CG_CLIENT_REQ(x)			((x) << 0)
#घोषणा		CG_CLIENT_REQ_MASK			(0xff << 0)
#घोषणा		CG_CLIENT_REQ_SHIFT			0
#घोषणा		CG_CLIENT_RESP(x)			((x) << 8)
#घोषणा		CG_CLIENT_RESP_MASK			(0xff << 8)
#घोषणा		CG_CLIENT_RESP_SHIFT			8
#घोषणा		CLIENT_CG_REQ(x)			((x) << 16)
#घोषणा		CLIENT_CG_REQ_MASK			(0xff << 16)
#घोषणा		CLIENT_CG_REQ_SHIFT			16
#घोषणा		CLIENT_CG_RESP(x)			((x) << 24)
#घोषणा		CLIENT_CG_RESP_MASK			(0xff << 24)
#घोषणा		CLIENT_CG_RESP_SHIFT			24

#घोषणा	SCLK_PSKIP_CNTL					0x8c0
#घोषणा		PSKIP_ON_ALLOW_STOP_HI(x)		((x) << 16)
#घोषणा		PSKIP_ON_ALLOW_STOP_HI_MASK		(0xff << 16)
#घोषणा		PSKIP_ON_ALLOW_STOP_HI_SHIFT		16

#घोषणा	CG_ULV_CONTROL					0x8c8
#घोषणा	CG_ULV_PARAMETER				0x8cc

#घोषणा	MC_ARB_DRAM_TIMING				0x2774
#घोषणा	MC_ARB_DRAM_TIMING2				0x2778

#घोषणा	MC_ARB_RFSH_RATE				0x27b0
#घोषणा		POWERMODE0(x)				((x) << 0)
#घोषणा		POWERMODE0_MASK				(0xff << 0)
#घोषणा		POWERMODE0_SHIFT			0
#घोषणा		POWERMODE1(x)				((x) << 8)
#घोषणा		POWERMODE1_MASK				(0xff << 8)
#घोषणा		POWERMODE1_SHIFT			8
#घोषणा		POWERMODE2(x)				((x) << 16)
#घोषणा		POWERMODE2_MASK				(0xff << 16)
#घोषणा		POWERMODE2_SHIFT			16
#घोषणा		POWERMODE3(x)				((x) << 24)
#घोषणा		POWERMODE3_MASK				(0xff << 24)
#घोषणा		POWERMODE3_SHIFT			24

#घोषणा MC_ARB_BURST_TIME                               0x2808
#घोषणा		STATE0(x)				((x) << 0)
#घोषणा		STATE0_MASK				(0x1f << 0)
#घोषणा		STATE0_SHIFT				0
#घोषणा		STATE1(x)				((x) << 5)
#घोषणा		STATE1_MASK				(0x1f << 5)
#घोषणा		STATE1_SHIFT				5
#घोषणा		STATE2(x)				((x) << 10)
#घोषणा		STATE2_MASK				(0x1f << 10)
#घोषणा		STATE2_SHIFT				10
#घोषणा		STATE3(x)				((x) << 15)
#घोषणा		STATE3_MASK				(0x1f << 15)
#घोषणा		STATE3_SHIFT				15

#घोषणा MC_SEQ_RAS_TIMING                               0x28a0
#घोषणा MC_SEQ_CAS_TIMING                               0x28a4
#घोषणा MC_SEQ_MISC_TIMING                              0x28a8
#घोषणा MC_SEQ_MISC_TIMING2                             0x28ac

#घोषणा MC_SEQ_RD_CTL_D0                                0x28b4
#घोषणा MC_SEQ_RD_CTL_D1                                0x28b8
#घोषणा MC_SEQ_WR_CTL_D0                                0x28bc
#घोषणा MC_SEQ_WR_CTL_D1                                0x28c0

#घोषणा MC_PMG_AUTO_CFG                                 0x28d4

#घोषणा MC_SEQ_STATUS_M                                 0x29f4
#       define PMG_PWRSTATE                             (1 << 16)

#घोषणा MC_SEQ_MISC0                                    0x2a00
#घोषणा         MC_SEQ_MISC0_GDDR5_SHIFT                28
#घोषणा         MC_SEQ_MISC0_GDDR5_MASK                 0xf0000000
#घोषणा         MC_SEQ_MISC0_GDDR5_VALUE                5
#घोषणा MC_SEQ_MISC1                                    0x2a04
#घोषणा MC_SEQ_RESERVE_M                                0x2a08
#घोषणा MC_PMG_CMD_EMRS                                 0x2a0c

#घोषणा MC_SEQ_MISC3                                    0x2a2c

#घोषणा MC_SEQ_MISC5                                    0x2a54
#घोषणा MC_SEQ_MISC6                                    0x2a58

#घोषणा MC_SEQ_MISC7                                    0x2a64

#घोषणा MC_SEQ_CG                                       0x2a68
#घोषणा		CG_SEQ_REQ(x)				((x) << 0)
#घोषणा		CG_SEQ_REQ_MASK				(0xff << 0)
#घोषणा		CG_SEQ_REQ_SHIFT			0
#घोषणा		CG_SEQ_RESP(x)				((x) << 8)
#घोषणा		CG_SEQ_RESP_MASK			(0xff << 8)
#घोषणा		CG_SEQ_RESP_SHIFT			8
#घोषणा		SEQ_CG_REQ(x)				((x) << 16)
#घोषणा		SEQ_CG_REQ_MASK				(0xff << 16)
#घोषणा		SEQ_CG_REQ_SHIFT			16
#घोषणा		SEQ_CG_RESP(x)				((x) << 24)
#घोषणा		SEQ_CG_RESP_MASK			(0xff << 24)
#घोषणा		SEQ_CG_RESP_SHIFT			24
#घोषणा MC_SEQ_RAS_TIMING_LP                            0x2a6c
#घोषणा MC_SEQ_CAS_TIMING_LP                            0x2a70
#घोषणा MC_SEQ_MISC_TIMING_LP                           0x2a74
#घोषणा MC_SEQ_MISC_TIMING2_LP                          0x2a78
#घोषणा MC_SEQ_WR_CTL_D0_LP                             0x2a7c
#घोषणा MC_SEQ_WR_CTL_D1_LP                             0x2a80
#घोषणा MC_SEQ_PMG_CMD_EMRS_LP                          0x2a84
#घोषणा MC_SEQ_PMG_CMD_MRS_LP                           0x2a88

#घोषणा MC_PMG_CMD_MRS                                  0x2aac

#घोषणा MC_SEQ_RD_CTL_D0_LP                             0x2b1c
#घोषणा MC_SEQ_RD_CTL_D1_LP                             0x2b20

#घोषणा MC_PMG_CMD_MRS1                                 0x2b44
#घोषणा MC_SEQ_PMG_CMD_MRS1_LP                          0x2b48

#घोषणा	LB_SYNC_RESET_SEL				0x6b28
#घोषणा		LB_SYNC_RESET_SEL_MASK			(3 << 0)
#घोषणा		LB_SYNC_RESET_SEL_SHIFT			0

/* PCIE link stuff */
#घोषणा PCIE_LC_SPEED_CNTL                                0xa4 /* PCIE_P */
#       define LC_GEN2_EN_STRAP                           (1 << 0)
#       define LC_TARGET_LINK_SPEED_OVERRIDE_EN           (1 << 1)
#       define LC_FORCE_EN_HW_SPEED_CHANGE                (1 << 5)
#       define LC_FORCE_DIS_HW_SPEED_CHANGE               (1 << 6)
#       define LC_SPEED_CHANGE_ATTEMPTS_ALLOWED_MASK      (0x3 << 8)
#       define LC_SPEED_CHANGE_ATTEMPTS_ALLOWED_SHIFT     3
#       define LC_CURRENT_DATA_RATE                       (1 << 11)
#       define LC_HW_VOLTAGE_IF_CONTROL(x)                ((x) << 12)
#       define LC_HW_VOLTAGE_IF_CONTROL_MASK              (3 << 12)
#       define LC_HW_VOLTAGE_IF_CONTROL_SHIFT             12
#       define LC_VOLTAGE_TIMER_SEL_MASK                  (0xf << 14)
#       define LC_CLR_FAILED_SPD_CHANGE_CNT               (1 << 21)
#       define LC_OTHER_SIDE_EVER_SENT_GEN2               (1 << 23)
#       define LC_OTHER_SIDE_SUPPORTS_GEN2                (1 << 24)

#पूर्ण_अगर
