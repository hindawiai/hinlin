<शैली गुरु>
/*
 * arch/arm/mach-orion5x/ts78xx-setup.c
 *
 * Maपूर्णांकainer: Alexander Clouter <alex@digriz.org.uk>
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2.  This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/sysfs.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/mv643xx_eth.h>
#समावेश <linux/ata_platक्रमm.h>
#समावेश <linux/mtd/platnand.h>
#समावेश <linux/समयriomem-rng.h>
#समावेश <यंत्र/mach-types.h>
#समावेश <यंत्र/mach/arch.h>
#समावेश <यंत्र/mach/map.h>
#समावेश "common.h"
#समावेश "mpp.h"
#समावेश "orion5x.h"
#समावेश "ts78xx-fpga.h"

/*****************************************************************************
 * TS-78xx Info
 ****************************************************************************/

/*
 * FPGA - lives where the PCI bus would be at ORION5X_PCI_MEM_PHYS_BASE
 */
#घोषणा TS78XX_FPGA_REGS_PHYS_BASE	0xe8000000
#घोषणा TS78XX_FPGA_REGS_VIRT_BASE	IOMEM(0xff900000)
#घोषणा TS78XX_FPGA_REGS_SIZE		SZ_1M

अटल काष्ठा ts78xx_fpga_data ts78xx_fpga = अणु
	.id		= 0,
	.state		= 1,
/*	.supports	= ... - populated by ts78xx_fpga_supports() */
पूर्ण;

/*****************************************************************************
 * I/O Address Mapping
 ****************************************************************************/
अटल काष्ठा map_desc ts78xx_io_desc[] __initdata = अणु
	अणु
		.भव	= (अचिन्हित दीर्घ)TS78XX_FPGA_REGS_VIRT_BASE,
		.pfn		= __phys_to_pfn(TS78XX_FPGA_REGS_PHYS_BASE),
		.length		= TS78XX_FPGA_REGS_SIZE,
		.type		= MT_DEVICE,
	पूर्ण,
पूर्ण;

अटल व्योम __init ts78xx_map_io(व्योम)
अणु
	orion5x_map_io();
	iotable_init(ts78xx_io_desc, ARRAY_SIZE(ts78xx_io_desc));
पूर्ण

/*****************************************************************************
 * Ethernet
 ****************************************************************************/
अटल काष्ठा mv643xx_eth_platक्रमm_data ts78xx_eth_data = अणु
	.phy_addr	= MV643XX_ETH_PHY_ADDR(0),
पूर्ण;

/*****************************************************************************
 * SATA
 ****************************************************************************/
अटल काष्ठा mv_sata_platक्रमm_data ts78xx_sata_data = अणु
	.n_ports	= 2,
पूर्ण;

/*****************************************************************************
 * RTC M48T86 - nicked^Wborrowed from arch/arm/mach-ep93xx/ts72xx.c
 ****************************************************************************/
#घोषणा TS_RTC_CTRL	(TS78XX_FPGA_REGS_PHYS_BASE + 0x808)
#घोषणा TS_RTC_DATA	(TS78XX_FPGA_REGS_PHYS_BASE + 0x80c)

अटल काष्ठा resource ts78xx_ts_rtc_resources[] = अणु
	DEFINE_RES_MEM(TS_RTC_CTRL, 0x01),
	DEFINE_RES_MEM(TS_RTC_DATA, 0x01),
पूर्ण;

अटल काष्ठा platक्रमm_device ts78xx_ts_rtc_device = अणु
	.name		= "rtc-m48t86",
	.id		= -1,
	.resource	= ts78xx_ts_rtc_resources,
	.num_resources 	= ARRAY_SIZE(ts78xx_ts_rtc_resources),
पूर्ण;

अटल पूर्णांक ts78xx_ts_rtc_load(व्योम)
अणु
	पूर्णांक rc;

	अगर (ts78xx_fpga.supports.ts_rtc.init == 0) अणु
		rc = platक्रमm_device_रेजिस्टर(&ts78xx_ts_rtc_device);
		अगर (!rc)
			ts78xx_fpga.supports.ts_rtc.init = 1;
	पूर्ण अन्यथा अणु
		rc = platक्रमm_device_add(&ts78xx_ts_rtc_device);
	पूर्ण

	अगर (rc)
		pr_info("RTC could not be registered: %d\n", rc);

	वापस rc;
पूर्ण

अटल व्योम ts78xx_ts_rtc_unload(व्योम)
अणु
	platक्रमm_device_del(&ts78xx_ts_rtc_device);
पूर्ण

/*****************************************************************************
 * न_अंकD Flash
 ****************************************************************************/
#घोषणा TS_न_अंकD_CTRL	(TS78XX_FPGA_REGS_VIRT_BASE + 0x800)	/* VIRT */
#घोषणा TS_न_अंकD_DATA	(TS78XX_FPGA_REGS_PHYS_BASE + 0x804)	/* PHYS */

/*
 * hardware specअगरic access to control-lines
 *
 * ctrl:
 * न_अंकD_NCE: bit 0 -> bit 2
 * न_अंकD_CLE: bit 1 -> bit 1
 * न_अंकD_ALE: bit 2 -> bit 0
 */
अटल व्योम ts78xx_ts_nand_cmd_ctrl(काष्ठा nand_chip *this, पूर्णांक cmd,
				    अचिन्हित पूर्णांक ctrl)
अणु
	अगर (ctrl & न_अंकD_CTRL_CHANGE) अणु
		अचिन्हित अक्षर bits;

		bits = (ctrl & न_अंकD_NCE) << 2;
		bits |= ctrl & न_अंकD_CLE;
		bits |= (ctrl & न_अंकD_ALE) >> 2;

		ग_लिखोb((पढ़ोb(TS_न_अंकD_CTRL) & ~0x7) | bits, TS_न_अंकD_CTRL);
	पूर्ण

	अगर (cmd != न_अंकD_CMD_NONE)
		ग_लिखोb(cmd, this->legacy.IO_ADDR_W);
पूर्ण

अटल पूर्णांक ts78xx_ts_nand_dev_पढ़ोy(काष्ठा nand_chip *chip)
अणु
	वापस पढ़ोb(TS_न_अंकD_CTRL) & 0x20;
पूर्ण

अटल व्योम ts78xx_ts_nand_ग_लिखो_buf(काष्ठा nand_chip *chip,
				     स्थिर uपूर्णांक8_t *buf, पूर्णांक len)
अणु
	व्योम __iomem *io_base = chip->legacy.IO_ADDR_W;
	अचिन्हित दीर्घ off = ((अचिन्हित दीर्घ)buf & 3);
	पूर्णांक sz;

	अगर (off) अणु
		sz = min_t(पूर्णांक, 4 - off, len);
		ग_लिखोsb(io_base, buf, sz);
		buf += sz;
		len -= sz;
	पूर्ण

	sz = len >> 2;
	अगर (sz) अणु
		u32 *buf32 = (u32 *)buf;
		ग_लिखोsl(io_base, buf32, sz);
		buf += sz << 2;
		len -= sz << 2;
	पूर्ण

	अगर (len)
		ग_लिखोsb(io_base, buf, len);
पूर्ण

अटल व्योम ts78xx_ts_nand_पढ़ो_buf(काष्ठा nand_chip *chip,
				    uपूर्णांक8_t *buf, पूर्णांक len)
अणु
	व्योम __iomem *io_base = chip->legacy.IO_ADDR_R;
	अचिन्हित दीर्घ off = ((अचिन्हित दीर्घ)buf & 3);
	पूर्णांक sz;

	अगर (off) अणु
		sz = min_t(पूर्णांक, 4 - off, len);
		पढ़ोsb(io_base, buf, sz);
		buf += sz;
		len -= sz;
	पूर्ण

	sz = len >> 2;
	अगर (sz) अणु
		u32 *buf32 = (u32 *)buf;
		पढ़ोsl(io_base, buf32, sz);
		buf += sz << 2;
		len -= sz << 2;
	पूर्ण

	अगर (len)
		पढ़ोsb(io_base, buf, len);
पूर्ण

अटल काष्ठा mtd_partition ts78xx_ts_nand_parts[] = अणु
	अणु
		.name		= "mbr",
		.offset		= 0,
		.size		= SZ_128K,
		.mask_flags	= MTD_WRITEABLE,
	पूर्ण, अणु
		.name		= "kernel",
		.offset		= MTDPART_OFS_APPEND,
		.size		= SZ_4M,
	पूर्ण, अणु
		.name		= "initrd",
		.offset		= MTDPART_OFS_APPEND,
		.size		= SZ_4M,
	पूर्ण, अणु
		.name		= "rootfs",
		.offset		= MTDPART_OFS_APPEND,
		.size		= MTDPART_SIZ_FULL,
	पूर्ण
पूर्ण;

अटल काष्ठा platक्रमm_nand_data ts78xx_ts_nand_data = अणु
	.chip	= अणु
		.nr_chips		= 1,
		.partitions		= ts78xx_ts_nand_parts,
		.nr_partitions		= ARRAY_SIZE(ts78xx_ts_nand_parts),
		.chip_delay		= 15,
		.bbt_options		= न_अंकD_BBT_USE_FLASH,
	पूर्ण,
	.ctrl	= अणु
		/*
		 * The HW ECC offloading functions, used to give about a 9%
		 * perक्रमmance increase क्रम 'dd if=/dev/mtdblockX' and 5% क्रम
		 * nanddump.  This all however was changed by git commit
		 * e6cf5df1838c28bb060ac45b5585e48e71bbc740 so now there is
		 * no perक्रमmance advantage to be had so we no दीर्घer bother
		 */
		.cmd_ctrl		= ts78xx_ts_nand_cmd_ctrl,
		.dev_पढ़ोy		= ts78xx_ts_nand_dev_पढ़ोy,
		.ग_लिखो_buf		= ts78xx_ts_nand_ग_लिखो_buf,
		.पढ़ो_buf		= ts78xx_ts_nand_पढ़ो_buf,
	पूर्ण,
पूर्ण;

अटल काष्ठा resource ts78xx_ts_nand_resources
			= DEFINE_RES_MEM(TS_न_अंकD_DATA, 4);

अटल काष्ठा platक्रमm_device ts78xx_ts_nand_device = अणु
	.name		= "gen_nand",
	.id		= -1,
	.dev		= अणु
		.platक्रमm_data	= &ts78xx_ts_nand_data,
	पूर्ण,
	.resource	= &ts78xx_ts_nand_resources,
	.num_resources	= 1,
पूर्ण;

अटल पूर्णांक ts78xx_ts_nand_load(व्योम)
अणु
	पूर्णांक rc;

	अगर (ts78xx_fpga.supports.ts_nand.init == 0) अणु
		rc = platक्रमm_device_रेजिस्टर(&ts78xx_ts_nand_device);
		अगर (!rc)
			ts78xx_fpga.supports.ts_nand.init = 1;
	पूर्ण अन्यथा
		rc = platक्रमm_device_add(&ts78xx_ts_nand_device);

	अगर (rc)
		pr_info("NAND could not be registered: %d\n", rc);
	वापस rc;
पूर्ण;

अटल व्योम ts78xx_ts_nand_unload(व्योम)
अणु
	platक्रमm_device_del(&ts78xx_ts_nand_device);
पूर्ण

/*****************************************************************************
 * HW RNG
 ****************************************************************************/
#घोषणा TS_RNG_DATA	(TS78XX_FPGA_REGS_PHYS_BASE | 0x044)

अटल काष्ठा resource ts78xx_ts_rng_resource
			= DEFINE_RES_MEM(TS_RNG_DATA, 4);

अटल काष्ठा समयriomem_rng_data ts78xx_ts_rng_data = अणु
	.period		= 1000000, /* one second */
पूर्ण;

अटल काष्ठा platक्रमm_device ts78xx_ts_rng_device = अणु
	.name		= "timeriomem_rng",
	.id		= -1,
	.dev		= अणु
		.platक्रमm_data	= &ts78xx_ts_rng_data,
	पूर्ण,
	.resource	= &ts78xx_ts_rng_resource,
	.num_resources	= 1,
पूर्ण;

अटल पूर्णांक ts78xx_ts_rng_load(व्योम)
अणु
	पूर्णांक rc;

	अगर (ts78xx_fpga.supports.ts_rng.init == 0) अणु
		rc = platक्रमm_device_रेजिस्टर(&ts78xx_ts_rng_device);
		अगर (!rc)
			ts78xx_fpga.supports.ts_rng.init = 1;
	पूर्ण अन्यथा
		rc = platक्रमm_device_add(&ts78xx_ts_rng_device);

	अगर (rc)
		pr_info("RNG could not be registered: %d\n", rc);
	वापस rc;
पूर्ण;

अटल व्योम ts78xx_ts_rng_unload(व्योम)
अणु
	platक्रमm_device_del(&ts78xx_ts_rng_device);
पूर्ण

/*****************************************************************************
 * FPGA 'hotplug' support code
 ****************************************************************************/
अटल व्योम ts78xx_fpga_devices_zero_init(व्योम)
अणु
	ts78xx_fpga.supports.ts_rtc.init = 0;
	ts78xx_fpga.supports.ts_nand.init = 0;
	ts78xx_fpga.supports.ts_rng.init = 0;
पूर्ण

अटल व्योम ts78xx_fpga_supports(व्योम)
अणु
	/* TODO: put this 'table' पूर्णांकo ts78xx-fpga.h */
	चयन (ts78xx_fpga.id) अणु
	हाल TS7800_REV_1:
	हाल TS7800_REV_2:
	हाल TS7800_REV_3:
	हाल TS7800_REV_4:
	हाल TS7800_REV_5:
	हाल TS7800_REV_6:
	हाल TS7800_REV_7:
	हाल TS7800_REV_8:
	हाल TS7800_REV_9:
		ts78xx_fpga.supports.ts_rtc.present = 1;
		ts78xx_fpga.supports.ts_nand.present = 1;
		ts78xx_fpga.supports.ts_rng.present = 1;
		अवरोध;
	शेष:
		/* enable devices अगर magic matches */
		चयन ((ts78xx_fpga.id >> 8) & 0xffffff) अणु
		हाल TS7800_FPGA_MAGIC:
			pr_warn("unrecognised FPGA revision 0x%.2x\n",
				ts78xx_fpga.id & 0xff);
			ts78xx_fpga.supports.ts_rtc.present = 1;
			ts78xx_fpga.supports.ts_nand.present = 1;
			ts78xx_fpga.supports.ts_rng.present = 1;
			अवरोध;
		शेष:
			ts78xx_fpga.supports.ts_rtc.present = 0;
			ts78xx_fpga.supports.ts_nand.present = 0;
			ts78xx_fpga.supports.ts_rng.present = 0;
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक ts78xx_fpga_load_devices(व्योम)
अणु
	पूर्णांक पंचांगp, ret = 0;

	अगर (ts78xx_fpga.supports.ts_rtc.present == 1) अणु
		पंचांगp = ts78xx_ts_rtc_load();
		अगर (पंचांगp)
			ts78xx_fpga.supports.ts_rtc.present = 0;
		ret |= पंचांगp;
	पूर्ण
	अगर (ts78xx_fpga.supports.ts_nand.present == 1) अणु
		पंचांगp = ts78xx_ts_nand_load();
		अगर (पंचांगp)
			ts78xx_fpga.supports.ts_nand.present = 0;
		ret |= पंचांगp;
	पूर्ण
	अगर (ts78xx_fpga.supports.ts_rng.present == 1) अणु
		पंचांगp = ts78xx_ts_rng_load();
		अगर (पंचांगp)
			ts78xx_fpga.supports.ts_rng.present = 0;
		ret |= पंचांगp;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक ts78xx_fpga_unload_devices(व्योम)
अणु

	अगर (ts78xx_fpga.supports.ts_rtc.present == 1)
		ts78xx_ts_rtc_unload();
	अगर (ts78xx_fpga.supports.ts_nand.present == 1)
		ts78xx_ts_nand_unload();
	अगर (ts78xx_fpga.supports.ts_rng.present == 1)
		ts78xx_ts_rng_unload();

	वापस 0;
पूर्ण

अटल पूर्णांक ts78xx_fpga_load(व्योम)
अणु
	ts78xx_fpga.id = पढ़ोl(TS78XX_FPGA_REGS_VIRT_BASE);

	pr_info("FPGA magic=0x%.6x, rev=0x%.2x\n",
			(ts78xx_fpga.id >> 8) & 0xffffff,
			ts78xx_fpga.id & 0xff);

	ts78xx_fpga_supports();

	अगर (ts78xx_fpga_load_devices()) अणु
		ts78xx_fpga.state = -1;
		वापस -EBUSY;
	पूर्ण

	वापस 0;
पूर्ण;

अटल पूर्णांक ts78xx_fpga_unload(व्योम)
अणु
	अचिन्हित पूर्णांक fpga_id;

	fpga_id = पढ़ोl(TS78XX_FPGA_REGS_VIRT_BASE);

	/*
	 * There करोes not seem to be a feasible way to block access to the GPIO
	 * pins from userspace (/dev/mem).  This अगर clause should hopefully warn
	 * those foolish enough not to follow 'policy' :)
	 *
	 * UrJTAG SVN since r1381 can be used to reprogram the FPGA
	 */
	अगर (ts78xx_fpga.id != fpga_id) अणु
		pr_err("FPGA magic/rev mismatch\n"
			"TS-78xx FPGA: was 0x%.6x/%.2x but now 0x%.6x/%.2x\n",
			(ts78xx_fpga.id >> 8) & 0xffffff, ts78xx_fpga.id & 0xff,
			(fpga_id >> 8) & 0xffffff, fpga_id & 0xff);
		ts78xx_fpga.state = -1;
		वापस -EBUSY;
	पूर्ण

	अगर (ts78xx_fpga_unload_devices()) अणु
		ts78xx_fpga.state = -1;
		वापस -EBUSY;
	पूर्ण

	वापस 0;
पूर्ण;

अटल sमाप_प्रकार ts78xx_fpga_show(काष्ठा kobject *kobj,
			काष्ठा kobj_attribute *attr, अक्षर *buf)
अणु
	अगर (ts78xx_fpga.state < 0)
		वापस प्र_लिखो(buf, "borked\n");

	वापस प्र_लिखो(buf, "%s\n", (ts78xx_fpga.state) ? "online" : "offline");
पूर्ण

अटल sमाप_प्रकार ts78xx_fpga_store(काष्ठा kobject *kobj,
			काष्ठा kobj_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार n)
अणु
	पूर्णांक value, ret;

	अगर (ts78xx_fpga.state < 0) अणु
		pr_err("FPGA borked, you must powercycle ASAP\n");
		वापस -EBUSY;
	पूर्ण

	अगर (म_भेदन(buf, "online", माप("online") - 1) == 0)
		value = 1;
	अन्यथा अगर (म_भेदन(buf, "offline", माप("offline") - 1) == 0)
		value = 0;
	अन्यथा
		वापस -EINVAL;

	अगर (ts78xx_fpga.state == value)
		वापस n;

	ret = (ts78xx_fpga.state == 0)
		? ts78xx_fpga_load()
		: ts78xx_fpga_unload();

	अगर (!(ret < 0))
		ts78xx_fpga.state = value;

	वापस n;
पूर्ण

अटल काष्ठा kobj_attribute ts78xx_fpga_attr =
	__ATTR(ts78xx_fpga, 0644, ts78xx_fpga_show, ts78xx_fpga_store);

/*****************************************************************************
 * General Setup
 ****************************************************************************/
अटल अचिन्हित पूर्णांक ts78xx_mpp_modes[] __initdata = अणु
	MPP0_UNUSED,
	MPP1_GPIO,		/* JTAG Clock */
	MPP2_GPIO,		/* JTAG Data In */
	MPP3_GPIO,		/* Lat ECP2 256 FPGA - PB2B */
	MPP4_GPIO,		/* JTAG Data Out */
	MPP5_GPIO,		/* JTAG TMS */
	MPP6_GPIO,		/* Lat ECP2 256 FPGA - PB31A_CLK4+ */
	MPP7_GPIO,		/* Lat ECP2 256 FPGA - PB22B */
	MPP8_UNUSED,
	MPP9_UNUSED,
	MPP10_UNUSED,
	MPP11_UNUSED,
	MPP12_UNUSED,
	MPP13_UNUSED,
	MPP14_UNUSED,
	MPP15_UNUSED,
	MPP16_UART,
	MPP17_UART,
	MPP18_UART,
	MPP19_UART,
	/*
	 * MPP[20] PCI Clock Out 1
	 * MPP[21] PCI Clock Out 0
	 * MPP[22] Unused
	 * MPP[23] Unused
	 * MPP[24] Unused
	 * MPP[25] Unused
	 */
	0,
पूर्ण;

अटल व्योम __init ts78xx_init(व्योम)
अणु
	पूर्णांक ret;

	/*
	 * Setup basic Orion functions. Need to be called early.
	 */
	orion5x_init();

	orion5x_mpp_conf(ts78xx_mpp_modes);

	/*
	 * Configure peripherals.
	 */
	orion5x_ehci0_init();
	orion5x_ehci1_init();
	orion5x_eth_init(&ts78xx_eth_data);
	orion5x_sata_init(&ts78xx_sata_data);
	orion5x_uart0_init();
	orion5x_uart1_init();
	orion5x_xor_init();

	/* FPGA init */
	ts78xx_fpga_devices_zero_init();
	ret = ts78xx_fpga_load();
	ret = sysfs_create_file(firmware_kobj, &ts78xx_fpga_attr.attr);
	अगर (ret)
		pr_err("sysfs_create_file failed: %d\n", ret);
पूर्ण

MACHINE_START(TS78XX, "Technologic Systems TS-78xx SBC")
	/* Maपूर्णांकainer: Alexander Clouter <alex@digriz.org.uk> */
	.atag_offset	= 0x100,
	.nr_irqs	= ORION5X_NR_IRQS,
	.init_machine	= ts78xx_init,
	.map_io		= ts78xx_map_io,
	.init_early	= orion5x_init_early,
	.init_irq	= orion5x_init_irq,
	.init_समय	= orion5x_समयr_init,
	.restart	= orion5x_restart,
MACHINE_END
