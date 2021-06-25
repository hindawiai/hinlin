<शैली गुरु>
/*
 * Copyright तऊ 2014 Intel Corporation
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
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 *
 */

#समावेश <linux/firmware.h>

#समावेश "i915_drv.h"
#समावेश "i915_reg.h"
#समावेश "intel_csr.h"
#समावेश "intel_de.h"

/**
 * DOC: csr support क्रम dmc
 *
 * Display Context Save and Restore (CSR) firmware support added from gen9
 * onwards to drive newly added DMC (Display microcontroller) in display
 * engine to save and restore the state of display engine when it enter पूर्णांकo
 * low-घातer state and comes back to normal.
 */

#घोषणा GEN12_CSR_MAX_FW_SIZE		ICL_CSR_MAX_FW_SIZE

#घोषणा ADLS_CSR_PATH			"i915/adls_dmc_ver2_01.bin"
#घोषणा ADLS_CSR_VERSION_REQUIRED	CSR_VERSION(2, 1)
MODULE_FIRMWARE(ADLS_CSR_PATH);

#घोषणा DG1_CSR_PATH			"i915/dg1_dmc_ver2_02.bin"
#घोषणा DG1_CSR_VERSION_REQUIRED	CSR_VERSION(2, 2)
MODULE_FIRMWARE(DG1_CSR_PATH);

#घोषणा RKL_CSR_PATH			"i915/rkl_dmc_ver2_02.bin"
#घोषणा RKL_CSR_VERSION_REQUIRED	CSR_VERSION(2, 2)
MODULE_FIRMWARE(RKL_CSR_PATH);

#घोषणा TGL_CSR_PATH			"i915/tgl_dmc_ver2_08.bin"
#घोषणा TGL_CSR_VERSION_REQUIRED	CSR_VERSION(2, 8)
MODULE_FIRMWARE(TGL_CSR_PATH);

#घोषणा ICL_CSR_PATH			"i915/icl_dmc_ver1_09.bin"
#घोषणा ICL_CSR_VERSION_REQUIRED	CSR_VERSION(1, 9)
#घोषणा ICL_CSR_MAX_FW_SIZE		0x6000
MODULE_FIRMWARE(ICL_CSR_PATH);

#घोषणा CNL_CSR_PATH			"i915/cnl_dmc_ver1_07.bin"
#घोषणा CNL_CSR_VERSION_REQUIRED	CSR_VERSION(1, 7)
#घोषणा CNL_CSR_MAX_FW_SIZE		GLK_CSR_MAX_FW_SIZE
MODULE_FIRMWARE(CNL_CSR_PATH);

#घोषणा GLK_CSR_PATH			"i915/glk_dmc_ver1_04.bin"
#घोषणा GLK_CSR_VERSION_REQUIRED	CSR_VERSION(1, 4)
#घोषणा GLK_CSR_MAX_FW_SIZE		0x4000
MODULE_FIRMWARE(GLK_CSR_PATH);

#घोषणा KBL_CSR_PATH			"i915/kbl_dmc_ver1_04.bin"
#घोषणा KBL_CSR_VERSION_REQUIRED	CSR_VERSION(1, 4)
#घोषणा KBL_CSR_MAX_FW_SIZE		BXT_CSR_MAX_FW_SIZE
MODULE_FIRMWARE(KBL_CSR_PATH);

#घोषणा SKL_CSR_PATH			"i915/skl_dmc_ver1_27.bin"
#घोषणा SKL_CSR_VERSION_REQUIRED	CSR_VERSION(1, 27)
#घोषणा SKL_CSR_MAX_FW_SIZE		BXT_CSR_MAX_FW_SIZE
MODULE_FIRMWARE(SKL_CSR_PATH);

#घोषणा BXT_CSR_PATH			"i915/bxt_dmc_ver1_07.bin"
#घोषणा BXT_CSR_VERSION_REQUIRED	CSR_VERSION(1, 7)
#घोषणा BXT_CSR_MAX_FW_SIZE		0x3000
MODULE_FIRMWARE(BXT_CSR_PATH);

#घोषणा CSR_DEFAULT_FW_OFFSET		0xFFFFFFFF
#घोषणा PACKAGE_MAX_FW_INFO_ENTRIES	20
#घोषणा PACKAGE_V2_MAX_FW_INFO_ENTRIES	32
#घोषणा DMC_V1_MAX_MMIO_COUNT		8
#घोषणा DMC_V3_MAX_MMIO_COUNT		20

काष्ठा पूर्णांकel_css_header अणु
	/* 0x09 क्रम DMC */
	u32 module_type;

	/* Includes the DMC specअगरic header in dwords */
	u32 header_len;

	/* always value would be 0x10000 */
	u32 header_ver;

	/* Not used */
	u32 module_id;

	/* Not used */
	u32 module_venकरोr;

	/* in YYYYMMDD क्रमmat */
	u32 date;

	/* Size in dwords (CSS_Headerlen + PackageHeaderLen + dmc FWsLen)/4 */
	u32 size;

	/* Not used */
	u32 key_size;

	/* Not used */
	u32 modulus_size;

	/* Not used */
	u32 exponent_size;

	/* Not used */
	u32 reserved1[12];

	/* Major Minor */
	u32 version;

	/* Not used */
	u32 reserved2[8];

	/* Not used */
	u32 kernel_header_info;
पूर्ण __packed;

काष्ठा पूर्णांकel_fw_info अणु
	u8 reserved1;

	/* reserved on package_header version 1, must be 0 on version 2 */
	u8 dmc_id;

	/* Stepping (A, B, C, ..., *). * is a wildcard */
	अक्षर stepping;

	/* Sub-stepping (0, 1, ..., *). * is a wildcard */
	अक्षर substepping;

	u32 offset;
	u32 reserved2;
पूर्ण __packed;

काष्ठा पूर्णांकel_package_header अणु
	/* DMC container header length in dwords */
	u8 header_len;

	/* 0x01, 0x02 */
	u8 header_ver;

	u8 reserved[10];

	/* Number of valid entries in the FWInfo array below */
	u32 num_entries;
पूर्ण __packed;

काष्ठा पूर्णांकel_dmc_header_base अणु
	/* always value would be 0x40403E3E */
	u32 signature;

	/* DMC binary header length */
	u8 header_len;

	/* 0x01 */
	u8 header_ver;

	/* Reserved */
	u16 dmcc_ver;

	/* Major, Minor */
	u32 project;

	/* Firmware program size (excluding header) in dwords */
	u32 fw_size;

	/* Major Minor version */
	u32 fw_version;
पूर्ण __packed;

काष्ठा पूर्णांकel_dmc_header_v1 अणु
	काष्ठा पूर्णांकel_dmc_header_base base;

	/* Number of valid MMIO cycles present. */
	u32 mmio_count;

	/* MMIO address */
	u32 mmioaddr[DMC_V1_MAX_MMIO_COUNT];

	/* MMIO data */
	u32 mmiodata[DMC_V1_MAX_MMIO_COUNT];

	/* FW filename  */
	अक्षर dfile[32];

	u32 reserved1[2];
पूर्ण __packed;

काष्ठा पूर्णांकel_dmc_header_v3 अणु
	काष्ठा पूर्णांकel_dmc_header_base base;

	/* DMC RAM start MMIO address */
	u32 start_mmioaddr;

	u32 reserved[9];

	/* FW filename */
	अक्षर dfile[32];

	/* Number of valid MMIO cycles present. */
	u32 mmio_count;

	/* MMIO address */
	u32 mmioaddr[DMC_V3_MAX_MMIO_COUNT];

	/* MMIO data */
	u32 mmiodata[DMC_V3_MAX_MMIO_COUNT];
पूर्ण __packed;

काष्ठा stepping_info अणु
	अक्षर stepping;
	अक्षर substepping;
पूर्ण;

अटल स्थिर काष्ठा stepping_info skl_stepping_info[] = अणु
	अणु'A', '0'}, {'B', '0'}, {'C', '0'पूर्ण,
	अणु'D', '0'}, {'E', '0'}, {'F', '0'पूर्ण,
	अणु'G', '0'}, {'H', '0'}, {'I', '0'पूर्ण,
	अणु'J', '0'}, {'K', '0'पूर्ण
पूर्ण;

अटल स्थिर काष्ठा stepping_info bxt_stepping_info[] = अणु
	अणु'A', '0'}, {'A', '1'}, {'A', '2'पूर्ण,
	अणु'B', '0'}, {'B', '1'}, {'B', '2'पूर्ण
पूर्ण;

अटल स्थिर काष्ठा stepping_info icl_stepping_info[] = अणु
	अणु'A', '0'}, {'A', '1'}, {'A', '2'पूर्ण,
	अणु'B', '0'}, {'B', '2'पूर्ण,
	अणु'C', '0'पूर्ण
पूर्ण;

अटल स्थिर काष्ठा stepping_info no_stepping_info = अणु '*', '*' पूर्ण;

अटल स्थिर काष्ठा stepping_info *
पूर्णांकel_get_stepping_info(काष्ठा drm_i915_निजी *dev_priv)
अणु
	स्थिर काष्ठा stepping_info *si;
	अचिन्हित पूर्णांक size;

	अगर (IS_ICELAKE(dev_priv)) अणु
		size = ARRAY_SIZE(icl_stepping_info);
		si = icl_stepping_info;
	पूर्ण अन्यथा अगर (IS_SKYLAKE(dev_priv)) अणु
		size = ARRAY_SIZE(skl_stepping_info);
		si = skl_stepping_info;
	पूर्ण अन्यथा अगर (IS_BROXTON(dev_priv)) अणु
		size = ARRAY_SIZE(bxt_stepping_info);
		si = bxt_stepping_info;
	पूर्ण अन्यथा अणु
		size = 0;
		si = शून्य;
	पूर्ण

	अगर (INTEL_REVID(dev_priv) < size)
		वापस si + INTEL_REVID(dev_priv);

	वापस &no_stepping_info;
पूर्ण

अटल व्योम gen9_set_dc_state_debugmask(काष्ठा drm_i915_निजी *dev_priv)
अणु
	u32 val, mask;

	mask = DC_STATE_DEBUG_MASK_MEMORY_UP;

	अगर (IS_GEN9_LP(dev_priv))
		mask |= DC_STATE_DEBUG_MASK_CORES;

	/* The below bit करोesn't need to be cleared ever afterwards */
	val = पूर्णांकel_de_पढ़ो(dev_priv, DC_STATE_DEBUG);
	अगर ((val & mask) != mask) अणु
		val |= mask;
		पूर्णांकel_de_ग_लिखो(dev_priv, DC_STATE_DEBUG, val);
		पूर्णांकel_de_posting_पढ़ो(dev_priv, DC_STATE_DEBUG);
	पूर्ण
पूर्ण

/**
 * पूर्णांकel_csr_load_program() - ग_लिखो the firmware from memory to रेजिस्टर.
 * @dev_priv: i915 drm device.
 *
 * CSR firmware is पढ़ो from a .bin file and kept in पूर्णांकernal memory one समय.
 * Everyसमय display comes back from low घातer state this function is called to
 * copy the firmware from पूर्णांकernal memory to रेजिस्टरs.
 */
व्योम पूर्णांकel_csr_load_program(काष्ठा drm_i915_निजी *dev_priv)
अणु
	u32 *payload = dev_priv->csr.dmc_payload;
	u32 i, fw_size;

	अगर (!HAS_CSR(dev_priv)) अणु
		drm_err(&dev_priv->drm,
			"No CSR support available for this platform\n");
		वापस;
	पूर्ण

	अगर (!dev_priv->csr.dmc_payload) अणु
		drm_err(&dev_priv->drm,
			"Tried to program CSR with empty payload\n");
		वापस;
	पूर्ण

	fw_size = dev_priv->csr.dmc_fw_size;
	निश्चित_rpm_wakelock_held(&dev_priv->runसमय_pm);

	preempt_disable();

	क्रम (i = 0; i < fw_size; i++)
		पूर्णांकel_uncore_ग_लिखो_fw(&dev_priv->uncore, CSR_PROGRAM(i),
				      payload[i]);

	preempt_enable();

	क्रम (i = 0; i < dev_priv->csr.mmio_count; i++) अणु
		पूर्णांकel_de_ग_लिखो(dev_priv, dev_priv->csr.mmioaddr[i],
			       dev_priv->csr.mmiodata[i]);
	पूर्ण

	dev_priv->csr.dc_state = 0;

	gen9_set_dc_state_debugmask(dev_priv);
पूर्ण

/*
 * Search fw_info table क्रम dmc_offset to find firmware binary: num_entries is
 * alपढ़ोy sanitized.
 */
अटल u32 find_dmc_fw_offset(स्थिर काष्ठा पूर्णांकel_fw_info *fw_info,
			      अचिन्हित पूर्णांक num_entries,
			      स्थिर काष्ठा stepping_info *si,
			      u8 package_ver)
अणु
	u32 dmc_offset = CSR_DEFAULT_FW_OFFSET;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < num_entries; i++) अणु
		अगर (package_ver > 1 && fw_info[i].dmc_id != 0)
			जारी;

		अगर (fw_info[i].substepping == '*' &&
		    si->stepping == fw_info[i].stepping) अणु
			dmc_offset = fw_info[i].offset;
			अवरोध;
		पूर्ण

		अगर (si->stepping == fw_info[i].stepping &&
		    si->substepping == fw_info[i].substepping) अणु
			dmc_offset = fw_info[i].offset;
			अवरोध;
		पूर्ण

		अगर (fw_info[i].stepping == '*' &&
		    fw_info[i].substepping == '*') अणु
			/*
			 * In theory we should stop the search as generic
			 * entries should always come after the more specअगरic
			 * ones, but let's जारी to make sure to work even
			 * with "broken" firmwares. If we करोn't find a more
			 * specअगरic one, then we use this entry
			 */
			dmc_offset = fw_info[i].offset;
		पूर्ण
	पूर्ण

	वापस dmc_offset;
पूर्ण

अटल u32 parse_csr_fw_dmc(काष्ठा पूर्णांकel_csr *csr,
			    स्थिर काष्ठा पूर्णांकel_dmc_header_base *dmc_header,
			    माप_प्रकार rem_size)
अणु
	अचिन्हित पूर्णांक header_len_bytes, dmc_header_size, payload_size, i;
	स्थिर u32 *mmioaddr, *mmiodata;
	u32 mmio_count, mmio_count_max;
	u8 *payload;

	BUILD_BUG_ON(ARRAY_SIZE(csr->mmioaddr) < DMC_V3_MAX_MMIO_COUNT ||
		     ARRAY_SIZE(csr->mmioaddr) < DMC_V1_MAX_MMIO_COUNT);

	/*
	 * Check अगर we can access common fields, we will checkc again below
	 * after we have पढ़ो the version
	 */
	अगर (rem_size < माप(काष्ठा पूर्णांकel_dmc_header_base))
		जाओ error_truncated;

	/* Cope with small dअगरferences between v1 and v3 */
	अगर (dmc_header->header_ver == 3) अणु
		स्थिर काष्ठा पूर्णांकel_dmc_header_v3 *v3 =
			(स्थिर काष्ठा पूर्णांकel_dmc_header_v3 *)dmc_header;

		अगर (rem_size < माप(काष्ठा पूर्णांकel_dmc_header_v3))
			जाओ error_truncated;

		mmioaddr = v3->mmioaddr;
		mmiodata = v3->mmiodata;
		mmio_count = v3->mmio_count;
		mmio_count_max = DMC_V3_MAX_MMIO_COUNT;
		/* header_len is in dwords */
		header_len_bytes = dmc_header->header_len * 4;
		dmc_header_size = माप(*v3);
	पूर्ण अन्यथा अगर (dmc_header->header_ver == 1) अणु
		स्थिर काष्ठा पूर्णांकel_dmc_header_v1 *v1 =
			(स्थिर काष्ठा पूर्णांकel_dmc_header_v1 *)dmc_header;

		अगर (rem_size < माप(काष्ठा पूर्णांकel_dmc_header_v1))
			जाओ error_truncated;

		mmioaddr = v1->mmioaddr;
		mmiodata = v1->mmiodata;
		mmio_count = v1->mmio_count;
		mmio_count_max = DMC_V1_MAX_MMIO_COUNT;
		header_len_bytes = dmc_header->header_len;
		dmc_header_size = माप(*v1);
	पूर्ण अन्यथा अणु
		DRM_ERROR("Unknown DMC fw header version: %u\n",
			  dmc_header->header_ver);
		वापस 0;
	पूर्ण

	अगर (header_len_bytes != dmc_header_size) अणु
		DRM_ERROR("DMC firmware has wrong dmc header length "
			  "(%u bytes)\n", header_len_bytes);
		वापस 0;
	पूर्ण

	/* Cache the dmc header info. */
	अगर (mmio_count > mmio_count_max) अणु
		DRM_ERROR("DMC firmware has wrong mmio count %u\n", mmio_count);
		वापस 0;
	पूर्ण

	क्रम (i = 0; i < mmio_count; i++) अणु
		अगर (mmioaddr[i] < CSR_MMIO_START_RANGE ||
		    mmioaddr[i] > CSR_MMIO_END_RANGE) अणु
			DRM_ERROR("DMC firmware has wrong mmio address 0x%x\n",
				  mmioaddr[i]);
			वापस 0;
		पूर्ण
		csr->mmioaddr[i] = _MMIO(mmioaddr[i]);
		csr->mmiodata[i] = mmiodata[i];
	पूर्ण
	csr->mmio_count = mmio_count;

	rem_size -= header_len_bytes;

	/* fw_size is in dwords, so multiplied by 4 to convert पूर्णांकo bytes. */
	payload_size = dmc_header->fw_size * 4;
	अगर (rem_size < payload_size)
		जाओ error_truncated;

	अगर (payload_size > csr->max_fw_size) अणु
		DRM_ERROR("DMC FW too big (%u bytes)\n", payload_size);
		वापस 0;
	पूर्ण
	csr->dmc_fw_size = dmc_header->fw_size;

	csr->dmc_payload = kदो_स्मृति(payload_size, GFP_KERNEL);
	अगर (!csr->dmc_payload) अणु
		DRM_ERROR("Memory allocation failed for dmc payload\n");
		वापस 0;
	पूर्ण

	payload = (u8 *)(dmc_header) + header_len_bytes;
	स_नकल(csr->dmc_payload, payload, payload_size);

	वापस header_len_bytes + payload_size;

error_truncated:
	DRM_ERROR("Truncated DMC firmware, refusing.\n");
	वापस 0;
पूर्ण

अटल u32
parse_csr_fw_package(काष्ठा पूर्णांकel_csr *csr,
		     स्थिर काष्ठा पूर्णांकel_package_header *package_header,
		     स्थिर काष्ठा stepping_info *si,
		     माप_प्रकार rem_size)
अणु
	u32 package_size = माप(काष्ठा पूर्णांकel_package_header);
	u32 num_entries, max_entries, dmc_offset;
	स्थिर काष्ठा पूर्णांकel_fw_info *fw_info;

	अगर (rem_size < package_size)
		जाओ error_truncated;

	अगर (package_header->header_ver == 1) अणु
		max_entries = PACKAGE_MAX_FW_INFO_ENTRIES;
	पूर्ण अन्यथा अगर (package_header->header_ver == 2) अणु
		max_entries = PACKAGE_V2_MAX_FW_INFO_ENTRIES;
	पूर्ण अन्यथा अणु
		DRM_ERROR("DMC firmware has unknown header version %u\n",
			  package_header->header_ver);
		वापस 0;
	पूर्ण

	/*
	 * We should always have space क्रम max_entries,
	 * even अगर not all are used
	 */
	package_size += max_entries * माप(काष्ठा पूर्णांकel_fw_info);
	अगर (rem_size < package_size)
		जाओ error_truncated;

	अगर (package_header->header_len * 4 != package_size) अणु
		DRM_ERROR("DMC firmware has wrong package header length "
			  "(%u bytes)\n", package_size);
		वापस 0;
	पूर्ण

	num_entries = package_header->num_entries;
	अगर (WARN_ON(package_header->num_entries > max_entries))
		num_entries = max_entries;

	fw_info = (स्थिर काष्ठा पूर्णांकel_fw_info *)
		((u8 *)package_header + माप(*package_header));
	dmc_offset = find_dmc_fw_offset(fw_info, num_entries, si,
					package_header->header_ver);
	अगर (dmc_offset == CSR_DEFAULT_FW_OFFSET) अणु
		DRM_ERROR("DMC firmware not supported for %c stepping\n",
			  si->stepping);
		वापस 0;
	पूर्ण

	/* dmc_offset is in dwords */
	वापस package_size + dmc_offset * 4;

error_truncated:
	DRM_ERROR("Truncated DMC firmware, refusing.\n");
	वापस 0;
पूर्ण

/* Return number of bytes parsed or 0 on error */
अटल u32 parse_csr_fw_css(काष्ठा पूर्णांकel_csr *csr,
			    काष्ठा पूर्णांकel_css_header *css_header,
			    माप_प्रकार rem_size)
अणु
	अगर (rem_size < माप(काष्ठा पूर्णांकel_css_header)) अणु
		DRM_ERROR("Truncated DMC firmware, refusing.\n");
		वापस 0;
	पूर्ण

	अगर (माप(काष्ठा पूर्णांकel_css_header) !=
	    (css_header->header_len * 4)) अणु
		DRM_ERROR("DMC firmware has wrong CSS header length "
			  "(%u bytes)\n",
			  (css_header->header_len * 4));
		वापस 0;
	पूर्ण

	अगर (csr->required_version &&
	    css_header->version != csr->required_version) अणु
		DRM_INFO("Refusing to load DMC firmware v%u.%u,"
			 " please use v%u.%u\n",
			 CSR_VERSION_MAJOR(css_header->version),
			 CSR_VERSION_MINOR(css_header->version),
			 CSR_VERSION_MAJOR(csr->required_version),
			 CSR_VERSION_MINOR(csr->required_version));
		वापस 0;
	पूर्ण

	csr->version = css_header->version;

	वापस माप(काष्ठा पूर्णांकel_css_header);
पूर्ण

अटल व्योम parse_csr_fw(काष्ठा drm_i915_निजी *dev_priv,
			 स्थिर काष्ठा firmware *fw)
अणु
	काष्ठा पूर्णांकel_css_header *css_header;
	काष्ठा पूर्णांकel_package_header *package_header;
	काष्ठा पूर्णांकel_dmc_header_base *dmc_header;
	काष्ठा पूर्णांकel_csr *csr = &dev_priv->csr;
	स्थिर काष्ठा stepping_info *si = पूर्णांकel_get_stepping_info(dev_priv);
	u32 पढ़ोcount = 0;
	u32 r;

	अगर (!fw)
		वापस;

	/* Extract CSS Header inक्रमmation */
	css_header = (काष्ठा पूर्णांकel_css_header *)fw->data;
	r = parse_csr_fw_css(csr, css_header, fw->size);
	अगर (!r)
		वापस;

	पढ़ोcount += r;

	/* Extract Package Header inक्रमmation */
	package_header = (काष्ठा पूर्णांकel_package_header *)&fw->data[पढ़ोcount];
	r = parse_csr_fw_package(csr, package_header, si, fw->size - पढ़ोcount);
	अगर (!r)
		वापस;

	पढ़ोcount += r;

	/* Extract dmc_header inक्रमmation */
	dmc_header = (काष्ठा पूर्णांकel_dmc_header_base *)&fw->data[पढ़ोcount];
	parse_csr_fw_dmc(csr, dmc_header, fw->size - पढ़ोcount);
पूर्ण

अटल व्योम पूर्णांकel_csr_runसमय_pm_get(काष्ठा drm_i915_निजी *dev_priv)
अणु
	drm_WARN_ON(&dev_priv->drm, dev_priv->csr.wakeref);
	dev_priv->csr.wakeref =
		पूर्णांकel_display_घातer_get(dev_priv, POWER_DOMAIN_INIT);
पूर्ण

अटल व्योम पूर्णांकel_csr_runसमय_pm_put(काष्ठा drm_i915_निजी *dev_priv)
अणु
	पूर्णांकel_wakeref_t wakeref __maybe_unused =
		fetch_and_zero(&dev_priv->csr.wakeref);

	पूर्णांकel_display_घातer_put(dev_priv, POWER_DOMAIN_INIT, wakeref);
पूर्ण

अटल व्योम csr_load_work_fn(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा drm_i915_निजी *dev_priv;
	काष्ठा पूर्णांकel_csr *csr;
	स्थिर काष्ठा firmware *fw = शून्य;

	dev_priv = container_of(work, typeof(*dev_priv), csr.work);
	csr = &dev_priv->csr;

	request_firmware(&fw, dev_priv->csr.fw_path, dev_priv->drm.dev);
	parse_csr_fw(dev_priv, fw);

	अगर (dev_priv->csr.dmc_payload) अणु
		पूर्णांकel_csr_load_program(dev_priv);
		पूर्णांकel_csr_runसमय_pm_put(dev_priv);

		drm_info(&dev_priv->drm,
			 "Finished loading DMC firmware %s (v%u.%u)\n",
			 dev_priv->csr.fw_path, CSR_VERSION_MAJOR(csr->version),
			 CSR_VERSION_MINOR(csr->version));
	पूर्ण अन्यथा अणु
		drm_notice(&dev_priv->drm,
			   "Failed to load DMC firmware %s."
			   " Disabling runtime power management.\n",
			   csr->fw_path);
		drm_notice(&dev_priv->drm, "DMC firmware homepage: %s",
			   INTEL_UC_FIRMWARE_URL);
	पूर्ण

	release_firmware(fw);
पूर्ण

/**
 * पूर्णांकel_csr_ucode_init() - initialize the firmware loading.
 * @dev_priv: i915 drm device.
 *
 * This function is called at the समय of loading the display driver to पढ़ो
 * firmware from a .bin file and copied पूर्णांकo a पूर्णांकernal memory.
 */
व्योम पूर्णांकel_csr_ucode_init(काष्ठा drm_i915_निजी *dev_priv)
अणु
	काष्ठा पूर्णांकel_csr *csr = &dev_priv->csr;

	INIT_WORK(&dev_priv->csr.work, csr_load_work_fn);

	अगर (!HAS_CSR(dev_priv))
		वापस;

	/*
	 * Obtain a runसमय pm reference, until CSR is loaded, to aव्योम entering
	 * runसमय-suspend.
	 *
	 * On error, we वापस with the rpm wakeref held to prevent runसमय
	 * suspend as runसमय suspend *requires* a working CSR क्रम whatever
	 * reason.
	 */
	पूर्णांकel_csr_runसमय_pm_get(dev_priv);

	अगर (IS_ALDERLAKE_S(dev_priv)) अणु
		csr->fw_path = ADLS_CSR_PATH;
		csr->required_version = ADLS_CSR_VERSION_REQUIRED;
		csr->max_fw_size = GEN12_CSR_MAX_FW_SIZE;
	पूर्ण अन्यथा अगर (IS_DG1(dev_priv)) अणु
		csr->fw_path = DG1_CSR_PATH;
		csr->required_version = DG1_CSR_VERSION_REQUIRED;
		csr->max_fw_size = GEN12_CSR_MAX_FW_SIZE;
	पूर्ण अन्यथा अगर (IS_ROCKETLAKE(dev_priv)) अणु
		csr->fw_path = RKL_CSR_PATH;
		csr->required_version = RKL_CSR_VERSION_REQUIRED;
		csr->max_fw_size = GEN12_CSR_MAX_FW_SIZE;
	पूर्ण अन्यथा अगर (DISPLAY_VER(dev_priv) >= 12) अणु
		csr->fw_path = TGL_CSR_PATH;
		csr->required_version = TGL_CSR_VERSION_REQUIRED;
		csr->max_fw_size = GEN12_CSR_MAX_FW_SIZE;
	पूर्ण अन्यथा अगर (IS_DISPLAY_VER(dev_priv, 11)) अणु
		csr->fw_path = ICL_CSR_PATH;
		csr->required_version = ICL_CSR_VERSION_REQUIRED;
		csr->max_fw_size = ICL_CSR_MAX_FW_SIZE;
	पूर्ण अन्यथा अगर (IS_CANNONLAKE(dev_priv)) अणु
		csr->fw_path = CNL_CSR_PATH;
		csr->required_version = CNL_CSR_VERSION_REQUIRED;
		csr->max_fw_size = CNL_CSR_MAX_FW_SIZE;
	पूर्ण अन्यथा अगर (IS_GEMINILAKE(dev_priv)) अणु
		csr->fw_path = GLK_CSR_PATH;
		csr->required_version = GLK_CSR_VERSION_REQUIRED;
		csr->max_fw_size = GLK_CSR_MAX_FW_SIZE;
	पूर्ण अन्यथा अगर (IS_KABYLAKE(dev_priv) ||
		   IS_COFFEELAKE(dev_priv) ||
		   IS_COMETLAKE(dev_priv)) अणु
		csr->fw_path = KBL_CSR_PATH;
		csr->required_version = KBL_CSR_VERSION_REQUIRED;
		csr->max_fw_size = KBL_CSR_MAX_FW_SIZE;
	पूर्ण अन्यथा अगर (IS_SKYLAKE(dev_priv)) अणु
		csr->fw_path = SKL_CSR_PATH;
		csr->required_version = SKL_CSR_VERSION_REQUIRED;
		csr->max_fw_size = SKL_CSR_MAX_FW_SIZE;
	पूर्ण अन्यथा अगर (IS_BROXTON(dev_priv)) अणु
		csr->fw_path = BXT_CSR_PATH;
		csr->required_version = BXT_CSR_VERSION_REQUIRED;
		csr->max_fw_size = BXT_CSR_MAX_FW_SIZE;
	पूर्ण

	अगर (dev_priv->params.dmc_firmware_path) अणु
		अगर (म_माप(dev_priv->params.dmc_firmware_path) == 0) अणु
			csr->fw_path = शून्य;
			drm_info(&dev_priv->drm,
				 "Disabling CSR firmware and runtime PM\n");
			वापस;
		पूर्ण

		csr->fw_path = dev_priv->params.dmc_firmware_path;
		/* Bypass version check क्रम firmware override. */
		csr->required_version = 0;
	पूर्ण

	अगर (csr->fw_path == शून्य) अणु
		drm_dbg_kms(&dev_priv->drm,
			    "No known CSR firmware for platform, disabling runtime PM\n");
		वापस;
	पूर्ण

	drm_dbg_kms(&dev_priv->drm, "Loading %s\n", csr->fw_path);
	schedule_work(&dev_priv->csr.work);
पूर्ण

/**
 * पूर्णांकel_csr_ucode_suspend() - prepare CSR firmware beक्रमe प्रणाली suspend
 * @dev_priv: i915 drm device
 *
 * Prepare the DMC firmware beक्रमe entering प्रणाली suspend. This includes
 * flushing pending work items and releasing any resources acquired during
 * init.
 */
व्योम पूर्णांकel_csr_ucode_suspend(काष्ठा drm_i915_निजी *dev_priv)
अणु
	अगर (!HAS_CSR(dev_priv))
		वापस;

	flush_work(&dev_priv->csr.work);

	/* Drop the reference held in हाल DMC isn't loaded. */
	अगर (!dev_priv->csr.dmc_payload)
		पूर्णांकel_csr_runसमय_pm_put(dev_priv);
पूर्ण

/**
 * पूर्णांकel_csr_ucode_resume() - init CSR firmware during प्रणाली resume
 * @dev_priv: i915 drm device
 *
 * Reinitialize the DMC firmware during प्रणाली resume, reacquiring any
 * resources released in पूर्णांकel_csr_ucode_suspend().
 */
व्योम पूर्णांकel_csr_ucode_resume(काष्ठा drm_i915_निजी *dev_priv)
अणु
	अगर (!HAS_CSR(dev_priv))
		वापस;

	/*
	 * Reacquire the reference to keep RPM disabled in हाल DMC isn't
	 * loaded.
	 */
	अगर (!dev_priv->csr.dmc_payload)
		पूर्णांकel_csr_runसमय_pm_get(dev_priv);
पूर्ण

/**
 * पूर्णांकel_csr_ucode_fini() - unload the CSR firmware.
 * @dev_priv: i915 drm device.
 *
 * Firmmware unloading includes मुक्तing the पूर्णांकernal memory and reset the
 * firmware loading status.
 */
व्योम पूर्णांकel_csr_ucode_fini(काष्ठा drm_i915_निजी *dev_priv)
अणु
	अगर (!HAS_CSR(dev_priv))
		वापस;

	पूर्णांकel_csr_ucode_suspend(dev_priv);
	drm_WARN_ON(&dev_priv->drm, dev_priv->csr.wakeref);

	kमुक्त(dev_priv->csr.dmc_payload);
पूर्ण
