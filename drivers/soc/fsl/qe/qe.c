<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2006-2010 Freescale Semiconductor, Inc. All rights reserved.
 *
 * Authors: 	Shlomi Gridish <gridish@मुक्तscale.com>
 * 		Li Yang <leoli@मुक्तscale.com>
 * Based on cpm2_common.c from Dan Malek (dmalek@jlc.net)
 *
 * Description:
 * General Purpose functions क्रम the global management of the
 * QUICC Engine (QE).
 */
#समावेश <linux/biपंचांगap.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/sched.h>
#समावेश <linux/kernel.h>
#समावेश <linux/param.h>
#समावेश <linux/माला.स>
#समावेश <linux/spinlock.h>
#समावेश <linux/mm.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/module.h>
#समावेश <linux/delay.h>
#समावेश <linux/ioport.h>
#समावेश <linux/iopoll.h>
#समावेश <linux/crc32.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <soc/fsl/qe/immap_qe.h>
#समावेश <soc/fsl/qe/qe.h>

अटल व्योम qe_snums_init(व्योम);
अटल पूर्णांक qe_sdma_init(व्योम);

अटल DEFINE_SPINLOCK(qe_lock);
DEFINE_SPINLOCK(cmxgcr_lock);
EXPORT_SYMBOL(cmxgcr_lock);

/* We allocate this here because it is used almost exclusively क्रम
 * the communication processor devices.
 */
काष्ठा qe_immap __iomem *qe_immr;
EXPORT_SYMBOL(qe_immr);

अटल u8 snums[QE_NUM_OF_SNUM];	/* Dynamically allocated SNUMs */
अटल DECLARE_BITMAP(snum_state, QE_NUM_OF_SNUM);
अटल अचिन्हित पूर्णांक qe_num_of_snum;

अटल phys_addr_t qebase = -1;

अटल काष्ठा device_node *qe_get_device_node(व्योम)
अणु
	काष्ठा device_node *qe;

	/*
	 * Newer device trees have an "fsl,qe" compatible property क्रम the QE
	 * node, but we still need to support older device trees.
	 */
	qe = of_find_compatible_node(शून्य, शून्य, "fsl,qe");
	अगर (qe)
		वापस qe;
	वापस of_find_node_by_type(शून्य, "qe");
पूर्ण

अटल phys_addr_t get_qe_base(व्योम)
अणु
	काष्ठा device_node *qe;
	पूर्णांक ret;
	काष्ठा resource res;

	अगर (qebase != -1)
		वापस qebase;

	qe = qe_get_device_node();
	अगर (!qe)
		वापस qebase;

	ret = of_address_to_resource(qe, 0, &res);
	अगर (!ret)
		qebase = res.start;
	of_node_put(qe);

	वापस qebase;
पूर्ण

व्योम qe_reset(व्योम)
अणु
	अगर (qe_immr == शून्य)
		qe_immr = ioremap(get_qe_base(), QE_IMMAP_SIZE);

	qe_snums_init();

	qe_issue_cmd(QE_RESET, QE_CR_SUBBLOCK_INVALID,
		     QE_CR_PROTOCOL_UNSPECIFIED, 0);

	/* Reclaim the MURAM memory क्रम our use. */
	qe_muram_init();

	अगर (qe_sdma_init())
		panic("sdma init failed!");
पूर्ण

पूर्णांक qe_issue_cmd(u32 cmd, u32 device, u8 mcn_protocol, u32 cmd_input)
अणु
	अचिन्हित दीर्घ flags;
	u8 mcn_shअगरt = 0, dev_shअगरt = 0;
	u32 val;
	पूर्णांक ret;

	spin_lock_irqsave(&qe_lock, flags);
	अगर (cmd == QE_RESET) अणु
		ioग_लिखो32be((u32)(cmd | QE_CR_FLG), &qe_immr->cp.cecr);
	पूर्ण अन्यथा अणु
		अगर (cmd == QE_ASSIGN_PAGE) अणु
			/* Here device is the SNUM, not sub-block */
			dev_shअगरt = QE_CR_SNUM_SHIFT;
		पूर्ण अन्यथा अगर (cmd == QE_ASSIGN_RISC) अणु
			/* Here device is the SNUM, and mcnProtocol is
			 * e_QeCmdRiscAssignment value */
			dev_shअगरt = QE_CR_SNUM_SHIFT;
			mcn_shअगरt = QE_CR_MCN_RISC_ASSIGN_SHIFT;
		पूर्ण अन्यथा अणु
			अगर (device == QE_CR_SUBBLOCK_USB)
				mcn_shअगरt = QE_CR_MCN_USB_SHIFT;
			अन्यथा
				mcn_shअगरt = QE_CR_MCN_NORMAL_SHIFT;
		पूर्ण

		ioग_लिखो32be(cmd_input, &qe_immr->cp.cecdr);
		ioग_लिखो32be((cmd | QE_CR_FLG | ((u32)device << dev_shअगरt) | (u32)mcn_protocol << mcn_shअगरt),
			       &qe_immr->cp.cecr);
	पूर्ण

	/* रुको क्रम the QE_CR_FLG to clear */
	ret = पढ़ोx_poll_समयout_atomic(ioपढ़ो32be, &qe_immr->cp.cecr, val,
					(val & QE_CR_FLG) == 0, 0, 100);
	/* On समयout, ret is -ETIMEDOUT, otherwise it will be 0. */
	spin_unlock_irqrestore(&qe_lock, flags);

	वापस ret == 0;
पूर्ण
EXPORT_SYMBOL(qe_issue_cmd);

/* Set a baud rate generator. This needs lots of work. There are
 * 16 BRGs, which can be connected to the QE channels or output
 * as घड़ीs. The BRGs are in two dअगरferent block of पूर्णांकernal
 * memory mapped space.
 * The BRG घड़ी is the QE घड़ी भागided by 2.
 * It was set up दीर्घ ago during the initial boot phase and is
 * is given to us.
 * Baud rate घड़ीs are zero-based in the driver code (as that maps
 * to port numbers). Documentation uses 1-based numbering.
 */
अटल अचिन्हित पूर्णांक brg_clk = 0;

#घोषणा CLK_GRAN	(1000)
#घोषणा CLK_GRAN_LIMIT	(5)

अचिन्हित पूर्णांक qe_get_brg_clk(व्योम)
अणु
	काष्ठा device_node *qe;
	u32 brg;
	अचिन्हित पूर्णांक mod;

	अगर (brg_clk)
		वापस brg_clk;

	qe = qe_get_device_node();
	अगर (!qe)
		वापस brg_clk;

	अगर (!of_property_पढ़ो_u32(qe, "brg-frequency", &brg))
		brg_clk = brg;

	of_node_put(qe);

	/* round this अगर near to a multiple of CLK_GRAN */
	mod = brg_clk % CLK_GRAN;
	अगर (mod) अणु
		अगर (mod < CLK_GRAN_LIMIT)
			brg_clk -= mod;
		अन्यथा अगर (mod > (CLK_GRAN - CLK_GRAN_LIMIT))
			brg_clk += CLK_GRAN - mod;
	पूर्ण

	वापस brg_clk;
पूर्ण
EXPORT_SYMBOL(qe_get_brg_clk);

#घोषणा PVR_VER_836x	0x8083
#घोषणा PVR_VER_832x	0x8084

अटल bool qe_general4_errata(व्योम)
अणु
#अगर_घोषित CONFIG_PPC32
	वापस pvr_version_is(PVR_VER_836x) || pvr_version_is(PVR_VER_832x);
#पूर्ण_अगर
	वापस false;
पूर्ण

/* Program the BRG to the given sampling rate and multiplier
 *
 * @brg: the BRG, QE_BRG1 - QE_BRG16
 * @rate: the desired sampling rate
 * @multiplier: corresponds to the value programmed in GUMR_L[RDCR] or
 * GUMR_L[TDCR].  E.g., अगर this BRG is the RX घड़ी, and GUMR_L[RDCR]=01,
 * then 'multiplier' should be 8.
 */
पूर्णांक qe_setbrg(क्रमागत qe_घड़ी brg, अचिन्हित पूर्णांक rate, अचिन्हित पूर्णांक multiplier)
अणु
	u32 भागisor, tempval;
	u32 भाग16 = 0;

	अगर ((brg < QE_BRG1) || (brg > QE_BRG16))
		वापस -EINVAL;

	भागisor = qe_get_brg_clk() / (rate * multiplier);

	अगर (भागisor > QE_BRGC_DIVISOR_MAX + 1) अणु
		भाग16 = QE_BRGC_DIV16;
		भागisor /= 16;
	पूर्ण

	/* Errata QE_General4, which affects some MPC832x and MPC836x SOCs, says
	   that the BRG भागisor must be even अगर you're not using भागide-by-16
	   mode. */
	अगर (qe_general4_errata())
		अगर (!भाग16 && (भागisor & 1) && (भागisor > 3))
			भागisor++;

	tempval = ((भागisor - 1) << QE_BRGC_DIVISOR_SHIFT) |
		QE_BRGC_ENABLE | भाग16;

	ioग_लिखो32be(tempval, &qe_immr->brg.brgc[brg - QE_BRG1]);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(qe_setbrg);

/* Convert a string to a QE घड़ी source क्रमागत
 *
 * This function takes a string, typically from a property in the device
 * tree, and वापसs the corresponding "enum qe_clock" value.
*/
क्रमागत qe_घड़ी qe_घड़ी_source(स्थिर अक्षर *source)
अणु
	अचिन्हित पूर्णांक i;

	अगर (strहालcmp(source, "none") == 0)
		वापस QE_CLK_NONE;

	अगर (म_भेद(source, "tsync_pin") == 0)
		वापस QE_TSYNC_PIN;

	अगर (म_भेद(source, "rsync_pin") == 0)
		वापस QE_RSYNC_PIN;

	अगर (strnहालcmp(source, "brg", 3) == 0) अणु
		i = simple_म_से_अदीर्घ(source + 3, शून्य, 10);
		अगर ((i >= 1) && (i <= 16))
			वापस (QE_BRG1 - 1) + i;
		अन्यथा
			वापस QE_CLK_DUMMY;
	पूर्ण

	अगर (strnहालcmp(source, "clk", 3) == 0) अणु
		i = simple_म_से_अदीर्घ(source + 3, शून्य, 10);
		अगर ((i >= 1) && (i <= 24))
			वापस (QE_CLK1 - 1) + i;
		अन्यथा
			वापस QE_CLK_DUMMY;
	पूर्ण

	वापस QE_CLK_DUMMY;
पूर्ण
EXPORT_SYMBOL(qe_घड़ी_source);

/* Initialize SNUMs (thपढ़ो serial numbers) according to
 * QE Module Control chapter, SNUM table
 */
अटल व्योम qe_snums_init(व्योम)
अणु
	अटल स्थिर u8 snum_init_76[] = अणु
		0x04, 0x05, 0x0C, 0x0D, 0x14, 0x15, 0x1C, 0x1D,
		0x24, 0x25, 0x2C, 0x2D, 0x34, 0x35, 0x88, 0x89,
		0x98, 0x99, 0xA8, 0xA9, 0xB8, 0xB9, 0xC8, 0xC9,
		0xD8, 0xD9, 0xE8, 0xE9, 0x44, 0x45, 0x4C, 0x4D,
		0x54, 0x55, 0x5C, 0x5D, 0x64, 0x65, 0x6C, 0x6D,
		0x74, 0x75, 0x7C, 0x7D, 0x84, 0x85, 0x8C, 0x8D,
		0x94, 0x95, 0x9C, 0x9D, 0xA4, 0xA5, 0xAC, 0xAD,
		0xB4, 0xB5, 0xBC, 0xBD, 0xC4, 0xC5, 0xCC, 0xCD,
		0xD4, 0xD5, 0xDC, 0xDD, 0xE4, 0xE5, 0xEC, 0xED,
		0xF4, 0xF5, 0xFC, 0xFD,
	पूर्ण;
	अटल स्थिर u8 snum_init_46[] = अणु
		0x04, 0x05, 0x0C, 0x0D, 0x14, 0x15, 0x1C, 0x1D,
		0x24, 0x25, 0x2C, 0x2D, 0x34, 0x35, 0x88, 0x89,
		0x98, 0x99, 0xA8, 0xA9, 0xB8, 0xB9, 0xC8, 0xC9,
		0xD8, 0xD9, 0xE8, 0xE9, 0x08, 0x09, 0x18, 0x19,
		0x28, 0x29, 0x38, 0x39, 0x48, 0x49, 0x58, 0x59,
		0x68, 0x69, 0x78, 0x79, 0x80, 0x81,
	पूर्ण;
	काष्ठा device_node *qe;
	स्थिर u8 *snum_init;
	पूर्णांक i;

	biपंचांगap_zero(snum_state, QE_NUM_OF_SNUM);
	qe_num_of_snum = 28; /* The शेष number of snum क्रम thपढ़ोs is 28 */
	qe = qe_get_device_node();
	अगर (qe) अणु
		i = of_property_पढ़ो_variable_u8_array(qe, "fsl,qe-snums",
						       snums, 1, QE_NUM_OF_SNUM);
		अगर (i > 0) अणु
			of_node_put(qe);
			qe_num_of_snum = i;
			वापस;
		पूर्ण
		/*
		 * Fall back to legacy binding of using the value of
		 * fsl,qe-num-snums to choose one of the अटल arrays
		 * above.
		 */
		of_property_पढ़ो_u32(qe, "fsl,qe-num-snums", &qe_num_of_snum);
		of_node_put(qe);
	पूर्ण

	अगर (qe_num_of_snum == 76) अणु
		snum_init = snum_init_76;
	पूर्ण अन्यथा अगर (qe_num_of_snum == 28 || qe_num_of_snum == 46) अणु
		snum_init = snum_init_46;
	पूर्ण अन्यथा अणु
		pr_err("QE: unsupported value of fsl,qe-num-snums: %u\n", qe_num_of_snum);
		वापस;
	पूर्ण
	स_नकल(snums, snum_init, qe_num_of_snum);
पूर्ण

पूर्णांक qe_get_snum(व्योम)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक snum = -EBUSY;
	पूर्णांक i;

	spin_lock_irqsave(&qe_lock, flags);
	i = find_first_zero_bit(snum_state, qe_num_of_snum);
	अगर (i < qe_num_of_snum) अणु
		set_bit(i, snum_state);
		snum = snums[i];
	पूर्ण
	spin_unlock_irqrestore(&qe_lock, flags);

	वापस snum;
पूर्ण
EXPORT_SYMBOL(qe_get_snum);

व्योम qe_put_snum(u8 snum)
अणु
	स्थिर u8 *p = स_प्रथम(snums, snum, qe_num_of_snum);

	अगर (p)
		clear_bit(p - snums, snum_state);
पूर्ण
EXPORT_SYMBOL(qe_put_snum);

अटल पूर्णांक qe_sdma_init(व्योम)
अणु
	काष्ठा sdma __iomem *sdma = &qe_immr->sdma;
	अटल s32 sdma_buf_offset = -ENOMEM;

	/* allocate 2 पूर्णांकernal temporary buffers (512 bytes size each) क्रम
	 * the SDMA */
	अगर (sdma_buf_offset < 0) अणु
		sdma_buf_offset = qe_muram_alloc(512 * 2, 4096);
		अगर (sdma_buf_offset < 0)
			वापस -ENOMEM;
	पूर्ण

	ioग_लिखो32be((u32)sdma_buf_offset & QE_SDEBCR_BA_MASK,
		       &sdma->sdebcr);
	ioग_लिखो32be((QE_SDMR_GLB_1_MSK | (0x1 << QE_SDMR_CEN_SHIFT)),
		       &sdma->sdmr);

	वापस 0;
पूर्ण

/* The maximum number of RISCs we support */
#घोषणा MAX_QE_RISC     4

/* Firmware inक्रमmation stored here क्रम qe_get_firmware_info() */
अटल काष्ठा qe_firmware_info qe_firmware_info;

/*
 * Set to 1 अगर QE firmware has been uploaded, and thereक्रमe
 * qe_firmware_info contains valid data.
 */
अटल पूर्णांक qe_firmware_uploaded;

/*
 * Upload a QE microcode
 *
 * This function is a worker function क्रम qe_upload_firmware().  It करोes
 * the actual uploading of the microcode.
 */
अटल व्योम qe_upload_microcode(स्थिर व्योम *base,
	स्थिर काष्ठा qe_microcode *ucode)
अणु
	स्थिर __be32 *code = base + be32_to_cpu(ucode->code_offset);
	अचिन्हित पूर्णांक i;

	अगर (ucode->major || ucode->minor || ucode->revision)
		prपूर्णांकk(KERN_INFO "qe-firmware: "
			"uploading microcode '%s' version %u.%u.%u\n",
			ucode->id, ucode->major, ucode->minor, ucode->revision);
	अन्यथा
		prपूर्णांकk(KERN_INFO "qe-firmware: "
			"uploading microcode '%s'\n", ucode->id);

	/* Use स्वतः-increment */
	ioग_लिखो32be(be32_to_cpu(ucode->iram_offset) | QE_IRAM_IADD_AIE | QE_IRAM_IADD_BADDR,
		       &qe_immr->iram.iadd);

	क्रम (i = 0; i < be32_to_cpu(ucode->count); i++)
		ioग_लिखो32be(be32_to_cpu(code[i]), &qe_immr->iram.idata);
	
	/* Set I-RAM Ready Register */
	ioग_लिखो32be(QE_IRAM_READY, &qe_immr->iram.iपढ़ोy);
पूर्ण

/*
 * Upload a microcode to the I-RAM at a specअगरic address.
 *
 * See Documentation/घातerpc/qe_firmware.rst क्रम inक्रमmation on QE microcode
 * uploading.
 *
 * Currently, only version 1 is supported, so the 'version' field must be
 * set to 1.
 *
 * The SOC model and revision are not validated, they are only displayed क्रम
 * inक्रमmational purposes.
 *
 * 'calc_size' is the calculated size, in bytes, of the firmware काष्ठाure and
 * all of the microcode काष्ठाures, minus the CRC.
 *
 * 'length' is the size that the काष्ठाure says it is, including the CRC.
 */
पूर्णांक qe_upload_firmware(स्थिर काष्ठा qe_firmware *firmware)
अणु
	अचिन्हित पूर्णांक i;
	अचिन्हित पूर्णांक j;
	u32 crc;
	माप_प्रकार calc_size;
	माप_प्रकार length;
	स्थिर काष्ठा qe_header *hdr;

	अगर (!firmware) अणु
		prपूर्णांकk(KERN_ERR "qe-firmware: invalid pointer\n");
		वापस -EINVAL;
	पूर्ण

	hdr = &firmware->header;
	length = be32_to_cpu(hdr->length);

	/* Check the magic */
	अगर ((hdr->magic[0] != 'Q') || (hdr->magic[1] != 'E') ||
	    (hdr->magic[2] != 'F')) अणु
		prपूर्णांकk(KERN_ERR "qe-firmware: not a microcode\n");
		वापस -EPERM;
	पूर्ण

	/* Check the version */
	अगर (hdr->version != 1) अणु
		prपूर्णांकk(KERN_ERR "qe-firmware: unsupported version\n");
		वापस -EPERM;
	पूर्ण

	/* Validate some of the fields */
	अगर ((firmware->count < 1) || (firmware->count > MAX_QE_RISC)) अणु
		prपूर्णांकk(KERN_ERR "qe-firmware: invalid data\n");
		वापस -EINVAL;
	पूर्ण

	/* Validate the length and check अगर there's a CRC */
	calc_size = काष्ठा_size(firmware, microcode, firmware->count);

	क्रम (i = 0; i < firmware->count; i++)
		/*
		 * For situations where the second RISC uses the same microcode
		 * as the first, the 'code_offset' and 'count' fields will be
		 * zero, so it's okay to add those.
		 */
		calc_size += माप(__be32) *
			be32_to_cpu(firmware->microcode[i].count);

	/* Validate the length */
	अगर (length != calc_size + माप(__be32)) अणु
		prपूर्णांकk(KERN_ERR "qe-firmware: invalid length\n");
		वापस -EPERM;
	पूर्ण

	/* Validate the CRC */
	crc = be32_to_cpu(*(__be32 *)((व्योम *)firmware + calc_size));
	अगर (crc != crc32(0, firmware, calc_size)) अणु
		prपूर्णांकk(KERN_ERR "qe-firmware: firmware CRC is invalid\n");
		वापस -EIO;
	पूर्ण

	/*
	 * If the microcode calls क्रम it, split the I-RAM.
	 */
	अगर (!firmware->split)
		qe_setbits_be16(&qe_immr->cp.cercr, QE_CP_CERCR_CIR);

	अगर (firmware->soc.model)
		prपूर्णांकk(KERN_INFO
			"qe-firmware: firmware '%s' for %u V%u.%u\n",
			firmware->id, be16_to_cpu(firmware->soc.model),
			firmware->soc.major, firmware->soc.minor);
	अन्यथा
		prपूर्णांकk(KERN_INFO "qe-firmware: firmware '%s'\n",
			firmware->id);

	/*
	 * The QE only supports one microcode per RISC, so clear out all the
	 * saved microcode inक्रमmation and put in the new.
	 */
	स_रखो(&qe_firmware_info, 0, माप(qe_firmware_info));
	strlcpy(qe_firmware_info.id, firmware->id, माप(qe_firmware_info.id));
	qe_firmware_info.extended_modes = be64_to_cpu(firmware->extended_modes);
	स_नकल(qe_firmware_info.vtraps, firmware->vtraps,
		माप(firmware->vtraps));

	/* Loop through each microcode. */
	क्रम (i = 0; i < firmware->count; i++) अणु
		स्थिर काष्ठा qe_microcode *ucode = &firmware->microcode[i];

		/* Upload a microcode अगर it's present */
		अगर (ucode->code_offset)
			qe_upload_microcode(firmware, ucode);

		/* Program the traps क्रम this processor */
		क्रम (j = 0; j < 16; j++) अणु
			u32 trap = be32_to_cpu(ucode->traps[j]);

			अगर (trap)
				ioग_लिखो32be(trap,
					       &qe_immr->rsp[i].tibcr[j]);
		पूर्ण

		/* Enable traps */
		ioग_लिखो32be(be32_to_cpu(ucode->eccr),
			       &qe_immr->rsp[i].eccr);
	पूर्ण

	qe_firmware_uploaded = 1;

	वापस 0;
पूर्ण
EXPORT_SYMBOL(qe_upload_firmware);

/*
 * Get info on the currently-loaded firmware
 *
 * This function also checks the device tree to see अगर the boot loader has
 * uploaded a firmware alपढ़ोy.
 */
काष्ठा qe_firmware_info *qe_get_firmware_info(व्योम)
अणु
	अटल पूर्णांक initialized;
	काष्ठा device_node *qe;
	काष्ठा device_node *fw = शून्य;
	स्थिर अक्षर *sprop;

	/*
	 * If we haven't checked yet, and a driver hasn't uploaded a firmware
	 * yet, then check the device tree क्रम inक्रमmation.
	 */
	अगर (qe_firmware_uploaded)
		वापस &qe_firmware_info;

	अगर (initialized)
		वापस शून्य;

	initialized = 1;

	qe = qe_get_device_node();
	अगर (!qe)
		वापस शून्य;

	/* Find the 'firmware' child node */
	fw = of_get_child_by_name(qe, "firmware");
	of_node_put(qe);

	/* Did we find the 'firmware' node? */
	अगर (!fw)
		वापस शून्य;

	qe_firmware_uploaded = 1;

	/* Copy the data पूर्णांकo qe_firmware_info*/
	sprop = of_get_property(fw, "id", शून्य);
	अगर (sprop)
		strlcpy(qe_firmware_info.id, sprop,
			माप(qe_firmware_info.id));

	of_property_पढ़ो_u64(fw, "extended-modes",
			     &qe_firmware_info.extended_modes);

	of_property_पढ़ो_u32_array(fw, "virtual-traps", qe_firmware_info.vtraps,
				   ARRAY_SIZE(qe_firmware_info.vtraps));

	of_node_put(fw);

	वापस &qe_firmware_info;
पूर्ण
EXPORT_SYMBOL(qe_get_firmware_info);

अचिन्हित पूर्णांक qe_get_num_of_risc(व्योम)
अणु
	काष्ठा device_node *qe;
	अचिन्हित पूर्णांक num_of_risc = 0;

	qe = qe_get_device_node();
	अगर (!qe)
		वापस num_of_risc;

	of_property_पढ़ो_u32(qe, "fsl,qe-num-riscs", &num_of_risc);

	of_node_put(qe);

	वापस num_of_risc;
पूर्ण
EXPORT_SYMBOL(qe_get_num_of_risc);

अचिन्हित पूर्णांक qe_get_num_of_snums(व्योम)
अणु
	वापस qe_num_of_snum;
पूर्ण
EXPORT_SYMBOL(qe_get_num_of_snums);

अटल पूर्णांक __init qe_init(व्योम)
अणु
	काष्ठा device_node *np;

	np = of_find_compatible_node(शून्य, शून्य, "fsl,qe");
	अगर (!np)
		वापस -ENODEV;
	qe_reset();
	of_node_put(np);
	वापस 0;
पूर्ण
subsys_initcall(qe_init);

#अगर defined(CONFIG_SUSPEND) && defined(CONFIG_PPC_85xx)
अटल पूर्णांक qe_resume(काष्ठा platक्रमm_device *ofdev)
अणु
	अगर (!qe_alive_during_sleep())
		qe_reset();
	वापस 0;
पूर्ण

अटल पूर्णांक qe_probe(काष्ठा platक्रमm_device *ofdev)
अणु
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id qe_ids[] = अणु
	अणु .compatible = "fsl,qe", पूर्ण,
	अणु पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_driver qe_driver = अणु
	.driver = अणु
		.name = "fsl-qe",
		.of_match_table = qe_ids,
	पूर्ण,
	.probe = qe_probe,
	.resume = qe_resume,
पूर्ण;

builtin_platक्रमm_driver(qe_driver);
#पूर्ण_अगर /* defined(CONFIG_SUSPEND) && defined(CONFIG_PPC_85xx) */
