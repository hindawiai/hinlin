<शैली गुरु>
/*
 * Copyright 2005-2006 Erik Waling
 * Copyright 2006 Stephane Marchesin
 * Copyright 2007-2009 Stuart Bennett
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
 * THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF
 * OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#समावेश "nouveau_drv.h"
#समावेश "nouveau_reg.h"
#समावेश "dispnv04/hw.h"
#समावेश "nouveau_encoder.h"

#समावेश <linux/io-mapping.h>
#समावेश <linux/firmware.h>

/* these defines are made up */
#घोषणा NV_CIO_CRE_44_HEADA 0x0
#घोषणा NV_CIO_CRE_44_HEADB 0x3
#घोषणा FEATURE_MOBILE 0x10	/* also FEATURE_QUADRO क्रम BMP */

#घोषणा EDID1_LEN 128

#घोषणा BIOSLOG(sip, fmt, arg...) NV_DEBUG(sip->dev, fmt, ##arg)
#घोषणा LOG_OLD_VALUE(x)

काष्ठा init_exec अणु
	bool execute;
	bool repeat;
पूर्ण;

अटल bool nv_cksum(स्थिर uपूर्णांक8_t *data, अचिन्हित पूर्णांक length)
अणु
	/*
	 * There's a few checksums in the BIOS, so here's a generic checking
	 * function.
	 */
	पूर्णांक i;
	uपूर्णांक8_t sum = 0;

	क्रम (i = 0; i < length; i++)
		sum += data[i];

	अगर (sum)
		वापस true;

	वापस false;
पूर्ण

अटल uपूर्णांक16_t clkcmptable(काष्ठा nvbios *bios, uपूर्णांक16_t clktable, पूर्णांक pxclk)
अणु
	पूर्णांक compare_record_len, i = 0;
	uपूर्णांक16_t compareclk, scriptptr = 0;

	अगर (bios->major_version < 5) /* pre BIT */
		compare_record_len = 3;
	अन्यथा
		compare_record_len = 4;

	करो अणु
		compareclk = ROM16(bios->data[clktable + compare_record_len * i]);
		अगर (pxclk >= compareclk * 10) अणु
			अगर (bios->major_version < 5) अणु
				uपूर्णांक8_t पंचांगdssub = bios->data[clktable + 2 + compare_record_len * i];
				scriptptr = ROM16(bios->data[bios->init_script_tbls_ptr + पंचांगdssub * 2]);
			पूर्ण अन्यथा
				scriptptr = ROM16(bios->data[clktable + 2 + compare_record_len * i]);
			अवरोध;
		पूर्ण
		i++;
	पूर्ण जबतक (compareclk);

	वापस scriptptr;
पूर्ण

अटल व्योम
run_digital_op_script(काष्ठा drm_device *dev, uपूर्णांक16_t scriptptr,
		      काष्ठा dcb_output *dcbent, पूर्णांक head, bool dl)
अणु
	काष्ठा nouveau_drm *drm = nouveau_drm(dev);

	NV_INFO(drm, "0x%04X: Parsing digital output script table\n",
		 scriptptr);
	NVWriteVgaCrtc(dev, 0, NV_CIO_CRE_44, head ? NV_CIO_CRE_44_HEADB :
					         NV_CIO_CRE_44_HEADA);
	nouveau_bios_run_init_table(dev, scriptptr, dcbent, head);

	nv04_dfp_bind_head(dev, dcbent, head, dl);
पूर्ण

अटल पूर्णांक call_lvds_manufacturer_script(काष्ठा drm_device *dev, काष्ठा dcb_output *dcbent, पूर्णांक head, क्रमागत LVDS_script script)
अणु
	काष्ठा nouveau_drm *drm = nouveau_drm(dev);
	काष्ठा nvbios *bios = &drm->vbios;
	uपूर्णांक8_t sub = bios->data[bios->fp.xlated_entry + script] + (bios->fp.link_c_increment && dcbent->or & DCB_OUTPUT_C ? 1 : 0);
	uपूर्णांक16_t scriptofs = ROM16(bios->data[bios->init_script_tbls_ptr + sub * 2]);
#अगर_घोषित __घातerpc__
	काष्ठा pci_dev *pdev = to_pci_dev(dev->dev);
#पूर्ण_अगर

	अगर (!bios->fp.xlated_entry || !sub || !scriptofs)
		वापस -EINVAL;

	run_digital_op_script(dev, scriptofs, dcbent, head, bios->fp.dual_link);

	अगर (script == LVDS_PANEL_OFF) अणु
		/* off-on delay in ms */
		mdelay(ROM16(bios->data[bios->fp.xlated_entry + 7]));
	पूर्ण
#अगर_घोषित __घातerpc__
	/* Powerbook specअगरic quirks */
	अगर (script == LVDS_RESET &&
	    (pdev->device == 0x0179 || pdev->device == 0x0189 ||
	     pdev->device == 0x0329))
		nv_ग_लिखो_पंचांगds(dev, dcbent->or, 0, 0x02, 0x72);
#पूर्ण_अगर

	वापस 0;
पूर्ण

अटल पूर्णांक run_lvds_table(काष्ठा drm_device *dev, काष्ठा dcb_output *dcbent, पूर्णांक head, क्रमागत LVDS_script script, पूर्णांक pxclk)
अणु
	/*
	 * The BIT LVDS table's header has the inक्रमmation to setup the
	 * necessary रेजिस्टरs. Following the standard 4 byte header are:
	 * A biपंचांगask byte and a dual-link transition pxclk value क्रम use in
	 * selecting the init script when not using straps; 4 script poपूर्णांकers
	 * क्रम panel घातer, selected by output and on/off; and 8 table poपूर्णांकers
	 * क्रम panel init, the needed one determined by output, and bits in the
	 * conf byte. These tables are similar to the TMDS tables, consisting
	 * of a list of pxclks and script poपूर्णांकers.
	 */
	काष्ठा nouveau_drm *drm = nouveau_drm(dev);
	काष्ठा nvbios *bios = &drm->vbios;
	अचिन्हित पूर्णांक outमाला_दोet = (dcbent->or == 4) ? 1 : 0;
	uपूर्णांक16_t scriptptr = 0, clktable;

	/*
	 * For now we assume version 3.0 table - g80 support will need some
	 * changes
	 */

	चयन (script) अणु
	हाल LVDS_INIT:
		वापस -ENOSYS;
	हाल LVDS_BACKLIGHT_ON:
	हाल LVDS_PANEL_ON:
		scriptptr = ROM16(bios->data[bios->fp.lvdsmanufacturerpoपूर्णांकer + 7 + outमाला_दोet * 2]);
		अवरोध;
	हाल LVDS_BACKLIGHT_OFF:
	हाल LVDS_PANEL_OFF:
		scriptptr = ROM16(bios->data[bios->fp.lvdsmanufacturerpoपूर्णांकer + 11 + outमाला_दोet * 2]);
		अवरोध;
	हाल LVDS_RESET:
		clktable = bios->fp.lvdsmanufacturerpoपूर्णांकer + 15;
		अगर (dcbent->or == 4)
			clktable += 8;

		अगर (dcbent->lvdsconf.use_straps_क्रम_mode) अणु
			अगर (bios->fp.dual_link)
				clktable += 4;
			अगर (bios->fp.अगर_is_24bit)
				clktable += 2;
		पूर्ण अन्यथा अणु
			/* using EDID */
			पूर्णांक cmpval_24bit = (dcbent->or == 4) ? 4 : 1;

			अगर (bios->fp.dual_link) अणु
				clktable += 4;
				cmpval_24bit <<= 1;
			पूर्ण

			अगर (bios->fp.strapless_is_24bit & cmpval_24bit)
				clktable += 2;
		पूर्ण

		clktable = ROM16(bios->data[clktable]);
		अगर (!clktable) अणु
			NV_ERROR(drm, "Pixel clock comparison table not found\n");
			वापस -ENOENT;
		पूर्ण
		scriptptr = clkcmptable(bios, clktable, pxclk);
	पूर्ण

	अगर (!scriptptr) अणु
		NV_ERROR(drm, "LVDS output init script not found\n");
		वापस -ENOENT;
	पूर्ण
	run_digital_op_script(dev, scriptptr, dcbent, head, bios->fp.dual_link);

	वापस 0;
पूर्ण

पूर्णांक call_lvds_script(काष्ठा drm_device *dev, काष्ठा dcb_output *dcbent, पूर्णांक head, क्रमागत LVDS_script script, पूर्णांक pxclk)
अणु
	/*
	 * LVDS operations are multiplexed in an efक्रमt to present a single API
	 * which works with two vastly dअगरfering underlying काष्ठाures.
	 * This acts as the demux
	 */

	काष्ठा nouveau_drm *drm = nouveau_drm(dev);
	काष्ठा nvअगर_object *device = &drm->client.device.object;
	काष्ठा nvbios *bios = &drm->vbios;
	uपूर्णांक8_t lvds_ver = bios->data[bios->fp.lvdsmanufacturerpoपूर्णांकer];
	uपूर्णांक32_t sel_clk_binding, sel_clk;
	पूर्णांक ret;

	अगर (bios->fp.last_script_invoc == (script << 1 | head) || !lvds_ver ||
	    (lvds_ver >= 0x30 && script == LVDS_INIT))
		वापस 0;

	अगर (!bios->fp.lvds_init_run) अणु
		bios->fp.lvds_init_run = true;
		call_lvds_script(dev, dcbent, head, LVDS_INIT, pxclk);
	पूर्ण

	अगर (script == LVDS_PANEL_ON && bios->fp.reset_after_pclk_change)
		call_lvds_script(dev, dcbent, head, LVDS_RESET, pxclk);
	अगर (script == LVDS_RESET && bios->fp.घातer_off_क्रम_reset)
		call_lvds_script(dev, dcbent, head, LVDS_PANEL_OFF, pxclk);

	NV_INFO(drm, "Calling LVDS script %d:\n", script);

	/* करोn't let script change pll->head binding */
	sel_clk_binding = nvअगर_rd32(device, NV_PRAMDAC_SEL_CLK) & 0x50000;

	अगर (lvds_ver < 0x30)
		ret = call_lvds_manufacturer_script(dev, dcbent, head, script);
	अन्यथा
		ret = run_lvds_table(dev, dcbent, head, script, pxclk);

	bios->fp.last_script_invoc = (script << 1 | head);

	sel_clk = NVReadRAMDAC(dev, 0, NV_PRAMDAC_SEL_CLK) & ~0x50000;
	NVWriteRAMDAC(dev, 0, NV_PRAMDAC_SEL_CLK, sel_clk | sel_clk_binding);
	/* some scripts set a value in NV_PBUS_POWERCTRL_2 and अवरोध video overlay */
	nvअगर_wr32(device, NV_PBUS_POWERCTRL_2, 0);

	वापस ret;
पूर्ण

काष्ठा lvdstableheader अणु
	uपूर्णांक8_t lvds_ver, headerlen, recordlen;
पूर्ण;

अटल पूर्णांक parse_lvds_manufacturer_table_header(काष्ठा drm_device *dev, काष्ठा nvbios *bios, काष्ठा lvdstableheader *lth)
अणु
	/*
	 * BMP version (0xa) LVDS table has a simple header of version and
	 * record length. The BIT LVDS table has the typical BIT table header:
	 * version byte, header length byte, record length byte, and a byte क्रम
	 * the maximum number of records that can be held in the table.
	 */

	काष्ठा nouveau_drm *drm = nouveau_drm(dev);
	uपूर्णांक8_t lvds_ver, headerlen, recordlen;

	स_रखो(lth, 0, माप(काष्ठा lvdstableheader));

	अगर (bios->fp.lvdsmanufacturerpoपूर्णांकer == 0x0) अणु
		NV_ERROR(drm, "Pointer to LVDS manufacturer table invalid\n");
		वापस -EINVAL;
	पूर्ण

	lvds_ver = bios->data[bios->fp.lvdsmanufacturerpoपूर्णांकer];

	चयन (lvds_ver) अणु
	हाल 0x0a:	/* pre NV40 */
		headerlen = 2;
		recordlen = bios->data[bios->fp.lvdsmanufacturerpoपूर्णांकer + 1];
		अवरोध;
	हाल 0x30:	/* NV4x */
		headerlen = bios->data[bios->fp.lvdsmanufacturerpoपूर्णांकer + 1];
		अगर (headerlen < 0x1f) अणु
			NV_ERROR(drm, "LVDS table header not understood\n");
			वापस -EINVAL;
		पूर्ण
		recordlen = bios->data[bios->fp.lvdsmanufacturerpoपूर्णांकer + 2];
		अवरोध;
	हाल 0x40:	/* G80/G90 */
		headerlen = bios->data[bios->fp.lvdsmanufacturerpoपूर्णांकer + 1];
		अगर (headerlen < 0x7) अणु
			NV_ERROR(drm, "LVDS table header not understood\n");
			वापस -EINVAL;
		पूर्ण
		recordlen = bios->data[bios->fp.lvdsmanufacturerpoपूर्णांकer + 2];
		अवरोध;
	शेष:
		NV_ERROR(drm,
			 "LVDS table revision %d.%d not currently supported\n",
			 lvds_ver >> 4, lvds_ver & 0xf);
		वापस -ENOSYS;
	पूर्ण

	lth->lvds_ver = lvds_ver;
	lth->headerlen = headerlen;
	lth->recordlen = recordlen;

	वापस 0;
पूर्ण

अटल पूर्णांक
get_fp_strap(काष्ठा drm_device *dev, काष्ठा nvbios *bios)
अणु
	काष्ठा nouveau_drm *drm = nouveau_drm(dev);
	काष्ठा nvअगर_object *device = &drm->client.device.object;

	/*
	 * The fp strap is normally dictated by the "User Strap" in
	 * PEXTDEV_BOOT_0[20:16], but on BMP cards when bit 2 of the
	 * Internal_Flags काष्ठा at 0x48 is set, the user strap माला_लो overriden
	 * by the PCI subप्रणाली ID during POST, but not beक्रमe the previous user
	 * strap has been committed to CR58 क्रम CR57=0xf on head A, which may be
	 * पढ़ो and used instead
	 */

	अगर (bios->major_version < 5 && bios->data[0x48] & 0x4)
		वापस NVReadVgaCrtc5758(dev, 0, 0xf) & 0xf;

	अगर (drm->client.device.info.family >= NV_DEVICE_INFO_V0_MAXWELL)
		वापस nvअगर_rd32(device, 0x001800) & 0x0000000f;
	अन्यथा
	अगर (drm->client.device.info.family >= NV_DEVICE_INFO_V0_TESLA)
		वापस (nvअगर_rd32(device, NV_PEXTDEV_BOOT_0) >> 24) & 0xf;
	अन्यथा
		वापस (nvअगर_rd32(device, NV_PEXTDEV_BOOT_0) >> 16) & 0xf;
पूर्ण

अटल पूर्णांक parse_fp_mode_table(काष्ठा drm_device *dev, काष्ठा nvbios *bios)
अणु
	काष्ठा nouveau_drm *drm = nouveau_drm(dev);
	uपूर्णांक8_t *fptable;
	uपूर्णांक8_t fptable_ver, headerlen = 0, recordlen, fpentries = 0xf, fpindex;
	पूर्णांक ret, ofs, fpstrapping;
	काष्ठा lvdstableheader lth;

	अगर (bios->fp.fptablepoपूर्णांकer == 0x0) अणु
		/* Most laptop cards lack an fp table. They use DDC. */
		NV_DEBUG(drm, "Pointer to flat panel table invalid\n");
		bios->digital_min_front_porch = 0x4b;
		वापस 0;
	पूर्ण

	fptable = &bios->data[bios->fp.fptablepoपूर्णांकer];
	fptable_ver = fptable[0];

	चयन (fptable_ver) अणु
	/*
	 * BMP version 0x5.0x11 BIOSen have version 1 like tables, but no
	 * version field, and miss one of the spपढ़ो spectrum/PWM bytes.
	 * This could affect early GF2Go parts (not seen any appropriate ROMs
	 * though). Here we assume that a version of 0x05 matches this हाल
	 * (combining with a BMP version check would be better), as the
	 * common हाल क्रम the panel type field is 0x0005, and that is in
	 * fact what we are पढ़ोing the first byte of.
	 */
	हाल 0x05:	/* some NV10, 11, 15, 16 */
		recordlen = 42;
		ofs = -1;
		अवरोध;
	हाल 0x10:	/* some NV15/16, and NV11+ */
		recordlen = 44;
		ofs = 0;
		अवरोध;
	हाल 0x20:	/* NV40+ */
		headerlen = fptable[1];
		recordlen = fptable[2];
		fpentries = fptable[3];
		/*
		 * fptable[4] is the minimum
		 * RAMDAC_FP_HCRTC -> RAMDAC_FP_HSYNC_START gap
		 */
		bios->digital_min_front_porch = fptable[4];
		ofs = -7;
		अवरोध;
	शेष:
		NV_ERROR(drm,
			 "FP table revision %d.%d not currently supported\n",
			 fptable_ver >> 4, fptable_ver & 0xf);
		वापस -ENOSYS;
	पूर्ण

	अगर (!bios->is_mobile) /* !mobile only needs digital_min_front_porch */
		वापस 0;

	ret = parse_lvds_manufacturer_table_header(dev, bios, &lth);
	अगर (ret)
		वापस ret;

	अगर (lth.lvds_ver == 0x30 || lth.lvds_ver == 0x40) अणु
		bios->fp.fpxlatetableptr = bios->fp.lvdsmanufacturerpoपूर्णांकer +
							lth.headerlen + 1;
		bios->fp.xlatwidth = lth.recordlen;
	पूर्ण
	अगर (bios->fp.fpxlatetableptr == 0x0) अणु
		NV_ERROR(drm, "Pointer to flat panel xlat table invalid\n");
		वापस -EINVAL;
	पूर्ण

	fpstrapping = get_fp_strap(dev, bios);

	fpindex = bios->data[bios->fp.fpxlatetableptr +
					fpstrapping * bios->fp.xlatwidth];

	अगर (fpindex > fpentries) अणु
		NV_ERROR(drm, "Bad flat panel table index\n");
		वापस -ENOENT;
	पूर्ण

	/* nv4x cards need both a strap value and fpindex of 0xf to use DDC */
	अगर (lth.lvds_ver > 0x10)
		bios->fp_no_ddc = fpstrapping != 0xf || fpindex != 0xf;

	/*
	 * If either the strap or xlated fpindex value are 0xf there is no
	 * panel using a strap-derived bios mode present.  this condition
	 * includes, but is dअगरferent from, the DDC panel indicator above
	 */
	अगर (fpstrapping == 0xf || fpindex == 0xf)
		वापस 0;

	bios->fp.mode_ptr = bios->fp.fptablepoपूर्णांकer + headerlen +
			    recordlen * fpindex + ofs;

	NV_INFO(drm, "BIOS FP mode: %dx%d (%dkHz pixel clock)\n",
		 ROM16(bios->data[bios->fp.mode_ptr + 11]) + 1,
		 ROM16(bios->data[bios->fp.mode_ptr + 25]) + 1,
		 ROM16(bios->data[bios->fp.mode_ptr + 7]) * 10);

	वापस 0;
पूर्ण

bool nouveau_bios_fp_mode(काष्ठा drm_device *dev, काष्ठा drm_display_mode *mode)
अणु
	काष्ठा nouveau_drm *drm = nouveau_drm(dev);
	काष्ठा nvbios *bios = &drm->vbios;
	uपूर्णांक8_t *mode_entry = &bios->data[bios->fp.mode_ptr];

	अगर (!mode)	/* just checking whether we can produce a mode */
		वापस bios->fp.mode_ptr;

	स_रखो(mode, 0, माप(काष्ठा drm_display_mode));
	/*
	 * For version 1.0 (version in byte 0):
	 * bytes 1-2 are "panel type", including bits on whether Colour/mono,
	 * single/dual link, and type (TFT etc.)
	 * bytes 3-6 are bits per colour in RGBX
	 */
	mode->घड़ी = ROM16(mode_entry[7]) * 10;
	/* bytes 9-10 is HActive */
	mode->hdisplay = ROM16(mode_entry[11]) + 1;
	/*
	 * bytes 13-14 is HValid Start
	 * bytes 15-16 is HValid End
	 */
	mode->hsync_start = ROM16(mode_entry[17]) + 1;
	mode->hsync_end = ROM16(mode_entry[19]) + 1;
	mode->htotal = ROM16(mode_entry[21]) + 1;
	/* bytes 23-24, 27-30 similarly, but vertical */
	mode->vdisplay = ROM16(mode_entry[25]) + 1;
	mode->vsync_start = ROM16(mode_entry[31]) + 1;
	mode->vsync_end = ROM16(mode_entry[33]) + 1;
	mode->vtotal = ROM16(mode_entry[35]) + 1;
	mode->flags |= (mode_entry[37] & 0x10) ?
			DRM_MODE_FLAG_PHSYNC : DRM_MODE_FLAG_NHSYNC;
	mode->flags |= (mode_entry[37] & 0x1) ?
			DRM_MODE_FLAG_PVSYNC : DRM_MODE_FLAG_NVSYNC;
	/*
	 * bytes 38-39 relate to spपढ़ो spectrum settings
	 * bytes 40-43 are something to करो with PWM
	 */

	mode->status = MODE_OK;
	mode->type = DRM_MODE_TYPE_DRIVER | DRM_MODE_TYPE_PREFERRED;
	drm_mode_set_name(mode);
	वापस bios->fp.mode_ptr;
पूर्ण

पूर्णांक nouveau_bios_parse_lvds_table(काष्ठा drm_device *dev, पूर्णांक pxclk, bool *dl, bool *अगर_is_24bit)
अणु
	/*
	 * The LVDS table header is (mostly) described in
	 * parse_lvds_manufacturer_table_header(): the BIT header additionally
	 * contains the dual-link transition pxclk (in 10s kHz), at byte 5 - अगर
	 * straps are not being used क्रम the panel, this specअगरies the frequency
	 * at which modes should be set up in the dual link style.
	 *
	 * Following the header, the BMP (ver 0xa) table has several records,
	 * indexed by a separate xlat table, indexed in turn by the fp strap in
	 * EXTDEV_BOOT. Each record had a config byte, followed by 6 script
	 * numbers क्रम use by INIT_SUB which controlled panel init and घातer,
	 * and finally a dword of ms to sleep between घातer off and on
	 * operations.
	 *
	 * In the BIT versions, the table following the header serves as an
	 * पूर्णांकegrated config and xlat table: the records in the table are
	 * indexed by the FP strap nibble in EXTDEV_BOOT, and each record has
	 * two bytes - the first as a config byte, the second क्रम indexing the
	 * fp mode table poपूर्णांकed to by the BIT 'D' table
	 *
	 * DDC is not used until after card init, so selecting the correct table
	 * entry and setting the dual link flag क्रम EDID equipped panels,
	 * requiring tests against the native-mode pixel घड़ी, cannot be करोne
	 * until later, when this function should be called with non-zero pxclk
	 */
	काष्ठा nouveau_drm *drm = nouveau_drm(dev);
	काष्ठा nvbios *bios = &drm->vbios;
	पूर्णांक fpstrapping = get_fp_strap(dev, bios), lvdsmanufacturerindex = 0;
	काष्ठा lvdstableheader lth;
	uपूर्णांक16_t lvdsofs;
	पूर्णांक ret, chip_version = bios->chip_version;

	ret = parse_lvds_manufacturer_table_header(dev, bios, &lth);
	अगर (ret)
		वापस ret;

	चयन (lth.lvds_ver) अणु
	हाल 0x0a:	/* pre NV40 */
		lvdsmanufacturerindex = bios->data[
					bios->fp.fpxlatemanufacturertableptr +
					fpstrapping];

		/* we're done if this isn't the EDID panel हाल */
		अगर (!pxclk)
			अवरोध;

		अगर (chip_version < 0x25) अणु
			/* nv17 behaviour
			 *
			 * It seems the old style lvds script poपूर्णांकer is reused
			 * to select 18/24 bit colour depth क्रम EDID panels.
			 */
			lvdsmanufacturerindex =
				(bios->legacy.lvds_single_a_script_ptr & 1) ?
									2 : 0;
			अगर (pxclk >= bios->fp.duallink_transition_clk)
				lvdsmanufacturerindex++;
		पूर्ण अन्यथा अगर (chip_version < 0x30) अणु
			/* nv28 behaviour (off-chip encoder)
			 *
			 * nv28 करोes a complex dance of first using byte 121 of
			 * the EDID to choose the lvdsmanufacturerindex, then
			 * later attempting to match the EDID manufacturer and
			 * product IDs in a table (signature 'pidt' (panel id
			 * table?)), setting an lvdsmanufacturerindex of 0 and
			 * an fp strap of the match index (or 0xf अगर none)
			 */
			lvdsmanufacturerindex = 0;
		पूर्ण अन्यथा अणु
			/* nv31, nv34 behaviour */
			lvdsmanufacturerindex = 0;
			अगर (pxclk >= bios->fp.duallink_transition_clk)
				lvdsmanufacturerindex = 2;
			अगर (pxclk >= 140000)
				lvdsmanufacturerindex = 3;
		पूर्ण

		/*
		 * nvidia set the high nibble of (cr57=f, cr58) to
		 * lvdsmanufacturerindex in this हाल; we करोn't
		 */
		अवरोध;
	हाल 0x30:	/* NV4x */
	हाल 0x40:	/* G80/G90 */
		lvdsmanufacturerindex = fpstrapping;
		अवरोध;
	शेष:
		NV_ERROR(drm, "LVDS table revision not currently supported\n");
		वापस -ENOSYS;
	पूर्ण

	lvdsofs = bios->fp.xlated_entry = bios->fp.lvdsmanufacturerpoपूर्णांकer + lth.headerlen + lth.recordlen * lvdsmanufacturerindex;
	चयन (lth.lvds_ver) अणु
	हाल 0x0a:
		bios->fp.घातer_off_क्रम_reset = bios->data[lvdsofs] & 1;
		bios->fp.reset_after_pclk_change = bios->data[lvdsofs] & 2;
		bios->fp.dual_link = bios->data[lvdsofs] & 4;
		bios->fp.link_c_increment = bios->data[lvdsofs] & 8;
		*अगर_is_24bit = bios->data[lvdsofs] & 16;
		अवरोध;
	हाल 0x30:
	हाल 0x40:
		/*
		 * No sign of the "power off for reset" or "reset क्रम panel
		 * on" bits, but it's safer to assume we should
		 */
		bios->fp.घातer_off_क्रम_reset = true;
		bios->fp.reset_after_pclk_change = true;

		/*
		 * It's ok lvdsofs is wrong क्रम nv4x edid हाल; dual_link is
		 * over-written, and अगर_is_24bit isn't used
		 */
		bios->fp.dual_link = bios->data[lvdsofs] & 1;
		bios->fp.अगर_is_24bit = bios->data[lvdsofs] & 2;
		bios->fp.strapless_is_24bit = bios->data[bios->fp.lvdsmanufacturerpoपूर्णांकer + 4];
		bios->fp.duallink_transition_clk = ROM16(bios->data[bios->fp.lvdsmanufacturerpoपूर्णांकer + 5]) * 10;
		अवरोध;
	पूर्ण

	/* set dual_link flag क्रम EDID हाल */
	अगर (pxclk && (chip_version < 0x25 || chip_version > 0x28))
		bios->fp.dual_link = (pxclk >= bios->fp.duallink_transition_clk);

	*dl = bios->fp.dual_link;

	वापस 0;
पूर्ण

पूर्णांक run_पंचांगds_table(काष्ठा drm_device *dev, काष्ठा dcb_output *dcbent, पूर्णांक head, पूर्णांक pxclk)
अणु
	/*
	 * the pxclk parameter is in kHz
	 *
	 * This runs the TMDS regs setting code found on BIT bios cards
	 *
	 * For ffs(or) == 1 use the first table, क्रम ffs(or) == 2 and
	 * ffs(or) == 3, use the second.
	 */

	काष्ठा nouveau_drm *drm = nouveau_drm(dev);
	काष्ठा nvअगर_object *device = &drm->client.device.object;
	काष्ठा nvbios *bios = &drm->vbios;
	पूर्णांक cv = bios->chip_version;
	uपूर्णांक16_t clktable = 0, scriptptr;
	uपूर्णांक32_t sel_clk_binding, sel_clk;

	/* pre-nv17 off-chip पंचांगds uses scripts, post nv17 करोesn't */
	अगर (cv >= 0x17 && cv != 0x1a && cv != 0x20 &&
	    dcbent->location != DCB_LOC_ON_CHIP)
		वापस 0;

	चयन (ffs(dcbent->or)) अणु
	हाल 1:
		clktable = bios->पंचांगds.output0_script_ptr;
		अवरोध;
	हाल 2:
	हाल 3:
		clktable = bios->पंचांगds.output1_script_ptr;
		अवरोध;
	पूर्ण

	अगर (!clktable) अणु
		NV_ERROR(drm, "Pixel clock comparison table not found\n");
		वापस -EINVAL;
	पूर्ण

	scriptptr = clkcmptable(bios, clktable, pxclk);

	अगर (!scriptptr) अणु
		NV_ERROR(drm, "TMDS output init script not found\n");
		वापस -ENOENT;
	पूर्ण

	/* करोn't let script change pll->head binding */
	sel_clk_binding = nvअगर_rd32(device, NV_PRAMDAC_SEL_CLK) & 0x50000;
	run_digital_op_script(dev, scriptptr, dcbent, head, pxclk >= 165000);
	sel_clk = NVReadRAMDAC(dev, 0, NV_PRAMDAC_SEL_CLK) & ~0x50000;
	NVWriteRAMDAC(dev, 0, NV_PRAMDAC_SEL_CLK, sel_clk | sel_clk_binding);

	वापस 0;
पूर्ण

अटल व्योम parse_script_table_poपूर्णांकers(काष्ठा nvbios *bios, uपूर्णांक16_t offset)
अणु
	/*
	 * Parses the init table segment क्रम poपूर्णांकers used in script execution.
	 *
	 * offset + 0  (16 bits): init script tables poपूर्णांकer
	 * offset + 2  (16 bits): macro index table poपूर्णांकer
	 * offset + 4  (16 bits): macro table poपूर्णांकer
	 * offset + 6  (16 bits): condition table poपूर्णांकer
	 * offset + 8  (16 bits): io condition table poपूर्णांकer
	 * offset + 10 (16 bits): io flag condition table poपूर्णांकer
	 * offset + 12 (16 bits): init function table poपूर्णांकer
	 */

	bios->init_script_tbls_ptr = ROM16(bios->data[offset]);
पूर्ण

अटल पूर्णांक parse_bit_A_tbl_entry(काष्ठा drm_device *dev, काष्ठा nvbios *bios, काष्ठा bit_entry *bitentry)
अणु
	/*
	 * Parses the load detect values क्रम g80 cards.
	 *
	 * offset + 0 (16 bits): loadval table poपूर्णांकer
	 */

	काष्ठा nouveau_drm *drm = nouveau_drm(dev);
	uपूर्णांक16_t load_table_ptr;
	uपूर्णांक8_t version, headerlen, entrylen, num_entries;

	अगर (bitentry->length != 3) अणु
		NV_ERROR(drm, "Do not understand BIT A table\n");
		वापस -EINVAL;
	पूर्ण

	load_table_ptr = ROM16(bios->data[bitentry->offset]);

	अगर (load_table_ptr == 0x0) अणु
		NV_DEBUG(drm, "Pointer to BIT loadval table invalid\n");
		वापस -EINVAL;
	पूर्ण

	version = bios->data[load_table_ptr];

	अगर (version != 0x10) अणु
		NV_ERROR(drm, "BIT loadval table version %d.%d not supported\n",
			 version >> 4, version & 0xF);
		वापस -ENOSYS;
	पूर्ण

	headerlen = bios->data[load_table_ptr + 1];
	entrylen = bios->data[load_table_ptr + 2];
	num_entries = bios->data[load_table_ptr + 3];

	अगर (headerlen != 4 || entrylen != 4 || num_entries != 2) अणु
		NV_ERROR(drm, "Do not understand BIT loadval table\n");
		वापस -EINVAL;
	पूर्ण

	/* First entry is normal dac, 2nd tv-out perhaps? */
	bios->dactestval = ROM32(bios->data[load_table_ptr + headerlen]) & 0x3ff;

	वापस 0;
पूर्ण

अटल पूर्णांक parse_bit_display_tbl_entry(काष्ठा drm_device *dev, काष्ठा nvbios *bios, काष्ठा bit_entry *bitentry)
अणु
	/*
	 * Parses the flat panel table segment that the bit entry poपूर्णांकs to.
	 * Starting at bitentry->offset:
	 *
	 * offset + 0  (16 bits): ??? table poपूर्णांकer - seems to have 18 byte
	 * records beginning with a freq.
	 * offset + 2  (16 bits): mode table poपूर्णांकer
	 */
	काष्ठा nouveau_drm *drm = nouveau_drm(dev);

	अगर (bitentry->length != 4) अणु
		NV_ERROR(drm, "Do not understand BIT display table\n");
		वापस -EINVAL;
	पूर्ण

	bios->fp.fptablepoपूर्णांकer = ROM16(bios->data[bitentry->offset + 2]);

	वापस 0;
पूर्ण

अटल पूर्णांक parse_bit_init_tbl_entry(काष्ठा drm_device *dev, काष्ठा nvbios *bios, काष्ठा bit_entry *bitentry)
अणु
	/*
	 * Parses the init table segment that the bit entry poपूर्णांकs to.
	 *
	 * See parse_script_table_poपूर्णांकers क्रम layout
	 */
	काष्ठा nouveau_drm *drm = nouveau_drm(dev);

	अगर (bitentry->length < 14) अणु
		NV_ERROR(drm, "Do not understand init table\n");
		वापस -EINVAL;
	पूर्ण

	parse_script_table_poपूर्णांकers(bios, bitentry->offset);
	वापस 0;
पूर्ण

अटल पूर्णांक parse_bit_i_tbl_entry(काष्ठा drm_device *dev, काष्ठा nvbios *bios, काष्ठा bit_entry *bitentry)
अणु
	/*
	 * BIT 'i' (info?) table
	 *
	 * offset + 0  (32 bits): BIOS version dword (as in B table)
	 * offset + 5  (8  bits): BIOS feature byte (same as क्रम BMP?)
	 * offset + 13 (16 bits): poपूर्णांकer to table containing DAC load
	 * detection comparison values
	 *
	 * There's other things in the table, purpose unknown
	 */

	काष्ठा nouveau_drm *drm = nouveau_drm(dev);
	uपूर्णांक16_t daccmpoffset;
	uपूर्णांक8_t dacver, dacheaderlen;

	अगर (bitentry->length < 6) अणु
		NV_ERROR(drm, "BIT i table too short for needed information\n");
		वापस -EINVAL;
	पूर्ण

	/*
	 * bit 4 seems to indicate a mobile bios (करोesn't suffer from BMP's
	 * Quadro identity crisis), other bits possibly as क्रम BMP feature byte
	 */
	bios->feature_byte = bios->data[bitentry->offset + 5];
	bios->is_mobile = bios->feature_byte & FEATURE_MOBILE;

	अगर (bitentry->length < 15) अणु
		NV_WARN(drm, "BIT i table not long enough for DAC load "
			       "detection comparison table\n");
		वापस -EINVAL;
	पूर्ण

	daccmpoffset = ROM16(bios->data[bitentry->offset + 13]);

	/* करोesn't exist on g80 */
	अगर (!daccmpoffset)
		वापस 0;

	/*
	 * The first value in the table, following the header, is the
	 * comparison value, the second entry is a comparison value क्रम
	 * TV load detection.
	 */

	dacver = bios->data[daccmpoffset];
	dacheaderlen = bios->data[daccmpoffset + 1];

	अगर (dacver != 0x00 && dacver != 0x10) अणु
		NV_WARN(drm, "DAC load detection comparison table version "
			       "%d.%d not known\n", dacver >> 4, dacver & 0xf);
		वापस -ENOSYS;
	पूर्ण

	bios->dactestval = ROM32(bios->data[daccmpoffset + dacheaderlen]);
	bios->tvdactestval = ROM32(bios->data[daccmpoffset + dacheaderlen + 4]);

	वापस 0;
पूर्ण

अटल पूर्णांक parse_bit_lvds_tbl_entry(काष्ठा drm_device *dev, काष्ठा nvbios *bios, काष्ठा bit_entry *bitentry)
अणु
	/*
	 * Parses the LVDS table segment that the bit entry poपूर्णांकs to.
	 * Starting at bitentry->offset:
	 *
	 * offset + 0  (16 bits): LVDS strap xlate table poपूर्णांकer
	 */

	काष्ठा nouveau_drm *drm = nouveau_drm(dev);

	अगर (bitentry->length != 2) अणु
		NV_ERROR(drm, "Do not understand BIT LVDS table\n");
		वापस -EINVAL;
	पूर्ण

	/*
	 * No idea अगर it's still called the LVDS manufacturer table, but
	 * the concept's बंद enough.
	 */
	bios->fp.lvdsmanufacturerpoपूर्णांकer = ROM16(bios->data[bitentry->offset]);

	वापस 0;
पूर्ण

अटल पूर्णांक
parse_bit_M_tbl_entry(काष्ठा drm_device *dev, काष्ठा nvbios *bios,
		      काष्ठा bit_entry *bitentry)
अणु
	/*
	 * offset + 2  (8  bits): number of options in an
	 * 	INIT_RAM_RESTRICT_ZM_REG_GROUP opcode option set
	 * offset + 3  (16 bits): poपूर्णांकer to strap xlate table क्रम RAM
	 * 	restrict option selection
	 *
	 * There's a bunch of bits in this table other than the RAM restrict
	 * stuff that we करोn't use - their use currently unknown
	 */

	/*
	 * Older bios versions करोn't have a sufficiently दीर्घ table क्रम
	 * what we want
	 */
	अगर (bitentry->length < 0x5)
		वापस 0;

	अगर (bitentry->version < 2) अणु
		bios->ram_restrict_group_count = bios->data[bitentry->offset + 2];
		bios->ram_restrict_tbl_ptr = ROM16(bios->data[bitentry->offset + 3]);
	पूर्ण अन्यथा अणु
		bios->ram_restrict_group_count = bios->data[bitentry->offset + 0];
		bios->ram_restrict_tbl_ptr = ROM16(bios->data[bitentry->offset + 1]);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक parse_bit_पंचांगds_tbl_entry(काष्ठा drm_device *dev, काष्ठा nvbios *bios, काष्ठा bit_entry *bitentry)
अणु
	/*
	 * Parses the poपूर्णांकer to the TMDS table
	 *
	 * Starting at bitentry->offset:
	 *
	 * offset + 0  (16 bits): TMDS table poपूर्णांकer
	 *
	 * The TMDS table is typically found just beक्रमe the DCB table, with a
	 * अक्षरacteristic signature of 0x11,0x13 (1.1 being version, 0x13 being
	 * length?)
	 *
	 * At offset +7 is a poपूर्णांकer to a script, which I करोn't know how to
	 * run yet.
	 * At offset +9 is a poपूर्णांकer to another script, likewise
	 * Offset +11 has a poपूर्णांकer to a table where the first word is a pxclk
	 * frequency and the second word a poपूर्णांकer to a script, which should be
	 * run अगर the comparison pxclk frequency is less than the pxclk desired.
	 * This repeats क्रम decreasing comparison frequencies
	 * Offset +13 has a poपूर्णांकer to a similar table
	 * The selection of table (and possibly +7/+9 script) is dictated by
	 * "or" from the DCB.
	 */

	काष्ठा nouveau_drm *drm = nouveau_drm(dev);
	uपूर्णांक16_t पंचांगdstableptr, script1, script2;

	अगर (bitentry->length != 2) अणु
		NV_ERROR(drm, "Do not understand BIT TMDS table\n");
		वापस -EINVAL;
	पूर्ण

	पंचांगdstableptr = ROM16(bios->data[bitentry->offset]);
	अगर (!पंचांगdstableptr) अणु
		NV_INFO(drm, "Pointer to TMDS table not found\n");
		वापस -EINVAL;
	पूर्ण

	NV_INFO(drm, "TMDS table version %d.%d\n",
		bios->data[पंचांगdstableptr] >> 4, bios->data[पंचांगdstableptr] & 0xf);

	/* nv50+ has v2.0, but we करोn't parse it aपंचांग */
	अगर (bios->data[पंचांगdstableptr] != 0x11)
		वापस -ENOSYS;

	/*
	 * These two scripts are odd: they करोn't seem to get run even when
	 * they are not stubbed.
	 */
	script1 = ROM16(bios->data[पंचांगdstableptr + 7]);
	script2 = ROM16(bios->data[पंचांगdstableptr + 9]);
	अगर (bios->data[script1] != 'q' || bios->data[script2] != 'q')
		NV_WARN(drm, "TMDS table script pointers not stubbed\n");

	bios->पंचांगds.output0_script_ptr = ROM16(bios->data[पंचांगdstableptr + 11]);
	bios->पंचांगds.output1_script_ptr = ROM16(bios->data[पंचांगdstableptr + 13]);

	वापस 0;
पूर्ण

काष्ठा bit_table अणु
	स्थिर अक्षर id;
	पूर्णांक (* स्थिर parse_fn)(काष्ठा drm_device *, काष्ठा nvbios *, काष्ठा bit_entry *);
पूर्ण;

#घोषणा BIT_TABLE(id, funcid) ((काष्ठा bit_table)अणु id, parse_bit_##funcid##_tbl_entry पूर्ण)

पूर्णांक
bit_table(काष्ठा drm_device *dev, u8 id, काष्ठा bit_entry *bit)
अणु
	काष्ठा nouveau_drm *drm = nouveau_drm(dev);
	काष्ठा nvbios *bios = &drm->vbios;
	u8 entries, *entry;

	अगर (bios->type != NVBIOS_BIT)
		वापस -ENODEV;

	entries = bios->data[bios->offset + 10];
	entry   = &bios->data[bios->offset + 12];
	जबतक (entries--) अणु
		अगर (entry[0] == id) अणु
			bit->id = entry[0];
			bit->version = entry[1];
			bit->length = ROM16(entry[2]);
			bit->offset = ROM16(entry[4]);
			bit->data = ROMPTR(dev, entry[4]);
			वापस 0;
		पूर्ण

		entry += bios->data[bios->offset + 9];
	पूर्ण

	वापस -ENOENT;
पूर्ण

अटल पूर्णांक
parse_bit_table(काष्ठा nvbios *bios, स्थिर uपूर्णांक16_t bitoffset,
		काष्ठा bit_table *table)
अणु
	काष्ठा drm_device *dev = bios->dev;
	काष्ठा nouveau_drm *drm = nouveau_drm(dev);
	काष्ठा bit_entry bitentry;

	अगर (bit_table(dev, table->id, &bitentry) == 0)
		वापस table->parse_fn(dev, bios, &bitentry);

	NV_INFO(drm, "BIT table '%c' not found\n", table->id);
	वापस -ENOSYS;
पूर्ण

अटल पूर्णांक
parse_bit_काष्ठाure(काष्ठा nvbios *bios, स्थिर uपूर्णांक16_t bitoffset)
अणु
	पूर्णांक ret;

	/*
	 * The only restriction on parsing order currently is having 'i' first
	 * क्रम use of bios->*_version or bios->feature_byte जबतक parsing;
	 * functions shouldn't be actually *करोing* anything apart from pulling
	 * data from the image पूर्णांकo the bios काष्ठा, thus no पूर्णांकerdependencies
	 */
	ret = parse_bit_table(bios, bitoffset, &BIT_TABLE('i', i));
	अगर (ret) /* info? */
		वापस ret;
	अगर (bios->major_version >= 0x60) /* g80+ */
		parse_bit_table(bios, bitoffset, &BIT_TABLE('A', A));
	parse_bit_table(bios, bitoffset, &BIT_TABLE('D', display));
	ret = parse_bit_table(bios, bitoffset, &BIT_TABLE('I', init));
	अगर (ret)
		वापस ret;
	parse_bit_table(bios, bitoffset, &BIT_TABLE('M', M)); /* memory? */
	parse_bit_table(bios, bitoffset, &BIT_TABLE('L', lvds));
	parse_bit_table(bios, bitoffset, &BIT_TABLE('T', पंचांगds));

	वापस 0;
पूर्ण

अटल पूर्णांक parse_bmp_काष्ठाure(काष्ठा drm_device *dev, काष्ठा nvbios *bios, अचिन्हित पूर्णांक offset)
अणु
	/*
	 * Parses the BMP काष्ठाure क्रम useful things, but करोes not act on them
	 *
	 * offset +   5: BMP major version
	 * offset +   6: BMP minor version
	 * offset +   9: BMP feature byte
	 * offset +  10: BCD encoded BIOS version
	 *
	 * offset +  18: init script table poपूर्णांकer (क्रम bios versions < 5.10h)
	 * offset +  20: extra init script table poपूर्णांकer (क्रम bios
	 * versions < 5.10h)
	 *
	 * offset +  24: memory init table poपूर्णांकer (used on early bios versions)
	 * offset +  26: SDR memory sequencing setup data table
	 * offset +  28: DDR memory sequencing setup data table
	 *
	 * offset +  54: index of I2C CRTC pair to use क्रम CRT output
	 * offset +  55: index of I2C CRTC pair to use क्रम TV output
	 * offset +  56: index of I2C CRTC pair to use क्रम flat panel output
	 * offset +  58: ग_लिखो CRTC index क्रम I2C pair 0
	 * offset +  59: पढ़ो CRTC index क्रम I2C pair 0
	 * offset +  60: ग_लिखो CRTC index क्रम I2C pair 1
	 * offset +  61: पढ़ो CRTC index क्रम I2C pair 1
	 *
	 * offset +  67: maximum पूर्णांकernal PLL frequency (single stage PLL)
	 * offset +  71: minimum पूर्णांकernal PLL frequency (single stage PLL)
	 *
	 * offset +  75: script table poपूर्णांकers, as described in
	 * parse_script_table_poपूर्णांकers
	 *
	 * offset +  89: TMDS single link output A table poपूर्णांकer
	 * offset +  91: TMDS single link output B table poपूर्णांकer
	 * offset +  95: LVDS single link output A table poपूर्णांकer
	 * offset + 105: flat panel timings table poपूर्णांकer
	 * offset + 107: flat panel strapping translation table poपूर्णांकer
	 * offset + 117: LVDS manufacturer panel config table poपूर्णांकer
	 * offset + 119: LVDS manufacturer strapping translation table poपूर्णांकer
	 *
	 * offset + 142: PLL limits table poपूर्णांकer
	 *
	 * offset + 156: minimum pixel घड़ी क्रम LVDS dual link
	 */

	काष्ठा nouveau_drm *drm = nouveau_drm(dev);
	uपूर्णांक8_t *bmp = &bios->data[offset], bmp_version_major, bmp_version_minor;
	uपूर्णांक16_t bmplength;
	uपूर्णांक16_t legacy_scripts_offset, legacy_i2c_offset;

	/* load needed शेषs in हाल we can't parse this info */
	bios->digital_min_front_porch = 0x4b;
	bios->fmaxvco = 256000;
	bios->fminvco = 128000;
	bios->fp.duallink_transition_clk = 90000;

	bmp_version_major = bmp[5];
	bmp_version_minor = bmp[6];

	NV_INFO(drm, "BMP version %d.%d\n",
		 bmp_version_major, bmp_version_minor);

	/*
	 * Make sure that 0x36 is blank and can't be mistaken क्रम a DCB
	 * poपूर्णांकer on early versions
	 */
	अगर (bmp_version_major < 5)
		*(uपूर्णांक16_t *)&bios->data[0x36] = 0;

	/*
	 * Seems that the minor version was 1 क्रम all major versions prior
	 * to 5. Version 6 could theoretically exist, but I suspect BIT
	 * happened instead.
	 */
	अगर ((bmp_version_major < 5 && bmp_version_minor != 1) || bmp_version_major > 5) अणु
		NV_ERROR(drm, "You have an unsupported BMP version. "
				"Please send in your bios\n");
		वापस -ENOSYS;
	पूर्ण

	अगर (bmp_version_major == 0)
		/* nothing that's currently useful in this version */
		वापस 0;
	अन्यथा अगर (bmp_version_major == 1)
		bmplength = 44; /* exact क्रम 1.01 */
	अन्यथा अगर (bmp_version_major == 2)
		bmplength = 48; /* exact क्रम 2.01 */
	अन्यथा अगर (bmp_version_major == 3)
		bmplength = 54;
		/* guessed - mem init tables added in this version */
	अन्यथा अगर (bmp_version_major == 4 || bmp_version_minor < 0x1)
		/* करोn't know अगर 5.0 exists... */
		bmplength = 62;
		/* guessed - BMP I2C indices added in version 4*/
	अन्यथा अगर (bmp_version_minor < 0x6)
		bmplength = 67; /* exact क्रम 5.01 */
	अन्यथा अगर (bmp_version_minor < 0x10)
		bmplength = 75; /* exact क्रम 5.06 */
	अन्यथा अगर (bmp_version_minor == 0x10)
		bmplength = 89; /* exact क्रम 5.10h */
	अन्यथा अगर (bmp_version_minor < 0x14)
		bmplength = 118; /* exact क्रम 5.11h */
	अन्यथा अगर (bmp_version_minor < 0x24)
		/*
		 * Not sure of version where pll limits came in;
		 * certainly exist by 0x24 though.
		 */
		/* length not exact: this is दीर्घ enough to get lvds members */
		bmplength = 123;
	अन्यथा अगर (bmp_version_minor < 0x27)
		/*
		 * Length not exact: this is दीर्घ enough to get pll limit
		 * member
		 */
		bmplength = 144;
	अन्यथा
		/*
		 * Length not exact: this is दीर्घ enough to get dual link
		 * transition घड़ी.
		 */
		bmplength = 158;

	/* checksum */
	अगर (nv_cksum(bmp, 8)) अणु
		NV_ERROR(drm, "Bad BMP checksum\n");
		वापस -EINVAL;
	पूर्ण

	/*
	 * Bit 4 seems to indicate either a mobile bios or a quadro card --
	 * mobile behaviour consistent (nv11+), quadro only seen nv18gl-nv36gl
	 * (not nv10gl), bit 5 that the flat panel tables are present, and
	 * bit 6 a tv bios.
	 */
	bios->feature_byte = bmp[9];

	अगर (bmp_version_major < 5 || bmp_version_minor < 0x10)
		bios->old_style_init = true;
	legacy_scripts_offset = 18;
	अगर (bmp_version_major < 2)
		legacy_scripts_offset -= 4;
	bios->init_script_tbls_ptr = ROM16(bmp[legacy_scripts_offset]);
	bios->extra_init_script_tbl_ptr = ROM16(bmp[legacy_scripts_offset + 2]);

	अगर (bmp_version_major > 2) अणु	/* appears in BMP 3 */
		bios->legacy.mem_init_tbl_ptr = ROM16(bmp[24]);
		bios->legacy.sdr_seq_tbl_ptr = ROM16(bmp[26]);
		bios->legacy.ddr_seq_tbl_ptr = ROM16(bmp[28]);
	पूर्ण

	legacy_i2c_offset = 0x48;	/* BMP version 2 & 3 */
	अगर (bmplength > 61)
		legacy_i2c_offset = offset + 54;
	bios->legacy.i2c_indices.crt = bios->data[legacy_i2c_offset];
	bios->legacy.i2c_indices.tv = bios->data[legacy_i2c_offset + 1];
	bios->legacy.i2c_indices.panel = bios->data[legacy_i2c_offset + 2];

	अगर (bmplength > 74) अणु
		bios->fmaxvco = ROM32(bmp[67]);
		bios->fminvco = ROM32(bmp[71]);
	पूर्ण
	अगर (bmplength > 88)
		parse_script_table_poपूर्णांकers(bios, offset + 75);
	अगर (bmplength > 94) अणु
		bios->पंचांगds.output0_script_ptr = ROM16(bmp[89]);
		bios->पंचांगds.output1_script_ptr = ROM16(bmp[91]);
		/*
		 * Never observed in use with lvds scripts, but is reused क्रम
		 * 18/24 bit panel पूर्णांकerface शेष क्रम EDID equipped panels
		 * (अगर_is_24bit not set directly to aव्योम any oscillation).
		 */
		bios->legacy.lvds_single_a_script_ptr = ROM16(bmp[95]);
	पूर्ण
	अगर (bmplength > 108) अणु
		bios->fp.fptablepoपूर्णांकer = ROM16(bmp[105]);
		bios->fp.fpxlatetableptr = ROM16(bmp[107]);
		bios->fp.xlatwidth = 1;
	पूर्ण
	अगर (bmplength > 120) अणु
		bios->fp.lvdsmanufacturerpoपूर्णांकer = ROM16(bmp[117]);
		bios->fp.fpxlatemanufacturertableptr = ROM16(bmp[119]);
	पूर्ण
#अगर 0
	अगर (bmplength > 143)
		bios->pll_limit_tbl_ptr = ROM16(bmp[142]);
#पूर्ण_अगर

	अगर (bmplength > 157)
		bios->fp.duallink_transition_clk = ROM16(bmp[156]) * 10;

	वापस 0;
पूर्ण

अटल uपूर्णांक16_t findstr(uपूर्णांक8_t *data, पूर्णांक n, स्थिर uपूर्णांक8_t *str, पूर्णांक len)
अणु
	पूर्णांक i, j;

	क्रम (i = 0; i <= (n - len); i++) अणु
		क्रम (j = 0; j < len; j++)
			अगर (data[i + j] != str[j])
				अवरोध;
		अगर (j == len)
			वापस i;
	पूर्ण

	वापस 0;
पूर्ण

व्योम *
olddcb_table(काष्ठा drm_device *dev)
अणु
	काष्ठा nouveau_drm *drm = nouveau_drm(dev);
	u8 *dcb = शून्य;

	अगर (drm->client.device.info.family > NV_DEVICE_INFO_V0_TNT)
		dcb = ROMPTR(dev, drm->vbios.data[0x36]);
	अगर (!dcb) अणु
		NV_WARN(drm, "No DCB data found in VBIOS\n");
		वापस शून्य;
	पूर्ण

	अगर (dcb[0] >= 0x42) अणु
		NV_WARN(drm, "DCB version 0x%02x unknown\n", dcb[0]);
		वापस शून्य;
	पूर्ण अन्यथा
	अगर (dcb[0] >= 0x30) अणु
		अगर (ROM32(dcb[6]) == 0x4edcbdcb)
			वापस dcb;
	पूर्ण अन्यथा
	अगर (dcb[0] >= 0x20) अणु
		अगर (ROM32(dcb[4]) == 0x4edcbdcb)
			वापस dcb;
	पूर्ण अन्यथा
	अगर (dcb[0] >= 0x15) अणु
		अगर (!स_भेद(&dcb[-7], "DEV_REC", 7))
			वापस dcb;
	पूर्ण अन्यथा अणु
		/*
		 * v1.4 (some NV15/16, NV11+) seems the same as v1.5, but
		 * always has the same single (crt) entry, even when tv-out
		 * present, so the conclusion is this version cannot really
		 * be used.
		 *
		 * v1.2 tables (some NV6/10, and NV15+) normally have the
		 * same 5 entries, which are not specअगरic to the card and so
		 * no use.
		 *
		 * v1.2 करोes have an I2C table that पढ़ो_dcb_i2c_table can
		 * handle, but cards exist (nv11 in #14821) with a bad i2c
		 * table poपूर्णांकer, so use the indices parsed in
		 * parse_bmp_काष्ठाure.
		 *
		 * v1.1 (NV5+, maybe some NV4) is entirely unhelpful
		 */
		NV_WARN(drm, "No useful DCB data in VBIOS\n");
		वापस शून्य;
	पूर्ण

	NV_WARN(drm, "DCB header validation failed\n");
	वापस शून्य;
पूर्ण

व्योम *
olddcb_outp(काष्ठा drm_device *dev, u8 idx)
अणु
	u8 *dcb = olddcb_table(dev);
	अगर (dcb && dcb[0] >= 0x30) अणु
		अगर (idx < dcb[2])
			वापस dcb + dcb[1] + (idx * dcb[3]);
	पूर्ण अन्यथा
	अगर (dcb && dcb[0] >= 0x20) अणु
		u8 *i2c = ROMPTR(dev, dcb[2]);
		u8 *ent = dcb + 8 + (idx * 8);
		अगर (i2c && ent < i2c)
			वापस ent;
	पूर्ण अन्यथा
	अगर (dcb && dcb[0] >= 0x15) अणु
		u8 *i2c = ROMPTR(dev, dcb[2]);
		u8 *ent = dcb + 4 + (idx * 10);
		अगर (i2c && ent < i2c)
			वापस ent;
	पूर्ण

	वापस शून्य;
पूर्ण

पूर्णांक
olddcb_outp_क्रमeach(काष्ठा drm_device *dev, व्योम *data,
		 पूर्णांक (*exec)(काष्ठा drm_device *, व्योम *, पूर्णांक idx, u8 *outp))
अणु
	पूर्णांक ret, idx = -1;
	u8 *outp = शून्य;
	जबतक ((outp = olddcb_outp(dev, ++idx))) अणु
		अगर (ROM32(outp[0]) == 0x00000000)
			अवरोध; /* seen on an NV11 with DCB v1.5 */
		अगर (ROM32(outp[0]) == 0xffffffff)
			अवरोध; /* seen on an NV17 with DCB v2.0 */

		अगर ((outp[0] & 0x0f) == DCB_OUTPUT_UNUSED)
			जारी;
		अगर ((outp[0] & 0x0f) == DCB_OUTPUT_EOL)
			अवरोध;

		ret = exec(dev, data, idx, outp);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

u8 *
olddcb_conntab(काष्ठा drm_device *dev)
अणु
	u8 *dcb = olddcb_table(dev);
	अगर (dcb && dcb[0] >= 0x30 && dcb[1] >= 0x16) अणु
		u8 *conntab = ROMPTR(dev, dcb[0x14]);
		अगर (conntab && conntab[0] >= 0x30 && conntab[0] <= 0x40)
			वापस conntab;
	पूर्ण
	वापस शून्य;
पूर्ण

u8 *
olddcb_conn(काष्ठा drm_device *dev, u8 idx)
अणु
	u8 *conntab = olddcb_conntab(dev);
	अगर (conntab && idx < conntab[2])
		वापस conntab + conntab[1] + (idx * conntab[3]);
	वापस शून्य;
पूर्ण

अटल काष्ठा dcb_output *new_dcb_entry(काष्ठा dcb_table *dcb)
अणु
	काष्ठा dcb_output *entry = &dcb->entry[dcb->entries];

	स_रखो(entry, 0, माप(काष्ठा dcb_output));
	entry->index = dcb->entries++;

	वापस entry;
पूर्ण

अटल व्योम fabricate_dcb_output(काष्ठा dcb_table *dcb, पूर्णांक type, पूर्णांक i2c,
				 पूर्णांक heads, पूर्णांक or)
अणु
	काष्ठा dcb_output *entry = new_dcb_entry(dcb);

	entry->type = type;
	entry->i2c_index = i2c;
	entry->heads = heads;
	अगर (type != DCB_OUTPUT_ANALOG)
		entry->location = !DCB_LOC_ON_CHIP; /* ie OFF CHIP */
	entry->or = or;
पूर्ण

अटल bool
parse_dcb20_entry(काष्ठा drm_device *dev, काष्ठा dcb_table *dcb,
		  uपूर्णांक32_t conn, uपूर्णांक32_t conf, काष्ठा dcb_output *entry)
अणु
	काष्ठा nouveau_drm *drm = nouveau_drm(dev);
	पूर्णांक link = 0;

	entry->type = conn & 0xf;
	entry->i2c_index = (conn >> 4) & 0xf;
	entry->heads = (conn >> 8) & 0xf;
	entry->connector = (conn >> 12) & 0xf;
	entry->bus = (conn >> 16) & 0xf;
	entry->location = (conn >> 20) & 0x3;
	entry->or = (conn >> 24) & 0xf;

	चयन (entry->type) अणु
	हाल DCB_OUTPUT_ANALOG:
		/*
		 * Although the rest of a CRT conf dword is usually
		 * zeros, mac biosen have stuff there so we must mask
		 */
		entry->crtconf.maxfreq = (dcb->version < 0x30) ?
					 (conf & 0xffff) * 10 :
					 (conf & 0xff) * 10000;
		अवरोध;
	हाल DCB_OUTPUT_LVDS:
		अणु
		uपूर्णांक32_t mask;
		अगर (conf & 0x1)
			entry->lvdsconf.use_straps_क्रम_mode = true;
		अगर (dcb->version < 0x22) अणु
			mask = ~0xd;
			/*
			 * The laptop in bug 14567 lies and claims to not use
			 * straps when it करोes, so assume all DCB 2.0 laptops
			 * use straps, until a broken EDID using one is produced
			 */
			entry->lvdsconf.use_straps_क्रम_mode = true;
			/*
			 * Both 0x4 and 0x8 show up in v2.0 tables; assume they
			 * mean the same thing (probably wrong, but might work)
			 */
			अगर (conf & 0x4 || conf & 0x8)
				entry->lvdsconf.use_घातer_scripts = true;
		पूर्ण अन्यथा अणु
			mask = ~0x7;
			अगर (conf & 0x2)
				entry->lvdsconf.use_acpi_क्रम_edid = true;
			अगर (conf & 0x4)
				entry->lvdsconf.use_घातer_scripts = true;
			entry->lvdsconf.sor.link = (conf & 0x00000030) >> 4;
			link = entry->lvdsconf.sor.link;
		पूर्ण
		अगर (conf & mask) अणु
			/*
			 * Until we even try to use these on G8x, it's
			 * useless reporting unknown bits.  They all are.
			 */
			अगर (dcb->version >= 0x40)
				अवरोध;

			NV_ERROR(drm, "Unknown LVDS configuration bits, "
				      "please report\n");
		पूर्ण
		अवरोध;
		पूर्ण
	हाल DCB_OUTPUT_TV:
	अणु
		अगर (dcb->version >= 0x30)
			entry->tvconf.has_component_output = conf & (0x8 << 4);
		अन्यथा
			entry->tvconf.has_component_output = false;

		अवरोध;
	पूर्ण
	हाल DCB_OUTPUT_DP:
		entry->dpconf.sor.link = (conf & 0x00000030) >> 4;
		entry->extdev = (conf & 0x0000ff00) >> 8;
		चयन ((conf & 0x00e00000) >> 21) अणु
		हाल 0:
			entry->dpconf.link_bw = 162000;
			अवरोध;
		हाल 1:
			entry->dpconf.link_bw = 270000;
			अवरोध;
		हाल 2:
			entry->dpconf.link_bw = 540000;
			अवरोध;
		हाल 3:
		शेष:
			entry->dpconf.link_bw = 810000;
			अवरोध;
		पूर्ण
		चयन ((conf & 0x0f000000) >> 24) अणु
		हाल 0xf:
		हाल 0x4:
			entry->dpconf.link_nr = 4;
			अवरोध;
		हाल 0x3:
		हाल 0x2:
			entry->dpconf.link_nr = 2;
			अवरोध;
		शेष:
			entry->dpconf.link_nr = 1;
			अवरोध;
		पूर्ण
		link = entry->dpconf.sor.link;
		अवरोध;
	हाल DCB_OUTPUT_TMDS:
		अगर (dcb->version >= 0x40) अणु
			entry->पंचांगdsconf.sor.link = (conf & 0x00000030) >> 4;
			entry->extdev = (conf & 0x0000ff00) >> 8;
			link = entry->पंचांगdsconf.sor.link;
		पूर्ण
		अन्यथा अगर (dcb->version >= 0x30)
			entry->पंचांगdsconf.slave_addr = (conf & 0x00000700) >> 8;
		अन्यथा अगर (dcb->version >= 0x22)
			entry->पंचांगdsconf.slave_addr = (conf & 0x00000070) >> 4;
		अवरोध;
	हाल DCB_OUTPUT_EOL:
		/* weird g80 mobile type that "nv" treats as a terminator */
		dcb->entries--;
		वापस false;
	शेष:
		अवरोध;
	पूर्ण

	अगर (dcb->version < 0x40) अणु
		/* Normal entries consist of a single bit, but dual link has
		 * the next most signअगरicant bit set too
		 */
		entry->duallink_possible =
			((1 << (ffs(entry->or) - 1)) * 3 == entry->or);
	पूर्ण अन्यथा अणु
		entry->duallink_possible = (entry->sorconf.link == 3);
	पूर्ण

	/* unsure what DCB version पूर्णांकroduces this, 3.0? */
	अगर (conf & 0x100000)
		entry->i2c_upper_शेष = true;

	entry->hasht = (entry->extdev << 8) | (entry->location << 4) |
			entry->type;
	entry->hashm = (entry->heads << 8) | (link << 6) | entry->or;
	वापस true;
पूर्ण

अटल bool
parse_dcb15_entry(काष्ठा drm_device *dev, काष्ठा dcb_table *dcb,
		  uपूर्णांक32_t conn, uपूर्णांक32_t conf, काष्ठा dcb_output *entry)
अणु
	काष्ठा nouveau_drm *drm = nouveau_drm(dev);

	चयन (conn & 0x0000000f) अणु
	हाल 0:
		entry->type = DCB_OUTPUT_ANALOG;
		अवरोध;
	हाल 1:
		entry->type = DCB_OUTPUT_TV;
		अवरोध;
	हाल 2:
	हाल 4:
		अगर (conn & 0x10)
			entry->type = DCB_OUTPUT_LVDS;
		अन्यथा
			entry->type = DCB_OUTPUT_TMDS;
		अवरोध;
	हाल 3:
		entry->type = DCB_OUTPUT_LVDS;
		अवरोध;
	शेष:
		NV_ERROR(drm, "Unknown DCB type %d\n", conn & 0x0000000f);
		वापस false;
	पूर्ण

	entry->i2c_index = (conn & 0x0003c000) >> 14;
	entry->heads = ((conn & 0x001c0000) >> 18) + 1;
	entry->or = entry->heads; /* same as heads, hopefully safe enough */
	entry->location = (conn & 0x01e00000) >> 21;
	entry->bus = (conn & 0x0e000000) >> 25;
	entry->duallink_possible = false;

	चयन (entry->type) अणु
	हाल DCB_OUTPUT_ANALOG:
		entry->crtconf.maxfreq = (conf & 0xffff) * 10;
		अवरोध;
	हाल DCB_OUTPUT_TV:
		entry->tvconf.has_component_output = false;
		अवरोध;
	हाल DCB_OUTPUT_LVDS:
		अगर ((conn & 0x00003f00) >> 8 != 0x10)
			entry->lvdsconf.use_straps_क्रम_mode = true;
		entry->lvdsconf.use_घातer_scripts = true;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस true;
पूर्ण

अटल
व्योम merge_like_dcb_entries(काष्ठा drm_device *dev, काष्ठा dcb_table *dcb)
अणु
	/*
	 * DCB v2.0 lists each output combination separately.
	 * Here we merge compatible entries to have fewer outमाला_दो, with
	 * more options
	 */

	काष्ठा nouveau_drm *drm = nouveau_drm(dev);
	पूर्णांक i, newentries = 0;

	क्रम (i = 0; i < dcb->entries; i++) अणु
		काष्ठा dcb_output *ient = &dcb->entry[i];
		पूर्णांक j;

		क्रम (j = i + 1; j < dcb->entries; j++) अणु
			काष्ठा dcb_output *jent = &dcb->entry[j];

			अगर (jent->type == 100) /* alपढ़ोy merged entry */
				जारी;

			/* merge heads field when all other fields the same */
			अगर (jent->i2c_index == ient->i2c_index &&
			    jent->type == ient->type &&
			    jent->location == ient->location &&
			    jent->or == ient->or) अणु
				NV_INFO(drm, "Merging DCB entries %d and %d\n",
					 i, j);
				ient->heads |= jent->heads;
				jent->type = 100; /* dummy value */
			पूर्ण
		पूर्ण
	पूर्ण

	/* Compact entries merged पूर्णांकo others out of dcb */
	क्रम (i = 0; i < dcb->entries; i++) अणु
		अगर (dcb->entry[i].type == 100)
			जारी;

		अगर (newentries != i) अणु
			dcb->entry[newentries] = dcb->entry[i];
			dcb->entry[newentries].index = newentries;
		पूर्ण
		newentries++;
	पूर्ण

	dcb->entries = newentries;
पूर्ण

अटल bool
apply_dcb_encoder_quirks(काष्ठा drm_device *dev, पूर्णांक idx, u32 *conn, u32 *conf)
अणु
	काष्ठा nouveau_drm *drm = nouveau_drm(dev);
	काष्ठा dcb_table *dcb = &drm->vbios.dcb;

	/* Dell Precision M6300
	 *   DCB entry 2: 02025312 00000010
	 *   DCB entry 3: 02026312 00000020
	 *
	 * Identical, except apparently a dअगरferent connector on a
	 * dअगरferent SOR link.  Not a clue how we're supposed to know
	 * which one is in use अगर it even shares an i2c line...
	 *
	 * Ignore the connector on the second SOR link to prevent
	 * nasty problems until this is sorted (assuming it's not a
	 * VBIOS bug).
	 */
	अगर (nv_match_device(dev, 0x040d, 0x1028, 0x019b)) अणु
		अगर (*conn == 0x02026312 && *conf == 0x00000020)
			वापस false;
	पूर्ण

	/* GeForce3 Ti 200
	 *
	 * DCB reports an LVDS output that should be TMDS:
	 *   DCB entry 1: f2005014 ffffffff
	 */
	अगर (nv_match_device(dev, 0x0201, 0x1462, 0x8851)) अणु
		अगर (*conn == 0xf2005014 && *conf == 0xffffffff) अणु
			fabricate_dcb_output(dcb, DCB_OUTPUT_TMDS, 1, 1, 1);
			वापस false;
		पूर्ण
	पूर्ण

	/* XFX GT-240X-YA
	 *
	 * So many things wrong here, replace the entire encoder table..
	 */
	अगर (nv_match_device(dev, 0x0ca3, 0x1682, 0x3003)) अणु
		अगर (idx == 0) अणु
			*conn = 0x02001300; /* VGA, connector 1 */
			*conf = 0x00000028;
		पूर्ण अन्यथा
		अगर (idx == 1) अणु
			*conn = 0x01010312; /* DVI, connector 0 */
			*conf = 0x00020030;
		पूर्ण अन्यथा
		अगर (idx == 2) अणु
			*conn = 0x01010310; /* VGA, connector 0 */
			*conf = 0x00000028;
		पूर्ण अन्यथा
		अगर (idx == 3) अणु
			*conn = 0x02022362; /* HDMI, connector 2 */
			*conf = 0x00020010;
		पूर्ण अन्यथा अणु
			*conn = 0x0000000e; /* EOL */
			*conf = 0x00000000;
		पूर्ण
	पूर्ण

	/* Some other twisted XFX board (rhbz#694914)
	 *
	 * The DVI/VGA encoder combo that's supposed to represent the
	 * DVI-I connector actually poपूर्णांक at two dअगरferent ones, and
	 * the HDMI connector ends up paired with the VGA instead.
	 *
	 * Connector table is missing anything क्रम VGA at all, poपूर्णांकing it
	 * an invalid conntab entry 2 so we figure it out ourself.
	 */
	अगर (nv_match_device(dev, 0x0615, 0x1682, 0x2605)) अणु
		अगर (idx == 0) अणु
			*conn = 0x02002300; /* VGA, connector 2 */
			*conf = 0x00000028;
		पूर्ण अन्यथा
		अगर (idx == 1) अणु
			*conn = 0x01010312; /* DVI, connector 0 */
			*conf = 0x00020030;
		पूर्ण अन्यथा
		अगर (idx == 2) अणु
			*conn = 0x04020310; /* VGA, connector 0 */
			*conf = 0x00000028;
		पूर्ण अन्यथा
		अगर (idx == 3) अणु
			*conn = 0x02021322; /* HDMI, connector 1 */
			*conf = 0x00020010;
		पूर्ण अन्यथा अणु
			*conn = 0x0000000e; /* EOL */
			*conf = 0x00000000;
		पूर्ण
	पूर्ण

	/* fकरो#50830: connector indices क्रम VGA and DVI-I are backwards */
	अगर (nv_match_device(dev, 0x0421, 0x3842, 0xc793)) अणु
		अगर (idx == 0 && *conn == 0x02000300)
			*conn = 0x02011300;
		अन्यथा
		अगर (idx == 1 && *conn == 0x04011310)
			*conn = 0x04000310;
		अन्यथा
		अगर (idx == 2 && *conn == 0x02011312)
			*conn = 0x02000312;
	पूर्ण

	वापस true;
पूर्ण

अटल व्योम
fabricate_dcb_encoder_table(काष्ठा drm_device *dev, काष्ठा nvbios *bios)
अणु
	काष्ठा dcb_table *dcb = &bios->dcb;
	पूर्णांक all_heads = (nv_two_heads(dev) ? 3 : 1);

#अगर_घोषित __घातerpc__
	/* Apple iMac G4 NV17 */
	अगर (of_machine_is_compatible("PowerMac4,5")) अणु
		fabricate_dcb_output(dcb, DCB_OUTPUT_TMDS, 0, all_heads, 1);
		fabricate_dcb_output(dcb, DCB_OUTPUT_ANALOG, 1, all_heads, 2);
		वापस;
	पूर्ण
#पूर्ण_अगर

	/* Make up some sane शेषs */
	fabricate_dcb_output(dcb, DCB_OUTPUT_ANALOG,
			     bios->legacy.i2c_indices.crt, 1, 1);

	अगर (nv04_tv_identअगरy(dev, bios->legacy.i2c_indices.tv) >= 0)
		fabricate_dcb_output(dcb, DCB_OUTPUT_TV,
				     bios->legacy.i2c_indices.tv,
				     all_heads, 0);

	अन्यथा अगर (bios->पंचांगds.output0_script_ptr ||
		 bios->पंचांगds.output1_script_ptr)
		fabricate_dcb_output(dcb, DCB_OUTPUT_TMDS,
				     bios->legacy.i2c_indices.panel,
				     all_heads, 1);
पूर्ण

अटल पूर्णांक
parse_dcb_entry(काष्ठा drm_device *dev, व्योम *data, पूर्णांक idx, u8 *outp)
अणु
	काष्ठा nouveau_drm *drm = nouveau_drm(dev);
	काष्ठा dcb_table *dcb = &drm->vbios.dcb;
	u32 conf = (dcb->version >= 0x20) ? ROM32(outp[4]) : ROM32(outp[6]);
	u32 conn = ROM32(outp[0]);
	bool ret;

	अगर (apply_dcb_encoder_quirks(dev, idx, &conn, &conf)) अणु
		काष्ठा dcb_output *entry = new_dcb_entry(dcb);

		NV_INFO(drm, "DCB outp %02d: %08x %08x\n", idx, conn, conf);

		अगर (dcb->version >= 0x20)
			ret = parse_dcb20_entry(dev, dcb, conn, conf, entry);
		अन्यथा
			ret = parse_dcb15_entry(dev, dcb, conn, conf, entry);
		अगर (!ret)
			वापस 1; /* stop parsing */

		/* Ignore the I2C index क्रम on-chip TV-out, as there
		 * are cards with bogus values (nv31m in bug 23212),
		 * and it's otherwise useless.
		 */
		अगर (entry->type == DCB_OUTPUT_TV &&
		    entry->location == DCB_LOC_ON_CHIP)
			entry->i2c_index = 0x0f;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम
dcb_fake_connectors(काष्ठा nvbios *bios)
अणु
	काष्ठा dcb_table *dcbt = &bios->dcb;
	u8 map[16] = अणु पूर्ण;
	पूर्णांक i, idx = 0;

	/* heuristic: अगर we ever get a non-zero connector field, assume
	 * that all the indices are valid and we करोn't need fake them.
	 *
	 * and, as usual, a blacklist of boards with bad bios data..
	 */
	अगर (!nv_match_device(bios->dev, 0x0392, 0x107d, 0x20a2)) अणु
		क्रम (i = 0; i < dcbt->entries; i++) अणु
			अगर (dcbt->entry[i].connector)
				वापस;
		पूर्ण
	पूर्ण

	/* no useful connector info available, we need to make it up
	 * ourselves.  the rule here is: anything on the same i2c bus
	 * is considered to be on the same connector.  any output
	 * without an associated i2c bus is asचिन्हित its own unique
	 * connector index.
	 */
	क्रम (i = 0; i < dcbt->entries; i++) अणु
		u8 i2c = dcbt->entry[i].i2c_index;
		अगर (i2c == 0x0f) अणु
			dcbt->entry[i].connector = idx++;
		पूर्ण अन्यथा अणु
			अगर (!map[i2c])
				map[i2c] = ++idx;
			dcbt->entry[i].connector = map[i2c] - 1;
		पूर्ण
	पूर्ण

	/* अगर we created more than one connector, destroy the connector
	 * table - just in हाल it has अक्रमom, rather than stub, entries.
	 */
	अगर (i > 1) अणु
		u8 *conntab = olddcb_conntab(bios->dev);
		अगर (conntab)
			conntab[0] = 0x00;
	पूर्ण
पूर्ण

अटल पूर्णांक
parse_dcb_table(काष्ठा drm_device *dev, काष्ठा nvbios *bios)
अणु
	काष्ठा nouveau_drm *drm = nouveau_drm(dev);
	काष्ठा dcb_table *dcb = &bios->dcb;
	u8 *dcbt, *conn;
	पूर्णांक idx;

	dcbt = olddcb_table(dev);
	अगर (!dcbt) अणु
		/* handle pre-DCB boards */
		अगर (bios->type == NVBIOS_BMP) अणु
			fabricate_dcb_encoder_table(dev, bios);
			वापस 0;
		पूर्ण

		वापस -EINVAL;
	पूर्ण

	NV_INFO(drm, "DCB version %d.%d\n", dcbt[0] >> 4, dcbt[0] & 0xf);

	dcb->version = dcbt[0];
	olddcb_outp_क्रमeach(dev, शून्य, parse_dcb_entry);

	/*
	 * apart क्रम v2.1+ not being known क्रम requiring merging, this
	 * guarantees dcbent->index is the index of the entry in the rom image
	 */
	अगर (dcb->version < 0x21)
		merge_like_dcb_entries(dev, dcb);

	/* dump connector table entries to log, अगर any exist */
	idx = -1;
	जबतक ((conn = olddcb_conn(dev, ++idx))) अणु
		अगर (conn[0] != 0xff) अणु
			अगर (olddcb_conntab(dev)[3] < 4)
				NV_INFO(drm, "DCB conn %02d: %04x\n",
					idx, ROM16(conn[0]));
			अन्यथा
				NV_INFO(drm, "DCB conn %02d: %08x\n",
					idx, ROM32(conn[0]));
		पूर्ण
	पूर्ण
	dcb_fake_connectors(bios);
	वापस 0;
पूर्ण

अटल पूर्णांक load_nv17_hwsq_ucode_entry(काष्ठा drm_device *dev, काष्ठा nvbios *bios, uपूर्णांक16_t hwsq_offset, पूर्णांक entry)
अणु
	/*
	 * The header following the "HWSQ" signature has the number of entries,
	 * and the entry size
	 *
	 * An entry consists of a dword to ग_लिखो to the sequencer control reg
	 * (0x00001304), followed by the ucode bytes, written sequentially,
	 * starting at reg 0x00001400
	 */

	काष्ठा nouveau_drm *drm = nouveau_drm(dev);
	काष्ठा nvअगर_object *device = &drm->client.device.object;
	uपूर्णांक8_t bytes_to_ग_लिखो;
	uपूर्णांक16_t hwsq_entry_offset;
	पूर्णांक i;

	अगर (bios->data[hwsq_offset] <= entry) अणु
		NV_ERROR(drm, "Too few entries in HW sequencer table for "
				"requested entry\n");
		वापस -ENOENT;
	पूर्ण

	bytes_to_ग_लिखो = bios->data[hwsq_offset + 1];

	अगर (bytes_to_ग_लिखो != 36) अणु
		NV_ERROR(drm, "Unknown HW sequencer entry size\n");
		वापस -EINVAL;
	पूर्ण

	NV_INFO(drm, "Loading NV17 power sequencing microcode\n");

	hwsq_entry_offset = hwsq_offset + 2 + entry * bytes_to_ग_लिखो;

	/* set sequencer control */
	nvअगर_wr32(device, 0x00001304, ROM32(bios->data[hwsq_entry_offset]));
	bytes_to_ग_लिखो -= 4;

	/* ग_लिखो ucode */
	क्रम (i = 0; i < bytes_to_ग_लिखो; i += 4)
		nvअगर_wr32(device, 0x00001400 + i, ROM32(bios->data[hwsq_entry_offset + i + 4]));

	/* twiddle NV_PBUS_DEBUG_4 */
	nvअगर_wr32(device, NV_PBUS_DEBUG_4, nvअगर_rd32(device, NV_PBUS_DEBUG_4) | 0x18);

	वापस 0;
पूर्ण

अटल पूर्णांक load_nv17_hw_sequencer_ucode(काष्ठा drm_device *dev,
					काष्ठा nvbios *bios)
अणु
	/*
	 * BMP based cards, from NV17, need a microcode loading to correctly
	 * control the GPIO etc क्रम LVDS panels
	 *
	 * BIT based cards seem to करो this directly in the init scripts
	 *
	 * The microcode entries are found by the "HWSQ" signature.
	 */

	अटल स्थिर uपूर्णांक8_t hwsq_signature[] = अणु 'H', 'W', 'S', 'Q' पूर्ण;
	स्थिर पूर्णांक sz = माप(hwsq_signature);
	पूर्णांक hwsq_offset;

	hwsq_offset = findstr(bios->data, bios->length, hwsq_signature, sz);
	अगर (!hwsq_offset)
		वापस 0;

	/* always use entry 0? */
	वापस load_nv17_hwsq_ucode_entry(dev, bios, hwsq_offset + sz, 0);
पूर्ण

uपूर्णांक8_t *nouveau_bios_embedded_edid(काष्ठा drm_device *dev)
अणु
	काष्ठा nouveau_drm *drm = nouveau_drm(dev);
	काष्ठा nvbios *bios = &drm->vbios;
	अटल स्थिर uपूर्णांक8_t edid_sig[] = अणु
			0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00 पूर्ण;
	uपूर्णांक16_t offset = 0;
	uपूर्णांक16_t newoffset;
	पूर्णांक searchlen = NV_PROM_SIZE;

	अगर (bios->fp.edid)
		वापस bios->fp.edid;

	जबतक (searchlen) अणु
		newoffset = findstr(&bios->data[offset], searchlen,
								edid_sig, 8);
		अगर (!newoffset)
			वापस शून्य;
		offset += newoffset;
		अगर (!nv_cksum(&bios->data[offset], EDID1_LEN))
			अवरोध;

		searchlen -= offset;
		offset++;
	पूर्ण

	NV_INFO(drm, "Found EDID in BIOS\n");

	वापस bios->fp.edid = &bios->data[offset];
पूर्ण

अटल bool NVInitVBIOS(काष्ठा drm_device *dev)
अणु
	काष्ठा nouveau_drm *drm = nouveau_drm(dev);
	काष्ठा nvkm_bios *bios = nvxx_bios(&drm->client.device);
	काष्ठा nvbios *legacy = &drm->vbios;

	स_रखो(legacy, 0, माप(काष्ठा nvbios));
	spin_lock_init(&legacy->lock);
	legacy->dev = dev;

	legacy->data = bios->data;
	legacy->length = bios->size;
	legacy->major_version = bios->version.major;
	legacy->chip_version = bios->version.chip;
	अगर (bios->bit_offset) अणु
		legacy->type = NVBIOS_BIT;
		legacy->offset = bios->bit_offset;
		वापस !parse_bit_काष्ठाure(legacy, legacy->offset + 6);
	पूर्ण अन्यथा
	अगर (bios->bmp_offset) अणु
		legacy->type = NVBIOS_BMP;
		legacy->offset = bios->bmp_offset;
		वापस !parse_bmp_काष्ठाure(dev, legacy, legacy->offset);
	पूर्ण

	वापस false;
पूर्ण

पूर्णांक
nouveau_run_vbios_init(काष्ठा drm_device *dev)
अणु
	काष्ठा nouveau_drm *drm = nouveau_drm(dev);
	काष्ठा nvbios *bios = &drm->vbios;
	पूर्णांक ret = 0;

	/* Reset the BIOS head to 0. */
	bios->state.crtchead = 0;

	अगर (bios->major_version < 5)	/* BMP only */
		load_nv17_hw_sequencer_ucode(dev, bios);

	अगर (bios->execute) अणु
		bios->fp.last_script_invoc = 0;
		bios->fp.lvds_init_run = false;
	पूर्ण

	वापस ret;
पूर्ण

अटल bool
nouveau_bios_posted(काष्ठा drm_device *dev)
अणु
	काष्ठा nouveau_drm *drm = nouveau_drm(dev);
	अचिन्हित htotal;

	अगर (drm->client.device.info.family >= NV_DEVICE_INFO_V0_TESLA)
		वापस true;

	htotal  = NVReadVgaCrtc(dev, 0, 0x06);
	htotal |= (NVReadVgaCrtc(dev, 0, 0x07) & 0x01) << 8;
	htotal |= (NVReadVgaCrtc(dev, 0, 0x07) & 0x20) << 4;
	htotal |= (NVReadVgaCrtc(dev, 0, 0x25) & 0x01) << 10;
	htotal |= (NVReadVgaCrtc(dev, 0, 0x41) & 0x01) << 11;
	वापस (htotal != 0);
पूर्ण

पूर्णांक
nouveau_bios_init(काष्ठा drm_device *dev)
अणु
	काष्ठा nouveau_drm *drm = nouveau_drm(dev);
	काष्ठा nvbios *bios = &drm->vbios;
	पूर्णांक ret;

	/* only relevant क्रम PCI devices */
	अगर (!dev_is_pci(dev->dev))
		वापस 0;

	अगर (!NVInitVBIOS(dev))
		वापस -ENODEV;

	ret = parse_dcb_table(dev, bios);
	अगर (ret)
		वापस ret;

	अगर (!bios->major_version)	/* we करोn't run version 0 bios */
		वापस 0;

	/* init script execution disabled */
	bios->execute = false;

	/* ... unless card isn't POSTed alपढ़ोy */
	अगर (!nouveau_bios_posted(dev)) अणु
		NV_INFO(drm, "Adaptor not initialised, "
			"running VBIOS init tables.\n");
		bios->execute = true;
	पूर्ण

	ret = nouveau_run_vbios_init(dev);
	अगर (ret)
		वापस ret;

	/* feature_byte on BMP is poor, but init always sets CR4B */
	अगर (bios->major_version < 5)
		bios->is_mobile = NVReadVgaCrtc(dev, 0, NV_CIO_CRE_4B) & 0x40;

	/* all BIT प्रणालीs need p_f_m_t क्रम digital_min_front_porch */
	अगर (bios->is_mobile || bios->major_version >= 5)
		ret = parse_fp_mode_table(dev, bios);

	/* allow subsequent scripts to execute */
	bios->execute = true;

	वापस 0;
पूर्ण

व्योम
nouveau_bios_takeकरोwn(काष्ठा drm_device *dev)
अणु
पूर्ण
