<शैली गुरु>
/*
 * Copyright 2007-2008 Nouveau Project
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the next
 * paragraph) shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */

#अगर_अघोषित __NOUVEAU_DISPBIOS_H__
#घोषणा __NOUVEAU_DISPBIOS_H__

#घोषणा DCB_MAX_NUM_ENTRIES 16
#घोषणा DCB_MAX_NUM_I2C_ENTRIES 16
#घोषणा DCB_MAX_NUM_GPIO_ENTRIES 32
#घोषणा DCB_MAX_NUM_CONNECTOR_ENTRIES 16

#घोषणा DCB_LOC_ON_CHIP 0

#घोषणा ROM16(x) get_unaligned_le16(&(x))
#घोषणा ROM32(x) get_unaligned_le32(&(x))
#घोषणा ROMPTR(d,x) (अणु            \
	काष्ठा nouveau_drm *drm = nouveau_drm((d)); \
	ROM16(x) ? &drm->vbios.data[ROM16(x)] : शून्य; \
पूर्ण)

काष्ठा bit_entry अणु
	uपूर्णांक8_t  id;
	uपूर्णांक8_t  version;
	uपूर्णांक16_t length;
	uपूर्णांक16_t offset;
	uपूर्णांक8_t *data;
पूर्ण;

पूर्णांक bit_table(काष्ठा drm_device *, u8 id, काष्ठा bit_entry *);

#समावेश <subdev/bios/dcb.h>
#समावेश <subdev/bios/conn.h>

काष्ठा dcb_table अणु
	uपूर्णांक8_t version;
	पूर्णांक entries;
	काष्ठा dcb_output entry[DCB_MAX_NUM_ENTRIES];
पूर्ण;

क्रमागत nouveau_or अणु
	DCB_OUTPUT_A = (1 << 0),
	DCB_OUTPUT_B = (1 << 1),
	DCB_OUTPUT_C = (1 << 2)
पूर्ण;

क्रमागत LVDS_script अणु
	/* Order *करोes* matter here */
	LVDS_INIT = 1,
	LVDS_RESET,
	LVDS_BACKLIGHT_ON,
	LVDS_BACKLIGHT_OFF,
	LVDS_PANEL_ON,
	LVDS_PANEL_OFF
पूर्ण;

काष्ठा nvbios अणु
	काष्ठा drm_device *dev;
	क्रमागत अणु
		NVBIOS_BMP,
		NVBIOS_BIT
	पूर्ण type;
	uपूर्णांक16_t offset;
	uपूर्णांक32_t length;
	uपूर्णांक8_t *data;

	uपूर्णांक8_t chip_version;

	uपूर्णांक32_t dactestval;
	uपूर्णांक32_t tvdactestval;
	uपूर्णांक8_t digital_min_front_porch;
	bool fp_no_ddc;

	spinlock_t lock;

	bool execute;

	uपूर्णांक8_t major_version;
	uपूर्णांक8_t feature_byte;
	bool is_mobile;

	uपूर्णांक32_t fmaxvco, fminvco;

	bool old_style_init;
	uपूर्णांक16_t init_script_tbls_ptr;
	uपूर्णांक16_t extra_init_script_tbl_ptr;

	uपूर्णांक16_t ram_restrict_tbl_ptr;
	uपूर्णांक8_t ram_restrict_group_count;

	काष्ठा dcb_table dcb;

	काष्ठा अणु
		पूर्णांक crtchead;
	पूर्ण state;

	काष्ठा अणु
		uपूर्णांक16_t fptablepoपूर्णांकer;	/* also used by पंचांगds */
		uपूर्णांक16_t fpxlatetableptr;
		पूर्णांक xlatwidth;
		uपूर्णांक16_t lvdsmanufacturerpoपूर्णांकer;
		uपूर्णांक16_t fpxlatemanufacturertableptr;
		uपूर्णांक16_t mode_ptr;
		uपूर्णांक16_t xlated_entry;
		bool घातer_off_क्रम_reset;
		bool reset_after_pclk_change;
		bool dual_link;
		bool link_c_increment;
		bool अगर_is_24bit;
		पूर्णांक duallink_transition_clk;
		uपूर्णांक8_t strapless_is_24bit;
		uपूर्णांक8_t *edid;

		/* will need resetting after suspend */
		पूर्णांक last_script_invoc;
		bool lvds_init_run;
	पूर्ण fp;

	काष्ठा अणु
		uपूर्णांक16_t output0_script_ptr;
		uपूर्णांक16_t output1_script_ptr;
	पूर्ण पंचांगds;

	काष्ठा अणु
		uपूर्णांक16_t mem_init_tbl_ptr;
		uपूर्णांक16_t sdr_seq_tbl_ptr;
		uपूर्णांक16_t ddr_seq_tbl_ptr;

		काष्ठा अणु
			uपूर्णांक8_t crt, tv, panel;
		पूर्ण i2c_indices;

		uपूर्णांक16_t lvds_single_a_script_ptr;
	पूर्ण legacy;
पूर्ण;

व्योम *olddcb_table(काष्ठा drm_device *);
व्योम *olddcb_outp(काष्ठा drm_device *, u8 idx);
पूर्णांक olddcb_outp_क्रमeach(काष्ठा drm_device *, व्योम *data,
		     पूर्णांक (*)(काष्ठा drm_device *, व्योम *, पूर्णांक idx, u8 *outp));
u8 *olddcb_conntab(काष्ठा drm_device *);
u8 *olddcb_conn(काष्ठा drm_device *, u8 idx);

पूर्णांक nouveau_bios_init(काष्ठा drm_device *);
व्योम nouveau_bios_takeकरोwn(काष्ठा drm_device *dev);
पूर्णांक nouveau_run_vbios_init(काष्ठा drm_device *);
काष्ठा dcb_connector_table_entry *
nouveau_bios_connector_entry(काष्ठा drm_device *, पूर्णांक index);
bool nouveau_bios_fp_mode(काष्ठा drm_device *, काष्ठा drm_display_mode *);
uपूर्णांक8_t *nouveau_bios_embedded_edid(काष्ठा drm_device *);
पूर्णांक nouveau_bios_parse_lvds_table(काष्ठा drm_device *, पूर्णांक pxclk,
					 bool *dl, bool *अगर_is_24bit);
पूर्णांक run_पंचांगds_table(काष्ठा drm_device *, काष्ठा dcb_output *,
			  पूर्णांक head, पूर्णांक pxclk);
पूर्णांक call_lvds_script(काष्ठा drm_device *, काष्ठा dcb_output *, पूर्णांक head,
			    क्रमागत LVDS_script, पूर्णांक pxclk);

#पूर्ण_अगर
