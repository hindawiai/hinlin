<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  cx18 firmware functions
 *
 *  Copyright (C) 2007  Hans Verkuil <hverkuil@xs4all.nl>
 *  Copyright (C) 2008  Andy Walls <awalls@md.metrocast.net>
 */

#समावेश "cx18-driver.h"
#समावेश "cx18-io.h"
#समावेश "cx18-scb.h"
#समावेश "cx18-irq.h"
#समावेश "cx18-firmware.h"
#समावेश "cx18-cards.h"
#समावेश <linux/firmware.h>

#घोषणा CX18_PROC_SOFT_RESET		0xc70010
#घोषणा CX18_DDR_SOFT_RESET		0xc70014
#घोषणा CX18_CLOCK_SELECT1		0xc71000
#घोषणा CX18_CLOCK_SELECT2		0xc71004
#घोषणा CX18_HALF_CLOCK_SELECT1		0xc71008
#घोषणा CX18_HALF_CLOCK_SELECT2		0xc7100C
#घोषणा CX18_CLOCK_POLARITY1		0xc71010
#घोषणा CX18_CLOCK_POLARITY2		0xc71014
#घोषणा CX18_ADD_DELAY_ENABLE1		0xc71018
#घोषणा CX18_ADD_DELAY_ENABLE2		0xc7101C
#घोषणा CX18_CLOCK_ENABLE1		0xc71020
#घोषणा CX18_CLOCK_ENABLE2		0xc71024

#घोषणा CX18_REG_BUS_TIMEOUT_EN		0xc72024

#घोषणा CX18_FAST_CLOCK_PLL_INT		0xc78000
#घोषणा CX18_FAST_CLOCK_PLL_FRAC	0xc78004
#घोषणा CX18_FAST_CLOCK_PLL_POST	0xc78008
#घोषणा CX18_FAST_CLOCK_PLL_PRESCALE	0xc7800C
#घोषणा CX18_FAST_CLOCK_PLL_ADJUST_BANDWIDTH 0xc78010

#घोषणा CX18_SLOW_CLOCK_PLL_INT		0xc78014
#घोषणा CX18_SLOW_CLOCK_PLL_FRAC	0xc78018
#घोषणा CX18_SLOW_CLOCK_PLL_POST	0xc7801C
#घोषणा CX18_MPEG_CLOCK_PLL_INT		0xc78040
#घोषणा CX18_MPEG_CLOCK_PLL_FRAC	0xc78044
#घोषणा CX18_MPEG_CLOCK_PLL_POST	0xc78048
#घोषणा CX18_PLL_POWER_DOWN		0xc78088
#घोषणा CX18_SW1_INT_STATUS             0xc73104
#घोषणा CX18_SW1_INT_ENABLE_PCI         0xc7311C
#घोषणा CX18_SW2_INT_SET                0xc73140
#घोषणा CX18_SW2_INT_STATUS             0xc73144
#घोषणा CX18_ADEC_CONTROL		0xc78120

#घोषणा CX18_DDR_REQUEST_ENABLE		0xc80000
#घोषणा CX18_DDR_CHIP_CONFIG		0xc80004
#घोषणा CX18_DDR_REFRESH		0xc80008
#घोषणा CX18_DDR_TIMING1		0xc8000C
#घोषणा CX18_DDR_TIMING2		0xc80010
#घोषणा CX18_DDR_POWER_REG		0xc8001C

#घोषणा CX18_DDR_TUNE_LANE		0xc80048
#घोषणा CX18_DDR_INITIAL_EMRS		0xc80054
#घोषणा CX18_DDR_MB_PER_ROW_7		0xc8009C
#घोषणा CX18_DDR_BASE_63_ADDR		0xc804FC

#घोषणा CX18_WMB_CLIENT02		0xc90108
#घोषणा CX18_WMB_CLIENT05		0xc90114
#घोषणा CX18_WMB_CLIENT06		0xc90118
#घोषणा CX18_WMB_CLIENT07		0xc9011C
#घोषणा CX18_WMB_CLIENT08		0xc90120
#घोषणा CX18_WMB_CLIENT09		0xc90124
#घोषणा CX18_WMB_CLIENT10		0xc90128
#घोषणा CX18_WMB_CLIENT11		0xc9012C
#घोषणा CX18_WMB_CLIENT12		0xc90130
#घोषणा CX18_WMB_CLIENT13		0xc90134
#घोषणा CX18_WMB_CLIENT14		0xc90138

#घोषणा CX18_DSP0_INTERRUPT_MASK	0xd0004C

#घोषणा APU_ROM_SYNC1 0x6D676553 /* "mgeS" */
#घोषणा APU_ROM_SYNC2 0x72646548 /* "rdeH" */

काष्ठा cx18_apu_rom_seghdr अणु
	u32 sync1;
	u32 sync2;
	u32 addr;
	u32 size;
पूर्ण;

अटल पूर्णांक load_cpu_fw_direct(स्थिर अक्षर *fn, u8 __iomem *mem, काष्ठा cx18 *cx)
अणु
	स्थिर काष्ठा firmware *fw = शून्य;
	पूर्णांक i, j;
	अचिन्हित size;
	u32 __iomem *dst = (u32 __iomem *)mem;
	स्थिर u32 *src;

	अगर (request_firmware(&fw, fn, &cx->pci_dev->dev)) अणु
		CX18_ERR("Unable to open firmware %s\n", fn);
		CX18_ERR("Did you put the firmware in the hotplug firmware directory?\n");
		वापस -ENOMEM;
	पूर्ण

	src = (स्थिर u32 *)fw->data;

	क्रम (i = 0; i < fw->size; i += 4096) अणु
		cx18_setup_page(cx, i);
		क्रम (j = i; j < fw->size && j < i + 4096; j += 4) अणु
			/* no need क्रम endianness conversion on the ppc */
			cx18_raw_ग_लिखोl(cx, *src, dst);
			अगर (cx18_raw_पढ़ोl(cx, dst) != *src) अणु
				CX18_ERR("Mismatch at offset %x\n", i);
				release_firmware(fw);
				cx18_setup_page(cx, 0);
				वापस -EIO;
			पूर्ण
			dst++;
			src++;
		पूर्ण
	पूर्ण
	अगर (!test_bit(CX18_F_I_LOADED_FW, &cx->i_flags))
		CX18_INFO("loaded %s firmware (%zu bytes)\n", fn, fw->size);
	size = fw->size;
	release_firmware(fw);
	cx18_setup_page(cx, SCB_OFFSET);
	वापस size;
पूर्ण

अटल पूर्णांक load_apu_fw_direct(स्थिर अक्षर *fn, u8 __iomem *dst, काष्ठा cx18 *cx,
				u32 *entry_addr)
अणु
	स्थिर काष्ठा firmware *fw = शून्य;
	पूर्णांक i, j;
	अचिन्हित size;
	स्थिर u32 *src;
	काष्ठा cx18_apu_rom_seghdr seghdr;
	स्थिर u8 *vers;
	u32 offset = 0;
	u32 apu_version = 0;
	पूर्णांक sz;

	अगर (request_firmware(&fw, fn, &cx->pci_dev->dev)) अणु
		CX18_ERR("unable to open firmware %s\n", fn);
		CX18_ERR("did you put the firmware in the hotplug firmware directory?\n");
		cx18_setup_page(cx, 0);
		वापस -ENOMEM;
	पूर्ण

	*entry_addr = 0;
	src = (स्थिर u32 *)fw->data;
	vers = fw->data + माप(seghdr);
	sz = fw->size;

	apu_version = (vers[0] << 24) | (vers[4] << 16) | vers[32];
	जबतक (offset + माप(seghdr) < fw->size) अणु
		स्थिर __le32 *shptr = (__क्रमce __le32 *)src + offset / 4;

		seghdr.sync1 = le32_to_cpu(shptr[0]);
		seghdr.sync2 = le32_to_cpu(shptr[1]);
		seghdr.addr = le32_to_cpu(shptr[2]);
		seghdr.size = le32_to_cpu(shptr[3]);

		offset += माप(seghdr);
		अगर (seghdr.sync1 != APU_ROM_SYNC1 ||
		    seghdr.sync2 != APU_ROM_SYNC2) अणु
			offset += seghdr.size;
			जारी;
		पूर्ण
		CX18_DEBUG_INFO("load segment %x-%x\n", seghdr.addr,
				seghdr.addr + seghdr.size - 1);
		अगर (*entry_addr == 0)
			*entry_addr = seghdr.addr;
		अगर (offset + seghdr.size > sz)
			अवरोध;
		क्रम (i = 0; i < seghdr.size; i += 4096) अणु
			cx18_setup_page(cx, seghdr.addr + i);
			क्रम (j = i; j < seghdr.size && j < i + 4096; j += 4) अणु
				/* no need क्रम endianness conversion on the ppc */
				cx18_raw_ग_लिखोl(cx, src[(offset + j) / 4],
						dst + seghdr.addr + j);
				अगर (cx18_raw_पढ़ोl(cx, dst + seghdr.addr + j)
				    != src[(offset + j) / 4]) अणु
					CX18_ERR("Mismatch at offset %x\n",
						 offset + j);
					release_firmware(fw);
					cx18_setup_page(cx, 0);
					वापस -EIO;
				पूर्ण
			पूर्ण
		पूर्ण
		offset += seghdr.size;
	पूर्ण
	अगर (!test_bit(CX18_F_I_LOADED_FW, &cx->i_flags))
		CX18_INFO("loaded %s firmware V%08x (%zu bytes)\n",
				fn, apu_version, fw->size);
	size = fw->size;
	release_firmware(fw);
	cx18_setup_page(cx, 0);
	वापस size;
पूर्ण

व्योम cx18_halt_firmware(काष्ठा cx18 *cx)
अणु
	CX18_DEBUG_INFO("Preparing for firmware halt.\n");
	cx18_ग_लिखो_reg_expect(cx, 0x000F000F, CX18_PROC_SOFT_RESET,
				  0x0000000F, 0x000F000F);
	cx18_ग_लिखो_reg_expect(cx, 0x00020002, CX18_ADEC_CONTROL,
				  0x00000002, 0x00020002);
पूर्ण

व्योम cx18_init_घातer(काष्ठा cx18 *cx, पूर्णांक lowpwr)
अणु
	/* घातer-करोwn Spare and AOM PLLs */
	/* घातer-up fast, slow and mpeg PLLs */
	cx18_ग_लिखो_reg(cx, 0x00000008, CX18_PLL_POWER_DOWN);

	/* ADEC out of sleep */
	cx18_ग_लिखो_reg_expect(cx, 0x00020000, CX18_ADEC_CONTROL,
				  0x00000000, 0x00020002);

	/*
	 * The PLL parameters are based on the बाह्यal crystal frequency that
	 * would ideally be:
	 *
	 * NTSC Color subcarrier freq * 8 =
	 *	4.5 MHz/286 * 455/2 * 8 = 28.63636363... MHz
	 *
	 * The accidents of history and rationale that explain from where this
	 * combination of magic numbers originate can be found in:
	 *
	 * [1] Abrahams, I. C., "Choice of Chrominance Subcarrier Frequency in
	 * the NTSC Standards", Proceedings of the I-R-E, January 1954, pp 79-80
	 *
	 * [2] Abrahams, I. C., "The 'Frequency Interleaving' Principle in the
	 * NTSC Standards", Proceedings of the I-R-E, January 1954, pp 81-83
	 *
	 * As Mike Bradley has rightly poपूर्णांकed out, it's not the exact crystal
	 * frequency that matters, only that all parts of the driver and
	 * firmware are using the same value (बंद to the ideal value).
	 *
	 * Since I have a strong suspicion that, अगर the firmware ever assumes a
	 * crystal value at all, it will assume 28.636360 MHz, the crystal
	 * freq used in calculations in this driver will be:
	 *
	 *	xtal_freq = 28.636360 MHz
	 *
	 * an error of less than 0.13 ppm which is way, way better than any off
	 * the shelf crystal will have क्रम accuracy anyway.
	 *
	 * Below I aim to run the PLLs' VCOs near 400 MHz to minimize errors.
	 *
	 * Many thanks to Jeff Campbell and Mike Bradley क्रम their extensive
	 * investigation, experimentation, testing, and suggested solutions of
	 * of audio/video sync problems with SVideo and CVBS captures.
	 */

	/* the fast घड़ी is at 200/245 MHz */
	/* 1 * xtal_freq * 0x0d.f7df9b8 / 2 = 200 MHz: 400 MHz pre post-भागide*/
	/* 1 * xtal_freq * 0x11.1c71eb8 / 2 = 245 MHz: 490 MHz pre post-भागide*/
	cx18_ग_लिखो_reg(cx, lowpwr ? 0xD : 0x11, CX18_FAST_CLOCK_PLL_INT);
	cx18_ग_लिखो_reg(cx, lowpwr ? 0x1EFBF37 : 0x038E3D7,
						CX18_FAST_CLOCK_PLL_FRAC);

	cx18_ग_लिखो_reg(cx, 2, CX18_FAST_CLOCK_PLL_POST);
	cx18_ग_लिखो_reg(cx, 1, CX18_FAST_CLOCK_PLL_PRESCALE);
	cx18_ग_लिखो_reg(cx, 4, CX18_FAST_CLOCK_PLL_ADJUST_BANDWIDTH);

	/* set slow घड़ी to 125/120 MHz */
	/* xtal_freq * 0x0d.1861a20 / 3 = 125 MHz: 375 MHz beक्रमe post-भागide */
	/* xtal_freq * 0x0c.92493f8 / 3 = 120 MHz: 360 MHz beक्रमe post-भागide */
	cx18_ग_लिखो_reg(cx, lowpwr ? 0xD : 0xC, CX18_SLOW_CLOCK_PLL_INT);
	cx18_ग_लिखो_reg(cx, lowpwr ? 0x30C344 : 0x124927F,
						CX18_SLOW_CLOCK_PLL_FRAC);
	cx18_ग_लिखो_reg(cx, 3, CX18_SLOW_CLOCK_PLL_POST);

	/* mpeg घड़ी pll 54MHz */
	/* xtal_freq * 0xf.15f17f0 / 8 = 54 MHz: 432 MHz beक्रमe post-भागide */
	cx18_ग_लिखो_reg(cx, 0xF, CX18_MPEG_CLOCK_PLL_INT);
	cx18_ग_लिखो_reg(cx, 0x2BE2FE, CX18_MPEG_CLOCK_PLL_FRAC);
	cx18_ग_लिखो_reg(cx, 8, CX18_MPEG_CLOCK_PLL_POST);

	/* Defaults */
	/* APU = SC or SC/2 = 125/62.5 */
	/* EPU = SC = 125 */
	/* DDR = FC = 180 */
	/* ENC = SC = 125 */
	/* AI1 = SC = 125 */
	/* VIM2 = disabled */
	/* PCI = FC/2 = 90 */
	/* AI2 = disabled */
	/* DEMUX = disabled */
	/* AO = SC/2 = 62.5 */
	/* SER = 54MHz */
	/* VFC = disabled */
	/* USB = disabled */

	अगर (lowpwr) अणु
		cx18_ग_लिखो_reg_expect(cx, 0xFFFF0020, CX18_CLOCK_SELECT1,
					  0x00000020, 0xFFFFFFFF);
		cx18_ग_लिखो_reg_expect(cx, 0xFFFF0004, CX18_CLOCK_SELECT2,
					  0x00000004, 0xFFFFFFFF);
	पूर्ण अन्यथा अणु
		/* This करोesn't explicitly set every घड़ी select */
		cx18_ग_लिखो_reg_expect(cx, 0x00060004, CX18_CLOCK_SELECT1,
					  0x00000004, 0x00060006);
		cx18_ग_लिखो_reg_expect(cx, 0x00060006, CX18_CLOCK_SELECT2,
					  0x00000006, 0x00060006);
	पूर्ण

	cx18_ग_लिखो_reg_expect(cx, 0xFFFF0002, CX18_HALF_CLOCK_SELECT1,
				  0x00000002, 0xFFFFFFFF);
	cx18_ग_लिखो_reg_expect(cx, 0xFFFF0104, CX18_HALF_CLOCK_SELECT2,
				  0x00000104, 0xFFFFFFFF);
	cx18_ग_लिखो_reg_expect(cx, 0xFFFF9026, CX18_CLOCK_ENABLE1,
				  0x00009026, 0xFFFFFFFF);
	cx18_ग_लिखो_reg_expect(cx, 0xFFFF3105, CX18_CLOCK_ENABLE2,
				  0x00003105, 0xFFFFFFFF);
पूर्ण

व्योम cx18_init_memory(काष्ठा cx18 *cx)
अणु
	cx18_msleep_समयout(10, 0);
	cx18_ग_लिखो_reg_expect(cx, 0x00010000, CX18_DDR_SOFT_RESET,
				  0x00000000, 0x00010001);
	cx18_msleep_समयout(10, 0);

	cx18_ग_लिखो_reg(cx, cx->card->ddr.chip_config, CX18_DDR_CHIP_CONFIG);

	cx18_msleep_समयout(10, 0);

	cx18_ग_लिखो_reg(cx, cx->card->ddr.refresh, CX18_DDR_REFRESH);
	cx18_ग_लिखो_reg(cx, cx->card->ddr.timing1, CX18_DDR_TIMING1);
	cx18_ग_लिखो_reg(cx, cx->card->ddr.timing2, CX18_DDR_TIMING2);

	cx18_msleep_समयout(10, 0);

	/* Initialize DQS pad समय */
	cx18_ग_लिखो_reg(cx, cx->card->ddr.tune_lane, CX18_DDR_TUNE_LANE);
	cx18_ग_लिखो_reg(cx, cx->card->ddr.initial_emrs, CX18_DDR_INITIAL_EMRS);

	cx18_msleep_समयout(10, 0);

	cx18_ग_लिखो_reg_expect(cx, 0x00020000, CX18_DDR_SOFT_RESET,
				  0x00000000, 0x00020002);
	cx18_msleep_समयout(10, 0);

	/* use घातer-करोwn mode when idle */
	cx18_ग_लिखो_reg(cx, 0x00000010, CX18_DDR_POWER_REG);

	cx18_ग_लिखो_reg_expect(cx, 0x00010001, CX18_REG_BUS_TIMEOUT_EN,
				  0x00000001, 0x00010001);

	cx18_ग_लिखो_reg(cx, 0x48, CX18_DDR_MB_PER_ROW_7);
	cx18_ग_लिखो_reg(cx, 0xE0000, CX18_DDR_BASE_63_ADDR);

	cx18_ग_लिखो_reg(cx, 0x00000101, CX18_WMB_CLIENT02);  /* AO */
	cx18_ग_लिखो_reg(cx, 0x00000101, CX18_WMB_CLIENT09);  /* AI2 */
	cx18_ग_लिखो_reg(cx, 0x00000101, CX18_WMB_CLIENT05);  /* VIM1 */
	cx18_ग_लिखो_reg(cx, 0x00000101, CX18_WMB_CLIENT06);  /* AI1 */
	cx18_ग_लिखो_reg(cx, 0x00000101, CX18_WMB_CLIENT07);  /* 3D comb */
	cx18_ग_लिखो_reg(cx, 0x00000101, CX18_WMB_CLIENT10);  /* ME */
	cx18_ग_लिखो_reg(cx, 0x00000101, CX18_WMB_CLIENT12);  /* ENC */
	cx18_ग_लिखो_reg(cx, 0x00000101, CX18_WMB_CLIENT13);  /* PK */
	cx18_ग_लिखो_reg(cx, 0x00000101, CX18_WMB_CLIENT11);  /* RC */
	cx18_ग_लिखो_reg(cx, 0x00000101, CX18_WMB_CLIENT14);  /* AVO */
पूर्ण

#घोषणा CX18_CPU_FIRMWARE "v4l-cx23418-cpu.fw"
#घोषणा CX18_APU_FIRMWARE "v4l-cx23418-apu.fw"

पूर्णांक cx18_firmware_init(काष्ठा cx18 *cx)
अणु
	u32 fw_entry_addr;
	पूर्णांक sz, retries;
	u32 api_args[MAX_MB_ARGUMENTS];

	/* Allow chip to control CLKRUN */
	cx18_ग_लिखो_reg(cx, 0x5, CX18_DSP0_INTERRUPT_MASK);

	/* Stop the firmware */
	cx18_ग_लिखो_reg_expect(cx, 0x000F000F, CX18_PROC_SOFT_RESET,
				  0x0000000F, 0x000F000F);

	cx18_msleep_समयout(1, 0);

	/* If the CPU is still running */
	अगर ((cx18_पढ़ो_reg(cx, CX18_PROC_SOFT_RESET) & 8) == 0) अणु
		CX18_ERR("%s: couldn't stop CPU to load firmware\n", __func__);
		वापस -EIO;
	पूर्ण

	cx18_sw1_irq_enable(cx, IRQ_CPU_TO_EPU | IRQ_APU_TO_EPU);
	cx18_sw2_irq_enable(cx, IRQ_CPU_TO_EPU_ACK | IRQ_APU_TO_EPU_ACK);

	sz = load_cpu_fw_direct(CX18_CPU_FIRMWARE, cx->enc_mem, cx);
	अगर (sz <= 0)
		वापस sz;

	/* The SCB & IPC area *must* be correct beक्रमe starting the firmwares */
	cx18_init_scb(cx);

	fw_entry_addr = 0;
	sz = load_apu_fw_direct(CX18_APU_FIRMWARE, cx->enc_mem, cx,
				&fw_entry_addr);
	अगर (sz <= 0)
		वापस sz;

	/* Start the CPU. The CPU will take care of the APU क्रम us. */
	cx18_ग_लिखो_reg_expect(cx, 0x00080000, CX18_PROC_SOFT_RESET,
				  0x00000000, 0x00080008);

	/* Wait up to 500 ms क्रम the APU to come out of reset */
	क्रम (retries = 0;
	     retries < 50 && (cx18_पढ़ो_reg(cx, CX18_PROC_SOFT_RESET) & 1) == 1;
	     retries++)
		cx18_msleep_समयout(10, 0);

	cx18_msleep_समयout(200, 0);

	अगर (retries == 50 &&
	    (cx18_पढ़ो_reg(cx, CX18_PROC_SOFT_RESET) & 1) == 1) अणु
		CX18_ERR("Could not start the CPU\n");
		वापस -EIO;
	पूर्ण

	/*
	 * The CPU had once beक्रमe set up to receive an पूर्णांकerrupt क्रम it's
	 * outgoing IRQ_CPU_TO_EPU_ACK to us.  If it ever करोes this, we get an
	 * पूर्णांकerrupt when it sends us an ack, but by the समय we process it,
	 * that flag in the SW2 status रेजिस्टर has been cleared by the CPU
	 * firmware.  We'll prevent that not so useful condition from happening
	 * by clearing the CPU's interrupt enables for Ack IRQ's we want to
	 * process.
	 */
	cx18_sw2_irq_disable_cpu(cx, IRQ_CPU_TO_EPU_ACK | IRQ_APU_TO_EPU_ACK);

	/* Try a benign command to see अगर the CPU is alive and well */
	sz = cx18_vapi_result(cx, api_args, CX18_CPU_DEBUG_PEEK32, 1, 0);
	अगर (sz < 0)
		वापस sz;

	/* initialize GPIO */
	cx18_ग_लिखो_reg_expect(cx, 0x14001400, 0xc78110, 0x00001400, 0x14001400);
	वापस 0;
पूर्ण

MODULE_FIRMWARE(CX18_CPU_FIRMWARE);
MODULE_FIRMWARE(CX18_APU_FIRMWARE);
