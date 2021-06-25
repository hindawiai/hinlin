<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Define the pci_ops क्रम the PCIC on Toshiba TX4927, TX4938, etc.
 *
 * Based on linux/arch/mips/pci/ops-tx4938.c,
 *	    linux/arch/mips/pci/fixup-rbtx4938.c,
 *	    linux/arch/mips/txx9/rbtx4938/setup.c,
 *	    and RBTX49xx patch from CELF patch archive.
 *
 * 2003-2005 (c) MontaVista Software, Inc.
 * Copyright (C) 2004 by Ralf Baechle (ralf@linux-mips.org)
 * (C) Copyright TOSHIBA CORPORATION 2000-2001, 2004-2007
 */
#समावेश <linux/kernel.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>
#समावेश <यंत्र/txx9/pci.h>
#समावेश <यंत्र/txx9/tx4927pcic.h>

अटल काष्ठा अणु
	काष्ठा pci_controller *channel;
	काष्ठा tx4927_pcic_reg __iomem *pcicptr;
पूर्ण pcicptrs[2];	/* TX4938 has 2 pcic */

अटल व्योम __init set_tx4927_pcicptr(काष्ठा pci_controller *channel,
				      काष्ठा tx4927_pcic_reg __iomem *pcicptr)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(pcicptrs); i++) अणु
		अगर (pcicptrs[i].channel == channel) अणु
			pcicptrs[i].pcicptr = pcicptr;
			वापस;
		पूर्ण
	पूर्ण
	क्रम (i = 0; i < ARRAY_SIZE(pcicptrs); i++) अणु
		अगर (!pcicptrs[i].channel) अणु
			pcicptrs[i].channel = channel;
			pcicptrs[i].pcicptr = pcicptr;
			वापस;
		पूर्ण
	पूर्ण
	BUG();
पूर्ण

काष्ठा tx4927_pcic_reg __iomem *get_tx4927_pcicptr(
	काष्ठा pci_controller *channel)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(pcicptrs); i++) अणु
		अगर (pcicptrs[i].channel == channel)
			वापस pcicptrs[i].pcicptr;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल पूर्णांक mkaddr(काष्ठा pci_bus *bus, अचिन्हित पूर्णांक devfn, पूर्णांक where,
		  काष्ठा tx4927_pcic_reg __iomem *pcicptr)
अणु
	अगर (bus->parent == शून्य &&
	    devfn >= PCI_DEVFN(TX4927_PCIC_MAX_DEVNU, 0))
		वापस -1;
	__raw_ग_लिखोl(((bus->number & 0xff) << 0x10)
		     | ((devfn & 0xff) << 0x08) | (where & 0xfc)
		     | (bus->parent ? 1 : 0),
		     &pcicptr->g2pcfgadrs);
	/* clear M_ABORT and Disable M_ABORT Int. */
	__raw_ग_लिखोl((__raw_पढ़ोl(&pcicptr->pcistatus) & 0x0000ffff)
		     | (PCI_STATUS_REC_MASTER_ABORT << 16),
		     &pcicptr->pcistatus);
	वापस 0;
पूर्ण

अटल पूर्णांक check_पात(काष्ठा tx4927_pcic_reg __iomem *pcicptr)
अणु
	पूर्णांक code = PCIBIOS_SUCCESSFUL;

	/* रुको ग_लिखो cycle completion beक्रमe checking error status */
	जबतक (__raw_पढ़ोl(&pcicptr->pcicstatus) & TX4927_PCIC_PCICSTATUS_IWB)
		;
	अगर (__raw_पढ़ोl(&pcicptr->pcistatus)
	    & (PCI_STATUS_REC_MASTER_ABORT << 16)) अणु
		__raw_ग_लिखोl((__raw_पढ़ोl(&pcicptr->pcistatus) & 0x0000ffff)
			     | (PCI_STATUS_REC_MASTER_ABORT << 16),
			     &pcicptr->pcistatus);
		/* flush ग_लिखो buffer */
		iob();
		code = PCIBIOS_DEVICE_NOT_FOUND;
	पूर्ण
	वापस code;
पूर्ण

अटल u8 icd_पढ़ोb(पूर्णांक offset, काष्ठा tx4927_pcic_reg __iomem *pcicptr)
अणु
#अगर_घोषित __BIG_ENDIAN
	offset ^= 3;
#पूर्ण_अगर
	वापस __raw_पढ़ोb((व्योम __iomem *)&pcicptr->g2pcfgdata + offset);
पूर्ण
अटल u16 icd_पढ़ोw(पूर्णांक offset, काष्ठा tx4927_pcic_reg __iomem *pcicptr)
अणु
#अगर_घोषित __BIG_ENDIAN
	offset ^= 2;
#पूर्ण_अगर
	वापस __raw_पढ़ोw((व्योम __iomem *)&pcicptr->g2pcfgdata + offset);
पूर्ण
अटल u32 icd_पढ़ोl(काष्ठा tx4927_pcic_reg __iomem *pcicptr)
अणु
	वापस __raw_पढ़ोl(&pcicptr->g2pcfgdata);
पूर्ण
अटल व्योम icd_ग_लिखोb(u8 val, पूर्णांक offset,
		       काष्ठा tx4927_pcic_reg __iomem *pcicptr)
अणु
#अगर_घोषित __BIG_ENDIAN
	offset ^= 3;
#पूर्ण_अगर
	__raw_ग_लिखोb(val, (व्योम __iomem *)&pcicptr->g2pcfgdata + offset);
पूर्ण
अटल व्योम icd_ग_लिखोw(u16 val, पूर्णांक offset,
		       काष्ठा tx4927_pcic_reg __iomem *pcicptr)
अणु
#अगर_घोषित __BIG_ENDIAN
	offset ^= 2;
#पूर्ण_अगर
	__raw_ग_लिखोw(val, (व्योम __iomem *)&pcicptr->g2pcfgdata + offset);
पूर्ण
अटल व्योम icd_ग_लिखोl(u32 val, काष्ठा tx4927_pcic_reg __iomem *pcicptr)
अणु
	__raw_ग_लिखोl(val, &pcicptr->g2pcfgdata);
पूर्ण

अटल काष्ठा tx4927_pcic_reg __iomem *pci_bus_to_pcicptr(काष्ठा pci_bus *bus)
अणु
	काष्ठा pci_controller *channel = bus->sysdata;
	वापस get_tx4927_pcicptr(channel);
पूर्ण

अटल पूर्णांक tx4927_pci_config_पढ़ो(काष्ठा pci_bus *bus, अचिन्हित पूर्णांक devfn,
				  पूर्णांक where, पूर्णांक size, u32 *val)
अणु
	काष्ठा tx4927_pcic_reg __iomem *pcicptr = pci_bus_to_pcicptr(bus);

	अगर (mkaddr(bus, devfn, where, pcicptr)) अणु
		*val = 0xffffffff;
		वापस -1;
	पूर्ण
	चयन (size) अणु
	हाल 1:
		*val = icd_पढ़ोb(where & 3, pcicptr);
		अवरोध;
	हाल 2:
		*val = icd_पढ़ोw(where & 3, pcicptr);
		अवरोध;
	शेष:
		*val = icd_पढ़ोl(pcicptr);
	पूर्ण
	वापस check_पात(pcicptr);
पूर्ण

अटल पूर्णांक tx4927_pci_config_ग_लिखो(काष्ठा pci_bus *bus, अचिन्हित पूर्णांक devfn,
				   पूर्णांक where, पूर्णांक size, u32 val)
अणु
	काष्ठा tx4927_pcic_reg __iomem *pcicptr = pci_bus_to_pcicptr(bus);

	अगर (mkaddr(bus, devfn, where, pcicptr))
		वापस -1;
	चयन (size) अणु
	हाल 1:
		icd_ग_लिखोb(val, where & 3, pcicptr);
		अवरोध;
	हाल 2:
		icd_ग_लिखोw(val, where & 3, pcicptr);
		अवरोध;
	शेष:
		icd_ग_लिखोl(val, pcicptr);
	पूर्ण
	वापस check_पात(pcicptr);
पूर्ण

अटल काष्ठा pci_ops tx4927_pci_ops = अणु
	.पढ़ो = tx4927_pci_config_पढ़ो,
	.ग_लिखो = tx4927_pci_config_ग_लिखो,
पूर्ण;

अटल काष्ठा अणु
	u8 trdyto;
	u8 retryto;
	u16 gbwc;
पूर्ण tx4927_pci_opts = अणु
	.trdyto = 0,
	.retryto = 0,
	.gbwc = 0xfe0,	/* 4064 GBUSCLK क्रम CCFG.GTOT=0b11 */
पूर्ण;

अक्षर *tx4927_pcibios_setup(अक्षर *str)
अणु
	अगर (!म_भेदन(str, "trdyto=", 7)) अणु
		u8 val = 0;
		अगर (kstrtou8(str + 7, 0, &val) == 0)
			tx4927_pci_opts.trdyto = val;
		वापस शून्य;
	पूर्ण
	अगर (!म_भेदन(str, "retryto=", 8)) अणु
		u8 val = 0;
		अगर (kstrtou8(str + 8, 0, &val) == 0)
			tx4927_pci_opts.retryto = val;
		वापस शून्य;
	पूर्ण
	अगर (!म_भेदन(str, "gbwc=", 5)) अणु
		u16 val;
		अगर (kstrtou16(str + 5, 0, &val) == 0)
			tx4927_pci_opts.gbwc = val;
		वापस शून्य;
	पूर्ण
	वापस str;
पूर्ण

व्योम __init tx4927_pcic_setup(काष्ठा tx4927_pcic_reg __iomem *pcicptr,
			      काष्ठा pci_controller *channel, पूर्णांक extarb)
अणु
	पूर्णांक i;
	अचिन्हित दीर्घ flags;

	set_tx4927_pcicptr(channel, pcicptr);

	अगर (!channel->pci_ops)
		prपूर्णांकk(KERN_INFO
		       "PCIC -- DID:%04x VID:%04x RID:%02x Arbiter:%s\n",
		       __raw_पढ़ोl(&pcicptr->pciid) >> 16,
		       __raw_पढ़ोl(&pcicptr->pciid) & 0xffff,
		       __raw_पढ़ोl(&pcicptr->pciccrev) & 0xff,
			extarb ? "External" : "Internal");
	channel->pci_ops = &tx4927_pci_ops;

	local_irq_save(flags);

	/* Disable All Initiator Space */
	__raw_ग_लिखोl(__raw_पढ़ोl(&pcicptr->pciccfg)
		     & ~(TX4927_PCIC_PCICCFG_G2PMEN(0)
			 | TX4927_PCIC_PCICCFG_G2PMEN(1)
			 | TX4927_PCIC_PCICCFG_G2PMEN(2)
			 | TX4927_PCIC_PCICCFG_G2PIOEN),
		     &pcicptr->pciccfg);

	/* GB->PCI mappings */
	__raw_ग_लिखोl((channel->io_resource->end - channel->io_resource->start)
		     >> 4,
		     &pcicptr->g2piomask);
	____raw_ग_लिखोq((channel->io_resource->start +
			channel->io_map_base - IO_BASE) |
#अगर_घोषित __BIG_ENDIAN
		       TX4927_PCIC_G2PIOGBASE_ECHG
#अन्यथा
		       TX4927_PCIC_G2PIOGBASE_BSDIS
#पूर्ण_अगर
		       , &pcicptr->g2piogbase);
	____raw_ग_लिखोq(channel->io_resource->start - channel->io_offset,
		       &pcicptr->g2piopbase);
	क्रम (i = 0; i < 3; i++) अणु
		__raw_ग_लिखोl(0, &pcicptr->g2pmmask[i]);
		____raw_ग_लिखोq(0, &pcicptr->g2pmgbase[i]);
		____raw_ग_लिखोq(0, &pcicptr->g2pmpbase[i]);
	पूर्ण
	अगर (channel->mem_resource->end) अणु
		__raw_ग_लिखोl((channel->mem_resource->end
			      - channel->mem_resource->start) >> 4,
			     &pcicptr->g2pmmask[0]);
		____raw_ग_लिखोq(channel->mem_resource->start |
#अगर_घोषित __BIG_ENDIAN
			       TX4927_PCIC_G2PMnGBASE_ECHG
#अन्यथा
			       TX4927_PCIC_G2PMnGBASE_BSDIS
#पूर्ण_अगर
			       , &pcicptr->g2pmgbase[0]);
		____raw_ग_लिखोq(channel->mem_resource->start -
			       channel->mem_offset,
			       &pcicptr->g2pmpbase[0]);
	पूर्ण
	/* PCI->GB mappings (I/O 256B) */
	__raw_ग_लिखोl(0, &pcicptr->p2giopbase); /* 256B */
	____raw_ग_लिखोq(0, &pcicptr->p2giogbase);
	/* PCI->GB mappings (MEM 512MB (64MB on R1.x)) */
	__raw_ग_लिखोl(0, &pcicptr->p2gm0plbase);
	__raw_ग_लिखोl(0, &pcicptr->p2gm0pubase);
	____raw_ग_लिखोq(TX4927_PCIC_P2GMnGBASE_TMEMEN |
#अगर_घोषित __BIG_ENDIAN
		       TX4927_PCIC_P2GMnGBASE_TECHG
#अन्यथा
		       TX4927_PCIC_P2GMnGBASE_TBSDIS
#पूर्ण_अगर
		       , &pcicptr->p2gmgbase[0]);
	/* PCI->GB mappings (MEM 16MB) */
	__raw_ग_लिखोl(0xffffffff, &pcicptr->p2gm1plbase);
	__raw_ग_लिखोl(0xffffffff, &pcicptr->p2gm1pubase);
	____raw_ग_लिखोq(0, &pcicptr->p2gmgbase[1]);
	/* PCI->GB mappings (MEM 1MB) */
	__raw_ग_लिखोl(0xffffffff, &pcicptr->p2gm2pbase); /* 1MB */
	____raw_ग_लिखोq(0, &pcicptr->p2gmgbase[2]);

	/* Clear all (including IRBER) except क्रम GBWC */
	__raw_ग_लिखोl((tx4927_pci_opts.gbwc << 16)
		     & TX4927_PCIC_PCICCFG_GBWC_MASK,
		     &pcicptr->pciccfg);
	/* Enable Initiator Memory Space */
	अगर (channel->mem_resource->end)
		__raw_ग_लिखोl(__raw_पढ़ोl(&pcicptr->pciccfg)
			     | TX4927_PCIC_PCICCFG_G2PMEN(0),
			     &pcicptr->pciccfg);
	/* Enable Initiator I/O Space */
	अगर (channel->io_resource->end)
		__raw_ग_लिखोl(__raw_पढ़ोl(&pcicptr->pciccfg)
			     | TX4927_PCIC_PCICCFG_G2PIOEN,
			     &pcicptr->pciccfg);
	/* Enable Initiator Config */
	__raw_ग_लिखोl(__raw_पढ़ोl(&pcicptr->pciccfg)
		     | TX4927_PCIC_PCICCFG_ICAEN | TX4927_PCIC_PCICCFG_TCAR,
		     &pcicptr->pciccfg);

	/* Do not use MEMMUL, MEMINF: YMFPCI card causes M_ABORT. */
	__raw_ग_लिखोl(0, &pcicptr->pcicfg1);

	__raw_ग_लिखोl((__raw_पढ़ोl(&pcicptr->g2ptocnt) & ~0xffff)
		     | (tx4927_pci_opts.trdyto & 0xff)
		     | ((tx4927_pci_opts.retryto & 0xff) << 8),
		     &pcicptr->g2ptocnt);

	/* Clear All Local Bus Status */
	__raw_ग_लिखोl(TX4927_PCIC_PCICSTATUS_ALL, &pcicptr->pcicstatus);
	/* Enable All Local Bus Interrupts */
	__raw_ग_लिखोl(TX4927_PCIC_PCICSTATUS_ALL, &pcicptr->pcicmask);
	/* Clear All Initiator Status */
	__raw_ग_लिखोl(TX4927_PCIC_G2PSTATUS_ALL, &pcicptr->g2pstatus);
	/* Enable All Initiator Interrupts */
	__raw_ग_लिखोl(TX4927_PCIC_G2PSTATUS_ALL, &pcicptr->g2pmask);
	/* Clear All PCI Status Error */
	__raw_ग_लिखोl((__raw_पढ़ोl(&pcicptr->pcistatus) & 0x0000ffff)
		     | (TX4927_PCIC_PCISTATUS_ALL << 16),
		     &pcicptr->pcistatus);
	/* Enable All PCI Status Error Interrupts */
	__raw_ग_लिखोl(TX4927_PCIC_PCISTATUS_ALL, &pcicptr->pcimask);

	अगर (!extarb) अणु
		/* Reset Bus Arbiter */
		__raw_ग_लिखोl(TX4927_PCIC_PBACFG_RPBA, &pcicptr->pbacfg);
		__raw_ग_लिखोl(0, &pcicptr->pbabm);
		/* Enable Bus Arbiter */
		__raw_ग_लिखोl(TX4927_PCIC_PBACFG_PBAEN, &pcicptr->pbacfg);
	पूर्ण

	__raw_ग_लिखोl(PCI_COMMAND_MASTER | PCI_COMMAND_MEMORY
		     | PCI_COMMAND_PARITY | PCI_COMMAND_SERR,
		     &pcicptr->pcistatus);
	local_irq_restore(flags);

	prपूर्णांकk(KERN_DEBUG
	       "PCI: COMMAND=%04x,PCIMASK=%04x,"
	       "TRDYTO=%02x,RETRYTO=%02x,GBWC=%03x\n",
	       __raw_पढ़ोl(&pcicptr->pcistatus) & 0xffff,
	       __raw_पढ़ोl(&pcicptr->pcimask) & 0xffff,
	       __raw_पढ़ोl(&pcicptr->g2ptocnt) & 0xff,
	       (__raw_पढ़ोl(&pcicptr->g2ptocnt) & 0xff00) >> 8,
	       (__raw_पढ़ोl(&pcicptr->pciccfg) >> 16) & 0xfff);
पूर्ण

अटल व्योम tx4927_report_pcic_status1(काष्ठा tx4927_pcic_reg __iomem *pcicptr)
अणु
	__u16 pcistatus = (__u16)(__raw_पढ़ोl(&pcicptr->pcistatus) >> 16);
	__u32 g2pstatus = __raw_पढ़ोl(&pcicptr->g2pstatus);
	__u32 pcicstatus = __raw_पढ़ोl(&pcicptr->pcicstatus);
	अटल काष्ठा अणु
		__u32 flag;
		स्थिर अक्षर *str;
	पूर्ण pcistat_tbl[] = अणु
		अणु PCI_STATUS_DETECTED_PARITY,	"DetectedParityError" पूर्ण,
		अणु PCI_STATUS_SIG_SYSTEM_ERROR,	"SignaledSystemError" पूर्ण,
		अणु PCI_STATUS_REC_MASTER_ABORT,	"ReceivedMasterAbort" पूर्ण,
		अणु PCI_STATUS_REC_TARGET_ABORT,	"ReceivedTargetAbort" पूर्ण,
		अणु PCI_STATUS_SIG_TARGET_ABORT,	"SignaledTargetAbort" पूर्ण,
		अणु PCI_STATUS_PARITY,	"MasterParityError" पूर्ण,
	पूर्ण, g2pstat_tbl[] = अणु
		अणु TX4927_PCIC_G2PSTATUS_TTOE,	"TIOE" पूर्ण,
		अणु TX4927_PCIC_G2PSTATUS_RTOE,	"RTOE" पूर्ण,
	पूर्ण, pcicstat_tbl[] = अणु
		अणु TX4927_PCIC_PCICSTATUS_PME,	"PME" पूर्ण,
		अणु TX4927_PCIC_PCICSTATUS_TLB,	"TLB" पूर्ण,
		अणु TX4927_PCIC_PCICSTATUS_NIB,	"NIB" पूर्ण,
		अणु TX4927_PCIC_PCICSTATUS_ZIB,	"ZIB" पूर्ण,
		अणु TX4927_PCIC_PCICSTATUS_PERR,	"PERR" पूर्ण,
		अणु TX4927_PCIC_PCICSTATUS_SERR,	"SERR" पूर्ण,
		अणु TX4927_PCIC_PCICSTATUS_GBE,	"GBE" पूर्ण,
		अणु TX4927_PCIC_PCICSTATUS_IWB,	"IWB" पूर्ण,
	पूर्ण;
	पूर्णांक i, cont;

	prपूर्णांकk(KERN_ERR "");
	अगर (pcistatus & TX4927_PCIC_PCISTATUS_ALL) अणु
		prपूर्णांकk(KERN_CONT "pcistat:%04x(", pcistatus);
		क्रम (i = 0, cont = 0; i < ARRAY_SIZE(pcistat_tbl); i++)
			अगर (pcistatus & pcistat_tbl[i].flag)
				prपूर्णांकk(KERN_CONT "%s%s",
				       cont++ ? " " : "", pcistat_tbl[i].str);
		prपूर्णांकk(KERN_CONT ") ");
	पूर्ण
	अगर (g2pstatus & TX4927_PCIC_G2PSTATUS_ALL) अणु
		prपूर्णांकk(KERN_CONT "g2pstatus:%08x(", g2pstatus);
		क्रम (i = 0, cont = 0; i < ARRAY_SIZE(g2pstat_tbl); i++)
			अगर (g2pstatus & g2pstat_tbl[i].flag)
				prपूर्णांकk(KERN_CONT "%s%s",
				       cont++ ? " " : "", g2pstat_tbl[i].str);
		prपूर्णांकk(KERN_CONT ") ");
	पूर्ण
	अगर (pcicstatus & TX4927_PCIC_PCICSTATUS_ALL) अणु
		prपूर्णांकk(KERN_CONT "pcicstatus:%08x(", pcicstatus);
		क्रम (i = 0, cont = 0; i < ARRAY_SIZE(pcicstat_tbl); i++)
			अगर (pcicstatus & pcicstat_tbl[i].flag)
				prपूर्णांकk(KERN_CONT "%s%s",
				       cont++ ? " " : "", pcicstat_tbl[i].str);
		prपूर्णांकk(KERN_CONT ")");
	पूर्ण
	prपूर्णांकk(KERN_CONT "\n");
पूर्ण

व्योम tx4927_report_pcic_status(व्योम)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(pcicptrs); i++) अणु
		अगर (pcicptrs[i].pcicptr)
			tx4927_report_pcic_status1(pcicptrs[i].pcicptr);
	पूर्ण
पूर्ण

अटल व्योम tx4927_dump_pcic_settings1(काष्ठा tx4927_pcic_reg __iomem *pcicptr)
अणु
	पूर्णांक i;
	__u32 __iomem *preg = (__u32 __iomem *)pcicptr;

	prपूर्णांकk(KERN_INFO "tx4927 pcic (0x%p) settings:", pcicptr);
	क्रम (i = 0; i < माप(काष्ठा tx4927_pcic_reg); i += 4, preg++) अणु
		अगर (i % 32 == 0) अणु
			prपूर्णांकk(KERN_CONT "\n");
			prपूर्णांकk(KERN_INFO "%04x:", i);
		पूर्ण
		/* skip रेजिस्टरs with side-effects */
		अगर (i == दुरत्व(काष्ठा tx4927_pcic_reg, g2pपूर्णांकack)
		    || i == दुरत्व(काष्ठा tx4927_pcic_reg, g2pspc)
		    || i == दुरत्व(काष्ठा tx4927_pcic_reg, g2pcfgadrs)
		    || i == दुरत्व(काष्ठा tx4927_pcic_reg, g2pcfgdata)) अणु
			prपूर्णांकk(KERN_CONT " XXXXXXXX");
			जारी;
		पूर्ण
		prपूर्णांकk(KERN_CONT " %08x", __raw_पढ़ोl(preg));
	पूर्ण
	prपूर्णांकk(KERN_CONT "\n");
पूर्ण

व्योम tx4927_dump_pcic_settings(व्योम)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(pcicptrs); i++) अणु
		अगर (pcicptrs[i].pcicptr)
			tx4927_dump_pcic_settings1(pcicptrs[i].pcicptr);
	पूर्ण
पूर्ण

irqवापस_t tx4927_pcierr_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा pt_regs *regs = get_irq_regs();
	काष्ठा tx4927_pcic_reg __iomem *pcicptr =
		(काष्ठा tx4927_pcic_reg __iomem *)(अचिन्हित दीर्घ)dev_id;

	अगर (txx9_pci_err_action != TXX9_PCI_ERR_IGNORE) अणु
		prपूर्णांकk(KERN_WARNING "PCIERR interrupt at 0x%0*lx\n",
		       (पूर्णांक)(2 * माप(अचिन्हित दीर्घ)), regs->cp0_epc);
		tx4927_report_pcic_status1(pcicptr);
	पूर्ण
	अगर (txx9_pci_err_action != TXX9_PCI_ERR_PANIC) अणु
		/* clear all pci errors */
		__raw_ग_लिखोl((__raw_पढ़ोl(&pcicptr->pcistatus) & 0x0000ffff)
			     | (TX4927_PCIC_PCISTATUS_ALL << 16),
			     &pcicptr->pcistatus);
		__raw_ग_लिखोl(TX4927_PCIC_G2PSTATUS_ALL, &pcicptr->g2pstatus);
		__raw_ग_लिखोl(TX4927_PCIC_PBASTATUS_ALL, &pcicptr->pbastatus);
		__raw_ग_लिखोl(TX4927_PCIC_PCICSTATUS_ALL, &pcicptr->pcicstatus);
		वापस IRQ_HANDLED;
	पूर्ण
	console_verbose();
	tx4927_dump_pcic_settings1(pcicptr);
	panic("PCI error.");
पूर्ण

#अगर_घोषित CONFIG_TOSHIBA_FPCIB0
अटल व्योम tx4927_quirk_slc90e66_bridge(काष्ठा pci_dev *dev)
अणु
	काष्ठा tx4927_pcic_reg __iomem *pcicptr = pci_bus_to_pcicptr(dev->bus);

	अगर (!pcicptr)
		वापस;
	अगर (__raw_पढ़ोl(&pcicptr->pbacfg) & TX4927_PCIC_PBACFG_PBAEN) अणु
		/* Reset Bus Arbiter */
		__raw_ग_लिखोl(TX4927_PCIC_PBACFG_RPBA, &pcicptr->pbacfg);
		/*
		 * swap reqBP and reqXP (उठाओ priority of SLC90E66).
		 * SLC90E66(PCI-ISA bridge) is connected to REQ2 on
		 * PCI Backplane board.
		 */
		__raw_ग_लिखोl(0x72543610, &pcicptr->pbareqport);
		__raw_ग_लिखोl(0, &pcicptr->pbabm);
		/* Use Fixed ParkMaster (required by SLC90E66) */
		__raw_ग_लिखोl(TX4927_PCIC_PBACFG_FIXPA, &pcicptr->pbacfg);
		/* Enable Bus Arbiter */
		__raw_ग_लिखोl(TX4927_PCIC_PBACFG_FIXPA |
			     TX4927_PCIC_PBACFG_PBAEN,
			     &pcicptr->pbacfg);
		prपूर्णांकk(KERN_INFO "PCI: Use Fixed Park Master (REQPORT %08x)\n",
		       __raw_पढ़ोl(&pcicptr->pbareqport));
	पूर्ण
पूर्ण
#घोषणा PCI_DEVICE_ID_EFAR_SLC90E66_0 0x9460
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_EFAR, PCI_DEVICE_ID_EFAR_SLC90E66_0,
	tx4927_quirk_slc90e66_bridge);
#पूर्ण_अगर
