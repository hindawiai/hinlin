<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * memconsole-coreboot.c
 *
 * Memory based BIOS console accessed through coreboot table.
 *
 * Copyright 2017 Google Inc.
 */

#समावेश <linux/device.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>

#समावेश "memconsole.h"
#समावेश "coreboot_table.h"

#घोषणा CB_TAG_CBMEM_CONSOLE	0x17

/* CBMEM firmware console log descriptor. */
काष्ठा cbmem_cons अणु
	u32 size_करोnt_access_after_boot;
	u32 cursor;
	u8  body[];
पूर्ण __packed;

#घोषणा CURSOR_MASK ((1 << 28) - 1)
#घोषणा OVERFLOW (1 << 31)

अटल काष्ठा cbmem_cons *cbmem_console;
अटल u32 cbmem_console_size;

/*
 * The cbmem_console काष्ठाure is पढ़ो again on every access because it may
 * change at any समय अगर runसमय firmware logs new messages. This may rarely
 * lead to race conditions where the firmware overग_लिखोs the beginning of the
 * ring buffer with more lines after we have alपढ़ोy पढ़ो |cursor|. It should be
 * rare and harmless enough that we करोn't spend extra efक्रमt working around it.
 */
अटल sमाप_प्रकार memconsole_coreboot_पढ़ो(अक्षर *buf, loff_t pos, माप_प्रकार count)
अणु
	u32 cursor = cbmem_console->cursor & CURSOR_MASK;
	u32 flags = cbmem_console->cursor & ~CURSOR_MASK;
	u32 size = cbmem_console_size;
	काष्ठा seg अणु	/* describes ring buffer segments in logical order */
		u32 phys;	/* physical offset from start of mem buffer */
		u32 len;	/* length of segment */
	पूर्ण seg[2] = अणु अणु0पूर्ण, अणु0पूर्ण पूर्ण;
	माप_प्रकार करोne = 0;
	पूर्णांक i;

	अगर (flags & OVERFLOW) अणु
		अगर (cursor > size)	/* Shouldn't really happen, but... */
			cursor = 0;
		seg[0] = (काष्ठा seg)अणु.phys = cursor, .len = size - cursorपूर्ण;
		seg[1] = (काष्ठा seg)अणु.phys = 0, .len = cursorपूर्ण;
	पूर्ण अन्यथा अणु
		seg[0] = (काष्ठा seg)अणु.phys = 0, .len = min(cursor, size)पूर्ण;
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(seg) && count > करोne; i++) अणु
		करोne += memory_पढ़ो_from_buffer(buf + करोne, count - करोne, &pos,
			cbmem_console->body + seg[i].phys, seg[i].len);
		pos -= seg[i].len;
	पूर्ण
	वापस करोne;
पूर्ण

अटल पूर्णांक memconsole_probe(काष्ठा coreboot_device *dev)
अणु
	काष्ठा cbmem_cons *पंचांगp_cbmc;

	पंचांगp_cbmc = memremap(dev->cbmem_ref.cbmem_addr,
			    माप(*पंचांगp_cbmc), MEMREMAP_WB);

	अगर (!पंचांगp_cbmc)
		वापस -ENOMEM;

	/* Read size only once to prevent overrun attack through /dev/mem. */
	cbmem_console_size = पंचांगp_cbmc->size_करोnt_access_after_boot;
	cbmem_console = devm_memremap(&dev->dev, dev->cbmem_ref.cbmem_addr,
				 cbmem_console_size + माप(*cbmem_console),
				 MEMREMAP_WB);
	memunmap(पंचांगp_cbmc);

	अगर (IS_ERR(cbmem_console))
		वापस PTR_ERR(cbmem_console);

	memconsole_setup(memconsole_coreboot_पढ़ो);

	वापस memconsole_sysfs_init();
पूर्ण

अटल व्योम memconsole_हटाओ(काष्ठा coreboot_device *dev)
अणु
	memconsole_निकास();
पूर्ण

अटल काष्ठा coreboot_driver memconsole_driver = अणु
	.probe = memconsole_probe,
	.हटाओ = memconsole_हटाओ,
	.drv = अणु
		.name = "memconsole",
	पूर्ण,
	.tag = CB_TAG_CBMEM_CONSOLE,
पूर्ण;
module_coreboot_driver(memconsole_driver);

MODULE_AUTHOR("Google, Inc.");
MODULE_LICENSE("GPL");
