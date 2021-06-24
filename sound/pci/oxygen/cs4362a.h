<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* रेजिस्टर 01h */
#घोषणा CS4362A_PDN		0x01
#घोषणा CS4362A_DAC1_DIS	0x02
#घोषणा CS4362A_DAC2_DIS	0x04
#घोषणा CS4362A_DAC3_DIS	0x08
#घोषणा CS4362A_MCLKDIV		0x20
#घोषणा CS4362A_FREEZE		0x40
#घोषणा CS4362A_CPEN		0x80
/* रेजिस्टर 02h */
#घोषणा CS4362A_DIF_MASK	0x70
#घोषणा CS4362A_DIF_LJUST	0x00
#घोषणा CS4362A_DIF_I2S		0x10
#घोषणा CS4362A_DIF_RJUST_16	0x20
#घोषणा CS4362A_DIF_RJUST_24	0x30
#घोषणा CS4362A_DIF_RJUST_20	0x40
#घोषणा CS4362A_DIF_RJUST_18	0x50
/* रेजिस्टर 03h */
#घोषणा CS4362A_MUTEC_MASK	0x03
#घोषणा CS4362A_MUTEC_6		0x00
#घोषणा CS4362A_MUTEC_1		0x01
#घोषणा CS4362A_MUTEC_3		0x03
#घोषणा CS4362A_AMUTE		0x04
#घोषणा CS4362A_MUTEC_POL	0x08
#घोषणा CS4362A_RMP_UP		0x10
#घोषणा CS4362A_SNGLVOL		0x20
#घोषणा CS4362A_ZERO_CROSS	0x40
#घोषणा CS4362A_SOFT_RAMP	0x80
/* रेजिस्टर 04h */
#घोषणा CS4362A_RMP_DN		0x01
#घोषणा CS4362A_DEM_MASK	0x06
#घोषणा CS4362A_DEM_NONE	0x00
#घोषणा CS4362A_DEM_44100	0x02
#घोषणा CS4362A_DEM_48000	0x04
#घोषणा CS4362A_DEM_32000	0x06
#घोषणा CS4362A_FILT_SEL	0x10
/* रेजिस्टर 05h */
#घोषणा CS4362A_INV_A1		0x01
#घोषणा CS4362A_INV_B1		0x02
#घोषणा CS4362A_INV_A2		0x04
#घोषणा CS4362A_INV_B2		0x08
#घोषणा CS4362A_INV_A3		0x10
#घोषणा CS4362A_INV_B3		0x20
/* रेजिस्टर 06h */
#घोषणा CS4362A_FM_MASK		0x03
#घोषणा CS4362A_FM_SINGLE	0x00
#घोषणा CS4362A_FM_DOUBLE	0x01
#घोषणा CS4362A_FM_QUAD		0x02
#घोषणा CS4362A_FM_DSD		0x03
#घोषणा CS4362A_ATAPI_MASK	0x7c
#घोषणा CS4362A_ATAPI_B_MUTE	0x00
#घोषणा CS4362A_ATAPI_B_R	0x04
#घोषणा CS4362A_ATAPI_B_L	0x08
#घोषणा CS4362A_ATAPI_B_LR	0x0c
#घोषणा CS4362A_ATAPI_A_MUTE	0x00
#घोषणा CS4362A_ATAPI_A_R	0x10
#घोषणा CS4362A_ATAPI_A_L	0x20
#घोषणा CS4362A_ATAPI_A_LR	0x30
#घोषणा CS4362A_ATAPI_MIX_LR_VOL 0x40
#घोषणा CS4362A_A_EQ_B		0x80
/* रेजिस्टर 07h */
#घोषणा CS4362A_VOL_MASK		0x7f
#घोषणा CS4362A_MUTE			0x80
/* रेजिस्टर 08h: like 07h */
/* रेजिस्टरs 09h..0Bh: like 06h..08h */
/* रेजिस्टरs 0Ch..0Eh: like 06h..08h */
/* रेजिस्टर 12h */
#घोषणा CS4362A_REV_MASK	0x07
#घोषणा CS4362A_PART_MASK	0xf8
#घोषणा CS4362A_PART_CS4362A	0x50
