<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2008 Nuovation System Designs, LLC
 *   Grant Erickson <gerickson@nuovations.com>
 */

#समावेश <linux/edac.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mm.h>
#समावेश <linux/module.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/types.h>

#समावेश <यंत्र/dcr.h>

#समावेश "edac_module.h"
#समावेश "ppc4xx_edac.h"

/*
 * This file implements a driver क्रम monitoring and handling events
 * associated with the IMB DDR2 ECC controller found in the AMCC/IBM
 * 405EX[r], 440SP, 440SPe, 460EX, 460GT and 460SX.
 *
 * As realized in the 405EX[r], this controller features:
 *
 *   - Support क्रम रेजिस्टरed- and non-रेजिस्टरed DDR1 and DDR2 memory.
 *   - 32-bit or 16-bit memory पूर्णांकerface with optional ECC.
 *
 *     o ECC support includes:
 *
 *       - 4-bit SEC/DED
 *       - Aligned-nibble error detect
 *       - Bypass mode
 *
 *   - Two (2) memory banks/ranks.
 *   - Up to 1 GiB per bank/rank in 32-bit mode and up to 512 MiB per
 *     bank/rank in 16-bit mode.
 *
 * As realized in the 440SP and 440SPe, this controller changes/adds:
 *
 *   - 64-bit or 32-bit memory पूर्णांकerface with optional ECC.
 *
 *     o ECC support includes:
 *
 *       - 8-bit SEC/DED
 *       - Aligned-nibble error detect
 *       - Bypass mode
 *
 *   - Up to 4 GiB per bank/rank in 64-bit mode and up to 2 GiB
 *     per bank/rank in 32-bit mode.
 *
 * As realized in the 460EX and 460GT, this controller changes/adds:
 *
 *   - 64-bit or 32-bit memory पूर्णांकerface with optional ECC.
 *
 *     o ECC support includes:
 *
 *       - 8-bit SEC/DED
 *       - Aligned-nibble error detect
 *       - Bypass mode
 *
 *   - Four (4) memory banks/ranks.
 *   - Up to 16 GiB per bank/rank in 64-bit mode and up to 8 GiB
 *     per bank/rank in 32-bit mode.
 *
 * At present, this driver has ONLY been tested against the controller
 * realization in the 405EX[r] on the AMCC Kilauea and Haleakala
 * boards (256 MiB w/o ECC memory soldered onto the board) and a
 * proprietary board based on those designs (128 MiB ECC memory, also
 * soldered onto the board).
 *
 * Dynamic feature detection and handling needs to be added क्रम the
 * other realizations of this controller listed above.
 *
 * Eventually, this driver will likely be adapted to the above variant
 * realizations of this controller as well as broken apart to handle
 * the other known ECC-capable controllers prevalent in other 4xx
 * processors:
 *
 *   - IBM SDRAM (405GP, 405CR and 405EP) "ibm,sdram-4xx"
 *   - IBM DDR1 (440GP, 440GX, 440EP and 440GR) "ibm,sdram-4xx-ddr"
 *   - Denali DDR1/DDR2 (440EPX and 440GRX) "denali,sdram-4xx-ddr2"
 *
 * For this controller, unक्रमtunately, correctable errors report
 * nothing more than the beat/cycle and byte/lane the correction
 * occurred on and the check bit group that covered the error.
 *
 * In contrast, uncorrectable errors also report the failing address,
 * the bus master and the transaction direction (i.e. पढ़ो or ग_लिखो)
 *
 * Regardless of whether the error is a CE or a UE, we report the
 * following pieces of inक्रमmation in the driver-unique message to the
 * EDAC subप्रणाली:
 *
 *   - Device tree path
 *   - Bank(s)
 *   - Check bit error group
 *   - Beat(s)/lane(s)
 */

/* Preprocessor Definitions */

#घोषणा EDAC_OPSTATE_INT_STR		"interrupt"
#घोषणा EDAC_OPSTATE_POLL_STR		"polled"
#घोषणा EDAC_OPSTATE_UNKNOWN_STR	"unknown"

#घोषणा PPC4XX_EDAC_MODULE_NAME		"ppc4xx_edac"
#घोषणा PPC4XX_EDAC_MODULE_REVISION	"v1.0.0"

#घोषणा PPC4XX_EDAC_MESSAGE_SIZE	256

/*
 * Kernel logging without an EDAC instance
 */
#घोषणा ppc4xx_edac_prपूर्णांकk(level, fmt, arg...) \
	edac_prपूर्णांकk(level, "PPC4xx MC", fmt, ##arg)

/*
 * Kernel logging with an EDAC instance
 */
#घोषणा ppc4xx_edac_mc_prपूर्णांकk(level, mci, fmt, arg...) \
	edac_mc_chipset_prपूर्णांकk(mci, level, "PPC4xx", fmt, ##arg)

/*
 * Macros to convert bank configuration size क्रमागतerations पूर्णांकo MiB and
 * page values.
 */
#घोषणा SDRAM_MBCF_SZ_MiB_MIN		4
#घोषणा SDRAM_MBCF_SZ_TO_MiB(n)		(SDRAM_MBCF_SZ_MiB_MIN \
					 << (SDRAM_MBCF_SZ_DECODE(n)))
#घोषणा SDRAM_MBCF_SZ_TO_PAGES(n)	(SDRAM_MBCF_SZ_MiB_MIN \
					 << (20 - PAGE_SHIFT + \
					     SDRAM_MBCF_SZ_DECODE(n)))

/*
 * The ibm,sdram-4xx-ddr2 Device Control Registers (DCRs) are
 * indirectly accessed and have a base and length defined by the
 * device tree. The base can be anything; however, we expect the
 * length to be precisely two रेजिस्टरs, the first क्रम the address
 * winकरोw and the second क्रम the data winकरोw.
 */
#घोषणा SDRAM_DCR_RESOURCE_LEN		2
#घोषणा SDRAM_DCR_ADDR_OFFSET		0
#घोषणा SDRAM_DCR_DATA_OFFSET		1

/*
 * Device tree पूर्णांकerrupt indices
 */
#घोषणा INTMAP_ECCDED_INDEX		0	/* Double-bit Error Detect */
#घोषणा INTMAP_ECCSEC_INDEX		1	/* Single-bit Error Correct */

/* Type Definitions */

/*
 * PPC4xx SDRAM memory controller निजी instance data
 */
काष्ठा ppc4xx_edac_pdata अणु
	dcr_host_t dcr_host;	/* Indirect DCR address/data winकरोw mapping */
	काष्ठा अणु
		पूर्णांक sec;	/* Single-bit correctable error IRQ asचिन्हित */
		पूर्णांक ded;	/* Double-bit detectable error IRQ asचिन्हित */
	पूर्ण irqs;
पूर्ण;

/*
 * Various status data gathered and manipulated when checking and
 * reporting ECC status.
 */
काष्ठा ppc4xx_ecc_status अणु
	u32 ecces;
	u32 besr;
	u32 bearh;
	u32 bearl;
	u32 wmirq;
पूर्ण;

/* Function Prototypes */

अटल पूर्णांक ppc4xx_edac_probe(काष्ठा platक्रमm_device *device);
अटल पूर्णांक ppc4xx_edac_हटाओ(काष्ठा platक्रमm_device *device);

/* Global Variables */

/*
 * Device tree node type and compatible tuples this driver can match
 * on.
 */
अटल स्थिर काष्ठा of_device_id ppc4xx_edac_match[] = अणु
	अणु
		.compatible	= "ibm,sdram-4xx-ddr2"
	पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, ppc4xx_edac_match);

अटल काष्ठा platक्रमm_driver ppc4xx_edac_driver = अणु
	.probe			= ppc4xx_edac_probe,
	.हटाओ			= ppc4xx_edac_हटाओ,
	.driver = अणु
		.name = PPC4XX_EDAC_MODULE_NAME,
		.of_match_table = ppc4xx_edac_match,
	पूर्ण,
पूर्ण;

/*
 * TODO: The row and channel parameters likely need to be dynamically
 * set based on the aक्रमementioned variant controller realizations.
 */
अटल स्थिर अचिन्हित ppc4xx_edac_nr_csrows = 2;
अटल स्थिर अचिन्हित ppc4xx_edac_nr_chans = 1;

/*
 * Strings associated with PLB master IDs capable of being posted in
 * SDRAM_BESR or SDRAM_WMIRQ on uncorrectable ECC errors.
 */
अटल स्थिर अक्षर * स्थिर ppc4xx_plb_masters[9] = अणु
	[SDRAM_PLB_M0ID_ICU]	= "ICU",
	[SDRAM_PLB_M0ID_PCIE0]	= "PCI-E 0",
	[SDRAM_PLB_M0ID_PCIE1]	= "PCI-E 1",
	[SDRAM_PLB_M0ID_DMA]	= "DMA",
	[SDRAM_PLB_M0ID_DCU]	= "DCU",
	[SDRAM_PLB_M0ID_OPB]	= "OPB",
	[SDRAM_PLB_M0ID_MAL]	= "MAL",
	[SDRAM_PLB_M0ID_SEC]	= "SEC",
	[SDRAM_PLB_M0ID_AHB]	= "AHB"
पूर्ण;

/**
 * mfsdram - पढ़ो and वापस controller रेजिस्टर data
 * @dcr_host: A poपूर्णांकer to the DCR mapping.
 * @idcr_n: The indirect DCR रेजिस्टर to पढ़ो.
 *
 * This routine पढ़ोs and वापसs the data associated with the
 * controller's specअगरied indirect DCR रेजिस्टर.
 *
 * Returns the पढ़ो data.
 */
अटल अंतरभूत u32
mfsdram(स्थिर dcr_host_t *dcr_host, अचिन्हित पूर्णांक idcr_n)
अणु
	वापस __mfdcri(dcr_host->base + SDRAM_DCR_ADDR_OFFSET,
			dcr_host->base + SDRAM_DCR_DATA_OFFSET,
			idcr_n);
पूर्ण

/**
 * mtsdram - ग_लिखो controller रेजिस्टर data
 * @dcr_host: A poपूर्णांकer to the DCR mapping.
 * @idcr_n: The indirect DCR रेजिस्टर to ग_लिखो.
 * @value: The data to ग_लिखो.
 *
 * This routine ग_लिखोs the provided data to the controller's specअगरied
 * indirect DCR रेजिस्टर.
 */
अटल अंतरभूत व्योम
mtsdram(स्थिर dcr_host_t *dcr_host, अचिन्हित पूर्णांक idcr_n, u32 value)
अणु
	वापस __mtdcri(dcr_host->base + SDRAM_DCR_ADDR_OFFSET,
			dcr_host->base + SDRAM_DCR_DATA_OFFSET,
			idcr_n,
			value);
पूर्ण

/**
 * ppc4xx_edac_check_bank_error - check a bank क्रम an ECC bank error
 * @status: A poपूर्णांकer to the ECC status काष्ठाure to check क्रम an
 *          ECC bank error.
 * @bank: The bank to check क्रम an ECC error.
 *
 * This routine determines whether the specअगरied bank has an ECC
 * error.
 *
 * Returns true अगर the specअगरied bank has an ECC error; otherwise,
 * false.
 */
अटल bool
ppc4xx_edac_check_bank_error(स्थिर काष्ठा ppc4xx_ecc_status *status,
			     अचिन्हित पूर्णांक bank)
अणु
	चयन (bank) अणु
	हाल 0:
		वापस status->ecces & SDRAM_ECCES_BK0ER;
	हाल 1:
		वापस status->ecces & SDRAM_ECCES_BK1ER;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

/**
 * ppc4xx_edac_generate_bank_message - generate पूर्णांकerpretted bank status message
 * @mci: A poपूर्णांकer to the EDAC memory controller instance associated
 *       with the bank message being generated.
 * @status: A poपूर्णांकer to the ECC status काष्ठाure to generate the
 *          message from.
 * @buffer: A poपूर्णांकer to the buffer in which to generate the
 *          message.
 * @size: The size, in bytes, of space available in buffer.
 *
 * This routine generates to the provided buffer the portion of the
 * driver-unique report message associated with the ECCESS[BKNER]
 * field of the specअगरied ECC status.
 *
 * Returns the number of अक्षरacters generated on success; otherwise, <
 * 0 on error.
 */
अटल पूर्णांक
ppc4xx_edac_generate_bank_message(स्थिर काष्ठा mem_ctl_info *mci,
				  स्थिर काष्ठा ppc4xx_ecc_status *status,
				  अक्षर *buffer,
				  माप_प्रकार size)
अणु
	पूर्णांक n, total = 0;
	अचिन्हित पूर्णांक row, rows;

	n = snम_लिखो(buffer, size, "%s: Banks: ", mci->dev_name);

	अगर (n < 0 || n >= size)
		जाओ fail;

	buffer += n;
	size -= n;
	total += n;

	क्रम (rows = 0, row = 0; row < mci->nr_csrows; row++) अणु
		अगर (ppc4xx_edac_check_bank_error(status, row)) अणु
			n = snम_लिखो(buffer, size, "%s%u",
					(rows++ ? ", " : ""), row);

			अगर (n < 0 || n >= size)
				जाओ fail;

			buffer += n;
			size -= n;
			total += n;
		पूर्ण
	पूर्ण

	n = snम_लिखो(buffer, size, "%s; ", rows ? "" : "None");

	अगर (n < 0 || n >= size)
		जाओ fail;

	buffer += n;
	size -= n;
	total += n;

 fail:
	वापस total;
पूर्ण

/**
 * ppc4xx_edac_generate_checkbit_message - generate पूर्णांकerpretted checkbit message
 * @mci: A poपूर्णांकer to the EDAC memory controller instance associated
 *       with the checkbit message being generated.
 * @status: A poपूर्णांकer to the ECC status काष्ठाure to generate the
 *          message from.
 * @buffer: A poपूर्णांकer to the buffer in which to generate the
 *          message.
 * @size: The size, in bytes, of space available in buffer.
 *
 * This routine generates to the provided buffer the portion of the
 * driver-unique report message associated with the ECCESS[CKBER]
 * field of the specअगरied ECC status.
 *
 * Returns the number of अक्षरacters generated on success; otherwise, <
 * 0 on error.
 */
अटल पूर्णांक
ppc4xx_edac_generate_checkbit_message(स्थिर काष्ठा mem_ctl_info *mci,
				      स्थिर काष्ठा ppc4xx_ecc_status *status,
				      अक्षर *buffer,
				      माप_प्रकार size)
अणु
	स्थिर काष्ठा ppc4xx_edac_pdata *pdata = mci->pvt_info;
	स्थिर अक्षर *ckber = शून्य;

	चयन (status->ecces & SDRAM_ECCES_CKBER_MASK) अणु
	हाल SDRAM_ECCES_CKBER_NONE:
		ckber = "None";
		अवरोध;
	हाल SDRAM_ECCES_CKBER_32_ECC_0_3:
		ckber = "ECC0:3";
		अवरोध;
	हाल SDRAM_ECCES_CKBER_32_ECC_4_8:
		चयन (mfsdram(&pdata->dcr_host, SDRAM_MCOPT1) &
			SDRAM_MCOPT1_WDTH_MASK) अणु
		हाल SDRAM_MCOPT1_WDTH_16:
			ckber = "ECC0:3";
			अवरोध;
		हाल SDRAM_MCOPT1_WDTH_32:
			ckber = "ECC4:8";
			अवरोध;
		शेष:
			ckber = "Unknown";
			अवरोध;
		पूर्ण
		अवरोध;
	हाल SDRAM_ECCES_CKBER_32_ECC_0_8:
		ckber = "ECC0:8";
		अवरोध;
	शेष:
		ckber = "Unknown";
		अवरोध;
	पूर्ण

	वापस snम_लिखो(buffer, size, "Checkbit Error: %s", ckber);
पूर्ण

/**
 * ppc4xx_edac_generate_lane_message - generate पूर्णांकerpretted byte lane message
 * @mci: A poपूर्णांकer to the EDAC memory controller instance associated
 *       with the byte lane message being generated.
 * @status: A poपूर्णांकer to the ECC status काष्ठाure to generate the
 *          message from.
 * @buffer: A poपूर्णांकer to the buffer in which to generate the
 *          message.
 * @size: The size, in bytes, of space available in buffer.
 *
 * This routine generates to the provided buffer the portion of the
 * driver-unique report message associated with the ECCESS[BNCE]
 * field of the specअगरied ECC status.
 *
 * Returns the number of अक्षरacters generated on success; otherwise, <
 * 0 on error.
 */
अटल पूर्णांक
ppc4xx_edac_generate_lane_message(स्थिर काष्ठा mem_ctl_info *mci,
				  स्थिर काष्ठा ppc4xx_ecc_status *status,
				  अक्षर *buffer,
				  माप_प्रकार size)
अणु
	पूर्णांक n, total = 0;
	अचिन्हित पूर्णांक lane, lanes;
	स्थिर अचिन्हित पूर्णांक first_lane = 0;
	स्थिर अचिन्हित पूर्णांक lane_count = 16;

	n = snम_लिखो(buffer, size, "; Byte Lane Errors: ");

	अगर (n < 0 || n >= size)
		जाओ fail;

	buffer += n;
	size -= n;
	total += n;

	क्रम (lanes = 0, lane = first_lane; lane < lane_count; lane++) अणु
		अगर ((status->ecces & SDRAM_ECCES_BNCE_ENCODE(lane)) != 0) अणु
			n = snम_लिखो(buffer, size,
				     "%s%u",
				     (lanes++ ? ", " : ""), lane);

			अगर (n < 0 || n >= size)
				जाओ fail;

			buffer += n;
			size -= n;
			total += n;
		पूर्ण
	पूर्ण

	n = snम_लिखो(buffer, size, "%s; ", lanes ? "" : "None");

	अगर (n < 0 || n >= size)
		जाओ fail;

	buffer += n;
	size -= n;
	total += n;

 fail:
	वापस total;
पूर्ण

/**
 * ppc4xx_edac_generate_ecc_message - generate पूर्णांकerpretted ECC status message
 * @mci: A poपूर्णांकer to the EDAC memory controller instance associated
 *       with the ECCES message being generated.
 * @status: A poपूर्णांकer to the ECC status काष्ठाure to generate the
 *          message from.
 * @buffer: A poपूर्णांकer to the buffer in which to generate the
 *          message.
 * @size: The size, in bytes, of space available in buffer.
 *
 * This routine generates to the provided buffer the portion of the
 * driver-unique report message associated with the ECCESS रेजिस्टर of
 * the specअगरied ECC status.
 *
 * Returns the number of अक्षरacters generated on success; otherwise, <
 * 0 on error.
 */
अटल पूर्णांक
ppc4xx_edac_generate_ecc_message(स्थिर काष्ठा mem_ctl_info *mci,
				 स्थिर काष्ठा ppc4xx_ecc_status *status,
				 अक्षर *buffer,
				 माप_प्रकार size)
अणु
	पूर्णांक n, total = 0;

	n = ppc4xx_edac_generate_bank_message(mci, status, buffer, size);

	अगर (n < 0 || n >= size)
		जाओ fail;

	buffer += n;
	size -= n;
	total += n;

	n = ppc4xx_edac_generate_checkbit_message(mci, status, buffer, size);

	अगर (n < 0 || n >= size)
		जाओ fail;

	buffer += n;
	size -= n;
	total += n;

	n = ppc4xx_edac_generate_lane_message(mci, status, buffer, size);

	अगर (n < 0 || n >= size)
		जाओ fail;

	buffer += n;
	size -= n;
	total += n;

 fail:
	वापस total;
पूर्ण

/**
 * ppc4xx_edac_generate_plb_message - generate पूर्णांकerpretted PLB status message
 * @mci: A poपूर्णांकer to the EDAC memory controller instance associated
 *       with the PLB message being generated.
 * @status: A poपूर्णांकer to the ECC status काष्ठाure to generate the
 *          message from.
 * @buffer: A poपूर्णांकer to the buffer in which to generate the
 *          message.
 * @size: The size, in bytes, of space available in buffer.
 *
 * This routine generates to the provided buffer the portion of the
 * driver-unique report message associated with the PLB-related BESR
 * and/or WMIRQ रेजिस्टरs of the specअगरied ECC status.
 *
 * Returns the number of अक्षरacters generated on success; otherwise, <
 * 0 on error.
 */
अटल पूर्णांक
ppc4xx_edac_generate_plb_message(स्थिर काष्ठा mem_ctl_info *mci,
				 स्थिर काष्ठा ppc4xx_ecc_status *status,
				 अक्षर *buffer,
				 माप_प्रकार size)
अणु
	अचिन्हित पूर्णांक master;
	bool पढ़ो;

	अगर ((status->besr & SDRAM_BESR_MASK) == 0)
		वापस 0;

	अगर ((status->besr & SDRAM_BESR_M0ET_MASK) == SDRAM_BESR_M0ET_NONE)
		वापस 0;

	पढ़ो = ((status->besr & SDRAM_BESR_M0RW_MASK) == SDRAM_BESR_M0RW_READ);

	master = SDRAM_BESR_M0ID_DECODE(status->besr);

	वापस snम_लिखो(buffer, size,
			"%s error w/ PLB master %u \"%s\"; ",
			(पढ़ो ? "Read" : "Write"),
			master,
			(((master >= SDRAM_PLB_M0ID_FIRST) &&
			  (master <= SDRAM_PLB_M0ID_LAST)) ?
			 ppc4xx_plb_masters[master] : "UNKNOWN"));
पूर्ण

/**
 * ppc4xx_edac_generate_message - generate पूर्णांकerpretted status message
 * @mci: A poपूर्णांकer to the EDAC memory controller instance associated
 *       with the driver-unique message being generated.
 * @status: A poपूर्णांकer to the ECC status काष्ठाure to generate the
 *          message from.
 * @buffer: A poपूर्णांकer to the buffer in which to generate the
 *          message.
 * @size: The size, in bytes, of space available in buffer.
 *
 * This routine generates to the provided buffer the driver-unique
 * EDAC report message from the specअगरied ECC status.
 */
अटल व्योम
ppc4xx_edac_generate_message(स्थिर काष्ठा mem_ctl_info *mci,
			     स्थिर काष्ठा ppc4xx_ecc_status *status,
			     अक्षर *buffer,
			     माप_प्रकार size)
अणु
	पूर्णांक n;

	अगर (buffer == शून्य || size == 0)
		वापस;

	n = ppc4xx_edac_generate_ecc_message(mci, status, buffer, size);

	अगर (n < 0 || n >= size)
		वापस;

	buffer += n;
	size -= n;

	ppc4xx_edac_generate_plb_message(mci, status, buffer, size);
पूर्ण

#अगर_घोषित DEBUG
/**
 * ppc4xx_ecc_dump_status - dump controller ECC status रेजिस्टरs
 * @mci: A poपूर्णांकer to the EDAC memory controller instance
 *       associated with the status being dumped.
 * @status: A poपूर्णांकer to the ECC status काष्ठाure to generate the
 *          dump from.
 *
 * This routine dumps to the kernel log buffer the raw and
 * पूर्णांकerpretted specअगरied ECC status.
 */
अटल व्योम
ppc4xx_ecc_dump_status(स्थिर काष्ठा mem_ctl_info *mci,
		       स्थिर काष्ठा ppc4xx_ecc_status *status)
अणु
	अक्षर message[PPC4XX_EDAC_MESSAGE_SIZE];

	ppc4xx_edac_generate_message(mci, status, message, माप(message));

	ppc4xx_edac_mc_prपूर्णांकk(KERN_INFO, mci,
			      "\n"
			      "\tECCES: 0x%08x\n"
			      "\tWMIRQ: 0x%08x\n"
			      "\tBESR:  0x%08x\n"
			      "\tBEAR:  0x%08x%08x\n"
			      "\t%s\n",
			      status->ecces,
			      status->wmirq,
			      status->besr,
			      status->bearh,
			      status->bearl,
			      message);
पूर्ण
#पूर्ण_अगर /* DEBUG */

/**
 * ppc4xx_ecc_get_status - get controller ECC status
 * @mci: A poपूर्णांकer to the EDAC memory controller instance
 *       associated with the status being retrieved.
 * @status: A poपूर्णांकer to the ECC status काष्ठाure to populate the
 *          ECC status with.
 *
 * This routine पढ़ोs and masks, as appropriate, all the relevant
 * status रेजिस्टरs that deal with ibm,sdram-4xx-ddr2 ECC errors.
 * While we पढ़ो all of them, क्रम correctable errors, we only expect
 * to deal with ECCES. For uncorrectable errors, we expect to deal
 * with all of them.
 */
अटल व्योम
ppc4xx_ecc_get_status(स्थिर काष्ठा mem_ctl_info *mci,
		      काष्ठा ppc4xx_ecc_status *status)
अणु
	स्थिर काष्ठा ppc4xx_edac_pdata *pdata = mci->pvt_info;
	स्थिर dcr_host_t *dcr_host = &pdata->dcr_host;

	status->ecces = mfsdram(dcr_host, SDRAM_ECCES) & SDRAM_ECCES_MASK;
	status->wmirq = mfsdram(dcr_host, SDRAM_WMIRQ) & SDRAM_WMIRQ_MASK;
	status->besr  = mfsdram(dcr_host, SDRAM_BESR)  & SDRAM_BESR_MASK;
	status->bearl = mfsdram(dcr_host, SDRAM_BEARL);
	status->bearh = mfsdram(dcr_host, SDRAM_BEARH);
पूर्ण

/**
 * ppc4xx_ecc_clear_status - clear controller ECC status
 * @mci: A poपूर्णांकer to the EDAC memory controller instance
 *       associated with the status being cleared.
 * @status: A poपूर्णांकer to the ECC status काष्ठाure containing the
 *          values to ग_लिखो to clear the ECC status.
 *
 * This routine clears--by writing the masked (as appropriate) status
 * values back to--the status रेजिस्टरs that deal with
 * ibm,sdram-4xx-ddr2 ECC errors.
 */
अटल व्योम
ppc4xx_ecc_clear_status(स्थिर काष्ठा mem_ctl_info *mci,
			स्थिर काष्ठा ppc4xx_ecc_status *status)
अणु
	स्थिर काष्ठा ppc4xx_edac_pdata *pdata = mci->pvt_info;
	स्थिर dcr_host_t *dcr_host = &pdata->dcr_host;

	mtsdram(dcr_host, SDRAM_ECCES,	status->ecces & SDRAM_ECCES_MASK);
	mtsdram(dcr_host, SDRAM_WMIRQ,	status->wmirq & SDRAM_WMIRQ_MASK);
	mtsdram(dcr_host, SDRAM_BESR,	status->besr & SDRAM_BESR_MASK);
	mtsdram(dcr_host, SDRAM_BEARL,	0);
	mtsdram(dcr_host, SDRAM_BEARH,	0);
पूर्ण

/**
 * ppc4xx_edac_handle_ce - handle controller correctable ECC error (CE)
 * @mci: A poपूर्णांकer to the EDAC memory controller instance
 *       associated with the correctable error being handled and reported.
 * @status: A poपूर्णांकer to the ECC status काष्ठाure associated with
 *          the correctable error being handled and reported.
 *
 * This routine handles an ibm,sdram-4xx-ddr2 controller ECC
 * correctable error. Per the aक्रमementioned discussion, there's not
 * enough status available to use the full EDAC correctable error
 * पूर्णांकerface, so we just pass driver-unique message to the "no info"
 * पूर्णांकerface.
 */
अटल व्योम
ppc4xx_edac_handle_ce(काष्ठा mem_ctl_info *mci,
		      स्थिर काष्ठा ppc4xx_ecc_status *status)
अणु
	पूर्णांक row;
	अक्षर message[PPC4XX_EDAC_MESSAGE_SIZE];

	ppc4xx_edac_generate_message(mci, status, message, माप(message));

	क्रम (row = 0; row < mci->nr_csrows; row++)
		अगर (ppc4xx_edac_check_bank_error(status, row))
			edac_mc_handle_error(HW_EVENT_ERR_CORRECTED, mci, 1,
					     0, 0, 0,
					     row, 0, -1,
					     message, "");
पूर्ण

/**
 * ppc4xx_edac_handle_ue - handle controller uncorrectable ECC error (UE)
 * @mci: A poपूर्णांकer to the EDAC memory controller instance
 *       associated with the uncorrectable error being handled and
 *       reported.
 * @status: A poपूर्णांकer to the ECC status काष्ठाure associated with
 *          the uncorrectable error being handled and reported.
 *
 * This routine handles an ibm,sdram-4xx-ddr2 controller ECC
 * uncorrectable error.
 */
अटल व्योम
ppc4xx_edac_handle_ue(काष्ठा mem_ctl_info *mci,
		      स्थिर काष्ठा ppc4xx_ecc_status *status)
अणु
	स्थिर u64 bear = ((u64)status->bearh << 32 | status->bearl);
	स्थिर अचिन्हित दीर्घ page = bear >> PAGE_SHIFT;
	स्थिर अचिन्हित दीर्घ offset = bear & ~PAGE_MASK;
	पूर्णांक row;
	अक्षर message[PPC4XX_EDAC_MESSAGE_SIZE];

	ppc4xx_edac_generate_message(mci, status, message, माप(message));

	क्रम (row = 0; row < mci->nr_csrows; row++)
		अगर (ppc4xx_edac_check_bank_error(status, row))
			edac_mc_handle_error(HW_EVENT_ERR_UNCORRECTED, mci, 1,
					     page, offset, 0,
					     row, 0, -1,
					     message, "");
पूर्ण

/**
 * ppc4xx_edac_check - check controller क्रम ECC errors
 * @mci: A poपूर्णांकer to the EDAC memory controller instance
 *       associated with the ibm,sdram-4xx-ddr2 controller being
 *       checked.
 *
 * This routine is used to check and post ECC errors and is called by
 * both the EDAC polling thपढ़ो and this driver's CE and UE पूर्णांकerrupt
 * handler.
 */
अटल व्योम
ppc4xx_edac_check(काष्ठा mem_ctl_info *mci)
अणु
#अगर_घोषित DEBUG
	अटल अचिन्हित पूर्णांक count;
#पूर्ण_अगर
	काष्ठा ppc4xx_ecc_status status;

	ppc4xx_ecc_get_status(mci, &status);

#अगर_घोषित DEBUG
	अगर (count++ % 30 == 0)
		ppc4xx_ecc_dump_status(mci, &status);
#पूर्ण_अगर

	अगर (status.ecces & SDRAM_ECCES_UE)
		ppc4xx_edac_handle_ue(mci, &status);

	अगर (status.ecces & SDRAM_ECCES_CE)
		ppc4xx_edac_handle_ce(mci, &status);

	ppc4xx_ecc_clear_status(mci, &status);
पूर्ण

/**
 * ppc4xx_edac_isr - SEC (CE) and DED (UE) पूर्णांकerrupt service routine
 * @irq:    The भव पूर्णांकerrupt number being serviced.
 * @dev_id: A poपूर्णांकer to the EDAC memory controller instance
 *          associated with the पूर्णांकerrupt being handled.
 *
 * This routine implements the पूर्णांकerrupt handler क्रम both correctable
 * (CE) and uncorrectable (UE) ECC errors क्रम the ibm,sdram-4xx-ddr2
 * controller. It simply calls through to the same routine used during
 * polling to check, report and clear the ECC status.
 *
 * Unconditionally वापसs IRQ_HANDLED.
 */
अटल irqवापस_t
ppc4xx_edac_isr(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा mem_ctl_info *mci = dev_id;

	ppc4xx_edac_check(mci);

	वापस IRQ_HANDLED;
पूर्ण

/**
 * ppc4xx_edac_get_dtype - वापस the controller memory width
 * @mcopt1: The 32-bit Memory Controller Option 1 रेजिस्टर value
 *          currently set क्रम the controller, from which the width
 *          is derived.
 *
 * This routine वापसs the EDAC device type width appropriate क्रम the
 * current controller configuration.
 *
 * TODO: This needs to be conditioned dynamically through feature
 * flags or some such when other controller variants are supported as
 * the 405EX[r] is 16-/32-bit and the others are 32-/64-bit with the
 * 16- and 64-bit field definition/value/क्रमागतeration (b1) overloaded
 * among them.
 *
 * Returns a device type width क्रमागतeration.
 */
अटल क्रमागत dev_type ppc4xx_edac_get_dtype(u32 mcopt1)
अणु
	चयन (mcopt1 & SDRAM_MCOPT1_WDTH_MASK) अणु
	हाल SDRAM_MCOPT1_WDTH_16:
		वापस DEV_X2;
	हाल SDRAM_MCOPT1_WDTH_32:
		वापस DEV_X4;
	शेष:
		वापस DEV_UNKNOWN;
	पूर्ण
पूर्ण

/**
 * ppc4xx_edac_get_mtype - वापस controller memory type
 * @mcopt1: The 32-bit Memory Controller Option 1 रेजिस्टर value
 *          currently set क्रम the controller, from which the memory type
 *          is derived.
 *
 * This routine वापसs the EDAC memory type appropriate क्रम the
 * current controller configuration.
 *
 * Returns a memory type क्रमागतeration.
 */
अटल क्रमागत mem_type ppc4xx_edac_get_mtype(u32 mcopt1)
अणु
	bool rden = ((mcopt1 & SDRAM_MCOPT1_RDEN_MASK) == SDRAM_MCOPT1_RDEN);

	चयन (mcopt1 & SDRAM_MCOPT1_DDR_TYPE_MASK) अणु
	हाल SDRAM_MCOPT1_DDR2_TYPE:
		वापस rden ? MEM_RDDR2 : MEM_DDR2;
	हाल SDRAM_MCOPT1_DDR1_TYPE:
		वापस rden ? MEM_RDDR : MEM_DDR;
	शेष:
		वापस MEM_UNKNOWN;
	पूर्ण
पूर्ण

/**
 * ppc4xx_edac_init_csrows - initialize driver instance rows
 * @mci: A poपूर्णांकer to the EDAC memory controller instance
 *       associated with the ibm,sdram-4xx-ddr2 controller क्रम which
 *       the csrows (i.e. banks/ranks) are being initialized.
 * @mcopt1: The 32-bit Memory Controller Option 1 रेजिस्टर value
 *          currently set क्रम the controller, from which bank width
 *          and memory typ inक्रमmation is derived.
 *
 * This routine initializes the भव "chip select rows" associated
 * with the EDAC memory controller instance. An ibm,sdram-4xx-ddr2
 * controller bank/rank is mapped to a row.
 *
 * Returns 0 अगर OK; otherwise, -EINVAL अगर the memory bank size
 * configuration cannot be determined.
 */
अटल पूर्णांक ppc4xx_edac_init_csrows(काष्ठा mem_ctl_info *mci, u32 mcopt1)
अणु
	स्थिर काष्ठा ppc4xx_edac_pdata *pdata = mci->pvt_info;
	पूर्णांक status = 0;
	क्रमागत mem_type mtype;
	क्रमागत dev_type dtype;
	क्रमागत edac_type edac_mode;
	पूर्णांक row, j;
	u32 mbxcf, size, nr_pages;

	/* Establish the memory type and width */

	mtype = ppc4xx_edac_get_mtype(mcopt1);
	dtype = ppc4xx_edac_get_dtype(mcopt1);

	/* Establish EDAC mode */

	अगर (mci->edac_cap & EDAC_FLAG_SECDED)
		edac_mode = EDAC_SECDED;
	अन्यथा अगर (mci->edac_cap & EDAC_FLAG_EC)
		edac_mode = EDAC_EC;
	अन्यथा
		edac_mode = EDAC_NONE;

	/*
	 * Initialize each chip select row काष्ठाure which correspond
	 * 1:1 with a controller bank/rank.
	 */

	क्रम (row = 0; row < mci->nr_csrows; row++) अणु
		काष्ठा csrow_info *csi = mci->csrows[row];

		/*
		 * Get the configuration settings क्रम this
		 * row/bank/rank and skip disabled banks.
		 */

		mbxcf = mfsdram(&pdata->dcr_host, SDRAM_MBXCF(row));

		अगर ((mbxcf & SDRAM_MBCF_BE_MASK) != SDRAM_MBCF_BE_ENABLE)
			जारी;

		/* Map the bank configuration size setting to pages. */

		size = mbxcf & SDRAM_MBCF_SZ_MASK;

		चयन (size) अणु
		हाल SDRAM_MBCF_SZ_4MB:
		हाल SDRAM_MBCF_SZ_8MB:
		हाल SDRAM_MBCF_SZ_16MB:
		हाल SDRAM_MBCF_SZ_32MB:
		हाल SDRAM_MBCF_SZ_64MB:
		हाल SDRAM_MBCF_SZ_128MB:
		हाल SDRAM_MBCF_SZ_256MB:
		हाल SDRAM_MBCF_SZ_512MB:
		हाल SDRAM_MBCF_SZ_1GB:
		हाल SDRAM_MBCF_SZ_2GB:
		हाल SDRAM_MBCF_SZ_4GB:
		हाल SDRAM_MBCF_SZ_8GB:
			nr_pages = SDRAM_MBCF_SZ_TO_PAGES(size);
			अवरोध;
		शेष:
			ppc4xx_edac_mc_prपूर्णांकk(KERN_ERR, mci,
					      "Unrecognized memory bank %d "
					      "size 0x%08x\n",
					      row, SDRAM_MBCF_SZ_DECODE(size));
			status = -EINVAL;
			जाओ करोne;
		पूर्ण

		/*
		 * It's unclear exactly what grain should be set to
		 * here. The SDRAM_ECCES रेजिस्टर allows resolution of
		 * an error करोwn to a nibble which would potentially
		 * argue क्रम a grain of '1' byte, even though we only
		 * know the associated address क्रम uncorrectable
		 * errors. This value is not used at present क्रम
		 * anything other than error reporting so getting it
		 * wrong should be of little consequence. Other
		 * possible values would be the PLB width (16), the
		 * page size (PAGE_SIZE) or the memory width (2 or 4).
		 */
		क्रम (j = 0; j < csi->nr_channels; j++) अणु
			काष्ठा dimm_info *dimm = csi->channels[j]->dimm;

			dimm->nr_pages  = nr_pages / csi->nr_channels;
			dimm->grain	= 1;

			dimm->mtype	= mtype;
			dimm->dtype	= dtype;

			dimm->edac_mode	= edac_mode;
		पूर्ण
	पूर्ण

 करोne:
	वापस status;
पूर्ण

/**
 * ppc4xx_edac_mc_init - initialize driver instance
 * @mci: A poपूर्णांकer to the EDAC memory controller instance being
 *       initialized.
 * @op: A poपूर्णांकer to the OpenFirmware device tree node associated
 *      with the controller this EDAC instance is bound to.
 * @dcr_host: A poपूर्णांकer to the DCR data containing the DCR mapping
 *            क्रम this controller instance.
 * @mcopt1: The 32-bit Memory Controller Option 1 रेजिस्टर value
 *          currently set क्रम the controller, from which ECC capabilities
 *          and scrub mode are derived.
 *
 * This routine perक्रमms initialization of the EDAC memory controller
 * instance and related driver-निजी data associated with the
 * ibm,sdram-4xx-ddr2 memory controller the instance is bound to.
 *
 * Returns 0 अगर OK; otherwise, < 0 on error.
 */
अटल पूर्णांक ppc4xx_edac_mc_init(काष्ठा mem_ctl_info *mci,
			       काष्ठा platक्रमm_device *op,
			       स्थिर dcr_host_t *dcr_host, u32 mcopt1)
अणु
	पूर्णांक status = 0;
	स्थिर u32 memcheck = (mcopt1 & SDRAM_MCOPT1_MCHK_MASK);
	काष्ठा ppc4xx_edac_pdata *pdata = शून्य;
	स्थिर काष्ठा device_node *np = op->dev.of_node;

	अगर (of_match_device(ppc4xx_edac_match, &op->dev) == शून्य)
		वापस -EINVAL;

	/* Initial driver poपूर्णांकers and निजी data */

	mci->pdev		= &op->dev;

	dev_set_drvdata(mci->pdev, mci);

	pdata			= mci->pvt_info;

	pdata->dcr_host		= *dcr_host;

	/* Initialize controller capabilities and configuration */

	mci->mtype_cap		= (MEM_FLAG_DDR | MEM_FLAG_RDDR |
				   MEM_FLAG_DDR2 | MEM_FLAG_RDDR2);

	mci->edac_ctl_cap	= (EDAC_FLAG_NONE |
				   EDAC_FLAG_EC |
				   EDAC_FLAG_SECDED);

	mci->scrub_cap		= SCRUB_NONE;
	mci->scrub_mode		= SCRUB_NONE;

	/*
	 * Update the actual capabilites based on the MCOPT1[MCHK]
	 * settings. Scrubbing is only useful अगर reporting is enabled.
	 */

	चयन (memcheck) अणु
	हाल SDRAM_MCOPT1_MCHK_CHK:
		mci->edac_cap	= EDAC_FLAG_EC;
		अवरोध;
	हाल SDRAM_MCOPT1_MCHK_CHK_REP:
		mci->edac_cap	= (EDAC_FLAG_EC | EDAC_FLAG_SECDED);
		mci->scrub_mode	= SCRUB_SW_SRC;
		अवरोध;
	शेष:
		mci->edac_cap	= EDAC_FLAG_NONE;
		अवरोध;
	पूर्ण

	/* Initialize strings */

	mci->mod_name		= PPC4XX_EDAC_MODULE_NAME;
	mci->ctl_name		= ppc4xx_edac_match->compatible;
	mci->dev_name		= np->full_name;

	/* Initialize callbacks */

	mci->edac_check		= ppc4xx_edac_check;
	mci->ctl_page_to_phys	= शून्य;

	/* Initialize chip select rows */

	status = ppc4xx_edac_init_csrows(mci, mcopt1);

	अगर (status)
		ppc4xx_edac_mc_prपूर्णांकk(KERN_ERR, mci,
				      "Failed to initialize rows!\n");

	वापस status;
पूर्ण

/**
 * ppc4xx_edac_रेजिस्टर_irq - setup and रेजिस्टर controller पूर्णांकerrupts
 * @op: A poपूर्णांकer to the OpenFirmware device tree node associated
 *      with the controller this EDAC instance is bound to.
 * @mci: A poपूर्णांकer to the EDAC memory controller instance
 *       associated with the ibm,sdram-4xx-ddr2 controller क्रम which
 *       पूर्णांकerrupts are being रेजिस्टरed.
 *
 * This routine parses the correctable (CE) and uncorrectable error (UE)
 * पूर्णांकerrupts from the device tree node and maps and assigns them to
 * the associated EDAC memory controller instance.
 *
 * Returns 0 अगर OK; otherwise, -ENODEV अगर the पूर्णांकerrupts could not be
 * mapped and asचिन्हित.
 */
अटल पूर्णांक ppc4xx_edac_रेजिस्टर_irq(काष्ठा platक्रमm_device *op,
				    काष्ठा mem_ctl_info *mci)
अणु
	पूर्णांक status = 0;
	पूर्णांक ded_irq, sec_irq;
	काष्ठा ppc4xx_edac_pdata *pdata = mci->pvt_info;
	काष्ठा device_node *np = op->dev.of_node;

	ded_irq = irq_of_parse_and_map(np, INTMAP_ECCDED_INDEX);
	sec_irq = irq_of_parse_and_map(np, INTMAP_ECCSEC_INDEX);

	अगर (!ded_irq || !sec_irq) अणु
		ppc4xx_edac_mc_prपूर्णांकk(KERN_ERR, mci,
				      "Unable to map interrupts.\n");
		status = -ENODEV;
		जाओ fail;
	पूर्ण

	status = request_irq(ded_irq,
			     ppc4xx_edac_isr,
			     0,
			     "[EDAC] MC ECCDED",
			     mci);

	अगर (status < 0) अणु
		ppc4xx_edac_mc_prपूर्णांकk(KERN_ERR, mci,
				      "Unable to request irq %d for ECC DED",
				      ded_irq);
		status = -ENODEV;
		जाओ fail1;
	पूर्ण

	status = request_irq(sec_irq,
			     ppc4xx_edac_isr,
			     0,
			     "[EDAC] MC ECCSEC",
			     mci);

	अगर (status < 0) अणु
		ppc4xx_edac_mc_prपूर्णांकk(KERN_ERR, mci,
				      "Unable to request irq %d for ECC SEC",
				      sec_irq);
		status = -ENODEV;
		जाओ fail2;
	पूर्ण

	ppc4xx_edac_mc_prपूर्णांकk(KERN_INFO, mci, "ECCDED irq is %d\n", ded_irq);
	ppc4xx_edac_mc_prपूर्णांकk(KERN_INFO, mci, "ECCSEC irq is %d\n", sec_irq);

	pdata->irqs.ded = ded_irq;
	pdata->irqs.sec = sec_irq;

	वापस 0;

 fail2:
	मुक्त_irq(sec_irq, mci);

 fail1:
	मुक्त_irq(ded_irq, mci);

 fail:
	वापस status;
पूर्ण

/**
 * ppc4xx_edac_map_dcrs - locate and map controller रेजिस्टरs
 * @np: A poपूर्णांकer to the device tree node containing the DCR
 *      resources to map.
 * @dcr_host: A poपूर्णांकer to the DCR data to populate with the
 *            DCR mapping.
 *
 * This routine attempts to locate in the device tree and map the DCR
 * रेजिस्टर resources associated with the controller's indirect DCR
 * address and data winकरोws.
 *
 * Returns 0 अगर the DCRs were successfully mapped; otherwise, < 0 on
 * error.
 */
अटल पूर्णांक ppc4xx_edac_map_dcrs(स्थिर काष्ठा device_node *np,
				dcr_host_t *dcr_host)
अणु
	अचिन्हित पूर्णांक dcr_base, dcr_len;

	अगर (np == शून्य || dcr_host == शून्य)
		वापस -EINVAL;

	/* Get the DCR resource extent and sanity check the values. */

	dcr_base = dcr_resource_start(np, 0);
	dcr_len = dcr_resource_len(np, 0);

	अगर (dcr_base == 0 || dcr_len == 0) अणु
		ppc4xx_edac_prपूर्णांकk(KERN_ERR,
				   "Failed to obtain DCR property.\n");
		वापस -ENODEV;
	पूर्ण

	अगर (dcr_len != SDRAM_DCR_RESOURCE_LEN) अणु
		ppc4xx_edac_prपूर्णांकk(KERN_ERR,
				   "Unexpected DCR length %d, expected %d.\n",
				   dcr_len, SDRAM_DCR_RESOURCE_LEN);
		वापस -ENODEV;
	पूर्ण

	/*  Attempt to map the DCR extent. */

	*dcr_host = dcr_map(np, dcr_base, dcr_len);

	अगर (!DCR_MAP_OK(*dcr_host)) अणु
		ppc4xx_edac_prपूर्णांकk(KERN_INFO, "Failed to map DCRs.\n");
		    वापस -ENODEV;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * ppc4xx_edac_probe - check controller and bind driver
 * @op: A poपूर्णांकer to the OpenFirmware device tree node associated
 *      with the controller being probed क्रम driver binding.
 *
 * This routine probes a specअगरic ibm,sdram-4xx-ddr2 controller
 * instance क्रम binding with the driver.
 *
 * Returns 0 अगर the controller instance was successfully bound to the
 * driver; otherwise, < 0 on error.
 */
अटल पूर्णांक ppc4xx_edac_probe(काष्ठा platक्रमm_device *op)
अणु
	पूर्णांक status = 0;
	u32 mcopt1, memcheck;
	dcr_host_t dcr_host;
	स्थिर काष्ठा device_node *np = op->dev.of_node;
	काष्ठा mem_ctl_info *mci = शून्य;
	काष्ठा edac_mc_layer layers[2];
	अटल पूर्णांक ppc4xx_edac_instance;

	/*
	 * At this poपूर्णांक, we only support the controller realized on
	 * the AMCC PPC 405EX[r]. Reject anything अन्यथा.
	 */

	अगर (!of_device_is_compatible(np, "ibm,sdram-405ex") &&
	    !of_device_is_compatible(np, "ibm,sdram-405exr")) अणु
		ppc4xx_edac_prपूर्णांकk(KERN_NOTICE,
				   "Only the PPC405EX[r] is supported.\n");
		वापस -ENODEV;
	पूर्ण

	/*
	 * Next, get the DCR property and attempt to map it so that we
	 * can probe the controller.
	 */

	status = ppc4xx_edac_map_dcrs(np, &dcr_host);

	अगर (status)
		वापस status;

	/*
	 * First determine whether ECC is enabled at all. If not,
	 * there is no useful checking or monitoring that can be करोne
	 * क्रम this controller.
	 */

	mcopt1 = mfsdram(&dcr_host, SDRAM_MCOPT1);
	memcheck = (mcopt1 & SDRAM_MCOPT1_MCHK_MASK);

	अगर (memcheck == SDRAM_MCOPT1_MCHK_NON) अणु
		ppc4xx_edac_prपूर्णांकk(KERN_INFO, "%pOF: No ECC memory detected or "
				   "ECC is disabled.\n", np);
		status = -ENODEV;
		जाओ करोne;
	पूर्ण

	/*
	 * At this poपूर्णांक, we know ECC is enabled, allocate an EDAC
	 * controller instance and perक्रमm the appropriate
	 * initialization.
	 */
	layers[0].type = EDAC_MC_LAYER_CHIP_SELECT;
	layers[0].size = ppc4xx_edac_nr_csrows;
	layers[0].is_virt_csrow = true;
	layers[1].type = EDAC_MC_LAYER_CHANNEL;
	layers[1].size = ppc4xx_edac_nr_chans;
	layers[1].is_virt_csrow = false;
	mci = edac_mc_alloc(ppc4xx_edac_instance, ARRAY_SIZE(layers), layers,
			    माप(काष्ठा ppc4xx_edac_pdata));
	अगर (mci == शून्य) अणु
		ppc4xx_edac_prपूर्णांकk(KERN_ERR, "%pOF: "
				   "Failed to allocate EDAC MC instance!\n",
				   np);
		status = -ENOMEM;
		जाओ करोne;
	पूर्ण

	status = ppc4xx_edac_mc_init(mci, op, &dcr_host, mcopt1);

	अगर (status) अणु
		ppc4xx_edac_mc_prपूर्णांकk(KERN_ERR, mci,
				      "Failed to initialize instance!\n");
		जाओ fail;
	पूर्ण

	/*
	 * We have a valid, initialized EDAC instance bound to the
	 * controller. Attempt to रेजिस्टर it with the EDAC subप्रणाली
	 * and, अगर necessary, रेजिस्टर पूर्णांकerrupts.
	 */

	अगर (edac_mc_add_mc(mci)) अणु
		ppc4xx_edac_mc_prपूर्णांकk(KERN_ERR, mci,
				      "Failed to add instance!\n");
		status = -ENODEV;
		जाओ fail;
	पूर्ण

	अगर (edac_op_state == EDAC_OPSTATE_INT) अणु
		status = ppc4xx_edac_रेजिस्टर_irq(op, mci);

		अगर (status)
			जाओ fail1;
	पूर्ण

	ppc4xx_edac_instance++;

	वापस 0;

 fail1:
	edac_mc_del_mc(mci->pdev);

 fail:
	edac_mc_मुक्त(mci);

 करोne:
	वापस status;
पूर्ण

/**
 * ppc4xx_edac_हटाओ - unbind driver from controller
 * @op: A poपूर्णांकer to the OpenFirmware device tree node associated
 *      with the controller this EDAC instance is to be unbound/हटाओd
 *      from.
 *
 * This routine unbinds the EDAC memory controller instance associated
 * with the specअगरied ibm,sdram-4xx-ddr2 controller described by the
 * OpenFirmware device tree node passed as a parameter.
 *
 * Unconditionally वापसs 0.
 */
अटल पूर्णांक
ppc4xx_edac_हटाओ(काष्ठा platक्रमm_device *op)
अणु
	काष्ठा mem_ctl_info *mci = dev_get_drvdata(&op->dev);
	काष्ठा ppc4xx_edac_pdata *pdata = mci->pvt_info;

	अगर (edac_op_state == EDAC_OPSTATE_INT) अणु
		मुक्त_irq(pdata->irqs.sec, mci);
		मुक्त_irq(pdata->irqs.ded, mci);
	पूर्ण

	dcr_unmap(pdata->dcr_host, SDRAM_DCR_RESOURCE_LEN);

	edac_mc_del_mc(mci->pdev);
	edac_mc_मुक्त(mci);

	वापस 0;
पूर्ण

/**
 * ppc4xx_edac_opstate_init - initialize EDAC reporting method
 *
 * This routine ensures that the EDAC memory controller reporting
 * method is mapped to a sane value as the EDAC core defines the value
 * to EDAC_OPSTATE_INVAL by शेष. We करोn't call the global
 * opstate_init as that शेषs to polling and we want पूर्णांकerrupt as
 * the शेष.
 */
अटल अंतरभूत व्योम __init
ppc4xx_edac_opstate_init(व्योम)
अणु
	चयन (edac_op_state) अणु
	हाल EDAC_OPSTATE_POLL:
	हाल EDAC_OPSTATE_INT:
		अवरोध;
	शेष:
		edac_op_state = EDAC_OPSTATE_INT;
		अवरोध;
	पूर्ण

	ppc4xx_edac_prपूर्णांकk(KERN_INFO, "Reporting type: %s\n",
			   ((edac_op_state == EDAC_OPSTATE_POLL) ?
			    EDAC_OPSTATE_POLL_STR :
			    ((edac_op_state == EDAC_OPSTATE_INT) ?
			     EDAC_OPSTATE_INT_STR :
			     EDAC_OPSTATE_UNKNOWN_STR)));
पूर्ण

/**
 * ppc4xx_edac_init - driver/module insertion entry poपूर्णांक
 *
 * This routine is the driver/module insertion entry poपूर्णांक. It
 * initializes the EDAC memory controller reporting state and
 * रेजिस्टरs the driver as an OpenFirmware device tree platक्रमm
 * driver.
 */
अटल पूर्णांक __init
ppc4xx_edac_init(व्योम)
अणु
	ppc4xx_edac_prपूर्णांकk(KERN_INFO, PPC4XX_EDAC_MODULE_REVISION "\n");

	ppc4xx_edac_opstate_init();

	वापस platक्रमm_driver_रेजिस्टर(&ppc4xx_edac_driver);
पूर्ण

/**
 * ppc4xx_edac_निकास - driver/module removal entry poपूर्णांक
 *
 * This routine is the driver/module removal entry poपूर्णांक. It
 * unरेजिस्टरs the driver as an OpenFirmware device tree platक्रमm
 * driver.
 */
अटल व्योम __निकास
ppc4xx_edac_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&ppc4xx_edac_driver);
पूर्ण

module_init(ppc4xx_edac_init);
module_निकास(ppc4xx_edac_निकास);

MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Grant Erickson <gerickson@nuovations.com>");
MODULE_DESCRIPTION("EDAC MC Driver for the PPC4xx IBM DDR2 Memory Controller");
module_param(edac_op_state, पूर्णांक, 0444);
MODULE_PARM_DESC(edac_op_state, "EDAC Error Reporting State: "
		 "0=" EDAC_OPSTATE_POLL_STR ", 2=" EDAC_OPSTATE_INT_STR);
