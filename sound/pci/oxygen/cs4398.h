<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* रेजिस्टर 1 */
#घोषणा CS4398_REV_MASK		0x07
#घोषणा CS4398_PART_MASK	0xf8
#घोषणा CS4398_PART_CS4398	0x70
/* रेजिस्टर 2 */
#घोषणा CS4398_FM_MASK		0x03
#घोषणा CS4398_FM_SINGLE	0x00
#घोषणा CS4398_FM_DOUBLE	0x01
#घोषणा CS4398_FM_QUAD		0x02
#घोषणा CS4398_FM_DSD		0x03
#घोषणा CS4398_DEM_MASK		0x0c
#घोषणा CS4398_DEM_NONE		0x00
#घोषणा CS4398_DEM_44100	0x04
#घोषणा CS4398_DEM_48000	0x08
#घोषणा CS4398_DEM_32000	0x0c
#घोषणा CS4398_DIF_MASK		0x70
#घोषणा CS4398_DIF_LJUST	0x00
#घोषणा CS4398_DIF_I2S		0x10
#घोषणा CS4398_DIF_RJUST_16	0x20
#घोषणा CS4398_DIF_RJUST_24	0x30
#घोषणा CS4398_DIF_RJUST_20	0x40
#घोषणा CS4398_DIF_RJUST_18	0x50
#घोषणा CS4398_DSD_SRC		0x80
/* रेजिस्टर 3 */
#घोषणा CS4398_ATAPI_MASK	0x1f
#घोषणा CS4398_ATAPI_B_MUTE	0x00
#घोषणा CS4398_ATAPI_B_R	0x01
#घोषणा CS4398_ATAPI_B_L	0x02
#घोषणा CS4398_ATAPI_B_LR	0x03
#घोषणा CS4398_ATAPI_A_MUTE	0x00
#घोषणा CS4398_ATAPI_A_R	0x04
#घोषणा CS4398_ATAPI_A_L	0x08
#घोषणा CS4398_ATAPI_A_LR	0x0c
#घोषणा CS4398_ATAPI_MIX_LR_VOL	0x10
#घोषणा CS4398_INVERT_B		0x20
#घोषणा CS4398_INVERT_A		0x40
#घोषणा CS4398_VOL_B_EQ_A	0x80
/* रेजिस्टर 4 */
#घोषणा CS4398_MUTEP_MASK	0x03
#घोषणा CS4398_MUTEP_AUTO	0x00
#घोषणा CS4398_MUTEP_LOW	0x02
#घोषणा CS4398_MUTEP_HIGH	0x03
#घोषणा CS4398_MUTE_B		0x08
#घोषणा CS4398_MUTE_A		0x10
#घोषणा CS4398_MUTEC_A_EQ_B	0x20
#घोषणा CS4398_DAMUTE		0x40
#घोषणा CS4398_PAMUTE		0x80
/* रेजिस्टर 5 */
#घोषणा CS4398_VOL_A_MASK	0xff
/* रेजिस्टर 6 */
#घोषणा CS4398_VOL_B_MASK	0xff
/* रेजिस्टर 7 */
#घोषणा CS4398_सूची_DSD		0x01
#घोषणा CS4398_FILT_SEL		0x04
#घोषणा CS4398_RMP_DN		0x10
#घोषणा CS4398_RMP_UP		0x20
#घोषणा CS4398_ZERO_CROSS	0x40
#घोषणा CS4398_SOFT_RAMP	0x80
/* रेजिस्टर 8 */
#घोषणा CS4398_MCLKDIV3		0x08
#घोषणा CS4398_MCLKDIV2		0x10
#घोषणा CS4398_FREEZE		0x20
#घोषणा CS4398_CPEN		0x40
#घोषणा CS4398_PDN		0x80
/* रेजिस्टर 9 */
#घोषणा CS4398_DSD_PM_EN	0x01
#घोषणा CS4398_DSD_PM_MODE	0x02
#घोषणा CS4398_INVALID_DSD	0x04
#घोषणा CS4398_STATIC_DSD	0x08
