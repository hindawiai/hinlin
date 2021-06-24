<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause
/*
 * Copyright (c) 2020, MIPI Alliance, Inc.
 *
 * Author: Nicolas Pitre <npitre@baylibre.com>
 */

#समावेश <linux/bitfield.h>
#समावेश <linux/device.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/i3c/master.h>
#समावेश <linux/kernel.h>
#समावेश <linux/पन.स>

#समावेश "hci.h"
#समावेश "ext_caps.h"
#समावेश "xfer_mode_rate.h"


/* Extended Capability Header */
#घोषणा CAP_HEADER_LENGTH		GENMASK(23, 8)
#घोषणा CAP_HEADER_ID			GENMASK(7, 0)

अटल पूर्णांक hci_extcap_hardware_id(काष्ठा i3c_hci *hci, व्योम __iomem *base)
अणु
	hci->venकरोr_mipi_id	= पढ़ोl(base + 0x04);
	hci->venकरोr_version_id	= पढ़ोl(base + 0x08);
	hci->venकरोr_product_id	= पढ़ोl(base + 0x0c);

	dev_info(&hci->master.dev, "vendor MIPI ID: %#x\n", hci->venकरोr_mipi_id);
	dev_info(&hci->master.dev, "vendor version ID: %#x\n", hci->venकरोr_version_id);
	dev_info(&hci->master.dev, "vendor product ID: %#x\n", hci->venकरोr_product_id);

	/* ought to go in a table अगर this grows too much */
	चयन (hci->venकरोr_mipi_id) अणु
	हाल MIPI_VENDOR_NXP:
		hci->quirks |= HCI_QUIRK_RAW_CCC;
		DBG("raw CCC quirks set");
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक hci_extcap_master_config(काष्ठा i3c_hci *hci, व्योम __iomem *base)
अणु
	u32 master_config = पढ़ोl(base + 0x04);
	अचिन्हित पूर्णांक operation_mode = FIELD_GET(GENMASK(5, 4), master_config);
	अटल स्थिर अक्षर * स्थिर functionality[] = अणु
		"(unknown)", "master only", "target only",
		"primary/secondary master" पूर्ण;
	dev_info(&hci->master.dev, "operation mode: %s\n", functionality[operation_mode]);
	अगर (operation_mode & 0x1)
		वापस 0;
	dev_err(&hci->master.dev, "only master mode is currently supported\n");
	वापस -EOPNOTSUPP;
पूर्ण

अटल पूर्णांक hci_extcap_multi_bus(काष्ठा i3c_hci *hci, व्योम __iomem *base)
अणु
	u32 bus_instance = पढ़ोl(base + 0x04);
	अचिन्हित पूर्णांक count = FIELD_GET(GENMASK(3, 0), bus_instance);

	dev_info(&hci->master.dev, "%d bus instances\n", count);
	वापस 0;
पूर्ण

अटल पूर्णांक hci_extcap_xfer_modes(काष्ठा i3c_hci *hci, व्योम __iomem *base)
अणु
	u32 header = पढ़ोl(base);
	u32 entries = FIELD_GET(CAP_HEADER_LENGTH, header) - 1;
	अचिन्हित पूर्णांक index;

	dev_info(&hci->master.dev, "transfer mode table has %d entries\n",
		 entries);
	base += 4;  /* skip header */
	क्रम (index = 0; index < entries; index++) अणु
		u32 mode_entry = पढ़ोl(base);

		DBG("mode %d: 0x%08x", index, mode_entry);
		/* TODO: will be needed when I3C core करोes more than SDR */
		base += 4;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक hci_extcap_xfer_rates(काष्ठा i3c_hci *hci, व्योम __iomem *base)
अणु
	u32 header = पढ़ोl(base);
	u32 entries = FIELD_GET(CAP_HEADER_LENGTH, header) - 1;
	u32 rate_entry;
	अचिन्हित पूर्णांक index, rate, rate_id, mode_id;

	base += 4;  /* skip header */

	dev_info(&hci->master.dev, "available data rates:\n");
	क्रम (index = 0; index < entries; index++) अणु
		rate_entry = पढ़ोl(base);
		DBG("entry %d: 0x%08x", index, rate_entry);
		rate = FIELD_GET(XFERRATE_ACTUAL_RATE_KHZ, rate_entry);
		rate_id = FIELD_GET(XFERRATE_RATE_ID, rate_entry);
		mode_id = FIELD_GET(XFERRATE_MODE_ID, rate_entry);
		dev_info(&hci->master.dev, "rate %d for %s = %d kHz\n",
			 rate_id,
			 mode_id == XFERRATE_MODE_I3C ? "I3C" :
			 mode_id == XFERRATE_MODE_I2C ? "I2C" :
			 "unknown mode",
			 rate);
		base += 4;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक hci_extcap_स्वतः_command(काष्ठा i3c_hci *hci, व्योम __iomem *base)
अणु
	u32 स्वतःcmd_ext_caps = पढ़ोl(base + 0x04);
	अचिन्हित पूर्णांक max_count = FIELD_GET(GENMASK(3, 0), स्वतःcmd_ext_caps);
	u32 स्वतःcmd_ext_config = पढ़ोl(base + 0x08);
	अचिन्हित पूर्णांक count = FIELD_GET(GENMASK(3, 0), स्वतःcmd_ext_config);

	dev_info(&hci->master.dev, "%d/%d active auto-command entries\n",
		 count, max_count);
	/* remember स्वतः-command रेजिस्टर location क्रम later use */
	hci->AUTOCMD_regs = base;
	वापस 0;
पूर्ण

अटल पूर्णांक hci_extcap_debug(काष्ठा i3c_hci *hci, व्योम __iomem *base)
अणु
	dev_info(&hci->master.dev, "debug registers present\n");
	hci->DEBUG_regs = base;
	वापस 0;
पूर्ण

अटल पूर्णांक hci_extcap_scheduled_cmd(काष्ठा i3c_hci *hci, व्योम __iomem *base)
अणु
	dev_info(&hci->master.dev, "scheduled commands available\n");
	/* hci->schedcmd_regs = base; */
	वापस 0;
पूर्ण

अटल पूर्णांक hci_extcap_non_curr_master(काष्ठा i3c_hci *hci, व्योम __iomem *base)
अणु
	dev_info(&hci->master.dev, "Non-Current Master support available\n");
	/* hci->NCM_regs = base; */
	वापस 0;
पूर्ण

अटल पूर्णांक hci_extcap_ccc_resp_conf(काष्ठा i3c_hci *hci, व्योम __iomem *base)
अणु
	dev_info(&hci->master.dev, "CCC Response Configuration available\n");
	वापस 0;
पूर्ण

अटल पूर्णांक hci_extcap_global_DAT(काष्ठा i3c_hci *hci, व्योम __iomem *base)
अणु
	dev_info(&hci->master.dev, "Global DAT available\n");
	वापस 0;
पूर्ण

अटल पूर्णांक hci_extcap_multilane(काष्ठा i3c_hci *hci, व्योम __iomem *base)
अणु
	dev_info(&hci->master.dev, "Master Multi-Lane support available\n");
	वापस 0;
पूर्ण

अटल पूर्णांक hci_extcap_ncm_multilane(काष्ठा i3c_hci *hci, व्योम __iomem *base)
अणु
	dev_info(&hci->master.dev, "NCM Multi-Lane support available\n");
	वापस 0;
पूर्ण

काष्ठा hci_ext_caps अणु
	u8  id;
	u16 min_length;
	पूर्णांक (*parser)(काष्ठा i3c_hci *hci, व्योम __iomem *base);
पूर्ण;

#घोषणा EXT_CAP(_id, _highest_mandatory_reg_offset, _parser) \
	अणु .id = (_id), .parser = (_parser), \
	  .min_length = (_highest_mandatory_reg_offset)/4 + 1 पूर्ण

अटल स्थिर काष्ठा hci_ext_caps ext_capabilities[] = अणु
	EXT_CAP(0x01, 0x0c, hci_extcap_hardware_id),
	EXT_CAP(0x02, 0x04, hci_extcap_master_config),
	EXT_CAP(0x03, 0x04, hci_extcap_multi_bus),
	EXT_CAP(0x04, 0x24, hci_extcap_xfer_modes),
	EXT_CAP(0x05, 0x08, hci_extcap_स्वतः_command),
	EXT_CAP(0x08, 0x40, hci_extcap_xfer_rates),
	EXT_CAP(0x0c, 0x10, hci_extcap_debug),
	EXT_CAP(0x0d, 0x0c, hci_extcap_scheduled_cmd),
	EXT_CAP(0x0e, 0x80, hci_extcap_non_curr_master), /* TODO confirm size */
	EXT_CAP(0x0f, 0x04, hci_extcap_ccc_resp_conf),
	EXT_CAP(0x10, 0x08, hci_extcap_global_DAT),
	EXT_CAP(0x9d, 0x04,	hci_extcap_multilane),
	EXT_CAP(0x9e, 0x04, hci_extcap_ncm_multilane),
पूर्ण;

अटल पूर्णांक hci_extcap_venकरोr_NXP(काष्ठा i3c_hci *hci, व्योम __iomem *base)
अणु
	hci->venकरोr_data = (__क्रमce व्योम *)base;
	dev_info(&hci->master.dev, "Build Date Info = %#x\n", पढ़ोl(base + 1*4));
	/* reset the FPGA */
	ग_लिखोl(0xdeadbeef, base + 1*4);
	वापस 0;
पूर्ण

काष्ठा hci_ext_cap_venकरोr_specअगरic अणु
	u32 venकरोr;
	u8  cap;
	u16 min_length;
	पूर्णांक (*parser)(काष्ठा i3c_hci *hci, व्योम __iomem *base);
पूर्ण;

#घोषणा EXT_CAP_VENDOR(_venकरोr, _cap, _highest_mandatory_reg_offset) \
	अणु .venकरोr = (MIPI_VENDOR_##_venकरोr), .cap = (_cap), \
	  .parser = (hci_extcap_venकरोr_##_venकरोr), \
	  .min_length = (_highest_mandatory_reg_offset)/4 + 1 पूर्ण

अटल स्थिर काष्ठा hci_ext_cap_venकरोr_specअगरic venकरोr_ext_caps[] = अणु
	EXT_CAP_VENDOR(NXP, 0xc0, 0x20),
पूर्ण;

अटल पूर्णांक hci_extcap_venकरोr_specअगरic(काष्ठा i3c_hci *hci, व्योम __iomem *base,
				      u32 cap_id, u32 cap_length)
अणु
	स्थिर काष्ठा hci_ext_cap_venकरोr_specअगरic *venकरोr_cap_entry;
	पूर्णांक i;

	venकरोr_cap_entry = शून्य;
	क्रम (i = 0; i < ARRAY_SIZE(venकरोr_ext_caps); i++) अणु
		अगर (venकरोr_ext_caps[i].venकरोr == hci->venकरोr_mipi_id &&
		    venकरोr_ext_caps[i].cap == cap_id) अणु
			venकरोr_cap_entry = &venकरोr_ext_caps[i];
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!venकरोr_cap_entry) अणु
		dev_notice(&hci->master.dev,
			   "unknown ext_cap 0x%02x for vendor 0x%02x\n",
			   cap_id, hci->venकरोr_mipi_id);
		वापस 0;
	पूर्ण
	अगर (cap_length < venकरोr_cap_entry->min_length) अणु
		dev_err(&hci->master.dev,
			"ext_cap 0x%02x has size %d (expecting >= %d)\n",
			cap_id, cap_length, venकरोr_cap_entry->min_length);
		वापस -EINVAL;
	पूर्ण
	वापस venकरोr_cap_entry->parser(hci, base);
पूर्ण

पूर्णांक i3c_hci_parse_ext_caps(काष्ठा i3c_hci *hci)
अणु
	व्योम __iomem *curr_cap = hci->EXTCAPS_regs;
	व्योम __iomem *end = curr_cap + 0x1000; /* some arbitrary limit */
	u32 cap_header, cap_id, cap_length;
	स्थिर काष्ठा hci_ext_caps *cap_entry;
	पूर्णांक i, err = 0;

	अगर (!curr_cap)
		वापस 0;

	क्रम (; !err && curr_cap < end; curr_cap += cap_length * 4) अणु
		cap_header = पढ़ोl(curr_cap);
		cap_id = FIELD_GET(CAP_HEADER_ID, cap_header);
		cap_length = FIELD_GET(CAP_HEADER_LENGTH, cap_header);
		DBG("id=0x%02x length=%d", cap_id, cap_length);
		अगर (!cap_length)
			अवरोध;
		अगर (curr_cap + cap_length * 4 >= end) अणु
			dev_err(&hci->master.dev,
				"ext_cap 0x%02x has size %d (too big)\n",
				cap_id, cap_length);
			err = -EINVAL;
			अवरोध;
		पूर्ण

		अगर (cap_id >= 0xc0 && cap_id <= 0xcf) अणु
			err = hci_extcap_venकरोr_specअगरic(hci, curr_cap,
							 cap_id, cap_length);
			जारी;
		पूर्ण

		cap_entry = शून्य;
		क्रम (i = 0; i < ARRAY_SIZE(ext_capabilities); i++) अणु
			अगर (ext_capabilities[i].id == cap_id) अणु
				cap_entry = &ext_capabilities[i];
				अवरोध;
			पूर्ण
		पूर्ण
		अगर (!cap_entry) अणु
			dev_notice(&hci->master.dev,
				   "unknown ext_cap 0x%02x\n", cap_id);
		पूर्ण अन्यथा अगर (cap_length < cap_entry->min_length) अणु
			dev_err(&hci->master.dev,
				"ext_cap 0x%02x has size %d (expecting >= %d)\n",
				cap_id, cap_length, cap_entry->min_length);
			err = -EINVAL;
		पूर्ण अन्यथा अणु
			err = cap_entry->parser(hci, curr_cap);
		पूर्ण
	पूर्ण
	वापस err;
पूर्ण
