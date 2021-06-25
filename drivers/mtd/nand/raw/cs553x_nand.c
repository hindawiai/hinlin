<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * (C) 2005, 2006 Red Hat Inc.
 *
 * Author: David Woodhouse <dwmw2@infradead.org>
 *	   Tom Sylla <tom.sylla@amd.com>
 *
 *  Overview:
 *   This is a device driver क्रम the न_अंकD flash controller found on
 *   the AMD CS5535/CS5536 companion chipsets क्रम the Geode processor.
 *   mtd-id क्रम command line partitioning is cs553x_nand_cs[0-3]
 *   where 0-3 reflects the chip select क्रम न_अंकD.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/delay.h>
#समावेश <linux/mtd/mtd.h>
#समावेश <linux/mtd/nand-ecc-sw-hamming.h>
#समावेश <linux/mtd/rawnand.h>
#समावेश <linux/mtd/partitions.h>
#समावेश <linux/iopoll.h>

#समावेश <यंत्र/msr.h>

#घोषणा NR_CS553X_CONTROLLERS	4

#घोषणा MSR_DIVIL_GLD_CAP	0x51400000	/* DIVIL capabilitiies */
#घोषणा CAP_CS5535		0x2df000ULL
#घोषणा CAP_CS5536		0x5df500ULL

/* न_अंकD Timing MSRs */
#घोषणा MSR_न_अंकDF_DATA		0x5140001b	/* न_अंकD Flash Data Timing MSR */
#घोषणा MSR_न_अंकDF_CTL		0x5140001c	/* न_अंकD Flash Control Timing */
#घोषणा MSR_न_अंकDF_RSVD		0x5140001d	/* Reserved */

/* न_अंकD BAR MSRs */
#घोषणा MSR_DIVIL_LBAR_FLSH0	0x51400010	/* Flash Chip Select 0 */
#घोषणा MSR_DIVIL_LBAR_FLSH1	0x51400011	/* Flash Chip Select 1 */
#घोषणा MSR_DIVIL_LBAR_FLSH2	0x51400012	/* Flash Chip Select 2 */
#घोषणा MSR_DIVIL_LBAR_FLSH3	0x51400013	/* Flash Chip Select 3 */
	/* Each made up of... */
#घोषणा FLSH_LBAR_EN		(1ULL<<32)
#घोषणा FLSH_NOR_न_अंकD		(1ULL<<33)	/* 1 क्रम न_अंकD */
#घोषणा FLSH_MEM_IO		(1ULL<<34)	/* 1 क्रम MMIO */
	/* I/O BARs have BASE_ADDR in bits 15:4, IO_MASK in 47:36 */
	/* MMIO BARs have BASE_ADDR in bits 31:12, MEM_MASK in 63:44 */

/* Pin function selection MSR (IDE vs. flash on the IDE pins) */
#घोषणा MSR_DIVIL_BALL_OPTS	0x51400015
#घोषणा PIN_OPT_IDE		(1<<0)	/* 0 क्रम flash, 1 क्रम IDE */

/* Registers within the न_अंकD flash controller BAR -- memory mapped */
#घोषणा MM_न_अंकD_DATA		0x00	/* 0 to 0x7ff, in fact */
#घोषणा MM_न_अंकD_CTL		0x800	/* Any even address 0x800-0x80e */
#घोषणा MM_न_अंकD_IO		0x801	/* Any odd address 0x801-0x80f */
#घोषणा MM_न_अंकD_STS		0x810
#घोषणा MM_न_अंकD_ECC_LSB		0x811
#घोषणा MM_न_अंकD_ECC_MSB		0x812
#घोषणा MM_न_अंकD_ECC_COL		0x813
#घोषणा MM_न_अंकD_LAC		0x814
#घोषणा MM_न_अंकD_ECC_CTL		0x815

/* Registers within the न_अंकD flash controller BAR -- I/O mapped */
#घोषणा IO_न_अंकD_DATA		0x00	/* 0 to 3, in fact */
#घोषणा IO_न_अंकD_CTL		0x04
#घोषणा IO_न_अंकD_IO		0x05
#घोषणा IO_न_अंकD_STS		0x06
#घोषणा IO_न_अंकD_ECC_CTL		0x08
#घोषणा IO_न_अंकD_ECC_LSB		0x09
#घोषणा IO_न_अंकD_ECC_MSB		0x0a
#घोषणा IO_न_अंकD_ECC_COL		0x0b
#घोषणा IO_न_अंकD_LAC		0x0c

#घोषणा CS_न_अंकD_CTL_DIST_EN	(1<<4)	/* Enable न_अंकD Distract पूर्णांकerrupt */
#घोषणा CS_न_अंकD_CTL_RDY_INT_MASK	(1<<3)	/* Enable RDY/BUSY# पूर्णांकerrupt */
#घोषणा CS_न_अंकD_CTL_ALE		(1<<2)
#घोषणा CS_न_अंकD_CTL_CLE		(1<<1)
#घोषणा CS_न_अंकD_CTL_CE		(1<<0)	/* Keep low; 1 to reset */

#घोषणा CS_न_अंकD_STS_FLASH_RDY	(1<<3)
#घोषणा CS_न_अंकD_CTLR_BUSY	(1<<2)
#घोषणा CS_न_अंकD_CMD_COMP	(1<<1)
#घोषणा CS_न_अंकD_DIST_ST		(1<<0)

#घोषणा CS_न_अंकD_ECC_PARITY	(1<<2)
#घोषणा CS_न_अंकD_ECC_CLRECC	(1<<1)
#घोषणा CS_न_अंकD_ECC_ENECC	(1<<0)

काष्ठा cs553x_nand_controller अणु
	काष्ठा nand_controller base;
	काष्ठा nand_chip chip;
	व्योम __iomem *mmio;
पूर्ण;

अटल काष्ठा cs553x_nand_controller *
to_cs553x(काष्ठा nand_controller *controller)
अणु
	वापस container_of(controller, काष्ठा cs553x_nand_controller, base);
पूर्ण

अटल पूर्णांक cs553x_ग_लिखो_ctrl_byte(काष्ठा cs553x_nand_controller *cs553x,
				  u32 ctl, u8 data)
अणु
	u8 status;
	पूर्णांक ret;

	ग_लिखोb(ctl, cs553x->mmio + MM_न_अंकD_CTL);
	ग_लिखोb(data, cs553x->mmio + MM_न_अंकD_IO);
	ret = पढ़ोb_poll_समयout_atomic(cs553x->mmio + MM_न_अंकD_STS, status,
					!(status & CS_न_अंकD_CTLR_BUSY), 1,
					100000);
	अगर (ret)
		वापस ret;

	वापस 0;
पूर्ण

अटल व्योम cs553x_data_in(काष्ठा cs553x_nand_controller *cs553x, व्योम *buf,
			   अचिन्हित पूर्णांक len)
अणु
	ग_लिखोb(0, cs553x->mmio + MM_न_अंकD_CTL);
	जबतक (unlikely(len > 0x800)) अणु
		स_नकल_fromio(buf, cs553x->mmio, 0x800);
		buf += 0x800;
		len -= 0x800;
	पूर्ण
	स_नकल_fromio(buf, cs553x->mmio, len);
पूर्ण

अटल व्योम cs553x_data_out(काष्ठा cs553x_nand_controller *cs553x,
			    स्थिर व्योम *buf, अचिन्हित पूर्णांक len)
अणु
	ग_लिखोb(0, cs553x->mmio + MM_न_अंकD_CTL);
	जबतक (unlikely(len > 0x800)) अणु
		स_नकल_toio(cs553x->mmio, buf, 0x800);
		buf += 0x800;
		len -= 0x800;
	पूर्ण
	स_नकल_toio(cs553x->mmio, buf, len);
पूर्ण

अटल पूर्णांक cs553x_रुको_पढ़ोy(काष्ठा cs553x_nand_controller *cs553x,
			     अचिन्हित पूर्णांक समयout_ms)
अणु
	u8 mask = CS_न_अंकD_CTLR_BUSY | CS_न_अंकD_STS_FLASH_RDY;
	u8 status;

	वापस पढ़ोb_poll_समयout(cs553x->mmio + MM_न_अंकD_STS, status,
				  (status & mask) == CS_न_अंकD_STS_FLASH_RDY, 100,
				  समयout_ms * 1000);
पूर्ण

अटल पूर्णांक cs553x_exec_instr(काष्ठा cs553x_nand_controller *cs553x,
			     स्थिर काष्ठा nand_op_instr *instr)
अणु
	अचिन्हित पूर्णांक i;
	पूर्णांक ret = 0;

	चयन (instr->type) अणु
	हाल न_अंकD_OP_CMD_INSTR:
		ret = cs553x_ग_लिखो_ctrl_byte(cs553x, CS_न_अंकD_CTL_CLE,
					     instr->ctx.cmd.opcode);
		अवरोध;

	हाल न_अंकD_OP_ADDR_INSTR:
		क्रम (i = 0; i < instr->ctx.addr.naddrs; i++) अणु
			ret = cs553x_ग_लिखो_ctrl_byte(cs553x, CS_न_अंकD_CTL_ALE,
						     instr->ctx.addr.addrs[i]);
			अगर (ret)
				अवरोध;
		पूर्ण
		अवरोध;

	हाल न_अंकD_OP_DATA_IN_INSTR:
		cs553x_data_in(cs553x, instr->ctx.data.buf.in,
			       instr->ctx.data.len);
		अवरोध;

	हाल न_अंकD_OP_DATA_OUT_INSTR:
		cs553x_data_out(cs553x, instr->ctx.data.buf.out,
				instr->ctx.data.len);
		अवरोध;

	हाल न_अंकD_OP_WAITRDY_INSTR:
		ret = cs553x_रुको_पढ़ोy(cs553x, instr->ctx.रुकोrdy.समयout_ms);
		अवरोध;
	पूर्ण

	अगर (instr->delay_ns)
		ndelay(instr->delay_ns);

	वापस ret;
पूर्ण

अटल पूर्णांक cs553x_exec_op(काष्ठा nand_chip *this,
			  स्थिर काष्ठा nand_operation *op,
			  bool check_only)
अणु
	काष्ठा cs553x_nand_controller *cs553x = to_cs553x(this->controller);
	अचिन्हित पूर्णांक i;
	पूर्णांक ret;

	अगर (check_only)
		वापस true;

	/* De-निश्चित the CE pin */
	ग_लिखोb(0, cs553x->mmio + MM_न_अंकD_CTL);
	क्रम (i = 0; i < op->ninstrs; i++) अणु
		ret = cs553x_exec_instr(cs553x, &op->instrs[i]);
		अगर (ret)
			अवरोध;
	पूर्ण

	/* Re-निश्चित the CE pin. */
	ग_लिखोb(CS_न_अंकD_CTL_CE, cs553x->mmio + MM_न_अंकD_CTL);

	वापस ret;
पूर्ण

अटल व्योम cs_enable_hwecc(काष्ठा nand_chip *this, पूर्णांक mode)
अणु
	काष्ठा cs553x_nand_controller *cs553x = to_cs553x(this->controller);

	ग_लिखोb(0x07, cs553x->mmio + MM_न_अंकD_ECC_CTL);
पूर्ण

अटल पूर्णांक cs_calculate_ecc(काष्ठा nand_chip *this, स्थिर u_अक्षर *dat,
			    u_अक्षर *ecc_code)
अणु
	काष्ठा cs553x_nand_controller *cs553x = to_cs553x(this->controller);
	uपूर्णांक32_t ecc;

	ecc = पढ़ोl(cs553x->mmio + MM_न_अंकD_STS);

	ecc_code[1] = ecc >> 8;
	ecc_code[0] = ecc >> 16;
	ecc_code[2] = ecc >> 24;
	वापस 0;
पूर्ण

अटल पूर्णांक cs553x_ecc_correct(काष्ठा nand_chip *chip,
			      अचिन्हित अक्षर *buf,
			      अचिन्हित अक्षर *पढ़ो_ecc,
			      अचिन्हित अक्षर *calc_ecc)
अणु
	वापस ecc_sw_hamming_correct(buf, पढ़ो_ecc, calc_ecc,
				      chip->ecc.size, false);
पूर्ण

अटल काष्ठा cs553x_nand_controller *controllers[4];

अटल पूर्णांक cs553x_attach_chip(काष्ठा nand_chip *chip)
अणु
	अगर (chip->ecc.engine_type != न_अंकD_ECC_ENGINE_TYPE_ON_HOST)
		वापस 0;

	chip->ecc.size = 256;
	chip->ecc.bytes = 3;
	chip->ecc.hwctl  = cs_enable_hwecc;
	chip->ecc.calculate = cs_calculate_ecc;
	chip->ecc.correct  = cs553x_ecc_correct;
	chip->ecc.strength = 1;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा nand_controller_ops cs553x_nand_controller_ops = अणु
	.exec_op = cs553x_exec_op,
	.attach_chip = cs553x_attach_chip,
पूर्ण;

अटल पूर्णांक __init cs553x_init_one(पूर्णांक cs, पूर्णांक mmio, अचिन्हित दीर्घ adr)
अणु
	काष्ठा cs553x_nand_controller *controller;
	पूर्णांक err = 0;
	काष्ठा nand_chip *this;
	काष्ठा mtd_info *new_mtd;

	pr_notice("Probing CS553x NAND controller CS#%d at %sIO 0x%08lx\n",
		  cs, mmio ? "MM" : "P", adr);

	अगर (!mmio) अणु
		pr_notice("PIO mode not yet implemented for CS553X NAND controller\n");
		वापस -ENXIO;
	पूर्ण

	/* Allocate memory क्रम MTD device काष्ठाure and निजी data */
	controller = kzalloc(माप(*controller), GFP_KERNEL);
	अगर (!controller) अणु
		err = -ENOMEM;
		जाओ out;
	पूर्ण

	this = &controller->chip;
	nand_controller_init(&controller->base);
	controller->base.ops = &cs553x_nand_controller_ops;
	this->controller = &controller->base;
	new_mtd = nand_to_mtd(this);

	/* Link the निजी data with the MTD काष्ठाure */
	new_mtd->owner = THIS_MODULE;

	/* map physical address */
	controller->mmio = ioremap(adr, 4096);
	अगर (!controller->mmio) अणु
		pr_warn("ioremap cs553x NAND @0x%08lx failed\n", adr);
		err = -EIO;
		जाओ out_mtd;
	पूर्ण

	/* Enable the following क्रम a flash based bad block table */
	this->bbt_options = न_अंकD_BBT_USE_FLASH;

	new_mtd->name = kaप्र_लिखो(GFP_KERNEL, "cs553x_nand_cs%d", cs);
	अगर (!new_mtd->name) अणु
		err = -ENOMEM;
		जाओ out_ior;
	पूर्ण

	/* Scan to find existence of the device */
	err = nand_scan(this, 1);
	अगर (err)
		जाओ out_मुक्त;

	controllers[cs] = controller;
	जाओ out;

out_मुक्त:
	kमुक्त(new_mtd->name);
out_ior:
	iounmap(controller->mmio);
out_mtd:
	kमुक्त(controller);
out:
	वापस err;
पूर्ण

अटल पूर्णांक is_geode(व्योम)
अणु
	/* These are the CPUs which will have a CS553[56] companion chip */
	अगर (boot_cpu_data.x86_venकरोr == X86_VENDOR_AMD &&
	    boot_cpu_data.x86 == 5 &&
	    boot_cpu_data.x86_model == 10)
		वापस 1; /* Geode LX */

	अगर ((boot_cpu_data.x86_venकरोr == X86_VENDOR_NSC ||
	     boot_cpu_data.x86_venकरोr == X86_VENDOR_CYRIX) &&
	    boot_cpu_data.x86 == 5 &&
	    boot_cpu_data.x86_model == 5)
		वापस 1; /* Geode GX (nथऊe GX2) */

	वापस 0;
पूर्ण

अटल पूर्णांक __init cs553x_init(व्योम)
अणु
	पूर्णांक err = -ENXIO;
	पूर्णांक i;
	uपूर्णांक64_t val;

	/* If the CPU isn't a Geode GX or LX, पात */
	अगर (!is_geode())
		वापस -ENXIO;

	/* If it करोesn't have the CS553[56], पात */
	rdmsrl(MSR_DIVIL_GLD_CAP, val);
	val &= ~0xFFULL;
	अगर (val != CAP_CS5535 && val != CAP_CS5536)
		वापस -ENXIO;

	/* If it करोesn't have the न_अंकD controller enabled, पात */
	rdmsrl(MSR_DIVIL_BALL_OPTS, val);
	अगर (val & PIN_OPT_IDE) अणु
		pr_info("CS553x NAND controller: Flash I/O not enabled in MSR_DIVIL_BALL_OPTS.\n");
		वापस -ENXIO;
	पूर्ण

	क्रम (i = 0; i < NR_CS553X_CONTROLLERS; i++) अणु
		rdmsrl(MSR_DIVIL_LBAR_FLSH0 + i, val);

		अगर ((val & (FLSH_LBAR_EN|FLSH_NOR_न_अंकD)) == (FLSH_LBAR_EN|FLSH_NOR_न_अंकD))
			err = cs553x_init_one(i, !!(val & FLSH_MEM_IO), val & 0xFFFFFFFF);
	पूर्ण

	/* Register all devices together here. This means we can easily hack it to
	   करो mtdconcat etc. अगर we want to. */
	क्रम (i = 0; i < NR_CS553X_CONTROLLERS; i++) अणु
		अगर (controllers[i]) अणु
			/* If any devices रेजिस्टरed, वापस success. Else the last error. */
			mtd_device_रेजिस्टर(nand_to_mtd(&controllers[i]->chip),
					    शून्य, 0);
			err = 0;
		पूर्ण
	पूर्ण

	वापस err;
पूर्ण

module_init(cs553x_init);

अटल व्योम __निकास cs553x_cleanup(व्योम)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < NR_CS553X_CONTROLLERS; i++) अणु
		काष्ठा cs553x_nand_controller *controller = controllers[i];
		काष्ठा nand_chip *this = &controller->chip;
		काष्ठा mtd_info *mtd = nand_to_mtd(this);
		पूर्णांक ret;

		अगर (!mtd)
			जारी;

		/* Release resources, unरेजिस्टर device */
		ret = mtd_device_unरेजिस्टर(mtd);
		WARN_ON(ret);
		nand_cleanup(this);
		kमुक्त(mtd->name);
		controllers[i] = शून्य;

		/* unmap physical address */
		iounmap(controller->mmio);

		/* Free the MTD device काष्ठाure */
		kमुक्त(controller);
	पूर्ण
पूर्ण

module_निकास(cs553x_cleanup);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("David Woodhouse <dwmw2@infradead.org>");
MODULE_DESCRIPTION("NAND controller driver for AMD CS5535/CS5536 companion chip");
