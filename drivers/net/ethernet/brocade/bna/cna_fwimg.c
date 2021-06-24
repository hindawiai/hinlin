<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Linux network driver क्रम QLogic BR-series Converged Network Adapter.
 */
/*
 * Copyright (c) 2005-2014 Brocade Communications Systems, Inc.
 * Copyright (c) 2014-2015 QLogic Corporation
 * All rights reserved
 * www.qlogic.com
 */
#समावेश <linux/firmware.h>
#समावेश "bnad.h"
#समावेश "bfi.h"
#समावेश "cna.h"

स्थिर काष्ठा firmware *bfi_fw;
अटल u32 *bfi_image_ct_cna, *bfi_image_ct2_cna;
अटल u32 bfi_image_ct_cna_size, bfi_image_ct2_cna_size;

अटल u32 *
cna_पढ़ो_firmware(काष्ठा pci_dev *pdev, u32 **bfi_image,
			u32 *bfi_image_size, अक्षर *fw_name)
अणु
	स्थिर काष्ठा firmware *fw;
	u32 n;

	अगर (request_firmware(&fw, fw_name, &pdev->dev)) अणु
		dev_alert(&pdev->dev, "can't load firmware %s\n", fw_name);
		जाओ error;
	पूर्ण

	*bfi_image = (u32 *)fw->data;
	*bfi_image_size = fw->size/माप(u32);
	bfi_fw = fw;

	/* Convert loaded firmware to host order as it is stored in file
	 * as sequence of LE32 पूर्णांकegers.
	 */
	क्रम (n = 0; n < *bfi_image_size; n++)
		le32_to_cpus(*bfi_image + n);

	वापस *bfi_image;
error:
	वापस शून्य;
पूर्ण

u32 *
cna_get_firmware_buf(काष्ठा pci_dev *pdev)
अणु
	अगर (pdev->device == BFA_PCI_DEVICE_ID_CT2) अणु
		अगर (bfi_image_ct2_cna_size == 0)
			cna_पढ़ो_firmware(pdev, &bfi_image_ct2_cna,
				&bfi_image_ct2_cna_size, CNA_FW_खाता_CT2);
		वापस bfi_image_ct2_cna;
	पूर्ण अन्यथा अगर (bfa_asic_id_ct(pdev->device)) अणु
		अगर (bfi_image_ct_cna_size == 0)
			cna_पढ़ो_firmware(pdev, &bfi_image_ct_cna,
				&bfi_image_ct_cna_size, CNA_FW_खाता_CT);
		वापस bfi_image_ct_cna;
	पूर्ण

	वापस शून्य;
पूर्ण

u32 *
bfa_cb_image_get_chunk(क्रमागत bfi_asic_gen asic_gen, u32 off)
अणु
	चयन (asic_gen) अणु
	हाल BFI_ASIC_GEN_CT:
		वापस (bfi_image_ct_cna + off);
	हाल BFI_ASIC_GEN_CT2:
		वापस (bfi_image_ct2_cna + off);
	शेष:
		वापस शून्य;
	पूर्ण
पूर्ण

u32
bfa_cb_image_get_size(क्रमागत bfi_asic_gen asic_gen)
अणु
	चयन (asic_gen) अणु
	हाल BFI_ASIC_GEN_CT:
		वापस bfi_image_ct_cna_size;
	हाल BFI_ASIC_GEN_CT2:
		वापस bfi_image_ct2_cna_size;
	शेष:
		वापस 0;
	पूर्ण
पूर्ण
