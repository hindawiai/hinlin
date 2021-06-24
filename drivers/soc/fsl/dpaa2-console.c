<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0+ OR BSD-3-Clause)
/*
 * Freescale DPAA2 Platक्रमms Console Driver
 *
 * Copyright 2015-2016 Freescale Semiconductor Inc.
 * Copyright 2018 NXP
 */

#घोषणा pr_fmt(fmt) "dpaa2-console: " fmt

#समावेश <linux/module.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_address.h>
#समावेश <linux/miscdevice.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/slab.h>
#समावेश <linux/fs.h>
#समावेश <linux/पन.स>

/* MC firmware base low/high रेजिस्टरs indexes */
#घोषणा MCFBALR_OFFSET 0
#घोषणा MCFBAHR_OFFSET 1

/* Bit masks used to get the most/least signअगरicant part of the MC base addr */
#घोषणा MC_FW_ADDR_MASK_HIGH 0x1FFFF
#घोषणा MC_FW_ADDR_MASK_LOW  0xE0000000

#घोषणा MC_BUFFER_OFFSET 0x01000000
#घोषणा MC_BUFFER_SIZE   (1024 * 1024 * 16)
#घोषणा MC_OFFSET_DELTA  MC_BUFFER_OFFSET

#घोषणा AIOP_BUFFER_OFFSET 0x06000000
#घोषणा AIOP_BUFFER_SIZE   (1024 * 1024 * 16)
#घोषणा AIOP_OFFSET_DELTA  0

#घोषणा LOG_HEADER_FLAG_BUFFER_WRAPAROUND 0x80000000
#घोषणा LAST_BYTE(a) ((a) & ~(LOG_HEADER_FLAG_BUFFER_WRAPAROUND))

/* MC and AIOP Magic words */
#घोषणा MAGIC_MC   0x4d430100
#घोषणा MAGIC_AIOP 0x41494F50

काष्ठा log_header अणु
	__le32 magic_word;
	अक्षर reserved[4];
	__le32 buf_start;
	__le32 buf_length;
	__le32 last_byte;
पूर्ण;

काष्ठा console_data अणु
	व्योम __iomem *map_addr;
	काष्ठा log_header __iomem *hdr;
	व्योम __iomem *start_addr;
	व्योम __iomem *end_addr;
	व्योम __iomem *end_of_data;
	व्योम __iomem *cur_ptr;
पूर्ण;

अटल काष्ठा resource mc_base_addr;

अटल अंतरभूत व्योम adjust_end(काष्ठा console_data *cd)
अणु
	u32 last_byte = पढ़ोl(&cd->hdr->last_byte);

	cd->end_of_data = cd->start_addr + LAST_BYTE(last_byte);
पूर्ण

अटल u64 get_mc_fw_base_address(व्योम)
अणु
	u64 mcfwbase = 0ULL;
	u32 __iomem *mcfbaregs;

	mcfbaregs = ioremap(mc_base_addr.start, resource_size(&mc_base_addr));
	अगर (!mcfbaregs) अणु
		pr_err("could not map MC Firmware Base registers\n");
		वापस 0;
	पूर्ण

	mcfwbase  = पढ़ोl(mcfbaregs + MCFBAHR_OFFSET) &
			  MC_FW_ADDR_MASK_HIGH;
	mcfwbase <<= 32;
	mcfwbase |= पढ़ोl(mcfbaregs + MCFBALR_OFFSET) & MC_FW_ADDR_MASK_LOW;
	iounmap(mcfbaregs);

	pr_debug("MC base address at 0x%016llx\n", mcfwbase);
	वापस mcfwbase;
पूर्ण

अटल sमाप_प्रकार dpaa2_console_size(काष्ठा console_data *cd)
अणु
	sमाप_प्रकार size;

	अगर (cd->cur_ptr <= cd->end_of_data)
		size = cd->end_of_data - cd->cur_ptr;
	अन्यथा
		size = (cd->end_addr - cd->cur_ptr) +
			(cd->end_of_data - cd->start_addr);

	वापस size;
पूर्ण

अटल पूर्णांक dpaa2_generic_console_खोलो(काष्ठा inode *node, काष्ठा file *fp,
				      u64 offset, u64 size,
				      u32 expected_magic,
				      u32 offset_delta)
अणु
	u32 पढ़ो_magic, wrapped, last_byte, buf_start, buf_length;
	काष्ठा console_data *cd;
	u64 base_addr;
	पूर्णांक err;

	cd = kदो_स्मृति(माप(*cd), GFP_KERNEL);
	अगर (!cd)
		वापस -ENOMEM;

	base_addr = get_mc_fw_base_address();
	अगर (!base_addr) अणु
		err = -EIO;
		जाओ err_fwba;
	पूर्ण

	cd->map_addr = ioremap(base_addr + offset, size);
	अगर (!cd->map_addr) अणु
		pr_err("cannot map console log memory\n");
		err = -EIO;
		जाओ err_ioremap;
	पूर्ण

	cd->hdr = (काष्ठा log_header __iomem *)cd->map_addr;
	पढ़ो_magic = पढ़ोl(&cd->hdr->magic_word);
	last_byte =  पढ़ोl(&cd->hdr->last_byte);
	buf_start =  पढ़ोl(&cd->hdr->buf_start);
	buf_length = पढ़ोl(&cd->hdr->buf_length);

	अगर (पढ़ो_magic != expected_magic) अणु
		pr_warn("expected = %08x, read = %08x\n",
			expected_magic, पढ़ो_magic);
		err = -EIO;
		जाओ err_magic;
	पूर्ण

	cd->start_addr = cd->map_addr + buf_start - offset_delta;
	cd->end_addr = cd->start_addr + buf_length;

	wrapped = last_byte & LOG_HEADER_FLAG_BUFFER_WRAPAROUND;

	adjust_end(cd);
	अगर (wrapped && cd->end_of_data != cd->end_addr)
		cd->cur_ptr = cd->end_of_data + 1;
	अन्यथा
		cd->cur_ptr = cd->start_addr;

	fp->निजी_data = cd;

	वापस 0;

err_magic:
	iounmap(cd->map_addr);

err_ioremap:
err_fwba:
	kमुक्त(cd);

	वापस err;
पूर्ण

अटल पूर्णांक dpaa2_mc_console_खोलो(काष्ठा inode *node, काष्ठा file *fp)
अणु
	वापस dpaa2_generic_console_खोलो(node, fp,
					  MC_BUFFER_OFFSET, MC_BUFFER_SIZE,
					  MAGIC_MC, MC_OFFSET_DELTA);
पूर्ण

अटल पूर्णांक dpaa2_aiop_console_खोलो(काष्ठा inode *node, काष्ठा file *fp)
अणु
	वापस dpaa2_generic_console_खोलो(node, fp,
					  AIOP_BUFFER_OFFSET, AIOP_BUFFER_SIZE,
					  MAGIC_AIOP, AIOP_OFFSET_DELTA);
पूर्ण

अटल पूर्णांक dpaa2_console_बंद(काष्ठा inode *node, काष्ठा file *fp)
अणु
	काष्ठा console_data *cd = fp->निजी_data;

	iounmap(cd->map_addr);
	kमुक्त(cd);
	वापस 0;
पूर्ण

अटल sमाप_प्रकार dpaa2_console_पढ़ो(काष्ठा file *fp, अक्षर __user *buf,
				  माप_प्रकार count, loff_t *f_pos)
अणु
	काष्ठा console_data *cd = fp->निजी_data;
	माप_प्रकार bytes = dpaa2_console_size(cd);
	माप_प्रकार bytes_end = cd->end_addr - cd->cur_ptr;
	माप_प्रकार written = 0;
	व्योम *kbuf;
	पूर्णांक err;

	/* Check अगर we need to adjust the end of data addr */
	adjust_end(cd);

	अगर (cd->end_of_data == cd->cur_ptr)
		वापस 0;

	अगर (count < bytes)
		bytes = count;

	kbuf = kदो_स्मृति(bytes, GFP_KERNEL);
	अगर (!kbuf)
		वापस -ENOMEM;

	अगर (bytes > bytes_end) अणु
		स_नकल_fromio(kbuf, cd->cur_ptr, bytes_end);
		अगर (copy_to_user(buf, kbuf, bytes_end)) अणु
			err = -EFAULT;
			जाओ err_मुक्त_buf;
		पूर्ण
		buf += bytes_end;
		cd->cur_ptr = cd->start_addr;
		bytes -= bytes_end;
		written += bytes_end;
	पूर्ण

	स_नकल_fromio(kbuf, cd->cur_ptr, bytes);
	अगर (copy_to_user(buf, kbuf, bytes)) अणु
		err = -EFAULT;
		जाओ err_मुक्त_buf;
	पूर्ण
	cd->cur_ptr += bytes;
	written += bytes;

	वापस written;

err_मुक्त_buf:
	kमुक्त(kbuf);

	वापस err;
पूर्ण

अटल स्थिर काष्ठा file_operations dpaa2_mc_console_fops = अणु
	.owner          = THIS_MODULE,
	.खोलो           = dpaa2_mc_console_खोलो,
	.release        = dpaa2_console_बंद,
	.पढ़ो           = dpaa2_console_पढ़ो,
पूर्ण;

अटल काष्ठा miscdevice dpaa2_mc_console_dev = अणु
	.minor = MISC_DYNAMIC_MINOR,
	.name = "dpaa2_mc_console",
	.fops = &dpaa2_mc_console_fops
पूर्ण;

अटल स्थिर काष्ठा file_operations dpaa2_aiop_console_fops = अणु
	.owner          = THIS_MODULE,
	.खोलो           = dpaa2_aiop_console_खोलो,
	.release        = dpaa2_console_बंद,
	.पढ़ो           = dpaa2_console_पढ़ो,
पूर्ण;

अटल काष्ठा miscdevice dpaa2_aiop_console_dev = अणु
	.minor = MISC_DYNAMIC_MINOR,
	.name = "dpaa2_aiop_console",
	.fops = &dpaa2_aiop_console_fops
पूर्ण;

अटल पूर्णांक dpaa2_console_probe(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक error;

	error = of_address_to_resource(pdev->dev.of_node, 0, &mc_base_addr);
	अगर (error < 0) अणु
		pr_err("of_address_to_resource() failed for %pOF with %d\n",
		       pdev->dev.of_node, error);
		वापस error;
	पूर्ण

	error = misc_रेजिस्टर(&dpaa2_mc_console_dev);
	अगर (error) अणु
		pr_err("cannot register device %s\n",
		       dpaa2_mc_console_dev.name);
		जाओ err_रेजिस्टर_mc;
	पूर्ण

	error = misc_रेजिस्टर(&dpaa2_aiop_console_dev);
	अगर (error) अणु
		pr_err("cannot register device %s\n",
		       dpaa2_aiop_console_dev.name);
		जाओ err_रेजिस्टर_aiop;
	पूर्ण

	वापस 0;

err_रेजिस्टर_aiop:
	misc_deरेजिस्टर(&dpaa2_mc_console_dev);
err_रेजिस्टर_mc:
	वापस error;
पूर्ण

अटल पूर्णांक dpaa2_console_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	misc_deरेजिस्टर(&dpaa2_mc_console_dev);
	misc_deरेजिस्टर(&dpaa2_aiop_console_dev);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id dpaa2_console_match_table[] = अणु
	अणु .compatible = "fsl,dpaa2-console",पूर्ण,
	अणुपूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(of, dpaa2_console_match_table);

अटल काष्ठा platक्रमm_driver dpaa2_console_driver = अणु
	.driver = अणु
		   .name = "dpaa2-console",
		   .pm = शून्य,
		   .of_match_table = dpaa2_console_match_table,
		   पूर्ण,
	.probe = dpaa2_console_probe,
	.हटाओ = dpaa2_console_हटाओ,
पूर्ण;
module_platक्रमm_driver(dpaa2_console_driver);

MODULE_LICENSE("Dual BSD/GPL");
MODULE_AUTHOR("Roy Pledge <roy.pledge@nxp.com>");
MODULE_DESCRIPTION("DPAA2 console driver");
