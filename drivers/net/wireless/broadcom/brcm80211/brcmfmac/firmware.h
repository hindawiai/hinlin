<शैली गुरु>
// SPDX-License-Identअगरier: ISC
/*
 * Copyright (c) 2013 Broadcom Corporation
 */
#अगर_अघोषित BRCMFMAC_FIRMWARE_H
#घोषणा BRCMFMAC_FIRMWARE_H

#घोषणा BRCMF_FW_REQF_OPTIONAL		0x0001

#घोषणा	BRCMF_FW_NAME_LEN		320

#घोषणा BRCMF_FW_DEFAULT_PATH		"brcm/"

/**
 * काष्ठा brcmf_firmware_mapping - Used to map chipid/revmask to firmware
 *	filename and nvram filename. Each bus type implementation should create
 *	a table of firmware mappings (using the macros defined below).
 *
 * @chipid: ID of chip.
 * @revmask: biपंचांगask of revisions, e.g. 0x10 means rev 4 only, 0xf means rev 0-3
 * @fw: name of the firmware file.
 * @nvram: name of nvram file.
 */
काष्ठा brcmf_firmware_mapping अणु
	u32 chipid;
	u32 revmask;
	स्थिर अक्षर *fw_base;
पूर्ण;

#घोषणा BRCMF_FW_DEF(fw_name, fw_base) \
अटल स्थिर अक्षर BRCM_ ## fw_name ## _FIRMWARE_BASENAME[] = \
	BRCMF_FW_DEFAULT_PATH fw_base; \
MODULE_FIRMWARE(BRCMF_FW_DEFAULT_PATH fw_base ".bin")

#घोषणा BRCMF_FW_ENTRY(chipid, mask, name) \
	अणु chipid, mask, BRCM_ ## name ## _FIRMWARE_BASENAME पूर्ण

व्योम brcmf_fw_nvram_मुक्त(व्योम *nvram);

क्रमागत brcmf_fw_type अणु
	BRCMF_FW_TYPE_BINARY,
	BRCMF_FW_TYPE_NVRAM
पूर्ण;

काष्ठा brcmf_fw_item अणु
	स्थिर अक्षर *path;
	क्रमागत brcmf_fw_type type;
	u16 flags;
	जोड़ अणु
		स्थिर काष्ठा firmware *binary;
		काष्ठा अणु
			व्योम *data;
			u32 len;
		पूर्ण nv_data;
	पूर्ण;
पूर्ण;

काष्ठा brcmf_fw_request अणु
	u16 करोमुख्य_nr;
	u16 bus_nr;
	u32 n_items;
	स्थिर अक्षर *board_type;
	काष्ठा brcmf_fw_item items[];
पूर्ण;

काष्ठा brcmf_fw_name अणु
	स्थिर अक्षर *extension;
	अक्षर *path;
पूर्ण;

काष्ठा brcmf_fw_request *
brcmf_fw_alloc_request(u32 chip, u32 chiprev,
		       स्थिर काष्ठा brcmf_firmware_mapping mapping_table[],
		       u32 table_size, काष्ठा brcmf_fw_name *fwnames,
		       u32 n_fwnames);

/*
 * Request firmware(s) asynchronously. When the asynchronous request
 * fails it will not use the callback, but call device_release_driver()
 * instead which will call the driver .हटाओ() callback.
 */
पूर्णांक brcmf_fw_get_firmwares(काष्ठा device *dev, काष्ठा brcmf_fw_request *req,
			   व्योम (*fw_cb)(काष्ठा device *dev, पूर्णांक err,
					 काष्ठा brcmf_fw_request *req));

#पूर्ण_अगर /* BRCMFMAC_FIRMWARE_H */
