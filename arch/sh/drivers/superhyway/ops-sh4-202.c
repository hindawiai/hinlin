<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * arch/sh/drivers/superhyway/ops-sh4-202.c
 *
 * SuperHyway bus support क्रम SH4-202
 *
 * Copyright (C) 2005  Paul Mundt
 */
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/superhyway.h>
#समावेश <linux/माला.स>
#समावेश <यंत्र/addrspace.h>
#समावेश <यंत्र/पन.स>

#घोषणा PHYS_EMI_CBLOCK		P4SEGADDR(0x1ec00000)
#घोषणा PHYS_EMI_DBLOCK		P4SEGADDR(0x08000000)
#घोषणा PHYS_FEMI_CBLOCK	P4SEGADDR(0x1f800000)
#घोषणा PHYS_FEMI_DBLOCK	P4SEGADDR(0x00000000)

#घोषणा PHYS_EPBR_BLOCK		P4SEGADDR(0x1de00000)
#घोषणा PHYS_DMAC_BLOCK		P4SEGADDR(0x1fa00000)
#घोषणा PHYS_PBR_BLOCK		P4SEGADDR(0x1fc00000)

अटल काष्ठा resource emi_resources[] = अणु
	[0] = अणु
		.start	= PHYS_EMI_CBLOCK,
		.end	= PHYS_EMI_CBLOCK + 0x00300000 - 1,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
	[1] = अणु
		.start	= PHYS_EMI_DBLOCK,
		.end	= PHYS_EMI_DBLOCK + 0x08000000 - 1,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
पूर्ण;

अटल काष्ठा superhyway_device emi_device = अणु
	.name		= "emi",
	.num_resources	= ARRAY_SIZE(emi_resources),
	.resource	= emi_resources,
पूर्ण;

अटल काष्ठा resource femi_resources[] = अणु
	[0] = अणु
		.start	= PHYS_FEMI_CBLOCK,
		.end	= PHYS_FEMI_CBLOCK + 0x00100000 - 1,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
	[1] = अणु
		.start	= PHYS_FEMI_DBLOCK,
		.end	= PHYS_FEMI_DBLOCK + 0x08000000 - 1,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
पूर्ण;

अटल काष्ठा superhyway_device femi_device = अणु
	.name		= "femi",
	.num_resources	= ARRAY_SIZE(femi_resources),
	.resource	= femi_resources,
पूर्ण;

अटल काष्ठा resource epbr_resources[] = अणु
	[0] = अणु
		.start	= P4SEGADDR(0x1e7ffff8),
		.end	= P4SEGADDR(0x1e7ffff8 + (माप(u32) * 2) - 1),
		.flags	= IORESOURCE_MEM,
	पूर्ण,
	[1] = अणु
		.start	= PHYS_EPBR_BLOCK,
		.end	= PHYS_EPBR_BLOCK + 0x00a00000 - 1,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
पूर्ण;

अटल काष्ठा superhyway_device epbr_device = अणु
	.name		= "epbr",
	.num_resources	= ARRAY_SIZE(epbr_resources),
	.resource	= epbr_resources,
पूर्ण;

अटल काष्ठा resource dmac_resource = अणु
	.start	= PHYS_DMAC_BLOCK,
	.end	= PHYS_DMAC_BLOCK + 0x00100000 - 1,
	.flags	= IORESOURCE_MEM,
पूर्ण;

अटल काष्ठा superhyway_device dmac_device = अणु
	.name		= "dmac",
	.num_resources	= 1,
	.resource	= &dmac_resource,
पूर्ण;

अटल काष्ठा resource pbr_resources[] = अणु
	[0] = अणु
		.start	= P4SEGADDR(0x1ffffff8),
		.end	= P4SEGADDR(0x1ffffff8 + (माप(u32) * 2) - 1),
		.flags	= IORESOURCE_MEM,
	पूर्ण,
	[1] = अणु
		.start	= PHYS_PBR_BLOCK,
		.end	= PHYS_PBR_BLOCK + 0x00400000 - (माप(u32) * 2) - 1,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
पूर्ण;

अटल काष्ठा superhyway_device pbr_device = अणु
	.name		= "pbr",
	.num_resources	= ARRAY_SIZE(pbr_resources),
	.resource	= pbr_resources,
पूर्ण;

अटल काष्ठा superhyway_device *sh4202_devices[] __initdata = अणु
	&emi_device, &femi_device, &epbr_device, &dmac_device, &pbr_device,
पूर्ण;

अटल पूर्णांक sh4202_पढ़ो_vcr(अचिन्हित दीर्घ base, काष्ठा superhyway_vcr_info *vcr)
अणु
	u32 vcrh, vcrl;
	u64 पंचांगp;

	/*
	 * XXX: Even though the SH4-202 Evaluation Device करोcumentation
	 * indicates that VCRL is mapped first with VCRH at a + 0x04
	 * offset, the opposite seems to be true.
	 *
	 * Some modules (PBR and ePBR क्रम instance) also appear to have
	 * VCRL/VCRH flipped in the करोcumentation, but on the SH4-202
	 * itself it appears that these are all consistently mapped with
	 * VCRH preceding VCRL.
	 *
	 * Do not trust the करोcumentation, क्रम it is evil.
	 */
	vcrh = __raw_पढ़ोl(base);
	vcrl = __raw_पढ़ोl(base + माप(u32));

	पंचांगp = ((u64)vcrh << 32) | vcrl;
	स_नकल(vcr, &पंचांगp, माप(u64));

	वापस 0;
पूर्ण

अटल पूर्णांक sh4202_ग_लिखो_vcr(अचिन्हित दीर्घ base, काष्ठा superhyway_vcr_info vcr)
अणु
	u64 पंचांगp = *(u64 *)&vcr;

	__raw_ग_लिखोl((पंचांगp >> 32) & 0xffffffff, base);
	__raw_ग_लिखोl(पंचांगp & 0xffffffff, base + माप(u32));

	वापस 0;
पूर्ण

अटल काष्ठा superhyway_ops sh4202_superhyway_ops = अणु
	.पढ़ो_vcr	= sh4202_पढ़ो_vcr,
	.ग_लिखो_vcr	= sh4202_ग_लिखो_vcr,
पूर्ण;

काष्ठा superhyway_bus superhyway_channels[] = अणु
	अणु &sh4202_superhyway_ops, पूर्ण,
	अणु 0, पूर्ण,
पूर्ण;

पूर्णांक __init superhyway_scan_bus(काष्ठा superhyway_bus *bus)
अणु
	वापस superhyway_add_devices(bus, sh4202_devices,
				      ARRAY_SIZE(sh4202_devices));
पूर्ण

