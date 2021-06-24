<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (c) 2018 - Bootlin
 *
 * Author: Boris Brezillon <boris.brezillon@bootlin.com>
 *
 * Header containing पूर्णांकernal definitions to be used only by core files.
 * न_अंकD controller drivers should not include this file.
 */

#अगर_अघोषित __LINUX_RAWन_अंकD_INTERNALS
#घोषणा __LINUX_RAWन_अंकD_INTERNALS

#समावेश <linux/mtd/rawnand.h>

/*
 * न_अंकD Flash Manufacturer ID Codes
 */
#घोषणा न_अंकD_MFR_AMD		0x01
#घोषणा न_अंकD_MFR_ATO		0x9b
#घोषणा न_अंकD_MFR_EON		0x92
#घोषणा न_अंकD_MFR_ESMT		0xc8
#घोषणा न_अंकD_MFR_FUJITSU	0x04
#घोषणा न_अंकD_MFR_HYNIX		0xad
#घोषणा न_अंकD_MFR_INTEL		0x89
#घोषणा न_अंकD_MFR_MACRONIX	0xc2
#घोषणा न_अंकD_MFR_MICRON		0x2c
#घोषणा न_अंकD_MFR_NATIONAL	0x8f
#घोषणा न_अंकD_MFR_RENESAS	0x07
#घोषणा न_अंकD_MFR_SAMSUNG	0xec
#घोषणा न_अंकD_MFR_SANDISK	0x45
#घोषणा न_अंकD_MFR_STMICRO	0x20
/* Kioxia is new name of Toshiba memory. */
#घोषणा न_अंकD_MFR_TOSHIBA	0x98
#घोषणा न_अंकD_MFR_WINBOND	0xef

/**
 * काष्ठा nand_manufacturer_ops - न_अंकD Manufacturer operations
 * @detect: detect the न_अंकD memory organization and capabilities
 * @init: initialize all venकरोr specअगरic fields (like the ->पढ़ो_retry()
 *	  implementation) अगर any.
 * @cleanup: the ->init() function may have allocated resources, ->cleanup()
 *	     is here to let venकरोr specअगरic code release those resources.
 * @fixup_onfi_param_page: apply venकरोr specअगरic fixups to the ONFI parameter
 *			   page. This is called after the checksum is verअगरied.
 */
काष्ठा nand_manufacturer_ops अणु
	व्योम (*detect)(काष्ठा nand_chip *chip);
	पूर्णांक (*init)(काष्ठा nand_chip *chip);
	व्योम (*cleanup)(काष्ठा nand_chip *chip);
	व्योम (*fixup_onfi_param_page)(काष्ठा nand_chip *chip,
				      काष्ठा nand_onfi_params *p);
पूर्ण;

/**
 * काष्ठा nand_manufacturer_desc - न_अंकD Flash Manufacturer descriptor
 * @name: Manufacturer name
 * @id: manufacturer ID code of device.
 * @ops: manufacturer operations
 */
काष्ठा nand_manufacturer_desc अणु
	पूर्णांक id;
	अक्षर *name;
	स्थिर काष्ठा nand_manufacturer_ops *ops;
पूर्ण;


बाह्य काष्ठा nand_flash_dev nand_flash_ids[];

बाह्य स्थिर काष्ठा nand_manufacturer_ops amd_nand_manuf_ops;
बाह्य स्थिर काष्ठा nand_manufacturer_ops esmt_nand_manuf_ops;
बाह्य स्थिर काष्ठा nand_manufacturer_ops hynix_nand_manuf_ops;
बाह्य स्थिर काष्ठा nand_manufacturer_ops macronix_nand_manuf_ops;
बाह्य स्थिर काष्ठा nand_manufacturer_ops micron_nand_manuf_ops;
बाह्य स्थिर काष्ठा nand_manufacturer_ops samsung_nand_manuf_ops;
बाह्य स्थिर काष्ठा nand_manufacturer_ops toshiba_nand_manuf_ops;

/* MLC pairing schemes */
बाह्य स्थिर काष्ठा mtd_pairing_scheme dist3_pairing_scheme;

/* Core functions */
स्थिर काष्ठा nand_manufacturer_desc *nand_get_manufacturer_desc(u8 id);
पूर्णांक nand_bbm_get_next_page(काष्ठा nand_chip *chip, पूर्णांक page);
पूर्णांक nand_markbad_bbm(काष्ठा nand_chip *chip, loff_t ofs);
पूर्णांक nand_erase_nand(काष्ठा nand_chip *chip, काष्ठा erase_info *instr,
		    पूर्णांक allowbbt);
व्योम onfi_fill_पूर्णांकerface_config(काष्ठा nand_chip *chip,
				काष्ठा nand_पूर्णांकerface_config *अगरace,
				क्रमागत nand_पूर्णांकerface_type type,
				अचिन्हित पूर्णांक timing_mode);
अचिन्हित पूर्णांक
onfi_find_बंदst_sdr_mode(स्थिर काष्ठा nand_sdr_timings *spec_timings);
पूर्णांक nand_choose_best_sdr_timings(काष्ठा nand_chip *chip,
				 काष्ठा nand_पूर्णांकerface_config *अगरace,
				 काष्ठा nand_sdr_timings *spec_timings);
स्थिर काष्ठा nand_पूर्णांकerface_config *nand_get_reset_पूर्णांकerface_config(व्योम);
पूर्णांक nand_get_features(काष्ठा nand_chip *chip, पूर्णांक addr, u8 *subfeature_param);
पूर्णांक nand_set_features(काष्ठा nand_chip *chip, पूर्णांक addr, u8 *subfeature_param);
पूर्णांक nand_पढ़ो_page_raw_notsupp(काष्ठा nand_chip *chip, u8 *buf,
			       पूर्णांक oob_required, पूर्णांक page);
पूर्णांक nand_ग_लिखो_page_raw_notsupp(काष्ठा nand_chip *chip, स्थिर u8 *buf,
				पूर्णांक oob_required, पूर्णांक page);
पूर्णांक nand_निकास_status_op(काष्ठा nand_chip *chip);
पूर्णांक nand_पढ़ो_param_page_op(काष्ठा nand_chip *chip, u8 page, व्योम *buf,
			    अचिन्हित पूर्णांक len);
व्योम nand_decode_ext_id(काष्ठा nand_chip *chip);
व्योम panic_nand_रुको(काष्ठा nand_chip *chip, अचिन्हित दीर्घ समयo);
व्योम sanitize_string(uपूर्णांक8_t *s, माप_प्रकार len);

अटल अंतरभूत bool nand_has_exec_op(काष्ठा nand_chip *chip)
अणु
	अगर (!chip->controller || !chip->controller->ops ||
	    !chip->controller->ops->exec_op)
		वापस false;

	वापस true;
पूर्ण

अटल अंतरभूत पूर्णांक nand_check_op(काष्ठा nand_chip *chip,
				स्थिर काष्ठा nand_operation *op)
अणु
	अगर (!nand_has_exec_op(chip))
		वापस 0;

	वापस chip->controller->ops->exec_op(chip, op, true);
पूर्ण

अटल अंतरभूत पूर्णांक nand_exec_op(काष्ठा nand_chip *chip,
			       स्थिर काष्ठा nand_operation *op)
अणु
	अगर (!nand_has_exec_op(chip))
		वापस -ENOTSUPP;

	अगर (WARN_ON(op->cs >= nanddev_ntarमाला_लो(&chip->base)))
		वापस -EINVAL;

	वापस chip->controller->ops->exec_op(chip, op, false);
पूर्ण

अटल अंतरभूत bool nand_controller_can_setup_पूर्णांकerface(काष्ठा nand_chip *chip)
अणु
	अगर (!chip->controller || !chip->controller->ops ||
	    !chip->controller->ops->setup_पूर्णांकerface)
		वापस false;

	अगर (chip->options & न_अंकD_KEEP_TIMINGS)
		वापस false;

	वापस true;
पूर्ण

/* BBT functions */
पूर्णांक nand_markbad_bbt(काष्ठा nand_chip *chip, loff_t offs);
पूर्णांक nand_isreserved_bbt(काष्ठा nand_chip *chip, loff_t offs);
पूर्णांक nand_isbad_bbt(काष्ठा nand_chip *chip, loff_t offs, पूर्णांक allowbbt);

/* Legacy */
व्योम nand_legacy_set_शेषs(काष्ठा nand_chip *chip);
व्योम nand_legacy_adjust_cmdfunc(काष्ठा nand_chip *chip);
पूर्णांक nand_legacy_check_hooks(काष्ठा nand_chip *chip);

/* ONFI functions */
u16 onfi_crc16(u16 crc, u8 स्थिर *p, माप_प्रकार len);
पूर्णांक nand_onfi_detect(काष्ठा nand_chip *chip);

/* JEDEC functions */
पूर्णांक nand_jedec_detect(काष्ठा nand_chip *chip);

#पूर्ण_अगर /* __LINUX_RAWन_अंकD_INTERNALS */
