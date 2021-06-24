<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Marvell OcteonTX CPT driver
 *
 * Copyright (C) 2019 Marvell International Ltd.
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#समावेश <linux/प्रकार.स>
#समावेश <linux/firmware.h>
#समावेश "otx_cpt_common.h"
#समावेश "otx_cptpf_ucode.h"
#समावेश "otx_cptpf.h"

#घोषणा CSR_DELAY 30
/* Tar archive defines */
#घोषणा TAR_MAGIC		"ustar"
#घोषणा TAR_MAGIC_LEN		6
#घोषणा TAR_BLOCK_LEN		512
#घोषणा REGTYPE			'0'
#घोषणा AREGTYPE		'\0'

/* tar header as defined in POSIX 1003.1-1990. */
काष्ठा tar_hdr_t अणु
	अक्षर name[100];
	अक्षर mode[8];
	अक्षर uid[8];
	अक्षर gid[8];
	अक्षर size[12];
	अक्षर mसमय[12];
	अक्षर chksum[8];
	अक्षर typeflag;
	अक्षर linkname[100];
	अक्षर magic[6];
	अक्षर version[2];
	अक्षर uname[32];
	अक्षर gname[32];
	अक्षर devmajor[8];
	अक्षर devminor[8];
	अक्षर prefix[155];
पूर्ण;

काष्ठा tar_blk_t अणु
	जोड़ अणु
		काष्ठा tar_hdr_t hdr;
		अक्षर block[TAR_BLOCK_LEN];
	पूर्ण;
पूर्ण;

काष्ठा tar_arch_info_t अणु
	काष्ठा list_head ucodes;
	स्थिर काष्ठा firmware *fw;
पूर्ण;

अटल काष्ठा otx_cpt_biपंचांगap get_cores_bmap(काष्ठा device *dev,
					   काष्ठा otx_cpt_eng_grp_info *eng_grp)
अणु
	काष्ठा otx_cpt_biपंचांगap bmap = अणु अणु0पूर्ण पूर्ण;
	bool found = false;
	पूर्णांक i;

	अगर (eng_grp->g->engs_num > OTX_CPT_MAX_ENGINES) अणु
		dev_err(dev, "unsupported number of engines %d on octeontx\n",
			eng_grp->g->engs_num);
		वापस bmap;
	पूर्ण

	क्रम (i = 0; i < OTX_CPT_MAX_ETYPES_PER_GRP; i++) अणु
		अगर (eng_grp->engs[i].type) अणु
			biपंचांगap_or(bmap.bits, bmap.bits,
				  eng_grp->engs[i].bmap,
				  eng_grp->g->engs_num);
			bmap.size = eng_grp->g->engs_num;
			found = true;
		पूर्ण
	पूर्ण

	अगर (!found)
		dev_err(dev, "No engines reserved for engine group %d\n",
			eng_grp->idx);
	वापस bmap;
पूर्ण

अटल पूर्णांक is_eng_type(पूर्णांक val, पूर्णांक eng_type)
अणु
	वापस val & (1 << eng_type);
पूर्ण

अटल पूर्णांक dev_supports_eng_type(काष्ठा otx_cpt_eng_grps *eng_grps,
				 पूर्णांक eng_type)
अणु
	वापस is_eng_type(eng_grps->eng_types_supported, eng_type);
पूर्ण

अटल व्योम set_ucode_filename(काष्ठा otx_cpt_ucode *ucode,
			       स्थिर अक्षर *filename)
अणु
	strlcpy(ucode->filename, filename, OTX_CPT_UCODE_NAME_LENGTH);
पूर्ण

अटल अक्षर *get_eng_type_str(पूर्णांक eng_type)
अणु
	अक्षर *str = "unknown";

	चयन (eng_type) अणु
	हाल OTX_CPT_SE_TYPES:
		str = "SE";
		अवरोध;

	हाल OTX_CPT_AE_TYPES:
		str = "AE";
		अवरोध;
	पूर्ण
	वापस str;
पूर्ण

अटल अक्षर *get_ucode_type_str(पूर्णांक ucode_type)
अणु
	अक्षर *str = "unknown";

	चयन (ucode_type) अणु
	हाल (1 << OTX_CPT_SE_TYPES):
		str = "SE";
		अवरोध;

	हाल (1 << OTX_CPT_AE_TYPES):
		str = "AE";
		अवरोध;
	पूर्ण
	वापस str;
पूर्ण

अटल पूर्णांक get_ucode_type(काष्ठा otx_cpt_ucode_hdr *ucode_hdr, पूर्णांक *ucode_type)
अणु
	अक्षर पंचांगp_ver_str[OTX_CPT_UCODE_VER_STR_SZ];
	u32 i, val = 0;
	u8 nn;

	strlcpy(पंचांगp_ver_str, ucode_hdr->ver_str, OTX_CPT_UCODE_VER_STR_SZ);
	क्रम (i = 0; i < म_माप(पंचांगp_ver_str); i++)
		पंचांगp_ver_str[i] = छोटे(पंचांगp_ver_str[i]);

	nn = ucode_hdr->ver_num.nn;
	अगर (strnstr(पंचांगp_ver_str, "se-", OTX_CPT_UCODE_VER_STR_SZ) &&
	    (nn == OTX_CPT_SE_UC_TYPE1 || nn == OTX_CPT_SE_UC_TYPE2 ||
	     nn == OTX_CPT_SE_UC_TYPE3))
		val |= 1 << OTX_CPT_SE_TYPES;
	अगर (strnstr(पंचांगp_ver_str, "ae", OTX_CPT_UCODE_VER_STR_SZ) &&
	    nn == OTX_CPT_AE_UC_TYPE)
		val |= 1 << OTX_CPT_AE_TYPES;

	*ucode_type = val;

	अगर (!val)
		वापस -EINVAL;
	अगर (is_eng_type(val, OTX_CPT_AE_TYPES) &&
	    is_eng_type(val, OTX_CPT_SE_TYPES))
		वापस -EINVAL;
	वापस 0;
पूर्ण

अटल पूर्णांक is_mem_zero(स्थिर अक्षर *ptr, पूर्णांक size)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < size; i++) अणु
		अगर (ptr[i])
			वापस 0;
	पूर्ण
	वापस 1;
पूर्ण

अटल पूर्णांक cpt_set_ucode_base(काष्ठा otx_cpt_eng_grp_info *eng_grp, व्योम *obj)
अणु
	काष्ठा otx_cpt_device *cpt = (काष्ठा otx_cpt_device *) obj;
	dma_addr_t dma_addr;
	काष्ठा otx_cpt_biपंचांगap bmap;
	पूर्णांक i;

	bmap = get_cores_bmap(&cpt->pdev->dev, eng_grp);
	अगर (!bmap.size)
		वापस -EINVAL;

	अगर (eng_grp->mirror.is_ena)
		dma_addr =
		       eng_grp->g->grp[eng_grp->mirror.idx].ucode[0].align_dma;
	अन्यथा
		dma_addr = eng_grp->ucode[0].align_dma;

	/*
	 * Set UCODE_BASE only क्रम the cores which are not used,
	 * other cores should have alपढ़ोy valid UCODE_BASE set
	 */
	क्रम_each_set_bit(i, bmap.bits, bmap.size)
		अगर (!eng_grp->g->eng_ref_cnt[i])
			ग_लिखोq((u64) dma_addr, cpt->reg_base +
				OTX_CPT_PF_ENGX_UCODE_BASE(i));
	वापस 0;
पूर्ण

अटल पूर्णांक cpt_detach_and_disable_cores(काष्ठा otx_cpt_eng_grp_info *eng_grp,
					व्योम *obj)
अणु
	काष्ठा otx_cpt_device *cpt = (काष्ठा otx_cpt_device *) obj;
	काष्ठा otx_cpt_biपंचांगap bmap = अणु अणु0पूर्ण पूर्ण;
	पूर्णांक समयout = 10;
	पूर्णांक i, busy;
	u64 reg;

	bmap = get_cores_bmap(&cpt->pdev->dev, eng_grp);
	अगर (!bmap.size)
		वापस -EINVAL;

	/* Detach the cores from group */
	reg = पढ़ोq(cpt->reg_base + OTX_CPT_PF_GX_EN(eng_grp->idx));
	क्रम_each_set_bit(i, bmap.bits, bmap.size) अणु
		अगर (reg & (1ull << i)) अणु
			eng_grp->g->eng_ref_cnt[i]--;
			reg &= ~(1ull << i);
		पूर्ण
	पूर्ण
	ग_लिखोq(reg, cpt->reg_base + OTX_CPT_PF_GX_EN(eng_grp->idx));

	/* Wait क्रम cores to become idle */
	करो अणु
		busy = 0;
		usleep_range(10000, 20000);
		अगर (समयout-- < 0)
			वापस -EBUSY;

		reg = पढ़ोq(cpt->reg_base + OTX_CPT_PF_EXEC_BUSY);
		क्रम_each_set_bit(i, bmap.bits, bmap.size)
			अगर (reg & (1ull << i)) अणु
				busy = 1;
				अवरोध;
			पूर्ण
	पूर्ण जबतक (busy);

	/* Disable the cores only अगर they are not used anymore */
	reg = पढ़ोq(cpt->reg_base + OTX_CPT_PF_EXE_CTL);
	क्रम_each_set_bit(i, bmap.bits, bmap.size)
		अगर (!eng_grp->g->eng_ref_cnt[i])
			reg &= ~(1ull << i);
	ग_लिखोq(reg, cpt->reg_base + OTX_CPT_PF_EXE_CTL);

	वापस 0;
पूर्ण

अटल पूर्णांक cpt_attach_and_enable_cores(काष्ठा otx_cpt_eng_grp_info *eng_grp,
				       व्योम *obj)
अणु
	काष्ठा otx_cpt_device *cpt = (काष्ठा otx_cpt_device *) obj;
	काष्ठा otx_cpt_biपंचांगap bmap;
	u64 reg;
	पूर्णांक i;

	bmap = get_cores_bmap(&cpt->pdev->dev, eng_grp);
	अगर (!bmap.size)
		वापस -EINVAL;

	/* Attach the cores to the group */
	reg = पढ़ोq(cpt->reg_base + OTX_CPT_PF_GX_EN(eng_grp->idx));
	क्रम_each_set_bit(i, bmap.bits, bmap.size) अणु
		अगर (!(reg & (1ull << i))) अणु
			eng_grp->g->eng_ref_cnt[i]++;
			reg |= 1ull << i;
		पूर्ण
	पूर्ण
	ग_लिखोq(reg, cpt->reg_base + OTX_CPT_PF_GX_EN(eng_grp->idx));

	/* Enable the cores */
	reg = पढ़ोq(cpt->reg_base + OTX_CPT_PF_EXE_CTL);
	क्रम_each_set_bit(i, bmap.bits, bmap.size)
		reg |= 1ull << i;
	ग_लिखोq(reg, cpt->reg_base + OTX_CPT_PF_EXE_CTL);

	वापस 0;
पूर्ण

अटल पूर्णांक process_tar_file(काष्ठा device *dev,
			    काष्ठा tar_arch_info_t *tar_arch, अक्षर *filename,
			    स्थिर u8 *data, u32 size)
अणु
	काष्ठा tar_ucode_info_t *tar_info;
	काष्ठा otx_cpt_ucode_hdr *ucode_hdr;
	पूर्णांक ucode_type, ucode_size;

	/*
	 * If size is less than microcode header size then करोn't report
	 * an error because it might not be microcode file, just process
	 * next file from archive
	 */
	अगर (size < माप(काष्ठा otx_cpt_ucode_hdr))
		वापस 0;

	ucode_hdr = (काष्ठा otx_cpt_ucode_hdr *) data;
	/*
	 * If microcode version can't be found don't report an error
	 * because it might not be microcode file, just process next file
	 */
	अगर (get_ucode_type(ucode_hdr, &ucode_type))
		वापस 0;

	ucode_size = ntohl(ucode_hdr->code_length) * 2;
	अगर (!ucode_size || (size < round_up(ucode_size, 16) +
	    माप(काष्ठा otx_cpt_ucode_hdr) + OTX_CPT_UCODE_SIGN_LEN)) अणु
		dev_err(dev, "Ucode %s invalid size\n", filename);
		वापस -EINVAL;
	पूर्ण

	tar_info = kzalloc(माप(काष्ठा tar_ucode_info_t), GFP_KERNEL);
	अगर (!tar_info)
		वापस -ENOMEM;

	tar_info->ucode_ptr = data;
	set_ucode_filename(&tar_info->ucode, filename);
	स_नकल(tar_info->ucode.ver_str, ucode_hdr->ver_str,
	       OTX_CPT_UCODE_VER_STR_SZ);
	tar_info->ucode.ver_num = ucode_hdr->ver_num;
	tar_info->ucode.type = ucode_type;
	tar_info->ucode.size = ucode_size;
	list_add_tail(&tar_info->list, &tar_arch->ucodes);

	वापस 0;
पूर्ण

अटल व्योम release_tar_archive(काष्ठा tar_arch_info_t *tar_arch)
अणु
	काष्ठा tar_ucode_info_t *curr, *temp;

	अगर (!tar_arch)
		वापस;

	list_क्रम_each_entry_safe(curr, temp, &tar_arch->ucodes, list) अणु
		list_del(&curr->list);
		kमुक्त(curr);
	पूर्ण

	अगर (tar_arch->fw)
		release_firmware(tar_arch->fw);
	kमुक्त(tar_arch);
पूर्ण

अटल काष्ठा tar_ucode_info_t *get_uc_from_tar_archive(
					काष्ठा tar_arch_info_t *tar_arch,
					पूर्णांक ucode_type)
अणु
	काष्ठा tar_ucode_info_t *curr, *uc_found = शून्य;

	list_क्रम_each_entry(curr, &tar_arch->ucodes, list) अणु
		अगर (!is_eng_type(curr->ucode.type, ucode_type))
			जारी;

		अगर (!uc_found) अणु
			uc_found = curr;
			जारी;
		पूर्ण

		चयन (ucode_type) अणु
		हाल OTX_CPT_AE_TYPES:
			अवरोध;

		हाल OTX_CPT_SE_TYPES:
			अगर (uc_found->ucode.ver_num.nn == OTX_CPT_SE_UC_TYPE2 ||
			    (uc_found->ucode.ver_num.nn == OTX_CPT_SE_UC_TYPE3
			     && curr->ucode.ver_num.nn == OTX_CPT_SE_UC_TYPE1))
				uc_found = curr;
			अवरोध;
		पूर्ण
	पूर्ण

	वापस uc_found;
पूर्ण

अटल व्योम prपूर्णांक_tar_dbg_info(काष्ठा tar_arch_info_t *tar_arch,
			       अक्षर *tar_filename)
अणु
	काष्ठा tar_ucode_info_t *curr;

	pr_debug("Tar archive filename %s\n", tar_filename);
	pr_debug("Tar archive pointer %p, size %ld\n", tar_arch->fw->data,
		 tar_arch->fw->size);
	list_क्रम_each_entry(curr, &tar_arch->ucodes, list) अणु
		pr_debug("Ucode filename %s\n", curr->ucode.filename);
		pr_debug("Ucode version string %s\n", curr->ucode.ver_str);
		pr_debug("Ucode version %d.%d.%d.%d\n",
			 curr->ucode.ver_num.nn, curr->ucode.ver_num.xx,
			 curr->ucode.ver_num.yy, curr->ucode.ver_num.zz);
		pr_debug("Ucode type (%d) %s\n", curr->ucode.type,
			 get_ucode_type_str(curr->ucode.type));
		pr_debug("Ucode size %d\n", curr->ucode.size);
		pr_debug("Ucode ptr %p\n", curr->ucode_ptr);
	पूर्ण
पूर्ण

अटल काष्ठा tar_arch_info_t *load_tar_archive(काष्ठा device *dev,
						अक्षर *tar_filename)
अणु
	काष्ठा tar_arch_info_t *tar_arch = शून्य;
	काष्ठा tar_blk_t *tar_blk;
	अचिन्हित पूर्णांक cur_size;
	माप_प्रकार tar_offs = 0;
	माप_प्रकार tar_size;
	पूर्णांक ret;

	tar_arch = kzalloc(माप(काष्ठा tar_arch_info_t), GFP_KERNEL);
	अगर (!tar_arch)
		वापस शून्य;

	INIT_LIST_HEAD(&tar_arch->ucodes);

	/* Load tar archive */
	ret = request_firmware(&tar_arch->fw, tar_filename, dev);
	अगर (ret)
		जाओ release_tar_arch;

	अगर (tar_arch->fw->size < TAR_BLOCK_LEN) अणु
		dev_err(dev, "Invalid tar archive %s\n", tar_filename);
		जाओ release_tar_arch;
	पूर्ण

	tar_size = tar_arch->fw->size;
	tar_blk = (काष्ठा tar_blk_t *) tar_arch->fw->data;
	अगर (म_भेदन(tar_blk->hdr.magic, TAR_MAGIC, TAR_MAGIC_LEN - 1)) अणु
		dev_err(dev, "Unsupported format of tar archive %s\n",
			tar_filename);
		जाओ release_tar_arch;
	पूर्ण

	जबतक (1) अणु
		/* Read current file size */
		ret = kstrtouपूर्णांक(tar_blk->hdr.size, 8, &cur_size);
		अगर (ret)
			जाओ release_tar_arch;

		अगर (tar_offs + cur_size > tar_size ||
		    tar_offs + 2*TAR_BLOCK_LEN > tar_size) अणु
			dev_err(dev, "Invalid tar archive %s\n", tar_filename);
			जाओ release_tar_arch;
		पूर्ण

		tar_offs += TAR_BLOCK_LEN;
		अगर (tar_blk->hdr.typeflag == REGTYPE ||
		    tar_blk->hdr.typeflag == AREGTYPE) अणु
			ret = process_tar_file(dev, tar_arch,
					       tar_blk->hdr.name,
					       &tar_arch->fw->data[tar_offs],
					       cur_size);
			अगर (ret)
				जाओ release_tar_arch;
		पूर्ण

		tar_offs += (cur_size/TAR_BLOCK_LEN) * TAR_BLOCK_LEN;
		अगर (cur_size % TAR_BLOCK_LEN)
			tar_offs += TAR_BLOCK_LEN;

		/* Check क्रम the end of the archive */
		अगर (tar_offs + 2*TAR_BLOCK_LEN > tar_size) अणु
			dev_err(dev, "Invalid tar archive %s\n", tar_filename);
			जाओ release_tar_arch;
		पूर्ण

		अगर (is_mem_zero(&tar_arch->fw->data[tar_offs],
		    2*TAR_BLOCK_LEN))
			अवरोध;

		/* Read next block from tar archive */
		tar_blk = (काष्ठा tar_blk_t *) &tar_arch->fw->data[tar_offs];
	पूर्ण

	prपूर्णांक_tar_dbg_info(tar_arch, tar_filename);
	वापस tar_arch;
release_tar_arch:
	release_tar_archive(tar_arch);
	वापस शून्य;
पूर्ण

अटल काष्ठा otx_cpt_engs_rsvd *find_engines_by_type(
					काष्ठा otx_cpt_eng_grp_info *eng_grp,
					पूर्णांक eng_type)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < OTX_CPT_MAX_ETYPES_PER_GRP; i++) अणु
		अगर (!eng_grp->engs[i].type)
			जारी;

		अगर (eng_grp->engs[i].type == eng_type)
			वापस &eng_grp->engs[i];
	पूर्ण
	वापस शून्य;
पूर्ण

पूर्णांक otx_cpt_uc_supports_eng_type(काष्ठा otx_cpt_ucode *ucode, पूर्णांक eng_type)
अणु
	वापस is_eng_type(ucode->type, eng_type);
पूर्ण
EXPORT_SYMBOL_GPL(otx_cpt_uc_supports_eng_type);

पूर्णांक otx_cpt_eng_grp_has_eng_type(काष्ठा otx_cpt_eng_grp_info *eng_grp,
				 पूर्णांक eng_type)
अणु
	काष्ठा otx_cpt_engs_rsvd *engs;

	engs = find_engines_by_type(eng_grp, eng_type);

	वापस (engs != शून्य ? 1 : 0);
पूर्ण
EXPORT_SYMBOL_GPL(otx_cpt_eng_grp_has_eng_type);

अटल व्योम prपूर्णांक_ucode_info(काष्ठा otx_cpt_eng_grp_info *eng_grp,
			     अक्षर *buf, पूर्णांक size)
अणु
	अगर (eng_grp->mirror.is_ena) अणु
		scnम_लिखो(buf, size, "%s (shared with engine_group%d)",
			  eng_grp->g->grp[eng_grp->mirror.idx].ucode[0].ver_str,
			  eng_grp->mirror.idx);
	पूर्ण अन्यथा अणु
		scnम_लिखो(buf, size, "%s", eng_grp->ucode[0].ver_str);
	पूर्ण
पूर्ण

अटल व्योम prपूर्णांक_engs_info(काष्ठा otx_cpt_eng_grp_info *eng_grp,
			    अक्षर *buf, पूर्णांक size, पूर्णांक idx)
अणु
	काष्ठा otx_cpt_engs_rsvd *mirrored_engs = शून्य;
	काष्ठा otx_cpt_engs_rsvd *engs;
	पूर्णांक len, i;

	buf[0] = '\0';
	क्रम (i = 0; i < OTX_CPT_MAX_ETYPES_PER_GRP; i++) अणु
		engs = &eng_grp->engs[i];
		अगर (!engs->type)
			जारी;
		अगर (idx != -1 && idx != i)
			जारी;

		अगर (eng_grp->mirror.is_ena)
			mirrored_engs = find_engines_by_type(
					&eng_grp->g->grp[eng_grp->mirror.idx],
					engs->type);
		अगर (i > 0 && idx == -1) अणु
			len = म_माप(buf);
			scnम_लिखो(buf+len, size-len, ", ");
		पूर्ण

		len = म_माप(buf);
		scnम_लिखो(buf+len, size-len, "%d %s ", mirrored_engs ?
			  engs->count + mirrored_engs->count : engs->count,
			  get_eng_type_str(engs->type));
		अगर (mirrored_engs) अणु
			len = म_माप(buf);
			scnम_लिखो(buf+len, size-len,
				  "(%d shared with engine_group%d) ",
				  engs->count <= 0 ? engs->count +
				  mirrored_engs->count : mirrored_engs->count,
				  eng_grp->mirror.idx);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम prपूर्णांक_ucode_dbg_info(काष्ठा otx_cpt_ucode *ucode)
अणु
	pr_debug("Ucode info\n");
	pr_debug("Ucode version string %s\n", ucode->ver_str);
	pr_debug("Ucode version %d.%d.%d.%d\n", ucode->ver_num.nn,
		 ucode->ver_num.xx, ucode->ver_num.yy, ucode->ver_num.zz);
	pr_debug("Ucode type %s\n", get_ucode_type_str(ucode->type));
	pr_debug("Ucode size %d\n", ucode->size);
	pr_debug("Ucode virt address %16.16llx\n", (u64)ucode->align_va);
	pr_debug("Ucode phys address %16.16llx\n", ucode->align_dma);
पूर्ण

अटल व्योम cpt_prपूर्णांक_engines_mask(काष्ठा otx_cpt_eng_grp_info *eng_grp,
				   काष्ठा device *dev, अक्षर *buf, पूर्णांक size)
अणु
	काष्ठा otx_cpt_biपंचांगap bmap;
	u32 mask[2];

	bmap = get_cores_bmap(dev, eng_grp);
	अगर (!bmap.size) अणु
		scnम_लिखो(buf, size, "unknown");
		वापस;
	पूर्ण
	biपंचांगap_to_arr32(mask, bmap.bits, bmap.size);
	scnम_लिखो(buf, size, "%8.8x %8.8x", mask[1], mask[0]);
पूर्ण


अटल व्योम prपूर्णांक_dbg_info(काष्ठा device *dev,
			   काष्ठा otx_cpt_eng_grps *eng_grps)
अणु
	अक्षर engs_info[2*OTX_CPT_UCODE_NAME_LENGTH];
	काष्ठा otx_cpt_eng_grp_info *mirrored_grp;
	अक्षर engs_mask[OTX_CPT_UCODE_NAME_LENGTH];
	काष्ठा otx_cpt_eng_grp_info *grp;
	काष्ठा otx_cpt_engs_rsvd *engs;
	u32 mask[4];
	पूर्णांक i, j;

	pr_debug("Engine groups global info\n");
	pr_debug("max SE %d, max AE %d\n",
		 eng_grps->avail.max_se_cnt, eng_grps->avail.max_ae_cnt);
	pr_debug("free SE %d\n", eng_grps->avail.se_cnt);
	pr_debug("free AE %d\n", eng_grps->avail.ae_cnt);

	क्रम (i = 0; i < OTX_CPT_MAX_ENGINE_GROUPS; i++) अणु
		grp = &eng_grps->grp[i];
		pr_debug("engine_group%d, state %s\n", i, grp->is_enabled ?
			 "enabled" : "disabled");
		अगर (grp->is_enabled) अणु
			mirrored_grp = &eng_grps->grp[grp->mirror.idx];
			pr_debug("Ucode0 filename %s, version %s\n",
				 grp->mirror.is_ena ?
				 mirrored_grp->ucode[0].filename :
				 grp->ucode[0].filename,
				 grp->mirror.is_ena ?
				 mirrored_grp->ucode[0].ver_str :
				 grp->ucode[0].ver_str);
		पूर्ण

		क्रम (j = 0; j < OTX_CPT_MAX_ETYPES_PER_GRP; j++) अणु
			engs = &grp->engs[j];
			अगर (engs->type) अणु
				prपूर्णांक_engs_info(grp, engs_info,
						2*OTX_CPT_UCODE_NAME_LENGTH, j);
				pr_debug("Slot%d: %s\n", j, engs_info);
				biपंचांगap_to_arr32(mask, engs->bmap,
						eng_grps->engs_num);
				pr_debug("Mask: %8.8x %8.8x %8.8x %8.8x\n",
					 mask[3], mask[2], mask[1], mask[0]);
			पूर्ण अन्यथा
				pr_debug("Slot%d not used\n", j);
		पूर्ण
		अगर (grp->is_enabled) अणु
			cpt_prपूर्णांक_engines_mask(grp, dev, engs_mask,
					       OTX_CPT_UCODE_NAME_LENGTH);
			pr_debug("Cmask: %s\n", engs_mask);
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक update_engines_avail_count(काष्ठा device *dev,
				      काष्ठा otx_cpt_engs_available *avail,
				      काष्ठा otx_cpt_engs_rsvd *engs, पूर्णांक val)
अणु
	चयन (engs->type) अणु
	हाल OTX_CPT_SE_TYPES:
		avail->se_cnt += val;
		अवरोध;

	हाल OTX_CPT_AE_TYPES:
		avail->ae_cnt += val;
		अवरोध;

	शेष:
		dev_err(dev, "Invalid engine type %d\n", engs->type);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक update_engines_offset(काष्ठा device *dev,
				 काष्ठा otx_cpt_engs_available *avail,
				 काष्ठा otx_cpt_engs_rsvd *engs)
अणु
	चयन (engs->type) अणु
	हाल OTX_CPT_SE_TYPES:
		engs->offset = 0;
		अवरोध;

	हाल OTX_CPT_AE_TYPES:
		engs->offset = avail->max_se_cnt;
		अवरोध;

	शेष:
		dev_err(dev, "Invalid engine type %d\n", engs->type);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक release_engines(काष्ठा device *dev, काष्ठा otx_cpt_eng_grp_info *grp)
अणु
	पूर्णांक i, ret = 0;

	क्रम (i = 0; i < OTX_CPT_MAX_ETYPES_PER_GRP; i++) अणु
		अगर (!grp->engs[i].type)
			जारी;

		अगर (grp->engs[i].count > 0) अणु
			ret = update_engines_avail_count(dev, &grp->g->avail,
							 &grp->engs[i],
							 grp->engs[i].count);
			अगर (ret)
				वापस ret;
		पूर्ण

		grp->engs[i].type = 0;
		grp->engs[i].count = 0;
		grp->engs[i].offset = 0;
		grp->engs[i].ucode = शून्य;
		biपंचांगap_zero(grp->engs[i].bmap, grp->g->engs_num);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक करो_reserve_engines(काष्ठा device *dev,
			      काष्ठा otx_cpt_eng_grp_info *grp,
			      काष्ठा otx_cpt_engines *req_engs)
अणु
	काष्ठा otx_cpt_engs_rsvd *engs = शून्य;
	पूर्णांक i, ret;

	क्रम (i = 0; i < OTX_CPT_MAX_ETYPES_PER_GRP; i++) अणु
		अगर (!grp->engs[i].type) अणु
			engs = &grp->engs[i];
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!engs)
		वापस -ENOMEM;

	engs->type = req_engs->type;
	engs->count = req_engs->count;

	ret = update_engines_offset(dev, &grp->g->avail, engs);
	अगर (ret)
		वापस ret;

	अगर (engs->count > 0) अणु
		ret = update_engines_avail_count(dev, &grp->g->avail, engs,
						 -engs->count);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक check_engines_availability(काष्ठा device *dev,
				      काष्ठा otx_cpt_eng_grp_info *grp,
				      काष्ठा otx_cpt_engines *req_eng)
अणु
	पूर्णांक avail_cnt = 0;

	चयन (req_eng->type) अणु
	हाल OTX_CPT_SE_TYPES:
		avail_cnt = grp->g->avail.se_cnt;
		अवरोध;

	हाल OTX_CPT_AE_TYPES:
		avail_cnt = grp->g->avail.ae_cnt;
		अवरोध;

	शेष:
		dev_err(dev, "Invalid engine type %d\n", req_eng->type);
		वापस -EINVAL;
	पूर्ण

	अगर (avail_cnt < req_eng->count) अणु
		dev_err(dev,
			"Error available %s engines %d < than requested %d\n",
			get_eng_type_str(req_eng->type),
			avail_cnt, req_eng->count);
		वापस -EBUSY;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक reserve_engines(काष्ठा device *dev, काष्ठा otx_cpt_eng_grp_info *grp,
			   काष्ठा otx_cpt_engines *req_engs, पूर्णांक req_cnt)
अणु
	पूर्णांक i, ret;

	/* Validate अगर a number of requested engines is available */
	क्रम (i = 0; i < req_cnt; i++) अणु
		ret = check_engines_availability(dev, grp, &req_engs[i]);
		अगर (ret)
			वापस ret;
	पूर्ण

	/* Reserve requested engines क्रम this engine group */
	क्रम (i = 0; i < req_cnt; i++) अणु
		ret = करो_reserve_engines(dev, grp, &req_engs[i]);
		अगर (ret)
			वापस ret;
	पूर्ण
	वापस 0;
पूर्ण

अटल sमाप_प्रकार eng_grp_info_show(काष्ठा device *dev,
				 काष्ठा device_attribute *attr,
				 अक्षर *buf)
अणु
	अक्षर ucode_info[2*OTX_CPT_UCODE_NAME_LENGTH];
	अक्षर engs_info[2*OTX_CPT_UCODE_NAME_LENGTH];
	अक्षर engs_mask[OTX_CPT_UCODE_NAME_LENGTH];
	काष्ठा otx_cpt_eng_grp_info *eng_grp;
	पूर्णांक ret;

	eng_grp = container_of(attr, काष्ठा otx_cpt_eng_grp_info, info_attr);
	mutex_lock(&eng_grp->g->lock);

	prपूर्णांक_engs_info(eng_grp, engs_info, 2*OTX_CPT_UCODE_NAME_LENGTH, -1);
	prपूर्णांक_ucode_info(eng_grp, ucode_info, 2*OTX_CPT_UCODE_NAME_LENGTH);
	cpt_prपूर्णांक_engines_mask(eng_grp, dev, engs_mask,
			       OTX_CPT_UCODE_NAME_LENGTH);
	ret = scnम_लिखो(buf, PAGE_SIZE,
			"Microcode : %s\nEngines: %s\nEngines mask: %s\n",
			ucode_info, engs_info, engs_mask);

	mutex_unlock(&eng_grp->g->lock);
	वापस ret;
पूर्ण

अटल पूर्णांक create_sysfs_eng_grps_info(काष्ठा device *dev,
				      काष्ठा otx_cpt_eng_grp_info *eng_grp)
अणु
	eng_grp->info_attr.show = eng_grp_info_show;
	eng_grp->info_attr.store = शून्य;
	eng_grp->info_attr.attr.name = eng_grp->sysfs_info_name;
	eng_grp->info_attr.attr.mode = 0440;
	sysfs_attr_init(&eng_grp->info_attr.attr);
	वापस device_create_file(dev, &eng_grp->info_attr);
पूर्ण

अटल व्योम ucode_unload(काष्ठा device *dev, काष्ठा otx_cpt_ucode *ucode)
अणु
	अगर (ucode->va) अणु
		dma_मुक्त_coherent(dev, ucode->size + OTX_CPT_UCODE_ALIGNMENT,
				  ucode->va, ucode->dma);
		ucode->va = शून्य;
		ucode->align_va = शून्य;
		ucode->dma = 0;
		ucode->align_dma = 0;
		ucode->size = 0;
	पूर्ण

	स_रखो(&ucode->ver_str, 0, OTX_CPT_UCODE_VER_STR_SZ);
	स_रखो(&ucode->ver_num, 0, माप(काष्ठा otx_cpt_ucode_ver_num));
	set_ucode_filename(ucode, "");
	ucode->type = 0;
पूर्ण

अटल पूर्णांक copy_ucode_to_dma_mem(काष्ठा device *dev,
				 काष्ठा otx_cpt_ucode *ucode,
				 स्थिर u8 *ucode_data)
अणु
	u32 i;

	/*  Allocate DMAable space */
	ucode->va = dma_alloc_coherent(dev, ucode->size +
				       OTX_CPT_UCODE_ALIGNMENT,
				       &ucode->dma, GFP_KERNEL);
	अगर (!ucode->va) अणु
		dev_err(dev, "Unable to allocate space for microcode\n");
		वापस -ENOMEM;
	पूर्ण
	ucode->align_va = PTR_ALIGN(ucode->va, OTX_CPT_UCODE_ALIGNMENT);
	ucode->align_dma = PTR_ALIGN(ucode->dma, OTX_CPT_UCODE_ALIGNMENT);

	स_नकल((व्योम *) ucode->align_va, (व्योम *) ucode_data +
	       माप(काष्ठा otx_cpt_ucode_hdr), ucode->size);

	/* Byte swap 64-bit */
	क्रम (i = 0; i < (ucode->size / 8); i++)
		((__be64 *)ucode->align_va)[i] =
				cpu_to_be64(((u64 *)ucode->align_va)[i]);
	/*  Ucode needs 16-bit swap */
	क्रम (i = 0; i < (ucode->size / 2); i++)
		((__be16 *)ucode->align_va)[i] =
				cpu_to_be16(((u16 *)ucode->align_va)[i]);
	वापस 0;
पूर्ण

अटल पूर्णांक ucode_load(काष्ठा device *dev, काष्ठा otx_cpt_ucode *ucode,
		      स्थिर अक्षर *ucode_filename)
अणु
	काष्ठा otx_cpt_ucode_hdr *ucode_hdr;
	स्थिर काष्ठा firmware *fw;
	पूर्णांक ret;

	set_ucode_filename(ucode, ucode_filename);
	ret = request_firmware(&fw, ucode->filename, dev);
	अगर (ret)
		वापस ret;

	ucode_hdr = (काष्ठा otx_cpt_ucode_hdr *) fw->data;
	स_नकल(ucode->ver_str, ucode_hdr->ver_str, OTX_CPT_UCODE_VER_STR_SZ);
	ucode->ver_num = ucode_hdr->ver_num;
	ucode->size = ntohl(ucode_hdr->code_length) * 2;
	अगर (!ucode->size || (fw->size < round_up(ucode->size, 16)
	    + माप(काष्ठा otx_cpt_ucode_hdr) + OTX_CPT_UCODE_SIGN_LEN)) अणु
		dev_err(dev, "Ucode %s invalid size\n", ucode_filename);
		ret = -EINVAL;
		जाओ release_fw;
	पूर्ण

	ret = get_ucode_type(ucode_hdr, &ucode->type);
	अगर (ret) अणु
		dev_err(dev, "Microcode %s unknown type 0x%x\n",
			ucode->filename, ucode->type);
		जाओ release_fw;
	पूर्ण

	ret = copy_ucode_to_dma_mem(dev, ucode, fw->data);
	अगर (ret)
		जाओ release_fw;

	prपूर्णांक_ucode_dbg_info(ucode);
release_fw:
	release_firmware(fw);
	वापस ret;
पूर्ण

अटल पूर्णांक enable_eng_grp(काष्ठा otx_cpt_eng_grp_info *eng_grp,
			  व्योम *obj)
अणु
	पूर्णांक ret;

	ret = cpt_set_ucode_base(eng_grp, obj);
	अगर (ret)
		वापस ret;

	ret = cpt_attach_and_enable_cores(eng_grp, obj);
	वापस ret;
पूर्ण

अटल पूर्णांक disable_eng_grp(काष्ठा device *dev,
			   काष्ठा otx_cpt_eng_grp_info *eng_grp,
			   व्योम *obj)
अणु
	पूर्णांक i, ret;

	ret = cpt_detach_and_disable_cores(eng_grp, obj);
	अगर (ret)
		वापस ret;

	/* Unload ucode used by this engine group */
	ucode_unload(dev, &eng_grp->ucode[0]);

	क्रम (i = 0; i < OTX_CPT_MAX_ETYPES_PER_GRP; i++) अणु
		अगर (!eng_grp->engs[i].type)
			जारी;

		eng_grp->engs[i].ucode = &eng_grp->ucode[0];
	पूर्ण

	ret = cpt_set_ucode_base(eng_grp, obj);

	वापस ret;
पूर्ण

अटल व्योम setup_eng_grp_mirroring(काष्ठा otx_cpt_eng_grp_info *dst_grp,
				    काष्ठा otx_cpt_eng_grp_info *src_grp)
अणु
	/* Setup fields क्रम engine group which is mirrored */
	src_grp->mirror.is_ena = false;
	src_grp->mirror.idx = 0;
	src_grp->mirror.ref_count++;

	/* Setup fields क्रम mirroring engine group */
	dst_grp->mirror.is_ena = true;
	dst_grp->mirror.idx = src_grp->idx;
	dst_grp->mirror.ref_count = 0;
पूर्ण

अटल व्योम हटाओ_eng_grp_mirroring(काष्ठा otx_cpt_eng_grp_info *dst_grp)
अणु
	काष्ठा otx_cpt_eng_grp_info *src_grp;

	अगर (!dst_grp->mirror.is_ena)
		वापस;

	src_grp = &dst_grp->g->grp[dst_grp->mirror.idx];

	src_grp->mirror.ref_count--;
	dst_grp->mirror.is_ena = false;
	dst_grp->mirror.idx = 0;
	dst_grp->mirror.ref_count = 0;
पूर्ण

अटल व्योम update_requested_engs(काष्ठा otx_cpt_eng_grp_info *mirrored_eng_grp,
				  काष्ठा otx_cpt_engines *engs, पूर्णांक engs_cnt)
अणु
	काष्ठा otx_cpt_engs_rsvd *mirrored_engs;
	पूर्णांक i;

	क्रम (i = 0; i < engs_cnt; i++) अणु
		mirrored_engs = find_engines_by_type(mirrored_eng_grp,
						     engs[i].type);
		अगर (!mirrored_engs)
			जारी;

		/*
		 * If mirrored group has this type of engines attached then
		 * there are 3 scenarios possible:
		 * 1) mirrored_engs.count == engs[i].count then all engines
		 * from mirrored engine group will be shared with this engine
		 * group
		 * 2) mirrored_engs.count > engs[i].count then only a subset of
		 * engines from mirrored engine group will be shared with this
		 * engine group
		 * 3) mirrored_engs.count < engs[i].count then all engines
		 * from mirrored engine group will be shared with this group
		 * and additional engines will be reserved क्रम exclusively use
		 * by this engine group
		 */
		engs[i].count -= mirrored_engs->count;
	पूर्ण
पूर्ण

अटल काष्ठा otx_cpt_eng_grp_info *find_mirrored_eng_grp(
					काष्ठा otx_cpt_eng_grp_info *grp)
अणु
	काष्ठा otx_cpt_eng_grps *eng_grps = grp->g;
	पूर्णांक i;

	क्रम (i = 0; i < OTX_CPT_MAX_ENGINE_GROUPS; i++) अणु
		अगर (!eng_grps->grp[i].is_enabled)
			जारी;
		अगर (eng_grps->grp[i].ucode[0].type)
			जारी;
		अगर (grp->idx == i)
			जारी;
		अगर (!strnहालcmp(eng_grps->grp[i].ucode[0].ver_str,
				 grp->ucode[0].ver_str,
				 OTX_CPT_UCODE_VER_STR_SZ))
			वापस &eng_grps->grp[i];
	पूर्ण

	वापस शून्य;
पूर्ण

अटल काष्ठा otx_cpt_eng_grp_info *find_unused_eng_grp(
					काष्ठा otx_cpt_eng_grps *eng_grps)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < OTX_CPT_MAX_ENGINE_GROUPS; i++) अणु
		अगर (!eng_grps->grp[i].is_enabled)
			वापस &eng_grps->grp[i];
	पूर्ण
	वापस शून्य;
पूर्ण

अटल पूर्णांक eng_grp_update_masks(काष्ठा device *dev,
				काष्ठा otx_cpt_eng_grp_info *eng_grp)
अणु
	काष्ठा otx_cpt_engs_rsvd *engs, *mirrored_engs;
	काष्ठा otx_cpt_biपंचांगap पंचांगp_bmap = अणु अणु0पूर्ण पूर्ण;
	पूर्णांक i, j, cnt, max_cnt;
	पूर्णांक bit;

	क्रम (i = 0; i < OTX_CPT_MAX_ETYPES_PER_GRP; i++) अणु
		engs = &eng_grp->engs[i];
		अगर (!engs->type)
			जारी;
		अगर (engs->count <= 0)
			जारी;

		चयन (engs->type) अणु
		हाल OTX_CPT_SE_TYPES:
			max_cnt = eng_grp->g->avail.max_se_cnt;
			अवरोध;

		हाल OTX_CPT_AE_TYPES:
			max_cnt = eng_grp->g->avail.max_ae_cnt;
			अवरोध;

		शेष:
			dev_err(dev, "Invalid engine type %d\n", engs->type);
			वापस -EINVAL;
		पूर्ण

		cnt = engs->count;
		WARN_ON(engs->offset + max_cnt > OTX_CPT_MAX_ENGINES);
		biपंचांगap_zero(पंचांगp_bmap.bits, eng_grp->g->engs_num);
		क्रम (j = engs->offset; j < engs->offset + max_cnt; j++) अणु
			अगर (!eng_grp->g->eng_ref_cnt[j]) अणु
				biपंचांगap_set(पंचांगp_bmap.bits, j, 1);
				cnt--;
				अगर (!cnt)
					अवरोध;
			पूर्ण
		पूर्ण

		अगर (cnt)
			वापस -ENOSPC;

		biपंचांगap_copy(engs->bmap, पंचांगp_bmap.bits, eng_grp->g->engs_num);
	पूर्ण

	अगर (!eng_grp->mirror.is_ena)
		वापस 0;

	क्रम (i = 0; i < OTX_CPT_MAX_ETYPES_PER_GRP; i++) अणु
		engs = &eng_grp->engs[i];
		अगर (!engs->type)
			जारी;

		mirrored_engs = find_engines_by_type(
					&eng_grp->g->grp[eng_grp->mirror.idx],
					engs->type);
		WARN_ON(!mirrored_engs && engs->count <= 0);
		अगर (!mirrored_engs)
			जारी;

		biपंचांगap_copy(पंचांगp_bmap.bits, mirrored_engs->bmap,
			    eng_grp->g->engs_num);
		अगर (engs->count < 0) अणु
			bit = find_first_bit(mirrored_engs->bmap,
					     eng_grp->g->engs_num);
			biपंचांगap_clear(पंचांगp_bmap.bits, bit, -engs->count);
		पूर्ण
		biपंचांगap_or(engs->bmap, engs->bmap, पंचांगp_bmap.bits,
			  eng_grp->g->engs_num);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक delete_engine_group(काष्ठा device *dev,
			       काष्ठा otx_cpt_eng_grp_info *eng_grp)
अणु
	पूर्णांक i, ret;

	अगर (!eng_grp->is_enabled)
		वापस -EINVAL;

	अगर (eng_grp->mirror.ref_count) अणु
		dev_err(dev, "Can't delete engine_group%d as it is used by engine_group(s):",
			eng_grp->idx);
		क्रम (i = 0; i < OTX_CPT_MAX_ENGINE_GROUPS; i++) अणु
			अगर (eng_grp->g->grp[i].mirror.is_ena &&
			    eng_grp->g->grp[i].mirror.idx == eng_grp->idx)
				pr_cont(" %d", i);
		पूर्ण
		pr_cont("\n");
		वापस -EINVAL;
	पूर्ण

	/* Removing engine group mirroring अगर enabled */
	हटाओ_eng_grp_mirroring(eng_grp);

	/* Disable engine group */
	ret = disable_eng_grp(dev, eng_grp, eng_grp->g->obj);
	अगर (ret)
		वापस ret;

	/* Release all engines held by this engine group */
	ret = release_engines(dev, eng_grp);
	अगर (ret)
		वापस ret;

	device_हटाओ_file(dev, &eng_grp->info_attr);
	eng_grp->is_enabled = false;

	वापस 0;
पूर्ण

अटल पूर्णांक validate_1_ucode_scenario(काष्ठा device *dev,
				     काष्ठा otx_cpt_eng_grp_info *eng_grp,
				     काष्ठा otx_cpt_engines *engs, पूर्णांक engs_cnt)
अणु
	पूर्णांक i;

	/* Verअगरy that ucode loaded supports requested engine types */
	क्रम (i = 0; i < engs_cnt; i++) अणु
		अगर (!otx_cpt_uc_supports_eng_type(&eng_grp->ucode[0],
						  engs[i].type)) अणु
			dev_err(dev,
				"Microcode %s does not support %s engines\n",
				eng_grp->ucode[0].filename,
				get_eng_type_str(engs[i].type));
			वापस -EINVAL;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम update_ucode_ptrs(काष्ठा otx_cpt_eng_grp_info *eng_grp)
अणु
	काष्ठा otx_cpt_ucode *ucode;

	अगर (eng_grp->mirror.is_ena)
		ucode = &eng_grp->g->grp[eng_grp->mirror.idx].ucode[0];
	अन्यथा
		ucode = &eng_grp->ucode[0];
	WARN_ON(!eng_grp->engs[0].type);
	eng_grp->engs[0].ucode = ucode;
पूर्ण

अटल पूर्णांक create_engine_group(काष्ठा device *dev,
			       काष्ठा otx_cpt_eng_grps *eng_grps,
			       काष्ठा otx_cpt_engines *engs, पूर्णांक engs_cnt,
			       व्योम *ucode_data[], पूर्णांक ucodes_cnt,
			       bool use_uc_from_tar_arch)
अणु
	काष्ठा otx_cpt_eng_grp_info *mirrored_eng_grp;
	काष्ठा tar_ucode_info_t *tar_info;
	काष्ठा otx_cpt_eng_grp_info *eng_grp;
	पूर्णांक i, ret = 0;

	अगर (ucodes_cnt > OTX_CPT_MAX_ETYPES_PER_GRP)
		वापस -EINVAL;

	/* Validate अगर requested engine types are supported by this device */
	क्रम (i = 0; i < engs_cnt; i++)
		अगर (!dev_supports_eng_type(eng_grps, engs[i].type)) अणु
			dev_err(dev, "Device does not support %s engines\n",
				get_eng_type_str(engs[i].type));
			वापस -EPERM;
		पूर्ण

	/* Find engine group which is not used */
	eng_grp = find_unused_eng_grp(eng_grps);
	अगर (!eng_grp) अणु
		dev_err(dev, "Error all engine groups are being used\n");
		वापस -ENOSPC;
	पूर्ण

	/* Load ucode */
	क्रम (i = 0; i < ucodes_cnt; i++) अणु
		अगर (use_uc_from_tar_arch) अणु
			tar_info = (काष्ठा tar_ucode_info_t *) ucode_data[i];
			eng_grp->ucode[i] = tar_info->ucode;
			ret = copy_ucode_to_dma_mem(dev, &eng_grp->ucode[i],
						    tar_info->ucode_ptr);
		पूर्ण अन्यथा
			ret = ucode_load(dev, &eng_grp->ucode[i],
					 (अक्षर *) ucode_data[i]);
		अगर (ret)
			जाओ err_ucode_unload;
	पूर्ण

	/* Validate scenario where 1 ucode is used */
	ret = validate_1_ucode_scenario(dev, eng_grp, engs, engs_cnt);
	अगर (ret)
		जाओ err_ucode_unload;

	/* Check अगर this group mirrors another existing engine group */
	mirrored_eng_grp = find_mirrored_eng_grp(eng_grp);
	अगर (mirrored_eng_grp) अणु
		/* Setup mirroring */
		setup_eng_grp_mirroring(eng_grp, mirrored_eng_grp);

		/*
		 * Update count of requested engines because some
		 * of them might be shared with mirrored group
		 */
		update_requested_engs(mirrored_eng_grp, engs, engs_cnt);
	पूर्ण

	/* Reserve engines */
	ret = reserve_engines(dev, eng_grp, engs, engs_cnt);
	अगर (ret)
		जाओ err_ucode_unload;

	/* Update ucode poपूर्णांकers used by engines */
	update_ucode_ptrs(eng_grp);

	/* Update engine masks used by this group */
	ret = eng_grp_update_masks(dev, eng_grp);
	अगर (ret)
		जाओ err_release_engs;

	/* Create sysfs entry क्रम engine group info */
	ret = create_sysfs_eng_grps_info(dev, eng_grp);
	अगर (ret)
		जाओ err_release_engs;

	/* Enable engine group */
	ret = enable_eng_grp(eng_grp, eng_grps->obj);
	अगर (ret)
		जाओ err_release_engs;

	/*
	 * If this engine group mirrors another engine group
	 * then we need to unload ucode as we will use ucode
	 * from mirrored engine group
	 */
	अगर (eng_grp->mirror.is_ena)
		ucode_unload(dev, &eng_grp->ucode[0]);

	eng_grp->is_enabled = true;
	अगर (eng_grp->mirror.is_ena)
		dev_info(dev,
			 "Engine_group%d: reuse microcode %s from group %d\n",
			 eng_grp->idx, mirrored_eng_grp->ucode[0].ver_str,
			 mirrored_eng_grp->idx);
	अन्यथा
		dev_info(dev, "Engine_group%d: microcode loaded %s\n",
			 eng_grp->idx, eng_grp->ucode[0].ver_str);

	वापस 0;

err_release_engs:
	release_engines(dev, eng_grp);
err_ucode_unload:
	ucode_unload(dev, &eng_grp->ucode[0]);
	वापस ret;
पूर्ण

अटल sमाप_प्रकार ucode_load_store(काष्ठा device *dev,
				काष्ठा device_attribute *attr,
				स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा otx_cpt_engines engs[OTX_CPT_MAX_ETYPES_PER_GRP] = अणु अणु0पूर्ण पूर्ण;
	अक्षर *ucode_filename[OTX_CPT_MAX_ETYPES_PER_GRP];
	अक्षर पंचांगp_buf[OTX_CPT_UCODE_NAME_LENGTH] = अणु 0 पूर्ण;
	अक्षर *start, *val, *err_msg, *पंचांगp;
	काष्ठा otx_cpt_eng_grps *eng_grps;
	पूर्णांक grp_idx = 0, ret = -EINVAL;
	bool has_se, has_ie, has_ae;
	पूर्णांक del_grp_idx = -1;
	पूर्णांक ucode_idx = 0;

	अगर (म_माप(buf) > OTX_CPT_UCODE_NAME_LENGTH)
		वापस -EINVAL;

	eng_grps = container_of(attr, काष्ठा otx_cpt_eng_grps, ucode_load_attr);
	err_msg = "Invalid engine group format";
	strlcpy(पंचांगp_buf, buf, OTX_CPT_UCODE_NAME_LENGTH);
	start = पंचांगp_buf;

	has_se = has_ie = has_ae = false;

	क्रम (;;) अणु
		val = strsep(&start, ";");
		अगर (!val)
			अवरोध;
		val = strim(val);
		अगर (!*val)
			जारी;

		अगर (!strnहालcmp(val, "engine_group", 12)) अणु
			अगर (del_grp_idx != -1)
				जाओ err_prपूर्णांक;
			पंचांगp = strim(strsep(&val, ":"));
			अगर (!val)
				जाओ err_prपूर्णांक;
			अगर (म_माप(पंचांगp) != 13)
				जाओ err_prपूर्णांक;
			अगर (kstrtoपूर्णांक((पंचांगp + 12), 10, &del_grp_idx))
				जाओ err_prपूर्णांक;
			val = strim(val);
			अगर (strnहालcmp(val, "null", 4))
				जाओ err_prपूर्णांक;
			अगर (म_माप(val) != 4)
				जाओ err_prपूर्णांक;
		पूर्ण अन्यथा अगर (!strnहालcmp(val, "se", 2) && म_अक्षर(val, ':')) अणु
			अगर (has_se || ucode_idx)
				जाओ err_prपूर्णांक;
			पंचांगp = strim(strsep(&val, ":"));
			अगर (!val)
				जाओ err_prपूर्णांक;
			अगर (म_माप(पंचांगp) != 2)
				जाओ err_prपूर्णांक;
			अगर (kstrtoपूर्णांक(strim(val), 10, &engs[grp_idx].count))
				जाओ err_prपूर्णांक;
			engs[grp_idx++].type = OTX_CPT_SE_TYPES;
			has_se = true;
		पूर्ण अन्यथा अगर (!strnहालcmp(val, "ae", 2) && म_अक्षर(val, ':')) अणु
			अगर (has_ae || ucode_idx)
				जाओ err_prपूर्णांक;
			पंचांगp = strim(strsep(&val, ":"));
			अगर (!val)
				जाओ err_prपूर्णांक;
			अगर (म_माप(पंचांगp) != 2)
				जाओ err_prपूर्णांक;
			अगर (kstrtoपूर्णांक(strim(val), 10, &engs[grp_idx].count))
				जाओ err_prपूर्णांक;
			engs[grp_idx++].type = OTX_CPT_AE_TYPES;
			has_ae = true;
		पूर्ण अन्यथा अणु
			अगर (ucode_idx > 1)
				जाओ err_prपूर्णांक;
			अगर (!म_माप(val))
				जाओ err_prपूर्णांक;
			अगर (strnstr(val, " ", म_माप(val)))
				जाओ err_prपूर्णांक;
			ucode_filename[ucode_idx++] = val;
		पूर्ण
	पूर्ण

	/* Validate input parameters */
	अगर (del_grp_idx == -1) अणु
		अगर (!(grp_idx && ucode_idx))
			जाओ err_prपूर्णांक;

		अगर (ucode_idx > 1 && grp_idx < 2)
			जाओ err_prपूर्णांक;

		अगर (grp_idx > OTX_CPT_MAX_ETYPES_PER_GRP) अणु
			err_msg = "Error max 2 engine types can be attached";
			जाओ err_prपूर्णांक;
		पूर्ण

	पूर्ण अन्यथा अणु
		अगर (del_grp_idx < 0 ||
		    del_grp_idx >= OTX_CPT_MAX_ENGINE_GROUPS) अणु
			dev_err(dev, "Invalid engine group index %d\n",
				del_grp_idx);
			ret = -EINVAL;
			वापस ret;
		पूर्ण

		अगर (!eng_grps->grp[del_grp_idx].is_enabled) अणु
			dev_err(dev, "Error engine_group%d is not configured\n",
				del_grp_idx);
			ret = -EINVAL;
			वापस ret;
		पूर्ण

		अगर (grp_idx || ucode_idx)
			जाओ err_prपूर्णांक;
	पूर्ण

	mutex_lock(&eng_grps->lock);

	अगर (eng_grps->is_rकरोnly) अणु
		dev_err(dev, "Disable VFs before modifying engine groups\n");
		ret = -EACCES;
		जाओ err_unlock;
	पूर्ण

	अगर (del_grp_idx == -1)
		/* create engine group */
		ret = create_engine_group(dev, eng_grps, engs, grp_idx,
					  (व्योम **) ucode_filename,
					  ucode_idx, false);
	अन्यथा
		/* delete engine group */
		ret = delete_engine_group(dev, &eng_grps->grp[del_grp_idx]);
	अगर (ret)
		जाओ err_unlock;

	prपूर्णांक_dbg_info(dev, eng_grps);
err_unlock:
	mutex_unlock(&eng_grps->lock);
	वापस ret ? ret : count;
err_prपूर्णांक:
	dev_err(dev, "%s\n", err_msg);

	वापस ret;
पूर्ण

पूर्णांक otx_cpt_try_create_शेष_eng_grps(काष्ठा pci_dev *pdev,
					काष्ठा otx_cpt_eng_grps *eng_grps,
					पूर्णांक pf_type)
अणु
	काष्ठा tar_ucode_info_t *tar_info[OTX_CPT_MAX_ETYPES_PER_GRP] = अणुपूर्ण;
	काष्ठा otx_cpt_engines engs[OTX_CPT_MAX_ETYPES_PER_GRP] = अणुपूर्ण;
	काष्ठा tar_arch_info_t *tar_arch = शून्य;
	अक्षर *tar_filename;
	पूर्णांक i, ret = 0;

	mutex_lock(&eng_grps->lock);

	/*
	 * We करोn't create engine group क्रम kernel crypto अगर attempt to create
	 * it was alपढ़ोy made (when user enabled VFs क्रम the first समय)
	 */
	अगर (eng_grps->is_first_try)
		जाओ unlock_mutex;
	eng_grps->is_first_try = true;

	/* We create group क्रम kcrypto only अगर no groups are configured */
	क्रम (i = 0; i < OTX_CPT_MAX_ENGINE_GROUPS; i++)
		अगर (eng_grps->grp[i].is_enabled)
			जाओ unlock_mutex;

	चयन (pf_type) अणु
	हाल OTX_CPT_AE:
	हाल OTX_CPT_SE:
		tar_filename = OTX_CPT_UCODE_TAR_खाता_NAME;
		अवरोध;

	शेष:
		dev_err(&pdev->dev, "Unknown PF type %d\n", pf_type);
		ret = -EINVAL;
		जाओ unlock_mutex;
	पूर्ण

	tar_arch = load_tar_archive(&pdev->dev, tar_filename);
	अगर (!tar_arch)
		जाओ unlock_mutex;

	/*
	 * If device supports SE engines and there is SE microcode in tar
	 * archive try to create engine group with SE engines क्रम kernel
	 * crypto functionality (symmetric crypto)
	 */
	tar_info[0] = get_uc_from_tar_archive(tar_arch, OTX_CPT_SE_TYPES);
	अगर (tar_info[0] &&
	    dev_supports_eng_type(eng_grps, OTX_CPT_SE_TYPES)) अणु

		engs[0].type = OTX_CPT_SE_TYPES;
		engs[0].count = eng_grps->avail.max_se_cnt;

		ret = create_engine_group(&pdev->dev, eng_grps, engs, 1,
					  (व्योम **) tar_info, 1, true);
		अगर (ret)
			जाओ release_tar_arch;
	पूर्ण
	/*
	 * If device supports AE engines and there is AE microcode in tar
	 * archive try to create engine group with AE engines क्रम asymmetric
	 * crypto functionality.
	 */
	tar_info[0] = get_uc_from_tar_archive(tar_arch, OTX_CPT_AE_TYPES);
	अगर (tar_info[0] &&
	    dev_supports_eng_type(eng_grps, OTX_CPT_AE_TYPES)) अणु

		engs[0].type = OTX_CPT_AE_TYPES;
		engs[0].count = eng_grps->avail.max_ae_cnt;

		ret = create_engine_group(&pdev->dev, eng_grps, engs, 1,
					  (व्योम **) tar_info, 1, true);
		अगर (ret)
			जाओ release_tar_arch;
	पूर्ण

	prपूर्णांक_dbg_info(&pdev->dev, eng_grps);
release_tar_arch:
	release_tar_archive(tar_arch);
unlock_mutex:
	mutex_unlock(&eng_grps->lock);
	वापस ret;
पूर्ण

व्योम otx_cpt_set_eng_grps_is_rकरोnly(काष्ठा otx_cpt_eng_grps *eng_grps,
				    bool is_rकरोnly)
अणु
	mutex_lock(&eng_grps->lock);

	eng_grps->is_rकरोnly = is_rकरोnly;

	mutex_unlock(&eng_grps->lock);
पूर्ण

व्योम otx_cpt_disable_all_cores(काष्ठा otx_cpt_device *cpt)
अणु
	पूर्णांक grp, समयout = 100;
	u64 reg;

	/* Disengage the cores from groups */
	क्रम (grp = 0; grp < OTX_CPT_MAX_ENGINE_GROUPS; grp++) अणु
		ग_लिखोq(0, cpt->reg_base + OTX_CPT_PF_GX_EN(grp));
		udelay(CSR_DELAY);
	पूर्ण

	reg = पढ़ोq(cpt->reg_base + OTX_CPT_PF_EXEC_BUSY);
	जबतक (reg) अणु
		udelay(CSR_DELAY);
		reg = पढ़ोq(cpt->reg_base + OTX_CPT_PF_EXEC_BUSY);
		अगर (समयout--) अणु
			dev_warn(&cpt->pdev->dev, "Cores still busy\n");
			अवरोध;
		पूर्ण
	पूर्ण

	/* Disable the cores */
	ग_लिखोq(0, cpt->reg_base + OTX_CPT_PF_EXE_CTL);
पूर्ण

व्योम otx_cpt_cleanup_eng_grps(काष्ठा pci_dev *pdev,
			      काष्ठा otx_cpt_eng_grps *eng_grps)
अणु
	काष्ठा otx_cpt_eng_grp_info *grp;
	पूर्णांक i, j;

	mutex_lock(&eng_grps->lock);
	अगर (eng_grps->is_ucode_load_created) अणु
		device_हटाओ_file(&pdev->dev,
				   &eng_grps->ucode_load_attr);
		eng_grps->is_ucode_load_created = false;
	पूर्ण

	/* First delete all mirroring engine groups */
	क्रम (i = 0; i < OTX_CPT_MAX_ENGINE_GROUPS; i++)
		अगर (eng_grps->grp[i].mirror.is_ena)
			delete_engine_group(&pdev->dev, &eng_grps->grp[i]);

	/* Delete reमुख्यing engine groups */
	क्रम (i = 0; i < OTX_CPT_MAX_ENGINE_GROUPS; i++)
		delete_engine_group(&pdev->dev, &eng_grps->grp[i]);

	/* Release memory */
	क्रम (i = 0; i < OTX_CPT_MAX_ENGINE_GROUPS; i++) अणु
		grp = &eng_grps->grp[i];
		क्रम (j = 0; j < OTX_CPT_MAX_ETYPES_PER_GRP; j++) अणु
			kमुक्त(grp->engs[j].bmap);
			grp->engs[j].bmap = शून्य;
		पूर्ण
	पूर्ण

	mutex_unlock(&eng_grps->lock);
पूर्ण

पूर्णांक otx_cpt_init_eng_grps(काष्ठा pci_dev *pdev,
			  काष्ठा otx_cpt_eng_grps *eng_grps, पूर्णांक pf_type)
अणु
	काष्ठा otx_cpt_eng_grp_info *grp;
	पूर्णांक i, j, ret = 0;

	mutex_init(&eng_grps->lock);
	eng_grps->obj = pci_get_drvdata(pdev);
	eng_grps->avail.se_cnt = eng_grps->avail.max_se_cnt;
	eng_grps->avail.ae_cnt = eng_grps->avail.max_ae_cnt;

	eng_grps->engs_num = eng_grps->avail.max_se_cnt +
			     eng_grps->avail.max_ae_cnt;
	अगर (eng_grps->engs_num > OTX_CPT_MAX_ENGINES) अणु
		dev_err(&pdev->dev,
			"Number of engines %d > than max supported %d\n",
			eng_grps->engs_num, OTX_CPT_MAX_ENGINES);
		ret = -EINVAL;
		जाओ err;
	पूर्ण

	क्रम (i = 0; i < OTX_CPT_MAX_ENGINE_GROUPS; i++) अणु
		grp = &eng_grps->grp[i];
		grp->g = eng_grps;
		grp->idx = i;

		snम_लिखो(grp->sysfs_info_name, OTX_CPT_UCODE_NAME_LENGTH,
			 "engine_group%d", i);
		क्रम (j = 0; j < OTX_CPT_MAX_ETYPES_PER_GRP; j++) अणु
			grp->engs[j].bmap =
				kसुस्मृति(BITS_TO_LONGS(eng_grps->engs_num),
					माप(दीर्घ), GFP_KERNEL);
			अगर (!grp->engs[j].bmap) अणु
				ret = -ENOMEM;
				जाओ err;
			पूर्ण
		पूर्ण
	पूर्ण

	चयन (pf_type) अणु
	हाल OTX_CPT_SE:
		/* OcteonTX 83XX SE CPT PF has only SE engines attached */
		eng_grps->eng_types_supported = 1 << OTX_CPT_SE_TYPES;
		अवरोध;

	हाल OTX_CPT_AE:
		/* OcteonTX 83XX AE CPT PF has only AE engines attached */
		eng_grps->eng_types_supported = 1 << OTX_CPT_AE_TYPES;
		अवरोध;

	शेष:
		dev_err(&pdev->dev, "Unknown PF type %d\n", pf_type);
		ret = -EINVAL;
		जाओ err;
	पूर्ण

	eng_grps->ucode_load_attr.show = शून्य;
	eng_grps->ucode_load_attr.store = ucode_load_store;
	eng_grps->ucode_load_attr.attr.name = "ucode_load";
	eng_grps->ucode_load_attr.attr.mode = 0220;
	sysfs_attr_init(&eng_grps->ucode_load_attr.attr);
	ret = device_create_file(&pdev->dev,
				 &eng_grps->ucode_load_attr);
	अगर (ret)
		जाओ err;
	eng_grps->is_ucode_load_created = true;

	prपूर्णांक_dbg_info(&pdev->dev, eng_grps);
	वापस ret;
err:
	otx_cpt_cleanup_eng_grps(pdev, eng_grps);
	वापस ret;
पूर्ण
