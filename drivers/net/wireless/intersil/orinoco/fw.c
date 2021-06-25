<शैली गुरु>
/* Firmware file पढ़ोing and करोwnload helpers
 *
 * See copyright notice in मुख्य.c
 */
#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/firmware.h>
#समावेश <linux/device.h>
#समावेश <linux/module.h>

#समावेश "hermes.h"
#समावेश "hermes_dld.h"
#समावेश "orinoco.h"

#समावेश "fw.h"

/* End markers (क्रम Symbol firmware only) */
#घोषणा TEXT_END	0x1A		/* End of text header */

काष्ठा fw_info अणु
	अक्षर *pri_fw;
	अक्षर *sta_fw;
	अक्षर *ap_fw;
	u32 pda_addr;
	u16 pda_size;
पूर्ण;

अटल स्थिर काष्ठा fw_info orinoco_fw[] = अणु
	अणु शून्य, "agere_sta_fw.bin", "agere_ap_fw.bin", 0x00390000, 1000 पूर्ण,
	अणु शून्य, "prism_sta_fw.bin", "prism_ap_fw.bin", 0, 1024 पूर्ण,
	अणु "symbol_sp24t_prim_fw", "symbol_sp24t_sec_fw", शून्य, 0x00003100, 512 पूर्ण
पूर्ण;
MODULE_FIRMWARE("agere_sta_fw.bin");
MODULE_FIRMWARE("agere_ap_fw.bin");
MODULE_FIRMWARE("prism_sta_fw.bin");
MODULE_FIRMWARE("prism_ap_fw.bin");
MODULE_FIRMWARE("symbol_sp24t_prim_fw");
MODULE_FIRMWARE("symbol_sp24t_sec_fw");

/* Structure used to access fields in FW
 * Make sure LE decoding macros are used
 */
काष्ठा orinoco_fw_header अणु
	अक्षर hdr_vers[6];       /* ASCII string क्रम header version */
	__le16 headersize;      /* Total length of header */
	__le32 entry_poपूर्णांक;     /* NIC entry poपूर्णांक */
	__le32 blocks;          /* Number of blocks to program */
	__le32 block_offset;    /* Offset of block data from eof header */
	__le32 pdr_offset;      /* Offset to PDR data from eof header */
	__le32 pri_offset;      /* Offset to primary plug data */
	__le32 compat_offset;   /* Offset to compatibility data*/
	अक्षर signature[];      /* FW signature length headersize-20 */
पूर्ण __packed;

/* Check the range of various header entries. Return a poपूर्णांकer to a
 * description of the problem, or शून्य अगर everything checks out. */
अटल स्थिर अक्षर *validate_fw(स्थिर काष्ठा orinoco_fw_header *hdr, माप_प्रकार len)
अणु
	u16 hdrsize;

	अगर (len < माप(*hdr))
		वापस "image too small";
	अगर (स_भेद(hdr->hdr_vers, "HFW", 3) != 0)
		वापस "format not recognised";

	hdrsize = le16_to_cpu(hdr->headersize);
	अगर (hdrsize > len)
		वापस "bad headersize";
	अगर ((hdrsize + le32_to_cpu(hdr->block_offset)) > len)
		वापस "bad block offset";
	अगर ((hdrsize + le32_to_cpu(hdr->pdr_offset)) > len)
		वापस "bad PDR offset";
	अगर ((hdrsize + le32_to_cpu(hdr->pri_offset)) > len)
		वापस "bad PRI offset";
	अगर ((hdrsize + le32_to_cpu(hdr->compat_offset)) > len)
		वापस "bad compat offset";

	/* TODO: consider adding a checksum or CRC to the firmware क्रमmat */
	वापस शून्य;
पूर्ण

#अगर defined(CONFIG_HERMES_CACHE_FW_ON_INIT) || defined(CONFIG_PM_SLEEP)
अटल अंतरभूत स्थिर काष्ठा firmware *
orinoco_cached_fw_get(काष्ठा orinoco_निजी *priv, bool primary)
अणु
	अगर (primary)
		वापस priv->cached_pri_fw;
	अन्यथा
		वापस priv->cached_fw;
पूर्ण
#अन्यथा
#घोषणा orinoco_cached_fw_get(priv, primary) (शून्य)
#पूर्ण_अगर

/* Download either STA or AP firmware पूर्णांकo the card. */
अटल पूर्णांक
orinoco_dl_firmware(काष्ठा orinoco_निजी *priv,
		    स्थिर काष्ठा fw_info *fw,
		    पूर्णांक ap)
अणु
	/* Plug Data Area (PDA) */
	__le16 *pda;

	काष्ठा hermes *hw = &priv->hw;
	स्थिर काष्ठा firmware *fw_entry;
	स्थिर काष्ठा orinoco_fw_header *hdr;
	स्थिर अचिन्हित अक्षर *first_block;
	स्थिर व्योम *end;
	स्थिर अक्षर *firmware;
	स्थिर अक्षर *fw_err;
	काष्ठा device *dev = priv->dev;
	पूर्णांक err = 0;

	pda = kzalloc(fw->pda_size, GFP_KERNEL);
	अगर (!pda)
		वापस -ENOMEM;

	अगर (ap)
		firmware = fw->ap_fw;
	अन्यथा
		firmware = fw->sta_fw;

	dev_dbg(dev, "Attempting to download firmware %s\n", firmware);

	/* Read current plug data */
	err = hw->ops->पढ़ो_pda(hw, pda, fw->pda_addr, fw->pda_size);
	dev_dbg(dev, "Read PDA returned %d\n", err);
	अगर (err)
		जाओ मुक्त;

	अगर (!orinoco_cached_fw_get(priv, false)) अणु
		err = request_firmware(&fw_entry, firmware, priv->dev);

		अगर (err) अणु
			dev_err(dev, "Cannot find firmware %s\n", firmware);
			err = -ENOENT;
			जाओ मुक्त;
		पूर्ण
	पूर्ण अन्यथा
		fw_entry = orinoco_cached_fw_get(priv, false);

	hdr = (स्थिर काष्ठा orinoco_fw_header *) fw_entry->data;

	fw_err = validate_fw(hdr, fw_entry->size);
	अगर (fw_err) अणु
		dev_warn(dev, "Invalid firmware image detected (%s). "
			 "Aborting download\n", fw_err);
		err = -EINVAL;
		जाओ पात;
	पूर्ण

	/* Enable aux port to allow programming */
	err = hw->ops->program_init(hw, le32_to_cpu(hdr->entry_poपूर्णांक));
	dev_dbg(dev, "Program init returned %d\n", err);
	अगर (err != 0)
		जाओ पात;

	/* Program data */
	first_block = (fw_entry->data +
		       le16_to_cpu(hdr->headersize) +
		       le32_to_cpu(hdr->block_offset));
	end = fw_entry->data + fw_entry->size;

	err = hermes_program(hw, first_block, end);
	dev_dbg(dev, "Program returned %d\n", err);
	अगर (err != 0)
		जाओ पात;

	/* Update production data */
	first_block = (fw_entry->data +
		       le16_to_cpu(hdr->headersize) +
		       le32_to_cpu(hdr->pdr_offset));

	err = hermes_apply_pda_with_शेषs(hw, first_block, end, pda,
					     &pda[fw->pda_size / माप(*pda)]);
	dev_dbg(dev, "Apply PDA returned %d\n", err);
	अगर (err)
		जाओ पात;

	/* Tell card we've finished */
	err = hw->ops->program_end(hw);
	dev_dbg(dev, "Program end returned %d\n", err);
	अगर (err != 0)
		जाओ पात;

	/* Check अगर we're running */
	dev_dbg(dev, "hermes_present returned %d\n", hermes_present(hw));

पात:
	/* If we requested the firmware, release it. */
	अगर (!orinoco_cached_fw_get(priv, false))
		release_firmware(fw_entry);

मुक्त:
	kमुक्त(pda);
	वापस err;
पूर्ण

/*
 * Process a firmware image - stop the card, load the firmware, reset
 * the card and make sure it responds.  For the secondary firmware take
 * care of the PDA - पढ़ो it and then ग_लिखो it on top of the firmware.
 */
अटल पूर्णांक
symbol_dl_image(काष्ठा orinoco_निजी *priv, स्थिर काष्ठा fw_info *fw,
		स्थिर अचिन्हित अक्षर *image, स्थिर व्योम *end,
		पूर्णांक secondary)
अणु
	काष्ठा hermes *hw = &priv->hw;
	पूर्णांक ret = 0;
	स्थिर अचिन्हित अक्षर *ptr;
	स्थिर अचिन्हित अक्षर *first_block;

	/* Plug Data Area (PDA) */
	__le16 *pda = शून्य;

	/* Binary block begins after the 0x1A marker */
	ptr = image;
	जबतक (*ptr++ != TEXT_END);
	first_block = ptr;

	/* Read the PDA from EEPROM */
	अगर (secondary) अणु
		pda = kzalloc(fw->pda_size, GFP_KERNEL);
		अगर (!pda)
			वापस -ENOMEM;

		ret = hw->ops->पढ़ो_pda(hw, pda, fw->pda_addr, fw->pda_size);
		अगर (ret)
			जाओ मुक्त;
	पूर्ण

	/* Stop the firmware, so that it can be safely rewritten */
	अगर (priv->stop_fw) अणु
		ret = priv->stop_fw(priv, 1);
		अगर (ret)
			जाओ मुक्त;
	पूर्ण

	/* Program the adapter with new firmware */
	ret = hermes_program(hw, first_block, end);
	अगर (ret)
		जाओ मुक्त;

	/* Write the PDA to the adapter */
	अगर (secondary) अणु
		माप_प्रकार len = hermes_blocks_length(first_block, end);
		ptr = first_block + len;
		ret = hermes_apply_pda(hw, ptr, end, pda,
				       &pda[fw->pda_size / माप(*pda)]);
		kमुक्त(pda);
		अगर (ret)
			वापस ret;
	पूर्ण

	/* Run the firmware */
	अगर (priv->stop_fw) अणु
		ret = priv->stop_fw(priv, 0);
		अगर (ret)
			वापस ret;
	पूर्ण

	/* Reset hermes chip and make sure it responds */
	ret = hw->ops->init(hw);

	/* hermes_reset() should वापस 0 with the secondary firmware */
	अगर (secondary && ret != 0)
		वापस -ENODEV;

	/* And this should work with any firmware */
	अगर (!hermes_present(hw))
		वापस -ENODEV;

	वापस 0;

मुक्त:
	kमुक्त(pda);
	वापस ret;
पूर्ण


/*
 * Download the firmware पूर्णांकo the card, this also करोes a PCMCIA soft
 * reset on the card, to make sure it's in a sane state.
 */
अटल पूर्णांक
symbol_dl_firmware(काष्ठा orinoco_निजी *priv,
		   स्थिर काष्ठा fw_info *fw)
अणु
	काष्ठा device *dev = priv->dev;
	पूर्णांक ret;
	स्थिर काष्ठा firmware *fw_entry;

	अगर (!orinoco_cached_fw_get(priv, true)) अणु
		अगर (request_firmware(&fw_entry, fw->pri_fw, priv->dev) != 0) अणु
			dev_err(dev, "Cannot find firmware: %s\n", fw->pri_fw);
			वापस -ENOENT;
		पूर्ण
	पूर्ण अन्यथा
		fw_entry = orinoco_cached_fw_get(priv, true);

	/* Load primary firmware */
	ret = symbol_dl_image(priv, fw, fw_entry->data,
			      fw_entry->data + fw_entry->size, 0);

	अगर (!orinoco_cached_fw_get(priv, true))
		release_firmware(fw_entry);
	अगर (ret) अणु
		dev_err(dev, "Primary firmware download failed\n");
		वापस ret;
	पूर्ण

	अगर (!orinoco_cached_fw_get(priv, false)) अणु
		अगर (request_firmware(&fw_entry, fw->sta_fw, priv->dev) != 0) अणु
			dev_err(dev, "Cannot find firmware: %s\n", fw->sta_fw);
			वापस -ENOENT;
		पूर्ण
	पूर्ण अन्यथा
		fw_entry = orinoco_cached_fw_get(priv, false);

	/* Load secondary firmware */
	ret = symbol_dl_image(priv, fw, fw_entry->data,
			      fw_entry->data + fw_entry->size, 1);
	अगर (!orinoco_cached_fw_get(priv, false))
		release_firmware(fw_entry);
	अगर (ret)
		dev_err(dev, "Secondary firmware download failed\n");

	वापस ret;
पूर्ण

पूर्णांक orinoco_करोwnload(काष्ठा orinoco_निजी *priv)
अणु
	पूर्णांक err = 0;
	/* Reload firmware */
	चयन (priv->firmware_type) अणु
	हाल FIRMWARE_TYPE_AGERE:
		/* हाल FIRMWARE_TYPE_INTERSIL: */
		err = orinoco_dl_firmware(priv,
					  &orinoco_fw[priv->firmware_type], 0);
		अवरोध;

	हाल FIRMWARE_TYPE_SYMBOL:
		err = symbol_dl_firmware(priv,
					 &orinoco_fw[priv->firmware_type]);
		अवरोध;
	हाल FIRMWARE_TYPE_INTERSIL:
		अवरोध;
	पूर्ण
	/* TODO: अगर we fail we probably need to reinitialise
	 * the driver */

	वापस err;
पूर्ण

#अगर defined(CONFIG_HERMES_CACHE_FW_ON_INIT) || defined(CONFIG_PM_SLEEP)
व्योम orinoco_cache_fw(काष्ठा orinoco_निजी *priv, पूर्णांक ap)
अणु
	स्थिर काष्ठा firmware *fw_entry = शून्य;
	स्थिर अक्षर *pri_fw;
	स्थिर अक्षर *fw;

	pri_fw = orinoco_fw[priv->firmware_type].pri_fw;
	अगर (ap)
		fw = orinoco_fw[priv->firmware_type].ap_fw;
	अन्यथा
		fw = orinoco_fw[priv->firmware_type].sta_fw;

	अगर (pri_fw) अणु
		अगर (request_firmware(&fw_entry, pri_fw, priv->dev) == 0)
			priv->cached_pri_fw = fw_entry;
	पूर्ण

	अगर (fw) अणु
		अगर (request_firmware(&fw_entry, fw, priv->dev) == 0)
			priv->cached_fw = fw_entry;
	पूर्ण
पूर्ण

व्योम orinoco_uncache_fw(काष्ठा orinoco_निजी *priv)
अणु
	release_firmware(priv->cached_pri_fw);
	release_firmware(priv->cached_fw);
	priv->cached_pri_fw = शून्य;
	priv->cached_fw = शून्य;
पूर्ण
#पूर्ण_अगर
