<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * This file contains work-arounds क्रम many known PCI hardware bugs.
 * Devices present only on certain architectures (host bridges et cetera)
 * should be handled in arch-specअगरic code.
 *
 * Note: any quirks क्रम hotpluggable devices must _NOT_ be declared __init.
 *
 * Copyright (c) 1999 Martin Mares <mj@ucw.cz>
 *
 * Init/reset quirks क्रम USB host controllers should be in the USB quirks
 * file, where their drivers can use them.
 */

#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/export.h>
#समावेश <linux/pci.h>
#समावेश <linux/init.h>
#समावेश <linux/delay.h>
#समावेश <linux/acpi.h>
#समावेश <linux/dmi.h>
#समावेश <linux/ioport.h>
#समावेश <linux/sched.h>
#समावेश <linux/kसमय.स>
#समावेश <linux/mm.h>
#समावेश <linux/nvme.h>
#समावेश <linux/platक्रमm_data/x86/apple.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/चयनtec.h>
#समावेश <यंत्र/dma.h>	/* isa_dma_bridge_buggy */
#समावेश "pci.h"

अटल kसमय_प्रकार fixup_debug_start(काष्ठा pci_dev *dev,
				 व्योम (*fn)(काष्ठा pci_dev *dev))
अणु
	अगर (initcall_debug)
		pci_info(dev, "calling  %pS @ %i\n", fn, task_pid_nr(current));

	वापस kसमय_get();
पूर्ण

अटल व्योम fixup_debug_report(काष्ठा pci_dev *dev, kसमय_प्रकार callसमय,
			       व्योम (*fn)(काष्ठा pci_dev *dev))
अणु
	kसमय_प्रकार delta, retसमय;
	अचिन्हित दीर्घ दीर्घ duration;

	retसमय = kसमय_get();
	delta = kसमय_sub(retसमय, callसमय);
	duration = (अचिन्हित दीर्घ दीर्घ) kसमय_प्रकारo_ns(delta) >> 10;
	अगर (initcall_debug || duration > 10000)
		pci_info(dev, "%pS took %lld usecs\n", fn, duration);
पूर्ण

अटल व्योम pci_करो_fixups(काष्ठा pci_dev *dev, काष्ठा pci_fixup *f,
			  काष्ठा pci_fixup *end)
अणु
	kसमय_प्रकार callसमय;

	क्रम (; f < end; f++)
		अगर ((f->class == (u32) (dev->class >> f->class_shअगरt) ||
		     f->class == (u32) PCI_ANY_ID) &&
		    (f->venकरोr == dev->venकरोr ||
		     f->venकरोr == (u16) PCI_ANY_ID) &&
		    (f->device == dev->device ||
		     f->device == (u16) PCI_ANY_ID)) अणु
			व्योम (*hook)(काष्ठा pci_dev *dev);
#अगर_घोषित CONFIG_HAVE_ARCH_PREL32_RELOCATIONS
			hook = offset_to_ptr(&f->hook_offset);
#अन्यथा
			hook = f->hook;
#पूर्ण_अगर
			callसमय = fixup_debug_start(dev, hook);
			hook(dev);
			fixup_debug_report(dev, callसमय, hook);
		पूर्ण
पूर्ण

बाह्य काष्ठा pci_fixup __start_pci_fixups_early[];
बाह्य काष्ठा pci_fixup __end_pci_fixups_early[];
बाह्य काष्ठा pci_fixup __start_pci_fixups_header[];
बाह्य काष्ठा pci_fixup __end_pci_fixups_header[];
बाह्य काष्ठा pci_fixup __start_pci_fixups_final[];
बाह्य काष्ठा pci_fixup __end_pci_fixups_final[];
बाह्य काष्ठा pci_fixup __start_pci_fixups_enable[];
बाह्य काष्ठा pci_fixup __end_pci_fixups_enable[];
बाह्य काष्ठा pci_fixup __start_pci_fixups_resume[];
बाह्य काष्ठा pci_fixup __end_pci_fixups_resume[];
बाह्य काष्ठा pci_fixup __start_pci_fixups_resume_early[];
बाह्य काष्ठा pci_fixup __end_pci_fixups_resume_early[];
बाह्य काष्ठा pci_fixup __start_pci_fixups_suspend[];
बाह्य काष्ठा pci_fixup __end_pci_fixups_suspend[];
बाह्य काष्ठा pci_fixup __start_pci_fixups_suspend_late[];
बाह्य काष्ठा pci_fixup __end_pci_fixups_suspend_late[];

अटल bool pci_apply_fixup_final_quirks;

व्योम pci_fixup_device(क्रमागत pci_fixup_pass pass, काष्ठा pci_dev *dev)
अणु
	काष्ठा pci_fixup *start, *end;

	चयन (pass) अणु
	हाल pci_fixup_early:
		start = __start_pci_fixups_early;
		end = __end_pci_fixups_early;
		अवरोध;

	हाल pci_fixup_header:
		start = __start_pci_fixups_header;
		end = __end_pci_fixups_header;
		अवरोध;

	हाल pci_fixup_final:
		अगर (!pci_apply_fixup_final_quirks)
			वापस;
		start = __start_pci_fixups_final;
		end = __end_pci_fixups_final;
		अवरोध;

	हाल pci_fixup_enable:
		start = __start_pci_fixups_enable;
		end = __end_pci_fixups_enable;
		अवरोध;

	हाल pci_fixup_resume:
		start = __start_pci_fixups_resume;
		end = __end_pci_fixups_resume;
		अवरोध;

	हाल pci_fixup_resume_early:
		start = __start_pci_fixups_resume_early;
		end = __end_pci_fixups_resume_early;
		अवरोध;

	हाल pci_fixup_suspend:
		start = __start_pci_fixups_suspend;
		end = __end_pci_fixups_suspend;
		अवरोध;

	हाल pci_fixup_suspend_late:
		start = __start_pci_fixups_suspend_late;
		end = __end_pci_fixups_suspend_late;
		अवरोध;

	शेष:
		/* stupid compiler warning, you would think with an क्रमागत... */
		वापस;
	पूर्ण
	pci_करो_fixups(dev, start, end);
पूर्ण
EXPORT_SYMBOL(pci_fixup_device);

अटल पूर्णांक __init pci_apply_final_quirks(व्योम)
अणु
	काष्ठा pci_dev *dev = शून्य;
	u8 cls = 0;
	u8 पंचांगp;

	अगर (pci_cache_line_size)
		pr_info("PCI: CLS %u bytes\n", pci_cache_line_size << 2);

	pci_apply_fixup_final_quirks = true;
	क्रम_each_pci_dev(dev) अणु
		pci_fixup_device(pci_fixup_final, dev);
		/*
		 * If arch hasn't set it explicitly yet, use the CLS
		 * value shared by all PCI devices.  If there's a
		 * mismatch, fall back to the शेष value.
		 */
		अगर (!pci_cache_line_size) अणु
			pci_पढ़ो_config_byte(dev, PCI_CACHE_LINE_SIZE, &पंचांगp);
			अगर (!cls)
				cls = पंचांगp;
			अगर (!पंचांगp || cls == पंचांगp)
				जारी;

			pci_info(dev, "CLS mismatch (%u != %u), using %u bytes\n",
			         cls << 2, पंचांगp << 2,
				 pci_dfl_cache_line_size << 2);
			pci_cache_line_size = pci_dfl_cache_line_size;
		पूर्ण
	पूर्ण

	अगर (!pci_cache_line_size) अणु
		pr_info("PCI: CLS %u bytes, default %u\n", cls << 2,
			pci_dfl_cache_line_size << 2);
		pci_cache_line_size = cls ? cls : pci_dfl_cache_line_size;
	पूर्ण

	वापस 0;
पूर्ण
fs_initcall_sync(pci_apply_final_quirks);

/*
 * Decoding should be disabled क्रम a PCI device during BAR sizing to aव्योम
 * conflict. But करोing so may cause problems on host bridge and perhaps other
 * key प्रणाली devices. For devices that need to have mmio decoding always-on,
 * we need to set the dev->mmio_always_on bit.
 */
अटल व्योम quirk_mmio_always_on(काष्ठा pci_dev *dev)
अणु
	dev->mmio_always_on = 1;
पूर्ण
DECLARE_PCI_FIXUP_CLASS_EARLY(PCI_ANY_ID, PCI_ANY_ID,
				PCI_CLASS_BRIDGE_HOST, 8, quirk_mmio_always_on);

/*
 * The Mellanox Tavor device gives false positive parity errors.  Disable
 * parity error reporting.
 */
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_MELLANOX, PCI_DEVICE_ID_MELLANOX_TAVOR, pci_disable_parity);
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_MELLANOX, PCI_DEVICE_ID_MELLANOX_TAVOR_BRIDGE, pci_disable_parity);

/*
 * Deal with broken BIOSes that neglect to enable passive release,
 * which can cause problems in combination with the 82441FX/PPro MTRRs
 */
अटल व्योम quirk_passive_release(काष्ठा pci_dev *dev)
अणु
	काष्ठा pci_dev *d = शून्य;
	अचिन्हित अक्षर dlc;

	/*
	 * We have to make sure a particular bit is set in the PIIX3
	 * ISA bridge, so we have to go out and find it.
	 */
	जबतक ((d = pci_get_device(PCI_VENDOR_ID_INTEL, PCI_DEVICE_ID_INTEL_82371SB_0, d))) अणु
		pci_पढ़ो_config_byte(d, 0x82, &dlc);
		अगर (!(dlc & 1<<1)) अणु
			pci_info(d, "PIIX3: Enabling Passive Release\n");
			dlc |= 1<<1;
			pci_ग_लिखो_config_byte(d, 0x82, dlc);
		पूर्ण
	पूर्ण
पूर्ण
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_INTEL,	PCI_DEVICE_ID_INTEL_82441,	quirk_passive_release);
DECLARE_PCI_FIXUP_RESUME(PCI_VENDOR_ID_INTEL,	PCI_DEVICE_ID_INTEL_82441,	quirk_passive_release);

/*
 * The VIA VP2/VP3/MVP3 seem to have some 'features'. There may be a
 * workaround but VIA करोn't answer queries. If you happen to have good
 * contacts at VIA ask them क्रम me please -- Alan
 *
 * This appears to be BIOS not version dependent. So presumably there is a
 * chipset level fix.
 */
अटल व्योम quirk_isa_dma_hangs(काष्ठा pci_dev *dev)
अणु
	अगर (!isa_dma_bridge_buggy) अणु
		isa_dma_bridge_buggy = 1;
		pci_info(dev, "Activating ISA DMA hang workarounds\n");
	पूर्ण
पूर्ण
/*
 * It's not totally clear which chipsets are the problematic ones.  We know
 * 82C586 and 82C596 variants are affected.
 */
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_VIA,	PCI_DEVICE_ID_VIA_82C586_0,	quirk_isa_dma_hangs);
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_VIA,	PCI_DEVICE_ID_VIA_82C596,	quirk_isa_dma_hangs);
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_INTEL,    PCI_DEVICE_ID_INTEL_82371SB_0,  quirk_isa_dma_hangs);
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_AL,	PCI_DEVICE_ID_AL_M1533,		quirk_isa_dma_hangs);
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_NEC,	PCI_DEVICE_ID_NEC_CBUS_1,	quirk_isa_dma_hangs);
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_NEC,	PCI_DEVICE_ID_NEC_CBUS_2,	quirk_isa_dma_hangs);
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_NEC,	PCI_DEVICE_ID_NEC_CBUS_3,	quirk_isa_dma_hangs);

/*
 * Intel NM10 "TigerPoint" LPC PM1a_STS.BM_STS must be clear
 * क्रम some HT machines to use C4 w/o hanging.
 */
अटल व्योम quirk_tigerpoपूर्णांक_bm_sts(काष्ठा pci_dev *dev)
अणु
	u32 pmbase;
	u16 pm1a;

	pci_पढ़ो_config_dword(dev, 0x40, &pmbase);
	pmbase = pmbase & 0xff80;
	pm1a = inw(pmbase);

	अगर (pm1a & 0x10) अणु
		pci_info(dev, FW_BUG "TigerPoint LPC.BM_STS cleared\n");
		outw(0x10, pmbase);
	पूर्ण
पूर्ण
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_INTEL, PCI_DEVICE_ID_INTEL_TGP_LPC, quirk_tigerpoपूर्णांक_bm_sts);

/* Chipsets where PCI->PCI transfers vanish or hang */
अटल व्योम quirk_nopcipci(काष्ठा pci_dev *dev)
अणु
	अगर ((pci_pci_problems & PCIPCI_FAIL) == 0) अणु
		pci_info(dev, "Disabling direct PCI/PCI transfers\n");
		pci_pci_problems |= PCIPCI_FAIL;
	पूर्ण
पूर्ण
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_SI,	PCI_DEVICE_ID_SI_5597,		quirk_nopcipci);
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_SI,	PCI_DEVICE_ID_SI_496,		quirk_nopcipci);

अटल व्योम quirk_nopciamd(काष्ठा pci_dev *dev)
अणु
	u8 rev;
	pci_पढ़ो_config_byte(dev, 0x08, &rev);
	अगर (rev == 0x13) अणु
		/* Erratum 24 */
		pci_info(dev, "Chipset erratum: Disabling direct PCI/AGP transfers\n");
		pci_pci_problems |= PCIAGP_FAIL;
	पूर्ण
पूर्ण
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_AMD,	PCI_DEVICE_ID_AMD_8151_0,	quirk_nopciamd);

/* Triton requires workarounds to be used by the drivers */
अटल व्योम quirk_triton(काष्ठा pci_dev *dev)
अणु
	अगर ((pci_pci_problems&PCIPCI_TRITON) == 0) अणु
		pci_info(dev, "Limiting direct PCI/PCI transfers\n");
		pci_pci_problems |= PCIPCI_TRITON;
	पूर्ण
पूर्ण
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_INTEL,	PCI_DEVICE_ID_INTEL_82437,	quirk_triton);
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_INTEL,	PCI_DEVICE_ID_INTEL_82437VX,	quirk_triton);
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_INTEL,	PCI_DEVICE_ID_INTEL_82439,	quirk_triton);
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_INTEL,	PCI_DEVICE_ID_INTEL_82439TX,	quirk_triton);

/*
 * VIA Apollo KT133 needs PCI latency patch
 * Made according to a Winकरोws driver-based patch by George E. Breese;
 * see PCI Latency Adjust on http://www.viahardware.com/करोwnload/viatweak.shपंचांग
 * Also see http://www.au-ja.org/review-kt133a-1-en.phपंचांगl क्रम the info on
 * which Mr Breese based his work.
 *
 * Updated based on further inक्रमmation from the site and also on
 * inक्रमmation provided by VIA
 */
अटल व्योम quirk_vialatency(काष्ठा pci_dev *dev)
अणु
	काष्ठा pci_dev *p;
	u8 busarb;

	/*
	 * Ok, we have a potential problem chipset here. Now see अगर we have
	 * a buggy southbridge.
	 */
	p = pci_get_device(PCI_VENDOR_ID_VIA, PCI_DEVICE_ID_VIA_82C686, शून्य);
	अगर (p != शून्य) अणु

		/*
		 * 0x40 - 0x4f == 686B, 0x10 - 0x2f == 686A;
		 * thanks Dan Hollis.
		 * Check क्रम buggy part revisions
		 */
		अगर (p->revision < 0x40 || p->revision > 0x42)
			जाओ निकास;
	पूर्ण अन्यथा अणु
		p = pci_get_device(PCI_VENDOR_ID_VIA, PCI_DEVICE_ID_VIA_8231, शून्य);
		अगर (p == शून्य)	/* No problem parts */
			जाओ निकास;

		/* Check क्रम buggy part revisions */
		अगर (p->revision < 0x10 || p->revision > 0x12)
			जाओ निकास;
	पूर्ण

	/*
	 * Ok we have the problem. Now set the PCI master grant to occur
	 * every master grant. The apparent bug is that under high PCI load
	 * (quite common in Linux of course) you can get data loss when the
	 * CPU is held off the bus क्रम 3 bus master requests.  This happens
	 * to include the IDE controllers....
	 *
	 * VIA only apply this fix when an SB Live! is present but under
	 * both Linux and Winकरोws this isn't enough, and we have seen
	 * corruption without SB Live! but with things like 3 UDMA IDE
	 * controllers. So we ignore that bit of the VIA recommendation..
	 */
	pci_पढ़ो_config_byte(dev, 0x76, &busarb);

	/*
	 * Set bit 4 and bit 5 of byte 76 to 0x01
	 * "Master priority rotation on every PCI master grant"
	 */
	busarb &= ~(1<<5);
	busarb |= (1<<4);
	pci_ग_लिखो_config_byte(dev, 0x76, busarb);
	pci_info(dev, "Applying VIA southbridge workaround\n");
निकास:
	pci_dev_put(p);
पूर्ण
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_VIA,	PCI_DEVICE_ID_VIA_8363_0,	quirk_vialatency);
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_VIA,	PCI_DEVICE_ID_VIA_8371_1,	quirk_vialatency);
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_VIA,	PCI_DEVICE_ID_VIA_8361,		quirk_vialatency);
/* Must restore this on a resume from RAM */
DECLARE_PCI_FIXUP_RESUME(PCI_VENDOR_ID_VIA,	PCI_DEVICE_ID_VIA_8363_0,	quirk_vialatency);
DECLARE_PCI_FIXUP_RESUME(PCI_VENDOR_ID_VIA,	PCI_DEVICE_ID_VIA_8371_1,	quirk_vialatency);
DECLARE_PCI_FIXUP_RESUME(PCI_VENDOR_ID_VIA,	PCI_DEVICE_ID_VIA_8361,		quirk_vialatency);

/* VIA Apollo VP3 needs ETBF on BT848/878 */
अटल व्योम quirk_viaetbf(काष्ठा pci_dev *dev)
अणु
	अगर ((pci_pci_problems&PCIPCI_VIAETBF) == 0) अणु
		pci_info(dev, "Limiting direct PCI/PCI transfers\n");
		pci_pci_problems |= PCIPCI_VIAETBF;
	पूर्ण
पूर्ण
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_VIA,	PCI_DEVICE_ID_VIA_82C597_0,	quirk_viaetbf);

अटल व्योम quirk_vsfx(काष्ठा pci_dev *dev)
अणु
	अगर ((pci_pci_problems&PCIPCI_VSFX) == 0) अणु
		pci_info(dev, "Limiting direct PCI/PCI transfers\n");
		pci_pci_problems |= PCIPCI_VSFX;
	पूर्ण
पूर्ण
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_VIA,	PCI_DEVICE_ID_VIA_82C576,	quirk_vsfx);

/*
 * ALi Magik requires workarounds to be used by the drivers that DMA to AGP
 * space. Latency must be set to 0xA and Triton workaround applied too.
 * [Info kindly provided by ALi]
 */
अटल व्योम quirk_alimagik(काष्ठा pci_dev *dev)
अणु
	अगर ((pci_pci_problems&PCIPCI_ALIMAGIK) == 0) अणु
		pci_info(dev, "Limiting direct PCI/PCI transfers\n");
		pci_pci_problems |= PCIPCI_ALIMAGIK|PCIPCI_TRITON;
	पूर्ण
पूर्ण
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_AL,	PCI_DEVICE_ID_AL_M1647,		quirk_alimagik);
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_AL,	PCI_DEVICE_ID_AL_M1651,		quirk_alimagik);

/* Natoma has some पूर्णांकeresting boundary conditions with Zoran stuff at least */
अटल व्योम quirk_natoma(काष्ठा pci_dev *dev)
अणु
	अगर ((pci_pci_problems&PCIPCI_NATOMA) == 0) अणु
		pci_info(dev, "Limiting direct PCI/PCI transfers\n");
		pci_pci_problems |= PCIPCI_NATOMA;
	पूर्ण
पूर्ण
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_INTEL,	PCI_DEVICE_ID_INTEL_82441,	quirk_natoma);
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_INTEL,	PCI_DEVICE_ID_INTEL_82443LX_0,	quirk_natoma);
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_INTEL,	PCI_DEVICE_ID_INTEL_82443LX_1,	quirk_natoma);
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_INTEL,	PCI_DEVICE_ID_INTEL_82443BX_0,	quirk_natoma);
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_INTEL,	PCI_DEVICE_ID_INTEL_82443BX_1,	quirk_natoma);
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_INTEL,	PCI_DEVICE_ID_INTEL_82443BX_2,	quirk_natoma);

/*
 * This chip can cause PCI parity errors अगर config रेजिस्टर 0xA0 is पढ़ो
 * जबतक DMAs are occurring.
 */
अटल व्योम quirk_citrine(काष्ठा pci_dev *dev)
अणु
	dev->cfg_size = 0xA0;
पूर्ण
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_IBM,	PCI_DEVICE_ID_IBM_CITRINE,	quirk_citrine);

/*
 * This chip can cause bus lockups अगर config addresses above 0x600
 * are पढ़ो or written.
 */
अटल व्योम quirk_nfp6000(काष्ठा pci_dev *dev)
अणु
	dev->cfg_size = 0x600;
पूर्ण
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_NETRONOME,	PCI_DEVICE_ID_NETRONOME_NFP4000,	quirk_nfp6000);
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_NETRONOME,	PCI_DEVICE_ID_NETRONOME_NFP6000,	quirk_nfp6000);
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_NETRONOME,	PCI_DEVICE_ID_NETRONOME_NFP5000,	quirk_nfp6000);
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_NETRONOME,	PCI_DEVICE_ID_NETRONOME_NFP6000_VF,	quirk_nfp6000);

/*  On IBM Crocodile ipr SAS adapters, expand BAR to प्रणाली page size */
अटल व्योम quirk_extend_bar_to_page(काष्ठा pci_dev *dev)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < PCI_STD_NUM_BARS; i++) अणु
		काष्ठा resource *r = &dev->resource[i];

		अगर (r->flags & IORESOURCE_MEM && resource_size(r) < PAGE_SIZE) अणु
			r->end = PAGE_SIZE - 1;
			r->start = 0;
			r->flags |= IORESOURCE_UNSET;
			pci_info(dev, "expanded BAR %d to page size: %pR\n",
				 i, r);
		पूर्ण
	पूर्ण
पूर्ण
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_IBM, 0x034a, quirk_extend_bar_to_page);

/*
 * S3 868 and 968 chips report region size equal to 32M, but they decode 64M.
 * If it's needed, re-allocate the region.
 */
अटल व्योम quirk_s3_64M(काष्ठा pci_dev *dev)
अणु
	काष्ठा resource *r = &dev->resource[0];

	अगर ((r->start & 0x3ffffff) || r->end != r->start + 0x3ffffff) अणु
		r->flags |= IORESOURCE_UNSET;
		r->start = 0;
		r->end = 0x3ffffff;
	पूर्ण
पूर्ण
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_S3,	PCI_DEVICE_ID_S3_868,		quirk_s3_64M);
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_S3,	PCI_DEVICE_ID_S3_968,		quirk_s3_64M);

अटल व्योम quirk_io(काष्ठा pci_dev *dev, पूर्णांक pos, अचिन्हित size,
		     स्थिर अक्षर *name)
अणु
	u32 region;
	काष्ठा pci_bus_region bus_region;
	काष्ठा resource *res = dev->resource + pos;

	pci_पढ़ो_config_dword(dev, PCI_BASE_ADDRESS_0 + (pos << 2), &region);

	अगर (!region)
		वापस;

	res->name = pci_name(dev);
	res->flags = region & ~PCI_BASE_ADDRESS_IO_MASK;
	res->flags |=
		(IORESOURCE_IO | IORESOURCE_PCI_FIXED | IORESOURCE_SIZEALIGN);
	region &= ~(size - 1);

	/* Convert from PCI bus to resource space */
	bus_region.start = region;
	bus_region.end = region + size - 1;
	pcibios_bus_to_resource(dev->bus, res, &bus_region);

	pci_info(dev, FW_BUG "%s quirk: reg 0x%x: %pR\n",
		 name, PCI_BASE_ADDRESS_0 + (pos << 2), res);
पूर्ण

/*
 * Some CS5536 BIOSes (क्रम example, the Soekris NET5501 board w/ comBIOS
 * ver. 1.33  20070103) करोn't set the correct ISA PCI region header info.
 * BAR0 should be 8 bytes; instead, it may be set to something like 8k
 * (which conflicts w/ BAR1's memory range).
 *
 * CS553x's ISA PCI BARs may also be पढ़ो-only (ref:
 * https://bugzilla.kernel.org/show_bug.cgi?id=85991 - Comment #4 क्रमward).
 */
अटल व्योम quirk_cs5536_vsa(काष्ठा pci_dev *dev)
अणु
	अटल अक्षर *name = "CS5536 ISA bridge";

	अगर (pci_resource_len(dev, 0) != 8) अणु
		quirk_io(dev, 0,   8, name);	/* SMB */
		quirk_io(dev, 1, 256, name);	/* GPIO */
		quirk_io(dev, 2,  64, name);	/* MFGPT */
		pci_info(dev, "%s bug detected (incorrect header); workaround applied\n",
			 name);
	पूर्ण
पूर्ण
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_AMD, PCI_DEVICE_ID_AMD_CS5536_ISA, quirk_cs5536_vsa);

अटल व्योम quirk_io_region(काष्ठा pci_dev *dev, पूर्णांक port,
				अचिन्हित size, पूर्णांक nr, स्थिर अक्षर *name)
अणु
	u16 region;
	काष्ठा pci_bus_region bus_region;
	काष्ठा resource *res = dev->resource + nr;

	pci_पढ़ो_config_word(dev, port, &region);
	region &= ~(size - 1);

	अगर (!region)
		वापस;

	res->name = pci_name(dev);
	res->flags = IORESOURCE_IO;

	/* Convert from PCI bus to resource space */
	bus_region.start = region;
	bus_region.end = region + size - 1;
	pcibios_bus_to_resource(dev->bus, res, &bus_region);

	अगर (!pci_claim_resource(dev, nr))
		pci_info(dev, "quirk: %pR claimed by %s\n", res, name);
पूर्ण

/*
 * ATI Northbridge setups MCE the processor अगर you even पढ़ो somewhere
 * between 0x3b0->0x3bb or पढ़ो 0x3d3
 */
अटल व्योम quirk_ati_exploding_mce(काष्ठा pci_dev *dev)
अणु
	pci_info(dev, "ATI Northbridge, reserving I/O ports 0x3b0 to 0x3bb\n");
	/* Mae rhaid i ni beidio ag edrych ar y lleoliadiau I/O hyn */
	request_region(0x3b0, 0x0C, "RadeonIGP");
	request_region(0x3d3, 0x01, "RadeonIGP");
पूर्ण
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_ATI,	PCI_DEVICE_ID_ATI_RS100,   quirk_ati_exploding_mce);

/*
 * In the AMD NL platक्रमm, this device ([1022:7912]) has a class code of
 * PCI_CLASS_SERIAL_USB_XHCI (0x0c0330), which means the xhci driver will
 * claim it.
 *
 * But the dwc3 driver is a more specअगरic driver क्रम this device, and we'd
 * prefer to use it instead of xhci. To prevent xhci from claiming the
 * device, change the class code to 0x0c03fe, which the PCI r3.0 spec
 * defines as "USB device (not host controller)". The dwc3 driver can then
 * claim it based on its Venकरोr and Device ID.
 */
अटल व्योम quirk_amd_nl_class(काष्ठा pci_dev *pdev)
अणु
	u32 class = pdev->class;

	/* Use "USB Device (not host controller)" class */
	pdev->class = PCI_CLASS_SERIAL_USB_DEVICE;
	pci_info(pdev, "PCI class overridden (%#08x -> %#08x) so dwc3 driver can claim this instead of xhci\n",
		 class, pdev->class);
पूर्ण
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_AMD, PCI_DEVICE_ID_AMD_NL_USB,
		quirk_amd_nl_class);

/*
 * Synopsys USB 3.x host HAPS platक्रमm has a class code of
 * PCI_CLASS_SERIAL_USB_XHCI, and xhci driver can claim it.  However, these
 * devices should use dwc3-haps driver.  Change these devices' class code to
 * PCI_CLASS_SERIAL_USB_DEVICE to prevent the xhci-pci driver from claiming
 * them.
 */
अटल व्योम quirk_synopsys_haps(काष्ठा pci_dev *pdev)
अणु
	u32 class = pdev->class;

	चयन (pdev->device) अणु
	हाल PCI_DEVICE_ID_SYNOPSYS_HAPSUSB3:
	हाल PCI_DEVICE_ID_SYNOPSYS_HAPSUSB3_AXI:
	हाल PCI_DEVICE_ID_SYNOPSYS_HAPSUSB31:
		pdev->class = PCI_CLASS_SERIAL_USB_DEVICE;
		pci_info(pdev, "PCI class overridden (%#08x -> %#08x) so dwc3 driver can claim this instead of xhci\n",
			 class, pdev->class);
		अवरोध;
	पूर्ण
पूर्ण
DECLARE_PCI_FIXUP_CLASS_HEADER(PCI_VENDOR_ID_SYNOPSYS, PCI_ANY_ID,
			       PCI_CLASS_SERIAL_USB_XHCI, 0,
			       quirk_synopsys_haps);

/*
 * Let's make the southbridge inक्रमmation explicit instead of having to
 * worry about people probing the ACPI areas, क्रम example.. (Yes, it
 * happens, and अगर you पढ़ो the wrong ACPI रेजिस्टर it will put the machine
 * to sleep with no way of waking it up again. Bummer).
 *
 * ALI M7101: Two IO regions poपूर्णांकed to by words at
 *	0xE0 (64 bytes of ACPI रेजिस्टरs)
 *	0xE2 (32 bytes of SMB रेजिस्टरs)
 */
अटल व्योम quirk_ali7101_acpi(काष्ठा pci_dev *dev)
अणु
	quirk_io_region(dev, 0xE0, 64, PCI_BRIDGE_RESOURCES, "ali7101 ACPI");
	quirk_io_region(dev, 0xE2, 32, PCI_BRIDGE_RESOURCES+1, "ali7101 SMB");
पूर्ण
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_AL,	PCI_DEVICE_ID_AL_M7101,		quirk_ali7101_acpi);

अटल व्योम piix4_io_quirk(काष्ठा pci_dev *dev, स्थिर अक्षर *name, अचिन्हित पूर्णांक port, अचिन्हित पूर्णांक enable)
अणु
	u32 devres;
	u32 mask, size, base;

	pci_पढ़ो_config_dword(dev, port, &devres);
	अगर ((devres & enable) != enable)
		वापस;
	mask = (devres >> 16) & 15;
	base = devres & 0xffff;
	size = 16;
	क्रम (;;) अणु
		अचिन्हित bit = size >> 1;
		अगर ((bit & mask) == bit)
			अवरोध;
		size = bit;
	पूर्ण
	/*
	 * For now we only prपूर्णांक it out. Eventually we'll want to
	 * reserve it (at least अगर it's in the 0x1000+ range), but
	 * let's get enough confirmation reports first.
	 */
	base &= -size;
	pci_info(dev, "%s PIO at %04x-%04x\n", name, base, base + size - 1);
पूर्ण

अटल व्योम piix4_mem_quirk(काष्ठा pci_dev *dev, स्थिर अक्षर *name, अचिन्हित पूर्णांक port, अचिन्हित पूर्णांक enable)
अणु
	u32 devres;
	u32 mask, size, base;

	pci_पढ़ो_config_dword(dev, port, &devres);
	अगर ((devres & enable) != enable)
		वापस;
	base = devres & 0xffff0000;
	mask = (devres & 0x3f) << 16;
	size = 128 << 16;
	क्रम (;;) अणु
		अचिन्हित bit = size >> 1;
		अगर ((bit & mask) == bit)
			अवरोध;
		size = bit;
	पूर्ण

	/*
	 * For now we only prपूर्णांक it out. Eventually we'll want to
	 * reserve it, but let's get enough confirmation reports first.
	 */
	base &= -size;
	pci_info(dev, "%s MMIO at %04x-%04x\n", name, base, base + size - 1);
पूर्ण

/*
 * PIIX4 ACPI: Two IO regions poपूर्णांकed to by दीर्घwords at
 *	0x40 (64 bytes of ACPI रेजिस्टरs)
 *	0x90 (16 bytes of SMB रेजिस्टरs)
 * and a few strange programmable PIIX4 device resources.
 */
अटल व्योम quirk_piix4_acpi(काष्ठा pci_dev *dev)
अणु
	u32 res_a;

	quirk_io_region(dev, 0x40, 64, PCI_BRIDGE_RESOURCES, "PIIX4 ACPI");
	quirk_io_region(dev, 0x90, 16, PCI_BRIDGE_RESOURCES+1, "PIIX4 SMB");

	/* Device resource A has enables क्रम some of the other ones */
	pci_पढ़ो_config_dword(dev, 0x5c, &res_a);

	piix4_io_quirk(dev, "PIIX4 devres B", 0x60, 3 << 21);
	piix4_io_quirk(dev, "PIIX4 devres C", 0x64, 3 << 21);

	/* Device resource D is just bitfields क्रम अटल resources */

	/* Device 12 enabled? */
	अगर (res_a & (1 << 29)) अणु
		piix4_io_quirk(dev, "PIIX4 devres E", 0x68, 1 << 20);
		piix4_mem_quirk(dev, "PIIX4 devres F", 0x6c, 1 << 7);
	पूर्ण
	/* Device 13 enabled? */
	अगर (res_a & (1 << 30)) अणु
		piix4_io_quirk(dev, "PIIX4 devres G", 0x70, 1 << 20);
		piix4_mem_quirk(dev, "PIIX4 devres H", 0x74, 1 << 7);
	पूर्ण
	piix4_io_quirk(dev, "PIIX4 devres I", 0x78, 1 << 20);
	piix4_io_quirk(dev, "PIIX4 devres J", 0x7c, 1 << 20);
पूर्ण
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_INTEL,	PCI_DEVICE_ID_INTEL_82371AB_3,	quirk_piix4_acpi);
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_INTEL,	PCI_DEVICE_ID_INTEL_82443MX_3,	quirk_piix4_acpi);

#घोषणा ICH_PMBASE	0x40
#घोषणा ICH_ACPI_CNTL	0x44
#घोषणा  ICH4_ACPI_EN	0x10
#घोषणा  ICH6_ACPI_EN	0x80
#घोषणा ICH4_GPIOBASE	0x58
#घोषणा ICH4_GPIO_CNTL	0x5c
#घोषणा  ICH4_GPIO_EN	0x10
#घोषणा ICH6_GPIOBASE	0x48
#घोषणा ICH6_GPIO_CNTL	0x4c
#घोषणा  ICH6_GPIO_EN	0x10

/*
 * ICH4, ICH4-M, ICH5, ICH5-M ACPI: Three IO regions poपूर्णांकed to by दीर्घwords at
 *	0x40 (128 bytes of ACPI, GPIO & TCO रेजिस्टरs)
 *	0x58 (64 bytes of GPIO I/O space)
 */
अटल व्योम quirk_ich4_lpc_acpi(काष्ठा pci_dev *dev)
अणु
	u8 enable;

	/*
	 * The check क्रम PCIBIOS_MIN_IO is to ensure we won't create a conflict
	 * with low legacy (and fixed) ports. We करोn't know the decoding
	 * priority and can't tell whether the legacy device or the one created
	 * here is really at that address.  This happens on boards with broken
	 * BIOSes.
	 */
	pci_पढ़ो_config_byte(dev, ICH_ACPI_CNTL, &enable);
	अगर (enable & ICH4_ACPI_EN)
		quirk_io_region(dev, ICH_PMBASE, 128, PCI_BRIDGE_RESOURCES,
				 "ICH4 ACPI/GPIO/TCO");

	pci_पढ़ो_config_byte(dev, ICH4_GPIO_CNTL, &enable);
	अगर (enable & ICH4_GPIO_EN)
		quirk_io_region(dev, ICH4_GPIOBASE, 64, PCI_BRIDGE_RESOURCES+1,
				"ICH4 GPIO");
पूर्ण
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_INTEL,    PCI_DEVICE_ID_INTEL_82801AA_0,		quirk_ich4_lpc_acpi);
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_INTEL,    PCI_DEVICE_ID_INTEL_82801AB_0,		quirk_ich4_lpc_acpi);
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_INTEL,    PCI_DEVICE_ID_INTEL_82801BA_0,		quirk_ich4_lpc_acpi);
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_INTEL,    PCI_DEVICE_ID_INTEL_82801BA_10,	quirk_ich4_lpc_acpi);
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_INTEL,    PCI_DEVICE_ID_INTEL_82801CA_0,		quirk_ich4_lpc_acpi);
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_INTEL,    PCI_DEVICE_ID_INTEL_82801CA_12,	quirk_ich4_lpc_acpi);
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_INTEL,    PCI_DEVICE_ID_INTEL_82801DB_0,		quirk_ich4_lpc_acpi);
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_INTEL,    PCI_DEVICE_ID_INTEL_82801DB_12,	quirk_ich4_lpc_acpi);
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_INTEL,    PCI_DEVICE_ID_INTEL_82801EB_0,		quirk_ich4_lpc_acpi);
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_INTEL,    PCI_DEVICE_ID_INTEL_ESB_1,		quirk_ich4_lpc_acpi);

अटल व्योम ich6_lpc_acpi_gpio(काष्ठा pci_dev *dev)
अणु
	u8 enable;

	pci_पढ़ो_config_byte(dev, ICH_ACPI_CNTL, &enable);
	अगर (enable & ICH6_ACPI_EN)
		quirk_io_region(dev, ICH_PMBASE, 128, PCI_BRIDGE_RESOURCES,
				 "ICH6 ACPI/GPIO/TCO");

	pci_पढ़ो_config_byte(dev, ICH6_GPIO_CNTL, &enable);
	अगर (enable & ICH6_GPIO_EN)
		quirk_io_region(dev, ICH6_GPIOBASE, 64, PCI_BRIDGE_RESOURCES+1,
				"ICH6 GPIO");
पूर्ण

अटल व्योम ich6_lpc_generic_decode(काष्ठा pci_dev *dev, अचिन्हित reg,
				    स्थिर अक्षर *name, पूर्णांक dynsize)
अणु
	u32 val;
	u32 size, base;

	pci_पढ़ो_config_dword(dev, reg, &val);

	/* Enabled? */
	अगर (!(val & 1))
		वापस;
	base = val & 0xfffc;
	अगर (dynsize) अणु
		/*
		 * This is not correct. It is 16, 32 or 64 bytes depending on
		 * रेजिस्टर D31:F0:ADh bits 5:4.
		 *
		 * But this माला_लो us at least _part_ of it.
		 */
		size = 16;
	पूर्ण अन्यथा अणु
		size = 128;
	पूर्ण
	base &= ~(size-1);

	/*
	 * Just prपूर्णांक it out क्रम now. We should reserve it after more
	 * debugging.
	 */
	pci_info(dev, "%s PIO at %04x-%04x\n", name, base, base+size-1);
पूर्ण

अटल व्योम quirk_ich6_lpc(काष्ठा pci_dev *dev)
अणु
	/* Shared ACPI/GPIO decode with all ICH6+ */
	ich6_lpc_acpi_gpio(dev);

	/* ICH6-specअगरic generic IO decode */
	ich6_lpc_generic_decode(dev, 0x84, "LPC Generic IO decode 1", 0);
	ich6_lpc_generic_decode(dev, 0x88, "LPC Generic IO decode 2", 1);
पूर्ण
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_INTEL,	PCI_DEVICE_ID_INTEL_ICH6_0, quirk_ich6_lpc);
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_INTEL,	PCI_DEVICE_ID_INTEL_ICH6_1, quirk_ich6_lpc);

अटल व्योम ich7_lpc_generic_decode(काष्ठा pci_dev *dev, अचिन्हित reg,
				    स्थिर अक्षर *name)
अणु
	u32 val;
	u32 mask, base;

	pci_पढ़ो_config_dword(dev, reg, &val);

	/* Enabled? */
	अगर (!(val & 1))
		वापस;

	/* IO base in bits 15:2, mask in bits 23:18, both are dword-based */
	base = val & 0xfffc;
	mask = (val >> 16) & 0xfc;
	mask |= 3;

	/*
	 * Just prपूर्णांक it out क्रम now. We should reserve it after more
	 * debugging.
	 */
	pci_info(dev, "%s PIO at %04x (mask %04x)\n", name, base, mask);
पूर्ण

/* ICH7-10 has the same common LPC generic IO decode रेजिस्टरs */
अटल व्योम quirk_ich7_lpc(काष्ठा pci_dev *dev)
अणु
	/* We share the common ACPI/GPIO decode with ICH6 */
	ich6_lpc_acpi_gpio(dev);

	/* And have 4 ICH7+ generic decodes */
	ich7_lpc_generic_decode(dev, 0x84, "ICH7 LPC Generic IO decode 1");
	ich7_lpc_generic_decode(dev, 0x88, "ICH7 LPC Generic IO decode 2");
	ich7_lpc_generic_decode(dev, 0x8c, "ICH7 LPC Generic IO decode 3");
	ich7_lpc_generic_decode(dev, 0x90, "ICH7 LPC Generic IO decode 4");
पूर्ण
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_INTEL,	PCI_DEVICE_ID_INTEL_ICH7_0, quirk_ich7_lpc);
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_INTEL,	PCI_DEVICE_ID_INTEL_ICH7_1, quirk_ich7_lpc);
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_INTEL,	PCI_DEVICE_ID_INTEL_ICH7_31, quirk_ich7_lpc);
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_INTEL,	PCI_DEVICE_ID_INTEL_ICH8_0, quirk_ich7_lpc);
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_INTEL,	PCI_DEVICE_ID_INTEL_ICH8_2, quirk_ich7_lpc);
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_INTEL,	PCI_DEVICE_ID_INTEL_ICH8_3, quirk_ich7_lpc);
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_INTEL,	PCI_DEVICE_ID_INTEL_ICH8_1, quirk_ich7_lpc);
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_INTEL,	PCI_DEVICE_ID_INTEL_ICH8_4, quirk_ich7_lpc);
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_INTEL,	PCI_DEVICE_ID_INTEL_ICH9_2, quirk_ich7_lpc);
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_INTEL,	PCI_DEVICE_ID_INTEL_ICH9_4, quirk_ich7_lpc);
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_INTEL,	PCI_DEVICE_ID_INTEL_ICH9_7, quirk_ich7_lpc);
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_INTEL,	PCI_DEVICE_ID_INTEL_ICH9_8, quirk_ich7_lpc);
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_INTEL,   PCI_DEVICE_ID_INTEL_ICH10_1, quirk_ich7_lpc);

/*
 * VIA ACPI: One IO region poपूर्णांकed to by दीर्घword at
 *	0x48 or 0x20 (256 bytes of ACPI रेजिस्टरs)
 */
अटल व्योम quirk_vt82c586_acpi(काष्ठा pci_dev *dev)
अणु
	अगर (dev->revision & 0x10)
		quirk_io_region(dev, 0x48, 256, PCI_BRIDGE_RESOURCES,
				"vt82c586 ACPI");
पूर्ण
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_VIA,	PCI_DEVICE_ID_VIA_82C586_3,	quirk_vt82c586_acpi);

/*
 * VIA VT82C686 ACPI: Three IO region poपूर्णांकed to by (दीर्घ)words at
 *	0x48 (256 bytes of ACPI रेजिस्टरs)
 *	0x70 (128 bytes of hardware monitoring रेजिस्टर)
 *	0x90 (16 bytes of SMB रेजिस्टरs)
 */
अटल व्योम quirk_vt82c686_acpi(काष्ठा pci_dev *dev)
अणु
	quirk_vt82c586_acpi(dev);

	quirk_io_region(dev, 0x70, 128, PCI_BRIDGE_RESOURCES+1,
				 "vt82c686 HW-mon");

	quirk_io_region(dev, 0x90, 16, PCI_BRIDGE_RESOURCES+2, "vt82c686 SMB");
पूर्ण
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_VIA,	PCI_DEVICE_ID_VIA_82C686_4,	quirk_vt82c686_acpi);

/*
 * VIA VT8235 ISA Bridge: Two IO regions poपूर्णांकed to by words at
 *	0x88 (128 bytes of घातer management रेजिस्टरs)
 *	0xd0 (16 bytes of SMB रेजिस्टरs)
 */
अटल व्योम quirk_vt8235_acpi(काष्ठा pci_dev *dev)
अणु
	quirk_io_region(dev, 0x88, 128, PCI_BRIDGE_RESOURCES, "vt8235 PM");
	quirk_io_region(dev, 0xd0, 16, PCI_BRIDGE_RESOURCES+1, "vt8235 SMB");
पूर्ण
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_VIA,	PCI_DEVICE_ID_VIA_8235,	quirk_vt8235_acpi);

/*
 * TI XIO2000a PCIe-PCI Bridge erroneously reports it supports fast
 * back-to-back: Disable fast back-to-back on the secondary bus segment
 */
अटल व्योम quirk_xio2000a(काष्ठा pci_dev *dev)
अणु
	काष्ठा pci_dev *pdev;
	u16 command;

	pci_warn(dev, "TI XIO2000a quirk detected; secondary bus fast back-to-back transfers disabled\n");
	list_क्रम_each_entry(pdev, &dev->subordinate->devices, bus_list) अणु
		pci_पढ़ो_config_word(pdev, PCI_COMMAND, &command);
		अगर (command & PCI_COMMAND_FAST_BACK)
			pci_ग_लिखो_config_word(pdev, PCI_COMMAND, command & ~PCI_COMMAND_FAST_BACK);
	पूर्ण
पूर्ण
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_TI, PCI_DEVICE_ID_TI_XIO2000A,
			quirk_xio2000a);

#अगर_घोषित CONFIG_X86_IO_APIC

#समावेश <यंत्र/io_apic.h>

/*
 * VIA 686A/B: If an IO-APIC is active, we need to route all on-chip
 * devices to the बाह्यal APIC.
 *
 * TODO: When we have device-specअगरic पूर्णांकerrupt routers, this code will go
 * away from quirks.
 */
अटल व्योम quirk_via_ioapic(काष्ठा pci_dev *dev)
अणु
	u8 पंचांगp;

	अगर (nr_ioapics < 1)
		पंचांगp = 0;    /* nothing routed to बाह्यal APIC */
	अन्यथा
		पंचांगp = 0x1f; /* all known bits (4-0) routed to बाह्यal APIC */

	pci_info(dev, "%sbling VIA external APIC routing\n",
	       पंचांगp == 0 ? "Disa" : "Ena");

	/* Offset 0x58: External APIC IRQ output control */
	pci_ग_लिखो_config_byte(dev, 0x58, पंचांगp);
पूर्ण
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_VIA,	PCI_DEVICE_ID_VIA_82C686,	quirk_via_ioapic);
DECLARE_PCI_FIXUP_RESUME_EARLY(PCI_VENDOR_ID_VIA,	PCI_DEVICE_ID_VIA_82C686,	quirk_via_ioapic);

/*
 * VIA 8237: Some BIOSes करोn't set the 'Bypass APIC De-Assert Message' Bit.
 * This leads to द्विगुनd level पूर्णांकerrupt rates.
 * Set this bit to get rid of cycle wastage.
 * Otherwise uncritical.
 */
अटल व्योम quirk_via_vt8237_bypass_apic_deनिश्चित(काष्ठा pci_dev *dev)
अणु
	u8 misc_control2;
#घोषणा BYPASS_APIC_DEASSERT 8

	pci_पढ़ो_config_byte(dev, 0x5B, &misc_control2);
	अगर (!(misc_control2 & BYPASS_APIC_DEASSERT)) अणु
		pci_info(dev, "Bypassing VIA 8237 APIC De-Assert Message\n");
		pci_ग_लिखो_config_byte(dev, 0x5B, misc_control2|BYPASS_APIC_DEASSERT);
	पूर्ण
पूर्ण
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_VIA,	PCI_DEVICE_ID_VIA_8237,		quirk_via_vt8237_bypass_apic_deनिश्चित);
DECLARE_PCI_FIXUP_RESUME_EARLY(PCI_VENDOR_ID_VIA,	PCI_DEVICE_ID_VIA_8237,		quirk_via_vt8237_bypass_apic_deनिश्चित);

/*
 * The AMD IO-APIC can hang the box when an APIC IRQ is masked.
 * We check all revs >= B0 (yet not in the pre production!) as the bug
 * is currently marked NoFix
 *
 * We have multiple reports of hangs with this chipset that went away with
 * noapic specअगरied. For the moment we assume it's the erratum. We may be wrong
 * of course. However the advice is demonstrably good even अगर so.
 */
अटल व्योम quirk_amd_ioapic(काष्ठा pci_dev *dev)
अणु
	अगर (dev->revision >= 0x02) अणु
		pci_warn(dev, "I/O APIC: AMD Erratum #22 may be present. In the event of instability try\n");
		pci_warn(dev, "        : booting with the \"noapic\" option\n");
	पूर्ण
पूर्ण
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_AMD,	PCI_DEVICE_ID_AMD_VIPER_7410,	quirk_amd_ioapic);
#पूर्ण_अगर /* CONFIG_X86_IO_APIC */

#अगर defined(CONFIG_ARM64) && defined(CONFIG_PCI_ATS)

अटल व्योम quirk_cavium_sriov_rnm_link(काष्ठा pci_dev *dev)
अणु
	/* Fix क्रम improper SR-IOV configuration on Cavium cn88xx RNM device */
	अगर (dev->subप्रणाली_device == 0xa118)
		dev->sriov->link = dev->devfn;
पूर्ण
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_CAVIUM, 0xa018, quirk_cavium_sriov_rnm_link);
#पूर्ण_अगर

/*
 * Some settings of MMRBC can lead to data corruption so block changes.
 * See AMD 8131 HyperTransport PCI-X Tunnel Revision Guide
 */
अटल व्योम quirk_amd_8131_mmrbc(काष्ठा pci_dev *dev)
अणु
	अगर (dev->subordinate && dev->revision <= 0x12) अणु
		pci_info(dev, "AMD8131 rev %x detected; disabling PCI-X MMRBC\n",
			 dev->revision);
		dev->subordinate->bus_flags |= PCI_BUS_FLAGS_NO_MMRBC;
	पूर्ण
पूर्ण
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_AMD, PCI_DEVICE_ID_AMD_8131_BRIDGE, quirk_amd_8131_mmrbc);

/*
 * FIXME: it is questionable that quirk_via_acpi() is needed.  It shows up
 * as an ISA bridge, and करोes not support the PCI_INTERRUPT_LINE रेजिस्टर
 * at all.  Thereक्रमe it seems like setting the pci_dev's IRQ to the value
 * of the ACPI SCI पूर्णांकerrupt is only करोne क्रम convenience.
 *	-jgarzik
 */
अटल व्योम quirk_via_acpi(काष्ठा pci_dev *d)
अणु
	u8 irq;

	/* VIA ACPI device: SCI IRQ line in PCI config byte 0x42 */
	pci_पढ़ो_config_byte(d, 0x42, &irq);
	irq &= 0xf;
	अगर (irq && (irq != 2))
		d->irq = irq;
पूर्ण
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_VIA,	PCI_DEVICE_ID_VIA_82C586_3,	quirk_via_acpi);
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_VIA,	PCI_DEVICE_ID_VIA_82C686_4,	quirk_via_acpi);

/* VIA bridges which have VLink */
अटल पूर्णांक via_vlink_dev_lo = -1, via_vlink_dev_hi = 18;

अटल व्योम quirk_via_bridge(काष्ठा pci_dev *dev)
अणु
	/* See what bridge we have and find the device ranges */
	चयन (dev->device) अणु
	हाल PCI_DEVICE_ID_VIA_82C686:
		/*
		 * The VT82C686 is special; it attaches to PCI and can have
		 * any device number. All its subdevices are functions of
		 * that single device.
		 */
		via_vlink_dev_lo = PCI_SLOT(dev->devfn);
		via_vlink_dev_hi = PCI_SLOT(dev->devfn);
		अवरोध;
	हाल PCI_DEVICE_ID_VIA_8237:
	हाल PCI_DEVICE_ID_VIA_8237A:
		via_vlink_dev_lo = 15;
		अवरोध;
	हाल PCI_DEVICE_ID_VIA_8235:
		via_vlink_dev_lo = 16;
		अवरोध;
	हाल PCI_DEVICE_ID_VIA_8231:
	हाल PCI_DEVICE_ID_VIA_8233_0:
	हाल PCI_DEVICE_ID_VIA_8233A:
	हाल PCI_DEVICE_ID_VIA_8233C_0:
		via_vlink_dev_lo = 17;
		अवरोध;
	पूर्ण
पूर्ण
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_VIA,	PCI_DEVICE_ID_VIA_82C686,	quirk_via_bridge);
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_VIA,	PCI_DEVICE_ID_VIA_8231,		quirk_via_bridge);
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_VIA,	PCI_DEVICE_ID_VIA_8233_0,	quirk_via_bridge);
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_VIA,	PCI_DEVICE_ID_VIA_8233A,	quirk_via_bridge);
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_VIA,	PCI_DEVICE_ID_VIA_8233C_0,	quirk_via_bridge);
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_VIA,	PCI_DEVICE_ID_VIA_8235,		quirk_via_bridge);
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_VIA,	PCI_DEVICE_ID_VIA_8237,		quirk_via_bridge);
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_VIA,	PCI_DEVICE_ID_VIA_8237A,	quirk_via_bridge);

/*
 * quirk_via_vlink		-	VIA VLink IRQ number update
 * @dev: PCI device
 *
 * If the device we are dealing with is on a PIC IRQ we need to ensure that
 * the IRQ line रेजिस्टर which usually is not relevant क्रम PCI cards, is
 * actually written so that पूर्णांकerrupts get sent to the right place.
 *
 * We only करो this on प्रणालीs where a VIA south bridge was detected, and
 * only क्रम VIA devices on the motherboard (see quirk_via_bridge above).
 */
अटल व्योम quirk_via_vlink(काष्ठा pci_dev *dev)
अणु
	u8 irq, new_irq;

	/* Check अगर we have VLink at all */
	अगर (via_vlink_dev_lo == -1)
		वापस;

	new_irq = dev->irq;

	/* Don't quirk पूर्णांकerrupts outside the legacy IRQ range */
	अगर (!new_irq || new_irq > 15)
		वापस;

	/* Internal device ? */
	अगर (dev->bus->number != 0 || PCI_SLOT(dev->devfn) > via_vlink_dev_hi ||
	    PCI_SLOT(dev->devfn) < via_vlink_dev_lo)
		वापस;

	/*
	 * This is an पूर्णांकernal VLink device on a PIC पूर्णांकerrupt. The BIOS
	 * ought to have set this but may not have, so we reकरो it.
	 */
	pci_पढ़ो_config_byte(dev, PCI_INTERRUPT_LINE, &irq);
	अगर (new_irq != irq) अणु
		pci_info(dev, "VIA VLink IRQ fixup, from %d to %d\n",
			irq, new_irq);
		udelay(15);	/* unknown अगर delay really needed */
		pci_ग_लिखो_config_byte(dev, PCI_INTERRUPT_LINE, new_irq);
	पूर्ण
पूर्ण
DECLARE_PCI_FIXUP_ENABLE(PCI_VENDOR_ID_VIA, PCI_ANY_ID, quirk_via_vlink);

/*
 * VIA VT82C598 has its device ID settable and many BIOSes set it to the ID
 * of VT82C597 क्रम backward compatibility.  We need to चयन it off to be
 * able to recognize the real type of the chip.
 */
अटल व्योम quirk_vt82c598_id(काष्ठा pci_dev *dev)
अणु
	pci_ग_लिखो_config_byte(dev, 0xfc, 0);
	pci_पढ़ो_config_word(dev, PCI_DEVICE_ID, &dev->device);
पूर्ण
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_VIA,	PCI_DEVICE_ID_VIA_82C597_0,	quirk_vt82c598_id);

/*
 * CardBus controllers have a legacy base address that enables them to
 * respond as i82365 pcmcia controllers.  We करोn't want them to करो this
 * even अगर the Linux CardBus driver is not loaded, because the Linux i82365
 * driver करोes not (and should not) handle CardBus.
 */
अटल व्योम quirk_cardbus_legacy(काष्ठा pci_dev *dev)
अणु
	pci_ग_लिखो_config_dword(dev, PCI_CB_LEGACY_MODE_BASE, 0);
पूर्ण
DECLARE_PCI_FIXUP_CLASS_FINAL(PCI_ANY_ID, PCI_ANY_ID,
			PCI_CLASS_BRIDGE_CARDBUS, 8, quirk_cardbus_legacy);
DECLARE_PCI_FIXUP_CLASS_RESUME_EARLY(PCI_ANY_ID, PCI_ANY_ID,
			PCI_CLASS_BRIDGE_CARDBUS, 8, quirk_cardbus_legacy);

/*
 * Following the PCI ordering rules is optional on the AMD762. I'm not sure
 * what the designers were smoking but let's not inhale...
 *
 * To be fair to AMD, it follows the spec by शेष, it's BIOS people who
 * turn it off!
 */
अटल व्योम quirk_amd_ordering(काष्ठा pci_dev *dev)
अणु
	u32 pcic;
	pci_पढ़ो_config_dword(dev, 0x4C, &pcic);
	अगर ((pcic & 6) != 6) अणु
		pcic |= 6;
		pci_warn(dev, "BIOS failed to enable PCI standards compliance; fixing this error\n");
		pci_ग_लिखो_config_dword(dev, 0x4C, pcic);
		pci_पढ़ो_config_dword(dev, 0x84, &pcic);
		pcic |= (1 << 23);	/* Required in this mode */
		pci_ग_लिखो_config_dword(dev, 0x84, pcic);
	पूर्ण
पूर्ण
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_AMD,	PCI_DEVICE_ID_AMD_FE_GATE_700C, quirk_amd_ordering);
DECLARE_PCI_FIXUP_RESUME_EARLY(PCI_VENDOR_ID_AMD,	PCI_DEVICE_ID_AMD_FE_GATE_700C, quirk_amd_ordering);

/*
 * DreamWorks-provided workaround क्रम Dunord I-3000 problem
 *
 * This card decodes and responds to addresses not apparently asचिन्हित to
 * it.  We क्रमce a larger allocation to ensure that nothing माला_लो put too
 * बंद to it.
 */
अटल व्योम quirk_dunord(काष्ठा pci_dev *dev)
अणु
	काष्ठा resource *r = &dev->resource[1];

	r->flags |= IORESOURCE_UNSET;
	r->start = 0;
	r->end = 0xffffff;
पूर्ण
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_DUNORD,	PCI_DEVICE_ID_DUNORD_I3000,	quirk_dunord);

/*
 * i82380FB mobile करोcking controller: its PCI-to-PCI bridge is subtractive
 * decoding (transparent), and करोes indicate this in the ProgIf.
 * Unक्रमtunately, the ProgIf value is wrong - 0x80 instead of 0x01.
 */
अटल व्योम quirk_transparent_bridge(काष्ठा pci_dev *dev)
अणु
	dev->transparent = 1;
पूर्ण
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_INTEL,	PCI_DEVICE_ID_INTEL_82380FB,	quirk_transparent_bridge);
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_TOSHIBA,	0x605,	quirk_transparent_bridge);

/*
 * Common misconfiguration of the MediaGX/Geode PCI master that will reduce
 * PCI bandwidth from 70MB/s to 25MB/s.  See the GXM/GXLV/GX1 datasheets
 * found at http://www.national.com/analog क्रम info on what these bits करो.
 * <christer@weinigel.se>
 */
अटल व्योम quirk_mediagx_master(काष्ठा pci_dev *dev)
अणु
	u8 reg;

	pci_पढ़ो_config_byte(dev, 0x41, &reg);
	अगर (reg & 2) अणु
		reg &= ~2;
		pci_info(dev, "Fixup for MediaGX/Geode Slave Disconnect Boundary (0x41=0x%02x)\n",
			 reg);
		pci_ग_लिखो_config_byte(dev, 0x41, reg);
	पूर्ण
पूर्ण
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_CYRIX,	PCI_DEVICE_ID_CYRIX_PCI_MASTER, quirk_mediagx_master);
DECLARE_PCI_FIXUP_RESUME(PCI_VENDOR_ID_CYRIX,	PCI_DEVICE_ID_CYRIX_PCI_MASTER, quirk_mediagx_master);

/*
 * Ensure C0 rev restreaming is off. This is normally करोne by the BIOS but
 * in the odd हाल it is not the results are corruption hence the presence
 * of a Linux check.
 */
अटल व्योम quirk_disable_pxb(काष्ठा pci_dev *pdev)
अणु
	u16 config;

	अगर (pdev->revision != 0x04)		/* Only C0 requires this */
		वापस;
	pci_पढ़ो_config_word(pdev, 0x40, &config);
	अगर (config & (1<<6)) अणु
		config &= ~(1<<6);
		pci_ग_लिखो_config_word(pdev, 0x40, config);
		pci_info(pdev, "C0 revision 450NX. Disabling PCI restreaming\n");
	पूर्ण
पूर्ण
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_INTEL,	PCI_DEVICE_ID_INTEL_82454NX,	quirk_disable_pxb);
DECLARE_PCI_FIXUP_RESUME_EARLY(PCI_VENDOR_ID_INTEL,	PCI_DEVICE_ID_INTEL_82454NX,	quirk_disable_pxb);

अटल व्योम quirk_amd_ide_mode(काष्ठा pci_dev *pdev)
अणु
	/* set SBX00/Hudson-2 SATA in IDE mode to AHCI mode */
	u8 पंचांगp;

	pci_पढ़ो_config_byte(pdev, PCI_CLASS_DEVICE, &पंचांगp);
	अगर (पंचांगp == 0x01) अणु
		pci_पढ़ो_config_byte(pdev, 0x40, &पंचांगp);
		pci_ग_लिखो_config_byte(pdev, 0x40, पंचांगp|1);
		pci_ग_लिखो_config_byte(pdev, 0x9, 1);
		pci_ग_लिखो_config_byte(pdev, 0xa, 6);
		pci_ग_लिखो_config_byte(pdev, 0x40, पंचांगp);

		pdev->class = PCI_CLASS_STORAGE_SATA_AHCI;
		pci_info(pdev, "set SATA to AHCI mode\n");
	पूर्ण
पूर्ण
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_ATI, PCI_DEVICE_ID_ATI_IXP600_SATA, quirk_amd_ide_mode);
DECLARE_PCI_FIXUP_RESUME_EARLY(PCI_VENDOR_ID_ATI, PCI_DEVICE_ID_ATI_IXP600_SATA, quirk_amd_ide_mode);
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_ATI, PCI_DEVICE_ID_ATI_IXP700_SATA, quirk_amd_ide_mode);
DECLARE_PCI_FIXUP_RESUME_EARLY(PCI_VENDOR_ID_ATI, PCI_DEVICE_ID_ATI_IXP700_SATA, quirk_amd_ide_mode);
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_AMD, PCI_DEVICE_ID_AMD_HUDSON2_SATA_IDE, quirk_amd_ide_mode);
DECLARE_PCI_FIXUP_RESUME_EARLY(PCI_VENDOR_ID_AMD, PCI_DEVICE_ID_AMD_HUDSON2_SATA_IDE, quirk_amd_ide_mode);
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_AMD, 0x7900, quirk_amd_ide_mode);
DECLARE_PCI_FIXUP_RESUME_EARLY(PCI_VENDOR_ID_AMD, 0x7900, quirk_amd_ide_mode);

/* Serverworks CSB5 IDE करोes not fully support native mode */
अटल व्योम quirk_svwks_csb5ide(काष्ठा pci_dev *pdev)
अणु
	u8 prog;
	pci_पढ़ो_config_byte(pdev, PCI_CLASS_PROG, &prog);
	अगर (prog & 5) अणु
		prog &= ~5;
		pdev->class &= ~5;
		pci_ग_लिखो_config_byte(pdev, PCI_CLASS_PROG, prog);
		/* PCI layer will sort out resources */
	पूर्ण
पूर्ण
DECLARE_PCI_FIXUP_EARLY(PCI_VENDOR_ID_SERVERWORKS, PCI_DEVICE_ID_SERVERWORKS_CSB5IDE, quirk_svwks_csb5ide);

/* Intel 82801CAM ICH3-M datasheet says IDE modes must be the same */
अटल व्योम quirk_ide_samemode(काष्ठा pci_dev *pdev)
अणु
	u8 prog;

	pci_पढ़ो_config_byte(pdev, PCI_CLASS_PROG, &prog);

	अगर (((prog & 1) && !(prog & 4)) || ((prog & 4) && !(prog & 1))) अणु
		pci_info(pdev, "IDE mode mismatch; forcing legacy mode\n");
		prog &= ~5;
		pdev->class &= ~5;
		pci_ग_लिखो_config_byte(pdev, PCI_CLASS_PROG, prog);
	पूर्ण
पूर्ण
DECLARE_PCI_FIXUP_EARLY(PCI_VENDOR_ID_INTEL, PCI_DEVICE_ID_INTEL_82801CA_10, quirk_ide_samemode);

/* Some ATA devices अवरोध अगर put पूर्णांकo D3 */
अटल व्योम quirk_no_ata_d3(काष्ठा pci_dev *pdev)
अणु
	pdev->dev_flags |= PCI_DEV_FLAGS_NO_D3;
पूर्ण
/* Quirk the legacy ATA devices only. The AHCI ones are ok */
DECLARE_PCI_FIXUP_CLASS_EARLY(PCI_VENDOR_ID_SERVERWORKS, PCI_ANY_ID,
				PCI_CLASS_STORAGE_IDE, 8, quirk_no_ata_d3);
DECLARE_PCI_FIXUP_CLASS_EARLY(PCI_VENDOR_ID_ATI, PCI_ANY_ID,
				PCI_CLASS_STORAGE_IDE, 8, quirk_no_ata_d3);
/* ALi loses some रेजिस्टर settings that we cannot then restore */
DECLARE_PCI_FIXUP_CLASS_EARLY(PCI_VENDOR_ID_AL, PCI_ANY_ID,
				PCI_CLASS_STORAGE_IDE, 8, quirk_no_ata_d3);
/* VIA comes back fine but we need to keep it alive or ACPI GTM failures
   occur when mode detecting */
DECLARE_PCI_FIXUP_CLASS_EARLY(PCI_VENDOR_ID_VIA, PCI_ANY_ID,
				PCI_CLASS_STORAGE_IDE, 8, quirk_no_ata_d3);

/*
 * This was originally an Alpha-specअगरic thing, but it really fits here.
 * The i82375 PCI/EISA bridge appears as non-classअगरied. Fix that.
 */
अटल व्योम quirk_eisa_bridge(काष्ठा pci_dev *dev)
अणु
	dev->class = PCI_CLASS_BRIDGE_EISA << 8;
पूर्ण
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_INTEL,	PCI_DEVICE_ID_INTEL_82375,	quirk_eisa_bridge);

/*
 * On ASUS P4B boards, the SMBus PCI Device within the ICH2/4 southbridge
 * is not activated. The myth is that Asus said that they करो not want the
 * users to be irritated by just another PCI Device in the Win98 device
 * manager. (see the file prog/hotplug/README.p4b in the lm_sensors
 * package 2.7.0 क्रम details)
 *
 * The SMBus PCI Device can be activated by setting a bit in the ICH LPC
 * bridge. Unक्रमtunately, this device has no subvenकरोr/subdevice ID. So it
 * becomes necessary to करो this tweak in two steps -- the chosen trigger
 * is either the Host bridge (preferred) or on-board VGA controller.
 *
 * Note that we used to unhide the SMBus that way on Toshiba laptops
 * (Satellite A40 and Tecra M2) but then found that the thermal management
 * was करोne by SMM code, which could cause unsynchronized concurrent
 * accesses to the SMBus रेजिस्टरs, with potentially bad effects. Thus you
 * should be very careful when adding new entries: अगर SMM is accessing the
 * Intel SMBus, this is a very good reason to leave it hidden.
 *
 * Likewise, many recent laptops use ACPI क्रम thermal management. If the
 * ACPI DSDT code accesses the SMBus, then Linux should not access it
 * natively, and keeping the SMBus hidden is the right thing to करो. If you
 * are about to add an entry in the table below, please first disassemble
 * the DSDT and द्विगुन-check that there is no code accessing the SMBus.
 */
अटल पूर्णांक asus_hides_smbus;

अटल व्योम asus_hides_smbus_hostbridge(काष्ठा pci_dev *dev)
अणु
	अगर (unlikely(dev->subप्रणाली_venकरोr == PCI_VENDOR_ID_ASUSTEK)) अणु
		अगर (dev->device == PCI_DEVICE_ID_INTEL_82845_HB)
			चयन (dev->subप्रणाली_device) अणु
			हाल 0x8025: /* P4B-LX */
			हाल 0x8070: /* P4B */
			हाल 0x8088: /* P4B533 */
			हाल 0x1626: /* L3C notebook */
				asus_hides_smbus = 1;
			पूर्ण
		अन्यथा अगर (dev->device == PCI_DEVICE_ID_INTEL_82845G_HB)
			चयन (dev->subप्रणाली_device) अणु
			हाल 0x80b1: /* P4GE-V */
			हाल 0x80b2: /* P4PE */
			हाल 0x8093: /* P4B533-V */
				asus_hides_smbus = 1;
			पूर्ण
		अन्यथा अगर (dev->device == PCI_DEVICE_ID_INTEL_82850_HB)
			चयन (dev->subप्रणाली_device) अणु
			हाल 0x8030: /* P4T533 */
				asus_hides_smbus = 1;
			पूर्ण
		अन्यथा अगर (dev->device == PCI_DEVICE_ID_INTEL_7205_0)
			चयन (dev->subप्रणाली_device) अणु
			हाल 0x8070: /* P4G8X Deluxe */
				asus_hides_smbus = 1;
			पूर्ण
		अन्यथा अगर (dev->device == PCI_DEVICE_ID_INTEL_E7501_MCH)
			चयन (dev->subप्रणाली_device) अणु
			हाल 0x80c9: /* PU-DLS */
				asus_hides_smbus = 1;
			पूर्ण
		अन्यथा अगर (dev->device == PCI_DEVICE_ID_INTEL_82855GM_HB)
			चयन (dev->subप्रणाली_device) अणु
			हाल 0x1751: /* M2N notebook */
			हाल 0x1821: /* M5N notebook */
			हाल 0x1897: /* A6L notebook */
				asus_hides_smbus = 1;
			पूर्ण
		अन्यथा अगर (dev->device == PCI_DEVICE_ID_INTEL_82855PM_HB)
			चयन (dev->subप्रणाली_device) अणु
			हाल 0x184b: /* W1N notebook */
			हाल 0x186a: /* M6Ne notebook */
				asus_hides_smbus = 1;
			पूर्ण
		अन्यथा अगर (dev->device == PCI_DEVICE_ID_INTEL_82865_HB)
			चयन (dev->subप्रणाली_device) अणु
			हाल 0x80f2: /* P4P800-X */
				asus_hides_smbus = 1;
			पूर्ण
		अन्यथा अगर (dev->device == PCI_DEVICE_ID_INTEL_82915GM_HB)
			चयन (dev->subप्रणाली_device) अणु
			हाल 0x1882: /* M6V notebook */
			हाल 0x1977: /* A6VA notebook */
				asus_hides_smbus = 1;
			पूर्ण
	पूर्ण अन्यथा अगर (unlikely(dev->subप्रणाली_venकरोr == PCI_VENDOR_ID_HP)) अणु
		अगर (dev->device ==  PCI_DEVICE_ID_INTEL_82855PM_HB)
			चयन (dev->subप्रणाली_device) अणु
			हाल 0x088C: /* HP Compaq nc8000 */
			हाल 0x0890: /* HP Compaq nc6000 */
				asus_hides_smbus = 1;
			पूर्ण
		अन्यथा अगर (dev->device == PCI_DEVICE_ID_INTEL_82865_HB)
			चयन (dev->subप्रणाली_device) अणु
			हाल 0x12bc: /* HP D330L */
			हाल 0x12bd: /* HP D530 */
			हाल 0x006a: /* HP Compaq nx9500 */
				asus_hides_smbus = 1;
			पूर्ण
		अन्यथा अगर (dev->device == PCI_DEVICE_ID_INTEL_82875_HB)
			चयन (dev->subप्रणाली_device) अणु
			हाल 0x12bf: /* HP xw4100 */
				asus_hides_smbus = 1;
			पूर्ण
	पूर्ण अन्यथा अगर (unlikely(dev->subप्रणाली_venकरोr == PCI_VENDOR_ID_SAMSUNG)) अणु
		अगर (dev->device ==  PCI_DEVICE_ID_INTEL_82855PM_HB)
			चयन (dev->subप्रणाली_device) अणु
			हाल 0xC00C: /* Samsung P35 notebook */
				asus_hides_smbus = 1;
		पूर्ण
	पूर्ण अन्यथा अगर (unlikely(dev->subप्रणाली_venकरोr == PCI_VENDOR_ID_COMPAQ)) अणु
		अगर (dev->device == PCI_DEVICE_ID_INTEL_82855PM_HB)
			चयन (dev->subप्रणाली_device) अणु
			हाल 0x0058: /* Compaq Evo N620c */
				asus_hides_smbus = 1;
			पूर्ण
		अन्यथा अगर (dev->device == PCI_DEVICE_ID_INTEL_82810_IG3)
			चयन (dev->subप्रणाली_device) अणु
			हाल 0xB16C: /* Compaq Deskpro EP 401963-001 (PCA# 010174) */
				/* Motherboard करोesn't have Host bridge
				 * subvenकरोr/subdevice IDs, thereक्रमe checking
				 * its on-board VGA controller */
				asus_hides_smbus = 1;
			पूर्ण
		अन्यथा अगर (dev->device == PCI_DEVICE_ID_INTEL_82801DB_2)
			चयन (dev->subप्रणाली_device) अणु
			हाल 0x00b8: /* Compaq Evo D510 CMT */
			हाल 0x00b9: /* Compaq Evo D510 SFF */
			हाल 0x00ba: /* Compaq Evo D510 USDT */
				/* Motherboard करोesn't have Host bridge
				 * subvenकरोr/subdevice IDs and on-board VGA
				 * controller is disabled अगर an AGP card is
				 * inserted, thereक्रमe checking USB UHCI
				 * Controller #1 */
				asus_hides_smbus = 1;
			पूर्ण
		अन्यथा अगर (dev->device == PCI_DEVICE_ID_INTEL_82815_CGC)
			चयन (dev->subप्रणाली_device) अणु
			हाल 0x001A: /* Compaq Deskpro EN SSF P667 815E */
				/* Motherboard करोesn't have host bridge
				 * subvenकरोr/subdevice IDs, thereक्रमe checking
				 * its on-board VGA controller */
				asus_hides_smbus = 1;
			पूर्ण
	पूर्ण
पूर्ण
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_INTEL,	PCI_DEVICE_ID_INTEL_82845_HB,	asus_hides_smbus_hostbridge);
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_INTEL,	PCI_DEVICE_ID_INTEL_82845G_HB,	asus_hides_smbus_hostbridge);
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_INTEL,	PCI_DEVICE_ID_INTEL_82850_HB,	asus_hides_smbus_hostbridge);
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_INTEL,	PCI_DEVICE_ID_INTEL_82865_HB,	asus_hides_smbus_hostbridge);
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_INTEL,	PCI_DEVICE_ID_INTEL_82875_HB,	asus_hides_smbus_hostbridge);
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_INTEL,	PCI_DEVICE_ID_INTEL_7205_0,	asus_hides_smbus_hostbridge);
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_INTEL,	PCI_DEVICE_ID_INTEL_E7501_MCH,	asus_hides_smbus_hostbridge);
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_INTEL,	PCI_DEVICE_ID_INTEL_82855PM_HB,	asus_hides_smbus_hostbridge);
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_INTEL,	PCI_DEVICE_ID_INTEL_82855GM_HB,	asus_hides_smbus_hostbridge);
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_INTEL,	PCI_DEVICE_ID_INTEL_82915GM_HB, asus_hides_smbus_hostbridge);

DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_INTEL,	PCI_DEVICE_ID_INTEL_82810_IG3,	asus_hides_smbus_hostbridge);
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_INTEL,	PCI_DEVICE_ID_INTEL_82801DB_2,	asus_hides_smbus_hostbridge);
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_INTEL,	PCI_DEVICE_ID_INTEL_82815_CGC,	asus_hides_smbus_hostbridge);

अटल व्योम asus_hides_smbus_lpc(काष्ठा pci_dev *dev)
अणु
	u16 val;

	अगर (likely(!asus_hides_smbus))
		वापस;

	pci_पढ़ो_config_word(dev, 0xF2, &val);
	अगर (val & 0x8) अणु
		pci_ग_लिखो_config_word(dev, 0xF2, val & (~0x8));
		pci_पढ़ो_config_word(dev, 0xF2, &val);
		अगर (val & 0x8)
			pci_info(dev, "i801 SMBus device continues to play 'hide and seek'! 0x%x\n",
				 val);
		अन्यथा
			pci_info(dev, "Enabled i801 SMBus device\n");
	पूर्ण
पूर्ण
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_INTEL,	PCI_DEVICE_ID_INTEL_82801AA_0,	asus_hides_smbus_lpc);
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_INTEL,	PCI_DEVICE_ID_INTEL_82801DB_0,	asus_hides_smbus_lpc);
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_INTEL,	PCI_DEVICE_ID_INTEL_82801BA_0,	asus_hides_smbus_lpc);
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_INTEL,	PCI_DEVICE_ID_INTEL_82801CA_0,	asus_hides_smbus_lpc);
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_INTEL,	PCI_DEVICE_ID_INTEL_82801CA_12,	asus_hides_smbus_lpc);
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_INTEL,	PCI_DEVICE_ID_INTEL_82801DB_12,	asus_hides_smbus_lpc);
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_INTEL,	PCI_DEVICE_ID_INTEL_82801EB_0,	asus_hides_smbus_lpc);
DECLARE_PCI_FIXUP_RESUME_EARLY(PCI_VENDOR_ID_INTEL,	PCI_DEVICE_ID_INTEL_82801AA_0,	asus_hides_smbus_lpc);
DECLARE_PCI_FIXUP_RESUME_EARLY(PCI_VENDOR_ID_INTEL,	PCI_DEVICE_ID_INTEL_82801DB_0,	asus_hides_smbus_lpc);
DECLARE_PCI_FIXUP_RESUME_EARLY(PCI_VENDOR_ID_INTEL,	PCI_DEVICE_ID_INTEL_82801BA_0,	asus_hides_smbus_lpc);
DECLARE_PCI_FIXUP_RESUME_EARLY(PCI_VENDOR_ID_INTEL,	PCI_DEVICE_ID_INTEL_82801CA_0,	asus_hides_smbus_lpc);
DECLARE_PCI_FIXUP_RESUME_EARLY(PCI_VENDOR_ID_INTEL,	PCI_DEVICE_ID_INTEL_82801CA_12,	asus_hides_smbus_lpc);
DECLARE_PCI_FIXUP_RESUME_EARLY(PCI_VENDOR_ID_INTEL,	PCI_DEVICE_ID_INTEL_82801DB_12,	asus_hides_smbus_lpc);
DECLARE_PCI_FIXUP_RESUME_EARLY(PCI_VENDOR_ID_INTEL,	PCI_DEVICE_ID_INTEL_82801EB_0,	asus_hides_smbus_lpc);

/* It appears we just have one such device. If not, we have a warning */
अटल व्योम __iomem *asus_rcba_base;
अटल व्योम asus_hides_smbus_lpc_ich6_suspend(काष्ठा pci_dev *dev)
अणु
	u32 rcba;

	अगर (likely(!asus_hides_smbus))
		वापस;
	WARN_ON(asus_rcba_base);

	pci_पढ़ो_config_dword(dev, 0xF0, &rcba);
	/* use bits 31:14, 16 kB aligned */
	asus_rcba_base = ioremap(rcba & 0xFFFFC000, 0x4000);
	अगर (asus_rcba_base == शून्य)
		वापस;
पूर्ण

अटल व्योम asus_hides_smbus_lpc_ich6_resume_early(काष्ठा pci_dev *dev)
अणु
	u32 val;

	अगर (likely(!asus_hides_smbus || !asus_rcba_base))
		वापस;

	/* पढ़ो the Function Disable रेजिस्टर, dword mode only */
	val = पढ़ोl(asus_rcba_base + 0x3418);

	/* enable the SMBus device */
	ग_लिखोl(val & 0xFFFFFFF7, asus_rcba_base + 0x3418);
पूर्ण

अटल व्योम asus_hides_smbus_lpc_ich6_resume(काष्ठा pci_dev *dev)
अणु
	अगर (likely(!asus_hides_smbus || !asus_rcba_base))
		वापस;

	iounmap(asus_rcba_base);
	asus_rcba_base = शून्य;
	pci_info(dev, "Enabled ICH6/i801 SMBus device\n");
पूर्ण

अटल व्योम asus_hides_smbus_lpc_ich6(काष्ठा pci_dev *dev)
अणु
	asus_hides_smbus_lpc_ich6_suspend(dev);
	asus_hides_smbus_lpc_ich6_resume_early(dev);
	asus_hides_smbus_lpc_ich6_resume(dev);
पूर्ण
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_INTEL,	PCI_DEVICE_ID_INTEL_ICH6_1,	asus_hides_smbus_lpc_ich6);
DECLARE_PCI_FIXUP_SUSPEND(PCI_VENDOR_ID_INTEL,	PCI_DEVICE_ID_INTEL_ICH6_1,	asus_hides_smbus_lpc_ich6_suspend);
DECLARE_PCI_FIXUP_RESUME(PCI_VENDOR_ID_INTEL,	PCI_DEVICE_ID_INTEL_ICH6_1,	asus_hides_smbus_lpc_ich6_resume);
DECLARE_PCI_FIXUP_RESUME_EARLY(PCI_VENDOR_ID_INTEL,	PCI_DEVICE_ID_INTEL_ICH6_1,	asus_hides_smbus_lpc_ich6_resume_early);

/* SiS 96x south bridge: BIOS typically hides SMBus device...  */
अटल व्योम quirk_sis_96x_smbus(काष्ठा pci_dev *dev)
अणु
	u8 val = 0;
	pci_पढ़ो_config_byte(dev, 0x77, &val);
	अगर (val & 0x10) अणु
		pci_info(dev, "Enabling SiS 96x SMBus\n");
		pci_ग_लिखो_config_byte(dev, 0x77, val & ~0x10);
	पूर्ण
पूर्ण
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_SI,	PCI_DEVICE_ID_SI_961,		quirk_sis_96x_smbus);
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_SI,	PCI_DEVICE_ID_SI_962,		quirk_sis_96x_smbus);
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_SI,	PCI_DEVICE_ID_SI_963,		quirk_sis_96x_smbus);
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_SI,	PCI_DEVICE_ID_SI_LPC,		quirk_sis_96x_smbus);
DECLARE_PCI_FIXUP_RESUME_EARLY(PCI_VENDOR_ID_SI,	PCI_DEVICE_ID_SI_961,		quirk_sis_96x_smbus);
DECLARE_PCI_FIXUP_RESUME_EARLY(PCI_VENDOR_ID_SI,	PCI_DEVICE_ID_SI_962,		quirk_sis_96x_smbus);
DECLARE_PCI_FIXUP_RESUME_EARLY(PCI_VENDOR_ID_SI,	PCI_DEVICE_ID_SI_963,		quirk_sis_96x_smbus);
DECLARE_PCI_FIXUP_RESUME_EARLY(PCI_VENDOR_ID_SI,	PCI_DEVICE_ID_SI_LPC,		quirk_sis_96x_smbus);

/*
 * ... This is further complicated by the fact that some SiS96x south
 * bridges pretend to be 85C503/5513 instead.  In that हाल see अगर we
 * spotted a compatible north bridge to make sure.
 * (pci_find_device() करोesn't work yet)
 *
 * We can also enable the sis96x bit in the discovery रेजिस्टर..
 */
#घोषणा SIS_DETECT_REGISTER 0x40

अटल व्योम quirk_sis_503(काष्ठा pci_dev *dev)
अणु
	u8 reg;
	u16 devid;

	pci_पढ़ो_config_byte(dev, SIS_DETECT_REGISTER, &reg);
	pci_ग_लिखो_config_byte(dev, SIS_DETECT_REGISTER, reg | (1 << 6));
	pci_पढ़ो_config_word(dev, PCI_DEVICE_ID, &devid);
	अगर (((devid & 0xfff0) != 0x0960) && (devid != 0x0018)) अणु
		pci_ग_लिखो_config_byte(dev, SIS_DETECT_REGISTER, reg);
		वापस;
	पूर्ण

	/*
	 * Ok, it now shows up as a 96x.  Run the 96x quirk by hand in हाल
	 * it has alपढ़ोy been processed.  (Depends on link order, which is
	 * apparently not guaranteed)
	 */
	dev->device = devid;
	quirk_sis_96x_smbus(dev);
पूर्ण
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_SI,	PCI_DEVICE_ID_SI_503,		quirk_sis_503);
DECLARE_PCI_FIXUP_RESUME_EARLY(PCI_VENDOR_ID_SI,	PCI_DEVICE_ID_SI_503,		quirk_sis_503);

/*
 * On ASUS A8V and A8V Deluxe boards, the onboard AC97 audio controller
 * and MC97 modem controller are disabled when a second PCI soundcard is
 * present. This patch, tweaking the VT8237 ISA bridge, enables them.
 * -- bjd
 */
अटल व्योम asus_hides_ac97_lpc(काष्ठा pci_dev *dev)
अणु
	u8 val;
	पूर्णांक asus_hides_ac97 = 0;

	अगर (likely(dev->subप्रणाली_venकरोr == PCI_VENDOR_ID_ASUSTEK)) अणु
		अगर (dev->device == PCI_DEVICE_ID_VIA_8237)
			asus_hides_ac97 = 1;
	पूर्ण

	अगर (!asus_hides_ac97)
		वापस;

	pci_पढ़ो_config_byte(dev, 0x50, &val);
	अगर (val & 0xc0) अणु
		pci_ग_लिखो_config_byte(dev, 0x50, val & (~0xc0));
		pci_पढ़ो_config_byte(dev, 0x50, &val);
		अगर (val & 0xc0)
			pci_info(dev, "Onboard AC97/MC97 devices continue to play 'hide and seek'! 0x%x\n",
				 val);
		अन्यथा
			pci_info(dev, "Enabled onboard AC97/MC97 devices\n");
	पूर्ण
पूर्ण
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_VIA,	PCI_DEVICE_ID_VIA_8237, asus_hides_ac97_lpc);
DECLARE_PCI_FIXUP_RESUME_EARLY(PCI_VENDOR_ID_VIA,	PCI_DEVICE_ID_VIA_8237, asus_hides_ac97_lpc);

#अगर defined(CONFIG_ATA) || defined(CONFIG_ATA_MODULE)

/*
 * If we are using libata we can drive this chip properly but must करो this
 * early on to make the additional device appear during the PCI scanning.
 */
अटल व्योम quirk_jmicron_ata(काष्ठा pci_dev *pdev)
अणु
	u32 conf1, conf5, class;
	u8 hdr;

	/* Only poke fn 0 */
	अगर (PCI_FUNC(pdev->devfn))
		वापस;

	pci_पढ़ो_config_dword(pdev, 0x40, &conf1);
	pci_पढ़ो_config_dword(pdev, 0x80, &conf5);

	conf1 &= ~0x00CFF302; /* Clear bit 1, 8, 9, 12-19, 22, 23 */
	conf5 &= ~(1 << 24);  /* Clear bit 24 */

	चयन (pdev->device) अणु
	हाल PCI_DEVICE_ID_JMICRON_JMB360: /* SATA single port */
	हाल PCI_DEVICE_ID_JMICRON_JMB362: /* SATA dual ports */
	हाल PCI_DEVICE_ID_JMICRON_JMB364: /* SATA dual ports */
		/* The controller should be in single function ahci mode */
		conf1 |= 0x0002A100; /* Set 8, 13, 15, 17 */
		अवरोध;

	हाल PCI_DEVICE_ID_JMICRON_JMB365:
	हाल PCI_DEVICE_ID_JMICRON_JMB366:
		/* Redirect IDE second PATA port to the right spot */
		conf5 |= (1 << 24);
		fallthrough;
	हाल PCI_DEVICE_ID_JMICRON_JMB361:
	हाल PCI_DEVICE_ID_JMICRON_JMB363:
	हाल PCI_DEVICE_ID_JMICRON_JMB369:
		/* Enable dual function mode, AHCI on fn 0, IDE fn1 */
		/* Set the class codes correctly and then direct IDE 0 */
		conf1 |= 0x00C2A1B3; /* Set 0, 1, 4, 5, 7, 8, 13, 15, 17, 22, 23 */
		अवरोध;

	हाल PCI_DEVICE_ID_JMICRON_JMB368:
		/* The controller should be in single function IDE mode */
		conf1 |= 0x00C00000; /* Set 22, 23 */
		अवरोध;
	पूर्ण

	pci_ग_लिखो_config_dword(pdev, 0x40, conf1);
	pci_ग_लिखो_config_dword(pdev, 0x80, conf5);

	/* Update pdev accordingly */
	pci_पढ़ो_config_byte(pdev, PCI_HEADER_TYPE, &hdr);
	pdev->hdr_type = hdr & 0x7f;
	pdev->multअगरunction = !!(hdr & 0x80);

	pci_पढ़ो_config_dword(pdev, PCI_CLASS_REVISION, &class);
	pdev->class = class >> 8;
पूर्ण
DECLARE_PCI_FIXUP_EARLY(PCI_VENDOR_ID_JMICRON, PCI_DEVICE_ID_JMICRON_JMB360, quirk_jmicron_ata);
DECLARE_PCI_FIXUP_EARLY(PCI_VENDOR_ID_JMICRON, PCI_DEVICE_ID_JMICRON_JMB361, quirk_jmicron_ata);
DECLARE_PCI_FIXUP_EARLY(PCI_VENDOR_ID_JMICRON, PCI_DEVICE_ID_JMICRON_JMB362, quirk_jmicron_ata);
DECLARE_PCI_FIXUP_EARLY(PCI_VENDOR_ID_JMICRON, PCI_DEVICE_ID_JMICRON_JMB363, quirk_jmicron_ata);
DECLARE_PCI_FIXUP_EARLY(PCI_VENDOR_ID_JMICRON, PCI_DEVICE_ID_JMICRON_JMB364, quirk_jmicron_ata);
DECLARE_PCI_FIXUP_EARLY(PCI_VENDOR_ID_JMICRON, PCI_DEVICE_ID_JMICRON_JMB365, quirk_jmicron_ata);
DECLARE_PCI_FIXUP_EARLY(PCI_VENDOR_ID_JMICRON, PCI_DEVICE_ID_JMICRON_JMB366, quirk_jmicron_ata);
DECLARE_PCI_FIXUP_EARLY(PCI_VENDOR_ID_JMICRON, PCI_DEVICE_ID_JMICRON_JMB368, quirk_jmicron_ata);
DECLARE_PCI_FIXUP_EARLY(PCI_VENDOR_ID_JMICRON, PCI_DEVICE_ID_JMICRON_JMB369, quirk_jmicron_ata);
DECLARE_PCI_FIXUP_RESUME_EARLY(PCI_VENDOR_ID_JMICRON, PCI_DEVICE_ID_JMICRON_JMB360, quirk_jmicron_ata);
DECLARE_PCI_FIXUP_RESUME_EARLY(PCI_VENDOR_ID_JMICRON, PCI_DEVICE_ID_JMICRON_JMB361, quirk_jmicron_ata);
DECLARE_PCI_FIXUP_RESUME_EARLY(PCI_VENDOR_ID_JMICRON, PCI_DEVICE_ID_JMICRON_JMB362, quirk_jmicron_ata);
DECLARE_PCI_FIXUP_RESUME_EARLY(PCI_VENDOR_ID_JMICRON, PCI_DEVICE_ID_JMICRON_JMB363, quirk_jmicron_ata);
DECLARE_PCI_FIXUP_RESUME_EARLY(PCI_VENDOR_ID_JMICRON, PCI_DEVICE_ID_JMICRON_JMB364, quirk_jmicron_ata);
DECLARE_PCI_FIXUP_RESUME_EARLY(PCI_VENDOR_ID_JMICRON, PCI_DEVICE_ID_JMICRON_JMB365, quirk_jmicron_ata);
DECLARE_PCI_FIXUP_RESUME_EARLY(PCI_VENDOR_ID_JMICRON, PCI_DEVICE_ID_JMICRON_JMB366, quirk_jmicron_ata);
DECLARE_PCI_FIXUP_RESUME_EARLY(PCI_VENDOR_ID_JMICRON, PCI_DEVICE_ID_JMICRON_JMB368, quirk_jmicron_ata);
DECLARE_PCI_FIXUP_RESUME_EARLY(PCI_VENDOR_ID_JMICRON, PCI_DEVICE_ID_JMICRON_JMB369, quirk_jmicron_ata);

#पूर्ण_अगर

अटल व्योम quirk_jmicron_async_suspend(काष्ठा pci_dev *dev)
अणु
	अगर (dev->multअगरunction) अणु
		device_disable_async_suspend(&dev->dev);
		pci_info(dev, "async suspend disabled to avoid multi-function power-on ordering issue\n");
	पूर्ण
पूर्ण
DECLARE_PCI_FIXUP_CLASS_FINAL(PCI_VENDOR_ID_JMICRON, PCI_ANY_ID, PCI_CLASS_STORAGE_IDE, 8, quirk_jmicron_async_suspend);
DECLARE_PCI_FIXUP_CLASS_FINAL(PCI_VENDOR_ID_JMICRON, PCI_ANY_ID, PCI_CLASS_STORAGE_SATA_AHCI, 0, quirk_jmicron_async_suspend);
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_JMICRON, 0x2362, quirk_jmicron_async_suspend);
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_JMICRON, 0x236f, quirk_jmicron_async_suspend);

#अगर_घोषित CONFIG_X86_IO_APIC
अटल व्योम quirk_alder_ioapic(काष्ठा pci_dev *pdev)
अणु
	पूर्णांक i;

	अगर ((pdev->class >> 8) != 0xff00)
		वापस;

	/*
	 * The first BAR is the location of the IO-APIC... we must
	 * not touch this (and it's alपढ़ोy covered by the fixmap), so
	 * क्रमcibly insert it पूर्णांकo the resource tree.
	 */
	अगर (pci_resource_start(pdev, 0) && pci_resource_len(pdev, 0))
		insert_resource(&iomem_resource, &pdev->resource[0]);

	/*
	 * The next five BARs all seem to be rubbish, so just clean
	 * them out.
	 */
	क्रम (i = 1; i < PCI_STD_NUM_BARS; i++)
		स_रखो(&pdev->resource[i], 0, माप(pdev->resource[i]));
पूर्ण
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_INTEL,	PCI_DEVICE_ID_INTEL_EESSC,	quirk_alder_ioapic);
#पूर्ण_अगर

अटल व्योम quirk_pcie_mch(काष्ठा pci_dev *pdev)
अणु
	pdev->no_msi = 1;
पूर्ण
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_INTEL,	PCI_DEVICE_ID_INTEL_E7520_MCH,	quirk_pcie_mch);
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_INTEL,	PCI_DEVICE_ID_INTEL_E7320_MCH,	quirk_pcie_mch);
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_INTEL,	PCI_DEVICE_ID_INTEL_E7525_MCH,	quirk_pcie_mch);

DECLARE_PCI_FIXUP_CLASS_FINAL(PCI_VENDOR_ID_HUAWEI, 0x1610, PCI_CLASS_BRIDGE_PCI, 8, quirk_pcie_mch);

/*
 * It's possible क्रम the MSI to get corrupted अगर SHPC and ACPI are used
 * together on certain PXH-based प्रणालीs.
 */
अटल व्योम quirk_pcie_pxh(काष्ठा pci_dev *dev)
अणु
	dev->no_msi = 1;
	pci_warn(dev, "PXH quirk detected; SHPC device MSI disabled\n");
पूर्ण
DECLARE_PCI_FIXUP_EARLY(PCI_VENDOR_ID_INTEL,	PCI_DEVICE_ID_INTEL_PXHD_0,	quirk_pcie_pxh);
DECLARE_PCI_FIXUP_EARLY(PCI_VENDOR_ID_INTEL,	PCI_DEVICE_ID_INTEL_PXHD_1,	quirk_pcie_pxh);
DECLARE_PCI_FIXUP_EARLY(PCI_VENDOR_ID_INTEL,	PCI_DEVICE_ID_INTEL_PXH_0,	quirk_pcie_pxh);
DECLARE_PCI_FIXUP_EARLY(PCI_VENDOR_ID_INTEL,	PCI_DEVICE_ID_INTEL_PXH_1,	quirk_pcie_pxh);
DECLARE_PCI_FIXUP_EARLY(PCI_VENDOR_ID_INTEL,	PCI_DEVICE_ID_INTEL_PXHV,	quirk_pcie_pxh);

/*
 * Some Intel PCI Express chipsets have trouble with करोwnstream device
 * घातer management.
 */
अटल व्योम quirk_पूर्णांकel_pcie_pm(काष्ठा pci_dev *dev)
अणु
	pci_pm_d3hot_delay = 120;
	dev->no_d1d2 = 1;
पूर्ण
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_INTEL,	0x25e2, quirk_पूर्णांकel_pcie_pm);
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_INTEL,	0x25e3, quirk_पूर्णांकel_pcie_pm);
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_INTEL,	0x25e4, quirk_पूर्णांकel_pcie_pm);
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_INTEL,	0x25e5, quirk_पूर्णांकel_pcie_pm);
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_INTEL,	0x25e6, quirk_पूर्णांकel_pcie_pm);
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_INTEL,	0x25e7, quirk_पूर्णांकel_pcie_pm);
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_INTEL,	0x25f7, quirk_पूर्णांकel_pcie_pm);
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_INTEL,	0x25f8, quirk_पूर्णांकel_pcie_pm);
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_INTEL,	0x25f9, quirk_पूर्णांकel_pcie_pm);
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_INTEL,	0x25fa, quirk_पूर्णांकel_pcie_pm);
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_INTEL,	0x2601, quirk_पूर्णांकel_pcie_pm);
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_INTEL,	0x2602, quirk_पूर्णांकel_pcie_pm);
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_INTEL,	0x2603, quirk_पूर्णांकel_pcie_pm);
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_INTEL,	0x2604, quirk_पूर्णांकel_pcie_pm);
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_INTEL,	0x2605, quirk_पूर्णांकel_pcie_pm);
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_INTEL,	0x2606, quirk_पूर्णांकel_pcie_pm);
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_INTEL,	0x2607, quirk_पूर्णांकel_pcie_pm);
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_INTEL,	0x2608, quirk_पूर्णांकel_pcie_pm);
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_INTEL,	0x2609, quirk_पूर्णांकel_pcie_pm);
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_INTEL,	0x260a, quirk_पूर्णांकel_pcie_pm);
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_INTEL,	0x260b, quirk_पूर्णांकel_pcie_pm);

अटल व्योम quirk_d3hot_delay(काष्ठा pci_dev *dev, अचिन्हित पूर्णांक delay)
अणु
	अगर (dev->d3hot_delay >= delay)
		वापस;

	dev->d3hot_delay = delay;
	pci_info(dev, "extending delay after power-on from D3hot to %d msec\n",
		 dev->d3hot_delay);
पूर्ण

अटल व्योम quirk_radeon_pm(काष्ठा pci_dev *dev)
अणु
	अगर (dev->subप्रणाली_venकरोr == PCI_VENDOR_ID_APPLE &&
	    dev->subप्रणाली_device == 0x00e2)
		quirk_d3hot_delay(dev, 20);
पूर्ण
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_ATI, 0x6741, quirk_radeon_pm);

/*
 * Ryzen5/7 XHCI controllers fail upon resume from runसमय suspend or s2idle.
 * https://bugzilla.kernel.org/show_bug.cgi?id=205587
 *
 * The kernel attempts to transition these devices to D3cold, but that seems
 * to be ineffective on the platक्रमms in question; the PCI device appears to
 * reमुख्य on in D3hot state. The D3hot-to-D0 transition then requires an
 * extended delay in order to succeed.
 */
अटल व्योम quirk_ryzen_xhci_d3hot(काष्ठा pci_dev *dev)
अणु
	quirk_d3hot_delay(dev, 20);
पूर्ण
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_AMD, 0x15e0, quirk_ryzen_xhci_d3hot);
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_AMD, 0x15e1, quirk_ryzen_xhci_d3hot);

#अगर_घोषित CONFIG_X86_IO_APIC
अटल पूर्णांक dmi_disable_ioapicreroute(स्थिर काष्ठा dmi_प्रणाली_id *d)
अणु
	noioapicreroute = 1;
	pr_info("%s detected: disable boot interrupt reroute\n", d->ident);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dmi_प्रणाली_id boot_पूर्णांकerrupt_dmi_table[] = अणु
	/*
	 * Systems to exclude from boot पूर्णांकerrupt reroute quirks
	 */
	अणु
		.callback = dmi_disable_ioapicreroute,
		.ident = "ASUSTek Computer INC. M2N-LR",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "ASUSTek Computer INC."),
			DMI_MATCH(DMI_PRODUCT_NAME, "M2N-LR"),
		पूर्ण,
	पूर्ण,
	अणुपूर्ण
पूर्ण;

/*
 * Boot पूर्णांकerrupts on some chipsets cannot be turned off. For these chipsets,
 * remap the original पूर्णांकerrupt in the Linux kernel to the boot पूर्णांकerrupt, so
 * that a PCI device's पूर्णांकerrupt handler is installed on the boot पूर्णांकerrupt
 * line instead.
 */
अटल व्योम quirk_reroute_to_boot_पूर्णांकerrupts_पूर्णांकel(काष्ठा pci_dev *dev)
अणु
	dmi_check_प्रणाली(boot_पूर्णांकerrupt_dmi_table);
	अगर (noioapicquirk || noioapicreroute)
		वापस;

	dev->irq_reroute_variant = INTEL_IRQ_REROUTE_VARIANT;
	pci_info(dev, "rerouting interrupts for [%04x:%04x]\n",
		 dev->venकरोr, dev->device);
पूर्ण
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_INTEL,	PCI_DEVICE_ID_INTEL_80333_0,	quirk_reroute_to_boot_पूर्णांकerrupts_पूर्णांकel);
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_INTEL,	PCI_DEVICE_ID_INTEL_80333_1,	quirk_reroute_to_boot_पूर्णांकerrupts_पूर्णांकel);
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_INTEL,	PCI_DEVICE_ID_INTEL_ESB2_0,	quirk_reroute_to_boot_पूर्णांकerrupts_पूर्णांकel);
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_INTEL,	PCI_DEVICE_ID_INTEL_PXH_0,	quirk_reroute_to_boot_पूर्णांकerrupts_पूर्णांकel);
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_INTEL,	PCI_DEVICE_ID_INTEL_PXH_1,	quirk_reroute_to_boot_पूर्णांकerrupts_पूर्णांकel);
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_INTEL,	PCI_DEVICE_ID_INTEL_PXHV,	quirk_reroute_to_boot_पूर्णांकerrupts_पूर्णांकel);
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_INTEL,	PCI_DEVICE_ID_INTEL_80332_0,	quirk_reroute_to_boot_पूर्णांकerrupts_पूर्णांकel);
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_INTEL,	PCI_DEVICE_ID_INTEL_80332_1,	quirk_reroute_to_boot_पूर्णांकerrupts_पूर्णांकel);
DECLARE_PCI_FIXUP_RESUME(PCI_VENDOR_ID_INTEL,	PCI_DEVICE_ID_INTEL_80333_0,	quirk_reroute_to_boot_पूर्णांकerrupts_पूर्णांकel);
DECLARE_PCI_FIXUP_RESUME(PCI_VENDOR_ID_INTEL,	PCI_DEVICE_ID_INTEL_80333_1,	quirk_reroute_to_boot_पूर्णांकerrupts_पूर्णांकel);
DECLARE_PCI_FIXUP_RESUME(PCI_VENDOR_ID_INTEL,	PCI_DEVICE_ID_INTEL_ESB2_0,	quirk_reroute_to_boot_पूर्णांकerrupts_पूर्णांकel);
DECLARE_PCI_FIXUP_RESUME(PCI_VENDOR_ID_INTEL,	PCI_DEVICE_ID_INTEL_PXH_0,	quirk_reroute_to_boot_पूर्णांकerrupts_पूर्णांकel);
DECLARE_PCI_FIXUP_RESUME(PCI_VENDOR_ID_INTEL,	PCI_DEVICE_ID_INTEL_PXH_1,	quirk_reroute_to_boot_पूर्णांकerrupts_पूर्णांकel);
DECLARE_PCI_FIXUP_RESUME(PCI_VENDOR_ID_INTEL,	PCI_DEVICE_ID_INTEL_PXHV,	quirk_reroute_to_boot_पूर्णांकerrupts_पूर्णांकel);
DECLARE_PCI_FIXUP_RESUME(PCI_VENDOR_ID_INTEL,	PCI_DEVICE_ID_INTEL_80332_0,	quirk_reroute_to_boot_पूर्णांकerrupts_पूर्णांकel);
DECLARE_PCI_FIXUP_RESUME(PCI_VENDOR_ID_INTEL,	PCI_DEVICE_ID_INTEL_80332_1,	quirk_reroute_to_boot_पूर्णांकerrupts_पूर्णांकel);

/*
 * On some chipsets we can disable the generation of legacy INTx boot
 * पूर्णांकerrupts.
 */

/*
 * IO-APIC1 on 6300ESB generates boot पूर्णांकerrupts, see Intel order no
 * 300641-004US, section 5.7.3.
 *
 * Core IO on Xeon E5 1600/2600/4600, see Intel order no 326509-003.
 * Core IO on Xeon E5 v2, see Intel order no 329188-003.
 * Core IO on Xeon E7 v2, see Intel order no 329595-002.
 * Core IO on Xeon E5 v3, see Intel order no 330784-003.
 * Core IO on Xeon E7 v3, see Intel order no 332315-001US.
 * Core IO on Xeon E5 v4, see Intel order no 333810-002US.
 * Core IO on Xeon E7 v4, see Intel order no 332315-001US.
 * Core IO on Xeon D-1500, see Intel order no 332051-001.
 * Core IO on Xeon Scalable, see Intel order no 610950.
 */
#घोषणा INTEL_6300_IOAPIC_ABAR		0x40	/* Bus 0, Dev 29, Func 5 */
#घोषणा INTEL_6300_DISABLE_BOOT_IRQ	(1<<14)

#घोषणा INTEL_CIPINTRC_CFG_OFFSET	0x14C	/* Bus 0, Dev 5, Func 0 */
#घोषणा INTEL_CIPINTRC_DIS_INTX_ICH	(1<<25)

अटल व्योम quirk_disable_पूर्णांकel_boot_पूर्णांकerrupt(काष्ठा pci_dev *dev)
अणु
	u16 pci_config_word;
	u32 pci_config_dword;

	अगर (noioapicquirk)
		वापस;

	चयन (dev->device) अणु
	हाल PCI_DEVICE_ID_INTEL_ESB_10:
		pci_पढ़ो_config_word(dev, INTEL_6300_IOAPIC_ABAR,
				     &pci_config_word);
		pci_config_word |= INTEL_6300_DISABLE_BOOT_IRQ;
		pci_ग_लिखो_config_word(dev, INTEL_6300_IOAPIC_ABAR,
				      pci_config_word);
		अवरोध;
	हाल 0x3c28:	/* Xeon E5 1600/2600/4600	*/
	हाल 0x0e28:	/* Xeon E5/E7 V2		*/
	हाल 0x2f28:	/* Xeon E5/E7 V3,V4		*/
	हाल 0x6f28:	/* Xeon D-1500			*/
	हाल 0x2034:	/* Xeon Scalable Family		*/
		pci_पढ़ो_config_dword(dev, INTEL_CIPINTRC_CFG_OFFSET,
				      &pci_config_dword);
		pci_config_dword |= INTEL_CIPINTRC_DIS_INTX_ICH;
		pci_ग_लिखो_config_dword(dev, INTEL_CIPINTRC_CFG_OFFSET,
				       pci_config_dword);
		अवरोध;
	शेष:
		वापस;
	पूर्ण
	pci_info(dev, "disabled boot interrupts on device [%04x:%04x]\n",
		 dev->venकरोr, dev->device);
पूर्ण
/*
 * Device 29 Func 5 Device IDs of IO-APIC
 * containing ABARै APIC1 Alternate Base Address Register
 */
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_INTEL,	PCI_DEVICE_ID_INTEL_ESB_10,
		quirk_disable_पूर्णांकel_boot_पूर्णांकerrupt);
DECLARE_PCI_FIXUP_RESUME(PCI_VENDOR_ID_INTEL,	PCI_DEVICE_ID_INTEL_ESB_10,
		quirk_disable_पूर्णांकel_boot_पूर्णांकerrupt);

/*
 * Device 5 Func 0 Device IDs of Core IO modules/hubs
 * containing Coherent Interface Protocol Interrupt Control
 *
 * Device IDs obtained from volume 2 datasheets of commented
 * families above.
 */
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_INTEL,	0x3c28,
		quirk_disable_पूर्णांकel_boot_पूर्णांकerrupt);
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_INTEL,	0x0e28,
		quirk_disable_पूर्णांकel_boot_पूर्णांकerrupt);
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_INTEL,	0x2f28,
		quirk_disable_पूर्णांकel_boot_पूर्णांकerrupt);
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_INTEL,	0x6f28,
		quirk_disable_पूर्णांकel_boot_पूर्णांकerrupt);
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_INTEL,	0x2034,
		quirk_disable_पूर्णांकel_boot_पूर्णांकerrupt);
DECLARE_PCI_FIXUP_RESUME(PCI_VENDOR_ID_INTEL,	0x3c28,
		quirk_disable_पूर्णांकel_boot_पूर्णांकerrupt);
DECLARE_PCI_FIXUP_RESUME(PCI_VENDOR_ID_INTEL,	0x0e28,
		quirk_disable_पूर्णांकel_boot_पूर्णांकerrupt);
DECLARE_PCI_FIXUP_RESUME(PCI_VENDOR_ID_INTEL,	0x2f28,
		quirk_disable_पूर्णांकel_boot_पूर्णांकerrupt);
DECLARE_PCI_FIXUP_RESUME(PCI_VENDOR_ID_INTEL,	0x6f28,
		quirk_disable_पूर्णांकel_boot_पूर्णांकerrupt);
DECLARE_PCI_FIXUP_RESUME(PCI_VENDOR_ID_INTEL,	0x2034,
		quirk_disable_पूर्णांकel_boot_पूर्णांकerrupt);

/* Disable boot पूर्णांकerrupts on HT-1000 */
#घोषणा BC_HT1000_FEATURE_REG		0x64
#घोषणा BC_HT1000_PIC_REGS_ENABLE	(1<<0)
#घोषणा BC_HT1000_MAP_IDX		0xC00
#घोषणा BC_HT1000_MAP_DATA		0xC01

अटल व्योम quirk_disable_broadcom_boot_पूर्णांकerrupt(काष्ठा pci_dev *dev)
अणु
	u32 pci_config_dword;
	u8 irq;

	अगर (noioapicquirk)
		वापस;

	pci_पढ़ो_config_dword(dev, BC_HT1000_FEATURE_REG, &pci_config_dword);
	pci_ग_लिखो_config_dword(dev, BC_HT1000_FEATURE_REG, pci_config_dword |
			BC_HT1000_PIC_REGS_ENABLE);

	क्रम (irq = 0x10; irq < 0x10 + 32; irq++) अणु
		outb(irq, BC_HT1000_MAP_IDX);
		outb(0x00, BC_HT1000_MAP_DATA);
	पूर्ण

	pci_ग_लिखो_config_dword(dev, BC_HT1000_FEATURE_REG, pci_config_dword);

	pci_info(dev, "disabled boot interrupts on device [%04x:%04x]\n",
		 dev->venकरोr, dev->device);
पूर्ण
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_SERVERWORKS,   PCI_DEVICE_ID_SERVERWORKS_HT1000SB,	quirk_disable_broadcom_boot_पूर्णांकerrupt);
DECLARE_PCI_FIXUP_RESUME(PCI_VENDOR_ID_SERVERWORKS,   PCI_DEVICE_ID_SERVERWORKS_HT1000SB,	quirk_disable_broadcom_boot_पूर्णांकerrupt);

/* Disable boot पूर्णांकerrupts on AMD and ATI chipsets */

/*
 * NOIOAMODE needs to be disabled to disable "boot interrupts". For AMD 8131
 * rev. A0 and B0, NOIOAMODE needs to be disabled anyway to fix IO-APIC mode
 * (due to an erratum).
 */
#घोषणा AMD_813X_MISC			0x40
#घोषणा AMD_813X_NOIOAMODE		(1<<0)
#घोषणा AMD_813X_REV_B1			0x12
#घोषणा AMD_813X_REV_B2			0x13

अटल व्योम quirk_disable_amd_813x_boot_पूर्णांकerrupt(काष्ठा pci_dev *dev)
अणु
	u32 pci_config_dword;

	अगर (noioapicquirk)
		वापस;
	अगर ((dev->revision == AMD_813X_REV_B1) ||
	    (dev->revision == AMD_813X_REV_B2))
		वापस;

	pci_पढ़ो_config_dword(dev, AMD_813X_MISC, &pci_config_dword);
	pci_config_dword &= ~AMD_813X_NOIOAMODE;
	pci_ग_लिखो_config_dword(dev, AMD_813X_MISC, pci_config_dword);

	pci_info(dev, "disabled boot interrupts on device [%04x:%04x]\n",
		 dev->venकरोr, dev->device);
पूर्ण
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_AMD,	PCI_DEVICE_ID_AMD_8131_BRIDGE,	quirk_disable_amd_813x_boot_पूर्णांकerrupt);
DECLARE_PCI_FIXUP_RESUME(PCI_VENDOR_ID_AMD,	PCI_DEVICE_ID_AMD_8131_BRIDGE,	quirk_disable_amd_813x_boot_पूर्णांकerrupt);
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_AMD,	PCI_DEVICE_ID_AMD_8132_BRIDGE,	quirk_disable_amd_813x_boot_पूर्णांकerrupt);
DECLARE_PCI_FIXUP_RESUME(PCI_VENDOR_ID_AMD,	PCI_DEVICE_ID_AMD_8132_BRIDGE,	quirk_disable_amd_813x_boot_पूर्णांकerrupt);

#घोषणा AMD_8111_PCI_IRQ_ROUTING	0x56

अटल व्योम quirk_disable_amd_8111_boot_पूर्णांकerrupt(काष्ठा pci_dev *dev)
अणु
	u16 pci_config_word;

	अगर (noioapicquirk)
		वापस;

	pci_पढ़ो_config_word(dev, AMD_8111_PCI_IRQ_ROUTING, &pci_config_word);
	अगर (!pci_config_word) अणु
		pci_info(dev, "boot interrupts on device [%04x:%04x] already disabled\n",
			 dev->venकरोr, dev->device);
		वापस;
	पूर्ण
	pci_ग_लिखो_config_word(dev, AMD_8111_PCI_IRQ_ROUTING, 0);
	pci_info(dev, "disabled boot interrupts on device [%04x:%04x]\n",
		 dev->venकरोr, dev->device);
पूर्ण
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_AMD,   PCI_DEVICE_ID_AMD_8111_SMBUS,	quirk_disable_amd_8111_boot_पूर्णांकerrupt);
DECLARE_PCI_FIXUP_RESUME(PCI_VENDOR_ID_AMD,   PCI_DEVICE_ID_AMD_8111_SMBUS,	quirk_disable_amd_8111_boot_पूर्णांकerrupt);
#पूर्ण_अगर /* CONFIG_X86_IO_APIC */

/*
 * Toshiba TC86C001 IDE controller reports the standard 8-byte BAR0 size
 * but the PIO transfers won't work अगर BAR0 falls at the odd 8 bytes.
 * Re-allocate the region अगर needed...
 */
अटल व्योम quirk_tc86c001_ide(काष्ठा pci_dev *dev)
अणु
	काष्ठा resource *r = &dev->resource[0];

	अगर (r->start & 0x8) अणु
		r->flags |= IORESOURCE_UNSET;
		r->start = 0;
		r->end = 0xf;
	पूर्ण
पूर्ण
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_TOSHIBA_2,
			 PCI_DEVICE_ID_TOSHIBA_TC86C001_IDE,
			 quirk_tc86c001_ide);

/*
 * PLX PCI 9050 PCI Target bridge controller has an erratum that prevents the
 * local configuration रेजिस्टरs accessible via BAR0 (memory) or BAR1 (i/o)
 * being पढ़ो correctly अगर bit 7 of the base address is set.
 * The BAR0 or BAR1 region may be disabled (size 0) or enabled (size 128).
 * Re-allocate the regions to a 256-byte boundary अगर necessary.
 */
अटल व्योम quirk_plx_pci9050(काष्ठा pci_dev *dev)
अणु
	अचिन्हित पूर्णांक bar;

	/* Fixed in revision 2 (PCI 9052). */
	अगर (dev->revision >= 2)
		वापस;
	क्रम (bar = 0; bar <= 1; bar++)
		अगर (pci_resource_len(dev, bar) == 0x80 &&
		    (pci_resource_start(dev, bar) & 0x80)) अणु
			काष्ठा resource *r = &dev->resource[bar];
			pci_info(dev, "Re-allocating PLX PCI 9050 BAR %u to length 256 to avoid bit 7 bug\n",
				 bar);
			r->flags |= IORESOURCE_UNSET;
			r->start = 0;
			r->end = 0xff;
		पूर्ण
पूर्ण
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_PLX, PCI_DEVICE_ID_PLX_9050,
			 quirk_plx_pci9050);
/*
 * The following Meilhaus (venकरोr ID 0x1402) device IDs (amongst others)
 * may be using the PLX PCI 9050: 0x0630, 0x0940, 0x0950, 0x0960, 0x100b,
 * 0x1400, 0x140a, 0x140b, 0x14e0, 0x14ea, 0x14eb, 0x1604, 0x1608, 0x160c,
 * 0x168f, 0x2000, 0x2600, 0x3000, 0x810a, 0x810b.
 *
 * Currently, device IDs 0x2000 and 0x2600 are used by the Comedi "me_daq"
 * driver.
 */
DECLARE_PCI_FIXUP_HEADER(0x1402, 0x2000, quirk_plx_pci9050);
DECLARE_PCI_FIXUP_HEADER(0x1402, 0x2600, quirk_plx_pci9050);

अटल व्योम quirk_neपंचांगos(काष्ठा pci_dev *dev)
अणु
	अचिन्हित पूर्णांक num_parallel = (dev->subप्रणाली_device & 0xf0) >> 4;
	अचिन्हित पूर्णांक num_serial = dev->subप्रणाली_device & 0xf;

	/*
	 * These Neपंचांगos parts are multiport serial devices with optional
	 * parallel ports.  Even when parallel ports are present, they
	 * are identअगरied as class SERIAL, which means the serial driver
	 * will claim them.  To prevent this, mark them as class OTHER.
	 * These combo devices should be claimed by parport_serial.
	 *
	 * The subdevice ID is of the क्रमm 0x00PS, where <P> is the number
	 * of parallel ports and <S> is the number of serial ports.
	 */
	चयन (dev->device) अणु
	हाल PCI_DEVICE_ID_NETMOS_9835:
		/* Well, this rule करोesn't hold क्रम the following 9835 device */
		अगर (dev->subप्रणाली_venकरोr == PCI_VENDOR_ID_IBM &&
				dev->subप्रणाली_device == 0x0299)
			वापस;
		fallthrough;
	हाल PCI_DEVICE_ID_NETMOS_9735:
	हाल PCI_DEVICE_ID_NETMOS_9745:
	हाल PCI_DEVICE_ID_NETMOS_9845:
	हाल PCI_DEVICE_ID_NETMOS_9855:
		अगर (num_parallel) अणु
			pci_info(dev, "Netmos %04x (%u parallel, %u serial); changing class SERIAL to OTHER (use parport_serial)\n",
				dev->device, num_parallel, num_serial);
			dev->class = (PCI_CLASS_COMMUNICATION_OTHER << 8) |
			    (dev->class & 0xff);
		पूर्ण
	पूर्ण
पूर्ण
DECLARE_PCI_FIXUP_CLASS_HEADER(PCI_VENDOR_ID_NETMOS, PCI_ANY_ID,
			 PCI_CLASS_COMMUNICATION_SERIAL, 8, quirk_neपंचांगos);

अटल व्योम quirk_e100_पूर्णांकerrupt(काष्ठा pci_dev *dev)
अणु
	u16 command, pmcsr;
	u8 __iomem *csr;
	u8 cmd_hi;

	चयन (dev->device) अणु
	/* PCI IDs taken from drivers/net/e100.c */
	हाल 0x1029:
	हाल 0x1030 ... 0x1034:
	हाल 0x1038 ... 0x103E:
	हाल 0x1050 ... 0x1057:
	हाल 0x1059:
	हाल 0x1064 ... 0x106B:
	हाल 0x1091 ... 0x1095:
	हाल 0x1209:
	हाल 0x1229:
	हाल 0x2449:
	हाल 0x2459:
	हाल 0x245D:
	हाल 0x27DC:
		अवरोध;
	शेष:
		वापस;
	पूर्ण

	/*
	 * Some firmware hands off the e100 with पूर्णांकerrupts enabled,
	 * which can cause a flood of पूर्णांकerrupts अगर packets are
	 * received beक्रमe the driver attaches to the device.  So
	 * disable all e100 पूर्णांकerrupts here.  The driver will
	 * re-enable them when it's पढ़ोy.
	 */
	pci_पढ़ो_config_word(dev, PCI_COMMAND, &command);

	अगर (!(command & PCI_COMMAND_MEMORY) || !pci_resource_start(dev, 0))
		वापस;

	/*
	 * Check that the device is in the D0 घातer state. If it's not,
	 * there is no poपूर्णांक to look any further.
	 */
	अगर (dev->pm_cap) अणु
		pci_पढ़ो_config_word(dev, dev->pm_cap + PCI_PM_CTRL, &pmcsr);
		अगर ((pmcsr & PCI_PM_CTRL_STATE_MASK) != PCI_D0)
			वापस;
	पूर्ण

	/* Convert from PCI bus to resource space.  */
	csr = ioremap(pci_resource_start(dev, 0), 8);
	अगर (!csr) अणु
		pci_warn(dev, "Can't map e100 registers\n");
		वापस;
	पूर्ण

	cmd_hi = पढ़ोb(csr + 3);
	अगर (cmd_hi == 0) अणु
		pci_warn(dev, "Firmware left e100 interrupts enabled; disabling\n");
		ग_लिखोb(1, csr + 3);
	पूर्ण

	iounmap(csr);
पूर्ण
DECLARE_PCI_FIXUP_CLASS_FINAL(PCI_VENDOR_ID_INTEL, PCI_ANY_ID,
			PCI_CLASS_NETWORK_ETHERNET, 8, quirk_e100_पूर्णांकerrupt);

/*
 * The 82575 and 82598 may experience data corruption issues when transitioning
 * out of L0S.  To prevent this we need to disable L0S on the PCIe link.
 */
अटल व्योम quirk_disable_aspm_l0s(काष्ठा pci_dev *dev)
अणु
	pci_info(dev, "Disabling L0s\n");
	pci_disable_link_state(dev, PCIE_LINK_STATE_L0S);
पूर्ण
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_INTEL, 0x10a7, quirk_disable_aspm_l0s);
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_INTEL, 0x10a9, quirk_disable_aspm_l0s);
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_INTEL, 0x10b6, quirk_disable_aspm_l0s);
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_INTEL, 0x10c6, quirk_disable_aspm_l0s);
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_INTEL, 0x10c7, quirk_disable_aspm_l0s);
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_INTEL, 0x10c8, quirk_disable_aspm_l0s);
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_INTEL, 0x10d6, quirk_disable_aspm_l0s);
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_INTEL, 0x10db, quirk_disable_aspm_l0s);
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_INTEL, 0x10dd, quirk_disable_aspm_l0s);
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_INTEL, 0x10e1, quirk_disable_aspm_l0s);
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_INTEL, 0x10ec, quirk_disable_aspm_l0s);
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_INTEL, 0x10f1, quirk_disable_aspm_l0s);
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_INTEL, 0x10f4, quirk_disable_aspm_l0s);
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_INTEL, 0x1508, quirk_disable_aspm_l0s);

अटल व्योम quirk_disable_aspm_l0s_l1(काष्ठा pci_dev *dev)
अणु
	pci_info(dev, "Disabling ASPM L0s/L1\n");
	pci_disable_link_state(dev, PCIE_LINK_STATE_L0S | PCIE_LINK_STATE_L1);
पूर्ण

/*
 * ASM1083/1085 PCIe-PCI bridge devices cause AER समयout errors on the
 * upstream PCIe root port when ASPM is enabled. At least L0s mode is affected;
 * disable both L0s and L1 क्रम now to be safe.
 */
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_ASMEDIA, 0x1080, quirk_disable_aspm_l0s_l1);

/*
 * Some Pericom PCIe-to-PCI bridges in reverse mode need the PCIe Retrain
 * Link bit cleared after starting the link retrain process to allow this
 * process to finish.
 *
 * Affected devices: PI7C9X110, PI7C9X111SL, PI7C9X130.  See also the
 * Pericom Errata Sheet PI7C9X111SLB_errata_rev1.2_102711.pdf.
 */
अटल व्योम quirk_enable_clear_retrain_link(काष्ठा pci_dev *dev)
अणु
	dev->clear_retrain_link = 1;
	pci_info(dev, "Enable PCIe Retrain Link quirk\n");
पूर्ण
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_PERICOM, 0xe110, quirk_enable_clear_retrain_link);
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_PERICOM, 0xe111, quirk_enable_clear_retrain_link);
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_PERICOM, 0xe130, quirk_enable_clear_retrain_link);

अटल व्योम fixup_rev1_53c810(काष्ठा pci_dev *dev)
अणु
	u32 class = dev->class;

	/*
	 * rev 1 ncr53c810 chips करोn't set the class at all which means
	 * they करोn't get their resources remapped. Fix that here.
	 */
	अगर (class)
		वापस;

	dev->class = PCI_CLASS_STORAGE_SCSI << 8;
	pci_info(dev, "NCR 53c810 rev 1 PCI class overridden (%#08x -> %#08x)\n",
		 class, dev->class);
पूर्ण
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_NCR, PCI_DEVICE_ID_NCR_53C810, fixup_rev1_53c810);

/* Enable 1k I/O space granularity on the Intel P64H2 */
अटल व्योम quirk_p64h2_1k_io(काष्ठा pci_dev *dev)
अणु
	u16 en1k;

	pci_पढ़ो_config_word(dev, 0x40, &en1k);

	अगर (en1k & 0x200) अणु
		pci_info(dev, "Enable I/O Space to 1KB granularity\n");
		dev->io_winकरोw_1k = 1;
	पूर्ण
पूर्ण
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_INTEL, 0x1460, quirk_p64h2_1k_io);

/*
 * Under some circumstances, AER is not linked with extended capabilities.
 * Force it to be linked by setting the corresponding control bit in the
 * config space.
 */
अटल व्योम quirk_nvidia_ck804_pcie_aer_ext_cap(काष्ठा pci_dev *dev)
अणु
	uपूर्णांक8_t b;

	अगर (pci_पढ़ो_config_byte(dev, 0xf41, &b) == 0) अणु
		अगर (!(b & 0x20)) अणु
			pci_ग_लिखो_config_byte(dev, 0xf41, b | 0x20);
			pci_info(dev, "Linking AER extended capability\n");
		पूर्ण
	पूर्ण
पूर्ण
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_NVIDIA,  PCI_DEVICE_ID_NVIDIA_CK804_PCIE,
			quirk_nvidia_ck804_pcie_aer_ext_cap);
DECLARE_PCI_FIXUP_RESUME_EARLY(PCI_VENDOR_ID_NVIDIA,  PCI_DEVICE_ID_NVIDIA_CK804_PCIE,
			quirk_nvidia_ck804_pcie_aer_ext_cap);

अटल व्योम quirk_via_cx700_pci_parking_caching(काष्ठा pci_dev *dev)
अणु
	/*
	 * Disable PCI Bus Parking and PCI Master पढ़ो caching on CX700
	 * which causes unspecअगरied timing errors with a VT6212L on the PCI
	 * bus leading to USB2.0 packet loss.
	 *
	 * This quirk is only enabled अगर a second (on the बाह्यal PCI bus)
	 * VT6212L is found -- the CX700 core itself also contains a USB
	 * host controller with the same PCI ID as the VT6212L.
	 */

	/* Count VT6212L instances */
	काष्ठा pci_dev *p = pci_get_device(PCI_VENDOR_ID_VIA,
		PCI_DEVICE_ID_VIA_8235_USB_2, शून्य);
	uपूर्णांक8_t b;

	/*
	 * p should contain the first (पूर्णांकernal) VT6212L -- see अगर we have
	 * an बाह्यal one by searching again.
	 */
	p = pci_get_device(PCI_VENDOR_ID_VIA, PCI_DEVICE_ID_VIA_8235_USB_2, p);
	अगर (!p)
		वापस;
	pci_dev_put(p);

	अगर (pci_पढ़ो_config_byte(dev, 0x76, &b) == 0) अणु
		अगर (b & 0x40) अणु
			/* Turn off PCI Bus Parking */
			pci_ग_लिखो_config_byte(dev, 0x76, b ^ 0x40);

			pci_info(dev, "Disabling VIA CX700 PCI parking\n");
		पूर्ण
	पूर्ण

	अगर (pci_पढ़ो_config_byte(dev, 0x72, &b) == 0) अणु
		अगर (b != 0) अणु
			/* Turn off PCI Master पढ़ो caching */
			pci_ग_लिखो_config_byte(dev, 0x72, 0x0);

			/* Set PCI Master Bus समय-out to "1x16 PCLK" */
			pci_ग_लिखो_config_byte(dev, 0x75, 0x1);

			/* Disable "Read FIFO Timer" */
			pci_ग_लिखो_config_byte(dev, 0x77, 0x0);

			pci_info(dev, "Disabling VIA CX700 PCI caching\n");
		पूर्ण
	पूर्ण
पूर्ण
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_VIA, 0x324e, quirk_via_cx700_pci_parking_caching);

अटल व्योम quirk_brcm_5719_limit_mrrs(काष्ठा pci_dev *dev)
अणु
	u32 rev;

	pci_पढ़ो_config_dword(dev, 0xf4, &rev);

	/* Only CAP the MRRS अगर the device is a 5719 A0 */
	अगर (rev == 0x05719000) अणु
		पूर्णांक पढ़ोrq = pcie_get_पढ़ोrq(dev);
		अगर (पढ़ोrq > 2048)
			pcie_set_पढ़ोrq(dev, 2048);
	पूर्ण
पूर्ण
DECLARE_PCI_FIXUP_ENABLE(PCI_VENDOR_ID_BROADCOM,
			 PCI_DEVICE_ID_TIGON3_5719,
			 quirk_brcm_5719_limit_mrrs);

/*
 * Originally in EDAC sources क्रम i82875P: Intel tells BIOS developers to
 * hide device 6 which configures the overflow device access containing the
 * DRBs - this is where we expose device 6.
 * http://www.x86-secret.com/articles/tweak/pat/patsecrets-2.hपंचांग
 */
अटल व्योम quirk_unhide_mch_dev6(काष्ठा pci_dev *dev)
अणु
	u8 reg;

	अगर (pci_पढ़ो_config_byte(dev, 0xF4, &reg) == 0 && !(reg & 0x02)) अणु
		pci_info(dev, "Enabling MCH 'Overflow' Device\n");
		pci_ग_लिखो_config_byte(dev, 0xF4, reg | 0x02);
	पूर्ण
पूर्ण
DECLARE_PCI_FIXUP_EARLY(PCI_VENDOR_ID_INTEL, PCI_DEVICE_ID_INTEL_82865_HB,
			quirk_unhide_mch_dev6);
DECLARE_PCI_FIXUP_EARLY(PCI_VENDOR_ID_INTEL, PCI_DEVICE_ID_INTEL_82875_HB,
			quirk_unhide_mch_dev6);

#अगर_घोषित CONFIG_PCI_MSI
/*
 * Some chipsets करो not support MSI. We cannot easily rely on setting
 * PCI_BUS_FLAGS_NO_MSI in its bus flags because there are actually some
 * other buses controlled by the chipset even अगर Linux is not aware of it.
 * Instead of setting the flag on all buses in the machine, simply disable
 * MSI globally.
 */
अटल व्योम quirk_disable_all_msi(काष्ठा pci_dev *dev)
अणु
	pci_no_msi();
	pci_warn(dev, "MSI quirk detected; MSI disabled\n");
पूर्ण
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_SERVERWORKS, PCI_DEVICE_ID_SERVERWORKS_GCNB_LE, quirk_disable_all_msi);
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_ATI, PCI_DEVICE_ID_ATI_RS400_200, quirk_disable_all_msi);
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_ATI, PCI_DEVICE_ID_ATI_RS480, quirk_disable_all_msi);
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_VIA, PCI_DEVICE_ID_VIA_VT3336, quirk_disable_all_msi);
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_VIA, PCI_DEVICE_ID_VIA_VT3351, quirk_disable_all_msi);
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_VIA, PCI_DEVICE_ID_VIA_VT3364, quirk_disable_all_msi);
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_VIA, PCI_DEVICE_ID_VIA_8380_0, quirk_disable_all_msi);
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_SI, 0x0761, quirk_disable_all_msi);
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_SAMSUNG, 0xa5e3, quirk_disable_all_msi);

/* Disable MSI on chipsets that are known to not support it */
अटल व्योम quirk_disable_msi(काष्ठा pci_dev *dev)
अणु
	अगर (dev->subordinate) अणु
		pci_warn(dev, "MSI quirk detected; subordinate MSI disabled\n");
		dev->subordinate->bus_flags |= PCI_BUS_FLAGS_NO_MSI;
	पूर्ण
पूर्ण
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_AMD, PCI_DEVICE_ID_AMD_8131_BRIDGE, quirk_disable_msi);
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_VIA, 0xa238, quirk_disable_msi);
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_ATI, 0x5a3f, quirk_disable_msi);

/*
 * The APC bridge device in AMD 780 family northbridges has some अक्रमom
 * OEM subप्रणाली ID in its venकरोr ID रेजिस्टर (erratum 18), so instead
 * we use the possible venकरोr/device IDs of the host bridge क्रम the
 * declared quirk, and search क्रम the APC bridge by slot number.
 */
अटल व्योम quirk_amd_780_apc_msi(काष्ठा pci_dev *host_bridge)
अणु
	काष्ठा pci_dev *apc_bridge;

	apc_bridge = pci_get_slot(host_bridge->bus, PCI_DEVFN(1, 0));
	अगर (apc_bridge) अणु
		अगर (apc_bridge->device == 0x9602)
			quirk_disable_msi(apc_bridge);
		pci_dev_put(apc_bridge);
	पूर्ण
पूर्ण
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_AMD, 0x9600, quirk_amd_780_apc_msi);
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_AMD, 0x9601, quirk_amd_780_apc_msi);

/*
 * Go through the list of HyperTransport capabilities and वापस 1 अगर a HT
 * MSI capability is found and enabled.
 */
अटल पूर्णांक msi_ht_cap_enabled(काष्ठा pci_dev *dev)
अणु
	पूर्णांक pos, ttl = PCI_FIND_CAP_TTL;

	pos = pci_find_ht_capability(dev, HT_CAPTYPE_MSI_MAPPING);
	जबतक (pos && ttl--) अणु
		u8 flags;

		अगर (pci_पढ़ो_config_byte(dev, pos + HT_MSI_FLAGS,
					 &flags) == 0) अणु
			pci_info(dev, "Found %s HT MSI Mapping\n",
				flags & HT_MSI_FLAGS_ENABLE ?
				"enabled" : "disabled");
			वापस (flags & HT_MSI_FLAGS_ENABLE) != 0;
		पूर्ण

		pos = pci_find_next_ht_capability(dev, pos,
						  HT_CAPTYPE_MSI_MAPPING);
	पूर्ण
	वापस 0;
पूर्ण

/* Check the HyperTransport MSI mapping to know whether MSI is enabled or not */
अटल व्योम quirk_msi_ht_cap(काष्ठा pci_dev *dev)
अणु
	अगर (!msi_ht_cap_enabled(dev))
		quirk_disable_msi(dev);
पूर्ण
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_SERVERWORKS, PCI_DEVICE_ID_SERVERWORKS_HT2000_PCIE,
			quirk_msi_ht_cap);

/*
 * The nVidia CK804 chipset may have 2 HT MSI mappings.  MSI is supported
 * अगर the MSI capability is set in any of these mappings.
 */
अटल व्योम quirk_nvidia_ck804_msi_ht_cap(काष्ठा pci_dev *dev)
अणु
	काष्ठा pci_dev *pdev;

	/*
	 * Check HT MSI cap on this chipset and the root one.  A single one
	 * having MSI is enough to be sure that MSI is supported.
	 */
	pdev = pci_get_slot(dev->bus, 0);
	अगर (!pdev)
		वापस;
	अगर (!msi_ht_cap_enabled(pdev))
		quirk_msi_ht_cap(dev);
	pci_dev_put(pdev);
पूर्ण
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_NVIDIA, PCI_DEVICE_ID_NVIDIA_CK804_PCIE,
			quirk_nvidia_ck804_msi_ht_cap);

/* Force enable MSI mapping capability on HT bridges */
अटल व्योम ht_enable_msi_mapping(काष्ठा pci_dev *dev)
अणु
	पूर्णांक pos, ttl = PCI_FIND_CAP_TTL;

	pos = pci_find_ht_capability(dev, HT_CAPTYPE_MSI_MAPPING);
	जबतक (pos && ttl--) अणु
		u8 flags;

		अगर (pci_पढ़ो_config_byte(dev, pos + HT_MSI_FLAGS,
					 &flags) == 0) अणु
			pci_info(dev, "Enabling HT MSI Mapping\n");

			pci_ग_लिखो_config_byte(dev, pos + HT_MSI_FLAGS,
					      flags | HT_MSI_FLAGS_ENABLE);
		पूर्ण
		pos = pci_find_next_ht_capability(dev, pos,
						  HT_CAPTYPE_MSI_MAPPING);
	पूर्ण
पूर्ण
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_SERVERWORKS,
			 PCI_DEVICE_ID_SERVERWORKS_HT1000_PXB,
			 ht_enable_msi_mapping);
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_AMD, PCI_DEVICE_ID_AMD_8132_BRIDGE,
			 ht_enable_msi_mapping);

/*
 * The P5N32-SLI motherboards from Asus have a problem with MSI
 * क्रम the MCP55 NIC. It is not yet determined whether the MSI problem
 * also affects other devices. As क्रम now, turn off MSI क्रम this device.
 */
अटल व्योम nvenet_msi_disable(काष्ठा pci_dev *dev)
अणु
	स्थिर अक्षर *board_name = dmi_get_प्रणाली_info(DMI_BOARD_NAME);

	अगर (board_name &&
	    (म_माला(board_name, "P5N32-SLI PREMIUM") ||
	     म_माला(board_name, "P5N32-E SLI"))) अणु
		pci_info(dev, "Disabling MSI for MCP55 NIC on P5N32-SLI\n");
		dev->no_msi = 1;
	पूर्ण
पूर्ण
DECLARE_PCI_FIXUP_EARLY(PCI_VENDOR_ID_NVIDIA,
			PCI_DEVICE_ID_NVIDIA_NVENET_15,
			nvenet_msi_disable);

/*
 * PCIe spec r4.0 sec 7.7.1.2 and sec 7.7.2.2 say that अगर MSI/MSI-X is enabled,
 * then the device can't use INTx interrupts. Tegra's PCIe root ports don't
 * generate MSI पूर्णांकerrupts क्रम PME and AER events instead only INTx पूर्णांकerrupts
 * are generated. Though Tegra's PCIe root ports can generate MSI पूर्णांकerrupts
 * क्रम other events, since PCIe specअगरiciation करोesn't support using a mix of
 * INTx and MSI/MSI-X, it is required to disable MSI पूर्णांकerrupts to aव्योम port
 * service drivers रेजिस्टरing their respective ISRs क्रम MSIs.
 */
अटल व्योम pci_quirk_nvidia_tegra_disable_rp_msi(काष्ठा pci_dev *dev)
अणु
	dev->no_msi = 1;
पूर्ण
DECLARE_PCI_FIXUP_CLASS_EARLY(PCI_VENDOR_ID_NVIDIA, 0x1ad0,
			      PCI_CLASS_BRIDGE_PCI, 8,
			      pci_quirk_nvidia_tegra_disable_rp_msi);
DECLARE_PCI_FIXUP_CLASS_EARLY(PCI_VENDOR_ID_NVIDIA, 0x1ad1,
			      PCI_CLASS_BRIDGE_PCI, 8,
			      pci_quirk_nvidia_tegra_disable_rp_msi);
DECLARE_PCI_FIXUP_CLASS_EARLY(PCI_VENDOR_ID_NVIDIA, 0x1ad2,
			      PCI_CLASS_BRIDGE_PCI, 8,
			      pci_quirk_nvidia_tegra_disable_rp_msi);
DECLARE_PCI_FIXUP_CLASS_EARLY(PCI_VENDOR_ID_NVIDIA, 0x0bf0,
			      PCI_CLASS_BRIDGE_PCI, 8,
			      pci_quirk_nvidia_tegra_disable_rp_msi);
DECLARE_PCI_FIXUP_CLASS_EARLY(PCI_VENDOR_ID_NVIDIA, 0x0bf1,
			      PCI_CLASS_BRIDGE_PCI, 8,
			      pci_quirk_nvidia_tegra_disable_rp_msi);
DECLARE_PCI_FIXUP_CLASS_EARLY(PCI_VENDOR_ID_NVIDIA, 0x0e1c,
			      PCI_CLASS_BRIDGE_PCI, 8,
			      pci_quirk_nvidia_tegra_disable_rp_msi);
DECLARE_PCI_FIXUP_CLASS_EARLY(PCI_VENDOR_ID_NVIDIA, 0x0e1d,
			      PCI_CLASS_BRIDGE_PCI, 8,
			      pci_quirk_nvidia_tegra_disable_rp_msi);
DECLARE_PCI_FIXUP_CLASS_EARLY(PCI_VENDOR_ID_NVIDIA, 0x0e12,
			      PCI_CLASS_BRIDGE_PCI, 8,
			      pci_quirk_nvidia_tegra_disable_rp_msi);
DECLARE_PCI_FIXUP_CLASS_EARLY(PCI_VENDOR_ID_NVIDIA, 0x0e13,
			      PCI_CLASS_BRIDGE_PCI, 8,
			      pci_quirk_nvidia_tegra_disable_rp_msi);
DECLARE_PCI_FIXUP_CLASS_EARLY(PCI_VENDOR_ID_NVIDIA, 0x0fae,
			      PCI_CLASS_BRIDGE_PCI, 8,
			      pci_quirk_nvidia_tegra_disable_rp_msi);
DECLARE_PCI_FIXUP_CLASS_EARLY(PCI_VENDOR_ID_NVIDIA, 0x0faf,
			      PCI_CLASS_BRIDGE_PCI, 8,
			      pci_quirk_nvidia_tegra_disable_rp_msi);
DECLARE_PCI_FIXUP_CLASS_EARLY(PCI_VENDOR_ID_NVIDIA, 0x10e5,
			      PCI_CLASS_BRIDGE_PCI, 8,
			      pci_quirk_nvidia_tegra_disable_rp_msi);
DECLARE_PCI_FIXUP_CLASS_EARLY(PCI_VENDOR_ID_NVIDIA, 0x10e6,
			      PCI_CLASS_BRIDGE_PCI, 8,
			      pci_quirk_nvidia_tegra_disable_rp_msi);

/*
 * Some versions of the MCP55 bridge from Nvidia have a legacy IRQ routing
 * config रेजिस्टर.  This रेजिस्टर controls the routing of legacy
 * पूर्णांकerrupts from devices that route through the MCP55.  If this रेजिस्टर
 * is misprogrammed, पूर्णांकerrupts are only sent to the BSP, unlike
 * conventional प्रणालीs where the IRQ is broadcast to all online CPUs.  Not
 * having this रेजिस्टर set properly prevents kdump from booting up
 * properly, so let's make sure that we have it set correctly.
 * Note that this is an unकरोcumented रेजिस्टर.
 */
अटल व्योम nvbridge_check_legacy_irq_routing(काष्ठा pci_dev *dev)
अणु
	u32 cfg;

	अगर (!pci_find_capability(dev, PCI_CAP_ID_HT))
		वापस;

	pci_पढ़ो_config_dword(dev, 0x74, &cfg);

	अगर (cfg & ((1 << 2) | (1 << 15))) अणु
		pr_info("Rewriting IRQ routing register on MCP55\n");
		cfg &= ~((1 << 2) | (1 << 15));
		pci_ग_लिखो_config_dword(dev, 0x74, cfg);
	पूर्ण
पूर्ण
DECLARE_PCI_FIXUP_EARLY(PCI_VENDOR_ID_NVIDIA,
			PCI_DEVICE_ID_NVIDIA_MCP55_BRIDGE_V0,
			nvbridge_check_legacy_irq_routing);
DECLARE_PCI_FIXUP_EARLY(PCI_VENDOR_ID_NVIDIA,
			PCI_DEVICE_ID_NVIDIA_MCP55_BRIDGE_V4,
			nvbridge_check_legacy_irq_routing);

अटल पूर्णांक ht_check_msi_mapping(काष्ठा pci_dev *dev)
अणु
	पूर्णांक pos, ttl = PCI_FIND_CAP_TTL;
	पूर्णांक found = 0;

	/* Check अगर there is HT MSI cap or enabled on this device */
	pos = pci_find_ht_capability(dev, HT_CAPTYPE_MSI_MAPPING);
	जबतक (pos && ttl--) अणु
		u8 flags;

		अगर (found < 1)
			found = 1;
		अगर (pci_पढ़ो_config_byte(dev, pos + HT_MSI_FLAGS,
					 &flags) == 0) अणु
			अगर (flags & HT_MSI_FLAGS_ENABLE) अणु
				अगर (found < 2) अणु
					found = 2;
					अवरोध;
				पूर्ण
			पूर्ण
		पूर्ण
		pos = pci_find_next_ht_capability(dev, pos,
						  HT_CAPTYPE_MSI_MAPPING);
	पूर्ण

	वापस found;
पूर्ण

अटल पूर्णांक host_bridge_with_leaf(काष्ठा pci_dev *host_bridge)
अणु
	काष्ठा pci_dev *dev;
	पूर्णांक pos;
	पूर्णांक i, dev_no;
	पूर्णांक found = 0;

	dev_no = host_bridge->devfn >> 3;
	क्रम (i = dev_no + 1; i < 0x20; i++) अणु
		dev = pci_get_slot(host_bridge->bus, PCI_DEVFN(i, 0));
		अगर (!dev)
			जारी;

		/* found next host bridge? */
		pos = pci_find_ht_capability(dev, HT_CAPTYPE_SLAVE);
		अगर (pos != 0) अणु
			pci_dev_put(dev);
			अवरोध;
		पूर्ण

		अगर (ht_check_msi_mapping(dev)) अणु
			found = 1;
			pci_dev_put(dev);
			अवरोध;
		पूर्ण
		pci_dev_put(dev);
	पूर्ण

	वापस found;
पूर्ण

#घोषणा PCI_HT_CAP_SLAVE_CTRL0     4    /* link control */
#घोषणा PCI_HT_CAP_SLAVE_CTRL1     8    /* link control to */

अटल पूर्णांक is_end_of_ht_chain(काष्ठा pci_dev *dev)
अणु
	पूर्णांक pos, ctrl_off;
	पूर्णांक end = 0;
	u16 flags, ctrl;

	pos = pci_find_ht_capability(dev, HT_CAPTYPE_SLAVE);

	अगर (!pos)
		जाओ out;

	pci_पढ़ो_config_word(dev, pos + PCI_CAP_FLAGS, &flags);

	ctrl_off = ((flags >> 10) & 1) ?
			PCI_HT_CAP_SLAVE_CTRL0 : PCI_HT_CAP_SLAVE_CTRL1;
	pci_पढ़ो_config_word(dev, pos + ctrl_off, &ctrl);

	अगर (ctrl & (1 << 6))
		end = 1;

out:
	वापस end;
पूर्ण

अटल व्योम nv_ht_enable_msi_mapping(काष्ठा pci_dev *dev)
अणु
	काष्ठा pci_dev *host_bridge;
	पूर्णांक pos;
	पूर्णांक i, dev_no;
	पूर्णांक found = 0;

	dev_no = dev->devfn >> 3;
	क्रम (i = dev_no; i >= 0; i--) अणु
		host_bridge = pci_get_slot(dev->bus, PCI_DEVFN(i, 0));
		अगर (!host_bridge)
			जारी;

		pos = pci_find_ht_capability(host_bridge, HT_CAPTYPE_SLAVE);
		अगर (pos != 0) अणु
			found = 1;
			अवरोध;
		पूर्ण
		pci_dev_put(host_bridge);
	पूर्ण

	अगर (!found)
		वापस;

	/* करोn't enable end_device/host_bridge with leaf directly here */
	अगर (host_bridge == dev && is_end_of_ht_chain(host_bridge) &&
	    host_bridge_with_leaf(host_bridge))
		जाओ out;

	/* root did that ! */
	अगर (msi_ht_cap_enabled(host_bridge))
		जाओ out;

	ht_enable_msi_mapping(dev);

out:
	pci_dev_put(host_bridge);
पूर्ण

अटल व्योम ht_disable_msi_mapping(काष्ठा pci_dev *dev)
अणु
	पूर्णांक pos, ttl = PCI_FIND_CAP_TTL;

	pos = pci_find_ht_capability(dev, HT_CAPTYPE_MSI_MAPPING);
	जबतक (pos && ttl--) अणु
		u8 flags;

		अगर (pci_पढ़ो_config_byte(dev, pos + HT_MSI_FLAGS,
					 &flags) == 0) अणु
			pci_info(dev, "Disabling HT MSI Mapping\n");

			pci_ग_लिखो_config_byte(dev, pos + HT_MSI_FLAGS,
					      flags & ~HT_MSI_FLAGS_ENABLE);
		पूर्ण
		pos = pci_find_next_ht_capability(dev, pos,
						  HT_CAPTYPE_MSI_MAPPING);
	पूर्ण
पूर्ण

अटल व्योम __nv_msi_ht_cap_quirk(काष्ठा pci_dev *dev, पूर्णांक all)
अणु
	काष्ठा pci_dev *host_bridge;
	पूर्णांक pos;
	पूर्णांक found;

	अगर (!pci_msi_enabled())
		वापस;

	/* check अगर there is HT MSI cap or enabled on this device */
	found = ht_check_msi_mapping(dev);

	/* no HT MSI CAP */
	अगर (found == 0)
		वापस;

	/*
	 * HT MSI mapping should be disabled on devices that are below
	 * a non-Hypertransport host bridge. Locate the host bridge...
	 */
	host_bridge = pci_get_करोमुख्य_bus_and_slot(pci_करोमुख्य_nr(dev->bus), 0,
						  PCI_DEVFN(0, 0));
	अगर (host_bridge == शून्य) अणु
		pci_warn(dev, "nv_msi_ht_cap_quirk didn't locate host bridge\n");
		वापस;
	पूर्ण

	pos = pci_find_ht_capability(host_bridge, HT_CAPTYPE_SLAVE);
	अगर (pos != 0) अणु
		/* Host bridge is to HT */
		अगर (found == 1) अणु
			/* it is not enabled, try to enable it */
			अगर (all)
				ht_enable_msi_mapping(dev);
			अन्यथा
				nv_ht_enable_msi_mapping(dev);
		पूर्ण
		जाओ out;
	पूर्ण

	/* HT MSI is not enabled */
	अगर (found == 1)
		जाओ out;

	/* Host bridge is not to HT, disable HT MSI mapping on this device */
	ht_disable_msi_mapping(dev);

out:
	pci_dev_put(host_bridge);
पूर्ण

अटल व्योम nv_msi_ht_cap_quirk_all(काष्ठा pci_dev *dev)
अणु
	वापस __nv_msi_ht_cap_quirk(dev, 1);
पूर्ण
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_AL, PCI_ANY_ID, nv_msi_ht_cap_quirk_all);
DECLARE_PCI_FIXUP_RESUME_EARLY(PCI_VENDOR_ID_AL, PCI_ANY_ID, nv_msi_ht_cap_quirk_all);

अटल व्योम nv_msi_ht_cap_quirk_leaf(काष्ठा pci_dev *dev)
अणु
	वापस __nv_msi_ht_cap_quirk(dev, 0);
पूर्ण
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_NVIDIA, PCI_ANY_ID, nv_msi_ht_cap_quirk_leaf);
DECLARE_PCI_FIXUP_RESUME_EARLY(PCI_VENDOR_ID_NVIDIA, PCI_ANY_ID, nv_msi_ht_cap_quirk_leaf);

अटल व्योम quirk_msi_पूर्णांकx_disable_bug(काष्ठा pci_dev *dev)
अणु
	dev->dev_flags |= PCI_DEV_FLAGS_MSI_INTX_DISABLE_BUG;
पूर्ण

अटल व्योम quirk_msi_पूर्णांकx_disable_ati_bug(काष्ठा pci_dev *dev)
अणु
	काष्ठा pci_dev *p;

	/*
	 * SB700 MSI issue will be fixed at HW level from revision A21;
	 * we need check PCI REVISION ID of SMBus controller to get SB700
	 * revision.
	 */
	p = pci_get_device(PCI_VENDOR_ID_ATI, PCI_DEVICE_ID_ATI_SBX00_SMBUS,
			   शून्य);
	अगर (!p)
		वापस;

	अगर ((p->revision < 0x3B) && (p->revision >= 0x30))
		dev->dev_flags |= PCI_DEV_FLAGS_MSI_INTX_DISABLE_BUG;
	pci_dev_put(p);
पूर्ण

अटल व्योम quirk_msi_पूर्णांकx_disable_qca_bug(काष्ठा pci_dev *dev)
अणु
	/* AR816X/AR817X/E210X MSI is fixed at HW level from revision 0x18 */
	अगर (dev->revision < 0x18) अणु
		pci_info(dev, "set MSI_INTX_DISABLE_BUG flag\n");
		dev->dev_flags |= PCI_DEV_FLAGS_MSI_INTX_DISABLE_BUG;
	पूर्ण
पूर्ण
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_BROADCOM,
			PCI_DEVICE_ID_TIGON3_5780,
			quirk_msi_पूर्णांकx_disable_bug);
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_BROADCOM,
			PCI_DEVICE_ID_TIGON3_5780S,
			quirk_msi_पूर्णांकx_disable_bug);
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_BROADCOM,
			PCI_DEVICE_ID_TIGON3_5714,
			quirk_msi_पूर्णांकx_disable_bug);
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_BROADCOM,
			PCI_DEVICE_ID_TIGON3_5714S,
			quirk_msi_पूर्णांकx_disable_bug);
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_BROADCOM,
			PCI_DEVICE_ID_TIGON3_5715,
			quirk_msi_पूर्णांकx_disable_bug);
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_BROADCOM,
			PCI_DEVICE_ID_TIGON3_5715S,
			quirk_msi_पूर्णांकx_disable_bug);

DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_ATI, 0x4390,
			quirk_msi_पूर्णांकx_disable_ati_bug);
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_ATI, 0x4391,
			quirk_msi_पूर्णांकx_disable_ati_bug);
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_ATI, 0x4392,
			quirk_msi_पूर्णांकx_disable_ati_bug);
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_ATI, 0x4393,
			quirk_msi_पूर्णांकx_disable_ati_bug);
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_ATI, 0x4394,
			quirk_msi_पूर्णांकx_disable_ati_bug);

DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_ATI, 0x4373,
			quirk_msi_पूर्णांकx_disable_bug);
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_ATI, 0x4374,
			quirk_msi_पूर्णांकx_disable_bug);
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_ATI, 0x4375,
			quirk_msi_पूर्णांकx_disable_bug);

DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_ATTANSIC, 0x1062,
			quirk_msi_पूर्णांकx_disable_bug);
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_ATTANSIC, 0x1063,
			quirk_msi_पूर्णांकx_disable_bug);
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_ATTANSIC, 0x2060,
			quirk_msi_पूर्णांकx_disable_bug);
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_ATTANSIC, 0x2062,
			quirk_msi_पूर्णांकx_disable_bug);
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_ATTANSIC, 0x1073,
			quirk_msi_पूर्णांकx_disable_bug);
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_ATTANSIC, 0x1083,
			quirk_msi_पूर्णांकx_disable_bug);
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_ATTANSIC, 0x1090,
			quirk_msi_पूर्णांकx_disable_qca_bug);
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_ATTANSIC, 0x1091,
			quirk_msi_पूर्णांकx_disable_qca_bug);
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_ATTANSIC, 0x10a0,
			quirk_msi_पूर्णांकx_disable_qca_bug);
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_ATTANSIC, 0x10a1,
			quirk_msi_पूर्णांकx_disable_qca_bug);
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_ATTANSIC, 0xe091,
			quirk_msi_पूर्णांकx_disable_qca_bug);

/*
 * Amazon's Annapurna Labs 1c36:0031 Root Ports don't support MSI-X, so it
 * should be disabled on platक्रमms where the device (mistakenly) advertises it.
 *
 * Notice that this quirk also disables MSI (which may work, but hasn't been
 * tested), since currently there is no standard way to disable only MSI-X.
 *
 * The 0031 device id is reused क्रम other non Root Port device types,
 * thereक्रमe the quirk is रेजिस्टरed क्रम the PCI_CLASS_BRIDGE_PCI class.
 */
अटल व्योम quirk_al_msi_disable(काष्ठा pci_dev *dev)
अणु
	dev->no_msi = 1;
	pci_warn(dev, "Disabling MSI/MSI-X\n");
पूर्ण
DECLARE_PCI_FIXUP_CLASS_FINAL(PCI_VENDOR_ID_AMAZON_ANNAPURNA_LABS, 0x0031,
			      PCI_CLASS_BRIDGE_PCI, 8, quirk_al_msi_disable);
#पूर्ण_अगर /* CONFIG_PCI_MSI */

/*
 * Allow manual resource allocation क्रम PCI hotplug bridges via
 * pci=hpmemsize=nnM and pci=hpiosize=nnM parameters. For some PCI-PCI
 * hotplug bridges, like PLX 6254 (क्रमmer HINT HB6), kernel fails to
 * allocate resources when hotplug device is inserted and PCI bus is
 * rescanned.
 */
अटल व्योम quirk_hotplug_bridge(काष्ठा pci_dev *dev)
अणु
	dev->is_hotplug_bridge = 1;
पूर्ण
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_HINT, 0x0020, quirk_hotplug_bridge);

/*
 * This is a quirk क्रम the Ricoh MMC controller found as a part of some
 * multअगरunction chips.
 *
 * This is very similar and based on the ricoh_mmc driver written by
 * Philip Langdale. Thank you क्रम these magic sequences.
 *
 * These chips implement the four मुख्य memory card controllers (SD, MMC,
 * MS, xD) and one or both of CardBus or FireWire.
 *
 * It happens that they implement SD and MMC support as separate
 * controllers (and PCI functions). The Linux SDHCI driver supports MMC
 * cards but the chip detects MMC cards in hardware and directs them to the
 * MMC controller - so the SDHCI driver never sees them.
 *
 * To get around this, we must disable the useless MMC controller.  At that
 * poपूर्णांक, the SDHCI controller will start seeing them.  It seems to be the
 * हाल that the relevant PCI रेजिस्टरs to deactivate the MMC controller
 * live on PCI function 0, which might be the CardBus controller or the
 * FireWire controller, depending on the particular chip in question
 *
 * This has to be करोne early, because as soon as we disable the MMC controller
 * other PCI functions shअगरt up one level, e.g. function #2 becomes function
 * #1, and this will confuse the PCI core.
 */
#अगर_घोषित CONFIG_MMC_RICOH_MMC
अटल व्योम ricoh_mmc_fixup_rl5c476(काष्ठा pci_dev *dev)
अणु
	u8 ग_लिखो_enable;
	u8 ग_लिखो_target;
	u8 disable;

	/*
	 * Disable via CardBus पूर्णांकerface
	 *
	 * This must be करोne via function #0
	 */
	अगर (PCI_FUNC(dev->devfn))
		वापस;

	pci_पढ़ो_config_byte(dev, 0xB7, &disable);
	अगर (disable & 0x02)
		वापस;

	pci_पढ़ो_config_byte(dev, 0x8E, &ग_लिखो_enable);
	pci_ग_लिखो_config_byte(dev, 0x8E, 0xAA);
	pci_पढ़ो_config_byte(dev, 0x8D, &ग_लिखो_target);
	pci_ग_लिखो_config_byte(dev, 0x8D, 0xB7);
	pci_ग_लिखो_config_byte(dev, 0xB7, disable | 0x02);
	pci_ग_लिखो_config_byte(dev, 0x8E, ग_लिखो_enable);
	pci_ग_लिखो_config_byte(dev, 0x8D, ग_लिखो_target);

	pci_notice(dev, "proprietary Ricoh MMC controller disabled (via CardBus function)\n");
	pci_notice(dev, "MMC cards are now supported by standard SDHCI controller\n");
पूर्ण
DECLARE_PCI_FIXUP_EARLY(PCI_VENDOR_ID_RICOH, PCI_DEVICE_ID_RICOH_RL5C476, ricoh_mmc_fixup_rl5c476);
DECLARE_PCI_FIXUP_RESUME_EARLY(PCI_VENDOR_ID_RICOH, PCI_DEVICE_ID_RICOH_RL5C476, ricoh_mmc_fixup_rl5c476);

अटल व्योम ricoh_mmc_fixup_r5c832(काष्ठा pci_dev *dev)
अणु
	u8 ग_लिखो_enable;
	u8 disable;

	/*
	 * Disable via FireWire पूर्णांकerface
	 *
	 * This must be करोne via function #0
	 */
	अगर (PCI_FUNC(dev->devfn))
		वापस;
	/*
	 * RICOH 0xe822 and 0xe823 SD/MMC card पढ़ोers fail to recognize
	 * certain types of SD/MMC cards. Lowering the SD base घड़ी
	 * frequency from 200Mhz to 50Mhz fixes this issue.
	 *
	 * 0x150 - SD2.0 mode enable क्रम changing base घड़ी
	 *	   frequency to 50Mhz
	 * 0xe1  - Base घड़ी frequency
	 * 0x32  - 50Mhz new घड़ी frequency
	 * 0xf9  - Key रेजिस्टर क्रम 0x150
	 * 0xfc  - key रेजिस्टर क्रम 0xe1
	 */
	अगर (dev->device == PCI_DEVICE_ID_RICOH_R5CE822 ||
	    dev->device == PCI_DEVICE_ID_RICOH_R5CE823) अणु
		pci_ग_लिखो_config_byte(dev, 0xf9, 0xfc);
		pci_ग_लिखो_config_byte(dev, 0x150, 0x10);
		pci_ग_लिखो_config_byte(dev, 0xf9, 0x00);
		pci_ग_लिखो_config_byte(dev, 0xfc, 0x01);
		pci_ग_लिखो_config_byte(dev, 0xe1, 0x32);
		pci_ग_लिखो_config_byte(dev, 0xfc, 0x00);

		pci_notice(dev, "MMC controller base frequency changed to 50Mhz.\n");
	पूर्ण

	pci_पढ़ो_config_byte(dev, 0xCB, &disable);

	अगर (disable & 0x02)
		वापस;

	pci_पढ़ो_config_byte(dev, 0xCA, &ग_लिखो_enable);
	pci_ग_लिखो_config_byte(dev, 0xCA, 0x57);
	pci_ग_लिखो_config_byte(dev, 0xCB, disable | 0x02);
	pci_ग_लिखो_config_byte(dev, 0xCA, ग_लिखो_enable);

	pci_notice(dev, "proprietary Ricoh MMC controller disabled (via FireWire function)\n");
	pci_notice(dev, "MMC cards are now supported by standard SDHCI controller\n");

पूर्ण
DECLARE_PCI_FIXUP_EARLY(PCI_VENDOR_ID_RICOH, PCI_DEVICE_ID_RICOH_R5C832, ricoh_mmc_fixup_r5c832);
DECLARE_PCI_FIXUP_RESUME_EARLY(PCI_VENDOR_ID_RICOH, PCI_DEVICE_ID_RICOH_R5C832, ricoh_mmc_fixup_r5c832);
DECLARE_PCI_FIXUP_EARLY(PCI_VENDOR_ID_RICOH, PCI_DEVICE_ID_RICOH_R5CE822, ricoh_mmc_fixup_r5c832);
DECLARE_PCI_FIXUP_RESUME_EARLY(PCI_VENDOR_ID_RICOH, PCI_DEVICE_ID_RICOH_R5CE822, ricoh_mmc_fixup_r5c832);
DECLARE_PCI_FIXUP_EARLY(PCI_VENDOR_ID_RICOH, PCI_DEVICE_ID_RICOH_R5CE823, ricoh_mmc_fixup_r5c832);
DECLARE_PCI_FIXUP_RESUME_EARLY(PCI_VENDOR_ID_RICOH, PCI_DEVICE_ID_RICOH_R5CE823, ricoh_mmc_fixup_r5c832);
#पूर्ण_अगर /*CONFIG_MMC_RICOH_MMC*/

#अगर_घोषित CONFIG_DMAR_TABLE
#घोषणा VTUNCERRMSK_REG	0x1ac
#घोषणा VTD_MSK_SPEC_ERRORS	(1 << 31)
/*
 * This is a quirk क्रम masking VT-d spec-defined errors to platक्रमm error
 * handling logic. Without this, platक्रमms using Intel 7500, 5500 chipsets
 * (and the derivative chipsets like X58 etc) seem to generate NMI/SMI (based
 * on the RAS config settings of the platक्रमm) when a VT-d fault happens.
 * The resulting SMI caused the प्रणाली to hang.
 *
 * VT-d spec-related errors are alपढ़ोy handled by the VT-d OS code, so no
 * need to report the same error through other channels.
 */
अटल व्योम vtd_mask_spec_errors(काष्ठा pci_dev *dev)
अणु
	u32 word;

	pci_पढ़ो_config_dword(dev, VTUNCERRMSK_REG, &word);
	pci_ग_लिखो_config_dword(dev, VTUNCERRMSK_REG, word | VTD_MSK_SPEC_ERRORS);
पूर्ण
DECLARE_PCI_FIXUP_EARLY(PCI_VENDOR_ID_INTEL, 0x342e, vtd_mask_spec_errors);
DECLARE_PCI_FIXUP_EARLY(PCI_VENDOR_ID_INTEL, 0x3c28, vtd_mask_spec_errors);
#पूर्ण_अगर

अटल व्योम fixup_ti816x_class(काष्ठा pci_dev *dev)
अणु
	u32 class = dev->class;

	/* TI 816x devices करो not have class code set when in PCIe boot mode */
	dev->class = PCI_CLASS_MULTIMEDIA_VIDEO << 8;
	pci_info(dev, "PCI class overridden (%#08x -> %#08x)\n",
		 class, dev->class);
पूर्ण
DECLARE_PCI_FIXUP_CLASS_EARLY(PCI_VENDOR_ID_TI, 0xb800,
			      PCI_CLASS_NOT_DEFINED, 8, fixup_ti816x_class);

/*
 * Some PCIe devices करो not work reliably with the claimed maximum
 * payload size supported.
 */
अटल व्योम fixup_mpss_256(काष्ठा pci_dev *dev)
अणु
	dev->pcie_mpss = 1; /* 256 bytes */
पूर्ण
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_SOLARFLARE,
			 PCI_DEVICE_ID_SOLARFLARE_SFC4000A_0, fixup_mpss_256);
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_SOLARFLARE,
			 PCI_DEVICE_ID_SOLARFLARE_SFC4000A_1, fixup_mpss_256);
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_SOLARFLARE,
			 PCI_DEVICE_ID_SOLARFLARE_SFC4000B, fixup_mpss_256);

/*
 * Intel 5000 and 5100 Memory controllers have an erratum with पढ़ो completion
 * coalescing (which is enabled by शेष on some BIOSes) and MPS of 256B.
 * Since there is no way of knowing what the PCIe MPS on each fabric will be
 * until all of the devices are discovered and buses walked, पढ़ो completion
 * coalescing must be disabled.  Unक्रमtunately, it cannot be re-enabled because
 * it is possible to hotplug a device with MPS of 256B.
 */
अटल व्योम quirk_पूर्णांकel_mc_errata(काष्ठा pci_dev *dev)
अणु
	पूर्णांक err;
	u16 rcc;

	अगर (pcie_bus_config == PCIE_BUS_TUNE_OFF ||
	    pcie_bus_config == PCIE_BUS_DEFAULT)
		वापस;

	/*
	 * Intel erratum specअगरies bits to change but करोes not say what
	 * they are.  Keeping them magical until such समय as the रेजिस्टरs
	 * and values can be explained.
	 */
	err = pci_पढ़ो_config_word(dev, 0x48, &rcc);
	अगर (err) अणु
		pci_err(dev, "Error attempting to read the read completion coalescing register\n");
		वापस;
	पूर्ण

	अगर (!(rcc & (1 << 10)))
		वापस;

	rcc &= ~(1 << 10);

	err = pci_ग_लिखो_config_word(dev, 0x48, rcc);
	अगर (err) अणु
		pci_err(dev, "Error attempting to write the read completion coalescing register\n");
		वापस;
	पूर्ण

	pr_info_once("Read completion coalescing disabled due to hardware erratum relating to 256B MPS\n");
पूर्ण
/* Intel 5000 series memory controllers and ports 2-7 */
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_INTEL, 0x25c0, quirk_पूर्णांकel_mc_errata);
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_INTEL, 0x25d0, quirk_पूर्णांकel_mc_errata);
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_INTEL, 0x25d4, quirk_पूर्णांकel_mc_errata);
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_INTEL, 0x25d8, quirk_पूर्णांकel_mc_errata);
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_INTEL, 0x25e2, quirk_पूर्णांकel_mc_errata);
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_INTEL, 0x25e3, quirk_पूर्णांकel_mc_errata);
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_INTEL, 0x25e4, quirk_पूर्णांकel_mc_errata);
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_INTEL, 0x25e5, quirk_पूर्णांकel_mc_errata);
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_INTEL, 0x25e6, quirk_पूर्णांकel_mc_errata);
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_INTEL, 0x25e7, quirk_पूर्णांकel_mc_errata);
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_INTEL, 0x25f7, quirk_पूर्णांकel_mc_errata);
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_INTEL, 0x25f8, quirk_पूर्णांकel_mc_errata);
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_INTEL, 0x25f9, quirk_पूर्णांकel_mc_errata);
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_INTEL, 0x25fa, quirk_पूर्णांकel_mc_errata);
/* Intel 5100 series memory controllers and ports 2-7 */
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_INTEL, 0x65c0, quirk_पूर्णांकel_mc_errata);
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_INTEL, 0x65e2, quirk_पूर्णांकel_mc_errata);
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_INTEL, 0x65e3, quirk_पूर्णांकel_mc_errata);
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_INTEL, 0x65e4, quirk_पूर्णांकel_mc_errata);
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_INTEL, 0x65e5, quirk_पूर्णांकel_mc_errata);
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_INTEL, 0x65e6, quirk_पूर्णांकel_mc_errata);
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_INTEL, 0x65e7, quirk_पूर्णांकel_mc_errata);
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_INTEL, 0x65f7, quirk_पूर्णांकel_mc_errata);
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_INTEL, 0x65f8, quirk_पूर्णांकel_mc_errata);
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_INTEL, 0x65f9, quirk_पूर्णांकel_mc_errata);
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_INTEL, 0x65fa, quirk_पूर्णांकel_mc_errata);

/*
 * Ivytown NTB BAR sizes are misreported by the hardware due to an erratum.
 * To work around this, query the size it should be configured to by the
 * device and modअगरy the resource end to correspond to this new size.
 */
अटल व्योम quirk_पूर्णांकel_ntb(काष्ठा pci_dev *dev)
अणु
	पूर्णांक rc;
	u8 val;

	rc = pci_पढ़ो_config_byte(dev, 0x00D0, &val);
	अगर (rc)
		वापस;

	dev->resource[2].end = dev->resource[2].start + ((u64) 1 << val) - 1;

	rc = pci_पढ़ो_config_byte(dev, 0x00D1, &val);
	अगर (rc)
		वापस;

	dev->resource[4].end = dev->resource[4].start + ((u64) 1 << val) - 1;
पूर्ण
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_INTEL, 0x0e08, quirk_पूर्णांकel_ntb);
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_INTEL, 0x0e0d, quirk_पूर्णांकel_ntb);

/*
 * Some BIOS implementations leave the Intel GPU पूर्णांकerrupts enabled, even
 * though no one is handling them (e.g., अगर the i915 driver is never
 * loaded).  Additionally the पूर्णांकerrupt destination is not set up properly
 * and the पूर्णांकerrupt ends up -somewhere-.
 *
 * These spurious पूर्णांकerrupts are "sticky" and the kernel disables the
 * (shared) पूर्णांकerrupt line after 100,000+ generated पूर्णांकerrupts.
 *
 * Fix it by disabling the still enabled पूर्णांकerrupts.  This resolves crashes
 * often seen on monitor unplug.
 */
#घोषणा I915_DEIER_REG 0x4400c
अटल व्योम disable_igfx_irq(काष्ठा pci_dev *dev)
अणु
	व्योम __iomem *regs = pci_iomap(dev, 0, 0);
	अगर (regs == शून्य) अणु
		pci_warn(dev, "igfx quirk: Can't iomap PCI device\n");
		वापस;
	पूर्ण

	/* Check अगर any पूर्णांकerrupt line is still enabled */
	अगर (पढ़ोl(regs + I915_DEIER_REG) != 0) अणु
		pci_warn(dev, "BIOS left Intel GPU interrupts enabled; disabling\n");

		ग_लिखोl(0, regs + I915_DEIER_REG);
	पूर्ण

	pci_iounmap(dev, regs);
पूर्ण
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_INTEL, 0x0042, disable_igfx_irq);
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_INTEL, 0x0046, disable_igfx_irq);
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_INTEL, 0x004a, disable_igfx_irq);
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_INTEL, 0x0102, disable_igfx_irq);
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_INTEL, 0x0106, disable_igfx_irq);
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_INTEL, 0x010a, disable_igfx_irq);
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_INTEL, 0x0152, disable_igfx_irq);

/*
 * PCI devices which are on Intel chips can skip the 10ms delay
 * beक्रमe entering D3 mode.
 */
अटल व्योम quirk_हटाओ_d3hot_delay(काष्ठा pci_dev *dev)
अणु
	dev->d3hot_delay = 0;
पूर्ण
/* C600 Series devices करो not need 10ms d3hot_delay */
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_INTEL, 0x0412, quirk_हटाओ_d3hot_delay);
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_INTEL, 0x0c00, quirk_हटाओ_d3hot_delay);
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_INTEL, 0x0c0c, quirk_हटाओ_d3hot_delay);
/* Lynxpoपूर्णांक-H PCH devices करो not need 10ms d3hot_delay */
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_INTEL, 0x8c02, quirk_हटाओ_d3hot_delay);
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_INTEL, 0x8c18, quirk_हटाओ_d3hot_delay);
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_INTEL, 0x8c1c, quirk_हटाओ_d3hot_delay);
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_INTEL, 0x8c20, quirk_हटाओ_d3hot_delay);
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_INTEL, 0x8c22, quirk_हटाओ_d3hot_delay);
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_INTEL, 0x8c26, quirk_हटाओ_d3hot_delay);
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_INTEL, 0x8c2d, quirk_हटाओ_d3hot_delay);
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_INTEL, 0x8c31, quirk_हटाओ_d3hot_delay);
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_INTEL, 0x8c3a, quirk_हटाओ_d3hot_delay);
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_INTEL, 0x8c3d, quirk_हटाओ_d3hot_delay);
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_INTEL, 0x8c4e, quirk_हटाओ_d3hot_delay);
/* Intel Cherrytrail devices करो not need 10ms d3hot_delay */
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_INTEL, 0x2280, quirk_हटाओ_d3hot_delay);
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_INTEL, 0x2298, quirk_हटाओ_d3hot_delay);
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_INTEL, 0x229c, quirk_हटाओ_d3hot_delay);
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_INTEL, 0x22b0, quirk_हटाओ_d3hot_delay);
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_INTEL, 0x22b5, quirk_हटाओ_d3hot_delay);
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_INTEL, 0x22b7, quirk_हटाओ_d3hot_delay);
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_INTEL, 0x22b8, quirk_हटाओ_d3hot_delay);
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_INTEL, 0x22d8, quirk_हटाओ_d3hot_delay);
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_INTEL, 0x22dc, quirk_हटाओ_d3hot_delay);

/*
 * Some devices may pass our check in pci_पूर्णांकx_mask_supported() अगर
 * PCI_COMMAND_INTX_DISABLE works though they actually करो not properly
 * support this feature.
 */
अटल व्योम quirk_broken_पूर्णांकx_masking(काष्ठा pci_dev *dev)
अणु
	dev->broken_पूर्णांकx_masking = 1;
पूर्ण
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_CHELSIO, 0x0030,
			quirk_broken_पूर्णांकx_masking);
DECLARE_PCI_FIXUP_FINAL(0x1814, 0x0601, /* Ralink RT2800 802.11n PCI */
			quirk_broken_पूर्णांकx_masking);
DECLARE_PCI_FIXUP_FINAL(0x1b7c, 0x0004, /* Ceton InfiniTV4 */
			quirk_broken_पूर्णांकx_masking);

/*
 * Realtek RTL8169 PCI Gigabit Ethernet Controller (rev 10)
 * Subप्रणाली: Realtek RTL8169/8110 Family PCI Gigabit Ethernet NIC
 *
 * RTL8110SC - Fails under PCI device assignment using DisINTx masking.
 */
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_REALTEK, 0x8169,
			quirk_broken_पूर्णांकx_masking);

/*
 * Intel i40e (XL710/X710) 10/20/40GbE NICs all have broken INTx masking,
 * DisINTx can be set but the पूर्णांकerrupt status bit is non-functional.
 */
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_INTEL, 0x1572, quirk_broken_पूर्णांकx_masking);
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_INTEL, 0x1574, quirk_broken_पूर्णांकx_masking);
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_INTEL, 0x1580, quirk_broken_पूर्णांकx_masking);
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_INTEL, 0x1581, quirk_broken_पूर्णांकx_masking);
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_INTEL, 0x1583, quirk_broken_पूर्णांकx_masking);
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_INTEL, 0x1584, quirk_broken_पूर्णांकx_masking);
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_INTEL, 0x1585, quirk_broken_पूर्णांकx_masking);
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_INTEL, 0x1586, quirk_broken_पूर्णांकx_masking);
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_INTEL, 0x1587, quirk_broken_पूर्णांकx_masking);
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_INTEL, 0x1588, quirk_broken_पूर्णांकx_masking);
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_INTEL, 0x1589, quirk_broken_पूर्णांकx_masking);
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_INTEL, 0x158a, quirk_broken_पूर्णांकx_masking);
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_INTEL, 0x158b, quirk_broken_पूर्णांकx_masking);
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_INTEL, 0x37d0, quirk_broken_पूर्णांकx_masking);
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_INTEL, 0x37d1, quirk_broken_पूर्णांकx_masking);
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_INTEL, 0x37d2, quirk_broken_पूर्णांकx_masking);

अटल u16 mellanox_broken_पूर्णांकx_devs[] = अणु
	PCI_DEVICE_ID_MELLANOX_HERMON_SDR,
	PCI_DEVICE_ID_MELLANOX_HERMON_DDR,
	PCI_DEVICE_ID_MELLANOX_HERMON_QDR,
	PCI_DEVICE_ID_MELLANOX_HERMON_DDR_GEN2,
	PCI_DEVICE_ID_MELLANOX_HERMON_QDR_GEN2,
	PCI_DEVICE_ID_MELLANOX_HERMON_EN,
	PCI_DEVICE_ID_MELLANOX_HERMON_EN_GEN2,
	PCI_DEVICE_ID_MELLANOX_CONNECTX_EN,
	PCI_DEVICE_ID_MELLANOX_CONNECTX_EN_T_GEN2,
	PCI_DEVICE_ID_MELLANOX_CONNECTX_EN_GEN2,
	PCI_DEVICE_ID_MELLANOX_CONNECTX_EN_5_GEN2,
	PCI_DEVICE_ID_MELLANOX_CONNECTX2,
	PCI_DEVICE_ID_MELLANOX_CONNECTX3,
	PCI_DEVICE_ID_MELLANOX_CONNECTX3_PRO,
पूर्ण;

#घोषणा CONNECTX_4_CURR_MAX_MINOR 99
#घोषणा CONNECTX_4_INTX_SUPPORT_MINOR 14

/*
 * Check ConnectX-4/LX FW version to see अगर it supports legacy पूर्णांकerrupts.
 * If so, करोn't mark it as broken.
 * FW minor > 99 means older FW version क्रमmat and no INTx masking support.
 * FW minor < 14 means new FW version क्रमmat and no INTx masking support.
 */
अटल व्योम mellanox_check_broken_पूर्णांकx_masking(काष्ठा pci_dev *pdev)
अणु
	__be32 __iomem *fw_ver;
	u16 fw_major;
	u16 fw_minor;
	u16 fw_subminor;
	u32 fw_maj_min;
	u32 fw_sub_min;
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(mellanox_broken_पूर्णांकx_devs); i++) अणु
		अगर (pdev->device == mellanox_broken_पूर्णांकx_devs[i]) अणु
			pdev->broken_पूर्णांकx_masking = 1;
			वापस;
		पूर्ण
	पूर्ण

	/*
	 * Getting here means Connect-IB cards and up. Connect-IB has no INTx
	 * support so shouldn't be checked further
	 */
	अगर (pdev->device == PCI_DEVICE_ID_MELLANOX_CONNECTIB)
		वापस;

	अगर (pdev->device != PCI_DEVICE_ID_MELLANOX_CONNECTX4 &&
	    pdev->device != PCI_DEVICE_ID_MELLANOX_CONNECTX4_LX)
		वापस;

	/* For ConnectX-4 and ConnectX-4LX, need to check FW support */
	अगर (pci_enable_device_mem(pdev)) अणु
		pci_warn(pdev, "Can't enable device memory\n");
		वापस;
	पूर्ण

	fw_ver = ioremap(pci_resource_start(pdev, 0), 4);
	अगर (!fw_ver) अणु
		pci_warn(pdev, "Can't map ConnectX-4 initialization segment\n");
		जाओ out;
	पूर्ण

	/* Reading from resource space should be 32b aligned */
	fw_maj_min = ioपढ़ो32be(fw_ver);
	fw_sub_min = ioपढ़ो32be(fw_ver + 1);
	fw_major = fw_maj_min & 0xffff;
	fw_minor = fw_maj_min >> 16;
	fw_subminor = fw_sub_min & 0xffff;
	अगर (fw_minor > CONNECTX_4_CURR_MAX_MINOR ||
	    fw_minor < CONNECTX_4_INTX_SUPPORT_MINOR) अणु
		pci_warn(pdev, "ConnectX-4: FW %u.%u.%u doesn't support INTx masking, disabling. Please upgrade FW to %d.14.1100 and up for INTx support\n",
			 fw_major, fw_minor, fw_subminor, pdev->device ==
			 PCI_DEVICE_ID_MELLANOX_CONNECTX4 ? 12 : 14);
		pdev->broken_पूर्णांकx_masking = 1;
	पूर्ण

	iounmap(fw_ver);

out:
	pci_disable_device(pdev);
पूर्ण
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_MELLANOX, PCI_ANY_ID,
			mellanox_check_broken_पूर्णांकx_masking);

अटल व्योम quirk_no_bus_reset(काष्ठा pci_dev *dev)
अणु
	dev->dev_flags |= PCI_DEV_FLAGS_NO_BUS_RESET;
पूर्ण

/*
 * Some NVIDIA GPU devices करो not work with bus reset, SBR needs to be
 * prevented क्रम those affected devices.
 */
अटल व्योम quirk_nvidia_no_bus_reset(काष्ठा pci_dev *dev)
अणु
	अगर ((dev->device & 0xffc0) == 0x2340)
		quirk_no_bus_reset(dev);
पूर्ण
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_NVIDIA, PCI_ANY_ID,
			 quirk_nvidia_no_bus_reset);

/*
 * Some Atheros AR9xxx and QCA988x chips करो not behave after a bus reset.
 * The device will throw a Link Down error on AER-capable प्रणालीs and
 * regardless of AER, config space of the device is never accessible again
 * and typically causes the प्रणाली to hang or reset when access is attempted.
 * https://lore.kernel.org/r/20140923210318.498dacbd@dualc.maya.org/
 */
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_ATHEROS, 0x0030, quirk_no_bus_reset);
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_ATHEROS, 0x0032, quirk_no_bus_reset);
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_ATHEROS, 0x003c, quirk_no_bus_reset);
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_ATHEROS, 0x0033, quirk_no_bus_reset);
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_ATHEROS, 0x0034, quirk_no_bus_reset);

/*
 * Root port on some Cavium CN8xxx chips करो not successfully complete a bus
 * reset when used with certain child devices.  After the reset, config
 * accesses to the child may fail.
 */
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_CAVIUM, 0xa100, quirk_no_bus_reset);

/*
 * Some TI KeyStone C667X devices करो not support bus/hot reset.  The PCIESS
 * स्वतःmatically disables LTSSM when Secondary Bus Reset is received and
 * the device stops working.  Prevent bus reset क्रम these devices.  With
 * this change, the device can be asचिन्हित to VMs with VFIO, but it will
 * leak state between VMs.  Reference
 * https://e2e.ti.com/support/processors/f/791/t/954382
 */
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_TI, 0xb005, quirk_no_bus_reset);

अटल व्योम quirk_no_pm_reset(काष्ठा pci_dev *dev)
अणु
	/*
	 * We can't करो a bus reset on root bus devices, but an ineffective
	 * PM reset may be better than nothing.
	 */
	अगर (!pci_is_root_bus(dev->bus))
		dev->dev_flags |= PCI_DEV_FLAGS_NO_PM_RESET;
पूर्ण

/*
 * Some AMD/ATI GPUS (HD8570 - Oland) report that a D3hot->D0 transition
 * causes a reset (i.e., they advertise NoSoftRst-).  This transition seems
 * to have no effect on the device: it retains the framebuffer contents and
 * monitor sync.  Advertising this support makes other layers, like VFIO,
 * assume pci_reset_function() is viable क्रम this device.  Mark it as
 * unavailable to skip it when testing reset methods.
 */
DECLARE_PCI_FIXUP_CLASS_HEADER(PCI_VENDOR_ID_ATI, PCI_ANY_ID,
			       PCI_CLASS_DISPLAY_VGA, 8, quirk_no_pm_reset);

/*
 * Thunderbolt controllers with broken MSI hotplug संकेतing:
 * Entire 1st generation (Light Ridge, Eagle Ridge, Light Peak) and part
 * of the 2nd generation (Cactus Ridge 4C up to revision 1, Port Ridge).
 */
अटल व्योम quirk_thunderbolt_hotplug_msi(काष्ठा pci_dev *pdev)
अणु
	अगर (pdev->is_hotplug_bridge &&
	    (pdev->device != PCI_DEVICE_ID_INTEL_CACTUS_RIDGE_4C ||
	     pdev->revision <= 1))
		pdev->no_msi = 1;
पूर्ण
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_INTEL, PCI_DEVICE_ID_INTEL_LIGHT_RIDGE,
			quirk_thunderbolt_hotplug_msi);
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_INTEL, PCI_DEVICE_ID_INTEL_EAGLE_RIDGE,
			quirk_thunderbolt_hotplug_msi);
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_INTEL, PCI_DEVICE_ID_INTEL_LIGHT_PEAK,
			quirk_thunderbolt_hotplug_msi);
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_INTEL, PCI_DEVICE_ID_INTEL_CACTUS_RIDGE_4C,
			quirk_thunderbolt_hotplug_msi);
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_INTEL, PCI_DEVICE_ID_INTEL_PORT_RIDGE,
			quirk_thunderbolt_hotplug_msi);

#अगर_घोषित CONFIG_ACPI
/*
 * Apple: Shutकरोwn Cactus Ridge Thunderbolt controller.
 *
 * On Apple hardware the Cactus Ridge Thunderbolt controller needs to be
 * shutकरोwn beक्रमe suspend. Otherwise the native host पूर्णांकerface (NHI) will not
 * be present after resume अगर a device was plugged in beक्रमe suspend.
 *
 * The Thunderbolt controller consists of a PCIe चयन with करोwnstream
 * bridges leading to the NHI and to the tunnel PCI bridges.
 *
 * This quirk cuts घातer to the whole chip. Thereक्रमe we have to apply it
 * during suspend_noirq of the upstream bridge.
 *
 * Power is स्वतःmagically restored beक्रमe resume. No action is needed.
 */
अटल व्योम quirk_apple_घातeroff_thunderbolt(काष्ठा pci_dev *dev)
अणु
	acpi_handle bridge, SXIO, SXFP, SXLV;

	अगर (!x86_apple_machine)
		वापस;
	अगर (pci_pcie_type(dev) != PCI_EXP_TYPE_UPSTREAM)
		वापस;
	bridge = ACPI_HANDLE(&dev->dev);
	अगर (!bridge)
		वापस;

	/*
	 * SXIO and SXLV are present only on machines requiring this quirk.
	 * Thunderbolt bridges in बाह्यal devices might have the same
	 * device ID as those on the host, but they will not have the
	 * associated ACPI methods. This implicitly checks that we are at
	 * the right bridge.
	 */
	अगर (ACPI_FAILURE(acpi_get_handle(bridge, "DSB0.NHI0.SXIO", &SXIO))
	    || ACPI_FAILURE(acpi_get_handle(bridge, "DSB0.NHI0.SXFP", &SXFP))
	    || ACPI_FAILURE(acpi_get_handle(bridge, "DSB0.NHI0.SXLV", &SXLV)))
		वापस;
	pci_info(dev, "quirk: cutting power to Thunderbolt controller...\n");

	/* magic sequence */
	acpi_execute_simple_method(SXIO, शून्य, 1);
	acpi_execute_simple_method(SXFP, शून्य, 0);
	msleep(300);
	acpi_execute_simple_method(SXLV, शून्य, 0);
	acpi_execute_simple_method(SXIO, शून्य, 0);
	acpi_execute_simple_method(SXLV, शून्य, 0);
पूर्ण
DECLARE_PCI_FIXUP_SUSPEND_LATE(PCI_VENDOR_ID_INTEL,
			       PCI_DEVICE_ID_INTEL_CACTUS_RIDGE_4C,
			       quirk_apple_घातeroff_thunderbolt);
#पूर्ण_अगर

/*
 * Following are device-specअगरic reset methods which can be used to
 * reset a single function अगर other methods (e.g. FLR, PM D0->D3) are
 * not available.
 */
अटल पूर्णांक reset_पूर्णांकel_82599_sfp_virtfn(काष्ठा pci_dev *dev, पूर्णांक probe)
अणु
	/*
	 * http://www.पूर्णांकel.com/content/dam/करोc/datasheet/82599-10-gbe-controller-datasheet.pdf
	 *
	 * The 82599 supports FLR on VFs, but FLR support is reported only
	 * in the PF DEVCAP (sec 9.3.10.4), not in the VF DEVCAP (sec 9.5).
	 * Thus we must call pcie_flr() directly without first checking अगर it is
	 * supported.
	 */
	अगर (!probe)
		pcie_flr(dev);
	वापस 0;
पूर्ण

#घोषणा SOUTH_CHICKEN2		0xc2004
#घोषणा PCH_PP_STATUS		0xc7200
#घोषणा PCH_PP_CONTROL		0xc7204
#घोषणा MSG_CTL			0x45010
#घोषणा NSDE_PWR_STATE		0xd0100
#घोषणा IGD_OPERATION_TIMEOUT	10000     /* set समयout 10 seconds */

अटल पूर्णांक reset_ivb_igd(काष्ठा pci_dev *dev, पूर्णांक probe)
अणु
	व्योम __iomem *mmio_base;
	अचिन्हित दीर्घ समयout;
	u32 val;

	अगर (probe)
		वापस 0;

	mmio_base = pci_iomap(dev, 0, 0);
	अगर (!mmio_base)
		वापस -ENOMEM;

	ioग_लिखो32(0x00000002, mmio_base + MSG_CTL);

	/*
	 * Clobbering SOUTH_CHICKEN2 रेजिस्टर is fine only अगर the next
	 * driver loaded sets the right bits. However, this's a reset and
	 * the bits have been set by i915 previously, so we clobber
	 * SOUTH_CHICKEN2 रेजिस्टर directly here.
	 */
	ioग_लिखो32(0x00000005, mmio_base + SOUTH_CHICKEN2);

	val = ioपढ़ो32(mmio_base + PCH_PP_CONTROL) & 0xfffffffe;
	ioग_लिखो32(val, mmio_base + PCH_PP_CONTROL);

	समयout = jअगरfies + msecs_to_jअगरfies(IGD_OPERATION_TIMEOUT);
	करो अणु
		val = ioपढ़ो32(mmio_base + PCH_PP_STATUS);
		अगर ((val & 0xb0000000) == 0)
			जाओ reset_complete;
		msleep(10);
	पूर्ण जबतक (समय_beक्रमe(jअगरfies, समयout));
	pci_warn(dev, "timeout during reset\n");

reset_complete:
	ioग_लिखो32(0x00000002, mmio_base + NSDE_PWR_STATE);

	pci_iounmap(dev, mmio_base);
	वापस 0;
पूर्ण

/* Device-specअगरic reset method क्रम Chelsio T4-based adapters */
अटल पूर्णांक reset_chelsio_generic_dev(काष्ठा pci_dev *dev, पूर्णांक probe)
अणु
	u16 old_command;
	u16 msix_flags;

	/*
	 * If this isn't a Chelsio T4-based device, वापस -ENOTTY indicating
	 * that we have no device-specअगरic reset method.
	 */
	अगर ((dev->device & 0xf000) != 0x4000)
		वापस -ENOTTY;

	/*
	 * If this is the "probe" phase, वापस 0 indicating that we can
	 * reset this device.
	 */
	अगर (probe)
		वापस 0;

	/*
	 * T4 can wedge अगर there are DMAs in flight within the chip and Bus
	 * Master has been disabled.  We need to have it on till the Function
	 * Level Reset completes.  (BUS_MASTER is disabled in
	 * pci_reset_function()).
	 */
	pci_पढ़ो_config_word(dev, PCI_COMMAND, &old_command);
	pci_ग_लिखो_config_word(dev, PCI_COMMAND,
			      old_command | PCI_COMMAND_MASTER);

	/*
	 * Perक्रमm the actual device function reset, saving and restoring
	 * configuration inक्रमmation around the reset.
	 */
	pci_save_state(dev);

	/*
	 * T4 also suffers a Head-Of-Line blocking problem अगर MSI-X पूर्णांकerrupts
	 * are disabled when an MSI-X पूर्णांकerrupt message needs to be delivered.
	 * So we briefly re-enable MSI-X पूर्णांकerrupts क्रम the duration of the
	 * FLR.  The pci_restore_state() below will restore the original
	 * MSI-X state.
	 */
	pci_पढ़ो_config_word(dev, dev->msix_cap+PCI_MSIX_FLAGS, &msix_flags);
	अगर ((msix_flags & PCI_MSIX_FLAGS_ENABLE) == 0)
		pci_ग_लिखो_config_word(dev, dev->msix_cap+PCI_MSIX_FLAGS,
				      msix_flags |
				      PCI_MSIX_FLAGS_ENABLE |
				      PCI_MSIX_FLAGS_MASKALL);

	pcie_flr(dev);

	/*
	 * Restore the configuration inक्रमmation (BAR values, etc.) including
	 * the original PCI Configuration Space Command word, and वापस
	 * success.
	 */
	pci_restore_state(dev);
	pci_ग_लिखो_config_word(dev, PCI_COMMAND, old_command);
	वापस 0;
पूर्ण

#घोषणा PCI_DEVICE_ID_INTEL_82599_SFP_VF   0x10ed
#घोषणा PCI_DEVICE_ID_INTEL_IVB_M_VGA      0x0156
#घोषणा PCI_DEVICE_ID_INTEL_IVB_M2_VGA     0x0166

/*
 * The Samsung SM961/PM961 controller can someबार enter a fatal state after
 * FLR where config space पढ़ोs from the device वापस -1.  We seem to be
 * able to aव्योम this condition अगर we disable the NVMe controller prior to
 * FLR.  This quirk is generic क्रम any NVMe class device requiring similar
 * assistance to quiesce the device prior to FLR.
 *
 * NVMe specअगरication: https://nvmexpress.org/resources/specअगरications/
 * Revision 1.0e:
 *    Chapter 2: Required and optional PCI config रेजिस्टरs
 *    Chapter 3: NVMe control रेजिस्टरs
 *    Chapter 7.3: Reset behavior
 */
अटल पूर्णांक nvme_disable_and_flr(काष्ठा pci_dev *dev, पूर्णांक probe)
अणु
	व्योम __iomem *bar;
	u16 cmd;
	u32 cfg;

	अगर (dev->class != PCI_CLASS_STORAGE_EXPRESS ||
	    !pcie_has_flr(dev) || !pci_resource_start(dev, 0))
		वापस -ENOTTY;

	अगर (probe)
		वापस 0;

	bar = pci_iomap(dev, 0, NVME_REG_CC + माप(cfg));
	अगर (!bar)
		वापस -ENOTTY;

	pci_पढ़ो_config_word(dev, PCI_COMMAND, &cmd);
	pci_ग_लिखो_config_word(dev, PCI_COMMAND, cmd | PCI_COMMAND_MEMORY);

	cfg = पढ़ोl(bar + NVME_REG_CC);

	/* Disable controller अगर enabled */
	अगर (cfg & NVME_CC_ENABLE) अणु
		u32 cap = पढ़ोl(bar + NVME_REG_CAP);
		अचिन्हित दीर्घ समयout;

		/*
		 * Per nvme_disable_ctrl() skip shutकरोwn notअगरication as it
		 * could complete commands to the admin queue.  We only पूर्णांकend
		 * to quiesce the device beक्रमe reset.
		 */
		cfg &= ~(NVME_CC_SHN_MASK | NVME_CC_ENABLE);

		ग_लिखोl(cfg, bar + NVME_REG_CC);

		/*
		 * Some controllers require an additional delay here, see
		 * NVME_QUIRK_DELAY_BEFORE_CHK_RDY.  None of those are yet
		 * supported by this quirk.
		 */

		/* Cap रेजिस्टर provides max समयout in 500ms increments */
		समयout = ((NVME_CAP_TIMEOUT(cap) + 1) * HZ / 2) + jअगरfies;

		क्रम (;;) अणु
			u32 status = पढ़ोl(bar + NVME_REG_CSTS);

			/* Ready status becomes zero on disable complete */
			अगर (!(status & NVME_CSTS_RDY))
				अवरोध;

			msleep(100);

			अगर (समय_after(jअगरfies, समयout)) अणु
				pci_warn(dev, "Timeout waiting for NVMe ready status to clear after disable\n");
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	pci_iounmap(dev, bar);

	pcie_flr(dev);

	वापस 0;
पूर्ण

/*
 * Intel DC P3700 NVMe controller will समयout रुकोing क्रम पढ़ोy status
 * to change after NVMe enable अगर the driver starts पूर्णांकeracting with the
 * device too soon after FLR.  A 250ms delay after FLR has heuristically
 * proven to produce reliably working results क्रम device assignment हालs.
 */
अटल पूर्णांक delay_250ms_after_flr(काष्ठा pci_dev *dev, पूर्णांक probe)
अणु
	अगर (!pcie_has_flr(dev))
		वापस -ENOTTY;

	अगर (probe)
		वापस 0;

	pcie_flr(dev);

	msleep(250);

	वापस 0;
पूर्ण

#घोषणा PCI_DEVICE_ID_HINIC_VF      0x375E
#घोषणा HINIC_VF_FLR_TYPE           0x1000
#घोषणा HINIC_VF_FLR_CAP_BIT        (1UL << 30)
#घोषणा HINIC_VF_OP                 0xE80
#घोषणा HINIC_VF_FLR_PROC_BIT       (1UL << 18)
#घोषणा HINIC_OPERATION_TIMEOUT     15000	/* 15 seconds */

/* Device-specअगरic reset method क्रम Huawei Intelligent NIC भव functions */
अटल पूर्णांक reset_hinic_vf_dev(काष्ठा pci_dev *pdev, पूर्णांक probe)
अणु
	अचिन्हित दीर्घ समयout;
	व्योम __iomem *bar;
	u32 val;

	अगर (probe)
		वापस 0;

	bar = pci_iomap(pdev, 0, 0);
	अगर (!bar)
		वापस -ENOTTY;

	/* Get and check firmware capabilities */
	val = ioपढ़ो32be(bar + HINIC_VF_FLR_TYPE);
	अगर (!(val & HINIC_VF_FLR_CAP_BIT)) अणु
		pci_iounmap(pdev, bar);
		वापस -ENOTTY;
	पूर्ण

	/* Set HINIC_VF_FLR_PROC_BIT क्रम the start of FLR */
	val = ioपढ़ो32be(bar + HINIC_VF_OP);
	val = val | HINIC_VF_FLR_PROC_BIT;
	ioग_लिखो32be(val, bar + HINIC_VF_OP);

	pcie_flr(pdev);

	/*
	 * The device must recapture its Bus and Device Numbers after FLR
	 * in order generate Completions.  Issue a config ग_लिखो to let the
	 * device capture this inक्रमmation.
	 */
	pci_ग_लिखो_config_word(pdev, PCI_VENDOR_ID, 0);

	/* Firmware clears HINIC_VF_FLR_PROC_BIT when reset is complete */
	समयout = jअगरfies + msecs_to_jअगरfies(HINIC_OPERATION_TIMEOUT);
	करो अणु
		val = ioपढ़ो32be(bar + HINIC_VF_OP);
		अगर (!(val & HINIC_VF_FLR_PROC_BIT))
			जाओ reset_complete;
		msleep(20);
	पूर्ण जबतक (समय_beक्रमe(jअगरfies, समयout));

	val = ioपढ़ो32be(bar + HINIC_VF_OP);
	अगर (!(val & HINIC_VF_FLR_PROC_BIT))
		जाओ reset_complete;

	pci_warn(pdev, "Reset dev timeout, FLR ack reg: %#010x\n", val);

reset_complete:
	pci_iounmap(pdev, bar);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा pci_dev_reset_methods pci_dev_reset_methods[] = अणु
	अणु PCI_VENDOR_ID_INTEL, PCI_DEVICE_ID_INTEL_82599_SFP_VF,
		 reset_पूर्णांकel_82599_sfp_virtfn पूर्ण,
	अणु PCI_VENDOR_ID_INTEL, PCI_DEVICE_ID_INTEL_IVB_M_VGA,
		reset_ivb_igd पूर्ण,
	अणु PCI_VENDOR_ID_INTEL, PCI_DEVICE_ID_INTEL_IVB_M2_VGA,
		reset_ivb_igd पूर्ण,
	अणु PCI_VENDOR_ID_SAMSUNG, 0xa804, nvme_disable_and_flr पूर्ण,
	अणु PCI_VENDOR_ID_INTEL, 0x0953, delay_250ms_after_flr पूर्ण,
	अणु PCI_VENDOR_ID_INTEL, 0x0a54, delay_250ms_after_flr पूर्ण,
	अणु PCI_VENDOR_ID_CHELSIO, PCI_ANY_ID,
		reset_chelsio_generic_dev पूर्ण,
	अणु PCI_VENDOR_ID_HUAWEI, PCI_DEVICE_ID_HINIC_VF,
		reset_hinic_vf_dev पूर्ण,
	अणु 0 पूर्ण
पूर्ण;

/*
 * These device-specअगरic reset methods are here rather than in a driver
 * because when a host assigns a device to a guest VM, the host may need
 * to reset the device but probably करोesn't have a driver क्रम it.
 */
पूर्णांक pci_dev_specअगरic_reset(काष्ठा pci_dev *dev, पूर्णांक probe)
अणु
	स्थिर काष्ठा pci_dev_reset_methods *i;

	क्रम (i = pci_dev_reset_methods; i->reset; i++) अणु
		अगर ((i->venकरोr == dev->venकरोr ||
		     i->venकरोr == (u16)PCI_ANY_ID) &&
		    (i->device == dev->device ||
		     i->device == (u16)PCI_ANY_ID))
			वापस i->reset(dev, probe);
	पूर्ण

	वापस -ENOTTY;
पूर्ण

अटल व्योम quirk_dma_func0_alias(काष्ठा pci_dev *dev)
अणु
	अगर (PCI_FUNC(dev->devfn) != 0)
		pci_add_dma_alias(dev, PCI_DEVFN(PCI_SLOT(dev->devfn), 0), 1);
पूर्ण

/*
 * https://bugzilla.redhat.com/show_bug.cgi?id=605888
 *
 * Some Ricoh devices use function 0 as the PCIe requester ID क्रम DMA.
 */
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_RICOH, 0xe832, quirk_dma_func0_alias);
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_RICOH, 0xe476, quirk_dma_func0_alias);

अटल व्योम quirk_dma_func1_alias(काष्ठा pci_dev *dev)
अणु
	अगर (PCI_FUNC(dev->devfn) != 1)
		pci_add_dma_alias(dev, PCI_DEVFN(PCI_SLOT(dev->devfn), 1), 1);
पूर्ण

/*
 * Marvell 88SE9123 uses function 1 as the requester ID क्रम DMA.  In some
 * SKUs function 1 is present and is a legacy IDE controller, in other
 * SKUs this function is not present, making this a ghost requester.
 * https://bugzilla.kernel.org/show_bug.cgi?id=42679
 */
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_MARVELL_EXT, 0x9120,
			 quirk_dma_func1_alias);
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_MARVELL_EXT, 0x9123,
			 quirk_dma_func1_alias);
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_MARVELL_EXT, 0x9128,
			 quirk_dma_func1_alias);
/* https://bugzilla.kernel.org/show_bug.cgi?id=42679#c14 */
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_MARVELL_EXT, 0x9130,
			 quirk_dma_func1_alias);
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_MARVELL_EXT, 0x9170,
			 quirk_dma_func1_alias);
/* https://bugzilla.kernel.org/show_bug.cgi?id=42679#c47 + c57 */
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_MARVELL_EXT, 0x9172,
			 quirk_dma_func1_alias);
/* https://bugzilla.kernel.org/show_bug.cgi?id=42679#c59 */
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_MARVELL_EXT, 0x917a,
			 quirk_dma_func1_alias);
/* https://bugzilla.kernel.org/show_bug.cgi?id=42679#c78 */
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_MARVELL_EXT, 0x9182,
			 quirk_dma_func1_alias);
/* https://bugzilla.kernel.org/show_bug.cgi?id=42679#c134 */
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_MARVELL_EXT, 0x9183,
			 quirk_dma_func1_alias);
/* https://bugzilla.kernel.org/show_bug.cgi?id=42679#c46 */
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_MARVELL_EXT, 0x91a0,
			 quirk_dma_func1_alias);
/* https://bugzilla.kernel.org/show_bug.cgi?id=42679#c135 */
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_MARVELL_EXT, 0x9215,
			 quirk_dma_func1_alias);
/* https://bugzilla.kernel.org/show_bug.cgi?id=42679#c127 */
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_MARVELL_EXT, 0x9220,
			 quirk_dma_func1_alias);
/* https://bugzilla.kernel.org/show_bug.cgi?id=42679#c49 */
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_MARVELL_EXT, 0x9230,
			 quirk_dma_func1_alias);
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_TTI, 0x0642,
			 quirk_dma_func1_alias);
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_TTI, 0x0645,
			 quirk_dma_func1_alias);
/* https://bugs.gentoo.org/show_bug.cgi?id=497630 */
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_JMICRON,
			 PCI_DEVICE_ID_JMICRON_JMB388_ESD,
			 quirk_dma_func1_alias);
/* https://bugzilla.kernel.org/show_bug.cgi?id=42679#c117 */
DECLARE_PCI_FIXUP_HEADER(0x1c28, /* Lite-On */
			 0x0122, /* Plextor M6E (Marvell 88SS9183)*/
			 quirk_dma_func1_alias);

/*
 * Some devices DMA with the wrong devfn, not just the wrong function.
 * quirk_fixed_dma_alias() uses this table to create fixed aliases, where
 * the alias is "fixed" and independent of the device devfn.
 *
 * For example, the Adaptec 3405 is a PCIe card with an Intel 80333 I/O
 * processor.  To software, this appears as a PCIe-to-PCI/X bridge with a
 * single device on the secondary bus.  In reality, the single exposed
 * device at 0e.0 is the Address Translation Unit (ATU) of the controller
 * that provides a bridge to the पूर्णांकernal bus of the I/O processor.  The
 * controller supports निजी devices, which can be hidden from PCI config
 * space.  In the हाल of the Adaptec 3405, a निजी device at 01.0
 * appears to be the DMA engine, which thereक्रमe needs to become a DMA
 * alias क्रम the device.
 */
अटल स्थिर काष्ठा pci_device_id fixed_dma_alias_tbl[] = अणु
	अणु PCI_DEVICE_SUB(PCI_VENDOR_ID_ADAPTEC2, 0x0285,
			 PCI_VENDOR_ID_ADAPTEC2, 0x02bb), /* Adaptec 3405 */
	  .driver_data = PCI_DEVFN(1, 0) पूर्ण,
	अणु PCI_DEVICE_SUB(PCI_VENDOR_ID_ADAPTEC2, 0x0285,
			 PCI_VENDOR_ID_ADAPTEC2, 0x02bc), /* Adaptec 3805 */
	  .driver_data = PCI_DEVFN(1, 0) पूर्ण,
	अणु 0 पूर्ण
पूर्ण;

अटल व्योम quirk_fixed_dma_alias(काष्ठा pci_dev *dev)
अणु
	स्थिर काष्ठा pci_device_id *id;

	id = pci_match_id(fixed_dma_alias_tbl, dev);
	अगर (id)
		pci_add_dma_alias(dev, id->driver_data, 1);
पूर्ण
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_ADAPTEC2, 0x0285, quirk_fixed_dma_alias);

/*
 * A few PCIe-to-PCI bridges fail to expose a PCIe capability, resulting in
 * using the wrong DMA alias क्रम the device.  Some of these devices can be
 * used as either क्रमward or reverse bridges, so we need to test whether the
 * device is operating in the correct mode.  We could probably apply this
 * quirk to PCI_ANY_ID, but क्रम now we'll just use known offenders.  The test
 * is क्रम a non-root, non-PCIe bridge where the upstream device is PCIe and
 * is not a PCIe-to-PCI bridge, then @pdev is actually a PCIe-to-PCI bridge.
 */
अटल व्योम quirk_use_pcie_bridge_dma_alias(काष्ठा pci_dev *pdev)
अणु
	अगर (!pci_is_root_bus(pdev->bus) &&
	    pdev->hdr_type == PCI_HEADER_TYPE_BRIDGE &&
	    !pci_is_pcie(pdev) && pci_is_pcie(pdev->bus->self) &&
	    pci_pcie_type(pdev->bus->self) != PCI_EXP_TYPE_PCI_BRIDGE)
		pdev->dev_flags |= PCI_DEV_FLAG_PCIE_BRIDGE_ALIAS;
पूर्ण
/* ASM1083/1085, https://bugzilla.kernel.org/show_bug.cgi?id=44881#c46 */
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_ASMEDIA, 0x1080,
			 quirk_use_pcie_bridge_dma_alias);
/* Tundra 8113, https://bugzilla.kernel.org/show_bug.cgi?id=44881#c43 */
DECLARE_PCI_FIXUP_HEADER(0x10e3, 0x8113, quirk_use_pcie_bridge_dma_alias);
/* ITE 8892, https://bugzilla.kernel.org/show_bug.cgi?id=73551 */
DECLARE_PCI_FIXUP_HEADER(0x1283, 0x8892, quirk_use_pcie_bridge_dma_alias);
/* ITE 8893 has the same problem as the 8892 */
DECLARE_PCI_FIXUP_HEADER(0x1283, 0x8893, quirk_use_pcie_bridge_dma_alias);
/* Intel 82801, https://bugzilla.kernel.org/show_bug.cgi?id=44881#c49 */
DECLARE_PCI_FIXUP_HEADER(0x8086, 0x244e, quirk_use_pcie_bridge_dma_alias);

/*
 * MIC x200 NTB क्रमwards PCIe traffic using multiple alien RIDs. They have to
 * be added as aliases to the DMA device in order to allow buffer access
 * when IOMMU is enabled. Following devfns have to match RIT-LUT table
 * programmed in the EEPROM.
 */
अटल व्योम quirk_mic_x200_dma_alias(काष्ठा pci_dev *pdev)
अणु
	pci_add_dma_alias(pdev, PCI_DEVFN(0x10, 0x0), 1);
	pci_add_dma_alias(pdev, PCI_DEVFN(0x11, 0x0), 1);
	pci_add_dma_alias(pdev, PCI_DEVFN(0x12, 0x3), 1);
पूर्ण
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_INTEL, 0x2260, quirk_mic_x200_dma_alias);
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_INTEL, 0x2264, quirk_mic_x200_dma_alias);

/*
 * Intel Visual Compute Accelerator (VCA) is a family of PCIe add-in devices
 * exposing computational units via Non Transparent Bridges (NTB, PEX 87xx).
 *
 * Similarly to MIC x200, we need to add DMA aliases to allow buffer access
 * when IOMMU is enabled.  These aliases allow computational unit access to
 * host memory.  These aliases mark the whole VCA device as one IOMMU
 * group.
 *
 * All possible slot numbers (0x20) are used, since we are unable to tell
 * what slot is used on other side.  This quirk is पूर्णांकended क्रम both host
 * and computational unit sides.  The VCA devices have up to five functions
 * (four क्रम DMA channels and one additional).
 */
अटल व्योम quirk_pex_vca_alias(काष्ठा pci_dev *pdev)
अणु
	स्थिर अचिन्हित पूर्णांक num_pci_slots = 0x20;
	अचिन्हित पूर्णांक slot;

	क्रम (slot = 0; slot < num_pci_slots; slot++)
		pci_add_dma_alias(pdev, PCI_DEVFN(slot, 0x0), 5);
पूर्ण
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_INTEL, 0x2954, quirk_pex_vca_alias);
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_INTEL, 0x2955, quirk_pex_vca_alias);
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_INTEL, 0x2956, quirk_pex_vca_alias);
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_INTEL, 0x2958, quirk_pex_vca_alias);
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_INTEL, 0x2959, quirk_pex_vca_alias);
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_INTEL, 0x295A, quirk_pex_vca_alias);

/*
 * The IOMMU and पूर्णांकerrupt controller on Broadcom Vulcan/Cavium ThunderX2 are
 * associated not at the root bus, but at a bridge below. This quirk aव्योमs
 * generating invalid DMA aliases.
 */
अटल व्योम quirk_bridge_cavm_thrx2_pcie_root(काष्ठा pci_dev *pdev)
अणु
	pdev->dev_flags |= PCI_DEV_FLAGS_BRIDGE_XLATE_ROOT;
पूर्ण
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_BROADCOM, 0x9000,
				quirk_bridge_cavm_thrx2_pcie_root);
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_BROADCOM, 0x9084,
				quirk_bridge_cavm_thrx2_pcie_root);

/*
 * Intersil/Techwell TW686[4589]-based video capture cards have an empty (zero)
 * class code.  Fix it.
 */
अटल व्योम quirk_tw686x_class(काष्ठा pci_dev *pdev)
अणु
	u32 class = pdev->class;

	/* Use "Multimedia controller" class */
	pdev->class = (PCI_CLASS_MULTIMEDIA_OTHER << 8) | 0x01;
	pci_info(pdev, "TW686x PCI class overridden (%#08x -> %#08x)\n",
		 class, pdev->class);
पूर्ण
DECLARE_PCI_FIXUP_CLASS_EARLY(0x1797, 0x6864, PCI_CLASS_NOT_DEFINED, 8,
			      quirk_tw686x_class);
DECLARE_PCI_FIXUP_CLASS_EARLY(0x1797, 0x6865, PCI_CLASS_NOT_DEFINED, 8,
			      quirk_tw686x_class);
DECLARE_PCI_FIXUP_CLASS_EARLY(0x1797, 0x6868, PCI_CLASS_NOT_DEFINED, 8,
			      quirk_tw686x_class);
DECLARE_PCI_FIXUP_CLASS_EARLY(0x1797, 0x6869, PCI_CLASS_NOT_DEFINED, 8,
			      quirk_tw686x_class);

/*
 * Some devices have problems with Transaction Layer Packets with the Relaxed
 * Ordering Attribute set.  Such devices should mark themselves and other
 * device drivers should check beक्रमe sending TLPs with RO set.
 */
अटल व्योम quirk_relaxeकरोrdering_disable(काष्ठा pci_dev *dev)
अणु
	dev->dev_flags |= PCI_DEV_FLAGS_NO_RELAXED_ORDERING;
	pci_info(dev, "Disable Relaxed Ordering Attributes to avoid PCIe Completion erratum\n");
पूर्ण

/*
 * Intel Xeon processors based on Broadwell/Haswell microarchitecture Root
 * Complex have a Flow Control Credit issue which can cause perक्रमmance
 * problems with Upstream Transaction Layer Packets with Relaxed Ordering set.
 */
DECLARE_PCI_FIXUP_CLASS_EARLY(PCI_VENDOR_ID_INTEL, 0x6f01, PCI_CLASS_NOT_DEFINED, 8,
			      quirk_relaxeकरोrdering_disable);
DECLARE_PCI_FIXUP_CLASS_EARLY(PCI_VENDOR_ID_INTEL, 0x6f02, PCI_CLASS_NOT_DEFINED, 8,
			      quirk_relaxeकरोrdering_disable);
DECLARE_PCI_FIXUP_CLASS_EARLY(PCI_VENDOR_ID_INTEL, 0x6f03, PCI_CLASS_NOT_DEFINED, 8,
			      quirk_relaxeकरोrdering_disable);
DECLARE_PCI_FIXUP_CLASS_EARLY(PCI_VENDOR_ID_INTEL, 0x6f04, PCI_CLASS_NOT_DEFINED, 8,
			      quirk_relaxeकरोrdering_disable);
DECLARE_PCI_FIXUP_CLASS_EARLY(PCI_VENDOR_ID_INTEL, 0x6f05, PCI_CLASS_NOT_DEFINED, 8,
			      quirk_relaxeकरोrdering_disable);
DECLARE_PCI_FIXUP_CLASS_EARLY(PCI_VENDOR_ID_INTEL, 0x6f06, PCI_CLASS_NOT_DEFINED, 8,
			      quirk_relaxeकरोrdering_disable);
DECLARE_PCI_FIXUP_CLASS_EARLY(PCI_VENDOR_ID_INTEL, 0x6f07, PCI_CLASS_NOT_DEFINED, 8,
			      quirk_relaxeकरोrdering_disable);
DECLARE_PCI_FIXUP_CLASS_EARLY(PCI_VENDOR_ID_INTEL, 0x6f08, PCI_CLASS_NOT_DEFINED, 8,
			      quirk_relaxeकरोrdering_disable);
DECLARE_PCI_FIXUP_CLASS_EARLY(PCI_VENDOR_ID_INTEL, 0x6f09, PCI_CLASS_NOT_DEFINED, 8,
			      quirk_relaxeकरोrdering_disable);
DECLARE_PCI_FIXUP_CLASS_EARLY(PCI_VENDOR_ID_INTEL, 0x6f0a, PCI_CLASS_NOT_DEFINED, 8,
			      quirk_relaxeकरोrdering_disable);
DECLARE_PCI_FIXUP_CLASS_EARLY(PCI_VENDOR_ID_INTEL, 0x6f0b, PCI_CLASS_NOT_DEFINED, 8,
			      quirk_relaxeकरोrdering_disable);
DECLARE_PCI_FIXUP_CLASS_EARLY(PCI_VENDOR_ID_INTEL, 0x6f0c, PCI_CLASS_NOT_DEFINED, 8,
			      quirk_relaxeकरोrdering_disable);
DECLARE_PCI_FIXUP_CLASS_EARLY(PCI_VENDOR_ID_INTEL, 0x6f0d, PCI_CLASS_NOT_DEFINED, 8,
			      quirk_relaxeकरोrdering_disable);
DECLARE_PCI_FIXUP_CLASS_EARLY(PCI_VENDOR_ID_INTEL, 0x6f0e, PCI_CLASS_NOT_DEFINED, 8,
			      quirk_relaxeकरोrdering_disable);
DECLARE_PCI_FIXUP_CLASS_EARLY(PCI_VENDOR_ID_INTEL, 0x2f01, PCI_CLASS_NOT_DEFINED, 8,
			      quirk_relaxeकरोrdering_disable);
DECLARE_PCI_FIXUP_CLASS_EARLY(PCI_VENDOR_ID_INTEL, 0x2f02, PCI_CLASS_NOT_DEFINED, 8,
			      quirk_relaxeकरोrdering_disable);
DECLARE_PCI_FIXUP_CLASS_EARLY(PCI_VENDOR_ID_INTEL, 0x2f03, PCI_CLASS_NOT_DEFINED, 8,
			      quirk_relaxeकरोrdering_disable);
DECLARE_PCI_FIXUP_CLASS_EARLY(PCI_VENDOR_ID_INTEL, 0x2f04, PCI_CLASS_NOT_DEFINED, 8,
			      quirk_relaxeकरोrdering_disable);
DECLARE_PCI_FIXUP_CLASS_EARLY(PCI_VENDOR_ID_INTEL, 0x2f05, PCI_CLASS_NOT_DEFINED, 8,
			      quirk_relaxeकरोrdering_disable);
DECLARE_PCI_FIXUP_CLASS_EARLY(PCI_VENDOR_ID_INTEL, 0x2f06, PCI_CLASS_NOT_DEFINED, 8,
			      quirk_relaxeकरोrdering_disable);
DECLARE_PCI_FIXUP_CLASS_EARLY(PCI_VENDOR_ID_INTEL, 0x2f07, PCI_CLASS_NOT_DEFINED, 8,
			      quirk_relaxeकरोrdering_disable);
DECLARE_PCI_FIXUP_CLASS_EARLY(PCI_VENDOR_ID_INTEL, 0x2f08, PCI_CLASS_NOT_DEFINED, 8,
			      quirk_relaxeकरोrdering_disable);
DECLARE_PCI_FIXUP_CLASS_EARLY(PCI_VENDOR_ID_INTEL, 0x2f09, PCI_CLASS_NOT_DEFINED, 8,
			      quirk_relaxeकरोrdering_disable);
DECLARE_PCI_FIXUP_CLASS_EARLY(PCI_VENDOR_ID_INTEL, 0x2f0a, PCI_CLASS_NOT_DEFINED, 8,
			      quirk_relaxeकरोrdering_disable);
DECLARE_PCI_FIXUP_CLASS_EARLY(PCI_VENDOR_ID_INTEL, 0x2f0b, PCI_CLASS_NOT_DEFINED, 8,
			      quirk_relaxeकरोrdering_disable);
DECLARE_PCI_FIXUP_CLASS_EARLY(PCI_VENDOR_ID_INTEL, 0x2f0c, PCI_CLASS_NOT_DEFINED, 8,
			      quirk_relaxeकरोrdering_disable);
DECLARE_PCI_FIXUP_CLASS_EARLY(PCI_VENDOR_ID_INTEL, 0x2f0d, PCI_CLASS_NOT_DEFINED, 8,
			      quirk_relaxeकरोrdering_disable);
DECLARE_PCI_FIXUP_CLASS_EARLY(PCI_VENDOR_ID_INTEL, 0x2f0e, PCI_CLASS_NOT_DEFINED, 8,
			      quirk_relaxeकरोrdering_disable);

/*
 * The AMD ARM A1100 (aka "SEATTLE") SoC has a bug in its PCIe Root Complex
 * where Upstream Transaction Layer Packets with the Relaxed Ordering
 * Attribute clear are allowed to bypass earlier TLPs with Relaxed Ordering
 * set.  This is a violation of the PCIe 3.0 Transaction Ordering Rules
 * outlined in Section 2.4.1 (PCI Express(r) Base Specअगरication Revision 3.0
 * November 10, 2010).  As a result, on this platक्रमm we can't use Relaxed
 * Ordering क्रम Upstream TLPs.
 */
DECLARE_PCI_FIXUP_CLASS_EARLY(PCI_VENDOR_ID_AMD, 0x1a00, PCI_CLASS_NOT_DEFINED, 8,
			      quirk_relaxeकरोrdering_disable);
DECLARE_PCI_FIXUP_CLASS_EARLY(PCI_VENDOR_ID_AMD, 0x1a01, PCI_CLASS_NOT_DEFINED, 8,
			      quirk_relaxeकरोrdering_disable);
DECLARE_PCI_FIXUP_CLASS_EARLY(PCI_VENDOR_ID_AMD, 0x1a02, PCI_CLASS_NOT_DEFINED, 8,
			      quirk_relaxeकरोrdering_disable);

/*
 * Per PCIe r3.0, sec 2.2.9, "Completion headers must supply the same
 * values क्रम the Attribute as were supplied in the header of the
 * corresponding Request, except as explicitly allowed when IDO is used."
 *
 * If a non-compliant device generates a completion with a dअगरferent
 * attribute than the request, the receiver may accept it (which itself
 * seems non-compliant based on sec 2.3.2), or it may handle it as a
 * Malक्रमmed TLP or an Unexpected Completion, which will probably lead to a
 * device access समयout.
 *
 * If the non-compliant device generates completions with zero attributes
 * (instead of copying the attributes from the request), we can work around
 * this by disabling the "Relaxed Ordering" and "No Snoop" attributes in
 * upstream devices so they always generate requests with zero attributes.
 *
 * This affects other devices under the same Root Port, but since these
 * attributes are perक्रमmance hपूर्णांकs, there should be no functional problem.
 *
 * Note that Configuration Space accesses are never supposed to have TLP
 * Attributes, so we're safe रुकोing till after any Configuration Space
 * accesses to करो the Root Port fixup.
 */
अटल व्योम quirk_disable_root_port_attributes(काष्ठा pci_dev *pdev)
अणु
	काष्ठा pci_dev *root_port = pcie_find_root_port(pdev);

	अगर (!root_port) अणु
		pci_warn(pdev, "PCIe Completion erratum may cause device errors\n");
		वापस;
	पूर्ण

	pci_info(root_port, "Disabling No Snoop/Relaxed Ordering Attributes to avoid PCIe Completion erratum in %s\n",
		 dev_name(&pdev->dev));
	pcie_capability_clear_and_set_word(root_port, PCI_EXP_DEVCTL,
					   PCI_EXP_DEVCTL_RELAX_EN |
					   PCI_EXP_DEVCTL_NOSNOOP_EN, 0);
पूर्ण

/*
 * The Chelsio T5 chip fails to copy TLP Attributes from a Request to the
 * Completion it generates.
 */
अटल व्योम quirk_chelsio_T5_disable_root_port_attributes(काष्ठा pci_dev *pdev)
अणु
	/*
	 * This mask/compare operation selects क्रम Physical Function 4 on a
	 * T5.  We only need to fix up the Root Port once क्रम any of the
	 * PFs.  PF[0..3] have PCI Device IDs of 0x50xx, but PF4 is uniquely
	 * 0x54xx so we use that one.
	 */
	अगर ((pdev->device & 0xff00) == 0x5400)
		quirk_disable_root_port_attributes(pdev);
पूर्ण
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_CHELSIO, PCI_ANY_ID,
			 quirk_chelsio_T5_disable_root_port_attributes);

/*
 * pci_acs_ctrl_enabled - compare desired ACS controls with those provided
 *			  by a device
 * @acs_ctrl_req: Biपंचांगask of desired ACS controls
 * @acs_ctrl_ena: Biपंचांगask of ACS controls enabled or provided implicitly by
 *		  the hardware design
 *
 * Return 1 अगर all ACS controls in the @acs_ctrl_req biपंचांगask are included
 * in @acs_ctrl_ena, i.e., the device provides all the access controls the
 * caller desires.  Return 0 otherwise.
 */
अटल पूर्णांक pci_acs_ctrl_enabled(u16 acs_ctrl_req, u16 acs_ctrl_ena)
अणु
	अगर ((acs_ctrl_req & acs_ctrl_ena) == acs_ctrl_req)
		वापस 1;
	वापस 0;
पूर्ण

/*
 * AMD has indicated that the devices below करो not support peer-to-peer
 * in any प्रणाली where they are found in the southbridge with an AMD
 * IOMMU in the प्रणाली.  Multअगरunction devices that करो not support
 * peer-to-peer between functions can claim to support a subset of ACS.
 * Such devices effectively enable request redirect (RR) and completion
 * redirect (CR) since all transactions are redirected to the upstream
 * root complex.
 *
 * https://lore.kernel.org/r/201207111426.q6BEQTbh002928@mail.maya.org/
 * https://lore.kernel.org/r/20120711165854.GM25282@amd.com/
 * https://lore.kernel.org/r/20121005130857.GX4009@amd.com/
 *
 * 1002:4385 SBx00 SMBus Controller
 * 1002:439c SB7x0/SB8x0/SB9x0 IDE Controller
 * 1002:4383 SBx00 Azalia (Intel HDA)
 * 1002:439d SB7x0/SB8x0/SB9x0 LPC host controller
 * 1002:4384 SBx00 PCI to PCI Bridge
 * 1002:4399 SB7x0/SB8x0/SB9x0 USB OHCI2 Controller
 *
 * https://bugzilla.kernel.org/show_bug.cgi?id=81841#c15
 *
 * 1022:780f [AMD] FCH PCI Bridge
 * 1022:7809 [AMD] FCH USB OHCI Controller
 */
अटल पूर्णांक pci_quirk_amd_sb_acs(काष्ठा pci_dev *dev, u16 acs_flags)
अणु
#अगर_घोषित CONFIG_ACPI
	काष्ठा acpi_table_header *header = शून्य;
	acpi_status status;

	/* Targeting multअगरunction devices on the SB (appears on root bus) */
	अगर (!dev->multअगरunction || !pci_is_root_bus(dev->bus))
		वापस -ENODEV;

	/* The IVRS table describes the AMD IOMMU */
	status = acpi_get_table("IVRS", 0, &header);
	अगर (ACPI_FAILURE(status))
		वापस -ENODEV;

	acpi_put_table(header);

	/* Filter out flags not applicable to multअगरunction */
	acs_flags &= (PCI_ACS_RR | PCI_ACS_CR | PCI_ACS_EC | PCI_ACS_DT);

	वापस pci_acs_ctrl_enabled(acs_flags, PCI_ACS_RR | PCI_ACS_CR);
#अन्यथा
	वापस -ENODEV;
#पूर्ण_अगर
पूर्ण

अटल bool pci_quirk_cavium_acs_match(काष्ठा pci_dev *dev)
अणु
	अगर (!pci_is_pcie(dev) || pci_pcie_type(dev) != PCI_EXP_TYPE_ROOT_PORT)
		वापस false;

	चयन (dev->device) अणु
	/*
	 * Effectively selects all करोwnstream ports क्रम whole ThunderX1
	 * (which represents 8 SoCs).
	 */
	हाल 0xa000 ... 0xa7ff: /* ThunderX1 */
	हाल 0xaf84:  /* ThunderX2 */
	हाल 0xb884:  /* ThunderX3 */
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल पूर्णांक pci_quirk_cavium_acs(काष्ठा pci_dev *dev, u16 acs_flags)
अणु
	अगर (!pci_quirk_cavium_acs_match(dev))
		वापस -ENOTTY;

	/*
	 * Cavium Root Ports करोn't advertise an ACS capability.  However,
	 * the RTL पूर्णांकernally implements similar protection as अगर ACS had
	 * Source Validation, Request Redirection, Completion Redirection,
	 * and Upstream Forwarding features enabled.  Assert that the
	 * hardware implements and enables equivalent ACS functionality क्रम
	 * these flags.
	 */
	वापस pci_acs_ctrl_enabled(acs_flags,
		PCI_ACS_SV | PCI_ACS_RR | PCI_ACS_CR | PCI_ACS_UF);
पूर्ण

अटल पूर्णांक pci_quirk_xgene_acs(काष्ठा pci_dev *dev, u16 acs_flags)
अणु
	/*
	 * X-Gene Root Ports matching this quirk करो not allow peer-to-peer
	 * transactions with others, allowing masking out these bits as अगर they
	 * were unimplemented in the ACS capability.
	 */
	वापस pci_acs_ctrl_enabled(acs_flags,
		PCI_ACS_SV | PCI_ACS_RR | PCI_ACS_CR | PCI_ACS_UF);
पूर्ण

/*
 * Many Zhaoxin Root Ports and Switch Downstream Ports have no ACS capability.
 * But the implementation could block peer-to-peer transactions between them
 * and provide ACS-like functionality.
 */
अटल पूर्णांक  pci_quirk_zhaoxin_pcie_ports_acs(काष्ठा pci_dev *dev, u16 acs_flags)
अणु
	अगर (!pci_is_pcie(dev) ||
	    ((pci_pcie_type(dev) != PCI_EXP_TYPE_ROOT_PORT) &&
	     (pci_pcie_type(dev) != PCI_EXP_TYPE_DOWNSTREAM)))
		वापस -ENOTTY;

	चयन (dev->device) अणु
	हाल 0x0710 ... 0x071e:
	हाल 0x0721:
	हाल 0x0723 ... 0x0732:
		वापस pci_acs_ctrl_enabled(acs_flags,
			PCI_ACS_SV | PCI_ACS_RR | PCI_ACS_CR | PCI_ACS_UF);
	पूर्ण

	वापस false;
पूर्ण

/*
 * Many Intel PCH Root Ports करो provide ACS-like features to disable peer
 * transactions and validate bus numbers in requests, but करो not provide an
 * actual PCIe ACS capability.  This is the list of device IDs known to fall
 * पूर्णांकo that category as provided by Intel in Red Hat bugzilla 1037684.
 */
अटल स्थिर u16 pci_quirk_पूर्णांकel_pch_acs_ids[] = अणु
	/* Ibexpeak PCH */
	0x3b42, 0x3b43, 0x3b44, 0x3b45, 0x3b46, 0x3b47, 0x3b48, 0x3b49,
	0x3b4a, 0x3b4b, 0x3b4c, 0x3b4d, 0x3b4e, 0x3b4f, 0x3b50, 0x3b51,
	/* Cougarpoपूर्णांक PCH */
	0x1c10, 0x1c11, 0x1c12, 0x1c13, 0x1c14, 0x1c15, 0x1c16, 0x1c17,
	0x1c18, 0x1c19, 0x1c1a, 0x1c1b, 0x1c1c, 0x1c1d, 0x1c1e, 0x1c1f,
	/* Pantherpoपूर्णांक PCH */
	0x1e10, 0x1e11, 0x1e12, 0x1e13, 0x1e14, 0x1e15, 0x1e16, 0x1e17,
	0x1e18, 0x1e19, 0x1e1a, 0x1e1b, 0x1e1c, 0x1e1d, 0x1e1e, 0x1e1f,
	/* Lynxpoपूर्णांक-H PCH */
	0x8c10, 0x8c11, 0x8c12, 0x8c13, 0x8c14, 0x8c15, 0x8c16, 0x8c17,
	0x8c18, 0x8c19, 0x8c1a, 0x8c1b, 0x8c1c, 0x8c1d, 0x8c1e, 0x8c1f,
	/* Lynxpoपूर्णांक-LP PCH */
	0x9c10, 0x9c11, 0x9c12, 0x9c13, 0x9c14, 0x9c15, 0x9c16, 0x9c17,
	0x9c18, 0x9c19, 0x9c1a, 0x9c1b,
	/* Wildcat PCH */
	0x9c90, 0x9c91, 0x9c92, 0x9c93, 0x9c94, 0x9c95, 0x9c96, 0x9c97,
	0x9c98, 0x9c99, 0x9c9a, 0x9c9b,
	/* Patsburg (X79) PCH */
	0x1d10, 0x1d12, 0x1d14, 0x1d16, 0x1d18, 0x1d1a, 0x1d1c, 0x1d1e,
	/* Wellsburg (X99) PCH */
	0x8d10, 0x8d11, 0x8d12, 0x8d13, 0x8d14, 0x8d15, 0x8d16, 0x8d17,
	0x8d18, 0x8d19, 0x8d1a, 0x8d1b, 0x8d1c, 0x8d1d, 0x8d1e,
	/* Lynx Poपूर्णांक (9 series) PCH */
	0x8c90, 0x8c92, 0x8c94, 0x8c96, 0x8c98, 0x8c9a, 0x8c9c, 0x8c9e,
पूर्ण;

अटल bool pci_quirk_पूर्णांकel_pch_acs_match(काष्ठा pci_dev *dev)
अणु
	पूर्णांक i;

	/* Filter out a few obvious non-matches first */
	अगर (!pci_is_pcie(dev) || pci_pcie_type(dev) != PCI_EXP_TYPE_ROOT_PORT)
		वापस false;

	क्रम (i = 0; i < ARRAY_SIZE(pci_quirk_पूर्णांकel_pch_acs_ids); i++)
		अगर (pci_quirk_पूर्णांकel_pch_acs_ids[i] == dev->device)
			वापस true;

	वापस false;
पूर्ण

अटल पूर्णांक pci_quirk_पूर्णांकel_pch_acs(काष्ठा pci_dev *dev, u16 acs_flags)
अणु
	अगर (!pci_quirk_पूर्णांकel_pch_acs_match(dev))
		वापस -ENOTTY;

	अगर (dev->dev_flags & PCI_DEV_FLAGS_ACS_ENABLED_QUIRK)
		वापस pci_acs_ctrl_enabled(acs_flags,
			PCI_ACS_SV | PCI_ACS_RR | PCI_ACS_CR | PCI_ACS_UF);

	वापस pci_acs_ctrl_enabled(acs_flags, 0);
पूर्ण

/*
 * These QCOM Root Ports करो provide ACS-like features to disable peer
 * transactions and validate bus numbers in requests, but करो not provide an
 * actual PCIe ACS capability.  Hardware supports source validation but it
 * will report the issue as Completer Abort instead of ACS Violation.
 * Hardware करोesn't support peer-to-peer and each Root Port is a Root
 * Complex with unique segment numbers.  It is not possible क्रम one Root
 * Port to pass traffic to another Root Port.  All PCIe transactions are
 * terminated inside the Root Port.
 */
अटल पूर्णांक pci_quirk_qcom_rp_acs(काष्ठा pci_dev *dev, u16 acs_flags)
अणु
	वापस pci_acs_ctrl_enabled(acs_flags,
		PCI_ACS_SV | PCI_ACS_RR | PCI_ACS_CR | PCI_ACS_UF);
पूर्ण

अटल पूर्णांक pci_quirk_al_acs(काष्ठा pci_dev *dev, u16 acs_flags)
अणु
	अगर (pci_pcie_type(dev) != PCI_EXP_TYPE_ROOT_PORT)
		वापस -ENOTTY;

	/*
	 * Amazon's Annapurna Labs root ports don't include an ACS capability,
	 * but करो include ACS-like functionality. The hardware करोesn't support
	 * peer-to-peer transactions via the root port and each has a unique
	 * segment number.
	 *
	 * Additionally, the root ports cannot send traffic to each other.
	 */
	acs_flags &= ~(PCI_ACS_SV | PCI_ACS_RR | PCI_ACS_CR | PCI_ACS_UF);

	वापस acs_flags ? 0 : 1;
पूर्ण

/*
 * Sunrise Poपूर्णांक PCH root ports implement ACS, but unक्रमtunately as shown in
 * the datasheet (Intel 100 Series Chipset Family PCH Datasheet, Vol. 2,
 * 12.1.46, 12.1.47)[1] this chipset uses dwords क्रम the ACS capability and
 * control रेजिस्टरs whereas the PCIe spec packs them पूर्णांकo words (Rev 3.0,
 * 7.16 ACS Extended Capability).  The bit definitions are correct, but the
 * control रेजिस्टर is at offset 8 instead of 6 and we should probably use
 * dword accesses to them.  This applies to the following PCI Device IDs, as
 * found in volume 1 of the datasheet[2]:
 *
 * 0xa110-0xa11f Sunrise Poपूर्णांक-H PCI Express Root Port #अणु0-16पूर्ण
 * 0xa167-0xa16a Sunrise Poपूर्णांक-H PCI Express Root Port #अणु17-20पूर्ण
 *
 * N.B. This करोesn't fix what lspci shows.
 *
 * The 100 series chipset specअगरication update includes this as errata #23[3].
 *
 * The 200 series chipset (Union Poपूर्णांक) has the same bug according to the
 * specअगरication update (Intel 200 Series Chipset Family Platक्रमm Controller
 * Hub, Specअगरication Update, January 2017, Revision 001, Document# 335194-001,
 * Errata 22)[4].  Per the datasheet[5], root port PCI Device IDs क्रम this
 * chipset include:
 *
 * 0xa290-0xa29f PCI Express Root port #अणु0-16पूर्ण
 * 0xa2e7-0xa2ee PCI Express Root port #अणु17-24पूर्ण
 *
 * Mobile chipsets are also affected, 7th & 8th Generation
 * Specअगरication update confirms ACS errata 22, status no fix: (7th Generation
 * Intel Processor Family I/O क्रम U/Y Platक्रमms and 8th Generation Intel
 * Processor Family I/O क्रम U Quad Core Platक्रमms Specअगरication Update,
 * August 2017, Revision 002, Document#: 334660-002)[6]
 * Device IDs from I/O datasheet: (7th Generation Intel Processor Family I/O
 * क्रम U/Y Platक्रमms and 8th Generation Intel तऍ Processor Family I/O क्रम U
 * Quad Core Platक्रमms, Vol 1 of 2, August 2017, Document#: 334658-003)[7]
 *
 * 0x9d10-0x9d1b PCI Express Root port #अणु1-12पूर्ण
 *
 * [1] https://www.पूर्णांकel.com/content/www/us/en/chipsets/100-series-chipset-datasheet-vol-2.hपंचांगl
 * [2] https://www.पूर्णांकel.com/content/www/us/en/chipsets/100-series-chipset-datasheet-vol-1.hपंचांगl
 * [3] https://www.पूर्णांकel.com/content/www/us/en/chipsets/100-series-chipset-spec-update.hपंचांगl
 * [4] https://www.पूर्णांकel.com/content/www/us/en/chipsets/200-series-chipset-pch-spec-update.hपंचांगl
 * [5] https://www.पूर्णांकel.com/content/www/us/en/chipsets/200-series-chipset-pch-datasheet-vol-1.hपंचांगl
 * [6] https://www.पूर्णांकel.com/content/www/us/en/processors/core/7th-gen-core-family-mobile-u-y-processor-lines-i-o-spec-update.hपंचांगl
 * [7] https://www.पूर्णांकel.com/content/www/us/en/processors/core/7th-gen-core-family-mobile-u-y-processor-lines-i-o-datasheet-vol-1.hपंचांगl
 */
अटल bool pci_quirk_पूर्णांकel_spt_pch_acs_match(काष्ठा pci_dev *dev)
अणु
	अगर (!pci_is_pcie(dev) || pci_pcie_type(dev) != PCI_EXP_TYPE_ROOT_PORT)
		वापस false;

	चयन (dev->device) अणु
	हाल 0xa110 ... 0xa11f: हाल 0xa167 ... 0xa16a: /* Sunrise Poपूर्णांक */
	हाल 0xa290 ... 0xa29f: हाल 0xa2e7 ... 0xa2ee: /* Union Poपूर्णांक */
	हाल 0x9d10 ... 0x9d1b: /* 7th & 8th Gen Mobile */
		वापस true;
	पूर्ण

	वापस false;
पूर्ण

#घोषणा INTEL_SPT_ACS_CTRL (PCI_ACS_CAP + 4)

अटल पूर्णांक pci_quirk_पूर्णांकel_spt_pch_acs(काष्ठा pci_dev *dev, u16 acs_flags)
अणु
	पूर्णांक pos;
	u32 cap, ctrl;

	अगर (!pci_quirk_पूर्णांकel_spt_pch_acs_match(dev))
		वापस -ENOTTY;

	pos = dev->acs_cap;
	अगर (!pos)
		वापस -ENOTTY;

	/* see pci_acs_flags_enabled() */
	pci_पढ़ो_config_dword(dev, pos + PCI_ACS_CAP, &cap);
	acs_flags &= (cap | PCI_ACS_EC);

	pci_पढ़ो_config_dword(dev, pos + INTEL_SPT_ACS_CTRL, &ctrl);

	वापस pci_acs_ctrl_enabled(acs_flags, ctrl);
पूर्ण

अटल पूर्णांक pci_quirk_mf_endpoपूर्णांक_acs(काष्ठा pci_dev *dev, u16 acs_flags)
अणु
	/*
	 * SV, TB, and UF are not relevant to multअगरunction endpoपूर्णांकs.
	 *
	 * Multअगरunction devices are only required to implement RR, CR, and DT
	 * in their ACS capability अगर they support peer-to-peer transactions.
	 * Devices matching this quirk have been verअगरied by the venकरोr to not
	 * perक्रमm peer-to-peer with other functions, allowing us to mask out
	 * these bits as अगर they were unimplemented in the ACS capability.
	 */
	वापस pci_acs_ctrl_enabled(acs_flags,
		PCI_ACS_SV | PCI_ACS_TB | PCI_ACS_RR |
		PCI_ACS_CR | PCI_ACS_UF | PCI_ACS_DT);
पूर्ण

अटल पूर्णांक pci_quirk_rciep_acs(काष्ठा pci_dev *dev, u16 acs_flags)
अणु
	/*
	 * Intel RCiEP's are required to allow p2p only on translated
	 * addresses.  Refer to Intel VT-d specअगरication, r3.1, sec 3.16,
	 * "Root-Complex Peer to Peer Considerations".
	 */
	अगर (pci_pcie_type(dev) != PCI_EXP_TYPE_RC_END)
		वापस -ENOTTY;

	वापस pci_acs_ctrl_enabled(acs_flags,
		PCI_ACS_SV | PCI_ACS_RR | PCI_ACS_CR | PCI_ACS_UF);
पूर्ण

अटल पूर्णांक pci_quirk_brcm_acs(काष्ठा pci_dev *dev, u16 acs_flags)
अणु
	/*
	 * iProc PAXB Root Ports करोn't advertise an ACS capability, but
	 * they करो not allow peer-to-peer transactions between Root Ports.
	 * Allow each Root Port to be in a separate IOMMU group by masking
	 * SV/RR/CR/UF bits.
	 */
	वापस pci_acs_ctrl_enabled(acs_flags,
		PCI_ACS_SV | PCI_ACS_RR | PCI_ACS_CR | PCI_ACS_UF);
पूर्ण

अटल स्थिर काष्ठा pci_dev_acs_enabled अणु
	u16 venकरोr;
	u16 device;
	पूर्णांक (*acs_enabled)(काष्ठा pci_dev *dev, u16 acs_flags);
पूर्ण pci_dev_acs_enabled[] = अणु
	अणु PCI_VENDOR_ID_ATI, 0x4385, pci_quirk_amd_sb_acs पूर्ण,
	अणु PCI_VENDOR_ID_ATI, 0x439c, pci_quirk_amd_sb_acs पूर्ण,
	अणु PCI_VENDOR_ID_ATI, 0x4383, pci_quirk_amd_sb_acs पूर्ण,
	अणु PCI_VENDOR_ID_ATI, 0x439d, pci_quirk_amd_sb_acs पूर्ण,
	अणु PCI_VENDOR_ID_ATI, 0x4384, pci_quirk_amd_sb_acs पूर्ण,
	अणु PCI_VENDOR_ID_ATI, 0x4399, pci_quirk_amd_sb_acs पूर्ण,
	अणु PCI_VENDOR_ID_AMD, 0x780f, pci_quirk_amd_sb_acs पूर्ण,
	अणु PCI_VENDOR_ID_AMD, 0x7809, pci_quirk_amd_sb_acs पूर्ण,
	अणु PCI_VENDOR_ID_SOLARFLARE, 0x0903, pci_quirk_mf_endpoपूर्णांक_acs पूर्ण,
	अणु PCI_VENDOR_ID_SOLARFLARE, 0x0923, pci_quirk_mf_endpoपूर्णांक_acs पूर्ण,
	अणु PCI_VENDOR_ID_SOLARFLARE, 0x0A03, pci_quirk_mf_endpoपूर्णांक_acs पूर्ण,
	अणु PCI_VENDOR_ID_INTEL, 0x10C6, pci_quirk_mf_endpoपूर्णांक_acs पूर्ण,
	अणु PCI_VENDOR_ID_INTEL, 0x10DB, pci_quirk_mf_endpoपूर्णांक_acs पूर्ण,
	अणु PCI_VENDOR_ID_INTEL, 0x10DD, pci_quirk_mf_endpoपूर्णांक_acs पूर्ण,
	अणु PCI_VENDOR_ID_INTEL, 0x10E1, pci_quirk_mf_endpoपूर्णांक_acs पूर्ण,
	अणु PCI_VENDOR_ID_INTEL, 0x10F1, pci_quirk_mf_endpoपूर्णांक_acs पूर्ण,
	अणु PCI_VENDOR_ID_INTEL, 0x10F7, pci_quirk_mf_endpoपूर्णांक_acs पूर्ण,
	अणु PCI_VENDOR_ID_INTEL, 0x10F8, pci_quirk_mf_endpoपूर्णांक_acs पूर्ण,
	अणु PCI_VENDOR_ID_INTEL, 0x10F9, pci_quirk_mf_endpoपूर्णांक_acs पूर्ण,
	अणु PCI_VENDOR_ID_INTEL, 0x10FA, pci_quirk_mf_endpoपूर्णांक_acs पूर्ण,
	अणु PCI_VENDOR_ID_INTEL, 0x10FB, pci_quirk_mf_endpoपूर्णांक_acs पूर्ण,
	अणु PCI_VENDOR_ID_INTEL, 0x10FC, pci_quirk_mf_endpoपूर्णांक_acs पूर्ण,
	अणु PCI_VENDOR_ID_INTEL, 0x1507, pci_quirk_mf_endpoपूर्णांक_acs पूर्ण,
	अणु PCI_VENDOR_ID_INTEL, 0x1514, pci_quirk_mf_endpoपूर्णांक_acs पूर्ण,
	अणु PCI_VENDOR_ID_INTEL, 0x151C, pci_quirk_mf_endpoपूर्णांक_acs पूर्ण,
	अणु PCI_VENDOR_ID_INTEL, 0x1529, pci_quirk_mf_endpoपूर्णांक_acs पूर्ण,
	अणु PCI_VENDOR_ID_INTEL, 0x152A, pci_quirk_mf_endpoपूर्णांक_acs पूर्ण,
	अणु PCI_VENDOR_ID_INTEL, 0x154D, pci_quirk_mf_endpoपूर्णांक_acs पूर्ण,
	अणु PCI_VENDOR_ID_INTEL, 0x154F, pci_quirk_mf_endpoपूर्णांक_acs पूर्ण,
	अणु PCI_VENDOR_ID_INTEL, 0x1551, pci_quirk_mf_endpoपूर्णांक_acs पूर्ण,
	अणु PCI_VENDOR_ID_INTEL, 0x1558, pci_quirk_mf_endpoपूर्णांक_acs पूर्ण,
	/* 82580 */
	अणु PCI_VENDOR_ID_INTEL, 0x1509, pci_quirk_mf_endpoपूर्णांक_acs पूर्ण,
	अणु PCI_VENDOR_ID_INTEL, 0x150E, pci_quirk_mf_endpoपूर्णांक_acs पूर्ण,
	अणु PCI_VENDOR_ID_INTEL, 0x150F, pci_quirk_mf_endpoपूर्णांक_acs पूर्ण,
	अणु PCI_VENDOR_ID_INTEL, 0x1510, pci_quirk_mf_endpoपूर्णांक_acs पूर्ण,
	अणु PCI_VENDOR_ID_INTEL, 0x1511, pci_quirk_mf_endpoपूर्णांक_acs पूर्ण,
	अणु PCI_VENDOR_ID_INTEL, 0x1516, pci_quirk_mf_endpoपूर्णांक_acs पूर्ण,
	अणु PCI_VENDOR_ID_INTEL, 0x1527, pci_quirk_mf_endpoपूर्णांक_acs पूर्ण,
	/* 82576 */
	अणु PCI_VENDOR_ID_INTEL, 0x10C9, pci_quirk_mf_endpoपूर्णांक_acs पूर्ण,
	अणु PCI_VENDOR_ID_INTEL, 0x10E6, pci_quirk_mf_endpoपूर्णांक_acs पूर्ण,
	अणु PCI_VENDOR_ID_INTEL, 0x10E7, pci_quirk_mf_endpoपूर्णांक_acs पूर्ण,
	अणु PCI_VENDOR_ID_INTEL, 0x10E8, pci_quirk_mf_endpoपूर्णांक_acs पूर्ण,
	अणु PCI_VENDOR_ID_INTEL, 0x150A, pci_quirk_mf_endpoपूर्णांक_acs पूर्ण,
	अणु PCI_VENDOR_ID_INTEL, 0x150D, pci_quirk_mf_endpoपूर्णांक_acs पूर्ण,
	अणु PCI_VENDOR_ID_INTEL, 0x1518, pci_quirk_mf_endpoपूर्णांक_acs पूर्ण,
	अणु PCI_VENDOR_ID_INTEL, 0x1526, pci_quirk_mf_endpoपूर्णांक_acs पूर्ण,
	/* 82575 */
	अणु PCI_VENDOR_ID_INTEL, 0x10A7, pci_quirk_mf_endpoपूर्णांक_acs पूर्ण,
	अणु PCI_VENDOR_ID_INTEL, 0x10A9, pci_quirk_mf_endpoपूर्णांक_acs पूर्ण,
	अणु PCI_VENDOR_ID_INTEL, 0x10D6, pci_quirk_mf_endpoपूर्णांक_acs पूर्ण,
	/* I350 */
	अणु PCI_VENDOR_ID_INTEL, 0x1521, pci_quirk_mf_endpoपूर्णांक_acs पूर्ण,
	अणु PCI_VENDOR_ID_INTEL, 0x1522, pci_quirk_mf_endpoपूर्णांक_acs पूर्ण,
	अणु PCI_VENDOR_ID_INTEL, 0x1523, pci_quirk_mf_endpoपूर्णांक_acs पूर्ण,
	अणु PCI_VENDOR_ID_INTEL, 0x1524, pci_quirk_mf_endpoपूर्णांक_acs पूर्ण,
	/* 82571 (Quads omitted due to non-ACS चयन) */
	अणु PCI_VENDOR_ID_INTEL, 0x105E, pci_quirk_mf_endpoपूर्णांक_acs पूर्ण,
	अणु PCI_VENDOR_ID_INTEL, 0x105F, pci_quirk_mf_endpoपूर्णांक_acs पूर्ण,
	अणु PCI_VENDOR_ID_INTEL, 0x1060, pci_quirk_mf_endpoपूर्णांक_acs पूर्ण,
	अणु PCI_VENDOR_ID_INTEL, 0x10D9, pci_quirk_mf_endpoपूर्णांक_acs पूर्ण,
	/* I219 */
	अणु PCI_VENDOR_ID_INTEL, 0x15b7, pci_quirk_mf_endpoपूर्णांक_acs पूर्ण,
	अणु PCI_VENDOR_ID_INTEL, 0x15b8, pci_quirk_mf_endpoपूर्णांक_acs पूर्ण,
	अणु PCI_VENDOR_ID_INTEL, PCI_ANY_ID, pci_quirk_rciep_acs पूर्ण,
	/* QCOM QDF2xxx root ports */
	अणु PCI_VENDOR_ID_QCOM, 0x0400, pci_quirk_qcom_rp_acs पूर्ण,
	अणु PCI_VENDOR_ID_QCOM, 0x0401, pci_quirk_qcom_rp_acs पूर्ण,
	/* HXT SD4800 root ports. The ACS design is same as QCOM QDF2xxx */
	अणु PCI_VENDOR_ID_HXT, 0x0401, pci_quirk_qcom_rp_acs पूर्ण,
	/* Intel PCH root ports */
	अणु PCI_VENDOR_ID_INTEL, PCI_ANY_ID, pci_quirk_पूर्णांकel_pch_acs पूर्ण,
	अणु PCI_VENDOR_ID_INTEL, PCI_ANY_ID, pci_quirk_पूर्णांकel_spt_pch_acs पूर्ण,
	अणु 0x19a2, 0x710, pci_quirk_mf_endpoपूर्णांक_acs पूर्ण, /* Emulex BE3-R */
	अणु 0x10df, 0x720, pci_quirk_mf_endpoपूर्णांक_acs पूर्ण, /* Emulex Skyhawk-R */
	/* Cavium ThunderX */
	अणु PCI_VENDOR_ID_CAVIUM, PCI_ANY_ID, pci_quirk_cavium_acs पूर्ण,
	/* APM X-Gene */
	अणु PCI_VENDOR_ID_AMCC, 0xE004, pci_quirk_xgene_acs पूर्ण,
	/* Ampere Computing */
	अणु PCI_VENDOR_ID_AMPERE, 0xE005, pci_quirk_xgene_acs पूर्ण,
	अणु PCI_VENDOR_ID_AMPERE, 0xE006, pci_quirk_xgene_acs पूर्ण,
	अणु PCI_VENDOR_ID_AMPERE, 0xE007, pci_quirk_xgene_acs पूर्ण,
	अणु PCI_VENDOR_ID_AMPERE, 0xE008, pci_quirk_xgene_acs पूर्ण,
	अणु PCI_VENDOR_ID_AMPERE, 0xE009, pci_quirk_xgene_acs पूर्ण,
	अणु PCI_VENDOR_ID_AMPERE, 0xE00A, pci_quirk_xgene_acs पूर्ण,
	अणु PCI_VENDOR_ID_AMPERE, 0xE00B, pci_quirk_xgene_acs पूर्ण,
	अणु PCI_VENDOR_ID_AMPERE, 0xE00C, pci_quirk_xgene_acs पूर्ण,
	/* Broadcom multi-function device */
	अणु PCI_VENDOR_ID_BROADCOM, 0x16D7, pci_quirk_mf_endpoपूर्णांक_acs पूर्ण,
	अणु PCI_VENDOR_ID_BROADCOM, 0xD714, pci_quirk_brcm_acs पूर्ण,
	/* Amazon Annapurna Lअसल */
	अणु PCI_VENDOR_ID_AMAZON_ANNAPURNA_LABS, 0x0031, pci_quirk_al_acs पूर्ण,
	/* Zhaoxin multi-function devices */
	अणु PCI_VENDOR_ID_ZHAOXIN, 0x3038, pci_quirk_mf_endpoपूर्णांक_acs पूर्ण,
	अणु PCI_VENDOR_ID_ZHAOXIN, 0x3104, pci_quirk_mf_endpoपूर्णांक_acs पूर्ण,
	अणु PCI_VENDOR_ID_ZHAOXIN, 0x9083, pci_quirk_mf_endpoपूर्णांक_acs पूर्ण,
	/* Zhaoxin Root/Downstream Ports */
	अणु PCI_VENDOR_ID_ZHAOXIN, PCI_ANY_ID, pci_quirk_zhaoxin_pcie_ports_acs पूर्ण,
	अणु 0 पूर्ण
पूर्ण;

/*
 * pci_dev_specअगरic_acs_enabled - check whether device provides ACS controls
 * @dev:	PCI device
 * @acs_flags:	Biपंचांगask of desired ACS controls
 *
 * Returns:
 *   -ENOTTY:	No quirk applies to this device; we can't tell whether the
 *		device provides the desired controls
 *   0:		Device करोes not provide all the desired controls
 *   >0:	Device provides all the controls in @acs_flags
 */
पूर्णांक pci_dev_specअगरic_acs_enabled(काष्ठा pci_dev *dev, u16 acs_flags)
अणु
	स्थिर काष्ठा pci_dev_acs_enabled *i;
	पूर्णांक ret;

	/*
	 * Allow devices that करो not expose standard PCIe ACS capabilities
	 * or control to indicate their support here.  Multi-function express
	 * devices which करो not allow पूर्णांकernal peer-to-peer between functions,
	 * but करो not implement PCIe ACS may wish to वापस true here.
	 */
	क्रम (i = pci_dev_acs_enabled; i->acs_enabled; i++) अणु
		अगर ((i->venकरोr == dev->venकरोr ||
		     i->venकरोr == (u16)PCI_ANY_ID) &&
		    (i->device == dev->device ||
		     i->device == (u16)PCI_ANY_ID)) अणु
			ret = i->acs_enabled(dev, acs_flags);
			अगर (ret >= 0)
				वापस ret;
		पूर्ण
	पूर्ण

	वापस -ENOTTY;
पूर्ण

/* Config space offset of Root Complex Base Address रेजिस्टर */
#घोषणा INTEL_LPC_RCBA_REG 0xf0
/* 31:14 RCBA address */
#घोषणा INTEL_LPC_RCBA_MASK 0xffffc000
/* RCBA Enable */
#घोषणा INTEL_LPC_RCBA_ENABLE (1 << 0)

/* Backbone Scratch Pad Register */
#घोषणा INTEL_BSPR_REG 0x1104
/* Backbone Peer Non-Posted Disable */
#घोषणा INTEL_BSPR_REG_BPNPD (1 << 8)
/* Backbone Peer Posted Disable */
#घोषणा INTEL_BSPR_REG_BPPD  (1 << 9)

/* Upstream Peer Decode Configuration Register */
#घोषणा INTEL_UPDCR_REG 0x1014
/* 5:0 Peer Decode Enable bits */
#घोषणा INTEL_UPDCR_REG_MASK 0x3f

अटल पूर्णांक pci_quirk_enable_पूर्णांकel_lpc_acs(काष्ठा pci_dev *dev)
अणु
	u32 rcba, bspr, updcr;
	व्योम __iomem *rcba_mem;

	/*
	 * Read the RCBA रेजिस्टर from the LPC (D31:F0).  PCH root ports
	 * are D28:F* and thereक्रमe get probed beक्रमe LPC, thus we can't
	 * use pci_get_slot()/pci_पढ़ो_config_dword() here.
	 */
	pci_bus_पढ़ो_config_dword(dev->bus, PCI_DEVFN(31, 0),
				  INTEL_LPC_RCBA_REG, &rcba);
	अगर (!(rcba & INTEL_LPC_RCBA_ENABLE))
		वापस -EINVAL;

	rcba_mem = ioremap(rcba & INTEL_LPC_RCBA_MASK,
				   PAGE_ALIGN(INTEL_UPDCR_REG));
	अगर (!rcba_mem)
		वापस -ENOMEM;

	/*
	 * The BSPR can disallow peer cycles, but it's set by soft strap and
	 * thereक्रमe पढ़ो-only.  If both posted and non-posted peer cycles are
	 * disallowed, we're ok.  If either are allowed, then we need to use
	 * the UPDCR to disable peer decodes क्रम each port.  This provides the
	 * PCIe ACS equivalent of PCI_ACS_RR | PCI_ACS_CR | PCI_ACS_UF
	 */
	bspr = पढ़ोl(rcba_mem + INTEL_BSPR_REG);
	bspr &= INTEL_BSPR_REG_BPNPD | INTEL_BSPR_REG_BPPD;
	अगर (bspr != (INTEL_BSPR_REG_BPNPD | INTEL_BSPR_REG_BPPD)) अणु
		updcr = पढ़ोl(rcba_mem + INTEL_UPDCR_REG);
		अगर (updcr & INTEL_UPDCR_REG_MASK) अणु
			pci_info(dev, "Disabling UPDCR peer decodes\n");
			updcr &= ~INTEL_UPDCR_REG_MASK;
			ग_लिखोl(updcr, rcba_mem + INTEL_UPDCR_REG);
		पूर्ण
	पूर्ण

	iounmap(rcba_mem);
	वापस 0;
पूर्ण

/* Miscellaneous Port Configuration रेजिस्टर */
#घोषणा INTEL_MPC_REG 0xd8
/* MPC: Invalid Receive Bus Number Check Enable */
#घोषणा INTEL_MPC_REG_IRBNCE (1 << 26)

अटल व्योम pci_quirk_enable_पूर्णांकel_rp_mpc_acs(काष्ठा pci_dev *dev)
अणु
	u32 mpc;

	/*
	 * When enabled, the IRBNCE bit of the MPC रेजिस्टर enables the
	 * equivalent of PCI ACS Source Validation (PCI_ACS_SV), which
	 * ensures that requester IDs fall within the bus number range
	 * of the bridge.  Enable अगर not alपढ़ोy.
	 */
	pci_पढ़ो_config_dword(dev, INTEL_MPC_REG, &mpc);
	अगर (!(mpc & INTEL_MPC_REG_IRBNCE)) अणु
		pci_info(dev, "Enabling MPC IRBNCE\n");
		mpc |= INTEL_MPC_REG_IRBNCE;
		pci_ग_लिखो_config_word(dev, INTEL_MPC_REG, mpc);
	पूर्ण
पूर्ण

/*
 * Currently this quirk करोes the equivalent of
 * PCI_ACS_SV | PCI_ACS_RR | PCI_ACS_CR | PCI_ACS_UF
 *
 * TODO: This quirk also needs to करो equivalent of PCI_ACS_TB,
 * अगर dev->बाह्यal_facing || dev->untrusted
 */
अटल पूर्णांक pci_quirk_enable_पूर्णांकel_pch_acs(काष्ठा pci_dev *dev)
अणु
	अगर (!pci_quirk_पूर्णांकel_pch_acs_match(dev))
		वापस -ENOTTY;

	अगर (pci_quirk_enable_पूर्णांकel_lpc_acs(dev)) अणु
		pci_warn(dev, "Failed to enable Intel PCH ACS quirk\n");
		वापस 0;
	पूर्ण

	pci_quirk_enable_पूर्णांकel_rp_mpc_acs(dev);

	dev->dev_flags |= PCI_DEV_FLAGS_ACS_ENABLED_QUIRK;

	pci_info(dev, "Intel PCH root port ACS workaround enabled\n");

	वापस 0;
पूर्ण

अटल पूर्णांक pci_quirk_enable_पूर्णांकel_spt_pch_acs(काष्ठा pci_dev *dev)
अणु
	पूर्णांक pos;
	u32 cap, ctrl;

	अगर (!pci_quirk_पूर्णांकel_spt_pch_acs_match(dev))
		वापस -ENOTTY;

	pos = dev->acs_cap;
	अगर (!pos)
		वापस -ENOTTY;

	pci_पढ़ो_config_dword(dev, pos + PCI_ACS_CAP, &cap);
	pci_पढ़ो_config_dword(dev, pos + INTEL_SPT_ACS_CTRL, &ctrl);

	ctrl |= (cap & PCI_ACS_SV);
	ctrl |= (cap & PCI_ACS_RR);
	ctrl |= (cap & PCI_ACS_CR);
	ctrl |= (cap & PCI_ACS_UF);

	अगर (dev->बाह्यal_facing || dev->untrusted)
		ctrl |= (cap & PCI_ACS_TB);

	pci_ग_लिखो_config_dword(dev, pos + INTEL_SPT_ACS_CTRL, ctrl);

	pci_info(dev, "Intel SPT PCH root port ACS workaround enabled\n");

	वापस 0;
पूर्ण

अटल पूर्णांक pci_quirk_disable_पूर्णांकel_spt_pch_acs_redir(काष्ठा pci_dev *dev)
अणु
	पूर्णांक pos;
	u32 cap, ctrl;

	अगर (!pci_quirk_पूर्णांकel_spt_pch_acs_match(dev))
		वापस -ENOTTY;

	pos = dev->acs_cap;
	अगर (!pos)
		वापस -ENOTTY;

	pci_पढ़ो_config_dword(dev, pos + PCI_ACS_CAP, &cap);
	pci_पढ़ो_config_dword(dev, pos + INTEL_SPT_ACS_CTRL, &ctrl);

	ctrl &= ~(PCI_ACS_RR | PCI_ACS_CR | PCI_ACS_EC);

	pci_ग_लिखो_config_dword(dev, pos + INTEL_SPT_ACS_CTRL, ctrl);

	pci_info(dev, "Intel SPT PCH root port workaround: disabled ACS redirect\n");

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा pci_dev_acs_ops अणु
	u16 venकरोr;
	u16 device;
	पूर्णांक (*enable_acs)(काष्ठा pci_dev *dev);
	पूर्णांक (*disable_acs_redir)(काष्ठा pci_dev *dev);
पूर्ण pci_dev_acs_ops[] = अणु
	अणु PCI_VENDOR_ID_INTEL, PCI_ANY_ID,
	    .enable_acs = pci_quirk_enable_पूर्णांकel_pch_acs,
	पूर्ण,
	अणु PCI_VENDOR_ID_INTEL, PCI_ANY_ID,
	    .enable_acs = pci_quirk_enable_पूर्णांकel_spt_pch_acs,
	    .disable_acs_redir = pci_quirk_disable_पूर्णांकel_spt_pch_acs_redir,
	पूर्ण,
पूर्ण;

पूर्णांक pci_dev_specअगरic_enable_acs(काष्ठा pci_dev *dev)
अणु
	स्थिर काष्ठा pci_dev_acs_ops *p;
	पूर्णांक i, ret;

	क्रम (i = 0; i < ARRAY_SIZE(pci_dev_acs_ops); i++) अणु
		p = &pci_dev_acs_ops[i];
		अगर ((p->venकरोr == dev->venकरोr ||
		     p->venकरोr == (u16)PCI_ANY_ID) &&
		    (p->device == dev->device ||
		     p->device == (u16)PCI_ANY_ID) &&
		    p->enable_acs) अणु
			ret = p->enable_acs(dev);
			अगर (ret >= 0)
				वापस ret;
		पूर्ण
	पूर्ण

	वापस -ENOTTY;
पूर्ण

पूर्णांक pci_dev_specअगरic_disable_acs_redir(काष्ठा pci_dev *dev)
अणु
	स्थिर काष्ठा pci_dev_acs_ops *p;
	पूर्णांक i, ret;

	क्रम (i = 0; i < ARRAY_SIZE(pci_dev_acs_ops); i++) अणु
		p = &pci_dev_acs_ops[i];
		अगर ((p->venकरोr == dev->venकरोr ||
		     p->venकरोr == (u16)PCI_ANY_ID) &&
		    (p->device == dev->device ||
		     p->device == (u16)PCI_ANY_ID) &&
		    p->disable_acs_redir) अणु
			ret = p->disable_acs_redir(dev);
			अगर (ret >= 0)
				वापस ret;
		पूर्ण
	पूर्ण

	वापस -ENOTTY;
पूर्ण

/*
 * The PCI capabilities list क्रम Intel DH895xCC VFs (device ID 0x0443) with
 * QuickAssist Technology (QAT) is prematurely terminated in hardware.  The
 * Next Capability poपूर्णांकer in the MSI Capability Structure should poपूर्णांक to
 * the PCIe Capability Structure but is incorrectly hardwired as 0 terminating
 * the list.
 */
अटल व्योम quirk_पूर्णांकel_qat_vf_cap(काष्ठा pci_dev *pdev)
अणु
	पूर्णांक pos, i = 0;
	u8 next_cap;
	u16 reg16, *cap;
	काष्ठा pci_cap_saved_state *state;

	/* Bail अगर the hardware bug is fixed */
	अगर (pdev->pcie_cap || pci_find_capability(pdev, PCI_CAP_ID_EXP))
		वापस;

	/* Bail अगर MSI Capability Structure is not found क्रम some reason */
	pos = pci_find_capability(pdev, PCI_CAP_ID_MSI);
	अगर (!pos)
		वापस;

	/*
	 * Bail अगर Next Capability poपूर्णांकer in the MSI Capability Structure
	 * is not the expected incorrect 0x00.
	 */
	pci_पढ़ो_config_byte(pdev, pos + 1, &next_cap);
	अगर (next_cap)
		वापस;

	/*
	 * PCIe Capability Structure is expected to be at 0x50 and should
	 * terminate the list (Next Capability poपूर्णांकer is 0x00).  Verअगरy
	 * Capability Id and Next Capability poपूर्णांकer is as expected.
	 * Open-code some of set_pcie_port_type() and pci_cfg_space_size_ext()
	 * to correctly set kernel data काष्ठाures which have alपढ़ोy been
	 * set incorrectly due to the hardware bug.
	 */
	pos = 0x50;
	pci_पढ़ो_config_word(pdev, pos, &reg16);
	अगर (reg16 == (0x0000 | PCI_CAP_ID_EXP)) अणु
		u32 status;
#अगर_अघोषित PCI_EXP_SAVE_REGS
#घोषणा PCI_EXP_SAVE_REGS     7
#पूर्ण_अगर
		पूर्णांक size = PCI_EXP_SAVE_REGS * माप(u16);

		pdev->pcie_cap = pos;
		pci_पढ़ो_config_word(pdev, pos + PCI_EXP_FLAGS, &reg16);
		pdev->pcie_flags_reg = reg16;
		pci_पढ़ो_config_word(pdev, pos + PCI_EXP_DEVCAP, &reg16);
		pdev->pcie_mpss = reg16 & PCI_EXP_DEVCAP_PAYLOAD;

		pdev->cfg_size = PCI_CFG_SPACE_EXP_SIZE;
		अगर (pci_पढ़ो_config_dword(pdev, PCI_CFG_SPACE_SIZE, &status) !=
		    PCIBIOS_SUCCESSFUL || (status == 0xffffffff))
			pdev->cfg_size = PCI_CFG_SPACE_SIZE;

		अगर (pci_find_saved_cap(pdev, PCI_CAP_ID_EXP))
			वापस;

		/* Save PCIe cap */
		state = kzalloc(माप(*state) + size, GFP_KERNEL);
		अगर (!state)
			वापस;

		state->cap.cap_nr = PCI_CAP_ID_EXP;
		state->cap.cap_extended = 0;
		state->cap.size = size;
		cap = (u16 *)&state->cap.data[0];
		pcie_capability_पढ़ो_word(pdev, PCI_EXP_DEVCTL, &cap[i++]);
		pcie_capability_पढ़ो_word(pdev, PCI_EXP_LNKCTL, &cap[i++]);
		pcie_capability_पढ़ो_word(pdev, PCI_EXP_SLTCTL, &cap[i++]);
		pcie_capability_पढ़ो_word(pdev, PCI_EXP_RTCTL,  &cap[i++]);
		pcie_capability_पढ़ो_word(pdev, PCI_EXP_DEVCTL2, &cap[i++]);
		pcie_capability_पढ़ो_word(pdev, PCI_EXP_LNKCTL2, &cap[i++]);
		pcie_capability_पढ़ो_word(pdev, PCI_EXP_SLTCTL2, &cap[i++]);
		hlist_add_head(&state->next, &pdev->saved_cap_space);
	पूर्ण
पूर्ण
DECLARE_PCI_FIXUP_EARLY(PCI_VENDOR_ID_INTEL, 0x443, quirk_पूर्णांकel_qat_vf_cap);

/*
 * FLR may cause the following to devices to hang:
 *
 * AMD Starship/Matisse HD Audio Controller 0x1487
 * AMD Starship USB 3.0 Host Controller 0x148c
 * AMD Matisse USB 3.0 Host Controller 0x149c
 * Intel 82579LM Gigabit Ethernet Controller 0x1502
 * Intel 82579V Gigabit Ethernet Controller 0x1503
 *
 */
अटल व्योम quirk_no_flr(काष्ठा pci_dev *dev)
अणु
	dev->dev_flags |= PCI_DEV_FLAGS_NO_FLR_RESET;
पूर्ण
DECLARE_PCI_FIXUP_EARLY(PCI_VENDOR_ID_AMD, 0x1487, quirk_no_flr);
DECLARE_PCI_FIXUP_EARLY(PCI_VENDOR_ID_AMD, 0x148c, quirk_no_flr);
DECLARE_PCI_FIXUP_EARLY(PCI_VENDOR_ID_AMD, 0x149c, quirk_no_flr);
DECLARE_PCI_FIXUP_EARLY(PCI_VENDOR_ID_INTEL, 0x1502, quirk_no_flr);
DECLARE_PCI_FIXUP_EARLY(PCI_VENDOR_ID_INTEL, 0x1503, quirk_no_flr);

अटल व्योम quirk_no_ext_tags(काष्ठा pci_dev *pdev)
अणु
	काष्ठा pci_host_bridge *bridge = pci_find_host_bridge(pdev->bus);

	अगर (!bridge)
		वापस;

	bridge->no_ext_tags = 1;
	pci_info(pdev, "disabling Extended Tags (this device can't handle them)\n");

	pci_walk_bus(bridge->bus, pci_configure_extended_tags, शून्य);
पूर्ण
DECLARE_PCI_FIXUP_EARLY(PCI_VENDOR_ID_SERVERWORKS, 0x0132, quirk_no_ext_tags);
DECLARE_PCI_FIXUP_EARLY(PCI_VENDOR_ID_SERVERWORKS, 0x0140, quirk_no_ext_tags);
DECLARE_PCI_FIXUP_EARLY(PCI_VENDOR_ID_SERVERWORKS, 0x0141, quirk_no_ext_tags);
DECLARE_PCI_FIXUP_EARLY(PCI_VENDOR_ID_SERVERWORKS, 0x0142, quirk_no_ext_tags);
DECLARE_PCI_FIXUP_EARLY(PCI_VENDOR_ID_SERVERWORKS, 0x0144, quirk_no_ext_tags);
DECLARE_PCI_FIXUP_EARLY(PCI_VENDOR_ID_SERVERWORKS, 0x0420, quirk_no_ext_tags);
DECLARE_PCI_FIXUP_EARLY(PCI_VENDOR_ID_SERVERWORKS, 0x0422, quirk_no_ext_tags);

#अगर_घोषित CONFIG_PCI_ATS
/*
 * Some devices require additional driver setup to enable ATS.  Don't use
 * ATS क्रम those devices as ATS will be enabled beक्रमe the driver has had a
 * chance to load and configure the device.
 */
अटल व्योम quirk_amd_harvest_no_ats(काष्ठा pci_dev *pdev)
अणु
	अगर ((pdev->device == 0x7312 && pdev->revision != 0x00) ||
	    (pdev->device == 0x7340 && pdev->revision != 0xc5) ||
	    (pdev->device == 0x7341 && pdev->revision != 0x00))
		वापस;

	अगर (pdev->device == 0x15d8) अणु
		अगर (pdev->revision == 0xcf &&
		    pdev->subप्रणाली_venकरोr == 0xea50 &&
		    (pdev->subप्रणाली_device == 0xce19 ||
		     pdev->subप्रणाली_device == 0xcc10 ||
		     pdev->subप्रणाली_device == 0xcc08))
			जाओ no_ats;
		अन्यथा
			वापस;
	पूर्ण

no_ats:
	pci_info(pdev, "disabling ATS\n");
	pdev->ats_cap = 0;
पूर्ण

/* AMD Stoney platक्रमm GPU */
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_ATI, 0x98e4, quirk_amd_harvest_no_ats);
/* AMD Iceland dGPU */
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_ATI, 0x6900, quirk_amd_harvest_no_ats);
/* AMD Navi10 dGPU */
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_ATI, 0x7312, quirk_amd_harvest_no_ats);
/* AMD Navi14 dGPU */
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_ATI, 0x7340, quirk_amd_harvest_no_ats);
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_ATI, 0x7341, quirk_amd_harvest_no_ats);
/* AMD Raven platक्रमm iGPU */
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_ATI, 0x15d8, quirk_amd_harvest_no_ats);
#पूर्ण_अगर /* CONFIG_PCI_ATS */

/* Freescale PCIe करोesn't support MSI in RC mode */
अटल व्योम quirk_fsl_no_msi(काष्ठा pci_dev *pdev)
अणु
	अगर (pci_pcie_type(pdev) == PCI_EXP_TYPE_ROOT_PORT)
		pdev->no_msi = 1;
पूर्ण
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_FREESCALE, PCI_ANY_ID, quirk_fsl_no_msi);

/*
 * Although not allowed by the spec, some multi-function devices have
 * dependencies of one function (consumer) on another (supplier).  For the
 * consumer to work in D0, the supplier must also be in D0.  Create a
 * device link from the consumer to the supplier to enक्रमce this
 * dependency.  Runसमय PM is allowed by शेष on the consumer to prevent
 * it from permanently keeping the supplier awake.
 */
अटल व्योम pci_create_device_link(काष्ठा pci_dev *pdev, अचिन्हित पूर्णांक consumer,
				   अचिन्हित पूर्णांक supplier, अचिन्हित पूर्णांक class,
				   अचिन्हित पूर्णांक class_shअगरt)
अणु
	काष्ठा pci_dev *supplier_pdev;

	अगर (PCI_FUNC(pdev->devfn) != consumer)
		वापस;

	supplier_pdev = pci_get_करोमुख्य_bus_and_slot(pci_करोमुख्य_nr(pdev->bus),
				pdev->bus->number,
				PCI_DEVFN(PCI_SLOT(pdev->devfn), supplier));
	अगर (!supplier_pdev || (supplier_pdev->class >> class_shअगरt) != class) अणु
		pci_dev_put(supplier_pdev);
		वापस;
	पूर्ण

	अगर (device_link_add(&pdev->dev, &supplier_pdev->dev,
			    DL_FLAG_STATELESS | DL_FLAG_PM_RUNTIME))
		pci_info(pdev, "D0 power state depends on %s\n",
			 pci_name(supplier_pdev));
	अन्यथा
		pci_err(pdev, "Cannot enforce power dependency on %s\n",
			pci_name(supplier_pdev));

	pm_runसमय_allow(&pdev->dev);
	pci_dev_put(supplier_pdev);
पूर्ण

/*
 * Create device link क्रम GPUs with पूर्णांकegrated HDA controller क्रम streaming
 * audio to attached displays.
 */
अटल व्योम quirk_gpu_hda(काष्ठा pci_dev *hda)
अणु
	pci_create_device_link(hda, 1, 0, PCI_BASE_CLASS_DISPLAY, 16);
पूर्ण
DECLARE_PCI_FIXUP_CLASS_FINAL(PCI_VENDOR_ID_ATI, PCI_ANY_ID,
			      PCI_CLASS_MULTIMEDIA_HD_AUDIO, 8, quirk_gpu_hda);
DECLARE_PCI_FIXUP_CLASS_FINAL(PCI_VENDOR_ID_AMD, PCI_ANY_ID,
			      PCI_CLASS_MULTIMEDIA_HD_AUDIO, 8, quirk_gpu_hda);
DECLARE_PCI_FIXUP_CLASS_FINAL(PCI_VENDOR_ID_NVIDIA, PCI_ANY_ID,
			      PCI_CLASS_MULTIMEDIA_HD_AUDIO, 8, quirk_gpu_hda);

/*
 * Create device link क्रम NVIDIA GPU with पूर्णांकegrated USB xHCI Host
 * controller to VGA.
 */
अटल व्योम quirk_gpu_usb(काष्ठा pci_dev *usb)
अणु
	pci_create_device_link(usb, 2, 0, PCI_BASE_CLASS_DISPLAY, 16);
पूर्ण
DECLARE_PCI_FIXUP_CLASS_FINAL(PCI_VENDOR_ID_NVIDIA, PCI_ANY_ID,
			      PCI_CLASS_SERIAL_USB, 8, quirk_gpu_usb);

/*
 * Create device link क्रम NVIDIA GPU with पूर्णांकegrated Type-C UCSI controller
 * to VGA. Currently there is no class code defined क्रम UCSI device over PCI
 * so using UNKNOWN class क्रम now and it will be updated when UCSI
 * over PCI माला_लो a class code.
 */
#घोषणा PCI_CLASS_SERIAL_UNKNOWN	0x0c80
अटल व्योम quirk_gpu_usb_typec_ucsi(काष्ठा pci_dev *ucsi)
अणु
	pci_create_device_link(ucsi, 3, 0, PCI_BASE_CLASS_DISPLAY, 16);
पूर्ण
DECLARE_PCI_FIXUP_CLASS_FINAL(PCI_VENDOR_ID_NVIDIA, PCI_ANY_ID,
			      PCI_CLASS_SERIAL_UNKNOWN, 8,
			      quirk_gpu_usb_typec_ucsi);

/*
 * Enable the NVIDIA GPU पूर्णांकegrated HDA controller अगर the BIOS left it
 * disabled.  https://devtalk.nvidia.com/शेष/topic/1024022
 */
अटल व्योम quirk_nvidia_hda(काष्ठा pci_dev *gpu)
अणु
	u8 hdr_type;
	u32 val;

	/* There was no पूर्णांकegrated HDA controller beक्रमe MCP89 */
	अगर (gpu->device < PCI_DEVICE_ID_NVIDIA_GEFORCE_320M)
		वापस;

	/* Bit 25 at offset 0x488 enables the HDA controller */
	pci_पढ़ो_config_dword(gpu, 0x488, &val);
	अगर (val & BIT(25))
		वापस;

	pci_info(gpu, "Enabling HDA controller\n");
	pci_ग_लिखो_config_dword(gpu, 0x488, val | BIT(25));

	/* The GPU becomes a multi-function device when the HDA is enabled */
	pci_पढ़ो_config_byte(gpu, PCI_HEADER_TYPE, &hdr_type);
	gpu->multअगरunction = !!(hdr_type & 0x80);
पूर्ण
DECLARE_PCI_FIXUP_CLASS_HEADER(PCI_VENDOR_ID_NVIDIA, PCI_ANY_ID,
			       PCI_BASE_CLASS_DISPLAY, 16, quirk_nvidia_hda);
DECLARE_PCI_FIXUP_CLASS_RESUME_EARLY(PCI_VENDOR_ID_NVIDIA, PCI_ANY_ID,
			       PCI_BASE_CLASS_DISPLAY, 16, quirk_nvidia_hda);

/*
 * Some IDT चयनes incorrectly flag an ACS Source Validation error on
 * completions क्रम config पढ़ो requests even though PCIe r4.0, sec
 * 6.12.1.1, says that completions are never affected by ACS Source
 * Validation.  Here's the text of IDT 89H32H8G3-YC, erratum #36:
 *
 *   Item #36 - Downstream port applies ACS Source Validation to Completions
 *   Section 6.12.1.1 of the PCI Express Base Specअगरication 3.1 states that
 *   completions are never affected by ACS Source Validation.  However,
 *   completions received by a करोwnstream port of the PCIe चयन from a
 *   device that has not yet captured a PCIe bus number are incorrectly
 *   dropped by ACS Source Validation by the चयन करोwnstream port.
 *
 * The workaround suggested by IDT is to issue a config ग_लिखो to the
 * करोwnstream device beक्रमe issuing the first config पढ़ो.  This allows the
 * करोwnstream device to capture its bus and device numbers (see PCIe r4.0,
 * sec 2.2.9), thus aव्योमing the ACS error on the completion.
 *
 * However, we करोn't know when the device is पढ़ोy to accept the config
 * ग_लिखो, so we करो config पढ़ोs until we receive a non-Config Request Retry
 * Status, then करो the config ग_लिखो.
 *
 * To aव्योम hitting the erratum when करोing the config पढ़ोs, we disable ACS
 * SV around this process.
 */
पूर्णांक pci_idt_bus_quirk(काष्ठा pci_bus *bus, पूर्णांक devfn, u32 *l, पूर्णांक समयout)
अणु
	पूर्णांक pos;
	u16 ctrl = 0;
	bool found;
	काष्ठा pci_dev *bridge = bus->self;

	pos = bridge->acs_cap;

	/* Disable ACS SV beक्रमe initial config पढ़ोs */
	अगर (pos) अणु
		pci_पढ़ो_config_word(bridge, pos + PCI_ACS_CTRL, &ctrl);
		अगर (ctrl & PCI_ACS_SV)
			pci_ग_लिखो_config_word(bridge, pos + PCI_ACS_CTRL,
					      ctrl & ~PCI_ACS_SV);
	पूर्ण

	found = pci_bus_generic_पढ़ो_dev_venकरोr_id(bus, devfn, l, समयout);

	/* Write Venकरोr ID (पढ़ो-only) so the endpoपूर्णांक latches its bus/dev */
	अगर (found)
		pci_bus_ग_लिखो_config_word(bus, devfn, PCI_VENDOR_ID, 0);

	/* Re-enable ACS_SV अगर it was previously enabled */
	अगर (ctrl & PCI_ACS_SV)
		pci_ग_लिखो_config_word(bridge, pos + PCI_ACS_CTRL, ctrl);

	वापस found;
पूर्ण

/*
 * Microsemi Switchtec NTB uses devfn proxy IDs to move TLPs between
 * NT endpoपूर्णांकs via the पूर्णांकernal चयन fabric. These IDs replace the
 * originating requestor ID TLPs which access host memory on peer NTB
 * ports. Thereक्रमe, all proxy IDs must be aliased to the NTB device
 * to permit access when the IOMMU is turned on.
 */
अटल व्योम quirk_चयनtec_ntb_dma_alias(काष्ठा pci_dev *pdev)
अणु
	व्योम __iomem *mmio;
	काष्ठा ntb_info_regs __iomem *mmio_ntb;
	काष्ठा ntb_ctrl_regs __iomem *mmio_ctrl;
	u64 partition_map;
	u8 partition;
	पूर्णांक pp;

	अगर (pci_enable_device(pdev)) अणु
		pci_err(pdev, "Cannot enable Switchtec device\n");
		वापस;
	पूर्ण

	mmio = pci_iomap(pdev, 0, 0);
	अगर (mmio == शून्य) अणु
		pci_disable_device(pdev);
		pci_err(pdev, "Cannot iomap Switchtec device\n");
		वापस;
	पूर्ण

	pci_info(pdev, "Setting Switchtec proxy ID aliases\n");

	mmio_ntb = mmio + SWITCHTEC_GAS_NTB_OFFSET;
	mmio_ctrl = (व्योम __iomem *) mmio_ntb + SWITCHTEC_NTB_REG_CTRL_OFFSET;

	partition = ioपढ़ो8(&mmio_ntb->partition_id);

	partition_map = ioपढ़ो32(&mmio_ntb->ep_map);
	partition_map |= ((u64) ioपढ़ो32(&mmio_ntb->ep_map + 4)) << 32;
	partition_map &= ~(1ULL << partition);

	क्रम (pp = 0; pp < (माप(partition_map) * 8); pp++) अणु
		काष्ठा ntb_ctrl_regs __iomem *mmio_peer_ctrl;
		u32 table_sz = 0;
		पूर्णांक te;

		अगर (!(partition_map & (1ULL << pp)))
			जारी;

		pci_dbg(pdev, "Processing partition %d\n", pp);

		mmio_peer_ctrl = &mmio_ctrl[pp];

		table_sz = ioपढ़ो16(&mmio_peer_ctrl->req_id_table_size);
		अगर (!table_sz) अणु
			pci_warn(pdev, "Partition %d table_sz 0\n", pp);
			जारी;
		पूर्ण

		अगर (table_sz > 512) अणु
			pci_warn(pdev,
				 "Invalid Switchtec partition %d table_sz %d\n",
				 pp, table_sz);
			जारी;
		पूर्ण

		क्रम (te = 0; te < table_sz; te++) अणु
			u32 rid_entry;
			u8 devfn;

			rid_entry = ioपढ़ो32(&mmio_peer_ctrl->req_id_table[te]);
			devfn = (rid_entry >> 1) & 0xFF;
			pci_dbg(pdev,
				"Aliasing Partition %d Proxy ID %02x.%d\n",
				pp, PCI_SLOT(devfn), PCI_FUNC(devfn));
			pci_add_dma_alias(pdev, devfn, 1);
		पूर्ण
	पूर्ण

	pci_iounmap(pdev, mmio);
	pci_disable_device(pdev);
पूर्ण
#घोषणा SWITCHTEC_QUIRK(vid) \
	DECLARE_PCI_FIXUP_CLASS_FINAL(PCI_VENDOR_ID_MICROSEMI, vid, \
		PCI_CLASS_BRIDGE_OTHER, 8, quirk_चयनtec_ntb_dma_alias)

SWITCHTEC_QUIRK(0x8531);  /* PFX 24xG3 */
SWITCHTEC_QUIRK(0x8532);  /* PFX 32xG3 */
SWITCHTEC_QUIRK(0x8533);  /* PFX 48xG3 */
SWITCHTEC_QUIRK(0x8534);  /* PFX 64xG3 */
SWITCHTEC_QUIRK(0x8535);  /* PFX 80xG3 */
SWITCHTEC_QUIRK(0x8536);  /* PFX 96xG3 */
SWITCHTEC_QUIRK(0x8541);  /* PSX 24xG3 */
SWITCHTEC_QUIRK(0x8542);  /* PSX 32xG3 */
SWITCHTEC_QUIRK(0x8543);  /* PSX 48xG3 */
SWITCHTEC_QUIRK(0x8544);  /* PSX 64xG3 */
SWITCHTEC_QUIRK(0x8545);  /* PSX 80xG3 */
SWITCHTEC_QUIRK(0x8546);  /* PSX 96xG3 */
SWITCHTEC_QUIRK(0x8551);  /* PAX 24XG3 */
SWITCHTEC_QUIRK(0x8552);  /* PAX 32XG3 */
SWITCHTEC_QUIRK(0x8553);  /* PAX 48XG3 */
SWITCHTEC_QUIRK(0x8554);  /* PAX 64XG3 */
SWITCHTEC_QUIRK(0x8555);  /* PAX 80XG3 */
SWITCHTEC_QUIRK(0x8556);  /* PAX 96XG3 */
SWITCHTEC_QUIRK(0x8561);  /* PFXL 24XG3 */
SWITCHTEC_QUIRK(0x8562);  /* PFXL 32XG3 */
SWITCHTEC_QUIRK(0x8563);  /* PFXL 48XG3 */
SWITCHTEC_QUIRK(0x8564);  /* PFXL 64XG3 */
SWITCHTEC_QUIRK(0x8565);  /* PFXL 80XG3 */
SWITCHTEC_QUIRK(0x8566);  /* PFXL 96XG3 */
SWITCHTEC_QUIRK(0x8571);  /* PFXI 24XG3 */
SWITCHTEC_QUIRK(0x8572);  /* PFXI 32XG3 */
SWITCHTEC_QUIRK(0x8573);  /* PFXI 48XG3 */
SWITCHTEC_QUIRK(0x8574);  /* PFXI 64XG3 */
SWITCHTEC_QUIRK(0x8575);  /* PFXI 80XG3 */
SWITCHTEC_QUIRK(0x8576);  /* PFXI 96XG3 */
SWITCHTEC_QUIRK(0x4000);  /* PFX 100XG4 */
SWITCHTEC_QUIRK(0x4084);  /* PFX 84XG4  */
SWITCHTEC_QUIRK(0x4068);  /* PFX 68XG4  */
SWITCHTEC_QUIRK(0x4052);  /* PFX 52XG4  */
SWITCHTEC_QUIRK(0x4036);  /* PFX 36XG4  */
SWITCHTEC_QUIRK(0x4028);  /* PFX 28XG4  */
SWITCHTEC_QUIRK(0x4100);  /* PSX 100XG4 */
SWITCHTEC_QUIRK(0x4184);  /* PSX 84XG4  */
SWITCHTEC_QUIRK(0x4168);  /* PSX 68XG4  */
SWITCHTEC_QUIRK(0x4152);  /* PSX 52XG4  */
SWITCHTEC_QUIRK(0x4136);  /* PSX 36XG4  */
SWITCHTEC_QUIRK(0x4128);  /* PSX 28XG4  */
SWITCHTEC_QUIRK(0x4200);  /* PAX 100XG4 */
SWITCHTEC_QUIRK(0x4284);  /* PAX 84XG4  */
SWITCHTEC_QUIRK(0x4268);  /* PAX 68XG4  */
SWITCHTEC_QUIRK(0x4252);  /* PAX 52XG4  */
SWITCHTEC_QUIRK(0x4236);  /* PAX 36XG4  */
SWITCHTEC_QUIRK(0x4228);  /* PAX 28XG4  */

/*
 * The PLX NTB uses devfn proxy IDs to move TLPs between NT endpoपूर्णांकs.
 * These IDs are used to क्रमward responses to the originator on the other
 * side of the NTB.  Alias all possible IDs to the NTB to permit access when
 * the IOMMU is turned on.
 */
अटल व्योम quirk_plx_ntb_dma_alias(काष्ठा pci_dev *pdev)
अणु
	pci_info(pdev, "Setting PLX NTB proxy ID aliases\n");
	/* PLX NTB may use all 256 devfns */
	pci_add_dma_alias(pdev, 0, 256);
पूर्ण
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_PLX, 0x87b0, quirk_plx_ntb_dma_alias);
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_PLX, 0x87b1, quirk_plx_ntb_dma_alias);

/*
 * On Lenovo Thinkpad P50 SKUs with a Nvidia Quadro M1000M, the BIOS करोes
 * not always reset the secondary Nvidia GPU between reboots अगर the प्रणाली
 * is configured to use Hybrid Graphics mode.  This results in the GPU
 * being left in whatever state it was in during the *previous* boot, which
 * causes spurious पूर्णांकerrupts from the GPU, which in turn causes us to
 * disable the wrong IRQ and end up अवरोधing the touchpad.  Unsurprisingly,
 * this also completely अवरोधs nouveau.
 *
 * Luckily, it seems a simple reset of the Nvidia GPU brings it back to a
 * clean state and fixes all these issues.
 *
 * When the machine is configured in Dedicated display mode, the issue
 * करोesn't occur.  Fortunately the GPU advertises NoReset+ when in this
 * mode, so we can detect that and aव्योम resetting it.
 */
अटल व्योम quirk_reset_lenovo_thinkpad_p50_nvgpu(काष्ठा pci_dev *pdev)
अणु
	व्योम __iomem *map;
	पूर्णांक ret;

	अगर (pdev->subप्रणाली_venकरोr != PCI_VENDOR_ID_LENOVO ||
	    pdev->subप्रणाली_device != 0x222e ||
	    !pdev->reset_fn)
		वापस;

	अगर (pci_enable_device_mem(pdev))
		वापस;

	/*
	 * Based on nvkm_device_ctor() in
	 * drivers/gpu/drm/nouveau/nvkm/engine/device/base.c
	 */
	map = pci_iomap(pdev, 0, 0x23000);
	अगर (!map) अणु
		pci_err(pdev, "Can't map MMIO space\n");
		जाओ out_disable;
	पूर्ण

	/*
	 * Make sure the GPU looks like it's been POSTed beक्रमe resetting
	 * it.
	 */
	अगर (ioपढ़ो32(map + 0x2240c) & 0x2) अणु
		pci_info(pdev, FW_BUG "GPU left initialized by EFI, resetting\n");
		ret = pci_reset_bus(pdev);
		अगर (ret < 0)
			pci_err(pdev, "Failed to reset GPU: %d\n", ret);
	पूर्ण

	iounmap(map);
out_disable:
	pci_disable_device(pdev);
पूर्ण
DECLARE_PCI_FIXUP_CLASS_FINAL(PCI_VENDOR_ID_NVIDIA, 0x13b1,
			      PCI_CLASS_DISPLAY_VGA, 8,
			      quirk_reset_lenovo_thinkpad_p50_nvgpu);

/*
 * Device [1b21:2142]
 * When in D0, PME# करोesn't get निश्चितed when plugging USB 3.0 device.
 */
अटल व्योम pci_fixup_no_d0_pme(काष्ठा pci_dev *dev)
अणु
	pci_info(dev, "PME# does not work under D0, disabling it\n");
	dev->pme_support &= ~(PCI_PM_CAP_PME_D0 >> PCI_PM_CAP_PME_SHIFT);
पूर्ण
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_ASMEDIA, 0x2142, pci_fixup_no_d0_pme);

/*
 * Device 12d8:0x400e [OHCI] and 12d8:0x400f [EHCI]
 *
 * These devices advertise PME# support in all घातer states but करोn't
 * reliably निश्चित it.
 *
 * These devices also advertise MSI, but करोcumentation (PI7C9X440SL.pdf)
 * says "The MSI Function is not implemented on this device" in chapters
 * 7.3.27, 7.3.29-7.3.31.
 */
अटल व्योम pci_fixup_no_msi_no_pme(काष्ठा pci_dev *dev)
अणु
#अगर_घोषित CONFIG_PCI_MSI
	pci_info(dev, "MSI is not implemented on this device, disabling it\n");
	dev->no_msi = 1;
#पूर्ण_अगर
	pci_info(dev, "PME# is unreliable, disabling it\n");
	dev->pme_support = 0;
पूर्ण
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_PERICOM, 0x400e, pci_fixup_no_msi_no_pme);
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_PERICOM, 0x400f, pci_fixup_no_msi_no_pme);

अटल व्योम apex_pci_fixup_class(काष्ठा pci_dev *pdev)
अणु
	pdev->class = (PCI_CLASS_SYSTEM_OTHER << 8) | pdev->class;
पूर्ण
DECLARE_PCI_FIXUP_CLASS_HEADER(0x1ac1, 0x089a,
			       PCI_CLASS_NOT_DEFINED, 8, apex_pci_fixup_class);
