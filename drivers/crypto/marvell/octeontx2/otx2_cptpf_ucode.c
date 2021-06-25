<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* Copyright (C) 2020 Marvell. */

#समावेश <linux/प्रकार.स>
#समावेश <linux/firmware.h>
#समावेश "otx2_cptpf_ucode.h"
#समावेश "otx2_cpt_common.h"
#समावेश "otx2_cptpf.h"
#समावेश "otx2_cptlf.h"
#समावेश "otx2_cpt_reqmgr.h"
#समावेश "rvu_reg.h"

#घोषणा CSR_DELAY 30

#घोषणा LOADFVC_RLEN 8
#घोषणा LOADFVC_MAJOR_OP 0x01
#घोषणा LOADFVC_MINOR_OP 0x08

काष्ठा fw_info_t अणु
	काष्ठा list_head ucodes;
पूर्ण;

अटल काष्ठा otx2_cpt_biपंचांगap get_cores_bmap(काष्ठा device *dev,
					काष्ठा otx2_cpt_eng_grp_info *eng_grp)
अणु
	काष्ठा otx2_cpt_biपंचांगap bmap = अणु अणु0पूर्ण पूर्ण;
	bool found = false;
	पूर्णांक i;

	अगर (eng_grp->g->engs_num > OTX2_CPT_MAX_ENGINES) अणु
		dev_err(dev, "unsupported number of engines %d on octeontx2\n",
			eng_grp->g->engs_num);
		वापस bmap;
	पूर्ण

	क्रम (i = 0; i  < OTX2_CPT_MAX_ETYPES_PER_GRP; i++) अणु
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

अटल पूर्णांक is_2nd_ucode_used(काष्ठा otx2_cpt_eng_grp_info *eng_grp)
अणु
	अगर (eng_grp->ucode[1].type)
		वापस true;
	अन्यथा
		वापस false;
पूर्ण

अटल व्योम set_ucode_filename(काष्ठा otx2_cpt_ucode *ucode,
			       स्थिर अक्षर *filename)
अणु
	strlcpy(ucode->filename, filename, OTX2_CPT_NAME_LENGTH);
पूर्ण

अटल अक्षर *get_eng_type_str(पूर्णांक eng_type)
अणु
	अक्षर *str = "unknown";

	चयन (eng_type) अणु
	हाल OTX2_CPT_SE_TYPES:
		str = "SE";
		अवरोध;

	हाल OTX2_CPT_IE_TYPES:
		str = "IE";
		अवरोध;

	हाल OTX2_CPT_AE_TYPES:
		str = "AE";
		अवरोध;
	पूर्ण
	वापस str;
पूर्ण

अटल अक्षर *get_ucode_type_str(पूर्णांक ucode_type)
अणु
	अक्षर *str = "unknown";

	चयन (ucode_type) अणु
	हाल (1 << OTX2_CPT_SE_TYPES):
		str = "SE";
		अवरोध;

	हाल (1 << OTX2_CPT_IE_TYPES):
		str = "IE";
		अवरोध;

	हाल (1 << OTX2_CPT_AE_TYPES):
		str = "AE";
		अवरोध;

	हाल (1 << OTX2_CPT_SE_TYPES | 1 << OTX2_CPT_IE_TYPES):
		str = "SE+IPSEC";
		अवरोध;
	पूर्ण
	वापस str;
पूर्ण

अटल पूर्णांक get_ucode_type(काष्ठा device *dev,
			  काष्ठा otx2_cpt_ucode_hdr *ucode_hdr,
			  पूर्णांक *ucode_type)
अणु
	काष्ठा otx2_cptpf_dev *cptpf = dev_get_drvdata(dev);
	अक्षर ver_str_prefix[OTX2_CPT_UCODE_VER_STR_SZ];
	अक्षर पंचांगp_ver_str[OTX2_CPT_UCODE_VER_STR_SZ];
	काष्ठा pci_dev *pdev = cptpf->pdev;
	पूर्णांक i, val = 0;
	u8 nn;

	strlcpy(पंचांगp_ver_str, ucode_hdr->ver_str, OTX2_CPT_UCODE_VER_STR_SZ);
	क्रम (i = 0; i < म_माप(पंचांगp_ver_str); i++)
		पंचांगp_ver_str[i] = छोटे(पंचांगp_ver_str[i]);

	प्र_लिखो(ver_str_prefix, "ocpt-%02d", pdev->revision);
	अगर (!strnstr(पंचांगp_ver_str, ver_str_prefix, OTX2_CPT_UCODE_VER_STR_SZ))
		वापस -EINVAL;

	nn = ucode_hdr->ver_num.nn;
	अगर (strnstr(पंचांगp_ver_str, "se-", OTX2_CPT_UCODE_VER_STR_SZ) &&
	    (nn == OTX2_CPT_SE_UC_TYPE1 || nn == OTX2_CPT_SE_UC_TYPE2 ||
	     nn == OTX2_CPT_SE_UC_TYPE3))
		val |= 1 << OTX2_CPT_SE_TYPES;
	अगर (strnstr(पंचांगp_ver_str, "ie-", OTX2_CPT_UCODE_VER_STR_SZ) &&
	    (nn == OTX2_CPT_IE_UC_TYPE1 || nn == OTX2_CPT_IE_UC_TYPE2 ||
	     nn == OTX2_CPT_IE_UC_TYPE3))
		val |= 1 << OTX2_CPT_IE_TYPES;
	अगर (strnstr(पंचांगp_ver_str, "ae", OTX2_CPT_UCODE_VER_STR_SZ) &&
	    nn == OTX2_CPT_AE_UC_TYPE)
		val |= 1 << OTX2_CPT_AE_TYPES;

	*ucode_type = val;

	अगर (!val)
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक __ग_लिखो_ucode_base(काष्ठा otx2_cptpf_dev *cptpf, पूर्णांक eng,
			      dma_addr_t dma_addr, पूर्णांक blkaddr)
अणु
	वापस otx2_cpt_ग_लिखो_af_reg(&cptpf->afpf_mbox, cptpf->pdev,
				     CPT_AF_EXEX_UCODE_BASE(eng),
				     (u64)dma_addr, blkaddr);
पूर्ण

अटल पूर्णांक cptx_set_ucode_base(काष्ठा otx2_cpt_eng_grp_info *eng_grp,
			       काष्ठा otx2_cptpf_dev *cptpf, पूर्णांक blkaddr)
अणु
	काष्ठा otx2_cpt_engs_rsvd *engs;
	dma_addr_t dma_addr;
	पूर्णांक i, bit, ret;

	/* Set PF number क्रम microcode fetches */
	ret = otx2_cpt_ग_लिखो_af_reg(&cptpf->afpf_mbox, cptpf->pdev,
				    CPT_AF_PF_FUNC,
				    cptpf->pf_id << RVU_PFVF_PF_SHIFT, blkaddr);
	अगर (ret)
		वापस ret;

	क्रम (i = 0; i < OTX2_CPT_MAX_ETYPES_PER_GRP; i++) अणु
		engs = &eng_grp->engs[i];
		अगर (!engs->type)
			जारी;

		dma_addr = engs->ucode->dma;

		/*
		 * Set UCODE_BASE only क्रम the cores which are not used,
		 * other cores should have alपढ़ोy valid UCODE_BASE set
		 */
		क्रम_each_set_bit(bit, engs->bmap, eng_grp->g->engs_num)
			अगर (!eng_grp->g->eng_ref_cnt[bit]) अणु
				ret = __ग_लिखो_ucode_base(cptpf, bit, dma_addr,
							 blkaddr);
				अगर (ret)
					वापस ret;
			पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक cpt_set_ucode_base(काष्ठा otx2_cpt_eng_grp_info *eng_grp, व्योम *obj)
अणु
	काष्ठा otx2_cptpf_dev *cptpf = obj;
	पूर्णांक ret;

	अगर (cptpf->has_cpt1) अणु
		ret = cptx_set_ucode_base(eng_grp, cptpf, BLKADDR_CPT1);
		अगर (ret)
			वापस ret;
	पूर्ण
	वापस cptx_set_ucode_base(eng_grp, cptpf, BLKADDR_CPT0);
पूर्ण

अटल पूर्णांक cptx_detach_and_disable_cores(काष्ठा otx2_cpt_eng_grp_info *eng_grp,
					 काष्ठा otx2_cptpf_dev *cptpf,
					 काष्ठा otx2_cpt_biपंचांगap bmap,
					 पूर्णांक blkaddr)
अणु
	पूर्णांक i, समयout = 10;
	पूर्णांक busy, ret;
	u64 reg = 0;

	/* Detach the cores from group */
	क्रम_each_set_bit(i, bmap.bits, bmap.size) अणु
		ret = otx2_cpt_पढ़ो_af_reg(&cptpf->afpf_mbox, cptpf->pdev,
					   CPT_AF_EXEX_CTL2(i), &reg, blkaddr);
		अगर (ret)
			वापस ret;

		अगर (reg & (1ull << eng_grp->idx)) अणु
			eng_grp->g->eng_ref_cnt[i]--;
			reg &= ~(1ull << eng_grp->idx);

			ret = otx2_cpt_ग_लिखो_af_reg(&cptpf->afpf_mbox,
						    cptpf->pdev,
						    CPT_AF_EXEX_CTL2(i), reg,
						    blkaddr);
			अगर (ret)
				वापस ret;
		पूर्ण
	पूर्ण

	/* Wait क्रम cores to become idle */
	करो अणु
		busy = 0;
		usleep_range(10000, 20000);
		अगर (समयout-- < 0)
			वापस -EBUSY;

		क्रम_each_set_bit(i, bmap.bits, bmap.size) अणु
			ret = otx2_cpt_पढ़ो_af_reg(&cptpf->afpf_mbox,
						   cptpf->pdev,
						   CPT_AF_EXEX_STS(i), &reg,
						   blkaddr);
			अगर (ret)
				वापस ret;

			अगर (reg & 0x1) अणु
				busy = 1;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण जबतक (busy);

	/* Disable the cores only अगर they are not used anymore */
	क्रम_each_set_bit(i, bmap.bits, bmap.size) अणु
		अगर (!eng_grp->g->eng_ref_cnt[i]) अणु
			ret = otx2_cpt_ग_लिखो_af_reg(&cptpf->afpf_mbox,
						    cptpf->pdev,
						    CPT_AF_EXEX_CTL(i), 0x0,
						    blkaddr);
			अगर (ret)
				वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक cpt_detach_and_disable_cores(काष्ठा otx2_cpt_eng_grp_info *eng_grp,
					व्योम *obj)
अणु
	काष्ठा otx2_cptpf_dev *cptpf = obj;
	काष्ठा otx2_cpt_biपंचांगap bmap;
	पूर्णांक ret;

	bmap = get_cores_bmap(&cptpf->pdev->dev, eng_grp);
	अगर (!bmap.size)
		वापस -EINVAL;

	अगर (cptpf->has_cpt1) अणु
		ret = cptx_detach_and_disable_cores(eng_grp, cptpf, bmap,
						    BLKADDR_CPT1);
		अगर (ret)
			वापस ret;
	पूर्ण
	वापस cptx_detach_and_disable_cores(eng_grp, cptpf, bmap,
					     BLKADDR_CPT0);
पूर्ण

अटल पूर्णांक cptx_attach_and_enable_cores(काष्ठा otx2_cpt_eng_grp_info *eng_grp,
					काष्ठा otx2_cptpf_dev *cptpf,
					काष्ठा otx2_cpt_biपंचांगap bmap,
					पूर्णांक blkaddr)
अणु
	u64 reg = 0;
	पूर्णांक i, ret;

	/* Attach the cores to the group */
	क्रम_each_set_bit(i, bmap.bits, bmap.size) अणु
		ret = otx2_cpt_पढ़ो_af_reg(&cptpf->afpf_mbox, cptpf->pdev,
					   CPT_AF_EXEX_CTL2(i), &reg, blkaddr);
		अगर (ret)
			वापस ret;

		अगर (!(reg & (1ull << eng_grp->idx))) अणु
			eng_grp->g->eng_ref_cnt[i]++;
			reg |= 1ull << eng_grp->idx;

			ret = otx2_cpt_ग_लिखो_af_reg(&cptpf->afpf_mbox,
						    cptpf->pdev,
						    CPT_AF_EXEX_CTL2(i), reg,
						    blkaddr);
			अगर (ret)
				वापस ret;
		पूर्ण
	पूर्ण

	/* Enable the cores */
	क्रम_each_set_bit(i, bmap.bits, bmap.size) अणु
		ret = otx2_cpt_add_ग_लिखो_af_reg(&cptpf->afpf_mbox, cptpf->pdev,
						CPT_AF_EXEX_CTL(i), 0x1,
						blkaddr);
		अगर (ret)
			वापस ret;
	पूर्ण
	वापस otx2_cpt_send_af_reg_requests(&cptpf->afpf_mbox, cptpf->pdev);
पूर्ण

अटल पूर्णांक cpt_attach_and_enable_cores(काष्ठा otx2_cpt_eng_grp_info *eng_grp,
				       व्योम *obj)
अणु
	काष्ठा otx2_cptpf_dev *cptpf = obj;
	काष्ठा otx2_cpt_biपंचांगap bmap;
	पूर्णांक ret;

	bmap = get_cores_bmap(&cptpf->pdev->dev, eng_grp);
	अगर (!bmap.size)
		वापस -EINVAL;

	अगर (cptpf->has_cpt1) अणु
		ret = cptx_attach_and_enable_cores(eng_grp, cptpf, bmap,
						   BLKADDR_CPT1);
		अगर (ret)
			वापस ret;
	पूर्ण
	वापस cptx_attach_and_enable_cores(eng_grp, cptpf, bmap, BLKADDR_CPT0);
पूर्ण

अटल पूर्णांक load_fw(काष्ठा device *dev, काष्ठा fw_info_t *fw_info,
		   अक्षर *filename)
अणु
	काष्ठा otx2_cpt_ucode_hdr *ucode_hdr;
	काष्ठा otx2_cpt_uc_info_t *uc_info;
	पूर्णांक ucode_type, ucode_size;
	पूर्णांक ret;

	uc_info = kzalloc(माप(*uc_info), GFP_KERNEL);
	अगर (!uc_info)
		वापस -ENOMEM;

	ret = request_firmware(&uc_info->fw, filename, dev);
	अगर (ret)
		जाओ मुक्त_uc_info;

	ucode_hdr = (काष्ठा otx2_cpt_ucode_hdr *)uc_info->fw->data;
	ret = get_ucode_type(dev, ucode_hdr, &ucode_type);
	अगर (ret)
		जाओ release_fw;

	ucode_size = ntohl(ucode_hdr->code_length) * 2;
	अगर (!ucode_size) अणु
		dev_err(dev, "Ucode %s invalid size\n", filename);
		ret = -EINVAL;
		जाओ release_fw;
	पूर्ण

	set_ucode_filename(&uc_info->ucode, filename);
	स_नकल(uc_info->ucode.ver_str, ucode_hdr->ver_str,
	       OTX2_CPT_UCODE_VER_STR_SZ);
	uc_info->ucode.ver_num = ucode_hdr->ver_num;
	uc_info->ucode.type = ucode_type;
	uc_info->ucode.size = ucode_size;
	list_add_tail(&uc_info->list, &fw_info->ucodes);

	वापस 0;

release_fw:
	release_firmware(uc_info->fw);
मुक्त_uc_info:
	kमुक्त(uc_info);
	वापस ret;
पूर्ण

अटल व्योम cpt_ucode_release_fw(काष्ठा fw_info_t *fw_info)
अणु
	काष्ठा otx2_cpt_uc_info_t *curr, *temp;

	अगर (!fw_info)
		वापस;

	list_क्रम_each_entry_safe(curr, temp, &fw_info->ucodes, list) अणु
		list_del(&curr->list);
		release_firmware(curr->fw);
		kमुक्त(curr);
	पूर्ण
पूर्ण

अटल काष्ठा otx2_cpt_uc_info_t *get_ucode(काष्ठा fw_info_t *fw_info,
					    पूर्णांक ucode_type)
अणु
	काष्ठा otx2_cpt_uc_info_t *curr;

	list_क्रम_each_entry(curr, &fw_info->ucodes, list) अणु
		अगर (!is_eng_type(curr->ucode.type, ucode_type))
			जारी;

		वापस curr;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल व्योम prपूर्णांक_uc_info(काष्ठा fw_info_t *fw_info)
अणु
	काष्ठा otx2_cpt_uc_info_t *curr;

	list_क्रम_each_entry(curr, &fw_info->ucodes, list) अणु
		pr_debug("Ucode filename %s\n", curr->ucode.filename);
		pr_debug("Ucode version string %s\n", curr->ucode.ver_str);
		pr_debug("Ucode version %d.%d.%d.%d\n",
			 curr->ucode.ver_num.nn, curr->ucode.ver_num.xx,
			 curr->ucode.ver_num.yy, curr->ucode.ver_num.zz);
		pr_debug("Ucode type (%d) %s\n", curr->ucode.type,
			 get_ucode_type_str(curr->ucode.type));
		pr_debug("Ucode size %d\n", curr->ucode.size);
		pr_debug("Ucode ptr %p\n", curr->fw->data);
	पूर्ण
पूर्ण

अटल पूर्णांक cpt_ucode_load_fw(काष्ठा pci_dev *pdev, काष्ठा fw_info_t *fw_info)
अणु
	अक्षर filename[OTX2_CPT_NAME_LENGTH];
	अक्षर eng_type[8] = अणु0पूर्ण;
	पूर्णांक ret, e, i;

	INIT_LIST_HEAD(&fw_info->ucodes);

	क्रम (e = 1; e < OTX2_CPT_MAX_ENG_TYPES; e++) अणु
		म_नकल(eng_type, get_eng_type_str(e));
		क्रम (i = 0; i < म_माप(eng_type); i++)
			eng_type[i] = छोटे(eng_type[i]);

		snम_लिखो(filename, माप(filename), "mrvl/cpt%02d/%s.out",
			 pdev->revision, eng_type);
		/* Request firmware क्रम each engine type */
		ret = load_fw(&pdev->dev, fw_info, filename);
		अगर (ret)
			जाओ release_fw;
	पूर्ण
	prपूर्णांक_uc_info(fw_info);
	वापस 0;

release_fw:
	cpt_ucode_release_fw(fw_info);
	वापस ret;
पूर्ण

अटल काष्ठा otx2_cpt_engs_rsvd *find_engines_by_type(
					काष्ठा otx2_cpt_eng_grp_info *eng_grp,
					पूर्णांक eng_type)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < OTX2_CPT_MAX_ETYPES_PER_GRP; i++) अणु
		अगर (!eng_grp->engs[i].type)
			जारी;

		अगर (eng_grp->engs[i].type == eng_type)
			वापस &eng_grp->engs[i];
	पूर्ण
	वापस शून्य;
पूर्ण

अटल पूर्णांक eng_grp_has_eng_type(काष्ठा otx2_cpt_eng_grp_info *eng_grp,
				पूर्णांक eng_type)
अणु
	काष्ठा otx2_cpt_engs_rsvd *engs;

	engs = find_engines_by_type(eng_grp, eng_type);

	वापस (engs != शून्य ? 1 : 0);
पूर्ण

अटल पूर्णांक update_engines_avail_count(काष्ठा device *dev,
				      काष्ठा otx2_cpt_engs_available *avail,
				      काष्ठा otx2_cpt_engs_rsvd *engs, पूर्णांक val)
अणु
	चयन (engs->type) अणु
	हाल OTX2_CPT_SE_TYPES:
		avail->se_cnt += val;
		अवरोध;

	हाल OTX2_CPT_IE_TYPES:
		avail->ie_cnt += val;
		अवरोध;

	हाल OTX2_CPT_AE_TYPES:
		avail->ae_cnt += val;
		अवरोध;

	शेष:
		dev_err(dev, "Invalid engine type %d\n", engs->type);
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक update_engines_offset(काष्ठा device *dev,
				 काष्ठा otx2_cpt_engs_available *avail,
				 काष्ठा otx2_cpt_engs_rsvd *engs)
अणु
	चयन (engs->type) अणु
	हाल OTX2_CPT_SE_TYPES:
		engs->offset = 0;
		अवरोध;

	हाल OTX2_CPT_IE_TYPES:
		engs->offset = avail->max_se_cnt;
		अवरोध;

	हाल OTX2_CPT_AE_TYPES:
		engs->offset = avail->max_se_cnt + avail->max_ie_cnt;
		अवरोध;

	शेष:
		dev_err(dev, "Invalid engine type %d\n", engs->type);
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक release_engines(काष्ठा device *dev,
			   काष्ठा otx2_cpt_eng_grp_info *grp)
अणु
	पूर्णांक i, ret = 0;

	क्रम (i = 0; i < OTX2_CPT_MAX_ETYPES_PER_GRP; i++) अणु
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
			      काष्ठा otx2_cpt_eng_grp_info *grp,
			      काष्ठा otx2_cpt_engines *req_engs)
अणु
	काष्ठा otx2_cpt_engs_rsvd *engs = शून्य;
	पूर्णांक i, ret;

	क्रम (i = 0; i < OTX2_CPT_MAX_ETYPES_PER_GRP; i++) अणु
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
				      काष्ठा otx2_cpt_eng_grp_info *grp,
				      काष्ठा otx2_cpt_engines *req_eng)
अणु
	पूर्णांक avail_cnt = 0;

	चयन (req_eng->type) अणु
	हाल OTX2_CPT_SE_TYPES:
		avail_cnt = grp->g->avail.se_cnt;
		अवरोध;

	हाल OTX2_CPT_IE_TYPES:
		avail_cnt = grp->g->avail.ie_cnt;
		अवरोध;

	हाल OTX2_CPT_AE_TYPES:
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

अटल पूर्णांक reserve_engines(काष्ठा device *dev,
			   काष्ठा otx2_cpt_eng_grp_info *grp,
			   काष्ठा otx2_cpt_engines *req_engs, पूर्णांक ucodes_cnt)
अणु
	पूर्णांक i, ret = 0;

	/* Validate अगर a number of requested engines are available */
	क्रम (i = 0; i < ucodes_cnt; i++) अणु
		ret = check_engines_availability(dev, grp, &req_engs[i]);
		अगर (ret)
			वापस ret;
	पूर्ण

	/* Reserve requested engines क्रम this engine group */
	क्रम (i = 0; i < ucodes_cnt; i++) अणु
		ret = करो_reserve_engines(dev, grp, &req_engs[i]);
		अगर (ret)
			वापस ret;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम ucode_unload(काष्ठा device *dev, काष्ठा otx2_cpt_ucode *ucode)
अणु
	अगर (ucode->va) अणु
		dma_मुक्त_coherent(dev, ucode->size, ucode->va, ucode->dma);
		ucode->va = शून्य;
		ucode->dma = 0;
		ucode->size = 0;
	पूर्ण

	स_रखो(&ucode->ver_str, 0, OTX2_CPT_UCODE_VER_STR_SZ);
	स_रखो(&ucode->ver_num, 0, माप(काष्ठा otx2_cpt_ucode_ver_num));
	set_ucode_filename(ucode, "");
	ucode->type = 0;
पूर्ण

अटल पूर्णांक copy_ucode_to_dma_mem(काष्ठा device *dev,
				 काष्ठा otx2_cpt_ucode *ucode,
				 स्थिर u8 *ucode_data)
अणु
	u32 i;

	/*  Allocate DMAable space */
	ucode->va = dma_alloc_coherent(dev, ucode->size, &ucode->dma,
				       GFP_KERNEL);
	अगर (!ucode->va)
		वापस -ENOMEM;

	स_नकल(ucode->va, ucode_data + माप(काष्ठा otx2_cpt_ucode_hdr),
	       ucode->size);

	/* Byte swap 64-bit */
	क्रम (i = 0; i < (ucode->size / 8); i++)
		cpu_to_be64s(&((u64 *)ucode->va)[i]);
	/*  Ucode needs 16-bit swap */
	क्रम (i = 0; i < (ucode->size / 2); i++)
		cpu_to_be16s(&((u16 *)ucode->va)[i]);
	वापस 0;
पूर्ण

अटल पूर्णांक enable_eng_grp(काष्ठा otx2_cpt_eng_grp_info *eng_grp,
			  व्योम *obj)
अणु
	पूर्णांक ret;

	/* Poपूर्णांक microcode to each core of the group */
	ret = cpt_set_ucode_base(eng_grp, obj);
	अगर (ret)
		वापस ret;

	/* Attach the cores to the group and enable them */
	ret = cpt_attach_and_enable_cores(eng_grp, obj);

	वापस ret;
पूर्ण

अटल पूर्णांक disable_eng_grp(काष्ठा device *dev,
			   काष्ठा otx2_cpt_eng_grp_info *eng_grp,
			   व्योम *obj)
अणु
	पूर्णांक i, ret;

	/* Disable all engines used by this group */
	ret = cpt_detach_and_disable_cores(eng_grp, obj);
	अगर (ret)
		वापस ret;

	/* Unload ucode used by this engine group */
	ucode_unload(dev, &eng_grp->ucode[0]);
	ucode_unload(dev, &eng_grp->ucode[1]);

	क्रम (i = 0; i < OTX2_CPT_MAX_ETYPES_PER_GRP; i++) अणु
		अगर (!eng_grp->engs[i].type)
			जारी;

		eng_grp->engs[i].ucode = &eng_grp->ucode[0];
	पूर्ण

	/* Clear UCODE_BASE रेजिस्टर क्रम each engine used by this group */
	ret = cpt_set_ucode_base(eng_grp, obj);

	वापस ret;
पूर्ण

अटल व्योम setup_eng_grp_mirroring(काष्ठा otx2_cpt_eng_grp_info *dst_grp,
				    काष्ठा otx2_cpt_eng_grp_info *src_grp)
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

अटल व्योम हटाओ_eng_grp_mirroring(काष्ठा otx2_cpt_eng_grp_info *dst_grp)
अणु
	काष्ठा otx2_cpt_eng_grp_info *src_grp;

	अगर (!dst_grp->mirror.is_ena)
		वापस;

	src_grp = &dst_grp->g->grp[dst_grp->mirror.idx];

	src_grp->mirror.ref_count--;
	dst_grp->mirror.is_ena = false;
	dst_grp->mirror.idx = 0;
	dst_grp->mirror.ref_count = 0;
पूर्ण

अटल व्योम update_requested_engs(काष्ठा otx2_cpt_eng_grp_info *mirror_eng_grp,
				  काष्ठा otx2_cpt_engines *engs, पूर्णांक engs_cnt)
अणु
	काष्ठा otx2_cpt_engs_rsvd *mirrored_engs;
	पूर्णांक i;

	क्रम (i = 0; i < engs_cnt; i++) अणु
		mirrored_engs = find_engines_by_type(mirror_eng_grp,
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

अटल काष्ठा otx2_cpt_eng_grp_info *find_mirrored_eng_grp(
					काष्ठा otx2_cpt_eng_grp_info *grp)
अणु
	काष्ठा otx2_cpt_eng_grps *eng_grps = grp->g;
	पूर्णांक i;

	क्रम (i = 0; i < OTX2_CPT_MAX_ENGINE_GROUPS; i++) अणु
		अगर (!eng_grps->grp[i].is_enabled)
			जारी;
		अगर (eng_grps->grp[i].ucode[0].type &&
		    eng_grps->grp[i].ucode[1].type)
			जारी;
		अगर (grp->idx == i)
			जारी;
		अगर (!strnहालcmp(eng_grps->grp[i].ucode[0].ver_str,
				 grp->ucode[0].ver_str,
				 OTX2_CPT_UCODE_VER_STR_SZ))
			वापस &eng_grps->grp[i];
	पूर्ण

	वापस शून्य;
पूर्ण

अटल काष्ठा otx2_cpt_eng_grp_info *find_unused_eng_grp(
					काष्ठा otx2_cpt_eng_grps *eng_grps)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < OTX2_CPT_MAX_ENGINE_GROUPS; i++) अणु
		अगर (!eng_grps->grp[i].is_enabled)
			वापस &eng_grps->grp[i];
	पूर्ण
	वापस शून्य;
पूर्ण

अटल पूर्णांक eng_grp_update_masks(काष्ठा device *dev,
				काष्ठा otx2_cpt_eng_grp_info *eng_grp)
अणु
	काष्ठा otx2_cpt_engs_rsvd *engs, *mirrored_engs;
	काष्ठा otx2_cpt_biपंचांगap पंचांगp_bmap = अणु अणु0पूर्ण पूर्ण;
	पूर्णांक i, j, cnt, max_cnt;
	पूर्णांक bit;

	क्रम (i = 0; i < OTX2_CPT_MAX_ETYPES_PER_GRP; i++) अणु
		engs = &eng_grp->engs[i];
		अगर (!engs->type)
			जारी;
		अगर (engs->count <= 0)
			जारी;

		चयन (engs->type) अणु
		हाल OTX2_CPT_SE_TYPES:
			max_cnt = eng_grp->g->avail.max_se_cnt;
			अवरोध;

		हाल OTX2_CPT_IE_TYPES:
			max_cnt = eng_grp->g->avail.max_ie_cnt;
			अवरोध;

		हाल OTX2_CPT_AE_TYPES:
			max_cnt = eng_grp->g->avail.max_ae_cnt;
			अवरोध;

		शेष:
			dev_err(dev, "Invalid engine type %d\n", engs->type);
			वापस -EINVAL;
		पूर्ण

		cnt = engs->count;
		WARN_ON(engs->offset + max_cnt > OTX2_CPT_MAX_ENGINES);
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

	क्रम (i = 0; i < OTX2_CPT_MAX_ETYPES_PER_GRP; i++) अणु
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
			       काष्ठा otx2_cpt_eng_grp_info *eng_grp)
अणु
	पूर्णांक ret;

	अगर (!eng_grp->is_enabled)
		वापस 0;

	अगर (eng_grp->mirror.ref_count)
		वापस -EINVAL;

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

	eng_grp->is_enabled = false;

	वापस 0;
पूर्ण

अटल व्योम update_ucode_ptrs(काष्ठा otx2_cpt_eng_grp_info *eng_grp)
अणु
	काष्ठा otx2_cpt_ucode *ucode;

	अगर (eng_grp->mirror.is_ena)
		ucode = &eng_grp->g->grp[eng_grp->mirror.idx].ucode[0];
	अन्यथा
		ucode = &eng_grp->ucode[0];
	WARN_ON(!eng_grp->engs[0].type);
	eng_grp->engs[0].ucode = ucode;

	अगर (eng_grp->engs[1].type) अणु
		अगर (is_2nd_ucode_used(eng_grp))
			eng_grp->engs[1].ucode = &eng_grp->ucode[1];
		अन्यथा
			eng_grp->engs[1].ucode = ucode;
	पूर्ण
पूर्ण

अटल पूर्णांक create_engine_group(काष्ठा device *dev,
			       काष्ठा otx2_cpt_eng_grps *eng_grps,
			       काष्ठा otx2_cpt_engines *engs, पूर्णांक ucodes_cnt,
			       व्योम *ucode_data[], पूर्णांक is_prपूर्णांक)
अणु
	काष्ठा otx2_cpt_eng_grp_info *mirrored_eng_grp;
	काष्ठा otx2_cpt_eng_grp_info *eng_grp;
	काष्ठा otx2_cpt_uc_info_t *uc_info;
	पूर्णांक i, ret = 0;

	/* Find engine group which is not used */
	eng_grp = find_unused_eng_grp(eng_grps);
	अगर (!eng_grp) अणु
		dev_err(dev, "Error all engine groups are being used\n");
		वापस -ENOSPC;
	पूर्ण
	/* Load ucode */
	क्रम (i = 0; i < ucodes_cnt; i++) अणु
		uc_info = (काष्ठा otx2_cpt_uc_info_t *) ucode_data[i];
		eng_grp->ucode[i] = uc_info->ucode;
		ret = copy_ucode_to_dma_mem(dev, &eng_grp->ucode[i],
					    uc_info->fw->data);
		अगर (ret)
			जाओ unload_ucode;
	पूर्ण

	/* Check अगर this group mirrors another existing engine group */
	mirrored_eng_grp = find_mirrored_eng_grp(eng_grp);
	अगर (mirrored_eng_grp) अणु
		/* Setup mirroring */
		setup_eng_grp_mirroring(eng_grp, mirrored_eng_grp);

		/*
		 * Update count of requested engines because some
		 * of them might be shared with mirrored group
		 */
		update_requested_engs(mirrored_eng_grp, engs, ucodes_cnt);
	पूर्ण
	ret = reserve_engines(dev, eng_grp, engs, ucodes_cnt);
	अगर (ret)
		जाओ unload_ucode;

	/* Update ucode poपूर्णांकers used by engines */
	update_ucode_ptrs(eng_grp);

	/* Update engine masks used by this group */
	ret = eng_grp_update_masks(dev, eng_grp);
	अगर (ret)
		जाओ release_engs;

	/* Enable engine group */
	ret = enable_eng_grp(eng_grp, eng_grps->obj);
	अगर (ret)
		जाओ release_engs;

	/*
	 * If this engine group mirrors another engine group
	 * then we need to unload ucode as we will use ucode
	 * from mirrored engine group
	 */
	अगर (eng_grp->mirror.is_ena)
		ucode_unload(dev, &eng_grp->ucode[0]);

	eng_grp->is_enabled = true;

	अगर (!is_prपूर्णांक)
		वापस 0;

	अगर (mirrored_eng_grp)
		dev_info(dev,
			 "Engine_group%d: reuse microcode %s from group %d\n",
			 eng_grp->idx, mirrored_eng_grp->ucode[0].ver_str,
			 mirrored_eng_grp->idx);
	अन्यथा
		dev_info(dev, "Engine_group%d: microcode loaded %s\n",
			 eng_grp->idx, eng_grp->ucode[0].ver_str);
	अगर (is_2nd_ucode_used(eng_grp))
		dev_info(dev, "Engine_group%d: microcode loaded %s\n",
			 eng_grp->idx, eng_grp->ucode[1].ver_str);

	वापस 0;

release_engs:
	release_engines(dev, eng_grp);
unload_ucode:
	ucode_unload(dev, &eng_grp->ucode[0]);
	ucode_unload(dev, &eng_grp->ucode[1]);
	वापस ret;
पूर्ण

अटल व्योम delete_engine_grps(काष्ठा pci_dev *pdev,
			       काष्ठा otx2_cpt_eng_grps *eng_grps)
अणु
	पूर्णांक i;

	/* First delete all mirroring engine groups */
	क्रम (i = 0; i < OTX2_CPT_MAX_ENGINE_GROUPS; i++)
		अगर (eng_grps->grp[i].mirror.is_ena)
			delete_engine_group(&pdev->dev, &eng_grps->grp[i]);

	/* Delete reमुख्यing engine groups */
	क्रम (i = 0; i < OTX2_CPT_MAX_ENGINE_GROUPS; i++)
		delete_engine_group(&pdev->dev, &eng_grps->grp[i]);
पूर्ण

पूर्णांक otx2_cpt_get_eng_grp(काष्ठा otx2_cpt_eng_grps *eng_grps, पूर्णांक eng_type)
अणु

	पूर्णांक eng_grp_num = OTX2_CPT_INVALID_CRYPTO_ENG_GRP;
	काष्ठा otx2_cpt_eng_grp_info *grp;
	पूर्णांक i;

	क्रम (i = 0; i < OTX2_CPT_MAX_ENGINE_GROUPS; i++) अणु
		grp = &eng_grps->grp[i];
		अगर (!grp->is_enabled)
			जारी;

		अगर (eng_type == OTX2_CPT_SE_TYPES) अणु
			अगर (eng_grp_has_eng_type(grp, eng_type) &&
			    !eng_grp_has_eng_type(grp, OTX2_CPT_IE_TYPES)) अणु
				eng_grp_num = i;
				अवरोध;
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (eng_grp_has_eng_type(grp, eng_type)) अणु
				eng_grp_num = i;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण
	वापस eng_grp_num;
पूर्ण

पूर्णांक otx2_cpt_create_eng_grps(काष्ठा pci_dev *pdev,
			     काष्ठा otx2_cpt_eng_grps *eng_grps)
अणु
	काष्ठा otx2_cpt_uc_info_t *uc_info[OTX2_CPT_MAX_ETYPES_PER_GRP] = अणु  पूर्ण;
	काष्ठा otx2_cpt_engines engs[OTX2_CPT_MAX_ETYPES_PER_GRP] = अणु अणु0पूर्ण पूर्ण;
	काष्ठा fw_info_t fw_info;
	पूर्णांक ret;

	/*
	 * We करोn't create engine groups अगर it was alपढ़ोy
	 * made (when user enabled VFs क्रम the first समय)
	 */
	अगर (eng_grps->is_grps_created)
		वापस 0;

	ret = cpt_ucode_load_fw(pdev, &fw_info);
	अगर (ret)
		वापस ret;

	/*
	 * Create engine group with SE engines क्रम kernel
	 * crypto functionality (symmetric crypto)
	 */
	uc_info[0] = get_ucode(&fw_info, OTX2_CPT_SE_TYPES);
	अगर (uc_info[0] == शून्य) अणु
		dev_err(&pdev->dev, "Unable to find firmware for SE\n");
		ret = -EINVAL;
		जाओ release_fw;
	पूर्ण
	engs[0].type = OTX2_CPT_SE_TYPES;
	engs[0].count = eng_grps->avail.max_se_cnt;

	ret = create_engine_group(&pdev->dev, eng_grps, engs, 1,
				  (व्योम **) uc_info, 1);
	अगर (ret)
		जाओ release_fw;

	/*
	 * Create engine group with SE+IE engines क्रम IPSec.
	 * All SE engines will be shared with engine group 0.
	 */
	uc_info[0] = get_ucode(&fw_info, OTX2_CPT_SE_TYPES);
	uc_info[1] = get_ucode(&fw_info, OTX2_CPT_IE_TYPES);

	अगर (uc_info[1] == शून्य) अणु
		dev_err(&pdev->dev, "Unable to find firmware for IE");
		ret = -EINVAL;
		जाओ delete_eng_grp;
	पूर्ण
	engs[0].type = OTX2_CPT_SE_TYPES;
	engs[0].count = eng_grps->avail.max_se_cnt;
	engs[1].type = OTX2_CPT_IE_TYPES;
	engs[1].count = eng_grps->avail.max_ie_cnt;

	ret = create_engine_group(&pdev->dev, eng_grps, engs, 2,
				  (व्योम **) uc_info, 1);
	अगर (ret)
		जाओ delete_eng_grp;

	/*
	 * Create engine group with AE engines क्रम asymmetric
	 * crypto functionality.
	 */
	uc_info[0] = get_ucode(&fw_info, OTX2_CPT_AE_TYPES);
	अगर (uc_info[0] == शून्य) अणु
		dev_err(&pdev->dev, "Unable to find firmware for AE");
		ret = -EINVAL;
		जाओ delete_eng_grp;
	पूर्ण
	engs[0].type = OTX2_CPT_AE_TYPES;
	engs[0].count = eng_grps->avail.max_ae_cnt;

	ret = create_engine_group(&pdev->dev, eng_grps, engs, 1,
				  (व्योम **) uc_info, 1);
	अगर (ret)
		जाओ delete_eng_grp;

	eng_grps->is_grps_created = true;

	cpt_ucode_release_fw(&fw_info);
	वापस 0;

delete_eng_grp:
	delete_engine_grps(pdev, eng_grps);
release_fw:
	cpt_ucode_release_fw(&fw_info);
	वापस ret;
पूर्ण

अटल पूर्णांक cptx_disable_all_cores(काष्ठा otx2_cptpf_dev *cptpf, पूर्णांक total_cores,
				  पूर्णांक blkaddr)
अणु
	पूर्णांक समयout = 10, ret;
	पूर्णांक i, busy;
	u64 reg;

	/* Disengage the cores from groups */
	क्रम (i = 0; i < total_cores; i++) अणु
		ret = otx2_cpt_add_ग_लिखो_af_reg(&cptpf->afpf_mbox, cptpf->pdev,
						CPT_AF_EXEX_CTL2(i), 0x0,
						blkaddr);
		अगर (ret)
			वापस ret;

		cptpf->eng_grps.eng_ref_cnt[i] = 0;
	पूर्ण
	ret = otx2_cpt_send_af_reg_requests(&cptpf->afpf_mbox, cptpf->pdev);
	अगर (ret)
		वापस ret;

	/* Wait क्रम cores to become idle */
	करो अणु
		busy = 0;
		usleep_range(10000, 20000);
		अगर (समयout-- < 0)
			वापस -EBUSY;

		क्रम (i = 0; i < total_cores; i++) अणु
			ret = otx2_cpt_पढ़ो_af_reg(&cptpf->afpf_mbox,
						   cptpf->pdev,
						   CPT_AF_EXEX_STS(i), &reg,
						   blkaddr);
			अगर (ret)
				वापस ret;

			अगर (reg & 0x1) अणु
				busy = 1;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण जबतक (busy);

	/* Disable the cores */
	क्रम (i = 0; i < total_cores; i++) अणु
		ret = otx2_cpt_add_ग_लिखो_af_reg(&cptpf->afpf_mbox, cptpf->pdev,
						CPT_AF_EXEX_CTL(i), 0x0,
						blkaddr);
		अगर (ret)
			वापस ret;
	पूर्ण
	वापस otx2_cpt_send_af_reg_requests(&cptpf->afpf_mbox, cptpf->pdev);
पूर्ण

पूर्णांक otx2_cpt_disable_all_cores(काष्ठा otx2_cptpf_dev *cptpf)
अणु
	पूर्णांक total_cores, ret;

	total_cores = cptpf->eng_grps.avail.max_se_cnt +
		      cptpf->eng_grps.avail.max_ie_cnt +
		      cptpf->eng_grps.avail.max_ae_cnt;

	अगर (cptpf->has_cpt1) अणु
		ret = cptx_disable_all_cores(cptpf, total_cores, BLKADDR_CPT1);
		अगर (ret)
			वापस ret;
	पूर्ण
	वापस cptx_disable_all_cores(cptpf, total_cores, BLKADDR_CPT0);
पूर्ण

व्योम otx2_cpt_cleanup_eng_grps(काष्ठा pci_dev *pdev,
			       काष्ठा otx2_cpt_eng_grps *eng_grps)
अणु
	काष्ठा otx2_cpt_eng_grp_info *grp;
	पूर्णांक i, j;

	delete_engine_grps(pdev, eng_grps);
	/* Release memory */
	क्रम (i = 0; i < OTX2_CPT_MAX_ENGINE_GROUPS; i++) अणु
		grp = &eng_grps->grp[i];
		क्रम (j = 0; j < OTX2_CPT_MAX_ETYPES_PER_GRP; j++) अणु
			kमुक्त(grp->engs[j].bmap);
			grp->engs[j].bmap = शून्य;
		पूर्ण
	पूर्ण
पूर्ण

पूर्णांक otx2_cpt_init_eng_grps(काष्ठा pci_dev *pdev,
			   काष्ठा otx2_cpt_eng_grps *eng_grps)
अणु
	काष्ठा otx2_cpt_eng_grp_info *grp;
	पूर्णांक i, j, ret;

	eng_grps->obj = pci_get_drvdata(pdev);
	eng_grps->avail.se_cnt = eng_grps->avail.max_se_cnt;
	eng_grps->avail.ie_cnt = eng_grps->avail.max_ie_cnt;
	eng_grps->avail.ae_cnt = eng_grps->avail.max_ae_cnt;

	eng_grps->engs_num = eng_grps->avail.max_se_cnt +
			     eng_grps->avail.max_ie_cnt +
			     eng_grps->avail.max_ae_cnt;
	अगर (eng_grps->engs_num > OTX2_CPT_MAX_ENGINES) अणु
		dev_err(&pdev->dev,
			"Number of engines %d > than max supported %d\n",
			eng_grps->engs_num, OTX2_CPT_MAX_ENGINES);
		ret = -EINVAL;
		जाओ cleanup_eng_grps;
	पूर्ण

	क्रम (i = 0; i < OTX2_CPT_MAX_ENGINE_GROUPS; i++) अणु
		grp = &eng_grps->grp[i];
		grp->g = eng_grps;
		grp->idx = i;

		क्रम (j = 0; j < OTX2_CPT_MAX_ETYPES_PER_GRP; j++) अणु
			grp->engs[j].bmap =
				kसुस्मृति(BITS_TO_LONGS(eng_grps->engs_num),
					माप(दीर्घ), GFP_KERNEL);
			अगर (!grp->engs[j].bmap) अणु
				ret = -ENOMEM;
				जाओ cleanup_eng_grps;
			पूर्ण
		पूर्ण
	पूर्ण
	वापस 0;

cleanup_eng_grps:
	otx2_cpt_cleanup_eng_grps(pdev, eng_grps);
	वापस ret;
पूर्ण

अटल पूर्णांक create_eng_caps_discovery_grps(काष्ठा pci_dev *pdev,
					  काष्ठा otx2_cpt_eng_grps *eng_grps)
अणु
	काष्ठा otx2_cpt_uc_info_t *uc_info[OTX2_CPT_MAX_ETYPES_PER_GRP] = अणु  पूर्ण;
	काष्ठा otx2_cpt_engines engs[OTX2_CPT_MAX_ETYPES_PER_GRP] = अणु अणु0पूर्ण पूर्ण;
	काष्ठा fw_info_t fw_info;
	पूर्णांक ret;

	ret = cpt_ucode_load_fw(pdev, &fw_info);
	अगर (ret)
		वापस ret;

	uc_info[0] = get_ucode(&fw_info, OTX2_CPT_SE_TYPES);
	अगर (uc_info[0] == शून्य) अणु
		dev_err(&pdev->dev, "Unable to find firmware for AE\n");
		ret = -EINVAL;
		जाओ release_fw;
	पूर्ण
	engs[0].type = OTX2_CPT_AE_TYPES;
	engs[0].count = 2;

	ret = create_engine_group(&pdev->dev, eng_grps, engs, 1,
				  (व्योम **) uc_info, 0);
	अगर (ret)
		जाओ release_fw;

	uc_info[0] = get_ucode(&fw_info, OTX2_CPT_SE_TYPES);
	अगर (uc_info[0] == शून्य) अणु
		dev_err(&pdev->dev, "Unable to find firmware for SE\n");
		ret = -EINVAL;
		जाओ delete_eng_grp;
	पूर्ण
	engs[0].type = OTX2_CPT_SE_TYPES;
	engs[0].count = 2;

	ret = create_engine_group(&pdev->dev, eng_grps, engs, 1,
				  (व्योम **) uc_info, 0);
	अगर (ret)
		जाओ delete_eng_grp;

	uc_info[0] = get_ucode(&fw_info, OTX2_CPT_IE_TYPES);
	अगर (uc_info[0] == शून्य) अणु
		dev_err(&pdev->dev, "Unable to find firmware for IE\n");
		ret = -EINVAL;
		जाओ delete_eng_grp;
	पूर्ण
	engs[0].type = OTX2_CPT_IE_TYPES;
	engs[0].count = 2;

	ret = create_engine_group(&pdev->dev, eng_grps, engs, 1,
				  (व्योम **) uc_info, 0);
	अगर (ret)
		जाओ delete_eng_grp;

	cpt_ucode_release_fw(&fw_info);
	वापस 0;

delete_eng_grp:
	delete_engine_grps(pdev, eng_grps);
release_fw:
	cpt_ucode_release_fw(&fw_info);
	वापस ret;
पूर्ण

/*
 * Get CPT HW capabilities using LOAD_FVC operation.
 */
पूर्णांक otx2_cpt_discover_eng_capabilities(काष्ठा otx2_cptpf_dev *cptpf)
अणु
	काष्ठा otx2_cptlfs_info *lfs = &cptpf->lfs;
	काष्ठा otx2_cpt_iq_command iq_cmd;
	जोड़ otx2_cpt_opcode opcode;
	जोड़ otx2_cpt_res_s *result;
	जोड़ otx2_cpt_inst_s inst;
	dma_addr_t rptr_baddr;
	काष्ठा pci_dev *pdev;
	u32 len, compl_rlen;
	पूर्णांक ret, etype;
	व्योम *rptr;

	/*
	 * We करोn't get capabilities अगर it was alपढ़ोy करोne
	 * (when user enabled VFs क्रम the first समय)
	 */
	अगर (cptpf->is_eng_caps_discovered)
		वापस 0;

	pdev = cptpf->pdev;
	/*
	 * Create engine groups क्रम each type to submit LOAD_FVC op and
	 * get engine's capabilities.
	 */
	ret = create_eng_caps_discovery_grps(pdev, &cptpf->eng_grps);
	अगर (ret)
		जाओ delete_grps;

	lfs->pdev = pdev;
	lfs->reg_base = cptpf->reg_base;
	lfs->mbox = &cptpf->afpf_mbox;
	lfs->blkaddr = BLKADDR_CPT0;
	ret = otx2_cptlf_init(&cptpf->lfs, OTX2_CPT_ALL_ENG_GRPS_MASK,
			      OTX2_CPT_QUEUE_HI_PRIO, 1);
	अगर (ret)
		जाओ delete_grps;

	compl_rlen = ALIGN(माप(जोड़ otx2_cpt_res_s), OTX2_CPT_DMA_MINALIGN);
	len = compl_rlen + LOADFVC_RLEN;

	result = kzalloc(len, GFP_KERNEL);
	अगर (!result) अणु
		ret = -ENOMEM;
		जाओ lf_cleanup;
	पूर्ण
	rptr_baddr = dma_map_single(&pdev->dev, (व्योम *)result, len,
				    DMA_BIसूचीECTIONAL);
	अगर (dma_mapping_error(&pdev->dev, rptr_baddr)) अणु
		dev_err(&pdev->dev, "DMA mapping failed\n");
		ret = -EFAULT;
		जाओ मुक्त_result;
	पूर्ण
	rptr = (u8 *)result + compl_rlen;

	/* Fill in the command */
	opcode.s.major = LOADFVC_MAJOR_OP;
	opcode.s.minor = LOADFVC_MINOR_OP;

	iq_cmd.cmd.u = 0;
	iq_cmd.cmd.s.opcode = cpu_to_be16(opcode.flags);

	/* 64-bit swap क्रम microcode data पढ़ोs, not needed क्रम addresses */
	cpu_to_be64s(&iq_cmd.cmd.u);
	iq_cmd.dptr = 0;
	iq_cmd.rptr = rptr_baddr + compl_rlen;
	iq_cmd.cptr.u = 0;

	क्रम (etype = 1; etype < OTX2_CPT_MAX_ENG_TYPES; etype++) अणु
		result->s.compcode = OTX2_CPT_COMPLETION_CODE_INIT;
		iq_cmd.cptr.s.grp = otx2_cpt_get_eng_grp(&cptpf->eng_grps,
							 etype);
		otx2_cpt_fill_inst(&inst, &iq_cmd, rptr_baddr);
		otx2_cpt_send_cmd(&inst, 1, &cptpf->lfs.lf[0]);

		जबतक (result->s.compcode == OTX2_CPT_COMPLETION_CODE_INIT)
			cpu_relax();

		cptpf->eng_caps[etype].u = be64_to_cpup(rptr);
	पूर्ण
	dma_unmap_single(&pdev->dev, rptr_baddr, len, DMA_BIसूचीECTIONAL);
	cptpf->is_eng_caps_discovered = true;

मुक्त_result:
	kमुक्त(result);
lf_cleanup:
	otx2_cptlf_shutकरोwn(&cptpf->lfs);
delete_grps:
	delete_engine_grps(pdev, &cptpf->eng_grps);

	वापस ret;
पूर्ण
