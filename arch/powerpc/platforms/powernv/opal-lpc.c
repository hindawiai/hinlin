<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * PowerNV LPC bus handling.
 *
 * Copyright 2013 IBM Corp.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/of.h>
#समावेश <linux/bug.h>
#समावेश <linux/पन.स>
#समावेश <linux/slab.h>

#समावेश <यंत्र/machdep.h>
#समावेश <यंत्र/firmware.h>
#समावेश <यंत्र/opal.h>
#समावेश <यंत्र/prom.h>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/debugfs.h>
#समावेश <यंत्र/isa-bridge.h>

अटल पूर्णांक opal_lpc_chip_id = -1;

अटल u8 opal_lpc_inb(अचिन्हित दीर्घ port)
अणु
	पूर्णांक64_t rc;
	__be32 data;

	अगर (opal_lpc_chip_id < 0 || port > 0xffff)
		वापस 0xff;
	rc = opal_lpc_पढ़ो(opal_lpc_chip_id, OPAL_LPC_IO, port, &data, 1);
	वापस rc ? 0xff : be32_to_cpu(data);
पूर्ण

अटल __le16 __opal_lpc_inw(अचिन्हित दीर्घ port)
अणु
	पूर्णांक64_t rc;
	__be32 data;

	अगर (opal_lpc_chip_id < 0 || port > 0xfffe)
		वापस 0xffff;
	अगर (port & 1)
		वापस (__le16)opal_lpc_inb(port) << 8 | opal_lpc_inb(port + 1);
	rc = opal_lpc_पढ़ो(opal_lpc_chip_id, OPAL_LPC_IO, port, &data, 2);
	वापस rc ? 0xffff : be32_to_cpu(data);
पूर्ण
अटल u16 opal_lpc_inw(अचिन्हित दीर्घ port)
अणु
	वापस le16_to_cpu(__opal_lpc_inw(port));
पूर्ण

अटल __le32 __opal_lpc_inl(अचिन्हित दीर्घ port)
अणु
	पूर्णांक64_t rc;
	__be32 data;

	अगर (opal_lpc_chip_id < 0 || port > 0xfffc)
		वापस 0xffffffff;
	अगर (port & 3)
		वापस (__le32)opal_lpc_inb(port    ) << 24 |
		       (__le32)opal_lpc_inb(port + 1) << 16 |
		       (__le32)opal_lpc_inb(port + 2) <<  8 |
			       opal_lpc_inb(port + 3);
	rc = opal_lpc_पढ़ो(opal_lpc_chip_id, OPAL_LPC_IO, port, &data, 4);
	वापस rc ? 0xffffffff : be32_to_cpu(data);
पूर्ण

अटल u32 opal_lpc_inl(अचिन्हित दीर्घ port)
अणु
	वापस le32_to_cpu(__opal_lpc_inl(port));
पूर्ण

अटल व्योम opal_lpc_outb(u8 val, अचिन्हित दीर्घ port)
अणु
	अगर (opal_lpc_chip_id < 0 || port > 0xffff)
		वापस;
	opal_lpc_ग_लिखो(opal_lpc_chip_id, OPAL_LPC_IO, port, val, 1);
पूर्ण

अटल व्योम __opal_lpc_outw(__le16 val, अचिन्हित दीर्घ port)
अणु
	अगर (opal_lpc_chip_id < 0 || port > 0xfffe)
		वापस;
	अगर (port & 1) अणु
		opal_lpc_outb(val >> 8, port);
		opal_lpc_outb(val     , port + 1);
		वापस;
	पूर्ण
	opal_lpc_ग_लिखो(opal_lpc_chip_id, OPAL_LPC_IO, port, val, 2);
पूर्ण

अटल व्योम opal_lpc_outw(u16 val, अचिन्हित दीर्घ port)
अणु
	__opal_lpc_outw(cpu_to_le16(val), port);
पूर्ण

अटल व्योम __opal_lpc_outl(__le32 val, अचिन्हित दीर्घ port)
अणु
	अगर (opal_lpc_chip_id < 0 || port > 0xfffc)
		वापस;
	अगर (port & 3) अणु
		opal_lpc_outb(val >> 24, port);
		opal_lpc_outb(val >> 16, port + 1);
		opal_lpc_outb(val >>  8, port + 2);
		opal_lpc_outb(val      , port + 3);
		वापस;
	पूर्ण
	opal_lpc_ग_लिखो(opal_lpc_chip_id, OPAL_LPC_IO, port, val, 4);
पूर्ण

अटल व्योम opal_lpc_outl(u32 val, अचिन्हित दीर्घ port)
अणु
	__opal_lpc_outl(cpu_to_le32(val), port);
पूर्ण

अटल व्योम opal_lpc_insb(अचिन्हित दीर्घ p, व्योम *b, अचिन्हित दीर्घ c)
अणु
	u8 *ptr = b;

	जबतक(c--)
		*(ptr++) = opal_lpc_inb(p);
पूर्ण

अटल व्योम opal_lpc_insw(अचिन्हित दीर्घ p, व्योम *b, अचिन्हित दीर्घ c)
अणु
	__le16 *ptr = b;

	जबतक(c--)
		*(ptr++) = __opal_lpc_inw(p);
पूर्ण

अटल व्योम opal_lpc_insl(अचिन्हित दीर्घ p, व्योम *b, अचिन्हित दीर्घ c)
अणु
	__le32 *ptr = b;

	जबतक(c--)
		*(ptr++) = __opal_lpc_inl(p);
पूर्ण

अटल व्योम opal_lpc_outsb(अचिन्हित दीर्घ p, स्थिर व्योम *b, अचिन्हित दीर्घ c)
अणु
	स्थिर u8 *ptr = b;

	जबतक(c--)
		opal_lpc_outb(*(ptr++), p);
पूर्ण

अटल व्योम opal_lpc_outsw(अचिन्हित दीर्घ p, स्थिर व्योम *b, अचिन्हित दीर्घ c)
अणु
	स्थिर __le16 *ptr = b;

	जबतक(c--)
		__opal_lpc_outw(*(ptr++), p);
पूर्ण

अटल व्योम opal_lpc_outsl(अचिन्हित दीर्घ p, स्थिर व्योम *b, अचिन्हित दीर्घ c)
अणु
	स्थिर __le32 *ptr = b;

	जबतक(c--)
		__opal_lpc_outl(*(ptr++), p);
पूर्ण

अटल स्थिर काष्ठा ppc_pci_io opal_lpc_io = अणु
	.inb	= opal_lpc_inb,
	.inw	= opal_lpc_inw,
	.inl	= opal_lpc_inl,
	.outb	= opal_lpc_outb,
	.outw	= opal_lpc_outw,
	.outl	= opal_lpc_outl,
	.insb	= opal_lpc_insb,
	.insw	= opal_lpc_insw,
	.insl	= opal_lpc_insl,
	.outsb	= opal_lpc_outsb,
	.outsw	= opal_lpc_outsw,
	.outsl	= opal_lpc_outsl,
पूर्ण;

#अगर_घोषित CONFIG_DEBUG_FS
काष्ठा lpc_debugfs_entry अणु
	क्रमागत OpalLPCAddressType lpc_type;
पूर्ण;

अटल sमाप_प्रकार lpc_debug_पढ़ो(काष्ठा file *filp, अक्षर __user *ubuf,
			      माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा lpc_debugfs_entry *lpc = filp->निजी_data;
	u32 data, pos, len, toकरो;
	पूर्णांक rc;

	अगर (!access_ok(ubuf, count))
		वापस -EFAULT;

	toकरो = count;
	जबतक (toकरो) अणु
		pos = *ppos;

		/*
		 * Select access size based on count and alignment and
		 * access type. IO and MEM only support byte acceses,
		 * FW supports all 3.
		 */
		len = 1;
		अगर (lpc->lpc_type == OPAL_LPC_FW) अणु
			अगर (toकरो > 3 && (pos & 3) == 0)
				len = 4;
			अन्यथा अगर (toकरो > 1 && (pos & 1) == 0)
				len = 2;
		पूर्ण
		rc = opal_lpc_पढ़ो(opal_lpc_chip_id, lpc->lpc_type, pos,
				   &data, len);
		अगर (rc)
			वापस -ENXIO;

		/*
		 * Now there is some trickery with the data वापसed by OPAL
		 * as it's the desired data right justअगरied in a 32-bit BE
		 * word.
		 *
		 * This is a very bad पूर्णांकerface and I'm to blame क्रम it :-(
		 *
		 * So we can't just apply a 32-bit swap to what comes from OPAL,
		 * because user space expects the *bytes* to be in their proper
		 * respective positions (ie, LPC position).
		 *
		 * So what we really want to करो here is to shअगरt data right
		 * appropriately on a LE kernel.
		 *
		 * IE. If the LPC transaction has bytes B0, B1, B2 and B3 in that
		 * order, we have in memory written to by OPAL at the "data"
		 * poपूर्णांकer:
		 *
		 *               Bytes:      OPAL "data"   LE "data"
		 *   32-bit:   B0 B1 B2 B3   B0B1B2B3      B3B2B1B0
		 *   16-bit:   B0 B1         0000B0B1      B1B00000
		 *    8-bit:   B0            000000B0      B0000000
		 *
		 * So a BE kernel will have the lefपंचांगost of the above in the MSB
		 * and righपंचांगost in the LSB and can just then "cast" the u32 "data"
		 * करोwn to the appropriate quantity and ग_लिखो it.
		 *
		 * However, an LE kernel can't. It doesn't need to swap because a
		 * load from data followed by a store to user are going to preserve
		 * the byte ordering which is the wire byte order which is what the
		 * user wants, but in order to "crop" to the right size, we need to
		 * shअगरt right first.
		 */
		चयन(len) अणु
		हाल 4:
			rc = __put_user((u32)data, (u32 __user *)ubuf);
			अवरोध;
		हाल 2:
#अगर_घोषित __LITTLE_ENDIAN__
			data >>= 16;
#पूर्ण_अगर
			rc = __put_user((u16)data, (u16 __user *)ubuf);
			अवरोध;
		शेष:
#अगर_घोषित __LITTLE_ENDIAN__
			data >>= 24;
#पूर्ण_अगर
			rc = __put_user((u8)data, (u8 __user *)ubuf);
			अवरोध;
		पूर्ण
		अगर (rc)
			वापस -EFAULT;
		*ppos += len;
		ubuf += len;
		toकरो -= len;
	पूर्ण

	वापस count;
पूर्ण

अटल sमाप_प्रकार lpc_debug_ग_लिखो(काष्ठा file *filp, स्थिर अक्षर __user *ubuf,
			       माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा lpc_debugfs_entry *lpc = filp->निजी_data;
	u32 data, pos, len, toकरो;
	पूर्णांक rc;

	अगर (!access_ok(ubuf, count))
		वापस -EFAULT;

	toकरो = count;
	जबतक (toकरो) अणु
		pos = *ppos;

		/*
		 * Select access size based on count and alignment and
		 * access type. IO and MEM only support byte acceses,
		 * FW supports all 3.
		 */
		len = 1;
		अगर (lpc->lpc_type == OPAL_LPC_FW) अणु
			अगर (toकरो > 3 && (pos & 3) == 0)
				len = 4;
			अन्यथा अगर (toकरो > 1 && (pos & 1) == 0)
				len = 2;
		पूर्ण

		/*
		 * Similarly to the पढ़ो हाल, we have some trickery here but
		 * it's dअगरferent to handle. We need to pass the value to OPAL in
		 * a रेजिस्टर whose layout depends on the access size. We want
		 * to reproduce the memory layout of the user, however we aren't
		 * करोing a load from user and a store to another memory location
		 * which would achieve that. Here we pass the value to OPAL via
		 * a रेजिस्टर which is expected to contain the "BE" पूर्णांकerpretation
		 * of the byte sequence. IE: क्रम a 32-bit access, byte 0 should be
		 * in the MSB. So here we *करो* need to byteswap on LE.
		 *
		 *           User bytes:    LE "data"  OPAL "data"
		 *  32-bit:  B0 B1 B2 B3    B3B2B1B0   B0B1B2B3
		 *  16-bit:  B0 B1          0000B1B0   0000B0B1
		 *   8-bit:  B0             000000B0   000000B0
		 */
		चयन(len) अणु
		हाल 4:
			rc = __get_user(data, (u32 __user *)ubuf);
			data = cpu_to_be32(data);
			अवरोध;
		हाल 2:
			rc = __get_user(data, (u16 __user *)ubuf);
			data = cpu_to_be16(data);
			अवरोध;
		शेष:
			rc = __get_user(data, (u8 __user *)ubuf);
			अवरोध;
		पूर्ण
		अगर (rc)
			वापस -EFAULT;

		rc = opal_lpc_ग_लिखो(opal_lpc_chip_id, lpc->lpc_type, pos,
				    data, len);
		अगर (rc)
			वापस -ENXIO;
		*ppos += len;
		ubuf += len;
		toकरो -= len;
	पूर्ण

	वापस count;
पूर्ण

अटल स्थिर काष्ठा file_operations lpc_fops = अणु
	.पढ़ो =		lpc_debug_पढ़ो,
	.ग_लिखो =	lpc_debug_ग_लिखो,
	.खोलो =		simple_खोलो,
	.llseek =	शेष_llseek,
पूर्ण;

अटल पूर्णांक opal_lpc_debugfs_create_type(काष्ठा dentry *folder,
					स्थिर अक्षर *fname,
					क्रमागत OpalLPCAddressType type)
अणु
	काष्ठा lpc_debugfs_entry *entry;
	entry = kzalloc(माप(*entry), GFP_KERNEL);
	अगर (!entry)
		वापस -ENOMEM;
	entry->lpc_type = type;
	debugfs_create_file(fname, 0600, folder, entry, &lpc_fops);
	वापस 0;
पूर्ण

अटल पूर्णांक opal_lpc_init_debugfs(व्योम)
अणु
	काष्ठा dentry *root;
	पूर्णांक rc = 0;

	अगर (opal_lpc_chip_id < 0)
		वापस -ENODEV;

	root = debugfs_create_dir("lpc", घातerpc_debugfs_root);

	rc |= opal_lpc_debugfs_create_type(root, "io", OPAL_LPC_IO);
	rc |= opal_lpc_debugfs_create_type(root, "mem", OPAL_LPC_MEM);
	rc |= opal_lpc_debugfs_create_type(root, "fw", OPAL_LPC_FW);
	वापस rc;
पूर्ण
machine_device_initcall(घातernv, opal_lpc_init_debugfs);
#पूर्ण_अगर  /* CONFIG_DEBUG_FS */

व्योम __init opal_lpc_init(व्योम)
अणु
	काष्ठा device_node *np;

	/*
	 * Look क्रम a Power8 LPC bus tagged as "primary",
	 * we currently support only one though the OPAL APIs
	 * support any number.
	 */
	क्रम_each_compatible_node(np, शून्य, "ibm,power8-lpc") अणु
		अगर (!of_device_is_available(np))
			जारी;
		अगर (!of_get_property(np, "primary", शून्य))
			जारी;
		opal_lpc_chip_id = of_get_ibm_chip_id(np);
		अवरोध;
	पूर्ण
	अगर (opal_lpc_chip_id < 0)
		वापस;

	/* Does it support direct mapping ? */
	अगर (of_get_property(np, "ranges", शून्य)) अणु
		pr_info("OPAL: Found memory mapped LPC bus on chip %d\n",
			opal_lpc_chip_id);
		isa_bridge_init_non_pci(np);
	पूर्ण अन्यथा अणु
		pr_info("OPAL: Found non-mapped LPC bus on chip %d\n",
			opal_lpc_chip_id);

		/* Setup special IO ops */
		ppc_pci_io = opal_lpc_io;
		isa_io_special = true;
	पूर्ण
पूर्ण
