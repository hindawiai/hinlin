<शैली गुरु>
// SPDX-License-Identअगरier: ISC
/*
 * Copyright (c) 2013 Broadcom Corporation
 */

#समावेश <linux/efi.h>
#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/device.h>
#समावेश <linux/firmware.h>
#समावेश <linux/module.h>
#समावेश <linux/bcm47xx_nvram.h>

#समावेश "debug.h"
#समावेश "firmware.h"
#समावेश "core.h"
#समावेश "common.h"
#समावेश "chip.h"

#घोषणा BRCMF_FW_MAX_NVRAM_SIZE			64000
#घोषणा BRCMF_FW_NVRAM_DEVPATH_LEN		19	/* devpath0=pcie/1/4/ */
#घोषणा BRCMF_FW_NVRAM_PCIEDEV_LEN		10	/* pcie/1/4/ + \0 */
#घोषणा BRCMF_FW_DEFAULT_BOARDREV		"boardrev=0xff"

क्रमागत nvram_parser_state अणु
	IDLE,
	KEY,
	VALUE,
	COMMENT,
	END
पूर्ण;

/**
 * काष्ठा nvram_parser - पूर्णांकernal info क्रम parser.
 *
 * @state: current parser state.
 * @data: input buffer being parsed.
 * @nvram: output buffer with parse result.
 * @nvram_len: length of parse result.
 * @line: current line.
 * @column: current column in line.
 * @pos: byte offset in input buffer.
 * @entry: start position of key,value entry.
 * @multi_dev_v1: detect pcie multi device v1 (compressed).
 * @multi_dev_v2: detect pcie multi device v2.
 * @boardrev_found: nvram contains boardrev inक्रमmation.
 */
काष्ठा nvram_parser अणु
	क्रमागत nvram_parser_state state;
	स्थिर u8 *data;
	u8 *nvram;
	u32 nvram_len;
	u32 line;
	u32 column;
	u32 pos;
	u32 entry;
	bool multi_dev_v1;
	bool multi_dev_v2;
	bool boardrev_found;
पूर्ण;

/*
 * is_nvram_अक्षर() - check अगर अक्षर is a valid one क्रम NVRAM entry
 *
 * It accepts all prपूर्णांकable ASCII अक्षरs except क्रम '#' which खोलोs a comment.
 * Please note that ' ' (space) जबतक accepted is not a valid key name अक्षर.
 */
अटल bool is_nvram_अक्षर(अक्षर c)
अणु
	/* comment marker excluded */
	अगर (c == '#')
		वापस false;

	/* key and value may have any other पढ़ोable अक्षरacter */
	वापस (c >= 0x20 && c < 0x7f);
पूर्ण

अटल bool is_whitespace(अक्षर c)
अणु
	वापस (c == ' ' || c == '\r' || c == '\n' || c == '\t');
पूर्ण

अटल क्रमागत nvram_parser_state brcmf_nvram_handle_idle(काष्ठा nvram_parser *nvp)
अणु
	अक्षर c;

	c = nvp->data[nvp->pos];
	अगर (c == '\n')
		वापस COMMENT;
	अगर (is_whitespace(c) || c == '\0')
		जाओ proceed;
	अगर (c == '#')
		वापस COMMENT;
	अगर (is_nvram_अक्षर(c)) अणु
		nvp->entry = nvp->pos;
		वापस KEY;
	पूर्ण
	brcmf_dbg(INFO, "warning: ln=%d:col=%d: ignoring invalid character\n",
		  nvp->line, nvp->column);
proceed:
	nvp->column++;
	nvp->pos++;
	वापस IDLE;
पूर्ण

अटल क्रमागत nvram_parser_state brcmf_nvram_handle_key(काष्ठा nvram_parser *nvp)
अणु
	क्रमागत nvram_parser_state st = nvp->state;
	अक्षर c;

	c = nvp->data[nvp->pos];
	अगर (c == '=') अणु
		/* ignore RAW1 by treating as comment */
		अगर (म_भेदन(&nvp->data[nvp->entry], "RAW1", 4) == 0)
			st = COMMENT;
		अन्यथा
			st = VALUE;
		अगर (म_भेदन(&nvp->data[nvp->entry], "devpath", 7) == 0)
			nvp->multi_dev_v1 = true;
		अगर (म_भेदन(&nvp->data[nvp->entry], "pcie/", 5) == 0)
			nvp->multi_dev_v2 = true;
		अगर (म_भेदन(&nvp->data[nvp->entry], "boardrev", 8) == 0)
			nvp->boardrev_found = true;
	पूर्ण अन्यथा अगर (!is_nvram_अक्षर(c) || c == ' ') अणु
		brcmf_dbg(INFO, "warning: ln=%d:col=%d: '=' expected, skip invalid key entry\n",
			  nvp->line, nvp->column);
		वापस COMMENT;
	पूर्ण

	nvp->column++;
	nvp->pos++;
	वापस st;
पूर्ण

अटल क्रमागत nvram_parser_state
brcmf_nvram_handle_value(काष्ठा nvram_parser *nvp)
अणु
	अक्षर c;
	अक्षर *skv;
	अक्षर *ekv;
	u32 cplen;

	c = nvp->data[nvp->pos];
	अगर (!is_nvram_अक्षर(c)) अणु
		/* key,value pair complete */
		ekv = (u8 *)&nvp->data[nvp->pos];
		skv = (u8 *)&nvp->data[nvp->entry];
		cplen = ekv - skv;
		अगर (nvp->nvram_len + cplen + 1 >= BRCMF_FW_MAX_NVRAM_SIZE)
			वापस END;
		/* copy to output buffer */
		स_नकल(&nvp->nvram[nvp->nvram_len], skv, cplen);
		nvp->nvram_len += cplen;
		nvp->nvram[nvp->nvram_len] = '\0';
		nvp->nvram_len++;
		वापस IDLE;
	पूर्ण
	nvp->pos++;
	nvp->column++;
	वापस VALUE;
पूर्ण

अटल क्रमागत nvram_parser_state
brcmf_nvram_handle_comment(काष्ठा nvram_parser *nvp)
अणु
	अक्षर *eoc, *sol;

	sol = (अक्षर *)&nvp->data[nvp->pos];
	eoc = म_अक्षर(sol, '\n');
	अगर (!eoc) अणु
		eoc = म_अक्षर(sol, '\0');
		अगर (!eoc)
			वापस END;
	पूर्ण

	/* eat all moving to next line */
	nvp->line++;
	nvp->column = 1;
	nvp->pos += (eoc - sol) + 1;
	वापस IDLE;
पूर्ण

अटल क्रमागत nvram_parser_state brcmf_nvram_handle_end(काष्ठा nvram_parser *nvp)
अणु
	/* final state */
	वापस END;
पूर्ण

अटल क्रमागत nvram_parser_state
(*nv_parser_states[])(काष्ठा nvram_parser *nvp) = अणु
	brcmf_nvram_handle_idle,
	brcmf_nvram_handle_key,
	brcmf_nvram_handle_value,
	brcmf_nvram_handle_comment,
	brcmf_nvram_handle_end
पूर्ण;

अटल पूर्णांक brcmf_init_nvram_parser(काष्ठा nvram_parser *nvp,
				   स्थिर u8 *data, माप_प्रकार data_len)
अणु
	माप_प्रकार size;

	स_रखो(nvp, 0, माप(*nvp));
	nvp->data = data;
	/* Limit size to MAX_NVRAM_SIZE, some files contain lot of comment */
	अगर (data_len > BRCMF_FW_MAX_NVRAM_SIZE)
		size = BRCMF_FW_MAX_NVRAM_SIZE;
	अन्यथा
		size = data_len;
	/* Alloc क्रम extra 0 byte + roundup by 4 + length field */
	size += 1 + 3 + माप(u32);
	nvp->nvram = kzalloc(size, GFP_KERNEL);
	अगर (!nvp->nvram)
		वापस -ENOMEM;

	nvp->line = 1;
	nvp->column = 1;
	वापस 0;
पूर्ण

/* brcmf_fw_strip_multi_v1 :Some nvram files contain settings क्रम multiple
 * devices. Strip it करोwn क्रम one device, use करोमुख्य_nr/bus_nr to determine
 * which data is to be वापसed. v1 is the version where nvram is stored
 * compressed and "devpath" maps to index क्रम valid entries.
 */
अटल व्योम brcmf_fw_strip_multi_v1(काष्ठा nvram_parser *nvp, u16 करोमुख्य_nr,
				    u16 bus_nr)
अणु
	/* Device path with a leading '=' key-value separator */
	अक्षर pci_path[] = "=pci/?/?";
	माप_प्रकार pci_len;
	अक्षर pcie_path[] = "=pcie/?/?";
	माप_प्रकार pcie_len;

	u32 i, j;
	bool found;
	u8 *nvram;
	u8 id;

	nvram = kzalloc(nvp->nvram_len + 1 + 3 + माप(u32), GFP_KERNEL);
	अगर (!nvram)
		जाओ fail;

	/* min length: devpath0=pcie/1/4/ + 0:x=y */
	अगर (nvp->nvram_len < BRCMF_FW_NVRAM_DEVPATH_LEN + 6)
		जाओ fail;

	/* First search क्रम the devpathX and see अगर it is the configuration
	 * क्रम करोमुख्य_nr/bus_nr. Search complete nvp
	 */
	snम_लिखो(pci_path, माप(pci_path), "=pci/%d/%d", करोमुख्य_nr,
		 bus_nr);
	pci_len = म_माप(pci_path);
	snम_लिखो(pcie_path, माप(pcie_path), "=pcie/%d/%d", करोमुख्य_nr,
		 bus_nr);
	pcie_len = म_माप(pcie_path);
	found = false;
	i = 0;
	जबतक (i < nvp->nvram_len - BRCMF_FW_NVRAM_DEVPATH_LEN) अणु
		/* Format: devpathX=pcie/Y/Z/
		 * Y = करोमुख्य_nr, Z = bus_nr, X = भव ID
		 */
		अगर (म_भेदन(&nvp->nvram[i], "devpath", 7) == 0 &&
		    (!म_भेदन(&nvp->nvram[i + 8], pci_path, pci_len) ||
		     !म_भेदन(&nvp->nvram[i + 8], pcie_path, pcie_len))) अणु
			id = nvp->nvram[i + 7] - '0';
			found = true;
			अवरोध;
		पूर्ण
		जबतक (nvp->nvram[i] != 0)
			i++;
		i++;
	पूर्ण
	अगर (!found)
		जाओ fail;

	/* Now copy all valid entries, release old nvram and assign new one */
	i = 0;
	j = 0;
	जबतक (i < nvp->nvram_len) अणु
		अगर ((nvp->nvram[i] - '0' == id) && (nvp->nvram[i + 1] == ':')) अणु
			i += 2;
			अगर (म_भेदन(&nvp->nvram[i], "boardrev", 8) == 0)
				nvp->boardrev_found = true;
			जबतक (nvp->nvram[i] != 0) अणु
				nvram[j] = nvp->nvram[i];
				i++;
				j++;
			पूर्ण
			nvram[j] = 0;
			j++;
		पूर्ण
		जबतक (nvp->nvram[i] != 0)
			i++;
		i++;
	पूर्ण
	kमुक्त(nvp->nvram);
	nvp->nvram = nvram;
	nvp->nvram_len = j;
	वापस;

fail:
	kमुक्त(nvram);
	nvp->nvram_len = 0;
पूर्ण

/* brcmf_fw_strip_multi_v2 :Some nvram files contain settings क्रम multiple
 * devices. Strip it करोwn क्रम one device, use करोमुख्य_nr/bus_nr to determine
 * which data is to be वापसed. v2 is the version where nvram is stored
 * uncompressed, all relevant valid entries are identअगरied by
 * pcie/करोमुख्य_nr/bus_nr:
 */
अटल व्योम brcmf_fw_strip_multi_v2(काष्ठा nvram_parser *nvp, u16 करोमुख्य_nr,
				    u16 bus_nr)
अणु
	अक्षर prefix[BRCMF_FW_NVRAM_PCIEDEV_LEN];
	माप_प्रकार len;
	u32 i, j;
	u8 *nvram;

	nvram = kzalloc(nvp->nvram_len + 1 + 3 + माप(u32), GFP_KERNEL);
	अगर (!nvram) अणु
		nvp->nvram_len = 0;
		वापस;
	पूर्ण

	/* Copy all valid entries, release old nvram and assign new one.
	 * Valid entries are of type pcie/X/Y/ where X = करोमुख्य_nr and
	 * Y = bus_nr.
	 */
	snम_लिखो(prefix, माप(prefix), "pcie/%d/%d/", करोमुख्य_nr, bus_nr);
	len = म_माप(prefix);
	i = 0;
	j = 0;
	जबतक (i < nvp->nvram_len - len) अणु
		अगर (म_भेदन(&nvp->nvram[i], prefix, len) == 0) अणु
			i += len;
			अगर (म_भेदन(&nvp->nvram[i], "boardrev", 8) == 0)
				nvp->boardrev_found = true;
			जबतक (nvp->nvram[i] != 0) अणु
				nvram[j] = nvp->nvram[i];
				i++;
				j++;
			पूर्ण
			nvram[j] = 0;
			j++;
		पूर्ण
		जबतक (nvp->nvram[i] != 0)
			i++;
		i++;
	पूर्ण
	kमुक्त(nvp->nvram);
	nvp->nvram = nvram;
	nvp->nvram_len = j;
पूर्ण

अटल व्योम brcmf_fw_add_शेषs(काष्ठा nvram_parser *nvp)
अणु
	अगर (nvp->boardrev_found)
		वापस;

	स_नकल(&nvp->nvram[nvp->nvram_len], &BRCMF_FW_DEFAULT_BOARDREV,
	       म_माप(BRCMF_FW_DEFAULT_BOARDREV));
	nvp->nvram_len += म_माप(BRCMF_FW_DEFAULT_BOARDREV);
	nvp->nvram[nvp->nvram_len] = '\0';
	nvp->nvram_len++;
पूर्ण

/* brcmf_nvram_strip :Takes a buffer of "<var>=<value>\n" lines पढ़ो from a fil
 * and ending in a NUL. Removes carriage वापसs, empty lines, comment lines,
 * and converts newlines to NULs. Shortens buffer as needed and pads with NULs.
 * End of buffer is completed with token identअगरying length of buffer.
 */
अटल व्योम *brcmf_fw_nvram_strip(स्थिर u8 *data, माप_प्रकार data_len,
				  u32 *new_length, u16 करोमुख्य_nr, u16 bus_nr)
अणु
	काष्ठा nvram_parser nvp;
	u32 pad;
	u32 token;
	__le32 token_le;

	अगर (brcmf_init_nvram_parser(&nvp, data, data_len) < 0)
		वापस शून्य;

	जबतक (nvp.pos < data_len) अणु
		nvp.state = nv_parser_states[nvp.state](&nvp);
		अगर (nvp.state == END)
			अवरोध;
	पूर्ण
	अगर (nvp.multi_dev_v1) अणु
		nvp.boardrev_found = false;
		brcmf_fw_strip_multi_v1(&nvp, करोमुख्य_nr, bus_nr);
	पूर्ण अन्यथा अगर (nvp.multi_dev_v2) अणु
		nvp.boardrev_found = false;
		brcmf_fw_strip_multi_v2(&nvp, करोमुख्य_nr, bus_nr);
	पूर्ण

	अगर (nvp.nvram_len == 0) अणु
		kमुक्त(nvp.nvram);
		वापस शून्य;
	पूर्ण

	brcmf_fw_add_शेषs(&nvp);

	pad = nvp.nvram_len;
	*new_length = roundup(nvp.nvram_len + 1, 4);
	जबतक (pad != *new_length) अणु
		nvp.nvram[pad] = 0;
		pad++;
	पूर्ण

	token = *new_length / 4;
	token = (~token << 16) | (token & 0x0000FFFF);
	token_le = cpu_to_le32(token);

	स_नकल(&nvp.nvram[*new_length], &token_le, माप(token_le));
	*new_length += माप(token_le);

	वापस nvp.nvram;
पूर्ण

व्योम brcmf_fw_nvram_मुक्त(व्योम *nvram)
अणु
	kमुक्त(nvram);
पूर्ण

काष्ठा brcmf_fw अणु
	काष्ठा device *dev;
	काष्ठा brcmf_fw_request *req;
	u32 curpos;
	व्योम (*करोne)(काष्ठा device *dev, पूर्णांक err, काष्ठा brcmf_fw_request *req);
पूर्ण;

अटल व्योम brcmf_fw_request_करोne(स्थिर काष्ठा firmware *fw, व्योम *ctx);

#अगर_घोषित CONFIG_EFI
/* In some हालs the EFI-var stored nvram contains "ccode=ALL" or "ccode=XV"
 * to specअगरy "worldwide" compatible settings, but these 2 ccode-s करो not work
 * properly. "ccode=ALL" causes channels 12 and 13 to not be available,
 * "ccode=XV" causes all 5GHz channels to not be available. So we replace both
 * with "ccode=X2" which allows channels 12+13 and 5Ghz channels in
 * no-Initiate-Radiation mode. This means that we will never send on these
 * channels without first having received valid wअगरi traffic on the channel.
 */
अटल व्योम brcmf_fw_fix_efi_nvram_ccode(अक्षर *data, अचिन्हित दीर्घ data_len)
अणु
	अक्षर *ccode;

	ccode = strnstr((अक्षर *)data, "ccode=ALL", data_len);
	अगर (!ccode)
		ccode = strnstr((अक्षर *)data, "ccode=XV\r", data_len);
	अगर (!ccode)
		वापस;

	ccode[6] = 'X';
	ccode[7] = '2';
	ccode[8] = '\r';
पूर्ण

अटल u8 *brcmf_fw_nvram_from_efi(माप_प्रकार *data_len_ret)
अणु
	स्थिर u16 name[] = अणु 'n', 'v', 'r', 'a', 'm', 0 पूर्ण;
	काष्ठा efivar_entry *nvram_efivar;
	अचिन्हित दीर्घ data_len = 0;
	u8 *data = शून्य;
	पूर्णांक err;

	nvram_efivar = kzalloc(माप(*nvram_efivar), GFP_KERNEL);
	अगर (!nvram_efivar)
		वापस शून्य;

	स_नकल(&nvram_efivar->var.VariableName, name, माप(name));
	nvram_efivar->var.VenकरोrGuid = EFI_GUID(0x74b00bd9, 0x805a, 0x4d61,
						0xb5, 0x1f, 0x43, 0x26,
						0x81, 0x23, 0xd1, 0x13);

	err = efivar_entry_size(nvram_efivar, &data_len);
	अगर (err)
		जाओ fail;

	data = kदो_स्मृति(data_len, GFP_KERNEL);
	अगर (!data)
		जाओ fail;

	err = efivar_entry_get(nvram_efivar, शून्य, &data_len, data);
	अगर (err)
		जाओ fail;

	brcmf_fw_fix_efi_nvram_ccode(data, data_len);
	brcmf_info("Using nvram EFI variable\n");

	kमुक्त(nvram_efivar);
	*data_len_ret = data_len;
	वापस data;

fail:
	kमुक्त(data);
	kमुक्त(nvram_efivar);
	वापस शून्य;
पूर्ण
#अन्यथा
अटल अंतरभूत u8 *brcmf_fw_nvram_from_efi(माप_प्रकार *data_len) अणु वापस शून्य; पूर्ण
#पूर्ण_अगर

अटल व्योम brcmf_fw_मुक्त_request(काष्ठा brcmf_fw_request *req)
अणु
	काष्ठा brcmf_fw_item *item;
	पूर्णांक i;

	क्रम (i = 0, item = &req->items[0]; i < req->n_items; i++, item++) अणु
		अगर (item->type == BRCMF_FW_TYPE_BINARY)
			release_firmware(item->binary);
		अन्यथा अगर (item->type == BRCMF_FW_TYPE_NVRAM)
			brcmf_fw_nvram_मुक्त(item->nv_data.data);
	पूर्ण
	kमुक्त(req);
पूर्ण

अटल पूर्णांक brcmf_fw_request_nvram_करोne(स्थिर काष्ठा firmware *fw, व्योम *ctx)
अणु
	काष्ठा brcmf_fw *fwctx = ctx;
	काष्ठा brcmf_fw_item *cur;
	bool मुक्त_bcm47xx_nvram = false;
	bool kमुक्त_nvram = false;
	u32 nvram_length = 0;
	व्योम *nvram = शून्य;
	u8 *data = शून्य;
	माप_प्रकार data_len;

	brcmf_dbg(TRACE, "enter: dev=%s\n", dev_name(fwctx->dev));

	cur = &fwctx->req->items[fwctx->curpos];

	अगर (fw && fw->data) अणु
		data = (u8 *)fw->data;
		data_len = fw->size;
	पूर्ण अन्यथा अणु
		अगर ((data = bcm47xx_nvram_get_contents(&data_len)))
			मुक्त_bcm47xx_nvram = true;
		अन्यथा अगर ((data = brcmf_fw_nvram_from_efi(&data_len)))
			kमुक्त_nvram = true;
		अन्यथा अगर (!(cur->flags & BRCMF_FW_REQF_OPTIONAL))
			जाओ fail;
	पूर्ण

	अगर (data)
		nvram = brcmf_fw_nvram_strip(data, data_len, &nvram_length,
					     fwctx->req->करोमुख्य_nr,
					     fwctx->req->bus_nr);

	अगर (मुक्त_bcm47xx_nvram)
		bcm47xx_nvram_release_contents(data);
	अगर (kमुक्त_nvram)
		kमुक्त(data);

	release_firmware(fw);
	अगर (!nvram && !(cur->flags & BRCMF_FW_REQF_OPTIONAL))
		जाओ fail;

	brcmf_dbg(TRACE, "nvram %p len %d\n", nvram, nvram_length);
	cur->nv_data.data = nvram;
	cur->nv_data.len = nvram_length;
	वापस 0;

fail:
	वापस -ENOENT;
पूर्ण

अटल पूर्णांक brcmf_fw_complete_request(स्थिर काष्ठा firmware *fw,
				     काष्ठा brcmf_fw *fwctx)
अणु
	काष्ठा brcmf_fw_item *cur = &fwctx->req->items[fwctx->curpos];
	पूर्णांक ret = 0;

	brcmf_dbg(TRACE, "firmware %s %sfound\n", cur->path, fw ? "" : "not ");

	चयन (cur->type) अणु
	हाल BRCMF_FW_TYPE_NVRAM:
		ret = brcmf_fw_request_nvram_करोne(fw, fwctx);
		अवरोध;
	हाल BRCMF_FW_TYPE_BINARY:
		अगर (fw)
			cur->binary = fw;
		अन्यथा
			ret = -ENOENT;
		अवरोध;
	शेष:
		/* something fishy here so bail out early */
		brcmf_err("unknown fw type: %d\n", cur->type);
		release_firmware(fw);
		ret = -EINVAL;
	पूर्ण

	वापस (cur->flags & BRCMF_FW_REQF_OPTIONAL) ? 0 : ret;
पूर्ण

अटल पूर्णांक brcmf_fw_request_firmware(स्थिर काष्ठा firmware **fw,
				     काष्ठा brcmf_fw *fwctx)
अणु
	काष्ठा brcmf_fw_item *cur = &fwctx->req->items[fwctx->curpos];
	पूर्णांक ret;

	/* nvram files are board-specअगरic, first try a board-specअगरic path */
	अगर (cur->type == BRCMF_FW_TYPE_NVRAM && fwctx->req->board_type) अणु
		अक्षर alt_path[BRCMF_FW_NAME_LEN];

		strlcpy(alt_path, cur->path, BRCMF_FW_NAME_LEN);
		/* strip .txt at the end */
		alt_path[म_माप(alt_path) - 4] = 0;
		strlcat(alt_path, ".", BRCMF_FW_NAME_LEN);
		strlcat(alt_path, fwctx->req->board_type, BRCMF_FW_NAME_LEN);
		strlcat(alt_path, ".txt", BRCMF_FW_NAME_LEN);

		ret = request_firmware(fw, alt_path, fwctx->dev);
		अगर (ret == 0)
			वापस ret;
	पूर्ण

	वापस request_firmware(fw, cur->path, fwctx->dev);
पूर्ण

अटल व्योम brcmf_fw_request_करोne(स्थिर काष्ठा firmware *fw, व्योम *ctx)
अणु
	काष्ठा brcmf_fw *fwctx = ctx;
	पूर्णांक ret;

	ret = brcmf_fw_complete_request(fw, fwctx);

	जबतक (ret == 0 && ++fwctx->curpos < fwctx->req->n_items) अणु
		brcmf_fw_request_firmware(&fw, fwctx);
		ret = brcmf_fw_complete_request(fw, ctx);
	पूर्ण

	अगर (ret) अणु
		brcmf_fw_मुक्त_request(fwctx->req);
		fwctx->req = शून्य;
	पूर्ण
	fwctx->करोne(fwctx->dev, ret, fwctx->req);
	kमुक्त(fwctx);
पूर्ण

अटल bool brcmf_fw_request_is_valid(काष्ठा brcmf_fw_request *req)
अणु
	काष्ठा brcmf_fw_item *item;
	पूर्णांक i;

	अगर (!req->n_items)
		वापस false;

	क्रम (i = 0, item = &req->items[0]; i < req->n_items; i++, item++) अणु
		अगर (!item->path)
			वापस false;
	पूर्ण
	वापस true;
पूर्ण

पूर्णांक brcmf_fw_get_firmwares(काष्ठा device *dev, काष्ठा brcmf_fw_request *req,
			   व्योम (*fw_cb)(काष्ठा device *dev, पूर्णांक err,
					 काष्ठा brcmf_fw_request *req))
अणु
	काष्ठा brcmf_fw_item *first = &req->items[0];
	काष्ठा brcmf_fw *fwctx;
	पूर्णांक ret;

	brcmf_dbg(TRACE, "enter: dev=%s\n", dev_name(dev));
	अगर (!fw_cb)
		वापस -EINVAL;

	अगर (!brcmf_fw_request_is_valid(req))
		वापस -EINVAL;

	fwctx = kzalloc(माप(*fwctx), GFP_KERNEL);
	अगर (!fwctx)
		वापस -ENOMEM;

	fwctx->dev = dev;
	fwctx->req = req;
	fwctx->करोne = fw_cb;

	ret = request_firmware_noरुको(THIS_MODULE, true, first->path,
				      fwctx->dev, GFP_KERNEL, fwctx,
				      brcmf_fw_request_करोne);
	अगर (ret < 0)
		brcmf_fw_request_करोne(शून्य, fwctx);

	वापस 0;
पूर्ण

काष्ठा brcmf_fw_request *
brcmf_fw_alloc_request(u32 chip, u32 chiprev,
		       स्थिर काष्ठा brcmf_firmware_mapping mapping_table[],
		       u32 table_size, काष्ठा brcmf_fw_name *fwnames,
		       u32 n_fwnames)
अणु
	काष्ठा brcmf_fw_request *fwreq;
	अक्षर chipname[12];
	स्थिर अक्षर *mp_path;
	माप_प्रकार mp_path_len;
	u32 i, j;
	अक्षर end = '\0';

	क्रम (i = 0; i < table_size; i++) अणु
		अगर (mapping_table[i].chipid == chip &&
		    mapping_table[i].revmask & BIT(chiprev))
			अवरोध;
	पूर्ण

	brcmf_chip_name(chip, chiprev, chipname, माप(chipname));

	अगर (i == table_size) अणु
		brcmf_err("Unknown chip %s\n", chipname);
		वापस शून्य;
	पूर्ण

	fwreq = kzalloc(काष्ठा_size(fwreq, items, n_fwnames), GFP_KERNEL);
	अगर (!fwreq)
		वापस शून्य;

	brcmf_info("using %s for chip %s\n",
		   mapping_table[i].fw_base, chipname);

	mp_path = brcmf_mp_global.firmware_path;
	mp_path_len = strnlen(mp_path, BRCMF_FW_ALTPATH_LEN);
	अगर (mp_path_len)
		end = mp_path[mp_path_len - 1];

	fwreq->n_items = n_fwnames;

	क्रम (j = 0; j < n_fwnames; j++) अणु
		fwreq->items[j].path = fwnames[j].path;
		fwnames[j].path[0] = '\0';
		/* check अगर firmware path is provided by module parameter */
		अगर (brcmf_mp_global.firmware_path[0] != '\0') अणु
			strlcpy(fwnames[j].path, mp_path,
				BRCMF_FW_NAME_LEN);

			अगर (end != '/') अणु
				strlcat(fwnames[j].path, "/",
					BRCMF_FW_NAME_LEN);
			पूर्ण
		पूर्ण
		strlcat(fwnames[j].path, mapping_table[i].fw_base,
			BRCMF_FW_NAME_LEN);
		strlcat(fwnames[j].path, fwnames[j].extension,
			BRCMF_FW_NAME_LEN);
		fwreq->items[j].path = fwnames[j].path;
	पूर्ण

	वापस fwreq;
पूर्ण
