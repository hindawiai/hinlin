<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  ISA Plug & Play support
 *  Copyright (c) by Jaroslav Kysela <perex@perex.cz>
 *
 *  Changelog:
 *  2000-01-01	Added quirks handling क्रम buggy hardware
 *		Peter Denison <peterd@pnd-pc.demon.co.uk>
 *  2000-06-14	Added isapnp_probe_devs() and isapnp_activate_dev()
 *		Christoph Hellwig <hch@infradead.org>
 *  2001-06-03  Added release_region calls to correspond with
 *		request_region calls when a failure occurs.  Also
 *		added KERN_* स्थिरants to prपूर्णांकk() calls.
 *  2001-11-07  Added isapnp_अणु,unपूर्णरेजिस्टर_driver calls aदीर्घ the lines
 *              of the pci driver पूर्णांकerface
 *              Kai Germaschewski <kai.germaschewski@gmx.de>
 *  2002-06-06  Made the use of dma channel 0 configurable
 *              Gerald Teschl <gerald.teschl@univie.ac.at>
 *  2002-10-06  Ported to PnP Layer - Adam Belay <ambx1@neo.rr.com>
 *  2003-08-11	Resource Management Updates - Adam Belay <ambx1@neo.rr.com>
 */

#समावेश <linux/moduleparam.h>
#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/delay.h>
#समावेश <linux/init.h>
#समावेश <linux/isapnp.h>
#समावेश <linux/mutex.h>
#समावेश <यंत्र/पन.स>

#समावेश "../base.h"

#अगर 0
#घोषणा ISAPNP_REGION_OK
#पूर्ण_अगर

पूर्णांक isapnp_disable;		/* Disable ISA PnP */
अटल पूर्णांक isapnp_rdp;		/* Read Data Port */
अटल पूर्णांक isapnp_reset = 1;	/* reset all PnP cards (deactivate) */
अटल पूर्णांक isapnp_verbose = 1;	/* verbose mode */

module_param(isapnp_disable, पूर्णांक, 0);
MODULE_PARM_DESC(isapnp_disable, "ISA Plug & Play disable");
module_param(isapnp_rdp, पूर्णांक, 0);
MODULE_PARM_DESC(isapnp_rdp, "ISA Plug & Play read data port");
module_param(isapnp_reset, पूर्णांक, 0);
MODULE_PARM_DESC(isapnp_reset, "ISA Plug & Play reset all cards");
module_param(isapnp_verbose, पूर्णांक, 0);
MODULE_PARM_DESC(isapnp_verbose, "ISA Plug & Play verbose mode");

#घोषणा _PIDXR		0x279
#घोषणा _PNPWRP		0xa79

/* लघु tags */
#घोषणा _STAG_PNPVERNO		0x01
#घोषणा _STAG_LOGDEVID		0x02
#घोषणा _STAG_COMPATDEVID	0x03
#घोषणा _STAG_IRQ		0x04
#घोषणा _STAG_DMA		0x05
#घोषणा _STAG_STARTDEP		0x06
#घोषणा _STAG_ENDDEP		0x07
#घोषणा _STAG_IOPORT		0x08
#घोषणा _STAG_FIXEDIO		0x09
#घोषणा _STAG_VENDOR		0x0e
#घोषणा _STAG_END		0x0f
/* दीर्घ tags */
#घोषणा _LTAG_MEMRANGE		0x81
#घोषणा _LTAG_ANSISTR		0x82
#घोषणा _LTAG_UNICODESTR	0x83
#घोषणा _LTAG_VENDOR		0x84
#घोषणा _LTAG_MEM32RANGE	0x85
#घोषणा _LTAG_FIXEDMEM32RANGE	0x86

/* Logical device control and configuration रेजिस्टरs */

#घोषणा ISAPNP_CFG_ACTIVATE	0x30	/* byte */
#घोषणा ISAPNP_CFG_MEM		0x40	/* 4 * dword */
#घोषणा ISAPNP_CFG_PORT		0x60	/* 8 * word */
#घोषणा ISAPNP_CFG_IRQ		0x70	/* 2 * word */
#घोषणा ISAPNP_CFG_DMA		0x74	/* 2 * byte */

/*
 * Sizes of ISAPNP logical device configuration रेजिस्टर sets.
 * See PNP-ISA-v1.0a.pdf, Appendix A.
 */
#घोषणा ISAPNP_MAX_MEM		4
#घोषणा ISAPNP_MAX_PORT		8
#घोषणा ISAPNP_MAX_IRQ		2
#घोषणा ISAPNP_MAX_DMA		2

अटल अचिन्हित अक्षर isapnp_checksum_value;
अटल DEFINE_MUTEX(isapnp_cfg_mutex);
अटल पूर्णांक isapnp_csn_count;

/* some prototypes */

अटल अंतरभूत व्योम ग_लिखो_data(अचिन्हित अक्षर x)
अणु
	outb(x, _PNPWRP);
पूर्ण

अटल अंतरभूत व्योम ग_लिखो_address(अचिन्हित अक्षर x)
अणु
	outb(x, _PIDXR);
	udelay(20);
पूर्ण

अटल अंतरभूत अचिन्हित अक्षर पढ़ो_data(व्योम)
अणु
	अचिन्हित अक्षर val = inb(isapnp_rdp);
	वापस val;
पूर्ण

अचिन्हित अक्षर isapnp_पढ़ो_byte(अचिन्हित अक्षर idx)
अणु
	ग_लिखो_address(idx);
	वापस पढ़ो_data();
पूर्ण

अटल अचिन्हित लघु isapnp_पढ़ो_word(अचिन्हित अक्षर idx)
अणु
	अचिन्हित लघु val;

	val = isapnp_पढ़ो_byte(idx);
	val = (val << 8) + isapnp_पढ़ो_byte(idx + 1);
	वापस val;
पूर्ण

व्योम isapnp_ग_लिखो_byte(अचिन्हित अक्षर idx, अचिन्हित अक्षर val)
अणु
	ग_लिखो_address(idx);
	ग_लिखो_data(val);
पूर्ण

अटल व्योम isapnp_ग_लिखो_word(अचिन्हित अक्षर idx, अचिन्हित लघु val)
अणु
	isapnp_ग_लिखो_byte(idx, val >> 8);
	isapnp_ग_लिखो_byte(idx + 1, val);
पूर्ण

अटल व्योम isapnp_key(व्योम)
अणु
	अचिन्हित अक्षर code = 0x6a, msb;
	पूर्णांक i;

	mdelay(1);
	ग_लिखो_address(0x00);
	ग_लिखो_address(0x00);

	ग_लिखो_address(code);

	क्रम (i = 1; i < 32; i++) अणु
		msb = ((code & 0x01) ^ ((code & 0x02) >> 1)) << 7;
		code = (code >> 1) | msb;
		ग_लिखो_address(code);
	पूर्ण
पूर्ण

/* place all pnp cards in रुको-क्रम-key state */
अटल व्योम isapnp_रुको(व्योम)
अणु
	isapnp_ग_लिखो_byte(0x02, 0x02);
पूर्ण

अटल व्योम isapnp_wake(अचिन्हित अक्षर csn)
अणु
	isapnp_ग_लिखो_byte(0x03, csn);
पूर्ण

अटल व्योम isapnp_device(अचिन्हित अक्षर logdev)
अणु
	isapnp_ग_लिखो_byte(0x07, logdev);
पूर्ण

अटल व्योम isapnp_activate(अचिन्हित अक्षर logdev)
अणु
	isapnp_device(logdev);
	isapnp_ग_लिखो_byte(ISAPNP_CFG_ACTIVATE, 1);
	udelay(250);
पूर्ण

अटल व्योम isapnp_deactivate(अचिन्हित अक्षर logdev)
अणु
	isapnp_device(logdev);
	isapnp_ग_लिखो_byte(ISAPNP_CFG_ACTIVATE, 0);
	udelay(500);
पूर्ण

अटल व्योम __init isapnp_peek(अचिन्हित अक्षर *data, पूर्णांक bytes)
अणु
	पूर्णांक i, j;
	अचिन्हित अक्षर d = 0;

	क्रम (i = 1; i <= bytes; i++) अणु
		क्रम (j = 0; j < 20; j++) अणु
			d = isapnp_पढ़ो_byte(0x05);
			अगर (d & 1)
				अवरोध;
			udelay(100);
		पूर्ण
		अगर (!(d & 1)) अणु
			अगर (data != शून्य)
				*data++ = 0xff;
			जारी;
		पूर्ण
		d = isapnp_पढ़ो_byte(0x04);	/* PRESDI */
		isapnp_checksum_value += d;
		अगर (data != शून्य)
			*data++ = d;
	पूर्ण
पूर्ण

#घोषणा RDP_STEP	32	/* minimum is 4 */

अटल पूर्णांक isapnp_next_rdp(व्योम)
अणु
	पूर्णांक rdp = isapnp_rdp;
	अटल पूर्णांक old_rdp = 0;

	अगर (old_rdp) अणु
		release_region(old_rdp, 1);
		old_rdp = 0;
	पूर्ण
	जबतक (rdp <= 0x3ff) अणु
		/*
		 *      We cannot use NE2000 probe spaces क्रम ISAPnP or we
		 *      will lock up machines.
		 */
		अगर ((rdp < 0x280 || rdp > 0x380)
		    && request_region(rdp, 1, "ISAPnP")) अणु
			isapnp_rdp = rdp;
			old_rdp = rdp;
			वापस 0;
		पूर्ण
		rdp += RDP_STEP;
	पूर्ण
	वापस -1;
पूर्ण

/* Set पढ़ो port address */
अटल अंतरभूत व्योम isapnp_set_rdp(व्योम)
अणु
	isapnp_ग_लिखो_byte(0x00, isapnp_rdp >> 2);
	udelay(100);
पूर्ण

/*
 *	Perक्रमm an isolation. The port selection code now tries to aव्योम
 *	"dangerous to read" ports.
 */
अटल पूर्णांक __init isapnp_isolate_rdp_select(व्योम)
अणु
	isapnp_रुको();
	isapnp_key();

	/* Control: reset CSN and conditionally everything अन्यथा too */
	isapnp_ग_लिखो_byte(0x02, isapnp_reset ? 0x05 : 0x04);
	mdelay(2);

	isapnp_रुको();
	isapnp_key();
	isapnp_wake(0x00);

	अगर (isapnp_next_rdp() < 0) अणु
		isapnp_रुको();
		वापस -1;
	पूर्ण

	isapnp_set_rdp();
	udelay(1000);
	ग_लिखो_address(0x01);
	udelay(1000);
	वापस 0;
पूर्ण

/*
 *  Isolate (assign uniqued CSN) to all ISA PnP devices.
 */
अटल पूर्णांक __init isapnp_isolate(व्योम)
अणु
	अचिन्हित अक्षर checksum = 0x6a;
	अचिन्हित अक्षर chksum = 0x00;
	अचिन्हित अक्षर bit = 0x00;
	पूर्णांक data;
	पूर्णांक csn = 0;
	पूर्णांक i;
	पूर्णांक iteration = 1;

	isapnp_rdp = 0x213;
	अगर (isapnp_isolate_rdp_select() < 0)
		वापस -1;

	जबतक (1) अणु
		क्रम (i = 1; i <= 64; i++) अणु
			data = पढ़ो_data() << 8;
			udelay(250);
			data = data | पढ़ो_data();
			udelay(250);
			अगर (data == 0x55aa)
				bit = 0x01;
			checksum =
			    ((((checksum ^ (checksum >> 1)) & 0x01) ^ bit) << 7)
			    | (checksum >> 1);
			bit = 0x00;
		पूर्ण
		क्रम (i = 65; i <= 72; i++) अणु
			data = पढ़ो_data() << 8;
			udelay(250);
			data = data | पढ़ो_data();
			udelay(250);
			अगर (data == 0x55aa)
				chksum |= (1 << (i - 65));
		पूर्ण
		अगर (checksum != 0x00 && checksum == chksum) अणु
			csn++;

			isapnp_ग_लिखो_byte(0x06, csn);
			udelay(250);
			iteration++;
			isapnp_wake(0x00);
			isapnp_set_rdp();
			udelay(1000);
			ग_लिखो_address(0x01);
			udelay(1000);
			जाओ __next;
		पूर्ण
		अगर (iteration == 1) अणु
			isapnp_rdp += RDP_STEP;
			अगर (isapnp_isolate_rdp_select() < 0)
				वापस -1;
		पूर्ण अन्यथा अगर (iteration > 1) अणु
			अवरोध;
		पूर्ण
__next:
		अगर (csn == 255)
			अवरोध;
		checksum = 0x6a;
		chksum = 0x00;
		bit = 0x00;
	पूर्ण
	isapnp_रुको();
	isapnp_csn_count = csn;
	वापस csn;
पूर्ण

/*
 *  Read one tag from stream.
 */
अटल पूर्णांक __init isapnp_पढ़ो_tag(अचिन्हित अक्षर *type, अचिन्हित लघु *size)
अणु
	अचिन्हित अक्षर tag, पंचांगp[2];

	isapnp_peek(&tag, 1);
	अगर (tag == 0)		/* invalid tag */
		वापस -1;
	अगर (tag & 0x80) अणु	/* large item */
		*type = tag;
		isapnp_peek(पंचांगp, 2);
		*size = (पंचांगp[1] << 8) | पंचांगp[0];
	पूर्ण अन्यथा अणु
		*type = (tag >> 3) & 0x0f;
		*size = tag & 0x07;
	पूर्ण
	अगर (*type == 0xff && *size == 0xffff)	/* probably invalid data */
		वापस -1;
	वापस 0;
पूर्ण

/*
 *  Skip specअगरied number of bytes from stream.
 */
अटल व्योम __init isapnp_skip_bytes(पूर्णांक count)
अणु
	isapnp_peek(शून्य, count);
पूर्ण

/*
 *  Parse logical device tag.
 */
अटल काष्ठा pnp_dev *__init isapnp_parse_device(काष्ठा pnp_card *card,
						  पूर्णांक size, पूर्णांक number)
अणु
	अचिन्हित अक्षर पंचांगp[6];
	काष्ठा pnp_dev *dev;
	u32 eisa_id;
	अक्षर id[8];

	isapnp_peek(पंचांगp, size);
	eisa_id = पंचांगp[0] | पंचांगp[1] << 8 | पंचांगp[2] << 16 | पंचांगp[3] << 24;
	pnp_eisa_id_to_string(eisa_id, id);

	dev = pnp_alloc_dev(&isapnp_protocol, number, id);
	अगर (!dev)
		वापस शून्य;

	dev->card = card;
	dev->capabilities |= PNP_CONFIGURABLE;
	dev->capabilities |= PNP_READ;
	dev->capabilities |= PNP_WRITE;
	dev->capabilities |= PNP_DISABLE;
	pnp_init_resources(dev);
	वापस dev;
पूर्ण

/*
 *  Add IRQ resource to resources list.
 */
अटल व्योम __init isapnp_parse_irq_resource(काष्ठा pnp_dev *dev,
					     अचिन्हित पूर्णांक option_flags,
					     पूर्णांक size)
अणु
	अचिन्हित अक्षर पंचांगp[3];
	अचिन्हित दीर्घ bits;
	pnp_irq_mask_t map;
	अचिन्हित अक्षर flags = IORESOURCE_IRQ_HIGHEDGE;

	isapnp_peek(पंचांगp, size);
	bits = (पंचांगp[1] << 8) | पंचांगp[0];

	biपंचांगap_zero(map.bits, PNP_IRQ_NR);
	biपंचांगap_copy(map.bits, &bits, 16);

	अगर (size > 2)
		flags = पंचांगp[2];

	pnp_रेजिस्टर_irq_resource(dev, option_flags, &map, flags);
पूर्ण

/*
 *  Add DMA resource to resources list.
 */
अटल व्योम __init isapnp_parse_dma_resource(काष्ठा pnp_dev *dev,
					     अचिन्हित पूर्णांक option_flags,
					     पूर्णांक size)
अणु
	अचिन्हित अक्षर पंचांगp[2];

	isapnp_peek(पंचांगp, size);
	pnp_रेजिस्टर_dma_resource(dev, option_flags, पंचांगp[0], पंचांगp[1]);
पूर्ण

/*
 *  Add port resource to resources list.
 */
अटल व्योम __init isapnp_parse_port_resource(काष्ठा pnp_dev *dev,
					      अचिन्हित पूर्णांक option_flags,
					      पूर्णांक size)
अणु
	अचिन्हित अक्षर पंचांगp[7];
	resource_माप_प्रकार min, max, align, len;
	अचिन्हित अक्षर flags;

	isapnp_peek(पंचांगp, size);
	min = (पंचांगp[2] << 8) | पंचांगp[1];
	max = (पंचांगp[4] << 8) | पंचांगp[3];
	align = पंचांगp[5];
	len = पंचांगp[6];
	flags = पंचांगp[0] ? IORESOURCE_IO_16BIT_ADDR : 0;
	pnp_रेजिस्टर_port_resource(dev, option_flags,
				   min, max, align, len, flags);
पूर्ण

/*
 *  Add fixed port resource to resources list.
 */
अटल व्योम __init isapnp_parse_fixed_port_resource(काष्ठा pnp_dev *dev,
						    अचिन्हित पूर्णांक option_flags,
						    पूर्णांक size)
अणु
	अचिन्हित अक्षर पंचांगp[3];
	resource_माप_प्रकार base, len;

	isapnp_peek(पंचांगp, size);
	base = (पंचांगp[1] << 8) | पंचांगp[0];
	len = पंचांगp[2];
	pnp_रेजिस्टर_port_resource(dev, option_flags, base, base, 0, len,
				   IORESOURCE_IO_FIXED);
पूर्ण

/*
 *  Add memory resource to resources list.
 */
अटल व्योम __init isapnp_parse_mem_resource(काष्ठा pnp_dev *dev,
					     अचिन्हित पूर्णांक option_flags,
					     पूर्णांक size)
अणु
	अचिन्हित अक्षर पंचांगp[9];
	resource_माप_प्रकार min, max, align, len;
	अचिन्हित अक्षर flags;

	isapnp_peek(पंचांगp, size);
	min = ((पंचांगp[2] << 8) | पंचांगp[1]) << 8;
	max = ((पंचांगp[4] << 8) | पंचांगp[3]) << 8;
	align = (पंचांगp[6] << 8) | पंचांगp[5];
	len = ((पंचांगp[8] << 8) | पंचांगp[7]) << 8;
	flags = पंचांगp[0];
	pnp_रेजिस्टर_mem_resource(dev, option_flags,
				  min, max, align, len, flags);
पूर्ण

/*
 *  Add 32-bit memory resource to resources list.
 */
अटल व्योम __init isapnp_parse_mem32_resource(काष्ठा pnp_dev *dev,
					       अचिन्हित पूर्णांक option_flags,
					       पूर्णांक size)
अणु
	अचिन्हित अक्षर पंचांगp[17];
	resource_माप_प्रकार min, max, align, len;
	अचिन्हित अक्षर flags;

	isapnp_peek(पंचांगp, size);
	min = (पंचांगp[4] << 24) | (पंचांगp[3] << 16) | (पंचांगp[2] << 8) | पंचांगp[1];
	max = (पंचांगp[8] << 24) | (पंचांगp[7] << 16) | (पंचांगp[6] << 8) | पंचांगp[5];
	align = (पंचांगp[12] << 24) | (पंचांगp[11] << 16) | (पंचांगp[10] << 8) | पंचांगp[9];
	len = (पंचांगp[16] << 24) | (पंचांगp[15] << 16) | (पंचांगp[14] << 8) | पंचांगp[13];
	flags = पंचांगp[0];
	pnp_रेजिस्टर_mem_resource(dev, option_flags,
				  min, max, align, len, flags);
पूर्ण

/*
 *  Add 32-bit fixed memory resource to resources list.
 */
अटल व्योम __init isapnp_parse_fixed_mem32_resource(काष्ठा pnp_dev *dev,
						     अचिन्हित पूर्णांक option_flags,
						     पूर्णांक size)
अणु
	अचिन्हित अक्षर पंचांगp[9];
	resource_माप_प्रकार base, len;
	अचिन्हित अक्षर flags;

	isapnp_peek(पंचांगp, size);
	base = (पंचांगp[4] << 24) | (पंचांगp[3] << 16) | (पंचांगp[2] << 8) | पंचांगp[1];
	len = (पंचांगp[8] << 24) | (पंचांगp[7] << 16) | (पंचांगp[6] << 8) | पंचांगp[5];
	flags = पंचांगp[0];
	pnp_रेजिस्टर_mem_resource(dev, option_flags, base, base, 0, len, flags);
पूर्ण

/*
 *  Parse card name क्रम ISA PnP device.
 */
अटल व्योम __init
isapnp_parse_name(अक्षर *name, अचिन्हित पूर्णांक name_max, अचिन्हित लघु *size)
अणु
	अगर (name[0] == '\0') अणु
		अचिन्हित लघु size1 =
		    *size >= name_max ? (name_max - 1) : *size;
		isapnp_peek(name, size1);
		name[size1] = '\0';
		*size -= size1;

		/* clean whitespace from end of string */
		जबतक (size1 > 0 && name[--size1] == ' ')
			name[size1] = '\0';
	पूर्ण
पूर्ण

/*
 *  Parse resource map क्रम logical device.
 */
अटल पूर्णांक __init isapnp_create_device(काष्ठा pnp_card *card,
				       अचिन्हित लघु size)
अणु
	पूर्णांक number = 0, skip = 0, priority, compat = 0;
	अचिन्हित अक्षर type, पंचांगp[17];
	अचिन्हित पूर्णांक option_flags;
	काष्ठा pnp_dev *dev;
	u32 eisa_id;
	अक्षर id[8];

	अगर ((dev = isapnp_parse_device(card, size, number++)) == शून्य)
		वापस 1;
	option_flags = 0;
	pnp_add_card_device(card, dev);

	जबतक (1) अणु
		अगर (isapnp_पढ़ो_tag(&type, &size) < 0)
			वापस 1;
		अगर (skip && type != _STAG_LOGDEVID && type != _STAG_END)
			जाओ __skip;
		चयन (type) अणु
		हाल _STAG_LOGDEVID:
			अगर (size >= 5 && size <= 6) अणु
				अगर ((dev =
				     isapnp_parse_device(card, size,
							 number++)) == शून्य)
					वापस 1;
				size = 0;
				skip = 0;
				option_flags = 0;
				pnp_add_card_device(card, dev);
			पूर्ण अन्यथा अणु
				skip = 1;
			पूर्ण
			compat = 0;
			अवरोध;
		हाल _STAG_COMPATDEVID:
			अगर (size == 4 && compat < DEVICE_COUNT_COMPATIBLE) अणु
				isapnp_peek(पंचांगp, 4);
				eisa_id = पंचांगp[0] | पंचांगp[1] << 8 |
					  पंचांगp[2] << 16 | पंचांगp[3] << 24;
				pnp_eisa_id_to_string(eisa_id, id);
				pnp_add_id(dev, id);
				compat++;
				size = 0;
			पूर्ण
			अवरोध;
		हाल _STAG_IRQ:
			अगर (size < 2 || size > 3)
				जाओ __skip;
			isapnp_parse_irq_resource(dev, option_flags, size);
			size = 0;
			अवरोध;
		हाल _STAG_DMA:
			अगर (size != 2)
				जाओ __skip;
			isapnp_parse_dma_resource(dev, option_flags, size);
			size = 0;
			अवरोध;
		हाल _STAG_STARTDEP:
			अगर (size > 1)
				जाओ __skip;
			priority = PNP_RES_PRIORITY_ACCEPTABLE;
			अगर (size > 0) अणु
				isapnp_peek(पंचांगp, size);
				priority = पंचांगp[0];
				size = 0;
			पूर्ण
			option_flags = pnp_new_dependent_set(dev, priority);
			अवरोध;
		हाल _STAG_ENDDEP:
			अगर (size != 0)
				जाओ __skip;
			option_flags = 0;
			अवरोध;
		हाल _STAG_IOPORT:
			अगर (size != 7)
				जाओ __skip;
			isapnp_parse_port_resource(dev, option_flags, size);
			size = 0;
			अवरोध;
		हाल _STAG_FIXEDIO:
			अगर (size != 3)
				जाओ __skip;
			isapnp_parse_fixed_port_resource(dev, option_flags,
							 size);
			size = 0;
			अवरोध;
		हाल _STAG_VENDOR:
			अवरोध;
		हाल _LTAG_MEMRANGE:
			अगर (size != 9)
				जाओ __skip;
			isapnp_parse_mem_resource(dev, option_flags, size);
			size = 0;
			अवरोध;
		हाल _LTAG_ANSISTR:
			isapnp_parse_name(dev->name, माप(dev->name), &size);
			अवरोध;
		हाल _LTAG_UNICODESTR:
			/* silently ignore */
			/* who use unicode क्रम hardware identअगरication? */
			अवरोध;
		हाल _LTAG_VENDOR:
			अवरोध;
		हाल _LTAG_MEM32RANGE:
			अगर (size != 17)
				जाओ __skip;
			isapnp_parse_mem32_resource(dev, option_flags, size);
			size = 0;
			अवरोध;
		हाल _LTAG_FIXEDMEM32RANGE:
			अगर (size != 9)
				जाओ __skip;
			isapnp_parse_fixed_mem32_resource(dev, option_flags,
							  size);
			size = 0;
			अवरोध;
		हाल _STAG_END:
			अगर (size > 0)
				isapnp_skip_bytes(size);
			वापस 1;
		शेष:
			dev_err(&dev->dev, "unknown tag %#x (card %i), "
				"ignored\n", type, card->number);
		पूर्ण
__skip:
		अगर (size > 0)
			isapnp_skip_bytes(size);
	पूर्ण
	वापस 0;
पूर्ण

/*
 *  Parse resource map क्रम ISA PnP card.
 */
अटल व्योम __init isapnp_parse_resource_map(काष्ठा pnp_card *card)
अणु
	अचिन्हित अक्षर type, पंचांगp[17];
	अचिन्हित लघु size;

	जबतक (1) अणु
		अगर (isapnp_पढ़ो_tag(&type, &size) < 0)
			वापस;
		चयन (type) अणु
		हाल _STAG_PNPVERNO:
			अगर (size != 2)
				जाओ __skip;
			isapnp_peek(पंचांगp, 2);
			card->pnpver = पंचांगp[0];
			card->productver = पंचांगp[1];
			size = 0;
			अवरोध;
		हाल _STAG_LOGDEVID:
			अगर (size >= 5 && size <= 6) अणु
				अगर (isapnp_create_device(card, size) == 1)
					वापस;
				size = 0;
			पूर्ण
			अवरोध;
		हाल _STAG_VENDOR:
			अवरोध;
		हाल _LTAG_ANSISTR:
			isapnp_parse_name(card->name, माप(card->name),
					  &size);
			अवरोध;
		हाल _LTAG_UNICODESTR:
			/* silently ignore */
			/* who use unicode क्रम hardware identअगरication? */
			अवरोध;
		हाल _LTAG_VENDOR:
			अवरोध;
		हाल _STAG_END:
			अगर (size > 0)
				isapnp_skip_bytes(size);
			वापस;
		शेष:
			dev_err(&card->dev, "unknown tag %#x, ignored\n",
			       type);
		पूर्ण
__skip:
		अगर (size > 0)
			isapnp_skip_bytes(size);
	पूर्ण
पूर्ण

/*
 *  Build device list क्रम all present ISA PnP devices.
 */
अटल पूर्णांक __init isapnp_build_device_list(व्योम)
अणु
	पूर्णांक csn;
	अचिन्हित अक्षर header[9];
	काष्ठा pnp_card *card;
	u32 eisa_id;
	अक्षर id[8];

	isapnp_रुको();
	isapnp_key();
	क्रम (csn = 1; csn <= isapnp_csn_count; csn++) अणु
		isapnp_wake(csn);
		isapnp_peek(header, 9);
		eisa_id = header[0] | header[1] << 8 |
			  header[2] << 16 | header[3] << 24;
		pnp_eisa_id_to_string(eisa_id, id);
		card = pnp_alloc_card(&isapnp_protocol, csn, id);
		अगर (!card)
			जारी;

		INIT_LIST_HEAD(&card->devices);
		card->serial =
		    (header[7] << 24) | (header[6] << 16) | (header[5] << 8) |
		    header[4];
		isapnp_checksum_value = 0x00;
		isapnp_parse_resource_map(card);
		अगर (isapnp_checksum_value != 0x00)
			dev_err(&card->dev, "invalid checksum %#x\n",
				isapnp_checksum_value);
		card->checksum = isapnp_checksum_value;

		pnp_add_card(card);
	पूर्ण
	isapnp_रुको();
	वापस 0;
पूर्ण

/*
 *  Basic configuration routines.
 */

पूर्णांक isapnp_present(व्योम)
अणु
	काष्ठा pnp_card *card;

	pnp_क्रम_each_card(card) अणु
		अगर (card->protocol == &isapnp_protocol)
			वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक isapnp_cfg_begin(पूर्णांक csn, पूर्णांक logdev)
अणु
	अगर (csn < 1 || csn > isapnp_csn_count || logdev > 10)
		वापस -EINVAL;
	mutex_lock(&isapnp_cfg_mutex);
	isapnp_रुको();
	isapnp_key();
	isapnp_wake(csn);
#अगर 0
	/* to aव्योम malfunction when the isapnptools package is used */
	/* we must set RDP to our value again */
	/* it is possible to set RDP only in the isolation phase */
	/*   Jens Thoms Toerring <Jens.Toerring@physik.fu-berlin.de> */
	isapnp_ग_लिखो_byte(0x02, 0x04);	/* clear CSN of card */
	mdelay(2);		/* is this necessary? */
	isapnp_wake(csn);	/* bring card पूर्णांकo sleep state */
	isapnp_wake(0);		/* bring card पूर्णांकo isolation state */
	isapnp_set_rdp();	/* reset the RDP port */
	udelay(1000);		/* delay 1000us */
	isapnp_ग_लिखो_byte(0x06, csn);	/* reset CSN to previous value */
	udelay(250);		/* is this necessary? */
#पूर्ण_अगर
	अगर (logdev >= 0)
		isapnp_device(logdev);
	वापस 0;
पूर्ण

पूर्णांक isapnp_cfg_end(व्योम)
अणु
	isapnp_रुको();
	mutex_unlock(&isapnp_cfg_mutex);
	वापस 0;
पूर्ण

/*
 *  Initialization.
 */

EXPORT_SYMBOL(isapnp_protocol);
EXPORT_SYMBOL(isapnp_present);
EXPORT_SYMBOL(isapnp_cfg_begin);
EXPORT_SYMBOL(isapnp_cfg_end);
EXPORT_SYMBOL(isapnp_ग_लिखो_byte);

अटल पूर्णांक isapnp_get_resources(काष्ठा pnp_dev *dev)
अणु
	पूर्णांक i, ret;

	pnp_dbg(&dev->dev, "get resources\n");
	pnp_init_resources(dev);
	isapnp_cfg_begin(dev->card->number, dev->number);
	dev->active = isapnp_पढ़ो_byte(ISAPNP_CFG_ACTIVATE);
	अगर (!dev->active)
		जाओ __end;

	क्रम (i = 0; i < ISAPNP_MAX_PORT; i++) अणु
		ret = isapnp_पढ़ो_word(ISAPNP_CFG_PORT + (i << 1));
		pnp_add_io_resource(dev, ret, ret,
				    ret == 0 ? IORESOURCE_DISABLED : 0);
	पूर्ण
	क्रम (i = 0; i < ISAPNP_MAX_MEM; i++) अणु
		ret = isapnp_पढ़ो_word(ISAPNP_CFG_MEM + (i << 3)) << 8;
		pnp_add_mem_resource(dev, ret, ret,
				     ret == 0 ? IORESOURCE_DISABLED : 0);
	पूर्ण
	क्रम (i = 0; i < ISAPNP_MAX_IRQ; i++) अणु
		ret = isapnp_पढ़ो_word(ISAPNP_CFG_IRQ + (i << 1)) >> 8;
		pnp_add_irq_resource(dev, ret,
				     ret == 0 ? IORESOURCE_DISABLED : 0);
	पूर्ण
	क्रम (i = 0; i < ISAPNP_MAX_DMA; i++) अणु
		ret = isapnp_पढ़ो_byte(ISAPNP_CFG_DMA + i);
		pnp_add_dma_resource(dev, ret,
				     ret == 4 ? IORESOURCE_DISABLED : 0);
	पूर्ण

__end:
	isapnp_cfg_end();
	वापस 0;
पूर्ण

अटल पूर्णांक isapnp_set_resources(काष्ठा pnp_dev *dev)
अणु
	काष्ठा resource *res;
	पूर्णांक पंचांगp;

	pnp_dbg(&dev->dev, "set resources\n");
	isapnp_cfg_begin(dev->card->number, dev->number);
	dev->active = 1;
	क्रम (पंचांगp = 0; पंचांगp < ISAPNP_MAX_PORT; पंचांगp++) अणु
		res = pnp_get_resource(dev, IORESOURCE_IO, पंचांगp);
		अगर (pnp_resource_enabled(res)) अणु
			pnp_dbg(&dev->dev, "  set io  %d to %#llx\n",
				पंचांगp, (अचिन्हित दीर्घ दीर्घ) res->start);
			isapnp_ग_लिखो_word(ISAPNP_CFG_PORT + (पंचांगp << 1),
					  res->start);
		पूर्ण
	पूर्ण
	क्रम (पंचांगp = 0; पंचांगp < ISAPNP_MAX_IRQ; पंचांगp++) अणु
		res = pnp_get_resource(dev, IORESOURCE_IRQ, पंचांगp);
		अगर (pnp_resource_enabled(res)) अणु
			पूर्णांक irq = res->start;
			अगर (irq == 2)
				irq = 9;
			pnp_dbg(&dev->dev, "  set irq %d to %d\n", पंचांगp, irq);
			isapnp_ग_लिखो_byte(ISAPNP_CFG_IRQ + (पंचांगp << 1), irq);
		पूर्ण
	पूर्ण
	क्रम (पंचांगp = 0; पंचांगp < ISAPNP_MAX_DMA; पंचांगp++) अणु
		res = pnp_get_resource(dev, IORESOURCE_DMA, पंचांगp);
		अगर (pnp_resource_enabled(res)) अणु
			pnp_dbg(&dev->dev, "  set dma %d to %lld\n",
				पंचांगp, (अचिन्हित दीर्घ दीर्घ) res->start);
			isapnp_ग_लिखो_byte(ISAPNP_CFG_DMA + पंचांगp, res->start);
		पूर्ण
	पूर्ण
	क्रम (पंचांगp = 0; पंचांगp < ISAPNP_MAX_MEM; पंचांगp++) अणु
		res = pnp_get_resource(dev, IORESOURCE_MEM, पंचांगp);
		अगर (pnp_resource_enabled(res)) अणु
			pnp_dbg(&dev->dev, "  set mem %d to %#llx\n",
				पंचांगp, (अचिन्हित दीर्घ दीर्घ) res->start);
			isapnp_ग_लिखो_word(ISAPNP_CFG_MEM + (पंचांगp << 3),
					  (res->start >> 8) & 0xffff);
		पूर्ण
	पूर्ण
	/* FIXME: We aren't handling 32bit mems properly here */
	isapnp_activate(dev->number);
	isapnp_cfg_end();
	वापस 0;
पूर्ण

अटल पूर्णांक isapnp_disable_resources(काष्ठा pnp_dev *dev)
अणु
	अगर (!dev->active)
		वापस -EINVAL;
	isapnp_cfg_begin(dev->card->number, dev->number);
	isapnp_deactivate(dev->number);
	dev->active = 0;
	isapnp_cfg_end();
	वापस 0;
पूर्ण

काष्ठा pnp_protocol isapnp_protocol = अणु
	.name = "ISA Plug and Play",
	.get = isapnp_get_resources,
	.set = isapnp_set_resources,
	.disable = isapnp_disable_resources,
पूर्ण;

अटल पूर्णांक __init isapnp_init(व्योम)
अणु
	पूर्णांक cards;
	काष्ठा pnp_card *card;
	काष्ठा pnp_dev *dev;

	अगर (isapnp_disable) अणु
		prपूर्णांकk(KERN_INFO "isapnp: ISA Plug & Play support disabled\n");
		वापस 0;
	पूर्ण
#अगर_घोषित CONFIG_PPC
	अगर (check_legacy_ioport(_PIDXR) || check_legacy_ioport(_PNPWRP))
		वापस -EINVAL;
#पूर्ण_अगर
#अगर_घोषित ISAPNP_REGION_OK
	अगर (!request_region(_PIDXR, 1, "isapnp index")) अणु
		prपूर्णांकk(KERN_ERR "isapnp: Index Register 0x%x already used\n",
		       _PIDXR);
		वापस -EBUSY;
	पूर्ण
#पूर्ण_अगर
	अगर (!request_region(_PNPWRP, 1, "isapnp write")) अणु
		prपूर्णांकk(KERN_ERR
		       "isapnp: Write Data Register 0x%x already used\n",
		       _PNPWRP);
#अगर_घोषित ISAPNP_REGION_OK
		release_region(_PIDXR, 1);
#पूर्ण_अगर
		वापस -EBUSY;
	पूर्ण

	अगर (pnp_रेजिस्टर_protocol(&isapnp_protocol) < 0)
		वापस -EBUSY;

	/*
	 *      Prपूर्णांक a message. The existing ISAPnP code is hanging machines
	 *      so let the user know where.
	 */

	prपूर्णांकk(KERN_INFO "isapnp: Scanning for PnP cards...\n");
	अगर (isapnp_rdp >= 0x203 && isapnp_rdp <= 0x3ff) अणु
		isapnp_rdp |= 3;
		अगर (!request_region(isapnp_rdp, 1, "isapnp read")) अणु
			prपूर्णांकk(KERN_ERR
			       "isapnp: Read Data Register 0x%x already used\n",
			       isapnp_rdp);
#अगर_घोषित ISAPNP_REGION_OK
			release_region(_PIDXR, 1);
#पूर्ण_अगर
			release_region(_PNPWRP, 1);
			वापस -EBUSY;
		पूर्ण
		isapnp_set_rdp();
	पूर्ण
	अगर (isapnp_rdp < 0x203 || isapnp_rdp > 0x3ff) अणु
		cards = isapnp_isolate();
		अगर (cards < 0 || (isapnp_rdp < 0x203 || isapnp_rdp > 0x3ff)) अणु
#अगर_घोषित ISAPNP_REGION_OK
			release_region(_PIDXR, 1);
#पूर्ण_अगर
			release_region(_PNPWRP, 1);
			prपूर्णांकk(KERN_INFO
			       "isapnp: No Plug & Play device found\n");
			वापस 0;
		पूर्ण
		request_region(isapnp_rdp, 1, "isapnp read");
	पूर्ण
	isapnp_build_device_list();
	cards = 0;

	protocol_क्रम_each_card(&isapnp_protocol, card) अणु
		cards++;
		अगर (isapnp_verbose) अणु
			dev_info(&card->dev, "card '%s'\n",
			       card->name[0] ? card->name : "unknown");
			अगर (isapnp_verbose < 2)
				जारी;
			card_क्रम_each_dev(card, dev) अणु
				dev_info(&card->dev, "device '%s'\n",
				       dev->name[0] ? dev->name : "unknown");
			पूर्ण
		पूर्ण
	पूर्ण
	अगर (cards)
		prपूर्णांकk(KERN_INFO
		       "isapnp: %i Plug & Play card%s detected total\n", cards,
		       cards > 1 ? "s" : "");
	अन्यथा
		prपूर्णांकk(KERN_INFO "isapnp: No Plug & Play card found\n");

	isapnp_proc_init();
	वापस 0;
पूर्ण

device_initcall(isapnp_init);

/* क्रमmat is: noisapnp */

अटल पूर्णांक __init isapnp_setup_disable(अक्षर *str)
अणु
	isapnp_disable = 1;
	वापस 1;
पूर्ण

__setup("noisapnp", isapnp_setup_disable);

/* क्रमmat is: isapnp=rdp,reset,skip_pci_scan,verbose */

अटल पूर्णांक __init isapnp_setup_isapnp(अक्षर *str)
अणु
	(व्योम)((get_option(&str, &isapnp_rdp) == 2) &&
	       (get_option(&str, &isapnp_reset) == 2) &&
	       (get_option(&str, &isapnp_verbose) == 2));
	वापस 1;
पूर्ण

__setup("isapnp=", isapnp_setup_isapnp);
