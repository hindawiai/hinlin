<शैली गुरु>
/*
 * This file is provided under a dual BSD/GPLv2 license.  When using or
 * redistributing this file, you may करो so under either license.
 *
 * GPL LICENSE SUMMARY
 *
 * Copyright(c) 2008 - 2011 Intel Corporation. All rights reserved.
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of version 2 of the GNU General Public License as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License क्रम more details.
 *
 * You should have received a copy of the GNU General Public License
 * aदीर्घ with this program; अगर not, ग_लिखो to the Free Software
 * Foundation, Inc., 51 Franklin St - Fअगरth Floor, Boston, MA 02110-1301 USA.
 * The full GNU General Public License is included in this distribution
 * in the file called LICENSE.GPL.
 */

/* probe_roms - scan क्रम oem parameters */

#समावेश <linux/kernel.h>
#समावेश <linux/firmware.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/efi.h>
#समावेश <यंत्र/probe_roms.h>

#समावेश "isci.h"
#समावेश "task.h"
#समावेश "probe_roms.h"

अटल efi_अक्षर16_t isci_efivar_name[] = अणु
	'R', 's', 't', 'S', 'c', 'u', 'O'
पूर्ण;

काष्ठा isci_orom *isci_request_oprom(काष्ठा pci_dev *pdev)
अणु
	व्योम __iomem *oprom = pci_map_biosrom(pdev);
	काष्ठा isci_orom *rom = शून्य;
	माप_प्रकार len, i;
	पूर्णांक j;
	अक्षर oem_sig[4];
	काष्ठा isci_oem_hdr oem_hdr;
	u8 *पंचांगp, sum;

	अगर (!oprom)
		वापस शून्य;

	len = pci_biosrom_size(pdev);
	rom = devm_kzalloc(&pdev->dev, माप(*rom), GFP_KERNEL);
	अगर (!rom) अणु
		pci_unmap_biosrom(oprom);
		dev_warn(&pdev->dev,
			 "Unable to allocate memory for orom\n");
		वापस शून्य;
	पूर्ण

	क्रम (i = 0; i < len && rom; i += ISCI_OEM_SIG_SIZE) अणु
		स_नकल_fromio(oem_sig, oprom + i, ISCI_OEM_SIG_SIZE);

		/* we think we found the OEM table */
		अगर (स_भेद(oem_sig, ISCI_OEM_SIG, ISCI_OEM_SIG_SIZE) == 0) अणु
			माप_प्रकार copy_len;

			स_नकल_fromio(&oem_hdr, oprom + i, माप(oem_hdr));

			copy_len = min(oem_hdr.len - माप(oem_hdr),
				       माप(*rom));

			स_नकल_fromio(rom,
				      oprom + i + माप(oem_hdr),
				      copy_len);

			/* calculate checksum */
			पंचांगp = (u8 *)&oem_hdr;
			क्रम (j = 0, sum = 0; j < माप(oem_hdr); j++, पंचांगp++)
				sum += *पंचांगp;

			पंचांगp = (u8 *)rom;
			क्रम (j = 0; j < माप(*rom); j++, पंचांगp++)
				sum += *पंचांगp;

			अगर (sum != 0) अणु
				dev_warn(&pdev->dev,
					 "OEM table checksum failed\n");
				जारी;
			पूर्ण

			/* keep going अगर that's not the oem param table */
			अगर (स_भेद(rom->hdr.signature,
				   ISCI_ROM_SIG,
				   ISCI_ROM_SIG_SIZE) != 0)
				जारी;

			dev_info(&pdev->dev,
				 "OEM parameter table found in OROM\n");
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (i >= len) अणु
		dev_err(&pdev->dev, "oprom parse error\n");
		rom = शून्य;
	पूर्ण
	pci_unmap_biosrom(oprom);

	वापस rom;
पूर्ण

काष्ठा isci_orom *isci_request_firmware(काष्ठा pci_dev *pdev, स्थिर काष्ठा firmware *fw)
अणु
	काष्ठा isci_orom *orom = शून्य, *data;
	पूर्णांक i, j;

	अगर (request_firmware(&fw, ISCI_FW_NAME, &pdev->dev) != 0)
		वापस शून्य;

	अगर (fw->size < माप(*orom))
		जाओ out;

	data = (काष्ठा isci_orom *)fw->data;

	अगर (म_भेदन(ISCI_ROM_SIG, data->hdr.signature,
		    म_माप(ISCI_ROM_SIG)) != 0)
		जाओ out;

	orom = devm_kzalloc(&pdev->dev, fw->size, GFP_KERNEL);
	अगर (!orom)
		जाओ out;

	स_नकल(orom, fw->data, fw->size);

	अगर (is_c0(pdev) || is_c1(pdev))
		जाओ out;

	/*
	 * deprecated: override शेष amp_control क्रम pre-preproduction
	 * silicon revisions
	 */
	क्रम (i = 0; i < ARRAY_SIZE(orom->ctrl); i++)
		क्रम (j = 0; j < ARRAY_SIZE(orom->ctrl[i].phys); j++) अणु
			orom->ctrl[i].phys[j].afe_tx_amp_control0 = 0xe7c03;
			orom->ctrl[i].phys[j].afe_tx_amp_control1 = 0xe7c03;
			orom->ctrl[i].phys[j].afe_tx_amp_control2 = 0xe7c03;
			orom->ctrl[i].phys[j].afe_tx_amp_control3 = 0xe7c03;
		पूर्ण
 out:
	release_firmware(fw);

	वापस orom;
पूर्ण

अटल काष्ठा efi *get_efi(व्योम)
अणु
#अगर_घोषित CONFIG_EFI
	वापस &efi;
#अन्यथा
	वापस शून्य;
#पूर्ण_अगर
पूर्ण

काष्ठा isci_orom *isci_get_efi_var(काष्ठा pci_dev *pdev)
अणु
	efi_status_t status;
	काष्ठा isci_orom *rom;
	काष्ठा isci_oem_hdr *oem_hdr;
	u8 *पंचांगp, sum;
	पूर्णांक j;
	अचिन्हित दीर्घ data_len;
	u8 *efi_data;
	u32 efi_attrib = 0;

	data_len = 1024;
	efi_data = devm_kzalloc(&pdev->dev, data_len, GFP_KERNEL);
	अगर (!efi_data) अणु
		dev_warn(&pdev->dev,
			 "Unable to allocate memory for EFI data\n");
		वापस शून्य;
	पूर्ण

	rom = (काष्ठा isci_orom *)(efi_data + माप(काष्ठा isci_oem_hdr));

	अगर (get_efi())
		status = get_efi()->get_variable(isci_efivar_name,
						 &ISCI_EFI_VENDOR_GUID,
						 &efi_attrib,
						 &data_len,
						 efi_data);
	अन्यथा
		status = EFI_NOT_FOUND;

	अगर (status != EFI_SUCCESS) अणु
		dev_warn(&pdev->dev,
			 "Unable to obtain EFI var data for OEM parms\n");
		वापस शून्य;
	पूर्ण

	oem_hdr = (काष्ठा isci_oem_hdr *)efi_data;

	अगर (स_भेद(oem_hdr->sig, ISCI_OEM_SIG, ISCI_OEM_SIG_SIZE) != 0) अणु
		dev_warn(&pdev->dev,
			 "Invalid OEM header signature\n");
		वापस शून्य;
	पूर्ण

	/* calculate checksum */
	पंचांगp = (u8 *)efi_data;
	क्रम (j = 0, sum = 0; j < (माप(*oem_hdr) + माप(*rom)); j++, पंचांगp++)
		sum += *पंचांगp;

	अगर (sum != 0) अणु
		dev_warn(&pdev->dev,
			 "OEM table checksum failed\n");
		वापस शून्य;
	पूर्ण

	अगर (स_भेद(rom->hdr.signature,
		   ISCI_ROM_SIG,
		   ISCI_ROM_SIG_SIZE) != 0) अणु
		dev_warn(&pdev->dev,
			 "Invalid OEM table signature\n");
		वापस शून्य;
	पूर्ण

	वापस rom;
पूर्ण
